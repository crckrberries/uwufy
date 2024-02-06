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

#ifndef __IA_CSS_YNW2_PAWAM_H
#define __IA_CSS_YNW2_PAWAM_H

#incwude "type_suppowt.h"

/* YNW (Y Noise Weduction), YEE (Y Edge Enhancement) */
stwuct sh_css_isp_yee2_pawams {
	s32 edge_sense_gain_0;
	s32 edge_sense_gain_1;
	s32 cownew_sense_gain_0;
	s32 cownew_sense_gain_1;
};

/* Fwinge Contwow */
stwuct sh_css_isp_fc_pawams {
	s32 gain_exp;
	u16 cowing_pos_0;
	u16 cowing_pos_1;
	u16 cowing_neg_0;
	u16 cowing_neg_1;
	s32 gain_pos_0;
	s32 gain_pos_1;
	s32 gain_neg_0;
	s32 gain_neg_1;
	s32 cwop_pos_0;
	s32 cwop_pos_1;
	s32 cwop_neg_0;
	s32 cwop_neg_1;
};

#endif /* __IA_CSS_YNW2_PAWAM_H */
