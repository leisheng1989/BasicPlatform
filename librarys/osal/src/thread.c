#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "thread.h"

int os_thread_create(int policy,
                    int priority, 
                    size_t  stack_size,
                    void *(*start)(void *),
                    void *arg)
{
    int ret;
    pthread_t tid;
    pthread_attr_t attr;
    struct sched_param params;

    if (start == NULL) {
        return -1;
    }

    switch(policy) {
    case OS_SCHED_FIFO:
        policy = SCHED_FIFO;
        break;

    case OS_SCHED_RR:
        policy = SCHED_RR;
        break;

    case OS_SCHED_OTHER:
    default:
        policy = SCHED_OTHER;
        break;
    }

    /* Initialize thread creation attributes */
    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        return -2;
    }

    if (stack_size > 0) {
        ret = pthread_attr_setstacksize(&attr, stack_size);
        if (ret != 0) {
            ret= -3;
            goto out;
        }
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (0 != ret){
        ret = -4;
        goto out;
    }

    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (0 != ret)
    {
        ret = -5;
        goto out;
    }

    ret = pthread_attr_setschedpolicy(&attr, policy);
    if (0 != ret)
    {
        ret = -6;
        goto out;
    }  

    params.sched_priority = priority;
    ret = pthread_attr_setschedparam(&attr, &params);
    if (0 != ret)
    {
        ret = -7;
        goto out;
    } 

    ret = pthread_create(&tid, &attr, start, arg);
    if (0 != ret)
    {
        ret = -8;
        goto out;
    }

out:
    pthread_attr_destroy(&attr);
    return ret;

}

unsigned long int os_thread_self(void)
{
    return pthread_self();
}


void os_thread_msleep(int ms) 
{
	struct timespec ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;

	nanosleep(&ts, NULL);
}

void os_thread_sleep(int s)
{
	sleep(s);
}

