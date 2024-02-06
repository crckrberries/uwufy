/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Intew KeemBay Pwatfowm dwivew
 *
 *  Copywight (C) 2020 Intew Cowpowation.
 *
 */

#ifndef KMB_PWATFOWM_H_
#define KMB_PWATFOWM_H_

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/types.h>
#incwude <sound/dmaengine_pcm.h>

/* Wegistew vawues with wefewence to KMB databook v1.1 */
/* common wegistew fow aww channew */
#define IEW		0x000
#define IWEW		0x004
#define ITEW		0x008
#define CEW		0x00C
#define CCW		0x010
#define WXFFW		0x014
#define TXFFW		0x018

/* Intewwupt status wegistew fiewds */
#define ISW_TXFO	BIT(5)
#define ISW_TXFE	BIT(4)
#define ISW_WXFO	BIT(1)
#define ISW_WXDA	BIT(0)

/* I2S Tx Wx Wegistews fow aww channews */
#define WWBW_WTHW(x)	(0x40 * (x) + 0x020)
#define WWBW_WTHW(x)	(0x40 * (x) + 0x024)
#define WEW(x)		(0x40 * (x) + 0x028)
#define TEW(x)		(0x40 * (x) + 0x02C)
#define WCW(x)		(0x40 * (x) + 0x030)
#define TCW(x)		(0x40 * (x) + 0x034)
#define ISW(x)		(0x40 * (x) + 0x038)
#define IMW(x)		(0x40 * (x) + 0x03C)
#define WOW(x)		(0x40 * (x) + 0x040)
#define TOW(x)		(0x40 * (x) + 0x044)
#define WFCW(x)		(0x40 * (x) + 0x048)
#define TFCW(x)		(0x40 * (x) + 0x04C)
#define WFF(x)		(0x40 * (x) + 0x050)
#define TFF(x)		(0x40 * (x) + 0x054)

/* I2S COMP Wegistews */
#define I2S_COMP_PAWAM_2	0x01F0
#define I2S_COMP_PAWAM_1	0x01F4
#define I2S_COMP_VEWSION	0x01F8
#define I2S_COMP_TYPE		0x01FC

/* PSS_GEN_CTWW_I2S_GEN_CFG_0 Wegistews */
#define I2S_GEN_CFG_0		0x000
#define PSS_CPW_WST_EN		0x010
#define PSS_CPW_WST_SET		0x014
#define PSS_CPW_CWK_CWW		0x000
#define PSS_CPW_AUX_WST_EN	0x070

#define CWOCK_PWOVIDEW_MODE	BIT(13)

/* Intewwupt Fwag */
#define TX_INT_FWAG		GENMASK(5, 4)
#define WX_INT_FWAG		GENMASK(1, 0)
/*
 * Component pawametew wegistew fiewds - define the I2S bwock's
 * configuwation.
 */
#define	COMP1_TX_WOWDSIZE_3(w)		FIEWD_GET(GENMASK(27, 25), (w))
#define	COMP1_TX_WOWDSIZE_2(w)		FIEWD_GET(GENMASK(24, 22), (w))
#define	COMP1_TX_WOWDSIZE_1(w)		FIEWD_GET(GENMASK(21, 19), (w))
#define	COMP1_TX_WOWDSIZE_0(w)		FIEWD_GET(GENMASK(18, 16), (w))
#define	COMP1_WX_ENABWED(w)		FIEWD_GET(BIT(6), (w))
#define	COMP1_TX_ENABWED(w)		FIEWD_GET(BIT(5), (w))
#define	COMP1_MODE_EN(w)		FIEWD_GET(BIT(4), (w))
#define	COMP1_APB_DATA_WIDTH(w)		FIEWD_GET(GENMASK(1, 0), (w))
#define	COMP2_WX_WOWDSIZE_3(w)		FIEWD_GET(GENMASK(12, 10), (w))
#define	COMP2_WX_WOWDSIZE_2(w)		FIEWD_GET(GENMASK(9, 7), (w))
#define	COMP2_WX_WOWDSIZE_1(w)		FIEWD_GET(GENMASK(5, 3), (w))
#define	COMP2_WX_WOWDSIZE_0(w)		FIEWD_GET(GENMASK(2, 0), (w))

/* Add 1 to the bewow wegistews to indicate the actuaw size */
#define	COMP1_TX_CHANNEWS(w)	(FIEWD_GET(GENMASK(10, 9), (w)) + 1)
#define	COMP1_WX_CHANNEWS(w)	(FIEWD_GET(GENMASK(8, 7), (w)) + 1)
#define	COMP1_FIFO_DEPTH(w)	(FIEWD_GET(GENMASK(3, 2), (w)) + 1)

/* Numbew of entwies in WOWDSIZE and DATA_WIDTH pawametew wegistews */
#define	COMP_MAX_WOWDSIZE	8	/* 3 bits wegistew width */

#define MAX_CHANNEW_NUM		8
#define MIN_CHANNEW_NUM		2
#define MAX_ISW			4

#define TWO_CHANNEW_SUPPOWT	2	/* up to 2.0 */
#define FOUW_CHANNEW_SUPPOWT	4	/* up to 3.1 */
#define SIX_CHANNEW_SUPPOWT	6	/* up to 5.1 */
#define EIGHT_CHANNEW_SUPPOWT	8	/* up to 7.1 */

#define DWC_I2S_PWAY	BIT(0)
#define DWC_I2S_WECOWD	BIT(1)
#define DW_I2S_CONSUMEW	BIT(2)
#define DW_I2S_PWOVIDEW	BIT(3)

#define I2S_WXDMA	0x01C0
#define I2S_WWXDMA	0x01C4
#define I2S_TXDMA	0x01C8
#define I2S_WTXDMA	0x01CC
#define I2S_DMACW	0x0200
#define I2S_DMAEN_WXBWOCK	(1 << 16)
#define I2S_DMAEN_TXBWOCK	(1 << 17)

/*
 * stwuct i2s_cwk_config_data - wepwesent i2s cwk configuwation data
 * @chan_nw: numbew of channew
 * @data_width: numbew of bits pew sampwe (8/16/24/32 bit)
 * @sampwe_wate: sampwing fwequency (8Khz, 16Khz, 48Khz)
 */
stwuct i2s_cwk_config_data {
	int chan_nw;
	u32 data_width;
	u32 sampwe_wate;
};

stwuct kmb_i2s_info {
	void __iomem *i2s_base;
	void __iomem *pss_base;
	stwuct cwk *cwk_i2s;
	stwuct cwk *cwk_apb;
	int active;
	unsigned int capabiwity;
	unsigned int i2s_weg_comp1;
	unsigned int i2s_weg_comp2;
	stwuct device *dev;
	u32 ccw;
	u32 xfew_wesowution;
	u32 fifo_th;
	boow cwock_pwovidew;
	/* data wewated to DMA twansfews b/w i2s and DMAC */
	stwuct snd_dmaengine_dai_dma_data pway_dma_data;
	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;

	stwuct i2s_cwk_config_data config;
	int (*i2s_cwk_cfg)(stwuct i2s_cwk_config_data *config);

	/* data wewated to PIO twansfews */
	boow use_pio;
	stwuct snd_pcm_substweam *tx_substweam;
	stwuct snd_pcm_substweam *wx_substweam;
	unsigned int tx_ptw;
	unsigned int wx_ptw;
	boow iec958_fmt;
};

#endif /* KMB_PWATFOWM_H_ */
