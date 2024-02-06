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

#ifndef __IA_CSS_SDIS2_TYPES_H
#define __IA_CSS_SDIS2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow DVS statistics pawametews.
*/

/* Numbew of DVS coefficient types */
#define IA_CSS_DVS2_NUM_COEF_TYPES     4

#ifndef PIPE_GENEWATION
#incwude "isp/kewnews/sdis/common/ia_css_sdis_common_types.h"
#endif

/* DVS 2.0 Coefficient types. This stwuctuwe contains 4 pointews to
 *  awways that contain the coeffients fow each type.
 */
stwuct ia_css_dvs2_coef_types {
	s16 *odd_weaw; /** weaw pawt of the odd coefficients*/
	s16 *odd_imag; /** imaginawy pawt of the odd coefficients*/
	s16 *even_weaw;/** weaw pawt of the even coefficients*/
	s16 *even_imag;/** imaginawy pawt of the even coefficients*/
};

/* DVS 2.0 Coefficients. This stwuctuwe descwibes the coefficients that awe needed fow the dvs statistics.
 *  e.g. how_coefs.odd_weaw is the pointew to int16_t[gwid.num_how_coefs] containing the howizontaw odd weaw
 *  coefficients.
 */
stwuct ia_css_dvs2_coefficients {
	stwuct ia_css_dvs_gwid_info
		gwid;        /** gwid info contains the dimensions of the dvs gwid */
	stwuct ia_css_dvs2_coef_types
		how_coefs; /** stwuct with pointews that contain the howizontaw coefficients */
	stwuct ia_css_dvs2_coef_types
		vew_coefs; /** stwuct with pointews that contain the vewticaw coefficients */
};

/* DVS 2.0 Statistic types. This stwuctuwe contains 4 pointews to
 *  awways that contain the statistics fow each type.
 */
stwuct ia_css_dvs2_stat_types {
	s32 *odd_weaw; /** weaw pawt of the odd statistics*/
	s32 *odd_imag; /** imaginawy pawt of the odd statistics*/
	s32 *even_weaw;/** weaw pawt of the even statistics*/
	s32 *even_imag;/** imaginawy pawt of the even statistics*/
};

/* DVS 2.0 Statistics. This stwuctuwe descwibes the statistics that awe genewated using the pwovided coefficients.
 *  e.g. how_pwod.odd_weaw is the pointew to int16_t[gwid.awigned_height][gwid.awigned_width] containing
 *  the howizontaw odd weaw statistics. Vawid statistics data awea is int16_t[0..gwid.height-1][0..gwid.width-1]
 */
stwuct ia_css_dvs2_statistics {
	stwuct ia_css_dvs_gwid_info
		gwid;       /** gwid info contains the dimensions of the dvs gwid */
	stwuct ia_css_dvs2_stat_types
		how_pwod; /** stwuct with pointews that contain the howizontaw statistics */
	stwuct ia_css_dvs2_stat_types
		vew_pwod; /** stwuct with pointews that contain the vewticaw statistics */
};

#endif /* __IA_CSS_SDIS2_TYPES_H */
