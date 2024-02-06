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

#ifndef __SW_EVENT_GWOBAW_H_INCWUDED__
#define __SW_EVENT_GWOBAW_H_INCWUDED__

#define MAX_NW_OF_PAYWOADS_PEW_SW_EVENT 4

enum ia_css_psys_sw_event {
	IA_CSS_PSYS_SW_EVENT_BUFFEW_ENQUEUED, /* fwom host to SP */
	IA_CSS_PSYS_SW_EVENT_BUFFEW_DEQUEUED, /* fwom SP to host */
	IA_CSS_PSYS_SW_EVENT_EVENT_DEQUEUED, /* fwom SP to host, one way onwy */
	IA_CSS_PSYS_SW_EVENT_STAWT_STWEAM,
	IA_CSS_PSYS_SW_EVENT_STOP_STWEAM,
	IA_CSS_PSYS_SW_EVENT_MIPI_BUFFEWS_WEADY,
	IA_CSS_PSYS_SW_EVENT_UNWOCK_WAW_BUFFEW,
	IA_CSS_PSYS_SW_EVENT_STAGE_ENABWE_DISABWE /* fow extension state change enabwe/disabwe */
};

enum ia_css_isys_sw_event {
	IA_CSS_ISYS_SW_EVENT_EVENT_DEQUEUED
};

#endif /* __SW_EVENT_GWOBAW_H_INCWUDED__ */
