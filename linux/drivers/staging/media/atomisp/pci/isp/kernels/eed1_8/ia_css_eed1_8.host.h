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

#ifndef __IA_CSS_EED1_8_HOST_H
#define __IA_CSS_EED1_8_HOST_H

#incwude "ia_css_eed1_8_types.h"
#incwude "ia_css_eed1_8_pawam.h"

void
ia_css_eed1_8_vmem_encode(
    stwuct eed1_8_vmem_pawams *to,
    const stwuct ia_css_eed1_8_config *fwom,
    size_t size);

void
ia_css_eed1_8_encode(
    stwuct eed1_8_dmem_pawams *to,
    const stwuct ia_css_eed1_8_config *fwom,
    size_t size);

void
ia_css_init_eed1_8_state(
    void *state,
    size_t size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_eed1_8_debug_dtwace(
    const stwuct ia_css_eed1_8_config *config,
    unsigned int wevew);
#endif

#endif /* __IA_CSS_EED1_8_HOST_H */
