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


osal_thread_rwlock_t *osal_thread_rwlock_create(void)
{
    int ret;
    osal_thread_rwlock_t *rwlock;

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


int osal_thread_rwlock_rdlock(osal_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_rdlock(rwlock->lock);
}

int osal_thread_rwlock_wrlock(osal_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_wrlock(rwlock->lock);
}


int osal_thread_rwlock_unlock(osal_thread_rwlock_t *rwlock)
{
    if ((rwlock == NULL) || (rwlock->lock == NULL)) {
        return -1;
    }

    return pthread_rwlock_unlock(rwlock->lock);
}


void osal_thread_rwlock_destroy(osal_thread_rwlock_t *rwlock)
{
    if ((rwlock) && (rwlock->lock)) {
        pthread_mutex_destroy(rwlock->lock);
        free(rwlock->lock);
        free(rwlock);
    }
}


/*
 * spin lock
 */
osal_thread_spin_t *osal_thread_spin_create(void)
{
    int ret;
    osal_thread_spin_t *spin;

    spin = malloc(sizeof(*spin));
    if (spin == NULL) {
        return NULL;
    }

    spin->lock = malloc(sizeof(pthread_spinlock_t));
    if (spin->lock == NULL) {
        free(spin);
        return NULL;
    }

    ret = pthread_spin_init((pthread_spinlock_t *)spin->lock, 0);
    if (ret != 0) {
        free(spin->lock);
        free(spin);
        return NULL;
    }

    return spin;
}

int osal_thread_spin_lock(osal_thread_spin_t *spin)
{    
    if ((spin == NULL) || (spin->lock == NULL)) {
        return -1;
    }

    return pthread_spin_lock(spin->lock);
}

int osal_thread_spin_unlock(osal_thread_spin_t *spin)
{    
    if ((spin == NULL) || (spin->lock == NULL)) {
        return -1;
    }

    return pthread_spin_unlock(spin->lock);
}

void osal_thread_spin_destroy(osal_thread_spin_t *spin)
{
    if ((spin) && (spin->lock)) {
        pthread_spin_destroy(spin->lock);
        free(spin->lock);
        free(spin);
    }
}