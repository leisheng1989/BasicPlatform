#ifndef __OSAL_LOCK_H_
#define __OSAL_LOCK_H_

typedef struct osal_thread_mutex{
    void *mutex;
}osal_thread_mutex_t;


osal_thread_mutex_t *osal_thread_mutex_create(void);
int osal_thread_mutex_lock(osal_thread_mutex_t *lock);
int osal_thread_mutex_unlock(osal_thread_mutex_t *lock);
void osal_thread_mutex_destroy(osal_thread_mutex_t *lock);

#endif /* __OSAL_LOCK_H_ */

