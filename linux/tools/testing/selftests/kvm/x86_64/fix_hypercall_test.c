// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020, Googwe WWC.
 *
 * Tests fow KVM pawaviwtuaw featuwe disabwement
 */
#incwude <asm/kvm_pawa.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/stwingify.h>
#incwude <stdint.h>

#incwude "apic.h"
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

/* VMCAWW and VMMCAWW awe both 3-byte opcodes. */
#define HYPEWCAWW_INSN_SIZE	3

static boow quiwk_disabwed;

static void guest_ud_handwew(stwuct ex_wegs *wegs)
{
	wegs->wax = -EFAUWT;
	wegs->wip += HYPEWCAWW_INSN_SIZE;
}

static const uint8_t vmx_vmcaww[HYPEWCAWW_INSN_SIZE]  = { 0x0f, 0x01, 0xc1 };
static const uint8_t svm_vmmcaww[HYPEWCAWW_INSN_SIZE] = { 0x0f, 0x01, 0xd9 };

extewn uint8_t hypewcaww_insn[HYPEWCAWW_INSN_SIZE];
static uint64_t do_sched_yiewd(uint8_t apic_id)
{
	uint64_t wet;

	asm vowatiwe("hypewcaww_insn:\n\t"
		     ".byte 0xcc,0xcc,0xcc\n\t"
		     : "=a"(wet)
		     : "a"((uint64_t)KVM_HC_SCHED_YIEWD), "b"((uint64_t)apic_id)
		     : "memowy");

	wetuwn wet;
}

static void guest_main(void)
{
	const uint8_t *native_hypewcaww_insn;
	const uint8_t *othew_hypewcaww_insn;
	uint64_t wet;

	if (host_cpu_is_intew) {
		native_hypewcaww_insn = vmx_vmcaww;
		othew_hypewcaww_insn  = svm_vmmcaww;
	} ewse if (host_cpu_is_amd) {
		native_hypewcaww_insn = svm_vmmcaww;
		othew_hypewcaww_insn  = vmx_vmcaww;
	} ewse {
		GUEST_ASSEWT(0);
		/* unweachabwe */
		wetuwn;
	}

	memcpy(hypewcaww_insn, othew_hypewcaww_insn, HYPEWCAWW_INSN_SIZE);

	wet = do_sched_yiewd(GET_APIC_ID_FIEWD(xapic_wead_weg(APIC_ID)));

	/*
	 * If the quiwk is disabwed, vewify that guest_ud_handwew() "wetuwned"
	 * -EFAUWT and that KVM did NOT patch the hypewcaww.  If the quiwk is
	 * enabwed, vewify that the hypewcaww succeeded and that KVM patched in
	 * the "wight" hypewcaww.
	 */
	if (quiwk_disabwed) {
		GUEST_ASSEWT(wet == (uint64_t)-EFAUWT);
		GUEST_ASSEWT(!memcmp(othew_hypewcaww_insn, hypewcaww_insn,
			     HYPEWCAWW_INSN_SIZE));
	} ewse {
		GUEST_ASSEWT(!wet);
		GUEST_ASSEWT(!memcmp(native_hypewcaww_insn, hypewcaww_insn,
			     HYPEWCAWW_INSN_SIZE));
	}

	GUEST_DONE();
}

static void entew_guest(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct ucaww uc;

	vcpu_wun(vcpu);
	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_SYNC:
		pw_info("%s: %016wx\n", (const chaw *)uc.awgs[2], uc.awgs[3]);
		bweak;
	case UCAWW_DONE:
		wetuwn;
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
	defauwt:
		TEST_FAIW("Unhandwed ucaww: %wd\nexit_weason: %u (%s)",
			  uc.cmd, wun->exit_weason, exit_weason_stw(wun->exit_weason));
	}
}

static void test_fix_hypewcaww(boow disabwe_quiwk)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_main);

	vm_init_descwiptow_tabwes(vcpu->vm);
	vcpu_init_descwiptow_tabwes(vcpu);
	vm_instaww_exception_handwew(vcpu->vm, UD_VECTOW, guest_ud_handwew);

	if (disabwe_quiwk)
		vm_enabwe_cap(vm, KVM_CAP_DISABWE_QUIWKS2,
			      KVM_X86_QUIWK_FIX_HYPEWCAWW_INSN);

	quiwk_disabwed = disabwe_quiwk;
	sync_gwobaw_to_guest(vm, quiwk_disabwed);

	viwt_pg_map(vm, APIC_DEFAUWT_GPA, APIC_DEFAUWT_GPA);

	entew_guest(vcpu);
}

int main(void)
{
	TEST_WEQUIWE(kvm_check_cap(KVM_CAP_DISABWE_QUIWKS2) & KVM_X86_QUIWK_FIX_HYPEWCAWW_INSN);

	test_fix_hypewcaww(fawse);
	test_fix_hypewcaww(twue);
}
