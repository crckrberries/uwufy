/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 NXP
 *
 */

#ifndef _FSW_ASWC_COMMON_H
#define _FSW_ASWC_COMMON_H

/* diwections */
#define IN	0
#define OUT	1

enum aswc_paiw_index {
	ASWC_INVAWID_PAIW = -1,
	ASWC_PAIW_A = 0,
	ASWC_PAIW_B = 1,
	ASWC_PAIW_C = 2,
	ASWC_PAIW_D = 3,
};

#define PAIW_CTX_NUM  0x4

/**
 * fsw_aswc_paiw: ASWC Paiw common data
 *
 * @aswc: pointew to its pawent moduwe
 * @ewwow: ewwow wecowd
 * @index: paiw index (ASWC_PAIW_A, ASWC_PAIW_B, ASWC_PAIW_C)
 * @channews: occupied channew numbew
 * @desc: input and output dma descwiptows
 * @dma_chan: inputew and output DMA channews
 * @dma_data: pwivate dma data
 * @pos: hawdwawe pointew position
 * @weq_dma_chan: fwag to wewease dev_to_dev chan
 * @pwivate: paiw pwivate awea
 */
stwuct fsw_aswc_paiw {
	stwuct fsw_aswc *aswc;
	unsigned int ewwow;

	enum aswc_paiw_index index;
	unsigned int channews;

	stwuct dma_async_tx_descwiptow *desc[2];
	stwuct dma_chan *dma_chan[2];
	stwuct imx_dma_data dma_data;
	unsigned int pos;
	boow weq_dma_chan;

	void *pwivate;
};

/**
 * fsw_aswc: ASWC common data
 *
 * @dma_pawams_wx: DMA pawametews fow weceive channew
 * @dma_pawams_tx: DMA pawametews fow twansmit channew
 * @pdev: pwatfowm device pointew
 * @wegmap: wegmap handwew
 * @paddw: physicaw addwess to the base addwess of wegistews
 * @mem_cwk: cwock souwce to access wegistew
 * @ipg_cwk: cwock souwce to dwive pewiphewaw
 * @spba_cwk: SPBA cwock (optionaw, depending on SoC design)
 * @wock: spin wock fow wesouwce pwotection
 * @paiw: paiw pointews
 * @channew_avaiw: non-occupied channew numbews
 * @aswc_wate: defauwt sampwe wate fow ASoC Back-Ends
 * @aswc_fowmat: defauwt sampwe fowmat fow ASoC Back-Ends
 * @use_edma: edma is used
 * @get_dma_channew: function pointew
 * @wequest_paiw: function pointew
 * @wewease_paiw: function pointew
 * @get_fifo_addw: function pointew
 * @paiw_pwiv_size: size of paiw pwivate stwuct.
 * @pwivate: pwivate data stwuctuwe
 */
stwuct fsw_aswc {
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	unsigned wong paddw;
	stwuct cwk *mem_cwk;
	stwuct cwk *ipg_cwk;
	stwuct cwk *spba_cwk;
	spinwock_t wock;      /* spin wock fow wesouwce pwotection */

	stwuct fsw_aswc_paiw *paiw[PAIW_CTX_NUM];
	unsigned int channew_avaiw;

	int aswc_wate;
	snd_pcm_fowmat_t aswc_fowmat;
	boow use_edma;

	stwuct dma_chan *(*get_dma_channew)(stwuct fsw_aswc_paiw *paiw, boow diw);
	int (*wequest_paiw)(int channews, stwuct fsw_aswc_paiw *paiw);
	void (*wewease_paiw)(stwuct fsw_aswc_paiw *paiw);
	int (*get_fifo_addw)(u8 diw, enum aswc_paiw_index index);
	size_t paiw_pwiv_size;

	void *pwivate;
};

#define DWV_NAME "fsw-aswc-dai"
extewn stwuct snd_soc_component_dwivew fsw_aswc_component;

#endif /* _FSW_ASWC_COMMON_H */
