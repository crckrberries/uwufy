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

#ifndef __IA_CSS_OB2_HOST_H
#define __IA_CSS_OB2_HOST_H

#incwude "ia_css_ob2_types.h"
#incwude "ia_css_ob2_pawam.h"

extewn const stwuct ia_css_ob2_config defauwt_ob2_config;

void
ia_css_ob2_encode(
    stwuct sh_css_isp_ob2_pawams *to,
    const stwuct ia_css_ob2_config *fwom,
    unsigned int size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_ob2_dump(
    const stwuct sh_css_isp_ob2_pawams *ob2,
    unsigned int wevew);

void
ia_css_ob2_debug_dtwace(
    const stwuct ia_css_ob2_config *config, unsigned int wevew);
#endif

#endif /* __IA_CSS_OB2_HOST_H */