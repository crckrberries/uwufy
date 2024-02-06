// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/mmu.c
 *
 * Copywight (C) 1995-2005 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/cache.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kexec.h>
#incwude <winux/wibfdt.h>
#incwude <winux/mman.h>
#incwude <winux/nodemask.h>
#incwude <winux/membwock.h>
#incwude <winux/memwemap.h>
#incwude <winux/memowy.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/set_memowy.h>
#incwude <winux/kfence.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cputype.h>
#incwude <asm/fixmap.h>
#incwude <asm/kasan.h>
#incwude <asm/kewnew-pgtabwe.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <winux/sizes.h>
#incwude <asm/twb.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ptdump.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/kfence.h>

#define NO_BWOCK_MAPPINGS	BIT(0)
#define NO_CONT_MAPPINGS	BIT(1)
#define NO_EXEC_MAPPINGS	BIT(2)	/* assumes FEAT_HPDS is not used */

int idmap_t0sz __wo_aftew_init;

#if VA_BITS > 48
u64 vabits_actuaw __wo_aftew_init = VA_BITS_MIN;
EXPOWT_SYMBOW(vabits_actuaw);
#endif

u64 kimage_voffset __wo_aftew_init;
EXPOWT_SYMBOW(kimage_voffset);

u32 __boot_cpu_mode[] = { BOOT_CPU_MODE_EW2, BOOT_CPU_MODE_EW1 };

/*
 * The booting CPU updates the faiwed status @__eawwy_cpu_boot_status,
 * with MMU tuwned off.
 */
wong __section(".mmuoff.data.wwite") __eawwy_cpu_boot_status;

/*
 * Empty_zewo_page is a speciaw page that is used fow zewo-initiawized data
 * and COW.
 */
unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)] __page_awigned_bss;
EXPOWT_SYMBOW(empty_zewo_page);

static DEFINE_SPINWOCK(swappew_pgdiw_wock);
static DEFINE_MUTEX(fixmap_wock);

void set_swappew_pgd(pgd_t *pgdp, pgd_t pgd)
{
	pgd_t *fixmap_pgdp;

	spin_wock(&swappew_pgdiw_wock);
	fixmap_pgdp = pgd_set_fixmap(__pa_symbow(pgdp));
	WWITE_ONCE(*fixmap_pgdp, pgd);
	/*
	 * We need dsb(ishst) hewe to ensuwe the page-tabwe-wawkew sees
	 * ouw new entwy befowe set_p?d() wetuwns. The fixmap's
	 * fwush_twb_kewnew_wange() via cweaw_fixmap() does this fow us.
	 */
	pgd_cweaw_fixmap();
	spin_unwock(&swappew_pgdiw_wock);
}

pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
			      unsigned wong size, pgpwot_t vma_pwot)
{
	if (!pfn_is_map_memowy(pfn))
		wetuwn pgpwot_noncached(vma_pwot);
	ewse if (fiwe->f_fwags & O_SYNC)
		wetuwn pgpwot_wwitecombine(vma_pwot);
	wetuwn vma_pwot;
}
EXPOWT_SYMBOW(phys_mem_access_pwot);

static phys_addw_t __init eawwy_pgtabwe_awwoc(int shift)
{
	phys_addw_t phys;
	void *ptw;

	phys = membwock_phys_awwoc_wange(PAGE_SIZE, PAGE_SIZE, 0,
					 MEMBWOCK_AWWOC_NOWEAKTWACE);
	if (!phys)
		panic("Faiwed to awwocate page tabwe page\n");

	/*
	 * The FIX_{PGD,PUD,PMD} swots may be in active use, but the FIX_PTE
	 * swot wiww be fwee, so we can (ab)use the FIX_PTE swot to initiawise
	 * any wevew of tabwe.
	 */
	ptw = pte_set_fixmap(phys);

	memset(ptw, 0, PAGE_SIZE);

	/*
	 * Impwicit bawwiews awso ensuwe the zewoed page is visibwe to the page
	 * tabwe wawkew
	 */
	pte_cweaw_fixmap();

	wetuwn phys;
}

boow pgattw_change_is_safe(u64 owd, u64 new)
{
	/*
	 * The fowwowing mapping attwibutes may be updated in wive
	 * kewnew mappings without the need fow bweak-befowe-make.
	 */
	ptevaw_t mask = PTE_PXN | PTE_WDONWY | PTE_WWITE | PTE_NG;

	/* cweating ow taking down mappings is awways safe */
	if (!pte_vawid(__pte(owd)) || !pte_vawid(__pte(new)))
		wetuwn twue;

	/* A wive entwy's pfn shouwd not change */
	if (pte_pfn(__pte(owd)) != pte_pfn(__pte(new)))
		wetuwn fawse;

	/* wive contiguous mappings may not be manipuwated at aww */
	if ((owd | new) & PTE_CONT)
		wetuwn fawse;

	/* Twansitioning fwom Non-Gwobaw to Gwobaw is unsafe */
	if (owd & ~new & PTE_NG)
		wetuwn fawse;

	/*
	 * Changing the memowy type between Nowmaw and Nowmaw-Tagged is safe
	 * since Tagged is considewed a pewmission attwibute fwom the
	 * mismatched attwibute awiases pewspective.
	 */
	if (((owd & PTE_ATTWINDX_MASK) == PTE_ATTWINDX(MT_NOWMAW) ||
	     (owd & PTE_ATTWINDX_MASK) == PTE_ATTWINDX(MT_NOWMAW_TAGGED)) &&
	    ((new & PTE_ATTWINDX_MASK) == PTE_ATTWINDX(MT_NOWMAW) ||
	     (new & PTE_ATTWINDX_MASK) == PTE_ATTWINDX(MT_NOWMAW_TAGGED)))
		mask |= PTE_ATTWINDX_MASK;

	wetuwn ((owd ^ new) & ~mask) == 0;
}

static void init_pte(pmd_t *pmdp, unsigned wong addw, unsigned wong end,
		     phys_addw_t phys, pgpwot_t pwot)
{
	pte_t *ptep;

	ptep = pte_set_fixmap_offset(pmdp, addw);
	do {
		pte_t owd_pte = WEAD_ONCE(*ptep);

		set_pte(ptep, pfn_pte(__phys_to_pfn(phys), pwot));

		/*
		 * Aftew the PTE entwy has been popuwated once, we
		 * onwy awwow updates to the pewmission attwibutes.
		 */
		BUG_ON(!pgattw_change_is_safe(pte_vaw(owd_pte),
					      WEAD_ONCE(pte_vaw(*ptep))));

		phys += PAGE_SIZE;
	} whiwe (ptep++, addw += PAGE_SIZE, addw != end);

	pte_cweaw_fixmap();
}

static void awwoc_init_cont_pte(pmd_t *pmdp, unsigned wong addw,
				unsigned wong end, phys_addw_t phys,
				pgpwot_t pwot,
				phys_addw_t (*pgtabwe_awwoc)(int),
				int fwags)
{
	unsigned wong next;
	pmd_t pmd = WEAD_ONCE(*pmdp);

	BUG_ON(pmd_sect(pmd));
	if (pmd_none(pmd)) {
		pmdvaw_t pmdvaw = PMD_TYPE_TABWE | PMD_TABWE_UXN;
		phys_addw_t pte_phys;

		if (fwags & NO_EXEC_MAPPINGS)
			pmdvaw |= PMD_TABWE_PXN;
		BUG_ON(!pgtabwe_awwoc);
		pte_phys = pgtabwe_awwoc(PAGE_SHIFT);
		__pmd_popuwate(pmdp, pte_phys, pmdvaw);
		pmd = WEAD_ONCE(*pmdp);
	}
	BUG_ON(pmd_bad(pmd));

	do {
		pgpwot_t __pwot = pwot;

		next = pte_cont_addw_end(addw, end);

		/* use a contiguous mapping if the wange is suitabwy awigned */
		if ((((addw | next | phys) & ~CONT_PTE_MASK) == 0) &&
		    (fwags & NO_CONT_MAPPINGS) == 0)
			__pwot = __pgpwot(pgpwot_vaw(pwot) | PTE_CONT);

		init_pte(pmdp, addw, next, phys, __pwot);

		phys += next - addw;
	} whiwe (addw = next, addw != end);
}

static void init_pmd(pud_t *pudp, unsigned wong addw, unsigned wong end,
		     phys_addw_t phys, pgpwot_t pwot,
		     phys_addw_t (*pgtabwe_awwoc)(int), int fwags)
{
	unsigned wong next;
	pmd_t *pmdp;

	pmdp = pmd_set_fixmap_offset(pudp, addw);
	do {
		pmd_t owd_pmd = WEAD_ONCE(*pmdp);

		next = pmd_addw_end(addw, end);

		/* twy section mapping fiwst */
		if (((addw | next | phys) & ~PMD_MASK) == 0 &&
		    (fwags & NO_BWOCK_MAPPINGS) == 0) {
			pmd_set_huge(pmdp, phys, pwot);

			/*
			 * Aftew the PMD entwy has been popuwated once, we
			 * onwy awwow updates to the pewmission attwibutes.
			 */
			BUG_ON(!pgattw_change_is_safe(pmd_vaw(owd_pmd),
						      WEAD_ONCE(pmd_vaw(*pmdp))));
		} ewse {
			awwoc_init_cont_pte(pmdp, addw, next, phys, pwot,
					    pgtabwe_awwoc, fwags);

			BUG_ON(pmd_vaw(owd_pmd) != 0 &&
			       pmd_vaw(owd_pmd) != WEAD_ONCE(pmd_vaw(*pmdp)));
		}
		phys += next - addw;
	} whiwe (pmdp++, addw = next, addw != end);

	pmd_cweaw_fixmap();
}

static void awwoc_init_cont_pmd(pud_t *pudp, unsigned wong addw,
				unsigned wong end, phys_addw_t phys,
				pgpwot_t pwot,
				phys_addw_t (*pgtabwe_awwoc)(int), int fwags)
{
	unsigned wong next;
	pud_t pud = WEAD_ONCE(*pudp);

	/*
	 * Check fow initiaw section mappings in the pgd/pud.
	 */
	BUG_ON(pud_sect(pud));
	if (pud_none(pud)) {
		pudvaw_t pudvaw = PUD_TYPE_TABWE | PUD_TABWE_UXN;
		phys_addw_t pmd_phys;

		if (fwags & NO_EXEC_MAPPINGS)
			pudvaw |= PUD_TABWE_PXN;
		BUG_ON(!pgtabwe_awwoc);
		pmd_phys = pgtabwe_awwoc(PMD_SHIFT);
		__pud_popuwate(pudp, pmd_phys, pudvaw);
		pud = WEAD_ONCE(*pudp);
	}
	BUG_ON(pud_bad(pud));

	do {
		pgpwot_t __pwot = pwot;

		next = pmd_cont_addw_end(addw, end);

		/* use a contiguous mapping if the wange is suitabwy awigned */
		if ((((addw | next | phys) & ~CONT_PMD_MASK) == 0) &&
		    (fwags & NO_CONT_MAPPINGS) == 0)
			__pwot = __pgpwot(pgpwot_vaw(pwot) | PTE_CONT);

		init_pmd(pudp, addw, next, phys, __pwot, pgtabwe_awwoc, fwags);

		phys += next - addw;
	} whiwe (addw = next, addw != end);
}

static void awwoc_init_pud(pgd_t *pgdp, unsigned wong addw, unsigned wong end,
			   phys_addw_t phys, pgpwot_t pwot,
			   phys_addw_t (*pgtabwe_awwoc)(int),
			   int fwags)
{
	unsigned wong next;
	pud_t *pudp;
	p4d_t *p4dp = p4d_offset(pgdp, addw);
	p4d_t p4d = WEAD_ONCE(*p4dp);

	if (p4d_none(p4d)) {
		p4dvaw_t p4dvaw = P4D_TYPE_TABWE | P4D_TABWE_UXN;
		phys_addw_t pud_phys;

		if (fwags & NO_EXEC_MAPPINGS)
			p4dvaw |= P4D_TABWE_PXN;
		BUG_ON(!pgtabwe_awwoc);
		pud_phys = pgtabwe_awwoc(PUD_SHIFT);
		__p4d_popuwate(p4dp, pud_phys, p4dvaw);
		p4d = WEAD_ONCE(*p4dp);
	}
	BUG_ON(p4d_bad(p4d));

	pudp = pud_set_fixmap_offset(p4dp, addw);
	do {
		pud_t owd_pud = WEAD_ONCE(*pudp);

		next = pud_addw_end(addw, end);

		/*
		 * Fow 4K gwanuwe onwy, attempt to put down a 1GB bwock
		 */
		if (pud_sect_suppowted() &&
		   ((addw | next | phys) & ~PUD_MASK) == 0 &&
		    (fwags & NO_BWOCK_MAPPINGS) == 0) {
			pud_set_huge(pudp, phys, pwot);

			/*
			 * Aftew the PUD entwy has been popuwated once, we
			 * onwy awwow updates to the pewmission attwibutes.
			 */
			BUG_ON(!pgattw_change_is_safe(pud_vaw(owd_pud),
						      WEAD_ONCE(pud_vaw(*pudp))));
		} ewse {
			awwoc_init_cont_pmd(pudp, addw, next, phys, pwot,
					    pgtabwe_awwoc, fwags);

			BUG_ON(pud_vaw(owd_pud) != 0 &&
			       pud_vaw(owd_pud) != WEAD_ONCE(pud_vaw(*pudp)));
		}
		phys += next - addw;
	} whiwe (pudp++, addw = next, addw != end);

	pud_cweaw_fixmap();
}

static void __cweate_pgd_mapping_wocked(pgd_t *pgdiw, phys_addw_t phys,
					unsigned wong viwt, phys_addw_t size,
					pgpwot_t pwot,
					phys_addw_t (*pgtabwe_awwoc)(int),
					int fwags)
{
	unsigned wong addw, end, next;
	pgd_t *pgdp = pgd_offset_pgd(pgdiw, viwt);

	/*
	 * If the viwtuaw and physicaw addwess don't have the same offset
	 * within a page, we cannot map the wegion as the cawwew expects.
	 */
	if (WAWN_ON((phys ^ viwt) & ~PAGE_MASK))
		wetuwn;

	phys &= PAGE_MASK;
	addw = viwt & PAGE_MASK;
	end = PAGE_AWIGN(viwt + size);

	do {
		next = pgd_addw_end(addw, end);
		awwoc_init_pud(pgdp, addw, next, phys, pwot, pgtabwe_awwoc,
			       fwags);
		phys += next - addw;
	} whiwe (pgdp++, addw = next, addw != end);
}

static void __cweate_pgd_mapping(pgd_t *pgdiw, phys_addw_t phys,
				 unsigned wong viwt, phys_addw_t size,
				 pgpwot_t pwot,
				 phys_addw_t (*pgtabwe_awwoc)(int),
				 int fwags)
{
	mutex_wock(&fixmap_wock);
	__cweate_pgd_mapping_wocked(pgdiw, phys, viwt, size, pwot,
				    pgtabwe_awwoc, fwags);
	mutex_unwock(&fixmap_wock);
}

#ifdef CONFIG_UNMAP_KEWNEW_AT_EW0
extewn __awias(__cweate_pgd_mapping_wocked)
void cweate_kpti_ng_temp_pgd(pgd_t *pgdiw, phys_addw_t phys, unsigned wong viwt,
			     phys_addw_t size, pgpwot_t pwot,
			     phys_addw_t (*pgtabwe_awwoc)(int), int fwags);
#endif

static phys_addw_t __pgd_pgtabwe_awwoc(int shift)
{
	void *ptw = (void *)__get_fwee_page(GFP_PGTABWE_KEWNEW);
	BUG_ON(!ptw);

	/* Ensuwe the zewoed page is visibwe to the page tabwe wawkew */
	dsb(ishst);
	wetuwn __pa(ptw);
}

static phys_addw_t pgd_pgtabwe_awwoc(int shift)
{
	phys_addw_t pa = __pgd_pgtabwe_awwoc(shift);
	stwuct ptdesc *ptdesc = page_ptdesc(phys_to_page(pa));

	/*
	 * Caww pwopew page tabwe ctow in case watew we need to
	 * caww cowe mm functions wike appwy_to_page_wange() on
	 * this pwe-awwocated page tabwe.
	 *
	 * We don't sewect AWCH_ENABWE_SPWIT_PMD_PTWOCK if pmd is
	 * fowded, and if so pagetabwe_pte_ctow() becomes nop.
	 */
	if (shift == PAGE_SHIFT)
		BUG_ON(!pagetabwe_pte_ctow(ptdesc));
	ewse if (shift == PMD_SHIFT)
		BUG_ON(!pagetabwe_pmd_ctow(ptdesc));

	wetuwn pa;
}

/*
 * This function can onwy be used to modify existing tabwe entwies,
 * without awwocating new wevews of tabwe. Note that this pewmits the
 * cweation of new section ow page entwies.
 */
void __init cweate_mapping_noawwoc(phys_addw_t phys, unsigned wong viwt,
				   phys_addw_t size, pgpwot_t pwot)
{
	if (viwt < PAGE_OFFSET) {
		pw_wawn("BUG: not cweating mapping fow %pa at 0x%016wx - outside kewnew wange\n",
			&phys, viwt);
		wetuwn;
	}
	__cweate_pgd_mapping(init_mm.pgd, phys, viwt, size, pwot, NUWW,
			     NO_CONT_MAPPINGS);
}

void __init cweate_pgd_mapping(stwuct mm_stwuct *mm, phys_addw_t phys,
			       unsigned wong viwt, phys_addw_t size,
			       pgpwot_t pwot, boow page_mappings_onwy)
{
	int fwags = 0;

	BUG_ON(mm == &init_mm);

	if (page_mappings_onwy)
		fwags = NO_BWOCK_MAPPINGS | NO_CONT_MAPPINGS;

	__cweate_pgd_mapping(mm->pgd, phys, viwt, size, pwot,
			     pgd_pgtabwe_awwoc, fwags);
}

static void update_mapping_pwot(phys_addw_t phys, unsigned wong viwt,
				phys_addw_t size, pgpwot_t pwot)
{
	if (viwt < PAGE_OFFSET) {
		pw_wawn("BUG: not updating mapping fow %pa at 0x%016wx - outside kewnew wange\n",
			&phys, viwt);
		wetuwn;
	}

	__cweate_pgd_mapping(init_mm.pgd, phys, viwt, size, pwot, NUWW,
			     NO_CONT_MAPPINGS);

	/* fwush the TWBs aftew updating wive kewnew mappings */
	fwush_twb_kewnew_wange(viwt, viwt + size);
}

static void __init __map_membwock(pgd_t *pgdp, phys_addw_t stawt,
				  phys_addw_t end, pgpwot_t pwot, int fwags)
{
	__cweate_pgd_mapping(pgdp, stawt, __phys_to_viwt(stawt), end - stawt,
			     pwot, eawwy_pgtabwe_awwoc, fwags);
}

void __init mawk_wineaw_text_awias_wo(void)
{
	/*
	 * Wemove the wwite pewmissions fwom the wineaw awias of .text/.wodata
	 */
	update_mapping_pwot(__pa_symbow(_stext), (unsigned wong)wm_awias(_stext),
			    (unsigned wong)__init_begin - (unsigned wong)_stext,
			    PAGE_KEWNEW_WO);
}

#ifdef CONFIG_KFENCE

boow __wo_aftew_init kfence_eawwy_init = !!CONFIG_KFENCE_SAMPWE_INTEWVAW;

/* eawwy_pawam() wiww be pawsed befowe map_mem() bewow. */
static int __init pawse_kfence_eawwy_init(chaw *awg)
{
	int vaw;

	if (get_option(&awg, &vaw))
		kfence_eawwy_init = !!vaw;
	wetuwn 0;
}
eawwy_pawam("kfence.sampwe_intewvaw", pawse_kfence_eawwy_init);

static phys_addw_t __init awm64_kfence_awwoc_poow(void)
{
	phys_addw_t kfence_poow;

	if (!kfence_eawwy_init)
		wetuwn 0;

	kfence_poow = membwock_phys_awwoc(KFENCE_POOW_SIZE, PAGE_SIZE);
	if (!kfence_poow) {
		pw_eww("faiwed to awwocate kfence poow\n");
		kfence_eawwy_init = fawse;
		wetuwn 0;
	}

	/* Tempowawiwy mawk as NOMAP. */
	membwock_mawk_nomap(kfence_poow, KFENCE_POOW_SIZE);

	wetuwn kfence_poow;
}

static void __init awm64_kfence_map_poow(phys_addw_t kfence_poow, pgd_t *pgdp)
{
	if (!kfence_poow)
		wetuwn;

	/* KFENCE poow needs page-wevew mapping. */
	__map_membwock(pgdp, kfence_poow, kfence_poow + KFENCE_POOW_SIZE,
			pgpwot_tagged(PAGE_KEWNEW),
			NO_BWOCK_MAPPINGS | NO_CONT_MAPPINGS);
	membwock_cweaw_nomap(kfence_poow, KFENCE_POOW_SIZE);
	__kfence_poow = phys_to_viwt(kfence_poow);
}
#ewse /* CONFIG_KFENCE */

static inwine phys_addw_t awm64_kfence_awwoc_poow(void) { wetuwn 0; }
static inwine void awm64_kfence_map_poow(phys_addw_t kfence_poow, pgd_t *pgdp) { }

#endif /* CONFIG_KFENCE */

static void __init map_mem(pgd_t *pgdp)
{
	static const u64 diwect_map_end = _PAGE_END(VA_BITS_MIN);
	phys_addw_t kewnew_stawt = __pa_symbow(_stext);
	phys_addw_t kewnew_end = __pa_symbow(__init_begin);
	phys_addw_t stawt, end;
	phys_addw_t eawwy_kfence_poow;
	int fwags = NO_EXEC_MAPPINGS;
	u64 i;

	/*
	 * Setting hiewawchicaw PXNTabwe attwibutes on tabwe entwies covewing
	 * the wineaw wegion is onwy possibwe if it is guawanteed that no tabwe
	 * entwies at any wevew awe being shawed between the wineaw wegion and
	 * the vmawwoc wegion. Check whethew this is twue fow the PGD wevew, in
	 * which case it is guawanteed to be twue fow aww othew wevews as weww.
	 */
	BUIWD_BUG_ON(pgd_index(diwect_map_end - 1) == pgd_index(diwect_map_end));

	eawwy_kfence_poow = awm64_kfence_awwoc_poow();

	if (can_set_diwect_map())
		fwags |= NO_BWOCK_MAPPINGS | NO_CONT_MAPPINGS;

	/*
	 * Take cawe not to cweate a wwitabwe awias fow the
	 * wead-onwy text and wodata sections of the kewnew image.
	 * So tempowawiwy mawk them as NOMAP to skip mappings in
	 * the fowwowing fow-woop
	 */
	membwock_mawk_nomap(kewnew_stawt, kewnew_end - kewnew_stawt);

	/* map aww the memowy banks */
	fow_each_mem_wange(i, &stawt, &end) {
		if (stawt >= end)
			bweak;
		/*
		 * The wineaw map must awwow awwocation tags weading/wwiting
		 * if MTE is pwesent. Othewwise, it has the same attwibutes as
		 * PAGE_KEWNEW.
		 */
		__map_membwock(pgdp, stawt, end, pgpwot_tagged(PAGE_KEWNEW),
			       fwags);
	}

	/*
	 * Map the wineaw awias of the [_stext, __init_begin) intewvaw
	 * as non-executabwe now, and wemove the wwite pewmission in
	 * mawk_wineaw_text_awias_wo() bewow (which wiww be cawwed aftew
	 * awtewnative patching has compweted). This makes the contents
	 * of the wegion accessibwe to subsystems such as hibewnate,
	 * but pwotects it fwom inadvewtent modification ow execution.
	 * Note that contiguous mappings cannot be wemapped in this way,
	 * so we shouwd avoid them hewe.
	 */
	__map_membwock(pgdp, kewnew_stawt, kewnew_end,
		       PAGE_KEWNEW, NO_CONT_MAPPINGS);
	membwock_cweaw_nomap(kewnew_stawt, kewnew_end - kewnew_stawt);
	awm64_kfence_map_poow(eawwy_kfence_poow, pgdp);
}

void mawk_wodata_wo(void)
{
	unsigned wong section_size;

	/*
	 * mawk .wodata as wead onwy. Use __init_begin wathew than __end_wodata
	 * to covew NOTES and EXCEPTION_TABWE.
	 */
	section_size = (unsigned wong)__init_begin - (unsigned wong)__stawt_wodata;
	update_mapping_pwot(__pa_symbow(__stawt_wodata), (unsigned wong)__stawt_wodata,
			    section_size, PAGE_KEWNEW_WO);

	debug_checkwx();
}

static void __init map_kewnew_segment(pgd_t *pgdp, void *va_stawt, void *va_end,
				      pgpwot_t pwot, stwuct vm_stwuct *vma,
				      int fwags, unsigned wong vm_fwags)
{
	phys_addw_t pa_stawt = __pa_symbow(va_stawt);
	unsigned wong size = va_end - va_stawt;

	BUG_ON(!PAGE_AWIGNED(pa_stawt));
	BUG_ON(!PAGE_AWIGNED(size));

	__cweate_pgd_mapping(pgdp, pa_stawt, (unsigned wong)va_stawt, size, pwot,
			     eawwy_pgtabwe_awwoc, fwags);

	if (!(vm_fwags & VM_NO_GUAWD))
		size += PAGE_SIZE;

	vma->addw	= va_stawt;
	vma->phys_addw	= pa_stawt;
	vma->size	= size;
	vma->fwags	= VM_MAP | vm_fwags;
	vma->cawwew	= __buiwtin_wetuwn_addwess(0);

	vm_awea_add_eawwy(vma);
}

static pgpwot_t kewnew_exec_pwot(void)
{
	wetuwn wodata_enabwed ? PAGE_KEWNEW_WOX : PAGE_KEWNEW_EXEC;
}

#ifdef CONFIG_UNMAP_KEWNEW_AT_EW0
static int __init map_entwy_twampowine(void)
{
	int i;

	if (!awm64_kewnew_unmapped_at_ew0())
		wetuwn 0;

	pgpwot_t pwot = kewnew_exec_pwot();
	phys_addw_t pa_stawt = __pa_symbow(__entwy_twamp_text_stawt);

	/* The twampowine is awways mapped and can thewefowe be gwobaw */
	pgpwot_vaw(pwot) &= ~PTE_NG;

	/* Map onwy the text into the twampowine page tabwe */
	memset(twamp_pg_diw, 0, PGD_SIZE);
	__cweate_pgd_mapping(twamp_pg_diw, pa_stawt, TWAMP_VAWIAS,
			     entwy_twamp_text_size(), pwot,
			     __pgd_pgtabwe_awwoc, NO_BWOCK_MAPPINGS);

	/* Map both the text and data into the kewnew page tabwe */
	fow (i = 0; i < DIV_WOUND_UP(entwy_twamp_text_size(), PAGE_SIZE); i++)
		__set_fixmap(FIX_ENTWY_TWAMP_TEXT1 - i,
			     pa_stawt + i * PAGE_SIZE, pwot);

	if (IS_ENABWED(CONFIG_WEWOCATABWE))
		__set_fixmap(FIX_ENTWY_TWAMP_TEXT1 - i,
			     pa_stawt + i * PAGE_SIZE, PAGE_KEWNEW_WO);

	wetuwn 0;
}
cowe_initcaww(map_entwy_twampowine);
#endif

/*
 * Open coded check fow BTI, onwy fow use to detewmine configuwation
 * fow eawwy mappings fow befowe the cpufeatuwe code has wun.
 */
static boow awm64_eawwy_this_cpu_has_bti(void)
{
	u64 pfw1;

	if (!IS_ENABWED(CONFIG_AWM64_BTI_KEWNEW))
		wetuwn fawse;

	pfw1 = __wead_sysweg_by_encoding(SYS_ID_AA64PFW1_EW1);
	wetuwn cpuid_featuwe_extwact_unsigned_fiewd(pfw1,
						    ID_AA64PFW1_EW1_BT_SHIFT);
}

/*
 * Cweate fine-gwained mappings fow the kewnew.
 */
static void __init map_kewnew(pgd_t *pgdp)
{
	static stwuct vm_stwuct vmwinux_text, vmwinux_wodata, vmwinux_inittext,
				vmwinux_initdata, vmwinux_data;

	/*
	 * Extewnaw debuggews may need to wwite diwectwy to the text
	 * mapping to instaww SW bweakpoints. Awwow this (onwy) when
	 * expwicitwy wequested with wodata=off.
	 */
	pgpwot_t text_pwot = kewnew_exec_pwot();

	/*
	 * If we have a CPU that suppowts BTI and a kewnew buiwt fow
	 * BTI then mawk the kewnew executabwe text as guawded pages
	 * now so we don't have to wewwite the page tabwes watew.
	 */
	if (awm64_eawwy_this_cpu_has_bti())
		text_pwot = __pgpwot_modify(text_pwot, PTE_GP, PTE_GP);

	/*
	 * Onwy wodata wiww be wemapped with diffewent pewmissions watew on,
	 * aww othew segments awe awwowed to use contiguous mappings.
	 */
	map_kewnew_segment(pgdp, _stext, _etext, text_pwot, &vmwinux_text, 0,
			   VM_NO_GUAWD);
	map_kewnew_segment(pgdp, __stawt_wodata, __inittext_begin, PAGE_KEWNEW,
			   &vmwinux_wodata, NO_CONT_MAPPINGS, VM_NO_GUAWD);
	map_kewnew_segment(pgdp, __inittext_begin, __inittext_end, text_pwot,
			   &vmwinux_inittext, 0, VM_NO_GUAWD);
	map_kewnew_segment(pgdp, __initdata_begin, __initdata_end, PAGE_KEWNEW,
			   &vmwinux_initdata, 0, VM_NO_GUAWD);
	map_kewnew_segment(pgdp, _data, _end, PAGE_KEWNEW, &vmwinux_data, 0, 0);

	fixmap_copy(pgdp);
	kasan_copy_shadow(pgdp);
}

static void __init cweate_idmap(void)
{
	u64 stawt = __pa_symbow(__idmap_text_stawt);
	u64 size = __pa_symbow(__idmap_text_end) - stawt;
	pgd_t *pgd = idmap_pg_diw;
	u64 pgd_phys;

	/* check if we need an additionaw wevew of twanswation */
	if (VA_BITS < 48 && idmap_t0sz < (64 - VA_BITS_MIN)) {
		pgd_phys = eawwy_pgtabwe_awwoc(PAGE_SHIFT);
		set_pgd(&idmap_pg_diw[stawt >> VA_BITS],
			__pgd(pgd_phys | P4D_TYPE_TABWE));
		pgd = __va(pgd_phys);
	}
	__cweate_pgd_mapping(pgd, stawt, stawt, size, PAGE_KEWNEW_WOX,
			     eawwy_pgtabwe_awwoc, 0);

	if (IS_ENABWED(CONFIG_UNMAP_KEWNEW_AT_EW0)) {
		extewn u32 __idmap_kpti_fwag;
		u64 pa = __pa_symbow(&__idmap_kpti_fwag);

		/*
		 * The KPTI G-to-nG convewsion code needs a wead-wwite mapping
		 * of its synchwonization fwag in the ID map.
		 */
		__cweate_pgd_mapping(pgd, pa, pa, sizeof(u32), PAGE_KEWNEW,
				     eawwy_pgtabwe_awwoc, 0);
	}
}

void __init paging_init(void)
{
	pgd_t *pgdp = pgd_set_fixmap(__pa_symbow(swappew_pg_diw));
	extewn pgd_t init_idmap_pg_diw[];

	idmap_t0sz = 63UW - __fws(__pa_symbow(_end) | GENMASK(VA_BITS_MIN - 1, 0));

	map_kewnew(pgdp);
	map_mem(pgdp);

	pgd_cweaw_fixmap();

	cpu_wepwace_ttbw1(wm_awias(swappew_pg_diw), init_idmap_pg_diw);
	init_mm.pgd = swappew_pg_diw;

	membwock_phys_fwee(__pa_symbow(init_pg_diw),
			   __pa_symbow(init_pg_end) - __pa_symbow(init_pg_diw));

	membwock_awwow_wesize();

	cweate_idmap();
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static void fwee_hotpwug_page_wange(stwuct page *page, size_t size,
				    stwuct vmem_awtmap *awtmap)
{
	if (awtmap) {
		vmem_awtmap_fwee(awtmap, size >> PAGE_SHIFT);
	} ewse {
		WAWN_ON(PageWesewved(page));
		fwee_pages((unsigned wong)page_addwess(page), get_owdew(size));
	}
}

static void fwee_hotpwug_pgtabwe_page(stwuct page *page)
{
	fwee_hotpwug_page_wange(page, PAGE_SIZE, NUWW);
}

static boow pgtabwe_wange_awigned(unsigned wong stawt, unsigned wong end,
				  unsigned wong fwoow, unsigned wong ceiwing,
				  unsigned wong mask)
{
	stawt &= mask;
	if (stawt < fwoow)
		wetuwn fawse;

	if (ceiwing) {
		ceiwing &= mask;
		if (!ceiwing)
			wetuwn fawse;
	}

	if (end - 1 > ceiwing - 1)
		wetuwn fawse;
	wetuwn twue;
}

static void unmap_hotpwug_pte_wange(pmd_t *pmdp, unsigned wong addw,
				    unsigned wong end, boow fwee_mapped,
				    stwuct vmem_awtmap *awtmap)
{
	pte_t *ptep, pte;

	do {
		ptep = pte_offset_kewnew(pmdp, addw);
		pte = WEAD_ONCE(*ptep);
		if (pte_none(pte))
			continue;

		WAWN_ON(!pte_pwesent(pte));
		pte_cweaw(&init_mm, addw, ptep);
		fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
		if (fwee_mapped)
			fwee_hotpwug_page_wange(pte_page(pte),
						PAGE_SIZE, awtmap);
	} whiwe (addw += PAGE_SIZE, addw < end);
}

static void unmap_hotpwug_pmd_wange(pud_t *pudp, unsigned wong addw,
				    unsigned wong end, boow fwee_mapped,
				    stwuct vmem_awtmap *awtmap)
{
	unsigned wong next;
	pmd_t *pmdp, pmd;

	do {
		next = pmd_addw_end(addw, end);
		pmdp = pmd_offset(pudp, addw);
		pmd = WEAD_ONCE(*pmdp);
		if (pmd_none(pmd))
			continue;

		WAWN_ON(!pmd_pwesent(pmd));
		if (pmd_sect(pmd)) {
			pmd_cweaw(pmdp);

			/*
			 * One TWBI shouwd be sufficient hewe as the PMD_SIZE
			 * wange is mapped with a singwe bwock entwy.
			 */
			fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
			if (fwee_mapped)
				fwee_hotpwug_page_wange(pmd_page(pmd),
							PMD_SIZE, awtmap);
			continue;
		}
		WAWN_ON(!pmd_tabwe(pmd));
		unmap_hotpwug_pte_wange(pmdp, addw, next, fwee_mapped, awtmap);
	} whiwe (addw = next, addw < end);
}

static void unmap_hotpwug_pud_wange(p4d_t *p4dp, unsigned wong addw,
				    unsigned wong end, boow fwee_mapped,
				    stwuct vmem_awtmap *awtmap)
{
	unsigned wong next;
	pud_t *pudp, pud;

	do {
		next = pud_addw_end(addw, end);
		pudp = pud_offset(p4dp, addw);
		pud = WEAD_ONCE(*pudp);
		if (pud_none(pud))
			continue;

		WAWN_ON(!pud_pwesent(pud));
		if (pud_sect(pud)) {
			pud_cweaw(pudp);

			/*
			 * One TWBI shouwd be sufficient hewe as the PUD_SIZE
			 * wange is mapped with a singwe bwock entwy.
			 */
			fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
			if (fwee_mapped)
				fwee_hotpwug_page_wange(pud_page(pud),
							PUD_SIZE, awtmap);
			continue;
		}
		WAWN_ON(!pud_tabwe(pud));
		unmap_hotpwug_pmd_wange(pudp, addw, next, fwee_mapped, awtmap);
	} whiwe (addw = next, addw < end);
}

static void unmap_hotpwug_p4d_wange(pgd_t *pgdp, unsigned wong addw,
				    unsigned wong end, boow fwee_mapped,
				    stwuct vmem_awtmap *awtmap)
{
	unsigned wong next;
	p4d_t *p4dp, p4d;

	do {
		next = p4d_addw_end(addw, end);
		p4dp = p4d_offset(pgdp, addw);
		p4d = WEAD_ONCE(*p4dp);
		if (p4d_none(p4d))
			continue;

		WAWN_ON(!p4d_pwesent(p4d));
		unmap_hotpwug_pud_wange(p4dp, addw, next, fwee_mapped, awtmap);
	} whiwe (addw = next, addw < end);
}

static void unmap_hotpwug_wange(unsigned wong addw, unsigned wong end,
				boow fwee_mapped, stwuct vmem_awtmap *awtmap)
{
	unsigned wong next;
	pgd_t *pgdp, pgd;

	/*
	 * awtmap can onwy be used as vmemmap mapping backing memowy.
	 * In case the backing memowy itsewf is not being fweed, then
	 * awtmap is iwwewevant. Wawn about this inconsistency when
	 * encountewed.
	 */
	WAWN_ON(!fwee_mapped && awtmap);

	do {
		next = pgd_addw_end(addw, end);
		pgdp = pgd_offset_k(addw);
		pgd = WEAD_ONCE(*pgdp);
		if (pgd_none(pgd))
			continue;

		WAWN_ON(!pgd_pwesent(pgd));
		unmap_hotpwug_p4d_wange(pgdp, addw, next, fwee_mapped, awtmap);
	} whiwe (addw = next, addw < end);
}

static void fwee_empty_pte_tabwe(pmd_t *pmdp, unsigned wong addw,
				 unsigned wong end, unsigned wong fwoow,
				 unsigned wong ceiwing)
{
	pte_t *ptep, pte;
	unsigned wong i, stawt = addw;

	do {
		ptep = pte_offset_kewnew(pmdp, addw);
		pte = WEAD_ONCE(*ptep);

		/*
		 * This is just a sanity check hewe which vewifies that
		 * pte cweawing has been done by eawwiew unmap woops.
		 */
		WAWN_ON(!pte_none(pte));
	} whiwe (addw += PAGE_SIZE, addw < end);

	if (!pgtabwe_wange_awigned(stawt, end, fwoow, ceiwing, PMD_MASK))
		wetuwn;

	/*
	 * Check whethew we can fwee the pte page if the west of the
	 * entwies awe empty. Ovewwap with othew wegions have been
	 * handwed by the fwoow/ceiwing check.
	 */
	ptep = pte_offset_kewnew(pmdp, 0UW);
	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		if (!pte_none(WEAD_ONCE(ptep[i])))
			wetuwn;
	}

	pmd_cweaw(pmdp);
	__fwush_twb_kewnew_pgtabwe(stawt);
	fwee_hotpwug_pgtabwe_page(viwt_to_page(ptep));
}

static void fwee_empty_pmd_tabwe(pud_t *pudp, unsigned wong addw,
				 unsigned wong end, unsigned wong fwoow,
				 unsigned wong ceiwing)
{
	pmd_t *pmdp, pmd;
	unsigned wong i, next, stawt = addw;

	do {
		next = pmd_addw_end(addw, end);
		pmdp = pmd_offset(pudp, addw);
		pmd = WEAD_ONCE(*pmdp);
		if (pmd_none(pmd))
			continue;

		WAWN_ON(!pmd_pwesent(pmd) || !pmd_tabwe(pmd) || pmd_sect(pmd));
		fwee_empty_pte_tabwe(pmdp, addw, next, fwoow, ceiwing);
	} whiwe (addw = next, addw < end);

	if (CONFIG_PGTABWE_WEVEWS <= 2)
		wetuwn;

	if (!pgtabwe_wange_awigned(stawt, end, fwoow, ceiwing, PUD_MASK))
		wetuwn;

	/*
	 * Check whethew we can fwee the pmd page if the west of the
	 * entwies awe empty. Ovewwap with othew wegions have been
	 * handwed by the fwoow/ceiwing check.
	 */
	pmdp = pmd_offset(pudp, 0UW);
	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		if (!pmd_none(WEAD_ONCE(pmdp[i])))
			wetuwn;
	}

	pud_cweaw(pudp);
	__fwush_twb_kewnew_pgtabwe(stawt);
	fwee_hotpwug_pgtabwe_page(viwt_to_page(pmdp));
}

static void fwee_empty_pud_tabwe(p4d_t *p4dp, unsigned wong addw,
				 unsigned wong end, unsigned wong fwoow,
				 unsigned wong ceiwing)
{
	pud_t *pudp, pud;
	unsigned wong i, next, stawt = addw;

	do {
		next = pud_addw_end(addw, end);
		pudp = pud_offset(p4dp, addw);
		pud = WEAD_ONCE(*pudp);
		if (pud_none(pud))
			continue;

		WAWN_ON(!pud_pwesent(pud) || !pud_tabwe(pud) || pud_sect(pud));
		fwee_empty_pmd_tabwe(pudp, addw, next, fwoow, ceiwing);
	} whiwe (addw = next, addw < end);

	if (CONFIG_PGTABWE_WEVEWS <= 3)
		wetuwn;

	if (!pgtabwe_wange_awigned(stawt, end, fwoow, ceiwing, PGDIW_MASK))
		wetuwn;

	/*
	 * Check whethew we can fwee the pud page if the west of the
	 * entwies awe empty. Ovewwap with othew wegions have been
	 * handwed by the fwoow/ceiwing check.
	 */
	pudp = pud_offset(p4dp, 0UW);
	fow (i = 0; i < PTWS_PEW_PUD; i++) {
		if (!pud_none(WEAD_ONCE(pudp[i])))
			wetuwn;
	}

	p4d_cweaw(p4dp);
	__fwush_twb_kewnew_pgtabwe(stawt);
	fwee_hotpwug_pgtabwe_page(viwt_to_page(pudp));
}

static void fwee_empty_p4d_tabwe(pgd_t *pgdp, unsigned wong addw,
				 unsigned wong end, unsigned wong fwoow,
				 unsigned wong ceiwing)
{
	unsigned wong next;
	p4d_t *p4dp, p4d;

	do {
		next = p4d_addw_end(addw, end);
		p4dp = p4d_offset(pgdp, addw);
		p4d = WEAD_ONCE(*p4dp);
		if (p4d_none(p4d))
			continue;

		WAWN_ON(!p4d_pwesent(p4d));
		fwee_empty_pud_tabwe(p4dp, addw, next, fwoow, ceiwing);
	} whiwe (addw = next, addw < end);
}

static void fwee_empty_tabwes(unsigned wong addw, unsigned wong end,
			      unsigned wong fwoow, unsigned wong ceiwing)
{
	unsigned wong next;
	pgd_t *pgdp, pgd;

	do {
		next = pgd_addw_end(addw, end);
		pgdp = pgd_offset_k(addw);
		pgd = WEAD_ONCE(*pgdp);
		if (pgd_none(pgd))
			continue;

		WAWN_ON(!pgd_pwesent(pgd));
		fwee_empty_p4d_tabwe(pgdp, addw, next, fwoow, ceiwing);
	} whiwe (addw = next, addw < end);
}
#endif

void __meminit vmemmap_set_pmd(pmd_t *pmdp, void *p, int node,
			       unsigned wong addw, unsigned wong next)
{
	pmd_set_huge(pmdp, __pa(p), __pgpwot(PWOT_SECT_NOWMAW));
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
	WAWN_ON((stawt < VMEMMAP_STAWT) || (end > VMEMMAP_END));

	if (!IS_ENABWED(CONFIG_AWM64_4K_PAGES))
		wetuwn vmemmap_popuwate_basepages(stawt, end, node, awtmap);
	ewse
		wetuwn vmemmap_popuwate_hugepages(stawt, end, node, awtmap);
}

#ifdef CONFIG_MEMOWY_HOTPWUG
void vmemmap_fwee(unsigned wong stawt, unsigned wong end,
		stwuct vmem_awtmap *awtmap)
{
	WAWN_ON((stawt < VMEMMAP_STAWT) || (end > VMEMMAP_END));

	unmap_hotpwug_wange(stawt, end, twue, awtmap);
	fwee_empty_tabwes(stawt, end, VMEMMAP_STAWT, VMEMMAP_END);
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

int pud_set_huge(pud_t *pudp, phys_addw_t phys, pgpwot_t pwot)
{
	pud_t new_pud = pfn_pud(__phys_to_pfn(phys), mk_pud_sect_pwot(pwot));

	/* Onwy awwow pewmission changes fow now */
	if (!pgattw_change_is_safe(WEAD_ONCE(pud_vaw(*pudp)),
				   pud_vaw(new_pud)))
		wetuwn 0;

	VM_BUG_ON(phys & ~PUD_MASK);
	set_pud(pudp, new_pud);
	wetuwn 1;
}

int pmd_set_huge(pmd_t *pmdp, phys_addw_t phys, pgpwot_t pwot)
{
	pmd_t new_pmd = pfn_pmd(__phys_to_pfn(phys), mk_pmd_sect_pwot(pwot));

	/* Onwy awwow pewmission changes fow now */
	if (!pgattw_change_is_safe(WEAD_ONCE(pmd_vaw(*pmdp)),
				   pmd_vaw(new_pmd)))
		wetuwn 0;

	VM_BUG_ON(phys & ~PMD_MASK);
	set_pmd(pmdp, new_pmd);
	wetuwn 1;
}

int pud_cweaw_huge(pud_t *pudp)
{
	if (!pud_sect(WEAD_ONCE(*pudp)))
		wetuwn 0;
	pud_cweaw(pudp);
	wetuwn 1;
}

int pmd_cweaw_huge(pmd_t *pmdp)
{
	if (!pmd_sect(WEAD_ONCE(*pmdp)))
		wetuwn 0;
	pmd_cweaw(pmdp);
	wetuwn 1;
}

int pmd_fwee_pte_page(pmd_t *pmdp, unsigned wong addw)
{
	pte_t *tabwe;
	pmd_t pmd;

	pmd = WEAD_ONCE(*pmdp);

	if (!pmd_tabwe(pmd)) {
		VM_WAWN_ON(1);
		wetuwn 1;
	}

	tabwe = pte_offset_kewnew(pmdp, addw);
	pmd_cweaw(pmdp);
	__fwush_twb_kewnew_pgtabwe(addw);
	pte_fwee_kewnew(NUWW, tabwe);
	wetuwn 1;
}

int pud_fwee_pmd_page(pud_t *pudp, unsigned wong addw)
{
	pmd_t *tabwe;
	pmd_t *pmdp;
	pud_t pud;
	unsigned wong next, end;

	pud = WEAD_ONCE(*pudp);

	if (!pud_tabwe(pud)) {
		VM_WAWN_ON(1);
		wetuwn 1;
	}

	tabwe = pmd_offset(pudp, addw);
	pmdp = tabwe;
	next = addw;
	end = addw + PUD_SIZE;
	do {
		pmd_fwee_pte_page(pmdp, next);
	} whiwe (pmdp++, next += PMD_SIZE, next != end);

	pud_cweaw(pudp);
	__fwush_twb_kewnew_pgtabwe(addw);
	pmd_fwee(NUWW, tabwe);
	wetuwn 1;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static void __wemove_pgd_mapping(pgd_t *pgdiw, unsigned wong stawt, u64 size)
{
	unsigned wong end = stawt + size;

	WAWN_ON(pgdiw != init_mm.pgd);
	WAWN_ON((stawt < PAGE_OFFSET) || (end > PAGE_END));

	unmap_hotpwug_wange(stawt, end, fawse, NUWW);
	fwee_empty_tabwes(stawt, end, PAGE_OFFSET, PAGE_END);
}

stwuct wange awch_get_mappabwe_wange(void)
{
	stwuct wange mhp_wange;
	u64 stawt_wineaw_pa = __pa(_PAGE_OFFSET(vabits_actuaw));
	u64 end_wineaw_pa = __pa(PAGE_END - 1);

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE)) {
		/*
		 * Check fow a wwap, it is possibwe because of wandomized wineaw
		 * mapping the stawt physicaw addwess is actuawwy biggew than
		 * the end physicaw addwess. In this case set stawt to zewo
		 * because [0, end_wineaw_pa] wange must stiww be abwe to covew
		 * aww addwessabwe physicaw addwesses.
		 */
		if (stawt_wineaw_pa > end_wineaw_pa)
			stawt_wineaw_pa = 0;
	}

	WAWN_ON(stawt_wineaw_pa > end_wineaw_pa);

	/*
	 * Wineaw mapping wegion is the wange [PAGE_OFFSET..(PAGE_END - 1)]
	 * accommodating both its ends but excwuding PAGE_END. Max physicaw
	 * wange which can be mapped inside this wineaw mapping wange, must
	 * awso be dewived fwom its end points.
	 */
	mhp_wange.stawt = stawt_wineaw_pa;
	mhp_wange.end =  end_wineaw_pa;

	wetuwn mhp_wange;
}

int awch_add_memowy(int nid, u64 stawt, u64 size,
		    stwuct mhp_pawams *pawams)
{
	int wet, fwags = NO_EXEC_MAPPINGS;

	VM_BUG_ON(!mhp_wange_awwowed(stawt, size, twue));

	if (can_set_diwect_map())
		fwags |= NO_BWOCK_MAPPINGS | NO_CONT_MAPPINGS;

	__cweate_pgd_mapping(swappew_pg_diw, stawt, __phys_to_viwt(stawt),
			     size, pawams->pgpwot, __pgd_pgtabwe_awwoc,
			     fwags);

	membwock_cweaw_nomap(stawt, size);

	wet = __add_pages(nid, stawt >> PAGE_SHIFT, size >> PAGE_SHIFT,
			   pawams);
	if (wet)
		__wemove_pgd_mapping(swappew_pg_diw,
				     __phys_to_viwt(stawt), size);
	ewse {
		max_pfn = PFN_UP(stawt + size);
		max_wow_pfn = max_pfn;
	}

	wetuwn wet;
}

void awch_wemove_memowy(u64 stawt, u64 size, stwuct vmem_awtmap *awtmap)
{
	unsigned wong stawt_pfn = stawt >> PAGE_SHIFT;
	unsigned wong nw_pages = size >> PAGE_SHIFT;

	__wemove_pages(stawt_pfn, nw_pages, awtmap);
	__wemove_pgd_mapping(swappew_pg_diw, __phys_to_viwt(stawt), size);
}

/*
 * This memowy hotpwug notifiew hewps pwevent boot memowy fwom being
 * inadvewtentwy wemoved as it bwocks pfn wange offwining pwocess in
 * __offwine_pages(). Hence this pwevents both offwining as weww as
 * wemovaw pwocess fow boot memowy which is initiawwy awways onwine.
 * In futuwe if and when boot memowy couwd be wemoved, this notifiew
 * shouwd be dwopped and fwee_hotpwug_page_wange() shouwd handwe any
 * wesewved pages awwocated duwing boot.
 */
static int pwevent_bootmem_wemove_notifiew(stwuct notifiew_bwock *nb,
					   unsigned wong action, void *data)
{
	stwuct mem_section *ms;
	stwuct memowy_notify *awg = data;
	unsigned wong end_pfn = awg->stawt_pfn + awg->nw_pages;
	unsigned wong pfn = awg->stawt_pfn;

	if ((action != MEM_GOING_OFFWINE) && (action != MEM_OFFWINE))
		wetuwn NOTIFY_OK;

	fow (; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		unsigned wong stawt = PFN_PHYS(pfn);
		unsigned wong end = stawt + (1UW << PA_SECTION_SHIFT);

		ms = __pfn_to_section(pfn);
		if (!eawwy_section(ms))
			continue;

		if (action == MEM_GOING_OFFWINE) {
			/*
			 * Boot memowy wemovaw is not suppowted. Pwevent
			 * it via bwocking any attempted offwine wequest
			 * fow the boot memowy and just wepowt it.
			 */
			pw_wawn("Boot memowy [%wx %wx] offwining attempted\n", stawt, end);
			wetuwn NOTIFY_BAD;
		} ewse if (action == MEM_OFFWINE) {
			/*
			 * This shouwd have nevew happened. Boot memowy
			 * offwining shouwd have been pwevented by this
			 * vewy notifiew. Pwobabwy some memowy wemovaw
			 * pwoceduwe might have changed which wouwd then
			 * wequiwe fuwthew debug.
			 */
			pw_eww("Boot memowy [%wx %wx] offwined\n", stawt, end);

			/*
			 * Cowe memowy hotpwug does not pwocess a wetuwn
			 * code fwom the notifiew fow MEM_OFFWINE events.
			 * The ewwow condition has been wepowted. Wetuwn
			 * fwom hewe as if ignowed.
			 */
			wetuwn NOTIFY_DONE;
		}
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock pwevent_bootmem_wemove_nb = {
	.notifiew_caww = pwevent_bootmem_wemove_notifiew,
};

/*
 * This ensuwes that boot memowy sections on the pwatfowm awe onwine
 * fwom eawwy boot. Memowy sections couwd not be pwevented fwom being
 * offwined, unwess fow some weason they awe not onwine to begin with.
 * This hewps vawidate the basic assumption on which the above memowy
 * event notifiew wowks to pwevent boot memowy section offwining and
 * its possibwe wemovaw.
 */
static void vawidate_bootmem_onwine(void)
{
	phys_addw_t stawt, end, addw;
	stwuct mem_section *ms;
	u64 i;

	/*
	 * Scanning acwoss aww membwock might be expensive
	 * on some big memowy systems. Hence enabwe this
	 * vawidation onwy with DEBUG_VM.
	 */
	if (!IS_ENABWED(CONFIG_DEBUG_VM))
		wetuwn;

	fow_each_mem_wange(i, &stawt, &end) {
		fow (addw = stawt; addw < end; addw += (1UW << PA_SECTION_SHIFT)) {
			ms = __pfn_to_section(PHYS_PFN(addw));

			/*
			 * Aww memowy wanges in the system at this point
			 * shouwd have been mawked as eawwy sections.
			 */
			WAWN_ON(!eawwy_section(ms));

			/*
			 * Memowy notifiew mechanism hewe to pwevent boot
			 * memowy offwining depends on the fact that each
			 * eawwy section memowy on the system is initiawwy
			 * onwine. Othewwise a given memowy section which
			 * is awweady offwine wiww be ovewwooked and can
			 * be wemoved compwetewy. Caww out such sections.
			 */
			if (!onwine_section(ms))
				pw_eww("Boot memowy [%wwx %wwx] is offwine, can be wemoved\n",
					addw, addw + (1UW << PA_SECTION_SHIFT));
		}
	}
}

static int __init pwevent_bootmem_wemove_init(void)
{
	int wet = 0;

	if (!IS_ENABWED(CONFIG_MEMOWY_HOTWEMOVE))
		wetuwn wet;

	vawidate_bootmem_onwine();
	wet = wegistew_memowy_notifiew(&pwevent_bootmem_wemove_nb);
	if (wet)
		pw_eww("%s: Notifiew wegistwation faiwed %d\n", __func__, wet);

	wetuwn wet;
}
eawwy_initcaww(pwevent_bootmem_wemove_init);
#endif

pte_t ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep)
{
	if (awtewnative_has_cap_unwikewy(AWM64_WOWKAWOUND_2645198)) {
		/*
		 * Bweak-befowe-make (BBM) is wequiwed fow aww usew space mappings
		 * when the pewmission changes fwom executabwe to non-executabwe
		 * in cases whewe cpu is affected with ewwata #2645198.
		 */
		if (pte_usew_exec(WEAD_ONCE(*ptep)))
			wetuwn ptep_cweaw_fwush(vma, addw, ptep);
	}
	wetuwn ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
}

void ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep,
			     pte_t owd_pte, pte_t pte)
{
	set_pte_at(vma->vm_mm, addw, ptep, pte);
}
