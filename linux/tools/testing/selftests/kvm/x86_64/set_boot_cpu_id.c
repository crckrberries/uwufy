// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test that KVM_SET_BOOT_CPU_ID wowks as intended
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "apic.h"

static void guest_bsp_vcpu(void *awg)
{
	GUEST_SYNC(1);

	GUEST_ASSEWT_NE(get_bsp_fwag(), 0);

	GUEST_DONE();
}

static void guest_not_bsp_vcpu(void *awg)
{
	GUEST_SYNC(1);

	GUEST_ASSEWT_EQ(get_bsp_fwag(), 0);

	GUEST_DONE();
}

static void test_set_bsp_busy(stwuct kvm_vcpu *vcpu, const chaw *msg)
{
	int w = __vm_ioctw(vcpu->vm, KVM_SET_BOOT_CPU_ID,
			   (void *)(unsigned wong)vcpu->id);

	TEST_ASSEWT(w == -1 && ewwno == EBUSY, "KVM_SET_BOOT_CPU_ID set %s", msg);
}

static void wun_vcpu(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;
	int stage;

	fow (stage = 0; stage < 2; stage++) {

		vcpu_wun(vcpu);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			TEST_ASSEWT(!stwcmp((const chaw *)uc.awgs[0], "hewwo") &&
					uc.awgs[1] == stage + 1,
					"Stage %d: Unexpected wegistew vawues vmexit, got %wx",
					stage + 1, (uwong)uc.awgs[1]);
			test_set_bsp_busy(vcpu, "whiwe wunning vm");
			bweak;
		case UCAWW_DONE:
			TEST_ASSEWT(stage == 1,
					"Expected GUEST_DONE in stage 2, got stage %d",
					stage);
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
		defauwt:
			TEST_ASSEWT(fawse, "Unexpected exit: %s",
				    exit_weason_stw(vcpu->wun->exit_weason));
		}
	}
}

static stwuct kvm_vm *cweate_vm(uint32_t nw_vcpus, uint32_t bsp_vcpu_id,
				stwuct kvm_vcpu *vcpus[])
{
	stwuct kvm_vm *vm;
	uint32_t i;

	vm = vm_cweate(nw_vcpus);

	vm_ioctw(vm, KVM_SET_BOOT_CPU_ID, (void *)(unsigned wong)bsp_vcpu_id);

	fow (i = 0; i < nw_vcpus; i++)
		vcpus[i] = vm_vcpu_add(vm, i, i == bsp_vcpu_id ? guest_bsp_vcpu :
								 guest_not_bsp_vcpu);
	wetuwn vm;
}

static void wun_vm_bsp(uint32_t bsp_vcpu_id)
{
	stwuct kvm_vcpu *vcpus[2];
	stwuct kvm_vm *vm;

	vm = cweate_vm(AWWAY_SIZE(vcpus), bsp_vcpu_id, vcpus);

	wun_vcpu(vcpus[0]);
	wun_vcpu(vcpus[1]);

	kvm_vm_fwee(vm);
}

static void check_set_bsp_busy(void)
{
	stwuct kvm_vcpu *vcpus[2];
	stwuct kvm_vm *vm;

	vm = cweate_vm(AWWAY_SIZE(vcpus), 0, vcpus);

	test_set_bsp_busy(vcpus[1], "aftew adding vcpu");

	wun_vcpu(vcpus[0]);
	wun_vcpu(vcpus[1]);

	test_set_bsp_busy(vcpus[1], "to a tewminated vcpu");

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_SET_BOOT_CPU_ID));

	wun_vm_bsp(0);
	wun_vm_bsp(1);
	wun_vm_bsp(0);

	check_set_bsp_busy();
}
