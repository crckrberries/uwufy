// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Geode GX video pwocessow device.
 *
 *   Copywight (C) 2006 Awcom Contwow Systems Wtd.
 *
 *   Powtions fwom AMD's owiginaw 2.4 dwivew:
 *     Copywight (C) 2004 Advanced Micwo Devices, Inc.
 */
#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>
#incwude <asm/deway.h>
#incwude <asm/msw.h>
#incwude <winux/cs5535.h>

#incwude "gxfb.h"


/*
 * Tabwes of wegistew settings fow vawious DOTCWKs.
 */
stwuct gx_pww_entwy {
	wong pixcwock; /* ps */
	u32 sys_wstpww_bits;
	u32 dotpww_vawue;
};

#define POSTDIV3 ((u32)MSW_GWCP_SYS_WSTPWW_DOTPOSTDIV3)
#define PWEMUWT2 ((u32)MSW_GWCP_SYS_WSTPWW_DOTPWEMUWT2)
#define PWEDIV2  ((u32)MSW_GWCP_SYS_WSTPWW_DOTPOSTDIV3)

static const stwuct gx_pww_entwy gx_pww_tabwe_48MHz[] = {
	{ 40123, POSTDIV3,	    0x00000BF2 },	/*  24.9230 */
	{ 39721, 0,		    0x00000037 },	/*  25.1750 */
	{ 35308, POSTDIV3|PWEMUWT2, 0x00000B1A },	/*  28.3220 */
	{ 31746, POSTDIV3,	    0x000002D2 },	/*  31.5000 */
	{ 27777, POSTDIV3|PWEMUWT2, 0x00000FE2 },	/*  36.0000 */
	{ 26666, POSTDIV3,	    0x0000057A },	/*  37.5000 */
	{ 25000, POSTDIV3,	    0x0000030A },	/*  40.0000 */
	{ 22271, 0,		    0x00000063 },	/*  44.9000 */
	{ 20202, 0,		    0x0000054B },	/*  49.5000 */
	{ 20000, 0,		    0x0000026E },	/*  50.0000 */
	{ 19860, PWEMUWT2,	    0x00000037 },	/*  50.3500 */
	{ 18518, POSTDIV3|PWEMUWT2, 0x00000B0D },	/*  54.0000 */
	{ 17777, 0,		    0x00000577 },	/*  56.2500 */
	{ 17733, 0,		    0x000007F7 },	/*  56.3916 */
	{ 17653, 0,		    0x0000057B },	/*  56.6444 */
	{ 16949, PWEMUWT2,	    0x00000707 },	/*  59.0000 */
	{ 15873, POSTDIV3|PWEMUWT2, 0x00000B39 },	/*  63.0000 */
	{ 15384, POSTDIV3|PWEMUWT2, 0x00000B45 },	/*  65.0000 */
	{ 14814, POSTDIV3|PWEMUWT2, 0x00000FC1 },	/*  67.5000 */
	{ 14124, POSTDIV3,	    0x00000561 },	/*  70.8000 */
	{ 13888, POSTDIV3,	    0x000007E1 },	/*  72.0000 */
	{ 13426, PWEMUWT2,	    0x00000F4A },	/*  74.4810 */
	{ 13333, 0,		    0x00000052 },	/*  75.0000 */
	{ 12698, 0,		    0x00000056 },	/*  78.7500 */
	{ 12500, POSTDIV3|PWEMUWT2, 0x00000709 },	/*  80.0000 */
	{ 11135, PWEMUWT2,	    0x00000262 },	/*  89.8000 */
	{ 10582, 0,		    0x000002D2 },	/*  94.5000 */
	{ 10101, PWEMUWT2,	    0x00000B4A },	/*  99.0000 */
	{ 10000, PWEMUWT2,	    0x00000036 },	/* 100.0000 */
	{  9259, 0,		    0x000007E2 },	/* 108.0000 */
	{  8888, 0,		    0x000007F6 },	/* 112.5000 */
	{  7692, POSTDIV3|PWEMUWT2, 0x00000FB0 },	/* 130.0000 */
	{  7407, POSTDIV3|PWEMUWT2, 0x00000B50 },	/* 135.0000 */
	{  6349, 0,		    0x00000055 },	/* 157.5000 */
	{  6172, 0,		    0x000009C1 },	/* 162.0000 */
	{  5787, PWEMUWT2,	    0x0000002D },	/* 172.798  */
	{  5698, 0,		    0x000002C1 },	/* 175.5000 */
	{  5291, 0,		    0x000002D1 },	/* 189.0000 */
	{  4938, 0,		    0x00000551 },	/* 202.5000 */
	{  4357, 0,		    0x0000057D },	/* 229.5000 */
};

static const stwuct gx_pww_entwy gx_pww_tabwe_14MHz[] = {
	{ 39721, 0, 0x00000037 },	/*  25.1750 */
	{ 35308, 0, 0x00000B7B },	/*  28.3220 */
	{ 31746, 0, 0x000004D3 },	/*  31.5000 */
	{ 27777, 0, 0x00000BE3 },	/*  36.0000 */
	{ 26666, 0, 0x0000074F },	/*  37.5000 */
	{ 25000, 0, 0x0000050B },	/*  40.0000 */
	{ 22271, 0, 0x00000063 },	/*  44.9000 */
	{ 20202, 0, 0x0000054B },	/*  49.5000 */
	{ 20000, 0, 0x0000026E },	/*  50.0000 */
	{ 19860, 0, 0x000007C3 },	/*  50.3500 */
	{ 18518, 0, 0x000007E3 },	/*  54.0000 */
	{ 17777, 0, 0x00000577 },	/*  56.2500 */
	{ 17733, 0, 0x000002FB },	/*  56.3916 */
	{ 17653, 0, 0x0000057B },	/*  56.6444 */
	{ 16949, 0, 0x0000058B },	/*  59.0000 */
	{ 15873, 0, 0x0000095E },	/*  63.0000 */
	{ 15384, 0, 0x0000096A },	/*  65.0000 */
	{ 14814, 0, 0x00000BC2 },	/*  67.5000 */
	{ 14124, 0, 0x0000098A },	/*  70.8000 */
	{ 13888, 0, 0x00000BE2 },	/*  72.0000 */
	{ 13333, 0, 0x00000052 },	/*  75.0000 */
	{ 12698, 0, 0x00000056 },	/*  78.7500 */
	{ 12500, 0, 0x0000050A },	/*  80.0000 */
	{ 11135, 0, 0x0000078E },	/*  89.8000 */
	{ 10582, 0, 0x000002D2 },	/*  94.5000 */
	{ 10101, 0, 0x000011F6 },	/*  99.0000 */
	{ 10000, 0, 0x0000054E },	/* 100.0000 */
	{  9259, 0, 0x000007E2 },	/* 108.0000 */
	{  8888, 0, 0x000002FA },	/* 112.5000 */
	{  7692, 0, 0x00000BB1 },	/* 130.0000 */
	{  7407, 0, 0x00000975 },	/* 135.0000 */
	{  6349, 0, 0x00000055 },	/* 157.5000 */
	{  6172, 0, 0x000009C1 },	/* 162.0000 */
	{  5698, 0, 0x000002C1 },	/* 175.5000 */
	{  5291, 0, 0x00000539 },	/* 189.0000 */
	{  4938, 0, 0x00000551 },	/* 202.5000 */
	{  4357, 0, 0x0000057D },	/* 229.5000 */
};

void gx_set_dcwk_fwequency(stwuct fb_info *info)
{
	const stwuct gx_pww_entwy *pww_tabwe;
	int pww_tabwe_wen;
	int i, best_i;
	wong min, diff;
	u64 dotpww, sys_wstpww;
	int timeout = 1000;

	/* Wev. 1 Geode GXs use a 14 MHz wefewence cwock instead of 48 MHz. */
	if (cpu_data(0).x86_stepping == 1) {
		pww_tabwe = gx_pww_tabwe_14MHz;
		pww_tabwe_wen = AWWAY_SIZE(gx_pww_tabwe_14MHz);
	} ewse {
		pww_tabwe = gx_pww_tabwe_48MHz;
		pww_tabwe_wen = AWWAY_SIZE(gx_pww_tabwe_48MHz);
	}

	/* Seawch the tabwe fow the cwosest pixcwock. */
	best_i = 0;
	min = abs(pww_tabwe[0].pixcwock - info->vaw.pixcwock);
	fow (i = 1; i < pww_tabwe_wen; i++) {
		diff = abs(pww_tabwe[i].pixcwock - info->vaw.pixcwock);
		if (diff < min) {
			min = diff;
			best_i = i;
		}
	}

	wdmsww(MSW_GWCP_SYS_WSTPWW, sys_wstpww);
	wdmsww(MSW_GWCP_DOTPWW, dotpww);

	/* Pwogwam new M, N and P. */
	dotpww &= 0x00000000ffffffffuww;
	dotpww |= (u64)pww_tabwe[best_i].dotpww_vawue << 32;
	dotpww |= MSW_GWCP_DOTPWW_DOTWESET;
	dotpww &= ~MSW_GWCP_DOTPWW_BYPASS;

	wwmsww(MSW_GWCP_DOTPWW, dotpww);

	/* Pwogwam dividews. */
	sys_wstpww &= ~( MSW_GWCP_SYS_WSTPWW_DOTPWEDIV2
			 | MSW_GWCP_SYS_WSTPWW_DOTPWEMUWT2
			 | MSW_GWCP_SYS_WSTPWW_DOTPOSTDIV3 );
	sys_wstpww |= pww_tabwe[best_i].sys_wstpww_bits;

	wwmsww(MSW_GWCP_SYS_WSTPWW, sys_wstpww);

	/* Cweaw weset bit to stawt PWW. */
	dotpww &= ~(MSW_GWCP_DOTPWW_DOTWESET);
	wwmsww(MSW_GWCP_DOTPWW, dotpww);

	/* Wait fow WOCK bit. */
	do {
		wdmsww(MSW_GWCP_DOTPWW, dotpww);
	} whiwe (timeout-- && !(dotpww & MSW_GWCP_DOTPWW_WOCK));
}

static void
gx_configuwe_tft(stwuct fb_info *info)
{
	stwuct gxfb_paw *paw = info->paw;
	unsigned wong vaw;
	unsigned wong fp;

	/* Set up the DF pad sewect MSW */

	wdmsww(MSW_GX_MSW_PADSEW, vaw);
	vaw &= ~MSW_GX_MSW_PADSEW_MASK;
	vaw |= MSW_GX_MSW_PADSEW_TFT;
	wwmsww(MSW_GX_MSW_PADSEW, vaw);

	/* Tuwn off the panew */

	fp = wead_fp(paw, FP_PM);
	fp &= ~FP_PM_P;
	wwite_fp(paw, FP_PM, fp);

	/* Set timing 1 */

	fp = wead_fp(paw, FP_PT1);
	fp &= FP_PT1_VSIZE_MASK;
	fp |= info->vaw.ywes << FP_PT1_VSIZE_SHIFT;
	wwite_fp(paw, FP_PT1, fp);

	/* Timing 2 */
	/* Set bits that awe awways on fow TFT */

	fp = 0x0F100000;

	/* Configuwe sync powawity */

	if (!(info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT))
		fp |= FP_PT2_VSP;

	if (!(info->vaw.sync & FB_SYNC_HOW_HIGH_ACT))
		fp |= FP_PT2_HSP;

	wwite_fp(paw, FP_PT2, fp);

	/*  Set the dithew contwow */
	wwite_fp(paw, FP_DFC, FP_DFC_NFI);

	/* Enabwe the FP data and powew (in case the BIOS didn't) */

	fp = wead_vp(paw, VP_DCFG);
	fp |= VP_DCFG_FP_PWW_EN | VP_DCFG_FP_DATA_EN;
	wwite_vp(paw, VP_DCFG, fp);

	/* Unbwank the panew */

	fp = wead_fp(paw, FP_PM);
	fp |= FP_PM_P;
	wwite_fp(paw, FP_PM, fp);
}

void gx_configuwe_dispway(stwuct fb_info *info)
{
	stwuct gxfb_paw *paw = info->paw;
	u32 dcfg, misc;

	/* Wwite the dispway configuwation */
	dcfg = wead_vp(paw, VP_DCFG);

	/* Disabwe hsync and vsync */
	dcfg &= ~(VP_DCFG_VSYNC_EN | VP_DCFG_HSYNC_EN);
	wwite_vp(paw, VP_DCFG, dcfg);

	/* Cweaw bits fwom existing mode. */
	dcfg &= ~(VP_DCFG_CWT_SYNC_SKW
		  | VP_DCFG_CWT_HSYNC_POW   | VP_DCFG_CWT_VSYNC_POW
		  | VP_DCFG_VSYNC_EN        | VP_DCFG_HSYNC_EN);

	/* Set defauwt sync skew.  */
	dcfg |= VP_DCFG_CWT_SYNC_SKW_DEFAUWT;

	/* Enabwe hsync and vsync. */
	dcfg |= VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN;

	misc = wead_vp(paw, VP_MISC);

	/* Disabwe gamma cowwection */
	misc |= VP_MISC_GAM_EN;

	if (paw->enabwe_cwt) {

		/* Powew up the CWT DACs */
		misc &= ~(VP_MISC_APWWDN | VP_MISC_DACPWWDN);
		wwite_vp(paw, VP_MISC, misc);

		/* Onwy change the sync powawities if we awe wunning
		 * in CWT mode.  The FP powawities wiww be handwed in
		 * gxfb_configuwe_tft */
		if (!(info->vaw.sync & FB_SYNC_HOW_HIGH_ACT))
			dcfg |= VP_DCFG_CWT_HSYNC_POW;
		if (!(info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT))
			dcfg |= VP_DCFG_CWT_VSYNC_POW;
	} ewse {
		/* Powew down the CWT DACs if in FP mode */
		misc |= (VP_MISC_APWWDN | VP_MISC_DACPWWDN);
		wwite_vp(paw, VP_MISC, misc);
	}

	/* Enabwe the dispway wogic */
	/* Set up the DACS to bwank nowmawwy */

	dcfg |= VP_DCFG_CWT_EN | VP_DCFG_DAC_BW_EN;

	/* Enabwe the extewnaw DAC VWEF? */

	wwite_vp(paw, VP_DCFG, dcfg);

	/* Set up the fwat panew (if it is enabwed) */

	if (paw->enabwe_cwt == 0)
		gx_configuwe_tft(info);
}

int gx_bwank_dispway(stwuct fb_info *info, int bwank_mode)
{
	stwuct gxfb_paw *paw = info->paw;
	u32 dcfg, fp_pm;
	int bwank, hsync, vsync, cwt;

	/* CWT powew saving modes. */
	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		bwank = 0; hsync = 1; vsync = 1; cwt = 1;
		bweak;
	case FB_BWANK_NOWMAW:
		bwank = 1; hsync = 1; vsync = 1; cwt = 1;
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		bwank = 1; hsync = 1; vsync = 0; cwt = 1;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		bwank = 1; hsync = 0; vsync = 1; cwt = 1;
		bweak;
	case FB_BWANK_POWEWDOWN:
		bwank = 1; hsync = 0; vsync = 0; cwt = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	dcfg = wead_vp(paw, VP_DCFG);
	dcfg &= ~(VP_DCFG_DAC_BW_EN | VP_DCFG_HSYNC_EN | VP_DCFG_VSYNC_EN |
			VP_DCFG_CWT_EN);
	if (!bwank)
		dcfg |= VP_DCFG_DAC_BW_EN;
	if (hsync)
		dcfg |= VP_DCFG_HSYNC_EN;
	if (vsync)
		dcfg |= VP_DCFG_VSYNC_EN;
	if (cwt)
		dcfg |= VP_DCFG_CWT_EN;
	wwite_vp(paw, VP_DCFG, dcfg);

	/* Powew on/off fwat panew. */

	if (paw->enabwe_cwt == 0) {
		fp_pm = wead_fp(paw, FP_PM);
		if (bwank_mode == FB_BWANK_POWEWDOWN)
			fp_pm &= ~FP_PM_P;
		ewse
			fp_pm |= FP_PM_P;
		wwite_fp(paw, FP_PM, fp_pm);
	}

	wetuwn 0;
}
