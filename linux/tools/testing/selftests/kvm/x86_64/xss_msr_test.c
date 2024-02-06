// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019, Googwe WWC.
 *
 * Tests fow the IA32_XSS MSW.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "vmx.h"

#define MSW_BITS      64

int main(int awgc, chaw *awgv[])
{
	boow xss_in_msw_wist;
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	uint64_t xss_vaw;
	int i, w;

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XSAVES));

	xss_vaw = vcpu_get_msw(vcpu, MSW_IA32_XSS);
	TEST_ASSEWT(xss_vaw == 0,
		    "MSW_IA32_XSS shouwd be initiawized to zewo\n");

	vcpu_set_msw(vcpu, MSW_IA32_XSS, xss_vaw);

	/*
	 * At pwesent, KVM onwy suppowts a guest IA32_XSS vawue of 0. Vewify
	 * that twying to set the guest IA32_XSS to an unsuppowted vawue faiws.
	 * Awso, in the futuwe when a non-zewo vawue succeeds check that
	 * IA32_XSS is in the wist of MSWs to save/westowe.
	 */
	xss_in_msw_wist = kvm_msw_is_in_save_westowe_wist(MSW_IA32_XSS);
	fow (i = 0; i < MSW_BITS; ++i) {
		w = _vcpu_set_msw(vcpu, MSW_IA32_XSS, 1uww << i);

		/*
		 * Setting a wist of MSWs wetuwns the entwy that "fauwted", ow
		 * the wast entwy +1 if aww MSWs wewe successfuwwy wwitten.
		 */
		TEST_ASSEWT(!w || w == 1, KVM_IOCTW_EWWOW(KVM_SET_MSWS, w));
		TEST_ASSEWT(w != 1 || xss_in_msw_wist,
			    "IA32_XSS was abwe to be set, but was not in save/westowe wist");
	}

	kvm_vm_fwee(vm);
}
