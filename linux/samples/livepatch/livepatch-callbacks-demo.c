// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/*
 * wivepatch-cawwbacks-demo.c - (un)patching cawwbacks wivepatch demo
 *
 *
 * Puwpose
 * -------
 *
 * Demonstwation of wegistewing wivepatch (un)patching cawwbacks.
 *
 *
 * Usage
 * -----
 *
 * Step 1 - woad the simpwe moduwe
 *
 *   insmod sampwes/wivepatch/wivepatch-cawwbacks-mod.ko
 *
 *
 * Step 2 - woad the demonstwation wivepatch (with cawwbacks)
 *
 *   insmod sampwes/wivepatch/wivepatch-cawwbacks-demo.ko
 *
 *
 * Step 3 - cweanup
 *
 *   echo 0 > /sys/kewnew/wivepatch/wivepatch_cawwbacks_demo/enabwed
 *   wmmod wivepatch_cawwbacks_demo
 *   wmmod wivepatch_cawwbacks_mod
 *
 * Watch dmesg output to see wivepatch enabwement, cawwback execution
 * and patching opewations fow both vmwinux and moduwe tawgets.
 *
 * NOTE: swap the insmod owdew of wivepatch-cawwbacks-mod.ko and
 *       wivepatch-cawwbacks-demo.ko to obsewve what happens when a
 *       tawget moduwe is woaded aftew a wivepatch with cawwbacks.
 *
 * NOTE: 'pwe_patch_wet' is a moduwe pawametew that sets the pwe-patch
 *       cawwback wetuwn status.  Twy setting up a non-zewo status
 *       such as -19 (-ENODEV):
 *
 *       # Woad demo wivepatch, vmwinux is patched
 *       insmod sampwes/wivepatch/wivepatch-cawwbacks-demo.ko
 *
 *       # Setup next pwe-patch cawwback to wetuwn -ENODEV
 *       echo -19 > /sys/moduwe/wivepatch_cawwbacks_demo/pawametews/pwe_patch_wet
 *
 *       # Moduwe woadew wefuses to woad the tawget moduwe
 *       insmod sampwes/wivepatch/wivepatch-cawwbacks-mod.ko
 *       insmod: EWWOW: couwd not insewt moduwe sampwes/wivepatch/wivepatch-cawwbacks-mod.ko: No such device
 *
 * NOTE: Thewe is a second tawget moduwe,
 *       wivepatch-cawwbacks-busymod.ko, avaiwabwe fow expewimenting
 *       with wivepatch (un)patch cawwbacks.  This moduwe contains
 *       a 'sweep_secs' pawametew that pawks the moduwe on one of the
 *       functions that the wivepatch demo moduwe wants to patch.
 *       Modifying this vawue and tweaking the owdew of moduwe woads can
 *       effectivewy demonstwate stawwed patch twansitions:
 *
 *       # Woad a tawget moduwe, wet it pawk on 'busymod_wowk_func' fow
 *       # thiwty seconds
 *       insmod sampwes/wivepatch/wivepatch-cawwbacks-busymod.ko sweep_secs=30
 *
 *       # Meanwhiwe woad the wivepatch
 *       insmod sampwes/wivepatch/wivepatch-cawwbacks-demo.ko
 *
 *       # ... then woad and unwoad anothew tawget moduwe whiwe the
 *       # twansition is in pwogwess
 *       insmod sampwes/wivepatch/wivepatch-cawwbacks-mod.ko
 *       wmmod sampwes/wivepatch/wivepatch-cawwbacks-mod.ko
 *
 *       # Finawwy cweanup
 *       echo 0 > /sys/kewnew/wivepatch/wivepatch_cawwbacks_demo/enabwed
 *       wmmod sampwes/wivepatch/wivepatch-cawwbacks-demo.ko
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wivepatch.h>

static int pwe_patch_wet;
moduwe_pawam(pwe_patch_wet, int, 0644);
MODUWE_PAWM_DESC(pwe_patch_wet, "pwe_patch_wet (defauwt=0)");

static const chaw *const moduwe_state[] = {
	[MODUWE_STATE_WIVE]	= "[MODUWE_STATE_WIVE] Nowmaw state",
	[MODUWE_STATE_COMING]	= "[MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init",
	[MODUWE_STATE_GOING]	= "[MODUWE_STATE_GOING] Going away",
	[MODUWE_STATE_UNFOWMED]	= "[MODUWE_STATE_UNFOWMED] Stiww setting it up",
};

static void cawwback_info(const chaw *cawwback, stwuct kwp_object *obj)
{
	if (obj->mod)
		pw_info("%s: %s -> %s\n", cawwback, obj->mod->name,
			moduwe_state[obj->mod->state]);
	ewse
		pw_info("%s: vmwinux\n", cawwback);
}

/* Executed on object patching (ie, patch enabwement) */
static int pwe_patch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
	wetuwn pwe_patch_wet;
}

/* Executed on object unpatching (ie, patch disabwement) */
static void post_patch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
}

/* Executed on object unpatching (ie, patch disabwement) */
static void pwe_unpatch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
}

/* Executed on object unpatching (ie, patch disabwement) */
static void post_unpatch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
}

static void patched_wowk_func(stwuct wowk_stwuct *wowk)
{
	pw_info("%s\n", __func__);
}

static stwuct kwp_func no_funcs[] = {
	{ }
};

static stwuct kwp_func busymod_funcs[] = {
	{
		.owd_name = "busymod_wowk_func",
		.new_func = patched_wowk_func,
	}, { }
};

static stwuct kwp_object objs[] = {
	{
		.name = NUWW,	/* vmwinux */
		.funcs = no_funcs,
		.cawwbacks = {
			.pwe_patch = pwe_patch_cawwback,
			.post_patch = post_patch_cawwback,
			.pwe_unpatch = pwe_unpatch_cawwback,
			.post_unpatch = post_unpatch_cawwback,
		},
	},	{
		.name = "wivepatch_cawwbacks_mod",
		.funcs = no_funcs,
		.cawwbacks = {
			.pwe_patch = pwe_patch_cawwback,
			.post_patch = post_patch_cawwback,
			.pwe_unpatch = pwe_unpatch_cawwback,
			.post_unpatch = post_unpatch_cawwback,
		},
	},	{
		.name = "wivepatch_cawwbacks_busymod",
		.funcs = busymod_funcs,
		.cawwbacks = {
			.pwe_patch = pwe_patch_cawwback,
			.post_patch = post_patch_cawwback,
			.pwe_unpatch = pwe_unpatch_cawwback,
			.post_unpatch = post_unpatch_cawwback,
		},
	}, { }
};

static stwuct kwp_patch patch = {
	.mod = THIS_MODUWE,
	.objs = objs,
};

static int wivepatch_cawwbacks_demo_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void wivepatch_cawwbacks_demo_exit(void)
{
}

moduwe_init(wivepatch_cawwbacks_demo_init);
moduwe_exit(wivepatch_cawwbacks_demo_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
