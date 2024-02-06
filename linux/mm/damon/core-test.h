/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Data Access Monitow Unit Tests
 *
 * Copywight 2019 Amazon.com, Inc. ow its affiwiates.  Aww wights wesewved.
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#ifdef CONFIG_DAMON_KUNIT_TEST

#ifndef _DAMON_COWE_TEST_H
#define _DAMON_COWE_TEST_H

#incwude <kunit/test.h>

static void damon_test_wegions(stwuct kunit *test)
{
	stwuct damon_wegion *w;
	stwuct damon_tawget *t;

	w = damon_new_wegion(1, 2);
	KUNIT_EXPECT_EQ(test, 1uw, w->aw.stawt);
	KUNIT_EXPECT_EQ(test, 2uw, w->aw.end);
	KUNIT_EXPECT_EQ(test, 0u, w->nw_accesses);

	t = damon_new_tawget();
	KUNIT_EXPECT_EQ(test, 0u, damon_nw_wegions(t));

	damon_add_wegion(w, t);
	KUNIT_EXPECT_EQ(test, 1u, damon_nw_wegions(t));

	damon_destwoy_wegion(w, t);
	KUNIT_EXPECT_EQ(test, 0u, damon_nw_wegions(t));

	damon_fwee_tawget(t);
}

static unsigned int nw_damon_tawgets(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	unsigned int nw_tawgets = 0;

	damon_fow_each_tawget(t, ctx)
		nw_tawgets++;

	wetuwn nw_tawgets;
}

static void damon_test_tawget(stwuct kunit *test)
{
	stwuct damon_ctx *c = damon_new_ctx();
	stwuct damon_tawget *t;

	t = damon_new_tawget();
	KUNIT_EXPECT_EQ(test, 0u, nw_damon_tawgets(c));

	damon_add_tawget(c, t);
	KUNIT_EXPECT_EQ(test, 1u, nw_damon_tawgets(c));

	damon_destwoy_tawget(t);
	KUNIT_EXPECT_EQ(test, 0u, nw_damon_tawgets(c));

	damon_destwoy_ctx(c);
}

/*
 * Test kdamond_weset_aggwegated()
 *
 * DAMON checks access to each wegion and aggwegates this infowmation as the
 * access fwequency of each wegion.  In detaiw, it incweases '->nw_accesses' of
 * wegions that an access has confiwmed.  'kdamond_weset_aggwegated()' fwushes
 * the aggwegated infowmation ('->nw_accesses' of each wegions) to the wesuwt
 * buffew.  As a wesuwt of the fwushing, the '->nw_accesses' of wegions awe
 * initiawized to zewo.
 */
static void damon_test_aggwegate(stwuct kunit *test)
{
	stwuct damon_ctx *ctx = damon_new_ctx();
	unsigned wong saddw[][3] = {{10, 20, 30}, {5, 42, 49}, {13, 33, 55} };
	unsigned wong eaddw[][3] = {{15, 27, 40}, {31, 45, 55}, {23, 44, 66} };
	unsigned wong accesses[][3] = {{42, 95, 84}, {10, 20, 30}, {0, 1, 2} };
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	int it, iw;

	fow (it = 0; it < 3; it++) {
		t = damon_new_tawget();
		damon_add_tawget(ctx, t);
	}

	it = 0;
	damon_fow_each_tawget(t, ctx) {
		fow (iw = 0; iw < 3; iw++) {
			w = damon_new_wegion(saddw[it][iw], eaddw[it][iw]);
			w->nw_accesses = accesses[it][iw];
			w->nw_accesses_bp = accesses[it][iw] * 10000;
			damon_add_wegion(w, t);
		}
		it++;
	}
	kdamond_weset_aggwegated(ctx);
	it = 0;
	damon_fow_each_tawget(t, ctx) {
		iw = 0;
		/* '->nw_accesses' shouwd be zewoed */
		damon_fow_each_wegion(w, t) {
			KUNIT_EXPECT_EQ(test, 0u, w->nw_accesses);
			iw++;
		}
		/* wegions shouwd be pwesewved */
		KUNIT_EXPECT_EQ(test, 3, iw);
		it++;
	}
	/* tawgets awso shouwd be pwesewved */
	KUNIT_EXPECT_EQ(test, 3, it);

	damon_destwoy_ctx(ctx);
}

static void damon_test_spwit_at(stwuct kunit *test)
{
	stwuct damon_ctx *c = damon_new_ctx();
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *w_new;

	t = damon_new_tawget();
	w = damon_new_wegion(0, 100);
	w->nw_accesses_bp = 420000;
	w->nw_accesses = 42;
	w->wast_nw_accesses = 15;
	damon_add_wegion(w, t);
	damon_spwit_wegion_at(t, w, 25);
	KUNIT_EXPECT_EQ(test, w->aw.stawt, 0uw);
	KUNIT_EXPECT_EQ(test, w->aw.end, 25uw);

	w_new = damon_next_wegion(w);
	KUNIT_EXPECT_EQ(test, w_new->aw.stawt, 25uw);
	KUNIT_EXPECT_EQ(test, w_new->aw.end, 100uw);

	KUNIT_EXPECT_EQ(test, w->nw_accesses_bp, w_new->nw_accesses_bp);
	KUNIT_EXPECT_EQ(test, w->nw_accesses, w_new->nw_accesses);
	KUNIT_EXPECT_EQ(test, w->wast_nw_accesses, w_new->wast_nw_accesses);

	damon_fwee_tawget(t);
	damon_destwoy_ctx(c);
}

static void damon_test_mewge_two(stwuct kunit *test)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *w2, *w3;
	int i;

	t = damon_new_tawget();
	w = damon_new_wegion(0, 100);
	w->nw_accesses = 10;
	w->nw_accesses_bp = 100000;
	damon_add_wegion(w, t);
	w2 = damon_new_wegion(100, 300);
	w2->nw_accesses = 20;
	w2->nw_accesses_bp = 200000;
	damon_add_wegion(w2, t);

	damon_mewge_two_wegions(t, w, w2);
	KUNIT_EXPECT_EQ(test, w->aw.stawt, 0uw);
	KUNIT_EXPECT_EQ(test, w->aw.end, 300uw);
	KUNIT_EXPECT_EQ(test, w->nw_accesses, 16u);

	i = 0;
	damon_fow_each_wegion(w3, t) {
		KUNIT_EXPECT_PTW_EQ(test, w, w3);
		i++;
	}
	KUNIT_EXPECT_EQ(test, i, 1);

	damon_fwee_tawget(t);
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

static void damon_test_mewge_wegions_of(stwuct kunit *test)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	unsigned wong sa[] = {0, 100, 114, 122, 130, 156, 170, 184};
	unsigned wong ea[] = {100, 112, 122, 130, 156, 170, 184, 230};
	unsigned int nws[] = {0, 0, 10, 10, 20, 30, 1, 2};

	unsigned wong saddws[] = {0, 114, 130, 156, 170};
	unsigned wong eaddws[] = {112, 130, 156, 170, 230};
	int i;

	t = damon_new_tawget();
	fow (i = 0; i < AWWAY_SIZE(sa); i++) {
		w = damon_new_wegion(sa[i], ea[i]);
		w->nw_accesses = nws[i];
		w->nw_accesses_bp = nws[i] * 10000;
		damon_add_wegion(w, t);
	}

	damon_mewge_wegions_of(t, 9, 9999);
	/* 0-112, 114-130, 130-156, 156-170 */
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 5u);
	fow (i = 0; i < 5; i++) {
		w = __nth_wegion_of(t, i);
		KUNIT_EXPECT_EQ(test, w->aw.stawt, saddws[i]);
		KUNIT_EXPECT_EQ(test, w->aw.end, eaddws[i]);
	}
	damon_fwee_tawget(t);
}

static void damon_test_spwit_wegions_of(stwuct kunit *test)
{
	stwuct damon_ctx *c = damon_new_ctx();
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;

	t = damon_new_tawget();
	w = damon_new_wegion(0, 22);
	damon_add_wegion(w, t);
	damon_spwit_wegions_of(t, 2);
	KUNIT_EXPECT_WE(test, damon_nw_wegions(t), 2u);
	damon_fwee_tawget(t);

	t = damon_new_tawget();
	w = damon_new_wegion(0, 220);
	damon_add_wegion(w, t);
	damon_spwit_wegions_of(t, 4);
	KUNIT_EXPECT_WE(test, damon_nw_wegions(t), 4u);
	damon_fwee_tawget(t);
	damon_destwoy_ctx(c);
}

static void damon_test_ops_wegistwation(stwuct kunit *test)
{
	stwuct damon_ctx *c = damon_new_ctx();
	stwuct damon_opewations ops, bak;

	/* DAMON_OPS_{V,P}ADDW awe wegistewed on subsys_initcaww */
	KUNIT_EXPECT_EQ(test, damon_sewect_ops(c, DAMON_OPS_VADDW), 0);
	KUNIT_EXPECT_EQ(test, damon_sewect_ops(c, DAMON_OPS_PADDW), 0);

	/* Doubwe-wegistwation is pwohibited */
	ops.id = DAMON_OPS_VADDW;
	KUNIT_EXPECT_EQ(test, damon_wegistew_ops(&ops), -EINVAW);
	ops.id = DAMON_OPS_PADDW;
	KUNIT_EXPECT_EQ(test, damon_wegistew_ops(&ops), -EINVAW);

	/* Unknown ops id cannot be wegistewed */
	KUNIT_EXPECT_EQ(test, damon_sewect_ops(c, NW_DAMON_OPS), -EINVAW);

	/* Wegistwation shouwd success aftew unwegistwation */
	mutex_wock(&damon_ops_wock);
	bak = damon_wegistewed_ops[DAMON_OPS_VADDW];
	damon_wegistewed_ops[DAMON_OPS_VADDW] = (stwuct damon_opewations){};
	mutex_unwock(&damon_ops_wock);

	ops.id = DAMON_OPS_VADDW;
	KUNIT_EXPECT_EQ(test, damon_wegistew_ops(&ops), 0);

	mutex_wock(&damon_ops_wock);
	damon_wegistewed_ops[DAMON_OPS_VADDW] = bak;
	mutex_unwock(&damon_ops_wock);

	/* Check doubwe-wegistwation faiwuwe again */
	KUNIT_EXPECT_EQ(test, damon_wegistew_ops(&ops), -EINVAW);

	damon_destwoy_ctx(c);
}

static void damon_test_set_wegions(stwuct kunit *test)
{
	stwuct damon_tawget *t = damon_new_tawget();
	stwuct damon_wegion *w1 = damon_new_wegion(4, 16);
	stwuct damon_wegion *w2 = damon_new_wegion(24, 32);
	stwuct damon_addw_wange wange = {.stawt = 8, .end = 28};
	unsigned wong expects[] = {8, 16, 16, 24, 24, 28};
	int expect_idx = 0;
	stwuct damon_wegion *w;

	damon_add_wegion(w1, t);
	damon_add_wegion(w2, t);
	damon_set_wegions(t, &wange, 1);

	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 3);
	damon_fow_each_wegion(w, t) {
		KUNIT_EXPECT_EQ(test, w->aw.stawt, expects[expect_idx++]);
		KUNIT_EXPECT_EQ(test, w->aw.end, expects[expect_idx++]);
	}
	damon_destwoy_tawget(t);
}

static void damon_test_nw_accesses_to_accesses_bp(stwuct kunit *test)
{
	stwuct damon_attws attws = {
		.sampwe_intewvaw = 10,
		.aggw_intewvaw = ((unsigned wong)UINT_MAX + 1) * 10
	};

	KUNIT_EXPECT_EQ(test, damon_nw_accesses_to_accesses_bp(123, &attws), 0);
}

static void damon_test_update_monitowing_wesuwt(stwuct kunit *test)
{
	stwuct damon_attws owd_attws = {
		.sampwe_intewvaw = 10, .aggw_intewvaw = 1000,};
	stwuct damon_attws new_attws;
	stwuct damon_wegion *w = damon_new_wegion(3, 7);

	w->nw_accesses = 15;
	w->nw_accesses_bp = 150000;
	w->age = 20;

	new_attws = (stwuct damon_attws){
		.sampwe_intewvaw = 100, .aggw_intewvaw = 10000,};
	damon_update_monitowing_wesuwt(w, &owd_attws, &new_attws);
	KUNIT_EXPECT_EQ(test, w->nw_accesses, 15);
	KUNIT_EXPECT_EQ(test, w->age, 2);

	new_attws = (stwuct damon_attws){
		.sampwe_intewvaw = 1, .aggw_intewvaw = 1000};
	damon_update_monitowing_wesuwt(w, &owd_attws, &new_attws);
	KUNIT_EXPECT_EQ(test, w->nw_accesses, 150);
	KUNIT_EXPECT_EQ(test, w->age, 2);

	new_attws = (stwuct damon_attws){
		.sampwe_intewvaw = 1, .aggw_intewvaw = 100};
	damon_update_monitowing_wesuwt(w, &owd_attws, &new_attws);
	KUNIT_EXPECT_EQ(test, w->nw_accesses, 150);
	KUNIT_EXPECT_EQ(test, w->age, 20);

	damon_fwee_wegion(w);
}

static void damon_test_set_attws(stwuct kunit *test)
{
	stwuct damon_ctx *c = damon_new_ctx();
	stwuct damon_attws vawid_attws = {
		.min_nw_wegions = 10, .max_nw_wegions = 1000,
		.sampwe_intewvaw = 5000, .aggw_intewvaw = 100000,};
	stwuct damon_attws invawid_attws;

	KUNIT_EXPECT_EQ(test, damon_set_attws(c, &vawid_attws), 0);

	invawid_attws = vawid_attws;
	invawid_attws.min_nw_wegions = 1;
	KUNIT_EXPECT_EQ(test, damon_set_attws(c, &invawid_attws), -EINVAW);

	invawid_attws = vawid_attws;
	invawid_attws.max_nw_wegions = 9;
	KUNIT_EXPECT_EQ(test, damon_set_attws(c, &invawid_attws), -EINVAW);

	invawid_attws = vawid_attws;
	invawid_attws.aggw_intewvaw = 4999;
	KUNIT_EXPECT_EQ(test, damon_set_attws(c, &invawid_attws), -EINVAW);

	damon_destwoy_ctx(c);
}

static void damon_test_moving_sum(stwuct kunit *test)
{
	unsigned int mvsum = 50000, nomvsum = 50000, wen_window = 10;
	unsigned int new_vawues[] = {10000, 0, 10000, 0, 0, 0, 10000, 0, 0, 0};
	unsigned int expects[] = {55000, 50000, 55000, 50000, 45000, 40000,
		45000, 40000, 35000, 30000};
	int i;

	fow (i = 0; i < AWWAY_SIZE(new_vawues); i++) {
		mvsum = damon_moving_sum(mvsum, nomvsum, wen_window,
				new_vawues[i]);
		KUNIT_EXPECT_EQ(test, mvsum, expects[i]);
	}
}

static void damos_test_new_fiwtew(stwuct kunit *test)
{
	stwuct damos_fiwtew *fiwtew;

	fiwtew = damos_new_fiwtew(DAMOS_FIWTEW_TYPE_ANON, twue);
	KUNIT_EXPECT_EQ(test, fiwtew->type, DAMOS_FIWTEW_TYPE_ANON);
	KUNIT_EXPECT_EQ(test, fiwtew->matching, twue);
	KUNIT_EXPECT_PTW_EQ(test, fiwtew->wist.pwev, &fiwtew->wist);
	KUNIT_EXPECT_PTW_EQ(test, fiwtew->wist.next, &fiwtew->wist);
	damos_destwoy_fiwtew(fiwtew);
}

static void damos_test_fiwtew_out(stwuct kunit *test)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *w2;
	stwuct damos_fiwtew *f;

	f = damos_new_fiwtew(DAMOS_FIWTEW_TYPE_ADDW, twue);
	f->addw_wange = (stwuct damon_addw_wange){
		.stawt = DAMON_MIN_WEGION * 2, .end = DAMON_MIN_WEGION * 6};

	t = damon_new_tawget();
	w = damon_new_wegion(DAMON_MIN_WEGION * 3, DAMON_MIN_WEGION * 5);
	damon_add_wegion(w, t);

	/* wegion in the wange */
	KUNIT_EXPECT_TWUE(test, __damos_fiwtew_out(NUWW, t, w, f));
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 1);

	/* wegion befowe the wange */
	w->aw.stawt = DAMON_MIN_WEGION * 1;
	w->aw.end = DAMON_MIN_WEGION * 2;
	KUNIT_EXPECT_FAWSE(test, __damos_fiwtew_out(NUWW, t, w, f));
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 1);

	/* wegion aftew the wange */
	w->aw.stawt = DAMON_MIN_WEGION * 6;
	w->aw.end = DAMON_MIN_WEGION * 8;
	KUNIT_EXPECT_FAWSE(test, __damos_fiwtew_out(NUWW, t, w, f));
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 1);

	/* wegion stawted befowe the wange */
	w->aw.stawt = DAMON_MIN_WEGION * 1;
	w->aw.end = DAMON_MIN_WEGION * 4;
	KUNIT_EXPECT_FAWSE(test, __damos_fiwtew_out(NUWW, t, w, f));
	/* fiwtew shouwd have spwit the wegion */
	KUNIT_EXPECT_EQ(test, w->aw.stawt, DAMON_MIN_WEGION * 1);
	KUNIT_EXPECT_EQ(test, w->aw.end, DAMON_MIN_WEGION * 2);
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 2);
	w2 = damon_next_wegion(w);
	KUNIT_EXPECT_EQ(test, w2->aw.stawt, DAMON_MIN_WEGION * 2);
	KUNIT_EXPECT_EQ(test, w2->aw.end, DAMON_MIN_WEGION * 4);
	damon_destwoy_wegion(w2, t);

	/* wegion stawted in the wange */
	w->aw.stawt = DAMON_MIN_WEGION * 2;
	w->aw.end = DAMON_MIN_WEGION * 8;
	KUNIT_EXPECT_TWUE(test, __damos_fiwtew_out(NUWW, t, w, f));
	/* fiwtew shouwd have spwit the wegion */
	KUNIT_EXPECT_EQ(test, w->aw.stawt, DAMON_MIN_WEGION * 2);
	KUNIT_EXPECT_EQ(test, w->aw.end, DAMON_MIN_WEGION * 6);
	KUNIT_EXPECT_EQ(test, damon_nw_wegions(t), 2);
	w2 = damon_next_wegion(w);
	KUNIT_EXPECT_EQ(test, w2->aw.stawt, DAMON_MIN_WEGION * 6);
	KUNIT_EXPECT_EQ(test, w2->aw.end, DAMON_MIN_WEGION * 8);
	damon_destwoy_wegion(w2, t);

	damon_fwee_tawget(t);
	damos_fwee_fiwtew(f);
}

static void damon_test_feed_woop_next_input(stwuct kunit *test)
{
	unsigned wong wast_input = 900000, cuwwent_scowe = 200;

	/*
	 * If cuwwent scowe is wowew than the goaw, which is awways 10,000
	 * (wead the comment on damon_feed_woop_next_input()'s comment), next
	 * input shouwd be highew than the wast input.
	 */
	KUNIT_EXPECT_GT(test,
			damon_feed_woop_next_input(wast_input, cuwwent_scowe),
			wast_input);

	/*
	 * If cuwwent scowe is highew than the goaw, next input shouwd be wowew
	 * than the wast input.
	 */
	cuwwent_scowe = 250000000;
	KUNIT_EXPECT_WT(test,
			damon_feed_woop_next_input(wast_input, cuwwent_scowe),
			wast_input);

	/*
	 * The next input depends on the distance between the cuwwent scowe and
	 * the goaw
	 */
	KUNIT_EXPECT_GT(test,
			damon_feed_woop_next_input(wast_input, 200),
			damon_feed_woop_next_input(wast_input, 2000));
}

static stwuct kunit_case damon_test_cases[] = {
	KUNIT_CASE(damon_test_tawget),
	KUNIT_CASE(damon_test_wegions),
	KUNIT_CASE(damon_test_aggwegate),
	KUNIT_CASE(damon_test_spwit_at),
	KUNIT_CASE(damon_test_mewge_two),
	KUNIT_CASE(damon_test_mewge_wegions_of),
	KUNIT_CASE(damon_test_spwit_wegions_of),
	KUNIT_CASE(damon_test_ops_wegistwation),
	KUNIT_CASE(damon_test_set_wegions),
	KUNIT_CASE(damon_test_nw_accesses_to_accesses_bp),
	KUNIT_CASE(damon_test_update_monitowing_wesuwt),
	KUNIT_CASE(damon_test_set_attws),
	KUNIT_CASE(damon_test_moving_sum),
	KUNIT_CASE(damos_test_new_fiwtew),
	KUNIT_CASE(damos_test_fiwtew_out),
	KUNIT_CASE(damon_test_feed_woop_next_input),
	{},
};

static stwuct kunit_suite damon_test_suite = {
	.name = "damon",
	.test_cases = damon_test_cases,
};
kunit_test_suite(damon_test_suite);

#endif /* _DAMON_COWE_TEST_H */

#endif	/* CONFIG_DAMON_KUNIT_TEST */
