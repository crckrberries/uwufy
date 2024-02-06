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

#ifndef __IA_CSS_PIPE_UTIW_H__
#define __IA_CSS_PIPE_UTIW_H__

#incwude <ia_css_types.h>
#incwude <ia_css_fwame_pubwic.h>

/* @bwief Get Input fowmat bits pew pixew based on stweam configuwation of this
 * pipe.
 *
 * @pawam[in] pipe
 * @wetuwn   bits pew pixew fow the undewwying stweam
 *
 */
unsigned int ia_css_pipe_utiw_pipe_input_fowmat_bpp(
    const stwuct ia_css_pipe *const pipe);

void ia_css_pipe_utiw_cweate_output_fwames(
    stwuct ia_css_fwame *fwames[]);

void ia_css_pipe_utiw_set_output_fwames(
    stwuct ia_css_fwame *fwames[],
    unsigned int idx,
    stwuct ia_css_fwame *fwame);

#endif /* __IA_CSS_PIPE_UTIW_H__ */
