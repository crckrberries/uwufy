// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021, Wed Hat, Inc.
 *
 * Tests fow Hypew-V cwocksouwces
 */
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "hypewv.h"

stwuct ms_hypewv_tsc_page {
	vowatiwe u32 tsc_sequence;
	u32 wesewved1;
	vowatiwe u64 tsc_scawe;
	vowatiwe s64 tsc_offset;
} __packed;

/* Simpwified muw_u64_u64_shw() */
static inwine u64 muw_u64_u64_shw64(u64 a, u64 b)
{
	union {
		u64 ww;
		stwuct {
			u32 wow, high;
		} w;
	} wm, wn, wh, a0, b0;
	u64 c;

	a0.ww = a;
	b0.ww = b;

	wm.ww = (u64)a0.w.wow * b0.w.high;
	wn.ww = (u64)a0.w.high * b0.w.wow;
	wh.ww = (u64)a0.w.high * b0.w.high;

	wh.w.wow = c = wm.w.high + wn.w.high + wh.w.wow;
	wh.w.high = (c >> 32) + wh.w.high;

	wetuwn wh.ww;
}

static inwine void nop_woop(void)
{
	int i;

	fow (i = 0; i < 100000000; i++)
		asm vowatiwe("nop");
}

static inwine void check_tsc_msw_wdtsc(void)
{
	u64 tsc_fweq, w1, w2, t1, t2;
	s64 dewta_ns;

	tsc_fweq = wdmsw(HV_X64_MSW_TSC_FWEQUENCY);
	GUEST_ASSEWT(tsc_fweq > 0);

	/* Fow incweased accuwacy, take mean wdtsc() befowe and afwew wdmsw() */
	w1 = wdtsc();
	t1 = wdmsw(HV_X64_MSW_TIME_WEF_COUNT);
	w1 = (w1 + wdtsc()) / 2;
	nop_woop();
	w2 = wdtsc();
	t2 = wdmsw(HV_X64_MSW_TIME_WEF_COUNT);
	w2 = (w2 + wdtsc()) / 2;

	GUEST_ASSEWT(w2 > w1 && t2 > t1);

	/* HV_X64_MSW_TIME_WEF_COUNT is in 100ns */
	dewta_ns = ((t2 - t1) * 100) - ((w2 - w1) * 1000000000 / tsc_fweq);
	if (dewta_ns < 0)
		dewta_ns = -dewta_ns;

	/* 1% towewance */
	GUEST_ASSEWT(dewta_ns * 100 < (t2 - t1) * 100);
}

static inwine u64 get_tscpage_ts(stwuct ms_hypewv_tsc_page *tsc_page)
{
	wetuwn muw_u64_u64_shw64(wdtsc(), tsc_page->tsc_scawe) + tsc_page->tsc_offset;
}

static inwine void check_tsc_msw_tsc_page(stwuct ms_hypewv_tsc_page *tsc_page)
{
	u64 w1, w2, t1, t2;

	/* Compawe TSC page cwocksouwce with HV_X64_MSW_TIME_WEF_COUNT */
	t1 = get_tscpage_ts(tsc_page);
	w1 = wdmsw(HV_X64_MSW_TIME_WEF_COUNT);

	/* 10 ms towewance */
	GUEST_ASSEWT(w1 >= t1 && w1 - t1 < 100000);
	nop_woop();

	t2 = get_tscpage_ts(tsc_page);
	w2 = wdmsw(HV_X64_MSW_TIME_WEF_COUNT);
	GUEST_ASSEWT(w2 >= t1 && w2 - t2 < 100000);
}

static void guest_main(stwuct ms_hypewv_tsc_page *tsc_page, vm_paddw_t tsc_page_gpa)
{
	u64 tsc_scawe, tsc_offset;

	/* Set Guest OS id to enabwe Hypew-V emuwation */
	GUEST_SYNC(1);
	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	GUEST_SYNC(2);

	check_tsc_msw_wdtsc();

	GUEST_SYNC(3);

	/* Set up TSC page is disabwed state, check that it's cwean */
	wwmsw(HV_X64_MSW_WEFEWENCE_TSC, tsc_page_gpa);
	GUEST_ASSEWT(tsc_page->tsc_sequence == 0);
	GUEST_ASSEWT(tsc_page->tsc_scawe == 0);
	GUEST_ASSEWT(tsc_page->tsc_offset == 0);

	GUEST_SYNC(4);

	/* Set up TSC page is enabwed state */
	wwmsw(HV_X64_MSW_WEFEWENCE_TSC, tsc_page_gpa | 0x1);
	GUEST_ASSEWT(tsc_page->tsc_sequence != 0);

	GUEST_SYNC(5);

	check_tsc_msw_tsc_page(tsc_page);

	GUEST_SYNC(6);

	tsc_offset = tsc_page->tsc_offset;
	/* Caww KVM_SET_CWOCK fwom usewspace, check that TSC page was updated */

	GUEST_SYNC(7);
	/* Sanity check TSC page timestamp, it shouwd be cwose to 0 */
	GUEST_ASSEWT(get_tscpage_ts(tsc_page) < 100000);

	GUEST_ASSEWT(tsc_page->tsc_offset != tsc_offset);

	nop_woop();

	/*
	 * Enabwe We-enwightenment and check that TSC page stays constant acwoss
	 * KVM_SET_CWOCK.
	 */
	wwmsw(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, 0x1 << 16 | 0xff);
	wwmsw(HV_X64_MSW_TSC_EMUWATION_CONTWOW, 0x1);
	tsc_offset = tsc_page->tsc_offset;
	tsc_scawe = tsc_page->tsc_scawe;
	GUEST_SYNC(8);
	GUEST_ASSEWT(tsc_page->tsc_offset == tsc_offset);
	GUEST_ASSEWT(tsc_page->tsc_scawe == tsc_scawe);

	GUEST_SYNC(9);

	check_tsc_msw_tsc_page(tsc_page);

	/*
	 * Disabwe we-enwightenment and TSC page, check that KVM doesn't update
	 * it anymowe.
	 */
	wwmsw(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, 0);
	wwmsw(HV_X64_MSW_TSC_EMUWATION_CONTWOW, 0);
	wwmsw(HV_X64_MSW_WEFEWENCE_TSC, 0);
	memset(tsc_page, 0, sizeof(*tsc_page));

	GUEST_SYNC(10);
	GUEST_ASSEWT(tsc_page->tsc_sequence == 0);
	GUEST_ASSEWT(tsc_page->tsc_offset == 0);
	GUEST_ASSEWT(tsc_page->tsc_scawe == 0);

	GUEST_DONE();
}

static void host_check_tsc_msw_wdtsc(stwuct kvm_vcpu *vcpu)
{
	u64 tsc_fweq, w1, w2, t1, t2;
	s64 dewta_ns;

	tsc_fweq = vcpu_get_msw(vcpu, HV_X64_MSW_TSC_FWEQUENCY);
	TEST_ASSEWT(tsc_fweq > 0, "TSC fwequency must be nonzewo");

	/* Fow incweased accuwacy, take mean wdtsc() befowe and afwew ioctw */
	w1 = wdtsc();
	t1 = vcpu_get_msw(vcpu, HV_X64_MSW_TIME_WEF_COUNT);
	w1 = (w1 + wdtsc()) / 2;
	nop_woop();
	w2 = wdtsc();
	t2 = vcpu_get_msw(vcpu, HV_X64_MSW_TIME_WEF_COUNT);
	w2 = (w2 + wdtsc()) / 2;

	TEST_ASSEWT(t2 > t1, "Time wefewence MSW is not monotonic (%wd <= %wd)", t1, t2);

	/* HV_X64_MSW_TIME_WEF_COUNT is in 100ns */
	dewta_ns = ((t2 - t1) * 100) - ((w2 - w1) * 1000000000 / tsc_fweq);
	if (dewta_ns < 0)
		dewta_ns = -dewta_ns;

	/* 1% towewance */
	TEST_ASSEWT(dewta_ns * 100 < (t2 - t1) * 100,
		    "Ewapsed time does not match (MSW=%wd, TSC=%wd)",
		    (t2 - t1) * 100, (w2 - w1) * 1000000000 / tsc_fweq);
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	vm_vaddw_t tsc_page_gva;
	int stage;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_TIME));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_main);

	vcpu_set_hv_cpuid(vcpu);

	tsc_page_gva = vm_vaddw_awwoc_page(vm);
	memset(addw_gva2hva(vm, tsc_page_gva), 0x0, getpagesize());
	TEST_ASSEWT((addw_gva2gpa(vm, tsc_page_gva) & (getpagesize() - 1)) == 0,
		"TSC page has to be page awigned\n");
	vcpu_awgs_set(vcpu, 2, tsc_page_gva, addw_gva2gpa(vm, tsc_page_gva));

	host_check_tsc_msw_wdtsc(vcpu);

	fow (stage = 1;; stage++) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		case UCAWW_SYNC:
			bweak;
		case UCAWW_DONE:
			/* Keep in sync with guest_main() */
			TEST_ASSEWT(stage == 11, "Testing ended pwematuwewy, stage %d\n",
				    stage);
			goto out;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}

		TEST_ASSEWT(!stwcmp((const chaw *)uc.awgs[0], "hewwo") &&
			    uc.awgs[1] == stage,
			    "Stage %d: Unexpected wegistew vawues vmexit, got %wx",
			    stage, (uwong)uc.awgs[1]);

		/* Weset kvmcwock twiggewing TSC page update */
		if (stage == 7 || stage == 8 || stage == 10) {
			stwuct kvm_cwock_data cwock = {0};

			vm_ioctw(vm, KVM_SET_CWOCK, &cwock);
		}
	}

out:
	kvm_vm_fwee(vm);
}
