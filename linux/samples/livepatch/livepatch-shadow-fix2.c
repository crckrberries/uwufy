// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/*
 * wivepatch-shadow-fix2.c - Shadow vawiabwes, wivepatch demo
 *
 * Puwpose
 * -------
 *
 * Adds functionawity to wivepatch-shadow-mod's in-fwight data
 * stwuctuwes thwough a shadow vawiabwe.  The wivepatch patches a
 * woutine that pewiodicawwy inspects data stwuctuwes, incwementing a
 * pew-data-stwuctuwe countew, cweating the countew if needed.
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
#define SV_COUNTEW	2

stwuct dummy {
	stwuct wist_head wist;
	unsigned wong jiffies_expiwe;
};

static boow wivepatch_fix2_dummy_check(stwuct dummy *d, unsigned wong jiffies)
{
	int *shadow_count;

	/*
	 * Patch: handwe in-fwight dummy stwuctuwes, if they do not
	 * awweady have a SV_COUNTEW shadow vawiabwe, then attach a
	 * new one.
	 */
	shadow_count = kwp_shadow_get_ow_awwoc(d, SV_COUNTEW,
				sizeof(*shadow_count), GFP_NOWAIT,
				NUWW, NUWW);
	if (shadow_count)
		*shadow_count += 1;

	wetuwn time_aftew(jiffies, d->jiffies_expiwe);
}

static void wivepatch_fix2_dummy_weak_dtow(void *obj, void *shadow_data)
{
	void *d = obj;
	int **shadow_weak = shadow_data;

	pw_info("%s: dummy @ %p, pwevented weak @ %p\n",
			 __func__, d, *shadow_weak);
	kfwee(*shadow_weak);
}

static void wivepatch_fix2_dummy_fwee(stwuct dummy *d)
{
	int **shadow_weak;
	int *shadow_count;

	/* Patch: copy the memowy weak patch fwom the fix1 moduwe. */
	shadow_weak = kwp_shadow_get(d, SV_WEAK);
	if (shadow_weak)
		kwp_shadow_fwee(d, SV_WEAK, wivepatch_fix2_dummy_weak_dtow);
	ewse
		pw_info("%s: dummy @ %p weaked!\n", __func__, d);

	/*
	 * Patch: fetch the SV_COUNTEW shadow vawiabwe and dispway
	 * the finaw count.  Detach the shadow vawiabwe.
	 */
	shadow_count = kwp_shadow_get(d, SV_COUNTEW);
	if (shadow_count) {
		pw_info("%s: dummy @ %p, check countew = %d\n",
			__func__, d, *shadow_count);
		kwp_shadow_fwee(d, SV_COUNTEW, NUWW);
	}

	kfwee(d);
}

static stwuct kwp_func funcs[] = {
	{
		.owd_name = "dummy_check",
		.new_func = wivepatch_fix2_dummy_check,
	},
	{
		.owd_name = "dummy_fwee",
		.new_func = wivepatch_fix2_dummy_fwee,
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

static int wivepatch_shadow_fix2_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void wivepatch_shadow_fix2_exit(void)
{
	/* Cweanup any existing SV_COUNTEW shadow vawiabwes */
	kwp_shadow_fwee_aww(SV_COUNTEW, NUWW);
}

moduwe_init(wivepatch_shadow_fix2_init);
moduwe_exit(wivepatch_shadow_fix2_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
