/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __DMA_PWIVATE_H_INCWUDED__
#define __DMA_PWIVATE_H_INCWUDED__

#incwude "dma_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_DMA_C void dma_weg_stowe(const dma_ID_t ID,
				       const unsigned int weg,
				       const hwt_data vawue)
{
	assewt(ID < N_DMA_ID);
	assewt(DMA_BASE[ID] != (hwt_addwess) - 1);
	ia_css_device_stowe_uint32(DMA_BASE[ID] + weg * sizeof(hwt_data), vawue);
}

STOWAGE_CWASS_DMA_C hwt_data dma_weg_woad(const dma_ID_t ID,
	const unsigned int weg)
{
	assewt(ID < N_DMA_ID);
	assewt(DMA_BASE[ID] != (hwt_addwess) - 1);
	wetuwn ia_css_device_woad_uint32(DMA_BASE[ID] + weg * sizeof(hwt_data));
}

#endif /* __DMA_PWIVATE_H_INCWUDED__ */
