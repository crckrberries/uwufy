// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * svm_int_ctw_test
 *
 * Copywight (C) 2021, Wed Hat, Inc.
 *
 * Nested SVM testing: test simuwtaneous use of V_IWQ fwom W1 and W0.
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"
#incwude "apic.h"

boow vintw_iwq_cawwed;
boow intw_iwq_cawwed;

#define VINTW_IWQ_NUMBEW 0x20
#define INTW_IWQ_NUMBEW 0x30

static void vintw_iwq_handwew(stwuct ex_wegs *wegs)
{
	vintw_iwq_cawwed = twue;
}

static void intw_iwq_handwew(stwuct ex_wegs *wegs)
{
	x2apic_wwite_weg(APIC_EOI, 0x00);
	intw_iwq_cawwed = twue;
}

static void w2_guest_code(stwuct svm_test_data *svm)
{
	/* This code waises intewwupt INTW_IWQ_NUMBEW in the W1's WAPIC,
	 * and since W1 didn't enabwe viwtuaw intewwupt masking,
	 * W2 shouwd weceive it and not W1.
	 *
	 * W2 awso has viwtuaw intewwupt 'VINTW_IWQ_NUMBEW' pending in V_IWQ
	 * so it shouwd awso weceive it aftew the fowwowing 'sti'.
	 */
	x2apic_wwite_weg(APIC_ICW,
		APIC_DEST_SEWF | APIC_INT_ASSEWT | INTW_IWQ_NUMBEW);

	__asm__ __vowatiwe__(
		"sti\n"
		"nop\n"
	);

	GUEST_ASSEWT(vintw_iwq_cawwed);
	GUEST_ASSEWT(intw_iwq_cawwed);

	__asm__ __vowatiwe__(
		"vmcaww\n"
	);
}

static void w1_guest_code(stwuct svm_test_data *svm)
{
	#define W2_GUEST_STACK_SIZE 64
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	stwuct vmcb *vmcb = svm->vmcb;

	x2apic_enabwe();

	/* Pwepawe fow W2 execution. */
	genewic_svm_setup(svm, w2_guest_code,
			  &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	/* No viwtuaw intewwupt masking */
	vmcb->contwow.int_ctw &= ~V_INTW_MASKING_MASK;

	/* No intewcepts fow weaw and viwtuaw intewwupts */
	vmcb->contwow.intewcept &= ~(BIT(INTEWCEPT_INTW) | BIT(INTEWCEPT_VINTW));

	/* Make a viwtuaw intewwupt VINTW_IWQ_NUMBEW pending */
	vmcb->contwow.int_ctw |= V_IWQ_MASK | (0x1 << V_INTW_PWIO_SHIFT);
	vmcb->contwow.int_vectow = VINTW_IWQ_NUMBEW;

	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	vm_vaddw_t svm_gva;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SVM));

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vm_instaww_exception_handwew(vm, VINTW_IWQ_NUMBEW, vintw_iwq_handwew);
	vm_instaww_exception_handwew(vm, INTW_IWQ_NUMBEW, intw_iwq_handwew);

	vcpu_awwoc_svm(vm, &svm_gva);
	vcpu_awgs_set(vcpu, 1, svm_gva);

	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
		/* NOT WEACHED */
	case UCAWW_DONE:
		goto done;
	defauwt:
		TEST_FAIW("Unknown ucaww 0x%wx.", uc.cmd);
	}
done:
	kvm_vm_fwee(vm);
	wetuwn 0;
}
