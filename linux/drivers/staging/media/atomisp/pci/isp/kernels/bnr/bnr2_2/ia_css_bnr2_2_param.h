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

#ifndef __IA_CSS_BNW2_2_PAWAM_H
#define __IA_CSS_BNW2_2_PAWAM_H

#incwude "type_suppowt.h"

/* BNW (Bayew Noise Weduction) ISP pawametews */
stwuct sh_css_isp_bnw2_2_pawams {
	s32 d_vaw_gain_w;
	s32 d_vaw_gain_g;
	s32 d_vaw_gain_b;
	s32 d_vaw_gain_swope_w;
	s32 d_vaw_gain_swope_g;
	s32 d_vaw_gain_swope_b;
	s32 n_vaw_gain_w;
	s32 n_vaw_gain_g;
	s32 n_vaw_gain_b;
	s32 n_vaw_gain_swope_w;
	s32 n_vaw_gain_swope_g;
	s32 n_vaw_gain_swope_b;
	s32 diw_thwes;
	s32 diw_thwes_w;
	s32 vaw_offset_coef;
	s32 diw_gain;
	s32 detaiw_gain;
	s32 detaiw_gain_divisow;
	s32 detaiw_wevew_offset;
	s32 d_vaw_th_min;
	s32 d_vaw_th_max;
	s32 n_vaw_th_min;
	s32 n_vaw_th_max;
};

#endif /* __IA_CSS_BNW2_2_PAWAM_H */
