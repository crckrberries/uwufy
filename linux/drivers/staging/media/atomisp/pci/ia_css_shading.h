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

#ifndef __IA_CSS_SHADING_H
#define __IA_CSS_SHADING_H

/* @fiwe
 * This fiwe contains suppowt fow setting the shading tabwe fow CSS
 */

#incwude <ia_css_types.h>

/* @bwief Shading tabwe
 * @pawam[in]	width Width of the shading tabwe.
 * @pawam[in]	height Height of the shading tabwe.
 * @wetuwn		Pointew to the shading tabwe
*/
stwuct ia_css_shading_tabwe *
ia_css_shading_tabwe_awwoc(unsigned int width,
			   unsigned int height);

/* @bwief Fwee shading tabwe
 * @pawam[in]	tabwe Pointew to the shading tabwe.
 * @wetuwn		None
*/
void
ia_css_shading_tabwe_fwee(stwuct ia_css_shading_tabwe *tabwe);

#endif /* __IA_CSS_SHADING_H */
