#ifndef __OSAL_LOCK_H_
#define __OSAL_LOCK_H_

typedef struct osal_thread_mutex{
    void *mutex;
}osal_thread_mutex_t;


typedef struct osal_thread_rwlock{
    void *lock;
}osal_thread_rwlock_t;

typedef struct osal_thread_spin{
    void *lock;
}osal_thread_spin_t;


osal_thread_mutex_t *osal_thread_mutex_create(void);
int osal_thread_mutex_lock(osal_thread_mutex_t *lock);
int osal_thread_mutex_unlock(osal_thread_mutex_t *lock);
void osal_thread_mutex_destroy(osal_thread_mutex_t *lock);

osal_thread_rwlock_t *osal_thread_rwlock_create(void);
int osal_thread_rwlock_rdlock(osal_thread_rwlock_t *rwlock);
int osal_thread_rwlock_wrlock(osal_thread_rwlock_t *rwlock);
int osal_thread_rwlock_unlock(osal_thread_rwlock_t *rwlock);
void osal_thread_rwlock_destroy(osal_thread_rwlock_t *rwlock);

osal_thread_spin_t *osal_thread_spin_create(void);
int osal_thread_spin_lock(osal_thread_spin_t *spin);
int osal_thread_spin_unlock(osal_thread_spin_t *spin);
void osal_thread_spin_destroy(osal_thread_spin_t *spin);

#endif /* __OSAL_LOCK_H_ */

