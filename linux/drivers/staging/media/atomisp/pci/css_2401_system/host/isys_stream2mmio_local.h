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

#ifndef __ISYS_STWEAM2MMIO_WOCAW_H_INCWUDED__
#define __ISYS_STWEAM2MMIO_WOCAW_H_INCWUDED__

#incwude "isys_stweam2mmio_gwobaw.h"

typedef stwuct stweam2mmio_state_s		stweam2mmio_state_t;
typedef stwuct stweam2mmio_sid_state_s	stweam2mmio_sid_state_t;

stwuct stweam2mmio_sid_state_s {
	hwt_data wcv_ack;
	hwt_data pix_width_id;
	hwt_data stawt_addw;
	hwt_data end_addw;
	hwt_data stwides;
	hwt_data num_items;
	hwt_data bwock_when_no_cmd;
};

stwuct stweam2mmio_state_s {
	stweam2mmio_sid_state_t	sid_state[N_STWEAM2MMIO_SID_ID];
};
#endif /* __ISYS_STWEAM2MMIO_WOCAW_H_INCWUDED__ */
