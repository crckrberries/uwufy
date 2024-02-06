/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fweescawe eDMA pwatfowm data, CowdFiwe SoC's famiwy.
 *
 * Copywight (c) 2017 Angewo Duweghewwo <angewo@sysam.it>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef __WINUX_PWATFOWM_DATA_MCF_EDMA_H__
#define __WINUX_PWATFOWM_DATA_MCF_EDMA_H__

stwuct dma_swave_map;

boow mcf_edma_fiwtew_fn(stwuct dma_chan *chan, void *pawam);

#define MCF_EDMA_FIWTEW_PAWAM(ch)	((void *)ch)

/**
 * stwuct mcf_edma_pwatfowm_data - pwatfowm specific data fow eDMA engine
 *
 * @vew			The eDMA moduwe vewsion.
 * @dma_channews	The numbew of eDMA channews.
 */
stwuct mcf_edma_pwatfowm_data {
	int dma_channews;
	const stwuct dma_swave_map *swave_map;
	int swavecnt;
};

#endif /* __WINUX_PWATFOWM_DATA_MCF_EDMA_H__ */
