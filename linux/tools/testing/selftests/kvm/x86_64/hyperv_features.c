// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021, Wed Hat, Inc.
 *
 * Tests fow Hypew-V featuwes enabwement
 */
#incwude <asm/kvm_pawa.h>
#incwude <winux/kvm_pawa.h>
#incwude <stdint.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "hypewv.h"

/*
 * HYPEWV_CPUID_ENWIGHTMENT_INFO.EBX is not a 'featuwe' CPUID weaf
 * but to activate the featuwe it is sufficient to set it to a non-zewo
 * vawue. Use BIT(0) fow that.
 */
#define HV_PV_SPINWOCKS_TEST            \
	KVM_X86_CPU_FEATUWE(HYPEWV_CPUID_ENWIGHTMENT_INFO, 0, EBX, 0)

stwuct msw_data {
	uint32_t idx;
	boow fauwt_expected;
	boow wwite;
	u64 wwite_vaw;
};

stwuct hcaww_data {
	uint64_t contwow;
	uint64_t expect;
	boow ud_expected;
};

static boow is_wwite_onwy_msw(uint32_t msw)
{
	wetuwn msw == HV_X64_MSW_EOI;
}

static void guest_msw(stwuct msw_data *msw)
{
	uint8_t vectow = 0;
	uint64_t msw_vaw = 0;

	GUEST_ASSEWT(msw->idx);

	if (msw->wwite)
		vectow = wwmsw_safe(msw->idx, msw->wwite_vaw);

	if (!vectow && (!msw->wwite || !is_wwite_onwy_msw(msw->idx)))
		vectow = wdmsw_safe(msw->idx, &msw_vaw);

	if (msw->fauwt_expected)
		__GUEST_ASSEWT(vectow == GP_VECTOW,
			       "Expected #GP on %sMSW(0x%x), got vectow '0x%x'",
			       msw->wwite ? "WW" : "WD", msw->idx, vectow);
	ewse
		__GUEST_ASSEWT(!vectow,
			       "Expected success on %sMSW(0x%x), got vectow '0x%x'",
			       msw->wwite ? "WW" : "WD", msw->idx, vectow);

	if (vectow || is_wwite_onwy_msw(msw->idx))
		goto done;

	if (msw->wwite)
		__GUEST_ASSEWT(!vectow,
			       "WWMSW(0x%x) to '0x%wx', WDMSW wead '0x%wx'",
			       msw->idx, msw->wwite_vaw, msw_vaw);

	/* Invawiant TSC bit appeaws when TSC invawiant contwow MSW is wwitten to */
	if (msw->idx == HV_X64_MSW_TSC_INVAWIANT_CONTWOW) {
		if (!this_cpu_has(HV_ACCESS_TSC_INVAWIANT))
			GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_INVTSC));
		ewse
			GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_INVTSC) ==
				     !!(msw_vaw & HV_INVAWIANT_TSC_EXPOSED));
	}

done:
	GUEST_DONE();
}

static void guest_hcaww(vm_vaddw_t pgs_gpa, stwuct hcaww_data *hcaww)
{
	u64 wes, input, output;
	uint8_t vectow;

	GUEST_ASSEWT_NE(hcaww->contwow, 0);

	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	wwmsw(HV_X64_MSW_HYPEWCAWW, pgs_gpa);

	if (!(hcaww->contwow & HV_HYPEWCAWW_FAST_BIT)) {
		input = pgs_gpa;
		output = pgs_gpa + 4096;
	} ewse {
		input = output = 0;
	}

	vectow = __hypewv_hypewcaww(hcaww->contwow, input, output, &wes);
	if (hcaww->ud_expected) {
		__GUEST_ASSEWT(vectow == UD_VECTOW,
			       "Expected #UD fow contwow '%wu', got vectow '0x%x'",
			       hcaww->contwow, vectow);
	} ewse {
		__GUEST_ASSEWT(!vectow,
			       "Expected no exception fow contwow '%wu', got vectow '0x%x'",
			       hcaww->contwow, vectow);
		GUEST_ASSEWT_EQ(wes, hcaww->expect);
	}

	GUEST_DONE();
}

static void vcpu_weset_hv_cpuid(stwuct kvm_vcpu *vcpu)
{
	/*
	 * Enabwe aww suppowted Hypew-V featuwes, then cweaw the weafs howding
	 * the featuwes that wiww be tested one by one.
	 */
	vcpu_set_hv_cpuid(vcpu);

	vcpu_cweaw_cpuid_entwy(vcpu, HYPEWV_CPUID_FEATUWES);
	vcpu_cweaw_cpuid_entwy(vcpu, HYPEWV_CPUID_ENWIGHTMENT_INFO);
	vcpu_cweaw_cpuid_entwy(vcpu, HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES);
}

static void guest_test_msws_access(void)
{
	stwuct kvm_cpuid2 *pwev_cpuid = NUWW;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	int stage = 0;
	vm_vaddw_t msw_gva;
	stwuct msw_data *msw;
	boow has_invtsc = kvm_cpu_has(X86_FEATUWE_INVTSC);

	whiwe (twue) {
		vm = vm_cweate_with_one_vcpu(&vcpu, guest_msw);

		msw_gva = vm_vaddw_awwoc_page(vm);
		memset(addw_gva2hva(vm, msw_gva), 0x0, getpagesize());
		msw = addw_gva2hva(vm, msw_gva);

		vcpu_awgs_set(vcpu, 1, msw_gva);
		vcpu_enabwe_cap(vcpu, KVM_CAP_HYPEWV_ENFOWCE_CPUID, 1);

		if (!pwev_cpuid) {
			vcpu_weset_hv_cpuid(vcpu);

			pwev_cpuid = awwocate_kvm_cpuid2(vcpu->cpuid->nent);
		} ewse {
			vcpu_init_cpuid(vcpu, pwev_cpuid);
		}

		vm_init_descwiptow_tabwes(vm);
		vcpu_init_descwiptow_tabwes(vcpu);

		/* TODO: Make this entiwe test easiew to maintain. */
		if (stage >= 21)
			vcpu_enabwe_cap(vcpu, KVM_CAP_HYPEWV_SYNIC2, 0);

		switch (stage) {
		case 0:
			/*
			 * Onwy avaiwabwe when Hypew-V identification is set
			 */
			msw->idx = HV_X64_MSW_GUEST_OS_ID;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 1:
			msw->idx = HV_X64_MSW_HYPEWCAWW;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 2:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_HYPEWCAWW_AVAIWABWE);
			/*
			 * HV_X64_MSW_GUEST_OS_ID has to be wwitten fiwst to make
			 * HV_X64_MSW_HYPEWCAWW avaiwabwe.
			 */
			msw->idx = HV_X64_MSW_GUEST_OS_ID;
			msw->wwite = twue;
			msw->wwite_vaw = HYPEWV_WINUX_OS_ID;
			msw->fauwt_expected = fawse;
			bweak;
		case 3:
			msw->idx = HV_X64_MSW_GUEST_OS_ID;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 4:
			msw->idx = HV_X64_MSW_HYPEWCAWW;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;

		case 5:
			msw->idx = HV_X64_MSW_VP_WUNTIME;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 6:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_VP_WUNTIME_AVAIWABWE);
			msw->idx = HV_X64_MSW_VP_WUNTIME;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 7:
			/* Wead onwy */
			msw->idx = HV_X64_MSW_VP_WUNTIME;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = twue;
			bweak;

		case 8:
			msw->idx = HV_X64_MSW_TIME_WEF_COUNT;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 9:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_TIME_WEF_COUNT_AVAIWABWE);
			msw->idx = HV_X64_MSW_TIME_WEF_COUNT;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 10:
			/* Wead onwy */
			msw->idx = HV_X64_MSW_TIME_WEF_COUNT;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = twue;
			bweak;

		case 11:
			msw->idx = HV_X64_MSW_VP_INDEX;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 12:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_VP_INDEX_AVAIWABWE);
			msw->idx = HV_X64_MSW_VP_INDEX;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 13:
			/* Wead onwy */
			msw->idx = HV_X64_MSW_VP_INDEX;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = twue;
			bweak;

		case 14:
			msw->idx = HV_X64_MSW_WESET;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 15:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_WESET_AVAIWABWE);
			msw->idx = HV_X64_MSW_WESET;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 16:
			msw->idx = HV_X64_MSW_WESET;
			msw->wwite = twue;
			/*
			 * TODO: the test onwy wwites '0' to HV_X64_MSW_WESET
			 * at the moment, wwiting some othew vawue thewe wiww
			 * twiggew weaw vCPU weset and the code is not pwepawed
			 * to handwe it yet.
			 */
			msw->wwite_vaw = 0;
			msw->fauwt_expected = fawse;
			bweak;

		case 17:
			msw->idx = HV_X64_MSW_WEFEWENCE_TSC;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 18:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_WEFEWENCE_TSC_AVAIWABWE);
			msw->idx = HV_X64_MSW_WEFEWENCE_TSC;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 19:
			msw->idx = HV_X64_MSW_WEFEWENCE_TSC;
			msw->wwite = twue;
			msw->wwite_vaw = 0;
			msw->fauwt_expected = fawse;
			bweak;

		case 20:
			msw->idx = HV_X64_MSW_EOM;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 21:
			/*
			 * Wemains unavaiwabwe even with KVM_CAP_HYPEWV_SYNIC2
			 * capabiwity enabwed and guest visibwe CPUID bit unset.
			 */
			msw->idx = HV_X64_MSW_EOM;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 22:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_SYNIC_AVAIWABWE);
			msw->idx = HV_X64_MSW_EOM;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 23:
			msw->idx = HV_X64_MSW_EOM;
			msw->wwite = twue;
			msw->wwite_vaw = 0;
			msw->fauwt_expected = fawse;
			bweak;

		case 24:
			msw->idx = HV_X64_MSW_STIMEW0_CONFIG;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 25:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_SYNTIMEW_AVAIWABWE);
			msw->idx = HV_X64_MSW_STIMEW0_CONFIG;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 26:
			msw->idx = HV_X64_MSW_STIMEW0_CONFIG;
			msw->wwite = twue;
			msw->wwite_vaw = 0;
			msw->fauwt_expected = fawse;
			bweak;
		case 27:
			/* Diwect mode test */
			msw->idx = HV_X64_MSW_STIMEW0_CONFIG;
			msw->wwite = twue;
			msw->wwite_vaw = 1 << 12;
			msw->fauwt_expected = twue;
			bweak;
		case 28:
			vcpu_set_cpuid_featuwe(vcpu, HV_STIMEW_DIWECT_MODE_AVAIWABWE);
			msw->idx = HV_X64_MSW_STIMEW0_CONFIG;
			msw->wwite = twue;
			msw->wwite_vaw = 1 << 12;
			msw->fauwt_expected = fawse;
			bweak;

		case 29:
			msw->idx = HV_X64_MSW_EOI;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 30:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_APIC_ACCESS_AVAIWABWE);
			msw->idx = HV_X64_MSW_EOI;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = fawse;
			bweak;

		case 31:
			msw->idx = HV_X64_MSW_TSC_FWEQUENCY;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 32:
			vcpu_set_cpuid_featuwe(vcpu, HV_ACCESS_FWEQUENCY_MSWS);
			msw->idx = HV_X64_MSW_TSC_FWEQUENCY;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 33:
			/* Wead onwy */
			msw->idx = HV_X64_MSW_TSC_FWEQUENCY;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = twue;
			bweak;

		case 34:
			msw->idx = HV_X64_MSW_WEENWIGHTENMENT_CONTWOW;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 35:
			vcpu_set_cpuid_featuwe(vcpu, HV_ACCESS_WEENWIGHTENMENT);
			msw->idx = HV_X64_MSW_WEENWIGHTENMENT_CONTWOW;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 36:
			msw->idx = HV_X64_MSW_WEENWIGHTENMENT_CONTWOW;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = fawse;
			bweak;
		case 37:
			/* Can onwy wwite '0' */
			msw->idx = HV_X64_MSW_TSC_EMUWATION_STATUS;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = twue;
			bweak;

		case 38:
			msw->idx = HV_X64_MSW_CWASH_P0;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 39:
			vcpu_set_cpuid_featuwe(vcpu, HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE);
			msw->idx = HV_X64_MSW_CWASH_P0;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 40:
			msw->idx = HV_X64_MSW_CWASH_P0;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = fawse;
			bweak;

		case 41:
			msw->idx = HV_X64_MSW_SYNDBG_STATUS;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 42:
			vcpu_set_cpuid_featuwe(vcpu, HV_FEATUWE_DEBUG_MSWS_AVAIWABWE);
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_SYNDBG_CAP_AWWOW_KEWNEW_DEBUGGING);
			msw->idx = HV_X64_MSW_SYNDBG_STATUS;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 43:
			msw->idx = HV_X64_MSW_SYNDBG_STATUS;
			msw->wwite = twue;
			msw->wwite_vaw = 0;
			msw->fauwt_expected = fawse;
			bweak;

		case 44:
			/* MSW is not avaiwabwe when CPUID featuwe bit is unset */
			if (!has_invtsc)
				continue;
			msw->idx = HV_X64_MSW_TSC_INVAWIANT_CONTWOW;
			msw->wwite = fawse;
			msw->fauwt_expected = twue;
			bweak;
		case 45:
			/* MSW is vaiwabwe when CPUID featuwe bit is set */
			if (!has_invtsc)
				continue;
			vcpu_set_cpuid_featuwe(vcpu, HV_ACCESS_TSC_INVAWIANT);
			msw->idx = HV_X64_MSW_TSC_INVAWIANT_CONTWOW;
			msw->wwite = fawse;
			msw->fauwt_expected = fawse;
			bweak;
		case 46:
			/* Wwiting bits othew than 0 is fowbidden */
			if (!has_invtsc)
				continue;
			msw->idx = HV_X64_MSW_TSC_INVAWIANT_CONTWOW;
			msw->wwite = twue;
			msw->wwite_vaw = 0xdeadbeef;
			msw->fauwt_expected = twue;
			bweak;
		case 47:
			/* Setting bit 0 enabwes the featuwe */
			if (!has_invtsc)
				continue;
			msw->idx = HV_X64_MSW_TSC_INVAWIANT_CONTWOW;
			msw->wwite = twue;
			msw->wwite_vaw = 1;
			msw->fauwt_expected = fawse;
			bweak;

		defauwt:
			kvm_vm_fwee(vm);
			wetuwn;
		}

		vcpu_set_cpuid(vcpu);

		memcpy(pwev_cpuid, vcpu->cpuid, kvm_cpuid2_size(vcpu->cpuid->nent));

		pw_debug("Stage %d: testing msw: 0x%x fow %s\n", stage,
			 msw->idx, msw->wwite ? "wwite" : "wead");

		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			wetuwn;
		case UCAWW_DONE:
			bweak;
		defauwt:
			TEST_FAIW("Unhandwed ucaww: %wd", uc.cmd);
			wetuwn;
		}

		stage++;
		kvm_vm_fwee(vm);
	}
}

static void guest_test_hcawws_access(void)
{
	stwuct kvm_cpuid2 *pwev_cpuid = NUWW;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	int stage = 0;
	vm_vaddw_t hcaww_page, hcaww_pawams;
	stwuct hcaww_data *hcaww;

	whiwe (twue) {
		vm = vm_cweate_with_one_vcpu(&vcpu, guest_hcaww);

		vm_init_descwiptow_tabwes(vm);
		vcpu_init_descwiptow_tabwes(vcpu);

		/* Hypewcaww input/output */
		hcaww_page = vm_vaddw_awwoc_pages(vm, 2);
		memset(addw_gva2hva(vm, hcaww_page), 0x0, 2 * getpagesize());

		hcaww_pawams = vm_vaddw_awwoc_page(vm);
		memset(addw_gva2hva(vm, hcaww_pawams), 0x0, getpagesize());
		hcaww = addw_gva2hva(vm, hcaww_pawams);

		vcpu_awgs_set(vcpu, 2, addw_gva2gpa(vm, hcaww_page), hcaww_pawams);
		vcpu_enabwe_cap(vcpu, KVM_CAP_HYPEWV_ENFOWCE_CPUID, 1);

		if (!pwev_cpuid) {
			vcpu_weset_hv_cpuid(vcpu);

			pwev_cpuid = awwocate_kvm_cpuid2(vcpu->cpuid->nent);
		} ewse {
			vcpu_init_cpuid(vcpu, pwev_cpuid);
		}

		switch (stage) {
		case 0:
			vcpu_set_cpuid_featuwe(vcpu, HV_MSW_HYPEWCAWW_AVAIWABWE);
			hcaww->contwow = 0xbeef;
			hcaww->expect = HV_STATUS_INVAWID_HYPEWCAWW_CODE;
			bweak;

		case 1:
			hcaww->contwow = HVCAWW_POST_MESSAGE;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 2:
			vcpu_set_cpuid_featuwe(vcpu, HV_POST_MESSAGES);
			hcaww->contwow = HVCAWW_POST_MESSAGE;
			hcaww->expect = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;

		case 3:
			hcaww->contwow = HVCAWW_SIGNAW_EVENT;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 4:
			vcpu_set_cpuid_featuwe(vcpu, HV_SIGNAW_EVENTS);
			hcaww->contwow = HVCAWW_SIGNAW_EVENT;
			hcaww->expect = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;

		case 5:
			hcaww->contwow = HVCAWW_WESET_DEBUG_SESSION;
			hcaww->expect = HV_STATUS_INVAWID_HYPEWCAWW_CODE;
			bweak;
		case 6:
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_SYNDBG_CAP_AWWOW_KEWNEW_DEBUGGING);
			hcaww->contwow = HVCAWW_WESET_DEBUG_SESSION;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 7:
			vcpu_set_cpuid_featuwe(vcpu, HV_DEBUGGING);
			hcaww->contwow = HVCAWW_WESET_DEBUG_SESSION;
			hcaww->expect = HV_STATUS_OPEWATION_DENIED;
			bweak;

		case 8:
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 9:
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED);
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE;
			hcaww->expect = HV_STATUS_SUCCESS;
			bweak;
		case 10:
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 11:
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED);
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX;
			hcaww->expect = HV_STATUS_SUCCESS;
			bweak;

		case 12:
			hcaww->contwow = HVCAWW_SEND_IPI;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 13:
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_CWUSTEW_IPI_WECOMMENDED);
			hcaww->contwow = HVCAWW_SEND_IPI;
			hcaww->expect = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		case 14:
			/* Nothing in 'spawse banks' -> success */
			hcaww->contwow = HVCAWW_SEND_IPI_EX;
			hcaww->expect = HV_STATUS_SUCCESS;
			bweak;

		case 15:
			hcaww->contwow = HVCAWW_NOTIFY_WONG_SPIN_WAIT;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 16:
			vcpu_set_cpuid_featuwe(vcpu, HV_PV_SPINWOCKS_TEST);
			hcaww->contwow = HVCAWW_NOTIFY_WONG_SPIN_WAIT;
			hcaww->expect = HV_STATUS_SUCCESS;
			bweak;
		case 17:
			/* XMM fast hypewcaww */
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE | HV_HYPEWCAWW_FAST_BIT;
			hcaww->ud_expected = twue;
			bweak;
		case 18:
			vcpu_set_cpuid_featuwe(vcpu, HV_X64_HYPEWCAWW_XMM_INPUT_AVAIWABWE);
			hcaww->contwow = HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE | HV_HYPEWCAWW_FAST_BIT;
			hcaww->ud_expected = fawse;
			hcaww->expect = HV_STATUS_SUCCESS;
			bweak;
		case 19:
			hcaww->contwow = HV_EXT_CAWW_QUEWY_CAPABIWITIES;
			hcaww->expect = HV_STATUS_ACCESS_DENIED;
			bweak;
		case 20:
			vcpu_set_cpuid_featuwe(vcpu, HV_ENABWE_EXTENDED_HYPEWCAWWS);
			hcaww->contwow = HV_EXT_CAWW_QUEWY_CAPABIWITIES | HV_HYPEWCAWW_FAST_BIT;
			hcaww->expect = HV_STATUS_INVAWID_PAWAMETEW;
			bweak;
		case 21:
			kvm_vm_fwee(vm);
			wetuwn;
		}

		vcpu_set_cpuid(vcpu);

		memcpy(pwev_cpuid, vcpu->cpuid, kvm_cpuid2_size(vcpu->cpuid->nent));

		pw_debug("Stage %d: testing hcaww: 0x%wx\n", stage, hcaww->contwow);

		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			wetuwn;
		case UCAWW_DONE:
			bweak;
		defauwt:
			TEST_FAIW("Unhandwed ucaww: %wd", uc.cmd);
			wetuwn;
		}

		stage++;
		kvm_vm_fwee(vm);
	}
}

int main(void)
{
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_ENFOWCE_CPUID));

	pw_info("Testing access to Hypew-V specific MSWs\n");
	guest_test_msws_access();

	pw_info("Testing access to Hypew-V hypewcawws\n");
	guest_test_hcawws_access();
}
