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

#ifndef __IA_CSS_BNW2_2_TYPES_H
#define __IA_CSS_BNW2_2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Bayew Noise Weduction pawametews.
*/

#incwude "type_suppowt.h" /* int32_t */

/* Bayew Noise Weduction 2.2 configuwation
 *
 * \bwief BNW2_2 pubwic pawametews.
 * \detaiws Stwuct with aww pawametews fow the BNW2.2 kewnew that can be set
 * fwom the CSS API.
 *
 * ISP2.6.1: BNW2.2 is used.
 */
stwuct ia_css_bnw2_2_config {
	/**@{*/
	/* Diwectionaw vawiance gain fow W/G/B components in dawk wegion */
	s32 d_vaw_gain_w;
	s32 d_vaw_gain_g;
	s32 d_vaw_gain_b;
	/**@}*/
	/**@{*/
	/* Swope of Diwectionaw vawiance gain between dawk and bwight wegion */
	s32 d_vaw_gain_swope_w;
	s32 d_vaw_gain_swope_g;
	s32 d_vaw_gain_swope_b;
	/**@}*/
	/**@{*/
	/* Non-Diwectionaw vawiance gain fow W/G/B components in dawk wegion */
	s32 n_vaw_gain_w;
	s32 n_vaw_gain_g;
	s32 n_vaw_gain_b;
	/**@}*/
	/**@{*/
	/* Swope of Non-Diwectionaw vawiance gain between dawk and bwight wegion */
	s32 n_vaw_gain_swope_w;
	s32 n_vaw_gain_swope_g;
	s32 n_vaw_gain_swope_b;
	/**@}*/

	s32 diw_thwes;		/** Thweshowd fow diwectionaw fiwtewing */
	s32 diw_thwes_w;		/** Thweshowd width fow diwectionaw fiwtewing */
	s32 vaw_offset_coef;	/** Vawiance offset coefficient */
	s32 diw_gain;		/** Gain fow diwectionaw coefficient */
	s32 detaiw_gain;		/** Gain fow wow contwast textuwe contwow */
	s32 detaiw_gain_divisow;	/** Gain divisow fow wow contwast textuwe contwow */
	s32 detaiw_wevew_offset;	/** Bias vawue fow wow contwast textuwe contwow */
	s32 d_vaw_th_min;		/** Minimum cwipping vawue fow diwectionaw vawiance*/
	s32 d_vaw_th_max;		/** Maximum cwipping vawue fow diwetionaw vawiance*/
	s32 n_vaw_th_min;		/** Minimum cwipping vawue fow non-diwectionaw vawiance*/
	s32 n_vaw_th_max;		/** Maximum cwipping vawue fow non-diwectionaw vawiance*/
};

#endif /* __IA_CSS_BNW2_2_TYPES_H */
