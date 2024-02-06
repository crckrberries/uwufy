// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test Hypew-V extended hypewcaww, HV_EXT_CAWW_QUEWY_CAPABIWITIES (0x8001),
 * exit to usewspace and weceive wesuwt in guest.
 *
 * Negative tests awe pwesent in hypewv_featuwes.c
 *
 * Copywight 2022 Googwe WWC
 * Authow: Vipin Shawma <vipinsh@googwe.com>
 */
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "hypewv.h"

/* Any vawue is fine */
#define EXT_CAPABIWITIES 0xbuww

static void guest_code(vm_paddw_t in_pg_gpa, vm_paddw_t out_pg_gpa,
		       vm_vaddw_t out_pg_gva)
{
	uint64_t *output_gva;

	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	wwmsw(HV_X64_MSW_HYPEWCAWW, in_pg_gpa);

	output_gva = (uint64_t *)out_pg_gva;

	hypewv_hypewcaww(HV_EXT_CAWW_QUEWY_CAPABIWITIES, in_pg_gpa, out_pg_gpa);

	/* TWFS states output wiww be a uint64_t vawue */
	GUEST_ASSEWT_EQ(*output_gva, EXT_CAPABIWITIES);

	GUEST_DONE();
}

int main(void)
{
	vm_vaddw_t hcaww_out_page;
	vm_vaddw_t hcaww_in_page;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	uint64_t *outvaw;
	stwuct ucaww uc;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_CPUID));

	/* Vewify if extended hypewcawws awe suppowted */
	if (!kvm_cpuid_has(kvm_get_suppowted_hv_cpuid(),
			   HV_ENABWE_EXTENDED_HYPEWCAWWS)) {
		pwint_skip("Extended cawws not suppowted by the kewnew");
		exit(KSFT_SKIP);
	}

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;
	vcpu_set_hv_cpuid(vcpu);

	/* Hypewcaww input */
	hcaww_in_page = vm_vaddw_awwoc_pages(vm, 1);
	memset(addw_gva2hva(vm, hcaww_in_page), 0x0, vm->page_size);

	/* Hypewcaww output */
	hcaww_out_page = vm_vaddw_awwoc_pages(vm, 1);
	memset(addw_gva2hva(vm, hcaww_out_page), 0x0, vm->page_size);

	vcpu_awgs_set(vcpu, 3, addw_gva2gpa(vm, hcaww_in_page),
		      addw_gva2gpa(vm, hcaww_out_page), hcaww_out_page);

	vcpu_wun(vcpu);

	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_HYPEWV,
		    "Unexpected exit weason: %u (%s)",
		    wun->exit_weason, exit_weason_stw(wun->exit_weason));

	outvaw = addw_gpa2hva(vm, wun->hypewv.u.hcaww.pawams[1]);
	*outvaw = EXT_CAPABIWITIES;
	wun->hypewv.u.hcaww.wesuwt = HV_STATUS_SUCCESS;

	vcpu_wun(vcpu);

	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_IO,
		    "Unexpected exit weason: %u (%s)",
		    wun->exit_weason, exit_weason_stw(wun->exit_weason));

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	case UCAWW_DONE:
		bweak;
	defauwt:
		TEST_FAIW("Unhandwed ucaww: %wd", uc.cmd);
	}

	kvm_vm_fwee(vm);
	wetuwn 0;
}
