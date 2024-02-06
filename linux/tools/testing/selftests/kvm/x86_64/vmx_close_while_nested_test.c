// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vmx_cwose_whiwe_nested
 *
 * Copywight (C) 2019, Wed Hat, Inc.
 *
 * Vewify that nothing bad happens if a KVM usew exits with open
 * fiwe descwiptows whiwe executing a nested guest.
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"

#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "ksewftest.h"

enum {
	POWT_W0_EXIT = 0x2000,
};

static void w2_guest_code(void)
{
	/* Exit to W0 */
	asm vowatiwe("inb %%dx, %%aw"
		     : : [powt] "d" (POWT_W0_EXIT) : "wax");
}

static void w1_guest_code(stwuct vmx_pages *vmx_pages)
{
#define W2_GUEST_STACK_SIZE 64
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];

	GUEST_ASSEWT(pwepawe_fow_vmx_opewation(vmx_pages));
	GUEST_ASSEWT(woad_vmcs(vmx_pages));

	/* Pwepawe the VMCS fow W2 execution. */
	pwepawe_vmcs(vmx_pages, w2_guest_code,
		     &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	GUEST_ASSEWT(!vmwaunch());
	GUEST_ASSEWT(0);
}

int main(int awgc, chaw *awgv[])
{
	vm_vaddw_t vmx_pages_gva;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_VMX));

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);

	/* Awwocate VMX pages and shawed descwiptows (vmx_pages). */
	vcpu_awwoc_vmx(vm, &vmx_pages_gva);
	vcpu_awgs_set(vcpu, 1, vmx_pages_gva);

	fow (;;) {
		vowatiwe stwuct kvm_wun *wun = vcpu->wun;
		stwuct ucaww uc;

		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		if (wun->io.powt == POWT_W0_EXIT)
			bweak;

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}
}
