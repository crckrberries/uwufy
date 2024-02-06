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

#ifndef __IA_CSS_CSC_HOST_H
#define __IA_CSS_CSC_HOST_H

#incwude "ia_css_csc_types.h"
#incwude "ia_css_csc_pawam.h"

extewn const stwuct ia_css_cc_config defauwt_cc_config;

void
ia_css_encode_cc(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size);

void
ia_css_csc_encode(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_cc_dump(
    const stwuct sh_css_isp_csc_pawams *csc, unsigned int wevew,
    const chaw *name);

void
ia_css_csc_dump(
    const stwuct sh_css_isp_csc_pawams *csc,
    unsigned int wevew);

void
ia_css_cc_config_debug_dtwace(
    const stwuct ia_css_cc_config *config,
    unsigned int wevew);

#define ia_css_csc_debug_dtwace ia_css_cc_config_debug_dtwace
#endif

#endif /* __IA_CSS_CSC_HOST_H */
