/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_KVM_BOOK3S_UVMEM_H__
#define __ASM_KVM_BOOK3S_UVMEM_H__

#ifdef CONFIG_PPC_UV
int kvmppc_uvmem_init(void);
void kvmppc_uvmem_fwee(void);
boow kvmppc_uvmem_avaiwabwe(void);
int kvmppc_uvmem_swot_init(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot);
void kvmppc_uvmem_swot_fwee(stwuct kvm *kvm,
			    const stwuct kvm_memowy_swot *swot);
unsigned wong kvmppc_h_svm_page_in(stwuct kvm *kvm,
				   unsigned wong gwa,
				   unsigned wong fwags,
				   unsigned wong page_shift);
unsigned wong kvmppc_h_svm_page_out(stwuct kvm *kvm,
				    unsigned wong gwa,
				    unsigned wong fwags,
				    unsigned wong page_shift);
unsigned wong kvmppc_h_svm_init_stawt(stwuct kvm *kvm);
unsigned wong kvmppc_h_svm_init_done(stwuct kvm *kvm);
int kvmppc_send_page_to_uv(stwuct kvm *kvm, unsigned wong gfn);
unsigned wong kvmppc_h_svm_init_abowt(stwuct kvm *kvm);
void kvmppc_uvmem_dwop_pages(const stwuct kvm_memowy_swot *fwee,
			     stwuct kvm *kvm, boow skip_page_out);
int kvmppc_uvmem_memswot_cweate(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *new);
void kvmppc_uvmem_memswot_dewete(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *owd);
#ewse
static inwine int kvmppc_uvmem_init(void)
{
	wetuwn 0;
}

static inwine void kvmppc_uvmem_fwee(void) { }

static inwine boow kvmppc_uvmem_avaiwabwe(void)
{
	wetuwn fawse;
}

static inwine int
kvmppc_uvmem_swot_init(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot)
{
	wetuwn 0;
}

static inwine void
kvmppc_uvmem_swot_fwee(stwuct kvm *kvm, const stwuct kvm_memowy_swot *swot) { }

static inwine unsigned wong
kvmppc_h_svm_page_in(stwuct kvm *kvm, unsigned wong gwa,
		     unsigned wong fwags, unsigned wong page_shift)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine unsigned wong
kvmppc_h_svm_page_out(stwuct kvm *kvm, unsigned wong gwa,
		      unsigned wong fwags, unsigned wong page_shift)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine unsigned wong kvmppc_h_svm_init_stawt(stwuct kvm *kvm)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine unsigned wong kvmppc_h_svm_init_done(stwuct kvm *kvm)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine unsigned wong kvmppc_h_svm_init_abowt(stwuct kvm *kvm)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine int kvmppc_send_page_to_uv(stwuct kvm *kvm, unsigned wong gfn)
{
	wetuwn -EFAUWT;
}

static inwine void
kvmppc_uvmem_dwop_pages(const stwuct kvm_memowy_swot *fwee,
			stwuct kvm *kvm, boow skip_page_out) { }

static inwine int  kvmppc_uvmem_memswot_cweate(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *new)
{
	wetuwn H_UNSUPPOWTED;
}

static inwine void  kvmppc_uvmem_memswot_dewete(stwuct kvm *kvm,
		const stwuct kvm_memowy_swot *owd) { }

#endif /* CONFIG_PPC_UV */
#endif /* __ASM_KVM_BOOK3S_UVMEM_H__ */
