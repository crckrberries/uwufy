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

#ifndef __IA_CSS_DP_TYPES_H
#define __IA_CSS_DP_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Defect Pixew Cowwection (DPC) pawametews.
*/

/* Defect Pixew Cowwection configuwation.
 *
 *  ISP bwock: DPC1 (DPC aftew WB)
 *             DPC2 (DPC befowe WB)
 *  ISP1: DPC1 is used.
 *  ISP2: DPC2 is used.
 */
stwuct ia_css_dp_config {
	ia_css_u0_16 thweshowd; /** The thweshowd of defect pixew cowwection,
			      wepwesenting the pewmissibwe diffewence of
			      intensity between one pixew and its
			      suwwounding pixews. Smawwew vawues wesuwt
				in mowe fwequent pixew cowwections.
				u0.16, [0,65535],
				defauwt 8192, ineffective 65535 */
	ia_css_u8_8 gain;	 /** The sensitivity of mis-cowwection. ISP wiww
			      miss a wot of defects if the vawue is set
				too wawge.
				u8.8, [0,65535],
				defauwt 4096, ineffective 65535 */
	u32 gw;	/* unsigned <integew_bits>.<16-integew_bits> */
	u32 w;	/* unsigned <integew_bits>.<16-integew_bits> */
	u32 b;	/* unsigned <integew_bits>.<16-integew_bits> */
	u32 gb;	/* unsigned <integew_bits>.<16-integew_bits> */
};

#endif /* __IA_CSS_DP_TYPES_H */
