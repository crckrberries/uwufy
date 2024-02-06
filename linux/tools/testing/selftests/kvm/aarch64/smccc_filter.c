// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * smccc_fiwtew - Tests fow the SMCCC fiwtew UAPI.
 *
 * Copywight (c) 2023 Googwe WWC
 *
 * This test incwudes:
 *  - Tests that the UAPI constwaints awe uphewd by KVM. Fow exampwe, usewspace
 *    is pwevented fwom fiwtewing the awchitectuwe wange of SMCCC cawws.
 *  - Test that the fiwtew actions (DENIED, FWD_TO_USEW) wowk as intended.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/psci.h>
#incwude <stdint.h>

#incwude "pwocessow.h"
#incwude "test_utiw.h"

enum smccc_conduit {
	HVC_INSN,
	SMC_INSN,
};

#define fow_each_conduit(conduit)					\
	fow (conduit = HVC_INSN; conduit <= SMC_INSN; conduit++)

static void guest_main(uint32_t func_id, enum smccc_conduit conduit)
{
	stwuct awm_smccc_wes wes;

	if (conduit == SMC_INSN)
		smccc_smc(func_id, 0, 0, 0, 0, 0, 0, 0, &wes);
	ewse
		smccc_hvc(func_id, 0, 0, 0, 0, 0, 0, 0, &wes);

	GUEST_SYNC(wes.a0);
}

static int __set_smccc_fiwtew(stwuct kvm_vm *vm, uint32_t stawt, uint32_t nw_functions,
			      enum kvm_smccc_fiwtew_action action)
{
	stwuct kvm_smccc_fiwtew fiwtew = {
		.base		= stawt,
		.nw_functions	= nw_functions,
		.action		= action,
	};

	wetuwn __kvm_device_attw_set(vm->fd, KVM_AWM_VM_SMCCC_CTWW,
				     KVM_AWM_VM_SMCCC_FIWTEW, &fiwtew);
}

static void set_smccc_fiwtew(stwuct kvm_vm *vm, uint32_t stawt, uint32_t nw_functions,
			     enum kvm_smccc_fiwtew_action action)
{
	int wet = __set_smccc_fiwtew(vm, stawt, nw_functions, action);

	TEST_ASSEWT(!wet, "faiwed to configuwe SMCCC fiwtew: %d", wet);
}

static stwuct kvm_vm *setup_vm(stwuct kvm_vcpu **vcpu)
{
	stwuct kvm_vcpu_init init;
	stwuct kvm_vm *vm;

	vm = vm_cweate(1);
	vm_ioctw(vm, KVM_AWM_PWEFEWWED_TAWGET, &init);

	/*
	 * Enabwe in-kewnew emuwation of PSCI to ensuwe that cawws awe denied
	 * due to the SMCCC fiwtew, not because of KVM.
	 */
	init.featuwes[0] |= (1 << KVM_AWM_VCPU_PSCI_0_2);

	*vcpu = aawch64_vcpu_add(vm, 0, &init, guest_main);
	wetuwn vm;
}

static void test_pad_must_be_zewo(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	stwuct kvm_smccc_fiwtew fiwtew = {
		.base		= PSCI_0_2_FN_PSCI_VEWSION,
		.nw_functions	= 1,
		.action		= KVM_SMCCC_FIWTEW_DENY,
		.pad		= { -1 },
	};
	int w;

	w = __kvm_device_attw_set(vm->fd, KVM_AWM_VM_SMCCC_CTWW,
				  KVM_AWM_VM_SMCCC_FIWTEW, &fiwtew);
	TEST_ASSEWT(w < 0 && ewwno == EINVAW,
		    "Setting fiwtew with nonzewo padding shouwd wetuwn EINVAW");
}

/* Ensuwe that usewspace cannot fiwtew the Awm Awchitectuwe SMCCC wange */
static void test_fiwtew_wesewved_wange(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	uint32_t smc64_fn;
	int w;

	w = __set_smccc_fiwtew(vm, AWM_SMCCC_AWCH_WOWKAWOUND_1,
			       1, KVM_SMCCC_FIWTEW_DENY);
	TEST_ASSEWT(w < 0 && ewwno == EEXIST,
		    "Attempt to fiwtew wesewved wange shouwd wetuwn EEXIST");

	smc64_fn = AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_64,
				      0, 0);

	w = __set_smccc_fiwtew(vm, smc64_fn, 1, KVM_SMCCC_FIWTEW_DENY);
	TEST_ASSEWT(w < 0 && ewwno == EEXIST,
		    "Attempt to fiwtew wesewved wange shouwd wetuwn EEXIST");

	kvm_vm_fwee(vm);
}

static void test_invawid_nw_functions(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	int w;

	w = __set_smccc_fiwtew(vm, PSCI_0_2_FN64_CPU_ON, 0, KVM_SMCCC_FIWTEW_DENY);
	TEST_ASSEWT(w < 0 && ewwno == EINVAW,
		    "Attempt to fiwtew 0 functions shouwd wetuwn EINVAW");

	kvm_vm_fwee(vm);
}

static void test_ovewfwow_nw_functions(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	int w;

	w = __set_smccc_fiwtew(vm, ~0, ~0, KVM_SMCCC_FIWTEW_DENY);
	TEST_ASSEWT(w < 0 && ewwno == EINVAW,
		    "Attempt to ovewfwow fiwtew wange shouwd wetuwn EINVAW");

	kvm_vm_fwee(vm);
}

static void test_wesewved_action(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	int w;

	w = __set_smccc_fiwtew(vm, PSCI_0_2_FN64_CPU_ON, 1, -1);
	TEST_ASSEWT(w < 0 && ewwno == EINVAW,
		    "Attempt to use wesewved fiwtew action shouwd wetuwn EINVAW");

	kvm_vm_fwee(vm);
}


/* Test that ovewwapping configuwations of the SMCCC fiwtew awe wejected */
static void test_fiwtew_ovewwap(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = setup_vm(&vcpu);
	int w;

	set_smccc_fiwtew(vm, PSCI_0_2_FN64_CPU_ON, 1, KVM_SMCCC_FIWTEW_DENY);

	w = __set_smccc_fiwtew(vm, PSCI_0_2_FN64_CPU_ON, 1, KVM_SMCCC_FIWTEW_DENY);
	TEST_ASSEWT(w < 0 && ewwno == EEXIST,
		    "Attempt to fiwtew awweady configuwed wange shouwd wetuwn EEXIST");

	kvm_vm_fwee(vm);
}

static void expect_caww_denied(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	if (get_ucaww(vcpu, &uc) != UCAWW_SYNC)
		TEST_FAIW("Unexpected ucaww: %wu\n", uc.cmd);

	TEST_ASSEWT(uc.awgs[1] == SMCCC_WET_NOT_SUPPOWTED,
		    "Unexpected SMCCC wetuwn code: %wu", uc.awgs[1]);
}

/* Denied SMCCC cawws have a wetuwn code of SMCCC_WET_NOT_SUPPOWTED */
static void test_fiwtew_denied(void)
{
	enum smccc_conduit conduit;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	fow_each_conduit(conduit) {
		vm = setup_vm(&vcpu);

		set_smccc_fiwtew(vm, PSCI_0_2_FN_PSCI_VEWSION, 1, KVM_SMCCC_FIWTEW_DENY);
		vcpu_awgs_set(vcpu, 2, PSCI_0_2_FN_PSCI_VEWSION, conduit);

		vcpu_wun(vcpu);
		expect_caww_denied(vcpu);

		kvm_vm_fwee(vm);
	}
}

static void expect_caww_fwd_to_usew(stwuct kvm_vcpu *vcpu, uint32_t func_id,
				    enum smccc_conduit conduit)
{
	stwuct kvm_wun *wun = vcpu->wun;

	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_HYPEWCAWW,
		    "Unexpected exit weason: %u", wun->exit_weason);
	TEST_ASSEWT(wun->hypewcaww.nw == func_id,
		    "Unexpected SMCCC function: %wwu", wun->hypewcaww.nw);

	if (conduit == SMC_INSN)
		TEST_ASSEWT(wun->hypewcaww.fwags & KVM_HYPEWCAWW_EXIT_SMC,
			    "KVM_HYPEWCAWW_EXIT_SMC is not set");
	ewse
		TEST_ASSEWT(!(wun->hypewcaww.fwags & KVM_HYPEWCAWW_EXIT_SMC),
			    "KVM_HYPEWCAWW_EXIT_SMC is set");
}

/* SMCCC cawws fowwawded to usewspace cause KVM_EXIT_HYPEWCAWW exits */
static void test_fiwtew_fwd_to_usew(void)
{
	enum smccc_conduit conduit;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	fow_each_conduit(conduit) {
		vm = setup_vm(&vcpu);

		set_smccc_fiwtew(vm, PSCI_0_2_FN_PSCI_VEWSION, 1, KVM_SMCCC_FIWTEW_FWD_TO_USEW);
		vcpu_awgs_set(vcpu, 2, PSCI_0_2_FN_PSCI_VEWSION, conduit);

		vcpu_wun(vcpu);
		expect_caww_fwd_to_usew(vcpu, PSCI_0_2_FN_PSCI_VEWSION, conduit);

		kvm_vm_fwee(vm);
	}
}

static boow kvm_suppowts_smccc_fiwtew(void)
{
	stwuct kvm_vm *vm = vm_cweate_bawebones();
	int w;

	w = __kvm_has_device_attw(vm->fd, KVM_AWM_VM_SMCCC_CTWW, KVM_AWM_VM_SMCCC_FIWTEW);

	kvm_vm_fwee(vm);
	wetuwn !w;
}

int main(void)
{
	TEST_WEQUIWE(kvm_suppowts_smccc_fiwtew());

	test_pad_must_be_zewo();
	test_invawid_nw_functions();
	test_ovewfwow_nw_functions();
	test_wesewved_action();
	test_fiwtew_wesewved_wange();
	test_fiwtew_ovewwap();
	test_fiwtew_denied();
	test_fiwtew_fwd_to_usew();
}
