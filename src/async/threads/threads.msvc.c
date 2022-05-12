#include "threads.h"
#include <process.h>

int thrd_create( thrd_t *tid, thrd_start_t func, void *arg )
{
    ( *tid ) = (HANDLE)_beginthreadex( NULL, 0U, (_beginthreadex_proc_type)func, arg, 0U, NULL );
    return ( ( NULL == *tid ) ? thrd_error : thrd_success );
}

int thrd_join( thrd_t tid, int *res )
{
    int retval = thrd_error;

    DWORD thrd_result;
    if( WAIT_OBJECT_0 == WaitForSingleObject( tid, INFINITE ) && GetExitCodeThread( tid, &thrd_result ) )
    {
        if( NULL != res )
        {
            *res = (int)thrd_result;
        }
        retval = thrd_success;
    }
    CloseHandle( tid );
    return retval;
}

thrd_t thrd_current( void )
{
    return GetCurrentThread();
}

struct mtx_t
{
    union
    {
        HANDLE mtx;
        CRITICAL_SECTION cs;
    };
    int type;
};

int mtx_init( mtx_t *mutex, const int type )
{
    int retval = thrd_error;
    if( NULL != mutex )
    {
        mutex[ 0 ] = (mtx_t)malloc( sizeof( struct mtx_t ) );

        if( NULL != *mutex )
        {
            // critical section lack the ability for a timed wait
            // on the other hand they have a lot less overhead and therefor
            // are much faster.
            if( type & mtx_timed )
            {
                mutex[ 0 ]->mtx = CreateMutex( NULL, FALSE, NULL );
                if( NULL != mutex[ 0 ]->mtx )
                {
                    retval = thrd_success;
                }
            }
            else
            {
                InitializeCriticalSection( &( mutex[ 0 ]->cs ) );
                retval = thrd_success;
            }
            mutex[ 0 ]->type = type;
        }
    }
    return retval;
}

void mtx_destroy( mtx_t *mutex )
{
    if( NULL != mutex )
    {
        if( mutex[ 0 ]->type & mtx_timed )
        {
            (void)CloseHandle( mutex[ 0 ]->mtx );
        }
        else
        {
            DeleteCriticalSection( &mutex[ 0 ]->cs );
        }
        free( mutex );
    }
}

int mtx_lock( mtx_t *mutex )
{
    int retval = thrd_error;
    if( NULL != mutex)
    {
        if( mutex[0]->type & mtx_timed )
        {
            switch( WaitForSingleObject( mutex[0]->mtx, INFINITE ) )
            {
                case WAIT_OBJECT_0:
                    retval = thrd_success;
                    break;
                default:
                    retval = thrd_error;
                    break;
            }
        }
        else
        {
            EnterCriticalSection( &mutex[ 0 ]->cs );
            retval = thrd_success;
        }
    }
    return retval;
}

int mtx_trylock( mtx_t *mutex )
{
    int retval = thrd_error;
    if( NULL != mutex )
    {
        if( mutex[ 0 ]->type & mtx_timed )
        {
            switch( WaitForSingleObject( *mutex, 0U ) )
            {
                case WAIT_OBJECT_0:
                    retval = thrd_success;
                    break;
                case WAIT_TIMEOUT:
                    retval = thrd_busy;
                    break;
                default:
                    retval = thrd_error;
            }
        }
        else
        {
            if( TryEnterCriticalSection( &mutex[0]->cs ) )
            {
                retval = thrd_success;
            }
            else
            {
                retval = thrd_busy;
            }
        }
    }
    return retval;
}

int mtx_timedlock( mtx_t *mutex, const struct timespec *time_point )
{
    int retval = thrd_error;

    if( NULL != mutex && mutex[ 0 ]->type & mtx_timed )
    {
        DWORD wait_time = 0U;
        if( NULL != time_point )
        {
            struct timespec now;
            (void)timespec_get( &now, TIME_UTC );

            const DWORD nowms = now.tv_sec * 1000U + now.tv_nsec / 1000000U;
            const DWORD thenms = time_point->tv_sec * 1000U + time_point->tv_nsec / 1000000U;

            wait_time = thenms - nowms;
        }

        switch( WaitForSingleObject( *mutex, wait_time ) )
        {
            case WAIT_OBJECT_0:
                retval = thrd_success;
            case WAIT_TIMEOUT:
                retval = thrd_timedout;
            default:
                break;
        }
    }

    return retval;
}

int mtx_unlock( mtx_t *mutex )
{
    int retval = thrd_error;
    if( NULL != mutex )
    {
        if( mutex[ 0 ]->type & mtx_timed && ReleaseMutex( mutex[ 0 ]->mtx ) )
        {
            retval = thrd_success;
        }
        else
        {
            LeaveCriticalSection( &mutex[ 0 ]->cs );
            retval = thrd_success;
        }
    }
    return retval;

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
