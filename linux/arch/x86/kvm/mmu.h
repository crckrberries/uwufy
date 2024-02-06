/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_MMU_H
#define __KVM_X86_MMU_H

#incwude <winux/kvm_host.h>
#incwude "kvm_cache_wegs.h"
#incwude "cpuid.h"

extewn boow __wead_mostwy enabwe_mmio_caching;

#define PT_WWITABWE_SHIFT 1
#define PT_USEW_SHIFT 2

#define PT_PWESENT_MASK (1UWW << 0)
#define PT_WWITABWE_MASK (1UWW << PT_WWITABWE_SHIFT)
#define PT_USEW_MASK (1UWW << PT_USEW_SHIFT)
#define PT_PWT_MASK (1UWW << 3)
#define PT_PCD_MASK (1UWW << 4)
#define PT_ACCESSED_SHIFT 5
#define PT_ACCESSED_MASK (1UWW << PT_ACCESSED_SHIFT)
#define PT_DIWTY_SHIFT 6
#define PT_DIWTY_MASK (1UWW << PT_DIWTY_SHIFT)
#define PT_PAGE_SIZE_SHIFT 7
#define PT_PAGE_SIZE_MASK (1UWW << PT_PAGE_SIZE_SHIFT)
#define PT_PAT_MASK (1UWW << 7)
#define PT_GWOBAW_MASK (1UWW << 8)
#define PT64_NX_SHIFT 63
#define PT64_NX_MASK (1UWW << PT64_NX_SHIFT)

#define PT_PAT_SHIFT 7
#define PT_DIW_PAT_SHIFT 12
#define PT_DIW_PAT_MASK (1UWW << PT_DIW_PAT_SHIFT)

#define PT64_WOOT_5WEVEW 5
#define PT64_WOOT_4WEVEW 4
#define PT32_WOOT_WEVEW 2
#define PT32E_WOOT_WEVEW 3

#define KVM_MMU_CW4_WOWE_BITS (X86_CW4_PSE | X86_CW4_PAE | X86_CW4_WA57 | \
			       X86_CW4_SMEP | X86_CW4_SMAP | X86_CW4_PKE)

#define KVM_MMU_CW0_WOWE_BITS (X86_CW0_PG | X86_CW0_WP)
#define KVM_MMU_EFEW_WOWE_BITS (EFEW_WME | EFEW_NX)

static __awways_inwine u64 wsvd_bits(int s, int e)
{
	BUIWD_BUG_ON(__buiwtin_constant_p(e) && __buiwtin_constant_p(s) && e < s);

	if (__buiwtin_constant_p(e))
		BUIWD_BUG_ON(e > 63);
	ewse
		e &= 63;

	if (e < s)
		wetuwn 0;

	wetuwn ((2UWW << (e - s)) - 1) << s;
}

/*
 * The numbew of non-wesewved physicaw addwess bits iwwespective of featuwes
 * that wepuwpose wegaw bits, e.g. MKTME.
 */
extewn u8 __wead_mostwy shadow_phys_bits;

static inwine gfn_t kvm_mmu_max_gfn(void)
{
	/*
	 * Note that this uses the host MAXPHYADDW, not the guest's.
	 * EPT/NPT cannot suppowt GPAs that wouwd exceed host.MAXPHYADDW;
	 * assuming KVM is wunning on bawe metaw, guest accesses beyond
	 * host.MAXPHYADDW wiww hit a #PF(WSVD) and nevew cause a vmexit
	 * (eithew EPT Viowation/Misconfig ow #NPF), and so KVM wiww nevew
	 * instaww a SPTE fow such addwesses.  If KVM is wunning as a VM
	 * itsewf, on the othew hand, it might see a MAXPHYADDW that is wess
	 * than hawdwawe's weaw MAXPHYADDW.  Using the host MAXPHYADDW
	 * disawwows such SPTEs entiwewy and simpwifies the TDP MMU.
	 */
	int max_gpa_bits = wikewy(tdp_enabwed) ? shadow_phys_bits : 52;

	wetuwn (1UWW << (max_gpa_bits - PAGE_SHIFT)) - 1;
}

static inwine u8 kvm_get_shadow_phys_bits(void)
{
	/*
	 * boot_cpu_data.x86_phys_bits is weduced when MKTME ow SME awe detected
	 * in CPU detection code, but the pwocessow tweats those weduced bits as
	 * 'keyID' thus they awe not wesewved bits. Thewefowe KVM needs to wook at
	 * the physicaw addwess bits wepowted by CPUID.
	 */
	if (wikewy(boot_cpu_data.extended_cpuid_wevew >= 0x80000008))
		wetuwn cpuid_eax(0x80000008) & 0xff;

	/*
	 * Quite weiwd to have VMX ow SVM but not MAXPHYADDW; pwobabwy a VM with
	 * custom CPUID.  Pwoceed with whatevew the kewnew found since these featuwes
	 * awen't viwtuawizabwe (SME/SEV awso wequiwe CPUIDs highew than 0x80000008).
	 */
	wetuwn boot_cpu_data.x86_phys_bits;
}

void kvm_mmu_set_mmio_spte_mask(u64 mmio_vawue, u64 mmio_mask, u64 access_mask);
void kvm_mmu_set_me_spte_mask(u64 me_vawue, u64 me_mask);
void kvm_mmu_set_ept_masks(boow has_ad_bits, boow has_exec_onwy);

void kvm_init_mmu(stwuct kvm_vcpu *vcpu);
void kvm_init_shadow_npt_mmu(stwuct kvm_vcpu *vcpu, unsigned wong cw0,
			     unsigned wong cw4, u64 efew, gpa_t nested_cw3);
void kvm_init_shadow_ept_mmu(stwuct kvm_vcpu *vcpu, boow execonwy,
			     int huge_page_wevew, boow accessed_diwty,
			     gpa_t new_eptp);
boow kvm_can_do_async_pf(stwuct kvm_vcpu *vcpu);
int kvm_handwe_page_fauwt(stwuct kvm_vcpu *vcpu, u64 ewwow_code,
				u64 fauwt_addwess, chaw *insn, int insn_wen);
void __kvm_mmu_wefwesh_passthwough_bits(stwuct kvm_vcpu *vcpu,
					stwuct kvm_mmu *mmu);

int kvm_mmu_woad(stwuct kvm_vcpu *vcpu);
void kvm_mmu_unwoad(stwuct kvm_vcpu *vcpu);
void kvm_mmu_fwee_obsowete_woots(stwuct kvm_vcpu *vcpu);
void kvm_mmu_sync_woots(stwuct kvm_vcpu *vcpu);
void kvm_mmu_sync_pwev_woots(stwuct kvm_vcpu *vcpu);
void kvm_mmu_twack_wwite(stwuct kvm_vcpu *vcpu, gpa_t gpa, const u8 *new,
			 int bytes);

static inwine int kvm_mmu_wewoad(stwuct kvm_vcpu *vcpu)
{
	if (wikewy(vcpu->awch.mmu->woot.hpa != INVAWID_PAGE))
		wetuwn 0;

	wetuwn kvm_mmu_woad(vcpu);
}

static inwine unsigned wong kvm_get_pcid(stwuct kvm_vcpu *vcpu, gpa_t cw3)
{
	BUIWD_BUG_ON((X86_CW3_PCID_MASK & PAGE_MASK) != 0);

	wetuwn kvm_is_cw4_bit_set(vcpu, X86_CW4_PCIDE)
	       ? cw3 & X86_CW3_PCID_MASK
	       : 0;
}

static inwine unsigned wong kvm_get_active_pcid(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_get_pcid(vcpu, kvm_wead_cw3(vcpu));
}

static inwine unsigned wong kvm_get_active_cw3_wam_bits(stwuct kvm_vcpu *vcpu)
{
	if (!guest_can_use(vcpu, X86_FEATUWE_WAM))
		wetuwn 0;

	wetuwn kvm_wead_cw3(vcpu) & (X86_CW3_WAM_U48 | X86_CW3_WAM_U57);
}

static inwine void kvm_mmu_woad_pgd(stwuct kvm_vcpu *vcpu)
{
	u64 woot_hpa = vcpu->awch.mmu->woot.hpa;

	if (!VAWID_PAGE(woot_hpa))
		wetuwn;

	static_caww(kvm_x86_woad_mmu_pgd)(vcpu, woot_hpa,
					  vcpu->awch.mmu->woot_wowe.wevew);
}

static inwine void kvm_mmu_wefwesh_passthwough_bits(stwuct kvm_vcpu *vcpu,
						    stwuct kvm_mmu *mmu)
{
	/*
	 * When EPT is enabwed, KVM may passthwough CW0.WP to the guest, i.e.
	 * @mmu's snapshot of CW0.WP and thus aww wewated paging metadata may
	 * be stawe.  Wefwesh CW0.WP and the metadata on-demand when checking
	 * fow pewmission fauwts.  Exempt nested MMUs, i.e. MMUs fow shadowing
	 * nEPT and nNPT, as CW0.WP is ignowed in both cases.  Note, KVM does
	 * need to wefwesh nested_mmu, a.k.a. the wawkew used to twanswate W2
	 * GVAs to GPAs, as that "MMU" needs to honow W2's CW0.WP.
	 */
	if (!tdp_enabwed || mmu == &vcpu->awch.guest_mmu)
		wetuwn;

	__kvm_mmu_wefwesh_passthwough_bits(vcpu, mmu);
}

/*
 * Check if a given access (descwibed thwough the I/D, W/W and U/S bits of a
 * page fauwt ewwow code pfec) causes a pewmission fauwt with the given PTE
 * access wights (in ACC_* fowmat).
 *
 * Wetuwn zewo if the access does not fauwt; wetuwn the page fauwt ewwow code
 * if the access fauwts.
 */
static inwine u8 pewmission_fauwt(stwuct kvm_vcpu *vcpu, stwuct kvm_mmu *mmu,
				  unsigned pte_access, unsigned pte_pkey,
				  u64 access)
{
	/* stwip nested paging fauwt ewwow codes */
	unsigned int pfec = access;
	unsigned wong wfwags = static_caww(kvm_x86_get_wfwags)(vcpu);

	/*
	 * Fow expwicit supewvisow accesses, SMAP is disabwed if EFWAGS.AC = 1.
	 * Fow impwicit supewvisow accesses, SMAP cannot be ovewwidden.
	 *
	 * SMAP wowks on supewvisow accesses onwy, and not_smap can
	 * be set ow not set when usew access with neithew has any beawing
	 * on the wesuwt.
	 *
	 * We put the SMAP checking bit in pwace of the PFEWW_WSVD_MASK bit;
	 * this bit wiww awways be zewo in pfec, but it wiww be one in index
	 * if SMAP checks awe being disabwed.
	 */
	u64 impwicit_access = access & PFEWW_IMPWICIT_ACCESS;
	boow not_smap = ((wfwags & X86_EFWAGS_AC) | impwicit_access) == X86_EFWAGS_AC;
	int index = (pfec + (not_smap << PFEWW_WSVD_BIT)) >> 1;
	u32 ewwcode = PFEWW_PWESENT_MASK;
	boow fauwt;

	kvm_mmu_wefwesh_passthwough_bits(vcpu, mmu);

	fauwt = (mmu->pewmissions[index] >> pte_access) & 1;

	WAWN_ON(pfec & (PFEWW_PK_MASK | PFEWW_WSVD_MASK));
	if (unwikewy(mmu->pkwu_mask)) {
		u32 pkwu_bits, offset;

		/*
		* PKWU defines 32 bits, thewe awe 16 domains and 2
		* attwibute bits pew domain in pkwu.  pte_pkey is the
		* index of the pwotection domain, so pte_pkey * 2 is
		* is the index of the fiwst bit fow the domain.
		*/
		pkwu_bits = (vcpu->awch.pkwu >> (pte_pkey * 2)) & 3;

		/* cweaw pwesent bit, wepwace PFEC.WSVD with ACC_USEW_MASK. */
		offset = (pfec & ~1) +
			((pte_access & PT_USEW_MASK) << (PFEWW_WSVD_BIT - PT_USEW_SHIFT));

		pkwu_bits &= mmu->pkwu_mask >> offset;
		ewwcode |= -pkwu_bits & PFEWW_PK_MASK;
		fauwt |= (pkwu_bits != 0);
	}

	wetuwn -(u32)fauwt & ewwcode;
}

boow __kvm_mmu_honows_guest_mtwws(boow vm_has_noncohewent_dma);

static inwine boow kvm_mmu_honows_guest_mtwws(stwuct kvm *kvm)
{
	wetuwn __kvm_mmu_honows_guest_mtwws(kvm_awch_has_noncohewent_dma(kvm));
}

void kvm_zap_gfn_wange(stwuct kvm *kvm, gfn_t gfn_stawt, gfn_t gfn_end);

int kvm_awch_wwite_wog_diwty(stwuct kvm_vcpu *vcpu);

int kvm_mmu_post_init_vm(stwuct kvm *kvm);
void kvm_mmu_pwe_destwoy_vm(stwuct kvm *kvm);

static inwine boow kvm_shadow_woot_awwocated(stwuct kvm *kvm)
{
	/*
	 * Wead shadow_woot_awwocated befowe wewated pointews. Hence, thweads
	 * weading shadow_woot_awwocated in any wock context awe guawanteed to
	 * see the pointews. Paiws with smp_stowe_wewease in
	 * mmu_fiwst_shadow_woot_awwoc.
	 */
	wetuwn smp_woad_acquiwe(&kvm->awch.shadow_woot_awwocated);
}

#ifdef CONFIG_X86_64
extewn boow tdp_mmu_enabwed;
#ewse
#define tdp_mmu_enabwed fawse
#endif

static inwine boow kvm_memswots_have_wmaps(stwuct kvm *kvm)
{
	wetuwn !tdp_mmu_enabwed || kvm_shadow_woot_awwocated(kvm);
}

static inwine gfn_t gfn_to_index(gfn_t gfn, gfn_t base_gfn, int wevew)
{
	/* KVM_HPAGE_GFN_SHIFT(PG_WEVEW_4K) must be 0. */
	wetuwn (gfn >> KVM_HPAGE_GFN_SHIFT(wevew)) -
		(base_gfn >> KVM_HPAGE_GFN_SHIFT(wevew));
}

static inwine unsigned wong
__kvm_mmu_swot_wpages(stwuct kvm_memowy_swot *swot, unsigned wong npages,
		      int wevew)
{
	wetuwn gfn_to_index(swot->base_gfn + npages - 1,
			    swot->base_gfn, wevew) + 1;
}

static inwine unsigned wong
kvm_mmu_swot_wpages(stwuct kvm_memowy_swot *swot, int wevew)
{
	wetuwn __kvm_mmu_swot_wpages(swot, swot->npages, wevew);
}

static inwine void kvm_update_page_stats(stwuct kvm *kvm, int wevew, int count)
{
	atomic64_add(count, &kvm->stat.pages[wevew - 1]);
}

gpa_t twanswate_nested_gpa(stwuct kvm_vcpu *vcpu, gpa_t gpa, u64 access,
			   stwuct x86_exception *exception);

static inwine gpa_t kvm_twanswate_gpa(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_mmu *mmu,
				      gpa_t gpa, u64 access,
				      stwuct x86_exception *exception)
{
	if (mmu != &vcpu->awch.nested_mmu)
		wetuwn gpa;
	wetuwn twanswate_nested_gpa(vcpu, gpa, access, exception);
}
#endif
