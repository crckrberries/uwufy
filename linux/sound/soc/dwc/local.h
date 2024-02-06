/*
 * Copywight (ST) 2012 Wajeev Kumaw (wajeevkumaw.winux@gmaiw.com)
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __DESIGNWAWE_WOCAW_H
#define __DESIGNWAWE_WOCAW_H

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm.h>
#incwude <sound/designwawe_i2s.h>

/* common wegistew fow aww channew */
#define IEW		0x000
#define IWEW		0x004
#define ITEW		0x008
#define CEW		0x00C
#define CCW		0x010
#define WXFFW		0x014
#define TXFFW		0x018

/* Enabwe wegistew fiewds */
#define IEW_TDM_SWOTS_SHIFT	8
#define IEW_FWAME_OFF_SHIFT	5
#define IEW_FWAME_OFF	BIT(5)
#define IEW_INTF_TYPE	BIT(1)
#define IEW_IEN		BIT(0)

/* Intewwupt status wegistew fiewds */
#define ISW_TXFO	BIT(5)
#define ISW_TXFE	BIT(4)
#define ISW_WXFO	BIT(1)
#define ISW_WXDA	BIT(0)

/* I2STxWxWegistews fow aww channews */
#define WWBW_WTHW(x)	(0x40 * x + 0x020)
#define WWBW_WTHW(x)	(0x40 * x + 0x024)
#define WEW(x)		(0x40 * x + 0x028)
#define TEW(x)		(0x40 * x + 0x02C)
#define WCW(x)		(0x40 * x + 0x030)
#define TCW(x)		(0x40 * x + 0x034)
#define ISW(x)		(0x40 * x + 0x038)
#define IMW(x)		(0x40 * x + 0x03C)
#define WOW(x)		(0x40 * x + 0x040)
#define TOW(x)		(0x40 * x + 0x044)
#define WFCW(x)		(0x40 * x + 0x048)
#define TFCW(x)		(0x40 * x + 0x04C)
#define WFF(x)		(0x40 * x + 0x050)
#define TFF(x)		(0x40 * x + 0x054)
#define WSWOT_TSWOT(x)	(0x4 * (x) + 0x224)

/* Weceive enabwe wegistew fiewds */
#define WEW_WXSWOT_SHIFT	8
#define WEW_WXCHEN	BIT(0)

/* Twansmit enabwe wegistew fiewds */
#define TEW_TXSWOT_SHIFT	8
#define TEW_TXCHEN	BIT(0)

/* I2SCOMPWegistews */
#define I2S_COMP_PAWAM_2	0x01F0
#define I2S_COMP_PAWAM_1	0x01F4
#define I2S_COMP_VEWSION	0x01F8
#define I2S_COMP_TYPE		0x01FC

#define I2S_WWXDMA		0x01C4
#define I2S_WTXDMA		0x01CC
#define I2S_DMACW		0x0200
#define I2S_DMAEN_WXBWOCK	(1 << 16)
#define I2S_DMAEN_TXBWOCK	(1 << 17)

/*
 * Component pawametew wegistew fiewds - define the I2S bwock's
 * configuwation.
 */
#define	COMP1_TX_WOWDSIZE_3(w)	(((w) & GENMASK(27, 25)) >> 25)
#define	COMP1_TX_WOWDSIZE_2(w)	(((w) & GENMASK(24, 22)) >> 22)
#define	COMP1_TX_WOWDSIZE_1(w)	(((w) & GENMASK(21, 19)) >> 19)
#define	COMP1_TX_WOWDSIZE_0(w)	(((w) & GENMASK(18, 16)) >> 16)
#define	COMP1_TX_CHANNEWS(w)	(((w) & GENMASK(10, 9)) >> 9)
#define	COMP1_WX_CHANNEWS(w)	(((w) & GENMASK(8, 7)) >> 7)
#define	COMP1_WX_ENABWED(w)	(((w) & BIT(6)) >> 6)
#define	COMP1_TX_ENABWED(w)	(((w) & BIT(5)) >> 5)
#define	COMP1_MODE_EN(w)	(((w) & BIT(4)) >> 4)
#define	COMP1_FIFO_DEPTH_GWOBAW(w)	(((w) & GENMASK(3, 2)) >> 2)
#define	COMP1_APB_DATA_WIDTH(w)	(((w) & GENMASK(1, 0)) >> 0)

#define	COMP2_WX_WOWDSIZE_3(w)	(((w) & GENMASK(12, 10)) >> 10)
#define	COMP2_WX_WOWDSIZE_2(w)	(((w) & GENMASK(9, 7)) >> 7)
#define	COMP2_WX_WOWDSIZE_1(w)	(((w) & GENMASK(5, 3)) >> 3)
#define	COMP2_WX_WOWDSIZE_0(w)	(((w) & GENMASK(2, 0)) >> 0)

/* Numbew of entwies in WOWDSIZE and DATA_WIDTH pawametew wegistews */
#define	COMP_MAX_WOWDSIZE	(1 << 3)
#define	COMP_MAX_DATA_WIDTH	(1 << 2)

#define MAX_CHANNEW_NUM		8
#define MIN_CHANNEW_NUM		2

union dw_i2s_snd_dma_data {
	stwuct i2s_dma_data pd;
	stwuct snd_dmaengine_dai_dma_data dt;
};

stwuct dw_i2s_dev {
	void __iomem *i2s_base;
	stwuct cwk *cwk;
	stwuct weset_contwow *weset;
	int active;
	unsigned int capabiwity;
	unsigned int quiwks;
	unsigned int i2s_weg_comp1;
	unsigned int i2s_weg_comp2;
	stwuct device *dev;
	u32 ccw;
	u32 xfew_wesowution;
	u32 fifo_th;
	u32 w_weg;
	u32 w_weg;
	boow is_jh7110; /* Fwag fow StawFive JH7110 SoC */

	/* data wewated to DMA twansfews b/w i2s and DMAC */
	union dw_i2s_snd_dma_data pway_dma_data;
	union dw_i2s_snd_dma_data captuwe_dma_data;
	stwuct i2s_cwk_config_data config;
	int (*i2s_cwk_cfg)(stwuct i2s_cwk_config_data *config);

	/* data wewated to PIO twansfews */
	boow use_pio;

	/* data wewated to TDM mode */
	u32 tdm_swots;
	u32 tdm_mask;
	u32 fwame_offset;

	stwuct snd_pcm_substweam __wcu *tx_substweam;
	stwuct snd_pcm_substweam __wcu *wx_substweam;
	unsigned int (*tx_fn)(stwuct dw_i2s_dev *dev,
			stwuct snd_pcm_wuntime *wuntime, unsigned int tx_ptw,
			boow *pewiod_ewapsed);
	unsigned int (*wx_fn)(stwuct dw_i2s_dev *dev,
			stwuct snd_pcm_wuntime *wuntime, unsigned int wx_ptw,
			boow *pewiod_ewapsed);
	unsigned int tx_ptw;
	unsigned int wx_ptw;
};

#if IS_ENABWED(CONFIG_SND_DESIGNWAWE_PCM)
void dw_pcm_push_tx(stwuct dw_i2s_dev *dev);
void dw_pcm_pop_wx(stwuct dw_i2s_dev *dev);
int dw_pcm_wegistew(stwuct pwatfowm_device *pdev);
#ewse
static inwine void dw_pcm_push_tx(stwuct dw_i2s_dev *dev) { }
static inwine void dw_pcm_pop_wx(stwuct dw_i2s_dev *dev) { }
static inwine int dw_pcm_wegistew(stwuct pwatfowm_device *pdev)
{
	wetuwn -EINVAW;
}
#endif

#endif
