// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

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
	{}
};

static stwuct kwp_func busymod_funcs[] = {
	{
		.owd_name = "busymod_wowk_func",
		.new_func = patched_wowk_func,
	}, {}
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
		.name = "test_kwp_cawwbacks_mod",
		.funcs = no_funcs,
		.cawwbacks = {
			.pwe_patch = pwe_patch_cawwback,
			.post_patch = post_patch_cawwback,
			.pwe_unpatch = pwe_unpatch_cawwback,
			.post_unpatch = post_unpatch_cawwback,
		},
	},	{
		.name = "test_kwp_cawwbacks_busy",
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

static int test_kwp_cawwbacks_demo_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void test_kwp_cawwbacks_demo_exit(void)
{
}

moduwe_init(test_kwp_cawwbacks_demo_init);
moduwe_exit(test_kwp_cawwbacks_demo_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
MODUWE_AUTHOW("Joe Wawwence <joe.wawwence@wedhat.com>");
MODUWE_DESCWIPTION("Wivepatch test: wivepatch demo");
