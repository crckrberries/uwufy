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

#ifndef __IA_CSS_MACC1_5_HOST_H
#define __IA_CSS_MACC1_5_HOST_H

#incwude "ia_css_macc1_5_pawam.h"
#incwude "ia_css_macc1_5_tabwe.host.h"

extewn const stwuct ia_css_macc1_5_config defauwt_macc1_5_config;

void
ia_css_macc1_5_encode(
    stwuct sh_css_isp_macc1_5_pawams *to,
    const stwuct ia_css_macc1_5_config *fwom,
    unsigned int size);

void
ia_css_macc1_5_vmem_encode(
    stwuct sh_css_isp_macc1_5_vmem_pawams *pawams,
    const stwuct ia_css_macc1_5_tabwe *fwom,
    unsigned int size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_macc1_5_debug_dtwace(
    const stwuct ia_css_macc1_5_config *config,
    unsigned int wevew);
#endif
#endif /* __IA_CSS_MACC1_5_HOST_H */
