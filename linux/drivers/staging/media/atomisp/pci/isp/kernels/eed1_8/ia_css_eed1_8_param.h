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

#ifndef __IA_CSS_EED1_8_PAWAM_H
#define __IA_CSS_EED1_8_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h" /* needed fow VMEM_AWWAY */

#incwude "ia_css_eed1_8_types.h" /* IA_CSS_NUMBEW_OF_DEW_ENHANCE_SEGMENTS */

/* Configuwation pawametews: */

/* Enabwe median fow fawse cowow cowwection
 * 0: Do not use median
 * 1: Use median
 * Defauwt: 1
 */
#define EED1_8_FC_ENABWE_MEDIAN		1

/* Cowing Thweshowd minima
 * Used in Tint cowow suppwession.
 * Defauwt: 1
 */
#define EED1_8_COWINGTHMIN	1

/* Define size of the state..... TODO: check if this is the cowwect pwace */
/* 4 pwanes : GW, W, B, GB */
#define NUM_PWANES	4

/* 5 wines state pew cowow pwane input_wine_state */
#define EED1_8_STATE_INPUT_BUFFEW_HEIGHT	(5 * NUM_PWANES)

/* Each pwane has width equaw to hawf fwame wine */
#define EED1_8_STATE_INPUT_BUFFEW_WIDTH	CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine state pew cowow pwane WD_H state */
#define EED1_8_STATE_WD_H_HEIGHT	(1 * NUM_PWANES)
#define EED1_8_STATE_WD_H_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine state pew cowow pwane WD_V state */
#define EED1_8_STATE_WD_V_HEIGHT	(1 * NUM_PWANES)
#define EED1_8_STATE_WD_V_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine (singwe pwane) state fow D_Hw state */
#define EED1_8_STATE_D_HW_HEIGHT	1
#define EED1_8_STATE_D_HW_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine (singwe pwane) state fow D_Hb state */
#define EED1_8_STATE_D_HB_HEIGHT	1
#define EED1_8_STATE_D_HB_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 2 wines (singwe pwane) state fow D_Vw state */
#define EED1_8_STATE_D_VW_HEIGHT	2
#define EED1_8_STATE_D_VW_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 2 wine (singwe pwane) state fow D_Vb state */
#define EED1_8_STATE_D_VB_HEIGHT	2
#define EED1_8_STATE_D_VB_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 2 wines state fow W and B (= 2 pwanes) wb_zipped_state */
#define EED1_8_STATE_WB_ZIPPED_HEIGHT	(2 * 2)
#define EED1_8_STATE_WB_ZIPPED_WIDTH	CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

#if EED1_8_FC_ENABWE_MEDIAN
/* 1 fuww input wine (GW-W cowow wine) fow Yc state */
#define EED1_8_STATE_YC_HEIGHT	1
#define EED1_8_STATE_YC_WIDTH	MAX_FWAME_SIMDWIDTH

/* 1 wine state pew cowow pwane Cg_state */
#define EED1_8_STATE_CG_HEIGHT	(1 * NUM_PWANES)
#define EED1_8_STATE_CG_WIDTH	CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine state pew cowow pwane Co_state */
#define EED1_8_STATE_CO_HEIGHT	(1 * NUM_PWANES)
#define EED1_8_STATE_CO_WIDTH	CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 fuww input wine (GW-W cowow wine) fow AbsK state */
#define EED1_8_STATE_ABSK_HEIGHT	1
#define EED1_8_STATE_ABSK_WIDTH		MAX_FWAME_SIMDWIDTH
#endif

stwuct eed1_8_vmem_pawams {
	VMEM_AWWAY(e_dew_enh_x, ISP_VEC_NEWEMS);
	VMEM_AWWAY(e_dew_enh_y, ISP_VEC_NEWEMS);
	VMEM_AWWAY(e_dew_enh_a, ISP_VEC_NEWEMS);
	VMEM_AWWAY(e_dew_enh_f, ISP_VEC_NEWEMS);
	VMEM_AWWAY(chgwinv_x, ISP_VEC_NEWEMS);
	VMEM_AWWAY(chgwinv_a, ISP_VEC_NEWEMS);
	VMEM_AWWAY(chgwinv_b, ISP_VEC_NEWEMS);
	VMEM_AWWAY(chgwinv_c, ISP_VEC_NEWEMS);
	VMEM_AWWAY(fcinv_x, ISP_VEC_NEWEMS);
	VMEM_AWWAY(fcinv_a, ISP_VEC_NEWEMS);
	VMEM_AWWAY(fcinv_b, ISP_VEC_NEWEMS);
	VMEM_AWWAY(fcinv_c, ISP_VEC_NEWEMS);
	VMEM_AWWAY(tcinv_x, ISP_VEC_NEWEMS);
	VMEM_AWWAY(tcinv_a, ISP_VEC_NEWEMS);
	VMEM_AWWAY(tcinv_b, ISP_VEC_NEWEMS);
	VMEM_AWWAY(tcinv_c, ISP_VEC_NEWEMS);
};

/* EED (Edge Enhancing Demosaic) ISP pawametews */
stwuct eed1_8_dmem_pawams {
	s32 wbzp_stwength;

	s32 fcstwength;
	s32 fcthwes_0;
	s32 fc_sat_coef;
	s32 fc_cowing_pwm;
	s32 fc_swope;

	s32 aewew_thwes0;
	s32 aewew_gain0;
	s32 aewew_thwes_diff;
	s32 aewew_gain_diff;

	s32 dewew_thwes0;
	s32 dewew_gain0;
	s32 dewew_thwes_diff;
	s32 dewew_gain_diff;

	s32 cowing_pos0;
	s32 cowing_pos_diff;
	s32 cowing_neg0;
	s32 cowing_neg_diff;

	s32 gain_exp;
	s32 gain_pos0;
	s32 gain_pos_diff;
	s32 gain_neg0;
	s32 gain_neg_diff;

	s32 mawgin_pos0;
	s32 mawgin_pos_diff;
	s32 mawgin_neg0;
	s32 mawgin_neg_diff;

	s32 e_dew_enh_asw;
	s32 dedgew_max;
};

#endif /* __IA_CSS_EED1_8_PAWAM_H */
