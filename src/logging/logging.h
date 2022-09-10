#if !defined(__LOGGING_H__)
#define __LOGGING_H__

/// 
/// @defgroup logging Logging
/// A simple Implementation of a logging module.
/// It allows the user to specify multiple log targets, named sinks.
/// @{
/// 

#include <stdio.h>
#include <time.h>

///
/// Write an error message to all sinks that are configured with #LOG_LEVEL_ERROR or less
/// 
#define log_error( fmt, ... ) log_write( LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__ )

/// 
/// Write a warning message to all sinks that are configured with #LOG_LEVEL_WARNING or less
/// 
#define log_warn( fmt, ... )  log_write( LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__ )

/// 
/// Write an if message to all sinks that are configured with #LOG_LEVEL_INFO or less
/// 
#define log_info( fmt, ... )  log_write( LOG_LEVEL_INFO, fmt, ##__VA_ARGS__ )

/// 
/// Write an if message to all sinks that are configured with #LOG_LEVEL_DEBUG or less
/// 
#define log_debug( fmt, ... ) log_write( LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__ )

/// 
/// Write an if message to all sinks that are configured with #LOG_LEVEL_TRACE or less
/// 
#define log_trace( fmt, ... ) log_write( LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__ )

/// @brief Available log severity levels
enum log_level
{
    /// 
    /// @brief severity level for an error message
    /// 
    /// If the colored argument of log_add_file_sink() the printed severity
    /// string will be red.
    /// 
    /// Use this level to indicate that the program ran into a potentially
    /// fatal runtime error that may lead to a crash.
    /// 
    LOG_LEVEL_ERROR,

    /// 
    /// @brief severity level for a warning message
    /// 
    /// If the colored argument of log_add_file_sink() the printed severity
    /// string will be yellow.
    /// 
    /// Use this level to indicate that something isn't working as expected but
    /// the program was able to handle the situation.
    ///
    LOG_LEVEL_WARNING,

    /// 
    /// @brief severity level for a info message
    /// 
    /// If the colored argument of log_add_file_sink() the printed severity
    /// string will be green.
    /// 
    /// use this level to display information
    ///
    LOG_LEVEL_INFO,

    /// 
    /// @brief severity level for a debug message
    /// 
    /// If the colored argument of log_add_file_sink() the printed severity
    /// string will be purple.
    /// 
    /// Use this level for messages that may be interesting for debugging.
    ///
    LOG_LEVEL_DEBUG,

    /// 
    /// @brief severity level for a trace message
    /// 
    /// If the colored argument of log_add_file_sink() the printed severity
    /// string will be light blue.
    /// 
    /// Use this level for messages that may be irrelevant for regular debugging
    /// but add a lot more context.
    ///
    LOG_LEVEL_TRACE
};
typedef enum log_level log_level_t;

/// @brief opaque structure that holds sink informations
typedef struct log_sink log_sink_t;

/// 
/// @memberof log_sink
/// 
/// @brief function definition for a log callback
/// 
/// When implementing a custom log callback this a function must be implemented
/// as defined by this typedef.
/// 
/// @param[in] level    The severity level of the message
/// @param[in] ts       The timestamp of the message
/// @param[in] msg      The message itself
/// @param[in] data     custom user data provided via the data argument of 
///                     log_add_cb_sink()
/// 
typedef void ( *log_message_sink )( const log_level_t level, const struct timespec *ts, const char *msg, void *data );

/// 
/// @brief Default log sink
/// 
/// This points to the default log sink that is added as a sink if, on init, no
/// other log sink is set.
/// 
/// By default this sink will log to stderr with colored output.
/// 
extern log_sink_t *default_log_sink;

/// @brief Write a log message to all sinks
/// 
/// This function will create and write a log message with the given severity
/// level and writes it to all sinks that have severity level of @p level or 
/// lower.
/// 
/// This function uses sprintf() to create the log message. This means that
/// format specifier that works with the printf function of the standard library
/// does work with this function.
/// 
/// @param[in] level    severity level of the message
/// @param[in] fmt      format string
/// @param[in] ...      varadic arguments
///   
void log_write( const log_level_t level, const char *fmt, ... );

/// 
/// @memberof log_sink
/// 
/// @brief Add a callback sink
/// 
/// A callback sink is a simple function that will be called each time a log
/// message is generated that has a severity level lower or equal to the one
/// set via @p loglevel.
/// 
/// The returned pointer can be used to modify the sink or remove it using 
/// log_remove_sink()
/// 
/// @param[in] callback     function to be called when a message is generated
/// @param[in] loglevel     initial minimum severity level for the sink
/// @param[in] data         custom user data that is passed to the callback
///                         function
/// 
/// @retval log_sink_t* Pointer to the newly created sink object.
log_sink_t *log_add_cb_sink( log_message_sink callback, const log_level_t loglevel, void *data );

/// 
/// @memberof log_sink
/// 
/// @brief Add a file sink.
/// 
/// This function will create and return a file sink object from an already
/// opened file.
/// Each generated log message will be written to the file if the set severity
/// is lower or equal to the serverity set via @p loglevel.
/// 
/// The returned pointer can be used to modify the sink or remove it using 
/// log_remove_sink()
/// 
/// @param[in] file         file to write to.
/// @param[in] loglevel     initial minimum severity level for the sink.
///                         log_set_level() can be used to change it.
/// @param[in] colored      If set to a non zero value the message will contain
///                         ANSII color codes to emphasize the severity of the
///                         message. 
/// @retval log_sink_t* Pointer to the newly created sink object.
log_sink_t *log_add_file_sink( FILE *file, const log_level_t loglevel, int colored );

/// 
/// @memberof log_sink
/// 
/// @brief Remove a log sink
/// 
/// @see log_add_cb_sink() and log_add_file_sink() on how to add a sink.
/// 
/// @param[in] sink     pointer to the sink that shall be removed.
/// 
void log_remove_sink( const log_sink_t *sink );

/// 
/// @brief Set maximum log level of a sink
/// 
/// @param[in] sink         The sink for which the level is to be set
/// @param[in] loglevel     Minimum message severity that shall be forwarded to
///                         the sink.
/// 
void log_set_level(log_sink_t *sink, const log_level_t loglevel );

/// 
/// @brief Turns severity level into string representation.
/// 
/// @param[in] lvl severity level that is to be converted into a string
///  
/// @retval "const char*" string representation of the given log level severity.
/// 
const char *log_level_to_string( const log_level_t lvl );

/// 
/// @}
/// 

#endif // __LOGGING_H__