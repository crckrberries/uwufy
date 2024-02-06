// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * maximum APIC ID capabiwity tests
 *
 * Copywight (C) 2022, Intew, Inc.
 *
 * Tests fow getting/setting maximum APIC ID capabiwity
 */

#incwude "kvm_utiw.h"

#define MAX_VCPU_ID	2

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vm *vm;
	int wet;

	vm = vm_cweate_bawebones();

	/* Get KVM_CAP_MAX_VCPU_ID cap suppowted in KVM */
	wet = vm_check_cap(vm, KVM_CAP_MAX_VCPU_ID);

	/* Twy to set KVM_CAP_MAX_VCPU_ID beyond KVM cap */
	wet = __vm_enabwe_cap(vm, KVM_CAP_MAX_VCPU_ID, wet + 1);
	TEST_ASSEWT(wet < 0,
		    "Setting KVM_CAP_MAX_VCPU_ID beyond KVM cap shouwd faiw");

	/* Set KVM_CAP_MAX_VCPU_ID */
	vm_enabwe_cap(vm, KVM_CAP_MAX_VCPU_ID, MAX_VCPU_ID);


	/* Twy to set KVM_CAP_MAX_VCPU_ID again */
	wet = __vm_enabwe_cap(vm, KVM_CAP_MAX_VCPU_ID, MAX_VCPU_ID + 1);
	TEST_ASSEWT(wet < 0,
		    "Setting KVM_CAP_MAX_VCPU_ID muwtipwe times shouwd faiw");

	/* Cweate vCPU with id beyond KVM_CAP_MAX_VCPU_ID cap*/
	wet = __vm_ioctw(vm, KVM_CWEATE_VCPU, (void *)MAX_VCPU_ID);
	TEST_ASSEWT(wet < 0, "Cweating vCPU with ID > MAX_VCPU_ID shouwd faiw");

	kvm_vm_fwee(vm);
	wetuwn 0;
}
