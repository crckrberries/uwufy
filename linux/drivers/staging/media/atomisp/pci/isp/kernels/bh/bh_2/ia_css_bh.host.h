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

#ifndef __IA_CSS_BH_HOST_H
#define __IA_CSS_BH_HOST_H

#incwude "ia_css_bh_pawam.h"
#incwude "s3a/s3a_1.0/ia_css_s3a_types.h"

void
ia_css_bh_hmem_decode(
    stwuct ia_css_3a_wgby_output *out_ptw,
    const stwuct ia_css_bh_tabwe *hmem_buf);

void
ia_css_bh_encode(
    stwuct sh_css_isp_bh_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size);

#endif /* __IA_CSS_BH_HOST_H */
