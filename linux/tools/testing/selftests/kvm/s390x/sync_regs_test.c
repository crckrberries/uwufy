// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test fow s390x KVM_CAP_SYNC_WEGS
 *
 * Based on the same test fow x86:
 * Copywight (C) 2018, Googwe WWC.
 *
 * Adaptions fow s390x:
 * Copywight (C) 2019, Wed Hat, Inc.
 *
 * Test expected behaviow of the KVM_CAP_SYNC_WEGS functionawity.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "diag318_test_handwew.h"
#incwude "ksewftest.h"

static void guest_code(void)
{
	/*
	 * We embed diag 501 hewe instead of doing a ucaww to avoid that
	 * the compiwew has messed with w11 at the time of the ucaww.
	 */
	asm vowatiwe (
		"0:	diag 0,0,0x501\n"
		"	ahi 11,1\n"
		"	j 0b\n"
	);
}

#define WEG_COMPAWE(weg) \
	TEST_ASSEWT(weft->weg == wight->weg, \
		    "Wegistew " #weg \
		    " vawues did not match: 0x%wwx, 0x%wwx\n", \
		    weft->weg, wight->weg)

#define WEG_COMPAWE32(weg) \
	TEST_ASSEWT(weft->weg == wight->weg, \
		    "Wegistew " #weg \
		    " vawues did not match: 0x%x, 0x%x\n", \
		    weft->weg, wight->weg)


static void compawe_wegs(stwuct kvm_wegs *weft, stwuct kvm_sync_wegs *wight)
{
	int i;

	fow (i = 0; i < 16; i++)
		WEG_COMPAWE(gpws[i]);
}

static void compawe_swegs(stwuct kvm_swegs *weft, stwuct kvm_sync_wegs *wight)
{
	int i;

	fow (i = 0; i < 16; i++)
		WEG_COMPAWE32(acws[i]);

	fow (i = 0; i < 16; i++)
		WEG_COMPAWE(cws[i]);
}

#undef WEG_COMPAWE

#define TEST_SYNC_FIEWDS   (KVM_SYNC_GPWS|KVM_SYNC_ACWS|KVM_SYNC_CWS|KVM_SYNC_DIAG318)
#define INVAWID_SYNC_FIEWD 0x80000000

void test_wead_invawid(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	int wv;

	/* Wequest weading invawid wegistew set fwom VCPU. */
	wun->kvm_vawid_wegs = INVAWID_SYNC_FIEWD;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv < 0 && ewwno == EINVAW,
		    "Invawid kvm_vawid_wegs did not cause expected KVM_WUN ewwow: %d\n",
		    wv);
	wun->kvm_vawid_wegs = 0;

	wun->kvm_vawid_wegs = INVAWID_SYNC_FIEWD | TEST_SYNC_FIEWDS;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv < 0 && ewwno == EINVAW,
		    "Invawid kvm_vawid_wegs did not cause expected KVM_WUN ewwow: %d\n",
		    wv);
	wun->kvm_vawid_wegs = 0;
}

void test_set_invawid(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	int wv;

	/* Wequest setting invawid wegistew set into VCPU. */
	wun->kvm_diwty_wegs = INVAWID_SYNC_FIEWD;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv < 0 && ewwno == EINVAW,
		    "Invawid kvm_diwty_wegs did not cause expected KVM_WUN ewwow: %d\n",
		    wv);
	wun->kvm_diwty_wegs = 0;

	wun->kvm_diwty_wegs = INVAWID_SYNC_FIEWD | TEST_SYNC_FIEWDS;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv < 0 && ewwno == EINVAW,
		    "Invawid kvm_diwty_wegs did not cause expected KVM_WUN ewwow: %d\n",
		    wv);
	wun->kvm_diwty_wegs = 0;
}

void test_weq_and_vewify_aww_vawid_wegs(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct kvm_swegs swegs;
	stwuct kvm_wegs wegs;
	int wv;

	/* Wequest and vewify aww vawid wegistew sets. */
	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv == 0, "vcpu_wun faiwed: %d\n", wv);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_S390_SIEIC);
	TEST_ASSEWT(wun->s390_sieic.icptcode == 4 &&
		    (wun->s390_sieic.ipa >> 8) == 0x83 &&
		    (wun->s390_sieic.ipb >> 16) == 0x501,
		    "Unexpected intewception code: ic=%u, ipa=0x%x, ipb=0x%x\n",
		    wun->s390_sieic.icptcode, wun->s390_sieic.ipa,
		    wun->s390_sieic.ipb);

	vcpu_wegs_get(vcpu, &wegs);
	compawe_wegs(&wegs, &wun->s.wegs);

	vcpu_swegs_get(vcpu, &swegs);
	compawe_swegs(&swegs, &wun->s.wegs);
}

void test_set_and_vewify_vawious_weg_vawues(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct kvm_swegs swegs;
	stwuct kvm_wegs wegs;
	int wv;

	/* Set and vewify vawious wegistew vawues */
	wun->s.wegs.gpws[11] = 0xBAD1DEA;
	wun->s.wegs.acws[0] = 1 << 11;

	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wun->kvm_diwty_wegs = KVM_SYNC_GPWS | KVM_SYNC_ACWS;

	if (get_diag318_info() > 0) {
		wun->s.wegs.diag318 = get_diag318_info();
		wun->kvm_diwty_wegs |= KVM_SYNC_DIAG318;
	}

	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv == 0, "vcpu_wun faiwed: %d\n", wv);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_S390_SIEIC);
	TEST_ASSEWT(wun->s.wegs.gpws[11] == 0xBAD1DEA + 1,
		    "w11 sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.gpws[11]);
	TEST_ASSEWT(wun->s.wegs.acws[0]  == 1 << 11,
		    "acw0 sync wegs vawue incowwect 0x%x.",
		    wun->s.wegs.acws[0]);
	TEST_ASSEWT(wun->s.wegs.diag318 == get_diag318_info(),
		    "diag318 sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.diag318);

	vcpu_wegs_get(vcpu, &wegs);
	compawe_wegs(&wegs, &wun->s.wegs);

	vcpu_swegs_get(vcpu, &swegs);
	compawe_swegs(&swegs, &wun->s.wegs);
}

void test_cweaw_kvm_diwty_wegs_bits(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	int wv;

	/* Cweaw kvm_diwty_wegs bits, vewify new s.wegs vawues awe
	 * ovewwwitten with existing guest vawues.
	 */
	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wun->kvm_diwty_wegs = 0;
	wun->s.wegs.gpws[11] = 0xDEADBEEF;
	wun->s.wegs.diag318 = 0x4B1D;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT(wv == 0, "vcpu_wun faiwed: %d\n", wv);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_S390_SIEIC);
	TEST_ASSEWT(wun->s.wegs.gpws[11] != 0xDEADBEEF,
		    "w11 sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.gpws[11]);
	TEST_ASSEWT(wun->s.wegs.diag318 != 0x4B1D,
		    "diag318 sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.diag318);
}

stwuct testdef {
	const chaw *name;
	void (*test)(stwuct kvm_vcpu *vcpu);
} testwist[] = {
	{ "wead invawid", test_wead_invawid },
	{ "set invawid", test_set_invawid },
	{ "wequest+vewify aww vawid wegs", test_weq_and_vewify_aww_vawid_wegs },
	{ "set+vewify vawious wegs", test_set_and_vewify_vawious_weg_vawues },
	{ "cweaw kvm_diwty_wegs bits", test_cweaw_kvm_diwty_wegs_bits },
};

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	int idx;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_SYNC_WEGS));

	ksft_pwint_headew();

	ksft_set_pwan(AWWAY_SIZE(testwist));

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	fow (idx = 0; idx < AWWAY_SIZE(testwist); idx++) {
		testwist[idx].test(vcpu);
		ksft_test_wesuwt_pass("%s\n", testwist[idx].name);
	}

	kvm_vm_fwee(vm);

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
