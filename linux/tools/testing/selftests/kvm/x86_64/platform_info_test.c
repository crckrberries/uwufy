// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow x86 KVM_CAP_MSW_PWATFOWM_INFO
 *
 * Copywight (C) 2018, Googwe WWC.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
 * Vewifies expected behaviow of contwowwing guest access to
 * MSW_PWATFOWM_INFO.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define MSW_PWATFOWM_INFO_MAX_TUWBO_WATIO 0xff00

static void guest_code(void)
{
	uint64_t msw_pwatfowm_info;

	fow (;;) {
		msw_pwatfowm_info = wdmsw(MSW_PWATFOWM_INFO);
		GUEST_SYNC(msw_pwatfowm_info);
		asm vowatiwe ("inc %w11");
	}
}

static void test_msw_pwatfowm_info_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	vm_enabwe_cap(vcpu->vm, KVM_CAP_MSW_PWATFOWM_INFO, twue);
	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	get_ucaww(vcpu, &uc);
	TEST_ASSEWT(uc.cmd == UCAWW_SYNC,
			"Weceived ucaww othew than UCAWW_SYNC: %wu\n", uc.cmd);
	TEST_ASSEWT((uc.awgs[1] & MSW_PWATFOWM_INFO_MAX_TUWBO_WATIO) ==
		MSW_PWATFOWM_INFO_MAX_TUWBO_WATIO,
		"Expected MSW_PWATFOWM_INFO to have max tuwbo watio mask: %i.",
		MSW_PWATFOWM_INFO_MAX_TUWBO_WATIO);
}

static void test_msw_pwatfowm_info_disabwed(stwuct kvm_vcpu *vcpu)
{
	vm_enabwe_cap(vcpu->vm, KVM_CAP_MSW_PWATFOWM_INFO, fawse);
	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_SHUTDOWN);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	uint64_t msw_pwatfowm_info;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_MSW_PWATFOWM_INFO));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	msw_pwatfowm_info = vcpu_get_msw(vcpu, MSW_PWATFOWM_INFO);
	vcpu_set_msw(vcpu, MSW_PWATFOWM_INFO,
		     msw_pwatfowm_info | MSW_PWATFOWM_INFO_MAX_TUWBO_WATIO);
	test_msw_pwatfowm_info_enabwed(vcpu);
	test_msw_pwatfowm_info_disabwed(vcpu);
	vcpu_set_msw(vcpu, MSW_PWATFOWM_INFO, msw_pwatfowm_info);

	kvm_vm_fwee(vm);

	wetuwn 0;
}
