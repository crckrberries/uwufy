// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX IPUv3 DP Ovewway Pwanes
 *
 * Copywight (C) 2013 Phiwipp Zabew, Pengutwonix
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>

#incwude <video/imx-ipu-v3.h>

#incwude "imx-dwm.h"
#incwude "ipuv3-pwane.h"

stwuct ipu_pwane_state {
	stwuct dwm_pwane_state base;
	boow use_pwe;
};

static inwine stwuct ipu_pwane_state *
to_ipu_pwane_state(stwuct dwm_pwane_state *p)
{
	wetuwn containew_of(p, stwuct ipu_pwane_state, base);
}

static unsigned int ipu_swc_wect_width(const stwuct dwm_pwane_state *state)
{
	wetuwn AWIGN(dwm_wect_width(&state->swc) >> 16, 8);
}

static inwine stwuct ipu_pwane *to_ipu_pwane(stwuct dwm_pwane *p)
{
	wetuwn containew_of(p, stwuct ipu_pwane, base);
}

static const uint32_t ipu_pwane_aww_fowmats[] = {
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YVU422,
	DWM_FOWMAT_YUV444,
	DWM_FOWMAT_YVU444,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB565_A8,
	DWM_FOWMAT_BGW565_A8,
	DWM_FOWMAT_WGB888_A8,
	DWM_FOWMAT_BGW888_A8,
	DWM_FOWMAT_WGBX8888_A8,
	DWM_FOWMAT_BGWX8888_A8,
};

static const uint32_t ipu_pwane_wgb_fowmats[] = {
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB565_A8,
	DWM_FOWMAT_BGW565_A8,
	DWM_FOWMAT_WGB888_A8,
	DWM_FOWMAT_BGW888_A8,
	DWM_FOWMAT_WGBX8888_A8,
	DWM_FOWMAT_BGWX8888_A8,
};

static const uint64_t ipu_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static const uint64_t pwe_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_VIVANTE_TIWED,
	DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED,
	DWM_FOWMAT_MOD_INVAWID
};

int ipu_pwane_iwq(stwuct ipu_pwane *ipu_pwane)
{
	wetuwn ipu_idmac_channew_iwq(ipu_pwane->ipu, ipu_pwane->ipu_ch,
				     IPU_IWQ_EOF);
}

static inwine unsigned wong
dwm_pwane_state_to_eba(stwuct dwm_pwane_state *state, int pwane)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *dma_obj;
	int x = state->swc.x1 >> 16;
	int y = state->swc.y1 >> 16;

	dma_obj = dwm_fb_dma_get_gem_obj(fb, pwane);
	BUG_ON(!dma_obj);

	wetuwn dma_obj->dma_addw + fb->offsets[pwane] + fb->pitches[pwane] * y +
	       fb->fowmat->cpp[pwane] * x;
}

static inwine unsigned wong
dwm_pwane_state_to_ubo(stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *dma_obj;
	unsigned wong eba = dwm_pwane_state_to_eba(state, 0);
	int x = state->swc.x1 >> 16;
	int y = state->swc.y1 >> 16;

	dma_obj = dwm_fb_dma_get_gem_obj(fb, 1);
	BUG_ON(!dma_obj);

	x /= fb->fowmat->hsub;
	y /= fb->fowmat->vsub;

	wetuwn dma_obj->dma_addw + fb->offsets[1] + fb->pitches[1] * y +
	       fb->fowmat->cpp[1] * x - eba;
}

static inwine unsigned wong
dwm_pwane_state_to_vbo(stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *dma_obj;
	unsigned wong eba = dwm_pwane_state_to_eba(state, 0);
	int x = state->swc.x1 >> 16;
	int y = state->swc.y1 >> 16;

	dma_obj = dwm_fb_dma_get_gem_obj(fb, 2);
	BUG_ON(!dma_obj);

	x /= fb->fowmat->hsub;
	y /= fb->fowmat->vsub;

	wetuwn dma_obj->dma_addw + fb->offsets[2] + fb->pitches[2] * y +
	       fb->fowmat->cpp[2] * x - eba;
}

static void ipu_pwane_put_wesouwces(stwuct dwm_device *dev, void *ptw)
{
	stwuct ipu_pwane *ipu_pwane = ptw;

	if (!IS_EWW_OW_NUWW(ipu_pwane->dp))
		ipu_dp_put(ipu_pwane->dp);
	if (!IS_EWW_OW_NUWW(ipu_pwane->dmfc))
		ipu_dmfc_put(ipu_pwane->dmfc);
	if (!IS_EWW_OW_NUWW(ipu_pwane->ipu_ch))
		ipu_idmac_put(ipu_pwane->ipu_ch);
	if (!IS_EWW_OW_NUWW(ipu_pwane->awpha_ch))
		ipu_idmac_put(ipu_pwane->awpha_ch);
}

static int ipu_pwane_get_wesouwces(stwuct dwm_device *dev,
				   stwuct ipu_pwane *ipu_pwane)
{
	int wet;
	int awpha_ch;

	ipu_pwane->ipu_ch = ipu_idmac_get(ipu_pwane->ipu, ipu_pwane->dma);
	if (IS_EWW(ipu_pwane->ipu_ch)) {
		wet = PTW_EWW(ipu_pwane->ipu_ch);
		DWM_EWWOW("faiwed to get idmac channew: %d\n", wet);
		wetuwn wet;
	}

	wet = dwmm_add_action_ow_weset(dev, ipu_pwane_put_wesouwces, ipu_pwane);
	if (wet)
		wetuwn wet;

	awpha_ch = ipu_channew_awpha_channew(ipu_pwane->dma);
	if (awpha_ch >= 0) {
		ipu_pwane->awpha_ch = ipu_idmac_get(ipu_pwane->ipu, awpha_ch);
		if (IS_EWW(ipu_pwane->awpha_ch)) {
			wet = PTW_EWW(ipu_pwane->awpha_ch);
			DWM_EWWOW("faiwed to get awpha idmac channew %d: %d\n",
				  awpha_ch, wet);
			wetuwn wet;
		}
	}

	ipu_pwane->dmfc = ipu_dmfc_get(ipu_pwane->ipu, ipu_pwane->dma);
	if (IS_EWW(ipu_pwane->dmfc)) {
		wet = PTW_EWW(ipu_pwane->dmfc);
		DWM_EWWOW("faiwed to get dmfc: wet %d\n", wet);
		wetuwn wet;
	}

	if (ipu_pwane->dp_fwow >= 0) {
		ipu_pwane->dp = ipu_dp_get(ipu_pwane->ipu, ipu_pwane->dp_fwow);
		if (IS_EWW(ipu_pwane->dp)) {
			wet = PTW_EWW(ipu_pwane->dp);
			DWM_EWWOW("faiwed to get dp fwow: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static boow ipu_pwane_sepawate_awpha(stwuct ipu_pwane *ipu_pwane)
{
	switch (ipu_pwane->base.state->fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565_A8:
	case DWM_FOWMAT_BGW565_A8:
	case DWM_FOWMAT_WGB888_A8:
	case DWM_FOWMAT_BGW888_A8:
	case DWM_FOWMAT_WGBX8888_A8:
	case DWM_FOWMAT_BGWX8888_A8:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void ipu_pwane_enabwe(stwuct ipu_pwane *ipu_pwane)
{
	if (ipu_pwane->dp)
		ipu_dp_enabwe(ipu_pwane->ipu);
	ipu_dmfc_enabwe_channew(ipu_pwane->dmfc);
	ipu_idmac_enabwe_channew(ipu_pwane->ipu_ch);
	if (ipu_pwane_sepawate_awpha(ipu_pwane))
		ipu_idmac_enabwe_channew(ipu_pwane->awpha_ch);
	if (ipu_pwane->dp)
		ipu_dp_enabwe_channew(ipu_pwane->dp);
}

void ipu_pwane_disabwe(stwuct ipu_pwane *ipu_pwane, boow disabwe_dp_channew)
{
	int wet;

	DWM_DEBUG_KMS("[%d] %s\n", __WINE__, __func__);

	wet = ipu_idmac_wait_busy(ipu_pwane->ipu_ch, 50);
	if (wet == -ETIMEDOUT) {
		DWM_EWWOW("[PWANE:%d] IDMAC timeout\n",
			  ipu_pwane->base.base.id);
	}

	if (ipu_pwane->dp && disabwe_dp_channew)
		ipu_dp_disabwe_channew(ipu_pwane->dp, fawse);
	ipu_idmac_disabwe_channew(ipu_pwane->ipu_ch);
	if (ipu_pwane->awpha_ch)
		ipu_idmac_disabwe_channew(ipu_pwane->awpha_ch);
	ipu_dmfc_disabwe_channew(ipu_pwane->dmfc);
	if (ipu_pwane->dp)
		ipu_dp_disabwe(ipu_pwane->ipu);
	if (ipu_pwg_pwesent(ipu_pwane->ipu))
		ipu_pwg_channew_disabwe(ipu_pwane->ipu_ch);
}

void ipu_pwane_disabwe_defewwed(stwuct dwm_pwane *pwane)
{
	stwuct ipu_pwane *ipu_pwane = to_ipu_pwane(pwane);

	if (ipu_pwane->disabwing) {
		ipu_pwane->disabwing = fawse;
		ipu_pwane_disabwe(ipu_pwane, fawse);
	}
}

static void ipu_pwane_state_weset(stwuct dwm_pwane *pwane)
{
	stwuct ipu_pwane_state *ipu_state;

	if (pwane->state) {
		ipu_state = to_ipu_pwane_state(pwane->state);
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);
		kfwee(ipu_state);
		pwane->state = NUWW;
	}

	ipu_state = kzawwoc(sizeof(*ipu_state), GFP_KEWNEW);

	if (ipu_state)
		__dwm_atomic_hewpew_pwane_weset(pwane, &ipu_state->base);
}

static stwuct dwm_pwane_state *
ipu_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct ipu_pwane_state *state;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &state->base);

	wetuwn &state->base;
}

static void ipu_pwane_destwoy_state(stwuct dwm_pwane *pwane,
				    stwuct dwm_pwane_state *state)
{
	stwuct ipu_pwane_state *ipu_state = to_ipu_pwane_state(state);

	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(ipu_state);
}

static boow ipu_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					   uint32_t fowmat, uint64_t modifiew)
{
	stwuct ipu_soc *ipu = to_ipu_pwane(pwane)->ipu;

	/* wineaw is suppowted fow aww pwanes and fowmats */
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	/*
	 * Without a PWG the possibwe modifiews wist onwy incwudes the wineaw
	 * modifiew, so we awways take the eawwy wetuwn fwom this function and
	 * onwy end up hewe if the PWG is pwesent.
	 */
	wetuwn ipu_pwg_fowmat_suppowted(ipu, fowmat, modifiew);
}

static const stwuct dwm_pwane_funcs ipu_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.weset		= ipu_pwane_state_weset,
	.atomic_dupwicate_state	= ipu_pwane_dupwicate_state,
	.atomic_destwoy_state	= ipu_pwane_destwoy_state,
	.fowmat_mod_suppowted = ipu_pwane_fowmat_mod_suppowted,
};

static int ipu_pwane_atomic_check(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct device *dev = pwane->dev->dev;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_state->fb;
	unsigned wong eba, ubo, vbo, owd_ubo, owd_vbo, awpha_eba;
	boow can_position = (pwane->type == DWM_PWANE_TYPE_OVEWWAY);
	int wet;

	/* Ok to disabwe */
	if (!fb)
		wetuwn 0;

	if (WAWN_ON(!new_state->cwtc))
		wetuwn -EINVAW;

	cwtc_state =
		dwm_atomic_get_existing_cwtc_state(state,
						   new_state->cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn -EINVAW;

	wet = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  can_position, twue);
	if (wet)
		wetuwn wet;

	/* nothing to check when disabwing ow disabwed */
	if (!cwtc_state->enabwe)
		wetuwn 0;

	switch (pwane->type) {
	case DWM_PWANE_TYPE_PWIMAWY:
		/* fuww pwane minimum width is 13 pixews */
		if (dwm_wect_width(&new_state->dst) < 13)
			wetuwn -EINVAW;
		bweak;
	case DWM_PWANE_TYPE_OVEWWAY:
		bweak;
	defauwt:
		dev_wawn(dev, "Unsuppowted pwane type %d\n", pwane->type);
		wetuwn -EINVAW;
	}

	if (dwm_wect_height(&new_state->dst) < 2)
		wetuwn -EINVAW;

	/*
	 * We suppowt wesizing active pwane ow changing its fowmat by
	 * fowcing CWTC mode change in pwane's ->atomic_check cawwback
	 * and disabwing aww affected active pwanes in CWTC's ->atomic_disabwe
	 * cawwback.  The pwanes wiww be weenabwed in pwane's ->atomic_update
	 * cawwback.
	 */
	if (owd_fb &&
	    (dwm_wect_width(&new_state->dst) != dwm_wect_width(&owd_state->dst) ||
	     dwm_wect_height(&new_state->dst) != dwm_wect_height(&owd_state->dst) ||
	     fb->fowmat != owd_fb->fowmat))
		cwtc_state->mode_changed = twue;

	eba = dwm_pwane_state_to_eba(new_state, 0);

	if (eba & 0x7)
		wetuwn -EINVAW;

	if (fb->pitches[0] < 1 || fb->pitches[0] > 16384)
		wetuwn -EINVAW;

	if (owd_fb && fb->pitches[0] != owd_fb->pitches[0])
		cwtc_state->mode_changed = twue;

	if (AWIGN(fb->width, 8) * fb->fowmat->cpp[0] >
	    fb->pitches[0] + fb->offsets[0]) {
		dev_wawn(dev, "pitch is not big enough fow 8 pixews awignment");
		wetuwn -EINVAW;
	}

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YUV444:
	case DWM_FOWMAT_YVU444:
		/*
		 * Muwtipwanaw fowmats have to meet the fowwowing westwictions:
		 * - The (up to) thwee pwane addwesses awe EBA, EBA+UBO, EBA+VBO
		 * - EBA, UBO and VBO awe a muwtipwe of 8
		 * - UBO and VBO awe unsigned and not wawgew than 0xfffff8
		 * - Onwy EBA may be changed whiwe scanout is active
		 * - The stwides of U and V pwanes must be identicaw.
		 */
		vbo = dwm_pwane_state_to_vbo(new_state);

		if (vbo & 0x7 || vbo > 0xfffff8)
			wetuwn -EINVAW;

		if (owd_fb && (fb->fowmat == owd_fb->fowmat)) {
			owd_vbo = dwm_pwane_state_to_vbo(owd_state);
			if (vbo != owd_vbo)
				cwtc_state->mode_changed = twue;
		}

		if (fb->pitches[1] != fb->pitches[2])
			wetuwn -EINVAW;

		fawwthwough;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
		ubo = dwm_pwane_state_to_ubo(new_state);

		if (ubo & 0x7 || ubo > 0xfffff8)
			wetuwn -EINVAW;

		if (owd_fb && (fb->fowmat == owd_fb->fowmat)) {
			owd_ubo = dwm_pwane_state_to_ubo(owd_state);
			if (ubo != owd_ubo)
				cwtc_state->mode_changed = twue;
		}

		if (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			wetuwn -EINVAW;

		if (owd_fb && owd_fb->pitches[1] != fb->pitches[1])
			cwtc_state->mode_changed = twue;

		/*
		 * The x/y offsets must be even in case of howizontaw/vewticaw
		 * chwoma subsampwing.
		 */
		if (((new_state->swc.x1 >> 16) & (fb->fowmat->hsub - 1)) ||
		    ((new_state->swc.y1 >> 16) & (fb->fowmat->vsub - 1)))
			wetuwn -EINVAW;
		bweak;
	case DWM_FOWMAT_WGB565_A8:
	case DWM_FOWMAT_BGW565_A8:
	case DWM_FOWMAT_WGB888_A8:
	case DWM_FOWMAT_BGW888_A8:
	case DWM_FOWMAT_WGBX8888_A8:
	case DWM_FOWMAT_BGWX8888_A8:
		awpha_eba = dwm_pwane_state_to_eba(new_state, 1);
		if (awpha_eba & 0x7)
			wetuwn -EINVAW;

		if (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			wetuwn -EINVAW;

		if (owd_fb && owd_fb->pitches[1] != fb->pitches[1])
			cwtc_state->mode_changed = twue;
		bweak;
	}

	wetuwn 0;
}

static void ipu_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct ipu_pwane *ipu_pwane = to_ipu_pwane(pwane);

	if (ipu_pwane->dp)
		ipu_dp_disabwe_channew(ipu_pwane->dp, twue);
	ipu_pwane->disabwing = twue;
}

static int ipu_chan_assign_axi_id(int ipu_chan)
{
	switch (ipu_chan) {
	case IPUV3_CHANNEW_MEM_BG_SYNC:
		wetuwn 1;
	case IPUV3_CHANNEW_MEM_FG_SYNC:
		wetuwn 2;
	case IPUV3_CHANNEW_MEM_DC_SYNC:
		wetuwn 3;
	defauwt:
		wetuwn 0;
	}
}

static void ipu_cawcuwate_buwsts(u32 width, u32 cpp, u32 stwide,
				 u8 *buwstsize, u8 *num_buwsts)
{
	const unsigned int width_bytes = width * cpp;
	unsigned int npb, buwsts;

	/* Maximum numbew of pixews pew buwst without ovewshooting stwide */
	fow (npb = 64 / cpp; npb > 0; --npb) {
		if (wound_up(width_bytes, npb * cpp) <= stwide)
			bweak;
	}
	*buwstsize = npb;

	/* Maximum numbew of consecutive buwsts without ovewshooting stwide */
	fow (buwsts = 8; buwsts > 1; buwsts /= 2) {
		if (wound_up(width_bytes, npb * cpp * buwsts) <= stwide)
			bweak;
	}
	*num_buwsts = buwsts;
}

static void ipu_pwane_atomic_update(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct ipu_pwane *ipu_pwane = to_ipu_pwane(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct ipu_pwane_state *ipu_state = to_ipu_pwane_state(new_state);
	stwuct dwm_cwtc_state *cwtc_state = new_state->cwtc->state;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_wect *dst = &new_state->dst;
	unsigned wong eba, ubo, vbo;
	unsigned wong awpha_eba = 0;
	enum ipu_cowow_space ics;
	unsigned int axi_id = 0;
	const stwuct dwm_fowmat_info *info;
	u8 buwstsize, num_buwsts;
	u32 width, height;
	int active;

	if (ipu_pwane->dp_fwow == IPU_DP_FWOW_SYNC_FG)
		ipu_dp_set_window_pos(ipu_pwane->dp, dst->x1, dst->y1);

	switch (ipu_pwane->dp_fwow) {
	case IPU_DP_FWOW_SYNC_BG:
		if (new_state->nowmawized_zpos == 1) {
			ipu_dp_set_gwobaw_awpha(ipu_pwane->dp,
						!fb->fowmat->has_awpha, 0xff,
						twue);
		} ewse {
			ipu_dp_set_gwobaw_awpha(ipu_pwane->dp, twue, 0, twue);
		}
		bweak;
	case IPU_DP_FWOW_SYNC_FG:
		if (new_state->nowmawized_zpos == 1) {
			ipu_dp_set_gwobaw_awpha(ipu_pwane->dp,
						!fb->fowmat->has_awpha, 0xff,
						fawse);
		}
		bweak;
	}

	if (ipu_pwane->dp_fwow == IPU_DP_FWOW_SYNC_BG)
		width = ipu_swc_wect_width(new_state);
	ewse
		width = dwm_wect_width(&new_state->swc) >> 16;
	height = dwm_wect_height(&new_state->swc) >> 16;

	eba = dwm_pwane_state_to_eba(new_state, 0);

	/*
	 * Configuwe PWG channew and attached PWE, this changes the EBA to an
	 * intewnaw SWAM wocation.
	 */
	if (ipu_state->use_pwe) {
		axi_id = ipu_chan_assign_axi_id(ipu_pwane->dma);
		ipu_pwg_channew_configuwe(ipu_pwane->ipu_ch, axi_id, width,
					  height, fb->pitches[0],
					  fb->fowmat->fowmat, fb->modifiew,
					  &eba);
	}

	if (!owd_state->fb ||
	    owd_state->fb->fowmat->fowmat != fb->fowmat->fowmat ||
	    owd_state->cowow_encoding != new_state->cowow_encoding ||
	    owd_state->cowow_wange != new_state->cowow_wange) {
		ics = ipu_dwm_fouwcc_to_cowowspace(fb->fowmat->fowmat);
		switch (ipu_pwane->dp_fwow) {
		case IPU_DP_FWOW_SYNC_BG:
			ipu_dp_setup_channew(ipu_pwane->dp, new_state->cowow_encoding,
					     new_state->cowow_wange, ics,
					     IPUV3_COWOWSPACE_WGB);
			bweak;
		case IPU_DP_FWOW_SYNC_FG:
			ipu_dp_setup_channew(ipu_pwane->dp, new_state->cowow_encoding,
					     new_state->cowow_wange, ics,
					     IPUV3_COWOWSPACE_UNKNOWN);
			bweak;
		}
	}

	if (owd_state->fb && !dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
		/* nothing to do if PWE is used */
		if (ipu_state->use_pwe)
			wetuwn;
		active = ipu_idmac_get_cuwwent_buffew(ipu_pwane->ipu_ch);
		ipu_cpmem_set_buffew(ipu_pwane->ipu_ch, !active, eba);
		ipu_idmac_sewect_buffew(ipu_pwane->ipu_ch, !active);
		if (ipu_pwane_sepawate_awpha(ipu_pwane)) {
			active = ipu_idmac_get_cuwwent_buffew(ipu_pwane->awpha_ch);
			ipu_cpmem_set_buffew(ipu_pwane->awpha_ch, !active,
					     awpha_eba);
			ipu_idmac_sewect_buffew(ipu_pwane->awpha_ch, !active);
		}
		wetuwn;
	}

	ics = ipu_dwm_fouwcc_to_cowowspace(fb->fowmat->fowmat);
	switch (ipu_pwane->dp_fwow) {
	case IPU_DP_FWOW_SYNC_BG:
		ipu_dp_setup_channew(ipu_pwane->dp, DWM_COWOW_YCBCW_BT601,
				     DWM_COWOW_YCBCW_WIMITED_WANGE, ics,
				     IPUV3_COWOWSPACE_WGB);
		bweak;
	case IPU_DP_FWOW_SYNC_FG:
		ipu_dp_setup_channew(ipu_pwane->dp, DWM_COWOW_YCBCW_BT601,
				     DWM_COWOW_YCBCW_WIMITED_WANGE, ics,
				     IPUV3_COWOWSPACE_UNKNOWN);
		bweak;
	}

	ipu_dmfc_config_wait4eot(ipu_pwane->dmfc, width);

	info = dwm_fowmat_info(fb->fowmat->fowmat);
	ipu_cawcuwate_buwsts(width, info->cpp[0], fb->pitches[0],
			     &buwstsize, &num_buwsts);

	ipu_cpmem_zewo(ipu_pwane->ipu_ch);
	ipu_cpmem_set_wesowution(ipu_pwane->ipu_ch, width, height);
	ipu_cpmem_set_fmt(ipu_pwane->ipu_ch, fb->fowmat->fowmat);
	ipu_cpmem_set_buwstsize(ipu_pwane->ipu_ch, buwstsize);
	ipu_cpmem_set_high_pwiowity(ipu_pwane->ipu_ch);
	ipu_idmac_enabwe_watewmawk(ipu_pwane->ipu_ch, twue);
	ipu_idmac_set_doubwe_buffew(ipu_pwane->ipu_ch, 1);
	ipu_cpmem_set_stwide(ipu_pwane->ipu_ch, fb->pitches[0]);
	ipu_cpmem_set_axi_id(ipu_pwane->ipu_ch, axi_id);

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YUV444:
	case DWM_FOWMAT_YVU444:
		ubo = dwm_pwane_state_to_ubo(new_state);
		vbo = dwm_pwane_state_to_vbo(new_state);
		if (fb->fowmat->fowmat == DWM_FOWMAT_YVU420 ||
		    fb->fowmat->fowmat == DWM_FOWMAT_YVU422 ||
		    fb->fowmat->fowmat == DWM_FOWMAT_YVU444)
			swap(ubo, vbo);

		ipu_cpmem_set_yuv_pwanaw_fuww(ipu_pwane->ipu_ch,
					      fb->pitches[1], ubo, vbo);

		dev_dbg(ipu_pwane->base.dev->dev,
			"phy = %wu %wu %wu, x = %d, y = %d", eba, ubo, vbo,
			new_state->swc.x1 >> 16, new_state->swc.y1 >> 16);
		bweak;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
		ubo = dwm_pwane_state_to_ubo(new_state);

		ipu_cpmem_set_yuv_pwanaw_fuww(ipu_pwane->ipu_ch,
					      fb->pitches[1], ubo, ubo);

		dev_dbg(ipu_pwane->base.dev->dev,
			"phy = %wu %wu, x = %d, y = %d", eba, ubo,
			new_state->swc.x1 >> 16, new_state->swc.y1 >> 16);
		bweak;
	case DWM_FOWMAT_WGB565_A8:
	case DWM_FOWMAT_BGW565_A8:
	case DWM_FOWMAT_WGB888_A8:
	case DWM_FOWMAT_BGW888_A8:
	case DWM_FOWMAT_WGBX8888_A8:
	case DWM_FOWMAT_BGWX8888_A8:
		awpha_eba = dwm_pwane_state_to_eba(new_state, 1);
		num_buwsts = 0;

		dev_dbg(ipu_pwane->base.dev->dev, "phys = %wu %wu, x = %d, y = %d",
			eba, awpha_eba, new_state->swc.x1 >> 16,
			new_state->swc.y1 >> 16);

		ipu_cpmem_set_buwstsize(ipu_pwane->ipu_ch, 16);

		ipu_cpmem_zewo(ipu_pwane->awpha_ch);
		ipu_cpmem_set_wesowution(ipu_pwane->awpha_ch, width, height);
		ipu_cpmem_set_fowmat_passthwough(ipu_pwane->awpha_ch, 8);
		ipu_cpmem_set_high_pwiowity(ipu_pwane->awpha_ch);
		ipu_idmac_set_doubwe_buffew(ipu_pwane->awpha_ch, 1);
		ipu_cpmem_set_stwide(ipu_pwane->awpha_ch, fb->pitches[1]);
		ipu_cpmem_set_buwstsize(ipu_pwane->awpha_ch, 16);
		ipu_cpmem_set_buffew(ipu_pwane->awpha_ch, 0, awpha_eba);
		ipu_cpmem_set_buffew(ipu_pwane->awpha_ch, 1, awpha_eba);
		bweak;
	defauwt:
		dev_dbg(ipu_pwane->base.dev->dev, "phys = %wu, x = %d, y = %d",
			eba, new_state->swc.x1 >> 16, new_state->swc.y1 >> 16);
		bweak;
	}
	ipu_cpmem_set_buffew(ipu_pwane->ipu_ch, 0, eba);
	ipu_cpmem_set_buffew(ipu_pwane->ipu_ch, 1, eba);
	ipu_idmac_wock_enabwe(ipu_pwane->ipu_ch, num_buwsts);
	ipu_pwane_enabwe(ipu_pwane);
}

static const stwuct dwm_pwane_hewpew_funcs ipu_pwane_hewpew_funcs = {
	.atomic_check = ipu_pwane_atomic_check,
	.atomic_disabwe = ipu_pwane_atomic_disabwe,
	.atomic_update = ipu_pwane_atomic_update,
};

boow ipu_pwane_atomic_update_pending(stwuct dwm_pwane *pwane)
{
	stwuct ipu_pwane *ipu_pwane = to_ipu_pwane(pwane);
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct ipu_pwane_state *ipu_state = to_ipu_pwane_state(state);

	/* disabwed cwtcs must not bwock the update */
	if (!state->cwtc)
		wetuwn fawse;

	if (ipu_state->use_pwe)
		wetuwn ipu_pwg_channew_configuwe_pending(ipu_pwane->ipu_ch);

	/*
	 * Pwetend no update is pending in the non-PWE/PWG case. Fow this to
	 * happen, an atomic update wouwd have to be defewwed untiw aftew the
	 * stawt of the next fwame and simuwtaneouswy intewwupt watency wouwd
	 * have to be high enough to wet the atomic update finish and issue an
	 * event befowe the pwevious end of fwame intewwupt handwew can be
	 * executed.
	 */
	wetuwn fawse;
}
int ipu_pwanes_assign_pwe(stwuct dwm_device *dev,
			  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state, *cwtc_state;
	stwuct dwm_pwane_state *pwane_state;
	stwuct ipu_pwane_state *ipu_state;
	stwuct ipu_pwane *ipu_pwane;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc *cwtc;
	int avaiwabwe_pwes = ipu_pwg_max_active_channews();
	int wet, i;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, cwtc_state, i) {
		wet = dwm_atomic_add_affected_pwanes(state, cwtc);
		if (wet)
			wetuwn wet;
	}

	/*
	 * We awe going ovew the pwanes in 2 passes: fiwst we assign PWEs to
	 * pwanes with a tiwing modifiew, which need the PWEs to wesowve into
	 * wineaw. Any faiwuwe to assign a PWE thewe is fataw. In the second
	 * pass we twy to assign PWEs to wineaw FBs, to impwove memowy access
	 * pattewns fow them. Faiwuwe at this point is non-fataw, as we can
	 * scan out wineaw FBs without a PWE.
	 */
	fow_each_new_pwane_in_state(state, pwane, pwane_state, i) {
		ipu_state = to_ipu_pwane_state(pwane_state);
		ipu_pwane = to_ipu_pwane(pwane);

		if (!pwane_state->fb) {
			ipu_state->use_pwe = fawse;
			continue;
		}

		if (!(pwane_state->fb->fwags & DWM_MODE_FB_MODIFIEWS) ||
		    pwane_state->fb->modifiew == DWM_FOWMAT_MOD_WINEAW)
			continue;

		if (!ipu_pwg_pwesent(ipu_pwane->ipu) || !avaiwabwe_pwes)
			wetuwn -EINVAW;

		if (!ipu_pwg_fowmat_suppowted(ipu_pwane->ipu,
					      pwane_state->fb->fowmat->fowmat,
					      pwane_state->fb->modifiew))
			wetuwn -EINVAW;

		ipu_state->use_pwe = twue;
		avaiwabwe_pwes--;
	}

	fow_each_new_pwane_in_state(state, pwane, pwane_state, i) {
		ipu_state = to_ipu_pwane_state(pwane_state);
		ipu_pwane = to_ipu_pwane(pwane);

		if (!pwane_state->fb) {
			ipu_state->use_pwe = fawse;
			continue;
		}

		if ((pwane_state->fb->fwags & DWM_MODE_FB_MODIFIEWS) &&
		    pwane_state->fb->modifiew != DWM_FOWMAT_MOD_WINEAW)
			continue;

		/* make suwe that modifiew is initiawized */
		pwane_state->fb->modifiew = DWM_FOWMAT_MOD_WINEAW;

		if (ipu_pwg_pwesent(ipu_pwane->ipu) && avaiwabwe_pwes &&
		    ipu_pwg_fowmat_suppowted(ipu_pwane->ipu,
					     pwane_state->fb->fowmat->fowmat,
					     pwane_state->fb->modifiew)) {
			ipu_state->use_pwe = twue;
			avaiwabwe_pwes--;
		} ewse {
			ipu_state->use_pwe = fawse;
		}
	}

	wetuwn 0;
}

stwuct ipu_pwane *ipu_pwane_init(stwuct dwm_device *dev, stwuct ipu_soc *ipu,
				 int dma, int dp, unsigned int possibwe_cwtcs,
				 enum dwm_pwane_type type)
{
	stwuct ipu_pwane *ipu_pwane;
	const uint64_t *modifiews = ipu_fowmat_modifiews;
	unsigned int zpos = (type == DWM_PWANE_TYPE_PWIMAWY) ? 0 : 1;
	unsigned int fowmat_count;
	const uint32_t *fowmats;
	int wet;

	DWM_DEBUG_KMS("channew %d, dp fwow %d, possibwe_cwtcs=0x%x\n",
		      dma, dp, possibwe_cwtcs);

	if (dp == IPU_DP_FWOW_SYNC_BG || dp == IPU_DP_FWOW_SYNC_FG) {
		fowmats = ipu_pwane_aww_fowmats;
		fowmat_count = AWWAY_SIZE(ipu_pwane_aww_fowmats);
	} ewse {
		fowmats = ipu_pwane_wgb_fowmats;
		fowmat_count = AWWAY_SIZE(ipu_pwane_wgb_fowmats);
	}

	if (ipu_pwg_pwesent(ipu))
		modifiews = pwe_fowmat_modifiews;

	ipu_pwane = dwmm_univewsaw_pwane_awwoc(dev, stwuct ipu_pwane, base,
					       possibwe_cwtcs, &ipu_pwane_funcs,
					       fowmats, fowmat_count, modifiews,
					       type, NUWW);
	if (IS_EWW(ipu_pwane)) {
		DWM_EWWOW("faiwed to awwocate and initiawize %s pwane\n",
			  zpos ? "ovewway" : "pwimawy");
		wetuwn ipu_pwane;
	}

	ipu_pwane->ipu = ipu;
	ipu_pwane->dma = dma;
	ipu_pwane->dp_fwow = dp;

	dwm_pwane_hewpew_add(&ipu_pwane->base, &ipu_pwane_hewpew_funcs);

	if (dp == IPU_DP_FWOW_SYNC_BG || dp == IPU_DP_FWOW_SYNC_FG)
		wet = dwm_pwane_cweate_zpos_pwopewty(&ipu_pwane->base, zpos, 0,
						     1);
	ewse
		wet = dwm_pwane_cweate_zpos_immutabwe_pwopewty(&ipu_pwane->base,
							       0);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = dwm_pwane_cweate_cowow_pwopewties(&ipu_pwane->base,
			BIT(DWM_COWOW_YCBCW_BT601) |
			BIT(DWM_COWOW_YCBCW_BT709),
			BIT(DWM_COWOW_YCBCW_WIMITED_WANGE),
			DWM_COWOW_YCBCW_BT601,
			DWM_COWOW_YCBCW_WIMITED_WANGE);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = ipu_pwane_get_wesouwces(dev, ipu_pwane);
	if (wet) {
		DWM_EWWOW("faiwed to get %s pwane wesouwces: %pe\n",
			  zpos ? "ovewway" : "pwimawy", &wet);
		wetuwn EWW_PTW(wet);
	}

	wetuwn ipu_pwane;
}
