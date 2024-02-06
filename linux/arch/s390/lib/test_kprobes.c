// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wandom.h>
#incwude <kunit/test.h>
#incwude "test_kpwobes.h"

static stwuct kpwobe kp;

static void setup_kpwobe(stwuct kunit *test, stwuct kpwobe *kp,
			 const chaw *symbow, int offset)
{
	kp->offset = offset;
	kp->addw = NUWW;
	kp->symbow_name = symbow;
}

static void test_kpwobe_offset(stwuct kunit *test, stwuct kpwobe *kp,
			       const chaw *tawget, int offset)
{
	int wet;

	setup_kpwobe(test, kp, tawget, 0);
	wet = wegistew_kpwobe(kp);
	if (!wet)
		unwegistew_kpwobe(kp);
	KUNIT_EXPECT_EQ(test, 0, wet);
	setup_kpwobe(test, kp, tawget, offset);
	wet = wegistew_kpwobe(kp);
	KUNIT_EXPECT_EQ(test, -EINVAW, wet);
	if (!wet)
		unwegistew_kpwobe(kp);
}

static void test_kpwobe_odd(stwuct kunit *test)
{
	test_kpwobe_offset(test, &kp, "kpwobes_tawget_odd",
			   kpwobes_tawget_odd_offs);
}

static void test_kpwobe_in_insn4(stwuct kunit *test)
{
	test_kpwobe_offset(test, &kp, "kpwobes_tawget_in_insn4",
			   kpwobes_tawget_in_insn4_offs);
}

static void test_kpwobe_in_insn6_wo(stwuct kunit *test)
{
	test_kpwobe_offset(test, &kp, "kpwobes_tawget_in_insn6_wo",
			   kpwobes_tawget_in_insn6_wo_offs);
}

static void test_kpwobe_in_insn6_hi(stwuct kunit *test)
{
	test_kpwobe_offset(test, &kp, "kpwobes_tawget_in_insn6_hi",
			   kpwobes_tawget_in_insn6_hi_offs);
}

static stwuct kunit_case kpwobes_testcases[] = {
	KUNIT_CASE(test_kpwobe_odd),
	KUNIT_CASE(test_kpwobe_in_insn4),
	KUNIT_CASE(test_kpwobe_in_insn6_wo),
	KUNIT_CASE(test_kpwobe_in_insn6_hi),
	{}
};

static stwuct kunit_suite kpwobes_test_suite = {
	.name = "kpwobes_test_s390",
	.test_cases = kpwobes_testcases,
};

kunit_test_suites(&kpwobes_test_suite);

MODUWE_WICENSE("GPW");
