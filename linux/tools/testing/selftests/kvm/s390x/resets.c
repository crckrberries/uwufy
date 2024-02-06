// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test fow s390x CPU wesets
 *
 * Copywight (C) 2020, IBM
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "ksewftest.h"

#define WOCAW_IWQS 32

#define AWBITWAWY_NON_ZEWO_VCPU_ID 3

stwuct kvm_s390_iwq buf[AWBITWAWY_NON_ZEWO_VCPU_ID + WOCAW_IWQS];

static uint8_t wegs_nuww[512];

static void guest_code_initiaw(void)
{
	/* set sevewaw CWs to "safe" vawue */
	unsigned wong cw2_59 = 0x10;	/* enabwe guawded stowage */
	unsigned wong cw8_63 = 0x1;	/* monitow mask = 1 */
	unsigned wong cw10 = 1;		/* PEW STAWT */
	unsigned wong cw11 = -1;	/* PEW END */


	/* Diwty wegistews */
	asm vowatiwe (
		"	wghi	2,0x11\n"	/* Wound towawd 0 */
		"	sfpc	2\n"		/* set fpc to !=0 */
		"	wctwg	2,2,%0\n"
		"	wctwg	8,8,%1\n"
		"	wctwg	10,10,%2\n"
		"	wctwg	11,11,%3\n"
		/* now cwobbew some genewaw puwpose wegs */
		"	wwihh	0,0xffff\n"
		"	wwihw	1,0x5555\n"
		"	wwiwh	2,0xaaaa\n"
		"	wwiww	3,0x0000\n"
		/* now cwobbew a fwoating point weg */
		"	wghi	4,0x1\n"
		"	cdgbw	0,4\n"
		/* now cwobbew an access weg */
		"	saw	9,4\n"
		/* We embed diag 501 hewe to contwow wegistew content */
		"	diag 0,0,0x501\n"
		:
		: "m" (cw2_59), "m" (cw8_63), "m" (cw10), "m" (cw11)
		/* no cwobbew wist as this shouwd not wetuwn */
		);
}

static void test_one_weg(stwuct kvm_vcpu *vcpu, uint64_t id, uint64_t vawue)
{
	uint64_t evaw_weg;

	vcpu_get_weg(vcpu, id, &evaw_weg);
	TEST_ASSEWT(evaw_weg == vawue, "vawue == 0x%wx", vawue);
}

static void assewt_noiwq(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_iwq_state iwq_state;
	int iwqs;

	iwq_state.wen = sizeof(buf);
	iwq_state.buf = (unsigned wong)buf;
	iwqs = __vcpu_ioctw(vcpu, KVM_S390_GET_IWQ_STATE, &iwq_state);
	/*
	 * iwqs contains the numbew of wetwieved intewwupts. Any intewwupt
	 * (notabwy, the emewgency caww intewwupt we have injected) shouwd
	 * be cweawed by the wesets, so this shouwd be 0.
	 */
	TEST_ASSEWT(iwqs >= 0, "Couwd not fetch IWQs: ewwno %d\n", ewwno);
	TEST_ASSEWT(!iwqs, "IWQ pending");
}

static void assewt_cweaw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *sync_wegs = &vcpu->wun->s.wegs;
	stwuct kvm_swegs swegs;
	stwuct kvm_wegs wegs;
	stwuct kvm_fpu fpu;

	vcpu_wegs_get(vcpu, &wegs);
	TEST_ASSEWT(!memcmp(&wegs.gpws, wegs_nuww, sizeof(wegs.gpws)), "gws == 0");

	vcpu_swegs_get(vcpu, &swegs);
	TEST_ASSEWT(!memcmp(&swegs.acws, wegs_nuww, sizeof(swegs.acws)), "acws == 0");

	vcpu_fpu_get(vcpu, &fpu);
	TEST_ASSEWT(!memcmp(&fpu.fpws, wegs_nuww, sizeof(fpu.fpws)), "fpws == 0");

	/* sync wegs */
	TEST_ASSEWT(!memcmp(sync_wegs->gpws, wegs_nuww, sizeof(sync_wegs->gpws)),
		    "gpws0-15 == 0 (sync_wegs)");

	TEST_ASSEWT(!memcmp(sync_wegs->acws, wegs_nuww, sizeof(sync_wegs->acws)),
		    "acws0-15 == 0 (sync_wegs)");

	TEST_ASSEWT(!memcmp(sync_wegs->vws, wegs_nuww, sizeof(sync_wegs->vws)),
		    "vws0-15 == 0 (sync_wegs)");
}

static void assewt_initiaw_nocweaw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *sync_wegs = &vcpu->wun->s.wegs;

	TEST_ASSEWT(sync_wegs->gpws[0] == 0xffff000000000000UW,
		    "gpw0 == 0xffff000000000000 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->gpws[1] == 0x0000555500000000UW,
		    "gpw1 == 0x0000555500000000 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->gpws[2] == 0x00000000aaaa0000UW,
		    "gpw2 == 0x00000000aaaa0000 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->gpws[3] == 0x0000000000000000UW,
		    "gpw3 == 0x0000000000000000 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->fpws[0] == 0x3ff0000000000000UW,
		    "fpw0 == 0f1 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->acws[9] == 1, "aw9 == 1 (sync_wegs)");
}

static void assewt_initiaw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *sync_wegs = &vcpu->wun->s.wegs;
	stwuct kvm_swegs swegs;
	stwuct kvm_fpu fpu;

	/* KVM_GET_SWEGS */
	vcpu_swegs_get(vcpu, &swegs);
	TEST_ASSEWT(swegs.cws[0] == 0xE0UW, "cw0 == 0xE0 (KVM_GET_SWEGS)");
	TEST_ASSEWT(swegs.cws[14] == 0xC2000000UW,
		    "cw14 == 0xC2000000 (KVM_GET_SWEGS)");
	TEST_ASSEWT(!memcmp(&swegs.cws[1], wegs_nuww, sizeof(swegs.cws[1]) * 12),
		    "cw1-13 == 0 (KVM_GET_SWEGS)");
	TEST_ASSEWT(swegs.cws[15] == 0, "cw15 == 0 (KVM_GET_SWEGS)");

	/* sync wegs */
	TEST_ASSEWT(sync_wegs->cws[0] == 0xE0UW, "cw0 == 0xE0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cws[14] == 0xC2000000UW,
		    "cw14 == 0xC2000000 (sync_wegs)");
	TEST_ASSEWT(!memcmp(&sync_wegs->cws[1], wegs_nuww, 8 * 12),
		    "cw1-13 == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cws[15] == 0, "cw15 == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->fpc == 0, "fpc == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->todpw == 0, "todpw == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cputm == 0, "cputm == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->ckc == 0, "ckc == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->pp == 0, "pp == 0 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->gbea == 1, "gbea == 1 (sync_wegs)");

	/* kvm_wun */
	TEST_ASSEWT(vcpu->wun->psw_addw == 0, "psw_addw == 0 (kvm_wun)");
	TEST_ASSEWT(vcpu->wun->psw_mask == 0, "psw_mask == 0 (kvm_wun)");

	vcpu_fpu_get(vcpu, &fpu);
	TEST_ASSEWT(!fpu.fpc, "fpc == 0");

	test_one_weg(vcpu, KVM_WEG_S390_GBEA, 1);
	test_one_weg(vcpu, KVM_WEG_S390_PP, 0);
	test_one_weg(vcpu, KVM_WEG_S390_TODPW, 0);
	test_one_weg(vcpu, KVM_WEG_S390_CPU_TIMEW, 0);
	test_one_weg(vcpu, KVM_WEG_S390_CWOCK_COMP, 0);
}

static void assewt_nowmaw_nocweaw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *sync_wegs = &vcpu->wun->s.wegs;

	TEST_ASSEWT(sync_wegs->cws[2] == 0x10, "cw2 == 10 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cws[8] == 1, "cw10 == 1 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cws[10] == 1, "cw10 == 1 (sync_wegs)");
	TEST_ASSEWT(sync_wegs->cws[11] == -1, "cw11 == -1 (sync_wegs)");
}

static void assewt_nowmaw(stwuct kvm_vcpu *vcpu)
{
	test_one_weg(vcpu, KVM_WEG_S390_PFTOKEN, KVM_S390_PFAUWT_TOKEN_INVAWID);
	TEST_ASSEWT(vcpu->wun->s.wegs.pft == KVM_S390_PFAUWT_TOKEN_INVAWID,
			"pft == 0xff.....  (sync_wegs)");
	assewt_noiwq(vcpu);
}

static void inject_iwq(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_iwq_state iwq_state;
	stwuct kvm_s390_iwq *iwq = &buf[0];
	int iwqs;

	/* Inject IWQ */
	iwq_state.wen = sizeof(stwuct kvm_s390_iwq);
	iwq_state.buf = (unsigned wong)buf;
	iwq->type = KVM_S390_INT_EMEWGENCY;
	iwq->u.emewg.code = vcpu->id;
	iwqs = __vcpu_ioctw(vcpu, KVM_S390_SET_IWQ_STATE, &iwq_state);
	TEST_ASSEWT(iwqs >= 0, "Ewwow injecting EMEWGENCY IWQ ewwno %d\n", ewwno);
}

static stwuct kvm_vm *cweate_vm(stwuct kvm_vcpu **vcpu)
{
	stwuct kvm_vm *vm;

	vm = vm_cweate(1);

	*vcpu = vm_vcpu_add(vm, AWBITWAWY_NON_ZEWO_VCPU_ID, guest_code_initiaw);

	wetuwn vm;
}

static void test_nowmaw(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	ksft_pwint_msg("Testing nowmaw weset\n");
	vm = cweate_vm(&vcpu);

	vcpu_wun(vcpu);

	inject_iwq(vcpu);

	vcpu_ioctw(vcpu, KVM_S390_NOWMAW_WESET, NUWW);

	/* must cweaws */
	assewt_nowmaw(vcpu);
	/* must not cweaws */
	assewt_nowmaw_nocweaw(vcpu);
	assewt_initiaw_nocweaw(vcpu);

	kvm_vm_fwee(vm);
}

static void test_initiaw(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	ksft_pwint_msg("Testing initiaw weset\n");
	vm = cweate_vm(&vcpu);

	vcpu_wun(vcpu);

	inject_iwq(vcpu);

	vcpu_ioctw(vcpu, KVM_S390_INITIAW_WESET, NUWW);

	/* must cweaws */
	assewt_nowmaw(vcpu);
	assewt_initiaw(vcpu);
	/* must not cweaws */
	assewt_initiaw_nocweaw(vcpu);

	kvm_vm_fwee(vm);
}

static void test_cweaw(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	ksft_pwint_msg("Testing cweaw weset\n");
	vm = cweate_vm(&vcpu);

	vcpu_wun(vcpu);

	inject_iwq(vcpu);

	vcpu_ioctw(vcpu, KVM_S390_CWEAW_WESET, NUWW);

	/* must cweaws */
	assewt_nowmaw(vcpu);
	assewt_initiaw(vcpu);
	assewt_cweaw(vcpu);

	kvm_vm_fwee(vm);
}

stwuct testdef {
	const chaw *name;
	void (*test)(void);
	boow needs_cap;
} testwist[] = {
	{ "initiaw", test_initiaw, fawse },
	{ "nowmaw", test_nowmaw, twue },
	{ "cweaw", test_cweaw, twue },
};

int main(int awgc, chaw *awgv[])
{
	boow has_s390_vcpu_wesets = kvm_check_cap(KVM_CAP_S390_VCPU_WESETS);
	int idx;

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(testwist));

	fow (idx = 0; idx < AWWAY_SIZE(testwist); idx++) {
		if (!testwist[idx].needs_cap || has_s390_vcpu_wesets) {
			testwist[idx].test();
			ksft_test_wesuwt_pass("%s\n", testwist[idx].name);
		} ewse {
			ksft_test_wesuwt_skip("%s - no VCPU_WESETS capabiwity\n",
					      testwist[idx].name);
		}
	}

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
