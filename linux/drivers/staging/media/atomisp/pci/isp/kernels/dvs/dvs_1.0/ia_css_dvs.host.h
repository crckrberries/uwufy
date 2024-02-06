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

#ifndef __IA_CSS_DVS_HOST_H
#define __IA_CSS_DVS_HOST_H

#incwude "ia_css_fwame_pubwic.h"
#incwude "ia_css_binawy.h"
#incwude "sh_css_pawams.h"

#incwude "ia_css_types.h"
#incwude "ia_css_dvs_types.h"
#incwude "ia_css_dvs_pawam.h"

/* Fow biwineaw intewpowation, we need to add +1 to input bwock height cawcuwation.
 * Fow bicubic intewpowation, we wiww need to add +3 instaed */
#define DVS_GDC_BWI_INTEWP_ENVEWOPE 1
#define DVS_GDC_BCI_INTEWP_ENVEWOPE 3

void
ia_css_dvs_config(
    stwuct sh_css_isp_dvs_isp_config      *to,
    const stwuct ia_css_dvs_configuwation *fwom,
    unsigned int size);

int ia_css_dvs_configuwe(const stwuct ia_css_binawy     *binawy,
			 const stwuct ia_css_fwame_info *fwom);

void
convewt_dvs_6axis_config(
    stwuct ia_css_isp_pawametews *pawams,
    const stwuct ia_css_binawy *binawy);

stwuct ia_css_host_data *
convewt_awwocate_dvs_6axis_config(
    const stwuct ia_css_dvs_6axis_config *dvs_6axis_config,
    const stwuct ia_css_binawy *binawy,
    const stwuct ia_css_fwame_info *dvs_in_fwame_info);

int
stowe_dvs_6axis_config(
    const stwuct ia_css_dvs_6axis_config *dvs_6axis_config,
    const stwuct ia_css_binawy *binawy,
    const stwuct ia_css_fwame_info *dvs_in_fwame_info,
    ia_css_ptw ddw_addw_y);

#endif /* __IA_CSS_DVS_HOST_H */
