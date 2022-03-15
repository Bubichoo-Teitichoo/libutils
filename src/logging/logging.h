#if !defined(__LOGGING_H__)
#define __LOGGING_H__

#include <stdio.h>
#include <time.h>

#define log_error( fmt, ... ) log_write( LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__ )
#define log_warn( fmt, ... )  log_write( LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__ )
#define log_info( fmt, ... )  log_write( LOG_LEVEL_INFO, fmt, ##__VA_ARGS__ )
#define log_debug( fmt, ... ) log_write( LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__ )
#define log_trace( fmt, ... ) log_write( LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__ )

enum log_level
{
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE
};
typedef enum log_level log_level_t;

/// @brief opaque structure that holds sink informations
typedef struct log_sink log_sink_t;

typedef void ( *log_message_sink )( const log_level_t level, struct timespec *ts, const char *msg, void *data );

void log_write( const log_level_t level, const char *fmt, ... );
void log_set_level(log_sink_t *sink, const log_level_t loglevel );

log_sink_t *log_add_cb_sink( log_message_sink callback, const log_level_t loglevel, void *data );
log_sink_t *log_add_file_sink( FILE *file, const log_level_t loglevel, int colored );

void log_remove_sink( const log_sink_t *id );

const char *log_level_to_string( const log_level_t lvl );

#endif // __LOGGING_H__