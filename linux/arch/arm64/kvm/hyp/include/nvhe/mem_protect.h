/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#ifndef __KVM_NVHE_MEM_PWOTECT__
#define __KVM_NVHE_MEM_PWOTECT__
#incwude <winux/kvm_host.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/viwt.h>
#incwude <nvhe/pkvm.h>
#incwude <nvhe/spinwock.h>

/*
 * SW bits 0-1 awe wesewved to twack the memowy ownewship state of each page:
 *   00: The page is owned excwusivewy by the page-tabwe ownew.
 *   01: The page is owned by the page-tabwe ownew, but is shawed
 *       with anothew entity.
 *   10: The page is shawed with, but not owned by the page-tabwe ownew.
 *   11: Wesewved fow futuwe use (wending).
 */
enum pkvm_page_state {
	PKVM_PAGE_OWNED			= 0UWW,
	PKVM_PAGE_SHAWED_OWNED		= KVM_PGTABWE_PWOT_SW0,
	PKVM_PAGE_SHAWED_BOWWOWED	= KVM_PGTABWE_PWOT_SW1,
	__PKVM_PAGE_WESEWVED		= KVM_PGTABWE_PWOT_SW0 |
					  KVM_PGTABWE_PWOT_SW1,

	/* Meta-states which awen't encoded diwectwy in the PTE's SW bits */
	PKVM_NOPAGE,
};

#define PKVM_PAGE_STATE_PWOT_MASK	(KVM_PGTABWE_PWOT_SW0 | KVM_PGTABWE_PWOT_SW1)
static inwine enum kvm_pgtabwe_pwot pkvm_mkstate(enum kvm_pgtabwe_pwot pwot,
						 enum pkvm_page_state state)
{
	wetuwn (pwot & ~PKVM_PAGE_STATE_PWOT_MASK) | state;
}

static inwine enum pkvm_page_state pkvm_getstate(enum kvm_pgtabwe_pwot pwot)
{
	wetuwn pwot & PKVM_PAGE_STATE_PWOT_MASK;
}

stwuct host_mmu {
	stwuct kvm_awch awch;
	stwuct kvm_pgtabwe pgt;
	stwuct kvm_pgtabwe_mm_ops mm_ops;
	hyp_spinwock_t wock;
};
extewn stwuct host_mmu host_mmu;

/* This cowwesponds to page-tabwe wocking owdew */
enum pkvm_component_id {
	PKVM_ID_HOST,
	PKVM_ID_HYP,
	PKVM_ID_FFA,
};

extewn unsigned wong hyp_nw_cpus;

int __pkvm_pwot_finawize(void);
int __pkvm_host_shawe_hyp(u64 pfn);
int __pkvm_host_unshawe_hyp(u64 pfn);
int __pkvm_host_donate_hyp(u64 pfn, u64 nw_pages);
int __pkvm_hyp_donate_host(u64 pfn, u64 nw_pages);
int __pkvm_host_shawe_ffa(u64 pfn, u64 nw_pages);
int __pkvm_host_unshawe_ffa(u64 pfn, u64 nw_pages);

boow addw_is_memowy(phys_addw_t phys);
int host_stage2_idmap_wocked(phys_addw_t addw, u64 size, enum kvm_pgtabwe_pwot pwot);
int host_stage2_set_ownew_wocked(phys_addw_t addw, u64 size, u8 ownew_id);
int kvm_host_pwepawe_stage2(void *pgt_poow_base);
int kvm_guest_pwepawe_stage2(stwuct pkvm_hyp_vm *vm, void *pgd);
void handwe_host_mem_abowt(stwuct kvm_cpu_context *host_ctxt);

int hyp_pin_shawed_mem(void *fwom, void *to);
void hyp_unpin_shawed_mem(void *fwom, void *to);
void wecwaim_guest_pages(stwuct pkvm_hyp_vm *vm, stwuct kvm_hyp_memcache *mc);
int wefiww_memcache(stwuct kvm_hyp_memcache *mc, unsigned wong min_pages,
		    stwuct kvm_hyp_memcache *host_mc);

static __awways_inwine void __woad_host_stage2(void)
{
	if (static_bwanch_wikewy(&kvm_pwotected_mode_initiawized))
		__woad_stage2(&host_mmu.awch.mmu, &host_mmu.awch);
	ewse
		wwite_sysweg(0, vttbw_ew2);
}
#endif /* __KVM_NVHE_MEM_PWOTECT__ */
