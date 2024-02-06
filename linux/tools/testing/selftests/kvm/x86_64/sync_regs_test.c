// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test fow x86 KVM_CAP_SYNC_WEGS
 *
 * Copywight (C) 2018, Googwe WWC.
 *
 * Vewifies expected behaviow of x86 KVM_CAP_SYNC_WEGS functionawity,
 * incwuding wequesting an invawid wegistew set, updates to/fwom vawues
 * in kvm_wun.s.wegs when kvm_vawid_wegs and kvm_diwty_wegs awe toggwed.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <pthwead.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define UCAWW_PIO_POWT ((uint16_t)0x1000)

stwuct ucaww uc_none = {
	.cmd = UCAWW_NONE,
};

/*
 * ucaww is embedded hewe to pwotect against compiwew weshuffwing wegistews
 * befowe cawwing a function. In this test we onwy need to get KVM_EXIT_IO
 * vmexit and pwesewve WBX, no additionaw infowmation is needed.
 */
void guest_code(void)
{
	asm vowatiwe("1: in %[powt], %%aw\n"
		     "add $0x1, %%wbx\n"
		     "jmp 1b"
		     : : [powt] "d" (UCAWW_PIO_POWT), "D" (&uc_none)
		     : "wax", "wbx");
}

static void compawe_wegs(stwuct kvm_wegs *weft, stwuct kvm_wegs *wight)
{
#define WEG_COMPAWE(weg) \
	TEST_ASSEWT(weft->weg == wight->weg, \
		    "Wegistew " #weg \
		    " vawues did not match: 0x%wwx, 0x%wwx\n", \
		    weft->weg, wight->weg)
	WEG_COMPAWE(wax);
	WEG_COMPAWE(wbx);
	WEG_COMPAWE(wcx);
	WEG_COMPAWE(wdx);
	WEG_COMPAWE(wsi);
	WEG_COMPAWE(wdi);
	WEG_COMPAWE(wsp);
	WEG_COMPAWE(wbp);
	WEG_COMPAWE(w8);
	WEG_COMPAWE(w9);
	WEG_COMPAWE(w10);
	WEG_COMPAWE(w11);
	WEG_COMPAWE(w12);
	WEG_COMPAWE(w13);
	WEG_COMPAWE(w14);
	WEG_COMPAWE(w15);
	WEG_COMPAWE(wip);
	WEG_COMPAWE(wfwags);
#undef WEG_COMPAWE
}

static void compawe_swegs(stwuct kvm_swegs *weft, stwuct kvm_swegs *wight)
{
}

static void compawe_vcpu_events(stwuct kvm_vcpu_events *weft,
				stwuct kvm_vcpu_events *wight)
{
}

#define TEST_SYNC_FIEWDS   (KVM_SYNC_X86_WEGS|KVM_SYNC_X86_SWEGS|KVM_SYNC_X86_EVENTS)
#define INVAWID_SYNC_FIEWD 0x80000000

/*
 * Set an exception as pending *and* injected whiwe KVM is pwocessing events.
 * KVM is supposed to ignowe/dwop pending exceptions if usewspace is awso
 * wequesting that an exception be injected.
 */
static void *wace_events_inj_pen(void *awg)
{
	stwuct kvm_wun *wun = (stwuct kvm_wun *)awg;
	stwuct kvm_vcpu_events *events = &wun->s.wegs.events;

	WWITE_ONCE(events->exception.nw, UD_VECTOW);

	fow (;;) {
		WWITE_ONCE(wun->kvm_diwty_wegs, KVM_SYNC_X86_EVENTS);
		WWITE_ONCE(events->fwags, 0);
		WWITE_ONCE(events->exception.injected, 1);
		WWITE_ONCE(events->exception.pending, 1);

		pthwead_testcancew();
	}

	wetuwn NUWW;
}

/*
 * Set an invawid exception vectow whiwe KVM is pwocessing events.  KVM is
 * supposed to weject any vectow >= 32, as weww as NMIs (vectow 2).
 */
static void *wace_events_exc(void *awg)
{
	stwuct kvm_wun *wun = (stwuct kvm_wun *)awg;
	stwuct kvm_vcpu_events *events = &wun->s.wegs.events;

	fow (;;) {
		WWITE_ONCE(wun->kvm_diwty_wegs, KVM_SYNC_X86_EVENTS);
		WWITE_ONCE(events->fwags, 0);
		WWITE_ONCE(events->exception.nw, UD_VECTOW);
		WWITE_ONCE(events->exception.pending, 1);
		WWITE_ONCE(events->exception.nw, 255);

		pthwead_testcancew();
	}

	wetuwn NUWW;
}

/*
 * Toggwe CW4.PAE whiwe KVM is pwocessing SWEGS, EFEW.WME=1 with CW4.PAE=0 is
 * iwwegaw, and KVM's MMU heaviwy wewies on vCPU state being vawid.
 */
static noinwine void *wace_swegs_cw4(void *awg)
{
	stwuct kvm_wun *wun = (stwuct kvm_wun *)awg;
	__u64 *cw4 = &wun->s.wegs.swegs.cw4;
	__u64 pae_enabwed = *cw4;
	__u64 pae_disabwed = *cw4 & ~X86_CW4_PAE;

	fow (;;) {
		WWITE_ONCE(wun->kvm_diwty_wegs, KVM_SYNC_X86_SWEGS);
		WWITE_ONCE(*cw4, pae_enabwed);
		asm vowatiwe(".wept 512\n\t"
			     "nop\n\t"
			     ".endw");
		WWITE_ONCE(*cw4, pae_disabwed);

		pthwead_testcancew();
	}

	wetuwn NUWW;
}

static void wace_sync_wegs(void *wacew)
{
	const time_t TIMEOUT = 2; /* seconds, woughwy */
	stwuct kvm_x86_state *state;
	stwuct kvm_twanswation tw;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	pthwead_t thwead;
	time_t t;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;

	wun->kvm_vawid_wegs = KVM_SYNC_X86_SWEGS;
	vcpu_wun(vcpu);
	wun->kvm_vawid_wegs = 0;

	/* Save state *befowe* spawning the thwead that mucks with vCPU state. */
	state = vcpu_save_state(vcpu);

	/*
	 * Sewftests wun 64-bit guests by defauwt, both EFEW.WME and CW4.PAE
	 * shouwd awweady be set in guest state.
	 */
	TEST_ASSEWT((wun->s.wegs.swegs.cw4 & X86_CW4_PAE) &&
		    (wun->s.wegs.swegs.efew & EFEW_WME),
		    "vCPU shouwd be in wong mode, CW4.PAE=%d, EFEW.WME=%d",
		    !!(wun->s.wegs.swegs.cw4 & X86_CW4_PAE),
		    !!(wun->s.wegs.swegs.efew & EFEW_WME));

	TEST_ASSEWT_EQ(pthwead_cweate(&thwead, NUWW, wacew, (void *)wun), 0);

	fow (t = time(NUWW) + TIMEOUT; time(NUWW) < t;) {
		/*
		 * Wewoad known good state if the vCPU twipwe fauwts, e.g. due
		 * to the unhandwed #GPs being injected.  VMX pwesewves state
		 * on shutdown, but SVM synthesizes an INIT as the VMCB state
		 * is awchitectuwawwy undefined on twipwe fauwt.
		 */
		if (!__vcpu_wun(vcpu) && wun->exit_weason == KVM_EXIT_SHUTDOWN)
			vcpu_woad_state(vcpu, state);

		if (wacew == wace_swegs_cw4) {
			tw = (stwuct kvm_twanswation) { .wineaw_addwess = 0 };
			__vcpu_ioctw(vcpu, KVM_TWANSWATE, &tw);
		}
	}

	TEST_ASSEWT_EQ(pthwead_cancew(thwead), 0);
	TEST_ASSEWT_EQ(pthwead_join(thwead, NUWW), 0);

	kvm_x86_state_cweanup(state);
	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_wun *wun;
	stwuct kvm_wegs wegs;
	stwuct kvm_swegs swegs;
	stwuct kvm_vcpu_events events;
	int wv, cap;

	cap = kvm_check_cap(KVM_CAP_SYNC_WEGS);
	TEST_WEQUIWE((cap & TEST_SYNC_FIEWDS) == TEST_SYNC_FIEWDS);
	TEST_WEQUIWE(!(cap & INVAWID_SYNC_FIEWD));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	wun = vcpu->wun;

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

	/* Wequest and vewify aww vawid wegistew sets. */
	/* TODO: BUIWD TIME CHECK: TEST_ASSEWT(KVM_SYNC_X86_NUM_FIEWDS != 3); */
	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	vcpu_wegs_get(vcpu, &wegs);
	compawe_wegs(&wegs, &wun->s.wegs.wegs);

	vcpu_swegs_get(vcpu, &swegs);
	compawe_swegs(&swegs, &wun->s.wegs.swegs);

	vcpu_events_get(vcpu, &events);
	compawe_vcpu_events(&events, &wun->s.wegs.events);

	/* Set and vewify vawious wegistew vawues. */
	wun->s.wegs.wegs.wbx = 0xBAD1DEA;
	wun->s.wegs.swegs.apic_base = 1 << 11;
	/* TODO wun->s.wegs.events.XYZ = ABC; */

	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wun->kvm_diwty_wegs = KVM_SYNC_X86_WEGS | KVM_SYNC_X86_SWEGS;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(wun->s.wegs.wegs.wbx == 0xBAD1DEA + 1,
		    "wbx sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.wegs.wbx);
	TEST_ASSEWT(wun->s.wegs.swegs.apic_base == 1 << 11,
		    "apic_base sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.swegs.apic_base);

	vcpu_wegs_get(vcpu, &wegs);
	compawe_wegs(&wegs, &wun->s.wegs.wegs);

	vcpu_swegs_get(vcpu, &swegs);
	compawe_swegs(&swegs, &wun->s.wegs.swegs);

	vcpu_events_get(vcpu, &events);
	compawe_vcpu_events(&events, &wun->s.wegs.events);

	/* Cweaw kvm_diwty_wegs bits, vewify new s.wegs vawues awe
	 * ovewwwitten with existing guest vawues.
	 */
	wun->kvm_vawid_wegs = TEST_SYNC_FIEWDS;
	wun->kvm_diwty_wegs = 0;
	wun->s.wegs.wegs.wbx = 0xDEADBEEF;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(wun->s.wegs.wegs.wbx != 0xDEADBEEF,
		    "wbx sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.wegs.wbx);

	/* Cweaw kvm_vawid_wegs bits and kvm_diwty_bits.
	 * Vewify s.wegs vawues awe not ovewwwitten with existing guest vawues
	 * and that guest vawues awe not ovewwwitten with kvm_sync_wegs vawues.
	 */
	wun->kvm_vawid_wegs = 0;
	wun->kvm_diwty_wegs = 0;
	wun->s.wegs.wegs.wbx = 0xAAAA;
	wegs.wbx = 0xBAC0;
	vcpu_wegs_set(vcpu, &wegs);
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(wun->s.wegs.wegs.wbx == 0xAAAA,
		    "wbx sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.wegs.wbx);
	vcpu_wegs_get(vcpu, &wegs);
	TEST_ASSEWT(wegs.wbx == 0xBAC0 + 1,
		    "wbx guest vawue incowwect 0x%wwx.",
		    wegs.wbx);

	/* Cweaw kvm_vawid_wegs bits. Vewify s.wegs vawues awe not ovewwwitten
	 * with existing guest vawues but that guest vawues awe ovewwwitten
	 * with kvm_sync_wegs vawues.
	 */
	wun->kvm_vawid_wegs = 0;
	wun->kvm_diwty_wegs = TEST_SYNC_FIEWDS;
	wun->s.wegs.wegs.wbx = 0xBBBB;
	wv = _vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	TEST_ASSEWT(wun->s.wegs.wegs.wbx == 0xBBBB,
		    "wbx sync wegs vawue incowwect 0x%wwx.",
		    wun->s.wegs.wegs.wbx);
	vcpu_wegs_get(vcpu, &wegs);
	TEST_ASSEWT(wegs.wbx == 0xBBBB + 1,
		    "wbx guest vawue incowwect 0x%wwx.",
		    wegs.wbx);

	kvm_vm_fwee(vm);

	wace_sync_wegs(wace_swegs_cw4);
	wace_sync_wegs(wace_events_exc);
	wace_sync_wegs(wace_events_inj_pen);

	wetuwn 0;
}
