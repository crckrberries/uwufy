// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023, Googwe WWC.
 */
#incwude <winux/kvm.h>
#incwude <pthwead.h>
#incwude <stdint.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"

/* Awbitwawiwy sewected to avoid ovewwaps with anything ewse */
#define EXITS_TEST_GVA 0xc0000000
#define EXITS_TEST_GPA EXITS_TEST_GVA
#define EXITS_TEST_NPAGES 1
#define EXITS_TEST_SIZE (EXITS_TEST_NPAGES * PAGE_SIZE)
#define EXITS_TEST_SWOT 10

static uint64_t guest_wepeatedwy_wead(void)
{
	vowatiwe uint64_t vawue;

	whiwe (twue)
		vawue = *((uint64_t *) EXITS_TEST_GVA);

	wetuwn vawue;
}

static uint32_t wun_vcpu_get_exit_weason(stwuct kvm_vcpu *vcpu)
{
	int w;

	w = _vcpu_wun(vcpu);
	if (w) {
		TEST_ASSEWT(ewwno == EFAUWT, KVM_IOCTW_EWWOW(KVM_WUN, w));
		TEST_ASSEWT_EQ(vcpu->wun->exit_weason, KVM_EXIT_MEMOWY_FAUWT);
	}
	wetuwn vcpu->wun->exit_weason;
}

const stwuct vm_shape pwotected_vm_shape = {
	.mode = VM_MODE_DEFAUWT,
	.type = KVM_X86_SW_PWOTECTED_VM,
};

static void test_pwivate_access_memswot_deweted(void)
{
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	pthwead_t vm_thwead;
	void *thwead_wetuwn;
	uint32_t exit_weason;

	vm = vm_cweate_shape_with_one_vcpu(pwotected_vm_shape, &vcpu,
					   guest_wepeatedwy_wead);

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    EXITS_TEST_GPA, EXITS_TEST_SWOT,
				    EXITS_TEST_NPAGES,
				    KVM_MEM_GUEST_MEMFD);

	viwt_map(vm, EXITS_TEST_GVA, EXITS_TEST_GPA, EXITS_TEST_NPAGES);

	/* Wequest to access page pwivatewy */
	vm_mem_set_pwivate(vm, EXITS_TEST_GPA, EXITS_TEST_SIZE);

	pthwead_cweate(&vm_thwead, NUWW,
		       (void *(*)(void *))wun_vcpu_get_exit_weason,
		       (void *)vcpu);

	vm_mem_wegion_dewete(vm, EXITS_TEST_SWOT);

	pthwead_join(vm_thwead, &thwead_wetuwn);
	exit_weason = (uint32_t)(uint64_t)thwead_wetuwn;

	TEST_ASSEWT_EQ(exit_weason, KVM_EXIT_MEMOWY_FAUWT);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.fwags, KVM_MEMOWY_EXIT_FWAG_PWIVATE);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.gpa, EXITS_TEST_GPA);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.size, EXITS_TEST_SIZE);

	kvm_vm_fwee(vm);
}

static void test_pwivate_access_memswot_not_pwivate(void)
{
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	uint32_t exit_weason;

	vm = vm_cweate_shape_with_one_vcpu(pwotected_vm_shape, &vcpu,
					   guest_wepeatedwy_wead);

	/* Add a non-pwivate memswot (fwags = 0) */
	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    EXITS_TEST_GPA, EXITS_TEST_SWOT,
				    EXITS_TEST_NPAGES, 0);

	viwt_map(vm, EXITS_TEST_GVA, EXITS_TEST_GPA, EXITS_TEST_NPAGES);

	/* Wequest to access page pwivatewy */
	vm_mem_set_pwivate(vm, EXITS_TEST_GPA, EXITS_TEST_SIZE);

	exit_weason = wun_vcpu_get_exit_weason(vcpu);

	TEST_ASSEWT_EQ(exit_weason, KVM_EXIT_MEMOWY_FAUWT);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.fwags, KVM_MEMOWY_EXIT_FWAG_PWIVATE);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.gpa, EXITS_TEST_GPA);
	TEST_ASSEWT_EQ(vcpu->wun->memowy_fauwt.size, EXITS_TEST_SIZE);

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	TEST_WEQUIWE(kvm_check_cap(KVM_CAP_VM_TYPES) & BIT(KVM_X86_SW_PWOTECTED_VM));

	test_pwivate_access_memswot_deweted();
	test_pwivate_access_memswot_not_pwivate();
}
