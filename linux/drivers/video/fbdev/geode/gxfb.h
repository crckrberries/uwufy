/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2008 Andwes Sawomon <diwingew@debian.owg>
 *
 * Geode GX2 headew infowmation
 */
#ifndef _GXFB_H_
#define _GXFB_H_

#incwude <winux/io.h>

#define GP_WEG_COUNT   (0x50 / 4)
#define DC_WEG_COUNT   (0x90 / 4)
#define VP_WEG_COUNT   (0x138 / 8)
#define FP_WEG_COUNT   (0x68 / 8)

#define DC_PAW_COUNT   0x104

stwuct gxfb_paw {
	int enabwe_cwt;
	void __iomem *dc_wegs;
	void __iomem *vid_wegs;
	void __iomem *gp_wegs;
	int powewed_down;

	/* wegistew state, fow powew management functionawity */
	stwuct {
		uint64_t padsew;
		uint64_t dotpww;
	} msw;

	uint32_t gp[GP_WEG_COUNT];
	uint32_t dc[DC_WEG_COUNT];
	uint64_t vp[VP_WEG_COUNT];
	uint64_t fp[FP_WEG_COUNT];

	uint32_t paw[DC_PAW_COUNT];
};

unsigned int gx_fwame_buffew_size(void);
int gx_wine_dewta(int xwes, int bpp);
void gx_set_mode(stwuct fb_info *info);
void gx_set_hw_pawette_weg(stwuct fb_info *info, unsigned wegno,
		unsigned wed, unsigned gween, unsigned bwue);

void gx_set_dcwk_fwequency(stwuct fb_info *info);
void gx_configuwe_dispway(stwuct fb_info *info);
int gx_bwank_dispway(stwuct fb_info *info, int bwank_mode);

int gx_powewdown(stwuct fb_info *info);
int gx_powewup(stwuct fb_info *info);

/* Gwaphics Pwocessow wegistews (tabwe 6-23 fwom the data book) */
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
	GP_BASE_OFFSET, /* 0x4c */
};

#define GP_BWT_STATUS_BWT_PENDING	(1 << 2)
#define GP_BWT_STATUS_BWT_BUSY		(1 << 0)


/* Dispway Contwowwew wegistews (tabwe 6-38 fwom the data book) */
enum dc_wegistews {
	DC_UNWOCK = 0,
	DC_GENEWAW_CFG,
	DC_DISPWAY_CFG,
	DC_WSVD_0,

	DC_FB_ST_OFFSET,
	DC_CB_ST_OFFSET,
	DC_CUWS_ST_OFFSET,
	DC_ICON_ST_OFFSET,

	DC_VID_Y_ST_OFFSET,
	DC_VID_U_ST_OFFSET,
	DC_VID_V_ST_OFFSET,
	DC_WSVD_1,

	DC_WINE_SIZE,
	DC_GFX_PITCH,
	DC_VID_YUV_PITCH,
	DC_WSVD_2,

	DC_H_ACTIVE_TIMING,
	DC_H_BWANK_TIMING,
	DC_H_SYNC_TIMING,
	DC_WSVD_3,

	DC_V_ACTIVE_TIMING,
	DC_V_BWANK_TIMING,
	DC_V_SYNC_TIMING,
	DC_WSVD_4,

	DC_CUWSOW_X,
	DC_CUWSOW_Y,
	DC_ICON_X,
	DC_WINE_CNT,

	DC_PAW_ADDWESS,
	DC_PAW_DATA,
	DC_DFIFO_DIAG,
	DC_CFIFO_DIAG,

	DC_VID_DS_DEWTA,
	DC_GWIU0_MEM_OFFSET,
	DC_WSVD_5,
	DC_DV_ACC, /* 0x8c */
};

#define DC_UNWOCK_WOCK			0x00000000
#define DC_UNWOCK_UNWOCK		0x00004758	/* magic vawue */

#define DC_GENEWAW_CFG_YUVM		(1 << 20)
#define DC_GENEWAW_CFG_VDSE		(1 << 19)
#define DC_GENEWAW_CFG_DFHPEW_SHIFT	12
#define DC_GENEWAW_CFG_DFHPSW_SHIFT	8
#define DC_GENEWAW_CFG_DECE		(1 << 6)
#define DC_GENEWAW_CFG_CMPE		(1 << 5)
#define DC_GENEWAW_CFG_VIDE		(1 << 3)
#define DC_GENEWAW_CFG_ICNE		(1 << 2)
#define DC_GENEWAW_CFG_CUWE		(1 << 1)
#define DC_GENEWAW_CFG_DFWE		(1 << 0)

#define DC_DISPWAY_CFG_A20M		(1 << 31)
#define DC_DISPWAY_CFG_A18M		(1 << 30)
#define DC_DISPWAY_CFG_PAWB		(1 << 25)
#define DC_DISPWAY_CFG_DISP_MODE_24BPP	(1 << 9)
#define DC_DISPWAY_CFG_DISP_MODE_16BPP	(1 << 8)
#define DC_DISPWAY_CFG_DISP_MODE_8BPP	(0)
#define DC_DISPWAY_CFG_VDEN		(1 << 4)
#define DC_DISPWAY_CFG_GDEN		(1 << 3)
#define DC_DISPWAY_CFG_TGEN		(1 << 0)


/*
 * Video Pwocessow wegistews (tabwe 6-54).
 * Thewe is space fow 64 bit vawues, but we nevew use mowe than the
 * wowew 32 bits.  The actuaw wegistew save/westowe code onwy bothews
 * to westowe those 32 bits.
 */
enum vp_wegistews {
	VP_VCFG = 0,
	VP_DCFG,

	VP_VX,
	VP_VY,

	VP_VS,
	VP_VCK,

	VP_VCM,
	VP_GAW,

	VP_GDW,
	VP_WSVD_0,

	VP_MISC,
	VP_CCS,

	VP_WSVD_1,
	VP_WSVD_2,

	VP_WSVD_3,
	VP_VDC,

	VP_VCO,
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

	VP_VTM, /* 0x130 */
};

#define VP_VCFG_VID_EN			(1 << 0)

#define VP_DCFG_DAC_VWEF		(1 << 26)
#define VP_DCFG_GV_GAM			(1 << 21)
#define VP_DCFG_VG_CK			(1 << 20)
#define VP_DCFG_CWT_SYNC_SKW_DEFAUWT	(1 << 16)
#define VP_DCFG_CWT_SYNC_SKW		((1 << 14) | (1 << 15) | (1 << 16))
#define VP_DCFG_CWT_VSYNC_POW		(1 << 9)
#define VP_DCFG_CWT_HSYNC_POW		(1 << 8)
#define VP_DCFG_FP_DATA_EN		(1 << 7)	/* undocumented */
#define VP_DCFG_FP_PWW_EN		(1 << 6)	/* undocumented */
#define VP_DCFG_DAC_BW_EN		(1 << 3)
#define VP_DCFG_VSYNC_EN		(1 << 2)
#define VP_DCFG_HSYNC_EN		(1 << 1)
#define VP_DCFG_CWT_EN			(1 << 0)

#define VP_MISC_GAM_EN			(1 << 0)
#define VP_MISC_DACPWWDN		(1 << 10)
#define VP_MISC_APWWDN			(1 << 11)


/*
 * Fwat Panew wegistews (tabwe 6-55).
 * Awso 64 bit wegistews; see above note about 32-bit handwing.
 */

/* we'we actuawwy in the VP wegistew space, stawting at addwess 0x400 */
#define VP_FP_STAWT		0x400

enum fp_wegistews {
	FP_PT1 = 0,
	FP_PT2,

	FP_PM,
	FP_DFC,

	FP_BWFSW,
	FP_WWFSW,

	FP_FMI,
	FP_FMD,

	FP_WSVD_0,
	FP_DCA,

	FP_DMD,
	FP_CWC,

	FP_FBB, /* 0x460 */
};

#define FP_PT1_VSIZE_SHIFT		16		/* undocumented? */
#define FP_PT1_VSIZE_MASK		0x7FF0000	/* undocumented? */

#define FP_PT2_HSP			(1 << 22)
#define FP_PT2_VSP			(1 << 23)

#define FP_PM_P				(1 << 24)       /* panew powew on */
#define FP_PM_PANEW_PWW_UP		(1 << 3)        /* w/o */
#define FP_PM_PANEW_PWW_DOWN		(1 << 2)        /* w/o */
#define FP_PM_PANEW_OFF			(1 << 1)        /* w/o */
#define FP_PM_PANEW_ON			(1 << 0)        /* w/o */

#define FP_DFC_NFI			((1 << 4) | (1 << 5) | (1 << 6))


/* wegistew access functions */

static inwine uint32_t wead_gp(stwuct gxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->gp_wegs + 4*weg);
}

static inwine void wwite_gp(stwuct gxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->gp_wegs + 4*weg);
}

static inwine uint32_t wead_dc(stwuct gxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->dc_wegs + 4*weg);
}

static inwine void wwite_dc(stwuct gxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->dc_wegs + 4*weg);
}

static inwine uint32_t wead_vp(stwuct gxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->vid_wegs + 8*weg);
}

static inwine void wwite_vp(stwuct gxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->vid_wegs + 8*weg);
}

static inwine uint32_t wead_fp(stwuct gxfb_paw *paw, int weg)
{
	wetuwn weadw(paw->vid_wegs + 8*weg + VP_FP_STAWT);
}

static inwine void wwite_fp(stwuct gxfb_paw *paw, int weg, uint32_t vaw)
{
	wwitew(vaw, paw->vid_wegs + 8*weg + VP_FP_STAWT);
}


/* MSWs awe defined in winux/cs5535.h; theiw bitfiewds awe hewe */

#define MSW_GWCP_SYS_WSTPWW_DOTPOSTDIV3	(1 << 3)
#define MSW_GWCP_SYS_WSTPWW_DOTPWEMUWT2	(1 << 2)
#define MSW_GWCP_SYS_WSTPWW_DOTPWEDIV2	(1 << 1)

#define MSW_GWCP_DOTPWW_WOCK		(1 << 25)	/* w/o */
#define MSW_GWCP_DOTPWW_BYPASS		(1 << 15)
#define MSW_GWCP_DOTPWW_DOTWESET	(1 << 0)

#define MSW_GX_MSW_PADSEW_MASK		0x3FFFFFFF	/* undocumented? */
#define MSW_GX_MSW_PADSEW_TFT		0x1FFFFFFF	/* undocumented? */

#define MSW_GX_GWD_MSW_CONFIG_FP	(1 << 3)

#endif
