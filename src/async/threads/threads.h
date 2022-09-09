#if !defined( __THREADS_H__ )
#define __THREADS_H__

#if defined( _MSC_VER )
#include <windows.h>
typedef HANDLE thrd_t;
typedef HANDLE cnd_t;
#else
#include <pthread.h>
typedef pthread_t thrd_t;
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


// ----------------------------------------------------------------------- //
// ------------------------------ Thread API ----------------------------- //
// ----------------------------------------------------------------------- //

typedef int ( *thrd_start_t )( void * );

/// @brief Create a new Thread
///
/// @param[out] tid
/// @param[in] func
/// @param[in] arg
/// @return
int thrd_create( thrd_t *tid, thrd_start_t func, void *arg );

int thrd_join( thrd_t tid, int *res );

thrd_t thrd_current( void );

// ----------------------------------------------------------------------- //
// ------------------------------ Mutex API ------------------------------ //
// ----------------------------------------------------------------------- //

enum
{
    /// 
    /// @brief plain mutex. 
    /// 
    /// @note On Windows plain and recursive mutexes are the same.
    /// 
    mtx_plain,

    /// 
    /// @brief recursive mutex
    /// 
    /// The mutex won't block on subsequent lock calls from the same thread.
    /// 
    mtx_recursive = 1,

    /// 
    /// @brief timed mutex
    /// 
    /// Allows the use of mtx_timedlock()
    ///  
    mtx_timed     = 2
};

typedef struct mtx *mtx_t;

/// @brief 
/// @param mutex 
/// @param type 
/// @return 
int mtx_init( mtx_t *mutex, int type );

/// @brief 
/// @param mutex 
void mtx_destroy( mtx_t *mutex );

int mtx_lock( mtx_t *mutex );

int mtx_trylock( mtx_t *mutex );

int mtx_timedlock( mtx_t *mutex, const struct timespec *time_point );

int mtx_unlock( mtx_t *mutex );

// ----------------------------------------------------------------------- //
// ------------------------ Condition Variable API ----------------------- //
// ----------------------------------------------------------------------- //

int cnd_init( cnd_t *cond );
void cnd_destroy( cnd_t *cond );
int cnd_signal( cnd_t *cond );
int cnd_broadcast( cnd_t *cond );
int cnd_wait( cnd_t *cond, mtx_t *mutex );

#endif   // !defined( __THREADS_H__ )
