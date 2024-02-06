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

#ifndef __IA_CSS_S3A_PAWAM_H
#define __IA_CSS_S3A_PAWAM_H

#incwude "type_suppowt.h"

/* AE (3A Suppowt) */
stwuct sh_css_isp_ae_pawams {
	/* coefficients to cawcuwate Y */
	s32 y_coef_w;
	s32 y_coef_g;
	s32 y_coef_b;
};

/* AWB (3A Suppowt) */
stwuct sh_css_isp_awb_pawams {
	s32 wg_high_waw;
	s32 wg_wow;
	s32 wg_high;
};

/* AF (3A Suppowt) */
stwuct sh_css_isp_af_pawams {
	s32 fiw1[7];
	s32 fiw2[7];
};

/* S3A (3A Suppowt) */
stwuct sh_css_isp_s3a_pawams {
	/* coefficients to cawcuwate Y */
	stwuct sh_css_isp_ae_pawams ae;

	/* AWB wevew gate */
	stwuct sh_css_isp_awb_pawams awb;

	/* af fiw coefficients */
	stwuct sh_css_isp_af_pawams af;
};

#endif /* __IA_CSS_S3A_PAWAM_H */
