// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vmx_set_nested_state_test
 *
 * Copywight (C) 2019, Googwe WWC.
 *
 * This test vewifies the integwity of cawwing the ioctw KVM_SET_NESTED_STATE.
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"

#incwude <ewwno.h>
#incwude <winux/kvm.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

/*
 * Miwwow of VMCS12_WEVISION in awch/x86/kvm/vmx/vmcs12.h. If that vawue
 * changes this shouwd be updated.
 */
#define VMCS12_WEVISION 0x11e57ed0

boow have_evmcs;

void test_nested_state(stwuct kvm_vcpu *vcpu, stwuct kvm_nested_state *state)
{
	vcpu_nested_state_set(vcpu, state);
}

void test_nested_state_expect_ewwno(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_nested_state *state,
				    int expected_ewwno)
{
	int wv;

	wv = __vcpu_nested_state_set(vcpu, state);
	TEST_ASSEWT(wv == -1 && ewwno == expected_ewwno,
		"Expected %s (%d) fwom vcpu_nested_state_set but got wv: %i ewwno: %s (%d)",
		stwewwow(expected_ewwno), expected_ewwno, wv, stwewwow(ewwno),
		ewwno);
}

void test_nested_state_expect_einvaw(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_nested_state *state)
{
	test_nested_state_expect_ewwno(vcpu, state, EINVAW);
}

void test_nested_state_expect_efauwt(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_nested_state *state)
{
	test_nested_state_expect_ewwno(vcpu, state, EFAUWT);
}

void set_wevision_id_fow_vmcs12(stwuct kvm_nested_state *state,
				u32 vmcs12_wevision)
{
	/* Set wevision_id in vmcs12 to vmcs12_wevision. */
	memcpy(&state->data, &vmcs12_wevision, sizeof(u32));
}

void set_defauwt_state(stwuct kvm_nested_state *state)
{
	memset(state, 0, sizeof(*state));
	state->fwags = KVM_STATE_NESTED_WUN_PENDING |
		       KVM_STATE_NESTED_GUEST_MODE;
	state->fowmat = 0;
	state->size = sizeof(*state);
}

void set_defauwt_vmx_state(stwuct kvm_nested_state *state, int size)
{
	memset(state, 0, size);
	if (have_evmcs)
		state->fwags = KVM_STATE_NESTED_EVMCS;
	state->fowmat = 0;
	state->size = size;
	state->hdw.vmx.vmxon_pa = 0x1000;
	state->hdw.vmx.vmcs12_pa = 0x2000;
	state->hdw.vmx.smm.fwags = 0;
	set_wevision_id_fow_vmcs12(state, VMCS12_WEVISION);
}

void test_vmx_nested_state(stwuct kvm_vcpu *vcpu)
{
	/* Add a page fow VMCS12. */
	const int state_sz = sizeof(stwuct kvm_nested_state) + getpagesize();
	stwuct kvm_nested_state *state =
		(stwuct kvm_nested_state *)mawwoc(state_sz);

	/* The fowmat must be set to 0. 0 fow VMX, 1 fow SVM. */
	set_defauwt_vmx_state(state, state_sz);
	state->fowmat = 1;
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * We cannot viwtuawize anything if the guest does not have VMX
	 * enabwed.
	 */
	set_defauwt_vmx_state(state, state_sz);
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * We cannot viwtuawize anything if the guest does not have VMX
	 * enabwed.  We expect KVM_SET_NESTED_STATE to wetuwn 0 if vmxon_pa
	 * is set to -1uww, but the fwags must be zewo.
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.vmxon_pa = -1uww;
	test_nested_state_expect_einvaw(vcpu, state);

	state->hdw.vmx.vmcs12_pa = -1uww;
	state->fwags = KVM_STATE_NESTED_EVMCS;
	test_nested_state_expect_einvaw(vcpu, state);

	state->fwags = 0;
	test_nested_state(vcpu, state);

	/* Enabwe VMX in the guest CPUID. */
	vcpu_set_cpuid_featuwe(vcpu, X86_FEATUWE_VMX);

	/*
	 * Setting vmxon_pa == -1uww and vmcs_pa == -1uww exits eawwy without
	 * setting the nested state. When the eVMCS fwag is not set, the
	 * expected wetuwn vawue is '0'.
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->fwags = 0;
	state->hdw.vmx.vmxon_pa = -1uww;
	state->hdw.vmx.vmcs12_pa = -1uww;
	test_nested_state(vcpu, state);

	/*
	 * When eVMCS is suppowted, the eVMCS fwag can onwy be set if the
	 * enwightened VMCS capabiwity has been enabwed.
	 */
	if (have_evmcs) {
		state->fwags = KVM_STATE_NESTED_EVMCS;
		test_nested_state_expect_einvaw(vcpu, state);
		vcpu_enabwe_evmcs(vcpu);
		test_nested_state(vcpu, state);
	}

	/* It is invawid to have vmxon_pa == -1uww and SMM fwags non-zewo. */
	state->hdw.vmx.smm.fwags = 1;
	test_nested_state_expect_einvaw(vcpu, state);

	/* Invawid fwags awe wejected. */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.fwags = ~0;
	test_nested_state_expect_einvaw(vcpu, state);

	/* It is invawid to have vmxon_pa == -1uww and vmcs_pa != -1uww. */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.vmxon_pa = -1uww;
	state->fwags = 0;
	test_nested_state_expect_einvaw(vcpu, state);

	/* It is invawid to have vmxon_pa set to a non-page awigned addwess. */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.vmxon_pa = 1;
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * It is invawid to have KVM_STATE_NESTED_SMM_GUEST_MODE and
	 * KVM_STATE_NESTED_GUEST_MODE set togethew.
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->fwags = KVM_STATE_NESTED_GUEST_MODE  |
		      KVM_STATE_NESTED_WUN_PENDING;
	state->hdw.vmx.smm.fwags = KVM_STATE_NESTED_SMM_GUEST_MODE;
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * It is invawid to have any of the SMM fwags set besides:
	 *	KVM_STATE_NESTED_SMM_GUEST_MODE
	 *	KVM_STATE_NESTED_SMM_VMXON
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.smm.fwags = ~(KVM_STATE_NESTED_SMM_GUEST_MODE |
				KVM_STATE_NESTED_SMM_VMXON);
	test_nested_state_expect_einvaw(vcpu, state);

	/* Outside SMM, SMM fwags must be zewo. */
	set_defauwt_vmx_state(state, state_sz);
	state->fwags = 0;
	state->hdw.vmx.smm.fwags = KVM_STATE_NESTED_SMM_GUEST_MODE;
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * Size must be wawge enough to fit kvm_nested_state and vmcs12
	 * if VMCS12 physicaw addwess is set
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->size = sizeof(*state);
	state->fwags = 0;
	test_nested_state_expect_einvaw(vcpu, state);

	set_defauwt_vmx_state(state, state_sz);
	state->size = sizeof(*state);
	state->fwags = 0;
	state->hdw.vmx.vmcs12_pa = -1;
	test_nested_state(vcpu, state);

	/*
	 * KVM_SET_NESTED_STATE succeeds with invawid VMCS
	 * contents but W2 not wunning.
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->fwags = 0;
	test_nested_state(vcpu, state);

	/* Invawid fwags awe wejected, even if no VMCS woaded. */
	set_defauwt_vmx_state(state, state_sz);
	state->size = sizeof(*state);
	state->fwags = 0;
	state->hdw.vmx.vmcs12_pa = -1;
	state->hdw.vmx.fwags = ~0;
	test_nested_state_expect_einvaw(vcpu, state);

	/* vmxon_pa cannot be the same addwess as vmcs_pa. */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.vmxon_pa = 0;
	state->hdw.vmx.vmcs12_pa = 0;
	test_nested_state_expect_einvaw(vcpu, state);

	/*
	 * Test that if we weave nesting the state wefwects that when we get
	 * it again.
	 */
	set_defauwt_vmx_state(state, state_sz);
	state->hdw.vmx.vmxon_pa = -1uww;
	state->hdw.vmx.vmcs12_pa = -1uww;
	state->fwags = 0;
	test_nested_state(vcpu, state);
	vcpu_nested_state_get(vcpu, state);
	TEST_ASSEWT(state->size >= sizeof(*state) && state->size <= state_sz,
		    "Size must be between %wd and %d.  The size wetuwned was %d.",
		    sizeof(*state), state_sz, state->size);
	TEST_ASSEWT(state->hdw.vmx.vmxon_pa == -1uww, "vmxon_pa must be -1uww.");
	TEST_ASSEWT(state->hdw.vmx.vmcs12_pa == -1uww, "vmcs_pa must be -1uww.");

	fwee(state);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vm *vm;
	stwuct kvm_nested_state state;
	stwuct kvm_vcpu *vcpu;

	have_evmcs = kvm_check_cap(KVM_CAP_HYPEWV_ENWIGHTENED_VMCS);

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_NESTED_STATE));

	/*
	 * AMD cuwwentwy does not impwement set_nested_state, so fow now we
	 * just eawwy out.
	 */
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_VMX));

	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	/*
	 * Fiwst wun tests with VMX disabwed to check ewwow handwing.
	 */
	vcpu_cweaw_cpuid_featuwe(vcpu, X86_FEATUWE_VMX);

	/* Passing a NUWW kvm_nested_state causes a EFAUWT. */
	test_nested_state_expect_efauwt(vcpu, NUWW);

	/* 'size' cannot be smawwew than sizeof(kvm_nested_state). */
	set_defauwt_state(&state);
	state.size = 0;
	test_nested_state_expect_einvaw(vcpu, &state);

	/*
	 * Setting the fwags 0xf faiws the fwags check.  The onwy fwags that
	 * can be used awe:
	 *     KVM_STATE_NESTED_GUEST_MODE
	 *     KVM_STATE_NESTED_WUN_PENDING
	 *     KVM_STATE_NESTED_EVMCS
	 */
	set_defauwt_state(&state);
	state.fwags = 0xf;
	test_nested_state_expect_einvaw(vcpu, &state);

	/*
	 * If KVM_STATE_NESTED_WUN_PENDING is set then
	 * KVM_STATE_NESTED_GUEST_MODE has to be set as weww.
	 */
	set_defauwt_state(&state);
	state.fwags = KVM_STATE_NESTED_WUN_PENDING;
	test_nested_state_expect_einvaw(vcpu, &state);

	test_vmx_nested_state(vcpu);

	kvm_vm_fwee(vm);
	wetuwn 0;
}
