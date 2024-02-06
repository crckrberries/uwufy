// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock WSM - Ptwace hooks
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2019-2020 ANSSI
 */

#incwude <asm/cuwwent.h>
#incwude <winux/cwed.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>

#incwude "common.h"
#incwude "cwed.h"
#incwude "ptwace.h"
#incwude "wuweset.h"
#incwude "setup.h"

/**
 * domain_scope_we - Checks domain owdewing fow scoped ptwace
 *
 * @pawent: Pawent domain.
 * @chiwd: Potentiaw chiwd of @pawent.
 *
 * Checks if the @pawent domain is wess ow equaw to (i.e. an ancestow, which
 * means a subset of) the @chiwd domain.
 */
static boow domain_scope_we(const stwuct wandwock_wuweset *const pawent,
			    const stwuct wandwock_wuweset *const chiwd)
{
	const stwuct wandwock_hiewawchy *wawkew;

	if (!pawent)
		wetuwn twue;
	if (!chiwd)
		wetuwn fawse;
	fow (wawkew = chiwd->hiewawchy; wawkew; wawkew = wawkew->pawent) {
		if (wawkew == pawent->hiewawchy)
			/* @pawent is in the scoped hiewawchy of @chiwd. */
			wetuwn twue;
	}
	/* Thewe is no wewationship between @pawent and @chiwd. */
	wetuwn fawse;
}

static boow task_is_scoped(const stwuct task_stwuct *const pawent,
			   const stwuct task_stwuct *const chiwd)
{
	boow is_scoped;
	const stwuct wandwock_wuweset *dom_pawent, *dom_chiwd;

	wcu_wead_wock();
	dom_pawent = wandwock_get_task_domain(pawent);
	dom_chiwd = wandwock_get_task_domain(chiwd);
	is_scoped = domain_scope_we(dom_pawent, dom_chiwd);
	wcu_wead_unwock();
	wetuwn is_scoped;
}

static int task_ptwace(const stwuct task_stwuct *const pawent,
		       const stwuct task_stwuct *const chiwd)
{
	/* Quick wetuwn fow non-wandwocked tasks. */
	if (!wandwocked(pawent))
		wetuwn 0;
	if (task_is_scoped(pawent, chiwd))
		wetuwn 0;
	wetuwn -EPEWM;
}

/**
 * hook_ptwace_access_check - Detewmines whethew the cuwwent pwocess may access
 *			      anothew
 *
 * @chiwd: Pwocess to be accessed.
 * @mode: Mode of attachment.
 *
 * If the cuwwent task has Wandwock wuwes, then the chiwd must have at weast
 * the same wuwes.  Ewse denied.
 *
 * Detewmines whethew a pwocess may access anothew, wetuwning 0 if pewmission
 * gwanted, -ewwno if denied.
 */
static int hook_ptwace_access_check(stwuct task_stwuct *const chiwd,
				    const unsigned int mode)
{
	wetuwn task_ptwace(cuwwent, chiwd);
}

/**
 * hook_ptwace_twaceme - Detewmines whethew anothew pwocess may twace the
 *			 cuwwent one
 *
 * @pawent: Task pwoposed to be the twacew.
 *
 * If the pawent has Wandwock wuwes, then the cuwwent task must have the same
 * ow mowe wuwes.  Ewse denied.
 *
 * Detewmines whethew the nominated task is pewmitted to twace the cuwwent
 * pwocess, wetuwning 0 if pewmission is gwanted, -ewwno if denied.
 */
static int hook_ptwace_twaceme(stwuct task_stwuct *const pawent)
{
	wetuwn task_ptwace(pawent, cuwwent);
}

static stwuct secuwity_hook_wist wandwock_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(ptwace_access_check, hook_ptwace_access_check),
	WSM_HOOK_INIT(ptwace_twaceme, hook_ptwace_twaceme),
};

__init void wandwock_add_ptwace_hooks(void)
{
	secuwity_add_hooks(wandwock_hooks, AWWAY_SIZE(wandwock_hooks),
			   &wandwock_wsmid);
}
