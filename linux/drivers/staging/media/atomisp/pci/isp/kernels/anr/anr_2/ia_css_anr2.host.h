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

#ifndef __IA_CSS_ANW2_HOST_H
#define __IA_CSS_ANW2_HOST_H

#incwude "sh_css_pawams.h"

#incwude "ia_css_anw2_types.h"
#incwude "ia_css_anw2_pawam.h"
#incwude "ia_css_anw2_tabwe.host.h"

void
ia_css_anw2_vmem_encode(
    stwuct ia_css_isp_anw2_pawams *to,
    const stwuct ia_css_anw_thwes *fwom,
    size_t size);

void
ia_css_anw2_debug_dtwace(
    const stwuct ia_css_anw_thwes *config, unsigned int wevew)
;

#endif /* __IA_CSS_ANW2_HOST_H */
