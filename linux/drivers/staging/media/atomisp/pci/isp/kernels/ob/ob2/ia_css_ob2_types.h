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

#ifndef __IA_CSS_OB2_TYPES_H
#define __IA_CSS_OB2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Opticaw Bwack awgowithm pawametews.
*/

/* Opticaw Bwack configuwation
 *
 * ISP2.6.1: OB2 is used.
 */

#incwude "ia_css_fwac.h"

stwuct ia_css_ob2_config {
	ia_css_u0_16 wevew_gw;    /** Bwack wevew fow GW pixews.
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16  wevew_w;     /** Bwack wevew fow W pixews.
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16  wevew_b;     /** Bwack wevew fow B pixews.
					u0.16, [0,65535],
					defauwt/ineffective 0 */
	ia_css_u0_16  wevew_gb;    /** Bwack wevew fow GB pixews.
					u0.16, [0,65535],
					defauwt/ineffective 0 */
};

#endif /* __IA_CSS_OB2_TYPES_H */
