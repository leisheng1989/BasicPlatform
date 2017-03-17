/*
 * Sample kfifo byte stream implementation
 *
 * Copyright (C) 2010 Stefani Seibold <stefani@seibold.net>
 *
 * Released under the GPL version 2 only.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "SysLogPublic.h"
#include "osal.h"


/*
 * This module shows how to create a byte stream fifo.
 */

/* fifo size in elements (bytes) */
#define FIFO_SIZE	32

/*
 * define DYNAMIC in this example for a dynamically allocated fifo.
 *
 * Otherwise the fifo storage will be a part of the fifo structure.
 */
#if 1
#define DYNAMIC
#endif

#ifdef DYNAMIC
static struct kfifo test;
#else
static DECLARE_KFIFO(test, unsigned char, FIFO_SIZE);
#endif

static const unsigned char expected_result[FIFO_SIZE] = {
	 3,  4,  5,  6,  7,  8,  9,  0,
	 1, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42,
};

static int testfunc(void)
{
	unsigned char	buf[6];
	unsigned char	i, j;
	unsigned int	ret;
	struct { unsigned char buf[6]; } hello = { "hello" };

	SysDebugTrace("byte stream fifo test start");

	/* put string into the fifo */
	kfifo_in(&test, &hello, 5);

	/* put values into the fifo */
	for (i = 0; i != 10; i++)
		kfifo_put(&test, &i);

	/* show the number of used elements */
	SysDebugTrace("fifo len: %u", kfifo_len(&test));

	/* get max of 5 bytes from the fifo */
	i = kfifo_out(&test, buf, 5);
	SysDebugTrace("buf: %.*s", i, buf);

	/* get max of 2 elements from the fifo */
	ret = kfifo_out(&test, buf, 2);
	SysDebugTrace("ret: %d", ret);
	/* and put it back to the end of the fifo */
	ret = kfifo_in(&test, buf, ret);
	SysDebugTrace("ret: %d", ret);

	/* skip first element of the fifo */
	SysDebugTrace("skip 1st element");
	kfifo_skip(&test);

	/* put values into the fifo until is full */
	for (i = 20; kfifo_put(&test, &i); i++)
		;

	SysDebugTrace("queue len: %u", kfifo_len(&test));

	/* show the first value without removing from the fifo */
	if (kfifo_peek(&test, &i))
		SysDebugTrace("%d", i);

	/* check the correctness of all values in the fifo */
	j = 0;
	while (kfifo_get(&test, &i)) {
		SysDebugTrace("item = %d", i);
		if (i != expected_result[j++]) {
			SysErrorTrace("value mismatch: test failed");
			return -EIO;
		}
	}
	if (j != ARRAY_SIZE(expected_result)) {
		SysErrorTrace("size mismatch: test failed");
		return -EIO;
	}
	SysErrorTrace("test passed");

	return 0;
}


int kfifo_bytes_test(void)
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

	return 0;
}

