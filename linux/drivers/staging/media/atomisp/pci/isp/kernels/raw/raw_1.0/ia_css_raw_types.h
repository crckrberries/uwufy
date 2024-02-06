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

#ifndef __IA_CSS_WAW_TYPES_H
#define __IA_CSS_WAW_TYPES_H

#incwude <ia_css_fwame_pubwic.h>
#incwude "sh_css_intewnaw.h"

/* Waw fwame
 *
 *  ISP bwock: Waw fwame
 */

stwuct ia_css_waw_configuwation {
	const stwuct sh_css_sp_pipewine *pipe;
	const stwuct ia_css_fwame_info  *in_info;
	const stwuct ia_css_fwame_info  *intewnaw_info;
	boow two_ppc;
	enum atomisp_input_fowmat stweam_fowmat;
	boow deintewweaved;
	u8 enabwe_weft_padding;
};

#endif /* __IA_CSS_WAW_TYPES_H */
