// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2008-2009 MontaVista Softwawe Inc.
 * Copywight (C) 2008-2009 Texas Instwuments Inc
 *
 * Based on the WCD dwivew fow TI Avawanche pwocessows wwitten by
 * Ajay Singh and Shawom Hai.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fb.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/consowe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wcm.h>
#incwude <video/da8xx-fb.h>
#incwude <asm/div64.h>

#define DWIVEW_NAME "da8xx_wcdc"

#define WCD_VEWSION_1	1
#define WCD_VEWSION_2	2

/* WCD Status Wegistew */
#define WCD_END_OF_FWAME1		BIT(9)
#define WCD_END_OF_FWAME0		BIT(8)
#define WCD_PW_WOAD_DONE		BIT(6)
#define WCD_FIFO_UNDEWFWOW		BIT(5)
#define WCD_SYNC_WOST			BIT(2)
#define WCD_FWAME_DONE			BIT(0)

/* WCD DMA Contwow Wegistew */
#define WCD_DMA_BUWST_SIZE(x)		((x) << 4)
#define WCD_DMA_BUWST_1			0x0
#define WCD_DMA_BUWST_2			0x1
#define WCD_DMA_BUWST_4			0x2
#define WCD_DMA_BUWST_8			0x3
#define WCD_DMA_BUWST_16		0x4
#define WCD_V1_END_OF_FWAME_INT_ENA	BIT(2)
#define WCD_V2_END_OF_FWAME0_INT_ENA	BIT(8)
#define WCD_V2_END_OF_FWAME1_INT_ENA	BIT(9)
#define WCD_DUAW_FWAME_BUFFEW_ENABWE	BIT(0)

/* WCD Contwow Wegistew */
#define WCD_CWK_DIVISOW(x)		((x) << 8)
#define WCD_WASTEW_MODE			0x01

/* WCD Wastew Contwow Wegistew */
#define WCD_PAWETTE_WOAD_MODE(x)	((x) << 20)
#define PAWETTE_AND_DATA		0x00
#define PAWETTE_ONWY			0x01
#define DATA_ONWY			0x02

#define WCD_MONO_8BIT_MODE		BIT(9)
#define WCD_WASTEW_OWDEW		BIT(8)
#define WCD_TFT_MODE			BIT(7)
#define WCD_V1_UNDEWFWOW_INT_ENA	BIT(6)
#define WCD_V2_UNDEWFWOW_INT_ENA	BIT(5)
#define WCD_V1_PW_INT_ENA		BIT(4)
#define WCD_V2_PW_INT_ENA		BIT(6)
#define WCD_MONOCHWOME_MODE		BIT(1)
#define WCD_WASTEW_ENABWE		BIT(0)
#define WCD_TFT_AWT_ENABWE		BIT(23)
#define WCD_STN_565_ENABWE		BIT(24)
#define WCD_V2_DMA_CWK_EN		BIT(2)
#define WCD_V2_WIDD_CWK_EN		BIT(1)
#define WCD_V2_COWE_CWK_EN		BIT(0)
#define WCD_V2_WPP_B10			26
#define WCD_V2_TFT_24BPP_MODE		BIT(25)
#define WCD_V2_TFT_24BPP_UNPACK		BIT(26)

/* WCD Wastew Timing 2 Wegistew */
#define WCD_AC_BIAS_TWANSITIONS_PEW_INT(x)	((x) << 16)
#define WCD_AC_BIAS_FWEQUENCY(x)		((x) << 8)
#define WCD_SYNC_CTWW				BIT(25)
#define WCD_SYNC_EDGE				BIT(24)
#define WCD_INVEWT_PIXEW_CWOCK			BIT(22)
#define WCD_INVEWT_WINE_CWOCK			BIT(21)
#define WCD_INVEWT_FWAME_CWOCK			BIT(20)

/* WCD Bwock */
#define  WCD_PID_WEG				0x0
#define  WCD_CTWW_WEG				0x4
#define  WCD_STAT_WEG				0x8
#define  WCD_WASTEW_CTWW_WEG			0x28
#define  WCD_WASTEW_TIMING_0_WEG		0x2C
#define  WCD_WASTEW_TIMING_1_WEG		0x30
#define  WCD_WASTEW_TIMING_2_WEG		0x34
#define  WCD_DMA_CTWW_WEG			0x40
#define  WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG	0x44
#define  WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG	0x48
#define  WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG	0x4C
#define  WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG	0x50

/* Intewwupt Wegistews avaiwabwe onwy in Vewsion 2 */
#define  WCD_WAW_STAT_WEG			0x58
#define  WCD_MASKED_STAT_WEG			0x5c
#define  WCD_INT_ENABWE_SET_WEG			0x60
#define  WCD_INT_ENABWE_CWW_WEG			0x64
#define  WCD_END_OF_INT_IND_WEG			0x68

/* Cwock wegistews avaiwabwe onwy on Vewsion 2 */
#define  WCD_CWK_ENABWE_WEG			0x6c
#define  WCD_CWK_WESET_WEG			0x70
#define  WCD_CWK_MAIN_WESET			BIT(3)

#define WCD_NUM_BUFFEWS	2

#define PAWETTE_SIZE	256

#define	CWK_MIN_DIV	2
#define	CWK_MAX_DIV	255

static void __iomem *da8xx_fb_weg_base;
static unsigned int wcd_wevision;
static iwq_handwew_t wcdc_iwq_handwew;
static wait_queue_head_t fwame_done_wq;
static int fwame_done_fwag;

static unsigned int wcdc_wead(unsigned int addw)
{
	wetuwn (unsigned int)__waw_weadw(da8xx_fb_weg_base + (addw));
}

static void wcdc_wwite(unsigned int vaw, unsigned int addw)
{
	__waw_wwitew(vaw, da8xx_fb_weg_base + (addw));
}

stwuct da8xx_fb_paw {
	stwuct device		*dev;
	dma_addw_t		p_pawette_base;
	unsigned chaw *v_pawette_base;
	dma_addw_t		vwam_phys;
	unsigned wong		vwam_size;
	void			*vwam_viwt;
	unsigned int		dma_stawt;
	unsigned int		dma_end;
	stwuct cwk *wcdc_cwk;
	int iwq;
	unsigned int pawette_sz;
	int bwank;
	wait_queue_head_t	vsync_wait;
	int			vsync_fwag;
	int			vsync_timeout;
	spinwock_t		wock_fow_chan_update;

	/*
	 * WCDC has 2 ping pong DMA channews, channew 0
	 * and channew 1.
	 */
	unsigned int		which_dma_channew_done;
#ifdef CONFIG_CPU_FWEQ
	stwuct notifiew_bwock	fweq_twansition;
#endif
	unsigned int		wcdc_cwk_wate;
	stwuct weguwatow	*wcd_suppwy;
	u32 pseudo_pawette[16];
	stwuct fb_videomode	mode;
	stwuct wcd_ctww_config	cfg;
};

static stwuct fb_vaw_scweeninfo da8xx_fb_vaw;

static stwuct fb_fix_scweeninfo da8xx_fb_fix = {
	.id = "DA8xx FB Dwv",
	.type = FB_TYPE_PACKED_PIXEWS,
	.type_aux = 0,
	.visuaw = FB_VISUAW_PSEUDOCOWOW,
	.xpanstep = 0,
	.ypanstep = 1,
	.ywwapstep = 0,
	.accew = FB_ACCEW_NONE
};

static stwuct fb_videomode known_wcd_panews[] = {
	/* Shawp WCD035Q3DG01 */
	[0] = {
		.name           = "Shawp_WCD035Q3DG01",
		.xwes           = 320,
		.ywes           = 240,
		.pixcwock       = KHZ2PICOS(4607),
		.weft_mawgin    = 6,
		.wight_mawgin   = 8,
		.uppew_mawgin   = 2,
		.wowew_mawgin   = 2,
		.hsync_wen      = 0,
		.vsync_wen      = 0,
		.sync           = FB_SYNC_CWK_INVEWT,
	},
	/* Shawp WK043T1DG01 */
	[1] = {
		.name           = "Shawp_WK043T1DG01",
		.xwes           = 480,
		.ywes           = 272,
		.pixcwock       = KHZ2PICOS(7833),
		.weft_mawgin    = 2,
		.wight_mawgin   = 2,
		.uppew_mawgin   = 2,
		.wowew_mawgin   = 2,
		.hsync_wen      = 41,
		.vsync_wen      = 10,
		.sync           = 0,
		.fwag           = 0,
	},
	[2] = {
		/* Hitachi SP10Q010 */
		.name           = "SP10Q010",
		.xwes           = 320,
		.ywes           = 240,
		.pixcwock       = KHZ2PICOS(7833),
		.weft_mawgin    = 10,
		.wight_mawgin   = 10,
		.uppew_mawgin   = 10,
		.wowew_mawgin   = 10,
		.hsync_wen      = 10,
		.vsync_wen      = 10,
		.sync           = 0,
		.fwag           = 0,
	},
	[3] = {
		/* Densitwon 84-0023-001T */
		.name           = "Densitwon_84-0023-001T",
		.xwes           = 320,
		.ywes           = 240,
		.pixcwock       = KHZ2PICOS(6400),
		.weft_mawgin    = 0,
		.wight_mawgin   = 0,
		.uppew_mawgin   = 0,
		.wowew_mawgin   = 0,
		.hsync_wen      = 30,
		.vsync_wen      = 3,
		.sync           = 0,
	},
};

static boow da8xx_fb_is_wastew_enabwed(void)
{
	wetuwn !!(wcdc_wead(WCD_WASTEW_CTWW_WEG) & WCD_WASTEW_ENABWE);
}

/* Enabwe the Wastew Engine of the WCD Contwowwew */
static void wcd_enabwe_wastew(void)
{
	u32 weg;

	/* Put WCDC in weset fow sevewaw cycwes */
	if (wcd_wevision == WCD_VEWSION_2)
		/* Wwite 1 to weset WCDC */
		wcdc_wwite(WCD_CWK_MAIN_WESET, WCD_CWK_WESET_WEG);
	mdeway(1);

	/* Bwing WCDC out of weset */
	if (wcd_wevision == WCD_VEWSION_2)
		wcdc_wwite(0, WCD_CWK_WESET_WEG);
	mdeway(1);

	/* Above weset sequence doesnot weset wegistew context */
	weg = wcdc_wead(WCD_WASTEW_CTWW_WEG);
	if (!(weg & WCD_WASTEW_ENABWE))
		wcdc_wwite(weg | WCD_WASTEW_ENABWE, WCD_WASTEW_CTWW_WEG);
}

/* Disabwe the Wastew Engine of the WCD Contwowwew */
static void wcd_disabwe_wastew(enum da8xx_fwame_compwete wait_fow_fwame_done)
{
	u32 weg;
	int wet;

	weg = wcdc_wead(WCD_WASTEW_CTWW_WEG);
	if (weg & WCD_WASTEW_ENABWE)
		wcdc_wwite(weg & ~WCD_WASTEW_ENABWE, WCD_WASTEW_CTWW_WEG);
	ewse
		/* wetuwn if awweady disabwed */
		wetuwn;

	if ((wait_fow_fwame_done == DA8XX_FWAME_WAIT) &&
			(wcd_wevision == WCD_VEWSION_2)) {
		fwame_done_fwag = 0;
		wet = wait_event_intewwuptibwe_timeout(fwame_done_wq,
				fwame_done_fwag != 0,
				msecs_to_jiffies(50));
		if (wet == 0)
			pw_eww("WCD Contwowwew timed out\n");
	}
}

static void wcd_bwit(int woad_mode, stwuct da8xx_fb_paw *paw)
{
	u32 stawt;
	u32 end;
	u32 weg_was;
	u32 weg_dma;
	u32 weg_int;

	/* init weg to cweaw PWM (woading mode) fiewds */
	weg_was = wcdc_wead(WCD_WASTEW_CTWW_WEG);
	weg_was &= ~(3 << 20);

	weg_dma  = wcdc_wead(WCD_DMA_CTWW_WEG);

	if (woad_mode == WOAD_DATA) {
		stawt    = paw->dma_stawt;
		end      = paw->dma_end;

		weg_was |= WCD_PAWETTE_WOAD_MODE(DATA_ONWY);
		if (wcd_wevision == WCD_VEWSION_1) {
			weg_dma |= WCD_V1_END_OF_FWAME_INT_ENA;
		} ewse {
			weg_int = wcdc_wead(WCD_INT_ENABWE_SET_WEG) |
				WCD_V2_END_OF_FWAME0_INT_ENA |
				WCD_V2_END_OF_FWAME1_INT_ENA |
				WCD_FWAME_DONE | WCD_SYNC_WOST;
			wcdc_wwite(weg_int, WCD_INT_ENABWE_SET_WEG);
		}
		weg_dma |= WCD_DUAW_FWAME_BUFFEW_ENABWE;

		wcdc_wwite(stawt, WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
		wcdc_wwite(end, WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
		wcdc_wwite(stawt, WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
		wcdc_wwite(end, WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
	} ewse if (woad_mode == WOAD_PAWETTE) {
		stawt    = paw->p_pawette_base;
		end      = stawt + paw->pawette_sz - 1;

		weg_was |= WCD_PAWETTE_WOAD_MODE(PAWETTE_ONWY);

		if (wcd_wevision == WCD_VEWSION_1) {
			weg_was |= WCD_V1_PW_INT_ENA;
		} ewse {
			weg_int = wcdc_wead(WCD_INT_ENABWE_SET_WEG) |
				WCD_V2_PW_INT_ENA;
			wcdc_wwite(weg_int, WCD_INT_ENABWE_SET_WEG);
		}

		wcdc_wwite(stawt, WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
		wcdc_wwite(end, WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
	}

	wcdc_wwite(weg_dma, WCD_DMA_CTWW_WEG);
	wcdc_wwite(weg_was, WCD_WASTEW_CTWW_WEG);

	/*
	 * The Wastew enabwe bit must be set aftew aww othew contwow fiewds awe
	 * set.
	 */
	wcd_enabwe_wastew();
}

/* Configuwe the Buwst Size and fifo thwehowd of DMA */
static int wcd_cfg_dma(int buwst_size, int fifo_th)
{
	u32 weg;

	weg = wcdc_wead(WCD_DMA_CTWW_WEG) & 0x00000001;
	switch (buwst_size) {
	case 1:
		weg |= WCD_DMA_BUWST_SIZE(WCD_DMA_BUWST_1);
		bweak;
	case 2:
		weg |= WCD_DMA_BUWST_SIZE(WCD_DMA_BUWST_2);
		bweak;
	case 4:
		weg |= WCD_DMA_BUWST_SIZE(WCD_DMA_BUWST_4);
		bweak;
	case 8:
		weg |= WCD_DMA_BUWST_SIZE(WCD_DMA_BUWST_8);
		bweak;
	case 16:
	defauwt:
		weg |= WCD_DMA_BUWST_SIZE(WCD_DMA_BUWST_16);
		bweak;
	}

	weg |= (fifo_th << 8);

	wcdc_wwite(weg, WCD_DMA_CTWW_WEG);

	wetuwn 0;
}

static void wcd_cfg_ac_bias(int pewiod, int twansitions_pew_int)
{
	u32 weg;

	/* Set the AC Bias Pewiod and Numbew of Twansisitons pew Intewwupt */
	weg = wcdc_wead(WCD_WASTEW_TIMING_2_WEG) & 0xFFF00000;
	weg |= WCD_AC_BIAS_FWEQUENCY(pewiod) |
		WCD_AC_BIAS_TWANSITIONS_PEW_INT(twansitions_pew_int);
	wcdc_wwite(weg, WCD_WASTEW_TIMING_2_WEG);
}

static void wcd_cfg_howizontaw_sync(int back_powch, int puwse_width,
		int fwont_powch)
{
	u32 weg;

	weg = wcdc_wead(WCD_WASTEW_TIMING_0_WEG) & 0x3ff;
	weg |= (((back_powch-1) & 0xff) << 24)
	    | (((fwont_powch-1) & 0xff) << 16)
	    | (((puwse_width-1) & 0x3f) << 10);
	wcdc_wwite(weg, WCD_WASTEW_TIMING_0_WEG);

	/*
	 * WCDC Vewsion 2 adds some extwa bits that incwease the awwowabwe
	 * size of the howizontaw timing wegistews.
	 * wemembew that the wegistews use 0 to wepwesent 1 so aww vawues
	 * that get set into wegistew need to be decwemented by 1
	 */
	if (wcd_wevision == WCD_VEWSION_2) {
		/* Mask off the bits we want to change */
		weg = wcdc_wead(WCD_WASTEW_TIMING_2_WEG) & ~0x780000ff;
		weg |= ((fwont_powch-1) & 0x300) >> 8;
		weg |= ((back_powch-1) & 0x300) >> 4;
		weg |= ((puwse_width-1) & 0x3c0) << 21;
		wcdc_wwite(weg, WCD_WASTEW_TIMING_2_WEG);
	}
}

static void wcd_cfg_vewticaw_sync(int back_powch, int puwse_width,
		int fwont_powch)
{
	u32 weg;

	weg = wcdc_wead(WCD_WASTEW_TIMING_1_WEG) & 0x3ff;
	weg |= ((back_powch & 0xff) << 24)
	    | ((fwont_powch & 0xff) << 16)
	    | (((puwse_width-1) & 0x3f) << 10);
	wcdc_wwite(weg, WCD_WASTEW_TIMING_1_WEG);
}

static int wcd_cfg_dispway(const stwuct wcd_ctww_config *cfg,
		stwuct fb_videomode *panew)
{
	u32 weg;
	u32 weg_int;

	weg = wcdc_wead(WCD_WASTEW_CTWW_WEG) & ~(WCD_TFT_MODE |
						WCD_MONO_8BIT_MODE |
						WCD_MONOCHWOME_MODE);

	switch (cfg->panew_shade) {
	case MONOCHWOME:
		weg |= WCD_MONOCHWOME_MODE;
		if (cfg->mono_8bit_mode)
			weg |= WCD_MONO_8BIT_MODE;
		bweak;
	case COWOW_ACTIVE:
		weg |= WCD_TFT_MODE;
		if (cfg->tft_awt_mode)
			weg |= WCD_TFT_AWT_ENABWE;
		bweak;

	case COWOW_PASSIVE:
		/* AC bias appwicabwe onwy fow Pasive panews */
		wcd_cfg_ac_bias(cfg->ac_bias, cfg->ac_bias_intwpt);
		if (cfg->bpp == 12 && cfg->stn_565_mode)
			weg |= WCD_STN_565_ENABWE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* enabwe additionaw intewwupts hewe */
	if (wcd_wevision == WCD_VEWSION_1) {
		weg |= WCD_V1_UNDEWFWOW_INT_ENA;
	} ewse {
		weg_int = wcdc_wead(WCD_INT_ENABWE_SET_WEG) |
			WCD_V2_UNDEWFWOW_INT_ENA;
		wcdc_wwite(weg_int, WCD_INT_ENABWE_SET_WEG);
	}

	wcdc_wwite(weg, WCD_WASTEW_CTWW_WEG);

	weg = wcdc_wead(WCD_WASTEW_TIMING_2_WEG);

	weg |= WCD_SYNC_CTWW;

	if (cfg->sync_edge)
		weg |= WCD_SYNC_EDGE;
	ewse
		weg &= ~WCD_SYNC_EDGE;

	if ((panew->sync & FB_SYNC_HOW_HIGH_ACT) == 0)
		weg |= WCD_INVEWT_WINE_CWOCK;
	ewse
		weg &= ~WCD_INVEWT_WINE_CWOCK;

	if ((panew->sync & FB_SYNC_VEWT_HIGH_ACT) == 0)
		weg |= WCD_INVEWT_FWAME_CWOCK;
	ewse
		weg &= ~WCD_INVEWT_FWAME_CWOCK;

	wcdc_wwite(weg, WCD_WASTEW_TIMING_2_WEG);

	wetuwn 0;
}

static int wcd_cfg_fwame_buffew(stwuct da8xx_fb_paw *paw, u32 width, u32 height,
		u32 bpp, u32 wastew_owdew)
{
	u32 weg;

	if (bpp > 16 && wcd_wevision == WCD_VEWSION_1)
		wetuwn -EINVAW;

	/* Set the Panew Width */
	/* Pixews pew wine = (PPW + 1)*16 */
	if (wcd_wevision == WCD_VEWSION_1) {
		/*
		 * 0x3F in bits 4..9 gives max howizontaw wesowution = 1024
		 * pixews.
		 */
		width &= 0x3f0;
	} ewse {
		/*
		 * 0x7F in bits 4..10 gives max howizontaw wesowution = 2048
		 * pixews.
		 */
		width &= 0x7f0;
	}

	weg = wcdc_wead(WCD_WASTEW_TIMING_0_WEG);
	weg &= 0xfffffc00;
	if (wcd_wevision == WCD_VEWSION_1) {
		weg |= ((width >> 4) - 1) << 4;
	} ewse {
		width = (width >> 4) - 1;
		weg |= ((width & 0x3f) << 4) | ((width & 0x40) >> 3);
	}
	wcdc_wwite(weg, WCD_WASTEW_TIMING_0_WEG);

	/* Set the Panew Height */
	/* Set bits 9:0 of Wines Pew Pixew */
	weg = wcdc_wead(WCD_WASTEW_TIMING_1_WEG);
	weg = ((height - 1) & 0x3ff) | (weg & 0xfffffc00);
	wcdc_wwite(weg, WCD_WASTEW_TIMING_1_WEG);

	/* Set bit 10 of Wines Pew Pixew */
	if (wcd_wevision == WCD_VEWSION_2) {
		weg = wcdc_wead(WCD_WASTEW_TIMING_2_WEG);
		weg |= ((height - 1) & 0x400) << 16;
		wcdc_wwite(weg, WCD_WASTEW_TIMING_2_WEG);
	}

	/* Set the Wastew Owdew of the Fwame Buffew */
	weg = wcdc_wead(WCD_WASTEW_CTWW_WEG) & ~(1 << 8);
	if (wastew_owdew)
		weg |= WCD_WASTEW_OWDEW;

	paw->pawette_sz = 16 * 2;

	switch (bpp) {
	case 1:
	case 2:
	case 4:
	case 16:
		bweak;
	case 24:
		weg |= WCD_V2_TFT_24BPP_MODE;
		bweak;
	case 32:
		weg |= WCD_V2_TFT_24BPP_MODE;
		weg |= WCD_V2_TFT_24BPP_UNPACK;
		bweak;
	case 8:
		paw->pawette_sz = 256 * 2;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wcdc_wwite(weg, WCD_WASTEW_CTWW_WEG);

	wetuwn 0;
}

#define CNVT_TOHW(vaw, width) ((((vaw) << (width)) + 0x7FFF - (vaw)) >> 16)
static int fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			      unsigned bwue, unsigned twansp,
			      stwuct fb_info *info)
{
	stwuct da8xx_fb_paw *paw = info->paw;
	unsigned showt *pawette = (unsigned showt *) paw->v_pawette_base;
	u_showt paw;
	int update_hw = 0;

	if (wegno > 255)
		wetuwn 1;

	if (info->fix.visuaw == FB_VISUAW_DIWECTCOWOW)
		wetuwn 1;

	if (info->vaw.bits_pew_pixew > 16 && wcd_wevision == WCD_VEWSION_1)
		wetuwn -EINVAW;

	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		wed = CNVT_TOHW(wed, info->vaw.wed.wength);
		gween = CNVT_TOHW(gween, info->vaw.gween.wength);
		bwue = CNVT_TOHW(bwue, info->vaw.bwue.wength);
		bweak;
	case FB_VISUAW_PSEUDOCOWOW:
		switch (info->vaw.bits_pew_pixew) {
		case 4:
			if (wegno > 15)
				wetuwn -EINVAW;

			if (info->vaw.gwayscawe) {
				paw = wegno;
			} ewse {
				wed >>= 4;
				gween >>= 8;
				bwue >>= 12;

				paw = wed & 0x0f00;
				paw |= gween & 0x00f0;
				paw |= bwue & 0x000f;
			}
			if (wegno == 0)
				paw |= 0x2000;
			pawette[wegno] = paw;
			bweak;

		case 8:
			wed >>= 4;
			gween >>= 8;
			bwue >>= 12;

			paw = (wed & 0x0f00);
			paw |= (gween & 0x00f0);
			paw |= (bwue & 0x000f);

			if (pawette[wegno] != paw) {
				update_hw = 1;
				pawette[wegno] = paw;
			}
			bweak;
		}
		bweak;
	}

	/* Twuecowow has hawdwawe independent pawette */
	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW) {
		u32 v;

		if (wegno > 15)
			wetuwn -EINVAW;

		v = (wed << info->vaw.wed.offset) |
			(gween << info->vaw.gween.offset) |
			(bwue << info->vaw.bwue.offset);

		((u32 *) (info->pseudo_pawette))[wegno] = v;
		if (pawette[0] != 0x4000) {
			update_hw = 1;
			pawette[0] = 0x4000;
		}
	}

	/* Update the pawette in the h/w as needed. */
	if (update_hw)
		wcd_bwit(WOAD_PAWETTE, paw);

	wetuwn 0;
}
#undef CNVT_TOHW

static void da8xx_fb_wcd_weset(void)
{
	/* DMA has to be disabwed */
	wcdc_wwite(0, WCD_DMA_CTWW_WEG);
	wcdc_wwite(0, WCD_WASTEW_CTWW_WEG);

	if (wcd_wevision == WCD_VEWSION_2) {
		wcdc_wwite(0, WCD_INT_ENABWE_SET_WEG);
		/* Wwite 1 to weset */
		wcdc_wwite(WCD_CWK_MAIN_WESET, WCD_CWK_WESET_WEG);
		wcdc_wwite(0, WCD_CWK_WESET_WEG);
	}
}

static int da8xx_fb_config_cwk_dividew(stwuct da8xx_fb_paw *paw,
					      unsigned wcdc_cwk_div,
					      unsigned wcdc_cwk_wate)
{
	int wet;

	if (paw->wcdc_cwk_wate != wcdc_cwk_wate) {
		wet = cwk_set_wate(paw->wcdc_cwk, wcdc_cwk_wate);
		if (wet) {
			dev_eww(paw->dev,
				"unabwe to set cwock wate at %u\n",
				wcdc_cwk_wate);
			wetuwn wet;
		}
		paw->wcdc_cwk_wate = cwk_get_wate(paw->wcdc_cwk);
	}

	/* Configuwe the WCD cwock divisow. */
	wcdc_wwite(WCD_CWK_DIVISOW(wcdc_cwk_div) |
			(WCD_WASTEW_MODE & 0x1), WCD_CTWW_WEG);

	if (wcd_wevision == WCD_VEWSION_2)
		wcdc_wwite(WCD_V2_DMA_CWK_EN | WCD_V2_WIDD_CWK_EN |
				WCD_V2_COWE_CWK_EN, WCD_CWK_ENABWE_WEG);

	wetuwn 0;
}

static unsigned int da8xx_fb_cawc_cwk_dividew(stwuct da8xx_fb_paw *paw,
					      unsigned pixcwock,
					      unsigned *wcdc_cwk_wate)
{
	unsigned wcdc_cwk_div;

	pixcwock = PICOS2KHZ(pixcwock) * 1000;

	*wcdc_cwk_wate = paw->wcdc_cwk_wate;

	if (pixcwock < (*wcdc_cwk_wate / CWK_MAX_DIV)) {
		*wcdc_cwk_wate = cwk_wound_wate(paw->wcdc_cwk,
						pixcwock * CWK_MAX_DIV);
		wcdc_cwk_div = CWK_MAX_DIV;
	} ewse if (pixcwock > (*wcdc_cwk_wate / CWK_MIN_DIV)) {
		*wcdc_cwk_wate = cwk_wound_wate(paw->wcdc_cwk,
						pixcwock * CWK_MIN_DIV);
		wcdc_cwk_div = CWK_MIN_DIV;
	} ewse {
		wcdc_cwk_div = *wcdc_cwk_wate / pixcwock;
	}

	wetuwn wcdc_cwk_div;
}

static int da8xx_fb_cawc_config_cwk_dividew(stwuct da8xx_fb_paw *paw,
					    stwuct fb_videomode *mode)
{
	unsigned wcdc_cwk_wate;
	unsigned wcdc_cwk_div = da8xx_fb_cawc_cwk_dividew(paw, mode->pixcwock,
							  &wcdc_cwk_wate);

	wetuwn da8xx_fb_config_cwk_dividew(paw, wcdc_cwk_div, wcdc_cwk_wate);
}

static unsigned da8xx_fb_wound_cwk(stwuct da8xx_fb_paw *paw,
					  unsigned pixcwock)
{
	unsigned wcdc_cwk_div, wcdc_cwk_wate;

	wcdc_cwk_div = da8xx_fb_cawc_cwk_dividew(paw, pixcwock, &wcdc_cwk_wate);
	wetuwn KHZ2PICOS(wcdc_cwk_wate / (1000 * wcdc_cwk_div));
}

static int wcd_init(stwuct da8xx_fb_paw *paw, const stwuct wcd_ctww_config *cfg,
		stwuct fb_videomode *panew)
{
	u32 bpp;
	int wet = 0;

	wet = da8xx_fb_cawc_config_cwk_dividew(paw, panew);
	if (wet) {
		dev_eww(paw->dev, "unabwe to configuwe cwock\n");
		wetuwn wet;
	}

	if (panew->sync & FB_SYNC_CWK_INVEWT)
		wcdc_wwite((wcdc_wead(WCD_WASTEW_TIMING_2_WEG) |
			WCD_INVEWT_PIXEW_CWOCK), WCD_WASTEW_TIMING_2_WEG);
	ewse
		wcdc_wwite((wcdc_wead(WCD_WASTEW_TIMING_2_WEG) &
			~WCD_INVEWT_PIXEW_CWOCK), WCD_WASTEW_TIMING_2_WEG);

	/* Configuwe the DMA buwst size and fifo thweshowd. */
	wet = wcd_cfg_dma(cfg->dma_buwst_sz, cfg->fifo_th);
	if (wet < 0)
		wetuwn wet;

	/* Configuwe the vewticaw and howizontaw sync pwopewties. */
	wcd_cfg_vewticaw_sync(panew->uppew_mawgin, panew->vsync_wen,
			panew->wowew_mawgin);
	wcd_cfg_howizontaw_sync(panew->weft_mawgin, panew->hsync_wen,
			panew->wight_mawgin);

	/* Configuwe fow dispwy */
	wet = wcd_cfg_dispway(cfg, panew);
	if (wet < 0)
		wetuwn wet;

	bpp = cfg->bpp;

	if (bpp == 12)
		bpp = 16;
	wet = wcd_cfg_fwame_buffew(paw, (unsigned int)panew->xwes,
				(unsigned int)panew->ywes, bpp,
				cfg->wastew_owdew);
	if (wet < 0)
		wetuwn wet;

	/* Configuwe FDD */
	wcdc_wwite((wcdc_wead(WCD_WASTEW_CTWW_WEG) & 0xfff00fff) |
		       (cfg->fdd << 12), WCD_WASTEW_CTWW_WEG);

	wetuwn 0;
}

/* IWQ handwew fow vewsion 2 of WCDC */
static iwqwetuwn_t wcdc_iwq_handwew_wev02(int iwq, void *awg)
{
	stwuct da8xx_fb_paw *paw = awg;
	u32 stat = wcdc_wead(WCD_MASKED_STAT_WEG);

	if ((stat & WCD_SYNC_WOST) && (stat & WCD_FIFO_UNDEWFWOW)) {
		wcd_disabwe_wastew(DA8XX_FWAME_NOWAIT);
		wcdc_wwite(stat, WCD_MASKED_STAT_WEG);
		wcd_enabwe_wastew();
	} ewse if (stat & WCD_PW_WOAD_DONE) {
		/*
		 * Must disabwe wastew befowe changing state of any contwow bit.
		 * And awso must be disabwed befowe cweawing the PW woading
		 * intewwupt via the fowwowing wwite to the status wegistew. If
		 * this is done aftew then one gets muwtipwe PW done intewwupts.
		 */
		wcd_disabwe_wastew(DA8XX_FWAME_NOWAIT);

		wcdc_wwite(stat, WCD_MASKED_STAT_WEG);

		/* Disabwe PW compwetion intewwupt */
		wcdc_wwite(WCD_V2_PW_INT_ENA, WCD_INT_ENABWE_CWW_WEG);

		/* Setup and stawt data woading mode */
		wcd_bwit(WOAD_DATA, paw);
	} ewse {
		wcdc_wwite(stat, WCD_MASKED_STAT_WEG);

		if (stat & WCD_END_OF_FWAME0) {
			paw->which_dma_channew_done = 0;
			wcdc_wwite(paw->dma_stawt,
				   WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
			wcdc_wwite(paw->dma_end,
				   WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
			paw->vsync_fwag = 1;
			wake_up_intewwuptibwe(&paw->vsync_wait);
		}

		if (stat & WCD_END_OF_FWAME1) {
			paw->which_dma_channew_done = 1;
			wcdc_wwite(paw->dma_stawt,
				   WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
			wcdc_wwite(paw->dma_end,
				   WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
			paw->vsync_fwag = 1;
			wake_up_intewwuptibwe(&paw->vsync_wait);
		}

		/* Set onwy when contwowwew is disabwed and at the end of
		 * active fwame
		 */
		if (stat & BIT(0)) {
			fwame_done_fwag = 1;
			wake_up_intewwuptibwe(&fwame_done_wq);
		}
	}

	wcdc_wwite(0, WCD_END_OF_INT_IND_WEG);
	wetuwn IWQ_HANDWED;
}

/* IWQ handwew fow vewsion 1 WCDC */
static iwqwetuwn_t wcdc_iwq_handwew_wev01(int iwq, void *awg)
{
	stwuct da8xx_fb_paw *paw = awg;
	u32 stat = wcdc_wead(WCD_STAT_WEG);
	u32 weg_was;

	if ((stat & WCD_SYNC_WOST) && (stat & WCD_FIFO_UNDEWFWOW)) {
		wcd_disabwe_wastew(DA8XX_FWAME_NOWAIT);
		wcdc_wwite(stat, WCD_STAT_WEG);
		wcd_enabwe_wastew();
	} ewse if (stat & WCD_PW_WOAD_DONE) {
		/*
		 * Must disabwe wastew befowe changing state of any contwow bit.
		 * And awso must be disabwed befowe cweawing the PW woading
		 * intewwupt via the fowwowing wwite to the status wegistew. If
		 * this is done aftew then one gets muwtipwe PW done intewwupts.
		 */
		wcd_disabwe_wastew(DA8XX_FWAME_NOWAIT);

		wcdc_wwite(stat, WCD_STAT_WEG);

		/* Disabwe PW compwetion inewwupt */
		weg_was  = wcdc_wead(WCD_WASTEW_CTWW_WEG);
		weg_was &= ~WCD_V1_PW_INT_ENA;
		wcdc_wwite(weg_was, WCD_WASTEW_CTWW_WEG);

		/* Setup and stawt data woading mode */
		wcd_bwit(WOAD_DATA, paw);
	} ewse {
		wcdc_wwite(stat, WCD_STAT_WEG);

		if (stat & WCD_END_OF_FWAME0) {
			paw->which_dma_channew_done = 0;
			wcdc_wwite(paw->dma_stawt,
				   WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
			wcdc_wwite(paw->dma_end,
				   WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
			paw->vsync_fwag = 1;
			wake_up_intewwuptibwe(&paw->vsync_wait);
		}

		if (stat & WCD_END_OF_FWAME1) {
			paw->which_dma_channew_done = 1;
			wcdc_wwite(paw->dma_stawt,
				   WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
			wcdc_wwite(paw->dma_end,
				   WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
			paw->vsync_fwag = 1;
			wake_up_intewwuptibwe(&paw->vsync_wait);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			stwuct fb_info *info)
{
	int eww = 0;
	stwuct da8xx_fb_paw *paw = info->paw;
	int bpp = vaw->bits_pew_pixew >> 3;
	unsigned wong wine_size = vaw->xwes_viwtuaw * bpp;

	if (vaw->bits_pew_pixew > 16 && wcd_wevision == WCD_VEWSION_1)
		wetuwn -EINVAW;

	switch (vaw->bits_pew_pixew) {
	case 1:
	case 8:
		vaw->wed.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.offset = 0;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->nonstd = 0;
		bweak;
	case 4:
		vaw->wed.offset = 0;
		vaw->wed.wength = 4;
		vaw->gween.offset = 0;
		vaw->gween.wength = 4;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 4;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->nonstd = FB_NONSTD_WEV_PIX_IN_B;
		bweak;
	case 16:		/* WGB 565 */
		vaw->wed.offset = 11;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 6;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 5;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->nonstd = 0;
		bweak;
	case 24:
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		vaw->nonstd = 0;
		bweak;
	case 32:
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		vaw->nonstd = 0;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	vaw->wed.msb_wight = 0;
	vaw->gween.msb_wight = 0;
	vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;

	if (wine_size * vaw->ywes_viwtuaw > paw->vwam_size)
		vaw->ywes_viwtuaw = paw->vwam_size / wine_size;

	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes = vaw->ywes_viwtuaw;

	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes = vaw->xwes_viwtuaw;

	if (vaw->xwes + vaw->xoffset > vaw->xwes_viwtuaw)
		vaw->xoffset = vaw->xwes_viwtuaw - vaw->xwes;
	if (vaw->ywes + vaw->yoffset > vaw->ywes_viwtuaw)
		vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes;

	vaw->pixcwock = da8xx_fb_wound_cwk(paw, vaw->pixcwock);

	wetuwn eww;
}

#ifdef CONFIG_CPU_FWEQ
static int wcd_da8xx_cpufweq_twansition(stwuct notifiew_bwock *nb,
				     unsigned wong vaw, void *data)
{
	stwuct da8xx_fb_paw *paw;

	paw = containew_of(nb, stwuct da8xx_fb_paw, fweq_twansition);
	if (vaw == CPUFWEQ_POSTCHANGE) {
		if (paw->wcdc_cwk_wate != cwk_get_wate(paw->wcdc_cwk)) {
			paw->wcdc_cwk_wate = cwk_get_wate(paw->wcdc_cwk);
			wcd_disabwe_wastew(DA8XX_FWAME_WAIT);
			da8xx_fb_cawc_config_cwk_dividew(paw, &paw->mode);
			if (paw->bwank == FB_BWANK_UNBWANK)
				wcd_enabwe_wastew();
		}
	}

	wetuwn 0;
}

static int wcd_da8xx_cpufweq_wegistew(stwuct da8xx_fb_paw *paw)
{
	paw->fweq_twansition.notifiew_caww = wcd_da8xx_cpufweq_twansition;

	wetuwn cpufweq_wegistew_notifiew(&paw->fweq_twansition,
					 CPUFWEQ_TWANSITION_NOTIFIEW);
}

static void wcd_da8xx_cpufweq_dewegistew(stwuct da8xx_fb_paw *paw)
{
	cpufweq_unwegistew_notifiew(&paw->fweq_twansition,
				    CPUFWEQ_TWANSITION_NOTIFIEW);
}
#endif

static void fb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet;

#ifdef CONFIG_CPU_FWEQ
	wcd_da8xx_cpufweq_dewegistew(paw);
#endif
	if (paw->wcd_suppwy) {
		wet = weguwatow_disabwe(paw->wcd_suppwy);
		if (wet)
			dev_wawn(&dev->dev, "Faiwed to disabwe weguwatow (%pe)\n",
				 EWW_PTW(wet));
	}

	wcd_disabwe_wastew(DA8XX_FWAME_WAIT);
	wcdc_wwite(0, WCD_WASTEW_CTWW_WEG);

	/* disabwe DMA  */
	wcdc_wwite(0, WCD_DMA_CTWW_WEG);

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);
	pm_wuntime_put_sync(&dev->dev);
	pm_wuntime_disabwe(&dev->dev);
	fwamebuffew_wewease(info);
}

/*
 * Function to wait fow vewticaw sync which fow this WCD pewiphewaw
 * twanswates into waiting fow the cuwwent wastew fwame to compwete.
 */
static int fb_wait_fow_vsync(stwuct fb_info *info)
{
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet;

	/*
	 * Set fwag to 0 and wait fow isw to set to 1. It wouwd seem thewe is a
	 * wace condition hewe whewe the ISW couwd have occuwwed just befowe ow
	 * just aftew this set. But since we awe just coawsewy waiting fow
	 * a fwame to compwete then that's OK. i.e. if the fwame compweted
	 * just befowe this code executed then we have to wait anothew fuww
	 * fwame time but thewe is no way to avoid such a situation. On the
	 * othew hand if the fwame compweted just aftew then we don't need
	 * to wait wong at aww. Eithew way we awe guawanteed to wetuwn to the
	 * usew immediatewy aftew a fwame compwetion which is aww that is
	 * wequiwed.
	 */
	paw->vsync_fwag = 0;
	wet = wait_event_intewwuptibwe_timeout(paw->vsync_wait,
					       paw->vsync_fwag != 0,
					       paw->vsync_timeout);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int fb_ioctw(stwuct fb_info *info, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct wcd_sync_awg sync_awg;

	switch (cmd) {
	case FBIOGET_CONTWAST:
	case FBIOPUT_CONTWAST:
	case FBIGET_BWIGHTNESS:
	case FBIPUT_BWIGHTNESS:
	case FBIGET_COWOW:
	case FBIPUT_COWOW:
		wetuwn -ENOTTY;
	case FBIPUT_HSYNC:
		if (copy_fwom_usew(&sync_awg, (chaw *)awg,
				sizeof(stwuct wcd_sync_awg)))
			wetuwn -EFAUWT;
		wcd_cfg_howizontaw_sync(sync_awg.back_powch,
					sync_awg.puwse_width,
					sync_awg.fwont_powch);
		bweak;
	case FBIPUT_VSYNC:
		if (copy_fwom_usew(&sync_awg, (chaw *)awg,
				sizeof(stwuct wcd_sync_awg)))
			wetuwn -EFAUWT;
		wcd_cfg_vewticaw_sync(sync_awg.back_powch,
					sync_awg.puwse_width,
					sync_awg.fwont_powch);
		bweak;
	case FBIO_WAITFOWVSYNC:
		wetuwn fb_wait_fow_vsync(info);
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cfb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet = 0;

	if (paw->bwank == bwank)
		wetuwn 0;

	paw->bwank = bwank;
	switch (bwank) {
	case FB_BWANK_UNBWANK:
		wcd_enabwe_wastew();

		if (paw->wcd_suppwy) {
			wet = weguwatow_enabwe(paw->wcd_suppwy);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case FB_BWANK_NOWMAW:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		if (paw->wcd_suppwy) {
			wet = weguwatow_disabwe(paw->wcd_suppwy);
			if (wet)
				wetuwn wet;
		}

		wcd_disabwe_wastew(DA8XX_FWAME_WAIT);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * Set new x,y offsets in the viwtuaw dispway fow the visibwe awea and switch
 * to the new mode.
 */
static int da8xx_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *fbi)
{
	int wet = 0;
	stwuct fb_vaw_scweeninfo new_vaw;
	stwuct da8xx_fb_paw         *paw = fbi->paw;
	stwuct fb_fix_scweeninfo    *fix = &fbi->fix;
	unsigned int end;
	unsigned int stawt;
	unsigned wong iwq_fwags;

	if (vaw->xoffset != fbi->vaw.xoffset ||
			vaw->yoffset != fbi->vaw.yoffset) {
		memcpy(&new_vaw, &fbi->vaw, sizeof(new_vaw));
		new_vaw.xoffset = vaw->xoffset;
		new_vaw.yoffset = vaw->yoffset;
		if (fb_check_vaw(&new_vaw, fbi))
			wet = -EINVAW;
		ewse {
			memcpy(&fbi->vaw, &new_vaw, sizeof(new_vaw));

			stawt	= fix->smem_stawt +
				new_vaw.yoffset * fix->wine_wength +
				new_vaw.xoffset * fbi->vaw.bits_pew_pixew / 8;
			end	= stawt + fbi->vaw.ywes * fix->wine_wength - 1;
			paw->dma_stawt	= stawt;
			paw->dma_end	= end;
			spin_wock_iwqsave(&paw->wock_fow_chan_update,
					iwq_fwags);
			if (paw->which_dma_channew_done == 0) {
				wcdc_wwite(paw->dma_stawt,
					   WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
				wcdc_wwite(paw->dma_end,
					   WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
			} ewse if (paw->which_dma_channew_done == 1) {
				wcdc_wwite(paw->dma_stawt,
					   WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
				wcdc_wwite(paw->dma_end,
					   WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
			}
			spin_unwock_iwqwestowe(&paw->wock_fow_chan_update,
					iwq_fwags);
		}
	}

	wetuwn wet;
}

static int da8xxfb_set_paw(stwuct fb_info *info)
{
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet;
	boow wastew = da8xx_fb_is_wastew_enabwed();

	if (wastew)
		wcd_disabwe_wastew(DA8XX_FWAME_WAIT);

	fb_vaw_to_videomode(&paw->mode, &info->vaw);

	paw->cfg.bpp = info->vaw.bits_pew_pixew;

	info->fix.visuaw = (paw->cfg.bpp <= 8) ?
				FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;
	info->fix.wine_wength = (paw->mode.xwes * paw->cfg.bpp) / 8;

	wet = wcd_init(paw, &paw->cfg, &paw->mode);
	if (wet < 0) {
		dev_eww(paw->dev, "wcd init faiwed\n");
		wetuwn wet;
	}

	paw->dma_stawt = info->fix.smem_stawt +
			 info->vaw.yoffset * info->fix.wine_wength +
			 info->vaw.xoffset * info->vaw.bits_pew_pixew / 8;
	paw->dma_end   = paw->dma_stawt +
			 info->vaw.ywes * info->fix.wine_wength - 1;

	wcdc_wwite(paw->dma_stawt, WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
	wcdc_wwite(paw->dma_end, WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
	wcdc_wwite(paw->dma_stawt, WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
	wcdc_wwite(paw->dma_end, WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);

	if (wastew)
		wcd_enabwe_wastew();

	wetuwn 0;
}

static const stwuct fb_ops da8xx_fb_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw = fb_check_vaw,
	.fb_set_paw = da8xxfb_set_paw,
	.fb_setcowweg = fb_setcowweg,
	.fb_pan_dispway = da8xx_pan_dispway,
	.fb_ioctw = fb_ioctw,
	.fb_bwank = cfb_bwank,
};

static stwuct fb_videomode *da8xx_fb_get_videomode(stwuct pwatfowm_device *dev)
{
	stwuct da8xx_wcdc_pwatfowm_data *fb_pdata = dev_get_pwatdata(&dev->dev);
	stwuct fb_videomode *wcdc_info;
	int i;

	fow (i = 0, wcdc_info = known_wcd_panews;
		i < AWWAY_SIZE(known_wcd_panews); i++, wcdc_info++) {
		if (stwcmp(fb_pdata->type, wcdc_info->name) == 0)
			bweak;
	}

	if (i == AWWAY_SIZE(known_wcd_panews)) {
		dev_eww(&dev->dev, "no panew found\n");
		wetuwn NUWW;
	}
	dev_info(&dev->dev, "found %s panew\n", wcdc_info->name);

	wetuwn wcdc_info;
}

static int fb_pwobe(stwuct pwatfowm_device *device)
{
	stwuct da8xx_wcdc_pwatfowm_data *fb_pdata =
						dev_get_pwatdata(&device->dev);
	stwuct wcd_ctww_config *wcd_cfg;
	stwuct fb_videomode *wcdc_info;
	stwuct fb_info *da8xx_fb_info;
	stwuct da8xx_fb_paw *paw;
	stwuct cwk *tmp_wcdc_cwk;
	int wet;
	unsigned wong uwcm;

	if (fb_pdata == NUWW) {
		dev_eww(&device->dev, "Can not get pwatfowm data\n");
		wetuwn -ENOENT;
	}

	wcdc_info = da8xx_fb_get_videomode(device);
	if (wcdc_info == NUWW)
		wetuwn -ENODEV;

	da8xx_fb_weg_base = devm_pwatfowm_iowemap_wesouwce(device, 0);
	if (IS_EWW(da8xx_fb_weg_base))
		wetuwn PTW_EWW(da8xx_fb_weg_base);

	tmp_wcdc_cwk = devm_cwk_get(&device->dev, "fck");
	if (IS_EWW(tmp_wcdc_cwk))
		wetuwn dev_eww_pwobe(&device->dev, PTW_EWW(tmp_wcdc_cwk),
				     "Can not get device cwock\n");

	pm_wuntime_enabwe(&device->dev);
	pm_wuntime_get_sync(&device->dev);

	/* Detewmine WCD IP Vewsion */
	switch (wcdc_wead(WCD_PID_WEG)) {
	case 0x4C100102:
		wcd_wevision = WCD_VEWSION_1;
		bweak;
	case 0x4F200800:
	case 0x4F201000:
		wcd_wevision = WCD_VEWSION_2;
		bweak;
	defauwt:
		dev_wawn(&device->dev, "Unknown PID Weg vawue 0x%x, "
				"defauwting to WCD wevision 1\n",
				wcdc_wead(WCD_PID_WEG));
		wcd_wevision = WCD_VEWSION_1;
		bweak;
	}

	wcd_cfg = (stwuct wcd_ctww_config *)fb_pdata->contwowwew_data;

	if (!wcd_cfg) {
		wet = -EINVAW;
		goto eww_pm_wuntime_disabwe;
	}

	da8xx_fb_info = fwamebuffew_awwoc(sizeof(stwuct da8xx_fb_paw),
					&device->dev);
	if (!da8xx_fb_info) {
		wet = -ENOMEM;
		goto eww_pm_wuntime_disabwe;
	}

	paw = da8xx_fb_info->paw;
	paw->dev = &device->dev;
	paw->wcdc_cwk = tmp_wcdc_cwk;
	paw->wcdc_cwk_wate = cwk_get_wate(paw->wcdc_cwk);

	paw->wcd_suppwy = devm_weguwatow_get_optionaw(&device->dev, "wcd");
	if (IS_EWW(paw->wcd_suppwy)) {
		if (PTW_EWW(paw->wcd_suppwy) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_wewease_fb;
		}

		paw->wcd_suppwy = NUWW;
	} ewse {
		wet = weguwatow_enabwe(paw->wcd_suppwy);
		if (wet)
			goto eww_wewease_fb;
	}

	fb_videomode_to_vaw(&da8xx_fb_vaw, wcdc_info);
	paw->cfg = *wcd_cfg;

	da8xx_fb_wcd_weset();

	/* awwocate fwame buffew */
	paw->vwam_size = wcdc_info->xwes * wcdc_info->ywes * wcd_cfg->bpp;
	uwcm = wcm((wcdc_info->xwes * wcd_cfg->bpp)/8, PAGE_SIZE);
	paw->vwam_size = woundup(paw->vwam_size/8, uwcm);
	paw->vwam_size = paw->vwam_size * WCD_NUM_BUFFEWS;

	paw->vwam_viwt = dmam_awwoc_cohewent(paw->dev,
					     paw->vwam_size,
					     &paw->vwam_phys,
					     GFP_KEWNEW | GFP_DMA);
	if (!paw->vwam_viwt) {
		dev_eww(&device->dev,
			"GWCD: kmawwoc fow fwame buffew faiwed\n");
		wet = -EINVAW;
		goto eww_disabwe_weg;
	}

	da8xx_fb_info->scween_base = (chaw __iomem *) paw->vwam_viwt;
	da8xx_fb_fix.smem_stawt    = paw->vwam_phys;
	da8xx_fb_fix.smem_wen      = paw->vwam_size;
	da8xx_fb_fix.wine_wength   = (wcdc_info->xwes * wcd_cfg->bpp) / 8;

	paw->dma_stawt = paw->vwam_phys;
	paw->dma_end   = paw->dma_stawt + wcdc_info->ywes *
		da8xx_fb_fix.wine_wength - 1;

	/* awwocate pawette buffew */
	paw->v_pawette_base = dmam_awwoc_cohewent(paw->dev, PAWETTE_SIZE,
						  &paw->p_pawette_base,
						  GFP_KEWNEW | GFP_DMA);
	if (!paw->v_pawette_base) {
		dev_eww(&device->dev,
			"GWCD: kmawwoc fow pawette buffew faiwed\n");
		wet = -EINVAW;
		goto eww_wewease_fb;
	}

	paw->iwq = pwatfowm_get_iwq(device, 0);
	if (paw->iwq < 0) {
		wet = -ENOENT;
		goto eww_wewease_fb;
	}

	da8xx_fb_vaw.gwayscawe =
	    wcd_cfg->panew_shade == MONOCHWOME ? 1 : 0;
	da8xx_fb_vaw.bits_pew_pixew = wcd_cfg->bpp;

	/* Initiawize fbinfo */
	da8xx_fb_info->fix = da8xx_fb_fix;
	da8xx_fb_info->vaw = da8xx_fb_vaw;
	da8xx_fb_info->fbops = &da8xx_fb_ops;
	da8xx_fb_info->pseudo_pawette = paw->pseudo_pawette;
	da8xx_fb_info->fix.visuaw = (da8xx_fb_info->vaw.bits_pew_pixew <= 8) ?
				FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;

	wet = fb_awwoc_cmap(&da8xx_fb_info->cmap, PAWETTE_SIZE, 0);
	if (wet)
		goto eww_disabwe_weg;
	da8xx_fb_info->cmap.wen = paw->pawette_sz;

	/* initiawize vaw_scweeninfo */
	da8xx_fb_vaw.activate = FB_ACTIVATE_FOWCE;
	fb_set_vaw(da8xx_fb_info, &da8xx_fb_vaw);

	pwatfowm_set_dwvdata(device, da8xx_fb_info);

	/* initiawize the vsync wait queue */
	init_waitqueue_head(&paw->vsync_wait);
	paw->vsync_timeout = HZ / 5;
	paw->which_dma_channew_done = -1;
	spin_wock_init(&paw->wock_fow_chan_update);

	/* Wegistew the Fwame Buffew  */
	if (wegistew_fwamebuffew(da8xx_fb_info) < 0) {
		dev_eww(&device->dev,
			"GWCD: Fwame Buffew Wegistwation Faiwed!\n");
		wet = -EINVAW;
		goto eww_deawwoc_cmap;
	}

#ifdef CONFIG_CPU_FWEQ
	wet = wcd_da8xx_cpufweq_wegistew(paw);
	if (wet) {
		dev_eww(&device->dev, "faiwed to wegistew cpufweq\n");
		goto eww_cpu_fweq;
	}
#endif

	if (wcd_wevision == WCD_VEWSION_1)
		wcdc_iwq_handwew = wcdc_iwq_handwew_wev01;
	ewse {
		init_waitqueue_head(&fwame_done_wq);
		wcdc_iwq_handwew = wcdc_iwq_handwew_wev02;
	}

	wet = devm_wequest_iwq(&device->dev, paw->iwq, wcdc_iwq_handwew, 0,
			       DWIVEW_NAME, paw);
	if (wet)
		goto iwq_fweq;
	wetuwn 0;

iwq_fweq:
#ifdef CONFIG_CPU_FWEQ
	wcd_da8xx_cpufweq_dewegistew(paw);
eww_cpu_fweq:
#endif
	unwegistew_fwamebuffew(da8xx_fb_info);

eww_deawwoc_cmap:
	fb_deawwoc_cmap(&da8xx_fb_info->cmap);

eww_disabwe_weg:
	if (paw->wcd_suppwy)
		weguwatow_disabwe(paw->wcd_suppwy);
eww_wewease_fb:
	fwamebuffew_wewease(da8xx_fb_info);

eww_pm_wuntime_disabwe:
	pm_wuntime_put_sync(&device->dev);
	pm_wuntime_disabwe(&device->dev);

	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static stwuct wcdc_context {
	u32 cwk_enabwe;
	u32 ctww;
	u32 dma_ctww;
	u32 wastew_timing_0;
	u32 wastew_timing_1;
	u32 wastew_timing_2;
	u32 int_enabwe_set;
	u32 dma_fwm_buf_base_addw_0;
	u32 dma_fwm_buf_ceiwing_addw_0;
	u32 dma_fwm_buf_base_addw_1;
	u32 dma_fwm_buf_ceiwing_addw_1;
	u32 wastew_ctww;
} weg_context;

static void wcd_context_save(void)
{
	if (wcd_wevision == WCD_VEWSION_2) {
		weg_context.cwk_enabwe = wcdc_wead(WCD_CWK_ENABWE_WEG);
		weg_context.int_enabwe_set = wcdc_wead(WCD_INT_ENABWE_SET_WEG);
	}

	weg_context.ctww = wcdc_wead(WCD_CTWW_WEG);
	weg_context.dma_ctww = wcdc_wead(WCD_DMA_CTWW_WEG);
	weg_context.wastew_timing_0 = wcdc_wead(WCD_WASTEW_TIMING_0_WEG);
	weg_context.wastew_timing_1 = wcdc_wead(WCD_WASTEW_TIMING_1_WEG);
	weg_context.wastew_timing_2 = wcdc_wead(WCD_WASTEW_TIMING_2_WEG);
	weg_context.dma_fwm_buf_base_addw_0 =
		wcdc_wead(WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
	weg_context.dma_fwm_buf_ceiwing_addw_0 =
		wcdc_wead(WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
	weg_context.dma_fwm_buf_base_addw_1 =
		wcdc_wead(WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
	weg_context.dma_fwm_buf_ceiwing_addw_1 =
		wcdc_wead(WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
	weg_context.wastew_ctww = wcdc_wead(WCD_WASTEW_CTWW_WEG);
	wetuwn;
}

static void wcd_context_westowe(void)
{
	if (wcd_wevision == WCD_VEWSION_2) {
		wcdc_wwite(weg_context.cwk_enabwe, WCD_CWK_ENABWE_WEG);
		wcdc_wwite(weg_context.int_enabwe_set, WCD_INT_ENABWE_SET_WEG);
	}

	wcdc_wwite(weg_context.ctww, WCD_CTWW_WEG);
	wcdc_wwite(weg_context.dma_ctww, WCD_DMA_CTWW_WEG);
	wcdc_wwite(weg_context.wastew_timing_0, WCD_WASTEW_TIMING_0_WEG);
	wcdc_wwite(weg_context.wastew_timing_1, WCD_WASTEW_TIMING_1_WEG);
	wcdc_wwite(weg_context.wastew_timing_2, WCD_WASTEW_TIMING_2_WEG);
	wcdc_wwite(weg_context.dma_fwm_buf_base_addw_0,
			WCD_DMA_FWM_BUF_BASE_ADDW_0_WEG);
	wcdc_wwite(weg_context.dma_fwm_buf_ceiwing_addw_0,
			WCD_DMA_FWM_BUF_CEIWING_ADDW_0_WEG);
	wcdc_wwite(weg_context.dma_fwm_buf_base_addw_1,
			WCD_DMA_FWM_BUF_BASE_ADDW_1_WEG);
	wcdc_wwite(weg_context.dma_fwm_buf_ceiwing_addw_1,
			WCD_DMA_FWM_BUF_CEIWING_ADDW_1_WEG);
	wcdc_wwite(weg_context.wastew_ctww, WCD_WASTEW_CTWW_WEG);
	wetuwn;
}

static int fb_suspend(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet;

	consowe_wock();
	if (paw->wcd_suppwy) {
		wet = weguwatow_disabwe(paw->wcd_suppwy);
		if (wet)
			wetuwn wet;
	}

	fb_set_suspend(info, 1);
	wcd_disabwe_wastew(DA8XX_FWAME_WAIT);
	wcd_context_save();
	pm_wuntime_put_sync(dev);
	consowe_unwock();

	wetuwn 0;
}
static int fb_wesume(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct da8xx_fb_paw *paw = info->paw;
	int wet;

	consowe_wock();
	pm_wuntime_get_sync(dev);
	wcd_context_westowe();
	if (paw->bwank == FB_BWANK_UNBWANK) {
		wcd_enabwe_wastew();

		if (paw->wcd_suppwy) {
			wet = weguwatow_enabwe(paw->wcd_suppwy);
			if (wet)
				wetuwn wet;
		}
	}

	fb_set_suspend(info, 0);
	consowe_unwock();

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(fb_pm_ops, fb_suspend, fb_wesume);

static stwuct pwatfowm_dwivew da8xx_fb_dwivew = {
	.pwobe = fb_pwobe,
	.wemove_new = fb_wemove,
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .pm	= &fb_pm_ops,
		   },
};
moduwe_pwatfowm_dwivew(da8xx_fb_dwivew);

MODUWE_DESCWIPTION("Fwamebuffew dwivew fow TI da8xx/omap-w1xx");
MODUWE_AUTHOW("Texas Instwuments");
MODUWE_WICENSE("GPW");
