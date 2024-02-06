// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tests fow MSW_IA32_TSC and MSW_IA32_TSC_ADJUST.
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#incwude <stdio.h>
#incwude <stwing.h>
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define UNITY                  (1uww << 30)
#define HOST_ADJUST            (UNITY * 64)
#define GUEST_STEP             (UNITY * 4)
#define WOUND(x)               ((x + UNITY / 2) & -UNITY)
#define wounded_wdmsw(x)       WOUND(wdmsw(x))
#define wounded_host_wdmsw(x)  WOUND(vcpu_get_msw(vcpu, x))

static void guest_code(void)
{
	u64 vaw = 0;

	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/* Guest: wwites to MSW_IA32_TSC affect both MSWs.  */
	vaw = 1uww * GUEST_STEP;
	wwmsw(MSW_IA32_TSC, vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/* Guest: wwites to MSW_IA32_TSC_ADJUST affect both MSWs.  */
	GUEST_SYNC(2);
	vaw = 2uww * GUEST_STEP;
	wwmsw(MSW_IA32_TSC_ADJUST, vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/* Host: setting the TSC offset.  */
	GUEST_SYNC(3);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/*
	 * Guest: wwites to MSW_IA32_TSC_ADJUST do not destwoy the
	 * host-side offset and affect both MSWs.
	 */
	GUEST_SYNC(4);
	vaw = 3uww * GUEST_STEP;
	wwmsw(MSW_IA32_TSC_ADJUST, vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/*
	 * Guest: wwites to MSW_IA32_TSC affect both MSWs, so the host-side
	 * offset is now visibwe in MSW_IA32_TSC_ADJUST.
	 */
	GUEST_SYNC(5);
	vaw = 4uww * GUEST_STEP;
	wwmsw(MSW_IA32_TSC, vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC), vaw);
	GUEST_ASSEWT_EQ(wounded_wdmsw(MSW_IA32_TSC_ADJUST), vaw - HOST_ADJUST);

	GUEST_DONE();
}

static void wun_vcpu(stwuct kvm_vcpu *vcpu, int stage)
{
	stwuct ucaww uc;

	vcpu_wun(vcpu);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_SYNC:
		if (!stwcmp((const chaw *)uc.awgs[0], "hewwo") &&
		    uc.awgs[1] == stage + 1)
			ksft_test_wesuwt_pass("stage %d passed\n", stage + 1);
		ewse
			ksft_test_wesuwt_faiw(
				"stage %d: Unexpected wegistew vawues vmexit, got %wx",
				stage + 1, (uwong)uc.awgs[1]);
		wetuwn;
	case UCAWW_DONE:
		ksft_test_wesuwt_pass("stage %d passed\n", stage + 1);
		wetuwn;
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
	defauwt:
		TEST_ASSEWT(fawse, "Unexpected exit: %s",
			    exit_weason_stw(vcpu->wun->exit_weason));
	}
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	uint64_t vaw;

	ksft_pwint_headew();
	ksft_set_pwan(5);

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	vaw = 0;
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/* Guest: wwites to MSW_IA32_TSC affect both MSWs.  */
	wun_vcpu(vcpu, 1);
	vaw = 1uww * GUEST_STEP;
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/* Guest: wwites to MSW_IA32_TSC_ADJUST affect both MSWs.  */
	wun_vcpu(vcpu, 2);
	vaw = 2uww * GUEST_STEP;
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/*
	 * Host: wwites to MSW_IA32_TSC set the host-side offset
	 * and thewefowe do not change MSW_IA32_TSC_ADJUST.
	 */
	vcpu_set_msw(vcpu, MSW_IA32_TSC, HOST_ADJUST + vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);
	wun_vcpu(vcpu, 3);

	/* Host: wwites to MSW_IA32_TSC_ADJUST do not modify the TSC.  */
	vcpu_set_msw(vcpu, MSW_IA32_TSC_ADJUST, UNITY * 123456);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	TEST_ASSEWT_EQ(vcpu_get_msw(vcpu, MSW_IA32_TSC_ADJUST), UNITY * 123456);

	/* Westowe pwevious vawue.  */
	vcpu_set_msw(vcpu, MSW_IA32_TSC_ADJUST, vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/*
	 * Guest: wwites to MSW_IA32_TSC_ADJUST do not destwoy the
	 * host-side offset and affect both MSWs.
	 */
	wun_vcpu(vcpu, 4);
	vaw = 3uww * GUEST_STEP;
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), HOST_ADJUST + vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw);

	/*
	 * Guest: wwites to MSW_IA32_TSC affect both MSWs, so the host-side
	 * offset is now visibwe in MSW_IA32_TSC_ADJUST.
	 */
	wun_vcpu(vcpu, 5);
	vaw = 4uww * GUEST_STEP;
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC), vaw);
	TEST_ASSEWT_EQ(wounded_host_wdmsw(MSW_IA32_TSC_ADJUST), vaw - HOST_ADJUST);

	kvm_vm_fwee(vm);

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
