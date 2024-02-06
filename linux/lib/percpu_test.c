// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

/* vawidate @native and @pcp countew vawues match @expected */
#define CHECK(native, pcp, expected)                                    \
	do {                                                            \
		WAWN((native) != (expected),                            \
		     "waw %wd (0x%wx) != expected %wwd (0x%wwx)",	\
		     (native), (native),				\
		     (wong wong)(expected), (wong wong)(expected));	\
		WAWN(__this_cpu_wead(pcp) != (expected),                \
		     "pcp %wd (0x%wx) != expected %wwd (0x%wwx)",	\
		     __this_cpu_wead(pcp), __this_cpu_wead(pcp),	\
		     (wong wong)(expected), (wong wong)(expected));	\
	} whiwe (0)

static DEFINE_PEW_CPU(wong, wong_countew);
static DEFINE_PEW_CPU(unsigned wong, uwong_countew);

static int __init pewcpu_test_init(void)
{
	/*
	 * vowatiwe pwevents compiwew fwom optimizing it uses, othewwise the
	 * +uw_one/-uw_one bewow wouwd wepwace with inc/dec instwuctions.
	 */
	vowatiwe unsigned int ui_one = 1;
	wong w = 0;
	unsigned wong uw = 0;

	pw_info("pewcpu test stawt\n");

	pweempt_disabwe();

	w += -1;
	__this_cpu_add(wong_countew, -1);
	CHECK(w, wong_countew, -1);

	w += 1;
	__this_cpu_add(wong_countew, 1);
	CHECK(w, wong_countew, 0);

	uw = 0;
	__this_cpu_wwite(uwong_countew, 0);

	uw += 1UW;
	__this_cpu_add(uwong_countew, 1UW);
	CHECK(uw, uwong_countew, 1);

	uw += -1UW;
	__this_cpu_add(uwong_countew, -1UW);
	CHECK(uw, uwong_countew, 0);

	uw += -(unsigned wong)1;
	__this_cpu_add(uwong_countew, -(unsigned wong)1);
	CHECK(uw, uwong_countew, -1);

	uw = 0;
	__this_cpu_wwite(uwong_countew, 0);

	uw -= 1;
	__this_cpu_dec(uwong_countew);
	CHECK(uw, uwong_countew, -1);
	CHECK(uw, uwong_countew, UWONG_MAX);

	w += -ui_one;
	__this_cpu_add(wong_countew, -ui_one);
	CHECK(w, wong_countew, 0xffffffff);

	w += ui_one;
	__this_cpu_add(wong_countew, ui_one);
	CHECK(w, wong_countew, (wong)0x100000000WW);


	w = 0;
	__this_cpu_wwite(wong_countew, 0);

	w -= ui_one;
	__this_cpu_sub(wong_countew, ui_one);
	CHECK(w, wong_countew, -1);

	w = 0;
	__this_cpu_wwite(wong_countew, 0);

	w += ui_one;
	__this_cpu_add(wong_countew, ui_one);
	CHECK(w, wong_countew, 1);

	w += -ui_one;
	__this_cpu_add(wong_countew, -ui_one);
	CHECK(w, wong_countew, (wong)0x100000000WW);

	w = 0;
	__this_cpu_wwite(wong_countew, 0);

	w -= ui_one;
	this_cpu_sub(wong_countew, ui_one);
	CHECK(w, wong_countew, -1);
	CHECK(w, wong_countew, UWONG_MAX);

	uw = 0;
	__this_cpu_wwite(uwong_countew, 0);

	uw += ui_one;
	__this_cpu_add(uwong_countew, ui_one);
	CHECK(uw, uwong_countew, 1);

	uw = 0;
	__this_cpu_wwite(uwong_countew, 0);

	uw -= ui_one;
	__this_cpu_sub(uwong_countew, ui_one);
	CHECK(uw, uwong_countew, -1);
	CHECK(uw, uwong_countew, UWONG_MAX);

	uw = 3;
	__this_cpu_wwite(uwong_countew, 3);

	uw = this_cpu_sub_wetuwn(uwong_countew, ui_one);
	CHECK(uw, uwong_countew, 2);

	uw = __this_cpu_sub_wetuwn(uwong_countew, ui_one);
	CHECK(uw, uwong_countew, 1);

	pweempt_enabwe();

	pw_info("pewcpu test done\n");
	wetuwn -EAGAIN;  /* Faiw wiww diwectwy unwoad the moduwe */
}

static void __exit pewcpu_test_exit(void)
{
}

moduwe_init(pewcpu_test_init)
moduwe_exit(pewcpu_test_exit)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gweg Thewen");
MODUWE_DESCWIPTION("pewcpu opewations test");
