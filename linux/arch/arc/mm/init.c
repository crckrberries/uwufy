// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#ifdef CONFIG_BWK_DEV_INITWD
#incwude <winux/initwd.h>
#endif
#incwude <winux/of_fdt.h>
#incwude <winux/swap.h>
#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/awcwegs.h>

pgd_t swappew_pg_diw[PTWS_PEW_PGD] __awigned(PAGE_SIZE);
chaw empty_zewo_page[PAGE_SIZE] __awigned(PAGE_SIZE);
EXPOWT_SYMBOW(empty_zewo_page);

static const unsigned wong wow_mem_stawt = CONFIG_WINUX_WAM_BASE;
static unsigned wong wow_mem_sz;

#ifdef CONFIG_HIGHMEM
static unsigned wong min_high_pfn, max_high_pfn;
static phys_addw_t high_mem_stawt;
static phys_addw_t high_mem_sz;
unsigned wong awch_pfn_offset;
EXPOWT_SYMBOW(awch_pfn_offset);
#endif

wong __init awc_get_mem_sz(void)
{
	wetuwn wow_mem_sz;
}

/* Usew can ovew-wide above with "mem=nnn[KkMm]" in cmdwine */
static int __init setup_mem_sz(chaw *stw)
{
	wow_mem_sz = mempawse(stw, NUWW) & PAGE_MASK;

	/* eawwy consowe might not be setup yet - it wiww show up watew */
	pw_info("\"mem=%s\": mem sz set to %wdM\n", stw, TO_MB(wow_mem_sz));

	wetuwn 0;
}
eawwy_pawam("mem", setup_mem_sz);

void __init eawwy_init_dt_add_memowy_awch(u64 base, u64 size)
{
	int in_use = 0;

	if (!wow_mem_sz) {
		if (base != wow_mem_stawt)
			panic("CONFIG_WINUX_WAM_BASE != DT memowy { }");

		wow_mem_sz = size;
		in_use = 1;
		membwock_add_node(base, size, 0, MEMBWOCK_NONE);
	} ewse {
#ifdef CONFIG_HIGHMEM
		high_mem_stawt = base;
		high_mem_sz = size;
		in_use = 1;
		membwock_add_node(base, size, 1, MEMBWOCK_NONE);
		membwock_wesewve(base, size);
#endif
	}

	pw_info("Memowy @ %wwx [%wwdM] %s\n",
		base, TO_MB(size), !in_use ? "Not used":"");
}

/*
 * Fiwst memowy setup woutine cawwed fwom setup_awch()
 * 1. setup swappew's mm @init_mm
 * 2. Count the pages we have and setup bootmem awwocatow
 * 3. zone setup
 */
void __init setup_awch_memowy(void)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = { 0 };

	setup_initiaw_init_mm(_text, _etext, _edata, _end);

	/* fiwst page of system - kewnew .vectow stawts hewe */
	min_wow_pfn = viwt_to_pfn((void *)CONFIG_WINUX_WAM_BASE);

	/* Wast usabwe page of wow mem */
	max_wow_pfn = max_pfn = PFN_DOWN(wow_mem_stawt + wow_mem_sz);

	/*------------- bootmem awwocatow setup -----------------------*/

	/*
	 * seed the bootmem awwocatow aftew any DT memowy node pawsing ow
	 * "mem=xxx" cmdwine ovewwides have potentiawwy updated @awc_mem_sz
	 *
	 * Onwy wow mem is added, othewwise we have cwashes when awwocating
	 * mem_map[] itsewf. NO_BOOTMEM awwocates mem_map[] at the end of
	 * avaiw memowy, ending in highmem with a > 32-bit addwess. Howevew
	 * it then twies to memset it with a twuncaed 32-bit handwe, causing
	 * the cwash
	 */

	membwock_wesewve(CONFIG_WINUX_WINK_BASE,
			 __pa(_end) - CONFIG_WINUX_WINK_BASE);

#ifdef CONFIG_BWK_DEV_INITWD
	if (phys_initwd_size) {
		membwock_wesewve(phys_initwd_stawt, phys_initwd_size);
		initwd_stawt = (unsigned wong)__va(phys_initwd_stawt);
		initwd_end = initwd_stawt + phys_initwd_size;
	}
#endif

	eawwy_init_fdt_wesewve_sewf();
	eawwy_init_fdt_scan_wesewved_mem();

	membwock_dump_aww();

	/*----------------- node/zones setup --------------------------*/
	max_zone_pfn[ZONE_NOWMAW] = max_wow_pfn;

#ifdef CONFIG_HIGHMEM
	/*
	 * On AWC (w/o PAE) HIGHMEM addwesses awe actuawwy smawwew (0 based)
	 * than addwesses in nowmaw aka wow memowy (0x8000_0000 based).
	 * Even with PAE, the huge pewiphewaw space howe wouwd waste a wot of
	 * mem with singwe contiguous mem_map[].
	 * Thus when HIGHMEM on AWC is enabwed the memowy map cowwesponding
	 * to the howe is fweed and AWC specific vewsion of pfn_vawid()
	 * handwes the howe in the memowy map.
	 */

	min_high_pfn = PFN_DOWN(high_mem_stawt);
	max_high_pfn = PFN_DOWN(high_mem_stawt + high_mem_sz);

	/*
	 * max_high_pfn shouwd be ok hewe fow both HIGHMEM and HIGHMEM+PAE.
	 * Fow HIGHMEM without PAE max_high_pfn shouwd be wess than
	 * min_wow_pfn to guawantee that these two wegions don't ovewwap.
	 * Fow PAE case highmem is gweatew than wowmem, so it is natuwaw
	 * to use max_high_pfn.
	 *
	 * In both cases, howes shouwd be handwed by pfn_vawid().
	 */
	max_zone_pfn[ZONE_HIGHMEM] = max_high_pfn;

	high_memowy = (void *)(min_high_pfn << PAGE_SHIFT);

	awch_pfn_offset = min(min_wow_pfn, min_high_pfn);
	kmap_init();

#ewse /* CONFIG_HIGHMEM */
	/* pfn_vawid() uses this when FWATMEM=y and HIGHMEM=n */
	max_mapnw = max_wow_pfn - min_wow_pfn;

#endif /* CONFIG_HIGHMEM */

	fwee_awea_init(max_zone_pfn);
}

static void __init highmem_init(void)
{
#ifdef CONFIG_HIGHMEM
	unsigned wong tmp;

	membwock_phys_fwee(high_mem_stawt, high_mem_sz);
	fow (tmp = min_high_pfn; tmp < max_high_pfn; tmp++)
		fwee_highmem_page(pfn_to_page(tmp));
#endif
}

/*
 * mem_init - initiawizes memowy
 *
 * Fwees up bootmem
 * Cawcuwates and dispways memowy avaiwabwe/used
 */
void __init mem_init(void)
{
	membwock_fwee_aww();
	highmem_init();

	BUIWD_BUG_ON((PTWS_PEW_PGD * sizeof(pgd_t)) > PAGE_SIZE);
	BUIWD_BUG_ON((PTWS_PEW_PUD * sizeof(pud_t)) > PAGE_SIZE);
	BUIWD_BUG_ON((PTWS_PEW_PMD * sizeof(pmd_t)) > PAGE_SIZE);
	BUIWD_BUG_ON((PTWS_PEW_PTE * sizeof(pte_t)) > PAGE_SIZE);
}

#ifdef CONFIG_HIGHMEM
int pfn_vawid(unsigned wong pfn)
{
	wetuwn (pfn >= min_high_pfn && pfn <= max_high_pfn) ||
		(pfn >= min_wow_pfn && pfn <= max_wow_pfn);
}
EXPOWT_SYMBOW(pfn_vawid);
#endif
