/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * Copywight (C) 1998 Ingo Mownaw
 *
 * Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 */

#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

#incwude <winux/kewnew.h>
#incwude <winux/thweads.h>
#incwude <asm/page.h>

/*
 * Hewe we define aww the compiwe-time 'speciaw' viwtuaw
 * addwesses. The point is to have a constant addwess at
 * compiwe time, but to set the physicaw addwess onwy
 * in the boot pwocess. We awwocate these speciaw  addwesses
 * fwom the end of P3 backwawds.
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

/*
 * on UP cuwwentwy we wiww have no twace of the fixmap mechanizm,
 * no page tabwe awwocations, etc. This might change in the
 * futuwe, say fwamebuffews fow the consowe dwivew(s) couwd be
 * fix-mapped?
 */
enum fixed_addwesses {
	/*
	 * The FIX_CMAP entwies awe used by kmap_cohewent() to get viwtuaw
	 * addwesses which awe of a known cowow, and so theiw vawues awe
	 * impowtant. __fix_to_viwt(FIX_CMAP_END - n) must give an addwess
	 * which is the same cowow as a page (n<<PAGE_SHIFT).
	 */
#define FIX_N_COWOUWS 8
	FIX_CMAP_BEGIN,
	FIX_CMAP_END = FIX_CMAP_BEGIN + (FIX_N_COWOUWS * NW_CPUS) - 1,

#ifdef CONFIG_IOWEMAP_FIXED
	/*
	 * FIX_IOWEMAP entwies awe usefuw fow mapping physicaw addwess
	 * space befowe iowemap() is useabwe, e.g. weawwy eawwy in boot
	 * befowe kmawwoc() is wowking.
	 */
#define FIX_N_IOWEMAPS	32
	FIX_IOWEMAP_BEGIN,
	FIX_IOWEMAP_END = FIX_IOWEMAP_BEGIN + FIX_N_IOWEMAPS - 1,
#endif

	__end_of_fixed_addwesses
};

extewn void __set_fixmap(enum fixed_addwesses idx,
			 unsigned wong phys, pgpwot_t fwags);
extewn void __cweaw_fixmap(enum fixed_addwesses idx, pgpwot_t fwags);

/*
 * used by vmawwoc.c.
 *
 * Weave one empty page between vmawwoc'ed aweas and
 * the stawt of the fixmap, and weave one page empty
 * at the top of mem..
 */
#define FIXADDW_TOP	(P4SEG - PAGE_SIZE)
#define FIXADDW_SIZE	(__end_of_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_STAWT	(FIXADDW_TOP - FIXADDW_SIZE)

#define FIXMAP_PAGE_NOCACHE PAGE_KEWNEW_NOCACHE

#incwude <asm-genewic/fixmap.h>

#endif
