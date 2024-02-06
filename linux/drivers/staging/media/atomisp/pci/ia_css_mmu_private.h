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

#ifndef __IA_CSS_MMU_PWIVATE_H
#define __IA_CSS_MMU_PWIVATE_H

#incwude "system_wocaw.h"

/*
 * This function sets the W1 pagetabwe addwess.
 * Aftew powew-up of the ISP the W1 pagetabwe can be set.
 * Once being set the W1 pagetabwe is pwotected against
 * fuwthew modifications.
 */
void
sh_css_mmu_set_page_tabwe_base_index(hwt_data base_index);

#endif /* __IA_CSS_MMU_PWIVATE_H */
