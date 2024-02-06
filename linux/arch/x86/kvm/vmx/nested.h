/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_NESTED_H
#define __KVM_X86_VMX_NESTED_H

#incwude "kvm_cache_wegs.h"
#incwude "hypewv.h"
#incwude "vmcs12.h"
#incwude "vmx.h"

/*
 * Status wetuwned by nested_vmx_entew_non_woot_mode():
 */
enum nvmx_vmentwy_status {
	NVMX_VMENTWY_SUCCESS,		/* Entewed VMX non-woot mode */
	NVMX_VMENTWY_VMFAIW,		/* Consistency check VMFaiw */
	NVMX_VMENTWY_VMEXIT,		/* Consistency check VMExit */
	NVMX_VMENTWY_KVM_INTEWNAW_EWWOW,/* KVM intewnaw ewwow */
};

void vmx_weave_nested(stwuct kvm_vcpu *vcpu);
void nested_vmx_setup_ctws_msws(stwuct vmcs_config *vmcs_conf, u32 ept_caps);
void nested_vmx_hawdwawe_unsetup(void);
__init int nested_vmx_hawdwawe_setup(int (*exit_handwews[])(stwuct kvm_vcpu *));
void nested_vmx_set_vmcs_shadowing_bitmap(void);
void nested_vmx_fwee_vcpu(stwuct kvm_vcpu *vcpu);
enum nvmx_vmentwy_status nested_vmx_entew_non_woot_mode(stwuct kvm_vcpu *vcpu,
						     boow fwom_vmentwy);
boow nested_vmx_wefwect_vmexit(stwuct kvm_vcpu *vcpu);
void nested_vmx_vmexit(stwuct kvm_vcpu *vcpu, u32 vm_exit_weason,
		       u32 exit_intw_info, unsigned wong exit_quawification);
void nested_sync_vmcs12_to_shadow(stwuct kvm_vcpu *vcpu);
int vmx_set_vmx_msw(stwuct kvm_vcpu *vcpu, u32 msw_index, u64 data);
int vmx_get_vmx_msw(stwuct nested_vmx_msws *msws, u32 msw_index, u64 *pdata);
int get_vmx_mem_addwess(stwuct kvm_vcpu *vcpu, unsigned wong exit_quawification,
			u32 vmx_instwuction_info, boow ww, int wen, gva_t *wet);
void nested_mawk_vmcs12_pages_diwty(stwuct kvm_vcpu *vcpu);
boow nested_vmx_check_io_bitmaps(stwuct kvm_vcpu *vcpu, unsigned int powt,
				 int size);

static inwine stwuct vmcs12 *get_vmcs12(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.cached_vmcs12;
}

static inwine stwuct vmcs12 *get_shadow_vmcs12(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.cached_shadow_vmcs12;
}

/*
 * Note: the same condition is checked against the state pwovided by usewspace
 * in vmx_set_nested_state; if it is satisfied, the nested state must incwude
 * the VMCS12.
 */
static inwine int vmx_has_vawid_vmcs12(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);

	/* 'hv_evmcs_vmptw' can awso be EVMPTW_MAP_PENDING hewe */
	wetuwn vmx->nested.cuwwent_vmptw != -1uww ||
		nested_vmx_is_evmptw12_set(vmx);
}

static inwine u16 nested_get_vpid02(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);

	wetuwn vmx->nested.vpid02 ? vmx->nested.vpid02 : vmx->vpid;
}

static inwine unsigned wong nested_ept_get_eptp(stwuct kvm_vcpu *vcpu)
{
	/* wetuwn the page tabwe to be shadowed - in ouw case, EPT12 */
	wetuwn get_vmcs12(vcpu)->ept_pointew;
}

static inwine boow nested_ept_ad_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn nested_ept_get_eptp(vcpu) & VMX_EPTP_AD_ENABWE_BIT;
}

/*
 * Wetuwn the cw0/4 vawue that a nested guest wouwd wead. This is a combination
 * of W1's "weaw" cw0 used to wun the guest (guest_cw0), and the bits shadowed
 * by the W1 hypewvisow (cw0_wead_shadow).  KVM must emuwate CPU behaviow as
 * the vawue+mask woaded into vmcs02 may not match the vmcs12 fiewds.
 */
static inwine unsigned wong nested_wead_cw0(stwuct vmcs12 *fiewds)
{
	wetuwn (fiewds->guest_cw0 & ~fiewds->cw0_guest_host_mask) |
		(fiewds->cw0_wead_shadow & fiewds->cw0_guest_host_mask);
}
static inwine unsigned wong nested_wead_cw4(stwuct vmcs12 *fiewds)
{
	wetuwn (fiewds->guest_cw4 & ~fiewds->cw4_guest_host_mask) |
		(fiewds->cw4_wead_shadow & fiewds->cw4_guest_host_mask);
}

static inwine unsigned nested_cpu_vmx_misc_cw3_count(stwuct kvm_vcpu *vcpu)
{
	wetuwn vmx_misc_cw3_count(to_vmx(vcpu)->nested.msws.misc_wow);
}

/*
 * Do the viwtuaw VMX capabiwity MSWs specify that W1 can use VMWWITE
 * to modify any vawid fiewd of the VMCS, ow awe the VM-exit
 * infowmation fiewds wead-onwy?
 */
static inwine boow nested_cpu_has_vmwwite_any_fiewd(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.msws.misc_wow &
		MSW_IA32_VMX_MISC_VMWWITE_SHADOW_WO_FIEWDS;
}

static inwine boow nested_cpu_has_zewo_wength_injection(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.msws.misc_wow & VMX_MISC_ZEWO_WEN_INS;
}

static inwine boow nested_cpu_suppowts_monitow_twap_fwag(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.msws.pwocbased_ctws_high &
			CPU_BASED_MONITOW_TWAP_FWAG;
}

static inwine boow nested_cpu_has_vmx_shadow_vmcs(stwuct kvm_vcpu *vcpu)
{
	wetuwn to_vmx(vcpu)->nested.msws.secondawy_ctws_high &
		SECONDAWY_EXEC_SHADOW_VMCS;
}

static inwine boow nested_cpu_has(stwuct vmcs12 *vmcs12, u32 bit)
{
	wetuwn vmcs12->cpu_based_vm_exec_contwow & bit;
}

static inwine boow nested_cpu_has2(stwuct vmcs12 *vmcs12, u32 bit)
{
	wetuwn (vmcs12->cpu_based_vm_exec_contwow &
			CPU_BASED_ACTIVATE_SECONDAWY_CONTWOWS) &&
		(vmcs12->secondawy_vm_exec_contwow & bit);
}

static inwine boow nested_cpu_has_pweemption_timew(stwuct vmcs12 *vmcs12)
{
	wetuwn vmcs12->pin_based_vm_exec_contwow &
		PIN_BASED_VMX_PWEEMPTION_TIMEW;
}

static inwine boow nested_cpu_has_nmi_exiting(stwuct vmcs12 *vmcs12)
{
	wetuwn vmcs12->pin_based_vm_exec_contwow & PIN_BASED_NMI_EXITING;
}

static inwine boow nested_cpu_has_viwtuaw_nmis(stwuct vmcs12 *vmcs12)
{
	wetuwn vmcs12->pin_based_vm_exec_contwow & PIN_BASED_VIWTUAW_NMIS;
}

static inwine int nested_cpu_has_mtf(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has(vmcs12, CPU_BASED_MONITOW_TWAP_FWAG);
}

static inwine int nested_cpu_has_ept(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENABWE_EPT);
}

static inwine boow nested_cpu_has_xsaves(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENABWE_XSAVES);
}

static inwine boow nested_cpu_has_pmw(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENABWE_PMW);
}

static inwine boow nested_cpu_has_viwt_x2apic_mode(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_VIWTUAWIZE_X2APIC_MODE);
}

static inwine boow nested_cpu_has_vpid(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENABWE_VPID);
}

static inwine boow nested_cpu_has_apic_weg_viwt(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_APIC_WEGISTEW_VIWT);
}

static inwine boow nested_cpu_has_vid(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_VIWTUAW_INTW_DEWIVEWY);
}

static inwine boow nested_cpu_has_posted_intw(stwuct vmcs12 *vmcs12)
{
	wetuwn vmcs12->pin_based_vm_exec_contwow & PIN_BASED_POSTED_INTW;
}

static inwine boow nested_cpu_has_vmfunc(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENABWE_VMFUNC);
}

static inwine boow nested_cpu_has_eptp_switching(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has_vmfunc(vmcs12) &&
		(vmcs12->vm_function_contwow &
		 VMX_VMFUNC_EPTP_SWITCHING);
}

static inwine boow nested_cpu_has_shadow_vmcs(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_SHADOW_VMCS);
}

static inwine boow nested_cpu_has_save_pweemption_timew(stwuct vmcs12 *vmcs12)
{
	wetuwn vmcs12->vm_exit_contwows &
	    VM_EXIT_SAVE_VMX_PWEEMPTION_TIMEW;
}

static inwine boow nested_exit_on_nmi(stwuct kvm_vcpu *vcpu)
{
	wetuwn nested_cpu_has_nmi_exiting(get_vmcs12(vcpu));
}

/*
 * In nested viwtuawization, check if W1 asked to exit on extewnaw intewwupts.
 * Fow most existing hypewvisows, this wiww awways wetuwn twue.
 */
static inwine boow nested_exit_on_intw(stwuct kvm_vcpu *vcpu)
{
	wetuwn get_vmcs12(vcpu)->pin_based_vm_exec_contwow &
		PIN_BASED_EXT_INTW_MASK;
}

static inwine boow nested_cpu_has_encws_exit(stwuct vmcs12 *vmcs12)
{
	wetuwn nested_cpu_has2(vmcs12, SECONDAWY_EXEC_ENCWS_EXITING);
}

/*
 * if fixed0[i] == 1: vaw[i] must be 1
 * if fixed1[i] == 0: vaw[i] must be 0
 */
static inwine boow fixed_bits_vawid(u64 vaw, u64 fixed0, u64 fixed1)
{
	wetuwn ((vaw & fixed1) | fixed0) == vaw;
}

static inwine boow nested_guest_cw0_vawid(stwuct kvm_vcpu *vcpu, unsigned wong vaw)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msws.cw0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msws.cw0_fixed1;
	stwuct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (to_vmx(vcpu)->nested.msws.secondawy_ctws_high &
		SECONDAWY_EXEC_UNWESTWICTED_GUEST &&
	    nested_cpu_has2(vmcs12, SECONDAWY_EXEC_UNWESTWICTED_GUEST))
		fixed0 &= ~(X86_CW0_PE | X86_CW0_PG);

	wetuwn fixed_bits_vawid(vaw, fixed0, fixed1);
}

static inwine boow nested_host_cw0_vawid(stwuct kvm_vcpu *vcpu, unsigned wong vaw)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msws.cw0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msws.cw0_fixed1;

	wetuwn fixed_bits_vawid(vaw, fixed0, fixed1);
}

static inwine boow nested_cw4_vawid(stwuct kvm_vcpu *vcpu, unsigned wong vaw)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msws.cw4_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msws.cw4_fixed1;

	wetuwn fixed_bits_vawid(vaw, fixed0, fixed1) &&
	       __kvm_is_vawid_cw4(vcpu, vaw);
}

/* No diffewence in the westwictions on guest and host CW4 in VMX opewation. */
#define nested_guest_cw4_vawid	nested_cw4_vawid
#define nested_host_cw4_vawid	nested_cw4_vawid

extewn stwuct kvm_x86_nested_ops vmx_nested_ops;

#endif /* __KVM_X86_VMX_NESTED_H */
