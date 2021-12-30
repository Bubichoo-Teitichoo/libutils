#include "threads.h"
#include <process.h>

int thrd_create( thrd_t *tid, thrd_start_t func, void *arg )
{
    ( *tid ) = (HANDLE)_beginthreadex( NULL, 0U, func, arg, 0U, NULL );
    return ( ( NULL == *tid ) ? thrd_error : thrd_success );
}

int thrd_join( thrd_t tid, int *res )
{
    WaitForSingleObject( tid, INFINITE );

    DWORD retval;
    if( GetExitCodeThread( tid, &retval ) && CloseHandle( tid ) )
    {
        if( NULL != res )
        {
            *res = (int)retval;
        }
        return thrd_success;
    }
    return thrd_error;
}

thrd_t thrd_current( void )
{
    return GetCurrentThread();
}

int mtx_init( mtx_t *mutex, int type )
{
    *mutex = CreateMutex( NULL, FALSE, NULL );

    return ( ( NULL == *mutex ) ? thrd_error : thrd_success );
}

void mtx_destroy( mtx_t *mutex )
{
    CloseHandle( *mutex );
}

int mtx_lock( mtx_t *mutex )
{
    return ( ( WAIT_OBJECT_0 == WaitForSingleObject( *mutex, INFINITE ) ) ? thrd_success : thrd_error );
}

int mtx_trylock( mtx_t *mutex )
{
    const DWORD result = WaitForSingleObject( *mutex, 0U );
    switch( result )
    {
        case WAIT_OBJECT_0:
            return thrd_success;
        case WAIT_TIMEOUT:
            return thrd_busy;
        default:
            return thrd_error;
    }
}

int mtx_timedlock( mtx_t *mutex, const struct timespec *time_point )
{
    struct timespec now;
    timespec_get( &now, TIME_UTC );

    DWORD wait_time = ( (DWORD)time_point->tv_sec - (DWORD)now.tv_sec ) * 1000;
    if( 0 > wait_time )
    {
        wait_time = 0;
    }
    const DWORD result = WaitForSingleObject( *mutex, wait_time );
    switch( result )
    {
        case WAIT_OBJECT_0:
            return thrd_success;
        case WAIT_TIMEOUT:
            return thrd_timedout;
        default:
            return thrd_error;
    }

    return 0;
}

int mtx_unlock( mtx_t *mutex )
{
    return ( ( 0 != ReleaseMutex( *mutex ) ) ? thrd_success : thrd_error );
}

int cnd_init( cnd_t *cond )
{
    *cond = CreateEventEx( NULL, NULL, 0, 0 );
    return ( ( NULL == *cond ) ? thrd_error : thrd_success );
}

void cnd_destroy( cnd_t *cond )
{
    CloseHandle( *cond );
}

int cnd_signal( cnd_t *cond )
{
    return ( 0 != SetEvent( *cond ) ) ? thrd_success : thrd_error;
}

int cnd_wait( cnd_t *cond, mtx_t *mutex )
{
    mtx_unlock( mutex );
    WaitForSingleObject( *cond, 0 );
    mtx_lock( mutex );
    return 0;
}
