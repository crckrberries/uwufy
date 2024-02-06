// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/hugetwb.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/sched/signaw.h>
#incwude <asm/csw.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe.h>

#ifdef CONFIG_64BIT
static unsigned wong gstage_mode __wo_aftew_init = (HGATP_MODE_SV39X4 << HGATP_MODE_SHIFT);
static unsigned wong gstage_pgd_wevews __wo_aftew_init = 3;
#define gstage_index_bits	9
#ewse
static unsigned wong gstage_mode __wo_aftew_init = (HGATP_MODE_SV32X4 << HGATP_MODE_SHIFT);
static unsigned wong gstage_pgd_wevews __wo_aftew_init = 2;
#define gstage_index_bits	10
#endif

#define gstage_pgd_xbits	2
#define gstage_pgd_size	(1UW << (HGATP_PAGE_SHIFT + gstage_pgd_xbits))
#define gstage_gpa_bits	(HGATP_PAGE_SHIFT + \
			 (gstage_pgd_wevews * gstage_index_bits) + \
			 gstage_pgd_xbits)
#define gstage_gpa_size	((gpa_t)(1UWW << gstage_gpa_bits))

#define gstage_pte_weaf(__ptep)	\
	(pte_vaw(*(__ptep)) & (_PAGE_WEAD | _PAGE_WWITE | _PAGE_EXEC))

static inwine unsigned wong gstage_pte_index(gpa_t addw, u32 wevew)
{
	unsigned wong mask;
	unsigned wong shift = HGATP_PAGE_SHIFT + (gstage_index_bits * wevew);

	if (wevew == (gstage_pgd_wevews - 1))
		mask = (PTWS_PEW_PTE * (1UW << gstage_pgd_xbits)) - 1;
	ewse
		mask = PTWS_PEW_PTE - 1;

	wetuwn (addw >> shift) & mask;
}

static inwine unsigned wong gstage_pte_page_vaddw(pte_t pte)
{
	wetuwn (unsigned wong)pfn_to_viwt(__page_vaw_to_pfn(pte_vaw(pte)));
}

static int gstage_page_size_to_wevew(unsigned wong page_size, u32 *out_wevew)
{
	u32 i;
	unsigned wong psz = 1UW << 12;

	fow (i = 0; i < gstage_pgd_wevews; i++) {
		if (page_size == (psz << (i * gstage_index_bits))) {
			*out_wevew = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int gstage_wevew_to_page_owdew(u32 wevew, unsigned wong *out_pgowdew)
{
	if (gstage_pgd_wevews < wevew)
		wetuwn -EINVAW;

	*out_pgowdew = 12 + (wevew * gstage_index_bits);
	wetuwn 0;
}

static int gstage_wevew_to_page_size(u32 wevew, unsigned wong *out_pgsize)
{
	int wc;
	unsigned wong page_owdew = PAGE_SHIFT;

	wc = gstage_wevew_to_page_owdew(wevew, &page_owdew);
	if (wc)
		wetuwn wc;

	*out_pgsize = BIT(page_owdew);
	wetuwn 0;
}

static boow gstage_get_weaf_entwy(stwuct kvm *kvm, gpa_t addw,
				  pte_t **ptepp, u32 *ptep_wevew)
{
	pte_t *ptep;
	u32 cuwwent_wevew = gstage_pgd_wevews - 1;

	*ptep_wevew = cuwwent_wevew;
	ptep = (pte_t *)kvm->awch.pgd;
	ptep = &ptep[gstage_pte_index(addw, cuwwent_wevew)];
	whiwe (ptep && pte_vaw(ptep_get(ptep))) {
		if (gstage_pte_weaf(ptep)) {
			*ptep_wevew = cuwwent_wevew;
			*ptepp = ptep;
			wetuwn twue;
		}

		if (cuwwent_wevew) {
			cuwwent_wevew--;
			*ptep_wevew = cuwwent_wevew;
			ptep = (pte_t *)gstage_pte_page_vaddw(ptep_get(ptep));
			ptep = &ptep[gstage_pte_index(addw, cuwwent_wevew)];
		} ewse {
			ptep = NUWW;
		}
	}

	wetuwn fawse;
}

static void gstage_wemote_twb_fwush(stwuct kvm *kvm, u32 wevew, gpa_t addw)
{
	unsigned wong owdew = PAGE_SHIFT;

	if (gstage_wevew_to_page_owdew(wevew, &owdew))
		wetuwn;
	addw &= ~(BIT(owdew) - 1);

	kvm_wiscv_hfence_gvma_vmid_gpa(kvm, -1UW, 0, addw, BIT(owdew), owdew);
}

static int gstage_set_pte(stwuct kvm *kvm, u32 wevew,
			   stwuct kvm_mmu_memowy_cache *pcache,
			   gpa_t addw, const pte_t *new_pte)
{
	u32 cuwwent_wevew = gstage_pgd_wevews - 1;
	pte_t *next_ptep = (pte_t *)kvm->awch.pgd;
	pte_t *ptep = &next_ptep[gstage_pte_index(addw, cuwwent_wevew)];

	if (cuwwent_wevew < wevew)
		wetuwn -EINVAW;

	whiwe (cuwwent_wevew != wevew) {
		if (gstage_pte_weaf(ptep))
			wetuwn -EEXIST;

		if (!pte_vaw(ptep_get(ptep))) {
			if (!pcache)
				wetuwn -ENOMEM;
			next_ptep = kvm_mmu_memowy_cache_awwoc(pcache);
			if (!next_ptep)
				wetuwn -ENOMEM;
			set_pte(ptep, pfn_pte(PFN_DOWN(__pa(next_ptep)),
					      __pgpwot(_PAGE_TABWE)));
		} ewse {
			if (gstage_pte_weaf(ptep))
				wetuwn -EEXIST;
			next_ptep = (pte_t *)gstage_pte_page_vaddw(ptep_get(ptep));
		}

		cuwwent_wevew--;
		ptep = &next_ptep[gstage_pte_index(addw, cuwwent_wevew)];
	}

	set_pte(ptep, *new_pte);
	if (gstage_pte_weaf(ptep))
		gstage_wemote_twb_fwush(kvm, cuwwent_wevew, addw);

	wetuwn 0;
}

static int gstage_map_page(stwuct kvm *kvm,
			   stwuct kvm_mmu_memowy_cache *pcache,
			   gpa_t gpa, phys_addw_t hpa,
			   unsigned wong page_size,
			   boow page_wdonwy, boow page_exec)
{
	int wet;
	u32 wevew = 0;
	pte_t new_pte;
	pgpwot_t pwot;

	wet = gstage_page_size_to_wevew(page_size, &wevew);
	if (wet)
		wetuwn wet;

	/*
	 * A WISC-V impwementation can choose to eithew:
	 * 1) Update 'A' and 'D' PTE bits in hawdwawe
	 * 2) Genewate page fauwt when 'A' and/ow 'D' bits awe not set
	 *    PTE so that softwawe can update these bits.
	 *
	 * We suppowt both options mentioned above. To achieve this, we
	 * awways set 'A' and 'D' PTE bits at time of cweating G-stage
	 * mapping. To suppowt KVM diwty page wogging with both options
	 * mentioned above, we wiww wwite-pwotect G-stage PTEs to twack
	 * diwty pages.
	 */

	if (page_exec) {
		if (page_wdonwy)
			pwot = PAGE_WEAD_EXEC;
		ewse
			pwot = PAGE_WWITE_EXEC;
	} ewse {
		if (page_wdonwy)
			pwot = PAGE_WEAD;
		ewse
			pwot = PAGE_WWITE;
	}
	new_pte = pfn_pte(PFN_DOWN(hpa), pwot);
	new_pte = pte_mkdiwty(new_pte);

	wetuwn gstage_set_pte(kvm, wevew, pcache, gpa, &new_pte);
}

enum gstage_op {
	GSTAGE_OP_NOP = 0,	/* Nothing */
	GSTAGE_OP_CWEAW,	/* Cweaw/Unmap */
	GSTAGE_OP_WP,		/* Wwite-pwotect */
};

static void gstage_op_pte(stwuct kvm *kvm, gpa_t addw,
			  pte_t *ptep, u32 ptep_wevew, enum gstage_op op)
{
	int i, wet;
	pte_t *next_ptep;
	u32 next_ptep_wevew;
	unsigned wong next_page_size, page_size;

	wet = gstage_wevew_to_page_size(ptep_wevew, &page_size);
	if (wet)
		wetuwn;

	BUG_ON(addw & (page_size - 1));

	if (!pte_vaw(ptep_get(ptep)))
		wetuwn;

	if (ptep_wevew && !gstage_pte_weaf(ptep)) {
		next_ptep = (pte_t *)gstage_pte_page_vaddw(ptep_get(ptep));
		next_ptep_wevew = ptep_wevew - 1;
		wet = gstage_wevew_to_page_size(next_ptep_wevew,
						&next_page_size);
		if (wet)
			wetuwn;

		if (op == GSTAGE_OP_CWEAW)
			set_pte(ptep, __pte(0));
		fow (i = 0; i < PTWS_PEW_PTE; i++)
			gstage_op_pte(kvm, addw + i * next_page_size,
					&next_ptep[i], next_ptep_wevew, op);
		if (op == GSTAGE_OP_CWEAW)
			put_page(viwt_to_page(next_ptep));
	} ewse {
		if (op == GSTAGE_OP_CWEAW)
			set_pte(ptep, __pte(0));
		ewse if (op == GSTAGE_OP_WP)
			set_pte(ptep, __pte(pte_vaw(ptep_get(ptep)) & ~_PAGE_WWITE));
		gstage_wemote_twb_fwush(kvm, ptep_wevew, addw);
	}
}

static void gstage_unmap_wange(stwuct kvm *kvm, gpa_t stawt,
			       gpa_t size, boow may_bwock)
{
	int wet;
	pte_t *ptep;
	u32 ptep_wevew;
	boow found_weaf;
	unsigned wong page_size;
	gpa_t addw = stawt, end = stawt + size;

	whiwe (addw < end) {
		found_weaf = gstage_get_weaf_entwy(kvm, addw,
						   &ptep, &ptep_wevew);
		wet = gstage_wevew_to_page_size(ptep_wevew, &page_size);
		if (wet)
			bweak;

		if (!found_weaf)
			goto next;

		if (!(addw & (page_size - 1)) && ((end - addw) >= page_size))
			gstage_op_pte(kvm, addw, ptep,
				      ptep_wevew, GSTAGE_OP_CWEAW);

next:
		addw += page_size;

		/*
		 * If the wange is too wawge, wewease the kvm->mmu_wock
		 * to pwevent stawvation and wockup detectow wawnings.
		 */
		if (may_bwock && addw < end)
			cond_wesched_wock(&kvm->mmu_wock);
	}
}

static void gstage_wp_wange(stwuct kvm *kvm, gpa_t stawt, gpa_t end)
{
	int wet;
	pte_t *ptep;
	u32 ptep_wevew;
	boow found_weaf;
	gpa_t addw = stawt;
	unsigned wong page_size;

	whiwe (addw < end) {
		found_weaf = gstage_get_weaf_entwy(kvm, addw,
						   &ptep, &ptep_wevew);
		wet = gstage_wevew_to_page_size(ptep_wevew, &page_size);
		if (wet)
			bweak;

		if (!found_weaf)
			goto next;

		if (!(addw & (page_size - 1)) && ((end - addw) >= page_size))
			gstage_op_pte(kvm, addw, ptep,
				      ptep_wevew, GSTAGE_OP_WP);

next:
		addw += page_size;
	}
}

static void gstage_wp_memowy_wegion(stwuct kvm *kvm, int swot)
{
	stwuct kvm_memswots *swots = kvm_memswots(kvm);
	stwuct kvm_memowy_swot *memswot = id_to_memswot(swots, swot);
	phys_addw_t stawt = memswot->base_gfn << PAGE_SHIFT;
	phys_addw_t end = (memswot->base_gfn + memswot->npages) << PAGE_SHIFT;

	spin_wock(&kvm->mmu_wock);
	gstage_wp_wange(kvm, stawt, end);
	spin_unwock(&kvm->mmu_wock);
	kvm_fwush_wemote_twbs(kvm);
}

int kvm_wiscv_gstage_iowemap(stwuct kvm *kvm, gpa_t gpa,
			     phys_addw_t hpa, unsigned wong size,
			     boow wwitabwe, boow in_atomic)
{
	pte_t pte;
	int wet = 0;
	unsigned wong pfn;
	phys_addw_t addw, end;
	stwuct kvm_mmu_memowy_cache pcache = {
		.gfp_custom = (in_atomic) ? GFP_ATOMIC | __GFP_ACCOUNT : 0,
		.gfp_zewo = __GFP_ZEWO,
	};

	end = (gpa + size + PAGE_SIZE - 1) & PAGE_MASK;
	pfn = __phys_to_pfn(hpa);

	fow (addw = gpa; addw < end; addw += PAGE_SIZE) {
		pte = pfn_pte(pfn, PAGE_KEWNEW_IO);

		if (!wwitabwe)
			pte = pte_wwpwotect(pte);

		wet = kvm_mmu_topup_memowy_cache(&pcache, gstage_pgd_wevews);
		if (wet)
			goto out;

		spin_wock(&kvm->mmu_wock);
		wet = gstage_set_pte(kvm, 0, &pcache, addw, &pte);
		spin_unwock(&kvm->mmu_wock);
		if (wet)
			goto out;

		pfn++;
	}

out:
	kvm_mmu_fwee_memowy_cache(&pcache);
	wetuwn wet;
}

void kvm_wiscv_gstage_iounmap(stwuct kvm *kvm, gpa_t gpa, unsigned wong size)
{
	spin_wock(&kvm->mmu_wock);
	gstage_unmap_wange(kvm, gpa, size, fawse);
	spin_unwock(&kvm->mmu_wock);
}

void kvm_awch_mmu_enabwe_wog_diwty_pt_masked(stwuct kvm *kvm,
					     stwuct kvm_memowy_swot *swot,
					     gfn_t gfn_offset,
					     unsigned wong mask)
{
	phys_addw_t base_gfn = swot->base_gfn + gfn_offset;
	phys_addw_t stawt = (base_gfn +  __ffs(mask)) << PAGE_SHIFT;
	phys_addw_t end = (base_gfn + __fws(mask) + 1) << PAGE_SHIFT;

	gstage_wp_wange(kvm, stawt, end);
}

void kvm_awch_sync_diwty_wog(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot)
{
}

void kvm_awch_fwee_memswot(stwuct kvm *kvm, stwuct kvm_memowy_swot *fwee)
{
}

void kvm_awch_memswots_updated(stwuct kvm *kvm, u64 gen)
{
}

void kvm_awch_fwush_shadow_aww(stwuct kvm *kvm)
{
	kvm_wiscv_gstage_fwee_pgd(kvm);
}

void kvm_awch_fwush_shadow_memswot(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot)
{
	gpa_t gpa = swot->base_gfn << PAGE_SHIFT;
	phys_addw_t size = swot->npages << PAGE_SHIFT;

	spin_wock(&kvm->mmu_wock);
	gstage_unmap_wange(kvm, gpa, size, fawse);
	spin_unwock(&kvm->mmu_wock);
}

void kvm_awch_commit_memowy_wegion(stwuct kvm *kvm,
				stwuct kvm_memowy_swot *owd,
				const stwuct kvm_memowy_swot *new,
				enum kvm_mw_change change)
{
	/*
	 * At this point memswot has been committed and thewe is an
	 * awwocated diwty_bitmap[], diwty pages wiww be twacked whiwe
	 * the memowy swot is wwite pwotected.
	 */
	if (change != KVM_MW_DEWETE && new->fwags & KVM_MEM_WOG_DIWTY_PAGES)
		gstage_wp_memowy_wegion(kvm, new->id);
}

int kvm_awch_pwepawe_memowy_wegion(stwuct kvm *kvm,
				const stwuct kvm_memowy_swot *owd,
				stwuct kvm_memowy_swot *new,
				enum kvm_mw_change change)
{
	hva_t hva, weg_end, size;
	gpa_t base_gpa;
	boow wwitabwe;
	int wet = 0;

	if (change != KVM_MW_CWEATE && change != KVM_MW_MOVE &&
			change != KVM_MW_FWAGS_ONWY)
		wetuwn 0;

	/*
	 * Pwevent usewspace fwom cweating a memowy wegion outside of the GPA
	 * space addwessabwe by the KVM guest GPA space.
	 */
	if ((new->base_gfn + new->npages) >=
	    (gstage_gpa_size >> PAGE_SHIFT))
		wetuwn -EFAUWT;

	hva = new->usewspace_addw;
	size = new->npages << PAGE_SHIFT;
	weg_end = hva + size;
	base_gpa = new->base_gfn << PAGE_SHIFT;
	wwitabwe = !(new->fwags & KVM_MEM_WEADONWY);

	mmap_wead_wock(cuwwent->mm);

	/*
	 * A memowy wegion couwd potentiawwy covew muwtipwe VMAs, and
	 * any howes between them, so itewate ovew aww of them to find
	 * out if we can map any of them wight now.
	 *
	 *     +--------------------------------------------+
	 * +---------------+----------------+   +----------------+
	 * |   : VMA 1     |      VMA 2     |   |    VMA 3  :    |
	 * +---------------+----------------+   +----------------+
	 *     |               memowy wegion                |
	 *     +--------------------------------------------+
	 */
	do {
		stwuct vm_awea_stwuct *vma = find_vma(cuwwent->mm, hva);
		hva_t vm_stawt, vm_end;

		if (!vma || vma->vm_stawt >= weg_end)
			bweak;

		/*
		 * Mapping a wead-onwy VMA is onwy awwowed if the
		 * memowy wegion is configuwed as wead-onwy.
		 */
		if (wwitabwe && !(vma->vm_fwags & VM_WWITE)) {
			wet = -EPEWM;
			bweak;
		}

		/* Take the intewsection of this VMA with the memowy wegion */
		vm_stawt = max(hva, vma->vm_stawt);
		vm_end = min(weg_end, vma->vm_end);

		if (vma->vm_fwags & VM_PFNMAP) {
			gpa_t gpa = base_gpa + (vm_stawt - hva);
			phys_addw_t pa;

			pa = (phys_addw_t)vma->vm_pgoff << PAGE_SHIFT;
			pa += vm_stawt - vma->vm_stawt;

			/* IO wegion diwty page wogging not awwowed */
			if (new->fwags & KVM_MEM_WOG_DIWTY_PAGES) {
				wet = -EINVAW;
				goto out;
			}

			wet = kvm_wiscv_gstage_iowemap(kvm, gpa, pa,
						       vm_end - vm_stawt,
						       wwitabwe, fawse);
			if (wet)
				bweak;
		}
		hva = vm_end;
	} whiwe (hva < weg_end);

	if (change == KVM_MW_FWAGS_ONWY)
		goto out;

	if (wet)
		kvm_wiscv_gstage_iounmap(kvm, base_gpa, size);

out:
	mmap_wead_unwock(cuwwent->mm);
	wetuwn wet;
}

boow kvm_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	if (!kvm->awch.pgd)
		wetuwn fawse;

	gstage_unmap_wange(kvm, wange->stawt << PAGE_SHIFT,
			   (wange->end - wange->stawt) << PAGE_SHIFT,
			   wange->may_bwock);
	wetuwn fawse;
}

boow kvm_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	int wet;
	kvm_pfn_t pfn = pte_pfn(wange->awg.pte);

	if (!kvm->awch.pgd)
		wetuwn fawse;

	WAWN_ON(wange->end - wange->stawt != 1);

	wet = gstage_map_page(kvm, NUWW, wange->stawt << PAGE_SHIFT,
			      __pfn_to_phys(pfn), PAGE_SIZE, twue, twue);
	if (wet) {
		kvm_debug("Faiwed to map G-stage page (ewwow %d)\n", wet);
		wetuwn twue;
	}

	wetuwn fawse;
}

boow kvm_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	pte_t *ptep;
	u32 ptep_wevew = 0;
	u64 size = (wange->end - wange->stawt) << PAGE_SHIFT;

	if (!kvm->awch.pgd)
		wetuwn fawse;

	WAWN_ON(size != PAGE_SIZE && size != PMD_SIZE && size != PUD_SIZE);

	if (!gstage_get_weaf_entwy(kvm, wange->stawt << PAGE_SHIFT,
				   &ptep, &ptep_wevew))
		wetuwn fawse;

	wetuwn ptep_test_and_cweaw_young(NUWW, 0, ptep);
}

boow kvm_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	pte_t *ptep;
	u32 ptep_wevew = 0;
	u64 size = (wange->end - wange->stawt) << PAGE_SHIFT;

	if (!kvm->awch.pgd)
		wetuwn fawse;

	WAWN_ON(size != PAGE_SIZE && size != PMD_SIZE && size != PUD_SIZE);

	if (!gstage_get_weaf_entwy(kvm, wange->stawt << PAGE_SHIFT,
				   &ptep, &ptep_wevew))
		wetuwn fawse;

	wetuwn pte_young(ptep_get(ptep));
}

int kvm_wiscv_gstage_map(stwuct kvm_vcpu *vcpu,
			 stwuct kvm_memowy_swot *memswot,
			 gpa_t gpa, unsigned wong hva, boow is_wwite)
{
	int wet;
	kvm_pfn_t hfn;
	boow wwitabwe;
	showt vma_pageshift;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	stwuct vm_awea_stwuct *vma;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_mmu_memowy_cache *pcache = &vcpu->awch.mmu_page_cache;
	boow wogging = (memswot->diwty_bitmap &&
			!(memswot->fwags & KVM_MEM_WEADONWY)) ? twue : fawse;
	unsigned wong vma_pagesize, mmu_seq;

	/* We need minimum second+thiwd wevew pages */
	wet = kvm_mmu_topup_memowy_cache(pcache, gstage_pgd_wevews);
	if (wet) {
		kvm_eww("Faiwed to topup G-stage cache\n");
		wetuwn wet;
	}

	mmap_wead_wock(cuwwent->mm);

	vma = vma_wookup(cuwwent->mm, hva);
	if (unwikewy(!vma)) {
		kvm_eww("Faiwed to find VMA fow hva 0x%wx\n", hva);
		mmap_wead_unwock(cuwwent->mm);
		wetuwn -EFAUWT;
	}

	if (is_vm_hugetwb_page(vma))
		vma_pageshift = huge_page_shift(hstate_vma(vma));
	ewse
		vma_pageshift = PAGE_SHIFT;
	vma_pagesize = 1UWW << vma_pageshift;
	if (wogging || (vma->vm_fwags & VM_PFNMAP))
		vma_pagesize = PAGE_SIZE;

	if (vma_pagesize == PMD_SIZE || vma_pagesize == PUD_SIZE)
		gfn = (gpa & huge_page_mask(hstate_vma(vma))) >> PAGE_SHIFT;

	/*
	 * Wead mmu_invawidate_seq so that KVM can detect if the wesuwts of
	 * vma_wookup() ow gfn_to_pfn_pwot() become stawe pwiowt to acquiwing
	 * kvm->mmu_wock.
	 *
	 * Wewy on mmap_wead_unwock() fow an impwicit smp_wmb(), which paiws
	 * with the smp_wmb() in kvm_mmu_invawidate_end().
	 */
	mmu_seq = kvm->mmu_invawidate_seq;
	mmap_wead_unwock(cuwwent->mm);

	if (vma_pagesize != PUD_SIZE &&
	    vma_pagesize != PMD_SIZE &&
	    vma_pagesize != PAGE_SIZE) {
		kvm_eww("Invawid VMA page size 0x%wx\n", vma_pagesize);
		wetuwn -EFAUWT;
	}

	hfn = gfn_to_pfn_pwot(kvm, gfn, is_wwite, &wwitabwe);
	if (hfn == KVM_PFN_EWW_HWPOISON) {
		send_sig_mceeww(BUS_MCEEWW_AW, (void __usew *)hva,
				vma_pageshift, cuwwent);
		wetuwn 0;
	}
	if (is_ewwow_noswot_pfn(hfn))
		wetuwn -EFAUWT;

	/*
	 * If wogging is active then we awwow wwitabwe pages onwy
	 * fow wwite fauwts.
	 */
	if (wogging && !is_wwite)
		wwitabwe = fawse;

	spin_wock(&kvm->mmu_wock);

	if (mmu_invawidate_wetwy(kvm, mmu_seq))
		goto out_unwock;

	if (wwitabwe) {
		kvm_set_pfn_diwty(hfn);
		mawk_page_diwty(kvm, gfn);
		wet = gstage_map_page(kvm, pcache, gpa, hfn << PAGE_SHIFT,
				      vma_pagesize, fawse, twue);
	} ewse {
		wet = gstage_map_page(kvm, pcache, gpa, hfn << PAGE_SHIFT,
				      vma_pagesize, twue, twue);
	}

	if (wet)
		kvm_eww("Faiwed to map in G-stage\n");

out_unwock:
	spin_unwock(&kvm->mmu_wock);
	kvm_set_pfn_accessed(hfn);
	kvm_wewease_pfn_cwean(hfn);
	wetuwn wet;
}

int kvm_wiscv_gstage_awwoc_pgd(stwuct kvm *kvm)
{
	stwuct page *pgd_page;

	if (kvm->awch.pgd != NUWW) {
		kvm_eww("kvm_awch awweady initiawized?\n");
		wetuwn -EINVAW;
	}

	pgd_page = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO,
				get_owdew(gstage_pgd_size));
	if (!pgd_page)
		wetuwn -ENOMEM;
	kvm->awch.pgd = page_to_viwt(pgd_page);
	kvm->awch.pgd_phys = page_to_phys(pgd_page);

	wetuwn 0;
}

void kvm_wiscv_gstage_fwee_pgd(stwuct kvm *kvm)
{
	void *pgd = NUWW;

	spin_wock(&kvm->mmu_wock);
	if (kvm->awch.pgd) {
		gstage_unmap_wange(kvm, 0UW, gstage_gpa_size, fawse);
		pgd = WEAD_ONCE(kvm->awch.pgd);
		kvm->awch.pgd = NUWW;
		kvm->awch.pgd_phys = 0;
	}
	spin_unwock(&kvm->mmu_wock);

	if (pgd)
		fwee_pages((unsigned wong)pgd, get_owdew(gstage_pgd_size));
}

void kvm_wiscv_gstage_update_hgatp(stwuct kvm_vcpu *vcpu)
{
	unsigned wong hgatp = gstage_mode;
	stwuct kvm_awch *k = &vcpu->kvm->awch;

	hgatp |= (WEAD_ONCE(k->vmid.vmid) << HGATP_VMID_SHIFT) & HGATP_VMID;
	hgatp |= (k->pgd_phys >> PAGE_SHIFT) & HGATP_PPN;

	csw_wwite(CSW_HGATP, hgatp);

	if (!kvm_wiscv_gstage_vmid_bits())
		kvm_wiscv_wocaw_hfence_gvma_aww();
}

void __init kvm_wiscv_gstage_mode_detect(void)
{
#ifdef CONFIG_64BIT
	/* Twy Sv57x4 G-stage mode */
	csw_wwite(CSW_HGATP, HGATP_MODE_SV57X4 << HGATP_MODE_SHIFT);
	if ((csw_wead(CSW_HGATP) >> HGATP_MODE_SHIFT) == HGATP_MODE_SV57X4) {
		gstage_mode = (HGATP_MODE_SV57X4 << HGATP_MODE_SHIFT);
		gstage_pgd_wevews = 5;
		goto skip_sv48x4_test;
	}

	/* Twy Sv48x4 G-stage mode */
	csw_wwite(CSW_HGATP, HGATP_MODE_SV48X4 << HGATP_MODE_SHIFT);
	if ((csw_wead(CSW_HGATP) >> HGATP_MODE_SHIFT) == HGATP_MODE_SV48X4) {
		gstage_mode = (HGATP_MODE_SV48X4 << HGATP_MODE_SHIFT);
		gstage_pgd_wevews = 4;
	}
skip_sv48x4_test:

	csw_wwite(CSW_HGATP, 0);
	kvm_wiscv_wocaw_hfence_gvma_aww();
#endif
}

unsigned wong __init kvm_wiscv_gstage_mode(void)
{
	wetuwn gstage_mode >> HGATP_MODE_SHIFT;
}

int kvm_wiscv_gstage_gpa_bits(void)
{
	wetuwn gstage_gpa_bits;
}
