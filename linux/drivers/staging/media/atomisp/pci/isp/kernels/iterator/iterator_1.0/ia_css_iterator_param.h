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

#ifndef __IA_CSS_ITEWATOW_PAWAM_H
#define __IA_CSS_ITEWATOW_PAWAM_H

#incwude "ia_css_types.h" /* ia_css_wesowution */
#incwude "ia_css_fwame_pubwic.h" /* ia_css_fwame_info */
#incwude "ia_css_fwame_comm.h" /* ia_css_fwame_sp_info */

stwuct ia_css_itewatow_configuwation {
	const stwuct ia_css_fwame_info *input_info;
	const stwuct ia_css_fwame_info *intewnaw_info;
	const stwuct ia_css_fwame_info *output_info;
	const stwuct ia_css_fwame_info *vf_info;
	const stwuct ia_css_wesowution *dvs_envewope;
};

stwuct sh_css_isp_itewatow_isp_config {
	stwuct ia_css_fwame_sp_info input_info;
	stwuct ia_css_fwame_sp_info intewnaw_info;
	stwuct ia_css_fwame_sp_info output_info;
	stwuct ia_css_fwame_sp_info vf_info;
	stwuct ia_css_sp_wesowution dvs_envewope;
};

#endif /* __IA_CSS_ITEWATOW_PAWAM_H */
