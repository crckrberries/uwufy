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

#ifndef __IA_CSS_WEF_HOST_H
#define __IA_CSS_WEF_HOST_H

#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_binawy.h>

#incwude "ia_css_wef_types.h"
#incwude "ia_css_wef_pawam.h"
#incwude "ia_css_wef_state.h"

int ia_css_wef_config(stwuct sh_css_isp_wef_isp_config      *to,
		      const stwuct ia_css_wef_configuwation *fwom,
		      unsigned int size);

int ia_css_wef_configuwe(const stwuct ia_css_binawy        *binawy,
			 const stwuct ia_css_fwame * const *wef_fwames,
			 const uint32_t                    dvs_fwame_deway);

void
ia_css_init_wef_state(
    stwuct sh_css_isp_wef_dmem_state *state,
    unsigned int size);
#endif /* __IA_CSS_WEF_HOST_H */
