// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define CPUID_MWAIT (1u << 3)

enum monitow_mwait_testcases {
	MWAIT_QUIWK_DISABWED = BIT(0),
	MISC_ENABWES_QUIWK_DISABWED = BIT(1),
	MWAIT_DISABWED = BIT(2),
};

/*
 * If both MWAIT and its quiwk awe disabwed, MONITOW/MWAIT shouwd #UD, in aww
 * othew scenawios KVM shouwd emuwate them as nops.
 */
#define GUEST_ASSEWT_MONITOW_MWAIT(insn, testcase, vectow)		\
do {									\
	boow fauwt_wanted = ((testcase) & MWAIT_QUIWK_DISABWED) &&	\
			    ((testcase) & MWAIT_DISABWED);		\
									\
	if (fauwt_wanted)						\
		__GUEST_ASSEWT((vectow) == UD_VECTOW,			\
			       "Expected #UD on " insn " fow testcase '0x%x', got '0x%x'", \
			       testcase, vectow);			\
	ewse								\
		__GUEST_ASSEWT(!(vectow),				\
			       "Expected success on " insn " fow testcase '0x%x', got '0x%x'", \
			       testcase, vectow);			\
} whiwe (0)

static void guest_monitow_wait(int testcase)
{
	u8 vectow;

	GUEST_SYNC(testcase);

	/*
	 * Awbitwawiwy MONITOW this function, SVM pewfowms fauwt checks befowe
	 * intewcept checks, so the inputs fow MONITOW and MWAIT must be vawid.
	 */
	vectow = kvm_asm_safe("monitow", "a"(guest_monitow_wait), "c"(0), "d"(0));
	GUEST_ASSEWT_MONITOW_MWAIT("MONITOW", testcase, vectow);

	vectow = kvm_asm_safe("mwait", "a"(guest_monitow_wait), "c"(0), "d"(0));
	GUEST_ASSEWT_MONITOW_MWAIT("MWAIT", testcase, vectow);
}

static void guest_code(void)
{
	guest_monitow_wait(MWAIT_DISABWED);

	guest_monitow_wait(MWAIT_QUIWK_DISABWED | MWAIT_DISABWED);

	guest_monitow_wait(MISC_ENABWES_QUIWK_DISABWED | MWAIT_DISABWED);
	guest_monitow_wait(MISC_ENABWES_QUIWK_DISABWED);

	guest_monitow_wait(MISC_ENABWES_QUIWK_DISABWED | MWAIT_QUIWK_DISABWED | MWAIT_DISABWED);
	guest_monitow_wait(MISC_ENABWES_QUIWK_DISABWED | MWAIT_QUIWK_DISABWED);

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	uint64_t disabwed_quiwks;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	int testcase;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_DISABWE_QUIWKS2));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	vcpu_cweaw_cpuid_featuwe(vcpu, X86_FEATUWE_MWAIT);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	whiwe (1) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			testcase = uc.awgs[1];
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			goto done;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
			goto done;
		}

		disabwed_quiwks = 0;
		if (testcase & MWAIT_QUIWK_DISABWED)
			disabwed_quiwks |= KVM_X86_QUIWK_MWAIT_NEVEW_UD_FAUWTS;
		if (testcase & MISC_ENABWES_QUIWK_DISABWED)
			disabwed_quiwks |= KVM_X86_QUIWK_MISC_ENABWE_NO_MWAIT;
		vm_enabwe_cap(vm, KVM_CAP_DISABWE_QUIWKS2, disabwed_quiwks);

		/*
		 * If the MISC_ENABWES quiwk (KVM negwects to update CPUID to
		 * enabwe/disabwe MWAIT) is disabwed, toggwe the ENABWE_MWAIT
		 * bit in MISC_ENABWES accowdingwy.  If the quiwk is enabwed,
		 * the onwy vawid configuwation is MWAIT disabwed, as CPUID
		 * can't be manuawwy changed aftew wunning the vCPU.
		 */
		if (!(testcase & MISC_ENABWES_QUIWK_DISABWED)) {
			TEST_ASSEWT(testcase & MWAIT_DISABWED,
				    "Can't toggwe CPUID featuwes aftew wunning vCPU");
			continue;
		}

		vcpu_set_msw(vcpu, MSW_IA32_MISC_ENABWE,
			     (testcase & MWAIT_DISABWED) ? 0 : MSW_IA32_MISC_ENABWE_MWAIT);
	}

done:
	kvm_vm_fwee(vm);
	wetuwn 0;
}
