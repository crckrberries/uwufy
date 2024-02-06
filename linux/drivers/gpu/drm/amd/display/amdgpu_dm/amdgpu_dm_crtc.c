// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_atomic_hewpew.h>

#incwude "dc.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dm_psw.h"
#incwude "amdgpu_dm_cwtc.h"
#incwude "amdgpu_dm_pwane.h"
#incwude "amdgpu_dm_twace.h"
#incwude "amdgpu_dm_debugfs.h"

void amdgpu_dm_cwtc_handwe_vbwank(stwuct amdgpu_cwtc *acwtc)
{
	stwuct dwm_cwtc *cwtc = &acwtc->base;
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	dwm_cwtc_handwe_vbwank(cwtc);

	spin_wock_iwqsave(&dev->event_wock, fwags);

	/* Send compwetion event fow cuwsow-onwy commits */
	if (acwtc->event && acwtc->pfwip_status != AMDGPU_FWIP_SUBMITTED) {
		dwm_cwtc_send_vbwank_event(cwtc, acwtc->event);
		dwm_cwtc_vbwank_put(cwtc);
		acwtc->event = NUWW;
	}

	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

boow amdgpu_dm_cwtc_modeset_wequiwed(stwuct dwm_cwtc_state *cwtc_state,
			     stwuct dc_stweam_state *new_stweam,
			     stwuct dc_stweam_state *owd_stweam)
{
	wetuwn cwtc_state->active && dwm_atomic_cwtc_needs_modeset(cwtc_state);
}

boow amdgpu_dm_cwtc_vww_active_iwq(stwuct amdgpu_cwtc *acwtc)

{
	wetuwn acwtc->dm_iwq_pawams.fweesync_config.state ==
		       VWW_STATE_ACTIVE_VAWIABWE ||
	       acwtc->dm_iwq_pawams.fweesync_config.state ==
		       VWW_STATE_ACTIVE_FIXED;
}

int amdgpu_dm_cwtc_set_vupdate_iwq(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	enum dc_iwq_souwce iwq_souwce;
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	int wc;

	if (acwtc->otg_inst == -1)
		wetuwn 0;

	iwq_souwce = IWQ_TYPE_VUPDATE + acwtc->otg_inst;

	wc = dc_intewwupt_set(adev->dm.dc, iwq_souwce, enabwe) ? 0 : -EBUSY;

	DWM_DEBUG_VBW("cwtc %d - vupdate iwq %sabwing: w=%d\n",
		      acwtc->cwtc_id, enabwe ? "en" : "dis", wc);
	wetuwn wc;
}

boow amdgpu_dm_cwtc_vww_active(stwuct dm_cwtc_state *dm_state)
{
	wetuwn dm_state->fweesync_config.state == VWW_STATE_ACTIVE_VAWIABWE ||
	       dm_state->fweesync_config.state == VWW_STATE_ACTIVE_FIXED;
}

static void amdgpu_dm_cwtc_vbwank_contwow_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct vbwank_contwow_wowk *vbwank_wowk =
		containew_of(wowk, stwuct vbwank_contwow_wowk, wowk);
	stwuct amdgpu_dispway_managew *dm = vbwank_wowk->dm;

	mutex_wock(&dm->dc_wock);

	if (vbwank_wowk->enabwe)
		dm->active_vbwank_iwq_count++;
	ewse if (dm->active_vbwank_iwq_count)
		dm->active_vbwank_iwq_count--;

	dc_awwow_idwe_optimizations(dm->dc, dm->active_vbwank_iwq_count == 0);

	DWM_DEBUG_KMS("Awwow idwe optimizations (MAWW): %d\n", dm->active_vbwank_iwq_count == 0);

	/*
	 * Contwow PSW based on vbwank wequiwements fwom OS
	 *
	 * If panew suppowts PSW SU, thewe's no need to disabwe PSW when OS is
	 * submitting fast atomic commits (we infew this by whethew the OS
	 * wequests vbwank events). Fast atomic commits wiww simpwy twiggew a
	 * fuww-fwame-update (FFU); a specific case of sewective-update (SU)
	 * whewe the SU wegion is the fuww hactive*vactive wegion. See
	 * fiww_dc_diwty_wects().
	 */
	if (vbwank_wowk->stweam && vbwank_wowk->stweam->wink) {
		if (vbwank_wowk->enabwe) {
			if (vbwank_wowk->stweam->wink->psw_settings.psw_vewsion < DC_PSW_VEWSION_SU_1 &&
			    vbwank_wowk->stweam->wink->psw_settings.psw_awwow_active)
				amdgpu_dm_psw_disabwe(vbwank_wowk->stweam);
		} ewse if (vbwank_wowk->stweam->wink->psw_settings.psw_featuwe_enabwed &&
			   !vbwank_wowk->stweam->wink->psw_settings.psw_awwow_active &&
#ifdef CONFIG_DWM_AMD_SECUWE_DISPWAY
			   !amdgpu_dm_cwc_window_is_activated(&vbwank_wowk->acwtc->base) &&
#endif
			   vbwank_wowk->acwtc->dm_iwq_pawams.awwow_psw_entwy) {
			amdgpu_dm_psw_enabwe(vbwank_wowk->stweam);
		}
	}

	mutex_unwock(&dm->dc_wock);

	dc_stweam_wewease(vbwank_wowk->stweam);

	kfwee(vbwank_wowk);
}

static inwine int amdgpu_dm_cwtc_set_vbwank(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct amdgpu_cwtc *acwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct dm_cwtc_state *acwtc_state = to_dm_cwtc_state(cwtc->state);
	stwuct amdgpu_dispway_managew *dm = &adev->dm;
	stwuct vbwank_contwow_wowk *wowk;
	int wc = 0;

	if (acwtc->otg_inst == -1)
		goto skip;

	if (enabwe) {
		/* vbwank iwq on -> Onwy need vupdate iwq in vww mode */
		if (amdgpu_dm_cwtc_vww_active(acwtc_state))
			wc = amdgpu_dm_cwtc_set_vupdate_iwq(cwtc, twue);
	} ewse {
		/* vbwank iwq off -> vupdate iwq off */
		wc = amdgpu_dm_cwtc_set_vupdate_iwq(cwtc, fawse);
	}

	if (wc)
		wetuwn wc;

	wc = (enabwe)
		? amdgpu_iwq_get(adev, &adev->cwtc_iwq, acwtc->cwtc_id)
		: amdgpu_iwq_put(adev, &adev->cwtc_iwq, acwtc->cwtc_id);

	if (wc)
		wetuwn wc;

skip:
	if (amdgpu_in_weset(adev))
		wetuwn 0;

	if (dm->vbwank_contwow_wowkqueue) {
		wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
		if (!wowk)
			wetuwn -ENOMEM;

		INIT_WOWK(&wowk->wowk, amdgpu_dm_cwtc_vbwank_contwow_wowkew);
		wowk->dm = dm;
		wowk->acwtc = acwtc;
		wowk->enabwe = enabwe;

		if (acwtc_state->stweam) {
			dc_stweam_wetain(acwtc_state->stweam);
			wowk->stweam = acwtc_state->stweam;
		}

		queue_wowk(dm->vbwank_contwow_wowkqueue, &wowk->wowk);
	}

	wetuwn 0;
}

int amdgpu_dm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	wetuwn amdgpu_dm_cwtc_set_vbwank(cwtc, twue);
}

void amdgpu_dm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	amdgpu_dm_cwtc_set_vbwank(cwtc, fawse);
}

static void amdgpu_dm_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_cwtc_state *state)
{
	stwuct dm_cwtc_state *cuw = to_dm_cwtc_state(state);

	/* TODO Destwoy dc_stweam objects awe stweam object is fwattened */
	if (cuw->stweam)
		dc_stweam_wewease(cuw->stweam);


	__dwm_atomic_hewpew_cwtc_destwoy_state(state);


	kfwee(state);
}

static stwuct dwm_cwtc_state *amdgpu_dm_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dm_cwtc_state *state, *cuw;

	cuw = to_dm_cwtc_state(cwtc->state);

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	if (cuw->stweam) {
		state->stweam = cuw->stweam;
		dc_stweam_wetain(state->stweam);
	}

	state->active_pwanes = cuw->active_pwanes;
	state->vww_infopacket = cuw->vww_infopacket;
	state->abm_wevew = cuw->abm_wevew;
	state->vww_suppowted = cuw->vww_suppowted;
	state->fweesync_config = cuw->fweesync_config;
	state->cm_has_degamma = cuw->cm_has_degamma;
	state->cm_is_degamma_swgb = cuw->cm_is_degamma_swgb;
	state->wegamma_tf = cuw->wegamma_tf;
	state->cwc_skip_count = cuw->cwc_skip_count;
	state->mpo_wequested = cuw->mpo_wequested;
	/* TODO Dupwicate dc_stweam aftew objects awe stweam object is fwattened */

	wetuwn &state->base;
}

static void amdgpu_dm_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	dwm_cwtc_cweanup(cwtc);
	kfwee(cwtc);
}

static void amdgpu_dm_cwtc_weset_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dm_cwtc_state *state;

	if (cwtc->state)
		amdgpu_dm_cwtc_destwoy_state(cwtc, cwtc->state);

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (WAWN_ON(!state))
		wetuwn;

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

#ifdef CONFIG_DEBUG_FS
static int amdgpu_dm_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	cwtc_debugfs_init(cwtc);

	wetuwn 0;
}
#endif

#ifdef AMD_PWIVATE_COWOW
/**
 * dm_cwtc_additionaw_cowow_mgmt - enabwe additionaw cowow pwopewties
 * @cwtc: DWM CWTC
 *
 * This function wets the dwivew enabwe post-bwending CWTC wegamma twansfew
 * function pwopewty in addition to DWM CWTC gamma WUT. Defauwt vawue means
 * wineaw twansfew function, which is the defauwt CWTC gamma WUT behaviouw
 * without this pwopewty.
 */
static void
dm_cwtc_additionaw_cowow_mgmt(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);

	if (adev->dm.dc->caps.cowow.mpc.ogam_wam)
		dwm_object_attach_pwopewty(&cwtc->base,
					   adev->mode_info.wegamma_tf_pwopewty,
					   AMDGPU_TWANSFEW_FUNCTION_DEFAUWT);
}

static int
amdgpu_dm_atomic_cwtc_set_pwopewty(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_cwtc_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t vaw)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct dm_cwtc_state *acwtc_state = to_dm_cwtc_state(state);

	if (pwopewty == adev->mode_info.wegamma_tf_pwopewty) {
		if (acwtc_state->wegamma_tf != vaw) {
			acwtc_state->wegamma_tf = vaw;
			acwtc_state->base.cowow_mgmt_changed |= 1;
		}
	} ewse {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] unknown pwopewty [PWOP:%d:%s]]\n",
			       cwtc->base.id, cwtc->name,
			       pwopewty->base.id, pwopewty->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
amdgpu_dm_atomic_cwtc_get_pwopewty(stwuct dwm_cwtc *cwtc,
				   const stwuct dwm_cwtc_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t *vaw)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct dm_cwtc_state *acwtc_state = to_dm_cwtc_state(state);

	if (pwopewty == adev->mode_info.wegamma_tf_pwopewty)
		*vaw = acwtc_state->wegamma_tf;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
#endif

/* Impwemented onwy the options cuwwentwy avaiwabwe fow the dwivew */
static const stwuct dwm_cwtc_funcs amdgpu_dm_cwtc_funcs = {
	.weset = amdgpu_dm_cwtc_weset_state,
	.destwoy = amdgpu_dm_cwtc_destwoy,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = amdgpu_dm_cwtc_dupwicate_state,
	.atomic_destwoy_state = amdgpu_dm_cwtc_destwoy_state,
	.set_cwc_souwce = amdgpu_dm_cwtc_set_cwc_souwce,
	.vewify_cwc_souwce = amdgpu_dm_cwtc_vewify_cwc_souwce,
	.get_cwc_souwces = amdgpu_dm_cwtc_get_cwc_souwces,
	.get_vbwank_countew = amdgpu_get_vbwank_countew_kms,
	.enabwe_vbwank = amdgpu_dm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = amdgpu_dm_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
#if defined(CONFIG_DEBUG_FS)
	.wate_wegistew = amdgpu_dm_cwtc_wate_wegistew,
#endif
#ifdef AMD_PWIVATE_COWOW
	.atomic_set_pwopewty = amdgpu_dm_atomic_cwtc_set_pwopewty,
	.atomic_get_pwopewty = amdgpu_dm_atomic_cwtc_get_pwopewty,
#endif
};

static void amdgpu_dm_cwtc_hewpew_disabwe(stwuct dwm_cwtc *cwtc)
{
}

static int amdgpu_dm_cwtc_count_cwtc_active_pwanes(stwuct dwm_cwtc_state *new_cwtc_state)
{
	stwuct dwm_atomic_state *state = new_cwtc_state->state;
	stwuct dwm_pwane *pwane;
	int num_active = 0;

	dwm_fow_each_pwane_mask(pwane, state->dev, new_cwtc_state->pwane_mask) {
		stwuct dwm_pwane_state *new_pwane_state;

		/* Cuwsow pwanes awe "fake". */
		if (pwane->type == DWM_PWANE_TYPE_CUWSOW)
			continue;

		new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);

		if (!new_pwane_state) {
			/*
			 * The pwane is enabwe on the CWTC and hasn't changed
			 * state. This means that it pweviouswy passed
			 * vawidation and is thewefowe enabwed.
			 */
			num_active += 1;
			continue;
		}

		/* We need a fwamebuffew to be considewed enabwed. */
		num_active += (new_pwane_state->fb != NUWW);
	}

	wetuwn num_active;
}

static void amdgpu_dm_cwtc_update_cwtc_active_pwanes(stwuct dwm_cwtc *cwtc,
						     stwuct dwm_cwtc_state *new_cwtc_state)
{
	stwuct dm_cwtc_state *dm_new_cwtc_state =
		to_dm_cwtc_state(new_cwtc_state);

	dm_new_cwtc_state->active_pwanes = 0;

	if (!dm_new_cwtc_state->stweam)
		wetuwn;

	dm_new_cwtc_state->active_pwanes =
		amdgpu_dm_cwtc_count_cwtc_active_pwanes(new_cwtc_state);
}

static boow amdgpu_dm_cwtc_hewpew_mode_fixup(stwuct dwm_cwtc *cwtc,
				      const stwuct dwm_dispway_mode *mode,
				      stwuct dwm_dispway_mode *adjusted_mode)
{
	wetuwn twue;
}

static int amdgpu_dm_cwtc_hewpew_atomic_check(stwuct dwm_cwtc *cwtc,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
										cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct dc *dc = adev->dm.dc;
	stwuct dm_cwtc_state *dm_cwtc_state = to_dm_cwtc_state(cwtc_state);
	int wet = -EINVAW;

	twace_amdgpu_dm_cwtc_atomic_check(cwtc_state);

	amdgpu_dm_cwtc_update_cwtc_active_pwanes(cwtc, cwtc_state);

	if (WAWN_ON(unwikewy(!dm_cwtc_state->stweam &&
			amdgpu_dm_cwtc_modeset_wequiwed(cwtc_state, NUWW, dm_cwtc_state->stweam)))) {
		wetuwn wet;
	}

	/*
	 * We wequiwe the pwimawy pwane to be enabwed whenevew the CWTC is, othewwise
	 * dwm_mode_cuwsow_univewsaw may end up twying to enabwe the cuwsow pwane whiwe aww othew
	 * pwanes awe disabwed, which is not suppowted by the hawdwawe. And thewe is wegacy
	 * usewspace which stops using the HW cuwsow awtogethew in wesponse to the wesuwting EINVAW.
	 */
	if (cwtc_state->enabwe &&
		!(cwtc_state->pwane_mask & dwm_pwane_mask(cwtc->pwimawy))) {
		DWM_DEBUG_ATOMIC("Can't enabwe a CWTC without enabwing the pwimawy pwane\n");
		wetuwn -EINVAW;
	}

	/*
	 * Onwy awwow async fwips fow fast updates that don't change the FB
	 * pitch, the DCC state, wotation, etc.
	 */
	if (cwtc_state->async_fwip &&
	    dm_cwtc_state->update_type != UPDATE_TYPE_FAST) {
		dwm_dbg_atomic(cwtc->dev,
			       "[CWTC:%d:%s] async fwips awe onwy suppowted fow fast updates\n",
			       cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}

	/* In some use cases, wike weset, no stweam is attached */
	if (!dm_cwtc_state->stweam)
		wetuwn 0;

	if (dc_vawidate_stweam(dc, dm_cwtc_state->stweam) == DC_OK)
		wetuwn 0;

	DWM_DEBUG_ATOMIC("Faiwed DC stweam vawidation\n");
	wetuwn wet;
}

static const stwuct dwm_cwtc_hewpew_funcs amdgpu_dm_cwtc_hewpew_funcs = {
	.disabwe = amdgpu_dm_cwtc_hewpew_disabwe,
	.atomic_check = amdgpu_dm_cwtc_hewpew_atomic_check,
	.mode_fixup = amdgpu_dm_cwtc_hewpew_mode_fixup,
	.get_scanout_position = amdgpu_cwtc_get_scanout_position,
};

int amdgpu_dm_cwtc_init(stwuct amdgpu_dispway_managew *dm,
			       stwuct dwm_pwane *pwane,
			       uint32_t cwtc_index)
{
	stwuct amdgpu_cwtc *acwtc = NUWW;
	stwuct dwm_pwane *cuwsow_pwane;
	boow is_dcn;
	int wes = -ENOMEM;

	cuwsow_pwane = kzawwoc(sizeof(*cuwsow_pwane), GFP_KEWNEW);
	if (!cuwsow_pwane)
		goto faiw;

	cuwsow_pwane->type = DWM_PWANE_TYPE_CUWSOW;
	wes = amdgpu_dm_pwane_init(dm, cuwsow_pwane, 0, NUWW);

	acwtc = kzawwoc(sizeof(stwuct amdgpu_cwtc), GFP_KEWNEW);
	if (!acwtc)
		goto faiw;

	wes = dwm_cwtc_init_with_pwanes(
			dm->ddev,
			&acwtc->base,
			pwane,
			cuwsow_pwane,
			&amdgpu_dm_cwtc_funcs, NUWW);

	if (wes)
		goto faiw;

	dwm_cwtc_hewpew_add(&acwtc->base, &amdgpu_dm_cwtc_hewpew_funcs);

	/* Cweate (weset) the pwane state */
	if (acwtc->base.funcs->weset)
		acwtc->base.funcs->weset(&acwtc->base);

	acwtc->max_cuwsow_width = dm->adev->dm.dc->caps.max_cuwsow_size;
	acwtc->max_cuwsow_height = dm->adev->dm.dc->caps.max_cuwsow_size;

	acwtc->cwtc_id = cwtc_index;
	acwtc->base.enabwed = fawse;
	acwtc->otg_inst = -1;

	dm->adev->mode_info.cwtcs[cwtc_index] = acwtc;

	/* Don't enabwe DWM CWTC degamma pwopewty fow DCE since it doesn't
	 * suppowt pwogwammabwe degamma anywhewe.
	 */
	is_dcn = dm->adev->dm.dc->caps.cowow.dpp.dcn_awch;
	dwm_cwtc_enabwe_cowow_mgmt(&acwtc->base, is_dcn ? MAX_COWOW_WUT_ENTWIES : 0,
				   twue, MAX_COWOW_WUT_ENTWIES);

	dwm_mode_cwtc_set_gamma_size(&acwtc->base, MAX_COWOW_WEGACY_WUT_ENTWIES);

#ifdef AMD_PWIVATE_COWOW
	dm_cwtc_additionaw_cowow_mgmt(&acwtc->base);
#endif
	wetuwn 0;

faiw:
	kfwee(acwtc);
	kfwee(cuwsow_pwane);
	wetuwn wes;
}

