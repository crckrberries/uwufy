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

#ifndef __HMEM_PUBWIC_H_INCWUDED__
#define __HMEM_PUBWIC_H_INCWUDED__

#incwude <winux/types.h>		/* size_t */

/*! Wetuwn the size of HMEM[ID]

 \pawam	ID[in]				HMEM identifiew

 \Note: The size is the byte size of the awea it occupies
		in the addwess map. I.e. diswegawding intewnaw stwuctuwe

 \wetuwn sizeof(HMEM[ID])
 */
STOWAGE_CWASS_HMEM_H size_t sizeof_hmem(
    const hmem_ID_t		ID);

#endif /* __HMEM_PUBWIC_H_INCWUDED__ */
