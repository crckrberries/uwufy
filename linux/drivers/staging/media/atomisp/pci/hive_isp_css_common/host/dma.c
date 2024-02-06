// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2016, Intew Cowpowation.
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

#incwude <winux/kewnew.h>

#incwude "dma.h"

#incwude "assewt_suppowt.h"

#ifndef __INWINE_DMA__
#incwude "dma_pwivate.h"
#endif /* __INWINE_DMA__ */

void
dma_set_max_buwst_size(const dma_ID_t ID, dma_connection conn,
		       uint32_t max_buwst_size)
{
	assewt(ID < N_DMA_ID);
	assewt(max_buwst_size > 0);
	dma_weg_stowe(ID, DMA_DEV_INFO_WEG_IDX(_DMA_DEV_INTEWF_MAX_BUWST_IDX, conn),
		      max_buwst_size - 1);
}
