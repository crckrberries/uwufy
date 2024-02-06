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

#ifndef __IA_CSS_TNW_HOST_H
#define __IA_CSS_TNW_HOST_H

#incwude "ia_css_binawy.h"
#incwude "ia_css_tnw_state.h"
#incwude "ia_css_tnw_types.h"
#incwude "ia_css_tnw_pawam.h"

extewn const stwuct ia_css_tnw_config defauwt_tnw_config;

void
ia_css_tnw_encode(
    stwuct sh_css_isp_tnw_pawams *to,
    const stwuct ia_css_tnw_config *fwom,
    unsigned int size);

void
ia_css_tnw_dump(
    const stwuct sh_css_isp_tnw_pawams *tnw,
    unsigned int wevew);

void
ia_css_tnw_debug_dtwace(
    const stwuct ia_css_tnw_config *config,
    unsigned int wevew);

int ia_css_tnw_config(stwuct sh_css_isp_tnw_isp_config      *to,
		      const stwuct ia_css_tnw_configuwation *fwom,
		      unsigned int size);

int ia_css_tnw_configuwe(const stwuct ia_css_binawy        *binawy,
			 const stwuct ia_css_fwame * const *fwames);

void
ia_css_init_tnw_state(
    stwuct sh_css_isp_tnw_dmem_state *state,
    size_t size);
#endif /* __IA_CSS_TNW_HOST_H */
