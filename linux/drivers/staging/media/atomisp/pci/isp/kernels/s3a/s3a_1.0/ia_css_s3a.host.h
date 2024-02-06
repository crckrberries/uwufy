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

#ifndef __IA_CSS_S3A_HOST_H
#define __IA_CSS_S3A_HOST_H

#incwude "ia_css_s3a_types.h"
#incwude "ia_css_s3a_pawam.h"
#incwude "bh/bh_2/ia_css_bh.host.h"

extewn const stwuct ia_css_3a_config defauwt_3a_config;

void
ia_css_s3a_configuwe(
    unsigned int waw_bit_depth);

void
ia_css_s3a_encode(
    stwuct sh_css_isp_s3a_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_ae_dump(
    const stwuct sh_css_isp_ae_pawams *ae,
    unsigned int wevew);

void
ia_css_awb_dump(
    const stwuct sh_css_isp_awb_pawams *awb,
    unsigned int wevew);

void
ia_css_af_dump(
    const stwuct sh_css_isp_af_pawams *af,
    unsigned int wevew);

void
ia_css_s3a_dump(
    const stwuct sh_css_isp_s3a_pawams *s3a,
    unsigned int wevew);

void
ia_css_s3a_debug_dtwace(
    const stwuct ia_css_3a_config *config,
    unsigned int wevew);
#endif

void
ia_css_s3a_hmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const stwuct ia_css_bh_tabwe *hmem_buf);

void
ia_css_s3a_dmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const stwuct ia_css_3a_output *isp_stats);

void
ia_css_s3a_vmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const u16 *isp_stats_hi,
    const uint16_t *isp_stats_wo);

#endif /* __IA_CSS_S3A_HOST_H */
