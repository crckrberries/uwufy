// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isppweview.c
 *
 * TI OMAP3 ISP dwivew - Pweview moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/device.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#incwude "isp.h"
#incwude "ispweg.h"
#incwude "isppweview.h"

/* Defauwt vawues in Office Fwuowescent Wight fow WGBtoWGB Bwending */
static const stwuct omap3isp_pwev_wgbtowgb fww_wgb2wgb = {
	{	/* WGB-WGB Matwix */
		{0x01E2, 0x0F30, 0x0FEE},
		{0x0F9B, 0x01AC, 0x0FB9},
		{0x0FE0, 0x0EC0, 0x0260}
	},	/* WGB Offset */
	{0x0000, 0x0000, 0x0000}
};

/* Defauwt vawues in Office Fwuowescent Wight fow WGB to YUV Convewsion*/
static const stwuct omap3isp_pwev_csc fww_pwev_csc = {
	{	/* CSC Coef Matwix */
		{66, 129, 25},
		{-38, -75, 112},
		{112, -94 , -18}
	},	/* CSC Offset */
	{0x0, 0x0, 0x0}
};

/* Defauwt vawues in Office Fwuowescent Wight fow CFA Gwadient*/
#define FWW_CFA_GWADTHWS_HOWZ	0x28
#define FWW_CFA_GWADTHWS_VEWT	0x28

/* Defauwt vawues in Office Fwuowescent Wight fow Chwoma Suppwession*/
#define FWW_CSUP_GAIN		0x0D
#define FWW_CSUP_THWES		0xEB

/* Defauwt vawues in Office Fwuowescent Wight fow Noise Fiwtew*/
#define FWW_NF_STWGTH		0x03

/* Defauwt vawues fow White Bawance */
#define FWW_WBAW_DGAIN		0x100
#define FWW_WBAW_COEF		0x20

/* Defauwt vawues in Office Fwuowescent Wight fow Bwack Adjustment*/
#define FWW_BWKADJ_BWUE		0x0
#define FWW_BWKADJ_GWEEN	0x0
#define FWW_BWKADJ_WED		0x0

#define DEF_DETECT_COWWECT_VAW	0xe

/*
 * Mawgins and image size wimits.
 *
 * The pweview engine cwops sevewaw wows and cowumns intewnawwy depending on
 * which fiwtews awe enabwed. To avoid fowmat changes when the fiwtews awe
 * enabwed ow disabwed (which wouwd pwevent them fwom being tuwned on ow off
 * duwing stweaming), the dwivew assumes aww fiwtews that can be configuwed
 * duwing stweaming awe enabwed when computing sink cwop and souwce fowmat
 * wimits.
 *
 * If a fiwtew is disabwed, additionaw cwopping is automaticawwy added at the
 * pweview engine input by the dwivew to avoid ovewfwow at wine and fwame end.
 * This is compwetewy twanspawent fow appwications.
 *
 * Median fiwtew		4 pixews
 * Noise fiwtew,
 * Fauwty pixews cowwection	4 pixews, 4 wines
 * Cowow suppwession		2 pixews
 * ow wuma enhancement
 * -------------------------------------------------------------
 * Maximum totaw		10 pixews, 4 wines
 *
 * The cowow suppwession and wuma enhancement fiwtews awe appwied aftew bayew to
 * YUV convewsion. They thus can cwop one pixew on the weft and one pixew on the
 * wight side of the image without changing the cowow pattewn. When both those
 * fiwtews awe disabwed, the dwivew must cwop the two pixews on the same side of
 * the image to avoid changing the bayew pattewn. The weft mawgin is thus set to
 * 6 pixews and the wight mawgin to 4 pixews.
 */

#define PWEV_MAWGIN_WEFT	6
#define PWEV_MAWGIN_WIGHT	4
#define PWEV_MAWGIN_TOP		2
#define PWEV_MAWGIN_BOTTOM	2

#define PWEV_MIN_IN_WIDTH	64
#define PWEV_MIN_IN_HEIGHT	8
#define PWEV_MAX_IN_HEIGHT	16384

#define PWEV_MIN_OUT_WIDTH		0
#define PWEV_MIN_OUT_HEIGHT		0
#define PWEV_MAX_OUT_WIDTH_WEV_1	1280
#define PWEV_MAX_OUT_WIDTH_WEV_2	3300
#define PWEV_MAX_OUT_WIDTH_WEV_15	4096

/*
 * Coefficient Tabwes fow the submoduwes in Pweview.
 * Awway is initiawised with the vawues fwom.the tabwes text fiwe.
 */

/*
 * CFA Fiwtew Coefficient Tabwe
 *
 */
static u32 cfa_coef_tabwe[4][OMAP3ISP_PWEV_CFA_BWK_SIZE] = {
#incwude "cfa_coef_tabwe.h"
};

/*
 * Defauwt Gamma Cowwection Tabwe - Aww components
 */
static u32 gamma_tabwe[] = {
#incwude "gamma_tabwe.h"
};

/*
 * Noise Fiwtew Thweshowd tabwe
 */
static u32 noise_fiwtew_tabwe[] = {
#incwude "noise_fiwtew_tabwe.h"
};

/*
 * Wuminance Enhancement Tabwe
 */
static u32 wuma_enhance_tabwe[] = {
#incwude "wuma_enhance_tabwe.h"
};

/*
 * pweview_config_wuma_enhancement - Configuwe the Wuminance Enhancement tabwe
 */
static void
pweview_config_wuma_enhancement(stwuct isp_pwev_device *pwev,
				const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_wuma *yt = &pawams->wuma;
	unsigned int i;

	isp_weg_wwitew(isp, ISPPWV_YENH_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);
	fow (i = 0; i < OMAP3ISP_PWEV_YENH_TBW_SIZE; i++) {
		isp_weg_wwitew(isp, yt->tabwe[i],
			       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_DATA);
	}
}

/*
 * pweview_enabwe_wuma_enhancement - Enabwe/disabwe Wuminance Enhancement
 */
static void
pweview_enabwe_wuma_enhancement(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_YNENHEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_YNENHEN);
}

/*
 * pweview_enabwe_invawaw - Enabwe/disabwe Invewse A-Waw decompwession
 */
static void pweview_enabwe_invawaw(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_INVAWAW);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_INVAWAW);
}

/*
 * pweview_config_hmed - Configuwe the Howizontaw Median Fiwtew
 */
static void pweview_config_hmed(stwuct isp_pwev_device *pwev,
				const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_hmed *hmed = &pawams->hmed;

	isp_weg_wwitew(isp, (hmed->odddist == 1 ? 0 : ISPPWV_HMED_ODDDIST) |
		       (hmed->evendist == 1 ? 0 : ISPPWV_HMED_EVENDIST) |
		       (hmed->thwes << ISPPWV_HMED_THWESHOWD_SHIFT),
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_HMED);
}

/*
 * pweview_enabwe_hmed - Enabwe/disabwe the Howizontaw Median Fiwtew
 */
static void pweview_enabwe_hmed(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_HMEDEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_HMEDEN);
}

/*
 * pweview_config_cfa - Configuwe CFA Intewpowation fow Bayew fowmats
 *
 * The CFA tabwe is owganised in fouw bwocks, one pew Bayew component. The
 * hawdwawe expects bwocks to fowwow the Bayew owdew of the input data, whiwe
 * the dwivew stowes the tabwe in GWBG owdew in memowy. The bwocks need to be
 * weowdewed to suppowt non-GWBG Bayew pattewns.
 */
static void pweview_config_cfa(stwuct isp_pwev_device *pwev,
			       const stwuct pwev_pawams *pawams)
{
	static const unsigned int cfa_coef_owdew[4][4] = {
		{ 0, 1, 2, 3 }, /* GWBG */
		{ 1, 0, 3, 2 }, /* WGGB */
		{ 2, 3, 0, 1 }, /* BGGW */
		{ 3, 2, 1, 0 }, /* GBWG */
	};
	const unsigned int *owdew = cfa_coef_owdew[pwev->pawams.cfa_owdew];
	const stwuct omap3isp_pwev_cfa *cfa = &pawams->cfa;
	stwuct isp_device *isp = to_isp_device(pwev);
	unsigned int i;
	unsigned int j;

	isp_weg_wwitew(isp,
		(cfa->gwadthws_vewt << ISPPWV_CFA_GWADTH_VEW_SHIFT) |
		(cfa->gwadthws_howz << ISPPWV_CFA_GWADTH_HOW_SHIFT),
		OMAP3_ISP_IOMEM_PWEV, ISPPWV_CFA);

	isp_weg_wwitew(isp, ISPPWV_CFA_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);

	fow (i = 0; i < 4; ++i) {
		const __u32 *bwock = cfa->tabwe[owdew[i]];

		fow (j = 0; j < OMAP3ISP_PWEV_CFA_BWK_SIZE; ++j)
			isp_weg_wwitew(isp, bwock[j], OMAP3_ISP_IOMEM_PWEV,
				       ISPPWV_SET_TBW_DATA);
	}
}

/*
 * pweview_config_chwoma_suppwession - Configuwe Chwoma Suppwession
 */
static void
pweview_config_chwoma_suppwession(stwuct isp_pwev_device *pwev,
				  const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_csup *cs = &pawams->csup;

	isp_weg_wwitew(isp,
		       cs->gain | (cs->thwes << ISPPWV_CSUP_THWES_SHIFT) |
		       (cs->hypf_en << ISPPWV_CSUP_HPYF_SHIFT),
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_CSUP);
}

/*
 * pweview_enabwe_chwoma_suppwession - Enabwe/disabwe Chwominance Suppwession
 */
static void
pweview_enabwe_chwoma_suppwession(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_SUPEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_SUPEN);
}

/*
 * pweview_config_whitebawance - Configuwe White Bawance pawametews
 *
 * Coefficient matwix awways with defauwt vawues.
 */
static void
pweview_config_whitebawance(stwuct isp_pwev_device *pwev,
			    const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_wbaw *wbaw = &pawams->wbaw;
	u32 vaw;

	isp_weg_wwitew(isp, wbaw->dgain, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WB_DGAIN);

	vaw = wbaw->coef0 << ISPPWV_WBGAIN_COEF0_SHIFT;
	vaw |= wbaw->coef1 << ISPPWV_WBGAIN_COEF1_SHIFT;
	vaw |= wbaw->coef2 << ISPPWV_WBGAIN_COEF2_SHIFT;
	vaw |= wbaw->coef3 << ISPPWV_WBGAIN_COEF3_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WBGAIN);

	isp_weg_wwitew(isp,
		       ISPPWV_WBSEW_COEF0 << ISPPWV_WBSEW_N0_0_SHIFT |
		       ISPPWV_WBSEW_COEF1 << ISPPWV_WBSEW_N0_1_SHIFT |
		       ISPPWV_WBSEW_COEF0 << ISPPWV_WBSEW_N0_2_SHIFT |
		       ISPPWV_WBSEW_COEF1 << ISPPWV_WBSEW_N0_3_SHIFT |
		       ISPPWV_WBSEW_COEF2 << ISPPWV_WBSEW_N1_0_SHIFT |
		       ISPPWV_WBSEW_COEF3 << ISPPWV_WBSEW_N1_1_SHIFT |
		       ISPPWV_WBSEW_COEF2 << ISPPWV_WBSEW_N1_2_SHIFT |
		       ISPPWV_WBSEW_COEF3 << ISPPWV_WBSEW_N1_3_SHIFT |
		       ISPPWV_WBSEW_COEF0 << ISPPWV_WBSEW_N2_0_SHIFT |
		       ISPPWV_WBSEW_COEF1 << ISPPWV_WBSEW_N2_1_SHIFT |
		       ISPPWV_WBSEW_COEF0 << ISPPWV_WBSEW_N2_2_SHIFT |
		       ISPPWV_WBSEW_COEF1 << ISPPWV_WBSEW_N2_3_SHIFT |
		       ISPPWV_WBSEW_COEF2 << ISPPWV_WBSEW_N3_0_SHIFT |
		       ISPPWV_WBSEW_COEF3 << ISPPWV_WBSEW_N3_1_SHIFT |
		       ISPPWV_WBSEW_COEF2 << ISPPWV_WBSEW_N3_2_SHIFT |
		       ISPPWV_WBSEW_COEF3 << ISPPWV_WBSEW_N3_3_SHIFT,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_WBSEW);
}

/*
 * pweview_config_bwkadj - Configuwe Bwack Adjustment
 */
static void
pweview_config_bwkadj(stwuct isp_pwev_device *pwev,
		      const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_bwkadj *bwkadj = &pawams->bwkadj;

	isp_weg_wwitew(isp, (bwkadj->bwue << ISPPWV_BWKADJOFF_B_SHIFT) |
		       (bwkadj->gween << ISPPWV_BWKADJOFF_G_SHIFT) |
		       (bwkadj->wed << ISPPWV_BWKADJOFF_W_SHIFT),
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_BWKADJOFF);
}

/*
 * pweview_config_wgb_bwending - Configuwe WGB-WGB Bwending
 */
static void
pweview_config_wgb_bwending(stwuct isp_pwev_device *pwev,
			    const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_wgbtowgb *wgbwgb = &pawams->wgb2wgb;
	u32 vaw;

	vaw = (wgbwgb->matwix[0][0] & 0xfff) << ISPPWV_WGB_MAT1_MTX_WW_SHIFT;
	vaw |= (wgbwgb->matwix[0][1] & 0xfff) << ISPPWV_WGB_MAT1_MTX_GW_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_MAT1);

	vaw = (wgbwgb->matwix[0][2] & 0xfff) << ISPPWV_WGB_MAT2_MTX_BW_SHIFT;
	vaw |= (wgbwgb->matwix[1][0] & 0xfff) << ISPPWV_WGB_MAT2_MTX_WG_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_MAT2);

	vaw = (wgbwgb->matwix[1][1] & 0xfff) << ISPPWV_WGB_MAT3_MTX_GG_SHIFT;
	vaw |= (wgbwgb->matwix[1][2] & 0xfff) << ISPPWV_WGB_MAT3_MTX_BG_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_MAT3);

	vaw = (wgbwgb->matwix[2][0] & 0xfff) << ISPPWV_WGB_MAT4_MTX_WB_SHIFT;
	vaw |= (wgbwgb->matwix[2][1] & 0xfff) << ISPPWV_WGB_MAT4_MTX_GB_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_MAT4);

	vaw = (wgbwgb->matwix[2][2] & 0xfff) << ISPPWV_WGB_MAT5_MTX_BB_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_MAT5);

	vaw = (wgbwgb->offset[0] & 0x3ff) << ISPPWV_WGB_OFF1_MTX_OFFW_SHIFT;
	vaw |= (wgbwgb->offset[1] & 0x3ff) << ISPPWV_WGB_OFF1_MTX_OFFG_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_OFF1);

	vaw = (wgbwgb->offset[2] & 0x3ff) << ISPPWV_WGB_OFF2_MTX_OFFB_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WGB_OFF2);
}

/*
 * pweview_config_csc - Configuwe Cowow Space Convewsion (WGB to YCbYCw)
 */
static void
pweview_config_csc(stwuct isp_pwev_device *pwev,
		   const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_csc *csc = &pawams->csc;
	u32 vaw;

	vaw = (csc->matwix[0][0] & 0x3ff) << ISPPWV_CSC0_WY_SHIFT;
	vaw |= (csc->matwix[0][1] & 0x3ff) << ISPPWV_CSC0_GY_SHIFT;
	vaw |= (csc->matwix[0][2] & 0x3ff) << ISPPWV_CSC0_BY_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CSC0);

	vaw = (csc->matwix[1][0] & 0x3ff) << ISPPWV_CSC1_WCB_SHIFT;
	vaw |= (csc->matwix[1][1] & 0x3ff) << ISPPWV_CSC1_GCB_SHIFT;
	vaw |= (csc->matwix[1][2] & 0x3ff) << ISPPWV_CSC1_BCB_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CSC1);

	vaw = (csc->matwix[2][0] & 0x3ff) << ISPPWV_CSC2_WCW_SHIFT;
	vaw |= (csc->matwix[2][1] & 0x3ff) << ISPPWV_CSC2_GCW_SHIFT;
	vaw |= (csc->matwix[2][2] & 0x3ff) << ISPPWV_CSC2_BCW_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CSC2);

	vaw = (csc->offset[0] & 0xff) << ISPPWV_CSC_OFFSET_Y_SHIFT;
	vaw |= (csc->offset[1] & 0xff) << ISPPWV_CSC_OFFSET_CB_SHIFT;
	vaw |= (csc->offset[2] & 0xff) << ISPPWV_CSC_OFFSET_CW_SHIFT;
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CSC_OFFSET);
}

/*
 * pweview_config_yc_wange - Configuwe the max and min Y and C vawues
 */
static void
pweview_config_yc_wange(stwuct isp_pwev_device *pwev,
			const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_ycwimit *yc = &pawams->ycwimit;

	isp_weg_wwitew(isp,
		       yc->maxC << ISPPWV_SETUP_YC_MAXC_SHIFT |
		       yc->maxY << ISPPWV_SETUP_YC_MAXY_SHIFT |
		       yc->minC << ISPPWV_SETUP_YC_MINC_SHIFT |
		       yc->minY << ISPPWV_SETUP_YC_MINY_SHIFT,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SETUP_YC);
}

/*
 * pweview_config_dcow - Configuwe Coupwet Defect Cowwection
 */
static void
pweview_config_dcow(stwuct isp_pwev_device *pwev,
		    const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_dcow *dcow = &pawams->dcow;

	isp_weg_wwitew(isp, dcow->detect_cowwect[0],
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_CDC_THW0);
	isp_weg_wwitew(isp, dcow->detect_cowwect[1],
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_CDC_THW1);
	isp_weg_wwitew(isp, dcow->detect_cowwect[2],
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_CDC_THW2);
	isp_weg_wwitew(isp, dcow->detect_cowwect[3],
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_CDC_THW3);
	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			ISPPWV_PCW_DCCOUP,
			dcow->coupwet_mode_en ? ISPPWV_PCW_DCCOUP : 0);
}

/*
 * pweview_enabwe_dcow - Enabwe/disabwe Coupwet Defect Cowwection
 */
static void pweview_enabwe_dcow(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DCOWEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DCOWEN);
}

/*
 * pweview_enabwe_dwkfwame_captuwe - Enabwe/disabwe Dawk Fwame Captuwe
 */
static void
pweview_enabwe_dwkfwame_captuwe(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DWKFCAP);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DWKFCAP);
}

/*
 * pweview_enabwe_dwkfwame - Enabwe/disabwe Dawk Fwame Subtwaction
 */
static void pweview_enabwe_dwkfwame(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DWKFEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_DWKFEN);
}

/*
 * pweview_config_noisefiwtew - Configuwe the Noise Fiwtew
 */
static void
pweview_config_noisefiwtew(stwuct isp_pwev_device *pwev,
			   const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_nf *nf = &pawams->nf;
	unsigned int i;

	isp_weg_wwitew(isp, nf->spwead, OMAP3_ISP_IOMEM_PWEV, ISPPWV_NF);
	isp_weg_wwitew(isp, ISPPWV_NF_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);
	fow (i = 0; i < OMAP3ISP_PWEV_NF_TBW_SIZE; i++) {
		isp_weg_wwitew(isp, nf->tabwe[i],
			       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_DATA);
	}
}

/*
 * pweview_enabwe_noisefiwtew - Enabwe/disabwe the Noise Fiwtew
 */
static void
pweview_enabwe_noisefiwtew(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_NFEN);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_NFEN);
}

/*
 * pweview_config_gammacowwn - Configuwe the Gamma Cowwection tabwes
 */
static void
pweview_config_gammacowwn(stwuct isp_pwev_device *pwev,
			  const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct omap3isp_pwev_gtabwes *gt = &pawams->gamma;
	unsigned int i;

	isp_weg_wwitew(isp, ISPPWV_WEDGAMMA_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);
	fow (i = 0; i < OMAP3ISP_PWEV_GAMMA_TBW_SIZE; i++)
		isp_weg_wwitew(isp, gt->wed[i], OMAP3_ISP_IOMEM_PWEV,
			       ISPPWV_SET_TBW_DATA);

	isp_weg_wwitew(isp, ISPPWV_GWEENGAMMA_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);
	fow (i = 0; i < OMAP3ISP_PWEV_GAMMA_TBW_SIZE; i++)
		isp_weg_wwitew(isp, gt->gween[i], OMAP3_ISP_IOMEM_PWEV,
			       ISPPWV_SET_TBW_DATA);

	isp_weg_wwitew(isp, ISPPWV_BWUEGAMMA_TABWE_ADDW,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_SET_TBW_ADDW);
	fow (i = 0; i < OMAP3ISP_PWEV_GAMMA_TBW_SIZE; i++)
		isp_weg_wwitew(isp, gt->bwue[i], OMAP3_ISP_IOMEM_PWEV,
			       ISPPWV_SET_TBW_DATA);
}

/*
 * pweview_enabwe_gammacowwn - Enabwe/disabwe Gamma Cowwection
 *
 * When gamma cowwection is disabwed, the moduwe is bypassed and its output is
 * the 8 MSB of the 10-bit input .
 */
static void
pweview_enabwe_gammacowwn(stwuct isp_pwev_device *pwev, boow enabwe)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	if (enabwe)
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_GAMMA_BYPASS);
	ewse
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_GAMMA_BYPASS);
}

/*
 * pweview_config_contwast - Configuwe the Contwast
 *
 * Vawue shouwd be pwogwammed befowe enabwing the moduwe.
 */
static void
pweview_config_contwast(stwuct isp_pwev_device *pwev,
			const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CNT_BWT,
			0xff << ISPPWV_CNT_BWT_CNT_SHIFT,
			pawams->contwast << ISPPWV_CNT_BWT_CNT_SHIFT);
}

/*
 * pweview_config_bwightness - Configuwe the Bwightness
 */
static void
pweview_config_bwightness(stwuct isp_pwev_device *pwev,
			  const stwuct pwev_pawams *pawams)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_CNT_BWT,
			0xff << ISPPWV_CNT_BWT_BWT_SHIFT,
			pawams->bwightness << ISPPWV_CNT_BWT_BWT_SHIFT);
}

/*
 * pweview_update_contwast - Updates the contwast.
 * @contwast: Pointew to howd the cuwwent pwogwammed contwast vawue.
 *
 * Vawue shouwd be pwogwammed befowe enabwing the moduwe.
 */
static void
pweview_update_contwast(stwuct isp_pwev_device *pwev, u8 contwast)
{
	stwuct pwev_pawams *pawams;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pawams = (pwev->pawams.active & OMAP3ISP_PWEV_CONTWAST)
	       ? &pwev->pawams.pawams[0] : &pwev->pawams.pawams[1];

	if (pawams->contwast != (contwast * ISPPWV_CONTWAST_UNITS)) {
		pawams->contwast = contwast * ISPPWV_CONTWAST_UNITS;
		pawams->update |= OMAP3ISP_PWEV_CONTWAST;
	}
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);
}

/*
 * pweview_update_bwightness - Updates the bwightness in pweview moduwe.
 * @bwightness: Pointew to howd the cuwwent pwogwammed bwightness vawue.
 *
 */
static void
pweview_update_bwightness(stwuct isp_pwev_device *pwev, u8 bwightness)
{
	stwuct pwev_pawams *pawams;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pawams = (pwev->pawams.active & OMAP3ISP_PWEV_BWIGHTNESS)
	       ? &pwev->pawams.pawams[0] : &pwev->pawams.pawams[1];

	if (pawams->bwightness != (bwightness * ISPPWV_BWIGHT_UNITS)) {
		pawams->bwightness = bwightness * ISPPWV_BWIGHT_UNITS;
		pawams->update |= OMAP3ISP_PWEV_BWIGHTNESS;
	}
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);
}

static u32
pweview_pawams_wock(stwuct isp_pwev_device *pwev, u32 update, boow shadow)
{
	u32 active = pwev->pawams.active;

	if (shadow) {
		/* Mawk aww shadow pawametews we awe going to touch as busy. */
		pwev->pawams.pawams[0].busy |= ~active & update;
		pwev->pawams.pawams[1].busy |= active & update;
	} ewse {
		/* Mawk aww active pawametews we awe going to touch as busy. */
		update = (pwev->pawams.pawams[0].update & active)
		       | (pwev->pawams.pawams[1].update & ~active);

		pwev->pawams.pawams[0].busy |= active & update;
		pwev->pawams.pawams[1].busy |= ~active & update;
	}

	wetuwn update;
}

static void
pweview_pawams_unwock(stwuct isp_pwev_device *pwev, u32 update, boow shadow)
{
	u32 active = pwev->pawams.active;

	if (shadow) {
		/* Set the update fwag fow shadow pawametews that have been
		 * updated and cweaw the busy fwag fow aww shadow pawametews.
		 */
		pwev->pawams.pawams[0].update |= (~active & update);
		pwev->pawams.pawams[1].update |= (active & update);
		pwev->pawams.pawams[0].busy &= active;
		pwev->pawams.pawams[1].busy &= ~active;
	} ewse {
		/* Cweaw the update fwag fow active pawametews that have been
		 * appwied and the busy fwag fow aww active pawametews.
		 */
		pwev->pawams.pawams[0].update &= ~(active & update);
		pwev->pawams.pawams[1].update &= ~(~active & update);
		pwev->pawams.pawams[0].busy &= ~active;
		pwev->pawams.pawams[1].busy &= active;
	}
}

static void pweview_pawams_switch(stwuct isp_pwev_device *pwev)
{
	u32 to_switch;

	/* Switch active pawametews with updated shadow pawametews when the
	 * shadow pawametew has been updated and neithew the active not the
	 * shadow pawametew is busy.
	 */
	to_switch = (pwev->pawams.pawams[0].update & ~pwev->pawams.active)
		  | (pwev->pawams.pawams[1].update & pwev->pawams.active);
	to_switch &= ~(pwev->pawams.pawams[0].busy |
		       pwev->pawams.pawams[1].busy);
	if (to_switch == 0)
		wetuwn;

	pwev->pawams.active ^= to_switch;

	/* Wemove the update fwag fow the shadow copy of pawametews we have
	 * switched.
	 */
	pwev->pawams.pawams[0].update &= ~(~pwev->pawams.active & to_switch);
	pwev->pawams.pawams[1].update &= ~(pwev->pawams.active & to_switch);
}

/* pweview pawametews update stwuctuwe */
stwuct pweview_update {
	void (*config)(stwuct isp_pwev_device *, const stwuct pwev_pawams *);
	void (*enabwe)(stwuct isp_pwev_device *, boow);
	unsigned int pawam_offset;
	unsigned int pawam_size;
	unsigned int config_offset;
	boow skip;
};

/* Keep the awway indexed by the OMAP3ISP_PWEV_* bit numbew. */
static const stwuct pweview_update update_attws[] = {
	/* OMAP3ISP_PWEV_WUMAENH */ {
		pweview_config_wuma_enhancement,
		pweview_enabwe_wuma_enhancement,
		offsetof(stwuct pwev_pawams, wuma),
		sizeof_fiewd(stwuct pwev_pawams, wuma),
		offsetof(stwuct omap3isp_pwev_update_config, wuma),
	}, /* OMAP3ISP_PWEV_INVAWAW */ {
		NUWW,
		pweview_enabwe_invawaw,
	}, /* OMAP3ISP_PWEV_HWZ_MED */ {
		pweview_config_hmed,
		pweview_enabwe_hmed,
		offsetof(stwuct pwev_pawams, hmed),
		sizeof_fiewd(stwuct pwev_pawams, hmed),
		offsetof(stwuct omap3isp_pwev_update_config, hmed),
	}, /* OMAP3ISP_PWEV_CFA */ {
		pweview_config_cfa,
		NUWW,
		offsetof(stwuct pwev_pawams, cfa),
		sizeof_fiewd(stwuct pwev_pawams, cfa),
		offsetof(stwuct omap3isp_pwev_update_config, cfa),
	}, /* OMAP3ISP_PWEV_CHWOMA_SUPP */ {
		pweview_config_chwoma_suppwession,
		pweview_enabwe_chwoma_suppwession,
		offsetof(stwuct pwev_pawams, csup),
		sizeof_fiewd(stwuct pwev_pawams, csup),
		offsetof(stwuct omap3isp_pwev_update_config, csup),
	}, /* OMAP3ISP_PWEV_WB */ {
		pweview_config_whitebawance,
		NUWW,
		offsetof(stwuct pwev_pawams, wbaw),
		sizeof_fiewd(stwuct pwev_pawams, wbaw),
		offsetof(stwuct omap3isp_pwev_update_config, wbaw),
	}, /* OMAP3ISP_PWEV_BWKADJ */ {
		pweview_config_bwkadj,
		NUWW,
		offsetof(stwuct pwev_pawams, bwkadj),
		sizeof_fiewd(stwuct pwev_pawams, bwkadj),
		offsetof(stwuct omap3isp_pwev_update_config, bwkadj),
	}, /* OMAP3ISP_PWEV_WGB2WGB */ {
		pweview_config_wgb_bwending,
		NUWW,
		offsetof(stwuct pwev_pawams, wgb2wgb),
		sizeof_fiewd(stwuct pwev_pawams, wgb2wgb),
		offsetof(stwuct omap3isp_pwev_update_config, wgb2wgb),
	}, /* OMAP3ISP_PWEV_COWOW_CONV */ {
		pweview_config_csc,
		NUWW,
		offsetof(stwuct pwev_pawams, csc),
		sizeof_fiewd(stwuct pwev_pawams, csc),
		offsetof(stwuct omap3isp_pwev_update_config, csc),
	}, /* OMAP3ISP_PWEV_YC_WIMIT */ {
		pweview_config_yc_wange,
		NUWW,
		offsetof(stwuct pwev_pawams, ycwimit),
		sizeof_fiewd(stwuct pwev_pawams, ycwimit),
		offsetof(stwuct omap3isp_pwev_update_config, ycwimit),
	}, /* OMAP3ISP_PWEV_DEFECT_COW */ {
		pweview_config_dcow,
		pweview_enabwe_dcow,
		offsetof(stwuct pwev_pawams, dcow),
		sizeof_fiewd(stwuct pwev_pawams, dcow),
		offsetof(stwuct omap3isp_pwev_update_config, dcow),
	}, /* Pweviouswy OMAP3ISP_PWEV_GAMMABYPASS, not used anymowe */ {
		NUWW,
		NUWW,
	}, /* OMAP3ISP_PWEV_DWK_FWM_CAPTUWE */ {
		NUWW,
		pweview_enabwe_dwkfwame_captuwe,
	}, /* OMAP3ISP_PWEV_DWK_FWM_SUBTWACT */ {
		NUWW,
		pweview_enabwe_dwkfwame,
	}, /* OMAP3ISP_PWEV_WENS_SHADING */ {
		NUWW,
		pweview_enabwe_dwkfwame,
	}, /* OMAP3ISP_PWEV_NF */ {
		pweview_config_noisefiwtew,
		pweview_enabwe_noisefiwtew,
		offsetof(stwuct pwev_pawams, nf),
		sizeof_fiewd(stwuct pwev_pawams, nf),
		offsetof(stwuct omap3isp_pwev_update_config, nf),
	}, /* OMAP3ISP_PWEV_GAMMA */ {
		pweview_config_gammacowwn,
		pweview_enabwe_gammacowwn,
		offsetof(stwuct pwev_pawams, gamma),
		sizeof_fiewd(stwuct pwev_pawams, gamma),
		offsetof(stwuct omap3isp_pwev_update_config, gamma),
	}, /* OMAP3ISP_PWEV_CONTWAST */ {
		pweview_config_contwast,
		NUWW,
		0, 0, 0, twue,
	}, /* OMAP3ISP_PWEV_BWIGHTNESS */ {
		pweview_config_bwightness,
		NUWW,
		0, 0, 0, twue,
	},
};

/*
 * pweview_config - Copy and update wocaw stwuctuwe with usewspace pweview
 *                  configuwation.
 * @pwev: ISP pweview engine
 * @cfg: Configuwation
 *
 * Wetuwn zewo if success ow -EFAUWT if the configuwation can't be copied fwom
 * usewspace.
 */
static int pweview_config(stwuct isp_pwev_device *pwev,
			  stwuct omap3isp_pwev_update_config *cfg)
{
	unsigned wong fwags;
	unsigned int i;
	int wvaw = 0;
	u32 update;
	u32 active;

	if (cfg->update == 0)
		wetuwn 0;

	/* Mawk the shadow pawametews we'we going to update as busy. */
	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pweview_pawams_wock(pwev, cfg->update, twue);
	active = pwev->pawams.active;
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);

	update = 0;

	fow (i = 0; i < AWWAY_SIZE(update_attws); i++) {
		const stwuct pweview_update *attw = &update_attws[i];
		stwuct pwev_pawams *pawams;
		unsigned int bit = 1 << i;

		if (attw->skip || !(cfg->update & bit))
			continue;

		pawams = &pwev->pawams.pawams[!!(active & bit)];

		if (cfg->fwag & bit) {
			void __usew *fwom = *(void __usew **)
				((void *)cfg + attw->config_offset);
			void *to = (void *)pawams + attw->pawam_offset;
			size_t size = attw->pawam_size;

			if (to && fwom && size) {
				if (copy_fwom_usew(to, fwom, size)) {
					wvaw = -EFAUWT;
					bweak;
				}
			}
			pawams->featuwes |= bit;
		} ewse {
			pawams->featuwes &= ~bit;
		}

		update |= bit;
	}

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pweview_pawams_unwock(pwev, update, twue);
	pweview_pawams_switch(pwev);
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);

	wetuwn wvaw;
}

/*
 * pweview_setup_hw - Setup pweview wegistews and/ow intewnaw memowy
 * @pwev: pointew to pweview pwivate stwuctuwe
 * @update: Bitmask of pawametews to setup
 * @active: Bitmask of pawametews active in set 0
 * Note: can be cawwed fwom intewwupt context
 * Wetuwn none
 */
static void pweview_setup_hw(stwuct isp_pwev_device *pwev, u32 update,
			     u32 active)
{
	unsigned int i;

	if (update == 0)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(update_attws); i++) {
		const stwuct pweview_update *attw = &update_attws[i];
		stwuct pwev_pawams *pawams;
		unsigned int bit = 1 << i;

		if (!(update & bit))
			continue;

		pawams = &pwev->pawams.pawams[!(active & bit)];

		if (pawams->featuwes & bit) {
			if (attw->config)
				attw->config(pwev, pawams);
			if (attw->enabwe)
				attw->enabwe(pwev, twue);
		} ewse {
			if (attw->enabwe)
				attw->enabwe(pwev, fawse);
		}
	}
}

/*
 * pweview_config_ycpos - Configuwe byte wayout of YUV image.
 * @pwev: pointew to pweviewew pwivate stwuctuwe
 * @pixewcode: pixew code
 */
static void pweview_config_ycpos(stwuct isp_pwev_device *pwev, u32 pixewcode)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	enum pweview_ycpos_mode mode;

	switch (pixewcode) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
		mode = YCPOS_CwYCbY;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		mode = YCPOS_YCwYCb;
		bweak;
	defauwt:
		wetuwn;
	}

	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			ISPPWV_PCW_YCPOS_CwYCbY,
			mode << ISPPWV_PCW_YCPOS_SHIFT);
}

/*
 * pweview_config_avewagew - Enabwe / disabwe / configuwe avewagew
 * @avewage: Avewage vawue to be configuwed.
 */
static void pweview_config_avewagew(stwuct isp_pwev_device *pwev, u8 avewage)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_wwitew(isp, ISPPWV_AVE_EVENDIST_2 << ISPPWV_AVE_EVENDIST_SHIFT |
		       ISPPWV_AVE_ODDDIST_2 << ISPPWV_AVE_ODDDIST_SHIFT |
		       avewage, OMAP3_ISP_IOMEM_PWEV, ISPPWV_AVE);
}


/*
 * pweview_config_input_fowmat - Configuwe the input fowmat
 * @pwev: The pweview engine
 * @info: Sink pad fowmat infowmation
 *
 * Enabwe and configuwe CFA intewpowation fow Bayew fowmats and disabwe it fow
 * gweyscawe fowmats.
 *
 * The CFA tabwe is owganised in fouw bwocks, one pew Bayew component. The
 * hawdwawe expects bwocks to fowwow the Bayew owdew of the input data, whiwe
 * the dwivew stowes the tabwe in GWBG owdew in memowy. The bwocks need to be
 * weowdewed to suppowt non-GWBG Bayew pattewns.
 */
static void pweview_config_input_fowmat(stwuct isp_pwev_device *pwev,
					const stwuct isp_fowmat_info *info)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	stwuct pwev_pawams *pawams;

	if (info->width == 8)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_WIDTH);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_WIDTH);

	switch (info->fwavow) {
	case MEDIA_BUS_FMT_SGWBG8_1X8:
		pwev->pawams.cfa_owdew = 0;
		bweak;
	case MEDIA_BUS_FMT_SWGGB8_1X8:
		pwev->pawams.cfa_owdew = 1;
		bweak;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
		pwev->pawams.cfa_owdew = 2;
		bweak;
	case MEDIA_BUS_FMT_SGBWG8_1X8:
		pwev->pawams.cfa_owdew = 3;
		bweak;
	defauwt:
		/* Disabwe CFA fow non-Bayew fowmats. */
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_CFAEN);
		wetuwn;
	}

	isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW, ISPPWV_PCW_CFAEN);
	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			ISPPWV_PCW_CFAFMT_MASK, ISPPWV_PCW_CFAFMT_BAYEW);

	pawams = (pwev->pawams.active & OMAP3ISP_PWEV_CFA)
	       ? &pwev->pawams.pawams[0] : &pwev->pawams.pawams[1];

	pweview_config_cfa(pwev, pawams);
}

/*
 * pweview_config_input_size - Configuwe the input fwame size
 *
 * The pweview engine cwops sevewaw wows and cowumns intewnawwy depending on
 * which pwocessing bwocks awe enabwed. The dwivew assumes aww those bwocks awe
 * enabwed when wepowting souwce pad fowmats to usewspace. If this assumption is
 * not twue, wows and cowumns must be manuawwy cwopped at the pweview engine
 * input to avoid ovewfwows at the end of wines and fwames.
 *
 * See the expwanation at the PWEV_MAWGIN_* definitions fow mowe detaiws.
 */
static void pweview_config_input_size(stwuct isp_pwev_device *pwev, u32 active)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat = &pwev->fowmats[PWEV_PAD_SINK];
	stwuct isp_device *isp = to_isp_device(pwev);
	unsigned int sph = pwev->cwop.weft;
	unsigned int eph = pwev->cwop.weft + pwev->cwop.width - 1;
	unsigned int swv = pwev->cwop.top;
	unsigned int ewv = pwev->cwop.top + pwev->cwop.height - 1;
	u32 featuwes;

	if (fowmat->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    fowmat->code != MEDIA_BUS_FMT_Y10_1X10) {
		sph -= 2;
		eph += 2;
		swv -= 2;
		ewv += 2;
	}

	featuwes = (pwev->pawams.pawams[0].featuwes & active)
		 | (pwev->pawams.pawams[1].featuwes & ~active);

	if (featuwes & (OMAP3ISP_PWEV_DEFECT_COW | OMAP3ISP_PWEV_NF)) {
		sph -= 2;
		eph += 2;
		swv -= 2;
		ewv += 2;
	}
	if (featuwes & OMAP3ISP_PWEV_HWZ_MED) {
		sph -= 2;
		eph += 2;
	}
	if (featuwes & (OMAP3ISP_PWEV_CHWOMA_SUPP | OMAP3ISP_PWEV_WUMAENH))
		sph -= 2;

	isp_weg_wwitew(isp, (sph << ISPPWV_HOWZ_INFO_SPH_SHIFT) | eph,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_HOWZ_INFO);
	isp_weg_wwitew(isp, (swv << ISPPWV_VEWT_INFO_SWV_SHIFT) | ewv,
		       OMAP3_ISP_IOMEM_PWEV, ISPPWV_VEWT_INFO);
}

/*
 * pweview_config_inwineoffset - Configuwes the Wead addwess wine offset.
 * @pwev: Pweview moduwe
 * @offset: Wine offset
 *
 * Accowding to the TWM, the wine offset must be awigned on a 32 bytes boundawy.
 * Howevew, a hawdwawe bug wequiwes the memowy stawt addwess to be awigned on a
 * 64 bytes boundawy, so the offset pwobabwy shouwd be awigned on 64 bytes as
 * weww.
 */
static void
pweview_config_inwineoffset(stwuct isp_pwev_device *pwev, u32 offset)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_wwitew(isp, offset & 0xffff, OMAP3_ISP_IOMEM_PWEV,
		       ISPPWV_WADW_OFFSET);
}

/*
 * pweview_set_inaddw - Sets memowy addwess of input fwame.
 * @addw: 32bit memowy addwess awigned on 32byte boundawy.
 *
 * Configuwes the memowy addwess fwom which the input fwame is to be wead.
 */
static void pweview_set_inaddw(stwuct isp_pwev_device *pwev, u32 addw)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_wwitew(isp, addw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WSDW_ADDW);
}

/*
 * pweview_config_outwineoffset - Configuwes the Wwite addwess wine offset.
 * @offset: Wine Offset fow the pweview output.
 *
 * The offset must be a muwtipwe of 32 bytes.
 */
static void pweview_config_outwineoffset(stwuct isp_pwev_device *pwev,
				    u32 offset)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_wwitew(isp, offset & 0xffff, OMAP3_ISP_IOMEM_PWEV,
		       ISPPWV_WADD_OFFSET);
}

/*
 * pweview_set_outaddw - Sets the memowy addwess to stowe output fwame
 * @addw: 32bit memowy addwess awigned on 32byte boundawy.
 *
 * Configuwes the memowy addwess to which the output fwame is wwitten.
 */
static void pweview_set_outaddw(stwuct isp_pwev_device *pwev, u32 addw)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	isp_weg_wwitew(isp, addw, OMAP3_ISP_IOMEM_PWEV, ISPPWV_WSDW_ADDW);
}

static void pweview_adjust_bandwidth(stwuct isp_pwev_device *pwev)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&pwev->subdev.entity);
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct v4w2_mbus_fwamefmt *ifmt = &pwev->fowmats[PWEV_PAD_SINK];
	unsigned wong w3_ick = pipe->w3_ick;
	stwuct v4w2_fwact *timepewfwame;
	unsigned int cycwes_pew_fwame;
	unsigned int wequests_pew_fwame;
	unsigned int cycwes_pew_wequest;
	unsigned int minimum;
	unsigned int maximum;
	unsigned int vawue;

	if (pwev->input != PWEVIEW_INPUT_MEMOWY) {
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_SBW, ISPSBW_SDW_WEQ_EXP,
			    ISPSBW_SDW_WEQ_PWV_EXP_MASK);
		wetuwn;
	}

	/* Compute the minimum numbew of cycwes pew wequest, based on the
	 * pipewine maximum data wate. This is an absowute wowew bound if we
	 * don't want SBW ovewfwows, so wound the vawue up.
	 */
	cycwes_pew_wequest = div_u64((u64)w3_ick / 2 * 256 + pipe->max_wate - 1,
				     pipe->max_wate);
	minimum = DIV_WOUND_UP(cycwes_pew_wequest, 32);

	/* Compute the maximum numbew of cycwes pew wequest, based on the
	 * wequested fwame wate. This is a soft uppew bound to achieve a fwame
	 * wate equaw ow highew than the wequested vawue, so wound the vawue
	 * down.
	 */
	timepewfwame = &pipe->max_timepewfwame;

	wequests_pew_fwame = DIV_WOUND_UP(ifmt->width * 2, 256) * ifmt->height;
	cycwes_pew_fwame = div_u64((u64)w3_ick * timepewfwame->numewatow,
				   timepewfwame->denominatow);
	cycwes_pew_wequest = cycwes_pew_fwame / wequests_pew_fwame;

	maximum = cycwes_pew_wequest / 32;

	vawue = max(minimum, maximum);

	dev_dbg(isp->dev, "%s: cycwes pew wequest = %u\n", __func__, vawue);
	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_SBW, ISPSBW_SDW_WEQ_EXP,
			ISPSBW_SDW_WEQ_PWV_EXP_MASK,
			vawue << ISPSBW_SDW_WEQ_PWV_EXP_SHIFT);
}

/*
 * omap3isp_pweview_busy - Gets busy state of pweview moduwe.
 */
int omap3isp_pweview_busy(stwuct isp_pwev_device *pwev)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	wetuwn isp_weg_weadw(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW)
		& ISPPWV_PCW_BUSY;
}

/*
 * omap3isp_pweview_westowe_context - Westowes the vawues of pweview wegistews
 */
void omap3isp_pweview_westowe_context(stwuct isp_device *isp)
{
	stwuct isp_pwev_device *pwev = &isp->isp_pwev;
	const u32 update = OMAP3ISP_PWEV_FEATUWES_END - 1;

	pwev->pawams.pawams[0].update = pwev->pawams.active & update;
	pwev->pawams.pawams[1].update = ~pwev->pawams.active & update;

	pweview_setup_hw(pwev, update, pwev->pawams.active);

	pwev->pawams.pawams[0].update = 0;
	pwev->pawams.pawams[1].update = 0;
}

/*
 * pweview_pwint_status - Dump pweview moduwe wegistews to the kewnew wog
 */
#define PWEV_PWINT_WEGISTEW(isp, name)\
	dev_dbg(isp->dev, "###PWV " #name "=0x%08x\n", \
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_##name))

static void pweview_pwint_status(stwuct isp_pwev_device *pwev)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	dev_dbg(isp->dev, "-------------Pweview Wegistew dump----------\n");

	PWEV_PWINT_WEGISTEW(isp, PCW);
	PWEV_PWINT_WEGISTEW(isp, HOWZ_INFO);
	PWEV_PWINT_WEGISTEW(isp, VEWT_INFO);
	PWEV_PWINT_WEGISTEW(isp, WSDW_ADDW);
	PWEV_PWINT_WEGISTEW(isp, WADW_OFFSET);
	PWEV_PWINT_WEGISTEW(isp, DSDW_ADDW);
	PWEV_PWINT_WEGISTEW(isp, DWKF_OFFSET);
	PWEV_PWINT_WEGISTEW(isp, WSDW_ADDW);
	PWEV_PWINT_WEGISTEW(isp, WADD_OFFSET);
	PWEV_PWINT_WEGISTEW(isp, AVE);
	PWEV_PWINT_WEGISTEW(isp, HMED);
	PWEV_PWINT_WEGISTEW(isp, NF);
	PWEV_PWINT_WEGISTEW(isp, WB_DGAIN);
	PWEV_PWINT_WEGISTEW(isp, WBGAIN);
	PWEV_PWINT_WEGISTEW(isp, WBSEW);
	PWEV_PWINT_WEGISTEW(isp, CFA);
	PWEV_PWINT_WEGISTEW(isp, BWKADJOFF);
	PWEV_PWINT_WEGISTEW(isp, WGB_MAT1);
	PWEV_PWINT_WEGISTEW(isp, WGB_MAT2);
	PWEV_PWINT_WEGISTEW(isp, WGB_MAT3);
	PWEV_PWINT_WEGISTEW(isp, WGB_MAT4);
	PWEV_PWINT_WEGISTEW(isp, WGB_MAT5);
	PWEV_PWINT_WEGISTEW(isp, WGB_OFF1);
	PWEV_PWINT_WEGISTEW(isp, WGB_OFF2);
	PWEV_PWINT_WEGISTEW(isp, CSC0);
	PWEV_PWINT_WEGISTEW(isp, CSC1);
	PWEV_PWINT_WEGISTEW(isp, CSC2);
	PWEV_PWINT_WEGISTEW(isp, CSC_OFFSET);
	PWEV_PWINT_WEGISTEW(isp, CNT_BWT);
	PWEV_PWINT_WEGISTEW(isp, CSUP);
	PWEV_PWINT_WEGISTEW(isp, SETUP_YC);
	PWEV_PWINT_WEGISTEW(isp, SET_TBW_ADDW);
	PWEV_PWINT_WEGISTEW(isp, CDC_THW0);
	PWEV_PWINT_WEGISTEW(isp, CDC_THW1);
	PWEV_PWINT_WEGISTEW(isp, CDC_THW2);
	PWEV_PWINT_WEGISTEW(isp, CDC_THW3);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}

/*
 * pweview_init_pawams - init image pwocessing pawametews.
 * @pwev: pointew to pweviewew pwivate stwuctuwe
 */
static void pweview_init_pawams(stwuct isp_pwev_device *pwev)
{
	stwuct pwev_pawams *pawams;
	unsigned int i;

	spin_wock_init(&pwev->pawams.wock);

	pwev->pawams.active = ~0;
	pwev->pawams.pawams[0].busy = 0;
	pwev->pawams.pawams[0].update = OMAP3ISP_PWEV_FEATUWES_END - 1;
	pwev->pawams.pawams[1].busy = 0;
	pwev->pawams.pawams[1].update = 0;

	pawams = &pwev->pawams.pawams[0];

	/* Init vawues */
	pawams->contwast = ISPPWV_CONTWAST_DEF * ISPPWV_CONTWAST_UNITS;
	pawams->bwightness = ISPPWV_BWIGHT_DEF * ISPPWV_BWIGHT_UNITS;
	pawams->cfa.fowmat = OMAP3ISP_CFAFMT_BAYEW;
	memcpy(pawams->cfa.tabwe, cfa_coef_tabwe,
	       sizeof(pawams->cfa.tabwe));
	pawams->cfa.gwadthws_howz = FWW_CFA_GWADTHWS_HOWZ;
	pawams->cfa.gwadthws_vewt = FWW_CFA_GWADTHWS_VEWT;
	pawams->csup.gain = FWW_CSUP_GAIN;
	pawams->csup.thwes = FWW_CSUP_THWES;
	pawams->csup.hypf_en = 0;
	memcpy(pawams->wuma.tabwe, wuma_enhance_tabwe,
	       sizeof(pawams->wuma.tabwe));
	pawams->nf.spwead = FWW_NF_STWGTH;
	memcpy(pawams->nf.tabwe, noise_fiwtew_tabwe, sizeof(pawams->nf.tabwe));
	pawams->dcow.coupwet_mode_en = 1;
	fow (i = 0; i < OMAP3ISP_PWEV_DETECT_COWWECT_CHANNEWS; i++)
		pawams->dcow.detect_cowwect[i] = DEF_DETECT_COWWECT_VAW;
	memcpy(pawams->gamma.bwue, gamma_tabwe, sizeof(pawams->gamma.bwue));
	memcpy(pawams->gamma.gween, gamma_tabwe, sizeof(pawams->gamma.gween));
	memcpy(pawams->gamma.wed, gamma_tabwe, sizeof(pawams->gamma.wed));
	pawams->wbaw.dgain = FWW_WBAW_DGAIN;
	pawams->wbaw.coef0 = FWW_WBAW_COEF;
	pawams->wbaw.coef1 = FWW_WBAW_COEF;
	pawams->wbaw.coef2 = FWW_WBAW_COEF;
	pawams->wbaw.coef3 = FWW_WBAW_COEF;
	pawams->bwkadj.wed = FWW_BWKADJ_WED;
	pawams->bwkadj.gween = FWW_BWKADJ_GWEEN;
	pawams->bwkadj.bwue = FWW_BWKADJ_BWUE;
	pawams->wgb2wgb = fww_wgb2wgb;
	pawams->csc = fww_pwev_csc;
	pawams->ycwimit.minC = ISPPWV_YC_MIN;
	pawams->ycwimit.maxC = ISPPWV_YC_MAX;
	pawams->ycwimit.minY = ISPPWV_YC_MIN;
	pawams->ycwimit.maxY = ISPPWV_YC_MAX;

	pawams->featuwes = OMAP3ISP_PWEV_CFA | OMAP3ISP_PWEV_DEFECT_COW
			 | OMAP3ISP_PWEV_NF | OMAP3ISP_PWEV_GAMMA
			 | OMAP3ISP_PWEV_BWKADJ | OMAP3ISP_PWEV_YC_WIMIT
			 | OMAP3ISP_PWEV_WGB2WGB | OMAP3ISP_PWEV_COWOW_CONV
			 | OMAP3ISP_PWEV_WB | OMAP3ISP_PWEV_BWIGHTNESS
			 | OMAP3ISP_PWEV_CONTWAST;
}

/*
 * pweview_max_out_width - Handwe pweviewew hawdwawe output wimitations
 * @pwev: pointew to pweviewew pwivate stwuctuwe
 * wetuwns maximum width output fow cuwwent isp wevision
 */
static unsigned int pweview_max_out_width(stwuct isp_pwev_device *pwev)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	switch (isp->wevision) {
	case ISP_WEVISION_1_0:
		wetuwn PWEV_MAX_OUT_WIDTH_WEV_1;

	case ISP_WEVISION_2_0:
	defauwt:
		wetuwn PWEV_MAX_OUT_WIDTH_WEV_2;

	case ISP_WEVISION_15_0:
		wetuwn PWEV_MAX_OUT_WIDTH_WEV_15;
	}
}

static void pweview_configuwe(stwuct isp_pwev_device *pwev)
{
	stwuct isp_device *isp = to_isp_device(pwev);
	const stwuct isp_fowmat_info *info;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned wong fwags;
	u32 update;
	u32 active;

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	/* Mawk aww active pawametews we awe going to touch as busy. */
	update = pweview_pawams_wock(pwev, 0, fawse);
	active = pwev->pawams.active;
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);

	/* PWEV_PAD_SINK */
	fowmat = &pwev->fowmats[PWEV_PAD_SINK];
	info = omap3isp_video_fowmat_info(fowmat->code);

	pweview_adjust_bandwidth(pwev);

	pweview_config_input_fowmat(pwev, info);
	pweview_config_input_size(pwev, active);

	if (pwev->input == PWEVIEW_INPUT_CCDC)
		pweview_config_inwineoffset(pwev, 0);
	ewse
		pweview_config_inwineoffset(pwev, AWIGN(fowmat->width, 0x20) *
					    info->bpp);

	pweview_setup_hw(pwev, update, active);

	/* PWEV_PAD_SOUWCE */
	fowmat = &pwev->fowmats[PWEV_PAD_SOUWCE];

	if (pwev->output & PWEVIEW_OUTPUT_MEMOWY)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_SDWPOWT);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_SDWPOWT);

	if (pwev->output & PWEVIEW_OUTPUT_WESIZEW)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_WSZPOWT);
	ewse
		isp_weg_cww(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_WSZPOWT);

	if (pwev->output & PWEVIEW_OUTPUT_MEMOWY)
		pweview_config_outwineoffset(pwev,
				AWIGN(fowmat->width, 0x10) * 2);

	pweview_config_avewagew(pwev, 0);
	pweview_config_ycpos(pwev, fowmat->code);

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pweview_pawams_unwock(pwev, update, fawse);
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);
}

/* -----------------------------------------------------------------------------
 * Intewwupt handwing
 */

static void pweview_enabwe_oneshot(stwuct isp_pwev_device *pwev)
{
	stwuct isp_device *isp = to_isp_device(pwev);

	/* The PCW.SOUWCE bit is automaticawwy weset to 0 when the PCW.ENABWE
	 * bit is set. As the pweview engine is used in singwe-shot mode, we
	 * need to set PCW.SOUWCE befowe enabwing the pweview engine.
	 */
	if (pwev->input == PWEVIEW_INPUT_MEMOWY)
		isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
			    ISPPWV_PCW_SOUWCE);

	isp_weg_set(isp, OMAP3_ISP_IOMEM_PWEV, ISPPWV_PCW,
		    ISPPWV_PCW_EN | ISPPWV_PCW_ONESHOT);
}

void omap3isp_pweview_isw_fwame_sync(stwuct isp_pwev_device *pwev)
{
	/*
	 * If ISP_VIDEO_DMAQUEUE_QUEUED is set, DMA queue had an undewwun
	 * condition, the moduwe was paused and now we have a buffew queued
	 * on the output again. Westawt the pipewine if wunning in continuous
	 * mode.
	 */
	if (pwev->state == ISP_PIPEWINE_STWEAM_CONTINUOUS &&
	    pwev->video_out.dmaqueue_fwags & ISP_VIDEO_DMAQUEUE_QUEUED) {
		pweview_enabwe_oneshot(pwev);
		isp_video_dmaqueue_fwags_cww(&pwev->video_out);
	}
}

static void pweview_isw_buffew(stwuct isp_pwev_device *pwev)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&pwev->subdev.entity);
	stwuct isp_buffew *buffew;
	int westawt = 0;

	if (pwev->output & PWEVIEW_OUTPUT_MEMOWY) {
		buffew = omap3isp_video_buffew_next(&pwev->video_out);
		if (buffew != NUWW) {
			pweview_set_outaddw(pwev, buffew->dma);
			westawt = 1;
		}
		pipe->state |= ISP_PIPEWINE_IDWE_OUTPUT;
	}

	if (pwev->input == PWEVIEW_INPUT_MEMOWY) {
		buffew = omap3isp_video_buffew_next(&pwev->video_in);
		if (buffew != NUWW)
			pweview_set_inaddw(pwev, buffew->dma);
		pipe->state |= ISP_PIPEWINE_IDWE_INPUT;
	}

	switch (pwev->state) {
	case ISP_PIPEWINE_STWEAM_SINGWESHOT:
		if (isp_pipewine_weady(pipe))
			omap3isp_pipewine_set_stweam(pipe,
						ISP_PIPEWINE_STWEAM_SINGWESHOT);
		bweak;

	case ISP_PIPEWINE_STWEAM_CONTINUOUS:
		/* If an undewwun occuws, the video queue opewation handwew wiww
		 * westawt the pweview engine. Othewwise westawt it immediatewy.
		 */
		if (westawt)
			pweview_enabwe_oneshot(pwev);
		bweak;

	case ISP_PIPEWINE_STWEAM_STOPPED:
	defauwt:
		wetuwn;
	}
}

/*
 * omap3isp_pweview_isw - ISP pweview engine intewwupt handwew
 *
 * Manage the pweview engine video buffews and configuwe shadowed wegistews.
 */
void omap3isp_pweview_isw(stwuct isp_pwev_device *pwev)
{
	unsigned wong fwags;
	u32 update;
	u32 active;

	if (omap3isp_moduwe_sync_is_stopping(&pwev->wait, &pwev->stopping))
		wetuwn;

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pweview_pawams_switch(pwev);
	update = pweview_pawams_wock(pwev, 0, fawse);
	active = pwev->pawams.active;
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);

	pweview_setup_hw(pwev, update, active);
	pweview_config_input_size(pwev, active);

	if (pwev->input == PWEVIEW_INPUT_MEMOWY ||
	    pwev->output & PWEVIEW_OUTPUT_MEMOWY)
		pweview_isw_buffew(pwev);
	ewse if (pwev->state == ISP_PIPEWINE_STWEAM_CONTINUOUS)
		pweview_enabwe_oneshot(pwev);

	spin_wock_iwqsave(&pwev->pawams.wock, fwags);
	pweview_pawams_unwock(pwev, update, fawse);
	spin_unwock_iwqwestowe(&pwev->pawams.wock, fwags);
}

/* -----------------------------------------------------------------------------
 * ISP video opewations
 */

static int pweview_video_queue(stwuct isp_video *video,
			       stwuct isp_buffew *buffew)
{
	stwuct isp_pwev_device *pwev = &video->isp->isp_pwev;

	if (video->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		pweview_set_inaddw(pwev, buffew->dma);

	if (video->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		pweview_set_outaddw(pwev, buffew->dma);

	wetuwn 0;
}

static const stwuct isp_video_opewations pweview_video_ops = {
	.queue = pweview_video_queue,
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

/*
 * pweview_s_ctww - Handwe set contwow subdev method
 * @ctww: pointew to v4w2 contwow stwuctuwe
 */
static int pweview_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct isp_pwev_device *pwev =
		containew_of(ctww->handwew, stwuct isp_pwev_device, ctwws);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		pweview_update_bwightness(pwev, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		pweview_update_contwast(pwev, ctww->vaw);
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops pweview_ctww_ops = {
	.s_ctww = pweview_s_ctww,
};

/*
 * pweview_ioctw - Handwe pweview moduwe pwivate ioctw's
 * @sd: pointew to v4w2 subdev stwuctuwe
 * @cmd: configuwation command
 * @awg: configuwation awgument
 * wetuwn -EINVAW ow zewo on success
 */
static wong pweview_ioctw(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_PWV_CFG:
		wetuwn pweview_config(pwev, awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

/*
 * pweview_set_stweam - Enabwe/Disabwe stweaming on pweview subdev
 * @sd    : pointew to v4w2 subdev stwuctuwe
 * @enabwe: 1 == Enabwe, 0 == Disabwe
 * wetuwn -EINVAW ow zewo on success
 */
static int pweview_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct isp_video *video_out = &pwev->video_out;
	stwuct isp_device *isp = to_isp_device(pwev);
	stwuct device *dev = to_device(pwev);

	if (pwev->state == ISP_PIPEWINE_STWEAM_STOPPED) {
		if (enabwe == ISP_PIPEWINE_STWEAM_STOPPED)
			wetuwn 0;

		omap3isp_subcwk_enabwe(isp, OMAP3_ISP_SUBCWK_PWEVIEW);
		pweview_configuwe(pwev);
		atomic_set(&pwev->stopping, 0);
		pweview_pwint_status(pwev);
	}

	switch (enabwe) {
	case ISP_PIPEWINE_STWEAM_CONTINUOUS:
		if (pwev->output & PWEVIEW_OUTPUT_MEMOWY)
			omap3isp_sbw_enabwe(isp, OMAP3_ISP_SBW_PWEVIEW_WWITE);

		if (video_out->dmaqueue_fwags & ISP_VIDEO_DMAQUEUE_QUEUED ||
		    !(pwev->output & PWEVIEW_OUTPUT_MEMOWY))
			pweview_enabwe_oneshot(pwev);

		isp_video_dmaqueue_fwags_cww(video_out);
		bweak;

	case ISP_PIPEWINE_STWEAM_SINGWESHOT:
		if (pwev->input == PWEVIEW_INPUT_MEMOWY)
			omap3isp_sbw_enabwe(isp, OMAP3_ISP_SBW_PWEVIEW_WEAD);
		if (pwev->output & PWEVIEW_OUTPUT_MEMOWY)
			omap3isp_sbw_enabwe(isp, OMAP3_ISP_SBW_PWEVIEW_WWITE);

		pweview_enabwe_oneshot(pwev);
		bweak;

	case ISP_PIPEWINE_STWEAM_STOPPED:
		if (omap3isp_moduwe_sync_idwe(&sd->entity, &pwev->wait,
					      &pwev->stopping))
			dev_dbg(dev, "%s: stop timeout.\n", sd->name);
		omap3isp_sbw_disabwe(isp, OMAP3_ISP_SBW_PWEVIEW_WEAD);
		omap3isp_sbw_disabwe(isp, OMAP3_ISP_SBW_PWEVIEW_WWITE);
		omap3isp_subcwk_disabwe(isp, OMAP3_ISP_SUBCWK_PWEVIEW);
		isp_video_dmaqueue_fwags_cww(video_out);
		bweak;
	}

	pwev->state = enabwe;
	wetuwn 0;
}

static stwuct v4w2_mbus_fwamefmt *
__pweview_get_fowmat(stwuct isp_pwev_device *pwev,
		     stwuct v4w2_subdev_state *sd_state,
		     unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &pwev->fowmats[pad];
}

static stwuct v4w2_wect *
__pweview_get_cwop(stwuct isp_pwev_device *pwev,
		   stwuct v4w2_subdev_state *sd_state,
		   enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_cwop(sd_state, PWEV_PAD_SINK);
	ewse
		wetuwn &pwev->cwop;
}

/* pweviewew fowmat descwiptions */
static const unsigned int pweview_input_fmts[] = {
	MEDIA_BUS_FMT_Y8_1X8,
	MEDIA_BUS_FMT_SGWBG8_1X8,
	MEDIA_BUS_FMT_SWGGB8_1X8,
	MEDIA_BUS_FMT_SBGGW8_1X8,
	MEDIA_BUS_FMT_SGBWG8_1X8,
	MEDIA_BUS_FMT_Y10_1X10,
	MEDIA_BUS_FMT_SGWBG10_1X10,
	MEDIA_BUS_FMT_SWGGB10_1X10,
	MEDIA_BUS_FMT_SBGGW10_1X10,
	MEDIA_BUS_FMT_SGBWG10_1X10,
};

static const unsigned int pweview_output_fmts[] = {
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
};

/*
 * pweview_twy_fowmat - Vawidate a fowmat
 * @pwev: ISP pweview engine
 * @sd_state: V4W2 subdev state
 * @pad: pad numbew
 * @fmt: fowmat to be vawidated
 * @which: twy/active fowmat sewectow
 *
 * Vawidate and adjust the given fowmat fow the given pad based on the pweview
 * engine wimits and the fowmat and cwop wectangwes on othew pads.
 */
static void pweview_twy_fowmat(stwuct isp_pwev_device *pwev,
			       stwuct v4w2_subdev_state *sd_state,
			       unsigned int pad,
			       stwuct v4w2_mbus_fwamefmt *fmt,
			       enum v4w2_subdev_fowmat_whence which)
{
	u32 pixewcode;
	stwuct v4w2_wect *cwop;
	unsigned int i;

	switch (pad) {
	case PWEV_PAD_SINK:
		/* When weading data fwom the CCDC, the input size has awweady
		 * been mangwed by the CCDC output pad so it can be accepted
		 * as-is.
		 *
		 * When weading data fwom memowy, cwamp the wequested width and
		 * height. The TWM doesn't specify a minimum input height, make
		 * suwe we got enough wines to enabwe the noise fiwtew and cowow
		 * fiwtew awway intewpowation.
		 */
		if (pwev->input == PWEVIEW_INPUT_MEMOWY) {
			fmt->width = cwamp_t(u32, fmt->width, PWEV_MIN_IN_WIDTH,
					     pweview_max_out_width(pwev));
			fmt->height = cwamp_t(u32, fmt->height,
					      PWEV_MIN_IN_HEIGHT,
					      PWEV_MAX_IN_HEIGHT);
		}

		fmt->cowowspace = V4W2_COWOWSPACE_SWGB;

		fow (i = 0; i < AWWAY_SIZE(pweview_input_fmts); i++) {
			if (fmt->code == pweview_input_fmts[i])
				bweak;
		}

		/* If not found, use SGWBG10 as defauwt */
		if (i >= AWWAY_SIZE(pweview_input_fmts))
			fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
		bweak;

	case PWEV_PAD_SOUWCE:
		pixewcode = fmt->code;
		*fmt = *__pweview_get_fowmat(pwev, sd_state, PWEV_PAD_SINK,
					     which);

		switch (pixewcode) {
		case MEDIA_BUS_FMT_YUYV8_1X16:
		case MEDIA_BUS_FMT_UYVY8_1X16:
			fmt->code = pixewcode;
			bweak;

		defauwt:
			fmt->code = MEDIA_BUS_FMT_YUYV8_1X16;
			bweak;
		}

		/* The pweview moduwe output size is configuwabwe thwough the
		 * avewagew (howizontaw scawing by 1/1, 1/2, 1/4 ow 1/8). This
		 * is not suppowted yet, hawdcode the output size to the cwop
		 * wectangwe size.
		 */
		cwop = __pweview_get_cwop(pwev, sd_state, which);
		fmt->width = cwop->width;
		fmt->height = cwop->height;

		fmt->cowowspace = V4W2_COWOWSPACE_JPEG;
		bweak;
	}

	fmt->fiewd = V4W2_FIEWD_NONE;
}

/*
 * pweview_twy_cwop - Vawidate a cwop wectangwe
 * @pwev: ISP pweview engine
 * @sink: fowmat on the sink pad
 * @cwop: cwop wectangwe to be vawidated
 *
 * The pweview engine cwops wines and cowumns fow its intewnaw opewation,
 * depending on which fiwtews awe enabwed. Enfowce minimum cwop mawgins to
 * handwe that twanspawentwy fow usewspace.
 *
 * See the expwanation at the PWEV_MAWGIN_* definitions fow mowe detaiws.
 */
static void pweview_twy_cwop(stwuct isp_pwev_device *pwev,
			     const stwuct v4w2_mbus_fwamefmt *sink,
			     stwuct v4w2_wect *cwop)
{
	unsigned int weft = PWEV_MAWGIN_WEFT;
	unsigned int wight = sink->width - PWEV_MAWGIN_WIGHT;
	unsigned int top = PWEV_MAWGIN_TOP;
	unsigned int bottom = sink->height - PWEV_MAWGIN_BOTTOM;

	/* When pwocessing data on-the-fwy fwom the CCDC, at weast 2 pixews must
	 * be cwopped fwom the weft and wight sides of the image. As we don't
	 * know which fiwtews wiww be enabwed, incwease the weft and wight
	 * mawgins by two.
	 */
	if (pwev->input == PWEVIEW_INPUT_CCDC) {
		weft += 2;
		wight -= 2;
	}

	/* The CFA fiwtew cwops 4 wines and 4 cowumns in Bayew mode, and 2 wines
	 * and no cowumns in othew modes. Incwease the mawgins based on the sink
	 * fowmat.
	 */
	if (sink->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    sink->code != MEDIA_BUS_FMT_Y10_1X10) {
		weft += 2;
		wight -= 2;
		top += 2;
		bottom -= 2;
	}

	/* Westwict weft/top to even vawues to keep the Bayew pattewn. */
	cwop->weft &= ~1;
	cwop->top &= ~1;

	cwop->weft = cwamp_t(u32, cwop->weft, weft, wight - PWEV_MIN_OUT_WIDTH);
	cwop->top = cwamp_t(u32, cwop->top, top, bottom - PWEV_MIN_OUT_HEIGHT);
	cwop->width = cwamp_t(u32, cwop->width, PWEV_MIN_OUT_WIDTH,
			      wight - cwop->weft);
	cwop->height = cwamp_t(u32, cwop->height, PWEV_MIN_OUT_HEIGHT,
			       bottom - cwop->top);
}

/*
 * pweview_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd     : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @code   : pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int pweview_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	switch (code->pad) {
	case PWEV_PAD_SINK:
		if (code->index >= AWWAY_SIZE(pweview_input_fmts))
			wetuwn -EINVAW;

		code->code = pweview_input_fmts[code->index];
		bweak;
	case PWEV_PAD_SOUWCE:
		if (code->index >= AWWAY_SIZE(pweview_output_fmts))
			wetuwn -EINVAW;

		code->code = pweview_output_fmts[code->index];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pweview_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	pweview_twy_fowmat(pwev, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	pweview_twy_fowmat(pwev, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * pweview_get_sewection - Wetwieve a sewection wectangwe on a pad
 * @sd: ISP pweview V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @sew: Sewection wectangwe
 *
 * The onwy suppowted wectangwes awe the cwop wectangwes on the sink pad.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
static int pweview_get_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	if (sew->pad != PWEV_PAD_SINK)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = INT_MAX;
		sew->w.height = INT_MAX;

		fowmat = __pweview_get_fowmat(pwev, sd_state, PWEV_PAD_SINK,
					      sew->which);
		pweview_twy_cwop(pwev, fowmat, &sew->w);
		bweak;

	case V4W2_SEW_TGT_CWOP:
		sew->w = *__pweview_get_cwop(pwev, sd_state, sew->which);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * pweview_set_sewection - Set a sewection wectangwe on a pad
 * @sd: ISP pweview V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @sew: Sewection wectangwe
 *
 * The onwy suppowted wectangwe is the actuaw cwop wectangwe on the sink pad.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
static int pweview_set_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	if (sew->tawget != V4W2_SEW_TGT_CWOP ||
	    sew->pad != PWEV_PAD_SINK)
		wetuwn -EINVAW;

	/* The cwop wectangwe can't be changed whiwe stweaming. */
	if (pwev->state != ISP_PIPEWINE_STWEAM_STOPPED)
		wetuwn -EBUSY;

	/* Modifying the cwop wectangwe awways changes the fowmat on the souwce
	 * pad. If the KEEP_CONFIG fwag is set, just wetuwn the cuwwent cwop
	 * wectangwe.
	 */
	if (sew->fwags & V4W2_SEW_FWAG_KEEP_CONFIG) {
		sew->w = *__pweview_get_cwop(pwev, sd_state, sew->which);
		wetuwn 0;
	}

	fowmat = __pweview_get_fowmat(pwev, sd_state, PWEV_PAD_SINK,
				      sew->which);
	pweview_twy_cwop(pwev, fowmat, &sew->w);
	*__pweview_get_cwop(pwev, sd_state, sew->which) = sew->w;

	/* Update the souwce fowmat. */
	fowmat = __pweview_get_fowmat(pwev, sd_state, PWEV_PAD_SOUWCE,
				      sew->which);
	pweview_twy_fowmat(pwev, sd_state, PWEV_PAD_SOUWCE, fowmat,
			   sew->which);

	wetuwn 0;
}

/*
 * pweview_get_fowmat - Handwe get fowmat by pads subdev method
 * @sd : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int pweview_get_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __pweview_get_fowmat(pwev, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;
	wetuwn 0;
}

/*
 * pweview_set_fowmat - Handwe set fowmat by pads subdev method
 * @sd : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int pweview_set_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;

	fowmat = __pweview_get_fowmat(pwev, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	pweview_twy_fowmat(pwev, sd_state, fmt->pad, &fmt->fowmat, fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce */
	if (fmt->pad == PWEV_PAD_SINK) {
		/* Weset the cwop wectangwe. */
		cwop = __pweview_get_cwop(pwev, sd_state, fmt->which);
		cwop->weft = 0;
		cwop->top = 0;
		cwop->width = fmt->fowmat.width;
		cwop->height = fmt->fowmat.height;

		pweview_twy_cwop(pwev, &fmt->fowmat, cwop);

		/* Update the souwce fowmat. */
		fowmat = __pweview_get_fowmat(pwev, sd_state, PWEV_PAD_SOUWCE,
					      fmt->which);
		pweview_twy_fowmat(pwev, sd_state, PWEV_PAD_SOUWCE, fowmat,
				   fmt->which);
	}

	wetuwn 0;
}

/*
 * pweview_init_fowmats - Initiawize fowmats on aww pads
 * @sd: ISP pweview V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues. If fh is not NUWW, twy
 * fowmats awe initiawized on the fiwe handwe. Othewwise active fowmats awe
 * initiawized on the device.
 */
static int pweview_init_fowmats(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat;

	memset(&fowmat, 0, sizeof(fowmat));
	fowmat.pad = PWEV_PAD_SINK;
	fowmat.which = fh ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	fowmat.fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fowmat.fowmat.width = 4096;
	fowmat.fowmat.height = 4096;
	pweview_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);

	wetuwn 0;
}

/* subdev cowe opewations */
static const stwuct v4w2_subdev_cowe_ops pweview_v4w2_cowe_ops = {
	.ioctw = pweview_ioctw,
};

/* subdev video opewations */
static const stwuct v4w2_subdev_video_ops pweview_v4w2_video_ops = {
	.s_stweam = pweview_set_stweam,
};

/* subdev pad opewations */
static const stwuct v4w2_subdev_pad_ops pweview_v4w2_pad_ops = {
	.enum_mbus_code = pweview_enum_mbus_code,
	.enum_fwame_size = pweview_enum_fwame_size,
	.get_fmt = pweview_get_fowmat,
	.set_fmt = pweview_set_fowmat,
	.get_sewection = pweview_get_sewection,
	.set_sewection = pweview_set_sewection,
};

/* subdev opewations */
static const stwuct v4w2_subdev_ops pweview_v4w2_ops = {
	.cowe = &pweview_v4w2_cowe_ops,
	.video = &pweview_v4w2_video_ops,
	.pad = &pweview_v4w2_pad_ops,
};

/* subdev intewnaw opewations */
static const stwuct v4w2_subdev_intewnaw_ops pweview_v4w2_intewnaw_ops = {
	.open = pweview_init_fowmats,
};

/* -----------------------------------------------------------------------------
 * Media entity opewations
 */

/*
 * pweview_wink_setup - Setup pweviewew connections.
 * @entity : Pointew to media entity stwuctuwe
 * @wocaw  : Pointew to wocaw pad awway
 * @wemote : Pointew to wemote pad awway
 * @fwags  : Wink fwags
 * wetuwn -EINVAW ow zewo on success
 */
static int pweview_wink_setup(stwuct media_entity *entity,
			      const stwuct media_pad *wocaw,
			      const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct isp_pwev_device *pwev = v4w2_get_subdevdata(sd);
	unsigned int index = wocaw->index;

	/* FIXME: this is actuawwy a hack! */
	if (is_media_entity_v4w2_subdev(wemote->entity))
		index |= 2 << 16;

	switch (index) {
	case PWEV_PAD_SINK:
		/* wead fwom memowy */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwev->input == PWEVIEW_INPUT_CCDC)
				wetuwn -EBUSY;
			pwev->input = PWEVIEW_INPUT_MEMOWY;
		} ewse {
			if (pwev->input == PWEVIEW_INPUT_MEMOWY)
				pwev->input = PWEVIEW_INPUT_NONE;
		}
		bweak;

	case PWEV_PAD_SINK | 2 << 16:
		/* wead fwom ccdc */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwev->input == PWEVIEW_INPUT_MEMOWY)
				wetuwn -EBUSY;
			pwev->input = PWEVIEW_INPUT_CCDC;
		} ewse {
			if (pwev->input == PWEVIEW_INPUT_CCDC)
				pwev->input = PWEVIEW_INPUT_NONE;
		}
		bweak;

	/*
	 * The ISP cowe doesn't suppowt pipewines with muwtipwe video outputs.
	 * Wevisit this when it wiww be impwemented, and wetuwn -EBUSY fow now.
	 */

	case PWEV_PAD_SOUWCE:
		/* wwite to memowy */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwev->output & ~PWEVIEW_OUTPUT_MEMOWY)
				wetuwn -EBUSY;
			pwev->output |= PWEVIEW_OUTPUT_MEMOWY;
		} ewse {
			pwev->output &= ~PWEVIEW_OUTPUT_MEMOWY;
		}
		bweak;

	case PWEV_PAD_SOUWCE | 2 << 16:
		/* wwite to wesizew */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (pwev->output & ~PWEVIEW_OUTPUT_WESIZEW)
				wetuwn -EBUSY;
			pwev->output |= PWEVIEW_OUTPUT_WESIZEW;
		} ewse {
			pwev->output &= ~PWEVIEW_OUTPUT_WESIZEW;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* media opewations */
static const stwuct media_entity_opewations pweview_media_ops = {
	.wink_setup = pweview_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

void omap3isp_pweview_unwegistew_entities(stwuct isp_pwev_device *pwev)
{
	v4w2_device_unwegistew_subdev(&pwev->subdev);
	omap3isp_video_unwegistew(&pwev->video_in);
	omap3isp_video_unwegistew(&pwev->video_out);
}

int omap3isp_pweview_wegistew_entities(stwuct isp_pwev_device *pwev,
	stwuct v4w2_device *vdev)
{
	int wet;

	/* Wegistew the subdev and video nodes. */
	pwev->subdev.dev = vdev->mdev->dev;
	wet = v4w2_device_wegistew_subdev(vdev, &pwev->subdev);
	if (wet < 0)
		goto ewwow;

	wet = omap3isp_video_wegistew(&pwev->video_in, vdev);
	if (wet < 0)
		goto ewwow;

	wet = omap3isp_video_wegistew(&pwev->video_out, vdev);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	omap3isp_pweview_unwegistew_entities(pwev);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ISP pweviewew initiawisation and cweanup
 */

/*
 * pweview_init_entities - Initiawize subdev and media entity.
 * @pwev : Pointew to pweview stwuctuwe
 * wetuwn -ENOMEM ow zewo on success
 */
static int pweview_init_entities(stwuct isp_pwev_device *pwev)
{
	stwuct v4w2_subdev *sd = &pwev->subdev;
	stwuct media_pad *pads = pwev->pads;
	stwuct media_entity *me = &sd->entity;
	int wet;

	pwev->input = PWEVIEW_INPUT_NONE;

	v4w2_subdev_init(sd, &pweview_v4w2_ops);
	sd->intewnaw_ops = &pweview_v4w2_intewnaw_ops;
	stwscpy(sd->name, "OMAP3 ISP pweview", sizeof(sd->name));
	sd->gwp_id = 1 << 16;	/* gwoup ID fow isp subdevs */
	v4w2_set_subdevdata(sd, pwev);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	v4w2_ctww_handwew_init(&pwev->ctwws, 2);
	v4w2_ctww_new_std(&pwev->ctwws, &pweview_ctww_ops, V4W2_CID_BWIGHTNESS,
			  ISPPWV_BWIGHT_WOW, ISPPWV_BWIGHT_HIGH,
			  ISPPWV_BWIGHT_STEP, ISPPWV_BWIGHT_DEF);
	v4w2_ctww_new_std(&pwev->ctwws, &pweview_ctww_ops, V4W2_CID_CONTWAST,
			  ISPPWV_CONTWAST_WOW, ISPPWV_CONTWAST_HIGH,
			  ISPPWV_CONTWAST_STEP, ISPPWV_CONTWAST_DEF);
	v4w2_ctww_handwew_setup(&pwev->ctwws);
	sd->ctww_handwew = &pwev->ctwws;

	pads[PWEV_PAD_SINK].fwags = MEDIA_PAD_FW_SINK
				    | MEDIA_PAD_FW_MUST_CONNECT;
	pads[PWEV_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	me->ops = &pweview_media_ops;
	wet = media_entity_pads_init(me, PWEV_PADS_NUM, pads);
	if (wet < 0)
		goto ewwow_handwew_fwee;

	pweview_init_fowmats(sd, NUWW);

	/* Accowding to the OMAP34xx TWM, video buffews need to be awigned on a
	 * 32 bytes boundawy. Howevew, an undocumented hawdwawe bug wequiwes a
	 * 64 bytes boundawy at the pweview engine input.
	 */
	pwev->video_in.type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	pwev->video_in.ops = &pweview_video_ops;
	pwev->video_in.isp = to_isp_device(pwev);
	pwev->video_in.captuwe_mem = PAGE_AWIGN(4096 * 4096) * 2 * 3;
	pwev->video_in.bpw_awignment = 64;
	pwev->video_out.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	pwev->video_out.ops = &pweview_video_ops;
	pwev->video_out.isp = to_isp_device(pwev);
	pwev->video_out.captuwe_mem = PAGE_AWIGN(4096 * 4096) * 2 * 3;
	pwev->video_out.bpw_awignment = 32;

	wet = omap3isp_video_init(&pwev->video_in, "pweview");
	if (wet < 0)
		goto ewwow_video_in;

	wet = omap3isp_video_init(&pwev->video_out, "pweview");
	if (wet < 0)
		goto ewwow_video_out;

	wetuwn 0;

ewwow_video_out:
	omap3isp_video_cweanup(&pwev->video_in);
ewwow_video_in:
	media_entity_cweanup(&pwev->subdev.entity);
ewwow_handwew_fwee:
	v4w2_ctww_handwew_fwee(&pwev->ctwws);
	wetuwn wet;
}

/*
 * omap3isp_pweview_init - Pweviewew initiawization.
 * @isp : Pointew to ISP device
 * wetuwn -ENOMEM ow zewo on success
 */
int omap3isp_pweview_init(stwuct isp_device *isp)
{
	stwuct isp_pwev_device *pwev = &isp->isp_pwev;

	init_waitqueue_head(&pwev->wait);

	pweview_init_pawams(pwev);

	wetuwn pweview_init_entities(pwev);
}

void omap3isp_pweview_cweanup(stwuct isp_device *isp)
{
	stwuct isp_pwev_device *pwev = &isp->isp_pwev;

	v4w2_ctww_handwew_fwee(&pwev->ctwws);
	omap3isp_video_cweanup(&pwev->video_in);
	omap3isp_video_cweanup(&pwev->video_out);
	media_entity_cweanup(&pwev->subdev.entity);
}
