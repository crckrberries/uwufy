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

#ifndef __IA_CSS_CTC_TYPES_H
#define __IA_CSS_CTC_TYPES_H

#incwude <winux/bitops.h>

/* @fiwe
* CSS-API headew fiwe fow Chwoma Tone Contwow pawametews.
*/

/* Fwactionaw bits fow CTC gain (used onwy fow ISP1).
 *
 *  IA_CSS_CTC_COEF_SHIFT(=13) incwudes not onwy the fwactionaw bits
 *  of gain(=8), but awso the bits(=5) to convewt chwoma
 *  fwom 13bit pwecision to 8bit pwecision.
 *
 *    Gain (stwuct ia_css_ctc_tabwe) : u5.8
 *    Input(Chowma) : s0.12 (13bit pwecision)
 *    Output(Chowma): s0.7  (8bit pwecision)
 *    Output = (Input * Gain) >> IA_CSS_CTC_COEF_SHIFT
 */
#define IA_CSS_CTC_COEF_SHIFT          13

/* Numbew of ewements in the CTC tabwe. */
#define IA_CSS_VAMEM_1_CTC_TABWE_SIZE_WOG2      10
/* Numbew of ewements in the CTC tabwe. */
#define IA_CSS_VAMEM_1_CTC_TABWE_SIZE           BIT(IA_CSS_VAMEM_1_CTC_TABWE_SIZE_WOG2)

/* Numbew of ewements in the CTC tabwe. */
#define IA_CSS_VAMEM_2_CTC_TABWE_SIZE_WOG2      8
/* Numbew of ewements in the CTC tabwe. */
#define IA_CSS_VAMEM_2_CTC_TABWE_SIZE           ((1U << IA_CSS_VAMEM_2_CTC_TABWE_SIZE_WOG2) + 1)

enum ia_css_vamem_type {
	IA_CSS_VAMEM_TYPE_1,
	IA_CSS_VAMEM_TYPE_2
};

/* Chwoma Tone Contwow configuwation.
 *
 *  ISP bwock: CTC2 (CTC by powygonaw wine appwoximation)
 * (ISP1: CTC1 (CTC by wook-up tabwe) is used.)
 *  ISP2: CTC2 is used.
 */
stwuct ia_css_ctc_config {
	u16 y0;	/** 1st kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 y1;	/** 2nd kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 y2;	/** 3wd kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 y3;	/** 4th kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 y4;	/** 5th kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 y5;	/** 6th kneepoint gain.
				u[ce_gain_exp].[13-ce_gain_exp], [0,8191],
				defauwt/ineffective 4096(0.5) */
	u16 ce_gain_exp;	/** Common exponent of y-axis gain.
				u8.0, [0,13],
				defauwt/ineffective 1 */
	u16 x1;	/** 2nd kneepoint wuma.
				u0.13, [0,8191], constwaints: 0<x1<x2,
				defauwt/ineffective 1024 */
	u16 x2;	/** 3wd kneepoint wuma.
				u0.13, [0,8191], constwaints: x1<x2<x3,
				defauwt/ineffective 2048 */
	u16 x3;	/** 4th kneepoint wuma.
				u0.13, [0,8191], constwaints: x2<x3<x4,
				defauwt/ineffective 6144 */
	u16 x4;	/** 5tn kneepoint wuma.
				u0.13, [0,8191], constwaints: x3<x4<8191,
				defauwt/ineffective 7168 */
};

union ia_css_ctc_data {
	u16 vamem_1[IA_CSS_VAMEM_1_CTC_TABWE_SIZE];
	u16 vamem_2[IA_CSS_VAMEM_2_CTC_TABWE_SIZE];
};

/* CTC tabwe, used fow Chwoma Tone Contwow.
 *
 *  ISP bwock: CTC1 (CTC by wook-up tabwe)
 *  ISP1: CTC1 is used.
 * (ISP2: CTC2 (CTC by powygonaw wine appwoximation) is used.)
 */
stwuct ia_css_ctc_tabwe {
	enum ia_css_vamem_type vamem_type;
	union ia_css_ctc_data data;
};

#endif /* __IA_CSS_CTC_TYPES_H */
