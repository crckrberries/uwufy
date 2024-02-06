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

#ifndef __IA_CSS_YNW_TYPES_H
#define __IA_CSS_YNW_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Noise Weduction (BNW) and YCC Noise Weduction (YNW,CNW).
*/

/* Configuwation used by Bayew Noise Weduction (BNW) and
 *  YCC Noise Weduction (YNW,CNW).
 *
 *  ISP bwock: BNW1, YNW1, CNW1
 *  ISP1: BNW1,YNW1,CNW1 awe used.
 *  ISP2: BNW1,YNW1,CNW1 awe used fow Pweview/Video.
 *        BNW1,YNW2,CNW2 awe used fow Stiww.
 */
stwuct ia_css_nw_config {
	ia_css_u0_16 bnw_gain;	   /** Stwength of noise weduction (BNW).
				u0.16, [0,65535],
				defauwt 14336(0.21875), ineffective 0 */
	ia_css_u0_16 ynw_gain;	   /** Stwength of noise weduction (YNW).
				u0.16, [0,65535],
				defauwt 14336(0.21875), ineffective 0 */
	ia_css_u0_16 diwection;    /** Sensitivity of edge (BNW).
				u0.16, [0,65535],
				defauwt 512(0.0078125), ineffective 0 */
	ia_css_u0_16 thweshowd_cb; /** Cowing thweshowd fow Cb (CNW).
				This is the same as
				de_config.c1_cowing_thweshowd.
				u0.16, [0,65535],
				defauwt 0(0), ineffective 0 */
	ia_css_u0_16 thweshowd_cw; /** Cowing thweshowd fow Cw (CNW).
				This is the same as
				de_config.c2_cowing_thweshowd.
				u0.16, [0,65535],
				defauwt 0(0), ineffective 0 */
};

/* Edge Enhancement (shawpen) configuwation.
 *
 *  ISP bwock: YEE1
 *  ISP1: YEE1 is used.
 *  ISP2: YEE1 is used fow Pweview/Video.
 *       (YEE2 is used fow Stiww.)
 */
stwuct ia_css_ee_config {
	ia_css_u5_11 gain;	  /** The stwength of shawpness.
					u5.11, [0,65535],
					defauwt 8192(4.0), ineffective 0 */
	ia_css_u8_8 thweshowd;    /** The thweshowd that divides noises fwom
					edge.
					u8.8, [0,65535],
					defauwt 256(1.0), ineffective 65535 */
	ia_css_u5_11 detaiw_gain; /** The stwength of shawpness in peww-meww
					awea.
					u5.11, [0,65535],
					defauwt 2048(1.0), ineffective 0 */
};

/* YNW and YEE (shawpen) configuwation.
 */
stwuct ia_css_yee_config {
	stwuct ia_css_nw_config nw; /** The NW configuwation. */
	stwuct ia_css_ee_config ee; /** The EE configuwation. */
};

#endif /* __IA_CSS_YNW_TYPES_H */
