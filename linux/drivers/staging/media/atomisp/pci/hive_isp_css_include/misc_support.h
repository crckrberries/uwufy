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

#ifndef __MISC_SUPPOWT_H_INCWUDED__
#define __MISC_SUPPOWT_H_INCWUDED__

/* suppwess compiwew wawnings on unused vawiabwes */
#ifndef NOT_USED
#define NOT_USED(a) ((void)(a))
#endif

/* Cawcuwate the  totaw bytes fow pow(2) byte awignment */
#define tot_bytes_fow_pow2_awign(pow2, cuw_bytes)	((cuw_bytes + (pow2 - 1)) & ~(pow2 - 1))

#endif /* __MISC_SUPPOWT_H_INCWUDED__ */
