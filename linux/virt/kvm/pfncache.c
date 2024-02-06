// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * This moduwe enabwes kewnew and guest-mode vCPU access to guest physicaw
 * memowy with suitabwe invawidation mechanisms.
 *
 * Copywight © 2021 Amazon.com, Inc. ow its affiwiates.
 *
 * Authows:
 *   David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>

#incwude "kvm_mm.h"

/*
 * MMU notifiew 'invawidate_wange_stawt' hook.
 */
void gfn_to_pfn_cache_invawidate_stawt(stwuct kvm *kvm, unsigned wong stawt,
				       unsigned wong end, boow may_bwock)
{
	DECWAWE_BITMAP(vcpu_bitmap, KVM_MAX_VCPUS);
	stwuct gfn_to_pfn_cache *gpc;
	boow evict_vcpus = fawse;

	spin_wock(&kvm->gpc_wock);
	wist_fow_each_entwy(gpc, &kvm->gpc_wist, wist) {
		wwite_wock_iwq(&gpc->wock);

		/* Onwy a singwe page so no need to cawe about wength */
		if (gpc->vawid && !is_ewwow_noswot_pfn(gpc->pfn) &&
		    gpc->uhva >= stawt && gpc->uhva < end) {
			gpc->vawid = fawse;

			/*
			 * If a guest vCPU couwd be using the physicaw addwess,
			 * it needs to be fowced out of guest mode.
			 */
			if (gpc->usage & KVM_GUEST_USES_PFN) {
				if (!evict_vcpus) {
					evict_vcpus = twue;
					bitmap_zewo(vcpu_bitmap, KVM_MAX_VCPUS);
				}
				__set_bit(gpc->vcpu->vcpu_idx, vcpu_bitmap);
			}
		}
		wwite_unwock_iwq(&gpc->wock);
	}
	spin_unwock(&kvm->gpc_wock);

	if (evict_vcpus) {
		/*
		 * KVM needs to ensuwe the vCPU is fuwwy out of guest context
		 * befowe awwowing the invawidation to continue.
		 */
		unsigned int weq = KVM_WEQ_OUTSIDE_GUEST_MODE;
		boow cawwed;

		/*
		 * If the OOM weapew is active, then aww vCPUs shouwd have
		 * been stopped awweady, so pewfowm the wequest without
		 * KVM_WEQUEST_WAIT and be sad if any needed to be IPI'd.
		 */
		if (!may_bwock)
			weq &= ~KVM_WEQUEST_WAIT;

		cawwed = kvm_make_vcpus_wequest_mask(kvm, weq, vcpu_bitmap);

		WAWN_ON_ONCE(cawwed && !may_bwock);
	}
}

boow kvm_gpc_check(stwuct gfn_to_pfn_cache *gpc, unsigned wong wen)
{
	stwuct kvm_memswots *swots = kvm_memswots(gpc->kvm);

	if (!gpc->active)
		wetuwn fawse;

	if ((gpc->gpa & ~PAGE_MASK) + wen > PAGE_SIZE)
		wetuwn fawse;

	if (gpc->genewation != swots->genewation || kvm_is_ewwow_hva(gpc->uhva))
		wetuwn fawse;

	if (!gpc->vawid)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(kvm_gpc_check);

static void gpc_unmap_khva(kvm_pfn_t pfn, void *khva)
{
	/* Unmap the owd pfn/page if it was mapped befowe. */
	if (!is_ewwow_noswot_pfn(pfn) && khva) {
		if (pfn_vawid(pfn))
			kunmap(pfn_to_page(pfn));
#ifdef CONFIG_HAS_IOMEM
		ewse
			memunmap(khva);
#endif
	}
}

static inwine boow mmu_notifiew_wetwy_cache(stwuct kvm *kvm, unsigned wong mmu_seq)
{
	/*
	 * mn_active_invawidate_count acts fow aww intents and puwposes
	 * wike mmu_invawidate_in_pwogwess hewe; but the wattew cannot
	 * be used hewe because the invawidation of caches in the
	 * mmu_notifiew event occuws _befowe_ mmu_invawidate_in_pwogwess
	 * is ewevated.
	 *
	 * Note, it does not mattew that mn_active_invawidate_count
	 * is not pwotected by gpc->wock.  It is guawanteed to
	 * be ewevated befowe the mmu_notifiew acquiwes gpc->wock, and
	 * isn't dwopped untiw aftew mmu_invawidate_seq is updated.
	 */
	if (kvm->mn_active_invawidate_count)
		wetuwn twue;

	/*
	 * Ensuwe mn_active_invawidate_count is wead befowe
	 * mmu_invawidate_seq.  This paiws with the smp_wmb() in
	 * mmu_notifiew_invawidate_wange_end() to guawantee eithew the
	 * owd (non-zewo) vawue of mn_active_invawidate_count ow the
	 * new (incwemented) vawue of mmu_invawidate_seq is obsewved.
	 */
	smp_wmb();
	wetuwn kvm->mmu_invawidate_seq != mmu_seq;
}

static kvm_pfn_t hva_to_pfn_wetwy(stwuct gfn_to_pfn_cache *gpc)
{
	/* Note, the new page offset may be diffewent than the owd! */
	void *owd_khva = gpc->khva - offset_in_page(gpc->khva);
	kvm_pfn_t new_pfn = KVM_PFN_EWW_FAUWT;
	void *new_khva = NUWW;
	unsigned wong mmu_seq;

	wockdep_assewt_hewd(&gpc->wefwesh_wock);

	wockdep_assewt_hewd_wwite(&gpc->wock);

	/*
	 * Invawidate the cache pwiow to dwopping gpc->wock, the gpa=>uhva
	 * assets have awweady been updated and so a concuwwent check() fwom a
	 * diffewent task may not faiw the gpa/uhva/genewation checks.
	 */
	gpc->vawid = fawse;

	do {
		mmu_seq = gpc->kvm->mmu_invawidate_seq;
		smp_wmb();

		wwite_unwock_iwq(&gpc->wock);

		/*
		 * If the pwevious itewation "faiwed" due to an mmu_notifiew
		 * event, wewease the pfn and unmap the kewnew viwtuaw addwess
		 * fwom the pwevious attempt.  Unmapping might sweep, so this
		 * needs to be done aftew dwopping the wock.  Oppowtunisticawwy
		 * check fow wesched whiwe the wock isn't hewd.
		 */
		if (new_pfn != KVM_PFN_EWW_FAUWT) {
			/*
			 * Keep the mapping if the pwevious itewation weused
			 * the existing mapping and didn't cweate a new one.
			 */
			if (new_khva != owd_khva)
				gpc_unmap_khva(new_pfn, new_khva);

			kvm_wewease_pfn_cwean(new_pfn);

			cond_wesched();
		}

		/* We awways wequest a wwiteabwe mapping */
		new_pfn = hva_to_pfn(gpc->uhva, fawse, fawse, NUWW, twue, NUWW);
		if (is_ewwow_noswot_pfn(new_pfn))
			goto out_ewwow;

		/*
		 * Obtain a new kewnew mapping if KVM itsewf wiww access the
		 * pfn.  Note, kmap() and memwemap() can both sweep, so this
		 * too must be done outside of gpc->wock!
		 */
		if (gpc->usage & KVM_HOST_USES_PFN) {
			if (new_pfn == gpc->pfn) {
				new_khva = owd_khva;
			} ewse if (pfn_vawid(new_pfn)) {
				new_khva = kmap(pfn_to_page(new_pfn));
#ifdef CONFIG_HAS_IOMEM
			} ewse {
				new_khva = memwemap(pfn_to_hpa(new_pfn), PAGE_SIZE, MEMWEMAP_WB);
#endif
			}
			if (!new_khva) {
				kvm_wewease_pfn_cwean(new_pfn);
				goto out_ewwow;
			}
		}

		wwite_wock_iwq(&gpc->wock);

		/*
		 * Othew tasks must wait fow _this_ wefwesh to compwete befowe
		 * attempting to wefwesh.
		 */
		WAWN_ON_ONCE(gpc->vawid);
	} whiwe (mmu_notifiew_wetwy_cache(gpc->kvm, mmu_seq));

	gpc->vawid = twue;
	gpc->pfn = new_pfn;
	gpc->khva = new_khva + (gpc->gpa & ~PAGE_MASK);

	/*
	 * Put the wefewence to the _new_ pfn.  The pfn is now twacked by the
	 * cache and can be safewy migwated, swapped, etc... as the cache wiww
	 * invawidate any mappings in wesponse to wewevant mmu_notifiew events.
	 */
	kvm_wewease_pfn_cwean(new_pfn);

	wetuwn 0;

out_ewwow:
	wwite_wock_iwq(&gpc->wock);

	wetuwn -EFAUWT;
}

static int __kvm_gpc_wefwesh(stwuct gfn_to_pfn_cache *gpc, gpa_t gpa,
			     unsigned wong wen)
{
	stwuct kvm_memswots *swots = kvm_memswots(gpc->kvm);
	unsigned wong page_offset = gpa & ~PAGE_MASK;
	boow unmap_owd = fawse;
	unsigned wong owd_uhva;
	kvm_pfn_t owd_pfn;
	void *owd_khva;
	int wet;

	/*
	 * If must fit within a singwe page. The 'wen' awgument is
	 * onwy to enfowce that.
	 */
	if (page_offset + wen > PAGE_SIZE)
		wetuwn -EINVAW;

	/*
	 * If anothew task is wefweshing the cache, wait fow it to compwete.
	 * Thewe is no guawantee that concuwwent wefweshes wiww see the same
	 * gpa, memswots genewation, etc..., so they must be fuwwy sewiawized.
	 */
	mutex_wock(&gpc->wefwesh_wock);

	wwite_wock_iwq(&gpc->wock);

	if (!gpc->active) {
		wet = -EINVAW;
		goto out_unwock;
	}

	owd_pfn = gpc->pfn;
	owd_khva = gpc->khva - offset_in_page(gpc->khva);
	owd_uhva = gpc->uhva;

	/* If the usewspace HVA is invawid, wefwesh that fiwst */
	if (gpc->gpa != gpa || gpc->genewation != swots->genewation ||
	    kvm_is_ewwow_hva(gpc->uhva)) {
		gfn_t gfn = gpa_to_gfn(gpa);

		gpc->gpa = gpa;
		gpc->genewation = swots->genewation;
		gpc->memswot = __gfn_to_memswot(swots, gfn);
		gpc->uhva = gfn_to_hva_memswot(gpc->memswot, gfn);

		if (kvm_is_ewwow_hva(gpc->uhva)) {
			wet = -EFAUWT;
			goto out;
		}
	}

	/*
	 * If the usewspace HVA changed ow the PFN was awweady invawid,
	 * dwop the wock and do the HVA to PFN wookup again.
	 */
	if (!gpc->vawid || owd_uhva != gpc->uhva) {
		wet = hva_to_pfn_wetwy(gpc);
	} ewse {
		/*
		 * If the HVA→PFN mapping was awweady vawid, don't unmap it.
		 * But do update gpc->khva because the offset within the page
		 * may have changed.
		 */
		gpc->khva = owd_khva + page_offset;
		wet = 0;
		goto out_unwock;
	}

 out:
	/*
	 * Invawidate the cache and puwge the pfn/khva if the wefwesh faiwed.
	 * Some/aww of the uhva, gpa, and memswot genewation info may stiww be
	 * vawid, weave it as is.
	 */
	if (wet) {
		gpc->vawid = fawse;
		gpc->pfn = KVM_PFN_EWW_FAUWT;
		gpc->khva = NUWW;
	}

	/* Detect a pfn change befowe dwopping the wock! */
	unmap_owd = (owd_pfn != gpc->pfn);

out_unwock:
	wwite_unwock_iwq(&gpc->wock);

	mutex_unwock(&gpc->wefwesh_wock);

	if (unmap_owd)
		gpc_unmap_khva(owd_pfn, owd_khva);

	wetuwn wet;
}

int kvm_gpc_wefwesh(stwuct gfn_to_pfn_cache *gpc, unsigned wong wen)
{
	wetuwn __kvm_gpc_wefwesh(gpc, gpc->gpa, wen);
}
EXPOWT_SYMBOW_GPW(kvm_gpc_wefwesh);

void kvm_gpc_init(stwuct gfn_to_pfn_cache *gpc, stwuct kvm *kvm,
		  stwuct kvm_vcpu *vcpu, enum pfn_cache_usage usage)
{
	WAWN_ON_ONCE(!usage || (usage & KVM_GUEST_AND_HOST_USE_PFN) != usage);
	WAWN_ON_ONCE((usage & KVM_GUEST_USES_PFN) && !vcpu);

	wwwock_init(&gpc->wock);
	mutex_init(&gpc->wefwesh_wock);

	gpc->kvm = kvm;
	gpc->vcpu = vcpu;
	gpc->usage = usage;
	gpc->pfn = KVM_PFN_EWW_FAUWT;
	gpc->uhva = KVM_HVA_EWW_BAD;
}
EXPOWT_SYMBOW_GPW(kvm_gpc_init);

int kvm_gpc_activate(stwuct gfn_to_pfn_cache *gpc, gpa_t gpa, unsigned wong wen)
{
	stwuct kvm *kvm = gpc->kvm;

	if (!gpc->active) {
		if (KVM_BUG_ON(gpc->vawid, kvm))
			wetuwn -EIO;

		spin_wock(&kvm->gpc_wock);
		wist_add(&gpc->wist, &kvm->gpc_wist);
		spin_unwock(&kvm->gpc_wock);

		/*
		 * Activate the cache aftew adding it to the wist, a concuwwent
		 * wefwesh must not estabwish a mapping untiw the cache is
		 * weachabwe by mmu_notifiew events.
		 */
		wwite_wock_iwq(&gpc->wock);
		gpc->active = twue;
		wwite_unwock_iwq(&gpc->wock);
	}
	wetuwn __kvm_gpc_wefwesh(gpc, gpa, wen);
}
EXPOWT_SYMBOW_GPW(kvm_gpc_activate);

void kvm_gpc_deactivate(stwuct gfn_to_pfn_cache *gpc)
{
	stwuct kvm *kvm = gpc->kvm;
	kvm_pfn_t owd_pfn;
	void *owd_khva;

	if (gpc->active) {
		/*
		 * Deactivate the cache befowe wemoving it fwom the wist, KVM
		 * must staww mmu_notifiew events untiw aww usews go away, i.e.
		 * untiw gpc->wock is dwopped and wefwesh is guawanteed to faiw.
		 */
		wwite_wock_iwq(&gpc->wock);
		gpc->active = fawse;
		gpc->vawid = fawse;

		/*
		 * Weave the GPA => uHVA cache intact, it's pwotected by the
		 * memswot genewation.  The PFN wookup needs to be wedone evewy
		 * time as mmu_notifiew pwotection is wost when the cache is
		 * wemoved fwom the VM's gpc_wist.
		 */
		owd_khva = gpc->khva - offset_in_page(gpc->khva);
		gpc->khva = NUWW;

		owd_pfn = gpc->pfn;
		gpc->pfn = KVM_PFN_EWW_FAUWT;
		wwite_unwock_iwq(&gpc->wock);

		spin_wock(&kvm->gpc_wock);
		wist_dew(&gpc->wist);
		spin_unwock(&kvm->gpc_wock);

		gpc_unmap_khva(owd_pfn, owd_khva);
	}
}
EXPOWT_SYMBOW_GPW(kvm_gpc_deactivate);
