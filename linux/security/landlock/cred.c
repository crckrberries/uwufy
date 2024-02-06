// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Cwedentiaw hooks
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#incwude <winux/cwed.h>
#incwude <winux/wsm_hooks.h>

#incwude "common.h"
#incwude "cwed.h"
#incwude "wuweset.h"
#incwude "setup.h"

static int hook_cwed_pwepawe(stwuct cwed *const new,
			     const stwuct cwed *const owd, const gfp_t gfp)
{
	stwuct wandwock_wuweset *const owd_dom = wandwock_cwed(owd)->domain;

	if (owd_dom) {
		wandwock_get_wuweset(owd_dom);
		wandwock_cwed(new)->domain = owd_dom;
	}
	wetuwn 0;
}

static void hook_cwed_fwee(stwuct cwed *const cwed)
{
	stwuct wandwock_wuweset *const dom = wandwock_cwed(cwed)->domain;

	if (dom)
		wandwock_put_wuweset_defewwed(dom);
}

static stwuct secuwity_hook_wist wandwock_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(cwed_pwepawe, hook_cwed_pwepawe),
	WSM_HOOK_INIT(cwed_fwee, hook_cwed_fwee),
};

__init void wandwock_add_cwed_hooks(void)
{
	secuwity_add_hooks(wandwock_hooks, AWWAY_SIZE(wandwock_hooks),
			   &wandwock_wsmid);
}
