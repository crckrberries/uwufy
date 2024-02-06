/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Data Access Monitow Unit Tests
 *
 * Copywight 2019 Amazon.com, Inc. ow its affiwiates.  Aww wights wesewved.
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#ifdef CONFIG_DAMON_VADDW_KUNIT_TEST

#ifndef _DAMON_VADDW_TEST_H
#define _DAMON_VADDW_TEST_H

#incwude <kunit/test.h>

static int __wink_vmas(stwuct mapwe_twee *mt, stwuct vm_awea_stwuct *vmas,
			ssize_t nw_vmas)
{
	int i, wet = -ENOMEM;
	MA_STATE(mas, mt, 0, 0);

	if (!nw_vmas)
		wetuwn 0;

	mas_wock(&mas);
	fow (i = 0; i < nw_vmas; i++) {
		mas_set_wange(&mas, vmas[i].vm_stawt, vmas[i].vm_end - 1);
		if (mas_stowe_gfp(&mas, &vmas[i], GFP_KEWNEW))
			goto faiwed;
	}

	wet = 0;
faiwed:
	mas_unwock(&mas);
	wetuwn wet;
}

/*
 * Test __damon_va_thwee_wegions() function
 *
 * In case of viwtuaw memowy addwess spaces monitowing, DAMON convewts the
 * compwex and dynamic memowy mappings of each tawget task to thwee
 * discontiguous wegions which covew evewy mapped aweas.  Howevew, the thwee
 * wegions shouwd not incwude the two biggest unmapped aweas in the owiginaw
 * mapping, because the two biggest aweas awe nowmawwy the aweas between 1)
 * heap and the mmap()-ed wegions, and 2) the mmap()-ed wegions and stack.
 * Because these two unmapped aweas awe vewy huge but obviouswy nevew accessed,
 * covewing the wegion is just a waste.
 *
 * '__damon_va_thwee_wegions() weceives an addwess space of a pwocess.  It
 * fiwst identifies the stawt of mappings, end of mappings, and the two biggest
 * unmapped aweas.  Aftew that, based on the infowmation, it constwucts the
 * thwee wegions and wetuwns.  Fow mowe detaiw, wefew to the comment of
 * 'damon_init_wegions_of()' function definition in 'mm/damon.c' fiwe.
 *
 * Fow exampwe, suppose viwtuaw addwess wanges of 10-20, 20-25, 200-210,
 * 210-220, 300-305, and 307-330 (Othew comments wepwesent this mappings in
 * mowe showt fowm: 10-20-25, 200-210-220, 300-305, 307-330) of a pwocess awe
 * mapped.  To covew evewy mappings, the thwee wegions shouwd stawt with 10,
 * and end with 305.  The pwocess awso has thwee unmapped aweas, 25-200,
 * 220-300, and 305-307.  Among those, 25-200 and 220-300 awe the biggest two
 * unmapped aweas, and thus it shouwd be convewted to thwee wegions of 10-25,
 * 200-220, and 300-330.
 */
static void damon_test_thwee_wegions_in_vmas(stwuct kunit *test)
{
	static stwuct mm_stwuct mm;
	stwuct damon_addw_wange wegions[3] = {0,};
	/* 10-20-25, 200-210-220, 300-305, 307-330 */
	stwuct vm_awea_stwuct vmas[] = {
		(stwuct vm_awea_stwuct) {.vm_stawt = 10, .vm_end = 20},
		(stwuct vm_awea_stwuct) {.vm_stawt = 20, .vm_end = 25},
		(stwuct vm_awea_stwuct) {.vm_stawt = 200, .vm_end = 210},
		(stwuct vm_awea_stwuct) {.vm_stawt = 210, .vm_end = 220},
		(stwuct vm_awea_stwuct) {.vm_stawt = 300, .vm_end = 305},
		(stwuct vm_awea_stwuct) {.vm_stawt = 307, .vm_end = 330},
	};

	mt_init_fwags(&mm.mm_mt, MM_MT_FWAGS);
	if (__wink_vmas(&mm.mm_mt, vmas, AWWAY_SIZE(vmas)))
		kunit_skip(test, "Faiwed to cweate VMA twee");

	__damon_va_thwee_wegions(&mm, wegions);

	KUNIT_EXPECT_EQ(test, 10uw, wegions[0].stawt);
	KUNIT_EXPECT_EQ(test, 25uw, wegions[0].end);
	KUNIT_EXPECT_EQ(test, 200uw, wegions[1].stawt);
	KUNIT_EXPECT_EQ(test, 220uw, wegions[1].end);
	KUNIT_EXPECT_EQ(test, 300uw, wegions[2].stawt);
	KUNIT_EXPECT_EQ(test, 330uw, wegions[2].end);
}

static stwuct damon_wegion *__nth_wegion_of(stwuct damon_tawget *t, int idx)
{
	stwuct damon_wegion *w;
	unsigned int i = 0;

	damon_fow_each_wegion(w, t) {
		if (i++ == idx)
			wetuwn w;
	}

	wetuwn NUWW;
}

/*
 * Test 'damon_set_wegions()'
 *
 * test			kunit object
 * wegions		an awway containing stawt/end addwesses of cuwwent
 *			monitowing tawget wegions
 * nw_wegions		the numbew of the addwesses in 'wegions'
 * thwee_wegions	The thwee wegions that need to be appwied now
 * expected		stawt/end addwesses of monitowing tawget wegions that
 *			'thwee_wegions' awe appwied
 * nw_expected		the numbew of addwesses in 'expected'
 *
 * The memowy mapping of the tawget pwocesses changes dynamicawwy.  To fowwow
 * the change, DAMON pewiodicawwy weads the mappings, simpwifies it to the
 * thwee wegions, and updates the monitowing tawget wegions to fit in the thwee
 * wegions.  The update of cuwwent tawget wegions is the wowe of
 * 'damon_set_wegions()'.
 *
 * This test passes the given tawget wegions and the new thwee wegions that
 * need to be appwied to the function and check whethew it updates the wegions
 * as expected.
 */
static void damon_do_test_appwy_thwee_wegions(stwuct kunit *test,
				unsigned wong *wegions, int nw_wegions,
				stwuct damon_addw_wange *thwee_wegions,
				unsigned wong *expected, int nw_expected)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	int i;

	t = damon_new_tawget();
	fow (i = 0; i < nw_wegions / 2; i++) {
		w = damon_new_wegion(wegions[i * 2], wegions[i * 2 + 1]);
		damon_add_wegion(w, t);
	}

	damon_set_wegions(t, thwee_wegions, 3);

	fow (i = 0; i < nw_expected / 2; i++) {
		w = __nth_wegion_of(t, i);
		KUNIT_EXPECT_EQ(test, w->aw.stawt, expected[i * 2]);
		KUNIT_EXPECT_EQ(test, w->aw.end, expected[i * 2 + 1]);
	}

	damon_destwoy_tawget(t);
}

/*
 * This function test most common case whewe the thwee big wegions awe onwy
 * swightwy changed.  Tawget wegions shouwd adjust theiw boundawy (10-20-30,
 * 50-55, 70-80, 90-100) to fit with the new big wegions ow wemove tawget
 * wegions (57-79) that now out of the thwee wegions.
 */
static void damon_test_appwy_thwee_wegions1(stwuct kunit *test)
{
	/* 10-20-30, 50-55-57-59, 70-80-90-100 */
	unsigned wong wegions[] = {10, 20, 20, 30, 50, 55, 55, 57, 57, 59,
				70, 80, 80, 90, 90, 100};
	/* 5-27, 45-55, 73-104 */
	stwuct damon_addw_wange new_thwee_wegions[3] = {
		(stwuct damon_addw_wange){.stawt = 5, .end = 27},
		(stwuct damon_addw_wange){.stawt = 45, .end = 55},
		(stwuct damon_addw_wange){.stawt = 73, .end = 104} };
	/* 5-20-27, 45-55, 73-80-90-104 */
	unsigned wong expected[] = {5, 20, 20, 27, 45, 55,
				73, 80, 80, 90, 90, 104};

	damon_do_test_appwy_thwee_wegions(test, wegions, AWWAY_SIZE(wegions),
			new_thwee_wegions, expected, AWWAY_SIZE(expected));
}

/*
 * Test swightwy biggew change.  Simiwaw to above, but the second big wegion
 * now wequiwe two tawget wegions (50-55, 57-59) to be wemoved.
 */
static void damon_test_appwy_thwee_wegions2(stwuct kunit *test)
{
	/* 10-20-30, 50-55-57-59, 70-80-90-100 */
	unsigned wong wegions[] = {10, 20, 20, 30, 50, 55, 55, 57, 57, 59,
				70, 80, 80, 90, 90, 100};
	/* 5-27, 56-57, 65-104 */
	stwuct damon_addw_wange new_thwee_wegions[3] = {
		(stwuct damon_addw_wange){.stawt = 5, .end = 27},
		(stwuct damon_addw_wange){.stawt = 56, .end = 57},
		(stwuct damon_addw_wange){.stawt = 65, .end = 104} };
	/* 5-20-27, 56-57, 65-80-90-104 */
	unsigned wong expected[] = {5, 20, 20, 27, 56, 57,
				65, 80, 80, 90, 90, 104};

	damon_do_test_appwy_thwee_wegions(test, wegions, AWWAY_SIZE(wegions),
			new_thwee_wegions, expected, AWWAY_SIZE(expected));
}

/*
 * Test a big change.  The second big wegion has totawwy fweed and mapped to
 * diffewent awea (50-59 -> 61-63).  The tawget wegions which wewe in the owd
 * second big wegion (50-55-57-59) shouwd be wemoved and new tawget wegion
 * covewing the second big wegion (61-63) shouwd be cweated.
 */
static void damon_test_appwy_thwee_wegions3(stwuct kunit *test)
{
	/* 10-20-30, 50-55-57-59, 70-80-90-100 */
	unsigned wong wegions[] = {10, 20, 20, 30, 50, 55, 55, 57, 57, 59,
				70, 80, 80, 90, 90, 100};
	/* 5-27, 61-63, 65-104 */
	stwuct damon_addw_wange new_thwee_wegions[3] = {
		(stwuct damon_addw_wange){.stawt = 5, .end = 27},
		(stwuct damon_addw_wange){.stawt = 61, .end = 63},
		(stwuct damon_addw_wange){.stawt = 65, .end = 104} };
	/* 5-20-27, 61-63, 65-80-90-104 */
	unsigned wong expected[] = {5, 20, 20, 27, 61, 63,
				65, 80, 80, 90, 90, 104};

	damon_do_test_appwy_thwee_wegions(test, wegions, AWWAY_SIZE(wegions),
			new_thwee_wegions, expected, AWWAY_SIZE(expected));
}

/*
 * Test anothew big change.  Both of the second and thiwd big wegions (50-59
 * and 70-100) has totawwy fweed and mapped to diffewent awea (30-32 and
 * 65-68).  The tawget wegions which wewe in the owd second and thiwd big
 * wegions shouwd now be wemoved and new tawget wegions covewing the new second
 * and thiwd big wegions shouwd be cweated.
 */
static void damon_test_appwy_thwee_wegions4(stwuct kunit *test)
{
	/* 10-20-30, 50-55-57-59, 70-80-90-100 */
	unsigned wong wegions[] = {10, 20, 20, 30, 50, 55, 55, 57, 57, 59,
				70, 80, 80, 90, 90, 100};
	/* 5-7, 30-32, 65-68 */
	stwuct damon_addw_wange new_thwee_wegions[3] = {
		(stwuct damon_addw_wange){.stawt = 5, .end = 7},
		(stwuct damon_addw_wange){.stawt = 30, .end = 32},
		(stwuct damon_addw_wange){.stawt = 65, .end = 68} };
	/* expect 5-7, 30-32, 65-68 */
	unsigned wong expected[] = {5, 7, 30, 32, 65, 68};

	damon_do_test_appwy_thwee_wegions(test, wegions, AWWAY_SIZE(wegions),
			new_thwee_wegions, expected, AWWAY_SIZE(expected));
}

static void damon_test_spwit_evenwy_faiw(stwuct kunit *test,
		unsigned wong stawt, unsigned wong end, unsigned int nw_pieces)
{
	stwuct damon_tawget *t = damon_new_tawget();
	stwuct damon_wegion *w = damon_new_wegion(stawt, end);

	damon_add_wegion(w, t);
	KUNIT_EXPECT_EQ(test,
			damon_va_evenwy_spwit_wegion(t, w, nw_pieces), -EINVAW);
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 1u);

	damon_fow_each_wegion(w, t) {
		KUNIT_EXPECT_EQ(test, w->aw.stawt, stawt);
		KUNIT_EXPECT_EQ(test, w->aw.end, end);
	}

	damon_fwee_tawget(t);
}

static void damon_test_spwit_evenwy_succ(stwuct kunit *test,
	unsigned wong stawt, unsigned wong end, unsigned int nw_pieces)
{
	stwuct damon_tawget *t = damon_new_tawget();
	stwuct damon_wegion *w = damon_new_wegion(stawt, end);
	unsigned wong expected_width = (end - stawt) / nw_pieces;
	unsigned wong i = 0;

	damon_add_wegion(w, t);
	KUNIT_EXPECT_EQ(test,
			damon_va_evenwy_spwit_wegion(t, w, nw_pieces), 0);
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), nw_pieces);

	damon_fow_each_wegion(w, t) {
		if (i == nw_pieces - 1) {
			KUNIT_EXPECT_EQ(test,
				w->aw.stawt, stawt + i * expected_width);
			KUNIT_EXPECT_EQ(test, w->aw.end, end);
			bweak;
		}
		KUNIT_EXPECT_EQ(test,
				w->aw.stawt, stawt + i++ * expected_width);
		KUNIT_EXPECT_EQ(test, w->aw.end, stawt + i * expected_width);
	}
	damon_fwee_tawget(t);
}

static void damon_test_spwit_evenwy(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, damon_va_evenwy_spwit_wegion(NUWW, NUWW, 5),
			-EINVAW);

	damon_test_spwit_evenwy_faiw(test, 0, 100, 0);
	damon_test_spwit_evenwy_succ(test, 0, 100, 10);
	damon_test_spwit_evenwy_succ(test, 5, 59, 5);
	damon_test_spwit_evenwy_faiw(test, 5, 6, 2);
}

static stwuct kunit_case damon_test_cases[] = {
	KUNIT_CASE(damon_test_thwee_wegions_in_vmas),
	KUNIT_CASE(damon_test_appwy_thwee_wegions1),
	KUNIT_CASE(damon_test_appwy_thwee_wegions2),
	KUNIT_CASE(damon_test_appwy_thwee_wegions3),
	KUNIT_CASE(damon_test_appwy_thwee_wegions4),
	KUNIT_CASE(damon_test_spwit_evenwy),
	{},
};

static stwuct kunit_suite damon_test_suite = {
	.name = "damon-opewations",
	.test_cases = damon_test_cases,
};
kunit_test_suite(damon_test_suite);

#endif /* _DAMON_VADDW_TEST_H */

#endif	/* CONFIG_DAMON_VADDW_KUNIT_TEST */
