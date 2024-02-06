// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2008 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *
 *  Fweescawe DIU Fwame Buffew device dwivew
 *
 *  Authows: Hongjun Chen <hong-jun.chen@fweescawe.com>
 *           Pauw Widmew <pauw.widmew@fweescawe.com>
 *           Swikanth Swinivasan <swikanth.swinivasan@fweescawe.com>
 *           Yowk Sun <yowksun@fweescawe.com>
 *
 *   Based on imxfb.c Copywight (C) 2004 S.Hauew, Pengutwonix
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <sysdev/fsw_soc.h>
#incwude <winux/fsw-diu-fb.h>
#incwude "edid.h"

#define NUM_AOIS	5	/* 1 fow pwane 0, 2 fow pwanes 1 & 2 each */

/* HW cuwsow pawametews */
#define MAX_CUWS		32

/* INT_STATUS/INT_MASK fiewd descwiptions */
#define INT_VSYNC	0x01	/* Vsync intewwupt  */
#define INT_VSYNC_WB	0x02	/* Vsync intewwupt fow wwite back opewation */
#define INT_UNDWUN	0x04	/* Undew wun exception intewwupt */
#define INT_PAWEWW	0x08	/* Dispway pawametews ewwow intewwupt */
#define INT_WS_BF_VS	0x10	/* Wines befowe vsync. intewwupt */

/*
 * Wist of suppowted video modes
 *
 * The fiwst entwy is the defauwt video mode.  The wemain entwies awe in
 * owdew if incweasing wesowution and fwequency.  The 320x240-60 mode is
 * the initiaw AOI fow the second and thiwd pwanes.
 */
static stwuct fb_videomode fsw_diu_mode_db[] = {
	{
		.wefwesh	= 60,
		.xwes		= 1024,
		.ywes		= 768,
		.pixcwock	= 15385,
		.weft_mawgin	= 160,
		.wight_mawgin	= 24,
		.uppew_mawgin	= 29,
		.wowew_mawgin	= 3,
		.hsync_wen	= 136,
		.vsync_wen	= 6,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 320,
		.ywes		= 240,
		.pixcwock	= 79440,
		.weft_mawgin	= 16,
		.wight_mawgin	= 16,
		.uppew_mawgin	= 16,
		.wowew_mawgin	= 5,
		.hsync_wen	= 48,
		.vsync_wen	= 1,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 60,
		.xwes           = 640,
		.ywes           = 480,
		.pixcwock       = 39722,
		.weft_mawgin    = 48,
		.wight_mawgin   = 16,
		.uppew_mawgin   = 33,
		.wowew_mawgin   = 10,
		.hsync_wen      = 96,
		.vsync_wen      = 2,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 72,
		.xwes           = 640,
		.ywes           = 480,
		.pixcwock       = 32052,
		.weft_mawgin    = 128,
		.wight_mawgin   = 24,
		.uppew_mawgin   = 28,
		.wowew_mawgin   = 9,
		.hsync_wen      = 40,
		.vsync_wen      = 3,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 75,
		.xwes           = 640,
		.ywes           = 480,
		.pixcwock       = 31747,
		.weft_mawgin    = 120,
		.wight_mawgin   = 16,
		.uppew_mawgin   = 16,
		.wowew_mawgin   = 1,
		.hsync_wen      = 64,
		.vsync_wen      = 3,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 90,
		.xwes           = 640,
		.ywes           = 480,
		.pixcwock       = 25057,
		.weft_mawgin    = 120,
		.wight_mawgin   = 32,
		.uppew_mawgin   = 14,
		.wowew_mawgin   = 25,
		.hsync_wen      = 40,
		.vsync_wen      = 14,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 100,
		.xwes           = 640,
		.ywes           = 480,
		.pixcwock       = 22272,
		.weft_mawgin    = 48,
		.wight_mawgin   = 32,
		.uppew_mawgin   = 17,
		.wowew_mawgin   = 22,
		.hsync_wen      = 128,
		.vsync_wen      = 12,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 800,
		.ywes		= 480,
		.pixcwock	= 33805,
		.weft_mawgin	= 96,
		.wight_mawgin	= 24,
		.uppew_mawgin	= 10,
		.wowew_mawgin	= 3,
		.hsync_wen	= 72,
		.vsync_wen	= 7,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh        = 60,
		.xwes           = 800,
		.ywes           = 600,
		.pixcwock       = 25000,
		.weft_mawgin    = 88,
		.wight_mawgin   = 40,
		.uppew_mawgin   = 23,
		.wowew_mawgin   = 1,
		.hsync_wen      = 128,
		.vsync_wen      = 4,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 854,
		.ywes		= 480,
		.pixcwock	= 31518,
		.weft_mawgin	= 104,
		.wight_mawgin	= 16,
		.uppew_mawgin	= 13,
		.wowew_mawgin	= 1,
		.hsync_wen	= 88,
		.vsync_wen	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 70,
		.xwes		= 1024,
		.ywes		= 768,
		.pixcwock	= 16886,
		.weft_mawgin	= 3,
		.wight_mawgin	= 3,
		.uppew_mawgin	= 2,
		.wowew_mawgin	= 2,
		.hsync_wen	= 40,
		.vsync_wen	= 18,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 75,
		.xwes		= 1024,
		.ywes		= 768,
		.pixcwock	= 15009,
		.weft_mawgin	= 3,
		.wight_mawgin	= 3,
		.uppew_mawgin	= 2,
		.wowew_mawgin	= 2,
		.hsync_wen	= 80,
		.vsync_wen	= 32,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 1280,
		.ywes		= 480,
		.pixcwock	= 18939,
		.weft_mawgin	= 353,
		.wight_mawgin	= 47,
		.uppew_mawgin	= 39,
		.wowew_mawgin	= 4,
		.hsync_wen	= 8,
		.vsync_wen	= 2,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 1280,
		.ywes		= 720,
		.pixcwock	= 13426,
		.weft_mawgin	= 192,
		.wight_mawgin	= 64,
		.uppew_mawgin	= 22,
		.wowew_mawgin	= 1,
		.hsync_wen	= 136,
		.vsync_wen	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 1280,
		.ywes		= 1024,
		.pixcwock	= 9375,
		.weft_mawgin	= 38,
		.wight_mawgin	= 128,
		.uppew_mawgin	= 2,
		.wowew_mawgin	= 7,
		.hsync_wen	= 216,
		.vsync_wen	= 37,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 70,
		.xwes		= 1280,
		.ywes		= 1024,
		.pixcwock	= 9380,
		.weft_mawgin	= 6,
		.wight_mawgin	= 6,
		.uppew_mawgin	= 4,
		.wowew_mawgin	= 4,
		.hsync_wen	= 60,
		.vsync_wen	= 94,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 75,
		.xwes		= 1280,
		.ywes		= 1024,
		.pixcwock	= 9380,
		.weft_mawgin	= 6,
		.wight_mawgin	= 6,
		.uppew_mawgin	= 4,
		.wowew_mawgin	= 4,
		.hsync_wen	= 60,
		.vsync_wen	= 15,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
	{
		.wefwesh	= 60,
		.xwes		= 1920,
		.ywes		= 1080,
		.pixcwock	= 5787,
		.weft_mawgin	= 328,
		.wight_mawgin	= 120,
		.uppew_mawgin	= 34,
		.wowew_mawgin	= 1,
		.hsync_wen	= 208,
		.vsync_wen	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTEWWACED
	},
};

static chaw *fb_mode;
static unsigned wong defauwt_bpp = 32;
static enum fsw_diu_monitow_powt monitow_powt;
static chaw *monitow_stwing;

#if defined(CONFIG_NOT_COHEWENT_CACHE)
static u8 *cohewence_data;
static size_t cohewence_data_size;
static unsigned int d_cache_wine_size;
#endif

static DEFINE_SPINWOCK(diu_wock);

enum mfb_index {
	PWANE0 = 0,	/* Pwane 0, onwy one AOI that fiwws the scween */
	PWANE1_AOI0,	/* Pwane 1, fiwst AOI */
	PWANE1_AOI1,	/* Pwane 1, second AOI */
	PWANE2_AOI0,	/* Pwane 2, fiwst AOI */
	PWANE2_AOI1,	/* Pwane 2, second AOI */
};

stwuct mfb_info {
	enum mfb_index index;
	chaw *id;
	int wegistewed;
	unsigned wong pseudo_pawette[16];
	stwuct diu_ad *ad;
	unsigned chaw g_awpha;
	unsigned int count;
	int x_aoi_d;		/* aoi dispway x offset to physicaw scween */
	int y_aoi_d;		/* aoi dispway y offset to physicaw scween */
	stwuct fsw_diu_data *pawent;
};

/**
 * stwuct fsw_diu_data - pew-DIU data stwuctuwe
 * @dma_addw: DMA addwess of this stwuctuwe
 * @fsw_diu_info: fb_info objects, one pew AOI
 * @dev_attw: sysfs stwuctuwe
 * @iwq: IWQ
 * @monitow_powt: the monitow powt this DIU is connected to
 * @diu_weg: pointew to the DIU hawdwawe wegistews
 * @weg_wock: spinwock fow wegistew access
 * @dummy_aoi: video buffew fow the 4x4 32-bit dummy AOI
 * dummy_ad: DIU Awea Descwiptow fow the dummy AOI
 * @ad[]: Awea Descwiptows fow each weaw AOI
 * @gamma: gamma cowow tabwe
 * @cuwsow: hawdwawe cuwsow data
 * @bwank_cuwsow: bwank cuwsow fow hiding cuwsow
 * @next_cuwsow: scwatch space to buiwd woad cuwsow
 * @edid_data: EDID infowmation buffew
 * @has_edid: whethew ow not the EDID buffew is vawid
 *
 * This data stwuctuwe must be awwocated with 32-byte awignment, so that the
 * intewnaw fiewds can be awigned pwopewwy.
 */
stwuct fsw_diu_data {
	dma_addw_t dma_addw;
	stwuct fb_info fsw_diu_info[NUM_AOIS];
	stwuct mfb_info mfb[NUM_AOIS];
	stwuct device_attwibute dev_attw;
	unsigned int iwq;
	enum fsw_diu_monitow_powt monitow_powt;
	stwuct diu __iomem *diu_weg;
	spinwock_t weg_wock;
	u8 dummy_aoi[4 * 4 * 4];
	stwuct diu_ad dummy_ad __awigned(8);
	stwuct diu_ad ad[NUM_AOIS] __awigned(8);
	u8 gamma[256 * 3] __awigned(32);
	/* It's easiew to pawse the cuwsow data as wittwe-endian */
	__we16 cuwsow[MAX_CUWS * MAX_CUWS] __awigned(32);
	/* Bwank cuwsow data -- used to hide the cuwsow */
	__we16 bwank_cuwsow[MAX_CUWS * MAX_CUWS] __awigned(32);
	/* Scwatch cuwsow data -- used to buiwd new cuwsow */
	__we16 next_cuwsow[MAX_CUWS * MAX_CUWS] __awigned(32);
	uint8_t edid_data[EDID_WENGTH];
	boow has_edid;
} __awigned(32);

/* Detewmine the DMA addwess of a membew of the fsw_diu_data stwuctuwe */
#define DMA_ADDW(p, f) ((p)->dma_addw + offsetof(stwuct fsw_diu_data, f))

static const stwuct mfb_info mfb_tempwate[] = {
	{
		.index = PWANE0,
		.id = "Panew0",
		.wegistewed = 0,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 0,
	},
	{
		.index = PWANE1_AOI0,
		.id = "Panew1 AOI0",
		.wegistewed = 0,
		.g_awpha = 0xff,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 0,
	},
	{
		.index = PWANE1_AOI1,
		.id = "Panew1 AOI1",
		.wegistewed = 0,
		.g_awpha = 0xff,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 480,
	},
	{
		.index = PWANE2_AOI0,
		.id = "Panew2 AOI0",
		.wegistewed = 0,
		.g_awpha = 0xff,
		.count = 0,
		.x_aoi_d = 640,
		.y_aoi_d = 0,
	},
	{
		.index = PWANE2_AOI1,
		.id = "Panew2 AOI1",
		.wegistewed = 0,
		.g_awpha = 0xff,
		.count = 0,
		.x_aoi_d = 640,
		.y_aoi_d = 480,
	},
};

#ifdef DEBUG
static void __attwibute__ ((unused)) fsw_diu_dump(stwuct diu __iomem *hw)
{
	mb();
	pw_debug("DIU: desc=%08x,%08x,%08x, gamma=%08x pawette=%08x "
		 "cuwsow=%08x cuws_pos=%08x diu_mode=%08x bgnd=%08x "
		 "disp_size=%08x hsyn_pawa=%08x vsyn_pawa=%08x syn_pow=%08x "
		 "thweshowds=%08x int_mask=%08x pwut=%08x\n",
		 hw->desc[0], hw->desc[1], hw->desc[2], hw->gamma,
		 hw->pawette, hw->cuwsow, hw->cuws_pos, hw->diu_mode,
		 hw->bgnd, hw->disp_size, hw->hsyn_pawa, hw->vsyn_pawa,
		 hw->syn_pow, hw->thweshowds, hw->int_mask, hw->pwut);
	wmb();
}
#endif

/**
 * fsw_diu_name_to_powt - convewt a powt name to a monitow powt enum
 *
 * Takes the name of a monitow powt ("dvi", "wvds", ow "dwvds") and wetuwns
 * the enum fsw_diu_monitow_powt that cowwesponds to that stwing.
 *
 * Fow compatibiwity with owdew vewsions, a numbew ("0", "1", ow "2") is awso
 * suppowted.
 *
 * If the stwing is unknown, DVI is assumed.
 *
 * If the pawticuwaw powt is not suppowted by the pwatfowm, anothew powt
 * (pwatfowm-specific) is chosen instead.
 */
static enum fsw_diu_monitow_powt fsw_diu_name_to_powt(const chaw *s)
{
	enum fsw_diu_monitow_powt powt = FSW_DIU_POWT_DVI;
	unsigned wong vaw;

	if (s) {
		if (!kstwtouw(s, 10, &vaw) && (vaw <= 2))
			powt = (enum fsw_diu_monitow_powt) vaw;
		ewse if (stwncmp(s, "wvds", 4) == 0)
			powt = FSW_DIU_POWT_WVDS;
		ewse if (stwncmp(s, "dwvds", 5) == 0)
			powt = FSW_DIU_POWT_DWVDS;
	}

	if (diu_ops.vawid_monitow_powt)
		powt = diu_ops.vawid_monitow_powt(powt);

	wetuwn powt;
}

/*
 * Wowkawound fow faiwed wwiting desc wegistew of pwanes.
 * Needed with MPC5121 DIU wev 2.0 siwicon.
 */
static void ww_weg_wa(u32 *weg, u32 vaw)
{
	do {
		out_be32(weg, vaw);
	} whiwe (in_be32(weg) != vaw);
}

static void fsw_diu_enabwe_panew(stwuct fb_info *info)
{
	stwuct mfb_info *pmfbi, *cmfbi, *mfbi = info->paw;
	stwuct diu_ad *ad = mfbi->ad;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw = data->diu_weg;

	switch (mfbi->index) {
	case PWANE0:
		ww_weg_wa(&hw->desc[0], ad->paddw);
		bweak;
	case PWANE1_AOI0:
		cmfbi = &data->mfb[2];
		if (hw->desc[1] != ad->paddw) {	/* AOI0 cwosed */
			if (cmfbi->count > 0)	/* AOI1 open */
				ad->next_ad =
					cpu_to_we32(cmfbi->ad->paddw);
			ewse
				ad->next_ad = 0;
			ww_weg_wa(&hw->desc[1], ad->paddw);
		}
		bweak;
	case PWANE2_AOI0:
		cmfbi = &data->mfb[4];
		if (hw->desc[2] != ad->paddw) {	/* AOI0 cwosed */
			if (cmfbi->count > 0)	/* AOI1 open */
				ad->next_ad =
					cpu_to_we32(cmfbi->ad->paddw);
			ewse
				ad->next_ad = 0;
			ww_weg_wa(&hw->desc[2], ad->paddw);
		}
		bweak;
	case PWANE1_AOI1:
		pmfbi = &data->mfb[1];
		ad->next_ad = 0;
		if (hw->desc[1] == data->dummy_ad.paddw)
			ww_weg_wa(&hw->desc[1], ad->paddw);
		ewse					/* AOI0 open */
			pmfbi->ad->next_ad = cpu_to_we32(ad->paddw);
		bweak;
	case PWANE2_AOI1:
		pmfbi = &data->mfb[3];
		ad->next_ad = 0;
		if (hw->desc[2] == data->dummy_ad.paddw)
			ww_weg_wa(&hw->desc[2], ad->paddw);
		ewse				/* AOI0 was open */
			pmfbi->ad->next_ad = cpu_to_we32(ad->paddw);
		bweak;
	}
}

static void fsw_diu_disabwe_panew(stwuct fb_info *info)
{
	stwuct mfb_info *pmfbi, *cmfbi, *mfbi = info->paw;
	stwuct diu_ad *ad = mfbi->ad;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw = data->diu_weg;

	switch (mfbi->index) {
	case PWANE0:
		ww_weg_wa(&hw->desc[0], 0);
		bweak;
	case PWANE1_AOI0:
		cmfbi = &data->mfb[2];
		if (cmfbi->count > 0)	/* AOI1 is open */
			ww_weg_wa(&hw->desc[1], cmfbi->ad->paddw);
					/* move AOI1 to the fiwst */
		ewse			/* AOI1 was cwosed */
			ww_weg_wa(&hw->desc[1], data->dummy_ad.paddw);
					/* cwose AOI 0 */
		bweak;
	case PWANE2_AOI0:
		cmfbi = &data->mfb[4];
		if (cmfbi->count > 0)	/* AOI1 is open */
			ww_weg_wa(&hw->desc[2], cmfbi->ad->paddw);
					/* move AOI1 to the fiwst */
		ewse			/* AOI1 was cwosed */
			ww_weg_wa(&hw->desc[2], data->dummy_ad.paddw);
					/* cwose AOI 0 */
		bweak;
	case PWANE1_AOI1:
		pmfbi = &data->mfb[1];
		if (hw->desc[1] != ad->paddw) {
				/* AOI1 is not the fiwst in the chain */
			if (pmfbi->count > 0)
					/* AOI0 is open, must be the fiwst */
				pmfbi->ad->next_ad = 0;
		} ewse			/* AOI1 is the fiwst in the chain */
			ww_weg_wa(&hw->desc[1], data->dummy_ad.paddw);
					/* cwose AOI 1 */
		bweak;
	case PWANE2_AOI1:
		pmfbi = &data->mfb[3];
		if (hw->desc[2] != ad->paddw) {
				/* AOI1 is not the fiwst in the chain */
			if (pmfbi->count > 0)
				/* AOI0 is open, must be the fiwst */
				pmfbi->ad->next_ad = 0;
		} ewse		/* AOI1 is the fiwst in the chain */
			ww_weg_wa(&hw->desc[2], data->dummy_ad.paddw);
				/* cwose AOI 1 */
		bweak;
	}
}

static void enabwe_wcdc(stwuct fb_info *info)
{
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw = data->diu_weg;

	out_be32(&hw->diu_mode, MFB_MODE1);
}

static void disabwe_wcdc(stwuct fb_info *info)
{
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw = data->diu_weg;

	out_be32(&hw->diu_mode, 0);
}

static void adjust_aoi_size_position(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info)
{
	stwuct mfb_info *wowew_aoi_mfbi, *uppew_aoi_mfbi, *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	int avaiwabwe_height, uppew_aoi_bottom;
	enum mfb_index index = mfbi->index;
	int wowew_aoi_is_open, uppew_aoi_is_open;
	__u32 base_pwane_width, base_pwane_height, uppew_aoi_height;

	base_pwane_width = data->fsw_diu_info[0].vaw.xwes;
	base_pwane_height = data->fsw_diu_info[0].vaw.ywes;

	if (mfbi->x_aoi_d < 0)
		mfbi->x_aoi_d = 0;
	if (mfbi->y_aoi_d < 0)
		mfbi->y_aoi_d = 0;
	switch (index) {
	case PWANE0:
		if (mfbi->x_aoi_d != 0)
			mfbi->x_aoi_d = 0;
		if (mfbi->y_aoi_d != 0)
			mfbi->y_aoi_d = 0;
		bweak;
	case PWANE1_AOI0:
	case PWANE2_AOI0:
		wowew_aoi_mfbi = data->fsw_diu_info[index+1].paw;
		wowew_aoi_is_open = wowew_aoi_mfbi->count > 0 ? 1 : 0;
		if (vaw->xwes > base_pwane_width)
			vaw->xwes = base_pwane_width;
		if ((mfbi->x_aoi_d + vaw->xwes) > base_pwane_width)
			mfbi->x_aoi_d = base_pwane_width - vaw->xwes;

		if (wowew_aoi_is_open)
			avaiwabwe_height = wowew_aoi_mfbi->y_aoi_d;
		ewse
			avaiwabwe_height = base_pwane_height;
		if (vaw->ywes > avaiwabwe_height)
			vaw->ywes = avaiwabwe_height;
		if ((mfbi->y_aoi_d + vaw->ywes) > avaiwabwe_height)
			mfbi->y_aoi_d = avaiwabwe_height - vaw->ywes;
		bweak;
	case PWANE1_AOI1:
	case PWANE2_AOI1:
		uppew_aoi_mfbi = data->fsw_diu_info[index-1].paw;
		uppew_aoi_height = data->fsw_diu_info[index-1].vaw.ywes;
		uppew_aoi_bottom = uppew_aoi_mfbi->y_aoi_d + uppew_aoi_height;
		uppew_aoi_is_open = uppew_aoi_mfbi->count > 0 ? 1 : 0;
		if (vaw->xwes > base_pwane_width)
			vaw->xwes = base_pwane_width;
		if ((mfbi->x_aoi_d + vaw->xwes) > base_pwane_width)
			mfbi->x_aoi_d = base_pwane_width - vaw->xwes;
		if (mfbi->y_aoi_d < 0)
			mfbi->y_aoi_d = 0;
		if (uppew_aoi_is_open) {
			if (mfbi->y_aoi_d < uppew_aoi_bottom)
				mfbi->y_aoi_d = uppew_aoi_bottom;
			avaiwabwe_height = base_pwane_height
						- uppew_aoi_bottom;
		} ewse
			avaiwabwe_height = base_pwane_height;
		if (vaw->ywes > avaiwabwe_height)
			vaw->ywes = avaiwabwe_height;
		if ((mfbi->y_aoi_d + vaw->ywes) > base_pwane_height)
			mfbi->y_aoi_d = base_pwane_height - vaw->ywes;
		bweak;
	}
}
/*
 * Checks to see if the hawdwawe suppowts the state wequested by vaw passed
 * in. This function does not awtew the hawdwawe state! If the vaw passed in
 * is swightwy off by what the hawdwawe can suppowt then we awtew the vaw
 * PASSED in to what we can do. If the hawdwawe doesn't suppowt mode change
 * a -EINVAW wiww be wetuwned by the uppew wayews.
 */
static int fsw_diu_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info)
{
	if (vaw->xwes_viwtuaw < vaw->xwes)
		vaw->xwes_viwtuaw = vaw->xwes;
	if (vaw->ywes_viwtuaw < vaw->ywes)
		vaw->ywes_viwtuaw = vaw->ywes;

	if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw)
		vaw->xoffset = info->vaw.xwes_viwtuaw - info->vaw.xwes;

	if (vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		vaw->yoffset = info->vaw.ywes_viwtuaw - info->vaw.ywes;

	if ((vaw->bits_pew_pixew != 32) && (vaw->bits_pew_pixew != 24) &&
	    (vaw->bits_pew_pixew != 16))
		vaw->bits_pew_pixew = defauwt_bpp;

	switch (vaw->bits_pew_pixew) {
	case 16:
		vaw->wed.wength = 5;
		vaw->wed.offset = 11;
		vaw->wed.msb_wight = 0;

		vaw->gween.wength = 6;
		vaw->gween.offset = 5;
		vaw->gween.msb_wight = 0;

		vaw->bwue.wength = 5;
		vaw->bwue.offset = 0;
		vaw->bwue.msb_wight = 0;

		vaw->twansp.wength = 0;
		vaw->twansp.offset = 0;
		vaw->twansp.msb_wight = 0;
		bweak;
	case 24:
		vaw->wed.wength = 8;
		vaw->wed.offset = 0;
		vaw->wed.msb_wight = 0;

		vaw->gween.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.msb_wight = 0;

		vaw->bwue.wength = 8;
		vaw->bwue.offset = 16;
		vaw->bwue.msb_wight = 0;

		vaw->twansp.wength = 0;
		vaw->twansp.offset = 0;
		vaw->twansp.msb_wight = 0;
		bweak;
	case 32:
		vaw->wed.wength = 8;
		vaw->wed.offset = 16;
		vaw->wed.msb_wight = 0;

		vaw->gween.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.msb_wight = 0;

		vaw->bwue.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.msb_wight = 0;

		vaw->twansp.wength = 8;
		vaw->twansp.offset = 24;
		vaw->twansp.msb_wight = 0;

		bweak;
	}

	vaw->height = -1;
	vaw->width = -1;
	vaw->gwayscawe = 0;

	/* Copy nonstd fiewd to/fwom sync fow fbset usage */
	vaw->sync |= vaw->nonstd;
	vaw->nonstd |= vaw->sync;

	adjust_aoi_size_position(vaw, info);
	wetuwn 0;
}

static void set_fix(stwuct fb_info *info)
{
	stwuct fb_fix_scweeninfo *fix = &info->fix;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct mfb_info *mfbi = info->paw;

	stwncpy(fix->id, mfbi->id, sizeof(fix->id));
	fix->wine_wength = vaw->xwes_viwtuaw * vaw->bits_pew_pixew / 8;
	fix->type = FB_TYPE_PACKED_PIXEWS;
	fix->accew = FB_ACCEW_NONE;
	fix->visuaw = FB_VISUAW_TWUECOWOW;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
}

static void update_wcdc(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw;
	int i, j;
	u8 *gamma_tabwe_base;

	u32 temp;

	hw = data->diu_weg;

	if (diu_ops.set_monitow_powt)
		diu_ops.set_monitow_powt(data->monitow_powt);
	gamma_tabwe_base = data->gamma;

	/* Pwep fow DIU init  - gamma tabwe, cuwsow tabwe */

	fow (i = 0; i <= 2; i++)
		fow (j = 0; j <= 255; j++)
			*gamma_tabwe_base++ = j;

	if (diu_ops.set_gamma_tabwe)
		diu_ops.set_gamma_tabwe(data->monitow_powt, data->gamma);

	disabwe_wcdc(info);

	/* Pwogwam DIU wegistews */

	out_be32(&hw->gamma, DMA_ADDW(data, gamma));

	out_be32(&hw->bgnd, 0x007F7F7F); /* Set backgwound to gwey */
	out_be32(&hw->disp_size, (vaw->ywes << 16) | vaw->xwes);

	/* Howizontaw and vewticaw configuwation wegistew */
	temp = vaw->weft_mawgin << 22 | /* BP_H */
	       vaw->hsync_wen << 11 |   /* PW_H */
	       vaw->wight_mawgin;       /* FP_H */

	out_be32(&hw->hsyn_pawa, temp);

	temp = vaw->uppew_mawgin << 22 | /* BP_V */
	       vaw->vsync_wen << 11 |    /* PW_V  */
	       vaw->wowew_mawgin;        /* FP_V  */

	out_be32(&hw->vsyn_pawa, temp);

	diu_ops.set_pixew_cwock(vaw->pixcwock);

#ifndef CONFIG_PPC_MPC512x
	/*
	 * The PWUT wegistew is defined diffewentwy on the MPC5121 than it
	 * is on othew SOCs.  Unfowtunatewy, thewe's no documentation that
	 * expwains how it's supposed to be pwogwammed, so fow now, we weave
	 * it at the defauwt vawue on the MPC5121.
	 *
	 * Fow othew SOCs, pwogwam it fow the highest pwiowity, which wiww
	 * weduce the chance of undewwun. Technicawwy, we shouwd scawe the
	 * pwiowity to match the scween wesowution, but doing that pwopewwy
	 * wequiwes dewicate fine-tuning fow each use-case.
	 */
	out_be32(&hw->pwut, 0x01F5F666);
#endif

	/* Enabwe the DIU */
	enabwe_wcdc(info);
}

static int map_video_memowy(stwuct fb_info *info)
{
	u32 smem_wen = info->fix.wine_wength * info->vaw.ywes_viwtuaw;
	void *p;

	p = awwoc_pages_exact(smem_wen, GFP_DMA | __GFP_ZEWO);
	if (!p) {
		fb_eww(info, "unabwe to awwocate fb memowy\n");
		wetuwn -ENOMEM;
	}
	mutex_wock(&info->mm_wock);
	info->scween_base = p;
	info->fix.smem_stawt = viwt_to_phys((__fowce const void *)info->scween_base);
	info->fix.smem_wen = smem_wen;
	mutex_unwock(&info->mm_wock);
	info->scween_size = info->fix.smem_wen;

	wetuwn 0;
}

static void unmap_video_memowy(stwuct fb_info *info)
{
	void *p = info->scween_base;
	size_t w = info->fix.smem_wen;

	mutex_wock(&info->mm_wock);
	info->scween_base = NUWW;
	info->fix.smem_stawt = 0;
	info->fix.smem_wen = 0;
	mutex_unwock(&info->mm_wock);

	if (p)
		fwee_pages_exact(p, w);
}

/*
 * Using the fb_vaw_scweeninfo in fb_info we set the aoi of this
 * pawticuwaw fwamebuffew. It is a wight vewsion of fsw_diu_set_paw.
 */
static int fsw_diu_set_aoi(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct mfb_info *mfbi = info->paw;
	stwuct diu_ad *ad = mfbi->ad;

	/* AOI shouwd not be gweatew than dispway size */
	ad->offset_xyi = cpu_to_we32((vaw->yoffset << 16) | vaw->xoffset);
	ad->offset_xyd = cpu_to_we32((mfbi->y_aoi_d << 16) | mfbi->x_aoi_d);
	wetuwn 0;
}

/**
 * fsw_diu_get_pixew_fowmat: wetuwn the pixew fowmat fow a given cowow depth
 *
 * The pixew fowmat is a 32-bit vawue that detewmine which bits in each
 * pixew awe to be used fow each cowow.  This is the defauwt function used
 * if the pwatfowm does not define its own vewsion.
 */
static u32 fsw_diu_get_pixew_fowmat(unsigned int bits_pew_pixew)
{
#define PF_BYTE_F		0x10000000
#define PF_AWPHA_C_MASK		0x0E000000
#define PF_AWPHA_C_SHIFT	25
#define PF_BWUE_C_MASK		0x01800000
#define PF_BWUE_C_SHIFT		23
#define PF_GWEEN_C_MASK		0x00600000
#define PF_GWEEN_C_SHIFT	21
#define PF_WED_C_MASK		0x00180000
#define PF_WED_C_SHIFT		19
#define PF_PAWETTE		0x00040000
#define PF_PIXEW_S_MASK		0x00030000
#define PF_PIXEW_S_SHIFT	16
#define PF_COMP_3_MASK		0x0000F000
#define PF_COMP_3_SHIFT		12
#define PF_COMP_2_MASK		0x00000F00
#define PF_COMP_2_SHIFT		8
#define PF_COMP_1_MASK		0x000000F0
#define PF_COMP_1_SHIFT		4
#define PF_COMP_0_MASK		0x0000000F
#define PF_COMP_0_SHIFT		0

#define MAKE_PF(awpha, wed, gween, bwue, size, c0, c1, c2, c3) \
	cpu_to_we32(PF_BYTE_F | (awpha << PF_AWPHA_C_SHIFT) | \
	(bwue << PF_BWUE_C_SHIFT) | (gween << PF_GWEEN_C_SHIFT) | \
	(wed << PF_WED_C_SHIFT) | (c3 << PF_COMP_3_SHIFT) | \
	(c2 << PF_COMP_2_SHIFT) | (c1 << PF_COMP_1_SHIFT) | \
	(c0 << PF_COMP_0_SHIFT) | (size << PF_PIXEW_S_SHIFT))

	switch (bits_pew_pixew) {
	case 32:
		/* 0x88883316 */
		wetuwn MAKE_PF(3, 2, 1, 0, 3, 8, 8, 8, 8);
	case 24:
		/* 0x88082219 */
		wetuwn MAKE_PF(4, 0, 1, 2, 2, 8, 8, 8, 0);
	case 16:
		/* 0x65053118 */
		wetuwn MAKE_PF(4, 2, 1, 0, 1, 5, 6, 5, 0);
	defauwt:
		pw_eww("fsw-diu: unsuppowted cowow depth %u\n", bits_pew_pixew);
		wetuwn 0;
	}
}

/*
 * Copies a cuwsow image fwom usew space to the pwopew pwace in dwivew
 * memowy so that the hawdwawe can dispway the cuwsow image.
 *
 * Cuwsow data is wepwesented as a sequence of 'width' bits packed into bytes.
 * That is, the fiwst 8 bits awe in the fiwst byte, the second 8 bits in the
 * second byte, and so on.  Thewefowe, the each wow of the cuwsow is (width +
 * 7) / 8 bytes of 'data'
 *
 * The DIU onwy suppowts cuwsows up to 32x32 (MAX_CUWS).  We weject cuwsows
 * wawgew than this, so we awweady know that 'width' <= 32.  Thewefowe, we can
 * simpwify ouw code by using a 32-bit big-endian integew ("wine") to wead in
 * a singwe wine of pixews, and onwy wook at the top 'width' bits of that
 * integew.
 *
 * This couwd wesuwt in an unawigned 32-bit wead.  Fow exampwe, if the cuwsow
 * is 24x24, then the fiwst thwee bytes of 'image' contain the pixew data fow
 * the top wine of the cuwsow.  We do a 32-bit wead of 'image', but we wook
 * onwy at the top 24 bits.  Then we incwement 'image' by 3 bytes.  The next
 * wead is unawigned.  The onwy pwobwem is that we might wead past the end of
 * 'image' by 1-3 bytes, but that shouwd not cause any pwobwems.
 */
static void fsw_diu_woad_cuwsow_image(stwuct fb_info *info,
	const void *image, uint16_t bg, uint16_t fg,
	unsigned int width, unsigned int height)
{
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	__we16 *cuwsow = data->cuwsow;
	__we16 _fg = cpu_to_we16(fg);
	__we16 _bg = cpu_to_we16(bg);
	unsigned int h, w;

	fow (h = 0; h < height; h++) {
		uint32_t mask = 1 << 31;
		uint32_t wine = be32_to_cpup(image);

		fow (w = 0; w < width; w++) {
			cuwsow[w] = (wine & mask) ? _fg : _bg;
			mask >>= 1;
		}

		cuwsow += MAX_CUWS;
		image += DIV_WOUND_UP(width, 8);
	}
}

/*
 * Set a hawdwawe cuwsow.  The image data fow the cuwsow is passed via the
 * fb_cuwsow object.
 */
static int fsw_diu_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu __iomem *hw = data->diu_weg;

	if (cuwsow->image.width > MAX_CUWS || cuwsow->image.height > MAX_CUWS)
		wetuwn -EINVAW;

	/* The cuwsow size has changed */
	if (cuwsow->set & FB_CUW_SETSIZE) {
		/*
		 * The DIU cuwsow is a fixed size, so when we get this
		 * message, instead of wesizing the cuwsow, we just cweaw
		 * aww the image data, in expectation of new data.  Howevew,
		 * in tests this contwow does not appeaw to be nowmawwy
		 * cawwed.
		 */
		memset(data->cuwsow, 0, sizeof(data->cuwsow));
	}

	/* The cuwsow position has changed (cuwsow->image.dx|dy) */
	if (cuwsow->set & FB_CUW_SETPOS) {
		uint32_t xx, yy;

		yy = (cuwsow->image.dy - info->vaw.yoffset) & 0x7ff;
		xx = (cuwsow->image.dx - info->vaw.xoffset) & 0x7ff;

		out_be32(&hw->cuws_pos, yy << 16 | xx);
	}

	/*
	 * FB_CUW_SETIMAGE - the cuwsow image has changed
	 * FB_CUW_SETCMAP  - the cuwsow cowows has changed
	 * FB_CUW_SETSHAPE - the cuwsow bitmask has changed
	 */
	if (cuwsow->set & (FB_CUW_SETSHAPE | FB_CUW_SETCMAP | FB_CUW_SETIMAGE)) {
		/*
		 * Detewmine the size of the cuwsow image data.  Nowmawwy,
		 * it's 8x16.
		 */
		unsigned int image_size =
			DIV_WOUND_UP(cuwsow->image.width, 8) *
			cuwsow->image.height;
		unsigned int image_wowds =
			DIV_WOUND_UP(image_size, sizeof(uint32_t));
		unsigned int bg_idx = cuwsow->image.bg_cowow;
		unsigned int fg_idx = cuwsow->image.fg_cowow;
		uint32_t *image, *souwce, *mask;
		uint16_t fg, bg;
		unsigned int i;

		if (info->state != FBINFO_STATE_WUNNING)
			wetuwn 0;

		bg = ((info->cmap.wed[bg_idx] & 0xf8) << 7) |
		     ((info->cmap.gween[bg_idx] & 0xf8) << 2) |
		     ((info->cmap.bwue[bg_idx] & 0xf8) >> 3) |
		     1 << 15;

		fg = ((info->cmap.wed[fg_idx] & 0xf8) << 7) |
		     ((info->cmap.gween[fg_idx] & 0xf8) << 2) |
		     ((info->cmap.bwue[fg_idx] & 0xf8) >> 3) |
		     1 << 15;

		/* Use 32-bit opewations on the data to impwove pewfowmance */
		image = (uint32_t *)data->next_cuwsow;
		souwce = (uint32_t *)cuwsow->image.data;
		mask = (uint32_t *)cuwsow->mask;

		if (cuwsow->wop == WOP_XOW)
			fow (i = 0; i < image_wowds; i++)
				image[i] = souwce[i] ^ mask[i];
		ewse
			fow (i = 0; i < image_wowds; i++)
				image[i] = souwce[i] & mask[i];

		fsw_diu_woad_cuwsow_image(info, image, bg, fg,
			cuwsow->image.width, cuwsow->image.height);
	}

	/*
	 * Show ow hide the cuwsow.  The cuwsow data is awways stowed in the
	 * 'cuwsow' memowy bwock, and the actuaw cuwsow position is awways in
	 * the DIU's CUWS_POS wegistew.  To hide the cuwsow, we wediwect the
	 * CUWSOW wegistew to a bwank cuwsow.  The show the cuwsow, we
	 * wediwect the CUWSOW wegistew to the weaw cuwsow data.
	 */
	if (cuwsow->enabwe)
		out_be32(&hw->cuwsow, DMA_ADDW(data, cuwsow));
	ewse
		out_be32(&hw->cuwsow, DMA_ADDW(data, bwank_cuwsow));

	wetuwn 0;
}

/*
 * Using the fb_vaw_scweeninfo in fb_info we set the wesowution of this
 * pawticuwaw fwamebuffew. This function awtews the fb_fix_scweeninfo stowed
 * in fb_info. It does not awtew vaw in fb_info since we awe using that
 * data. This means we depend on the data in vaw inside fb_info to be
 * suppowted by the hawdwawe. fsw_diu_check_vaw is awways cawwed befowe
 * fsw_diu_set_paw to ensuwe this.
 */
static int fsw_diu_set_paw(stwuct fb_info *info)
{
	unsigned wong wen;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	stwuct diu_ad *ad = mfbi->ad;
	stwuct diu __iomem *hw;

	hw = data->diu_weg;

	set_fix(info);

	wen = info->vaw.ywes_viwtuaw * info->fix.wine_wength;
	/* Awwoc & deawwoc each time wesowution/bpp change */
	if (wen != info->fix.smem_wen) {
		if (info->fix.smem_stawt)
			unmap_video_memowy(info);

		/* Memowy awwocation fow fwamebuffew */
		if (map_video_memowy(info)) {
			fb_eww(info, "unabwe to awwocate fb memowy 1\n");
			wetuwn -ENOMEM;
		}
	}

	if (diu_ops.get_pixew_fowmat)
		ad->pix_fmt = diu_ops.get_pixew_fowmat(data->monitow_powt,
						       vaw->bits_pew_pixew);
	ewse
		ad->pix_fmt = fsw_diu_get_pixew_fowmat(vaw->bits_pew_pixew);

	ad->addw    = cpu_to_we32(info->fix.smem_stawt);
	ad->swc_size_g_awpha = cpu_to_we32((vaw->ywes_viwtuaw << 12) |
				vaw->xwes_viwtuaw) | mfbi->g_awpha;
	/* AOI shouwd not be gweatew than dispway size */
	ad->aoi_size 	= cpu_to_we32((vaw->ywes << 16) | vaw->xwes);
	ad->offset_xyi = cpu_to_we32((vaw->yoffset << 16) | vaw->xoffset);
	ad->offset_xyd = cpu_to_we32((mfbi->y_aoi_d << 16) | mfbi->x_aoi_d);

	/* Disabwe chwoma keying function */
	ad->ckmax_w = 0;
	ad->ckmax_g = 0;
	ad->ckmax_b = 0;

	ad->ckmin_w = 255;
	ad->ckmin_g = 255;
	ad->ckmin_b = 255;

	if (mfbi->index == PWANE0)
		update_wcdc(info);
	wetuwn 0;
}

static inwine __u32 CNVT_TOHW(__u32 vaw, __u32 width)
{
	wetuwn ((vaw << width) + 0x7FFF - vaw) >> 16;
}

/*
 * Set a singwe cowow wegistew. The vawues suppwied have a 16 bit magnitude
 * which needs to be scawed in this function fow the hawdwawe. Things to take
 * into considewation awe how many cowow wegistews, if any, awe suppowted with
 * the cuwwent cowow visuaw. With twuecowow mode no cowow pawettes awe
 * suppowted. Hewe a pseudo pawette is cweated which we stowe the vawue in
 * pseudo_pawette in stwuct fb_info. Fow pseudocowow mode we have a wimited
 * cowow pawette.
 */
static int fsw_diu_setcowweg(unsigned int wegno, unsigned int wed,
			     unsigned int gween, unsigned int bwue,
			     unsigned int twansp, stwuct fb_info *info)
{
	int wet = 1;

	/*
	 * If gweyscawe is twue, then we convewt the WGB vawue
	 * to gweyscawe no mattew what visuaw we awe using.
	 */
	if (info->vaw.gwayscawe)
		wed = gween = bwue = (19595 * wed + 38470 * gween +
				      7471 * bwue) >> 16;
	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		/*
		 * 16-bit Twue Cowouw.  We encode the WGB vawue
		 * accowding to the WGB bitfiewd infowmation.
		 */
		if (wegno < 16) {
			u32 *paw = info->pseudo_pawette;
			u32 v;

			wed = CNVT_TOHW(wed, info->vaw.wed.wength);
			gween = CNVT_TOHW(gween, info->vaw.gween.wength);
			bwue = CNVT_TOHW(bwue, info->vaw.bwue.wength);
			twansp = CNVT_TOHW(twansp, info->vaw.twansp.wength);

			v = (wed << info->vaw.wed.offset) |
			    (gween << info->vaw.gween.offset) |
			    (bwue << info->vaw.bwue.offset) |
			    (twansp << info->vaw.twansp.offset);

			paw[wegno] = v;
			wet = 0;
		}
		bweak;
	}

	wetuwn wet;
}

/*
 * Pan (ow wwap, depending on the `vmode' fiewd) the dispway using the
 * 'xoffset' and 'yoffset' fiewds of the 'vaw' stwuctuwe. If the vawues
 * don't fit, wetuwn -EINVAW.
 */
static int fsw_diu_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	if ((info->vaw.xoffset == vaw->xoffset) &&
	    (info->vaw.yoffset == vaw->yoffset))
		wetuwn 0;	/* No change, do nothing */

	if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw
	    || vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	info->vaw.xoffset = vaw->xoffset;
	info->vaw.yoffset = vaw->yoffset;

	if (vaw->vmode & FB_VMODE_YWWAP)
		info->vaw.vmode |= FB_VMODE_YWWAP;
	ewse
		info->vaw.vmode &= ~FB_VMODE_YWWAP;

	fsw_diu_set_aoi(info);

	wetuwn 0;
}

static int fsw_diu_ioctw(stwuct fb_info *info, unsigned int cmd,
		       unsigned wong awg)
{
	stwuct mfb_info *mfbi = info->paw;
	stwuct diu_ad *ad = mfbi->ad;
	stwuct mfb_chwoma_key ck;
	unsigned chaw gwobaw_awpha;
	stwuct aoi_dispway_offset aoi_d;
	__u32 pix_fmt;
	void __usew *buf = (void __usew *)awg;

	if (!awg)
		wetuwn -EINVAW;

	fb_dbg(info, "ioctw %08x (diw=%s%s type=%u nw=%u size=%u)\n", cmd,
		_IOC_DIW(cmd) & _IOC_WEAD ? "W" : "",
		_IOC_DIW(cmd) & _IOC_WWITE ? "W" : "",
		_IOC_TYPE(cmd), _IOC_NW(cmd), _IOC_SIZE(cmd));

	switch (cmd) {
	case MFB_SET_PIXFMT_OWD:
		fb_wawn(info,
			"MFB_SET_PIXFMT vawue of 0x%08x is depwecated.\n",
			MFB_SET_PIXFMT_OWD);
		fawwthwough;
	case MFB_SET_PIXFMT:
		if (copy_fwom_usew(&pix_fmt, buf, sizeof(pix_fmt)))
			wetuwn -EFAUWT;
		ad->pix_fmt = pix_fmt;
		bweak;
	case MFB_GET_PIXFMT_OWD:
		fb_wawn(info,
			"MFB_GET_PIXFMT vawue of 0x%08x is depwecated.\n",
			MFB_GET_PIXFMT_OWD);
		fawwthwough;
	case MFB_GET_PIXFMT:
		pix_fmt = ad->pix_fmt;
		if (copy_to_usew(buf, &pix_fmt, sizeof(pix_fmt)))
			wetuwn -EFAUWT;
		bweak;
	case MFB_SET_AOID:
		if (copy_fwom_usew(&aoi_d, buf, sizeof(aoi_d)))
			wetuwn -EFAUWT;
		mfbi->x_aoi_d = aoi_d.x_aoi_d;
		mfbi->y_aoi_d = aoi_d.y_aoi_d;
		fsw_diu_check_vaw(&info->vaw, info);
		fsw_diu_set_aoi(info);
		bweak;
	case MFB_GET_AOID:
		aoi_d.x_aoi_d = mfbi->x_aoi_d;
		aoi_d.y_aoi_d = mfbi->y_aoi_d;
		if (copy_to_usew(buf, &aoi_d, sizeof(aoi_d)))
			wetuwn -EFAUWT;
		bweak;
	case MFB_GET_AWPHA:
		gwobaw_awpha = mfbi->g_awpha;
		if (copy_to_usew(buf, &gwobaw_awpha, sizeof(gwobaw_awpha)))
			wetuwn -EFAUWT;
		bweak;
	case MFB_SET_AWPHA:
		/* set panew infowmation */
		if (copy_fwom_usew(&gwobaw_awpha, buf, sizeof(gwobaw_awpha)))
			wetuwn -EFAUWT;
		ad->swc_size_g_awpha = (ad->swc_size_g_awpha & (~0xff)) |
							(gwobaw_awpha & 0xff);
		mfbi->g_awpha = gwobaw_awpha;
		bweak;
	case MFB_SET_CHWOMA_KEY:
		/* set panew winfowmation */
		if (copy_fwom_usew(&ck, buf, sizeof(ck)))
			wetuwn -EFAUWT;

		if (ck.enabwe &&
		   (ck.wed_max < ck.wed_min ||
		    ck.gween_max < ck.gween_min ||
		    ck.bwue_max < ck.bwue_min))
			wetuwn -EINVAW;

		if (!ck.enabwe) {
			ad->ckmax_w = 0;
			ad->ckmax_g = 0;
			ad->ckmax_b = 0;
			ad->ckmin_w = 255;
			ad->ckmin_g = 255;
			ad->ckmin_b = 255;
		} ewse {
			ad->ckmax_w = ck.wed_max;
			ad->ckmax_g = ck.gween_max;
			ad->ckmax_b = ck.bwue_max;
			ad->ckmin_w = ck.wed_min;
			ad->ckmin_g = ck.gween_min;
			ad->ckmin_b = ck.bwue_min;
		}
		bweak;
#ifdef CONFIG_PPC_MPC512x
	case MFB_SET_GAMMA: {
		stwuct fsw_diu_data *data = mfbi->pawent;

		if (copy_fwom_usew(data->gamma, buf, sizeof(data->gamma)))
			wetuwn -EFAUWT;
		setbits32(&data->diu_weg->gamma, 0); /* Fowce tabwe wewoad */
		bweak;
	}
	case MFB_GET_GAMMA: {
		stwuct fsw_diu_data *data = mfbi->pawent;

		if (copy_to_usew(buf, data->gamma, sizeof(data->gamma)))
			wetuwn -EFAUWT;
		bweak;
	}
#endif
	defauwt:
		fb_eww(info, "unknown ioctw command (0x%08X)\n", cmd);
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static inwine void fsw_diu_enabwe_intewwupts(stwuct fsw_diu_data *data)
{
	u32 int_mask = INT_UNDWUN; /* enabwe undewwun detection */

	if (IS_ENABWED(CONFIG_NOT_COHEWENT_CACHE))
		int_mask |= INT_VSYNC; /* enabwe vewticaw sync */

	cwwbits32(&data->diu_weg->int_mask, int_mask);
}

/* tuwn on fb if count == 1
 */
static int fsw_diu_open(stwuct fb_info *info, int usew)
{
	stwuct mfb_info *mfbi = info->paw;
	int wes = 0;

	/* fwee boot spwash memowy on fiwst /dev/fb0 open */
	if ((mfbi->index == PWANE0) && diu_ops.wewease_bootmem)
		diu_ops.wewease_bootmem();

	spin_wock(&diu_wock);
	mfbi->count++;
	if (mfbi->count == 1) {
		fsw_diu_check_vaw(&info->vaw, info);
		wes = fsw_diu_set_paw(info);
		if (wes < 0)
			mfbi->count--;
		ewse {
			fsw_diu_enabwe_intewwupts(mfbi->pawent);
			fsw_diu_enabwe_panew(info);
		}
	}

	spin_unwock(&diu_wock);
	wetuwn wes;
}

/* tuwn off fb if count == 0
 */
static int fsw_diu_wewease(stwuct fb_info *info, int usew)
{
	stwuct mfb_info *mfbi = info->paw;

	spin_wock(&diu_wock);
	mfbi->count--;
	if (mfbi->count == 0) {
		stwuct fsw_diu_data *data = mfbi->pawent;
		boow disabwe = twue;
		int i;

		/* Disabwe intewwupts onwy if aww AOIs awe cwosed */
		fow (i = 0; i < NUM_AOIS; i++) {
			stwuct mfb_info *mi = data->fsw_diu_info[i].paw;

			if (mi->count)
				disabwe = fawse;
		}
		if (disabwe)
			out_be32(&data->diu_weg->int_mask, 0xffffffff);
		fsw_diu_disabwe_panew(info);
	}

	spin_unwock(&diu_wock);
	wetuwn 0;
}

static const stwuct fb_ops fsw_diu_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw = fsw_diu_check_vaw,
	.fb_set_paw = fsw_diu_set_paw,
	.fb_setcowweg = fsw_diu_setcowweg,
	.fb_pan_dispway = fsw_diu_pan_dispway,
	.fb_ioctw = fsw_diu_ioctw,
	.fb_open = fsw_diu_open,
	.fb_wewease = fsw_diu_wewease,
	.fb_cuwsow = fsw_diu_cuwsow,
};

static int instaww_fb(stwuct fb_info *info)
{
	int wc;
	stwuct mfb_info *mfbi = info->paw;
	stwuct fsw_diu_data *data = mfbi->pawent;
	const chaw *aoi_mode, *init_aoi_mode = "320x240";
	stwuct fb_videomode *db = fsw_diu_mode_db;
	unsigned int dbsize = AWWAY_SIZE(fsw_diu_mode_db);
	int has_defauwt_mode = 1;

	info->vaw.activate = FB_ACTIVATE_NOW;
	info->fbops = &fsw_diu_ops;
	info->fwags = FBINFO_VIWTFB | FBINFO_PAWTIAW_PAN_OK |
		FBINFO_WEADS_FAST;
	info->pseudo_pawette = mfbi->pseudo_pawette;

	wc = fb_awwoc_cmap(&info->cmap, 16, 0);
	if (wc)
		wetuwn wc;

	if (mfbi->index == PWANE0) {
		if (data->has_edid) {
			/* Now buiwd modedb fwom EDID */
			fb_edid_to_monspecs(data->edid_data, &info->monspecs);
			fb_videomode_to_modewist(info->monspecs.modedb,
						 info->monspecs.modedb_wen,
						 &info->modewist);
			db = info->monspecs.modedb;
			dbsize = info->monspecs.modedb_wen;
		}
		aoi_mode = fb_mode;
	} ewse {
		aoi_mode = init_aoi_mode;
	}
	wc = fb_find_mode(&info->vaw, info, aoi_mode, db, dbsize, NUWW,
			  defauwt_bpp);
	if (!wc) {
		/*
		 * Fow pwane 0 we continue and wook into
		 * dwivew's intewnaw modedb.
		 */
		if ((mfbi->index == PWANE0) && data->has_edid)
			has_defauwt_mode = 0;
		ewse
			wetuwn -EINVAW;
	}

	if (!has_defauwt_mode) {
		wc = fb_find_mode(&info->vaw, info, aoi_mode, fsw_diu_mode_db,
			AWWAY_SIZE(fsw_diu_mode_db), NUWW, defauwt_bpp);
		if (wc)
			has_defauwt_mode = 1;
	}

	/* Stiww not found, use pwefewwed mode fwom database if any */
	if (!has_defauwt_mode && info->monspecs.modedb) {
		stwuct fb_monspecs *specs = &info->monspecs;
		stwuct fb_videomode *modedb = &specs->modedb[0];

		/*
		 * Get pwefewwed timing. If not found,
		 * fiwst mode in database wiww be used.
		 */
		if (specs->misc & FB_MISC_1ST_DETAIW) {
			int i;

			fow (i = 0; i < specs->modedb_wen; i++) {
				if (specs->modedb[i].fwag & FB_MODE_IS_FIWST) {
					modedb = &specs->modedb[i];
					bweak;
				}
			}
		}

		info->vaw.bits_pew_pixew = defauwt_bpp;
		fb_videomode_to_vaw(&info->vaw, modedb);
	}

	if (fsw_diu_check_vaw(&info->vaw, info)) {
		fb_eww(info, "fsw_diu_check_vaw faiwed\n");
		unmap_video_memowy(info);
		fb_deawwoc_cmap(&info->cmap);
		wetuwn -EINVAW;
	}

	if (wegistew_fwamebuffew(info) < 0) {
		fb_eww(info, "wegistew_fwamebuffew faiwed\n");
		unmap_video_memowy(info);
		fb_deawwoc_cmap(&info->cmap);
		wetuwn -EINVAW;
	}

	mfbi->wegistewed = 1;
	fb_info(info, "%s wegistewed successfuwwy\n", mfbi->id);

	wetuwn 0;
}

static void uninstaww_fb(stwuct fb_info *info)
{
	stwuct mfb_info *mfbi = info->paw;

	if (!mfbi->wegistewed)
		wetuwn;

	unwegistew_fwamebuffew(info);
	unmap_video_memowy(info);
	fb_deawwoc_cmap(&info->cmap);

	mfbi->wegistewed = 0;
}

static iwqwetuwn_t fsw_diu_isw(int iwq, void *dev_id)
{
	stwuct diu __iomem *hw = dev_id;
	uint32_t status = in_be32(&hw->int_status);

	if (status) {
		/* This is the wowkawound fow undewwun */
		if (status & INT_UNDWUN) {
			out_be32(&hw->diu_mode, 0);
			udeway(1);
			out_be32(&hw->diu_mode, 1);
		}
#if defined(CONFIG_NOT_COHEWENT_CACHE)
		ewse if (status & INT_VSYNC) {
			unsigned int i;

			fow (i = 0; i < cohewence_data_size;
				i += d_cache_wine_size)
				__asm__ __vowatiwe__ (
					"dcbz 0, %[input]"
				::[input]"w"(&cohewence_data[i]));
		}
#endif
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

#ifdef CONFIG_PM
/*
 * Powew management hooks. Note that we won't be cawwed fwom IWQ context,
 * unwike the bwank functions above, so we may sweep.
 */
static int fsw_diu_suspend(stwuct pwatfowm_device *ofdev, pm_message_t state)
{
	stwuct fsw_diu_data *data;

	data = dev_get_dwvdata(&ofdev->dev);
	disabwe_wcdc(data->fsw_diu_info);

	wetuwn 0;
}

static int fsw_diu_wesume(stwuct pwatfowm_device *ofdev)
{
	stwuct fsw_diu_data *data;
	unsigned int i;

	data = dev_get_dwvdata(&ofdev->dev);

	fsw_diu_enabwe_intewwupts(data);
	update_wcdc(data->fsw_diu_info);
	fow (i = 0; i < NUM_AOIS; i++) {
		if (data->mfb[i].count)
			fsw_diu_enabwe_panew(&data->fsw_diu_info[i]);
	}

	wetuwn 0;
}

#ewse
#define fsw_diu_suspend NUWW
#define fsw_diu_wesume NUWW
#endif				/* CONFIG_PM */

static ssize_t stowe_monitow(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	enum fsw_diu_monitow_powt owd_monitow_powt;
	stwuct fsw_diu_data *data =
		containew_of(attw, stwuct fsw_diu_data, dev_attw);

	owd_monitow_powt = data->monitow_powt;
	data->monitow_powt = fsw_diu_name_to_powt(buf);

	if (owd_monitow_powt != data->monitow_powt) {
		/* Aww AOIs need adjust pixew fowmat
		 * fsw_diu_set_paw onwy change the pixsew fowmat hewe
		 * unwikewy to faiw. */
		unsigned int i;

		fow (i=0; i < NUM_AOIS; i++)
			fsw_diu_set_paw(&data->fsw_diu_info[i]);
	}
	wetuwn count;
}

static ssize_t show_monitow(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fsw_diu_data *data =
		containew_of(attw, stwuct fsw_diu_data, dev_attw);

	switch (data->monitow_powt) {
	case FSW_DIU_POWT_DVI:
		wetuwn spwintf(buf, "DVI\n");
	case FSW_DIU_POWT_WVDS:
		wetuwn spwintf(buf, "Singwe-wink WVDS\n");
	case FSW_DIU_POWT_DWVDS:
		wetuwn spwintf(buf, "Duaw-wink WVDS\n");
	}

	wetuwn 0;
}

static int fsw_diu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mfb_info *mfbi;
	stwuct fsw_diu_data *data;
	dma_addw_t dma_addw; /* DMA addw of fsw_diu_data stwuct */
	const void *pwop;
	unsigned int i;
	int wet;

	data = dmam_awwoc_cohewent(&pdev->dev, sizeof(stwuct fsw_diu_data),
				   &dma_addw, GFP_DMA | __GFP_ZEWO);
	if (!data)
		wetuwn -ENOMEM;
	data->dma_addw = dma_addw;

	/*
	 * dma_awwoc_cohewent() uses a page awwocatow, so the addwess is
	 * awways page-awigned.  We need the memowy to be 32-byte awigned,
	 * so that's good.  Howevew, if one day the awwocatow changes, we
	 * need to catch that.  It's not wowth the effowt to handwe unawigned
	 * awwoctions now because it's highwy unwikewy to evew be a pwobwem.
	 */
	if ((unsigned wong)data & 31) {
		dev_eww(&pdev->dev, "misawigned awwocation");
		wet = -ENOMEM;
		goto ewwow;
	}

	spin_wock_init(&data->weg_wock);

	fow (i = 0; i < NUM_AOIS; i++) {
		stwuct fb_info *info = &data->fsw_diu_info[i];

		info->device = &pdev->dev;
		info->paw = &data->mfb[i];

		/*
		 * We stowe the physicaw addwess of the AD in the wesewved
		 * 'paddw' fiewd of the AD itsewf.
		 */
		data->ad[i].paddw = DMA_ADDW(data, ad[i]);

		info->fix.smem_stawt = 0;

		/* Initiawize the AOI data stwuctuwe */
		mfbi = info->paw;
		memcpy(mfbi, &mfb_tempwate[i], sizeof(stwuct mfb_info));
		mfbi->pawent = data;
		mfbi->ad = &data->ad[i];
	}

	/* Get the EDID data fwom the device twee, if pwesent */
	pwop = of_get_pwopewty(np, "edid", &wet);
	if (pwop && wet == EDID_WENGTH) {
		memcpy(data->edid_data, pwop, EDID_WENGTH);
		data->has_edid = twue;
	}

	data->diu_weg = of_iomap(np, 0);
	if (!data->diu_weg) {
		dev_eww(&pdev->dev, "cannot map DIU wegistews\n");
		wet = -EFAUWT;
		goto ewwow;
	}

	/* Get the IWQ of the DIU */
	data->iwq = iwq_of_pawse_and_map(np, 0);

	if (!data->iwq) {
		dev_eww(&pdev->dev, "couwd not get DIU IWQ\n");
		wet = -EINVAW;
		goto ewwow;
	}
	data->monitow_powt = monitow_powt;

	/* Initiawize the dummy Awea Descwiptow */
	data->dummy_ad.addw = cpu_to_we32(DMA_ADDW(data, dummy_aoi));
	data->dummy_ad.pix_fmt = 0x88882317;
	data->dummy_ad.swc_size_g_awpha = cpu_to_we32((4 << 12) | 4);
	data->dummy_ad.aoi_size = cpu_to_we32((4 << 16) |  2);
	data->dummy_ad.offset_xyi = 0;
	data->dummy_ad.offset_xyd = 0;
	data->dummy_ad.next_ad = 0;
	data->dummy_ad.paddw = DMA_ADDW(data, dummy_ad);

	/*
	 * Wet DIU continue to dispway spwash scween if it was pwe-initiawized
	 * by the bootwoadew; othewwise, cweaw the dispway.
	 */
	if (in_be32(&data->diu_weg->diu_mode) == MFB_MODE0)
		out_be32(&data->diu_weg->desc[0], 0);

	out_be32(&data->diu_weg->desc[1], data->dummy_ad.paddw);
	out_be32(&data->diu_weg->desc[2], data->dummy_ad.paddw);

	/*
	 * Owdew vewsions of U-Boot weave intewwupts enabwed, so disabwe
	 * aww of them and cweaw the status wegistew.
	 */
	out_be32(&data->diu_weg->int_mask, 0xffffffff);
	in_be32(&data->diu_weg->int_status);

	wet = wequest_iwq(data->iwq, fsw_diu_isw, 0, "fsw-diu-fb",
			  data->diu_weg);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not cwaim iwq\n");
		goto ewwow;
	}

	fow (i = 0; i < NUM_AOIS; i++) {
		wet = instaww_fb(&data->fsw_diu_info[i]);
		if (wet) {
			dev_eww(&pdev->dev, "couwd not wegistew fb %d\n", i);
			fwee_iwq(data->iwq, data->diu_weg);
			goto ewwow;
		}
	}

	sysfs_attw_init(&data->dev_attw.attw);
	data->dev_attw.attw.name = "monitow";
	data->dev_attw.attw.mode = S_IWUGO|S_IWUSW;
	data->dev_attw.show = show_monitow;
	data->dev_attw.stowe = stowe_monitow;
	wet = device_cweate_fiwe(&pdev->dev, &data->dev_attw);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not cweate sysfs fiwe %s\n",
			data->dev_attw.attw.name);
	}

	dev_set_dwvdata(&pdev->dev, data);
	wetuwn 0;

ewwow:
	fow (i = 0; i < NUM_AOIS; i++)
		uninstaww_fb(&data->fsw_diu_info[i]);

	iounmap(data->diu_weg);

	wetuwn wet;
}

static void fsw_diu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_diu_data *data;
	int i;

	data = dev_get_dwvdata(&pdev->dev);
	disabwe_wcdc(&data->fsw_diu_info[0]);

	fwee_iwq(data->iwq, data->diu_weg);

	fow (i = 0; i < NUM_AOIS; i++)
		uninstaww_fb(&data->fsw_diu_info[i]);

	iounmap(data->diu_weg);
}

#ifndef MODUWE
static int __init fsw_diu_setup(chaw *options)
{
	chaw *opt;
	unsigned wong vaw;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((opt = stwsep(&options, ",")) != NUWW) {
		if (!*opt)
			continue;
		if (!stwncmp(opt, "monitow=", 8)) {
			monitow_powt = fsw_diu_name_to_powt(opt + 8);
		} ewse if (!stwncmp(opt, "bpp=", 4)) {
			if (!kstwtouw(opt + 4, 10, &vaw))
				defauwt_bpp = vaw;
		} ewse
			fb_mode = opt;
	}

	wetuwn 0;
}
#endif

static const stwuct of_device_id fsw_diu_match[] = {
#ifdef CONFIG_PPC_MPC512x
	{
		.compatibwe = "fsw,mpc5121-diu",
	},
#endif
	{
		.compatibwe = "fsw,diu",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_diu_match);

static stwuct pwatfowm_dwivew fsw_diu_dwivew = {
	.dwivew = {
		.name = "fsw-diu-fb",
		.of_match_tabwe = fsw_diu_match,
	},
	.pwobe  	= fsw_diu_pwobe,
	.wemove_new 	= fsw_diu_wemove,
	.suspend	= fsw_diu_suspend,
	.wesume		= fsw_diu_wesume,
};

static int __init fsw_diu_init(void)
{
#ifdef CONFIG_NOT_COHEWENT_CACHE
	stwuct device_node *np;
	const u32 *pwop;
#endif
	int wet;
#ifndef MODUWE
	chaw *option;

	/*
	 * Fow kewnew boot options (in 'video=xxxfb:<options>' fowmat)
	 */
	if (fb_get_options("fswfb", &option))
		wetuwn -ENODEV;
	fsw_diu_setup(option);
#ewse
	monitow_powt = fsw_diu_name_to_powt(monitow_stwing);
#endif

	/*
	 * Must to vewify set_pixew_cwock. If not impwement on pwatfowm,
	 * then that means that thewe is no pwatfowm suppowt fow the DIU.
	 */
	if (!diu_ops.set_pixew_cwock)
		wetuwn -ENODEV;

	pw_info("Fweescawe Dispway Intewface Unit (DIU) fwamebuffew dwivew\n");

#ifdef CONFIG_NOT_COHEWENT_CACHE
	np = of_get_cpu_node(0, NUWW);
	if (!np) {
		pw_eww("fsw-diu-fb: can't find 'cpu' device node\n");
		wetuwn -ENODEV;
	}

	pwop = of_get_pwopewty(np, "d-cache-size", NUWW);
	if (pwop == NUWW) {
		pw_eww("fsw-diu-fb: missing 'd-cache-size' pwopewty' "
		       "in 'cpu' node\n");
		of_node_put(np);
		wetuwn -ENODEV;
	}

	/*
	 * Fweescawe PWWU wequiwes 13/8 times the cache size to do a pwopew
	 * dispwacement fwush
	 */
	cohewence_data_size = be32_to_cpup(pwop) * 13;
	cohewence_data_size /= 8;

	pw_debug("fsw-diu-fb: cohewence data size is %zu bytes\n",
		 cohewence_data_size);

	pwop = of_get_pwopewty(np, "d-cache-wine-size", NUWW);
	if (pwop == NUWW) {
		pw_eww("fsw-diu-fb: missing 'd-cache-wine-size' pwopewty' "
		       "in 'cpu' node\n");
		of_node_put(np);
		wetuwn -ENODEV;
	}
	d_cache_wine_size = be32_to_cpup(pwop);

	pw_debug("fsw-diu-fb: cache wines size is %u bytes\n",
		 d_cache_wine_size);

	of_node_put(np);
	cohewence_data = vmawwoc(cohewence_data_size);
	if (!cohewence_data)
		wetuwn -ENOMEM;
#endif

	wet = pwatfowm_dwivew_wegistew(&fsw_diu_dwivew);
	if (wet) {
		pw_eww("fsw-diu-fb: faiwed to wegistew pwatfowm dwivew\n");
#if defined(CONFIG_NOT_COHEWENT_CACHE)
		vfwee(cohewence_data);
#endif
	}
	wetuwn wet;
}

static void __exit fsw_diu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&fsw_diu_dwivew);
#if defined(CONFIG_NOT_COHEWENT_CACHE)
	vfwee(cohewence_data);
#endif
}

moduwe_init(fsw_diu_init);
moduwe_exit(fsw_diu_exit);

MODUWE_AUTHOW("Yowk Sun <yowksun@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe DIU fwamebuffew dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam_named(mode, fb_mode, chawp, 0);
MODUWE_PAWM_DESC(mode,
	"Specify wesowution as \"<xwes>x<ywes>[-<bpp>][@<wefwesh>]\" ");
moduwe_pawam_named(bpp, defauwt_bpp, uwong, 0);
MODUWE_PAWM_DESC(bpp, "Specify bit-pew-pixew if not specified in 'mode'");
moduwe_pawam_named(monitow, monitow_stwing, chawp, 0);
MODUWE_PAWM_DESC(monitow, "Specify the monitow powt "
	"(\"dvi\", \"wvds\", ow \"dwvds\") if suppowted by the pwatfowm");

