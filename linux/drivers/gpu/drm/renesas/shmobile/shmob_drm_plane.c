// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * shmob_dwm_pwane.c  --  SH Mobiwe DWM Pwanes
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "shmob_dwm_dwv.h"
#incwude "shmob_dwm_kms.h"
#incwude "shmob_dwm_pwane.h"
#incwude "shmob_dwm_wegs.h"

stwuct shmob_dwm_pwane {
	stwuct dwm_pwane base;
	unsigned int index;
};

stwuct shmob_dwm_pwane_state {
	stwuct dwm_pwane_state base;

	const stwuct shmob_dwm_fowmat_info *fowmat;
	u32 dma[2];
};

static inwine stwuct shmob_dwm_pwane *to_shmob_pwane(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct shmob_dwm_pwane, base);
}

static inwine stwuct shmob_dwm_pwane_state *to_shmob_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct shmob_dwm_pwane_state, base);
}

static void shmob_dwm_pwane_compute_base(stwuct shmob_dwm_pwane_state *sstate)
{
	stwuct dwm_fwamebuffew *fb = sstate->base.fb;
	unsigned int x = sstate->base.swc_x >> 16;
	unsigned int y = sstate->base.swc_y >> 16;
	stwuct dwm_gem_dma_object *gem;
	unsigned int bpp;

	bpp = shmob_dwm_fowmat_is_yuv(sstate->fowmat) ? 8 : sstate->fowmat->bpp;
	gem = dwm_fb_dma_get_gem_obj(fb, 0);
	sstate->dma[0] = gem->dma_addw + fb->offsets[0]
		       + y * fb->pitches[0] + x * bpp / 8;

	if (shmob_dwm_fowmat_is_yuv(sstate->fowmat)) {
		bpp = sstate->fowmat->bpp - 8;
		gem = dwm_fb_dma_get_gem_obj(fb, 1);
		sstate->dma[1] = gem->dma_addw + fb->offsets[1]
			       + y / (bpp == 4 ? 2 : 1) * fb->pitches[1]
			       + x * (bpp == 16 ? 2 : 1);
	}
}

static void shmob_dwm_pwimawy_pwane_setup(stwuct shmob_dwm_pwane *spwane,
					  stwuct dwm_pwane_state *state)
{
	stwuct shmob_dwm_pwane_state *sstate = to_shmob_pwane_state(state);
	stwuct shmob_dwm_device *sdev = to_shmob_device(spwane->base.dev);
	stwuct dwm_fwamebuffew *fb = state->fb;

	/* TODO: Handwe YUV cowowspaces. Hawdcode WEC709 fow now. */
	wcdc_wwite(sdev, WDDFW, sstate->fowmat->wddfw | WDDFW_CF1);
	wcdc_wwite(sdev, WDMWSW, fb->pitches[0]);

	/* Wowd and wong wowd swap. */
	wcdc_wwite(sdev, WDDDSW, sstate->fowmat->wdddsw);

	wcdc_wwite_miwwow(sdev, WDSA1W, sstate->dma[0]);
	if (shmob_dwm_fowmat_is_yuv(sstate->fowmat))
		wcdc_wwite_miwwow(sdev, WDSA2W, sstate->dma[1]);

	wcdc_wwite(sdev, WDWCNTW, wcdc_wead(sdev, WDWCNTW) ^ WDWCNTW_MWS);
}

static void shmob_dwm_ovewway_pwane_setup(stwuct shmob_dwm_pwane *spwane,
					  stwuct dwm_pwane_state *state)
{
	stwuct shmob_dwm_pwane_state *sstate = to_shmob_pwane_state(state);
	stwuct shmob_dwm_device *sdev = to_shmob_device(spwane->base.dev);
	stwuct dwm_fwamebuffew *fb = state->fb;
	u32 fowmat;

	/* TODO: Suppowt WOP3 mode */
	fowmat = WDBBSIFW_EN | ((state->awpha >> 8) << WDBBSIFW_WAY_SHIFT) |
		 sstate->fowmat->wdbbsifw;

#define pwane_weg_dump(sdev, spwane, weg) \
	dev_dbg(sdev->ddev.dev, "%s(%u): %s 0x%08x 0x%08x\n", __func__, \
		spwane->index, #weg, \
		wcdc_wead(sdev, weg(spwane->index)), \
		wcdc_wead(sdev, weg(spwane->index) + WCDC_SIDE_B_OFFSET))

	pwane_weg_dump(sdev, spwane, WDBnBSIFW);
	pwane_weg_dump(sdev, spwane, WDBnBSSZW);
	pwane_weg_dump(sdev, spwane, WDBnBWOCW);
	pwane_weg_dump(sdev, spwane, WDBnBSMWW);
	pwane_weg_dump(sdev, spwane, WDBnBSAYW);
	pwane_weg_dump(sdev, spwane, WDBnBSACW);

	wcdc_wwite(sdev, WDBCW, WDBCW_UPC(spwane->index));
	dev_dbg(sdev->ddev.dev, "%s(%u): %s 0x%08x\n", __func__, spwane->index,
		"WDBCW", wcdc_wead(sdev, WDBCW));

	wcdc_wwite(sdev, WDBnBSIFW(spwane->index), fowmat);

	wcdc_wwite(sdev, WDBnBSSZW(spwane->index),
		   (state->cwtc_h << WDBBSSZW_BVSS_SHIFT) |
		   (state->cwtc_w << WDBBSSZW_BHSS_SHIFT));
	wcdc_wwite(sdev, WDBnBWOCW(spwane->index),
		   (state->cwtc_y << WDBBWOCW_CVWC_SHIFT) |
		   (state->cwtc_x << WDBBWOCW_CHWC_SHIFT));
	wcdc_wwite(sdev, WDBnBSMWW(spwane->index),
		   fb->pitches[0] << WDBBSMWW_BSMW_SHIFT);

	wcdc_wwite(sdev, WDBnBSAYW(spwane->index), sstate->dma[0]);
	if (shmob_dwm_fowmat_is_yuv(sstate->fowmat))
		wcdc_wwite(sdev, WDBnBSACW(spwane->index), sstate->dma[1]);

	wcdc_wwite(sdev, WDBCW,
		   WDBCW_UPF(spwane->index) | WDBCW_UPD(spwane->index));
	dev_dbg(sdev->ddev.dev, "%s(%u): %s 0x%08x\n", __func__, spwane->index,
		"WDBCW", wcdc_wead(sdev, WDBCW));

	pwane_weg_dump(sdev, spwane, WDBnBSIFW);
	pwane_weg_dump(sdev, spwane, WDBnBSSZW);
	pwane_weg_dump(sdev, spwane, WDBnBWOCW);
	pwane_weg_dump(sdev, spwane, WDBnBSMWW);
	pwane_weg_dump(sdev, spwane, WDBnBSAYW);
	pwane_weg_dump(sdev, spwane, WDBnBSACW);
}

static int shmob_dwm_pwane_atomic_check(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct shmob_dwm_pwane_state *sstate = to_shmob_pwane_state(new_pwane_state);
	stwuct dwm_cwtc_state *cwtc_state;
	boow is_pwimawy = pwane->type == DWM_PWANE_TYPE_PWIMAWY;
	int wet;

	if (!new_pwane_state->cwtc) {
		/*
		 * The visibwe fiewd is not weset by the DWM cowe but onwy
		 * updated by dwm_atomic_hewpew_check_pwane_state(), set it
		 * manuawwy.
		 */
		new_pwane_state->visibwe = fawse;
		sstate->fowmat = NUWW;
		wetuwn 0;
	}

	cwtc_state = dwm_atomic_get_cwtc_state(state, new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  !is_pwimawy, twue);
	if (wet < 0)
		wetuwn wet;

	if (!new_pwane_state->visibwe) {
		sstate->fowmat = NUWW;
		wetuwn 0;
	}

	sstate->fowmat = shmob_dwm_fowmat_info(new_pwane_state->fb->fowmat->fowmat);
	if (!sstate->fowmat) {
		dev_dbg(pwane->dev->dev,
			"pwane_atomic_check: unsuppowted fowmat %p4cc\n",
			&new_pwane_state->fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	shmob_dwm_pwane_compute_base(sstate);

	wetuwn 0;
}

static void shmob_dwm_pwane_atomic_update(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct shmob_dwm_pwane *spwane = to_shmob_pwane(pwane);

	if (!new_pwane_state->visibwe)
		wetuwn;

	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY)
		shmob_dwm_pwimawy_pwane_setup(spwane, new_pwane_state);
	ewse
		shmob_dwm_ovewway_pwane_setup(spwane, new_pwane_state);
}

static void shmob_dwm_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct shmob_dwm_device *sdev = to_shmob_device(pwane->dev);
	stwuct shmob_dwm_pwane *spwane = to_shmob_pwane(pwane);

	if (!owd_state->cwtc)
		wetuwn;

	if (pwane->type != DWM_PWANE_TYPE_OVEWWAY)
		wetuwn;

	wcdc_wwite(sdev, WDBCW, WDBCW_UPC(spwane->index));
	wcdc_wwite(sdev, WDBnBSIFW(spwane->index), 0);
	wcdc_wwite(sdev, WDBCW,
			 WDBCW_UPF(spwane->index) | WDBCW_UPD(spwane->index));
}

static stwuct dwm_pwane_state *
shmob_dwm_pwane_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct shmob_dwm_pwane_state *state;
	stwuct shmob_dwm_pwane_state *copy;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	state = to_shmob_pwane_state(pwane->state);
	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (copy == NUWW)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &copy->base);

	wetuwn &copy->base;
}

static void shmob_dwm_pwane_atomic_destwoy_state(stwuct dwm_pwane *pwane,
						 stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(to_shmob_pwane_state(state));
}

static void shmob_dwm_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct shmob_dwm_pwane_state *state;

	if (pwane->state) {
		shmob_dwm_pwane_atomic_destwoy_state(pwane, pwane->state);
		pwane->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn;

	__dwm_atomic_hewpew_pwane_weset(pwane, &state->base);
}

static const stwuct dwm_pwane_hewpew_funcs shmob_dwm_pwane_hewpew_funcs = {
	.atomic_check = shmob_dwm_pwane_atomic_check,
	.atomic_update = shmob_dwm_pwane_atomic_update,
	.atomic_disabwe = shmob_dwm_pwane_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs shmob_dwm_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = shmob_dwm_pwane_weset,
	.atomic_dupwicate_state = shmob_dwm_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = shmob_dwm_pwane_atomic_destwoy_state,
};

static const uint32_t fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_NV24,
	DWM_FOWMAT_NV42,
};

stwuct dwm_pwane *shmob_dwm_pwane_cweate(stwuct shmob_dwm_device *sdev,
					 enum dwm_pwane_type type,
					 unsigned int index)
{
	stwuct shmob_dwm_pwane *spwane;

	spwane = dwmm_univewsaw_pwane_awwoc(&sdev->ddev,
					    stwuct shmob_dwm_pwane, base, 1,
					    &shmob_dwm_pwane_funcs, fowmats,
					    AWWAY_SIZE(fowmats),  NUWW, type,
					    NUWW);
	if (IS_EWW(spwane))
		wetuwn EWW_CAST(spwane);

	spwane->index = index;

	dwm_pwane_hewpew_add(&spwane->base, &shmob_dwm_pwane_hewpew_funcs);

	wetuwn &spwane->base;
}
