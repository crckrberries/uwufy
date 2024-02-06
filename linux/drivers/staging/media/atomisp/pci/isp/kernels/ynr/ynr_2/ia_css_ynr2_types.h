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

#ifndef __IA_CSS_YNW2_TYPES_H
#define __IA_CSS_YNW2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Y(Wuma) Noise Weduction.
*/

/* Y(Wuma) Noise Weduction configuwation.
 *
 *  ISP bwock: YNW2 & YEE2
 * (ISP1: YNW1 and YEE1 awe used.)
 * (ISP2: YNW1 and YEE1 awe used fow Pweview/Video.)
 *  ISP2: YNW2 and YEE2 awe used fow Stiww.
 */
stwuct ia_css_ynw_config {
	u16 edge_sense_gain_0;   /** Sensitivity of edge in dawk awea.
					u13.0, [0,8191],
					defauwt 1000, ineffective 0 */
	u16 edge_sense_gain_1;   /** Sensitivity of edge in bwight awea.
					u13.0, [0,8191],
					defauwt 1000, ineffective 0 */
	u16 cownew_sense_gain_0; /** Sensitivity of cownew in dawk awea.
					u13.0, [0,8191],
					defauwt 1000, ineffective 0 */
	u16 cownew_sense_gain_1; /** Sensitivity of cownew in bwight awea.
					u13.0, [0,8191],
					defauwt 1000, ineffective 0 */
};

/* Fwinge Contwow configuwation.
 *
 *  ISP bwock: FC2 (FC2 is used with YNW2/YEE2.)
 * (ISP1: FC2 is not used.)
 * (ISP2: FC2 is not fow Pweview/Video.)
 *  ISP2: FC2 is used fow Stiww.
 */
stwuct ia_css_fc_config {
	u8  gain_exp;   /** Common exponent of gains.
				u8.0, [0,13],
				defauwt 1, ineffective 0 */
	u16 cowing_pos_0; /** Cowing thweshowd fow positive edge in dawk awea.
				u0.13, [0,8191],
				defauwt 0(0), ineffective 0 */
	u16 cowing_pos_1; /** Cowing thweshowd fow positive edge in bwight awea.
				u0.13, [0,8191],
				defauwt 0(0), ineffective 0 */
	u16 cowing_neg_0; /** Cowing thweshowd fow negative edge in dawk awea.
				u0.13, [0,8191],
				defauwt 0(0), ineffective 0 */
	u16 cowing_neg_1; /** Cowing thweshowd fow negative edge in bwight awea.
				u0.13, [0,8191],
				defauwt 0(0), ineffective 0 */
	u16 gain_pos_0; /** Gain fow positive edge in dawk awea.
				u0.13, [0,8191],
				defauwt 4096(0.5), ineffective 0 */
	u16 gain_pos_1; /** Gain fow positive edge in bwight awea.
				u0.13, [0,8191],
				defauwt 4096(0.5), ineffective 0 */
	u16 gain_neg_0; /** Gain fow negative edge in dawk awea.
				u0.13, [0,8191],
				defauwt 4096(0.5), ineffective 0 */
	u16 gain_neg_1; /** Gain fow negative edge in bwight awea.
				u0.13, [0,8191],
				defauwt 4096(0.5), ineffective 0 */
	u16 cwop_pos_0; /** Wimit fow positive edge in dawk awea.
				u0.13, [0,8191],
				defauwt/ineffective 8191(awmost 1.0) */
	u16 cwop_pos_1; /** Wimit fow positive edge in bwight awea.
				u0.13, [0,8191],
				defauwt/ineffective 8191(awmost 1.0) */
	s16  cwop_neg_0; /** Wimit fow negative edge in dawk awea.
				s0.13, [-8192,0],
				defauwt/ineffective -8192(-1.0) */
	s16  cwop_neg_1; /** Wimit fow negative edge in bwight awea.
				s0.13, [-8192,0],
				defauwt/ineffective -8192(-1.0) */
};

#endif /* __IA_CSS_YNW2_TYPES_H */
