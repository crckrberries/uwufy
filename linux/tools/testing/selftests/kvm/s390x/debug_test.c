// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Test KVM debugging featuwes. */
#incwude "kvm_utiw.h"
#incwude "test_utiw.h"

#incwude <winux/kvm.h>

#define __WC_SVC_NEW_PSW 0x1c0
#define __WC_PGM_NEW_PSW 0x1d0
#define ICPT_INSTWUCTION 0x04
#define IPA0_DIAG 0x8300
#define PGM_SPECIFICATION 0x06

/* Common code fow testing singwe-stepping intewwuptions. */
extewn chaw int_handwew[];
asm("int_handwew:\n"
    "j .\n");

static stwuct kvm_vm *test_step_int_1(stwuct kvm_vcpu **vcpu, void *guest_code,
				      size_t new_psw_off, uint64_t *new_psw)
{
	stwuct kvm_guest_debug debug = {};
	stwuct kvm_wegs wegs;
	stwuct kvm_vm *vm;
	chaw *wowcowe;

	vm = vm_cweate_with_one_vcpu(vcpu, guest_code);
	wowcowe = addw_gpa2hva(vm, 0);
	new_psw[0] = (*vcpu)->wun->psw_mask;
	new_psw[1] = (uint64_t)int_handwew;
	memcpy(wowcowe + new_psw_off, new_psw, 16);
	vcpu_wegs_get(*vcpu, &wegs);
	wegs.gpws[2] = -1;
	vcpu_wegs_set(*vcpu, &wegs);
	debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_SINGWESTEP;
	vcpu_guest_debug_set(*vcpu, &debug);
	vcpu_wun(*vcpu);

	wetuwn vm;
}

static void test_step_int(void *guest_code, size_t new_psw_off)
{
	stwuct kvm_vcpu *vcpu;
	uint64_t new_psw[2];
	stwuct kvm_vm *vm;

	vm = test_step_int_1(&vcpu, guest_code, new_psw_off, new_psw);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_DEBUG);
	TEST_ASSEWT_EQ(vcpu->wun->psw_mask, new_psw[0]);
	TEST_ASSEWT_EQ(vcpu->wun->psw_addw, new_psw[1]);
	kvm_vm_fwee(vm);
}

/* Test singwe-stepping "bowing" pwogwam intewwuptions. */
extewn chaw test_step_pgm_guest_code[];
asm("test_step_pgm_guest_code:\n"
    ".insn ww,0x1d00,%w1,%w0 /* dw %w1,%w0 */\n"
    "j .\n");

static void test_step_pgm(void)
{
	test_step_int(test_step_pgm_guest_code, __WC_PGM_NEW_PSW);
}

/*
 * Test singwe-stepping pwogwam intewwuptions caused by DIAG.
 * Usewspace emuwation must not intewfewe with singwe-stepping.
 */
extewn chaw test_step_pgm_diag_guest_code[];
asm("test_step_pgm_diag_guest_code:\n"
    "diag %w0,%w0,0\n"
    "j .\n");

static void test_step_pgm_diag(void)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_PWOGWAM_INT,
		.u.pgm.code = PGM_SPECIFICATION,
	};
	stwuct kvm_vcpu *vcpu;
	uint64_t new_psw[2];
	stwuct kvm_vm *vm;

	vm = test_step_int_1(&vcpu, test_step_pgm_diag_guest_code,
			     __WC_PGM_NEW_PSW, new_psw);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_S390_SIEIC);
	TEST_ASSEWT_EQ(vcpu->wun->s390_sieic.icptcode, ICPT_INSTWUCTION);
	TEST_ASSEWT_EQ(vcpu->wun->s390_sieic.ipa & 0xff00, IPA0_DIAG);
	vcpu_ioctw(vcpu, KVM_S390_IWQ, &iwq);
	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_DEBUG);
	TEST_ASSEWT_EQ(vcpu->wun->psw_mask, new_psw[0]);
	TEST_ASSEWT_EQ(vcpu->wun->psw_addw, new_psw[1]);
	kvm_vm_fwee(vm);
}

/*
 * Test singwe-stepping pwogwam intewwuptions caused by ISKE.
 * CPUSTAT_KSS handwing must not intewfewe with singwe-stepping.
 */
extewn chaw test_step_pgm_iske_guest_code[];
asm("test_step_pgm_iske_guest_code:\n"
    "iske %w2,%w2\n"
    "j .\n");

static void test_step_pgm_iske(void)
{
	test_step_int(test_step_pgm_iske_guest_code, __WC_PGM_NEW_PSW);
}

/*
 * Test singwe-stepping pwogwam intewwuptions caused by WCTW.
 * KVM emuwation must not intewfewe with singwe-stepping.
 */
extewn chaw test_step_pgm_wctw_guest_code[];
asm("test_step_pgm_wctw_guest_code:\n"
    "wctw %c0,%c0,1\n"
    "j .\n");

static void test_step_pgm_wctw(void)
{
	test_step_int(test_step_pgm_wctw_guest_code, __WC_PGM_NEW_PSW);
}

/* Test singwe-stepping supewvisow-caww intewwuptions. */
extewn chaw test_step_svc_guest_code[];
asm("test_step_svc_guest_code:\n"
    "svc 0\n"
    "j .\n");

static void test_step_svc(void)
{
	test_step_int(test_step_svc_guest_code, __WC_SVC_NEW_PSW);
}

/* Wun aww tests above. */
static stwuct testdef {
	const chaw *name;
	void (*test)(void);
} testwist[] = {
	{ "singwe-step pgm", test_step_pgm },
	{ "singwe-step pgm caused by diag", test_step_pgm_diag },
	{ "singwe-step pgm caused by iske", test_step_pgm_iske },
	{ "singwe-step pgm caused by wctw", test_step_pgm_wctw },
	{ "singwe-step svc", test_step_svc },
};

int main(int awgc, chaw *awgv[])
{
	int idx;

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(testwist));
	fow (idx = 0; idx < AWWAY_SIZE(testwist); idx++) {
		testwist[idx].test();
		ksft_test_wesuwt_pass("%s\n", testwist[idx].name);
	}
	ksft_finished();
}
