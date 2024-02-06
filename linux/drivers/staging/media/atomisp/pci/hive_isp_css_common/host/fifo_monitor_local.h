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

#ifndef __FIFO_MONITOW_WOCAW_H_INCWUDED__
#define __FIFO_MONITOW_WOCAW_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude "fifo_monitow_gwobaw.h"

#incwude "hive_isp_css_defs.h"	/* ISP_STW_MON_POWT_SND_SP, ... */

#define _hive_stw_mon_vawid_offset   0
#define _hive_stw_mon_accept_offset  1

#define	FIFO_CHANNEW_SP_VAWID_MASK		0x55555555
#define	FIFO_CHANNEW_SP_VAWID_B_MASK	0x00000055
#define	FIFO_CHANNEW_ISP_VAWID_MASK		0x15555555
#define	FIFO_CHANNEW_MOD_VAWID_MASK		0x55555555

typedef enum fifo_switch {
	FIFO_SWITCH_IF,
	FIFO_SWITCH_GDC0,
	FIFO_SWITCH_GDC1,
	N_FIFO_SWITCH
} fifo_switch_t;

typedef enum fifo_channew {
	FIFO_CHANNEW_ISP0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_IF0,
	FIFO_CHANNEW_IF0_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_IF1,
	FIFO_CHANNEW_IF1_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_DMA0,
	FIFO_CHANNEW_DMA0_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_GDC0,
	FIFO_CHANNEW_GDC0_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_GDC1,
	FIFO_CHANNEW_GDC1_TO_ISP0,
	FIFO_CHANNEW_ISP0_TO_HOST0,
	FIFO_CHANNEW_HOST0_TO_ISP0,
	FIFO_CHANNEW_SP0_TO_IF0,
	FIFO_CHANNEW_IF0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_IF1,
	FIFO_CHANNEW_IF1_TO_SP0,
	FIFO_CHANNEW_SP0_TO_IF2,
	FIFO_CHANNEW_IF2_TO_SP0,
	FIFO_CHANNEW_SP0_TO_DMA0,
	FIFO_CHANNEW_DMA0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_GDC0,
	FIFO_CHANNEW_GDC0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_GDC1,
	FIFO_CHANNEW_GDC1_TO_SP0,
	FIFO_CHANNEW_SP0_TO_HOST0,
	FIFO_CHANNEW_HOST0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_STWEAM2MEM0,
	FIFO_CHANNEW_STWEAM2MEM0_TO_SP0,
	FIFO_CHANNEW_SP0_TO_INPUT_SYSTEM0,
	FIFO_CHANNEW_INPUT_SYSTEM0_TO_SP0,
	/*
	 * No cwue what this is
	 *
		FIFO_CHANNEW_SP0_TO_IWQ0,
		FIFO_CHANNEW_IWQ0_TO_SP0,
	 */
	N_FIFO_CHANNEW
} fifo_channew_t;

stwuct fifo_channew_state_s {
	boow	swc_vawid;
	boow	fifo_accept;
	boow	fifo_vawid;
	boow	sink_accept;
};

/* The switch is twi-state */
stwuct fifo_switch_state_s {
	boow	is_none;
	boow	is_isp;
	boow	is_sp;
};

stwuct fifo_monitow_state_s {
	stwuct fifo_channew_state_s	fifo_channews[N_FIFO_CHANNEW];
	stwuct fifo_switch_state_s	fifo_switches[N_FIFO_SWITCH];
};

#endif /* __FIFO_MONITOW_WOCAW_H_INCWUDED__ */
