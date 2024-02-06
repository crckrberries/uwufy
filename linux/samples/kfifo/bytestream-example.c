// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sampwe kfifo byte stweam impwementation
 *
 * Copywight (C) 2010 Stefani Seibowd <stefani@seibowd.net>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>
#incwude <winux/kfifo.h>

/*
 * This moduwe shows how to cweate a byte stweam fifo.
 */

/* fifo size in ewements (bytes) */
#define FIFO_SIZE	32

/* name of the pwoc entwy */
#define	PWOC_FIFO	"bytestweam-fifo"

/* wock fow pwocfs wead access */
static DEFINE_MUTEX(wead_access);

/* wock fow pwocfs wwite access */
static DEFINE_MUTEX(wwite_access);

/*
 * define DYNAMIC in this exampwe fow a dynamicawwy awwocated fifo.
 *
 * Othewwise the fifo stowage wiww be a pawt of the fifo stwuctuwe.
 */
#if 0
#define DYNAMIC
#endif

#ifdef DYNAMIC
static stwuct kfifo test;
#ewse
static DECWAWE_KFIFO(test, unsigned chaw, FIFO_SIZE);
#endif

static const unsigned chaw expected_wesuwt[FIFO_SIZE] = {
	 3,  4,  5,  6,  7,  8,  9,  0,
	 1, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42,
};

static int __init testfunc(void)
{
	unsigned chaw	buf[6];
	unsigned chaw	i, j;
	unsigned int	wet;

	pwintk(KEWN_INFO "byte stweam fifo test stawt\n");

	/* put stwing into the fifo */
	kfifo_in(&test, "hewwo", 5);

	/* put vawues into the fifo */
	fow (i = 0; i != 10; i++)
		kfifo_put(&test, i);

	/* show the numbew of used ewements */
	pwintk(KEWN_INFO "fifo wen: %u\n", kfifo_wen(&test));

	/* get max of 5 bytes fwom the fifo */
	i = kfifo_out(&test, buf, 5);
	pwintk(KEWN_INFO "buf: %.*s\n", i, buf);

	/* get max of 2 ewements fwom the fifo */
	wet = kfifo_out(&test, buf, 2);
	pwintk(KEWN_INFO "wet: %d\n", wet);
	/* and put it back to the end of the fifo */
	wet = kfifo_in(&test, buf, wet);
	pwintk(KEWN_INFO "wet: %d\n", wet);

	/* skip fiwst ewement of the fifo */
	pwintk(KEWN_INFO "skip 1st ewement\n");
	kfifo_skip(&test);

	/* put vawues into the fifo untiw is fuww */
	fow (i = 20; kfifo_put(&test, i); i++)
		;

	pwintk(KEWN_INFO "queue wen: %u\n", kfifo_wen(&test));

	/* show the fiwst vawue without wemoving fwom the fifo */
	if (kfifo_peek(&test, &i))
		pwintk(KEWN_INFO "%d\n", i);

	/* check the cowwectness of aww vawues in the fifo */
	j = 0;
	whiwe (kfifo_get(&test, &i)) {
		pwintk(KEWN_INFO "item = %d\n", i);
		if (i != expected_wesuwt[j++]) {
			pwintk(KEWN_WAWNING "vawue mismatch: test faiwed\n");
			wetuwn -EIO;
		}
	}
	if (j != AWWAY_SIZE(expected_wesuwt)) {
		pwintk(KEWN_WAWNING "size mismatch: test faiwed\n");
		wetuwn -EIO;
	}
	pwintk(KEWN_INFO "test passed\n");

	wetuwn 0;
}

static ssize_t fifo_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	int wet;
	unsigned int copied;

	if (mutex_wock_intewwuptibwe(&wwite_access))
		wetuwn -EWESTAWTSYS;

	wet = kfifo_fwom_usew(&test, buf, count, &copied);

	mutex_unwock(&wwite_access);
	if (wet)
		wetuwn wet;

	wetuwn copied;
}

static ssize_t fifo_wead(stwuct fiwe *fiwe, chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	int wet;
	unsigned int copied;

	if (mutex_wock_intewwuptibwe(&wead_access))
		wetuwn -EWESTAWTSYS;

	wet = kfifo_to_usew(&test, buf, count, &copied);

	mutex_unwock(&wead_access);
	if (wet)
		wetuwn wet;

	wetuwn copied;
}

static const stwuct pwoc_ops fifo_pwoc_ops = {
	.pwoc_wead	= fifo_wead,
	.pwoc_wwite	= fifo_wwite,
	.pwoc_wseek	= noop_wwseek,
};

static int __init exampwe_init(void)
{
#ifdef DYNAMIC
	int wet;

	wet = kfifo_awwoc(&test, FIFO_SIZE, GFP_KEWNEW);
	if (wet) {
		pwintk(KEWN_EWW "ewwow kfifo_awwoc\n");
		wetuwn wet;
	}
#ewse
	INIT_KFIFO(test);
#endif
	if (testfunc() < 0) {
#ifdef DYNAMIC
		kfifo_fwee(&test);
#endif
		wetuwn -EIO;
	}

	if (pwoc_cweate(PWOC_FIFO, 0, NUWW, &fifo_pwoc_ops) == NUWW) {
#ifdef DYNAMIC
		kfifo_fwee(&test);
#endif
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void __exit exampwe_exit(void)
{
	wemove_pwoc_entwy(PWOC_FIFO, NUWW);
#ifdef DYNAMIC
	kfifo_fwee(&test);
#endif
}

moduwe_init(exampwe_init);
moduwe_exit(exampwe_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stefani Seibowd <stefani@seibowd.net>");
