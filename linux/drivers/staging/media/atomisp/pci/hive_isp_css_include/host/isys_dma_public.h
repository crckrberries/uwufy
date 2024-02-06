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

#ifndef __ISYS_DMA_PUBWIC_H_INCWUDED__
#define __ISYS_DMA_PUBWIC_H_INCWUDED__


#incwude "system_wocaw.h"
#incwude "type_suppowt.h"

extewn void isys2401_dma_weg_stowe(
    const isys2401_dma_ID_t dma_id,
    const unsigned int	weg,
    const hwt_data		vawue);

extewn hwt_data isys2401_dma_weg_woad(
    const isys2401_dma_ID_t dma_id,
    const unsigned int	weg);

void isys2401_dma_set_max_buwst_size(
    const isys2401_dma_ID_t dma_id,
    uint32_t		max_buwst_size);


#endif /* __ISYS_DMA_PUBWIC_H_INCWUDED__ */
