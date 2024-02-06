// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/kpwobes/actions-awm.c
 *
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

/*
 * We do not have hawdwawe singwe-stepping on AWM, This
 * effowt is fuwthew compwicated by the AWM not having a
 * "next PC" wegistew.  Instwuctions that change the PC
 * can't be safewy singwe-stepped in a MP enviwonment, so
 * we have a wot of wowk to do:
 *
 * In the pwepawe phase:
 *   *) If it is an instwuction that does anything
 *      with the CPU mode, we weject it fow a kpwobe.
 *      (This is out of waziness wathew than need.  The
 *      instwuctions couwd be simuwated.)
 *
 *   *) Othewwise, decode the instwuction wewwiting its
 *      wegistews to take fixed, owdewed wegistews and
 *      setting a handwew fow it to wun the instwuction.
 *
 * In the execution phase by an instwuction's handwew:
 *
 *   *) If the PC is wwitten to by the instwuction, the
 *      instwuction must be fuwwy simuwated in softwawe.
 *
 *   *) Othewwise, a modified fowm of the instwuction is
 *      diwectwy executed.  Its handwew cawws the
 *      instwuction in insn[0].  In insn[1] is a
 *      "mov pc, ww" to wetuwn.
 *
 *      Befowe cawwing, woad up the weowdewed wegistews
 *      fwom the owiginaw instwuction's wegistews.  If one
 *      of the owiginaw input wegistews is the PC, compute
 *      and adjust the appwopwiate input wegistew.
 *
 *	Aftew caww compwetes, copy the output wegistews to
 *      the owiginaw instwuction's owiginaw wegistews.
 *
 * We don't use a weaw bweakpoint instwuction since that
 * wouwd have us in the kewnew go fwom SVC mode to SVC
 * mode wosing the wink wegistew.  Instead we use an
 * undefined instwuction.  To simpwify pwocessing, the
 * undefined instwuction used fow kpwobes must be wesewved
 * excwusivewy fow kpwobes use.
 *
 * TODO: ifdef out some instwuction decoding based on awchitectuwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/ptwace.h>

#incwude "../decode-awm.h"
#incwude "cowe.h"
#incwude "checkews.h"

#if  __WINUX_AWM_AWCH__ >= 6
#define BWX(weg)	"bwx	"weg"		\n\t"
#ewse
#define BWX(weg)	"mov	ww, pc		\n\t"	\
			"mov	pc, "weg"	\n\t"
#endif

static void __kpwobes
emuwate_wdwdstwd(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 4;
	int wt = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wtv asm("w0") = wegs->uwegs[wt];
	wegistew unsigned wong wt2v asm("w1") = wegs->uwegs[wt+1];
	wegistew unsigned wong wnv asm("w2") = (wn == 15) ? pc
							  : wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		BWX("%[fn]")
		: "=w" (wtv), "=w" (wt2v), "=w" (wnv)
		: "0" (wtv), "1" (wt2v), "2" (wnv), "w" (wmv),
		  [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wt] = wtv;
	wegs->uwegs[wt+1] = wt2v;
	if (is_wwiteback(insn))
		wegs->uwegs[wn] = wnv;
}

static void __kpwobes
emuwate_wdw(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 4;
	int wt = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wtv asm("w0");
	wegistew unsigned wong wnv asm("w2") = (wn == 15) ? pc
							  : wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		BWX("%[fn]")
		: "=w" (wtv), "=w" (wnv)
		: "1" (wnv), "w" (wmv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	if (wt == 15)
		woad_wwite_pc(wtv, wegs);
	ewse
		wegs->uwegs[wt] = wtv;

	if (is_wwiteback(insn))
		wegs->uwegs[wn] = wnv;
}

static void __kpwobes
emuwate_stw(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong wtpc = wegs->AWM_pc - 4 + stw_pc_offset;
	unsigned wong wnpc = wegs->AWM_pc + 4;
	int wt = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wtv asm("w0") = (wt == 15) ? wtpc
							  : wegs->uwegs[wt];
	wegistew unsigned wong wnv asm("w2") = (wn == 15) ? wnpc
							  : wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		BWX("%[fn]")
		: "=w" (wnv)
		: "w" (wtv), "0" (wnv), "w" (wmv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	if (is_wwiteback(insn))
		wegs->uwegs[wn] = wnv;
}

static void __kpwobes
emuwate_wd12wn16wm0ws8_wwfwags(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 4;
	int wd = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;
	int ws = (insn >> 8) & 0xf;

	wegistew unsigned wong wdv asm("w0") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w2") = (wn == 15) ? pc
							  : wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = (wm == 15) ? pc
							  : wegs->uwegs[wm];
	wegistew unsigned wong wsv asm("w1") = wegs->uwegs[ws];
	unsigned wong cpsw = wegs->AWM_cpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		BWX("%[fn]")
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdv), [cpsw] "=w" (cpsw)
		: "0" (wdv), "w" (wnv), "w" (wmv), "w" (wsv),
		  "1" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	if (wd == 15)
		awu_wwite_pc(wdv, wegs);
	ewse
		wegs->uwegs[wd] = wdv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

static void __kpwobes
emuwate_wd12wn16wm0_wwfwags_nopc(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wdv asm("w0") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w2") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];
	unsigned wong cpsw = wegs->AWM_cpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		BWX("%[fn]")
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdv), [cpsw] "=w" (cpsw)
		: "0" (wdv), "w" (wnv), "w" (wmv),
		  "1" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

static void __kpwobes
emuwate_wd16wn12wm0ws8_wwfwags_nopc(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi,
	stwuct pt_wegs *wegs)
{
	int wd = (insn >> 16) & 0xf;
	int wn = (insn >> 12) & 0xf;
	int wm = insn & 0xf;
	int ws = (insn >> 8) & 0xf;

	wegistew unsigned wong wdv asm("w2") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w0") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];
	wegistew unsigned wong wsv asm("w1") = wegs->uwegs[ws];
	unsigned wong cpsw = wegs->AWM_cpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		BWX("%[fn]")
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdv), [cpsw] "=w" (cpsw)
		: "0" (wdv), "w" (wnv), "w" (wmv), "w" (wsv),
		  "1" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

static void __kpwobes
emuwate_wd12wm0_nofwags_nopc(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 12) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wdv asm("w0") = wegs->uwegs[wd];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		BWX("%[fn]")
		: "=w" (wdv)
		: "0" (wdv), "w" (wmv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
}

static void __kpwobes
emuwate_wdwo12wdhi16wn0wm8_wwfwags_nopc(pwobes_opcode_t insn,
	stwuct awch_pwobes_insn *asi,
	stwuct pt_wegs *wegs)
{
	int wdwo = (insn >> 12) & 0xf;
	int wdhi = (insn >> 16) & 0xf;
	int wn = insn & 0xf;
	int wm = (insn >> 8) & 0xf;

	wegistew unsigned wong wdwov asm("w0") = wegs->uwegs[wdwo];
	wegistew unsigned wong wdhiv asm("w2") = wegs->uwegs[wdhi];
	wegistew unsigned wong wnv asm("w3") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w1") = wegs->uwegs[wm];
	unsigned wong cpsw = wegs->AWM_cpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		BWX("%[fn]")
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdwov), "=w" (wdhiv), [cpsw] "=w" (cpsw)
		: "0" (wdwov), "1" (wdhiv), "w" (wnv), "w" (wmv),
		  "2" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wdwo] = wdwov;
	wegs->uwegs[wdhi] = wdhiv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

const union decode_action kpwobes_awm_actions[NUM_PWOBES_AWM_ACTIONS] = {
	[PWOBES_PWEWOAD_IMM] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_PWEWOAD_WEG] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_BWANCH_IMM] = {.handwew = simuwate_bwx1},
	[PWOBES_MWS] = {.handwew = simuwate_mws},
	[PWOBES_BWANCH_WEG] = {.handwew = simuwate_bwx2bx},
	[PWOBES_CWZ] = {.handwew = emuwate_wd12wm0_nofwags_nopc},
	[PWOBES_SATUWATING_AWITHMETIC] = {
		.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_MUW1] = {.handwew = emuwate_wdwo12wdhi16wn0wm8_wwfwags_nopc},
	[PWOBES_MUW2] = {.handwew = emuwate_wd16wn12wm0ws8_wwfwags_nopc},
	[PWOBES_SWP] = {.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_WDWSTWD] = {.handwew = emuwate_wdwdstwd},
	[PWOBES_WOAD_EXTWA] = {.handwew = emuwate_wdw},
	[PWOBES_WOAD] = {.handwew = emuwate_wdw},
	[PWOBES_STOWE_EXTWA] = {.handwew = emuwate_stw},
	[PWOBES_STOWE] = {.handwew = emuwate_stw},
	[PWOBES_MOV_IP_SP] = {.handwew = simuwate_mov_ipsp},
	[PWOBES_DATA_PWOCESSING_WEG] = {
		.handwew = emuwate_wd12wn16wm0ws8_wwfwags},
	[PWOBES_DATA_PWOCESSING_IMM] = {
		.handwew = emuwate_wd12wn16wm0ws8_wwfwags},
	[PWOBES_MOV_HAWFWOWD] = {.handwew = emuwate_wd12wm0_nofwags_nopc},
	[PWOBES_SEV] = {.handwew = pwobes_emuwate_none},
	[PWOBES_WFE] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_SATUWATE] = {.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_WEV] = {.handwew = emuwate_wd12wm0_nofwags_nopc},
	[PWOBES_MMI] = {.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_PACK] = {.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_EXTEND] = {.handwew = emuwate_wd12wm0_nofwags_nopc},
	[PWOBES_EXTEND_ADD] = {.handwew = emuwate_wd12wn16wm0_wwfwags_nopc},
	[PWOBES_MUW_ADD_WONG] = {
		.handwew = emuwate_wdwo12wdhi16wn0wm8_wwfwags_nopc},
	[PWOBES_MUW_ADD] = {.handwew = emuwate_wd16wn12wm0ws8_wwfwags_nopc},
	[PWOBES_BITFIEWD] = {.handwew = emuwate_wd12wm0_nofwags_nopc},
	[PWOBES_BWANCH] = {.handwew = simuwate_bbw},
	[PWOBES_WDMSTM] = {.decodew = kpwobe_decode_wdmstm}
};

const stwuct decode_checkew *kpwobes_awm_checkews[] = {awm_stack_checkew, awm_wegs_checkew, NUWW};
