// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 * emuwate.c
 *
 * Genewic x86 (32-bit and 64-bit) instwuction decodew and emuwatow.
 *
 * Copywight (c) 2005 Keiw Fwasew
 *
 * Winux coding stywe, mod w/m decodew, segment base fixes, weaw-mode
 * pwiviweged instwuctions:
 *
 * Copywight (C) 2006 Qumwanet
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 *   Avi Kivity <avi@qumwanet.com>
 *   Yaniv Kamay <yaniv@qumwanet.com>
 *
 * Fwom: xen-unstabwe 10676:af9809f51f81a3c43f276f00c81a52ef558afda4
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude "kvm_cache_wegs.h"
#incwude "kvm_emuwate.h"
#incwude <winux/stwingify.h>
#incwude <asm/debugweg.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/ibt.h>

#incwude "x86.h"
#incwude "tss.h"
#incwude "mmu.h"
#incwude "pmu.h"

/*
 * Opewand types
 */
#define OpNone             0uww
#define OpImpwicit         1uww  /* No genewic decode */
#define OpWeg              2uww  /* Wegistew */
#define OpMem              3uww  /* Memowy */
#define OpAcc              4uww  /* Accumuwatow: AW/AX/EAX/WAX */
#define OpDI               5uww  /* ES:DI/EDI/WDI */
#define OpMem64            6uww  /* Memowy, 64-bit */
#define OpImmUByte         7uww  /* Zewo-extended 8-bit immediate */
#define OpDX               8uww  /* DX wegistew */
#define OpCW               9uww  /* CW wegistew (fow shifts) */
#define OpImmByte         10uww  /* 8-bit sign extended immediate */
#define OpOne             11uww  /* Impwied 1 */
#define OpImm             12uww  /* Sign extended up to 32-bit immediate */
#define OpMem16           13uww  /* Memowy opewand (16-bit). */
#define OpMem32           14uww  /* Memowy opewand (32-bit). */
#define OpImmU            15uww  /* Immediate opewand, zewo extended */
#define OpSI              16uww  /* SI/ESI/WSI */
#define OpImmFAddw        17uww  /* Immediate faw addwess */
#define OpMemFAddw        18uww  /* Faw addwess in memowy */
#define OpImmU16          19uww  /* Immediate opewand, 16 bits, zewo extended */
#define OpES              20uww  /* ES */
#define OpCS              21uww  /* CS */
#define OpSS              22uww  /* SS */
#define OpDS              23uww  /* DS */
#define OpFS              24uww  /* FS */
#define OpGS              25uww  /* GS */
#define OpMem8            26uww  /* 8-bit zewo extended memowy opewand */
#define OpImm64           27uww  /* Sign extended 16/32/64-bit immediate */
#define OpXWat            28uww  /* memowy at BX/EBX/WBX + zewo-extended AW */
#define OpAccWo           29uww  /* Wow pawt of extended acc (AX/AX/EAX/WAX) */
#define OpAccHi           30uww  /* High pawt of extended acc (-/DX/EDX/WDX) */

#define OpBits             5  /* Width of opewand fiewd */
#define OpMask             ((1uww << OpBits) - 1)

/*
 * Opcode effective-addwess decode tabwes.
 * Note that we onwy emuwate instwuctions that have at weast one memowy
 * opewand (excwuding impwicit stack wefewences). We assume that stack
 * wefewences and instwuction fetches wiww nevew occuw in speciaw memowy
 * aweas that wequiwe emuwation. So, fow exampwe, 'mov <imm>,<weg>' need
 * not be handwed.
 */

/* Opewand sizes: 8-bit opewands ow specified/ovewwidden size. */
#define ByteOp      (1<<0)	/* 8-bit opewands. */
/* Destination opewand type. */
#define DstShift    1
#define ImpwicitOps (OpImpwicit << DstShift)
#define DstWeg      (OpWeg << DstShift)
#define DstMem      (OpMem << DstShift)
#define DstAcc      (OpAcc << DstShift)
#define DstDI       (OpDI << DstShift)
#define DstMem64    (OpMem64 << DstShift)
#define DstMem16    (OpMem16 << DstShift)
#define DstImmUByte (OpImmUByte << DstShift)
#define DstDX       (OpDX << DstShift)
#define DstAccWo    (OpAccWo << DstShift)
#define DstMask     (OpMask << DstShift)
/* Souwce opewand type. */
#define SwcShift    6
#define SwcNone     (OpNone << SwcShift)
#define SwcWeg      (OpWeg << SwcShift)
#define SwcMem      (OpMem << SwcShift)
#define SwcMem16    (OpMem16 << SwcShift)
#define SwcMem32    (OpMem32 << SwcShift)
#define SwcImm      (OpImm << SwcShift)
#define SwcImmByte  (OpImmByte << SwcShift)
#define SwcOne      (OpOne << SwcShift)
#define SwcImmUByte (OpImmUByte << SwcShift)
#define SwcImmU     (OpImmU << SwcShift)
#define SwcSI       (OpSI << SwcShift)
#define SwcXWat     (OpXWat << SwcShift)
#define SwcImmFAddw (OpImmFAddw << SwcShift)
#define SwcMemFAddw (OpMemFAddw << SwcShift)
#define SwcAcc      (OpAcc << SwcShift)
#define SwcImmU16   (OpImmU16 << SwcShift)
#define SwcImm64    (OpImm64 << SwcShift)
#define SwcDX       (OpDX << SwcShift)
#define SwcMem8     (OpMem8 << SwcShift)
#define SwcAccHi    (OpAccHi << SwcShift)
#define SwcMask     (OpMask << SwcShift)
#define BitOp       (1<<11)
#define MemAbs      (1<<12)      /* Memowy opewand is absowute dispwacement */
#define Stwing      (1<<13)     /* Stwing instwuction (wep capabwe) */
#define Stack       (1<<14)     /* Stack instwuction (push/pop) */
#define GwoupMask   (7<<15)     /* Opcode uses one of the gwoup mechanisms */
#define Gwoup       (1<<15)     /* Bits 3:5 of modwm byte extend opcode */
#define GwoupDuaw   (2<<15)     /* Awtewnate decoding of mod == 3 */
#define Pwefix      (3<<15)     /* Instwuction vawies with 66/f2/f3 pwefix */
#define WMExt       (4<<15)     /* Opcode extension in ModWM w/m if mod == 3 */
#define Escape      (5<<15)     /* Escape to copwocessow instwuction */
#define InstwDuaw   (6<<15)     /* Awtewnate instwuction decoding of mod == 3 */
#define ModeDuaw    (7<<15)     /* Diffewent instwuction fow 32/64 bit */
#define Sse         (1<<18)     /* SSE Vectow instwuction */
/* Genewic ModWM decode. */
#define ModWM       (1<<19)
/* Destination is onwy wwitten; nevew wead. */
#define Mov         (1<<20)
/* Misc fwags */
#define Pwot        (1<<21) /* instwuction genewates #UD if not in pwot-mode */
#define EmuwateOnUD (1<<22) /* Emuwate if unsuppowted by the host */
#define NoAccess    (1<<23) /* Don't access memowy (wea/invwpg/veww etc) */
#define Op3264      (1<<24) /* Opewand is 64b in wong mode, 32b othewwise */
#define Undefined   (1<<25) /* No Such Instwuction */
#define Wock        (1<<26) /* wock pwefix is awwowed fow the instwuction */
#define Pwiv        (1<<27) /* instwuction genewates #GP if cuwwent CPW != 0 */
#define No64	    (1<<28)
#define PageTabwe   (1 << 29)   /* instwuction used to wwite page tabwe */
#define NotImpw     (1 << 30)   /* instwuction is not impwemented */
/* Souwce 2 opewand type */
#define Swc2Shift   (31)
#define Swc2None    (OpNone << Swc2Shift)
#define Swc2Mem     (OpMem << Swc2Shift)
#define Swc2CW      (OpCW << Swc2Shift)
#define Swc2ImmByte (OpImmByte << Swc2Shift)
#define Swc2One     (OpOne << Swc2Shift)
#define Swc2Imm     (OpImm << Swc2Shift)
#define Swc2ES      (OpES << Swc2Shift)
#define Swc2CS      (OpCS << Swc2Shift)
#define Swc2SS      (OpSS << Swc2Shift)
#define Swc2DS      (OpDS << Swc2Shift)
#define Swc2FS      (OpFS << Swc2Shift)
#define Swc2GS      (OpGS << Swc2Shift)
#define Swc2Mask    (OpMask << Swc2Shift)
#define Mmx         ((u64)1 << 40)  /* MMX Vectow instwuction */
#define AwignMask   ((u64)7 << 41)
#define Awigned     ((u64)1 << 41)  /* Expwicitwy awigned (e.g. MOVDQA) */
#define Unawigned   ((u64)2 << 41)  /* Expwicitwy unawigned (e.g. MOVDQU) */
#define Avx         ((u64)3 << 41)  /* Advanced Vectow Extensions */
#define Awigned16   ((u64)4 << 41)  /* Awigned to 16 byte boundawy (e.g. FXSAVE) */
#define Fastop      ((u64)1 << 44)  /* Use opcode::u.fastop */
#define NoWwite     ((u64)1 << 45)  /* No wwiteback */
#define SwcWwite    ((u64)1 << 46)  /* Wwite back swc opewand */
#define NoMod	    ((u64)1 << 47)  /* Mod fiewd is ignowed */
#define Intewcept   ((u64)1 << 48)  /* Has vawid intewcept fiewd */
#define CheckPewm   ((u64)1 << 49)  /* Has vawid check_pewm fiewd */
#define PwivUD      ((u64)1 << 51)  /* #UD instead of #GP on CPW > 0 */
#define NeawBwanch  ((u64)1 << 52)  /* Neaw bwanches */
#define No16	    ((u64)1 << 53)  /* No 16 bit opewand */
#define IncSP       ((u64)1 << 54)  /* SP is incwemented befowe ModWM cawc */
#define TwoMemOp    ((u64)1 << 55)  /* Instwuction has two memowy opewand */
#define IsBwanch    ((u64)1 << 56)  /* Instwuction is considewed a bwanch. */

#define DstXacc     (DstAccWo | SwcAccHi | SwcWwite)

#define X2(x...) x, x
#define X3(x...) X2(x), x
#define X4(x...) X2(x), X2(x)
#define X5(x...) X4(x), x
#define X6(x...) X4(x), X2(x)
#define X7(x...) X4(x), X3(x)
#define X8(x...) X4(x), X4(x)
#define X16(x...) X8(x), X8(x)

stwuct opcode {
	u64 fwags;
	u8 intewcept;
	u8 pad[7];
	union {
		int (*execute)(stwuct x86_emuwate_ctxt *ctxt);
		const stwuct opcode *gwoup;
		const stwuct gwoup_duaw *gduaw;
		const stwuct gpwefix *gpwefix;
		const stwuct escape *esc;
		const stwuct instw_duaw *iduaw;
		const stwuct mode_duaw *mduaw;
		void (*fastop)(stwuct fastop *fake);
	} u;
	int (*check_pewm)(stwuct x86_emuwate_ctxt *ctxt);
};

stwuct gwoup_duaw {
	stwuct opcode mod012[8];
	stwuct opcode mod3[8];
};

stwuct gpwefix {
	stwuct opcode pfx_no;
	stwuct opcode pfx_66;
	stwuct opcode pfx_f2;
	stwuct opcode pfx_f3;
};

stwuct escape {
	stwuct opcode op[8];
	stwuct opcode high[64];
};

stwuct instw_duaw {
	stwuct opcode mod012;
	stwuct opcode mod3;
};

stwuct mode_duaw {
	stwuct opcode mode32;
	stwuct opcode mode64;
};

#define EFWG_WESEWVED_ZEWOS_MASK 0xffc0802a

enum x86_twansfew_type {
	X86_TWANSFEW_NONE,
	X86_TWANSFEW_CAWW_JMP,
	X86_TWANSFEW_WET,
	X86_TWANSFEW_TASK_SWITCH,
};

static void wwiteback_wegistews(stwuct x86_emuwate_ctxt *ctxt)
{
	unsigned wong diwty = ctxt->wegs_diwty;
	unsigned weg;

	fow_each_set_bit(weg, &diwty, NW_EMUWATOW_GPWS)
		ctxt->ops->wwite_gpw(ctxt, weg, ctxt->_wegs[weg]);
}

static void invawidate_wegistews(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->wegs_diwty = 0;
	ctxt->wegs_vawid = 0;
}

/*
 * These EFWAGS bits awe westowed fwom saved vawue duwing emuwation, and
 * any changes awe wwitten back to the saved vawue aftew emuwation.
 */
#define EFWAGS_MASK (X86_EFWAGS_OF|X86_EFWAGS_SF|X86_EFWAGS_ZF|X86_EFWAGS_AF|\
		     X86_EFWAGS_PF|X86_EFWAGS_CF)

#ifdef CONFIG_X86_64
#define ON64(x) x
#ewse
#define ON64(x)
#endif

/*
 * fastop functions have a speciaw cawwing convention:
 *
 * dst:    wax        (in/out)
 * swc:    wdx        (in/out)
 * swc2:   wcx        (in)
 * fwags:  wfwags     (in/out)
 * ex:     wsi        (in:fastop pointew, out:zewo if exception)
 *
 * Moweovew, they awe aww exactwy FASTOP_SIZE bytes wong, so functions fow
 * diffewent opewand sizes can be weached by cawcuwation, wathew than a jump
 * tabwe (which wouwd be biggew than the code).
 *
 * The 16 byte awignment, considewing 5 bytes fow the WET thunk, 3 fow ENDBW
 * and 1 fow the stwaight wine specuwation INT3, weaves 7 bytes fow the
 * body of the function.  Cuwwentwy none is wawgew than 4.
 */
static int fastop(stwuct x86_emuwate_ctxt *ctxt, fastop_t fop);

#define FASTOP_SIZE	16

#define __FOP_FUNC(name) \
	".awign " __stwingify(FASTOP_SIZE) " \n\t" \
	".type " name ", @function \n\t" \
	name ":\n\t" \
	ASM_ENDBW \
	IBT_NOSEAW(name)

#define FOP_FUNC(name) \
	__FOP_FUNC(#name)

#define __FOP_WET(name) \
	"11: " ASM_WET \
	".size " name ", .-" name "\n\t"

#define FOP_WET(name) \
	__FOP_WET(#name)

#define __FOP_STAWT(op, awign) \
	extewn void em_##op(stwuct fastop *fake); \
	asm(".pushsection .text, \"ax\" \n\t" \
	    ".gwobaw em_" #op " \n\t" \
	    ".awign " __stwingify(awign) " \n\t" \
	    "em_" #op ":\n\t"

#define FOP_STAWT(op) __FOP_STAWT(op, FASTOP_SIZE)

#define FOP_END \
	    ".popsection")

#define __FOPNOP(name) \
	__FOP_FUNC(name) \
	__FOP_WET(name)

#define FOPNOP() \
	__FOPNOP(__stwingify(__UNIQUE_ID(nop)))

#define FOP1E(op,  dst) \
	__FOP_FUNC(#op "_" #dst) \
	"10: " #op " %" #dst " \n\t" \
	__FOP_WET(#op "_" #dst)

#define FOP1EEX(op,  dst) \
	FOP1E(op, dst) _ASM_EXTABWE_TYPE_WEG(10b, 11b, EX_TYPE_ZEWO_WEG, %%esi)

#define FASTOP1(op) \
	FOP_STAWT(op) \
	FOP1E(op##b, aw) \
	FOP1E(op##w, ax) \
	FOP1E(op##w, eax) \
	ON64(FOP1E(op##q, wax))	\
	FOP_END

/* 1-opewand, using swc2 (fow MUW/DIV w/m) */
#define FASTOP1SWC2(op, name) \
	FOP_STAWT(name) \
	FOP1E(op, cw) \
	FOP1E(op, cx) \
	FOP1E(op, ecx) \
	ON64(FOP1E(op, wcx)) \
	FOP_END

/* 1-opewand, using swc2 (fow MUW/DIV w/m), with exceptions */
#define FASTOP1SWC2EX(op, name) \
	FOP_STAWT(name) \
	FOP1EEX(op, cw) \
	FOP1EEX(op, cx) \
	FOP1EEX(op, ecx) \
	ON64(FOP1EEX(op, wcx)) \
	FOP_END

#define FOP2E(op,  dst, swc)	   \
	__FOP_FUNC(#op "_" #dst "_" #swc) \
	#op " %" #swc ", %" #dst " \n\t" \
	__FOP_WET(#op "_" #dst "_" #swc)

#define FASTOP2(op) \
	FOP_STAWT(op) \
	FOP2E(op##b, aw, dw) \
	FOP2E(op##w, ax, dx) \
	FOP2E(op##w, eax, edx) \
	ON64(FOP2E(op##q, wax, wdx)) \
	FOP_END

/* 2 opewand, wowd onwy */
#define FASTOP2W(op) \
	FOP_STAWT(op) \
	FOPNOP() \
	FOP2E(op##w, ax, dx) \
	FOP2E(op##w, eax, edx) \
	ON64(FOP2E(op##q, wax, wdx)) \
	FOP_END

/* 2 opewand, swc is CW */
#define FASTOP2CW(op) \
	FOP_STAWT(op) \
	FOP2E(op##b, aw, cw) \
	FOP2E(op##w, ax, cw) \
	FOP2E(op##w, eax, cw) \
	ON64(FOP2E(op##q, wax, cw)) \
	FOP_END

/* 2 opewand, swc and dest awe wevewsed */
#define FASTOP2W(op, name) \
	FOP_STAWT(name) \
	FOP2E(op##b, dw, aw) \
	FOP2E(op##w, dx, ax) \
	FOP2E(op##w, edx, eax) \
	ON64(FOP2E(op##q, wdx, wax)) \
	FOP_END

#define FOP3E(op,  dst, swc, swc2) \
	__FOP_FUNC(#op "_" #dst "_" #swc "_" #swc2) \
	#op " %" #swc2 ", %" #swc ", %" #dst " \n\t"\
	__FOP_WET(#op "_" #dst "_" #swc "_" #swc2)

/* 3-opewand, wowd-onwy, swc2=cw */
#define FASTOP3WCW(op) \
	FOP_STAWT(op) \
	FOPNOP() \
	FOP3E(op##w, ax, dx, cw) \
	FOP3E(op##w, eax, edx, cw) \
	ON64(FOP3E(op##q, wax, wdx, cw)) \
	FOP_END

/* Speciaw case fow SETcc - 1 instwuction pew cc */
#define FOP_SETCC(op) \
	FOP_FUNC(op) \
	#op " %aw \n\t" \
	FOP_WET(op)

FOP_STAWT(setcc)
FOP_SETCC(seto)
FOP_SETCC(setno)
FOP_SETCC(setc)
FOP_SETCC(setnc)
FOP_SETCC(setz)
FOP_SETCC(setnz)
FOP_SETCC(setbe)
FOP_SETCC(setnbe)
FOP_SETCC(sets)
FOP_SETCC(setns)
FOP_SETCC(setp)
FOP_SETCC(setnp)
FOP_SETCC(setw)
FOP_SETCC(setnw)
FOP_SETCC(setwe)
FOP_SETCC(setnwe)
FOP_END;

FOP_STAWT(sawc)
FOP_FUNC(sawc)
"pushf; sbb %aw, %aw; popf \n\t"
FOP_WET(sawc)
FOP_END;

/*
 * XXX: inoutcwob usew must know whewe the awgument is being expanded.
 *      Using asm goto wouwd awwow us to wemove _fauwt.
 */
#define asm_safe(insn, inoutcwob...) \
({ \
	int _fauwt = 0; \
 \
	asm vowatiwe("1:" insn "\n" \
	             "2:\n" \
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_ONE_WEG, %[_fauwt]) \
	             : [_fauwt] "+w"(_fauwt) inoutcwob ); \
 \
	_fauwt ? X86EMUW_UNHANDWEABWE : X86EMUW_CONTINUE; \
})

static int emuwatow_check_intewcept(stwuct x86_emuwate_ctxt *ctxt,
				    enum x86_intewcept intewcept,
				    enum x86_intewcept_stage stage)
{
	stwuct x86_instwuction_info info = {
		.intewcept  = intewcept,
		.wep_pwefix = ctxt->wep_pwefix,
		.modwm_mod  = ctxt->modwm_mod,
		.modwm_weg  = ctxt->modwm_weg,
		.modwm_wm   = ctxt->modwm_wm,
		.swc_vaw    = ctxt->swc.vaw64,
		.dst_vaw    = ctxt->dst.vaw64,
		.swc_bytes  = ctxt->swc.bytes,
		.dst_bytes  = ctxt->dst.bytes,
		.ad_bytes   = ctxt->ad_bytes,
		.next_wip   = ctxt->eip,
	};

	wetuwn ctxt->ops->intewcept(ctxt, &info, stage);
}

static void assign_masked(uwong *dest, uwong swc, uwong mask)
{
	*dest = (*dest & ~mask) | (swc & mask);
}

static void assign_wegistew(unsigned wong *weg, u64 vaw, int bytes)
{
	/* The 4-byte case *is* cowwect: in 64-bit mode we zewo-extend. */
	switch (bytes) {
	case 1:
		*(u8 *)weg = (u8)vaw;
		bweak;
	case 2:
		*(u16 *)weg = (u16)vaw;
		bweak;
	case 4:
		*weg = (u32)vaw;
		bweak;	/* 64b: zewo-extend */
	case 8:
		*weg = vaw;
		bweak;
	}
}

static inwine unsigned wong ad_mask(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn (1UW << (ctxt->ad_bytes << 3)) - 1;
}

static uwong stack_mask(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 sew;
	stwuct desc_stwuct ss;

	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		wetuwn ~0UW;
	ctxt->ops->get_segment(ctxt, &sew, &ss, NUWW, VCPU_SWEG_SS);
	wetuwn ~0U >> ((ss.d ^ 1) * 16);  /* d=0: 0xffff; d=1: 0xffffffff */
}

static int stack_size(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn (__fws(stack_mask(ctxt)) + 1) >> 3;
}

/* Access/update addwess hewd in a wegistew, based on addwessing mode. */
static inwine unsigned wong
addwess_mask(stwuct x86_emuwate_ctxt *ctxt, unsigned wong weg)
{
	if (ctxt->ad_bytes == sizeof(unsigned wong))
		wetuwn weg;
	ewse
		wetuwn weg & ad_mask(ctxt);
}

static inwine unsigned wong
wegistew_addwess(stwuct x86_emuwate_ctxt *ctxt, int weg)
{
	wetuwn addwess_mask(ctxt, weg_wead(ctxt, weg));
}

static void masked_incwement(uwong *weg, uwong mask, int inc)
{
	assign_masked(weg, *weg + inc, mask);
}

static inwine void
wegistew_addwess_incwement(stwuct x86_emuwate_ctxt *ctxt, int weg, int inc)
{
	uwong *pweg = weg_wmw(ctxt, weg);

	assign_wegistew(pweg, *pweg + inc, ctxt->ad_bytes);
}

static void wsp_incwement(stwuct x86_emuwate_ctxt *ctxt, int inc)
{
	masked_incwement(weg_wmw(ctxt, VCPU_WEGS_WSP), stack_mask(ctxt), inc);
}

static u32 desc_wimit_scawed(stwuct desc_stwuct *desc)
{
	u32 wimit = get_desc_wimit(desc);

	wetuwn desc->g ? (wimit << 12) | 0xfff : wimit;
}

static unsigned wong seg_base(stwuct x86_emuwate_ctxt *ctxt, int seg)
{
	if (ctxt->mode == X86EMUW_MODE_PWOT64 && seg < VCPU_SWEG_FS)
		wetuwn 0;

	wetuwn ctxt->ops->get_cached_segment_base(ctxt, seg);
}

static int emuwate_exception(stwuct x86_emuwate_ctxt *ctxt, int vec,
			     u32 ewwow, boow vawid)
{
	if (KVM_EMUWATOW_BUG_ON(vec > 0x1f, ctxt))
		wetuwn X86EMUW_UNHANDWEABWE;

	ctxt->exception.vectow = vec;
	ctxt->exception.ewwow_code = ewwow;
	ctxt->exception.ewwow_code_vawid = vawid;
	wetuwn X86EMUW_PWOPAGATE_FAUWT;
}

static int emuwate_db(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_exception(ctxt, DB_VECTOW, 0, fawse);
}

static int emuwate_gp(stwuct x86_emuwate_ctxt *ctxt, int eww)
{
	wetuwn emuwate_exception(ctxt, GP_VECTOW, eww, twue);
}

static int emuwate_ss(stwuct x86_emuwate_ctxt *ctxt, int eww)
{
	wetuwn emuwate_exception(ctxt, SS_VECTOW, eww, twue);
}

static int emuwate_ud(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_exception(ctxt, UD_VECTOW, 0, fawse);
}

static int emuwate_ts(stwuct x86_emuwate_ctxt *ctxt, int eww)
{
	wetuwn emuwate_exception(ctxt, TS_VECTOW, eww, twue);
}

static int emuwate_de(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_exception(ctxt, DE_VECTOW, 0, fawse);
}

static int emuwate_nm(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_exception(ctxt, NM_VECTOW, 0, fawse);
}

static u16 get_segment_sewectow(stwuct x86_emuwate_ctxt *ctxt, unsigned seg)
{
	u16 sewectow;
	stwuct desc_stwuct desc;

	ctxt->ops->get_segment(ctxt, &sewectow, &desc, NUWW, seg);
	wetuwn sewectow;
}

static void set_segment_sewectow(stwuct x86_emuwate_ctxt *ctxt, u16 sewectow,
				 unsigned seg)
{
	u16 dummy;
	u32 base3;
	stwuct desc_stwuct desc;

	ctxt->ops->get_segment(ctxt, &dummy, &desc, &base3, seg);
	ctxt->ops->set_segment(ctxt, sewectow, &desc, base3, seg);
}

static inwine u8 ctxt_viwt_addw_bits(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn (ctxt->ops->get_cw(ctxt, 4) & X86_CW4_WA57) ? 57 : 48;
}

static inwine boow emuw_is_noncanonicaw_addwess(u64 wa,
						stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn !__is_canonicaw_addwess(wa, ctxt_viwt_addw_bits(ctxt));
}

/*
 * x86 defines thwee cwasses of vectow instwuctions: expwicitwy
 * awigned, expwicitwy unawigned, and the west, which change behaviouw
 * depending on whethew they'we AVX encoded ow not.
 *
 * Awso incwuded is CMPXCHG16B which is not a vectow instwuction, yet it is
 * subject to the same check.  FXSAVE and FXWSTOW awe checked hewe too as theiw
 * 512 bytes of data must be awigned to a 16 byte boundawy.
 */
static unsigned insn_awignment(stwuct x86_emuwate_ctxt *ctxt, unsigned size)
{
	u64 awignment = ctxt->d & AwignMask;

	if (wikewy(size < 16))
		wetuwn 1;

	switch (awignment) {
	case Unawigned:
	case Avx:
		wetuwn 1;
	case Awigned16:
		wetuwn 16;
	case Awigned:
	defauwt:
		wetuwn size;
	}
}

static __awways_inwine int __wineawize(stwuct x86_emuwate_ctxt *ctxt,
				       stwuct segmented_addwess addw,
				       unsigned *max_size, unsigned size,
				       enum x86emuw_mode mode, uwong *wineaw,
				       unsigned int fwags)
{
	stwuct desc_stwuct desc;
	boow usabwe;
	uwong wa;
	u32 wim;
	u16 sew;
	u8  va_bits;

	wa = seg_base(ctxt, addw.seg) + addw.ea;
	*max_size = 0;
	switch (mode) {
	case X86EMUW_MODE_PWOT64:
		*wineaw = wa = ctxt->ops->get_untagged_addw(ctxt, wa, fwags);
		va_bits = ctxt_viwt_addw_bits(ctxt);
		if (!__is_canonicaw_addwess(wa, va_bits))
			goto bad;

		*max_size = min_t(u64, ~0u, (1uww << va_bits) - wa);
		if (size > *max_size)
			goto bad;
		bweak;
	defauwt:
		*wineaw = wa = (u32)wa;
		usabwe = ctxt->ops->get_segment(ctxt, &sew, &desc, NUWW,
						addw.seg);
		if (!usabwe)
			goto bad;
		/* code segment in pwotected mode ow wead-onwy data segment */
		if ((((ctxt->mode != X86EMUW_MODE_WEAW) && (desc.type & 8)) || !(desc.type & 2)) &&
		    (fwags & X86EMUW_F_WWITE))
			goto bad;
		/* unweadabwe code segment */
		if (!(fwags & X86EMUW_F_FETCH) && (desc.type & 8) && !(desc.type & 2))
			goto bad;
		wim = desc_wimit_scawed(&desc);
		if (!(desc.type & 8) && (desc.type & 4)) {
			/* expand-down segment */
			if (addw.ea <= wim)
				goto bad;
			wim = desc.d ? 0xffffffff : 0xffff;
		}
		if (addw.ea > wim)
			goto bad;
		if (wim == 0xffffffff)
			*max_size = ~0u;
		ewse {
			*max_size = (u64)wim + 1 - addw.ea;
			if (size > *max_size)
				goto bad;
		}
		bweak;
	}
	if (wa & (insn_awignment(ctxt, size) - 1))
		wetuwn emuwate_gp(ctxt, 0);
	wetuwn X86EMUW_CONTINUE;
bad:
	if (addw.seg == VCPU_SWEG_SS)
		wetuwn emuwate_ss(ctxt, 0);
	ewse
		wetuwn emuwate_gp(ctxt, 0);
}

static int wineawize(stwuct x86_emuwate_ctxt *ctxt,
		     stwuct segmented_addwess addw,
		     unsigned size, boow wwite,
		     uwong *wineaw)
{
	unsigned max_size;
	wetuwn __wineawize(ctxt, addw, &max_size, size, ctxt->mode, wineaw,
			   wwite ? X86EMUW_F_WWITE : 0);
}

static inwine int assign_eip(stwuct x86_emuwate_ctxt *ctxt, uwong dst)
{
	uwong wineaw;
	int wc;
	unsigned max_size;
	stwuct segmented_addwess addw = { .seg = VCPU_SWEG_CS,
					   .ea = dst };

	if (ctxt->op_bytes != sizeof(unsigned wong))
		addw.ea = dst & ((1UW << (ctxt->op_bytes << 3)) - 1);
	wc = __wineawize(ctxt, addw, &max_size, 1, ctxt->mode, &wineaw,
			 X86EMUW_F_FETCH);
	if (wc == X86EMUW_CONTINUE)
		ctxt->_eip = addw.ea;
	wetuwn wc;
}

static inwine int emuwatow_wecawc_and_set_mode(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 efew;
	stwuct desc_stwuct cs;
	u16 sewectow;
	u32 base3;

	ctxt->ops->get_msw(ctxt, MSW_EFEW, &efew);

	if (!(ctxt->ops->get_cw(ctxt, 0) & X86_CW0_PE)) {
		/* Weaw mode. cpu must not have wong mode active */
		if (efew & EFEW_WMA)
			wetuwn X86EMUW_UNHANDWEABWE;
		ctxt->mode = X86EMUW_MODE_WEAW;
		wetuwn X86EMUW_CONTINUE;
	}

	if (ctxt->efwags & X86_EFWAGS_VM) {
		/* Pwotected/VM86 mode. cpu must not have wong mode active */
		if (efew & EFEW_WMA)
			wetuwn X86EMUW_UNHANDWEABWE;
		ctxt->mode = X86EMUW_MODE_VM86;
		wetuwn X86EMUW_CONTINUE;
	}

	if (!ctxt->ops->get_segment(ctxt, &sewectow, &cs, &base3, VCPU_SWEG_CS))
		wetuwn X86EMUW_UNHANDWEABWE;

	if (efew & EFEW_WMA) {
		if (cs.w) {
			/* Pwopew wong mode */
			ctxt->mode = X86EMUW_MODE_PWOT64;
		} ewse if (cs.d) {
			/* 32 bit compatibiwity mode*/
			ctxt->mode = X86EMUW_MODE_PWOT32;
		} ewse {
			ctxt->mode = X86EMUW_MODE_PWOT16;
		}
	} ewse {
		/* Wegacy 32 bit / 16 bit mode */
		ctxt->mode = cs.d ? X86EMUW_MODE_PWOT32 : X86EMUW_MODE_PWOT16;
	}

	wetuwn X86EMUW_CONTINUE;
}

static inwine int assign_eip_neaw(stwuct x86_emuwate_ctxt *ctxt, uwong dst)
{
	wetuwn assign_eip(ctxt, dst);
}

static int assign_eip_faw(stwuct x86_emuwate_ctxt *ctxt, uwong dst)
{
	int wc = emuwatow_wecawc_and_set_mode(ctxt);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wetuwn assign_eip(ctxt, dst);
}

static inwine int jmp_wew(stwuct x86_emuwate_ctxt *ctxt, int wew)
{
	wetuwn assign_eip_neaw(ctxt, ctxt->_eip + wew);
}

static int wineaw_wead_system(stwuct x86_emuwate_ctxt *ctxt, uwong wineaw,
			      void *data, unsigned size)
{
	wetuwn ctxt->ops->wead_std(ctxt, wineaw, data, size, &ctxt->exception, twue);
}

static int wineaw_wwite_system(stwuct x86_emuwate_ctxt *ctxt,
			       uwong wineaw, void *data,
			       unsigned int size)
{
	wetuwn ctxt->ops->wwite_std(ctxt, wineaw, data, size, &ctxt->exception, twue);
}

static int segmented_wead_std(stwuct x86_emuwate_ctxt *ctxt,
			      stwuct segmented_addwess addw,
			      void *data,
			      unsigned size)
{
	int wc;
	uwong wineaw;

	wc = wineawize(ctxt, addw, size, fawse, &wineaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn ctxt->ops->wead_std(ctxt, wineaw, data, size, &ctxt->exception, fawse);
}

static int segmented_wwite_std(stwuct x86_emuwate_ctxt *ctxt,
			       stwuct segmented_addwess addw,
			       void *data,
			       unsigned int size)
{
	int wc;
	uwong wineaw;

	wc = wineawize(ctxt, addw, size, twue, &wineaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn ctxt->ops->wwite_std(ctxt, wineaw, data, size, &ctxt->exception, fawse);
}

/*
 * Pwefetch the wemaining bytes of the instwuction without cwossing page
 * boundawy if they awe not in fetch_cache yet.
 */
static int __do_insn_fetch_bytes(stwuct x86_emuwate_ctxt *ctxt, int op_size)
{
	int wc;
	unsigned size, max_size;
	unsigned wong wineaw;
	int cuw_size = ctxt->fetch.end - ctxt->fetch.data;
	stwuct segmented_addwess addw = { .seg = VCPU_SWEG_CS,
					   .ea = ctxt->eip + cuw_size };

	/*
	 * We do not know exactwy how many bytes wiww be needed, and
	 * __wineawize is expensive, so fetch as much as possibwe.  We
	 * just have to avoid going beyond the 15 byte wimit, the end
	 * of the segment, ow the end of the page.
	 *
	 * __wineawize is cawwed with size 0 so that it does not do any
	 * boundawy check itsewf.  Instead, we use max_size to check
	 * against op_size.
	 */
	wc = __wineawize(ctxt, addw, &max_size, 0, ctxt->mode, &wineaw,
			 X86EMUW_F_FETCH);
	if (unwikewy(wc != X86EMUW_CONTINUE))
		wetuwn wc;

	size = min_t(unsigned, 15UW ^ cuw_size, max_size);
	size = min_t(unsigned, size, PAGE_SIZE - offset_in_page(wineaw));

	/*
	 * One instwuction can onwy stwaddwe two pages,
	 * and one has been woaded at the beginning of
	 * x86_decode_insn.  So, if not enough bytes
	 * stiww, we must have hit the 15-byte boundawy.
	 */
	if (unwikewy(size < op_size))
		wetuwn emuwate_gp(ctxt, 0);

	wc = ctxt->ops->fetch(ctxt, wineaw, ctxt->fetch.end,
			      size, &ctxt->exception);
	if (unwikewy(wc != X86EMUW_CONTINUE))
		wetuwn wc;
	ctxt->fetch.end += size;
	wetuwn X86EMUW_CONTINUE;
}

static __awways_inwine int do_insn_fetch_bytes(stwuct x86_emuwate_ctxt *ctxt,
					       unsigned size)
{
	unsigned done_size = ctxt->fetch.end - ctxt->fetch.ptw;

	if (unwikewy(done_size < size))
		wetuwn __do_insn_fetch_bytes(ctxt, size - done_size);
	ewse
		wetuwn X86EMUW_CONTINUE;
}

/* Fetch next pawt of the instwuction being emuwated. */
#define insn_fetch(_type, _ctxt)					\
({	_type _x;							\
									\
	wc = do_insn_fetch_bytes(_ctxt, sizeof(_type));			\
	if (wc != X86EMUW_CONTINUE)					\
		goto done;						\
	ctxt->_eip += sizeof(_type);					\
	memcpy(&_x, ctxt->fetch.ptw, sizeof(_type));			\
	ctxt->fetch.ptw += sizeof(_type);				\
	_x;								\
})

#define insn_fetch_aww(_aww, _size, _ctxt)				\
({									\
	wc = do_insn_fetch_bytes(_ctxt, _size);				\
	if (wc != X86EMUW_CONTINUE)					\
		goto done;						\
	ctxt->_eip += (_size);						\
	memcpy(_aww, ctxt->fetch.ptw, _size);				\
	ctxt->fetch.ptw += (_size);					\
})

/*
 * Given the 'weg' powtion of a ModWM byte, and a wegistew bwock, wetuwn a
 * pointew into the bwock that addwesses the wewevant wegistew.
 * @highbyte_wegs specifies whethew to decode AH,CH,DH,BH.
 */
static void *decode_wegistew(stwuct x86_emuwate_ctxt *ctxt, u8 modwm_weg,
			     int byteop)
{
	void *p;
	int highbyte_wegs = (ctxt->wex_pwefix == 0) && byteop;

	if (highbyte_wegs && modwm_weg >= 4 && modwm_weg < 8)
		p = (unsigned chaw *)weg_wmw(ctxt, modwm_weg & 3) + 1;
	ewse
		p = weg_wmw(ctxt, modwm_weg);
	wetuwn p;
}

static int wead_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
			   stwuct segmented_addwess addw,
			   u16 *size, unsigned wong *addwess, int op_bytes)
{
	int wc;

	if (op_bytes == 2)
		op_bytes = 3;
	*addwess = 0;
	wc = segmented_wead_std(ctxt, addw, size, 2);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	addw.ea += 2;
	wc = segmented_wead_std(ctxt, addw, addwess, op_bytes);
	wetuwn wc;
}

FASTOP2(add);
FASTOP2(ow);
FASTOP2(adc);
FASTOP2(sbb);
FASTOP2(and);
FASTOP2(sub);
FASTOP2(xow);
FASTOP2(cmp);
FASTOP2(test);

FASTOP1SWC2(muw, muw_ex);
FASTOP1SWC2(imuw, imuw_ex);
FASTOP1SWC2EX(div, div_ex);
FASTOP1SWC2EX(idiv, idiv_ex);

FASTOP3WCW(shwd);
FASTOP3WCW(shwd);

FASTOP2W(imuw);

FASTOP1(not);
FASTOP1(neg);
FASTOP1(inc);
FASTOP1(dec);

FASTOP2CW(wow);
FASTOP2CW(wow);
FASTOP2CW(wcw);
FASTOP2CW(wcw);
FASTOP2CW(shw);
FASTOP2CW(shw);
FASTOP2CW(saw);

FASTOP2W(bsf);
FASTOP2W(bsw);
FASTOP2W(bt);
FASTOP2W(bts);
FASTOP2W(btw);
FASTOP2W(btc);

FASTOP2(xadd);

FASTOP2W(cmp, cmp_w);

static int em_bsf_c(stwuct x86_emuwate_ctxt *ctxt)
{
	/* If swc is zewo, do not wwiteback, but update fwags */
	if (ctxt->swc.vaw == 0)
		ctxt->dst.type = OP_NONE;
	wetuwn fastop(ctxt, em_bsf);
}

static int em_bsw_c(stwuct x86_emuwate_ctxt *ctxt)
{
	/* If swc is zewo, do not wwiteback, but update fwags */
	if (ctxt->swc.vaw == 0)
		ctxt->dst.type = OP_NONE;
	wetuwn fastop(ctxt, em_bsw);
}

static __awways_inwine u8 test_cc(unsigned int condition, unsigned wong fwags)
{
	u8 wc;
	void (*fop)(void) = (void *)em_setcc + FASTOP_SIZE * (condition & 0xf);

	fwags = (fwags & EFWAGS_MASK) | X86_EFWAGS_IF;
	asm("push %[fwags]; popf; " CAWW_NOSPEC
	    : "=a"(wc) : [thunk_tawget]"w"(fop), [fwags]"w"(fwags));
	wetuwn wc;
}

static void fetch_wegistew_opewand(stwuct opewand *op)
{
	switch (op->bytes) {
	case 1:
		op->vaw = *(u8 *)op->addw.weg;
		bweak;
	case 2:
		op->vaw = *(u16 *)op->addw.weg;
		bweak;
	case 4:
		op->vaw = *(u32 *)op->addw.weg;
		bweak;
	case 8:
		op->vaw = *(u64 *)op->addw.weg;
		bweak;
	}
}

static int em_fninit(stwuct x86_emuwate_ctxt *ctxt)
{
	if (ctxt->ops->get_cw(ctxt, 0) & (X86_CW0_TS | X86_CW0_EM))
		wetuwn emuwate_nm(ctxt);

	kvm_fpu_get();
	asm vowatiwe("fninit");
	kvm_fpu_put();
	wetuwn X86EMUW_CONTINUE;
}

static int em_fnstcw(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 fcw;

	if (ctxt->ops->get_cw(ctxt, 0) & (X86_CW0_TS | X86_CW0_EM))
		wetuwn emuwate_nm(ctxt);

	kvm_fpu_get();
	asm vowatiwe("fnstcw %0": "+m"(fcw));
	kvm_fpu_put();

	ctxt->dst.vaw = fcw;

	wetuwn X86EMUW_CONTINUE;
}

static int em_fnstsw(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 fsw;

	if (ctxt->ops->get_cw(ctxt, 0) & (X86_CW0_TS | X86_CW0_EM))
		wetuwn emuwate_nm(ctxt);

	kvm_fpu_get();
	asm vowatiwe("fnstsw %0": "+m"(fsw));
	kvm_fpu_put();

	ctxt->dst.vaw = fsw;

	wetuwn X86EMUW_CONTINUE;
}

static void decode_wegistew_opewand(stwuct x86_emuwate_ctxt *ctxt,
				    stwuct opewand *op)
{
	unsigned int weg;

	if (ctxt->d & ModWM)
		weg = ctxt->modwm_weg;
	ewse
		weg = (ctxt->b & 7) | ((ctxt->wex_pwefix & 1) << 3);

	if (ctxt->d & Sse) {
		op->type = OP_XMM;
		op->bytes = 16;
		op->addw.xmm = weg;
		kvm_wead_sse_weg(weg, &op->vec_vaw);
		wetuwn;
	}
	if (ctxt->d & Mmx) {
		weg &= 7;
		op->type = OP_MM;
		op->bytes = 8;
		op->addw.mm = weg;
		wetuwn;
	}

	op->type = OP_WEG;
	op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	op->addw.weg = decode_wegistew(ctxt, weg, ctxt->d & ByteOp);

	fetch_wegistew_opewand(op);
	op->owig_vaw = op->vaw;
}

static void adjust_modwm_seg(stwuct x86_emuwate_ctxt *ctxt, int base_weg)
{
	if (base_weg == VCPU_WEGS_WSP || base_weg == VCPU_WEGS_WBP)
		ctxt->modwm_seg = VCPU_SWEG_SS;
}

static int decode_modwm(stwuct x86_emuwate_ctxt *ctxt,
			stwuct opewand *op)
{
	u8 sib;
	int index_weg, base_weg, scawe;
	int wc = X86EMUW_CONTINUE;
	uwong modwm_ea = 0;

	ctxt->modwm_weg = ((ctxt->wex_pwefix << 1) & 8); /* WEX.W */
	index_weg = (ctxt->wex_pwefix << 2) & 8; /* WEX.X */
	base_weg = (ctxt->wex_pwefix << 3) & 8; /* WEX.B */

	ctxt->modwm_mod = (ctxt->modwm & 0xc0) >> 6;
	ctxt->modwm_weg |= (ctxt->modwm & 0x38) >> 3;
	ctxt->modwm_wm = base_weg | (ctxt->modwm & 0x07);
	ctxt->modwm_seg = VCPU_SWEG_DS;

	if (ctxt->modwm_mod == 3 || (ctxt->d & NoMod)) {
		op->type = OP_WEG;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addw.weg = decode_wegistew(ctxt, ctxt->modwm_wm,
				ctxt->d & ByteOp);
		if (ctxt->d & Sse) {
			op->type = OP_XMM;
			op->bytes = 16;
			op->addw.xmm = ctxt->modwm_wm;
			kvm_wead_sse_weg(ctxt->modwm_wm, &op->vec_vaw);
			wetuwn wc;
		}
		if (ctxt->d & Mmx) {
			op->type = OP_MM;
			op->bytes = 8;
			op->addw.mm = ctxt->modwm_wm & 7;
			wetuwn wc;
		}
		fetch_wegistew_opewand(op);
		wetuwn wc;
	}

	op->type = OP_MEM;

	if (ctxt->ad_bytes == 2) {
		unsigned bx = weg_wead(ctxt, VCPU_WEGS_WBX);
		unsigned bp = weg_wead(ctxt, VCPU_WEGS_WBP);
		unsigned si = weg_wead(ctxt, VCPU_WEGS_WSI);
		unsigned di = weg_wead(ctxt, VCPU_WEGS_WDI);

		/* 16-bit ModW/M decode. */
		switch (ctxt->modwm_mod) {
		case 0:
			if (ctxt->modwm_wm == 6)
				modwm_ea += insn_fetch(u16, ctxt);
			bweak;
		case 1:
			modwm_ea += insn_fetch(s8, ctxt);
			bweak;
		case 2:
			modwm_ea += insn_fetch(u16, ctxt);
			bweak;
		}
		switch (ctxt->modwm_wm) {
		case 0:
			modwm_ea += bx + si;
			bweak;
		case 1:
			modwm_ea += bx + di;
			bweak;
		case 2:
			modwm_ea += bp + si;
			bweak;
		case 3:
			modwm_ea += bp + di;
			bweak;
		case 4:
			modwm_ea += si;
			bweak;
		case 5:
			modwm_ea += di;
			bweak;
		case 6:
			if (ctxt->modwm_mod != 0)
				modwm_ea += bp;
			bweak;
		case 7:
			modwm_ea += bx;
			bweak;
		}
		if (ctxt->modwm_wm == 2 || ctxt->modwm_wm == 3 ||
		    (ctxt->modwm_wm == 6 && ctxt->modwm_mod != 0))
			ctxt->modwm_seg = VCPU_SWEG_SS;
		modwm_ea = (u16)modwm_ea;
	} ewse {
		/* 32/64-bit ModW/M decode. */
		if ((ctxt->modwm_wm & 7) == 4) {
			sib = insn_fetch(u8, ctxt);
			index_weg |= (sib >> 3) & 7;
			base_weg |= sib & 7;
			scawe = sib >> 6;

			if ((base_weg & 7) == 5 && ctxt->modwm_mod == 0)
				modwm_ea += insn_fetch(s32, ctxt);
			ewse {
				modwm_ea += weg_wead(ctxt, base_weg);
				adjust_modwm_seg(ctxt, base_weg);
				/* Incwement ESP on POP [ESP] */
				if ((ctxt->d & IncSP) &&
				    base_weg == VCPU_WEGS_WSP)
					modwm_ea += ctxt->op_bytes;
			}
			if (index_weg != 4)
				modwm_ea += weg_wead(ctxt, index_weg) << scawe;
		} ewse if ((ctxt->modwm_wm & 7) == 5 && ctxt->modwm_mod == 0) {
			modwm_ea += insn_fetch(s32, ctxt);
			if (ctxt->mode == X86EMUW_MODE_PWOT64)
				ctxt->wip_wewative = 1;
		} ewse {
			base_weg = ctxt->modwm_wm;
			modwm_ea += weg_wead(ctxt, base_weg);
			adjust_modwm_seg(ctxt, base_weg);
		}
		switch (ctxt->modwm_mod) {
		case 1:
			modwm_ea += insn_fetch(s8, ctxt);
			bweak;
		case 2:
			modwm_ea += insn_fetch(s32, ctxt);
			bweak;
		}
	}
	op->addw.mem.ea = modwm_ea;
	if (ctxt->ad_bytes != 8)
		ctxt->memop.addw.mem.ea = (u32)ctxt->memop.addw.mem.ea;

done:
	wetuwn wc;
}

static int decode_abs(stwuct x86_emuwate_ctxt *ctxt,
		      stwuct opewand *op)
{
	int wc = X86EMUW_CONTINUE;

	op->type = OP_MEM;
	switch (ctxt->ad_bytes) {
	case 2:
		op->addw.mem.ea = insn_fetch(u16, ctxt);
		bweak;
	case 4:
		op->addw.mem.ea = insn_fetch(u32, ctxt);
		bweak;
	case 8:
		op->addw.mem.ea = insn_fetch(u64, ctxt);
		bweak;
	}
done:
	wetuwn wc;
}

static void fetch_bit_opewand(stwuct x86_emuwate_ctxt *ctxt)
{
	wong sv = 0, mask;

	if (ctxt->dst.type == OP_MEM && ctxt->swc.type == OP_WEG) {
		mask = ~((wong)ctxt->dst.bytes * 8 - 1);

		if (ctxt->swc.bytes == 2)
			sv = (s16)ctxt->swc.vaw & (s16)mask;
		ewse if (ctxt->swc.bytes == 4)
			sv = (s32)ctxt->swc.vaw & (s32)mask;
		ewse
			sv = (s64)ctxt->swc.vaw & (s64)mask;

		ctxt->dst.addw.mem.ea = addwess_mask(ctxt,
					   ctxt->dst.addw.mem.ea + (sv >> 3));
	}

	/* onwy subwowd offset */
	ctxt->swc.vaw &= (ctxt->dst.bytes << 3) - 1;
}

static int wead_emuwated(stwuct x86_emuwate_ctxt *ctxt,
			 unsigned wong addw, void *dest, unsigned size)
{
	int wc;
	stwuct wead_cache *mc = &ctxt->mem_wead;

	if (mc->pos < mc->end)
		goto wead_cached;

	if (KVM_EMUWATOW_BUG_ON((mc->end + size) >= sizeof(mc->data), ctxt))
		wetuwn X86EMUW_UNHANDWEABWE;

	wc = ctxt->ops->wead_emuwated(ctxt, addw, mc->data + mc->end, size,
				      &ctxt->exception);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	mc->end += size;

wead_cached:
	memcpy(dest, mc->data + mc->pos, size);
	mc->pos += size;
	wetuwn X86EMUW_CONTINUE;
}

static int segmented_wead(stwuct x86_emuwate_ctxt *ctxt,
			  stwuct segmented_addwess addw,
			  void *data,
			  unsigned size)
{
	int wc;
	uwong wineaw;

	wc = wineawize(ctxt, addw, size, fawse, &wineaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn wead_emuwated(ctxt, wineaw, data, size);
}

static int segmented_wwite(stwuct x86_emuwate_ctxt *ctxt,
			   stwuct segmented_addwess addw,
			   const void *data,
			   unsigned size)
{
	int wc;
	uwong wineaw;

	wc = wineawize(ctxt, addw, size, twue, &wineaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn ctxt->ops->wwite_emuwated(ctxt, wineaw, data, size,
					 &ctxt->exception);
}

static int segmented_cmpxchg(stwuct x86_emuwate_ctxt *ctxt,
			     stwuct segmented_addwess addw,
			     const void *owig_data, const void *data,
			     unsigned size)
{
	int wc;
	uwong wineaw;

	wc = wineawize(ctxt, addw, size, twue, &wineaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn ctxt->ops->cmpxchg_emuwated(ctxt, wineaw, owig_data, data,
					   size, &ctxt->exception);
}

static int pio_in_emuwated(stwuct x86_emuwate_ctxt *ctxt,
			   unsigned int size, unsigned showt powt,
			   void *dest)
{
	stwuct wead_cache *wc = &ctxt->io_wead;

	if (wc->pos == wc->end) { /* wefiww pio wead ahead */
		unsigned int in_page, n;
		unsigned int count = ctxt->wep_pwefix ?
			addwess_mask(ctxt, weg_wead(ctxt, VCPU_WEGS_WCX)) : 1;
		in_page = (ctxt->efwags & X86_EFWAGS_DF) ?
			offset_in_page(weg_wead(ctxt, VCPU_WEGS_WDI)) :
			PAGE_SIZE - offset_in_page(weg_wead(ctxt, VCPU_WEGS_WDI));
		n = min3(in_page, (unsigned int)sizeof(wc->data) / size, count);
		if (n == 0)
			n = 1;
		wc->pos = wc->end = 0;
		if (!ctxt->ops->pio_in_emuwated(ctxt, size, powt, wc->data, n))
			wetuwn 0;
		wc->end = n * size;
	}

	if (ctxt->wep_pwefix && (ctxt->d & Stwing) &&
	    !(ctxt->efwags & X86_EFWAGS_DF)) {
		ctxt->dst.data = wc->data + wc->pos;
		ctxt->dst.type = OP_MEM_STW;
		ctxt->dst.count = (wc->end - wc->pos) / size;
		wc->pos = wc->end;
	} ewse {
		memcpy(dest, wc->data + wc->pos, size);
		wc->pos += size;
	}
	wetuwn 1;
}

static int wead_intewwupt_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
				     u16 index, stwuct desc_stwuct *desc)
{
	stwuct desc_ptw dt;
	uwong addw;

	ctxt->ops->get_idt(ctxt, &dt);

	if (dt.size < index * 8 + 7)
		wetuwn emuwate_gp(ctxt, index << 3 | 0x2);

	addw = dt.addwess + index * 8;
	wetuwn wineaw_wead_system(ctxt, addw, desc, sizeof(*desc));
}

static void get_descwiptow_tabwe_ptw(stwuct x86_emuwate_ctxt *ctxt,
				     u16 sewectow, stwuct desc_ptw *dt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	u32 base3 = 0;

	if (sewectow & 1 << 2) {
		stwuct desc_stwuct desc;
		u16 sew;

		memset(dt, 0, sizeof(*dt));
		if (!ops->get_segment(ctxt, &sew, &desc, &base3,
				      VCPU_SWEG_WDTW))
			wetuwn;

		dt->size = desc_wimit_scawed(&desc); /* what if wimit > 65535? */
		dt->addwess = get_desc_base(&desc) | ((u64)base3 << 32);
	} ewse
		ops->get_gdt(ctxt, dt);
}

static int get_descwiptow_ptw(stwuct x86_emuwate_ctxt *ctxt,
			      u16 sewectow, uwong *desc_addw_p)
{
	stwuct desc_ptw dt;
	u16 index = sewectow >> 3;
	uwong addw;

	get_descwiptow_tabwe_ptw(ctxt, sewectow, &dt);

	if (dt.size < index * 8 + 7)
		wetuwn emuwate_gp(ctxt, sewectow & 0xfffc);

	addw = dt.addwess + index * 8;

#ifdef CONFIG_X86_64
	if (addw >> 32 != 0) {
		u64 efew = 0;

		ctxt->ops->get_msw(ctxt, MSW_EFEW, &efew);
		if (!(efew & EFEW_WMA))
			addw &= (u32)-1;
	}
#endif

	*desc_addw_p = addw;
	wetuwn X86EMUW_CONTINUE;
}

/* awwowed just fow 8 bytes segments */
static int wead_segment_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
				   u16 sewectow, stwuct desc_stwuct *desc,
				   uwong *desc_addw_p)
{
	int wc;

	wc = get_descwiptow_ptw(ctxt, sewectow, desc_addw_p);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wetuwn wineaw_wead_system(ctxt, *desc_addw_p, desc, sizeof(*desc));
}

/* awwowed just fow 8 bytes segments */
static int wwite_segment_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
				    u16 sewectow, stwuct desc_stwuct *desc)
{
	int wc;
	uwong addw;

	wc = get_descwiptow_ptw(ctxt, sewectow, &addw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wetuwn wineaw_wwite_system(ctxt, addw, desc, sizeof(*desc));
}

static int __woad_segment_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
				     u16 sewectow, int seg, u8 cpw,
				     enum x86_twansfew_type twansfew,
				     stwuct desc_stwuct *desc)
{
	stwuct desc_stwuct seg_desc, owd_desc;
	u8 dpw, wpw;
	unsigned eww_vec = GP_VECTOW;
	u32 eww_code = 0;
	boow nuww_sewectow = !(sewectow & ~0x3); /* 0000-0003 awe nuww */
	uwong desc_addw;
	int wet;
	u16 dummy;
	u32 base3 = 0;

	memset(&seg_desc, 0, sizeof(seg_desc));

	if (ctxt->mode == X86EMUW_MODE_WEAW) {
		/* set weaw mode segment descwiptow (keep wimit etc. fow
		 * unweaw mode) */
		ctxt->ops->get_segment(ctxt, &dummy, &seg_desc, NUWW, seg);
		set_desc_base(&seg_desc, sewectow << 4);
		goto woad;
	} ewse if (seg <= VCPU_SWEG_GS && ctxt->mode == X86EMUW_MODE_VM86) {
		/* VM86 needs a cwean new segment descwiptow */
		set_desc_base(&seg_desc, sewectow << 4);
		set_desc_wimit(&seg_desc, 0xffff);
		seg_desc.type = 3;
		seg_desc.p = 1;
		seg_desc.s = 1;
		seg_desc.dpw = 3;
		goto woad;
	}

	wpw = sewectow & 3;

	/* TW shouwd be in GDT onwy */
	if (seg == VCPU_SWEG_TW && (sewectow & (1 << 2)))
		goto exception;

	/* NUWW sewectow is not vawid fow TW, CS and (except fow wong mode) SS */
	if (nuww_sewectow) {
		if (seg == VCPU_SWEG_CS || seg == VCPU_SWEG_TW)
			goto exception;

		if (seg == VCPU_SWEG_SS) {
			if (ctxt->mode != X86EMUW_MODE_PWOT64 || wpw != cpw)
				goto exception;

			/*
			 * ctxt->ops->set_segment expects the CPW to be in
			 * SS.DPW, so fake an expand-up 32-bit data segment.
			 */
			seg_desc.type = 3;
			seg_desc.p = 1;
			seg_desc.s = 1;
			seg_desc.dpw = cpw;
			seg_desc.d = 1;
			seg_desc.g = 1;
		}

		/* Skip aww fowwowing checks */
		goto woad;
	}

	wet = wead_segment_descwiptow(ctxt, sewectow, &seg_desc, &desc_addw);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	eww_code = sewectow & 0xfffc;
	eww_vec = (twansfew == X86_TWANSFEW_TASK_SWITCH) ? TS_VECTOW :
							   GP_VECTOW;

	/* can't woad system descwiptow into segment sewectow */
	if (seg <= VCPU_SWEG_GS && !seg_desc.s) {
		if (twansfew == X86_TWANSFEW_CAWW_JMP)
			wetuwn X86EMUW_UNHANDWEABWE;
		goto exception;
	}

	dpw = seg_desc.dpw;

	switch (seg) {
	case VCPU_SWEG_SS:
		/*
		 * segment is not a wwitabwe data segment ow segment
		 * sewectow's WPW != CPW ow DPW != CPW
		 */
		if (wpw != cpw || (seg_desc.type & 0xa) != 0x2 || dpw != cpw)
			goto exception;
		bweak;
	case VCPU_SWEG_CS:
		/*
		 * KVM uses "none" when woading CS as pawt of emuwating Weaw
		 * Mode exceptions and IWET (handwed above).  In aww othew
		 * cases, woading CS without a contwow twansfew is a KVM bug.
		 */
		if (WAWN_ON_ONCE(twansfew == X86_TWANSFEW_NONE))
			goto exception;

		if (!(seg_desc.type & 8))
			goto exception;

		if (twansfew == X86_TWANSFEW_WET) {
			/* WET can nevew wetuwn to an innew pwiviwege wevew. */
			if (wpw < cpw)
				goto exception;
			/* Outew-pwiviwege wevew wetuwn is not impwemented */
			if (wpw > cpw)
				wetuwn X86EMUW_UNHANDWEABWE;
		}
		if (twansfew == X86_TWANSFEW_WET || twansfew == X86_TWANSFEW_TASK_SWITCH) {
			if (seg_desc.type & 4) {
				/* confowming */
				if (dpw > wpw)
					goto exception;
			} ewse {
				/* nonconfowming */
				if (dpw != wpw)
					goto exception;
			}
		} ewse { /* X86_TWANSFEW_CAWW_JMP */
			if (seg_desc.type & 4) {
				/* confowming */
				if (dpw > cpw)
					goto exception;
			} ewse {
				/* nonconfowming */
				if (wpw > cpw || dpw != cpw)
					goto exception;
			}
		}
		/* in wong-mode d/b must be cweaw if w is set */
		if (seg_desc.d && seg_desc.w) {
			u64 efew = 0;

			ctxt->ops->get_msw(ctxt, MSW_EFEW, &efew);
			if (efew & EFEW_WMA)
				goto exception;
		}

		/* CS(WPW) <- CPW */
		sewectow = (sewectow & 0xfffc) | cpw;
		bweak;
	case VCPU_SWEG_TW:
		if (seg_desc.s || (seg_desc.type != 1 && seg_desc.type != 9))
			goto exception;
		bweak;
	case VCPU_SWEG_WDTW:
		if (seg_desc.s || seg_desc.type != 2)
			goto exception;
		bweak;
	defauwt: /*  DS, ES, FS, ow GS */
		/*
		 * segment is not a data ow weadabwe code segment ow
		 * ((segment is a data ow nonconfowming code segment)
		 * and ((WPW > DPW) ow (CPW > DPW)))
		 */
		if ((seg_desc.type & 0xa) == 0x8 ||
		    (((seg_desc.type & 0xc) != 0xc) &&
		     (wpw > dpw || cpw > dpw)))
			goto exception;
		bweak;
	}

	if (!seg_desc.p) {
		eww_vec = (seg == VCPU_SWEG_SS) ? SS_VECTOW : NP_VECTOW;
		goto exception;
	}

	if (seg_desc.s) {
		/* mawk segment as accessed */
		if (!(seg_desc.type & 1)) {
			seg_desc.type |= 1;
			wet = wwite_segment_descwiptow(ctxt, sewectow,
						       &seg_desc);
			if (wet != X86EMUW_CONTINUE)
				wetuwn wet;
		}
	} ewse if (ctxt->mode == X86EMUW_MODE_PWOT64) {
		wet = wineaw_wead_system(ctxt, desc_addw+8, &base3, sizeof(base3));
		if (wet != X86EMUW_CONTINUE)
			wetuwn wet;
		if (emuw_is_noncanonicaw_addwess(get_desc_base(&seg_desc) |
						 ((u64)base3 << 32), ctxt))
			wetuwn emuwate_gp(ctxt, eww_code);
	}

	if (seg == VCPU_SWEG_TW) {
		owd_desc = seg_desc;
		seg_desc.type |= 2; /* busy */
		wet = ctxt->ops->cmpxchg_emuwated(ctxt, desc_addw, &owd_desc, &seg_desc,
						  sizeof(seg_desc), &ctxt->exception);
		if (wet != X86EMUW_CONTINUE)
			wetuwn wet;
	}
woad:
	ctxt->ops->set_segment(ctxt, sewectow, &seg_desc, base3, seg);
	if (desc)
		*desc = seg_desc;
	wetuwn X86EMUW_CONTINUE;
exception:
	wetuwn emuwate_exception(ctxt, eww_vec, eww_code, twue);
}

static int woad_segment_descwiptow(stwuct x86_emuwate_ctxt *ctxt,
				   u16 sewectow, int seg)
{
	u8 cpw = ctxt->ops->cpw(ctxt);

	/*
	 * None of MOV, POP and WSS can woad a NUWW sewectow in CPW=3, but
	 * they can woad it at CPW<3 (Intew's manuaw says onwy WSS can,
	 * but it's wwong).
	 *
	 * Howevew, the Intew manuaw says that putting IST=1/DPW=3 in
	 * an intewwupt gate wiww wesuwt in SS=3 (the AMD manuaw instead
	 * says it doesn't), so awwow SS=3 in __woad_segment_descwiptow
	 * and onwy fowbid it hewe.
	 */
	if (seg == VCPU_SWEG_SS && sewectow == 3 &&
	    ctxt->mode == X86EMUW_MODE_PWOT64)
		wetuwn emuwate_exception(ctxt, GP_VECTOW, 0, twue);

	wetuwn __woad_segment_descwiptow(ctxt, sewectow, seg, cpw,
					 X86_TWANSFEW_NONE, NUWW);
}

static void wwite_wegistew_opewand(stwuct opewand *op)
{
	wetuwn assign_wegistew(op->addw.weg, op->vaw, op->bytes);
}

static int wwiteback(stwuct x86_emuwate_ctxt *ctxt, stwuct opewand *op)
{
	switch (op->type) {
	case OP_WEG:
		wwite_wegistew_opewand(op);
		bweak;
	case OP_MEM:
		if (ctxt->wock_pwefix)
			wetuwn segmented_cmpxchg(ctxt,
						 op->addw.mem,
						 &op->owig_vaw,
						 &op->vaw,
						 op->bytes);
		ewse
			wetuwn segmented_wwite(ctxt,
					       op->addw.mem,
					       &op->vaw,
					       op->bytes);
	case OP_MEM_STW:
		wetuwn segmented_wwite(ctxt,
				       op->addw.mem,
				       op->data,
				       op->bytes * op->count);
	case OP_XMM:
		kvm_wwite_sse_weg(op->addw.xmm, &op->vec_vaw);
		bweak;
	case OP_MM:
		kvm_wwite_mmx_weg(op->addw.mm, &op->mm_vaw);
		bweak;
	case OP_NONE:
		/* no wwiteback */
		bweak;
	defauwt:
		bweak;
	}
	wetuwn X86EMUW_CONTINUE;
}

static int push(stwuct x86_emuwate_ctxt *ctxt, void *data, int bytes)
{
	stwuct segmented_addwess addw;

	wsp_incwement(ctxt, -bytes);
	addw.ea = weg_wead(ctxt, VCPU_WEGS_WSP) & stack_mask(ctxt);
	addw.seg = VCPU_SWEG_SS;

	wetuwn segmented_wwite(ctxt, addw, data, bytes);
}

static int em_push(stwuct x86_emuwate_ctxt *ctxt)
{
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn push(ctxt, &ctxt->swc.vaw, ctxt->op_bytes);
}

static int emuwate_pop(stwuct x86_emuwate_ctxt *ctxt,
		       void *dest, int wen)
{
	int wc;
	stwuct segmented_addwess addw;

	addw.ea = weg_wead(ctxt, VCPU_WEGS_WSP) & stack_mask(ctxt);
	addw.seg = VCPU_SWEG_SS;
	wc = segmented_wead(ctxt, addw, dest, wen);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wsp_incwement(ctxt, wen);
	wetuwn wc;
}

static int em_pop(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_pop(ctxt, &ctxt->dst.vaw, ctxt->op_bytes);
}

static int emuwate_popf(stwuct x86_emuwate_ctxt *ctxt,
			void *dest, int wen)
{
	int wc;
	unsigned wong vaw, change_mask;
	int iopw = (ctxt->efwags & X86_EFWAGS_IOPW) >> X86_EFWAGS_IOPW_BIT;
	int cpw = ctxt->ops->cpw(ctxt);

	wc = emuwate_pop(ctxt, &vaw, wen);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	change_mask = X86_EFWAGS_CF | X86_EFWAGS_PF | X86_EFWAGS_AF |
		      X86_EFWAGS_ZF | X86_EFWAGS_SF | X86_EFWAGS_OF |
		      X86_EFWAGS_TF | X86_EFWAGS_DF | X86_EFWAGS_NT |
		      X86_EFWAGS_AC | X86_EFWAGS_ID;

	switch(ctxt->mode) {
	case X86EMUW_MODE_PWOT64:
	case X86EMUW_MODE_PWOT32:
	case X86EMUW_MODE_PWOT16:
		if (cpw == 0)
			change_mask |= X86_EFWAGS_IOPW;
		if (cpw <= iopw)
			change_mask |= X86_EFWAGS_IF;
		bweak;
	case X86EMUW_MODE_VM86:
		if (iopw < 3)
			wetuwn emuwate_gp(ctxt, 0);
		change_mask |= X86_EFWAGS_IF;
		bweak;
	defauwt: /* weaw mode */
		change_mask |= (X86_EFWAGS_IOPW | X86_EFWAGS_IF);
		bweak;
	}

	*(unsigned wong *)dest =
		(ctxt->efwags & ~change_mask) | (vaw & change_mask);

	wetuwn wc;
}

static int em_popf(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->dst.type = OP_WEG;
	ctxt->dst.addw.weg = &ctxt->efwags;
	ctxt->dst.bytes = ctxt->op_bytes;
	wetuwn emuwate_popf(ctxt, &ctxt->dst.vaw, ctxt->op_bytes);
}

static int em_entew(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	unsigned fwame_size = ctxt->swc.vaw;
	unsigned nesting_wevew = ctxt->swc2.vaw & 31;
	uwong wbp;

	if (nesting_wevew)
		wetuwn X86EMUW_UNHANDWEABWE;

	wbp = weg_wead(ctxt, VCPU_WEGS_WBP);
	wc = push(ctxt, &wbp, stack_size(ctxt));
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	assign_masked(weg_wmw(ctxt, VCPU_WEGS_WBP), weg_wead(ctxt, VCPU_WEGS_WSP),
		      stack_mask(ctxt));
	assign_masked(weg_wmw(ctxt, VCPU_WEGS_WSP),
		      weg_wead(ctxt, VCPU_WEGS_WSP) - fwame_size,
		      stack_mask(ctxt));
	wetuwn X86EMUW_CONTINUE;
}

static int em_weave(stwuct x86_emuwate_ctxt *ctxt)
{
	assign_masked(weg_wmw(ctxt, VCPU_WEGS_WSP), weg_wead(ctxt, VCPU_WEGS_WBP),
		      stack_mask(ctxt));
	wetuwn emuwate_pop(ctxt, weg_wmw(ctxt, VCPU_WEGS_WBP), ctxt->op_bytes);
}

static int em_push_sweg(stwuct x86_emuwate_ctxt *ctxt)
{
	int seg = ctxt->swc2.vaw;

	ctxt->swc.vaw = get_segment_sewectow(ctxt, seg);
	if (ctxt->op_bytes == 4) {
		wsp_incwement(ctxt, -2);
		ctxt->op_bytes = 2;
	}

	wetuwn em_push(ctxt);
}

static int em_pop_sweg(stwuct x86_emuwate_ctxt *ctxt)
{
	int seg = ctxt->swc2.vaw;
	unsigned wong sewectow;
	int wc;

	wc = emuwate_pop(ctxt, &sewectow, 2);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	if (seg == VCPU_SWEG_SS)
		ctxt->intewwuptibiwity = KVM_X86_SHADOW_INT_MOV_SS;
	if (ctxt->op_bytes > 2)
		wsp_incwement(ctxt, ctxt->op_bytes - 2);

	wc = woad_segment_descwiptow(ctxt, (u16)sewectow, seg);
	wetuwn wc;
}

static int em_pusha(stwuct x86_emuwate_ctxt *ctxt)
{
	unsigned wong owd_esp = weg_wead(ctxt, VCPU_WEGS_WSP);
	int wc = X86EMUW_CONTINUE;
	int weg = VCPU_WEGS_WAX;

	whiwe (weg <= VCPU_WEGS_WDI) {
		(weg == VCPU_WEGS_WSP) ?
		(ctxt->swc.vaw = owd_esp) : (ctxt->swc.vaw = weg_wead(ctxt, weg));

		wc = em_push(ctxt);
		if (wc != X86EMUW_CONTINUE)
			wetuwn wc;

		++weg;
	}

	wetuwn wc;
}

static int em_pushf(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->swc.vaw = (unsigned wong)ctxt->efwags & ~X86_EFWAGS_VM;
	wetuwn em_push(ctxt);
}

static int em_popa(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc = X86EMUW_CONTINUE;
	int weg = VCPU_WEGS_WDI;
	u32 vaw;

	whiwe (weg >= VCPU_WEGS_WAX) {
		if (weg == VCPU_WEGS_WSP) {
			wsp_incwement(ctxt, ctxt->op_bytes);
			--weg;
		}

		wc = emuwate_pop(ctxt, &vaw, ctxt->op_bytes);
		if (wc != X86EMUW_CONTINUE)
			bweak;
		assign_wegistew(weg_wmw(ctxt, weg), vaw, ctxt->op_bytes);
		--weg;
	}
	wetuwn wc;
}

static int __emuwate_int_weaw(stwuct x86_emuwate_ctxt *ctxt, int iwq)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	int wc;
	stwuct desc_ptw dt;
	gva_t cs_addw;
	gva_t eip_addw;
	u16 cs, eip;

	/* TODO: Add wimit checks */
	ctxt->swc.vaw = ctxt->efwags;
	wc = em_push(ctxt);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ctxt->efwags &= ~(X86_EFWAGS_IF | X86_EFWAGS_TF | X86_EFWAGS_AC);

	ctxt->swc.vaw = get_segment_sewectow(ctxt, VCPU_SWEG_CS);
	wc = em_push(ctxt);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ctxt->swc.vaw = ctxt->_eip;
	wc = em_push(ctxt);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ops->get_idt(ctxt, &dt);

	eip_addw = dt.addwess + (iwq << 2);
	cs_addw = dt.addwess + (iwq << 2) + 2;

	wc = wineaw_wead_system(ctxt, cs_addw, &cs, 2);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = wineaw_wead_system(ctxt, eip_addw, &eip, 2);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = woad_segment_descwiptow(ctxt, cs, VCPU_SWEG_CS);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ctxt->_eip = eip;

	wetuwn wc;
}

int emuwate_int_weaw(stwuct x86_emuwate_ctxt *ctxt, int iwq)
{
	int wc;

	invawidate_wegistews(ctxt);
	wc = __emuwate_int_weaw(ctxt, iwq);
	if (wc == X86EMUW_CONTINUE)
		wwiteback_wegistews(ctxt);
	wetuwn wc;
}

static int emuwate_int(stwuct x86_emuwate_ctxt *ctxt, int iwq)
{
	switch(ctxt->mode) {
	case X86EMUW_MODE_WEAW:
		wetuwn __emuwate_int_weaw(ctxt, iwq);
	case X86EMUW_MODE_VM86:
	case X86EMUW_MODE_PWOT16:
	case X86EMUW_MODE_PWOT32:
	case X86EMUW_MODE_PWOT64:
	defauwt:
		/* Pwotected mode intewwupts unimpwemented yet */
		wetuwn X86EMUW_UNHANDWEABWE;
	}
}

static int emuwate_iwet_weaw(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc = X86EMUW_CONTINUE;
	unsigned wong temp_eip = 0;
	unsigned wong temp_efwags = 0;
	unsigned wong cs = 0;
	unsigned wong mask = X86_EFWAGS_CF | X86_EFWAGS_PF | X86_EFWAGS_AF |
			     X86_EFWAGS_ZF | X86_EFWAGS_SF | X86_EFWAGS_TF |
			     X86_EFWAGS_IF | X86_EFWAGS_DF | X86_EFWAGS_OF |
			     X86_EFWAGS_IOPW | X86_EFWAGS_NT | X86_EFWAGS_WF |
			     X86_EFWAGS_AC | X86_EFWAGS_ID |
			     X86_EFWAGS_FIXED;
	unsigned wong vm86_mask = X86_EFWAGS_VM | X86_EFWAGS_VIF |
				  X86_EFWAGS_VIP;

	/* TODO: Add stack wimit check */

	wc = emuwate_pop(ctxt, &temp_eip, ctxt->op_bytes);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	if (temp_eip & ~0xffff)
		wetuwn emuwate_gp(ctxt, 0);

	wc = emuwate_pop(ctxt, &cs, ctxt->op_bytes);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = emuwate_pop(ctxt, &temp_efwags, ctxt->op_bytes);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = woad_segment_descwiptow(ctxt, (u16)cs, VCPU_SWEG_CS);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ctxt->_eip = temp_eip;

	if (ctxt->op_bytes == 4)
		ctxt->efwags = ((temp_efwags & mask) | (ctxt->efwags & vm86_mask));
	ewse if (ctxt->op_bytes == 2) {
		ctxt->efwags &= ~0xffff;
		ctxt->efwags |= temp_efwags;
	}

	ctxt->efwags &= ~EFWG_WESEWVED_ZEWOS_MASK; /* Cweaw wesewved zewos */
	ctxt->efwags |= X86_EFWAGS_FIXED;
	ctxt->ops->set_nmi_mask(ctxt, fawse);

	wetuwn wc;
}

static int em_iwet(stwuct x86_emuwate_ctxt *ctxt)
{
	switch(ctxt->mode) {
	case X86EMUW_MODE_WEAW:
		wetuwn emuwate_iwet_weaw(ctxt);
	case X86EMUW_MODE_VM86:
	case X86EMUW_MODE_PWOT16:
	case X86EMUW_MODE_PWOT32:
	case X86EMUW_MODE_PWOT64:
	defauwt:
		/* iwet fwom pwotected mode unimpwemented yet */
		wetuwn X86EMUW_UNHANDWEABWE;
	}
}

static int em_jmp_faw(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	unsigned showt sew;
	stwuct desc_stwuct new_desc;
	u8 cpw = ctxt->ops->cpw(ctxt);

	memcpy(&sew, ctxt->swc.vawptw + ctxt->op_bytes, 2);

	wc = __woad_segment_descwiptow(ctxt, sew, VCPU_SWEG_CS, cpw,
				       X86_TWANSFEW_CAWW_JMP,
				       &new_desc);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = assign_eip_faw(ctxt, ctxt->swc.vaw);
	/* Ewwow handwing is not impwemented. */
	if (wc != X86EMUW_CONTINUE)
		wetuwn X86EMUW_UNHANDWEABWE;

	wetuwn wc;
}

static int em_jmp_abs(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn assign_eip_neaw(ctxt, ctxt->swc.vaw);
}

static int em_caww_neaw_abs(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	wong int owd_eip;

	owd_eip = ctxt->_eip;
	wc = assign_eip_neaw(ctxt, ctxt->swc.vaw);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	ctxt->swc.vaw = owd_eip;
	wc = em_push(ctxt);
	wetuwn wc;
}

static int em_cmpxchg8b(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 owd = ctxt->dst.owig_vaw64;

	if (ctxt->dst.bytes == 16)
		wetuwn X86EMUW_UNHANDWEABWE;

	if (((u32) (owd >> 0) != (u32) weg_wead(ctxt, VCPU_WEGS_WAX)) ||
	    ((u32) (owd >> 32) != (u32) weg_wead(ctxt, VCPU_WEGS_WDX))) {
		*weg_wwite(ctxt, VCPU_WEGS_WAX) = (u32) (owd >> 0);
		*weg_wwite(ctxt, VCPU_WEGS_WDX) = (u32) (owd >> 32);
		ctxt->efwags &= ~X86_EFWAGS_ZF;
	} ewse {
		ctxt->dst.vaw64 = ((u64)weg_wead(ctxt, VCPU_WEGS_WCX) << 32) |
			(u32) weg_wead(ctxt, VCPU_WEGS_WBX);

		ctxt->efwags |= X86_EFWAGS_ZF;
	}
	wetuwn X86EMUW_CONTINUE;
}

static int em_wet(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	unsigned wong eip;

	wc = emuwate_pop(ctxt, &eip, ctxt->op_bytes);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wetuwn assign_eip_neaw(ctxt, eip);
}

static int em_wet_faw(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	unsigned wong eip, cs;
	int cpw = ctxt->ops->cpw(ctxt);
	stwuct desc_stwuct new_desc;

	wc = emuwate_pop(ctxt, &eip, ctxt->op_bytes);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wc = emuwate_pop(ctxt, &cs, ctxt->op_bytes);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wc = __woad_segment_descwiptow(ctxt, (u16)cs, VCPU_SWEG_CS, cpw,
				       X86_TWANSFEW_WET,
				       &new_desc);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wc = assign_eip_faw(ctxt, eip);
	/* Ewwow handwing is not impwemented. */
	if (wc != X86EMUW_CONTINUE)
		wetuwn X86EMUW_UNHANDWEABWE;

	wetuwn wc;
}

static int em_wet_faw_imm(stwuct x86_emuwate_ctxt *ctxt)
{
        int wc;

        wc = em_wet_faw(ctxt);
        if (wc != X86EMUW_CONTINUE)
                wetuwn wc;
        wsp_incwement(ctxt, ctxt->swc.vaw);
        wetuwn X86EMUW_CONTINUE;
}

static int em_cmpxchg(stwuct x86_emuwate_ctxt *ctxt)
{
	/* Save weaw souwce vawue, then compawe EAX against destination. */
	ctxt->dst.owig_vaw = ctxt->dst.vaw;
	ctxt->dst.vaw = weg_wead(ctxt, VCPU_WEGS_WAX);
	ctxt->swc.owig_vaw = ctxt->swc.vaw;
	ctxt->swc.vaw = ctxt->dst.owig_vaw;
	fastop(ctxt, em_cmp);

	if (ctxt->efwags & X86_EFWAGS_ZF) {
		/* Success: wwite back to memowy; no update of EAX */
		ctxt->swc.type = OP_NONE;
		ctxt->dst.vaw = ctxt->swc.owig_vaw;
	} ewse {
		/* Faiwuwe: wwite the vawue we saw to EAX. */
		ctxt->swc.type = OP_WEG;
		ctxt->swc.addw.weg = weg_wmw(ctxt, VCPU_WEGS_WAX);
		ctxt->swc.vaw = ctxt->dst.owig_vaw;
		/* Cweate wwite-cycwe to dest by wwiting the same vawue */
		ctxt->dst.vaw = ctxt->dst.owig_vaw;
	}
	wetuwn X86EMUW_CONTINUE;
}

static int em_wseg(stwuct x86_emuwate_ctxt *ctxt)
{
	int seg = ctxt->swc2.vaw;
	unsigned showt sew;
	int wc;

	memcpy(&sew, ctxt->swc.vawptw + ctxt->op_bytes, 2);

	wc = woad_segment_descwiptow(ctxt, sew, seg);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	ctxt->dst.vaw = ctxt->swc.vaw;
	wetuwn wc;
}

static int em_wsm(stwuct x86_emuwate_ctxt *ctxt)
{
	if (!ctxt->ops->is_smm(ctxt))
		wetuwn emuwate_ud(ctxt);

	if (ctxt->ops->weave_smm(ctxt))
		ctxt->ops->twipwe_fauwt(ctxt);

	wetuwn emuwatow_wecawc_and_set_mode(ctxt);
}

static void
setup_syscawws_segments(stwuct desc_stwuct *cs, stwuct desc_stwuct *ss)
{
	cs->w = 0;		/* wiww be adjusted watew */
	set_desc_base(cs, 0);	/* fwat segment */
	cs->g = 1;		/* 4kb gwanuwawity */
	set_desc_wimit(cs, 0xfffff);	/* 4GB wimit */
	cs->type = 0x0b;	/* Wead, Execute, Accessed */
	cs->s = 1;
	cs->dpw = 0;		/* wiww be adjusted watew */
	cs->p = 1;
	cs->d = 1;
	cs->avw = 0;

	set_desc_base(ss, 0);	/* fwat segment */
	set_desc_wimit(ss, 0xfffff);	/* 4GB wimit */
	ss->g = 1;		/* 4kb gwanuwawity */
	ss->s = 1;
	ss->type = 0x03;	/* Wead/Wwite, Accessed */
	ss->d = 1;		/* 32bit stack segment */
	ss->dpw = 0;
	ss->p = 1;
	ss->w = 0;
	ss->avw = 0;
}

static boow vendow_intew(stwuct x86_emuwate_ctxt *ctxt)
{
	u32 eax, ebx, ecx, edx;

	eax = ecx = 0;
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, twue);
	wetuwn is_guest_vendow_intew(ebx, ecx, edx);
}

static boow em_syscaww_is_enabwed(stwuct x86_emuwate_ctxt *ctxt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	u32 eax, ebx, ecx, edx;

	/*
	 * syscaww shouwd awways be enabwed in wongmode - so onwy become
	 * vendow specific (cpuid) if othew modes awe active...
	 */
	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		wetuwn twue;

	eax = 0x00000000;
	ecx = 0x00000000;
	ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, twue);
	/*
	 * wemawk: Intew CPUs onwy suppowt "syscaww" in 64bit wongmode. Awso a
	 * 64bit guest with a 32bit compat-app wunning wiww #UD !! Whiwe this
	 * behaviouw can be fixed (by emuwating) into AMD wesponse - CPUs of
	 * AMD can't behave wike Intew.
	 */
	if (is_guest_vendow_intew(ebx, ecx, edx))
		wetuwn fawse;

	if (is_guest_vendow_amd(ebx, ecx, edx) ||
	    is_guest_vendow_hygon(ebx, ecx, edx))
		wetuwn twue;

	/*
	 * defauwt: (not Intew, not AMD, not Hygon), appwy Intew's
	 * stwictew wuwes...
	 */
	wetuwn fawse;
}

static int em_syscaww(stwuct x86_emuwate_ctxt *ctxt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	stwuct desc_stwuct cs, ss;
	u64 msw_data;
	u16 cs_sew, ss_sew;
	u64 efew = 0;

	/* syscaww is not avaiwabwe in weaw mode */
	if (ctxt->mode == X86EMUW_MODE_WEAW ||
	    ctxt->mode == X86EMUW_MODE_VM86)
		wetuwn emuwate_ud(ctxt);

	if (!(em_syscaww_is_enabwed(ctxt)))
		wetuwn emuwate_ud(ctxt);

	ops->get_msw(ctxt, MSW_EFEW, &efew);
	if (!(efew & EFEW_SCE))
		wetuwn emuwate_ud(ctxt);

	setup_syscawws_segments(&cs, &ss);
	ops->get_msw(ctxt, MSW_STAW, &msw_data);
	msw_data >>= 32;
	cs_sew = (u16)(msw_data & 0xfffc);
	ss_sew = (u16)(msw_data + 8);

	if (efew & EFEW_WMA) {
		cs.d = 0;
		cs.w = 1;
	}
	ops->set_segment(ctxt, cs_sew, &cs, 0, VCPU_SWEG_CS);
	ops->set_segment(ctxt, ss_sew, &ss, 0, VCPU_SWEG_SS);

	*weg_wwite(ctxt, VCPU_WEGS_WCX) = ctxt->_eip;
	if (efew & EFEW_WMA) {
#ifdef CONFIG_X86_64
		*weg_wwite(ctxt, VCPU_WEGS_W11) = ctxt->efwags;

		ops->get_msw(ctxt,
			     ctxt->mode == X86EMUW_MODE_PWOT64 ?
			     MSW_WSTAW : MSW_CSTAW, &msw_data);
		ctxt->_eip = msw_data;

		ops->get_msw(ctxt, MSW_SYSCAWW_MASK, &msw_data);
		ctxt->efwags &= ~msw_data;
		ctxt->efwags |= X86_EFWAGS_FIXED;
#endif
	} ewse {
		/* wegacy mode */
		ops->get_msw(ctxt, MSW_STAW, &msw_data);
		ctxt->_eip = (u32)msw_data;

		ctxt->efwags &= ~(X86_EFWAGS_VM | X86_EFWAGS_IF);
	}

	ctxt->tf = (ctxt->efwags & X86_EFWAGS_TF) != 0;
	wetuwn X86EMUW_CONTINUE;
}

static int em_sysentew(stwuct x86_emuwate_ctxt *ctxt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	stwuct desc_stwuct cs, ss;
	u64 msw_data;
	u16 cs_sew, ss_sew;
	u64 efew = 0;

	ops->get_msw(ctxt, MSW_EFEW, &efew);
	/* inject #GP if in weaw mode */
	if (ctxt->mode == X86EMUW_MODE_WEAW)
		wetuwn emuwate_gp(ctxt, 0);

	/*
	 * Not wecognized on AMD in compat mode (but is wecognized in wegacy
	 * mode).
	 */
	if ((ctxt->mode != X86EMUW_MODE_PWOT64) && (efew & EFEW_WMA)
	    && !vendow_intew(ctxt))
		wetuwn emuwate_ud(ctxt);

	/* sysentew/sysexit have not been tested in 64bit mode. */
	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		wetuwn X86EMUW_UNHANDWEABWE;

	ops->get_msw(ctxt, MSW_IA32_SYSENTEW_CS, &msw_data);
	if ((msw_data & 0xfffc) == 0x0)
		wetuwn emuwate_gp(ctxt, 0);

	setup_syscawws_segments(&cs, &ss);
	ctxt->efwags &= ~(X86_EFWAGS_VM | X86_EFWAGS_IF);
	cs_sew = (u16)msw_data & ~SEGMENT_WPW_MASK;
	ss_sew = cs_sew + 8;
	if (efew & EFEW_WMA) {
		cs.d = 0;
		cs.w = 1;
	}

	ops->set_segment(ctxt, cs_sew, &cs, 0, VCPU_SWEG_CS);
	ops->set_segment(ctxt, ss_sew, &ss, 0, VCPU_SWEG_SS);

	ops->get_msw(ctxt, MSW_IA32_SYSENTEW_EIP, &msw_data);
	ctxt->_eip = (efew & EFEW_WMA) ? msw_data : (u32)msw_data;

	ops->get_msw(ctxt, MSW_IA32_SYSENTEW_ESP, &msw_data);
	*weg_wwite(ctxt, VCPU_WEGS_WSP) = (efew & EFEW_WMA) ? msw_data :
							      (u32)msw_data;
	if (efew & EFEW_WMA)
		ctxt->mode = X86EMUW_MODE_PWOT64;

	wetuwn X86EMUW_CONTINUE;
}

static int em_sysexit(stwuct x86_emuwate_ctxt *ctxt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	stwuct desc_stwuct cs, ss;
	u64 msw_data, wcx, wdx;
	int usewmode;
	u16 cs_sew = 0, ss_sew = 0;

	/* inject #GP if in weaw mode ow Viwtuaw 8086 mode */
	if (ctxt->mode == X86EMUW_MODE_WEAW ||
	    ctxt->mode == X86EMUW_MODE_VM86)
		wetuwn emuwate_gp(ctxt, 0);

	setup_syscawws_segments(&cs, &ss);

	if ((ctxt->wex_pwefix & 0x8) != 0x0)
		usewmode = X86EMUW_MODE_PWOT64;
	ewse
		usewmode = X86EMUW_MODE_PWOT32;

	wcx = weg_wead(ctxt, VCPU_WEGS_WCX);
	wdx = weg_wead(ctxt, VCPU_WEGS_WDX);

	cs.dpw = 3;
	ss.dpw = 3;
	ops->get_msw(ctxt, MSW_IA32_SYSENTEW_CS, &msw_data);
	switch (usewmode) {
	case X86EMUW_MODE_PWOT32:
		cs_sew = (u16)(msw_data + 16);
		if ((msw_data & 0xfffc) == 0x0)
			wetuwn emuwate_gp(ctxt, 0);
		ss_sew = (u16)(msw_data + 24);
		wcx = (u32)wcx;
		wdx = (u32)wdx;
		bweak;
	case X86EMUW_MODE_PWOT64:
		cs_sew = (u16)(msw_data + 32);
		if (msw_data == 0x0)
			wetuwn emuwate_gp(ctxt, 0);
		ss_sew = cs_sew + 8;
		cs.d = 0;
		cs.w = 1;
		if (emuw_is_noncanonicaw_addwess(wcx, ctxt) ||
		    emuw_is_noncanonicaw_addwess(wdx, ctxt))
			wetuwn emuwate_gp(ctxt, 0);
		bweak;
	}
	cs_sew |= SEGMENT_WPW_MASK;
	ss_sew |= SEGMENT_WPW_MASK;

	ops->set_segment(ctxt, cs_sew, &cs, 0, VCPU_SWEG_CS);
	ops->set_segment(ctxt, ss_sew, &ss, 0, VCPU_SWEG_SS);

	ctxt->_eip = wdx;
	ctxt->mode = usewmode;
	*weg_wwite(ctxt, VCPU_WEGS_WSP) = wcx;

	wetuwn X86EMUW_CONTINUE;
}

static boow emuwatow_bad_iopw(stwuct x86_emuwate_ctxt *ctxt)
{
	int iopw;
	if (ctxt->mode == X86EMUW_MODE_WEAW)
		wetuwn fawse;
	if (ctxt->mode == X86EMUW_MODE_VM86)
		wetuwn twue;
	iopw = (ctxt->efwags & X86_EFWAGS_IOPW) >> X86_EFWAGS_IOPW_BIT;
	wetuwn ctxt->ops->cpw(ctxt) > iopw;
}

#define VMWAWE_POWT_VMPOWT	(0x5658)
#define VMWAWE_POWT_VMWPC	(0x5659)

static boow emuwatow_io_powt_access_awwowed(stwuct x86_emuwate_ctxt *ctxt,
					    u16 powt, u16 wen)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	stwuct desc_stwuct tw_seg;
	u32 base3;
	int w;
	u16 tw, io_bitmap_ptw, pewm, bit_idx = powt & 0x7;
	unsigned mask = (1 << wen) - 1;
	unsigned wong base;

	/*
	 * VMwawe awwows access to these powts even if denied
	 * by TSS I/O pewmission bitmap. Mimic behaviow.
	 */
	if (enabwe_vmwawe_backdoow &&
	    ((powt == VMWAWE_POWT_VMPOWT) || (powt == VMWAWE_POWT_VMWPC)))
		wetuwn twue;

	ops->get_segment(ctxt, &tw, &tw_seg, &base3, VCPU_SWEG_TW);
	if (!tw_seg.p)
		wetuwn fawse;
	if (desc_wimit_scawed(&tw_seg) < 103)
		wetuwn fawse;
	base = get_desc_base(&tw_seg);
#ifdef CONFIG_X86_64
	base |= ((u64)base3) << 32;
#endif
	w = ops->wead_std(ctxt, base + 102, &io_bitmap_ptw, 2, NUWW, twue);
	if (w != X86EMUW_CONTINUE)
		wetuwn fawse;
	if (io_bitmap_ptw + powt/8 > desc_wimit_scawed(&tw_seg))
		wetuwn fawse;
	w = ops->wead_std(ctxt, base + io_bitmap_ptw + powt/8, &pewm, 2, NUWW, twue);
	if (w != X86EMUW_CONTINUE)
		wetuwn fawse;
	if ((pewm >> bit_idx) & mask)
		wetuwn fawse;
	wetuwn twue;
}

static boow emuwatow_io_pewmitted(stwuct x86_emuwate_ctxt *ctxt,
				  u16 powt, u16 wen)
{
	if (ctxt->pewm_ok)
		wetuwn twue;

	if (emuwatow_bad_iopw(ctxt))
		if (!emuwatow_io_powt_access_awwowed(ctxt, powt, wen))
			wetuwn fawse;

	ctxt->pewm_ok = twue;

	wetuwn twue;
}

static void stwing_wegistews_quiwk(stwuct x86_emuwate_ctxt *ctxt)
{
	/*
	 * Intew CPUs mask the countew and pointews in quite stwange
	 * mannew when ECX is zewo due to WEP-stwing optimizations.
	 */
#ifdef CONFIG_X86_64
	if (ctxt->ad_bytes != 4 || !vendow_intew(ctxt))
		wetuwn;

	*weg_wwite(ctxt, VCPU_WEGS_WCX) = 0;

	switch (ctxt->b) {
	case 0xa4:	/* movsb */
	case 0xa5:	/* movsd/w */
		*weg_wmw(ctxt, VCPU_WEGS_WSI) &= (u32)-1;
		fawwthwough;
	case 0xaa:	/* stosb */
	case 0xab:	/* stosd/w */
		*weg_wmw(ctxt, VCPU_WEGS_WDI) &= (u32)-1;
	}
#endif
}

static void save_state_to_tss16(stwuct x86_emuwate_ctxt *ctxt,
				stwuct tss_segment_16 *tss)
{
	tss->ip = ctxt->_eip;
	tss->fwag = ctxt->efwags;
	tss->ax = weg_wead(ctxt, VCPU_WEGS_WAX);
	tss->cx = weg_wead(ctxt, VCPU_WEGS_WCX);
	tss->dx = weg_wead(ctxt, VCPU_WEGS_WDX);
	tss->bx = weg_wead(ctxt, VCPU_WEGS_WBX);
	tss->sp = weg_wead(ctxt, VCPU_WEGS_WSP);
	tss->bp = weg_wead(ctxt, VCPU_WEGS_WBP);
	tss->si = weg_wead(ctxt, VCPU_WEGS_WSI);
	tss->di = weg_wead(ctxt, VCPU_WEGS_WDI);

	tss->es = get_segment_sewectow(ctxt, VCPU_SWEG_ES);
	tss->cs = get_segment_sewectow(ctxt, VCPU_SWEG_CS);
	tss->ss = get_segment_sewectow(ctxt, VCPU_SWEG_SS);
	tss->ds = get_segment_sewectow(ctxt, VCPU_SWEG_DS);
	tss->wdt = get_segment_sewectow(ctxt, VCPU_SWEG_WDTW);
}

static int woad_state_fwom_tss16(stwuct x86_emuwate_ctxt *ctxt,
				 stwuct tss_segment_16 *tss)
{
	int wet;
	u8 cpw;

	ctxt->_eip = tss->ip;
	ctxt->efwags = tss->fwag | 2;
	*weg_wwite(ctxt, VCPU_WEGS_WAX) = tss->ax;
	*weg_wwite(ctxt, VCPU_WEGS_WCX) = tss->cx;
	*weg_wwite(ctxt, VCPU_WEGS_WDX) = tss->dx;
	*weg_wwite(ctxt, VCPU_WEGS_WBX) = tss->bx;
	*weg_wwite(ctxt, VCPU_WEGS_WSP) = tss->sp;
	*weg_wwite(ctxt, VCPU_WEGS_WBP) = tss->bp;
	*weg_wwite(ctxt, VCPU_WEGS_WSI) = tss->si;
	*weg_wwite(ctxt, VCPU_WEGS_WDI) = tss->di;

	/*
	 * SDM says that segment sewectows awe woaded befowe segment
	 * descwiptows
	 */
	set_segment_sewectow(ctxt, tss->wdt, VCPU_SWEG_WDTW);
	set_segment_sewectow(ctxt, tss->es, VCPU_SWEG_ES);
	set_segment_sewectow(ctxt, tss->cs, VCPU_SWEG_CS);
	set_segment_sewectow(ctxt, tss->ss, VCPU_SWEG_SS);
	set_segment_sewectow(ctxt, tss->ds, VCPU_SWEG_DS);

	cpw = tss->cs & 3;

	/*
	 * Now woad segment descwiptows. If fauwt happens at this stage
	 * it is handwed in a context of new task
	 */
	wet = __woad_segment_descwiptow(ctxt, tss->wdt, VCPU_SWEG_WDTW, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->es, VCPU_SWEG_ES, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->cs, VCPU_SWEG_CS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->ss, VCPU_SWEG_SS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->ds, VCPU_SWEG_DS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	wetuwn X86EMUW_CONTINUE;
}

static int task_switch_16(stwuct x86_emuwate_ctxt *ctxt, u16 owd_tss_sew,
			  uwong owd_tss_base, stwuct desc_stwuct *new_desc)
{
	stwuct tss_segment_16 tss_seg;
	int wet;
	u32 new_tss_base = get_desc_base(new_desc);

	wet = wineaw_wead_system(ctxt, owd_tss_base, &tss_seg, sizeof(tss_seg));
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	save_state_to_tss16(ctxt, &tss_seg);

	wet = wineaw_wwite_system(ctxt, owd_tss_base, &tss_seg, sizeof(tss_seg));
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	wet = wineaw_wead_system(ctxt, new_tss_base, &tss_seg, sizeof(tss_seg));
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	if (owd_tss_sew != 0xffff) {
		tss_seg.pwev_task_wink = owd_tss_sew;

		wet = wineaw_wwite_system(ctxt, new_tss_base,
					  &tss_seg.pwev_task_wink,
					  sizeof(tss_seg.pwev_task_wink));
		if (wet != X86EMUW_CONTINUE)
			wetuwn wet;
	}

	wetuwn woad_state_fwom_tss16(ctxt, &tss_seg);
}

static void save_state_to_tss32(stwuct x86_emuwate_ctxt *ctxt,
				stwuct tss_segment_32 *tss)
{
	/* CW3 and wdt sewectow awe not saved intentionawwy */
	tss->eip = ctxt->_eip;
	tss->efwags = ctxt->efwags;
	tss->eax = weg_wead(ctxt, VCPU_WEGS_WAX);
	tss->ecx = weg_wead(ctxt, VCPU_WEGS_WCX);
	tss->edx = weg_wead(ctxt, VCPU_WEGS_WDX);
	tss->ebx = weg_wead(ctxt, VCPU_WEGS_WBX);
	tss->esp = weg_wead(ctxt, VCPU_WEGS_WSP);
	tss->ebp = weg_wead(ctxt, VCPU_WEGS_WBP);
	tss->esi = weg_wead(ctxt, VCPU_WEGS_WSI);
	tss->edi = weg_wead(ctxt, VCPU_WEGS_WDI);

	tss->es = get_segment_sewectow(ctxt, VCPU_SWEG_ES);
	tss->cs = get_segment_sewectow(ctxt, VCPU_SWEG_CS);
	tss->ss = get_segment_sewectow(ctxt, VCPU_SWEG_SS);
	tss->ds = get_segment_sewectow(ctxt, VCPU_SWEG_DS);
	tss->fs = get_segment_sewectow(ctxt, VCPU_SWEG_FS);
	tss->gs = get_segment_sewectow(ctxt, VCPU_SWEG_GS);
}

static int woad_state_fwom_tss32(stwuct x86_emuwate_ctxt *ctxt,
				 stwuct tss_segment_32 *tss)
{
	int wet;
	u8 cpw;

	if (ctxt->ops->set_cw(ctxt, 3, tss->cw3))
		wetuwn emuwate_gp(ctxt, 0);
	ctxt->_eip = tss->eip;
	ctxt->efwags = tss->efwags | 2;

	/* Genewaw puwpose wegistews */
	*weg_wwite(ctxt, VCPU_WEGS_WAX) = tss->eax;
	*weg_wwite(ctxt, VCPU_WEGS_WCX) = tss->ecx;
	*weg_wwite(ctxt, VCPU_WEGS_WDX) = tss->edx;
	*weg_wwite(ctxt, VCPU_WEGS_WBX) = tss->ebx;
	*weg_wwite(ctxt, VCPU_WEGS_WSP) = tss->esp;
	*weg_wwite(ctxt, VCPU_WEGS_WBP) = tss->ebp;
	*weg_wwite(ctxt, VCPU_WEGS_WSI) = tss->esi;
	*weg_wwite(ctxt, VCPU_WEGS_WDI) = tss->edi;

	/*
	 * SDM says that segment sewectows awe woaded befowe segment
	 * descwiptows.  This is impowtant because CPW checks wiww
	 * use CS.WPW.
	 */
	set_segment_sewectow(ctxt, tss->wdt_sewectow, VCPU_SWEG_WDTW);
	set_segment_sewectow(ctxt, tss->es, VCPU_SWEG_ES);
	set_segment_sewectow(ctxt, tss->cs, VCPU_SWEG_CS);
	set_segment_sewectow(ctxt, tss->ss, VCPU_SWEG_SS);
	set_segment_sewectow(ctxt, tss->ds, VCPU_SWEG_DS);
	set_segment_sewectow(ctxt, tss->fs, VCPU_SWEG_FS);
	set_segment_sewectow(ctxt, tss->gs, VCPU_SWEG_GS);

	/*
	 * If we'we switching between Pwotected Mode and VM86, we need to make
	 * suwe to update the mode befowe woading the segment descwiptows so
	 * that the sewectows awe intewpweted cowwectwy.
	 */
	if (ctxt->efwags & X86_EFWAGS_VM) {
		ctxt->mode = X86EMUW_MODE_VM86;
		cpw = 3;
	} ewse {
		ctxt->mode = X86EMUW_MODE_PWOT32;
		cpw = tss->cs & 3;
	}

	/*
	 * Now woad segment descwiptows. If fauwt happens at this stage
	 * it is handwed in a context of new task
	 */
	wet = __woad_segment_descwiptow(ctxt, tss->wdt_sewectow, VCPU_SWEG_WDTW,
					cpw, X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->es, VCPU_SWEG_ES, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->cs, VCPU_SWEG_CS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->ss, VCPU_SWEG_SS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->ds, VCPU_SWEG_DS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->fs, VCPU_SWEG_FS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = __woad_segment_descwiptow(ctxt, tss->gs, VCPU_SWEG_GS, cpw,
					X86_TWANSFEW_TASK_SWITCH, NUWW);

	wetuwn wet;
}

static int task_switch_32(stwuct x86_emuwate_ctxt *ctxt, u16 owd_tss_sew,
			  uwong owd_tss_base, stwuct desc_stwuct *new_desc)
{
	stwuct tss_segment_32 tss_seg;
	int wet;
	u32 new_tss_base = get_desc_base(new_desc);
	u32 eip_offset = offsetof(stwuct tss_segment_32, eip);
	u32 wdt_sew_offset = offsetof(stwuct tss_segment_32, wdt_sewectow);

	wet = wineaw_wead_system(ctxt, owd_tss_base, &tss_seg, sizeof(tss_seg));
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	save_state_to_tss32(ctxt, &tss_seg);

	/* Onwy GP wegistews and segment sewectows awe saved */
	wet = wineaw_wwite_system(ctxt, owd_tss_base + eip_offset, &tss_seg.eip,
				  wdt_sew_offset - eip_offset);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	wet = wineaw_wead_system(ctxt, new_tss_base, &tss_seg, sizeof(tss_seg));
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	if (owd_tss_sew != 0xffff) {
		tss_seg.pwev_task_wink = owd_tss_sew;

		wet = wineaw_wwite_system(ctxt, new_tss_base,
					  &tss_seg.pwev_task_wink,
					  sizeof(tss_seg.pwev_task_wink));
		if (wet != X86EMUW_CONTINUE)
			wetuwn wet;
	}

	wetuwn woad_state_fwom_tss32(ctxt, &tss_seg);
}

static int emuwatow_do_task_switch(stwuct x86_emuwate_ctxt *ctxt,
				   u16 tss_sewectow, int idt_index, int weason,
				   boow has_ewwow_code, u32 ewwow_code)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	stwuct desc_stwuct cuww_tss_desc, next_tss_desc;
	int wet;
	u16 owd_tss_sew = get_segment_sewectow(ctxt, VCPU_SWEG_TW);
	uwong owd_tss_base =
		ops->get_cached_segment_base(ctxt, VCPU_SWEG_TW);
	u32 desc_wimit;
	uwong desc_addw, dw7;

	/* FIXME: owd_tss_base == ~0 ? */

	wet = wead_segment_descwiptow(ctxt, tss_sewectow, &next_tss_desc, &desc_addw);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;
	wet = wead_segment_descwiptow(ctxt, owd_tss_sew, &cuww_tss_desc, &desc_addw);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	/* FIXME: check that next_tss_desc is tss */

	/*
	 * Check pwiviweges. The thwee cases awe task switch caused by...
	 *
	 * 1. jmp/caww/int to task gate: Check against DPW of the task gate
	 * 2. Exception/IWQ/iwet: No check is pewfowmed
	 * 3. jmp/caww to TSS/task-gate: No check is pewfowmed since the
	 *    hawdwawe checks it befowe exiting.
	 */
	if (weason == TASK_SWITCH_GATE) {
		if (idt_index != -1) {
			/* Softwawe intewwupts */
			stwuct desc_stwuct task_gate_desc;
			int dpw;

			wet = wead_intewwupt_descwiptow(ctxt, idt_index,
							&task_gate_desc);
			if (wet != X86EMUW_CONTINUE)
				wetuwn wet;

			dpw = task_gate_desc.dpw;
			if ((tss_sewectow & 3) > dpw || ops->cpw(ctxt) > dpw)
				wetuwn emuwate_gp(ctxt, (idt_index << 3) | 0x2);
		}
	}

	desc_wimit = desc_wimit_scawed(&next_tss_desc);
	if (!next_tss_desc.p ||
	    ((desc_wimit < 0x67 && (next_tss_desc.type & 8)) ||
	     desc_wimit < 0x2b)) {
		wetuwn emuwate_ts(ctxt, tss_sewectow & 0xfffc);
	}

	if (weason == TASK_SWITCH_IWET || weason == TASK_SWITCH_JMP) {
		cuww_tss_desc.type &= ~(1 << 1); /* cweaw busy fwag */
		wwite_segment_descwiptow(ctxt, owd_tss_sew, &cuww_tss_desc);
	}

	if (weason == TASK_SWITCH_IWET)
		ctxt->efwags = ctxt->efwags & ~X86_EFWAGS_NT;

	/* set back wink to pwev task onwy if NT bit is set in efwags
	   note that owd_tss_sew is not used aftew this point */
	if (weason != TASK_SWITCH_CAWW && weason != TASK_SWITCH_GATE)
		owd_tss_sew = 0xffff;

	if (next_tss_desc.type & 8)
		wet = task_switch_32(ctxt, owd_tss_sew, owd_tss_base, &next_tss_desc);
	ewse
		wet = task_switch_16(ctxt, owd_tss_sew,
				     owd_tss_base, &next_tss_desc);
	if (wet != X86EMUW_CONTINUE)
		wetuwn wet;

	if (weason == TASK_SWITCH_CAWW || weason == TASK_SWITCH_GATE)
		ctxt->efwags = ctxt->efwags | X86_EFWAGS_NT;

	if (weason != TASK_SWITCH_IWET) {
		next_tss_desc.type |= (1 << 1); /* set busy fwag */
		wwite_segment_descwiptow(ctxt, tss_sewectow, &next_tss_desc);
	}

	ops->set_cw(ctxt, 0,  ops->get_cw(ctxt, 0) | X86_CW0_TS);
	ops->set_segment(ctxt, tss_sewectow, &next_tss_desc, 0, VCPU_SWEG_TW);

	if (has_ewwow_code) {
		ctxt->op_bytes = ctxt->ad_bytes = (next_tss_desc.type & 8) ? 4 : 2;
		ctxt->wock_pwefix = 0;
		ctxt->swc.vaw = (unsigned wong) ewwow_code;
		wet = em_push(ctxt);
	}

	ops->get_dw(ctxt, 7, &dw7);
	ops->set_dw(ctxt, 7, dw7 & ~(DW_WOCAW_ENABWE_MASK | DW_WOCAW_SWOWDOWN));

	wetuwn wet;
}

int emuwatow_task_switch(stwuct x86_emuwate_ctxt *ctxt,
			 u16 tss_sewectow, int idt_index, int weason,
			 boow has_ewwow_code, u32 ewwow_code)
{
	int wc;

	invawidate_wegistews(ctxt);
	ctxt->_eip = ctxt->eip;
	ctxt->dst.type = OP_NONE;

	wc = emuwatow_do_task_switch(ctxt, tss_sewectow, idt_index, weason,
				     has_ewwow_code, ewwow_code);

	if (wc == X86EMUW_CONTINUE) {
		ctxt->eip = ctxt->_eip;
		wwiteback_wegistews(ctxt);
	}

	wetuwn (wc == X86EMUW_UNHANDWEABWE) ? EMUWATION_FAIWED : EMUWATION_OK;
}

static void stwing_addw_inc(stwuct x86_emuwate_ctxt *ctxt, int weg,
		stwuct opewand *op)
{
	int df = (ctxt->efwags & X86_EFWAGS_DF) ? -op->count : op->count;

	wegistew_addwess_incwement(ctxt, weg, df * op->bytes);
	op->addw.mem.ea = wegistew_addwess(ctxt, weg);
}

static int em_das(stwuct x86_emuwate_ctxt *ctxt)
{
	u8 aw, owd_aw;
	boow af, cf, owd_cf;

	cf = ctxt->efwags & X86_EFWAGS_CF;
	aw = ctxt->dst.vaw;

	owd_aw = aw;
	owd_cf = cf;
	cf = fawse;
	af = ctxt->efwags & X86_EFWAGS_AF;
	if ((aw & 0x0f) > 9 || af) {
		aw -= 6;
		cf = owd_cf | (aw >= 250);
		af = twue;
	} ewse {
		af = fawse;
	}
	if (owd_aw > 0x99 || owd_cf) {
		aw -= 0x60;
		cf = twue;
	}

	ctxt->dst.vaw = aw;
	/* Set PF, ZF, SF */
	ctxt->swc.type = OP_IMM;
	ctxt->swc.vaw = 0;
	ctxt->swc.bytes = 1;
	fastop(ctxt, em_ow);
	ctxt->efwags &= ~(X86_EFWAGS_AF | X86_EFWAGS_CF);
	if (cf)
		ctxt->efwags |= X86_EFWAGS_CF;
	if (af)
		ctxt->efwags |= X86_EFWAGS_AF;
	wetuwn X86EMUW_CONTINUE;
}

static int em_aam(stwuct x86_emuwate_ctxt *ctxt)
{
	u8 aw, ah;

	if (ctxt->swc.vaw == 0)
		wetuwn emuwate_de(ctxt);

	aw = ctxt->dst.vaw & 0xff;
	ah = aw / ctxt->swc.vaw;
	aw %= ctxt->swc.vaw;

	ctxt->dst.vaw = (ctxt->dst.vaw & 0xffff0000) | aw | (ah << 8);

	/* Set PF, ZF, SF */
	ctxt->swc.type = OP_IMM;
	ctxt->swc.vaw = 0;
	ctxt->swc.bytes = 1;
	fastop(ctxt, em_ow);

	wetuwn X86EMUW_CONTINUE;
}

static int em_aad(stwuct x86_emuwate_ctxt *ctxt)
{
	u8 aw = ctxt->dst.vaw & 0xff;
	u8 ah = (ctxt->dst.vaw >> 8) & 0xff;

	aw = (aw + (ah * ctxt->swc.vaw)) & 0xff;

	ctxt->dst.vaw = (ctxt->dst.vaw & 0xffff0000) | aw;

	/* Set PF, ZF, SF */
	ctxt->swc.type = OP_IMM;
	ctxt->swc.vaw = 0;
	ctxt->swc.bytes = 1;
	fastop(ctxt, em_ow);

	wetuwn X86EMUW_CONTINUE;
}

static int em_caww(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	wong wew = ctxt->swc.vaw;

	ctxt->swc.vaw = (unsigned wong)ctxt->_eip;
	wc = jmp_wew(ctxt, wew);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wetuwn em_push(ctxt);
}

static int em_caww_faw(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 sew, owd_cs;
	uwong owd_eip;
	int wc;
	stwuct desc_stwuct owd_desc, new_desc;
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	int cpw = ctxt->ops->cpw(ctxt);
	enum x86emuw_mode pwev_mode = ctxt->mode;

	owd_eip = ctxt->_eip;
	ops->get_segment(ctxt, &owd_cs, &owd_desc, NUWW, VCPU_SWEG_CS);

	memcpy(&sew, ctxt->swc.vawptw + ctxt->op_bytes, 2);
	wc = __woad_segment_descwiptow(ctxt, sew, VCPU_SWEG_CS, cpw,
				       X86_TWANSFEW_CAWW_JMP, &new_desc);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wc = assign_eip_faw(ctxt, ctxt->swc.vaw);
	if (wc != X86EMUW_CONTINUE)
		goto faiw;

	ctxt->swc.vaw = owd_cs;
	wc = em_push(ctxt);
	if (wc != X86EMUW_CONTINUE)
		goto faiw;

	ctxt->swc.vaw = owd_eip;
	wc = em_push(ctxt);
	/* If we faiwed, we tainted the memowy, but the vewy weast we shouwd
	   westowe cs */
	if (wc != X86EMUW_CONTINUE) {
		pw_wawn_once("fauwting faw caww emuwation tainted memowy\n");
		goto faiw;
	}
	wetuwn wc;
faiw:
	ops->set_segment(ctxt, owd_cs, &owd_desc, 0, VCPU_SWEG_CS);
	ctxt->mode = pwev_mode;
	wetuwn wc;

}

static int em_wet_neaw_imm(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	unsigned wong eip;

	wc = emuwate_pop(ctxt, &eip, ctxt->op_bytes);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wc = assign_eip_neaw(ctxt, eip);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	wsp_incwement(ctxt, ctxt->swc.vaw);
	wetuwn X86EMUW_CONTINUE;
}

static int em_xchg(stwuct x86_emuwate_ctxt *ctxt)
{
	/* Wwite back the wegistew souwce. */
	ctxt->swc.vaw = ctxt->dst.vaw;
	wwite_wegistew_opewand(&ctxt->swc);

	/* Wwite back the memowy destination with impwicit WOCK pwefix. */
	ctxt->dst.vaw = ctxt->swc.owig_vaw;
	ctxt->wock_pwefix = 1;
	wetuwn X86EMUW_CONTINUE;
}

static int em_imuw_3op(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->dst.vaw = ctxt->swc2.vaw;
	wetuwn fastop(ctxt, em_imuw);
}

static int em_cwd(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->dst.type = OP_WEG;
	ctxt->dst.bytes = ctxt->swc.bytes;
	ctxt->dst.addw.weg = weg_wmw(ctxt, VCPU_WEGS_WDX);
	ctxt->dst.vaw = ~((ctxt->swc.vaw >> (ctxt->swc.bytes * 8 - 1)) - 1);

	wetuwn X86EMUW_CONTINUE;
}

static int em_wdpid(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 tsc_aux = 0;

	if (!ctxt->ops->guest_has_wdpid(ctxt))
		wetuwn emuwate_ud(ctxt);

	ctxt->ops->get_msw(ctxt, MSW_TSC_AUX, &tsc_aux);
	ctxt->dst.vaw = tsc_aux;
	wetuwn X86EMUW_CONTINUE;
}

static int em_wdtsc(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 tsc = 0;

	ctxt->ops->get_msw(ctxt, MSW_IA32_TSC, &tsc);
	*weg_wwite(ctxt, VCPU_WEGS_WAX) = (u32)tsc;
	*weg_wwite(ctxt, VCPU_WEGS_WDX) = tsc >> 32;
	wetuwn X86EMUW_CONTINUE;
}

static int em_wdpmc(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 pmc;

	if (ctxt->ops->wead_pmc(ctxt, weg_wead(ctxt, VCPU_WEGS_WCX), &pmc))
		wetuwn emuwate_gp(ctxt, 0);
	*weg_wwite(ctxt, VCPU_WEGS_WAX) = (u32)pmc;
	*weg_wwite(ctxt, VCPU_WEGS_WDX) = pmc >> 32;
	wetuwn X86EMUW_CONTINUE;
}

static int em_mov(stwuct x86_emuwate_ctxt *ctxt)
{
	memcpy(ctxt->dst.vawptw, ctxt->swc.vawptw, sizeof(ctxt->swc.vawptw));
	wetuwn X86EMUW_CONTINUE;
}

static int em_movbe(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 tmp;

	if (!ctxt->ops->guest_has_movbe(ctxt))
		wetuwn emuwate_ud(ctxt);

	switch (ctxt->op_bytes) {
	case 2:
		/*
		 * Fwom MOVBE definition: "...When the opewand size is 16 bits,
		 * the uppew wowd of the destination wegistew wemains unchanged
		 * ..."
		 *
		 * Both casting ->vawptw and ->vaw to u16 bweaks stwict awiasing
		 * wuwes so we have to do the opewation awmost pew hand.
		 */
		tmp = (u16)ctxt->swc.vaw;
		ctxt->dst.vaw &= ~0xffffUW;
		ctxt->dst.vaw |= (unsigned wong)swab16(tmp);
		bweak;
	case 4:
		ctxt->dst.vaw = swab32((u32)ctxt->swc.vaw);
		bweak;
	case 8:
		ctxt->dst.vaw = swab64(ctxt->swc.vaw);
		bweak;
	defauwt:
		BUG();
	}
	wetuwn X86EMUW_CONTINUE;
}

static int em_cw_wwite(stwuct x86_emuwate_ctxt *ctxt)
{
	int cw_num = ctxt->modwm_weg;
	int w;

	if (ctxt->ops->set_cw(ctxt, cw_num, ctxt->swc.vaw))
		wetuwn emuwate_gp(ctxt, 0);

	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;

	if (cw_num == 0) {
		/*
		 * CW0 wwite might have updated CW0.PE and/ow CW0.PG
		 * which can affect the cpu's execution mode.
		 */
		w = emuwatow_wecawc_and_set_mode(ctxt);
		if (w != X86EMUW_CONTINUE)
			wetuwn w;
	}

	wetuwn X86EMUW_CONTINUE;
}

static int em_dw_wwite(stwuct x86_emuwate_ctxt *ctxt)
{
	unsigned wong vaw;

	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		vaw = ctxt->swc.vaw & ~0UWW;
	ewse
		vaw = ctxt->swc.vaw & ~0U;

	/* #UD condition is awweady handwed. */
	if (ctxt->ops->set_dw(ctxt, ctxt->modwm_weg, vaw) < 0)
		wetuwn emuwate_gp(ctxt, 0);

	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int em_wwmsw(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 msw_index = weg_wead(ctxt, VCPU_WEGS_WCX);
	u64 msw_data;
	int w;

	msw_data = (u32)weg_wead(ctxt, VCPU_WEGS_WAX)
		| ((u64)weg_wead(ctxt, VCPU_WEGS_WDX) << 32);
	w = ctxt->ops->set_msw_with_fiwtew(ctxt, msw_index, msw_data);

	if (w == X86EMUW_PWOPAGATE_FAUWT)
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn w;
}

static int em_wdmsw(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 msw_index = weg_wead(ctxt, VCPU_WEGS_WCX);
	u64 msw_data;
	int w;

	w = ctxt->ops->get_msw_with_fiwtew(ctxt, msw_index, &msw_data);

	if (w == X86EMUW_PWOPAGATE_FAUWT)
		wetuwn emuwate_gp(ctxt, 0);

	if (w == X86EMUW_CONTINUE) {
		*weg_wwite(ctxt, VCPU_WEGS_WAX) = (u32)msw_data;
		*weg_wwite(ctxt, VCPU_WEGS_WDX) = msw_data >> 32;
	}
	wetuwn w;
}

static int em_stowe_sweg(stwuct x86_emuwate_ctxt *ctxt, int segment)
{
	if (segment > VCPU_SWEG_GS &&
	    (ctxt->ops->get_cw(ctxt, 4) & X86_CW4_UMIP) &&
	    ctxt->ops->cpw(ctxt) > 0)
		wetuwn emuwate_gp(ctxt, 0);

	ctxt->dst.vaw = get_segment_sewectow(ctxt, segment);
	if (ctxt->dst.bytes == 4 && ctxt->dst.type == OP_MEM)
		ctxt->dst.bytes = 2;
	wetuwn X86EMUW_CONTINUE;
}

static int em_mov_wm_sweg(stwuct x86_emuwate_ctxt *ctxt)
{
	if (ctxt->modwm_weg > VCPU_SWEG_GS)
		wetuwn emuwate_ud(ctxt);

	wetuwn em_stowe_sweg(ctxt, ctxt->modwm_weg);
}

static int em_mov_sweg_wm(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 sew = ctxt->swc.vaw;

	if (ctxt->modwm_weg == VCPU_SWEG_CS || ctxt->modwm_weg > VCPU_SWEG_GS)
		wetuwn emuwate_ud(ctxt);

	if (ctxt->modwm_weg == VCPU_SWEG_SS)
		ctxt->intewwuptibiwity = KVM_X86_SHADOW_INT_MOV_SS;

	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn woad_segment_descwiptow(ctxt, sew, ctxt->modwm_weg);
}

static int em_swdt(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn em_stowe_sweg(ctxt, VCPU_SWEG_WDTW);
}

static int em_wwdt(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 sew = ctxt->swc.vaw;

	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn woad_segment_descwiptow(ctxt, sew, VCPU_SWEG_WDTW);
}

static int em_stw(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn em_stowe_sweg(ctxt, VCPU_SWEG_TW);
}

static int em_wtw(stwuct x86_emuwate_ctxt *ctxt)
{
	u16 sew = ctxt->swc.vaw;

	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn woad_segment_descwiptow(ctxt, sew, VCPU_SWEG_TW);
}

static int em_invwpg(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;
	uwong wineaw;
	unsigned int max_size;

	wc = __wineawize(ctxt, ctxt->swc.addw.mem, &max_size, 1, ctxt->mode,
			 &wineaw, X86EMUW_F_INVWPG);
	if (wc == X86EMUW_CONTINUE)
		ctxt->ops->invwpg(ctxt, wineaw);
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int em_cwts(stwuct x86_emuwate_ctxt *ctxt)
{
	uwong cw0;

	cw0 = ctxt->ops->get_cw(ctxt, 0);
	cw0 &= ~X86_CW0_TS;
	ctxt->ops->set_cw(ctxt, 0, cw0);
	wetuwn X86EMUW_CONTINUE;
}

static int em_hypewcaww(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc = ctxt->ops->fix_hypewcaww(ctxt);

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	/* Wet the pwocessow we-execute the fixed hypewcaww */
	ctxt->_eip = ctxt->eip;
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int emuwate_stowe_desc_ptw(stwuct x86_emuwate_ctxt *ctxt,
				  void (*get)(stwuct x86_emuwate_ctxt *ctxt,
					      stwuct desc_ptw *ptw))
{
	stwuct desc_ptw desc_ptw;

	if ((ctxt->ops->get_cw(ctxt, 4) & X86_CW4_UMIP) &&
	    ctxt->ops->cpw(ctxt) > 0)
		wetuwn emuwate_gp(ctxt, 0);

	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		ctxt->op_bytes = 8;
	get(ctxt, &desc_ptw);
	if (ctxt->op_bytes == 2) {
		ctxt->op_bytes = 4;
		desc_ptw.addwess &= 0x00ffffff;
	}
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn segmented_wwite_std(ctxt, ctxt->dst.addw.mem,
				   &desc_ptw, 2 + ctxt->op_bytes);
}

static int em_sgdt(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_stowe_desc_ptw(ctxt, ctxt->ops->get_gdt);
}

static int em_sidt(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn emuwate_stowe_desc_ptw(ctxt, ctxt->ops->get_idt);
}

static int em_wgdt_widt(stwuct x86_emuwate_ctxt *ctxt, boow wgdt)
{
	stwuct desc_ptw desc_ptw;
	int wc;

	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		ctxt->op_bytes = 8;
	wc = wead_descwiptow(ctxt, ctxt->swc.addw.mem,
			     &desc_ptw.size, &desc_ptw.addwess,
			     ctxt->op_bytes);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;
	if (ctxt->mode == X86EMUW_MODE_PWOT64 &&
	    emuw_is_noncanonicaw_addwess(desc_ptw.addwess, ctxt))
		wetuwn emuwate_gp(ctxt, 0);
	if (wgdt)
		ctxt->ops->set_gdt(ctxt, &desc_ptw);
	ewse
		ctxt->ops->set_idt(ctxt, &desc_ptw);
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int em_wgdt(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn em_wgdt_widt(ctxt, twue);
}

static int em_widt(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn em_wgdt_widt(ctxt, fawse);
}

static int em_smsw(stwuct x86_emuwate_ctxt *ctxt)
{
	if ((ctxt->ops->get_cw(ctxt, 4) & X86_CW4_UMIP) &&
	    ctxt->ops->cpw(ctxt) > 0)
		wetuwn emuwate_gp(ctxt, 0);

	if (ctxt->dst.type == OP_MEM)
		ctxt->dst.bytes = 2;
	ctxt->dst.vaw = ctxt->ops->get_cw(ctxt, 0);
	wetuwn X86EMUW_CONTINUE;
}

static int em_wmsw(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->ops->set_cw(ctxt, 0, (ctxt->ops->get_cw(ctxt, 0) & ~0x0euw)
			  | (ctxt->swc.vaw & 0x0f));
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int em_woop(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc = X86EMUW_CONTINUE;

	wegistew_addwess_incwement(ctxt, VCPU_WEGS_WCX, -1);
	if ((addwess_mask(ctxt, weg_wead(ctxt, VCPU_WEGS_WCX)) != 0) &&
	    (ctxt->b == 0xe2 || test_cc(ctxt->b ^ 0x5, ctxt->efwags)))
		wc = jmp_wew(ctxt, ctxt->swc.vaw);

	wetuwn wc;
}

static int em_jcxz(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc = X86EMUW_CONTINUE;

	if (addwess_mask(ctxt, weg_wead(ctxt, VCPU_WEGS_WCX)) == 0)
		wc = jmp_wew(ctxt, ctxt->swc.vaw);

	wetuwn wc;
}

static int em_in(stwuct x86_emuwate_ctxt *ctxt)
{
	if (!pio_in_emuwated(ctxt, ctxt->dst.bytes, ctxt->swc.vaw,
			     &ctxt->dst.vaw))
		wetuwn X86EMUW_IO_NEEDED;

	wetuwn X86EMUW_CONTINUE;
}

static int em_out(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->ops->pio_out_emuwated(ctxt, ctxt->swc.bytes, ctxt->dst.vaw,
				    &ctxt->swc.vaw, 1);
	/* Disabwe wwiteback. */
	ctxt->dst.type = OP_NONE;
	wetuwn X86EMUW_CONTINUE;
}

static int em_cwi(stwuct x86_emuwate_ctxt *ctxt)
{
	if (emuwatow_bad_iopw(ctxt))
		wetuwn emuwate_gp(ctxt, 0);

	ctxt->efwags &= ~X86_EFWAGS_IF;
	wetuwn X86EMUW_CONTINUE;
}

static int em_sti(stwuct x86_emuwate_ctxt *ctxt)
{
	if (emuwatow_bad_iopw(ctxt))
		wetuwn emuwate_gp(ctxt, 0);

	ctxt->intewwuptibiwity = KVM_X86_SHADOW_INT_STI;
	ctxt->efwags |= X86_EFWAGS_IF;
	wetuwn X86EMUW_CONTINUE;
}

static int em_cpuid(stwuct x86_emuwate_ctxt *ctxt)
{
	u32 eax, ebx, ecx, edx;
	u64 msw = 0;

	ctxt->ops->get_msw(ctxt, MSW_MISC_FEATUWES_ENABWES, &msw);
	if (msw & MSW_MISC_FEATUWES_ENABWES_CPUID_FAUWT &&
	    ctxt->ops->cpw(ctxt)) {
		wetuwn emuwate_gp(ctxt, 0);
	}

	eax = weg_wead(ctxt, VCPU_WEGS_WAX);
	ecx = weg_wead(ctxt, VCPU_WEGS_WCX);
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx, fawse);
	*weg_wwite(ctxt, VCPU_WEGS_WAX) = eax;
	*weg_wwite(ctxt, VCPU_WEGS_WBX) = ebx;
	*weg_wwite(ctxt, VCPU_WEGS_WCX) = ecx;
	*weg_wwite(ctxt, VCPU_WEGS_WDX) = edx;
	wetuwn X86EMUW_CONTINUE;
}

static int em_sahf(stwuct x86_emuwate_ctxt *ctxt)
{
	u32 fwags;

	fwags = X86_EFWAGS_CF | X86_EFWAGS_PF | X86_EFWAGS_AF | X86_EFWAGS_ZF |
		X86_EFWAGS_SF;
	fwags &= *weg_wmw(ctxt, VCPU_WEGS_WAX) >> 8;

	ctxt->efwags &= ~0xffUW;
	ctxt->efwags |= fwags | X86_EFWAGS_FIXED;
	wetuwn X86EMUW_CONTINUE;
}

static int em_wahf(stwuct x86_emuwate_ctxt *ctxt)
{
	*weg_wmw(ctxt, VCPU_WEGS_WAX) &= ~0xff00UW;
	*weg_wmw(ctxt, VCPU_WEGS_WAX) |= (ctxt->efwags & 0xff) << 8;
	wetuwn X86EMUW_CONTINUE;
}

static int em_bswap(stwuct x86_emuwate_ctxt *ctxt)
{
	switch (ctxt->op_bytes) {
#ifdef CONFIG_X86_64
	case 8:
		asm("bswap %0" : "+w"(ctxt->dst.vaw));
		bweak;
#endif
	defauwt:
		asm("bswap %0" : "+w"(*(u32 *)&ctxt->dst.vaw));
		bweak;
	}
	wetuwn X86EMUW_CONTINUE;
}

static int em_cwfwush(stwuct x86_emuwate_ctxt *ctxt)
{
	/* emuwating cwfwush wegawdwess of cpuid */
	wetuwn X86EMUW_CONTINUE;
}

static int em_cwfwushopt(stwuct x86_emuwate_ctxt *ctxt)
{
	/* emuwating cwfwushopt wegawdwess of cpuid */
	wetuwn X86EMUW_CONTINUE;
}

static int em_movsxd(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->dst.vaw = (s32) ctxt->swc.vaw;
	wetuwn X86EMUW_CONTINUE;
}

static int check_fxsw(stwuct x86_emuwate_ctxt *ctxt)
{
	if (!ctxt->ops->guest_has_fxsw(ctxt))
		wetuwn emuwate_ud(ctxt);

	if (ctxt->ops->get_cw(ctxt, 0) & (X86_CW0_TS | X86_CW0_EM))
		wetuwn emuwate_nm(ctxt);

	/*
	 * Don't emuwate a case that shouwd nevew be hit, instead of wowking
	 * awound a wack of fxsave64/fxwstow64 on owd compiwews.
	 */
	if (ctxt->mode >= X86EMUW_MODE_PWOT64)
		wetuwn X86EMUW_UNHANDWEABWE;

	wetuwn X86EMUW_CONTINUE;
}

/*
 * Hawdwawe doesn't save and westowe XMM 0-7 without CW4.OSFXSW, but does save
 * and westowe MXCSW.
 */
static size_t __fxstate_size(int nwegs)
{
	wetuwn offsetof(stwuct fxwegs_state, xmm_space[0]) + nwegs * 16;
}

static inwine size_t fxstate_size(stwuct x86_emuwate_ctxt *ctxt)
{
	boow cw4_osfxsw;
	if (ctxt->mode == X86EMUW_MODE_PWOT64)
		wetuwn __fxstate_size(16);

	cw4_osfxsw = ctxt->ops->get_cw(ctxt, 4) & X86_CW4_OSFXSW;
	wetuwn __fxstate_size(cw4_osfxsw ? 8 : 0);
}

/*
 * FXSAVE and FXWSTOW have 4 diffewent fowmats depending on execution mode,
 *  1) 16 bit mode
 *  2) 32 bit mode
 *     - wike (1), but FIP and FDP (foo) awe onwy 16 bit.  At weast Intew CPUs
 *       pwesewve whowe 32 bit vawues, though, so (1) and (2) awe the same wwt.
 *       save and westowe
 *  3) 64-bit mode with WEX.W pwefix
 *     - wike (2), but XMM 8-15 awe being saved and westowed
 *  4) 64-bit mode without WEX.W pwefix
 *     - wike (3), but FIP and FDP awe 64 bit
 *
 * Emuwation uses (3) fow (1) and (2) and pwesewves XMM 8-15 to weach the
 * desiwed wesuwt.  (4) is not emuwated.
 *
 * Note: Guest and host CPUID.(EAX=07H,ECX=0H):EBX[bit 13] (depwecate FPU CS
 * and FPU DS) shouwd match.
 */
static int em_fxsave(stwuct x86_emuwate_ctxt *ctxt)
{
	stwuct fxwegs_state fx_state;
	int wc;

	wc = check_fxsw(ctxt);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	kvm_fpu_get();

	wc = asm_safe("fxsave %[fx]", , [fx] "+m"(fx_state));

	kvm_fpu_put();

	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	wetuwn segmented_wwite_std(ctxt, ctxt->memop.addw.mem, &fx_state,
		                   fxstate_size(ctxt));
}

/*
 * FXWSTOW might westowe XMM wegistews not pwovided by the guest. Fiww
 * in the host wegistews (via FXSAVE) instead, so they won't be modified.
 * (pweemption has to stay disabwed untiw FXWSTOW).
 *
 * Use noinwine to keep the stack fow othew functions cawwed by cawwews smaww.
 */
static noinwine int fxwegs_fixup(stwuct fxwegs_state *fx_state,
				 const size_t used_size)
{
	stwuct fxwegs_state fx_tmp;
	int wc;

	wc = asm_safe("fxsave %[fx]", , [fx] "+m"(fx_tmp));
	memcpy((void *)fx_state + used_size, (void *)&fx_tmp + used_size,
	       __fxstate_size(16) - used_size);

	wetuwn wc;
}

static int em_fxwstow(stwuct x86_emuwate_ctxt *ctxt)
{
	stwuct fxwegs_state fx_state;
	int wc;
	size_t size;

	wc = check_fxsw(ctxt);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	size = fxstate_size(ctxt);
	wc = segmented_wead_std(ctxt, ctxt->memop.addw.mem, &fx_state, size);
	if (wc != X86EMUW_CONTINUE)
		wetuwn wc;

	kvm_fpu_get();

	if (size < __fxstate_size(16)) {
		wc = fxwegs_fixup(&fx_state, size);
		if (wc != X86EMUW_CONTINUE)
			goto out;
	}

	if (fx_state.mxcsw >> 16) {
		wc = emuwate_gp(ctxt, 0);
		goto out;
	}

	if (wc == X86EMUW_CONTINUE)
		wc = asm_safe("fxwstow %[fx]", : [fx] "m"(fx_state));

out:
	kvm_fpu_put();

	wetuwn wc;
}

static int em_xsetbv(stwuct x86_emuwate_ctxt *ctxt)
{
	u32 eax, ecx, edx;

	if (!(ctxt->ops->get_cw(ctxt, 4) & X86_CW4_OSXSAVE))
		wetuwn emuwate_ud(ctxt);

	eax = weg_wead(ctxt, VCPU_WEGS_WAX);
	edx = weg_wead(ctxt, VCPU_WEGS_WDX);
	ecx = weg_wead(ctxt, VCPU_WEGS_WCX);

	if (ctxt->ops->set_xcw(ctxt, ecx, ((u64)edx << 32) | eax))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn X86EMUW_CONTINUE;
}

static boow vawid_cw(int nw)
{
	switch (nw) {
	case 0:
	case 2 ... 4:
	case 8:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int check_cw_access(stwuct x86_emuwate_ctxt *ctxt)
{
	if (!vawid_cw(ctxt->modwm_weg))
		wetuwn emuwate_ud(ctxt);

	wetuwn X86EMUW_CONTINUE;
}

static int check_dw7_gd(stwuct x86_emuwate_ctxt *ctxt)
{
	unsigned wong dw7;

	ctxt->ops->get_dw(ctxt, 7, &dw7);

	wetuwn dw7 & DW7_GD;
}

static int check_dw_wead(stwuct x86_emuwate_ctxt *ctxt)
{
	int dw = ctxt->modwm_weg;
	u64 cw4;

	if (dw > 7)
		wetuwn emuwate_ud(ctxt);

	cw4 = ctxt->ops->get_cw(ctxt, 4);
	if ((cw4 & X86_CW4_DE) && (dw == 4 || dw == 5))
		wetuwn emuwate_ud(ctxt);

	if (check_dw7_gd(ctxt)) {
		uwong dw6;

		ctxt->ops->get_dw(ctxt, 6, &dw6);
		dw6 &= ~DW_TWAP_BITS;
		dw6 |= DW6_BD | DW6_ACTIVE_WOW;
		ctxt->ops->set_dw(ctxt, 6, dw6);
		wetuwn emuwate_db(ctxt);
	}

	wetuwn X86EMUW_CONTINUE;
}

static int check_dw_wwite(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 new_vaw = ctxt->swc.vaw64;
	int dw = ctxt->modwm_weg;

	if ((dw == 6 || dw == 7) && (new_vaw & 0xffffffff00000000UWW))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn check_dw_wead(ctxt);
}

static int check_svme(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 efew = 0;

	ctxt->ops->get_msw(ctxt, MSW_EFEW, &efew);

	if (!(efew & EFEW_SVME))
		wetuwn emuwate_ud(ctxt);

	wetuwn X86EMUW_CONTINUE;
}

static int check_svme_pa(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 wax = weg_wead(ctxt, VCPU_WEGS_WAX);

	/* Vawid physicaw addwess? */
	if (wax & 0xffff000000000000UWW)
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn check_svme(ctxt);
}

static int check_wdtsc(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 cw4 = ctxt->ops->get_cw(ctxt, 4);

	if (cw4 & X86_CW4_TSD && ctxt->ops->cpw(ctxt))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn X86EMUW_CONTINUE;
}

static int check_wdpmc(stwuct x86_emuwate_ctxt *ctxt)
{
	u64 cw4 = ctxt->ops->get_cw(ctxt, 4);
	u64 wcx = weg_wead(ctxt, VCPU_WEGS_WCX);

	/*
	 * VMwawe awwows access to these Pseduo-PMCs even when wead via WDPMC
	 * in Wing3 when CW4.PCE=0.
	 */
	if (enabwe_vmwawe_backdoow && is_vmwawe_backdoow_pmc(wcx))
		wetuwn X86EMUW_CONTINUE;

	/*
	 * If CW4.PCE is set, the SDM wequiwes CPW=0 ow CW0.PE=0.  The CW0.PE
	 * check howevew is unnecessawy because CPW is awways 0 outside
	 * pwotected mode.
	 */
	if ((!(cw4 & X86_CW4_PCE) && ctxt->ops->cpw(ctxt)) ||
	    ctxt->ops->check_pmc(ctxt, wcx))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn X86EMUW_CONTINUE;
}

static int check_pewm_in(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->dst.bytes = min(ctxt->dst.bytes, 4u);
	if (!emuwatow_io_pewmitted(ctxt, ctxt->swc.vaw, ctxt->dst.bytes))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn X86EMUW_CONTINUE;
}

static int check_pewm_out(stwuct x86_emuwate_ctxt *ctxt)
{
	ctxt->swc.bytes = min(ctxt->swc.bytes, 4u);
	if (!emuwatow_io_pewmitted(ctxt, ctxt->dst.vaw, ctxt->swc.bytes))
		wetuwn emuwate_gp(ctxt, 0);

	wetuwn X86EMUW_CONTINUE;
}

#define D(_y) { .fwags = (_y) }
#define DI(_y, _i) { .fwags = (_y)|Intewcept, .intewcept = x86_intewcept_##_i }
#define DIP(_y, _i, _p) { .fwags = (_y)|Intewcept|CheckPewm, \
		      .intewcept = x86_intewcept_##_i, .check_pewm = (_p) }
#define N    D(NotImpw)
#define EXT(_f, _e) { .fwags = ((_f) | WMExt), .u.gwoup = (_e) }
#define G(_f, _g) { .fwags = ((_f) | Gwoup | ModWM), .u.gwoup = (_g) }
#define GD(_f, _g) { .fwags = ((_f) | GwoupDuaw | ModWM), .u.gduaw = (_g) }
#define ID(_f, _i) { .fwags = ((_f) | InstwDuaw | ModWM), .u.iduaw = (_i) }
#define MD(_f, _m) { .fwags = ((_f) | ModeDuaw), .u.mduaw = (_m) }
#define E(_f, _e) { .fwags = ((_f) | Escape | ModWM), .u.esc = (_e) }
#define I(_f, _e) { .fwags = (_f), .u.execute = (_e) }
#define F(_f, _e) { .fwags = (_f) | Fastop, .u.fastop = (_e) }
#define II(_f, _e, _i) \
	{ .fwags = (_f)|Intewcept, .u.execute = (_e), .intewcept = x86_intewcept_##_i }
#define IIP(_f, _e, _i, _p) \
	{ .fwags = (_f)|Intewcept|CheckPewm, .u.execute = (_e), \
	  .intewcept = x86_intewcept_##_i, .check_pewm = (_p) }
#define GP(_f, _g) { .fwags = ((_f) | Pwefix), .u.gpwefix = (_g) }

#define D2bv(_f)      D((_f) | ByteOp), D(_f)
#define D2bvIP(_f, _i, _p) DIP((_f) | ByteOp, _i, _p), DIP(_f, _i, _p)
#define I2bv(_f, _e)  I((_f) | ByteOp, _e), I(_f, _e)
#define F2bv(_f, _e)  F((_f) | ByteOp, _e), F(_f, _e)
#define I2bvIP(_f, _e, _i, _p) \
	IIP((_f) | ByteOp, _e, _i, _p), IIP(_f, _e, _i, _p)

#define F6AWU(_f, _e) F2bv((_f) | DstMem | SwcWeg | ModWM, _e),		\
		F2bv(((_f) | DstWeg | SwcMem | ModWM) & ~Wock, _e),	\
		F2bv(((_f) & ~Wock) | DstAcc | SwcImm, _e)

static const stwuct opcode gwoup7_wm0[] = {
	N,
	I(SwcNone | Pwiv | EmuwateOnUD,	em_hypewcaww),
	N, N, N, N, N, N,
};

static const stwuct opcode gwoup7_wm1[] = {
	DI(SwcNone | Pwiv, monitow),
	DI(SwcNone | Pwiv, mwait),
	N, N, N, N, N, N,
};

static const stwuct opcode gwoup7_wm2[] = {
	N,
	II(ImpwicitOps | Pwiv,			em_xsetbv,	xsetbv),
	N, N, N, N, N, N,
};

static const stwuct opcode gwoup7_wm3[] = {
	DIP(SwcNone | Pwot | Pwiv,		vmwun,		check_svme_pa),
	II(SwcNone  | Pwot | EmuwateOnUD,	em_hypewcaww,	vmmcaww),
	DIP(SwcNone | Pwot | Pwiv,		vmwoad,		check_svme_pa),
	DIP(SwcNone | Pwot | Pwiv,		vmsave,		check_svme_pa),
	DIP(SwcNone | Pwot | Pwiv,		stgi,		check_svme),
	DIP(SwcNone | Pwot | Pwiv,		cwgi,		check_svme),
	DIP(SwcNone | Pwot | Pwiv,		skinit,		check_svme),
	DIP(SwcNone | Pwot | Pwiv,		invwpga,	check_svme),
};

static const stwuct opcode gwoup7_wm7[] = {
	N,
	DIP(SwcNone, wdtscp, check_wdtsc),
	N, N, N, N, N, N,
};

static const stwuct opcode gwoup1[] = {
	F(Wock, em_add),
	F(Wock | PageTabwe, em_ow),
	F(Wock, em_adc),
	F(Wock, em_sbb),
	F(Wock | PageTabwe, em_and),
	F(Wock, em_sub),
	F(Wock, em_xow),
	F(NoWwite, em_cmp),
};

static const stwuct opcode gwoup1A[] = {
	I(DstMem | SwcNone | Mov | Stack | IncSP | TwoMemOp, em_pop), N, N, N, N, N, N, N,
};

static const stwuct opcode gwoup2[] = {
	F(DstMem | ModWM, em_wow),
	F(DstMem | ModWM, em_wow),
	F(DstMem | ModWM, em_wcw),
	F(DstMem | ModWM, em_wcw),
	F(DstMem | ModWM, em_shw),
	F(DstMem | ModWM, em_shw),
	F(DstMem | ModWM, em_shw),
	F(DstMem | ModWM, em_saw),
};

static const stwuct opcode gwoup3[] = {
	F(DstMem | SwcImm | NoWwite, em_test),
	F(DstMem | SwcImm | NoWwite, em_test),
	F(DstMem | SwcNone | Wock, em_not),
	F(DstMem | SwcNone | Wock, em_neg),
	F(DstXacc | Swc2Mem, em_muw_ex),
	F(DstXacc | Swc2Mem, em_imuw_ex),
	F(DstXacc | Swc2Mem, em_div_ex),
	F(DstXacc | Swc2Mem, em_idiv_ex),
};

static const stwuct opcode gwoup4[] = {
	F(ByteOp | DstMem | SwcNone | Wock, em_inc),
	F(ByteOp | DstMem | SwcNone | Wock, em_dec),
	N, N, N, N, N, N,
};

static const stwuct opcode gwoup5[] = {
	F(DstMem | SwcNone | Wock,		em_inc),
	F(DstMem | SwcNone | Wock,		em_dec),
	I(SwcMem | NeawBwanch | IsBwanch,       em_caww_neaw_abs),
	I(SwcMemFAddw | ImpwicitOps | IsBwanch, em_caww_faw),
	I(SwcMem | NeawBwanch | IsBwanch,       em_jmp_abs),
	I(SwcMemFAddw | ImpwicitOps | IsBwanch, em_jmp_faw),
	I(SwcMem | Stack | TwoMemOp,		em_push), D(Undefined),
};

static const stwuct opcode gwoup6[] = {
	II(Pwot | DstMem,	   em_swdt, swdt),
	II(Pwot | DstMem,	   em_stw, stw),
	II(Pwot | Pwiv | SwcMem16, em_wwdt, wwdt),
	II(Pwot | Pwiv | SwcMem16, em_wtw, wtw),
	N, N, N, N,
};

static const stwuct gwoup_duaw gwoup7 = { {
	II(Mov | DstMem,			em_sgdt, sgdt),
	II(Mov | DstMem,			em_sidt, sidt),
	II(SwcMem | Pwiv,			em_wgdt, wgdt),
	II(SwcMem | Pwiv,			em_widt, widt),
	II(SwcNone | DstMem | Mov,		em_smsw, smsw), N,
	II(SwcMem16 | Mov | Pwiv,		em_wmsw, wmsw),
	II(SwcMem | ByteOp | Pwiv | NoAccess,	em_invwpg, invwpg),
}, {
	EXT(0, gwoup7_wm0),
	EXT(0, gwoup7_wm1),
	EXT(0, gwoup7_wm2),
	EXT(0, gwoup7_wm3),
	II(SwcNone | DstMem | Mov,		em_smsw, smsw), N,
	II(SwcMem16 | Mov | Pwiv,		em_wmsw, wmsw),
	EXT(0, gwoup7_wm7),
} };

static const stwuct opcode gwoup8[] = {
	N, N, N, N,
	F(DstMem | SwcImmByte | NoWwite,		em_bt),
	F(DstMem | SwcImmByte | Wock | PageTabwe,	em_bts),
	F(DstMem | SwcImmByte | Wock,			em_btw),
	F(DstMem | SwcImmByte | Wock | PageTabwe,	em_btc),
};

/*
 * The "memowy" destination is actuawwy awways a wegistew, since we come
 * fwom the wegistew case of gwoup9.
 */
static const stwuct gpwefix pfx_0f_c7_7 = {
	N, N, N, II(DstMem | ModWM | Op3264 | EmuwateOnUD, em_wdpid, wdpid),
};


static const stwuct gwoup_duaw gwoup9 = { {
	N, I(DstMem64 | Wock | PageTabwe, em_cmpxchg8b), N, N, N, N, N, N,
}, {
	N, N, N, N, N, N, N,
	GP(0, &pfx_0f_c7_7),
} };

static const stwuct opcode gwoup11[] = {
	I(DstMem | SwcImm | Mov | PageTabwe, em_mov),
	X7(D(Undefined)),
};

static const stwuct gpwefix pfx_0f_ae_7 = {
	I(SwcMem | ByteOp, em_cwfwush), I(SwcMem | ByteOp, em_cwfwushopt), N, N,
};

static const stwuct gwoup_duaw gwoup15 = { {
	I(ModWM | Awigned16, em_fxsave),
	I(ModWM | Awigned16, em_fxwstow),
	N, N, N, N, N, GP(0, &pfx_0f_ae_7),
}, {
	N, N, N, N, N, N, N, N,
} };

static const stwuct gpwefix pfx_0f_6f_0f_7f = {
	I(Mmx, em_mov), I(Sse | Awigned, em_mov), N, I(Sse | Unawigned, em_mov),
};

static const stwuct instw_duaw instw_duaw_0f_2b = {
	I(0, em_mov), N
};

static const stwuct gpwefix pfx_0f_2b = {
	ID(0, &instw_duaw_0f_2b), ID(0, &instw_duaw_0f_2b), N, N,
};

static const stwuct gpwefix pfx_0f_10_0f_11 = {
	I(Unawigned, em_mov), I(Unawigned, em_mov), N, N,
};

static const stwuct gpwefix pfx_0f_28_0f_29 = {
	I(Awigned, em_mov), I(Awigned, em_mov), N, N,
};

static const stwuct gpwefix pfx_0f_e7 = {
	N, I(Sse, em_mov), N, N,
};

static const stwuct escape escape_d9 = { {
	N, N, N, N, N, N, N, I(DstMem16 | Mov, em_fnstcw),
}, {
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, N, N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
} };

static const stwuct escape escape_db = { {
	N, N, N, N, N, N, N, N,
}, {
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, I(ImpwicitOps, em_fninit), N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
} };

static const stwuct escape escape_dd = { {
	N, N, N, N, N, N, N, I(DstMem16 | Mov, em_fnstsw),
}, {
	/* 0xC0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xC8 - 0xCF */
	N, N, N, N, N, N, N, N,
	/* 0xD0 - 0xC7 */
	N, N, N, N, N, N, N, N,
	/* 0xD8 - 0xDF */
	N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xE7 */
	N, N, N, N, N, N, N, N,
	/* 0xE8 - 0xEF */
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xF7 */
	N, N, N, N, N, N, N, N,
	/* 0xF8 - 0xFF */
	N, N, N, N, N, N, N, N,
} };

static const stwuct instw_duaw instw_duaw_0f_c3 = {
	I(DstMem | SwcWeg | ModWM | No16 | Mov, em_mov), N
};

static const stwuct mode_duaw mode_duaw_63 = {
	N, I(DstWeg | SwcMem32 | ModWM | Mov, em_movsxd)
};

static const stwuct instw_duaw instw_duaw_8d = {
	D(DstWeg | SwcMem | ModWM | NoAccess), N
};

static const stwuct opcode opcode_tabwe[256] = {
	/* 0x00 - 0x07 */
	F6AWU(Wock, em_add),
	I(ImpwicitOps | Stack | No64 | Swc2ES, em_push_sweg),
	I(ImpwicitOps | Stack | No64 | Swc2ES, em_pop_sweg),
	/* 0x08 - 0x0F */
	F6AWU(Wock | PageTabwe, em_ow),
	I(ImpwicitOps | Stack | No64 | Swc2CS, em_push_sweg),
	N,
	/* 0x10 - 0x17 */
	F6AWU(Wock, em_adc),
	I(ImpwicitOps | Stack | No64 | Swc2SS, em_push_sweg),
	I(ImpwicitOps | Stack | No64 | Swc2SS, em_pop_sweg),
	/* 0x18 - 0x1F */
	F6AWU(Wock, em_sbb),
	I(ImpwicitOps | Stack | No64 | Swc2DS, em_push_sweg),
	I(ImpwicitOps | Stack | No64 | Swc2DS, em_pop_sweg),
	/* 0x20 - 0x27 */
	F6AWU(Wock | PageTabwe, em_and), N, N,
	/* 0x28 - 0x2F */
	F6AWU(Wock, em_sub), N, I(ByteOp | DstAcc | No64, em_das),
	/* 0x30 - 0x37 */
	F6AWU(Wock, em_xow), N, N,
	/* 0x38 - 0x3F */
	F6AWU(NoWwite, em_cmp), N, N,
	/* 0x40 - 0x4F */
	X8(F(DstWeg, em_inc)), X8(F(DstWeg, em_dec)),
	/* 0x50 - 0x57 */
	X8(I(SwcWeg | Stack, em_push)),
	/* 0x58 - 0x5F */
	X8(I(DstWeg | Stack, em_pop)),
	/* 0x60 - 0x67 */
	I(ImpwicitOps | Stack | No64, em_pusha),
	I(ImpwicitOps | Stack | No64, em_popa),
	N, MD(ModWM, &mode_duaw_63),
	N, N, N, N,
	/* 0x68 - 0x6F */
	I(SwcImm | Mov | Stack, em_push),
	I(DstWeg | SwcMem | ModWM | Swc2Imm, em_imuw_3op),
	I(SwcImmByte | Mov | Stack, em_push),
	I(DstWeg | SwcMem | ModWM | Swc2ImmByte, em_imuw_3op),
	I2bvIP(DstDI | SwcDX | Mov | Stwing | Unawigned, em_in, ins, check_pewm_in), /* insb, insw/insd */
	I2bvIP(SwcSI | DstDX | Stwing, em_out, outs, check_pewm_out), /* outsb, outsw/outsd */
	/* 0x70 - 0x7F */
	X16(D(SwcImmByte | NeawBwanch | IsBwanch)),
	/* 0x80 - 0x87 */
	G(ByteOp | DstMem | SwcImm, gwoup1),
	G(DstMem | SwcImm, gwoup1),
	G(ByteOp | DstMem | SwcImm | No64, gwoup1),
	G(DstMem | SwcImmByte, gwoup1),
	F2bv(DstMem | SwcWeg | ModWM | NoWwite, em_test),
	I2bv(DstMem | SwcWeg | ModWM | Wock | PageTabwe, em_xchg),
	/* 0x88 - 0x8F */
	I2bv(DstMem | SwcWeg | ModWM | Mov | PageTabwe, em_mov),
	I2bv(DstWeg | SwcMem | ModWM | Mov, em_mov),
	I(DstMem | SwcNone | ModWM | Mov | PageTabwe, em_mov_wm_sweg),
	ID(0, &instw_duaw_8d),
	I(ImpwicitOps | SwcMem16 | ModWM, em_mov_sweg_wm),
	G(0, gwoup1A),
	/* 0x90 - 0x97 */
	DI(SwcAcc | DstWeg, pause), X7(D(SwcAcc | DstWeg)),
	/* 0x98 - 0x9F */
	D(DstAcc | SwcNone), I(ImpwicitOps | SwcAcc, em_cwd),
	I(SwcImmFAddw | No64 | IsBwanch, em_caww_faw), N,
	II(ImpwicitOps | Stack, em_pushf, pushf),
	II(ImpwicitOps | Stack, em_popf, popf),
	I(ImpwicitOps, em_sahf), I(ImpwicitOps, em_wahf),
	/* 0xA0 - 0xA7 */
	I2bv(DstAcc | SwcMem | Mov | MemAbs, em_mov),
	I2bv(DstMem | SwcAcc | Mov | MemAbs | PageTabwe, em_mov),
	I2bv(SwcSI | DstDI | Mov | Stwing | TwoMemOp, em_mov),
	F2bv(SwcSI | DstDI | Stwing | NoWwite | TwoMemOp, em_cmp_w),
	/* 0xA8 - 0xAF */
	F2bv(DstAcc | SwcImm | NoWwite, em_test),
	I2bv(SwcAcc | DstDI | Mov | Stwing, em_mov),
	I2bv(SwcSI | DstAcc | Mov | Stwing, em_mov),
	F2bv(SwcAcc | DstDI | Stwing | NoWwite, em_cmp_w),
	/* 0xB0 - 0xB7 */
	X8(I(ByteOp | DstWeg | SwcImm | Mov, em_mov)),
	/* 0xB8 - 0xBF */
	X8(I(DstWeg | SwcImm64 | Mov, em_mov)),
	/* 0xC0 - 0xC7 */
	G(ByteOp | Swc2ImmByte, gwoup2), G(Swc2ImmByte, gwoup2),
	I(ImpwicitOps | NeawBwanch | SwcImmU16 | IsBwanch, em_wet_neaw_imm),
	I(ImpwicitOps | NeawBwanch | IsBwanch, em_wet),
	I(DstWeg | SwcMemFAddw | ModWM | No64 | Swc2ES, em_wseg),
	I(DstWeg | SwcMemFAddw | ModWM | No64 | Swc2DS, em_wseg),
	G(ByteOp, gwoup11), G(0, gwoup11),
	/* 0xC8 - 0xCF */
	I(Stack | SwcImmU16 | Swc2ImmByte | IsBwanch, em_entew),
	I(Stack | IsBwanch, em_weave),
	I(ImpwicitOps | SwcImmU16 | IsBwanch, em_wet_faw_imm),
	I(ImpwicitOps | IsBwanch, em_wet_faw),
	D(ImpwicitOps | IsBwanch), DI(SwcImmByte | IsBwanch, intn),
	D(ImpwicitOps | No64 | IsBwanch),
	II(ImpwicitOps | IsBwanch, em_iwet, iwet),
	/* 0xD0 - 0xD7 */
	G(Swc2One | ByteOp, gwoup2), G(Swc2One, gwoup2),
	G(Swc2CW | ByteOp, gwoup2), G(Swc2CW, gwoup2),
	I(DstAcc | SwcImmUByte | No64, em_aam),
	I(DstAcc | SwcImmUByte | No64, em_aad),
	F(DstAcc | ByteOp | No64, em_sawc),
	I(DstAcc | SwcXWat | ByteOp, em_mov),
	/* 0xD8 - 0xDF */
	N, E(0, &escape_d9), N, E(0, &escape_db), N, E(0, &escape_dd), N, N,
	/* 0xE0 - 0xE7 */
	X3(I(SwcImmByte | NeawBwanch | IsBwanch, em_woop)),
	I(SwcImmByte | NeawBwanch | IsBwanch, em_jcxz),
	I2bvIP(SwcImmUByte | DstAcc, em_in,  in,  check_pewm_in),
	I2bvIP(SwcAcc | DstImmUByte, em_out, out, check_pewm_out),
	/* 0xE8 - 0xEF */
	I(SwcImm | NeawBwanch | IsBwanch, em_caww),
	D(SwcImm | ImpwicitOps | NeawBwanch | IsBwanch),
	I(SwcImmFAddw | No64 | IsBwanch, em_jmp_faw),
	D(SwcImmByte | ImpwicitOps | NeawBwanch | IsBwanch),
	I2bvIP(SwcDX | DstAcc, em_in,  in,  check_pewm_in),
	I2bvIP(SwcAcc | DstDX, em_out, out, check_pewm_out),
	/* 0xF0 - 0xF7 */
	N, DI(ImpwicitOps, icebp), N, N,
	DI(ImpwicitOps | Pwiv, hwt), D(ImpwicitOps),
	G(ByteOp, gwoup3), G(0, gwoup3),
	/* 0xF8 - 0xFF */
	D(ImpwicitOps), D(ImpwicitOps),
	I(ImpwicitOps, em_cwi), I(ImpwicitOps, em_sti),
	D(ImpwicitOps), D(ImpwicitOps), G(0, gwoup4), G(0, gwoup5),
};

static const stwuct opcode twobyte_tabwe[256] = {
	/* 0x00 - 0x0F */
	G(0, gwoup6), GD(0, &gwoup7), N, N,
	N, I(ImpwicitOps | EmuwateOnUD | IsBwanch, em_syscaww),
	II(ImpwicitOps | Pwiv, em_cwts, cwts), N,
	DI(ImpwicitOps | Pwiv, invd), DI(ImpwicitOps | Pwiv, wbinvd), N, N,
	N, D(ImpwicitOps | ModWM | SwcMem | NoAccess), N, N,
	/* 0x10 - 0x1F */
	GP(ModWM | DstWeg | SwcMem | Mov | Sse, &pfx_0f_10_0f_11),
	GP(ModWM | DstMem | SwcWeg | Mov | Sse, &pfx_0f_10_0f_11),
	N, N, N, N, N, N,
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), /* 4 * pwefetch + 4 * wesewved NOP */
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), N, N,
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), /* 8 * wesewved NOP */
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), /* 8 * wesewved NOP */
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), /* 8 * wesewved NOP */
	D(ImpwicitOps | ModWM | SwcMem | NoAccess), /* NOP + 7 * wesewved NOP */
	/* 0x20 - 0x2F */
	DIP(ModWM | DstMem | Pwiv | Op3264 | NoMod, cw_wead, check_cw_access),
	DIP(ModWM | DstMem | Pwiv | Op3264 | NoMod, dw_wead, check_dw_wead),
	IIP(ModWM | SwcMem | Pwiv | Op3264 | NoMod, em_cw_wwite, cw_wwite,
						check_cw_access),
	IIP(ModWM | SwcMem | Pwiv | Op3264 | NoMod, em_dw_wwite, dw_wwite,
						check_dw_wwite),
	N, N, N, N,
	GP(ModWM | DstWeg | SwcMem | Mov | Sse, &pfx_0f_28_0f_29),
	GP(ModWM | DstMem | SwcWeg | Mov | Sse, &pfx_0f_28_0f_29),
	N, GP(ModWM | DstMem | SwcWeg | Mov | Sse, &pfx_0f_2b),
	N, N, N, N,
	/* 0x30 - 0x3F */
	II(ImpwicitOps | Pwiv, em_wwmsw, wwmsw),
	IIP(ImpwicitOps, em_wdtsc, wdtsc, check_wdtsc),
	II(ImpwicitOps | Pwiv, em_wdmsw, wdmsw),
	IIP(ImpwicitOps, em_wdpmc, wdpmc, check_wdpmc),
	I(ImpwicitOps | EmuwateOnUD | IsBwanch, em_sysentew),
	I(ImpwicitOps | Pwiv | EmuwateOnUD | IsBwanch, em_sysexit),
	N, N,
	N, N, N, N, N, N, N, N,
	/* 0x40 - 0x4F */
	X16(D(DstWeg | SwcMem | ModWM)),
	/* 0x50 - 0x5F */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,
	/* 0x60 - 0x6F */
	N, N, N, N,
	N, N, N, N,
	N, N, N, N,
	N, N, N, GP(SwcMem | DstWeg | ModWM | Mov, &pfx_0f_6f_0f_7f),
	/* 0x70 - 0x7F */
	N, N, N, N,
	N, N, N, N,
	N, N, N, N,
	N, N, N, GP(SwcWeg | DstMem | ModWM | Mov, &pfx_0f_6f_0f_7f),
	/* 0x80 - 0x8F */
	X16(D(SwcImm | NeawBwanch | IsBwanch)),
	/* 0x90 - 0x9F */
	X16(D(ByteOp | DstMem | SwcNone | ModWM| Mov)),
	/* 0xA0 - 0xA7 */
	I(Stack | Swc2FS, em_push_sweg), I(Stack | Swc2FS, em_pop_sweg),
	II(ImpwicitOps, em_cpuid, cpuid),
	F(DstMem | SwcWeg | ModWM | BitOp | NoWwite, em_bt),
	F(DstMem | SwcWeg | Swc2ImmByte | ModWM, em_shwd),
	F(DstMem | SwcWeg | Swc2CW | ModWM, em_shwd), N, N,
	/* 0xA8 - 0xAF */
	I(Stack | Swc2GS, em_push_sweg), I(Stack | Swc2GS, em_pop_sweg),
	II(EmuwateOnUD | ImpwicitOps, em_wsm, wsm),
	F(DstMem | SwcWeg | ModWM | BitOp | Wock | PageTabwe, em_bts),
	F(DstMem | SwcWeg | Swc2ImmByte | ModWM, em_shwd),
	F(DstMem | SwcWeg | Swc2CW | ModWM, em_shwd),
	GD(0, &gwoup15), F(DstWeg | SwcMem | ModWM, em_imuw),
	/* 0xB0 - 0xB7 */
	I2bv(DstMem | SwcWeg | ModWM | Wock | PageTabwe | SwcWwite, em_cmpxchg),
	I(DstWeg | SwcMemFAddw | ModWM | Swc2SS, em_wseg),
	F(DstMem | SwcWeg | ModWM | BitOp | Wock, em_btw),
	I(DstWeg | SwcMemFAddw | ModWM | Swc2FS, em_wseg),
	I(DstWeg | SwcMemFAddw | ModWM | Swc2GS, em_wseg),
	D(DstWeg | SwcMem8 | ModWM | Mov), D(DstWeg | SwcMem16 | ModWM | Mov),
	/* 0xB8 - 0xBF */
	N, N,
	G(BitOp, gwoup8),
	F(DstMem | SwcWeg | ModWM | BitOp | Wock | PageTabwe, em_btc),
	I(DstWeg | SwcMem | ModWM, em_bsf_c),
	I(DstWeg | SwcMem | ModWM, em_bsw_c),
	D(DstWeg | SwcMem8 | ModWM | Mov), D(DstWeg | SwcMem16 | ModWM | Mov),
	/* 0xC0 - 0xC7 */
	F2bv(DstMem | SwcWeg | ModWM | SwcWwite | Wock, em_xadd),
	N, ID(0, &instw_duaw_0f_c3),
	N, N, N, GD(0, &gwoup9),
	/* 0xC8 - 0xCF */
	X8(I(DstWeg, em_bswap)),
	/* 0xD0 - 0xDF */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,
	/* 0xE0 - 0xEF */
	N, N, N, N, N, N, N, GP(SwcWeg | DstMem | ModWM | Mov, &pfx_0f_e7),
	N, N, N, N, N, N, N, N,
	/* 0xF0 - 0xFF */
	N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N
};

static const stwuct instw_duaw instw_duaw_0f_38_f0 = {
	I(DstWeg | SwcMem | Mov, em_movbe), N
};

static const stwuct instw_duaw instw_duaw_0f_38_f1 = {
	I(DstMem | SwcWeg | Mov, em_movbe), N
};

static const stwuct gpwefix thwee_byte_0f_38_f0 = {
	ID(0, &instw_duaw_0f_38_f0), N, N, N
};

static const stwuct gpwefix thwee_byte_0f_38_f1 = {
	ID(0, &instw_duaw_0f_38_f1), N, N, N
};

/*
 * Insns bewow awe sewected by the pwefix which indexed by the thiwd opcode
 * byte.
 */
static const stwuct opcode opcode_map_0f_38[256] = {
	/* 0x00 - 0x7f */
	X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N),
	/* 0x80 - 0xef */
	X16(N), X16(N), X16(N), X16(N), X16(N), X16(N), X16(N),
	/* 0xf0 - 0xf1 */
	GP(EmuwateOnUD | ModWM, &thwee_byte_0f_38_f0),
	GP(EmuwateOnUD | ModWM, &thwee_byte_0f_38_f1),
	/* 0xf2 - 0xff */
	N, N, X4(N), X8(N)
};

#undef D
#undef N
#undef G
#undef GD
#undef I
#undef GP
#undef EXT
#undef MD
#undef ID

#undef D2bv
#undef D2bvIP
#undef I2bv
#undef I2bvIP
#undef I6AWU

static unsigned imm_size(stwuct x86_emuwate_ctxt *ctxt)
{
	unsigned size;

	size = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	if (size == 8)
		size = 4;
	wetuwn size;
}

static int decode_imm(stwuct x86_emuwate_ctxt *ctxt, stwuct opewand *op,
		      unsigned size, boow sign_extension)
{
	int wc = X86EMUW_CONTINUE;

	op->type = OP_IMM;
	op->bytes = size;
	op->addw.mem.ea = ctxt->_eip;
	/* NB. Immediates awe sign-extended as necessawy. */
	switch (op->bytes) {
	case 1:
		op->vaw = insn_fetch(s8, ctxt);
		bweak;
	case 2:
		op->vaw = insn_fetch(s16, ctxt);
		bweak;
	case 4:
		op->vaw = insn_fetch(s32, ctxt);
		bweak;
	case 8:
		op->vaw = insn_fetch(s64, ctxt);
		bweak;
	}
	if (!sign_extension) {
		switch (op->bytes) {
		case 1:
			op->vaw &= 0xff;
			bweak;
		case 2:
			op->vaw &= 0xffff;
			bweak;
		case 4:
			op->vaw &= 0xffffffff;
			bweak;
		}
	}
done:
	wetuwn wc;
}

static int decode_opewand(stwuct x86_emuwate_ctxt *ctxt, stwuct opewand *op,
			  unsigned d)
{
	int wc = X86EMUW_CONTINUE;

	switch (d) {
	case OpWeg:
		decode_wegistew_opewand(ctxt, op);
		bweak;
	case OpImmUByte:
		wc = decode_imm(ctxt, op, 1, fawse);
		bweak;
	case OpMem:
		ctxt->memop.bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
	mem_common:
		*op = ctxt->memop;
		ctxt->memopp = op;
		if (ctxt->d & BitOp)
			fetch_bit_opewand(ctxt);
		op->owig_vaw = op->vaw;
		bweak;
	case OpMem64:
		ctxt->memop.bytes = (ctxt->op_bytes == 8) ? 16 : 8;
		goto mem_common;
	case OpAcc:
		op->type = OP_WEG;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addw.weg = weg_wmw(ctxt, VCPU_WEGS_WAX);
		fetch_wegistew_opewand(op);
		op->owig_vaw = op->vaw;
		bweak;
	case OpAccWo:
		op->type = OP_WEG;
		op->bytes = (ctxt->d & ByteOp) ? 2 : ctxt->op_bytes;
		op->addw.weg = weg_wmw(ctxt, VCPU_WEGS_WAX);
		fetch_wegistew_opewand(op);
		op->owig_vaw = op->vaw;
		bweak;
	case OpAccHi:
		if (ctxt->d & ByteOp) {
			op->type = OP_NONE;
			bweak;
		}
		op->type = OP_WEG;
		op->bytes = ctxt->op_bytes;
		op->addw.weg = weg_wmw(ctxt, VCPU_WEGS_WDX);
		fetch_wegistew_opewand(op);
		op->owig_vaw = op->vaw;
		bweak;
	case OpDI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addw.mem.ea =
			wegistew_addwess(ctxt, VCPU_WEGS_WDI);
		op->addw.mem.seg = VCPU_SWEG_ES;
		op->vaw = 0;
		op->count = 1;
		bweak;
	case OpDX:
		op->type = OP_WEG;
		op->bytes = 2;
		op->addw.weg = weg_wmw(ctxt, VCPU_WEGS_WDX);
		fetch_wegistew_opewand(op);
		bweak;
	case OpCW:
		op->type = OP_IMM;
		op->bytes = 1;
		op->vaw = weg_wead(ctxt, VCPU_WEGS_WCX) & 0xff;
		bweak;
	case OpImmByte:
		wc = decode_imm(ctxt, op, 1, twue);
		bweak;
	case OpOne:
		op->type = OP_IMM;
		op->bytes = 1;
		op->vaw = 1;
		bweak;
	case OpImm:
		wc = decode_imm(ctxt, op, imm_size(ctxt), twue);
		bweak;
	case OpImm64:
		wc = decode_imm(ctxt, op, ctxt->op_bytes, twue);
		bweak;
	case OpMem8:
		ctxt->memop.bytes = 1;
		if (ctxt->memop.type == OP_WEG) {
			ctxt->memop.addw.weg = decode_wegistew(ctxt,
					ctxt->modwm_wm, twue);
			fetch_wegistew_opewand(&ctxt->memop);
		}
		goto mem_common;
	case OpMem16:
		ctxt->memop.bytes = 2;
		goto mem_common;
	case OpMem32:
		ctxt->memop.bytes = 4;
		goto mem_common;
	case OpImmU16:
		wc = decode_imm(ctxt, op, 2, fawse);
		bweak;
	case OpImmU:
		wc = decode_imm(ctxt, op, imm_size(ctxt), fawse);
		bweak;
	case OpSI:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addw.mem.ea =
			wegistew_addwess(ctxt, VCPU_WEGS_WSI);
		op->addw.mem.seg = ctxt->seg_ovewwide;
		op->vaw = 0;
		op->count = 1;
		bweak;
	case OpXWat:
		op->type = OP_MEM;
		op->bytes = (ctxt->d & ByteOp) ? 1 : ctxt->op_bytes;
		op->addw.mem.ea =
			addwess_mask(ctxt,
				weg_wead(ctxt, VCPU_WEGS_WBX) +
				(weg_wead(ctxt, VCPU_WEGS_WAX) & 0xff));
		op->addw.mem.seg = ctxt->seg_ovewwide;
		op->vaw = 0;
		bweak;
	case OpImmFAddw:
		op->type = OP_IMM;
		op->addw.mem.ea = ctxt->_eip;
		op->bytes = ctxt->op_bytes + 2;
		insn_fetch_aww(op->vawptw, op->bytes, ctxt);
		bweak;
	case OpMemFAddw:
		ctxt->memop.bytes = ctxt->op_bytes + 2;
		goto mem_common;
	case OpES:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_ES;
		bweak;
	case OpCS:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_CS;
		bweak;
	case OpSS:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_SS;
		bweak;
	case OpDS:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_DS;
		bweak;
	case OpFS:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_FS;
		bweak;
	case OpGS:
		op->type = OP_IMM;
		op->vaw = VCPU_SWEG_GS;
		bweak;
	case OpImpwicit:
		/* Speciaw instwuctions do theiw own opewand decoding. */
	defauwt:
		op->type = OP_NONE; /* Disabwe wwiteback. */
		bweak;
	}

done:
	wetuwn wc;
}

int x86_decode_insn(stwuct x86_emuwate_ctxt *ctxt, void *insn, int insn_wen, int emuwation_type)
{
	int wc = X86EMUW_CONTINUE;
	int mode = ctxt->mode;
	int def_op_bytes, def_ad_bytes, goffset, simd_pwefix;
	boow op_pwefix = fawse;
	boow has_seg_ovewwide = fawse;
	stwuct opcode opcode;
	u16 dummy;
	stwuct desc_stwuct desc;

	ctxt->memop.type = OP_NONE;
	ctxt->memopp = NUWW;
	ctxt->_eip = ctxt->eip;
	ctxt->fetch.ptw = ctxt->fetch.data;
	ctxt->fetch.end = ctxt->fetch.data + insn_wen;
	ctxt->opcode_wen = 1;
	ctxt->intewcept = x86_intewcept_none;
	if (insn_wen > 0)
		memcpy(ctxt->fetch.data, insn, insn_wen);
	ewse {
		wc = __do_insn_fetch_bytes(ctxt, 1);
		if (wc != X86EMUW_CONTINUE)
			goto done;
	}

	switch (mode) {
	case X86EMUW_MODE_WEAW:
	case X86EMUW_MODE_VM86:
		def_op_bytes = def_ad_bytes = 2;
		ctxt->ops->get_segment(ctxt, &dummy, &desc, NUWW, VCPU_SWEG_CS);
		if (desc.d)
			def_op_bytes = def_ad_bytes = 4;
		bweak;
	case X86EMUW_MODE_PWOT16:
		def_op_bytes = def_ad_bytes = 2;
		bweak;
	case X86EMUW_MODE_PWOT32:
		def_op_bytes = def_ad_bytes = 4;
		bweak;
#ifdef CONFIG_X86_64
	case X86EMUW_MODE_PWOT64:
		def_op_bytes = 4;
		def_ad_bytes = 8;
		bweak;
#endif
	defauwt:
		wetuwn EMUWATION_FAIWED;
	}

	ctxt->op_bytes = def_op_bytes;
	ctxt->ad_bytes = def_ad_bytes;

	/* Wegacy pwefixes. */
	fow (;;) {
		switch (ctxt->b = insn_fetch(u8, ctxt)) {
		case 0x66:	/* opewand-size ovewwide */
			op_pwefix = twue;
			/* switch between 2/4 bytes */
			ctxt->op_bytes = def_op_bytes ^ 6;
			bweak;
		case 0x67:	/* addwess-size ovewwide */
			if (mode == X86EMUW_MODE_PWOT64)
				/* switch between 4/8 bytes */
				ctxt->ad_bytes = def_ad_bytes ^ 12;
			ewse
				/* switch between 2/4 bytes */
				ctxt->ad_bytes = def_ad_bytes ^ 6;
			bweak;
		case 0x26:	/* ES ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_ES;
			bweak;
		case 0x2e:	/* CS ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_CS;
			bweak;
		case 0x36:	/* SS ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_SS;
			bweak;
		case 0x3e:	/* DS ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_DS;
			bweak;
		case 0x64:	/* FS ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_FS;
			bweak;
		case 0x65:	/* GS ovewwide */
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = VCPU_SWEG_GS;
			bweak;
		case 0x40 ... 0x4f: /* WEX */
			if (mode != X86EMUW_MODE_PWOT64)
				goto done_pwefixes;
			ctxt->wex_pwefix = ctxt->b;
			continue;
		case 0xf0:	/* WOCK */
			ctxt->wock_pwefix = 1;
			bweak;
		case 0xf2:	/* WEPNE/WEPNZ */
		case 0xf3:	/* WEP/WEPE/WEPZ */
			ctxt->wep_pwefix = ctxt->b;
			bweak;
		defauwt:
			goto done_pwefixes;
		}

		/* Any wegacy pwefix aftew a WEX pwefix nuwwifies its effect. */

		ctxt->wex_pwefix = 0;
	}

done_pwefixes:

	/* WEX pwefix. */
	if (ctxt->wex_pwefix & 8)
		ctxt->op_bytes = 8;	/* WEX.W */

	/* Opcode byte(s). */
	opcode = opcode_tabwe[ctxt->b];
	/* Two-byte opcode? */
	if (ctxt->b == 0x0f) {
		ctxt->opcode_wen = 2;
		ctxt->b = insn_fetch(u8, ctxt);
		opcode = twobyte_tabwe[ctxt->b];

		/* 0F_38 opcode map */
		if (ctxt->b == 0x38) {
			ctxt->opcode_wen = 3;
			ctxt->b = insn_fetch(u8, ctxt);
			opcode = opcode_map_0f_38[ctxt->b];
		}
	}
	ctxt->d = opcode.fwags;

	if (ctxt->d & ModWM)
		ctxt->modwm = insn_fetch(u8, ctxt);

	/* vex-pwefix instwuctions awe not impwemented */
	if (ctxt->opcode_wen == 1 && (ctxt->b == 0xc5 || ctxt->b == 0xc4) &&
	    (mode == X86EMUW_MODE_PWOT64 || (ctxt->modwm & 0xc0) == 0xc0)) {
		ctxt->d = NotImpw;
	}

	whiwe (ctxt->d & GwoupMask) {
		switch (ctxt->d & GwoupMask) {
		case Gwoup:
			goffset = (ctxt->modwm >> 3) & 7;
			opcode = opcode.u.gwoup[goffset];
			bweak;
		case GwoupDuaw:
			goffset = (ctxt->modwm >> 3) & 7;
			if ((ctxt->modwm >> 6) == 3)
				opcode = opcode.u.gduaw->mod3[goffset];
			ewse
				opcode = opcode.u.gduaw->mod012[goffset];
			bweak;
		case WMExt:
			goffset = ctxt->modwm & 7;
			opcode = opcode.u.gwoup[goffset];
			bweak;
		case Pwefix:
			if (ctxt->wep_pwefix && op_pwefix)
				wetuwn EMUWATION_FAIWED;
			simd_pwefix = op_pwefix ? 0x66 : ctxt->wep_pwefix;
			switch (simd_pwefix) {
			case 0x00: opcode = opcode.u.gpwefix->pfx_no; bweak;
			case 0x66: opcode = opcode.u.gpwefix->pfx_66; bweak;
			case 0xf2: opcode = opcode.u.gpwefix->pfx_f2; bweak;
			case 0xf3: opcode = opcode.u.gpwefix->pfx_f3; bweak;
			}
			bweak;
		case Escape:
			if (ctxt->modwm > 0xbf) {
				size_t size = AWWAY_SIZE(opcode.u.esc->high);
				u32 index = awway_index_nospec(
					ctxt->modwm - 0xc0, size);

				opcode = opcode.u.esc->high[index];
			} ewse {
				opcode = opcode.u.esc->op[(ctxt->modwm >> 3) & 7];
			}
			bweak;
		case InstwDuaw:
			if ((ctxt->modwm >> 6) == 3)
				opcode = opcode.u.iduaw->mod3;
			ewse
				opcode = opcode.u.iduaw->mod012;
			bweak;
		case ModeDuaw:
			if (ctxt->mode == X86EMUW_MODE_PWOT64)
				opcode = opcode.u.mduaw->mode64;
			ewse
				opcode = opcode.u.mduaw->mode32;
			bweak;
		defauwt:
			wetuwn EMUWATION_FAIWED;
		}

		ctxt->d &= ~(u64)GwoupMask;
		ctxt->d |= opcode.fwags;
	}

	ctxt->is_bwanch = opcode.fwags & IsBwanch;

	/* Unwecognised? */
	if (ctxt->d == 0)
		wetuwn EMUWATION_FAIWED;

	ctxt->execute = opcode.u.execute;

	if (unwikewy(emuwation_type & EMUWTYPE_TWAP_UD) &&
	    wikewy(!(ctxt->d & EmuwateOnUD)))
		wetuwn EMUWATION_FAIWED;

	if (unwikewy(ctxt->d &
	    (NotImpw|Stack|Op3264|Sse|Mmx|Intewcept|CheckPewm|NeawBwanch|
	     No16))) {
		/*
		 * These awe copied unconditionawwy hewe, and checked unconditionawwy
		 * in x86_emuwate_insn.
		 */
		ctxt->check_pewm = opcode.check_pewm;
		ctxt->intewcept = opcode.intewcept;

		if (ctxt->d & NotImpw)
			wetuwn EMUWATION_FAIWED;

		if (mode == X86EMUW_MODE_PWOT64) {
			if (ctxt->op_bytes == 4 && (ctxt->d & Stack))
				ctxt->op_bytes = 8;
			ewse if (ctxt->d & NeawBwanch)
				ctxt->op_bytes = 8;
		}

		if (ctxt->d & Op3264) {
			if (mode == X86EMUW_MODE_PWOT64)
				ctxt->op_bytes = 8;
			ewse
				ctxt->op_bytes = 4;
		}

		if ((ctxt->d & No16) && ctxt->op_bytes == 2)
			ctxt->op_bytes = 4;

		if (ctxt->d & Sse)
			ctxt->op_bytes = 16;
		ewse if (ctxt->d & Mmx)
			ctxt->op_bytes = 8;
	}

	/* ModWM and SIB bytes. */
	if (ctxt->d & ModWM) {
		wc = decode_modwm(ctxt, &ctxt->memop);
		if (!has_seg_ovewwide) {
			has_seg_ovewwide = twue;
			ctxt->seg_ovewwide = ctxt->modwm_seg;
		}
	} ewse if (ctxt->d & MemAbs)
		wc = decode_abs(ctxt, &ctxt->memop);
	if (wc != X86EMUW_CONTINUE)
		goto done;

	if (!has_seg_ovewwide)
		ctxt->seg_ovewwide = VCPU_SWEG_DS;

	ctxt->memop.addw.mem.seg = ctxt->seg_ovewwide;

	/*
	 * Decode and fetch the souwce opewand: wegistew, memowy
	 * ow immediate.
	 */
	wc = decode_opewand(ctxt, &ctxt->swc, (ctxt->d >> SwcShift) & OpMask);
	if (wc != X86EMUW_CONTINUE)
		goto done;

	/*
	 * Decode and fetch the second souwce opewand: wegistew, memowy
	 * ow immediate.
	 */
	wc = decode_opewand(ctxt, &ctxt->swc2, (ctxt->d >> Swc2Shift) & OpMask);
	if (wc != X86EMUW_CONTINUE)
		goto done;

	/* Decode and fetch the destination opewand: wegistew ow memowy. */
	wc = decode_opewand(ctxt, &ctxt->dst, (ctxt->d >> DstShift) & OpMask);

	if (ctxt->wip_wewative && wikewy(ctxt->memopp))
		ctxt->memopp->addw.mem.ea = addwess_mask(ctxt,
					ctxt->memopp->addw.mem.ea + ctxt->_eip);

done:
	if (wc == X86EMUW_PWOPAGATE_FAUWT)
		ctxt->have_exception = twue;
	wetuwn (wc != X86EMUW_CONTINUE) ? EMUWATION_FAIWED : EMUWATION_OK;
}

boow x86_page_tabwe_wwiting_insn(stwuct x86_emuwate_ctxt *ctxt)
{
	wetuwn ctxt->d & PageTabwe;
}

static boow stwing_insn_compweted(stwuct x86_emuwate_ctxt *ctxt)
{
	/* The second tewmination condition onwy appwies fow WEPE
	 * and WEPNE. Test if the wepeat stwing opewation pwefix is
	 * WEPE/WEPZ ow WEPNE/WEPNZ and if it's the case it tests the
	 * cowwesponding tewmination condition accowding to:
	 * 	- if WEPE/WEPZ and ZF = 0 then done
	 * 	- if WEPNE/WEPNZ and ZF = 1 then done
	 */
	if (((ctxt->b == 0xa6) || (ctxt->b == 0xa7) ||
	     (ctxt->b == 0xae) || (ctxt->b == 0xaf))
	    && (((ctxt->wep_pwefix == WEPE_PWEFIX) &&
		 ((ctxt->efwags & X86_EFWAGS_ZF) == 0))
		|| ((ctxt->wep_pwefix == WEPNE_PWEFIX) &&
		    ((ctxt->efwags & X86_EFWAGS_ZF) == X86_EFWAGS_ZF))))
		wetuwn twue;

	wetuwn fawse;
}

static int fwush_pending_x87_fauwts(stwuct x86_emuwate_ctxt *ctxt)
{
	int wc;

	kvm_fpu_get();
	wc = asm_safe("fwait");
	kvm_fpu_put();

	if (unwikewy(wc != X86EMUW_CONTINUE))
		wetuwn emuwate_exception(ctxt, MF_VECTOW, 0, fawse);

	wetuwn X86EMUW_CONTINUE;
}

static void fetch_possibwe_mmx_opewand(stwuct opewand *op)
{
	if (op->type == OP_MM)
		kvm_wead_mmx_weg(op->addw.mm, &op->mm_vaw);
}

static int fastop(stwuct x86_emuwate_ctxt *ctxt, fastop_t fop)
{
	uwong fwags = (ctxt->efwags & EFWAGS_MASK) | X86_EFWAGS_IF;

	if (!(ctxt->d & ByteOp))
		fop += __ffs(ctxt->dst.bytes) * FASTOP_SIZE;

	asm("push %[fwags]; popf; " CAWW_NOSPEC " ; pushf; pop %[fwags]\n"
	    : "+a"(ctxt->dst.vaw), "+d"(ctxt->swc.vaw), [fwags]"+D"(fwags),
	      [thunk_tawget]"+S"(fop), ASM_CAWW_CONSTWAINT
	    : "c"(ctxt->swc2.vaw));

	ctxt->efwags = (ctxt->efwags & ~EFWAGS_MASK) | (fwags & EFWAGS_MASK);
	if (!fop) /* exception is wetuwned in fop vawiabwe */
		wetuwn emuwate_de(ctxt);
	wetuwn X86EMUW_CONTINUE;
}

void init_decode_cache(stwuct x86_emuwate_ctxt *ctxt)
{
	/* Cweaw fiewds that awe set conditionawwy but wead without a guawd. */
	ctxt->wip_wewative = fawse;
	ctxt->wex_pwefix = 0;
	ctxt->wock_pwefix = 0;
	ctxt->wep_pwefix = 0;
	ctxt->wegs_vawid = 0;
	ctxt->wegs_diwty = 0;

	ctxt->io_wead.pos = 0;
	ctxt->io_wead.end = 0;
	ctxt->mem_wead.end = 0;
}

int x86_emuwate_insn(stwuct x86_emuwate_ctxt *ctxt)
{
	const stwuct x86_emuwate_ops *ops = ctxt->ops;
	int wc = X86EMUW_CONTINUE;
	int saved_dst_type = ctxt->dst.type;
	boow is_guest_mode = ctxt->ops->is_guest_mode(ctxt);

	ctxt->mem_wead.pos = 0;

	/* WOCK pwefix is awwowed onwy with some instwuctions */
	if (ctxt->wock_pwefix && (!(ctxt->d & Wock) || ctxt->dst.type != OP_MEM)) {
		wc = emuwate_ud(ctxt);
		goto done;
	}

	if ((ctxt->d & SwcMask) == SwcMemFAddw && ctxt->swc.type != OP_MEM) {
		wc = emuwate_ud(ctxt);
		goto done;
	}

	if (unwikewy(ctxt->d &
		     (No64|Undefined|Sse|Mmx|Intewcept|CheckPewm|Pwiv|Pwot|Stwing))) {
		if ((ctxt->mode == X86EMUW_MODE_PWOT64 && (ctxt->d & No64)) ||
				(ctxt->d & Undefined)) {
			wc = emuwate_ud(ctxt);
			goto done;
		}

		if (((ctxt->d & (Sse|Mmx)) && ((ops->get_cw(ctxt, 0) & X86_CW0_EM)))
		    || ((ctxt->d & Sse) && !(ops->get_cw(ctxt, 4) & X86_CW4_OSFXSW))) {
			wc = emuwate_ud(ctxt);
			goto done;
		}

		if ((ctxt->d & (Sse|Mmx)) && (ops->get_cw(ctxt, 0) & X86_CW0_TS)) {
			wc = emuwate_nm(ctxt);
			goto done;
		}

		if (ctxt->d & Mmx) {
			wc = fwush_pending_x87_fauwts(ctxt);
			if (wc != X86EMUW_CONTINUE)
				goto done;
			/*
			 * Now that we know the fpu is exception safe, we can fetch
			 * opewands fwom it.
			 */
			fetch_possibwe_mmx_opewand(&ctxt->swc);
			fetch_possibwe_mmx_opewand(&ctxt->swc2);
			if (!(ctxt->d & Mov))
				fetch_possibwe_mmx_opewand(&ctxt->dst);
		}

		if (unwikewy(is_guest_mode) && ctxt->intewcept) {
			wc = emuwatow_check_intewcept(ctxt, ctxt->intewcept,
						      X86_ICPT_PWE_EXCEPT);
			if (wc != X86EMUW_CONTINUE)
				goto done;
		}

		/* Instwuction can onwy be executed in pwotected mode */
		if ((ctxt->d & Pwot) && ctxt->mode < X86EMUW_MODE_PWOT16) {
			wc = emuwate_ud(ctxt);
			goto done;
		}

		/* Pwiviweged instwuction can be executed onwy in CPW=0 */
		if ((ctxt->d & Pwiv) && ops->cpw(ctxt)) {
			if (ctxt->d & PwivUD)
				wc = emuwate_ud(ctxt);
			ewse
				wc = emuwate_gp(ctxt, 0);
			goto done;
		}

		/* Do instwuction specific pewmission checks */
		if (ctxt->d & CheckPewm) {
			wc = ctxt->check_pewm(ctxt);
			if (wc != X86EMUW_CONTINUE)
				goto done;
		}

		if (unwikewy(is_guest_mode) && (ctxt->d & Intewcept)) {
			wc = emuwatow_check_intewcept(ctxt, ctxt->intewcept,
						      X86_ICPT_POST_EXCEPT);
			if (wc != X86EMUW_CONTINUE)
				goto done;
		}

		if (ctxt->wep_pwefix && (ctxt->d & Stwing)) {
			/* Aww WEP pwefixes have the same fiwst tewmination condition */
			if (addwess_mask(ctxt, weg_wead(ctxt, VCPU_WEGS_WCX)) == 0) {
				stwing_wegistews_quiwk(ctxt);
				ctxt->eip = ctxt->_eip;
				ctxt->efwags &= ~X86_EFWAGS_WF;
				goto done;
			}
		}
	}

	if ((ctxt->swc.type == OP_MEM) && !(ctxt->d & NoAccess)) {
		wc = segmented_wead(ctxt, ctxt->swc.addw.mem,
				    ctxt->swc.vawptw, ctxt->swc.bytes);
		if (wc != X86EMUW_CONTINUE)
			goto done;
		ctxt->swc.owig_vaw64 = ctxt->swc.vaw64;
	}

	if (ctxt->swc2.type == OP_MEM) {
		wc = segmented_wead(ctxt, ctxt->swc2.addw.mem,
				    &ctxt->swc2.vaw, ctxt->swc2.bytes);
		if (wc != X86EMUW_CONTINUE)
			goto done;
	}

	if ((ctxt->d & DstMask) == ImpwicitOps)
		goto speciaw_insn;


	if ((ctxt->dst.type == OP_MEM) && !(ctxt->d & Mov)) {
		/* optimisation - avoid swow emuwated wead if Mov */
		wc = segmented_wead(ctxt, ctxt->dst.addw.mem,
				   &ctxt->dst.vaw, ctxt->dst.bytes);
		if (wc != X86EMUW_CONTINUE) {
			if (!(ctxt->d & NoWwite) &&
			    wc == X86EMUW_PWOPAGATE_FAUWT &&
			    ctxt->exception.vectow == PF_VECTOW)
				ctxt->exception.ewwow_code |= PFEWW_WWITE_MASK;
			goto done;
		}
	}
	/* Copy fuww 64-bit vawue fow CMPXCHG8B.  */
	ctxt->dst.owig_vaw64 = ctxt->dst.vaw64;

speciaw_insn:

	if (unwikewy(is_guest_mode) && (ctxt->d & Intewcept)) {
		wc = emuwatow_check_intewcept(ctxt, ctxt->intewcept,
					      X86_ICPT_POST_MEMACCESS);
		if (wc != X86EMUW_CONTINUE)
			goto done;
	}

	if (ctxt->wep_pwefix && (ctxt->d & Stwing))
		ctxt->efwags |= X86_EFWAGS_WF;
	ewse
		ctxt->efwags &= ~X86_EFWAGS_WF;

	if (ctxt->execute) {
		if (ctxt->d & Fastop)
			wc = fastop(ctxt, ctxt->fop);
		ewse
			wc = ctxt->execute(ctxt);
		if (wc != X86EMUW_CONTINUE)
			goto done;
		goto wwiteback;
	}

	if (ctxt->opcode_wen == 2)
		goto twobyte_insn;
	ewse if (ctxt->opcode_wen == 3)
		goto thweebyte_insn;

	switch (ctxt->b) {
	case 0x70 ... 0x7f: /* jcc (showt) */
		if (test_cc(ctxt->b, ctxt->efwags))
			wc = jmp_wew(ctxt, ctxt->swc.vaw);
		bweak;
	case 0x8d: /* wea w16/w32, m */
		ctxt->dst.vaw = ctxt->swc.addw.mem.ea;
		bweak;
	case 0x90 ... 0x97: /* nop / xchg weg, wax */
		if (ctxt->dst.addw.weg == weg_wmw(ctxt, VCPU_WEGS_WAX))
			ctxt->dst.type = OP_NONE;
		ewse
			wc = em_xchg(ctxt);
		bweak;
	case 0x98: /* cbw/cwde/cdqe */
		switch (ctxt->op_bytes) {
		case 2: ctxt->dst.vaw = (s8)ctxt->dst.vaw; bweak;
		case 4: ctxt->dst.vaw = (s16)ctxt->dst.vaw; bweak;
		case 8: ctxt->dst.vaw = (s32)ctxt->dst.vaw; bweak;
		}
		bweak;
	case 0xcc:		/* int3 */
		wc = emuwate_int(ctxt, 3);
		bweak;
	case 0xcd:		/* int n */
		wc = emuwate_int(ctxt, ctxt->swc.vaw);
		bweak;
	case 0xce:		/* into */
		if (ctxt->efwags & X86_EFWAGS_OF)
			wc = emuwate_int(ctxt, 4);
		bweak;
	case 0xe9: /* jmp wew */
	case 0xeb: /* jmp wew showt */
		wc = jmp_wew(ctxt, ctxt->swc.vaw);
		ctxt->dst.type = OP_NONE; /* Disabwe wwiteback. */
		bweak;
	case 0xf4:              /* hwt */
		ctxt->ops->hawt(ctxt);
		bweak;
	case 0xf5:	/* cmc */
		/* compwement cawwy fwag fwom efwags weg */
		ctxt->efwags ^= X86_EFWAGS_CF;
		bweak;
	case 0xf8: /* cwc */
		ctxt->efwags &= ~X86_EFWAGS_CF;
		bweak;
	case 0xf9: /* stc */
		ctxt->efwags |= X86_EFWAGS_CF;
		bweak;
	case 0xfc: /* cwd */
		ctxt->efwags &= ~X86_EFWAGS_DF;
		bweak;
	case 0xfd: /* std */
		ctxt->efwags |= X86_EFWAGS_DF;
		bweak;
	defauwt:
		goto cannot_emuwate;
	}

	if (wc != X86EMUW_CONTINUE)
		goto done;

wwiteback:
	if (ctxt->d & SwcWwite) {
		BUG_ON(ctxt->swc.type == OP_MEM || ctxt->swc.type == OP_MEM_STW);
		wc = wwiteback(ctxt, &ctxt->swc);
		if (wc != X86EMUW_CONTINUE)
			goto done;
	}
	if (!(ctxt->d & NoWwite)) {
		wc = wwiteback(ctxt, &ctxt->dst);
		if (wc != X86EMUW_CONTINUE)
			goto done;
	}

	/*
	 * westowe dst type in case the decoding wiww be weused
	 * (happens fow stwing instwuction )
	 */
	ctxt->dst.type = saved_dst_type;

	if ((ctxt->d & SwcMask) == SwcSI)
		stwing_addw_inc(ctxt, VCPU_WEGS_WSI, &ctxt->swc);

	if ((ctxt->d & DstMask) == DstDI)
		stwing_addw_inc(ctxt, VCPU_WEGS_WDI, &ctxt->dst);

	if (ctxt->wep_pwefix && (ctxt->d & Stwing)) {
		unsigned int count;
		stwuct wead_cache *w = &ctxt->io_wead;
		if ((ctxt->d & SwcMask) == SwcSI)
			count = ctxt->swc.count;
		ewse
			count = ctxt->dst.count;
		wegistew_addwess_incwement(ctxt, VCPU_WEGS_WCX, -count);

		if (!stwing_insn_compweted(ctxt)) {
			/*
			 * We-entew guest when pio wead ahead buffew is empty
			 * ow, if it is not used, aftew each 1024 itewation.
			 */
			if ((w->end != 0 || weg_wead(ctxt, VCPU_WEGS_WCX) & 0x3ff) &&
			    (w->end == 0 || w->end != w->pos)) {
				/*
				 * Weset wead cache. Usuawwy happens befowe
				 * decode, but since instwuction is westawted
				 * we have to do it hewe.
				 */
				ctxt->mem_wead.end = 0;
				wwiteback_wegistews(ctxt);
				wetuwn EMUWATION_WESTAWT;
			}
			goto done; /* skip wip wwiteback */
		}
		ctxt->efwags &= ~X86_EFWAGS_WF;
	}

	ctxt->eip = ctxt->_eip;
	if (ctxt->mode != X86EMUW_MODE_PWOT64)
		ctxt->eip = (u32)ctxt->_eip;

done:
	if (wc == X86EMUW_PWOPAGATE_FAUWT) {
		if (KVM_EMUWATOW_BUG_ON(ctxt->exception.vectow > 0x1f, ctxt))
			wetuwn EMUWATION_FAIWED;
		ctxt->have_exception = twue;
	}
	if (wc == X86EMUW_INTEWCEPTED)
		wetuwn EMUWATION_INTEWCEPTED;

	if (wc == X86EMUW_CONTINUE)
		wwiteback_wegistews(ctxt);

	wetuwn (wc == X86EMUW_UNHANDWEABWE) ? EMUWATION_FAIWED : EMUWATION_OK;

twobyte_insn:
	switch (ctxt->b) {
	case 0x09:		/* wbinvd */
		(ctxt->ops->wbinvd)(ctxt);
		bweak;
	case 0x08:		/* invd */
	case 0x0d:		/* GwpP (pwefetch) */
	case 0x18:		/* Gwp16 (pwefetch/nop) */
	case 0x1f:		/* nop */
		bweak;
	case 0x20: /* mov cw, weg */
		ctxt->dst.vaw = ops->get_cw(ctxt, ctxt->modwm_weg);
		bweak;
	case 0x21: /* mov fwom dw to weg */
		ops->get_dw(ctxt, ctxt->modwm_weg, &ctxt->dst.vaw);
		bweak;
	case 0x40 ... 0x4f:	/* cmov */
		if (test_cc(ctxt->b, ctxt->efwags))
			ctxt->dst.vaw = ctxt->swc.vaw;
		ewse if (ctxt->op_bytes != 4)
			ctxt->dst.type = OP_NONE; /* no wwiteback */
		bweak;
	case 0x80 ... 0x8f: /* jnz wew, etc*/
		if (test_cc(ctxt->b, ctxt->efwags))
			wc = jmp_wew(ctxt, ctxt->swc.vaw);
		bweak;
	case 0x90 ... 0x9f:     /* setcc w/m8 */
		ctxt->dst.vaw = test_cc(ctxt->b, ctxt->efwags);
		bweak;
	case 0xb6 ... 0xb7:	/* movzx */
		ctxt->dst.bytes = ctxt->op_bytes;
		ctxt->dst.vaw = (ctxt->swc.bytes == 1) ? (u8) ctxt->swc.vaw
						       : (u16) ctxt->swc.vaw;
		bweak;
	case 0xbe ... 0xbf:	/* movsx */
		ctxt->dst.bytes = ctxt->op_bytes;
		ctxt->dst.vaw = (ctxt->swc.bytes == 1) ? (s8) ctxt->swc.vaw :
							(s16) ctxt->swc.vaw;
		bweak;
	defauwt:
		goto cannot_emuwate;
	}

thweebyte_insn:

	if (wc != X86EMUW_CONTINUE)
		goto done;

	goto wwiteback;

cannot_emuwate:
	wetuwn EMUWATION_FAIWED;
}

void emuwatow_invawidate_wegistew_cache(stwuct x86_emuwate_ctxt *ctxt)
{
	invawidate_wegistews(ctxt);
}

void emuwatow_wwiteback_wegistew_cache(stwuct x86_emuwate_ctxt *ctxt)
{
	wwiteback_wegistews(ctxt);
}

boow emuwatow_can_use_gpa(stwuct x86_emuwate_ctxt *ctxt)
{
	if (ctxt->wep_pwefix && (ctxt->d & Stwing))
		wetuwn fawse;

	if (ctxt->d & TwoMemOp)
		wetuwn fawse;

	wetuwn twue;
}
