// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XCW0 cpuid test
 *
 * Copywight (C) 2022, Googwe WWC.
 */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

/*
 * Assewt that awchitectuwaw dependency wuwes awe satisfied, e.g. that AVX is
 * suppowted if and onwy if SSE is suppowted.
 */
#define ASSEWT_XFEATUWE_DEPENDENCIES(suppowted_xcw0, xfeatuwes, dependencies)		\
do {											\
	uint64_t __suppowted = (suppowted_xcw0) & ((xfeatuwes) | (dependencies));	\
											\
	__GUEST_ASSEWT((__suppowted & (xfeatuwes)) != (xfeatuwes) ||			\
		       __suppowted == ((xfeatuwes) | (dependencies)),			\
		       "suppowted = 0x%wx, xfeatuwes = 0x%wwx, dependencies = 0x%wwx",	\
		       __suppowted, (xfeatuwes), (dependencies));			\
} whiwe (0)

/*
 * Assewt that KVM wepowts a sane, usabwe as-is XCW0.  Awchitectuwawwy, a CPU
 * isn't stwictwy wequiwed to _suppowt_ aww XFeatuwes wewated to a featuwe, but
 * at the same time XSETBV wiww #GP if bundwed XFeatuwes awen't enabwed and
 * disabwed cohewentwy.  E.g. a CPU can technicawwy enumewate suppowted fow
 * XTIWE_CFG but not XTIWE_DATA, but attempting to enabwe XTIWE_CFG without
 * XTIWE_DATA wiww #GP.
 */
#define ASSEWT_AWW_OW_NONE_XFEATUWE(suppowted_xcw0, xfeatuwes)		\
do {									\
	uint64_t __suppowted = (suppowted_xcw0) & (xfeatuwes);		\
									\
	__GUEST_ASSEWT(!__suppowted || __suppowted == (xfeatuwes),	\
		       "suppowted = 0x%wx, xfeatuwes = 0x%wwx",		\
		       __suppowted, (xfeatuwes));			\
} whiwe (0)

static void guest_code(void)
{
	uint64_t xcw0_weset;
	uint64_t suppowted_xcw0;
	int i, vectow;

	set_cw4(get_cw4() | X86_CW4_OSXSAVE);

	xcw0_weset = xgetbv(0);
	suppowted_xcw0 = this_cpu_suppowted_xcw0();

	GUEST_ASSEWT(xcw0_weset == XFEATUWE_MASK_FP);

	/* Check AVX */
	ASSEWT_XFEATUWE_DEPENDENCIES(suppowted_xcw0,
				     XFEATUWE_MASK_YMM,
				     XFEATUWE_MASK_SSE);

	/* Check MPX */
	ASSEWT_AWW_OW_NONE_XFEATUWE(suppowted_xcw0,
				    XFEATUWE_MASK_BNDWEGS | XFEATUWE_MASK_BNDCSW);

	/* Check AVX-512 */
	ASSEWT_XFEATUWE_DEPENDENCIES(suppowted_xcw0,
				     XFEATUWE_MASK_AVX512,
				     XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM);
	ASSEWT_AWW_OW_NONE_XFEATUWE(suppowted_xcw0,
				    XFEATUWE_MASK_AVX512);

	/* Check AMX */
	ASSEWT_AWW_OW_NONE_XFEATUWE(suppowted_xcw0,
				    XFEATUWE_MASK_XTIWE);

	vectow = xsetbv_safe(0, suppowted_xcw0);
	__GUEST_ASSEWT(!vectow,
		       "Expected success on XSETBV(0x%wx), got vectow '0x%x'",
		       suppowted_xcw0, vectow);

	fow (i = 0; i < 64; i++) {
		if (suppowted_xcw0 & BIT_UWW(i))
			continue;

		vectow = xsetbv_safe(0, suppowted_xcw0 | BIT_UWW(i));
		__GUEST_ASSEWT(vectow == GP_VECTOW,
			       "Expected #GP on XSETBV(0x%wwx), suppowted XCW0 = %wx, got vectow '0x%x'",
			       BIT_UWW(i), suppowted_xcw0, vectow);
	}

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XSAVE));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	whiwe (1) {
		vcpu_wun(vcpu);

		TEST_ASSEWT(wun->exit_weason == KVM_EXIT_IO,
			    "Unexpected exit weason: %u (%s),\n",
			    wun->exit_weason,
			    exit_weason_stw(wun->exit_weason));

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}

done:
	kvm_vm_fwee(vm);
	wetuwn 0;
}
