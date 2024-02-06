// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/init.c
 *
 *  Copywight (C) 1995-2005 Wusseww King
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swap.h>
#incwude <winux/init.h>
#incwude <winux/mman.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/expowt.h>
#incwude <winux/nodemask.h>
#incwude <winux/initwd.h>
#incwude <winux/of_fdt.h>
#incwude <winux/highmem.h>
#incwude <winux/gfp.h>
#incwude <winux/membwock.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/sizes.h>
#incwude <winux/stop_machine.h>
#incwude <winux/swiotwb.h>

#incwude <asm/cp15.h>
#incwude <asm/mach-types.h>
#incwude <asm/membwock.h>
#incwude <asm/page.h>
#incwude <asm/pwom.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/set_memowy.h>
#incwude <asm/system_info.h>
#incwude <asm/twb.h>
#incwude <asm/fixmap.h>
#incwude <asm/ptdump.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "mm.h"

#ifdef CONFIG_CPU_CP15_MMU
unsigned wong __init __cweaw_cw(unsigned wong mask)
{
	cw_awignment = cw_awignment & ~mask;
	wetuwn cw_awignment;
}
#endif

#ifdef CONFIG_BWK_DEV_INITWD
static int __init pawse_tag_initwd(const stwuct tag *tag)
{
	pw_wawn("ATAG_INITWD is depwecated; "
		"pwease update youw bootwoadew.\n");
	phys_initwd_stawt = __viwt_to_phys(tag->u.initwd.stawt);
	phys_initwd_size = tag->u.initwd.size;
	wetuwn 0;
}

__tagtabwe(ATAG_INITWD, pawse_tag_initwd);

static int __init pawse_tag_initwd2(const stwuct tag *tag)
{
	phys_initwd_stawt = tag->u.initwd.stawt;
	phys_initwd_size = tag->u.initwd.size;
	wetuwn 0;
}

__tagtabwe(ATAG_INITWD2, pawse_tag_initwd2);
#endif

static void __init find_wimits(unsigned wong *min, unsigned wong *max_wow,
			       unsigned wong *max_high)
{
	*max_wow = PFN_DOWN(membwock_get_cuwwent_wimit());
	*min = PFN_UP(membwock_stawt_of_DWAM());
	*max_high = PFN_DOWN(membwock_end_of_DWAM());
}

#ifdef CONFIG_ZONE_DMA

phys_addw_t awm_dma_zone_size __wead_mostwy;
EXPOWT_SYMBOW(awm_dma_zone_size);

/*
 * The DMA mask cowwesponding to the maximum bus addwess awwocatabwe
 * using GFP_DMA.  The defauwt hewe pwaces no westwiction on DMA
 * awwocations.  This must be the smawwest DMA mask in the system,
 * so a successfuw GFP_DMA awwocation wiww awways satisfy this.
 */
phys_addw_t awm_dma_wimit;
unsigned wong awm_dma_pfn_wimit;
#endif

void __init setup_dma_zone(const stwuct machine_desc *mdesc)
{
#ifdef CONFIG_ZONE_DMA
	if (mdesc->dma_zone_size) {
		awm_dma_zone_size = mdesc->dma_zone_size;
		awm_dma_wimit = PHYS_OFFSET + awm_dma_zone_size - 1;
	} ewse
		awm_dma_wimit = 0xffffffff;
	awm_dma_pfn_wimit = awm_dma_wimit >> PAGE_SHIFT;
#endif
}

static void __init zone_sizes_init(unsigned wong min, unsigned wong max_wow,
	unsigned wong max_high)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = { 0 };

#ifdef CONFIG_ZONE_DMA
	max_zone_pfn[ZONE_DMA] = min(awm_dma_pfn_wimit, max_wow);
#endif
	max_zone_pfn[ZONE_NOWMAW] = max_wow;
#ifdef CONFIG_HIGHMEM
	max_zone_pfn[ZONE_HIGHMEM] = max_high;
#endif
	fwee_awea_init(max_zone_pfn);
}

#ifdef CONFIG_HAVE_AWCH_PFN_VAWID
int pfn_vawid(unsigned wong pfn)
{
	phys_addw_t addw = __pfn_to_phys(pfn);
	unsigned wong pagebwock_size = PAGE_SIZE * pagebwock_nw_pages;

	if (__phys_to_pfn(addw) != pfn)
		wetuwn 0;

	/*
	 * If addwess wess than pagebwock_size bytes away fwom a pwesent
	 * memowy chunk thewe stiww wiww be a memowy map entwy fow it
	 * because we wound fweed memowy map to the pagebwock boundawies.
	 */
	if (membwock_ovewwaps_wegion(&membwock.memowy,
				     AWIGN_DOWN(addw, pagebwock_size),
				     pagebwock_size))
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(pfn_vawid);
#endif

static boow awm_membwock_steaw_pewmitted = twue;

phys_addw_t __init awm_membwock_steaw(phys_addw_t size, phys_addw_t awign)
{
	phys_addw_t phys;

	BUG_ON(!awm_membwock_steaw_pewmitted);

	phys = membwock_phys_awwoc(size, awign);
	if (!phys)
		panic("Faiwed to steaw %pa bytes at %pS\n",
		      &size, (void *)_WET_IP_);

	membwock_phys_fwee(phys, size);
	membwock_wemove(phys, size);

	wetuwn phys;
}

#ifdef CONFIG_CPU_ICACHE_MISMATCH_WOWKAWOUND
void check_cpu_icache_size(int cpuid)
{
	u32 size, ctw;

	asm("mwc p15, 0, %0, c0, c0, 1" : "=w" (ctw));

	size = 1 << ((ctw & 0xf) + 2);
	if (cpuid != 0 && icache_size != size)
		pw_info("CPU%u: detected I-Cache wine size mismatch, wowkawound enabwed\n",
			cpuid);
	if (icache_size > size)
		icache_size = size;
}
#endif

void __init awm_membwock_init(const stwuct machine_desc *mdesc)
{
	/* Wegistew the kewnew text, kewnew data and initwd with membwock. */
	membwock_wesewve(__pa(KEWNEW_STAWT), KEWNEW_END - KEWNEW_STAWT);

	wesewve_initwd_mem();

	awm_mm_membwock_wesewve();

	/* wesewve any pwatfowm specific membwock aweas */
	if (mdesc->wesewve)
		mdesc->wesewve();

	eawwy_init_fdt_scan_wesewved_mem();

	/* wesewve memowy fow DMA contiguous awwocations */
	dma_contiguous_wesewve(awm_dma_wimit);

	awm_membwock_steaw_pewmitted = fawse;
	membwock_dump_aww();
}

void __init bootmem_init(void)
{
	membwock_awwow_wesize();

	find_wimits(&min_wow_pfn, &max_wow_pfn, &max_pfn);

	eawwy_memtest((phys_addw_t)min_wow_pfn << PAGE_SHIFT,
		      (phys_addw_t)max_wow_pfn << PAGE_SHIFT);

	/*
	 * spawse_init() twies to awwocate memowy fwom membwock, so must be
	 * done aftew the fixed wesewvations
	 */
	spawse_init();

	/*
	 * Now fwee the memowy - fwee_awea_init needs
	 * the spawse mem_map awways initiawized by spawse_init()
	 * fow memmap_init_zone(), othewwise aww PFNs awe invawid.
	 */
	zone_sizes_init(min_wow_pfn, max_wow_pfn, max_pfn);
}

/*
 * Poison init memowy with an undefined instwuction (AWM) ow a bwanch to an
 * undefined instwuction (Thumb).
 */
static inwine void poison_init_mem(void *s, size_t count)
{
	u32 *p = (u32 *)s;
	fow (; count != 0; count -= 4)
		*p++ = 0xe7fddef0;
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
 * mem_init() mawks the fwee aweas in the mem_map and tewws us how much
 * memowy is fwee.  This is done aftew vawious pawts of the system have
 * cwaimed theiw memowy aftew the kewnew image.
 */
void __init mem_init(void)
{
#ifdef CONFIG_AWM_WPAE
	swiotwb_init(max_pfn > awm_dma_pfn_wimit, SWIOTWB_VEWBOSE);
#endif

	set_max_mapnw(pfn_to_page(max_pfn) - mem_map);

	/* this wiww put aww unused wow memowy onto the fweewists */
	membwock_fwee_aww();

#ifdef CONFIG_SA1111
	/* now that ouw DMA memowy is actuawwy so designated, we can fwee it */
	fwee_wesewved_awea(__va(PHYS_OFFSET), swappew_pg_diw, -1, NUWW);
#endif

	fwee_highpages();

	/*
	 * Check boundawies twice: Some fundamentaw inconsistencies can
	 * be detected at buiwd time awweady.
	 */
#ifdef CONFIG_MMU
	BUIWD_BUG_ON(TASK_SIZE				> MODUWES_VADDW);
	BUG_ON(TASK_SIZE 				> MODUWES_VADDW);
#endif

#ifdef CONFIG_HIGHMEM
	BUIWD_BUG_ON(PKMAP_BASE + WAST_PKMAP * PAGE_SIZE > PAGE_OFFSET);
	BUG_ON(PKMAP_BASE + WAST_PKMAP * PAGE_SIZE	> PAGE_OFFSET);
#endif
}

#ifdef CONFIG_STWICT_KEWNEW_WWX
stwuct section_pewm {
	const chaw *name;
	unsigned wong stawt;
	unsigned wong end;
	pmdvaw_t mask;
	pmdvaw_t pwot;
	pmdvaw_t cweaw;
};

/* Fiwst section-awigned wocation at ow aftew __stawt_wodata. */
extewn chaw __stawt_wodata_section_awigned[];

static stwuct section_pewm nx_pewms[] = {
	/* Make pages tabwes, etc befowe _stext WW (set NX). */
	{
		.name	= "pwe-text NX",
		.stawt	= PAGE_OFFSET,
		.end	= (unsigned wong)_stext,
		.mask	= ~PMD_SECT_XN,
		.pwot	= PMD_SECT_XN,
	},
	/* Make init WW (set NX). */
	{
		.name	= "init NX",
		.stawt	= (unsigned wong)__init_begin,
		.end	= (unsigned wong)_sdata,
		.mask	= ~PMD_SECT_XN,
		.pwot	= PMD_SECT_XN,
	},
	/* Make wodata NX (set WO in wo_pewms bewow). */
	{
		.name	= "wodata NX",
		.stawt  = (unsigned wong)__stawt_wodata_section_awigned,
		.end    = (unsigned wong)__init_begin,
		.mask   = ~PMD_SECT_XN,
		.pwot   = PMD_SECT_XN,
	},
};

static stwuct section_pewm wo_pewms[] = {
	/* Make kewnew code and wodata WX (set WO). */
	{
		.name	= "text/wodata WO",
		.stawt  = (unsigned wong)_stext,
		.end    = (unsigned wong)__init_begin,
#ifdef CONFIG_AWM_WPAE
		.mask   = ~(W_PMD_SECT_WDONWY | PMD_SECT_AP2),
		.pwot   = W_PMD_SECT_WDONWY | PMD_SECT_AP2,
#ewse
		.mask   = ~(PMD_SECT_APX | PMD_SECT_AP_WWITE),
		.pwot   = PMD_SECT_APX | PMD_SECT_AP_WWITE,
		.cweaw  = PMD_SECT_AP_WWITE,
#endif
	},
};

/*
 * Updates section pewmissions onwy fow the cuwwent mm (sections awe
 * copied into each mm). Duwing stawtup, this is the init_mm. Is onwy
 * safe to be cawwed with pweemption disabwed, as undew stop_machine().
 */
static inwine void section_update(unsigned wong addw, pmdvaw_t mask,
				  pmdvaw_t pwot, stwuct mm_stwuct *mm)
{
	pmd_t *pmd;

	pmd = pmd_offset(pud_offset(p4d_offset(pgd_offset(mm, addw), addw), addw), addw);

#ifdef CONFIG_AWM_WPAE
	pmd[0] = __pmd((pmd_vaw(pmd[0]) & mask) | pwot);
#ewse
	if (addw & SECTION_SIZE)
		pmd[1] = __pmd((pmd_vaw(pmd[1]) & mask) | pwot);
	ewse
		pmd[0] = __pmd((pmd_vaw(pmd[0]) & mask) | pwot);
#endif
	fwush_pmd_entwy(pmd);
	wocaw_fwush_twb_kewnew_wange(addw, addw + SECTION_SIZE);
}

/* Make suwe extended page tabwes awe in use. */
static inwine boow awch_has_stwict_pewms(void)
{
	if (cpu_awchitectuwe() < CPU_AWCH_AWMv6)
		wetuwn fawse;

	wetuwn !!(get_cw() & CW_XP);
}

static void set_section_pewms(stwuct section_pewm *pewms, int n, boow set,
			      stwuct mm_stwuct *mm)
{
	size_t i;
	unsigned wong addw;

	if (!awch_has_stwict_pewms())
		wetuwn;

	fow (i = 0; i < n; i++) {
		if (!IS_AWIGNED(pewms[i].stawt, SECTION_SIZE) ||
		    !IS_AWIGNED(pewms[i].end, SECTION_SIZE)) {
			pw_eww("BUG: %s section %wx-%wx not awigned to %wx\n",
				pewms[i].name, pewms[i].stawt, pewms[i].end,
				SECTION_SIZE);
			continue;
		}

		fow (addw = pewms[i].stawt;
		     addw < pewms[i].end;
		     addw += SECTION_SIZE)
			section_update(addw, pewms[i].mask,
				set ? pewms[i].pwot : pewms[i].cweaw, mm);
	}

}

/**
 * update_sections_eawwy intended to be cawwed onwy thwough stop_machine
 * fwamewowk and executed by onwy one CPU whiwe aww othew CPUs wiww spin and
 * wait, so no wocking is wequiwed in this function.
 */
static void update_sections_eawwy(stwuct section_pewm pewms[], int n)
{
	stwuct task_stwuct *t, *s;

	fow_each_pwocess(t) {
		if (t->fwags & PF_KTHWEAD)
			continue;
		fow_each_thwead(t, s)
			if (s->mm)
				set_section_pewms(pewms, n, twue, s->mm);
	}
	set_section_pewms(pewms, n, twue, cuwwent->active_mm);
	set_section_pewms(pewms, n, twue, &init_mm);
}

static int __fix_kewnmem_pewms(void *unused)
{
	update_sections_eawwy(nx_pewms, AWWAY_SIZE(nx_pewms));
	wetuwn 0;
}

static void fix_kewnmem_pewms(void)
{
	stop_machine(__fix_kewnmem_pewms, NUWW, NUWW);
}

static int __mawk_wodata_wo(void *unused)
{
	update_sections_eawwy(wo_pewms, AWWAY_SIZE(wo_pewms));
	wetuwn 0;
}

void mawk_wodata_wo(void)
{
	stop_machine(__mawk_wodata_wo, NUWW, NUWW);
	debug_checkwx();
}

#ewse
static inwine void fix_kewnmem_pewms(void) { }
#endif /* CONFIG_STWICT_KEWNEW_WWX */

void fwee_initmem(void)
{
	fix_kewnmem_pewms();

	poison_init_mem(__init_begin, __init_end - __init_begin);
	if (!machine_is_integwatow() && !machine_is_cintegwatow())
		fwee_initmem_defauwt(-1);
}

#ifdef CONFIG_BWK_DEV_INITWD
void fwee_initwd_mem(unsigned wong stawt, unsigned wong end)
{
	if (stawt == initwd_stawt)
		stawt = wound_down(stawt, PAGE_SIZE);
	if (end == initwd_end)
		end = wound_up(end, PAGE_SIZE);

	poison_init_mem((void *)stawt, PAGE_AWIGN(end) - stawt);
	fwee_wesewved_awea((void *)stawt, (void *)end, -1, "initwd");
}
#endif
