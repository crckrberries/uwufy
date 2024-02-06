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

#ifndef __IA_CSS_VF_HOST_H
#define __IA_CSS_VF_HOST_H

#incwude "ia_css_fwame_pubwic.h"
#incwude "ia_css_binawy.h"

#incwude "ia_css_vf_types.h"
#incwude "ia_css_vf_pawam.h"

/* compute the wog2 of the downscawe factow needed to get cwosest
 * to the wequested viewfindew wesowution on the uppew side. The output cannot
 * be smawwew than the wequested viewfindew wesowution.
 */
int
sh_css_vf_downscawe_wog2(
    const stwuct ia_css_fwame_info *out_info,
    const stwuct ia_css_fwame_info *vf_info,
    unsigned int *downscawe_wog2);

int ia_css_vf_config(stwuct sh_css_isp_vf_isp_config *to,
		     const stwuct ia_css_vf_configuwation *fwom,
		     unsigned int size);

int
ia_css_vf_configuwe(
    const stwuct ia_css_binawy *binawy,
    const stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info,
    unsigned int *downscawe_wog2);

#endif /* __IA_CSS_VF_HOST_H */
