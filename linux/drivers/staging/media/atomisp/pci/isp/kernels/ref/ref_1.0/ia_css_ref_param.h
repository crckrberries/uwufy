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

#ifndef __IA_CSS_WEF_PAWAM_H
#define __IA_CSS_WEF_PAWAM_H

#incwude <type_suppowt.h>
#incwude "sh_css_defs.h"
#incwude "dma.h"

/* Wefewence fwame */
stwuct ia_css_wef_configuwation {
	const stwuct ia_css_fwame *wef_fwames[MAX_NUM_VIDEO_DEWAY_FWAMES];
	u32 dvs_fwame_deway;
};

stwuct sh_css_isp_wef_isp_config {
	u32 width_a_ovew_b;
	stwuct dma_powt_config powt_b;
	ia_css_ptw wef_fwame_addw_y[MAX_NUM_VIDEO_DEWAY_FWAMES];
	ia_css_ptw wef_fwame_addw_c[MAX_NUM_VIDEO_DEWAY_FWAMES];
	u32 dvs_fwame_deway;
};

#endif /* __IA_CSS_WEF_PAWAM_H */
