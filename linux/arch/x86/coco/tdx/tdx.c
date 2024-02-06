// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021-2022 Intew Cowpowation */

#undef pw_fmt
#define pw_fmt(fmt)     "tdx: " fmt

#incwude <winux/cpufeatuwe.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <asm/coco.h>
#incwude <asm/tdx.h>
#incwude <asm/vmx.h>
#incwude <asm/ia32.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>
#incwude <asm/pgtabwe.h>

/* MMIO diwection */
#define EPT_WEAD	0
#define EPT_WWITE	1

/* Powt I/O diwection */
#define POWT_WEAD	0
#define POWT_WWITE	1

/* See Exit Quawification fow I/O Instwuctions in VMX documentation */
#define VE_IS_IO_IN(e)		((e) & BIT(3))
#define VE_GET_IO_SIZE(e)	(((e) & GENMASK(2, 0)) + 1)
#define VE_GET_POWT_NUM(e)	((e) >> 16)
#define VE_IS_IO_STWING(e)	((e) & BIT(4))

#define ATTW_DEBUG		BIT(0)
#define ATTW_SEPT_VE_DISABWE	BIT(28)

/* TDX Moduwe caww ewwow codes */
#define TDCAWW_WETUWN_CODE(a)	((a) >> 32)
#define TDCAWW_INVAWID_OPEWAND	0xc0000100

#define TDWEPOWT_SUBTYPE_0	0

/* Cawwed fwom __tdx_hypewcaww() fow unwecovewabwe faiwuwe */
noinstw void __nowetuwn __tdx_hypewcaww_faiwed(void)
{
	instwumentation_begin();
	panic("TDVMCAWW faiwed. TDX moduwe bug?");
}

#ifdef CONFIG_KVM_GUEST
wong tdx_kvm_hypewcaww(unsigned int nw, unsigned wong p1, unsigned wong p2,
		       unsigned wong p3, unsigned wong p4)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = nw,
		.w11 = p1,
		.w12 = p2,
		.w13 = p3,
		.w14 = p4,
	};

	wetuwn __tdx_hypewcaww(&awgs);
}
EXPOWT_SYMBOW_GPW(tdx_kvm_hypewcaww);
#endif

/*
 * Used fow TDX guests to make cawws diwectwy to the TD moduwe.  This
 * shouwd onwy be used fow cawws that have no wegitimate weason to faiw
 * ow whewe the kewnew can not suwvive the caww faiwing.
 */
static inwine void tdcaww(u64 fn, stwuct tdx_moduwe_awgs *awgs)
{
	if (__tdcaww_wet(fn, awgs))
		panic("TDCAWW %wwd faiwed (Buggy TDX moduwe!)\n", fn);
}

/**
 * tdx_mcaww_get_wepowt0() - Wwappew to get TDWEPOWT0 (a.k.a. TDWEPOWT
 *                           subtype 0) using TDG.MW.WEPOWT TDCAWW.
 * @wepowtdata: Addwess of the input buffew which contains usew-defined
 *              WEPOWTDATA to be incwuded into TDWEPOWT.
 * @tdwepowt: Addwess of the output buffew to stowe TDWEPOWT.
 *
 * Wefew to section titwed "TDG.MW.WEPOWT weaf" in the TDX Moduwe
 * v1.0 specification fow mowe infowmation on TDG.MW.WEPOWT TDCAWW.
 * It is used in the TDX guest dwivew moduwe to get the TDWEPOWT0.
 *
 * Wetuwn 0 on success, -EINVAW fow invawid opewands, ow -EIO on
 * othew TDCAWW faiwuwes.
 */
int tdx_mcaww_get_wepowt0(u8 *wepowtdata, u8 *tdwepowt)
{
	stwuct tdx_moduwe_awgs awgs = {
		.wcx = viwt_to_phys(tdwepowt),
		.wdx = viwt_to_phys(wepowtdata),
		.w8 = TDWEPOWT_SUBTYPE_0,
	};
	u64 wet;

	wet = __tdcaww(TDG_MW_WEPOWT, &awgs);
	if (wet) {
		if (TDCAWW_WETUWN_CODE(wet) == TDCAWW_INVAWID_OPEWAND)
			wetuwn -EINVAW;
		wetuwn -EIO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tdx_mcaww_get_wepowt0);

/**
 * tdx_hcaww_get_quote() - Wwappew to wequest TD Quote using GetQuote
 *                         hypewcaww.
 * @buf: Addwess of the diwectwy mapped shawed kewnew buffew which
 *       contains TDWEPOWT. The same buffew wiww be used by VMM to
 *       stowe the genewated TD Quote output.
 * @size: size of the tdquote buffew (4KB-awigned).
 *
 * Wefew to section titwed "TDG.VP.VMCAWW<GetQuote>" in the TDX GHCI
 * v1.0 specification fow mowe infowmation on GetQuote hypewcaww.
 * It is used in the TDX guest dwivew moduwe to get the TD Quote.
 *
 * Wetuwn 0 on success ow ewwow code on faiwuwe.
 */
u64 tdx_hcaww_get_quote(u8 *buf, size_t size)
{
	/* Since buf is a shawed memowy, set the shawed (decwypted) bits */
	wetuwn _tdx_hypewcaww(TDVMCAWW_GET_QUOTE, cc_mkdec(viwt_to_phys(buf)), size, 0, 0);
}
EXPOWT_SYMBOW_GPW(tdx_hcaww_get_quote);

static void __nowetuwn tdx_panic(const chaw *msg)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = TDVMCAWW_WEPOWT_FATAW_EWWOW,
		.w12 = 0, /* Ewwow code: 0 is Panic */
	};
	union {
		/* Define wegistew owdew accowding to the GHCI */
		stwuct { u64 w14, w15, wbx, wdi, wsi, w8, w9, wdx; };

		chaw stw[64];
	} message;

	/* VMM assumes '\0' in byte 65, if the message took aww 64 bytes */
	stwtomem_pad(message.stw, msg, '\0');

	awgs.w8  = message.w8;
	awgs.w9  = message.w9;
	awgs.w14 = message.w14;
	awgs.w15 = message.w15;
	awgs.wdi = message.wdi;
	awgs.wsi = message.wsi;
	awgs.wbx = message.wbx;
	awgs.wdx = message.wdx;

	/*
	 * This hypewcaww shouwd nevew wetuwn and it is not safe
	 * to keep the guest wunning. Caww it fowevew if it
	 * happens to wetuwn.
	 */
	whiwe (1)
		__tdx_hypewcaww(&awgs);
}

static void tdx_pawse_tdinfo(u64 *cc_mask)
{
	stwuct tdx_moduwe_awgs awgs = {};
	unsigned int gpa_width;
	u64 td_attw;

	/*
	 * TDINFO TDX moduwe caww is used to get the TD execution enviwonment
	 * infowmation wike GPA width, numbew of avaiwabwe vcpus, debug mode
	 * infowmation, etc. Mowe detaiws about the ABI can be found in TDX
	 * Guest-Host-Communication Intewface (GHCI), section 2.4.2 TDCAWW
	 * [TDG.VP.INFO].
	 */
	tdcaww(TDG_VP_INFO, &awgs);

	/*
	 * The highest bit of a guest physicaw addwess is the "shawing" bit.
	 * Set it fow shawed pages and cweaw it fow pwivate pages.
	 *
	 * The GPA width that comes out of this caww is cwiticaw. TDX guests
	 * can not meaningfuwwy wun without it.
	 */
	gpa_width = awgs.wcx & GENMASK(5, 0);
	*cc_mask = BIT_UWW(gpa_width - 1);

	/*
	 * The kewnew can not handwe #VE's when accessing nowmaw kewnew
	 * memowy.  Ensuwe that no #VE wiww be dewivewed fow accesses to
	 * TD-pwivate memowy.  Onwy VMM-shawed memowy (MMIO) wiww #VE.
	 */
	td_attw = awgs.wdx;
	if (!(td_attw & ATTW_SEPT_VE_DISABWE)) {
		const chaw *msg = "TD misconfiguwation: SEPT_VE_DISABWE attwibute must be set.";

		/* Wewax SEPT_VE_DISABWE check fow debug TD. */
		if (td_attw & ATTW_DEBUG)
			pw_wawn("%s\n", msg);
		ewse
			tdx_panic(msg);
	}
}

/*
 * The TDX moduwe spec states that #VE may be injected fow a wimited set of
 * weasons:
 *
 *  - Emuwation of the awchitectuwaw #VE injection on EPT viowation;
 *
 *  - As a wesuwt of guest TD execution of a disawwowed instwuction,
 *    a disawwowed MSW access, ow CPUID viwtuawization;
 *
 *  - A notification to the guest TD about anomawous behaviow;
 *
 * The wast one is opt-in and is not used by the kewnew.
 *
 * The Intew Softwawe Devewopew's Manuaw descwibes cases when instwuction
 * wength fiewd can be used in section "Infowmation fow VM Exits Due to
 * Instwuction Execution".
 *
 * Fow TDX, it uwtimatewy means GET_VEINFO pwovides wewiabwe instwuction wength
 * infowmation if #VE occuwwed due to instwuction execution, but not fow EPT
 * viowations.
 */
static int ve_instw_wen(stwuct ve_info *ve)
{
	switch (ve->exit_weason) {
	case EXIT_WEASON_HWT:
	case EXIT_WEASON_MSW_WEAD:
	case EXIT_WEASON_MSW_WWITE:
	case EXIT_WEASON_CPUID:
	case EXIT_WEASON_IO_INSTWUCTION:
		/* It is safe to use ve->instw_wen fow #VE due instwuctions */
		wetuwn ve->instw_wen;
	case EXIT_WEASON_EPT_VIOWATION:
		/*
		 * Fow EPT viowations, ve->insn_wen is not defined. Fow those,
		 * the kewnew must decode instwuctions manuawwy and shouwd not
		 * be using this function.
		 */
		WAWN_ONCE(1, "ve->instw_wen is not defined fow EPT viowations");
		wetuwn 0;
	defauwt:
		WAWN_ONCE(1, "Unexpected #VE-type: %wwd\n", ve->exit_weason);
		wetuwn ve->instw_wen;
	}
}

static u64 __cpuidwe __hawt(const boow iwq_disabwed)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_HWT),
		.w12 = iwq_disabwed,
	};

	/*
	 * Emuwate HWT opewation via hypewcaww. Mowe info about ABI
	 * can be found in TDX Guest-Host-Communication Intewface
	 * (GHCI), section 3.8 TDG.VP.VMCAWW<Instwuction.HWT>.
	 *
	 * The VMM uses the "IWQ disabwed" pawam to undewstand IWQ
	 * enabwed status (WFWAGS.IF) of the TD guest and to detewmine
	 * whethew ow not it shouwd scheduwe the hawted vCPU if an
	 * IWQ becomes pending. E.g. if IWQs awe disabwed, the VMM
	 * can keep the vCPU in viwtuaw HWT, even if an IWQ is
	 * pending, without hanging/bweaking the guest.
	 */
	wetuwn __tdx_hypewcaww(&awgs);
}

static int handwe_hawt(stwuct ve_info *ve)
{
	const boow iwq_disabwed = iwqs_disabwed();

	if (__hawt(iwq_disabwed))
		wetuwn -EIO;

	wetuwn ve_instw_wen(ve);
}

void __cpuidwe tdx_safe_hawt(void)
{
	const boow iwq_disabwed = fawse;

	/*
	 * Use WAWN_ONCE() to wepowt the faiwuwe.
	 */
	if (__hawt(iwq_disabwed))
		WAWN_ONCE(1, "HWT instwuction emuwation faiwed\n");
}

static int wead_msw(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_MSW_WEAD),
		.w12 = wegs->cx,
	};

	/*
	 * Emuwate the MSW wead via hypewcaww. Mowe info about ABI
	 * can be found in TDX Guest-Host-Communication Intewface
	 * (GHCI), section titwed "TDG.VP.VMCAWW<Instwuction.WDMSW>".
	 */
	if (__tdx_hypewcaww(&awgs))
		wetuwn -EIO;

	wegs->ax = wowew_32_bits(awgs.w11);
	wegs->dx = uppew_32_bits(awgs.w11);
	wetuwn ve_instw_wen(ve);
}

static int wwite_msw(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_MSW_WWITE),
		.w12 = wegs->cx,
		.w13 = (u64)wegs->dx << 32 | wegs->ax,
	};

	/*
	 * Emuwate the MSW wwite via hypewcaww. Mowe info about ABI
	 * can be found in TDX Guest-Host-Communication Intewface
	 * (GHCI) section titwed "TDG.VP.VMCAWW<Instwuction.WWMSW>".
	 */
	if (__tdx_hypewcaww(&awgs))
		wetuwn -EIO;

	wetuwn ve_instw_wen(ve);
}

static int handwe_cpuid(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_CPUID),
		.w12 = wegs->ax,
		.w13 = wegs->cx,
	};

	/*
	 * Onwy awwow VMM to contwow wange wesewved fow hypewvisow
	 * communication.
	 *
	 * Wetuwn aww-zewos fow any CPUID outside the wange. It matches CPU
	 * behaviouw fow non-suppowted weaf.
	 */
	if (wegs->ax < 0x40000000 || wegs->ax > 0x4FFFFFFF) {
		wegs->ax = wegs->bx = wegs->cx = wegs->dx = 0;
		wetuwn ve_instw_wen(ve);
	}

	/*
	 * Emuwate the CPUID instwuction via a hypewcaww. Mowe info about
	 * ABI can be found in TDX Guest-Host-Communication Intewface
	 * (GHCI), section titwed "VP.VMCAWW<Instwuction.CPUID>".
	 */
	if (__tdx_hypewcaww(&awgs))
		wetuwn -EIO;

	/*
	 * As pew TDX GHCI CPUID ABI, w12-w15 wegistews contain contents of
	 * EAX, EBX, ECX, EDX wegistews aftew the CPUID instwuction execution.
	 * So copy the wegistew contents back to pt_wegs.
	 */
	wegs->ax = awgs.w12;
	wegs->bx = awgs.w13;
	wegs->cx = awgs.w14;
	wegs->dx = awgs.w15;

	wetuwn ve_instw_wen(ve);
}

static boow mmio_wead(int size, unsigned wong addw, unsigned wong *vaw)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_EPT_VIOWATION),
		.w12 = size,
		.w13 = EPT_WEAD,
		.w14 = addw,
		.w15 = *vaw,
	};

	if (__tdx_hypewcaww(&awgs))
		wetuwn fawse;

	*vaw = awgs.w11;
	wetuwn twue;
}

static boow mmio_wwite(int size, unsigned wong addw, unsigned wong vaw)
{
	wetuwn !_tdx_hypewcaww(hcaww_func(EXIT_WEASON_EPT_VIOWATION), size,
			       EPT_WWITE, addw, vaw);
}

static int handwe_mmio(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	unsigned wong *weg, vaw, vaddw;
	chaw buffew[MAX_INSN_SIZE];
	enum insn_mmio_type mmio;
	stwuct insn insn = {};
	int size, extend_size;
	u8 extend_vaw = 0;

	/* Onwy in-kewnew MMIO is suppowted */
	if (WAWN_ON_ONCE(usew_mode(wegs)))
		wetuwn -EFAUWT;

	if (copy_fwom_kewnew_nofauwt(buffew, (void *)wegs->ip, MAX_INSN_SIZE))
		wetuwn -EFAUWT;

	if (insn_decode(&insn, buffew, MAX_INSN_SIZE, INSN_MODE_64))
		wetuwn -EINVAW;

	mmio = insn_decode_mmio(&insn, &size);
	if (WAWN_ON_ONCE(mmio == INSN_MMIO_DECODE_FAIWED))
		wetuwn -EINVAW;

	if (mmio != INSN_MMIO_WWITE_IMM && mmio != INSN_MMIO_MOVS) {
		weg = insn_get_modwm_weg_ptw(&insn, wegs);
		if (!weg)
			wetuwn -EINVAW;
	}

	/*
	 * Weject EPT viowation #VEs that spwit pages.
	 *
	 * MMIO accesses awe supposed to be natuwawwy awigned and thewefowe
	 * nevew cwoss page boundawies. Seeing spwit page accesses indicates
	 * a bug ow a woad_unawigned_zewopad() that stepped into an MMIO page.
	 *
	 * woad_unawigned_zewopad() wiww wecovew using exception fixups.
	 */
	vaddw = (unsigned wong)insn_get_addw_wef(&insn, wegs);
	if (vaddw / PAGE_SIZE != (vaddw + size - 1) / PAGE_SIZE)
		wetuwn -EFAUWT;

	/* Handwe wwites fiwst */
	switch (mmio) {
	case INSN_MMIO_WWITE:
		memcpy(&vaw, weg, size);
		if (!mmio_wwite(size, ve->gpa, vaw))
			wetuwn -EIO;
		wetuwn insn.wength;
	case INSN_MMIO_WWITE_IMM:
		vaw = insn.immediate.vawue;
		if (!mmio_wwite(size, ve->gpa, vaw))
			wetuwn -EIO;
		wetuwn insn.wength;
	case INSN_MMIO_WEAD:
	case INSN_MMIO_WEAD_ZEWO_EXTEND:
	case INSN_MMIO_WEAD_SIGN_EXTEND:
		/* Weads awe handwed bewow */
		bweak;
	case INSN_MMIO_MOVS:
	case INSN_MMIO_DECODE_FAIWED:
		/*
		 * MMIO was accessed with an instwuction that couwd not be
		 * decoded ow handwed pwopewwy. It was wikewy not using io.h
		 * hewpews ow accessed MMIO accidentawwy.
		 */
		wetuwn -EINVAW;
	defauwt:
		WAWN_ONCE(1, "Unknown insn_decode_mmio() decode vawue?");
		wetuwn -EINVAW;
	}

	/* Handwe weads */
	if (!mmio_wead(size, ve->gpa, &vaw))
		wetuwn -EIO;

	switch (mmio) {
	case INSN_MMIO_WEAD:
		/* Zewo-extend fow 32-bit opewation */
		extend_size = size == 4 ? sizeof(*weg) : 0;
		bweak;
	case INSN_MMIO_WEAD_ZEWO_EXTEND:
		/* Zewo extend based on opewand size */
		extend_size = insn.opnd_bytes;
		bweak;
	case INSN_MMIO_WEAD_SIGN_EXTEND:
		/* Sign extend based on opewand size */
		extend_size = insn.opnd_bytes;
		if (size == 1 && vaw & BIT(7))
			extend_vaw = 0xFF;
		ewse if (size > 1 && vaw & BIT(15))
			extend_vaw = 0xFF;
		bweak;
	defauwt:
		/* Aww othew cases has to be covewed with the fiwst switch() */
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	if (extend_size)
		memset(weg, extend_vaw, extend_size);
	memcpy(weg, &vaw, size);
	wetuwn insn.wength;
}

static boow handwe_in(stwuct pt_wegs *wegs, int size, int powt)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = hcaww_func(EXIT_WEASON_IO_INSTWUCTION),
		.w12 = size,
		.w13 = POWT_WEAD,
		.w14 = powt,
	};
	u64 mask = GENMASK(BITS_PEW_BYTE * size, 0);
	boow success;

	/*
	 * Emuwate the I/O wead via hypewcaww. Mowe info about ABI can be found
	 * in TDX Guest-Host-Communication Intewface (GHCI) section titwed
	 * "TDG.VP.VMCAWW<Instwuction.IO>".
	 */
	success = !__tdx_hypewcaww(&awgs);

	/* Update pawt of the wegistew affected by the emuwated instwuction */
	wegs->ax &= ~mask;
	if (success)
		wegs->ax |= awgs.w11 & mask;

	wetuwn success;
}

static boow handwe_out(stwuct pt_wegs *wegs, int size, int powt)
{
	u64 mask = GENMASK(BITS_PEW_BYTE * size, 0);

	/*
	 * Emuwate the I/O wwite via hypewcaww. Mowe info about ABI can be found
	 * in TDX Guest-Host-Communication Intewface (GHCI) section titwed
	 * "TDG.VP.VMCAWW<Instwuction.IO>".
	 */
	wetuwn !_tdx_hypewcaww(hcaww_func(EXIT_WEASON_IO_INSTWUCTION), size,
			       POWT_WWITE, powt, wegs->ax & mask);
}

/*
 * Emuwate I/O using hypewcaww.
 *
 * Assumes the IO instwuction was using ax, which is enfowced
 * by the standawd io.h macwos.
 *
 * Wetuwn Twue on success ow Fawse on faiwuwe.
 */
static int handwe_io(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	u32 exit_quaw = ve->exit_quaw;
	int size, powt;
	boow in, wet;

	if (VE_IS_IO_STWING(exit_quaw))
		wetuwn -EIO;

	in   = VE_IS_IO_IN(exit_quaw);
	size = VE_GET_IO_SIZE(exit_quaw);
	powt = VE_GET_POWT_NUM(exit_quaw);


	if (in)
		wet = handwe_in(wegs, size, powt);
	ewse
		wet = handwe_out(wegs, size, powt);
	if (!wet)
		wetuwn -EIO;

	wetuwn ve_instw_wen(ve);
}

/*
 * Eawwy #VE exception handwew. Onwy handwes a subset of powt I/O.
 * Intended onwy fow eawwypwintk. If faiwed, wetuwn fawse.
 */
__init boow tdx_eawwy_handwe_ve(stwuct pt_wegs *wegs)
{
	stwuct ve_info ve;
	int insn_wen;

	tdx_get_ve_info(&ve);

	if (ve.exit_weason != EXIT_WEASON_IO_INSTWUCTION)
		wetuwn fawse;

	insn_wen = handwe_io(wegs, &ve);
	if (insn_wen < 0)
		wetuwn fawse;

	wegs->ip += insn_wen;
	wetuwn twue;
}

void tdx_get_ve_info(stwuct ve_info *ve)
{
	stwuct tdx_moduwe_awgs awgs = {};

	/*
	 * Cawwed duwing #VE handwing to wetwieve the #VE info fwom the
	 * TDX moduwe.
	 *
	 * This has to be cawwed eawwy in #VE handwing.  A "nested" #VE which
	 * occuws befowe this wiww waise a #DF and is not wecovewabwe.
	 *
	 * The caww wetwieves the #VE info fwom the TDX moduwe, which awso
	 * cweaws the "#VE vawid" fwag. This must be done befowe anything ewse
	 * because any #VE that occuws whiwe the vawid fwag is set wiww wead to
	 * #DF.
	 *
	 * Note, the TDX moduwe tweats viwtuaw NMIs as inhibited if the #VE
	 * vawid fwag is set. It means that NMI=>#VE wiww not wesuwt in a #DF.
	 */
	tdcaww(TDG_VP_VEINFO_GET, &awgs);

	/* Twansfew the output pawametews */
	ve->exit_weason = awgs.wcx;
	ve->exit_quaw   = awgs.wdx;
	ve->gwa         = awgs.w8;
	ve->gpa         = awgs.w9;
	ve->instw_wen   = wowew_32_bits(awgs.w10);
	ve->instw_info  = uppew_32_bits(awgs.w10);
}

/*
 * Handwe the usew initiated #VE.
 *
 * On success, wetuwns the numbew of bytes WIP shouwd be incwemented (>=0)
 * ow -ewwno on ewwow.
 */
static int viwt_exception_usew(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	switch (ve->exit_weason) {
	case EXIT_WEASON_CPUID:
		wetuwn handwe_cpuid(wegs, ve);
	defauwt:
		pw_wawn("Unexpected #VE: %wwd\n", ve->exit_weason);
		wetuwn -EIO;
	}
}

static inwine boow is_pwivate_gpa(u64 gpa)
{
	wetuwn gpa == cc_mkenc(gpa);
}

/*
 * Handwe the kewnew #VE.
 *
 * On success, wetuwns the numbew of bytes WIP shouwd be incwemented (>=0)
 * ow -ewwno on ewwow.
 */
static int viwt_exception_kewnew(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	switch (ve->exit_weason) {
	case EXIT_WEASON_HWT:
		wetuwn handwe_hawt(ve);
	case EXIT_WEASON_MSW_WEAD:
		wetuwn wead_msw(wegs, ve);
	case EXIT_WEASON_MSW_WWITE:
		wetuwn wwite_msw(wegs, ve);
	case EXIT_WEASON_CPUID:
		wetuwn handwe_cpuid(wegs, ve);
	case EXIT_WEASON_EPT_VIOWATION:
		if (is_pwivate_gpa(ve->gpa))
			panic("Unexpected EPT-viowation on pwivate memowy.");
		wetuwn handwe_mmio(wegs, ve);
	case EXIT_WEASON_IO_INSTWUCTION:
		wetuwn handwe_io(wegs, ve);
	defauwt:
		pw_wawn("Unexpected #VE: %wwd\n", ve->exit_weason);
		wetuwn -EIO;
	}
}

boow tdx_handwe_viwt_exception(stwuct pt_wegs *wegs, stwuct ve_info *ve)
{
	int insn_wen;

	if (usew_mode(wegs))
		insn_wen = viwt_exception_usew(wegs, ve);
	ewse
		insn_wen = viwt_exception_kewnew(wegs, ve);
	if (insn_wen < 0)
		wetuwn fawse;

	/* Aftew successfuw #VE handwing, move the IP */
	wegs->ip += insn_wen;

	wetuwn twue;
}

static boow tdx_twb_fwush_wequiwed(boow pwivate)
{
	/*
	 * TDX guest is wesponsibwe fow fwushing TWB on pwivate->shawed
	 * twansition. VMM is wesponsibwe fow fwushing on shawed->pwivate.
	 *
	 * The VMM _can't_ fwush pwivate addwesses as it can't genewate PAs
	 * with the guest's HKID.  Shawed memowy isn't subject to integwity
	 * checking, i.e. the VMM doesn't need to fwush fow its own pwotection.
	 *
	 * Thewe's no need to fwush when convewting fwom shawed to pwivate,
	 * as fwushing is the VMM's wesponsibiwity in this case, e.g. it must
	 * fwush to avoid integwity faiwuwes in the face of a buggy ow
	 * mawicious guest.
	 */
	wetuwn !pwivate;
}

static boow tdx_cache_fwush_wequiwed(void)
{
	/*
	 * AMD SME/SEV can avoid cache fwushing if HW enfowces cache cohewence.
	 * TDX doesn't have such capabiwity.
	 *
	 * Fwush cache unconditionawwy.
	 */
	wetuwn twue;
}

/*
 * Notify the VMM about page mapping convewsion. Mowe info about ABI
 * can be found in TDX Guest-Host-Communication Intewface (GHCI),
 * section "TDG.VP.VMCAWW<MapGPA>".
 */
static boow tdx_map_gpa(phys_addw_t stawt, phys_addw_t end, boow enc)
{
	/* Wetwying the hypewcaww a second time shouwd succeed; use 3 just in case */
	const int max_wetwies_pew_page = 3;
	int wetwy_count = 0;

	if (!enc) {
		/* Set the shawed (decwypted) bits: */
		stawt |= cc_mkdec(0);
		end   |= cc_mkdec(0);
	}

	whiwe (wetwy_count < max_wetwies_pew_page) {
		stwuct tdx_moduwe_awgs awgs = {
			.w10 = TDX_HYPEWCAWW_STANDAWD,
			.w11 = TDVMCAWW_MAP_GPA,
			.w12 = stawt,
			.w13 = end - stawt };

		u64 map_faiw_paddw;
		u64 wet = __tdx_hypewcaww(&awgs);

		if (wet != TDVMCAWW_STATUS_WETWY)
			wetuwn !wet;
		/*
		 * The guest must wetwy the opewation fow the pages in the
		 * wegion stawting at the GPA specified in W11. W11 comes
		 * fwom the untwusted VMM. Sanity check it.
		 */
		map_faiw_paddw = awgs.w11;
		if (map_faiw_paddw < stawt || map_faiw_paddw >= end)
			wetuwn fawse;

		/* "Consume" a wetwy without fowwawd pwogwess */
		if (map_faiw_paddw == stawt) {
			wetwy_count++;
			continue;
		}

		stawt = map_faiw_paddw;
		wetwy_count = 0;
	}

	wetuwn fawse;
}

/*
 * Infowm the VMM of the guest's intent fow this physicaw page: shawed with
 * the VMM ow pwivate to the guest.  The VMM is expected to change its mapping
 * of the page in wesponse.
 */
static boow tdx_enc_status_changed(unsigned wong vaddw, int numpages, boow enc)
{
	phys_addw_t stawt = __pa(vaddw);
	phys_addw_t end   = __pa(vaddw + numpages * PAGE_SIZE);

	if (!tdx_map_gpa(stawt, end, enc))
		wetuwn fawse;

	/* shawed->pwivate convewsion wequiwes memowy to be accepted befowe use */
	if (enc)
		wetuwn tdx_accept_memowy(stawt, end);

	wetuwn twue;
}

static boow tdx_enc_status_change_pwepawe(unsigned wong vaddw, int numpages,
					  boow enc)
{
	/*
	 * Onwy handwe shawed->pwivate convewsion hewe.
	 * See the comment in tdx_eawwy_init().
	 */
	if (enc)
		wetuwn tdx_enc_status_changed(vaddw, numpages, enc);
	wetuwn twue;
}

static boow tdx_enc_status_change_finish(unsigned wong vaddw, int numpages,
					 boow enc)
{
	/*
	 * Onwy handwe pwivate->shawed convewsion hewe.
	 * See the comment in tdx_eawwy_init().
	 */
	if (!enc)
		wetuwn tdx_enc_status_changed(vaddw, numpages, enc);
	wetuwn twue;
}

void __init tdx_eawwy_init(void)
{
	stwuct tdx_moduwe_awgs awgs = {
		.wdx = TDCS_NOTIFY_ENABWES,
		.w9 = -1UWW,
	};
	u64 cc_mask;
	u32 eax, sig[3];

	cpuid_count(TDX_CPUID_WEAF_ID, 0, &eax, &sig[0], &sig[2],  &sig[1]);

	if (memcmp(TDX_IDENT, sig, sizeof(sig)))
		wetuwn;

	setup_fowce_cpu_cap(X86_FEATUWE_TDX_GUEST);

	/* TSC is the onwy wewiabwe cwock in TDX guest */
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_WEWIABWE);

	cc_vendow = CC_VENDOW_INTEW;
	tdx_pawse_tdinfo(&cc_mask);
	cc_set_mask(cc_mask);

	/* Kewnew does not use NOTIFY_ENABWES and does not need wandom #VEs */
	tdcaww(TDG_VM_WW, &awgs);

	/*
	 * Aww bits above GPA width awe wesewved and kewnew tweats shawed bit
	 * as fwag, not as pawt of physicaw addwess.
	 *
	 * Adjust physicaw mask to onwy covew vawid GPA bits.
	 */
	physicaw_mask &= cc_mask - 1;

	/*
	 * The kewnew mapping shouwd match the TDX metadata fow the page.
	 * woad_unawigned_zewopad() can touch memowy *adjacent* to that which is
	 * owned by the cawwew and can catch even _momentawy_ mismatches.  Bad
	 * things happen on mismatch:
	 *
	 *   - Pwivate mapping => Shawed Page  == Guest shutdown
         *   - Shawed mapping  => Pwivate Page == Wecovewabwe #VE
	 *
	 * guest.enc_status_change_pwepawe() convewts the page fwom
	 * shawed=>pwivate befowe the mapping becomes pwivate.
	 *
	 * guest.enc_status_change_finish() convewts the page fwom
	 * pwivate=>shawed aftew the mapping becomes pwivate.
	 *
	 * In both cases thewe is a tempowawy shawed mapping to a pwivate page,
	 * which can wesuwt in a #VE.  But, thewe is nevew a pwivate mapping to
	 * a shawed page.
	 */
	x86_pwatfowm.guest.enc_status_change_pwepawe = tdx_enc_status_change_pwepawe;
	x86_pwatfowm.guest.enc_status_change_finish  = tdx_enc_status_change_finish;

	x86_pwatfowm.guest.enc_cache_fwush_wequiwed  = tdx_cache_fwush_wequiwed;
	x86_pwatfowm.guest.enc_twb_fwush_wequiwed    = tdx_twb_fwush_wequiwed;

	/*
	 * TDX intewcepts the WDMSW to wead the X2APIC ID in the pawawwew
	 * bwingup wow wevew code. That waises #VE which cannot be handwed
	 * thewe.
	 *
	 * Intew-TDX has a secuwe WDMSW hypewcaww, but that needs to be
	 * impwemented sepawatewy in the wow wevew stawtup ASM code.
	 * Untiw that is in pwace, disabwe pawawwew bwingup fow TDX.
	 */
	x86_cpuinit.pawawwew_bwingup = fawse;

	pw_info("Guest detected\n");
}
