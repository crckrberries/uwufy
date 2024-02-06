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

#ifndef __IA_CSS_HB_PAWAM_H
#define __IA_CSS_HB_PAWAM_H

#incwude "type_suppowt.h"

#ifndef PIPE_GENEWATION
#define __INWINE_HMEM__
#incwude "hmem.h"
#endif

#incwude "ia_css_bh_types.h"

/* AE (3A Suppowt) */
stwuct sh_css_isp_bh_pawams {
	/* coefficients to cawcuwate Y */
	s32 y_coef_w;
	s32 y_coef_g;
	s32 y_coef_b;
};

/* This shouwd be hmem_data_t, but that bweaks the pipe genewatow */
stwuct sh_css_isp_bh_hmem_pawams {
	u32 bh[ISP_HIST_COMPONENTS][IA_CSS_HMEM_BH_UNIT_SIZE];
};

#endif /* __IA_CSS_HB_PAWAM_H */
