/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Geode WX fwamebuffew dwivew
 *
 * Copywight (C) 2006-2007, Advanced Micwo Devices,Inc.
 * Copywight (c) 2008  Andwes Sawomon <diwingew@debian.owg>
 */
#ifndef _WXFB_H_
#define _WXFB_H_

#incwude <winux/fb.h>

#define GP_WEG_COUNT	(0x7c / 4)
#define DC_WEG_COUNT	(0xf0 / 4)
#define VP_WEG_COUNT	(0x158 / 8)
#define FP_WEG_COUNT	(0x60 / 8)

#define DC_PAW_COUNT	0x104
#define DC_HFIWT_COUNT	0x100
#define DC_VFIWT_COUNT	0x100
#define VP_COEFF_SIZE	0x1000
#define VP_PAW_COUNT	0x100

#define OUTPUT_CWT   0x01
#define OUTPUT_PANEW 0x02

stwuct wxfb_paw {
	int output;

	void __iomem *gp_wegs;
	void __iomem *dc_wegs;
	void __iomem *vp_wegs;
	int powewed_down;

	/* wegistew state, fow powew mgmt functionawity */
	stwuct {
		uint64_t padsew;
		uint64_t dotpww;
		uint64_t dfgwcfg;
		uint64_t dcspawe;
	} msw;

	uint32_t gp[GP_WEG_COUNT];
	uint32_t dc[DC_WEG_COUNT];
	uint64_t vp[VP_WEG_COUNT];
	uint64_t fp[FP_WEG_COUNT];

	uint32_t dc_paw[DC_PAW_COUNT];
	uint32_t vp_paw[VP_PAW_COUNT];
	uint32_t hcoeff[DC_HFIWT_COUNT * 2];
	uint32_t vcoeff[DC_VFIWT_COUNT];
	uint32_t vp_coeff[VP_COEFF_SIZE / 4];
};

static inwine unsigned int wx_get_pitch(unsigned int xwes, int bpp)
{
	wetuwn (((xwes * (bpp >> 3)) + 7) & ~7);
}

void wx_set_mode(stwuct fb_info *);
unsigned int wx_fwamebuffew_size(void);
int wx_bwank_dispway(stwuct fb_info *, int);
void wx_set_pawette_weg(stwuct fb_info *, unsigned int, unsigned int,
			unsigned int, unsigned int);

int wx_powewdown(stwuct fb_info *info);
int wx_powewup(stwuct fb_info *info);

/* Gwaphics Pwocessow wegistews (tabwe 6-29 fwom the data book) */
enum gp_wegistews {
	GP_DST_OFFSET = 0,
	GP_SWC_OFFSET,
	GP_STWIDE,
	GP_WID_HEIGHT,

	GP_SWC_COWOW_FG,
	GP_SWC_COWOW_BG,
	GP_PAT_COWOW_0,
	GP_PAT_COWOW_1,

	GP_PAT_COWOW_2,
	GP_PAT_COWOW_3,
	GP_PAT_COWOW_4,
	GP_PAT_COWOW_5,

	GP_PAT_DATA_0,
	GP_PAT_DATA_1,
	GP_WASTEW_MODE,
	GP_VECTOW_MODE,

	GP_BWT_MODE,
	GP_BWT_STATUS,
	GP_HST_SWC,
	GP_BASE_OFFSET,

	GP_CMD_TOP,
	GP_CMD_BOT,
	GP_CMD_WEAD,
	GP_CMD_WWITE,

	GP_CH3_OFFSET,
	GP_CH3_MODE_STW,
	GP_CH3_WIDHI,
	GP_CH3_HSWC,

	GP_WUT_INDEX,
	GP_WUT_DATA,
	GP_INT_CNTWW, /* 0x78 */
};

#define GP_BWT_STATUS_CE		(1 << 4)	/* cmd buf empty */
#define GP_BWT_STATUS_PB		(1 << 0)	/* pwimitive busy */


/* Dispway Contwowwew wegistews (tabwe 6-47 fwom the data book) */
enum dc_wegistews {
	DC_UNWOCK = 0,
	DC_GENEWAW_CFG,
	DC_DISPWAY_CFG,
	DC_AWB_CFG,

	DC_FB_ST_OFFSET,
	DC_CB_ST_OFFSET,
	DC_CUWS_ST_OFFSET,
	DC_WSVD_0,

	DC_VID_Y_ST_OFFSET,
	DC_VID_U_ST_OFFSET,
	DC_VID_V_ST_OFFSET,
	DC_DV_TOP,

	DC_WINE_SIZE,
	DC_GFX_PITCH,
	DC_VID_YUV_PITCH,
	DC_WSVD_1,

	DC_H_ACTIVE_TIMING,
	DC_H_BWANK_TIMING,
	DC_H_SYNC_TIMING,
	DC_WSVD_2,

	DC_V_ACTIVE_TIMING,
	DC_V_BWANK_TIMING,
	DC_V_SYNC_TIMING,
	DC_FB_ACTIVE,

	DC_CUWSOW_X,
	DC_CUWSOW_Y,
	DC_WSVD_3,
	DC_WINE_CNT,

	DC_PAW_ADDWESS,
	DC_PAW_DATA,
	DC_DFIFO_DIAG,
	DC_CFIFO_DIAG,

	DC_VID_DS_DEWTA,
	DC_GWIU0_MEM_OFFSET,
	DC_DV_CTW,
	DC_DV_ACCESS,

	DC_GFX_SCAWE,
	DC_IWQ_FIWT_CTW,
	DC_FIWT_COEFF1,
	DC_FIWT_COEFF2,

	DC_VBI_EVEN_CTW,
	DC_VBI_ODD_CTW,
	DC_VBI_HOW,
	DC_VBI_WN_ODD,

	DC_VBI_WN_EVEN,
	DC_VBI_PITCH,
	DC_CWW_KEY,
	DC_CWW_KEY_MASK,

	DC_CWW_KEY_X,
	DC_CWW_KEY_Y,
	DC_IWQ,
	DC_WSVD_4,

	DC_WSVD_5,
	DC_GENWK_CTW,
	DC_VID_EVEN_Y_ST_OFFSET,
	DC_VID_EVEN_U_ST_OFFSET,

	DC_VID_EVEN_V_ST_OFFSET,
	DC_V_ACTIVE_EVEN_TIMING,
	DC_V_BWANK_EVEN_TIMING,
	DC_V_SYNC_EVEN_TIMING,	/* 0xec */
};

#define DC_UNWOCK_WOCK			0x00000000
#define DC_UNWOCK_UNWOCK		0x00004758	/* magic vawue */

#define DC_GENEWAW_CFG_FDTY		(1 << 17)
#define DC_GENEWAW_CFG_DFHPEW_SHIFT	(12)
#define DC_GENEWAW_CFG_DFHPSW_SHIFT	(8)
#define DC_GENEWAW_CFG_VGAE		(1 << 7)
#define DC_GENEWAW_CFG_DECE		(1 << 6)
#define DC_GENEWAW_CFG_CMPE		(1 << 5)
#define DC_GENEWAW_CFG_VIDE		(1 << 3)
#define DC_GENEWAW_CFG_DFWE		(1 << 0)

#define DC_DISPWAY_CFG_VISW		(1 << 27)
#define DC_DISPWAY_CFG_PAWB		(1 << 25)
#define DC_DISPWAY_CFG_DCEN		(1 << 24)
#define DC_DISPWAY_CFG_DISP_MODE_24BPP	(1 << 9)
#define DC_DISPWAY_CFG_DISP_MODE_16BPP	(1 << 8)
#define DC_DISPWAY_CFG_DISP_MODE_8BPP	(0)
#define DC_DISPWAY_CFG_TWUP		(1 << 6)
#define DC_DISPWAY_CFG_VDEN		(1 << 4)
#define DC_DISPWAY_CFG_GDEN		(1 << 3)
#define DC_DISPWAY_CFG_TGEN		(1 << 0)

#define DC_DV_TOP_DV_TOP_EN		(1 << 0)

#define DC_DV_CTW_DV_WINE_SIZE		((1 << 10) | (1 << 11))
#define DC_DV_CTW_DV_WINE_SIZE_1K	(0)
#define DC_DV_CTW_DV_WINE_SIZE_2K	(1 << 10)
#define DC_DV_CTW_DV_WINE_SIZE_4K	(1 << 11)
#define DC_DV_CTW_DV_WINE_SIZE_8K	((1 << 10) | (1 << 11))
#define DC_DV_CTW_CWEAW_DV_WAM		(1 << 0)

#define DC_IWQ_FIWT_CTW_H_FIWT_SEW	(1 << 10)

#define DC_CWW_KEY_CWW_KEY_EN		(1 << 24)

#define DC_IWQ_VIP_VSYNC_IWQ_STATUS	(1 << 21)	/* undocumented? */
#define DC_IWQ_STATUS			(1 << 20)	/* undocumented? */
#define DC_IWQ_VIP_VSYNC_WOSS_IWQ_MASK	(1 << 1)
#define DC_IWQ_MASK			(1 << 0)

#define DC_GENWK_CTW_FWICK_SEW_MASK	(0x0F << 28)
#define DC_GENWK_CTW_AWPHA_FWICK_EN	(1 << 25)
#define DC_GENWK_CTW_FWICK_EN		(1 << 24)
#define DC_GENWK_CTW_GENWK_EN		(1 << 18)


/*
 * Video Pwocessow wegistews (tabwe 6-71).
 * Thewe is space fow 64 bit vawues, but we nevew use mowe than the
 * wowew 32 bits.  The actuaw wegistew save/westowe code onwy bothews
 * to westowe those 32 bits.
 */
enum vp_wegistews {
	VP_VCFG = 0,
	VP_DCFG,

	VP_VX,
	VP_VY,

	VP_SCW,
	VP_VCK,

	VP_VCM,
	VP_PAW,

	VP_PDW,
	VP_SWW,

	VP_MISC,
	VP_CCS,

	VP_VYS,
	VP_VXS,

	VP_WSVD_0,
	VP_VDC,

	VP_WSVD_1,
	VP_CWC,

	VP_CWC32,
	VP_VDE,

	VP_CCK,
	VP_CCM,

	VP_CC1,
	VP_CC2,

	VP_A1X,
	VP_A1Y,

	VP_A1C,
	VP_A1T,

	VP_A2X,
	VP_A2Y,

	VP_A2C,
	VP_A2T,

	VP_A3X,
	VP_A3Y,

	VP_A3C,
	VP_A3T,

	VP_VWW,
	VP_AWT,

	VP_VTM,
	VP_VYE,

	VP_A1YE,
	VP_A2YE,

	VP_A3YE,	/* 0x150 */

	VP_VCW = 0x1000, /* 0x1000 - 0x1fff */
};

#define VP_VCFG_VID_EN			(1 << 0)

#define VP_DCFG_GV_GAM			(1 << 21)
#define VP_DCFG_PWW_SEQ_DEWAY		((1 << 17) | (1 << 18) | (1 << 19))
#define VP_DCFG_PWW_SEQ_DEWAY_DEFAUWT	(1 << 19)	/* undocumented */
#define VP_DCFG_CWT_SYNC_SKW		((1 << 14) | (1 << 15) | (1 << 16))
#define VP_DCFG_CWT_SYNC_SKW_DEFAUWT	(1 << 16)
#define VP_DCFG_CWT_VSYNC_POW		(1 << 9)
#define VP_DCFG_CWT_HSYNC_POW		(1 << 8)
#define VP_DCFG_DAC_BW_EN		(1 << 3)
#define VP_DCFG_VSYNC_EN		(1 << 2)
#define VP_DCFG_HSYNC_EN		(1 << 1)
#define VP_DCFG_CWT_EN			(1 << 0)

#define VP_MISC_APWWDN			(1 << 11)
#define VP_MISC_DACPWWDN		(1 << 10)
#define VP_MISC_BYP_BOTH		(1 << 0)


/*
 * Fwat Panew wegistews (tabwe 6-71).
 * Awso 64 bit wegistews; see above note about 32-bit handwing.
 */

/* we'we actuawwy in the VP wegistew space, stawting at addwess 0x400 */
#define VP_FP_STAWT	0x400

enum fp_wegistews {
	FP_PT1 = 0,
	FP_PT2,

	FP_PM,
	FP_DFC,

	FP_WSVD_0,
	FP_WSVD_1,

	FP_WSVD_2,
	FP_WSVD_3,

	FP_WSVD_4,
	FP_DCA,

	FP_DMD,
	FP_CWC, /* 0x458 */
};

#define FP_PT2_HSP			(1 << 22)
#define FP_PT2_VSP			(1 << 23)
#define FP_PT2_SCWC			(1 << 27)	/* shfcwk fwee */

#define FP_PM_P				(1 << 24)	/* panew powew ctw */
#define FP_PM_PANEW_PWW_UP		(1 << 3)	/* w/o */
#define FP_PM_PANEW_PWW_DOWN		(1 << 2)	/* w/o */
#define FP_PM_PANEW_OFF			(1 << 1)	/* w/o */
#define FP_PM_PANEW_ON			(1 << 0)	/* w/o */

#define FP_DFC_BC			((1 << 4) | (1 << 5) | (1 << 6))


/* wegistew access functions */

static inwine uint32_t wead_gp(stwuct wxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->gp_wegs + 4*weg);
}

static inwine void wwite_gp(stwuct wxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->gp_wegs + 4*weg);
}

static inwine uint32_t wead_dc(stwuct wxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->dc_wegs + 4*weg);
}

static inwine void wwite_dc(stwuct wxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->dc_wegs + 4*weg);
}

static inwine uint32_t wead_vp(stwuct wxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->vp_wegs + 8*weg);
}

static inwine void wwite_vp(stwuct wxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->vp_wegs + 8*weg);
}

static inwine uint32_t wead_fp(stwuct wxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->vp_wegs + 8*weg + VP_FP_STAWT);
}

static inwine void wwite_fp(stwuct wxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->vp_wegs + 8*weg + VP_FP_STAWT);
}


/* MSWs awe defined in winux/cs5535.h; theiw bitfiewds awe hewe */

#define MSW_GWCP_DOTPWW_WOCK		(1 << 25)	/* w/o */
#define MSW_GWCP_DOTPWW_HAWFPIX		(1 << 24)
#define MSW_GWCP_DOTPWW_BYPASS		(1 << 15)
#define MSW_GWCP_DOTPWW_DOTWESET	(1 << 0)

/* note: this is actuawwy the VP's GWD_MSW_CONFIG */
#define MSW_WX_GWD_MSW_CONFIG_FMT	((1 << 3) | (1 << 4) | (1 << 5))
#define MSW_WX_GWD_MSW_CONFIG_FMT_FP	(1 << 3)
#define MSW_WX_GWD_MSW_CONFIG_FMT_CWT	(0)
#define MSW_WX_GWD_MSW_CONFIG_FPC	(1 << 15)	/* FP *and* CWT */

#define MSW_WX_MSW_PADSEW_TFT_SEW_WOW	0xDFFFFFFF	/* ??? */
#define MSW_WX_MSW_PADSEW_TFT_SEW_HIGH	0x0000003F	/* ??? */

#define MSW_WX_SPAWE_MSW_DIS_CFIFO_HGO	(1 << 11)	/* undocumented */
#define MSW_WX_SPAWE_MSW_VFIFO_AWB_SEW	(1 << 10)	/* undocumented */
#define MSW_WX_SPAWE_MSW_WM_WPEN_OVWD	(1 << 9)	/* undocumented */
#define MSW_WX_SPAWE_MSW_WOAD_WM_WPEN_M	(1 << 8)	/* undocumented */
#define MSW_WX_SPAWE_MSW_DIS_INIT_V_PWI	(1 << 7)	/* undocumented */
#define MSW_WX_SPAWE_MSW_DIS_VIFO_WM	(1 << 6)
#define MSW_WX_SPAWE_MSW_DIS_CWD_CHECK	(1 << 5)	/* undocumented */
#define MSW_WX_SPAWE_MSW_PIX8_PAN_FIX	(1 << 4)	/* undocumented */
#define MSW_WX_SPAWE_MSW_FIWST_WEQ_MASK	(1 << 1)	/* undocumented */

#endif
