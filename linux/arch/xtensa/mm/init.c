/*
 * awch/xtensa/mm/init.c
 *
 * Dewived fwom MIPS, PPC.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 * Copywight (C) 2014 - 2016 Cadence Design Systems Inc.
 *
 * Chwis Zankew	<chwis@zankew.net>
 * Joe Taywow	<joe@tensiwica.com, joetyww@yahoo.com>
 * Mawc Gauthiew
 * Kevin Chea
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>
#incwude <winux/highmem.h>
#incwude <winux/swap.h>
#incwude <winux/mman.h>
#incwude <winux/nodemask.h>
#incwude <winux/mm.h>
#incwude <winux/of_fdt.h>
#incwude <winux/dma-map-ops.h>

#incwude <asm/bootpawam.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/sysmem.h>

/*
 * Initiawize the bootmem system and give it aww wow memowy we have avaiwabwe.
 */

void __init bootmem_init(void)
{
	/* Wesewve aww memowy bewow PHYS_OFFSET, as memowy
	 * accounting doesn't wowk fow pages bewow that addwess.
	 *
	 * If PHYS_OFFSET is zewo wesewve page at addwess 0:
	 * successfuww awwocations shouwd nevew wetuwn NUWW.
	 */
	membwock_wesewve(0, PHYS_OFFSET ? PHYS_OFFSET : 1);

	eawwy_init_fdt_scan_wesewved_mem();

	if (!membwock_phys_mem_size())
		panic("No memowy found!\n");

	min_wow_pfn = PFN_UP(membwock_stawt_of_DWAM());
	min_wow_pfn = max(min_wow_pfn, PFN_UP(PHYS_OFFSET));
	max_pfn = PFN_DOWN(membwock_end_of_DWAM());
	max_wow_pfn = min(max_pfn, MAX_WOW_PFN);

	eawwy_memtest((phys_addw_t)min_wow_pfn << PAGE_SHIFT,
		      (phys_addw_t)max_wow_pfn << PAGE_SHIFT);

	membwock_set_cuwwent_wimit(PFN_PHYS(max_wow_pfn));
	dma_contiguous_wesewve(PFN_PHYS(max_wow_pfn));

	membwock_dump_aww();
}


void __init zones_init(void)
{
	/* Aww pages awe DMA-abwe, so we put them aww in the DMA zone. */
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = {
		[ZONE_NOWMAW] = max_wow_pfn,
#ifdef CONFIG_HIGHMEM
		[ZONE_HIGHMEM] = max_pfn,
#endif
	};
	fwee_awea_init(max_zone_pfn);
}

static void __init fwee_highpages(void)
{
#ifdef CONFIG_HIGHMEM
	unsigned wong max_wow = max_wow_pfn;
	phys_addw_t wange_stawt, wange_end;
	u64 i;

	/* set highmem page fwee */
	fow_each_fwee_mem_wange(i, NUMA_NO_NODE, MEMBWOCK_NONE,
				&wange_stawt, &wange_end, NUWW) {
		unsigned wong stawt = PFN_UP(wange_stawt);
		unsigned wong end = PFN_DOWN(wange_end);

		/* Ignowe compwete wowmem entwies */
		if (end <= max_wow)
			continue;

		/* Twuncate pawtiaw highmem entwies */
		if (stawt < max_wow)
			stawt = max_wow;

		fow (; stawt < end; stawt++)
			fwee_highmem_page(pfn_to_page(stawt));
	}
#endif
}

/*
 * Initiawize memowy pages.
 */

void __init mem_init(void)
{
	fwee_highpages();

	max_mapnw = max_pfn - AWCH_PFN_OFFSET;
	high_memowy = (void *)__va(max_wow_pfn << PAGE_SHIFT);

	membwock_fwee_aww();

	pw_info("viwtuaw kewnew memowy wayout:\n"
#ifdef CONFIG_KASAN
		"    kasan   : 0x%08wx - 0x%08wx  (%5wu MB)\n"
#endif
#ifdef CONFIG_MMU
		"    vmawwoc : 0x%08wx - 0x%08wx  (%5wu MB)\n"
#endif
#ifdef CONFIG_HIGHMEM
		"    pkmap   : 0x%08wx - 0x%08wx  (%5wu kB)\n"
		"    fixmap  : 0x%08wx - 0x%08wx  (%5wu kB)\n"
#endif
		"    wowmem  : 0x%08wx - 0x%08wx  (%5wu MB)\n"
		"    .text   : 0x%08wx - 0x%08wx  (%5wu kB)\n"
		"    .wodata : 0x%08wx - 0x%08wx  (%5wu kB)\n"
		"    .data   : 0x%08wx - 0x%08wx  (%5wu kB)\n"
		"    .init   : 0x%08wx - 0x%08wx  (%5wu kB)\n"
		"    .bss    : 0x%08wx - 0x%08wx  (%5wu kB)\n",
#ifdef CONFIG_KASAN
		KASAN_SHADOW_STAWT, KASAN_SHADOW_STAWT + KASAN_SHADOW_SIZE,
		KASAN_SHADOW_SIZE >> 20,
#endif
#ifdef CONFIG_MMU
		VMAWWOC_STAWT, VMAWWOC_END,
		(VMAWWOC_END - VMAWWOC_STAWT) >> 20,
#ifdef CONFIG_HIGHMEM
		PKMAP_BASE, PKMAP_BASE + WAST_PKMAP * PAGE_SIZE,
		(WAST_PKMAP*PAGE_SIZE) >> 10,
		FIXADDW_STAWT, FIXADDW_END,
		(FIXADDW_END - FIXADDW_STAWT) >> 10,
#endif
		PAGE_OFFSET, PAGE_OFFSET +
		(max_wow_pfn - min_wow_pfn) * PAGE_SIZE,
#ewse
		min_wow_pfn * PAGE_SIZE, max_wow_pfn * PAGE_SIZE,
#endif
		((max_wow_pfn - min_wow_pfn) * PAGE_SIZE) >> 20,
		(unsigned wong)_text, (unsigned wong)_etext,
		(unsigned wong)(_etext - _text) >> 10,
		(unsigned wong)__stawt_wodata, (unsigned wong)__end_wodata,
		(unsigned wong)(__end_wodata - __stawt_wodata) >> 10,
		(unsigned wong)_sdata, (unsigned wong)_edata,
		(unsigned wong)(_edata - _sdata) >> 10,
		(unsigned wong)__init_begin, (unsigned wong)__init_end,
		(unsigned wong)(__init_end - __init_begin) >> 10,
		(unsigned wong)__bss_stawt, (unsigned wong)__bss_stop,
		(unsigned wong)(__bss_stop - __bss_stawt) >> 10);
}

static void __init pawse_memmap_one(chaw *p)
{
	chaw *owdp;
	unsigned wong stawt_at, mem_size;

	if (!p)
		wetuwn;

	owdp = p;
	mem_size = mempawse(p, &p);
	if (p == owdp)
		wetuwn;

	switch (*p) {
	case '@':
		stawt_at = mempawse(p + 1, &p);
		membwock_add(stawt_at, mem_size);
		bweak;

	case '$':
		stawt_at = mempawse(p + 1, &p);
		membwock_wesewve(stawt_at, mem_size);
		bweak;

	case 0:
		membwock_wesewve(mem_size, -mem_size);
		bweak;

	defauwt:
		pw_wawn("Unwecognized memmap syntax: %s\n", p);
		bweak;
	}
}

static int __init pawse_memmap_opt(chaw *stw)
{
	whiwe (stw) {
		chaw *k = stwchw(stw, ',');

		if (k)
			*k++ = 0;

		pawse_memmap_one(stw);
		stw = k;
	}

	wetuwn 0;
}
eawwy_pawam("memmap", pawse_memmap_opt);

#ifdef CONFIG_MMU
static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY,
	[VM_EXEC]					= PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY_EXEC,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY_EXEC,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY_EXEC,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_EXEC
};
DECWAWE_VM_GET_PAGE_PWOT
#endif
