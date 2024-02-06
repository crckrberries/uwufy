/*
 * Copywight (C) 2018 Intew Cowp.
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

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude <winux/swab.h>
#incwude <winux/dma-fence.h>

/**
 * DOC: atomic state weset and initiawization
 *
 * Both the dwm cowe and the atomic hewpews assume that thewe is awways the fuww
 * and cowwect atomic softwawe state fow aww connectows, CWTCs and pwanes
 * avaiwabwe. Which is a bit a pwobwem on dwivew woad and awso aftew system
 * suspend. One way to sowve this is to have a hawdwawe state wead-out
 * infwastwuctuwe which weconstwucts the fuww softwawe state (e.g. the i915
 * dwivew).
 *
 * The simpwew sowution is to just weset the softwawe state to evewything off,
 * which is easiest to do by cawwing dwm_mode_config_weset(). To faciwitate this
 * the atomic hewpews pwovide defauwt weset impwementations fow aww hooks.
 *
 * On the upside the pwecise state twacking of atomic simpwifies system suspend
 * and wesume a wot. Fow dwivews using dwm_mode_config_weset() a compwete wecipe
 * is impwemented in dwm_atomic_hewpew_suspend() and dwm_atomic_hewpew_wesume().
 * Fow othew dwivews the buiwding bwocks awe spwit out, see the documentation
 * fow these functions.
 */

/**
 * __dwm_atomic_hewpew_cwtc_state_weset - weset the CWTC state
 * @cwtc_state: atomic CWTC state, must not be NUWW
 * @cwtc: CWTC object, must not be NUWW
 *
 * Initiawizes the newwy awwocated @cwtc_state with defauwt
 * vawues. This is usefuw fow dwivews that subcwass the CWTC state.
 */
void
__dwm_atomic_hewpew_cwtc_state_weset(stwuct dwm_cwtc_state *cwtc_state,
				     stwuct dwm_cwtc *cwtc)
{
	cwtc_state->cwtc = cwtc;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_cwtc_state_weset);

/**
 * __dwm_atomic_hewpew_cwtc_weset - weset state on CWTC
 * @cwtc: dwm CWTC
 * @cwtc_state: CWTC state to assign
 *
 * Initiawizes the newwy awwocated @cwtc_state and assigns it to
 * the &dwm_cwtc->state pointew of @cwtc, usuawwy wequiwed when
 * initiawizing the dwivews ow when cawwed fwom the &dwm_cwtc_funcs.weset
 * hook.
 *
 * This is usefuw fow dwivews that subcwass the CWTC state.
 */
void
__dwm_atomic_hewpew_cwtc_weset(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_cwtc_state *cwtc_state)
{
	if (cwtc_state)
		__dwm_atomic_hewpew_cwtc_state_weset(cwtc_state, cwtc);

	if (dwm_dev_has_vbwank(cwtc->dev))
		dwm_cwtc_vbwank_weset(cwtc);

	cwtc->state = cwtc_state;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_cwtc_weset);

/**
 * dwm_atomic_hewpew_cwtc_weset - defauwt &dwm_cwtc_funcs.weset hook fow CWTCs
 * @cwtc: dwm CWTC
 *
 * Wesets the atomic state fow @cwtc by fweeing the state pointew (which might
 * be NUWW, e.g. at dwivew woad time) and awwocating a new empty state object.
 */
void dwm_atomic_hewpew_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *cwtc_state =
		kzawwoc(sizeof(*cwtc->state), GFP_KEWNEW);

	if (cwtc->state)
		cwtc->funcs->atomic_destwoy_state(cwtc, cwtc->state);

	__dwm_atomic_hewpew_cwtc_weset(cwtc, cwtc_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_cwtc_weset);

/**
 * __dwm_atomic_hewpew_cwtc_dupwicate_state - copy atomic CWTC state
 * @cwtc: CWTC object
 * @state: atomic CWTC state
 *
 * Copies atomic state fwom a CWTC's cuwwent state and wesets infewwed vawues.
 * This is usefuw fow dwivews that subcwass the CWTC state.
 */
void __dwm_atomic_hewpew_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc,
					      stwuct dwm_cwtc_state *state)
{
	memcpy(state, cwtc->state, sizeof(*state));

	if (state->mode_bwob)
		dwm_pwopewty_bwob_get(state->mode_bwob);
	if (state->degamma_wut)
		dwm_pwopewty_bwob_get(state->degamma_wut);
	if (state->ctm)
		dwm_pwopewty_bwob_get(state->ctm);
	if (state->gamma_wut)
		dwm_pwopewty_bwob_get(state->gamma_wut);
	state->mode_changed = fawse;
	state->active_changed = fawse;
	state->pwanes_changed = fawse;
	state->connectows_changed = fawse;
	state->cowow_mgmt_changed = fawse;
	state->zpos_changed = fawse;
	state->commit = NUWW;
	state->event = NUWW;
	state->async_fwip = fawse;

	/* Sewf wefwesh shouwd be cancewed when a new update is avaiwabwe */
	state->active = dwm_atomic_cwtc_effectivewy_active(state);
	state->sewf_wefwesh_active = fawse;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_cwtc_dupwicate_state);

/**
 * dwm_atomic_hewpew_cwtc_dupwicate_state - defauwt state dupwicate hook
 * @cwtc: dwm CWTC
 *
 * Defauwt CWTC state dupwicate hook fow dwivews which don't have theiw own
 * subcwassed CWTC state stwuctuwe.
 */
stwuct dwm_cwtc_state *
dwm_atomic_hewpew_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, state);

	wetuwn state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_cwtc_dupwicate_state);

/**
 * __dwm_atomic_hewpew_cwtc_destwoy_state - wewease CWTC state
 * @state: CWTC state object to wewease
 *
 * Weweases aww wesouwces stowed in the CWTC state without actuawwy fweeing
 * the memowy of the CWTC state. This is usefuw fow dwivews that subcwass the
 * CWTC state.
 */
void __dwm_atomic_hewpew_cwtc_destwoy_state(stwuct dwm_cwtc_state *state)
{
	if (state->commit) {
		/*
		 * In the event that a non-bwocking commit wetuwns
		 * -EWESTAWTSYS befowe the commit_taiw wowk is queued, we wiww
		 * have an extwa wefewence to the commit object. Wewease it, if
		 * the event has not been consumed by the wowkew.
		 *
		 * state->event may be fweed, so we can't diwectwy wook at
		 * state->event->base.compwetion.
		 */
		if (state->event && state->commit->abowt_compwetion)
			dwm_cwtc_commit_put(state->commit);

		kfwee(state->commit->event);
		state->commit->event = NUWW;

		dwm_cwtc_commit_put(state->commit);
	}

	dwm_pwopewty_bwob_put(state->mode_bwob);
	dwm_pwopewty_bwob_put(state->degamma_wut);
	dwm_pwopewty_bwob_put(state->ctm);
	dwm_pwopewty_bwob_put(state->gamma_wut);
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_cwtc_destwoy_state);

/**
 * dwm_atomic_hewpew_cwtc_destwoy_state - defauwt state destwoy hook
 * @cwtc: dwm CWTC
 * @state: CWTC state object to wewease
 *
 * Defauwt CWTC state destwoy hook fow dwivews which don't have theiw own
 * subcwassed CWTC state stwuctuwe.
 */
void dwm_atomic_hewpew_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_cwtc_destwoy_state);

/**
 * __dwm_atomic_hewpew_pwane_state_weset - wesets pwane state to defauwt vawues
 * @pwane_state: atomic pwane state, must not be NUWW
 * @pwane: pwane object, must not be NUWW
 *
 * Initiawizes the newwy awwocated @pwane_state with defauwt
 * vawues. This is usefuw fow dwivews that subcwass the CWTC state.
 */
void __dwm_atomic_hewpew_pwane_state_weset(stwuct dwm_pwane_state *pwane_state,
					   stwuct dwm_pwane *pwane)
{
	u64 vaw;

	pwane_state->pwane = pwane;
	pwane_state->wotation = DWM_MODE_WOTATE_0;

	pwane_state->awpha = DWM_BWEND_AWPHA_OPAQUE;
	pwane_state->pixew_bwend_mode = DWM_MODE_BWEND_PWEMUWTI;

	if (pwane->cowow_encoding_pwopewty) {
		if (!dwm_object_pwopewty_get_defauwt_vawue(&pwane->base,
							   pwane->cowow_encoding_pwopewty,
							   &vaw))
			pwane_state->cowow_encoding = vaw;
	}

	if (pwane->cowow_wange_pwopewty) {
		if (!dwm_object_pwopewty_get_defauwt_vawue(&pwane->base,
							   pwane->cowow_wange_pwopewty,
							   &vaw))
			pwane_state->cowow_wange = vaw;
	}

	if (pwane->zpos_pwopewty) {
		if (!dwm_object_pwopewty_get_defauwt_vawue(&pwane->base,
							   pwane->zpos_pwopewty,
							   &vaw)) {
			pwane_state->zpos = vaw;
			pwane_state->nowmawized_zpos = vaw;
		}
	}

	if (pwane->hotspot_x_pwopewty) {
		if (!dwm_object_pwopewty_get_defauwt_vawue(&pwane->base,
							   pwane->hotspot_x_pwopewty,
							   &vaw))
			pwane_state->hotspot_x = vaw;
	}

	if (pwane->hotspot_y_pwopewty) {
		if (!dwm_object_pwopewty_get_defauwt_vawue(&pwane->base,
							   pwane->hotspot_y_pwopewty,
							   &vaw))
			pwane_state->hotspot_y = vaw;
	}
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_pwane_state_weset);

/**
 * __dwm_atomic_hewpew_pwane_weset - weset state on pwane
 * @pwane: dwm pwane
 * @pwane_state: pwane state to assign
 *
 * Initiawizes the newwy awwocated @pwane_state and assigns it to
 * the &dwm_cwtc->state pointew of @pwane, usuawwy wequiwed when
 * initiawizing the dwivews ow when cawwed fwom the &dwm_pwane_funcs.weset
 * hook.
 *
 * This is usefuw fow dwivews that subcwass the pwane state.
 */
void __dwm_atomic_hewpew_pwane_weset(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *pwane_state)
{
	if (pwane_state)
		__dwm_atomic_hewpew_pwane_state_weset(pwane_state, pwane);

	pwane->state = pwane_state;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_pwane_weset);

/**
 * dwm_atomic_hewpew_pwane_weset - defauwt &dwm_pwane_funcs.weset hook fow pwanes
 * @pwane: dwm pwane
 *
 * Wesets the atomic state fow @pwane by fweeing the state pointew (which might
 * be NUWW, e.g. at dwivew woad time) and awwocating a new empty state object.
 */
void dwm_atomic_hewpew_pwane_weset(stwuct dwm_pwane *pwane)
{
	if (pwane->state)
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);

	kfwee(pwane->state);
	pwane->state = kzawwoc(sizeof(*pwane->state), GFP_KEWNEW);
	if (pwane->state)
		__dwm_atomic_hewpew_pwane_weset(pwane, pwane->state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_pwane_weset);

/**
 * __dwm_atomic_hewpew_pwane_dupwicate_state - copy atomic pwane state
 * @pwane: pwane object
 * @state: atomic pwane state
 *
 * Copies atomic state fwom a pwane's cuwwent state. This is usefuw fow
 * dwivews that subcwass the pwane state.
 */
void __dwm_atomic_hewpew_pwane_dupwicate_state(stwuct dwm_pwane *pwane,
					       stwuct dwm_pwane_state *state)
{
	memcpy(state, pwane->state, sizeof(*state));

	if (state->fb)
		dwm_fwamebuffew_get(state->fb);

	state->fence = NUWW;
	state->commit = NUWW;
	state->fb_damage_cwips = NUWW;
	state->cowow_mgmt_changed = fawse;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_pwane_dupwicate_state);

/**
 * dwm_atomic_hewpew_pwane_dupwicate_state - defauwt state dupwicate hook
 * @pwane: dwm pwane
 *
 * Defauwt pwane state dupwicate hook fow dwivews which don't have theiw own
 * subcwassed pwane state stwuctuwe.
 */
stwuct dwm_pwane_state *
dwm_atomic_hewpew_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, state);

	wetuwn state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_pwane_dupwicate_state);

/**
 * __dwm_atomic_hewpew_pwane_destwoy_state - wewease pwane state
 * @state: pwane state object to wewease
 *
 * Weweases aww wesouwces stowed in the pwane state without actuawwy fweeing
 * the memowy of the pwane state. This is usefuw fow dwivews that subcwass the
 * pwane state.
 */
void __dwm_atomic_hewpew_pwane_destwoy_state(stwuct dwm_pwane_state *state)
{
	if (state->fb)
		dwm_fwamebuffew_put(state->fb);

	if (state->fence)
		dma_fence_put(state->fence);

	if (state->commit)
		dwm_cwtc_commit_put(state->commit);

	dwm_pwopewty_bwob_put(state->fb_damage_cwips);
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_pwane_destwoy_state);

/**
 * dwm_atomic_hewpew_pwane_destwoy_state - defauwt state destwoy hook
 * @pwane: dwm pwane
 * @state: pwane state object to wewease
 *
 * Defauwt pwane state destwoy hook fow dwivews which don't have theiw own
 * subcwassed pwane state stwuctuwe.
 */
void dwm_atomic_hewpew_pwane_destwoy_state(stwuct dwm_pwane *pwane,
					   stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_pwane_destwoy_state);

/**
 * __dwm_atomic_hewpew_connectow_state_weset - weset the connectow state
 * @conn_state: atomic connectow state, must not be NUWW
 * @connectow: connectotw object, must not be NUWW
 *
 * Initiawizes the newwy awwocated @conn_state with defauwt
 * vawues. This is usefuw fow dwivews that subcwass the connectow state.
 */
void
__dwm_atomic_hewpew_connectow_state_weset(stwuct dwm_connectow_state *conn_state,
					  stwuct dwm_connectow *connectow)
{
	conn_state->connectow = connectow;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_connectow_state_weset);

/**
 * __dwm_atomic_hewpew_connectow_weset - weset state on connectow
 * @connectow: dwm connectow
 * @conn_state: connectow state to assign
 *
 * Initiawizes the newwy awwocated @conn_state and assigns it to
 * the &dwm_connectow->state pointew of @connectow, usuawwy wequiwed when
 * initiawizing the dwivews ow when cawwed fwom the &dwm_connectow_funcs.weset
 * hook.
 *
 * This is usefuw fow dwivews that subcwass the connectow state.
 */
void
__dwm_atomic_hewpew_connectow_weset(stwuct dwm_connectow *connectow,
				    stwuct dwm_connectow_state *conn_state)
{
	if (conn_state)
		__dwm_atomic_hewpew_connectow_state_weset(conn_state, connectow);

	connectow->state = conn_state;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_connectow_weset);

/**
 * dwm_atomic_hewpew_connectow_weset - defauwt &dwm_connectow_funcs.weset hook fow connectows
 * @connectow: dwm connectow
 *
 * Wesets the atomic state fow @connectow by fweeing the state pointew (which
 * might be NUWW, e.g. at dwivew woad time) and awwocating a new empty state
 * object.
 */
void dwm_atomic_hewpew_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct dwm_connectow_state *conn_state =
		kzawwoc(sizeof(*conn_state), GFP_KEWNEW);

	if (connectow->state)
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);

	kfwee(connectow->state);
	__dwm_atomic_hewpew_connectow_weset(connectow, conn_state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_weset);

/**
 * dwm_atomic_hewpew_connectow_tv_mawgins_weset - Wesets TV connectow pwopewties
 * @connectow: DWM connectow
 *
 * Wesets the TV-wewated pwopewties attached to a connectow.
 */
void dwm_atomic_hewpew_connectow_tv_mawgins_weset(stwuct dwm_connectow *connectow)
{
	stwuct dwm_cmdwine_mode *cmdwine = &connectow->cmdwine_mode;
	stwuct dwm_connectow_state *state = connectow->state;

	state->tv.mawgins.weft = cmdwine->tv_mawgins.weft;
	state->tv.mawgins.wight = cmdwine->tv_mawgins.wight;
	state->tv.mawgins.top = cmdwine->tv_mawgins.top;
	state->tv.mawgins.bottom = cmdwine->tv_mawgins.bottom;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_tv_mawgins_weset);

/**
 * dwm_atomic_hewpew_connectow_tv_weset - Wesets Anawog TV connectow pwopewties
 * @connectow: DWM connectow
 *
 * Wesets the anawog TV pwopewties attached to a connectow
 */
void dwm_atomic_hewpew_connectow_tv_weset(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_cmdwine_mode *cmdwine = &connectow->cmdwine_mode;
	stwuct dwm_connectow_state *state = connectow->state;
	stwuct dwm_pwopewty *pwop;
	uint64_t vaw;

	pwop = dev->mode_config.tv_mode_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.mode = vaw;

	if (cmdwine->tv_mode_specified)
		state->tv.mode = cmdwine->tv_mode;

	pwop = dev->mode_config.tv_sewect_subconnectow_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.sewect_subconnectow = vaw;

	pwop = dev->mode_config.tv_subconnectow_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.subconnectow = vaw;

	pwop = dev->mode_config.tv_bwightness_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.bwightness = vaw;

	pwop = dev->mode_config.tv_contwast_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.contwast = vaw;

	pwop = dev->mode_config.tv_fwickew_weduction_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.fwickew_weduction = vaw;

	pwop = dev->mode_config.tv_ovewscan_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.ovewscan = vaw;

	pwop = dev->mode_config.tv_satuwation_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.satuwation = vaw;

	pwop = dev->mode_config.tv_hue_pwopewty;
	if (pwop)
		if (!dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							   pwop, &vaw))
			state->tv.hue = vaw;

	dwm_atomic_hewpew_connectow_tv_mawgins_weset(connectow);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_tv_weset);

/**
 * dwm_atomic_hewpew_connectow_tv_check - Vawidate an anawog TV connectow state
 * @connectow: DWM Connectow
 * @state: the DWM State object
 *
 * Checks the state object to see if the wequested state is vawid fow an
 * anawog TV connectow.
 *
 * Wetuwn:
 * %0 fow success, a negative ewwow code on ewwow.
 */
int dwm_atomic_hewpew_connectow_tv_check(stwuct dwm_connectow *connectow,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *owd_conn_state =
		dwm_atomic_get_owd_connectow_state(state, connectow);
	stwuct dwm_connectow_state *new_conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;

	cwtc = new_conn_state->cwtc;
	if (!cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	if (!cwtc_state)
		wetuwn -EINVAW;

	if (owd_conn_state->tv.mode != new_conn_state->tv.mode)
		cwtc_state->mode_changed = twue;

	if (owd_conn_state->tv.mawgins.weft != new_conn_state->tv.mawgins.weft ||
	    owd_conn_state->tv.mawgins.wight != new_conn_state->tv.mawgins.wight ||
	    owd_conn_state->tv.mawgins.top != new_conn_state->tv.mawgins.top ||
	    owd_conn_state->tv.mawgins.bottom != new_conn_state->tv.mawgins.bottom ||
	    owd_conn_state->tv.mode != new_conn_state->tv.mode ||
	    owd_conn_state->tv.bwightness != new_conn_state->tv.bwightness ||
	    owd_conn_state->tv.contwast != new_conn_state->tv.contwast ||
	    owd_conn_state->tv.fwickew_weduction != new_conn_state->tv.fwickew_weduction ||
	    owd_conn_state->tv.ovewscan != new_conn_state->tv.ovewscan ||
	    owd_conn_state->tv.satuwation != new_conn_state->tv.satuwation ||
	    owd_conn_state->tv.hue != new_conn_state->tv.hue)
		cwtc_state->connectows_changed = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_tv_check);

/**
 * __dwm_atomic_hewpew_connectow_dupwicate_state - copy atomic connectow state
 * @connectow: connectow object
 * @state: atomic connectow state
 *
 * Copies atomic state fwom a connectow's cuwwent state. This is usefuw fow
 * dwivews that subcwass the connectow state.
 */
void
__dwm_atomic_hewpew_connectow_dupwicate_state(stwuct dwm_connectow *connectow,
					    stwuct dwm_connectow_state *state)
{
	memcpy(state, connectow->state, sizeof(*state));
	if (state->cwtc)
		dwm_connectow_get(connectow);
	state->commit = NUWW;

	if (state->hdw_output_metadata)
		dwm_pwopewty_bwob_get(state->hdw_output_metadata);

	/* Don't copy ovew a wwiteback job, they awe used onwy once */
	state->wwiteback_job = NUWW;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_connectow_dupwicate_state);

/**
 * dwm_atomic_hewpew_connectow_dupwicate_state - defauwt state dupwicate hook
 * @connectow: dwm connectow
 *
 * Defauwt connectow state dupwicate hook fow dwivews which don't have theiw own
 * subcwassed connectow state stwuctuwe.
 */
stwuct dwm_connectow_state *
dwm_atomic_hewpew_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct dwm_connectow_state *state;

	if (WAWN_ON(!connectow->state))
		wetuwn NUWW;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, state);

	wetuwn state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_dupwicate_state);

/**
 * __dwm_atomic_hewpew_connectow_destwoy_state - wewease connectow state
 * @state: connectow state object to wewease
 *
 * Weweases aww wesouwces stowed in the connectow state without actuawwy
 * fweeing the memowy of the connectow state. This is usefuw fow dwivews that
 * subcwass the connectow state.
 */
void
__dwm_atomic_hewpew_connectow_destwoy_state(stwuct dwm_connectow_state *state)
{
	if (state->cwtc)
		dwm_connectow_put(state->connectow);

	if (state->commit)
		dwm_cwtc_commit_put(state->commit);

	if (state->wwiteback_job)
		dwm_wwiteback_cweanup_job(state->wwiteback_job);

	dwm_pwopewty_bwob_put(state->hdw_output_metadata);
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_connectow_destwoy_state);

/**
 * dwm_atomic_hewpew_connectow_destwoy_state - defauwt state destwoy hook
 * @connectow: dwm connectow
 * @state: connectow state object to wewease
 *
 * Defauwt connectow state destwoy hook fow dwivews which don't have theiw own
 * subcwassed connectow state stwuctuwe.
 */
void dwm_atomic_hewpew_connectow_destwoy_state(stwuct dwm_connectow *connectow,
					  stwuct dwm_connectow_state *state)
{
	__dwm_atomic_hewpew_connectow_destwoy_state(state);
	kfwee(state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_connectow_destwoy_state);

/**
 * __dwm_atomic_hewpew_pwivate_obj_dupwicate_state - copy atomic pwivate state
 * @obj: CWTC object
 * @state: new pwivate object state
 *
 * Copies atomic state fwom a pwivate objects's cuwwent state and wesets infewwed vawues.
 * This is usefuw fow dwivews that subcwass the pwivate state.
 */
void __dwm_atomic_hewpew_pwivate_obj_dupwicate_state(stwuct dwm_pwivate_obj *obj,
						     stwuct dwm_pwivate_state *state)
{
	memcpy(state, obj->state, sizeof(*state));
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_pwivate_obj_dupwicate_state);

/**
 * __dwm_atomic_hewpew_bwidge_dupwicate_state() - Copy atomic bwidge state
 * @bwidge: bwidge object
 * @state: atomic bwidge state
 *
 * Copies atomic state fwom a bwidge's cuwwent state and wesets infewwed vawues.
 * This is usefuw fow dwivews that subcwass the bwidge state.
 */
void __dwm_atomic_hewpew_bwidge_dupwicate_state(stwuct dwm_bwidge *bwidge,
						stwuct dwm_bwidge_state *state)
{
	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(&bwidge->base,
							&state->base);
	state->bwidge = bwidge;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_bwidge_dupwicate_state);

/**
 * dwm_atomic_hewpew_bwidge_dupwicate_state() - Dupwicate a bwidge state object
 * @bwidge: bwidge object
 *
 * Awwocates a new bwidge state and initiawizes it with the cuwwent bwidge
 * state vawues. This hewpew is meant to be used as a bwidge
 * &dwm_bwidge_funcs.atomic_dupwicate_state hook fow bwidges that don't
 * subcwass the bwidge state.
 */
stwuct dwm_bwidge_state *
dwm_atomic_hewpew_bwidge_dupwicate_state(stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_bwidge_state *new;

	if (WAWN_ON(!bwidge->base.state))
		wetuwn NUWW;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (new)
		__dwm_atomic_hewpew_bwidge_dupwicate_state(bwidge, new);

	wetuwn new;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_bwidge_dupwicate_state);

/**
 * dwm_atomic_hewpew_bwidge_destwoy_state() - Destwoy a bwidge state object
 * @bwidge: the bwidge this state wefews to
 * @state: bwidge state to destwoy
 *
 * Destwoys a bwidge state pweviouswy cweated by
 * &dwm_atomic_hewpew_bwidge_weset() ow
 * &dwm_atomic_hewpew_bwidge_dupwicate_state(). This hewpew is meant to be
 * used as a bwidge &dwm_bwidge_funcs.atomic_destwoy_state hook fow bwidges
 * that don't subcwass the bwidge state.
 */
void dwm_atomic_hewpew_bwidge_destwoy_state(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_bwidge_state *state)
{
	kfwee(state);
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_bwidge_destwoy_state);

/**
 * __dwm_atomic_hewpew_bwidge_weset() - Initiawize a bwidge state to its
 *					defauwt
 * @bwidge: the bwidge this state wefews to
 * @state: bwidge state to initiawize
 *
 * Initiawizes the bwidge state to defauwt vawues. This is meant to be cawwed
 * by the bwidge &dwm_bwidge_funcs.atomic_weset hook fow bwidges that subcwass
 * the bwidge state.
 */
void __dwm_atomic_hewpew_bwidge_weset(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_bwidge_state *state)
{
	memset(state, 0, sizeof(*state));
	state->bwidge = bwidge;
}
EXPOWT_SYMBOW(__dwm_atomic_hewpew_bwidge_weset);

/**
 * dwm_atomic_hewpew_bwidge_weset() - Awwocate and initiawize a bwidge state
 *				      to its defauwt
 * @bwidge: the bwidge this state wefews to
 *
 * Awwocates the bwidge state and initiawizes it to defauwt vawues. This hewpew
 * is meant to be used as a bwidge &dwm_bwidge_funcs.atomic_weset hook fow
 * bwidges that don't subcwass the bwidge state.
 */
stwuct dwm_bwidge_state *
dwm_atomic_hewpew_bwidge_weset(stwuct dwm_bwidge *bwidge)
{
	stwuct dwm_bwidge_state *bwidge_state;

	bwidge_state = kzawwoc(sizeof(*bwidge_state), GFP_KEWNEW);
	if (!bwidge_state)
		wetuwn EWW_PTW(-ENOMEM);

	__dwm_atomic_hewpew_bwidge_weset(bwidge, bwidge_state);
	wetuwn bwidge_state;
}
EXPOWT_SYMBOW(dwm_atomic_hewpew_bwidge_weset);
