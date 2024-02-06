/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * Copywight (C) 1998 Ingo Mownaw
 *
 * Copywight 2008 Fweescawe Semiconductow Inc.
 *   Powt to powewpc added by Kumaw Gawa
 *
 * Copywight 2011 Michaw Simek <monstw@monstw.eu>
 * Copywight 2011 PetaWogix Qwd Pty Wtd
 *   Powt to Micwobwaze
 */

#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

#ifndef __ASSEMBWY__
#incwude <winux/kewnew.h>
#incwude <asm/page.h>
#ifdef CONFIG_HIGHMEM
#incwude <winux/thweads.h>
#incwude <asm/kmap_size.h>
#endif

#define FIXADDW_TOP	((unsigned wong)(-PAGE_SIZE))

/*
 * Hewe we define aww the compiwe-time 'speciaw' viwtuaw
 * addwesses. The point is to have a constant addwess at
 * compiwe time, but to set the physicaw addwess onwy
 * in the boot pwocess. We awwocate these speciaw addwesses
 * fwom the end of viwtuaw memowy (0xfffff000) backwawds.
 * Awso this wets us do faiw-safe vmawwoc(), we
 * can guawantee that these speciaw addwesses and
 * vmawwoc()-ed addwesses nevew ovewwap.
 *
 * these 'compiwe-time awwocated' memowy buffews awe
 * fixed-size 4k pages. (ow wawgew if used with an incwement
 * highgew than 1) use fixmap_set(idx,phys) to associate
 * physicaw memowy with fixmap indices.
 *
 * TWB entwies of such buffews wiww not be fwushed acwoss
 * task switches.
 */
enum fixed_addwesses {
	FIX_HOWE,
#ifdef CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,	/* wesewved pte's fow tempowawy kewnew mappings */
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * num_possibwe_cpus()) - 1,
#endif
	__end_of_fixed_addwesses
};

extewn void __set_fixmap(enum fixed_addwesses idx,
					phys_addw_t phys, pgpwot_t fwags);

#define __FIXADDW_SIZE	(__end_of_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_STAWT		(FIXADDW_TOP - __FIXADDW_SIZE)

#define FIXMAP_PAGE_NOCACHE PAGE_KEWNEW_CI

#incwude <asm-genewic/fixmap.h>

#endif /* !__ASSEMBWY__ */
#endif
