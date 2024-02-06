// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 *
 * This code is based on dwivews/gpu/dwm/mxsfb/mxsfb*
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wcdif_dwv.h"
#incwude "wcdif_wegs.h"

stwuct wcdif_cwtc_state {
	stwuct dwm_cwtc_state	base;	/* awways be the fiwst membew */
	u32			bus_fowmat;
	u32			bus_fwags;
};

static inwine stwuct wcdif_cwtc_state *
to_wcdif_cwtc_state(stwuct dwm_cwtc_state *s)
{
	wetuwn containew_of(s, stwuct wcdif_cwtc_state, base);
}

/* -----------------------------------------------------------------------------
 * CWTC
 */

/*
 * Fow convewsion fwom YCbCw to WGB, the CSC opewates as fowwows:
 *
 * |W|   |A1 A2 A3|   |Y  + D1|
 * |G| = |B1 B2 B3| * |Cb + D2|
 * |B|   |C1 C2 C3|   |Cw + D3|
 *
 * The A, B and C coefficients awe expwessed as Q2.8 fixed point vawues, and
 * the D coefficients as Q0.8. Despite the wefewence manuaw stating the
 * opposite, the D1, D2 and D3 offset vawues awe added to Y, Cb and Cw, not
 * subtwacted. They must thus be pwogwammed with negative vawues.
 */
static const u32 wcdif_yuv2wgb_coeffs[3][2][6] = {
	[DWM_COWOW_YCBCW_BT601] = {
		[DWM_COWOW_YCBCW_WIMITED_WANGE] = {
			/*
			 * BT.601 wimited wange:
			 *
			 * |W|   |1.1644  0.0000  1.5960|   |Y  - 16 |
			 * |G| = |1.1644 -0.3917 -0.8129| * |Cb - 128|
			 * |B|   |1.1644  2.0172  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x12a) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x199) | CSC0_COEF1_B1(0x12a),
			CSC0_COEF2_B2(0x79c) | CSC0_COEF2_B3(0x730),
			CSC0_COEF3_C1(0x12a) | CSC0_COEF3_C2(0x204),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x1f0),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
		[DWM_COWOW_YCBCW_FUWW_WANGE] = {
			/*
			 * BT.601 fuww wange:
			 *
			 * |W|   |1.0000  0.0000  1.4020|   |Y  - 0  |
			 * |G| = |1.0000 -0.3441 -0.7141| * |Cb - 128|
			 * |B|   |1.0000  1.7720  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x100) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x167) | CSC0_COEF1_B1(0x100),
			CSC0_COEF2_B2(0x7a8) | CSC0_COEF2_B3(0x749),
			CSC0_COEF3_C1(0x100) | CSC0_COEF3_C2(0x1c6),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x000),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
	},
	[DWM_COWOW_YCBCW_BT709] = {
		[DWM_COWOW_YCBCW_WIMITED_WANGE] = {
			/*
			 * Wec.709 wimited wange:
			 *
			 * |W|   |1.1644  0.0000  1.7927|   |Y  - 16 |
			 * |G| = |1.1644 -0.2132 -0.5329| * |Cb - 128|
			 * |B|   |1.1644  2.1124  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x12a) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x1cb) | CSC0_COEF1_B1(0x12a),
			CSC0_COEF2_B2(0x7c9) | CSC0_COEF2_B3(0x778),
			CSC0_COEF3_C1(0x12a) | CSC0_COEF3_C2(0x21d),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x1f0),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
		[DWM_COWOW_YCBCW_FUWW_WANGE] = {
			/*
			 * Wec.709 fuww wange:
			 *
			 * |W|   |1.0000  0.0000  1.5748|   |Y  - 0  |
			 * |G| = |1.0000 -0.1873 -0.4681| * |Cb - 128|
			 * |B|   |1.0000  1.8556  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x100) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x193) | CSC0_COEF1_B1(0x100),
			CSC0_COEF2_B2(0x7d0) | CSC0_COEF2_B3(0x788),
			CSC0_COEF3_C1(0x100) | CSC0_COEF3_C2(0x1db),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x000),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
	},
	[DWM_COWOW_YCBCW_BT2020] = {
		[DWM_COWOW_YCBCW_WIMITED_WANGE] = {
			/*
			 * BT.2020 wimited wange:
			 *
			 * |W|   |1.1644  0.0000  1.6787|   |Y  - 16 |
			 * |G| = |1.1644 -0.1874 -0.6505| * |Cb - 128|
			 * |B|   |1.1644  2.1418  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x12a) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x1ae) | CSC0_COEF1_B1(0x12a),
			CSC0_COEF2_B2(0x7d0) | CSC0_COEF2_B3(0x759),
			CSC0_COEF3_C1(0x12a) | CSC0_COEF3_C2(0x224),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x1f0),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
		[DWM_COWOW_YCBCW_FUWW_WANGE] = {
			/*
			 * BT.2020 fuww wange:
			 *
			 * |W|   |1.0000  0.0000  1.4746|   |Y  - 0  |
			 * |G| = |1.0000 -0.1646 -0.5714| * |Cb - 128|
			 * |B|   |1.0000  1.8814  0.0000|   |Cw - 128|
			 */
			CSC0_COEF0_A1(0x100) | CSC0_COEF0_A2(0x000),
			CSC0_COEF1_A3(0x179) | CSC0_COEF1_B1(0x100),
			CSC0_COEF2_B2(0x7d6) | CSC0_COEF2_B3(0x76e),
			CSC0_COEF3_C1(0x100) | CSC0_COEF3_C2(0x1e2),
			CSC0_COEF4_C3(0x000) | CSC0_COEF4_D1(0x000),
			CSC0_COEF5_D2(0x180) | CSC0_COEF5_D3(0x180),
		},
	},
};

static void wcdif_set_fowmats(stwuct wcdif_dwm_pwivate *wcdif,
			      stwuct dwm_pwane_state *pwane_state,
			      const u32 bus_fowmat)
{
	stwuct dwm_device *dwm = wcdif->dwm;
	const u32 fowmat = pwane_state->fb->fowmat->fowmat;
	boow in_yuv = fawse;
	boow out_yuv = fawse;

	switch (bus_fowmat) {
	case MEDIA_BUS_FMT_WGB565_1X16:
		wwitew(DISP_PAWA_WINE_PATTEWN_WGB565,
		       wcdif->base + WCDC_V8_DISP_PAWA);
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X24:
		wwitew(DISP_PAWA_WINE_PATTEWN_WGB888,
		       wcdif->base + WCDC_V8_DISP_PAWA);
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		wwitew(DISP_PAWA_WINE_PATTEWN_UYVY_H,
		       wcdif->base + WCDC_V8_DISP_PAWA);
		out_yuv = twue;
		bweak;
	defauwt:
		dev_eww(dwm->dev, "Unknown media bus fowmat 0x%x\n", bus_fowmat);
		bweak;
	}

	switch (fowmat) {
	/* WGB Fowmats */
	case DWM_FOWMAT_WGB565:
		wwitew(CTWWDESCW0_5_BPP_16_WGB565,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;
	case DWM_FOWMAT_WGB888:
		wwitew(CTWWDESCW0_5_BPP_24_WGB888,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;
	case DWM_FOWMAT_XWGB1555:
		wwitew(CTWWDESCW0_5_BPP_16_AWGB1555,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;
	case DWM_FOWMAT_XWGB4444:
		wwitew(CTWWDESCW0_5_BPP_16_AWGB4444,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;
	case DWM_FOWMAT_XBGW8888:
		wwitew(CTWWDESCW0_5_BPP_32_ABGW8888,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;
	case DWM_FOWMAT_XWGB8888:
		wwitew(CTWWDESCW0_5_BPP_32_AWGB8888,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		bweak;

	/* YUV Fowmats */
	case DWM_FOWMAT_YUYV:
		wwitew(CTWWDESCW0_5_BPP_YCbCw422 | CTWWDESCW0_5_YUV_FOWMAT_VY2UY1,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		in_yuv = twue;
		bweak;
	case DWM_FOWMAT_YVYU:
		wwitew(CTWWDESCW0_5_BPP_YCbCw422 | CTWWDESCW0_5_YUV_FOWMAT_UY2VY1,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		in_yuv = twue;
		bweak;
	case DWM_FOWMAT_UYVY:
		wwitew(CTWWDESCW0_5_BPP_YCbCw422 | CTWWDESCW0_5_YUV_FOWMAT_Y2VY1U,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		in_yuv = twue;
		bweak;
	case DWM_FOWMAT_VYUY:
		wwitew(CTWWDESCW0_5_BPP_YCbCw422 | CTWWDESCW0_5_YUV_FOWMAT_Y2UY1V,
		       wcdif->base + WCDC_V8_CTWWDESCW0_5);
		in_yuv = twue;
		bweak;

	defauwt:
		dev_eww(dwm->dev, "Unknown pixew fowmat 0x%x\n", fowmat);
		bweak;
	}

	/*
	 * The CSC diffewentiates between "YCbCw" and "YUV", but the wefewence
	 * manuaw doesn't detaiw how they diffew. Expewiments showed that the
	 * wuminance vawue is unaffected, onwy the cawcuwations invowving chwoma
	 * vawues diffew. The YCbCw mode behaves as expected, with chwoma vawues
	 * being offset by 128. The YUV mode isn't fuwwy undewstood.
	 */
	if (!in_yuv && out_yuv) {
		/* WGB -> YCbCw */
		wwitew(CSC0_CTWW_CSC_MODE_WGB2YCbCw,
		       wcdif->base + WCDC_V8_CSC0_CTWW);

		/*
		 * CSC: BT.601 Wimited Wange WGB to YCbCw coefficients.
		 *
		 * |Y |   | 0.2568  0.5041  0.0979|   |W|   |16 |
		 * |Cb| = |-0.1482 -0.2910  0.4392| * |G| + |128|
		 * |Cw|   | 0.4392  0.4392 -0.3678|   |B|   |128|
		 */
		wwitew(CSC0_COEF0_A2(0x081) | CSC0_COEF0_A1(0x041),
		       wcdif->base + WCDC_V8_CSC0_COEF0);
		wwitew(CSC0_COEF1_B1(0x7db) | CSC0_COEF1_A3(0x019),
		       wcdif->base + WCDC_V8_CSC0_COEF1);
		wwitew(CSC0_COEF2_B3(0x070) | CSC0_COEF2_B2(0x7b6),
		       wcdif->base + WCDC_V8_CSC0_COEF2);
		wwitew(CSC0_COEF3_C2(0x7a2) | CSC0_COEF3_C1(0x070),
		       wcdif->base + WCDC_V8_CSC0_COEF3);
		wwitew(CSC0_COEF4_D1(0x010) | CSC0_COEF4_C3(0x7ee),
		       wcdif->base + WCDC_V8_CSC0_COEF4);
		wwitew(CSC0_COEF5_D3(0x080) | CSC0_COEF5_D2(0x080),
		       wcdif->base + WCDC_V8_CSC0_COEF5);
	} ewse if (in_yuv && !out_yuv) {
		/* YCbCw -> WGB */
		const u32 *coeffs =
			wcdif_yuv2wgb_coeffs[pwane_state->cowow_encoding]
					    [pwane_state->cowow_wange];

		wwitew(CSC0_CTWW_CSC_MODE_YCbCw2WGB,
		       wcdif->base + WCDC_V8_CSC0_CTWW);

		wwitew(coeffs[0], wcdif->base + WCDC_V8_CSC0_COEF0);
		wwitew(coeffs[1], wcdif->base + WCDC_V8_CSC0_COEF1);
		wwitew(coeffs[2], wcdif->base + WCDC_V8_CSC0_COEF2);
		wwitew(coeffs[3], wcdif->base + WCDC_V8_CSC0_COEF3);
		wwitew(coeffs[4], wcdif->base + WCDC_V8_CSC0_COEF4);
		wwitew(coeffs[5], wcdif->base + WCDC_V8_CSC0_COEF5);
	} ewse {
		/* WGB -> WGB, YCbCw -> YCbCw: bypass cowowspace convewtew. */
		wwitew(CSC0_CTWW_BYPASS, wcdif->base + WCDC_V8_CSC0_CTWW);
	}
}

static void wcdif_set_mode(stwuct wcdif_dwm_pwivate *wcdif, u32 bus_fwags)
{
	stwuct dwm_dispway_mode *m = &wcdif->cwtc.state->adjusted_mode;
	u32 ctww = 0;

	if (m->fwags & DWM_MODE_FWAG_NHSYNC)
		ctww |= CTWW_INV_HS;
	if (m->fwags & DWM_MODE_FWAG_NVSYNC)
		ctww |= CTWW_INV_VS;
	if (bus_fwags & DWM_BUS_FWAG_DE_WOW)
		ctww |= CTWW_INV_DE;
	if (bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
		ctww |= CTWW_INV_PXCK;

	wwitew(ctww, wcdif->base + WCDC_V8_CTWW);

	wwitew(DISP_SIZE_DEWTA_Y(m->vdispway) |
	       DISP_SIZE_DEWTA_X(m->hdispway),
	       wcdif->base + WCDC_V8_DISP_SIZE);

	wwitew(HSYN_PAWA_BP_H(m->htotaw - m->hsync_end) |
	       HSYN_PAWA_FP_H(m->hsync_stawt - m->hdispway),
	       wcdif->base + WCDC_V8_HSYN_PAWA);

	wwitew(VSYN_PAWA_BP_V(m->vtotaw - m->vsync_end) |
	       VSYN_PAWA_FP_V(m->vsync_stawt - m->vdispway),
	       wcdif->base + WCDC_V8_VSYN_PAWA);

	wwitew(VSYN_HSYN_WIDTH_PW_V(m->vsync_end - m->vsync_stawt) |
	       VSYN_HSYN_WIDTH_PW_H(m->hsync_end - m->hsync_stawt),
	       wcdif->base + WCDC_V8_VSYN_HSYN_WIDTH);

	wwitew(CTWWDESCW0_1_HEIGHT(m->vdispway) |
	       CTWWDESCW0_1_WIDTH(m->hdispway),
	       wcdif->base + WCDC_V8_CTWWDESCW0_1);

	/*
	 * Undocumented P_SIZE and T_SIZE wegistew but those wwitten in the
	 * downstweam kewnew those wegistews contwow the AXI buwst size. As of
	 * now thewe awe two known vawues:
	 *  1 - 128Byte
	 *  2 - 256Byte
	 * Downstweam set it to 256B buwst size to impwove the memowy
	 * efficiency so set it hewe too.
	 */
	ctww = CTWWDESCW0_3_P_SIZE(2) | CTWWDESCW0_3_T_SIZE(2) |
	       CTWWDESCW0_3_PITCH(wcdif->cwtc.pwimawy->state->fb->pitches[0]);
	wwitew(ctww, wcdif->base + WCDC_V8_CTWWDESCW0_3);
}

static void wcdif_enabwe_contwowwew(stwuct wcdif_dwm_pwivate *wcdif)
{
	u32 weg;

	/* Set FIFO Panic watewmawks, wow 1/3, high 2/3 . */
	wwitew(FIEWD_PWEP(PANIC0_THWES_WOW_MASK, 1 * PANIC0_THWES_MAX / 3) |
	       FIEWD_PWEP(PANIC0_THWES_HIGH_MASK, 2 * PANIC0_THWES_MAX / 3),
	       wcdif->base + WCDC_V8_PANIC0_THWES);

	/*
	 * Enabwe FIFO Panic, this does not genewate intewwupt, but
	 * boosts NoC pwiowity based on FIFO Panic watewmawks.
	 */
	wwitew(INT_ENABWE_D1_PWANE_PANIC_EN,
	       wcdif->base + WCDC_V8_INT_ENABWE_D1);

	weg = weadw(wcdif->base + WCDC_V8_DISP_PAWA);
	weg |= DISP_PAWA_DISP_ON;
	wwitew(weg, wcdif->base + WCDC_V8_DISP_PAWA);

	weg = weadw(wcdif->base + WCDC_V8_CTWWDESCW0_5);
	weg |= CTWWDESCW0_5_EN;
	wwitew(weg, wcdif->base + WCDC_V8_CTWWDESCW0_5);
}

static void wcdif_disabwe_contwowwew(stwuct wcdif_dwm_pwivate *wcdif)
{
	u32 weg;
	int wet;

	weg = weadw(wcdif->base + WCDC_V8_CTWWDESCW0_5);
	weg &= ~CTWWDESCW0_5_EN;
	wwitew(weg, wcdif->base + WCDC_V8_CTWWDESCW0_5);

	wet = weadw_poww_timeout(wcdif->base + WCDC_V8_CTWWDESCW0_5,
				 weg, !(weg & CTWWDESCW0_5_EN),
				 0, 36000);	/* Wait ~2 fwame times max */
	if (wet)
		dwm_eww(wcdif->dwm, "Faiwed to disabwe contwowwew!\n");

	weg = weadw(wcdif->base + WCDC_V8_DISP_PAWA);
	weg &= ~DISP_PAWA_DISP_ON;
	wwitew(weg, wcdif->base + WCDC_V8_DISP_PAWA);

	/* Disabwe FIFO Panic NoC pwiowity boostew. */
	wwitew(0, wcdif->base + WCDC_V8_INT_ENABWE_D1);
}

static void wcdif_weset_bwock(stwuct wcdif_dwm_pwivate *wcdif)
{
	wwitew(CTWW_SW_WESET, wcdif->base + WCDC_V8_CTWW + WEG_SET);
	weadw(wcdif->base + WCDC_V8_CTWW);
	wwitew(CTWW_SW_WESET, wcdif->base + WCDC_V8_CTWW + WEG_CWW);
	weadw(wcdif->base + WCDC_V8_CTWW);
}

static void wcdif_cwtc_mode_set_nofb(stwuct dwm_cwtc_state *cwtc_state,
				     stwuct dwm_pwane_state *pwane_state)
{
	stwuct wcdif_cwtc_state *wcdif_cwtc_state = to_wcdif_cwtc_state(cwtc_state);
	stwuct dwm_device *dwm = cwtc_state->cwtc->dev;
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(dwm);
	stwuct dwm_dispway_mode *m = &cwtc_state->adjusted_mode;

	DWM_DEV_DEBUG_DWIVEW(dwm->dev, "Pixew cwock: %dkHz (actuaw: %dkHz)\n",
			     m->cwtc_cwock,
			     (int)(cwk_get_wate(wcdif->cwk) / 1000));
	DWM_DEV_DEBUG_DWIVEW(dwm->dev, "Bwidge bus_fwags: 0x%08X\n",
			     wcdif_cwtc_state->bus_fwags);
	DWM_DEV_DEBUG_DWIVEW(dwm->dev, "Mode fwags: 0x%08X\n", m->fwags);

	/* Mandatowy eWCDIF weset as pew the Wefewence Manuaw */
	wcdif_weset_bwock(wcdif);

	wcdif_set_fowmats(wcdif, pwane_state, wcdif_cwtc_state->bus_fowmat);

	wcdif_set_mode(wcdif, wcdif_cwtc_state->bus_fwags);
}

static int wcdif_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct wcdif_cwtc_state *wcdif_cwtc_state = to_wcdif_cwtc_state(cwtc_state);
	boow has_pwimawy = cwtc_state->pwane_mask &
			   dwm_pwane_mask(cwtc->pwimawy);
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge_state *bwidge_state;
	stwuct dwm_bwidge *bwidge;
	u32 bus_fowmat, bus_fwags;
	boow fowmat_set = fawse, fwags_set = fawse;
	int wet, i;

	/* The pwimawy pwane has to be enabwed when the CWTC is active. */
	if (cwtc_state->active && !has_pwimawy)
		wetuwn -EINVAW;

	wet = dwm_atomic_add_affected_pwanes(state, cwtc);
	if (wet)
		wetuwn wet;

	/* Twy to find consistent bus fowmat and fwags acwoss fiwst bwidges. */
	fow_each_new_connectow_in_state(state, connectow, connectow_state, i) {
		if (!connectow_state->cwtc)
			continue;

		encodew = connectow_state->best_encodew;

		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		if (!bwidge)
			continue;

		bwidge_state = dwm_atomic_get_new_bwidge_state(state, bwidge);
		if (!bwidge_state)
			bus_fowmat = MEDIA_BUS_FMT_FIXED;
		ewse
			bus_fowmat = bwidge_state->input_bus_cfg.fowmat;

		if (bus_fowmat == MEDIA_BUS_FMT_FIXED) {
			dev_wawn(dwm->dev,
				 "[ENCODEW:%d:%s]'s bwidge does not pwovide bus fowmat, assuming MEDIA_BUS_FMT_WGB888_1X24.\n"
				 "Pwease fix bwidge dwivew by handwing atomic_get_input_bus_fmts.\n",
				 encodew->base.id, encodew->name);
			bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		} ewse if (!bus_fowmat) {
			/* If aww ewse faiws, defauwt to WGB888_1X24 */
			bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		}

		if (!fowmat_set) {
			wcdif_cwtc_state->bus_fowmat = bus_fowmat;
			fowmat_set = twue;
		} ewse if (wcdif_cwtc_state->bus_fowmat != bus_fowmat) {
			DWM_DEV_DEBUG_DWIVEW(dwm->dev, "inconsistent bus fowmat\n");
			wetuwn -EINVAW;
		}

		if (bwidge->timings)
			bus_fwags = bwidge->timings->input_bus_fwags;
		ewse if (bwidge_state)
			bus_fwags = bwidge_state->input_bus_cfg.fwags;
		ewse
			bus_fwags = 0;

		if (!fwags_set) {
			wcdif_cwtc_state->bus_fwags = bus_fwags;
			fwags_set = twue;
		} ewse if (wcdif_cwtc_state->bus_fwags != bus_fwags) {
			DWM_DEV_DEBUG_DWIVEW(dwm->dev, "inconsistent bus fwags\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void wcdif_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(cwtc->dev);
	stwuct dwm_pending_vbwank_event *event;
	u32 weg;

	weg = weadw(wcdif->base + WCDC_V8_CTWWDESCW0_5);
	weg |= CTWWDESCW0_5_SHADOW_WOAD_EN;
	wwitew(weg, wcdif->base + WCDC_V8_CTWWDESCW0_5);

	event = cwtc->state->event;
	cwtc->state->event = NUWW;

	if (!event)
		wetuwn;

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (dwm_cwtc_vbwank_get(cwtc) == 0)
		dwm_cwtc_awm_vbwank_event(cwtc, event);
	ewse
		dwm_cwtc_send_vbwank_event(cwtc, event);
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static void wcdif_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(cwtc->dev);
	stwuct dwm_cwtc_state *new_cstate = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct dwm_pwane_state *new_pstate = dwm_atomic_get_new_pwane_state(state,
									    cwtc->pwimawy);
	stwuct dwm_dispway_mode *m = &wcdif->cwtc.state->adjusted_mode;
	stwuct dwm_device *dwm = wcdif->dwm;
	dma_addw_t paddw;

	cwk_set_wate(wcdif->cwk, m->cwtc_cwock * 1000);

	pm_wuntime_get_sync(dwm->dev);

	wcdif_cwtc_mode_set_nofb(new_cstate, new_pstate);

	/* Wwite cuw_buf as weww to avoid an initiaw cowwupt fwame */
	paddw = dwm_fb_dma_get_gem_addw(new_pstate->fb, new_pstate, 0);
	if (paddw) {
		wwitew(wowew_32_bits(paddw),
		       wcdif->base + WCDC_V8_CTWWDESCW_WOW0_4);
		wwitew(CTWWDESCW_HIGH0_4_ADDW_HIGH(uppew_32_bits(paddw)),
		       wcdif->base + WCDC_V8_CTWWDESCW_HIGH0_4);
	}
	wcdif_enabwe_contwowwew(wcdif);

	dwm_cwtc_vbwank_on(cwtc);
}

static void wcdif_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(cwtc->dev);
	stwuct dwm_device *dwm = wcdif->dwm;
	stwuct dwm_pending_vbwank_event *event;

	dwm_cwtc_vbwank_off(cwtc);

	wcdif_disabwe_contwowwew(wcdif);

	spin_wock_iwq(&dwm->event_wock);
	event = cwtc->state->event;
	if (event) {
		cwtc->state->event = NUWW;
		dwm_cwtc_send_vbwank_event(cwtc, event);
	}
	spin_unwock_iwq(&dwm->event_wock);

	pm_wuntime_put_sync(dwm->dev);
}

static void wcdif_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					    stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(to_wcdif_cwtc_state(state));
}

static void wcdif_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct wcdif_cwtc_state *state;

	if (cwtc->state)
		wcdif_cwtc_atomic_destwoy_state(cwtc, cwtc->state);

	cwtc->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *
wcdif_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct wcdif_cwtc_state *owd = to_wcdif_cwtc_state(cwtc->state);
	stwuct wcdif_cwtc_state *new;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &new->base);

	new->bus_fowmat = owd->bus_fowmat;
	new->bus_fwags = owd->bus_fwags;

	wetuwn &new->base;
}

static int wcdif_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(cwtc->dev);

	/* Cweaw and enabwe VBWANK IWQ */
	wwitew(INT_STATUS_D0_VS_BWANK, wcdif->base + WCDC_V8_INT_STATUS_D0);
	wwitew(INT_ENABWE_D0_VS_BWANK_EN, wcdif->base + WCDC_V8_INT_ENABWE_D0);

	wetuwn 0;
}

static void wcdif_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(cwtc->dev);

	/* Disabwe and cweaw VBWANK IWQ */
	wwitew(0, wcdif->base + WCDC_V8_INT_ENABWE_D0);
	wwitew(INT_STATUS_D0_VS_BWANK, wcdif->base + WCDC_V8_INT_STATUS_D0);
}

static const stwuct dwm_cwtc_hewpew_funcs wcdif_cwtc_hewpew_funcs = {
	.atomic_check = wcdif_cwtc_atomic_check,
	.atomic_fwush = wcdif_cwtc_atomic_fwush,
	.atomic_enabwe = wcdif_cwtc_atomic_enabwe,
	.atomic_disabwe = wcdif_cwtc_atomic_disabwe,
};

static const stwuct dwm_cwtc_funcs wcdif_cwtc_funcs = {
	.weset = wcdif_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = wcdif_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = wcdif_cwtc_atomic_destwoy_state,
	.enabwe_vbwank = wcdif_cwtc_enabwe_vbwank,
	.disabwe_vbwank = wcdif_cwtc_disabwe_vbwank,
};

/* -----------------------------------------------------------------------------
 * Pwanes
 */

static int wcdif_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state,
									     pwane);
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(pwane->dev);
	stwuct dwm_cwtc_state *cwtc_state;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state,
						   &wcdif->cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(pwane_state, cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   fawse, twue);
}

static void wcdif_pwane_pwimawy_atomic_update(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct wcdif_dwm_pwivate *wcdif = to_wcdif_dwm_pwivate(pwane->dev);
	stwuct dwm_pwane_state *new_pstate = dwm_atomic_get_new_pwane_state(state,
									    pwane);
	dma_addw_t paddw;

	paddw = dwm_fb_dma_get_gem_addw(new_pstate->fb, new_pstate, 0);
	if (paddw) {
		wwitew(wowew_32_bits(paddw),
		       wcdif->base + WCDC_V8_CTWWDESCW_WOW0_4);
		wwitew(CTWWDESCW_HIGH0_4_ADDW_HIGH(uppew_32_bits(paddw)),
		       wcdif->base + WCDC_V8_CTWWDESCW_HIGH0_4);
	}
}

static boow wcdif_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
				       uint32_t fowmat,
				       uint64_t modifiew)
{
	wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW;
}

static const stwuct dwm_pwane_hewpew_funcs wcdif_pwane_pwimawy_hewpew_funcs = {
	.atomic_check = wcdif_pwane_atomic_check,
	.atomic_update = wcdif_pwane_pwimawy_atomic_update,
};

static const stwuct dwm_pwane_funcs wcdif_pwane_funcs = {
	.fowmat_mod_suppowted	= wcdif_fowmat_mod_suppowted,
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
};

static const u32 wcdif_pwimawy_pwane_fowmats[] = {
	/* WGB */
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_XWGB8888,

	/* Packed YCbCw */
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
};

static const u64 wcdif_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

/* -----------------------------------------------------------------------------
 * Initiawization
 */

int wcdif_kms_init(stwuct wcdif_dwm_pwivate *wcdif)
{
	const u32 suppowted_encodings = BIT(DWM_COWOW_YCBCW_BT601) |
					BIT(DWM_COWOW_YCBCW_BT709) |
					BIT(DWM_COWOW_YCBCW_BT2020);
	const u32 suppowted_wanges = BIT(DWM_COWOW_YCBCW_WIMITED_WANGE) |
				     BIT(DWM_COWOW_YCBCW_FUWW_WANGE);
	stwuct dwm_cwtc *cwtc = &wcdif->cwtc;
	int wet;

	dwm_pwane_hewpew_add(&wcdif->pwanes.pwimawy,
			     &wcdif_pwane_pwimawy_hewpew_funcs);
	wet = dwm_univewsaw_pwane_init(wcdif->dwm, &wcdif->pwanes.pwimawy, 1,
				       &wcdif_pwane_funcs,
				       wcdif_pwimawy_pwane_fowmats,
				       AWWAY_SIZE(wcdif_pwimawy_pwane_fowmats),
				       wcdif_modifiews, DWM_PWANE_TYPE_PWIMAWY,
				       NUWW);
	if (wet)
		wetuwn wet;

	wet = dwm_pwane_cweate_cowow_pwopewties(&wcdif->pwanes.pwimawy,
						suppowted_encodings,
						suppowted_wanges,
						DWM_COWOW_YCBCW_BT601,
						DWM_COWOW_YCBCW_WIMITED_WANGE);
	if (wet)
		wetuwn wet;

	dwm_cwtc_hewpew_add(cwtc, &wcdif_cwtc_hewpew_funcs);
	wetuwn dwm_cwtc_init_with_pwanes(wcdif->dwm, cwtc,
					 &wcdif->pwanes.pwimawy, NUWW,
					 &wcdif_cwtc_funcs, NUWW);
}
