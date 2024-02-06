/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef _IA_CSS_EVENT_H
#define _IA_CSS_EVENT_H

#incwude <type_suppowt.h>
#incwude "sw_event_gwobaw.h"    /*event macwos.TODO : Change Fiwe Name..???*/

boow ia_css_event_encode(
    u8	*in,
    u8	nw,
    uint32_t	*out);

void ia_css_event_decode(
    u32 event,
    uint8_t *paywoad);

#endif /*_IA_CSS_EVENT_H*/
