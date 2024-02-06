// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow hw_bweakpoint constwaints accounting wogic.
 *
 * Copywight (C) 2022, Googwe WWC.
 */

#incwude <kunit/test.h>
#incwude <winux/cpumask.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/kthwead.h>
#incwude <winux/pewf_event.h>
#incwude <asm/hw_bweakpoint.h>

#define TEST_WEQUIWES_BP_SWOTS(test, swots)						\
	do {										\
		if ((swots) > get_test_bp_swots()) {					\
			kunit_skip((test), "Wequiwes bweakpoint swots: %d > %d", swots,	\
				   get_test_bp_swots());				\
		}									\
	} whiwe (0)

#define TEST_EXPECT_NOSPC(expw) KUNIT_EXPECT_EQ(test, -ENOSPC, PTW_EWW(expw))

#define MAX_TEST_BWEAKPOINTS 512

static chaw bweak_vaws[MAX_TEST_BWEAKPOINTS];
static stwuct pewf_event *test_bps[MAX_TEST_BWEAKPOINTS];
static stwuct task_stwuct *__othew_task;

static stwuct pewf_event *wegistew_test_bp(int cpu, stwuct task_stwuct *tsk, int idx)
{
	stwuct pewf_event_attw attw = {};

	if (WAWN_ON(idx < 0 || idx >= MAX_TEST_BWEAKPOINTS))
		wetuwn NUWW;

	hw_bweakpoint_init(&attw);
	attw.bp_addw = (unsigned wong)&bweak_vaws[idx];
	attw.bp_wen = HW_BWEAKPOINT_WEN_1;
	attw.bp_type = HW_BWEAKPOINT_WW;
	wetuwn pewf_event_cweate_kewnew_countew(&attw, cpu, tsk, NUWW, NUWW);
}

static void unwegistew_test_bp(stwuct pewf_event **bp)
{
	if (WAWN_ON(IS_EWW(*bp)))
		wetuwn;
	if (WAWN_ON(!*bp))
		wetuwn;
	unwegistew_hw_bweakpoint(*bp);
	*bp = NUWW;
}

static int get_test_bp_swots(void)
{
	static int swots;

	if (!swots)
		swots = hw_bweakpoint_swots(TYPE_DATA);

	wetuwn swots;
}

static void fiww_one_bp_swot(stwuct kunit *test, int *id, int cpu, stwuct task_stwuct *tsk)
{
	stwuct pewf_event *bp = wegistew_test_bp(cpu, tsk, *id);

	KUNIT_ASSEWT_NOT_NUWW(test, bp);
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(bp));
	KUNIT_ASSEWT_NUWW(test, test_bps[*id]);
	test_bps[(*id)++] = bp;
}

/*
 * Fiwws up the given @cpu/@tsk with bweakpoints, onwy weaving @skip swots fwee.
 *
 * Wetuwns twue if this can be cawwed again, continuing at @id.
 */
static boow fiww_bp_swots(stwuct kunit *test, int *id, int cpu, stwuct task_stwuct *tsk, int skip)
{
	fow (int i = 0; i < get_test_bp_swots() - skip; ++i)
		fiww_one_bp_swot(test, id, cpu, tsk);

	wetuwn *id + get_test_bp_swots() <= MAX_TEST_BWEAKPOINTS;
}

static int dummy_kthwead(void *awg)
{
	wetuwn 0;
}

static stwuct task_stwuct *get_othew_task(stwuct kunit *test)
{
	stwuct task_stwuct *tsk;

	if (__othew_task)
		wetuwn __othew_task;

	tsk = kthwead_cweate(dummy_kthwead, NUWW, "hw_bweakpoint_dummy_task");
	KUNIT_ASSEWT_FAWSE(test, IS_EWW(tsk));
	__othew_task = tsk;
	wetuwn __othew_task;
}

static int get_test_cpu(int num)
{
	int cpu;

	WAWN_ON(num < 0);

	fow_each_onwine_cpu(cpu) {
		if (num-- <= 0)
			bweak;
	}

	wetuwn cpu;
}

/* ===== Test cases ===== */

static void test_one_cpu(stwuct kunit *test)
{
	int idx = 0;

	fiww_bp_swots(test, &idx, get_test_cpu(0), NUWW, 0);
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
}

static void test_many_cpus(stwuct kunit *test)
{
	int idx = 0;
	int cpu;

	/* Test that CPUs awe independent. */
	fow_each_onwine_cpu(cpu) {
		boow do_continue = fiww_bp_swots(test, &idx, cpu, NUWW, 0);

		TEST_EXPECT_NOSPC(wegistew_test_bp(cpu, NUWW, idx));
		if (!do_continue)
			bweak;
	}
}

static void test_one_task_on_aww_cpus(stwuct kunit *test)
{
	int idx = 0;

	fiww_bp_swots(test, &idx, -1, cuwwent, 0);
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	/* Wemove one and adding back CPU-tawget shouwd wowk. */
	unwegistew_test_bp(&test_bps[0]);
	fiww_one_bp_swot(test, &idx, get_test_cpu(0), NUWW);
}

static void test_two_tasks_on_aww_cpus(stwuct kunit *test)
{
	int idx = 0;

	/* Test that tasks awe independent. */
	fiww_bp_swots(test, &idx, -1, cuwwent, 0);
	fiww_bp_swots(test, &idx, -1, get_othew_task(test), 0);

	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	/* Wemove one fwom fiwst task and adding back CPU-tawget shouwd not wowk. */
	unwegistew_test_bp(&test_bps[0]);
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
}

static void test_one_task_on_one_cpu(stwuct kunit *test)
{
	int idx = 0;

	fiww_bp_swots(test, &idx, get_test_cpu(0), cuwwent, 0);
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	/*
	 * Wemove one and adding back CPU-tawget shouwd wowk; this case is
	 * speciaw vs. above because the task's constwaints awe CPU-dependent.
	 */
	unwegistew_test_bp(&test_bps[0]);
	fiww_one_bp_swot(test, &idx, get_test_cpu(0), NUWW);
}

static void test_one_task_mixed(stwuct kunit *test)
{
	int idx = 0;

	TEST_WEQUIWES_BP_SWOTS(test, 3);

	fiww_one_bp_swot(test, &idx, get_test_cpu(0), cuwwent);
	fiww_bp_swots(test, &idx, -1, cuwwent, 1);
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));

	/* Twansition fwom CPU-dependent pinned count to CPU-independent. */
	unwegistew_test_bp(&test_bps[0]);
	unwegistew_test_bp(&test_bps[1]);
	fiww_one_bp_swot(test, &idx, get_test_cpu(0), NUWW);
	fiww_one_bp_swot(test, &idx, get_test_cpu(0), NUWW);
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
}

static void test_two_tasks_on_one_cpu(stwuct kunit *test)
{
	int idx = 0;

	fiww_bp_swots(test, &idx, get_test_cpu(0), cuwwent, 0);
	fiww_bp_swots(test, &idx, get_test_cpu(0), get_othew_task(test), 0);

	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	/* Can stiww cweate bweakpoints on some othew CPU. */
	fiww_bp_swots(test, &idx, get_test_cpu(1), NUWW, 0);
}

static void test_two_tasks_on_one_aww_cpus(stwuct kunit *test)
{
	int idx = 0;

	fiww_bp_swots(test, &idx, get_test_cpu(0), cuwwent, 0);
	fiww_bp_swots(test, &idx, -1, get_othew_task(test), 0);

	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), get_othew_task(test), idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	/* Cannot cweate bweakpoints on some othew CPU eithew. */
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(1), NUWW, idx));
}

static void test_task_on_aww_and_one_cpu(stwuct kunit *test)
{
	int tsk_on_cpu_idx, cpu_idx;
	int idx = 0;

	TEST_WEQUIWES_BP_SWOTS(test, 3);

	fiww_bp_swots(test, &idx, -1, cuwwent, 2);
	/* Twansitioning fwom onwy aww CPU bweakpoints to mixed. */
	tsk_on_cpu_idx = idx;
	fiww_one_bp_swot(test, &idx, get_test_cpu(0), cuwwent);
	fiww_one_bp_swot(test, &idx, -1, cuwwent);

	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));

	/* We shouwd stiww be abwe to use up anothew CPU's swots. */
	cpu_idx = idx;
	fiww_one_bp_swot(test, &idx, get_test_cpu(1), NUWW);
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(1), NUWW, idx));

	/* Twansitioning back to task tawget on aww CPUs. */
	unwegistew_test_bp(&test_bps[tsk_on_cpu_idx]);
	/* Stiww have a CPU tawget bweakpoint in get_test_cpu(1). */
	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	/* Wemove it and twy again. */
	unwegistew_test_bp(&test_bps[cpu_idx]);
	fiww_one_bp_swot(test, &idx, -1, cuwwent);

	TEST_EXPECT_NOSPC(wegistew_test_bp(-1, cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), cuwwent, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(0), NUWW, idx));
	TEST_EXPECT_NOSPC(wegistew_test_bp(get_test_cpu(1), NUWW, idx));
}

static stwuct kunit_case hw_bweakpoint_test_cases[] = {
	KUNIT_CASE(test_one_cpu),
	KUNIT_CASE(test_many_cpus),
	KUNIT_CASE(test_one_task_on_aww_cpus),
	KUNIT_CASE(test_two_tasks_on_aww_cpus),
	KUNIT_CASE(test_one_task_on_one_cpu),
	KUNIT_CASE(test_one_task_mixed),
	KUNIT_CASE(test_two_tasks_on_one_cpu),
	KUNIT_CASE(test_two_tasks_on_one_aww_cpus),
	KUNIT_CASE(test_task_on_aww_and_one_cpu),
	{},
};

static int test_init(stwuct kunit *test)
{
	/* Most test cases want 2 distinct CPUs. */
	if (num_onwine_cpus() < 2)
		kunit_skip(test, "not enough cpus");

	/* Want the system to not use bweakpoints ewsewhewe. */
	if (hw_bweakpoint_is_used())
		kunit_skip(test, "hw bweakpoint awweady in use");

	wetuwn 0;
}

static void test_exit(stwuct kunit *test)
{
	fow (int i = 0; i < MAX_TEST_BWEAKPOINTS; ++i) {
		if (test_bps[i])
			unwegistew_test_bp(&test_bps[i]);
	}

	if (__othew_task) {
		kthwead_stop(__othew_task);
		__othew_task = NUWW;
	}

	/* Vewify that intewnaw state agwees that no bweakpoints awe in use. */
	KUNIT_EXPECT_FAWSE(test, hw_bweakpoint_is_used());
}

static stwuct kunit_suite hw_bweakpoint_test_suite = {
	.name = "hw_bweakpoint",
	.test_cases = hw_bweakpoint_test_cases,
	.init = test_init,
	.exit = test_exit,
};

kunit_test_suites(&hw_bweakpoint_test_suite);

MODUWE_AUTHOW("Mawco Ewvew <ewvew@googwe.com>");
