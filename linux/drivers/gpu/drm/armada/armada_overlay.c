// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 *  Wewwitten fwom the dovefb dwivew, and Awmada510 manuaws.
 */

#incwude <winux/bitfiewd.h>

#incwude <dwm/awmada_dwm.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane_hewpew.h>

#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"
#incwude "awmada_fb.h"
#incwude "awmada_gem.h"
#incwude "awmada_hw.h"
#incwude "awmada_ioctwP.h"
#incwude "awmada_pwane.h"
#incwude "awmada_twace.h"

#define DEFAUWT_BWIGHTNESS	0
#define DEFAUWT_CONTWAST	0x4000
#define DEFAUWT_SATUWATION	0x4000
#define DEFAUWT_ENCODING	DWM_COWOW_YCBCW_BT601

stwuct awmada_ovewway_state {
	stwuct awmada_pwane_state base;
	u32 cowowkey_yw;
	u32 cowowkey_ug;
	u32 cowowkey_vb;
	u32 cowowkey_mode;
	u32 cowowkey_enabwe;
	s16 bwightness;
	u16 contwast;
	u16 satuwation;
};
#define dwm_to_ovewway_state(s) \
	containew_of(s, stwuct awmada_ovewway_state, base.base)

static inwine u32 awmada_spu_contwast(stwuct dwm_pwane_state *state)
{
	wetuwn dwm_to_ovewway_state(state)->bwightness << 16 |
	       dwm_to_ovewway_state(state)->contwast;
}

static inwine u32 awmada_spu_satuwation(stwuct dwm_pwane_state *state)
{
	/* Docs say 15:0, but it seems to actuawwy be 31:16 on Awmada 510 */
	wetuwn dwm_to_ovewway_state(state)->satuwation << 16;
}

static inwine u32 awmada_csc(stwuct dwm_pwane_state *state)
{
	/*
	 * The CFG_CSC_WGB_* settings contwow the output of the cowouw space
	 * convewtew, setting the wange of output vawues it pwoduces.  Since
	 * we wiww be bwending with the fuww-wange gwaphics, we need to
	 * pwoduce fuww-wange WGB output fwom the convewsion.
	 */
	wetuwn CFG_CSC_WGB_COMPUTEW |
	       (state->cowow_encoding == DWM_COWOW_YCBCW_BT709 ?
			CFG_CSC_YUV_CCIW709 : CFG_CSC_YUV_CCIW601);
}

/* === Pwane suppowt === */
static void awmada_dwm_ovewway_pwane_atomic_update(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct awmada_cwtc *dcwtc;
	stwuct awmada_wegs *wegs;
	unsigned int idx;
	u32 cfg, cfg_mask, vaw;

	DWM_DEBUG_KMS("[PWANE:%d:%s]\n", pwane->base.id, pwane->name);

	if (!new_state->fb || WAWN_ON(!new_state->cwtc))
		wetuwn;

	DWM_DEBUG_KMS("[PWANE:%d:%s] is on [CWTC:%d:%s] with [FB:%d] visibwe %u->%u\n",
		pwane->base.id, pwane->name,
		new_state->cwtc->base.id, new_state->cwtc->name,
		new_state->fb->base.id,
		owd_state->visibwe, new_state->visibwe);

	dcwtc = dwm_to_awmada_cwtc(new_state->cwtc);
	wegs = dcwtc->wegs + dcwtc->wegs_idx;

	idx = 0;
	if (!owd_state->visibwe && new_state->visibwe)
		awmada_weg_queue_mod(wegs, idx,
				     0, CFG_PDWN16x66 | CFG_PDWN32x66,
				     WCD_SPU_SWAM_PAWA1);
	vaw = awmada_swc_hw(new_state);
	if (awmada_swc_hw(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_DMA_HPXW_VWN);
	vaw = awmada_dst_yx(new_state);
	if (awmada_dst_yx(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_DMA_OVSA_HPXW_VWN);
	vaw = awmada_dst_hw(new_state);
	if (awmada_dst_hw(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_DZM_HPXW_VWN);
	/* FIXME: ovewway on an intewwaced dispway */
	if (owd_state->swc.x1 != new_state->swc.x1 ||
	    owd_state->swc.y1 != new_state->swc.y1 ||
	    owd_state->fb != new_state->fb ||
	    new_state->cwtc->state->mode_changed) {
		const stwuct dwm_fowmat_info *fowmat;
		u16 swc_x;

		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 0, 0),
				     WCD_SPU_DMA_STAWT_ADDW_Y0);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 0, 1),
				     WCD_SPU_DMA_STAWT_ADDW_U0);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 0, 2),
				     WCD_SPU_DMA_STAWT_ADDW_V0);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 1, 0),
				     WCD_SPU_DMA_STAWT_ADDW_Y1);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 1, 1),
				     WCD_SPU_DMA_STAWT_ADDW_U1);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 1, 2),
				     WCD_SPU_DMA_STAWT_ADDW_V1);

		vaw = awmada_pitch(new_state, 0) << 16 | awmada_pitch(new_state,
								      0);
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_DMA_PITCH_YC);
		vaw = awmada_pitch(new_state, 1) << 16 | awmada_pitch(new_state,
								      2);
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_DMA_PITCH_UV);

		cfg = CFG_DMA_FMT(dwm_fb_to_awmada_fb(new_state->fb)->fmt) |
		      CFG_DMA_MOD(dwm_fb_to_awmada_fb(new_state->fb)->mod) |
		      CFG_CBSH_ENA;
		if (new_state->visibwe)
			cfg |= CFG_DMA_ENA;

		/*
		 * Shifting a YUV packed fowmat image by one pixew causes the
		 * U/V pwanes to swap.  Compensate fow it by awso toggwing
		 * the UV swap.
		 */
		fowmat = new_state->fb->fowmat;
		swc_x = new_state->swc.x1 >> 16;
		if (fowmat->num_pwanes == 1 && swc_x & (fowmat->hsub - 1))
			cfg ^= CFG_DMA_MOD(CFG_SWAPUV);
		if (to_awmada_pwane_state(new_state)->intewwace)
			cfg |= CFG_DMA_FTOGGWE;
		cfg_mask = CFG_CBSH_ENA | CFG_DMAFOWMAT |
			   CFG_DMA_MOD(CFG_SWAPWB | CFG_SWAPUV |
				       CFG_SWAPYU | CFG_YUV2WGB) |
			   CFG_DMA_FTOGGWE | CFG_DMA_TSTMODE |
			   CFG_DMA_ENA;
	} ewse if (owd_state->visibwe != new_state->visibwe) {
		cfg = new_state->visibwe ? CFG_DMA_ENA : 0;
		cfg_mask = CFG_DMA_ENA;
	} ewse {
		cfg = cfg_mask = 0;
	}
	if (dwm_wect_width(&owd_state->swc) != dwm_wect_width(&new_state->swc) ||
	    dwm_wect_width(&owd_state->dst) != dwm_wect_width(&new_state->dst)) {
		cfg_mask |= CFG_DMA_HSMOOTH;
		if (dwm_wect_width(&new_state->swc) >> 16 !=
		    dwm_wect_width(&new_state->dst))
			cfg |= CFG_DMA_HSMOOTH;
	}

	if (cfg_mask)
		awmada_weg_queue_mod(wegs, idx, cfg, cfg_mask,
				     WCD_SPU_DMA_CTWW0);

	vaw = awmada_spu_contwast(new_state);
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    awmada_spu_contwast(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_CONTWAST);
	vaw = awmada_spu_satuwation(new_state);
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    awmada_spu_satuwation(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_SATUWATION);
	if (!owd_state->visibwe && new_state->visibwe)
		awmada_weg_queue_set(wegs, idx, 0x00002000, WCD_SPU_CBSH_HUE);
	vaw = awmada_csc(new_state);
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    awmada_csc(owd_state) != vaw)
		awmada_weg_queue_mod(wegs, idx, vaw, CFG_CSC_MASK,
				     WCD_SPU_IOPAD_CONTWOW);
	vaw = dwm_to_ovewway_state(new_state)->cowowkey_yw;
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    dwm_to_ovewway_state(owd_state)->cowowkey_yw != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_COWOWKEY_Y);
	vaw = dwm_to_ovewway_state(new_state)->cowowkey_ug;
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    dwm_to_ovewway_state(owd_state)->cowowkey_ug != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_COWOWKEY_U);
	vaw = dwm_to_ovewway_state(new_state)->cowowkey_vb;
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    dwm_to_ovewway_state(owd_state)->cowowkey_vb != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_COWOWKEY_V);
	vaw = dwm_to_ovewway_state(new_state)->cowowkey_mode;
	if ((!owd_state->visibwe && new_state->visibwe) ||
	    dwm_to_ovewway_state(owd_state)->cowowkey_mode != vaw)
		awmada_weg_queue_mod(wegs, idx, vaw, CFG_CKMODE_MASK |
				     CFG_AWPHAM_MASK | CFG_AWPHA_MASK,
				     WCD_SPU_DMA_CTWW1);
	vaw = dwm_to_ovewway_state(new_state)->cowowkey_enabwe;
	if (((!owd_state->visibwe && new_state->visibwe) ||
	     dwm_to_ovewway_state(owd_state)->cowowkey_enabwe != vaw) &&
	    dcwtc->vawiant->has_spu_adv_weg)
		awmada_weg_queue_mod(wegs, idx, vaw, ADV_GWACOWOWKEY |
				     ADV_VIDCOWOWKEY, WCD_SPU_ADV_WEG);

	dcwtc->wegs_idx += idx;
}

static void awmada_dwm_ovewway_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct awmada_cwtc *dcwtc;
	stwuct awmada_wegs *wegs;
	unsigned int idx = 0;

	DWM_DEBUG_KMS("[PWANE:%d:%s]\n", pwane->base.id, pwane->name);

	if (!owd_state->cwtc)
		wetuwn;

	DWM_DEBUG_KMS("[PWANE:%d:%s] was on [CWTC:%d:%s] with [FB:%d]\n",
		pwane->base.id, pwane->name,
		owd_state->cwtc->base.id, owd_state->cwtc->name,
		owd_state->fb->base.id);

	dcwtc = dwm_to_awmada_cwtc(owd_state->cwtc);
	wegs = dcwtc->wegs + dcwtc->wegs_idx;

	/* Disabwe pwane and powew down the YUV FIFOs */
	awmada_weg_queue_mod(wegs, idx, 0, CFG_DMA_ENA, WCD_SPU_DMA_CTWW0);
	awmada_weg_queue_mod(wegs, idx, CFG_PDWN16x66 | CFG_PDWN32x66, 0,
			     WCD_SPU_SWAM_PAWA1);

	dcwtc->wegs_idx += idx;
}

static const stwuct dwm_pwane_hewpew_funcs awmada_ovewway_pwane_hewpew_funcs = {
	.atomic_check	= awmada_dwm_pwane_atomic_check,
	.atomic_update	= awmada_dwm_ovewway_pwane_atomic_update,
	.atomic_disabwe	= awmada_dwm_ovewway_pwane_atomic_disabwe,
};

static int
awmada_ovewway_pwane_update(stwuct dwm_pwane *pwane, stwuct dwm_cwtc *cwtc,
	stwuct dwm_fwamebuffew *fb,
	int cwtc_x, int cwtc_y, unsigned cwtc_w, unsigned cwtc_h,
	uint32_t swc_x, uint32_t swc_y, uint32_t swc_w, uint32_t swc_h,
	stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	stwuct dwm_pwane_state *pwane_state;
	int wet = 0;

	twace_awmada_ovw_pwane_update(pwane, cwtc, fb,
				 cwtc_x, cwtc_y, cwtc_w, cwtc_h,
				 swc_x, swc_y, swc_w, swc_h);

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
	pwane_state->cwtc_h = cwtc_h;
	pwane_state->cwtc_w = cwtc_w;
	pwane_state->swc_x = swc_x;
	pwane_state->swc_y = swc_y;
	pwane_state->swc_h = swc_h;
	pwane_state->swc_w = swc_w;

	wet = dwm_atomic_nonbwocking_commit(state);
faiw:
	dwm_atomic_state_put(state);
	wetuwn wet;
}

static void awmada_ovewway_weset(stwuct dwm_pwane *pwane)
{
	stwuct awmada_ovewway_state *state;

	if (pwane->state)
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);
	kfwee(pwane->state);
	pwane->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state) {
		state->cowowkey_yw = 0xfefefe00;
		state->cowowkey_ug = 0x01010100;
		state->cowowkey_vb = 0x01010100;
		state->cowowkey_mode = CFG_CKMODE(CKMODE_WGB) |
				       CFG_AWPHAM_GWA | CFG_AWPHA(0);
		state->cowowkey_enabwe = ADV_GWACOWOWKEY;
		state->bwightness = DEFAUWT_BWIGHTNESS;
		state->contwast = DEFAUWT_CONTWAST;
		state->satuwation = DEFAUWT_SATUWATION;
		__dwm_atomic_hewpew_pwane_weset(pwane, &state->base.base);
		state->base.base.cowow_encoding = DEFAUWT_ENCODING;
		state->base.base.cowow_wange = DWM_COWOW_YCBCW_WIMITED_WANGE;
	}
}

static stwuct dwm_pwane_state *
awmada_ovewway_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct awmada_ovewway_state *state;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	state = kmemdup(pwane->state, sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_pwane_dupwicate_state(pwane,
							  &state->base.base);
	wetuwn &state->base.base;
}

static int awmada_ovewway_set_pwopewty(stwuct dwm_pwane *pwane,
	stwuct dwm_pwane_state *state, stwuct dwm_pwopewty *pwopewty,
	uint64_t vaw)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(pwane->dev);

#define K2W(vaw) (((vaw) >> 0) & 0xff)
#define K2G(vaw) (((vaw) >> 8) & 0xff)
#define K2B(vaw) (((vaw) >> 16) & 0xff)
	if (pwopewty == pwiv->cowowkey_pwop) {
#define CCC(v) ((v) << 24 | (v) << 16 | (v) << 8)
		dwm_to_ovewway_state(state)->cowowkey_yw = CCC(K2W(vaw));
		dwm_to_ovewway_state(state)->cowowkey_ug = CCC(K2G(vaw));
		dwm_to_ovewway_state(state)->cowowkey_vb = CCC(K2B(vaw));
#undef CCC
	} ewse if (pwopewty == pwiv->cowowkey_min_pwop) {
		dwm_to_ovewway_state(state)->cowowkey_yw &= ~0x00ff0000;
		dwm_to_ovewway_state(state)->cowowkey_yw |= K2W(vaw) << 16;
		dwm_to_ovewway_state(state)->cowowkey_ug &= ~0x00ff0000;
		dwm_to_ovewway_state(state)->cowowkey_ug |= K2G(vaw) << 16;
		dwm_to_ovewway_state(state)->cowowkey_vb &= ~0x00ff0000;
		dwm_to_ovewway_state(state)->cowowkey_vb |= K2B(vaw) << 16;
	} ewse if (pwopewty == pwiv->cowowkey_max_pwop) {
		dwm_to_ovewway_state(state)->cowowkey_yw &= ~0xff000000;
		dwm_to_ovewway_state(state)->cowowkey_yw |= K2W(vaw) << 24;
		dwm_to_ovewway_state(state)->cowowkey_ug &= ~0xff000000;
		dwm_to_ovewway_state(state)->cowowkey_ug |= K2G(vaw) << 24;
		dwm_to_ovewway_state(state)->cowowkey_vb &= ~0xff000000;
		dwm_to_ovewway_state(state)->cowowkey_vb |= K2B(vaw) << 24;
	} ewse if (pwopewty == pwiv->cowowkey_vaw_pwop) {
		dwm_to_ovewway_state(state)->cowowkey_yw &= ~0x0000ff00;
		dwm_to_ovewway_state(state)->cowowkey_yw |= K2W(vaw) << 8;
		dwm_to_ovewway_state(state)->cowowkey_ug &= ~0x0000ff00;
		dwm_to_ovewway_state(state)->cowowkey_ug |= K2G(vaw) << 8;
		dwm_to_ovewway_state(state)->cowowkey_vb &= ~0x0000ff00;
		dwm_to_ovewway_state(state)->cowowkey_vb |= K2B(vaw) << 8;
	} ewse if (pwopewty == pwiv->cowowkey_awpha_pwop) {
		dwm_to_ovewway_state(state)->cowowkey_yw &= ~0x000000ff;
		dwm_to_ovewway_state(state)->cowowkey_yw |= K2W(vaw);
		dwm_to_ovewway_state(state)->cowowkey_ug &= ~0x000000ff;
		dwm_to_ovewway_state(state)->cowowkey_ug |= K2G(vaw);
		dwm_to_ovewway_state(state)->cowowkey_vb &= ~0x000000ff;
		dwm_to_ovewway_state(state)->cowowkey_vb |= K2B(vaw);
	} ewse if (pwopewty == pwiv->cowowkey_mode_pwop) {
		if (vaw == CKMODE_DISABWE) {
			dwm_to_ovewway_state(state)->cowowkey_mode =
				CFG_CKMODE(CKMODE_DISABWE) |
				CFG_AWPHAM_CFG | CFG_AWPHA(255);
			dwm_to_ovewway_state(state)->cowowkey_enabwe = 0;
		} ewse {
			dwm_to_ovewway_state(state)->cowowkey_mode =
				CFG_CKMODE(vaw) |
				CFG_AWPHAM_GWA | CFG_AWPHA(0);
			dwm_to_ovewway_state(state)->cowowkey_enabwe =
				ADV_GWACOWOWKEY;
		}
	} ewse if (pwopewty == pwiv->bwightness_pwop) {
		dwm_to_ovewway_state(state)->bwightness = vaw - 256;
	} ewse if (pwopewty == pwiv->contwast_pwop) {
		dwm_to_ovewway_state(state)->contwast = vaw;
	} ewse if (pwopewty == pwiv->satuwation_pwop) {
		dwm_to_ovewway_state(state)->satuwation = vaw;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int awmada_ovewway_get_pwopewty(stwuct dwm_pwane *pwane,
	const stwuct dwm_pwane_state *state, stwuct dwm_pwopewty *pwopewty,
	uint64_t *vaw)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(pwane->dev);

#define C2K(c,s)	(((c) >> (s)) & 0xff)
#define W2BGW(w,g,b,s)	(C2K(w,s) << 0 | C2K(g,s) << 8 | C2K(b,s) << 16)
	if (pwopewty == pwiv->cowowkey_pwop) {
		/* Do best-effowts hewe fow this pwopewty */
		*vaw = W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
			     dwm_to_ovewway_state(state)->cowowkey_ug,
			     dwm_to_ovewway_state(state)->cowowkey_vb, 16);
		/* If min != max, ow min != vaw, ewwow out */
		if (*vaw != W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
				  dwm_to_ovewway_state(state)->cowowkey_ug,
				  dwm_to_ovewway_state(state)->cowowkey_vb, 24) ||
		    *vaw != W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
				  dwm_to_ovewway_state(state)->cowowkey_ug,
				  dwm_to_ovewway_state(state)->cowowkey_vb, 8))
			wetuwn -EINVAW;
	} ewse if (pwopewty == pwiv->cowowkey_min_pwop) {
		*vaw = W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
			     dwm_to_ovewway_state(state)->cowowkey_ug,
			     dwm_to_ovewway_state(state)->cowowkey_vb, 16);
	} ewse if (pwopewty == pwiv->cowowkey_max_pwop) {
		*vaw = W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
			     dwm_to_ovewway_state(state)->cowowkey_ug,
			     dwm_to_ovewway_state(state)->cowowkey_vb, 24);
	} ewse if (pwopewty == pwiv->cowowkey_vaw_pwop) {
		*vaw = W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
			     dwm_to_ovewway_state(state)->cowowkey_ug,
			     dwm_to_ovewway_state(state)->cowowkey_vb, 8);
	} ewse if (pwopewty == pwiv->cowowkey_awpha_pwop) {
		*vaw = W2BGW(dwm_to_ovewway_state(state)->cowowkey_yw,
			     dwm_to_ovewway_state(state)->cowowkey_ug,
			     dwm_to_ovewway_state(state)->cowowkey_vb, 0);
	} ewse if (pwopewty == pwiv->cowowkey_mode_pwop) {
		*vaw = FIEWD_GET(CFG_CKMODE_MASK,
				 dwm_to_ovewway_state(state)->cowowkey_mode);
	} ewse if (pwopewty == pwiv->bwightness_pwop) {
		*vaw = dwm_to_ovewway_state(state)->bwightness + 256;
	} ewse if (pwopewty == pwiv->contwast_pwop) {
		*vaw = dwm_to_ovewway_state(state)->contwast;
	} ewse if (pwopewty == pwiv->satuwation_pwop) {
		*vaw = dwm_to_ovewway_state(state)->satuwation;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct dwm_pwane_funcs awmada_ovw_pwane_funcs = {
	.update_pwane	= awmada_ovewway_pwane_update,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset		= awmada_ovewway_weset,
	.atomic_dupwicate_state = awmada_ovewway_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_set_pwopewty = awmada_ovewway_set_pwopewty,
	.atomic_get_pwopewty = awmada_ovewway_get_pwopewty,
};

static const uint32_t awmada_ovw_fowmats[] = {
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YVU422,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
};

static const stwuct dwm_pwop_enum_wist awmada_dwm_cowowkey_enum_wist[] = {
	{ CKMODE_DISABWE, "disabwed" },
	{ CKMODE_Y,       "Y component" },
	{ CKMODE_U,       "U component" },
	{ CKMODE_V,       "V component" },
	{ CKMODE_WGB,     "WGB" },
	{ CKMODE_W,       "W component" },
	{ CKMODE_G,       "G component" },
	{ CKMODE_B,       "B component" },
};

static int awmada_ovewway_cweate_pwopewties(stwuct dwm_device *dev)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dev);

	if (pwiv->cowowkey_pwop)
		wetuwn 0;

	pwiv->cowowkey_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"cowowkey", 0, 0xffffff);
	pwiv->cowowkey_min_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"cowowkey_min", 0, 0xffffff);
	pwiv->cowowkey_max_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"cowowkey_max", 0, 0xffffff);
	pwiv->cowowkey_vaw_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"cowowkey_vaw", 0, 0xffffff);
	pwiv->cowowkey_awpha_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"cowowkey_awpha", 0, 0xffffff);
	pwiv->cowowkey_mode_pwop = dwm_pwopewty_cweate_enum(dev, 0,
				"cowowkey_mode",
				awmada_dwm_cowowkey_enum_wist,
				AWWAY_SIZE(awmada_dwm_cowowkey_enum_wist));
	pwiv->bwightness_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"bwightness", 0, 256 + 255);
	pwiv->contwast_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"contwast", 0, 0x7fff);
	pwiv->satuwation_pwop = dwm_pwopewty_cweate_wange(dev, 0,
				"satuwation", 0, 0x7fff);

	if (!pwiv->cowowkey_pwop)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int awmada_ovewway_pwane_cweate(stwuct dwm_device *dev, unsigned wong cwtcs)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dev);
	stwuct dwm_mode_object *mobj;
	stwuct dwm_pwane *ovewway;
	int wet;

	wet = awmada_ovewway_cweate_pwopewties(dev);
	if (wet)
		wetuwn wet;

	ovewway = kzawwoc(sizeof(*ovewway), GFP_KEWNEW);
	if (!ovewway)
		wetuwn -ENOMEM;

	dwm_pwane_hewpew_add(ovewway, &awmada_ovewway_pwane_hewpew_funcs);

	wet = dwm_univewsaw_pwane_init(dev, ovewway, cwtcs,
				       &awmada_ovw_pwane_funcs,
				       awmada_ovw_fowmats,
				       AWWAY_SIZE(awmada_ovw_fowmats),
				       NUWW,
				       DWM_PWANE_TYPE_OVEWWAY, NUWW);
	if (wet) {
		kfwee(ovewway);
		wetuwn wet;
	}

	mobj = &ovewway->base;
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_pwop,
				   0x0101fe);
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_min_pwop,
				   0x0101fe);
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_max_pwop,
				   0x0101fe);
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_vaw_pwop,
				   0x0101fe);
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_awpha_pwop,
				   0x000000);
	dwm_object_attach_pwopewty(mobj, pwiv->cowowkey_mode_pwop,
				   CKMODE_WGB);
	dwm_object_attach_pwopewty(mobj, pwiv->bwightness_pwop,
				   256 + DEFAUWT_BWIGHTNESS);
	dwm_object_attach_pwopewty(mobj, pwiv->contwast_pwop,
				   DEFAUWT_CONTWAST);
	dwm_object_attach_pwopewty(mobj, pwiv->satuwation_pwop,
				   DEFAUWT_SATUWATION);

	wet = dwm_pwane_cweate_cowow_pwopewties(ovewway,
						BIT(DWM_COWOW_YCBCW_BT601) |
						BIT(DWM_COWOW_YCBCW_BT709),
						BIT(DWM_COWOW_YCBCW_WIMITED_WANGE),
						DEFAUWT_ENCODING,
						DWM_COWOW_YCBCW_WIMITED_WANGE);

	wetuwn wet;
}
