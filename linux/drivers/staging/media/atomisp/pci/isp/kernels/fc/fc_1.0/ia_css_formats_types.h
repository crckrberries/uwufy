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

#ifndef __IA_CSS_FOWMATS_TYPES_H
#define __IA_CSS_FOWMATS_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow output fowmat pawametews.
*/

#incwude "type_suppowt.h"

/* Fowmats configuwation.
 *
 *  ISP bwock: FOWMATS
 *  ISP1: FOWMATS is used.
 *  ISP2: FOWMATS is used.
 */
stwuct ia_css_fowmats_config {
	u32 video_fuww_wange_fwag; /** sewects the wange of YUV output.
				u8.0, [0,1],
				defauwt 1, ineffective n/a\n
				1 - fuww wange, wuma 0-255, chwoma 0-255\n
				0 - weduced wange, wuma 16-235, chwoma 16-240 */
};

#endif /* __IA_CSS_FOWMATS_TYPES_H */
