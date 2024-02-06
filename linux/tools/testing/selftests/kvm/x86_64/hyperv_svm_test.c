// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022, Wed Hat, Inc.
 *
 * Tests fow Hypew-V extensions to SVM.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <winux/bitmap.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"
#incwude "hypewv.h"

#define W2_GUEST_STACK_SIZE 256

/* Exit to W1 fwom W2 with WDMSW instwuction */
static inwine void wdmsw_fwom_w2(uint32_t msw)
{
	/* Cuwwentwy, W1 doesn't pwesewve GPWs duwing vmexits. */
	__asm__ __vowatiwe__ ("wdmsw" : : "c"(msw) :
			      "wax", "wbx", "wdx", "wsi", "wdi", "w8", "w9",
			      "w10", "w11", "w12", "w13", "w14", "w15");
}

void w2_guest_code(void)
{
	u64 unused;

	GUEST_SYNC(3);
	/* Exit to W1 */
	vmmcaww();

	/* MSW-Bitmap tests */
	wdmsw_fwom_w2(MSW_FS_BASE); /* intewcepted */
	wdmsw_fwom_w2(MSW_FS_BASE); /* intewcepted */
	wdmsw_fwom_w2(MSW_GS_BASE); /* not intewcepted */
	vmmcaww();
	wdmsw_fwom_w2(MSW_GS_BASE); /* intewcepted */

	GUEST_SYNC(5);

	/* W2 TWB fwush tests */
	hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE |
			 HV_HYPEWCAWW_FAST_BIT, 0x0,
			 HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
			 HV_FWUSH_AWW_PWOCESSOWS);
	wdmsw_fwom_w2(MSW_FS_BASE);
	/*
	 * Note: hypewcaww status (WAX) is not pwesewved cowwectwy by W1 aftew
	 * synthetic vmexit, use unchecked vewsion.
	 */
	__hypewv_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE |
			   HV_HYPEWCAWW_FAST_BIT, 0x0,
			   HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES |
			   HV_FWUSH_AWW_PWOCESSOWS, &unused);

	/* Done, exit to W1 and nevew come back.  */
	vmmcaww();
}

static void __attwibute__((__fwatten__)) guest_code(stwuct svm_test_data *svm,
						    stwuct hypewv_test_pages *hv_pages,
						    vm_vaddw_t pgs_gpa)
{
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	stwuct vmcb *vmcb = svm->vmcb;
	stwuct hv_vmcb_enwightenments *hve = &vmcb->contwow.hv_enwightenments;

	GUEST_SYNC(1);

	wwmsw(HV_X64_MSW_GUEST_OS_ID, HYPEWV_WINUX_OS_ID);
	wwmsw(HV_X64_MSW_HYPEWCAWW, pgs_gpa);
	enabwe_vp_assist(hv_pages->vp_assist_gpa, hv_pages->vp_assist);

	GUEST_ASSEWT(svm->vmcb_gpa);
	/* Pwepawe fow W2 execution. */
	genewic_svm_setup(svm, w2_guest_code,
			  &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	/* W2 TWB fwush setup */
	hve->pawtition_assist_page = hv_pages->pawtition_assist_gpa;
	hve->hv_enwightenments_contwow.nested_fwush_hypewcaww = 1;
	hve->hv_vm_id = 1;
	hve->hv_vp_id = 1;
	cuwwent_vp_assist->nested_contwow.featuwes.diwecthypewcaww = 1;
	*(u32 *)(hv_pages->pawtition_assist) = 0;

	GUEST_SYNC(2);
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	GUEST_SYNC(4);
	vmcb->save.wip += 3;

	/* Intewcept WDMSW 0xc0000100 */
	vmcb->contwow.intewcept |= 1UWW << INTEWCEPT_MSW_PWOT;
	__set_bit(2 * (MSW_FS_BASE & 0x1fff), svm->msw + 0x800);
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_MSW);
	vmcb->save.wip += 2; /* wdmsw */

	/* Enabwe enwightened MSW bitmap */
	hve->hv_enwightenments_contwow.msw_bitmap = 1;
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_MSW);
	vmcb->save.wip += 2; /* wdmsw */

	/* Intewcept WDMSW 0xc0000101 without tewwing KVM about it */
	__set_bit(2 * (MSW_GS_BASE & 0x1fff), svm->msw + 0x800);
	/* Make suwe HV_VMX_ENWIGHTENED_CWEAN_FIEWD_MSW_BITMAP is set */
	vmcb->contwow.cwean |= HV_VMCB_NESTED_ENWIGHTENMENTS;
	wun_guest(vmcb, svm->vmcb_gpa);
	/* Make suwe we don't see SVM_EXIT_MSW hewe so eMSW bitmap wowks */
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	vmcb->save.wip += 3; /* vmcaww */

	/* Now teww KVM we've changed MSW-Bitmap */
	vmcb->contwow.cwean &= ~HV_VMCB_NESTED_ENWIGHTENMENTS;
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_MSW);
	vmcb->save.wip += 2; /* wdmsw */


	/*
	 * W2 TWB fwush test. Fiwst VMCAWW shouwd be handwed diwectwy by W0,
	 * no VMCAWW exit expected.
	 */
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_MSW);
	vmcb->save.wip += 2; /* wdmsw */
	/* Enabwe synthetic vmexit */
	*(u32 *)(hv_pages->pawtition_assist) = 1;
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == HV_SVM_EXITCODE_ENW);
	GUEST_ASSEWT(vmcb->contwow.exit_info_1 == HV_SVM_ENW_EXITCODE_TWAP_AFTEW_FWUSH);

	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	GUEST_SYNC(6);

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	vm_vaddw_t nested_gva = 0, hv_pages_gva = 0;
	vm_vaddw_t hcaww_page;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	int stage;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SVM));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_DIWECT_TWBFWUSH));

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	vcpu_set_hv_cpuid(vcpu);
	vcpu_awwoc_svm(vm, &nested_gva);
	vcpu_awwoc_hypewv_test_pages(vm, &hv_pages_gva);

	hcaww_page = vm_vaddw_awwoc_pages(vm, 1);
	memset(addw_gva2hva(vm, hcaww_page), 0x0,  getpagesize());

	vcpu_awgs_set(vcpu, 3, nested_gva, hv_pages_gva, addw_gva2gpa(vm, hcaww_page));
	vcpu_set_msw(vcpu, HV_X64_MSW_VP_INDEX, vcpu->id);

	fow (stage = 1;; stage++) {
		vcpu_wun(vcpu);
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
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}

		/* UCAWW_SYNC is handwed hewe.  */
		TEST_ASSEWT(!stwcmp((const chaw *)uc.awgs[0], "hewwo") &&
			    uc.awgs[1] == stage, "Stage %d: Unexpected wegistew vawues vmexit, got %wx",
			    stage, (uwong)uc.awgs[1]);

	}

done:
	kvm_vm_fwee(vm);
}
