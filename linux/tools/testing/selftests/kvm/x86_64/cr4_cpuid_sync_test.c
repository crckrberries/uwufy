// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CW4 and CPUID sync test
 *
 * Copywight 2018, Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authow:
 *   Wei Huang <wei@wedhat.com>
 */

#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

static inwine boow cw4_cpuid_is_sync(void)
{
	uint64_t cw4 = get_cw4();

	wetuwn (this_cpu_has(X86_FEATUWE_OSXSAVE) == !!(cw4 & X86_CW4_OSXSAVE));
}

static void guest_code(void)
{
	uint64_t cw4;

	/* tuwn on CW4.OSXSAVE */
	cw4 = get_cw4();
	cw4 |= X86_CW4_OSXSAVE;
	set_cw4(cw4);

	/* vewify CW4.OSXSAVE == CPUID.OSXSAVE */
	GUEST_ASSEWT(cw4_cpuid_is_sync());

	/* notify hypewvisow to change CW4 */
	GUEST_SYNC(0);

	/* check again */
	GUEST_ASSEWT(cw4_cpuid_is_sync());

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_swegs swegs;
	stwuct ucaww uc;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XSAVE));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	whiwe (1) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			/* emuwate hypewvisow cweawing CW4.OSXSAVE */
			vcpu_swegs_get(vcpu, &swegs);
			swegs.cw4 &= ~X86_CW4_OSXSAVE;
			vcpu_swegs_set(vcpu, &swegs);
			bweak;
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
