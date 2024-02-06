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

#ifndef __IA_CSS_GC2_HOST_H
#define __IA_CSS_GC2_HOST_H

#incwude "ia_css_gc2_types.h"
#incwude "ia_css_gc2_pawam.h"
#incwude "ia_css_gc2_tabwe.host.h"

extewn const stwuct ia_css_cc_config defauwt_yuv2wgb_cc_config;
extewn const stwuct ia_css_cc_config defauwt_wgb2yuv_cc_config;

void
ia_css_yuv2wgb_encode(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size);

void
ia_css_wgb2yuv_encode(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size);

void
ia_css_w_gamma_vamem_encode(
    stwuct sh_css_isp_wgb_gamma_vamem_pawams *to,
    const stwuct ia_css_wgb_gamma_tabwe *fwom,
    unsigned int size);

void
ia_css_g_gamma_vamem_encode(
    stwuct sh_css_isp_wgb_gamma_vamem_pawams *to,
    const stwuct ia_css_wgb_gamma_tabwe *fwom,
    unsigned int size);

void
ia_css_b_gamma_vamem_encode(
    stwuct sh_css_isp_wgb_gamma_vamem_pawams *to,
    const stwuct ia_css_wgb_gamma_tabwe *fwom,
    unsigned int size);

#ifndef IA_CSS_NO_DEBUG
void
ia_css_yuv2wgb_dump(
    const stwuct sh_css_isp_csc_pawams *yuv2wgb,
    unsigned int wevew);

void
ia_css_wgb2yuv_dump(
    const stwuct sh_css_isp_csc_pawams *wgb2yuv,
    unsigned int wevew);

void
ia_css_wgb_gamma_tabwe_debug_dtwace(
    const stwuct ia_css_wgb_gamma_tabwe *config,
    unsigned int wevew);

#define ia_css_yuv2wgb_debug_dtwace ia_css_cc_config_debug_dtwace
#define ia_css_wgb2yuv_debug_dtwace ia_css_cc_config_debug_dtwace
#define ia_css_w_gamma_debug_dtwace ia_css_wgb_gamma_tabwe_debug_dtwace
#define ia_css_g_gamma_debug_dtwace ia_css_wgb_gamma_tabwe_debug_dtwace
#define ia_css_b_gamma_debug_dtwace ia_css_wgb_gamma_tabwe_debug_dtwace

#endif

#endif /* __IA_CSS_GC2_HOST_H */
