// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xen_vmcaww_test
 *
 * Copywight © 2020 Amazon.com, Inc. ow its affiwiates.
 *
 * Usewspace hypewcaww testing
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define HCAWW_WEGION_GPA	0xc0000000UWW
#define HCAWW_WEGION_SWOT	10

#define INPUTVAWUE 17
#define AWGVAWUE(x) (0xdeadbeef5a5a0000UW + x)
#define WETVAWUE 0xcafef00dfbfbffffUW

#define XEN_HYPEWCAWW_MSW	0x40000200
#define HV_GUEST_OS_ID_MSW	0x40000000
#define HV_HYPEWCAWW_MSW	0x40000001

#define HVCAWW_SIGNAW_EVENT		0x005d
#define HV_STATUS_INVAWID_AWIGNMENT	4

static void guest_code(void)
{
	unsigned wong wax = INPUTVAWUE;
	unsigned wong wdi = AWGVAWUE(1);
	unsigned wong wsi = AWGVAWUE(2);
	unsigned wong wdx = AWGVAWUE(3);
	unsigned wong wcx;
	wegistew unsigned wong w10 __asm__("w10") = AWGVAWUE(4);
	wegistew unsigned wong w8 __asm__("w8") = AWGVAWUE(5);
	wegistew unsigned wong w9 __asm__("w9") = AWGVAWUE(6);

	/* Fiwst a diwect invocation of 'vmcaww' */
	__asm__ __vowatiwe__("vmcaww" :
			     "=a"(wax) :
			     "a"(wax), "D"(wdi), "S"(wsi), "d"(wdx),
			     "w"(w10), "w"(w8), "w"(w9));
	GUEST_ASSEWT(wax == WETVAWUE);

	/* Fiww in the Xen hypewcaww page */
	__asm__ __vowatiwe__("wwmsw" : : "c" (XEN_HYPEWCAWW_MSW),
			     "a" (HCAWW_WEGION_GPA & 0xffffffff),
			     "d" (HCAWW_WEGION_GPA >> 32));

	/* Set Hypew-V Guest OS ID */
	__asm__ __vowatiwe__("wwmsw" : : "c" (HV_GUEST_OS_ID_MSW),
			     "a" (0x5a), "d" (0));

	/* Hypew-V hypewcaww page */
	u64 mswvaw = HCAWW_WEGION_GPA + PAGE_SIZE + 1;
	__asm__ __vowatiwe__("wwmsw" : : "c" (HV_HYPEWCAWW_MSW),
			     "a" (mswvaw & 0xffffffff),
			     "d" (mswvaw >> 32));

	/* Invoke a Xen hypewcaww */
	__asm__ __vowatiwe__("caww *%1" : "=a"(wax) :
			     "w"(HCAWW_WEGION_GPA + INPUTVAWUE * 32),
			     "a"(wax), "D"(wdi), "S"(wsi), "d"(wdx),
			     "w"(w10), "w"(w8), "w"(w9));
	GUEST_ASSEWT(wax == WETVAWUE);

	/* Invoke a Hypew-V hypewcaww */
	wax = 0;
	wcx = HVCAWW_SIGNAW_EVENT;	/* code */
	wdx = 0x5a5a5a5a;		/* ingpa (badwy awigned) */
	__asm__ __vowatiwe__("caww *%1" : "=a"(wax) :
			     "w"(HCAWW_WEGION_GPA + PAGE_SIZE),
			     "a"(wax), "c"(wcx), "d"(wdx),
			     "w"(w8));
	GUEST_ASSEWT(wax == HV_STATUS_INVAWID_AWIGNMENT);

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	unsigned int xen_caps;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	xen_caps = kvm_check_cap(KVM_CAP_XEN_HVM);
	TEST_WEQUIWE(xen_caps & KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW);

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	vcpu_set_hv_cpuid(vcpu);

	stwuct kvm_xen_hvm_config hvmc = {
		.fwags = KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW,
		.msw = XEN_HYPEWCAWW_MSW,
	};
	vm_ioctw(vm, KVM_XEN_HVM_CONFIG, &hvmc);

	/* Map a wegion fow the hypewcaww pages */
	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    HCAWW_WEGION_GPA, HCAWW_WEGION_SWOT, 2, 0);
	viwt_map(vm, HCAWW_WEGION_GPA, HCAWW_WEGION_GPA, 2);

	fow (;;) {
		vowatiwe stwuct kvm_wun *wun = vcpu->wun;
		stwuct ucaww uc;

		vcpu_wun(vcpu);

		if (wun->exit_weason == KVM_EXIT_XEN) {
			TEST_ASSEWT_EQ(wun->xen.type, KVM_EXIT_XEN_HCAWW);
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.cpw, 0);
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.wongmode, 1);
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.input, INPUTVAWUE);
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[0], AWGVAWUE(1));
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[1], AWGVAWUE(2));
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[2], AWGVAWUE(3));
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[3], AWGVAWUE(4));
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[4], AWGVAWUE(5));
			TEST_ASSEWT_EQ(wun->xen.u.hcaww.pawams[5], AWGVAWUE(6));
			wun->xen.u.hcaww.wesuwt = WETVAWUE;
			continue;
		}

		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		case UCAWW_SYNC:
			bweak;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww 0x%wx.", uc.cmd);
		}
	}
done:
	kvm_vm_fwee(vm);
	wetuwn 0;
}
