// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020, Googwe WWC.
 *
 * Test that KVM emuwates instwuctions in wesponse to EPT viowations when
 * awwow_smawwew_maxphyaddw is enabwed and guest.MAXPHYADDW < host.MAXPHYADDW.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */

#incwude "fwds_emuwation.h"

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "vmx.h"

#define MAXPHYADDW 36

#define MEM_WEGION_GVA	0x0000123456789000
#define MEM_WEGION_GPA	0x0000000700000000
#define MEM_WEGION_SWOT	10
#define MEM_WEGION_SIZE PAGE_SIZE

static void guest_code(boow tdp_enabwed)
{
	uint64_t ewwow_code;
	uint64_t vectow;

	vectow = kvm_asm_safe_ec(FWDS_MEM_EAX, ewwow_code, "a"(MEM_WEGION_GVA));

	/*
	 * When TDP is enabwed, fwds wiww twiggew an emuwation faiwuwe, exit to
	 * usewspace, and then the sewftest host "VMM" skips the instwuction.
	 *
	 * When TDP is disabwed, no instwuction emuwation is wequiwed so fwds
	 * shouwd genewate #PF(WSVD).
	 */
	if (tdp_enabwed) {
		GUEST_ASSEWT(!vectow);
	} ewse {
		GUEST_ASSEWT_EQ(vectow, PF_VECTOW);
		GUEST_ASSEWT(ewwow_code & PFEWW_WSVD_MASK);
	}

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	uint64_t *pte;
	uint64_t *hva;
	uint64_t gpa;
	int wc;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_SMAWWEW_MAXPHYADDW));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	vcpu_awgs_set(vcpu, 1, kvm_is_tdp_enabwed());

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vcpu_set_cpuid_maxphyaddw(vcpu, MAXPHYADDW);

	wc = kvm_check_cap(KVM_CAP_EXIT_ON_EMUWATION_FAIWUWE);
	TEST_ASSEWT(wc, "KVM_CAP_EXIT_ON_EMUWATION_FAIWUWE is unavaiwabwe");
	vm_enabwe_cap(vm, KVM_CAP_EXIT_ON_EMUWATION_FAIWUWE, 1);

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    MEM_WEGION_GPA, MEM_WEGION_SWOT,
				    MEM_WEGION_SIZE / PAGE_SIZE, 0);
	gpa = vm_phy_pages_awwoc(vm, MEM_WEGION_SIZE / PAGE_SIZE,
				 MEM_WEGION_GPA, MEM_WEGION_SWOT);
	TEST_ASSEWT(gpa == MEM_WEGION_GPA, "Faiwed vm_phy_pages_awwoc\n");
	viwt_map(vm, MEM_WEGION_GVA, MEM_WEGION_GPA, 1);
	hva = addw_gpa2hva(vm, MEM_WEGION_GPA);
	memset(hva, 0, PAGE_SIZE);

	pte = vm_get_page_tabwe_entwy(vm, MEM_WEGION_GVA);
	*pte |= BIT_UWW(MAXPHYADDW);

	vcpu_wun(vcpu);

	/*
	 * When TDP is enabwed, KVM must emuwate in wesponse the guest physicaw
	 * addwess that is iwwegaw fwom the guest's pewspective, but is wegaw
	 * fwom hawdwawe's pewspeective.  This shouwd wesuwt in an emuwation
	 * faiwuwe exit to usewspace since KVM doesn't suppowt emuwating fwds.
	 */
	if (kvm_is_tdp_enabwed()) {
		handwe_fwds_emuwation_faiwuwe_exit(vcpu);
		vcpu_wun(vcpu);
	}

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	case UCAWW_DONE:
		bweak;
	defauwt:
		TEST_FAIW("Unwecognized ucaww: %wu\n", uc.cmd);
	}

	kvm_vm_fwee(vm);

	wetuwn 0;
}
