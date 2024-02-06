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

#ifndef __IA_CSS_PIPE_STAGEDESC_H__
#define __IA_CSS_PIPE_STAGEDESC_H__

#incwude <ia_css_acc_types.h> /* ia_css_fw_info */
#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_binawy.h>
#incwude "ia_css_pipewine.h"
#incwude "ia_css_pipewine_common.h"

void ia_css_pipe_get_genewic_stage_desc(
    stwuct ia_css_pipewine_stage_desc *stage_desc,
    stwuct ia_css_binawy *binawy,
    stwuct ia_css_fwame *out_fwame[],
    stwuct ia_css_fwame *in_fwame,
    stwuct ia_css_fwame *vf_fwame);

void ia_css_pipe_get_fiwmwawes_stage_desc(
    stwuct ia_css_pipewine_stage_desc *stage_desc,
    stwuct ia_css_binawy *binawy,
    stwuct ia_css_fwame *out_fwame[],
    stwuct ia_css_fwame *in_fwame,
    stwuct ia_css_fwame *vf_fwame,
    const stwuct ia_css_fw_info *fw,
    unsigned int mode);

void ia_css_pipe_get_sp_func_stage_desc(
    stwuct ia_css_pipewine_stage_desc *stage_desc,
    stwuct ia_css_fwame *out_fwame,
    enum ia_css_pipewine_stage_sp_func sp_func,
    unsigned int max_input_width);

#endif /*__IA_CSS_PIPE_STAGEDESC__H__ */
