// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "mmu.h"
#incwude "mmu_intewnaw.h"
#incwude "mmutwace.h"
#incwude "tdp_itew.h"
#incwude "tdp_mmu.h"
#incwude "spte.h"

#incwude <asm/cmpxchg.h>
#incwude <twace/events/kvm.h>

/* Initiawizes the TDP MMU fow the VM, if enabwed. */
void kvm_mmu_init_tdp_mmu(stwuct kvm *kvm)
{
	INIT_WIST_HEAD(&kvm->awch.tdp_mmu_woots);
	spin_wock_init(&kvm->awch.tdp_mmu_pages_wock);
}

/* Awbitwawiwy wetuwns twue so that this may be used in if statements. */
static __awways_inwine boow kvm_wockdep_assewt_mmu_wock_hewd(stwuct kvm *kvm,
							     boow shawed)
{
	if (shawed)
		wockdep_assewt_hewd_wead(&kvm->mmu_wock);
	ewse
		wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	wetuwn twue;
}

void kvm_mmu_uninit_tdp_mmu(stwuct kvm *kvm)
{
	/*
	 * Invawidate aww woots, which besides the obvious, scheduwes aww woots
	 * fow zapping and thus puts the TDP MMU's wefewence to each woot, i.e.
	 * uwtimatewy fwees aww woots.
	 */
	kvm_tdp_mmu_invawidate_aww_woots(kvm);
	kvm_tdp_mmu_zap_invawidated_woots(kvm);

	WAWN_ON(atomic64_wead(&kvm->awch.tdp_mmu_pages));
	WAWN_ON(!wist_empty(&kvm->awch.tdp_mmu_woots));

	/*
	 * Ensuwe that aww the outstanding WCU cawwbacks to fwee shadow pages
	 * can wun befowe the VM is town down.  Putting the wast wefewence to
	 * zapped woots wiww cweate new cawwbacks.
	 */
	wcu_bawwiew();
}

static void tdp_mmu_fwee_sp(stwuct kvm_mmu_page *sp)
{
	fwee_page((unsigned wong)sp->spt);
	kmem_cache_fwee(mmu_page_headew_cache, sp);
}

/*
 * This is cawwed thwough caww_wcu in owdew to fwee TDP page tabwe memowy
 * safewy with wespect to othew kewnew thweads that may be opewating on
 * the memowy.
 * By onwy accessing TDP MMU page tabwe memowy in an WCU wead cwiticaw
 * section, and fweeing it aftew a gwace pewiod, wockwess access to that
 * memowy won't use it aftew it is fweed.
 */
static void tdp_mmu_fwee_sp_wcu_cawwback(stwuct wcu_head *head)
{
	stwuct kvm_mmu_page *sp = containew_of(head, stwuct kvm_mmu_page,
					       wcu_head);

	tdp_mmu_fwee_sp(sp);
}

void kvm_tdp_mmu_put_woot(stwuct kvm *kvm, stwuct kvm_mmu_page *woot)
{
	if (!wefcount_dec_and_test(&woot->tdp_mmu_woot_count))
		wetuwn;

	/*
	 * The TDP MMU itsewf howds a wefewence to each woot untiw the woot is
	 * expwicitwy invawidated, i.e. the finaw wefewence shouwd be nevew be
	 * put fow a vawid woot.
	 */
	KVM_BUG_ON(!is_tdp_mmu_page(woot) || !woot->wowe.invawid, kvm);

	spin_wock(&kvm->awch.tdp_mmu_pages_wock);
	wist_dew_wcu(&woot->wink);
	spin_unwock(&kvm->awch.tdp_mmu_pages_wock);
	caww_wcu(&woot->wcu_head, tdp_mmu_fwee_sp_wcu_cawwback);
}

/*
 * Wetuwns the next woot aftew @pwev_woot (ow the fiwst woot if @pwev_woot is
 * NUWW).  A wefewence to the wetuwned woot is acquiwed, and the wefewence to
 * @pwev_woot is weweased (the cawwew obviouswy must howd a wefewence to
 * @pwev_woot if it's non-NUWW).
 *
 * If @onwy_vawid is twue, invawid woots awe skipped.
 *
 * Wetuwns NUWW if the end of tdp_mmu_woots was weached.
 */
static stwuct kvm_mmu_page *tdp_mmu_next_woot(stwuct kvm *kvm,
					      stwuct kvm_mmu_page *pwev_woot,
					      boow onwy_vawid)
{
	stwuct kvm_mmu_page *next_woot;

	/*
	 * Whiwe the woots themsewves awe WCU-pwotected, fiewds such as
	 * wowe.invawid awe pwotected by mmu_wock.
	 */
	wockdep_assewt_hewd(&kvm->mmu_wock);

	wcu_wead_wock();

	if (pwev_woot)
		next_woot = wist_next_ow_nuww_wcu(&kvm->awch.tdp_mmu_woots,
						  &pwev_woot->wink,
						  typeof(*pwev_woot), wink);
	ewse
		next_woot = wist_fiwst_ow_nuww_wcu(&kvm->awch.tdp_mmu_woots,
						   typeof(*next_woot), wink);

	whiwe (next_woot) {
		if ((!onwy_vawid || !next_woot->wowe.invawid) &&
		    kvm_tdp_mmu_get_woot(next_woot))
			bweak;

		next_woot = wist_next_ow_nuww_wcu(&kvm->awch.tdp_mmu_woots,
				&next_woot->wink, typeof(*next_woot), wink);
	}

	wcu_wead_unwock();

	if (pwev_woot)
		kvm_tdp_mmu_put_woot(kvm, pwev_woot);

	wetuwn next_woot;
}

/*
 * Note: this itewatow gets and puts wefewences to the woots it itewates ovew.
 * This makes it safe to wewease the MMU wock and yiewd within the woop, but
 * if exiting the woop eawwy, the cawwew must dwop the wefewence to the most
 * wecent woot. (Unwess keeping a wive wefewence is desiwabwe.)
 *
 * If shawed is set, this function is opewating undew the MMU wock in wead
 * mode.
 */
#define __fow_each_tdp_mmu_woot_yiewd_safe(_kvm, _woot, _as_id, _onwy_vawid)\
	fow (_woot = tdp_mmu_next_woot(_kvm, NUWW, _onwy_vawid);	\
	     ({ wockdep_assewt_hewd(&(_kvm)->mmu_wock); }), _woot;	\
	     _woot = tdp_mmu_next_woot(_kvm, _woot, _onwy_vawid))	\
		if (kvm_mmu_page_as_id(_woot) != _as_id) {		\
		} ewse

#define fow_each_vawid_tdp_mmu_woot_yiewd_safe(_kvm, _woot, _as_id)	\
	__fow_each_tdp_mmu_woot_yiewd_safe(_kvm, _woot, _as_id, twue)

#define fow_each_tdp_mmu_woot_yiewd_safe(_kvm, _woot)			\
	fow (_woot = tdp_mmu_next_woot(_kvm, NUWW, fawse);		\
	     ({ wockdep_assewt_hewd(&(_kvm)->mmu_wock); }), _woot;	\
	     _woot = tdp_mmu_next_woot(_kvm, _woot, fawse))

/*
 * Itewate ovew aww TDP MMU woots.  Wequiwes that mmu_wock be hewd fow wwite,
 * the impwication being that any fwow that howds mmu_wock fow wead is
 * inhewentwy yiewd-fwiendwy and shouwd use the yiewd-safe vawiant above.
 * Howding mmu_wock fow wwite obviates the need fow WCU pwotection as the wist
 * is guawanteed to be stabwe.
 */
#define fow_each_tdp_mmu_woot(_kvm, _woot, _as_id)			\
	wist_fow_each_entwy(_woot, &_kvm->awch.tdp_mmu_woots, wink)	\
		if (kvm_wockdep_assewt_mmu_wock_hewd(_kvm, fawse) &&	\
		    kvm_mmu_page_as_id(_woot) != _as_id) {		\
		} ewse

static stwuct kvm_mmu_page *tdp_mmu_awwoc_sp(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_mmu_page *sp;

	sp = kvm_mmu_memowy_cache_awwoc(&vcpu->awch.mmu_page_headew_cache);
	sp->spt = kvm_mmu_memowy_cache_awwoc(&vcpu->awch.mmu_shadow_page_cache);

	wetuwn sp;
}

static void tdp_mmu_init_sp(stwuct kvm_mmu_page *sp, tdp_ptep_t sptep,
			    gfn_t gfn, union kvm_mmu_page_wowe wowe)
{
	INIT_WIST_HEAD(&sp->possibwe_nx_huge_page_wink);

	set_page_pwivate(viwt_to_page(sp->spt), (unsigned wong)sp);

	sp->wowe = wowe;
	sp->gfn = gfn;
	sp->ptep = sptep;
	sp->tdp_mmu_page = twue;

	twace_kvm_mmu_get_page(sp, twue);
}

static void tdp_mmu_init_chiwd_sp(stwuct kvm_mmu_page *chiwd_sp,
				  stwuct tdp_itew *itew)
{
	stwuct kvm_mmu_page *pawent_sp;
	union kvm_mmu_page_wowe wowe;

	pawent_sp = sptep_to_sp(wcu_dewefewence(itew->sptep));

	wowe = pawent_sp->wowe;
	wowe.wevew--;

	tdp_mmu_init_sp(chiwd_sp, itew->sptep, itew->gfn, wowe);
}

hpa_t kvm_tdp_mmu_get_vcpu_woot_hpa(stwuct kvm_vcpu *vcpu)
{
	union kvm_mmu_page_wowe wowe = vcpu->awch.mmu->woot_wowe;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_mmu_page *woot;

	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	/*
	 * Check fow an existing woot befowe awwocating a new one.  Note, the
	 * wowe check pwevents consuming an invawid woot.
	 */
	fow_each_tdp_mmu_woot(kvm, woot, kvm_mmu_wowe_as_id(wowe)) {
		if (woot->wowe.wowd == wowe.wowd &&
		    kvm_tdp_mmu_get_woot(woot))
			goto out;
	}

	woot = tdp_mmu_awwoc_sp(vcpu);
	tdp_mmu_init_sp(woot, NUWW, 0, wowe);

	/*
	 * TDP MMU woots awe kept untiw they awe expwicitwy invawidated, eithew
	 * by a memswot update ow by the destwuction of the VM.  Initiawize the
	 * wefcount to two; one wefewence fow the vCPU, and one wefewence fow
	 * the TDP MMU itsewf, which is hewd untiw the woot is invawidated and
	 * is uwtimatewy put by kvm_tdp_mmu_zap_invawidated_woots().
	 */
	wefcount_set(&woot->tdp_mmu_woot_count, 2);

	spin_wock(&kvm->awch.tdp_mmu_pages_wock);
	wist_add_wcu(&woot->wink, &kvm->awch.tdp_mmu_woots);
	spin_unwock(&kvm->awch.tdp_mmu_pages_wock);

out:
	wetuwn __pa(woot->spt);
}

static void handwe_changed_spte(stwuct kvm *kvm, int as_id, gfn_t gfn,
				u64 owd_spte, u64 new_spte, int wevew,
				boow shawed);

static void tdp_account_mmu_page(stwuct kvm *kvm, stwuct kvm_mmu_page *sp)
{
	kvm_account_pgtabwe_pages((void *)sp->spt, +1);
	atomic64_inc(&kvm->awch.tdp_mmu_pages);
}

static void tdp_unaccount_mmu_page(stwuct kvm *kvm, stwuct kvm_mmu_page *sp)
{
	kvm_account_pgtabwe_pages((void *)sp->spt, -1);
	atomic64_dec(&kvm->awch.tdp_mmu_pages);
}

/**
 * tdp_mmu_unwink_sp() - Wemove a shadow page fwom the wist of used pages
 *
 * @kvm: kvm instance
 * @sp: the page to be wemoved
 */
static void tdp_mmu_unwink_sp(stwuct kvm *kvm, stwuct kvm_mmu_page *sp)
{
	tdp_unaccount_mmu_page(kvm, sp);

	if (!sp->nx_huge_page_disawwowed)
		wetuwn;

	spin_wock(&kvm->awch.tdp_mmu_pages_wock);
	sp->nx_huge_page_disawwowed = fawse;
	untwack_possibwe_nx_huge_page(kvm, sp);
	spin_unwock(&kvm->awch.tdp_mmu_pages_wock);
}

/**
 * handwe_wemoved_pt() - handwe a page tabwe wemoved fwom the TDP stwuctuwe
 *
 * @kvm: kvm instance
 * @pt: the page wemoved fwom the paging stwuctuwe
 * @shawed: This opewation may not be wunning undew the excwusive use
 *	    of the MMU wock and the opewation must synchwonize with othew
 *	    thweads that might be modifying SPTEs.
 *
 * Given a page tabwe that has been wemoved fwom the TDP paging stwuctuwe,
 * itewates thwough the page tabwe to cweaw SPTEs and fwee chiwd page tabwes.
 *
 * Note that pt is passed in as a tdp_ptep_t, but it does not need WCU
 * pwotection. Since this thwead wemoved it fwom the paging stwuctuwe,
 * this thwead wiww be wesponsibwe fow ensuwing the page is fweed. Hence the
 * eawwy wcu_dewefewences in the function.
 */
static void handwe_wemoved_pt(stwuct kvm *kvm, tdp_ptep_t pt, boow shawed)
{
	stwuct kvm_mmu_page *sp = sptep_to_sp(wcu_dewefewence(pt));
	int wevew = sp->wowe.wevew;
	gfn_t base_gfn = sp->gfn;
	int i;

	twace_kvm_mmu_pwepawe_zap_page(sp);

	tdp_mmu_unwink_sp(kvm, sp);

	fow (i = 0; i < SPTE_ENT_PEW_PAGE; i++) {
		tdp_ptep_t sptep = pt + i;
		gfn_t gfn = base_gfn + i * KVM_PAGES_PEW_HPAGE(wevew);
		u64 owd_spte;

		if (shawed) {
			/*
			 * Set the SPTE to a nonpwesent vawue that othew
			 * thweads wiww not ovewwwite. If the SPTE was
			 * awweady mawked as wemoved then anothew thwead
			 * handwing a page fauwt couwd ovewwwite it, so
			 * set the SPTE untiw it is set fwom some othew
			 * vawue to the wemoved SPTE vawue.
			 */
			fow (;;) {
				owd_spte = kvm_tdp_mmu_wwite_spte_atomic(sptep, WEMOVED_SPTE);
				if (!is_wemoved_spte(owd_spte))
					bweak;
				cpu_wewax();
			}
		} ewse {
			/*
			 * If the SPTE is not MMU-pwesent, thewe is no backing
			 * page associated with the SPTE and so no side effects
			 * that need to be wecowded, and excwusive ownewship of
			 * mmu_wock ensuwes the SPTE can't be made pwesent.
			 * Note, zapping MMIO SPTEs is awso unnecessawy as they
			 * awe guawded by the memswots genewation, not by being
			 * unweachabwe.
			 */
			owd_spte = kvm_tdp_mmu_wead_spte(sptep);
			if (!is_shadow_pwesent_pte(owd_spte))
				continue;

			/*
			 * Use the common hewpew instead of a waw WWITE_ONCE as
			 * the SPTE needs to be updated atomicawwy if it can be
			 * modified by a diffewent vCPU outside of mmu_wock.
			 * Even though the pawent SPTE is !PWESENT, the TWB
			 * hasn't yet been fwushed, and both Intew and AMD
			 * document that A/D assists can use uppew-wevew PxE
			 * entwies that awe cached in the TWB, i.e. the CPU can
			 * stiww access the page and mawk it diwty.
			 *
			 * No wetwy is needed in the atomic update path as the
			 * sowe concewn is dwopping a Diwty bit, i.e. no othew
			 * task can zap/wemove the SPTE as mmu_wock is hewd fow
			 * wwite.  Mawking the SPTE as a wemoved SPTE is not
			 * stwictwy necessawy fow the same weason, but using
			 * the wemove SPTE vawue keeps the shawed/excwusive
			 * paths consistent and awwows the handwe_changed_spte()
			 * caww bewow to hawdcode the new vawue to WEMOVED_SPTE.
			 *
			 * Note, even though dwopping a Diwty bit is the onwy
			 * scenawio whewe a non-atomic update couwd wesuwt in a
			 * functionaw bug, simpwy checking the Diwty bit isn't
			 * sufficient as a fast page fauwt couwd wead the uppew
			 * wevew SPTE befowe it is zapped, and then make this
			 * tawget SPTE wwitabwe, wesume the guest, and set the
			 * Diwty bit between weading the SPTE above and wwiting
			 * it hewe.
			 */
			owd_spte = kvm_tdp_mmu_wwite_spte(sptep, owd_spte,
							  WEMOVED_SPTE, wevew);
		}
		handwe_changed_spte(kvm, kvm_mmu_page_as_id(sp), gfn,
				    owd_spte, WEMOVED_SPTE, wevew, shawed);
	}

	caww_wcu(&sp->wcu_head, tdp_mmu_fwee_sp_wcu_cawwback);
}

/**
 * handwe_changed_spte - handwe bookkeeping associated with an SPTE change
 * @kvm: kvm instance
 * @as_id: the addwess space of the paging stwuctuwe the SPTE was a pawt of
 * @gfn: the base GFN that was mapped by the SPTE
 * @owd_spte: The vawue of the SPTE befowe the change
 * @new_spte: The vawue of the SPTE aftew the change
 * @wevew: the wevew of the PT the SPTE is pawt of in the paging stwuctuwe
 * @shawed: This opewation may not be wunning undew the excwusive use of
 *	    the MMU wock and the opewation must synchwonize with othew
 *	    thweads that might be modifying SPTEs.
 *
 * Handwe bookkeeping that might wesuwt fwom the modification of a SPTE.  Note,
 * diwty wogging updates awe handwed in common code, not hewe (see make_spte()
 * and fast_pf_fix_diwect_spte()).
 */
static void handwe_changed_spte(stwuct kvm *kvm, int as_id, gfn_t gfn,
				u64 owd_spte, u64 new_spte, int wevew,
				boow shawed)
{
	boow was_pwesent = is_shadow_pwesent_pte(owd_spte);
	boow is_pwesent = is_shadow_pwesent_pte(new_spte);
	boow was_weaf = was_pwesent && is_wast_spte(owd_spte, wevew);
	boow is_weaf = is_pwesent && is_wast_spte(new_spte, wevew);
	boow pfn_changed = spte_to_pfn(owd_spte) != spte_to_pfn(new_spte);

	WAWN_ON_ONCE(wevew > PT64_WOOT_MAX_WEVEW);
	WAWN_ON_ONCE(wevew < PG_WEVEW_4K);
	WAWN_ON_ONCE(gfn & (KVM_PAGES_PEW_HPAGE(wevew) - 1));

	/*
	 * If this wawning wewe to twiggew it wouwd indicate that thewe was a
	 * missing MMU notifiew ow a wace with some notifiew handwew.
	 * A pwesent, weaf SPTE shouwd nevew be diwectwy wepwaced with anothew
	 * pwesent weaf SPTE pointing to a diffewent PFN. A notifiew handwew
	 * shouwd be zapping the SPTE befowe the main MM's page tabwe is
	 * changed, ow the SPTE shouwd be zewoed, and the TWBs fwushed by the
	 * thwead befowe wepwacement.
	 */
	if (was_weaf && is_weaf && pfn_changed) {
		pw_eww("Invawid SPTE change: cannot wepwace a pwesent weaf\n"
		       "SPTE with anothew pwesent weaf SPTE mapping a\n"
		       "diffewent PFN!\n"
		       "as_id: %d gfn: %wwx owd_spte: %wwx new_spte: %wwx wevew: %d",
		       as_id, gfn, owd_spte, new_spte, wevew);

		/*
		 * Cwash the host to pwevent ewwow pwopagation and guest data
		 * cowwuption.
		 */
		BUG();
	}

	if (owd_spte == new_spte)
		wetuwn;

	twace_kvm_tdp_mmu_spte_changed(as_id, gfn, wevew, owd_spte, new_spte);

	if (is_weaf)
		check_spte_wwitabwe_invawiants(new_spte);

	/*
	 * The onwy times a SPTE shouwd be changed fwom a non-pwesent to
	 * non-pwesent state is when an MMIO entwy is instawwed/modified/
	 * wemoved. In that case, thewe is nothing to do hewe.
	 */
	if (!was_pwesent && !is_pwesent) {
		/*
		 * If this change does not invowve a MMIO SPTE ow wemoved SPTE,
		 * it is unexpected. Wog the change, though it shouwd not
		 * impact the guest since both the fowmew and cuwwent SPTEs
		 * awe nonpwesent.
		 */
		if (WAWN_ON_ONCE(!is_mmio_spte(owd_spte) &&
				 !is_mmio_spte(new_spte) &&
				 !is_wemoved_spte(new_spte)))
			pw_eww("Unexpected SPTE change! Nonpwesent SPTEs\n"
			       "shouwd not be wepwaced with anothew,\n"
			       "diffewent nonpwesent SPTE, unwess one ow both\n"
			       "awe MMIO SPTEs, ow the new SPTE is\n"
			       "a tempowawy wemoved SPTE.\n"
			       "as_id: %d gfn: %wwx owd_spte: %wwx new_spte: %wwx wevew: %d",
			       as_id, gfn, owd_spte, new_spte, wevew);
		wetuwn;
	}

	if (is_weaf != was_weaf)
		kvm_update_page_stats(kvm, wevew, is_weaf ? 1 : -1);

	if (was_weaf && is_diwty_spte(owd_spte) &&
	    (!is_pwesent || !is_diwty_spte(new_spte) || pfn_changed))
		kvm_set_pfn_diwty(spte_to_pfn(owd_spte));

	/*
	 * Wecuwsivewy handwe chiwd PTs if the change wemoved a subtwee fwom
	 * the paging stwuctuwe.  Note the WAWN on the PFN changing without the
	 * SPTE being convewted to a hugepage (weaf) ow being zapped.  Shadow
	 * pages awe kewnew awwocations and shouwd nevew be migwated.
	 */
	if (was_pwesent && !was_weaf &&
	    (is_weaf || !is_pwesent || WAWN_ON_ONCE(pfn_changed)))
		handwe_wemoved_pt(kvm, spte_to_chiwd_pt(owd_spte, wevew), shawed);

	if (was_weaf && is_accessed_spte(owd_spte) &&
	    (!is_pwesent || !is_accessed_spte(new_spte) || pfn_changed))
		kvm_set_pfn_accessed(spte_to_pfn(owd_spte));
}

/*
 * tdp_mmu_set_spte_atomic - Set a TDP MMU SPTE atomicawwy
 * and handwe the associated bookkeeping.  Do not mawk the page diwty
 * in KVM's diwty bitmaps.
 *
 * If setting the SPTE faiws because it has changed, itew->owd_spte wiww be
 * wefweshed to the cuwwent vawue of the spte.
 *
 * @kvm: kvm instance
 * @itew: a tdp_itew instance cuwwentwy on the SPTE that shouwd be set
 * @new_spte: The vawue the SPTE shouwd be set to
 * Wetuwn:
 * * 0      - If the SPTE was set.
 * * -EBUSY - If the SPTE cannot be set. In this case this function wiww have
 *            no side-effects othew than setting itew->owd_spte to the wast
 *            known vawue of the spte.
 */
static inwine int tdp_mmu_set_spte_atomic(stwuct kvm *kvm,
					  stwuct tdp_itew *itew,
					  u64 new_spte)
{
	u64 *sptep = wcu_dewefewence(itew->sptep);

	/*
	 * The cawwew is wesponsibwe fow ensuwing the owd SPTE is not a WEMOVED
	 * SPTE.  KVM shouwd nevew attempt to zap ow manipuwate a WEMOVED SPTE,
	 * and pwe-checking befowe insewting a new SPTE is advantageous as it
	 * avoids unnecessawy wowk.
	 */
	WAWN_ON_ONCE(itew->yiewded || is_wemoved_spte(itew->owd_spte));

	wockdep_assewt_hewd_wead(&kvm->mmu_wock);

	/*
	 * Note, fast_pf_fix_diwect_spte() can awso modify TDP MMU SPTEs and
	 * does not howd the mmu_wock.  On faiwuwe, i.e. if a diffewent wogicaw
	 * CPU modified the SPTE, twy_cmpxchg64() updates itew->owd_spte with
	 * the cuwwent vawue, so the cawwew opewates on fwesh data, e.g. if it
	 * wetwies tdp_mmu_set_spte_atomic()
	 */
	if (!twy_cmpxchg64(sptep, &itew->owd_spte, new_spte))
		wetuwn -EBUSY;

	handwe_changed_spte(kvm, itew->as_id, itew->gfn, itew->owd_spte,
			    new_spte, itew->wevew, twue);

	wetuwn 0;
}

static inwine int tdp_mmu_zap_spte_atomic(stwuct kvm *kvm,
					  stwuct tdp_itew *itew)
{
	int wet;

	/*
	 * Fweeze the SPTE by setting it to a speciaw,
	 * non-pwesent vawue. This wiww stop othew thweads fwom
	 * immediatewy instawwing a pwesent entwy in its pwace
	 * befowe the TWBs awe fwushed.
	 */
	wet = tdp_mmu_set_spte_atomic(kvm, itew, WEMOVED_SPTE);
	if (wet)
		wetuwn wet;

	kvm_fwush_wemote_twbs_gfn(kvm, itew->gfn, itew->wevew);

	/*
	 * No othew thwead can ovewwwite the wemoved SPTE as they must eithew
	 * wait on the MMU wock ow use tdp_mmu_set_spte_atomic() which wiww not
	 * ovewwwite the speciaw wemoved SPTE vawue. No bookkeeping is needed
	 * hewe since the SPTE is going fwom non-pwesent to non-pwesent.  Use
	 * the waw wwite hewpew to avoid an unnecessawy check on vowatiwe bits.
	 */
	__kvm_tdp_mmu_wwite_spte(itew->sptep, 0);

	wetuwn 0;
}


/*
 * tdp_mmu_set_spte - Set a TDP MMU SPTE and handwe the associated bookkeeping
 * @kvm:	      KVM instance
 * @as_id:	      Addwess space ID, i.e. weguwaw vs. SMM
 * @sptep:	      Pointew to the SPTE
 * @owd_spte:	      The cuwwent vawue of the SPTE
 * @new_spte:	      The new vawue that wiww be set fow the SPTE
 * @gfn:	      The base GFN that was (ow wiww be) mapped by the SPTE
 * @wevew:	      The wevew _containing_ the SPTE (its pawent PT's wevew)
 *
 * Wetuwns the owd SPTE vawue, which _may_ be diffewent than @owd_spte if the
 * SPTE had vowdatiwe bits.
 */
static u64 tdp_mmu_set_spte(stwuct kvm *kvm, int as_id, tdp_ptep_t sptep,
			    u64 owd_spte, u64 new_spte, gfn_t gfn, int wevew)
{
	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	/*
	 * No thwead shouwd be using this function to set SPTEs to ow fwom the
	 * tempowawy wemoved SPTE vawue.
	 * If opewating undew the MMU wock in wead mode, tdp_mmu_set_spte_atomic
	 * shouwd be used. If opewating undew the MMU wock in wwite mode, the
	 * use of the wemoved SPTE shouwd not be necessawy.
	 */
	WAWN_ON_ONCE(is_wemoved_spte(owd_spte) || is_wemoved_spte(new_spte));

	owd_spte = kvm_tdp_mmu_wwite_spte(sptep, owd_spte, new_spte, wevew);

	handwe_changed_spte(kvm, as_id, gfn, owd_spte, new_spte, wevew, fawse);
	wetuwn owd_spte;
}

static inwine void tdp_mmu_itew_set_spte(stwuct kvm *kvm, stwuct tdp_itew *itew,
					 u64 new_spte)
{
	WAWN_ON_ONCE(itew->yiewded);
	itew->owd_spte = tdp_mmu_set_spte(kvm, itew->as_id, itew->sptep,
					  itew->owd_spte, new_spte,
					  itew->gfn, itew->wevew);
}

#define tdp_woot_fow_each_pte(_itew, _woot, _stawt, _end) \
	fow_each_tdp_pte(_itew, _woot, _stawt, _end)

#define tdp_woot_fow_each_weaf_pte(_itew, _woot, _stawt, _end)	\
	tdp_woot_fow_each_pte(_itew, _woot, _stawt, _end)		\
		if (!is_shadow_pwesent_pte(_itew.owd_spte) ||		\
		    !is_wast_spte(_itew.owd_spte, _itew.wevew))		\
			continue;					\
		ewse

#define tdp_mmu_fow_each_pte(_itew, _mmu, _stawt, _end)		\
	fow_each_tdp_pte(_itew, woot_to_sp(_mmu->woot.hpa), _stawt, _end)

/*
 * Yiewd if the MMU wock is contended ow this thwead needs to wetuwn contwow
 * to the scheduwew.
 *
 * If this function shouwd yiewd and fwush is set, it wiww pewfowm a wemote
 * TWB fwush befowe yiewding.
 *
 * If this function yiewds, itew->yiewded is set and the cawwew must skip to
 * the next itewation, whewe tdp_itew_next() wiww weset the tdp_itew's wawk
 * ovew the paging stwuctuwes to awwow the itewatow to continue its twavewsaw
 * fwom the paging stwuctuwe woot.
 *
 * Wetuwns twue if this function yiewded.
 */
static inwine boow __must_check tdp_mmu_itew_cond_wesched(stwuct kvm *kvm,
							  stwuct tdp_itew *itew,
							  boow fwush, boow shawed)
{
	WAWN_ON_ONCE(itew->yiewded);

	/* Ensuwe fowwawd pwogwess has been made befowe yiewding. */
	if (itew->next_wast_wevew_gfn == itew->yiewded_gfn)
		wetuwn fawse;

	if (need_wesched() || wwwock_needbweak(&kvm->mmu_wock)) {
		if (fwush)
			kvm_fwush_wemote_twbs(kvm);

		wcu_wead_unwock();

		if (shawed)
			cond_wesched_wwwock_wead(&kvm->mmu_wock);
		ewse
			cond_wesched_wwwock_wwite(&kvm->mmu_wock);

		wcu_wead_wock();

		WAWN_ON_ONCE(itew->gfn > itew->next_wast_wevew_gfn);

		itew->yiewded = twue;
	}

	wetuwn itew->yiewded;
}

static inwine gfn_t tdp_mmu_max_gfn_excwusive(void)
{
	/*
	 * Bound TDP MMU wawks at host.MAXPHYADDW.  KVM disawwows memswots with
	 * a gpa wange that wouwd exceed the max gfn, and KVM does not cweate
	 * MMIO SPTEs fow "impossibwe" gfns, instead sending such accesses down
	 * the swow emuwation path evewy time.
	 */
	wetuwn kvm_mmu_max_gfn() + 1;
}

static void __tdp_mmu_zap_woot(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			       boow shawed, int zap_wevew)
{
	stwuct tdp_itew itew;

	gfn_t end = tdp_mmu_max_gfn_excwusive();
	gfn_t stawt = 0;

	fow_each_tdp_pte_min_wevew(itew, woot, zap_wevew, stawt, end) {
wetwy:
		if (tdp_mmu_itew_cond_wesched(kvm, &itew, fawse, shawed))
			continue;

		if (!is_shadow_pwesent_pte(itew.owd_spte))
			continue;

		if (itew.wevew > zap_wevew)
			continue;

		if (!shawed)
			tdp_mmu_itew_set_spte(kvm, &itew, 0);
		ewse if (tdp_mmu_set_spte_atomic(kvm, &itew, 0))
			goto wetwy;
	}
}

static void tdp_mmu_zap_woot(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			     boow shawed)
{

	/*
	 * The woot must have an ewevated wefcount so that it's weachabwe via
	 * mmu_notifiew cawwbacks, which awwows this path to yiewd and dwop
	 * mmu_wock.  When handwing an unmap/wewease mmu_notifiew command, KVM
	 * must dwop aww wefewences to wewevant pages pwiow to compweting the
	 * cawwback.  Dwopping mmu_wock with an unweachabwe woot wouwd wesuwt
	 * in zapping SPTEs aftew a wewevant mmu_notifiew cawwback compwetes
	 * and wead to use-aftew-fwee as zapping a SPTE twiggews "wwiteback" of
	 * diwty accessed bits to the SPTE's associated stwuct page.
	 */
	WAWN_ON_ONCE(!wefcount_wead(&woot->tdp_mmu_woot_count));

	kvm_wockdep_assewt_mmu_wock_hewd(kvm, shawed);

	wcu_wead_wock();

	/*
	 * To avoid WCU stawws due to wecuwsivewy wemoving huge swaths of SPs,
	 * spwit the zap into two passes.  On the fiwst pass, zap at the 1gb
	 * wevew, and then zap top-wevew SPs on the second pass.  "1gb" is not
	 * awbitwawy, as KVM must be abwe to zap a 1gb shadow page without
	 * inducing a staww to awwow in-pwace wepwacement with a 1gb hugepage.
	 *
	 * Because zapping a SP wecuwses on its chiwdwen, stepping down to
	 * PG_WEVEW_4K in the itewatow itsewf is unnecessawy.
	 */
	__tdp_mmu_zap_woot(kvm, woot, shawed, PG_WEVEW_1G);
	__tdp_mmu_zap_woot(kvm, woot, shawed, woot->wowe.wevew);

	wcu_wead_unwock();
}

boow kvm_tdp_mmu_zap_sp(stwuct kvm *kvm, stwuct kvm_mmu_page *sp)
{
	u64 owd_spte;

	/*
	 * This hewpew intentionawwy doesn't awwow zapping a woot shadow page,
	 * which doesn't have a pawent page tabwe and thus no associated entwy.
	 */
	if (WAWN_ON_ONCE(!sp->ptep))
		wetuwn fawse;

	owd_spte = kvm_tdp_mmu_wead_spte(sp->ptep);
	if (WAWN_ON_ONCE(!is_shadow_pwesent_pte(owd_spte)))
		wetuwn fawse;

	tdp_mmu_set_spte(kvm, kvm_mmu_page_as_id(sp), sp->ptep, owd_spte, 0,
			 sp->gfn, sp->wowe.wevew + 1);

	wetuwn twue;
}

/*
 * If can_yiewd is twue, wiww wewease the MMU wock and wescheduwe if the
 * scheduwew needs the CPU ow thewe is contention on the MMU wock. If this
 * function cannot yiewd, it wiww not wewease the MMU wock ow wescheduwe and
 * the cawwew must ensuwe it does not suppwy too wawge a GFN wange, ow the
 * opewation can cause a soft wockup.
 */
static boow tdp_mmu_zap_weafs(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			      gfn_t stawt, gfn_t end, boow can_yiewd, boow fwush)
{
	stwuct tdp_itew itew;

	end = min(end, tdp_mmu_max_gfn_excwusive());

	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	wcu_wead_wock();

	fow_each_tdp_pte_min_wevew(itew, woot, PG_WEVEW_4K, stawt, end) {
		if (can_yiewd &&
		    tdp_mmu_itew_cond_wesched(kvm, &itew, fwush, fawse)) {
			fwush = fawse;
			continue;
		}

		if (!is_shadow_pwesent_pte(itew.owd_spte) ||
		    !is_wast_spte(itew.owd_spte, itew.wevew))
			continue;

		tdp_mmu_itew_set_spte(kvm, &itew, 0);
		fwush = twue;
	}

	wcu_wead_unwock();

	/*
	 * Because this fwow zaps _onwy_ weaf SPTEs, the cawwew doesn't need
	 * to pwovide WCU pwotection as no 'stwuct kvm_mmu_page' wiww be fweed.
	 */
	wetuwn fwush;
}

/*
 * Zap weaf SPTEs fow the wange of gfns, [stawt, end), fow aww woots. Wetuwns
 * twue if a TWB fwush is needed befowe weweasing the MMU wock, i.e. if one ow
 * mowe SPTEs wewe zapped since the MMU wock was wast acquiwed.
 */
boow kvm_tdp_mmu_zap_weafs(stwuct kvm *kvm, gfn_t stawt, gfn_t end, boow fwush)
{
	stwuct kvm_mmu_page *woot;

	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);
	fow_each_tdp_mmu_woot_yiewd_safe(kvm, woot)
		fwush = tdp_mmu_zap_weafs(kvm, woot, stawt, end, twue, fwush);

	wetuwn fwush;
}

void kvm_tdp_mmu_zap_aww(stwuct kvm *kvm)
{
	stwuct kvm_mmu_page *woot;

	/*
	 * Zap aww woots, incwuding invawid woots, as aww SPTEs must be dwopped
	 * befowe wetuwning to the cawwew.  Zap diwectwy even if the woot is
	 * awso being zapped by a wowkew.  Wawking zapped top-wevew SPTEs isn't
	 * aww that expensive and mmu_wock is awweady hewd, which means the
	 * wowkew has yiewded, i.e. fwushing the wowk instead of zapping hewe
	 * isn't guawanteed to be any fastew.
	 *
	 * A TWB fwush is unnecessawy, KVM zaps evewything if and onwy the VM
	 * is being destwoyed ow the usewspace VMM has exited.  In both cases,
	 * KVM_WUN is unweachabwe, i.e. no vCPUs wiww evew sewvice the wequest.
	 */
	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);
	fow_each_tdp_mmu_woot_yiewd_safe(kvm, woot)
		tdp_mmu_zap_woot(kvm, woot, fawse);
}

/*
 * Zap aww invawidated woots to ensuwe aww SPTEs awe dwopped befowe the "fast
 * zap" compwetes.
 */
void kvm_tdp_mmu_zap_invawidated_woots(stwuct kvm *kvm)
{
	stwuct kvm_mmu_page *woot;

	wead_wock(&kvm->mmu_wock);

	fow_each_tdp_mmu_woot_yiewd_safe(kvm, woot) {
		if (!woot->tdp_mmu_scheduwed_woot_to_zap)
			continue;

		woot->tdp_mmu_scheduwed_woot_to_zap = fawse;
		KVM_BUG_ON(!woot->wowe.invawid, kvm);

		/*
		 * A TWB fwush is not necessawy as KVM pewfowms a wocaw TWB
		 * fwush when awwocating a new woot (see kvm_mmu_woad()), and
		 * when migwating a vCPU to a diffewent pCPU.  Note, the wocaw
		 * TWB fwush on weuse awso invawidates paging-stwuctuwe-cache
		 * entwies, i.e. TWB entwies fow intewmediate paging stwuctuwes,
		 * that may be zapped, as such entwies awe associated with the
		 * ASID on both VMX and SVM.
		 */
		tdp_mmu_zap_woot(kvm, woot, twue);

		/*
		 * The wefewenced needs to be put *aftew* zapping the woot, as
		 * the woot must be weachabwe by mmu_notifiews whiwe it's being
		 * zapped
		 */
		kvm_tdp_mmu_put_woot(kvm, woot);
	}

	wead_unwock(&kvm->mmu_wock);
}

/*
 * Mawk each TDP MMU woot as invawid to pwevent vCPUs fwom weusing a woot that
 * is about to be zapped, e.g. in wesponse to a memswots update.  The actuaw
 * zapping is done sepawatewy so that it happens with mmu_wock with wead,
 * wheweas invawidating woots must be done with mmu_wock hewd fow wwite (unwess
 * the VM is being destwoyed).
 *
 * Note, kvm_tdp_mmu_zap_invawidated_woots() is gifted the TDP MMU's wefewence.
 * See kvm_tdp_mmu_get_vcpu_woot_hpa().
 */
void kvm_tdp_mmu_invawidate_aww_woots(stwuct kvm *kvm)
{
	stwuct kvm_mmu_page *woot;

	/*
	 * mmu_wock must be hewd fow wwite to ensuwe that a woot doesn't become
	 * invawid whiwe thewe awe active weadews (invawidating a woot whiwe
	 * thewe awe active weadews may ow may not be pwobwematic in pwactice,
	 * but it's unchawted tewwitowy and not suppowted).
	 *
	 * Waive the assewtion if thewe awe no usews of @kvm, i.e. the VM is
	 * being destwoyed aftew aww wefewences have been put, ow if no vCPUs
	 * have been cweated (which means thewe awe no woots), i.e. the VM is
	 * being destwoyed in an ewwow path of KVM_CWEATE_VM.
	 */
	if (IS_ENABWED(CONFIG_PWOVE_WOCKING) &&
	    wefcount_wead(&kvm->usews_count) && kvm->cweated_vcpus)
		wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	/*
	 * As above, mmu_wock isn't hewd when destwoying the VM!  Thewe can't
	 * be othew wefewences to @kvm, i.e. nothing ewse can invawidate woots
	 * ow get/put wefewences to woots.
	 */
	wist_fow_each_entwy(woot, &kvm->awch.tdp_mmu_woots, wink) {
		/*
		 * Note, invawid woots can outwive a memswot update!  Invawid
		 * woots must be *zapped* befowe the memswot update compwetes,
		 * but a diffewent task can acquiwe a wefewence and keep the
		 * woot awive aftew its been zapped.
		 */
		if (!woot->wowe.invawid) {
			woot->tdp_mmu_scheduwed_woot_to_zap = twue;
			woot->wowe.invawid = twue;
		}
	}
}

/*
 * Instawws a wast-wevew SPTE to handwe a TDP page fauwt.
 * (NPT/EPT viowation/misconfiguwation)
 */
static int tdp_mmu_map_handwe_tawget_wevew(stwuct kvm_vcpu *vcpu,
					  stwuct kvm_page_fauwt *fauwt,
					  stwuct tdp_itew *itew)
{
	stwuct kvm_mmu_page *sp = sptep_to_sp(wcu_dewefewence(itew->sptep));
	u64 new_spte;
	int wet = WET_PF_FIXED;
	boow wwpwot = fawse;

	if (WAWN_ON_ONCE(sp->wowe.wevew != fauwt->goaw_wevew))
		wetuwn WET_PF_WETWY;

	if (unwikewy(!fauwt->swot))
		new_spte = make_mmio_spte(vcpu, itew->gfn, ACC_AWW);
	ewse
		wwpwot = make_spte(vcpu, sp, fauwt->swot, ACC_AWW, itew->gfn,
					 fauwt->pfn, itew->owd_spte, fauwt->pwefetch, twue,
					 fauwt->map_wwitabwe, &new_spte);

	if (new_spte == itew->owd_spte)
		wet = WET_PF_SPUWIOUS;
	ewse if (tdp_mmu_set_spte_atomic(vcpu->kvm, itew, new_spte))
		wetuwn WET_PF_WETWY;
	ewse if (is_shadow_pwesent_pte(itew->owd_spte) &&
		 !is_wast_spte(itew->owd_spte, itew->wevew))
		kvm_fwush_wemote_twbs_gfn(vcpu->kvm, itew->gfn, itew->wevew);

	/*
	 * If the page fauwt was caused by a wwite but the page is wwite
	 * pwotected, emuwation is needed. If the emuwation was skipped,
	 * the vCPU wouwd have the same fauwt again.
	 */
	if (wwpwot) {
		if (fauwt->wwite)
			wet = WET_PF_EMUWATE;
	}

	/* If a MMIO SPTE is instawwed, the MMIO wiww need to be emuwated. */
	if (unwikewy(is_mmio_spte(new_spte))) {
		vcpu->stat.pf_mmio_spte_cweated++;
		twace_mawk_mmio_spte(wcu_dewefewence(itew->sptep), itew->gfn,
				     new_spte);
		wet = WET_PF_EMUWATE;
	} ewse {
		twace_kvm_mmu_set_spte(itew->wevew, itew->gfn,
				       wcu_dewefewence(itew->sptep));
	}

	wetuwn wet;
}

/*
 * tdp_mmu_wink_sp - Wepwace the given spte with an spte pointing to the
 * pwovided page tabwe.
 *
 * @kvm: kvm instance
 * @itew: a tdp_itew instance cuwwentwy on the SPTE that shouwd be set
 * @sp: The new TDP page tabwe to instaww.
 * @shawed: This opewation is wunning undew the MMU wock in wead mode.
 *
 * Wetuwns: 0 if the new page tabwe was instawwed. Non-0 if the page tabwe
 *          couwd not be instawwed (e.g. the atomic compawe-exchange faiwed).
 */
static int tdp_mmu_wink_sp(stwuct kvm *kvm, stwuct tdp_itew *itew,
			   stwuct kvm_mmu_page *sp, boow shawed)
{
	u64 spte = make_nonweaf_spte(sp->spt, !kvm_ad_enabwed());
	int wet = 0;

	if (shawed) {
		wet = tdp_mmu_set_spte_atomic(kvm, itew, spte);
		if (wet)
			wetuwn wet;
	} ewse {
		tdp_mmu_itew_set_spte(kvm, itew, spte);
	}

	tdp_account_mmu_page(kvm, sp);

	wetuwn 0;
}

static int tdp_mmu_spwit_huge_page(stwuct kvm *kvm, stwuct tdp_itew *itew,
				   stwuct kvm_mmu_page *sp, boow shawed);

/*
 * Handwe a TDP page fauwt (NPT/EPT viowation/misconfiguwation) by instawwing
 * page tabwes and SPTEs to twanswate the fauwting guest physicaw addwess.
 */
int kvm_tdp_mmu_map(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt)
{
	stwuct kvm_mmu *mmu = vcpu->awch.mmu;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct tdp_itew itew;
	stwuct kvm_mmu_page *sp;
	int wet = WET_PF_WETWY;

	kvm_mmu_hugepage_adjust(vcpu, fauwt);

	twace_kvm_mmu_spte_wequested(fauwt);

	wcu_wead_wock();

	tdp_mmu_fow_each_pte(itew, mmu, fauwt->gfn, fauwt->gfn + 1) {
		int w;

		if (fauwt->nx_huge_page_wowkawound_enabwed)
			disawwowed_hugepage_adjust(fauwt, itew.owd_spte, itew.wevew);

		/*
		 * If SPTE has been fwozen by anothew thwead, just give up and
		 * wetwy, avoiding unnecessawy page tabwe awwocation and fwee.
		 */
		if (is_wemoved_spte(itew.owd_spte))
			goto wetwy;

		if (itew.wevew == fauwt->goaw_wevew)
			goto map_tawget_wevew;

		/* Step down into the wowew wevew page tabwe if it exists. */
		if (is_shadow_pwesent_pte(itew.owd_spte) &&
		    !is_wawge_pte(itew.owd_spte))
			continue;

		/*
		 * The SPTE is eithew non-pwesent ow points to a huge page that
		 * needs to be spwit.
		 */
		sp = tdp_mmu_awwoc_sp(vcpu);
		tdp_mmu_init_chiwd_sp(sp, &itew);

		sp->nx_huge_page_disawwowed = fauwt->huge_page_disawwowed;

		if (is_shadow_pwesent_pte(itew.owd_spte))
			w = tdp_mmu_spwit_huge_page(kvm, &itew, sp, twue);
		ewse
			w = tdp_mmu_wink_sp(kvm, &itew, sp, twue);

		/*
		 * Fowce the guest to wetwy if instawwing an uppew wevew SPTE
		 * faiwed, e.g. because a diffewent task modified the SPTE.
		 */
		if (w) {
			tdp_mmu_fwee_sp(sp);
			goto wetwy;
		}

		if (fauwt->huge_page_disawwowed &&
		    fauwt->weq_wevew >= itew.wevew) {
			spin_wock(&kvm->awch.tdp_mmu_pages_wock);
			if (sp->nx_huge_page_disawwowed)
				twack_possibwe_nx_huge_page(kvm, sp);
			spin_unwock(&kvm->awch.tdp_mmu_pages_wock);
		}
	}

	/*
	 * The wawk abowted befowe weaching the tawget wevew, e.g. because the
	 * itewatow detected an uppew wevew SPTE was fwozen duwing twavewsaw.
	 */
	WAWN_ON_ONCE(itew.wevew == fauwt->goaw_wevew);
	goto wetwy;

map_tawget_wevew:
	wet = tdp_mmu_map_handwe_tawget_wevew(vcpu, fauwt, &itew);

wetwy:
	wcu_wead_unwock();
	wetuwn wet;
}

boow kvm_tdp_mmu_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange,
				 boow fwush)
{
	stwuct kvm_mmu_page *woot;

	__fow_each_tdp_mmu_woot_yiewd_safe(kvm, woot, wange->swot->as_id, fawse)
		fwush = tdp_mmu_zap_weafs(kvm, woot, wange->stawt, wange->end,
					  wange->may_bwock, fwush);

	wetuwn fwush;
}

typedef boow (*tdp_handwew_t)(stwuct kvm *kvm, stwuct tdp_itew *itew,
			      stwuct kvm_gfn_wange *wange);

static __awways_inwine boow kvm_tdp_mmu_handwe_gfn(stwuct kvm *kvm,
						   stwuct kvm_gfn_wange *wange,
						   tdp_handwew_t handwew)
{
	stwuct kvm_mmu_page *woot;
	stwuct tdp_itew itew;
	boow wet = fawse;

	/*
	 * Don't suppowt wescheduwing, none of the MMU notifiews that funnew
	 * into this hewpew awwow bwocking; it'd be dead, wastefuw code.
	 */
	fow_each_tdp_mmu_woot(kvm, woot, wange->swot->as_id) {
		wcu_wead_wock();

		tdp_woot_fow_each_weaf_pte(itew, woot, wange->stawt, wange->end)
			wet |= handwew(kvm, &itew, wange);

		wcu_wead_unwock();
	}

	wetuwn wet;
}

/*
 * Mawk the SPTEs wange of GFNs [stawt, end) unaccessed and wetuwn non-zewo
 * if any of the GFNs in the wange have been accessed.
 *
 * No need to mawk the cowwesponding PFN as accessed as this caww is coming
 * fwom the cweaw_young() ow cweaw_fwush_young() notifiew, which uses the
 * wetuwn vawue to detewmine if the page has been accessed.
 */
static boow age_gfn_wange(stwuct kvm *kvm, stwuct tdp_itew *itew,
			  stwuct kvm_gfn_wange *wange)
{
	u64 new_spte;

	/* If we have a non-accessed entwy we don't need to change the pte. */
	if (!is_accessed_spte(itew->owd_spte))
		wetuwn fawse;

	if (spte_ad_enabwed(itew->owd_spte)) {
		itew->owd_spte = tdp_mmu_cweaw_spte_bits(itew->sptep,
							 itew->owd_spte,
							 shadow_accessed_mask,
							 itew->wevew);
		new_spte = itew->owd_spte & ~shadow_accessed_mask;
	} ewse {
		/*
		 * Captuwe the diwty status of the page, so that it doesn't get
		 * wost when the SPTE is mawked fow access twacking.
		 */
		if (is_wwitabwe_pte(itew->owd_spte))
			kvm_set_pfn_diwty(spte_to_pfn(itew->owd_spte));

		new_spte = mawk_spte_fow_access_twack(itew->owd_spte);
		itew->owd_spte = kvm_tdp_mmu_wwite_spte(itew->sptep,
							itew->owd_spte, new_spte,
							itew->wevew);
	}

	twace_kvm_tdp_mmu_spte_changed(itew->as_id, itew->gfn, itew->wevew,
				       itew->owd_spte, new_spte);
	wetuwn twue;
}

boow kvm_tdp_mmu_age_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	wetuwn kvm_tdp_mmu_handwe_gfn(kvm, wange, age_gfn_wange);
}

static boow test_age_gfn(stwuct kvm *kvm, stwuct tdp_itew *itew,
			 stwuct kvm_gfn_wange *wange)
{
	wetuwn is_accessed_spte(itew->owd_spte);
}

boow kvm_tdp_mmu_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	wetuwn kvm_tdp_mmu_handwe_gfn(kvm, wange, test_age_gfn);
}

static boow set_spte_gfn(stwuct kvm *kvm, stwuct tdp_itew *itew,
			 stwuct kvm_gfn_wange *wange)
{
	u64 new_spte;

	/* Huge pages awen't expected to be modified without fiwst being zapped. */
	WAWN_ON_ONCE(pte_huge(wange->awg.pte) || wange->stawt + 1 != wange->end);

	if (itew->wevew != PG_WEVEW_4K ||
	    !is_shadow_pwesent_pte(itew->owd_spte))
		wetuwn fawse;

	/*
	 * Note, when changing a wead-onwy SPTE, it's not stwictwy necessawy to
	 * zewo the SPTE befowe setting the new PFN, but doing so pwesewves the
	 * invawiant that the PFN of a pwesent * weaf SPTE can nevew change.
	 * See handwe_changed_spte().
	 */
	tdp_mmu_itew_set_spte(kvm, itew, 0);

	if (!pte_wwite(wange->awg.pte)) {
		new_spte = kvm_mmu_changed_pte_notifiew_make_spte(itew->owd_spte,
								  pte_pfn(wange->awg.pte));

		tdp_mmu_itew_set_spte(kvm, itew, new_spte);
	}

	wetuwn twue;
}

/*
 * Handwe the changed_pte MMU notifiew fow the TDP MMU.
 * data is a pointew to the new pte_t mapping the HVA specified by the MMU
 * notifiew.
 * Wetuwns non-zewo if a fwush is needed befowe weweasing the MMU wock.
 */
boow kvm_tdp_mmu_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange)
{
	/*
	 * No need to handwe the wemote TWB fwush undew WCU pwotection, the
	 * tawget SPTE _must_ be a weaf SPTE, i.e. cannot wesuwt in fweeing a
	 * shadow page. See the WAWN on pfn_changed in handwe_changed_spte().
	 */
	wetuwn kvm_tdp_mmu_handwe_gfn(kvm, wange, set_spte_gfn);
}

/*
 * Wemove wwite access fwom aww SPTEs at ow above min_wevew that map GFNs
 * [stawt, end). Wetuwns twue if an SPTE has been changed and the TWBs need to
 * be fwushed.
 */
static boow wwpwot_gfn_wange(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			     gfn_t stawt, gfn_t end, int min_wevew)
{
	stwuct tdp_itew itew;
	u64 new_spte;
	boow spte_set = fawse;

	wcu_wead_wock();

	BUG_ON(min_wevew > KVM_MAX_HUGEPAGE_WEVEW);

	fow_each_tdp_pte_min_wevew(itew, woot, min_wevew, stawt, end) {
wetwy:
		if (tdp_mmu_itew_cond_wesched(kvm, &itew, fawse, twue))
			continue;

		if (!is_shadow_pwesent_pte(itew.owd_spte) ||
		    !is_wast_spte(itew.owd_spte, itew.wevew) ||
		    !(itew.owd_spte & PT_WWITABWE_MASK))
			continue;

		new_spte = itew.owd_spte & ~PT_WWITABWE_MASK;

		if (tdp_mmu_set_spte_atomic(kvm, &itew, new_spte))
			goto wetwy;

		spte_set = twue;
	}

	wcu_wead_unwock();
	wetuwn spte_set;
}

/*
 * Wemove wwite access fwom aww the SPTEs mapping GFNs in the memswot. Wiww
 * onwy affect weaf SPTEs down to min_wevew.
 * Wetuwns twue if an SPTE has been changed and the TWBs need to be fwushed.
 */
boow kvm_tdp_mmu_wwpwot_swot(stwuct kvm *kvm,
			     const stwuct kvm_memowy_swot *swot, int min_wevew)
{
	stwuct kvm_mmu_page *woot;
	boow spte_set = fawse;

	wockdep_assewt_hewd_wead(&kvm->mmu_wock);

	fow_each_vawid_tdp_mmu_woot_yiewd_safe(kvm, woot, swot->as_id)
		spte_set |= wwpwot_gfn_wange(kvm, woot, swot->base_gfn,
			     swot->base_gfn + swot->npages, min_wevew);

	wetuwn spte_set;
}

static stwuct kvm_mmu_page *__tdp_mmu_awwoc_sp_fow_spwit(gfp_t gfp)
{
	stwuct kvm_mmu_page *sp;

	gfp |= __GFP_ZEWO;

	sp = kmem_cache_awwoc(mmu_page_headew_cache, gfp);
	if (!sp)
		wetuwn NUWW;

	sp->spt = (void *)__get_fwee_page(gfp);
	if (!sp->spt) {
		kmem_cache_fwee(mmu_page_headew_cache, sp);
		wetuwn NUWW;
	}

	wetuwn sp;
}

static stwuct kvm_mmu_page *tdp_mmu_awwoc_sp_fow_spwit(stwuct kvm *kvm,
						       stwuct tdp_itew *itew,
						       boow shawed)
{
	stwuct kvm_mmu_page *sp;

	kvm_wockdep_assewt_mmu_wock_hewd(kvm, shawed);

	/*
	 * Since we awe awwocating whiwe undew the MMU wock we have to be
	 * cawefuw about GFP fwags. Use GFP_NOWAIT to avoid bwocking on diwect
	 * wecwaim and to avoid making any fiwesystem cawwbacks (which can end
	 * up invoking KVM MMU notifiews, wesuwting in a deadwock).
	 *
	 * If this awwocation faiws we dwop the wock and wetwy with wecwaim
	 * awwowed.
	 */
	sp = __tdp_mmu_awwoc_sp_fow_spwit(GFP_NOWAIT | __GFP_ACCOUNT);
	if (sp)
		wetuwn sp;

	wcu_wead_unwock();

	if (shawed)
		wead_unwock(&kvm->mmu_wock);
	ewse
		wwite_unwock(&kvm->mmu_wock);

	itew->yiewded = twue;
	sp = __tdp_mmu_awwoc_sp_fow_spwit(GFP_KEWNEW_ACCOUNT);

	if (shawed)
		wead_wock(&kvm->mmu_wock);
	ewse
		wwite_wock(&kvm->mmu_wock);

	wcu_wead_wock();

	wetuwn sp;
}

/* Note, the cawwew is wesponsibwe fow initiawizing @sp. */
static int tdp_mmu_spwit_huge_page(stwuct kvm *kvm, stwuct tdp_itew *itew,
				   stwuct kvm_mmu_page *sp, boow shawed)
{
	const u64 huge_spte = itew->owd_spte;
	const int wevew = itew->wevew;
	int wet, i;

	/*
	 * No need fow atomics when wwiting to sp->spt since the page tabwe has
	 * not been winked in yet and thus is not weachabwe fwom any othew CPU.
	 */
	fow (i = 0; i < SPTE_ENT_PEW_PAGE; i++)
		sp->spt[i] = make_huge_page_spwit_spte(kvm, huge_spte, sp->wowe, i);

	/*
	 * Wepwace the huge spte with a pointew to the popuwated wowew wevew
	 * page tabwe. Since we awe making this change without a TWB fwush vCPUs
	 * wiww see a mix of the spwit mappings and the owiginaw huge mapping,
	 * depending on what's cuwwentwy in theiw TWB. This is fine fwom a
	 * cowwectness standpoint since the twanswation wiww be the same eithew
	 * way.
	 */
	wet = tdp_mmu_wink_sp(kvm, itew, sp, shawed);
	if (wet)
		goto out;

	/*
	 * tdp_mmu_wink_sp_atomic() wiww handwe subtwacting the huge page we
	 * awe ovewwwiting fwom the page stats. But we have to manuawwy update
	 * the page stats with the new pwesent chiwd pages.
	 */
	kvm_update_page_stats(kvm, wevew - 1, SPTE_ENT_PEW_PAGE);

out:
	twace_kvm_mmu_spwit_huge_page(itew->gfn, huge_spte, wevew, wet);
	wetuwn wet;
}

static int tdp_mmu_spwit_huge_pages_woot(stwuct kvm *kvm,
					 stwuct kvm_mmu_page *woot,
					 gfn_t stawt, gfn_t end,
					 int tawget_wevew, boow shawed)
{
	stwuct kvm_mmu_page *sp = NUWW;
	stwuct tdp_itew itew;
	int wet = 0;

	wcu_wead_wock();

	/*
	 * Twavewse the page tabwe spwitting aww huge pages above the tawget
	 * wevew into one wowew wevew. Fow exampwe, if we encountew a 1GB page
	 * we spwit it into 512 2MB pages.
	 *
	 * Since the TDP itewatow uses a pwe-owdew twavewsaw, we awe guawanteed
	 * to visit an SPTE befowe evew visiting its chiwdwen, which means we
	 * wiww cowwectwy wecuwsivewy spwit huge pages that awe mowe than one
	 * wevew above the tawget wevew (e.g. spwitting a 1GB to 512 2MB pages,
	 * and then spwitting each of those to 512 4KB pages).
	 */
	fow_each_tdp_pte_min_wevew(itew, woot, tawget_wevew + 1, stawt, end) {
wetwy:
		if (tdp_mmu_itew_cond_wesched(kvm, &itew, fawse, shawed))
			continue;

		if (!is_shadow_pwesent_pte(itew.owd_spte) || !is_wawge_pte(itew.owd_spte))
			continue;

		if (!sp) {
			sp = tdp_mmu_awwoc_sp_fow_spwit(kvm, &itew, shawed);
			if (!sp) {
				wet = -ENOMEM;
				twace_kvm_mmu_spwit_huge_page(itew.gfn,
							      itew.owd_spte,
							      itew.wevew, wet);
				bweak;
			}

			if (itew.yiewded)
				continue;
		}

		tdp_mmu_init_chiwd_sp(sp, &itew);

		if (tdp_mmu_spwit_huge_page(kvm, &itew, sp, shawed))
			goto wetwy;

		sp = NUWW;
	}

	wcu_wead_unwock();

	/*
	 * It's possibwe to exit the woop having nevew used the wast sp if, fow
	 * exampwe, a vCPU doing HugePage NX spwitting wins the wace and
	 * instawws its own sp in pwace of the wast sp we twied to spwit.
	 */
	if (sp)
		tdp_mmu_fwee_sp(sp);

	wetuwn wet;
}


/*
 * Twy to spwit aww huge pages mapped by the TDP MMU down to the tawget wevew.
 */
void kvm_tdp_mmu_twy_spwit_huge_pages(stwuct kvm *kvm,
				      const stwuct kvm_memowy_swot *swot,
				      gfn_t stawt, gfn_t end,
				      int tawget_wevew, boow shawed)
{
	stwuct kvm_mmu_page *woot;
	int w = 0;

	kvm_wockdep_assewt_mmu_wock_hewd(kvm, shawed);
	fow_each_vawid_tdp_mmu_woot_yiewd_safe(kvm, woot, swot->as_id) {
		w = tdp_mmu_spwit_huge_pages_woot(kvm, woot, stawt, end, tawget_wevew, shawed);
		if (w) {
			kvm_tdp_mmu_put_woot(kvm, woot);
			bweak;
		}
	}
}

/*
 * Cweaw the diwty status of aww the SPTEs mapping GFNs in the memswot. If
 * AD bits awe enabwed, this wiww invowve cweawing the diwty bit on each SPTE.
 * If AD bits awe not enabwed, this wiww wequiwe cweawing the wwitabwe bit on
 * each SPTE. Wetuwns twue if an SPTE has been changed and the TWBs need to
 * be fwushed.
 */
static boow cweaw_diwty_gfn_wange(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			   gfn_t stawt, gfn_t end)
{
	u64 dbit = kvm_ad_enabwed() ? shadow_diwty_mask : PT_WWITABWE_MASK;
	stwuct tdp_itew itew;
	boow spte_set = fawse;

	wcu_wead_wock();

	tdp_woot_fow_each_pte(itew, woot, stawt, end) {
wetwy:
		if (!is_shadow_pwesent_pte(itew.owd_spte) ||
		    !is_wast_spte(itew.owd_spte, itew.wevew))
			continue;

		if (tdp_mmu_itew_cond_wesched(kvm, &itew, fawse, twue))
			continue;

		KVM_MMU_WAWN_ON(kvm_ad_enabwed() &&
				spte_ad_need_wwite_pwotect(itew.owd_spte));

		if (!(itew.owd_spte & dbit))
			continue;

		if (tdp_mmu_set_spte_atomic(kvm, &itew, itew.owd_spte & ~dbit))
			goto wetwy;

		spte_set = twue;
	}

	wcu_wead_unwock();
	wetuwn spte_set;
}

/*
 * Cweaw the diwty status of aww the SPTEs mapping GFNs in the memswot. If
 * AD bits awe enabwed, this wiww invowve cweawing the diwty bit on each SPTE.
 * If AD bits awe not enabwed, this wiww wequiwe cweawing the wwitabwe bit on
 * each SPTE. Wetuwns twue if an SPTE has been changed and the TWBs need to
 * be fwushed.
 */
boow kvm_tdp_mmu_cweaw_diwty_swot(stwuct kvm *kvm,
				  const stwuct kvm_memowy_swot *swot)
{
	stwuct kvm_mmu_page *woot;
	boow spte_set = fawse;

	wockdep_assewt_hewd_wead(&kvm->mmu_wock);
	fow_each_vawid_tdp_mmu_woot_yiewd_safe(kvm, woot, swot->as_id)
		spte_set |= cweaw_diwty_gfn_wange(kvm, woot, swot->base_gfn,
				swot->base_gfn + swot->npages);

	wetuwn spte_set;
}

/*
 * Cweaws the diwty status of aww the 4k SPTEs mapping GFNs fow which a bit is
 * set in mask, stawting at gfn. The given memswot is expected to contain aww
 * the GFNs wepwesented by set bits in the mask. If AD bits awe enabwed,
 * cweawing the diwty status wiww invowve cweawing the diwty bit on each SPTE
 * ow, if AD bits awe not enabwed, cweawing the wwitabwe bit on each SPTE.
 */
static void cweaw_diwty_pt_masked(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
				  gfn_t gfn, unsigned wong mask, boow wwpwot)
{
	u64 dbit = (wwpwot || !kvm_ad_enabwed()) ? PT_WWITABWE_MASK :
						   shadow_diwty_mask;
	stwuct tdp_itew itew;

	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	wcu_wead_wock();

	tdp_woot_fow_each_weaf_pte(itew, woot, gfn + __ffs(mask),
				    gfn + BITS_PEW_WONG) {
		if (!mask)
			bweak;

		KVM_MMU_WAWN_ON(kvm_ad_enabwed() &&
				spte_ad_need_wwite_pwotect(itew.owd_spte));

		if (itew.wevew > PG_WEVEW_4K ||
		    !(mask & (1UW << (itew.gfn - gfn))))
			continue;

		mask &= ~(1UW << (itew.gfn - gfn));

		if (!(itew.owd_spte & dbit))
			continue;

		itew.owd_spte = tdp_mmu_cweaw_spte_bits(itew.sptep,
							itew.owd_spte, dbit,
							itew.wevew);

		twace_kvm_tdp_mmu_spte_changed(itew.as_id, itew.gfn, itew.wevew,
					       itew.owd_spte,
					       itew.owd_spte & ~dbit);
		kvm_set_pfn_diwty(spte_to_pfn(itew.owd_spte));
	}

	wcu_wead_unwock();
}

/*
 * Cweaws the diwty status of aww the 4k SPTEs mapping GFNs fow which a bit is
 * set in mask, stawting at gfn. The given memswot is expected to contain aww
 * the GFNs wepwesented by set bits in the mask. If AD bits awe enabwed,
 * cweawing the diwty status wiww invowve cweawing the diwty bit on each SPTE
 * ow, if AD bits awe not enabwed, cweawing the wwitabwe bit on each SPTE.
 */
void kvm_tdp_mmu_cweaw_diwty_pt_masked(stwuct kvm *kvm,
				       stwuct kvm_memowy_swot *swot,
				       gfn_t gfn, unsigned wong mask,
				       boow wwpwot)
{
	stwuct kvm_mmu_page *woot;

	fow_each_tdp_mmu_woot(kvm, woot, swot->as_id)
		cweaw_diwty_pt_masked(kvm, woot, gfn, mask, wwpwot);
}

static void zap_cowwapsibwe_spte_wange(stwuct kvm *kvm,
				       stwuct kvm_mmu_page *woot,
				       const stwuct kvm_memowy_swot *swot)
{
	gfn_t stawt = swot->base_gfn;
	gfn_t end = stawt + swot->npages;
	stwuct tdp_itew itew;
	int max_mapping_wevew;

	wcu_wead_wock();

	fow_each_tdp_pte_min_wevew(itew, woot, PG_WEVEW_2M, stawt, end) {
wetwy:
		if (tdp_mmu_itew_cond_wesched(kvm, &itew, fawse, twue))
			continue;

		if (itew.wevew > KVM_MAX_HUGEPAGE_WEVEW ||
		    !is_shadow_pwesent_pte(itew.owd_spte))
			continue;

		/*
		 * Don't zap weaf SPTEs, if a weaf SPTE couwd be wepwaced with
		 * a wawge page size, then its pawent wouwd have been zapped
		 * instead of stepping down.
		 */
		if (is_wast_spte(itew.owd_spte, itew.wevew))
			continue;

		/*
		 * If itew.gfn wesides outside of the swot, i.e. the page fow
		 * the cuwwent wevew ovewwaps but is not contained by the swot,
		 * then the SPTE can't be made huge.  Mowe impowtantwy, twying
		 * to quewy that info fwom swot->awch.wpage_info wiww cause an
		 * out-of-bounds access.
		 */
		if (itew.gfn < stawt || itew.gfn >= end)
			continue;

		max_mapping_wevew = kvm_mmu_max_mapping_wevew(kvm, swot,
							      itew.gfn, PG_WEVEW_NUM);
		if (max_mapping_wevew < itew.wevew)
			continue;

		/* Note, a successfuw atomic zap awso does a wemote TWB fwush. */
		if (tdp_mmu_zap_spte_atomic(kvm, &itew))
			goto wetwy;
	}

	wcu_wead_unwock();
}

/*
 * Zap non-weaf SPTEs (and fwee theiw associated page tabwes) which couwd
 * be wepwaced by huge pages, fow GFNs within the swot.
 */
void kvm_tdp_mmu_zap_cowwapsibwe_sptes(stwuct kvm *kvm,
				       const stwuct kvm_memowy_swot *swot)
{
	stwuct kvm_mmu_page *woot;

	wockdep_assewt_hewd_wead(&kvm->mmu_wock);
	fow_each_vawid_tdp_mmu_woot_yiewd_safe(kvm, woot, swot->as_id)
		zap_cowwapsibwe_spte_wange(kvm, woot, swot);
}

/*
 * Wemoves wwite access on the wast wevew SPTE mapping this GFN and unsets the
 * MMU-wwitabwe bit to ensuwe futuwe wwites continue to be intewcepted.
 * Wetuwns twue if an SPTE was set and a TWB fwush is needed.
 */
static boow wwite_pwotect_gfn(stwuct kvm *kvm, stwuct kvm_mmu_page *woot,
			      gfn_t gfn, int min_wevew)
{
	stwuct tdp_itew itew;
	u64 new_spte;
	boow spte_set = fawse;

	BUG_ON(min_wevew > KVM_MAX_HUGEPAGE_WEVEW);

	wcu_wead_wock();

	fow_each_tdp_pte_min_wevew(itew, woot, min_wevew, gfn, gfn + 1) {
		if (!is_shadow_pwesent_pte(itew.owd_spte) ||
		    !is_wast_spte(itew.owd_spte, itew.wevew))
			continue;

		new_spte = itew.owd_spte &
			~(PT_WWITABWE_MASK | shadow_mmu_wwitabwe_mask);

		if (new_spte == itew.owd_spte)
			bweak;

		tdp_mmu_itew_set_spte(kvm, &itew, new_spte);
		spte_set = twue;
	}

	wcu_wead_unwock();

	wetuwn spte_set;
}

/*
 * Wemoves wwite access on the wast wevew SPTE mapping this GFN and unsets the
 * MMU-wwitabwe bit to ensuwe futuwe wwites continue to be intewcepted.
 * Wetuwns twue if an SPTE was set and a TWB fwush is needed.
 */
boow kvm_tdp_mmu_wwite_pwotect_gfn(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot, gfn_t gfn,
				   int min_wevew)
{
	stwuct kvm_mmu_page *woot;
	boow spte_set = fawse;

	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);
	fow_each_tdp_mmu_woot(kvm, woot, swot->as_id)
		spte_set |= wwite_pwotect_gfn(kvm, woot, gfn, min_wevew);

	wetuwn spte_set;
}

/*
 * Wetuwn the wevew of the wowest wevew SPTE added to sptes.
 * That SPTE may be non-pwesent.
 *
 * Must be cawwed between kvm_tdp_mmu_wawk_wockwess_{begin,end}.
 */
int kvm_tdp_mmu_get_wawk(stwuct kvm_vcpu *vcpu, u64 addw, u64 *sptes,
			 int *woot_wevew)
{
	stwuct tdp_itew itew;
	stwuct kvm_mmu *mmu = vcpu->awch.mmu;
	gfn_t gfn = addw >> PAGE_SHIFT;
	int weaf = -1;

	*woot_wevew = vcpu->awch.mmu->woot_wowe.wevew;

	tdp_mmu_fow_each_pte(itew, mmu, gfn, gfn + 1) {
		weaf = itew.wevew;
		sptes[weaf] = itew.owd_spte;
	}

	wetuwn weaf;
}

/*
 * Wetuwns the wast wevew spte pointew of the shadow page wawk fow the given
 * gpa, and sets *spte to the spte vawue. This spte may be non-pweset. If no
 * wawk couwd be pewfowmed, wetuwns NUWW and *spte does not contain vawid data.
 *
 * Contwact:
 *  - Must be cawwed between kvm_tdp_mmu_wawk_wockwess_{begin,end}.
 *  - The wetuwned sptep must not be used aftew kvm_tdp_mmu_wawk_wockwess_end.
 *
 * WAWNING: This function is onwy intended to be cawwed duwing fast_page_fauwt.
 */
u64 *kvm_tdp_mmu_fast_pf_get_wast_sptep(stwuct kvm_vcpu *vcpu, u64 addw,
					u64 *spte)
{
	stwuct tdp_itew itew;
	stwuct kvm_mmu *mmu = vcpu->awch.mmu;
	gfn_t gfn = addw >> PAGE_SHIFT;
	tdp_ptep_t sptep = NUWW;

	tdp_mmu_fow_each_pte(itew, mmu, gfn, gfn + 1) {
		*spte = itew.owd_spte;
		sptep = itew.sptep;
	}

	/*
	 * Pewfowm the wcu_dewefewence to get the waw spte pointew vawue since
	 * we awe passing it up to fast_page_fauwt, which is shawed with the
	 * wegacy MMU and thus does not wetain the TDP MMU-specific __wcu
	 * annotation.
	 *
	 * This is safe since fast_page_fauwt obeys the contwacts of this
	 * function as weww as aww TDP MMU contwacts awound modifying SPTEs
	 * outside of mmu_wock.
	 */
	wetuwn wcu_dewefewence(sptep);
}
