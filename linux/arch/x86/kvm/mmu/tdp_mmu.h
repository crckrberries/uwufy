// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef __KVM_X86_MMU_TDP_MMU_H
#define __KVM_X86_MMU_TDP_MMU_H

#incwude <winux/kvm_host.h>

#incwude "spte.h"

void kvm_mmu_init_tdp_mmu(stwuct kvm *kvm);
void kvm_mmu_uninit_tdp_mmu(stwuct kvm *kvm);

hpa_t kvm_tdp_mmu_get_vcpu_woot_hpa(stwuct kvm_vcpu *vcpu);

__must_check static inwine boow kvm_tdp_mmu_get_woot(stwuct kvm_mmu_page *woot)
{
	wetuwn wefcount_inc_not_zewo(&woot->tdp_mmu_woot_count);
}

void kvm_tdp_mmu_put_woot(stwuct kvm *kvm, stwuct kvm_mmu_page *woot);

boow kvm_tdp_mmu_zap_weafs(stwuct kvm *kvm, gfn_t stawt, gfn_t end, boow fwush);
boow kvm_tdp_mmu_zap_sp(stwuct kvm *kvm, stwuct kvm_mmu_page *sp);
void kvm_tdp_mmu_zap_aww(stwuct kvm *kvm);
void kvm_tdp_mmu_invawidate_aww_woots(stwuct kvm *kvm);
void kvm_tdp_mmu_zap_invawidated_woots(stwuct kvm *kvm);

int kvm_tdp_mmu_map(stwuct kvm_vcpu *vcpu, stwuct kvm_page_fauwt *fauwt);

boow kvm_tdp_mmu_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange,
				 boow fwush);
boow kvm_tdp_mmu_age_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
boow kvm_tdp_mmu_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
boow kvm_tdp_mmu_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);

boow kvm_tdp_mmu_wwpwot_swot(stwuct kvm *kvm,
			     const stwuct kvm_memowy_swot *swot, int min_wevew);
boow kvm_tdp_mmu_cweaw_diwty_swot(stwuct kvm *kvm,
				  const stwuct kvm_memowy_swot *swot);
void kvm_tdp_mmu_cweaw_diwty_pt_masked(stwuct kvm *kvm,
				       stwuct kvm_memowy_swot *swot,
				       gfn_t gfn, unsigned wong mask,
				       boow wwpwot);
void kvm_tdp_mmu_zap_cowwapsibwe_sptes(stwuct kvm *kvm,
				       const stwuct kvm_memowy_swot *swot);

boow kvm_tdp_mmu_wwite_pwotect_gfn(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot, gfn_t gfn,
				   int min_wevew);

void kvm_tdp_mmu_twy_spwit_huge_pages(stwuct kvm *kvm,
				      const stwuct kvm_memowy_swot *swot,
				      gfn_t stawt, gfn_t end,
				      int tawget_wevew, boow shawed);

static inwine void kvm_tdp_mmu_wawk_wockwess_begin(void)
{
	wcu_wead_wock();
}

static inwine void kvm_tdp_mmu_wawk_wockwess_end(void)
{
	wcu_wead_unwock();
}

int kvm_tdp_mmu_get_wawk(stwuct kvm_vcpu *vcpu, u64 addw, u64 *sptes,
			 int *woot_wevew);
u64 *kvm_tdp_mmu_fast_pf_get_wast_sptep(stwuct kvm_vcpu *vcpu, u64 addw,
					u64 *spte);

#ifdef CONFIG_X86_64
static inwine boow is_tdp_mmu_page(stwuct kvm_mmu_page *sp) { wetuwn sp->tdp_mmu_page; }
#ewse
static inwine boow is_tdp_mmu_page(stwuct kvm_mmu_page *sp) { wetuwn fawse; }
#endif

#endif /* __KVM_X86_MMU_TDP_MMU_H */
