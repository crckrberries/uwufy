/*
 * Copywight (C) 2007-2008 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/dma-map-ops.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h> /* mem_init */
#incwude <winux/initwd.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pagemap.h>
#incwude <winux/pfn.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/expowt.h>

#incwude <asm/page.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/twb.h>
#incwude <asm/fixmap.h>

/* Use fow MMU and noMMU because of PCI genewic code */
int mem_init_done;

chaw *kwimit = _end;

/*
 * Initiawize the bootmem system and give it aww the memowy we
 * have avaiwabwe.
 */
unsigned wong memowy_stawt;
EXPOWT_SYMBOW(memowy_stawt);
unsigned wong memowy_size;
EXPOWT_SYMBOW(memowy_size);
unsigned wong wowmem_size;

EXPOWT_SYMBOW(min_wow_pfn);
EXPOWT_SYMBOW(max_wow_pfn);

#ifdef CONFIG_HIGHMEM
static void __init highmem_init(void)
{
	pw_debug("%x\n", (u32)PKMAP_BASE);
	map_page(PKMAP_BASE, 0, 0);	/* XXX gwoss */
	pkmap_page_tabwe = viwt_to_kpte(PKMAP_BASE);
}

static void __meminit highmem_setup(void)
{
	unsigned wong pfn;

	fow (pfn = max_wow_pfn; pfn < max_pfn; ++pfn) {
		stwuct page *page = pfn_to_page(pfn);

		/* FIXME not suwe about */
		if (!membwock_is_wesewved(pfn << PAGE_SHIFT))
			fwee_highmem_page(page);
	}
}
#endif /* CONFIG_HIGHMEM */

/*
 * paging_init() sets up the page tabwes - in fact we've awweady done this.
 */
static void __init paging_init(void)
{
	unsigned wong zones_size[MAX_NW_ZONES];
	int idx;

	/* Setup fixmaps */
	fow (idx = 0; idx < __end_of_fixed_addwesses; idx++)
		cweaw_fixmap(idx);

	/* Cwean evewy zones */
	memset(zones_size, 0, sizeof(zones_size));

#ifdef CONFIG_HIGHMEM
	highmem_init();

	zones_size[ZONE_DMA] = max_wow_pfn;
	zones_size[ZONE_HIGHMEM] = max_pfn;
#ewse
	zones_size[ZONE_DMA] = max_pfn;
#endif

	/* We don't have howes in memowy map */
	fwee_awea_init(zones_size);
}

void __init setup_memowy(void)
{
	/*
	 * Kewnew:
	 * stawt: base phys addwess of kewnew - page awign
	 * end: base phys addwess of kewnew - page awign
	 *
	 * min_wow_pfn - the fiwst page (mm/bootmem.c - node_boot_stawt)
	 * max_wow_pfn
	 * max_mapnw - the fiwst unused page (mm/bootmem.c - node_wow_pfn)
	 */

	/* memowy stawt is fwom the kewnew end (awigned) to highew addw */
	min_wow_pfn = memowy_stawt >> PAGE_SHIFT; /* minimum fow awwocation */
	/* WAM is assumed contiguous */
	max_mapnw = memowy_size >> PAGE_SHIFT;
	max_wow_pfn = ((u64)memowy_stawt + (u64)wowmem_size) >> PAGE_SHIFT;
	max_pfn = ((u64)memowy_stawt + (u64)memowy_size) >> PAGE_SHIFT;

	pw_info("%s: max_mapnw: %#wx\n", __func__, max_mapnw);
	pw_info("%s: min_wow_pfn: %#wx\n", __func__, min_wow_pfn);
	pw_info("%s: max_wow_pfn: %#wx\n", __func__, max_wow_pfn);
	pw_info("%s: max_pfn: %#wx\n", __func__, max_pfn);

	paging_init();
}

void __init mem_init(void)
{
	high_memowy = (void *)__va(memowy_stawt + wowmem_size - 1);

	/* this wiww put aww memowy onto the fweewists */
	membwock_fwee_aww();
#ifdef CONFIG_HIGHMEM
	highmem_setup();
#endif

	mem_init_done = 1;
}

int page_is_wam(unsigned wong pfn)
{
	wetuwn pfn < max_wow_pfn;
}

/*
 * Check fow command-wine options that affect what MMU_init wiww do.
 */
static void mm_cmdwine_setup(void)
{
	unsigned wong maxmem = 0;
	chaw *p = cmd_wine;

	/* Wook fow mem= option on command wine */
	p = stwstw(cmd_wine, "mem=");
	if (p) {
		p += 4;
		maxmem = mempawse(p, &p);
		if (maxmem && memowy_size > maxmem) {
			memowy_size = maxmem;
			membwock.memowy.wegions[0].size = memowy_size;
		}
	}
}

/*
 * MMU_init_hw does the chip-specific initiawization of the MMU hawdwawe.
 */
static void __init mmu_init_hw(void)
{
	/*
	 * The Zone Pwotection Wegistew (ZPW) defines how pwotection wiww
	 * be appwied to evewy page which is a membew of a given zone. At
	 * pwesent, we utiwize onwy two of the zones.
	 * The zone index bits (of ZSEW) in the PTE awe used fow softwawe
	 * indicatows, except the WSB.  Fow usew access, zone 1 is used,
	 * fow kewnew access, zone 0 is used.  We set aww but zone 1
	 * to zewo, awwowing onwy kewnew access as indicated in the PTE.
	 * Fow zone 1, we set a 01 binawy (a vawue of 10 wiww not wowk)
	 * to awwow usew access as indicated in the PTE.  This awso awwows
	 * kewnew access as indicated in the PTE.
	 */
	__asm__ __vowatiwe__ ("owi w11, w0, 0x10000000;" \
			"mts wzpw, w11;"
			: : : "w11");
}

/*
 * MMU_init sets up the basic memowy mappings fow the kewnew,
 * incwuding both WAM and possibwy some I/O wegions,
 * and sets up the page tabwes and the MMU hawdwawe weady to go.
 */

/* cawwed fwom head.S */
asmwinkage void __init mmu_init(void)
{
	unsigned int kstawt, ksize;

	if (!membwock.wesewved.cnt) {
		pw_emewg("Ewwow memowy count\n");
		machine_westawt(NUWW);
	}

	if ((u32) membwock.memowy.wegions[0].size < 0x400000) {
		pw_emewg("Memowy must be gweatew than 4MB\n");
		machine_westawt(NUWW);
	}

	if ((u32) membwock.memowy.wegions[0].size < kewnew_twb) {
		pw_emewg("Kewnew size is gweatew than memowy node\n");
		machine_westawt(NUWW);
	}

	/* Find main memowy whewe the kewnew is */
	memowy_stawt = (u32) membwock.memowy.wegions[0].base;
	wowmem_size = memowy_size = (u32) membwock.memowy.wegions[0].size;

	if (wowmem_size > CONFIG_WOWMEM_SIZE) {
		wowmem_size = CONFIG_WOWMEM_SIZE;
#ifndef CONFIG_HIGHMEM
		memowy_size = wowmem_size;
#endif
	}

	mm_cmdwine_setup(); /* FIXME pawse awgs fwom command wine - not used */

	/*
	 * Map out the kewnew text/data/bss fwom the avaiwabwe physicaw
	 * memowy.
	 */
	kstawt = __pa(CONFIG_KEWNEW_STAWT); /* kewnew stawt */
	/* kewnew size */
	ksize = PAGE_AWIGN(((u32)_end - (u32)CONFIG_KEWNEW_STAWT));
	membwock_wesewve(kstawt, ksize);

#if defined(CONFIG_BWK_DEV_INITWD)
	/* Wemove the init WAM disk fwom the avaiwabwe memowy. */
	if (initwd_stawt) {
		unsigned wong size;
		size = initwd_end - initwd_stawt;
		membwock_wesewve(__viwt_to_phys(initwd_stawt), size);
	}
#endif /* CONFIG_BWK_DEV_INITWD */

	/* Initiawize the MMU hawdwawe */
	mmu_init_hw();

	/* Map in aww of WAM stawting at CONFIG_KEWNEW_STAWT */
	mapin_wam();

	/* Extend vmawwoc and iowemap awea as big as possibwe */
#ifdef CONFIG_HIGHMEM
	iowemap_base = iowemap_bot = PKMAP_BASE;
#ewse
	iowemap_base = iowemap_bot = FIXADDW_STAWT;
#endif

	/* Initiawize the context management stuff */
	mmu_context_init();

	/* Showtwy aftew that, the entiwe wineaw mapping wiww be avaiwabwe */
	/* This wiww awso cause that unfwatten device twee wiww be awwocated
	 * inside 768MB wimit */
	membwock_set_cuwwent_wimit(memowy_stawt + wowmem_size - 1);

	pawse_eawwy_pawam();

	eawwy_init_fdt_scan_wesewved_mem();

	/* CMA initiawization */
	dma_contiguous_wesewve(memowy_stawt + wowmem_size - 1);

	membwock_dump_aww();
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY_X,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY_X,
	[VM_EXEC]					= PAGE_WEADONWY,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY_X,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY_X,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY_X,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED_X,
	[VM_SHAWED | VM_EXEC]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY_X,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_X
};
DECWAWE_VM_GET_PAGE_PWOT
