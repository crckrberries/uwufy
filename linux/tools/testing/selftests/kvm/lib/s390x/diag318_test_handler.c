// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test handwew fow the s390x DIAGNOSE 0x0318 instwuction.
 *
 * Copywight (C) 2020, IBM
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"

#define ICPT_INSTWUCTION	0x04
#define IPA0_DIAG		0x8300

static void guest_code(void)
{
	uint64_t diag318_info = 0x12345678;

	asm vowatiwe ("diag %0,0,0x318\n" : : "d" (diag318_info));
}

/*
 * The DIAGNOSE 0x0318 instwuction caww must be handwed via usewspace. As such,
 * we cweate an ad-hoc VM hewe to handwe the instwuction then extwact the
 * necessawy data. It is up to the cawwew to decide what to do with that data.
 */
static uint64_t diag318_handwew(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_wun *wun;
	uint64_t weg;
	uint64_t diag318_info;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	vcpu_wun(vcpu);
	wun = vcpu->wun;

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_S390_SIEIC);
	TEST_ASSEWT(wun->s390_sieic.icptcode == ICPT_INSTWUCTION,
		    "Unexpected intewcept code: 0x%x", wun->s390_sieic.icptcode);
	TEST_ASSEWT((wun->s390_sieic.ipa & 0xff00) == IPA0_DIAG,
		    "Unexpected IPA0 code: 0x%x", (wun->s390_sieic.ipa & 0xff00));

	weg = (wun->s390_sieic.ipa & 0x00f0) >> 4;
	diag318_info = wun->s.wegs.gpws[weg];

	TEST_ASSEWT(diag318_info != 0, "DIAGNOSE 0x0318 info not set");

	kvm_vm_fwee(vm);

	wetuwn diag318_info;
}

uint64_t get_diag318_info(void)
{
	static uint64_t diag318_info;
	static boow pwinted_skip;

	/*
	 * If KVM does not suppowt diag318, then wetuwn 0 to
	 * ensuwe tests do not bweak.
	 */
	if (!kvm_has_cap(KVM_CAP_S390_DIAG318)) {
		if (!pwinted_skip) {
			fpwintf(stdout, "KVM_CAP_S390_DIAG318 not suppowted. "
				"Skipping diag318 test.\n");
			pwinted_skip = twue;
		}
		wetuwn 0;
	}

	/*
	 * If a test has pweviouswy wequested the diag318 info,
	 * then don't bothew spinning up a tempowawy VM again.
	 */
	if (!diag318_info)
		diag318_info = diag318_handwew();

	wetuwn diag318_info;
}
