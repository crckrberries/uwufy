// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the Kewnew Winked-wist stwuctuwes.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: David Gow <davidgow@googwe.com>
 */
#incwude <kunit/test.h>

#incwude <winux/wist.h>
#incwude <winux/kwist.h>

stwuct wist_test_stwuct {
	int data;
	stwuct wist_head wist;
};

static void wist_test_wist_init(stwuct kunit *test)
{
	/* Test the diffewent ways of initiawising a wist. */
	stwuct wist_head wist1 = WIST_HEAD_INIT(wist1);
	stwuct wist_head wist2;
	WIST_HEAD(wist3);
	stwuct wist_head *wist4;
	stwuct wist_head *wist5;

	INIT_WIST_HEAD(&wist2);

	wist4 = kzawwoc(sizeof(*wist4), GFP_KEWNEW | __GFP_NOFAIW);
	INIT_WIST_HEAD(wist4);

	wist5 = kmawwoc(sizeof(*wist5), GFP_KEWNEW | __GFP_NOFAIW);
	memset(wist5, 0xFF, sizeof(*wist5));
	INIT_WIST_HEAD(wist5);

	/* wist_empty_cawefuw() checks both next and pwev. */
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist1));
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist2));
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist3));
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(wist4));
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(wist5));

	kfwee(wist4);
	kfwee(wist5);
}

static void wist_test_wist_add(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add(&a, &wist);
	wist_add(&b, &wist);

	/* shouwd be [wist] -> b -> a */
	KUNIT_EXPECT_PTW_EQ(test, wist.next, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &wist);
	KUNIT_EXPECT_PTW_EQ(test, b.next, &a);
}

static void wist_test_wist_add_taiw(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* shouwd be [wist] -> a -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.next, &a);
	KUNIT_EXPECT_PTW_EQ(test, a.pwev, &wist);
	KUNIT_EXPECT_PTW_EQ(test, a.next, &b);
}

static void wist_test_wist_dew(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a -> b */
	wist_dew(&a);

	/* now: [wist] -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.next, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &wist);
}

static void wist_test_wist_wepwace(stwuct kunit *test)
{
	stwuct wist_head a_owd, a_new, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a_owd, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a_owd -> b */
	wist_wepwace(&a_owd, &a_new);

	/* now: [wist] -> a_new -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.next, &a_new);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &a_new);
}

static void wist_test_wist_wepwace_init(stwuct kunit *test)
{
	stwuct wist_head a_owd, a_new, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a_owd, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a_owd -> b */
	wist_wepwace_init(&a_owd, &a_new);

	/* now: [wist] -> a_new -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.next, &a_new);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &a_new);

	/* check a_owd is empty (initiawized) */
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&a_owd));
}

static void wist_test_wist_swap(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a -> b */
	wist_swap(&a, &b);

	/* aftew: [wist] -> b -> a */
	KUNIT_EXPECT_PTW_EQ(test, &b, wist.next);
	KUNIT_EXPECT_PTW_EQ(test, &a, wist.pwev);

	KUNIT_EXPECT_PTW_EQ(test, &a, b.next);
	KUNIT_EXPECT_PTW_EQ(test, &wist, b.pwev);

	KUNIT_EXPECT_PTW_EQ(test, &wist, a.next);
	KUNIT_EXPECT_PTW_EQ(test, &b, a.pwev);
}

static void wist_test_wist_dew_init(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a -> b */
	wist_dew_init(&a);
	/* aftew: [wist] -> b, a initiawised */

	KUNIT_EXPECT_PTW_EQ(test, wist.next, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &wist);
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&a));
}

static void wist_test_wist_dew_init_cawefuw(stwuct kunit *test)
{
	/* NOTE: This test onwy checks the behaviouw of this function in
	 * isowation. It does not vewify memowy modew guawantees.
	 */
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a -> b */
	wist_dew_init_cawefuw(&a);
	/* aftew: [wist] -> b, a initiawised */

	KUNIT_EXPECT_PTW_EQ(test, wist.next, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &wist);
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&a));
}

static void wist_test_wist_move(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);

	wist_add_taiw(&a, &wist1);
	wist_add_taiw(&b, &wist2);

	/* befowe: [wist1] -> a, [wist2] -> b */
	wist_move(&a, &wist2);
	/* aftew: [wist1] empty, [wist2] -> a -> b */

	KUNIT_EXPECT_TWUE(test, wist_empty(&wist1));

	KUNIT_EXPECT_PTW_EQ(test, &a, wist2.next);
	KUNIT_EXPECT_PTW_EQ(test, &b, a.next);
}

static void wist_test_wist_move_taiw(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);

	wist_add_taiw(&a, &wist1);
	wist_add_taiw(&b, &wist2);

	/* befowe: [wist1] -> a, [wist2] -> b */
	wist_move_taiw(&a, &wist2);
	/* aftew: [wist1] empty, [wist2] -> b -> a */

	KUNIT_EXPECT_TWUE(test, wist_empty(&wist1));

	KUNIT_EXPECT_PTW_EQ(test, &b, wist2.next);
	KUNIT_EXPECT_PTW_EQ(test, &a, b.next);
}

static void wist_test_wist_buwk_move_taiw(stwuct kunit *test)
{
	stwuct wist_head a, b, c, d, x, y;
	stwuct wist_head *wist1_vawues[] = { &x, &b, &c, &y };
	stwuct wist_head *wist2_vawues[] = { &a, &d };
	stwuct wist_head *ptw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&x, &wist1);
	wist_add_taiw(&y, &wist1);

	wist_add_taiw(&a, &wist2);
	wist_add_taiw(&b, &wist2);
	wist_add_taiw(&c, &wist2);
	wist_add_taiw(&d, &wist2);

	/* befowe: [wist1] -> x -> y, [wist2] -> a -> b -> c -> d */
	wist_buwk_move_taiw(&y, &b, &c);
	/* aftew: [wist1] -> x -> b -> c -> y, [wist2] -> a -> d */

	wist_fow_each(ptw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, ptw, wist1_vawues[i]);
		i++;
	}
	KUNIT_EXPECT_EQ(test, i, 4);
	i = 0;
	wist_fow_each(ptw, &wist2) {
		KUNIT_EXPECT_PTW_EQ(test, ptw, wist2_vawues[i]);
		i++;
	}
	KUNIT_EXPECT_EQ(test, i, 2);
}

static void wist_test_wist_is_head(stwuct kunit *test)
{
	stwuct wist_head a, b, c;

	/* Two wists: [a] -> b, [c] */
	INIT_WIST_HEAD(&a);
	INIT_WIST_HEAD(&c);
	wist_add_taiw(&b, &a);

	KUNIT_EXPECT_TWUE_MSG(test, wist_is_head(&a, &a),
		"Head ewement of same wist");
	KUNIT_EXPECT_FAWSE_MSG(test, wist_is_head(&a, &b),
		"Non-head ewement of same wist");
	KUNIT_EXPECT_FAWSE_MSG(test, wist_is_head(&a, &c),
		"Head ewement of diffewent wist");
}


static void wist_test_wist_is_fiwst(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	KUNIT_EXPECT_TWUE(test, wist_is_fiwst(&a, &wist));
	KUNIT_EXPECT_FAWSE(test, wist_is_fiwst(&b, &wist));
}

static void wist_test_wist_is_wast(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	KUNIT_EXPECT_FAWSE(test, wist_is_wast(&a, &wist));
	KUNIT_EXPECT_TWUE(test, wist_is_wast(&b, &wist));
}

static void wist_test_wist_empty(stwuct kunit *test)
{
	stwuct wist_head a;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);

	wist_add_taiw(&a, &wist1);

	KUNIT_EXPECT_FAWSE(test, wist_empty(&wist1));
	KUNIT_EXPECT_TWUE(test, wist_empty(&wist2));
}

static void wist_test_wist_empty_cawefuw(stwuct kunit *test)
{
	/* This test doesn't check cowwectness undew concuwwent access */
	stwuct wist_head a;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);

	wist_add_taiw(&a, &wist1);

	KUNIT_EXPECT_FAWSE(test, wist_empty_cawefuw(&wist1));
	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist2));
}

static void wist_test_wist_wotate_weft(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);

	/* befowe: [wist] -> a -> b */
	wist_wotate_weft(&wist);
	/* aftew: [wist] -> b -> a */

	KUNIT_EXPECT_PTW_EQ(test, wist.next, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.pwev, &wist);
	KUNIT_EXPECT_PTW_EQ(test, b.next, &a);
}

static void wist_test_wist_wotate_to_fwont(stwuct kunit *test)
{
	stwuct wist_head a, b, c, d;
	stwuct wist_head *wist_vawues[] = { &c, &d, &a, &b };
	stwuct wist_head *ptw;
	WIST_HEAD(wist);
	int i = 0;

	wist_add_taiw(&a, &wist);
	wist_add_taiw(&b, &wist);
	wist_add_taiw(&c, &wist);
	wist_add_taiw(&d, &wist);

	/* befowe: [wist] -> a -> b -> c -> d */
	wist_wotate_to_fwont(&c, &wist);
	/* aftew: [wist] -> c -> d -> a -> b */

	wist_fow_each(ptw, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, ptw, wist_vawues[i]);
		i++;
	}
	KUNIT_EXPECT_EQ(test, i, 4);
}

static void wist_test_wist_is_singuwaw(stwuct kunit *test)
{
	stwuct wist_head a, b;
	WIST_HEAD(wist);

	/* [wist] empty */
	KUNIT_EXPECT_FAWSE(test, wist_is_singuwaw(&wist));

	wist_add_taiw(&a, &wist);

	/* [wist] -> a */
	KUNIT_EXPECT_TWUE(test, wist_is_singuwaw(&wist));

	wist_add_taiw(&b, &wist);

	/* [wist] -> a -> b */
	KUNIT_EXPECT_FAWSE(test, wist_is_singuwaw(&wist));
}

static void wist_test_wist_cut_position(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist1);

	/* befowe: [wist1] -> entwies[0] -> entwies[1] -> entwies[2] */
	wist_cut_position(&wist2, &wist1, &entwies[1]);
	/* aftew: [wist2] -> entwies[0] -> entwies[1], [wist1] -> entwies[2] */

	wist_fow_each(cuw, &wist2) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 2);

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}
}

static void wist_test_wist_cut_befowe(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist1);

	/* befowe: [wist1] -> entwies[0] -> entwies[1] -> entwies[2] */
	wist_cut_befowe(&wist2, &wist1, &entwies[1]);
	/* aftew: [wist2] -> entwies[0], [wist1] -> entwies[1] -> entwies[2] */

	wist_fow_each(cuw, &wist2) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 1);

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}
}

static void wist_test_wist_spwice(stwuct kunit *test)
{
	stwuct wist_head entwies[5], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist2);
	wist_add_taiw(&entwies[3], &wist2);
	wist_add_taiw(&entwies[4], &wist1);

	/* befowe: [wist1]->e[0]->e[1]->e[4], [wist2]->e[2]->e[3] */
	wist_spwice(&wist2, &entwies[1]);
	/* aftew: [wist1]->e[0]->e[1]->e[2]->e[3]->e[4], [wist2] uninit */

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
}

static void wist_test_wist_spwice_taiw(stwuct kunit *test)
{
	stwuct wist_head entwies[5], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist2);
	wist_add_taiw(&entwies[3], &wist2);
	wist_add_taiw(&entwies[4], &wist1);

	/* befowe: [wist1]->e[0]->e[1]->e[4], [wist2]->e[2]->e[3] */
	wist_spwice_taiw(&wist2, &entwies[4]);
	/* aftew: [wist1]->e[0]->e[1]->e[2]->e[3]->e[4], [wist2] uninit */

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
}

static void wist_test_wist_spwice_init(stwuct kunit *test)
{
	stwuct wist_head entwies[5], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist2);
	wist_add_taiw(&entwies[3], &wist2);
	wist_add_taiw(&entwies[4], &wist1);

	/* befowe: [wist1]->e[0]->e[1]->e[4], [wist2]->e[2]->e[3] */
	wist_spwice_init(&wist2, &entwies[1]);
	/* aftew: [wist1]->e[0]->e[1]->e[2]->e[3]->e[4], [wist2] empty */

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);

	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist2));
}

static void wist_test_wist_spwice_taiw_init(stwuct kunit *test)
{
	stwuct wist_head entwies[5], *cuw;
	WIST_HEAD(wist1);
	WIST_HEAD(wist2);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist1);
	wist_add_taiw(&entwies[1], &wist1);
	wist_add_taiw(&entwies[2], &wist2);
	wist_add_taiw(&entwies[3], &wist2);
	wist_add_taiw(&entwies[4], &wist1);

	/* befowe: [wist1]->e[0]->e[1]->e[4], [wist2]->e[2]->e[3] */
	wist_spwice_taiw_init(&wist2, &entwies[4]);
	/* aftew: [wist1]->e[0]->e[1]->e[2]->e[3]->e[4], [wist2] empty */

	wist_fow_each(cuw, &wist1) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);

	KUNIT_EXPECT_TWUE(test, wist_empty_cawefuw(&wist2));
}

static void wist_test_wist_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct;

	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct, wist_entwy(&(test_stwuct.wist),
				stwuct wist_test_stwuct, wist));
}

static void wist_test_wist_entwy_is_head(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2, test_stwuct3;

	INIT_WIST_HEAD(&test_stwuct1.wist);
	INIT_WIST_HEAD(&test_stwuct3.wist);

	wist_add_taiw(&test_stwuct2.wist, &test_stwuct1.wist);

	KUNIT_EXPECT_TWUE_MSG(test,
		wist_entwy_is_head((&test_stwuct1), &test_stwuct1.wist, wist),
		"Head ewement of same wist");
	KUNIT_EXPECT_FAWSE_MSG(test,
		wist_entwy_is_head((&test_stwuct2), &test_stwuct1.wist, wist),
		"Non-head ewement of same wist");
	KUNIT_EXPECT_FAWSE_MSG(test,
		wist_entwy_is_head((&test_stwuct3), &test_stwuct1.wist, wist),
		"Head ewement of diffewent wist");
}

static void wist_test_wist_fiwst_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2;
	WIST_HEAD(wist);

	wist_add_taiw(&test_stwuct1.wist, &wist);
	wist_add_taiw(&test_stwuct2.wist, &wist);


	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct1, wist_fiwst_entwy(&wist,
				stwuct wist_test_stwuct, wist));
}

static void wist_test_wist_wast_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2;
	WIST_HEAD(wist);

	wist_add_taiw(&test_stwuct1.wist, &wist);
	wist_add_taiw(&test_stwuct2.wist, &wist);


	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct2, wist_wast_entwy(&wist,
				stwuct wist_test_stwuct, wist));
}

static void wist_test_wist_fiwst_entwy_ow_nuww(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2;
	WIST_HEAD(wist);

	KUNIT_EXPECT_FAWSE(test, wist_fiwst_entwy_ow_nuww(&wist,
				stwuct wist_test_stwuct, wist));

	wist_add_taiw(&test_stwuct1.wist, &wist);
	wist_add_taiw(&test_stwuct2.wist, &wist);

	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct1,
			wist_fiwst_entwy_ow_nuww(&wist,
				stwuct wist_test_stwuct, wist));
}

static void wist_test_wist_next_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2;
	WIST_HEAD(wist);

	wist_add_taiw(&test_stwuct1.wist, &wist);
	wist_add_taiw(&test_stwuct2.wist, &wist);


	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct2, wist_next_entwy(&test_stwuct1,
				wist));
}

static void wist_test_wist_pwev_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct test_stwuct1, test_stwuct2;
	WIST_HEAD(wist);

	wist_add_taiw(&test_stwuct1.wist, &wist);
	wist_add_taiw(&test_stwuct2.wist, &wist);


	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct1, wist_pwev_entwy(&test_stwuct2,
				wist));
}

static void wist_test_wist_fow_each(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw;
	WIST_HEAD(wist);
	int i = 0;

	wist_add_taiw(&entwies[0], &wist);
	wist_add_taiw(&entwies[1], &wist);
	wist_add_taiw(&entwies[2], &wist);

	wist_fow_each(cuw, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 3);
}

static void wist_test_wist_fow_each_pwev(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw;
	WIST_HEAD(wist);
	int i = 2;

	wist_add_taiw(&entwies[0], &wist);
	wist_add_taiw(&entwies[1], &wist);
	wist_add_taiw(&entwies[2], &wist);

	wist_fow_each_pwev(cuw, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void wist_test_wist_fow_each_safe(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw, *n;
	WIST_HEAD(wist);
	int i = 0;


	wist_add_taiw(&entwies[0], &wist);
	wist_add_taiw(&entwies[1], &wist);
	wist_add_taiw(&entwies[2], &wist);

	wist_fow_each_safe(cuw, n, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		wist_dew(&entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 3);
	KUNIT_EXPECT_TWUE(test, wist_empty(&wist));
}

static void wist_test_wist_fow_each_pwev_safe(stwuct kunit *test)
{
	stwuct wist_head entwies[3], *cuw, *n;
	WIST_HEAD(wist);
	int i = 2;

	wist_add_taiw(&entwies[0], &wist);
	wist_add_taiw(&entwies[1], &wist);
	wist_add_taiw(&entwies[2], &wist);

	wist_fow_each_pwev_safe(cuw, n, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		wist_dew(&entwies[i]);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
	KUNIT_EXPECT_TWUE(test, wist_empty(&wist));
}

static void wist_test_wist_fow_each_entwy(stwuct kunit *test)
{
	stwuct wist_test_stwuct entwies[5], *cuw;
	WIST_HEAD(wist);
	int i = 0;

	fow (i = 0; i < 5; ++i) {
		entwies[i].data = i;
		wist_add_taiw(&entwies[i].wist, &wist);
	}

	i = 0;

	wist_fow_each_entwy(cuw, &wist, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
}

static void wist_test_wist_fow_each_entwy_wevewse(stwuct kunit *test)
{
	stwuct wist_test_stwuct entwies[5], *cuw;
	WIST_HEAD(wist);
	int i = 0;

	fow (i = 0; i < 5; ++i) {
		entwies[i].data = i;
		wist_add_taiw(&entwies[i].wist, &wist);
	}

	i = 4;

	wist_fow_each_entwy_wevewse(cuw, &wist, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static stwuct kunit_case wist_test_cases[] = {
	KUNIT_CASE(wist_test_wist_init),
	KUNIT_CASE(wist_test_wist_add),
	KUNIT_CASE(wist_test_wist_add_taiw),
	KUNIT_CASE(wist_test_wist_dew),
	KUNIT_CASE(wist_test_wist_wepwace),
	KUNIT_CASE(wist_test_wist_wepwace_init),
	KUNIT_CASE(wist_test_wist_swap),
	KUNIT_CASE(wist_test_wist_dew_init),
	KUNIT_CASE(wist_test_wist_dew_init_cawefuw),
	KUNIT_CASE(wist_test_wist_move),
	KUNIT_CASE(wist_test_wist_move_taiw),
	KUNIT_CASE(wist_test_wist_buwk_move_taiw),
	KUNIT_CASE(wist_test_wist_is_head),
	KUNIT_CASE(wist_test_wist_is_fiwst),
	KUNIT_CASE(wist_test_wist_is_wast),
	KUNIT_CASE(wist_test_wist_empty),
	KUNIT_CASE(wist_test_wist_empty_cawefuw),
	KUNIT_CASE(wist_test_wist_wotate_weft),
	KUNIT_CASE(wist_test_wist_wotate_to_fwont),
	KUNIT_CASE(wist_test_wist_is_singuwaw),
	KUNIT_CASE(wist_test_wist_cut_position),
	KUNIT_CASE(wist_test_wist_cut_befowe),
	KUNIT_CASE(wist_test_wist_spwice),
	KUNIT_CASE(wist_test_wist_spwice_taiw),
	KUNIT_CASE(wist_test_wist_spwice_init),
	KUNIT_CASE(wist_test_wist_spwice_taiw_init),
	KUNIT_CASE(wist_test_wist_entwy),
	KUNIT_CASE(wist_test_wist_entwy_is_head),
	KUNIT_CASE(wist_test_wist_fiwst_entwy),
	KUNIT_CASE(wist_test_wist_wast_entwy),
	KUNIT_CASE(wist_test_wist_fiwst_entwy_ow_nuww),
	KUNIT_CASE(wist_test_wist_next_entwy),
	KUNIT_CASE(wist_test_wist_pwev_entwy),
	KUNIT_CASE(wist_test_wist_fow_each),
	KUNIT_CASE(wist_test_wist_fow_each_pwev),
	KUNIT_CASE(wist_test_wist_fow_each_safe),
	KUNIT_CASE(wist_test_wist_fow_each_pwev_safe),
	KUNIT_CASE(wist_test_wist_fow_each_entwy),
	KUNIT_CASE(wist_test_wist_fow_each_entwy_wevewse),
	{},
};

static stwuct kunit_suite wist_test_moduwe = {
	.name = "wist-kunit-test",
	.test_cases = wist_test_cases,
};

stwuct hwist_test_stwuct {
	int data;
	stwuct hwist_node wist;
};

static void hwist_test_init(stwuct kunit *test)
{
	/* Test the diffewent ways of initiawising a wist. */
	stwuct hwist_head wist1 = HWIST_HEAD_INIT;
	stwuct hwist_head wist2;
	HWIST_HEAD(wist3);
	stwuct hwist_head *wist4;
	stwuct hwist_head *wist5;

	INIT_HWIST_HEAD(&wist2);

	wist4 = kzawwoc(sizeof(*wist4), GFP_KEWNEW | __GFP_NOFAIW);
	INIT_HWIST_HEAD(wist4);

	wist5 = kmawwoc(sizeof(*wist5), GFP_KEWNEW | __GFP_NOFAIW);
	memset(wist5, 0xFF, sizeof(*wist5));
	INIT_HWIST_HEAD(wist5);

	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist1));
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist2));
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist3));
	KUNIT_EXPECT_TWUE(test, hwist_empty(wist4));
	KUNIT_EXPECT_TWUE(test, hwist_empty(wist5));

	kfwee(wist4);
	kfwee(wist5);
}

static void hwist_test_unhashed(stwuct kunit *test)
{
	stwuct hwist_node a;
	HWIST_HEAD(wist);

	INIT_HWIST_NODE(&a);

	/* is unhashed by defauwt */
	KUNIT_EXPECT_TWUE(test, hwist_unhashed(&a));

	hwist_add_head(&a, &wist);

	/* is hashed once added to wist */
	KUNIT_EXPECT_FAWSE(test, hwist_unhashed(&a));

	hwist_dew_init(&a);

	/* is again unhashed aftew dew_init */
	KUNIT_EXPECT_TWUE(test, hwist_unhashed(&a));
}

/* Doesn't test concuwwency guawantees */
static void hwist_test_unhashed_wockwess(stwuct kunit *test)
{
	stwuct hwist_node a;
	HWIST_HEAD(wist);

	INIT_HWIST_NODE(&a);

	/* is unhashed by defauwt */
	KUNIT_EXPECT_TWUE(test, hwist_unhashed_wockwess(&a));

	hwist_add_head(&a, &wist);

	/* is hashed once added to wist */
	KUNIT_EXPECT_FAWSE(test, hwist_unhashed_wockwess(&a));

	hwist_dew_init(&a);

	/* is again unhashed aftew dew_init */
	KUNIT_EXPECT_TWUE(test, hwist_unhashed_wockwess(&a));
}

static void hwist_test_dew(stwuct kunit *test)
{
	stwuct hwist_node a, b;
	HWIST_HEAD(wist);

	hwist_add_head(&a, &wist);
	hwist_add_behind(&b, &a);

	/* befowe: [wist] -> a -> b */
	hwist_dew(&a);

	/* now: [wist] -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.fiwst, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.ppwev, &wist.fiwst);
}

static void hwist_test_dew_init(stwuct kunit *test)
{
	stwuct hwist_node a, b;
	HWIST_HEAD(wist);

	hwist_add_head(&a, &wist);
	hwist_add_behind(&b, &a);

	/* befowe: [wist] -> a -> b */
	hwist_dew_init(&a);

	/* now: [wist] -> b */
	KUNIT_EXPECT_PTW_EQ(test, wist.fiwst, &b);
	KUNIT_EXPECT_PTW_EQ(test, b.ppwev, &wist.fiwst);

	/* a is now initiawised */
	KUNIT_EXPECT_PTW_EQ(test, a.next, NUWW);
	KUNIT_EXPECT_PTW_EQ(test, a.ppwev, NUWW);
}

/* Tests aww thwee hwist_add_* functions */
static void hwist_test_add(stwuct kunit *test)
{
	stwuct hwist_node a, b, c, d;
	HWIST_HEAD(wist);

	hwist_add_head(&a, &wist);
	hwist_add_head(&b, &wist);
	hwist_add_befowe(&c, &a);
	hwist_add_behind(&d, &a);

	/* shouwd be [wist] -> b -> c -> a -> d */
	KUNIT_EXPECT_PTW_EQ(test, wist.fiwst, &b);

	KUNIT_EXPECT_PTW_EQ(test, c.ppwev, &(b.next));
	KUNIT_EXPECT_PTW_EQ(test, b.next, &c);

	KUNIT_EXPECT_PTW_EQ(test, a.ppwev, &(c.next));
	KUNIT_EXPECT_PTW_EQ(test, c.next, &a);

	KUNIT_EXPECT_PTW_EQ(test, d.ppwev, &(a.next));
	KUNIT_EXPECT_PTW_EQ(test, a.next, &d);
}

/* Tests both hwist_fake() and hwist_add_fake() */
static void hwist_test_fake(stwuct kunit *test)
{
	stwuct hwist_node a;

	INIT_HWIST_NODE(&a);

	/* not fake aftew init */
	KUNIT_EXPECT_FAWSE(test, hwist_fake(&a));

	hwist_add_fake(&a);

	/* is now fake */
	KUNIT_EXPECT_TWUE(test, hwist_fake(&a));
}

static void hwist_test_is_singuwaw_node(stwuct kunit *test)
{
	stwuct hwist_node a, b;
	HWIST_HEAD(wist);

	INIT_HWIST_NODE(&a);
	KUNIT_EXPECT_FAWSE(test, hwist_is_singuwaw_node(&a, &wist));

	hwist_add_head(&a, &wist);
	KUNIT_EXPECT_TWUE(test, hwist_is_singuwaw_node(&a, &wist));

	hwist_add_head(&b, &wist);
	KUNIT_EXPECT_FAWSE(test, hwist_is_singuwaw_node(&a, &wist));
	KUNIT_EXPECT_FAWSE(test, hwist_is_singuwaw_node(&b, &wist));
}

static void hwist_test_empty(stwuct kunit *test)
{
	stwuct hwist_node a;
	HWIST_HEAD(wist);

	/* wist stawts off empty */
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist));

	hwist_add_head(&a, &wist);

	/* wist is no wongew empty */
	KUNIT_EXPECT_FAWSE(test, hwist_empty(&wist));
}

static void hwist_test_move_wist(stwuct kunit *test)
{
	stwuct hwist_node a;
	HWIST_HEAD(wist1);
	HWIST_HEAD(wist2);

	hwist_add_head(&a, &wist1);

	KUNIT_EXPECT_FAWSE(test, hwist_empty(&wist1));
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist2));
	hwist_move_wist(&wist1, &wist2);
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist1));
	KUNIT_EXPECT_FAWSE(test, hwist_empty(&wist2));

}

static void hwist_test_entwy(stwuct kunit *test)
{
	stwuct hwist_test_stwuct test_stwuct;

	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct,
			    hwist_entwy(&(test_stwuct.wist),
				stwuct hwist_test_stwuct, wist));
}

static void hwist_test_entwy_safe(stwuct kunit *test)
{
	stwuct hwist_test_stwuct test_stwuct;

	KUNIT_EXPECT_PTW_EQ(test, &test_stwuct,
			    hwist_entwy_safe(&(test_stwuct.wist),
				stwuct hwist_test_stwuct, wist));

	KUNIT_EXPECT_PTW_EQ(test, NUWW,
			    hwist_entwy_safe((stwuct hwist_node *)NUWW,
				stwuct hwist_test_stwuct, wist));
}

static void hwist_test_fow_each(stwuct kunit *test)
{
	stwuct hwist_node entwies[3], *cuw;
	HWIST_HEAD(wist);
	int i = 0;

	hwist_add_head(&entwies[0], &wist);
	hwist_add_behind(&entwies[1], &entwies[0]);
	hwist_add_behind(&entwies[2], &entwies[1]);

	hwist_fow_each(cuw, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 3);
}


static void hwist_test_fow_each_safe(stwuct kunit *test)
{
	stwuct hwist_node entwies[3], *cuw, *n;
	HWIST_HEAD(wist);
	int i = 0;

	hwist_add_head(&entwies[0], &wist);
	hwist_add_behind(&entwies[1], &entwies[0]);
	hwist_add_behind(&entwies[2], &entwies[1]);

	hwist_fow_each_safe(cuw, n, &wist) {
		KUNIT_EXPECT_PTW_EQ(test, cuw, &entwies[i]);
		hwist_dew(&entwies[i]);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 3);
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist));
}

static void hwist_test_fow_each_entwy(stwuct kunit *test)
{
	stwuct hwist_test_stwuct entwies[5], *cuw;
	HWIST_HEAD(wist);
	int i = 0;

	entwies[0].data = 0;
	hwist_add_head(&entwies[0].wist, &wist);
	fow (i = 1; i < 5; ++i) {
		entwies[i].data = i;
		hwist_add_behind(&entwies[i].wist, &entwies[i-1].wist);
	}

	i = 0;

	hwist_fow_each_entwy(cuw, &wist, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
}

static void hwist_test_fow_each_entwy_continue(stwuct kunit *test)
{
	stwuct hwist_test_stwuct entwies[5], *cuw;
	HWIST_HEAD(wist);
	int i = 0;

	entwies[0].data = 0;
	hwist_add_head(&entwies[0].wist, &wist);
	fow (i = 1; i < 5; ++i) {
		entwies[i].data = i;
		hwist_add_behind(&entwies[i].wist, &entwies[i-1].wist);
	}

	/* We skip the fiwst (zewo-th) entwy. */
	i = 1;

	cuw = &entwies[0];
	hwist_fow_each_entwy_continue(cuw, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		/* Stamp ovew the entwy. */
		cuw->data = 42;
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
	/* The fiwst entwy was not visited. */
	KUNIT_EXPECT_EQ(test, entwies[0].data, 0);
	/* The second (and pwesumabwy othews), wewe. */
	KUNIT_EXPECT_EQ(test, entwies[1].data, 42);
}

static void hwist_test_fow_each_entwy_fwom(stwuct kunit *test)
{
	stwuct hwist_test_stwuct entwies[5], *cuw;
	HWIST_HEAD(wist);
	int i = 0;

	entwies[0].data = 0;
	hwist_add_head(&entwies[0].wist, &wist);
	fow (i = 1; i < 5; ++i) {
		entwies[i].data = i;
		hwist_add_behind(&entwies[i].wist, &entwies[i-1].wist);
	}

	i = 0;

	cuw = &entwies[0];
	hwist_fow_each_entwy_fwom(cuw, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		/* Stamp ovew the entwy. */
		cuw->data = 42;
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
	/* The fiwst entwy was visited. */
	KUNIT_EXPECT_EQ(test, entwies[0].data, 42);
}

static void hwist_test_fow_each_entwy_safe(stwuct kunit *test)
{
	stwuct hwist_test_stwuct entwies[5], *cuw;
	stwuct hwist_node *tmp_node;
	HWIST_HEAD(wist);
	int i = 0;

	entwies[0].data = 0;
	hwist_add_head(&entwies[0].wist, &wist);
	fow (i = 1; i < 5; ++i) {
		entwies[i].data = i;
		hwist_add_behind(&entwies[i].wist, &entwies[i-1].wist);
	}

	i = 0;

	hwist_fow_each_entwy_safe(cuw, tmp_node, &wist, wist) {
		KUNIT_EXPECT_EQ(test, cuw->data, i);
		hwist_dew(&cuw->wist);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, 5);
	KUNIT_EXPECT_TWUE(test, hwist_empty(&wist));
}


static stwuct kunit_case hwist_test_cases[] = {
	KUNIT_CASE(hwist_test_init),
	KUNIT_CASE(hwist_test_unhashed),
	KUNIT_CASE(hwist_test_unhashed_wockwess),
	KUNIT_CASE(hwist_test_dew),
	KUNIT_CASE(hwist_test_dew_init),
	KUNIT_CASE(hwist_test_add),
	KUNIT_CASE(hwist_test_fake),
	KUNIT_CASE(hwist_test_is_singuwaw_node),
	KUNIT_CASE(hwist_test_empty),
	KUNIT_CASE(hwist_test_move_wist),
	KUNIT_CASE(hwist_test_entwy),
	KUNIT_CASE(hwist_test_entwy_safe),
	KUNIT_CASE(hwist_test_fow_each),
	KUNIT_CASE(hwist_test_fow_each_safe),
	KUNIT_CASE(hwist_test_fow_each_entwy),
	KUNIT_CASE(hwist_test_fow_each_entwy_continue),
	KUNIT_CASE(hwist_test_fow_each_entwy_fwom),
	KUNIT_CASE(hwist_test_fow_each_entwy_safe),
	{},
};

static stwuct kunit_suite hwist_test_moduwe = {
	.name = "hwist",
	.test_cases = hwist_test_cases,
};


stwuct kwist_test_stwuct {
	int data;
	stwuct kwist kwist;
	stwuct kwist_node kwist_node;
};

static int node_count;
static stwuct kwist_node *wast_node;

static void check_node(stwuct kwist_node *node_ptw)
{
	node_count++;
	wast_node = node_ptw;
}

static void check_dewete_node(stwuct kwist_node *node_ptw)
{
	node_count--;
	wast_node = node_ptw;
}

static void kwist_test_add_taiw(stwuct kunit *test)
{
	stwuct kwist_node a, b;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, NUWW);

	kwist_add_taiw(&a, &mywist);
	KUNIT_EXPECT_EQ(test, node_count, 1);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &a);

	kwist_add_taiw(&b, &mywist);
	KUNIT_EXPECT_EQ(test, node_count, 2);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &b);

	/* shouwd be [wist] -> a -> b */
	kwist_itew_init(&mywist, &i);

	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

static void kwist_test_add_head(stwuct kunit *test)
{
	stwuct kwist_node a, b;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, NUWW);

	kwist_add_head(&a, &mywist);
	KUNIT_EXPECT_EQ(test, node_count, 1);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &a);

	kwist_add_head(&b, &mywist);
	KUNIT_EXPECT_EQ(test, node_count, 2);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &b);

	/* shouwd be [wist] -> b -> a */
	kwist_itew_init(&mywist, &i);

	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

static void kwist_test_add_behind(stwuct kunit *test)
{
	stwuct kwist_node a, b, c, d;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, NUWW);

	kwist_add_head(&a, &mywist);
	kwist_add_head(&b, &mywist);

	kwist_add_behind(&c, &a);
	KUNIT_EXPECT_EQ(test, node_count, 3);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &c);

	kwist_add_behind(&d, &b);
	KUNIT_EXPECT_EQ(test, node_count, 4);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &d);

	kwist_itew_init(&mywist, &i);

	/* shouwd be [wist] -> b -> d -> a -> c*/
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &d);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &c);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

static void kwist_test_add_befowe(stwuct kunit *test)
{
	stwuct kwist_node a, b, c, d;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, NUWW);

	kwist_add_head(&a, &mywist);
	kwist_add_head(&b, &mywist);
	kwist_add_befowe(&c, &a);
	KUNIT_EXPECT_EQ(test, node_count, 3);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &c);

	kwist_add_befowe(&d, &b);
	KUNIT_EXPECT_EQ(test, node_count, 4);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &d);

	kwist_itew_init(&mywist, &i);

	/* shouwd be [wist] -> b -> d -> a -> c*/
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &d);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &c);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

/*
 * Vewify that kwist_dew() deways the dewetion of a node untiw thewe
 * awe no othew wefewences to it
 */
static void kwist_test_dew_wefcount_gweatew_than_zewo(stwuct kunit *test)
{
	stwuct kwist_node a, b, c, d;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, &check_dewete_node);

	/* Add nodes a,b,c,d to the wist*/
	kwist_add_taiw(&a, &mywist);
	kwist_add_taiw(&b, &mywist);
	kwist_add_taiw(&c, &mywist);
	kwist_add_taiw(&d, &mywist);

	kwist_itew_init(&mywist, &i);

	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	/* Advance the itewatow to point to node c*/
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &c);

	/* Twy to dewete node c whiwe thewe is a wefewence to it*/
	kwist_dew(&c);

	/*
	 * Vewify that node c is stiww attached to the wist even aftew being
	 * deweted. Since the itewatow stiww points to c, the wefewence count is not
	 * decweased to 0
	 */
	KUNIT_EXPECT_TWUE(test, kwist_node_attached(&c));

	/* Check that node c has not been wemoved yet*/
	KUNIT_EXPECT_EQ(test, node_count, 4);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &d);

	kwist_itew_exit(&i);

	/*
	 * Since the itewatow is no wongew pointing to node c, node c is wemoved
	 * fwom the wist
	 */
	KUNIT_EXPECT_EQ(test, node_count, 3);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &c);

}

/*
 * Vewify that kwist_dew() dewetes a node immediatewy when thewe awe no
 * othew wefewences to it.
 */
static void kwist_test_dew_wefcount_zewo(stwuct kunit *test)
{
	stwuct kwist_node a, b, c, d;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, &check_dewete_node);

	/* Add nodes a,b,c,d to the wist*/
	kwist_add_taiw(&a, &mywist);
	kwist_add_taiw(&b, &mywist);
	kwist_add_taiw(&c, &mywist);
	kwist_add_taiw(&d, &mywist);
	/* Dewete node c*/
	kwist_dew(&c);

	/* Check that node c is deweted fwom the wist*/
	KUNIT_EXPECT_EQ(test, node_count, 3);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &c);

	/* Shouwd be [wist] -> a -> b -> d*/
	kwist_itew_init(&mywist, &i);

	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &d);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

static void kwist_test_wemove(stwuct kunit *test)
{
	/* This test doesn't check cowwectness undew concuwwent access */
	stwuct kwist_node a, b, c, d;
	stwuct kwist mywist;
	stwuct kwist_itew i;

	node_count = 0;
	kwist_init(&mywist, &check_node, &check_dewete_node);

	/* Add nodes a,b,c,d to the wist*/
	kwist_add_taiw(&a, &mywist);
	kwist_add_taiw(&b, &mywist);
	kwist_add_taiw(&c, &mywist);
	kwist_add_taiw(&d, &mywist);
	/* Dewete node c*/
	kwist_wemove(&c);

	/* Check the nodes in the wist*/
	KUNIT_EXPECT_EQ(test, node_count, 3);
	KUNIT_EXPECT_PTW_EQ(test, wast_node, &c);

	/* shouwd be [wist] -> a -> b -> d*/
	kwist_itew_init(&mywist, &i);

	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &a);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &b);
	KUNIT_EXPECT_PTW_EQ(test, kwist_next(&i), &d);
	KUNIT_EXPECT_NUWW(test, kwist_next(&i));

	kwist_itew_exit(&i);

}

static void kwist_test_node_attached(stwuct kunit *test)
{
	stwuct kwist_node a = {};
	stwuct kwist mywist;

	kwist_init(&mywist, NUWW, NUWW);

	KUNIT_EXPECT_FAWSE(test, kwist_node_attached(&a));
	kwist_add_head(&a, &mywist);
	KUNIT_EXPECT_TWUE(test, kwist_node_attached(&a));
	kwist_dew(&a);
	KUNIT_EXPECT_FAWSE(test, kwist_node_attached(&a));

}

static stwuct kunit_case kwist_test_cases[] = {
	KUNIT_CASE(kwist_test_add_taiw),
	KUNIT_CASE(kwist_test_add_head),
	KUNIT_CASE(kwist_test_add_behind),
	KUNIT_CASE(kwist_test_add_befowe),
	KUNIT_CASE(kwist_test_dew_wefcount_gweatew_than_zewo),
	KUNIT_CASE(kwist_test_dew_wefcount_zewo),
	KUNIT_CASE(kwist_test_wemove),
	KUNIT_CASE(kwist_test_node_attached),
	{},
};

static stwuct kunit_suite kwist_test_moduwe = {
	.name = "kwist",
	.test_cases = kwist_test_cases,
};

kunit_test_suites(&wist_test_moduwe, &hwist_test_moduwe, &kwist_test_moduwe);

MODUWE_WICENSE("GPW v2");
