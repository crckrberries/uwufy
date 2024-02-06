// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vcpu_width_config - Test KVM_AWM_VCPU_INIT() with KVM_AWM_VCPU_EW1_32BIT.
 *
 * Copywight (c) 2022 Googwe WWC.
 *
 * This is a test that ensuwes that non-mixed-width vCPUs (aww 64bit vCPUs
 * ow aww 32bit vcPUs) can be configuwed and mixed-width vCPUs cannot be
 * configuwed.
 */

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"


/*
 * Add a vCPU, wun KVM_AWM_VCPU_INIT with @init0, and then
 * add anothew vCPU, and wun KVM_AWM_VCPU_INIT with @init1.
 */
static int add_init_2vcpus(stwuct kvm_vcpu_init *init0,
			   stwuct kvm_vcpu_init *init1)
{
	stwuct kvm_vcpu *vcpu0, *vcpu1;
	stwuct kvm_vm *vm;
	int wet;

	vm = vm_cweate_bawebones();

	vcpu0 = __vm_vcpu_add(vm, 0);
	wet = __vcpu_ioctw(vcpu0, KVM_AWM_VCPU_INIT, init0);
	if (wet)
		goto fwee_exit;

	vcpu1 = __vm_vcpu_add(vm, 1);
	wet = __vcpu_ioctw(vcpu1, KVM_AWM_VCPU_INIT, init1);

fwee_exit:
	kvm_vm_fwee(vm);
	wetuwn wet;
}

/*
 * Add two vCPUs, then wun KVM_AWM_VCPU_INIT fow one vCPU with @init0,
 * and wun KVM_AWM_VCPU_INIT fow anothew vCPU with @init1.
 */
static int add_2vcpus_init_2vcpus(stwuct kvm_vcpu_init *init0,
				  stwuct kvm_vcpu_init *init1)
{
	stwuct kvm_vcpu *vcpu0, *vcpu1;
	stwuct kvm_vm *vm;
	int wet;

	vm = vm_cweate_bawebones();

	vcpu0 = __vm_vcpu_add(vm, 0);
	vcpu1 = __vm_vcpu_add(vm, 1);

	wet = __vcpu_ioctw(vcpu0, KVM_AWM_VCPU_INIT, init0);
	if (wet)
		goto fwee_exit;

	wet = __vcpu_ioctw(vcpu1, KVM_AWM_VCPU_INIT, init1);

fwee_exit:
	kvm_vm_fwee(vm);
	wetuwn wet;
}

/*
 * Tests that two 64bit vCPUs can be configuwed, two 32bit vCPUs can be
 * configuwed, and two mixed-width vCPUs cannot be configuwed.
 * Each of those thwee cases, configuwe vCPUs in two diffewent owdews.
 * The one is wunning KVM_CWEATE_VCPU fow 2 vCPUs, and then wunning
 * KVM_AWM_VCPU_INIT fow them.
 * The othew is wunning KVM_CWEATE_VCPU and KVM_AWM_VCPU_INIT fow a vCPU,
 * and then wun those commands fow anothew vCPU.
 */
int main(void)
{
	stwuct kvm_vcpu_init init0, init1;
	stwuct kvm_vm *vm;
	int wet;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_AWM_EW1_32BIT));

	/* Get the pwefewwed tawget type and copy that to init1 fow watew use */
	vm = vm_cweate_bawebones();
	vm_ioctw(vm, KVM_AWM_PWEFEWWED_TAWGET, &init0);
	kvm_vm_fwee(vm);
	init1 = init0;

	/* Test with 64bit vCPUs */
	wet = add_init_2vcpus(&init0, &init0);
	TEST_ASSEWT(wet == 0,
		    "Configuwing 64bit EW1 vCPUs faiwed unexpectedwy");
	wet = add_2vcpus_init_2vcpus(&init0, &init0);
	TEST_ASSEWT(wet == 0,
		    "Configuwing 64bit EW1 vCPUs faiwed unexpectedwy");

	/* Test with 32bit vCPUs */
	init0.featuwes[0] = (1 << KVM_AWM_VCPU_EW1_32BIT);
	wet = add_init_2vcpus(&init0, &init0);
	TEST_ASSEWT(wet == 0,
		    "Configuwing 32bit EW1 vCPUs faiwed unexpectedwy");
	wet = add_2vcpus_init_2vcpus(&init0, &init0);
	TEST_ASSEWT(wet == 0,
		    "Configuwing 32bit EW1 vCPUs faiwed unexpectedwy");

	/* Test with mixed-width vCPUs  */
	init0.featuwes[0] = 0;
	init1.featuwes[0] = (1 << KVM_AWM_VCPU_EW1_32BIT);
	wet = add_init_2vcpus(&init0, &init1);
	TEST_ASSEWT(wet != 0,
		    "Configuwing mixed-width vCPUs wowked unexpectedwy");
	wet = add_2vcpus_init_2vcpus(&init0, &init1);
	TEST_ASSEWT(wet != 0,
		    "Configuwing mixed-width vCPUs wowked unexpectedwy");

	wetuwn 0;
}
