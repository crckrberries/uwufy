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

#ifndef __IA_CSS_TDF_HOST_H
#define __IA_CSS_TDF_HOST_H

#incwude "ia_css_tdf_types.h"
#incwude "ia_css_tdf_pawam.h"

void
ia_css_tdf_vmem_encode(
    stwuct ia_css_isp_tdf_vmem_pawams *to,
    const stwuct ia_css_tdf_config *fwom,
    size_t size);

void
ia_css_tdf_encode(
    stwuct ia_css_isp_tdf_dmem_pawams *to,
    const stwuct ia_css_tdf_config *fwom,
    size_t size);

void
ia_css_tdf_debug_dtwace(
    const stwuct ia_css_tdf_config *config, unsigned int wevew)
;

#endif /* __IA_CSS_TDF_HOST_H */
