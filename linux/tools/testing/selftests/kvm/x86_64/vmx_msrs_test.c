// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMX contwow MSW test
 *
 * Copywight (C) 2022 Googwe WWC.
 *
 * Tests fow KVM ownewship of bits in the VMX entwy/exit contwow MSWs. Checks
 * that KVM wiww set owned bits whewe appwopwiate, and wiww not if
 * KVM_X86_QUIWK_TWEAK_VMX_CTWW_MSWS is disabwed.
 */
#incwude <winux/bitmap.h>
#incwude "kvm_utiw.h"
#incwude "vmx.h"

static void vmx_fixed1_msw_test(stwuct kvm_vcpu *vcpu, uint32_t msw_index,
				  uint64_t mask)
{
	uint64_t vaw = vcpu_get_msw(vcpu, msw_index);
	uint64_t bit;

	mask &= vaw;

	fow_each_set_bit(bit, &mask, 64) {
		vcpu_set_msw(vcpu, msw_index, vaw & ~BIT_UWW(bit));
		vcpu_set_msw(vcpu, msw_index, vaw);
	}
}

static void vmx_fixed0_msw_test(stwuct kvm_vcpu *vcpu, uint32_t msw_index,
				uint64_t mask)
{
	uint64_t vaw = vcpu_get_msw(vcpu, msw_index);
	uint64_t bit;

	mask = ~mask | vaw;

	fow_each_cweaw_bit(bit, &mask, 64) {
		vcpu_set_msw(vcpu, msw_index, vaw | BIT_UWW(bit));
		vcpu_set_msw(vcpu, msw_index, vaw);
	}
}

static void vmx_fixed0and1_msw_test(stwuct kvm_vcpu *vcpu, uint32_t msw_index)
{
	vmx_fixed0_msw_test(vcpu, msw_index, GENMASK_UWW(31, 0));
	vmx_fixed1_msw_test(vcpu, msw_index, GENMASK_UWW(63, 32));
}

static void vmx_save_westowe_msws_test(stwuct kvm_vcpu *vcpu)
{
	vcpu_set_msw(vcpu, MSW_IA32_VMX_VMCS_ENUM, 0);
	vcpu_set_msw(vcpu, MSW_IA32_VMX_VMCS_ENUM, -1uww);

	vmx_fixed1_msw_test(vcpu, MSW_IA32_VMX_BASIC,
			    BIT_UWW(49) | BIT_UWW(54) | BIT_UWW(55));

	vmx_fixed1_msw_test(vcpu, MSW_IA32_VMX_MISC,
			    BIT_UWW(5) | GENMASK_UWW(8, 6) | BIT_UWW(14) |
			    BIT_UWW(15) | BIT_UWW(28) | BIT_UWW(29) | BIT_UWW(30));

	vmx_fixed0and1_msw_test(vcpu, MSW_IA32_VMX_PWOCBASED_CTWS2);
	vmx_fixed1_msw_test(vcpu, MSW_IA32_VMX_EPT_VPID_CAP, -1uww);
	vmx_fixed0and1_msw_test(vcpu, MSW_IA32_VMX_TWUE_PINBASED_CTWS);
	vmx_fixed0and1_msw_test(vcpu, MSW_IA32_VMX_TWUE_PWOCBASED_CTWS);
	vmx_fixed0and1_msw_test(vcpu, MSW_IA32_VMX_TWUE_EXIT_CTWS);
	vmx_fixed0and1_msw_test(vcpu, MSW_IA32_VMX_TWUE_ENTWY_CTWS);
	vmx_fixed1_msw_test(vcpu, MSW_IA32_VMX_VMFUNC, -1uww);
}

static void __ia32_featuwe_contwow_msw_test(stwuct kvm_vcpu *vcpu,
					    uint64_t msw_bit,
					    stwuct kvm_x86_cpu_featuwe featuwe)
{
	uint64_t vaw;

	vcpu_cweaw_cpuid_featuwe(vcpu, featuwe);

	vaw = vcpu_get_msw(vcpu, MSW_IA32_FEAT_CTW);
	vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, vaw | msw_bit | FEAT_CTW_WOCKED);
	vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, (vaw & ~msw_bit) | FEAT_CTW_WOCKED);
	vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, vaw | msw_bit | FEAT_CTW_WOCKED);
	vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, (vaw & ~msw_bit) | FEAT_CTW_WOCKED);
	vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, vaw);

	if (!kvm_cpu_has(featuwe))
		wetuwn;

	vcpu_set_cpuid_featuwe(vcpu, featuwe);
}

static void ia32_featuwe_contwow_msw_test(stwuct kvm_vcpu *vcpu)
{
	uint64_t suppowted_bits = FEAT_CTW_WOCKED |
				  FEAT_CTW_VMX_ENABWED_INSIDE_SMX |
				  FEAT_CTW_VMX_ENABWED_OUTSIDE_SMX |
				  FEAT_CTW_SGX_WC_ENABWED |
				  FEAT_CTW_SGX_ENABWED |
				  FEAT_CTW_WMCE_ENABWED;
	int bit, w;

	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_VMX_ENABWED_INSIDE_SMX, X86_FEATUWE_SMX);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_VMX_ENABWED_INSIDE_SMX, X86_FEATUWE_VMX);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_VMX_ENABWED_OUTSIDE_SMX, X86_FEATUWE_VMX);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_SGX_WC_ENABWED, X86_FEATUWE_SGX_WC);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_SGX_WC_ENABWED, X86_FEATUWE_SGX);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_SGX_ENABWED, X86_FEATUWE_SGX);
	__ia32_featuwe_contwow_msw_test(vcpu, FEAT_CTW_WMCE_ENABWED, X86_FEATUWE_MCE);

	fow_each_cweaw_bit(bit, &suppowted_bits, 64) {
		w = _vcpu_set_msw(vcpu, MSW_IA32_FEAT_CTW, BIT(bit));
		TEST_ASSEWT(w == 0,
			    "Setting wesewved bit %d in IA32_FEATUWE_CONTWOW shouwd faiw", bit);
	}
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_DISABWE_QUIWKS2));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_VMX));

	/* No need to actuawwy do KVM_WUN, thus no guest code. */
	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	vmx_save_westowe_msws_test(vcpu);
	ia32_featuwe_contwow_msw_test(vcpu);

	kvm_vm_fwee(vm);
}
