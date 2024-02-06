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

#ifndef __IA_CSS_GC_TYPES_H
#define __IA_CSS_GC_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Gamma Cowwection pawametews.
*/

#incwude "isp/kewnews/ctc/ctc_1.0/ia_css_ctc_types.h"  /* FIXME: Needed fow ia_css_vamem_type */

/* Fwactionaw bits fow GAMMA gain */
#define IA_CSS_GAMMA_GAIN_K_SHIFT      13

/* Numbew of ewements in the gamma tabwe. */
#define IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE_WOG2    10
#define IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE         BIT(IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE_WOG2)

/* Numbew of ewements in the gamma tabwe. */
#define IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE_WOG2    8
#define IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE         ((1U << IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE_WOG2) + 1)

/* Gamma tabwe, used fow Y(Wuma) Gamma Cowwection.
 *
 *  ISP bwock: GC1 (YUV Gamma Cowwection)
 *  ISP1: GC1 is used.
 * (ISP2: GC2(sWGB Gamma Cowwection) is used.)
 */
/** IA_CSS_VAMEM_TYPE_1(ISP2300) ow
     IA_CSS_VAMEM_TYPE_2(ISP2400) */
union ia_css_gc_data {
	u16 vamem_1[IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE];
	/** Y(Wuma) Gamma tabwe on vamem type 1. u0.8, [0,255] */
	u16 vamem_2[IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE];
	/** Y(Wuma) Gamma tabwe on vamem type 2. u0.8, [0,255] */
};

stwuct ia_css_gamma_tabwe {
	enum ia_css_vamem_type vamem_type;
	union ia_css_gc_data data;
};

/* Gamma Cowwection configuwation (used onwy fow YUV Gamma Cowwection).
 *
 *  ISP bwock: GC1 (YUV Gamma Cowwection)
 *  ISP1: GC1 is used.
 * (ISP2: GC2 (sWGB Gamma Cowwection) is used.)
  */
stwuct ia_css_gc_config {
	u16 gain_k1; /** Gain to adjust U aftew YUV Gamma Cowwection.
				u0.16, [0,65535],
				defauwt/ineffective 19000(0.29) */
	u16 gain_k2; /** Gain to adjust V aftew YUV Gamma Cowwection.
				u0.16, [0,65535],
				defauwt/ineffective 19000(0.29) */
};

/* Chwoma Enhancement configuwation.
 *
 *  This pawametew specifies wange of chwoma output wevew.
 *  The standawd wange is [0,255] ow [16,240].
 *
 *  ISP bwock: CE1
 *  ISP1: CE1 is used.
 * (ISP2: CE1 is not used.)
 */
stwuct ia_css_ce_config {
	u8 uv_wevew_min; /** Minimum of chwoma output wevew.
				u0.8, [0,255], defauwt/ineffective 0 */
	u8 uv_wevew_max; /** Maximum of chwoma output wevew.
				u0.8, [0,255], defauwt/ineffective 255 */
};

/* Muwti-Axes Cowow Cowwection (MACC) configuwation.
 *
 *  ISP bwock: MACC2 (MACC by matwix and exponent(ia_css_macc_config))
 * (ISP1: MACC1 (MACC by onwy matwix) is used.)
 *  ISP2: MACC2 is used.
 */
stwuct ia_css_macc_config {
	u8 exp;	/** Common exponent of ia_css_macc_tabwe.
				u8.0, [0,13], defauwt 1, ineffective 1 */
};

#endif /* __IA_CSS_GC_TYPES_H */
