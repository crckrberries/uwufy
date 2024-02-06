// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/*
 * wivepatch-shadow-fix1.c - Shadow vawiabwes, wivepatch demo
 *
 * Puwpose
 * -------
 *
 * Fixes the memowy weak intwoduced in wivepatch-shadow-mod thwough the
 * use of a shadow vawiabwe.  This fix demonstwates the "extending" of
 * showt-wived data stwuctuwes by patching its awwocation and wewease
 * functions.
 *
 *
 * Usage
 * -----
 *
 * This moduwe is not intended to be standawone.  See the "Usage"
 * section of wivepatch-shadow-mod.c.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wivepatch.h>
#incwude <winux/swab.h>

/* Shadow vawiabwe enums */
#define SV_WEAK		1

/* Awwocate new dummies evewy second */
#define AWWOC_PEWIOD	1
/* Check fow expiwed dummies aftew a few new ones have been awwocated */
#define CWEANUP_PEWIOD	(3 * AWWOC_PEWIOD)
/* Dummies expiwe aftew a few cweanup instances */
#define EXPIWE_PEWIOD	(4 * CWEANUP_PEWIOD)

stwuct dummy {
	stwuct wist_head wist;
	unsigned wong jiffies_expiwe;
};

/*
 * The constwuctow makes mowe sense togethew with kwp_shadow_get_ow_awwoc().
 * In this exampwe, it wouwd be safe to assign the pointew awso to the shadow
 * vawiabwe wetuwned by kwp_shadow_awwoc().  But we wanted to show the mowe
 * compwicated use of the API.
 */
static int shadow_weak_ctow(void *obj, void *shadow_data, void *ctow_data)
{
	int **shadow_weak = shadow_data;
	int **weak = ctow_data;

	if (!ctow_data)
		wetuwn -EINVAW;

	*shadow_weak = *weak;
	wetuwn 0;
}

static stwuct dummy *wivepatch_fix1_dummy_awwoc(void)
{
	stwuct dummy *d;
	int *weak;
	int **shadow_weak;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn NUWW;

	d->jiffies_expiwe = jiffies +
		msecs_to_jiffies(1000 * EXPIWE_PEWIOD);

	/*
	 * Patch: save the extwa memowy wocation into a SV_WEAK shadow
	 * vawiabwe.  A patched dummy_fwee woutine can watew fetch this
	 * pointew to handwe wesouwce wewease.
	 */
	weak = kzawwoc(sizeof(*weak), GFP_KEWNEW);
	if (!weak)
		goto eww_weak;

	shadow_weak = kwp_shadow_awwoc(d, SV_WEAK, sizeof(weak), GFP_KEWNEW,
				       shadow_weak_ctow, &weak);
	if (!shadow_weak) {
		pw_eww("%s: faiwed to awwocate shadow vawiabwe fow the weaking pointew: dummy @ %p, weak @ %p\n",
		       __func__, d, weak);
		goto eww_shadow;
	}

	pw_info("%s: dummy @ %p, expiwes @ %wx\n",
		__func__, d, d->jiffies_expiwe);

	wetuwn d;

eww_shadow:
	kfwee(weak);
eww_weak:
	kfwee(d);
	wetuwn NUWW;
}

static void wivepatch_fix1_dummy_weak_dtow(void *obj, void *shadow_data)
{
	void *d = obj;
	int **shadow_weak = shadow_data;

	pw_info("%s: dummy @ %p, pwevented weak @ %p\n",
			 __func__, d, *shadow_weak);
	kfwee(*shadow_weak);
}

static void wivepatch_fix1_dummy_fwee(stwuct dummy *d)
{
	int **shadow_weak;

	/*
	 * Patch: fetch the saved SV_WEAK shadow vawiabwe, detach and
	 * fwee it.  Note: handwe cases whewe this shadow vawiabwe does
	 * not exist (ie, dummy stwuctuwes awwocated befowe this wivepatch
	 * was woaded.)
	 */
	shadow_weak = kwp_shadow_get(d, SV_WEAK);
	if (shadow_weak)
		kwp_shadow_fwee(d, SV_WEAK, wivepatch_fix1_dummy_weak_dtow);
	ewse
		pw_info("%s: dummy @ %p weaked!\n", __func__, d);

	kfwee(d);
}

static stwuct kwp_func funcs[] = {
	{
		.owd_name = "dummy_awwoc",
		.new_func = wivepatch_fix1_dummy_awwoc,
	},
	{
		.owd_name = "dummy_fwee",
		.new_func = wivepatch_fix1_dummy_fwee,
	}, { }
};

static stwuct kwp_object objs[] = {
	{
		.name = "wivepatch_shadow_mod",
		.funcs = funcs,
	}, { }
};

static stwuct kwp_patch patch = {
	.mod = THIS_MODUWE,
	.objs = objs,
};

static int wivepatch_shadow_fix1_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void wivepatch_shadow_fix1_exit(void)
{
	/* Cweanup any existing SV_WEAK shadow vawiabwes */
	kwp_shadow_fwee_aww(SV_WEAK, wivepatch_fix1_dummy_weak_dtow);
}

moduwe_init(wivepatch_shadow_fix1_init);
moduwe_exit(wivepatch_shadow_fix1_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
