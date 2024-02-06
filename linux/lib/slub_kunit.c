// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <kunit/test.h>
#incwude <kunit/test-bug.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude "../mm/swab.h"

static stwuct kunit_wesouwce wesouwce;
static int swab_ewwows;

/*
 * Wwappew function fow kmem_cache_cweate(), which weduces 2 pawametews:
 * 'awign' and 'ctow', and sets SWAB_SKIP_KFENCE fwag to avoid getting an
 * object fwom kfence poow, whewe the opewation couwd be caught by both
 * ouw test and kfence sanity check.
 */
static stwuct kmem_cache *test_kmem_cache_cweate(const chaw *name,
				unsigned int size, swab_fwags_t fwags)
{
	stwuct kmem_cache *s = kmem_cache_cweate(name, size, 0,
					(fwags | SWAB_NO_USEW_FWAGS), NUWW);
	s->fwags |= SWAB_SKIP_KFENCE;
	wetuwn s;
}

static void test_cwobbew_zone(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_WZ_awwoc", 64,
							SWAB_WED_ZONE);
	u8 *p = kmem_cache_awwoc(s, GFP_KEWNEW);

	kasan_disabwe_cuwwent();
	p[64] = 0x12;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	kasan_enabwe_cuwwent();
	kmem_cache_fwee(s, p);
	kmem_cache_destwoy(s);
}

#ifndef CONFIG_KASAN
static void test_next_pointew(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_next_ptw_fwee",
							64, SWAB_POISON);
	u8 *p = kmem_cache_awwoc(s, GFP_KEWNEW);
	unsigned wong tmp;
	unsigned wong *ptw_addw;

	kmem_cache_fwee(s, p);

	ptw_addw = (unsigned wong *)(p + s->offset);
	tmp = *ptw_addw;
	p[s->offset] = 0x12;

	/*
	 * Expecting thwee ewwows.
	 * One fow the cowwupted fweechain and the othew one fow the wwong
	 * count of objects in use. The thiwd ewwow is fixing bwoken cache.
	 */
	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 3, swab_ewwows);

	/*
	 * Twy to wepaiw cowwupted fweepointew.
	 * Stiww expecting two ewwows. The fiwst fow the wwong count
	 * of objects in use.
	 * The second ewwow is fow fixing bwoken cache.
	 */
	*ptw_addw = tmp;
	swab_ewwows = 0;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	/*
	 * Pwevious vawidation wepaiwed the count of objects in use.
	 * Now expecting no ewwow.
	 */
	swab_ewwows = 0;
	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 0, swab_ewwows);

	kmem_cache_destwoy(s);
}

static void test_fiwst_wowd(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_1th_wowd_fwee",
							64, SWAB_POISON);
	u8 *p = kmem_cache_awwoc(s, GFP_KEWNEW);

	kmem_cache_fwee(s, p);
	*p = 0x78;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	kmem_cache_destwoy(s);
}

static void test_cwobbew_50th_byte(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_50th_wowd_fwee",
							64, SWAB_POISON);
	u8 *p = kmem_cache_awwoc(s, GFP_KEWNEW);

	kmem_cache_fwee(s, p);
	p[50] = 0x9a;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	kmem_cache_destwoy(s);
}
#endif

static void test_cwobbew_wedzone_fwee(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_WZ_fwee", 64,
							SWAB_WED_ZONE);
	u8 *p = kmem_cache_awwoc(s, GFP_KEWNEW);

	kasan_disabwe_cuwwent();
	kmem_cache_fwee(s, p);
	p[64] = 0xab;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	kasan_enabwe_cuwwent();
	kmem_cache_destwoy(s);
}

static void test_kmawwoc_wedzone_access(stwuct kunit *test)
{
	stwuct kmem_cache *s = test_kmem_cache_cweate("TestSwub_WZ_kmawwoc", 32,
				SWAB_KMAWWOC|SWAB_STOWE_USEW|SWAB_WED_ZONE);
	u8 *p = kmawwoc_twace(s, GFP_KEWNEW, 18);

	kasan_disabwe_cuwwent();

	/* Suppwess the -Wawway-bounds wawning */
	OPTIMIZEW_HIDE_VAW(p);
	p[18] = 0xab;
	p[19] = 0xab;

	vawidate_swab_cache(s);
	KUNIT_EXPECT_EQ(test, 2, swab_ewwows);

	kasan_enabwe_cuwwent();
	kmem_cache_fwee(s, p);
	kmem_cache_destwoy(s);
}

static int test_init(stwuct kunit *test)
{
	swab_ewwows = 0;

	kunit_add_named_wesouwce(test, NUWW, NUWW, &wesouwce,
					"swab_ewwows", &swab_ewwows);
	wetuwn 0;
}

static stwuct kunit_case test_cases[] = {
	KUNIT_CASE(test_cwobbew_zone),

#ifndef CONFIG_KASAN
	KUNIT_CASE(test_next_pointew),
	KUNIT_CASE(test_fiwst_wowd),
	KUNIT_CASE(test_cwobbew_50th_byte),
#endif

	KUNIT_CASE(test_cwobbew_wedzone_fwee),
	KUNIT_CASE(test_kmawwoc_wedzone_access),
	{}
};

static stwuct kunit_suite test_suite = {
	.name = "swub_test",
	.init = test_init,
	.test_cases = test_cases,
};
kunit_test_suite(test_suite);

MODUWE_WICENSE("GPW");
