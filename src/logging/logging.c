#if defined( _MSC_VER )
#include <Windows.h>
#endif

#include <stdarg.h>
#include <string.h>

#include "logging.h"

#if defined( _MSC_VER )
#define xplocaltime( TIME_T, TM ) localtime_s( ( TM ), ( TIME_T ) )
#else
#define xplocaltime( TIME_T, TM ) localtime_r( ( TIME_T ), ( TM ) )
#endif

struct log_sink
{
	FILE* file;
	int colored;
	log_message_sink callback;
	void* data;
};

static log_level_t max_level = LOG_LEVEL_INFO;

#if defined( _MSC_VER )
#define CLOCK_REALTIME 1

static int clock_gettime(int a, struct timespec* spec)
{
	__int64 wintime;
	GetSystemTimeAsFileTime((FILETIME*)&wintime);
	wintime -= 116444736000000000i64;              // 1jan1601 to 1jan1970
	spec->tv_sec = wintime / 10000000i64;         // seconds
	spec->tv_nsec = wintime % 10000000i64 * 100;   // nano-seconds
	return 0;
}
#endif

static char* log_level_to_ansii_color_string(const log_level_t lvl);
static void log_create_timestamp(char* buf, size_t len, struct timespec* ts);

void log_write(const log_level_t lvl, const char* fmt, ...)
{
	va_list ap;
	struct timespec now = { 0 };
	char ts[32] = { 0 };
	char msg[256] = { 0 };

	if (lvl <= max_level)
	{
		clock_gettime(CLOCK_REALTIME, &now);

		va_start(ap, fmt);
		vsnprintf(msg, sizeof(msg), fmt, ap);
		va_end(ap);

		log_create_timestamp(ts, sizeof(ts), &now);

		const char* lvlstr = log_level_to_ansii_color_string(lvl);

		fprintf(stderr, "%s [%s] %s\n", ts, lvlstr, msg);

		//for (size_t i = 0U; i < dynamic_array_len(sinks); i++)
		//{
		//	log_sink_t sink = DYNAMIC_ARRAY_GET_CAST(sinks, i, log_sink_t);
		//	if (NULL != sink.file)
		//	{
		//		char ts[32] = { 0 };
		//		log_create_timestamp(ts, sizeof(ts), &now);
		//
		//		const char* lvlstr;
		//		if (sink.colored)
		//		{
		//			lvlstr = log_level_to_ansii_color_string(lvl);
		//		}
		//		else
		//		{
		//			lvlstr = log_level_to_string(lvl);
		//		}
		//		fprintf(sink.file, "%s [%s] %s\n", ts, lvlstr, msg);
		//	}
		//	else if (NULL != sink.callback)
		//	{
		//		sink.callback(lvl, &now, msg, sink.data);
		//	}
		//}
	}
}

void log_set_level(const log_level_t loglevel)
{
	max_level = loglevel;
	log_debug("log level changed to %s", log_level_to_string(loglevel));
}

log_sink_t* log_add_cb_sink(log_message_sink callback, void* data)
{
	//log_sink_t sink = { 0 };
	//sink.callback = callback;
	//sink.data = data;
	//return dynamic_array_append(sinks, &sink);
	return NULL;
}

log_sink_t* log_add_file_sink(FILE* file, int colored)
{
	//log_sink_t sink = { 0 };
	//sink.file = file;
	//sink.colored = colored;
	//return dynamic_array_append(sinks, &sink);
	return NULL;
}

void log_remove_sink(const log_sink_t* sink)
{
	//size_t i = 0U;
	//for (; i < dynamic_array_len(sinks); i++)
	//{
	//	if (sink == dynamic_array_get(sinks, i))
	//	{
	//		dynamic_array_remove_fast(sinks, i);
	//	}
	//}
}


const char* log_level_to_string(const log_level_t lvl)
{
	switch (lvl)
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

static char* log_level_to_ansii_color_string(const log_level_t lvl)
{
	switch (lvl)
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

static void log_create_timestamp(char* buf, size_t len, struct timespec* ts)
{
	struct tm tm = { 0 };
	xplocaltime(&ts->tv_sec, &tm);

	char timestamp[32] = { 0 };
	strftime(timestamp, sizeof(timestamp), "%F %T", &tm);
	snprintf(buf, len, "%s.%.03ld", timestamp, ts->tv_nsec / 1000000);
}
