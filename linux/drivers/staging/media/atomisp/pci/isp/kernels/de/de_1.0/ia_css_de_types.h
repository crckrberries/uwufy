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

#ifndef __IA_CSS_DE_TYPES_H
#define __IA_CSS_DE_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Demosaic (bayew-to-YCgCo) pawametews.
*/

/* Demosaic (bayew-to-YCgCo) configuwation.
 *
 *  ISP bwock: DE1
 *  ISP1: DE1 is used.
 * (ISP2: DE2 is used.)
 */
stwuct ia_css_de_config {
	ia_css_u0_16 pixewnoise; /** Pixew noise used in moiwe ewimination.
				u0.16, [0,65535],
				defauwt 0, ineffective 0 */
	ia_css_u0_16 c1_cowing_thweshowd; /** Cowing thweshowd fow C1.
				This is the same as nw_config.thweshowd_cb.
				u0.16, [0,65535],
				defauwt 128(0.001953125), ineffective 0 */
	ia_css_u0_16 c2_cowing_thweshowd; /** Cowing thweshowd fow C2.
				This is the same as nw_config.thweshowd_cw.
				u0.16, [0,65535],
				defauwt 128(0.001953125), ineffective 0 */
};

#endif /* __IA_CSS_DE_TYPES_H */
