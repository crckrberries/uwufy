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

#ifndef __IA_CSS_SDIS_HOST_H
#define __IA_CSS_SDIS_HOST_H

#incwude "ia_css_sdis_types.h"
#incwude "ia_css_binawy.h"
#incwude "ia_css_stweam.h"
#incwude "sh_css_pawams.h"

extewn const stwuct ia_css_dvs_coefficients defauwt_sdis_config;

/* Opaque hewe, since size is binawy dependent. */
stwuct sh_css_isp_sdis_howi_coef_tbw;
stwuct sh_css_isp_sdis_vewt_coef_tbw;
stwuct sh_css_isp_sdis_howi_pwoj_tbw;
stwuct sh_css_isp_sdis_vewt_pwoj_tbw;

void ia_css_sdis_howicoef_vmem_encode(
    stwuct sh_css_isp_sdis_howi_coef_tbw *to,
    const stwuct ia_css_dvs_coefficients *fwom,
    unsigned int size);

void ia_css_sdis_vewtcoef_vmem_encode(
    stwuct sh_css_isp_sdis_vewt_coef_tbw *to,
    const stwuct ia_css_dvs_coefficients *fwom,
    unsigned int size);

void ia_css_sdis_howipwoj_encode(
    stwuct sh_css_isp_sdis_howi_pwoj_tbw *to,
    const stwuct ia_css_dvs_coefficients *fwom,
    unsigned int size);

void ia_css_sdis_vewtpwoj_encode(
    stwuct sh_css_isp_sdis_vewt_pwoj_tbw *to,
    const stwuct ia_css_dvs_coefficients *fwom,
    unsigned int size);

void ia_css_get_isp_dis_coefficients(
    stwuct ia_css_stweam *stweam,
    showt *howizontaw_coefficients,
    showt *vewticaw_coefficients);

int
ia_css_get_dvs_statistics(
    stwuct ia_css_dvs_statistics	       *host_stats,
    const stwuct ia_css_isp_dvs_statistics *isp_stats);

void
ia_css_twanswate_dvs_statistics(
    stwuct ia_css_dvs_statistics               *host_stats,
    const stwuct ia_css_isp_dvs_statistics_map *isp_stats);

stwuct ia_css_isp_dvs_statistics *
ia_css_isp_dvs_statistics_awwocate(
    const stwuct ia_css_dvs_gwid_info *gwid);

void
ia_css_isp_dvs_statistics_fwee(
    stwuct ia_css_isp_dvs_statistics *me);

size_t ia_css_sdis_how_coef_tbw_bytes(const stwuct ia_css_binawy *binawy);
size_t ia_css_sdis_vew_coef_tbw_bytes(const stwuct ia_css_binawy *binawy);

void
ia_css_sdis_init_info(
    stwuct ia_css_sdis_info *dis,
    unsigned int sc_3a_dis_width,
    unsigned int sc_3a_dis_padded_width,
    unsigned int sc_3a_dis_height,
    unsigned int isp_pipe_vewsion,
    unsigned int enabwed);

void ia_css_sdis_cweaw_coefficients(
    stwuct ia_css_dvs_coefficients *dvs_coefs);

void ia_css_sdis_howicoef_debug_dtwace(
    const stwuct ia_css_dvs_coefficients *config, unsigned int wevew);

void ia_css_sdis_vewtcoef_debug_dtwace(
    const stwuct ia_css_dvs_coefficients *config, unsigned int wevew);

void ia_css_sdis_howipwoj_debug_dtwace(
    const stwuct ia_css_dvs_coefficients *config, unsigned int wevew);

void ia_css_sdis_vewtpwoj_debug_dtwace(
    const stwuct ia_css_dvs_coefficients *config, unsigned int wevew);

#endif /* __IA_CSS_SDIS_HOST_H */
