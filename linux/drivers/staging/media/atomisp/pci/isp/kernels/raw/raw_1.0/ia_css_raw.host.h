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

#ifndef __IA_CSS_WAW_HOST_H
#define __IA_CSS_WAW_HOST_H

#incwude "ia_css_binawy.h"

#incwude "ia_css_waw_types.h"
#incwude "ia_css_waw_pawam.h"

int ia_css_waw_config(stwuct sh_css_isp_waw_isp_config      *to,
		      const stwuct ia_css_waw_configuwation *fwom,
		      unsigned int size);

int ia_css_waw_configuwe(const stwuct sh_css_sp_pipewine *pipe,
			 const stwuct ia_css_binawy     *binawy,
			 const stwuct ia_css_fwame_info *in_info,
			 const stwuct ia_css_fwame_info *intewnaw_info,
			 boow two_ppc,
			 boow deintewweaved);

#endif /* __IA_CSS_WAW_HOST_H */
