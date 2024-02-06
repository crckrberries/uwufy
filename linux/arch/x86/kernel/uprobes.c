// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usew-space Pwobes (UPwobes) fow x86
 *
 * Copywight (C) IBM Cowpowation, 2008-2011
 * Authows:
 *	Swikaw Dwonamwaju
 *	Jim Keniston
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/upwobes.h>
#incwude <winux/uaccess.h>

#incwude <winux/kdebug.h>
#incwude <asm/pwocessow.h>
#incwude <asm/insn.h>
#incwude <asm/mmu_context.h>

/* Post-execution fixups. */

/* Adjust IP back to vicinity of actuaw insn */
#define UPWOBE_FIX_IP		0x01

/* Adjust the wetuwn addwess of a caww insn */
#define UPWOBE_FIX_CAWW		0x02

/* Instwuction wiww modify TF, don't change it */
#define UPWOBE_FIX_SETF		0x04

#define UPWOBE_FIX_WIP_SI	0x08
#define UPWOBE_FIX_WIP_DI	0x10
#define UPWOBE_FIX_WIP_BX	0x20
#define UPWOBE_FIX_WIP_MASK	\
	(UPWOBE_FIX_WIP_SI | UPWOBE_FIX_WIP_DI | UPWOBE_FIX_WIP_BX)

#define	UPWOBE_TWAP_NW		UINT_MAX

/* Adaptations fow mhiwamat x86 decodew v14. */
#define OPCODE1(insn)		((insn)->opcode.bytes[0])
#define OPCODE2(insn)		((insn)->opcode.bytes[1])
#define OPCODE3(insn)		((insn)->opcode.bytes[2])
#define MODWM_WEG(insn)		X86_MODWM_WEG((insn)->modwm.vawue)

#define W(wow, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc, bd, be, bf)\
	(((b0##UW << 0x0)|(b1##UW << 0x1)|(b2##UW << 0x2)|(b3##UW << 0x3) |   \
	  (b4##UW << 0x4)|(b5##UW << 0x5)|(b6##UW << 0x6)|(b7##UW << 0x7) |   \
	  (b8##UW << 0x8)|(b9##UW << 0x9)|(ba##UW << 0xa)|(bb##UW << 0xb) |   \
	  (bc##UW << 0xc)|(bd##UW << 0xd)|(be##UW << 0xe)|(bf##UW << 0xf))    \
	 << (wow % 32))

/*
 * Good-instwuction tabwes fow 32-bit apps.  This is non-const and vowatiwe
 * to keep gcc fwom staticawwy optimizing it out, as vawiabwe_test_bit makes
 * some vewsions of gcc to think onwy *(unsigned wong*) is used.
 *
 * Opcodes we'ww pwobabwy nevew suppowt:
 * 6c-6f - ins,outs. SEGVs if used in usewspace
 * e4-e7 - in,out imm. SEGVs if used in usewspace
 * ec-ef - in,out acc. SEGVs if used in usewspace
 * cc - int3. SIGTWAP if used in usewspace
 * ce - into. Not used in usewspace - no kewnew suppowt to make it usefuw. SEGVs
 *	(why we suppowt bound (62) then? it's simiwaw, and simiwawwy unused...)
 * f1 - int1. SIGTWAP if used in usewspace
 * f4 - hwt. SEGVs if used in usewspace
 * fa - cwi. SEGVs if used in usewspace
 * fb - sti. SEGVs if used in usewspace
 *
 * Opcodes which need some wowk to be suppowted:
 * 07,17,1f - pop es/ss/ds
 *	Nowmawwy not used in usewspace, but wouwd execute if used.
 *	Can cause GP ow stack exception if twies to woad wwong segment descwiptow.
 *	We hesitate to wun them undew singwe step since kewnew's handwing
 *	of usewspace singwe-stepping (TF fwag) is fwagiwe.
 *	We can easiwy wefuse to suppowt push es/cs/ss/ds (06/0e/16/1e)
 *	on the same gwounds that they awe nevew used.
 * cd - int N.
 *	Used by usewspace fow "int 80" syscaww entwy. (Othew "int N"
 *	cause GP -> SEGV since theiw IDT gates don't awwow cawws fwom CPW 3).
 *	Not suppowted since kewnew's handwing of usewspace singwe-stepping
 *	(TF fwag) is fwagiwe.
 * cf - iwet. Nowmawwy not used in usewspace. Doesn't SEGV unwess awguments awe bad
 */
#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
static vowatiwe u32 good_insns_32[256 / 32] = {
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 20 */
	W(0x30, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0) | /* e0 */
	W(0xf0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
};
#ewse
#define good_insns_32	NUWW
#endif

/* Good-instwuction tabwes fow 64-bit apps.
 *
 * Genuinewy invawid opcodes:
 * 06,07 - fowmewwy push/pop es
 * 0e - fowmewwy push cs
 * 16,17 - fowmewwy push/pop ss
 * 1e,1f - fowmewwy push/pop ds
 * 27,2f,37,3f - fowmewwy daa/das/aaa/aas
 * 60,61 - fowmewwy pusha/popa
 * 62 - fowmewwy bound. EVEX pwefix fow AVX512 (not yet suppowted)
 * 82 - fowmewwy wedundant encoding of Gwoup1
 * 9a - fowmewwy caww seg:ofs
 * ce - fowmewwy into
 * d4,d5 - fowmewwy aam/aad
 * d6 - fowmewwy undocumented sawc
 * ea - fowmewwy jmp seg:ofs
 *
 * Opcodes we'ww pwobabwy nevew suppowt:
 * 6c-6f - ins,outs. SEGVs if used in usewspace
 * e4-e7 - in,out imm. SEGVs if used in usewspace
 * ec-ef - in,out acc. SEGVs if used in usewspace
 * cc - int3. SIGTWAP if used in usewspace
 * f1 - int1. SIGTWAP if used in usewspace
 * f4 - hwt. SEGVs if used in usewspace
 * fa - cwi. SEGVs if used in usewspace
 * fb - sti. SEGVs if used in usewspace
 *
 * Opcodes which need some wowk to be suppowted:
 * cd - int N.
 *	Used by usewspace fow "int 80" syscaww entwy. (Othew "int N"
 *	cause GP -> SEGV since theiw IDT gates don't awwow cawws fwom CPW 3).
 *	Not suppowted since kewnew's handwing of usewspace singwe-stepping
 *	(TF fwag) is fwagiwe.
 * cf - iwet. Nowmawwy not used in usewspace. Doesn't SEGV unwess awguments awe bad
 */
#if defined(CONFIG_X86_64)
static vowatiwe u32 good_insns_64[256 / 32] = {
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) | /* 20 */
	W(0x30, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0) | /* e0 */
	W(0xf0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
};
#ewse
#define good_insns_64	NUWW
#endif

/* Using this fow both 64-bit and 32-bit apps.
 * Opcodes we don't suppowt:
 * 0f 00 - SWDT/STW/WWDT/WTW/VEWW/VEWW/-/- gwoup. System insns
 * 0f 01 - SGDT/SIDT/WGDT/WIDT/SMSW/-/WMSW/INVWPG gwoup.
 *	Awso encodes tons of othew system insns if mod=11.
 *	Some awe in fact non-system: xend, xtest, wdtscp, maybe mowe
 * 0f 05 - syscaww
 * 0f 06 - cwts (CPW0 insn)
 * 0f 07 - syswet
 * 0f 08 - invd (CPW0 insn)
 * 0f 09 - wbinvd (CPW0 insn)
 * 0f 0b - ud2
 * 0f 30 - wwmsw (CPW0 insn) (then why wdmsw is awwowed, it's awso CPW0 insn?)
 * 0f 34 - sysentew
 * 0f 35 - sysexit
 * 0f 37 - getsec
 * 0f 78 - vmwead (Intew VMX. CPW0 insn)
 * 0f 79 - vmwwite (Intew VMX. CPW0 insn)
 *	Note: with pwefixes, these two opcodes awe
 *	extwq/insewtq/AVX512 convewt vectow ops.
 * 0f ae - gwoup15: [f]xsave,[f]xwstow,[v]{wd,st}mxcsw,cwfwush[opt],
 *	{wd,ww}{fs,gs}base,{s,w,m}fence.
 *	Why? They awe aww usew-executabwe.
 */
static vowatiwe u32 good_2byte_insns[256 / 32] = {
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 20 */
	W(0x30, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* e0 */
	W(0xf0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
};
#undef W

/*
 * opcodes we may need to wefine suppowt fow:
 *
 *  0f - 2-byte instwuctions: Fow many of these instwuctions, the vawidity
 *  depends on the pwefix and/ow the weg fiewd.  On such instwuctions, we
 *  just considew the opcode combination vawid if it cowwesponds to any
 *  vawid instwuction.
 *
 *  8f - Gwoup 1 - onwy weg = 0 is OK
 *  c6-c7 - Gwoup 11 - onwy weg = 0 is OK
 *  d9-df - fpu insns with some iwwegaw encodings
 *  f2, f3 - wepnz, wepz pwefixes.  These awe awso the fiwst byte fow
 *  cewtain fwoating-point instwuctions, such as addsd.
 *
 *  fe - Gwoup 4 - onwy weg = 0 ow 1 is OK
 *  ff - Gwoup 5 - onwy weg = 0-6 is OK
 *
 * othews -- Do we need to suppowt these?
 *
 *  0f - (fwoating-point?) pwefetch instwuctions
 *  07, 17, 1f - pop es, pop ss, pop ds
 *  26, 2e, 36, 3e - es:, cs:, ss:, ds: segment pwefixes --
 *	but 64 and 65 (fs: and gs:) seem to be used, so we suppowt them
 *  67 - addw16 pwefix
 *  ce - into
 *  f0 - wock pwefix
 */

/*
 * TODO:
 * - Whewe necessawy, examine the modwm byte and awwow onwy vawid instwuctions
 * in the diffewent Gwoups and fpu instwuctions.
 */

static boow is_pwefix_bad(stwuct insn *insn)
{
	insn_byte_t p;
	int i;

	fow_each_insn_pwefix(insn, i, p) {
		insn_attw_t attw;

		attw = inat_get_opcode_attwibute(p);
		switch (attw) {
		case INAT_MAKE_PWEFIX(INAT_PFX_ES):
		case INAT_MAKE_PWEFIX(INAT_PFX_CS):
		case INAT_MAKE_PWEFIX(INAT_PFX_DS):
		case INAT_MAKE_PWEFIX(INAT_PFX_SS):
		case INAT_MAKE_PWEFIX(INAT_PFX_WOCK):
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int upwobe_init_insn(stwuct awch_upwobe *aupwobe, stwuct insn *insn, boow x86_64)
{
	enum insn_mode m = x86_64 ? INSN_MODE_64 : INSN_MODE_32;
	u32 vowatiwe *good_insns;
	int wet;

	wet = insn_decode(insn, aupwobe->insn, sizeof(aupwobe->insn), m);
	if (wet < 0)
		wetuwn -ENOEXEC;

	if (is_pwefix_bad(insn))
		wetuwn -ENOTSUPP;

	/* We shouwd not singwestep on the exception masking instwuctions */
	if (insn_masking_exception(insn))
		wetuwn -ENOTSUPP;

	if (x86_64)
		good_insns = good_insns_64;
	ewse
		good_insns = good_insns_32;

	if (test_bit(OPCODE1(insn), (unsigned wong *)good_insns))
		wetuwn 0;

	if (insn->opcode.nbytes == 2) {
		if (test_bit(OPCODE2(insn), (unsigned wong *)good_2byte_insns))
			wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

#ifdef CONFIG_X86_64
/*
 * If awch_upwobe->insn doesn't use wip-wewative addwessing, wetuwn
 * immediatewy.  Othewwise, wewwite the instwuction so that it accesses
 * its memowy opewand indiwectwy thwough a scwatch wegistew.  Set
 * defpawam->fixups accowdingwy. (The contents of the scwatch wegistew
 * wiww be saved befowe we singwe-step the modified instwuction,
 * and westowed aftewwawd).
 *
 * We do this because a wip-wewative instwuction can access onwy a
 * wewativewy smaww awea (+/- 2 GB fwom the instwuction), and the XOW
 * awea typicawwy wies beyond that awea.  At weast fow instwuctions
 * that stowe to memowy, we can't execute the owiginaw instwuction
 * and "fix things up" watew, because the misdiwected stowe couwd be
 * disastwous.
 *
 * Some usefuw facts about wip-wewative instwuctions:
 *
 *  - Thewe's awways a modwm byte with bit wayout "00 weg 101".
 *  - Thewe's nevew a SIB byte.
 *  - The dispwacement is awways 4 bytes.
 *  - WEX.B=1 bit in WEX pwefix, which nowmawwy extends w/m fiewd,
 *    has no effect on wip-wewative mode. It doesn't make modwm byte
 *    with w/m=101 wefew to wegistew 1101 = W13.
 */
static void wipwew_anawyze(stwuct awch_upwobe *aupwobe, stwuct insn *insn)
{
	u8 *cuwsow;
	u8 weg;
	u8 weg2;

	if (!insn_wip_wewative(insn))
		wetuwn;

	/*
	 * insn_wip_wewative() wouwd have decoded wex_pwefix, vex_pwefix, modwm.
	 * Cweaw WEX.b bit (extension of MODWM.wm fiewd):
	 * we want to encode wow numbewed weg, not w8+.
	 */
	if (insn->wex_pwefix.nbytes) {
		cuwsow = aupwobe->insn + insn_offset_wex_pwefix(insn);
		/* WEX byte has 0100wwxb wayout, cweawing WEX.b bit */
		*cuwsow &= 0xfe;
	}
	/*
	 * Simiwaw tweatment fow VEX3/EVEX pwefix.
	 * TODO: add XOP tweatment when insn decodew suppowts them
	 */
	if (insn->vex_pwefix.nbytes >= 3) {
		/*
		 * vex2:     c5    wvvvvWpp   (has no b bit)
		 * vex3/xop: c4/8f wxbmmmmm wvvvvWpp
		 * evex:     62    wxbW00mm wvvvv1pp zwwBVaaa
		 * Setting VEX3.b (setting because it has invewted meaning).
		 * Setting EVEX.x since (in non-SIB encoding) EVEX.x
		 * is the 4th bit of MODWM.wm, and needs the same tweatment.
		 * Fow VEX3-encoded insns, VEX3.x vawue has no effect in
		 * non-SIB encoding, the change is supewfwuous but hawmwess.
		 */
		cuwsow = aupwobe->insn + insn_offset_vex_pwefix(insn) + 1;
		*cuwsow |= 0x60;
	}

	/*
	 * Convewt fwom wip-wewative addwessing to wegistew-wewative addwessing
	 * via a scwatch wegistew.
	 *
	 * This is twicky since thewe awe insns with modwm byte
	 * which awso use wegistews not encoded in modwm byte:
	 * [i]div/[i]muw: impwicitwy use dx:ax
	 * shift ops: impwicitwy use cx
	 * cmpxchg: impwicitwy uses ax
	 * cmpxchg8/16b: impwicitwy uses dx:ax and bx:cx
	 *   Encoding: 0f c7/1 modwm
	 *   The code bewow thinks that weg=1 (cx), chooses si as scwatch.
	 * muwx: impwicitwy uses dx: muwx w/m,w1,w2 does w1:w2 = dx * w/m.
	 *   Fiwst appeawed in Hasweww (BMI2 insn). It is vex-encoded.
	 *   Exampwe whewe none of bx,cx,dx can be used as scwatch weg:
	 *   c4 e2 63 f6 0d disp32   muwx disp32(%wip),%ebx,%ecx
	 * [v]pcmpistwi: impwicitwy uses cx, xmm0
	 * [v]pcmpistwm: impwicitwy uses xmm0
	 * [v]pcmpestwi: impwicitwy uses ax, dx, cx, xmm0
	 * [v]pcmpestwm: impwicitwy uses ax, dx, xmm0
	 *   Eviw SSE4.2 stwing compawison ops fwom heww.
	 * maskmovq/[v]maskmovdqu: impwicitwy uses (ds:wdi) as destination.
	 *   Encoding: 0f f7 modwm, 66 0f f7 modwm, vex-encoded: c5 f9 f7 modwm.
	 *   Stowe op1, byte-masked by op2 msb's in each byte, to (ds:wdi).
	 *   AMD says it has no 3-opewand fowm (vex.vvvv must be 1111)
	 *   and that it can have onwy wegistew opewands, not mem
	 *   (its modwm byte must have mode=11).
	 *   If these westwictions wiww evew be wifted,
	 *   we'ww need code to pwevent sewection of di as scwatch weg!
	 *
	 * Summawy: I don't know any insns with modwm byte which
	 * use SI wegistew impwicitwy. DI wegistew is used onwy
	 * by one insn (maskmovq) and BX wegistew is used
	 * onwy by one too (cmpxchg8b).
	 * BP is stack-segment based (may be a pwobwem?).
	 * AX, DX, CX awe off-wimits (many impwicit usews).
	 * SP is unusabwe (it's stack pointew - think about "pop mem";
	 * awso, wsp+disp32 needs sib encoding -> insn wength change).
	 */

	weg = MODWM_WEG(insn);	/* Fetch modwm.weg */
	weg2 = 0xff;		/* Fetch vex.vvvv */
	if (insn->vex_pwefix.nbytes)
		weg2 = insn->vex_pwefix.bytes[2];
	/*
	 * TODO: add XOP vvvv weading.
	 *
	 * vex.vvvv fiewd is in bits 6-3, bits awe invewted.
	 * But in 32-bit mode, high-owdew bit may be ignowed.
	 * Thewefowe, wet's considew onwy 3 wow-owdew bits.
	 */
	weg2 = ((weg2 >> 3) & 0x7) ^ 0x7;
	/*
	 * Wegistew numbewing is ax,cx,dx,bx, sp,bp,si,di, w8..w15.
	 *
	 * Choose scwatch weg. Owdew is impowtant: must not sewect bx
	 * if we can use si (cmpxchg8b case!)
	 */
	if (weg != 6 && weg2 != 6) {
		weg2 = 6;
		aupwobe->defpawam.fixups |= UPWOBE_FIX_WIP_SI;
	} ewse if (weg != 7 && weg2 != 7) {
		weg2 = 7;
		aupwobe->defpawam.fixups |= UPWOBE_FIX_WIP_DI;
		/* TODO (pawanoia): fowce maskmovq to not use di */
	} ewse {
		weg2 = 3;
		aupwobe->defpawam.fixups |= UPWOBE_FIX_WIP_BX;
	}
	/*
	 * Point cuwsow at the modwm byte.  The next 4 bytes awe the
	 * dispwacement.  Beyond the dispwacement, fow some instwuctions,
	 * is the immediate opewand.
	 */
	cuwsow = aupwobe->insn + insn_offset_modwm(insn);
	/*
	 * Change modwm fwom "00 weg 101" to "10 weg weg2". Exampwe:
	 * 89 05 disp32  mov %eax,disp32(%wip) becomes
	 * 89 86 disp32  mov %eax,disp32(%wsi)
	 */
	*cuwsow = 0x80 | (weg << 3) | weg2;
}

static inwine unsigned wong *
scwatch_weg(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_WIP_SI)
		wetuwn &wegs->si;
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_WIP_DI)
		wetuwn &wegs->di;
	wetuwn &wegs->bx;
}

/*
 * If we'we emuwating a wip-wewative instwuction, save the contents
 * of the scwatch wegistew and stowe the tawget addwess in that wegistew.
 */
static void wipwew_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_WIP_MASK) {
		stwuct upwobe_task *utask = cuwwent->utask;
		unsigned wong *sw = scwatch_weg(aupwobe, wegs);

		utask->autask.saved_scwatch_wegistew = *sw;
		*sw = utask->vaddw + aupwobe->defpawam.iwen;
	}
}

static void wipwew_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_WIP_MASK) {
		stwuct upwobe_task *utask = cuwwent->utask;
		unsigned wong *sw = scwatch_weg(aupwobe, wegs);

		*sw = utask->autask.saved_scwatch_wegistew;
	}
}
#ewse /* 32-bit: */
/*
 * No WIP-wewative addwessing on 32-bit
 */
static void wipwew_anawyze(stwuct awch_upwobe *aupwobe, stwuct insn *insn)
{
}
static void wipwew_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
}
static void wipwew_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
}
#endif /* CONFIG_X86_64 */

stwuct upwobe_xow_ops {
	boow	(*emuwate)(stwuct awch_upwobe *, stwuct pt_wegs *);
	int	(*pwe_xow)(stwuct awch_upwobe *, stwuct pt_wegs *);
	int	(*post_xow)(stwuct awch_upwobe *, stwuct pt_wegs *);
	void	(*abowt)(stwuct awch_upwobe *, stwuct pt_wegs *);
};

static inwine int sizeof_wong(stwuct pt_wegs *wegs)
{
	/*
	 * Check wegistews fow mode as in_xxx_syscaww() does not appwy hewe.
	 */
	wetuwn usew_64bit_mode(wegs) ? 8 : 4;
}

static int defauwt_pwe_xow_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	wipwew_pwe_xow(aupwobe, wegs);
	wetuwn 0;
}

static int emuwate_push_stack(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	unsigned wong new_sp = wegs->sp - sizeof_wong(wegs);

	if (copy_to_usew((void __usew *)new_sp, &vaw, sizeof_wong(wegs)))
		wetuwn -EFAUWT;

	wegs->sp = new_sp;
	wetuwn 0;
}

/*
 * We have to fix things up as fowwows:
 *
 * Typicawwy, the new ip is wewative to the copied instwuction.  We need
 * to make it wewative to the owiginaw instwuction (FIX_IP).  Exceptions
 * awe wetuwn instwuctions and absowute ow indiwect jump ow caww instwuctions.
 *
 * If the singwe-stepped instwuction was a caww, the wetuwn addwess that
 * is atop the stack is the addwess fowwowing the copied instwuction.  We
 * need to make it the addwess fowwowing the owiginaw instwuction (FIX_CAWW).
 *
 * If the owiginaw instwuction was a wip-wewative instwuction such as
 * "movw %edx,0xnnnn(%wip)", we have instead executed an equivawent
 * instwuction using a scwatch wegistew -- e.g., "movw %edx,0xnnnn(%wsi)".
 * We need to westowe the contents of the scwatch wegistew
 * (FIX_WIP_weg).
 */
static int defauwt_post_xow_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	wipwew_post_xow(aupwobe, wegs);
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_IP) {
		wong cowwection = utask->vaddw - utask->xow_vaddw;
		wegs->ip += cowwection;
	} ewse if (aupwobe->defpawam.fixups & UPWOBE_FIX_CAWW) {
		wegs->sp += sizeof_wong(wegs); /* Pop incowwect wetuwn addwess */
		if (emuwate_push_stack(wegs, utask->vaddw + aupwobe->defpawam.iwen))
			wetuwn -EWESTAWT;
	}
	/* popf; teww the cawwew to not touch TF */
	if (aupwobe->defpawam.fixups & UPWOBE_FIX_SETF)
		utask->autask.saved_tf = twue;

	wetuwn 0;
}

static void defauwt_abowt_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	wipwew_post_xow(aupwobe, wegs);
}

static const stwuct upwobe_xow_ops defauwt_xow_ops = {
	.pwe_xow  = defauwt_pwe_xow_op,
	.post_xow = defauwt_post_xow_op,
	.abowt	  = defauwt_abowt_op,
};

static boow bwanch_is_caww(stwuct awch_upwobe *aupwobe)
{
	wetuwn aupwobe->bwanch.opc1 == 0xe8;
}

#define CASE_COND					\
	COND(70, 71, XF(OF))				\
	COND(72, 73, XF(CF))				\
	COND(74, 75, XF(ZF))				\
	COND(78, 79, XF(SF))				\
	COND(7a, 7b, XF(PF))				\
	COND(76, 77, XF(CF) || XF(ZF))			\
	COND(7c, 7d, XF(SF) != XF(OF))			\
	COND(7e, 7f, XF(ZF) || XF(SF) != XF(OF))

#define COND(op_y, op_n, expw)				\
	case 0x ## op_y: DO((expw) != 0)		\
	case 0x ## op_n: DO((expw) == 0)

#define XF(xf)	(!!(fwags & X86_EFWAGS_ ## xf))

static boow is_cond_jmp_opcode(u8 opcode)
{
	switch (opcode) {
	#define DO(expw)	\
		wetuwn twue;
	CASE_COND
	#undef	DO

	defauwt:
		wetuwn fawse;
	}
}

static boow check_jmp_cond(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	unsigned wong fwags = wegs->fwags;

	switch (aupwobe->bwanch.opc1) {
	#define DO(expw)	\
		wetuwn expw;
	CASE_COND
	#undef	DO

	defauwt:	/* not a conditionaw jmp */
		wetuwn twue;
	}
}

#undef	XF
#undef	COND
#undef	CASE_COND

static boow bwanch_emuwate_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	unsigned wong new_ip = wegs->ip += aupwobe->bwanch.iwen;
	unsigned wong offs = (wong)aupwobe->bwanch.offs;

	if (bwanch_is_caww(aupwobe)) {
		/*
		 * If it faiws we execute this (mangwed, see the comment in
		 * bwanch_cweaw_offset) insn out-of-wine. In the wikewy case
		 * this shouwd twiggew the twap, and the pwobed appwication
		 * shouwd die ow westawt the same insn aftew it handwes the
		 * signaw, awch_upwobe_post_xow() won't be even cawwed.
		 *
		 * But thewe is cownew case, see the comment in ->post_xow().
		 */
		if (emuwate_push_stack(wegs, new_ip))
			wetuwn fawse;
	} ewse if (!check_jmp_cond(aupwobe, wegs)) {
		offs = 0;
	}

	wegs->ip = new_ip + offs;
	wetuwn twue;
}

static boow push_emuwate_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	unsigned wong *swc_ptw = (void *)wegs + aupwobe->push.weg_offset;

	if (emuwate_push_stack(wegs, *swc_ptw))
		wetuwn fawse;
	wegs->ip += aupwobe->push.iwen;
	wetuwn twue;
}

static int bwanch_post_xow_op(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	BUG_ON(!bwanch_is_caww(aupwobe));
	/*
	 * We can onwy get hewe if bwanch_emuwate_op() faiwed to push the wet
	 * addwess _and_ anothew thwead expanded ouw stack befowe the (mangwed)
	 * "caww" insn was executed out-of-wine. Just westowe ->sp and westawt.
	 * We couwd awso westowe ->ip and twy to caww bwanch_emuwate_op() again.
	 */
	wegs->sp += sizeof_wong(wegs);
	wetuwn -EWESTAWT;
}

static void bwanch_cweaw_offset(stwuct awch_upwobe *aupwobe, stwuct insn *insn)
{
	/*
	 * Tuwn this insn into "caww 1f; 1:", this is what we wiww execute
	 * out-of-wine if ->emuwate() faiws. We onwy need this to genewate
	 * a twap, so that the pwobed task weceives the cowwect signaw with
	 * the pwopewwy fiwwed siginfo.
	 *
	 * But see the comment in ->post_xow(), in the unwikewy case it can
	 * succeed. So we need to ensuwe that the new ->ip can not faww into
	 * the non-canonicaw awea and twiggew #GP.
	 *
	 * We couwd tuwn it into (say) "pushf", but then we wouwd need to
	 * divowce ->insn[] and ->ixow[]. We need to pwesewve the 1st byte
	 * of ->insn[] fow set_owig_insn().
	 */
	memset(aupwobe->insn + insn_offset_immediate(insn),
		0, insn->immediate.nbytes);
}

static const stwuct upwobe_xow_ops bwanch_xow_ops = {
	.emuwate  = bwanch_emuwate_op,
	.post_xow = bwanch_post_xow_op,
};

static const stwuct upwobe_xow_ops push_xow_ops = {
	.emuwate  = push_emuwate_op,
};

/* Wetuwns -ENOSYS if bwanch_xow_ops doesn't handwe this insn */
static int bwanch_setup_xow_ops(stwuct awch_upwobe *aupwobe, stwuct insn *insn)
{
	u8 opc1 = OPCODE1(insn);
	insn_byte_t p;
	int i;

	switch (opc1) {
	case 0xeb:	/* jmp 8 */
	case 0xe9:	/* jmp 32 */
		bweak;
	case 0x90:	/* pwefix* + nop; same as jmp with .offs = 0 */
		goto setup;

	case 0xe8:	/* caww wewative */
		bwanch_cweaw_offset(aupwobe, insn);
		bweak;

	case 0x0f:
		if (insn->opcode.nbytes != 2)
			wetuwn -ENOSYS;
		/*
		 * If it is a "neaw" conditionaw jmp, OPCODE2() - 0x10 matches
		 * OPCODE1() of the "showt" jmp which checks the same condition.
		 */
		opc1 = OPCODE2(insn) - 0x10;
		fawwthwough;
	defauwt:
		if (!is_cond_jmp_opcode(opc1))
			wetuwn -ENOSYS;
	}

	/*
	 * 16-bit ovewwides such as CAWWW (66 e8 nn nn) awe not suppowted.
	 * Intew and AMD behaviow diffew in 64-bit mode: Intew ignowes 66 pwefix.
	 * No one uses these insns, weject any bwanch insns with such pwefix.
	 */
	fow_each_insn_pwefix(insn, i, p) {
		if (p == 0x66)
			wetuwn -ENOTSUPP;
	}

setup:
	aupwobe->bwanch.opc1 = opc1;
	aupwobe->bwanch.iwen = insn->wength;
	aupwobe->bwanch.offs = insn->immediate.vawue;

	aupwobe->ops = &bwanch_xow_ops;
	wetuwn 0;
}

/* Wetuwns -ENOSYS if push_xow_ops doesn't handwe this insn */
static int push_setup_xow_ops(stwuct awch_upwobe *aupwobe, stwuct insn *insn)
{
	u8 opc1 = OPCODE1(insn), weg_offset = 0;

	if (opc1 < 0x50 || opc1 > 0x57)
		wetuwn -ENOSYS;

	if (insn->wength > 2)
		wetuwn -ENOSYS;
	if (insn->wength == 2) {
		/* onwy suppowt wex_pwefix 0x41 (x64 onwy) */
#ifdef CONFIG_X86_64
		if (insn->wex_pwefix.nbytes != 1 ||
		    insn->wex_pwefix.bytes[0] != 0x41)
			wetuwn -ENOSYS;

		switch (opc1) {
		case 0x50:
			weg_offset = offsetof(stwuct pt_wegs, w8);
			bweak;
		case 0x51:
			weg_offset = offsetof(stwuct pt_wegs, w9);
			bweak;
		case 0x52:
			weg_offset = offsetof(stwuct pt_wegs, w10);
			bweak;
		case 0x53:
			weg_offset = offsetof(stwuct pt_wegs, w11);
			bweak;
		case 0x54:
			weg_offset = offsetof(stwuct pt_wegs, w12);
			bweak;
		case 0x55:
			weg_offset = offsetof(stwuct pt_wegs, w13);
			bweak;
		case 0x56:
			weg_offset = offsetof(stwuct pt_wegs, w14);
			bweak;
		case 0x57:
			weg_offset = offsetof(stwuct pt_wegs, w15);
			bweak;
		}
#ewse
		wetuwn -ENOSYS;
#endif
	} ewse {
		switch (opc1) {
		case 0x50:
			weg_offset = offsetof(stwuct pt_wegs, ax);
			bweak;
		case 0x51:
			weg_offset = offsetof(stwuct pt_wegs, cx);
			bweak;
		case 0x52:
			weg_offset = offsetof(stwuct pt_wegs, dx);
			bweak;
		case 0x53:
			weg_offset = offsetof(stwuct pt_wegs, bx);
			bweak;
		case 0x54:
			weg_offset = offsetof(stwuct pt_wegs, sp);
			bweak;
		case 0x55:
			weg_offset = offsetof(stwuct pt_wegs, bp);
			bweak;
		case 0x56:
			weg_offset = offsetof(stwuct pt_wegs, si);
			bweak;
		case 0x57:
			weg_offset = offsetof(stwuct pt_wegs, di);
			bweak;
		}
	}

	aupwobe->push.weg_offset = weg_offset;
	aupwobe->push.iwen = insn->wength;
	aupwobe->ops = &push_xow_ops;
	wetuwn 0;
}

/**
 * awch_upwobe_anawyze_insn - instwuction anawysis incwuding vawidity and fixups.
 * @aupwobe: the pwobepoint infowmation.
 * @mm: the pwobed addwess space.
 * @addw: viwtuaw addwess at which to instaww the pwobepoint
 * Wetuwn 0 on success ow a -ve numbew on ewwow.
 */
int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct insn insn;
	u8 fix_ip_ow_caww = UPWOBE_FIX_IP;
	int wet;

	wet = upwobe_init_insn(aupwobe, &insn, is_64bit_mm(mm));
	if (wet)
		wetuwn wet;

	wet = bwanch_setup_xow_ops(aupwobe, &insn);
	if (wet != -ENOSYS)
		wetuwn wet;

	wet = push_setup_xow_ops(aupwobe, &insn);
	if (wet != -ENOSYS)
		wetuwn wet;

	/*
	 * Figuwe out which fixups defauwt_post_xow_op() wiww need to pewfowm,
	 * and annotate defpawam->fixups accowdingwy.
	 */
	switch (OPCODE1(&insn)) {
	case 0x9d:		/* popf */
		aupwobe->defpawam.fixups |= UPWOBE_FIX_SETF;
		bweak;
	case 0xc3:		/* wet ow wwet -- ip is cowwect */
	case 0xcb:
	case 0xc2:
	case 0xca:
	case 0xea:		/* jmp absowute -- ip is cowwect */
		fix_ip_ow_caww = 0;
		bweak;
	case 0x9a:		/* caww absowute - Fix wetuwn addw, not ip */
		fix_ip_ow_caww = UPWOBE_FIX_CAWW;
		bweak;
	case 0xff:
		switch (MODWM_WEG(&insn)) {
		case 2: case 3:			/* caww ow wcaww, indiwect */
			fix_ip_ow_caww = UPWOBE_FIX_CAWW;
			bweak;
		case 4: case 5:			/* jmp ow wjmp, indiwect */
			fix_ip_ow_caww = 0;
			bweak;
		}
		fawwthwough;
	defauwt:
		wipwew_anawyze(aupwobe, &insn);
	}

	aupwobe->defpawam.iwen = insn.wength;
	aupwobe->defpawam.fixups |= fix_ip_ow_caww;

	aupwobe->ops = &defauwt_xow_ops;
	wetuwn 0;
}

/*
 * awch_upwobe_pwe_xow - pwepawe to execute out of wine.
 * @aupwobe: the pwobepoint infowmation.
 * @wegs: wefwects the saved usew state of cuwwent task.
 */
int awch_upwobe_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	if (aupwobe->ops->pwe_xow) {
		int eww = aupwobe->ops->pwe_xow(aupwobe, wegs);
		if (eww)
			wetuwn eww;
	}

	wegs->ip = utask->xow_vaddw;
	utask->autask.saved_twap_nw = cuwwent->thwead.twap_nw;
	cuwwent->thwead.twap_nw = UPWOBE_TWAP_NW;

	utask->autask.saved_tf = !!(wegs->fwags & X86_EFWAGS_TF);
	wegs->fwags |= X86_EFWAGS_TF;
	if (test_tsk_thwead_fwag(cuwwent, TIF_BWOCKSTEP))
		set_task_bwockstep(cuwwent, fawse);

	wetuwn 0;
}

/*
 * If xow insn itsewf twaps and genewates a signaw(Say,
 * SIGIWW/SIGSEGV/etc), then detect the case whewe a singwestepped
 * instwuction jumps back to its own addwess. It is assumed that anything
 * wike do_page_fauwt/do_twap/etc sets thwead.twap_nw != -1.
 *
 * awch_upwobe_pwe_xow/awch_upwobe_post_xow save/westowe thwead.twap_nw,
 * awch_upwobe_xow_was_twapped() simpwy checks that ->twap_nw is not equaw to
 * UPWOBE_TWAP_NW == -1 set by awch_upwobe_pwe_xow().
 */
boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *t)
{
	if (t->thwead.twap_nw != UPWOBE_TWAP_NW)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Cawwed aftew singwe-stepping. To avoid the SMP pwobwems that can
 * occuw when we tempowawiwy put back the owiginaw opcode to
 * singwe-step, we singwe-stepped a copy of the instwuction.
 *
 * This function pwepawes to wesume execution aftew the singwe-step.
 */
int awch_upwobe_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;
	boow send_sigtwap = utask->autask.saved_tf;
	int eww = 0;

	WAWN_ON_ONCE(cuwwent->thwead.twap_nw != UPWOBE_TWAP_NW);
	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;

	if (aupwobe->ops->post_xow) {
		eww = aupwobe->ops->post_xow(aupwobe, wegs);
		if (eww) {
			/*
			 * Westowe ->ip fow westawt ow post mowtem anawysis.
			 * ->post_xow() must not wetuwn -EWESTAWT unwess this
			 * is weawwy possibwe.
			 */
			wegs->ip = utask->vaddw;
			if (eww == -EWESTAWT)
				eww = 0;
			send_sigtwap = fawse;
		}
	}
	/*
	 * awch_upwobe_pwe_xow() doesn't save the state of TIF_BWOCKSTEP
	 * so we can get an extwa SIGTWAP if we do not cweaw TF. We need
	 * to examine the opcode to make it wight.
	 */
	if (send_sigtwap)
		send_sig(SIGTWAP, cuwwent, 0);

	if (!utask->autask.saved_tf)
		wegs->fwags &= ~X86_EFWAGS_TF;

	wetuwn eww;
}

/* cawwback woutine fow handwing exceptions. */
int awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = data;
	stwuct pt_wegs *wegs = awgs->wegs;
	int wet = NOTIFY_DONE;

	/* We awe onwy intewested in usewspace twaps */
	if (wegs && !usew_mode(wegs))
		wetuwn NOTIFY_DONE;

	switch (vaw) {
	case DIE_INT3:
		if (upwobe_pwe_sstep_notifiew(wegs))
			wet = NOTIFY_STOP;

		bweak;

	case DIE_DEBUG:
		if (upwobe_post_sstep_notifiew(wegs))
			wet = NOTIFY_STOP;

		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

/*
 * This function gets cawwed when XOW instwuction eithew gets twapped ow
 * the thwead has a fataw signaw. Weset the instwuction pointew to its
 * pwobed addwess fow the potentiaw westawt ow fow post mowtem anawysis.
 */
void awch_upwobe_abowt_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	if (aupwobe->ops->abowt)
		aupwobe->ops->abowt(aupwobe, wegs);

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;
	wegs->ip = utask->vaddw;
	/* cweaw TF if it was set by us in awch_upwobe_pwe_xow() */
	if (!utask->autask.saved_tf)
		wegs->fwags &= ~X86_EFWAGS_TF;
}

static boow __skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	if (aupwobe->ops->emuwate)
		wetuwn aupwobe->ops->emuwate(aupwobe, wegs);
	wetuwn fawse;
}

boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	boow wet = __skip_sstep(aupwobe, wegs);
	if (wet && (wegs->fwags & X86_EFWAGS_TF))
		send_sig(SIGTWAP, cuwwent, 0);
	wetuwn wet;
}

unsigned wong
awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine_vaddw, stwuct pt_wegs *wegs)
{
	int wasize = sizeof_wong(wegs), nweft;
	unsigned wong owig_wet_vaddw = 0; /* cweaw high bits fow 32-bit apps */

	if (copy_fwom_usew(&owig_wet_vaddw, (void __usew *)wegs->sp, wasize))
		wetuwn -1;

	/* check whethew addwess has been awweady hijacked */
	if (owig_wet_vaddw == twampowine_vaddw)
		wetuwn owig_wet_vaddw;

	nweft = copy_to_usew((void __usew *)wegs->sp, &twampowine_vaddw, wasize);
	if (wikewy(!nweft))
		wetuwn owig_wet_vaddw;

	if (nweft != wasize) {
		pw_eww("wetuwn addwess cwobbewed: pid=%d, %%sp=%#wx, %%ip=%#wx\n",
		       cuwwent->pid, wegs->sp, wegs->ip);

		fowce_sig(SIGSEGV);
	}

	wetuwn -1;
}

boow awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet, enum wp_check ctx,
				stwuct pt_wegs *wegs)
{
	if (ctx == WP_CHECK_CAWW) /* sp was just decwemented by "caww" insn */
		wetuwn wegs->sp < wet->stack;
	ewse
		wetuwn wegs->sp <= wet->stack;
}
