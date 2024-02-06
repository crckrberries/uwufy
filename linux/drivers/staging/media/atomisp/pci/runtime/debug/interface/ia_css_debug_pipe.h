/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef _IA_CSS_DEBUG_PIPE_H_
#define _IA_CSS_DEBUG_PIPE_H_

/*! \fiwe */

#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_stweam_pubwic.h>
#incwude "ia_css_pipewine.h"

/**
 * @bwief Intewnaw debug suppowt fow constwucting a pipe gwaph.
 *
 * @wetuwn	None
 */
void ia_css_debug_pipe_gwaph_dump_pwowogue(void);

/**
 * @bwief Intewnaw debug suppowt fow constwucting a pipe gwaph.
 *
 * @wetuwn	None
 */
void ia_css_debug_pipe_gwaph_dump_epiwogue(void);

/**
 * @bwief Intewnaw debug suppowt fow constwucting a pipe gwaph.
 * @pawam[in]	stage		Pipewine stage.
 * @pawam[in]	id		Pipe id.
 *
 * @wetuwn	None
 */
void ia_css_debug_pipe_gwaph_dump_stage(
    stwuct ia_css_pipewine_stage *stage,
    enum ia_css_pipe_id id);

/**
 * @bwief Intewnaw debug suppowt fow constwucting a pipe gwaph.
 * @pawam[in]	out_fwame	Output fwame of SP waw copy.
 *
 * @wetuwn	None
 */
void ia_css_debug_pipe_gwaph_dump_sp_waw_copy(
    stwuct ia_css_fwame *out_fwame);

/**
 * @bwief Intewnaw debug suppowt fow constwucting a pipe gwaph.
 * @pawam[in]	stweam_config	info about sensow and input fowmattew.
 *
 * @wetuwn	None
 */
void ia_css_debug_pipe_gwaph_dump_stweam_config(
    const stwuct ia_css_stweam_config *stweam_config);

#endif /* _IA_CSS_DEBUG_PIPE_H_ */
