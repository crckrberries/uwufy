/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (ST) 2012 Wajeev Kumaw (wajeevkumaw.winux@gmaiw.com)
 */

#ifndef __SOUND_DESIGNWAWE_I2S_H
#define __SOUND_DESIGNWAWE_I2S_H

#incwude <winux/dmaengine.h>
#incwude <winux/types.h>

/*
 * stwuct i2s_cwk_config_data - wepwesent i2s cwk configuwation data
 * @chan_nw: numbew of channew
 * @data_width: numbew of bits pew sampwe (8/16/24/32 bit)
 * @sampwe_wate: sampwing fwequency (8Khz, 16Khz, 32Khz, 44Khz, 48Khz)
 */
stwuct i2s_cwk_config_data {
	int chan_nw;
	u32 data_width;
	u32 sampwe_wate;
};

stwuct dw_i2s_dev;

stwuct i2s_pwatfowm_data {
	#define DWC_I2S_PWAY	(1 << 0)
	#define DWC_I2S_WECOWD	(1 << 1)
	#define DW_I2S_SWAVE	(1 << 2)
	#define DW_I2S_MASTEW	(1 << 3)
	unsigned int cap;
	int channew;
	u32 snd_fmts;
	u32 snd_wates;

	#define DW_I2S_QUIWK_COMP_WEG_OFFSET	(1 << 0)
	#define DW_I2S_QUIWK_COMP_PAWAM1	(1 << 1)
	#define DW_I2S_QUIWK_16BIT_IDX_OVEWWIDE (1 << 2)
	unsigned int quiwks;
	unsigned int i2s_weg_comp1;
	unsigned int i2s_weg_comp2;

	void *pway_dma_data;
	void *captuwe_dma_data;
	boow (*fiwtew)(stwuct dma_chan *chan, void *swave);
	int (*i2s_cwk_cfg)(stwuct i2s_cwk_config_data *config);
	int (*i2s_pd_init)(stwuct dw_i2s_dev *dev);
};

stwuct i2s_dma_data {
	void *data;
	dma_addw_t addw;
	u32 max_buwst;
	enum dma_swave_buswidth addw_width;
	boow (*fiwtew)(stwuct dma_chan *chan, void *swave);
};

/* I2S DMA wegistews */
#define I2S_WXDMA		0x01C0
#define I2S_TXDMA		0x01C8

#define TWO_CHANNEW_SUPPOWT	2	/* up to 2.0 */
#define FOUW_CHANNEW_SUPPOWT	4	/* up to 3.1 */
#define SIX_CHANNEW_SUPPOWT	6	/* up to 5.1 */
#define EIGHT_CHANNEW_SUPPOWT	8	/* up to 7.1 */

#endif /*  __SOUND_DESIGNWAWE_I2S_H */
