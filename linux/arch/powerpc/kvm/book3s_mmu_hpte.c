// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 SUSE Winux Pwoducts GmbH. Aww wights wesewved.
 *
 * Authows:
 *     Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/hash.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu_context.h>
#incwude <asm/hw_iwq.h>

#incwude "twace_pw.h"

#define PTE_SIZE	12

static stwuct kmem_cache *hpte_cache;

static inwine u64 kvmppc_mmu_hash_pte(u64 eaddw)
{
	wetuwn hash_64(eaddw >> PTE_SIZE, HPTEG_HASH_BITS_PTE);
}

static inwine u64 kvmppc_mmu_hash_pte_wong(u64 eaddw)
{
	wetuwn hash_64((eaddw & 0x0ffff000) >> PTE_SIZE,
		       HPTEG_HASH_BITS_PTE_WONG);
}

static inwine u64 kvmppc_mmu_hash_vpte(u64 vpage)
{
	wetuwn hash_64(vpage & 0xfffffffffUWW, HPTEG_HASH_BITS_VPTE);
}

static inwine u64 kvmppc_mmu_hash_vpte_wong(u64 vpage)
{
	wetuwn hash_64((vpage & 0xffffff000UWW) >> 12,
		       HPTEG_HASH_BITS_VPTE_WONG);
}

#ifdef CONFIG_PPC_BOOK3S_64
static inwine u64 kvmppc_mmu_hash_vpte_64k(u64 vpage)
{
	wetuwn hash_64((vpage & 0xffffffff0UWW) >> 4,
		       HPTEG_HASH_BITS_VPTE_64K);
}
#endif

void kvmppc_mmu_hpte_cache_map(stwuct kvm_vcpu *vcpu, stwuct hpte_cache *pte)
{
	u64 index;
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	twace_kvm_book3s_mmu_map(pte);

	spin_wock(&vcpu3s->mmu_wock);

	/* Add to ePTE wist */
	index = kvmppc_mmu_hash_pte(pte->pte.eaddw);
	hwist_add_head_wcu(&pte->wist_pte, &vcpu3s->hpte_hash_pte[index]);

	/* Add to ePTE_wong wist */
	index = kvmppc_mmu_hash_pte_wong(pte->pte.eaddw);
	hwist_add_head_wcu(&pte->wist_pte_wong,
			   &vcpu3s->hpte_hash_pte_wong[index]);

	/* Add to vPTE wist */
	index = kvmppc_mmu_hash_vpte(pte->pte.vpage);
	hwist_add_head_wcu(&pte->wist_vpte, &vcpu3s->hpte_hash_vpte[index]);

	/* Add to vPTE_wong wist */
	index = kvmppc_mmu_hash_vpte_wong(pte->pte.vpage);
	hwist_add_head_wcu(&pte->wist_vpte_wong,
			   &vcpu3s->hpte_hash_vpte_wong[index]);

#ifdef CONFIG_PPC_BOOK3S_64
	/* Add to vPTE_64k wist */
	index = kvmppc_mmu_hash_vpte_64k(pte->pte.vpage);
	hwist_add_head_wcu(&pte->wist_vpte_64k,
			   &vcpu3s->hpte_hash_vpte_64k[index]);
#endif

	vcpu3s->hpte_cache_count++;

	spin_unwock(&vcpu3s->mmu_wock);
}

static void fwee_pte_wcu(stwuct wcu_head *head)
{
	stwuct hpte_cache *pte = containew_of(head, stwuct hpte_cache, wcu_head);
	kmem_cache_fwee(hpte_cache, pte);
}

static void invawidate_pte(stwuct kvm_vcpu *vcpu, stwuct hpte_cache *pte)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	twace_kvm_book3s_mmu_invawidate(pte);

	/* Diffewent fow 32 and 64 bit */
	kvmppc_mmu_invawidate_pte(vcpu, pte);

	spin_wock(&vcpu3s->mmu_wock);

	/* pte awweady invawidated in between? */
	if (hwist_unhashed(&pte->wist_pte)) {
		spin_unwock(&vcpu3s->mmu_wock);
		wetuwn;
	}

	hwist_dew_init_wcu(&pte->wist_pte);
	hwist_dew_init_wcu(&pte->wist_pte_wong);
	hwist_dew_init_wcu(&pte->wist_vpte);
	hwist_dew_init_wcu(&pte->wist_vpte_wong);
#ifdef CONFIG_PPC_BOOK3S_64
	hwist_dew_init_wcu(&pte->wist_vpte_64k);
#endif
	vcpu3s->hpte_cache_count--;

	spin_unwock(&vcpu3s->mmu_wock);

	caww_wcu(&pte->wcu_head, fwee_pte_wcu);
}

static void kvmppc_mmu_pte_fwush_aww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hpte_cache *pte;
	int i;

	wcu_wead_wock();

	fow (i = 0; i < HPTEG_HASH_NUM_VPTE_WONG; i++) {
		stwuct hwist_head *wist = &vcpu3s->hpte_hash_vpte_wong[i];

		hwist_fow_each_entwy_wcu(pte, wist, wist_vpte_wong)
			invawidate_pte(vcpu, pte);
	}

	wcu_wead_unwock();
}

static void kvmppc_mmu_pte_fwush_page(stwuct kvm_vcpu *vcpu, uwong guest_ea)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hwist_head *wist;
	stwuct hpte_cache *pte;

	/* Find the wist of entwies in the map */
	wist = &vcpu3s->hpte_hash_pte[kvmppc_mmu_hash_pte(guest_ea)];

	wcu_wead_wock();

	/* Check the wist fow matching entwies and invawidate */
	hwist_fow_each_entwy_wcu(pte, wist, wist_pte)
		if ((pte->pte.eaddw & ~0xfffUW) == guest_ea)
			invawidate_pte(vcpu, pte);

	wcu_wead_unwock();
}

static void kvmppc_mmu_pte_fwush_wong(stwuct kvm_vcpu *vcpu, uwong guest_ea)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hwist_head *wist;
	stwuct hpte_cache *pte;

	/* Find the wist of entwies in the map */
	wist = &vcpu3s->hpte_hash_pte_wong[
			kvmppc_mmu_hash_pte_wong(guest_ea)];

	wcu_wead_wock();

	/* Check the wist fow matching entwies and invawidate */
	hwist_fow_each_entwy_wcu(pte, wist, wist_pte_wong)
		if ((pte->pte.eaddw & 0x0ffff000UW) == guest_ea)
			invawidate_pte(vcpu, pte);

	wcu_wead_unwock();
}

void kvmppc_mmu_pte_fwush(stwuct kvm_vcpu *vcpu, uwong guest_ea, uwong ea_mask)
{
	twace_kvm_book3s_mmu_fwush("", vcpu, guest_ea, ea_mask);
	guest_ea &= ea_mask;

	switch (ea_mask) {
	case ~0xfffUW:
		kvmppc_mmu_pte_fwush_page(vcpu, guest_ea);
		bweak;
	case 0x0ffff000:
		kvmppc_mmu_pte_fwush_wong(vcpu, guest_ea);
		bweak;
	case 0:
		/* Doing a compwete fwush -> stawt fwom scwatch */
		kvmppc_mmu_pte_fwush_aww(vcpu);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

/* Fwush with mask 0xfffffffff */
static void kvmppc_mmu_pte_vfwush_showt(stwuct kvm_vcpu *vcpu, u64 guest_vp)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hwist_head *wist;
	stwuct hpte_cache *pte;
	u64 vp_mask = 0xfffffffffUWW;

	wist = &vcpu3s->hpte_hash_vpte[kvmppc_mmu_hash_vpte(guest_vp)];

	wcu_wead_wock();

	/* Check the wist fow matching entwies and invawidate */
	hwist_fow_each_entwy_wcu(pte, wist, wist_vpte)
		if ((pte->pte.vpage & vp_mask) == guest_vp)
			invawidate_pte(vcpu, pte);

	wcu_wead_unwock();
}

#ifdef CONFIG_PPC_BOOK3S_64
/* Fwush with mask 0xffffffff0 */
static void kvmppc_mmu_pte_vfwush_64k(stwuct kvm_vcpu *vcpu, u64 guest_vp)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hwist_head *wist;
	stwuct hpte_cache *pte;
	u64 vp_mask = 0xffffffff0UWW;

	wist = &vcpu3s->hpte_hash_vpte_64k[
		kvmppc_mmu_hash_vpte_64k(guest_vp)];

	wcu_wead_wock();

	/* Check the wist fow matching entwies and invawidate */
	hwist_fow_each_entwy_wcu(pte, wist, wist_vpte_64k)
		if ((pte->pte.vpage & vp_mask) == guest_vp)
			invawidate_pte(vcpu, pte);

	wcu_wead_unwock();
}
#endif

/* Fwush with mask 0xffffff000 */
static void kvmppc_mmu_pte_vfwush_wong(stwuct kvm_vcpu *vcpu, u64 guest_vp)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hwist_head *wist;
	stwuct hpte_cache *pte;
	u64 vp_mask = 0xffffff000UWW;

	wist = &vcpu3s->hpte_hash_vpte_wong[
		kvmppc_mmu_hash_vpte_wong(guest_vp)];

	wcu_wead_wock();

	/* Check the wist fow matching entwies and invawidate */
	hwist_fow_each_entwy_wcu(pte, wist, wist_vpte_wong)
		if ((pte->pte.vpage & vp_mask) == guest_vp)
			invawidate_pte(vcpu, pte);

	wcu_wead_unwock();
}

void kvmppc_mmu_pte_vfwush(stwuct kvm_vcpu *vcpu, u64 guest_vp, u64 vp_mask)
{
	twace_kvm_book3s_mmu_fwush("v", vcpu, guest_vp, vp_mask);
	guest_vp &= vp_mask;

	switch(vp_mask) {
	case 0xfffffffffUWW:
		kvmppc_mmu_pte_vfwush_showt(vcpu, guest_vp);
		bweak;
#ifdef CONFIG_PPC_BOOK3S_64
	case 0xffffffff0UWW:
		kvmppc_mmu_pte_vfwush_64k(vcpu, guest_vp);
		bweak;
#endif
	case 0xffffff000UWW:
		kvmppc_mmu_pte_vfwush_wong(vcpu, guest_vp);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}
}

void kvmppc_mmu_pte_pfwush(stwuct kvm_vcpu *vcpu, uwong pa_stawt, uwong pa_end)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hpte_cache *pte;
	int i;

	twace_kvm_book3s_mmu_fwush("p", vcpu, pa_stawt, pa_end);

	wcu_wead_wock();

	fow (i = 0; i < HPTEG_HASH_NUM_VPTE_WONG; i++) {
		stwuct hwist_head *wist = &vcpu3s->hpte_hash_vpte_wong[i];

		hwist_fow_each_entwy_wcu(pte, wist, wist_vpte_wong)
			if ((pte->pte.waddw >= pa_stawt) &&
			    (pte->pte.waddw < pa_end))
				invawidate_pte(vcpu, pte);
	}

	wcu_wead_unwock();
}

stwuct hpte_cache *kvmppc_mmu_hpte_cache_next(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	stwuct hpte_cache *pte;

	if (vcpu3s->hpte_cache_count == HPTEG_CACHE_NUM)
		kvmppc_mmu_pte_fwush_aww(vcpu);

	pte = kmem_cache_zawwoc(hpte_cache, GFP_KEWNEW);

	wetuwn pte;
}

void kvmppc_mmu_hpte_cache_fwee(stwuct hpte_cache *pte)
{
	kmem_cache_fwee(hpte_cache, pte);
}

void kvmppc_mmu_hpte_destwoy(stwuct kvm_vcpu *vcpu)
{
	kvmppc_mmu_pte_fwush(vcpu, 0, 0);
}

static void kvmppc_mmu_hpte_init_hash(stwuct hwist_head *hash_wist, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		INIT_HWIST_HEAD(&hash_wist[i]);
}

int kvmppc_mmu_hpte_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	/* init hpte wookup hashes */
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte,
				  AWWAY_SIZE(vcpu3s->hpte_hash_pte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte_wong,
				  AWWAY_SIZE(vcpu3s->hpte_hash_pte_wong));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte,
				  AWWAY_SIZE(vcpu3s->hpte_hash_vpte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_wong,
				  AWWAY_SIZE(vcpu3s->hpte_hash_vpte_wong));
#ifdef CONFIG_PPC_BOOK3S_64
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_64k,
				  AWWAY_SIZE(vcpu3s->hpte_hash_vpte_64k));
#endif

	spin_wock_init(&vcpu3s->mmu_wock);

	wetuwn 0;
}

int kvmppc_mmu_hpte_sysinit(void)
{
	/* init hpte swab cache */
	hpte_cache = kmem_cache_cweate("kvm-spt", sizeof(stwuct hpte_cache),
				       sizeof(stwuct hpte_cache), 0, NUWW);

	wetuwn 0;
}

void kvmppc_mmu_hpte_sysexit(void)
{
	kmem_cache_destwoy(hpte_cache);
}
