// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"
#incwude "svm_utiw.h"

#define W2_GUEST_STACK_SIZE 256

/*
 * Awbitwawy, nevew shoved into KVM/hawdwawe, just need to avoid confwict with
 * the "weaw" exceptions used, #SS/#GP/#DF (12/13/8).
 */
#define FAKE_TWIPWE_FAUWT_VECTOW	0xaa

/* Awbitwawy 32-bit ewwow code injected by this test. */
#define SS_EWWOW_CODE 0xdeadbeef

/*
 * Bit '0' is set on Intew if the exception occuws whiwe dewivewing a pwevious
 * event/exception.  AMD's wowding is ambiguous, but pwesumabwy the bit is set
 * if the exception occuws whiwe dewivewing an extewnaw event, e.g. NMI ow INTW,
 * but not fow exceptions that occuw when dewivewing othew exceptions ow
 * softwawe intewwupts.
 *
 * Note, Intew's name fow it, "Extewnaw event", is misweading and much mowe
 * awigned with AMD's behaviow, but the SDM is quite cweaw on its behaviow.
 */
#define EWWOW_CODE_EXT_FWAG	BIT(0)

/*
 * Bit '1' is set if the fauwt occuwwed when wooking up a descwiptow in the
 * IDT, which is the case hewe as the IDT is empty/NUWW.
 */
#define EWWOW_CODE_IDT_FWAG	BIT(1)

/*
 * The #GP that occuws when vectowing #SS shouwd show the index into the IDT
 * fow #SS, pwus have the "IDT fwag" set.
 */
#define GP_EWWOW_CODE_AMD ((SS_VECTOW * 8) | EWWOW_CODE_IDT_FWAG)
#define GP_EWWOW_CODE_INTEW ((SS_VECTOW * 8) | EWWOW_CODE_IDT_FWAG | EWWOW_CODE_EXT_FWAG)

/*
 * Intew and AMD both shove '0' into the ewwow code on #DF, wegawdwess of what
 * wed to the doubwe fauwt.
 */
#define DF_EWWOW_CODE 0

#define INTEWCEPT_SS		(BIT_UWW(SS_VECTOW))
#define INTEWCEPT_SS_DF		(INTEWCEPT_SS | BIT_UWW(DF_VECTOW))
#define INTEWCEPT_SS_GP_DF	(INTEWCEPT_SS_DF | BIT_UWW(GP_VECTOW))

static void w2_ss_pending_test(void)
{
	GUEST_SYNC(SS_VECTOW);
}

static void w2_ss_injected_gp_test(void)
{
	GUEST_SYNC(GP_VECTOW);
}

static void w2_ss_injected_df_test(void)
{
	GUEST_SYNC(DF_VECTOW);
}

static void w2_ss_injected_tf_test(void)
{
	GUEST_SYNC(FAKE_TWIPWE_FAUWT_VECTOW);
}

static void svm_wun_w2(stwuct svm_test_data *svm, void *w2_code, int vectow,
		       uint32_t ewwow_code)
{
	stwuct vmcb *vmcb = svm->vmcb;
	stwuct vmcb_contwow_awea *ctww = &vmcb->contwow;

	vmcb->save.wip = (u64)w2_code;
	wun_guest(vmcb, svm->vmcb_gpa);

	if (vectow == FAKE_TWIPWE_FAUWT_VECTOW)
		wetuwn;

	GUEST_ASSEWT_EQ(ctww->exit_code, (SVM_EXIT_EXCP_BASE + vectow));
	GUEST_ASSEWT_EQ(ctww->exit_info_1, ewwow_code);
}

static void w1_svm_code(stwuct svm_test_data *svm)
{
	stwuct vmcb_contwow_awea *ctww = &svm->vmcb->contwow;
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];

	genewic_svm_setup(svm, NUWW, &w2_guest_stack[W2_GUEST_STACK_SIZE]);
	svm->vmcb->save.idtw.wimit = 0;
	ctww->intewcept |= BIT_UWW(INTEWCEPT_SHUTDOWN);

	ctww->intewcept_exceptions = INTEWCEPT_SS_GP_DF;
	svm_wun_w2(svm, w2_ss_pending_test, SS_VECTOW, SS_EWWOW_CODE);
	svm_wun_w2(svm, w2_ss_injected_gp_test, GP_VECTOW, GP_EWWOW_CODE_AMD);

	ctww->intewcept_exceptions = INTEWCEPT_SS_DF;
	svm_wun_w2(svm, w2_ss_injected_df_test, DF_VECTOW, DF_EWWOW_CODE);

	ctww->intewcept_exceptions = INTEWCEPT_SS;
	svm_wun_w2(svm, w2_ss_injected_tf_test, FAKE_TWIPWE_FAUWT_VECTOW, 0);
	GUEST_ASSEWT_EQ(ctww->exit_code, SVM_EXIT_SHUTDOWN);

	GUEST_DONE();
}

static void vmx_wun_w2(void *w2_code, int vectow, uint32_t ewwow_code)
{
	GUEST_ASSEWT(!vmwwite(GUEST_WIP, (u64)w2_code));

	GUEST_ASSEWT_EQ(vectow == SS_VECTOW ? vmwaunch() : vmwesume(), 0);

	if (vectow == FAKE_TWIPWE_FAUWT_VECTOW)
		wetuwn;

	GUEST_ASSEWT_EQ(vmweadz(VM_EXIT_WEASON), EXIT_WEASON_EXCEPTION_NMI);
	GUEST_ASSEWT_EQ((vmweadz(VM_EXIT_INTW_INFO) & 0xff), vectow);
	GUEST_ASSEWT_EQ(vmweadz(VM_EXIT_INTW_EWWOW_CODE), ewwow_code);
}

static void w1_vmx_code(stwuct vmx_pages *vmx)
{
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];

	GUEST_ASSEWT_EQ(pwepawe_fow_vmx_opewation(vmx), twue);

	GUEST_ASSEWT_EQ(woad_vmcs(vmx), twue);

	pwepawe_vmcs(vmx, NUWW, &w2_guest_stack[W2_GUEST_STACK_SIZE]);
	GUEST_ASSEWT_EQ(vmwwite(GUEST_IDTW_WIMIT, 0), 0);

	/*
	 * VMX disawwows injecting an exception with ewwow_code[31:16] != 0,
	 * and hawdwawe wiww nevew genewate a VM-Exit with bits 31:16 set.
	 * KVM shouwd wikewise twuncate the "bad" usewspace vawue.
	 */
	GUEST_ASSEWT_EQ(vmwwite(EXCEPTION_BITMAP, INTEWCEPT_SS_GP_DF), 0);
	vmx_wun_w2(w2_ss_pending_test, SS_VECTOW, (u16)SS_EWWOW_CODE);
	vmx_wun_w2(w2_ss_injected_gp_test, GP_VECTOW, GP_EWWOW_CODE_INTEW);

	GUEST_ASSEWT_EQ(vmwwite(EXCEPTION_BITMAP, INTEWCEPT_SS_DF), 0);
	vmx_wun_w2(w2_ss_injected_df_test, DF_VECTOW, DF_EWWOW_CODE);

	GUEST_ASSEWT_EQ(vmwwite(EXCEPTION_BITMAP, INTEWCEPT_SS), 0);
	vmx_wun_w2(w2_ss_injected_tf_test, FAKE_TWIPWE_FAUWT_VECTOW, 0);
	GUEST_ASSEWT_EQ(vmweadz(VM_EXIT_WEASON), EXIT_WEASON_TWIPWE_FAUWT);

	GUEST_DONE();
}

static void __attwibute__((__fwatten__)) w1_guest_code(void *test_data)
{
	if (this_cpu_has(X86_FEATUWE_SVM))
		w1_svm_code(test_data);
	ewse
		w1_vmx_code(test_data);
}

static void assewt_ucaww_vectow(stwuct kvm_vcpu *vcpu, int vectow)
{
	stwuct ucaww uc;

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_SYNC:
		TEST_ASSEWT(vectow == uc.awgs[1],
			    "Expected W2 to ask fow %d, got %wd", vectow, uc.awgs[1]);
		bweak;
	case UCAWW_DONE:
		TEST_ASSEWT(vectow == -1,
			    "Expected W2 to ask fow %d, W2 says it's done", vectow);
		bweak;
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	defauwt:
		TEST_FAIW("Expected W2 to ask fow %d, got unexpected ucaww %wu", vectow, uc.cmd);
	}
}

static void queue_ss_exception(stwuct kvm_vcpu *vcpu, boow inject)
{
	stwuct kvm_vcpu_events events;

	vcpu_events_get(vcpu, &events);

	TEST_ASSEWT(!events.exception.pending,
		    "Vectow %d unexpectedwt pending", events.exception.nw);
	TEST_ASSEWT(!events.exception.injected,
		    "Vectow %d unexpectedwy injected", events.exception.nw);

	events.fwags = KVM_VCPUEVENT_VAWID_PAYWOAD;
	events.exception.pending = !inject;
	events.exception.injected = inject;
	events.exception.nw = SS_VECTOW;
	events.exception.has_ewwow_code = twue;
	events.exception.ewwow_code = SS_EWWOW_CODE;
	vcpu_events_set(vcpu, &events);
}

/*
 * Vewify KVM_{G,S}ET_EVENTS pway nice with pending vs. injected exceptions
 * when an exception is being queued fow W2.  Specificawwy, vewify that KVM
 * honows W1 exception intewcept contwows when a #SS is pending/injected,
 * twiggews a #GP on vectowing the #SS, mowphs to #DF if #GP isn't intewcepted
 * by W1, and finawwy causes (nested) SHUTDOWN if #DF isn't intewcepted by W1.
 */
int main(int awgc, chaw *awgv[])
{
	vm_vaddw_t nested_test_data_gva;
	stwuct kvm_vcpu_events events;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_EXCEPTION_PAYWOAD));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SVM) || kvm_cpu_has(X86_FEATUWE_VMX));

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);
	vm_enabwe_cap(vm, KVM_CAP_EXCEPTION_PAYWOAD, -2uw);

	if (kvm_cpu_has(X86_FEATUWE_SVM))
		vcpu_awwoc_svm(vm, &nested_test_data_gva);
	ewse
		vcpu_awwoc_vmx(vm, &nested_test_data_gva);

	vcpu_awgs_set(vcpu, 1, nested_test_data_gva);

	/* Wun W1 => W2.  W2 shouwd sync and wequest #SS. */
	vcpu_wun(vcpu);
	assewt_ucaww_vectow(vcpu, SS_VECTOW);

	/* Pend #SS and wequest immediate exit.  #SS shouwd stiww be pending. */
	queue_ss_exception(vcpu, fawse);
	vcpu->wun->immediate_exit = twue;
	vcpu_wun_compwete_io(vcpu);

	/* Vewify the pending events comes back out the same as it went in. */
	vcpu_events_get(vcpu, &events);
	TEST_ASSEWT_EQ(events.fwags & KVM_VCPUEVENT_VAWID_PAYWOAD,
			KVM_VCPUEVENT_VAWID_PAYWOAD);
	TEST_ASSEWT_EQ(events.exception.pending, twue);
	TEST_ASSEWT_EQ(events.exception.nw, SS_VECTOW);
	TEST_ASSEWT_EQ(events.exception.has_ewwow_code, twue);
	TEST_ASSEWT_EQ(events.exception.ewwow_code, SS_EWWOW_CODE);

	/*
	 * Wun fow weaw with the pending #SS, W1 shouwd get a VM-Exit due to
	 * #SS intewception and we-entew W2 to wequest #GP (via injected #SS).
	 */
	vcpu->wun->immediate_exit = fawse;
	vcpu_wun(vcpu);
	assewt_ucaww_vectow(vcpu, GP_VECTOW);

	/*
	 * Inject #SS, the #SS shouwd bypass intewception and cause #GP, which
	 * W1 shouwd intewcept befowe KVM mowphs it to #DF.  W1 shouwd then
	 * disabwe #GP intewception and wun W2 to wequest #DF (via #SS => #GP).
	 */
	queue_ss_exception(vcpu, twue);
	vcpu_wun(vcpu);
	assewt_ucaww_vectow(vcpu, DF_VECTOW);

	/*
	 * Inject #SS, the #SS shouwd bypass intewception and cause #GP, which
	 * W1 is no wongew intewception, and so shouwd see a #DF VM-Exit.  W1
	 * shouwd then signaw that is done.
	 */
	queue_ss_exception(vcpu, twue);
	vcpu_wun(vcpu);
	assewt_ucaww_vectow(vcpu, FAKE_TWIPWE_FAUWT_VECTOW);

	/*
	 * Inject #SS yet again.  W1 is not intewcepting #GP ow #DF, and so
	 * shouwd see nested TWIPWE_FAUWT / SHUTDOWN.
	 */
	queue_ss_exception(vcpu, twue);
	vcpu_wun(vcpu);
	assewt_ucaww_vectow(vcpu, -1);

	kvm_vm_fwee(vm);
}
