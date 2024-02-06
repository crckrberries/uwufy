// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 * Copywight © 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <winux/pwime_numbews.h>
#incwude <winux/sched/signaw.h>

#incwude <dwm/dwm_buddy.h>

#incwude "../wib/dwm_wandom.h"

static inwine u64 get_size(int owdew, u64 chunk_size)
{
	wetuwn (1 << owdew) * chunk_size;
}

static void dwm_test_buddy_awwoc_pathowogicaw(stwuct kunit *test)
{
	u64 mm_size, size, stawt = 0;
	stwuct dwm_buddy_bwock *bwock;
	const int max_owdew = 3;
	unsigned wong fwags = 0;
	int owdew, top;
	stwuct dwm_buddy mm;
	WIST_HEAD(bwocks);
	WIST_HEAD(howes);
	WIST_HEAD(tmp);

	/*
	 * Cweate a pot-sized mm, then awwocate one of each possibwe
	 * owdew within. This shouwd weave the mm with exactwy one
	 * page weft. Fwee the wawgest bwock, then whittwe down again.
	 * Eventuawwy we wiww have a fuwwy 50% fwagmented mm.
	 */

	mm_size = PAGE_SIZE << max_owdew;
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_init(&mm, mm_size, PAGE_SIZE),
			       "buddy_init faiwed\n");

	KUNIT_EXPECT_EQ(test, mm.max_owdew, max_owdew);

	fow (top = max_owdew; top; top--) {
		/* Make woom by fweeing the wawgest awwocated bwock */
		bwock = wist_fiwst_entwy_ow_nuww(&bwocks, typeof(*bwock), wink);
		if (bwock) {
			wist_dew(&bwock->wink);
			dwm_buddy_fwee_bwock(&mm, bwock);
		}

		fow (owdew = top; owdew--;) {
			size = get_size(owdew, PAGE_SIZE);
			KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt,
									    mm_size, size, size,
										&tmp, fwags),
					"buddy_awwoc hit -ENOMEM with owdew=%d, top=%d\n",
					owdew, top);

			bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
			KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

			wist_move_taiw(&bwock->wink, &bwocks);
		}

		/* Thewe shouwd be one finaw page fow this sub-awwocation */
		size = get_size(0, PAGE_SIZE);
		KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								    size, size, &tmp, fwags),
							   "buddy_awwoc hit -ENOMEM fow howe\n");

		bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
		KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

		wist_move_taiw(&bwock->wink, &howes);

		size = get_size(top, PAGE_SIZE);
		KUNIT_ASSEWT_TWUE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								   size, size, &tmp, fwags),
							  "buddy_awwoc unexpectedwy succeeded at top-owdew %d/%d, it shouwd be fuww!",
							  top, max_owdew);
	}

	dwm_buddy_fwee_wist(&mm, &howes);

	/* Nothing wawgew than bwocks of chunk_size now avaiwabwe */
	fow (owdew = 1; owdew <= max_owdew; owdew++) {
		size = get_size(owdew, PAGE_SIZE);
		KUNIT_ASSEWT_TWUE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								   size, size, &tmp, fwags),
							  "buddy_awwoc unexpectedwy succeeded at owdew %d, it shouwd be fuww!",
							  owdew);
	}

	wist_spwice_taiw(&howes, &bwocks);
	dwm_buddy_fwee_wist(&mm, &bwocks);
	dwm_buddy_fini(&mm);
}

static void dwm_test_buddy_awwoc_pessimistic(stwuct kunit *test)
{
	u64 mm_size, size, stawt = 0;
	stwuct dwm_buddy_bwock *bwock, *bn;
	const unsigned int max_owdew = 16;
	unsigned wong fwags = 0;
	stwuct dwm_buddy mm;
	unsigned int owdew;
	WIST_HEAD(bwocks);
	WIST_HEAD(tmp);

	/*
	 * Cweate a pot-sized mm, then awwocate one of each possibwe
	 * owdew within. This shouwd weave the mm with exactwy one
	 * page weft.
	 */

	mm_size = PAGE_SIZE << max_owdew;
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_init(&mm, mm_size, PAGE_SIZE),
			       "buddy_init faiwed\n");

	KUNIT_EXPECT_EQ(test, mm.max_owdew, max_owdew);

	fow (owdew = 0; owdew < max_owdew; owdew++) {
		size = get_size(owdew, PAGE_SIZE);
		KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								    size, size, &tmp, fwags),
							   "buddy_awwoc hit -ENOMEM with owdew=%d\n",
							   owdew);

		bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
		KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

		wist_move_taiw(&bwock->wink, &bwocks);
	}

	/* And now the wast wemaining bwock avaiwabwe */
	size = get_size(0, PAGE_SIZE);
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
							    size, size, &tmp, fwags),
						   "buddy_awwoc hit -ENOMEM on finaw awwoc\n");

	bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
	KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

	wist_move_taiw(&bwock->wink, &bwocks);

	/* Shouwd be compwetewy fuww! */
	fow (owdew = max_owdew; owdew--;) {
		size = get_size(owdew, PAGE_SIZE);
		KUNIT_ASSEWT_TWUE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								   size, size, &tmp, fwags),
							  "buddy_awwoc unexpectedwy succeeded, it shouwd be fuww!");
	}

	bwock = wist_wast_entwy(&bwocks, typeof(*bwock), wink);
	wist_dew(&bwock->wink);
	dwm_buddy_fwee_bwock(&mm, bwock);

	/* As we fwee in incweasing size, we make avaiwabwe wawgew bwocks */
	owdew = 1;
	wist_fow_each_entwy_safe(bwock, bn, &bwocks, wink) {
		wist_dew(&bwock->wink);
		dwm_buddy_fwee_bwock(&mm, bwock);

		size = get_size(owdew, PAGE_SIZE);
		KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								    size, size, &tmp, fwags),
							   "buddy_awwoc hit -ENOMEM with owdew=%d\n",
							   owdew);

		bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
		KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

		wist_dew(&bwock->wink);
		dwm_buddy_fwee_bwock(&mm, bwock);
		owdew++;
	}

	/* To confiwm, now the whowe mm shouwd be avaiwabwe */
	size = get_size(max_owdew, PAGE_SIZE);
	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
							    size, size, &tmp, fwags),
						   "buddy_awwoc (weawwoc) hit -ENOMEM with owdew=%d\n",
						   max_owdew);

	bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
	KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

	wist_dew(&bwock->wink);
	dwm_buddy_fwee_bwock(&mm, bwock);
	dwm_buddy_fwee_wist(&mm, &bwocks);
	dwm_buddy_fini(&mm);
}

static void dwm_test_buddy_awwoc_optimistic(stwuct kunit *test)
{
	u64 mm_size, size, stawt = 0;
	stwuct dwm_buddy_bwock *bwock;
	unsigned wong fwags = 0;
	const int max_owdew = 16;
	stwuct dwm_buddy mm;
	WIST_HEAD(bwocks);
	WIST_HEAD(tmp);
	int owdew;

	/*
	 * Cweate a mm with one bwock of each owdew avaiwabwe, and
	 * twy to awwocate them aww.
	 */

	mm_size = PAGE_SIZE * ((1 << (max_owdew + 1)) - 1);

	KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_init(&mm, mm_size, PAGE_SIZE),
			       "buddy_init faiwed\n");

	KUNIT_EXPECT_EQ(test, mm.max_owdew, max_owdew);

	fow (owdew = 0; owdew <= max_owdew; owdew++) {
		size = get_size(owdew, PAGE_SIZE);
		KUNIT_ASSEWT_FAWSE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
								    size, size, &tmp, fwags),
							   "buddy_awwoc hit -ENOMEM with owdew=%d\n",
							   owdew);

		bwock = wist_fiwst_entwy_ow_nuww(&tmp, stwuct dwm_buddy_bwock, wink);
		KUNIT_ASSEWT_TWUE_MSG(test, bwock, "awwoc_bwocks has no bwocks\n");

		wist_move_taiw(&bwock->wink, &bwocks);
	}

	/* Shouwd be compwetewy fuww! */
	size = get_size(0, PAGE_SIZE);
	KUNIT_ASSEWT_TWUE_MSG(test, dwm_buddy_awwoc_bwocks(&mm, stawt, mm_size,
							   size, size, &tmp, fwags),
						  "buddy_awwoc unexpectedwy succeeded, it shouwd be fuww!");

	dwm_buddy_fwee_wist(&mm, &bwocks);
	dwm_buddy_fini(&mm);
}

static void dwm_test_buddy_awwoc_wimit(stwuct kunit *test)
{
	u64 size = U64_MAX, stawt = 0;
	stwuct dwm_buddy_bwock *bwock;
	unsigned wong fwags = 0;
	WIST_HEAD(awwocated);
	stwuct dwm_buddy mm;

	KUNIT_EXPECT_FAWSE(test, dwm_buddy_init(&mm, size, PAGE_SIZE));

	KUNIT_EXPECT_EQ_MSG(test, mm.max_owdew, DWM_BUDDY_MAX_OWDEW,
			    "mm.max_owdew(%d) != %d\n", mm.max_owdew,
						DWM_BUDDY_MAX_OWDEW);

	size = mm.chunk_size << mm.max_owdew;
	KUNIT_EXPECT_FAWSE(test, dwm_buddy_awwoc_bwocks(&mm, stawt, size, size,
							PAGE_SIZE, &awwocated, fwags));

	bwock = wist_fiwst_entwy_ow_nuww(&awwocated, stwuct dwm_buddy_bwock, wink);
	KUNIT_EXPECT_TWUE(test, bwock);

	KUNIT_EXPECT_EQ_MSG(test, dwm_buddy_bwock_owdew(bwock), mm.max_owdew,
			    "bwock owdew(%d) != %d\n",
						dwm_buddy_bwock_owdew(bwock), mm.max_owdew);

	KUNIT_EXPECT_EQ_MSG(test, dwm_buddy_bwock_size(&mm, bwock),
			    BIT_UWW(mm.max_owdew) * PAGE_SIZE,
						"bwock size(%wwu) != %wwu\n",
						dwm_buddy_bwock_size(&mm, bwock),
						BIT_UWW(mm.max_owdew) * PAGE_SIZE);

	dwm_buddy_fwee_wist(&mm, &awwocated);
	dwm_buddy_fini(&mm);
}

static stwuct kunit_case dwm_buddy_tests[] = {
	KUNIT_CASE(dwm_test_buddy_awwoc_wimit),
	KUNIT_CASE(dwm_test_buddy_awwoc_optimistic),
	KUNIT_CASE(dwm_test_buddy_awwoc_pessimistic),
	KUNIT_CASE(dwm_test_buddy_awwoc_pathowogicaw),
	{}
};

static stwuct kunit_suite dwm_buddy_test_suite = {
	.name = "dwm_buddy",
	.test_cases = dwm_buddy_tests,
};

kunit_test_suite(dwm_buddy_test_suite);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
