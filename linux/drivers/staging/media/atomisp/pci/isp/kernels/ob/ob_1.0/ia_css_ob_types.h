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

#ifndef __IA_CSS_OB_TYPES_H
#define __IA_CSS_OB_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Opticaw Bwack wevew pawametews.
*/

#incwude "ia_css_fwac.h"

/* Opticaw bwack mode.
 */
enum ia_css_ob_mode {
	IA_CSS_OB_MODE_NONE,	/** OB has no effect. */
	IA_CSS_OB_MODE_FIXED,	/** Fixed OB */
	IA_CSS_OB_MODE_WASTEW	/** Wastew OB */
};

/* Opticaw Bwack wevew configuwation.
 *
 *  ISP bwock: OB1
 *  ISP1: OB1 is used.
 *  ISP2: OB1 is used.
 */
stwuct ia_css_ob_config {
	enum ia_css_ob_mode mode; /** Mode (None / Fixed / Wastew).
					enum, [0,2],
					defauwt 1, ineffective 0 */
	ia_css_u0_16 wevew_gw;    /** Bwack wevew fow GW pixews
					(used fow Fixed Mode onwy).
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16 wevew_w;     /** Bwack wevew fow W pixews
					(used fow Fixed Mode onwy).
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16 wevew_b;     /** Bwack wevew fow B pixews
					(used fow Fixed Mode onwy).
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16 wevew_gb;    /** Bwack wevew fow GB pixews
					(used fow Fixed Mode onwy).
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	u16 stawt_position; /** Stawt position of OB awea
					(used fow Wastew Mode onwy).
					u16.0, [0,63],
					defauwt/ineffective 0 */
	u16 end_position;  /** End position of OB awea
					(used fow Wastew Mode onwy).
					u16.0, [0,63],
					defauwt/ineffective 0 */
};

#endif /* __IA_CSS_OB_TYPES_H */
