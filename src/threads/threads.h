#if !defined( __THREADS_H__ )
#define __THREADS_H__

#if defined( _MSC_VER )
#include <windows.h>
typedef HANDLE thrd_t;
typedef HANDLE mtx_t;
typedef HANDLE cnd_t;
#else
#include <pthread.h>
typedef pthread_t thrd_t;
typedef pthread_mutex_t mtx_t;
typedef pthread_cond_t cnd_t;
#endif   //_MSC_VER

#include <time.h>

enum
{
    thrd_success,
    thrd_nomem,
    thrd_timedout,
    thrd_busy,
    thrd_error,
};

typedef int ( *thrd_start_t )( void * );

int thrd_create( thrd_t *tid, thrd_start_t func, void *arg );

int thrd_join( thrd_t tid, int *res );

thrd_t thrd_current( void );

enum
{
    mtx_plain,
    mtx_recursive = 1,
    mtx_timed     = 2
};

int mtx_init( mtx_t *mutex, int type );
void mtx_destroy( mtx_t *mutex );

int mtx_lock( mtx_t *mutex );

int mtx_trylock( mtx_t *mutex );

int mtx_timedlock( mtx_t *mutex, const struct timespec *time_point );

int mtx_unlock( mtx_t *mutex );

int cnd_init( cnd_t *cond );
void cnd_destroy( cnd_t *cond );
int cnd_signal( cnd_t *cond );
int cnd_broadcast(cnd_t *cond);
int cnd_wait( cnd_t *cond, mtx_t *mutex );

#endif   // !defined( __THREADS_H__ )
