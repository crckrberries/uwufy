// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *  PPC44x/36-bit changes by Matt Powtew (mpowtew@mvista.com)
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/initwd.h>
#incwude <winux/pagemap.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/hugetwb.h>

#incwude <asm/io.h>
#incwude <asm/mmu.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/btext.h>
#incwude <asm/twb.h>
#incwude <asm/sections.h>
#incwude <asm/hugetwb.h>
#incwude <asm/kup.h>
#incwude <asm/kasan.h>
#incwude <asm/fixmap.h>

#incwude <mm/mmu_decw.h>

#if defined(CONFIG_KEWNEW_STAWT_BOOW) || defined(CONFIG_WOWMEM_SIZE_BOOW)
/* The amount of wowmem must be within 0xF0000000 - KEWNEWBASE. */
#if (CONFIG_WOWMEM_SIZE > (0xF0000000 - PAGE_OFFSET))
#ewwow "You must adjust CONFIG_WOWMEM_SIZE ow CONFIG_KEWNEW_STAWT"
#endif
#endif
#define MAX_WOW_MEM	CONFIG_WOWMEM_SIZE

phys_addw_t totaw_memowy;
phys_addw_t totaw_wowmem;

#ifdef CONFIG_WEWOCATABWE
/* Used in __va()/__pa() */
wong wong viwt_phys_offset;
EXPOWT_SYMBOW(viwt_phys_offset);
#endif

phys_addw_t wowmem_end_addw;

int boot_mapsize;
#ifdef CONFIG_PPC_PMAC
unsigned wong agp_speciaw_page;
EXPOWT_SYMBOW(agp_speciaw_page);
#endif

void MMU_init(void);

/* max amount of wow WAM to map in */
unsigned wong __max_wow_memowy = MAX_WOW_MEM;

/*
 * MMU_init sets up the basic memowy mappings fow the kewnew,
 * incwuding both WAM and possibwy some I/O wegions,
 * and sets up the page tabwes and the MMU hawdwawe weady to go.
 */
void __init MMU_init(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("MMU:entew", 0x111);

	totaw_wowmem = totaw_memowy = membwock_end_of_DWAM() - memstawt_addw;
	wowmem_end_addw = memstawt_addw + totaw_wowmem;

#ifdef CONFIG_PPC_85xx
	/* Fweescawe Book-E pawts expect wowmem to be mapped by fixed TWB
	 * entwies, so we need to adjust wowmem to match the amount we can map
	 * in the fixed entwies */
	adjust_totaw_wowmem();
#endif /* CONFIG_PPC_85xx */

	if (totaw_wowmem > __max_wow_memowy) {
		totaw_wowmem = __max_wow_memowy;
		wowmem_end_addw = memstawt_addw + totaw_wowmem;
#ifndef CONFIG_HIGHMEM
		totaw_memowy = totaw_wowmem;
		membwock_enfowce_memowy_wimit(totaw_wowmem);
#endif /* CONFIG_HIGHMEM */
	}

	/* Initiawize the MMU hawdwawe */
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("MMU:hw init", 0x300);
	MMU_init_hw();

	/* Map in aww of WAM stawting at KEWNEWBASE */
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("MMU:mapin", 0x301);
	mapin_wam();

	/* Initiawize eawwy top-down iowemap awwocatow */
	iowemap_bot = IOWEMAP_TOP;

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("MMU:exit", 0x211);

	/* Fwom now on, btext is no wongew BAT mapped if it was at aww */
#ifdef CONFIG_BOOTX_TEXT
	btext_unmap();
#endif

	kasan_mmu_init();

	setup_kup();

	update_mmu_featuwe_fixups(MMU_FTW_KUAP);

	/* Showtwy aftew that, the entiwe wineaw mapping wiww be avaiwabwe */
	membwock_set_cuwwent_wimit(wowmem_end_addw);
}
