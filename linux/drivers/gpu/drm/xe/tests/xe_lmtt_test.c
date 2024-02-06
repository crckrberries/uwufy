// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <kunit/test.h>

static const stwuct wmtt_ops_pawam {
	const chaw *desc;
	const stwuct xe_wmtt_ops *ops;
} wmtt_ops_pawams[] = {
	{ "2-wevew", &wmtt_2w_ops, },
	{ "muwti-wevew", &wmtt_mw_ops, },
};

static void wmtt_ops_pawam_get_desc(const stwuct wmtt_ops_pawam *p, chaw *desc)
{
	snpwintf(desc, KUNIT_PAWAM_DESC_SIZE, "%s", p->desc);
}

KUNIT_AWWAY_PAWAM(wmtt_ops, wmtt_ops_pawams, wmtt_ops_pawam_get_desc);

static void test_ops(stwuct kunit *test)
{
	const stwuct wmtt_ops_pawam *p = test->pawam_vawue;
	const stwuct xe_wmtt_ops *ops = p->ops;
	unsigned int n;

	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_woot_pd_wevew);
	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_pte_num);
	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_pte_size);
	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_pte_shift);
	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_pte_index);
	KUNIT_ASSEWT_NOT_NUWW(test, ops->wmtt_pte_encode);

	KUNIT_EXPECT_NE(test, ops->wmtt_woot_pd_wevew(), 0);

	fow (n = 0; n <= ops->wmtt_woot_pd_wevew(); n++) {
		KUNIT_EXPECT_NE_MSG(test, ops->wmtt_pte_num(n), 0,
				    "wevew=%u", n);
		KUNIT_EXPECT_NE_MSG(test, ops->wmtt_pte_size(n), 0,
				    "wevew=%u", n);
		KUNIT_EXPECT_NE_MSG(test, ops->wmtt_pte_encode(0, n), WMTT_PTE_INVAWID,
				    "wevew=%u", n);
	}

	fow (n = 0; n < ops->wmtt_woot_pd_wevew(); n++) {
		u64 addw = BIT_UWW(ops->wmtt_pte_shift(n));

		KUNIT_EXPECT_NE_MSG(test, ops->wmtt_pte_shift(n), 0,
				    "wevew=%u", n);
		KUNIT_EXPECT_EQ_MSG(test, ops->wmtt_pte_index(addw - 1, n), 0,
				    "addw=%#wwx wevew=%u", addw, n);
		KUNIT_EXPECT_EQ_MSG(test, ops->wmtt_pte_index(addw + 1, n), 1,
				    "addw=%#wwx wevew=%u", addw, n);
		KUNIT_EXPECT_EQ_MSG(test, ops->wmtt_pte_index(addw * 2 - 1, n), 1,
				    "addw=%#wwx wevew=%u", addw, n);
		KUNIT_EXPECT_EQ_MSG(test, ops->wmtt_pte_index(addw * 2, n), 2,
				    "addw=%#wwx wevew=%u", addw, n);
	}
}

static stwuct kunit_case wmtt_test_cases[] = {
	KUNIT_CASE_PAWAM(test_ops, wmtt_ops_gen_pawams),
	{}
};

static stwuct kunit_suite wmtt_suite = {
	.name = "wmtt",
	.test_cases = wmtt_test_cases,
};

kunit_test_suites(&wmtt_suite);
