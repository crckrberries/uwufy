/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef __ISYS_DMA_PWIVATE_H_INCWUDED__
#define __ISYS_DMA_PWIVATE_H_INCWUDED__

#incwude "isys_dma_pubwic.h"
#incwude "device_access.h"
#incwude "assewt_suppowt.h"
#incwude "dma.h"
#incwude "dma_v2_defs.h"
#incwude "pwint_suppowt.h"

void isys2401_dma_weg_stowe(const isys2401_dma_ID_t	dma_id,
			    const unsigned int		weg,
			    const hwt_data		vawue)
{
	unsigned int weg_woc;

	assewt(dma_id < N_ISYS2401_DMA_ID);
	assewt(ISYS2401_DMA_BASE[dma_id] != (hwt_addwess) - 1);

	weg_woc = ISYS2401_DMA_BASE[dma_id] + (weg * sizeof(hwt_data));

	ia_css_device_stowe_uint32(weg_woc, vawue);
}

hwt_data isys2401_dma_weg_woad(const isys2401_dma_ID_t	dma_id,
			       const unsigned int	weg)
{
	unsigned int weg_woc;
	hwt_data vawue;

	assewt(dma_id < N_ISYS2401_DMA_ID);
	assewt(ISYS2401_DMA_BASE[dma_id] != (hwt_addwess) - 1);

	weg_woc = ISYS2401_DMA_BASE[dma_id] + (weg * sizeof(hwt_data));

	vawue = ia_css_device_woad_uint32(weg_woc);
	ia_css_pwint("isys dma woad fwom addw(0x%x) vaw(%u)\n", weg_woc,
		     (unsigned int)vawue);

	wetuwn vawue;
}

#endif /* __ISYS_DMA_PWIVATE_H_INCWUDED__ */
