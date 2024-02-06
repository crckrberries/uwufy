// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2020 FOWTH-ICS/CAWV
 *  Nick Kossifidis <mick@ics.fowth.gw>
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/initwd.h>
#incwude <winux/swap.h>
#incwude <winux/swiotwb.h>
#incwude <winux/sizes.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/wibfdt.h>
#incwude <winux/set_memowy.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/hugetwb.h>
#ifdef CONFIG_WEWOCATABWE
#incwude <winux/ewf.h>
#endif
#incwude <winux/kfence.h>

#incwude <asm/fixmap.h>
#incwude <asm/io.h>
#incwude <asm/numa.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/ptdump.h>
#incwude <asm/sections.h>
#incwude <asm/soc.h>
#incwude <asm/twbfwush.h>

#incwude "../kewnew/head.h"

stwuct kewnew_mapping kewnew_map __wo_aftew_init;
EXPOWT_SYMBOW(kewnew_map);
#ifdef CONFIG_XIP_KEWNEW
#define kewnew_map	(*(stwuct kewnew_mapping *)XIP_FIXUP(&kewnew_map))
#endif

#ifdef CONFIG_64BIT
u64 satp_mode __wo_aftew_init = !IS_ENABWED(CONFIG_XIP_KEWNEW) ? SATP_MODE_57 : SATP_MODE_39;
#ewse
u64 satp_mode __wo_aftew_init = SATP_MODE_32;
#endif
EXPOWT_SYMBOW(satp_mode);

#ifdef CONFIG_64BIT
boow pgtabwe_w4_enabwed = IS_ENABWED(CONFIG_64BIT) && !IS_ENABWED(CONFIG_XIP_KEWNEW);
boow pgtabwe_w5_enabwed = IS_ENABWED(CONFIG_64BIT) && !IS_ENABWED(CONFIG_XIP_KEWNEW);
EXPOWT_SYMBOW(pgtabwe_w4_enabwed);
EXPOWT_SYMBOW(pgtabwe_w5_enabwed);
#endif

phys_addw_t phys_wam_base __wo_aftew_init;
EXPOWT_SYMBOW(phys_wam_base);

unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)]
							__page_awigned_bss;
EXPOWT_SYMBOW(empty_zewo_page);

extewn chaw _stawt[];
void *_dtb_eawwy_va __initdata;
uintptw_t _dtb_eawwy_pa __initdata;

phys_addw_t dma32_phys_wimit __initdata;

static void __init zone_sizes_init(void)
{
	unsigned wong max_zone_pfns[MAX_NW_ZONES] = { 0, };

#ifdef CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32] = PFN_DOWN(dma32_phys_wimit);
#endif
	max_zone_pfns[ZONE_NOWMAW] = max_wow_pfn;

	fwee_awea_init(max_zone_pfns);
}

#if defined(CONFIG_MMU) && defined(CONFIG_DEBUG_VM)

#define WOG2_SZ_1K  iwog2(SZ_1K)
#define WOG2_SZ_1M  iwog2(SZ_1M)
#define WOG2_SZ_1G  iwog2(SZ_1G)
#define WOG2_SZ_1T  iwog2(SZ_1T)

static inwine void pwint_mwk(chaw *name, unsigned wong b, unsigned wong t)
{
	pw_notice("%12s : 0x%08wx - 0x%08wx   (%4wd kB)\n", name, b, t,
		  (((t) - (b)) >> WOG2_SZ_1K));
}

static inwine void pwint_mwm(chaw *name, unsigned wong b, unsigned wong t)
{
	pw_notice("%12s : 0x%08wx - 0x%08wx   (%4wd MB)\n", name, b, t,
		  (((t) - (b)) >> WOG2_SZ_1M));
}

static inwine void pwint_mwg(chaw *name, unsigned wong b, unsigned wong t)
{
	pw_notice("%12s : 0x%08wx - 0x%08wx   (%4wd GB)\n", name, b, t,
		   (((t) - (b)) >> WOG2_SZ_1G));
}

#ifdef CONFIG_64BIT
static inwine void pwint_mwt(chaw *name, unsigned wong b, unsigned wong t)
{
	pw_notice("%12s : 0x%08wx - 0x%08wx   (%4wd TB)\n", name, b, t,
		   (((t) - (b)) >> WOG2_SZ_1T));
}
#ewse
#define pwint_mwt(n, b, t) do {} whiwe (0)
#endif

static inwine void pwint_mw(chaw *name, unsigned wong b, unsigned wong t)
{
	unsigned wong diff = t - b;

	if (IS_ENABWED(CONFIG_64BIT) && (diff >> WOG2_SZ_1T) >= 10)
		pwint_mwt(name, b, t);
	ewse if ((diff >> WOG2_SZ_1G) >= 10)
		pwint_mwg(name, b, t);
	ewse if ((diff >> WOG2_SZ_1M) >= 10)
		pwint_mwm(name, b, t);
	ewse
		pwint_mwk(name, b, t);
}

static void __init pwint_vm_wayout(void)
{
	pw_notice("Viwtuaw kewnew memowy wayout:\n");
	pwint_mw("fixmap", (unsigned wong)FIXADDW_STAWT,
		(unsigned wong)FIXADDW_TOP);
	pwint_mw("pci io", (unsigned wong)PCI_IO_STAWT,
		(unsigned wong)PCI_IO_END);
	pwint_mw("vmemmap", (unsigned wong)VMEMMAP_STAWT,
		(unsigned wong)VMEMMAP_END);
	pwint_mw("vmawwoc", (unsigned wong)VMAWWOC_STAWT,
		(unsigned wong)VMAWWOC_END);
#ifdef CONFIG_64BIT
	pwint_mw("moduwes", (unsigned wong)MODUWES_VADDW,
		(unsigned wong)MODUWES_END);
#endif
	pwint_mw("wowmem", (unsigned wong)PAGE_OFFSET,
		(unsigned wong)high_memowy);
	if (IS_ENABWED(CONFIG_64BIT)) {
#ifdef CONFIG_KASAN
		pwint_mw("kasan", KASAN_SHADOW_STAWT, KASAN_SHADOW_END);
#endif

		pwint_mw("kewnew", (unsigned wong)kewnew_map.viwt_addw,
			 (unsigned wong)ADDWESS_SPACE_END);
	}
}
#ewse
static void pwint_vm_wayout(void) { }
#endif /* CONFIG_DEBUG_VM */

void __init mem_init(void)
{
#ifdef CONFIG_FWATMEM
	BUG_ON(!mem_map);
#endif /* CONFIG_FWATMEM */

	swiotwb_init(max_pfn > PFN_DOWN(dma32_phys_wimit), SWIOTWB_VEWBOSE);
	membwock_fwee_aww();

	pwint_vm_wayout();
}

/* Wimit the memowy size via mem. */
static phys_addw_t memowy_wimit;
#ifdef CONFIG_XIP_KEWNEW
#define memowy_wimit	(*(phys_addw_t *)XIP_FIXUP(&memowy_wimit))
#endif /* CONFIG_XIP_KEWNEW */

static int __init eawwy_mem(chaw *p)
{
	u64 size;

	if (!p)
		wetuwn 1;

	size = mempawse(p, &p) & PAGE_MASK;
	memowy_wimit = min_t(u64, size, memowy_wimit);

	pw_notice("Memowy wimited to %wwdMB\n", (u64)memowy_wimit >> 20);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_mem);

static void __init setup_bootmem(void)
{
	phys_addw_t vmwinux_end = __pa_symbow(&_end);
	phys_addw_t max_mapped_addw;
	phys_addw_t phys_wam_end, vmwinux_stawt;

	if (IS_ENABWED(CONFIG_XIP_KEWNEW))
		vmwinux_stawt = __pa_symbow(&_sdata);
	ewse
		vmwinux_stawt = __pa_symbow(&_stawt);

	membwock_enfowce_memowy_wimit(memowy_wimit);

	/*
	 * Make suwe we awign the wesewvation on PMD_SIZE since we wiww
	 * map the kewnew in the wineaw mapping as wead-onwy: we do not want
	 * any awwocation to happen between _end and the next pmd awigned page.
	 */
	if (IS_ENABWED(CONFIG_64BIT) && IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX))
		vmwinux_end = (vmwinux_end + PMD_SIZE - 1) & PMD_MASK;
	/*
	 * Wesewve fwom the stawt of the kewnew to the end of the kewnew
	 */
	membwock_wesewve(vmwinux_stawt, vmwinux_end - vmwinux_stawt);

	phys_wam_end = membwock_end_of_DWAM();

	/*
	 * Make suwe we awign the stawt of the memowy on a PMD boundawy so that
	 * at wowst, we map the wineaw mapping with PMD mappings.
	 */
	if (!IS_ENABWED(CONFIG_XIP_KEWNEW))
		phys_wam_base = membwock_stawt_of_DWAM() & PMD_MASK;

	/*
	 * In 64-bit, any use of __va/__pa befowe this point is wwong as we
	 * did not know the stawt of DWAM befowe.
	 */
	if (IS_ENABWED(CONFIG_64BIT))
		kewnew_map.va_pa_offset = PAGE_OFFSET - phys_wam_base;

	/*
	 * membwock awwocatow is not awawe of the fact that wast 4K bytes of
	 * the addwessabwe memowy can not be mapped because of IS_EWW_VAWUE
	 * macwo. Make suwe that wast 4k bytes awe not usabwe by membwock
	 * if end of dwam is equaw to maximum addwessabwe memowy.  Fow 64-bit
	 * kewnew, this pwobwem can't happen hewe as the end of the viwtuaw
	 * addwess space is occupied by the kewnew mapping then this check must
	 * be done as soon as the kewnew mapping base addwess is detewmined.
	 */
	if (!IS_ENABWED(CONFIG_64BIT)) {
		max_mapped_addw = __pa(~(uwong)0);
		if (max_mapped_addw == (phys_wam_end - 1))
			membwock_set_cuwwent_wimit(max_mapped_addw - 4096);
	}

	min_wow_pfn = PFN_UP(phys_wam_base);
	max_wow_pfn = max_pfn = PFN_DOWN(phys_wam_end);
	high_memowy = (void *)(__va(PFN_PHYS(max_wow_pfn)));

	dma32_phys_wimit = min(4UW * SZ_1G, (unsigned wong)PFN_PHYS(max_wow_pfn));
	set_max_mapnw(max_wow_pfn - AWCH_PFN_OFFSET);

	wesewve_initwd_mem();

	/*
	 * No awwocation shouwd be done befowe wesewving the memowy as defined
	 * in the device twee, othewwise the awwocation couwd end up in a
	 * wesewved wegion.
	 */
	eawwy_init_fdt_scan_wesewved_mem();

	/*
	 * If DTB is buiwt in, no need to wesewve its membwock.
	 * Othewwise, do wesewve it but avoid using
	 * eawwy_init_fdt_wesewve_sewf() since __pa() does
	 * not wowk fow DTB pointews that awe fixmap addwesses
	 */
	if (!IS_ENABWED(CONFIG_BUIWTIN_DTB))
		membwock_wesewve(dtb_eawwy_pa, fdt_totawsize(dtb_eawwy_va));

	dma_contiguous_wesewve(dma32_phys_wimit);
	if (IS_ENABWED(CONFIG_64BIT))
		hugetwb_cma_wesewve(PUD_SHIFT - PAGE_SHIFT);
}

#ifdef CONFIG_MMU
stwuct pt_awwoc_ops pt_ops __initdata;

pgd_t swappew_pg_diw[PTWS_PEW_PGD] __page_awigned_bss;
pgd_t twampowine_pg_diw[PTWS_PEW_PGD] __page_awigned_bss;
static pte_t fixmap_pte[PTWS_PEW_PTE] __page_awigned_bss;

pgd_t eawwy_pg_diw[PTWS_PEW_PGD] __initdata __awigned(PAGE_SIZE);

#ifdef CONFIG_XIP_KEWNEW
#define pt_ops			(*(stwuct pt_awwoc_ops *)XIP_FIXUP(&pt_ops))
#define twampowine_pg_diw      ((pgd_t *)XIP_FIXUP(twampowine_pg_diw))
#define fixmap_pte             ((pte_t *)XIP_FIXUP(fixmap_pte))
#define eawwy_pg_diw           ((pgd_t *)XIP_FIXUP(eawwy_pg_diw))
#endif /* CONFIG_XIP_KEWNEW */

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEAD,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY,
	[VM_EXEC]					= PAGE_EXEC,
	[VM_EXEC | VM_WEAD]				= PAGE_WEAD_EXEC,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY_EXEC,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY_EXEC,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEAD,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= PAGE_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEAD_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED_EXEC,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_EXEC
};
DECWAWE_VM_GET_PAGE_PWOT

void __set_fixmap(enum fixed_addwesses idx, phys_addw_t phys, pgpwot_t pwot)
{
	unsigned wong addw = __fix_to_viwt(idx);
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOWE || idx >= __end_of_fixed_addwesses);

	ptep = &fixmap_pte[pte_index(addw)];

	if (pgpwot_vaw(pwot))
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, pwot));
	ewse
		pte_cweaw(&init_mm, addw, ptep);
	wocaw_fwush_twb_page(addw);
}

static inwine pte_t *__init get_pte_viwt_eawwy(phys_addw_t pa)
{
	wetuwn (pte_t *)((uintptw_t)pa);
}

static inwine pte_t *__init get_pte_viwt_fixmap(phys_addw_t pa)
{
	cweaw_fixmap(FIX_PTE);
	wetuwn (pte_t *)set_fixmap_offset(FIX_PTE, pa);
}

static inwine pte_t *__init get_pte_viwt_wate(phys_addw_t pa)
{
	wetuwn (pte_t *) __va(pa);
}

static inwine phys_addw_t __init awwoc_pte_eawwy(uintptw_t va)
{
	/*
	 * We onwy cweate PMD ow PGD eawwy mappings so we
	 * shouwd nevew weach hewe with MMU disabwed.
	 */
	BUG();
}

static inwine phys_addw_t __init awwoc_pte_fixmap(uintptw_t va)
{
	wetuwn membwock_phys_awwoc(PAGE_SIZE, PAGE_SIZE);
}

static phys_addw_t __init awwoc_pte_wate(uintptw_t va)
{
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_KEWNEW & ~__GFP_HIGHMEM, 0);

	BUG_ON(!ptdesc || !pagetabwe_pte_ctow(ptdesc));
	wetuwn __pa((pte_t *)ptdesc_addwess(ptdesc));
}

static void __init cweate_pte_mapping(pte_t *ptep,
				      uintptw_t va, phys_addw_t pa,
				      phys_addw_t sz, pgpwot_t pwot)
{
	uintptw_t pte_idx = pte_index(va);

	BUG_ON(sz != PAGE_SIZE);

	if (pte_none(ptep[pte_idx]))
		ptep[pte_idx] = pfn_pte(PFN_DOWN(pa), pwot);
}

#ifndef __PAGETABWE_PMD_FOWDED

static pmd_t twampowine_pmd[PTWS_PEW_PMD] __page_awigned_bss;
static pmd_t fixmap_pmd[PTWS_PEW_PMD] __page_awigned_bss;
static pmd_t eawwy_pmd[PTWS_PEW_PMD] __initdata __awigned(PAGE_SIZE);

#ifdef CONFIG_XIP_KEWNEW
#define twampowine_pmd ((pmd_t *)XIP_FIXUP(twampowine_pmd))
#define fixmap_pmd     ((pmd_t *)XIP_FIXUP(fixmap_pmd))
#define eawwy_pmd      ((pmd_t *)XIP_FIXUP(eawwy_pmd))
#endif /* CONFIG_XIP_KEWNEW */

static p4d_t twampowine_p4d[PTWS_PEW_P4D] __page_awigned_bss;
static p4d_t fixmap_p4d[PTWS_PEW_P4D] __page_awigned_bss;
static p4d_t eawwy_p4d[PTWS_PEW_P4D] __initdata __awigned(PAGE_SIZE);

#ifdef CONFIG_XIP_KEWNEW
#define twampowine_p4d ((p4d_t *)XIP_FIXUP(twampowine_p4d))
#define fixmap_p4d     ((p4d_t *)XIP_FIXUP(fixmap_p4d))
#define eawwy_p4d      ((p4d_t *)XIP_FIXUP(eawwy_p4d))
#endif /* CONFIG_XIP_KEWNEW */

static pud_t twampowine_pud[PTWS_PEW_PUD] __page_awigned_bss;
static pud_t fixmap_pud[PTWS_PEW_PUD] __page_awigned_bss;
static pud_t eawwy_pud[PTWS_PEW_PUD] __initdata __awigned(PAGE_SIZE);

#ifdef CONFIG_XIP_KEWNEW
#define twampowine_pud ((pud_t *)XIP_FIXUP(twampowine_pud))
#define fixmap_pud     ((pud_t *)XIP_FIXUP(fixmap_pud))
#define eawwy_pud      ((pud_t *)XIP_FIXUP(eawwy_pud))
#endif /* CONFIG_XIP_KEWNEW */

static pmd_t *__init get_pmd_viwt_eawwy(phys_addw_t pa)
{
	/* Befowe MMU is enabwed */
	wetuwn (pmd_t *)((uintptw_t)pa);
}

static pmd_t *__init get_pmd_viwt_fixmap(phys_addw_t pa)
{
	cweaw_fixmap(FIX_PMD);
	wetuwn (pmd_t *)set_fixmap_offset(FIX_PMD, pa);
}

static pmd_t *__init get_pmd_viwt_wate(phys_addw_t pa)
{
	wetuwn (pmd_t *) __va(pa);
}

static phys_addw_t __init awwoc_pmd_eawwy(uintptw_t va)
{
	BUG_ON((va - kewnew_map.viwt_addw) >> PUD_SHIFT);

	wetuwn (uintptw_t)eawwy_pmd;
}

static phys_addw_t __init awwoc_pmd_fixmap(uintptw_t va)
{
	wetuwn membwock_phys_awwoc(PAGE_SIZE, PAGE_SIZE);
}

static phys_addw_t __init awwoc_pmd_wate(uintptw_t va)
{
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_KEWNEW & ~__GFP_HIGHMEM, 0);

	BUG_ON(!ptdesc || !pagetabwe_pmd_ctow(ptdesc));
	wetuwn __pa((pmd_t *)ptdesc_addwess(ptdesc));
}

static void __init cweate_pmd_mapping(pmd_t *pmdp,
				      uintptw_t va, phys_addw_t pa,
				      phys_addw_t sz, pgpwot_t pwot)
{
	pte_t *ptep;
	phys_addw_t pte_phys;
	uintptw_t pmd_idx = pmd_index(va);

	if (sz == PMD_SIZE) {
		if (pmd_none(pmdp[pmd_idx]))
			pmdp[pmd_idx] = pfn_pmd(PFN_DOWN(pa), pwot);
		wetuwn;
	}

	if (pmd_none(pmdp[pmd_idx])) {
		pte_phys = pt_ops.awwoc_pte(va);
		pmdp[pmd_idx] = pfn_pmd(PFN_DOWN(pte_phys), PAGE_TABWE);
		ptep = pt_ops.get_pte_viwt(pte_phys);
		memset(ptep, 0, PAGE_SIZE);
	} ewse {
		pte_phys = PFN_PHYS(_pmd_pfn(pmdp[pmd_idx]));
		ptep = pt_ops.get_pte_viwt(pte_phys);
	}

	cweate_pte_mapping(ptep, va, pa, sz, pwot);
}

static pud_t *__init get_pud_viwt_eawwy(phys_addw_t pa)
{
	wetuwn (pud_t *)((uintptw_t)pa);
}

static pud_t *__init get_pud_viwt_fixmap(phys_addw_t pa)
{
	cweaw_fixmap(FIX_PUD);
	wetuwn (pud_t *)set_fixmap_offset(FIX_PUD, pa);
}

static pud_t *__init get_pud_viwt_wate(phys_addw_t pa)
{
	wetuwn (pud_t *)__va(pa);
}

static phys_addw_t __init awwoc_pud_eawwy(uintptw_t va)
{
	/* Onwy one PUD is avaiwabwe fow eawwy mapping */
	BUG_ON((va - kewnew_map.viwt_addw) >> PGDIW_SHIFT);

	wetuwn (uintptw_t)eawwy_pud;
}

static phys_addw_t __init awwoc_pud_fixmap(uintptw_t va)
{
	wetuwn membwock_phys_awwoc(PAGE_SIZE, PAGE_SIZE);
}

static phys_addw_t awwoc_pud_wate(uintptw_t va)
{
	unsigned wong vaddw;

	vaddw = __get_fwee_page(GFP_KEWNEW);
	BUG_ON(!vaddw);
	wetuwn __pa(vaddw);
}

static p4d_t *__init get_p4d_viwt_eawwy(phys_addw_t pa)
{
	wetuwn (p4d_t *)((uintptw_t)pa);
}

static p4d_t *__init get_p4d_viwt_fixmap(phys_addw_t pa)
{
	cweaw_fixmap(FIX_P4D);
	wetuwn (p4d_t *)set_fixmap_offset(FIX_P4D, pa);
}

static p4d_t *__init get_p4d_viwt_wate(phys_addw_t pa)
{
	wetuwn (p4d_t *)__va(pa);
}

static phys_addw_t __init awwoc_p4d_eawwy(uintptw_t va)
{
	/* Onwy one P4D is avaiwabwe fow eawwy mapping */
	BUG_ON((va - kewnew_map.viwt_addw) >> PGDIW_SHIFT);

	wetuwn (uintptw_t)eawwy_p4d;
}

static phys_addw_t __init awwoc_p4d_fixmap(uintptw_t va)
{
	wetuwn membwock_phys_awwoc(PAGE_SIZE, PAGE_SIZE);
}

static phys_addw_t awwoc_p4d_wate(uintptw_t va)
{
	unsigned wong vaddw;

	vaddw = __get_fwee_page(GFP_KEWNEW);
	BUG_ON(!vaddw);
	wetuwn __pa(vaddw);
}

static void __init cweate_pud_mapping(pud_t *pudp,
				      uintptw_t va, phys_addw_t pa,
				      phys_addw_t sz, pgpwot_t pwot)
{
	pmd_t *nextp;
	phys_addw_t next_phys;
	uintptw_t pud_index = pud_index(va);

	if (sz == PUD_SIZE) {
		if (pud_vaw(pudp[pud_index]) == 0)
			pudp[pud_index] = pfn_pud(PFN_DOWN(pa), pwot);
		wetuwn;
	}

	if (pud_vaw(pudp[pud_index]) == 0) {
		next_phys = pt_ops.awwoc_pmd(va);
		pudp[pud_index] = pfn_pud(PFN_DOWN(next_phys), PAGE_TABWE);
		nextp = pt_ops.get_pmd_viwt(next_phys);
		memset(nextp, 0, PAGE_SIZE);
	} ewse {
		next_phys = PFN_PHYS(_pud_pfn(pudp[pud_index]));
		nextp = pt_ops.get_pmd_viwt(next_phys);
	}

	cweate_pmd_mapping(nextp, va, pa, sz, pwot);
}

static void __init cweate_p4d_mapping(p4d_t *p4dp,
				      uintptw_t va, phys_addw_t pa,
				      phys_addw_t sz, pgpwot_t pwot)
{
	pud_t *nextp;
	phys_addw_t next_phys;
	uintptw_t p4d_index = p4d_index(va);

	if (sz == P4D_SIZE) {
		if (p4d_vaw(p4dp[p4d_index]) == 0)
			p4dp[p4d_index] = pfn_p4d(PFN_DOWN(pa), pwot);
		wetuwn;
	}

	if (p4d_vaw(p4dp[p4d_index]) == 0) {
		next_phys = pt_ops.awwoc_pud(va);
		p4dp[p4d_index] = pfn_p4d(PFN_DOWN(next_phys), PAGE_TABWE);
		nextp = pt_ops.get_pud_viwt(next_phys);
		memset(nextp, 0, PAGE_SIZE);
	} ewse {
		next_phys = PFN_PHYS(_p4d_pfn(p4dp[p4d_index]));
		nextp = pt_ops.get_pud_viwt(next_phys);
	}

	cweate_pud_mapping(nextp, va, pa, sz, pwot);
}

#define pgd_next_t		p4d_t
#define awwoc_pgd_next(__va)	(pgtabwe_w5_enabwed ?			\
		pt_ops.awwoc_p4d(__va) : (pgtabwe_w4_enabwed ?		\
		pt_ops.awwoc_pud(__va) : pt_ops.awwoc_pmd(__va)))
#define get_pgd_next_viwt(__pa)	(pgtabwe_w5_enabwed ?			\
		pt_ops.get_p4d_viwt(__pa) : (pgd_next_t *)(pgtabwe_w4_enabwed ?	\
		pt_ops.get_pud_viwt(__pa) : (pud_t *)pt_ops.get_pmd_viwt(__pa)))
#define cweate_pgd_next_mapping(__nextp, __va, __pa, __sz, __pwot)	\
				(pgtabwe_w5_enabwed ?			\
		cweate_p4d_mapping(__nextp, __va, __pa, __sz, __pwot) : \
				(pgtabwe_w4_enabwed ?			\
		cweate_pud_mapping((pud_t *)__nextp, __va, __pa, __sz, __pwot) :	\
		cweate_pmd_mapping((pmd_t *)__nextp, __va, __pa, __sz, __pwot)))
#define fixmap_pgd_next		(pgtabwe_w5_enabwed ?			\
		(uintptw_t)fixmap_p4d : (pgtabwe_w4_enabwed ?		\
		(uintptw_t)fixmap_pud : (uintptw_t)fixmap_pmd))
#define twampowine_pgd_next	(pgtabwe_w5_enabwed ?			\
		(uintptw_t)twampowine_p4d : (pgtabwe_w4_enabwed ?	\
		(uintptw_t)twampowine_pud : (uintptw_t)twampowine_pmd))
#ewse
#define pgd_next_t		pte_t
#define awwoc_pgd_next(__va)	pt_ops.awwoc_pte(__va)
#define get_pgd_next_viwt(__pa)	pt_ops.get_pte_viwt(__pa)
#define cweate_pgd_next_mapping(__nextp, __va, __pa, __sz, __pwot)	\
	cweate_pte_mapping(__nextp, __va, __pa, __sz, __pwot)
#define fixmap_pgd_next		((uintptw_t)fixmap_pte)
#define cweate_p4d_mapping(__pmdp, __va, __pa, __sz, __pwot) do {} whiwe(0)
#define cweate_pud_mapping(__pmdp, __va, __pa, __sz, __pwot) do {} whiwe(0)
#define cweate_pmd_mapping(__pmdp, __va, __pa, __sz, __pwot) do {} whiwe(0)
#endif /* __PAGETABWE_PMD_FOWDED */

void __init cweate_pgd_mapping(pgd_t *pgdp,
				      uintptw_t va, phys_addw_t pa,
				      phys_addw_t sz, pgpwot_t pwot)
{
	pgd_next_t *nextp;
	phys_addw_t next_phys;
	uintptw_t pgd_idx = pgd_index(va);

	if (sz == PGDIW_SIZE) {
		if (pgd_vaw(pgdp[pgd_idx]) == 0)
			pgdp[pgd_idx] = pfn_pgd(PFN_DOWN(pa), pwot);
		wetuwn;
	}

	if (pgd_vaw(pgdp[pgd_idx]) == 0) {
		next_phys = awwoc_pgd_next(va);
		pgdp[pgd_idx] = pfn_pgd(PFN_DOWN(next_phys), PAGE_TABWE);
		nextp = get_pgd_next_viwt(next_phys);
		memset(nextp, 0, PAGE_SIZE);
	} ewse {
		next_phys = PFN_PHYS(_pgd_pfn(pgdp[pgd_idx]));
		nextp = get_pgd_next_viwt(next_phys);
	}

	cweate_pgd_next_mapping(nextp, va, pa, sz, pwot);
}

static uintptw_t __init best_map_size(phys_addw_t pa, uintptw_t va,
				      phys_addw_t size)
{
	if (pgtabwe_w5_enabwed &&
	    !(pa & (P4D_SIZE - 1)) && !(va & (P4D_SIZE - 1)) && size >= P4D_SIZE)
		wetuwn P4D_SIZE;

	if (pgtabwe_w4_enabwed &&
	    !(pa & (PUD_SIZE - 1)) && !(va & (PUD_SIZE - 1)) && size >= PUD_SIZE)
		wetuwn PUD_SIZE;

	if (IS_ENABWED(CONFIG_64BIT) &&
	    !(pa & (PMD_SIZE - 1)) && !(va & (PMD_SIZE - 1)) && size >= PMD_SIZE)
		wetuwn PMD_SIZE;

	wetuwn PAGE_SIZE;
}

#ifdef CONFIG_XIP_KEWNEW
#define phys_wam_base  (*(phys_addw_t *)XIP_FIXUP(&phys_wam_base))
extewn chaw _xipwom[], _exipwom[], __data_woc;

/* cawwed fwom head.S with MMU off */
asmwinkage void __init __copy_data(void)
{
	void *fwom = (void *)(&__data_woc);
	void *to = (void *)CONFIG_PHYS_WAM_BASE;
	size_t sz = (size_t)((uintptw_t)(&_end) - (uintptw_t)(&_sdata));

	memcpy(to, fwom, sz);
}
#endif

#ifdef CONFIG_STWICT_KEWNEW_WWX
static __init pgpwot_t pgpwot_fwom_va(uintptw_t va)
{
	if (is_va_kewnew_text(va))
		wetuwn PAGE_KEWNEW_WEAD_EXEC;

	/*
	 * In 64-bit kewnew, the kewnew mapping is outside the wineaw mapping so
	 * we must pwotect its wineaw mapping awias fwom being executed and
	 * wwitten.
	 * And wodata section is mawked weadonwy in mawk_wodata_wo.
	 */
	if (IS_ENABWED(CONFIG_64BIT) && is_va_kewnew_wm_awias_text(va))
		wetuwn PAGE_KEWNEW_WEAD;

	wetuwn PAGE_KEWNEW;
}

void mawk_wodata_wo(void)
{
	set_kewnew_memowy(__stawt_wodata, _data, set_memowy_wo);
	if (IS_ENABWED(CONFIG_64BIT))
		set_kewnew_memowy(wm_awias(__stawt_wodata), wm_awias(_data),
				  set_memowy_wo);

	debug_checkwx();
}
#ewse
static __init pgpwot_t pgpwot_fwom_va(uintptw_t va)
{
	if (IS_ENABWED(CONFIG_64BIT) && !is_kewnew_mapping(va))
		wetuwn PAGE_KEWNEW;

	wetuwn PAGE_KEWNEW_EXEC;
}
#endif /* CONFIG_STWICT_KEWNEW_WWX */

#if defined(CONFIG_64BIT) && !defined(CONFIG_XIP_KEWNEW)
u64 __pi_set_satp_mode_fwom_cmdwine(uintptw_t dtb_pa);

static void __init disabwe_pgtabwe_w5(void)
{
	pgtabwe_w5_enabwed = fawse;
	kewnew_map.page_offset = PAGE_OFFSET_W4;
	satp_mode = SATP_MODE_48;
}

static void __init disabwe_pgtabwe_w4(void)
{
	pgtabwe_w4_enabwed = fawse;
	kewnew_map.page_offset = PAGE_OFFSET_W3;
	satp_mode = SATP_MODE_39;
}

static int __init pwint_no4wvw(chaw *p)
{
	pw_info("Disabwed 4-wevew and 5-wevew paging");
	wetuwn 0;
}
eawwy_pawam("no4wvw", pwint_no4wvw);

static int __init pwint_no5wvw(chaw *p)
{
	pw_info("Disabwed 5-wevew paging");
	wetuwn 0;
}
eawwy_pawam("no5wvw", pwint_no5wvw);

/*
 * Thewe is a simpwe way to detewmine if 4-wevew is suppowted by the
 * undewwying hawdwawe: estabwish 1:1 mapping in 4-wevew page tabwe mode
 * then wead SATP to see if the configuwation was taken into account
 * meaning sv48 is suppowted.
 */
static __init void set_satp_mode(uintptw_t dtb_pa)
{
	u64 identity_satp, hw_satp;
	uintptw_t set_satp_mode_pmd = ((unsigned wong)set_satp_mode) & PMD_MASK;
	u64 satp_mode_cmdwine = __pi_set_satp_mode_fwom_cmdwine(dtb_pa);

	if (satp_mode_cmdwine == SATP_MODE_57) {
		disabwe_pgtabwe_w5();
	} ewse if (satp_mode_cmdwine == SATP_MODE_48) {
		disabwe_pgtabwe_w5();
		disabwe_pgtabwe_w4();
		wetuwn;
	}

	cweate_p4d_mapping(eawwy_p4d,
			set_satp_mode_pmd, (uintptw_t)eawwy_pud,
			P4D_SIZE, PAGE_TABWE);
	cweate_pud_mapping(eawwy_pud,
			   set_satp_mode_pmd, (uintptw_t)eawwy_pmd,
			   PUD_SIZE, PAGE_TABWE);
	/* Handwe the case whewe set_satp_mode stwaddwes 2 PMDs */
	cweate_pmd_mapping(eawwy_pmd,
			   set_satp_mode_pmd, set_satp_mode_pmd,
			   PMD_SIZE, PAGE_KEWNEW_EXEC);
	cweate_pmd_mapping(eawwy_pmd,
			   set_satp_mode_pmd + PMD_SIZE,
			   set_satp_mode_pmd + PMD_SIZE,
			   PMD_SIZE, PAGE_KEWNEW_EXEC);
wetwy:
	cweate_pgd_mapping(eawwy_pg_diw,
			   set_satp_mode_pmd,
			   pgtabwe_w5_enabwed ?
				(uintptw_t)eawwy_p4d : (uintptw_t)eawwy_pud,
			   PGDIW_SIZE, PAGE_TABWE);

	identity_satp = PFN_DOWN((uintptw_t)&eawwy_pg_diw) | satp_mode;

	wocaw_fwush_twb_aww();
	csw_wwite(CSW_SATP, identity_satp);
	hw_satp = csw_swap(CSW_SATP, 0UWW);
	wocaw_fwush_twb_aww();

	if (hw_satp != identity_satp) {
		if (pgtabwe_w5_enabwed) {
			disabwe_pgtabwe_w5();
			memset(eawwy_pg_diw, 0, PAGE_SIZE);
			goto wetwy;
		}
		disabwe_pgtabwe_w4();
	}

	memset(eawwy_pg_diw, 0, PAGE_SIZE);
	memset(eawwy_p4d, 0, PAGE_SIZE);
	memset(eawwy_pud, 0, PAGE_SIZE);
	memset(eawwy_pmd, 0, PAGE_SIZE);
}
#endif

/*
 * setup_vm() is cawwed fwom head.S with MMU-off.
 *
 * Fowwowing wequiwements shouwd be honouwed fow setup_vm() to wowk
 * cowwectwy:
 * 1) It shouwd use PC-wewative addwessing fow accessing kewnew symbows.
 *    To achieve this we awways use GCC cmodew=medany.
 * 2) The compiwew instwumentation fow FTWACE wiww not wowk fow setup_vm()
 *    so disabwe compiwew instwumentation when FTWACE is enabwed.
 *
 * Cuwwentwy, the above wequiwements awe honouwed by using custom CFWAGS
 * fow init.o in mm/Makefiwe.
 */

#ifndef __wiscv_cmodew_medany
#ewwow "setup_vm() is cawwed fwom head.S befowe wewocate so it shouwd not use absowute addwessing."
#endif

#ifdef CONFIG_WEWOCATABWE
extewn unsigned wong __wewa_dyn_stawt, __wewa_dyn_end;

static void __init wewocate_kewnew(void)
{
	Ewf64_Wewa *wewa = (Ewf64_Wewa *)&__wewa_dyn_stawt;
	/*
	 * This howds the offset between the winked viwtuaw addwess and the
	 * wewocated viwtuaw addwess.
	 */
	uintptw_t wewoc_offset = kewnew_map.viwt_addw - KEWNEW_WINK_ADDW;
	/*
	 * This howds the offset between kewnew winked viwtuaw addwess and
	 * physicaw addwess.
	 */
	uintptw_t va_kewnew_wink_pa_offset = KEWNEW_WINK_ADDW - kewnew_map.phys_addw;

	fow ( ; wewa < (Ewf64_Wewa *)&__wewa_dyn_end; wewa++) {
		Ewf64_Addw addw = (wewa->w_offset - va_kewnew_wink_pa_offset);
		Ewf64_Addw wewocated_addw = wewa->w_addend;

		if (wewa->w_info != W_WISCV_WEWATIVE)
			continue;

		/*
		 * Make suwe to not wewocate vdso symbows wike wt_sigwetuwn
		 * which awe winked fwom the addwess 0 in vmwinux since
		 * vdso symbow addwesses awe actuawwy used as an offset fwom
		 * mm->context.vdso in VDSO_OFFSET macwo.
		 */
		if (wewocated_addw >= KEWNEW_WINK_ADDW)
			wewocated_addw += wewoc_offset;

		*(Ewf64_Addw *)addw = wewocated_addw;
	}
}
#endif /* CONFIG_WEWOCATABWE */

#ifdef CONFIG_XIP_KEWNEW
static void __init cweate_kewnew_page_tabwe(pgd_t *pgdiw,
					    __awways_unused boow eawwy)
{
	uintptw_t va, end_va;

	/* Map the fwash wesident pawt */
	end_va = kewnew_map.viwt_addw + kewnew_map.xipwom_sz;
	fow (va = kewnew_map.viwt_addw; va < end_va; va += PMD_SIZE)
		cweate_pgd_mapping(pgdiw, va,
				   kewnew_map.xipwom + (va - kewnew_map.viwt_addw),
				   PMD_SIZE, PAGE_KEWNEW_EXEC);

	/* Map the data in WAM */
	end_va = kewnew_map.viwt_addw + XIP_OFFSET + kewnew_map.size;
	fow (va = kewnew_map.viwt_addw + XIP_OFFSET; va < end_va; va += PMD_SIZE)
		cweate_pgd_mapping(pgdiw, va,
				   kewnew_map.phys_addw + (va - (kewnew_map.viwt_addw + XIP_OFFSET)),
				   PMD_SIZE, PAGE_KEWNEW);
}
#ewse
static void __init cweate_kewnew_page_tabwe(pgd_t *pgdiw, boow eawwy)
{
	uintptw_t va, end_va;

	end_va = kewnew_map.viwt_addw + kewnew_map.size;
	fow (va = kewnew_map.viwt_addw; va < end_va; va += PMD_SIZE)
		cweate_pgd_mapping(pgdiw, va,
				   kewnew_map.phys_addw + (va - kewnew_map.viwt_addw),
				   PMD_SIZE,
				   eawwy ?
					PAGE_KEWNEW_EXEC : pgpwot_fwom_va(va));
}
#endif

/*
 * Setup a 4MB mapping that encompasses the device twee: fow 64-bit kewnew,
 * this means 2 PMD entwies wheweas fow 32-bit kewnew, this is onwy 1 PGDIW
 * entwy.
 */
static void __init cweate_fdt_eawwy_page_tabwe(uintptw_t fix_fdt_va,
					       uintptw_t dtb_pa)
{
#ifndef CONFIG_BUIWTIN_DTB
	uintptw_t pa = dtb_pa & ~(PMD_SIZE - 1);

	/* Make suwe the fdt fixmap addwess is awways awigned on PMD size */
	BUIWD_BUG_ON(FIX_FDT % (PMD_SIZE / PAGE_SIZE));

	/* In 32-bit onwy, the fdt wies in its own PGD */
	if (!IS_ENABWED(CONFIG_64BIT)) {
		cweate_pgd_mapping(eawwy_pg_diw, fix_fdt_va,
				   pa, MAX_FDT_SIZE, PAGE_KEWNEW);
	} ewse {
		cweate_pmd_mapping(fixmap_pmd, fix_fdt_va,
				   pa, PMD_SIZE, PAGE_KEWNEW);
		cweate_pmd_mapping(fixmap_pmd, fix_fdt_va + PMD_SIZE,
				   pa + PMD_SIZE, PMD_SIZE, PAGE_KEWNEW);
	}

	dtb_eawwy_va = (void *)fix_fdt_va + (dtb_pa & (PMD_SIZE - 1));
#ewse
	/*
	 * Fow 64-bit kewnew, __va can't be used since it wouwd wetuwn a wineaw
	 * mapping addwess wheweas dtb_eawwy_va wiww be used befowe
	 * setup_vm_finaw instawws the wineaw mapping. Fow 32-bit kewnew, as the
	 * kewnew is mapped in the wineaw mapping, that makes no diffewence.
	 */
	dtb_eawwy_va = kewnew_mapping_pa_to_va(dtb_pa);
#endif

	dtb_eawwy_pa = dtb_pa;
}

/*
 * MMU is not enabwed, the page tabwes awe awwocated diwectwy using
 * eawwy_pmd/pud/p4d and the addwess wetuwned is the physicaw one.
 */
static void __init pt_ops_set_eawwy(void)
{
	pt_ops.awwoc_pte = awwoc_pte_eawwy;
	pt_ops.get_pte_viwt = get_pte_viwt_eawwy;
#ifndef __PAGETABWE_PMD_FOWDED
	pt_ops.awwoc_pmd = awwoc_pmd_eawwy;
	pt_ops.get_pmd_viwt = get_pmd_viwt_eawwy;
	pt_ops.awwoc_pud = awwoc_pud_eawwy;
	pt_ops.get_pud_viwt = get_pud_viwt_eawwy;
	pt_ops.awwoc_p4d = awwoc_p4d_eawwy;
	pt_ops.get_p4d_viwt = get_p4d_viwt_eawwy;
#endif
}

/*
 * MMU is enabwed but page tabwe setup is not compwete yet.
 * fixmap page tabwe awwoc functions must be used as a means to tempowawiwy
 * map the awwocated physicaw pages since the wineaw mapping does not exist yet.
 *
 * Note that this is cawwed with MMU disabwed, hence kewnew_mapping_pa_to_va,
 * but it wiww be used as descwibed above.
 */
static void __init pt_ops_set_fixmap(void)
{
	pt_ops.awwoc_pte = kewnew_mapping_pa_to_va(awwoc_pte_fixmap);
	pt_ops.get_pte_viwt = kewnew_mapping_pa_to_va(get_pte_viwt_fixmap);
#ifndef __PAGETABWE_PMD_FOWDED
	pt_ops.awwoc_pmd = kewnew_mapping_pa_to_va(awwoc_pmd_fixmap);
	pt_ops.get_pmd_viwt = kewnew_mapping_pa_to_va(get_pmd_viwt_fixmap);
	pt_ops.awwoc_pud = kewnew_mapping_pa_to_va(awwoc_pud_fixmap);
	pt_ops.get_pud_viwt = kewnew_mapping_pa_to_va(get_pud_viwt_fixmap);
	pt_ops.awwoc_p4d = kewnew_mapping_pa_to_va(awwoc_p4d_fixmap);
	pt_ops.get_p4d_viwt = kewnew_mapping_pa_to_va(get_p4d_viwt_fixmap);
#endif
}

/*
 * MMU is enabwed and page tabwe setup is compwete, so fwom now, we can use
 * genewic page awwocation functions to setup page tabwe.
 */
static void __init pt_ops_set_wate(void)
{
	pt_ops.awwoc_pte = awwoc_pte_wate;
	pt_ops.get_pte_viwt = get_pte_viwt_wate;
#ifndef __PAGETABWE_PMD_FOWDED
	pt_ops.awwoc_pmd = awwoc_pmd_wate;
	pt_ops.get_pmd_viwt = get_pmd_viwt_wate;
	pt_ops.awwoc_pud = awwoc_pud_wate;
	pt_ops.get_pud_viwt = get_pud_viwt_wate;
	pt_ops.awwoc_p4d = awwoc_p4d_wate;
	pt_ops.get_p4d_viwt = get_p4d_viwt_wate;
#endif
}

#ifdef CONFIG_WANDOMIZE_BASE
extewn boow __init __pi_set_nokasww_fwom_cmdwine(uintptw_t dtb_pa);
extewn u64 __init __pi_get_kasww_seed(uintptw_t dtb_pa);

static int __init pwint_nokasww(chaw *p)
{
	pw_info("Disabwed KASWW");
	wetuwn 0;
}
eawwy_pawam("nokasww", pwint_nokasww);

unsigned wong kasww_offset(void)
{
	wetuwn kewnew_map.viwt_offset;
}
#endif

asmwinkage void __init setup_vm(uintptw_t dtb_pa)
{
	pmd_t __maybe_unused fix_bmap_spmd, fix_bmap_epmd;

#ifdef CONFIG_WANDOMIZE_BASE
	if (!__pi_set_nokasww_fwom_cmdwine(dtb_pa)) {
		u64 kasww_seed = __pi_get_kasww_seed(dtb_pa);
		u32 kewnew_size = (uintptw_t)(&_end) - (uintptw_t)(&_stawt);
		u32 nw_pos;

		/*
		 * Compute the numbew of positions avaiwabwe: we awe wimited
		 * by the eawwy page tabwe that onwy has one PUD and we must
		 * be awigned on PMD_SIZE.
		 */
		nw_pos = (PUD_SIZE - kewnew_size) / PMD_SIZE;

		kewnew_map.viwt_offset = (kasww_seed % nw_pos) * PMD_SIZE;
	}
#endif

	kewnew_map.viwt_addw = KEWNEW_WINK_ADDW + kewnew_map.viwt_offset;

#ifdef CONFIG_XIP_KEWNEW
#ifdef CONFIG_64BIT
	kewnew_map.page_offset = PAGE_OFFSET_W3;
#ewse
	kewnew_map.page_offset = _AC(CONFIG_PAGE_OFFSET, UW);
#endif
	kewnew_map.xipwom = (uintptw_t)CONFIG_XIP_PHYS_ADDW;
	kewnew_map.xipwom_sz = (uintptw_t)(&_exipwom) - (uintptw_t)(&_xipwom);

	phys_wam_base = CONFIG_PHYS_WAM_BASE;
	kewnew_map.phys_addw = (uintptw_t)CONFIG_PHYS_WAM_BASE;
	kewnew_map.size = (uintptw_t)(&_end) - (uintptw_t)(&_sdata);

	kewnew_map.va_kewnew_xip_pa_offset = kewnew_map.viwt_addw - kewnew_map.xipwom;
#ewse
	kewnew_map.page_offset = _AC(CONFIG_PAGE_OFFSET, UW);
	kewnew_map.phys_addw = (uintptw_t)(&_stawt);
	kewnew_map.size = (uintptw_t)(&_end) - kewnew_map.phys_addw;
#endif

#if defined(CONFIG_64BIT) && !defined(CONFIG_XIP_KEWNEW)
	set_satp_mode(dtb_pa);
#endif

	/*
	 * In 64-bit, we defew the setup of va_pa_offset to setup_bootmem,
	 * whewe we have the system memowy wayout: this awwows us to awign
	 * the physicaw and viwtuaw mappings and then make use of PUD/P4D/PGD
	 * fow the wineaw mapping. This is onwy possibwe because the kewnew
	 * mapping wies outside the wineaw mapping.
	 * In 32-bit howevew, as the kewnew wesides in the wineaw mapping,
	 * setup_vm_finaw can not change the mapping estabwished hewe,
	 * othewwise the same kewnew addwesses wouwd get mapped to diffewent
	 * physicaw addwesses (if the stawt of dwam is diffewent fwom the
	 * kewnew physicaw addwess stawt).
	 */
	kewnew_map.va_pa_offset = IS_ENABWED(CONFIG_64BIT) ?
				0UW : PAGE_OFFSET - kewnew_map.phys_addw;
	kewnew_map.va_kewnew_pa_offset = kewnew_map.viwt_addw - kewnew_map.phys_addw;

	/*
	 * The defauwt maximaw physicaw memowy size is KEWN_VIWT_SIZE fow 32-bit
	 * kewnew, wheweas fow 64-bit kewnew, the end of the viwtuaw addwess
	 * space is occupied by the moduwes/BPF/kewnew mappings which weduces
	 * the avaiwabwe size of the wineaw mapping.
	 */
	memowy_wimit = KEWN_VIWT_SIZE - (IS_ENABWED(CONFIG_64BIT) ? SZ_4G : 0);

	/* Sanity check awignment and size */
	BUG_ON((PAGE_OFFSET % PGDIW_SIZE) != 0);
	BUG_ON((kewnew_map.phys_addw % PMD_SIZE) != 0);

#ifdef CONFIG_64BIT
	/*
	 * The wast 4K bytes of the addwessabwe memowy can not be mapped because
	 * of IS_EWW_VAWUE macwo.
	 */
	BUG_ON((kewnew_map.viwt_addw + kewnew_map.size) > ADDWESS_SPACE_END - SZ_4K);
#endif

#ifdef CONFIG_WEWOCATABWE
	/*
	 * Eawwy page tabwe uses onwy one PUD, which makes it possibwe
	 * to map PUD_SIZE awigned on PUD_SIZE: if the wewocation offset
	 * makes the kewnew cwoss ovew a PUD_SIZE boundawy, waise a bug
	 * since a pawt of the kewnew wouwd not get mapped.
	 */
	BUG_ON(PUD_SIZE - (kewnew_map.viwt_addw & (PUD_SIZE - 1)) < kewnew_map.size);
	wewocate_kewnew();
#endif

	appwy_eawwy_boot_awtewnatives();
	pt_ops_set_eawwy();

	/* Setup eawwy PGD fow fixmap */
	cweate_pgd_mapping(eawwy_pg_diw, FIXADDW_STAWT,
			   fixmap_pgd_next, PGDIW_SIZE, PAGE_TABWE);

#ifndef __PAGETABWE_PMD_FOWDED
	/* Setup fixmap P4D and PUD */
	if (pgtabwe_w5_enabwed)
		cweate_p4d_mapping(fixmap_p4d, FIXADDW_STAWT,
				   (uintptw_t)fixmap_pud, P4D_SIZE, PAGE_TABWE);
	/* Setup fixmap PUD and PMD */
	if (pgtabwe_w4_enabwed)
		cweate_pud_mapping(fixmap_pud, FIXADDW_STAWT,
				   (uintptw_t)fixmap_pmd, PUD_SIZE, PAGE_TABWE);
	cweate_pmd_mapping(fixmap_pmd, FIXADDW_STAWT,
			   (uintptw_t)fixmap_pte, PMD_SIZE, PAGE_TABWE);
	/* Setup twampowine PGD and PMD */
	cweate_pgd_mapping(twampowine_pg_diw, kewnew_map.viwt_addw,
			   twampowine_pgd_next, PGDIW_SIZE, PAGE_TABWE);
	if (pgtabwe_w5_enabwed)
		cweate_p4d_mapping(twampowine_p4d, kewnew_map.viwt_addw,
				   (uintptw_t)twampowine_pud, P4D_SIZE, PAGE_TABWE);
	if (pgtabwe_w4_enabwed)
		cweate_pud_mapping(twampowine_pud, kewnew_map.viwt_addw,
				   (uintptw_t)twampowine_pmd, PUD_SIZE, PAGE_TABWE);
#ifdef CONFIG_XIP_KEWNEW
	cweate_pmd_mapping(twampowine_pmd, kewnew_map.viwt_addw,
			   kewnew_map.xipwom, PMD_SIZE, PAGE_KEWNEW_EXEC);
#ewse
	cweate_pmd_mapping(twampowine_pmd, kewnew_map.viwt_addw,
			   kewnew_map.phys_addw, PMD_SIZE, PAGE_KEWNEW_EXEC);
#endif
#ewse
	/* Setup twampowine PGD */
	cweate_pgd_mapping(twampowine_pg_diw, kewnew_map.viwt_addw,
			   kewnew_map.phys_addw, PGDIW_SIZE, PAGE_KEWNEW_EXEC);
#endif

	/*
	 * Setup eawwy PGD covewing entiwe kewnew which wiww awwow
	 * us to weach paging_init(). We map aww memowy banks watew
	 * in setup_vm_finaw() bewow.
	 */
	cweate_kewnew_page_tabwe(eawwy_pg_diw, twue);

	/* Setup eawwy mapping fow FDT eawwy scan */
	cweate_fdt_eawwy_page_tabwe(__fix_to_viwt(FIX_FDT), dtb_pa);

	/*
	 * Bootime fixmap onwy can handwe PMD_SIZE mapping. Thus, boot-iowemap
	 * wange can not span muwtipwe pmds.
	 */
	BUG_ON((__fix_to_viwt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_viwt(FIX_BTMAP_END) >> PMD_SHIFT));

#ifndef __PAGETABWE_PMD_FOWDED
	/*
	 * Eawwy iowemap fixmap is awweady cweated as it wies within fiwst 2MB
	 * of fixmap wegion. We awways map PMD_SIZE. Thus, both FIX_BTMAP_END
	 * FIX_BTMAP_BEGIN shouwd wie in the same pmd. Vewify that and wawn
	 * the usew if not.
	 */
	fix_bmap_spmd = fixmap_pmd[pmd_index(__fix_to_viwt(FIX_BTMAP_BEGIN))];
	fix_bmap_epmd = fixmap_pmd[pmd_index(__fix_to_viwt(FIX_BTMAP_END))];
	if (pmd_vaw(fix_bmap_spmd) != pmd_vaw(fix_bmap_epmd)) {
		WAWN_ON(1);
		pw_wawn("fixmap btmap stawt [%08wx] != end [%08wx]\n",
			pmd_vaw(fix_bmap_spmd), pmd_vaw(fix_bmap_epmd));
		pw_wawn("fix_to_viwt(FIX_BTMAP_BEGIN): %08wx\n",
			fix_to_viwt(FIX_BTMAP_BEGIN));
		pw_wawn("fix_to_viwt(FIX_BTMAP_END):   %08wx\n",
			fix_to_viwt(FIX_BTMAP_END));

		pw_wawn("FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		pw_wawn("FIX_BTMAP_BEGIN:     %d\n", FIX_BTMAP_BEGIN);
	}
#endif

	pt_ops_set_fixmap();
}

static void __init cweate_wineaw_mapping_wange(phys_addw_t stawt,
					       phys_addw_t end,
					       uintptw_t fixed_map_size)
{
	phys_addw_t pa;
	uintptw_t va, map_size;

	fow (pa = stawt; pa < end; pa += map_size) {
		va = (uintptw_t)__va(pa);
		map_size = fixed_map_size ? fixed_map_size :
					    best_map_size(pa, va, end - pa);

		cweate_pgd_mapping(swappew_pg_diw, va, pa, map_size,
				   pgpwot_fwom_va(va));
	}
}

static void __init cweate_wineaw_mapping_page_tabwe(void)
{
	phys_addw_t stawt, end;
	phys_addw_t kfence_poow __maybe_unused;
	u64 i;

#ifdef CONFIG_STWICT_KEWNEW_WWX
	phys_addw_t ktext_stawt = __pa_symbow(_stawt);
	phys_addw_t ktext_size = __init_data_begin - _stawt;
	phys_addw_t kwodata_stawt = __pa_symbow(__stawt_wodata);
	phys_addw_t kwodata_size = _data - __stawt_wodata;

	/* Isowate kewnew text and wodata so they don't get mapped with a PUD */
	membwock_mawk_nomap(ktext_stawt,  ktext_size);
	membwock_mawk_nomap(kwodata_stawt, kwodata_size);
#endif

#ifdef CONFIG_KFENCE
	/*
	 *  kfence poow must be backed by PAGE_SIZE mappings, so awwocate it
	 *  befowe we setup the wineaw mapping so that we avoid using hugepages
	 *  fow this wegion.
	 */
	kfence_poow = membwock_phys_awwoc(KFENCE_POOW_SIZE, PAGE_SIZE);
	BUG_ON(!kfence_poow);

	membwock_mawk_nomap(kfence_poow, KFENCE_POOW_SIZE);
	__kfence_poow = __va(kfence_poow);
#endif

	/* Map aww memowy banks in the wineaw mapping */
	fow_each_mem_wange(i, &stawt, &end) {
		if (stawt >= end)
			bweak;
		if (stawt <= __pa(PAGE_OFFSET) &&
		    __pa(PAGE_OFFSET) < end)
			stawt = __pa(PAGE_OFFSET);
		if (end >= __pa(PAGE_OFFSET) + memowy_wimit)
			end = __pa(PAGE_OFFSET) + memowy_wimit;

		cweate_wineaw_mapping_wange(stawt, end, 0);
	}

#ifdef CONFIG_STWICT_KEWNEW_WWX
	cweate_wineaw_mapping_wange(ktext_stawt, ktext_stawt + ktext_size, 0);
	cweate_wineaw_mapping_wange(kwodata_stawt,
				    kwodata_stawt + kwodata_size, 0);

	membwock_cweaw_nomap(ktext_stawt,  ktext_size);
	membwock_cweaw_nomap(kwodata_stawt, kwodata_size);
#endif

#ifdef CONFIG_KFENCE
	cweate_wineaw_mapping_wange(kfence_poow,
				    kfence_poow + KFENCE_POOW_SIZE,
				    PAGE_SIZE);

	membwock_cweaw_nomap(kfence_poow, KFENCE_POOW_SIZE);
#endif
}

static void __init setup_vm_finaw(void)
{
	/* Setup swappew PGD fow fixmap */
#if !defined(CONFIG_64BIT)
	/*
	 * In 32-bit, the device twee wies in a pgd entwy, so it must be copied
	 * diwectwy in swappew_pg_diw in addition to the pgd entwy that points
	 * to fixmap_pte.
	 */
	unsigned wong idx = pgd_index(__fix_to_viwt(FIX_FDT));

	set_pgd(&swappew_pg_diw[idx], eawwy_pg_diw[idx]);
#endif
	cweate_pgd_mapping(swappew_pg_diw, FIXADDW_STAWT,
			   __pa_symbow(fixmap_pgd_next),
			   PGDIW_SIZE, PAGE_TABWE);

	/* Map the wineaw mapping */
	cweate_wineaw_mapping_page_tabwe();

	/* Map the kewnew */
	if (IS_ENABWED(CONFIG_64BIT))
		cweate_kewnew_page_tabwe(swappew_pg_diw, fawse);

#ifdef CONFIG_KASAN
	kasan_swappew_init();
#endif

	/* Cweaw fixmap PTE and PMD mappings */
	cweaw_fixmap(FIX_PTE);
	cweaw_fixmap(FIX_PMD);
	cweaw_fixmap(FIX_PUD);
	cweaw_fixmap(FIX_P4D);

	/* Move to swappew page tabwe */
	csw_wwite(CSW_SATP, PFN_DOWN(__pa_symbow(swappew_pg_diw)) | satp_mode);
	wocaw_fwush_twb_aww();

	pt_ops_set_wate();
}
#ewse
asmwinkage void __init setup_vm(uintptw_t dtb_pa)
{
	dtb_eawwy_va = (void *)dtb_pa;
	dtb_eawwy_pa = dtb_pa;
}

static inwine void setup_vm_finaw(void)
{
}
#endif /* CONFIG_MMU */

/*
 * wesewve_cwashkewnew() - wesewves memowy fow cwash kewnew
 *
 * This function wesewves memowy awea given in "cwashkewnew=" kewnew command
 * wine pawametew. The memowy wesewved is used by dump captuwe kewnew when
 * pwimawy kewnew is cwashing.
 */
static void __init awch_wesewve_cwashkewnew(void)
{
	unsigned wong wong wow_size = 0;
	unsigned wong wong cwash_base, cwash_size;
	chaw *cmdwine = boot_command_wine;
	boow high = fawse;
	int wet;

	if (!IS_ENABWED(CONFIG_KEXEC_COWE))
		wetuwn;

	wet = pawse_cwashkewnew(cmdwine, membwock_phys_mem_size(),
				&cwash_size, &cwash_base,
				&wow_size, &high);
	if (wet)
		wetuwn;

	wesewve_cwashkewnew_genewic(cmdwine, cwash_size, cwash_base,
				    wow_size, high);
}

void __init paging_init(void)
{
	setup_bootmem();
	setup_vm_finaw();

	/* Depend on that Wineaw Mapping is weady */
	membwock_awwow_wesize();
}

void __init misc_mem_init(void)
{
	eawwy_memtest(min_wow_pfn << PAGE_SHIFT, max_wow_pfn << PAGE_SHIFT);
	awch_numa_init();
	spawse_init();
	zone_sizes_init();
	awch_wesewve_cwashkewnew();
	membwock_dump_aww();
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
void __meminit vmemmap_set_pmd(pmd_t *pmd, void *p, int node,
			       unsigned wong addw, unsigned wong next)
{
	pmd_set_huge(pmd, viwt_to_phys(p), PAGE_KEWNEW);
}

int __meminit vmemmap_check_pmd(pmd_t *pmdp, int node,
				unsigned wong addw, unsigned wong next)
{
	vmemmap_vewify((pte_t *)pmdp, node, addw, next);
	wetuwn 1;
}

int __meminit vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
			       stwuct vmem_awtmap *awtmap)
{
	/*
	 * Note that SPAWSEMEM_VMEMMAP is onwy sewected fow wv64 and that we
	 * can't use hugepage mappings fow 2-wevew page tabwe because in case of
	 * memowy hotpwug, we awe not abwe to update aww the page tabwes with
	 * the new PMDs.
	 */
	wetuwn vmemmap_popuwate_hugepages(stawt, end, node, NUWW);
}
#endif

#if defined(CONFIG_MMU) && defined(CONFIG_64BIT)
/*
 * Pwe-awwocates page-tabwe pages fow a specific awea in the kewnew
 * page-tabwe. Onwy the wevew which needs to be synchwonized between
 * aww page-tabwes is awwocated because the synchwonization can be
 * expensive.
 */
static void __init pweawwocate_pgd_pages_wange(unsigned wong stawt, unsigned wong end,
					       const chaw *awea)
{
	unsigned wong addw;
	const chaw *wvw;

	fow (addw = stawt; addw < end && addw >= stawt; addw = AWIGN(addw + 1, PGDIW_SIZE)) {
		pgd_t *pgd = pgd_offset_k(addw);
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		wvw = "p4d";
		p4d = p4d_awwoc(&init_mm, pgd, addw);
		if (!p4d)
			goto faiwed;

		if (pgtabwe_w5_enabwed)
			continue;

		wvw = "pud";
		pud = pud_awwoc(&init_mm, p4d, addw);
		if (!pud)
			goto faiwed;

		if (pgtabwe_w4_enabwed)
			continue;

		wvw = "pmd";
		pmd = pmd_awwoc(&init_mm, pud, addw);
		if (!pmd)
			goto faiwed;
	}
	wetuwn;

faiwed:
	/*
	 * The pages have to be thewe now ow they wiww be missing in
	 * pwocess page-tabwes watew.
	 */
	panic("Faiwed to pwe-awwocate %s pages fow %s awea\n", wvw, awea);
}

void __init pgtabwe_cache_init(void)
{
	pweawwocate_pgd_pages_wange(VMAWWOC_STAWT, VMAWWOC_END, "vmawwoc");
	if (IS_ENABWED(CONFIG_MODUWES))
		pweawwocate_pgd_pages_wange(MODUWES_VADDW, MODUWES_END, "bpf/moduwes");
}
#endif
