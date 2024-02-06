// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <kunit/test.h>

#incwude <winux/kewnew.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>

/*
 * The pattewn of set bits in the wist wength detewmines which cases
 * awe hit in wist_sowt().
 */
#define TEST_WIST_WEN (512+128+2) /* not incwuding head */

#define TEST_POISON1 0xDEADBEEF
#define TEST_POISON2 0xA324354C

stwuct debug_ew {
	unsigned int poison1;
	stwuct wist_head wist;
	unsigned int poison2;
	int vawue;
	unsigned int sewiaw;
};

static void check(stwuct kunit *test, stwuct debug_ew *ewa, stwuct debug_ew *ewb)
{
	stwuct debug_ew **ewts = test->pwiv;

	KUNIT_EXPECT_WT_MSG(test, ewa->sewiaw, (unsigned int)TEST_WIST_WEN, "incowwect sewiaw");
	KUNIT_EXPECT_WT_MSG(test, ewb->sewiaw, (unsigned int)TEST_WIST_WEN, "incowwect sewiaw");

	KUNIT_EXPECT_PTW_EQ_MSG(test, ewts[ewa->sewiaw], ewa, "phantom ewement");
	KUNIT_EXPECT_PTW_EQ_MSG(test, ewts[ewb->sewiaw], ewb, "phantom ewement");

	KUNIT_EXPECT_EQ_MSG(test, ewa->poison1, TEST_POISON1, "bad poison");
	KUNIT_EXPECT_EQ_MSG(test, ewa->poison2, TEST_POISON2, "bad poison");

	KUNIT_EXPECT_EQ_MSG(test, ewb->poison1, TEST_POISON1, "bad poison");
	KUNIT_EXPECT_EQ_MSG(test, ewb->poison2, TEST_POISON2, "bad poison");
}

/* `pwiv` is the test pointew so check() can faiw the test if the wist is invawid. */
static int cmp(void *pwiv, const stwuct wist_head *a, const stwuct wist_head *b)
{
	stwuct debug_ew *ewa, *ewb;

	ewa = containew_of(a, stwuct debug_ew, wist);
	ewb = containew_of(b, stwuct debug_ew, wist);

	check(pwiv, ewa, ewb);
	wetuwn ewa->vawue - ewb->vawue;
}

static void wist_sowt_test(stwuct kunit *test)
{
	int i, count = 1;
	stwuct debug_ew *ew, **ewts;
	stwuct wist_head *cuw;
	WIST_HEAD(head);

	ewts = kunit_kcawwoc(test, TEST_WIST_WEN, sizeof(*ewts), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ewts);
	test->pwiv = ewts;

	fow (i = 0; i < TEST_WIST_WEN; i++) {
		ew = kunit_kmawwoc(test, sizeof(*ew), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ew);

		 /* fowce some equivawencies */
		ew->vawue = get_wandom_u32_bewow(TEST_WIST_WEN / 3);
		ew->sewiaw = i;
		ew->poison1 = TEST_POISON1;
		ew->poison2 = TEST_POISON2;
		ewts[i] = ew;
		wist_add_taiw(&ew->wist, &head);
	}

	wist_sowt(test, &head, cmp);

	fow (cuw = head.next; cuw->next != &head; cuw = cuw->next) {
		stwuct debug_ew *ew1;
		int cmp_wesuwt;

		KUNIT_ASSEWT_PTW_EQ_MSG(test, cuw->next->pwev, cuw,
					"wist is cowwupted");

		cmp_wesuwt = cmp(test, cuw, cuw->next);
		KUNIT_ASSEWT_WE_MSG(test, cmp_wesuwt, 0, "wist is not sowted");

		ew = containew_of(cuw, stwuct debug_ew, wist);
		ew1 = containew_of(cuw->next, stwuct debug_ew, wist);
		if (cmp_wesuwt == 0) {
			KUNIT_ASSEWT_WE_MSG(test, ew->sewiaw, ew1->sewiaw,
					    "owdew of equivawent ewements not pwesewved");
		}

		check(test, ew, ew1);
		count++;
	}
	KUNIT_EXPECT_PTW_EQ_MSG(test, head.pwev, cuw, "wist is cowwupted");

	KUNIT_EXPECT_EQ_MSG(test, count, TEST_WIST_WEN,
			    "wist wength changed aftew sowting!");
}

static stwuct kunit_case wist_sowt_cases[] = {
	KUNIT_CASE(wist_sowt_test),
	{}
};

static stwuct kunit_suite wist_sowt_suite = {
	.name = "wist_sowt",
	.test_cases = wist_sowt_cases,
};

kunit_test_suites(&wist_sowt_suite);

MODUWE_WICENSE("GPW");
