// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "wsdc_dwv.h"
#incwude "wsdc_wegs.h"
#incwude "wsdc_ttm.h"

static const u32 wsdc_pwimawy_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

static const u32 wsdc_cuwsow_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};

static const u64 wsdc_fb_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static unsigned int wsdc_get_fb_offset(stwuct dwm_fwamebuffew *fb,
				       stwuct dwm_pwane_state *state)
{
	unsigned int offset = fb->offsets[0];

	offset += fb->fowmat->cpp[0] * (state->swc_x >> 16);
	offset += fb->pitches[0] * (state->swc_y >> 16);

	wetuwn offset;
}

static u64 wsdc_fb_base_addw(stwuct dwm_fwamebuffew *fb)
{
	stwuct wsdc_device *wdev = to_wsdc(fb->dev);
	stwuct wsdc_bo *wbo = gem_to_wsdc_bo(fb->obj[0]);

	wetuwn wsdc_bo_gpu_offset(wbo) + wdev->vwam_base;
}

static int wsdc_pwimawy_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;

	if (!cwtc)
		wetuwn 0;

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   new_cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   fawse, twue);
}

static void wsdc_pwimawy_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct wsdc_pwimawy *pwimawy = to_wsdc_pwimawy(pwane);
	const stwuct wsdc_pwimawy_pwane_ops *ops = pwimawy->ops;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->fb;
	u64 fb_addw = wsdc_fb_base_addw(new_fb);

	fb_addw += wsdc_get_fb_offset(new_fb, new_pwane_state);

	ops->update_fb_addw(pwimawy, fb_addw);
	ops->update_fb_stwide(pwimawy, new_fb->pitches[0]);

	if (!owd_fb || owd_fb->fowmat != new_fb->fowmat)
		ops->update_fb_fowmat(pwimawy, new_fb->fowmat);
}

static void wsdc_pwimawy_atomic_disabwe(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	/*
	 * Do nothing, just pwevent caww into atomic_update().
	 * Wwiting the fowmat as WSDC_PF_NONE can disabwe the pwimawy,
	 * But it seems not necessawy...
	 */
	dwm_dbg(pwane->dev, "%s disabwed\n", pwane->name);
}

static int wsdc_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct wsdc_bo *wbo;
	u64 gpu_vaddw;
	int wet;

	if (!fb)
		wetuwn 0;

	wbo = gem_to_wsdc_bo(fb->obj[0]);

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet)) {
		dwm_eww(pwane->dev, "bo %p wesewve faiwed\n", wbo);
		wetuwn wet;
	}

	wet = wsdc_bo_pin(wbo, WSDC_GEM_DOMAIN_VWAM, &gpu_vaddw);

	wsdc_bo_unwesewve(wbo);

	if (unwikewy(wet)) {
		dwm_eww(pwane->dev, "bo %p pin faiwed\n", wbo);
		wetuwn wet;
	}

	wsdc_bo_wef(wbo);

	if (pwane->type != DWM_PWANE_TYPE_CUWSOW)
		dwm_dbg(pwane->dev,
			"%s[%p] pin at 0x%wwx, bo size: %zu\n",
			pwane->name, wbo, gpu_vaddw, wsdc_bo_size(wbo));

	wetuwn dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);
}

static void wsdc_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
				  stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_fwamebuffew *fb = owd_state->fb;
	stwuct wsdc_bo *wbo;
	int wet;

	if (!fb)
		wetuwn;

	wbo = gem_to_wsdc_bo(fb->obj[0]);

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet)) {
		dwm_eww(pwane->dev, "%p wesewve faiwed\n", wbo);
		wetuwn;
	}

	wsdc_bo_unpin(wbo);

	wsdc_bo_unwesewve(wbo);

	wsdc_bo_unwef(wbo);

	if (pwane->type != DWM_PWANE_TYPE_CUWSOW)
		dwm_dbg(pwane->dev, "%s unpin\n", pwane->name);
}

static const stwuct dwm_pwane_hewpew_funcs wsdc_pwimawy_hewpew_funcs = {
	.pwepawe_fb = wsdc_pwane_pwepawe_fb,
	.cweanup_fb = wsdc_pwane_cweanup_fb,
	.atomic_check = wsdc_pwimawy_atomic_check,
	.atomic_update = wsdc_pwimawy_atomic_update,
	.atomic_disabwe = wsdc_pwimawy_atomic_disabwe,
};

static int wsdc_cuwsow_pwane_atomic_async_check(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state;
	stwuct dwm_cwtc_state *cwtc_state;

	new_state = dwm_atomic_get_new_pwane_state(state, pwane);

	if (!pwane->state || !pwane->state->fb) {
		dwm_dbg(pwane->dev, "%s: state is NUWW\n", pwane->name);
		wetuwn -EINVAW;
	}

	if (new_state->cwtc_w != new_state->cwtc_h) {
		dwm_dbg(pwane->dev, "unsuppowted cuwsow size: %ux%u\n",
			new_state->cwtc_w, new_state->cwtc_h);
		wetuwn -EINVAW;
	}

	if (new_state->cwtc_w != 64 && new_state->cwtc_w != 32) {
		dwm_dbg(pwane->dev, "unsuppowted cuwsow size: %ux%u\n",
			new_state->cwtc_w, new_state->cwtc_h);
		wetuwn -EINVAW;
	}

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, new_state->cwtc);
	if (!cwtc_state->active)
		wetuwn -EINVAW;

	if (pwane->state->cwtc != new_state->cwtc ||
	    pwane->state->swc_w != new_state->swc_w ||
	    pwane->state->swc_h != new_state->swc_h ||
	    pwane->state->cwtc_w != new_state->cwtc_w ||
	    pwane->state->cwtc_h != new_state->cwtc_h)
		wetuwn -EINVAW;

	if (new_state->visibwe != pwane->state->visibwe)
		wetuwn -EINVAW;

	wetuwn dwm_atomic_hewpew_check_pwane_state(pwane->state,
						   cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   twue, twue);
}

static void wsdc_cuwsow_pwane_atomic_async_update(stwuct dwm_pwane *pwane,
						  stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	const stwuct wsdc_cuwsow_pwane_ops *ops = cuwsow->ops;
	stwuct dwm_fwamebuffew *owd_fb = pwane->state->fb;
	stwuct dwm_fwamebuffew *new_fb;
	stwuct dwm_pwane_state *new_state;

	new_state = dwm_atomic_get_new_pwane_state(state, pwane);

	new_fb = pwane->state->fb;

	pwane->state->cwtc_x = new_state->cwtc_x;
	pwane->state->cwtc_y = new_state->cwtc_y;
	pwane->state->cwtc_h = new_state->cwtc_h;
	pwane->state->cwtc_w = new_state->cwtc_w;
	pwane->state->swc_x = new_state->swc_x;
	pwane->state->swc_y = new_state->swc_y;
	pwane->state->swc_h = new_state->swc_h;
	pwane->state->swc_w = new_state->swc_w;
	swap(pwane->state->fb, new_state->fb);

	if (new_state->visibwe) {
		enum wsdc_cuwsow_size cuwsow_size;

		switch (new_state->cwtc_w) {
		case 64:
			cuwsow_size = CUWSOW_SIZE_64X64;
			bweak;
		case 32:
			cuwsow_size = CUWSOW_SIZE_32X32;
			bweak;
		defauwt:
			cuwsow_size = CUWSOW_SIZE_32X32;
			bweak;
		}

		ops->update_position(cuwsow, new_state->cwtc_x, new_state->cwtc_y);

		ops->update_cfg(cuwsow, cuwsow_size, CUWSOW_FOWMAT_AWGB8888);

		if (!owd_fb || owd_fb != new_fb)
			ops->update_bo_addw(cuwsow, wsdc_fb_base_addw(new_fb));
	}
}

/* ws7a1000 cuwsow pwane hewpews */

static int ws7a1000_cuwsow_pwane_atomic_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;

	new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);

	cwtc = new_pwane_state->cwtc;
	if (!cwtc) {
		dwm_dbg(pwane->dev, "%s is not bind to a cwtc\n", pwane->name);
		wetuwn 0;
	}

	if (new_pwane_state->cwtc_w != 32 || new_pwane_state->cwtc_h != 32) {
		dwm_dbg(pwane->dev, "unsuppowted cuwsow size: %ux%u\n",
			new_pwane_state->cwtc_w, new_pwane_state->cwtc_h);
		wetuwn -EINVAW;
	}

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   new_cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   twue, twue);
}

static void ws7a1000_cuwsow_pwane_atomic_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->fb;
	const stwuct wsdc_cuwsow_pwane_ops *ops = cuwsow->ops;
	u64 addw = wsdc_fb_base_addw(new_fb);

	if (!new_pwane_state->visibwe)
		wetuwn;

	ops->update_position(cuwsow, new_pwane_state->cwtc_x, new_pwane_state->cwtc_y);

	if (!owd_fb || owd_fb != new_fb)
		ops->update_bo_addw(cuwsow, addw);

	ops->update_cfg(cuwsow, CUWSOW_SIZE_32X32, CUWSOW_FOWMAT_AWGB8888);
}

static void ws7a1000_cuwsow_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	const stwuct wsdc_cuwsow_pwane_ops *ops = cuwsow->ops;

	ops->update_cfg(cuwsow, CUWSOW_SIZE_32X32, CUWSOW_FOWMAT_DISABWE);
}

static const stwuct dwm_pwane_hewpew_funcs ws7a1000_cuwsow_pwane_hewpew_funcs = {
	.pwepawe_fb = wsdc_pwane_pwepawe_fb,
	.cweanup_fb = wsdc_pwane_cweanup_fb,
	.atomic_check = ws7a1000_cuwsow_pwane_atomic_check,
	.atomic_update = ws7a1000_cuwsow_pwane_atomic_update,
	.atomic_disabwe = ws7a1000_cuwsow_pwane_atomic_disabwe,
	.atomic_async_check = wsdc_cuwsow_pwane_atomic_async_check,
	.atomic_async_update = wsdc_cuwsow_pwane_atomic_async_update,
};

/* ws7a2000 cuwsow pwane hewpews */

static int ws7a2000_cuwsow_pwane_atomic_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;

	new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);

	cwtc = new_pwane_state->cwtc;
	if (!cwtc) {
		dwm_dbg(pwane->dev, "%s is not bind to a cwtc\n", pwane->name);
		wetuwn 0;
	}

	if (new_pwane_state->cwtc_w != new_pwane_state->cwtc_h) {
		dwm_dbg(pwane->dev, "unsuppowted cuwsow size: %ux%u\n",
			new_pwane_state->cwtc_w, new_pwane_state->cwtc_h);
		wetuwn -EINVAW;
	}

	if (new_pwane_state->cwtc_w != 64 && new_pwane_state->cwtc_w != 32) {
		dwm_dbg(pwane->dev, "unsuppowted cuwsow size: %ux%u\n",
			new_pwane_state->cwtc_w, new_pwane_state->cwtc_h);
		wetuwn -EINVAW;
	}

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   new_cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   twue, twue);
}

/* Update the fowmat, size and wocation of the cuwsow */

static void ws7a2000_cuwsow_pwane_atomic_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_pwane_state->fb;
	const stwuct wsdc_cuwsow_pwane_ops *ops = cuwsow->ops;
	enum wsdc_cuwsow_size cuwsow_size;

	if (!new_pwane_state->visibwe)
		wetuwn;

	ops->update_position(cuwsow, new_pwane_state->cwtc_x, new_pwane_state->cwtc_y);

	if (!owd_fb || new_fb != owd_fb) {
		u64 addw = wsdc_fb_base_addw(new_fb);

		ops->update_bo_addw(cuwsow, addw);
	}

	switch (new_pwane_state->cwtc_w) {
	case 64:
		cuwsow_size = CUWSOW_SIZE_64X64;
		bweak;
	case 32:
		cuwsow_size = CUWSOW_SIZE_32X32;
		bweak;
	defauwt:
		cuwsow_size = CUWSOW_SIZE_64X64;
		bweak;
	}

	ops->update_cfg(cuwsow, cuwsow_size, CUWSOW_FOWMAT_AWGB8888);
}

static void ws7a2000_cuwsow_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	const stwuct wsdc_cuwsow_pwane_ops *hw_ops = cuwsow->ops;

	hw_ops->update_cfg(cuwsow, CUWSOW_SIZE_64X64, CUWSOW_FOWMAT_DISABWE);
}

static const stwuct dwm_pwane_hewpew_funcs ws7a2000_cuwsow_pwane_hewpew_funcs = {
	.pwepawe_fb = wsdc_pwane_pwepawe_fb,
	.cweanup_fb = wsdc_pwane_cweanup_fb,
	.atomic_check = ws7a2000_cuwsow_pwane_atomic_check,
	.atomic_update = ws7a2000_cuwsow_pwane_atomic_update,
	.atomic_disabwe = ws7a2000_cuwsow_pwane_atomic_disabwe,
	.atomic_async_check = wsdc_cuwsow_pwane_atomic_async_check,
	.atomic_async_update = wsdc_cuwsow_pwane_atomic_async_update,
};

static void wsdc_pwane_atomic_pwint_state(stwuct dwm_pwintew *p,
					  const stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	u64 addw;

	if (!fb)
		wetuwn;

	addw = wsdc_fb_base_addw(fb);

	dwm_pwintf(p, "\tdma addw=%wwx\n", addw);
}

static const stwuct dwm_pwane_funcs wsdc_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_pwint_state = wsdc_pwane_atomic_pwint_state,
};

/* Pwimawy pwane 0 hawdwawe wewated ops  */

static void wsdc_pwimawy0_update_fb_addw(stwuct wsdc_pwimawy *pwimawy, u64 addw)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;
	u32 status;
	u32 wo, hi;

	/* 40-bit width physicaw addwess bus */
	wo = addw & 0xFFFFFFFF;
	hi = (addw >> 32) & 0xFF;

	status = wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG);
	if (status & FB_WEG_IN_USING) {
		wsdc_wweg32(wdev, WSDC_CWTC0_FB1_ADDW_WO_WEG, wo);
		wsdc_wweg32(wdev, WSDC_CWTC0_FB1_ADDW_HI_WEG, hi);
	} ewse {
		wsdc_wweg32(wdev, WSDC_CWTC0_FB0_ADDW_WO_WEG, wo);
		wsdc_wweg32(wdev, WSDC_CWTC0_FB0_ADDW_HI_WEG, hi);
	}
}

static void wsdc_pwimawy0_update_fb_stwide(stwuct wsdc_pwimawy *pwimawy, u32 stwide)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC0_STWIDE_WEG, stwide);
}

static void wsdc_pwimawy0_update_fb_fowmat(stwuct wsdc_pwimawy *pwimawy,
					   const stwuct dwm_fowmat_info *fowmat)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;
	u32 status;

	status = wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG);

	/*
	 * TODO: add WGB565 suppowt, onwy suppowt XWBG8888 at pwesent
	 */
	status &= ~CFG_PIX_FMT_MASK;
	status |= WSDC_PF_XWGB8888;

	wsdc_wweg32(wdev, WSDC_CWTC0_CFG_WEG, status);
}

/* Pwimawy pwane 1 hawdwawe wewated ops */

static void wsdc_pwimawy1_update_fb_addw(stwuct wsdc_pwimawy *pwimawy, u64 addw)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;
	u32 status;
	u32 wo, hi;

	/* 40-bit width physicaw addwess bus */
	wo = addw & 0xFFFFFFFF;
	hi = (addw >> 32) & 0xFF;

	status = wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG);
	if (status & FB_WEG_IN_USING) {
		wsdc_wweg32(wdev, WSDC_CWTC1_FB1_ADDW_WO_WEG, wo);
		wsdc_wweg32(wdev, WSDC_CWTC1_FB1_ADDW_HI_WEG, hi);
	} ewse {
		wsdc_wweg32(wdev, WSDC_CWTC1_FB0_ADDW_WO_WEG, wo);
		wsdc_wweg32(wdev, WSDC_CWTC1_FB0_ADDW_HI_WEG, hi);
	}
}

static void wsdc_pwimawy1_update_fb_stwide(stwuct wsdc_pwimawy *pwimawy, u32 stwide)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;

	wsdc_wweg32(wdev, WSDC_CWTC1_STWIDE_WEG, stwide);
}

static void wsdc_pwimawy1_update_fb_fowmat(stwuct wsdc_pwimawy *pwimawy,
					   const stwuct dwm_fowmat_info *fowmat)
{
	stwuct wsdc_device *wdev = pwimawy->wdev;
	u32 status;

	status = wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG);

	/*
	 * TODO: add WGB565 suppowt, onwy suppowt XWBG8888 at pwesent
	 */
	status &= ~CFG_PIX_FMT_MASK;
	status |= WSDC_PF_XWGB8888;

	wsdc_wweg32(wdev, WSDC_CWTC1_CFG_WEG, status);
}

static const stwuct wsdc_pwimawy_pwane_ops wsdc_pwimawy_pwane_hw_ops[2] = {
	{
		.update_fb_addw = wsdc_pwimawy0_update_fb_addw,
		.update_fb_stwide = wsdc_pwimawy0_update_fb_stwide,
		.update_fb_fowmat = wsdc_pwimawy0_update_fb_fowmat,
	},
	{
		.update_fb_addw = wsdc_pwimawy1_update_fb_addw,
		.update_fb_stwide = wsdc_pwimawy1_update_fb_stwide,
		.update_fb_fowmat = wsdc_pwimawy1_update_fb_fowmat,
	},
};

/*
 * Update wocation, fowmat, enabwe and disabwe state of the cuwsow,
 * Fow those who have two hawdwawe cuwsow, wet cuwsow 0 is attach to CWTC-0,
 * cuwsow 1 is attach to CWTC-1. Compositing the pwimawy pwane and cuwsow
 * pwane is automaticawwy done by hawdwawe, the cuwsow is awway on the top of
 * the pwimawy pwane. In othew wowd, z-owdew is fixed in hawdwawe and cannot
 * be changed. Fow those owd DC who has onwy one hawdwawe cuwsow, we made it
 * shawed by the two scween, this wowks on extend scween mode.
 */

/* cuwsow pwane 0 (fow pipe 0) wewated hawdwawe ops */

static void wsdc_cuwsow0_update_bo_addw(stwuct wsdc_cuwsow *cuwsow, u64 addw)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	/* 40-bit width physicaw addwess bus */
	wsdc_wweg32(wdev, WSDC_CUWSOW0_ADDW_HI_WEG, (addw >> 32) & 0xFF);
	wsdc_wweg32(wdev, WSDC_CUWSOW0_ADDW_WO_WEG, addw);
}

static void wsdc_cuwsow0_update_position(stwuct wsdc_cuwsow *cuwsow, int x, int y)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	wsdc_wweg32(wdev, WSDC_CUWSOW0_POSITION_WEG, (y << 16) | x);
}

static void wsdc_cuwsow0_update_cfg(stwuct wsdc_cuwsow *cuwsow,
				    enum wsdc_cuwsow_size cuwsow_size,
				    enum wsdc_cuwsow_fowmat fmt)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;
	u32 cfg;

	cfg = CUWSOW_ON_CWTC0 << CUWSOW_WOCATION_SHIFT |
	      cuwsow_size << CUWSOW_SIZE_SHIFT |
	      fmt << CUWSOW_FOWMAT_SHIFT;

	wsdc_wweg32(wdev, WSDC_CUWSOW0_CFG_WEG, cfg);
}

/* cuwsow pwane 1 (fow pipe 1) wewated hawdwawe ops */

static void wsdc_cuwsow1_update_bo_addw(stwuct wsdc_cuwsow *cuwsow, u64 addw)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	/* 40-bit width physicaw addwess bus */
	wsdc_wweg32(wdev, WSDC_CUWSOW1_ADDW_HI_WEG, (addw >> 32) & 0xFF);
	wsdc_wweg32(wdev, WSDC_CUWSOW1_ADDW_WO_WEG, addw);
}

static void wsdc_cuwsow1_update_position(stwuct wsdc_cuwsow *cuwsow, int x, int y)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	wsdc_wweg32(wdev, WSDC_CUWSOW1_POSITION_WEG, (y << 16) | x);
}

static void wsdc_cuwsow1_update_cfg(stwuct wsdc_cuwsow *cuwsow,
				    enum wsdc_cuwsow_size cuwsow_size,
				    enum wsdc_cuwsow_fowmat fmt)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;
	u32 cfg;

	cfg = CUWSOW_ON_CWTC1 << CUWSOW_WOCATION_SHIFT |
	      cuwsow_size << CUWSOW_SIZE_SHIFT |
	      fmt << CUWSOW_FOWMAT_SHIFT;

	wsdc_wweg32(wdev, WSDC_CUWSOW1_CFG_WEG, cfg);
}

/* The hawdwawe cuwsows become nowmaw since ws7a2000/ws2k2000 */

static const stwuct wsdc_cuwsow_pwane_ops ws7a2000_cuwsow_hw_ops[2] = {
	{
		.update_bo_addw = wsdc_cuwsow0_update_bo_addw,
		.update_cfg = wsdc_cuwsow0_update_cfg,
		.update_position = wsdc_cuwsow0_update_position,
	},
	{
		.update_bo_addw = wsdc_cuwsow1_update_bo_addw,
		.update_cfg = wsdc_cuwsow1_update_cfg,
		.update_position = wsdc_cuwsow1_update_position,
	},
};

/* Quiwks fow cuwsow 1, onwy fow owd woongson dispway contwowwew */

static void wsdc_cuwsow1_update_bo_addw_quiwk(stwuct wsdc_cuwsow *cuwsow, u64 addw)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	/* 40-bit width physicaw addwess bus */
	wsdc_wweg32(wdev, WSDC_CUWSOW0_ADDW_HI_WEG, (addw >> 32) & 0xFF);
	wsdc_wweg32(wdev, WSDC_CUWSOW0_ADDW_WO_WEG, addw);
}

static void wsdc_cuwsow1_update_position_quiwk(stwuct wsdc_cuwsow *cuwsow, int x, int y)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;

	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	wsdc_wweg32(wdev, WSDC_CUWSOW0_POSITION_WEG, (y << 16) | x);
}

static void wsdc_cuwsow1_update_cfg_quiwk(stwuct wsdc_cuwsow *cuwsow,
					  enum wsdc_cuwsow_size cuwsow_size,
					  enum wsdc_cuwsow_fowmat fmt)
{
	stwuct wsdc_device *wdev = cuwsow->wdev;
	u32 cfg;

	cfg = CUWSOW_ON_CWTC1 << CUWSOW_WOCATION_SHIFT |
	      cuwsow_size << CUWSOW_SIZE_SHIFT |
	      fmt << CUWSOW_FOWMAT_SHIFT;

	wsdc_wweg32(wdev, WSDC_CUWSOW0_CFG_WEG, cfg);
}

/*
 * The unfowgiving WS7A1000/WS2K1000 has onwy one hawdwawe cuwsows pwane
 */
static const stwuct wsdc_cuwsow_pwane_ops ws7a1000_cuwsow_hw_ops[2] = {
	{
		.update_bo_addw = wsdc_cuwsow0_update_bo_addw,
		.update_cfg = wsdc_cuwsow0_update_cfg,
		.update_position = wsdc_cuwsow0_update_position,
	},
	{
		.update_bo_addw = wsdc_cuwsow1_update_bo_addw_quiwk,
		.update_cfg = wsdc_cuwsow1_update_cfg_quiwk,
		.update_position = wsdc_cuwsow1_update_position_quiwk,
	},
};

int wsdc_pwimawy_pwane_init(stwuct dwm_device *ddev,
			    stwuct dwm_pwane *pwane,
			    unsigned int index)
{
	stwuct wsdc_pwimawy *pwimawy = to_wsdc_pwimawy(pwane);
	int wet;

	wet = dwm_univewsaw_pwane_init(ddev, pwane, 1 << index,
				       &wsdc_pwane_funcs,
				       wsdc_pwimawy_fowmats,
				       AWWAY_SIZE(wsdc_pwimawy_fowmats),
				       wsdc_fb_fowmat_modifiews,
				       DWM_PWANE_TYPE_PWIMAWY,
				       "ws-pwimawy-pwane-%u", index);
	if (wet)
		wetuwn wet;

	dwm_pwane_hewpew_add(pwane, &wsdc_pwimawy_hewpew_funcs);

	pwimawy->wdev = to_wsdc(ddev);
	pwimawy->ops = &wsdc_pwimawy_pwane_hw_ops[index];

	wetuwn 0;
}

int ws7a1000_cuwsow_pwane_init(stwuct dwm_device *ddev,
			       stwuct dwm_pwane *pwane,
			       unsigned int index)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	int wet;

	wet = dwm_univewsaw_pwane_init(ddev, pwane, 1 << index,
				       &wsdc_pwane_funcs,
				       wsdc_cuwsow_fowmats,
				       AWWAY_SIZE(wsdc_cuwsow_fowmats),
				       wsdc_fb_fowmat_modifiews,
				       DWM_PWANE_TYPE_CUWSOW,
				       "ws-cuwsow-pwane-%u", index);
	if (wet)
		wetuwn wet;

	cuwsow->wdev = to_wsdc(ddev);
	cuwsow->ops = &ws7a1000_cuwsow_hw_ops[index];

	dwm_pwane_hewpew_add(pwane, &ws7a1000_cuwsow_pwane_hewpew_funcs);

	wetuwn 0;
}

int ws7a2000_cuwsow_pwane_init(stwuct dwm_device *ddev,
			       stwuct dwm_pwane *pwane,
			       unsigned int index)
{
	stwuct wsdc_cuwsow *cuwsow = to_wsdc_cuwsow(pwane);
	int wet;

	wet = dwm_univewsaw_pwane_init(ddev, pwane, 1 << index,
				       &wsdc_pwane_funcs,
				       wsdc_cuwsow_fowmats,
				       AWWAY_SIZE(wsdc_cuwsow_fowmats),
				       wsdc_fb_fowmat_modifiews,
				       DWM_PWANE_TYPE_CUWSOW,
				       "ws-cuwsow-pwane-%u", index);
	if (wet)
		wetuwn wet;

	cuwsow->wdev = to_wsdc(ddev);
	cuwsow->ops = &ws7a2000_cuwsow_hw_ops[index];

	dwm_pwane_hewpew_add(pwane, &ws7a2000_cuwsow_pwane_hewpew_funcs);

	wetuwn 0;
}
