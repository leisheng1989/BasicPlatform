#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "SysLogPublic.h"
#include "osal.h"

/*
 * This module shows how to create a variable sized record fifo.
 */

/* fifo size in elements (bytes) */
#define FIFO_SIZE	128

/*
 * define DYNAMIC in this example for a dynamically allocated fifo.
 *
 * Otherwise the fifo storage will be a part of the fifo structure.
 */
#if 1
#define DYNAMIC
#endif

/*
 * struct kfifo_rec_ptr_1 and  STRUCT_KFIFO_REC_1 can handle records of a
 * length between 0 and 255 bytes.
 *
 * struct kfifo_rec_ptr_2 and  STRUCT_KFIFO_REC_2 can handle records of a
 * length between 0 and 65535 bytes.
 */

#ifdef DYNAMIC
struct kfifo_rec_ptr_2 test;

#else
typedef STRUCT_KFIFO_REC_2(FIFO_SIZE) mytest;

static mytest test;
#endif

static const char *expected_result[] = {
	"a",
	"bb",
	"ccc",
	"dddd",
	"eeeee",
	"ffffff",
	"ggggggg",
	"hhhhhhhh",
	"iiiiiiiii",
	"jjjjjjjjjj",
};

static int testfunc(void)
{
	char		buf[100];
	unsigned int	i;
	unsigned int	ret;
	struct { unsigned char buf[6]; } hello = { "hello" };

	SysDebugTrace("record fifo test start, fifo len: %u avail: %u",
        kfifo_len(&test), kfifo_avail(&test));

	kfifo_in(&test, &hello, sizeof(hello));

	/* show the size of the next record in the fifo */
	SysDebugTrace("fifo peek len: %u", kfifo_peek_len(&test));

	/* put in variable length data */
	for (i = 0; i < 10; i++) {
		memset(buf, 'a' + i, i + 1);
		kfifo_in(&test, buf, i + 1);
	}

	/* skip first element of the fifo */
	SysDebugTrace("before skip 1st element, fifo len: %u avail: %u",
	    kfifo_len(&test), kfifo_avail(&test));
	kfifo_skip(&test);
	SysDebugTrace("after  skip 1st element, fifo len: %u avail: %u",
        kfifo_len(&test), kfifo_avail(&test));

	/* show the first record without removing from the fifo */
	ret = kfifo_out_peek(&test, buf, sizeof(buf));
	if (ret)
		SysDebugTrace("%.*s", ret, buf);

	/* check the correctness of all values in the fifo */
	i = 0;
	while (!kfifo_is_empty(&test)) {
		ret = kfifo_out(&test, buf, sizeof(buf));
		buf[ret] = '\0';
		SysDebugTrace("item = %.*s", ret, buf);
		if (strcmp(buf, expected_result[i++])) {
			SysErrorTrace("value mismatch: test failed");
			return -EIO;
		}
	}
	if (i != ARRAY_SIZE(expected_result)) {
		SysErrorTrace("size mismatch: test failed");
		return -EIO;
	}
	SysDebugTrace("test passed");

	return 0;
}

int kfifo_record_test(void)
{
     
#ifdef DYNAMIC  
    int ret;

    ret = kfifo_alloc(&test, FIFO_SIZE);
    if (ret) {
        SysErrorTrace("error kfifo_alloc");
        return ret;
    }
#else
    INIT_KFIFO(test);
#endif
    if (testfunc() < 0) {
#ifdef DYNAMIC
        kfifo_free(&test);
#endif
        return -EIO;
    }

    kfifo_free(&test);

    return 0;
}

