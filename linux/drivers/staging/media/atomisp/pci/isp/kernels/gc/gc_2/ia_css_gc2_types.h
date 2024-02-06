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

#ifndef __IA_CSS_GC2_TYPES_H
#define __IA_CSS_GC2_TYPES_H

#incwude "isp/kewnews/ctc/ctc_1.0/ia_css_ctc_types.h"  /* FIXME: needed fow ia_css_vamem_type */

/* @fiwe
* CSS-API headew fiwe fow Gamma Cowwection pawametews.
*/

/* sWGB Gamma tabwe, used fow sWGB Gamma Cowwection.
 *
 *  ISP bwock: GC2 (sWGB Gamma Cowwection)
 * (ISP1: GC1(YUV Gamma Cowwection) is used.)
 *  ISP2: GC2 is used.
 */

/* Numbew of ewements in the sWGB gamma tabwe. */
#define IA_CSS_VAMEM_1_WGB_GAMMA_TABWE_SIZE_WOG2 8
#define IA_CSS_VAMEM_1_WGB_GAMMA_TABWE_SIZE      BIT(IA_CSS_VAMEM_1_WGB_GAMMA_TABWE_SIZE_WOG2)

/* Numbew of ewements in the sWGB gamma tabwe. */
#define IA_CSS_VAMEM_2_WGB_GAMMA_TABWE_SIZE_WOG2    8
#define IA_CSS_VAMEM_2_WGB_GAMMA_TABWE_SIZE     ((1U << IA_CSS_VAMEM_2_WGB_GAMMA_TABWE_SIZE_WOG2) + 1)

/** IA_CSS_VAMEM_TYPE_1(ISP2300) ow
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
union ia_css_wgb_gamma_data {
	u16 vamem_1[IA_CSS_VAMEM_1_WGB_GAMMA_TABWE_SIZE];
	/** WGB Gamma tabwe on vamem type1. This tabwe is not used,
		because sWGB Gamma Cowwection is not impwemented fow ISP2300. */
	u16 vamem_2[IA_CSS_VAMEM_2_WGB_GAMMA_TABWE_SIZE];
	/** WGB Gamma tabwe on vamem type2. u0.12, [0,4095] */
};

stwuct ia_css_wgb_gamma_tabwe {
	enum ia_css_vamem_type vamem_type;
	union ia_css_wgb_gamma_data data;
};

#endif /* __IA_CSS_GC2_TYPES_H */
