#include "threads.h"

int thrd_create( thrd_t *tid, thrd_start_t func, void *arg )
{
    int result = thrd_success;
    if( 0 != pthread_create( tid, NULL, (void *(*)(void *))func, arg ) )
    {
        result = thrd_error;
    }
    return result;
}

thrd_t thrd_current( void )
{
    return pthread_self();
}
