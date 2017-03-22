#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "errno-base.h"
#include "SysLogPublic.h"
#include "assert.h"
#include "lock.h"


os_mutex_t *os_mutex_create(void)
{
    int ret;
    os_mutex_t *lock;

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


int os_mutex_lock(os_mutex_t *mutex)
{    
    ASSERT_RETURN(mutex != NULL, -EINVAL);

    return pthread_mutex_lock(mutex->mutex);
}


int os_mutex_unlock(os_mutex_t *mutex)
{
    ASSERT_RETURN(mutex != NULL, -EINVAL);

    return pthread_mutex_unlock(mutex->mutex);
}

void os_mutex_destroy(os_mutex_t *mutex)
{
    ASSERT(mutex != NULL);
    ASSERT(mutex->mutex != NULL);
    
    if (pthread_mutex_destroy(mutex->mutex) == 0) {
        free(mutex->mutex);
        free(mutex);
    }
}


os_thread_rwlock_t *os_thread_rwlock_create(void)
{
    int ret;
    os_thread_rwlock_t *rwlock;

    rwlock = malloc(sizeof(*rwlock));
    if (rwlock == NULL) {
        return NULL;
    }

    rwlock->lock = malloc(sizeof(pthread_rwlock_t));
    if (rwlock->lock == NULL) {
        free(rwlock);
        return NULL;
    }

    ret = pthread_mutex_init((pthread_mutex_t *)rwlock->lock, NULL);
    if (ret != 0) {
        free(rwlock->lock);
        free(rwlock);
        return NULL;
    }

    return rwlock;
}


int os_thread_rwlock_rdlock(os_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_rdlock(rwlock->lock);
}

int os_thread_rwlock_wrlock(os_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_wrlock(rwlock->lock);
}


int os_thread_rwlock_unlock(os_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_unlock(rwlock->lock);
}


void os_thread_rwlock_destroy(os_thread_rwlock_t *rwlock)
{
    if ((rwlock) && (rwlock->lock)) {
        pthread_mutex_destroy(rwlock->lock);
        free(rwlock->lock);
        free(rwlock);
    }
}

