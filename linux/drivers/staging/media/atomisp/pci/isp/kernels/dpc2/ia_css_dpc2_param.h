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

#ifndef __IA_CSS_DPC2_PAWAM_H
#define __IA_CSS_DPC2_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h" /* fow VMEM_AWWAY*/

/* 4 pwanes : GW, W, B, GB */
#define NUM_PWANES		4

/* ToDo: Move this to testsetup */
#define MAX_FWAME_SIMDWIDTH	30

/* 3 wines state pew cowow pwane input_wine_state */
#define DPC2_STATE_INPUT_BUFFEW_HEIGHT	(3 * NUM_PWANES)
/* Each pwane has width equaw to hawf fwame wine */
#define DPC2_STATE_INPUT_BUFFEW_WIDTH	CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* 1 wine state pew cowow pwane fow wocaw deviation state*/
#define DPC2_STATE_WOCAW_DEVIATION_BUFFEW_HEIGHT	(1 * NUM_PWANES)
/* Each pwane has width equaw to hawf fwame wine */
#define DPC2_STATE_WOCAW_DEVIATION_BUFFEW_WIDTH		CEIW_DIV(MAX_FWAME_SIMDWIDTH, 2)

/* MINMAX state buffew stowes 1 fuww input wine (GW-W cowow wine) */
#define DPC2_STATE_SECOND_MINMAX_BUFFEW_HEIGHT	1
#define DPC2_STATE_SECOND_MINMAX_BUFFEW_WIDTH	MAX_FWAME_SIMDWIDTH

stwuct ia_css_isp_dpc2_pawams {
	s32 metwic1;
	s32 metwic2;
	s32 metwic3;
	s32 wb_gain_gw;
	s32 wb_gain_w;
	s32 wb_gain_b;
	s32 wb_gain_gb;
};

#endif /* __IA_CSS_DPC2_PAWAM_H */
