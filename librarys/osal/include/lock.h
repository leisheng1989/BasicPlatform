#ifndef __OS_LOCK_H_
#define __OS_LOCK_H_

typedef struct os_thread_mutex{
    void *mutex;
}os_thread_mutex_t;


typedef struct os_thread_rwlock{
    void *lock;
}os_thread_rwlock_t;

typedef struct os_thread_spin{
    void *lock;
}os_thread_spin_t;


os_thread_mutex_t *os_thread_mutex_create(void);
int os_thread_mutex_lock(os_thread_mutex_t *lock);
int os_thread_mutex_unlock(os_thread_mutex_t *lock);
void os_thread_mutex_destroy(os_thread_mutex_t *lock);

os_thread_rwlock_t *os_thread_rwlock_create(void);
int os_thread_rwlock_rdlock(os_thread_rwlock_t *rwlock);
int os_thread_rwlock_wrlock(os_thread_rwlock_t *rwlock);
int os_thread_rwlock_unlock(os_thread_rwlock_t *rwlock);
void os_thread_rwlock_destroy(os_thread_rwlock_t *rwlock);

os_thread_spin_t *os_thread_spin_create(void);
int os_thread_spin_lock(os_thread_spin_t *spin);
int os_thread_spin_unlock(os_thread_spin_t *spin);
void os_thread_spin_destroy(os_thread_spin_t *spin);

#endif /* __OS_LOCK_H_ */

