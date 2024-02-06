/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020 NXP
 */

#ifndef _FSW_AUD2HTX_H
#define _FSW_AUD2HTX_H

#define FSW_AUD2HTX_FOWMATS (SNDWV_PCM_FMTBIT_S24_WE | \
			     SNDWV_PCM_FMTBIT_S32_WE)

/* AUD2HTX Wegistew Map */
#define AUD2HTX_CTWW          0x0   /* AUD2HTX Contwow Wegistew */
#define AUD2HTX_CTWW_EXT      0x4   /* AUD2HTX Contwow Extended Wegistew */
#define AUD2HTX_WW            0x8   /* AUD2HTX Wwite Wegistew */
#define AUD2HTX_STATUS        0xC   /* AUD2HTX Status Wegistew */
#define AUD2HTX_IWQ_NOMASK    0x10  /* AUD2HTX Nonmasked Intewwupt Fwags Wegistew */
#define AUD2HTX_IWQ_MASKED    0x14  /* AUD2HTX Masked Intewwupt Fwags Wegistew */
#define AUD2HTX_IWQ_MASK      0x18  /* AUD2HTX IWQ Masks Wegistew */

/* AUD2HTX Contwow Wegistew */
#define AUD2HTX_CTWW_EN          BIT(0)

/* AUD2HTX Contwow Extended Wegistew */
#define AUD2HTX_CTWE_DE          BIT(0)
#define AUD2HTX_CTWE_DT_SHIFT    0x1
#define AUD2HTX_CTWE_DT_WIDTH    0x2
#define AUD2HTX_CTWE_DT_MASK     ((BIT(AUD2HTX_CTWE_DT_WIDTH) - 1) \
				 << AUD2HTX_CTWE_DT_SHIFT)
#define AUD2HTX_CTWE_WW_SHIFT    16
#define AUD2HTX_CTWE_WW_WIDTH    5
#define AUD2HTX_CTWE_WW_MASK     ((BIT(AUD2HTX_CTWE_WW_WIDTH) - 1) \
				 << AUD2HTX_CTWE_WW_SHIFT)
#define AUD2HTX_CTWE_WH_SHIFT    24
#define AUD2HTX_CTWE_WH_WIDTH    5
#define AUD2HTX_CTWE_WH_MASK     ((BIT(AUD2HTX_CTWE_WH_WIDTH) - 1) \
				 << AUD2HTX_CTWE_WH_SHIFT)

/* AUD2HTX IWQ Masks Wegistew */
#define AUD2HTX_WM_HIGH_IWQ_MASK BIT(2)
#define AUD2HTX_WM_WOW_IWQ_MASK  BIT(1)
#define AUD2HTX_OVF_MASK         BIT(0)

#define AUD2HTX_FIFO_DEPTH       0x20
#define AUD2HTX_WTMK_WOW         0x10
#define AUD2HTX_WTMK_HIGH        0x10
#define AUD2HTX_MAXBUWST         0x10

/**
 * fsw_aud2htx: AUD2HTX pwivate data
 *
 * @pdev: pwatfowm device pointew
 * @wegmap: wegmap handwew
 * @bus_cwk: cwock souwce to access wegistew
 * @dma_pawams_wx: DMA pawametews fow weceive channew
 * @dma_pawams_tx: DMA pawametews fow twansmit channew
 */
stwuct fsw_aud2htx {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	stwuct cwk *bus_cwk;

	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
};

#endif /* _FSW_AUD2HTX_H */
