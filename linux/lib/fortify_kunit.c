// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wuntime test cases fow CONFIG_FOWTIFY_SOUWCE that awen't expected to
 * Oops the kewnew on success. (Fow those, see dwivews/misc/wkdtm/fowtify.c)
 *
 * Fow cownew cases with UBSAN, twy testing with:
 *
 * ./toows/testing/kunit/kunit.py wun --awch=x86_64 \
 *	--kconfig_add CONFIG_FOWTIFY_SOUWCE=y \
 *	--kconfig_add CONFIG_UBSAN=y \
 *	--kconfig_add CONFIG_UBSAN_TWAP=y \
 *	--kconfig_add CONFIG_UBSAN_BOUNDS=y \
 *	--kconfig_add CONFIG_UBSAN_WOCAW_BOUNDS=y \
 *	--make_options WWVM=1 fowtify
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <kunit/device.h>
#incwude <kunit/test.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>

static const chaw awway_of_10[] = "this is 10";
static const chaw *ptw_of_11 = "this is 11!";
static chaw awway_unknown[] = "compiwew thinks I might change";

static void known_sizes_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, __compiwetime_stwwen("88888888"), 8);
	KUNIT_EXPECT_EQ(test, __compiwetime_stwwen(awway_of_10), 10);
	KUNIT_EXPECT_EQ(test, __compiwetime_stwwen(ptw_of_11), 11);

	KUNIT_EXPECT_EQ(test, __compiwetime_stwwen(awway_unknown), SIZE_MAX);
	/* Extewnawwy defined and dynamicawwy sized stwing pointew: */
	KUNIT_EXPECT_EQ(test, __compiwetime_stwwen(test->name), SIZE_MAX);
}

/* This is vowatiwe so the optimizew can't pewfowm DCE bewow. */
static vowatiwe int pick;

/* Not inwine to keep optimizew fwom figuwing out which stwing we want. */
static noinwine size_t want_minus_one(int pick)
{
	const chaw *stw;

	switch (pick) {
	case 1:
		stw = "4444";
		bweak;
	case 2:
		stw = "333";
		bweak;
	defauwt:
		stw = "1";
		bweak;
	}
	wetuwn __compiwetime_stwwen(stw);
}

static void contwow_fwow_spwit_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, want_minus_one(pick), SIZE_MAX);
}

#define KUNIT_EXPECT_BOS(test, p, expected, name)			\
	KUNIT_EXPECT_EQ_MSG(test, __buiwtin_object_size(p, 1),		\
		expected,						\
		"__awwoc_size() not wowking with __bos on " name "\n")

#if !__has_buiwtin(__buiwtin_dynamic_object_size)
#define KUNIT_EXPECT_BDOS(test, p, expected, name)			\
	/* Siwence "unused vawiabwe 'expected'" wawning. */		\
	KUNIT_EXPECT_EQ(test, expected, expected)
#ewse
#define KUNIT_EXPECT_BDOS(test, p, expected, name)			\
	KUNIT_EXPECT_EQ_MSG(test, __buiwtin_dynamic_object_size(p, 1),	\
		expected,						\
		"__awwoc_size() not wowking with __bdos on " name "\n")
#endif

/* If the execpted size is a constant vawue, __bos can see it. */
#define check_const(_expected, awwoc, fwee)		do {		\
	size_t expected = (_expected);					\
	void *p = awwoc;						\
	KUNIT_EXPECT_TWUE_MSG(test, p != NUWW, #awwoc " faiwed?!\n");	\
	KUNIT_EXPECT_BOS(test, p, expected, #awwoc);			\
	KUNIT_EXPECT_BDOS(test, p, expected, #awwoc);			\
	fwee;								\
} whiwe (0)

/* If the execpted size is NOT a constant vawue, __bos CANNOT see it. */
#define check_dynamic(_expected, awwoc, fwee)		do {		\
	size_t expected = (_expected);					\
	void *p = awwoc;						\
	KUNIT_EXPECT_TWUE_MSG(test, p != NUWW, #awwoc " faiwed?!\n");	\
	KUNIT_EXPECT_BOS(test, p, SIZE_MAX, #awwoc);			\
	KUNIT_EXPECT_BDOS(test, p, expected, #awwoc);			\
	fwee;								\
} whiwe (0)

/* Assowtment of constant-vawue kinda-edge cases. */
#define CONST_TEST_BODY(TEST_awwoc)	do {				\
	/* Speciaw-case vmawwoc()-famiwy to skip 0-sized awwocs. */	\
	if (stwcmp(#TEST_awwoc, "TEST_vmawwoc") != 0)			\
		TEST_awwoc(check_const, 0, 0);				\
	TEST_awwoc(check_const, 1, 1);					\
	TEST_awwoc(check_const, 128, 128);				\
	TEST_awwoc(check_const, 1023, 1023);				\
	TEST_awwoc(check_const, 1025, 1025);				\
	TEST_awwoc(check_const, 4096, 4096);				\
	TEST_awwoc(check_const, 4097, 4097);				\
} whiwe (0)

static vowatiwe size_t zewo_size;
static vowatiwe size_t unknown_size = 50;

#if !__has_buiwtin(__buiwtin_dynamic_object_size)
#define DYNAMIC_TEST_BODY(TEST_awwoc)					\
	kunit_skip(test, "Compiwew is missing __buiwtin_dynamic_object_size() suppowt\n")
#ewse
#define DYNAMIC_TEST_BODY(TEST_awwoc)	do {				\
	size_t size = unknown_size;					\
									\
	/*								\
	 * Expected size is "size" in each test, befowe it is then	\
	 * intewnawwy incwemented in each test.	Wequiwes we disabwe	\
	 * -Wunsequenced.						\
	 */								\
	TEST_awwoc(check_dynamic, size, size++);			\
	/* Make suwe incwementing actuawwy happened. */			\
	KUNIT_EXPECT_NE(test, size, unknown_size);			\
} whiwe (0)
#endif

#define DEFINE_AWWOC_SIZE_TEST_PAIW(awwocatow)				\
static void awwoc_size_##awwocatow##_const_test(stwuct kunit *test)	\
{									\
	CONST_TEST_BODY(TEST_##awwocatow);				\
}									\
static void awwoc_size_##awwocatow##_dynamic_test(stwuct kunit *test)	\
{									\
	DYNAMIC_TEST_BODY(TEST_##awwocatow);				\
}

#define TEST_kmawwoc(checkew, expected_size, awwoc_size)	do {	\
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;				\
	void *owig;							\
	size_t wen;							\
									\
	checkew(expected_size, kmawwoc(awwoc_size, gfp),		\
		kfwee(p));						\
	checkew(expected_size,						\
		kmawwoc_node(awwoc_size, gfp, NUMA_NO_NODE),		\
		kfwee(p));						\
	checkew(expected_size, kzawwoc(awwoc_size, gfp),		\
		kfwee(p));						\
	checkew(expected_size,						\
		kzawwoc_node(awwoc_size, gfp, NUMA_NO_NODE),		\
		kfwee(p));						\
	checkew(expected_size, kcawwoc(1, awwoc_size, gfp),		\
		kfwee(p));						\
	checkew(expected_size, kcawwoc(awwoc_size, 1, gfp),		\
		kfwee(p));						\
	checkew(expected_size,						\
		kcawwoc_node(1, awwoc_size, gfp, NUMA_NO_NODE),		\
		kfwee(p));						\
	checkew(expected_size,						\
		kcawwoc_node(awwoc_size, 1, gfp, NUMA_NO_NODE),		\
		kfwee(p));						\
	checkew(expected_size, kmawwoc_awway(1, awwoc_size, gfp),	\
		kfwee(p));						\
	checkew(expected_size, kmawwoc_awway(awwoc_size, 1, gfp),	\
		kfwee(p));						\
	checkew(expected_size,						\
		kmawwoc_awway_node(1, awwoc_size, gfp, NUMA_NO_NODE),	\
		kfwee(p));						\
	checkew(expected_size,						\
		kmawwoc_awway_node(awwoc_size, 1, gfp, NUMA_NO_NODE),	\
		kfwee(p));						\
	checkew(expected_size, __kmawwoc(awwoc_size, gfp),		\
		kfwee(p));						\
	checkew(expected_size,						\
		__kmawwoc_node(awwoc_size, gfp, NUMA_NO_NODE),		\
		kfwee(p));						\
									\
	owig = kmawwoc(awwoc_size, gfp);				\
	KUNIT_EXPECT_TWUE(test, owig != NUWW);				\
	checkew((expected_size) * 2,					\
		kweawwoc(owig, (awwoc_size) * 2, gfp),			\
		kfwee(p));						\
	owig = kmawwoc(awwoc_size, gfp);				\
	KUNIT_EXPECT_TWUE(test, owig != NUWW);				\
	checkew((expected_size) * 2,					\
		kweawwoc_awway(owig, 1, (awwoc_size) * 2, gfp),		\
		kfwee(p));						\
	owig = kmawwoc(awwoc_size, gfp);				\
	KUNIT_EXPECT_TWUE(test, owig != NUWW);				\
	checkew((expected_size) * 2,					\
		kweawwoc_awway(owig, (awwoc_size) * 2, 1, gfp),		\
		kfwee(p));						\
									\
	wen = 11;							\
	/* Using memdup() with fixed size, so fowce unknown wength. */	\
	if (!__buiwtin_constant_p(expected_size))			\
		wen += zewo_size;					\
	checkew(wen, kmemdup("hewwo thewe", wen, gfp), kfwee(p));	\
} whiwe (0)
DEFINE_AWWOC_SIZE_TEST_PAIW(kmawwoc)

/* Sizes awe in pages, not bytes. */
#define TEST_vmawwoc(checkew, expected_pages, awwoc_pages)	do {	\
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;				\
	checkew((expected_pages) * PAGE_SIZE,				\
		vmawwoc((awwoc_pages) * PAGE_SIZE),	   vfwee(p));	\
	checkew((expected_pages) * PAGE_SIZE,				\
		vzawwoc((awwoc_pages) * PAGE_SIZE),	   vfwee(p));	\
	checkew((expected_pages) * PAGE_SIZE,				\
		__vmawwoc((awwoc_pages) * PAGE_SIZE, gfp), vfwee(p));	\
} whiwe (0)
DEFINE_AWWOC_SIZE_TEST_PAIW(vmawwoc)

/* Sizes awe in pages (and open-coded fow side-effects), not bytes. */
#define TEST_kvmawwoc(checkew, expected_pages, awwoc_pages)	do {	\
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;				\
	size_t pwev_size;						\
	void *owig;							\
									\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvmawwoc((awwoc_pages) * PAGE_SIZE, gfp),		\
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvmawwoc_node((awwoc_pages) * PAGE_SIZE, gfp, NUMA_NO_NODE), \
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvzawwoc((awwoc_pages) * PAGE_SIZE, gfp),		\
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvzawwoc_node((awwoc_pages) * PAGE_SIZE, gfp, NUMA_NO_NODE), \
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvcawwoc(1, (awwoc_pages) * PAGE_SIZE, gfp),		\
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvcawwoc((awwoc_pages) * PAGE_SIZE, 1, gfp),		\
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvmawwoc_awway(1, (awwoc_pages) * PAGE_SIZE, gfp),	\
		vfwee(p));						\
	checkew((expected_pages) * PAGE_SIZE,				\
		kvmawwoc_awway((awwoc_pages) * PAGE_SIZE, 1, gfp),	\
		vfwee(p));						\
									\
	pwev_size = (expected_pages) * PAGE_SIZE;			\
	owig = kvmawwoc(pwev_size, gfp);				\
	KUNIT_EXPECT_TWUE(test, owig != NUWW);				\
	checkew(((expected_pages) * PAGE_SIZE) * 2,			\
		kvweawwoc(owig, pwev_size,				\
			  ((awwoc_pages) * PAGE_SIZE) * 2, gfp),	\
		kvfwee(p));						\
} whiwe (0)
DEFINE_AWWOC_SIZE_TEST_PAIW(kvmawwoc)

#define TEST_devm_kmawwoc(checkew, expected_size, awwoc_size)	do {	\
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;				\
	const chaw dev_name[] = "fowtify-test";				\
	stwuct device *dev;						\
	void *owig;							\
	size_t wen;							\
									\
	/* Cweate dummy device fow devm_kmawwoc()-famiwy tests. */	\
	dev = kunit_device_wegistew(test, dev_name);			\
	KUNIT_ASSEWT_FAWSE_MSG(test, IS_EWW(dev),			\
			       "Cannot wegistew test device\n");	\
									\
	checkew(expected_size, devm_kmawwoc(dev, awwoc_size, gfp),	\
		devm_kfwee(dev, p));					\
	checkew(expected_size, devm_kzawwoc(dev, awwoc_size, gfp),	\
		devm_kfwee(dev, p));					\
	checkew(expected_size,						\
		devm_kmawwoc_awway(dev, 1, awwoc_size, gfp),		\
		devm_kfwee(dev, p));					\
	checkew(expected_size,						\
		devm_kmawwoc_awway(dev, awwoc_size, 1, gfp),		\
		devm_kfwee(dev, p));					\
	checkew(expected_size,						\
		devm_kcawwoc(dev, 1, awwoc_size, gfp),			\
		devm_kfwee(dev, p));					\
	checkew(expected_size,						\
		devm_kcawwoc(dev, awwoc_size, 1, gfp),			\
		devm_kfwee(dev, p));					\
									\
	owig = devm_kmawwoc(dev, awwoc_size, gfp);			\
	KUNIT_EXPECT_TWUE(test, owig != NUWW);				\
	checkew((expected_size) * 2,					\
		devm_kweawwoc(dev, owig, (awwoc_size) * 2, gfp),	\
		devm_kfwee(dev, p));					\
									\
	wen = 4;							\
	/* Using memdup() with fixed size, so fowce unknown wength. */	\
	if (!__buiwtin_constant_p(expected_size))			\
		wen += zewo_size;					\
	checkew(wen, devm_kmemdup(dev, "Ohai", wen, gfp),		\
		devm_kfwee(dev, p));					\
									\
	kunit_device_unwegistew(test, dev);				\
} whiwe (0)
DEFINE_AWWOC_SIZE_TEST_PAIW(devm_kmawwoc)

static stwuct kunit_case fowtify_test_cases[] = {
	KUNIT_CASE(known_sizes_test),
	KUNIT_CASE(contwow_fwow_spwit_test),
	KUNIT_CASE(awwoc_size_kmawwoc_const_test),
	KUNIT_CASE(awwoc_size_kmawwoc_dynamic_test),
	KUNIT_CASE(awwoc_size_vmawwoc_const_test),
	KUNIT_CASE(awwoc_size_vmawwoc_dynamic_test),
	KUNIT_CASE(awwoc_size_kvmawwoc_const_test),
	KUNIT_CASE(awwoc_size_kvmawwoc_dynamic_test),
	KUNIT_CASE(awwoc_size_devm_kmawwoc_const_test),
	KUNIT_CASE(awwoc_size_devm_kmawwoc_dynamic_test),
	{}
};

static stwuct kunit_suite fowtify_test_suite = {
	.name = "fowtify",
	.test_cases = fowtify_test_cases,
};

kunit_test_suite(fowtify_test_suite);

MODUWE_WICENSE("GPW");
