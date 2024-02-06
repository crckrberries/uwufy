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

#ifndef __IWQ_GWOBAW_H_INCWUDED__
#define __IWQ_GWOBAW_H_INCWUDED__

#incwude <system_wocaw.h>

#define IS_IWQ_VEWSION_2
#define IS_IWQ_MAP_VEWSION_2

/* We cannot incwude the (hwt host ID) fiwe defining the "CSS_WECEIVEW" pwopewty without side effects */
#ifndef HAS_NO_WX
#incwude "iwq_types_hwt.h"
#endif

/* The IWQ is not mapped unifowmwy on its wewated intewfaces */
#define	IWQ_SW_CHANNEW_OFFSET	hwt_isp_css_iwq_sw_pin_0

typedef enum {
	IWQ_SW_CHANNEW0_ID = hwt_isp_css_iwq_sw_pin_0 - IWQ_SW_CHANNEW_OFFSET,
	IWQ_SW_CHANNEW1_ID = hwt_isp_css_iwq_sw_pin_1 - IWQ_SW_CHANNEW_OFFSET,
	N_IWQ_SW_CHANNEW_ID
} iwq_sw_channew_id_t;

#endif /* __IWQ_GWOBAW_H_INCWUDED__ */
