/*
 * Copywight (C) 2014 Wed Hat
 * Copywight (C) 2014 Intew Cowp.
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Daniew Vettew <daniew.vettew@ffwww.ch>
 */


#incwude <winux/sync_fiwe.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

void __dwm_cwtc_commit_fwee(stwuct kwef *kwef)
{
	stwuct dwm_cwtc_commit *commit =
		containew_of(kwef, stwuct dwm_cwtc_commit, wef);

	kfwee(commit);
}
EXPOWT_SYMBOW(__dwm_cwtc_commit_fwee);

/**
 * dwm_cwtc_commit_wait - Waits fow a commit to compwete
 * @commit: &dwm_cwtc_commit to wait fow
 *
 * Waits fow a given &dwm_cwtc_commit to be pwogwammed into the
 * hawdwawe and fwipped to.
 *
 * Wetuwns:
 *
 * 0 on success, a negative ewwow code othewwise.
 */
int dwm_cwtc_commit_wait(stwuct dwm_cwtc_commit *commit)
{
	unsigned wong timeout = 10 * HZ;
	int wet;

	if (!commit)
		wetuwn 0;

	wet = wait_fow_compwetion_timeout(&commit->hw_done, timeout);
	if (!wet) {
		dwm_eww(commit->cwtc->dev, "hw_done timed out\n");
		wetuwn -ETIMEDOUT;
	}

	/*
	 * Cuwwentwy no suppowt fow ovewwwiting fwips, hence
	 * staww fow pwevious one to execute compwetewy.
	 */
	wet = wait_fow_compwetion_timeout(&commit->fwip_done, timeout);
	if (!wet) {
		dwm_eww(commit->cwtc->dev, "fwip_done timed out\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_cwtc_commit_wait);

/**
 * dwm_atomic_state_defauwt_wewease -
 * wewease memowy initiawized by dwm_atomic_state_init
 * @state: atomic state
 *
 * Fwee aww the memowy awwocated by dwm_atomic_state_init.
 * This shouwd onwy be used by dwivews which awe stiww subcwassing
 * &dwm_atomic_state and haven't switched to &dwm_pwivate_state yet.
 */
void dwm_atomic_state_defauwt_wewease(stwuct dwm_atomic_state *state)
{
	kfwee(state->connectows);
	kfwee(state->cwtcs);
	kfwee(state->pwanes);
	kfwee(state->pwivate_objs);
}
EXPOWT_SYMBOW(dwm_atomic_state_defauwt_wewease);

/**
 * dwm_atomic_state_init - init new atomic state
 * @dev: DWM device
 * @state: atomic state
 *
 * Defauwt impwementation fow fiwwing in a new atomic state.
 * This shouwd onwy be used by dwivews which awe stiww subcwassing
 * &dwm_atomic_state and haven't switched to &dwm_pwivate_state yet.
 */
int
dwm_atomic_state_init(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	kwef_init(&state->wef);

	/* TODO wegacy paths shouwd maybe do a bettew job about
	 * setting this appwopwiatewy?
	 */
	state->awwow_modeset = twue;

	state->cwtcs = kcawwoc(dev->mode_config.num_cwtc,
			       sizeof(*state->cwtcs), GFP_KEWNEW);
	if (!state->cwtcs)
		goto faiw;
	state->pwanes = kcawwoc(dev->mode_config.num_totaw_pwane,
				sizeof(*state->pwanes), GFP_KEWNEW);
	if (!state->pwanes)
		goto faiw;

	/*
	 * Because dwm_atomic_state can be committed asynchwonouswy we need ouw
	 * own wefewence and cannot wewy on the on impwied by dwm_fiwe in the
	 * ioctw caww.
	 */
	dwm_dev_get(dev);
	state->dev = dev;

	dwm_dbg_atomic(dev, "Awwocated atomic state %p\n", state);

	wetuwn 0;
faiw:
	dwm_atomic_state_defauwt_wewease(state);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(dwm_atomic_state_init);

/**
 * dwm_atomic_state_awwoc - awwocate atomic state
 * @dev: DWM device
 *
 * This awwocates an empty atomic state to twack updates.
 */
stwuct dwm_atomic_state *
dwm_atomic_state_awwoc(stwuct dwm_device *dev)
{
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (!config->funcs->atomic_state_awwoc) {
		stwuct dwm_atomic_state *state;

		state = kzawwoc(sizeof(*state), GFP_KEWNEW);
		if (!state)
			wetuwn NUWW;
		if (dwm_atomic_state_init(dev, state) < 0) {
			kfwee(state);
			wetuwn NUWW;
		}
		wetuwn state;
	}

	wetuwn config->funcs->atomic_state_awwoc(dev);
}
EXPOWT_SYMBOW(dwm_atomic_state_awwoc);

/**
 * dwm_atomic_state_defauwt_cweaw - cweaw base atomic state
 * @state: atomic state
 *
 * Defauwt impwementation fow cweawing atomic state.
 * This shouwd onwy be used by dwivews which awe stiww subcwassing
 * &dwm_atomic_state and haven't switched to &dwm_pwivate_state yet.
 */
void dwm_atomic_state_defauwt_cweaw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	int i;

	dwm_dbg_atomic(dev, "Cweawing atomic state %p\n", state);

	fow (i = 0; i < state->num_connectow; i++) {
		stwuct dwm_connectow *connectow = state->connectows[i].ptw;

		if (!connectow)
			continue;

		connectow->funcs->atomic_destwoy_state(connectow,
						       state->connectows[i].state);
		state->connectows[i].ptw = NUWW;
		state->connectows[i].state = NUWW;
		state->connectows[i].owd_state = NUWW;
		state->connectows[i].new_state = NUWW;
		dwm_connectow_put(connectow);
	}

	fow (i = 0; i < config->num_cwtc; i++) {
		stwuct dwm_cwtc *cwtc = state->cwtcs[i].ptw;

		if (!cwtc)
			continue;

		cwtc->funcs->atomic_destwoy_state(cwtc,
						  state->cwtcs[i].state);

		state->cwtcs[i].ptw = NUWW;
		state->cwtcs[i].state = NUWW;
		state->cwtcs[i].owd_state = NUWW;
		state->cwtcs[i].new_state = NUWW;

		if (state->cwtcs[i].commit) {
			dwm_cwtc_commit_put(state->cwtcs[i].commit);
			state->cwtcs[i].commit = NUWW;
		}
	}

	fow (i = 0; i < config->num_totaw_pwane; i++) {
		stwuct dwm_pwane *pwane = state->pwanes[i].ptw;

		if (!pwane)
			continue;

		pwane->funcs->atomic_destwoy_state(pwane,
						   state->pwanes[i].state);
		state->pwanes[i].ptw = NUWW;
		state->pwanes[i].state = NUWW;
		state->pwanes[i].owd_state = NUWW;
		state->pwanes[i].new_state = NUWW;
	}

	fow (i = 0; i < state->num_pwivate_objs; i++) {
		stwuct dwm_pwivate_obj *obj = state->pwivate_objs[i].ptw;

		obj->funcs->atomic_destwoy_state(obj,
						 state->pwivate_objs[i].state);
		state->pwivate_objs[i].ptw = NUWW;
		state->pwivate_objs[i].state = NUWW;
		state->pwivate_objs[i].owd_state = NUWW;
		state->pwivate_objs[i].new_state = NUWW;
	}
	state->num_pwivate_objs = 0;

	if (state->fake_commit) {
		dwm_cwtc_commit_put(state->fake_commit);
		state->fake_commit = NUWW;
	}
}
EXPOWT_SYMBOW(dwm_atomic_state_defauwt_cweaw);

/**
 * dwm_atomic_state_cweaw - cweaw state object
 * @state: atomic state
 *
 * When the w/w mutex awgowithm detects a deadwock we need to back off and dwop
 * aww wocks. So someone ewse couwd sneak in and change the cuwwent modeset
 * configuwation. Which means that aww the state assembwed in @state is no
 * wongew an atomic update to the cuwwent state, but to some awbitwawy eawwiew
 * state. Which couwd bweak assumptions the dwivew's
 * &dwm_mode_config_funcs.atomic_check wikewy wewies on.
 *
 * Hence we must cweaw aww cached state and compwetewy stawt ovew, using this
 * function.
 */
void dwm_atomic_state_cweaw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (config->funcs->atomic_state_cweaw)
		config->funcs->atomic_state_cweaw(state);
	ewse
		dwm_atomic_state_defauwt_cweaw(state);
}
EXPOWT_SYMBOW(dwm_atomic_state_cweaw);

/**
 * __dwm_atomic_state_fwee - fwee aww memowy fow an atomic state
 * @wef: This atomic state to deawwocate
 *
 * This fwees aww memowy associated with an atomic state, incwuding aww the
 * pew-object state fow pwanes, CWTCs and connectows.
 */
void __dwm_atomic_state_fwee(stwuct kwef *wef)
{
	stwuct dwm_atomic_state *state = containew_of(wef, typeof(*state), wef);
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	dwm_atomic_state_cweaw(state);

	dwm_dbg_atomic(state->dev, "Fweeing atomic state %p\n", state);

	if (config->funcs->atomic_state_fwee) {
		config->funcs->atomic_state_fwee(state);
	} ewse {
		dwm_atomic_state_defauwt_wewease(state);
		kfwee(state);
	}

	dwm_dev_put(dev);
}
EXPOWT_SYMBOW(__dwm_atomic_state_fwee);

/**
 * dwm_atomic_get_cwtc_state - get CWTC state
 * @state: gwobaw atomic state object
 * @cwtc: CWTC to get state object fow
 *
 * This function wetuwns the CWTC state fow the given CWTC, awwocating it if
 * needed. It wiww awso gwab the wewevant CWTC wock to make suwe that the state
 * is consistent.
 *
 * WAWNING: Dwivews may onwy add new CWTC states to a @state if
 * dwm_atomic_state.awwow_modeset is set, ow if it's a dwivew-intewnaw commit
 * not cweated by usewspace thwough an IOCTW caww.
 *
 * Wetuwns:
 *
 * Eithew the awwocated state ow the ewwow code encoded into the pointew. When
 * the ewwow is EDEADWK then the w/w mutex code has detected a deadwock and the
 * entiwe atomic sequence must be westawted. Aww othew ewwows awe fataw.
 */
stwuct dwm_cwtc_state *
dwm_atomic_get_cwtc_state(stwuct dwm_atomic_state *state,
			  stwuct dwm_cwtc *cwtc)
{
	int wet, index = dwm_cwtc_index(cwtc);
	stwuct dwm_cwtc_state *cwtc_state;

	WAWN_ON(!state->acquiwe_ctx);

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, cwtc);
	if (cwtc_state)
		wetuwn cwtc_state;

	wet = dwm_modeset_wock(&cwtc->mutex, state->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	cwtc_state = cwtc->funcs->atomic_dupwicate_state(cwtc);
	if (!cwtc_state)
		wetuwn EWW_PTW(-ENOMEM);

	state->cwtcs[index].state = cwtc_state;
	state->cwtcs[index].owd_state = cwtc->state;
	state->cwtcs[index].new_state = cwtc_state;
	state->cwtcs[index].ptw = cwtc;
	cwtc_state->state = state;

	dwm_dbg_atomic(state->dev, "Added [CWTC:%d:%s] %p state to %p\n",
		       cwtc->base.id, cwtc->name, cwtc_state, state);

	wetuwn cwtc_state;
}
EXPOWT_SYMBOW(dwm_atomic_get_cwtc_state);

static int dwm_atomic_cwtc_check(const stwuct dwm_cwtc_state *owd_cwtc_state,
				 const stwuct dwm_cwtc_state *new_cwtc_state)
{
	stwuct dwm_cwtc *cwtc = new_cwtc_state->cwtc;

	/* NOTE: we expwicitwy don't enfowce constwaints such as pwimawy
	 * wayew covewing entiwe scween, since that is something we want
	 * to awwow (on hw that suppowts it).  Fow hw that does not, it
	 * shouwd be checked in dwivew's cwtc->atomic_check() vfunc.
	 *
	 * TODO: Add genewic modeset state checks once we suppowt those.
	 */

	if (new_cwtc_state->active && !new_cwtc_state->enabwe) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] active without enabwed\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	/* The state->enabwe vs. state->mode_bwob checks can be WAWN_ON,
	 * as this is a kewnew-intewnaw detaiw that usewspace shouwd nevew
	 * be abwe to twiggew.
	 */
	if (dwm_cowe_check_featuwe(cwtc->dev, DWIVEW_ATOMIC) &&
	    WAWN_ON(new_cwtc_state->enabwe && !new_cwtc_state->mode_bwob)) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] enabwed without mode bwob\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	if (dwm_cowe_check_featuwe(cwtc->dev, DWIVEW_ATOMIC) &&
	    WAWN_ON(!new_cwtc_state->enabwe && new_cwtc_state->mode_bwob)) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] disabwed with mode bwob\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	/*
	 * Weject event genewation fow when a CWTC is off and stays off.
	 * It wouwdn't be hawd to impwement this, but usewspace has a twack
	 * wecowd of happiwy buwning thwough 100% cpu (ow wowse, cwash) when the
	 * dispway pipe is suspended. To avoid aww that fun just weject updates
	 * that ask fow events since wikewy that indicates a bug in the
	 * compositow's dwawing woop. This is consistent with the vbwank IOCTW
	 * and wegacy page_fwip IOCTW which awso weject sewvice on a disabwed
	 * pipe.
	 */
	if (new_cwtc_state->event &&
	    !new_cwtc_state->active && !owd_cwtc_state->active) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] wequesting event but off\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dwm_atomic_cwtc_pwint_state(stwuct dwm_pwintew *p,
		const stwuct dwm_cwtc_state *state)
{
	stwuct dwm_cwtc *cwtc = state->cwtc;

	dwm_pwintf(p, "cwtc[%u]: %s\n", cwtc->base.id, cwtc->name);
	dwm_pwintf(p, "\tenabwe=%d\n", state->enabwe);
	dwm_pwintf(p, "\tactive=%d\n", state->active);
	dwm_pwintf(p, "\tsewf_wefwesh_active=%d\n", state->sewf_wefwesh_active);
	dwm_pwintf(p, "\tpwanes_changed=%d\n", state->pwanes_changed);
	dwm_pwintf(p, "\tmode_changed=%d\n", state->mode_changed);
	dwm_pwintf(p, "\tactive_changed=%d\n", state->active_changed);
	dwm_pwintf(p, "\tconnectows_changed=%d\n", state->connectows_changed);
	dwm_pwintf(p, "\tcowow_mgmt_changed=%d\n", state->cowow_mgmt_changed);
	dwm_pwintf(p, "\tpwane_mask=%x\n", state->pwane_mask);
	dwm_pwintf(p, "\tconnectow_mask=%x\n", state->connectow_mask);
	dwm_pwintf(p, "\tencodew_mask=%x\n", state->encodew_mask);
	dwm_pwintf(p, "\tmode: " DWM_MODE_FMT "\n", DWM_MODE_AWG(&state->mode));

	if (cwtc->funcs->atomic_pwint_state)
		cwtc->funcs->atomic_pwint_state(p, state);
}

static int dwm_atomic_connectow_check(stwuct dwm_connectow *connectow,
		stwuct dwm_connectow_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_wwiteback_job *wwiteback_job = state->wwiteback_job;
	const stwuct dwm_dispway_info *info = &connectow->dispway_info;

	state->max_bpc = info->bpc ? info->bpc : 8;
	if (connectow->max_bpc_pwopewty)
		state->max_bpc = min(state->max_bpc, state->max_wequested_bpc);

	if ((connectow->connectow_type != DWM_MODE_CONNECTOW_WWITEBACK) || !wwiteback_job)
		wetuwn 0;

	if (wwiteback_job->fb && !state->cwtc) {
		dwm_dbg_atomic(connectow->dev,
			       "[CONNECTOW:%d:%s] fwamebuffew without CWTC\n",
			       connectow->base.id, connectow->name);
		wetuwn -EINVAW;
	}

	if (state->cwtc)
		cwtc_state = dwm_atomic_get_existing_cwtc_state(state->state,
								state->cwtc);

	if (wwiteback_job->fb && !cwtc_state->active) {
		dwm_dbg_atomic(connectow->dev,
			       "[CONNECTOW:%d:%s] has fwamebuffew, but [CWTC:%d] is off\n",
			       connectow->base.id, connectow->name,
			       state->cwtc->base.id);
		wetuwn -EINVAW;
	}

	if (!wwiteback_job->fb) {
		if (wwiteback_job->out_fence) {
			dwm_dbg_atomic(connectow->dev,
				       "[CONNECTOW:%d:%s] wequesting out-fence without fwamebuffew\n",
				       connectow->base.id, connectow->name);
			wetuwn -EINVAW;
		}

		dwm_wwiteback_cweanup_job(wwiteback_job);
		state->wwiteback_job = NUWW;
	}

	wetuwn 0;
}

/**
 * dwm_atomic_get_pwane_state - get pwane state
 * @state: gwobaw atomic state object
 * @pwane: pwane to get state object fow
 *
 * This function wetuwns the pwane state fow the given pwane, awwocating it if
 * needed. It wiww awso gwab the wewevant pwane wock to make suwe that the state
 * is consistent.
 *
 * Wetuwns:
 *
 * Eithew the awwocated state ow the ewwow code encoded into the pointew. When
 * the ewwow is EDEADWK then the w/w mutex code has detected a deadwock and the
 * entiwe atomic sequence must be westawted. Aww othew ewwows awe fataw.
 */
stwuct dwm_pwane_state *
dwm_atomic_get_pwane_state(stwuct dwm_atomic_state *state,
			  stwuct dwm_pwane *pwane)
{
	int wet, index = dwm_pwane_index(pwane);
	stwuct dwm_pwane_state *pwane_state;

	WAWN_ON(!state->acquiwe_ctx);

	/* the wegacy pointews shouwd nevew be set */
	WAWN_ON(pwane->fb);
	WAWN_ON(pwane->owd_fb);
	WAWN_ON(pwane->cwtc);

	pwane_state = dwm_atomic_get_existing_pwane_state(state, pwane);
	if (pwane_state)
		wetuwn pwane_state;

	wet = dwm_modeset_wock(&pwane->mutex, state->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	pwane_state = pwane->funcs->atomic_dupwicate_state(pwane);
	if (!pwane_state)
		wetuwn EWW_PTW(-ENOMEM);

	state->pwanes[index].state = pwane_state;
	state->pwanes[index].ptw = pwane;
	state->pwanes[index].owd_state = pwane->state;
	state->pwanes[index].new_state = pwane_state;
	pwane_state->state = state;

	dwm_dbg_atomic(pwane->dev, "Added [PWANE:%d:%s] %p state to %p\n",
		       pwane->base.id, pwane->name, pwane_state, state);

	if (pwane_state->cwtc) {
		stwuct dwm_cwtc_state *cwtc_state;

		cwtc_state = dwm_atomic_get_cwtc_state(state,
						       pwane_state->cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn EWW_CAST(cwtc_state);
	}

	wetuwn pwane_state;
}
EXPOWT_SYMBOW(dwm_atomic_get_pwane_state);

static boow
pwane_switching_cwtc(const stwuct dwm_pwane_state *owd_pwane_state,
		     const stwuct dwm_pwane_state *new_pwane_state)
{
	if (!owd_pwane_state->cwtc || !new_pwane_state->cwtc)
		wetuwn fawse;

	if (owd_pwane_state->cwtc == new_pwane_state->cwtc)
		wetuwn fawse;

	/* This couwd be wefined, but cuwwentwy thewe's no hewpew ow dwivew code
	 * to impwement diwect switching of active pwanes now usewspace to take
	 * advantage of mowe diwect pwane switching without the intewmediate
	 * fuww OFF state.
	 */
	wetuwn twue;
}

/**
 * dwm_atomic_pwane_check - check pwane state
 * @owd_pwane_state: owd pwane state to check
 * @new_pwane_state: new pwane state to check
 *
 * Pwovides cowe sanity checks fow pwane state.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe
 */
static int dwm_atomic_pwane_check(const stwuct dwm_pwane_state *owd_pwane_state,
				  const stwuct dwm_pwane_state *new_pwane_state)
{
	stwuct dwm_pwane *pwane = new_pwane_state->pwane;
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	const stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	unsigned int fb_width, fb_height;
	stwuct dwm_mode_wect *cwips;
	uint32_t num_cwips;
	int wet;

	/* eithew *both* CWTC and FB must be set, ow neithew */
	if (cwtc && !fb) {
		dwm_dbg_atomic(pwane->dev, "[PWANE:%d:%s] CWTC set but no FB\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	} ewse if (fb && !cwtc) {
		dwm_dbg_atomic(pwane->dev, "[PWANE:%d:%s] FB set but no CWTC\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	/* if disabwed, we don't cawe about the west of the state: */
	if (!cwtc)
		wetuwn 0;

	/* Check whethew this pwane is usabwe on this CWTC */
	if (!(pwane->possibwe_cwtcs & dwm_cwtc_mask(cwtc))) {
		dwm_dbg_atomic(pwane->dev,
			       "Invawid [CWTC:%d:%s] fow [PWANE:%d:%s]\n",
			       cwtc->base.id, cwtc->name,
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	/* Check whethew this pwane suppowts the fb pixew fowmat. */
	wet = dwm_pwane_check_pixew_fowmat(pwane, fb->fowmat->fowmat,
					   fb->modifiew);
	if (wet) {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] invawid pixew fowmat %p4cc, modifiew 0x%wwx\n",
			       pwane->base.id, pwane->name,
			       &fb->fowmat->fowmat, fb->modifiew);
		wetuwn wet;
	}

	/* Give dwivews some hewp against integew ovewfwows */
	if (new_pwane_state->cwtc_w > INT_MAX ||
	    new_pwane_state->cwtc_x > INT_MAX - (int32_t) new_pwane_state->cwtc_w ||
	    new_pwane_state->cwtc_h > INT_MAX ||
	    new_pwane_state->cwtc_y > INT_MAX - (int32_t) new_pwane_state->cwtc_h) {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] invawid CWTC coowdinates %ux%u+%d+%d\n",
			       pwane->base.id, pwane->name,
			       new_pwane_state->cwtc_w, new_pwane_state->cwtc_h,
			       new_pwane_state->cwtc_x, new_pwane_state->cwtc_y);
		wetuwn -EWANGE;
	}

	fb_width = fb->width << 16;
	fb_height = fb->height << 16;

	/* Make suwe souwce coowdinates awe inside the fb. */
	if (new_pwane_state->swc_w > fb_width ||
	    new_pwane_state->swc_x > fb_width - new_pwane_state->swc_w ||
	    new_pwane_state->swc_h > fb_height ||
	    new_pwane_state->swc_y > fb_height - new_pwane_state->swc_h) {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] invawid souwce coowdinates "
			       "%u.%06ux%u.%06u+%u.%06u+%u.%06u (fb %ux%u)\n",
			       pwane->base.id, pwane->name,
			       new_pwane_state->swc_w >> 16,
			       ((new_pwane_state->swc_w & 0xffff) * 15625) >> 10,
			       new_pwane_state->swc_h >> 16,
			       ((new_pwane_state->swc_h & 0xffff) * 15625) >> 10,
			       new_pwane_state->swc_x >> 16,
			       ((new_pwane_state->swc_x & 0xffff) * 15625) >> 10,
			       new_pwane_state->swc_y >> 16,
			       ((new_pwane_state->swc_y & 0xffff) * 15625) >> 10,
			       fb->width, fb->height);
		wetuwn -ENOSPC;
	}

	cwips = __dwm_pwane_get_damage_cwips(new_pwane_state);
	num_cwips = dwm_pwane_get_damage_cwips_count(new_pwane_state);

	/* Make suwe damage cwips awe vawid and inside the fb. */
	whiwe (num_cwips > 0) {
		if (cwips->x1 >= cwips->x2 ||
		    cwips->y1 >= cwips->y2 ||
		    cwips->x1 < 0 ||
		    cwips->y1 < 0 ||
		    cwips->x2 > fb_width ||
		    cwips->y2 > fb_height) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] invawid damage cwip %d %d %d %d\n",
				       pwane->base.id, pwane->name, cwips->x1,
				       cwips->y1, cwips->x2, cwips->y2);
			wetuwn -EINVAW;
		}
		cwips++;
		num_cwips--;
	}

	if (pwane_switching_cwtc(owd_pwane_state, new_pwane_state)) {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] switching CWTC diwectwy\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dwm_atomic_pwane_pwint_state(stwuct dwm_pwintew *p,
		const stwuct dwm_pwane_state *state)
{
	stwuct dwm_pwane *pwane = state->pwane;
	stwuct dwm_wect swc  = dwm_pwane_state_swc(state);
	stwuct dwm_wect dest = dwm_pwane_state_dest(state);

	dwm_pwintf(p, "pwane[%u]: %s\n", pwane->base.id, pwane->name);
	dwm_pwintf(p, "\tcwtc=%s\n", state->cwtc ? state->cwtc->name : "(nuww)");
	dwm_pwintf(p, "\tfb=%u\n", state->fb ? state->fb->base.id : 0);
	if (state->fb)
		dwm_fwamebuffew_pwint_info(p, 2, state->fb);
	dwm_pwintf(p, "\tcwtc-pos=" DWM_WECT_FMT "\n", DWM_WECT_AWG(&dest));
	dwm_pwintf(p, "\tswc-pos=" DWM_WECT_FP_FMT "\n", DWM_WECT_FP_AWG(&swc));
	dwm_pwintf(p, "\twotation=%x\n", state->wotation);
	dwm_pwintf(p, "\tnowmawized-zpos=%x\n", state->nowmawized_zpos);
	dwm_pwintf(p, "\tcowow-encoding=%s\n",
		   dwm_get_cowow_encoding_name(state->cowow_encoding));
	dwm_pwintf(p, "\tcowow-wange=%s\n",
		   dwm_get_cowow_wange_name(state->cowow_wange));
	dwm_pwintf(p, "\tcowow_mgmt_changed=%d\n", state->cowow_mgmt_changed);

	if (pwane->funcs->atomic_pwint_state)
		pwane->funcs->atomic_pwint_state(p, state);
}

/**
 * DOC: handwing dwivew pwivate state
 *
 * Vewy often the DWM objects exposed to usewspace in the atomic modeset api
 * (&dwm_connectow, &dwm_cwtc and &dwm_pwane) do not map neatwy to the
 * undewwying hawdwawe. Especiawwy fow any kind of shawed wesouwces (e.g. shawed
 * cwocks, scawew units, bandwidth and fifo wimits shawed among a gwoup of
 * pwanes ow CWTCs, and so on) it makes sense to modew these as independent
 * objects. Dwivews then need to do simiwaw state twacking and commit owdewing fow
 * such pwivate (since not exposed to usewspace) objects as the atomic cowe and
 * hewpews awweady pwovide fow connectows, pwanes and CWTCs.
 *
 * To make this easiew on dwivews the atomic cowe pwovides some suppowt to twack
 * dwivew pwivate state objects using stwuct &dwm_pwivate_obj, with the
 * associated state stwuct &dwm_pwivate_state.
 *
 * Simiwaw to usewspace-exposed objects, pwivate state stwuctuwes can be
 * acquiwed by cawwing dwm_atomic_get_pwivate_obj_state(). This awso takes cawe
 * of wocking, hence dwivews shouwd not have a need to caww dwm_modeset_wock()
 * diwectwy. Sequence of the actuaw hawdwawe state commit is not handwed,
 * dwivews might need to keep twack of stwuct dwm_cwtc_commit within subcwassed
 * stwuctuwe of &dwm_pwivate_state as necessawy, e.g. simiwaw to
 * &dwm_pwane_state.commit. See awso &dwm_atomic_state.fake_commit.
 *
 * Aww pwivate state stwuctuwes contained in a &dwm_atomic_state update can be
 * itewated using fow_each_owdnew_pwivate_obj_in_state(),
 * fow_each_new_pwivate_obj_in_state() and fow_each_owd_pwivate_obj_in_state().
 * Dwivews awe wecommended to wwap these fow each type of dwivew pwivate state
 * object they have, fiwtewing on &dwm_pwivate_obj.funcs using fow_each_if(), at
 * weast if they want to itewate ovew aww objects of a given type.
 *
 * An eawwiew way to handwe dwivew pwivate state was by subcwassing stwuct
 * &dwm_atomic_state. But since that encouwages non-standawd ways to impwement
 * the check/commit spwit atomic wequiwes (by using e.g. "check and wowwback ow
 * commit instead" of "dupwicate state, check, then eithew commit ow wewease
 * dupwicated state) it is depwecated in favouw of using &dwm_pwivate_state.
 */

/**
 * dwm_atomic_pwivate_obj_init - initiawize pwivate object
 * @dev: DWM device this object wiww be attached to
 * @obj: pwivate object
 * @state: initiaw pwivate object state
 * @funcs: pointew to the stwuct of function pointews that identify the object
 * type
 *
 * Initiawize the pwivate object, which can be embedded into any
 * dwivew pwivate object that needs its own atomic state.
 */
void
dwm_atomic_pwivate_obj_init(stwuct dwm_device *dev,
			    stwuct dwm_pwivate_obj *obj,
			    stwuct dwm_pwivate_state *state,
			    const stwuct dwm_pwivate_state_funcs *funcs)
{
	memset(obj, 0, sizeof(*obj));

	dwm_modeset_wock_init(&obj->wock);

	obj->state = state;
	obj->funcs = funcs;
	wist_add_taiw(&obj->head, &dev->mode_config.pwivobj_wist);

	state->obj = obj;
}
EXPOWT_SYMBOW(dwm_atomic_pwivate_obj_init);

/**
 * dwm_atomic_pwivate_obj_fini - finawize pwivate object
 * @obj: pwivate object
 *
 * Finawize the pwivate object.
 */
void
dwm_atomic_pwivate_obj_fini(stwuct dwm_pwivate_obj *obj)
{
	wist_dew(&obj->head);
	obj->funcs->atomic_destwoy_state(obj, obj->state);
	dwm_modeset_wock_fini(&obj->wock);
}
EXPOWT_SYMBOW(dwm_atomic_pwivate_obj_fini);

/**
 * dwm_atomic_get_pwivate_obj_state - get pwivate object state
 * @state: gwobaw atomic state
 * @obj: pwivate object to get the state fow
 *
 * This function wetuwns the pwivate object state fow the given pwivate object,
 * awwocating the state if needed. It wiww awso gwab the wewevant pwivate
 * object wock to make suwe that the state is consistent.
 *
 * WETUWNS:
 *
 * Eithew the awwocated state ow the ewwow code encoded into a pointew.
 */
stwuct dwm_pwivate_state *
dwm_atomic_get_pwivate_obj_state(stwuct dwm_atomic_state *state,
				 stwuct dwm_pwivate_obj *obj)
{
	int index, num_objs, i, wet;
	size_t size;
	stwuct __dwm_pwivate_objs_state *aww;
	stwuct dwm_pwivate_state *obj_state;

	fow (i = 0; i < state->num_pwivate_objs; i++)
		if (obj == state->pwivate_objs[i].ptw)
			wetuwn state->pwivate_objs[i].state;

	wet = dwm_modeset_wock(&obj->wock, state->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	num_objs = state->num_pwivate_objs + 1;
	size = sizeof(*state->pwivate_objs) * num_objs;
	aww = kweawwoc(state->pwivate_objs, size, GFP_KEWNEW);
	if (!aww)
		wetuwn EWW_PTW(-ENOMEM);

	state->pwivate_objs = aww;
	index = state->num_pwivate_objs;
	memset(&state->pwivate_objs[index], 0, sizeof(*state->pwivate_objs));

	obj_state = obj->funcs->atomic_dupwicate_state(obj);
	if (!obj_state)
		wetuwn EWW_PTW(-ENOMEM);

	state->pwivate_objs[index].state = obj_state;
	state->pwivate_objs[index].owd_state = obj->state;
	state->pwivate_objs[index].new_state = obj_state;
	state->pwivate_objs[index].ptw = obj;
	obj_state->state = state;

	state->num_pwivate_objs = num_objs;

	dwm_dbg_atomic(state->dev,
		       "Added new pwivate object %p state %p to %p\n",
		       obj, obj_state, state);

	wetuwn obj_state;
}
EXPOWT_SYMBOW(dwm_atomic_get_pwivate_obj_state);

/**
 * dwm_atomic_get_owd_pwivate_obj_state
 * @state: gwobaw atomic state object
 * @obj: pwivate_obj to gwab
 *
 * This function wetuwns the owd pwivate object state fow the given pwivate_obj,
 * ow NUWW if the pwivate_obj is not pawt of the gwobaw atomic state.
 */
stwuct dwm_pwivate_state *
dwm_atomic_get_owd_pwivate_obj_state(const stwuct dwm_atomic_state *state,
				     stwuct dwm_pwivate_obj *obj)
{
	int i;

	fow (i = 0; i < state->num_pwivate_objs; i++)
		if (obj == state->pwivate_objs[i].ptw)
			wetuwn state->pwivate_objs[i].owd_state;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_owd_pwivate_obj_state);

/**
 * dwm_atomic_get_new_pwivate_obj_state
 * @state: gwobaw atomic state object
 * @obj: pwivate_obj to gwab
 *
 * This function wetuwns the new pwivate object state fow the given pwivate_obj,
 * ow NUWW if the pwivate_obj is not pawt of the gwobaw atomic state.
 */
stwuct dwm_pwivate_state *
dwm_atomic_get_new_pwivate_obj_state(const stwuct dwm_atomic_state *state,
				     stwuct dwm_pwivate_obj *obj)
{
	int i;

	fow (i = 0; i < state->num_pwivate_objs; i++)
		if (obj == state->pwivate_objs[i].ptw)
			wetuwn state->pwivate_objs[i].new_state;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_new_pwivate_obj_state);

/**
 * dwm_atomic_get_owd_connectow_fow_encodew - Get owd connectow fow an encodew
 * @state: Atomic state
 * @encodew: The encodew to fetch the connectow state fow
 *
 * This function finds and wetuwns the connectow that was connected to @encodew
 * as specified by the @state.
 *
 * If thewe is no connectow in @state which pweviouswy had @encodew connected to
 * it, this function wiww wetuwn NUWW. Whiwe this may seem wike an invawid use
 * case, it is sometimes usefuw to diffewentiate commits which had no pwiow
 * connectows attached to @encodew vs ones that did (and to inspect theiw
 * state). This is especiawwy twue in enabwe hooks because the pipewine has
 * changed.
 *
 * Wetuwns: The owd connectow connected to @encodew, ow NUWW if the encodew is
 * not connected.
 */
stwuct dwm_connectow *
dwm_atomic_get_owd_connectow_fow_encodew(const stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *connectow;
	unsigned int i;

	fow_each_owd_connectow_in_state(state, connectow, conn_state, i) {
		if (conn_state->best_encodew == encodew)
			wetuwn connectow;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_owd_connectow_fow_encodew);

/**
 * dwm_atomic_get_new_connectow_fow_encodew - Get new connectow fow an encodew
 * @state: Atomic state
 * @encodew: The encodew to fetch the connectow state fow
 *
 * This function finds and wetuwns the connectow that wiww be connected to
 * @encodew as specified by the @state.
 *
 * If thewe is no connectow in @state which wiww have @encodew connected to it,
 * this function wiww wetuwn NUWW. Whiwe this may seem wike an invawid use case,
 * it is sometimes usefuw to diffewentiate commits which have no connectows
 * attached to @encodew vs ones that do (and to inspect theiw state). This is
 * especiawwy twue in disabwe hooks because the pipewine wiww change.
 *
 * Wetuwns: The new connectow connected to @encodew, ow NUWW if the encodew is
 * not connected.
 */
stwuct dwm_connectow *
dwm_atomic_get_new_connectow_fow_encodew(const stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *connectow;
	unsigned int i;

	fow_each_new_connectow_in_state(state, connectow, conn_state, i) {
		if (conn_state->best_encodew == encodew)
			wetuwn connectow;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_new_connectow_fow_encodew);

/**
 * dwm_atomic_get_owd_cwtc_fow_encodew - Get owd cwtc fow an encodew
 * @state: Atomic state
 * @encodew: The encodew to fetch the cwtc state fow
 *
 * This function finds and wetuwns the cwtc that was connected to @encodew
 * as specified by the @state.
 *
 * Wetuwns: The owd cwtc connected to @encodew, ow NUWW if the encodew is
 * not connected.
 */
stwuct dwm_cwtc *
dwm_atomic_get_owd_cwtc_fow_encodew(stwuct dwm_atomic_state *state,
				    stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;

	connectow = dwm_atomic_get_owd_connectow_fow_encodew(state, encodew);
	if (!connectow)
		wetuwn NUWW;

	conn_state = dwm_atomic_get_owd_connectow_state(state, connectow);
	if (!conn_state)
		wetuwn NUWW;

	wetuwn conn_state->cwtc;
}
EXPOWT_SYMBOW(dwm_atomic_get_owd_cwtc_fow_encodew);

/**
 * dwm_atomic_get_new_cwtc_fow_encodew - Get new cwtc fow an encodew
 * @state: Atomic state
 * @encodew: The encodew to fetch the cwtc state fow
 *
 * This function finds and wetuwns the cwtc that wiww be connected to @encodew
 * as specified by the @state.
 *
 * Wetuwns: The new cwtc connected to @encodew, ow NUWW if the encodew is
 * not connected.
 */
stwuct dwm_cwtc *
dwm_atomic_get_new_cwtc_fow_encodew(stwuct dwm_atomic_state *state,
				    stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state, encodew);
	if (!connectow)
		wetuwn NUWW;

	conn_state = dwm_atomic_get_new_connectow_state(state, connectow);
	if (!conn_state)
		wetuwn NUWW;

	wetuwn conn_state->cwtc;
}
EXPOWT_SYMBOW(dwm_atomic_get_new_cwtc_fow_encodew);

/**
 * dwm_atomic_get_connectow_state - get connectow state
 * @state: gwobaw atomic state object
 * @connectow: connectow to get state object fow
 *
 * This function wetuwns the connectow state fow the given connectow,
 * awwocating it if needed. It wiww awso gwab the wewevant connectow wock to
 * make suwe that the state is consistent.
 *
 * Wetuwns:
 *
 * Eithew the awwocated state ow the ewwow code encoded into the pointew. When
 * the ewwow is EDEADWK then the w/w mutex code has detected a deadwock and the
 * entiwe atomic sequence must be westawted. Aww othew ewwows awe fataw.
 */
stwuct dwm_connectow_state *
dwm_atomic_get_connectow_state(stwuct dwm_atomic_state *state,
			  stwuct dwm_connectow *connectow)
{
	int wet, index;
	stwuct dwm_mode_config *config = &connectow->dev->mode_config;
	stwuct dwm_connectow_state *connectow_state;

	WAWN_ON(!state->acquiwe_ctx);

	wet = dwm_modeset_wock(&config->connection_mutex, state->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	index = dwm_connectow_index(connectow);

	if (index >= state->num_connectow) {
		stwuct __dwm_connnectows_state *c;
		int awwoc = max(index + 1, config->num_connectow);

		c = kweawwoc_awway(state->connectows, awwoc,
				   sizeof(*state->connectows), GFP_KEWNEW);
		if (!c)
			wetuwn EWW_PTW(-ENOMEM);

		state->connectows = c;
		memset(&state->connectows[state->num_connectow], 0,
		       sizeof(*state->connectows) * (awwoc - state->num_connectow));

		state->num_connectow = awwoc;
	}

	if (state->connectows[index].state)
		wetuwn state->connectows[index].state;

	connectow_state = connectow->funcs->atomic_dupwicate_state(connectow);
	if (!connectow_state)
		wetuwn EWW_PTW(-ENOMEM);

	dwm_connectow_get(connectow);
	state->connectows[index].state = connectow_state;
	state->connectows[index].owd_state = connectow->state;
	state->connectows[index].new_state = connectow_state;
	state->connectows[index].ptw = connectow;
	connectow_state->state = state;

	dwm_dbg_atomic(connectow->dev, "Added [CONNECTOW:%d:%s] %p state to %p\n",
			 connectow->base.id, connectow->name,
			 connectow_state, state);

	if (connectow_state->cwtc) {
		stwuct dwm_cwtc_state *cwtc_state;

		cwtc_state = dwm_atomic_get_cwtc_state(state,
						       connectow_state->cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn EWW_CAST(cwtc_state);
	}

	wetuwn connectow_state;
}
EXPOWT_SYMBOW(dwm_atomic_get_connectow_state);

static void dwm_atomic_connectow_pwint_state(stwuct dwm_pwintew *p,
		const stwuct dwm_connectow_state *state)
{
	stwuct dwm_connectow *connectow = state->connectow;

	dwm_pwintf(p, "connectow[%u]: %s\n", connectow->base.id, connectow->name);
	dwm_pwintf(p, "\tcwtc=%s\n", state->cwtc ? state->cwtc->name : "(nuww)");
	dwm_pwintf(p, "\tsewf_wefwesh_awawe=%d\n", state->sewf_wefwesh_awawe);
	dwm_pwintf(p, "\tmax_wequested_bpc=%d\n", state->max_wequested_bpc);
	dwm_pwintf(p, "\tcowowspace=%s\n", dwm_get_cowowspace_name(state->cowowspace));

	if (connectow->connectow_type == DWM_MODE_CONNECTOW_WWITEBACK)
		if (state->wwiteback_job && state->wwiteback_job->fb)
			dwm_pwintf(p, "\tfb=%d\n", state->wwiteback_job->fb->base.id);

	if (connectow->funcs->atomic_pwint_state)
		connectow->funcs->atomic_pwint_state(p, state);
}

/**
 * dwm_atomic_get_bwidge_state - get bwidge state
 * @state: gwobaw atomic state object
 * @bwidge: bwidge to get state object fow
 *
 * This function wetuwns the bwidge state fow the given bwidge, awwocating it
 * if needed. It wiww awso gwab the wewevant bwidge wock to make suwe that the
 * state is consistent.
 *
 * Wetuwns:
 *
 * Eithew the awwocated state ow the ewwow code encoded into the pointew. When
 * the ewwow is EDEADWK then the w/w mutex code has detected a deadwock and the
 * entiwe atomic sequence must be westawted.
 */
stwuct dwm_bwidge_state *
dwm_atomic_get_bwidge_state(stwuct dwm_atomic_state *state,
			    stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_pwivate_state *obj_state;

	obj_state = dwm_atomic_get_pwivate_obj_state(state, &bwidge->base);
	if (IS_EWW(obj_state))
		wetuwn EWW_CAST(obj_state);

	wetuwn dwm_pwiv_to_bwidge_state(obj_state);
}
EXPOWT_SYMBOW(dwm_atomic_get_bwidge_state);

/**
 * dwm_atomic_get_owd_bwidge_state - get owd bwidge state, if it exists
 * @state: gwobaw atomic state object
 * @bwidge: bwidge to gwab
 *
 * This function wetuwns the owd bwidge state fow the given bwidge, ow NUWW if
 * the bwidge is not pawt of the gwobaw atomic state.
 */
stwuct dwm_bwidge_state *
dwm_atomic_get_owd_bwidge_state(const stwuct dwm_atomic_state *state,
				stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_pwivate_state *obj_state;

	obj_state = dwm_atomic_get_owd_pwivate_obj_state(state, &bwidge->base);
	if (!obj_state)
		wetuwn NUWW;

	wetuwn dwm_pwiv_to_bwidge_state(obj_state);
}
EXPOWT_SYMBOW(dwm_atomic_get_owd_bwidge_state);

/**
 * dwm_atomic_get_new_bwidge_state - get new bwidge state, if it exists
 * @state: gwobaw atomic state object
 * @bwidge: bwidge to gwab
 *
 * This function wetuwns the new bwidge state fow the given bwidge, ow NUWW if
 * the bwidge is not pawt of the gwobaw atomic state.
 */
stwuct dwm_bwidge_state *
dwm_atomic_get_new_bwidge_state(const stwuct dwm_atomic_state *state,
				stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_pwivate_state *obj_state;

	obj_state = dwm_atomic_get_new_pwivate_obj_state(state, &bwidge->base);
	if (!obj_state)
		wetuwn NUWW;

	wetuwn dwm_pwiv_to_bwidge_state(obj_state);
}
EXPOWT_SYMBOW(dwm_atomic_get_new_bwidge_state);

/**
 * dwm_atomic_add_encodew_bwidges - add bwidges attached to an encodew
 * @state: atomic state
 * @encodew: DWM encodew
 *
 * This function adds aww bwidges attached to @encodew. This is needed to add
 * bwidge states to @state and make them avaiwabwe when
 * &dwm_bwidge_funcs.atomic_check(), &dwm_bwidge_funcs.atomic_pwe_enabwe(),
 * &dwm_bwidge_funcs.atomic_enabwe(),
 * &dwm_bwidge_funcs.atomic_disabwe_post_disabwe() awe cawwed.
 *
 * Wetuwns:
 * 0 on success ow can faiw with -EDEADWK ow -ENOMEM. When the ewwow is EDEADWK
 * then the w/w mutex code has detected a deadwock and the entiwe atomic
 * sequence must be westawted. Aww othew ewwows awe fataw.
 */
int
dwm_atomic_add_encodew_bwidges(stwuct dwm_atomic_state *state,
			       stwuct dwm_encodew *encodew)
{
	stwuct dwm_bwidge_state *bwidge_state;
	stwuct dwm_bwidge *bwidge;

	if (!encodew)
		wetuwn 0;

	dwm_dbg_atomic(encodew->dev,
		       "Adding aww bwidges fow [encodew:%d:%s] to %p\n",
		       encodew->base.id, encodew->name, state);

	dwm_fow_each_bwidge_in_chain(encodew, bwidge) {
		/* Skip bwidges that don't impwement the atomic state hooks. */
		if (!bwidge->funcs->atomic_dupwicate_state)
			continue;

		bwidge_state = dwm_atomic_get_bwidge_state(state, bwidge);
		if (IS_EWW(bwidge_state))
			wetuwn PTW_EWW(bwidge_state);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_add_encodew_bwidges);

/**
 * dwm_atomic_add_affected_connectows - add connectows fow CWTC
 * @state: atomic state
 * @cwtc: DWM CWTC
 *
 * This function wawks the cuwwent configuwation and adds aww connectows
 * cuwwentwy using @cwtc to the atomic configuwation @state. Note that this
 * function must acquiwe the connection mutex. This can potentiawwy cause
 * unneeded sewiawization if the update is just fow the pwanes on one CWTC. Hence
 * dwivews and hewpews shouwd onwy caww this when weawwy needed (e.g. when a
 * fuww modeset needs to happen due to some change).
 *
 * Wetuwns:
 * 0 on success ow can faiw with -EDEADWK ow -ENOMEM. When the ewwow is EDEADWK
 * then the w/w mutex code has detected a deadwock and the entiwe atomic
 * sequence must be westawted. Aww othew ewwows awe fataw.
 */
int
dwm_atomic_add_affected_connectows(stwuct dwm_atomic_state *state,
				   stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_mode_config *config = &state->dev->mode_config;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wet = dwm_modeset_wock(&config->connection_mutex, state->acquiwe_ctx);
	if (wet)
		wetuwn wet;

	dwm_dbg_atomic(cwtc->dev,
		       "Adding aww cuwwent connectows fow [CWTC:%d:%s] to %p\n",
		       cwtc->base.id, cwtc->name, state);

	/*
	 * Changed connectows awe awweady in @state, so onwy need to wook
	 * at the connectow_mask in cwtc_state.
	 */
	dwm_connectow_wist_itew_begin(state->dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (!(cwtc_state->connectow_mask & dwm_connectow_mask(connectow)))
			continue;

		conn_state = dwm_atomic_get_connectow_state(state, connectow);
		if (IS_EWW(conn_state)) {
			dwm_connectow_wist_itew_end(&conn_itew);
			wetuwn PTW_EWW(conn_state);
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_add_affected_connectows);

/**
 * dwm_atomic_add_affected_pwanes - add pwanes fow CWTC
 * @state: atomic state
 * @cwtc: DWM CWTC
 *
 * This function wawks the cuwwent configuwation and adds aww pwanes
 * cuwwentwy used by @cwtc to the atomic configuwation @state. This is usefuw
 * when an atomic commit awso needs to check aww cuwwentwy enabwed pwane on
 * @cwtc, e.g. when changing the mode. It's awso usefuw when we-enabwing a CWTC
 * to avoid speciaw code to fowce-enabwe aww pwanes.
 *
 * Since acquiwing a pwane state wiww awways awso acquiwe the w/w mutex of the
 * cuwwent CWTC fow that pwane (if thewe is any) adding aww the pwane states fow
 * a CWTC wiww not weduce pawawwewism of atomic updates.
 *
 * Wetuwns:
 * 0 on success ow can faiw with -EDEADWK ow -ENOMEM. When the ewwow is EDEADWK
 * then the w/w mutex code has detected a deadwock and the entiwe atomic
 * sequence must be westawted. Aww othew ewwows awe fataw.
 */
int
dwm_atomic_add_affected_pwanes(stwuct dwm_atomic_state *state,
			       stwuct dwm_cwtc *cwtc)
{
	const stwuct dwm_cwtc_state *owd_cwtc_state =
		dwm_atomic_get_owd_cwtc_state(state, cwtc);
	stwuct dwm_pwane *pwane;

	WAWN_ON(!dwm_atomic_get_new_cwtc_state(state, cwtc));

	dwm_dbg_atomic(cwtc->dev,
		       "Adding aww cuwwent pwanes fow [CWTC:%d:%s] to %p\n",
		       cwtc->base.id, cwtc->name, state);

	dwm_fow_each_pwane_mask(pwane, state->dev, owd_cwtc_state->pwane_mask) {
		stwuct dwm_pwane_state *pwane_state =
			dwm_atomic_get_pwane_state(state, pwane);

		if (IS_EWW(pwane_state))
			wetuwn PTW_EWW(pwane_state);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_add_affected_pwanes);

/**
 * dwm_atomic_check_onwy - check whethew a given config wouwd wowk
 * @state: atomic configuwation to check
 *
 * Note that this function can wetuwn -EDEADWK if the dwivew needed to acquiwe
 * mowe wocks but encountewed a deadwock. The cawwew must then do the usuaw w/w
 * backoff dance and westawt. Aww othew ewwows awe fataw.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_atomic_check_onwy(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state;
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *conn_state;
	unsigned int wequested_cwtc = 0;
	unsigned int affected_cwtc = 0;
	int i, wet = 0;

	dwm_dbg_atomic(dev, "checking %p\n", state);

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (new_cwtc_state->enabwe)
			wequested_cwtc |= dwm_cwtc_mask(cwtc);
	}

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		wet = dwm_atomic_pwane_check(owd_pwane_state, new_pwane_state);
		if (wet) {
			dwm_dbg_atomic(dev, "[PWANE:%d:%s] atomic cowe check faiwed\n",
				       pwane->base.id, pwane->name);
			wetuwn wet;
		}
	}

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		wet = dwm_atomic_cwtc_check(owd_cwtc_state, new_cwtc_state);
		if (wet) {
			dwm_dbg_atomic(dev, "[CWTC:%d:%s] atomic cowe check faiwed\n",
				       cwtc->base.id, cwtc->name);
			wetuwn wet;
		}
	}

	fow_each_new_connectow_in_state(state, conn, conn_state, i) {
		wet = dwm_atomic_connectow_check(conn, conn_state);
		if (wet) {
			dwm_dbg_atomic(dev, "[CONNECTOW:%d:%s] atomic cowe check faiwed\n",
				       conn->base.id, conn->name);
			wetuwn wet;
		}
	}

	if (config->funcs->atomic_check) {
		wet = config->funcs->atomic_check(state->dev, state);

		if (wet) {
			dwm_dbg_atomic(dev, "atomic dwivew check fow %p faiwed: %d\n",
				       state, wet);
			wetuwn wet;
		}
	}

	if (!state->awwow_modeset) {
		fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
			if (dwm_atomic_cwtc_needs_modeset(new_cwtc_state)) {
				dwm_dbg_atomic(dev, "[CWTC:%d:%s] wequiwes fuww modeset\n",
					       cwtc->base.id, cwtc->name);
				wetuwn -EINVAW;
			}
		}
	}

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (new_cwtc_state->enabwe)
			affected_cwtc |= dwm_cwtc_mask(cwtc);
	}

	/*
	 * Fow commits that awwow modesets dwivews can add othew CWTCs to the
	 * atomic commit, e.g. when they need to weawwocate gwobaw wesouwces.
	 * This can cause spuwious EBUSY, which wobs compositows of a vewy
	 * effective sanity check fow theiw dwawing woop. Thewefow onwy awwow
	 * dwivews to add unwewated CWTC states fow modeset commits.
	 *
	 * FIXME: Shouwd add affected_cwtc mask to the ATOMIC IOCTW as an output
	 * so compositows know what's going on.
	 */
	if (affected_cwtc != wequested_cwtc) {
		dwm_dbg_atomic(dev,
			       "dwivew added CWTC to commit: wequested 0x%x, affected 0x%0x\n",
			       wequested_cwtc, affected_cwtc);
		WAWN(!state->awwow_modeset, "adding CWTC not awwowed without modesets: wequested 0x%x, affected 0x%0x\n",
		     wequested_cwtc, affected_cwtc);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_check_onwy);

/**
 * dwm_atomic_commit - commit configuwation atomicawwy
 * @state: atomic configuwation to check
 *
 * Note that this function can wetuwn -EDEADWK if the dwivew needed to acquiwe
 * mowe wocks but encountewed a deadwock. The cawwew must then do the usuaw w/w
 * backoff dance and westawt. Aww othew ewwows awe fataw.
 *
 * This function wiww take its own wefewence on @state.
 * Cawwews shouwd awways wewease theiw wefewence with dwm_atomic_state_put().
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_atomic_commit(stwuct dwm_atomic_state *state)
{
	stwuct dwm_mode_config *config = &state->dev->mode_config;
	stwuct dwm_pwintew p = dwm_info_pwintew(state->dev->dev);
	int wet;

	if (dwm_debug_enabwed(DWM_UT_STATE))
		dwm_atomic_pwint_new_state(state, &p);

	wet = dwm_atomic_check_onwy(state);
	if (wet)
		wetuwn wet;

	dwm_dbg_atomic(state->dev, "committing %p\n", state);

	wetuwn config->funcs->atomic_commit(state->dev, state, fawse);
}
EXPOWT_SYMBOW(dwm_atomic_commit);

/**
 * dwm_atomic_nonbwocking_commit - atomic nonbwocking commit
 * @state: atomic configuwation to check
 *
 * Note that this function can wetuwn -EDEADWK if the dwivew needed to acquiwe
 * mowe wocks but encountewed a deadwock. The cawwew must then do the usuaw w/w
 * backoff dance and westawt. Aww othew ewwows awe fataw.
 *
 * This function wiww take its own wefewence on @state.
 * Cawwews shouwd awways wewease theiw wefewence with dwm_atomic_state_put().
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_atomic_nonbwocking_commit(stwuct dwm_atomic_state *state)
{
	stwuct dwm_mode_config *config = &state->dev->mode_config;
	int wet;

	wet = dwm_atomic_check_onwy(state);
	if (wet)
		wetuwn wet;

	dwm_dbg_atomic(state->dev, "committing %p nonbwocking\n", state);

	wetuwn config->funcs->atomic_commit(state->dev, state, twue);
}
EXPOWT_SYMBOW(dwm_atomic_nonbwocking_commit);

/* just used fwom dwm-cwient and atomic-hewpew: */
int __dwm_atomic_hewpew_disabwe_pwane(stwuct dwm_pwane *pwane,
				      stwuct dwm_pwane_state *pwane_state)
{
	int wet;

	wet = dwm_atomic_set_cwtc_fow_pwane(pwane_state, NUWW);
	if (wet != 0)
		wetuwn wet;

	dwm_atomic_set_fb_fow_pwane(pwane_state, NUWW);
	pwane_state->cwtc_x = 0;
	pwane_state->cwtc_y = 0;
	pwane_state->cwtc_w = 0;
	pwane_state->cwtc_h = 0;
	pwane_state->swc_x = 0;
	pwane_state->swc_y = 0;
	pwane_state->swc_w = 0;
	pwane_state->swc_h = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_disabwe_pwane);

static int update_output_state(stwuct dwm_atomic_state *state,
			       stwuct dwm_mode_set *set)
{
	stwuct dwm_device *dev = set->cwtc->dev;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	int wet, i;

	wet = dwm_modeset_wock(&dev->mode_config.connection_mutex,
			       state->acquiwe_ctx);
	if (wet)
		wetuwn wet;

	/* Fiwst disabwe aww connectows on the tawget cwtc. */
	wet = dwm_atomic_add_affected_connectows(state, set->cwtc);
	if (wet)
		wetuwn wet;

	fow_each_new_connectow_in_state(state, connectow, new_conn_state, i) {
		if (new_conn_state->cwtc == set->cwtc) {
			wet = dwm_atomic_set_cwtc_fow_connectow(new_conn_state,
								NUWW);
			if (wet)
				wetuwn wet;

			/* Make suwe wegacy setCwtc awways we-twains */
			new_conn_state->wink_status = DWM_WINK_STATUS_GOOD;
		}
	}

	/* Then set aww connectows fwom set->connectows on the tawget cwtc */
	fow (i = 0; i < set->num_connectows; i++) {
		new_conn_state = dwm_atomic_get_connectow_state(state,
								set->connectows[i]);
		if (IS_EWW(new_conn_state))
			wetuwn PTW_EWW(new_conn_state);

		wet = dwm_atomic_set_cwtc_fow_connectow(new_conn_state,
							set->cwtc);
		if (wet)
			wetuwn wet;
	}

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		/*
		 * Don't update ->enabwe fow the CWTC in the set_config wequest,
		 * since a mismatch wouwd indicate a bug in the uppew wayews.
		 * The actuaw modeset code watew on wiww catch any
		 * inconsistencies hewe.
		 */
		if (cwtc == set->cwtc)
			continue;

		if (!new_cwtc_state->connectow_mask) {
			wet = dwm_atomic_set_mode_pwop_fow_cwtc(new_cwtc_state,
								NUWW);
			if (wet < 0)
				wetuwn wet;

			new_cwtc_state->active = fawse;
		}
	}

	wetuwn 0;
}

/* just used fwom dwm-cwient and atomic-hewpew: */
int __dwm_atomic_hewpew_set_config(stwuct dwm_mode_set *set,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_pwane_state *pwimawy_state;
	stwuct dwm_cwtc *cwtc = set->cwtc;
	int hdispway, vdispway;
	int wet;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	pwimawy_state = dwm_atomic_get_pwane_state(state, cwtc->pwimawy);
	if (IS_EWW(pwimawy_state))
		wetuwn PTW_EWW(pwimawy_state);

	if (!set->mode) {
		WAWN_ON(set->fb);
		WAWN_ON(set->num_connectows);

		wet = dwm_atomic_set_mode_fow_cwtc(cwtc_state, NUWW);
		if (wet != 0)
			wetuwn wet;

		cwtc_state->active = fawse;

		wet = dwm_atomic_set_cwtc_fow_pwane(pwimawy_state, NUWW);
		if (wet != 0)
			wetuwn wet;

		dwm_atomic_set_fb_fow_pwane(pwimawy_state, NUWW);

		goto commit;
	}

	WAWN_ON(!set->fb);
	WAWN_ON(!set->num_connectows);

	wet = dwm_atomic_set_mode_fow_cwtc(cwtc_state, set->mode);
	if (wet != 0)
		wetuwn wet;

	cwtc_state->active = twue;

	wet = dwm_atomic_set_cwtc_fow_pwane(pwimawy_state, cwtc);
	if (wet != 0)
		wetuwn wet;

	dwm_mode_get_hv_timing(set->mode, &hdispway, &vdispway);

	dwm_atomic_set_fb_fow_pwane(pwimawy_state, set->fb);
	pwimawy_state->cwtc_x = 0;
	pwimawy_state->cwtc_y = 0;
	pwimawy_state->cwtc_w = hdispway;
	pwimawy_state->cwtc_h = vdispway;
	pwimawy_state->swc_x = set->x << 16;
	pwimawy_state->swc_y = set->y << 16;
	if (dwm_wotation_90_ow_270(pwimawy_state->wotation)) {
		pwimawy_state->swc_w = vdispway << 16;
		pwimawy_state->swc_h = hdispway << 16;
	} ewse {
		pwimawy_state->swc_w = hdispway << 16;
		pwimawy_state->swc_h = vdispway << 16;
	}

commit:
	wet = update_output_state(state, set);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_set_config);

static void dwm_atomic_pwivate_obj_pwint_state(stwuct dwm_pwintew *p,
					       const stwuct dwm_pwivate_state *state)
{
	stwuct dwm_pwivate_obj *obj = state->obj;

	if (obj->funcs->atomic_pwint_state)
		obj->funcs->atomic_pwint_state(p, state);
}

/**
 * dwm_atomic_pwint_new_state - pwints dwm atomic state
 * @state: atomic configuwation to check
 * @p: dwm pwintew
 *
 * This functions pwints the dwm atomic state snapshot using the dwm pwintew
 * which is passed to it. This snapshot can be used fow debugging puwposes.
 *
 * Note that this function wooks into the new state objects and hence its not
 * safe to be used aftew the caww to dwm_atomic_hewpew_commit_hw_done().
 */
void dwm_atomic_pwint_new_state(const stwuct dwm_atomic_state *state,
		stwuct dwm_pwintew *p)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *pwane_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_pwivate_obj *obj;
	stwuct dwm_pwivate_state *obj_state;
	int i;

	if (!p) {
		dwm_eww(state->dev, "invawid dwm pwintew\n");
		wetuwn;
	}

	dwm_dbg_atomic(state->dev, "checking %p\n", state);

	fow_each_new_pwane_in_state(state, pwane, pwane_state, i)
		dwm_atomic_pwane_pwint_state(p, pwane_state);

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i)
		dwm_atomic_cwtc_pwint_state(p, cwtc_state);

	fow_each_new_connectow_in_state(state, connectow, connectow_state, i)
		dwm_atomic_connectow_pwint_state(p, connectow_state);

	fow_each_new_pwivate_obj_in_state(state, obj, obj_state, i)
		dwm_atomic_pwivate_obj_pwint_state(p, obj_state);
}
EXPOWT_SYMBOW(dwm_atomic_pwint_new_state);

static void __dwm_state_dump(stwuct dwm_device *dev, stwuct dwm_pwintew *p,
			     boow take_wocks)
{
	stwuct dwm_mode_config *config = &dev->mode_config;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_pwivate_obj *obj;

	if (!dwm_dwv_uses_atomic_modeset(dev))
		wetuwn;

	wist_fow_each_entwy(pwane, &config->pwane_wist, head) {
		if (take_wocks)
			dwm_modeset_wock(&pwane->mutex, NUWW);
		dwm_atomic_pwane_pwint_state(p, pwane->state);
		if (take_wocks)
			dwm_modeset_unwock(&pwane->mutex);
	}

	wist_fow_each_entwy(cwtc, &config->cwtc_wist, head) {
		if (take_wocks)
			dwm_modeset_wock(&cwtc->mutex, NUWW);
		dwm_atomic_cwtc_pwint_state(p, cwtc->state);
		if (take_wocks)
			dwm_modeset_unwock(&cwtc->mutex);
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	if (take_wocks)
		dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	dwm_fow_each_connectow_itew(connectow, &conn_itew)
		dwm_atomic_connectow_pwint_state(p, connectow->state);
	if (take_wocks)
		dwm_modeset_unwock(&dev->mode_config.connection_mutex);
	dwm_connectow_wist_itew_end(&conn_itew);

	wist_fow_each_entwy(obj, &config->pwivobj_wist, head) {
		if (take_wocks)
			dwm_modeset_wock(&obj->wock, NUWW);
		dwm_atomic_pwivate_obj_pwint_state(p, obj->state);
		if (take_wocks)
			dwm_modeset_unwock(&obj->wock);
	}
}

/**
 * dwm_state_dump - dump entiwe device atomic state
 * @dev: the dwm device
 * @p: whewe to pwint the state to
 *
 * Just fow debugging.  Dwivews might want an option to dump state
 * to dmesg in case of ewwow iwq's.  (Hint, you pwobabwy want to
 * watewimit this!)
 *
 * The cawwew must wwap this dwm_modeset_wock_aww_ctx() and
 * dwm_modeset_dwop_wocks(). If this is cawwed fwom ewwow iwq handwew, it shouwd
 * not be enabwed by defauwt - if you awe debugging ewwows you might
 * not cawe that this is wacey, but cawwing this without aww modeset wocks hewd
 * is inhewentwy unsafe.
 */
void dwm_state_dump(stwuct dwm_device *dev, stwuct dwm_pwintew *p)
{
	__dwm_state_dump(dev, p, fawse);
}
EXPOWT_SYMBOW(dwm_state_dump);

#ifdef CONFIG_DEBUG_FS
static int dwm_state_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	__dwm_state_dump(dev, &p, twue);

	wetuwn 0;
}

/* any use in debugfs fiwes to dump individuaw pwanes/cwtc/etc? */
static const stwuct dwm_debugfs_info dwm_atomic_debugfs_wist[] = {
	{"state", dwm_state_info, 0},
};

void dwm_atomic_debugfs_init(stwuct dwm_device *dev)
{
	dwm_debugfs_add_fiwes(dev, dwm_atomic_debugfs_wist,
			      AWWAY_SIZE(dwm_atomic_debugfs_wist));
}
#endif
