#include "semaphore.h"

int sem_init( sem_t *sem, int pshare, unsigned int value )
{
    *sem = CreateSemaphore( NULL, (LONG)value, LONG_MAX, NULL );
    return ( ( NULL != *sem ) ? 0 : -1 );
}

void sem_destroy( sem_t *sem )
{
    CloseHandle( *sem );
}

int sem_post( sem_t *sem )
{
    return ( FALSE == ReleaseSemaphore( *sem, 1, NULL ) );
}

int sem_wait( sem_t *sem )
{
    return ( ( WAIT_OBJECT_0 == WaitForSingleObjectEx( *sem, INFINITE, FALSE ) ) ? 0 : -1 );
}
