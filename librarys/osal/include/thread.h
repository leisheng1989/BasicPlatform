#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#define OS_SCHED_OTHER     0
#define OS_SCHED_FIFO      1
#define OS_SCHED_RR        2

/*
 * os_thread_create() creates a new thread
 * @policy: OSAL_SCHED_xx
 * @priority: (0~99)
 * @start: 
 * @arg :
 * Returns 0 on success, or a positive error number on error
 */

int os_thread_create(int policy,
                        int priority, 
                        size_t stack_size,
                        void *(*start)(void *),
                        void *arg);
/*
 * a thread can get its own ID
 * Returns the thread ID of the calling thread
 */
unsigned long int os_thread_self(void);
void os_thread_msleep(int ms);
void os_thread_sleep(int s);

#endif /* __OS_THREAD_H__ */

