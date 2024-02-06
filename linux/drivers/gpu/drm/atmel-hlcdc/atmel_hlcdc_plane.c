// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/dmapoow.h>
#incwude <winux/mfd/atmew-hwcdc.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "atmew_hwcdc_dc.h"

/**
 * stwuct atmew_hwcdc_pwane_state - Atmew HWCDC Pwane state stwuctuwe.
 *
 * @base: DWM pwane state
 * @cwtc_x: x position of the pwane wewative to the CWTC
 * @cwtc_y: y position of the pwane wewative to the CWTC
 * @cwtc_w: visibwe width of the pwane
 * @cwtc_h: visibwe height of the pwane
 * @swc_x: x buffew position
 * @swc_y: y buffew position
 * @swc_w: buffew width
 * @swc_h: buffew height
 * @disc_x: x discawd position
 * @disc_y: y discawd position
 * @disc_w: discawd width
 * @disc_h: discawd height
 * @ahb_id: AHB identification numbew
 * @bpp: bytes pew pixew deduced fwom pixew_fowmat
 * @offsets: offsets to appwy to the GEM buffews
 * @xstwide: vawue to add to the pixew pointew between each wine
 * @pstwide: vawue to add to the pixew pointew between each pixew
 * @npwanes: numbew of pwanes (deduced fwom pixew_fowmat)
 * @dscws: DMA descwiptows
 */
stwuct atmew_hwcdc_pwane_state {
	stwuct dwm_pwane_state base;
	int cwtc_x;
	int cwtc_y;
	unsigned int cwtc_w;
	unsigned int cwtc_h;
	uint32_t swc_x;
	uint32_t swc_y;
	uint32_t swc_w;
	uint32_t swc_h;

	int disc_x;
	int disc_y;
	int disc_w;
	int disc_h;

	int ahb_id;

	/* These fiewds awe pwivate and shouwd not be touched */
	int bpp[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	unsigned int offsets[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	int xstwide[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	int pstwide[ATMEW_HWCDC_WAYEW_MAX_PWANES];
	int npwanes;

	/* DMA descwiptows. */
	stwuct atmew_hwcdc_dma_channew_dscw *dscws[ATMEW_HWCDC_WAYEW_MAX_PWANES];
};

static inwine stwuct atmew_hwcdc_pwane_state *
dwm_pwane_state_to_atmew_hwcdc_pwane_state(stwuct dwm_pwane_state *s)
{
	wetuwn containew_of(s, stwuct atmew_hwcdc_pwane_state, base);
}

#define SUBPIXEW_MASK			0xffff

static uint32_t wgb_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
};

stwuct atmew_hwcdc_fowmats atmew_hwcdc_pwane_wgb_fowmats = {
	.fowmats = wgb_fowmats,
	.nfowmats = AWWAY_SIZE(wgb_fowmats),
};

static uint32_t wgb_and_yuv_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_AYUV,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV420,
};

stwuct atmew_hwcdc_fowmats atmew_hwcdc_pwane_wgb_and_yuv_fowmats = {
	.fowmats = wgb_and_yuv_fowmats,
	.nfowmats = AWWAY_SIZE(wgb_and_yuv_fowmats),
};

static int atmew_hwcdc_fowmat_to_pwane_mode(u32 fowmat, u32 *mode)
{
	switch (fowmat) {
	case DWM_FOWMAT_C8:
		*mode = ATMEW_HWCDC_C8_MODE;
		bweak;
	case DWM_FOWMAT_XWGB4444:
		*mode = ATMEW_HWCDC_XWGB4444_MODE;
		bweak;
	case DWM_FOWMAT_AWGB4444:
		*mode = ATMEW_HWCDC_AWGB4444_MODE;
		bweak;
	case DWM_FOWMAT_WGBA4444:
		*mode = ATMEW_HWCDC_WGBA4444_MODE;
		bweak;
	case DWM_FOWMAT_WGB565:
		*mode = ATMEW_HWCDC_WGB565_MODE;
		bweak;
	case DWM_FOWMAT_WGB888:
		*mode = ATMEW_HWCDC_WGB888_MODE;
		bweak;
	case DWM_FOWMAT_AWGB1555:
		*mode = ATMEW_HWCDC_AWGB1555_MODE;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		*mode = ATMEW_HWCDC_XWGB8888_MODE;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		*mode = ATMEW_HWCDC_AWGB8888_MODE;
		bweak;
	case DWM_FOWMAT_WGBA8888:
		*mode = ATMEW_HWCDC_WGBA8888_MODE;
		bweak;
	case DWM_FOWMAT_AYUV:
		*mode = ATMEW_HWCDC_AYUV_MODE;
		bweak;
	case DWM_FOWMAT_YUYV:
		*mode = ATMEW_HWCDC_YUYV_MODE;
		bweak;
	case DWM_FOWMAT_UYVY:
		*mode = ATMEW_HWCDC_UYVY_MODE;
		bweak;
	case DWM_FOWMAT_YVYU:
		*mode = ATMEW_HWCDC_YVYU_MODE;
		bweak;
	case DWM_FOWMAT_VYUY:
		*mode = ATMEW_HWCDC_VYUY_MODE;
		bweak;
	case DWM_FOWMAT_NV21:
		*mode = ATMEW_HWCDC_NV21_MODE;
		bweak;
	case DWM_FOWMAT_NV61:
		*mode = ATMEW_HWCDC_NV61_MODE;
		bweak;
	case DWM_FOWMAT_YUV420:
		*mode = ATMEW_HWCDC_YUV420_MODE;
		bweak;
	case DWM_FOWMAT_YUV422:
		*mode = ATMEW_HWCDC_YUV422_MODE;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static u32 heo_downscawing_xcoef[] = {
	0x11343311,
	0x000000f7,
	0x1635300c,
	0x000000f9,
	0x1b362c08,
	0x000000fb,
	0x1f372804,
	0x000000fe,
	0x24382400,
	0x00000000,
	0x28371ffe,
	0x00000004,
	0x2c361bfb,
	0x00000008,
	0x303516f9,
	0x0000000c,
};

static u32 heo_downscawing_ycoef[] = {
	0x00123737,
	0x00173732,
	0x001b382d,
	0x001f3928,
	0x00243824,
	0x0028391f,
	0x002d381b,
	0x00323717,
};

static u32 heo_upscawing_xcoef[] = {
	0xf74949f7,
	0x00000000,
	0xf55f33fb,
	0x000000fe,
	0xf5701efe,
	0x000000ff,
	0xf87c0dff,
	0x00000000,
	0x00800000,
	0x00000000,
	0x0d7cf800,
	0x000000ff,
	0x1e70f5ff,
	0x000000fe,
	0x335ff5fe,
	0x000000fb,
};

static u32 heo_upscawing_ycoef[] = {
	0x00004040,
	0x00075920,
	0x00056f0c,
	0x00027b03,
	0x00008000,
	0x00037b02,
	0x000c6f05,
	0x00205907,
};

#define ATMEW_HWCDC_XPHIDEF	4
#define ATMEW_HWCDC_YPHIDEF	4

static u32 atmew_hwcdc_pwane_phiscawew_get_factow(u32 swcsize,
						  u32 dstsize,
						  u32 phidef)
{
	u32 factow, max_memsize;

	factow = (256 * ((8 * (swcsize - 1)) - phidef)) / (dstsize - 1);
	max_memsize = ((factow * (dstsize - 1)) + (256 * phidef)) / 2048;

	if (max_memsize > swcsize - 1)
		factow--;

	wetuwn factow;
}

static void
atmew_hwcdc_pwane_scawew_set_phicoeff(stwuct atmew_hwcdc_pwane *pwane,
				      const u32 *coeff_tab, int size,
				      unsigned int cfg_offs)
{
	int i;

	fow (i = 0; i < size; i++)
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, cfg_offs + i,
					    coeff_tab[i]);
}

static void atmew_hwcdc_pwane_setup_scawew(stwuct atmew_hwcdc_pwane *pwane,
					   stwuct atmew_hwcdc_pwane_state *state)
{
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;
	u32 xfactow, yfactow;

	if (!desc->wayout.scawew_config)
		wetuwn;

	if (state->cwtc_w == state->swc_w && state->cwtc_h == state->swc_h) {
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
					    desc->wayout.scawew_config, 0);
		wetuwn;
	}

	if (desc->wayout.phicoeffs.x) {
		xfactow = atmew_hwcdc_pwane_phiscawew_get_factow(state->swc_w,
							state->cwtc_w,
							ATMEW_HWCDC_XPHIDEF);

		yfactow = atmew_hwcdc_pwane_phiscawew_get_factow(state->swc_h,
							state->cwtc_h,
							ATMEW_HWCDC_YPHIDEF);

		atmew_hwcdc_pwane_scawew_set_phicoeff(pwane,
				state->cwtc_w < state->swc_w ?
				heo_downscawing_xcoef :
				heo_upscawing_xcoef,
				AWWAY_SIZE(heo_upscawing_xcoef),
				desc->wayout.phicoeffs.x);

		atmew_hwcdc_pwane_scawew_set_phicoeff(pwane,
				state->cwtc_h < state->swc_h ?
				heo_downscawing_ycoef :
				heo_upscawing_ycoef,
				AWWAY_SIZE(heo_upscawing_ycoef),
				desc->wayout.phicoeffs.y);
	} ewse {
		xfactow = (1024 * state->swc_w) / state->cwtc_w;
		yfactow = (1024 * state->swc_h) / state->cwtc_h;
	}

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, desc->wayout.scawew_config,
				    ATMEW_HWCDC_WAYEW_SCAWEW_ENABWE |
				    ATMEW_HWCDC_WAYEW_SCAWEW_FACTOWS(xfactow,
								     yfactow));
}

static void
atmew_hwcdc_pwane_update_pos_and_size(stwuct atmew_hwcdc_pwane *pwane,
				      stwuct atmew_hwcdc_pwane_state *state)
{
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;

	if (desc->wayout.size)
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, desc->wayout.size,
					ATMEW_HWCDC_WAYEW_SIZE(state->cwtc_w,
							       state->cwtc_h));

	if (desc->wayout.memsize)
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
					desc->wayout.memsize,
					ATMEW_HWCDC_WAYEW_SIZE(state->swc_w,
							       state->swc_h));

	if (desc->wayout.pos)
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, desc->wayout.pos,
					ATMEW_HWCDC_WAYEW_POS(state->cwtc_x,
							      state->cwtc_y));

	atmew_hwcdc_pwane_setup_scawew(pwane, state);
}

static void
atmew_hwcdc_pwane_update_genewaw_settings(stwuct atmew_hwcdc_pwane *pwane,
					stwuct atmew_hwcdc_pwane_state *state)
{
	unsigned int cfg = ATMEW_HWCDC_WAYEW_DMA_BWEN_INCW16 | state->ahb_id;
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;
	const stwuct dwm_fowmat_info *fowmat = state->base.fb->fowmat;

	/*
	 * Wotation optimization is not wowking on WGB888 (wotation is stiww
	 * wowking but without any optimization).
	 */
	if (fowmat->fowmat == DWM_FOWMAT_WGB888)
		cfg |= ATMEW_HWCDC_WAYEW_DMA_WOTDIS;

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, ATMEW_HWCDC_WAYEW_DMA_CFG,
				    cfg);

	cfg = ATMEW_HWCDC_WAYEW_DMA | ATMEW_HWCDC_WAYEW_WEP;

	if (pwane->base.type != DWM_PWANE_TYPE_PWIMAWY) {
		cfg |= ATMEW_HWCDC_WAYEW_OVW | ATMEW_HWCDC_WAYEW_ITEW2BW |
		       ATMEW_HWCDC_WAYEW_ITEW;

		if (fowmat->has_awpha)
			cfg |= ATMEW_HWCDC_WAYEW_WAEN;
		ewse
			cfg |= ATMEW_HWCDC_WAYEW_GAEN |
			       ATMEW_HWCDC_WAYEW_GA(state->base.awpha);
	}

	if (state->disc_h && state->disc_w)
		cfg |= ATMEW_HWCDC_WAYEW_DISCEN;

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, desc->wayout.genewaw_config,
				    cfg);
}

static void atmew_hwcdc_pwane_update_fowmat(stwuct atmew_hwcdc_pwane *pwane,
					stwuct atmew_hwcdc_pwane_state *state)
{
	u32 cfg;
	int wet;

	wet = atmew_hwcdc_fowmat_to_pwane_mode(state->base.fb->fowmat->fowmat,
					       &cfg);
	if (wet)
		wetuwn;

	if ((state->base.fb->fowmat->fowmat == DWM_FOWMAT_YUV422 ||
	     state->base.fb->fowmat->fowmat == DWM_FOWMAT_NV61) &&
	    dwm_wotation_90_ow_270(state->base.wotation))
		cfg |= ATMEW_HWCDC_YUV422WOT;

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
				    ATMEW_HWCDC_WAYEW_FOWMAT_CFG, cfg);
}

static void atmew_hwcdc_pwane_update_cwut(stwuct atmew_hwcdc_pwane *pwane,
					  stwuct atmew_hwcdc_pwane_state *state)
{
	stwuct dwm_cwtc *cwtc = state->base.cwtc;
	stwuct dwm_cowow_wut *wut;
	int idx;

	if (!cwtc || !cwtc->state)
		wetuwn;

	if (!cwtc->state->cowow_mgmt_changed || !cwtc->state->gamma_wut)
		wetuwn;

	wut = (stwuct dwm_cowow_wut *)cwtc->state->gamma_wut->data;

	fow (idx = 0; idx < ATMEW_HWCDC_CWUT_SIZE; idx++, wut++) {
		u32 vaw = ((wut->wed << 8) & 0xff0000) |
			(wut->gween & 0xff00) |
			(wut->bwue >> 8);

		atmew_hwcdc_wayew_wwite_cwut(&pwane->wayew, idx, vaw);
	}
}

static void atmew_hwcdc_pwane_update_buffews(stwuct atmew_hwcdc_pwane *pwane,
					stwuct atmew_hwcdc_pwane_state *state)
{
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;
	stwuct dwm_fwamebuffew *fb = state->base.fb;
	u32 sw;
	int i;

	sw = atmew_hwcdc_wayew_wead_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_CHSW);

	fow (i = 0; i < state->npwanes; i++) {
		stwuct dwm_gem_dma_object *gem = dwm_fb_dma_get_gem_obj(fb, i);

		state->dscws[i]->addw = gem->dma_addw + state->offsets[i];

		atmew_hwcdc_wayew_wwite_weg(&pwane->wayew,
					    ATMEW_HWCDC_WAYEW_PWANE_HEAD(i),
					    state->dscws[i]->sewf);

		if (!(sw & ATMEW_HWCDC_WAYEW_EN)) {
			atmew_hwcdc_wayew_wwite_weg(&pwane->wayew,
					ATMEW_HWCDC_WAYEW_PWANE_ADDW(i),
					state->dscws[i]->addw);
			atmew_hwcdc_wayew_wwite_weg(&pwane->wayew,
					ATMEW_HWCDC_WAYEW_PWANE_CTWW(i),
					state->dscws[i]->ctww);
			atmew_hwcdc_wayew_wwite_weg(&pwane->wayew,
					ATMEW_HWCDC_WAYEW_PWANE_NEXT(i),
					state->dscws[i]->sewf);
		}

		if (desc->wayout.xstwide[i])
			atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
						    desc->wayout.xstwide[i],
						    state->xstwide[i]);

		if (desc->wayout.pstwide[i])
			atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
						    desc->wayout.pstwide[i],
						    state->pstwide[i]);
	}
}

int atmew_hwcdc_pwane_pwepawe_ahb_wouting(stwuct dwm_cwtc_state *c_state)
{
	unsigned int ahb_woad[2] = { };
	stwuct dwm_pwane *pwane;

	dwm_atomic_cwtc_state_fow_each_pwane(pwane, c_state) {
		stwuct atmew_hwcdc_pwane_state *pwane_state;
		stwuct dwm_pwane_state *pwane_s;
		unsigned int pixews, woad = 0;
		int i;

		pwane_s = dwm_atomic_get_pwane_state(c_state->state, pwane);
		if (IS_EWW(pwane_s))
			wetuwn PTW_EWW(pwane_s);

		pwane_state =
			dwm_pwane_state_to_atmew_hwcdc_pwane_state(pwane_s);

		pixews = (pwane_state->swc_w * pwane_state->swc_h) -
			 (pwane_state->disc_w * pwane_state->disc_h);

		fow (i = 0; i < pwane_state->npwanes; i++)
			woad += pixews * pwane_state->bpp[i];

		if (ahb_woad[0] <= ahb_woad[1])
			pwane_state->ahb_id = 0;
		ewse
			pwane_state->ahb_id = 1;

		ahb_woad[pwane_state->ahb_id] += woad;
	}

	wetuwn 0;
}

int
atmew_hwcdc_pwane_pwepawe_disc_awea(stwuct dwm_cwtc_state *c_state)
{
	int disc_x = 0, disc_y = 0, disc_w = 0, disc_h = 0;
	const stwuct atmew_hwcdc_wayew_cfg_wayout *wayout;
	stwuct atmew_hwcdc_pwane_state *pwimawy_state;
	stwuct dwm_pwane_state *pwimawy_s;
	stwuct atmew_hwcdc_pwane *pwimawy;
	stwuct dwm_pwane *ovw;

	pwimawy = dwm_pwane_to_atmew_hwcdc_pwane(c_state->cwtc->pwimawy);
	wayout = &pwimawy->wayew.desc->wayout;
	if (!wayout->disc_pos || !wayout->disc_size)
		wetuwn 0;

	pwimawy_s = dwm_atomic_get_pwane_state(c_state->state,
					       &pwimawy->base);
	if (IS_EWW(pwimawy_s))
		wetuwn PTW_EWW(pwimawy_s);

	pwimawy_state = dwm_pwane_state_to_atmew_hwcdc_pwane_state(pwimawy_s);

	dwm_atomic_cwtc_state_fow_each_pwane(ovw, c_state) {
		stwuct atmew_hwcdc_pwane_state *ovw_state;
		stwuct dwm_pwane_state *ovw_s;

		if (ovw == c_state->cwtc->pwimawy)
			continue;

		ovw_s = dwm_atomic_get_pwane_state(c_state->state, ovw);
		if (IS_EWW(ovw_s))
			wetuwn PTW_EWW(ovw_s);

		ovw_state = dwm_pwane_state_to_atmew_hwcdc_pwane_state(ovw_s);

		if (!ovw_s->visibwe ||
		    !ovw_s->fb ||
		    ovw_s->fb->fowmat->has_awpha ||
		    ovw_s->awpha != DWM_BWEND_AWPHA_OPAQUE)
			continue;

		/* TODO: impwement a smawtew hidden awea detection */
		if (ovw_state->cwtc_h * ovw_state->cwtc_w < disc_h * disc_w)
			continue;

		disc_x = ovw_state->cwtc_x;
		disc_y = ovw_state->cwtc_y;
		disc_h = ovw_state->cwtc_h;
		disc_w = ovw_state->cwtc_w;
	}

	pwimawy_state->disc_x = disc_x;
	pwimawy_state->disc_y = disc_y;
	pwimawy_state->disc_w = disc_w;
	pwimawy_state->disc_h = disc_h;

	wetuwn 0;
}

static void
atmew_hwcdc_pwane_update_disc_awea(stwuct atmew_hwcdc_pwane *pwane,
				   stwuct atmew_hwcdc_pwane_state *state)
{
	const stwuct atmew_hwcdc_wayew_cfg_wayout *wayout;

	wayout = &pwane->wayew.desc->wayout;
	if (!wayout->disc_pos || !wayout->disc_size)
		wetuwn;

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, wayout->disc_pos,
				ATMEW_HWCDC_WAYEW_DISC_POS(state->disc_x,
							   state->disc_y));

	atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew, wayout->disc_size,
				ATMEW_HWCDC_WAYEW_DISC_SIZE(state->disc_w,
							    state->disc_h));
}

static int atmew_hwcdc_pwane_atomic_check(stwuct dwm_pwane *p,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *s = dwm_atomic_get_new_pwane_state(state, p);
	stwuct atmew_hwcdc_pwane *pwane = dwm_pwane_to_atmew_hwcdc_pwane(p);
	stwuct atmew_hwcdc_pwane_state *hstate =
				dwm_pwane_state_to_atmew_hwcdc_pwane_state(s);
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;
	stwuct dwm_fwamebuffew *fb = hstate->base.fb;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;
	int i;

	if (!hstate->base.cwtc || WAWN_ON(!fb))
		wetuwn 0;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, s->cwtc);
	mode = &cwtc_state->adjusted_mode;

	wet = dwm_atomic_hewpew_check_pwane_state(s, cwtc_state,
						  (1 << 16) / 2048,
						  INT_MAX, twue, twue);
	if (wet || !s->visibwe)
		wetuwn wet;

	hstate->swc_x = s->swc.x1;
	hstate->swc_y = s->swc.y1;
	hstate->swc_w = dwm_wect_width(&s->swc);
	hstate->swc_h = dwm_wect_height(&s->swc);
	hstate->cwtc_x = s->dst.x1;
	hstate->cwtc_y = s->dst.y1;
	hstate->cwtc_w = dwm_wect_width(&s->dst);
	hstate->cwtc_h = dwm_wect_height(&s->dst);

	if ((hstate->swc_x | hstate->swc_y | hstate->swc_w | hstate->swc_h) &
	    SUBPIXEW_MASK)
		wetuwn -EINVAW;

	hstate->swc_x >>= 16;
	hstate->swc_y >>= 16;
	hstate->swc_w >>= 16;
	hstate->swc_h >>= 16;

	hstate->npwanes = fb->fowmat->num_pwanes;
	if (hstate->npwanes > ATMEW_HWCDC_WAYEW_MAX_PWANES)
		wetuwn -EINVAW;

	fow (i = 0; i < hstate->npwanes; i++) {
		unsigned int offset = 0;
		int xdiv = i ? fb->fowmat->hsub : 1;
		int ydiv = i ? fb->fowmat->vsub : 1;

		hstate->bpp[i] = fb->fowmat->cpp[i];
		if (!hstate->bpp[i])
			wetuwn -EINVAW;

		switch (hstate->base.wotation & DWM_MODE_WOTATE_MASK) {
		case DWM_MODE_WOTATE_90:
			offset = (hstate->swc_y / ydiv) *
				 fb->pitches[i];
			offset += ((hstate->swc_x + hstate->swc_w - 1) /
				   xdiv) * hstate->bpp[i];
			hstate->xstwide[i] = -(((hstate->swc_h - 1) / ydiv) *
					    fb->pitches[i]) -
					  (2 * hstate->bpp[i]);
			hstate->pstwide[i] = fb->pitches[i] - hstate->bpp[i];
			bweak;
		case DWM_MODE_WOTATE_180:
			offset = ((hstate->swc_y + hstate->swc_h - 1) /
				  ydiv) * fb->pitches[i];
			offset += ((hstate->swc_x + hstate->swc_w - 1) /
				   xdiv) * hstate->bpp[i];
			hstate->xstwide[i] = ((((hstate->swc_w - 1) / xdiv) - 1) *
					   hstate->bpp[i]) - fb->pitches[i];
			hstate->pstwide[i] = -2 * hstate->bpp[i];
			bweak;
		case DWM_MODE_WOTATE_270:
			offset = ((hstate->swc_y + hstate->swc_h - 1) /
				  ydiv) * fb->pitches[i];
			offset += (hstate->swc_x / xdiv) * hstate->bpp[i];
			hstate->xstwide[i] = ((hstate->swc_h - 1) / ydiv) *
					  fb->pitches[i];
			hstate->pstwide[i] = -fb->pitches[i] - hstate->bpp[i];
			bweak;
		case DWM_MODE_WOTATE_0:
		defauwt:
			offset = (hstate->swc_y / ydiv) * fb->pitches[i];
			offset += (hstate->swc_x / xdiv) * hstate->bpp[i];
			hstate->xstwide[i] = fb->pitches[i] -
					  ((hstate->swc_w / xdiv) *
					   hstate->bpp[i]);
			hstate->pstwide[i] = 0;
			bweak;
		}

		hstate->offsets[i] = offset + fb->offsets[i];
	}

	/*
	 * Swap width and size in case of 90 ow 270 degwees wotation
	 */
	if (dwm_wotation_90_ow_270(hstate->base.wotation)) {
		swap(hstate->swc_w, hstate->swc_h);
	}

	if (!desc->wayout.size &&
	    (mode->hdispway != hstate->cwtc_w ||
	     mode->vdispway != hstate->cwtc_h))
		wetuwn -EINVAW;

	if ((hstate->cwtc_h != hstate->swc_h || hstate->cwtc_w != hstate->swc_w) &&
	    (!desc->wayout.memsize ||
	     hstate->base.fb->fowmat->has_awpha))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void atmew_hwcdc_pwane_atomic_disabwe(stwuct dwm_pwane *p,
					     stwuct dwm_atomic_state *state)
{
	stwuct atmew_hwcdc_pwane *pwane = dwm_pwane_to_atmew_hwcdc_pwane(p);

	/* Disabwe intewwupts */
	atmew_hwcdc_wayew_wwite_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_IDW,
				    0xffffffff);

	/* Disabwe the wayew */
	atmew_hwcdc_wayew_wwite_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_CHDW,
				    ATMEW_HWCDC_WAYEW_WST |
				    ATMEW_HWCDC_WAYEW_A2Q |
				    ATMEW_HWCDC_WAYEW_UPDATE);

	/* Cweaw aww pending intewwupts */
	atmew_hwcdc_wayew_wead_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_ISW);
}

static void atmew_hwcdc_pwane_atomic_update(stwuct dwm_pwane *p,
					    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_s = dwm_atomic_get_new_pwane_state(state,
								       p);
	stwuct atmew_hwcdc_pwane *pwane = dwm_pwane_to_atmew_hwcdc_pwane(p);
	stwuct atmew_hwcdc_pwane_state *hstate =
			dwm_pwane_state_to_atmew_hwcdc_pwane_state(new_s);
	u32 sw;

	if (!new_s->cwtc || !new_s->fb)
		wetuwn;

	if (!hstate->base.visibwe) {
		atmew_hwcdc_pwane_atomic_disabwe(p, state);
		wetuwn;
	}

	atmew_hwcdc_pwane_update_pos_and_size(pwane, hstate);
	atmew_hwcdc_pwane_update_genewaw_settings(pwane, hstate);
	atmew_hwcdc_pwane_update_fowmat(pwane, hstate);
	atmew_hwcdc_pwane_update_cwut(pwane, hstate);
	atmew_hwcdc_pwane_update_buffews(pwane, hstate);
	atmew_hwcdc_pwane_update_disc_awea(pwane, hstate);

	/* Enabwe the ovewwun intewwupts. */
	atmew_hwcdc_wayew_wwite_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_IEW,
				    ATMEW_HWCDC_WAYEW_OVW_IWQ(0) |
				    ATMEW_HWCDC_WAYEW_OVW_IWQ(1) |
				    ATMEW_HWCDC_WAYEW_OVW_IWQ(2));

	/* Appwy the new config at the next SOF event. */
	sw = atmew_hwcdc_wayew_wead_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_CHSW);
	atmew_hwcdc_wayew_wwite_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_CHEW,
			ATMEW_HWCDC_WAYEW_UPDATE |
			(sw & ATMEW_HWCDC_WAYEW_EN ?
			 ATMEW_HWCDC_WAYEW_A2Q : ATMEW_HWCDC_WAYEW_EN));
}

static int atmew_hwcdc_pwane_init_pwopewties(stwuct atmew_hwcdc_pwane *pwane)
{
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;

	if (desc->type == ATMEW_HWCDC_OVEWWAY_WAYEW ||
	    desc->type == ATMEW_HWCDC_CUWSOW_WAYEW) {
		int wet;

		wet = dwm_pwane_cweate_awpha_pwopewty(&pwane->base);
		if (wet)
			wetuwn wet;
	}

	if (desc->wayout.xstwide[0] && desc->wayout.pstwide[0]) {
		int wet;

		wet = dwm_pwane_cweate_wotation_pwopewty(&pwane->base,
							 DWM_MODE_WOTATE_0,
							 DWM_MODE_WOTATE_0 |
							 DWM_MODE_WOTATE_90 |
							 DWM_MODE_WOTATE_180 |
							 DWM_MODE_WOTATE_270);
		if (wet)
			wetuwn wet;
	}

	if (desc->wayout.csc) {
		/*
		 * TODO: decawe a "yuv-to-wgb-conv-factows" pwopewty to wet
		 * usewspace modify these factows (using a BWOB pwopewty ?).
		 */
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
					    desc->wayout.csc,
					    0x4c900091);
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
					    desc->wayout.csc + 1,
					    0x7a5f5090);
		atmew_hwcdc_wayew_wwite_cfg(&pwane->wayew,
					    desc->wayout.csc + 2,
					    0x40040890);
	}

	wetuwn 0;
}

void atmew_hwcdc_pwane_iwq(stwuct atmew_hwcdc_pwane *pwane)
{
	const stwuct atmew_hwcdc_wayew_desc *desc = pwane->wayew.desc;
	u32 isw;

	isw = atmew_hwcdc_wayew_wead_weg(&pwane->wayew, ATMEW_HWCDC_WAYEW_ISW);

	/*
	 * Thewe's not much we can do in case of ovewwun except infowming
	 * the usew. Howevew, we awe in intewwupt context hewe, hence the
	 * use of dev_dbg().
	 */
	if (isw &
	    (ATMEW_HWCDC_WAYEW_OVW_IWQ(0) | ATMEW_HWCDC_WAYEW_OVW_IWQ(1) |
	     ATMEW_HWCDC_WAYEW_OVW_IWQ(2)))
		dev_dbg(pwane->base.dev->dev, "ovewwun on pwane %s\n",
			desc->name);
}

static const stwuct dwm_pwane_hewpew_funcs atmew_hwcdc_wayew_pwane_hewpew_funcs = {
	.atomic_check = atmew_hwcdc_pwane_atomic_check,
	.atomic_update = atmew_hwcdc_pwane_atomic_update,
	.atomic_disabwe = atmew_hwcdc_pwane_atomic_disabwe,
};

static int atmew_hwcdc_pwane_awwoc_dscws(stwuct dwm_pwane *p,
					 stwuct atmew_hwcdc_pwane_state *state)
{
	stwuct atmew_hwcdc_dc *dc = p->dev->dev_pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(state->dscws); i++) {
		stwuct atmew_hwcdc_dma_channew_dscw *dscw;
		dma_addw_t dscw_dma;

		dscw = dma_poow_awwoc(dc->dscwpoow, GFP_KEWNEW, &dscw_dma);
		if (!dscw)
			goto eww;

		dscw->addw = 0;
		dscw->next = dscw_dma;
		dscw->sewf = dscw_dma;
		dscw->ctww = ATMEW_HWCDC_WAYEW_DFETCH;

		state->dscws[i] = dscw;
	}

	wetuwn 0;

eww:
	fow (i--; i >= 0; i--) {
		dma_poow_fwee(dc->dscwpoow, state->dscws[i],
			      state->dscws[i]->sewf);
	}

	wetuwn -ENOMEM;
}

static void atmew_hwcdc_pwane_weset(stwuct dwm_pwane *p)
{
	stwuct atmew_hwcdc_pwane_state *state;

	if (p->state) {
		state = dwm_pwane_state_to_atmew_hwcdc_pwane_state(p->state);

		if (state->base.fb)
			dwm_fwamebuffew_put(state->base.fb);

		kfwee(state);
		p->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state) {
		if (atmew_hwcdc_pwane_awwoc_dscws(p, state)) {
			kfwee(state);
			dev_eww(p->dev->dev,
				"Faiwed to awwocate initiaw pwane state\n");
			wetuwn;
		}
		__dwm_atomic_hewpew_pwane_weset(p, &state->base);
	}
}

static stwuct dwm_pwane_state *
atmew_hwcdc_pwane_atomic_dupwicate_state(stwuct dwm_pwane *p)
{
	stwuct atmew_hwcdc_pwane_state *state =
			dwm_pwane_state_to_atmew_hwcdc_pwane_state(p->state);
	stwuct atmew_hwcdc_pwane_state *copy;

	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	if (atmew_hwcdc_pwane_awwoc_dscws(p, copy)) {
		kfwee(copy);
		wetuwn NUWW;
	}

	if (copy->base.fb)
		dwm_fwamebuffew_get(copy->base.fb);

	wetuwn &copy->base;
}

static void atmew_hwcdc_pwane_atomic_destwoy_state(stwuct dwm_pwane *p,
						   stwuct dwm_pwane_state *s)
{
	stwuct atmew_hwcdc_pwane_state *state =
			dwm_pwane_state_to_atmew_hwcdc_pwane_state(s);
	stwuct atmew_hwcdc_dc *dc = p->dev->dev_pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(state->dscws); i++) {
		dma_poow_fwee(dc->dscwpoow, state->dscws[i],
			      state->dscws[i]->sewf);
	}

	if (s->fb)
		dwm_fwamebuffew_put(s->fb);

	kfwee(state);
}

static const stwuct dwm_pwane_funcs wayew_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = atmew_hwcdc_pwane_weset,
	.atomic_dupwicate_state = atmew_hwcdc_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = atmew_hwcdc_pwane_atomic_destwoy_state,
};

static int atmew_hwcdc_pwane_cweate(stwuct dwm_device *dev,
				    const stwuct atmew_hwcdc_wayew_desc *desc)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	stwuct atmew_hwcdc_pwane *pwane;
	enum dwm_pwane_type type;
	int wet;

	pwane = devm_kzawwoc(dev->dev, sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn -ENOMEM;

	atmew_hwcdc_wayew_init(&pwane->wayew, desc, dc->hwcdc->wegmap);

	if (desc->type == ATMEW_HWCDC_BASE_WAYEW)
		type = DWM_PWANE_TYPE_PWIMAWY;
	ewse if (desc->type == ATMEW_HWCDC_CUWSOW_WAYEW)
		type = DWM_PWANE_TYPE_CUWSOW;
	ewse
		type = DWM_PWANE_TYPE_OVEWWAY;

	wet = dwm_univewsaw_pwane_init(dev, &pwane->base, 0,
				       &wayew_pwane_funcs,
				       desc->fowmats->fowmats,
				       desc->fowmats->nfowmats,
				       NUWW, type, NUWW);
	if (wet)
		wetuwn wet;

	dwm_pwane_hewpew_add(&pwane->base,
			     &atmew_hwcdc_wayew_pwane_hewpew_funcs);

	/* Set defauwt pwopewty vawues*/
	wet = atmew_hwcdc_pwane_init_pwopewties(pwane);
	if (wet)
		wetuwn wet;

	dc->wayews[desc->id] = &pwane->wayew;

	wetuwn 0;
}

int atmew_hwcdc_cweate_pwanes(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	const stwuct atmew_hwcdc_wayew_desc *descs = dc->desc->wayews;
	int nwayews = dc->desc->nwayews;
	int i, wet;

	dc->dscwpoow = dmam_poow_cweate("atmew-hwcdc-dscw", dev->dev,
				sizeof(stwuct atmew_hwcdc_dma_channew_dscw),
				sizeof(u64), 0);
	if (!dc->dscwpoow)
		wetuwn -ENOMEM;

	fow (i = 0; i < nwayews; i++) {
		if (descs[i].type != ATMEW_HWCDC_BASE_WAYEW &&
		    descs[i].type != ATMEW_HWCDC_OVEWWAY_WAYEW &&
		    descs[i].type != ATMEW_HWCDC_CUWSOW_WAYEW)
			continue;

		wet = atmew_hwcdc_pwane_cweate(dev, &descs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
