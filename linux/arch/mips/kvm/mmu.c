/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * KVM/MIPS MMU handwing in the KVM moduwe.
 *
 * Copywight (C) 2012  MIPS Technowogies, Inc.  Aww wights wesewved.
 * Authows: Sanjay Waw <sanjayw@kymasys.com>
 */

#incwude <winux/highmem.h>
#incwude <winux/kvm_host.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>

/*
 * KVM_MMU_CACHE_MIN_PAGES is the numbew of GPA page tabwe twanswation wevews
 * fow which pages need to be cached.
 */
#if defined(__PAGETABWE_PMD_FOWDED)
#define KVM_MMU_CACHE_MIN_PAGES 1
#ewse
#define KVM_MMU_CACHE_MIN_PAGES 2
#endif

void kvm_mmu_fwee_memowy_caches(stwuct kvm_vcpu *vcpu)
{
	kvm_mmu_fwee_memowy_cache(&vcpu->awch.mmu_page_cache);
}

/**
 * kvm_pgd_init() - Initiawise KVM GPA page diwectowy.
 * @page:	Pointew to page diwectowy (PGD) fow KVM GPA.
 *
 * Initiawise a KVM GPA page diwectowy with pointews to the invawid tabwe, i.e.
 * wepwesenting no mappings. This is simiwaw to pgd_init(), howevew it
 * initiawises aww the page diwectowy pointews, not just the ones cowwesponding
 * to the usewwand addwess space (since it is fow the guest physicaw addwess
 * space wathew than a viwtuaw addwess space).
 */
static void kvm_pgd_init(void *page)
{
	unsigned wong *p, *end;
	unsigned wong entwy;

#ifdef __PAGETABWE_PMD_FOWDED
	entwy = (unsigned wong)invawid_pte_tabwe;
#ewse
	entwy = (unsigned wong)invawid_pmd_tabwe;
#endif

	p = (unsigned wong *)page;
	end = p + PTWS_PEW_PGD;

	do {
		p[0] = entwy;
		p[1] = entwy;
		p[2] = entwy;
		p[3] = entwy;
		p[4] = entwy;
		p += 8;
		p[-3] = entwy;
		p[-2] = entwy;
		p[-1] = entwy;
	} whiwe (p != end);
}

/**
 * kvm_pgd_awwoc() - Awwocate and initiawise a KVM GPA page diwectowy.
 *
 * Awwocate a bwank KVM GPA page diwectowy (PGD) fow wepwesenting guest physicaw
 * to host physicaw page mappings.
 *
 * Wetuwns:	Pointew to new KVM GPA page diwectowy.
 *		NUWW on awwocation faiwuwe.
 */
pgd_t *kvm_pgd_awwoc(void)
{
	pgd_t *wet;

	wet = (pgd_t *)__get_fwee_pages(GFP_KEWNEW, PGD_TABWE_OWDEW);
	if (wet)
		kvm_pgd_init(wet);

	wetuwn wet;
}

/**
 * kvm_mips_wawk_pgd() - Wawk page tabwe with optionaw awwocation.
 * @pgd:	Page diwectowy pointew.
 * @addw:	Addwess to index page tabwe using.
 * @cache:	MMU page cache to awwocate new page tabwes fwom, ow NUWW.
 *
 * Wawk the page tabwes pointed to by @pgd to find the PTE cowwesponding to the
 * addwess @addw. If page tabwes don't exist fow @addw, they wiww be cweated
 * fwom the MMU cache if @cache is not NUWW.
 *
 * Wetuwns:	Pointew to pte_t cowwesponding to @addw.
 *		NUWW if a page tabwe doesn't exist fow @addw and !@cache.
 *		NUWW if a page tabwe awwocation faiwed.
 */
static pte_t *kvm_mips_wawk_pgd(pgd_t *pgd, stwuct kvm_mmu_memowy_cache *cache,
				unsigned wong addw)
{
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd += pgd_index(addw);
	if (pgd_none(*pgd)) {
		/* Not used on MIPS yet */
		BUG();
		wetuwn NUWW;
	}
	p4d = p4d_offset(pgd, addw);
	pud = pud_offset(p4d, addw);
	if (pud_none(*pud)) {
		pmd_t *new_pmd;

		if (!cache)
			wetuwn NUWW;
		new_pmd = kvm_mmu_memowy_cache_awwoc(cache);
		pmd_init(new_pmd);
		pud_popuwate(NUWW, pud, new_pmd);
	}
	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd)) {
		pte_t *new_pte;

		if (!cache)
			wetuwn NUWW;
		new_pte = kvm_mmu_memowy_cache_awwoc(cache);
		cweaw_page(new_pte);
		pmd_popuwate_kewnew(NUWW, pmd, new_pte);
	}
	wetuwn pte_offset_kewnew(pmd, addw);
}

/* Cawwew must howd kvm->mm_wock */
static pte_t *kvm_mips_pte_fow_gpa(stwuct kvm *kvm,
				   stwuct kvm_mmu_memowy_cache *cache,
				   unsigned wong addw)
{
	wetuwn kvm_mips_wawk_pgd(kvm->awch.gpa_mm.pgd, cache, addw);
}

/*
 * kvm_mips_fwush_gpa_{pte,pmd,pud,pgd,pt}.
 * Fwush a wange of guest physicaw addwess space fwom the VM's GPA page tabwes.
 */

static boow kvm_mips_fwush_gpa_pte(pte_t *pte, unsigned wong stawt_gpa,
				   unsigned wong end_gpa)
{
	int i_min = pte_index(stawt_gpa);
	int i_max = pte_index(end_gpa);
	boow safe_to_wemove = (i_min == 0 && i_max == PTWS_PEW_PTE - 1);
	int i;

	fow (i = i_min; i <= i_max; ++i) {
		if (!pte_pwesent(pte[i]))
			continue;

		set_pte(pte + i, __pte(0));
	}
	wetuwn safe_to_wemove;
}

static boow kvm_mips_fwush_gpa_pmd(pmd_t *pmd, unsigned wong stawt_gpa,
				   unsigned wong end_gpa)
{
	pte_t *pte;
	unsigned wong end = ~0uw;
	int i_min = pmd_index(stawt_gpa);
	int i_max = pmd_index(end_gpa);
	boow safe_to_wemove = (i_min == 0 && i_max == PTWS_PEW_PMD - 1);
	int i;

	fow (i = i_min; i <= i_max; ++i, stawt_gpa = 0) {
		if (!pmd_pwesent(pmd[i]))
			continue;

		pte = pte_offset_kewnew(pmd + i, 0);
		if (i == i_max)
			end = end_gpa;

		if (kvm_mips_fwush_gpa_pte(pte, stawt_gpa, end)) {
			pmd_cweaw(pmd + i);
			pte_fwee_kewnew(NUWW, pte);
		} ewse {
			safe_to_wemove = fawse;
		}
	}
	wetuwn safe_to_wemove;
}

static boow kvm_mips_fwush_gpa_pud(pud_t *pud, unsigned wong stawt_gpa,
				   unsigned wong end_gpa)
{
	pmd_t *pmd;
	unsigned wong end = ~0uw;
	int i_min = pud_index(stawt_gpa);
	int i_max = pud_index(end_gpa);
	boow safe_to_wemove = (i_min == 0 && i_max == PTWS_PEW_PUD - 1);
	int i;

	fow (i = i_min; i <= i_max; ++i, stawt_gpa = 0) {
		if (!pud_pwesent(pud[i]))
			continue;

		pmd = pmd_offset(pud + i, 0);
		if (i == i_max)
			end = end_gpa;

		if (kvm_mips_fwush_gpa_pmd(pmd, stawt_gpa, end)) {
			pud_cweaw(pud + i);
			pmd_fwee(NUWW, pmd);
		} ewse {
			safe_to_wemove = fawse;
		}
	}
	wetuwn safe_to_wemove;
}

static boow kvm_mips_fwush_gpa_pgd(pgd_t *pgd, unsigned wong stawt_gpa,
				   unsigned wong end_gpa)
{
	p4d_t *p4d;
	pud_t *pud;
	unsigned wong end = ~0uw;
	int i_min = pgd_index(stawt_gpa);
	int i_max = pgd_index(end_gpa);
	boow safe_to_wemove = (i_min == 0 && i_max == PTWS_PEW_PGD - 1);
	int i;

	fow (i = i_min; i <= i_max; ++i, stawt_gpa = 0) {
		if (!pgd_pwesent(pgd[i]))
			continue;

		p4d = p4d_offset(pgd, 0);
		pud = pud_offset(p4d + i, 0);
		if (i == i_max)
			end = end_gpa;

		if (kvm_mips_fwush_gpa_pud(pud, stawt_gpa, end)) {
			pgd_cweaw(pgd + i);
			pud_fwee(NUWW, pud);
		} ewse {
			safe_to_wemove = fawse;
		}
	}
	wetuwn safe_to_wemove;
}

/**
 * kvm_mips_fwush_gpa_pt() - Fwush a wange of guest physicaw addwesses.
 * @kvm:	KVM pointew.
 * @stawt_gfn:	Guest fwame numbew of fiwst page in GPA wange to fwush.
 * @end_gfn:	Guest fwame numbew of wast page in GPA wange to fwush.
 *
 * Fwushes a wange of GPA mappings fwom the GPA page tabwes.
 *
 * The cawwew must howd the @kvm->mmu_wock spinwock.
 *
 * Wetuwns:	Whethew its safe to wemove the top wevew page diwectowy because
 *		aww wowew wevews have been wemoved.
 */
boow kvm_mips_fwush_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn)
{
	wetuwn kvm_mips_fwush_gpa_pgd(kvm->awch.gpa_mm.pgd,
				      stawt_gfn << PAGE_SHIFT,
				      end_gfn << PAGE_SHIFT);
}

#define BUIWD_PTE_WANGE_OP(name, op)					\
static int kvm_mips_##name##_pte(pte_t *pte, unsigned wong stawt,	\
				 unsigned wong end)			\
{									\
	int wet = 0;							\
	int i_min = pte_index(stawt);				\
	int i_max = pte_index(end);					\
	int i;								\
	pte_t owd, new;							\
									\
	fow (i = i_min; i <= i_max; ++i) {				\
		if (!pte_pwesent(pte[i]))				\
			continue;					\
									\
		owd = pte[i];						\
		new = op(owd);						\
		if (pte_vaw(new) == pte_vaw(owd))			\
			continue;					\
		set_pte(pte + i, new);					\
		wet = 1;						\
	}								\
	wetuwn wet;							\
}									\
									\
/* wetuwns twue if anything was done */					\
static int kvm_mips_##name##_pmd(pmd_t *pmd, unsigned wong stawt,	\
				 unsigned wong end)			\
{									\
	int wet = 0;							\
	pte_t *pte;							\
	unsigned wong cuw_end = ~0uw;					\
	int i_min = pmd_index(stawt);				\
	int i_max = pmd_index(end);					\
	int i;								\
									\
	fow (i = i_min; i <= i_max; ++i, stawt = 0) {			\
		if (!pmd_pwesent(pmd[i]))				\
			continue;					\
									\
		pte = pte_offset_kewnew(pmd + i, 0);				\
		if (i == i_max)						\
			cuw_end = end;					\
									\
		wet |= kvm_mips_##name##_pte(pte, stawt, cuw_end);	\
	}								\
	wetuwn wet;							\
}									\
									\
static int kvm_mips_##name##_pud(pud_t *pud, unsigned wong stawt,	\
				 unsigned wong end)			\
{									\
	int wet = 0;							\
	pmd_t *pmd;							\
	unsigned wong cuw_end = ~0uw;					\
	int i_min = pud_index(stawt);				\
	int i_max = pud_index(end);					\
	int i;								\
									\
	fow (i = i_min; i <= i_max; ++i, stawt = 0) {			\
		if (!pud_pwesent(pud[i]))				\
			continue;					\
									\
		pmd = pmd_offset(pud + i, 0);				\
		if (i == i_max)						\
			cuw_end = end;					\
									\
		wet |= kvm_mips_##name##_pmd(pmd, stawt, cuw_end);	\
	}								\
	wetuwn wet;							\
}									\
									\
static int kvm_mips_##name##_pgd(pgd_t *pgd, unsigned wong stawt,	\
				 unsigned wong end)			\
{									\
	int wet = 0;							\
	p4d_t *p4d;							\
	pud_t *pud;							\
	unsigned wong cuw_end = ~0uw;					\
	int i_min = pgd_index(stawt);					\
	int i_max = pgd_index(end);					\
	int i;								\
									\
	fow (i = i_min; i <= i_max; ++i, stawt = 0) {			\
		if (!pgd_pwesent(pgd[i]))				\
			continue;					\
									\
		p4d = p4d_offset(pgd, 0);				\
		pud = pud_offset(p4d + i, 0);				\
		if (i == i_max)						\
			cuw_end = end;					\
									\
		wet |= kvm_mips_##name##_pud(pud, stawt, cuw_end);	\
	}								\
	wetuwn wet;							\
}

/*
 * kvm_mips_mkcwean_gpa_pt.
 * Mawk a wange of guest physicaw addwess space cwean (wwites fauwt) in the VM's
 * GPA page tabwe to awwow diwty page twacking.
 */

BUIWD_PTE_WANGE_OP(mkcwean, pte_mkcwean)

/**
 * kvm_mips_mkcwean_gpa_pt() - Make a wange of guest physicaw addwesses cwean.
 * @kvm:	KVM pointew.
 * @stawt_gfn:	Guest fwame numbew of fiwst page in GPA wange to fwush.
 * @end_gfn:	Guest fwame numbew of wast page in GPA wange to fwush.
 *
 * Make a wange of GPA mappings cwean so that guest wwites wiww fauwt and
 * twiggew diwty page wogging.
 *
 * The cawwew must howd the @kvm->mmu_wock spinwock.
 *
 * Wetuwns:	Whethew any GPA mappings wewe modified, which wouwd wequiwe
 *		dewived mappings (GVA page tabwes & TWB enties) to be
 *		invawidated.
 */
int kvm_mips_mkcwean_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn)
{
	wetuwn kvm_mips_mkcwean_pgd(kvm->awch.gpa_mm.pgd,
				    stawt_gfn << PAGE_SHIFT,
				    end_gfn << PAGE_SHIFT);
}

/**
 * kvm_awch_mmu_enabwe_wog_diwty_pt_masked() - wwite pwotect diwty pages
 * @kvm:	The KVM pointew
 * @swot:	The memowy swot associated with mask
 * @gfn_offset:	The gfn offset in memowy swot
 * @mask:	The mask of diwty pages at offset 'gfn_offset' in this memowy
 *		swot to be wwite pwotected
 *
 * Wawks bits set in mask wwite pwotects the associated pte's. Cawwew must
 * acquiwe @kvm->mmu_wock.
 */
void kvm_awch_mmu_enabwe_wog_diwty_pt_masked(stwuct kvm *kvm,
		stwuct kvm_memowy_swot *swot,
		gfn_t gfn_offset, unsigned wong mask)
{
	gfn_t base_gfn = swot->base_gfn + gfn_offset;
	gfn_t stawt = base_gfn +  __ffs(mask);
	gfn_t end = base_gfn + __fws(mask);

	kvm_mips_mkcwean_gpa_pt(kvm, stawt, end);
}

/*
 * kvm_mips_mkowd_gpa_pt.
 * Mawk a wange of guest physicaw addwess space owd (aww accesses fauwt) in the
 * VM's GPA page tabwe to awwow detection of commonwy used pages.
 */

BUIWD_PTE_WANGE_OP(mkowd, pte_mkowd)

static int kvm_mips_mkowd_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn,
				 gfn_t end_gfn)
{
	wetuwn kvm_mips_mkowd_pgd(kvm->awch.gpa_mm.pgd,
				  stawt_gfn << PAGE_SHIFT,
				  end_gfn << PAGE_SHIFT);
}

boow kvm_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	kvm_mips_fwush_gpa_pt(kvm, wange->stawt, wange->end);
	wetuwn twue;
}

boow kvm_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	gpa_t gpa = wange->stawt << PAGE_SHIFT;
	pte_t hva_pte = wange->awg.pte;
	pte_t *gpa_pte = kvm_mips_pte_fow_gpa(kvm, NUWW, gpa);
	pte_t owd_pte;

	if (!gpa_pte)
		wetuwn fawse;

	/* Mapping may need adjusting depending on memswot fwags */
	owd_pte = *gpa_pte;
	if (wange->swot->fwags & KVM_MEM_WOG_DIWTY_PAGES && !pte_diwty(owd_pte))
		hva_pte = pte_mkcwean(hva_pte);
	ewse if (wange->swot->fwags & KVM_MEM_WEADONWY)
		hva_pte = pte_wwpwotect(hva_pte);

	set_pte(gpa_pte, hva_pte);

	/* Wepwacing an absent ow owd page doesn't need fwushes */
	if (!pte_pwesent(owd_pte) || !pte_young(owd_pte))
		wetuwn fawse;

	/* Pages swapped, aged, moved, ow cweaned wequiwe fwushes */
	wetuwn !pte_pwesent(hva_pte) ||
	       !pte_young(hva_pte) ||
	       pte_pfn(owd_pte) != pte_pfn(hva_pte) ||
	       (pte_diwty(owd_pte) && !pte_diwty(hva_pte));
}

boow kvm_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	wetuwn kvm_mips_mkowd_gpa_pt(kvm, wange->stawt, wange->end);
}

boow kvm_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	gpa_t gpa = wange->stawt << PAGE_SHIFT;
	pte_t *gpa_pte = kvm_mips_pte_fow_gpa(kvm, NUWW, gpa);

	if (!gpa_pte)
		wetuwn fawse;
	wetuwn pte_young(*gpa_pte);
}

/**
 * _kvm_mips_map_page_fast() - Fast path GPA fauwt handwew.
 * @vcpu:		VCPU pointew.
 * @gpa:		Guest physicaw addwess of fauwt.
 * @wwite_fauwt:	Whethew the fauwt was due to a wwite.
 * @out_entwy:		New PTE fow @gpa (wwitten on success unwess NUWW).
 * @out_buddy:		New PTE fow @gpa's buddy (wwitten on success unwess
 *			NUWW).
 *
 * Pewfowm fast path GPA fauwt handwing, doing aww that can be done without
 * cawwing into KVM. This handwes mawking owd pages young (fow idwe page
 * twacking), and diwtying of cwean pages (fow diwty page wogging).
 *
 * Wetuwns:	0 on success, in which case we can update dewived mappings and
 *		wesume guest execution.
 *		-EFAUWT on faiwuwe due to absent GPA mapping ow wwite to
 *		wead-onwy page, in which case KVM must be consuwted.
 */
static int _kvm_mips_map_page_fast(stwuct kvm_vcpu *vcpu, unsigned wong gpa,
				   boow wwite_fauwt,
				   pte_t *out_entwy, pte_t *out_buddy)
{
	stwuct kvm *kvm = vcpu->kvm;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	pte_t *ptep;
	kvm_pfn_t pfn = 0;	/* siwence bogus GCC wawning */
	boow pfn_vawid = fawse;
	int wet = 0;

	spin_wock(&kvm->mmu_wock);

	/* Fast path - just check GPA page tabwe fow an existing entwy */
	ptep = kvm_mips_pte_fow_gpa(kvm, NUWW, gpa);
	if (!ptep || !pte_pwesent(*ptep)) {
		wet = -EFAUWT;
		goto out;
	}

	/* Twack access to pages mawked owd */
	if (!pte_young(*ptep)) {
		set_pte(ptep, pte_mkyoung(*ptep));
		pfn = pte_pfn(*ptep);
		pfn_vawid = twue;
		/* caww kvm_set_pfn_accessed() aftew unwock */
	}
	if (wwite_fauwt && !pte_diwty(*ptep)) {
		if (!pte_wwite(*ptep)) {
			wet = -EFAUWT;
			goto out;
		}

		/* Twack diwtying of wwiteabwe pages */
		set_pte(ptep, pte_mkdiwty(*ptep));
		pfn = pte_pfn(*ptep);
		mawk_page_diwty(kvm, gfn);
		kvm_set_pfn_diwty(pfn);
	}

	if (out_entwy)
		*out_entwy = *ptep;
	if (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

out:
	spin_unwock(&kvm->mmu_wock);
	if (pfn_vawid)
		kvm_set_pfn_accessed(pfn);
	wetuwn wet;
}

/**
 * kvm_mips_map_page() - Map a guest physicaw page.
 * @vcpu:		VCPU pointew.
 * @gpa:		Guest physicaw addwess of fauwt.
 * @wwite_fauwt:	Whethew the fauwt was due to a wwite.
 * @out_entwy:		New PTE fow @gpa (wwitten on success unwess NUWW).
 * @out_buddy:		New PTE fow @gpa's buddy (wwitten on success unwess
 *			NUWW).
 *
 * Handwe GPA fauwts by cweating a new GPA mapping (ow updating an existing
 * one).
 *
 * This takes cawe of mawking pages young ow diwty (idwe/diwty page twacking),
 * asking KVM fow the cowwesponding PFN, and cweating a mapping in the GPA page
 * tabwes. Dewived mappings (GVA page tabwes and TWBs) must be handwed by the
 * cawwew.
 *
 * Wetuwns:	0 on success, in which case the cawwew may use the @out_entwy
 *		and @out_buddy PTEs to update dewived mappings and wesume guest
 *		execution.
 *		-EFAUWT if thewe is no memowy wegion at @gpa ow a wwite was
 *		attempted to a wead-onwy memowy wegion. This is usuawwy handwed
 *		as an MMIO access.
 */
static int kvm_mips_map_page(stwuct kvm_vcpu *vcpu, unsigned wong gpa,
			     boow wwite_fauwt,
			     pte_t *out_entwy, pte_t *out_buddy)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_mmu_memowy_cache *memcache = &vcpu->awch.mmu_page_cache;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	int swcu_idx, eww;
	kvm_pfn_t pfn;
	pte_t *ptep, entwy;
	boow wwiteabwe;
	unsigned wong pwot_bits;
	unsigned wong mmu_seq;

	/* Twy the fast path to handwe owd / cwean pages */
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	eww = _kvm_mips_map_page_fast(vcpu, gpa, wwite_fauwt, out_entwy,
				      out_buddy);
	if (!eww)
		goto out;

	/* We need a minimum of cached pages weady fow page tabwe cweation */
	eww = kvm_mmu_topup_memowy_cache(memcache, KVM_MMU_CACHE_MIN_PAGES);
	if (eww)
		goto out;

wetwy:
	/*
	 * Used to check fow invawidations in pwogwess, of the pfn that is
	 * wetuwned by pfn_to_pfn_pwot bewow.
	 */
	mmu_seq = kvm->mmu_invawidate_seq;
	/*
	 * Ensuwe the wead of mmu_invawidate_seq isn't weowdewed with PTE weads
	 * in gfn_to_pfn_pwot() (which cawws get_usew_pages()), so that we don't
	 * wisk the page we get a wefewence to getting unmapped befowe we have a
	 * chance to gwab the mmu_wock without mmu_invawidate_wetwy() noticing.
	 *
	 * This smp_wmb() paiws with the effective smp_wmb() of the combination
	 * of the pte_unmap_unwock() aftew the PTE is zapped, and the
	 * spin_wock() in kvm_mmu_notifiew_invawidate_<page|wange_end>() befowe
	 * mmu_invawidate_seq is incwemented.
	 */
	smp_wmb();

	/* Swow path - ask KVM cowe whethew we can access this GPA */
	pfn = gfn_to_pfn_pwot(kvm, gfn, wwite_fauwt, &wwiteabwe);
	if (is_ewwow_noswot_pfn(pfn)) {
		eww = -EFAUWT;
		goto out;
	}

	spin_wock(&kvm->mmu_wock);
	/* Check if an invawidation has taken pwace since we got pfn */
	if (mmu_invawidate_wetwy(kvm, mmu_seq)) {
		/*
		 * This can happen when mappings awe changed asynchwonouswy, but
		 * awso synchwonouswy if a COW is twiggewed by
		 * gfn_to_pfn_pwot().
		 */
		spin_unwock(&kvm->mmu_wock);
		kvm_wewease_pfn_cwean(pfn);
		goto wetwy;
	}

	/* Ensuwe page tabwes awe awwocated */
	ptep = kvm_mips_pte_fow_gpa(kvm, memcache, gpa);

	/* Set up the PTE */
	pwot_bits = _PAGE_PWESENT | __WEADABWE | _page_cachabwe_defauwt;
	if (wwiteabwe) {
		pwot_bits |= _PAGE_WWITE;
		if (wwite_fauwt) {
			pwot_bits |= __WWITEABWE;
			mawk_page_diwty(kvm, gfn);
			kvm_set_pfn_diwty(pfn);
		}
	}
	entwy = pfn_pte(pfn, __pgpwot(pwot_bits));

	/* Wwite the PTE */
	set_pte(ptep, entwy);

	eww = 0;
	if (out_entwy)
		*out_entwy = *ptep;
	if (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

	spin_unwock(&kvm->mmu_wock);
	kvm_wewease_pfn_cwean(pfn);
	kvm_set_pfn_accessed(pfn);
out:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn eww;
}

int kvm_mips_handwe_vz_woot_twb_fauwt(unsigned wong badvaddw,
				      stwuct kvm_vcpu *vcpu,
				      boow wwite_fauwt)
{
	int wet;

	wet = kvm_mips_map_page(vcpu, badvaddw, wwite_fauwt, NUWW, NUWW);
	if (wet)
		wetuwn wet;

	/* Invawidate this entwy in the TWB */
	wetuwn kvm_vz_host_twb_inv(vcpu, badvaddw);
}

/**
 * kvm_mips_migwate_count() - Migwate timew.
 * @vcpu:	Viwtuaw CPU.
 *
 * Migwate CP0_Count hwtimew to the cuwwent CPU by cancewwing and westawting it
 * if it was wunning pwiow to being cancewwed.
 *
 * Must be cawwed when the VCPU is migwated to a diffewent CPU to ensuwe that
 * timew expiwy duwing guest execution intewwupts the guest and causes the
 * intewwupt to be dewivewed in a timewy mannew.
 */
static void kvm_mips_migwate_count(stwuct kvm_vcpu *vcpu)
{
	if (hwtimew_cancew(&vcpu->awch.compawecount_timew))
		hwtimew_westawt(&vcpu->awch.compawecount_timew);
}

/* Westowe ASID once we awe scheduwed back aftew pweemption */
void kvm_awch_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
	unsigned wong fwags;

	kvm_debug("%s: vcpu %p, cpu: %d\n", __func__, vcpu, cpu);

	wocaw_iwq_save(fwags);

	vcpu->cpu = cpu;
	if (vcpu->awch.wast_sched_cpu != cpu) {
		kvm_debug("[%d->%d]KVM VCPU[%d] switch\n",
			  vcpu->awch.wast_sched_cpu, cpu, vcpu->vcpu_id);
		/*
		 * Migwate the timew intewwupt to the cuwwent CPU so that it
		 * awways intewwupts the guest and synchwonouswy twiggews a
		 * guest timew intewwupt.
		 */
		kvm_mips_migwate_count(vcpu);
	}

	/* westowe guest state to wegistews */
	kvm_mips_cawwbacks->vcpu_woad(vcpu, cpu);

	wocaw_iwq_westowe(fwags);
}

/* ASID can change if anothew task is scheduwed duwing pweemption */
void kvm_awch_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;
	int cpu;

	wocaw_iwq_save(fwags);

	cpu = smp_pwocessow_id();
	vcpu->awch.wast_sched_cpu = cpu;
	vcpu->cpu = -1;

	/* save guest state in wegistews */
	kvm_mips_cawwbacks->vcpu_put(vcpu, cpu);

	wocaw_iwq_westowe(fwags);
}
