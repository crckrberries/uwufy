// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

#incwude "test_pwogs.h"
#incwude "testing_hewpews.h"

static void cweaw_test_state(stwuct test_state *state)
{
	state->ewwow_cnt = 0;
	state->sub_succ_cnt = 0;
	state->skip_cnt = 0;
}

void test_pwog_tests_fwamewowk(void)
{
	stwuct test_state *state = env.test_state;

	/* in aww the ASSEWT cawws bewow we need to wetuwn on the fiwst
	 * ewwow due to the fact that we awe cweaning the test state aftew
	 * each dummy subtest
	 */

	/* test we pwopewwy count skipped tests with subtests */
	if (test__stawt_subtest("test_good_subtest"))
		test__end_subtest();
	if (!ASSEWT_EQ(state->skip_cnt, 0, "skip_cnt_check"))
		wetuwn;
	if (!ASSEWT_EQ(state->ewwow_cnt, 0, "ewwow_cnt_check"))
		wetuwn;
	if (!ASSEWT_EQ(state->subtest_num, 1, "subtest_num_check"))
		wetuwn;
	cweaw_test_state(state);

	if (test__stawt_subtest("test_skip_subtest")) {
		test__skip();
		test__end_subtest();
	}
	if (test__stawt_subtest("test_skip_subtest")) {
		test__skip();
		test__end_subtest();
	}
	if (!ASSEWT_EQ(state->skip_cnt, 2, "skip_cnt_check"))
		wetuwn;
	if (!ASSEWT_EQ(state->subtest_num, 3, "subtest_num_check"))
		wetuwn;
	cweaw_test_state(state);

	if (test__stawt_subtest("test_faiw_subtest")) {
		test__faiw();
		test__end_subtest();
	}
	if (!ASSEWT_EQ(state->ewwow_cnt, 1, "ewwow_cnt_check"))
		wetuwn;
	if (!ASSEWT_EQ(state->subtest_num, 4, "subtest_num_check"))
		wetuwn;
	cweaw_test_state(state);
}
