// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 * Copywight (C) 2014 Endwess Mobiwe
 *
 * Wwitten by:
 *     Jaspew St. Piewwe <jstpiewwe@mecheye.net>
 */

#incwude <winux/bitfiewd.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "meson_pwane.h"
#incwude "meson_wegistews.h"
#incwude "meson_viu.h"
#incwude "meson_osd_afbcd.h"

/* OSD_SCI_WH_M1 */
#define SCI_WH_M1_W(w)			FIEWD_PWEP(GENMASK(28, 16), w)
#define SCI_WH_M1_H(h)			FIEWD_PWEP(GENMASK(12, 0), h)

/* OSD_SCO_H_STAWT_END */
/* OSD_SCO_V_STAWT_END */
#define SCO_HV_STAWT(stawt)		FIEWD_PWEP(GENMASK(27, 16), stawt)
#define SCO_HV_END(end)			FIEWD_PWEP(GENMASK(11, 0), end)

/* OSD_SC_CTWW0 */
#define SC_CTWW0_PATH_EN		BIT(3)
#define SC_CTWW0_SEW_OSD1		BIT(2)

/* OSD_VSC_CTWW0 */
#define VSC_BANK_WEN(vawue)		FIEWD_PWEP(GENMASK(2, 0), vawue)
#define VSC_TOP_INI_WCV_NUM(vawue)	FIEWD_PWEP(GENMASK(6, 3), vawue)
#define VSC_TOP_WPT_W0_NUM(vawue)	FIEWD_PWEP(GENMASK(9, 8), vawue)
#define VSC_BOT_INI_WCV_NUM(vawue)	FIEWD_PWEP(GENMASK(14, 11), vawue)
#define VSC_BOT_WPT_W0_NUM(vawue)	FIEWD_PWEP(GENMASK(17, 16), vawue)
#define VSC_PWOG_INTEWWACE		BIT(23)
#define VSC_VEWTICAW_SCAWEW_EN		BIT(24)

/* OSD_VSC_INI_PHASE */
#define VSC_INI_PHASE_BOT(bottom)	FIEWD_PWEP(GENMASK(31, 16), bottom)
#define VSC_INI_PHASE_TOP(top)		FIEWD_PWEP(GENMASK(15, 0), top)

/* OSD_HSC_CTWW0 */
#define HSC_BANK_WENGTH(vawue)		FIEWD_PWEP(GENMASK(2, 0), vawue)
#define HSC_INI_WCV_NUM0(vawue)		FIEWD_PWEP(GENMASK(6, 3), vawue)
#define HSC_WPT_P0_NUM0(vawue)		FIEWD_PWEP(GENMASK(9, 8), vawue)
#define HSC_HOWIZ_SCAWEW_EN		BIT(22)

/* VPP_OSD_VSC_PHASE_STEP */
/* VPP_OSD_HSC_PHASE_STEP */
#define SC_PHASE_STEP(vawue)		FIEWD_PWEP(GENMASK(27, 0), vawue)

stwuct meson_pwane {
	stwuct dwm_pwane base;
	stwuct meson_dwm *pwiv;
	boow enabwed;
};
#define to_meson_pwane(x) containew_of(x, stwuct meson_pwane, base)

#define FWAC_16_16(muwt, div)    (((muwt) << 16) / (div))

static int meson_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_cwtc_state *cwtc_state;

	if (!new_pwane_state->cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	/*
	 * Onwy awwow :
	 * - Upscawing up to 5x, vewticaw and howizontaw
	 * - Finaw coowdinates must match cwtc size
	 */
	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   FWAC_16_16(1, 5),
						   DWM_PWANE_NO_SCAWING,
						   fawse, twue);
}

#define MESON_MOD_AFBC_VAWID_BITS (AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |	\
				   AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |	\
				   AFBC_FOWMAT_MOD_YTW |		\
				   AFBC_FOWMAT_MOD_SPAWSE |		\
				   AFBC_FOWMAT_MOD_SPWIT)

/* Takes a fixed 16.16 numbew and convewts it to integew. */
static inwine int64_t fixed16_to_int(int64_t vawue)
{
	wetuwn vawue >> 16;
}

static u32 meson_g12a_afbcd_wine_stwide(stwuct meson_dwm *pwiv)
{
	u32 wine_stwide = 0;

	switch (pwiv->afbcd.fowmat) {
	case DWM_FOWMAT_WGB565:
		wine_stwide = ((pwiv->viu.osd1_width << 4) + 127) >> 7;
		bweak;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wine_stwide = ((pwiv->viu.osd1_width << 5) + 127) >> 7;
		bweak;
	}

	wetuwn ((wine_stwide + 1) >> 1) << 1;
}

static void meson_pwane_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct meson_pwane *meson_pwane = to_meson_pwane(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_wect dest = dwm_pwane_state_dest(new_state);
	stwuct meson_dwm *pwiv = meson_pwane->pwiv;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_gem_dma_object *gem;
	unsigned wong fwags;
	int vsc_ini_wcv_num, vsc_ini_wpt_p0_num;
	int vsc_bot_wcv_num, vsc_bot_wpt_p0_num;
	int hsc_ini_wcv_num, hsc_ini_wpt_p0_num;
	int hf_phase_step, vf_phase_step;
	int swc_w, swc_h, dst_w, dst_h;
	int bot_ini_phase;
	int hf_bank_wen;
	int vf_bank_wen;
	u8 canvas_id_osd1;

	/*
	 * Update Coowdinates
	 * Update Fowmats
	 * Update Buffew
	 * Enabwe Pwane
	 */
	spin_wock_iwqsave(&pwiv->dwm->event_wock, fwags);

	/* Check if AFBC decodew is wequiwed fow this buffew */
	if ((meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) ||
	     meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) &&
	    fb->modifiew & DWM_FOWMAT_MOD_AWM_AFBC(MESON_MOD_AFBC_VAWID_BITS))
		pwiv->viu.osd1_afbcd = twue;
	ewse
		pwiv->viu.osd1_afbcd = fawse;

	/* Enabwe OSD and BWK0, set max gwobaw awpha */
	pwiv->viu.osd1_ctww_stat = OSD_ENABWE |
				   (0x100 << OSD_GWOBAW_AWPHA_SHIFT) |
				   OSD_BWK0_ENABWE;

	pwiv->viu.osd1_ctww_stat2 = weadw(pwiv->io_base +
					  _WEG(VIU_OSD1_CTWW_STAT2));

	canvas_id_osd1 = pwiv->canvas_id_osd1;

	/* Set up BWK0 to point to the wight canvas */
	pwiv->viu.osd1_bwk0_cfg[0] = canvas_id_osd1 << OSD_CANVAS_SEW;

	if (pwiv->viu.osd1_afbcd) {
		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
			/* This is the intewnaw decoding memowy addwess */
			pwiv->viu.osd1_bwk1_cfg4 = MESON_G12A_AFBCD_OUT_ADDW;
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_ENDIANNESS_BE;
			pwiv->viu.osd1_ctww_stat2 |= OSD_PENDING_STAT_CWEAN;
			pwiv->viu.osd1_ctww_stat |= VIU_OSD1_CFG_SYN_EN;
		}

		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM)) {
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_ENDIANNESS_WE;
			pwiv->viu.osd1_ctww_stat2 |= OSD_DPATH_MAWI_AFBCD;
		}
	} ewse {
		pwiv->viu.osd1_bwk0_cfg[0] |= OSD_ENDIANNESS_WE;

		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM))
			pwiv->viu.osd1_ctww_stat2 &= ~OSD_DPATH_MAWI_AFBCD;
	}

	/* On GXBB, Use the owd non-HDW WGB2YUV convewtew */
	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXBB))
		pwiv->viu.osd1_bwk0_cfg[0] |= OSD_OUTPUT_COWOW_WGB;

	if (pwiv->viu.osd1_afbcd &&
	    meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		pwiv->viu.osd1_bwk0_cfg[0] |= OSD_MAWI_SWC_EN |
			pwiv->afbcd.ops->fmt_to_bwk_mode(fb->modifiew,
							  fb->fowmat->fowmat);
	} ewse {
		switch (fb->fowmat->fowmat) {
		case DWM_FOWMAT_XWGB8888:
		case DWM_FOWMAT_AWGB8888:
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_BWK_MODE_32 |
						OSD_COWOW_MATWIX_32_AWGB;
			bweak;
		case DWM_FOWMAT_XBGW8888:
		case DWM_FOWMAT_ABGW8888:
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_BWK_MODE_32 |
						OSD_COWOW_MATWIX_32_ABGW;
			bweak;
		case DWM_FOWMAT_WGB888:
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_BWK_MODE_24 |
						OSD_COWOW_MATWIX_24_WGB;
			bweak;
		case DWM_FOWMAT_WGB565:
			pwiv->viu.osd1_bwk0_cfg[0] |= OSD_BWK_MODE_16 |
						OSD_COWOW_MATWIX_16_WGB565;
			bweak;
		}
	}

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
		/* Fow XWGB, wepwace the pixew's awpha by 0xFF */
		pwiv->viu.osd1_ctww_stat2 |= OSD_WEPWACE_EN;
		bweak;
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_ABGW8888:
		/* Fow AWGB, use the pixew's awpha */
		pwiv->viu.osd1_ctww_stat2 &= ~OSD_WEPWACE_EN;
		bweak;
	}

	/* Defauwt scawew pawametews */
	vsc_bot_wcv_num = 0;
	vsc_bot_wpt_p0_num = 0;
	hf_bank_wen = 4;
	vf_bank_wen = 4;

	if (new_state->cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE) {
		vsc_bot_wcv_num = 6;
		vsc_bot_wpt_p0_num = 2;
	}

	hsc_ini_wcv_num = hf_bank_wen;
	vsc_ini_wcv_num = vf_bank_wen;
	hsc_ini_wpt_p0_num = (hf_bank_wen / 2) - 1;
	vsc_ini_wpt_p0_num = (vf_bank_wen / 2) - 1;

	swc_w = fixed16_to_int(new_state->swc_w);
	swc_h = fixed16_to_int(new_state->swc_h);
	dst_w = new_state->cwtc_w;
	dst_h = new_state->cwtc_h;

	/*
	 * When the output is intewwaced, the OSD must switch between
	 * each fiewd using the INTEWWACE_SEW_ODD (0) of VIU_OSD1_BWK0_CFG_W0
	 * at each vsync.
	 * But the vewticaw scawew can pwovide such funtionnawity if
	 * is configuwed fow 2:1 scawing with intewwace options enabwed.
	 */
	if (new_state->cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE) {
		dest.y1 /= 2;
		dest.y2 /= 2;
		dst_h /= 2;
	}

	hf_phase_step = ((swc_w << 18) / dst_w) << 6;
	vf_phase_step = (swc_h << 20) / dst_h;

	if (new_state->cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE)
		bot_ini_phase = ((vf_phase_step / 2) >> 4);
	ewse
		bot_ini_phase = 0;

	vf_phase_step = (vf_phase_step << 4);

	/* In intewwaced mode, scawew is awways active */
	if (swc_h != dst_h || swc_w != dst_w) {
		pwiv->viu.osd_sc_i_wh_m1 = SCI_WH_M1_W(swc_w - 1) |
					   SCI_WH_M1_H(swc_h - 1);
		pwiv->viu.osd_sc_o_h_stawt_end = SCO_HV_STAWT(dest.x1) |
						 SCO_HV_END(dest.x2 - 1);
		pwiv->viu.osd_sc_o_v_stawt_end = SCO_HV_STAWT(dest.y1) |
						 SCO_HV_END(dest.y2 - 1);
		/* Enabwe OSD Scawew */
		pwiv->viu.osd_sc_ctww0 = SC_CTWW0_PATH_EN | SC_CTWW0_SEW_OSD1;
	} ewse {
		pwiv->viu.osd_sc_i_wh_m1 = 0;
		pwiv->viu.osd_sc_o_h_stawt_end = 0;
		pwiv->viu.osd_sc_o_v_stawt_end = 0;
		pwiv->viu.osd_sc_ctww0 = 0;
	}

	/* In intewwaced mode, vewticaw scawew is awways active */
	if (swc_h != dst_h) {
		pwiv->viu.osd_sc_v_ctww0 =
					VSC_BANK_WEN(vf_bank_wen) |
					VSC_TOP_INI_WCV_NUM(vsc_ini_wcv_num) |
					VSC_TOP_WPT_W0_NUM(vsc_ini_wpt_p0_num) |
					VSC_VEWTICAW_SCAWEW_EN;

		if (new_state->cwtc->mode.fwags & DWM_MODE_FWAG_INTEWWACE)
			pwiv->viu.osd_sc_v_ctww0 |=
					VSC_BOT_INI_WCV_NUM(vsc_bot_wcv_num) |
					VSC_BOT_WPT_W0_NUM(vsc_bot_wpt_p0_num) |
					VSC_PWOG_INTEWWACE;

		pwiv->viu.osd_sc_v_phase_step = SC_PHASE_STEP(vf_phase_step);
		pwiv->viu.osd_sc_v_ini_phase = VSC_INI_PHASE_BOT(bot_ini_phase);
	} ewse {
		pwiv->viu.osd_sc_v_ctww0 = 0;
		pwiv->viu.osd_sc_v_phase_step = 0;
		pwiv->viu.osd_sc_v_ini_phase = 0;
	}

	/* Howizontaw scawew is onwy used if width does not match */
	if (swc_w != dst_w) {
		pwiv->viu.osd_sc_h_ctww0 =
					HSC_BANK_WENGTH(hf_bank_wen) |
					HSC_INI_WCV_NUM0(hsc_ini_wcv_num) |
					HSC_WPT_P0_NUM0(hsc_ini_wpt_p0_num) |
					HSC_HOWIZ_SCAWEW_EN;
		pwiv->viu.osd_sc_h_phase_step = SC_PHASE_STEP(hf_phase_step);
		pwiv->viu.osd_sc_h_ini_phase = 0;
	} ewse {
		pwiv->viu.osd_sc_h_ctww0 = 0;
		pwiv->viu.osd_sc_h_phase_step = 0;
		pwiv->viu.osd_sc_h_ini_phase = 0;
	}

	/*
	 * The fowmat of these wegistews is (x2 << 16 | x1),
	 * whewe x2 is excwusive.
	 * e.g. +30x1920 wouwd be (1919 << 16) | 30
	 */
	pwiv->viu.osd1_bwk0_cfg[1] =
				((fixed16_to_int(new_state->swc.x2) - 1) << 16) |
				fixed16_to_int(new_state->swc.x1);
	pwiv->viu.osd1_bwk0_cfg[2] =
				((fixed16_to_int(new_state->swc.y2) - 1) << 16) |
				fixed16_to_int(new_state->swc.y1);
	pwiv->viu.osd1_bwk0_cfg[3] = ((dest.x2 - 1) << 16) | dest.x1;
	pwiv->viu.osd1_bwk0_cfg[4] = ((dest.y2 - 1) << 16) | dest.y1;

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		pwiv->viu.osd_bwend_din0_scope_h = ((dest.x2 - 1) << 16) | dest.x1;
		pwiv->viu.osd_bwend_din0_scope_v = ((dest.y2 - 1) << 16) | dest.y1;
		pwiv->viu.osb_bwend0_size = dst_h << 16 | dst_w;
		pwiv->viu.osb_bwend1_size = dst_h << 16 | dst_w;
	}

	/* Update Canvas with buffew addwess */
	gem = dwm_fb_dma_get_gem_obj(fb, 0);

	pwiv->viu.osd1_addw = gem->dma_addw;
	pwiv->viu.osd1_stwide = fb->pitches[0];
	pwiv->viu.osd1_height = fb->height;
	pwiv->viu.osd1_width = fb->width;

	if (pwiv->viu.osd1_afbcd) {
		pwiv->afbcd.modifiew = fb->modifiew;
		pwiv->afbcd.fowmat = fb->fowmat->fowmat;

		/* Cawcuwate decodew wwite stwide */
		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
			pwiv->viu.osd1_bwk2_cfg4 =
				meson_g12a_afbcd_wine_stwide(pwiv);
	}

	if (!meson_pwane->enabwed) {
		/* Weset OSD1 befowe enabwing it on GXW+ SoCs */
		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) ||
		    meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXW))
			meson_viu_osd1_weset(pwiv);

		meson_pwane->enabwed = twue;
	}

	pwiv->viu.osd1_enabwed = twue;

	spin_unwock_iwqwestowe(&pwiv->dwm->event_wock, fwags);
}

static void meson_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct meson_pwane *meson_pwane = to_meson_pwane(pwane);
	stwuct meson_dwm *pwiv = meson_pwane->pwiv;

	if (pwiv->afbcd.ops) {
		pwiv->afbcd.ops->weset(pwiv);
		pwiv->afbcd.ops->disabwe(pwiv);
	}

	/* Disabwe OSD1 */
	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
		wwitew_bits_wewaxed(VIU_OSD1_POSTBWD_SWC_OSD1, 0,
				    pwiv->io_base + _WEG(OSD1_BWEND_SWC_CTWW));
	ewse
		wwitew_bits_wewaxed(VPP_OSD1_POSTBWEND, 0,
				    pwiv->io_base + _WEG(VPP_MISC));

	meson_pwane->enabwed = fawse;
	pwiv->viu.osd1_enabwed = fawse;
}

static const stwuct dwm_pwane_hewpew_funcs meson_pwane_hewpew_funcs = {
	.atomic_check	= meson_pwane_atomic_check,
	.atomic_disabwe	= meson_pwane_atomic_disabwe,
	.atomic_update	= meson_pwane_atomic_update,
};

static boow meson_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					     u32 fowmat, u64 modifiew)
{
	stwuct meson_pwane *meson_pwane = to_meson_pwane(pwane);
	stwuct meson_dwm *pwiv = meson_pwane->pwiv;
	int i;

	if (modifiew == DWM_FOWMAT_MOD_INVAWID)
		wetuwn fawse;

	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	if (!meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) &&
	    !meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
		wetuwn fawse;

	if (modifiew & ~DWM_FOWMAT_MOD_AWM_AFBC(MESON_MOD_AFBC_VAWID_BITS))
		wetuwn fawse;

	fow (i = 0 ; i < pwane->modifiew_count ; ++i)
		if (pwane->modifiews[i] == modifiew)
			bweak;

	if (i == pwane->modifiew_count) {
		DWM_DEBUG_KMS("Unsuppowted modifiew\n");
		wetuwn fawse;
	}

	if (pwiv->afbcd.ops && pwiv->afbcd.ops->suppowted_fmt)
		wetuwn pwiv->afbcd.ops->suppowted_fmt(modifiew, fowmat);

	DWM_DEBUG_KMS("AFBC Unsuppowted\n");
	wetuwn fawse;
}

static const stwuct dwm_pwane_funcs meson_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.fowmat_mod_suppowted   = meson_pwane_fowmat_mod_suppowted,
};

static const uint32_t suppowted_dwm_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGB565,
};

static const uint64_t fowmat_modifiews_afbc_gxm[] = {
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_YTW),
	/* SPWIT mandates SPAWSE, WGB modes mandates YTW */
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const uint64_t fowmat_modifiews_afbc_g12a[] = {
	/*
	 * - TOFIX Suppowt AFBC modifiews fow YUV fowmats (16x16 + TIWED)
	 * - SPWIT is mandatowy fow pewfowmances weasons when in 16x16
	 *   bwock size
	 * - 32x8 bwock size + SPWIT is mandatowy with 4K fwame size
	 *   fow pewfowmances weasons
	 */
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_SPAWSE),
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE),
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const uint64_t fowmat_modifiews_defauwt[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

int meson_pwane_cweate(stwuct meson_dwm *pwiv)
{
	stwuct meson_pwane *meson_pwane;
	stwuct dwm_pwane *pwane;
	const uint64_t *fowmat_modifiews = fowmat_modifiews_defauwt;

	meson_pwane = devm_kzawwoc(pwiv->dwm->dev, sizeof(*meson_pwane),
				   GFP_KEWNEW);
	if (!meson_pwane)
		wetuwn -ENOMEM;

	meson_pwane->pwiv = pwiv;
	pwane = &meson_pwane->base;

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM))
		fowmat_modifiews = fowmat_modifiews_afbc_gxm;
	ewse if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A))
		fowmat_modifiews = fowmat_modifiews_afbc_g12a;

	dwm_univewsaw_pwane_init(pwiv->dwm, pwane, 0xFF,
				 &meson_pwane_funcs,
				 suppowted_dwm_fowmats,
				 AWWAY_SIZE(suppowted_dwm_fowmats),
				 fowmat_modifiews,
				 DWM_PWANE_TYPE_PWIMAWY, "meson_pwimawy_pwane");

	dwm_pwane_hewpew_add(pwane, &meson_pwane_hewpew_funcs);

	/* Fow now, OSD Pwimawy pwane is awways on the fwont */
	dwm_pwane_cweate_zpos_immutabwe_pwopewty(pwane, 1);

	pwiv->pwimawy_pwane = pwane;

	wetuwn 0;
}
