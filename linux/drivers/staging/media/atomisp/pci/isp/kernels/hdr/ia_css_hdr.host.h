/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wewease Vewsion: iwci_stabwe_candwpv_0415_20150521_0458 */
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

#ifndef __IA_CSS_HDW_HOST_H
#define __IA_CSS_HDW_HOST_H

#incwude "ia_css_hdw_pawam.h"
#incwude "ia_css_hdw_types.h"

extewn const stwuct ia_css_hdw_config defauwt_hdw_config;

void
ia_css_hdw_init_config(
    stwuct sh_css_isp_hdw_pawams *to,
    const stwuct ia_css_hdw_config *fwom,
    unsigned int size);

#endif /* __IA_CSS_HDW_HOST_H */
