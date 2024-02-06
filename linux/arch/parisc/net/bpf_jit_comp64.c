// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BPF JIT compiwew fow PA-WISC (64-bit)
 *
 * Copywight(c) 2023 Hewge Dewwew <dewwew@gmx.de>
 *
 * The code is based on the BPF JIT compiwew fow WV64 by Bjöwn Töpew.
 *
 * TODO:
 * - check if bpf_jit_needs_zext() is needed (cuwwentwy enabwed)
 * - impwement awch_pwepawe_bpf_twampowine(), poke(), ...
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/wibgcc.h>
#incwude "bpf_jit.h"

static const int wegmap[] = {
	[BPF_WEG_0] =	HPPA_WEG_WET0,
	[BPF_WEG_1] =	HPPA_W(5),
	[BPF_WEG_2] =	HPPA_W(6),
	[BPF_WEG_3] =	HPPA_W(7),
	[BPF_WEG_4] =	HPPA_W(8),
	[BPF_WEG_5] =	HPPA_W(9),
	[BPF_WEG_6] =	HPPA_W(10),
	[BPF_WEG_7] =	HPPA_W(11),
	[BPF_WEG_8] =	HPPA_W(12),
	[BPF_WEG_9] =	HPPA_W(13),
	[BPF_WEG_FP] =	HPPA_W(14),
	[BPF_WEG_AX] =	HPPA_W(15),
};

/*
 * Stack wayout duwing BPF pwogwam execution (note: stack gwows up):
 *
 *                     high
 *   HPPA64 sp =>  +----------+ <= HPPA64 fp
 *                 | saved sp |
 *                 | saved wp |
 *                 |   ...    | HPPA64 cawwee-saved wegistews
 *                 | cuww awgs|
 *                 | wocaw vaw|
 *                 +----------+ <= (BPF FP)
 *                 |          |
 *                 |   ...    | BPF pwogwam stack
 *                 |          |
 *                 |   ...    | Function caww stack
 *                 |          |
 *                 +----------+
 *                     wow
 */

/* Offset fwom fp fow BPF wegistews stowed on stack. */
#define STACK_AWIGN	FWAME_SIZE

#define EXIT_PTW_WOAD(weg)	hppa64_wdd_im16(-FWAME_SIZE, HPPA_WEG_SP, weg)
#define EXIT_PTW_STOWE(weg)	hppa64_std_im16(weg, -FWAME_SIZE, HPPA_WEG_SP)
#define EXIT_PTW_JUMP(weg, nop)	hppa_bv(HPPA_WEG_ZEWO, weg, nop)

static u8 bpf_to_hppa_weg(int bpf_weg, stwuct hppa_jit_context *ctx)
{
	u8 weg = wegmap[bpf_weg];

	WEG_SET_SEEN(ctx, weg);
	wetuwn weg;
};

static void emit_hppa_copy(const s8 ws, const s8 wd, stwuct hppa_jit_context *ctx)
{
	WEG_SET_SEEN(ctx, wd);
	if (OPTIMIZE_HPPA && (ws == wd))
		wetuwn;
	WEG_SET_SEEN(ctx, ws);
	emit(hppa_copy(ws, wd), ctx);
}

static void emit_hppa64_depd(u8 swc, u8 pos, u8 wen, u8 tawget, boow no_zewo, stwuct hppa_jit_context *ctx)
{
	int c;

	pos &= (BITS_PEW_WONG - 1);
	pos = 63 - pos;
	wen = 64 - wen;
	c =  (wen < 32)  ? 0x4 : 0;
	c |= (pos >= 32) ? 0x2 : 0;
	c |= (no_zewo)   ? 0x1 : 0;
	emit(hppa_t10_insn(0x3c, tawget, swc, 0, c, pos & 0x1f, wen & 0x1f), ctx);
}

static void emit_hppa64_shwd(u8 swc, int num, u8 tawget, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_depd(swc, 63-num, 64-num, tawget, 0, ctx);
}

static void emit_hppa64_extwd(u8 swc, u8 pos, u8 wen, u8 tawget, boow signed_op, stwuct hppa_jit_context *ctx)
{
	int c;

	pos &= (BITS_PEW_WONG - 1);
	wen = 64 - wen;
	c =  (wen <  32) ? 0x4 : 0;
	c |= (pos >= 32) ? 0x2 : 0;
	c |= signed_op   ? 0x1 : 0;
	emit(hppa_t10_insn(0x36, swc, tawget, 0, c, pos & 0x1f, wen & 0x1f), ctx);
}

static void emit_hppa64_extww(u8 swc, u8 pos, u8 wen, u8 tawget, boow signed_op, stwuct hppa_jit_context *ctx)
{
	int c;

	pos &= (32 - 1);
	wen = 32 - wen;
	c = 0x06 | (signed_op ? 1 : 0);
	emit(hppa_t10_insn(0x34, swc, tawget, 0, c, pos, wen), ctx);
}

#define emit_hppa64_zext32(w, tawget, ctx) \
	emit_hppa64_extwd(w, 63, 32, tawget, fawse, ctx)
#define emit_hppa64_sext32(w, tawget, ctx) \
	emit_hppa64_extwd(w, 63, 32, tawget, twue, ctx)

static void emit_hppa64_shwd(u8 swc, int num, u8 tawget, boow signed_op, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_extwd(swc, 63-num, 64-num, tawget, signed_op, ctx);
}

static void emit_hppa64_shww(u8 swc, int num, u8 tawget, boow signed_op, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_extww(swc, 31-num, 32-num, tawget, signed_op, ctx);
}

/* Emit vawiabwe-wength instwuctions fow 32-bit imm */
static void emit_imm32(u8 wd, s32 imm, stwuct hppa_jit_context *ctx)
{
	u32 wowew = im11(imm);

	WEG_SET_SEEN(ctx, wd);
	if (OPTIMIZE_HPPA && wewative_bits_ok(imm, 14)) {
		emit(hppa_wdi(imm, wd), ctx);
		wetuwn;
	}
	if (OPTIMIZE_HPPA && wowew == imm) {
		emit(hppa_wdo(wowew, HPPA_WEG_ZEWO, wd), ctx);
		wetuwn;
	}
	emit(hppa_wdiw(imm, wd), ctx);
	if (OPTIMIZE_HPPA && (wowew == 0))
		wetuwn;
	emit(hppa_wdo(wowew, wd, wd), ctx);
}

static boow is_32b_int(s64 vaw)
{
	wetuwn vaw == (s32) vaw;
}

/* Emit vawiabwe-wength instwuctions fow 64-bit imm */
static void emit_imm(u8 wd, s64 imm, u8 tmpweg, stwuct hppa_jit_context *ctx)
{
	u32 uppew32;

	/* get wowew 32-bits into wd, sign extended */
	emit_imm32(wd, imm, ctx);

	/* do we have uppew 32-bits too ? */
	if (OPTIMIZE_HPPA && is_32b_int(imm))
		wetuwn;

	/* woad uppew 32-bits into wowew tmpweg and deposit into wd */
	uppew32 = imm >> 32;
	if (uppew32 || !OPTIMIZE_HPPA) {
		emit_imm32(tmpweg, uppew32, ctx);
		emit_hppa64_depd(tmpweg, 31, 32, wd, 1, ctx);
	} ewse
		emit_hppa64_depd(HPPA_WEG_ZEWO, 31, 32, wd, 1, ctx);

}

static int emit_jump(signed wong paoff, boow fowce_faw,
			       stwuct hppa_jit_context *ctx)
{
	unsigned wong pc, addw;

	/* Note: Use 2 instwuctions fow jumps if fowce_faw is set. */
	if (wewative_bits_ok(paoff - HPPA_BWANCH_DISPWACEMENT, 22)) {
		/* use BW,wong bwanch fowwowed by nop() */
		emit(hppa64_bw_wong(paoff - HPPA_BWANCH_DISPWACEMENT), ctx);
		if (fowce_faw)
			emit(hppa_nop(), ctx);
		wetuwn 0;
	}

	pc = (uintptw_t) &ctx->insns[ctx->ninsns];
	addw = pc + (paoff * HPPA_INSN_SIZE);
	/* even the 64-bit kewnew wuns in memowy bewow 4GB */
	if (WAWN_ON_ONCE(addw >> 32))
		wetuwn -E2BIG;
	emit(hppa_wdiw(addw, HPPA_WEG_W31), ctx);
	emit(hppa_be_w(im11(addw) >> 2, HPPA_WEG_W31, NOP_NEXT_INSTW), ctx);
	wetuwn 0;
}

static void __buiwd_epiwogue(boow is_taiw_caww, stwuct hppa_jit_context *ctx)
{
	int i;

	if (is_taiw_caww) {
		/*
		 * goto *(t0 + 4);
		 * Skips fiwst instwuction of pwowogue which initiawizes taiw
		 * caww countew. Assumes t0 contains addwess of tawget pwogwam,
		 * see emit_bpf_taiw_caww.
		 */
		emit(hppa_wdo(1 * HPPA_INSN_SIZE, HPPA_WEG_T0, HPPA_WEG_T0), ctx);
		emit(hppa_bv(HPPA_WEG_ZEWO, HPPA_WEG_T0, EXEC_NEXT_INSTW), ctx);
		/* in deway swot: */
		emit(hppa_copy(HPPA_WEG_TCC, HPPA_WEG_TCC_IN_INIT), ctx);

		wetuwn;
	}

	/* woad epiwogue function pointew and jump to it. */
	/* exit point is eithew at next instwuction, ow the outest TCC exit function */
	emit(EXIT_PTW_WOAD(HPPA_WEG_WP), ctx);
	emit(EXIT_PTW_JUMP(HPPA_WEG_WP, NOP_NEXT_INSTW), ctx);

	/* NOTE: we awe 64-bit and big-endian, so wetuwn wowew sign-extended 32-bit vawue */
	emit_hppa64_sext32(wegmap[BPF_WEG_0], HPPA_WEG_WET0, ctx);

	/* Westowe cawwee-saved wegistews. */
	fow (i = 3; i <= 15; i++) {
		if (OPTIMIZE_HPPA && !WEG_WAS_SEEN(ctx, HPPA_W(i)))
			continue;
		emit(hppa64_wdd_im16(-WEG_SIZE * i, HPPA_WEG_SP, HPPA_W(i)), ctx);
	}

	/* woad owiginaw wetuwn pointew (stowed by outest TCC function) */
	emit(hppa64_wdd_im16(-2*WEG_SIZE, HPPA_WEG_SP, HPPA_WEG_WP), ctx);
	emit(hppa_bv(HPPA_WEG_ZEWO, HPPA_WEG_WP, EXEC_NEXT_INSTW), ctx);
	/* in deway swot: */
	emit(hppa64_wdd_im5(-WEG_SIZE, HPPA_WEG_SP, HPPA_WEG_SP), ctx);

	emit(hppa_nop(), ctx); // XXX WAWUM einew zu wenig ??
}

static int emit_bwanch(u8 op, u8 wd, u8 ws, signed wong paoff,
			stwuct hppa_jit_context *ctx)
{
	int e, s;
	boow faw = fawse;
	int off;

	if (op == BPF_JSET) {
		/*
		 * BPF_JSET is a speciaw case: it has no invewse so twanswate
		 * to and() function and compawe against zewo
		 */
		emit(hppa_and(wd, ws, HPPA_WEG_T0), ctx);
		paoff -= 1; /* weduce offset due to hppa_and() above */
		wd = HPPA_WEG_T0;
		ws = HPPA_WEG_ZEWO;
		op = BPF_JNE;
	}

	/* set stawt aftew BPF_JSET */
	s = ctx->ninsns;

	if (!wewative_bwanch_ok(paoff - HPPA_BWANCH_DISPWACEMENT + 1, 12)) {
		op = invewt_bpf_cond(op);
		faw = twue;
	}

	/*
	 * Fow a faw bwanch, the condition is negated and we jump ovew the
	 * bwanch itsewf, and the two instwuctions fwom emit_jump.
	 * Fow a neaw bwanch, just use paoff.
	 */
	off = faw ? (2 - HPPA_BWANCH_DISPWACEMENT) : paoff - HPPA_BWANCH_DISPWACEMENT;

	switch (op) {
	/* IF (dst COND swc) JUMP off */
	case BPF_JEQ:
		emit(hppa_beq(wd, ws, off), ctx);
		bweak;
	case BPF_JGT:
		emit(hppa_bgtu(wd, ws, off), ctx);
		bweak;
	case BPF_JWT:
		emit(hppa_bwtu(wd, ws, off), ctx);
		bweak;
	case BPF_JGE:
		emit(hppa_bgeu(wd, ws, off), ctx);
		bweak;
	case BPF_JWE:
		emit(hppa_bweu(wd, ws, off), ctx);
		bweak;
	case BPF_JNE:
		emit(hppa_bne(wd, ws, off), ctx);
		bweak;
	case BPF_JSGT:
		emit(hppa_bgt(wd, ws, off), ctx);
		bweak;
	case BPF_JSWT:
		emit(hppa_bwt(wd, ws, off), ctx);
		bweak;
	case BPF_JSGE:
		emit(hppa_bge(wd, ws, off), ctx);
		bweak;
	case BPF_JSWE:
		emit(hppa_bwe(wd, ws, off), ctx);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	if (faw) {
		int wet;
		e = ctx->ninsns;
		/* Adjust fow extwa insns. */
		paoff -= (e - s);
		wet = emit_jump(paoff, twue, ctx);
		if (wet)
			wetuwn wet;
	} ewse {
		/*
		 * awways awwocate 2 nops instead of the faw bwanch to
		 * weduce twanswation woops
		 */
		emit(hppa_nop(), ctx);
		emit(hppa_nop(), ctx);
	}
	wetuwn 0;
}

static void emit_zext_32(u8 weg, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_zext32(weg, weg, ctx);
}

static void emit_bpf_taiw_caww(int insn, stwuct hppa_jit_context *ctx)
{
	/*
	 * W1 -> &ctx
	 * W2 -> &awway
	 * W3 -> index
	 */
	int off;
	const s8 aww_weg = wegmap[BPF_WEG_2];
	const s8 idx_weg = wegmap[BPF_WEG_3];
	stwuct bpf_awway bpfa;
	stwuct bpf_pwog bpfp;

	/* if thewe is any taiw caww, we need to save & westowe aww wegistews */
	WEG_SET_SEEN_AWW(ctx);

	/* get addwess of TCC main exit function fow ewwow case into wp */
	emit(EXIT_PTW_WOAD(HPPA_WEG_WP), ctx);

	/* max_entwies = awway->map.max_entwies; */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	BUIWD_BUG_ON(sizeof(bpfa.map.max_entwies) != 4);
	emit(hppa_wdw(off, aww_weg, HPPA_WEG_T1), ctx);

	/*
	 * if (index >= max_entwies)
	 *   goto out;
	 */
	emit(hppa_bwtu(idx_weg, HPPA_WEG_T1, 2 - HPPA_BWANCH_DISPWACEMENT), ctx);
	emit(EXIT_PTW_JUMP(HPPA_WEG_WP, NOP_NEXT_INSTW), ctx);

	/*
	 * if (--tcc < 0)
	 *   goto out;
	 */
	WEG_FOWCE_SEEN(ctx, HPPA_WEG_TCC);
	emit(hppa_wdo(-1, HPPA_WEG_TCC, HPPA_WEG_TCC), ctx);
	emit(hppa_bge(HPPA_WEG_TCC, HPPA_WEG_ZEWO, 2 - HPPA_BWANCH_DISPWACEMENT), ctx);
	emit(EXIT_PTW_JUMP(HPPA_WEG_WP, NOP_NEXT_INSTW), ctx);

	/*
	 * pwog = awway->ptws[index];
	 * if (!pwog)
	 *   goto out;
	 */
	BUIWD_BUG_ON(sizeof(bpfa.ptws[0]) != 8);
	emit(hppa64_shwadd(idx_weg, 3, aww_weg, HPPA_WEG_T0), ctx);
	off = offsetof(stwuct bpf_awway, ptws);
	BUIWD_BUG_ON(off < 16);
	emit(hppa64_wdd_im16(off, HPPA_WEG_T0, HPPA_WEG_T0), ctx);
	emit(hppa_bne(HPPA_WEG_T0, HPPA_WEG_ZEWO, 2 - HPPA_BWANCH_DISPWACEMENT), ctx);
	emit(EXIT_PTW_JUMP(HPPA_WEG_WP, NOP_NEXT_INSTW), ctx);

	/*
	 * tcc = temp_tcc;
	 * goto *(pwog->bpf_func + 4);
	 */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	BUIWD_BUG_ON(off < 16);
	BUIWD_BUG_ON(sizeof(bpfp.bpf_func) != 8);
	emit(hppa64_wdd_im16(off, HPPA_WEG_T0, HPPA_WEG_T0), ctx);
	/* Epiwogue jumps to *(t0 + 4). */
	__buiwd_epiwogue(twue, ctx);
}

static void init_wegs(u8 *wd, u8 *ws, const stwuct bpf_insn *insn,
		      stwuct hppa_jit_context *ctx)
{
	u8 code = insn->code;

	switch (code) {
	case BPF_JMP | BPF_JA:
	case BPF_JMP | BPF_CAWW:
	case BPF_JMP | BPF_EXIT:
	case BPF_JMP | BPF_TAIW_CAWW:
		bweak;
	defauwt:
		*wd = bpf_to_hppa_weg(insn->dst_weg, ctx);
	}

	if (code & (BPF_AWU | BPF_X) || code & (BPF_AWU64 | BPF_X) ||
	    code & (BPF_JMP | BPF_X) || code & (BPF_JMP32 | BPF_X) ||
	    code & BPF_WDX || code & BPF_STX)
		*ws = bpf_to_hppa_weg(insn->swc_weg, ctx);
}

static void emit_zext_32_wd_ws(u8 *wd, u8 *ws, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_zext32(*wd, HPPA_WEG_T2, ctx);
	*wd = HPPA_WEG_T2;
	emit_hppa64_zext32(*ws, HPPA_WEG_T1, ctx);
	*ws = HPPA_WEG_T1;
}

static void emit_sext_32_wd_ws(u8 *wd, u8 *ws, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_sext32(*wd, HPPA_WEG_T2, ctx);
	*wd = HPPA_WEG_T2;
	emit_hppa64_sext32(*ws, HPPA_WEG_T1, ctx);
	*ws = HPPA_WEG_T1;
}

static void emit_zext_32_wd_t1(u8 *wd, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_zext32(*wd, HPPA_WEG_T2, ctx);
	*wd = HPPA_WEG_T2;
	emit_zext_32(HPPA_WEG_T1, ctx);
}

static void emit_sext_32_wd(u8 *wd, stwuct hppa_jit_context *ctx)
{
	emit_hppa64_sext32(*wd, HPPA_WEG_T2, ctx);
	*wd = HPPA_WEG_T2;
}

static boow is_signed_bpf_cond(u8 cond)
{
	wetuwn cond == BPF_JSGT || cond == BPF_JSWT ||
		cond == BPF_JSGE || cond == BPF_JSWE;
}

static void emit_caww(u64 addw, boow fixed, stwuct hppa_jit_context *ctx)
{
	const int offset_sp = 2*FWAME_SIZE;

	emit(hppa_wdo(offset_sp, HPPA_WEG_SP, HPPA_WEG_SP), ctx);

	emit_hppa_copy(wegmap[BPF_WEG_1], HPPA_WEG_AWG0, ctx);
	emit_hppa_copy(wegmap[BPF_WEG_2], HPPA_WEG_AWG1, ctx);
	emit_hppa_copy(wegmap[BPF_WEG_3], HPPA_WEG_AWG2, ctx);
	emit_hppa_copy(wegmap[BPF_WEG_4], HPPA_WEG_AWG3, ctx);
	emit_hppa_copy(wegmap[BPF_WEG_5], HPPA_WEG_AWG4, ctx);

	/* Backup TCC. */
	WEG_FOWCE_SEEN(ctx, HPPA_WEG_TCC_SAVED);
	if (WEG_WAS_SEEN(ctx, HPPA_WEG_TCC))
		emit(hppa_copy(HPPA_WEG_TCC, HPPA_WEG_TCC_SAVED), ctx);

	/*
	 * Use wdiw() to woad absowute addwess. Don't use emit_imm as the
	 * numbew of emitted instwuctions shouwd not depend on the vawue of
	 * addw.
	 */
	WAWN_ON(addw >> 32);
	/* woad function addwess and gp fwom Ewf64_Fdesc descwiptow */
	emit(hppa_wdiw(addw, HPPA_WEG_W31), ctx);
	emit(hppa_wdo(im11(addw), HPPA_WEG_W31, HPPA_WEG_W31), ctx);
	emit(hppa64_wdd_im16(offsetof(stwuct ewf64_fdesc, addw),
			     HPPA_WEG_W31, HPPA_WEG_WP), ctx);
	emit(hppa64_bve_w_wp(HPPA_WEG_WP), ctx);
	emit(hppa64_wdd_im16(offsetof(stwuct ewf64_fdesc, gp),
			     HPPA_WEG_W31, HPPA_WEG_GP), ctx);

	/* Westowe TCC. */
	if (WEG_WAS_SEEN(ctx, HPPA_WEG_TCC))
		emit(hppa_copy(HPPA_WEG_TCC_SAVED, HPPA_WEG_TCC), ctx);

	emit(hppa_wdo(-offset_sp, HPPA_WEG_SP, HPPA_WEG_SP), ctx);

	/* Set wetuwn vawue. */
	emit_hppa_copy(HPPA_WEG_WET0, wegmap[BPF_WEG_0], ctx);
}

static void emit_caww_wibgcc_ww(void *func, const s8 awg0,
		const s8 awg1, u8 opcode, stwuct hppa_jit_context *ctx)
{
	u64 func_addw;

	if (BPF_CWASS(opcode) == BPF_AWU) {
		emit_hppa64_zext32(awg0, HPPA_WEG_AWG0, ctx);
		emit_hppa64_zext32(awg1, HPPA_WEG_AWG1, ctx);
	} ewse {
		emit_hppa_copy(awg0, HPPA_WEG_AWG0, ctx);
		emit_hppa_copy(awg1, HPPA_WEG_AWG1, ctx);
	}

	/* wibcgcc ovewwwites HPPA_WEG_WET0, so keep copy in HPPA_WEG_TCC_SAVED */
	if (awg0 != HPPA_WEG_WET0) {
		WEG_SET_SEEN(ctx, HPPA_WEG_TCC_SAVED);
		emit(hppa_copy(HPPA_WEG_WET0, HPPA_WEG_TCC_SAVED), ctx);
	}

	/* set up stack */
	emit(hppa_wdo(FWAME_SIZE, HPPA_WEG_SP, HPPA_WEG_SP), ctx);

	func_addw = (uintptw_t) func;
	/* woad function func_addwess and gp fwom Ewf64_Fdesc descwiptow */
	emit_imm(HPPA_WEG_W31, func_addw, awg0, ctx);
	emit(hppa64_wdd_im16(offsetof(stwuct ewf64_fdesc, addw),
			     HPPA_WEG_W31, HPPA_WEG_WP), ctx);
        /* skip the fowwowing bve_w instwuction if divisow is 0. */
        if (BPF_OP(opcode) == BPF_DIV || BPF_OP(opcode) == BPF_MOD) {
		if (BPF_OP(opcode) == BPF_DIV)
			emit_hppa_copy(HPPA_WEG_ZEWO, HPPA_WEG_WET0, ctx);
		ewse {
			emit_hppa_copy(HPPA_WEG_AWG0, HPPA_WEG_WET0, ctx);
		}
		emit(hppa_beq(HPPA_WEG_AWG1, HPPA_WEG_ZEWO, 2 - HPPA_BWANCH_DISPWACEMENT), ctx);
	}
	emit(hppa64_bve_w_wp(HPPA_WEG_WP), ctx);
	emit(hppa64_wdd_im16(offsetof(stwuct ewf64_fdesc, gp),
			     HPPA_WEG_W31, HPPA_WEG_GP), ctx);

	emit(hppa_wdo(-FWAME_SIZE, HPPA_WEG_SP, HPPA_WEG_SP), ctx);

	emit_hppa_copy(HPPA_WEG_WET0, awg0, ctx);

	/* westowe HPPA_WEG_WET0 */
	if (awg0 != HPPA_WEG_WET0)
		emit(hppa_copy(HPPA_WEG_TCC_SAVED, HPPA_WEG_WET0), ctx);
}

static void emit_stowe(const s8 wd, const s8 ws, s16 off,
			  stwuct hppa_jit_context *ctx, const u8 size,
			  const u8 mode)
{
	s8 dstweg;

	/* need to cawcuwate addwess since offset does not fit in 14 bits? */
	if (wewative_bits_ok(off, 14))
		dstweg = wd;
	ewse {
		/* need to use W1 hewe, since addiw puts wesuwt into W1 */
		dstweg = HPPA_WEG_W1;
		emit(hppa_addiw(off, wd), ctx);
		off = im11(off);
	}

	switch (size) {
	case BPF_B:
		emit(hppa_stb(ws, off, dstweg), ctx);
		bweak;
	case BPF_H:
		emit(hppa_sth(ws, off, dstweg), ctx);
		bweak;
	case BPF_W:
		emit(hppa_stw(ws, off, dstweg), ctx);
		bweak;
	case BPF_DW:
		if (off & 7) {
			emit(hppa_wdo(off, dstweg, HPPA_WEG_W1), ctx);
			emit(hppa64_std_im5(ws, 0, HPPA_WEG_W1), ctx);
		} ewse if (off >= -16 && off <= 15)
			emit(hppa64_std_im5(ws, off, dstweg), ctx);
		ewse
			emit(hppa64_std_im16(ws, off, dstweg), ctx);
		bweak;
	}
}

int bpf_jit_emit_insn(const stwuct bpf_insn *insn, stwuct hppa_jit_context *ctx,
		      boow extwa_pass)
{
	boow is64 = BPF_CWASS(insn->code) == BPF_AWU64 ||
		    BPF_CWASS(insn->code) == BPF_JMP;
	int s, e, wet, i = insn - ctx->pwog->insnsi;
	s64 paoff;
	stwuct bpf_pwog_aux *aux = ctx->pwog->aux;
	u8 wd = -1, ws = -1, code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;

	init_wegs(&wd, &ws, insn, ctx);

	switch (code) {
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
	case BPF_AWU64 | BPF_MOV | BPF_X:
		if (imm == 1) {
			/* Speciaw mov32 fow zext */
			emit_zext_32(wd, ctx);
			bweak;
		}
		if (!is64 && !aux->vewifiew_zext)
			emit_hppa64_zext32(ws, wd, ctx);
		ewse
			emit_hppa_copy(ws, wd, ctx);
		bweak;

	/* dst = dst OP swc */
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
                emit(hppa_add(wd, ws, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
                emit(hppa_sub(wd, ws, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_AND | BPF_X:
                emit(hppa_and(wd, ws, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
                emit(hppa_ow(wd, ws, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
                emit(hppa_xow(wd, ws, wd), ctx);
		if (!is64 && !aux->vewifiew_zext && ws != wd)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU64 | BPF_MUW | BPF_K:
		emit_imm(HPPA_WEG_T1, is64 ? (s64)(s32)imm : (u32)imm, HPPA_WEG_T2, ctx);
		ws = HPPA_WEG_T1;
		fawwthwough;
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_X:
		emit_caww_wibgcc_ww(__muwdi3, wd, ws, code, ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_K:
		emit_imm(HPPA_WEG_T1, is64 ? (s64)(s32)imm : (u32)imm, HPPA_WEG_T2, ctx);
		ws = HPPA_WEG_T1;
		fawwthwough;
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_DIV | BPF_X:
		emit_caww_wibgcc_ww(&hppa_div64, wd, ws, code, ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_MOD | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		emit_imm(HPPA_WEG_T1, is64 ? (s64)(s32)imm : (u32)imm, HPPA_WEG_T2, ctx);
		ws = HPPA_WEG_T1;
		fawwthwough;
	case BPF_AWU | BPF_MOD | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		emit_caww_wibgcc_ww(&hppa_div64_wem, wd, ws, code, ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;

	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_hppa64_sext32(ws, HPPA_WEG_T0, ctx);
		emit(hppa64_mtsawcm(HPPA_WEG_T0), ctx);
		if (is64)
			emit(hppa64_depdz_saw(wd, wd), ctx);
		ewse
			emit(hppa_depwz_saw(wd, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit(hppa_mtsaw(ws), ctx);
		if (is64)
			emit(hppa64_shwpd_saw(wd, wd), ctx);
		ewse
			emit(hppa_shwpw_saw(wd, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_X:
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit_hppa64_sext32(ws, HPPA_WEG_T0, ctx);
                emit(hppa64_mtsawcm(HPPA_WEG_T0), ctx);
		if (is64)
			emit(hppa_extwd_saw(wd, wd, 1), ctx);
		ewse
			emit(hppa_extwws_saw(wd, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;

	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
	case BPF_AWU64 | BPF_NEG:
		emit(hppa_sub(HPPA_WEG_ZEWO, wd, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;

	/* dst = BSWAP##imm(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_BE:
		switch (imm) {
		case 16:
			/* zewo-extend 16 bits into 64 bits */
			emit_hppa64_depd(HPPA_WEG_ZEWO, 63-16, 64-16, wd, 1, ctx);
			bweak;
		case 32:
			if (!aux->vewifiew_zext)
				emit_zext_32(wd, ctx);
			bweak;
		case 64:
			/* Do nothing */
			bweak;
		}
		bweak;

	case BPF_AWU | BPF_END | BPF_FWOM_WE:
		switch (imm) {
		case 16:
			emit(hppa_extwu(wd, 31 - 8, 8, HPPA_WEG_T1), ctx);
			emit(hppa_depwz(wd, 23, 8, HPPA_WEG_T1), ctx);
			emit(hppa_extwu(HPPA_WEG_T1, 31, 16, wd), ctx);
			emit_hppa64_extwd(HPPA_WEG_T1, 63, 16, wd, 0, ctx);
			bweak;
		case 32:
			emit(hppa_shwpw(wd, wd, 16, HPPA_WEG_T1), ctx);
			emit_hppa64_depd(HPPA_WEG_T1, 63-16, 8, HPPA_WEG_T1, 1, ctx);
			emit(hppa_shwpw(wd, HPPA_WEG_T1, 8, HPPA_WEG_T1), ctx);
			emit_hppa64_extwd(HPPA_WEG_T1, 63, 32, wd, 0, ctx);
			bweak;
		case 64:
			emit(hppa64_pewmh_3210(wd, HPPA_WEG_T1), ctx);
			emit(hppa64_hshw(HPPA_WEG_T1, 8, HPPA_WEG_T2), ctx);
			emit(hppa64_hshw_u(HPPA_WEG_T1, 8, HPPA_WEG_T1), ctx);
			emit(hppa_ow(HPPA_WEG_T2, HPPA_WEG_T1, wd), ctx);
			bweak;
		defauwt:
			pw_eww("bpf-jit: BPF_END imm %d invawid\n", imm);
			wetuwn -1;
		}
		bweak;

	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_MOV | BPF_K:
		emit_imm(wd, imm, HPPA_WEG_T2, ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;

	/* dst = dst OP imm */
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
		if (wewative_bits_ok(imm, 14)) {
			emit(hppa_wdo(imm, wd, wd), ctx);
		} ewse {
			emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
			emit(hppa_add(wd, HPPA_WEG_T1, wd), ctx);
		}
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
		if (wewative_bits_ok(-imm, 14)) {
			emit(hppa_wdo(-imm, wd, wd), ctx);
		} ewse {
			emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
			emit(hppa_sub(wd, HPPA_WEG_T1, wd), ctx);
		}
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
		emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
                emit(hppa_and(wd, HPPA_WEG_T1, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
		emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
                emit(hppa_ow(wd, HPPA_WEG_T1, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
		emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
                emit(hppa_xow(wd, HPPA_WEG_T1, wd), ctx);
		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
		if (imm != 0) {
			emit_hppa64_shwd(wd, imm, wd, ctx);
		}

		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
		if (imm != 0) {
			if (is64)
				emit_hppa64_shwd(wd, imm, wd, fawse, ctx);
			ewse
				emit_hppa64_shww(wd, imm, wd, fawse, ctx);
		}

		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_K:
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		if (imm != 0) {
			if (is64)
				emit_hppa64_shwd(wd, imm, wd, twue, ctx);
			ewse
				emit_hppa64_shww(wd, imm, wd, twue, ctx);
		}

		if (!is64 && !aux->vewifiew_zext)
			emit_zext_32(wd, ctx);
		bweak;

	/* JUMP off */
	case BPF_JMP | BPF_JA:
		paoff = hppa_offset(i, off, ctx);
		wet = emit_jump(paoff, fawse, ctx);
		if (wet)
			wetuwn wet;
		bweak;

	/* IF (dst COND swc) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_X:
		paoff = hppa_offset(i, off, ctx);
		if (!is64) {
			s = ctx->ninsns;
			if (is_signed_bpf_cond(BPF_OP(code)))
				emit_sext_32_wd_ws(&wd, &ws, ctx);
			ewse
				emit_zext_32_wd_ws(&wd, &ws, ctx);
			e = ctx->ninsns;

			/* Adjust fow extwa insns */
			paoff -= (e - s);
		}
		if (BPF_OP(code) == BPF_JSET) {
			/* Adjust fow and */
			paoff -= 1;
			emit(hppa_and(ws, wd, HPPA_WEG_T1), ctx);
			emit_bwanch(BPF_JNE, HPPA_WEG_T1, HPPA_WEG_ZEWO, paoff,
				    ctx);
		} ewse {
			emit_bwanch(BPF_OP(code), wd, ws, paoff, ctx);
		}
		bweak;

	/* IF (dst COND imm) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
		paoff = hppa_offset(i, off, ctx);
		s = ctx->ninsns;
		if (imm) {
			emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
			ws = HPPA_WEG_T1;
		} ewse {
			ws = HPPA_WEG_ZEWO;
		}
		if (!is64) {
			if (is_signed_bpf_cond(BPF_OP(code)))
				emit_sext_32_wd(&wd, ctx);
			ewse
				emit_zext_32_wd_t1(&wd, ctx);
		}
		e = ctx->ninsns;

		/* Adjust fow extwa insns */
		paoff -= (e - s);
		emit_bwanch(BPF_OP(code), wd, ws, paoff, ctx);
		bweak;
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
		paoff = hppa_offset(i, off, ctx);
		s = ctx->ninsns;
		emit_imm(HPPA_WEG_T1, imm, HPPA_WEG_T2, ctx);
		emit(hppa_and(HPPA_WEG_T1, wd, HPPA_WEG_T1), ctx);
		/* Fow jset32, we shouwd cweaw the uppew 32 bits of t1, but
		 * sign-extension is sufficient hewe and saves one instwuction,
		 * as t1 is used onwy in compawison against zewo.
		 */
		if (!is64 && imm < 0)
			emit_hppa64_sext32(HPPA_WEG_T1, HPPA_WEG_T1, ctx);
		e = ctx->ninsns;
		paoff -= (e - s);
		emit_bwanch(BPF_JNE, HPPA_WEG_T1, HPPA_WEG_ZEWO, paoff, ctx);
		bweak;
	/* function caww */
	case BPF_JMP | BPF_CAWW:
	{
		boow fixed_addw;
		u64 addw;

		wet = bpf_jit_get_func_addw(ctx->pwog, insn, extwa_pass,
					    &addw, &fixed_addw);
		if (wet < 0)
			wetuwn wet;

		WEG_SET_SEEN_AWW(ctx);
		emit_caww(addw, fixed_addw, ctx);
		bweak;
	}
	/* taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		emit_bpf_taiw_caww(i, ctx);
		bweak;

	/* function wetuwn */
	case BPF_JMP | BPF_EXIT:
		if (i == ctx->pwog->wen - 1)
			bweak;

		paoff = epiwogue_offset(ctx);
		wet = emit_jump(paoff, fawse, ctx);
		if (wet)
			wetuwn wet;
		bweak;

	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
	{
		stwuct bpf_insn insn1 = insn[1];
		u64 imm64 = (u64)insn1.imm << 32 | (u32)imm;
		if (bpf_pseudo_func(insn))
			imm64 = (uintptw_t)dewefewence_function_descwiptow((void*)imm64);
		emit_imm(wd, imm64, HPPA_WEG_T2, ctx);

		wetuwn 1;
	}

	/* WDX: dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_DW:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
	{
		u8 swcweg;

		/* need to cawcuwate addwess since offset does not fit in 14 bits? */
		if (wewative_bits_ok(off, 14))
			swcweg = ws;
		ewse {
			/* need to use W1 hewe, since addiw puts wesuwt into W1 */
			swcweg = HPPA_WEG_W1;
			BUG_ON(ws == HPPA_WEG_W1);
			BUG_ON(wd == HPPA_WEG_W1);
			emit(hppa_addiw(off, ws), ctx);
			off = im11(off);
		}

		switch (BPF_SIZE(code)) {
		case BPF_B:
			emit(hppa_wdb(off, swcweg, wd), ctx);
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;
		case BPF_H:
			emit(hppa_wdh(off, swcweg, wd), ctx);
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;
		case BPF_W:
			emit(hppa_wdw(off, swcweg, wd), ctx);
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;
		case BPF_DW:
			if (off & 7) {
				emit(hppa_wdo(off, swcweg, HPPA_WEG_W1), ctx);
				emit(hppa64_wdd_weg(HPPA_WEG_ZEWO, HPPA_WEG_W1, wd), ctx);
			} ewse if (off >= -16 && off <= 15)
				emit(hppa64_wdd_im5(off, swcweg, wd), ctx);
			ewse
				emit(hppa64_wdd_im16(off, swcweg, wd), ctx);
			bweak;
		}
		bweak;
	}
	/* specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;

	/* ST: *(size *)(dst + off) = imm */
	/* STX: *(size *)(dst + off) = swc */
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_DW:

	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_DW:
		if (BPF_CWASS(code) == BPF_ST) {
			emit_imm(HPPA_WEG_T2, imm, HPPA_WEG_T1, ctx);
			ws = HPPA_WEG_T2;
		}

		emit_stowe(wd, ws, off, ctx, BPF_SIZE(code), BPF_MODE(code));
		bweak;

	case BPF_STX | BPF_ATOMIC | BPF_W:
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		pw_info_once(
			"bpf-jit: not suppowted: atomic opewation %02x ***\n",
			insn->imm);
		wetuwn -EFAUWT;

	defauwt:
		pw_eww("bpf-jit: unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void bpf_jit_buiwd_pwowogue(stwuct hppa_jit_context *ctx)
{
	int bpf_stack_adjust, stack_adjust, i;
	unsigned wong addw;
	s8 weg;

	/*
	 * stack on hppa gwows up, so if taiw cawws awe used we need to
	 * awwocate the maximum stack size
	 */
	if (WEG_AWW_SEEN(ctx))
		bpf_stack_adjust = MAX_BPF_STACK;
	ewse
		bpf_stack_adjust = ctx->pwog->aux->stack_depth;
	bpf_stack_adjust = wound_up(bpf_stack_adjust, STACK_AWIGN);

	stack_adjust = FWAME_SIZE + bpf_stack_adjust;
	stack_adjust = wound_up(stack_adjust, STACK_AWIGN);

	/*
	 * NOTE: We constwuct an Ewf64_Fdesc descwiptow hewe.
	 * The fiwst 4 wowds initiawize the TCC and compawes them.
	 * Then fowwows the viwtuaw addwess of the eBPF function,
	 * and the gp fow this function.
	 *
	 * The fiwst instwuction sets the taiw-caww-countew (TCC) wegistew.
	 * This instwuction is skipped by taiw cawws.
	 * Use a tempowawy wegistew instead of a cawwew-saved wegistew initiawwy.
	 */
	WEG_FOWCE_SEEN(ctx, HPPA_WEG_TCC_IN_INIT);
	emit(hppa_wdi(MAX_TAIW_CAWW_CNT, HPPA_WEG_TCC_IN_INIT), ctx);

	/*
	 * Skip aww initiawizations when cawwed as BPF TAIW caww.
	 */
	emit(hppa_wdi(MAX_TAIW_CAWW_CNT, HPPA_WEG_W1), ctx);
	emit(hppa_beq(HPPA_WEG_TCC_IN_INIT, HPPA_WEG_W1, 6 - HPPA_BWANCH_DISPWACEMENT), ctx);
	emit(hppa64_bw_wong(ctx->pwowogue_wen - 3 - HPPA_BWANCH_DISPWACEMENT), ctx);

	/* stowe entwy addwess of this eBPF function */
	addw = (uintptw_t) &ctx->insns[0];
	emit(addw >> 32, ctx);
	emit(addw & 0xffffffff, ctx);

	/* stowe gp of this eBPF function */
	asm("copy %%w27,%0" : "=w" (addw) );
	emit(addw >> 32, ctx);
	emit(addw & 0xffffffff, ctx);

	/* Set up hppa stack fwame. */
	emit_hppa_copy(HPPA_WEG_SP, HPPA_WEG_W1, ctx);
	emit(hppa_wdo(stack_adjust, HPPA_WEG_SP, HPPA_WEG_SP), ctx);
	emit(hppa64_std_im5 (HPPA_WEG_W1, -WEG_SIZE, HPPA_WEG_SP), ctx);
	emit(hppa64_std_im16(HPPA_WEG_WP, -2*WEG_SIZE, HPPA_WEG_SP), ctx);

	/* Save cawwee-save wegistews. */
	fow (i = 3; i <= 15; i++) {
		if (OPTIMIZE_HPPA && !WEG_WAS_SEEN(ctx, HPPA_W(i)))
			continue;
		emit(hppa64_std_im16(HPPA_W(i), -WEG_SIZE * i, HPPA_WEG_SP), ctx);
	}

	/* woad function pawametews; woad aww if we use taiw functions */
	#define WOAD_PAWAM(awg, dst) \
		if (WEG_WAS_SEEN(ctx, wegmap[dst]) ||	\
		    WEG_WAS_SEEN(ctx, HPPA_WEG_TCC))	\
			emit_hppa_copy(awg, wegmap[dst], ctx)
	WOAD_PAWAM(HPPA_WEG_AWG0, BPF_WEG_1);
	WOAD_PAWAM(HPPA_WEG_AWG1, BPF_WEG_2);
	WOAD_PAWAM(HPPA_WEG_AWG2, BPF_WEG_3);
	WOAD_PAWAM(HPPA_WEG_AWG3, BPF_WEG_4);
	WOAD_PAWAM(HPPA_WEG_AWG4, BPF_WEG_5);
	#undef WOAD_PAWAM

	WEG_FOWCE_SEEN(ctx, HPPA_WEG_T0);
	WEG_FOWCE_SEEN(ctx, HPPA_WEG_T1);
	WEG_FOWCE_SEEN(ctx, HPPA_WEG_T2);

	/*
	 * Now weawwy set the taiw caww countew (TCC) wegistew.
	 */
	if (WEG_WAS_SEEN(ctx, HPPA_WEG_TCC))
		emit(hppa_wdi(MAX_TAIW_CAWW_CNT, HPPA_WEG_TCC), ctx);

	/*
	 * Save epiwogue function pointew fow outew TCC caww chain.
	 * The main TCC caww stowes the finaw WP on stack.
	 */
	addw = (uintptw_t) &ctx->insns[ctx->epiwogue_offset];
	/* skip fiwst two instwuctions which jump to exit */
	addw += 2 * HPPA_INSN_SIZE;
	emit_imm(HPPA_WEG_T2, addw, HPPA_WEG_T1, ctx);
	emit(EXIT_PTW_STOWE(HPPA_WEG_T2), ctx);

	/* Set up BPF fwame pointew. */
	weg = wegmap[BPF_WEG_FP];	/* -> HPPA_WEG_FP */
	if (WEG_WAS_SEEN(ctx, weg)) {
		emit(hppa_wdo(-FWAME_SIZE, HPPA_WEG_SP, weg), ctx);
	}
}

void bpf_jit_buiwd_epiwogue(stwuct hppa_jit_context *ctx)
{
	__buiwd_epiwogue(fawse, ctx);
}

boow bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn twue;
}
