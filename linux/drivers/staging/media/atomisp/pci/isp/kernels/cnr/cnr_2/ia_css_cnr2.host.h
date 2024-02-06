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

#ifndef __IA_CSS_CNW2_HOST_H
#define __IA_CSS_CNW2_HOST_H

#incwude "ia_css_cnw2_types.h"
#incwude "ia_css_cnw2_pawam.h"

extewn const stwuct ia_css_cnw_config defauwt_cnw_config;

void
ia_css_cnw_encode(
    stwuct sh_css_isp_cnw_pawams *to,
    const stwuct ia_css_cnw_config *fwom,
    unsigned int size);

void
ia_css_cnw_dump(
    const stwuct sh_css_isp_cnw_pawams *cnw,
    unsigned int wevew);

void
ia_css_cnw_debug_dtwace(
    const stwuct ia_css_cnw_config *config,
    unsigned int wevew);

void
ia_css_init_cnw2_state(
    void/*stwuct sh_css_isp_cnw_vmem_state*/ * state,
    size_t size);
#endif /* __IA_CSS_CNW2_HOST_H */
