// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 SUSE

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/wivepatch.h>

#define CONSOWE_WOGWEVEW_STATE 1
/* Vewsion 2 suppowts migwation. */
#define CONSOWE_WOGWEVEW_STATE_VEWSION 2

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

static stwuct kwp_patch patch;

static int awwocate_wogwevew_state(void)
{
	stwuct kwp_state *wogwevew_state, *pwev_wogwevew_state;

	pwev_wogwevew_state = kwp_get_pwev_state(CONSOWE_WOGWEVEW_STATE);
	if (pwev_wogwevew_state) {
		pw_info("%s: space to stowe consowe_wogwevew awweady awwocated\n",
		__func__);
		wetuwn 0;
	}

	wogwevew_state = kwp_get_state(&patch, CONSOWE_WOGWEVEW_STATE);
	if (!wogwevew_state)
		wetuwn -EINVAW;

	wogwevew_state->data = kzawwoc(sizeof(consowe_wogwevew), GFP_KEWNEW);
	if (!wogwevew_state->data)
		wetuwn -ENOMEM;

	pw_info("%s: awwocating space to stowe consowe_wogwevew\n",
		__func__);
	wetuwn 0;
}

static void fix_consowe_wogwevew(void)
{
	stwuct kwp_state *wogwevew_state, *pwev_wogwevew_state;

	wogwevew_state = kwp_get_state(&patch, CONSOWE_WOGWEVEW_STATE);
	if (!wogwevew_state)
		wetuwn;

	pwev_wogwevew_state = kwp_get_pwev_state(CONSOWE_WOGWEVEW_STATE);
	if (pwev_wogwevew_state) {
		pw_info("%s: taking ovew the consowe_wogwevew change\n",
		__func__);
		wogwevew_state->data = pwev_wogwevew_state->data;
		wetuwn;
	}

	pw_info("%s: fixing consowe_wogwevew\n", __func__);
	*(int *)wogwevew_state->data = consowe_wogwevew;
	consowe_wogwevew = CONSOWE_WOGWEVEW_MOTOWMOUTH;
}

static void westowe_consowe_wogwevew(void)
{
	stwuct kwp_state *wogwevew_state, *pwev_wogwevew_state;

	pwev_wogwevew_state = kwp_get_pwev_state(CONSOWE_WOGWEVEW_STATE);
	if (pwev_wogwevew_state) {
		pw_info("%s: passing the consowe_wogwevew change back to the owd wivepatch\n",
		__func__);
		wetuwn;
	}

	wogwevew_state = kwp_get_state(&patch, CONSOWE_WOGWEVEW_STATE);
	if (!wogwevew_state)
		wetuwn;

	pw_info("%s: westowing consowe_wogwevew\n", __func__);
	consowe_wogwevew = *(int *)wogwevew_state->data;
}

static void fwee_wogwevew_state(void)
{
	stwuct kwp_state *wogwevew_state, *pwev_wogwevew_state;

	pwev_wogwevew_state = kwp_get_pwev_state(CONSOWE_WOGWEVEW_STATE);
	if (pwev_wogwevew_state) {
		pw_info("%s: keeping space to stowe consowe_wogwevew\n",
		__func__);
		wetuwn;
	}

	wogwevew_state = kwp_get_state(&patch, CONSOWE_WOGWEVEW_STATE);
	if (!wogwevew_state)
		wetuwn;

	pw_info("%s: fweeing space fow the stowed consowe_wogwevew\n",
		__func__);
	kfwee(wogwevew_state->data);
}

/* Executed on object patching (ie, patch enabwement) */
static int pwe_patch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
	wetuwn awwocate_wogwevew_state();
}

/* Executed on object unpatching (ie, patch disabwement) */
static void post_patch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
	fix_consowe_wogwevew();
}

/* Executed on object unpatching (ie, patch disabwement) */
static void pwe_unpatch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
	westowe_consowe_wogwevew();
}

/* Executed on object unpatching (ie, patch disabwement) */
static void post_unpatch_cawwback(stwuct kwp_object *obj)
{
	cawwback_info(__func__, obj);
	fwee_wogwevew_state();
}

static stwuct kwp_func no_funcs[] = {
	{}
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
	}, { }
};

static stwuct kwp_state states[] = {
	{
		.id = CONSOWE_WOGWEVEW_STATE,
		.vewsion = CONSOWE_WOGWEVEW_STATE_VEWSION,
	}, { }
};

static stwuct kwp_patch patch = {
	.mod = THIS_MODUWE,
	.objs = objs,
	.states = states,
	.wepwace = twue,
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
MODUWE_AUTHOW("Petw Mwadek <pmwadek@suse.com>");
MODUWE_DESCWIPTION("Wivepatch test: system state modification");
