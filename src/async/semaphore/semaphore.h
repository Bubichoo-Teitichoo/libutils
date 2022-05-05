#if !defined( __SEMAPHORE_H__ )
#define __SEMAPHORE_H__

#include <Windows.h>

typedef HANDLE sem_t;

int sem_init( sem_t *sem, int pshare, unsigned int value );
void sem_destroy( sem_t *sem );

int sem_post( sem_t *sem );
int sem_wait( sem_t *sem );

#endif   // __SEMAPHORE_H__