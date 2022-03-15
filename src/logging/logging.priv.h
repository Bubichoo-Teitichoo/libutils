#if !defined(__LOGGING_PRIV_H__)
#define __LOGGING_PRIV_H__

#if defined( _MSC_VER )

#include <Windows.h>

#define CLOCK_REALTIME 1

#define xplocaltime( TIME_T, TM ) localtime_s( ( TM ), ( TIME_T ) )

static int clock_gettime(int a, struct timespec* spec)
{
	__int64 wintime;
	GetSystemTimeAsFileTime((FILETIME*)&wintime);
	wintime -= 116444736000000000i64;              // 1jan1601 to 1jan1970
	spec->tv_sec = wintime / 10000000i64;         // seconds
	spec->tv_nsec = wintime % 10000000i64 * 100;   // nano-seconds
	return 0;
}

#else

#define xplocaltime( TIME_T, TM ) localtime_r( ( TIME_T ), ( TM ) )

#endif

#endif // __LOGGING_PRIV_H__