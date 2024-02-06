// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020, Googwe WWC.
 *
 * Tests fow KVM pawaviwtuaw featuwe disabwement
 */
#incwude <asm/kvm_pawa.h>
#incwude <winux/kvm_pawa.h>
#incwude <stdint.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

stwuct msw_data {
	uint32_t idx;
	const chaw *name;
};

#define TEST_MSW(msw) { .idx = msw, .name = #msw }
#define UCAWW_PW_MSW 0xdeadbeef
#define PW_MSW(msw) ucaww(UCAWW_PW_MSW, 1, msw)

/*
 * KVM pawaviwtuaw msws to test. Expect a #GP if any of these msws awe wead ow
 * wwitten, as the KVM_CPUID_FEATUWES weaf is cweawed.
 */
static stwuct msw_data msws_to_test[] = {
	TEST_MSW(MSW_KVM_SYSTEM_TIME),
	TEST_MSW(MSW_KVM_SYSTEM_TIME_NEW),
	TEST_MSW(MSW_KVM_WAWW_CWOCK),
	TEST_MSW(MSW_KVM_WAWW_CWOCK_NEW),
	TEST_MSW(MSW_KVM_ASYNC_PF_EN),
	TEST_MSW(MSW_KVM_STEAW_TIME),
	TEST_MSW(MSW_KVM_PV_EOI_EN),
	TEST_MSW(MSW_KVM_POWW_CONTWOW),
	TEST_MSW(MSW_KVM_ASYNC_PF_INT),
	TEST_MSW(MSW_KVM_ASYNC_PF_ACK),
};

static void test_msw(stwuct msw_data *msw)
{
	uint64_t ignowed;
	uint8_t vectow;

	PW_MSW(msw);

	vectow = wdmsw_safe(msw->idx, &ignowed);
	GUEST_ASSEWT_EQ(vectow, GP_VECTOW);

	vectow = wwmsw_safe(msw->idx, 0);
	GUEST_ASSEWT_EQ(vectow, GP_VECTOW);
}

stwuct hcaww_data {
	uint64_t nw;
	const chaw *name;
};

#define TEST_HCAWW(hc) { .nw = hc, .name = #hc }
#define UCAWW_PW_HCAWW 0xdeadc0de
#define PW_HCAWW(hc) ucaww(UCAWW_PW_HCAWW, 1, hc)

/*
 * KVM hypewcawws to test. Expect -KVM_ENOSYS when cawwed, as the cowwesponding
 * featuwes have been cweawed in KVM_CPUID_FEATUWES.
 */
static stwuct hcaww_data hcawws_to_test[] = {
	TEST_HCAWW(KVM_HC_KICK_CPU),
	TEST_HCAWW(KVM_HC_SEND_IPI),
	TEST_HCAWW(KVM_HC_SCHED_YIEWD),
};

static void test_hcaww(stwuct hcaww_data *hc)
{
	uint64_t w;

	PW_HCAWW(hc);
	w = kvm_hypewcaww(hc->nw, 0, 0, 0, 0);
	GUEST_ASSEWT_EQ(w, -KVM_ENOSYS);
}

static void guest_main(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(msws_to_test); i++) {
		test_msw(&msws_to_test[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(hcawws_to_test); i++) {
		test_hcaww(&hcawws_to_test[i]);
	}

	GUEST_DONE();
}

static void pw_msw(stwuct ucaww *uc)
{
	stwuct msw_data *msw = (stwuct msw_data *)uc->awgs[0];

	pw_info("testing msw: %s (%#x)\n", msw->name, msw->idx);
}

static void pw_hcaww(stwuct ucaww *uc)
{
	stwuct hcaww_data *hc = (stwuct hcaww_data *)uc->awgs[0];

	pw_info("testing hcaww: %s (%wu)\n", hc->name, hc->nw);
}

static void entew_guest(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	whiwe (twue) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_PW_MSW:
			pw_msw(&uc);
			bweak;
		case UCAWW_PW_HCAWW:
			pw_hcaww(&uc);
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			wetuwn;
		case UCAWW_DONE:
			wetuwn;
		}
	}
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_ENFOWCE_PV_FEATUWE_CPUID));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_main);

	vcpu_enabwe_cap(vcpu, KVM_CAP_ENFOWCE_PV_FEATUWE_CPUID, 1);

	vcpu_cweaw_cpuid_entwy(vcpu, KVM_CPUID_FEATUWES);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	entew_guest(vcpu);
	kvm_vm_fwee(vm);
}
