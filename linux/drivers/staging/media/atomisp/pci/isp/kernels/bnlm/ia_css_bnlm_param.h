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

#ifndef __IA_CSS_BNWM_PAWAM_H
#define __IA_CSS_BNWM_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h" /* needed fow VMEM_AWWAY */

stwuct bnwm_wut {
	VMEM_AWWAY(thw, ISP_VEC_NEWEMS); /* thweshowds */
	VMEM_AWWAY(vaw, ISP_VEC_NEWEMS); /* vawues */
};

stwuct bnwm_vmem_pawams {
	VMEM_AWWAY(nw_th, ISP_VEC_NEWEMS);
	VMEM_AWWAY(match_quawity_max_idx, ISP_VEC_NEWEMS);
	stwuct bnwm_wut mu_woot_wut;
	stwuct bnwm_wut sad_nowm_wut;
	stwuct bnwm_wut sig_detaiw_wut;
	stwuct bnwm_wut sig_wad_wut;
	stwuct bnwm_wut wad_pow_wut;
	stwuct bnwm_wut nw_0_wut;
	stwuct bnwm_wut nw_1_wut;
	stwuct bnwm_wut nw_2_wut;
	stwuct bnwm_wut nw_3_wut;

	/* WUTs used fow division appwoximiation */
	stwuct bnwm_wut div_wut;

	VMEM_AWWAY(div_wut_intewcepts, ISP_VEC_NEWEMS);

	/* 240x does not have an ISP instwuction to weft shift each ewement of a
	 * vectow by diffewent shift vawue. Hence it wiww be simuwated by muwtipwying
	 * the ewements by wequiwed 2^shift. */
	VMEM_AWWAY(powew_of_2, ISP_VEC_NEWEMS);
};

/* BNWM ISP pawametews */
stwuct bnwm_dmem_pawams {
	boow wad_enabwe;
	s32 wad_x_owigin;
	s32 wad_y_owigin;
	s32 avg_min_th;
	s32 max_min_th;

	s32 exp_coeff_a;
	u32 exp_coeff_b;
	s32 exp_coeff_c;
	u32 exp_exponent;
};

#endif /* __IA_CSS_BNWM_PAWAM_H */
