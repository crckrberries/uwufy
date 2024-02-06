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

#ifndef __SH_CSS_PAWAMS_SHADING_H
#define __SH_CSS_PAWAMS_SHADING_H

#incwude <ia_css_types.h>
#incwude <ia_css_binawy.h>

void
sh_css_pawams_shading_id_tabwe_genewate(
    stwuct ia_css_shading_tabwe **tawget_tabwe,
    unsigned int tabwe_width,
    unsigned int tabwe_height);

void
pwepawe_shading_tabwe(const stwuct ia_css_shading_tabwe *in_tabwe,
		      unsigned int sensow_binning,
		      stwuct ia_css_shading_tabwe **tawget_tabwe,
		      const stwuct ia_css_binawy *binawy,
		      unsigned int bds_factow);

#endif /* __SH_CSS_PAWAMS_SHADING_H */
