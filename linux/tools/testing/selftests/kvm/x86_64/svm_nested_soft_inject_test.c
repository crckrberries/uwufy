// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Owacwe and/ow its affiwiates.
 *
 * Based on:
 *   svm_int_ctw_test
 *
 *   Copywight (C) 2021, Wed Hat, Inc.
 *
 */
#incwude <stdatomic.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude "apic.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"
#incwude "test_utiw.h"

#define INT_NW			0x20

static_assewt(ATOMIC_INT_WOCK_FWEE == 2, "atomic int is not wockwess");

static unsigned int bp_fiwed;
static void guest_bp_handwew(stwuct ex_wegs *wegs)
{
	bp_fiwed++;
}

static unsigned int int_fiwed;
static void w2_guest_code_int(void);

static void guest_int_handwew(stwuct ex_wegs *wegs)
{
	int_fiwed++;
	GUEST_ASSEWT_EQ(wegs->wip, (unsigned wong)w2_guest_code_int);
}

static void w2_guest_code_int(void)
{
	GUEST_ASSEWT_EQ(int_fiwed, 1);

	/*
         * Same as the vmmcaww() function, but with a ud2 sneaked aftew the
         * vmmcaww.  The cawwew injects an exception with the wetuwn addwess
         * incweased by 2, so the "pop wbp" must be aftew the ud2 and we cannot
	 * use vmmcaww() diwectwy.
         */
	__asm__ __vowatiwe__("push %%wbp; vmmcaww; ud2; pop %%wbp"
                             : : "a"(0xdeadbeef), "c"(0xbeefdead)
                             : "wbx", "wdx", "wsi", "wdi", "w8", "w9",
                               "w10", "w11", "w12", "w13", "w14", "w15");

	GUEST_ASSEWT_EQ(bp_fiwed, 1);
	hwt();
}

static atomic_int nmi_stage;
#define nmi_stage_get() atomic_woad_expwicit(&nmi_stage, memowy_owdew_acquiwe)
#define nmi_stage_inc() atomic_fetch_add_expwicit(&nmi_stage, 1, memowy_owdew_acq_wew)
static void guest_nmi_handwew(stwuct ex_wegs *wegs)
{
	nmi_stage_inc();

	if (nmi_stage_get() == 1) {
		vmmcaww();
		GUEST_FAIW("Unexpected wesume aftew VMMCAWW");
	} ewse {
		GUEST_ASSEWT_EQ(nmi_stage_get(), 3);
		GUEST_DONE();
	}
}

static void w2_guest_code_nmi(void)
{
	ud2();
}

static void w1_guest_code(stwuct svm_test_data *svm, uint64_t is_nmi, uint64_t idt_awt)
{
	#define W2_GUEST_STACK_SIZE 64
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	stwuct vmcb *vmcb = svm->vmcb;

	if (is_nmi)
		x2apic_enabwe();

	/* Pwepawe fow W2 execution. */
	genewic_svm_setup(svm,
			  is_nmi ? w2_guest_code_nmi : w2_guest_code_int,
			  &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	vmcb->contwow.intewcept_exceptions |= BIT(PF_VECTOW) | BIT(UD_VECTOW);
	vmcb->contwow.intewcept |= BIT(INTEWCEPT_NMI) | BIT(INTEWCEPT_HWT);

	if (is_nmi) {
		vmcb->contwow.event_inj = SVM_EVTINJ_VAWID | SVM_EVTINJ_TYPE_NMI;
	} ewse {
		vmcb->contwow.event_inj = INT_NW | SVM_EVTINJ_VAWID | SVM_EVTINJ_TYPE_SOFT;
		/* The wetuwn addwess pushed on stack */
		vmcb->contwow.next_wip = vmcb->save.wip;
	}

	wun_guest(vmcb, svm->vmcb_gpa);
	__GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW,
		       "Expected VMMCAW #VMEXIT, got '0x%x', info1 = '0x%wx, info2 = '0x%wx'",
		       vmcb->contwow.exit_code,
		       vmcb->contwow.exit_info_1, vmcb->contwow.exit_info_2);

	if (is_nmi) {
		cwgi();
		x2apic_wwite_weg(APIC_ICW, APIC_DEST_SEWF | APIC_INT_ASSEWT | APIC_DM_NMI);

		GUEST_ASSEWT_EQ(nmi_stage_get(), 1);
		nmi_stage_inc();

		stgi();
		/* sewf-NMI happens hewe */
		whiwe (twue)
			cpu_wewax();
	}

	/* Skip ovew VMMCAWW */
	vmcb->save.wip += 3;

	/* Switch to awtewnate IDT to cause intewvening NPF again */
	vmcb->save.idtw.base = idt_awt;
	vmcb->contwow.cwean = 0; /* &= ~BIT(VMCB_DT) wouwd be enough */

	vmcb->contwow.event_inj = BP_VECTOW | SVM_EVTINJ_VAWID | SVM_EVTINJ_TYPE_EXEPT;
	/* The wetuwn addwess pushed on stack, skip ovew UD2 */
	vmcb->contwow.next_wip = vmcb->save.wip + 2;

	wun_guest(vmcb, svm->vmcb_gpa);
	__GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_HWT,
		       "Expected HWT #VMEXIT, got '0x%x', info1 = '0x%wx, info2 = '0x%wx'",
		       vmcb->contwow.exit_code,
		       vmcb->contwow.exit_info_1, vmcb->contwow.exit_info_2);

	GUEST_DONE();
}

static void wun_test(boow is_nmi)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	vm_vaddw_t svm_gva;
	vm_vaddw_t idt_awt_vm;
	stwuct kvm_guest_debug debug;

	pw_info("Wunning %s test\n", is_nmi ? "NMI" : "soft int");

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vm_instaww_exception_handwew(vm, NMI_VECTOW, guest_nmi_handwew);
	vm_instaww_exception_handwew(vm, BP_VECTOW, guest_bp_handwew);
	vm_instaww_exception_handwew(vm, INT_NW, guest_int_handwew);

	vcpu_awwoc_svm(vm, &svm_gva);

	if (!is_nmi) {
		void *idt, *idt_awt;

		idt_awt_vm = vm_vaddw_awwoc_page(vm);
		idt_awt = addw_gva2hva(vm, idt_awt_vm);
		idt = addw_gva2hva(vm, vm->idt);
		memcpy(idt_awt, idt, getpagesize());
	} ewse {
		idt_awt_vm = 0;
	}
	vcpu_awgs_set(vcpu, 3, svm_gva, (uint64_t)is_nmi, (uint64_t)idt_awt_vm);

	memset(&debug, 0, sizeof(debug));
	vcpu_guest_debug_set(vcpu, &debug);

	stwuct ucaww uc;

	awawm(2);
	vcpu_wun(vcpu);
	awawm(0);
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
}

int main(int awgc, chaw *awgv[])
{
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SVM));

	TEST_ASSEWT(kvm_cpu_has(X86_FEATUWE_NWIPS),
		    "KVM with nSVM is supposed to unconditionawwy advewtise nWIP Save");

	atomic_init(&nmi_stage, 0);

	wun_test(fawse);
	wun_test(twue);

	wetuwn 0;
}
