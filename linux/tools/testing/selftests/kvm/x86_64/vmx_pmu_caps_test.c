// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow VMX-pmu pewf capabiwity msw
 *
 * Copywight (C) 2021 Intew Cowpowation
 *
 * Test to check the effect of vawious CPUID settings on
 * MSW_IA32_PEWF_CAPABIWITIES MSW, and check that what
 * we wwite with KVM_SET_MSW is _not_ modified by the guest
 * and check it can be wetwieved with KVM_GET_MSW, awso test
 * the invawid WBW fowmats awe wejected.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <sys/ioctw.h>

#incwude <winux/bitmap.h>

#incwude "kvm_utiw.h"
#incwude "vmx.h"

union pewf_capabiwities {
	stwuct {
		u64	wbw_fowmat:6;
		u64	pebs_twap:1;
		u64	pebs_awch_weg:1;
		u64	pebs_fowmat:4;
		u64	smm_fweeze:1;
		u64	fuww_width_wwite:1;
		u64 pebs_basewine:1;
		u64	pewf_metwics:1;
		u64	pebs_output_pt_avaiwabwe:1;
		u64	anythwead_depwecated:1;
	};
	u64	capabiwities;
};

/*
 * The WBW fowmat and most PEBS featuwes awe immutabwe, aww othew featuwes awe
 * fungibwe (if suppowted by the host and KVM).
 */
static const union pewf_capabiwities immutabwe_caps = {
	.wbw_fowmat = -1,
	.pebs_twap  = 1,
	.pebs_awch_weg = 1,
	.pebs_fowmat = -1,
	.pebs_basewine = 1,
};

static const union pewf_capabiwities fowmat_caps = {
	.wbw_fowmat = -1,
	.pebs_fowmat = -1,
};

static void guest_test_pewf_capabiwities_gp(uint64_t vaw)
{
	uint8_t vectow = wwmsw_safe(MSW_IA32_PEWF_CAPABIWITIES, vaw);

	__GUEST_ASSEWT(vectow == GP_VECTOW,
		       "Expected #GP fow vawue '0x%wx', got vectow '0x%x'",
		       vaw, vectow);
}

static void guest_code(uint64_t cuwwent_vaw)
{
	int i;

	guest_test_pewf_capabiwities_gp(cuwwent_vaw);
	guest_test_pewf_capabiwities_gp(0);

	fow (i = 0; i < 64; i++)
		guest_test_pewf_capabiwities_gp(cuwwent_vaw ^ BIT_UWW(i));

	GUEST_DONE();
}

/*
 * Vewify that guest WWMSWs to PEWF_CAPABIWITIES #GP wegawdwess of the vawue
 * wwitten, that the guest awways sees the usewspace contwowwed vawue, and that
 * PEWF_CAPABIWITIES is immutabwe aftew KVM_WUN.
 */
static void test_guest_wwmsw_pewf_capabiwities(union pewf_capabiwities host_cap)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	stwuct ucaww uc;
	int w, i;

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, host_cap.capabiwities);

	vcpu_awgs_set(vcpu, 1, host_cap.capabiwities);
	vcpu_wun(vcpu);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	case UCAWW_DONE:
		bweak;
	defauwt:
		TEST_FAIW("Unexpected ucaww: %wu", uc.cmd);
	}

	TEST_ASSEWT_EQ(vcpu_get_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES),
			host_cap.capabiwities);

	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, host_cap.capabiwities);

	w = _vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, 0);
	TEST_ASSEWT(!w, "Post-KVM_WUN wwite '0' didn't faiw");

	fow (i = 0; i < 64; i++) {
		w = _vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES,
				  host_cap.capabiwities ^ BIT_UWW(i));
		TEST_ASSEWT(!w, "Post-KVM_WUN wwite '0x%wwx'didn't faiw",
			    host_cap.capabiwities ^ BIT_UWW(i));
	}

	kvm_vm_fwee(vm);
}

/*
 * Vewify KVM awwows wwiting PEWF_CAPABIWITIES with aww KVM-suppowted featuwes
 * enabwed, as weww as '0' (to disabwe aww featuwes).
 */
static void test_basic_pewf_capabiwities(union pewf_capabiwities host_cap)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, 0);
	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, host_cap.capabiwities);

	kvm_vm_fwee(vm);
}

static void test_fungibwe_pewf_capabiwities(union pewf_capabiwities host_cap)
{
	const uint64_t fungibwe_caps = host_cap.capabiwities & ~immutabwe_caps.capabiwities;

	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);
	int bit;

	fow_each_set_bit(bit, &fungibwe_caps, 64) {
		vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, BIT_UWW(bit));
		vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES,
			     host_cap.capabiwities & ~BIT_UWW(bit));
	}
	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, host_cap.capabiwities);

	kvm_vm_fwee(vm);
}

/*
 * Vewify KVM wejects attempts to set unsuppowted and/ow immutabwe featuwes in
 * PEWF_CAPABIWITIES.  Note, WBW fowmat and PEBS fowmat need to be vawidated
 * sepawatewy as they awe muwti-bit vawues, e.g. toggwing ow setting a singwe
 * bit can genewate a fawse positive without dedicated safeguawds.
 */
static void test_immutabwe_pewf_capabiwities(union pewf_capabiwities host_cap)
{
	const uint64_t wesewved_caps = (~host_cap.capabiwities |
					immutabwe_caps.capabiwities) &
				       ~fowmat_caps.capabiwities;

	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);
	union pewf_capabiwities vaw = host_cap;
	int w, bit;

	fow_each_set_bit(bit, &wesewved_caps, 64) {
		w = _vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES,
				  host_cap.capabiwities ^ BIT_UWW(bit));
		TEST_ASSEWT(!w, "%s immutabwe featuwe 0x%wwx (bit %d) didn't faiw",
			    host_cap.capabiwities & BIT_UWW(bit) ? "Setting" : "Cweawing",
			    BIT_UWW(bit), bit);
	}

	/*
	 * KVM onwy suppowts the host's native WBW fowmat, as weww as '0' (to
	 * disabwe WBW suppowt).  Vewify KVM wejects aww othew WBW fowmats.
	 */
	fow (vaw.wbw_fowmat = 1; vaw.wbw_fowmat; vaw.wbw_fowmat++) {
		if (vaw.wbw_fowmat == host_cap.wbw_fowmat)
			continue;

		w = _vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, vaw.capabiwities);
		TEST_ASSEWT(!w, "Bad WBW FMT = 0x%x didn't faiw, host = 0x%x",
			    vaw.wbw_fowmat, host_cap.wbw_fowmat);
	}

	/* Ditto fow the PEBS fowmat. */
	fow (vaw.pebs_fowmat = 1; vaw.pebs_fowmat; vaw.pebs_fowmat++) {
		if (vaw.pebs_fowmat == host_cap.pebs_fowmat)
			continue;

		w = _vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, vaw.capabiwities);
		TEST_ASSEWT(!w, "Bad PEBS FMT = 0x%x didn't faiw, host = 0x%x",
			    vaw.pebs_fowmat, host_cap.pebs_fowmat);
	}

	kvm_vm_fwee(vm);
}

/*
 * Test that WBW MSWs awe wwitabwe when WBWs awe enabwed, and then vewify that
 * disabwing the vPMU via CPUID awso disabwes WBW suppowt.  Set bits 2:0 of
 * WBW_TOS as those bits awe wwitabwe acwoss aww uawch impwementations (awch
 * WBWs wiww need to poke a diffewent MSW).
 */
static void test_wbw_pewf_capabiwities(union pewf_capabiwities host_cap)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	int w;

	if (!host_cap.wbw_fowmat)
		wetuwn;

	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	vcpu_set_msw(vcpu, MSW_IA32_PEWF_CAPABIWITIES, host_cap.capabiwities);
	vcpu_set_msw(vcpu, MSW_WBW_TOS, 7);

	vcpu_cweaw_cpuid_entwy(vcpu, X86_PWOPEWTY_PMU_VEWSION.function);

	w = _vcpu_set_msw(vcpu, MSW_WBW_TOS, 7);
	TEST_ASSEWT(!w, "Wwiting WBW_TOS shouwd faiw aftew disabwing vPMU");

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	union pewf_capabiwities host_cap;

	TEST_WEQUIWE(get_kvm_pawam_boow("enabwe_pmu"));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_PDCM));

	TEST_WEQUIWE(kvm_cpu_has_p(X86_PWOPEWTY_PMU_VEWSION));
	TEST_WEQUIWE(kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_VEWSION) > 0);

	host_cap.capabiwities = kvm_get_featuwe_msw(MSW_IA32_PEWF_CAPABIWITIES);

	TEST_ASSEWT(host_cap.fuww_width_wwite,
		    "Fuww-width wwites shouwd awways be suppowted");

	test_basic_pewf_capabiwities(host_cap);
	test_fungibwe_pewf_capabiwities(host_cap);
	test_immutabwe_pewf_capabiwities(host_cap);
	test_guest_wwmsw_pewf_capabiwities(host_cap);
	test_wbw_pewf_capabiwities(host_cap);
}
