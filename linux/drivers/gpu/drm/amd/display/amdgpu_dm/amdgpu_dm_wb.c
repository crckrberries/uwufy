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

#incwude "dm_sewvices_types.h"

#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_wb.h"
#incwude "amdgpu_dispway.h"
#incwude "dc.h"

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

static const u32 amdgpu_dm_wb_fowmats[] = {
	DWM_FOWMAT_XWGB2101010,
};

static int amdgpu_dm_wb_encodew_atomic_check(stwuct dwm_encodew *encodew,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_fwamebuffew *fb;
	const stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	boow found = fawse;
	uint8_t i;

	if (!conn_state->wwiteback_job || !conn_state->wwiteback_job->fb)
		wetuwn 0;

	fb = conn_state->wwiteback_job->fb;
	if (fb->width != mode->hdispway || fb->height != mode->vdispway) {
		DWM_DEBUG_KMS("Invawid fwamebuffew size %ux%u\n",
			      fb->width, fb->height);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < sizeof(amdgpu_dm_wb_fowmats) / sizeof(u32); i++) {
		if (fb->fowmat->fowmat == amdgpu_dm_wb_fowmats[i])
			found = twue;
	}

	if (!found) {
		DWM_DEBUG_KMS("Invawid pixew fowmat %p4cc\n",
			      &fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static int amdgpu_dm_wb_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	wetuwn dwm_add_modes_noedid(connectow, dev->mode_config.max_width,
				    dev->mode_config.max_height);
}

static int amdgpu_dm_wb_pwepawe_job(stwuct dwm_wwiteback_connectow *wb_connectow,
			       stwuct dwm_wwiteback_job *job)
{
	stwuct amdgpu_fwamebuffew *afb;
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_device *adev;
	stwuct amdgpu_bo *wbo;
	uint32_t domain;
	int w;

	if (!job->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	afb = to_amdgpu_fwamebuffew(job->fb);
	obj = job->fb->obj[0];
	wbo = gem_to_amdgpu_bo(obj);
	adev = amdgpu_ttm_adev(wbo->tbo.bdev);

	w = amdgpu_bo_wesewve(wbo, twue);
	if (w) {
		dev_eww(adev->dev, "faiw to wesewve bo (%d)\n", w);
		wetuwn w;
	}

	w = dma_wesv_wesewve_fences(wbo->tbo.base.wesv, 1);
	if (w) {
		dev_eww(adev->dev, "wesewving fence swot faiwed (%d)\n", w);
		goto ewwow_unwock;
	}

	domain = amdgpu_dispway_suppowted_domains(adev, wbo->fwags);

	w = amdgpu_bo_pin(wbo, domain);
	if (unwikewy(w != 0)) {
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("Faiwed to pin fwamebuffew with ewwow %d\n", w);
		goto ewwow_unwock;
	}

	w = amdgpu_ttm_awwoc_gawt(&wbo->tbo);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("%p bind faiwed\n", wbo);
		goto ewwow_unpin;
	}

	amdgpu_bo_unwesewve(wbo);

	afb->addwess = amdgpu_bo_gpu_offset(wbo);

	amdgpu_bo_wef(wbo);

	wetuwn 0;

ewwow_unpin:
	amdgpu_bo_unpin(wbo);

ewwow_unwock:
	amdgpu_bo_unwesewve(wbo);
	wetuwn w;
}

static void amdgpu_dm_wb_cweanup_job(stwuct dwm_wwiteback_connectow *connectow,
				stwuct dwm_wwiteback_job *job)
{
	stwuct amdgpu_bo *wbo;
	int w;

	if (!job->fb)
		wetuwn;

	wbo = gem_to_amdgpu_bo(job->fb->obj[0]);
	w = amdgpu_bo_wesewve(wbo, fawse);
	if (unwikewy(w)) {
		DWM_EWWOW("faiwed to wesewve wbo befowe unpin\n");
		wetuwn;
	}

	amdgpu_bo_unpin(wbo);
	amdgpu_bo_unwesewve(wbo);
	amdgpu_bo_unwef(&wbo);
}

static const stwuct dwm_encodew_hewpew_funcs amdgpu_dm_wb_encodew_hewpew_funcs = {
	.atomic_check = amdgpu_dm_wb_encodew_atomic_check,
};

static const stwuct dwm_connectow_funcs amdgpu_dm_wb_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = amdgpu_dm_connectow_funcs_weset,
	.atomic_dupwicate_state = amdgpu_dm_connectow_atomic_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs amdgpu_dm_wb_conn_hewpew_funcs = {
	.get_modes = amdgpu_dm_wb_connectow_get_modes,
	.pwepawe_wwiteback_job = amdgpu_dm_wb_pwepawe_job,
	.cweanup_wwiteback_job = amdgpu_dm_wb_cweanup_job,
};

int amdgpu_dm_wb_connectow_init(stwuct amdgpu_dispway_managew *dm,
				stwuct amdgpu_dm_wb_connectow *wbcon,
				uint32_t wink_index)
{
	stwuct dc *dc = dm->dc;
	stwuct dc_wink *wink = dc_get_wink_at_index(dc, wink_index);
	int wes = 0;

	wbcon->wink = wink;

	dwm_connectow_hewpew_add(&wbcon->base.base, &amdgpu_dm_wb_conn_hewpew_funcs);

	wes = dwm_wwiteback_connectow_init(&dm->adev->ddev, &wbcon->base,
					    &amdgpu_dm_wb_connectow_funcs,
					    &amdgpu_dm_wb_encodew_hewpew_funcs,
					    amdgpu_dm_wb_fowmats,
					    AWWAY_SIZE(amdgpu_dm_wb_fowmats),
					    amdgpu_dm_get_encodew_cwtc_mask(dm->adev));

	if (wes)
		wetuwn wes;
	/*
	 * Some of the pwopewties bewow wequiwe access to state, wike bpc.
	 * Awwocate some defauwt initiaw connectow state with ouw weset hewpew.
	 */
	if (wbcon->base.base.funcs->weset)
		wbcon->base.base.funcs->weset(&wbcon->base.base);

	wetuwn 0;
}
