#ifndef __OSAL_THREAD_H__
#define __OSAL_THREAD_H__

#define OSAL_SCHED_OTHER     0
#define OSAL_SCHED_FIFO      1
#define OSAL_SCHED_RR        2

/*
 * os_thread_create() creates a new thread
 * @policy: OSAL_SCHED_xx
 * @priority: (0~99)
 * @start: 
 * @arg :
 * Returns 0 on success, or a positive error number on error
 */

int osal_thread_create(int policy,
                        int priority, 
                        size_t stack_size,
                        void *(*start)(void *),
                        void *arg);
/*
 * a thread can get its own ID
 * Returns the thread ID of the calling thread
 */
unsigned long int osal_thread_self(void);
void osal_thread_msleep(int ms);
void osal_thread_sleep(int s);

#endif /* __OSAL_THREAD_H__ */

