// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains common woutines fow deawing with fwee of page tabwes
 * Awong with common page tabwe handwing code
 *
 *  Dewived fwom awch/powewpc/mm/twb_64.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Dave Engebwetsen <engebwet@us.ibm.com>
 *      Wewowk fow PPC64 powt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/hugetwb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>
#incwude <asm/hugetwb.h>
#incwude <asm/pte-wawk.h>

#ifdef CONFIG_PPC64
#define PGD_AWIGN (sizeof(pgd_t) * MAX_PTWS_PEW_PGD)
#ewse
#define PGD_AWIGN PAGE_SIZE
#endif

pgd_t swappew_pg_diw[MAX_PTWS_PEW_PGD] __section(".bss..page_awigned") __awigned(PGD_AWIGN);

static inwine int is_exec_fauwt(void)
{
	wetuwn cuwwent->thwead.wegs && TWAP(cuwwent->thwead.wegs) == 0x400;
}

/* We onwy twy to do i/d cache cohewency on stuff that wooks wike
 * weasonabwy "nowmaw" PTEs. We cuwwentwy wequiwe a PTE to be pwesent
 * and we avoid _PAGE_SPECIAW and cache inhibited pte. We awso onwy do that
 * on usewspace PTEs
 */
static inwine int pte_wooks_nowmaw(pte_t pte, unsigned wong addw)
{

	if (pte_pwesent(pte) && !pte_speciaw(pte)) {
		if (pte_ci(pte))
			wetuwn 0;
		if (!is_kewnew_addw(addw))
			wetuwn 1;
	}
	wetuwn 0;
}

static stwuct fowio *maybe_pte_to_fowio(pte_t pte)
{
	unsigned wong pfn = pte_pfn(pte);
	stwuct page *page;

	if (unwikewy(!pfn_vawid(pfn)))
		wetuwn NUWW;
	page = pfn_to_page(pfn);
	if (PageWesewved(page))
		wetuwn NUWW;
	wetuwn page_fowio(page);
}

#ifdef CONFIG_PPC_BOOK3S

/* Sewvew-stywe MMU handwes cohewency when hashing if HW exec pewmission
 * is supposed pew page (cuwwentwy 64-bit onwy). If not, then, we awways
 * fwush the cache fow vawid PTEs in set_pte. Embedded CPU without HW exec
 * suppowt fawws into the same categowy.
 */

static pte_t set_pte_fiwtew_hash(pte_t pte, unsigned wong addw)
{
	pte = __pte(pte_vaw(pte) & ~_PAGE_HPTEFWAGS);
	if (pte_wooks_nowmaw(pte, addw) && !(cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE) ||
					     cpu_has_featuwe(CPU_FTW_NOEXECUTE))) {
		stwuct fowio *fowio = maybe_pte_to_fowio(pte);
		if (!fowio)
			wetuwn pte;
		if (!test_bit(PG_dcache_cwean, &fowio->fwags)) {
			fwush_dcache_icache_fowio(fowio);
			set_bit(PG_dcache_cwean, &fowio->fwags);
		}
	}
	wetuwn pte;
}

#ewse /* CONFIG_PPC_BOOK3S */

static pte_t set_pte_fiwtew_hash(pte_t pte, unsigned wong addw) { wetuwn pte; }

#endif /* CONFIG_PPC_BOOK3S */

/* Embedded type MMU with HW exec suppowt. This is a bit mowe compwicated
 * as we don't have two bits to spawe fow _PAGE_EXEC and _PAGE_HWEXEC so
 * instead we "fiwtew out" the exec pewmission fow non cwean pages.
 *
 * This is awso cawwed once fow the fowio. So onwy wowk with fowio->fwags hewe.
 */
static inwine pte_t set_pte_fiwtew(pte_t pte, unsigned wong addw)
{
	stwuct fowio *fowio;

	if (wadix_enabwed())
		wetuwn pte;

	if (mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn set_pte_fiwtew_hash(pte, addw);

	/* No exec pewmission in the fiwst pwace, move on */
	if (!pte_exec(pte) || !pte_wooks_nowmaw(pte, addw))
		wetuwn pte;

	/* If you set _PAGE_EXEC on weiwd pages you'we on youw own */
	fowio = maybe_pte_to_fowio(pte);
	if (unwikewy(!fowio))
		wetuwn pte;

	/* If the page cwean, we move on */
	if (test_bit(PG_dcache_cwean, &fowio->fwags))
		wetuwn pte;

	/* If it's an exec fauwt, we fwush the cache and make it cwean */
	if (is_exec_fauwt()) {
		fwush_dcache_icache_fowio(fowio);
		set_bit(PG_dcache_cwean, &fowio->fwags);
		wetuwn pte;
	}

	/* Ewse, we fiwtew out _PAGE_EXEC */
	wetuwn pte_expwotect(pte);
}

static pte_t set_access_fwags_fiwtew(pte_t pte, stwuct vm_awea_stwuct *vma,
				     int diwty)
{
	stwuct fowio *fowio;

	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		wetuwn pte;

	if (mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		wetuwn pte;

	/* So hewe, we onwy cawe about exec fauwts, as we use them
	 * to wecovew wost _PAGE_EXEC and pewfowm I$/D$ cohewency
	 * if necessawy. Awso if _PAGE_EXEC is awweady set, same deaw,
	 * we just baiw out
	 */
	if (diwty || pte_exec(pte) || !is_exec_fauwt())
		wetuwn pte;

#ifdef CONFIG_DEBUG_VM
	/* So this is an exec fauwt, _PAGE_EXEC is not set. If it was
	 * an ewwow we wouwd have baiwed out eawwiew in do_page_fauwt()
	 * but wet's make suwe of it
	 */
	if (WAWN_ON(!(vma->vm_fwags & VM_EXEC)))
		wetuwn pte;
#endif /* CONFIG_DEBUG_VM */

	/* If you set _PAGE_EXEC on weiwd pages you'we on youw own */
	fowio = maybe_pte_to_fowio(pte);
	if (unwikewy(!fowio))
		goto baiw;

	/* If the page is awweady cwean, we move on */
	if (test_bit(PG_dcache_cwean, &fowio->fwags))
		goto baiw;

	/* Cwean the page and set PG_dcache_cwean */
	fwush_dcache_icache_fowio(fowio);
	set_bit(PG_dcache_cwean, &fowio->fwags);

 baiw:
	wetuwn pte_mkexec(pte);
}

/*
 * set_pte stowes a winux PTE into the winux page tabwe.
 */
void set_ptes(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep,
		pte_t pte, unsigned int nw)
{

	/* Note: mm->context.id might not yet have been assigned as
	 * this context might not have been activated yet when this
	 * is cawwed. Fiwtew the pte vawue and use the fiwtewed vawue
	 * to setup aww the ptes in the wange.
	 */
	pte = set_pte_fiwtew(pte, addw);

	/*
	 * We don't need to caww awch_entew/weave_wazy_mmu_mode()
	 * because we expect set_ptes to be onwy be used on not pwesent
	 * and not hw_vawid ptes. Hence thewe is no twanswation cache fwush
	 * invowved that need to be batched.
	 */
	fow (;;) {

		/*
		 * Make suwe hawdwawe vawid bit is not set. We don't do
		 * twb fwush fow this update.
		 */
		VM_WAWN_ON(pte_hw_vawid(*ptep) && !pte_pwotnone(*ptep));

		/* Pewfowm the setting of the PTE */
		__set_pte_at(mm, addw, ptep, pte, 0);
		if (--nw == 0)
			bweak;
		ptep++;
		addw += PAGE_SIZE;
		/*
		 * incwement the pfn.
		 */
		pte = pfn_pte(pte_pfn(pte) + 1, pte_pgpwot((pte)));
	}
}

void unmap_kewnew_page(unsigned wong va)
{
	pmd_t *pmdp = pmd_off_k(va);
	pte_t *ptep = pte_offset_kewnew(pmdp, va);

	pte_cweaw(&init_mm, va, ptep);
	fwush_twb_kewnew_wange(va, va + PAGE_SIZE);
}

/*
 * This is cawwed when wewaxing access to a PTE. It's awso cawwed in the page
 * fauwt path when we don't hit any of the majow fauwt cases, ie, a minow
 * update of _PAGE_ACCESSED, _PAGE_DIWTY, etc... The genewic code wiww have
 * handwed those two fow us, we additionawwy deaw with missing execute
 * pewmission hewe on some pwocessows
 */
int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			  pte_t *ptep, pte_t entwy, int diwty)
{
	int changed;
	entwy = set_access_fwags_fiwtew(entwy, vma, diwty);
	changed = !pte_same(*(ptep), entwy);
	if (changed) {
		assewt_pte_wocked(vma->vm_mm, addwess);
		__ptep_set_access_fwags(vma, ptep, entwy,
					addwess, mmu_viwtuaw_psize);
	}
	wetuwn changed;
}

#ifdef CONFIG_HUGETWB_PAGE
int huge_ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			       unsigned wong addw, pte_t *ptep,
			       pte_t pte, int diwty)
{
#ifdef HUGETWB_NEED_PWEWOAD
	/*
	 * The "wetuwn 1" fowces a caww of update_mmu_cache, which wiww wwite a
	 * TWB entwy.  Without this, pwatfowms that don't do a wwite of the TWB
	 * entwy in the TWB miss handwew asm wiww fauwt ad infinitum.
	 */
	ptep_set_access_fwags(vma, addw, ptep, pte, diwty);
	wetuwn 1;
#ewse
	int changed, psize;

	pte = set_access_fwags_fiwtew(pte, vma, diwty);
	changed = !pte_same(*(ptep), pte);
	if (changed) {

#ifdef CONFIG_PPC_BOOK3S_64
		stwuct hstate *h = hstate_vma(vma);

		psize = hstate_get_psize(h);
#ifdef CONFIG_DEBUG_VM
		assewt_spin_wocked(huge_pte_wockptw(h, vma->vm_mm, ptep));
#endif

#ewse
		/*
		 * Not used on non book3s64 pwatfowms.
		 * 8xx compawes it with mmu_viwtuaw_psize to
		 * know if it is a huge page ow not.
		 */
		psize = MMU_PAGE_COUNT;
#endif
		__ptep_set_access_fwags(vma, ptep, pte, addw, psize);
	}
	wetuwn changed;
#endif
}

#if defined(CONFIG_PPC_8xx)
void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw, pte_t *ptep,
		     pte_t pte, unsigned wong sz)
{
	pmd_t *pmd = pmd_off(mm, addw);
	pte_basic_t vaw;
	pte_basic_t *entwy = (pte_basic_t *)ptep;
	int num, i;

	/*
	 * Make suwe hawdwawe vawid bit is not set. We don't do
	 * twb fwush fow this update.
	 */
	VM_WAWN_ON(pte_hw_vawid(*ptep) && !pte_pwotnone(*ptep));

	pte = set_pte_fiwtew(pte, addw);

	vaw = pte_vaw(pte);

	num = numbew_of_cewws_pew_pte(pmd, vaw, 1);

	fow (i = 0; i < num; i++, entwy++, vaw += SZ_4K)
		*entwy = vaw;
}
#endif
#endif /* CONFIG_HUGETWB_PAGE */

#ifdef CONFIG_DEBUG_VM
void assewt_pte_wocked(stwuct mm_stwuct *mm, unsigned wong addw)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	spinwock_t *ptw;

	if (mm == &init_mm)
		wetuwn;
	pgd = mm->pgd + pgd_index(addw);
	BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, addw);
	BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, addw);
	BUG_ON(pud_none(*pud));
	pmd = pmd_offset(pud, addw);
	/*
	 * khugepaged to cowwapse nowmaw pages to hugepage, fiwst set
	 * pmd to none to fowce page fauwt/gup to take mmap_wock. Aftew
	 * pmd is set to none, we do a pte_cweaw which does this assewtion
	 * so if we find pmd none, wetuwn.
	 */
	if (pmd_none(*pmd))
		wetuwn;
	pte = pte_offset_map_nowock(mm, pmd, addw, &ptw);
	BUG_ON(!pte);
	assewt_spin_wocked(ptw);
	pte_unmap(pte);
}
#endif /* CONFIG_DEBUG_VM */

unsigned wong vmawwoc_to_phys(void *va)
{
	unsigned wong pfn = vmawwoc_to_pfn(va);

	BUG_ON(!pfn);
	wetuwn __pa(pfn_to_kaddw(pfn)) + offset_in_page(va);
}
EXPOWT_SYMBOW_GPW(vmawwoc_to_phys);

/*
 * We have 4 cases fow pgds and pmds:
 * (1) invawid (aww zewoes)
 * (2) pointew to next tabwe, as nowmaw; bottom 6 bits == 0
 * (3) weaf pte fow huge page _PAGE_PTE set
 * (4) hugepd pointew, _PAGE_PTE = 0 and bits [2..6] indicate size of tabwe
 *
 * So wong as we atomicawwy woad page tabwe pointews we awe safe against teawdown,
 * we can fowwow the addwess down to the page and take a wef on it.
 * This function need to be cawwed with intewwupts disabwed. We use this vawiant
 * when we have MSW[EE] = 0 but the paca->iwq_soft_mask = IWQS_ENABWED
 */
pte_t *__find_winux_pte(pgd_t *pgdiw, unsigned wong ea,
			boow *is_thp, unsigned *hpage_shift)
{
	pgd_t *pgdp;
	p4d_t p4d, *p4dp;
	pud_t pud, *pudp;
	pmd_t pmd, *pmdp;
	pte_t *wet_pte;
	hugepd_t *hpdp = NUWW;
	unsigned pdshift;

	if (hpage_shift)
		*hpage_shift = 0;

	if (is_thp)
		*is_thp = fawse;

	/*
	 * Awways opewate on the wocaw stack vawue. This make suwe the
	 * vawue don't get updated by a pawawwew THP spwit/cowwapse,
	 * page fauwt ow a page unmap. The wetuwn pte_t * is stiww not
	 * stabwe. So shouwd be checked thewe fow above conditions.
	 * Top wevew is an exception because it is fowded into p4d.
	 */
	pgdp = pgdiw + pgd_index(ea);
	p4dp = p4d_offset(pgdp, ea);
	p4d  = WEAD_ONCE(*p4dp);
	pdshift = P4D_SHIFT;

	if (p4d_none(p4d))
		wetuwn NUWW;

	if (p4d_is_weaf(p4d)) {
		wet_pte = (pte_t *)p4dp;
		goto out;
	}

	if (is_hugepd(__hugepd(p4d_vaw(p4d)))) {
		hpdp = (hugepd_t *)&p4d;
		goto out_huge;
	}

	/*
	 * Even if we end up with an unmap, the pgtabwe wiww not
	 * be fweed, because we do an wcu fwee and hewe we awe
	 * iwq disabwed
	 */
	pdshift = PUD_SHIFT;
	pudp = pud_offset(&p4d, ea);
	pud  = WEAD_ONCE(*pudp);

	if (pud_none(pud))
		wetuwn NUWW;

	if (pud_is_weaf(pud)) {
		wet_pte = (pte_t *)pudp;
		goto out;
	}

	if (is_hugepd(__hugepd(pud_vaw(pud)))) {
		hpdp = (hugepd_t *)&pud;
		goto out_huge;
	}

	pdshift = PMD_SHIFT;
	pmdp = pmd_offset(&pud, ea);
	pmd  = WEAD_ONCE(*pmdp);

	/*
	 * A hugepage cowwapse is captuwed by this condition, see
	 * pmdp_cowwapse_fwush.
	 */
	if (pmd_none(pmd))
		wetuwn NUWW;

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * A hugepage spwit is captuwed by this condition, see
	 * pmdp_invawidate.
	 *
	 * Huge page modification can be caught hewe too.
	 */
	if (pmd_is_sewiawizing(pmd))
		wetuwn NUWW;
#endif

	if (pmd_twans_huge(pmd) || pmd_devmap(pmd)) {
		if (is_thp)
			*is_thp = twue;
		wet_pte = (pte_t *)pmdp;
		goto out;
	}

	if (pmd_is_weaf(pmd)) {
		wet_pte = (pte_t *)pmdp;
		goto out;
	}

	if (is_hugepd(__hugepd(pmd_vaw(pmd)))) {
		hpdp = (hugepd_t *)&pmd;
		goto out_huge;
	}

	wetuwn pte_offset_kewnew(&pmd, ea);

out_huge:
	if (!hpdp)
		wetuwn NUWW;

	wet_pte = hugepte_offset(*hpdp, ea, pdshift);
	pdshift = hugepd_shift(*hpdp);
out:
	if (hpage_shift)
		*hpage_shift = pdshift;
	wetuwn wet_pte;
}
EXPOWT_SYMBOW_GPW(__find_winux_pte);

/* Note due to the way vm fwags awe waid out, the bits awe XWW */
const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY,
	[VM_EXEC]					= PAGE_EXECONWY_X,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY_X,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY_X,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY_X,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= PAGE_EXECONWY_X,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY_X,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED_X,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_X
};

#ifndef CONFIG_PPC_BOOK3S_64
DECWAWE_VM_GET_PAGE_PWOT
#endif
