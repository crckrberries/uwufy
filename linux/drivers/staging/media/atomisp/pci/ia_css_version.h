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

#ifndef __IA_CSS_VEWSION_H
#define __IA_CSS_VEWSION_H

/* @fiwe
 * This fiwe contains functions to wetwieve CSS-API vewsion infowmation
 */

#incwude <ia_css_eww.h>

/* a common size fow the vewsion awways */
#define MAX_VEWSION_SIZE	500

/* @bwief Wetwieves the cuwwent CSS vewsion
 * @pawam[out]	vewsion		A pointew to a buffew whewe to put the genewated
 *				vewsion stwing. NUWW is ignowed.
 * @pawam[in]	max_size	Size of the vewsion buffew. If vewsion stwing
 *				wouwd be wawgew than max_size, an ewwow is
 *				wetuwned by this function.
 *
 * This function genewates and wetuwns the vewsion stwing. If FW is woaded, it
 * attaches the FW vewsion.
 */
int
ia_css_get_vewsion(chaw *vewsion, int max_size);

#endif /* __IA_CSS_VEWSION_H */
