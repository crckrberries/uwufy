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

#ifndef __IA_CSS_AA2_TYPES_H
#define __IA_CSS_AA2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Anti-Awiasing pawametews.
*/

/* Anti-Awiasing configuwation.
 *
 *  This stwuctuwe is used both fow YUV AA and Bayew AA.
 *
 *  1. YUV Anti-Awiasing
 *     stwuct ia_css_aa_config   *aa_config
 *
 *     ISP bwock: AA2
 *    (ISP1: AA2 is not used.)
 *     ISP2: AA2 shouwd be used. But, AA2 is not used cuwwentwy.
 *
 *  2. Bayew Anti-Awiasing
 *     stwuct ia_css_aa_config   *baa_config
 *
 *     ISP bwock: BAA2
 *     ISP1: BAA2 is used.
 *     ISP2: BAA2 is used.
 */
stwuct ia_css_aa_config {
	u16 stwength;	/** Stwength of the fiwtew.
					u0.13, [0,8191],
					defauwt/ineffective 0 */
};

#endif /* __IA_CSS_AA2_TYPES_H */
