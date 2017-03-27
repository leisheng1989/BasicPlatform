#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

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


os_rwlock_t *os_rwlock_create(void)
{
    int ret;
    os_rwlock_t *rwlock;

    rwlock = malloc(sizeof(*rwlock));
    if (rwlock == NULL) {
        return NULL;
    }

    rwlock->lock = malloc(sizeof(pthread_rwlock_t));
    if (rwlock->lock == NULL) {
        free(rwlock);
        return NULL;
    }

    ret = pthread_rwlock_init((pthread_rwlock_t *)rwlock->lock, NULL);
    if (ret != 0) {
        free(rwlock->lock);
        free(rwlock);
        return NULL;
    }

    return rwlock;
}


int os_rwlock_rdlock(os_rwlock_t *rwlock)
{
    ASSERT_RETURN(rwlock != NULL, -EINVAL);

    return pthread_rwlock_rdlock(rwlock->lock);
}

int os_rwlock_wrlock(os_rwlock_t *rwlock)
{
    ASSERT_RETURN(rwlock != NULL, -EINVAL);

    return pthread_rwlock_wrlock(rwlock->lock);
}


int os_rwlock_unlock(os_rwlock_t *rwlock)
{
    ASSERT_RETURN(rwlock != NULL, -EINVAL);

    return pthread_rwlock_unlock(rwlock->lock);
}


void os_rwlock_destroy(os_rwlock_t *rwlock)
{
    if ((rwlock) && (rwlock->lock)) {
        pthread_rwlock_destroy(rwlock->lock);
        free(rwlock->lock);
        free(rwlock);
    }
}


/* 
 * semaphore 
 */
os_sem_t *os_sem_create(void)
{
    int ret;
    os_sem_t *sem;

    sem = malloc(sizeof(*sem));
    if (sem == NULL) {
        return NULL;
    }

    sem->sem = malloc(sizeof(sem_t));
    if (sem->sem == NULL) {
        free(sem->sem);
        return NULL;
    }

    ret = sem_init(sem->sem, 0, 0);
    if (ret != 0) {
        free(sem->sem);
        free(sem);
        return NULL;
    }

    return sem;
}


int os_sem_post(os_sem_t *sem)
{    
    ASSERT_RETURN(sem != NULL, -EINVAL);

    return sem_post(sem->sem);
}


int os_sem_wait(os_sem_t *sem)
{
    ASSERT_RETURN(sem != NULL, -EINVAL);

    return sem_wait(sem->sem);
}


int os_sem_trywait(os_sem_t *sem)
{
    ASSERT_RETURN(sem != NULL, -EINVAL);

    return sem_trywait(sem->sem);
}


void os_sem_destroy(os_sem_t *sem)
{
    ASSERT(sem != NULL);
    ASSERT(sem->sem != NULL);
    
    if (sem_destroy(sem->sem) == 0) {
        free(sem->sem);
        free(sem);
    }
}

