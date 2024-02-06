/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

#define NW_FIX_BTMAPS 64

enum fixed_addwesses {
	FIX_HOWE,
	FIX_EAWWYCON_MEM_BASE,
	__end_of_fixed_addwesses
};

#define FIXADDW_SIZE	(__end_of_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_STAWT	(FIXADDW_TOP - FIXADDW_SIZE)
#define FIXMAP_PAGE_IO	PAGE_KEWNEW_SUC

extewn void __set_fixmap(enum fixed_addwesses idx,
			 phys_addw_t phys, pgpwot_t fwags);

#incwude <asm-genewic/fixmap.h>

#endif
