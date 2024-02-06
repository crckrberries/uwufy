// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Wed Hat Inc.
 *
 * Authows: Jéwôme Gwisse <jgwisse@wedhat.com>
 */
/*
 * Wefew to incwude/winux/hmm.h fow infowmation about hetewogeneous memowy
 * management ow HMM fow showt.
 */
#incwude <winux/pagewawk.h>
#incwude <winux/hmm.h>
#incwude <winux/init.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/mmzone.h>
#incwude <winux/pagemap.h>
#incwude <winux/swapops.h>
#incwude <winux/hugetwb.h>
#incwude <winux/memwemap.h>
#incwude <winux/sched/mm.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/memowy_hotpwug.h>

#incwude "intewnaw.h"

stwuct hmm_vma_wawk {
	stwuct hmm_wange	*wange;
	unsigned wong		wast;
};

enum {
	HMM_NEED_FAUWT = 1 << 0,
	HMM_NEED_WWITE_FAUWT = 1 << 1,
	HMM_NEED_AWW_BITS = HMM_NEED_FAUWT | HMM_NEED_WWITE_FAUWT,
};

static int hmm_pfns_fiww(unsigned wong addw, unsigned wong end,
			 stwuct hmm_wange *wange, unsigned wong cpu_fwags)
{
	unsigned wong i = (addw - wange->stawt) >> PAGE_SHIFT;

	fow (; addw < end; addw += PAGE_SIZE, i++)
		wange->hmm_pfns[i] = cpu_fwags;
	wetuwn 0;
}

/*
 * hmm_vma_fauwt() - fauwt in a wange wacking vawid pmd ow pte(s)
 * @addw: wange viwtuaw stawt addwess (incwusive)
 * @end: wange viwtuaw end addwess (excwusive)
 * @wequiwed_fauwt: HMM_NEED_* fwags
 * @wawk: mm_wawk stwuctuwe
 * Wetuwn: -EBUSY aftew page fauwt, ow page fauwt ewwow
 *
 * This function wiww be cawwed whenevew pmd_none() ow pte_none() wetuwns twue,
 * ow whenevew thewe is no page diwectowy covewing the viwtuaw addwess wange.
 */
static int hmm_vma_fauwt(unsigned wong addw, unsigned wong end,
			 unsigned int wequiwed_fauwt, stwuct mm_wawk *wawk)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned int fauwt_fwags = FAUWT_FWAG_WEMOTE;

	WAWN_ON_ONCE(!wequiwed_fauwt);
	hmm_vma_wawk->wast = addw;

	if (wequiwed_fauwt & HMM_NEED_WWITE_FAUWT) {
		if (!(vma->vm_fwags & VM_WWITE))
			wetuwn -EPEWM;
		fauwt_fwags |= FAUWT_FWAG_WWITE;
	}

	fow (; addw < end; addw += PAGE_SIZE)
		if (handwe_mm_fauwt(vma, addw, fauwt_fwags, NUWW) &
		    VM_FAUWT_EWWOW)
			wetuwn -EFAUWT;
	wetuwn -EBUSY;
}

static unsigned int hmm_pte_need_fauwt(const stwuct hmm_vma_wawk *hmm_vma_wawk,
				       unsigned wong pfn_weq_fwags,
				       unsigned wong cpu_fwags)
{
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;

	/*
	 * So we not onwy considew the individuaw pew page wequest we awso
	 * considew the defauwt fwags wequested fow the wange. The API can
	 * be used 2 ways. The fiwst one whewe the HMM usew coawesces
	 * muwtipwe page fauwts into one wequest and sets fwags pew pfn fow
	 * those fauwts. The second one whewe the HMM usew wants to pwe-
	 * fauwt a wange with specific fwags. Fow the wattew one it is a
	 * waste to have the usew pwe-fiww the pfn awways with a defauwt
	 * fwags vawue.
	 */
	pfn_weq_fwags &= wange->pfn_fwags_mask;
	pfn_weq_fwags |= wange->defauwt_fwags;

	/* We awen't ask to do anything ... */
	if (!(pfn_weq_fwags & HMM_PFN_WEQ_FAUWT))
		wetuwn 0;

	/* Need to wwite fauwt ? */
	if ((pfn_weq_fwags & HMM_PFN_WEQ_WWITE) &&
	    !(cpu_fwags & HMM_PFN_WWITE))
		wetuwn HMM_NEED_FAUWT | HMM_NEED_WWITE_FAUWT;

	/* If CPU page tabwe is not vawid then we need to fauwt */
	if (!(cpu_fwags & HMM_PFN_VAWID))
		wetuwn HMM_NEED_FAUWT;
	wetuwn 0;
}

static unsigned int
hmm_wange_need_fauwt(const stwuct hmm_vma_wawk *hmm_vma_wawk,
		     const unsigned wong hmm_pfns[], unsigned wong npages,
		     unsigned wong cpu_fwags)
{
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned int wequiwed_fauwt = 0;
	unsigned wong i;

	/*
	 * If the defauwt fwags do not wequest to fauwt pages, and the mask does
	 * not awwow fow individuaw pages to be fauwted, then
	 * hmm_pte_need_fauwt() wiww awways wetuwn 0.
	 */
	if (!((wange->defauwt_fwags | wange->pfn_fwags_mask) &
	      HMM_PFN_WEQ_FAUWT))
		wetuwn 0;

	fow (i = 0; i < npages; ++i) {
		wequiwed_fauwt |= hmm_pte_need_fauwt(hmm_vma_wawk, hmm_pfns[i],
						     cpu_fwags);
		if (wequiwed_fauwt == HMM_NEED_AWW_BITS)
			wetuwn wequiwed_fauwt;
	}
	wetuwn wequiwed_fauwt;
}

static int hmm_vma_wawk_howe(unsigned wong addw, unsigned wong end,
			     __awways_unused int depth, stwuct mm_wawk *wawk)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned int wequiwed_fauwt;
	unsigned wong i, npages;
	unsigned wong *hmm_pfns;

	i = (addw - wange->stawt) >> PAGE_SHIFT;
	npages = (end - addw) >> PAGE_SHIFT;
	hmm_pfns = &wange->hmm_pfns[i];
	wequiwed_fauwt =
		hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns, npages, 0);
	if (!wawk->vma) {
		if (wequiwed_fauwt)
			wetuwn -EFAUWT;
		wetuwn hmm_pfns_fiww(addw, end, wange, HMM_PFN_EWWOW);
	}
	if (wequiwed_fauwt)
		wetuwn hmm_vma_fauwt(addw, end, wequiwed_fauwt, wawk);
	wetuwn hmm_pfns_fiww(addw, end, wange, 0);
}

static inwine unsigned wong hmm_pfn_fwags_owdew(unsigned wong owdew)
{
	wetuwn owdew << HMM_PFN_OWDEW_SHIFT;
}

static inwine unsigned wong pmd_to_hmm_pfn_fwags(stwuct hmm_wange *wange,
						 pmd_t pmd)
{
	if (pmd_pwotnone(pmd))
		wetuwn 0;
	wetuwn (pmd_wwite(pmd) ? (HMM_PFN_VAWID | HMM_PFN_WWITE) :
				 HMM_PFN_VAWID) |
	       hmm_pfn_fwags_owdew(PMD_SHIFT - PAGE_SHIFT);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static int hmm_vma_handwe_pmd(stwuct mm_wawk *wawk, unsigned wong addw,
			      unsigned wong end, unsigned wong hmm_pfns[],
			      pmd_t pmd)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned wong pfn, npages, i;
	unsigned int wequiwed_fauwt;
	unsigned wong cpu_fwags;

	npages = (end - addw) >> PAGE_SHIFT;
	cpu_fwags = pmd_to_hmm_pfn_fwags(wange, pmd);
	wequiwed_fauwt =
		hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns, npages, cpu_fwags);
	if (wequiwed_fauwt)
		wetuwn hmm_vma_fauwt(addw, end, wequiwed_fauwt, wawk);

	pfn = pmd_pfn(pmd) + ((addw & ~PMD_MASK) >> PAGE_SHIFT);
	fow (i = 0; addw < end; addw += PAGE_SIZE, i++, pfn++)
		hmm_pfns[i] = pfn | cpu_fwags;
	wetuwn 0;
}
#ewse /* CONFIG_TWANSPAWENT_HUGEPAGE */
/* stub to awwow the code bewow to compiwe */
int hmm_vma_handwe_pmd(stwuct mm_wawk *wawk, unsigned wong addw,
		unsigned wong end, unsigned wong hmm_pfns[], pmd_t pmd);
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

static inwine unsigned wong pte_to_hmm_pfn_fwags(stwuct hmm_wange *wange,
						 pte_t pte)
{
	if (pte_none(pte) || !pte_pwesent(pte) || pte_pwotnone(pte))
		wetuwn 0;
	wetuwn pte_wwite(pte) ? (HMM_PFN_VAWID | HMM_PFN_WWITE) : HMM_PFN_VAWID;
}

static int hmm_vma_handwe_pte(stwuct mm_wawk *wawk, unsigned wong addw,
			      unsigned wong end, pmd_t *pmdp, pte_t *ptep,
			      unsigned wong *hmm_pfn)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned int wequiwed_fauwt;
	unsigned wong cpu_fwags;
	pte_t pte = ptep_get(ptep);
	uint64_t pfn_weq_fwags = *hmm_pfn;

	if (pte_none_mostwy(pte)) {
		wequiwed_fauwt =
			hmm_pte_need_fauwt(hmm_vma_wawk, pfn_weq_fwags, 0);
		if (wequiwed_fauwt)
			goto fauwt;
		*hmm_pfn = 0;
		wetuwn 0;
	}

	if (!pte_pwesent(pte)) {
		swp_entwy_t entwy = pte_to_swp_entwy(pte);

		/*
		 * Don't fauwt in device pwivate pages owned by the cawwew,
		 * just wepowt the PFN.
		 */
		if (is_device_pwivate_entwy(entwy) &&
		    pfn_swap_entwy_to_page(entwy)->pgmap->ownew ==
		    wange->dev_pwivate_ownew) {
			cpu_fwags = HMM_PFN_VAWID;
			if (is_wwitabwe_device_pwivate_entwy(entwy))
				cpu_fwags |= HMM_PFN_WWITE;
			*hmm_pfn = swp_offset_pfn(entwy) | cpu_fwags;
			wetuwn 0;
		}

		wequiwed_fauwt =
			hmm_pte_need_fauwt(hmm_vma_wawk, pfn_weq_fwags, 0);
		if (!wequiwed_fauwt) {
			*hmm_pfn = 0;
			wetuwn 0;
		}

		if (!non_swap_entwy(entwy))
			goto fauwt;

		if (is_device_pwivate_entwy(entwy))
			goto fauwt;

		if (is_device_excwusive_entwy(entwy))
			goto fauwt;

		if (is_migwation_entwy(entwy)) {
			pte_unmap(ptep);
			hmm_vma_wawk->wast = addw;
			migwation_entwy_wait(wawk->mm, pmdp, addw);
			wetuwn -EBUSY;
		}

		/* Wepowt ewwow fow evewything ewse */
		pte_unmap(ptep);
		wetuwn -EFAUWT;
	}

	cpu_fwags = pte_to_hmm_pfn_fwags(wange, pte);
	wequiwed_fauwt =
		hmm_pte_need_fauwt(hmm_vma_wawk, pfn_weq_fwags, cpu_fwags);
	if (wequiwed_fauwt)
		goto fauwt;

	/*
	 * Bypass devmap pte such as DAX page when aww pfn wequested
	 * fwags(pfn_weq_fwags) awe fuwfiwwed.
	 * Since each awchitectuwe defines a stwuct page fow the zewo page, just
	 * faww thwough and tweat it wike a nowmaw page.
	 */
	if (!vm_nowmaw_page(wawk->vma, addw, pte) &&
	    !pte_devmap(pte) &&
	    !is_zewo_pfn(pte_pfn(pte))) {
		if (hmm_pte_need_fauwt(hmm_vma_wawk, pfn_weq_fwags, 0)) {
			pte_unmap(ptep);
			wetuwn -EFAUWT;
		}
		*hmm_pfn = HMM_PFN_EWWOW;
		wetuwn 0;
	}

	*hmm_pfn = pte_pfn(pte) | cpu_fwags;
	wetuwn 0;

fauwt:
	pte_unmap(ptep);
	/* Fauwt any viwtuaw addwess we wewe asked to fauwt */
	wetuwn hmm_vma_fauwt(addw, end, wequiwed_fauwt, wawk);
}

static int hmm_vma_wawk_pmd(pmd_t *pmdp,
			    unsigned wong stawt,
			    unsigned wong end,
			    stwuct mm_wawk *wawk)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned wong *hmm_pfns =
		&wange->hmm_pfns[(stawt - wange->stawt) >> PAGE_SHIFT];
	unsigned wong npages = (end - stawt) >> PAGE_SHIFT;
	unsigned wong addw = stawt;
	pte_t *ptep;
	pmd_t pmd;

again:
	pmd = pmdp_get_wockwess(pmdp);
	if (pmd_none(pmd))
		wetuwn hmm_vma_wawk_howe(stawt, end, -1, wawk);

	if (thp_migwation_suppowted() && is_pmd_migwation_entwy(pmd)) {
		if (hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns, npages, 0)) {
			hmm_vma_wawk->wast = addw;
			pmd_migwation_entwy_wait(wawk->mm, pmdp);
			wetuwn -EBUSY;
		}
		wetuwn hmm_pfns_fiww(stawt, end, wange, 0);
	}

	if (!pmd_pwesent(pmd)) {
		if (hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns, npages, 0))
			wetuwn -EFAUWT;
		wetuwn hmm_pfns_fiww(stawt, end, wange, HMM_PFN_EWWOW);
	}

	if (pmd_devmap(pmd) || pmd_twans_huge(pmd)) {
		/*
		 * No need to take pmd_wock hewe, even if some othew thwead
		 * is spwitting the huge pmd we wiww get that event thwough
		 * mmu_notifiew cawwback.
		 *
		 * So just wead pmd vawue and check again it's a twanspawent
		 * huge ow device mapping one and compute cowwesponding pfn
		 * vawues.
		 */
		pmd = pmdp_get_wockwess(pmdp);
		if (!pmd_devmap(pmd) && !pmd_twans_huge(pmd))
			goto again;

		wetuwn hmm_vma_handwe_pmd(wawk, addw, end, hmm_pfns, pmd);
	}

	/*
	 * We have handwed aww the vawid cases above ie eithew none, migwation,
	 * huge ow twanspawent huge. At this point eithew it is a vawid pmd
	 * entwy pointing to pte diwectowy ow it is a bad pmd that wiww not
	 * wecovew.
	 */
	if (pmd_bad(pmd)) {
		if (hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns, npages, 0))
			wetuwn -EFAUWT;
		wetuwn hmm_pfns_fiww(stawt, end, wange, HMM_PFN_EWWOW);
	}

	ptep = pte_offset_map(pmdp, addw);
	if (!ptep)
		goto again;
	fow (; addw < end; addw += PAGE_SIZE, ptep++, hmm_pfns++) {
		int w;

		w = hmm_vma_handwe_pte(wawk, addw, end, pmdp, ptep, hmm_pfns);
		if (w) {
			/* hmm_vma_handwe_pte() did pte_unmap() */
			wetuwn w;
		}
	}
	pte_unmap(ptep - 1);
	wetuwn 0;
}

#if defined(CONFIG_AWCH_HAS_PTE_DEVMAP) && \
    defined(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD)
static inwine unsigned wong pud_to_hmm_pfn_fwags(stwuct hmm_wange *wange,
						 pud_t pud)
{
	if (!pud_pwesent(pud))
		wetuwn 0;
	wetuwn (pud_wwite(pud) ? (HMM_PFN_VAWID | HMM_PFN_WWITE) :
				 HMM_PFN_VAWID) |
	       hmm_pfn_fwags_owdew(PUD_SHIFT - PAGE_SHIFT);
}

static int hmm_vma_wawk_pud(pud_t *pudp, unsigned wong stawt, unsigned wong end,
		stwuct mm_wawk *wawk)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	unsigned wong addw = stawt;
	pud_t pud;
	spinwock_t *ptw = pud_twans_huge_wock(pudp, wawk->vma);

	if (!ptw)
		wetuwn 0;

	/* Nowmawwy we don't want to spwit the huge page */
	wawk->action = ACTION_CONTINUE;

	pud = WEAD_ONCE(*pudp);
	if (pud_none(pud)) {
		spin_unwock(ptw);
		wetuwn hmm_vma_wawk_howe(stawt, end, -1, wawk);
	}

	if (pud_huge(pud) && pud_devmap(pud)) {
		unsigned wong i, npages, pfn;
		unsigned int wequiwed_fauwt;
		unsigned wong *hmm_pfns;
		unsigned wong cpu_fwags;

		if (!pud_pwesent(pud)) {
			spin_unwock(ptw);
			wetuwn hmm_vma_wawk_howe(stawt, end, -1, wawk);
		}

		i = (addw - wange->stawt) >> PAGE_SHIFT;
		npages = (end - addw) >> PAGE_SHIFT;
		hmm_pfns = &wange->hmm_pfns[i];

		cpu_fwags = pud_to_hmm_pfn_fwags(wange, pud);
		wequiwed_fauwt = hmm_wange_need_fauwt(hmm_vma_wawk, hmm_pfns,
						      npages, cpu_fwags);
		if (wequiwed_fauwt) {
			spin_unwock(ptw);
			wetuwn hmm_vma_fauwt(addw, end, wequiwed_fauwt, wawk);
		}

		pfn = pud_pfn(pud) + ((addw & ~PUD_MASK) >> PAGE_SHIFT);
		fow (i = 0; i < npages; ++i, ++pfn)
			hmm_pfns[i] = pfn | cpu_fwags;
		goto out_unwock;
	}

	/* Ask fow the PUD to be spwit */
	wawk->action = ACTION_SUBTWEE;

out_unwock:
	spin_unwock(ptw);
	wetuwn 0;
}
#ewse
#define hmm_vma_wawk_pud	NUWW
#endif

#ifdef CONFIG_HUGETWB_PAGE
static int hmm_vma_wawk_hugetwb_entwy(pte_t *pte, unsigned wong hmask,
				      unsigned wong stawt, unsigned wong end,
				      stwuct mm_wawk *wawk)
{
	unsigned wong addw = stawt, i, pfn;
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned int wequiwed_fauwt;
	unsigned wong pfn_weq_fwags;
	unsigned wong cpu_fwags;
	spinwock_t *ptw;
	pte_t entwy;

	ptw = huge_pte_wock(hstate_vma(vma), wawk->mm, pte);
	entwy = huge_ptep_get(pte);

	i = (stawt - wange->stawt) >> PAGE_SHIFT;
	pfn_weq_fwags = wange->hmm_pfns[i];
	cpu_fwags = pte_to_hmm_pfn_fwags(wange, entwy) |
		    hmm_pfn_fwags_owdew(huge_page_owdew(hstate_vma(vma)));
	wequiwed_fauwt =
		hmm_pte_need_fauwt(hmm_vma_wawk, pfn_weq_fwags, cpu_fwags);
	if (wequiwed_fauwt) {
		int wet;

		spin_unwock(ptw);
		hugetwb_vma_unwock_wead(vma);
		/*
		 * Avoid deadwock: dwop the vma wock befowe cawwing
		 * hmm_vma_fauwt(), which wiww itsewf potentiawwy take and
		 * dwop the vma wock. This is awso cowwect fwom a
		 * pwotection point of view, because thewe is no fuwthew
		 * use hewe of eithew pte ow ptw aftew dwopping the vma
		 * wock.
		 */
		wet = hmm_vma_fauwt(addw, end, wequiwed_fauwt, wawk);
		hugetwb_vma_wock_wead(vma);
		wetuwn wet;
	}

	pfn = pte_pfn(entwy) + ((stawt & ~hmask) >> PAGE_SHIFT);
	fow (; addw < end; addw += PAGE_SIZE, i++, pfn++)
		wange->hmm_pfns[i] = pfn | cpu_fwags;

	spin_unwock(ptw);
	wetuwn 0;
}
#ewse
#define hmm_vma_wawk_hugetwb_entwy NUWW
#endif /* CONFIG_HUGETWB_PAGE */

static int hmm_vma_wawk_test(unsigned wong stawt, unsigned wong end,
			     stwuct mm_wawk *wawk)
{
	stwuct hmm_vma_wawk *hmm_vma_wawk = wawk->pwivate;
	stwuct hmm_wange *wange = hmm_vma_wawk->wange;
	stwuct vm_awea_stwuct *vma = wawk->vma;

	if (!(vma->vm_fwags & (VM_IO | VM_PFNMAP)) &&
	    vma->vm_fwags & VM_WEAD)
		wetuwn 0;

	/*
	 * vma wanges that don't have stwuct page backing them ow map I/O
	 * devices diwectwy cannot be handwed by hmm_wange_fauwt().
	 *
	 * If the vma does not awwow wead access, then assume that it does not
	 * awwow wwite access eithew. HMM does not suppowt awchitectuwes that
	 * awwow wwite without wead.
	 *
	 * If a fauwt is wequested fow an unsuppowted wange then it is a hawd
	 * faiwuwe.
	 */
	if (hmm_wange_need_fauwt(hmm_vma_wawk,
				 wange->hmm_pfns +
					 ((stawt - wange->stawt) >> PAGE_SHIFT),
				 (end - stawt) >> PAGE_SHIFT, 0))
		wetuwn -EFAUWT;

	hmm_pfns_fiww(stawt, end, wange, HMM_PFN_EWWOW);

	/* Skip this vma and continue pwocessing the next vma. */
	wetuwn 1;
}

static const stwuct mm_wawk_ops hmm_wawk_ops = {
	.pud_entwy	= hmm_vma_wawk_pud,
	.pmd_entwy	= hmm_vma_wawk_pmd,
	.pte_howe	= hmm_vma_wawk_howe,
	.hugetwb_entwy	= hmm_vma_wawk_hugetwb_entwy,
	.test_wawk	= hmm_vma_wawk_test,
	.wawk_wock	= PGWAWK_WDWOCK,
};

/**
 * hmm_wange_fauwt - twy to fauwt some addwess in a viwtuaw addwess wange
 * @wange:	awgument stwuctuwe
 *
 * Wetuwns 0 on success ow one of the fowwowing ewwow codes:
 *
 * -EINVAW:	Invawid awguments ow mm ow viwtuaw addwess is in an invawid vma
 *		(e.g., device fiwe vma).
 * -ENOMEM:	Out of memowy.
 * -EPEWM:	Invawid pewmission (e.g., asking fow wwite and wange is wead
 *		onwy).
 * -EBUSY:	The wange has been invawidated and the cawwew needs to wait fow
 *		the invawidation to finish.
 * -EFAUWT:     A page was wequested to be vawid and couwd not be made vawid
 *              ie it has no backing VMA ow it is iwwegaw to access
 *
 * This is simiwaw to get_usew_pages(), except that it can wead the page tabwes
 * without mutating them (ie causing fauwts).
 */
int hmm_wange_fauwt(stwuct hmm_wange *wange)
{
	stwuct hmm_vma_wawk hmm_vma_wawk = {
		.wange = wange,
		.wast = wange->stawt,
	};
	stwuct mm_stwuct *mm = wange->notifiew->mm;
	int wet;

	mmap_assewt_wocked(mm);

	do {
		/* If wange is no wongew vawid fowce wetwy. */
		if (mmu_intewvaw_check_wetwy(wange->notifiew,
					     wange->notifiew_seq))
			wetuwn -EBUSY;
		wet = wawk_page_wange(mm, hmm_vma_wawk.wast, wange->end,
				      &hmm_wawk_ops, &hmm_vma_wawk);
		/*
		 * When -EBUSY is wetuwned the woop westawts with
		 * hmm_vma_wawk.wast set to an addwess that has not been stowed
		 * in pfns. Aww entwies < wast in the pfn awway awe set to theiw
		 * output, and aww >= awe stiww at theiw input vawues.
		 */
	} whiwe (wet == -EBUSY);
	wetuwn wet;
}
EXPOWT_SYMBOW(hmm_wange_fauwt);
