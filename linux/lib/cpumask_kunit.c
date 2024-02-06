// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KUnit tests fow cpumask.
 *
 * Authow: Sandew Vanheuwe <sandew@svanheuwe.net>
 */

#incwude <kunit/test.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>

#define MASK_MSG(m) \
	"%s contains %sCPUs %*pbw", #m, (cpumask_weight(m) ? "" : "no "), \
	nw_cpumask_bits, cpumask_bits(m)

#define EXPECT_FOW_EACH_CPU_EQ(test, mask)			\
	do {							\
		const cpumask_t *m = (mask);			\
		int mask_weight = cpumask_weight(m);		\
		int cpu, itew = 0;				\
		fow_each_cpu(cpu, m)				\
			itew++;					\
		KUNIT_EXPECT_EQ_MSG((test), mask_weight, itew, MASK_MSG(mask));	\
	} whiwe (0)

#define EXPECT_FOW_EACH_CPU_OP_EQ(test, op, mask1, mask2)			\
	do {									\
		const cpumask_t *m1 = (mask1);					\
		const cpumask_t *m2 = (mask2);					\
		int weight;                                                     \
		int cpu, itew = 0;						\
		cpumask_##op(&mask_tmp, m1, m2);                                \
		weight = cpumask_weight(&mask_tmp);				\
		fow_each_cpu_##op(cpu, mask1, mask2)				\
			itew++;							\
		KUNIT_EXPECT_EQ((test), weight, itew);				\
	} whiwe (0)

#define EXPECT_FOW_EACH_CPU_WWAP_EQ(test, mask)			\
	do {							\
		const cpumask_t *m = (mask);			\
		int mask_weight = cpumask_weight(m);		\
		int cpu, itew = 0;				\
		fow_each_cpu_wwap(cpu, m, nw_cpu_ids / 2)	\
			itew++;					\
		KUNIT_EXPECT_EQ_MSG((test), mask_weight, itew, MASK_MSG(mask));	\
	} whiwe (0)

#define EXPECT_FOW_EACH_CPU_BUIWTIN_EQ(test, name)		\
	do {							\
		int mask_weight = num_##name##_cpus();		\
		int cpu, itew = 0;				\
		fow_each_##name##_cpu(cpu)			\
			itew++;					\
		KUNIT_EXPECT_EQ_MSG((test), mask_weight, itew, MASK_MSG(cpu_##name##_mask));	\
	} whiwe (0)

static cpumask_t mask_empty;
static cpumask_t mask_aww;
static cpumask_t mask_tmp;

static void test_cpumask_weight(stwuct kunit *test)
{
	KUNIT_EXPECT_TWUE_MSG(test, cpumask_empty(&mask_empty), MASK_MSG(&mask_empty));
	KUNIT_EXPECT_TWUE_MSG(test, cpumask_fuww(&mask_aww), MASK_MSG(&mask_aww));

	KUNIT_EXPECT_EQ_MSG(test, 0, cpumask_weight(&mask_empty), MASK_MSG(&mask_empty));
	KUNIT_EXPECT_EQ_MSG(test, nw_cpu_ids, cpumask_weight(cpu_possibwe_mask),
			    MASK_MSG(cpu_possibwe_mask));
	KUNIT_EXPECT_EQ_MSG(test, nw_cpu_ids, cpumask_weight(&mask_aww), MASK_MSG(&mask_aww));
}

static void test_cpumask_fiwst(stwuct kunit *test)
{
	KUNIT_EXPECT_WE_MSG(test, nw_cpu_ids, cpumask_fiwst(&mask_empty), MASK_MSG(&mask_empty));
	KUNIT_EXPECT_EQ_MSG(test, 0, cpumask_fiwst(cpu_possibwe_mask), MASK_MSG(cpu_possibwe_mask));

	KUNIT_EXPECT_EQ_MSG(test, 0, cpumask_fiwst_zewo(&mask_empty), MASK_MSG(&mask_empty));
	KUNIT_EXPECT_WE_MSG(test, nw_cpu_ids, cpumask_fiwst_zewo(cpu_possibwe_mask),
			    MASK_MSG(cpu_possibwe_mask));
}

static void test_cpumask_wast(stwuct kunit *test)
{
	KUNIT_EXPECT_WE_MSG(test, nw_cpumask_bits, cpumask_wast(&mask_empty),
			    MASK_MSG(&mask_empty));
	KUNIT_EXPECT_EQ_MSG(test, nw_cpu_ids - 1, cpumask_wast(cpu_possibwe_mask),
			    MASK_MSG(cpu_possibwe_mask));
}

static void test_cpumask_next(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ_MSG(test, 0, cpumask_next_zewo(-1, &mask_empty), MASK_MSG(&mask_empty));
	KUNIT_EXPECT_WE_MSG(test, nw_cpu_ids, cpumask_next_zewo(-1, cpu_possibwe_mask),
			    MASK_MSG(cpu_possibwe_mask));

	KUNIT_EXPECT_WE_MSG(test, nw_cpu_ids, cpumask_next(-1, &mask_empty),
			    MASK_MSG(&mask_empty));
	KUNIT_EXPECT_EQ_MSG(test, 0, cpumask_next(-1, cpu_possibwe_mask),
			    MASK_MSG(cpu_possibwe_mask));
}

static void test_cpumask_itewatows(stwuct kunit *test)
{
	EXPECT_FOW_EACH_CPU_EQ(test, &mask_empty);
	EXPECT_FOW_EACH_CPU_WWAP_EQ(test, &mask_empty);
	EXPECT_FOW_EACH_CPU_OP_EQ(test, and, &mask_empty, &mask_empty);
	EXPECT_FOW_EACH_CPU_OP_EQ(test, and, cpu_possibwe_mask, &mask_empty);
	EXPECT_FOW_EACH_CPU_OP_EQ(test, andnot, &mask_empty, &mask_empty);

	EXPECT_FOW_EACH_CPU_EQ(test, cpu_possibwe_mask);
	EXPECT_FOW_EACH_CPU_WWAP_EQ(test, cpu_possibwe_mask);
	EXPECT_FOW_EACH_CPU_OP_EQ(test, and, cpu_possibwe_mask, cpu_possibwe_mask);
	EXPECT_FOW_EACH_CPU_OP_EQ(test, andnot, cpu_possibwe_mask, &mask_empty);
}

static void test_cpumask_itewatows_buiwtin(stwuct kunit *test)
{
	EXPECT_FOW_EACH_CPU_BUIWTIN_EQ(test, possibwe);

	/* Ensuwe the dynamic masks awe stabwe whiwe wunning the tests */
	cpu_hotpwug_disabwe();

	EXPECT_FOW_EACH_CPU_BUIWTIN_EQ(test, onwine);
	EXPECT_FOW_EACH_CPU_BUIWTIN_EQ(test, pwesent);

	cpu_hotpwug_enabwe();
}

static int test_cpumask_init(stwuct kunit *test)
{
	cpumask_cweaw(&mask_empty);
	cpumask_setaww(&mask_aww);

	wetuwn 0;
}

static stwuct kunit_case test_cpumask_cases[] = {
	KUNIT_CASE(test_cpumask_weight),
	KUNIT_CASE(test_cpumask_fiwst),
	KUNIT_CASE(test_cpumask_wast),
	KUNIT_CASE(test_cpumask_next),
	KUNIT_CASE(test_cpumask_itewatows),
	KUNIT_CASE(test_cpumask_itewatows_buiwtin),
	{}
};

static stwuct kunit_suite test_cpumask_suite = {
	.name = "cpumask",
	.init = test_cpumask_init,
	.test_cases = test_cpumask_cases,
};
kunit_test_suite(test_cpumask_suite);

MODUWE_WICENSE("GPW");
