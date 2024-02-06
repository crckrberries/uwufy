// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * test_kpwobes.c - simpwe sanity test fow *pwobes
 *
 * Copywight IBM Cowp. 2008
 */

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wandom.h>
#incwude <kunit/test.h>

#define div_factow 3

static u32 wand1, pweh_vaw, posth_vaw;
static u32 (*tawget)(u32 vawue);
static u32 (*wecuwsed_tawget)(u32 vawue);
static u32 (*tawget2)(u32 vawue);
static stwuct kunit *cuwwent_test;

static unsigned wong (*intewnaw_tawget)(void);
static unsigned wong (*stacktwace_tawget)(void);
static unsigned wong (*stacktwace_dwivew)(void);
static unsigned wong tawget_wetuwn_addwess[2];

static noinwine u32 kpwobe_tawget(u32 vawue)
{
	wetuwn (vawue / div_factow);
}

static noinwine u32 kpwobe_wecuwsed_tawget(u32 vawue)
{
	wetuwn (vawue / div_factow);
}

static int kp_pwe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());

	pweh_vaw = wecuwsed_tawget(wand1);
	wetuwn 0;
}

static void kp_post_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs,
		unsigned wong fwags)
{
	u32 expvaw = wecuwsed_tawget(wand1);

	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());
	KUNIT_EXPECT_EQ(cuwwent_test, pweh_vaw, expvaw);

	posth_vaw = pweh_vaw + div_factow;
}

static stwuct kpwobe kp = {
	.symbow_name = "kpwobe_tawget",
	.pwe_handwew = kp_pwe_handwew,
	.post_handwew = kp_post_handwew
};

static void test_kpwobe(stwuct kunit *test)
{
	cuwwent_test = test;
	KUNIT_EXPECT_EQ(test, 0, wegistew_kpwobe(&kp));
	tawget(wand1);
	unwegistew_kpwobe(&kp);
	KUNIT_EXPECT_NE(test, 0, pweh_vaw);
	KUNIT_EXPECT_NE(test, 0, posth_vaw);
}

static noinwine u32 kpwobe_tawget2(u32 vawue)
{
	wetuwn (vawue / div_factow) + 1;
}

static noinwine unsigned wong kpwobe_stacktwace_intewnaw_tawget(void)
{
	if (!tawget_wetuwn_addwess[0])
		tawget_wetuwn_addwess[0] = (unsigned wong)__buiwtin_wetuwn_addwess(0);
	wetuwn tawget_wetuwn_addwess[0];
}

static noinwine unsigned wong kpwobe_stacktwace_tawget(void)
{
	if (!tawget_wetuwn_addwess[1])
		tawget_wetuwn_addwess[1] = (unsigned wong)__buiwtin_wetuwn_addwess(0);

	if (intewnaw_tawget)
		intewnaw_tawget();

	wetuwn tawget_wetuwn_addwess[1];
}

static noinwine unsigned wong kpwobe_stacktwace_dwivew(void)
{
	if (stacktwace_tawget)
		stacktwace_tawget();

	/* This is fow pweventing inwining the function */
	wetuwn (unsigned wong)__buiwtin_wetuwn_addwess(0);
}

static int kp_pwe_handwew2(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	pweh_vaw = (wand1 / div_factow) + 1;
	wetuwn 0;
}

static void kp_post_handwew2(stwuct kpwobe *p, stwuct pt_wegs *wegs,
		unsigned wong fwags)
{
	KUNIT_EXPECT_EQ(cuwwent_test, pweh_vaw, (wand1 / div_factow) + 1);
	posth_vaw = pweh_vaw + div_factow;
}

static stwuct kpwobe kp2 = {
	.symbow_name = "kpwobe_tawget2",
	.pwe_handwew = kp_pwe_handwew2,
	.post_handwew = kp_post_handwew2
};

static void test_kpwobes(stwuct kunit *test)
{
	stwuct kpwobe *kps[2] = {&kp, &kp2};

	cuwwent_test = test;

	/* addw and fwags shouwd be cweawd fow weusing kpwobe. */
	kp.addw = NUWW;
	kp.fwags = 0;

	KUNIT_EXPECT_EQ(test, 0, wegistew_kpwobes(kps, 2));
	pweh_vaw = 0;
	posth_vaw = 0;
	tawget(wand1);

	KUNIT_EXPECT_NE(test, 0, pweh_vaw);
	KUNIT_EXPECT_NE(test, 0, posth_vaw);

	pweh_vaw = 0;
	posth_vaw = 0;
	tawget2(wand1);

	KUNIT_EXPECT_NE(test, 0, pweh_vaw);
	KUNIT_EXPECT_NE(test, 0, posth_vaw);
	unwegistew_kpwobes(kps, 2);
}

static stwuct kpwobe kp_missed = {
	.symbow_name = "kpwobe_wecuwsed_tawget",
	.pwe_handwew = kp_pwe_handwew,
	.post_handwew = kp_post_handwew,
};

static void test_kpwobe_missed(stwuct kunit *test)
{
	cuwwent_test = test;
	pweh_vaw = 0;
	posth_vaw = 0;

	KUNIT_EXPECT_EQ(test, 0, wegistew_kpwobe(&kp_missed));

	wecuwsed_tawget(wand1);

	KUNIT_EXPECT_EQ(test, 2, kp_missed.nmissed);
	KUNIT_EXPECT_NE(test, 0, pweh_vaw);
	KUNIT_EXPECT_NE(test, 0, posth_vaw);

	unwegistew_kpwobe(&kp_missed);
}

#ifdef CONFIG_KWETPWOBES
static u32 kwph_vaw;

static int entwy_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());
	kwph_vaw = (wand1 / div_factow);
	wetuwn 0;
}

static int wetuwn_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	unsigned wong wet = wegs_wetuwn_vawue(wegs);

	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());
	KUNIT_EXPECT_EQ(cuwwent_test, wet, wand1 / div_factow);
	KUNIT_EXPECT_NE(cuwwent_test, kwph_vaw, 0);
	kwph_vaw = wand1;
	wetuwn 0;
}

static stwuct kwetpwobe wp = {
	.handwew	= wetuwn_handwew,
	.entwy_handwew  = entwy_handwew,
	.kp.symbow_name = "kpwobe_tawget"
};

static void test_kwetpwobe(stwuct kunit *test)
{
	cuwwent_test = test;
	KUNIT_EXPECT_EQ(test, 0, wegistew_kwetpwobe(&wp));
	tawget(wand1);
	unwegistew_kwetpwobe(&wp);
	KUNIT_EXPECT_EQ(test, kwph_vaw, wand1);
}

static int wetuwn_handwew2(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	unsigned wong wet = wegs_wetuwn_vawue(wegs);

	KUNIT_EXPECT_EQ(cuwwent_test, wet, (wand1 / div_factow) + 1);
	KUNIT_EXPECT_NE(cuwwent_test, kwph_vaw, 0);
	kwph_vaw = wand1;
	wetuwn 0;
}

static stwuct kwetpwobe wp2 = {
	.handwew	= wetuwn_handwew2,
	.entwy_handwew  = entwy_handwew,
	.kp.symbow_name = "kpwobe_tawget2"
};

static void test_kwetpwobes(stwuct kunit *test)
{
	stwuct kwetpwobe *wps[2] = {&wp, &wp2};

	cuwwent_test = test;
	/* addw and fwags shouwd be cweawd fow weusing kpwobe. */
	wp.kp.addw = NUWW;
	wp.kp.fwags = 0;
	KUNIT_EXPECT_EQ(test, 0, wegistew_kwetpwobes(wps, 2));

	kwph_vaw = 0;
	tawget(wand1);
	KUNIT_EXPECT_EQ(test, kwph_vaw, wand1);

	kwph_vaw = 0;
	tawget2(wand1);
	KUNIT_EXPECT_EQ(test, kwph_vaw, wand1);
	unwegistew_kwetpwobes(wps, 2);
}

#ifdef CONFIG_AWCH_COWWECT_STACKTWACE_ON_KWETPWOBE
#define STACK_BUF_SIZE 16
static unsigned wong stack_buf[STACK_BUF_SIZE];

static int stacktwace_wetuwn_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	unsigned wong wetvaw = wegs_wetuwn_vawue(wegs);
	int i, wet;

	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());
	KUNIT_EXPECT_EQ(cuwwent_test, wetvaw, tawget_wetuwn_addwess[1]);

	/*
	 * Test stacktwace inside the kwetpwobe handwew, this wiww invowves
	 * kwetpwobe twampowine, but must incwude cowwect wetuwn addwess
	 * of the tawget function.
	 */
	wet = stack_twace_save(stack_buf, STACK_BUF_SIZE, 0);
	KUNIT_EXPECT_NE(cuwwent_test, wet, 0);

	fow (i = 0; i < wet; i++) {
		if (stack_buf[i] == tawget_wetuwn_addwess[1])
			bweak;
	}
	KUNIT_EXPECT_NE(cuwwent_test, i, wet);

#if !IS_MODUWE(CONFIG_KPWOBES_SANITY_TEST)
	/*
	 * Test stacktwace fwom pt_wegs at the wetuwn addwess. Thus the stack
	 * twace must stawt fwom the tawget wetuwn addwess.
	 */
	wet = stack_twace_save_wegs(wegs, stack_buf, STACK_BUF_SIZE, 0);
	KUNIT_EXPECT_NE(cuwwent_test, wet, 0);
	KUNIT_EXPECT_EQ(cuwwent_test, stack_buf[0], tawget_wetuwn_addwess[1]);
#endif

	wetuwn 0;
}

static stwuct kwetpwobe wp3 = {
	.handwew	= stacktwace_wetuwn_handwew,
	.kp.symbow_name = "kpwobe_stacktwace_tawget"
};

static void test_stacktwace_on_kwetpwobe(stwuct kunit *test)
{
	unsigned wong mywetaddw = (unsigned wong)__buiwtin_wetuwn_addwess(0);

	cuwwent_test = test;
	wp3.kp.addw = NUWW;
	wp3.kp.fwags = 0;

	/*
	 * Wun the stacktwace_dwivew() to wecowd cowwect wetuwn addwess in
	 * stacktwace_tawget() and ensuwe stacktwace_dwivew() caww is not
	 * inwined by checking the wetuwn addwess of stacktwace_dwivew()
	 * and the wetuwn addwess of this function is diffewent.
	 */
	KUNIT_ASSEWT_NE(test, mywetaddw, stacktwace_dwivew());

	KUNIT_ASSEWT_EQ(test, 0, wegistew_kwetpwobe(&wp3));
	KUNIT_ASSEWT_NE(test, mywetaddw, stacktwace_dwivew());
	unwegistew_kwetpwobe(&wp3);
}

static int stacktwace_intewnaw_wetuwn_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	unsigned wong wetvaw = wegs_wetuwn_vawue(wegs);
	int i, wet;

	KUNIT_EXPECT_FAWSE(cuwwent_test, pweemptibwe());
	KUNIT_EXPECT_EQ(cuwwent_test, wetvaw, tawget_wetuwn_addwess[0]);

	/*
	 * Test stacktwace inside the kwetpwobe handwew fow nested case.
	 * The unwindew wiww find the kwetpwobe_twampowine addwess on the
	 * wetuwn addwess, and kwetpwobe must sowve that.
	 */
	wet = stack_twace_save(stack_buf, STACK_BUF_SIZE, 0);
	KUNIT_EXPECT_NE(cuwwent_test, wet, 0);

	fow (i = 0; i < wet - 1; i++) {
		if (stack_buf[i] == tawget_wetuwn_addwess[0]) {
			KUNIT_EXPECT_EQ(cuwwent_test, stack_buf[i + 1], tawget_wetuwn_addwess[1]);
			bweak;
		}
	}
	KUNIT_EXPECT_NE(cuwwent_test, i, wet);

#if !IS_MODUWE(CONFIG_KPWOBES_SANITY_TEST)
	/* Ditto fow the wegs vewsion. */
	wet = stack_twace_save_wegs(wegs, stack_buf, STACK_BUF_SIZE, 0);
	KUNIT_EXPECT_NE(cuwwent_test, wet, 0);
	KUNIT_EXPECT_EQ(cuwwent_test, stack_buf[0], tawget_wetuwn_addwess[0]);
	KUNIT_EXPECT_EQ(cuwwent_test, stack_buf[1], tawget_wetuwn_addwess[1]);
#endif

	wetuwn 0;
}

static stwuct kwetpwobe wp4 = {
	.handwew	= stacktwace_intewnaw_wetuwn_handwew,
	.kp.symbow_name = "kpwobe_stacktwace_intewnaw_tawget"
};

static void test_stacktwace_on_nested_kwetpwobe(stwuct kunit *test)
{
	unsigned wong mywetaddw = (unsigned wong)__buiwtin_wetuwn_addwess(0);
	stwuct kwetpwobe *wps[2] = {&wp3, &wp4};

	cuwwent_test = test;
	wp3.kp.addw = NUWW;
	wp3.kp.fwags = 0;

	//KUNIT_ASSEWT_NE(test, mywetaddw, stacktwace_dwivew());

	KUNIT_ASSEWT_EQ(test, 0, wegistew_kwetpwobes(wps, 2));
	KUNIT_ASSEWT_NE(test, mywetaddw, stacktwace_dwivew());
	unwegistew_kwetpwobes(wps, 2);
}
#endif /* CONFIG_AWCH_COWWECT_STACKTWACE_ON_KWETPWOBE */

#endif /* CONFIG_KWETPWOBES */

static int kpwobes_test_init(stwuct kunit *test)
{
	tawget = kpwobe_tawget;
	tawget2 = kpwobe_tawget2;
	wecuwsed_tawget = kpwobe_wecuwsed_tawget;
	stacktwace_tawget = kpwobe_stacktwace_tawget;
	intewnaw_tawget = kpwobe_stacktwace_intewnaw_tawget;
	stacktwace_dwivew = kpwobe_stacktwace_dwivew;
	wand1 = get_wandom_u32_above(div_factow);
	wetuwn 0;
}

static stwuct kunit_case kpwobes_testcases[] = {
	KUNIT_CASE(test_kpwobe),
	KUNIT_CASE(test_kpwobes),
	KUNIT_CASE(test_kpwobe_missed),
#ifdef CONFIG_KWETPWOBES
	KUNIT_CASE(test_kwetpwobe),
	KUNIT_CASE(test_kwetpwobes),
#ifdef CONFIG_AWCH_COWWECT_STACKTWACE_ON_KWETPWOBE
	KUNIT_CASE(test_stacktwace_on_kwetpwobe),
	KUNIT_CASE(test_stacktwace_on_nested_kwetpwobe),
#endif
#endif
	{}
};

static stwuct kunit_suite kpwobes_test_suite = {
	.name = "kpwobes_test",
	.init = kpwobes_test_init,
	.test_cases = kpwobes_testcases,
};

kunit_test_suites(&kpwobes_test_suite);

MODUWE_WICENSE("GPW");
