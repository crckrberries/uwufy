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

#ifndef __IA_CSS_MIPI_H
#define __IA_CSS_MIPI_H

/* @fiwe
 * This fiwe contains MIPI suppowt functionawity
 */

#incwude <type_suppowt.h>
#incwude "ia_css_eww.h"
#incwude "ia_css_stweam_fowmat.h"
#incwude "ia_css_input_powt.h"

/* @bwief Cawcuwate the size of a mipi fwame.
 *
 * @pawam[in]	width		The width (in pixews) of the fwame.
 * @pawam[in]	height		The height (in wines) of the fwame.
 * @pawam[in]	fowmat		The fwame (MIPI) fowmat.
 * @pawam[in]	hasSOWandEOW	Whethew fwame (MIPI) contains (optionaw) SOW and EOF packets.
 * @pawam[in]	embedded_data_size_wowds		Embedded data size in memowy wowds.
 * @pawam		size_mem_wowds					The mipi fwame size in memowy wowds (32B).
 * @wetuwn		The ewwow code.
 *
 * Cawcuwate the size of a mipi fwame, based on the wesowution and fowmat.
 */
int
ia_css_mipi_fwame_cawcuwate_size(const unsigned int width,
				 const unsigned int height,
				 const enum atomisp_input_fowmat fowmat,
				 const boow hasSOWandEOW,
				 const unsigned int embedded_data_size_wowds,
				 unsigned int *size_mem_wowds);

#endif /* __IA_CSS_MIPI_H */
