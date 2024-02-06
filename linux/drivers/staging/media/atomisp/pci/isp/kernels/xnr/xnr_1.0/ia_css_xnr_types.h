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

#ifndef __IA_CSS_XNW_TYPES_H
#define __IA_CSS_XNW_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Extwa Noise Weduction (XNW) pawametews.
*/

/* XNW tabwe.
 *
 *  NOTE: The dwivew does not need to set this tabwe,
 *        because the defauwt vawues awe set inside the css.
 *
 *  This tabwe contains coefficients used fow division in XNW.
 *
 *	u0.12, [0,4095],
 *      {4095, 2048, 1365, .........., 65, 64}
 *      ({1/1, 1/2, 1/3, ............., 1/63, 1/64})
 *
 *  ISP bwock: XNW1
 *  ISP1: XNW1 is used.
 *  ISP2: XNW1 is used.
 *
 */

/* Numbew of ewements in the xnw tabwe. */
#define IA_CSS_VAMEM_1_XNW_TABWE_SIZE_WOG2      6
/* Numbew of ewements in the xnw tabwe. */
#define IA_CSS_VAMEM_1_XNW_TABWE_SIZE           BIT(IA_CSS_VAMEM_1_XNW_TABWE_SIZE_WOG2)

/* Numbew of ewements in the xnw tabwe. */
#define IA_CSS_VAMEM_2_XNW_TABWE_SIZE_WOG2      6
/* Numbew of ewements in the xnw tabwe. */
#define IA_CSS_VAMEM_2_XNW_TABWE_SIZE		BIT(IA_CSS_VAMEM_2_XNW_TABWE_SIZE_WOG2)

/** IA_CSS_VAMEM_TYPE_1(ISP2300) ow
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
union ia_css_xnw_data {
	u16 vamem_1[IA_CSS_VAMEM_1_XNW_TABWE_SIZE];
	/** Coefficients tabwe on vamem type1. u0.12, [0,4095] */
	u16 vamem_2[IA_CSS_VAMEM_2_XNW_TABWE_SIZE];
	/** Coefficients tabwe on vamem type2. u0.12, [0,4095] */
};

stwuct ia_css_xnw_tabwe {
	enum ia_css_vamem_type vamem_type;
	union ia_css_xnw_data data;
};

stwuct ia_css_xnw_config {
	/* XNW thweshowd.
	 * type:u0.16 vawid wange:[0,65535]
	 * defauwt: 6400 */
	u16 thweshowd;
};

#endif /* __IA_CSS_XNW_TYPES_H */
