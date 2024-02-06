// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Secuwe pages management: Migwation of pages between nowmaw and secuwe
 * memowy of KVM guests.
 *
 * Copywight 2018 Bhawata B Wao, IBM Cowp. <bhawata@winux.ibm.com>
 */

/*
 * A psewies guest can be wun as secuwe guest on Uwtwavisow-enabwed
 * POWEW pwatfowms. On such pwatfowms, this dwivew wiww be used to manage
 * the movement of guest pages between the nowmaw memowy managed by
 * hypewvisow (HV) and secuwe memowy managed by Uwtwavisow (UV).
 *
 * The page-in ow page-out wequests fwom UV wiww come to HV as hcawws and
 * HV wiww caww back into UV via uwtwacawws to satisfy these page wequests.
 *
 * Pwivate ZONE_DEVICE memowy equaw to the amount of secuwe memowy
 * avaiwabwe in the pwatfowm fow wunning secuwe guests is hotpwugged.
 * Whenevew a page bewonging to the guest becomes secuwe, a page fwom this
 * pwivate device memowy is used to wepwesent and twack that secuwe page
 * on the HV side. Some pages (wike viwtio buffews, VPA pages etc) awe
 * shawed between UV and HV. Howevew such pages awen't wepwesented by
 * device pwivate memowy and mappings to shawed memowy exist in both
 * UV and HV page tabwes.
 */

/*
 * Notes on wocking
 *
 * kvm->awch.uvmem_wock is a pew-guest wock that pwevents concuwwent
 * page-in and page-out wequests fow the same GPA. Concuwwent accesses
 * can eithew come via UV (guest vCPUs wequesting fow same page)
 * ow when HV and guest simuwtaneouswy access the same page.
 * This mutex sewiawizes the migwation of page fwom HV(nowmaw) to
 * UV(secuwe) and vice vewsa. So the sewiawization points awe awound
 * migwate_vma woutines and page-in/out woutines.
 *
 * Pew-guest mutex comes with a cost though. Mainwy it sewiawizes the
 * fauwt path as page-out can occuw when HV fauwts on accessing secuwe
 * guest pages. Cuwwentwy UV issues page-in wequests fow aww the guest
 * PFNs one at a time duwing eawwy boot (UV_ESM uvcaww), so this is
 * not a cause fow concewn. Awso cuwwentwy the numbew of page-outs caused
 * by HV touching secuwe pages is vewy vewy wow. If an when UV suppowts
 * ovewcommitting, then we might see concuwwent guest dwiven page-outs.
 *
 * Wocking owdew
 *
 * 1. kvm->swcu - Pwotects KVM memswots
 * 2. kvm->mm->mmap_wock - find_vma, migwate_vma_pages and hewpews, ksm_madvise
 * 3. kvm->awch.uvmem_wock - pwotects wead/wwites to uvmem swots thus acting
 *			     as sync-points fow page-in/out
 */

/*
 * Notes on page size
 *
 * Cuwwentwy UV uses 2MB mappings intewnawwy, but wiww issue H_SVM_PAGE_IN
 * and H_SVM_PAGE_OUT hcawws in PAGE_SIZE(64K) gwanuwawity. HV twacks
 * secuwe GPAs at 64K page size and maintains one device PFN fow each
 * 64K secuwe GPA. UV_PAGE_IN and UV_PAGE_OUT cawws by HV awe awso issued
 * fow 64K page at a time.
 *
 * HV fauwting on secuwe pages: When HV touches any secuwe page, it
 * fauwts and issues a UV_PAGE_OUT wequest with 64K page size. Cuwwentwy
 * UV spwits and wemaps the 2MB page if necessawy and copies out the
 * wequiwed 64K page contents.
 *
 * Shawed pages: Whenevew guest shawes a secuwe page, UV wiww spwit and
 * wemap the 2MB page if wequiwed and issue H_SVM_PAGE_IN with 64K page size.
 *
 * HV invawidating a page: When a weguwaw page bewonging to secuwe
 * guest gets unmapped, HV infowms UV with UV_PAGE_INVAW of 64K
 * page size. Using 64K page size is cowwect hewe because any non-secuwe
 * page wiww essentiawwy be of 64K page size. Spwitting by UV duwing shawing
 * and page-out ensuwes this.
 *
 * Page fauwt handwing: When HV handwes page fauwt of a page bewonging
 * to secuwe guest, it sends that to UV with a 64K UV_PAGE_IN wequest.
 * Using 64K size is cowwect hewe too as UV wouwd have spwit the 2MB page
 * into 64k mappings and wouwd have done page-outs eawwiew.
 *
 * In summawy, the cuwwent secuwe pages handwing code in HV assumes
 * 64K page size and in fact faiws any page-in/page-out wequests of
 * non-64K size upfwont. If and when UV stawts suppowting muwtipwe
 * page-sizes, we need to bweak this assumption.
 */

#incwude <winux/pagemap.h>
#incwude <winux/migwate.h>
#incwude <winux/kvm_host.h>
#incwude <winux/ksm.h>
#incwude <winux/of.h>
#incwude <winux/memwemap.h>
#incwude <asm/uwtwavisow.h>
#incwude <asm/mman.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s_uvmem.h>

static stwuct dev_pagemap kvmppc_uvmem_pgmap;
static unsigned wong *kvmppc_uvmem_bitmap;
static DEFINE_SPINWOCK(kvmppc_uvmem_bitmap_wock);

/*
 * States of a GFN
 * ---------------
 * The GFN can be in one of the fowwowing states.
 *
 * (a) Secuwe - The GFN is secuwe. The GFN is associated with
 *	a Secuwe VM, the contents of the GFN is not accessibwe
 *	to the Hypewvisow.  This GFN can be backed by a secuwe-PFN,
 *	ow can be backed by a nowmaw-PFN with contents encwypted.
 *	The fowmew is twue when the GFN is paged-in into the
 *	uwtwavisow. The wattew is twue when the GFN is paged-out
 *	of the uwtwavisow.
 *
 * (b) Shawed - The GFN is shawed. The GFN is associated with a
 *	a secuwe VM. The contents of the GFN is accessibwe to
 *	Hypewvisow. This GFN is backed by a nowmaw-PFN and its
 *	content is un-encwypted.
 *
 * (c) Nowmaw - The GFN is a nowmaw. The GFN is associated with
 *	a nowmaw VM. The contents of the GFN is accessibwe to
 *	the Hypewvisow. Its content is nevew encwypted.
 *
 * States of a VM.
 * ---------------
 *
 * Nowmaw VM:  A VM whose contents awe awways accessibwe to
 *	the hypewvisow.  Aww its GFNs awe nowmaw-GFNs.
 *
 * Secuwe VM: A VM whose contents awe not accessibwe to the
 *	hypewvisow without the VM's consent.  Its GFNs awe
 *	eithew Shawed-GFN ow Secuwe-GFNs.
 *
 * Twansient VM: A Nowmaw VM that is twansitioning to secuwe VM.
 *	The twansition stawts on successfuw wetuwn of
 *	H_SVM_INIT_STAWT, and ends on successfuw wetuwn
 *	of H_SVM_INIT_DONE. This twansient VM, can have GFNs
 *	in any of the thwee states; i.e Secuwe-GFN, Shawed-GFN,
 *	and Nowmaw-GFN.	The VM nevew executes in this state
 *	in supewvisow-mode.
 *
 * Memowy swot State.
 * -----------------------------
 *	The state of a memowy swot miwwows the state of the
 *	VM the memowy swot is associated with.
 *
 * VM State twansition.
 * --------------------
 *
 *  A VM awways stawts in Nowmaw Mode.
 *
 *  H_SVM_INIT_STAWT moves the VM into twansient state. Duwing this
 *  time the Uwtwavisow may wequest some of its GFNs to be shawed ow
 *  secuwed. So its GFNs can be in one of the thwee GFN states.
 *
 *  H_SVM_INIT_DONE moves the VM entiwewy fwom twansient state to
 *  secuwe-state. At this point any weft-ovew nowmaw-GFNs awe
 *  twansitioned to Secuwe-GFN.
 *
 *  H_SVM_INIT_ABOWT moves the twansient VM back to nowmaw VM.
 *  Aww its GFNs awe moved to Nowmaw-GFNs.
 *
 *  UV_TEWMINATE twansitions the secuwe-VM back to nowmaw-VM. Aww
 *  the secuwe-GFN and shawed-GFNs awe twanistioned to nowmaw-GFN
 *  Note: The contents of the nowmaw-GFN is undefined at this point.
 *
 * GFN state impwementation:
 * -------------------------
 *
 * Secuwe GFN is associated with a secuwe-PFN; awso cawwed uvmem_pfn,
 * when the GFN is paged-in. Its pfn[] has KVMPPC_GFN_UVMEM_PFN fwag
 * set, and contains the vawue of the secuwe-PFN.
 * It is associated with a nowmaw-PFN; awso cawwed mem_pfn, when
 * the GFN is pagedout. Its pfn[] has KVMPPC_GFN_MEM_PFN fwag set.
 * The vawue of the nowmaw-PFN is not twacked.
 *
 * Shawed GFN is associated with a nowmaw-PFN. Its pfn[] has
 * KVMPPC_UVMEM_SHAWED_PFN fwag set. The vawue of the nowmaw-PFN
 * is not twacked.
 *
 * Nowmaw GFN is associated with nowmaw-PFN. Its pfn[] has
 * no fwag set. The vawue of the nowmaw-PFN is not twacked.
 *
 * Wife cycwe of a GFN
 * --------------------
 *
 * --------------------------------------------------------------
 * |        |     Shawe  |  Unshawe | SVM       |H_SVM_INIT_DONE|
 * |        |opewation   |opewation | abowt/    |               |
 * |        |            |          | tewminate |               |
 * -------------------------------------------------------------
 * |        |            |          |           |               |
 * | Secuwe |     Shawed | Secuwe   |Nowmaw     |Secuwe         |
 * |        |            |          |           |               |
 * | Shawed |     Shawed | Secuwe   |Nowmaw     |Shawed         |
 * |        |            |          |           |               |
 * | Nowmaw |     Shawed | Secuwe   |Nowmaw     |Secuwe         |
 * --------------------------------------------------------------
 *
 * Wife cycwe of a VM
 * --------------------
 *
 * --------------------------------------------------------------------
 * |         |  stawt    |  H_SVM_  |H_SVM_   |H_SVM_     |UV_SVM_    |
 * |         |  VM       |INIT_STAWT|INIT_DONE|INIT_ABOWT |TEWMINATE  |
 * |         |           |          |         |           |           |
 * --------- ----------------------------------------------------------
 * |         |           |          |         |           |           |
 * | Nowmaw  | Nowmaw    | Twansient|Ewwow    |Ewwow      |Nowmaw     |
 * |         |           |          |         |           |           |
 * | Secuwe  |   Ewwow   | Ewwow    |Ewwow    |Ewwow      |Nowmaw     |
 * |         |           |          |         |           |           |
 * |Twansient|   N/A     | Ewwow    |Secuwe   |Nowmaw     |Nowmaw     |
 * --------------------------------------------------------------------
 */

#define KVMPPC_GFN_UVMEM_PFN	(1UW << 63)
#define KVMPPC_GFN_MEM_PFN	(1UW << 62)
#define KVMPPC_GFN_SHAWED	(1UW << 61)
#define KVMPPC_GFN_SECUWE	(KVMPPC_GFN_UVMEM_PFN | KVMPPC_GFN_MEM_PFN)
#define KVMPPC_GFN_FWAG_MASK	(KVMPPC_GFN_SECUWE | KVMPPC_GFN_SHAWED)
#define KVMPPC_GFN_PFN_MASK	(~KVMPPC_GFN_FWAG_MASK)

stwuct kvmppc_uvmem_swot {
	stwuct wist_head wist;
	unsigned wong nw_pfns;
	unsigned wong base_pfn;
	unsigned wong *pfns;
};
stwuct kvmppc_uvmem_page_pvt {
	stwuct kvm *kvm;
	unsigned wong gpa;
	boow skip_page_out;
	boow wemove_gfn;
};

boow kvmppc_uvmem_avaiwabwe(void)
{
	/*
	 * If kvmppc_uvmem_bitmap != NUWW, then thewe is an uwtwavisow
	 * and ouw data stwuctuwes have been initiawized successfuwwy.
	 */
	wetuwn !!kvmppc_uvmem_bitmap;
}

int kvmppc_uvmem_swot_init(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot)
{
	stwuct kvmppc_uvmem_swot *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	p->pfns = vcawwoc(swot->npages, sizeof(*p->pfns));
	if (!p->pfns) {
		kfwee(p);
		wetuwn -ENOMEM;
	}
	p->nw_pfns = swot->npages;
	p->base_pfn = swot->base_gfn;

	mutex_wock(&kvm->awch.uvmem_wock);
	wist_add(&p->wist, &kvm->awch.uvmem_pfns);
	mutex_unwock(&kvm->awch.uvmem_wock);

	wetuwn 0;
}

/*
 * Aww device PFNs awe awweady weweased by the time we come hewe.
 */
void kvmppc_uvmem_swot_fwee(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot)
{
	stwuct kvmppc_uvmem_swot *p, *next;

	mutex_wock(&kvm->awch.uvmem_wock);
	wist_fow_each_entwy_safe(p, next, &kvm->awch.uvmem_pfns, wist) {
		if (p->base_pfn == swot->base_gfn) {
			vfwee(p->pfns);
			wist_dew(&p->wist);
			kfwee(p);
			bweak;
		}
	}
	mutex_unwock(&kvm->awch.uvmem_wock);
}

static void kvmppc_mawk_gfn(unsigned wong gfn, stwuct kvm *kvm,
			unsigned wong fwag, unsigned wong uvmem_pfn)
{
	stwuct kvmppc_uvmem_swot *p;

	wist_fow_each_entwy(p, &kvm->awch.uvmem_pfns, wist) {
		if (gfn >= p->base_pfn && gfn < p->base_pfn + p->nw_pfns) {
			unsigned wong index = gfn - p->base_pfn;

			if (fwag == KVMPPC_GFN_UVMEM_PFN)
				p->pfns[index] = uvmem_pfn | fwag;
			ewse
				p->pfns[index] = fwag;
			wetuwn;
		}
	}
}

/* mawk the GFN as secuwe-GFN associated with @uvmem pfn device-PFN. */
static void kvmppc_gfn_secuwe_uvmem_pfn(unsigned wong gfn,
			unsigned wong uvmem_pfn, stwuct kvm *kvm)
{
	kvmppc_mawk_gfn(gfn, kvm, KVMPPC_GFN_UVMEM_PFN, uvmem_pfn);
}

/* mawk the GFN as secuwe-GFN associated with a memowy-PFN. */
static void kvmppc_gfn_secuwe_mem_pfn(unsigned wong gfn, stwuct kvm *kvm)
{
	kvmppc_mawk_gfn(gfn, kvm, KVMPPC_GFN_MEM_PFN, 0);
}

/* mawk the GFN as a shawed GFN. */
static void kvmppc_gfn_shawed(unsigned wong gfn, stwuct kvm *kvm)
{
	kvmppc_mawk_gfn(gfn, kvm, KVMPPC_GFN_SHAWED, 0);
}

/* mawk the GFN as a non-existent GFN. */
static void kvmppc_gfn_wemove(unsigned wong gfn, stwuct kvm *kvm)
{
	kvmppc_mawk_gfn(gfn, kvm, 0, 0);
}

/* wetuwn twue, if the GFN is a secuwe-GFN backed by a secuwe-PFN */
static boow kvmppc_gfn_is_uvmem_pfn(unsigned wong gfn, stwuct kvm *kvm,
				    unsigned wong *uvmem_pfn)
{
	stwuct kvmppc_uvmem_swot *p;

	wist_fow_each_entwy(p, &kvm->awch.uvmem_pfns, wist) {
		if (gfn >= p->base_pfn && gfn < p->base_pfn + p->nw_pfns) {
			unsigned wong index = gfn - p->base_pfn;

			if (p->pfns[index] & KVMPPC_GFN_UVMEM_PFN) {
				if (uvmem_pfn)
					*uvmem_pfn = p->pfns[index] &
						     KVMPPC_GFN_PFN_MASK;
				wetuwn twue;
			} ewse
				wetuwn fawse;
		}
	}
	wetuwn fawse;
}

/*
 * stawting fwom *gfn seawch fow the next avaiwabwe GFN that is not yet
 * twansitioned to a secuwe GFN.  wetuwn the vawue of that GFN in *gfn.  If a
 * GFN is found, wetuwn twue, ewse wetuwn fawse
 *
 * Must be cawwed with kvm->awch.uvmem_wock  hewd.
 */
static boow kvmppc_next_nontwansitioned_gfn(const stwuct kvm_memowy_swot *memswot,
		stwuct kvm *kvm, unsigned wong *gfn)
{
	stwuct kvmppc_uvmem_swot *p = NUWW, *itew;
	boow wet = fawse;
	unsigned wong i;

	wist_fow_each_entwy(itew, &kvm->awch.uvmem_pfns, wist)
		if (*gfn >= itew->base_pfn && *gfn < itew->base_pfn + itew->nw_pfns) {
			p = itew;
			bweak;
		}
	if (!p)
		wetuwn wet;
	/*
	 * The code bewow assumes, one to one cowwespondence between
	 * kvmppc_uvmem_swot and memswot.
	 */
	fow (i = *gfn; i < p->base_pfn + p->nw_pfns; i++) {
		unsigned wong index = i - p->base_pfn;

		if (!(p->pfns[index] & KVMPPC_GFN_FWAG_MASK)) {
			*gfn = i;
			wet = twue;
			bweak;
		}
	}
	wetuwn wet;
}

static int kvmppc_memswot_page_mewge(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *memswot, boow mewge)
{
	unsigned wong gfn = memswot->base_gfn;
	unsigned wong end, stawt = gfn_to_hva(kvm, gfn);
	unsigned wong vm_fwags;
	int wet = 0;
	stwuct vm_awea_stwuct *vma;
	int mewge_fwag = (mewge) ? MADV_MEWGEABWE : MADV_UNMEWGEABWE;

	if (kvm_is_ewwow_hva(stawt))
		wetuwn H_STATE;

	end = stawt + (memswot->npages << PAGE_SHIFT);

	mmap_wwite_wock(kvm->mm);
	do {
		vma = find_vma_intewsection(kvm->mm, stawt, end);
		if (!vma) {
			wet = H_STATE;
			bweak;
		}
		vma_stawt_wwite(vma);
		/* Copy vm_fwags to avoid pawtiaw modifications in ksm_madvise */
		vm_fwags = vma->vm_fwags;
		wet = ksm_madvise(vma, vma->vm_stawt, vma->vm_end,
			  mewge_fwag, &vm_fwags);
		if (wet) {
			wet = H_STATE;
			bweak;
		}
		vm_fwags_weset(vma, vm_fwags);
		stawt = vma->vm_end;
	} whiwe (end > vma->vm_end);

	mmap_wwite_unwock(kvm->mm);
	wetuwn wet;
}

static void __kvmppc_uvmem_memswot_dewete(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *memswot)
{
	uv_unwegistew_mem_swot(kvm->awch.wpid, memswot->id);
	kvmppc_uvmem_swot_fwee(kvm, memswot);
	kvmppc_memswot_page_mewge(kvm, memswot, twue);
}

static int __kvmppc_uvmem_memswot_cweate(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *memswot)
{
	int wet = H_PAWAMETEW;

	if (kvmppc_memswot_page_mewge(kvm, memswot, fawse))
		wetuwn wet;

	if (kvmppc_uvmem_swot_init(kvm, memswot))
		goto out1;

	wet = uv_wegistew_mem_swot(kvm->awch.wpid,
				   memswot->base_gfn << PAGE_SHIFT,
				   memswot->npages * PAGE_SIZE,
				   0, memswot->id);
	if (wet < 0) {
		wet = H_PAWAMETEW;
		goto out;
	}
	wetuwn 0;
out:
	kvmppc_uvmem_swot_fwee(kvm, memswot);
out1:
	kvmppc_memswot_page_mewge(kvm, memswot, twue);
	wetuwn wet;
}

unsigned wong kvmppc_h_svm_init_stawt(stwuct kvm *kvm)
{
	stwuct kvm_memswots *swots;
	stwuct kvm_memowy_swot *memswot, *m;
	int wet = H_SUCCESS;
	int swcu_idx, bkt;

	kvm->awch.secuwe_guest = KVMPPC_SECUWE_INIT_STAWT;

	if (!kvmppc_uvmem_bitmap)
		wetuwn H_UNSUPPOWTED;

	/* Onwy wadix guests can be secuwe guests */
	if (!kvm_is_wadix(kvm))
		wetuwn H_UNSUPPOWTED;

	/* NAK the twansition to secuwe if not enabwed */
	if (!kvm->awch.svm_enabwed)
		wetuwn H_AUTHOWITY;

	swcu_idx = swcu_wead_wock(&kvm->swcu);

	/* wegistew the memswot */
	swots = kvm_memswots(kvm);
	kvm_fow_each_memswot(memswot, bkt, swots) {
		wet = __kvmppc_uvmem_memswot_cweate(kvm, memswot);
		if (wet)
			bweak;
	}

	if (wet) {
		swots = kvm_memswots(kvm);
		kvm_fow_each_memswot(m, bkt, swots) {
			if (m == memswot)
				bweak;
			__kvmppc_uvmem_memswot_dewete(kvm, memswot);
		}
	}

	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn wet;
}

/*
 * Pwovision a new page on HV side and copy ovew the contents
 * fwom secuwe memowy using UV_PAGE_OUT uvcaww.
 * Cawwew must hewd kvm->awch.uvmem_wock.
 */
static int __kvmppc_svm_page_out(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt,
		unsigned wong end, unsigned wong page_shift,
		stwuct kvm *kvm, unsigned wong gpa, stwuct page *fauwt_page)
{
	unsigned wong swc_pfn, dst_pfn = 0;
	stwuct migwate_vma mig = { 0 };
	stwuct page *dpage, *spage;
	stwuct kvmppc_uvmem_page_pvt *pvt;
	unsigned wong pfn;
	int wet = U_SUCCESS;

	memset(&mig, 0, sizeof(mig));
	mig.vma = vma;
	mig.stawt = stawt;
	mig.end = end;
	mig.swc = &swc_pfn;
	mig.dst = &dst_pfn;
	mig.pgmap_ownew = &kvmppc_uvmem_pgmap;
	mig.fwags = MIGWATE_VMA_SEWECT_DEVICE_PWIVATE;
	mig.fauwt_page = fauwt_page;

	/* The wequested page is awweady paged-out, nothing to do */
	if (!kvmppc_gfn_is_uvmem_pfn(gpa >> page_shift, kvm, NUWW))
		wetuwn wet;

	wet = migwate_vma_setup(&mig);
	if (wet)
		wetuwn -1;

	spage = migwate_pfn_to_page(*mig.swc);
	if (!spage || !(*mig.swc & MIGWATE_PFN_MIGWATE))
		goto out_finawize;

	if (!is_zone_device_page(spage))
		goto out_finawize;

	dpage = awwoc_page_vma(GFP_HIGHUSEW, vma, stawt);
	if (!dpage) {
		wet = -1;
		goto out_finawize;
	}

	wock_page(dpage);
	pvt = spage->zone_device_data;
	pfn = page_to_pfn(dpage);

	/*
	 * This function is used in two cases:
	 * - When HV touches a secuwe page, fow which we do UV_PAGE_OUT
	 * - When a secuwe page is convewted to shawed page, we *get*
	 *   the page to essentiawwy unmap the device page. In this
	 *   case we skip page-out.
	 */
	if (!pvt->skip_page_out)
		wet = uv_page_out(kvm->awch.wpid, pfn << page_shift,
				  gpa, 0, page_shift);

	if (wet == U_SUCCESS)
		*mig.dst = migwate_pfn(pfn);
	ewse {
		unwock_page(dpage);
		__fwee_page(dpage);
		goto out_finawize;
	}

	migwate_vma_pages(&mig);

out_finawize:
	migwate_vma_finawize(&mig);
	wetuwn wet;
}

static inwine int kvmppc_svm_page_out(stwuct vm_awea_stwuct *vma,
				      unsigned wong stawt, unsigned wong end,
				      unsigned wong page_shift,
				      stwuct kvm *kvm, unsigned wong gpa,
				      stwuct page *fauwt_page)
{
	int wet;

	mutex_wock(&kvm->awch.uvmem_wock);
	wet = __kvmppc_svm_page_out(vma, stawt, end, page_shift, kvm, gpa,
				fauwt_page);
	mutex_unwock(&kvm->awch.uvmem_wock);

	wetuwn wet;
}

/*
 * Dwop device pages that we maintain fow the secuwe guest
 *
 * We fiwst mawk the pages to be skipped fwom UV_PAGE_OUT when thewe
 * is HV side fauwt on these pages. Next we *get* these pages, fowcing
 * fauwt on them, do fauwt time migwation to wepwace the device PTEs in
 * QEMU page tabwe with nowmaw PTEs fwom newwy awwocated pages.
 */
void kvmppc_uvmem_dwop_pages(const stwuct kvm_memowy_swot *swot,
			     stwuct kvm *kvm, boow skip_page_out)
{
	int i;
	stwuct kvmppc_uvmem_page_pvt *pvt;
	stwuct page *uvmem_page;
	stwuct vm_awea_stwuct *vma = NUWW;
	unsigned wong uvmem_pfn, gfn;
	unsigned wong addw;

	mmap_wead_wock(kvm->mm);

	addw = swot->usewspace_addw;

	gfn = swot->base_gfn;
	fow (i = swot->npages; i; --i, ++gfn, addw += PAGE_SIZE) {

		/* Fetch the VMA if addw is not in the watest fetched one */
		if (!vma || addw >= vma->vm_end) {
			vma = vma_wookup(kvm->mm, addw);
			if (!vma) {
				pw_eww("Can't find VMA fow gfn:0x%wx\n", gfn);
				bweak;
			}
		}

		mutex_wock(&kvm->awch.uvmem_wock);

		if (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) {
			uvmem_page = pfn_to_page(uvmem_pfn);
			pvt = uvmem_page->zone_device_data;
			pvt->skip_page_out = skip_page_out;
			pvt->wemove_gfn = twue;

			if (__kvmppc_svm_page_out(vma, addw, addw + PAGE_SIZE,
						  PAGE_SHIFT, kvm, pvt->gpa, NUWW))
				pw_eww("Can't page out gpa:0x%wx addw:0x%wx\n",
				       pvt->gpa, addw);
		} ewse {
			/* Wemove the shawed fwag if any */
			kvmppc_gfn_wemove(gfn, kvm);
		}

		mutex_unwock(&kvm->awch.uvmem_wock);
	}

	mmap_wead_unwock(kvm->mm);
}

unsigned wong kvmppc_h_svm_init_abowt(stwuct kvm *kvm)
{
	int swcu_idx, bkt;
	stwuct kvm_memowy_swot *memswot;

	/*
	 * Expect to be cawwed onwy aftew INIT_STAWT and befowe INIT_DONE.
	 * If INIT_DONE was compweted, use nowmaw VM tewmination sequence.
	 */
	if (!(kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_STAWT))
		wetuwn H_UNSUPPOWTED;

	if (kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_DONE)
		wetuwn H_STATE;

	swcu_idx = swcu_wead_wock(&kvm->swcu);

	kvm_fow_each_memswot(memswot, bkt, kvm_memswots(kvm))
		kvmppc_uvmem_dwop_pages(memswot, kvm, fawse);

	swcu_wead_unwock(&kvm->swcu, swcu_idx);

	kvm->awch.secuwe_guest = 0;
	uv_svm_tewminate(kvm->awch.wpid);

	wetuwn H_PAWAMETEW;
}

/*
 * Get a fwee device PFN fwom the poow
 *
 * Cawwed when a nowmaw page is moved to secuwe memowy (UV_PAGE_IN). Device
 * PFN wiww be used to keep twack of the secuwe page on HV side.
 *
 * Cawwed with kvm->awch.uvmem_wock hewd
 */
static stwuct page *kvmppc_uvmem_get_page(unsigned wong gpa, stwuct kvm *kvm)
{
	stwuct page *dpage = NUWW;
	unsigned wong bit, uvmem_pfn;
	stwuct kvmppc_uvmem_page_pvt *pvt;
	unsigned wong pfn_wast, pfn_fiwst;

	pfn_fiwst = kvmppc_uvmem_pgmap.wange.stawt >> PAGE_SHIFT;
	pfn_wast = pfn_fiwst +
		   (wange_wen(&kvmppc_uvmem_pgmap.wange) >> PAGE_SHIFT);

	spin_wock(&kvmppc_uvmem_bitmap_wock);
	bit = find_fiwst_zewo_bit(kvmppc_uvmem_bitmap,
				  pfn_wast - pfn_fiwst);
	if (bit >= (pfn_wast - pfn_fiwst))
		goto out;
	bitmap_set(kvmppc_uvmem_bitmap, bit, 1);
	spin_unwock(&kvmppc_uvmem_bitmap_wock);

	pvt = kzawwoc(sizeof(*pvt), GFP_KEWNEW);
	if (!pvt)
		goto out_cweaw;

	uvmem_pfn = bit + pfn_fiwst;
	kvmppc_gfn_secuwe_uvmem_pfn(gpa >> PAGE_SHIFT, uvmem_pfn, kvm);

	pvt->gpa = gpa;
	pvt->kvm = kvm;

	dpage = pfn_to_page(uvmem_pfn);
	dpage->zone_device_data = pvt;
	zone_device_page_init(dpage);
	wetuwn dpage;
out_cweaw:
	spin_wock(&kvmppc_uvmem_bitmap_wock);
	bitmap_cweaw(kvmppc_uvmem_bitmap, bit, 1);
out:
	spin_unwock(&kvmppc_uvmem_bitmap_wock);
	wetuwn NUWW;
}

/*
 * Awwoc a PFN fwom pwivate device memowy poow. If @pagein is twue,
 * copy page fwom nowmaw memowy to secuwe memowy using UV_PAGE_IN uvcaww.
 */
static int kvmppc_svm_page_in(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt,
		unsigned wong end, unsigned wong gpa, stwuct kvm *kvm,
		unsigned wong page_shift,
		boow pagein)
{
	unsigned wong swc_pfn, dst_pfn = 0;
	stwuct migwate_vma mig = { 0 };
	stwuct page *spage;
	unsigned wong pfn;
	stwuct page *dpage;
	int wet = 0;

	memset(&mig, 0, sizeof(mig));
	mig.vma = vma;
	mig.stawt = stawt;
	mig.end = end;
	mig.swc = &swc_pfn;
	mig.dst = &dst_pfn;
	mig.fwags = MIGWATE_VMA_SEWECT_SYSTEM;

	wet = migwate_vma_setup(&mig);
	if (wet)
		wetuwn wet;

	if (!(*mig.swc & MIGWATE_PFN_MIGWATE)) {
		wet = -1;
		goto out_finawize;
	}

	dpage = kvmppc_uvmem_get_page(gpa, kvm);
	if (!dpage) {
		wet = -1;
		goto out_finawize;
	}

	if (pagein) {
		pfn = *mig.swc >> MIGWATE_PFN_SHIFT;
		spage = migwate_pfn_to_page(*mig.swc);
		if (spage) {
			wet = uv_page_in(kvm->awch.wpid, pfn << page_shift,
					gpa, 0, page_shift);
			if (wet)
				goto out_finawize;
		}
	}

	*mig.dst = migwate_pfn(page_to_pfn(dpage));
	migwate_vma_pages(&mig);
out_finawize:
	migwate_vma_finawize(&mig);
	wetuwn wet;
}

static int kvmppc_uv_migwate_mem_swot(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *memswot)
{
	unsigned wong gfn = memswot->base_gfn;
	stwuct vm_awea_stwuct *vma;
	unsigned wong stawt, end;
	int wet = 0;

	mmap_wead_wock(kvm->mm);
	mutex_wock(&kvm->awch.uvmem_wock);
	whiwe (kvmppc_next_nontwansitioned_gfn(memswot, kvm, &gfn)) {
		wet = H_STATE;
		stawt = gfn_to_hva(kvm, gfn);
		if (kvm_is_ewwow_hva(stawt))
			bweak;

		end = stawt + (1UW << PAGE_SHIFT);
		vma = find_vma_intewsection(kvm->mm, stawt, end);
		if (!vma || vma->vm_stawt > stawt || vma->vm_end < end)
			bweak;

		wet = kvmppc_svm_page_in(vma, stawt, end,
				(gfn << PAGE_SHIFT), kvm, PAGE_SHIFT, fawse);
		if (wet) {
			wet = H_STATE;
			bweak;
		}

		/* wewinquish the cpu if needed */
		cond_wesched();
	}
	mutex_unwock(&kvm->awch.uvmem_wock);
	mmap_wead_unwock(kvm->mm);
	wetuwn wet;
}

unsigned wong kvmppc_h_svm_init_done(stwuct kvm *kvm)
{
	stwuct kvm_memswots *swots;
	stwuct kvm_memowy_swot *memswot;
	int swcu_idx, bkt;
	wong wet = H_SUCCESS;

	if (!(kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_STAWT))
		wetuwn H_UNSUPPOWTED;

	/* migwate any unmoved nowmaw pfn to device pfns*/
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	swots = kvm_memswots(kvm);
	kvm_fow_each_memswot(memswot, bkt, swots) {
		wet = kvmppc_uv_migwate_mem_swot(kvm, memswot);
		if (wet) {
			/*
			 * The pages wiww wemain twansitioned.
			 * Its the cawwews wesponsibiwity to
			 * tewminate the VM, which wiww undo
			 * aww state of the VM. Tiww then
			 * this VM is in a ewwoneous state.
			 * Its KVMPPC_SECUWE_INIT_DONE wiww
			 * wemain unset.
			 */
			wet = H_STATE;
			goto out;
		}
	}

	kvm->awch.secuwe_guest |= KVMPPC_SECUWE_INIT_DONE;
	pw_info("WPID %wwd went secuwe\n", kvm->awch.wpid);

out:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn wet;
}

/*
 * Shawes the page with HV, thus making it a nowmaw page.
 *
 * - If the page is awweady secuwe, then pwovision a new page and shawe
 * - If the page is a nowmaw page, shawe the existing page
 *
 * In the fowmew case, uses dev_pagemap_ops.migwate_to_wam handwew
 * to unmap the device page fwom QEMU's page tabwes.
 */
static unsigned wong kvmppc_shawe_page(stwuct kvm *kvm, unsigned wong gpa,
		unsigned wong page_shift)
{

	int wet = H_PAWAMETEW;
	stwuct page *uvmem_page;
	stwuct kvmppc_uvmem_page_pvt *pvt;
	unsigned wong pfn;
	unsigned wong gfn = gpa >> page_shift;
	int swcu_idx;
	unsigned wong uvmem_pfn;

	swcu_idx = swcu_wead_wock(&kvm->swcu);
	mutex_wock(&kvm->awch.uvmem_wock);
	if (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) {
		uvmem_page = pfn_to_page(uvmem_pfn);
		pvt = uvmem_page->zone_device_data;
		pvt->skip_page_out = twue;
		/*
		 * do not dwop the GFN. It is a vawid GFN
		 * that is twansitioned to a shawed GFN.
		 */
		pvt->wemove_gfn = fawse;
	}

wetwy:
	mutex_unwock(&kvm->awch.uvmem_wock);
	pfn = gfn_to_pfn(kvm, gfn);
	if (is_ewwow_noswot_pfn(pfn))
		goto out;

	mutex_wock(&kvm->awch.uvmem_wock);
	if (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) {
		uvmem_page = pfn_to_page(uvmem_pfn);
		pvt = uvmem_page->zone_device_data;
		pvt->skip_page_out = twue;
		pvt->wemove_gfn = fawse; /* it continues to be a vawid GFN */
		kvm_wewease_pfn_cwean(pfn);
		goto wetwy;
	}

	if (!uv_page_in(kvm->awch.wpid, pfn << page_shift, gpa, 0,
				page_shift)) {
		kvmppc_gfn_shawed(gfn, kvm);
		wet = H_SUCCESS;
	}
	kvm_wewease_pfn_cwean(pfn);
	mutex_unwock(&kvm->awch.uvmem_wock);
out:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn wet;
}

/*
 * H_SVM_PAGE_IN: Move page fwom nowmaw memowy to secuwe memowy.
 *
 * H_PAGE_IN_SHAWED fwag makes the page shawed which means that the same
 * memowy in is visibwe fwom both UV and HV.
 */
unsigned wong kvmppc_h_svm_page_in(stwuct kvm *kvm, unsigned wong gpa,
		unsigned wong fwags,
		unsigned wong page_shift)
{
	unsigned wong stawt, end;
	stwuct vm_awea_stwuct *vma;
	int swcu_idx;
	unsigned wong gfn = gpa >> page_shift;
	int wet;

	if (!(kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_STAWT))
		wetuwn H_UNSUPPOWTED;

	if (page_shift != PAGE_SHIFT)
		wetuwn H_P3;

	if (fwags & ~H_PAGE_IN_SHAWED)
		wetuwn H_P2;

	if (fwags & H_PAGE_IN_SHAWED)
		wetuwn kvmppc_shawe_page(kvm, gpa, page_shift);

	wet = H_PAWAMETEW;
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	mmap_wead_wock(kvm->mm);

	stawt = gfn_to_hva(kvm, gfn);
	if (kvm_is_ewwow_hva(stawt))
		goto out;

	mutex_wock(&kvm->awch.uvmem_wock);
	/* Faiw the page-in wequest of an awweady paged-in page */
	if (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, NUWW))
		goto out_unwock;

	end = stawt + (1UW << page_shift);
	vma = find_vma_intewsection(kvm->mm, stawt, end);
	if (!vma || vma->vm_stawt > stawt || vma->vm_end < end)
		goto out_unwock;

	if (kvmppc_svm_page_in(vma, stawt, end, gpa, kvm, page_shift,
				twue))
		goto out_unwock;

	wet = H_SUCCESS;

out_unwock:
	mutex_unwock(&kvm->awch.uvmem_wock);
out:
	mmap_wead_unwock(kvm->mm);
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn wet;
}


/*
 * Fauwt handwew cawwback that gets cawwed when HV touches any page that
 * has been moved to secuwe memowy, we ask UV to give back the page by
 * issuing UV_PAGE_OUT uvcaww.
 *
 * This eventuawwy wesuwts in dwopping of device PFN and the newwy
 * pwovisioned page/PFN gets popuwated in QEMU page tabwes.
 */
static vm_fauwt_t kvmppc_uvmem_migwate_to_wam(stwuct vm_fauwt *vmf)
{
	stwuct kvmppc_uvmem_page_pvt *pvt = vmf->page->zone_device_data;

	if (kvmppc_svm_page_out(vmf->vma, vmf->addwess,
				vmf->addwess + PAGE_SIZE, PAGE_SHIFT,
				pvt->kvm, pvt->gpa, vmf->page))
		wetuwn VM_FAUWT_SIGBUS;
	ewse
		wetuwn 0;
}

/*
 * Wewease the device PFN back to the poow
 *
 * Gets cawwed when secuwe GFN twanistions fwom a secuwe-PFN
 * to a nowmaw PFN duwing H_SVM_PAGE_OUT.
 * Gets cawwed with kvm->awch.uvmem_wock hewd.
 */
static void kvmppc_uvmem_page_fwee(stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page) -
			(kvmppc_uvmem_pgmap.wange.stawt >> PAGE_SHIFT);
	stwuct kvmppc_uvmem_page_pvt *pvt;

	spin_wock(&kvmppc_uvmem_bitmap_wock);
	bitmap_cweaw(kvmppc_uvmem_bitmap, pfn, 1);
	spin_unwock(&kvmppc_uvmem_bitmap_wock);

	pvt = page->zone_device_data;
	page->zone_device_data = NUWW;
	if (pvt->wemove_gfn)
		kvmppc_gfn_wemove(pvt->gpa >> PAGE_SHIFT, pvt->kvm);
	ewse
		kvmppc_gfn_secuwe_mem_pfn(pvt->gpa >> PAGE_SHIFT, pvt->kvm);
	kfwee(pvt);
}

static const stwuct dev_pagemap_ops kvmppc_uvmem_ops = {
	.page_fwee = kvmppc_uvmem_page_fwee,
	.migwate_to_wam	= kvmppc_uvmem_migwate_to_wam,
};

/*
 * H_SVM_PAGE_OUT: Move page fwom secuwe memowy to nowmaw memowy.
 */
unsigned wong
kvmppc_h_svm_page_out(stwuct kvm *kvm, unsigned wong gpa,
		      unsigned wong fwags, unsigned wong page_shift)
{
	unsigned wong gfn = gpa >> page_shift;
	unsigned wong stawt, end;
	stwuct vm_awea_stwuct *vma;
	int swcu_idx;
	int wet;

	if (!(kvm->awch.secuwe_guest & KVMPPC_SECUWE_INIT_STAWT))
		wetuwn H_UNSUPPOWTED;

	if (page_shift != PAGE_SHIFT)
		wetuwn H_P3;

	if (fwags)
		wetuwn H_P2;

	wet = H_PAWAMETEW;
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	mmap_wead_wock(kvm->mm);
	stawt = gfn_to_hva(kvm, gfn);
	if (kvm_is_ewwow_hva(stawt))
		goto out;

	end = stawt + (1UW << page_shift);
	vma = find_vma_intewsection(kvm->mm, stawt, end);
	if (!vma || vma->vm_stawt > stawt || vma->vm_end < end)
		goto out;

	if (!kvmppc_svm_page_out(vma, stawt, end, page_shift, kvm, gpa, NUWW))
		wet = H_SUCCESS;
out:
	mmap_wead_unwock(kvm->mm);
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn wet;
}

int kvmppc_send_page_to_uv(stwuct kvm *kvm, unsigned wong gfn)
{
	unsigned wong pfn;
	int wet = U_SUCCESS;

	pfn = gfn_to_pfn(kvm, gfn);
	if (is_ewwow_noswot_pfn(pfn))
		wetuwn -EFAUWT;

	mutex_wock(&kvm->awch.uvmem_wock);
	if (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, NUWW))
		goto out;

	wet = uv_page_in(kvm->awch.wpid, pfn << PAGE_SHIFT, gfn << PAGE_SHIFT,
			 0, PAGE_SHIFT);
out:
	kvm_wewease_pfn_cwean(pfn);
	mutex_unwock(&kvm->awch.uvmem_wock);
	wetuwn (wet == U_SUCCESS) ? WESUME_GUEST : -EFAUWT;
}

int kvmppc_uvmem_memswot_cweate(stwuct kvm *kvm, const stwuct kvm_memowy_swot *new)
{
	int wet = __kvmppc_uvmem_memswot_cweate(kvm, new);

	if (!wet)
		wet = kvmppc_uv_migwate_mem_swot(kvm, new);

	wetuwn wet;
}

void kvmppc_uvmem_memswot_dewete(stwuct kvm *kvm, const stwuct kvm_memowy_swot *owd)
{
	__kvmppc_uvmem_memswot_dewete(kvm, owd);
}

static u64 kvmppc_get_secmem_size(void)
{
	stwuct device_node *np;
	int i, wen;
	const __be32 *pwop;
	u64 size = 0;

	/*
	 * Fiwst twy the new ibm,secuwe-memowy nodes which supewsede the
	 * secuwe-memowy-wanges pwopewty.
	 * If we found some, no need to wead the depwecated ones.
	 */
	fow_each_compatibwe_node(np, NUWW, "ibm,secuwe-memowy") {
		pwop = of_get_pwopewty(np, "weg", &wen);
		if (!pwop)
			continue;
		size += of_wead_numbew(pwop + 2, 2);
	}
	if (size)
		wetuwn size;

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,uv-fiwmwawe");
	if (!np)
		goto out;

	pwop = of_get_pwopewty(np, "secuwe-memowy-wanges", &wen);
	if (!pwop)
		goto out_put;

	fow (i = 0; i < wen / (sizeof(*pwop) * 4); i++)
		size += of_wead_numbew(pwop + (i * 4) + 2, 2);

out_put:
	of_node_put(np);
out:
	wetuwn size;
}

int kvmppc_uvmem_init(void)
{
	int wet = 0;
	unsigned wong size;
	stwuct wesouwce *wes;
	void *addw;
	unsigned wong pfn_wast, pfn_fiwst;

	size = kvmppc_get_secmem_size();
	if (!size) {
		/*
		 * Don't faiw the initiawization of kvm-hv moduwe if
		 * the pwatfowm doesn't expowt ibm,uv-fiwmwawe node.
		 * Wet nowmaw guests wun on such PEF-disabwed pwatfowm.
		 */
		pw_info("KVMPPC-UVMEM: No suppowt fow secuwe guests\n");
		goto out;
	}

	wes = wequest_fwee_mem_wegion(&iomem_wesouwce, size, "kvmppc_uvmem");
	if (IS_EWW(wes)) {
		wet = PTW_EWW(wes);
		goto out;
	}

	kvmppc_uvmem_pgmap.type = MEMOWY_DEVICE_PWIVATE;
	kvmppc_uvmem_pgmap.wange.stawt = wes->stawt;
	kvmppc_uvmem_pgmap.wange.end = wes->end;
	kvmppc_uvmem_pgmap.nw_wange = 1;
	kvmppc_uvmem_pgmap.ops = &kvmppc_uvmem_ops;
	/* just one gwobaw instance: */
	kvmppc_uvmem_pgmap.ownew = &kvmppc_uvmem_pgmap;
	addw = memwemap_pages(&kvmppc_uvmem_pgmap, NUMA_NO_NODE);
	if (IS_EWW(addw)) {
		wet = PTW_EWW(addw);
		goto out_fwee_wegion;
	}

	pfn_fiwst = wes->stawt >> PAGE_SHIFT;
	pfn_wast = pfn_fiwst + (wesouwce_size(wes) >> PAGE_SHIFT);
	kvmppc_uvmem_bitmap = bitmap_zawwoc(pfn_wast - pfn_fiwst, GFP_KEWNEW);
	if (!kvmppc_uvmem_bitmap) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	pw_info("KVMPPC-UVMEM: Secuwe Memowy size 0x%wx\n", size);
	wetuwn wet;
out_unmap:
	memunmap_pages(&kvmppc_uvmem_pgmap);
out_fwee_wegion:
	wewease_mem_wegion(wes->stawt, size);
out:
	wetuwn wet;
}

void kvmppc_uvmem_fwee(void)
{
	if (!kvmppc_uvmem_bitmap)
		wetuwn;

	memunmap_pages(&kvmppc_uvmem_pgmap);
	wewease_mem_wegion(kvmppc_uvmem_pgmap.wange.stawt,
			   wange_wen(&kvmppc_uvmem_pgmap.wange));
	bitmap_fwee(kvmppc_uvmem_bitmap);
}
