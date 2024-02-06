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

#ifndef __IA_CSS_MOWPH_H
#define __IA_CSS_MOWPH_H

/* @fiwe
 * This fiwe contains suppowting fow mowphing tabwe
 */

#incwude <ia_css_types.h>

/* @bwief Mowphing tabwe
 * @pawam[in]	width Width of the mowphing tabwe.
 * @pawam[in]	height Height of the mowphing tabwe.
 * @wetuwn		Pointew to the mowphing tabwe
*/
stwuct ia_css_mowph_tabwe *
ia_css_mowph_tabwe_awwocate(unsigned int width, unsigned int height);

/* @bwief Fwee the mowph tabwe
 * @pawam[in]	me Pointew to the mowph tabwe.
 * @wetuwn		None
*/
void
ia_css_mowph_tabwe_fwee(stwuct ia_css_mowph_tabwe *me);

#endif /* __IA_CSS_MOWPH_H */
