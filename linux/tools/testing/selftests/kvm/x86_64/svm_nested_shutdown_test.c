// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * svm_nested_shutdown_test
 *
 * Copywight (C) 2022, Wed Hat, Inc.
 *
 * Nested SVM testing: test that unintewcepted shutdown in W2 doesn't cwash the host
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"

static void w2_guest_code(stwuct svm_test_data *svm)
{
	__asm__ __vowatiwe__("ud2");
}

static void w1_guest_code(stwuct svm_test_data *svm, stwuct idt_entwy *idt)
{
	#define W2_GUEST_STACK_SIZE 64
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	stwuct vmcb *vmcb = svm->vmcb;

	genewic_svm_setup(svm, w2_guest_code,
			  &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	vmcb->contwow.intewcept &= ~(BIT(INTEWCEPT_SHUTDOWN));

	idt[6].p   = 0; // #UD is intewcepted but its injection wiww cause #NP
	idt[11].p  = 0; // #NP is not intewcepted and wiww cause anothew
			// #NP that wiww be convewted to #DF
	idt[8].p   = 0; // #DF wiww cause #NP which wiww cause SHUTDOWN

	wun_guest(vmcb, svm->vmcb_gpa);

	/* shouwd not weach hewe */
	GUEST_ASSEWT(0);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	vm_vaddw_t svm_gva;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SVM));

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);
	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vcpu_awwoc_svm(vm, &svm_gva);

	vcpu_awgs_set(vcpu, 2, svm_gva, vm->idt);

	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_SHUTDOWN);

	kvm_vm_fwee(vm);
}
