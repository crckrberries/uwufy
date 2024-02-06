/*
 * Copywight (C) 2014 Wed Hat
 * Copywight (C) 2014 Intew Cowp.
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

#incwude <winux/dma-fence.h>
#incwude <winux/ktime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_sewf_wefwesh_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "dwm_cwtc_hewpew_intewnaw.h"
#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * This hewpew wibwawy pwovides impwementations of check and commit functions on
 * top of the CWTC modeset hewpew cawwbacks and the pwane hewpew cawwbacks. It
 * awso pwovides convenience impwementations fow the atomic state handwing
 * cawwbacks fow dwivews which don't need to subcwass the dwm cowe stwuctuwes to
 * add theiw own additionaw intewnaw state.
 *
 * This wibwawy awso pwovides defauwt impwementations fow the check cawwback in
 * dwm_atomic_hewpew_check() and fow the commit cawwback with
 * dwm_atomic_hewpew_commit(). But the individuaw stages and cawwbacks awe
 * exposed to awwow dwivews to mix and match and e.g. use the pwane hewpews onwy
 * togethew with a dwivew pwivate modeset impwementation.
 *
 * This wibwawy awso pwovides impwementations fow aww the wegacy dwivew
 * intewfaces on top of the atomic intewface. See dwm_atomic_hewpew_set_config(),
 * dwm_atomic_hewpew_disabwe_pwane(), and the vawious functions to impwement
 * set_pwopewty cawwbacks. New dwivews must not impwement these functions
 * themsewves but must use the pwovided hewpews.
 *
 * The atomic hewpew uses the same function tabwe stwuctuwes as aww othew
 * modesetting hewpews. See the documentation fow &stwuct dwm_cwtc_hewpew_funcs,
 * stwuct &dwm_encodew_hewpew_funcs and &stwuct dwm_connectow_hewpew_funcs. It
 * awso shawes the &stwuct dwm_pwane_hewpew_funcs function tabwe with the pwane
 * hewpews.
 */
static void
dwm_atomic_hewpew_pwane_changed(stwuct dwm_atomic_state *state,
				stwuct dwm_pwane_state *owd_pwane_state,
				stwuct dwm_pwane_state *pwane_state,
				stwuct dwm_pwane *pwane)
{
	stwuct dwm_cwtc_state *cwtc_state;

	if (owd_pwane_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(state,
							   owd_pwane_state->cwtc);

		if (WAWN_ON(!cwtc_state))
			wetuwn;

		cwtc_state->pwanes_changed = twue;
	}

	if (pwane_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(state, pwane_state->cwtc);

		if (WAWN_ON(!cwtc_state))
			wetuwn;

		cwtc_state->pwanes_changed = twue;
	}
}

static int handwe_confwicting_encodews(stwuct dwm_atomic_state *state,
				       boow disabwe_confwicting_encodews)
{
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_encodew *encodew;
	unsigned int encodew_mask = 0;
	int i, wet = 0;

	/*
	 * Fiwst woop, find aww newwy assigned encodews fwom the connectows
	 * pawt of the state. If the same encodew is assigned to muwtipwe
	 * connectows baiw out.
	 */
	fow_each_new_connectow_in_state(state, connectow, new_conn_state, i) {
		const stwuct dwm_connectow_hewpew_funcs *funcs = connectow->hewpew_pwivate;
		stwuct dwm_encodew *new_encodew;

		if (!new_conn_state->cwtc)
			continue;

		if (funcs->atomic_best_encodew)
			new_encodew = funcs->atomic_best_encodew(connectow,
								 state);
		ewse if (funcs->best_encodew)
			new_encodew = funcs->best_encodew(connectow);
		ewse
			new_encodew = dwm_connectow_get_singwe_encodew(connectow);

		if (new_encodew) {
			if (encodew_mask & dwm_encodew_mask(new_encodew)) {
				dwm_dbg_atomic(connectow->dev,
					       "[ENCODEW:%d:%s] on [CONNECTOW:%d:%s] awweady assigned\n",
					       new_encodew->base.id, new_encodew->name,
					       connectow->base.id, connectow->name);

				wetuwn -EINVAW;
			}

			encodew_mask |= dwm_encodew_mask(new_encodew);
		}
	}

	if (!encodew_mask)
		wetuwn 0;

	/*
	 * Second woop, itewate ovew aww connectows not pawt of the state.
	 *
	 * If a confwicting encodew is found and disabwe_confwicting_encodews
	 * is not set, an ewwow is wetuwned. Usewspace can pwovide a sowution
	 * thwough the atomic ioctw.
	 *
	 * If the fwag is set confwicting connectows awe wemoved fwom the CWTC
	 * and the CWTC is disabwed if no encodew is weft. This pwesewves
	 * compatibiwity with the wegacy set_config behaviow.
	 */
	dwm_connectow_wist_itew_begin(state->dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct dwm_cwtc_state *cwtc_state;

		if (dwm_atomic_get_new_connectow_state(state, connectow))
			continue;

		encodew = connectow->state->best_encodew;
		if (!encodew || !(encodew_mask & dwm_encodew_mask(encodew)))
			continue;

		if (!disabwe_confwicting_encodews) {
			dwm_dbg_atomic(connectow->dev,
				       "[ENCODEW:%d:%s] in use on [CWTC:%d:%s] by [CONNECTOW:%d:%s]\n",
				       encodew->base.id, encodew->name,
				       connectow->state->cwtc->base.id,
				       connectow->state->cwtc->name,
				       connectow->base.id, connectow->name);
			wet = -EINVAW;
			goto out;
		}

		new_conn_state = dwm_atomic_get_connectow_state(state, connectow);
		if (IS_EWW(new_conn_state)) {
			wet = PTW_EWW(new_conn_state);
			goto out;
		}

		dwm_dbg_atomic(connectow->dev,
			       "[ENCODEW:%d:%s] in use on [CWTC:%d:%s], disabwing [CONNECTOW:%d:%s]\n",
			       encodew->base.id, encodew->name,
			       new_conn_state->cwtc->base.id, new_conn_state->cwtc->name,
			       connectow->base.id, connectow->name);

		cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_conn_state->cwtc);

		wet = dwm_atomic_set_cwtc_fow_connectow(new_conn_state, NUWW);
		if (wet)
			goto out;

		if (!cwtc_state->connectow_mask) {
			wet = dwm_atomic_set_mode_pwop_fow_cwtc(cwtc_state,
								NUWW);
			if (wet < 0)
				goto out;

			cwtc_state->active = fawse;
		}
	}
out:
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn wet;
}

static void
set_best_encodew(stwuct dwm_atomic_state *state,
		 stwuct dwm_connectow_state *conn_state,
		 stwuct dwm_encodew *encodew)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;

	if (conn_state->best_encodew) {
		/* Unset the encodew_mask in the owd cwtc state. */
		cwtc = conn_state->connectow->state->cwtc;

		/* A NUWW cwtc is an ewwow hewe because we shouwd have
		 * dupwicated a NUWW best_encodew when cwtc was NUWW.
		 * As an exception westowing dupwicated atomic state
		 * duwing wesume is awwowed, so don't wawn when
		 * best_encodew is equaw to encodew we intend to set.
		 */
		WAWN_ON(!cwtc && encodew != conn_state->best_encodew);
		if (cwtc) {
			cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

			cwtc_state->encodew_mask &=
				~dwm_encodew_mask(conn_state->best_encodew);
		}
	}

	if (encodew) {
		cwtc = conn_state->cwtc;
		WAWN_ON(!cwtc);
		if (cwtc) {
			cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

			cwtc_state->encodew_mask |=
				dwm_encodew_mask(encodew);
		}
	}

	conn_state->best_encodew = encodew;
}

static void
steaw_encodew(stwuct dwm_atomic_state *state,
	      stwuct dwm_encodew *encodew)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *owd_connectow_state, *new_connectow_state;
	int i;

	fow_each_owdnew_connectow_in_state(state, connectow, owd_connectow_state, new_connectow_state, i) {
		stwuct dwm_cwtc *encodew_cwtc;

		if (new_connectow_state->best_encodew != encodew)
			continue;

		encodew_cwtc = owd_connectow_state->cwtc;

		dwm_dbg_atomic(encodew->dev,
			       "[ENCODEW:%d:%s] in use on [CWTC:%d:%s], steawing it\n",
			       encodew->base.id, encodew->name,
			       encodew_cwtc->base.id, encodew_cwtc->name);

		set_best_encodew(state, new_connectow_state, NUWW);

		cwtc_state = dwm_atomic_get_new_cwtc_state(state, encodew_cwtc);
		cwtc_state->connectows_changed = twue;

		wetuwn;
	}
}

static int
update_connectow_wouting(stwuct dwm_atomic_state *state,
			 stwuct dwm_connectow *connectow,
			 stwuct dwm_connectow_state *owd_connectow_state,
			 stwuct dwm_connectow_state *new_connectow_state,
			 boow added_by_usew)
{
	const stwuct dwm_connectow_hewpew_funcs *funcs;
	stwuct dwm_encodew *new_encodew;
	stwuct dwm_cwtc_state *cwtc_state;

	dwm_dbg_atomic(connectow->dev, "Updating wouting fow [CONNECTOW:%d:%s]\n",
		       connectow->base.id, connectow->name);

	if (owd_connectow_state->cwtc != new_connectow_state->cwtc) {
		if (owd_connectow_state->cwtc) {
			cwtc_state = dwm_atomic_get_new_cwtc_state(state, owd_connectow_state->cwtc);
			cwtc_state->connectows_changed = twue;
		}

		if (new_connectow_state->cwtc) {
			cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_connectow_state->cwtc);
			cwtc_state->connectows_changed = twue;
		}
	}

	if (!new_connectow_state->cwtc) {
		dwm_dbg_atomic(connectow->dev, "Disabwing [CONNECTOW:%d:%s]\n",
				connectow->base.id, connectow->name);

		set_best_encodew(state, new_connectow_state, NUWW);

		wetuwn 0;
	}

	cwtc_state = dwm_atomic_get_new_cwtc_state(state,
						   new_connectow_state->cwtc);
	/*
	 * Fow compatibiwity with wegacy usews, we want to make suwe that
	 * we awwow DPMS On->Off modesets on unwegistewed connectows. Modesets
	 * which wouwd wesuwt in anything ewse must be considewed invawid, to
	 * avoid tuwning on new dispways on dead connectows.
	 *
	 * Since the connectow can be unwegistewed at any point duwing an
	 * atomic check ow commit, this is wacy. But that's OK: aww we cawe
	 * about is ensuwing that usewspace can't do anything but shut off the
	 * dispway on a connectow that was destwoyed aftew it's been notified,
	 * not befowe.
	 *
	 * Additionawwy, we awso want to ignowe connectow wegistwation when
	 * we'we twying to westowe an atomic state duwing system wesume since
	 * thewe's a chance the connectow may have been destwoyed duwing the
	 * pwocess, but it's bettew to ignowe that then cause
	 * dwm_atomic_hewpew_wesume() to faiw.
	 *
	 * Wast, we want to ignowe connectow wegistwation when the connectow
	 * was not puwwed in the atomic state by usew-space (ie, was puwwed
	 * in by the dwivew, e.g. when updating a DP-MST stweam).
	 */
	if (!state->dupwicated && dwm_connectow_is_unwegistewed(connectow) &&
	    added_by_usew && cwtc_state->active) {
		dwm_dbg_atomic(connectow->dev,
			       "[CONNECTOW:%d:%s] is not wegistewed\n",
			       connectow->base.id, connectow->name);
		wetuwn -EINVAW;
	}

	funcs = connectow->hewpew_pwivate;

	if (funcs->atomic_best_encodew)
		new_encodew = funcs->atomic_best_encodew(connectow, state);
	ewse if (funcs->best_encodew)
		new_encodew = funcs->best_encodew(connectow);
	ewse
		new_encodew = dwm_connectow_get_singwe_encodew(connectow);

	if (!new_encodew) {
		dwm_dbg_atomic(connectow->dev,
			       "No suitabwe encodew found fow [CONNECTOW:%d:%s]\n",
			       connectow->base.id, connectow->name);
		wetuwn -EINVAW;
	}

	if (!dwm_encodew_cwtc_ok(new_encodew, new_connectow_state->cwtc)) {
		dwm_dbg_atomic(connectow->dev,
			       "[ENCODEW:%d:%s] incompatibwe with [CWTC:%d:%s]\n",
			       new_encodew->base.id,
			       new_encodew->name,
			       new_connectow_state->cwtc->base.id,
			       new_connectow_state->cwtc->name);
		wetuwn -EINVAW;
	}

	if (new_encodew == new_connectow_state->best_encodew) {
		set_best_encodew(state, new_connectow_state, new_encodew);

		dwm_dbg_atomic(connectow->dev,
			       "[CONNECTOW:%d:%s] keeps [ENCODEW:%d:%s], now on [CWTC:%d:%s]\n",
			       connectow->base.id,
			       connectow->name,
			       new_encodew->base.id,
			       new_encodew->name,
			       new_connectow_state->cwtc->base.id,
			       new_connectow_state->cwtc->name);

		wetuwn 0;
	}

	steaw_encodew(state, new_encodew);

	set_best_encodew(state, new_connectow_state, new_encodew);

	cwtc_state->connectows_changed = twue;

	dwm_dbg_atomic(connectow->dev,
		       "[CONNECTOW:%d:%s] using [ENCODEW:%d:%s] on [CWTC:%d:%s]\n",
		       connectow->base.id,
		       connectow->name,
		       new_encodew->base.id,
		       new_encodew->name,
		       new_connectow_state->cwtc->base.id,
		       new_connectow_state->cwtc->name);

	wetuwn 0;
}

static int
mode_fixup(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	int i;
	int wet;

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (!new_cwtc_state->mode_changed &&
		    !new_cwtc_state->connectows_changed)
			continue;

		dwm_mode_copy(&new_cwtc_state->adjusted_mode, &new_cwtc_state->mode);
	}

	fow_each_new_connectow_in_state(state, connectow, new_conn_state, i) {
		const stwuct dwm_encodew_hewpew_funcs *funcs;
		stwuct dwm_encodew *encodew;
		stwuct dwm_bwidge *bwidge;

		WAWN_ON(!!new_conn_state->best_encodew != !!new_conn_state->cwtc);

		if (!new_conn_state->cwtc || !new_conn_state->best_encodew)
			continue;

		new_cwtc_state =
			dwm_atomic_get_new_cwtc_state(state, new_conn_state->cwtc);

		/*
		 * Each encodew has at most one connectow (since we awways steaw
		 * it away), so we won't caww ->mode_fixup twice.
		 */
		encodew = new_conn_state->best_encodew;
		funcs = encodew->hewpew_pwivate;

		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		wet = dwm_atomic_bwidge_chain_check(bwidge,
						    new_cwtc_state,
						    new_conn_state);
		if (wet) {
			dwm_dbg_atomic(encodew->dev, "Bwidge atomic check faiwed\n");
			wetuwn wet;
		}

		if (funcs && funcs->atomic_check) {
			wet = funcs->atomic_check(encodew, new_cwtc_state,
						  new_conn_state);
			if (wet) {
				dwm_dbg_atomic(encodew->dev,
					       "[ENCODEW:%d:%s] check faiwed\n",
					       encodew->base.id, encodew->name);
				wetuwn wet;
			}
		} ewse if (funcs && funcs->mode_fixup) {
			wet = funcs->mode_fixup(encodew, &new_cwtc_state->mode,
						&new_cwtc_state->adjusted_mode);
			if (!wet) {
				dwm_dbg_atomic(encodew->dev,
					       "[ENCODEW:%d:%s] fixup faiwed\n",
					       encodew->base.id, encodew->name);
				wetuwn -EINVAW;
			}
		}
	}

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		if (!new_cwtc_state->enabwe)
			continue;

		if (!new_cwtc_state->mode_changed &&
		    !new_cwtc_state->connectows_changed)
			continue;

		funcs = cwtc->hewpew_pwivate;
		if (!funcs || !funcs->mode_fixup)
			continue;

		wet = funcs->mode_fixup(cwtc, &new_cwtc_state->mode,
					&new_cwtc_state->adjusted_mode);
		if (!wet) {
			dwm_dbg_atomic(cwtc->dev, "[CWTC:%d:%s] fixup faiwed\n",
				       cwtc->base.id, cwtc->name);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static enum dwm_mode_status mode_vawid_path(stwuct dwm_connectow *connectow,
					    stwuct dwm_encodew *encodew,
					    stwuct dwm_cwtc *cwtc,
					    const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_bwidge *bwidge;
	enum dwm_mode_status wet;

	wet = dwm_encodew_mode_vawid(encodew, mode);
	if (wet != MODE_OK) {
		dwm_dbg_atomic(encodew->dev,
			       "[ENCODEW:%d:%s] mode_vawid() faiwed\n",
			       encodew->base.id, encodew->name);
		wetuwn wet;
	}

	bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
	wet = dwm_bwidge_chain_mode_vawid(bwidge, &connectow->dispway_info,
					  mode);
	if (wet != MODE_OK) {
		dwm_dbg_atomic(encodew->dev, "[BWIDGE] mode_vawid() faiwed\n");
		wetuwn wet;
	}

	wet = dwm_cwtc_mode_vawid(cwtc, mode);
	if (wet != MODE_OK) {
		dwm_dbg_atomic(encodew->dev, "[CWTC:%d:%s] mode_vawid() faiwed\n",
			       cwtc->base.id, cwtc->name);
		wetuwn wet;
	}

	wetuwn wet;
}

static int
mode_vawid(stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *connectow;
	int i;

	fow_each_new_connectow_in_state(state, connectow, conn_state, i) {
		stwuct dwm_encodew *encodew = conn_state->best_encodew;
		stwuct dwm_cwtc *cwtc = conn_state->cwtc;
		stwuct dwm_cwtc_state *cwtc_state;
		enum dwm_mode_status mode_status;
		const stwuct dwm_dispway_mode *mode;

		if (!cwtc || !encodew)
			continue;

		cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
		if (!cwtc_state)
			continue;
		if (!cwtc_state->mode_changed && !cwtc_state->connectows_changed)
			continue;

		mode = &cwtc_state->mode;

		mode_status = mode_vawid_path(connectow, encodew, cwtc, mode);
		if (mode_status != MODE_OK)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * dwm_atomic_hewpew_check_modeset - vawidate state object fow modeset changes
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * Check the state object to see if the wequested state is physicawwy possibwe.
 * This does aww the CWTC and connectow wewated computations fow an atomic
 * update and adds any additionaw connectows needed fow fuww modesets. It cawws
 * the vawious pew-object cawwbacks in the fowwow owdew:
 *
 * 1. &dwm_connectow_hewpew_funcs.atomic_best_encodew fow detewmining the new encodew.
 * 2. &dwm_connectow_hewpew_funcs.atomic_check to vawidate the connectow state.
 * 3. If it's detewmined a modeset is needed then aww connectows on the affected
 *    CWTC awe added and &dwm_connectow_hewpew_funcs.atomic_check is wun on them.
 * 4. &dwm_encodew_hewpew_funcs.mode_vawid, &dwm_bwidge_funcs.mode_vawid and
 *    &dwm_cwtc_hewpew_funcs.mode_vawid awe cawwed on the affected components.
 * 5. &dwm_bwidge_funcs.mode_fixup is cawwed on aww encodew bwidges.
 * 6. &dwm_encodew_hewpew_funcs.atomic_check is cawwed to vawidate any encodew state.
 *    This function is onwy cawwed when the encodew wiww be pawt of a configuwed CWTC,
 *    it must not be used fow impwementing connectow pwopewty vawidation.
 *    If this function is NUWW, &dwm_atomic_encodew_hewpew_funcs.mode_fixup is cawwed
 *    instead.
 * 7. &dwm_cwtc_hewpew_funcs.mode_fixup is cawwed wast, to fix up the mode with CWTC constwaints.
 *
 * &dwm_cwtc_state.mode_changed is set when the input mode is changed.
 * &dwm_cwtc_state.connectows_changed is set when a connectow is added ow
 * wemoved fwom the CWTC.  &dwm_cwtc_state.active_changed is set when
 * &dwm_cwtc_state.active changes, which is used fow DPMS.
 * &dwm_cwtc_state.no_vbwank is set fwom the wesuwt of dwm_dev_has_vbwank().
 * See awso: dwm_atomic_cwtc_needs_modeset()
 *
 * IMPOWTANT:
 *
 * Dwivews which set &dwm_cwtc_state.mode_changed (e.g. in theiw
 * &dwm_pwane_hewpew_funcs.atomic_check hooks if a pwane update can't be done
 * without a fuww modeset) _must_ caww this function aftew that change. It is
 * pewmitted to caww this function muwtipwe times fow the same update, e.g.
 * when the &dwm_cwtc_hewpew_funcs.atomic_check functions depend upon the
 * adjusted dotcwock fow fifo space awwocation and watewmawk computation.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int
dwm_atomic_hewpew_check_modeset(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *owd_connectow_state, *new_connectow_state;
	int i, wet;
	unsigned int connectows_mask = 0, usew_connectows_mask = 0;

	fow_each_owdnew_connectow_in_state(state, connectow, owd_connectow_state, new_connectow_state, i)
		usew_connectows_mask |= BIT(i);

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		boow has_connectows =
			!!new_cwtc_state->connectow_mask;

		WAWN_ON(!dwm_modeset_is_wocked(&cwtc->mutex));

		if (!dwm_mode_equaw(&owd_cwtc_state->mode, &new_cwtc_state->mode)) {
			dwm_dbg_atomic(dev, "[CWTC:%d:%s] mode changed\n",
				       cwtc->base.id, cwtc->name);
			new_cwtc_state->mode_changed = twue;
		}

		if (owd_cwtc_state->enabwe != new_cwtc_state->enabwe) {
			dwm_dbg_atomic(dev, "[CWTC:%d:%s] enabwe changed\n",
				       cwtc->base.id, cwtc->name);

			/*
			 * Fow cwawity this assignment is done hewe, but
			 * enabwe == 0 is onwy twue when thewe awe no
			 * connectows and a NUWW mode.
			 *
			 * The othew way awound is twue as weww. enabwe != 0
			 * impwies that connectows awe attached and a mode is set.
			 */
			new_cwtc_state->mode_changed = twue;
			new_cwtc_state->connectows_changed = twue;
		}

		if (owd_cwtc_state->active != new_cwtc_state->active) {
			dwm_dbg_atomic(dev, "[CWTC:%d:%s] active changed\n",
				       cwtc->base.id, cwtc->name);
			new_cwtc_state->active_changed = twue;
		}

		if (new_cwtc_state->enabwe != has_connectows) {
			dwm_dbg_atomic(dev, "[CWTC:%d:%s] enabwed/connectows mismatch\n",
				       cwtc->base.id, cwtc->name);

			wetuwn -EINVAW;
		}

		if (dwm_dev_has_vbwank(dev))
			new_cwtc_state->no_vbwank = fawse;
		ewse
			new_cwtc_state->no_vbwank = twue;
	}

	wet = handwe_confwicting_encodews(state, fawse);
	if (wet)
		wetuwn wet;

	fow_each_owdnew_connectow_in_state(state, connectow, owd_connectow_state, new_connectow_state, i) {
		const stwuct dwm_connectow_hewpew_funcs *funcs = connectow->hewpew_pwivate;

		WAWN_ON(!dwm_modeset_is_wocked(&dev->mode_config.connection_mutex));

		/*
		 * This onwy sets cwtc->connectows_changed fow wouting changes,
		 * dwivews must set cwtc->connectows_changed themsewves when
		 * connectow pwopewties need to be updated.
		 */
		wet = update_connectow_wouting(state, connectow,
					       owd_connectow_state,
					       new_connectow_state,
					       BIT(i) & usew_connectows_mask);
		if (wet)
			wetuwn wet;
		if (owd_connectow_state->cwtc) {
			new_cwtc_state = dwm_atomic_get_new_cwtc_state(state,
								       owd_connectow_state->cwtc);
			if (owd_connectow_state->wink_status !=
			    new_connectow_state->wink_status)
				new_cwtc_state->connectows_changed = twue;

			if (owd_connectow_state->max_wequested_bpc !=
			    new_connectow_state->max_wequested_bpc)
				new_cwtc_state->connectows_changed = twue;
		}

		if (funcs->atomic_check)
			wet = funcs->atomic_check(connectow, state);
		if (wet) {
			dwm_dbg_atomic(dev,
				       "[CONNECTOW:%d:%s] dwivew check faiwed\n",
				       connectow->base.id, connectow->name);
			wetuwn wet;
		}

		connectows_mask |= BIT(i);
	}

	/*
	 * Aftew aww the wouting has been pwepawed we need to add in any
	 * connectow which is itsewf unchanged, but whose CWTC changes its
	 * configuwation. This must be done befowe cawwing mode_fixup in case a
	 * cwtc onwy changed its mode but has the same set of connectows.
	 */
	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		if (!dwm_atomic_cwtc_needs_modeset(new_cwtc_state))
			continue;

		dwm_dbg_atomic(dev,
			       "[CWTC:%d:%s] needs aww connectows, enabwe: %c, active: %c\n",
			       cwtc->base.id, cwtc->name,
			       new_cwtc_state->enabwe ? 'y' : 'n',
			       new_cwtc_state->active ? 'y' : 'n');

		wet = dwm_atomic_add_affected_connectows(state, cwtc);
		if (wet != 0)
			wetuwn wet;

		wet = dwm_atomic_add_affected_pwanes(state, cwtc);
		if (wet != 0)
			wetuwn wet;
	}

	/*
	 * Itewate ovew aww connectows again, to make suwe atomic_check()
	 * has been cawwed on them when a modeset is fowced.
	 */
	fow_each_owdnew_connectow_in_state(state, connectow, owd_connectow_state, new_connectow_state, i) {
		const stwuct dwm_connectow_hewpew_funcs *funcs = connectow->hewpew_pwivate;

		if (connectows_mask & BIT(i))
			continue;

		if (funcs->atomic_check)
			wet = funcs->atomic_check(connectow, state);
		if (wet) {
			dwm_dbg_atomic(dev,
				       "[CONNECTOW:%d:%s] dwivew check faiwed\n",
				       connectow->base.id, connectow->name);
			wetuwn wet;
		}
	}

	/*
	 * Itewate ovew aww connectows again, and add aww affected bwidges to
	 * the state.
	 */
	fow_each_owdnew_connectow_in_state(state, connectow,
					   owd_connectow_state,
					   new_connectow_state, i) {
		stwuct dwm_encodew *encodew;

		encodew = owd_connectow_state->best_encodew;
		wet = dwm_atomic_add_encodew_bwidges(state, encodew);
		if (wet)
			wetuwn wet;

		encodew = new_connectow_state->best_encodew;
		wet = dwm_atomic_add_encodew_bwidges(state, encodew);
		if (wet)
			wetuwn wet;
	}

	wet = mode_vawid(state);
	if (wet)
		wetuwn wet;

	wetuwn mode_fixup(state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_modeset);

/**
 * dwm_atomic_hewpew_check_wb_connectow_state() - Check wwiteback connectow state
 * @connectow: cowwesponding connectow
 * @state: the dwivew state object
 *
 * Checks if the wwiteback connectow state is vawid, and wetuwns an ewwow if it
 * isn't.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int
dwm_atomic_hewpew_check_wb_connectow_state(stwuct dwm_connectow *connectow,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	stwuct dwm_wwiteback_job *wb_job = conn_state->wwiteback_job;
	stwuct dwm_pwopewty_bwob *pixew_fowmat_bwob;
	stwuct dwm_fwamebuffew *fb;
	size_t i, nfowmats;
	u32 *fowmats;

	if (!wb_job || !wb_job->fb)
		wetuwn 0;

	pixew_fowmat_bwob = wb_job->connectow->pixew_fowmats_bwob_ptw;
	nfowmats = pixew_fowmat_bwob->wength / sizeof(u32);
	fowmats = pixew_fowmat_bwob->data;
	fb = wb_job->fb;

	fow (i = 0; i < nfowmats; i++)
		if (fb->fowmat->fowmat == fowmats[i])
			wetuwn 0;

	dwm_dbg_kms(connectow->dev, "Invawid pixew fowmat %p4cc\n", &fb->fowmat->fowmat);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_wb_connectow_state);

/**
 * dwm_atomic_hewpew_check_pwane_state() - Check pwane state fow vawidity
 * @pwane_state: pwane state to check
 * @cwtc_state: CWTC state to check
 * @min_scawe: minimum @swc:@dest scawing factow in 16.16 fixed point
 * @max_scawe: maximum @swc:@dest scawing factow in 16.16 fixed point
 * @can_position: is it wegaw to position the pwane such that it
 *                doesn't covew the entiwe CWTC?  This wiww genewawwy
 *                onwy be fawse fow pwimawy pwanes.
 * @can_update_disabwed: can the pwane be updated whiwe the CWTC
 *                       is disabwed?
 *
 * Checks that a desiwed pwane update is vawid, and updates vawious
 * bits of dewived state (cwipped coowdinates etc.). Dwivews that pwovide
 * theiw own pwane handwing wathew than hewpew-pwovided impwementations may
 * stiww wish to caww this function to avoid dupwication of ewwow checking
 * code.
 *
 * WETUWNS:
 * Zewo if update appeaws vawid, ewwow code on faiwuwe
 */
int dwm_atomic_hewpew_check_pwane_state(stwuct dwm_pwane_state *pwane_state,
					const stwuct dwm_cwtc_state *cwtc_state,
					int min_scawe,
					int max_scawe,
					boow can_position,
					boow can_update_disabwed)
{
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_wect *swc = &pwane_state->swc;
	stwuct dwm_wect *dst = &pwane_state->dst;
	unsigned int wotation = pwane_state->wotation;
	stwuct dwm_wect cwip = {};
	int hscawe, vscawe;

	WAWN_ON(pwane_state->cwtc && pwane_state->cwtc != cwtc_state->cwtc);

	*swc = dwm_pwane_state_swc(pwane_state);
	*dst = dwm_pwane_state_dest(pwane_state);

	if (!fb) {
		pwane_state->visibwe = fawse;
		wetuwn 0;
	}

	/* cwtc shouwd onwy be NUWW when disabwing (i.e., !fb) */
	if (WAWN_ON(!pwane_state->cwtc)) {
		pwane_state->visibwe = fawse;
		wetuwn 0;
	}

	if (!cwtc_state->enabwe && !can_update_disabwed) {
		dwm_dbg_kms(pwane_state->pwane->dev,
			    "Cannot update pwane of a disabwed CWTC.\n");
		wetuwn -EINVAW;
	}

	dwm_wect_wotate(swc, fb->width << 16, fb->height << 16, wotation);

	/* Check scawing */
	hscawe = dwm_wect_cawc_hscawe(swc, dst, min_scawe, max_scawe);
	vscawe = dwm_wect_cawc_vscawe(swc, dst, min_scawe, max_scawe);
	if (hscawe < 0 || vscawe < 0) {
		dwm_dbg_kms(pwane_state->pwane->dev,
			    "Invawid scawing of pwane\n");
		dwm_wect_debug_pwint("swc: ", &pwane_state->swc, twue);
		dwm_wect_debug_pwint("dst: ", &pwane_state->dst, fawse);
		wetuwn -EWANGE;
	}

	if (cwtc_state->enabwe)
		dwm_mode_get_hv_timing(&cwtc_state->mode, &cwip.x2, &cwip.y2);

	pwane_state->visibwe = dwm_wect_cwip_scawed(swc, dst, &cwip);

	dwm_wect_wotate_inv(swc, fb->width << 16, fb->height << 16, wotation);

	if (!pwane_state->visibwe)
		/*
		 * Pwane isn't visibwe; some dwivews can handwe this
		 * so we just wetuwn success hewe.  Dwivews that can't
		 * (incwuding those that use the pwimawy pwane hewpew's
		 * update function) wiww wetuwn an ewwow fwom theiw
		 * update_pwane handwew.
		 */
		wetuwn 0;

	if (!can_position && !dwm_wect_equaws(dst, &cwip)) {
		dwm_dbg_kms(pwane_state->pwane->dev,
			    "Pwane must covew entiwe CWTC\n");
		dwm_wect_debug_pwint("dst: ", dst, fawse);
		dwm_wect_debug_pwint("cwip: ", &cwip, fawse);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_pwane_state);

/**
 * dwm_atomic_hewpew_check_cwtc_pwimawy_pwane() - Check CWTC state fow pwimawy pwane
 * @cwtc_state: CWTC state to check
 *
 * Checks that a CWTC has at weast one pwimawy pwane attached to it, which is
 * a wequiwement on some hawdwawe. Note that this onwy invowves the CWTC side
 * of the test. To test if the pwimawy pwane is visibwe ow if it can be updated
 * without the CWTC being enabwed, use dwm_atomic_hewpew_check_pwane_state() in
 * the pwane's atomic check.
 *
 * WETUWNS:
 * 0 if a pwimawy pwane is attached to the CWTC, ow an ewwow code othewwise
 */
int dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(stwuct dwm_cwtc_state *cwtc_state)
{
	stwuct dwm_cwtc *cwtc = cwtc_state->cwtc;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_pwane *pwane;

	/* needs at weast one pwimawy pwane to be enabwed */
	dwm_fow_each_pwane_mask(pwane, dev, cwtc_state->pwane_mask) {
		if (pwane->type == DWM_PWANE_TYPE_PWIMAWY)
			wetuwn 0;
	}

	dwm_dbg_atomic(dev, "[CWTC:%d:%s] pwimawy pwane missing\n", cwtc->base.id, cwtc->name);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_cwtc_pwimawy_pwane);

/**
 * dwm_atomic_hewpew_check_pwanes - vawidate state object fow pwanes changes
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * Check the state object to see if the wequested state is physicawwy possibwe.
 * This does aww the pwane update wewated checks using by cawwing into the
 * &dwm_cwtc_hewpew_funcs.atomic_check and &dwm_pwane_hewpew_funcs.atomic_check
 * hooks pwovided by the dwivew.
 *
 * It awso sets &dwm_cwtc_state.pwanes_changed to indicate that a CWTC has
 * updated pwanes.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int
dwm_atomic_hewpew_check_pwanes(stwuct dwm_device *dev,
			       stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state, *owd_pwane_state;
	int i, wet = 0;

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs;

		WAWN_ON(!dwm_modeset_is_wocked(&pwane->mutex));

		funcs = pwane->hewpew_pwivate;

		dwm_atomic_hewpew_pwane_changed(state, owd_pwane_state, new_pwane_state, pwane);

		dwm_atomic_hewpew_check_pwane_damage(state, new_pwane_state);

		if (!funcs || !funcs->atomic_check)
			continue;

		wet = funcs->atomic_check(pwane, state);
		if (wet) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] atomic dwivew check faiwed\n",
				       pwane->base.id, pwane->name);
			wetuwn wet;
		}
	}

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		funcs = cwtc->hewpew_pwivate;

		if (!funcs || !funcs->atomic_check)
			continue;

		wet = funcs->atomic_check(cwtc, state);
		if (wet) {
			dwm_dbg_atomic(cwtc->dev,
				       "[CWTC:%d:%s] atomic dwivew check faiwed\n",
				       cwtc->base.id, cwtc->name);
			wetuwn wet;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check_pwanes);

/**
 * dwm_atomic_hewpew_check - vawidate state object
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * Check the state object to see if the wequested state is physicawwy possibwe.
 * Onwy CWTCs and pwanes have check cawwbacks, so fow any additionaw (gwobaw)
 * checking that a dwivew needs it can simpwy wwap that awound this function.
 * Dwivews without such needs can diwectwy use this as theiw
 * &dwm_mode_config_funcs.atomic_check cawwback.
 *
 * This just wwaps the two pawts of the state checking fow pwanes and modeset
 * state in the defauwt owdew: Fiwst it cawws dwm_atomic_hewpew_check_modeset()
 * and then dwm_atomic_hewpew_check_pwanes(). The assumption is that the
 * @dwm_pwane_hewpew_funcs.atomic_check and @dwm_cwtc_hewpew_funcs.atomic_check
 * functions depend upon an updated adjusted_mode.cwock to e.g. pwopewwy compute
 * watewmawks.
 *
 * Note that zpos nowmawization wiww add aww enabwe pwanes to the state which
 * might not desiwed fow some dwivews.
 * Fow exampwe enabwe/disabwe of a cuwsow pwane which have fixed zpos vawue
 * wouwd twiggew aww othew enabwed pwanes to be fowced to the state change.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int dwm_atomic_hewpew_check(stwuct dwm_device *dev,
			    stwuct dwm_atomic_state *state)
{
	int wet;

	wet = dwm_atomic_hewpew_check_modeset(dev, state);
	if (wet)
		wetuwn wet;

	if (dev->mode_config.nowmawize_zpos) {
		wet = dwm_atomic_nowmawize_zpos(dev, state);
		if (wet)
			wetuwn wet;
	}

	wet = dwm_atomic_hewpew_check_pwanes(dev, state);
	if (wet)
		wetuwn wet;

	if (state->wegacy_cuwsow_update)
		state->async_update = !dwm_atomic_hewpew_async_check(dev, state);

	dwm_sewf_wefwesh_hewpew_awtew_state(state);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_check);

static boow
cwtc_needs_disabwe(stwuct dwm_cwtc_state *owd_state,
		   stwuct dwm_cwtc_state *new_state)
{
	/*
	 * No new_state means the CWTC is off, so the onwy cwitewia is whethew
	 * it's cuwwentwy active ow in sewf wefwesh mode.
	 */
	if (!new_state)
		wetuwn dwm_atomic_cwtc_effectivewy_active(owd_state);

	/*
	 * We need to disabwe bwidge(s) and CWTC if we'we twansitioning out of
	 * sewf-wefwesh and changing CWTCs at the same time, because the
	 * bwidge twacks sewf-wefwesh status via CWTC state.
	 */
	if (owd_state->sewf_wefwesh_active &&
	    owd_state->cwtc != new_state->cwtc)
		wetuwn twue;

	/*
	 * We awso need to wun thwough the cwtc_funcs->disabwe() function if
	 * the CWTC is cuwwentwy on, if it's twansitioning to sewf wefwesh
	 * mode, ow if it's in sewf wefwesh mode and needs to be fuwwy
	 * disabwed.
	 */
	wetuwn owd_state->active ||
	       (owd_state->sewf_wefwesh_active && !new_state->active) ||
	       new_state->sewf_wefwesh_active;
}

static void
disabwe_outputs(stwuct dwm_device *dev, stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	int i;

	fow_each_owdnew_connectow_in_state(owd_state, connectow, owd_conn_state, new_conn_state, i) {
		const stwuct dwm_encodew_hewpew_funcs *funcs;
		stwuct dwm_encodew *encodew;
		stwuct dwm_bwidge *bwidge;

		/*
		 * Shut down evewything that's in the changeset and cuwwentwy
		 * stiww on. So need to check the owd, saved state.
		 */
		if (!owd_conn_state->cwtc)
			continue;

		owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(owd_state, owd_conn_state->cwtc);

		if (new_conn_state->cwtc)
			new_cwtc_state = dwm_atomic_get_new_cwtc_state(
						owd_state,
						new_conn_state->cwtc);
		ewse
			new_cwtc_state = NUWW;

		if (!cwtc_needs_disabwe(owd_cwtc_state, new_cwtc_state) ||
		    !dwm_atomic_cwtc_needs_modeset(owd_conn_state->cwtc->state))
			continue;

		encodew = owd_conn_state->best_encodew;

		/* We shouwdn't get this faw if we didn't pweviouswy have
		 * an encodew.. but WAWN_ON() wathew than expwode.
		 */
		if (WAWN_ON(!encodew))
			continue;

		funcs = encodew->hewpew_pwivate;

		dwm_dbg_atomic(dev, "disabwing [ENCODEW:%d:%s]\n",
			       encodew->base.id, encodew->name);

		/*
		 * Each encodew has at most one connectow (since we awways steaw
		 * it away), so we won't caww disabwe hooks twice.
		 */
		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		dwm_atomic_bwidge_chain_disabwe(bwidge, owd_state);

		/* Wight function depends upon tawget state. */
		if (funcs) {
			if (funcs->atomic_disabwe)
				funcs->atomic_disabwe(encodew, owd_state);
			ewse if (new_conn_state->cwtc && funcs->pwepawe)
				funcs->pwepawe(encodew);
			ewse if (funcs->disabwe)
				funcs->disabwe(encodew);
			ewse if (funcs->dpms)
				funcs->dpms(encodew, DWM_MODE_DPMS_OFF);
		}

		dwm_atomic_bwidge_chain_post_disabwe(bwidge, owd_state);
	}

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;
		int wet;

		/* Shut down evewything that needs a fuww modeset. */
		if (!dwm_atomic_cwtc_needs_modeset(new_cwtc_state))
			continue;

		if (!cwtc_needs_disabwe(owd_cwtc_state, new_cwtc_state))
			continue;

		funcs = cwtc->hewpew_pwivate;

		dwm_dbg_atomic(dev, "disabwing [CWTC:%d:%s]\n",
			       cwtc->base.id, cwtc->name);


		/* Wight function depends upon tawget state. */
		if (new_cwtc_state->enabwe && funcs->pwepawe)
			funcs->pwepawe(cwtc);
		ewse if (funcs->atomic_disabwe)
			funcs->atomic_disabwe(cwtc, owd_state);
		ewse if (funcs->disabwe)
			funcs->disabwe(cwtc);
		ewse if (funcs->dpms)
			funcs->dpms(cwtc, DWM_MODE_DPMS_OFF);

		if (!dwm_dev_has_vbwank(dev))
			continue;

		wet = dwm_cwtc_vbwank_get(cwtc);
		/*
		 * Sewf-wefwesh is not a twue "disabwe"; ensuwe vbwank wemains
		 * enabwed.
		 */
		if (new_cwtc_state->sewf_wefwesh_active)
			WAWN_ONCE(wet != 0,
				  "dwivew disabwed vbwank in sewf-wefwesh\n");
		ewse
			WAWN_ONCE(wet != -EINVAW,
				  "dwivew fowgot to caww dwm_cwtc_vbwank_off()\n");
		if (wet == 0)
			dwm_cwtc_vbwank_put(cwtc);
	}
}

/**
 * dwm_atomic_hewpew_update_wegacy_modeset_state - update wegacy modeset state
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function updates aww the vawious wegacy modeset state pointews in
 * connectows, encodews and CWTCs.
 *
 * Dwivews can use this fow buiwding theiw own atomic commit if they don't have
 * a puwe hewpew-based modeset impwementation.
 *
 * Since these updates awe not synchwonized with wockings, onwy code paths
 * cawwed fwom &dwm_mode_config_hewpew_funcs.atomic_commit_taiw can wook at the
 * wegacy state fiwwed out by this hewpew. Defacto this means this hewpew and
 * the wegacy state pointews awe onwy weawwy usefuw fow twansitioning an
 * existing dwivew to the atomic wowwd.
 */
void
dwm_atomic_hewpew_update_wegacy_modeset_state(stwuct dwm_device *dev,
					      stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	int i;

	/* cweaw out existing winks and update dpms */
	fow_each_owdnew_connectow_in_state(owd_state, connectow, owd_conn_state, new_conn_state, i) {
		if (connectow->encodew) {
			WAWN_ON(!connectow->encodew->cwtc);

			connectow->encodew->cwtc = NUWW;
			connectow->encodew = NUWW;
		}

		cwtc = new_conn_state->cwtc;
		if ((!cwtc && owd_conn_state->cwtc) ||
		    (cwtc && dwm_atomic_cwtc_needs_modeset(cwtc->state))) {
			int mode = DWM_MODE_DPMS_OFF;

			if (cwtc && cwtc->state->active)
				mode = DWM_MODE_DPMS_ON;

			connectow->dpms = mode;
		}
	}

	/* set new winks */
	fow_each_new_connectow_in_state(owd_state, connectow, new_conn_state, i) {
		if (!new_conn_state->cwtc)
			continue;

		if (WAWN_ON(!new_conn_state->best_encodew))
			continue;

		connectow->encodew = new_conn_state->best_encodew;
		connectow->encodew->cwtc = new_conn_state->cwtc;
	}

	/* set wegacy state in the cwtc stwuctuwe */
	fow_each_new_cwtc_in_state(owd_state, cwtc, new_cwtc_state, i) {
		stwuct dwm_pwane *pwimawy = cwtc->pwimawy;
		stwuct dwm_pwane_state *new_pwane_state;

		cwtc->mode = new_cwtc_state->mode;
		cwtc->enabwed = new_cwtc_state->enabwe;

		new_pwane_state =
			dwm_atomic_get_new_pwane_state(owd_state, pwimawy);

		if (new_pwane_state && new_pwane_state->cwtc == cwtc) {
			cwtc->x = new_pwane_state->swc_x >> 16;
			cwtc->y = new_pwane_state->swc_y >> 16;
		}
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_update_wegacy_modeset_state);

/**
 * dwm_atomic_hewpew_cawc_timestamping_constants - update vbwank timestamping constants
 * @state: atomic state object
 *
 * Updates the timestamping constants used fow pwecise vbwank timestamps
 * by cawwing dwm_cawc_timestamping_constants() fow aww enabwed cwtcs in @state.
 */
void dwm_atomic_hewpew_cawc_timestamping_constants(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	int i;

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (new_cwtc_state->enabwe)
			dwm_cawc_timestamping_constants(cwtc,
							&new_cwtc_state->adjusted_mode);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_cawc_timestamping_constants);

static void
cwtc_set_mode(stwuct dwm_device *dev, stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	int i;

	fow_each_new_cwtc_in_state(owd_state, cwtc, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		if (!new_cwtc_state->mode_changed)
			continue;

		funcs = cwtc->hewpew_pwivate;

		if (new_cwtc_state->enabwe && funcs->mode_set_nofb) {
			dwm_dbg_atomic(dev, "modeset on [CWTC:%d:%s]\n",
				       cwtc->base.id, cwtc->name);

			funcs->mode_set_nofb(cwtc);
		}
	}

	fow_each_new_connectow_in_state(owd_state, connectow, new_conn_state, i) {
		const stwuct dwm_encodew_hewpew_funcs *funcs;
		stwuct dwm_encodew *encodew;
		stwuct dwm_dispway_mode *mode, *adjusted_mode;
		stwuct dwm_bwidge *bwidge;

		if (!new_conn_state->best_encodew)
			continue;

		encodew = new_conn_state->best_encodew;
		funcs = encodew->hewpew_pwivate;
		new_cwtc_state = new_conn_state->cwtc->state;
		mode = &new_cwtc_state->mode;
		adjusted_mode = &new_cwtc_state->adjusted_mode;

		if (!new_cwtc_state->mode_changed)
			continue;

		dwm_dbg_atomic(dev, "modeset on [ENCODEW:%d:%s]\n",
			       encodew->base.id, encodew->name);

		/*
		 * Each encodew has at most one connectow (since we awways steaw
		 * it away), so we won't caww mode_set hooks twice.
		 */
		if (funcs && funcs->atomic_mode_set) {
			funcs->atomic_mode_set(encodew, new_cwtc_state,
					       new_conn_state);
		} ewse if (funcs && funcs->mode_set) {
			funcs->mode_set(encodew, mode, adjusted_mode);
		}

		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		dwm_bwidge_chain_mode_set(bwidge, mode, adjusted_mode);
	}
}

/**
 * dwm_atomic_hewpew_commit_modeset_disabwes - modeset commit to disabwe outputs
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function shuts down aww the outputs that need to be shut down and
 * pwepawes them (if wequiwed) with the new mode.
 *
 * Fow compatibiwity with wegacy CWTC hewpews this shouwd be cawwed befowe
 * dwm_atomic_hewpew_commit_pwanes(), which is what the defauwt commit function
 * does. But dwivews with diffewent needs can gwoup the modeset commits togethew
 * and do the pwane commits at the end. This is usefuw fow dwivews doing wuntime
 * PM since pwanes updates then onwy happen when the CWTC is actuawwy enabwed.
 */
void dwm_atomic_hewpew_commit_modeset_disabwes(stwuct dwm_device *dev,
					       stwuct dwm_atomic_state *owd_state)
{
	disabwe_outputs(dev, owd_state);

	dwm_atomic_hewpew_update_wegacy_modeset_state(dev, owd_state);
	dwm_atomic_hewpew_cawc_timestamping_constants(owd_state);

	cwtc_set_mode(dev, owd_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_modeset_disabwes);

static void dwm_atomic_hewpew_commit_wwitebacks(stwuct dwm_device *dev,
						stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	int i;

	fow_each_new_connectow_in_state(owd_state, connectow, new_conn_state, i) {
		const stwuct dwm_connectow_hewpew_funcs *funcs;

		funcs = connectow->hewpew_pwivate;
		if (!funcs->atomic_commit)
			continue;

		if (new_conn_state->wwiteback_job && new_conn_state->wwiteback_job->fb) {
			WAWN_ON(connectow->connectow_type != DWM_MODE_CONNECTOW_WWITEBACK);
			funcs->atomic_commit(connectow, owd_state);
		}
	}
}

/**
 * dwm_atomic_hewpew_commit_modeset_enabwes - modeset commit to enabwe outputs
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function enabwes aww the outputs with the new configuwation which had to
 * be tuwned off fow the update.
 *
 * Fow compatibiwity with wegacy CWTC hewpews this shouwd be cawwed aftew
 * dwm_atomic_hewpew_commit_pwanes(), which is what the defauwt commit function
 * does. But dwivews with diffewent needs can gwoup the modeset commits togethew
 * and do the pwane commits at the end. This is usefuw fow dwivews doing wuntime
 * PM since pwanes updates then onwy happen when the CWTC is actuawwy enabwed.
 */
void dwm_atomic_hewpew_commit_modeset_enabwes(stwuct dwm_device *dev,
					      stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	int i;

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		/* Need to fiwtew out CWTCs whewe onwy pwanes change. */
		if (!dwm_atomic_cwtc_needs_modeset(new_cwtc_state))
			continue;

		if (!new_cwtc_state->active)
			continue;

		funcs = cwtc->hewpew_pwivate;

		if (new_cwtc_state->enabwe) {
			dwm_dbg_atomic(dev, "enabwing [CWTC:%d:%s]\n",
				       cwtc->base.id, cwtc->name);
			if (funcs->atomic_enabwe)
				funcs->atomic_enabwe(cwtc, owd_state);
			ewse if (funcs->commit)
				funcs->commit(cwtc);
		}
	}

	fow_each_new_connectow_in_state(owd_state, connectow, new_conn_state, i) {
		const stwuct dwm_encodew_hewpew_funcs *funcs;
		stwuct dwm_encodew *encodew;
		stwuct dwm_bwidge *bwidge;

		if (!new_conn_state->best_encodew)
			continue;

		if (!new_conn_state->cwtc->state->active ||
		    !dwm_atomic_cwtc_needs_modeset(new_conn_state->cwtc->state))
			continue;

		encodew = new_conn_state->best_encodew;
		funcs = encodew->hewpew_pwivate;

		dwm_dbg_atomic(dev, "enabwing [ENCODEW:%d:%s]\n",
			       encodew->base.id, encodew->name);

		/*
		 * Each encodew has at most one connectow (since we awways steaw
		 * it away), so we won't caww enabwe hooks twice.
		 */
		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		dwm_atomic_bwidge_chain_pwe_enabwe(bwidge, owd_state);

		if (funcs) {
			if (funcs->atomic_enabwe)
				funcs->atomic_enabwe(encodew, owd_state);
			ewse if (funcs->enabwe)
				funcs->enabwe(encodew);
			ewse if (funcs->commit)
				funcs->commit(encodew);
		}

		dwm_atomic_bwidge_chain_enabwe(bwidge, owd_state);
	}

	dwm_atomic_hewpew_commit_wwitebacks(dev, owd_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_modeset_enabwes);

/*
 * Fow atomic updates which touch just a singwe CWTC, cawcuwate the time of the
 * next vbwank, and infowm aww the fences of the deadwine.
 */
static void set_fence_deadwine(stwuct dwm_device *dev,
			       stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state;
	ktime_t vbwtime = 0;
	int i;

	fow_each_new_cwtc_in_state (state, cwtc, new_cwtc_state, i) {
		ktime_t v;

		if (dwm_atomic_cwtc_needs_modeset(new_cwtc_state))
			continue;

		if (!new_cwtc_state->active)
			continue;

		if (dwm_cwtc_next_vbwank_stawt(cwtc, &v))
			continue;

		if (!vbwtime || ktime_befowe(v, vbwtime))
			vbwtime = v;
	}

	/* If no CWTCs updated, then nothing to do: */
	if (!vbwtime)
		wetuwn;

	fow_each_new_pwane_in_state (state, pwane, new_pwane_state, i) {
		if (!new_pwane_state->fence)
			continue;
		dma_fence_set_deadwine(new_pwane_state->fence, vbwtime);
	}
}

/**
 * dwm_atomic_hewpew_wait_fow_fences - wait fow fences stashed in pwane state
 * @dev: DWM device
 * @state: atomic state object with owd state stwuctuwes
 * @pwe_swap: If twue, do an intewwuptibwe wait, and @state is the new state.
 *	Othewwise @state is the owd state.
 *
 * Fow impwicit sync, dwivew shouwd fish the excwusive fence out fwom the
 * incoming fb's and stash it in the dwm_pwane_state.  This is cawwed aftew
 * dwm_atomic_hewpew_swap_state() so it uses the cuwwent pwane state (and
 * just uses the atomic state to find the changed pwanes)
 *
 * Note that @pwe_swap is needed since the point whewe we bwock fow fences moves
 * awound depending upon whethew an atomic commit is bwocking ow
 * non-bwocking. Fow non-bwocking commit aww waiting needs to happen aftew
 * dwm_atomic_hewpew_swap_state() is cawwed, but fow bwocking commits we want
 * to wait **befowe** we do anything that can't be easiwy wowwed back. That is
 * befowe we caww dwm_atomic_hewpew_swap_state().
 *
 * Wetuwns zewo if success ow < 0 if dma_fence_wait() faiws.
 */
int dwm_atomic_hewpew_wait_fow_fences(stwuct dwm_device *dev,
				      stwuct dwm_atomic_state *state,
				      boow pwe_swap)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state;
	int i, wet;

	set_fence_deadwine(dev, state);

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		if (!new_pwane_state->fence)
			continue;

		WAWN_ON(!new_pwane_state->fb);

		/*
		 * If waiting fow fences pwe-swap (ie: nonbwock), usewspace can
		 * stiww intewwupt the opewation. Instead of bwocking untiw the
		 * timew expiwes, make the wait intewwuptibwe.
		 */
		wet = dma_fence_wait(new_pwane_state->fence, pwe_swap);
		if (wet)
			wetuwn wet;

		dma_fence_put(new_pwane_state->fence);
		new_pwane_state->fence = NUWW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_wait_fow_fences);

/**
 * dwm_atomic_hewpew_wait_fow_vbwanks - wait fow vbwank on CWTCs
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * Hewpew to, aftew atomic commit, wait fow vbwanks on aww affected
 * CWTCs (ie. befowe cweaning up owd fwamebuffews using
 * dwm_atomic_hewpew_cweanup_pwanes()). It wiww onwy wait on CWTCs whewe the
 * fwamebuffews have actuawwy changed to optimize fow the wegacy cuwsow and
 * pwane update use-case.
 *
 * Dwivews using the nonbwocking commit twacking suppowt initiawized by cawwing
 * dwm_atomic_hewpew_setup_commit() shouwd wook at
 * dwm_atomic_hewpew_wait_fow_fwip_done() as an awtewnative.
 */
void
dwm_atomic_hewpew_wait_fow_vbwanks(stwuct dwm_device *dev,
		stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	int i, wet;
	unsigned int cwtc_mask = 0;

	 /*
	  * Wegacy cuwsow ioctws awe compwetewy unsynced, and usewspace
	  * wewies on that (by doing tons of cuwsow updates).
	  */
	if (owd_state->wegacy_cuwsow_update)
		wetuwn;

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		if (!new_cwtc_state->active)
			continue;

		wet = dwm_cwtc_vbwank_get(cwtc);
		if (wet != 0)
			continue;

		cwtc_mask |= dwm_cwtc_mask(cwtc);
		owd_state->cwtcs[i].wast_vbwank_count = dwm_cwtc_vbwank_count(cwtc);
	}

	fow_each_owd_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, i) {
		if (!(cwtc_mask & dwm_cwtc_mask(cwtc)))
			continue;

		wet = wait_event_timeout(dev->vbwank[i].queue,
				owd_state->cwtcs[i].wast_vbwank_count !=
					dwm_cwtc_vbwank_count(cwtc),
				msecs_to_jiffies(100));

		WAWN(!wet, "[CWTC:%d:%s] vbwank wait timed out\n",
		     cwtc->base.id, cwtc->name);

		dwm_cwtc_vbwank_put(cwtc);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_wait_fow_vbwanks);

/**
 * dwm_atomic_hewpew_wait_fow_fwip_done - wait fow aww page fwips to be done
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * Hewpew to, aftew atomic commit, wait fow page fwips on aww affected
 * cwtcs (ie. befowe cweaning up owd fwamebuffews using
 * dwm_atomic_hewpew_cweanup_pwanes()). Compawed to
 * dwm_atomic_hewpew_wait_fow_vbwanks() this waits fow the compwetion on aww
 * CWTCs, assuming that cuwsows-onwy updates awe signawwing theiw compwetion
 * immediatewy (ow using a diffewent path).
 *
 * This wequiwes that dwivews use the nonbwocking commit twacking suppowt
 * initiawized using dwm_atomic_hewpew_setup_commit().
 */
void dwm_atomic_hewpew_wait_fow_fwip_done(stwuct dwm_device *dev,
					  stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	int i;

	fow (i = 0; i < dev->mode_config.num_cwtc; i++) {
		stwuct dwm_cwtc_commit *commit = owd_state->cwtcs[i].commit;
		int wet;

		cwtc = owd_state->cwtcs[i].ptw;

		if (!cwtc || !commit)
			continue;

		wet = wait_fow_compwetion_timeout(&commit->fwip_done, 10 * HZ);
		if (wet == 0)
			dwm_eww(dev, "[CWTC:%d:%s] fwip_done timed out\n",
				cwtc->base.id, cwtc->name);
	}

	if (owd_state->fake_commit)
		compwete_aww(&owd_state->fake_commit->fwip_done);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_wait_fow_fwip_done);

/**
 * dwm_atomic_hewpew_commit_taiw - commit atomic update to hawdwawe
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This is the defauwt impwementation fow the
 * &dwm_mode_config_hewpew_funcs.atomic_commit_taiw hook, fow dwivews
 * that do not suppowt wuntime_pm ow do not need the CWTC to be
 * enabwed to pewfowm a commit. Othewwise, see
 * dwm_atomic_hewpew_commit_taiw_wpm().
 *
 * Note that the defauwt owdewing of how the vawious stages awe cawwed is to
 * match the wegacy modeset hewpew wibwawy cwosest.
 */
void dwm_atomic_hewpew_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_pwanes(dev, owd_state, 0);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

	dwm_atomic_hewpew_fake_vbwank(owd_state);

	dwm_atomic_hewpew_commit_hw_done(owd_state);

	dwm_atomic_hewpew_wait_fow_vbwanks(dev, owd_state);

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_taiw);

/**
 * dwm_atomic_hewpew_commit_taiw_wpm - commit atomic update to hawdwawe
 * @owd_state: new modeset state to be committed
 *
 * This is an awtewnative impwementation fow the
 * &dwm_mode_config_hewpew_funcs.atomic_commit_taiw hook, fow dwivews
 * that suppowt wuntime_pm ow need the CWTC to be enabwed to pewfowm a
 * commit. Othewwise, one shouwd use the defauwt impwementation
 * dwm_atomic_hewpew_commit_taiw().
 */
void dwm_atomic_hewpew_commit_taiw_wpm(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_pwanes(dev, owd_state,
					DWM_PWANE_COMMIT_ACTIVE_ONWY);

	dwm_atomic_hewpew_fake_vbwank(owd_state);

	dwm_atomic_hewpew_commit_hw_done(owd_state);

	dwm_atomic_hewpew_wait_fow_vbwanks(dev, owd_state);

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_taiw_wpm);

static void commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;
	const stwuct dwm_mode_config_hewpew_funcs *funcs;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	ktime_t stawt;
	s64 commit_time_ms;
	unsigned int i, new_sewf_wefwesh_mask = 0;

	funcs = dev->mode_config.hewpew_pwivate;

	/*
	 * We'we measuwing the _entiwe_ commit, so the time wiww vawy depending
	 * on how many fences and objects awe invowved. Fow the puwposes of sewf
	 * wefwesh, this is desiwabwe since it'ww give us an idea of how
	 * congested things awe. This wiww infowm ouw decision on how often we
	 * shouwd entew sewf wefwesh aftew idwe.
	 *
	 * These times wiww be avewaged out in the sewf wefwesh hewpews to avoid
	 * ovewweacting ovew one outwiew fwame
	 */
	stawt = ktime_get();

	dwm_atomic_hewpew_wait_fow_fences(dev, owd_state, fawse);

	dwm_atomic_hewpew_wait_fow_dependencies(owd_state);

	/*
	 * We cannot safewy access new_cwtc_state aftew
	 * dwm_atomic_hewpew_commit_hw_done() so figuwe out which cwtc's have
	 * sewf-wefwesh active befowehand:
	 */
	fow_each_new_cwtc_in_state(owd_state, cwtc, new_cwtc_state, i)
		if (new_cwtc_state->sewf_wefwesh_active)
			new_sewf_wefwesh_mask |= BIT(i);

	if (funcs && funcs->atomic_commit_taiw)
		funcs->atomic_commit_taiw(owd_state);
	ewse
		dwm_atomic_hewpew_commit_taiw(owd_state);

	commit_time_ms = ktime_ms_dewta(ktime_get(), stawt);
	if (commit_time_ms > 0)
		dwm_sewf_wefwesh_hewpew_update_avg_times(owd_state,
						 (unsigned wong)commit_time_ms,
						 new_sewf_wefwesh_mask);

	dwm_atomic_hewpew_commit_cweanup_done(owd_state);

	dwm_atomic_state_put(owd_state);
}

static void commit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_atomic_state *state = containew_of(wowk,
						      stwuct dwm_atomic_state,
						      commit_wowk);
	commit_taiw(state);
}

/**
 * dwm_atomic_hewpew_async_check - check if state can be committed asynchwonouswy
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * This hewpew wiww check if it is possibwe to commit the state asynchwonouswy.
 * Async commits awe not supposed to swap the states wike nowmaw sync commits
 * but just do in-pwace changes on the cuwwent state.
 *
 * It wiww wetuwn 0 if the commit can happen in an asynchwonous fashion ow ewwow
 * if not. Note that ewwow just mean it can't be committed asynchwonouswy, if it
 * faiws the commit shouwd be tweated wike a nowmaw synchwonous commit.
 */
int dwm_atomic_hewpew_async_check(stwuct dwm_device *dev,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_pwane *pwane = NUWW;
	stwuct dwm_pwane_state *owd_pwane_state = NUWW;
	stwuct dwm_pwane_state *new_pwane_state = NUWW;
	const stwuct dwm_pwane_hewpew_funcs *funcs;
	int i, wet, n_pwanes = 0;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
			wetuwn -EINVAW;
	}

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i)
		n_pwanes++;

	/* FIXME: we suppowt onwy singwe pwane updates fow now */
	if (n_pwanes != 1) {
		dwm_dbg_atomic(dev,
			       "onwy singwe pwane async updates awe suppowted\n");
		wetuwn -EINVAW;
	}

	if (!new_pwane_state->cwtc ||
	    owd_pwane_state->cwtc != new_pwane_state->cwtc) {
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] async update cannot change CWTC\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	funcs = pwane->hewpew_pwivate;
	if (!funcs->atomic_async_update) {
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] dwivew does not suppowt async updates\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	if (new_pwane_state->fence) {
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] missing fence fow async update\n",
			       pwane->base.id, pwane->name);
		wetuwn -EINVAW;
	}

	/*
	 * Don't do an async update if thewe is an outstanding commit modifying
	 * the pwane.  This pwevents ouw async update's changes fwom getting
	 * ovewwidden by a pwevious synchwonous update's state.
	 */
	if (owd_pwane_state->commit &&
	    !twy_wait_fow_compwetion(&owd_pwane_state->commit->hw_done)) {
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] infwight pwevious commit pweventing async commit\n",
			       pwane->base.id, pwane->name);
		wetuwn -EBUSY;
	}

	wet = funcs->atomic_async_check(pwane, state);
	if (wet != 0)
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] dwivew async check faiwed\n",
			       pwane->base.id, pwane->name);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_async_check);

/**
 * dwm_atomic_hewpew_async_commit - commit state asynchwonouswy
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * This function commits a state asynchwonouswy, i.e., not vbwank
 * synchwonized. It shouwd be used on a state onwy when
 * dwm_atomic_async_check() succeeds. Async commits awe not supposed to swap
 * the states wike nowmaw sync commits, but just do in-pwace changes on the
 * cuwwent state.
 *
 * TODO: Impwement fuww swap instead of doing in-pwace changes.
 */
void dwm_atomic_hewpew_async_commit(stwuct dwm_device *dev,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *pwane_state;
	const stwuct dwm_pwane_hewpew_funcs *funcs;
	int i;

	fow_each_new_pwane_in_state(state, pwane, pwane_state, i) {
		stwuct dwm_fwamebuffew *new_fb = pwane_state->fb;
		stwuct dwm_fwamebuffew *owd_fb = pwane->state->fb;

		funcs = pwane->hewpew_pwivate;
		funcs->atomic_async_update(pwane, state);

		/*
		 * ->atomic_async_update() is supposed to update the
		 * pwane->state in-pwace, make suwe at weast common
		 * pwopewties have been pwopewwy updated.
		 */
		WAWN_ON_ONCE(pwane->state->fb != new_fb);
		WAWN_ON_ONCE(pwane->state->cwtc_x != pwane_state->cwtc_x);
		WAWN_ON_ONCE(pwane->state->cwtc_y != pwane_state->cwtc_y);
		WAWN_ON_ONCE(pwane->state->swc_x != pwane_state->swc_x);
		WAWN_ON_ONCE(pwane->state->swc_y != pwane_state->swc_y);

		/*
		 * Make suwe the FBs have been swapped so that cweanups in the
		 * new_state pewfowms a cweanup in the owd FB.
		 */
		WAWN_ON_ONCE(pwane_state->fb != owd_fb);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_async_commit);

/**
 * dwm_atomic_hewpew_commit - commit vawidated state object
 * @dev: DWM device
 * @state: the dwivew state object
 * @nonbwock: whethew nonbwocking behaviow is wequested.
 *
 * This function commits a with dwm_atomic_hewpew_check() pwe-vawidated state
 * object. This can stiww faiw when e.g. the fwamebuffew wesewvation faiws. This
 * function impwements nonbwocking commits, using
 * dwm_atomic_hewpew_setup_commit() and wewated functions.
 *
 * Committing the actuaw hawdwawe state is done thwough the
 * &dwm_mode_config_hewpew_funcs.atomic_commit_taiw cawwback, ow its defauwt
 * impwementation dwm_atomic_hewpew_commit_taiw().
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno.
 */
int dwm_atomic_hewpew_commit(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state,
			     boow nonbwock)
{
	int wet;

	if (state->async_update) {
		wet = dwm_atomic_hewpew_pwepawe_pwanes(dev, state);
		if (wet)
			wetuwn wet;

		dwm_atomic_hewpew_async_commit(dev, state);
		dwm_atomic_hewpew_unpwepawe_pwanes(dev, state);

		wetuwn 0;
	}

	wet = dwm_atomic_hewpew_setup_commit(state, nonbwock);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&state->commit_wowk, commit_wowk);

	wet = dwm_atomic_hewpew_pwepawe_pwanes(dev, state);
	if (wet)
		wetuwn wet;

	if (!nonbwock) {
		wet = dwm_atomic_hewpew_wait_fow_fences(dev, state, twue);
		if (wet)
			goto eww;
	}

	/*
	 * This is the point of no wetuwn - evewything bewow nevew faiws except
	 * when the hw goes bonghits. Which means we can commit the new state on
	 * the softwawe side now.
	 */

	wet = dwm_atomic_hewpew_swap_state(state, twue);
	if (wet)
		goto eww;

	/*
	 * Evewything bewow can be wun asynchwonouswy without the need to gwab
	 * any modeset wocks at aww undew one condition: It must be guawanteed
	 * that the asynchwonous wowk has eithew been cancewwed (if the dwivew
	 * suppowts it, which at weast wequiwes that the fwamebuffews get
	 * cweaned up with dwm_atomic_hewpew_cweanup_pwanes()) ow compweted
	 * befowe the new state gets committed on the softwawe side with
	 * dwm_atomic_hewpew_swap_state().
	 *
	 * This scheme awwows new atomic state updates to be pwepawed and
	 * checked in pawawwew to the asynchwonous compwetion of the pwevious
	 * update. Which is impowtant since compositows need to figuwe out the
	 * composition of the next fwame wight aftew having submitted the
	 * cuwwent wayout.
	 *
	 * NOTE: Commit wowk has muwtipwe phases, fiwst hawdwawe commit, then
	 * cweanup. We want them to ovewwap, hence need system_unbound_wq to
	 * make suwe wowk items don't awtificiawwy staww on each anothew.
	 */

	dwm_atomic_state_get(state);
	if (nonbwock)
		queue_wowk(system_unbound_wq, &state->commit_wowk);
	ewse
		commit_taiw(state);

	wetuwn 0;

eww:
	dwm_atomic_hewpew_unpwepawe_pwanes(dev, state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit);

/**
 * DOC: impwementing nonbwocking commit
 *
 * Nonbwocking atomic commits shouwd use stwuct &dwm_cwtc_commit to sequence
 * diffewent opewations against each anothew. Wocks, especiawwy stwuct
 * &dwm_modeset_wock, shouwd not be hewd in wowkew thweads ow any othew
 * asynchwonous context used to commit the hawdwawe state.
 *
 * dwm_atomic_hewpew_commit() impwements the wecommended sequence fow
 * nonbwocking commits, using dwm_atomic_hewpew_setup_commit() intewnawwy:
 *
 * 1. Wun dwm_atomic_hewpew_pwepawe_pwanes(). Since this can faiw and we
 * need to pwopagate out of memowy/VWAM ewwows to usewspace, it must be cawwed
 * synchwonouswy.
 *
 * 2. Synchwonize with any outstanding nonbwocking commit wowkew thweads which
 * might be affected by the new state update. This is handwed by
 * dwm_atomic_hewpew_setup_commit().
 *
 * Asynchwonous wowkews need to have sufficient pawawwewism to be abwe to wun
 * diffewent atomic commits on diffewent CWTCs in pawawwew. The simpwest way to
 * achieve this is by wunning them on the &system_unbound_wq wowk queue. Note
 * that dwivews awe not wequiwed to spwit up atomic commits and wun an
 * individuaw commit in pawawwew - usewspace is supposed to do that if it cawes.
 * But it might be beneficiaw to do that fow modesets, since those necessawiwy
 * must be done as one gwobaw opewation, and enabwing ow disabwing a CWTC can
 * take a wong time. But even that is not wequiwed.
 *
 * IMPOWTANT: A &dwm_atomic_state update fow muwtipwe CWTCs is sequenced
 * against aww CWTCs thewein. Thewefowe fow atomic state updates which onwy fwip
 * pwanes the dwivew must not get the stwuct &dwm_cwtc_state of unwewated CWTCs
 * in its atomic check code: This wouwd pwevent committing of atomic updates to
 * muwtipwe CWTCs in pawawwew. In genewaw, adding additionaw state stwuctuwes
 * shouwd be avoided as much as possibwe, because this weduces pawawwewism in
 * (nonbwocking) commits, both due to wocking and due to commit sequencing
 * wequiwements.
 *
 * 3. The softwawe state is updated synchwonouswy with
 * dwm_atomic_hewpew_swap_state(). Doing this undew the pwotection of aww modeset
 * wocks means concuwwent cawwews nevew see inconsistent state. Note that commit
 * wowkews do not howd any wocks; theiw access is onwy coowdinated thwough
 * owdewing. If wowkews wouwd access state onwy thwough the pointews in the
 * fwee-standing state objects (cuwwentwy not the case fow any dwivew) then even
 * muwtipwe pending commits couwd be in-fwight at the same time.
 *
 * 4. Scheduwe a wowk item to do aww subsequent steps, using the spwit-out
 * commit hewpews: a) pwe-pwane commit b) pwane commit c) post-pwane commit and
 * then cweaning up the fwamebuffews aftew the owd fwamebuffew is no wongew
 * being dispwayed. The scheduwed wowk shouwd synchwonize against othew wowkews
 * using the &dwm_cwtc_commit infwastwuctuwe as needed. See
 * dwm_atomic_hewpew_setup_commit() fow mowe detaiws.
 */

static int staww_checks(stwuct dwm_cwtc *cwtc, boow nonbwock)
{
	stwuct dwm_cwtc_commit *commit, *staww_commit = NUWW;
	boow compweted = twue;
	int i;
	wong wet = 0;

	spin_wock(&cwtc->commit_wock);
	i = 0;
	wist_fow_each_entwy(commit, &cwtc->commit_wist, commit_entwy) {
		if (i == 0) {
			compweted = twy_wait_fow_compwetion(&commit->fwip_done);
			/*
			 * Usewspace is not awwowed to get ahead of the pwevious
			 * commit with nonbwocking ones.
			 */
			if (!compweted && nonbwock) {
				spin_unwock(&cwtc->commit_wock);
				dwm_dbg_atomic(cwtc->dev,
					       "[CWTC:%d:%s] busy with a pwevious commit\n",
					       cwtc->base.id, cwtc->name);

				wetuwn -EBUSY;
			}
		} ewse if (i == 1) {
			staww_commit = dwm_cwtc_commit_get(commit);
			bweak;
		}

		i++;
	}
	spin_unwock(&cwtc->commit_wock);

	if (!staww_commit)
		wetuwn 0;

	/* We don't want to wet commits get ahead of cweanup wowk too much,
	 * stawwing on 2nd pwevious commit means twipwe-buffew won't evew staww.
	 */
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&staww_commit->cweanup_done,
							10*HZ);
	if (wet == 0)
		dwm_eww(cwtc->dev, "[CWTC:%d:%s] cweanup_done timed out\n",
			cwtc->base.id, cwtc->name);

	dwm_cwtc_commit_put(staww_commit);

	wetuwn wet < 0 ? wet : 0;
}

static void wewease_cwtc_commit(stwuct compwetion *compwetion)
{
	stwuct dwm_cwtc_commit *commit = containew_of(compwetion,
						      typeof(*commit),
						      fwip_done);

	dwm_cwtc_commit_put(commit);
}

static void init_commit(stwuct dwm_cwtc_commit *commit, stwuct dwm_cwtc *cwtc)
{
	init_compwetion(&commit->fwip_done);
	init_compwetion(&commit->hw_done);
	init_compwetion(&commit->cweanup_done);
	INIT_WIST_HEAD(&commit->commit_entwy);
	kwef_init(&commit->wef);
	commit->cwtc = cwtc;
}

static stwuct dwm_cwtc_commit *
cwtc_ow_fake_commit(stwuct dwm_atomic_state *state, stwuct dwm_cwtc *cwtc)
{
	if (cwtc) {
		stwuct dwm_cwtc_state *new_cwtc_state;

		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

		wetuwn new_cwtc_state->commit;
	}

	if (!state->fake_commit) {
		state->fake_commit = kzawwoc(sizeof(*state->fake_commit), GFP_KEWNEW);
		if (!state->fake_commit)
			wetuwn NUWW;

		init_commit(state->fake_commit, NUWW);
	}

	wetuwn state->fake_commit;
}

/**
 * dwm_atomic_hewpew_setup_commit - setup possibwy nonbwocking commit
 * @state: new modeset state to be committed
 * @nonbwock: whethew nonbwocking behaviow is wequested.
 *
 * This function pwepawes @state to be used by the atomic hewpew's suppowt fow
 * nonbwocking commits. Dwivews using the nonbwocking commit infwastwuctuwe
 * shouwd awways caww this function fwom theiw
 * &dwm_mode_config_funcs.atomic_commit hook.
 *
 * Dwivews that need to extend the commit setup to pwivate objects can use the
 * &dwm_mode_config_hewpew_funcs.atomic_commit_setup hook.
 *
 * To be abwe to use this suppowt dwivews need to use a few mowe hewpew
 * functions. dwm_atomic_hewpew_wait_fow_dependencies() must be cawwed befowe
 * actuawwy committing the hawdwawe state, and fow nonbwocking commits this caww
 * must be pwaced in the async wowkew. See awso dwm_atomic_hewpew_swap_state()
 * and its staww pawametew, fow when a dwivew's commit hooks wook at the
 * &dwm_cwtc.state, &dwm_pwane.state ow &dwm_connectow.state pointew diwectwy.
 *
 * Compwetion of the hawdwawe commit step must be signawwed using
 * dwm_atomic_hewpew_commit_hw_done(). Aftew this step the dwivew is not awwowed
 * to wead ow change any pewmanent softwawe ow hawdwawe modeset state. The onwy
 * exception is state pwotected by othew means than &dwm_modeset_wock wocks.
 * Onwy the fwee standing @state with pointews to the owd state stwuctuwes can
 * be inspected, e.g. to cwean up owd buffews using
 * dwm_atomic_hewpew_cweanup_pwanes().
 *
 * At the vewy end, befowe cweaning up @state dwivews must caww
 * dwm_atomic_hewpew_commit_cweanup_done().
 *
 * This is aww impwemented by in dwm_atomic_hewpew_commit(), giving dwivews a
 * compwete and easy-to-use defauwt impwementation of the atomic_commit() hook.
 *
 * The twacking of asynchwonouswy executed and stiww pending commits is done
 * using the cowe stwuctuwe &dwm_cwtc_commit.
 *
 * By defauwt thewe's no need to cwean up wesouwces awwocated by this function
 * expwicitwy: dwm_atomic_state_defauwt_cweaw() wiww take cawe of that
 * automaticawwy.
 *
 * Wetuwns:
 *
 * 0 on success. -EBUSY when usewspace scheduwes nonbwocking commits too fast,
 * -ENOMEM on awwocation faiwuwes and -EINTW when a signaw is pending.
 */
int dwm_atomic_hewpew_setup_commit(stwuct dwm_atomic_state *state,
				   boow nonbwock)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	stwuct dwm_cwtc_commit *commit;
	const stwuct dwm_mode_config_hewpew_funcs *funcs;
	int i, wet;

	funcs = state->dev->mode_config.hewpew_pwivate;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		commit = kzawwoc(sizeof(*commit), GFP_KEWNEW);
		if (!commit)
			wetuwn -ENOMEM;

		init_commit(commit, cwtc);

		new_cwtc_state->commit = commit;

		wet = staww_checks(cwtc, nonbwock);
		if (wet)
			wetuwn wet;

		/*
		 * Dwivews onwy send out events when at weast eithew cuwwent ow
		 * new CWTC state is active. Compwete wight away if evewything
		 * stays off.
		 */
		if (!owd_cwtc_state->active && !new_cwtc_state->active) {
			compwete_aww(&commit->fwip_done);
			continue;
		}

		/* Wegacy cuwsow updates awe fuwwy unsynced. */
		if (state->wegacy_cuwsow_update) {
			compwete_aww(&commit->fwip_done);
			continue;
		}

		if (!new_cwtc_state->event) {
			commit->event = kzawwoc(sizeof(*commit->event),
						GFP_KEWNEW);
			if (!commit->event)
				wetuwn -ENOMEM;

			new_cwtc_state->event = commit->event;
		}

		new_cwtc_state->event->base.compwetion = &commit->fwip_done;
		new_cwtc_state->event->base.compwetion_wewease = wewease_cwtc_commit;
		dwm_cwtc_commit_get(commit);

		commit->abowt_compwetion = twue;

		state->cwtcs[i].commit = commit;
		dwm_cwtc_commit_get(commit);
	}

	fow_each_owdnew_connectow_in_state(state, conn, owd_conn_state, new_conn_state, i) {
		/*
		 * Usewspace is not awwowed to get ahead of the pwevious
		 * commit with nonbwocking ones.
		 */
		if (nonbwock && owd_conn_state->commit &&
		    !twy_wait_fow_compwetion(&owd_conn_state->commit->fwip_done)) {
			dwm_dbg_atomic(conn->dev,
				       "[CONNECTOW:%d:%s] busy with a pwevious commit\n",
				       conn->base.id, conn->name);

			wetuwn -EBUSY;
		}

		/* Awways twack connectows expwicitwy fow e.g. wink wetwaining. */
		commit = cwtc_ow_fake_commit(state, new_conn_state->cwtc ?: owd_conn_state->cwtc);
		if (!commit)
			wetuwn -ENOMEM;

		new_conn_state->commit = dwm_cwtc_commit_get(commit);
	}

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		/*
		 * Usewspace is not awwowed to get ahead of the pwevious
		 * commit with nonbwocking ones.
		 */
		if (nonbwock && owd_pwane_state->commit &&
		    !twy_wait_fow_compwetion(&owd_pwane_state->commit->fwip_done)) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] busy with a pwevious commit\n",
				       pwane->base.id, pwane->name);

			wetuwn -EBUSY;
		}

		/* Awways twack pwanes expwicitwy fow async pagefwip suppowt. */
		commit = cwtc_ow_fake_commit(state, new_pwane_state->cwtc ?: owd_pwane_state->cwtc);
		if (!commit)
			wetuwn -ENOMEM;

		new_pwane_state->commit = dwm_cwtc_commit_get(commit);
	}

	if (funcs && funcs->atomic_commit_setup)
		wetuwn funcs->atomic_commit_setup(state);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_setup_commit);

/**
 * dwm_atomic_hewpew_wait_fow_dependencies - wait fow wequiwed pweceding commits
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function waits fow aww pweceding commits that touch the same CWTC as
 * @owd_state to both be committed to the hawdwawe (as signawwed by
 * dwm_atomic_hewpew_commit_hw_done()) and executed by the hawdwawe (as signawwed
 * by cawwing dwm_cwtc_send_vbwank_event() on the &dwm_cwtc_state.event).
 *
 * This is pawt of the atomic hewpew suppowt fow nonbwocking commits, see
 * dwm_atomic_hewpew_setup_commit() fow an ovewview.
 */
void dwm_atomic_hewpew_wait_fow_dependencies(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *owd_conn_state;
	int i;
	wong wet;

	fow_each_owd_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, i) {
		wet = dwm_cwtc_commit_wait(owd_cwtc_state->commit);
		if (wet)
			dwm_eww(cwtc->dev,
				"[CWTC:%d:%s] commit wait timed out\n",
				cwtc->base.id, cwtc->name);
	}

	fow_each_owd_connectow_in_state(owd_state, conn, owd_conn_state, i) {
		wet = dwm_cwtc_commit_wait(owd_conn_state->commit);
		if (wet)
			dwm_eww(conn->dev,
				"[CONNECTOW:%d:%s] commit wait timed out\n",
				conn->base.id, conn->name);
	}

	fow_each_owd_pwane_in_state(owd_state, pwane, owd_pwane_state, i) {
		wet = dwm_cwtc_commit_wait(owd_pwane_state->commit);
		if (wet)
			dwm_eww(pwane->dev,
				"[PWANE:%d:%s] commit wait timed out\n",
				pwane->base.id, pwane->name);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_wait_fow_dependencies);

/**
 * dwm_atomic_hewpew_fake_vbwank - fake VBWANK events if needed
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function wawks aww CWTCs and fakes VBWANK events on those with
 * &dwm_cwtc_state.no_vbwank set to twue and &dwm_cwtc_state.event != NUWW.
 * The pwimawy use of this function is wwiteback connectows wowking in oneshot
 * mode and faking VBWANK events. In this case they onwy fake the VBWANK event
 * when a job is queued, and any change to the pipewine that does not touch the
 * connectow is weading to timeouts when cawwing
 * dwm_atomic_hewpew_wait_fow_vbwanks() ow
 * dwm_atomic_hewpew_wait_fow_fwip_done(). In addition to wwiteback
 * connectows, this function can awso fake VBWANK events fow CWTCs without
 * VBWANK intewwupt.
 *
 * This is pawt of the atomic hewpew suppowt fow nonbwocking commits, see
 * dwm_atomic_hewpew_setup_commit() fow an ovewview.
 */
void dwm_atomic_hewpew_fake_vbwank(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	int i;

	fow_each_new_cwtc_in_state(owd_state, cwtc, new_cwtc_state, i) {
		unsigned wong fwags;

		if (!new_cwtc_state->no_vbwank)
			continue;

		spin_wock_iwqsave(&owd_state->dev->event_wock, fwags);
		if (new_cwtc_state->event) {
			dwm_cwtc_send_vbwank_event(cwtc,
						   new_cwtc_state->event);
			new_cwtc_state->event = NUWW;
		}
		spin_unwock_iwqwestowe(&owd_state->dev->event_wock, fwags);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_fake_vbwank);

/**
 * dwm_atomic_hewpew_commit_hw_done - setup possibwe nonbwocking commit
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function is used to signaw compwetion of the hawdwawe commit step. Aftew
 * this step the dwivew is not awwowed to wead ow change any pewmanent softwawe
 * ow hawdwawe modeset state. The onwy exception is state pwotected by othew
 * means than &dwm_modeset_wock wocks.
 *
 * Dwivews shouwd twy to postpone any expensive ow dewayed cweanup wowk aftew
 * this function is cawwed.
 *
 * This is pawt of the atomic hewpew suppowt fow nonbwocking commits, see
 * dwm_atomic_hewpew_setup_commit() fow an ovewview.
 */
void dwm_atomic_hewpew_commit_hw_done(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_cwtc_commit *commit;
	int i;

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		commit = new_cwtc_state->commit;
		if (!commit)
			continue;

		/*
		 * copy new_cwtc_state->commit to owd_cwtc_state->commit,
		 * it's unsafe to touch new_cwtc_state aftew hw_done,
		 * but we stiww need to do so in cweanup_done().
		 */
		if (owd_cwtc_state->commit)
			dwm_cwtc_commit_put(owd_cwtc_state->commit);

		owd_cwtc_state->commit = dwm_cwtc_commit_get(commit);

		/* backend must have consumed any event by now */
		WAWN_ON(new_cwtc_state->event);
		compwete_aww(&commit->hw_done);
	}

	if (owd_state->fake_commit) {
		compwete_aww(&owd_state->fake_commit->hw_done);
		compwete_aww(&owd_state->fake_commit->fwip_done);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_hw_done);

/**
 * dwm_atomic_hewpew_commit_cweanup_done - signaw compwetion of commit
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This signaws compwetion of the atomic update @owd_state, incwuding any
 * cweanup wowk. If used, it must be cawwed wight befowe cawwing
 * dwm_atomic_state_put().
 *
 * This is pawt of the atomic hewpew suppowt fow nonbwocking commits, see
 * dwm_atomic_hewpew_setup_commit() fow an ovewview.
 */
void dwm_atomic_hewpew_commit_cweanup_done(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	stwuct dwm_cwtc_commit *commit;
	int i;

	fow_each_owd_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, i) {
		commit = owd_cwtc_state->commit;
		if (WAWN_ON(!commit))
			continue;

		compwete_aww(&commit->cweanup_done);
		WAWN_ON(!twy_wait_fow_compwetion(&commit->hw_done));

		spin_wock(&cwtc->commit_wock);
		wist_dew(&commit->commit_entwy);
		spin_unwock(&cwtc->commit_wock);
	}

	if (owd_state->fake_commit) {
		compwete_aww(&owd_state->fake_commit->cweanup_done);
		WAWN_ON(!twy_wait_fow_compwetion(&owd_state->fake_commit->hw_done));
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_cweanup_done);

/**
 * dwm_atomic_hewpew_pwepawe_pwanes - pwepawe pwane wesouwces befowe commit
 * @dev: DWM device
 * @state: atomic state object with new state stwuctuwes
 *
 * This function pwepawes pwane state, specificawwy fwamebuffews, fow the new
 * configuwation, by cawwing &dwm_pwane_hewpew_funcs.pwepawe_fb. If any faiwuwe
 * is encountewed this function wiww caww &dwm_pwane_hewpew_funcs.cweanup_fb on
 * any awweady successfuwwy pwepawed fwamebuffew.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_atomic_hewpew_pwepawe_pwanes(stwuct dwm_device *dev,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state;
	int wet, i, j;

	fow_each_new_connectow_in_state(state, connectow, new_conn_state, i) {
		if (!new_conn_state->wwiteback_job)
			continue;

		wet = dwm_wwiteback_pwepawe_job(new_conn_state->wwiteback_job);
		if (wet < 0)
			wetuwn wet;
	}

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs;

		funcs = pwane->hewpew_pwivate;

		if (funcs->pwepawe_fb) {
			wet = funcs->pwepawe_fb(pwane, new_pwane_state);
			if (wet)
				goto faiw_pwepawe_fb;
		} ewse {
			WAWN_ON_ONCE(funcs->cweanup_fb);

			if (!dwm_cowe_check_featuwe(dev, DWIVEW_GEM))
				continue;

			wet = dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_pwane_state);
			if (wet)
				goto faiw_pwepawe_fb;
		}
	}

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (funcs->begin_fb_access) {
			wet = funcs->begin_fb_access(pwane, new_pwane_state);
			if (wet)
				goto faiw_begin_fb_access;
		}
	}

	wetuwn 0;

faiw_begin_fb_access:
	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, j) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (j >= i)
			continue;

		if (funcs->end_fb_access)
			funcs->end_fb_access(pwane, new_pwane_state);
	}
	i = j; /* set i to uppew wimit to cweanup aww pwanes */
faiw_pwepawe_fb:
	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, j) {
		const stwuct dwm_pwane_hewpew_funcs *funcs;

		if (j >= i)
			continue;

		funcs = pwane->hewpew_pwivate;

		if (funcs->cweanup_fb)
			funcs->cweanup_fb(pwane, new_pwane_state);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_pwepawe_pwanes);

/**
 * dwm_atomic_hewpew_unpwepawe_pwanes - wewease pwane wesouwces on abowts
 * @dev: DWM device
 * @state: atomic state object with owd state stwuctuwes
 *
 * This function cweans up pwane state, specificawwy fwamebuffews, fwom the
 * atomic state. It undoes the effects of dwm_atomic_hewpew_pwepawe_pwanes()
 * when abowting an atomic commit. Fow cweaning up aftew a successfuw commit
 * use dwm_atomic_hewpew_cweanup_pwanes().
 */
void dwm_atomic_hewpew_unpwepawe_pwanes(stwuct dwm_device *dev,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state;
	int i;

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (funcs->end_fb_access)
			funcs->end_fb_access(pwane, new_pwane_state);
	}

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (funcs->cweanup_fb)
			funcs->cweanup_fb(pwane, new_pwane_state);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_unpwepawe_pwanes);

static boow pwane_cwtc_active(const stwuct dwm_pwane_state *state)
{
	wetuwn state->cwtc && state->cwtc->state->active;
}

/**
 * dwm_atomic_hewpew_commit_pwanes - commit pwane state
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 * @fwags: fwags fow committing pwane state
 *
 * This function commits the new pwane state using the pwane and atomic hewpew
 * functions fow pwanes and CWTCs. It assumes that the atomic state has awweady
 * been pushed into the wewevant object state pointews, since this step can no
 * wongew faiw.
 *
 * It stiww wequiwes the gwobaw state object @owd_state to know which pwanes and
 * cwtcs need to be updated though.
 *
 * Note that this function does aww pwane updates acwoss aww CWTCs in one step.
 * If the hawdwawe can't suppowt this appwoach wook at
 * dwm_atomic_hewpew_commit_pwanes_on_cwtc() instead.
 *
 * Pwane pawametews can be updated by appwications whiwe the associated CWTC is
 * disabwed. The DWM/KMS cowe wiww stowe the pawametews in the pwane state,
 * which wiww be avaiwabwe to the dwivew when the CWTC is tuwned on. As a wesuwt
 * most dwivews don't need to be immediatewy notified of pwane updates fow a
 * disabwed CWTC.
 *
 * Unwess othewwise needed, dwivews awe advised to set the ACTIVE_ONWY fwag in
 * @fwags in owdew not to weceive pwane update notifications wewated to a
 * disabwed CWTC. This avoids the need to manuawwy ignowe pwane updates in
 * dwivew code when the dwivew and/ow hawdwawe can't ow just don't need to deaw
 * with updates on disabwed CWTCs, fow exampwe when suppowting wuntime PM.
 *
 * Dwivews may set the NO_DISABWE_AFTEW_MODESET fwag in @fwags if the wewevant
 * dispway contwowwews wequiwe to disabwe a CWTC's pwanes when the CWTC is
 * disabwed. This function wouwd skip the &dwm_pwane_hewpew_funcs.atomic_disabwe
 * caww fow a pwane if the CWTC of the owd pwane state needs a modesetting
 * opewation. Of couwse, the dwivews need to disabwe the pwanes in theiw CWTC
 * disabwe cawwbacks since no one ewse wouwd do that.
 *
 * The dwm_atomic_hewpew_commit() defauwt impwementation doesn't set the
 * ACTIVE_ONWY fwag to most cwosewy match the behaviouw of the wegacy hewpews.
 * This shouwd not be copied bwindwy by dwivews.
 */
void dwm_atomic_hewpew_commit_pwanes(stwuct dwm_device *dev,
				     stwuct dwm_atomic_state *owd_state,
				     uint32_t fwags)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	int i;
	boow active_onwy = fwags & DWM_PWANE_COMMIT_ACTIVE_ONWY;
	boow no_disabwe = fwags & DWM_PWANE_COMMIT_NO_DISABWE_AFTEW_MODESET;

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		funcs = cwtc->hewpew_pwivate;

		if (!funcs || !funcs->atomic_begin)
			continue;

		if (active_onwy && !new_cwtc_state->active)
			continue;

		funcs->atomic_begin(cwtc, owd_state);
	}

	fow_each_owdnew_pwane_in_state(owd_state, pwane, owd_pwane_state, new_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs;
		boow disabwing;

		funcs = pwane->hewpew_pwivate;

		if (!funcs)
			continue;

		disabwing = dwm_atomic_pwane_disabwing(owd_pwane_state,
						       new_pwane_state);

		if (active_onwy) {
			/*
			 * Skip pwanes wewated to inactive CWTCs. If the pwane
			 * is enabwed use the state of the cuwwent CWTC. If the
			 * pwane is being disabwed use the state of the owd
			 * CWTC to avoid skipping pwanes being disabwed on an
			 * active CWTC.
			 */
			if (!disabwing && !pwane_cwtc_active(new_pwane_state))
				continue;
			if (disabwing && !pwane_cwtc_active(owd_pwane_state))
				continue;
		}

		/*
		 * Speciaw-case disabwing the pwane if dwivews suppowt it.
		 */
		if (disabwing && funcs->atomic_disabwe) {
			stwuct dwm_cwtc_state *cwtc_state;

			cwtc_state = owd_pwane_state->cwtc->state;

			if (dwm_atomic_cwtc_needs_modeset(cwtc_state) &&
			    no_disabwe)
				continue;

			funcs->atomic_disabwe(pwane, owd_state);
		} ewse if (new_pwane_state->cwtc || disabwing) {
			funcs->atomic_update(pwane, owd_state);

			if (!disabwing && funcs->atomic_enabwe) {
				if (dwm_atomic_pwane_enabwing(owd_pwane_state, new_pwane_state))
					funcs->atomic_enabwe(pwane, owd_state);
			}
		}
	}

	fow_each_owdnew_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		const stwuct dwm_cwtc_hewpew_funcs *funcs;

		funcs = cwtc->hewpew_pwivate;

		if (!funcs || !funcs->atomic_fwush)
			continue;

		if (active_onwy && !new_cwtc_state->active)
			continue;

		funcs->atomic_fwush(cwtc, owd_state);
	}

	/*
	 * Signaw end of fwamebuffew access hewe befowe hw_done. Aftew hw_done,
	 * a watew commit might have awweady weweased the pwane state.
	 */
	fow_each_owd_pwane_in_state(owd_state, pwane, owd_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (funcs->end_fb_access)
			funcs->end_fb_access(pwane, owd_pwane_state);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_pwanes);

/**
 * dwm_atomic_hewpew_commit_pwanes_on_cwtc - commit pwane state fow a CWTC
 * @owd_cwtc_state: atomic state object with the owd CWTC state
 *
 * This function commits the new pwane state using the pwane and atomic hewpew
 * functions fow pwanes on the specific CWTC. It assumes that the atomic state
 * has awweady been pushed into the wewevant object state pointews, since this
 * step can no wongew faiw.
 *
 * This function is usefuw when pwane updates shouwd be done CWTC-by-CWTC
 * instead of one gwobaw step wike dwm_atomic_hewpew_commit_pwanes() does.
 *
 * This function can onwy be savewy used when pwanes awe not awwowed to move
 * between diffewent CWTCs because this function doesn't handwe intew-CWTC
 * dependencies. Cawwews need to ensuwe that eithew no such dependencies exist,
 * wesowve them thwough owdewing of commit cawws ow thwough some othew means.
 */
void
dwm_atomic_hewpew_commit_pwanes_on_cwtc(stwuct dwm_cwtc_state *owd_cwtc_state)
{
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs;
	stwuct dwm_cwtc *cwtc = owd_cwtc_state->cwtc;
	stwuct dwm_atomic_state *owd_state = owd_cwtc_state->state;
	stwuct dwm_cwtc_state *new_cwtc_state =
		dwm_atomic_get_new_cwtc_state(owd_state, cwtc);
	stwuct dwm_pwane *pwane;
	unsigned int pwane_mask;

	pwane_mask = owd_cwtc_state->pwane_mask;
	pwane_mask |= new_cwtc_state->pwane_mask;

	cwtc_funcs = cwtc->hewpew_pwivate;
	if (cwtc_funcs && cwtc_funcs->atomic_begin)
		cwtc_funcs->atomic_begin(cwtc, owd_state);

	dwm_fow_each_pwane_mask(pwane, cwtc->dev, pwane_mask) {
		stwuct dwm_pwane_state *owd_pwane_state =
			dwm_atomic_get_owd_pwane_state(owd_state, pwane);
		stwuct dwm_pwane_state *new_pwane_state =
			dwm_atomic_get_new_pwane_state(owd_state, pwane);
		const stwuct dwm_pwane_hewpew_funcs *pwane_funcs;
		boow disabwing;

		pwane_funcs = pwane->hewpew_pwivate;

		if (!owd_pwane_state || !pwane_funcs)
			continue;

		WAWN_ON(new_pwane_state->cwtc &&
			new_pwane_state->cwtc != cwtc);

		disabwing = dwm_atomic_pwane_disabwing(owd_pwane_state, new_pwane_state);

		if (disabwing && pwane_funcs->atomic_disabwe) {
			pwane_funcs->atomic_disabwe(pwane, owd_state);
		} ewse if (new_pwane_state->cwtc || disabwing) {
			pwane_funcs->atomic_update(pwane, owd_state);

			if (!disabwing && pwane_funcs->atomic_enabwe) {
				if (dwm_atomic_pwane_enabwing(owd_pwane_state, new_pwane_state))
					pwane_funcs->atomic_enabwe(pwane, owd_state);
			}
		}
	}

	if (cwtc_funcs && cwtc_funcs->atomic_fwush)
		cwtc_funcs->atomic_fwush(cwtc, owd_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_pwanes_on_cwtc);

/**
 * dwm_atomic_hewpew_disabwe_pwanes_on_cwtc - hewpew to disabwe CWTC's pwanes
 * @owd_cwtc_state: atomic state object with the owd CWTC state
 * @atomic: if set, synchwonize with CWTC's atomic_begin/fwush hooks
 *
 * Disabwes aww pwanes associated with the given CWTC. This can be
 * used fow instance in the CWTC hewpew atomic_disabwe cawwback to disabwe
 * aww pwanes.
 *
 * If the atomic-pawametew is set the function cawws the CWTC's
 * atomic_begin hook befowe and atomic_fwush hook aftew disabwing the
 * pwanes.
 *
 * It is a bug to caww this function without having impwemented the
 * &dwm_pwane_hewpew_funcs.atomic_disabwe pwane hook.
 */
void
dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(stwuct dwm_cwtc_state *owd_cwtc_state,
					 boow atomic)
{
	stwuct dwm_cwtc *cwtc = owd_cwtc_state->cwtc;
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs =
		cwtc->hewpew_pwivate;
	stwuct dwm_pwane *pwane;

	if (atomic && cwtc_funcs && cwtc_funcs->atomic_begin)
		cwtc_funcs->atomic_begin(cwtc, NUWW);

	dwm_atomic_cwtc_state_fow_each_pwane(pwane, owd_cwtc_state) {
		const stwuct dwm_pwane_hewpew_funcs *pwane_funcs =
			pwane->hewpew_pwivate;

		if (!pwane_funcs)
			continue;

		WAWN_ON(!pwane_funcs->atomic_disabwe);
		if (pwane_funcs->atomic_disabwe)
			pwane_funcs->atomic_disabwe(pwane, NUWW);
	}

	if (atomic && cwtc_funcs && cwtc_funcs->atomic_fwush)
		cwtc_funcs->atomic_fwush(cwtc, NUWW);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_disabwe_pwanes_on_cwtc);

/**
 * dwm_atomic_hewpew_cweanup_pwanes - cweanup pwane wesouwces aftew commit
 * @dev: DWM device
 * @owd_state: atomic state object with owd state stwuctuwes
 *
 * This function cweans up pwane state, specificawwy fwamebuffews, fwom the owd
 * configuwation. Hence the owd configuwation must be pewsewved in @owd_state to
 * be abwe to caww this function.
 *
 * This function may not be cawwed on the new state when the atomic update
 * faiws at any point aftew cawwing dwm_atomic_hewpew_pwepawe_pwanes(). Use
 * dwm_atomic_hewpew_unpwepawe_pwanes() in this case.
 */
void dwm_atomic_hewpew_cweanup_pwanes(stwuct dwm_device *dev,
				      stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state;
	int i;

	fow_each_owd_pwane_in_state(owd_state, pwane, owd_pwane_state, i) {
		const stwuct dwm_pwane_hewpew_funcs *funcs = pwane->hewpew_pwivate;

		if (funcs->cweanup_fb)
			funcs->cweanup_fb(pwane, owd_pwane_state);
	}
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_cweanup_pwanes);

/**
 * dwm_atomic_hewpew_swap_state - stowe atomic state into cuwwent sw state
 * @state: atomic state
 * @staww: staww fow pweceding commits
 *
 * This function stowes the atomic state into the cuwwent state pointews in aww
 * dwivew objects. It shouwd be cawwed aftew aww faiwing steps have been done
 * and succeeded, but befowe the actuaw hawdwawe state is committed.
 *
 * Fow cweanup and ewwow wecovewy the cuwwent state fow aww changed objects wiww
 * be swapped into @state.
 *
 * With that sequence it fits pewfectwy into the pwane pwepawe/cweanup sequence:
 *
 * 1. Caww dwm_atomic_hewpew_pwepawe_pwanes() with the staged atomic state.
 *
 * 2. Do any othew steps that might faiw.
 *
 * 3. Put the staged state into the cuwwent state pointews with this function.
 *
 * 4. Actuawwy commit the hawdwawe state.
 *
 * 5. Caww dwm_atomic_hewpew_cweanup_pwanes() with @state, which since step 3
 * contains the owd state. Awso do any othew cweanup wequiwed with that state.
 *
 * @staww must be set when nonbwocking commits fow this dwivew diwectwy access
 * the &dwm_pwane.state, &dwm_cwtc.state ow &dwm_connectow.state pointew. With
 * the cuwwent atomic hewpews this is awmost awways the case, since the hewpews
 * don't pass the wight state stwuctuwes to the cawwbacks.
 *
 * Wetuwns:
 *
 * Wetuwns 0 on success. Can wetuwn -EWESTAWTSYS when @staww is twue and the
 * waiting fow the pwevious commits has been intewwupted.
 */
int dwm_atomic_hewpew_swap_state(stwuct dwm_atomic_state *state,
				  boow staww)
{
	int i, wet;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	stwuct dwm_cwtc_commit *commit;
	stwuct dwm_pwivate_obj *obj;
	stwuct dwm_pwivate_state *owd_obj_state, *new_obj_state;

	if (staww) {
		/*
		 * We have to staww fow hw_done hewe befowe
		 * dwm_atomic_hewpew_wait_fow_dependencies() because fwip
		 * depth > 1 is not yet suppowted by aww dwivews. As wong as
		 * obj->state is diwectwy dewefewenced anywhewe in the dwivews
		 * atomic_commit_taiw function, then it's unsafe to swap state
		 * befowe dwm_atomic_hewpew_commit_hw_done() is cawwed.
		 */

		fow_each_owd_cwtc_in_state(state, cwtc, owd_cwtc_state, i) {
			commit = owd_cwtc_state->commit;

			if (!commit)
				continue;

			wet = wait_fow_compwetion_intewwuptibwe(&commit->hw_done);
			if (wet)
				wetuwn wet;
		}

		fow_each_owd_connectow_in_state(state, connectow, owd_conn_state, i) {
			commit = owd_conn_state->commit;

			if (!commit)
				continue;

			wet = wait_fow_compwetion_intewwuptibwe(&commit->hw_done);
			if (wet)
				wetuwn wet;
		}

		fow_each_owd_pwane_in_state(state, pwane, owd_pwane_state, i) {
			commit = owd_pwane_state->commit;

			if (!commit)
				continue;

			wet = wait_fow_compwetion_intewwuptibwe(&commit->hw_done);
			if (wet)
				wetuwn wet;
		}
	}

	fow_each_owdnew_connectow_in_state(state, connectow, owd_conn_state, new_conn_state, i) {
		WAWN_ON(connectow->state != owd_conn_state);

		owd_conn_state->state = state;
		new_conn_state->state = NUWW;

		state->connectows[i].state = owd_conn_state;
		connectow->state = new_conn_state;
	}

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		WAWN_ON(cwtc->state != owd_cwtc_state);

		owd_cwtc_state->state = state;
		new_cwtc_state->state = NUWW;

		state->cwtcs[i].state = owd_cwtc_state;
		cwtc->state = new_cwtc_state;

		if (new_cwtc_state->commit) {
			spin_wock(&cwtc->commit_wock);
			wist_add(&new_cwtc_state->commit->commit_entwy,
				 &cwtc->commit_wist);
			spin_unwock(&cwtc->commit_wock);

			new_cwtc_state->commit->event = NUWW;
		}
	}

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		WAWN_ON(pwane->state != owd_pwane_state);

		owd_pwane_state->state = state;
		new_pwane_state->state = NUWW;

		state->pwanes[i].state = owd_pwane_state;
		pwane->state = new_pwane_state;
	}

	fow_each_owdnew_pwivate_obj_in_state(state, obj, owd_obj_state, new_obj_state, i) {
		WAWN_ON(obj->state != owd_obj_state);

		owd_obj_state->state = state;
		new_obj_state->state = NUWW;

		state->pwivate_objs[i].state = owd_obj_state;
		obj->state = new_obj_state;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_swap_state);

/**
 * dwm_atomic_hewpew_update_pwane - Hewpew fow pwimawy pwane update using atomic
 * @pwane: pwane object to update
 * @cwtc: owning CWTC of owning pwane
 * @fb: fwamebuffew to fwip onto pwane
 * @cwtc_x: x offset of pwimawy pwane on @cwtc
 * @cwtc_y: y offset of pwimawy pwane on @cwtc
 * @cwtc_w: width of pwimawy pwane wectangwe on @cwtc
 * @cwtc_h: height of pwimawy pwane wectangwe on @cwtc
 * @swc_x: x offset of @fb fow panning
 * @swc_y: y offset of @fb fow panning
 * @swc_w: width of souwce wectangwe in @fb
 * @swc_h: height of souwce wectangwe in @fb
 * @ctx: wock acquiwe context
 *
 * Pwovides a defauwt pwane update handwew using the atomic dwivew intewface.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe
 */
int dwm_atomic_hewpew_update_pwane(stwuct dwm_pwane *pwane,
				   stwuct dwm_cwtc *cwtc,
				   stwuct dwm_fwamebuffew *fb,
				   int cwtc_x, int cwtc_y,
				   unsigned int cwtc_w, unsigned int cwtc_h,
				   uint32_t swc_x, uint32_t swc_y,
				   uint32_t swc_w, uint32_t swc_h,
				   stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_pwane_state *pwane_state;
	int wet = 0;

	state = dwm_atomic_state_awwoc(pwane->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;
	pwane_state = dwm_atomic_get_pwane_state(state, pwane);
	if (IS_EWW(pwane_state)) {
		wet = PTW_EWW(pwane_state);
		goto faiw;
	}

	wet = dwm_atomic_set_cwtc_fow_pwane(pwane_state, cwtc);
	if (wet != 0)
		goto faiw;
	dwm_atomic_set_fb_fow_pwane(pwane_state, fb);
	pwane_state->cwtc_x = cwtc_x;
	pwane_state->cwtc_y = cwtc_y;
	pwane_state->cwtc_w = cwtc_w;
	pwane_state->cwtc_h = cwtc_h;
	pwane_state->swc_x = swc_x;
	pwane_state->swc_y = swc_y;
	pwane_state->swc_w = swc_w;
	pwane_state->swc_h = swc_h;

	if (pwane == cwtc->cuwsow)
		state->wegacy_cuwsow_update = twue;

	wet = dwm_atomic_commit(state);
faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_update_pwane);

/**
 * dwm_atomic_hewpew_disabwe_pwane - Hewpew fow pwimawy pwane disabwe using atomic
 * @pwane: pwane to disabwe
 * @ctx: wock acquiwe context
 *
 * Pwovides a defauwt pwane disabwe handwew using the atomic dwivew intewface.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe
 */
int dwm_atomic_hewpew_disabwe_pwane(stwuct dwm_pwane *pwane,
				    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_pwane_state *pwane_state;
	int wet = 0;

	state = dwm_atomic_state_awwoc(pwane->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;
	pwane_state = dwm_atomic_get_pwane_state(state, pwane);
	if (IS_EWW(pwane_state)) {
		wet = PTW_EWW(pwane_state);
		goto faiw;
	}

	if (pwane_state->cwtc && pwane_state->cwtc->cuwsow == pwane)
		pwane_state->state->wegacy_cuwsow_update = twue;

	wet = __dwm_atomic_hewpew_disabwe_pwane(pwane, pwane_state);
	if (wet != 0)
		goto faiw;

	wet = dwm_atomic_commit(state);
faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_disabwe_pwane);

/**
 * dwm_atomic_hewpew_set_config - set a new config fwom usewspace
 * @set: mode set configuwation
 * @ctx: wock acquisition context
 *
 * Pwovides a defauwt CWTC set_config handwew using the atomic dwivew intewface.
 *
 * NOTE: Fow backwawds compatibiwity with owd usewspace this automaticawwy
 * wesets the "wink-status" pwopewty to GOOD, to fowce any wink
 * we-twaining. The SETCWTC ioctw does not define whethew an update does
 * need a fuww modeset ow just a pwane update, hence we'we awwowed to do
 * that. See awso dwm_connectow_set_wink_status_pwopewty().
 *
 * Wetuwns:
 * Wetuwns 0 on success, negative ewwno numbews on faiwuwe.
 */
int dwm_atomic_hewpew_set_config(stwuct dwm_mode_set *set,
				 stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_cwtc *cwtc = set->cwtc;
	int wet = 0;

	state = dwm_atomic_state_awwoc(cwtc->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;
	wet = __dwm_atomic_hewpew_set_config(set, state);
	if (wet != 0)
		goto faiw;

	wet = handwe_confwicting_encodews(state, twue);
	if (wet)
		goto faiw;

	wet = dwm_atomic_commit(state);

faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_set_config);

/**
 * dwm_atomic_hewpew_disabwe_aww - disabwe aww cuwwentwy active outputs
 * @dev: DWM device
 * @ctx: wock acquisition context
 *
 * Woops thwough aww connectows, finding those that awen't tuwned off and then
 * tuwns them off by setting theiw DPMS mode to OFF and deactivating the CWTC
 * that they awe connected to.
 *
 * This is used fow exampwe in suspend/wesume to disabwe aww cuwwentwy active
 * functions when suspending. If you just want to shut down evewything at e.g.
 * dwivew unwoad, wook at dwm_atomic_hewpew_shutdown().
 *
 * Note that if cawwews haven't awweady acquiwed aww modeset wocks this might
 * wetuwn -EDEADWK, which must be handwed by cawwing dwm_modeset_backoff().
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 *
 * See awso:
 * dwm_atomic_hewpew_suspend(), dwm_atomic_hewpew_wesume() and
 * dwm_atomic_hewpew_shutdown().
 */
int dwm_atomic_hewpew_disabwe_aww(stwuct dwm_device *dev,
				  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_connectow *conn;
	stwuct dwm_pwane_state *pwane_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	int wet, i;

	state = dwm_atomic_state_awwoc(dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;

	dwm_fow_each_cwtc(cwtc, dev) {
		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state)) {
			wet = PTW_EWW(cwtc_state);
			goto fwee;
		}

		cwtc_state->active = fawse;

		wet = dwm_atomic_set_mode_pwop_fow_cwtc(cwtc_state, NUWW);
		if (wet < 0)
			goto fwee;

		wet = dwm_atomic_add_affected_pwanes(state, cwtc);
		if (wet < 0)
			goto fwee;

		wet = dwm_atomic_add_affected_connectows(state, cwtc);
		if (wet < 0)
			goto fwee;
	}

	fow_each_new_connectow_in_state(state, conn, conn_state, i) {
		wet = dwm_atomic_set_cwtc_fow_connectow(conn_state, NUWW);
		if (wet < 0)
			goto fwee;
	}

	fow_each_new_pwane_in_state(state, pwane, pwane_state, i) {
		wet = dwm_atomic_set_cwtc_fow_pwane(pwane_state, NUWW);
		if (wet < 0)
			goto fwee;

		dwm_atomic_set_fb_fow_pwane(pwane_state, NUWW);
	}

	wet = dwm_atomic_commit(state);
fwee:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_disabwe_aww);

/**
 * dwm_atomic_hewpew_shutdown - shutdown aww CWTC
 * @dev: DWM device
 *
 * This shuts down aww CWTC, which is usefuw fow dwivew unwoading. Shutdown on
 * suspend shouwd instead be handwed with dwm_atomic_hewpew_suspend(), since
 * that awso takes a snapshot of the modeset state to be westowed on wesume.
 *
 * This is just a convenience wwappew awound dwm_atomic_hewpew_disabwe_aww(),
 * and it is the atomic vewsion of dwm_hewpew_fowce_disabwe_aww().
 */
void dwm_atomic_hewpew_shutdown(stwuct dwm_device *dev)
{
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet;

	if (dev == NUWW)
		wetuwn;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);

	wet = dwm_atomic_hewpew_disabwe_aww(dev, &ctx);
	if (wet)
		dwm_eww(dev,
			"Disabwing aww cwtc's duwing unwoad faiwed with %i\n",
			wet);

	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_shutdown);

/**
 * dwm_atomic_hewpew_dupwicate_state - dupwicate an atomic state object
 * @dev: DWM device
 * @ctx: wock acquisition context
 *
 * Makes a copy of the cuwwent atomic state by wooping ovew aww objects and
 * dupwicating theiw wespective states. This is used fow exampwe by suspend/
 * wesume suppowt code to save the state pwiow to suspend such that it can
 * be westowed upon wesume.
 *
 * Note that this tweats atomic state as pewsistent between save and westowe.
 * Dwivews must make suwe that this is possibwe and won't wesuwt in confusion
 * ow ewwoneous behaviouw.
 *
 * Note that if cawwews haven't awweady acquiwed aww modeset wocks this might
 * wetuwn -EDEADWK, which must be handwed by cawwing dwm_modeset_backoff().
 *
 * Wetuwns:
 * A pointew to the copy of the atomic state object on success ow an
 * EWW_PTW()-encoded ewwow code on faiwuwe.
 *
 * See awso:
 * dwm_atomic_hewpew_suspend(), dwm_atomic_hewpew_wesume()
 */
stwuct dwm_atomic_state *
dwm_atomic_hewpew_dupwicate_state(stwuct dwm_device *dev,
				  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc *cwtc;
	int eww = 0;

	state = dwm_atomic_state_awwoc(dev);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	state->acquiwe_ctx = ctx;
	state->dupwicated = twue;

	dwm_fow_each_cwtc(cwtc, dev) {
		stwuct dwm_cwtc_state *cwtc_state;

		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state)) {
			eww = PTW_EWW(cwtc_state);
			goto fwee;
		}
	}

	dwm_fow_each_pwane(pwane, dev) {
		stwuct dwm_pwane_state *pwane_state;

		pwane_state = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state)) {
			eww = PTW_EWW(pwane_state);
			goto fwee;
		}
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(conn, &conn_itew) {
		stwuct dwm_connectow_state *conn_state;

		conn_state = dwm_atomic_get_connectow_state(state, conn);
		if (IS_EWW(conn_state)) {
			eww = PTW_EWW(conn_state);
			dwm_connectow_wist_itew_end(&conn_itew);
			goto fwee;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	/* cweaw the acquiwe context so that it isn't accidentawwy weused */
	state->acquiwe_ctx = NUWW;

fwee:
	if (eww < 0) {
		dwm_atomic_state_put(state);
		state = EWW_PTW(eww);
	}

	wetuwn state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_dupwicate_state);

/**
 * dwm_atomic_hewpew_suspend - subsystem-wevew suspend hewpew
 * @dev: DWM device
 *
 * Dupwicates the cuwwent atomic state, disabwes aww active outputs and then
 * wetuwns a pointew to the owiginaw atomic state to the cawwew. Dwivews can
 * pass this pointew to the dwm_atomic_hewpew_wesume() hewpew upon wesume to
 * westowe the output configuwation that was active at the time the system
 * entewed suspend.
 *
 * Note that it is potentiawwy unsafe to use this. The atomic state object
 * wetuwned by this function is assumed to be pewsistent. Dwivews must ensuwe
 * that this howds twue. Befowe cawwing this function, dwivews must make suwe
 * to suspend fbdev emuwation so that nothing can be using the device.
 *
 * Wetuwns:
 * A pointew to a copy of the state befowe suspend on success ow an EWW_PTW()-
 * encoded ewwow code on faiwuwe. Dwivews shouwd stowe the wetuwned atomic
 * state object and pass it to the dwm_atomic_hewpew_wesume() hewpew upon
 * wesume.
 *
 * See awso:
 * dwm_atomic_hewpew_dupwicate_state(), dwm_atomic_hewpew_disabwe_aww(),
 * dwm_atomic_hewpew_wesume(), dwm_atomic_hewpew_commit_dupwicated_state()
 */
stwuct dwm_atomic_state *dwm_atomic_hewpew_suspend(stwuct dwm_device *dev)
{
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_atomic_state *state;
	int eww;

	/* This can nevew be wetuwned, but it makes the compiwew happy */
	state = EWW_PTW(-EINVAW);

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, eww);

	state = dwm_atomic_hewpew_dupwicate_state(dev, &ctx);
	if (IS_EWW(state))
		goto unwock;

	eww = dwm_atomic_hewpew_disabwe_aww(dev, &ctx);
	if (eww < 0) {
		dwm_atomic_state_put(state);
		state = EWW_PTW(eww);
		goto unwock;
	}

unwock:
	DWM_MODESET_WOCK_AWW_END(dev, ctx, eww);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_suspend);

/**
 * dwm_atomic_hewpew_commit_dupwicated_state - commit dupwicated state
 * @state: dupwicated atomic state to commit
 * @ctx: pointew to acquiwe_ctx to use fow commit.
 *
 * The state wetuwned by dwm_atomic_hewpew_dupwicate_state() and
 * dwm_atomic_hewpew_suspend() is pawtiawwy invawid, and needs to
 * be fixed up befowe commit.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 *
 * See awso:
 * dwm_atomic_hewpew_suspend()
 */
int dwm_atomic_hewpew_commit_dupwicated_state(stwuct dwm_atomic_state *state,
					      stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	int i, wet;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;

	state->acquiwe_ctx = ctx;

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i)
		state->pwanes[i].owd_state = pwane->state;

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i)
		state->cwtcs[i].owd_state = cwtc->state;

	fow_each_new_connectow_in_state(state, connectow, new_conn_state, i)
		state->connectows[i].owd_state = connectow->state;

	wet = dwm_atomic_commit(state);

	state->acquiwe_ctx = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_commit_dupwicated_state);

/**
 * dwm_atomic_hewpew_wesume - subsystem-wevew wesume hewpew
 * @dev: DWM device
 * @state: atomic state to wesume to
 *
 * Cawws dwm_mode_config_weset() to synchwonize hawdwawe and softwawe states,
 * gwabs aww modeset wocks and commits the atomic state object. This can be
 * used in conjunction with the dwm_atomic_hewpew_suspend() hewpew to
 * impwement suspend/wesume fow dwivews that suppowt atomic mode-setting.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 *
 * See awso:
 * dwm_atomic_hewpew_suspend()
 */
int dwm_atomic_hewpew_wesume(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state)
{
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int eww;

	dwm_mode_config_weset(dev);

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, eww);

	eww = dwm_atomic_hewpew_commit_dupwicated_state(state, &ctx);

	DWM_MODESET_WOCK_AWW_END(dev, ctx, eww);
	dwm_atomic_state_put(state);

	wetuwn eww;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_wesume);

static int page_fwip_common(stwuct dwm_atomic_state *state,
			    stwuct dwm_cwtc *cwtc,
			    stwuct dwm_fwamebuffew *fb,
			    stwuct dwm_pending_vbwank_event *event,
			    uint32_t fwags)
{
	stwuct dwm_pwane *pwane = cwtc->pwimawy;
	stwuct dwm_pwane_state *pwane_state;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet = 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	cwtc_state->event = event;
	cwtc_state->async_fwip = fwags & DWM_MODE_PAGE_FWIP_ASYNC;

	pwane_state = dwm_atomic_get_pwane_state(state, pwane);
	if (IS_EWW(pwane_state))
		wetuwn PTW_EWW(pwane_state);

	wet = dwm_atomic_set_cwtc_fow_pwane(pwane_state, cwtc);
	if (wet != 0)
		wetuwn wet;
	dwm_atomic_set_fb_fow_pwane(pwane_state, fb);

	/* Make suwe we don't accidentawwy do a fuww modeset. */
	state->awwow_modeset = fawse;
	if (!cwtc_state->active) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] disabwed, wejecting wegacy fwip\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * dwm_atomic_hewpew_page_fwip - execute a wegacy page fwip
 * @cwtc: DWM CWTC
 * @fb: DWM fwamebuffew
 * @event: optionaw DWM event to signaw upon compwetion
 * @fwags: fwip fwags fow non-vbwank sync'ed updates
 * @ctx: wock acquisition context
 *
 * Pwovides a defauwt &dwm_cwtc_funcs.page_fwip impwementation
 * using the atomic dwivew intewface.
 *
 * Wetuwns:
 * Wetuwns 0 on success, negative ewwno numbews on faiwuwe.
 *
 * See awso:
 * dwm_atomic_hewpew_page_fwip_tawget()
 */
int dwm_atomic_hewpew_page_fwip(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t fwags,
				stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_pwane *pwane = cwtc->pwimawy;
	stwuct dwm_atomic_state *state;
	int wet = 0;

	state = dwm_atomic_state_awwoc(pwane->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;

	wet = page_fwip_common(state, cwtc, fb, event, fwags);
	if (wet != 0)
		goto faiw;

	wet = dwm_atomic_nonbwocking_commit(state);
faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_page_fwip);

/**
 * dwm_atomic_hewpew_page_fwip_tawget - do page fwip on tawget vbwank pewiod.
 * @cwtc: DWM CWTC
 * @fb: DWM fwamebuffew
 * @event: optionaw DWM event to signaw upon compwetion
 * @fwags: fwip fwags fow non-vbwank sync'ed updates
 * @tawget: specifying the tawget vbwank pewiod when the fwip to take effect
 * @ctx: wock acquisition context
 *
 * Pwovides a defauwt &dwm_cwtc_funcs.page_fwip_tawget impwementation.
 * Simiwaw to dwm_atomic_hewpew_page_fwip() with extwa pawametew to specify
 * tawget vbwank pewiod to fwip.
 *
 * Wetuwns:
 * Wetuwns 0 on success, negative ewwno numbews on faiwuwe.
 */
int dwm_atomic_hewpew_page_fwip_tawget(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_fwamebuffew *fb,
				       stwuct dwm_pending_vbwank_event *event,
				       uint32_t fwags,
				       uint32_t tawget,
				       stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_pwane *pwane = cwtc->pwimawy;
	stwuct dwm_atomic_state *state;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet = 0;

	state = dwm_atomic_state_awwoc(pwane->dev);
	if (!state)
		wetuwn -ENOMEM;

	state->acquiwe_ctx = ctx;

	wet = page_fwip_common(state, cwtc, fb, event, fwags);
	if (wet != 0)
		goto faiw;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	if (WAWN_ON(!cwtc_state)) {
		wet = -EINVAW;
		goto faiw;
	}
	cwtc_state->tawget_vbwank = tawget;

	wet = dwm_atomic_nonbwocking_commit(state);
faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_page_fwip_tawget);

/**
 * dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt() - Pwopagate output fowmat to
 *						  the input end of a bwidge
 * @bwidge: bwidge contwow stwuctuwe
 * @bwidge_state: new bwidge state
 * @cwtc_state: new CWTC state
 * @conn_state: new connectow state
 * @output_fmt: tested output bus fowmat
 * @num_input_fmts: wiww contain the size of the wetuwned awway
 *
 * This hewpew is a pwuggabwe impwementation of the
 * &dwm_bwidge_funcs.atomic_get_input_bus_fmts opewation fow bwidges that don't
 * modify the bus configuwation between theiw input and theiw output. It
 * wetuwns an awway of input fowmats with a singwe ewement set to @output_fmt.
 *
 * WETUWNS:
 * a vawid fowmat awway of size @num_input_fmts, ow NUWW if the awwocation
 * faiwed
 */
u32 *
dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	input_fmts = kzawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts) {
		*num_input_fmts = 0;
		wetuwn NUWW;
	}

	*num_input_fmts = 1;
	input_fmts[0] = output_fmt;
	wetuwn input_fmts;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt);
