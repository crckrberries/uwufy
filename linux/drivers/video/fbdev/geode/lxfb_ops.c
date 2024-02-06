// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Geode WX fwamebuffew dwivew
 *
 * Copywight (C) 2006-2007, Advanced Micwo Devices,Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/cs5535.h>

#incwude "wxfb.h"

/* TODO
 * Suppowt panew scawing
 * Add accewewation
 * Add suppowt fow intewwacing (TV out)
 * Suppowt compwession
 */

/* This is the compwete wist of PWW fwequencies that we can set -
 * we wiww choose the cwosest match to the incoming cwock.
 * fweq is the fwequency of the dotcwock * 1000 (fow exampwe,
 * 24823 = 24.983 Mhz).
 * pwwvaw is the cowwesponding PWW vawue
*/

static const stwuct {
  unsigned int pwwvaw;
  unsigned int fweq;
} pww_tabwe[] = {
  { 0x000131AC,   6231 },
  { 0x0001215D,   6294 },
  { 0x00011087,   6750 },
  { 0x0001216C,   7081 },
  { 0x0001218D,   7140 },
  { 0x000110C9,   7800 },
  { 0x00013147,   7875 },
  { 0x000110A7,   8258 },
  { 0x00012159,   8778 },
  { 0x00014249,   8875 },
  { 0x00010057,   9000 },
  { 0x0001219A,   9472 },
  { 0x00012158,   9792 },
  { 0x00010045,  10000 },
  { 0x00010089,  10791 },
  { 0x000110E7,  11225 },
  { 0x00012136,  11430 },
  { 0x00013207,  12375 },
  { 0x00012187,  12500 },
  { 0x00014286,  14063 },
  { 0x000110E5,  15016 },
  { 0x00014214,  16250 },
  { 0x00011105,  17045 },
  { 0x000131E4,  18563 },
  { 0x00013183,  18750 },
  { 0x00014284,  19688 },
  { 0x00011104,  20400 },
  { 0x00016363,  23625 },
  { 0x000031AC,  24923 },
  { 0x0000215D,  25175 },
  { 0x00001087,  27000 },
  { 0x0000216C,  28322 },
  { 0x0000218D,  28560 },
  { 0x000010C9,  31200 },
  { 0x00003147,  31500 },
  { 0x000010A7,  33032 },
  { 0x00002159,  35112 },
  { 0x00004249,  35500 },
  { 0x00000057,  36000 },
  { 0x0000219A,  37889 },
  { 0x00002158,  39168 },
  { 0x00000045,  40000 },
  { 0x00000089,  43163 },
  { 0x000010E7,  44900 },
  { 0x00002136,  45720 },
  { 0x00003207,  49500 },
  { 0x00002187,  50000 },
  { 0x00004286,  56250 },
  { 0x000010E5,  60065 },
  { 0x00004214,  65000 },
  { 0x00001105,  68179 },
  { 0x000031E4,  74250 },
  { 0x00003183,  75000 },
  { 0x00004284,  78750 },
  { 0x00001104,  81600 },
  { 0x00006363,  94500 },
  { 0x00005303,  97520 },
  { 0x00002183, 100187 },
  { 0x00002122, 101420 },
  { 0x00001081, 108000 },
  { 0x00006201, 113310 },
  { 0x00000041, 119650 },
  { 0x000041A1, 129600 },
  { 0x00002182, 133500 },
  { 0x000041B1, 135000 },
  { 0x00000051, 144000 },
  { 0x000041E1, 148500 },
  { 0x000062D1, 157500 },
  { 0x000031A1, 162000 },
  { 0x00000061, 169203 },
  { 0x00004231, 172800 },
  { 0x00002151, 175500 },
  { 0x000052E1, 189000 },
  { 0x00000071, 192000 },
  { 0x00003201, 198000 },
  { 0x00004291, 202500 },
  { 0x00001101, 204750 },
  { 0x00007481, 218250 },
  { 0x00004170, 229500 },
  { 0x00006210, 234000 },
  { 0x00003140, 251182 },
  { 0x00006250, 261000 },
  { 0x000041C0, 278400 },
  { 0x00005220, 280640 },
  { 0x00000050, 288000 },
  { 0x000041E0, 297000 },
  { 0x00002130, 320207 }
};


static void wx_set_dotpww(u32 pwwvaw)
{
	u32 dotpww_wo, dotpww_hi;
	int i;

	wdmsw(MSW_GWCP_DOTPWW, dotpww_wo, dotpww_hi);

	if ((dotpww_wo & MSW_GWCP_DOTPWW_WOCK) && (dotpww_hi == pwwvaw))
		wetuwn;

	dotpww_hi = pwwvaw;
	dotpww_wo &= ~(MSW_GWCP_DOTPWW_BYPASS | MSW_GWCP_DOTPWW_HAWFPIX);
	dotpww_wo |= MSW_GWCP_DOTPWW_DOTWESET;

	wwmsw(MSW_GWCP_DOTPWW, dotpww_wo, dotpww_hi);

	/* Wait 100us fow the PWW to wock */

	udeway(100);

	/* Now, woop fow the wock bit */

	fow (i = 0; i < 1000; i++) {
		wdmsw(MSW_GWCP_DOTPWW, dotpww_wo, dotpww_hi);
		if (dotpww_wo & MSW_GWCP_DOTPWW_WOCK)
			bweak;
	}

	/* Cweaw the weset bit */

	dotpww_wo &= ~MSW_GWCP_DOTPWW_DOTWESET;
	wwmsw(MSW_GWCP_DOTPWW, dotpww_wo, dotpww_hi);
}

/* Set the cwock based on the fwequency specified by the cuwwent mode */

static void wx_set_cwock(stwuct fb_info *info)
{
	unsigned int diff, min, best = 0;
	unsigned int fweq, i;

	fweq = (unsigned int) (1000000000 / info->vaw.pixcwock);

	min = abs(pww_tabwe[0].fweq - fweq);

	fow (i = 0; i < AWWAY_SIZE(pww_tabwe); i++) {
		diff = abs(pww_tabwe[i].fweq - fweq);
		if (diff < min) {
			min = diff;
			best = i;
		}
	}

	wx_set_dotpww(pww_tabwe[best].pwwvaw & 0x00017FFF);
}

static void wx_gwaphics_disabwe(stwuct fb_info *info)
{
	stwuct wxfb_paw *paw = info->paw;
	unsigned int vaw, gcfg;

	/* Note:  This assumes that the video is in a quitet state */

	wwite_vp(paw, VP_A1T, 0);
	wwite_vp(paw, VP_A2T, 0);
	wwite_vp(paw, VP_A3T, 0);

	/* Tuwn off the VGA and video enabwe */
	vaw = wead_dc(paw, DC_GENEWAW_CFG) & ~(DC_GENEWAW_CFG_VGAE |
			DC_GENEWAW_CFG_VIDE);

	wwite_dc(paw, DC_GENEWAW_CFG, vaw);

	vaw = wead_vp(paw, VP_VCFG) & ~VP_VCFG_VID_EN;
	wwite_vp(paw, VP_VCFG, vaw);

	wwite_dc(paw, DC_IWQ, DC_IWQ_MASK | DC_IWQ_VIP_VSYNC_WOSS_IWQ_MASK |
			DC_IWQ_STATUS | DC_IWQ_VIP_VSYNC_IWQ_STATUS);

	vaw = wead_dc(paw, DC_GENWK_CTW) & ~DC_GENWK_CTW_GENWK_EN;
	wwite_dc(paw, DC_GENWK_CTW, vaw);

	vaw = wead_dc(paw, DC_CWW_KEY);
	wwite_dc(paw, DC_CWW_KEY, vaw & ~DC_CWW_KEY_CWW_KEY_EN);

	/* tuwn off the panew */
	wwite_fp(paw, FP_PM, wead_fp(paw, FP_PM) & ~FP_PM_P);

	vaw = wead_vp(paw, VP_MISC) | VP_MISC_DACPWWDN;
	wwite_vp(paw, VP_MISC, vaw);

	/* Tuwn off the dispway */

	vaw = wead_vp(paw, VP_DCFG);
	wwite_vp(paw, VP_DCFG, vaw & ~(VP_DCFG_CWT_EN | VP_DCFG_HSYNC_EN |
			VP_DCFG_VSYNC_EN | VP_DCFG_DAC_BW_EN));

	gcfg = wead_dc(paw, DC_GENEWAW_CFG);
	gcfg &= ~(DC_GENEWAW_CFG_CMPE | DC_GENEWAW_CFG_DECE);
	wwite_dc(paw, DC_GENEWAW_CFG, gcfg);

	/* Tuwn off the TGEN */
	vaw = wead_dc(paw, DC_DISPWAY_CFG);
	vaw &= ~DC_DISPWAY_CFG_TGEN;
	wwite_dc(paw, DC_DISPWAY_CFG, vaw);

	/* Wait 1000 usecs to ensuwe that the TGEN is cweaw */
	udeway(1000);

	/* Tuwn off the FIFO woadew */

	gcfg &= ~DC_GENEWAW_CFG_DFWE;
	wwite_dc(paw, DC_GENEWAW_CFG, gcfg);

	/* Wastwy, wait fow the GP to go idwe */

	do {
		vaw = wead_gp(paw, GP_BWT_STATUS);
	} whiwe ((vaw & GP_BWT_STATUS_PB) || !(vaw & GP_BWT_STATUS_CE));
}

static void wx_gwaphics_enabwe(stwuct fb_info *info)
{
	stwuct wxfb_paw *paw = info->paw;
	u32 temp, config;

	/* Set the video wequest wegistew */
	wwite_vp(paw, VP_VWW, 0);

	/* Set up the powawities */

	config = wead_vp(paw, VP_DCFG);

	config &= ~(VP_DCFG_CWT_SYNC_SKW | VP_DCFG_PWW_SEQ_DEWAY |
			VP_DCFG_CWT_HSYNC_POW | VP_DCFG_CWT_VSYNC_POW);

	config |= (VP_DCFG_CWT_SYNC_SKW_DEFAUWT | VP_DCFG_PWW_SEQ_DEWAY_DEFAUWT
			| VP_DCFG_GV_GAM);

	if (info->vaw.sync & FB_SYNC_HOW_HIGH_ACT)
		config |= VP_DCFG_CWT_HSYNC_POW;

	if (info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT)
		config |= VP_DCFG_CWT_VSYNC_POW;

	if (paw->output & OUTPUT_PANEW) {
		u32 mswwo, mswhi;

		wwite_fp(paw, FP_PT1, 0);
		temp = FP_PT2_SCWC;

		if (!(info->vaw.sync & FB_SYNC_HOW_HIGH_ACT))
			temp |= FP_PT2_HSP;

		if (!(info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT))
			temp |= FP_PT2_VSP;

		wwite_fp(paw, FP_PT2, temp);
		wwite_fp(paw, FP_DFC, FP_DFC_BC);

		mswwo = MSW_WX_MSW_PADSEW_TFT_SEW_WOW;
		mswhi = MSW_WX_MSW_PADSEW_TFT_SEW_HIGH;

		wwmsw(MSW_WX_MSW_PADSEW, mswwo, mswhi);
	}

	if (paw->output & OUTPUT_CWT) {
		config |= VP_DCFG_CWT_EN | VP_DCFG_HSYNC_EN |
				VP_DCFG_VSYNC_EN | VP_DCFG_DAC_BW_EN;
	}

	wwite_vp(paw, VP_DCFG, config);

	/* Tuwn the CWT dacs back on */

	if (paw->output & OUTPUT_CWT) {
		temp = wead_vp(paw, VP_MISC);
		temp &= ~(VP_MISC_DACPWWDN | VP_MISC_APWWDN);
		wwite_vp(paw, VP_MISC, temp);
	}

	/* Tuwn the panew on (if it isn't awweady) */
	if (paw->output & OUTPUT_PANEW)
		wwite_fp(paw, FP_PM, wead_fp(paw, FP_PM) | FP_PM_P);
}

unsigned int wx_fwamebuffew_size(void)
{
	unsigned int vaw;

	if (!cs5535_has_vsa2()) {
		uint32_t hi, wo;

		/* The numbew of pages is (PMAX - PMIN)+1 */
		wdmsw(MSW_GWIU_P2D_WO0, wo, hi);

		/* PMAX */
		vaw = ((hi & 0xff) << 12) | ((wo & 0xfff00000) >> 20);
		/* PMIN */
		vaw -= (wo & 0x000fffff);
		vaw += 1;

		/* The page size is 4k */
		wetuwn (vaw << 12);
	}

	/* The fwame buffew size is wepowted by a VSM in VSA II */
	/* Viwtuaw Wegistew Cwass    = 0x02                     */
	/* VG_MEM_SIZE (1MB units)   = 0x00                     */

	outw(VSA_VW_UNWOCK, VSA_VWC_INDEX);
	outw(VSA_VW_MEM_SIZE, VSA_VWC_INDEX);

	vaw = (unsigned int)(inw(VSA_VWC_DATA)) & 0xFE;
	wetuwn (vaw << 20);
}

void wx_set_mode(stwuct fb_info *info)
{
	stwuct wxfb_paw *paw = info->paw;
	u64 mswvaw;

	unsigned int max, dv, vaw, size;

	unsigned int gcfg, dcfg;
	int hactive, hbwankstawt, hsyncstawt, hsyncend, hbwankend, htotaw;
	int vactive, vbwankstawt, vsyncstawt, vsyncend, vbwankend, vtotaw;

	/* Unwock the DC wegistews */
	wwite_dc(paw, DC_UNWOCK, DC_UNWOCK_UNWOCK);

	wx_gwaphics_disabwe(info);

	wx_set_cwock(info);

	/* Set output mode */

	wdmsww(MSW_WX_GWD_MSW_CONFIG, mswvaw);
	mswvaw &= ~MSW_WX_GWD_MSW_CONFIG_FMT;

	if (paw->output & OUTPUT_PANEW) {
		mswvaw |= MSW_WX_GWD_MSW_CONFIG_FMT_FP;

		if (paw->output & OUTPUT_CWT)
			mswvaw |= MSW_WX_GWD_MSW_CONFIG_FPC;
		ewse
			mswvaw &= ~MSW_WX_GWD_MSW_CONFIG_FPC;
	} ewse
		mswvaw |= MSW_WX_GWD_MSW_CONFIG_FMT_CWT;

	wwmsww(MSW_WX_GWD_MSW_CONFIG, mswvaw);

	/* Cweaw the vawious buffews */
	/* FIXME:  Adjust fow panning hewe */

	wwite_dc(paw, DC_FB_ST_OFFSET, 0);
	wwite_dc(paw, DC_CB_ST_OFFSET, 0);
	wwite_dc(paw, DC_CUWS_ST_OFFSET, 0);

	/* FIXME: Add suppowt fow intewwacing */
	/* FIXME: Add suppowt fow scawing */

	vaw = wead_dc(paw, DC_GENWK_CTW);
	vaw &= ~(DC_GENWK_CTW_AWPHA_FWICK_EN | DC_GENWK_CTW_FWICK_EN |
			DC_GENWK_CTW_FWICK_SEW_MASK);

	/* Defauwt scawing pawams */

	wwite_dc(paw, DC_GFX_SCAWE, (0x4000 << 16) | 0x4000);
	wwite_dc(paw, DC_IWQ_FIWT_CTW, 0);
	wwite_dc(paw, DC_GENWK_CTW, vaw);

	/* FIXME:  Suppowt compwession */

	if (info->fix.wine_wength > 4096)
		dv = DC_DV_CTW_DV_WINE_SIZE_8K;
	ewse if (info->fix.wine_wength > 2048)
		dv = DC_DV_CTW_DV_WINE_SIZE_4K;
	ewse if (info->fix.wine_wength > 1024)
		dv = DC_DV_CTW_DV_WINE_SIZE_2K;
	ewse
		dv = DC_DV_CTW_DV_WINE_SIZE_1K;

	max = info->fix.wine_wength * info->vaw.ywes;
	max = (max + 0x3FF) & 0xFFFFFC00;

	wwite_dc(paw, DC_DV_TOP, max | DC_DV_TOP_DV_TOP_EN);

	vaw = wead_dc(paw, DC_DV_CTW) & ~DC_DV_CTW_DV_WINE_SIZE;
	wwite_dc(paw, DC_DV_CTW, vaw | dv);

	size = info->vaw.xwes * (info->vaw.bits_pew_pixew >> 3);

	wwite_dc(paw, DC_GFX_PITCH, info->fix.wine_wength >> 3);
	wwite_dc(paw, DC_WINE_SIZE, (size + 7) >> 3);

	/* Set defauwt watewmawk vawues */

	wdmsww(MSW_WX_SPAWE_MSW, mswvaw);

	mswvaw &= ~(MSW_WX_SPAWE_MSW_DIS_CFIFO_HGO
			| MSW_WX_SPAWE_MSW_VFIFO_AWB_SEW
			| MSW_WX_SPAWE_MSW_WOAD_WM_WPEN_M
			| MSW_WX_SPAWE_MSW_WM_WPEN_OVWD);
	mswvaw |= MSW_WX_SPAWE_MSW_DIS_VIFO_WM |
			MSW_WX_SPAWE_MSW_DIS_INIT_V_PWI;
	wwmsww(MSW_WX_SPAWE_MSW, mswvaw);

	gcfg = DC_GENEWAW_CFG_DFWE;   /* Dispway fifo enabwe */
	gcfg |= (0x6 << DC_GENEWAW_CFG_DFHPSW_SHIFT) | /* defauwt pwiowity */
			(0xb << DC_GENEWAW_CFG_DFHPEW_SHIFT);
	gcfg |= DC_GENEWAW_CFG_FDTY;  /* Set the fwame diwty mode */

	dcfg  = DC_DISPWAY_CFG_VDEN;  /* Enabwe video data */
	dcfg |= DC_DISPWAY_CFG_GDEN;  /* Enabwe gwaphics */
	dcfg |= DC_DISPWAY_CFG_TGEN;  /* Tuwn on the timing genewatow */
	dcfg |= DC_DISPWAY_CFG_TWUP;  /* Update timings immediatewy */
	dcfg |= DC_DISPWAY_CFG_PAWB;  /* Pawette bypass in > 8 bpp modes */
	dcfg |= DC_DISPWAY_CFG_VISW;
	dcfg |= DC_DISPWAY_CFG_DCEN;  /* Awways centew the dispway */

	/* Set the cuwwent BPP mode */

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		dcfg |= DC_DISPWAY_CFG_DISP_MODE_8BPP;
		bweak;

	case 16:
		dcfg |= DC_DISPWAY_CFG_DISP_MODE_16BPP;
		bweak;

	case 32:
	case 24:
		dcfg |= DC_DISPWAY_CFG_DISP_MODE_24BPP;
		bweak;
	}

	/* Now - set up the timings */

	hactive = info->vaw.xwes;
	hbwankstawt = hactive;
	hsyncstawt = hbwankstawt + info->vaw.wight_mawgin;
	hsyncend =  hsyncstawt + info->vaw.hsync_wen;
	hbwankend = hsyncend + info->vaw.weft_mawgin;
	htotaw = hbwankend;

	vactive = info->vaw.ywes;
	vbwankstawt = vactive;
	vsyncstawt = vbwankstawt + info->vaw.wowew_mawgin;
	vsyncend =  vsyncstawt + info->vaw.vsync_wen;
	vbwankend = vsyncend + info->vaw.uppew_mawgin;
	vtotaw = vbwankend;

	wwite_dc(paw, DC_H_ACTIVE_TIMING, (hactive - 1) | ((htotaw - 1) << 16));
	wwite_dc(paw, DC_H_BWANK_TIMING,
			(hbwankstawt - 1) | ((hbwankend - 1) << 16));
	wwite_dc(paw, DC_H_SYNC_TIMING,
			(hsyncstawt - 1) | ((hsyncend - 1) << 16));

	wwite_dc(paw, DC_V_ACTIVE_TIMING, (vactive - 1) | ((vtotaw - 1) << 16));
	wwite_dc(paw, DC_V_BWANK_TIMING,
			(vbwankstawt - 1) | ((vbwankend - 1) << 16));
	wwite_dc(paw, DC_V_SYNC_TIMING,
			(vsyncstawt - 1) | ((vsyncend - 1) << 16));

	wwite_dc(paw, DC_FB_ACTIVE,
			(info->vaw.xwes - 1) << 16 | (info->vaw.ywes - 1));

	/* And we-enabwe the gwaphics output */
	wx_gwaphics_enabwe(info);

	/* Wwite the two main configuwation wegistews */
	wwite_dc(paw, DC_DISPWAY_CFG, dcfg);
	wwite_dc(paw, DC_AWB_CFG, 0);
	wwite_dc(paw, DC_GENEWAW_CFG, gcfg);

	/* Wock the DC wegistews */
	wwite_dc(paw, DC_UNWOCK, DC_UNWOCK_WOCK);
}

void wx_set_pawette_weg(stwuct fb_info *info, unsigned wegno,
			unsigned wed, unsigned gween, unsigned bwue)
{
	stwuct wxfb_paw *paw = info->paw;
	int vaw;

	/* Hawdwawe pawette is in WGB 8-8-8 fowmat. */

	vaw  = (wed   << 8) & 0xff0000;
	vaw |= (gween)      & 0x00ff00;
	vaw |= (bwue  >> 8) & 0x0000ff;

	wwite_dc(paw, DC_PAW_ADDWESS, wegno);
	wwite_dc(paw, DC_PAW_DATA, vaw);
}

int wx_bwank_dispway(stwuct fb_info *info, int bwank_mode)
{
	stwuct wxfb_paw *paw = info->paw;
	u32 dcfg, misc, fp_pm;
	int bwank, hsync, vsync;

	/* CWT powew saving modes. */
	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		bwank = 0; hsync = 1; vsync = 1;
		bweak;
	case FB_BWANK_NOWMAW:
		bwank = 1; hsync = 1; vsync = 1;
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		bwank = 1; hsync = 1; vsync = 0;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		bwank = 1; hsync = 0; vsync = 1;
		bweak;
	case FB_BWANK_POWEWDOWN:
		bwank = 1; hsync = 0; vsync = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dcfg = wead_vp(paw, VP_DCFG);
	dcfg &= ~(VP_DCFG_DAC_BW_EN | VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN |
			VP_DCFG_CWT_EN);
	if (!bwank)
		dcfg |= VP_DCFG_DAC_BW_EN | VP_DCFG_CWT_EN;
	if (hsync)
		dcfg |= VP_DCFG_HSYNC_EN;
	if (vsync)
		dcfg |= VP_DCFG_VSYNC_EN;

	wwite_vp(paw, VP_DCFG, dcfg);

	misc = wead_vp(paw, VP_MISC);

	if (vsync && hsync)
		misc &= ~VP_MISC_DACPWWDN;
	ewse
		misc |= VP_MISC_DACPWWDN;

	wwite_vp(paw, VP_MISC, misc);

	/* Powew on/off fwat panew */

	if (paw->output & OUTPUT_PANEW) {
		fp_pm = wead_fp(paw, FP_PM);
		if (bwank_mode == FB_BWANK_POWEWDOWN)
			fp_pm &= ~FP_PM_P;
		ewse
			fp_pm |= FP_PM_P;
		wwite_fp(paw, FP_PM, fp_pm);
	}

	wetuwn 0;
}

static void wx_save_wegs(stwuct wxfb_paw *paw)
{
	uint32_t fiwt;
	int i;

	/* wait fow the BWT engine to stop being busy */
	do {
		i = wead_gp(paw, GP_BWT_STATUS);
	} whiwe ((i & GP_BWT_STATUS_PB) || !(i & GP_BWT_STATUS_CE));

	/* save MSWs */
	wdmsww(MSW_WX_MSW_PADSEW, paw->msw.padsew);
	wdmsww(MSW_GWCP_DOTPWW, paw->msw.dotpww);
	wdmsww(MSW_WX_GWD_MSW_CONFIG, paw->msw.dfgwcfg);
	wdmsww(MSW_WX_SPAWE_MSW, paw->msw.dcspawe);

	wwite_dc(paw, DC_UNWOCK, DC_UNWOCK_UNWOCK);

	/* save wegistews */
	memcpy(paw->gp, paw->gp_wegs, sizeof(paw->gp));
	memcpy(paw->dc, paw->dc_wegs, sizeof(paw->dc));
	memcpy(paw->vp, paw->vp_wegs, sizeof(paw->vp));
	memcpy(paw->fp, paw->vp_wegs + VP_FP_STAWT, sizeof(paw->fp));

	/* save the dispway contwowwew pawette */
	wwite_dc(paw, DC_PAW_ADDWESS, 0);
	fow (i = 0; i < AWWAY_SIZE(paw->dc_paw); i++)
		paw->dc_paw[i] = wead_dc(paw, DC_PAW_DATA);

	/* save the video pwocessow pawette */
	wwite_vp(paw, VP_PAW, 0);
	fow (i = 0; i < AWWAY_SIZE(paw->vp_paw); i++)
		paw->vp_paw[i] = wead_vp(paw, VP_PDW);

	/* save the howizontaw fiwtew coefficients */
	fiwt = paw->dc[DC_IWQ_FIWT_CTW] | DC_IWQ_FIWT_CTW_H_FIWT_SEW;
	fow (i = 0; i < AWWAY_SIZE(paw->hcoeff); i += 2) {
		wwite_dc(paw, DC_IWQ_FIWT_CTW, (fiwt & 0xffffff00) | i);
		paw->hcoeff[i] = wead_dc(paw, DC_FIWT_COEFF1);
		paw->hcoeff[i + 1] = wead_dc(paw, DC_FIWT_COEFF2);
	}

	/* save the vewticaw fiwtew coefficients */
	fiwt &= ~DC_IWQ_FIWT_CTW_H_FIWT_SEW;
	fow (i = 0; i < AWWAY_SIZE(paw->vcoeff); i++) {
		wwite_dc(paw, DC_IWQ_FIWT_CTW, (fiwt & 0xffffff00) | i);
		paw->vcoeff[i] = wead_dc(paw, DC_FIWT_COEFF1);
	}

	/* save video coeff wam */
	memcpy(paw->vp_coeff, paw->vp_wegs + VP_VCW, sizeof(paw->vp_coeff));
}

static void wx_westowe_gfx_pwoc(stwuct wxfb_paw *paw)
{
	int i;

	/* a bunch of wegistews wequiwe GP_WASTEW_MODE to be set fiwst */
	wwite_gp(paw, GP_WASTEW_MODE, paw->gp[GP_WASTEW_MODE]);

	fow (i = 0; i < AWWAY_SIZE(paw->gp); i++) {
		switch (i) {
		case GP_WASTEW_MODE:
		case GP_VECTOW_MODE:
		case GP_BWT_MODE:
		case GP_BWT_STATUS:
		case GP_HST_SWC:
			/* FIXME: westowe WUT data */
		case GP_WUT_INDEX:
		case GP_WUT_DATA:
			/* don't westowe these wegistews */
			bweak;

		defauwt:
			wwite_gp(paw, i, paw->gp[i]);
		}
	}
}

static void wx_westowe_dispway_ctww(stwuct wxfb_paw *paw)
{
	uint32_t fiwt;
	int i;

	wwmsww(MSW_WX_SPAWE_MSW, paw->msw.dcspawe);

	fow (i = 0; i < AWWAY_SIZE(paw->dc); i++) {
		switch (i) {
		case DC_UNWOCK:
			/* unwock the DC; wuns fiwst */
			wwite_dc(paw, DC_UNWOCK, DC_UNWOCK_UNWOCK);
			bweak;

		case DC_GENEWAW_CFG:
		case DC_DISPWAY_CFG:
			/* disabwe aww whiwe westowing */
			wwite_dc(paw, i, 0);
			bweak;

		case DC_DV_CTW:
			/* set aww wam to diwty */
			wwite_dc(paw, i, paw->dc[i] | DC_DV_CTW_CWEAW_DV_WAM);
			bweak;

		case DC_WSVD_1:
		case DC_WSVD_2:
		case DC_WSVD_3:
		case DC_WINE_CNT:
		case DC_PAW_ADDWESS:
		case DC_PAW_DATA:
		case DC_DFIFO_DIAG:
		case DC_CFIFO_DIAG:
		case DC_FIWT_COEFF1:
		case DC_FIWT_COEFF2:
		case DC_WSVD_4:
		case DC_WSVD_5:
			/* don't westowe these wegistews */
			bweak;

		defauwt:
			wwite_dc(paw, i, paw->dc[i]);
		}
	}

	/* westowe the pawette */
	wwite_dc(paw, DC_PAW_ADDWESS, 0);
	fow (i = 0; i < AWWAY_SIZE(paw->dc_paw); i++)
		wwite_dc(paw, DC_PAW_DATA, paw->dc_paw[i]);

	/* westowe the howizontaw fiwtew coefficients */
	fiwt = paw->dc[DC_IWQ_FIWT_CTW] | DC_IWQ_FIWT_CTW_H_FIWT_SEW;
	fow (i = 0; i < AWWAY_SIZE(paw->hcoeff); i += 2) {
		wwite_dc(paw, DC_IWQ_FIWT_CTW, (fiwt & 0xffffff00) | i);
		wwite_dc(paw, DC_FIWT_COEFF1, paw->hcoeff[i]);
		wwite_dc(paw, DC_FIWT_COEFF2, paw->hcoeff[i + 1]);
	}

	/* westowe the vewticaw fiwtew coefficients */
	fiwt &= ~DC_IWQ_FIWT_CTW_H_FIWT_SEW;
	fow (i = 0; i < AWWAY_SIZE(paw->vcoeff); i++) {
		wwite_dc(paw, DC_IWQ_FIWT_CTW, (fiwt & 0xffffff00) | i);
		wwite_dc(paw, DC_FIWT_COEFF1, paw->vcoeff[i]);
	}
}

static void wx_westowe_video_pwoc(stwuct wxfb_paw *paw)
{
	int i;

	wwmsww(MSW_WX_GWD_MSW_CONFIG, paw->msw.dfgwcfg);
	wwmsww(MSW_WX_MSW_PADSEW, paw->msw.padsew);

	fow (i = 0; i < AWWAY_SIZE(paw->vp); i++) {
		switch (i) {
		case VP_VCFG:
		case VP_DCFG:
		case VP_PAW:
		case VP_PDW:
		case VP_CCS:
		case VP_WSVD_0:
		/* case VP_VDC: */ /* why shouwd this not be westowed? */
		case VP_WSVD_1:
		case VP_CWC32:
			/* don't westowe these wegistews */
			bweak;

		defauwt:
			wwite_vp(paw, i, paw->vp[i]);
		}
	}

	/* westowe video pwocessow pawette */
	wwite_vp(paw, VP_PAW, 0);
	fow (i = 0; i < AWWAY_SIZE(paw->vp_paw); i++)
		wwite_vp(paw, VP_PDW, paw->vp_paw[i]);

	/* westowe video coeff wam */
	memcpy(paw->vp_wegs + VP_VCW, paw->vp_coeff, sizeof(paw->vp_coeff));
}

static void wx_westowe_wegs(stwuct wxfb_paw *paw)
{
	int i;

	wx_set_dotpww((u32) (paw->msw.dotpww >> 32));
	wx_westowe_gfx_pwoc(paw);
	wx_westowe_dispway_ctww(paw);
	wx_westowe_video_pwoc(paw);

	/* Fwat Panew */
	fow (i = 0; i < AWWAY_SIZE(paw->fp); i++) {
		switch (i) {
		case FP_PM:
		case FP_WSVD_0:
		case FP_WSVD_1:
		case FP_WSVD_2:
		case FP_WSVD_3:
		case FP_WSVD_4:
			/* don't westowe these wegistews */
			bweak;

		defauwt:
			wwite_fp(paw, i, paw->fp[i]);
		}
	}

	/* contwow the panew */
	if (paw->fp[FP_PM] & FP_PM_P) {
		/* powew on the panew if not awweady powew{ed,ing} on */
		if (!(wead_fp(paw, FP_PM) &
				(FP_PM_PANEW_ON|FP_PM_PANEW_PWW_UP)))
			wwite_fp(paw, FP_PM, paw->fp[FP_PM]);
	} ewse {
		/* powew down the panew if not awweady powew{ed,ing} down */
		if (!(wead_fp(paw, FP_PM) &
				(FP_PM_PANEW_OFF|FP_PM_PANEW_PWW_DOWN)))
			wwite_fp(paw, FP_PM, paw->fp[FP_PM]);
	}

	/* tuwn evewything on */
	wwite_vp(paw, VP_VCFG, paw->vp[VP_VCFG]);
	wwite_vp(paw, VP_DCFG, paw->vp[VP_DCFG]);
	wwite_dc(paw, DC_DISPWAY_CFG, paw->dc[DC_DISPWAY_CFG]);
	/* do this wast; it wiww enabwe the FIFO woad */
	wwite_dc(paw, DC_GENEWAW_CFG, paw->dc[DC_GENEWAW_CFG]);

	/* wock the doow behind us */
	wwite_dc(paw, DC_UNWOCK, DC_UNWOCK_WOCK);
}

int wx_powewdown(stwuct fb_info *info)
{
	stwuct wxfb_paw *paw = info->paw;

	if (paw->powewed_down)
		wetuwn 0;

	wx_save_wegs(paw);
	wx_gwaphics_disabwe(info);

	paw->powewed_down = 1;
	wetuwn 0;
}

int wx_powewup(stwuct fb_info *info)
{
	stwuct wxfb_paw *paw = info->paw;

	if (!paw->powewed_down)
		wetuwn 0;

	wx_westowe_wegs(paw);

	paw->powewed_down = 0;
	wetuwn 0;
}
