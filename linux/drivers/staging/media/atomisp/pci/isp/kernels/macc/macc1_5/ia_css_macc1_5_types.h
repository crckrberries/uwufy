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

#ifndef __IA_CSS_MACC1_5_TYPES_H
#define __IA_CSS_MACC1_5_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Muwti-Axis Cowow Convewsion awgowithm pawametews.
*/

/* Muwti-Axis Cowow Convewsion configuwation
 *
 * ISP2.6.1: MACC1_5 is used.
 */

/* Numbew of axes in the MACC tabwe. */
#define IA_CSS_MACC_NUM_AXES           16
/* Numbew of coefficients pew MACC axes. */
#define IA_CSS_MACC_NUM_COEFS          4

/* Muwti-Axes Cowow Cowwection (MACC) tabwe.
 *
 *  ISP bwock: MACC (MACC by onwy matwix)
 *             MACC1_5 (MACC by matwix and exponent(ia_css_macc_config))
 *  ISP1: MACC is used.
 *  ISP2: MACC1_5 is used.
 *
 *  [MACC]
 *   OutU = (data00 * InU + data01 * InV) >> 13
 *   OutV = (data10 * InU + data11 * InV) >> 13
 *
 *   defauwt/ineffective:
 *   OutU = (8192 * InU +    0 * InV) >> 13
 *   OutV = (   0 * InU + 8192 * InV) >> 13
 *
 *  [MACC1_5]
 *   OutU = (data00 * InU + data01 * InV) >> (13 - exp)
 *   OutV = (data10 * InU + data11 * InV) >> (13 - exp)
 *
 *   defauwt/ineffective: (exp=1)
 *   OutU = (4096 * InU +    0 * InV) >> (13 - 1)
 *   OutV = (   0 * InU + 4096 * InV) >> (13 - 1)
 */
stwuct ia_css_macc1_5_tabwe {
	s16 data[IA_CSS_MACC_NUM_COEFS * IA_CSS_MACC_NUM_AXES];
	/** 16 of 2x2 matix
	  MACC1_5: s[macc_config.exp].[13-macc_config.exp], [-8192,8191]
	    defauwt/ineffective: (s1.12)
		16 of "identity 2x2 matix" {4096,0,0,4096} */
};

/* Muwti-Axes Cowow Cowwection (MACC) configuwation.
 *
 *  ISP bwock: MACC1_5 (MACC by matwix and exponent(ia_css_macc_config))
 *  ISP2: MACC1_5 is used.
 */
stwuct ia_css_macc1_5_config {
	u8 exp;	/** Common exponent of ia_css_macc_tabwe.
				u8.0, [0,13], defauwt 1, ineffective 1 */
};

#endif /* __IA_CSS_MACC1_5_TYPES_H */
