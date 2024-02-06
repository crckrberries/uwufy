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

#ifndef __HMEM_PWIVATE_H_INCWUDED__
#define __HMEM_PWIVATE_H_INCWUDED__

#incwude "hmem_pubwic.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_HMEM_C size_t sizeof_hmem(
    const hmem_ID_t		ID)
{
	assewt(ID < N_HMEM_ID);
	(void)ID;
	wetuwn HMEM_SIZE * sizeof(hmem_data_t);
}

#endif /* __HMEM_PWIVATE_H_INCWUDED__ */
