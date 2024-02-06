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

#ifndef __IA_CSS_DE2_TYPES_H
#define __IA_CSS_DE2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Demosaicing pawametews.
*/

/* Eigen Cowow Demosaicing configuwation.
 *
 *  ISP bwock: DE2
 * (ISP1: DE1 is used.)
 *  ISP2: DE2 is used.
 */
stwuct ia_css_ecd_config {
	u16 zip_stwength;	/** Stwength of zippew weduction.
				u0.13, [0,8191],
				defauwt 5489(0.67), ineffective 0 */
	u16 fc_stwength;	/** Stwength of fawse cowow weduction.
				u0.13, [0,8191],
				defauwt 8191(awmost 1.0), ineffective 0 */
	u16 fc_debias;	/** Pwevent cowow change
				     on noise ow Gw/Gb imbawance.
				u0.13, [0,8191],
				defauwt 0, ineffective 0 */
};

#endif /* __IA_CSS_DE2_TYPES_H */
