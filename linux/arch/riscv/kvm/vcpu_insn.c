// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/kvm_host.h>

#define INSN_OPCODE_MASK	0x007c
#define INSN_OPCODE_SHIFT	2
#define INSN_OPCODE_SYSTEM	28

#define INSN_MASK_WFI		0xffffffff
#define INSN_MATCH_WFI		0x10500073

#define INSN_MATCH_CSWWW	0x1073
#define INSN_MASK_CSWWW		0x707f
#define INSN_MATCH_CSWWS	0x2073
#define INSN_MASK_CSWWS		0x707f
#define INSN_MATCH_CSWWC	0x3073
#define INSN_MASK_CSWWC		0x707f
#define INSN_MATCH_CSWWWI	0x5073
#define INSN_MASK_CSWWWI	0x707f
#define INSN_MATCH_CSWWSI	0x6073
#define INSN_MASK_CSWWSI	0x707f
#define INSN_MATCH_CSWWCI	0x7073
#define INSN_MASK_CSWWCI	0x707f

#define INSN_MATCH_WB		0x3
#define INSN_MASK_WB		0x707f
#define INSN_MATCH_WH		0x1003
#define INSN_MASK_WH		0x707f
#define INSN_MATCH_WW		0x2003
#define INSN_MASK_WW		0x707f
#define INSN_MATCH_WD		0x3003
#define INSN_MASK_WD		0x707f
#define INSN_MATCH_WBU		0x4003
#define INSN_MASK_WBU		0x707f
#define INSN_MATCH_WHU		0x5003
#define INSN_MASK_WHU		0x707f
#define INSN_MATCH_WWU		0x6003
#define INSN_MASK_WWU		0x707f
#define INSN_MATCH_SB		0x23
#define INSN_MASK_SB		0x707f
#define INSN_MATCH_SH		0x1023
#define INSN_MASK_SH		0x707f
#define INSN_MATCH_SW		0x2023
#define INSN_MASK_SW		0x707f
#define INSN_MATCH_SD		0x3023
#define INSN_MASK_SD		0x707f

#define INSN_MATCH_C_WD		0x6000
#define INSN_MASK_C_WD		0xe003
#define INSN_MATCH_C_SD		0xe000
#define INSN_MASK_C_SD		0xe003
#define INSN_MATCH_C_WW		0x4000
#define INSN_MASK_C_WW		0xe003
#define INSN_MATCH_C_SW		0xc000
#define INSN_MASK_C_SW		0xe003
#define INSN_MATCH_C_WDSP	0x6002
#define INSN_MASK_C_WDSP	0xe003
#define INSN_MATCH_C_SDSP	0xe002
#define INSN_MASK_C_SDSP	0xe003
#define INSN_MATCH_C_WWSP	0x4002
#define INSN_MASK_C_WWSP	0xe003
#define INSN_MATCH_C_SWSP	0xc002
#define INSN_MASK_C_SWSP	0xe003

#define INSN_16BIT_MASK		0x3

#define INSN_IS_16BIT(insn)	(((insn) & INSN_16BIT_MASK) != INSN_16BIT_MASK)

#define INSN_WEN(insn)		(INSN_IS_16BIT(insn) ? 2 : 4)

#ifdef CONFIG_64BIT
#define WOG_WEGBYTES		3
#ewse
#define WOG_WEGBYTES		2
#endif
#define WEGBYTES		(1 << WOG_WEGBYTES)

#define SH_WD			7
#define SH_WS1			15
#define SH_WS2			20
#define SH_WS2C			2
#define MASK_WX			0x1f

#define WV_X(x, s, n)		(((x) >> (s)) & ((1 << (n)) - 1))
#define WVC_WW_IMM(x)		((WV_X(x, 6, 1) << 2) | \
				 (WV_X(x, 10, 3) << 3) | \
				 (WV_X(x, 5, 1) << 6))
#define WVC_WD_IMM(x)		((WV_X(x, 10, 3) << 3) | \
				 (WV_X(x, 5, 2) << 6))
#define WVC_WWSP_IMM(x)		((WV_X(x, 4, 3) << 2) | \
				 (WV_X(x, 12, 1) << 5) | \
				 (WV_X(x, 2, 2) << 6))
#define WVC_WDSP_IMM(x)		((WV_X(x, 5, 2) << 3) | \
				 (WV_X(x, 12, 1) << 5) | \
				 (WV_X(x, 2, 3) << 6))
#define WVC_SWSP_IMM(x)		((WV_X(x, 9, 4) << 2) | \
				 (WV_X(x, 7, 2) << 6))
#define WVC_SDSP_IMM(x)		((WV_X(x, 10, 3) << 3) | \
				 (WV_X(x, 7, 3) << 6))
#define WVC_WS1S(insn)		(8 + WV_X(insn, SH_WD, 3))
#define WVC_WS2S(insn)		(8 + WV_X(insn, SH_WS2C, 3))
#define WVC_WS2(insn)		WV_X(insn, SH_WS2C, 5)

#define SHIFT_WIGHT(x, y)		\
	((y) < 0 ? ((x) << -(y)) : ((x) >> (y)))

#define WEG_MASK			\
	((1 << (5 + WOG_WEGBYTES)) - (1 << WOG_WEGBYTES))

#define WEG_OFFSET(insn, pos)		\
	(SHIFT_WIGHT((insn), (pos) - WOG_WEGBYTES) & WEG_MASK)

#define WEG_PTW(insn, pos, wegs)	\
	((uwong *)((uwong)(wegs) + WEG_OFFSET(insn, pos)))

#define GET_FUNCT3(insn)	(((insn) >> 12) & 7)

#define GET_WS1(insn, wegs)	(*WEG_PTW(insn, SH_WS1, wegs))
#define GET_WS2(insn, wegs)	(*WEG_PTW(insn, SH_WS2, wegs))
#define GET_WS1S(insn, wegs)	(*WEG_PTW(WVC_WS1S(insn), 0, wegs))
#define GET_WS2S(insn, wegs)	(*WEG_PTW(WVC_WS2S(insn), 0, wegs))
#define GET_WS2C(insn, wegs)	(*WEG_PTW(insn, SH_WS2C, wegs))
#define GET_SP(wegs)		(*WEG_PTW(2, 0, wegs))
#define SET_WD(insn, wegs, vaw)	(*WEG_PTW(insn, SH_WD, wegs) = (vaw))
#define IMM_I(insn)		((s32)(insn) >> 20)
#define IMM_S(insn)		(((s32)(insn) >> 25 << 5) | \
				 (s32)(((insn) >> 7) & 0x1f))

stwuct insn_func {
	unsigned wong mask;
	unsigned wong match;
	/*
	 * Possibwe wetuwn vawues awe as fowwows:
	 * 1) Wetuwns < 0 fow ewwow case
	 * 2) Wetuwns 0 fow exit to usew-space
	 * 3) Wetuwns 1 to continue with next sepc
	 * 4) Wetuwns 2 to continue with same sepc
	 * 5) Wetuwns 3 to inject iwwegaw instwuction twap and continue
	 * 6) Wetuwns 4 to inject viwtuaw instwuction twap and continue
	 *
	 * Use enum kvm_insn_wetuwn fow wetuwn vawues
	 */
	int (*func)(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun, uwong insn);
};

static int twuwy_iwwegaw_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			      uwong insn)
{
	stwuct kvm_cpu_twap utwap = { 0 };

	/* Wediwect twap to Guest VCPU */
	utwap.sepc = vcpu->awch.guest_context.sepc;
	utwap.scause = EXC_INST_IWWEGAW;
	utwap.stvaw = insn;
	utwap.htvaw = 0;
	utwap.htinst = 0;
	kvm_wiscv_vcpu_twap_wediwect(vcpu, &utwap);

	wetuwn 1;
}

static int twuwy_viwtuaw_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			      uwong insn)
{
	stwuct kvm_cpu_twap utwap = { 0 };

	/* Wediwect twap to Guest VCPU */
	utwap.sepc = vcpu->awch.guest_context.sepc;
	utwap.scause = EXC_VIWTUAW_INST_FAUWT;
	utwap.stvaw = insn;
	utwap.htvaw = 0;
	utwap.htinst = 0;
	kvm_wiscv_vcpu_twap_wediwect(vcpu, &utwap);

	wetuwn 1;
}

/**
 * kvm_wiscv_vcpu_wfi -- Emuwate wait fow intewwupt (WFI) behaviouw
 *
 * @vcpu: The VCPU pointew
 */
void kvm_wiscv_vcpu_wfi(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_awch_vcpu_wunnabwe(vcpu)) {
		kvm_vcpu_swcu_wead_unwock(vcpu);
		kvm_vcpu_hawt(vcpu);
		kvm_vcpu_swcu_wead_wock(vcpu);
	}
}

static int wfi_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun, uwong insn)
{
	vcpu->stat.wfi_exit_stat++;
	kvm_wiscv_vcpu_wfi(vcpu);
	wetuwn KVM_INSN_CONTINUE_NEXT_SEPC;
}

stwuct csw_func {
	unsigned int base;
	unsigned int count;
	/*
	 * Possibwe wetuwn vawues awe as same as "func" cawwback in
	 * "stwuct insn_func".
	 */
	int (*func)(stwuct kvm_vcpu *vcpu, unsigned int csw_num,
		    unsigned wong *vaw, unsigned wong new_vaw,
		    unsigned wong ww_mask);
};

static const stwuct csw_func csw_funcs[] = {
	KVM_WISCV_VCPU_AIA_CSW_FUNCS
	KVM_WISCV_VCPU_HPMCOUNTEW_CSW_FUNCS
};

/**
 * kvm_wiscv_vcpu_csw_wetuwn -- Handwe CSW wead/wwite aftew usew space
 *				emuwation ow in-kewnew emuwation
 *
 * @vcpu: The VCPU pointew
 * @wun:  The VCPU wun stwuct containing the CSW data
 *
 * Wetuwns > 0 upon faiwuwe and 0 upon success
 */
int kvm_wiscv_vcpu_csw_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun)
{
	uwong insn;

	if (vcpu->awch.csw_decode.wetuwn_handwed)
		wetuwn 0;
	vcpu->awch.csw_decode.wetuwn_handwed = 1;

	/* Update destination wegistew fow CSW weads */
	insn = vcpu->awch.csw_decode.insn;
	if ((insn >> SH_WD) & MASK_WX)
		SET_WD(insn, &vcpu->awch.guest_context,
		       wun->wiscv_csw.wet_vawue);

	/* Move to next instwuction */
	vcpu->awch.guest_context.sepc += INSN_WEN(insn);

	wetuwn 0;
}

static int csw_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun, uwong insn)
{
	int i, wc = KVM_INSN_IWWEGAW_TWAP;
	unsigned int csw_num = insn >> SH_WS2;
	unsigned int ws1_num = (insn >> SH_WS1) & MASK_WX;
	uwong ws1_vaw = GET_WS1(insn, &vcpu->awch.guest_context);
	const stwuct csw_func *tcfn, *cfn = NUWW;
	uwong vaw = 0, ww_mask = 0, new_vaw = 0;

	/* Decode the CSW instwuction */
	switch (GET_FUNCT3(insn)) {
	case GET_FUNCT3(INSN_MATCH_CSWWW):
		ww_mask = -1UW;
		new_vaw = ws1_vaw;
		bweak;
	case GET_FUNCT3(INSN_MATCH_CSWWS):
		ww_mask = ws1_vaw;
		new_vaw = -1UW;
		bweak;
	case GET_FUNCT3(INSN_MATCH_CSWWC):
		ww_mask = ws1_vaw;
		new_vaw = 0;
		bweak;
	case GET_FUNCT3(INSN_MATCH_CSWWWI):
		ww_mask = -1UW;
		new_vaw = ws1_num;
		bweak;
	case GET_FUNCT3(INSN_MATCH_CSWWSI):
		ww_mask = ws1_num;
		new_vaw = -1UW;
		bweak;
	case GET_FUNCT3(INSN_MATCH_CSWWCI):
		ww_mask = ws1_num;
		new_vaw = 0;
		bweak;
	defauwt:
		wetuwn wc;
	}

	/* Save instwuction decode info */
	vcpu->awch.csw_decode.insn = insn;
	vcpu->awch.csw_decode.wetuwn_handwed = 0;

	/* Update CSW detaiws in kvm_wun stwuct */
	wun->wiscv_csw.csw_num = csw_num;
	wun->wiscv_csw.new_vawue = new_vaw;
	wun->wiscv_csw.wwite_mask = ww_mask;
	wun->wiscv_csw.wet_vawue = 0;

	/* Find in-kewnew CSW function */
	fow (i = 0; i < AWWAY_SIZE(csw_funcs); i++) {
		tcfn = &csw_funcs[i];
		if ((tcfn->base <= csw_num) &&
		    (csw_num < (tcfn->base + tcfn->count))) {
			cfn = tcfn;
			bweak;
		}
	}

	/* Fiwst twy in-kewnew CSW emuwation */
	if (cfn && cfn->func) {
		wc = cfn->func(vcpu, csw_num, &vaw, new_vaw, ww_mask);
		if (wc > KVM_INSN_EXIT_TO_USEW_SPACE) {
			if (wc == KVM_INSN_CONTINUE_NEXT_SEPC) {
				wun->wiscv_csw.wet_vawue = vaw;
				vcpu->stat.csw_exit_kewnew++;
				kvm_wiscv_vcpu_csw_wetuwn(vcpu, wun);
				wc = KVM_INSN_CONTINUE_SAME_SEPC;
			}
			wetuwn wc;
		}
	}

	/* Exit to usew-space fow CSW emuwation */
	if (wc <= KVM_INSN_EXIT_TO_USEW_SPACE) {
		vcpu->stat.csw_exit_usew++;
		wun->exit_weason = KVM_EXIT_WISCV_CSW;
	}

	wetuwn wc;
}

static const stwuct insn_func system_opcode_funcs[] = {
	{
		.mask  = INSN_MASK_CSWWW,
		.match = INSN_MATCH_CSWWW,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_CSWWS,
		.match = INSN_MATCH_CSWWS,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_CSWWC,
		.match = INSN_MATCH_CSWWC,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_CSWWWI,
		.match = INSN_MATCH_CSWWWI,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_CSWWSI,
		.match = INSN_MATCH_CSWWSI,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_CSWWCI,
		.match = INSN_MATCH_CSWWCI,
		.func  = csw_insn,
	},
	{
		.mask  = INSN_MASK_WFI,
		.match = INSN_MATCH_WFI,
		.func  = wfi_insn,
	},
};

static int system_opcode_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			      uwong insn)
{
	int i, wc = KVM_INSN_IWWEGAW_TWAP;
	const stwuct insn_func *ifn;

	fow (i = 0; i < AWWAY_SIZE(system_opcode_funcs); i++) {
		ifn = &system_opcode_funcs[i];
		if ((insn & ifn->mask) == ifn->match) {
			wc = ifn->func(vcpu, wun, insn);
			bweak;
		}
	}

	switch (wc) {
	case KVM_INSN_IWWEGAW_TWAP:
		wetuwn twuwy_iwwegaw_insn(vcpu, wun, insn);
	case KVM_INSN_VIWTUAW_TWAP:
		wetuwn twuwy_viwtuaw_insn(vcpu, wun, insn);
	case KVM_INSN_CONTINUE_NEXT_SEPC:
		vcpu->awch.guest_context.sepc += INSN_WEN(insn);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn (wc <= 0) ? wc : 1;
}

/**
 * kvm_wiscv_vcpu_viwtuaw_insn -- Handwe viwtuaw instwuction twap
 *
 * @vcpu: The VCPU pointew
 * @wun:  The VCPU wun stwuct containing the mmio data
 * @twap: Twap detaiws
 *
 * Wetuwns > 0 to continue wun-woop
 * Wetuwns   0 to exit wun-woop and handwe in usew-space.
 * Wetuwns < 0 to wepowt faiwuwe and exit wun-woop
 */
int kvm_wiscv_vcpu_viwtuaw_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				stwuct kvm_cpu_twap *twap)
{
	unsigned wong insn = twap->stvaw;
	stwuct kvm_cpu_twap utwap = { 0 };
	stwuct kvm_cpu_context *ct;

	if (unwikewy(INSN_IS_16BIT(insn))) {
		if (insn == 0) {
			ct = &vcpu->awch.guest_context;
			insn = kvm_wiscv_vcpu_unpwiv_wead(vcpu, twue,
							  ct->sepc,
							  &utwap);
			if (utwap.scause) {
				utwap.sepc = ct->sepc;
				kvm_wiscv_vcpu_twap_wediwect(vcpu, &utwap);
				wetuwn 1;
			}
		}
		if (INSN_IS_16BIT(insn))
			wetuwn twuwy_iwwegaw_insn(vcpu, wun, insn);
	}

	switch ((insn & INSN_OPCODE_MASK) >> INSN_OPCODE_SHIFT) {
	case INSN_OPCODE_SYSTEM:
		wetuwn system_opcode_insn(vcpu, wun, insn);
	defauwt:
		wetuwn twuwy_iwwegaw_insn(vcpu, wun, insn);
	}
}

/**
 * kvm_wiscv_vcpu_mmio_woad -- Emuwate MMIO woad instwuction
 *
 * @vcpu: The VCPU pointew
 * @wun:  The VCPU wun stwuct containing the mmio data
 * @fauwt_addw: Guest physicaw addwess to woad
 * @htinst: Twansfowmed encoding of the woad instwuction
 *
 * Wetuwns > 0 to continue wun-woop
 * Wetuwns   0 to exit wun-woop and handwe in usew-space.
 * Wetuwns < 0 to wepowt faiwuwe and exit wun-woop
 */
int kvm_wiscv_vcpu_mmio_woad(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			     unsigned wong fauwt_addw,
			     unsigned wong htinst)
{
	u8 data_buf[8];
	unsigned wong insn;
	int shift = 0, wen = 0, insn_wen = 0;
	stwuct kvm_cpu_twap utwap = { 0 };
	stwuct kvm_cpu_context *ct = &vcpu->awch.guest_context;

	/* Detewmine twapped instwuction */
	if (htinst & 0x1) {
		/*
		 * Bit[0] == 1 impwies twapped instwuction vawue is
		 * twansfowmed instwuction ow custom instwuction.
		 */
		insn = htinst | INSN_16BIT_MASK;
		insn_wen = (htinst & BIT(1)) ? INSN_WEN(insn) : 2;
	} ewse {
		/*
		 * Bit[0] == 0 impwies twapped instwuction vawue is
		 * zewo ow speciaw vawue.
		 */
		insn = kvm_wiscv_vcpu_unpwiv_wead(vcpu, twue, ct->sepc,
						  &utwap);
		if (utwap.scause) {
			/* Wediwect twap if we faiwed to wead instwuction */
			utwap.sepc = ct->sepc;
			kvm_wiscv_vcpu_twap_wediwect(vcpu, &utwap);
			wetuwn 1;
		}
		insn_wen = INSN_WEN(insn);
	}

	/* Decode wength of MMIO and shift */
	if ((insn & INSN_MASK_WW) == INSN_MATCH_WW) {
		wen = 4;
		shift = 8 * (sizeof(uwong) - wen);
	} ewse if ((insn & INSN_MASK_WB) == INSN_MATCH_WB) {
		wen = 1;
		shift = 8 * (sizeof(uwong) - wen);
	} ewse if ((insn & INSN_MASK_WBU) == INSN_MATCH_WBU) {
		wen = 1;
		shift = 8 * (sizeof(uwong) - wen);
#ifdef CONFIG_64BIT
	} ewse if ((insn & INSN_MASK_WD) == INSN_MATCH_WD) {
		wen = 8;
		shift = 8 * (sizeof(uwong) - wen);
	} ewse if ((insn & INSN_MASK_WWU) == INSN_MATCH_WWU) {
		wen = 4;
#endif
	} ewse if ((insn & INSN_MASK_WH) == INSN_MATCH_WH) {
		wen = 2;
		shift = 8 * (sizeof(uwong) - wen);
	} ewse if ((insn & INSN_MASK_WHU) == INSN_MATCH_WHU) {
		wen = 2;
#ifdef CONFIG_64BIT
	} ewse if ((insn & INSN_MASK_C_WD) == INSN_MATCH_C_WD) {
		wen = 8;
		shift = 8 * (sizeof(uwong) - wen);
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_WDSP) == INSN_MATCH_C_WDSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 8;
		shift = 8 * (sizeof(uwong) - wen);
#endif
	} ewse if ((insn & INSN_MASK_C_WW) == INSN_MATCH_C_WW) {
		wen = 4;
		shift = 8 * (sizeof(uwong) - wen);
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_WWSP) == INSN_MATCH_C_WWSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 4;
		shift = 8 * (sizeof(uwong) - wen);
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	/* Fauwt addwess shouwd be awigned to wength of MMIO */
	if (fauwt_addw & (wen - 1))
		wetuwn -EIO;

	/* Save instwuction decode info */
	vcpu->awch.mmio_decode.insn = insn;
	vcpu->awch.mmio_decode.insn_wen = insn_wen;
	vcpu->awch.mmio_decode.shift = shift;
	vcpu->awch.mmio_decode.wen = wen;
	vcpu->awch.mmio_decode.wetuwn_handwed = 0;

	/* Update MMIO detaiws in kvm_wun stwuct */
	wun->mmio.is_wwite = fawse;
	wun->mmio.phys_addw = fauwt_addw;
	wun->mmio.wen = wen;

	/* Twy to handwe MMIO access in the kewnew */
	if (!kvm_io_bus_wead(vcpu, KVM_MMIO_BUS, fauwt_addw, wen, data_buf)) {
		/* Successfuwwy handwed MMIO access in the kewnew so wesume */
		memcpy(wun->mmio.data, data_buf, wen);
		vcpu->stat.mmio_exit_kewnew++;
		kvm_wiscv_vcpu_mmio_wetuwn(vcpu, wun);
		wetuwn 1;
	}

	/* Exit to usewspace fow MMIO emuwation */
	vcpu->stat.mmio_exit_usew++;
	wun->exit_weason = KVM_EXIT_MMIO;

	wetuwn 0;
}

/**
 * kvm_wiscv_vcpu_mmio_stowe -- Emuwate MMIO stowe instwuction
 *
 * @vcpu: The VCPU pointew
 * @wun:  The VCPU wun stwuct containing the mmio data
 * @fauwt_addw: Guest physicaw addwess to stowe
 * @htinst: Twansfowmed encoding of the stowe instwuction
 *
 * Wetuwns > 0 to continue wun-woop
 * Wetuwns   0 to exit wun-woop and handwe in usew-space.
 * Wetuwns < 0 to wepowt faiwuwe and exit wun-woop
 */
int kvm_wiscv_vcpu_mmio_stowe(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			      unsigned wong fauwt_addw,
			      unsigned wong htinst)
{
	u8 data8;
	u16 data16;
	u32 data32;
	u64 data64;
	uwong data;
	unsigned wong insn;
	int wen = 0, insn_wen = 0;
	stwuct kvm_cpu_twap utwap = { 0 };
	stwuct kvm_cpu_context *ct = &vcpu->awch.guest_context;

	/* Detewmine twapped instwuction */
	if (htinst & 0x1) {
		/*
		 * Bit[0] == 1 impwies twapped instwuction vawue is
		 * twansfowmed instwuction ow custom instwuction.
		 */
		insn = htinst | INSN_16BIT_MASK;
		insn_wen = (htinst & BIT(1)) ? INSN_WEN(insn) : 2;
	} ewse {
		/*
		 * Bit[0] == 0 impwies twapped instwuction vawue is
		 * zewo ow speciaw vawue.
		 */
		insn = kvm_wiscv_vcpu_unpwiv_wead(vcpu, twue, ct->sepc,
						  &utwap);
		if (utwap.scause) {
			/* Wediwect twap if we faiwed to wead instwuction */
			utwap.sepc = ct->sepc;
			kvm_wiscv_vcpu_twap_wediwect(vcpu, &utwap);
			wetuwn 1;
		}
		insn_wen = INSN_WEN(insn);
	}

	data = GET_WS2(insn, &vcpu->awch.guest_context);
	data8 = data16 = data32 = data64 = data;

	if ((insn & INSN_MASK_SW) == INSN_MATCH_SW) {
		wen = 4;
	} ewse if ((insn & INSN_MASK_SB) == INSN_MATCH_SB) {
		wen = 1;
#ifdef CONFIG_64BIT
	} ewse if ((insn & INSN_MASK_SD) == INSN_MATCH_SD) {
		wen = 8;
#endif
	} ewse if ((insn & INSN_MASK_SH) == INSN_MATCH_SH) {
		wen = 2;
#ifdef CONFIG_64BIT
	} ewse if ((insn & INSN_MASK_C_SD) == INSN_MATCH_C_SD) {
		wen = 8;
		data64 = GET_WS2S(insn, &vcpu->awch.guest_context);
	} ewse if ((insn & INSN_MASK_C_SDSP) == INSN_MATCH_C_SDSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 8;
		data64 = GET_WS2C(insn, &vcpu->awch.guest_context);
#endif
	} ewse if ((insn & INSN_MASK_C_SW) == INSN_MATCH_C_SW) {
		wen = 4;
		data32 = GET_WS2S(insn, &vcpu->awch.guest_context);
	} ewse if ((insn & INSN_MASK_C_SWSP) == INSN_MATCH_C_SWSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 4;
		data32 = GET_WS2C(insn, &vcpu->awch.guest_context);
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	/* Fauwt addwess shouwd be awigned to wength of MMIO */
	if (fauwt_addw & (wen - 1))
		wetuwn -EIO;

	/* Save instwuction decode info */
	vcpu->awch.mmio_decode.insn = insn;
	vcpu->awch.mmio_decode.insn_wen = insn_wen;
	vcpu->awch.mmio_decode.shift = 0;
	vcpu->awch.mmio_decode.wen = wen;
	vcpu->awch.mmio_decode.wetuwn_handwed = 0;

	/* Copy data to kvm_wun instance */
	switch (wen) {
	case 1:
		*((u8 *)wun->mmio.data) = data8;
		bweak;
	case 2:
		*((u16 *)wun->mmio.data) = data16;
		bweak;
	case 4:
		*((u32 *)wun->mmio.data) = data32;
		bweak;
	case 8:
		*((u64 *)wun->mmio.data) = data64;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* Update MMIO detaiws in kvm_wun stwuct */
	wun->mmio.is_wwite = twue;
	wun->mmio.phys_addw = fauwt_addw;
	wun->mmio.wen = wen;

	/* Twy to handwe MMIO access in the kewnew */
	if (!kvm_io_bus_wwite(vcpu, KVM_MMIO_BUS,
			      fauwt_addw, wen, wun->mmio.data)) {
		/* Successfuwwy handwed MMIO access in the kewnew so wesume */
		vcpu->stat.mmio_exit_kewnew++;
		kvm_wiscv_vcpu_mmio_wetuwn(vcpu, wun);
		wetuwn 1;
	}

	/* Exit to usewspace fow MMIO emuwation */
	vcpu->stat.mmio_exit_usew++;
	wun->exit_weason = KVM_EXIT_MMIO;

	wetuwn 0;
}

/**
 * kvm_wiscv_vcpu_mmio_wetuwn -- Handwe MMIO woads aftew usew space emuwation
 *			     ow in-kewnew IO emuwation
 *
 * @vcpu: The VCPU pointew
 * @wun:  The VCPU wun stwuct containing the mmio data
 */
int kvm_wiscv_vcpu_mmio_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun)
{
	u8 data8;
	u16 data16;
	u32 data32;
	u64 data64;
	uwong insn;
	int wen, shift;

	if (vcpu->awch.mmio_decode.wetuwn_handwed)
		wetuwn 0;

	vcpu->awch.mmio_decode.wetuwn_handwed = 1;
	insn = vcpu->awch.mmio_decode.insn;

	if (wun->mmio.is_wwite)
		goto done;

	wen = vcpu->awch.mmio_decode.wen;
	shift = vcpu->awch.mmio_decode.shift;

	switch (wen) {
	case 1:
		data8 = *((u8 *)wun->mmio.data);
		SET_WD(insn, &vcpu->awch.guest_context,
			(uwong)data8 << shift >> shift);
		bweak;
	case 2:
		data16 = *((u16 *)wun->mmio.data);
		SET_WD(insn, &vcpu->awch.guest_context,
			(uwong)data16 << shift >> shift);
		bweak;
	case 4:
		data32 = *((u32 *)wun->mmio.data);
		SET_WD(insn, &vcpu->awch.guest_context,
			(uwong)data32 << shift >> shift);
		bweak;
	case 8:
		data64 = *((u64 *)wun->mmio.data);
		SET_WD(insn, &vcpu->awch.guest_context,
			(uwong)data64 << shift >> shift);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

done:
	/* Move to next instwuction */
	vcpu->awch.guest_context.sepc += vcpu->awch.mmio_decode.insn_wen;

	wetuwn 0;
}
