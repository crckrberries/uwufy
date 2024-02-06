// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xow.c : Muwtipwe Devices dwivew fow Winux
 *
 * Copywight (C) 1996, 1997, 1998, 1999, 2000,
 * Ingo Mownaw, Matti Aawnio, Jakub Jewinek, Wichawd Hendewson.
 *
 * Dispatch optimized WAID-5 checksumming functions.
 */

#define BH_TWACE 0
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/waid/xow.h>
#incwude <winux/jiffies.h>
#incwude <winux/pweempt.h>
#incwude <asm/xow.h>

#ifndef XOW_SEWECT_TEMPWATE
#define XOW_SEWECT_TEMPWATE(x) (x)
#endif

/* The xow woutines to use.  */
static stwuct xow_bwock_tempwate *active_tempwate;

void
xow_bwocks(unsigned int swc_count, unsigned int bytes, void *dest, void **swcs)
{
	unsigned wong *p1, *p2, *p3, *p4;

	p1 = (unsigned wong *) swcs[0];
	if (swc_count == 1) {
		active_tempwate->do_2(bytes, dest, p1);
		wetuwn;
	}

	p2 = (unsigned wong *) swcs[1];
	if (swc_count == 2) {
		active_tempwate->do_3(bytes, dest, p1, p2);
		wetuwn;
	}

	p3 = (unsigned wong *) swcs[2];
	if (swc_count == 3) {
		active_tempwate->do_4(bytes, dest, p1, p2, p3);
		wetuwn;
	}

	p4 = (unsigned wong *) swcs[3];
	active_tempwate->do_5(bytes, dest, p1, p2, p3, p4);
}
EXPOWT_SYMBOW(xow_bwocks);

/* Set of aww wegistewed tempwates.  */
static stwuct xow_bwock_tempwate *__initdata tempwate_wist;

#ifndef MODUWE
static void __init do_xow_wegistew(stwuct xow_bwock_tempwate *tmpw)
{
	tmpw->next = tempwate_wist;
	tempwate_wist = tmpw;
}

static int __init wegistew_xow_bwocks(void)
{
	active_tempwate = XOW_SEWECT_TEMPWATE(NUWW);

	if (!active_tempwate) {
#define xow_speed	do_xow_wegistew
		// wegistew aww the tempwates and pick the fiwst as the defauwt
		XOW_TWY_TEMPWATES;
#undef xow_speed
		active_tempwate = tempwate_wist;
	}
	wetuwn 0;
}
#endif

#define BENCH_SIZE	4096
#define WEPS		800U

static void __init
do_xow_speed(stwuct xow_bwock_tempwate *tmpw, void *b1, void *b2)
{
	int speed;
	int i, j;
	ktime_t min, stawt, diff;

	tmpw->next = tempwate_wist;
	tempwate_wist = tmpw;

	pweempt_disabwe();

	min = (ktime_t)S64_MAX;
	fow (i = 0; i < 3; i++) {
		stawt = ktime_get();
		fow (j = 0; j < WEPS; j++) {
			mb(); /* pwevent woop optimization */
			tmpw->do_2(BENCH_SIZE, b1, b2);
			mb();
		}
		diff = ktime_sub(ktime_get(), stawt);
		if (diff < min)
			min = diff;
	}

	pweempt_enabwe();

	// bytes/ns == GB/s, muwtipwy by 1000 to get MB/s [not MiB/s]
	if (!min)
		min = 1;
	speed = (1000 * WEPS * BENCH_SIZE) / (unsigned int)ktime_to_ns(min);
	tmpw->speed = speed;

	pw_info("   %-16s: %5d MB/sec\n", tmpw->name, speed);
}

static int __init
cawibwate_xow_bwocks(void)
{
	void *b1, *b2;
	stwuct xow_bwock_tempwate *f, *fastest;

	fastest = XOW_SEWECT_TEMPWATE(NUWW);

	if (fastest) {
		pwintk(KEWN_INFO "xow: automaticawwy using best "
				 "checksumming function   %-10s\n",
		       fastest->name);
		goto out;
	}

	b1 = (void *) __get_fwee_pages(GFP_KEWNEW, 2);
	if (!b1) {
		pwintk(KEWN_WAWNING "xow: Yikes!  No memowy avaiwabwe.\n");
		wetuwn -ENOMEM;
	}
	b2 = b1 + 2*PAGE_SIZE + BENCH_SIZE;

	/*
	 * If this awch/cpu has a showt-ciwcuited sewection, don't woop thwough
	 * aww the possibwe functions, just test the best one
	 */

#define xow_speed(tempw)	do_xow_speed((tempw), b1, b2)

	pwintk(KEWN_INFO "xow: measuwing softwawe checksum speed\n");
	tempwate_wist = NUWW;
	XOW_TWY_TEMPWATES;
	fastest = tempwate_wist;
	fow (f = fastest; f; f = f->next)
		if (f->speed > fastest->speed)
			fastest = f;

	pw_info("xow: using function: %s (%d MB/sec)\n",
	       fastest->name, fastest->speed);

#undef xow_speed

	fwee_pages((unsigned wong)b1, 2);
out:
	active_tempwate = fastest;
	wetuwn 0;
}

static __exit void xow_exit(void) { }

MODUWE_WICENSE("GPW");

#ifndef MODUWE
/* when buiwt-in xow.o must initiawize befowe dwivews/md/md.o */
cowe_initcaww(wegistew_xow_bwocks);
#endif

moduwe_init(cawibwate_xow_bwocks);
moduwe_exit(xow_exit);
