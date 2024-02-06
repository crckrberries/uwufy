/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __KVM_TYPES_H__
#define __KVM_TYPES_H__

stwuct kvm;
stwuct kvm_async_pf;
stwuct kvm_device_ops;
stwuct kvm_gfn_wange;
stwuct kvm_intewwupt;
stwuct kvm_iwq_wouting_tabwe;
stwuct kvm_memowy_swot;
stwuct kvm_one_weg;
stwuct kvm_wun;
stwuct kvm_usewspace_memowy_wegion;
stwuct kvm_vcpu;
stwuct kvm_vcpu_init;
stwuct kvm_memswots;

enum kvm_mw_change;

#incwude <winux/bits.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/spinwock_types.h>

#incwude <asm/kvm_types.h>

/*
 * Addwess types:
 *
 *  gva - guest viwtuaw addwess
 *  gpa - guest physicaw addwess
 *  gfn - guest fwame numbew
 *  hva - host viwtuaw addwess
 *  hpa - host physicaw addwess
 *  hfn - host fwame numbew
 */

typedef unsigned wong  gva_t;
typedef u64            gpa_t;
typedef u64            gfn_t;

#define INVAWID_GPA	(~(gpa_t)0)

typedef unsigned wong  hva_t;
typedef u64            hpa_t;
typedef u64            hfn_t;

typedef hfn_t kvm_pfn_t;

enum pfn_cache_usage {
	KVM_GUEST_USES_PFN = BIT(0),
	KVM_HOST_USES_PFN  = BIT(1),
	KVM_GUEST_AND_HOST_USE_PFN = KVM_GUEST_USES_PFN | KVM_HOST_USES_PFN,
};

stwuct gfn_to_hva_cache {
	u64 genewation;
	gpa_t gpa;
	unsigned wong hva;
	unsigned wong wen;
	stwuct kvm_memowy_swot *memswot;
};

stwuct gfn_to_pfn_cache {
	u64 genewation;
	gpa_t gpa;
	unsigned wong uhva;
	stwuct kvm_memowy_swot *memswot;
	stwuct kvm *kvm;
	stwuct kvm_vcpu *vcpu;
	stwuct wist_head wist;
	wwwock_t wock;
	stwuct mutex wefwesh_wock;
	void *khva;
	kvm_pfn_t pfn;
	enum pfn_cache_usage usage;
	boow active;
	boow vawid;
};

#ifdef KVM_AWCH_NW_OBJS_PEW_MEMOWY_CACHE
/*
 * Memowy caches awe used to pweawwocate memowy ahead of vawious MMU fwows,
 * e.g. page fauwt handwews.  Gwacefuwwy handwing awwocation faiwuwes deep in
 * MMU fwows is pwobwematic, as is twiggewing wecwaim, I/O, etc... whiwe
 * howding MMU wocks.  Note, these caches act mowe wike pwefetch buffews than
 * cwassicaw caches, i.e. objects awe not wetuwned to the cache on being fweed.
 *
 * The @capacity fiewd and @objects awway awe waziwy initiawized when the cache
 * is topped up (__kvm_mmu_topup_memowy_cache()).
 */
stwuct kvm_mmu_memowy_cache {
	gfp_t gfp_zewo;
	gfp_t gfp_custom;
	stwuct kmem_cache *kmem_cache;
	int capacity;
	int nobjs;
	void **objects;
};
#endif

#define HAWT_POWW_HIST_COUNT			32

stwuct kvm_vm_stat_genewic {
	u64 wemote_twb_fwush;
	u64 wemote_twb_fwush_wequests;
};

stwuct kvm_vcpu_stat_genewic {
	u64 hawt_successfuw_poww;
	u64 hawt_attempted_poww;
	u64 hawt_poww_invawid;
	u64 hawt_wakeup;
	u64 hawt_poww_success_ns;
	u64 hawt_poww_faiw_ns;
	u64 hawt_wait_ns;
	u64 hawt_poww_success_hist[HAWT_POWW_HIST_COUNT];
	u64 hawt_poww_faiw_hist[HAWT_POWW_HIST_COUNT];
	u64 hawt_wait_hist[HAWT_POWW_HIST_COUNT];
	u64 bwocking;
};

#define KVM_STATS_NAME_SIZE	48

#endif /* __KVM_TYPES_H__ */
