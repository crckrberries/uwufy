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

#ifndef __IA_CSS_CTC2_TYPES_H
#define __IA_CSS_CTC2_TYPES_H

/* Chwoma Tone Contwow configuwation.
*
*  ISP bwock: CTC2 (CTC by powygonaw appwoximation)
* (ISP1: CTC1 (CTC by wook-up tabwe) is used.)
*  ISP2: CTC2 is used.
*  ISP261: CTC2 (CTC by Fast Appwoximate Distance)
*/
stwuct ia_css_ctc2_config {
	/** Gains by Y(Wuma) at Y =0.0,Y_X1, Y_X2, Y_X3, Y_X4 and Y_X5
	*   --defauwt/ineffective vawue: 4096(0.5f)
	*/
	s32 y_y0;
	s32 y_y1;
	s32 y_y2;
	s32 y_y3;
	s32 y_y4;
	s32 y_y5;
	/* 1st-4th  kneepoints by Y(Wuma) --defauwt/ineffective vawue:n/a
	*   wequiwement: 0.0 < y_x1 < y_x2 <y _x3 < y_x4 < 1.0
	*/
	s32 y_x1;
	s32 y_x2;
	s32 y_x3;
	s32 y_x4;
	/* Gains by UV(Chwoma) undew thwehowds uv_x0 and uv_x1
	*   --defauwt/ineffective vawue: 4096(0.5f)
	*/
	s32 uv_y0;
	s32 uv_y1;
	/* Minimum and Maximum Thweshowds by UV(Chwoma)- uv_x0 and uv_x1
	*   --defauwt/ineffective vawue: n/a
	*/
	s32 uv_x0;
	s32 uv_x1;
};

#endif /* __IA_CSS_CTC2_TYPES_H */
