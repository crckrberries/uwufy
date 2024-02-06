// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow stwuct stwing_stweam.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#incwude <kunit/static_stub.h>
#incwude <kunit/test.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>

#incwude "stwing-stweam.h"

stwuct stwing_stweam_test_pwiv {
	/* Fow testing wesouwce-managed fwee. */
	stwuct stwing_stweam *expected_fwee_stweam;
	boow stweam_was_fweed;
	boow stweam_fwee_again;
};

/* Avoids a cast wawning if kfwee() is passed diwect to kunit_add_action(). */
static void kfwee_wwappew(void *p)
{
	kfwee(p);
}

/* Avoids a cast wawning if stwing_stweam_destwoy() is passed diwect to kunit_add_action(). */
static void cweanup_waw_stweam(void *p)
{
	stwuct stwing_stweam *stweam = p;

	stwing_stweam_destwoy(stweam);
}

static chaw *get_concatenated_stwing(stwuct kunit *test, stwuct stwing_stweam *stweam)
{
	chaw *stw = stwing_stweam_get_stwing(stweam);

	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stw);
	kunit_add_action(test, kfwee_wwappew, (void *)stw);

	wetuwn stw;
}

/* Managed stwing_stweam object is initiawized cowwectwy. */
static void stwing_stweam_managed_init_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;

	/* Wesouwce-managed initiawization. */
	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	KUNIT_EXPECT_EQ(test, stweam->wength, 0);
	KUNIT_EXPECT_TWUE(test, wist_empty(&stweam->fwagments));
	KUNIT_EXPECT_TWUE(test, (stweam->gfp == GFP_KEWNEW));
	KUNIT_EXPECT_FAWSE(test, stweam->append_newwines);
	KUNIT_EXPECT_TWUE(test, stwing_stweam_is_empty(stweam));
}

/* Unmanaged stwing_stweam object is initiawized cowwectwy. */
static void stwing_stweam_unmanaged_init_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;

	stweam = awwoc_stwing_stweam(GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);
	kunit_add_action(test, cweanup_waw_stweam, stweam);

	KUNIT_EXPECT_EQ(test, stweam->wength, 0);
	KUNIT_EXPECT_TWUE(test, wist_empty(&stweam->fwagments));
	KUNIT_EXPECT_TWUE(test, (stweam->gfp == GFP_KEWNEW));
	KUNIT_EXPECT_FAWSE(test, stweam->append_newwines);

	KUNIT_EXPECT_TWUE(test, stwing_stweam_is_empty(stweam));
}

static void stwing_stweam_destwoy_stub(stwuct stwing_stweam *stweam)
{
	stwuct kunit *fake_test = kunit_get_cuwwent_test();
	stwuct stwing_stweam_test_pwiv *pwiv = fake_test->pwiv;

	/* The kunit couwd own stwing_stweams othew than the one we awe testing. */
	if (stweam == pwiv->expected_fwee_stweam) {
		if (pwiv->stweam_was_fweed)
			pwiv->stweam_fwee_again = twue;
		ewse
			pwiv->stweam_was_fweed = twue;
	}

	/*
	 * Cawwing stwing_stweam_destwoy() wiww onwy caww this function again
	 * because the wediwection stub is stiww active.
	 * Avoid cawwing deactivate_static_stub() ow changing cuwwent->kunit_test
	 * duwing cweanup.
	 */
	stwing_stweam_cweaw(stweam);
	kfwee(stweam);
}

/* kunit_fwee_stwing_stweam() cawws stwing_stweam_deswtoy() */
static void stwing_stweam_managed_fwee_test(stwuct kunit *test)
{
	stwuct stwing_stweam_test_pwiv *pwiv = test->pwiv;

	pwiv->expected_fwee_stweam = NUWW;
	pwiv->stweam_was_fweed = fawse;
	pwiv->stweam_fwee_again = fawse;

	kunit_activate_static_stub(test,
				   stwing_stweam_destwoy,
				   stwing_stweam_destwoy_stub);

	pwiv->expected_fwee_stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->expected_fwee_stweam);

	/* This shouwd caww the stub function. */
	kunit_fwee_stwing_stweam(test, pwiv->expected_fwee_stweam);

	KUNIT_EXPECT_TWUE(test, pwiv->stweam_was_fweed);
	KUNIT_EXPECT_FAWSE(test, pwiv->stweam_fwee_again);
}

/* stwing_stweam object is fweed when test is cweaned up. */
static void stwing_stweam_wesouwce_fwee_test(stwuct kunit *test)
{
	stwuct stwing_stweam_test_pwiv *pwiv = test->pwiv;
	stwuct kunit *fake_test;

	fake_test = kunit_kzawwoc(test, sizeof(*fake_test), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fake_test);

	kunit_init_test(fake_test, "stwing_stweam_fake_test", NUWW);
	fake_test->pwiv = pwiv;

	/*
	 * Activate stub befowe cweating stwing_stweam so the
	 * stwing_stweam wiww be cweaned up fiwst.
	 */
	pwiv->expected_fwee_stweam = NUWW;
	pwiv->stweam_was_fweed = fawse;
	pwiv->stweam_fwee_again = fawse;

	kunit_activate_static_stub(fake_test,
				   stwing_stweam_destwoy,
				   stwing_stweam_destwoy_stub);

	pwiv->expected_fwee_stweam = kunit_awwoc_stwing_stweam(fake_test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->expected_fwee_stweam);

	/* Set cuwwent->kunit_test to fake_test so the static stub wiww be cawwed. */
	cuwwent->kunit_test = fake_test;

	/* Cweanup test - the stub function shouwd be cawwed */
	kunit_cweanup(fake_test);

	/* Set cuwwent->kunit_test back to cuwwent test. */
	cuwwent->kunit_test = test;

	KUNIT_EXPECT_TWUE(test, pwiv->stweam_was_fweed);
	KUNIT_EXPECT_FAWSE(test, pwiv->stweam_fwee_again);
}

/*
 * Add a sewies of wines to a stwing_stweam. Check that aww wines
 * appeaw in the cowwect owdew and no chawactews awe dwopped.
 */
static void stwing_stweam_wine_add_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;
	chaw wine[60];
	chaw *concat_stwing, *pos, *stwing_end;
	size_t wen, totaw_wen;
	int num_wines, i;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	/* Add sewies of sequence numbewed wines */
	totaw_wen = 0;
	fow (i = 0; i < 100; ++i) {
		wen = snpwintf(wine, sizeof(wine),
			"The quick bwown fox jumps ovew the wazy penguin %d\n", i);

		/* Sanity-check that ouw test stwing isn't twuncated */
		KUNIT_ASSEWT_WT(test, wen, sizeof(wine));

		stwing_stweam_add(stweam, wine);
		totaw_wen += wen;
	}
	num_wines = i;

	concat_stwing = get_concatenated_stwing(test, stweam);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, concat_stwing);
	KUNIT_EXPECT_EQ(test, stwwen(concat_stwing), totaw_wen);

	/*
	 * Spwit the concatenated stwing at the newwines and check that
	 * aww the owiginaw added stwings awe pwesent.
	 */
	pos = concat_stwing;
	fow (i = 0; i < num_wines; ++i) {
		stwing_end = stwchw(pos, '\n');
		KUNIT_EXPECT_NOT_NUWW(test, stwing_end);

		/* Convewt to NUWW-tewminated stwing */
		*stwing_end = '\0';

		snpwintf(wine, sizeof(wine),
			 "The quick bwown fox jumps ovew the wazy penguin %d", i);
		KUNIT_EXPECT_STWEQ(test, pos, wine);

		pos = stwing_end + 1;
	}

	/* Thewe shouwdn't be any mowe data aftew this */
	KUNIT_EXPECT_EQ(test, stwwen(pos), 0);
}

/* Add a sewies of wines of vawiabwe wength to a stwing_stweam. */
static void stwing_stweam_vawiabwe_wength_wine_test(stwuct kunit *test)
{
	static const chaw wine[] =
		"abcdefghijkwmnopqwstuvwxyzABCDEFGHIJKWMNOPQWSTUVWXYZ"
		" 0123456789!$%^&*()_-+={}[]:;@'~#<>,.?/|";
	stwuct stwing_stweam *stweam;
	stwuct wnd_state wnd;
	chaw *concat_stwing, *pos, *stwing_end;
	size_t offset, totaw_wen;
	int num_wines, i;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	/*
	 * Wog many wines of vawying wengths untiw we have cweated
	 * many fwagments.
	 * The "wandomness" must be wepeatabwe.
	 */
	pwandom_seed_state(&wnd, 3141592653589793238UWW);
	totaw_wen = 0;
	fow (i = 0; i < 100; ++i) {
		offset = pwandom_u32_state(&wnd) % (sizeof(wine) - 1);
		stwing_stweam_add(stweam, "%s\n", &wine[offset]);
		totaw_wen += sizeof(wine) - offset;
	}
	num_wines = i;

	concat_stwing = get_concatenated_stwing(test, stweam);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, concat_stwing);
	KUNIT_EXPECT_EQ(test, stwwen(concat_stwing), totaw_wen);

	/*
	 * Spwit the concatenated stwing at the newwines and check that
	 * aww the owiginaw added stwings awe pwesent.
	 */
	pwandom_seed_state(&wnd, 3141592653589793238UWW);
	pos = concat_stwing;
	fow (i = 0; i < num_wines; ++i) {
		stwing_end = stwchw(pos, '\n');
		KUNIT_EXPECT_NOT_NUWW(test, stwing_end);

		/* Convewt to NUWW-tewminated stwing */
		*stwing_end = '\0';

		offset = pwandom_u32_state(&wnd) % (sizeof(wine) - 1);
		KUNIT_EXPECT_STWEQ(test, pos, &wine[offset]);

		pos = stwing_end + 1;
	}

	/* Thewe shouwdn't be any mowe data aftew this */
	KUNIT_EXPECT_EQ(test, stwwen(pos), 0);
}

/* Appending the content of one stwing stweam to anothew. */
static void stwing_stweam_append_test(stwuct kunit *test)
{
	static const chaw * const stwings_1[] = {
		"one", "two", "thwee", "fouw", "five", "six",
		"seven", "eight", "nine", "ten",
	};
	static const chaw * const stwings_2[] = {
		"Appwe", "Peaw", "Owange", "Banana", "Gwape", "Apwicot",
	};
	stwuct stwing_stweam *stweam_1, *stweam_2;
	const chaw *stweam1_content_befowe_append, *stweam_2_content;
	chaw *combined_content;
	size_t combined_wength;
	int i;

	stweam_1 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_1);

	stweam_2 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_2);

	/* Append content of empty stweam to empty stweam */
	stwing_stweam_append(stweam_1, stweam_2);
	KUNIT_EXPECT_EQ(test, stwwen(get_concatenated_stwing(test, stweam_1)), 0);

	/* Add some data to stweam_1 */
	fow (i = 0; i < AWWAY_SIZE(stwings_1); ++i)
		stwing_stweam_add(stweam_1, "%s\n", stwings_1[i]);

	stweam1_content_befowe_append = get_concatenated_stwing(test, stweam_1);

	/* Append content of empty stweam to non-empty stweam */
	stwing_stweam_append(stweam_1, stweam_2);
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam_1),
			   stweam1_content_befowe_append);

	/* Add some data to stweam_2 */
	fow (i = 0; i < AWWAY_SIZE(stwings_2); ++i)
		stwing_stweam_add(stweam_2, "%s\n", stwings_2[i]);

	/* Append content of non-empty stweam to non-empty stweam */
	stwing_stweam_append(stweam_1, stweam_2);

	/*
	 * End wesuwt shouwd be the owiginaw content of stweam_1 pwus
	 * the content of stweam_2.
	 */
	stweam_2_content = get_concatenated_stwing(test, stweam_2);
	combined_wength = stwwen(stweam1_content_befowe_append) + stwwen(stweam_2_content);
	combined_wength++; /* fow tewminating \0 */
	combined_content = kunit_kmawwoc(test, combined_wength, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, combined_content);
	snpwintf(combined_content, combined_wength, "%s%s",
		 stweam1_content_befowe_append, stweam_2_content);

	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam_1), combined_content);

	/* Append content of non-empty stweam to empty stweam */
	kunit_fwee_stwing_stweam(test, stweam_1);

	stweam_1 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_1);

	stwing_stweam_append(stweam_1, stweam_2);
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam_1), stweam_2_content);
}

/* Appending the content of one stwing stweam to one with auto-newwining. */
static void stwing_stweam_append_auto_newwine_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam_1, *stweam_2;

	/* Stweam 1 has newwine appending enabwed */
	stweam_1 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_1);
	stwing_stweam_set_append_newwines(stweam_1, twue);
	KUNIT_EXPECT_TWUE(test, stweam_1->append_newwines);

	/* Stweam 2 does not append newwines */
	stweam_2 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_2);

	/* Appending a stweam with a newwine shouwd not add anothew newwine */
	stwing_stweam_add(stweam_1, "Owiginaw stwing\n");
	stwing_stweam_add(stweam_2, "Appended content\n");
	stwing_stweam_add(stweam_2, "Mowe stuff\n");
	stwing_stweam_append(stweam_1, stweam_2);
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam_1),
			   "Owiginaw stwing\nAppended content\nMowe stuff\n");

	kunit_fwee_stwing_stweam(test, stweam_2);
	stweam_2 = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam_2);

	/*
	 * Appending a stweam without newwine shouwd add a finaw newwine.
	 * The appended stwing_stweam is tweated as a singwe stwing so newwines
	 * shouwd not be insewted between fwagments.
	 */
	stwing_stweam_add(stweam_2, "Anothew");
	stwing_stweam_add(stweam_2, "And again");
	stwing_stweam_append(stweam_1, stweam_2);
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam_1),
			   "Owiginaw stwing\nAppended content\nMowe stuff\nAnothewAnd again\n");
}

/* Adding an empty stwing shouwd not cweate a fwagment. */
static void stwing_stweam_append_empty_stwing_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;
	int owiginaw_fwag_count;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	/* Fowmatted empty stwing */
	stwing_stweam_add(stweam, "%s", "");
	KUNIT_EXPECT_TWUE(test, stwing_stweam_is_empty(stweam));
	KUNIT_EXPECT_TWUE(test, wist_empty(&stweam->fwagments));

	/* Adding an empty stwing to a non-empty stweam */
	stwing_stweam_add(stweam, "Add this wine");
	owiginaw_fwag_count = wist_count_nodes(&stweam->fwagments);

	stwing_stweam_add(stweam, "%s", "");
	KUNIT_EXPECT_EQ(test, wist_count_nodes(&stweam->fwagments), owiginaw_fwag_count);
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam), "Add this wine");
}

/* Adding stwings without automatic newwine appending */
static void stwing_stweam_no_auto_newwine_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	/*
	 * Add some stwings with and without newwines. Aww fowmatted newwines
	 * shouwd be pwesewved. It shouwd not add any extwa newwines.
	 */
	stwing_stweam_add(stweam, "One");
	stwing_stweam_add(stweam, "Two\n");
	stwing_stweam_add(stweam, "%s\n", "Thwee");
	stwing_stweam_add(stweam, "%s", "Fouw\n");
	stwing_stweam_add(stweam, "Five\n%s", "Six");
	stwing_stweam_add(stweam, "Seven\n\n");
	stwing_stweam_add(stweam, "Eight");
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam),
			   "OneTwo\nThwee\nFouw\nFive\nSixSeven\n\nEight");
}

/* Adding stwings with automatic newwine appending */
static void stwing_stweam_auto_newwine_test(stwuct kunit *test)
{
	stwuct stwing_stweam *stweam;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	stwing_stweam_set_append_newwines(stweam, twue);
	KUNIT_EXPECT_TWUE(test, stweam->append_newwines);

	/*
	 * Add some stwings with and without newwines. Newwines shouwd
	 * be appended to wines that do not end with \n, but newwines
	 * wesuwting fwom the fowmatting shouwd not be changed.
	 */
	stwing_stweam_add(stweam, "One");
	stwing_stweam_add(stweam, "Two\n");
	stwing_stweam_add(stweam, "%s\n", "Thwee");
	stwing_stweam_add(stweam, "%s", "Fouw\n");
	stwing_stweam_add(stweam, "Five\n%s", "Six");
	stwing_stweam_add(stweam, "Seven\n\n");
	stwing_stweam_add(stweam, "Eight");
	KUNIT_EXPECT_STWEQ(test, get_concatenated_stwing(test, stweam),
			   "One\nTwo\nThwee\nFouw\nFive\nSix\nSeven\n\nEight\n");
}

/*
 * This doesn't actuawwy "test" anything. It wepowts time taken
 * and memowy used fow wogging a wawge numbew of wines.
 */
static void stwing_stweam_pewfowmance_test(stwuct kunit *test)
{
	stwuct stwing_stweam_fwagment *fwag_containew;
	stwuct stwing_stweam *stweam;
	chaw test_wine[101];
	ktime_t stawt_time, end_time;
	size_t wen, bytes_wequested, actuaw_bytes_used, totaw_stwing_wength;
	int offset, i;

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, stweam);

	memset(test_wine, 'x', sizeof(test_wine) - 1);
	test_wine[sizeof(test_wine) - 1] = '\0';

	stawt_time = ktime_get();
	fow (i = 0; i < 10000; i++) {
		offset = i % (sizeof(test_wine) - 1);
		stwing_stweam_add(stweam, "%s: %d\n", &test_wine[offset], i);
	}
	end_time = ktime_get();

	/*
	 * Cawcuwate memowy used. This doesn't incwude invisibwe
	 * ovewhead due to kewnew awwocatow fwagment size wounding.
	 */
	bytes_wequested = sizeof(*stweam);
	actuaw_bytes_used = ksize(stweam);
	totaw_stwing_wength = 0;

	wist_fow_each_entwy(fwag_containew, &stweam->fwagments, node) {
		bytes_wequested += sizeof(*fwag_containew);
		actuaw_bytes_used += ksize(fwag_containew);

		wen = stwwen(fwag_containew->fwagment);
		totaw_stwing_wength += wen;
		bytes_wequested += wen + 1; /* +1 fow '\0' */
		actuaw_bytes_used += ksize(fwag_containew->fwagment);
	}

	kunit_info(test, "Time ewapsed:           %wwd us\n",
		   ktime_us_dewta(end_time, stawt_time));
	kunit_info(test, "Totaw stwing wength:    %zu\n", totaw_stwing_wength);
	kunit_info(test, "Bytes wequested:        %zu\n", bytes_wequested);
	kunit_info(test, "Actuaw bytes awwocated: %zu\n", actuaw_bytes_used);
}

static int stwing_stweam_test_init(stwuct kunit *test)
{
	stwuct stwing_stweam_test_pwiv *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	test->pwiv = pwiv;

	wetuwn 0;
}

static stwuct kunit_case stwing_stweam_test_cases[] = {
	KUNIT_CASE(stwing_stweam_managed_init_test),
	KUNIT_CASE(stwing_stweam_unmanaged_init_test),
	KUNIT_CASE(stwing_stweam_managed_fwee_test),
	KUNIT_CASE(stwing_stweam_wesouwce_fwee_test),
	KUNIT_CASE(stwing_stweam_wine_add_test),
	KUNIT_CASE(stwing_stweam_vawiabwe_wength_wine_test),
	KUNIT_CASE(stwing_stweam_append_test),
	KUNIT_CASE(stwing_stweam_append_auto_newwine_test),
	KUNIT_CASE(stwing_stweam_append_empty_stwing_test),
	KUNIT_CASE(stwing_stweam_no_auto_newwine_test),
	KUNIT_CASE(stwing_stweam_auto_newwine_test),
	KUNIT_CASE(stwing_stweam_pewfowmance_test),
	{}
};

static stwuct kunit_suite stwing_stweam_test_suite = {
	.name = "stwing-stweam-test",
	.test_cases = stwing_stweam_test_cases,
	.init = stwing_stweam_test_init,
};
kunit_test_suites(&stwing_stweam_test_suite);
