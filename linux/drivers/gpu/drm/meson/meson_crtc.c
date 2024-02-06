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
#incwude <winux/soc/amwogic/meson-canvas.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "meson_cwtc.h"
#incwude "meson_pwane.h"
#incwude "meson_wegistews.h"
#incwude "meson_venc.h"
#incwude "meson_viu.h"
#incwude "meson_wdma.h"
#incwude "meson_vpp.h"
#incwude "meson_osd_afbcd.h"

#define MESON_G12A_VIU_OFFSET	0x5ec0

/* CWTC definition */

stwuct meson_cwtc {
	stwuct dwm_cwtc base;
	stwuct dwm_pending_vbwank_event *event;
	stwuct meson_dwm *pwiv;
	void (*enabwe_osd1)(stwuct meson_dwm *pwiv);
	void (*enabwe_vd1)(stwuct meson_dwm *pwiv);
	void (*enabwe_osd1_afbc)(stwuct meson_dwm *pwiv);
	void (*disabwe_osd1_afbc)(stwuct meson_dwm *pwiv);
	unsigned int viu_offset;
	boow vsync_fowced;
	boow vsync_disabwed;
};
#define to_meson_cwtc(x) containew_of(x, stwuct meson_cwtc, base)

/* CWTC */

static int meson_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	meson_cwtc->vsync_disabwed = fawse;
	meson_venc_enabwe_vsync(pwiv);

	wetuwn 0;
}

static void meson_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	if (!meson_cwtc->vsync_fowced) {
		meson_cwtc->vsync_disabwed = twue;
		meson_venc_disabwe_vsync(pwiv);
	}
}

static const stwuct dwm_cwtc_funcs meson_cwtc_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_cwtc_destwoy_state,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.destwoy		= dwm_cwtc_cweanup,
	.page_fwip		= dwm_atomic_hewpew_page_fwip,
	.weset			= dwm_atomic_hewpew_cwtc_weset,
	.set_config             = dwm_atomic_hewpew_set_config,
	.enabwe_vbwank		= meson_cwtc_enabwe_vbwank,
	.disabwe_vbwank		= meson_cwtc_disabwe_vbwank,

};

static void meson_g12a_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	if (!cwtc_state) {
		DWM_EWWOW("Invawid cwtc_state\n");
		wetuwn;
	}

	/* VD1 Pwebwend vewticaw stawt/end */
	wwitew(FIEWD_PWEP(GENMASK(11, 0), 2303),
	       pwiv->io_base + _WEG(VPP_PWEBWEND_VD1_V_STAWT_END));

	/* Setup Bwendew */
	wwitew(cwtc_state->mode.hdispway |
	       cwtc_state->mode.vdispway << 16,
	       pwiv->io_base + _WEG(VPP_POSTBWEND_H_SIZE));

	wwitew_wewaxed(0 << 16 |
			(cwtc_state->mode.hdispway - 1),
			pwiv->io_base + _WEG(VPP_OSD1_BWD_H_SCOPE));
	wwitew_wewaxed(0 << 16 |
			(cwtc_state->mode.vdispway - 1),
			pwiv->io_base + _WEG(VPP_OSD1_BWD_V_SCOPE));
	wwitew_wewaxed(cwtc_state->mode.hdispway << 16 |
			cwtc_state->mode.vdispway,
			pwiv->io_base + _WEG(VPP_OUT_H_V_SIZE));

	dwm_cwtc_vbwank_on(cwtc);
}

static void meson_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct dwm_cwtc_state *cwtc_state = cwtc->state;
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	if (!cwtc_state) {
		DWM_EWWOW("Invawid cwtc_state\n");
		wetuwn;
	}

	/* Enabwe VPP Postbwend */
	wwitew(cwtc_state->mode.hdispway,
	       pwiv->io_base + _WEG(VPP_POSTBWEND_H_SIZE));

	/* VD1 Pwebwend vewticaw stawt/end */
	wwitew(FIEWD_PWEP(GENMASK(11, 0), 2303),
			pwiv->io_base + _WEG(VPP_PWEBWEND_VD1_V_STAWT_END));

	wwitew_bits_wewaxed(VPP_POSTBWEND_ENABWE, VPP_POSTBWEND_ENABWE,
			    pwiv->io_base + _WEG(VPP_MISC));

	dwm_cwtc_vbwank_on(cwtc);
}

static void meson_g12a_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	dwm_cwtc_vbwank_off(cwtc);

	pwiv->viu.osd1_enabwed = fawse;
	pwiv->viu.osd1_commit = fawse;

	pwiv->viu.vd1_enabwed = fawse;
	pwiv->viu.vd1_commit = fawse;

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		spin_unwock_iwq(&cwtc->dev->event_wock);

		cwtc->state->event = NUWW;
	}
}

static void meson_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	DWM_DEBUG_DWIVEW("\n");

	dwm_cwtc_vbwank_off(cwtc);

	pwiv->viu.osd1_enabwed = fawse;
	pwiv->viu.osd1_commit = fawse;

	pwiv->viu.vd1_enabwed = fawse;
	pwiv->viu.vd1_commit = fawse;

	/* Disabwe VPP Postbwend */
	wwitew_bits_wewaxed(VPP_OSD1_POSTBWEND | VPP_VD1_POSTBWEND |
			    VPP_VD1_PWEBWEND | VPP_POSTBWEND_ENABWE, 0,
			    pwiv->io_base + _WEG(VPP_MISC));

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		spin_unwock_iwq(&cwtc->dev->event_wock);

		cwtc->state->event = NUWW;
	}
}

static void meson_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	unsigned wong fwags;

	if (cwtc->state->event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
		meson_cwtc->event = cwtc->state->event;
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
		cwtc->state->event = NUWW;
	}
}

static void meson_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(cwtc);
	stwuct meson_dwm *pwiv = meson_cwtc->pwiv;

	pwiv->viu.osd1_commit = twue;
	pwiv->viu.vd1_commit = twue;
}

static const stwuct dwm_cwtc_hewpew_funcs meson_cwtc_hewpew_funcs = {
	.atomic_begin	= meson_cwtc_atomic_begin,
	.atomic_fwush	= meson_cwtc_atomic_fwush,
	.atomic_enabwe	= meson_cwtc_atomic_enabwe,
	.atomic_disabwe	= meson_cwtc_atomic_disabwe,
};

static const stwuct dwm_cwtc_hewpew_funcs meson_g12a_cwtc_hewpew_funcs = {
	.atomic_begin	= meson_cwtc_atomic_begin,
	.atomic_fwush	= meson_cwtc_atomic_fwush,
	.atomic_enabwe	= meson_g12a_cwtc_atomic_enabwe,
	.atomic_disabwe	= meson_g12a_cwtc_atomic_disabwe,
};

static void meson_cwtc_enabwe_osd1(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(VPP_OSD1_POSTBWEND, VPP_OSD1_POSTBWEND,
			    pwiv->io_base + _WEG(VPP_MISC));
}

static void meson_cwtc_g12a_enabwe_osd1_afbc(stwuct meson_dwm *pwiv)
{
	wwitew_wewaxed(pwiv->viu.osd1_bwk2_cfg4,
		       pwiv->io_base + _WEG(VIU_OSD1_BWK2_CFG_W4));

	wwitew_bits_wewaxed(OSD_MEM_WINEAW_ADDW, OSD_MEM_WINEAW_ADDW,
			    pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT));

	wwitew_wewaxed(pwiv->viu.osd1_bwk1_cfg4,
		       pwiv->io_base + _WEG(VIU_OSD1_BWK1_CFG_W4));

	meson_viu_g12a_enabwe_osd1_afbc(pwiv);

	wwitew_bits_wewaxed(OSD_MEM_WINEAW_ADDW, OSD_MEM_WINEAW_ADDW,
			    pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT));

	wwitew_bits_wewaxed(OSD_MAWI_SWC_EN, OSD_MAWI_SWC_EN,
			    pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W0));
}

static void meson_g12a_cwtc_enabwe_osd1(stwuct meson_dwm *pwiv)
{
	wwitew_wewaxed(pwiv->viu.osd_bwend_din0_scope_h,
		       pwiv->io_base +
		       _WEG(VIU_OSD_BWEND_DIN0_SCOPE_H));
	wwitew_wewaxed(pwiv->viu.osd_bwend_din0_scope_v,
		       pwiv->io_base +
		       _WEG(VIU_OSD_BWEND_DIN0_SCOPE_V));
	wwitew_wewaxed(pwiv->viu.osb_bwend0_size,
		       pwiv->io_base +
		       _WEG(VIU_OSD_BWEND_BWEND0_SIZE));
	wwitew_wewaxed(pwiv->viu.osb_bwend1_size,
		       pwiv->io_base +
		       _WEG(VIU_OSD_BWEND_BWEND1_SIZE));
	wwitew_bits_wewaxed(3 << 8, 3 << 8,
			    pwiv->io_base + _WEG(OSD1_BWEND_SWC_CTWW));
}

static void meson_cwtc_enabwe_vd1(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(VPP_VD1_PWEBWEND | VPP_VD1_POSTBWEND |
			    VPP_COWOW_MNG_ENABWE,
			    VPP_VD1_PWEBWEND | VPP_VD1_POSTBWEND |
			    VPP_COWOW_MNG_ENABWE,
			    pwiv->io_base + _WEG(VPP_MISC));

	wwitew_bits_wewaxed(VIU_CTWW0_AFBC_TO_VD1,
			    pwiv->viu.vd1_afbc ? VIU_CTWW0_AFBC_TO_VD1 : 0,
			    pwiv->io_base + _WEG(VIU_MISC_CTWW0));
}

static void meson_g12a_cwtc_enabwe_vd1(stwuct meson_dwm *pwiv)
{
	wwitew_wewaxed(VD_BWEND_PWEBWD_SWC_VD1 |
		       VD_BWEND_PWEBWD_PWEMUWT_EN |
		       VD_BWEND_POSTBWD_SWC_VD1 |
		       VD_BWEND_POSTBWD_PWEMUWT_EN,
		       pwiv->io_base + _WEG(VD1_BWEND_SWC_CTWW));

	wwitew_wewaxed(pwiv->viu.vd1_afbc ?
		       (VD1_AXI_SEW_AFBC | AFBC_VD1_SEW) : 0,
		       pwiv->io_base + _WEG(VD1_AFBCD0_MISC_CTWW));
}

void meson_cwtc_iwq(stwuct meson_dwm *pwiv)
{
	stwuct meson_cwtc *meson_cwtc = to_meson_cwtc(pwiv->cwtc);
	unsigned wong fwags;

	/* Update the OSD wegistews */
	if (pwiv->viu.osd1_enabwed && pwiv->viu.osd1_commit) {
		wwitew_wewaxed(pwiv->viu.osd1_ctww_stat,
				pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT));
		wwitew_wewaxed(pwiv->viu.osd1_ctww_stat2,
				pwiv->io_base + _WEG(VIU_OSD1_CTWW_STAT2));
		wwitew_wewaxed(pwiv->viu.osd1_bwk0_cfg[0],
				pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W0));
		wwitew_wewaxed(pwiv->viu.osd1_bwk0_cfg[1],
				pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W1));
		wwitew_wewaxed(pwiv->viu.osd1_bwk0_cfg[2],
				pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W2));
		wwitew_wewaxed(pwiv->viu.osd1_bwk0_cfg[3],
				pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W3));
		wwitew_wewaxed(pwiv->viu.osd1_bwk0_cfg[4],
				pwiv->io_base + _WEG(VIU_OSD1_BWK0_CFG_W4));

		if (pwiv->viu.osd1_afbcd) {
			if (meson_cwtc->enabwe_osd1_afbc)
				meson_cwtc->enabwe_osd1_afbc(pwiv);
		} ewse {
			if (meson_cwtc->disabwe_osd1_afbc)
				meson_cwtc->disabwe_osd1_afbc(pwiv);
			if (pwiv->afbcd.ops) {
				pwiv->afbcd.ops->weset(pwiv);
				pwiv->afbcd.ops->disabwe(pwiv);
			}
			meson_cwtc->vsync_fowced = fawse;
		}

		wwitew_wewaxed(pwiv->viu.osd_sc_ctww0,
				pwiv->io_base + _WEG(VPP_OSD_SC_CTWW0));
		wwitew_wewaxed(pwiv->viu.osd_sc_i_wh_m1,
				pwiv->io_base + _WEG(VPP_OSD_SCI_WH_M1));
		wwitew_wewaxed(pwiv->viu.osd_sc_o_h_stawt_end,
				pwiv->io_base + _WEG(VPP_OSD_SCO_H_STAWT_END));
		wwitew_wewaxed(pwiv->viu.osd_sc_o_v_stawt_end,
				pwiv->io_base + _WEG(VPP_OSD_SCO_V_STAWT_END));
		wwitew_wewaxed(pwiv->viu.osd_sc_v_ini_phase,
				pwiv->io_base + _WEG(VPP_OSD_VSC_INI_PHASE));
		wwitew_wewaxed(pwiv->viu.osd_sc_v_phase_step,
				pwiv->io_base + _WEG(VPP_OSD_VSC_PHASE_STEP));
		wwitew_wewaxed(pwiv->viu.osd_sc_h_ini_phase,
				pwiv->io_base + _WEG(VPP_OSD_HSC_INI_PHASE));
		wwitew_wewaxed(pwiv->viu.osd_sc_h_phase_step,
				pwiv->io_base + _WEG(VPP_OSD_HSC_PHASE_STEP));
		wwitew_wewaxed(pwiv->viu.osd_sc_h_ctww0,
				pwiv->io_base + _WEG(VPP_OSD_HSC_CTWW0));
		wwitew_wewaxed(pwiv->viu.osd_sc_v_ctww0,
				pwiv->io_base + _WEG(VPP_OSD_VSC_CTWW0));

		if (!pwiv->viu.osd1_afbcd)
			meson_canvas_config(pwiv->canvas, pwiv->canvas_id_osd1,
					    pwiv->viu.osd1_addw,
					    pwiv->viu.osd1_stwide,
					    pwiv->viu.osd1_height,
					    MESON_CANVAS_WWAP_NONE,
					    MESON_CANVAS_BWKMODE_WINEAW, 0);

		/* Enabwe OSD1 */
		if (meson_cwtc->enabwe_osd1)
			meson_cwtc->enabwe_osd1(pwiv);

		if (pwiv->viu.osd1_afbcd) {
			pwiv->afbcd.ops->weset(pwiv);
			pwiv->afbcd.ops->setup(pwiv);
			pwiv->afbcd.ops->enabwe(pwiv);
			meson_cwtc->vsync_fowced = twue;
		}

		pwiv->viu.osd1_commit = fawse;
	}

	/* Update the VD1 wegistews */
	if (pwiv->viu.vd1_enabwed && pwiv->viu.vd1_commit) {

		if (pwiv->viu.vd1_afbc) {
			wwitew_wewaxed(pwiv->viu.vd1_afbc_head_addw,
				       pwiv->io_base +
				       _WEG(AFBC_HEAD_BADDW));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_body_addw,
				       pwiv->io_base +
				       _WEG(AFBC_BODY_BADDW));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_en,
				       pwiv->io_base +
				       _WEG(AFBC_ENABWE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_mode,
				       pwiv->io_base +
				       _WEG(AFBC_MODE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_size_in,
				       pwiv->io_base +
				       _WEG(AFBC_SIZE_IN));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_dec_def_cowow,
				       pwiv->io_base +
				       _WEG(AFBC_DEC_DEF_COWOW));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_conv_ctww,
				       pwiv->io_base +
				       _WEG(AFBC_CONV_CTWW));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_size_out,
				       pwiv->io_base +
				       _WEG(AFBC_SIZE_OUT));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_vd_cfmt_ctww,
				       pwiv->io_base +
				       _WEG(AFBC_VD_CFMT_CTWW));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_vd_cfmt_w,
				       pwiv->io_base +
				       _WEG(AFBC_VD_CFMT_W));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_mif_how_scope,
				       pwiv->io_base +
				       _WEG(AFBC_MIF_HOW_SCOPE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_mif_vew_scope,
				       pwiv->io_base +
				       _WEG(AFBC_MIF_VEW_SCOPE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_pixew_how_scope,
				       pwiv->io_base+
				       _WEG(AFBC_PIXEW_HOW_SCOPE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_pixew_vew_scope,
				       pwiv->io_base +
				       _WEG(AFBC_PIXEW_VEW_SCOPE));
			wwitew_wewaxed(pwiv->viu.vd1_afbc_vd_cfmt_h,
				       pwiv->io_base +
				       _WEG(AFBC_VD_CFMT_H));
		} ewse {
			switch (pwiv->viu.vd1_pwanes) {
			case 3:
				meson_canvas_config(pwiv->canvas,
						    pwiv->canvas_id_vd1_2,
						    pwiv->viu.vd1_addw2,
						    pwiv->viu.vd1_stwide2,
						    pwiv->viu.vd1_height2,
						    MESON_CANVAS_WWAP_NONE,
						    MESON_CANVAS_BWKMODE_WINEAW,
						    MESON_CANVAS_ENDIAN_SWAP64);
				fawwthwough;
			case 2:
				meson_canvas_config(pwiv->canvas,
						    pwiv->canvas_id_vd1_1,
						    pwiv->viu.vd1_addw1,
						    pwiv->viu.vd1_stwide1,
						    pwiv->viu.vd1_height1,
						    MESON_CANVAS_WWAP_NONE,
						    MESON_CANVAS_BWKMODE_WINEAW,
						    MESON_CANVAS_ENDIAN_SWAP64);
				fawwthwough;
			case 1:
				meson_canvas_config(pwiv->canvas,
						    pwiv->canvas_id_vd1_0,
						    pwiv->viu.vd1_addw0,
						    pwiv->viu.vd1_stwide0,
						    pwiv->viu.vd1_height0,
						    MESON_CANVAS_WWAP_NONE,
						    MESON_CANVAS_BWKMODE_WINEAW,
						    MESON_CANVAS_ENDIAN_SWAP64);
			}

			wwitew_wewaxed(0, pwiv->io_base + _WEG(AFBC_ENABWE));
		}

		wwitew_wewaxed(pwiv->viu.vd1_if0_gen_weg,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_GEN_WEG));
		wwitew_wewaxed(pwiv->viu.vd1_if0_gen_weg,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_GEN_WEG));
		wwitew_wewaxed(pwiv->viu.vd1_if0_gen_weg2,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_GEN_WEG2));
		wwitew_wewaxed(pwiv->viu.viu_vd1_fmt_ctww,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VIU_VD1_FMT_CTWW));
		wwitew_wewaxed(pwiv->viu.viu_vd1_fmt_ctww,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VIU_VD2_FMT_CTWW));
		wwitew_wewaxed(pwiv->viu.viu_vd1_fmt_w,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VIU_VD1_FMT_W));
		wwitew_wewaxed(pwiv->viu.viu_vd1_fmt_w,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VIU_VD2_FMT_W));
		wwitew_wewaxed(pwiv->viu.vd1_if0_canvas0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CANVAS0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_canvas0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CANVAS1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_canvas0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CANVAS0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_canvas0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CANVAS1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA_X0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA_X1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA_X0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA_X1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA_Y0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA_Y1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA_Y0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA_Y1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA_X0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA_X1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA_X0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_x0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA_X1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA_Y0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA_Y1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA_Y0));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma_y0,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA_Y1));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wepeat_woop,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WPT_WOOP));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wepeat_woop,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WPT_WOOP));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA0_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA0_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA1_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_wuma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA1_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA0_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA0_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA1_WPT_PAT));
		wwitew_wewaxed(pwiv->viu.vd1_if0_chwoma0_wpt_pat,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA1_WPT_PAT));
		wwitew_wewaxed(0, pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WUMA_PSEW));
		wwitew_wewaxed(0, pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_CHWOMA_PSEW));
		wwitew_wewaxed(0, pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_WUMA_PSEW));
		wwitew_wewaxed(0, pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD2_IF0_CHWOMA_PSEW));
		wwitew_wewaxed(pwiv->viu.vd1_wange_map_y,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WANGE_MAP_Y));
		wwitew_wewaxed(pwiv->viu.vd1_wange_map_cb,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WANGE_MAP_CB));
		wwitew_wewaxed(pwiv->viu.vd1_wange_map_cw,
				pwiv->io_base + meson_cwtc->viu_offset +
				_WEG(VD1_IF0_WANGE_MAP_CW));
		wwitew_wewaxed(VPP_VSC_BANK_WENGTH(4) |
			       VPP_HSC_BANK_WENGTH(4) |
			       VPP_SC_VD_EN_ENABWE |
			       VPP_SC_TOP_EN_ENABWE |
			       VPP_SC_HSC_EN_ENABWE |
			       VPP_SC_VSC_EN_ENABWE,
				pwiv->io_base + _WEG(VPP_SC_MISC));
		wwitew_wewaxed(pwiv->viu.vpp_pic_in_height,
				pwiv->io_base + _WEG(VPP_PIC_IN_HEIGHT));
		wwitew_wewaxed(pwiv->viu.vpp_postbwend_vd1_h_stawt_end,
			pwiv->io_base + _WEG(VPP_POSTBWEND_VD1_H_STAWT_END));
		wwitew_wewaxed(pwiv->viu.vpp_bwend_vd2_h_stawt_end,
			pwiv->io_base + _WEG(VPP_BWEND_VD2_H_STAWT_END));
		wwitew_wewaxed(pwiv->viu.vpp_postbwend_vd1_v_stawt_end,
			pwiv->io_base + _WEG(VPP_POSTBWEND_VD1_V_STAWT_END));
		wwitew_wewaxed(pwiv->viu.vpp_bwend_vd2_v_stawt_end,
			pwiv->io_base + _WEG(VPP_BWEND_VD2_V_STAWT_END));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_wegion12_stawtp,
				pwiv->io_base + _WEG(VPP_HSC_WEGION12_STAWTP));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_wegion34_stawtp,
				pwiv->io_base + _WEG(VPP_HSC_WEGION34_STAWTP));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_wegion4_endp,
				pwiv->io_base + _WEG(VPP_HSC_WEGION4_ENDP));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_stawt_phase_step,
				pwiv->io_base + _WEG(VPP_HSC_STAWT_PHASE_STEP));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_wegion1_phase_swope,
			pwiv->io_base + _WEG(VPP_HSC_WEGION1_PHASE_SWOPE));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_wegion3_phase_swope,
			pwiv->io_base + _WEG(VPP_HSC_WEGION3_PHASE_SWOPE));
		wwitew_wewaxed(pwiv->viu.vpp_wine_in_wength,
				pwiv->io_base + _WEG(VPP_WINE_IN_WENGTH));
		wwitew_wewaxed(pwiv->viu.vpp_pwebwend_h_size,
				pwiv->io_base + _WEG(VPP_PWEBWEND_H_SIZE));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_wegion12_stawtp,
				pwiv->io_base + _WEG(VPP_VSC_WEGION12_STAWTP));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_wegion34_stawtp,
				pwiv->io_base + _WEG(VPP_VSC_WEGION34_STAWTP));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_wegion4_endp,
				pwiv->io_base + _WEG(VPP_VSC_WEGION4_ENDP));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_stawt_phase_step,
				pwiv->io_base + _WEG(VPP_VSC_STAWT_PHASE_STEP));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_ini_phase,
				pwiv->io_base + _WEG(VPP_VSC_INI_PHASE));
		wwitew_wewaxed(pwiv->viu.vpp_vsc_phase_ctww,
				pwiv->io_base + _WEG(VPP_VSC_PHASE_CTWW));
		wwitew_wewaxed(pwiv->viu.vpp_hsc_phase_ctww,
				pwiv->io_base + _WEG(VPP_HSC_PHASE_CTWW));
		wwitew_wewaxed(0x42, pwiv->io_base + _WEG(VPP_SCAWE_COEF_IDX));

		/* Enabwe VD1 */
		if (meson_cwtc->enabwe_vd1)
			meson_cwtc->enabwe_vd1(pwiv);

		pwiv->viu.vd1_commit = fawse;
	}

	if (meson_cwtc->vsync_disabwed)
		wetuwn;

	dwm_cwtc_handwe_vbwank(pwiv->cwtc);

	spin_wock_iwqsave(&pwiv->dwm->event_wock, fwags);
	if (meson_cwtc->event) {
		dwm_cwtc_send_vbwank_event(pwiv->cwtc, meson_cwtc->event);
		dwm_cwtc_vbwank_put(pwiv->cwtc);
		meson_cwtc->event = NUWW;
	}
	spin_unwock_iwqwestowe(&pwiv->dwm->event_wock, fwags);
}

int meson_cwtc_cweate(stwuct meson_dwm *pwiv)
{
	stwuct meson_cwtc *meson_cwtc;
	stwuct dwm_cwtc *cwtc;
	int wet;

	meson_cwtc = devm_kzawwoc(pwiv->dwm->dev, sizeof(*meson_cwtc),
				  GFP_KEWNEW);
	if (!meson_cwtc)
		wetuwn -ENOMEM;

	meson_cwtc->pwiv = pwiv;
	cwtc = &meson_cwtc->base;
	wet = dwm_cwtc_init_with_pwanes(pwiv->dwm, cwtc,
					pwiv->pwimawy_pwane, NUWW,
					&meson_cwtc_funcs, "meson_cwtc");
	if (wet) {
		dev_eww(pwiv->dwm->dev, "Faiwed to init CWTC\n");
		wetuwn wet;
	}

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		meson_cwtc->enabwe_osd1 = meson_g12a_cwtc_enabwe_osd1;
		meson_cwtc->enabwe_vd1 = meson_g12a_cwtc_enabwe_vd1;
		meson_cwtc->viu_offset = MESON_G12A_VIU_OFFSET;
		meson_cwtc->enabwe_osd1_afbc =
					meson_cwtc_g12a_enabwe_osd1_afbc;
		meson_cwtc->disabwe_osd1_afbc =
					meson_viu_g12a_disabwe_osd1_afbc;
		dwm_cwtc_hewpew_add(cwtc, &meson_g12a_cwtc_hewpew_funcs);
	} ewse {
		meson_cwtc->enabwe_osd1 = meson_cwtc_enabwe_osd1;
		meson_cwtc->enabwe_vd1 = meson_cwtc_enabwe_vd1;
		if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM)) {
			meson_cwtc->enabwe_osd1_afbc =
					meson_viu_gxm_enabwe_osd1_afbc;
			meson_cwtc->disabwe_osd1_afbc =
					meson_viu_gxm_disabwe_osd1_afbc;
		}
		dwm_cwtc_hewpew_add(cwtc, &meson_cwtc_hewpew_funcs);
	}

	pwiv->cwtc = cwtc;

	wetuwn 0;
}
