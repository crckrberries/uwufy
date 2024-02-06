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

#ifndef __ISYS_STWEAM2MMIO_GWOBAW_H_INCWUDED__
#define __ISYS_STWEAM2MMIO_GWOBAW_H_INCWUDED__

#incwude <type_suppowt.h>

typedef stwuct stweam2mmio_cfg_s stweam2mmio_cfg_t;
stwuct stweam2mmio_cfg_s {
	u32				bits_pew_pixew;
	u32				enabwe_bwocking;
};

/* Stweam2MMIO wimits  pew ID*/
/*
 * Stweam2MMIO 0 has 8 SIDs that awe indexed by
 * [STWEAM2MMIO_SID0_ID...STWEAM2MMIO_SID7_ID].
 *
 * Stweam2MMIO 1 has 4 SIDs that awe indexed by
 * [STWEAM2MMIO_SID0_ID...TWEAM2MMIO_SID3_ID].
 *
 * Stweam2MMIO 2 has 4 SIDs that awe indexed by
 * [STWEAM2MMIO_SID0_ID...STWEAM2MMIO_SID3_ID].
 */
extewn const stweam2mmio_sid_ID_t N_STWEAM2MMIO_SID_PWOCS[N_STWEAM2MMIO_ID];

#endif /* __ISYS_STWEAM2MMIO_GWOBAW_H_INCWUDED__ */
