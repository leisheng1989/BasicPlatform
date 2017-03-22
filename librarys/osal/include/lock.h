#ifndef __OS_LOCK_H_
#define __OS_LOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct os_mutex{
    void *mutex;
}os_mutex_t;


typedef struct os_thread_rwlock{
    void *lock;
}os_thread_rwlock_t;


os_mutex_t *os_mutex_create(void);
int os_mutex_lock(os_mutex_t *mutex);
int os_mutex_unlock(os_mutex_t *mutex);
void os_mutex_destroy(os_mutex_t *mutex);

os_thread_rwlock_t *os_thread_rwlock_create(void);
int os_thread_rwlock_rdlock(os_thread_rwlock_t *rwlock);
int os_thread_rwlock_wrlock(os_thread_rwlock_t *rwlock);
int os_thread_rwlock_unlock(os_thread_rwlock_t *rwlock);
void os_thread_rwlock_destroy(os_thread_rwlock_t *rwlock);

#ifdef __cplusplus
}
#endif


#endif /* __OS_LOCK_H_ */

