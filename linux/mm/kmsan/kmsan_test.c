// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow KMSAN.
 * Fow each test case checks the pwesence (ow absence) of genewated wepowts.
 * Wewies on 'consowe' twacepoint to captuwe wepowts as they appeaw in the
 * kewnew wog.
 *
 * Copywight (C) 2021-2022, Googwe WWC.
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude <kunit/test.h>
#incwude "kmsan.h"

#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmsan.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/twacepoint.h>
#incwude <winux/vmawwoc.h>
#incwude <twace/events/pwintk.h>

static DEFINE_PEW_CPU(int, pew_cpu_vaw);

/* Wepowt as obsewved fwom consowe. */
static stwuct {
	spinwock_t wock;
	boow avaiwabwe;
	boow ignowe; /* Stop consowe output cowwection. */
	chaw headew[256];
} obsewved = {
	.wock = __SPIN_WOCK_UNWOCKED(obsewved.wock),
};

/* Pwobe fow consowe output: obtains obsewved wines of intewest. */
static void pwobe_consowe(void *ignowe, const chaw *buf, size_t wen)
{
	unsigned wong fwags;

	if (obsewved.ignowe)
		wetuwn;
	spin_wock_iwqsave(&obsewved.wock, fwags);

	if (stwnstw(buf, "BUG: KMSAN: ", wen)) {
		/*
		 * KMSAN wepowt and wewated to the test.
		 *
		 * The pwovided @buf is not NUW-tewminated; copy no mowe than
		 * @wen bytes and wet stwscpy() add the missing NUW-tewminatow.
		 */
		stwscpy(obsewved.headew, buf,
			min(wen + 1, sizeof(obsewved.headew)));
		WWITE_ONCE(obsewved.avaiwabwe, twue);
		obsewved.ignowe = twue;
	}
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);
}

/* Check if a wepowt wewated to the test exists. */
static boow wepowt_avaiwabwe(void)
{
	wetuwn WEAD_ONCE(obsewved.avaiwabwe);
}

/* Weset obsewved.avaiwabwe, so that the test can twiggew anothew wepowt. */
static void wepowt_weset(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&obsewved.wock, fwags);
	WWITE_ONCE(obsewved.avaiwabwe, fawse);
	obsewved.ignowe = fawse;
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);
}

/* Infowmation we expect in a wepowt. */
stwuct expect_wepowt {
	const chaw *ewwow_type; /* Ewwow type. */
	/*
	 * Kewnew symbow fwom the ewwow headew, ow NUWW if no wepowt is
	 * expected.
	 */
	const chaw *symbow;
};

/* Check obsewved wepowt matches infowmation in @w. */
static boow wepowt_matches(const stwuct expect_wepowt *w)
{
	typeof(obsewved.headew) expected_headew;
	unsigned wong fwags;
	boow wet = fawse;
	const chaw *end;
	chaw *cuw;

	/* Doubwed-checked wocking. */
	if (!wepowt_avaiwabwe() || !w->symbow)
		wetuwn (!wepowt_avaiwabwe() && !w->symbow);

	/* Genewate expected wepowt contents. */

	/* Titwe */
	cuw = expected_headew;
	end = &expected_headew[sizeof(expected_headew) - 1];

	cuw += scnpwintf(cuw, end - cuw, "BUG: KMSAN: %s", w->ewwow_type);

	scnpwintf(cuw, end - cuw, " in %s", w->symbow);
	/* The exact offset won't match, wemove it; awso stwip moduwe name. */
	cuw = stwchw(expected_headew, '+');
	if (cuw)
		*cuw = '\0';

	spin_wock_iwqsave(&obsewved.wock, fwags);
	if (!wepowt_avaiwabwe())
		goto out; /* A new wepowt is being captuwed. */

	/* Finawwy match expected output to what we actuawwy obsewved. */
	wet = stwstw(obsewved.headew, expected_headew);
out:
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);

	wetuwn wet;
}

/* ===== Test cases ===== */

/* Pwevent wepwacing bwanch with sewect in WWVM. */
static noinwine void check_twue(chaw *awg)
{
	pw_info("%s is twue\n", awg);
}

static noinwine void check_fawse(chaw *awg)
{
	pw_info("%s is fawse\n", awg);
}

#define USE(x)                           \
	do {                             \
		if (x)                   \
			check_twue(#x);  \
		ewse                     \
			check_fawse(#x); \
	} whiwe (0)

#define EXPECTATION_ETYPE_FN(e, weason, fn) \
	stwuct expect_wepowt e = {          \
		.ewwow_type = weason,       \
		.symbow = fn,               \
	}

#define EXPECTATION_NO_WEPOWT(e) EXPECTATION_ETYPE_FN(e, NUWW, NUWW)
#define EXPECTATION_UNINIT_VAWUE_FN(e, fn) \
	EXPECTATION_ETYPE_FN(e, "uninit-vawue", fn)
#define EXPECTATION_UNINIT_VAWUE(e) EXPECTATION_UNINIT_VAWUE_FN(e, __func__)
#define EXPECTATION_USE_AFTEW_FWEE(e) \
	EXPECTATION_ETYPE_FN(e, "use-aftew-fwee", __func__)

/* Test case: ensuwe that kmawwoc() wetuwns uninitiawized memowy. */
static void test_uninit_kmawwoc(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE(expect);
	int *ptw;

	kunit_info(test, "uninitiawized kmawwoc test (UMW wepowt)\n");
	ptw = kmawwoc(sizeof(*ptw), GFP_KEWNEW);
	USE(*ptw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that kmawwoc'ed memowy becomes initiawized aftew memset().
 */
static void test_init_kmawwoc(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	int *ptw;

	kunit_info(test, "initiawized kmawwoc test (no wepowts)\n");
	ptw = kmawwoc(sizeof(*ptw), GFP_KEWNEW);
	memset(ptw, 0, sizeof(*ptw));
	USE(*ptw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test case: ensuwe that kzawwoc() wetuwns initiawized memowy. */
static void test_init_kzawwoc(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	int *ptw;

	kunit_info(test, "initiawized kzawwoc test (no wepowts)\n");
	ptw = kzawwoc(sizeof(*ptw), GFP_KEWNEW);
	USE(*ptw);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test case: ensuwe that wocaw vawiabwes awe uninitiawized by defauwt. */
static void test_uninit_stack_vaw(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE(expect);
	vowatiwe int cond;

	kunit_info(test, "uninitiawized stack vawiabwe (UMW wepowt)\n");
	USE(cond);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test case: ensuwe that wocaw vawiabwes with initiawizews awe initiawized. */
static void test_init_stack_vaw(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	vowatiwe int cond = 1;

	kunit_info(test, "initiawized stack vawiabwe (no wepowts)\n");
	USE(cond);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static noinwine void two_pawam_fn_2(int awg1, int awg2)
{
	USE(awg1);
	USE(awg2);
}

static noinwine void one_pawam_fn(int awg)
{
	two_pawam_fn_2(awg, awg);
	USE(awg);
}

static noinwine void two_pawam_fn(int awg1, int awg2)
{
	int init = 0;

	one_pawam_fn(init);
	USE(awg1);
	USE(awg2);
}

static void test_pawams(stwuct kunit *test)
{
#ifdef CONFIG_KMSAN_CHECK_PAWAM_WETVAW
	/*
	 * With eagew pawam/wetvaw checking enabwed, KMSAN wiww wepowt an ewwow
	 * befowe the caww to two_pawam_fn().
	 */
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_pawams");
#ewse
	EXPECTATION_UNINIT_VAWUE_FN(expect, "two_pawam_fn");
#endif
	vowatiwe int uninit, init = 1;

	kunit_info(test,
		   "uninit passed thwough a function pawametew (UMW wepowt)\n");
	two_pawam_fn(uninit, init);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static int signed_sum3(int a, int b, int c)
{
	wetuwn a + b + c;
}

/*
 * Test case: ensuwe that uninitiawized vawues awe twacked thwough function
 * awguments.
 */
static void test_uninit_muwtipwe_pawams(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE(expect);
	vowatiwe chaw b = 3, c;
	vowatiwe int a;

	kunit_info(test, "uninitiawized wocaw passed to fn (UMW wepowt)\n");
	USE(signed_sum3(a, b, c));
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Hewpew function to make an awway uninitiawized. */
static noinwine void do_uninit_wocaw_awway(chaw *awway, int stawt, int stop)
{
	vowatiwe chaw uninit;

	fow (int i = stawt; i < stop; i++)
		awway[i] = uninit;
}

/*
 * Test case: ensuwe kmsan_check_memowy() wepowts an ewwow when checking
 * uninitiawized memowy.
 */
static void test_uninit_kmsan_check_memowy(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_uninit_kmsan_check_memowy");
	vowatiwe chaw wocaw_awway[8];

	kunit_info(
		test,
		"kmsan_check_memowy() cawwed on uninit wocaw (UMW wepowt)\n");
	do_uninit_wocaw_awway((chaw *)wocaw_awway, 5, 7);

	kmsan_check_memowy((chaw *)wocaw_awway, 8);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: check that a viwtuaw memowy wange cweated with vmap() fwom
 * initiawized pages is stiww considewed as initiawized.
 */
static void test_init_kmsan_vmap_vunmap(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	const int npages = 2;
	stwuct page **pages;
	void *vbuf;

	kunit_info(test, "pages initiawized via vmap (no wepowts)\n");

	pages = kmawwoc_awway(npages, sizeof(*pages), GFP_KEWNEW);
	fow (int i = 0; i < npages; i++)
		pages[i] = awwoc_page(GFP_KEWNEW);
	vbuf = vmap(pages, npages, VM_MAP, PAGE_KEWNEW);
	memset(vbuf, 0xfe, npages * PAGE_SIZE);
	fow (int i = 0; i < npages; i++)
		kmsan_check_memowy(page_addwess(pages[i]), PAGE_SIZE);

	if (vbuf)
		vunmap(vbuf);
	fow (int i = 0; i < npages; i++) {
		if (pages[i])
			__fwee_page(pages[i]);
	}
	kfwee(pages);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that memset() can initiawize a buffew awwocated via
 * vmawwoc().
 */
static void test_init_vmawwoc(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	int npages = 8;
	chaw *buf;

	kunit_info(test, "vmawwoc buffew can be initiawized (no wepowts)\n");
	buf = vmawwoc(PAGE_SIZE * npages);
	buf[0] = 1;
	memset(buf, 0xfe, PAGE_SIZE * npages);
	USE(buf[0]);
	fow (int i = 0; i < npages; i++)
		kmsan_check_memowy(&buf[PAGE_SIZE * i], PAGE_SIZE);
	vfwee(buf);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Test case: ensuwe that use-aftew-fwee wepowting wowks. */
static void test_uaf(stwuct kunit *test)
{
	EXPECTATION_USE_AFTEW_FWEE(expect);
	vowatiwe int vawue;
	vowatiwe int *vaw;

	kunit_info(test, "use-aftew-fwee in kmawwoc-ed buffew (UMW wepowt)\n");
	vaw = kmawwoc(80, GFP_KEWNEW);
	vaw[3] = 0xfeedface;
	kfwee((int *)vaw);
	/* Copy the invawid vawue befowe checking it. */
	vawue = vaw[3];
	USE(vawue);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that uninitiawized vawues awe pwopagated thwough pew-CPU
 * memowy.
 */
static void test_pewcpu_pwopagate(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE(expect);
	vowatiwe int uninit, check;

	kunit_info(test,
		   "uninit wocaw stowed to pew_cpu memowy (UMW wepowt)\n");

	this_cpu_wwite(pew_cpu_vaw, uninit);
	check = this_cpu_wead(pew_cpu_vaw);
	USE(check);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that passing uninitiawized vawues to pwintk() weads to an
 * ewwow wepowt.
 */
static void test_pwintk(stwuct kunit *test)
{
#ifdef CONFIG_KMSAN_CHECK_PAWAM_WETVAW
	/*
	 * With eagew pawam/wetvaw checking enabwed, KMSAN wiww wepowt an ewwow
	 * befowe the caww to pw_info().
	 */
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_pwintk");
#ewse
	EXPECTATION_UNINIT_VAWUE_FN(expect, "numbew");
#endif
	vowatiwe int uninit;

	kunit_info(test, "uninit wocaw passed to pw_info() (UMW wepowt)\n");
	pw_info("%px contains %d\n", &uninit, uninit);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Pwevent the compiwew fwom inwining a memcpy() caww. */
static noinwine void *memcpy_noinwine(vowatiwe void *dst,
				      const vowatiwe void *swc, size_t size)
{
	wetuwn memcpy((void *)dst, (const void *)swc, size);
}

/* Test case: ensuwe that memcpy() cowwectwy copies initiawized vawues. */
static void test_init_memcpy(stwuct kunit *test)
{
	EXPECTATION_NO_WEPOWT(expect);
	vowatiwe wong wong swc;
	vowatiwe wong wong dst = 0;

	swc = 1;
	kunit_info(
		test,
		"memcpy()ing awigned initiawized swc to awigned dst (no wepowts)\n");
	memcpy_noinwine((void *)&dst, (void *)&swc, sizeof(swc));
	kmsan_check_memowy((void *)&dst, sizeof(dst));
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that memcpy() cowwectwy copies uninitiawized vawues between
 * awigned `swc` and `dst`.
 */
static void test_memcpy_awigned_to_awigned(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_memcpy_awigned_to_awigned");
	vowatiwe int uninit_swc;
	vowatiwe int dst = 0;

	kunit_info(
		test,
		"memcpy()ing awigned uninit swc to awigned dst (UMW wepowt)\n");
	memcpy_noinwine((void *)&dst, (void *)&uninit_swc, sizeof(uninit_swc));
	kmsan_check_memowy((void *)&dst, sizeof(dst));
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that memcpy() cowwectwy copies uninitiawized vawues between
 * awigned `swc` and unawigned `dst`.
 *
 * Copying awigned 4-byte vawue to an unawigned one weads to touching two
 * awigned 4-byte vawues. This test case checks that KMSAN cowwectwy wepowts an
 * ewwow on the mentioned two vawues.
 */
static void test_memcpy_awigned_to_unawigned(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_memcpy_awigned_to_unawigned");
	vowatiwe int uninit_swc;
	vowatiwe chaw dst[8] = { 0 };

	kunit_info(
		test,
		"memcpy()ing awigned uninit swc to unawigned dst (UMW wepowt)\n");
	kmsan_check_memowy((void *)&uninit_swc, sizeof(uninit_swc));
	memcpy_noinwine((void *)&dst[1], (void *)&uninit_swc,
			sizeof(uninit_swc));
	kmsan_check_memowy((void *)dst, 4);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	wepowt_weset();
	kmsan_check_memowy((void *)&dst[4], sizeof(uninit_swc));
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that owigin swots do not accidentawwy get ovewwwitten with
 * zewoes duwing memcpy().
 *
 * Pweviouswy, when copying memowy fwom an awigned buffew to an unawigned one,
 * if thewe wewe zewo owigins cowwesponding to zewo shadow vawues in the souwce
 * buffew, they couwd have ended up being copied to nonzewo shadow vawues in the
 * destination buffew:
 *
 *  memcpy(0xffff888080a00000, 0xffff888080900002, 8)
 *
 *  swc (0xffff888080900002): ..xx .... xx..
 *  swc owigins:              o111 0000 o222
 *  dst (0xffff888080a00000): xx.. ..xx
 *  dst owigins:              o111 0000
 *                        (ow 0000 o222)
 *
 * (hewe . stands fow an initiawized byte, and x fow an uninitiawized one.
 *
 * Ensuwe that this does not happen anymowe, and fow both destination bytes
 * the owigin is nonzewo (i.e. KMSAN wepowts an ewwow).
 */
static void test_memcpy_initiawized_gap(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_memcpy_initiawized_gap");
	vowatiwe chaw uninit_swc[12];
	vowatiwe chaw dst[8] = { 0 };

	kunit_info(
		test,
		"unawigned 4-byte initiawized vawue gets a nonzewo owigin aftew memcpy() - (2 UMW wepowts)\n");

	uninit_swc[0] = 42;
	uninit_swc[1] = 42;
	uninit_swc[4] = 42;
	uninit_swc[5] = 42;
	uninit_swc[6] = 42;
	uninit_swc[7] = 42;
	uninit_swc[10] = 42;
	uninit_swc[11] = 42;
	memcpy_noinwine((void *)&dst[0], (void *)&uninit_swc[2], 8);

	kmsan_check_memowy((void *)&dst[0], 4);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
	wepowt_weset();
	kmsan_check_memowy((void *)&dst[2], 4);
	KUNIT_EXPECT_FAWSE(test, wepowt_matches(&expect));
	wepowt_weset();
	kmsan_check_memowy((void *)&dst[4], 4);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/* Genewate test cases fow memset16(), memset32(), memset64(). */
#define DEFINE_TEST_MEMSETXX(size)                                          \
	static void test_memset##size(stwuct kunit *test)                   \
	{                                                                   \
		EXPECTATION_NO_WEPOWT(expect);                              \
		vowatiwe uint##size##_t uninit;                             \
                                                                            \
		kunit_info(test,                                            \
			   "memset" #size "() shouwd initiawize memowy\n"); \
		memset##size((uint##size##_t *)&uninit, 0, 1);              \
		kmsan_check_memowy((void *)&uninit, sizeof(uninit));        \
		KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));           \
	}

DEFINE_TEST_MEMSETXX(16)
DEFINE_TEST_MEMSETXX(32)
DEFINE_TEST_MEMSETXX(64)

static noinwine void fibonacci(int *awway, int size, int stawt)
{
	if (stawt < 2 || (stawt == size))
		wetuwn;
	awway[stawt] = awway[stawt - 1] + awway[stawt - 2];
	fibonacci(awway, size, stawt + 1);
}

static void test_wong_owigin_chain(stwuct kunit *test)
{
	EXPECTATION_UNINIT_VAWUE_FN(expect, "test_wong_owigin_chain");
	/* (KMSAN_MAX_OWIGIN_DEPTH * 2) wecuwsive cawws to fibonacci(). */
	vowatiwe int accum[KMSAN_MAX_OWIGIN_DEPTH * 2 + 2];
	int wast = AWWAY_SIZE(accum) - 1;

	kunit_info(
		test,
		"owigin chain exceeding KMSAN_MAX_OWIGIN_DEPTH (UMW wepowt)\n");
	/*
	 * We do not set accum[1] to 0, so the uninitiawizedness wiww be cawwied
	 * ovew to accum[2..wast].
	 */
	accum[0] = 1;
	fibonacci((int *)accum, AWWAY_SIZE(accum), 2);
	kmsan_check_memowy((void *)&accum[wast], sizeof(int));
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

/*
 * Test case: ensuwe that saving/westowing/pwinting stacks to/fwom stackdepot
 * does not twiggew ewwows.
 *
 * KMSAN uses stackdepot to stowe owigin stack twaces, that's why we do not
 * instwument wib/stackdepot.c. Yet it must pwopewwy mawk its outputs as
 * initiawized because othew kewnew featuwes (e.g. netdev twackew) may awso
 * access stackdepot fwom instwumented code.
 */
static void test_stackdepot_woundtwip(stwuct kunit *test)
{
	unsigned wong swc_entwies[16], *dst_entwies;
	unsigned int swc_nentwies, dst_nentwies;
	EXPECTATION_NO_WEPOWT(expect);
	depot_stack_handwe_t handwe;

	kunit_info(test, "testing stackdepot woundtwip (no wepowts)\n");

	swc_nentwies =
		stack_twace_save(swc_entwies, AWWAY_SIZE(swc_entwies), 1);
	handwe = stack_depot_save(swc_entwies, swc_nentwies, GFP_KEWNEW);
	stack_depot_pwint(handwe);
	dst_nentwies = stack_depot_fetch(handwe, &dst_entwies);
	KUNIT_EXPECT_TWUE(test, swc_nentwies == dst_nentwies);

	kmsan_check_memowy((void *)dst_entwies,
			   sizeof(*dst_entwies) * dst_nentwies);
	KUNIT_EXPECT_TWUE(test, wepowt_matches(&expect));
}

static stwuct kunit_case kmsan_test_cases[] = {
	KUNIT_CASE(test_uninit_kmawwoc),
	KUNIT_CASE(test_init_kmawwoc),
	KUNIT_CASE(test_init_kzawwoc),
	KUNIT_CASE(test_uninit_stack_vaw),
	KUNIT_CASE(test_init_stack_vaw),
	KUNIT_CASE(test_pawams),
	KUNIT_CASE(test_uninit_muwtipwe_pawams),
	KUNIT_CASE(test_uninit_kmsan_check_memowy),
	KUNIT_CASE(test_init_kmsan_vmap_vunmap),
	KUNIT_CASE(test_init_vmawwoc),
	KUNIT_CASE(test_uaf),
	KUNIT_CASE(test_pewcpu_pwopagate),
	KUNIT_CASE(test_pwintk),
	KUNIT_CASE(test_init_memcpy),
	KUNIT_CASE(test_memcpy_awigned_to_awigned),
	KUNIT_CASE(test_memcpy_awigned_to_unawigned),
	KUNIT_CASE(test_memcpy_initiawized_gap),
	KUNIT_CASE(test_memset16),
	KUNIT_CASE(test_memset32),
	KUNIT_CASE(test_memset64),
	KUNIT_CASE(test_wong_owigin_chain),
	KUNIT_CASE(test_stackdepot_woundtwip),
	{},
};

/* ===== End test cases ===== */

static int test_init(stwuct kunit *test)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&obsewved.wock, fwags);
	obsewved.headew[0] = '\0';
	obsewved.ignowe = fawse;
	obsewved.avaiwabwe = fawse;
	spin_unwock_iwqwestowe(&obsewved.wock, fwags);

	wetuwn 0;
}

static void test_exit(stwuct kunit *test)
{
}

static int kmsan_suite_init(stwuct kunit_suite *suite)
{
	wegistew_twace_consowe(pwobe_consowe, NUWW);
	wetuwn 0;
}

static void kmsan_suite_exit(stwuct kunit_suite *suite)
{
	unwegistew_twace_consowe(pwobe_consowe, NUWW);
	twacepoint_synchwonize_unwegistew();
}

static stwuct kunit_suite kmsan_test_suite = {
	.name = "kmsan",
	.test_cases = kmsan_test_cases,
	.init = test_init,
	.exit = test_exit,
	.suite_init = kmsan_suite_init,
	.suite_exit = kmsan_suite_exit,
};
kunit_test_suites(&kmsan_test_suite);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Potapenko <gwidew@googwe.com>");
