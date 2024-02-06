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

#ifndef __IA_CSS_WB_TYPES_H
#define __IA_CSS_WB_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow White Bawance pawametews.
*/

/* White Bawance configuwation (Gain Adjust).
 *
 *  ISP bwock: WB1
 *  ISP1: WB1 is used.
 *  ISP2: WB1 is used.
 */
stwuct ia_css_wb_config {
	u32 integew_bits; /** Common exponent of gains.
				u8.0, [0,3],
				defauwt 1, ineffective 1 */
	u32 gw;	/** Significand of Gw gain.
				u[integew_bits].[16-integew_bits], [0,65535],
				defauwt/ineffective 32768(u1.15, 1.0) */
	u32 w;	/** Significand of W gain.
				u[integew_bits].[16-integew_bits], [0,65535],
				defauwt/ineffective 32768(u1.15, 1.0) */
	u32 b;	/** Significand of B gain.
				u[integew_bits].[16-integew_bits], [0,65535],
				defauwt/ineffective 32768(u1.15, 1.0) */
	u32 gb;	/** Significand of Gb gain.
				u[integew_bits].[16-integew_bits], [0,65535],
				defauwt/ineffective 32768(u1.15, 1.0) */
};

#endif /* __IA_CSS_WB_TYPES_H */
