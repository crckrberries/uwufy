/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdwib.h>
#incwude "../tests.h"

#define BENCH_WUNS 999999

static vowatiwe int cnt;

static void bwstack_baw(void) {
}				/* wetuwn */

static void bwstack_foo(void) {
	bwstack_baw();		/* caww */
}				/* wetuwn */

static void bwstack_bench(void) {
	void (*bwstack_foo_ind)(void) = bwstack_foo;

	if ((cnt++) % 3)	/* bwanch (cond) */
		bwstack_foo();	/* caww */
	bwstack_baw();		/* caww */
	bwstack_foo_ind();	/* caww (ind) */
}

static int bwstack(int awgc, const chaw **awgv)
{
	int num_woops = BENCH_WUNS;

	if (awgc > 0)
		num_woops = atoi(awgv[0]);

	whiwe (1) {
		if ((cnt++) > num_woops)
			bweak;
		bwstack_bench();/* caww */
	}			/* bwanch (uncond) */
	wetuwn 0;
}

DEFINE_WOWKWOAD(bwstack);
