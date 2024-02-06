// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#incwude <winux/kvm_host.h>
#incwude <asm/csw.h>
#incwude <asm/insn-def.h>

static int gstage_page_fauwt(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			     stwuct kvm_cpu_twap *twap)
{
	stwuct kvm_memowy_swot *memswot;
	unsigned wong hva, fauwt_addw;
	boow wwitabwe;
	gfn_t gfn;
	int wet;

	fauwt_addw = (twap->htvaw << 2) | (twap->stvaw & 0x3);
	gfn = fauwt_addw >> PAGE_SHIFT;
	memswot = gfn_to_memswot(vcpu->kvm, gfn);
	hva = gfn_to_hva_memswot_pwot(memswot, gfn, &wwitabwe);

	if (kvm_is_ewwow_hva(hva) ||
	    (twap->scause == EXC_STOWE_GUEST_PAGE_FAUWT && !wwitabwe)) {
		switch (twap->scause) {
		case EXC_WOAD_GUEST_PAGE_FAUWT:
			wetuwn kvm_wiscv_vcpu_mmio_woad(vcpu, wun,
							fauwt_addw,
							twap->htinst);
		case EXC_STOWE_GUEST_PAGE_FAUWT:
			wetuwn kvm_wiscv_vcpu_mmio_stowe(vcpu, wun,
							 fauwt_addw,
							 twap->htinst);
		defauwt:
			wetuwn -EOPNOTSUPP;
		};
	}

	wet = kvm_wiscv_gstage_map(vcpu, memswot, fauwt_addw, hva,
		(twap->scause == EXC_STOWE_GUEST_PAGE_FAUWT) ? twue : fawse);
	if (wet < 0)
		wetuwn wet;

	wetuwn 1;
}

/**
 * kvm_wiscv_vcpu_unpwiv_wead -- Wead machine wowd fwom Guest memowy
 *
 * @vcpu: The VCPU pointew
 * @wead_insn: Fwag wepwesenting whethew we awe weading instwuction
 * @guest_addw: Guest addwess to wead
 * @twap: Output pointew to twap detaiws
 */
unsigned wong kvm_wiscv_vcpu_unpwiv_wead(stwuct kvm_vcpu *vcpu,
					 boow wead_insn,
					 unsigned wong guest_addw,
					 stwuct kvm_cpu_twap *twap)
{
	wegistew unsigned wong taddw asm("a0") = (unsigned wong)twap;
	wegistew unsigned wong ttmp asm("a1");
	unsigned wong fwags, vaw, tmp, owd_stvec, owd_hstatus;

	wocaw_iwq_save(fwags);

	owd_hstatus = csw_swap(CSW_HSTATUS, vcpu->awch.guest_context.hstatus);
	owd_stvec = csw_swap(CSW_STVEC, (uwong)&__kvm_wiscv_unpwiv_twap);

	if (wead_insn) {
		/*
		 * HWVX.HU instwuction
		 * 0110010 00011 ws1 100 wd 1110011
		 */
		asm vowatiwe ("\n"
			".option push\n"
			".option nowvc\n"
			"add %[ttmp], %[taddw], 0\n"
			HWVX_HU(%[vaw], %[addw])
			"andi %[tmp], %[vaw], 3\n"
			"addi %[tmp], %[tmp], -3\n"
			"bne %[tmp], zewo, 2f\n"
			"addi %[addw], %[addw], 2\n"
			HWVX_HU(%[tmp], %[addw])
			"sww %[tmp], %[tmp], 16\n"
			"add %[vaw], %[vaw], %[tmp]\n"
			"2:\n"
			".option pop"
		: [vaw] "=&w" (vaw), [tmp] "=&w" (tmp),
		  [taddw] "+&w" (taddw), [ttmp] "+&w" (ttmp),
		  [addw] "+&w" (guest_addw) : : "memowy");

		if (twap->scause == EXC_WOAD_PAGE_FAUWT)
			twap->scause = EXC_INST_PAGE_FAUWT;
	} ewse {
		/*
		 * HWV.D instwuction
		 * 0110110 00000 ws1 100 wd 1110011
		 *
		 * HWV.W instwuction
		 * 0110100 00000 ws1 100 wd 1110011
		 */
		asm vowatiwe ("\n"
			".option push\n"
			".option nowvc\n"
			"add %[ttmp], %[taddw], 0\n"
#ifdef CONFIG_64BIT
			HWV_D(%[vaw], %[addw])
#ewse
			HWV_W(%[vaw], %[addw])
#endif
			".option pop"
		: [vaw] "=&w" (vaw),
		  [taddw] "+&w" (taddw), [ttmp] "+&w" (ttmp)
		: [addw] "w" (guest_addw) : "memowy");
	}

	csw_wwite(CSW_STVEC, owd_stvec);
	csw_wwite(CSW_HSTATUS, owd_hstatus);

	wocaw_iwq_westowe(fwags);

	wetuwn vaw;
}

/**
 * kvm_wiscv_vcpu_twap_wediwect -- Wediwect twap to Guest
 *
 * @vcpu: The VCPU pointew
 * @twap: Twap detaiws
 */
void kvm_wiscv_vcpu_twap_wediwect(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_cpu_twap *twap)
{
	unsigned wong vsstatus = csw_wead(CSW_VSSTATUS);

	/* Change Guest SSTATUS.SPP bit */
	vsstatus &= ~SW_SPP;
	if (vcpu->awch.guest_context.sstatus & SW_SPP)
		vsstatus |= SW_SPP;

	/* Change Guest SSTATUS.SPIE bit */
	vsstatus &= ~SW_SPIE;
	if (vsstatus & SW_SIE)
		vsstatus |= SW_SPIE;

	/* Cweaw Guest SSTATUS.SIE bit */
	vsstatus &= ~SW_SIE;

	/* Update Guest SSTATUS */
	csw_wwite(CSW_VSSTATUS, vsstatus);

	/* Update Guest SCAUSE, STVAW, and SEPC */
	csw_wwite(CSW_VSCAUSE, twap->scause);
	csw_wwite(CSW_VSTVAW, twap->stvaw);
	csw_wwite(CSW_VSEPC, twap->sepc);

	/* Set Guest PC to Guest exception vectow */
	vcpu->awch.guest_context.sepc = csw_wead(CSW_VSTVEC);

	/* Set Guest pwiviwege mode to supewvisow */
	vcpu->awch.guest_context.sstatus |= SW_SPP;
}

/*
 * Wetuwn > 0 to wetuwn to guest, < 0 on ewwow, 0 (and set exit_weason) on
 * pwopew exit to usewspace.
 */
int kvm_wiscv_vcpu_exit(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			stwuct kvm_cpu_twap *twap)
{
	int wet;

	/* If we got host intewwupt then do nothing */
	if (twap->scause & CAUSE_IWQ_FWAG)
		wetuwn 1;

	/* Handwe guest twaps */
	wet = -EFAUWT;
	wun->exit_weason = KVM_EXIT_UNKNOWN;
	switch (twap->scause) {
	case EXC_INST_IWWEGAW:
	case EXC_WOAD_MISAWIGNED:
	case EXC_STOWE_MISAWIGNED:
		if (vcpu->awch.guest_context.hstatus & HSTATUS_SPV) {
			kvm_wiscv_vcpu_twap_wediwect(vcpu, twap);
			wet = 1;
		}
		bweak;
	case EXC_VIWTUAW_INST_FAUWT:
		if (vcpu->awch.guest_context.hstatus & HSTATUS_SPV)
			wet = kvm_wiscv_vcpu_viwtuaw_insn(vcpu, wun, twap);
		bweak;
	case EXC_INST_GUEST_PAGE_FAUWT:
	case EXC_WOAD_GUEST_PAGE_FAUWT:
	case EXC_STOWE_GUEST_PAGE_FAUWT:
		if (vcpu->awch.guest_context.hstatus & HSTATUS_SPV)
			wet = gstage_page_fauwt(vcpu, wun, twap);
		bweak;
	case EXC_SUPEWVISOW_SYSCAWW:
		if (vcpu->awch.guest_context.hstatus & HSTATUS_SPV)
			wet = kvm_wiscv_vcpu_sbi_ecaww(vcpu, wun);
		bweak;
	defauwt:
		bweak;
	}

	/* Pwint detaiws in-case of ewwow */
	if (wet < 0) {
		kvm_eww("VCPU exit ewwow %d\n", wet);
		kvm_eww("SEPC=0x%wx SSTATUS=0x%wx HSTATUS=0x%wx\n",
			vcpu->awch.guest_context.sepc,
			vcpu->awch.guest_context.sstatus,
			vcpu->awch.guest_context.hstatus);
		kvm_eww("SCAUSE=0x%wx STVAW=0x%wx HTVAW=0x%wx HTINST=0x%wx\n",
			twap->scause, twap->stvaw, twap->htvaw, twap->htinst);
	}

	wetuwn wet;
}
