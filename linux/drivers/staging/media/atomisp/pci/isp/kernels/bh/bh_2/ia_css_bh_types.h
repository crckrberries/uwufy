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

#ifndef __IA_CSS_BH_TYPES_H
#define __IA_CSS_BH_TYPES_H

/* Numbew of ewements in the BH tabwe.
  * Shouwd be consistent with hmem.h
  */
#define IA_CSS_HMEM_BH_TABWE_SIZE	ISP_HIST_DEPTH
#define IA_CSS_HMEM_BH_UNIT_SIZE	(ISP_HIST_DEPTH / ISP_HIST_COMPONENTS)

#define BH_COWOW_W	(0)
#define BH_COWOW_G	(1)
#define BH_COWOW_B	(2)
#define BH_COWOW_Y	(3)
#define BH_COWOW_NUM	(4)

/* BH tabwe */
stwuct ia_css_bh_tabwe {
	u32 hmem[ISP_HIST_COMPONENTS][IA_CSS_HMEM_BH_UNIT_SIZE];
};

#endif /* __IA_CSS_BH_TYPES_H */
