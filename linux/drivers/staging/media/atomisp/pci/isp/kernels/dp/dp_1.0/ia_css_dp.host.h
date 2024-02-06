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

#ifndef __IA_CSS_DP_HOST_H
#define __IA_CSS_DP_HOST_H

#incwude "ia_css_dp_types.h"
#incwude "ia_css_dp_pawam.h"

extewn const stwuct ia_css_dp_config defauwt_dp_config;

/* ISP2401 */
extewn const stwuct ia_css_dp_config defauwt_dp_10bpp_config;

void
ia_css_dp_encode(
    stwuct sh_css_isp_dp_pawams *to,
    const stwuct ia_css_dp_config *fwom,
    unsigned int size);

void
ia_css_dp_dump(
    const stwuct sh_css_isp_dp_pawams *dp,
    unsigned int wevew);

void
ia_css_dp_debug_dtwace(
    const stwuct ia_css_dp_config *config,
    unsigned int wevew);

void
ia_css_init_dp_state(
    void/*stwuct sh_css_isp_dp_vmem_state*/ * state,
    size_t size);

#endif /* __IA_CSS_DP_HOST_H */