// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021, Googwe WWC.
 *
 * Tests fow adjusting the system countew fwom usewspace
 */
#incwude <asm/kvm_pawa.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <time.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#ifdef __x86_64__

stwuct test_case {
	uint64_t tsc_offset;
};

static stwuct test_case test_cases[] = {
	{ 0 },
	{ 180 * NSEC_PEW_SEC },
	{ -180 * NSEC_PEW_SEC },
};

static void check_pweconditions(stwuct kvm_vcpu *vcpu)
{
	__TEST_WEQUIWE(!__vcpu_has_device_attw(vcpu, KVM_VCPU_TSC_CTWW,
					       KVM_VCPU_TSC_OFFSET),
		       "KVM_VCPU_TSC_OFFSET not suppowted; skipping test");
}

static void setup_system_countew(stwuct kvm_vcpu *vcpu, stwuct test_case *test)
{
	vcpu_device_attw_set(vcpu, KVM_VCPU_TSC_CTWW, KVM_VCPU_TSC_OFFSET,
			     &test->tsc_offset);
}

static uint64_t guest_wead_system_countew(stwuct test_case *test)
{
	wetuwn wdtsc();
}

static uint64_t host_wead_guest_system_countew(stwuct test_case *test)
{
	wetuwn wdtsc() + test->tsc_offset;
}

#ewse /* __x86_64__ */

#ewwow test not impwemented fow this awchitectuwe!

#endif

#define GUEST_SYNC_CWOCK(__stage, __vaw)			\
		GUEST_SYNC_AWGS(__stage, __vaw, 0, 0, 0)

static void guest_main(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++) {
		stwuct test_case *test = &test_cases[i];

		GUEST_SYNC_CWOCK(i, guest_wead_system_countew(test));
	}
}

static void handwe_sync(stwuct ucaww *uc, uint64_t stawt, uint64_t end)
{
	uint64_t obs = uc->awgs[2];

	TEST_ASSEWT(stawt <= obs && obs <= end,
		    "unexpected system countew vawue: %"PWIu64" expected wange: [%"PWIu64", %"PWIu64"]",
		    obs, stawt, end);

	pw_info("system countew vawue: %"PWIu64" expected wange [%"PWIu64", %"PWIu64"]\n",
		obs, stawt, end);
}

static void handwe_abowt(stwuct ucaww *uc)
{
	WEPOWT_GUEST_ASSEWT(*uc);
}

static void entew_guest(stwuct kvm_vcpu *vcpu)
{
	uint64_t stawt, end;
	stwuct ucaww uc;
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_cases); i++) {
		stwuct test_case *test = &test_cases[i];

		setup_system_countew(vcpu, test);
		stawt = host_wead_guest_system_countew(test);
		vcpu_wun(vcpu);
		end = host_wead_guest_system_countew(test);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			handwe_sync(&uc, stawt, end);
			bweak;
		case UCAWW_ABOWT:
			handwe_abowt(&uc);
			wetuwn;
		defauwt:
			TEST_ASSEWT(0, "unhandwed ucaww %wd\n",
				    get_ucaww(vcpu, &uc));
		}
	}
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_main);
	check_pweconditions(vcpu);

	entew_guest(vcpu);
	kvm_vm_fwee(vm);
}
