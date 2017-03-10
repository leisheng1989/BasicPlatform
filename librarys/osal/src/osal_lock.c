#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "osal_lock.h"


osal_thread_mutex_t *osal_thread_mutex_create(void)
{
    int ret;
    osal_thread_mutex_t *lock;

    lock = malloc(sizeof(*lock));
    if (lock == NULL) {
        return NULL;
    }

    lock->mutex = malloc(sizeof(pthread_mutex_t));
    if (lock->mutex == NULL) {
        free(lock);
        return NULL;
    }

    ret = pthread_mutex_init((pthread_mutex_t *)lock->mutex, NULL);
    if (ret != 0) {
        free(lock->mutex);
        free(lock);
        return NULL;
    }

    return lock;
}


int osal_thread_mutex_lock(osal_thread_mutex_t *lock)
{
    int ret;
    
    if ((lock == NULL) || (lock->mutex == NULL)) {
        return -1;
    }

    return pthread_mutex_lock(lock->mutex);
}


int osal_thread_mutex_unlock(osal_thread_mutex_t *lock)
{
    if ((lock == NULL) || (lock->mutex == NULL)) {
        return -1;
    }

    return pthread_mutex_unlock(lock->mutex);
}

void osal_thread_mutex_destroy(osal_thread_mutex_t *lock)
{
    if ((lock) && (lock->mutex)) {
        pthread_mutex_destroy(lock->mutex);
        free(lock->mutex);
        free(lock);
    }
}

