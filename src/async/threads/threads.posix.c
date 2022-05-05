#include "threads.h"
#include <stdlib.h>

typedef struct
{
    thrd_start_t func;
    void *args;
    int result;
} thrd_data_t;

void *thrd_runner(void *args)
{
    thrd_data_t *data = (thrd_data_t *)args;
    data->result = data->func(data->args);
    return data;
}

int thrd_create(thrd_t *tid, thrd_start_t func, void *arg)
{
    thrd_data_t *data = malloc(sizeof(thrd_data_t));
    if (NULL != data)
    {
        data->func = func;
        data->args = arg;
        if (0 == pthread_create(tid, NULL, thrd_runner, data))
        {
            return thrd_success;
        }
    }
    return thrd_error;
}

int thrd_join(thrd_t tid, int *res)
{
    thrd_data_t *data;
    if (0 == pthread_join(tid, (void *)&data))
    {
        if (NULL != res)
        {
            *res = data->result;
        }
        return thrd_error;
    }
    return thrd_success;
}

thrd_t thrd_current(void)
{
    return pthread_self();
}

int mtx_init(mtx_t *mutex, int type)
{
    return ((0 == pthread_mutex_init(mutex, NULL)) ? thrd_success : thrd_error);
}

void mtx_destroy(mtx_t *mutex)
{
    pthread_mutex_destroy(mutex);
}

int mtx_lock(mtx_t *mutex)
{
    return ((0 == pthread_mutex_lock(mutex)) ? thrd_success : thrd_error);
}

int mtx_trylock(mtx_t *mutex)
{
    return ((0 == pthread_mutex_trylock(mutex)) ? thrd_success : thrd_error);
}

int mtx_timedlock(mtx_t *mutex, const struct timespec *time_point)
{
   return thrd_error;
}

int mtx_unlock(mtx_t *mutex)
{
    return ((0 == pthread_mutex_unlock(mutex)) ? thrd_success : thrd_error);
}

int cnd_init(cnd_t *cond)
{
    return ((0 == pthread_cond_init(cond, NULL)) ? thrd_success : thrd_error);
}

void cnd_destroy(cnd_t *cond)
{
    pthread_cond_destroy(cond);
}

int cnd_signal(cnd_t *cond)
{
    return (0 == pthread_cond_signal(cond)) ? thrd_success : thrd_error;
}

int cnd_broadcast(cnd_t *cond)
{
    return ((0 == pthread_cond_broadcast(cond)) ? thrd_success : thrd_error);
}

int cnd_wait(cnd_t *cond, mtx_t *mutex)
{
    return (0 == pthread_cond_wait(cond,mutex)) ? thrd_success : thrd_error;
}
