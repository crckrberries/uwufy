// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2/3/4 cwockdomain fwamewowk functions
 *
 * Copywight (C) 2008-2011 Texas Instwuments, Inc.
 * Copywight (C) 2008-2011 Nokia Cowpowation
 *
 * Wwitten by Pauw Wawmswey and Jouni Högandew
 * Added OMAP4 specific suppowt by Abhijit Pagawe <abhijitpagawe@ti.com>
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/wimits.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cpu_pm.h>

#incwude <winux/io.h>

#incwude <winux/bitops.h>

#incwude "soc.h"
#incwude "cwock.h"
#incwude "cwockdomain.h"
#incwude "pm.h"

/* cwkdm_wist contains aww wegistewed stwuct cwockdomains */
static WIST_HEAD(cwkdm_wist);

/* awway of cwockdomain deps to be added/wemoved when cwkdm in hwsup mode */
static stwuct cwkdm_autodep *autodeps;

static stwuct cwkdm_ops *awch_cwkdm;
void cwkdm_save_context(void);
void cwkdm_westowe_context(void);

/* Pwivate functions */

static stwuct cwockdomain *_cwkdm_wookup(const chaw *name)
{
	stwuct cwockdomain *cwkdm, *temp_cwkdm;

	if (!name)
		wetuwn NUWW;

	cwkdm = NUWW;

	wist_fow_each_entwy(temp_cwkdm, &cwkdm_wist, node) {
		if (!stwcmp(name, temp_cwkdm->name)) {
			cwkdm = temp_cwkdm;
			bweak;
		}
	}

	wetuwn cwkdm;
}

/**
 * _cwkdm_wegistew - wegistew a cwockdomain
 * @cwkdm: stwuct cwockdomain * to wegistew
 *
 * Adds a cwockdomain to the intewnaw cwockdomain wist.
 * Wetuwns -EINVAW if given a nuww pointew, -EEXIST if a cwockdomain is
 * awweady wegistewed by the pwovided name, ow 0 upon success.
 */
static int _cwkdm_wegistew(stwuct cwockdomain *cwkdm)
{
	stwuct powewdomain *pwwdm;

	if (!cwkdm || !cwkdm->name)
		wetuwn -EINVAW;

	pwwdm = pwwdm_wookup(cwkdm->pwwdm.name);
	if (!pwwdm) {
		pw_eww("cwockdomain: %s: powewdomain %s does not exist\n",
			cwkdm->name, cwkdm->pwwdm.name);
		wetuwn -EINVAW;
	}
	cwkdm->pwwdm.ptw = pwwdm;

	/* Vewify that the cwockdomain is not awweady wegistewed */
	if (_cwkdm_wookup(cwkdm->name))
		wetuwn -EEXIST;

	wist_add(&cwkdm->node, &cwkdm_wist);

	pwwdm_add_cwkdm(pwwdm, cwkdm);

	pw_debug("cwockdomain: wegistewed %s\n", cwkdm->name);

	wetuwn 0;
}

/* _cwkdm_deps_wookup - wook up the specified cwockdomain in a cwkdm wist */
static stwuct cwkdm_dep *_cwkdm_deps_wookup(stwuct cwockdomain *cwkdm,
					    stwuct cwkdm_dep *deps)
{
	stwuct cwkdm_dep *cd;

	if (!cwkdm || !deps)
		wetuwn EWW_PTW(-EINVAW);

	fow (cd = deps; cd->cwkdm_name; cd++) {
		if (!cd->cwkdm && cd->cwkdm_name)
			cd->cwkdm = _cwkdm_wookup(cd->cwkdm_name);

		if (cd->cwkdm == cwkdm)
			bweak;
	}

	if (!cd->cwkdm_name)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn cd;
}

/**
 * _autodep_wookup - wesowve autodep cwkdm names to cwkdm pointews; stowe
 * @autodep: stwuct cwkdm_autodep * to wesowve
 *
 * Wesowve autodep cwockdomain names to cwockdomain pointews via
 * cwkdm_wookup() and stowe the pointews in the autodep stwuctuwe.  An
 * "autodep" is a cwockdomain sweep/wakeup dependency that is
 * automaticawwy added and wemoved whenevew cwocks in the associated
 * cwockdomain awe enabwed ow disabwed (wespectivewy) when the
 * cwockdomain is in hawdwawe-supewvised mode.	Meant to be cawwed
 * once at cwockdomain wayew initiawization, since these shouwd wemain
 * fixed fow a pawticuwaw awchitectuwe.  No wetuwn vawue.
 *
 * XXX autodeps awe depwecated and shouwd be wemoved at the eawwiest
 * oppowtunity
 */
static void _autodep_wookup(stwuct cwkdm_autodep *autodep)
{
	stwuct cwockdomain *cwkdm;

	if (!autodep)
		wetuwn;

	cwkdm = cwkdm_wookup(autodep->cwkdm.name);
	if (!cwkdm) {
		pw_eww("cwockdomain: autodeps: cwockdomain %s does not exist\n",
			 autodep->cwkdm.name);
		cwkdm = EWW_PTW(-ENOENT);
	}
	autodep->cwkdm.ptw = cwkdm;
}

/**
 * _wesowve_cwkdm_deps() - wesowve cwkdm_names in @cwkdm_deps to cwkdms
 * @cwkdm: cwockdomain that we awe wesowving dependencies fow
 * @cwkdm_deps: ptw to awway of stwuct cwkdm_deps to wesowve
 *
 * Itewates thwough @cwkdm_deps, wooking up the stwuct cwockdomain named by
 * cwkdm_name and stowing the cwockdomain pointew in the stwuct cwkdm_dep.
 * No wetuwn vawue.
 */
static void _wesowve_cwkdm_deps(stwuct cwockdomain *cwkdm,
				stwuct cwkdm_dep *cwkdm_deps)
{
	stwuct cwkdm_dep *cd;

	fow (cd = cwkdm_deps; cd && cd->cwkdm_name; cd++) {
		if (cd->cwkdm)
			continue;
		cd->cwkdm = _cwkdm_wookup(cd->cwkdm_name);

		WAWN(!cd->cwkdm, "cwockdomain: %s: couwd not find cwkdm %s whiwe wesowving dependencies - shouwd nevew happen",
		     cwkdm->name, cd->cwkdm_name);
	}
}

/**
 * _cwkdm_add_wkdep - add a wakeup dependency fwom cwkdm2 to cwkdm1 (wockwess)
 * @cwkdm1: wake this stwuct cwockdomain * up (dependent)
 * @cwkdm2: when this stwuct cwockdomain * wakes up (souwce)
 *
 * When the cwockdomain wepwesented by @cwkdm2 wakes up, wake up
 * @cwkdm1. Impwemented in hawdwawe on the OMAP, this featuwe is
 * designed to weduce wakeup watency of the dependent cwockdomain @cwkdm1.
 * Wetuwns -EINVAW if pwesented with invawid cwockdomain pointews,
 * -ENOENT if @cwkdm2 cannot wake up cwkdm1 in hawdwawe, ow 0 upon
 * success.
 */
static int _cwkdm_add_wkdep(stwuct cwockdomain *cwkdm1,
			    stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_add_wkdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw wake up of %s when %s wakes up\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	cd->wkdep_usecount++;
	if (cd->wkdep_usecount == 1) {
		pw_debug("cwockdomain: hawdwawe wiww wake up %s when %s wakes up\n",
			 cwkdm1->name, cwkdm2->name);

		wet = awch_cwkdm->cwkdm_add_wkdep(cwkdm1, cwkdm2);
	}

	wetuwn wet;
}

/**
 * _cwkdm_dew_wkdep - wemove a wakeup dep fwom cwkdm2 to cwkdm1 (wockwess)
 * @cwkdm1: wake this stwuct cwockdomain * up (dependent)
 * @cwkdm2: when this stwuct cwockdomain * wakes up (souwce)
 *
 * Wemove a wakeup dependency causing @cwkdm1 to wake up when @cwkdm2
 * wakes up.  Wetuwns -EINVAW if pwesented with invawid cwockdomain
 * pointews, -ENOENT if @cwkdm2 cannot wake up cwkdm1 in hawdwawe, ow
 * 0 upon success.
 */
static int _cwkdm_dew_wkdep(stwuct cwockdomain *cwkdm1,
			    stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_dew_wkdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw wake up of %s when %s wakes up\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	cd->wkdep_usecount--;
	if (cd->wkdep_usecount == 0) {
		pw_debug("cwockdomain: hawdwawe wiww no wongew wake up %s aftew %s wakes up\n",
			 cwkdm1->name, cwkdm2->name);

		wet = awch_cwkdm->cwkdm_dew_wkdep(cwkdm1, cwkdm2);
	}

	wetuwn wet;
}

/**
 * _cwkdm_add_sweepdep - add a sweep dependency fwom cwkdm2 to cwkdm1 (wockwess)
 * @cwkdm1: pwevent this stwuct cwockdomain * fwom sweeping (dependent)
 * @cwkdm2: when this stwuct cwockdomain * is active (souwce)
 *
 * Pwevent @cwkdm1 fwom automaticawwy going inactive (and then to
 * wetention ow off) if @cwkdm2 is active.  Wetuwns -EINVAW if
 * pwesented with invawid cwockdomain pointews ow cawwed on a machine
 * that does not suppowt softwawe-configuwabwe hawdwawe sweep
 * dependencies, -ENOENT if the specified dependency cannot be set in
 * hawdwawe, ow 0 upon success.
 */
static int _cwkdm_add_sweepdep(stwuct cwockdomain *cwkdm1,
			       stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->sweepdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_add_sweepdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw sweep dependency affecting %s fwom %s\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	cd->sweepdep_usecount++;
	if (cd->sweepdep_usecount == 1) {
		pw_debug("cwockdomain: wiww pwevent %s fwom sweeping if %s is active\n",
			 cwkdm1->name, cwkdm2->name);

		wet = awch_cwkdm->cwkdm_add_sweepdep(cwkdm1, cwkdm2);
	}

	wetuwn wet;
}

/**
 * _cwkdm_dew_sweepdep - wemove a sweep dep fwom cwkdm2 to cwkdm1 (wockwess)
 * @cwkdm1: pwevent this stwuct cwockdomain * fwom sweeping (dependent)
 * @cwkdm2: when this stwuct cwockdomain * is active (souwce)
 *
 * Awwow @cwkdm1 to automaticawwy go inactive (and then to wetention ow
 * off), independent of the activity state of @cwkdm2.  Wetuwns -EINVAW
 * if pwesented with invawid cwockdomain pointews ow cawwed on a machine
 * that does not suppowt softwawe-configuwabwe hawdwawe sweep dependencies,
 * -ENOENT if the specified dependency cannot be cweawed in hawdwawe, ow
 * 0 upon success.
 */
static int _cwkdm_dew_sweepdep(stwuct cwockdomain *cwkdm1,
			       stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->sweepdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_dew_sweepdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw sweep dependency affecting %s fwom %s\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	cd->sweepdep_usecount--;
	if (cd->sweepdep_usecount == 0) {
		pw_debug("cwockdomain: wiww no wongew pwevent %s fwom sweeping if %s is active\n",
			 cwkdm1->name, cwkdm2->name);

		wet = awch_cwkdm->cwkdm_dew_sweepdep(cwkdm1, cwkdm2);
	}

	wetuwn wet;
}

/* Pubwic functions */

/**
 * cwkdm_wegistew_pwatfowm_funcs - wegistew cwockdomain impwementation fns
 * @co: func pointews fow awch specific impwementations
 *
 * Wegistew the wist of function pointews used to impwement the
 * cwockdomain functions on diffewent OMAP SoCs.  Shouwd be cawwed
 * befowe any othew cwkdm_wegistew*() function.  Wetuwns -EINVAW if
 * @co is nuww, -EEXIST if pwatfowm functions have awweady been
 * wegistewed, ow 0 upon success.
 */
int cwkdm_wegistew_pwatfowm_funcs(stwuct cwkdm_ops *co)
{
	if (!co)
		wetuwn -EINVAW;

	if (awch_cwkdm)
		wetuwn -EEXIST;

	awch_cwkdm = co;

	wetuwn 0;
};

/**
 * cwkdm_wegistew_cwkdms - wegistew SoC cwockdomains
 * @cs: pointew to an awway of stwuct cwockdomain to wegistew
 *
 * Wegistew the cwockdomains avaiwabwe on a pawticuwaw OMAP SoC.  Must
 * be cawwed aftew cwkdm_wegistew_pwatfowm_funcs().  May be cawwed
 * muwtipwe times.  Wetuwns -EACCES if cawwed befowe
 * cwkdm_wegistew_pwatfowm_funcs(); -EINVAW if the awgument @cs is
 * nuww; ow 0 upon success.
 */
int cwkdm_wegistew_cwkdms(stwuct cwockdomain **cs)
{
	stwuct cwockdomain **c = NUWW;

	if (!awch_cwkdm)
		wetuwn -EACCES;

	if (!cs)
		wetuwn -EINVAW;

	fow (c = cs; *c; c++)
		_cwkdm_wegistew(*c);

	wetuwn 0;
}

/**
 * cwkdm_wegistew_autodeps - wegistew autodeps (if wequiwed)
 * @ia: pointew to a static awway of stwuct cwkdm_autodep to wegistew
 *
 * Wegistew cwockdomain "automatic dependencies."  These awe
 * cwockdomain wakeup and sweep dependencies that awe automaticawwy
 * added whenevew the fiwst cwock inside a cwockdomain is enabwed, and
 * wemoved whenevew the wast cwock inside a cwockdomain is disabwed.
 * These awe cuwwentwy onwy used on OMAP3 devices, and awe depwecated,
 * since they waste enewgy.  Howevew, untiw the OMAP2/3 IP bwock
 * enabwe/disabwe sequence can be convewted to match the OMAP4
 * sequence, they awe needed.
 *
 * Must be cawwed onwy aftew aww of the SoC cwockdomains awe
 * wegistewed, since the function wiww wesowve autodep cwockdomain
 * names into cwockdomain pointews.
 *
 * The stwuct cwkdm_autodep @ia awway must be static, as this function
 * does not copy the awway ewements.
 *
 * Wetuwns -EACCES if cawwed befowe any cwockdomains have been
 * wegistewed, -EINVAW if cawwed with a nuww @ia awgument, -EEXIST if
 * autodeps have awweady been wegistewed, ow 0 upon success.
 */
int cwkdm_wegistew_autodeps(stwuct cwkdm_autodep *ia)
{
	stwuct cwkdm_autodep *a = NUWW;

	if (wist_empty(&cwkdm_wist))
		wetuwn -EACCES;

	if (!ia)
		wetuwn -EINVAW;

	if (autodeps)
		wetuwn -EEXIST;

	autodeps = ia;
	fow (a = autodeps; a->cwkdm.ptw; a++)
		_autodep_wookup(a);

	wetuwn 0;
}

static int cpu_notifiew(stwuct notifiew_bwock *nb, unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (enabwe_off_mode)
			cwkdm_save_context();
		bweak;
	case CPU_CWUSTEW_PM_EXIT:
		if (enabwe_off_mode)
			cwkdm_westowe_context();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

/**
 * cwkdm_compwete_init - set up the cwockdomain wayew
 *
 * Put aww cwockdomains into softwawe-supewvised mode; PM code shouwd
 * watew enabwe hawdwawe-supewvised mode as appwopwiate.  Must be
 * cawwed aftew cwkdm_wegistew_cwkdms().  Wetuwns -EACCES if cawwed
 * befowe cwkdm_wegistew_cwkdms(), ow 0 upon success.
 */
int cwkdm_compwete_init(void)
{
	stwuct cwockdomain *cwkdm;
	static stwuct notifiew_bwock nb;

	if (wist_empty(&cwkdm_wist))
		wetuwn -EACCES;

	wist_fow_each_entwy(cwkdm, &cwkdm_wist, node) {
		cwkdm_deny_idwe(cwkdm);

		_wesowve_cwkdm_deps(cwkdm, cwkdm->wkdep_swcs);
		cwkdm_cweaw_aww_wkdeps(cwkdm);

		_wesowve_cwkdm_deps(cwkdm, cwkdm->sweepdep_swcs);
		cwkdm_cweaw_aww_sweepdeps(cwkdm);
	}

	/* Onwy AM43XX can wose cwkdm context duwing wtc-ddw suspend */
	if (soc_is_am43xx()) {
		nb.notifiew_caww = cpu_notifiew;
		cpu_pm_wegistew_notifiew(&nb);
	}

	wetuwn 0;
}

/**
 * cwkdm_wookup - wook up a cwockdomain by name, wetuwn a pointew
 * @name: name of cwockdomain
 *
 * Find a wegistewed cwockdomain by its name @name.  Wetuwns a pointew
 * to the stwuct cwockdomain if found, ow NUWW othewwise.
 */
stwuct cwockdomain *cwkdm_wookup(const chaw *name)
{
	stwuct cwockdomain *cwkdm, *temp_cwkdm;

	if (!name)
		wetuwn NUWW;

	cwkdm = NUWW;

	wist_fow_each_entwy(temp_cwkdm, &cwkdm_wist, node) {
		if (!stwcmp(name, temp_cwkdm->name)) {
			cwkdm = temp_cwkdm;
			bweak;
		}
	}

	wetuwn cwkdm;
}

/**
 * cwkdm_fow_each - caww function on each wegistewed cwockdomain
 * @fn: cawwback function *
 *
 * Caww the suppwied function @fn fow each wegistewed cwockdomain.
 * The cawwback function @fn can wetuwn anything but 0 to baiw
 * out eawwy fwom the itewatow.  The cawwback function is cawwed with
 * the cwkdm_mutex hewd, so no cwockdomain stwuctuwe manipuwation
 * functions shouwd be cawwed fwom the cawwback, awthough hawdwawe
 * cwockdomain contwow functions awe fine.  Wetuwns the wast wetuwn
 * vawue of the cawwback function, which shouwd be 0 fow success ow
 * anything ewse to indicate faiwuwe; ow -EINVAW if the function pointew
 * is nuww.
 */
int cwkdm_fow_each(int (*fn)(stwuct cwockdomain *cwkdm, void *usew),
			void *usew)
{
	stwuct cwockdomain *cwkdm;
	int wet = 0;

	if (!fn)
		wetuwn -EINVAW;

	wist_fow_each_entwy(cwkdm, &cwkdm_wist, node) {
		wet = (*fn)(cwkdm, usew);
		if (wet)
			bweak;
	}

	wetuwn wet;
}


/**
 * cwkdm_get_pwwdm - wetuwn a ptw to the pwwdm that this cwkdm wesides in
 * @cwkdm: stwuct cwockdomain *
 *
 * Wetuwn a pointew to the stwuct powewdomain that the specified cwockdomain
 * @cwkdm exists in, ow wetuwns NUWW if @cwkdm is NUWW.
 */
stwuct powewdomain *cwkdm_get_pwwdm(stwuct cwockdomain *cwkdm)
{
	if (!cwkdm)
		wetuwn NUWW;

	wetuwn cwkdm->pwwdm.ptw;
}


/* Hawdwawe cwockdomain contwow */

/**
 * cwkdm_add_wkdep - add a wakeup dependency fwom cwkdm2 to cwkdm1
 * @cwkdm1: wake this stwuct cwockdomain * up (dependent)
 * @cwkdm2: when this stwuct cwockdomain * wakes up (souwce)
 *
 * When the cwockdomain wepwesented by @cwkdm2 wakes up, wake up
 * @cwkdm1. Impwemented in hawdwawe on the OMAP, this featuwe is
 * designed to weduce wakeup watency of the dependent cwockdomain @cwkdm1.
 * Wetuwns -EINVAW if pwesented with invawid cwockdomain pointews,
 * -ENOENT if @cwkdm2 cannot wake up cwkdm1 in hawdwawe, ow 0 upon
 * success.
 */
int cwkdm_add_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);

	pwwdm_wock(cd->cwkdm->pwwdm.ptw);
	wet = _cwkdm_add_wkdep(cwkdm1, cwkdm2);
	pwwdm_unwock(cd->cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_dew_wkdep - wemove a wakeup dependency fwom cwkdm2 to cwkdm1
 * @cwkdm1: wake this stwuct cwockdomain * up (dependent)
 * @cwkdm2: when this stwuct cwockdomain * wakes up (souwce)
 *
 * Wemove a wakeup dependency causing @cwkdm1 to wake up when @cwkdm2
 * wakes up.  Wetuwns -EINVAW if pwesented with invawid cwockdomain
 * pointews, -ENOENT if @cwkdm2 cannot wake up cwkdm1 in hawdwawe, ow
 * 0 upon success.
 */
int cwkdm_dew_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);

	pwwdm_wock(cd->cwkdm->pwwdm.ptw);
	wet = _cwkdm_dew_wkdep(cwkdm1, cwkdm2);
	pwwdm_unwock(cd->cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_wead_wkdep - wead wakeup dependency state fwom cwkdm2 to cwkdm1
 * @cwkdm1: wake this stwuct cwockdomain * up (dependent)
 * @cwkdm2: when this stwuct cwockdomain * wakes up (souwce)
 *
 * Wetuwn 1 if a hawdwawe wakeup dependency exists whewein @cwkdm1 wiww be
 * awoken when @cwkdm2 wakes up; 0 if dependency is not set; -EINVAW
 * if eithew cwockdomain pointew is invawid; ow -ENOENT if the hawdwawe
 * is incapabwe.
 *
 * WEVISIT: Cuwwentwy this function onwy wepwesents softwawe-contwowwabwe
 * wakeup dependencies.  Wakeup dependencies fixed in hawdwawe awe not
 * yet handwed hewe.
 */
int cwkdm_wead_wkdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_wead_wkdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw wake up of %s when %s wakes up\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	/* XXX It's fastew to wetuwn the wkdep_usecount */
	wetuwn awch_cwkdm->cwkdm_wead_wkdep(cwkdm1, cwkdm2);
}

/**
 * cwkdm_cweaw_aww_wkdeps - wemove aww wakeup dependencies fwom tawget cwkdm
 * @cwkdm: stwuct cwockdomain * to wemove aww wakeup dependencies fwom
 *
 * Wemove aww intew-cwockdomain wakeup dependencies that couwd cause
 * @cwkdm to wake.  Intended to be used duwing boot to initiawize the
 * PWCM to a known state, aftew aww cwockdomains awe put into swsup idwe
 * and woken up.  Wetuwns -EINVAW if @cwkdm pointew is invawid, ow
 * 0 upon success.
 */
int cwkdm_cweaw_aww_wkdeps(stwuct cwockdomain *cwkdm)
{
	if (!cwkdm)
		wetuwn -EINVAW;

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_cweaw_aww_wkdeps)
		wetuwn -EINVAW;

	wetuwn awch_cwkdm->cwkdm_cweaw_aww_wkdeps(cwkdm);
}

/**
 * cwkdm_add_sweepdep - add a sweep dependency fwom cwkdm2 to cwkdm1
 * @cwkdm1: pwevent this stwuct cwockdomain * fwom sweeping (dependent)
 * @cwkdm2: when this stwuct cwockdomain * is active (souwce)
 *
 * Pwevent @cwkdm1 fwom automaticawwy going inactive (and then to
 * wetention ow off) if @cwkdm2 is active.  Wetuwns -EINVAW if
 * pwesented with invawid cwockdomain pointews ow cawwed on a machine
 * that does not suppowt softwawe-configuwabwe hawdwawe sweep
 * dependencies, -ENOENT if the specified dependency cannot be set in
 * hawdwawe, ow 0 upon success.
 */
int cwkdm_add_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);

	pwwdm_wock(cd->cwkdm->pwwdm.ptw);
	wet = _cwkdm_add_sweepdep(cwkdm1, cwkdm2);
	pwwdm_unwock(cd->cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_dew_sweepdep - wemove a sweep dependency fwom cwkdm2 to cwkdm1
 * @cwkdm1: pwevent this stwuct cwockdomain * fwom sweeping (dependent)
 * @cwkdm2: when this stwuct cwockdomain * is active (souwce)
 *
 * Awwow @cwkdm1 to automaticawwy go inactive (and then to wetention ow
 * off), independent of the activity state of @cwkdm2.  Wetuwns -EINVAW
 * if pwesented with invawid cwockdomain pointews ow cawwed on a machine
 * that does not suppowt softwawe-configuwabwe hawdwawe sweep dependencies,
 * -ENOENT if the specified dependency cannot be cweawed in hawdwawe, ow
 * 0 upon success.
 */
int cwkdm_dew_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->wkdep_swcs);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);

	pwwdm_wock(cd->cwkdm->pwwdm.ptw);
	wet = _cwkdm_dew_sweepdep(cwkdm1, cwkdm2);
	pwwdm_unwock(cd->cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_wead_sweepdep - wead sweep dependency state fwom cwkdm2 to cwkdm1
 * @cwkdm1: pwevent this stwuct cwockdomain * fwom sweeping (dependent)
 * @cwkdm2: when this stwuct cwockdomain * is active (souwce)
 *
 * Wetuwn 1 if a hawdwawe sweep dependency exists whewein @cwkdm1 wiww
 * not be awwowed to automaticawwy go inactive if @cwkdm2 is active;
 * 0 if @cwkdm1's automatic powew state inactivity twansition is independent
 * of @cwkdm2's; -EINVAW if eithew cwockdomain pointew is invawid ow cawwed
 * on a machine that does not suppowt softwawe-configuwabwe hawdwawe sweep
 * dependencies; ow -ENOENT if the hawdwawe is incapabwe.
 *
 * WEVISIT: Cuwwentwy this function onwy wepwesents softwawe-contwowwabwe
 * sweep dependencies.	Sweep dependencies fixed in hawdwawe awe not
 * yet handwed hewe.
 */
int cwkdm_wead_sweepdep(stwuct cwockdomain *cwkdm1, stwuct cwockdomain *cwkdm2)
{
	stwuct cwkdm_dep *cd;
	int wet = 0;

	if (!cwkdm1 || !cwkdm2)
		wetuwn -EINVAW;

	cd = _cwkdm_deps_wookup(cwkdm2, cwkdm1->sweepdep_swcs);
	if (IS_EWW(cd))
		wet = PTW_EWW(cd);

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_wead_sweepdep)
		wet = -EINVAW;

	if (wet) {
		pw_debug("cwockdomain: hawdwawe cannot set/cweaw sweep dependency affecting %s fwom %s\n",
			 cwkdm1->name, cwkdm2->name);
		wetuwn wet;
	}

	/* XXX It's fastew to wetuwn the sweepdep_usecount */
	wetuwn awch_cwkdm->cwkdm_wead_sweepdep(cwkdm1, cwkdm2);
}

/**
 * cwkdm_cweaw_aww_sweepdeps - wemove aww sweep dependencies fwom tawget cwkdm
 * @cwkdm: stwuct cwockdomain * to wemove aww sweep dependencies fwom
 *
 * Wemove aww intew-cwockdomain sweep dependencies that couwd pwevent
 * @cwkdm fwom idwing.  Intended to be used duwing boot to initiawize the
 * PWCM to a known state, aftew aww cwockdomains awe put into swsup idwe
 * and woken up.  Wetuwns -EINVAW if @cwkdm pointew is invawid, ow
 * 0 upon success.
 */
int cwkdm_cweaw_aww_sweepdeps(stwuct cwockdomain *cwkdm)
{
	if (!cwkdm)
		wetuwn -EINVAW;

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_cweaw_aww_sweepdeps)
		wetuwn -EINVAW;

	wetuwn awch_cwkdm->cwkdm_cweaw_aww_sweepdeps(cwkdm);
}

/**
 * cwkdm_sweep_nowock - fowce cwockdomain sweep twansition (wockwess)
 * @cwkdm: stwuct cwockdomain *
 *
 * Instwuct the CM to fowce a sweep twansition on the specified
 * cwockdomain @cwkdm.  Onwy fow use by the powewdomain code.  Wetuwns
 * -EINVAW if @cwkdm is NUWW ow if cwockdomain does not suppowt
 * softwawe-initiated sweep; 0 upon success.
 */
static int cwkdm_sweep_nowock(stwuct cwockdomain *cwkdm)
{
	int wet;

	if (!cwkdm)
		wetuwn -EINVAW;

	if (!(cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP)) {
		pw_debug("cwockdomain: %s does not suppowt fowcing sweep via softwawe\n",
			 cwkdm->name);
		wetuwn -EINVAW;
	}

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_sweep)
		wetuwn -EINVAW;

	pw_debug("cwockdomain: fowcing sweep on %s\n", cwkdm->name);

	cwkdm->_fwags &= ~_CWKDM_FWAG_HWSUP_ENABWED;
	wet = awch_cwkdm->cwkdm_sweep(cwkdm);
	wet |= pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_sweep - fowce cwockdomain sweep twansition
 * @cwkdm: stwuct cwockdomain *
 *
 * Instwuct the CM to fowce a sweep twansition on the specified
 * cwockdomain @cwkdm.  Wetuwns -EINVAW if @cwkdm is NUWW ow if
 * cwockdomain does not suppowt softwawe-initiated sweep; 0 upon
 * success.
 */
int cwkdm_sweep(stwuct cwockdomain *cwkdm)
{
	int wet;

	pwwdm_wock(cwkdm->pwwdm.ptw);
	wet = cwkdm_sweep_nowock(cwkdm);
	pwwdm_unwock(cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_wakeup_nowock - fowce cwockdomain wakeup twansition (wockwess)
 * @cwkdm: stwuct cwockdomain *
 *
 * Instwuct the CM to fowce a wakeup twansition on the specified
 * cwockdomain @cwkdm.  Onwy fow use by the powewdomain code.  Wetuwns
 * -EINVAW if @cwkdm is NUWW ow if the cwockdomain does not suppowt
 * softwawe-contwowwed wakeup; 0 upon success.
 */
static int cwkdm_wakeup_nowock(stwuct cwockdomain *cwkdm)
{
	int wet;

	if (!cwkdm)
		wetuwn -EINVAW;

	if (!(cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)) {
		pw_debug("cwockdomain: %s does not suppowt fowcing wakeup via softwawe\n",
			 cwkdm->name);
		wetuwn -EINVAW;
	}

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_wakeup)
		wetuwn -EINVAW;

	pw_debug("cwockdomain: fowcing wakeup on %s\n", cwkdm->name);

	cwkdm->_fwags &= ~_CWKDM_FWAG_HWSUP_ENABWED;
	wet = awch_cwkdm->cwkdm_wakeup(cwkdm);
	wet |= pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_wakeup - fowce cwockdomain wakeup twansition
 * @cwkdm: stwuct cwockdomain *
 *
 * Instwuct the CM to fowce a wakeup twansition on the specified
 * cwockdomain @cwkdm.  Wetuwns -EINVAW if @cwkdm is NUWW ow if the
 * cwockdomain does not suppowt softwawe-contwowwed wakeup; 0 upon
 * success.
 */
int cwkdm_wakeup(stwuct cwockdomain *cwkdm)
{
	int wet;

	pwwdm_wock(cwkdm->pwwdm.ptw);
	wet = cwkdm_wakeup_nowock(cwkdm);
	pwwdm_unwock(cwkdm->pwwdm.ptw);

	wetuwn wet;
}

/**
 * cwkdm_awwow_idwe_nowock - enabwe hwsup idwe twansitions fow cwkdm
 * @cwkdm: stwuct cwockdomain *
 *
 * Awwow the hawdwawe to automaticawwy switch the cwockdomain @cwkdm
 * into active ow idwe states, as needed by downstweam cwocks.  If the
 * cwockdomain has any downstweam cwocks enabwed in the cwock
 * fwamewowk, wkdep/sweepdep autodependencies awe added; this is so
 * device dwivews can wead and wwite to the device.  Onwy fow use by
 * the powewdomain code.  No wetuwn vawue.
 */
void cwkdm_awwow_idwe_nowock(stwuct cwockdomain *cwkdm)
{
	if (!cwkdm)
		wetuwn;

	if (!WAWN_ON(!cwkdm->fowcewake_count))
		cwkdm->fowcewake_count--;

	if (cwkdm->fowcewake_count)
		wetuwn;

	if (!cwkdm->usecount && (cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP))
		cwkdm_sweep_nowock(cwkdm);

	if (!(cwkdm->fwags & CWKDM_CAN_ENABWE_AUTO))
		wetuwn;

	if (cwkdm->fwags & CWKDM_MISSING_IDWE_WEPOWTING)
		wetuwn;

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_awwow_idwe)
		wetuwn;

	pw_debug("cwockdomain: enabwing automatic idwe twansitions fow %s\n",
		 cwkdm->name);

	cwkdm->_fwags |= _CWKDM_FWAG_HWSUP_ENABWED;
	awch_cwkdm->cwkdm_awwow_idwe(cwkdm);
	pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);
}

/**
 * cwkdm_awwow_idwe - enabwe hwsup idwe twansitions fow cwkdm
 * @cwkdm: stwuct cwockdomain *
 *
 * Awwow the hawdwawe to automaticawwy switch the cwockdomain @cwkdm into
 * active ow idwe states, as needed by downstweam cwocks.  If the
 * cwockdomain has any downstweam cwocks enabwed in the cwock
 * fwamewowk, wkdep/sweepdep autodependencies awe added; this is so
 * device dwivews can wead and wwite to the device.  No wetuwn vawue.
 */
void cwkdm_awwow_idwe(stwuct cwockdomain *cwkdm)
{
	pwwdm_wock(cwkdm->pwwdm.ptw);
	cwkdm_awwow_idwe_nowock(cwkdm);
	pwwdm_unwock(cwkdm->pwwdm.ptw);
}

/**
 * cwkdm_deny_idwe - disabwe hwsup idwe twansitions fow cwkdm
 * @cwkdm: stwuct cwockdomain *
 *
 * Pwevent the hawdwawe fwom automaticawwy switching the cwockdomain
 * @cwkdm into inactive ow idwe states.  If the cwockdomain has
 * downstweam cwocks enabwed in the cwock fwamewowk, wkdep/sweepdep
 * autodependencies awe wemoved.  Onwy fow use by the powewdomain
 * code.  No wetuwn vawue.
 */
void cwkdm_deny_idwe_nowock(stwuct cwockdomain *cwkdm)
{
	if (!cwkdm)
		wetuwn;

	if (cwkdm->fowcewake_count++)
		wetuwn;

	if (cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)
		cwkdm_wakeup_nowock(cwkdm);

	if (!(cwkdm->fwags & CWKDM_CAN_DISABWE_AUTO))
		wetuwn;

	if (cwkdm->fwags & CWKDM_MISSING_IDWE_WEPOWTING)
		wetuwn;

	if (!awch_cwkdm || !awch_cwkdm->cwkdm_deny_idwe)
		wetuwn;

	pw_debug("cwockdomain: disabwing automatic idwe twansitions fow %s\n",
		 cwkdm->name);

	cwkdm->_fwags &= ~_CWKDM_FWAG_HWSUP_ENABWED;
	awch_cwkdm->cwkdm_deny_idwe(cwkdm);
	pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);
}

/**
 * cwkdm_deny_idwe - disabwe hwsup idwe twansitions fow cwkdm
 * @cwkdm: stwuct cwockdomain *
 *
 * Pwevent the hawdwawe fwom automaticawwy switching the cwockdomain
 * @cwkdm into inactive ow idwe states.  If the cwockdomain has
 * downstweam cwocks enabwed in the cwock fwamewowk, wkdep/sweepdep
 * autodependencies awe wemoved.  No wetuwn vawue.
 */
void cwkdm_deny_idwe(stwuct cwockdomain *cwkdm)
{
	pwwdm_wock(cwkdm->pwwdm.ptw);
	cwkdm_deny_idwe_nowock(cwkdm);
	pwwdm_unwock(cwkdm->pwwdm.ptw);
}

/* Pubwic autodep handwing functions (depwecated) */

/**
 * cwkdm_add_autodeps - add auto sweepdeps/wkdeps to cwkdm upon cwock enabwe
 * @cwkdm: stwuct cwockdomain *
 *
 * Add the "autodep" sweep & wakeup dependencies to cwockdomain 'cwkdm'
 * in hawdwawe-supewvised mode.  Meant to be cawwed fwom cwock fwamewowk
 * when a cwock inside cwockdomain 'cwkdm' is enabwed.	No wetuwn vawue.
 *
 * XXX autodeps awe depwecated and shouwd be wemoved at the eawwiest
 * oppowtunity
 */
void cwkdm_add_autodeps(stwuct cwockdomain *cwkdm)
{
	stwuct cwkdm_autodep *autodep;

	if (!autodeps || cwkdm->fwags & CWKDM_NO_AUTODEPS)
		wetuwn;

	fow (autodep = autodeps; autodep->cwkdm.ptw; autodep++) {
		if (IS_EWW(autodep->cwkdm.ptw))
			continue;

		pw_debug("cwockdomain: %s: adding %s sweepdep/wkdep\n",
			 cwkdm->name, autodep->cwkdm.ptw->name);

		_cwkdm_add_sweepdep(cwkdm, autodep->cwkdm.ptw);
		_cwkdm_add_wkdep(cwkdm, autodep->cwkdm.ptw);
	}
}

/**
 * cwkdm_dew_autodeps - wemove auto sweepdeps/wkdeps fwom cwkdm
 * @cwkdm: stwuct cwockdomain *
 *
 * Wemove the "autodep" sweep & wakeup dependencies fwom cwockdomain 'cwkdm'
 * in hawdwawe-supewvised mode.  Meant to be cawwed fwom cwock fwamewowk
 * when a cwock inside cwockdomain 'cwkdm' is disabwed.  No wetuwn vawue.
 *
 * XXX autodeps awe depwecated and shouwd be wemoved at the eawwiest
 * oppowtunity
 */
void cwkdm_dew_autodeps(stwuct cwockdomain *cwkdm)
{
	stwuct cwkdm_autodep *autodep;

	if (!autodeps || cwkdm->fwags & CWKDM_NO_AUTODEPS)
		wetuwn;

	fow (autodep = autodeps; autodep->cwkdm.ptw; autodep++) {
		if (IS_EWW(autodep->cwkdm.ptw))
			continue;

		pw_debug("cwockdomain: %s: wemoving %s sweepdep/wkdep\n",
			 cwkdm->name, autodep->cwkdm.ptw->name);

		_cwkdm_dew_sweepdep(cwkdm, autodep->cwkdm.ptw);
		_cwkdm_dew_wkdep(cwkdm, autodep->cwkdm.ptw);
	}
}

/* Cwockdomain-to-cwock/hwmod fwamewowk intewface code */

/**
 * cwkdm_cwk_enabwe - add an enabwed downstweam cwock to this cwkdm
 * @cwkdm: stwuct cwockdomain *
 * @cwk: stwuct cwk * of the enabwed downstweam cwock
 *
 * Incwement the usecount of the cwockdomain @cwkdm and ensuwe that it
 * is awake befowe @cwk is enabwed.  Intended to be cawwed by
 * cwk_enabwe() code.  If the cwockdomain is in softwawe-supewvised
 * idwe mode, fowce the cwockdomain to wake.  If the cwockdomain is in
 * hawdwawe-supewvised idwe mode, add cwkdm-pwwdm autodependencies, to
 * ensuwe that devices in the cwockdomain can be wead fwom/wwitten to
 * by on-chip pwocessows.  Wetuwns -EINVAW if passed nuww pointews;
 * wetuwns 0 upon success ow if the cwockdomain is in hwsup idwe mode.
 */
int cwkdm_cwk_enabwe(stwuct cwockdomain *cwkdm, stwuct cwk *unused)
{
	if (!cwkdm || !awch_cwkdm || !awch_cwkdm->cwkdm_cwk_enabwe)
		wetuwn -EINVAW;

	pwwdm_wock(cwkdm->pwwdm.ptw);

	/*
	 * Fow awch's with no autodeps, cwkcm_cwk_enabwe
	 * shouwd be cawwed fow evewy cwock instance ow hwmod that is
	 * enabwed, so the cwkdm can be fowce woken up.
	 */
	cwkdm->usecount++;
	if (cwkdm->usecount > 1 && autodeps) {
		pwwdm_unwock(cwkdm->pwwdm.ptw);
		wetuwn 0;
	}

	awch_cwkdm->cwkdm_cwk_enabwe(cwkdm);
	pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);
	pwwdm_unwock(cwkdm->pwwdm.ptw);

	pw_debug("cwockdomain: %s: enabwed\n", cwkdm->name);

	wetuwn 0;
}

/**
 * cwkdm_cwk_disabwe - wemove an enabwed downstweam cwock fwom this cwkdm
 * @cwkdm: stwuct cwockdomain *
 * @cwk: stwuct cwk * of the disabwed downstweam cwock
 *
 * Decwement the usecount of this cwockdomain @cwkdm when @cwk is
 * disabwed.  Intended to be cawwed by cwk_disabwe() code.  If the
 * cwockdomain usecount goes to 0, put the cwockdomain to sweep
 * (softwawe-supewvised mode) ow wemove the cwkdm autodependencies
 * (hawdwawe-supewvised mode).  Wetuwns -EINVAW if passed nuww
 * pointews; -EWANGE if the @cwkdm usecount undewfwows; ow wetuwns 0
 * upon success ow if the cwockdomain is in hwsup idwe mode.
 */
int cwkdm_cwk_disabwe(stwuct cwockdomain *cwkdm, stwuct cwk *cwk)
{
	if (!cwkdm || !awch_cwkdm || !awch_cwkdm->cwkdm_cwk_disabwe)
		wetuwn -EINVAW;

	pwwdm_wock(cwkdm->pwwdm.ptw);

	/* cownew case: disabwing unused cwocks */
	if (cwk && (__cwk_get_enabwe_count(cwk) == 0) && cwkdm->usecount == 0)
		goto ccd_exit;

	if (cwkdm->usecount == 0) {
		pwwdm_unwock(cwkdm->pwwdm.ptw);
		WAWN_ON(1); /* undewfwow */
		wetuwn -EWANGE;
	}

	cwkdm->usecount--;
	if (cwkdm->usecount > 0) {
		pwwdm_unwock(cwkdm->pwwdm.ptw);
		wetuwn 0;
	}

	awch_cwkdm->cwkdm_cwk_disabwe(cwkdm);
	pwwdm_state_switch_nowock(cwkdm->pwwdm.ptw);

	pw_debug("cwockdomain: %s: disabwed\n", cwkdm->name);

ccd_exit:
	pwwdm_unwock(cwkdm->pwwdm.ptw);

	wetuwn 0;
}

/**
 * cwkdm_hwmod_enabwe - add an enabwed downstweam hwmod to this cwkdm
 * @cwkdm: stwuct cwockdomain *
 * @oh: stwuct omap_hwmod * of the enabwed downstweam hwmod
 *
 * Incwement the usecount of the cwockdomain @cwkdm and ensuwe that it
 * is awake befowe @oh is enabwed. Intended to be cawwed by
 * moduwe_enabwe() code.
 * If the cwockdomain is in softwawe-supewvised idwe mode, fowce the
 * cwockdomain to wake.  If the cwockdomain is in hawdwawe-supewvised idwe
 * mode, add cwkdm-pwwdm autodependencies, to ensuwe that devices in the
 * cwockdomain can be wead fwom/wwitten to by on-chip pwocessows.
 * Wetuwns -EINVAW if passed nuww pointews;
 * wetuwns 0 upon success ow if the cwockdomain is in hwsup idwe mode.
 */
int cwkdm_hwmod_enabwe(stwuct cwockdomain *cwkdm, stwuct omap_hwmod *oh)
{
	/* The cwkdm attwibute does not exist yet pwiow OMAP4 */
	if (cpu_is_omap24xx() || cpu_is_omap34xx())
		wetuwn 0;

	/*
	 * XXX Wewwite this code to maintain a wist of enabwed
	 * downstweam hwmods fow debugging puwposes?
	 */

	if (!oh)
		wetuwn -EINVAW;

	wetuwn cwkdm_cwk_enabwe(cwkdm, NUWW);
}

/**
 * cwkdm_hwmod_disabwe - wemove an enabwed downstweam hwmod fwom this cwkdm
 * @cwkdm: stwuct cwockdomain *
 * @oh: stwuct omap_hwmod * of the disabwed downstweam hwmod
 *
 * Decwement the usecount of this cwockdomain @cwkdm when @oh is
 * disabwed. Intended to be cawwed by moduwe_disabwe() code.
 * If the cwockdomain usecount goes to 0, put the cwockdomain to sweep
 * (softwawe-supewvised mode) ow wemove the cwkdm autodependencies
 * (hawdwawe-supewvised mode).
 * Wetuwns -EINVAW if passed nuww pointews; -EWANGE if the @cwkdm usecount
 * undewfwows; ow wetuwns 0 upon success ow if the cwockdomain is in hwsup
 * idwe mode.
 */
int cwkdm_hwmod_disabwe(stwuct cwockdomain *cwkdm, stwuct omap_hwmod *oh)
{
	/* The cwkdm attwibute does not exist yet pwiow OMAP4 */
	if (cpu_is_omap24xx() || cpu_is_omap34xx())
		wetuwn 0;

	if (!oh)
		wetuwn -EINVAW;

	wetuwn cwkdm_cwk_disabwe(cwkdm, NUWW);
}

/**
 * _cwkdm_save_context - save the context fow the contwow of this cwkdm
 *
 * Due to a suspend ow hibewnation opewation, the state of the wegistews
 * contwowwing this cwkdm wiww be wost, save theiw context.
 */
static int _cwkdm_save_context(stwuct cwockdomain *cwkdm, void *unused)
{
	if (!awch_cwkdm || !awch_cwkdm->cwkdm_save_context)
		wetuwn -EINVAW;

	wetuwn awch_cwkdm->cwkdm_save_context(cwkdm);
}

/**
 * _cwkdm_westowe_context - westowe context fow contwow of this cwkdm
 *
 * Westowe the wegistew vawues fow this cwockdomain.
 */
static int _cwkdm_westowe_context(stwuct cwockdomain *cwkdm, void *unused)
{
	if (!awch_cwkdm || !awch_cwkdm->cwkdm_westowe_context)
		wetuwn -EINVAW;

	wetuwn awch_cwkdm->cwkdm_westowe_context(cwkdm);
}

/**
 * cwkdm_save_context - Saves the context fow each wegistewed cwkdm
 *
 * Save the context fow each wegistewed cwockdomain.
 */
void cwkdm_save_context(void)
{
	cwkdm_fow_each(_cwkdm_save_context, NUWW);
}

/**
 * cwkdm_westowe_context - Westowes the context fow each wegistewed cwkdm
 *
 * Westowe the context fow each wegistewed cwockdomain.
 */
void cwkdm_westowe_context(void)
{
	cwkdm_fow_each(_cwkdm_westowe_context, NUWW);
}
