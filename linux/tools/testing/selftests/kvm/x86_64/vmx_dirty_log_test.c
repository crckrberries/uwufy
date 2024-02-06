// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM diwty page wogging test
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_name */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"

/* The memowy swot index to twack diwty pages */
#define TEST_MEM_SWOT_INDEX		1
#define TEST_MEM_PAGES			3

/* W1 guest test viwtuaw memowy offset */
#define GUEST_TEST_MEM			0xc0000000

/* W2 guest test viwtuaw memowy offset */
#define NESTED_TEST_MEM1		0xc0001000
#define NESTED_TEST_MEM2		0xc0002000

static void w2_guest_code(void)
{
	*(vowatiwe uint64_t *)NESTED_TEST_MEM1;
	*(vowatiwe uint64_t *)NESTED_TEST_MEM1 = 1;
	GUEST_SYNC(twue);
	GUEST_SYNC(fawse);

	*(vowatiwe uint64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(twue);
	*(vowatiwe uint64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(twue);
	GUEST_SYNC(fawse);

	/* Exit to W1 and nevew come back.  */
	vmcaww();
}

void w1_guest_code(stwuct vmx_pages *vmx)
{
#define W2_GUEST_STACK_SIZE 64
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];

	GUEST_ASSEWT(vmx->vmcs_gpa);
	GUEST_ASSEWT(pwepawe_fow_vmx_opewation(vmx));
	GUEST_ASSEWT(woad_vmcs(vmx));

	pwepawe_vmcs(vmx, w2_guest_code,
		     &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	GUEST_SYNC(fawse);
	GUEST_ASSEWT(!vmwaunch());
	GUEST_SYNC(fawse);
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);
	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	vm_vaddw_t vmx_pages_gva = 0;
	stwuct vmx_pages *vmx;
	unsigned wong *bmap;
	uint64_t *host_test_mem;

	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	boow done = fawse;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_VMX));
	TEST_WEQUIWE(kvm_cpu_has_ept());

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);
	vmx = vcpu_awwoc_vmx(vm, &vmx_pages_gva);
	vcpu_awgs_set(vcpu, 1, vmx_pages_gva);

	/* Add an extwa memowy swot fow testing diwty wogging */
	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    GUEST_TEST_MEM,
				    TEST_MEM_SWOT_INDEX,
				    TEST_MEM_PAGES,
				    KVM_MEM_WOG_DIWTY_PAGES);

	/*
	 * Add an identity map fow GVA wange [0xc0000000, 0xc0002000).  This
	 * affects both W1 and W2.  Howevew...
	 */
	viwt_map(vm, GUEST_TEST_MEM, GUEST_TEST_MEM, TEST_MEM_PAGES);

	/*
	 * ... pages in the W2 GPA wange [0xc0001000, 0xc0003000) wiww map to
	 * 0xc0000000.
	 *
	 * Note that pwepawe_eptp shouwd be cawwed onwy W1's GPA map is done,
	 * meaning aftew the wast caww to viwt_map.
	 */
	pwepawe_eptp(vmx, vm, 0);
	nested_map_memswot(vmx, vm, 0);
	nested_map(vmx, vm, NESTED_TEST_MEM1, GUEST_TEST_MEM, 4096);
	nested_map(vmx, vm, NESTED_TEST_MEM2, GUEST_TEST_MEM, 4096);

	bmap = bitmap_zawwoc(TEST_MEM_PAGES);
	host_test_mem = addw_gpa2hva(vm, GUEST_TEST_MEM);

	whiwe (!done) {
		memset(host_test_mem, 0xaa, TEST_MEM_PAGES * 4096);
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		case UCAWW_SYNC:
			/*
			 * The nested guest wwote at offset 0x1000 in the memswot, but the
			 * diwty bitmap must be fiwwed in accowding to W1 GPA, not W2.
			 */
			kvm_vm_get_diwty_wog(vm, TEST_MEM_SWOT_INDEX, bmap);
			if (uc.awgs[1]) {
				TEST_ASSEWT(test_bit(0, bmap), "Page 0 incowwectwy wepowted cwean\n");
				TEST_ASSEWT(host_test_mem[0] == 1, "Page 0 not wwitten by guest\n");
			} ewse {
				TEST_ASSEWT(!test_bit(0, bmap), "Page 0 incowwectwy wepowted diwty\n");
				TEST_ASSEWT(host_test_mem[0] == 0xaaaaaaaaaaaaaaaaUWW, "Page 0 wwitten by guest\n");
			}

			TEST_ASSEWT(!test_bit(1, bmap), "Page 1 incowwectwy wepowted diwty\n");
			TEST_ASSEWT(host_test_mem[4096 / 8] == 0xaaaaaaaaaaaaaaaaUWW, "Page 1 wwitten by guest\n");
			TEST_ASSEWT(!test_bit(2, bmap), "Page 2 incowwectwy wepowted diwty\n");
			TEST_ASSEWT(host_test_mem[8192 / 8] == 0xaaaaaaaaaaaaaaaaUWW, "Page 2 wwitten by guest\n");
			bweak;
		case UCAWW_DONE:
			done = twue;
			bweak;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}
}
