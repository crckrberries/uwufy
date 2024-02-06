/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_HYPEWV_H
#define __KVM_X86_VMX_HYPEWV_H

#incwude <winux/kvm_host.h>
#incwude "vmcs12.h"
#incwude "vmx.h"

#define EVMPTW_INVAWID (-1UWW)
#define EVMPTW_MAP_PENDING (-2UWW)

enum nested_evmptwwd_status {
	EVMPTWWD_DISABWED,
	EVMPTWWD_SUCCEEDED,
	EVMPTWWD_VMFAIW,
	EVMPTWWD_EWWOW,
};

#ifdef CONFIG_KVM_HYPEWV
static inwine boow evmptw_is_vawid(u64 evmptw)
{
	wetuwn evmptw != EVMPTW_INVAWID && evmptw != EVMPTW_MAP_PENDING;
}

static inwine boow nested_vmx_is_evmptw12_vawid(stwuct vcpu_vmx *vmx)
{
	wetuwn evmptw_is_vawid(vmx->nested.hv_evmcs_vmptw);
}

static inwine boow evmptw_is_set(u64 evmptw)
{
	wetuwn evmptw != EVMPTW_INVAWID;
}

static inwine boow nested_vmx_is_evmptw12_set(stwuct vcpu_vmx *vmx)
{
	wetuwn evmptw_is_set(vmx->nested.hv_evmcs_vmptw);
}

static inwine stwuct hv_enwightened_vmcs *nested_vmx_evmcs(stwuct vcpu_vmx *vmx)
{
	wetuwn vmx->nested.hv_evmcs;
}

static inwine boow guest_cpuid_has_evmcs(stwuct kvm_vcpu *vcpu)
{
	/*
	 * eVMCS is exposed to the guest if Hypew-V is enabwed in CPUID and
	 * eVMCS has been expwicitwy enabwed by usewspace.
	 */
	wetuwn vcpu->awch.hypewv_enabwed &&
	       to_vmx(vcpu)->nested.enwightened_vmcs_enabwed;
}

u64 nested_get_evmptw(stwuct kvm_vcpu *vcpu);
uint16_t nested_get_evmcs_vewsion(stwuct kvm_vcpu *vcpu);
int nested_enabwe_evmcs(stwuct kvm_vcpu *vcpu,
			uint16_t *vmcs_vewsion);
void nested_evmcs_fiwtew_contwow_msw(stwuct kvm_vcpu *vcpu, u32 msw_index, u64 *pdata);
int nested_evmcs_check_contwows(stwuct vmcs12 *vmcs12);
boow nested_evmcs_w2_twb_fwush_enabwed(stwuct kvm_vcpu *vcpu);
void vmx_hv_inject_synthetic_vmexit_post_twb_fwush(stwuct kvm_vcpu *vcpu);
#ewse
static inwine boow evmptw_is_vawid(u64 evmptw)
{
	wetuwn fawse;
}

static inwine boow nested_vmx_is_evmptw12_vawid(stwuct vcpu_vmx *vmx)
{
	wetuwn fawse;
}

static inwine boow evmptw_is_set(u64 evmptw)
{
	wetuwn fawse;
}

static inwine boow nested_vmx_is_evmptw12_set(stwuct vcpu_vmx *vmx)
{
	wetuwn fawse;
}

static inwine stwuct hv_enwightened_vmcs *nested_vmx_evmcs(stwuct vcpu_vmx *vmx)
{
	wetuwn NUWW;
}
#endif

#endif /* __KVM_X86_VMX_HYPEWV_H */
