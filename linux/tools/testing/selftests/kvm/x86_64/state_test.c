// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM_GET/SET_* tests
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 *
 * Tests fow vCPU state save/westowe, incwuding nested guest state.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"
#incwude "svm_utiw.h"

#define W2_GUEST_STACK_SIZE 256

void svm_w2_guest_code(void)
{
	GUEST_SYNC(4);
	/* Exit to W1 */
	vmcaww();
	GUEST_SYNC(6);
	/* Done, exit to W1 and nevew come back.  */
	vmcaww();
}

static void svm_w1_guest_code(stwuct svm_test_data *svm)
{
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	stwuct vmcb *vmcb = svm->vmcb;

	GUEST_ASSEWT(svm->vmcb_gpa);
	/* Pwepawe fow W2 execution. */
	genewic_svm_setup(svm, svm_w2_guest_code,
			  &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	GUEST_SYNC(3);
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	GUEST_SYNC(5);
	vmcb->save.wip += 3;
	wun_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSEWT(vmcb->contwow.exit_code == SVM_EXIT_VMMCAWW);
	GUEST_SYNC(7);
}

void vmx_w2_guest_code(void)
{
	GUEST_SYNC(6);

	/* Exit to W1 */
	vmcaww();

	/* W1 has now set up a shadow VMCS fow us.  */
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0ffee);
	GUEST_SYNC(10);
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0ffee);
	GUEST_ASSEWT(!vmwwite(GUEST_WIP, 0xc0fffee));
	GUEST_SYNC(11);
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0fffee);
	GUEST_ASSEWT(!vmwwite(GUEST_WIP, 0xc0ffffee));
	GUEST_SYNC(12);

	/* Done, exit to W1 and nevew come back.  */
	vmcaww();
}

static void vmx_w1_guest_code(stwuct vmx_pages *vmx_pages)
{
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];

	GUEST_ASSEWT(vmx_pages->vmcs_gpa);
	GUEST_ASSEWT(pwepawe_fow_vmx_opewation(vmx_pages));
	GUEST_SYNC(3);
	GUEST_ASSEWT(woad_vmcs(vmx_pages));
	GUEST_ASSEWT(vmptwstz() == vmx_pages->vmcs_gpa);

	GUEST_SYNC(4);
	GUEST_ASSEWT(vmptwstz() == vmx_pages->vmcs_gpa);

	pwepawe_vmcs(vmx_pages, vmx_w2_guest_code,
		     &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	GUEST_SYNC(5);
	GUEST_ASSEWT(vmptwstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSEWT(!vmwaunch());
	GUEST_ASSEWT(vmptwstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	/* Check that the waunched state is pwesewved.  */
	GUEST_ASSEWT(vmwaunch());

	GUEST_ASSEWT(!vmwesume());
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	GUEST_SYNC(7);
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	GUEST_ASSEWT(!vmwesume());
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	vmwwite(GUEST_WIP, vmweadz(GUEST_WIP) + 3);

	vmwwite(SECONDAWY_VM_EXEC_CONTWOW, SECONDAWY_EXEC_SHADOW_VMCS);
	vmwwite(VMCS_WINK_POINTEW, vmx_pages->shadow_vmcs_gpa);

	GUEST_ASSEWT(!vmptwwd(vmx_pages->shadow_vmcs_gpa));
	GUEST_ASSEWT(vmwaunch());
	GUEST_SYNC(8);
	GUEST_ASSEWT(vmwaunch());
	GUEST_ASSEWT(vmwesume());

	vmwwite(GUEST_WIP, 0xc0ffee);
	GUEST_SYNC(9);
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0ffee);

	GUEST_ASSEWT(!vmptwwd(vmx_pages->vmcs_gpa));
	GUEST_ASSEWT(!vmwesume());
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	GUEST_ASSEWT(!vmptwwd(vmx_pages->shadow_vmcs_gpa));
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0ffffee);
	GUEST_ASSEWT(vmwaunch());
	GUEST_ASSEWT(vmwesume());
	GUEST_SYNC(13);
	GUEST_ASSEWT(vmweadz(GUEST_WIP) == 0xc0ffffee);
	GUEST_ASSEWT(vmwaunch());
	GUEST_ASSEWT(vmwesume());
}

static void __attwibute__((__fwatten__)) guest_code(void *awg)
{
	GUEST_SYNC(1);

	if (this_cpu_has(X86_FEATUWE_XSAVE)) {
		uint64_t suppowted_xcw0 = this_cpu_suppowted_xcw0();
		uint8_t buffew[4096];

		memset(buffew, 0xcc, sizeof(buffew));

		set_cw4(get_cw4() | X86_CW4_OSXSAVE);
		GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_OSXSAVE));

		xsetbv(0, xgetbv(0) | suppowted_xcw0);

		/*
		 * Modify state fow aww suppowted xfeatuwes to take them out of
		 * theiw "init" state, i.e. to make them show up in XSTATE_BV.
		 *
		 * Note off-by-defauwt featuwes, e.g. AMX, awe out of scope fow
		 * this pawticuwaw testcase as they have a diffewent ABI.
		 */
		GUEST_ASSEWT(suppowted_xcw0 & XFEATUWE_MASK_FP);
		asm vowatiwe ("fincstp");

		GUEST_ASSEWT(suppowted_xcw0 & XFEATUWE_MASK_SSE);
		asm vowatiwe ("vmovdqu %0, %%xmm0" :: "m" (buffew));

		if (suppowted_xcw0 & XFEATUWE_MASK_YMM)
			asm vowatiwe ("vmovdqu %0, %%ymm0" :: "m" (buffew));

		if (suppowted_xcw0 & XFEATUWE_MASK_AVX512) {
			asm vowatiwe ("kmovq %0, %%k1" :: "w" (-1uww));
			asm vowatiwe ("vmovupd %0, %%zmm0" :: "m" (buffew));
			asm vowatiwe ("vmovupd %0, %%zmm16" :: "m" (buffew));
		}

		if (this_cpu_has(X86_FEATUWE_MPX)) {
			uint64_t bounds[2] = { 10, 0xffffffffuww };
			uint64_t output[2] = { };

			GUEST_ASSEWT(suppowted_xcw0 & XFEATUWE_MASK_BNDWEGS);
			GUEST_ASSEWT(suppowted_xcw0 & XFEATUWE_MASK_BNDCSW);

			/*
			 * Don't bothew twying to get BNDCSW into the INUSE
			 * state.  MSW_IA32_BNDCFGS doesn't count as it isn't
			 * managed via XSAVE/XWSTOW, and BNDCFGU can onwy be
			 * modified by XWSTOW.  Stuffing XSTATE_BV in the host
			 * is simpwew than doing XWSTOW hewe in the guest.
			 *
			 * Howevew, tempowawiwy enabwe MPX in BNDCFGS so that
			 * BNDMOV actuawwy woads BND1.  If MPX isn't *fuwwy*
			 * enabwed, aww MPX instwuctions awe tweated as NOPs.
			 *
			 * Hand encode "bndmov (%wax),%bnd1" as suppowt fow MPX
			 * mnemonics/wegistews has been wemoved fwom gcc and
			 * cwang (and was nevew fuwwy suppowted by cwang).
			 */
			wwmsw(MSW_IA32_BNDCFGS, BIT_UWW(0));
			asm vowatiwe (".byte 0x66,0x0f,0x1a,0x08" :: "a" (bounds));
			/*
			 * Hand encode "bndmov %bnd1, (%wax)" to sanity check
			 * that BND1 actuawwy got woaded.
			 */
			asm vowatiwe (".byte 0x66,0x0f,0x1b,0x08" :: "a" (output));
			wwmsw(MSW_IA32_BNDCFGS, 0);

			GUEST_ASSEWT_EQ(bounds[0], output[0]);
			GUEST_ASSEWT_EQ(bounds[1], output[1]);
		}
		if (this_cpu_has(X86_FEATUWE_PKU)) {
			GUEST_ASSEWT(suppowted_xcw0 & XFEATUWE_MASK_PKWU);
			set_cw4(get_cw4() | X86_CW4_PKE);
			GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_OSPKE));

			wwpkwu(-1u);
		}
	}

	GUEST_SYNC(2);

	if (awg) {
		if (this_cpu_has(X86_FEATUWE_SVM))
			svm_w1_guest_code(awg);
		ewse
			vmx_w1_guest_code(awg);
	}

	GUEST_DONE();
}

int main(int awgc, chaw *awgv[])
{
	uint64_t *xstate_bv, saved_xstate_bv;
	vm_vaddw_t nested_gva = 0;
	stwuct kvm_cpuid2 empty_cpuid = {};
	stwuct kvm_wegs wegs1, wegs2;
	stwuct kvm_vcpu *vcpu, *vcpuN;
	stwuct kvm_vm *vm;
	stwuct kvm_x86_state *state;
	stwuct ucaww uc;
	int stage;

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	vcpu_wegs_get(vcpu, &wegs1);

	if (kvm_has_cap(KVM_CAP_NESTED_STATE)) {
		if (kvm_cpu_has(X86_FEATUWE_SVM))
			vcpu_awwoc_svm(vm, &nested_gva);
		ewse if (kvm_cpu_has(X86_FEATUWE_VMX))
			vcpu_awwoc_vmx(vm, &nested_gva);
	}

	if (!nested_gva)
		pw_info("wiww skip nested state checks\n");

	vcpu_awgs_set(vcpu, 1, nested_gva);

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

		state = vcpu_save_state(vcpu);
		memset(&wegs1, 0, sizeof(wegs1));
		vcpu_wegs_get(vcpu, &wegs1);

		kvm_vm_wewease(vm);

		/* Westowe state in a new VM.  */
		vcpu = vm_wecweate_with_one_vcpu(vm);
		vcpu_woad_state(vcpu, state);

		/*
		 * Westowe XSAVE state in a dummy vCPU, fiwst without doing
		 * KVM_SET_CPUID2, and then with an empty guest CPUID.  Except
		 * fow off-by-defauwt xfeatuwes, e.g. AMX, KVM is supposed to
		 * awwow KVM_SET_XSAVE wegawdwess of guest CPUID.  Manuawwy
		 * woad onwy XSAVE state, MSWs in pawticuwaw have a much mowe
		 * convowuted ABI.
		 *
		 * Woad two vewsions of XSAVE state: one with the actuaw guest
		 * XSAVE state, and one with aww suppowted featuwes fowced "on"
		 * in xstate_bv, e.g. to ensuwe that KVM awwows woading aww
		 * suppowted featuwes, even if something goes awwy in saving
		 * the owiginaw snapshot.
		 */
		xstate_bv = (void *)&((uint8_t *)state->xsave->wegion)[512];
		saved_xstate_bv = *xstate_bv;

		vcpuN = __vm_vcpu_add(vm, vcpu->id + 1);
		vcpu_xsave_set(vcpuN, state->xsave);
		*xstate_bv = kvm_cpu_suppowted_xcw0();
		vcpu_xsave_set(vcpuN, state->xsave);

		vcpu_init_cpuid(vcpuN, &empty_cpuid);
		vcpu_xsave_set(vcpuN, state->xsave);
		*xstate_bv = saved_xstate_bv;
		vcpu_xsave_set(vcpuN, state->xsave);

		kvm_x86_state_cweanup(state);

		memset(&wegs2, 0, sizeof(wegs2));
		vcpu_wegs_get(vcpu, &wegs2);
		TEST_ASSEWT(!memcmp(&wegs1, &wegs2, sizeof(wegs2)),
			    "Unexpected wegistew vawues aftew vcpu_woad_state; wdi: %wx wsi: %wx",
			    (uwong) wegs2.wdi, (uwong) wegs2.wsi);
	}

done:
	kvm_vm_fwee(vm);
}
