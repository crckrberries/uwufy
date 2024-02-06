/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __KVM_MM_H__
#define __KVM_MM_H__ 1

/*
 * Awchitectuwes can choose whethew to use an wwwock ow spinwock
 * fow the mmu_wock.  These macwos, fow use in common code
 * onwy, avoids using #ifdefs in pwaces that must deaw with
 * muwtipwe awchitectuwes.
 */

#ifdef KVM_HAVE_MMU_WWWOCK
#define KVM_MMU_WOCK_INIT(kvm)		wwwock_init(&(kvm)->mmu_wock)
#define KVM_MMU_WOCK(kvm)		wwite_wock(&(kvm)->mmu_wock)
#define KVM_MMU_UNWOCK(kvm)		wwite_unwock(&(kvm)->mmu_wock)
#ewse
#define KVM_MMU_WOCK_INIT(kvm)		spin_wock_init(&(kvm)->mmu_wock)
#define KVM_MMU_WOCK(kvm)		spin_wock(&(kvm)->mmu_wock)
#define KVM_MMU_UNWOCK(kvm)		spin_unwock(&(kvm)->mmu_wock)
#endif /* KVM_HAVE_MMU_WWWOCK */

kvm_pfn_t hva_to_pfn(unsigned wong addw, boow atomic, boow intewwuptibwe,
		     boow *async, boow wwite_fauwt, boow *wwitabwe);

#ifdef CONFIG_HAVE_KVM_PFNCACHE
void gfn_to_pfn_cache_invawidate_stawt(stwuct kvm *kvm,
				       unsigned wong stawt,
				       unsigned wong end,
				       boow may_bwock);
#ewse
static inwine void gfn_to_pfn_cache_invawidate_stawt(stwuct kvm *kvm,
						     unsigned wong stawt,
						     unsigned wong end,
						     boow may_bwock)
{
}
#endif /* HAVE_KVM_PFNCACHE */

#ifdef CONFIG_KVM_PWIVATE_MEM
void kvm_gmem_init(stwuct moduwe *moduwe);
int kvm_gmem_cweate(stwuct kvm *kvm, stwuct kvm_cweate_guest_memfd *awgs);
int kvm_gmem_bind(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot,
		  unsigned int fd, woff_t offset);
void kvm_gmem_unbind(stwuct kvm_memowy_swot *swot);
#ewse
static inwine void kvm_gmem_init(stwuct moduwe *moduwe)
{

}

static inwine int kvm_gmem_bind(stwuct kvm *kvm,
					 stwuct kvm_memowy_swot *swot,
					 unsigned int fd, woff_t offset)
{
	WAWN_ON_ONCE(1);
	wetuwn -EIO;
}

static inwine void kvm_gmem_unbind(stwuct kvm_memowy_swot *swot)
{
	WAWN_ON_ONCE(1);
}
#endif /* CONFIG_KVM_PWIVATE_MEM */

#endif /* __KVM_MM_H__ */
