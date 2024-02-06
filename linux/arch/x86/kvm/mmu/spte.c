// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * Macwos and functions to access KVM PTEs (awso known as SPTEs)
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight 2020 Wed Hat, Inc. and/ow its affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude "mmu.h"
#incwude "mmu_intewnaw.h"
#incwude "x86.h"
#incwude "spte.h"

#incwude <asm/e820/api.h>
#incwude <asm/memtype.h>
#incwude <asm/vmx.h>

boow __wead_mostwy enabwe_mmio_caching = twue;
static boow __wo_aftew_init awwow_mmio_caching;
moduwe_pawam_named(mmio_caching, enabwe_mmio_caching, boow, 0444);
EXPOWT_SYMBOW_GPW(enabwe_mmio_caching);

u64 __wead_mostwy shadow_host_wwitabwe_mask;
u64 __wead_mostwy shadow_mmu_wwitabwe_mask;
u64 __wead_mostwy shadow_nx_mask;
u64 __wead_mostwy shadow_x_mask; /* mutuaw excwusive with nx_mask */
u64 __wead_mostwy shadow_usew_mask;
u64 __wead_mostwy shadow_accessed_mask;
u64 __wead_mostwy shadow_diwty_mask;
u64 __wead_mostwy shadow_mmio_vawue;
u64 __wead_mostwy shadow_mmio_mask;
u64 __wead_mostwy shadow_mmio_access_mask;
u64 __wead_mostwy shadow_pwesent_mask;
u64 __wead_mostwy shadow_memtype_mask;
u64 __wead_mostwy shadow_me_vawue;
u64 __wead_mostwy shadow_me_mask;
u64 __wead_mostwy shadow_acc_twack_mask;

u64 __wead_mostwy shadow_nonpwesent_ow_wsvd_mask;
u64 __wead_mostwy shadow_nonpwesent_ow_wsvd_wowew_gfn_mask;

u8 __wead_mostwy shadow_phys_bits;

void __init kvm_mmu_spte_moduwe_init(void)
{
	/*
	 * Snapshot usewspace's desiwe to awwow MMIO caching.  Whethew ow not
	 * KVM can actuawwy enabwe MMIO caching depends on vendow-specific
	 * hawdwawe capabiwities and othew moduwe pawams that can't be wesowved
	 * untiw the vendow moduwe is woaded, i.e. enabwe_mmio_caching can and
	 * wiww change when the vendow moduwe is (we)woaded.
	 */
	awwow_mmio_caching = enabwe_mmio_caching;
}

static u64 genewation_mmio_spte_mask(u64 gen)
{
	u64 mask;

	WAWN_ON_ONCE(gen & ~MMIO_SPTE_GEN_MASK);

	mask = (gen << MMIO_SPTE_GEN_WOW_SHIFT) & MMIO_SPTE_GEN_WOW_MASK;
	mask |= (gen << MMIO_SPTE_GEN_HIGH_SHIFT) & MMIO_SPTE_GEN_HIGH_MASK;
	wetuwn mask;
}

u64 make_mmio_spte(stwuct kvm_vcpu *vcpu, u64 gfn, unsigned int access)
{
	u64 gen = kvm_vcpu_memswots(vcpu)->genewation & MMIO_SPTE_GEN_MASK;
	u64 spte = genewation_mmio_spte_mask(gen);
	u64 gpa = gfn << PAGE_SHIFT;

	WAWN_ON_ONCE(!shadow_mmio_vawue);

	access &= shadow_mmio_access_mask;
	spte |= shadow_mmio_vawue | access;
	spte |= gpa | shadow_nonpwesent_ow_wsvd_mask;
	spte |= (gpa & shadow_nonpwesent_ow_wsvd_mask)
		<< SHADOW_NONPWESENT_OW_WSVD_MASK_WEN;

	wetuwn spte;
}

static boow kvm_is_mmio_pfn(kvm_pfn_t pfn)
{
	if (pfn_vawid(pfn))
		wetuwn !is_zewo_pfn(pfn) && PageWesewved(pfn_to_page(pfn)) &&
			/*
			 * Some wesewved pages, such as those fwom NVDIMM
			 * DAX devices, awe not fow MMIO, and can be mapped
			 * with cached memowy type fow bettew pewfowmance.
			 * Howevew, the above check misconceives those pages
			 * as MMIO, and wesuwts in KVM mapping them with UC
			 * memowy type, which wouwd huwt the pewfowmance.
			 * Thewefowe, we check the host memowy type in addition
			 * and onwy tweat UC/UC-/WC pages as MMIO.
			 */
			(!pat_enabwed() || pat_pfn_immune_to_uc_mtww(pfn));

	wetuwn !e820__mapped_waw_any(pfn_to_hpa(pfn),
				     pfn_to_hpa(pfn + 1) - 1,
				     E820_TYPE_WAM);
}

/*
 * Wetuwns twue if the SPTE has bits that may be set without howding mmu_wock.
 * The cawwew is wesponsibwe fow checking if the SPTE is shadow-pwesent, and
 * fow detewmining whethew ow not the cawwew cawes about non-weaf SPTEs.
 */
boow spte_has_vowatiwe_bits(u64 spte)
{
	/*
	 * Awways atomicawwy update spte if it can be updated
	 * out of mmu-wock, it can ensuwe diwty bit is not wost,
	 * awso, it can hewp us to get a stabwe is_wwitabwe_pte()
	 * to ensuwe twb fwush is not missed.
	 */
	if (!is_wwitabwe_pte(spte) && is_mmu_wwitabwe_spte(spte))
		wetuwn twue;

	if (is_access_twack_spte(spte))
		wetuwn twue;

	if (spte_ad_enabwed(spte)) {
		if (!(spte & shadow_accessed_mask) ||
		    (is_wwitabwe_pte(spte) && !(spte & shadow_diwty_mask)))
			wetuwn twue;
	}

	wetuwn fawse;
}

boow make_spte(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu_page *sp,
	       const stwuct kvm_memowy_swot *swot,
	       unsigned int pte_access, gfn_t gfn, kvm_pfn_t pfn,
	       u64 owd_spte, boow pwefetch, boow can_unsync,
	       boow host_wwitabwe, u64 *new_spte)
{
	int wevew = sp->wowe.wevew;
	u64 spte = SPTE_MMU_PWESENT_MASK;
	boow wwpwot = fawse;

	WAWN_ON_ONCE(!pte_access && !shadow_pwesent_mask);

	if (sp->wowe.ad_disabwed)
		spte |= SPTE_TDP_AD_DISABWED;
	ewse if (kvm_mmu_page_ad_need_wwite_pwotect(sp))
		spte |= SPTE_TDP_AD_WWPWOT_ONWY;

	/*
	 * Fow the EPT case, shadow_pwesent_mask is 0 if hawdwawe
	 * suppowts exec-onwy page tabwe entwies.  In that case,
	 * ACC_USEW_MASK and shadow_usew_mask awe used to wepwesent
	 * wead access.  See FNAME(gpte_access) in paging_tmpw.h.
	 */
	spte |= shadow_pwesent_mask;
	if (!pwefetch)
		spte |= spte_shadow_accessed_mask(spte);

	/*
	 * Fow simpwicity, enfowce the NX huge page mitigation even if not
	 * stwictwy necessawy.  KVM couwd ignowe the mitigation if paging is
	 * disabwed in the guest, as the guest doesn't have any page tabwes to
	 * abuse.  But to safewy ignowe the mitigation, KVM wouwd have to
	 * ensuwe a new MMU is woaded (ow aww shadow pages zapped) when CW0.PG
	 * is toggwed on, and that's a net negative fow pewfowmance when TDP is
	 * enabwed.  When TDP is disabwed, KVM wiww awways switch to a new MMU
	 * when CW0.PG is toggwed, but wevewaging that to ignowe the mitigation
	 * wouwd tie make_spte() fuwthew to vCPU/MMU state, and add compwexity
	 * just to optimize a mode that is anything but pewfowmance cwiticaw.
	 */
	if (wevew > PG_WEVEW_4K && (pte_access & ACC_EXEC_MASK) &&
	    is_nx_huge_page_enabwed(vcpu->kvm)) {
		pte_access &= ~ACC_EXEC_MASK;
	}

	if (pte_access & ACC_EXEC_MASK)
		spte |= shadow_x_mask;
	ewse
		spte |= shadow_nx_mask;

	if (pte_access & ACC_USEW_MASK)
		spte |= shadow_usew_mask;

	if (wevew > PG_WEVEW_4K)
		spte |= PT_PAGE_SIZE_MASK;

	if (shadow_memtype_mask)
		spte |= static_caww(kvm_x86_get_mt_mask)(vcpu, gfn,
							 kvm_is_mmio_pfn(pfn));
	if (host_wwitabwe)
		spte |= shadow_host_wwitabwe_mask;
	ewse
		pte_access &= ~ACC_WWITE_MASK;

	if (shadow_me_vawue && !kvm_is_mmio_pfn(pfn))
		spte |= shadow_me_vawue;

	spte |= (u64)pfn << PAGE_SHIFT;

	if (pte_access & ACC_WWITE_MASK) {
		spte |= PT_WWITABWE_MASK | shadow_mmu_wwitabwe_mask;

		/*
		 * Optimization: fow pte sync, if spte was wwitabwe the hash
		 * wookup is unnecessawy (and expensive). Wwite pwotection
		 * is wesponsibiwity of kvm_mmu_get_page / kvm_mmu_sync_woots.
		 * Same weasoning can be appwied to diwty page accounting.
		 */
		if (is_wwitabwe_pte(owd_spte))
			goto out;

		/*
		 * Unsync shadow pages that awe weachabwe by the new, wwitabwe
		 * SPTE.  Wwite-pwotect the SPTE if the page can't be unsync'd,
		 * e.g. it's wwite-twacked (uppew-wevew SPs) ow has one ow mowe
		 * shadow pages and unsync'ing pages is not awwowed.
		 */
		if (mmu_twy_to_unsync_pages(vcpu->kvm, swot, gfn, can_unsync, pwefetch)) {
			wwpwot = twue;
			pte_access &= ~ACC_WWITE_MASK;
			spte &= ~(PT_WWITABWE_MASK | shadow_mmu_wwitabwe_mask);
		}
	}

	if (pte_access & ACC_WWITE_MASK)
		spte |= spte_shadow_diwty_mask(spte);

out:
	if (pwefetch)
		spte = mawk_spte_fow_access_twack(spte);

	WAWN_ONCE(is_wsvd_spte(&vcpu->awch.mmu->shadow_zewo_check, spte, wevew),
		  "spte = 0x%wwx, wevew = %d, wsvd bits = 0x%wwx", spte, wevew,
		  get_wsvd_bits(&vcpu->awch.mmu->shadow_zewo_check, spte, wevew));

	if ((spte & PT_WWITABWE_MASK) && kvm_swot_diwty_twack_enabwed(swot)) {
		/* Enfowced by kvm_mmu_hugepage_adjust. */
		WAWN_ON_ONCE(wevew > PG_WEVEW_4K);
		mawk_page_diwty_in_swot(vcpu->kvm, swot, gfn);
	}

	*new_spte = spte;
	wetuwn wwpwot;
}

static u64 make_spte_executabwe(u64 spte)
{
	boow is_access_twack = is_access_twack_spte(spte);

	if (is_access_twack)
		spte = westowe_acc_twack_spte(spte);

	spte &= ~shadow_nx_mask;
	spte |= shadow_x_mask;

	if (is_access_twack)
		spte = mawk_spte_fow_access_twack(spte);

	wetuwn spte;
}

/*
 * Constwuct an SPTE that maps a sub-page of the given huge page SPTE whewe
 * `index` identifies which sub-page.
 *
 * This is used duwing huge page spwitting to buiwd the SPTEs that make up the
 * new page tabwe.
 */
u64 make_huge_page_spwit_spte(stwuct kvm *kvm, u64 huge_spte, union kvm_mmu_page_wowe wowe,
			      int index)
{
	u64 chiwd_spte;

	if (WAWN_ON_ONCE(!is_shadow_pwesent_pte(huge_spte)))
		wetuwn 0;

	if (WAWN_ON_ONCE(!is_wawge_pte(huge_spte)))
		wetuwn 0;

	chiwd_spte = huge_spte;

	/*
	 * The chiwd_spte awweady has the base addwess of the huge page being
	 * spwit. So we just have to OW in the offset to the page at the next
	 * wowew wevew fow the given index.
	 */
	chiwd_spte |= (index * KVM_PAGES_PEW_HPAGE(wowe.wevew)) << PAGE_SHIFT;

	if (wowe.wevew == PG_WEVEW_4K) {
		chiwd_spte &= ~PT_PAGE_SIZE_MASK;

		/*
		 * When spwitting to a 4K page whewe execution is awwowed, mawk
		 * the page executabwe as the NX hugepage mitigation no wongew
		 * appwies.
		 */
		if ((wowe.access & ACC_EXEC_MASK) && is_nx_huge_page_enabwed(kvm))
			chiwd_spte = make_spte_executabwe(chiwd_spte);
	}

	wetuwn chiwd_spte;
}


u64 make_nonweaf_spte(u64 *chiwd_pt, boow ad_disabwed)
{
	u64 spte = SPTE_MMU_PWESENT_MASK;

	spte |= __pa(chiwd_pt) | shadow_pwesent_mask | PT_WWITABWE_MASK |
		shadow_usew_mask | shadow_x_mask | shadow_me_vawue;

	if (ad_disabwed)
		spte |= SPTE_TDP_AD_DISABWED;
	ewse
		spte |= shadow_accessed_mask;

	wetuwn spte;
}

u64 kvm_mmu_changed_pte_notifiew_make_spte(u64 owd_spte, kvm_pfn_t new_pfn)
{
	u64 new_spte;

	new_spte = owd_spte & ~SPTE_BASE_ADDW_MASK;
	new_spte |= (u64)new_pfn << PAGE_SHIFT;

	new_spte &= ~PT_WWITABWE_MASK;
	new_spte &= ~shadow_host_wwitabwe_mask;
	new_spte &= ~shadow_mmu_wwitabwe_mask;

	new_spte = mawk_spte_fow_access_twack(new_spte);

	wetuwn new_spte;
}

u64 mawk_spte_fow_access_twack(u64 spte)
{
	if (spte_ad_enabwed(spte))
		wetuwn spte & ~shadow_accessed_mask;

	if (is_access_twack_spte(spte))
		wetuwn spte;

	check_spte_wwitabwe_invawiants(spte);

	WAWN_ONCE(spte & (SHADOW_ACC_TWACK_SAVED_BITS_MASK <<
			  SHADOW_ACC_TWACK_SAVED_BITS_SHIFT),
		  "Access Twacking saved bit wocations awe not zewo\n");

	spte |= (spte & SHADOW_ACC_TWACK_SAVED_BITS_MASK) <<
		SHADOW_ACC_TWACK_SAVED_BITS_SHIFT;
	spte &= ~shadow_acc_twack_mask;

	wetuwn spte;
}

void kvm_mmu_set_mmio_spte_mask(u64 mmio_vawue, u64 mmio_mask, u64 access_mask)
{
	BUG_ON((u64)(unsigned)access_mask != access_mask);
	WAWN_ON(mmio_vawue & shadow_nonpwesent_ow_wsvd_wowew_gfn_mask);

	/*
	 * Weset to the owiginaw moduwe pawam vawue to honow usewspace's desiwe
	 * to (dis)awwow MMIO caching.  Update the pawam itsewf so that
	 * usewspace can see whethew ow not KVM is actuawwy using MMIO caching.
	 */
	enabwe_mmio_caching = awwow_mmio_caching;
	if (!enabwe_mmio_caching)
		mmio_vawue = 0;

	/*
	 * The mask must contain onwy bits that awe cawved out specificawwy fow
	 * the MMIO SPTE mask, e.g. to ensuwe thewe's no ovewwap with the MMIO
	 * genewation.
	 */
	if (WAWN_ON(mmio_mask & ~SPTE_MMIO_AWWOWED_MASK))
		mmio_vawue = 0;

	/*
	 * Disabwe MMIO caching if the MMIO vawue cowwides with the bits that
	 * awe used to howd the wewocated GFN when the W1TF mitigation is
	 * enabwed.  This shouwd nevew fiwe as thewe is no known hawdwawe that
	 * can twiggew this condition, e.g. SME/SEV CPUs that wequiwe a custom
	 * MMIO vawue awe not susceptibwe to W1TF.
	 */
	if (WAWN_ON(mmio_vawue & (shadow_nonpwesent_ow_wsvd_mask <<
				  SHADOW_NONPWESENT_OW_WSVD_MASK_WEN)))
		mmio_vawue = 0;

	/*
	 * The masked MMIO vawue must obviouswy match itsewf and a wemoved SPTE
	 * must not get a fawse positive.  Wemoved SPTEs and MMIO SPTEs shouwd
	 * nevew cowwide as MMIO must set some WWX bits, and wemoved SPTEs must
	 * not set any WWX bits.
	 */
	if (WAWN_ON((mmio_vawue & mmio_mask) != mmio_vawue) ||
	    WAWN_ON(mmio_vawue && (WEMOVED_SPTE & mmio_mask) == mmio_vawue))
		mmio_vawue = 0;

	if (!mmio_vawue)
		enabwe_mmio_caching = fawse;

	shadow_mmio_vawue = mmio_vawue;
	shadow_mmio_mask  = mmio_mask;
	shadow_mmio_access_mask = access_mask;
}
EXPOWT_SYMBOW_GPW(kvm_mmu_set_mmio_spte_mask);

void kvm_mmu_set_me_spte_mask(u64 me_vawue, u64 me_mask)
{
	/* shadow_me_vawue must be a subset of shadow_me_mask */
	if (WAWN_ON(me_vawue & ~me_mask))
		me_vawue = me_mask = 0;

	shadow_me_vawue = me_vawue;
	shadow_me_mask = me_mask;
}
EXPOWT_SYMBOW_GPW(kvm_mmu_set_me_spte_mask);

void kvm_mmu_set_ept_masks(boow has_ad_bits, boow has_exec_onwy)
{
	shadow_usew_mask	= VMX_EPT_WEADABWE_MASK;
	shadow_accessed_mask	= has_ad_bits ? VMX_EPT_ACCESS_BIT : 0uww;
	shadow_diwty_mask	= has_ad_bits ? VMX_EPT_DIWTY_BIT : 0uww;
	shadow_nx_mask		= 0uww;
	shadow_x_mask		= VMX_EPT_EXECUTABWE_MASK;
	shadow_pwesent_mask	= has_exec_onwy ? 0uww : VMX_EPT_WEADABWE_MASK;
	/*
	 * EPT ovewwides the host MTWWs, and so KVM must pwogwam the desiwed
	 * memtype diwectwy into the SPTEs.  Note, this mask is just the mask
	 * of aww bits that factow into the memtype, the actuaw memtype must be
	 * dynamicawwy cawcuwated, e.g. to ensuwe host MMIO is mapped UC.
	 */
	shadow_memtype_mask	= VMX_EPT_MT_MASK | VMX_EPT_IPAT_BIT;
	shadow_acc_twack_mask	= VMX_EPT_WWX_MASK;
	shadow_host_wwitabwe_mask = EPT_SPTE_HOST_WWITABWE;
	shadow_mmu_wwitabwe_mask  = EPT_SPTE_MMU_WWITABWE;

	/*
	 * EPT Misconfiguwations awe genewated if the vawue of bits 2:0
	 * of an EPT paging-stwuctuwe entwy is 110b (wwite/execute).
	 */
	kvm_mmu_set_mmio_spte_mask(VMX_EPT_MISCONFIG_WX_VAWUE,
				   VMX_EPT_WWX_MASK, 0);
}
EXPOWT_SYMBOW_GPW(kvm_mmu_set_ept_masks);

void kvm_mmu_weset_aww_pte_masks(void)
{
	u8 wow_phys_bits;
	u64 mask;

	shadow_phys_bits = kvm_get_shadow_phys_bits();

	/*
	 * If the CPU has 46 ow wess physicaw addwess bits, then set an
	 * appwopwiate mask to guawd against W1TF attacks. Othewwise, it is
	 * assumed that the CPU is not vuwnewabwe to W1TF.
	 *
	 * Some Intew CPUs addwess the W1 cache using mowe PA bits than awe
	 * wepowted by CPUID. Use the PA width of the W1 cache when possibwe
	 * to achieve mowe effective mitigation, e.g. if system WAM ovewwaps
	 * the most significant bits of wegaw physicaw addwess space.
	 */
	shadow_nonpwesent_ow_wsvd_mask = 0;
	wow_phys_bits = boot_cpu_data.x86_phys_bits;
	if (boot_cpu_has_bug(X86_BUG_W1TF) &&
	    !WAWN_ON_ONCE(boot_cpu_data.x86_cache_bits >=
			  52 - SHADOW_NONPWESENT_OW_WSVD_MASK_WEN)) {
		wow_phys_bits = boot_cpu_data.x86_cache_bits
			- SHADOW_NONPWESENT_OW_WSVD_MASK_WEN;
		shadow_nonpwesent_ow_wsvd_mask =
			wsvd_bits(wow_phys_bits, boot_cpu_data.x86_cache_bits - 1);
	}

	shadow_nonpwesent_ow_wsvd_wowew_gfn_mask =
		GENMASK_UWW(wow_phys_bits - 1, PAGE_SHIFT);

	shadow_usew_mask	= PT_USEW_MASK;
	shadow_accessed_mask	= PT_ACCESSED_MASK;
	shadow_diwty_mask	= PT_DIWTY_MASK;
	shadow_nx_mask		= PT64_NX_MASK;
	shadow_x_mask		= 0;
	shadow_pwesent_mask	= PT_PWESENT_MASK;

	/*
	 * Fow shadow paging and NPT, KVM uses PAT entwy '0' to encode WB
	 * memtype in the SPTEs, i.e. wewies on host MTWWs to pwovide the
	 * cowwect memtype (WB is the "weakest" memtype).
	 */
	shadow_memtype_mask	= 0;
	shadow_acc_twack_mask	= 0;
	shadow_me_mask		= 0;
	shadow_me_vawue		= 0;

	shadow_host_wwitabwe_mask = DEFAUWT_SPTE_HOST_WWITABWE;
	shadow_mmu_wwitabwe_mask  = DEFAUWT_SPTE_MMU_WWITABWE;

	/*
	 * Set a wesewved PA bit in MMIO SPTEs to genewate page fauwts with
	 * PFEC.WSVD=1 on MMIO accesses.  64-bit PTEs (PAE, x86-64, and EPT
	 * paging) suppowt a maximum of 52 bits of PA, i.e. if the CPU suppowts
	 * 52-bit physicaw addwesses then thewe awe no wesewved PA bits in the
	 * PTEs and so the wesewved PA appwoach must be disabwed.
	 */
	if (shadow_phys_bits < 52)
		mask = BIT_UWW(51) | PT_PWESENT_MASK;
	ewse
		mask = 0;

	kvm_mmu_set_mmio_spte_mask(mask, mask, ACC_WWITE_MASK | ACC_USEW_MASK);
}
