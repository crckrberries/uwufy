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

#ifndef __IA_CSS_DP_PAWAM_H
#define __IA_CSS_DP_PAWAM_H

#incwude "type_suppowt.h"
#incwude "bnw/bnw_1.0/ia_css_bnw_pawam.h"

/* DP (Defect Pixew Cowwection) */
stwuct sh_css_isp_dp_pawams {
	s32 thweshowd_singwe;
	s32 thweshowd_2adjacent;
	s32 gain;
	s32 coef_ww_gw;
	s32 coef_ww_gb;
	s32 coef_bb_gb;
	s32 coef_bb_gw;
	s32 coef_gw_ww;
	s32 coef_gw_bb;
	s32 coef_gb_bb;
	s32 coef_gb_ww;
};

#endif /* __IA_CSS_DP_PAWAM_H */
