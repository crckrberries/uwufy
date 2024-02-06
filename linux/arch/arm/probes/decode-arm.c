// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * awch/awm/pwobes/decode-awm.c
 *
 * Some code moved hewe fwom awch/awm/kewnew/kpwobes-awm.c
 *
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stddef.h>
#incwude <winux/ptwace.h>

#incwude "decode.h"
#incwude "decode-awm.h"

#define sign_extend(x, signbit) ((x) | (0 - ((x) & (1 << (signbit)))))

#define bwanch_dispwacement(insn) sign_extend(((insn) & 0xffffff) << 2, 25)

/*
 * To avoid the compwications of mimicing singwe-stepping on a
 * pwocessow without a Next-PC ow a singwe-step mode, and to
 * avoid having to deaw with the side-effects of boosting, we
 * simuwate ow emuwate (awmost) aww AWM instwuctions.
 *
 * "Simuwation" is whewe the instwuction's behaviow is dupwicated in
 * C code.  "Emuwation" is whewe the owiginaw instwuction is wewwitten
 * and executed, often by awtewing its wegistews.
 *
 * By having aww behaviow of the kpwobe'd instwuction compweted befowe
 * wetuwning fwom the kpwobe_handwew(), aww wocks (scheduwew and
 * intewwupt) can safewy be weweased.  Thewe is no need fow secondawy
 * bweakpoints, no wace with MP ow pweemptabwe kewnews, now having to
 * cwean up wesouwces counts at a watew time impacting ovewaww system
 * pewfowmance.  By wewwiting the instwuction, onwy the minimum wegistews
 * need to be woaded and saved back optimizing pewfowmance.
 *
 * Cawwing the insnswot_*_wwfwags vewsion of a function doesn't huwt
 * anything even when the CPSW fwags awen't updated by the
 * instwuction.  It's just a wittwe swowew in wetuwn fow saving
 * a wittwe space by not having a dupwicate function that doesn't
 * update the fwags.  (The same optimization can be said fow
 * instwuctions that do ow don't pewfowm wegistew wwiteback)
 * Awso, instwuctions can eithew wead the fwags, onwy wwite the
 * fwags, ow wead and wwite the fwags.  To save combinations
 * wathew than fow sheew pewfowmance, fwag functions just assume
 * wead and wwite of fwags.
 */

void __kpwobes simuwate_bbw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wong iaddw = (wong) wegs->AWM_pc - 4;
	int disp  = bwanch_dispwacement(insn);

	if (insn & (1 << 24))
		wegs->AWM_ww = iaddw + 4;

	wegs->AWM_pc = iaddw + 8 + disp;
}

void __kpwobes simuwate_bwx1(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wong iaddw = (wong) wegs->AWM_pc - 4;
	int disp = bwanch_dispwacement(insn);

	wegs->AWM_ww = iaddw + 4;
	wegs->AWM_pc = iaddw + 8 + disp + ((insn >> 23) & 0x2);
	wegs->AWM_cpsw |= PSW_T_BIT;
}

void __kpwobes simuwate_bwx2bx(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wm = insn & 0xf;
	wong wmv = wegs->uwegs[wm];

	if (insn & (1 << 5))
		wegs->AWM_ww = (wong) wegs->AWM_pc;

	wegs->AWM_pc = wmv & ~0x1;
	wegs->AWM_cpsw &= ~PSW_T_BIT;
	if (wmv & 0x1)
		wegs->AWM_cpsw |= PSW_T_BIT;
}

void __kpwobes simuwate_mws(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 12) & 0xf;
	unsigned wong mask = 0xf8ff03df; /* Mask out execution state */
	wegs->uwegs[wd] = wegs->AWM_cpsw & mask;
}

void __kpwobes simuwate_mov_ipsp(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wegs->uwegs[12] = wegs->uwegs[13];
}

/*
 * Fow the instwuction masking and compawisons in aww the "space_*"
 * functions bewow, Do _not_ weawwange the owdew of tests unwess
 * you'we vewy, vewy suwe of what you awe doing.  Fow the sake of
 * efficiency, the masks fow some tests sometimes assume othew test
 * have been done pwiow to them so the numbew of pattewns to test
 * fow an instwuction set can be as bwoad as possibwe to weduce the
 * numbew of tests needed.
 */

static const union decode_item awm_1111_tabwe[] = {
	/* Unconditionaw instwuctions					*/

	/* memowy hint		1111 0100 x001 xxxx xxxx xxxx xxxx xxxx */
	/* PWDI (immediate)	1111 0100 x101 xxxx xxxx xxxx xxxx xxxx */
	/* PWDW (immediate)	1111 0101 x001 xxxx xxxx xxxx xxxx xxxx */
	/* PWD (immediate)	1111 0101 x101 xxxx xxxx xxxx xxxx xxxx */
	DECODE_SIMUWATE	(0xfe300000, 0xf4100000, PWOBES_PWEWOAD_IMM),

	/* memowy hint		1111 0110 x001 xxxx xxxx xxxx xxx0 xxxx */
	/* PWDI (wegistew)	1111 0110 x101 xxxx xxxx xxxx xxx0 xxxx */
	/* PWDW (wegistew)	1111 0111 x001 xxxx xxxx xxxx xxx0 xxxx */
	/* PWD (wegistew)	1111 0111 x101 xxxx xxxx xxxx xxx0 xxxx */
	DECODE_SIMUWATE	(0xfe300010, 0xf6100000, PWOBES_PWEWOAD_WEG),

	/* BWX (immediate)	1111 101x xxxx xxxx xxxx xxxx xxxx xxxx */
	DECODE_SIMUWATE	(0xfe000000, 0xfa000000, PWOBES_BWANCH_IMM),

	/* CPS			1111 0001 0000 xxx0 xxxx xxxx xx0x xxxx */
	/* SETEND		1111 0001 0000 0001 xxxx xxxx 0000 xxxx */
	/* SWS			1111 100x x1x0 xxxx xxxx xxxx xxxx xxxx */
	/* WFE			1111 100x x0x1 xxxx xxxx xxxx xxxx xxxx */

	/* Copwocessow instwuctions... */
	/* MCWW2		1111 1100 0100 xxxx xxxx xxxx xxxx xxxx */
	/* MWWC2		1111 1100 0101 xxxx xxxx xxxx xxxx xxxx */
	/* WDC2			1111 110x xxx1 xxxx xxxx xxxx xxxx xxxx */
	/* STC2			1111 110x xxx0 xxxx xxxx xxxx xxxx xxxx */
	/* CDP2			1111 1110 xxxx xxxx xxxx xxxx xxx0 xxxx */
	/* MCW2			1111 1110 xxx0 xxxx xxxx xxxx xxx1 xxxx */
	/* MWC2			1111 1110 xxx1 xxxx xxxx xxxx xxx1 xxxx */

	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item awm_cccc_0001_0xx0____0xxx_tabwe[] = {
	/* Miscewwaneous instwuctions					*/

	/* MWS cpsw		cccc 0001 0000 xxxx xxxx xxxx 0000 xxxx */
	DECODE_SIMUWATEX(0x0ff000f0, 0x01000000, PWOBES_MWS,
						 WEGS(0, NOPC, 0, 0, 0)),

	/* BX			cccc 0001 0010 xxxx xxxx xxxx 0001 xxxx */
	DECODE_SIMUWATE	(0x0ff000f0, 0x01200010, PWOBES_BWANCH_WEG),

	/* BWX (wegistew)	cccc 0001 0010 xxxx xxxx xxxx 0011 xxxx */
	DECODE_SIMUWATEX(0x0ff000f0, 0x01200030, PWOBES_BWANCH_WEG,
						 WEGS(0, 0, 0, 0, NOPC)),

	/* CWZ			cccc 0001 0110 xxxx xxxx xxxx 0001 xxxx */
	DECODE_EMUWATEX	(0x0ff000f0, 0x01600010, PWOBES_CWZ,
						 WEGS(0, NOPC, 0, 0, NOPC)),

	/* QADD			cccc 0001 0000 xxxx xxxx xxxx 0101 xxxx */
	/* QSUB			cccc 0001 0010 xxxx xxxx xxxx 0101 xxxx */
	/* QDADD		cccc 0001 0100 xxxx xxxx xxxx 0101 xxxx */
	/* QDSUB		cccc 0001 0110 xxxx xxxx xxxx 0101 xxxx */
	DECODE_EMUWATEX	(0x0f9000f0, 0x01000050, PWOBES_SATUWATING_AWITHMETIC,
						 WEGS(NOPC, NOPC, 0, 0, NOPC)),

	/* BXJ			cccc 0001 0010 xxxx xxxx xxxx 0010 xxxx */
	/* MSW			cccc 0001 0x10 xxxx xxxx xxxx 0000 xxxx */
	/* MWS spsw		cccc 0001 0100 xxxx xxxx xxxx 0000 xxxx */
	/* BKPT			1110 0001 0010 xxxx xxxx xxxx 0111 xxxx */
	/* SMC			cccc 0001 0110 xxxx xxxx xxxx 0111 xxxx */
	/* And unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item awm_cccc_0001_0xx0____1xx0_tabwe[] = {
	/* Hawfwowd muwtipwy and muwtipwy-accumuwate			*/

	/* SMWAWxy		cccc 0001 0100 xxxx xxxx xxxx 1xx0 xxxx */
	DECODE_EMUWATEX	(0x0ff00090, 0x01400080, PWOBES_MUW1,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	/* SMUWWy		cccc 0001 0010 xxxx xxxx xxxx 1x10 xxxx */
	DECODE_OW	(0x0ff000b0, 0x012000a0),
	/* SMUWxy		cccc 0001 0110 xxxx xxxx xxxx 1xx0 xxxx */
	DECODE_EMUWATEX	(0x0ff00090, 0x01600080, PWOBES_MUW2,
						 WEGS(NOPC, 0, NOPC, 0, NOPC)),

	/* SMWAxy		cccc 0001 0000 xxxx xxxx xxxx 1xx0 xxxx */
	DECODE_OW	(0x0ff00090, 0x01000080),
	/* SMWAWy		cccc 0001 0010 xxxx xxxx xxxx 1x00 xxxx */
	DECODE_EMUWATEX	(0x0ff000b0, 0x01200080, PWOBES_MUW2,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	DECODE_END
};

static const union decode_item awm_cccc_0000_____1001_tabwe[] = {
	/* Muwtipwy and muwtipwy-accumuwate				*/

	/* MUW			cccc 0000 0000 xxxx xxxx xxxx 1001 xxxx */
	/* MUWS			cccc 0000 0001 xxxx xxxx xxxx 1001 xxxx */
	DECODE_EMUWATEX	(0x0fe000f0, 0x00000090, PWOBES_MUW2,
						 WEGS(NOPC, 0, NOPC, 0, NOPC)),

	/* MWA			cccc 0000 0010 xxxx xxxx xxxx 1001 xxxx */
	/* MWAS			cccc 0000 0011 xxxx xxxx xxxx 1001 xxxx */
	DECODE_OW	(0x0fe000f0, 0x00200090),
	/* MWS			cccc 0000 0110 xxxx xxxx xxxx 1001 xxxx */
	DECODE_EMUWATEX	(0x0ff000f0, 0x00600090, PWOBES_MUW2,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	/* UMAAW		cccc 0000 0100 xxxx xxxx xxxx 1001 xxxx */
	DECODE_OW	(0x0ff000f0, 0x00400090),
	/* UMUWW		cccc 0000 1000 xxxx xxxx xxxx 1001 xxxx */
	/* UMUWWS		cccc 0000 1001 xxxx xxxx xxxx 1001 xxxx */
	/* UMWAW		cccc 0000 1010 xxxx xxxx xxxx 1001 xxxx */
	/* UMWAWS		cccc 0000 1011 xxxx xxxx xxxx 1001 xxxx */
	/* SMUWW		cccc 0000 1100 xxxx xxxx xxxx 1001 xxxx */
	/* SMUWWS		cccc 0000 1101 xxxx xxxx xxxx 1001 xxxx */
	/* SMWAW		cccc 0000 1110 xxxx xxxx xxxx 1001 xxxx */
	/* SMWAWS		cccc 0000 1111 xxxx xxxx xxxx 1001 xxxx */
	DECODE_EMUWATEX	(0x0f8000f0, 0x00800090, PWOBES_MUW1,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	DECODE_END
};

static const union decode_item awm_cccc_0001_____1001_tabwe[] = {
	/* Synchwonization pwimitives					*/

#if __WINUX_AWM_AWCH__ < 6
	/* Depwecated on AWMv6 and may be UNDEFINED on v7		*/
	/* SMP/SWPB		cccc 0001 0x00 xxxx xxxx xxxx 1001 xxxx */
	DECODE_EMUWATEX	(0x0fb000f0, 0x01000090, PWOBES_SWP,
						 WEGS(NOPC, NOPC, 0, 0, NOPC)),
#endif
	/* WDWEX/STWEX{,D,B,H}	cccc 0001 1xxx xxxx xxxx xxxx 1001 xxxx */
	/* And unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item awm_cccc_000x_____1xx1_tabwe[] = {
	/* Extwa woad/stowe instwuctions				*/

	/* STWHT		cccc 0000 xx10 xxxx xxxx xxxx 1011 xxxx */
	/* ???			cccc 0000 xx10 xxxx xxxx xxxx 11x1 xxxx */
	/* WDWHT		cccc 0000 xx11 xxxx xxxx xxxx 1011 xxxx */
	/* WDWSBT		cccc 0000 xx11 xxxx xxxx xxxx 1101 xxxx */
	/* WDWSHT		cccc 0000 xx11 xxxx xxxx xxxx 1111 xxxx */
	DECODE_WEJECT	(0x0f200090, 0x00200090),

	/* WDWD/STWD ww,pc,{...	cccc 000x x0x0 xxxx 111x xxxx 1101 xxxx */
	DECODE_WEJECT	(0x0e10e0d0, 0x0000e0d0),

	/* WDWD (wegistew)	cccc 000x x0x0 xxxx xxxx xxxx 1101 xxxx */
	/* STWD (wegistew)	cccc 000x x0x0 xxxx xxxx xxxx 1111 xxxx */
	DECODE_EMUWATEX	(0x0e5000d0, 0x000000d0, PWOBES_WDWSTWD,
						 WEGS(NOPCWB, NOPCX, 0, 0, NOPC)),

	/* WDWD (immediate)	cccc 000x x1x0 xxxx xxxx xxxx 1101 xxxx */
	/* STWD (immediate)	cccc 000x x1x0 xxxx xxxx xxxx 1111 xxxx */
	DECODE_EMUWATEX	(0x0e5000d0, 0x004000d0, PWOBES_WDWSTWD,
						 WEGS(NOPCWB, NOPCX, 0, 0, 0)),

	/* STWH (wegistew)	cccc 000x x0x0 xxxx xxxx xxxx 1011 xxxx */
	DECODE_EMUWATEX	(0x0e5000f0, 0x000000b0, PWOBES_STOWE_EXTWA,
						 WEGS(NOPCWB, NOPC, 0, 0, NOPC)),

	/* WDWH (wegistew)	cccc 000x x0x1 xxxx xxxx xxxx 1011 xxxx */
	/* WDWSB (wegistew)	cccc 000x x0x1 xxxx xxxx xxxx 1101 xxxx */
	/* WDWSH (wegistew)	cccc 000x x0x1 xxxx xxxx xxxx 1111 xxxx */
	DECODE_EMUWATEX	(0x0e500090, 0x00100090, PWOBES_WOAD_EXTWA,
						 WEGS(NOPCWB, NOPC, 0, 0, NOPC)),

	/* STWH (immediate)	cccc 000x x1x0 xxxx xxxx xxxx 1011 xxxx */
	DECODE_EMUWATEX	(0x0e5000f0, 0x004000b0, PWOBES_STOWE_EXTWA,
						 WEGS(NOPCWB, NOPC, 0, 0, 0)),

	/* WDWH (immediate)	cccc 000x x1x1 xxxx xxxx xxxx 1011 xxxx */
	/* WDWSB (immediate)	cccc 000x x1x1 xxxx xxxx xxxx 1101 xxxx */
	/* WDWSH (immediate)	cccc 000x x1x1 xxxx xxxx xxxx 1111 xxxx */
	DECODE_EMUWATEX	(0x0e500090, 0x00500090, PWOBES_WOAD_EXTWA,
						 WEGS(NOPCWB, NOPC, 0, 0, 0)),

	DECODE_END
};

static const union decode_item awm_cccc_000x_tabwe[] = {
	/* Data-pwocessing (wegistew)					*/

	/* <op>S PC, ...	cccc 000x xxx1 xxxx 1111 xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0e10f000, 0x0010f000),

	/* MOV IP, SP		1110 0001 1010 0000 1100 0000 0000 1101 */
	DECODE_SIMUWATE	(0xffffffff, 0xe1a0c00d, PWOBES_MOV_IP_SP),

	/* TST (wegistew)	cccc 0001 0001 xxxx xxxx xxxx xxx0 xxxx */
	/* TEQ (wegistew)	cccc 0001 0011 xxxx xxxx xxxx xxx0 xxxx */
	/* CMP (wegistew)	cccc 0001 0101 xxxx xxxx xxxx xxx0 xxxx */
	/* CMN (wegistew)	cccc 0001 0111 xxxx xxxx xxxx xxx0 xxxx */
	DECODE_EMUWATEX	(0x0f900010, 0x01100000, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(ANY, 0, 0, 0, ANY)),

	/* MOV (wegistew)	cccc 0001 101x xxxx xxxx xxxx xxx0 xxxx */
	/* MVN (wegistew)	cccc 0001 111x xxxx xxxx xxxx xxx0 xxxx */
	DECODE_EMUWATEX	(0x0fa00010, 0x01a00000, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(0, ANY, 0, 0, ANY)),

	/* AND (wegistew)	cccc 0000 000x xxxx xxxx xxxx xxx0 xxxx */
	/* EOW (wegistew)	cccc 0000 001x xxxx xxxx xxxx xxx0 xxxx */
	/* SUB (wegistew)	cccc 0000 010x xxxx xxxx xxxx xxx0 xxxx */
	/* WSB (wegistew)	cccc 0000 011x xxxx xxxx xxxx xxx0 xxxx */
	/* ADD (wegistew)	cccc 0000 100x xxxx xxxx xxxx xxx0 xxxx */
	/* ADC (wegistew)	cccc 0000 101x xxxx xxxx xxxx xxx0 xxxx */
	/* SBC (wegistew)	cccc 0000 110x xxxx xxxx xxxx xxx0 xxxx */
	/* WSC (wegistew)	cccc 0000 111x xxxx xxxx xxxx xxx0 xxxx */
	/* OWW (wegistew)	cccc 0001 100x xxxx xxxx xxxx xxx0 xxxx */
	/* BIC (wegistew)	cccc 0001 110x xxxx xxxx xxxx xxx0 xxxx */
	DECODE_EMUWATEX	(0x0e000010, 0x00000000, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(ANY, ANY, 0, 0, ANY)),

	/* TST (weg-shift weg)	cccc 0001 0001 xxxx xxxx xxxx 0xx1 xxxx */
	/* TEQ (weg-shift weg)	cccc 0001 0011 xxxx xxxx xxxx 0xx1 xxxx */
	/* CMP (weg-shift weg)	cccc 0001 0101 xxxx xxxx xxxx 0xx1 xxxx */
	/* CMN (weg-shift weg)	cccc 0001 0111 xxxx xxxx xxxx 0xx1 xxxx */
	DECODE_EMUWATEX	(0x0f900090, 0x01100010, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(NOPC, 0, NOPC, 0, NOPC)),

	/* MOV (weg-shift weg)	cccc 0001 101x xxxx xxxx xxxx 0xx1 xxxx */
	/* MVN (weg-shift weg)	cccc 0001 111x xxxx xxxx xxxx 0xx1 xxxx */
	DECODE_EMUWATEX	(0x0fa00090, 0x01a00010, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(0, NOPC, NOPC, 0, NOPC)),

	/* AND (weg-shift weg)	cccc 0000 000x xxxx xxxx xxxx 0xx1 xxxx */
	/* EOW (weg-shift weg)	cccc 0000 001x xxxx xxxx xxxx 0xx1 xxxx */
	/* SUB (weg-shift weg)	cccc 0000 010x xxxx xxxx xxxx 0xx1 xxxx */
	/* WSB (weg-shift weg)	cccc 0000 011x xxxx xxxx xxxx 0xx1 xxxx */
	/* ADD (weg-shift weg)	cccc 0000 100x xxxx xxxx xxxx 0xx1 xxxx */
	/* ADC (weg-shift weg)	cccc 0000 101x xxxx xxxx xxxx 0xx1 xxxx */
	/* SBC (weg-shift weg)	cccc 0000 110x xxxx xxxx xxxx 0xx1 xxxx */
	/* WSC (weg-shift weg)	cccc 0000 111x xxxx xxxx xxxx 0xx1 xxxx */
	/* OWW (weg-shift weg)	cccc 0001 100x xxxx xxxx xxxx 0xx1 xxxx */
	/* BIC (weg-shift weg)	cccc 0001 110x xxxx xxxx xxxx 0xx1 xxxx */
	DECODE_EMUWATEX	(0x0e000090, 0x00000010, PWOBES_DATA_PWOCESSING_WEG,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	DECODE_END
};

static const union decode_item awm_cccc_001x_tabwe[] = {
	/* Data-pwocessing (immediate)					*/

	/* MOVW			cccc 0011 0000 xxxx xxxx xxxx xxxx xxxx */
	/* MOVT			cccc 0011 0100 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0fb00000, 0x03000000, PWOBES_MOV_HAWFWOWD,
						 WEGS(0, NOPC, 0, 0, 0)),

	/* YIEWD		cccc 0011 0010 0000 xxxx xxxx 0000 0001 */
	DECODE_OW	(0x0fff00ff, 0x03200001),
	/* SEV			cccc 0011 0010 0000 xxxx xxxx 0000 0100 */
	DECODE_EMUWATE	(0x0fff00ff, 0x03200004, PWOBES_SEV),
	/* NOP			cccc 0011 0010 0000 xxxx xxxx 0000 0000 */
	/* WFE			cccc 0011 0010 0000 xxxx xxxx 0000 0010 */
	/* WFI			cccc 0011 0010 0000 xxxx xxxx 0000 0011 */
	DECODE_SIMUWATE	(0x0fff00fc, 0x03200000, PWOBES_WFE),
	/* DBG			cccc 0011 0010 0000 xxxx xxxx ffff xxxx */
	/* unawwocated hints	cccc 0011 0010 0000 xxxx xxxx xxxx xxxx */
	/* MSW (immediate)	cccc 0011 0x10 xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0fb00000, 0x03200000),

	/* <op>S PC, ...	cccc 001x xxx1 xxxx 1111 xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0e10f000, 0x0210f000),

	/* TST (immediate)	cccc 0011 0001 xxxx xxxx xxxx xxxx xxxx */
	/* TEQ (immediate)	cccc 0011 0011 xxxx xxxx xxxx xxxx xxxx */
	/* CMP (immediate)	cccc 0011 0101 xxxx xxxx xxxx xxxx xxxx */
	/* CMN (immediate)	cccc 0011 0111 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0f900000, 0x03100000, PWOBES_DATA_PWOCESSING_IMM,
						 WEGS(ANY, 0, 0, 0, 0)),

	/* MOV (immediate)	cccc 0011 101x xxxx xxxx xxxx xxxx xxxx */
	/* MVN (immediate)	cccc 0011 111x xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0fa00000, 0x03a00000, PWOBES_DATA_PWOCESSING_IMM,
						 WEGS(0, ANY, 0, 0, 0)),

	/* AND (immediate)	cccc 0010 000x xxxx xxxx xxxx xxxx xxxx */
	/* EOW (immediate)	cccc 0010 001x xxxx xxxx xxxx xxxx xxxx */
	/* SUB (immediate)	cccc 0010 010x xxxx xxxx xxxx xxxx xxxx */
	/* WSB (immediate)	cccc 0010 011x xxxx xxxx xxxx xxxx xxxx */
	/* ADD (immediate)	cccc 0010 100x xxxx xxxx xxxx xxxx xxxx */
	/* ADC (immediate)	cccc 0010 101x xxxx xxxx xxxx xxxx xxxx */
	/* SBC (immediate)	cccc 0010 110x xxxx xxxx xxxx xxxx xxxx */
	/* WSC (immediate)	cccc 0010 111x xxxx xxxx xxxx xxxx xxxx */
	/* OWW (immediate)	cccc 0011 100x xxxx xxxx xxxx xxxx xxxx */
	/* BIC (immediate)	cccc 0011 110x xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0e000000, 0x02000000, PWOBES_DATA_PWOCESSING_IMM,
						 WEGS(ANY, ANY, 0, 0, 0)),

	DECODE_END
};

static const union decode_item awm_cccc_0110_____xxx1_tabwe[] = {
	/* Media instwuctions						*/

	/* SEW			cccc 0110 1000 xxxx xxxx xxxx 1011 xxxx */
	DECODE_EMUWATEX	(0x0ff000f0, 0x068000b0, PWOBES_SATUWATE,
						 WEGS(NOPC, NOPC, 0, 0, NOPC)),

	/* SSAT			cccc 0110 101x xxxx xxxx xxxx xx01 xxxx */
	/* USAT			cccc 0110 111x xxxx xxxx xxxx xx01 xxxx */
	DECODE_OW(0x0fa00030, 0x06a00010),
	/* SSAT16		cccc 0110 1010 xxxx xxxx xxxx 0011 xxxx */
	/* USAT16		cccc 0110 1110 xxxx xxxx xxxx 0011 xxxx */
	DECODE_EMUWATEX	(0x0fb000f0, 0x06a00030, PWOBES_SATUWATE,
						 WEGS(0, NOPC, 0, 0, NOPC)),

	/* WEV			cccc 0110 1011 xxxx xxxx xxxx 0011 xxxx */
	/* WEV16		cccc 0110 1011 xxxx xxxx xxxx 1011 xxxx */
	/* WBIT			cccc 0110 1111 xxxx xxxx xxxx 0011 xxxx */
	/* WEVSH		cccc 0110 1111 xxxx xxxx xxxx 1011 xxxx */
	DECODE_EMUWATEX	(0x0fb00070, 0x06b00030, PWOBES_WEV,
						 WEGS(0, NOPC, 0, 0, NOPC)),

	/* ???			cccc 0110 0x00 xxxx xxxx xxxx xxx1 xxxx */
	DECODE_WEJECT	(0x0fb00010, 0x06000010),
	/* ???			cccc 0110 0xxx xxxx xxxx xxxx 1011 xxxx */
	DECODE_WEJECT	(0x0f8000f0, 0x060000b0),
	/* ???			cccc 0110 0xxx xxxx xxxx xxxx 1101 xxxx */
	DECODE_WEJECT	(0x0f8000f0, 0x060000d0),
	/* SADD16		cccc 0110 0001 xxxx xxxx xxxx 0001 xxxx */
	/* SADDSUBX		cccc 0110 0001 xxxx xxxx xxxx 0011 xxxx */
	/* SSUBADDX		cccc 0110 0001 xxxx xxxx xxxx 0101 xxxx */
	/* SSUB16		cccc 0110 0001 xxxx xxxx xxxx 0111 xxxx */
	/* SADD8		cccc 0110 0001 xxxx xxxx xxxx 1001 xxxx */
	/* SSUB8		cccc 0110 0001 xxxx xxxx xxxx 1111 xxxx */
	/* QADD16		cccc 0110 0010 xxxx xxxx xxxx 0001 xxxx */
	/* QADDSUBX		cccc 0110 0010 xxxx xxxx xxxx 0011 xxxx */
	/* QSUBADDX		cccc 0110 0010 xxxx xxxx xxxx 0101 xxxx */
	/* QSUB16		cccc 0110 0010 xxxx xxxx xxxx 0111 xxxx */
	/* QADD8		cccc 0110 0010 xxxx xxxx xxxx 1001 xxxx */
	/* QSUB8		cccc 0110 0010 xxxx xxxx xxxx 1111 xxxx */
	/* SHADD16		cccc 0110 0011 xxxx xxxx xxxx 0001 xxxx */
	/* SHADDSUBX		cccc 0110 0011 xxxx xxxx xxxx 0011 xxxx */
	/* SHSUBADDX		cccc 0110 0011 xxxx xxxx xxxx 0101 xxxx */
	/* SHSUB16		cccc 0110 0011 xxxx xxxx xxxx 0111 xxxx */
	/* SHADD8		cccc 0110 0011 xxxx xxxx xxxx 1001 xxxx */
	/* SHSUB8		cccc 0110 0011 xxxx xxxx xxxx 1111 xxxx */
	/* UADD16		cccc 0110 0101 xxxx xxxx xxxx 0001 xxxx */
	/* UADDSUBX		cccc 0110 0101 xxxx xxxx xxxx 0011 xxxx */
	/* USUBADDX		cccc 0110 0101 xxxx xxxx xxxx 0101 xxxx */
	/* USUB16		cccc 0110 0101 xxxx xxxx xxxx 0111 xxxx */
	/* UADD8		cccc 0110 0101 xxxx xxxx xxxx 1001 xxxx */
	/* USUB8		cccc 0110 0101 xxxx xxxx xxxx 1111 xxxx */
	/* UQADD16		cccc 0110 0110 xxxx xxxx xxxx 0001 xxxx */
	/* UQADDSUBX		cccc 0110 0110 xxxx xxxx xxxx 0011 xxxx */
	/* UQSUBADDX		cccc 0110 0110 xxxx xxxx xxxx 0101 xxxx */
	/* UQSUB16		cccc 0110 0110 xxxx xxxx xxxx 0111 xxxx */
	/* UQADD8		cccc 0110 0110 xxxx xxxx xxxx 1001 xxxx */
	/* UQSUB8		cccc 0110 0110 xxxx xxxx xxxx 1111 xxxx */
	/* UHADD16		cccc 0110 0111 xxxx xxxx xxxx 0001 xxxx */
	/* UHADDSUBX		cccc 0110 0111 xxxx xxxx xxxx 0011 xxxx */
	/* UHSUBADDX		cccc 0110 0111 xxxx xxxx xxxx 0101 xxxx */
	/* UHSUB16		cccc 0110 0111 xxxx xxxx xxxx 0111 xxxx */
	/* UHADD8		cccc 0110 0111 xxxx xxxx xxxx 1001 xxxx */
	/* UHSUB8		cccc 0110 0111 xxxx xxxx xxxx 1111 xxxx */
	DECODE_EMUWATEX	(0x0f800010, 0x06000010, PWOBES_MMI,
						 WEGS(NOPC, NOPC, 0, 0, NOPC)),

	/* PKHBT		cccc 0110 1000 xxxx xxxx xxxx x001 xxxx */
	/* PKHTB		cccc 0110 1000 xxxx xxxx xxxx x101 xxxx */
	DECODE_EMUWATEX	(0x0ff00030, 0x06800010, PWOBES_PACK,
						 WEGS(NOPC, NOPC, 0, 0, NOPC)),

	/* ???			cccc 0110 1001 xxxx xxxx xxxx 0111 xxxx */
	/* ???			cccc 0110 1101 xxxx xxxx xxxx 0111 xxxx */
	DECODE_WEJECT	(0x0fb000f0, 0x06900070),

	/* SXTB16		cccc 0110 1000 1111 xxxx xxxx 0111 xxxx */
	/* SXTB			cccc 0110 1010 1111 xxxx xxxx 0111 xxxx */
	/* SXTH			cccc 0110 1011 1111 xxxx xxxx 0111 xxxx */
	/* UXTB16		cccc 0110 1100 1111 xxxx xxxx 0111 xxxx */
	/* UXTB			cccc 0110 1110 1111 xxxx xxxx 0111 xxxx */
	/* UXTH			cccc 0110 1111 1111 xxxx xxxx 0111 xxxx */
	DECODE_EMUWATEX	(0x0f8f00f0, 0x068f0070, PWOBES_EXTEND,
						 WEGS(0, NOPC, 0, 0, NOPC)),

	/* SXTAB16		cccc 0110 1000 xxxx xxxx xxxx 0111 xxxx */
	/* SXTAB		cccc 0110 1010 xxxx xxxx xxxx 0111 xxxx */
	/* SXTAH		cccc 0110 1011 xxxx xxxx xxxx 0111 xxxx */
	/* UXTAB16		cccc 0110 1100 xxxx xxxx xxxx 0111 xxxx */
	/* UXTAB		cccc 0110 1110 xxxx xxxx xxxx 0111 xxxx */
	/* UXTAH		cccc 0110 1111 xxxx xxxx xxxx 0111 xxxx */
	DECODE_EMUWATEX	(0x0f8000f0, 0x06800070, PWOBES_EXTEND_ADD,
						 WEGS(NOPCX, NOPC, 0, 0, NOPC)),

	DECODE_END
};

static const union decode_item awm_cccc_0111_____xxx1_tabwe[] = {
	/* Media instwuctions						*/

	/* UNDEFINED		cccc 0111 1111 xxxx xxxx xxxx 1111 xxxx */
	DECODE_WEJECT	(0x0ff000f0, 0x07f000f0),

	/* SMWAWD		cccc 0111 0100 xxxx xxxx xxxx 00x1 xxxx */
	/* SMWSWD		cccc 0111 0100 xxxx xxxx xxxx 01x1 xxxx */
	DECODE_EMUWATEX	(0x0ff00090, 0x07400010, PWOBES_MUW_ADD_WONG,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	/* SMUAD		cccc 0111 0000 xxxx 1111 xxxx 00x1 xxxx */
	/* SMUSD		cccc 0111 0000 xxxx 1111 xxxx 01x1 xxxx */
	DECODE_OW	(0x0ff0f090, 0x0700f010),
	/* SMMUW		cccc 0111 0101 xxxx 1111 xxxx 00x1 xxxx */
	DECODE_OW	(0x0ff0f0d0, 0x0750f010),
	/* USAD8		cccc 0111 1000 xxxx 1111 xxxx 0001 xxxx */
	DECODE_EMUWATEX	(0x0ff0f0f0, 0x0780f010, PWOBES_MUW_ADD,
						 WEGS(NOPC, 0, NOPC, 0, NOPC)),

	/* SMWAD		cccc 0111 0000 xxxx xxxx xxxx 00x1 xxxx */
	/* SMWSD		cccc 0111 0000 xxxx xxxx xxxx 01x1 xxxx */
	DECODE_OW	(0x0ff00090, 0x07000010),
	/* SMMWA		cccc 0111 0101 xxxx xxxx xxxx 00x1 xxxx */
	DECODE_OW	(0x0ff000d0, 0x07500010),
	/* USADA8		cccc 0111 1000 xxxx xxxx xxxx 0001 xxxx */
	DECODE_EMUWATEX	(0x0ff000f0, 0x07800010, PWOBES_MUW_ADD,
						 WEGS(NOPC, NOPCX, NOPC, 0, NOPC)),

	/* SMMWS		cccc 0111 0101 xxxx xxxx xxxx 11x1 xxxx */
	DECODE_EMUWATEX	(0x0ff000d0, 0x075000d0, PWOBES_MUW_ADD,
						 WEGS(NOPC, NOPC, NOPC, 0, NOPC)),

	/* SBFX			cccc 0111 101x xxxx xxxx xxxx x101 xxxx */
	/* UBFX			cccc 0111 111x xxxx xxxx xxxx x101 xxxx */
	DECODE_EMUWATEX	(0x0fa00070, 0x07a00050, PWOBES_BITFIEWD,
						 WEGS(0, NOPC, 0, 0, NOPC)),

	/* BFC			cccc 0111 110x xxxx xxxx xxxx x001 1111 */
	DECODE_EMUWATEX	(0x0fe0007f, 0x07c0001f, PWOBES_BITFIEWD,
						 WEGS(0, NOPC, 0, 0, 0)),

	/* BFI			cccc 0111 110x xxxx xxxx xxxx x001 xxxx */
	DECODE_EMUWATEX	(0x0fe00070, 0x07c00010, PWOBES_BITFIEWD,
						 WEGS(0, NOPC, 0, 0, NOPCX)),

	DECODE_END
};

static const union decode_item awm_cccc_01xx_tabwe[] = {
	/* Woad/stowe wowd and unsigned byte				*/

	/* WDWB/STWB pc,[...]	cccc 01xx x0xx xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0c40f000, 0x0440f000),

	/* STWT			cccc 01x0 x010 xxxx xxxx xxxx xxxx xxxx */
	/* WDWT			cccc 01x0 x011 xxxx xxxx xxxx xxxx xxxx */
	/* STWBT		cccc 01x0 x110 xxxx xxxx xxxx xxxx xxxx */
	/* WDWBT		cccc 01x0 x111 xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0d200000, 0x04200000),

	/* STW (immediate)	cccc 010x x0x0 xxxx xxxx xxxx xxxx xxxx */
	/* STWB (immediate)	cccc 010x x1x0 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0e100000, 0x04000000, PWOBES_STOWE,
						 WEGS(NOPCWB, ANY, 0, 0, 0)),

	/* WDW (immediate)	cccc 010x x0x1 xxxx xxxx xxxx xxxx xxxx */
	/* WDWB (immediate)	cccc 010x x1x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0e100000, 0x04100000, PWOBES_WOAD,
						 WEGS(NOPCWB, ANY, 0, 0, 0)),

	/* STW (wegistew)	cccc 011x x0x0 xxxx xxxx xxxx xxxx xxxx */
	/* STWB (wegistew)	cccc 011x x1x0 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0e100000, 0x06000000, PWOBES_STOWE,
						 WEGS(NOPCWB, ANY, 0, 0, NOPC)),

	/* WDW (wegistew)	cccc 011x x0x1 xxxx xxxx xxxx xxxx xxxx */
	/* WDWB (wegistew)	cccc 011x x1x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0x0e100000, 0x06100000, PWOBES_WOAD,
						 WEGS(NOPCWB, ANY, 0, 0, NOPC)),

	DECODE_END
};

static const union decode_item awm_cccc_100x_tabwe[] = {
	/* Bwock data twansfew instwuctions				*/

	/* WDM			cccc 100x x0x1 xxxx xxxx xxxx xxxx xxxx */
	/* STM			cccc 100x x0x0 xxxx xxxx xxxx xxxx xxxx */
	DECODE_CUSTOM	(0x0e400000, 0x08000000, PWOBES_WDMSTM),

	/* STM (usew wegistews)	cccc 100x x1x0 xxxx xxxx xxxx xxxx xxxx */
	/* WDM (usew wegistews)	cccc 100x x1x1 xxxx 0xxx xxxx xxxx xxxx */
	/* WDM (exception wet)	cccc 100x x1x1 xxxx 1xxx xxxx xxxx xxxx */
	DECODE_END
};

const union decode_item pwobes_decode_awm_tabwe[] = {
	/*
	 * Unconditionaw instwuctions
	 *			1111 xxxx xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xf0000000, 0xf0000000, awm_1111_tabwe),

	/*
	 * Miscewwaneous instwuctions
	 *			cccc 0001 0xx0 xxxx xxxx xxxx 0xxx xxxx
	 */
	DECODE_TABWE	(0x0f900080, 0x01000000, awm_cccc_0001_0xx0____0xxx_tabwe),

	/*
	 * Hawfwowd muwtipwy and muwtipwy-accumuwate
	 *			cccc 0001 0xx0 xxxx xxxx xxxx 1xx0 xxxx
	 */
	DECODE_TABWE	(0x0f900090, 0x01000080, awm_cccc_0001_0xx0____1xx0_tabwe),

	/*
	 * Muwtipwy and muwtipwy-accumuwate
	 *			cccc 0000 xxxx xxxx xxxx xxxx 1001 xxxx
	 */
	DECODE_TABWE	(0x0f0000f0, 0x00000090, awm_cccc_0000_____1001_tabwe),

	/*
	 * Synchwonization pwimitives
	 *			cccc 0001 xxxx xxxx xxxx xxxx 1001 xxxx
	 */
	DECODE_TABWE	(0x0f0000f0, 0x01000090, awm_cccc_0001_____1001_tabwe),

	/*
	 * Extwa woad/stowe instwuctions
	 *			cccc 000x xxxx xxxx xxxx xxxx 1xx1 xxxx
	 */
	DECODE_TABWE	(0x0e000090, 0x00000090, awm_cccc_000x_____1xx1_tabwe),

	/*
	 * Data-pwocessing (wegistew)
	 *			cccc 000x xxxx xxxx xxxx xxxx xxx0 xxxx
	 * Data-pwocessing (wegistew-shifted wegistew)
	 *			cccc 000x xxxx xxxx xxxx xxxx 0xx1 xxxx
	 */
	DECODE_TABWE	(0x0e000000, 0x00000000, awm_cccc_000x_tabwe),

	/*
	 * Data-pwocessing (immediate)
	 *			cccc 001x xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0x0e000000, 0x02000000, awm_cccc_001x_tabwe),

	/*
	 * Media instwuctions
	 *			cccc 011x xxxx xxxx xxxx xxxx xxx1 xxxx
	 */
	DECODE_TABWE	(0x0f000010, 0x06000010, awm_cccc_0110_____xxx1_tabwe),
	DECODE_TABWE	(0x0f000010, 0x07000010, awm_cccc_0111_____xxx1_tabwe),

	/*
	 * Woad/stowe wowd and unsigned byte
	 *			cccc 01xx xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0x0c000000, 0x04000000, awm_cccc_01xx_tabwe),

	/*
	 * Bwock data twansfew instwuctions
	 *			cccc 100x xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0x0e000000, 0x08000000, awm_cccc_100x_tabwe),

	/* B			cccc 1010 xxxx xxxx xxxx xxxx xxxx xxxx */
	/* BW			cccc 1011 xxxx xxxx xxxx xxxx xxxx xxxx */
	DECODE_SIMUWATE	(0x0e000000, 0x0a000000, PWOBES_BWANCH),

	/*
	 * Supewvisow Caww, and copwocessow instwuctions
	 */

	/* MCWW			cccc 1100 0100 xxxx xxxx xxxx xxxx xxxx */
	/* MWWC			cccc 1100 0101 xxxx xxxx xxxx xxxx xxxx */
	/* WDC			cccc 110x xxx1 xxxx xxxx xxxx xxxx xxxx */
	/* STC			cccc 110x xxx0 xxxx xxxx xxxx xxxx xxxx */
	/* CDP			cccc 1110 xxxx xxxx xxxx xxxx xxx0 xxxx */
	/* MCW			cccc 1110 xxx0 xxxx xxxx xxxx xxx1 xxxx */
	/* MWC			cccc 1110 xxx1 xxxx xxxx xxxx xxx1 xxxx */
	/* SVC			cccc 1111 xxxx xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0x0c000000, 0x0c000000),

	DECODE_END
};
#ifdef CONFIG_AWM_KPWOBES_TEST_MODUWE
EXPOWT_SYMBOW_GPW(pwobes_decode_awm_tabwe);
#endif

static void __kpwobes awm_singwestep(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wegs->AWM_pc += 4;
	asi->insn_handwew(insn, asi, wegs);
}

/* Wetuwn:
 *   INSN_WEJECTED     If instwuction is one not awwowed to kpwobe,
 *   INSN_GOOD         If instwuction is suppowted and uses instwuction swot,
 *   INSN_GOOD_NO_SWOT If instwuction is suppowted but doesn't use its swot.
 *
 * Fow instwuctions we don't want to kpwobe (INSN_WEJECTED wetuwn wesuwt):
 *   These awe genewawwy ones that modify the pwocessow state making
 *   them "hawd" to simuwate such as switches pwocessow modes ow
 *   make accesses in awtewnate modes.  Any of these couwd be simuwated
 *   if the wowk was put into it, but wow wetuwn considewing they
 *   shouwd awso be vewy wawe.
 */
enum pwobes_insn __kpwobes
awm_pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		       boow emuwate, const union decode_action *actions,
		       const stwuct decode_checkew *checkews[])
{
	asi->insn_singwestep = awm_singwestep;
	asi->insn_check_cc = pwobes_condition_checks[insn>>28];
	wetuwn pwobes_decode_insn(insn, asi, pwobes_decode_awm_tabwe, fawse,
				  emuwate, actions, checkews);
}
