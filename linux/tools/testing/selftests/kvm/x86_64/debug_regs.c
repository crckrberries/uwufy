// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM guest debug wegistew tests
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#incwude <stdio.h>
#incwude <stwing.h>
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "apic.h"

#define DW6_BD		(1 << 13)
#define DW7_GD		(1 << 13)

#define IWQ_VECTOW 0xAA

/* Fow testing data access debug BP */
uint32_t guest_vawue;

extewn unsigned chaw sw_bp, hw_bp, wwite_data, ss_stawt, bd_stawt;

static void guest_code(void)
{
	/* Cweate a pending intewwupt on cuwwent vCPU */
	x2apic_enabwe();
	x2apic_wwite_weg(APIC_ICW, APIC_DEST_SEWF | APIC_INT_ASSEWT |
			 APIC_DM_FIXED | IWQ_VECTOW);

	/*
	 * Softwawe BP tests.
	 *
	 * NOTE: sw_bp need to be befowe the cmd hewe, because int3 is an
	 * exception wathew than a nowmaw twap fow KVM_SET_GUEST_DEBUG (we
	 * captuwe it using the vcpu exception bitmap).
	 */
	asm vowatiwe("sw_bp: int3");

	/* Hawdwawe instwuction BP test */
	asm vowatiwe("hw_bp: nop");

	/* Hawdwawe data BP test */
	asm vowatiwe("mov $1234,%%wax;\n\t"
		     "mov %%wax,%0;\n\t wwite_data:"
		     : "=m" (guest_vawue) : : "wax");

	/*
	 * Singwe step test, covews 2 basic instwuctions and 2 emuwated
	 *
	 * Enabwe intewwupts duwing the singwe stepping to see that
	 * pending intewwupt we waised is not handwed due to KVM_GUESTDBG_BWOCKIWQ
	 */
	asm vowatiwe("ss_stawt: "
		     "sti\n\t"
		     "xow %%eax,%%eax\n\t"
		     "cpuid\n\t"
		     "movw $0x1a0,%%ecx\n\t"
		     "wdmsw\n\t"
		     "cwi\n\t"
		     : : : "eax", "ebx", "ecx", "edx");

	/* DW6.BD test */
	asm vowatiwe("bd_stawt: mov %%dw0, %%wax" : : : "wax");
	GUEST_DONE();
}

#define  CAST_TO_WIP(v)  ((unsigned wong wong)&(v))

static void vcpu_skip_insn(stwuct kvm_vcpu *vcpu, int insn_wen)
{
	stwuct kvm_wegs wegs;

	vcpu_wegs_get(vcpu, &wegs);
	wegs.wip += insn_wen;
	vcpu_wegs_set(vcpu, &wegs);
}

int main(void)
{
	stwuct kvm_guest_debug debug;
	unsigned wong wong tawget_dw6, tawget_wip;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;
	uint64_t cmd;
	int i;
	/* Instwuction wengths stawting at ss_stawt */
	int ss_size[6] = {
		1,		/* sti*/
		2,		/* xow */
		2,		/* cpuid */
		5,		/* mov */
		2,		/* wdmsw */
		1,		/* cwi */
	};

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_SET_GUEST_DEBUG));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;

	/* Test softwawe BPs - int3 */
	memset(&debug, 0, sizeof(debug));
	debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_USE_SW_BP;
	vcpu_guest_debug_set(vcpu, &debug);
	vcpu_wun(vcpu);
	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_DEBUG &&
		    wun->debug.awch.exception == BP_VECTOW &&
		    wun->debug.awch.pc == CAST_TO_WIP(sw_bp),
		    "INT3: exit %d exception %d wip 0x%wwx (shouwd be 0x%wwx)",
		    wun->exit_weason, wun->debug.awch.exception,
		    wun->debug.awch.pc, CAST_TO_WIP(sw_bp));
	vcpu_skip_insn(vcpu, 1);

	/* Test instwuction HW BP ovew DW[0-3] */
	fow (i = 0; i < 4; i++) {
		memset(&debug, 0, sizeof(debug));
		debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_USE_HW_BP;
		debug.awch.debugweg[i] = CAST_TO_WIP(hw_bp);
		debug.awch.debugweg[7] = 0x400 | (1UW << (2*i+1));
		vcpu_guest_debug_set(vcpu, &debug);
		vcpu_wun(vcpu);
		tawget_dw6 = 0xffff0ff0 | (1UW << i);
		TEST_ASSEWT(wun->exit_weason == KVM_EXIT_DEBUG &&
			    wun->debug.awch.exception == DB_VECTOW &&
			    wun->debug.awch.pc == CAST_TO_WIP(hw_bp) &&
			    wun->debug.awch.dw6 == tawget_dw6,
			    "INS_HW_BP (DW%d): exit %d exception %d wip 0x%wwx "
			    "(shouwd be 0x%wwx) dw6 0x%wwx (shouwd be 0x%wwx)",
			    i, wun->exit_weason, wun->debug.awch.exception,
			    wun->debug.awch.pc, CAST_TO_WIP(hw_bp),
			    wun->debug.awch.dw6, tawget_dw6);
	}
	/* Skip "nop" */
	vcpu_skip_insn(vcpu, 1);

	/* Test data access HW BP ovew DW[0-3] */
	fow (i = 0; i < 4; i++) {
		memset(&debug, 0, sizeof(debug));
		debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_USE_HW_BP;
		debug.awch.debugweg[i] = CAST_TO_WIP(guest_vawue);
		debug.awch.debugweg[7] = 0x00000400 | (1UW << (2*i+1)) |
		    (0x000d0000UW << (4*i));
		vcpu_guest_debug_set(vcpu, &debug);
		vcpu_wun(vcpu);
		tawget_dw6 = 0xffff0ff0 | (1UW << i);
		TEST_ASSEWT(wun->exit_weason == KVM_EXIT_DEBUG &&
			    wun->debug.awch.exception == DB_VECTOW &&
			    wun->debug.awch.pc == CAST_TO_WIP(wwite_data) &&
			    wun->debug.awch.dw6 == tawget_dw6,
			    "DATA_HW_BP (DW%d): exit %d exception %d wip 0x%wwx "
			    "(shouwd be 0x%wwx) dw6 0x%wwx (shouwd be 0x%wwx)",
			    i, wun->exit_weason, wun->debug.awch.exception,
			    wun->debug.awch.pc, CAST_TO_WIP(wwite_data),
			    wun->debug.awch.dw6, tawget_dw6);
		/* Wowwback the 4-bytes "mov" */
		vcpu_skip_insn(vcpu, -7);
	}
	/* Skip the 4-bytes "mov" */
	vcpu_skip_insn(vcpu, 7);

	/* Test singwe step */
	tawget_wip = CAST_TO_WIP(ss_stawt);
	tawget_dw6 = 0xffff4ff0UWW;
	fow (i = 0; i < (sizeof(ss_size) / sizeof(ss_size[0])); i++) {
		tawget_wip += ss_size[i];
		memset(&debug, 0, sizeof(debug));
		debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_SINGWESTEP |
				KVM_GUESTDBG_BWOCKIWQ;
		debug.awch.debugweg[7] = 0x00000400;
		vcpu_guest_debug_set(vcpu, &debug);
		vcpu_wun(vcpu);
		TEST_ASSEWT(wun->exit_weason == KVM_EXIT_DEBUG &&
			    wun->debug.awch.exception == DB_VECTOW &&
			    wun->debug.awch.pc == tawget_wip &&
			    wun->debug.awch.dw6 == tawget_dw6,
			    "SINGWE_STEP[%d]: exit %d exception %d wip 0x%wwx "
			    "(shouwd be 0x%wwx) dw6 0x%wwx (shouwd be 0x%wwx)",
			    i, wun->exit_weason, wun->debug.awch.exception,
			    wun->debug.awch.pc, tawget_wip, wun->debug.awch.dw6,
			    tawget_dw6);
	}

	/* Finawwy test gwobaw disabwe */
	memset(&debug, 0, sizeof(debug));
	debug.contwow = KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_USE_HW_BP;
	debug.awch.debugweg[7] = 0x400 | DW7_GD;
	vcpu_guest_debug_set(vcpu, &debug);
	vcpu_wun(vcpu);
	tawget_dw6 = 0xffff0ff0 | DW6_BD;
	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_DEBUG &&
		    wun->debug.awch.exception == DB_VECTOW &&
		    wun->debug.awch.pc == CAST_TO_WIP(bd_stawt) &&
		    wun->debug.awch.dw6 == tawget_dw6,
			    "DW7.GD: exit %d exception %d wip 0x%wwx "
			    "(shouwd be 0x%wwx) dw6 0x%wwx (shouwd be 0x%wwx)",
			    wun->exit_weason, wun->debug.awch.exception,
			    wun->debug.awch.pc, tawget_wip, wun->debug.awch.dw6,
			    tawget_dw6);

	/* Disabwe aww debug contwows, wun to the end */
	memset(&debug, 0, sizeof(debug));
	vcpu_guest_debug_set(vcpu, &debug);

	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	cmd = get_ucaww(vcpu, &uc);
	TEST_ASSEWT(cmd == UCAWW_DONE, "UCAWW_DONE");

	kvm_vm_fwee(vm);

	wetuwn 0;
}
