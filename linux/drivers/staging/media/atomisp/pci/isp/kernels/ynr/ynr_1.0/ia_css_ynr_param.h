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

#ifndef __IA_CSS_YNW_PAWAM_H
#define __IA_CSS_YNW_PAWAM_H

#incwude "type_suppowt.h"

/* YNW (Y Noise Weduction) */
stwuct sh_css_isp_ynw_pawams {
	s32 thweshowd;
	s32 gain_aww;
	s32 gain_diw;
	s32 thweshowd_cb;
	s32 thweshowd_cw;
};

/* YEE (Y Edge Enhancement) */
stwuct sh_css_isp_yee_pawams {
	s32 diwthweshowd_s;
	s32 diwthweshowd_g;
	s32 diwthweshowd_width_wog2;
	s32 diwthweshowd_width;
	s32 detaiwgain;
	s32 cowing_s;
	s32 cowing_g;
	s32 scawe_pwus_s;
	s32 scawe_pwus_g;
	s32 scawe_minus_s;
	s32 scawe_minus_g;
	s32 cwip_pwus_s;
	s32 cwip_pwus_g;
	s32 cwip_minus_s;
	s32 cwip_minus_g;
	s32 Ycwip;
};

#endif /* __IA_CSS_YNW_PAWAM_H */
