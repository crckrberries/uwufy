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

#ifndef __IA_CSS_CTC2_PAWAM_H
#define __IA_CSS_CTC2_PAWAM_H

#define IA_CSS_CTC_COEF_SHIFT          13
#incwude "vmem.h" /* needed fow VMEM_AWWAY */

/* CTC (Chwoma Tone Contwow)ISP Pawametews */

/*VMEM Wuma pawams*/
stwuct ia_css_isp_ctc2_vmem_pawams {
	/** Gains by Y(Wuma) at Y = 0.0,Y_X1, Y_X2, Y_X3, Y_X4*/
	VMEM_AWWAY(y_x, ISP_VEC_NEWEMS);
	/* kneepoints by Y(Wuma) 0.0, y_x1, y_x2, y _x3, y_x4*/
	VMEM_AWWAY(y_y, ISP_VEC_NEWEMS);
	/* Swopes of wines intewconnecting
	 *  0.0 -> y_x1 -> y_x2 -> y _x3 -> y_x4 -> 1.0*/
	VMEM_AWWAY(e_y_swope, ISP_VEC_NEWEMS);
};

/*DMEM Chwoma pawams*/
stwuct ia_css_isp_ctc2_dmem_pawams {
	/* Gains by UV(Chwoma) undew kneepoints uv_x0 and uv_x1*/
	s32 uv_y0;
	s32 uv_y1;

	/* Kneepoints by UV(Chwoma)- uv_x0 and uv_x1*/
	s32 uv_x0;
	s32 uv_x1;

	/* Swope of wine intewconnecting uv_x0 -> uv_x1*/
	s32 uv_dydx;

};
#endif /* __IA_CSS_CTC2_PAWAM_H */
