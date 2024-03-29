#include "logging.h"
#include "logging.priv.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "dynamic-array.h"
#include "threads.h"

enum log_sink_type
{
    LOG_SINK_INVALID = 0,
    LOG_SINK_CB,
    LOG_SINK_FILE
};

typedef struct
{
    log_message_sink callback;
    void *data;
} log_callback_sink_t;

typedef struct
{
    FILE *file;
    int opened;
    int colored;
} log_file_sink_t;

struct log_sink
{
    log_callback_sink_t cbsink;
    log_file_sink_t fsink;
    log_level_t max;
    enum log_sink_type type;
};

static dynamic_array_t *sinks = NULL;
static mtx_t mtx;
static log_sink_t default_sink = { 
    .type = LOG_SINK_FILE,
    .max = LOG_LEVEL_WARNING, 
    .fsink.file = NULL,
    .fsink.colored = 1,
    .fsink.opened = 0
};

log_sink_t *default_log_sink = &default_sink;

static char *log_level_to_ansii_color_string( const log_level_t lvl );
static void log_create_timestamp( char *buf, size_t len, struct timespec *ts );

static inline void log_init( const int init_default );
static void log_finalize( void );
static inline log_sink_t *log_append_sink( const log_sink_t *sink );

static inline void log_init( const int init_default )
{
    static atomic_flag initialized = ATOMIC_FLAG_INIT;
    if( 0 == atomic_flag_test_and_set( &initialized ) )
    {
        mtx_init( &mtx, 0U );
        sinks = dynamic_array_new( sizeof( log_sink_t ), 10 );

        if( 1 == init_default )
        {
            default_log_sink->fsink.file = stderr;
            default_log_sink = log_append_sink( default_log_sink );
        }
        atexit( log_finalize );
    }
}

static void log_finalize( void )
{
    dynamic_array_free( sinks );
}

static inline log_sink_t *log_append_sink( const log_sink_t *sink )
{
    log_init( 0 );

    mtx_lock( &mtx );
    log_sink_t *retval = dynamic_array_append( sinks, sink );
    mtx_unlock( &mtx );
    return retval;
}

void log_write( const log_level_t lvl, const char *fmt, ... )
{
    log_init( 1 );

    struct timespec now = { 0 };
    clock_gettime( CLOCK_REALTIME, &now );

    char ts[ 64 ] = { 0 };
    log_create_timestamp( ts, sizeof( ts ), &now );

    va_list ap;
    va_start( ap, fmt );
    char msg[ 256 ] = { 0 };
    vsnprintf( msg, sizeof( msg ), fmt, ap );
    va_end( ap );

    const char *lvl_name         = log_level_to_string( lvl );
    const char *lvl_name_colored = log_level_to_ansii_color_string( lvl );

    for( size_t idx = 0U; idx < dynamic_array_len( sinks ); idx++ )
    {
        const log_sink_t *sink = dynamic_array_get( sinks, idx );
        if( lvl <= sink->max )
        {
            if( LOG_SINK_CB == sink->type )
            {
                sink->cbsink.callback( lvl, &now, msg, sink->cbsink.data );
            }
            else if( LOG_SINK_FILE == sink->type )
            {
                if( sink->fsink.colored )
                {
                    fprintf( sink->fsink.file, "%s [%s] %s\n", ts, lvl_name_colored, msg );
                }
                else
                {
                    fprintf( sink->fsink.file, "%s [%s] %s\n", ts, lvl_name, msg );
                }
            }
        }
    }
}

void log_set_level( log_sink_t *sink, const log_level_t loglevel )
{
    if( NULL != sink )
    {
        sink->max = loglevel;
    }
}

log_sink_t *log_add_cb_sink( log_message_sink callback, const log_level_t loglevel, void *data )
{
    const log_sink_t sink = { 
        .type   = LOG_SINK_CB, 
        .max    = loglevel,
        .fsink  = { 0 },
        .cbsink = { 
            .callback = callback, 
            .data     = data
        }
    };
    return log_append_sink( &sink );
}

log_sink_t *log_add_file_sink( FILE *file, const log_level_t loglevel, int colored )
{
    const log_sink_t sink = { 
        .type          = LOG_SINK_FILE,
        .fsink.file    = file,
        .fsink.opened  = 0,
        .fsink.colored = colored,
        .cbsink        = { 0 },
        .max           = loglevel 
    };
    return log_append_sink( &sink );
}

void log_remove_sink( const log_sink_t *const sink )
{
    mtx_lock( &mtx );
    for( size_t idx = 0U; idx < dynamic_array_len( sinks ); idx++ )
    {
        if( sink == dynamic_array_get( sinks, idx ) )
        {
            (void)dynamic_array_remove_fast( sinks, idx );
            break;
        }
    }
    mtx_unlock( &mtx );
}


const char *log_level_to_string( const log_level_t lvl )
{
    switch( lvl )
    {
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_WARNING:
            return "WARNING";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_TRACE:
            return "TRACE";
    }
    return NULL;
}

static char *log_level_to_ansii_color_string( const log_level_t lvl )
{
    switch( lvl )
    {
        case LOG_LEVEL_ERROR:
            return "\033[0;31mERROR\033[0;37m";
        case LOG_LEVEL_WARNING:
            return "\033[0;33mWARNING\033[0;37m";
        case LOG_LEVEL_INFO:
            return "\033[0;32mINFO\033[0;37m";
        case LOG_LEVEL_DEBUG:
            return "\033[0;35mDEBUG\033[0;37m";
        case LOG_LEVEL_TRACE:
            return "\033[0;36mTRACE\033[0;37m";
        default:
            return "\033[0;34mUNKN\033[0;37m";
    }
}

static void log_create_timestamp( char *buf, size_t len, struct timespec *ts )
{
    struct tm tm = { 0 };
    xplocaltime( &ts->tv_sec, &tm );

    char timestamp[ 32 ] = { 0 };
    strftime( timestamp, sizeof( timestamp ), "%F %T", &tm );
    snprintf( buf, len, "%s.%.03ld", timestamp, ts->tv_nsec / 1000000 );
}
