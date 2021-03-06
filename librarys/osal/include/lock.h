#ifndef __OS_LOCK_H_
#define __OS_LOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct os_mutex{
    void *mutex;
}os_mutex_t;


typedef struct os_rwlock{
    void *lock;
}os_rwlock_t;

typedef struct os_sem{
    void *sem;
}os_sem_t;


os_mutex_t *os_mutex_create(void);
int os_mutex_lock(os_mutex_t *mutex);
int os_mutex_unlock(os_mutex_t *mutex);
void os_mutex_destroy(os_mutex_t *mutex);

os_rwlock_t *os_rwlock_create(void);
int os_rwlock_rdlock(os_rwlock_t *rwlock);
int os_rwlock_wrlock(os_rwlock_t *rwlock);
int os_rwlock_unlock(os_rwlock_t *rwlock);
void os_rwlock_destroy(os_rwlock_t *rwlock);

os_sem_t *os_sem_create(void);
int os_sem_post(os_sem_t *sem);
int os_sem_wait(os_sem_t *sem);
int os_sem_trywait(os_sem_t *sem);
void os_sem_destroy(os_sem_t *sem);

#ifdef __cplusplus
}
#endif


#endif /* __OS_LOCK_H_ */

