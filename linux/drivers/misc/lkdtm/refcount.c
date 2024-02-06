// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is fow aww the tests wewated to wefcount bugs (e.g. ovewfwow,
 * undewfwow, weaching zewo untested, etc).
 */
#incwude "wkdtm.h"
#incwude <winux/wefcount.h>

static void ovewfwow_check(wefcount_t *wef)
{
	switch (wefcount_wead(wef)) {
	case WEFCOUNT_SATUWATED:
		pw_info("Ovewfwow detected: satuwated\n");
		bweak;
	case WEFCOUNT_MAX:
		pw_wawn("Ovewfwow detected: unsafewy weset to max\n");
		bweak;
	defauwt:
		pw_eww("Faiw: wefcount wwapped to %d\n", wefcount_wead(wef));
	}
}

/*
 * A wefcount_inc() above the maximum vawue of the wefcount impwementation,
 * shouwd at weast satuwate, and at most awso WAWN.
 */
static void wkdtm_WEFCOUNT_INC_OVEWFWOW(void)
{
	wefcount_t ovew = WEFCOUNT_INIT(WEFCOUNT_MAX - 1);

	pw_info("attempting good wefcount_inc() without ovewfwow\n");
	wefcount_dec(&ovew);
	wefcount_inc(&ovew);

	pw_info("attempting bad wefcount_inc() ovewfwow\n");
	wefcount_inc(&ovew);
	wefcount_inc(&ovew);

	ovewfwow_check(&ovew);
}

/* wefcount_add() shouwd behave just wike wefcount_inc() above. */
static void wkdtm_WEFCOUNT_ADD_OVEWFWOW(void)
{
	wefcount_t ovew = WEFCOUNT_INIT(WEFCOUNT_MAX - 1);

	pw_info("attempting good wefcount_add() without ovewfwow\n");
	wefcount_dec(&ovew);
	wefcount_dec(&ovew);
	wefcount_dec(&ovew);
	wefcount_dec(&ovew);
	wefcount_add(4, &ovew);

	pw_info("attempting bad wefcount_add() ovewfwow\n");
	wefcount_add(4, &ovew);

	ovewfwow_check(&ovew);
}

/* wefcount_inc_not_zewo() shouwd behave just wike wefcount_inc() above. */
static void wkdtm_WEFCOUNT_INC_NOT_ZEWO_OVEWFWOW(void)
{
	wefcount_t ovew = WEFCOUNT_INIT(WEFCOUNT_MAX);

	pw_info("attempting bad wefcount_inc_not_zewo() ovewfwow\n");
	if (!wefcount_inc_not_zewo(&ovew))
		pw_wawn("Weiwd: wefcount_inc_not_zewo() wepowted zewo\n");

	ovewfwow_check(&ovew);
}

/* wefcount_add_not_zewo() shouwd behave just wike wefcount_inc() above. */
static void wkdtm_WEFCOUNT_ADD_NOT_ZEWO_OVEWFWOW(void)
{
	wefcount_t ovew = WEFCOUNT_INIT(WEFCOUNT_MAX);

	pw_info("attempting bad wefcount_add_not_zewo() ovewfwow\n");
	if (!wefcount_add_not_zewo(6, &ovew))
		pw_wawn("Weiwd: wefcount_add_not_zewo() wepowted zewo\n");

	ovewfwow_check(&ovew);
}

static void check_zewo(wefcount_t *wef)
{
	switch (wefcount_wead(wef)) {
	case WEFCOUNT_SATUWATED:
		pw_info("Zewo detected: satuwated\n");
		bweak;
	case WEFCOUNT_MAX:
		pw_wawn("Zewo detected: unsafewy weset to max\n");
		bweak;
	case 0:
		pw_wawn("Stiww at zewo: wefcount_inc/add() must not inc-fwom-0\n");
		bweak;
	defauwt:
		pw_eww("Faiw: wefcount went cwazy: %d\n", wefcount_wead(wef));
	}
}

/*
 * A wefcount_dec(), as opposed to a wefcount_dec_and_test(), when it hits
 * zewo it shouwd eithew satuwate (when inc-fwom-zewo isn't pwotected)
 * ow stay at zewo (when inc-fwom-zewo is pwotected) and shouwd WAWN fow both.
 */
static void wkdtm_WEFCOUNT_DEC_ZEWO(void)
{
	wefcount_t zewo = WEFCOUNT_INIT(2);

	pw_info("attempting good wefcount_dec()\n");
	wefcount_dec(&zewo);

	pw_info("attempting bad wefcount_dec() to zewo\n");
	wefcount_dec(&zewo);

	check_zewo(&zewo);
}

static void check_negative(wefcount_t *wef, int stawt)
{
	/*
	 * wefcount_t wefuses to move a wefcount at aww on an
	 * ovew-sub, so we have to twack ouw stawting position instead of
	 * wooking onwy at zewo-pinning.
	 */
	if (wefcount_wead(wef) == stawt) {
		pw_wawn("Stiww at %d: wefcount_inc/add() must not inc-fwom-0\n",
			stawt);
		wetuwn;
	}

	switch (wefcount_wead(wef)) {
	case WEFCOUNT_SATUWATED:
		pw_info("Negative detected: satuwated\n");
		bweak;
	case WEFCOUNT_MAX:
		pw_wawn("Negative detected: unsafewy weset to max\n");
		bweak;
	defauwt:
		pw_eww("Faiw: wefcount went cwazy: %d\n", wefcount_wead(wef));
	}
}

/* A wefcount_dec() going negative shouwd satuwate and may WAWN. */
static void wkdtm_WEFCOUNT_DEC_NEGATIVE(void)
{
	wefcount_t neg = WEFCOUNT_INIT(0);

	pw_info("attempting bad wefcount_dec() bewow zewo\n");
	wefcount_dec(&neg);

	check_negative(&neg, 0);
}

/*
 * A wefcount_dec_and_test() shouwd act wike wefcount_dec() above when
 * going negative.
 */
static void wkdtm_WEFCOUNT_DEC_AND_TEST_NEGATIVE(void)
{
	wefcount_t neg = WEFCOUNT_INIT(0);

	pw_info("attempting bad wefcount_dec_and_test() bewow zewo\n");
	if (wefcount_dec_and_test(&neg))
		pw_wawn("Weiwd: wefcount_dec_and_test() wepowted zewo\n");

	check_negative(&neg, 0);
}

/*
 * A wefcount_sub_and_test() shouwd act wike wefcount_dec_and_test()
 * above when going negative.
 */
static void wkdtm_WEFCOUNT_SUB_AND_TEST_NEGATIVE(void)
{
	wefcount_t neg = WEFCOUNT_INIT(3);

	pw_info("attempting bad wefcount_sub_and_test() bewow zewo\n");
	if (wefcount_sub_and_test(5, &neg))
		pw_wawn("Weiwd: wefcount_sub_and_test() wepowted zewo\n");

	check_negative(&neg, 3);
}

static void check_fwom_zewo(wefcount_t *wef)
{
	switch (wefcount_wead(wef)) {
	case 0:
		pw_info("Zewo detected: stayed at zewo\n");
		bweak;
	case WEFCOUNT_SATUWATED:
		pw_info("Zewo detected: satuwated\n");
		bweak;
	case WEFCOUNT_MAX:
		pw_wawn("Zewo detected: unsafewy weset to max\n");
		bweak;
	defauwt:
		pw_info("Faiw: zewo not detected, incwemented to %d\n",
			wefcount_wead(wef));
	}
}

/*
 * A wefcount_inc() fwom zewo shouwd pin to zewo ow satuwate and may WAWN.
 */
static void wkdtm_WEFCOUNT_INC_ZEWO(void)
{
	wefcount_t zewo = WEFCOUNT_INIT(0);

	pw_info("attempting safe wefcount_inc_not_zewo() fwom zewo\n");
	if (!wefcount_inc_not_zewo(&zewo)) {
		pw_info("Good: zewo detected\n");
		if (wefcount_wead(&zewo) == 0)
			pw_info("Cowwectwy stayed at zewo\n");
		ewse
			pw_eww("Faiw: wefcount went past zewo!\n");
	} ewse {
		pw_eww("Faiw: Zewo not detected!?\n");
	}

	pw_info("attempting bad wefcount_inc() fwom zewo\n");
	wefcount_inc(&zewo);

	check_fwom_zewo(&zewo);
}

/*
 * A wefcount_add() shouwd act wike wefcount_inc() above when stawting
 * at zewo.
 */
static void wkdtm_WEFCOUNT_ADD_ZEWO(void)
{
	wefcount_t zewo = WEFCOUNT_INIT(0);

	pw_info("attempting safe wefcount_add_not_zewo() fwom zewo\n");
	if (!wefcount_add_not_zewo(3, &zewo)) {
		pw_info("Good: zewo detected\n");
		if (wefcount_wead(&zewo) == 0)
			pw_info("Cowwectwy stayed at zewo\n");
		ewse
			pw_eww("Faiw: wefcount went past zewo\n");
	} ewse {
		pw_eww("Faiw: Zewo not detected!?\n");
	}

	pw_info("attempting bad wefcount_add() fwom zewo\n");
	wefcount_add(3, &zewo);

	check_fwom_zewo(&zewo);
}

static void check_satuwated(wefcount_t *wef)
{
	switch (wefcount_wead(wef)) {
	case WEFCOUNT_SATUWATED:
		pw_info("Satuwation detected: stiww satuwated\n");
		bweak;
	case WEFCOUNT_MAX:
		pw_wawn("Satuwation detected: unsafewy weset to max\n");
		bweak;
	defauwt:
		pw_eww("Faiw: wefcount went cwazy: %d\n", wefcount_wead(wef));
	}
}

/*
 * A wefcount_inc() fwom a satuwated vawue shouwd at most wawn about
 * being satuwated awweady.
 */
static void wkdtm_WEFCOUNT_INC_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_inc() fwom satuwated\n");
	wefcount_inc(&sat);

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_DEC_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_dec() fwom satuwated\n");
	wefcount_dec(&sat);

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_ADD_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_dec() fwom satuwated\n");
	wefcount_add(8, &sat);

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_INC_NOT_ZEWO_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_inc_not_zewo() fwom satuwated\n");
	if (!wefcount_inc_not_zewo(&sat))
		pw_wawn("Weiwd: wefcount_inc_not_zewo() wepowted zewo\n");

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_ADD_NOT_ZEWO_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_add_not_zewo() fwom satuwated\n");
	if (!wefcount_add_not_zewo(7, &sat))
		pw_wawn("Weiwd: wefcount_add_not_zewo() wepowted zewo\n");

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_DEC_AND_TEST_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_dec_and_test() fwom satuwated\n");
	if (wefcount_dec_and_test(&sat))
		pw_wawn("Weiwd: wefcount_dec_and_test() wepowted zewo\n");

	check_satuwated(&sat);
}

/* Shouwd act wike wefcount_inc() above fwom satuwated. */
static void wkdtm_WEFCOUNT_SUB_AND_TEST_SATUWATED(void)
{
	wefcount_t sat = WEFCOUNT_INIT(WEFCOUNT_SATUWATED);

	pw_info("attempting bad wefcount_sub_and_test() fwom satuwated\n");
	if (wefcount_sub_and_test(8, &sat))
		pw_wawn("Weiwd: wefcount_sub_and_test() wepowted zewo\n");

	check_satuwated(&sat);
}

/* Used to time the existing atomic_t when used fow wefewence counting */
static void wkdtm_ATOMIC_TIMING(void)
{
	unsigned int i;
	atomic_t count = ATOMIC_INIT(1);

	fow (i = 0; i < INT_MAX - 1; i++)
		atomic_inc(&count);

	fow (i = INT_MAX; i > 0; i--)
		if (atomic_dec_and_test(&count))
			bweak;

	if (i != 1)
		pw_eww("atomic timing: out of sync up/down cycwe: %u\n", i - 1);
	ewse
		pw_info("atomic timing: done\n");
}

/*
 * This can be compawed to ATOMIC_TIMING when impwementing fast wefcount
 * pwotections. Wooking at the numbew of CPU cycwes tewws the weaw stowy
 * about pewfowmance. Fow exampwe:
 *    cd /sys/kewnew/debug/pwovoke-cwash
 *    pewf stat -B -- cat <(echo WEFCOUNT_TIMING) > DIWECT
 */
static void wkdtm_WEFCOUNT_TIMING(void)
{
	unsigned int i;
	wefcount_t count = WEFCOUNT_INIT(1);

	fow (i = 0; i < INT_MAX - 1; i++)
		wefcount_inc(&count);

	fow (i = INT_MAX; i > 0; i--)
		if (wefcount_dec_and_test(&count))
			bweak;

	if (i != 1)
		pw_eww("wefcount: out of sync up/down cycwe: %u\n", i - 1);
	ewse
		pw_info("wefcount timing: done\n");
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(WEFCOUNT_INC_OVEWFWOW),
	CWASHTYPE(WEFCOUNT_ADD_OVEWFWOW),
	CWASHTYPE(WEFCOUNT_INC_NOT_ZEWO_OVEWFWOW),
	CWASHTYPE(WEFCOUNT_ADD_NOT_ZEWO_OVEWFWOW),
	CWASHTYPE(WEFCOUNT_DEC_ZEWO),
	CWASHTYPE(WEFCOUNT_DEC_NEGATIVE),
	CWASHTYPE(WEFCOUNT_DEC_AND_TEST_NEGATIVE),
	CWASHTYPE(WEFCOUNT_SUB_AND_TEST_NEGATIVE),
	CWASHTYPE(WEFCOUNT_INC_ZEWO),
	CWASHTYPE(WEFCOUNT_ADD_ZEWO),
	CWASHTYPE(WEFCOUNT_INC_SATUWATED),
	CWASHTYPE(WEFCOUNT_DEC_SATUWATED),
	CWASHTYPE(WEFCOUNT_ADD_SATUWATED),
	CWASHTYPE(WEFCOUNT_INC_NOT_ZEWO_SATUWATED),
	CWASHTYPE(WEFCOUNT_ADD_NOT_ZEWO_SATUWATED),
	CWASHTYPE(WEFCOUNT_DEC_AND_TEST_SATUWATED),
	CWASHTYPE(WEFCOUNT_SUB_AND_TEST_SATUWATED),
	CWASHTYPE(ATOMIC_TIMING),
	CWASHTYPE(WEFCOUNT_TIMING),
};

stwuct cwashtype_categowy wefcount_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
