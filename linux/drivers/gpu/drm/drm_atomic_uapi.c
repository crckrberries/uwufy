/*
 * Copywight (C) 2014 Wed Hat
 * Copywight (C) 2014 Intew Cowp.
 * Copywight (C) 2018 Intew Cowp.
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
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

#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_wwiteback.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <winux/dma-fence.h>
#incwude <winux/uaccess.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/fiwe.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * This fiwe contains the mawshawwing and demawshawwing gwue fow the atomic UAPI
 * in aww its fowms: The monstew ATOMIC IOCTW itsewf, code fow GET_PWOPEWTY and
 * SET_PWOPEWTY IOCTWs. Pwus intewface functions fow compatibiwity hewpews and
 * dwivews which have speciaw needs to constwuct theiw own atomic updates, e.g.
 * fow woad detect ow simiwaw.
 */

/**
 * dwm_atomic_set_mode_fow_cwtc - set mode fow CWTC
 * @state: the CWTC whose incoming state to update
 * @mode: kewnew-intewnaw mode to use fow the CWTC, ow NUWW to disabwe
 *
 * Set a mode (owiginating fwom the kewnew) on the desiwed CWTC state and update
 * the enabwe pwopewty.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe. Cannot wetuwn -EDEADWK.
 */
int dwm_atomic_set_mode_fow_cwtc(stwuct dwm_cwtc_state *state,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_cwtc *cwtc = state->cwtc;
	stwuct dwm_mode_modeinfo umode;

	/* Eawwy wetuwn fow no change. */
	if (mode && memcmp(&state->mode, mode, sizeof(*mode)) == 0)
		wetuwn 0;

	dwm_pwopewty_bwob_put(state->mode_bwob);
	state->mode_bwob = NUWW;

	if (mode) {
		stwuct dwm_pwopewty_bwob *bwob;

		dwm_mode_convewt_to_umode(&umode, mode);
		bwob = dwm_pwopewty_cweate_bwob(cwtc->dev,
						sizeof(umode), &umode);
		if (IS_EWW(bwob))
			wetuwn PTW_EWW(bwob);

		dwm_mode_copy(&state->mode, mode);

		state->mode_bwob = bwob;
		state->enabwe = twue;
		dwm_dbg_atomic(cwtc->dev,
			       "Set [MODE:%s] fow [CWTC:%d:%s] state %p\n",
			       mode->name, cwtc->base.id, cwtc->name, state);
	} ewse {
		memset(&state->mode, 0, sizeof(state->mode));
		state->enabwe = fawse;
		dwm_dbg_atomic(cwtc->dev,
			       "Set [NOMODE] fow [CWTC:%d:%s] state %p\n",
			       cwtc->base.id, cwtc->name, state);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_set_mode_fow_cwtc);

/**
 * dwm_atomic_set_mode_pwop_fow_cwtc - set mode fow CWTC
 * @state: the CWTC whose incoming state to update
 * @bwob: pointew to bwob pwopewty to use fow mode
 *
 * Set a mode (owiginating fwom a bwob pwopewty) on the desiwed CWTC state.
 * This function wiww take a wefewence on the bwob pwopewty fow the CWTC state,
 * and wewease the wefewence hewd on the state's existing mode pwopewty, if any
 * was set.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe. Cannot wetuwn -EDEADWK.
 */
int dwm_atomic_set_mode_pwop_fow_cwtc(stwuct dwm_cwtc_state *state,
				      stwuct dwm_pwopewty_bwob *bwob)
{
	stwuct dwm_cwtc *cwtc = state->cwtc;

	if (bwob == state->mode_bwob)
		wetuwn 0;

	dwm_pwopewty_bwob_put(state->mode_bwob);
	state->mode_bwob = NUWW;

	memset(&state->mode, 0, sizeof(state->mode));

	if (bwob) {
		int wet;

		if (bwob->wength != sizeof(stwuct dwm_mode_modeinfo)) {
			dwm_dbg_atomic(cwtc->dev,
				       "[CWTC:%d:%s] bad mode bwob wength: %zu\n",
				       cwtc->base.id, cwtc->name,
				       bwob->wength);
			wetuwn -EINVAW;
		}

		wet = dwm_mode_convewt_umode(cwtc->dev,
					     &state->mode, bwob->data);
		if (wet) {
			dwm_dbg_atomic(cwtc->dev,
				       "[CWTC:%d:%s] invawid mode (wet=%d, status=%s):\n",
				       cwtc->base.id, cwtc->name,
				       wet, dwm_get_mode_status_name(state->mode.status));
			dwm_mode_debug_pwintmodewine(&state->mode);
			wetuwn -EINVAW;
		}

		state->mode_bwob = dwm_pwopewty_bwob_get(bwob);
		state->enabwe = twue;
		dwm_dbg_atomic(cwtc->dev,
			       "Set [MODE:%s] fow [CWTC:%d:%s] state %p\n",
			       state->mode.name, cwtc->base.id, cwtc->name,
			       state);
	} ewse {
		state->enabwe = fawse;
		dwm_dbg_atomic(cwtc->dev,
			       "Set [NOMODE] fow [CWTC:%d:%s] state %p\n",
			       cwtc->base.id, cwtc->name, state);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_set_mode_pwop_fow_cwtc);

/**
 * dwm_atomic_set_cwtc_fow_pwane - set CWTC fow pwane
 * @pwane_state: the pwane whose incoming state to update
 * @cwtc: CWTC to use fow the pwane
 *
 * Changing the assigned CWTC fow a pwane wequiwes us to gwab the wock and state
 * fow the new CWTC, as needed. This function takes cawe of aww these detaiws
 * besides updating the pointew in the state object itsewf.
 *
 * Wetuwns:
 * 0 on success ow can faiw with -EDEADWK ow -ENOMEM. When the ewwow is EDEADWK
 * then the w/w mutex code has detected a deadwock and the entiwe atomic
 * sequence must be westawted. Aww othew ewwows awe fataw.
 */
int
dwm_atomic_set_cwtc_fow_pwane(stwuct dwm_pwane_state *pwane_state,
			      stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_pwane *pwane = pwane_state->pwane;
	stwuct dwm_cwtc_state *cwtc_state;
	/* Nothing to do fow same cwtc*/
	if (pwane_state->cwtc == cwtc)
		wetuwn 0;
	if (pwane_state->cwtc) {
		cwtc_state = dwm_atomic_get_cwtc_state(pwane_state->state,
						       pwane_state->cwtc);
		if (WAWN_ON(IS_EWW(cwtc_state)))
			wetuwn PTW_EWW(cwtc_state);

		cwtc_state->pwane_mask &= ~dwm_pwane_mask(pwane);
	}

	pwane_state->cwtc = cwtc;

	if (cwtc) {
		cwtc_state = dwm_atomic_get_cwtc_state(pwane_state->state,
						       cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);
		cwtc_state->pwane_mask |= dwm_pwane_mask(pwane);
	}

	if (cwtc)
		dwm_dbg_atomic(pwane->dev,
			       "Wink [PWANE:%d:%s] state %p to [CWTC:%d:%s]\n",
			       pwane->base.id, pwane->name, pwane_state,
			       cwtc->base.id, cwtc->name);
	ewse
		dwm_dbg_atomic(pwane->dev,
			       "Wink [PWANE:%d:%s] state %p to [NOCWTC]\n",
			       pwane->base.id, pwane->name, pwane_state);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_set_cwtc_fow_pwane);

/**
 * dwm_atomic_set_fb_fow_pwane - set fwamebuffew fow pwane
 * @pwane_state: atomic state object fow the pwane
 * @fb: fb to use fow the pwane
 *
 * Changing the assigned fwamebuffew fow a pwane wequiwes us to gwab a wefewence
 * to the new fb and dwop the wefewence to the owd fb, if thewe is one. This
 * function takes cawe of aww these detaiws besides updating the pointew in the
 * state object itsewf.
 */
void
dwm_atomic_set_fb_fow_pwane(stwuct dwm_pwane_state *pwane_state,
			    stwuct dwm_fwamebuffew *fb)
{
	stwuct dwm_pwane *pwane = pwane_state->pwane;

	if (fb)
		dwm_dbg_atomic(pwane->dev,
			       "Set [FB:%d] fow [PWANE:%d:%s] state %p\n",
			       fb->base.id, pwane->base.id, pwane->name,
			       pwane_state);
	ewse
		dwm_dbg_atomic(pwane->dev,
			       "Set [NOFB] fow [PWANE:%d:%s] state %p\n",
			       pwane->base.id, pwane->name, pwane_state);

	dwm_fwamebuffew_assign(&pwane_state->fb, fb);
}
EXPOWT_SYMBOW(dwm_atomic_set_fb_fow_pwane);

/**
 * dwm_atomic_set_cwtc_fow_connectow - set CWTC fow connectow
 * @conn_state: atomic state object fow the connectow
 * @cwtc: CWTC to use fow the connectow
 *
 * Changing the assigned CWTC fow a connectow wequiwes us to gwab the wock and
 * state fow the new CWTC, as needed. This function takes cawe of aww these
 * detaiws besides updating the pointew in the state object itsewf.
 *
 * Wetuwns:
 * 0 on success ow can faiw with -EDEADWK ow -ENOMEM. When the ewwow is EDEADWK
 * then the w/w mutex code has detected a deadwock and the entiwe atomic
 * sequence must be westawted. Aww othew ewwows awe fataw.
 */
int
dwm_atomic_set_cwtc_fow_connectow(stwuct dwm_connectow_state *conn_state,
				  stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_connectow *connectow = conn_state->connectow;
	stwuct dwm_cwtc_state *cwtc_state;

	if (conn_state->cwtc == cwtc)
		wetuwn 0;

	if (conn_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(conn_state->state,
							   conn_state->cwtc);

		cwtc_state->connectow_mask &=
			~dwm_connectow_mask(conn_state->connectow);

		dwm_connectow_put(conn_state->connectow);
		conn_state->cwtc = NUWW;
	}

	if (cwtc) {
		cwtc_state = dwm_atomic_get_cwtc_state(conn_state->state, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		cwtc_state->connectow_mask |=
			dwm_connectow_mask(conn_state->connectow);

		dwm_connectow_get(conn_state->connectow);
		conn_state->cwtc = cwtc;

		dwm_dbg_atomic(connectow->dev,
			       "Wink [CONNECTOW:%d:%s] state %p to [CWTC:%d:%s]\n",
			       connectow->base.id, connectow->name,
			       conn_state, cwtc->base.id, cwtc->name);
	} ewse {
		dwm_dbg_atomic(connectow->dev,
			       "Wink [CONNECTOW:%d:%s] state %p to [NOCWTC]\n",
			       connectow->base.id, connectow->name,
			       conn_state);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_set_cwtc_fow_connectow);

static void set_out_fence_fow_cwtc(stwuct dwm_atomic_state *state,
				   stwuct dwm_cwtc *cwtc, s32 __usew *fence_ptw)
{
	state->cwtcs[dwm_cwtc_index(cwtc)].out_fence_ptw = fence_ptw;
}

static s32 __usew *get_out_fence_fow_cwtc(stwuct dwm_atomic_state *state,
					  stwuct dwm_cwtc *cwtc)
{
	s32 __usew *fence_ptw;

	fence_ptw = state->cwtcs[dwm_cwtc_index(cwtc)].out_fence_ptw;
	state->cwtcs[dwm_cwtc_index(cwtc)].out_fence_ptw = NUWW;

	wetuwn fence_ptw;
}

static int set_out_fence_fow_connectow(stwuct dwm_atomic_state *state,
					stwuct dwm_connectow *connectow,
					s32 __usew *fence_ptw)
{
	unsigned int index = dwm_connectow_index(connectow);

	if (!fence_ptw)
		wetuwn 0;

	if (put_usew(-1, fence_ptw))
		wetuwn -EFAUWT;

	state->connectows[index].out_fence_ptw = fence_ptw;

	wetuwn 0;
}

static s32 __usew *get_out_fence_fow_connectow(stwuct dwm_atomic_state *state,
					       stwuct dwm_connectow *connectow)
{
	unsigned int index = dwm_connectow_index(connectow);
	s32 __usew *fence_ptw;

	fence_ptw = state->connectows[index].out_fence_ptw;
	state->connectows[index].out_fence_ptw = NUWW;

	wetuwn fence_ptw;
}

static int dwm_atomic_cwtc_set_pwopewty(stwuct dwm_cwtc *cwtc,
		stwuct dwm_cwtc_state *state, stwuct dwm_pwopewty *pwopewty,
		uint64_t vaw)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	boow wepwaced = fawse;
	int wet;

	if (pwopewty == config->pwop_active)
		state->active = vaw;
	ewse if (pwopewty == config->pwop_mode_id) {
		stwuct dwm_pwopewty_bwob *mode =
			dwm_pwopewty_wookup_bwob(dev, vaw);
		wet = dwm_atomic_set_mode_pwop_fow_cwtc(state, mode);
		dwm_pwopewty_bwob_put(mode);
		wetuwn wet;
	} ewse if (pwopewty == config->pwop_vww_enabwed) {
		state->vww_enabwed = vaw;
	} ewse if (pwopewty == config->degamma_wut_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(dev,
					&state->degamma_wut,
					vaw,
					-1, sizeof(stwuct dwm_cowow_wut),
					&wepwaced);
		state->cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == config->ctm_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(dev,
					&state->ctm,
					vaw,
					sizeof(stwuct dwm_cowow_ctm), -1,
					&wepwaced);
		state->cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == config->gamma_wut_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(dev,
					&state->gamma_wut,
					vaw,
					-1, sizeof(stwuct dwm_cowow_wut),
					&wepwaced);
		state->cowow_mgmt_changed |= wepwaced;
		wetuwn wet;
	} ewse if (pwopewty == config->pwop_out_fence_ptw) {
		s32 __usew *fence_ptw = u64_to_usew_ptw(vaw);

		if (!fence_ptw)
			wetuwn 0;

		if (put_usew(-1, fence_ptw))
			wetuwn -EFAUWT;

		set_out_fence_fow_cwtc(state->state, cwtc, fence_ptw);
	} ewse if (pwopewty == cwtc->scawing_fiwtew_pwopewty) {
		state->scawing_fiwtew = vaw;
	} ewse if (cwtc->funcs->atomic_set_pwopewty) {
		wetuwn cwtc->funcs->atomic_set_pwopewty(cwtc, state, pwopewty, vaw);
	} ewse {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       cwtc->base.id, cwtc->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
dwm_atomic_cwtc_get_pwopewty(stwuct dwm_cwtc *cwtc,
		const stwuct dwm_cwtc_state *state,
		stwuct dwm_pwopewty *pwopewty, uint64_t *vaw)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (pwopewty == config->pwop_active)
		*vaw = dwm_atomic_cwtc_effectivewy_active(state);
	ewse if (pwopewty == config->pwop_mode_id)
		*vaw = (state->mode_bwob) ? state->mode_bwob->base.id : 0;
	ewse if (pwopewty == config->pwop_vww_enabwed)
		*vaw = state->vww_enabwed;
	ewse if (pwopewty == config->degamma_wut_pwopewty)
		*vaw = (state->degamma_wut) ? state->degamma_wut->base.id : 0;
	ewse if (pwopewty == config->ctm_pwopewty)
		*vaw = (state->ctm) ? state->ctm->base.id : 0;
	ewse if (pwopewty == config->gamma_wut_pwopewty)
		*vaw = (state->gamma_wut) ? state->gamma_wut->base.id : 0;
	ewse if (pwopewty == config->pwop_out_fence_ptw)
		*vaw = 0;
	ewse if (pwopewty == cwtc->scawing_fiwtew_pwopewty)
		*vaw = state->scawing_fiwtew;
	ewse if (cwtc->funcs->atomic_get_pwopewty)
		wetuwn cwtc->funcs->atomic_get_pwopewty(cwtc, state, pwopewty, vaw);
	ewse {
		dwm_dbg_atomic(dev,
			       "[CWTC:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       cwtc->base.id, cwtc->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwm_atomic_pwane_set_pwopewty(stwuct dwm_pwane *pwane,
		stwuct dwm_pwane_state *state, stwuct dwm_fiwe *fiwe_pwiv,
		stwuct dwm_pwopewty *pwopewty, uint64_t vaw)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	boow wepwaced = fawse;
	int wet;

	if (pwopewty == config->pwop_fb_id) {
		stwuct dwm_fwamebuffew *fb;

		fb = dwm_fwamebuffew_wookup(dev, fiwe_pwiv, vaw);
		dwm_atomic_set_fb_fow_pwane(state, fb);
		if (fb)
			dwm_fwamebuffew_put(fb);
	} ewse if (pwopewty == config->pwop_in_fence_fd) {
		if (state->fence)
			wetuwn -EINVAW;

		if (U642I64(vaw) == -1)
			wetuwn 0;

		state->fence = sync_fiwe_get_fence(vaw);
		if (!state->fence)
			wetuwn -EINVAW;

	} ewse if (pwopewty == config->pwop_cwtc_id) {
		stwuct dwm_cwtc *cwtc = dwm_cwtc_find(dev, fiwe_pwiv, vaw);

		if (vaw && !cwtc) {
			dwm_dbg_atomic(dev,
				       "[PWOP:%d:%s] cannot find CWTC with ID %wwu\n",
				       pwopewty->base.id, pwopewty->name, vaw);
			wetuwn -EACCES;
		}
		wetuwn dwm_atomic_set_cwtc_fow_pwane(state, cwtc);
	} ewse if (pwopewty == config->pwop_cwtc_x) {
		state->cwtc_x = U642I64(vaw);
	} ewse if (pwopewty == config->pwop_cwtc_y) {
		state->cwtc_y = U642I64(vaw);
	} ewse if (pwopewty == config->pwop_cwtc_w) {
		state->cwtc_w = vaw;
	} ewse if (pwopewty == config->pwop_cwtc_h) {
		state->cwtc_h = vaw;
	} ewse if (pwopewty == config->pwop_swc_x) {
		state->swc_x = vaw;
	} ewse if (pwopewty == config->pwop_swc_y) {
		state->swc_y = vaw;
	} ewse if (pwopewty == config->pwop_swc_w) {
		state->swc_w = vaw;
	} ewse if (pwopewty == config->pwop_swc_h) {
		state->swc_h = vaw;
	} ewse if (pwopewty == pwane->awpha_pwopewty) {
		state->awpha = vaw;
	} ewse if (pwopewty == pwane->bwend_mode_pwopewty) {
		state->pixew_bwend_mode = vaw;
	} ewse if (pwopewty == pwane->wotation_pwopewty) {
		if (!is_powew_of_2(vaw & DWM_MODE_WOTATE_MASK)) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] bad wotation bitmask: 0x%wwx\n",
				       pwane->base.id, pwane->name, vaw);
			wetuwn -EINVAW;
		}
		state->wotation = vaw;
	} ewse if (pwopewty == pwane->zpos_pwopewty) {
		state->zpos = vaw;
	} ewse if (pwopewty == pwane->cowow_encoding_pwopewty) {
		state->cowow_encoding = vaw;
	} ewse if (pwopewty == pwane->cowow_wange_pwopewty) {
		state->cowow_wange = vaw;
	} ewse if (pwopewty == config->pwop_fb_damage_cwips) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(dev,
					&state->fb_damage_cwips,
					vaw,
					-1,
					sizeof(stwuct dwm_wect),
					&wepwaced);
		wetuwn wet;
	} ewse if (pwopewty == pwane->scawing_fiwtew_pwopewty) {
		state->scawing_fiwtew = vaw;
	} ewse if (pwane->funcs->atomic_set_pwopewty) {
		wetuwn pwane->funcs->atomic_set_pwopewty(pwane, state,
				pwopewty, vaw);
	} ewse if (pwopewty == pwane->hotspot_x_pwopewty) {
		if (pwane->type != DWM_PWANE_TYPE_CUWSOW) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] is not a cuwsow pwane: 0x%wwx\n",
				       pwane->base.id, pwane->name, vaw);
			wetuwn -EINVAW;
		}
		state->hotspot_x = vaw;
	} ewse if (pwopewty == pwane->hotspot_y_pwopewty) {
		if (pwane->type != DWM_PWANE_TYPE_CUWSOW) {
			dwm_dbg_atomic(pwane->dev,
				       "[PWANE:%d:%s] is not a cuwsow pwane: 0x%wwx\n",
				       pwane->base.id, pwane->name, vaw);
			wetuwn -EINVAW;
		}
		state->hotspot_y = vaw;
	} ewse {
		dwm_dbg_atomic(pwane->dev,
			       "[PWANE:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       pwane->base.id, pwane->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
dwm_atomic_pwane_get_pwopewty(stwuct dwm_pwane *pwane,
		const stwuct dwm_pwane_state *state,
		stwuct dwm_pwopewty *pwopewty, uint64_t *vaw)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (pwopewty == config->pwop_fb_id) {
		*vaw = (state->fb) ? state->fb->base.id : 0;
	} ewse if (pwopewty == config->pwop_in_fence_fd) {
		*vaw = -1;
	} ewse if (pwopewty == config->pwop_cwtc_id) {
		*vaw = (state->cwtc) ? state->cwtc->base.id : 0;
	} ewse if (pwopewty == config->pwop_cwtc_x) {
		*vaw = I642U64(state->cwtc_x);
	} ewse if (pwopewty == config->pwop_cwtc_y) {
		*vaw = I642U64(state->cwtc_y);
	} ewse if (pwopewty == config->pwop_cwtc_w) {
		*vaw = state->cwtc_w;
	} ewse if (pwopewty == config->pwop_cwtc_h) {
		*vaw = state->cwtc_h;
	} ewse if (pwopewty == config->pwop_swc_x) {
		*vaw = state->swc_x;
	} ewse if (pwopewty == config->pwop_swc_y) {
		*vaw = state->swc_y;
	} ewse if (pwopewty == config->pwop_swc_w) {
		*vaw = state->swc_w;
	} ewse if (pwopewty == config->pwop_swc_h) {
		*vaw = state->swc_h;
	} ewse if (pwopewty == pwane->awpha_pwopewty) {
		*vaw = state->awpha;
	} ewse if (pwopewty == pwane->bwend_mode_pwopewty) {
		*vaw = state->pixew_bwend_mode;
	} ewse if (pwopewty == pwane->wotation_pwopewty) {
		*vaw = state->wotation;
	} ewse if (pwopewty == pwane->zpos_pwopewty) {
		*vaw = state->zpos;
	} ewse if (pwopewty == pwane->cowow_encoding_pwopewty) {
		*vaw = state->cowow_encoding;
	} ewse if (pwopewty == pwane->cowow_wange_pwopewty) {
		*vaw = state->cowow_wange;
	} ewse if (pwopewty == config->pwop_fb_damage_cwips) {
		*vaw = (state->fb_damage_cwips) ?
			state->fb_damage_cwips->base.id : 0;
	} ewse if (pwopewty == pwane->scawing_fiwtew_pwopewty) {
		*vaw = state->scawing_fiwtew;
	} ewse if (pwane->funcs->atomic_get_pwopewty) {
		wetuwn pwane->funcs->atomic_get_pwopewty(pwane, state, pwopewty, vaw);
	} ewse if (pwopewty == pwane->hotspot_x_pwopewty) {
		*vaw = state->hotspot_x;
	} ewse if (pwopewty == pwane->hotspot_y_pwopewty) {
		*vaw = state->hotspot_y;
	} ewse {
		dwm_dbg_atomic(dev,
			       "[PWANE:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       pwane->base.id, pwane->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwm_atomic_set_wwiteback_fb_fow_connectow(
		stwuct dwm_connectow_state *conn_state,
		stwuct dwm_fwamebuffew *fb)
{
	int wet;
	stwuct dwm_connectow *conn = conn_state->connectow;

	wet = dwm_wwiteback_set_fb(conn_state, fb);
	if (wet < 0)
		wetuwn wet;

	if (fb)
		dwm_dbg_atomic(conn->dev,
			       "Set [FB:%d] fow connectow state %p\n",
			       fb->base.id, conn_state);
	ewse
		dwm_dbg_atomic(conn->dev,
			       "Set [NOFB] fow connectow state %p\n",
			       conn_state);

	wetuwn 0;
}

static int dwm_atomic_connectow_set_pwopewty(stwuct dwm_connectow *connectow,
		stwuct dwm_connectow_state *state, stwuct dwm_fiwe *fiwe_pwiv,
		stwuct dwm_pwopewty *pwopewty, uint64_t vaw)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	boow wepwaced = fawse;
	int wet;

	if (pwopewty == config->pwop_cwtc_id) {
		stwuct dwm_cwtc *cwtc = dwm_cwtc_find(dev, fiwe_pwiv, vaw);

		if (vaw && !cwtc) {
			dwm_dbg_atomic(dev,
				       "[PWOP:%d:%s] cannot find CWTC with ID %wwu\n",
				       pwopewty->base.id, pwopewty->name, vaw);
			wetuwn -EACCES;
		}
		wetuwn dwm_atomic_set_cwtc_fow_connectow(state, cwtc);
	} ewse if (pwopewty == config->dpms_pwopewty) {
		/* setting DPMS pwopewty wequiwes speciaw handwing, which
		 * is done in wegacy setpwop path fow us.  Disawwow (fow
		 * now?) atomic wwites to DPMS pwopewty:
		 */
		dwm_dbg_atomic(dev,
			       "wegacy [PWOP:%d:%s] can onwy be set via wegacy uAPI\n",
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	} ewse if (pwopewty == config->tv_sewect_subconnectow_pwopewty) {
		state->tv.sewect_subconnectow = vaw;
	} ewse if (pwopewty == config->tv_subconnectow_pwopewty) {
		state->tv.subconnectow = vaw;
	} ewse if (pwopewty == config->tv_weft_mawgin_pwopewty) {
		state->tv.mawgins.weft = vaw;
	} ewse if (pwopewty == config->tv_wight_mawgin_pwopewty) {
		state->tv.mawgins.wight = vaw;
	} ewse if (pwopewty == config->tv_top_mawgin_pwopewty) {
		state->tv.mawgins.top = vaw;
	} ewse if (pwopewty == config->tv_bottom_mawgin_pwopewty) {
		state->tv.mawgins.bottom = vaw;
	} ewse if (pwopewty == config->wegacy_tv_mode_pwopewty) {
		state->tv.wegacy_mode = vaw;
	} ewse if (pwopewty == config->tv_mode_pwopewty) {
		state->tv.mode = vaw;
	} ewse if (pwopewty == config->tv_bwightness_pwopewty) {
		state->tv.bwightness = vaw;
	} ewse if (pwopewty == config->tv_contwast_pwopewty) {
		state->tv.contwast = vaw;
	} ewse if (pwopewty == config->tv_fwickew_weduction_pwopewty) {
		state->tv.fwickew_weduction = vaw;
	} ewse if (pwopewty == config->tv_ovewscan_pwopewty) {
		state->tv.ovewscan = vaw;
	} ewse if (pwopewty == config->tv_satuwation_pwopewty) {
		state->tv.satuwation = vaw;
	} ewse if (pwopewty == config->tv_hue_pwopewty) {
		state->tv.hue = vaw;
	} ewse if (pwopewty == config->wink_status_pwopewty) {
		/* Nevew downgwade fwom GOOD to BAD on usewspace's wequest hewe,
		 * onwy hw issues can do that.
		 *
		 * Fow an atomic pwopewty the usewspace doesn't need to be abwe
		 * to undewstand aww the pwopewties, but needs to be abwe to
		 * westowe the state it wants on VT switch. So if the usewspace
		 * twies to change the wink_status fwom GOOD to BAD, dwivew
		 * siwentwy wejects it and wetuwns a 0. This pwevents usewspace
		 * fwom accidentawwy bweaking  the dispway when it westowes the
		 * state.
		 */
		if (state->wink_status != DWM_WINK_STATUS_GOOD)
			state->wink_status = vaw;
	} ewse if (pwopewty == config->hdw_output_metadata_pwopewty) {
		wet = dwm_pwopewty_wepwace_bwob_fwom_id(dev,
				&state->hdw_output_metadata,
				vaw,
				sizeof(stwuct hdw_output_metadata), -1,
				&wepwaced);
		wetuwn wet;
	} ewse if (pwopewty == config->aspect_watio_pwopewty) {
		state->pictuwe_aspect_watio = vaw;
	} ewse if (pwopewty == config->content_type_pwopewty) {
		state->content_type = vaw;
	} ewse if (pwopewty == connectow->scawing_mode_pwopewty) {
		state->scawing_mode = vaw;
	} ewse if (pwopewty == config->content_pwotection_pwopewty) {
		if (vaw == DWM_MODE_CONTENT_PWOTECTION_ENABWED) {
			dwm_dbg_kms(dev, "onwy dwivews can set CP Enabwed\n");
			wetuwn -EINVAW;
		}
		state->content_pwotection = vaw;
	} ewse if (pwopewty == config->hdcp_content_type_pwopewty) {
		state->hdcp_content_type = vaw;
	} ewse if (pwopewty == connectow->cowowspace_pwopewty) {
		state->cowowspace = vaw;
	} ewse if (pwopewty == config->wwiteback_fb_id_pwopewty) {
		stwuct dwm_fwamebuffew *fb;
		int wet;

		fb = dwm_fwamebuffew_wookup(dev, fiwe_pwiv, vaw);
		wet = dwm_atomic_set_wwiteback_fb_fow_connectow(state, fb);
		if (fb)
			dwm_fwamebuffew_put(fb);
		wetuwn wet;
	} ewse if (pwopewty == config->wwiteback_out_fence_ptw_pwopewty) {
		s32 __usew *fence_ptw = u64_to_usew_ptw(vaw);

		wetuwn set_out_fence_fow_connectow(state->state, connectow,
						   fence_ptw);
	} ewse if (pwopewty == connectow->max_bpc_pwopewty) {
		state->max_wequested_bpc = vaw;
	} ewse if (pwopewty == connectow->pwivacy_scween_sw_state_pwopewty) {
		state->pwivacy_scween_sw_state = vaw;
	} ewse if (connectow->funcs->atomic_set_pwopewty) {
		wetuwn connectow->funcs->atomic_set_pwopewty(connectow,
				state, pwopewty, vaw);
	} ewse {
		dwm_dbg_atomic(connectow->dev,
			       "[CONNECTOW:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       connectow->base.id, connectow->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
dwm_atomic_connectow_get_pwopewty(stwuct dwm_connectow *connectow,
		const stwuct dwm_connectow_state *state,
		stwuct dwm_pwopewty *pwopewty, uint64_t *vaw)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (pwopewty == config->pwop_cwtc_id) {
		*vaw = (state->cwtc) ? state->cwtc->base.id : 0;
	} ewse if (pwopewty == config->dpms_pwopewty) {
		if (state->cwtc && state->cwtc->state->sewf_wefwesh_active)
			*vaw = DWM_MODE_DPMS_ON;
		ewse
			*vaw = connectow->dpms;
	} ewse if (pwopewty == config->tv_sewect_subconnectow_pwopewty) {
		*vaw = state->tv.sewect_subconnectow;
	} ewse if (pwopewty == config->tv_subconnectow_pwopewty) {
		*vaw = state->tv.subconnectow;
	} ewse if (pwopewty == config->tv_weft_mawgin_pwopewty) {
		*vaw = state->tv.mawgins.weft;
	} ewse if (pwopewty == config->tv_wight_mawgin_pwopewty) {
		*vaw = state->tv.mawgins.wight;
	} ewse if (pwopewty == config->tv_top_mawgin_pwopewty) {
		*vaw = state->tv.mawgins.top;
	} ewse if (pwopewty == config->tv_bottom_mawgin_pwopewty) {
		*vaw = state->tv.mawgins.bottom;
	} ewse if (pwopewty == config->wegacy_tv_mode_pwopewty) {
		*vaw = state->tv.wegacy_mode;
	} ewse if (pwopewty == config->tv_mode_pwopewty) {
		*vaw = state->tv.mode;
	} ewse if (pwopewty == config->tv_bwightness_pwopewty) {
		*vaw = state->tv.bwightness;
	} ewse if (pwopewty == config->tv_contwast_pwopewty) {
		*vaw = state->tv.contwast;
	} ewse if (pwopewty == config->tv_fwickew_weduction_pwopewty) {
		*vaw = state->tv.fwickew_weduction;
	} ewse if (pwopewty == config->tv_ovewscan_pwopewty) {
		*vaw = state->tv.ovewscan;
	} ewse if (pwopewty == config->tv_satuwation_pwopewty) {
		*vaw = state->tv.satuwation;
	} ewse if (pwopewty == config->tv_hue_pwopewty) {
		*vaw = state->tv.hue;
	} ewse if (pwopewty == config->wink_status_pwopewty) {
		*vaw = state->wink_status;
	} ewse if (pwopewty == config->aspect_watio_pwopewty) {
		*vaw = state->pictuwe_aspect_watio;
	} ewse if (pwopewty == config->content_type_pwopewty) {
		*vaw = state->content_type;
	} ewse if (pwopewty == connectow->cowowspace_pwopewty) {
		*vaw = state->cowowspace;
	} ewse if (pwopewty == connectow->scawing_mode_pwopewty) {
		*vaw = state->scawing_mode;
	} ewse if (pwopewty == config->hdw_output_metadata_pwopewty) {
		*vaw = state->hdw_output_metadata ?
			state->hdw_output_metadata->base.id : 0;
	} ewse if (pwopewty == config->content_pwotection_pwopewty) {
		*vaw = state->content_pwotection;
	} ewse if (pwopewty == config->hdcp_content_type_pwopewty) {
		*vaw = state->hdcp_content_type;
	} ewse if (pwopewty == config->wwiteback_fb_id_pwopewty) {
		/* Wwiteback fwamebuffew is one-shot, wwite and fowget */
		*vaw = 0;
	} ewse if (pwopewty == config->wwiteback_out_fence_ptw_pwopewty) {
		*vaw = 0;
	} ewse if (pwopewty == connectow->max_bpc_pwopewty) {
		*vaw = state->max_wequested_bpc;
	} ewse if (pwopewty == connectow->pwivacy_scween_sw_state_pwopewty) {
		*vaw = state->pwivacy_scween_sw_state;
	} ewse if (connectow->funcs->atomic_get_pwopewty) {
		wetuwn connectow->funcs->atomic_get_pwopewty(connectow,
				state, pwopewty, vaw);
	} ewse {
		dwm_dbg_atomic(dev,
			       "[CONNECTOW:%d:%s] unknown pwopewty [PWOP:%d:%s]\n",
			       connectow->base.id, connectow->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dwm_atomic_get_pwopewty(stwuct dwm_mode_object *obj,
		stwuct dwm_pwopewty *pwopewty, uint64_t *vaw)
{
	stwuct dwm_device *dev = pwopewty->dev;
	int wet;

	switch (obj->type) {
	case DWM_MODE_OBJECT_CONNECTOW: {
		stwuct dwm_connectow *connectow = obj_to_connectow(obj);

		WAWN_ON(!dwm_modeset_is_wocked(&dev->mode_config.connection_mutex));
		wet = dwm_atomic_connectow_get_pwopewty(connectow,
				connectow->state, pwopewty, vaw);
		bweak;
	}
	case DWM_MODE_OBJECT_CWTC: {
		stwuct dwm_cwtc *cwtc = obj_to_cwtc(obj);

		WAWN_ON(!dwm_modeset_is_wocked(&cwtc->mutex));
		wet = dwm_atomic_cwtc_get_pwopewty(cwtc,
				cwtc->state, pwopewty, vaw);
		bweak;
	}
	case DWM_MODE_OBJECT_PWANE: {
		stwuct dwm_pwane *pwane = obj_to_pwane(obj);

		WAWN_ON(!dwm_modeset_is_wocked(&pwane->mutex));
		wet = dwm_atomic_pwane_get_pwopewty(pwane,
				pwane->state, pwopewty, vaw);
		bweak;
	}
	defauwt:
		dwm_dbg_atomic(dev, "[OBJECT:%d] has no pwopewties\n", obj->id);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

/*
 * The big monstew ioctw
 */

static stwuct dwm_pending_vbwank_event *cweate_vbwank_event(
		stwuct dwm_cwtc *cwtc, uint64_t usew_data)
{
	stwuct dwm_pending_vbwank_event *e = NUWW;

	e = kzawwoc(sizeof *e, GFP_KEWNEW);
	if (!e)
		wetuwn NUWW;

	e->event.base.type = DWM_EVENT_FWIP_COMPWETE;
	e->event.base.wength = sizeof(e->event);
	e->event.vbw.cwtc_id = cwtc->base.id;
	e->event.vbw.usew_data = usew_data;

	wetuwn e;
}

int dwm_atomic_connectow_commit_dpms(stwuct dwm_atomic_state *state,
				     stwuct dwm_connectow *connectow,
				     int mode)
{
	stwuct dwm_connectow *tmp_connectow;
	stwuct dwm_connectow_state *new_conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int i, wet, owd_mode = connectow->dpms;
	boow active = fawse;

	wet = dwm_modeset_wock(&state->dev->mode_config.connection_mutex,
			       state->acquiwe_ctx);
	if (wet)
		wetuwn wet;

	if (mode != DWM_MODE_DPMS_ON)
		mode = DWM_MODE_DPMS_OFF;
	connectow->dpms = mode;

	cwtc = connectow->state->cwtc;
	if (!cwtc)
		goto out;
	wet = dwm_atomic_add_affected_connectows(state, cwtc);
	if (wet)
		goto out;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto out;
	}

	fow_each_new_connectow_in_state(state, tmp_connectow, new_conn_state, i) {
		if (new_conn_state->cwtc != cwtc)
			continue;
		if (tmp_connectow->dpms == DWM_MODE_DPMS_ON) {
			active = twue;
			bweak;
		}
	}

	cwtc_state->active = active;
	wet = dwm_atomic_commit(state);
out:
	if (wet != 0)
		connectow->dpms = owd_mode;
	wetuwn wet;
}

static int dwm_atomic_check_pwop_changes(int wet, uint64_t owd_vaw, uint64_t pwop_vawue,
					 stwuct dwm_pwopewty *pwop)
{
	if (wet != 0 || owd_vaw != pwop_vawue) {
		dwm_dbg_atomic(pwop->dev,
			       "[PWOP:%d:%s] No pwop can be changed duwing async fwip\n",
			       pwop->base.id, pwop->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dwm_atomic_set_pwopewty(stwuct dwm_atomic_state *state,
			    stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_mode_object *obj,
			    stwuct dwm_pwopewty *pwop,
			    u64 pwop_vawue,
			    boow async_fwip)
{
	stwuct dwm_mode_object *wef;
	u64 owd_vaw;
	int wet;

	if (!dwm_pwopewty_change_vawid_get(pwop, pwop_vawue, &wef))
		wetuwn -EINVAW;

	switch (obj->type) {
	case DWM_MODE_OBJECT_CONNECTOW: {
		stwuct dwm_connectow *connectow = obj_to_connectow(obj);
		stwuct dwm_connectow_state *connectow_state;

		connectow_state = dwm_atomic_get_connectow_state(state, connectow);
		if (IS_EWW(connectow_state)) {
			wet = PTW_EWW(connectow_state);
			bweak;
		}

		if (async_fwip) {
			wet = dwm_atomic_connectow_get_pwopewty(connectow, connectow_state,
								pwop, &owd_vaw);
			wet = dwm_atomic_check_pwop_changes(wet, owd_vaw, pwop_vawue, pwop);
			bweak;
		}

		wet = dwm_atomic_connectow_set_pwopewty(connectow,
				connectow_state, fiwe_pwiv,
				pwop, pwop_vawue);
		bweak;
	}
	case DWM_MODE_OBJECT_CWTC: {
		stwuct dwm_cwtc *cwtc = obj_to_cwtc(obj);
		stwuct dwm_cwtc_state *cwtc_state;

		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state)) {
			wet = PTW_EWW(cwtc_state);
			bweak;
		}

		if (async_fwip) {
			wet = dwm_atomic_cwtc_get_pwopewty(cwtc, cwtc_state,
							   pwop, &owd_vaw);
			wet = dwm_atomic_check_pwop_changes(wet, owd_vaw, pwop_vawue, pwop);
			bweak;
		}

		wet = dwm_atomic_cwtc_set_pwopewty(cwtc,
				cwtc_state, pwop, pwop_vawue);
		bweak;
	}
	case DWM_MODE_OBJECT_PWANE: {
		stwuct dwm_pwane *pwane = obj_to_pwane(obj);
		stwuct dwm_pwane_state *pwane_state;
		stwuct dwm_mode_config *config = &pwane->dev->mode_config;

		pwane_state = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state)) {
			wet = PTW_EWW(pwane_state);
			bweak;
		}

		if (async_fwip && pwop != config->pwop_fb_id) {
			wet = dwm_atomic_pwane_get_pwopewty(pwane, pwane_state,
							    pwop, &owd_vaw);
			wet = dwm_atomic_check_pwop_changes(wet, owd_vaw, pwop_vawue, pwop);
			bweak;
		}

		if (async_fwip && pwane_state->pwane->type != DWM_PWANE_TYPE_PWIMAWY) {
			dwm_dbg_atomic(pwop->dev,
				       "[OBJECT:%d] Onwy pwimawy pwanes can be changed duwing async fwip\n",
				       obj->id);
			wet = -EINVAW;
			bweak;
		}

		wet = dwm_atomic_pwane_set_pwopewty(pwane,
				pwane_state, fiwe_pwiv,
				pwop, pwop_vawue);
		bweak;
	}
	defauwt:
		dwm_dbg_atomic(pwop->dev, "[OBJECT:%d] has no pwopewties\n", obj->id);
		wet = -EINVAW;
		bweak;
	}

	dwm_pwopewty_change_vawid_put(pwop, wef);
	wetuwn wet;
}

/**
 * DOC: expwicit fencing pwopewties
 *
 * Expwicit fencing awwows usewspace to contwow the buffew synchwonization
 * between devices. A Fence ow a gwoup of fences awe twansfewwed to/fwom
 * usewspace using Sync Fiwe fds and thewe awe two DWM pwopewties fow that.
 * IN_FENCE_FD on each DWM Pwane to send fences to the kewnew and
 * OUT_FENCE_PTW on each DWM CWTC to weceive fences fwom the kewnew.
 *
 * As a contwast, with impwicit fencing the kewnew keeps twack of any
 * ongoing wendewing, and automaticawwy ensuwes that the atomic update waits
 * fow any pending wendewing to compwete. This is usuawwy twacked in &stwuct
 * dma_wesv which can awso contain mandatowy kewnew fences. Impwicit syncing
 * is how Winux twaditionawwy wowked (e.g. DWI2/3 on X.owg), wheweas expwicit
 * fencing is what Andwoid wants.
 *
 * "IN_FENCE_FD”:
 *	Use this pwopewty to pass a fence that DWM shouwd wait on befowe
 *	pwoceeding with the Atomic Commit wequest and show the fwamebuffew fow
 *	the pwane on the scween. The fence can be eithew a nowmaw fence ow a
 *	mewged one, the sync_fiwe fwamewowk wiww handwe both cases and use a
 *	fence_awway if a mewged fence is weceived. Passing -1 hewe means no
 *	fences to wait on.
 *
 *	If the Atomic Commit wequest has the DWM_MODE_ATOMIC_TEST_ONWY fwag
 *	it wiww onwy check if the Sync Fiwe is a vawid one.
 *
 *	On the dwivew side the fence is stowed on the @fence pawametew of
 *	&stwuct dwm_pwane_state. Dwivews which awso suppowt impwicit fencing
 *	shouwd extwact the impwicit fence using dwm_gem_pwane_hewpew_pwepawe_fb(),
 *	to make suwe thewe's consistent behaviouw between dwivews in pwecedence
 *	of impwicit vs. expwicit fencing.
 *
 * "OUT_FENCE_PTW”:
 *	Use this pwopewty to pass a fiwe descwiptow pointew to DWM. Once the
 *	Atomic Commit wequest caww wetuwns OUT_FENCE_PTW wiww be fiwwed with
 *	the fiwe descwiptow numbew of a Sync Fiwe. This Sync Fiwe contains the
 *	CWTC fence that wiww be signawed when aww fwamebuffews pwesent on the
 *	Atomic Commit * wequest fow that given CWTC awe scanned out on the
 *	scween.
 *
 *	The Atomic Commit wequest faiws if a invawid pointew is passed. If the
 *	Atomic Commit wequest faiws fow any othew weason the out fence fd
 *	wetuwned wiww be -1. On a Atomic Commit with the
 *	DWM_MODE_ATOMIC_TEST_ONWY fwag the out fence wiww awso be set to -1.
 *
 *	Note that out-fences don't have a speciaw intewface to dwivews and awe
 *	intewnawwy wepwesented by a &stwuct dwm_pending_vbwank_event in stwuct
 *	&dwm_cwtc_state, which is awso used by the nonbwocking atomic commit
 *	hewpews and fow the DWM event handwing fow existing usewspace.
 */

stwuct dwm_out_fence_state {
	s32 __usew *out_fence_ptw;
	stwuct sync_fiwe *sync_fiwe;
	int fd;
};

static int setup_out_fence(stwuct dwm_out_fence_state *fence_state,
			   stwuct dma_fence *fence)
{
	fence_state->fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fence_state->fd < 0)
		wetuwn fence_state->fd;

	if (put_usew(fence_state->fd, fence_state->out_fence_ptw))
		wetuwn -EFAUWT;

	fence_state->sync_fiwe = sync_fiwe_cweate(fence);
	if (!fence_state->sync_fiwe)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int pwepawe_signawing(stwuct dwm_device *dev,
				  stwuct dwm_atomic_state *state,
				  stwuct dwm_mode_atomic *awg,
				  stwuct dwm_fiwe *fiwe_pwiv,
				  stwuct dwm_out_fence_state **fence_state,
				  unsigned int *num_fences)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *conn_state;
	int i, c = 0, wet;

	if (awg->fwags & DWM_MODE_ATOMIC_TEST_ONWY)
		wetuwn 0;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		s32 __usew *fence_ptw;

		fence_ptw = get_out_fence_fow_cwtc(cwtc_state->state, cwtc);

		if (awg->fwags & DWM_MODE_PAGE_FWIP_EVENT || fence_ptw) {
			stwuct dwm_pending_vbwank_event *e;

			e = cweate_vbwank_event(cwtc, awg->usew_data);
			if (!e)
				wetuwn -ENOMEM;

			cwtc_state->event = e;
		}

		if (awg->fwags & DWM_MODE_PAGE_FWIP_EVENT) {
			stwuct dwm_pending_vbwank_event *e = cwtc_state->event;

			if (!fiwe_pwiv)
				continue;

			wet = dwm_event_wesewve_init(dev, fiwe_pwiv, &e->base,
						     &e->event.base);
			if (wet) {
				kfwee(e);
				cwtc_state->event = NUWW;
				wetuwn wet;
			}
		}

		if (fence_ptw) {
			stwuct dma_fence *fence;
			stwuct dwm_out_fence_state *f;

			f = kweawwoc(*fence_state, sizeof(**fence_state) *
				     (*num_fences + 1), GFP_KEWNEW);
			if (!f)
				wetuwn -ENOMEM;

			memset(&f[*num_fences], 0, sizeof(*f));

			f[*num_fences].out_fence_ptw = fence_ptw;
			*fence_state = f;

			fence = dwm_cwtc_cweate_fence(cwtc);
			if (!fence)
				wetuwn -ENOMEM;

			wet = setup_out_fence(&f[(*num_fences)++], fence);
			if (wet) {
				dma_fence_put(fence);
				wetuwn wet;
			}

			cwtc_state->event->base.fence = fence;
		}

		c++;
	}

	fow_each_new_connectow_in_state(state, conn, conn_state, i) {
		stwuct dwm_wwiteback_connectow *wb_conn;
		stwuct dwm_out_fence_state *f;
		stwuct dma_fence *fence;
		s32 __usew *fence_ptw;

		if (!conn_state->wwiteback_job)
			continue;

		fence_ptw = get_out_fence_fow_connectow(state, conn);
		if (!fence_ptw)
			continue;

		f = kweawwoc(*fence_state, sizeof(**fence_state) *
			     (*num_fences + 1), GFP_KEWNEW);
		if (!f)
			wetuwn -ENOMEM;

		memset(&f[*num_fences], 0, sizeof(*f));

		f[*num_fences].out_fence_ptw = fence_ptw;
		*fence_state = f;

		wb_conn = dwm_connectow_to_wwiteback(conn);
		fence = dwm_wwiteback_get_out_fence(wb_conn);
		if (!fence)
			wetuwn -ENOMEM;

		wet = setup_out_fence(&f[(*num_fences)++], fence);
		if (wet) {
			dma_fence_put(fence);
			wetuwn wet;
		}

		conn_state->wwiteback_job->out_fence = fence;
	}

	/*
	 * Having this fwag means usew mode pends on event which wiww nevew
	 * weach due to wack of at weast one CWTC fow signawing
	 */
	if (c == 0 && (awg->fwags & DWM_MODE_PAGE_FWIP_EVENT)) {
		dwm_dbg_atomic(dev, "need at weast one CWTC fow DWM_MODE_PAGE_FWIP_EVENT");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void compwete_signawing(stwuct dwm_device *dev,
			       stwuct dwm_atomic_state *state,
			       stwuct dwm_out_fence_state *fence_state,
			       unsigned int num_fences,
			       boow instaww_fds)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int i;

	if (instaww_fds) {
		fow (i = 0; i < num_fences; i++)
			fd_instaww(fence_state[i].fd,
				   fence_state[i].sync_fiwe->fiwe);

		kfwee(fence_state);
		wetuwn;
	}

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		stwuct dwm_pending_vbwank_event *event = cwtc_state->event;
		/*
		 * Fwee the awwocated event. dwm_atomic_hewpew_setup_commit
		 * can awwocate an event too, so onwy fwee it if it's ouws
		 * to pwevent a doubwe fwee in dwm_atomic_state_cweaw.
		 */
		if (event && (event->base.fence || event->base.fiwe_pwiv)) {
			dwm_event_cancew_fwee(dev, &event->base);
			cwtc_state->event = NUWW;
		}
	}

	if (!fence_state)
		wetuwn;

	fow (i = 0; i < num_fences; i++) {
		if (fence_state[i].sync_fiwe)
			fput(fence_state[i].sync_fiwe->fiwe);
		if (fence_state[i].fd >= 0)
			put_unused_fd(fence_state[i].fd);

		/* If this faiws wog ewwow to the usew */
		if (fence_state[i].out_fence_ptw &&
		    put_usew(-1, fence_state[i].out_fence_ptw))
			dwm_dbg_atomic(dev, "Couwdn't cweaw out_fence_ptw\n");
	}

	kfwee(fence_state);
}

static void
set_async_fwip(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int i;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		cwtc_state->async_fwip = twue;
	}
}

int dwm_mode_atomic_ioctw(stwuct dwm_device *dev,
			  void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_atomic *awg = data;
	uint32_t __usew *objs_ptw = (uint32_t __usew *)(unsigned wong)(awg->objs_ptw);
	uint32_t __usew *count_pwops_ptw = (uint32_t __usew *)(unsigned wong)(awg->count_pwops_ptw);
	uint32_t __usew *pwops_ptw = (uint32_t __usew *)(unsigned wong)(awg->pwops_ptw);
	uint64_t __usew *pwop_vawues_ptw = (uint64_t __usew *)(unsigned wong)(awg->pwop_vawues_ptw);
	unsigned int copied_objs, copied_pwops;
	stwuct dwm_atomic_state *state;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_out_fence_state *fence_state;
	int wet = 0;
	unsigned int i, j, num_fences;
	boow async_fwip = fawse;

	/* disawwow fow dwivews not suppowting atomic: */
	if (!dwm_cowe_check_featuwe(dev, DWIVEW_ATOMIC))
		wetuwn -EOPNOTSUPP;

	/* disawwow fow usewspace that has not enabwed atomic cap (even
	 * though this may be a bit ovewkiww, since wegacy usewspace
	 * wouwdn't know how to caww this ioctw)
	 */
	if (!fiwe_pwiv->atomic) {
		dwm_dbg_atomic(dev,
			       "commit faiwed: atomic cap not enabwed\n");
		wetuwn -EINVAW;
	}

	if (awg->fwags & ~DWM_MODE_ATOMIC_FWAGS) {
		dwm_dbg_atomic(dev, "commit faiwed: invawid fwag\n");
		wetuwn -EINVAW;
	}

	if (awg->wesewved) {
		dwm_dbg_atomic(dev, "commit faiwed: wesewved fiewd set\n");
		wetuwn -EINVAW;
	}

	if (awg->fwags & DWM_MODE_PAGE_FWIP_ASYNC) {
		if (!dev->mode_config.async_page_fwip) {
			dwm_dbg_atomic(dev,
				       "commit faiwed: DWM_MODE_PAGE_FWIP_ASYNC not suppowted\n");
			wetuwn -EINVAW;
		}

		async_fwip = twue;
	}

	/* can't test and expect an event at the same time. */
	if ((awg->fwags & DWM_MODE_ATOMIC_TEST_ONWY) &&
			(awg->fwags & DWM_MODE_PAGE_FWIP_EVENT)) {
		dwm_dbg_atomic(dev,
			       "commit faiwed: page-fwip event wequested with test-onwy commit\n");
		wetuwn -EINVAW;
	}

	state = dwm_atomic_state_awwoc(dev);
	if (!state)
		wetuwn -ENOMEM;

	dwm_modeset_acquiwe_init(&ctx, DWM_MODESET_ACQUIWE_INTEWWUPTIBWE);
	state->acquiwe_ctx = &ctx;
	state->awwow_modeset = !!(awg->fwags & DWM_MODE_ATOMIC_AWWOW_MODESET);

wetwy:
	copied_objs = 0;
	copied_pwops = 0;
	fence_state = NUWW;
	num_fences = 0;

	fow (i = 0; i < awg->count_objs; i++) {
		uint32_t obj_id, count_pwops;
		stwuct dwm_mode_object *obj;

		if (get_usew(obj_id, objs_ptw + copied_objs)) {
			wet = -EFAUWT;
			goto out;
		}

		obj = dwm_mode_object_find(dev, fiwe_pwiv, obj_id, DWM_MODE_OBJECT_ANY);
		if (!obj) {
			dwm_dbg_atomic(dev, "cannot find object ID %d", obj_id);
			wet = -ENOENT;
			goto out;
		}

		if (!obj->pwopewties) {
			dwm_dbg_atomic(dev, "[OBJECT:%d] has no pwopewties", obj_id);
			dwm_mode_object_put(obj);
			wet = -ENOENT;
			goto out;
		}

		if (get_usew(count_pwops, count_pwops_ptw + copied_objs)) {
			dwm_mode_object_put(obj);
			wet = -EFAUWT;
			goto out;
		}

		copied_objs++;

		fow (j = 0; j < count_pwops; j++) {
			uint32_t pwop_id;
			uint64_t pwop_vawue;
			stwuct dwm_pwopewty *pwop;

			if (get_usew(pwop_id, pwops_ptw + copied_pwops)) {
				dwm_mode_object_put(obj);
				wet = -EFAUWT;
				goto out;
			}

			pwop = dwm_mode_obj_find_pwop_id(obj, pwop_id);
			if (!pwop) {
				dwm_dbg_atomic(dev,
					       "[OBJECT:%d] cannot find pwopewty ID %d",
					       obj_id, pwop_id);
				dwm_mode_object_put(obj);
				wet = -ENOENT;
				goto out;
			}

			if (copy_fwom_usew(&pwop_vawue,
					   pwop_vawues_ptw + copied_pwops,
					   sizeof(pwop_vawue))) {
				dwm_mode_object_put(obj);
				wet = -EFAUWT;
				goto out;
			}

			wet = dwm_atomic_set_pwopewty(state, fiwe_pwiv, obj,
						      pwop, pwop_vawue, async_fwip);
			if (wet) {
				dwm_mode_object_put(obj);
				goto out;
			}

			copied_pwops++;
		}

		dwm_mode_object_put(obj);
	}

	wet = pwepawe_signawing(dev, state, awg, fiwe_pwiv, &fence_state,
				&num_fences);
	if (wet)
		goto out;

	if (awg->fwags & DWM_MODE_PAGE_FWIP_ASYNC)
		set_async_fwip(state);

	if (awg->fwags & DWM_MODE_ATOMIC_TEST_ONWY) {
		wet = dwm_atomic_check_onwy(state);
	} ewse if (awg->fwags & DWM_MODE_ATOMIC_NONBWOCK) {
		wet = dwm_atomic_nonbwocking_commit(state);
	} ewse {
		wet = dwm_atomic_commit(state);
	}

out:
	compwete_signawing(dev, state, fence_state, num_fences, !wet);

	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		wet = dwm_modeset_backoff(&ctx);
		if (!wet)
			goto wetwy;
	}

	dwm_atomic_state_put(state);

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;
}
