#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#if defined(__GNUC__)

#include <unistd.h>
#include <time.h>

/*
 * here are several simple functions that do the job.
 * First of all, there are twelve (yes, twelve-12)
 * functions that do atomic add, substitution, 
 * and logical atomic or, and, xor and nand. 
 * There are two functions for each operation.
 * One that returns value of the variable before
 * changing it and another that returns value of the variable after changing it.
 */

/*
 * type in each of the expressions can be one of the following:
 * char
 * unsigned char
 * short
 * unsigned short
 * int
 * unsigned int
 * long
 * unsigned long
 * long long
 * unsigned long long
 */

/*
 * type tmp = *v ; *v += a ; return tmp;
 */
#define ATOM_FETCH_ADD(v, a) __sync_fetch_and_add(v, (a))

/*
 * type tmp = *v; *v++; return tmp;
 */
#define ATOM_FETCH_INC(v) __sync_fetch_and_add(v, 1)

 /*
  * type tmp = *v ; *v -= a ; return tmp;
  */
#define ATOM_FETCH_SUB(v, a) __sync_fetch_and_sub(v, (a))

/*
 * type tmp = *v; *v--; return tmp;
 */
#define ATOM_FETCH_DEC(v) __sync_fetch_and_sub(v, 1)

 /*
  * type tmp = *v ; *v |= a ; return tmp;
  */
#define ATOM_FETCH_OR(v, a) __sync_fetch_and_or(v, (a))

 /*
  * type tmp = *v ; *v &= a ; return tmp;
  */
#define ATOM_FETCH_AND(v, a) __sync_fetch_and_and(v, (a))

 /*
  * type tmp = *v ; *v ^= a ; return tmp;
  */
#define ATOM_FETCH_XOR(v, a) __sync_fetch_and_xor(v, (a))

 /*
  * type tmp = *v ; *v = (~)tmp & a ; return tmp;
  */
#define ATOM_FETCH_NAND(v, a) __sync_fetch_and_nand(v, (a))



/*
 * *v += a ; return *v;
 */
#define ATOM_ADD_FETCH(v, a) __sync_add_and_fetch(v, (a))

/*
 * type tmp = *v; *v++; return *v;
 */
#define ATOM_INC_FETCH(v) __sync_add_and_fetch(v, 1)

 /*
  * type tmp = *v; *v--; return *v;
  */
#define ATOM_SUB_FETCH(v, a) __sync_sub_and_fetch(v, (a))

/*
 * *v--;
 */
#define ATOM_DEC_FETCH(v) __sync_sub_and_fetch(v, 1)

 /*
  * *v |= a ; return *v;
  */
#define ATOM_OR_FETCH(v, a) __sync_or_and_fetch(v, (a))

 /*
  * *v &= a ; return *v;
  */
#define ATOM_AND_FETCH(v, a) __sync_and_and_fetch(v, (a))

 /*
  * *v ^= a ; return *v;
  */
#define ATOM_XOR_FETCH(v, a) __sync_xor_and_fetch(v, (a))

 /*
  * tmp = *v; *v = (~)tmp & a ; return *v;
  */
#define ATOM_NAND_FETCH(v, a) __sync_nand_and_fetch(v, (a))


/*
 * *v = a; return *v;
 */
#define ATOM_SET(v, a) __sync_lock_test_and_set(v, (a))

/*
 * *v = 0;
 */
#define ATOM_RESET(v) __sync_lock_release(v)

/*
 * bool b = *v == c; b ? *v=a : ; return b;
 */
#define ATOM_BOOL_CMP_SWAP(v, c, a) __sync_bool_compare_and_swap(v, (c), (a))

/*
 * type tmp = *v ; *v == c ? *v = a : ;  return tmp;
 */
#define ATOM_VAL_CMP_SWAP(v, c, a) __sync_val_compare_and_swap(v, (c), (a))

/*
 * This builtin issues a full memory barrier
 */
#define ATOM_SYNC()    __sync_synchronize()


typedef struct atom_spinlock {
    int lock;
}atom_spinlock_t;


static inline void atom_spinlock_init(atom_spinlock_t *lock)
{
    lock->lock = 0;
}

static inline void atom_spinlock_lock(atom_spinlock_t *lock)
{
	struct timespec ts;

	ts.tv_sec = 0;
	ts.tv_nsec = 500;

    for (;;) {  
        // isuued a full memory barrier. This typically means that operations issued   
        // prior to the barrier are guaranteed to be performed before operations issued after the barrier.  
        while(lock->lock) {  
            nanosleep(&ts, NULL);
        }
        
        if (__sync_bool_compare_and_swap(&lock->lock, 0, 1)) {
            break;
        }
    } 
}


static inline void atom_spinlock_unlock(atom_spinlock_t *lock)
{
     __sync_lock_release(&lock->lock);
}


#endif /* __GNUC__ */

#endif /* __ATOMIC_H__ */

