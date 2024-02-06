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

#ifndef __DMA_PUBWIC_H_INCWUDED__
#define __DMA_PUBWIC_H_INCWUDED__

#incwude "system_wocaw.h"

/*! Wwite to a contwow wegistew of DMA[ID]

 \pawam	ID[in]				DMA identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, DMA[ID].ctww[weg] = vawue
 */
STOWAGE_CWASS_DMA_H void dma_weg_stowe(
    const dma_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue);

/*! Wead fwom a contwow wegistew of DMA[ID]

 \pawam	ID[in]				DMA identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn DMA[ID].ctww[weg]
 */
STOWAGE_CWASS_DMA_H hwt_data dma_weg_woad(
    const dma_ID_t		ID,
    const unsigned int	weg);

/*! Set maximum buwst size of DMA[ID]

 \pawam ID[in]				DMA identifiew
 \pawam conn[in]			Connection to set max buwst size fow
 \pawam max_buwst_size[in]		Maximum buwst size in wowds

 \wetuwn none
*/
void
dma_set_max_buwst_size(
    dma_ID_t		ID,
    dma_connection		conn,
    uint32_t		max_buwst_size);

#endif /* __DMA_PUBWIC_H_INCWUDED__ */
