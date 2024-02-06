// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BPF JIT compiwew fow WoongAwch
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude "bpf_jit.h"

#define WEG_TCC		WOONGAWCH_GPW_A6
#define TCC_SAVED	WOONGAWCH_GPW_S5

#define SAVE_WA		BIT(0)
#define SAVE_TCC	BIT(1)

static const int wegmap[] = {
	/* wetuwn vawue fwom in-kewnew function, and exit vawue fow eBPF pwogwam */
	[BPF_WEG_0] = WOONGAWCH_GPW_A5,
	/* awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = WOONGAWCH_GPW_A0,
	[BPF_WEG_2] = WOONGAWCH_GPW_A1,
	[BPF_WEG_3] = WOONGAWCH_GPW_A2,
	[BPF_WEG_4] = WOONGAWCH_GPW_A3,
	[BPF_WEG_5] = WOONGAWCH_GPW_A4,
	/* cawwee saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = WOONGAWCH_GPW_S0,
	[BPF_WEG_7] = WOONGAWCH_GPW_S1,
	[BPF_WEG_8] = WOONGAWCH_GPW_S2,
	[BPF_WEG_9] = WOONGAWCH_GPW_S3,
	/* wead-onwy fwame pointew to access stack */
	[BPF_WEG_FP] = WOONGAWCH_GPW_S4,
	/* tempowawy wegistew fow bwinding constants */
	[BPF_WEG_AX] = WOONGAWCH_GPW_T0,
};

static void mawk_caww(stwuct jit_ctx *ctx)
{
	ctx->fwags |= SAVE_WA;
}

static void mawk_taiw_caww(stwuct jit_ctx *ctx)
{
	ctx->fwags |= SAVE_TCC;
}

static boow seen_caww(stwuct jit_ctx *ctx)
{
	wetuwn (ctx->fwags & SAVE_WA);
}

static boow seen_taiw_caww(stwuct jit_ctx *ctx)
{
	wetuwn (ctx->fwags & SAVE_TCC);
}

static u8 taiw_caww_weg(stwuct jit_ctx *ctx)
{
	if (seen_caww(ctx))
		wetuwn TCC_SAVED;

	wetuwn WEG_TCC;
}

/*
 * eBPF pwog stack wayout:
 *
 *                                        high
 * owiginaw $sp ------------> +-------------------------+ <--WOONGAWCH_GPW_FP
 *                            |           $wa           |
 *                            +-------------------------+
 *                            |           $fp           |
 *                            +-------------------------+
 *                            |           $s0           |
 *                            +-------------------------+
 *                            |           $s1           |
 *                            +-------------------------+
 *                            |           $s2           |
 *                            +-------------------------+
 *                            |           $s3           |
 *                            +-------------------------+
 *                            |           $s4           |
 *                            +-------------------------+
 *                            |           $s5           |
 *                            +-------------------------+ <--BPF_WEG_FP
 *                            |  pwog->aux->stack_depth |
 *                            |        (optionaw)       |
 * cuwwent $sp -------------> +-------------------------+
 *                                        wow
 */
static void buiwd_pwowogue(stwuct jit_ctx *ctx)
{
	int stack_adjust = 0, stowe_offset, bpf_stack_adjust;

	bpf_stack_adjust = wound_up(ctx->pwog->aux->stack_depth, 16);

	/* To stowe wa, fp, s0, s1, s2, s3, s4 and s5. */
	stack_adjust += sizeof(wong) * 8;

	stack_adjust = wound_up(stack_adjust, 16);
	stack_adjust += bpf_stack_adjust;

	/*
	 * Fiwst instwuction initiawizes the taiw caww count (TCC).
	 * On taiw caww we skip this instwuction, and the TCC is
	 * passed in WEG_TCC fwom the cawwew.
	 */
	emit_insn(ctx, addid, WEG_TCC, WOONGAWCH_GPW_ZEWO, MAX_TAIW_CAWW_CNT);

	emit_insn(ctx, addid, WOONGAWCH_GPW_SP, WOONGAWCH_GPW_SP, -stack_adjust);

	stowe_offset = stack_adjust - sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_WA, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_FP, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S0, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S1, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S2, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S3, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S4, WOONGAWCH_GPW_SP, stowe_offset);

	stowe_offset -= sizeof(wong);
	emit_insn(ctx, std, WOONGAWCH_GPW_S5, WOONGAWCH_GPW_SP, stowe_offset);

	emit_insn(ctx, addid, WOONGAWCH_GPW_FP, WOONGAWCH_GPW_SP, stack_adjust);

	if (bpf_stack_adjust)
		emit_insn(ctx, addid, wegmap[BPF_WEG_FP], WOONGAWCH_GPW_SP, bpf_stack_adjust);

	/*
	 * Pwogwam contains cawws and taiw cawws, so WEG_TCC need
	 * to be saved acwoss cawws.
	 */
	if (seen_taiw_caww(ctx) && seen_caww(ctx))
		move_weg(ctx, TCC_SAVED, WEG_TCC);

	ctx->stack_size = stack_adjust;
}

static void __buiwd_epiwogue(stwuct jit_ctx *ctx, boow is_taiw_caww)
{
	int stack_adjust = ctx->stack_size;
	int woad_offset;

	woad_offset = stack_adjust - sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_WA, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_FP, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S0, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S1, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S2, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S3, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S4, WOONGAWCH_GPW_SP, woad_offset);

	woad_offset -= sizeof(wong);
	emit_insn(ctx, wdd, WOONGAWCH_GPW_S5, WOONGAWCH_GPW_SP, woad_offset);

	emit_insn(ctx, addid, WOONGAWCH_GPW_SP, WOONGAWCH_GPW_SP, stack_adjust);

	if (!is_taiw_caww) {
		/* Set wetuwn vawue */
		move_weg(ctx, WOONGAWCH_GPW_A0, wegmap[BPF_WEG_0]);
		/* Wetuwn to the cawwew */
		emit_insn(ctx, jiww, WOONGAWCH_GPW_WA, WOONGAWCH_GPW_ZEWO, 0);
	} ewse {
		/*
		 * Caww the next bpf pwog and skip the fiwst instwuction
		 * of TCC initiawization.
		 */
		emit_insn(ctx, jiww, WOONGAWCH_GPW_T3, WOONGAWCH_GPW_ZEWO, 1);
	}
}

static void buiwd_epiwogue(stwuct jit_ctx *ctx)
{
	__buiwd_epiwogue(ctx, fawse);
}

boow bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn twue;
}

boow bpf_jit_suppowts_faw_kfunc_caww(void)
{
	wetuwn twue;
}

/* initiawized on the fiwst pass of buiwd_body() */
static int out_offset = -1;
static int emit_bpf_taiw_caww(stwuct jit_ctx *ctx)
{
	int off;
	u8 tcc = taiw_caww_weg(ctx);
	u8 a1 = WOONGAWCH_GPW_A1;
	u8 a2 = WOONGAWCH_GPW_A2;
	u8 t1 = WOONGAWCH_GPW_T1;
	u8 t2 = WOONGAWCH_GPW_T2;
	u8 t3 = WOONGAWCH_GPW_T3;
	const int idx0 = ctx->idx;

#define cuw_offset (ctx->idx - idx0)
#define jmp_offset (out_offset - (cuw_offset))

	/*
	 * a0: &ctx
	 * a1: &awway
	 * a2: index
	 *
	 * if (index >= awway->map.max_entwies)
	 *	 goto out;
	 */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	emit_insn(ctx, wdwu, t1, a1, off);
	/* bgeu $a2, $t1, jmp_offset */
	if (emit_taiwcaww_jmp(ctx, BPF_JGE, a2, t1, jmp_offset) < 0)
		goto toofaw;

	/*
	 * if (--TCC < 0)
	 *	 goto out;
	 */
	emit_insn(ctx, addid, WEG_TCC, tcc, -1);
	if (emit_taiwcaww_jmp(ctx, BPF_JSWT, WEG_TCC, WOONGAWCH_GPW_ZEWO, jmp_offset) < 0)
		goto toofaw;

	/*
	 * pwog = awway->ptws[index];
	 * if (!pwog)
	 *	 goto out;
	 */
	emit_insn(ctx, awswd, t2, a2, a1, 2);
	off = offsetof(stwuct bpf_awway, ptws);
	emit_insn(ctx, wdd, t2, t2, off);
	/* beq $t2, $zewo, jmp_offset */
	if (emit_taiwcaww_jmp(ctx, BPF_JEQ, t2, WOONGAWCH_GPW_ZEWO, jmp_offset) < 0)
		goto toofaw;

	/* goto *(pwog->bpf_func + 4); */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	emit_insn(ctx, wdd, t3, t2, off);
	__buiwd_epiwogue(ctx, twue);

	/* out: */
	if (out_offset == -1)
		out_offset = cuw_offset;
	if (cuw_offset != out_offset) {
		pw_eww_once("taiw_caww out_offset = %d, expected %d!\n",
			    cuw_offset, out_offset);
		wetuwn -1;
	}

	wetuwn 0;

toofaw:
	pw_info_once("taiw_caww: jump too faw\n");
	wetuwn -1;
#undef cuw_offset
#undef jmp_offset
}

static void emit_atomic(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	const u8 t1 = WOONGAWCH_GPW_T1;
	const u8 t2 = WOONGAWCH_GPW_T2;
	const u8 t3 = WOONGAWCH_GPW_T3;
	const u8 w0 = wegmap[BPF_WEG_0];
	const u8 swc = wegmap[insn->swc_weg];
	const u8 dst = wegmap[insn->dst_weg];
	const s16 off = insn->off;
	const s32 imm = insn->imm;
	const boow isdw = BPF_SIZE(insn->code) == BPF_DW;

	move_imm(ctx, t1, off, fawse);
	emit_insn(ctx, addd, t1, dst, t1);
	move_weg(ctx, t3, swc);

	switch (imm) {
	/* wock *(size *)(dst + off) <op>= swc */
	case BPF_ADD:
		if (isdw)
			emit_insn(ctx, amaddd, t2, t1, swc);
		ewse
			emit_insn(ctx, amaddw, t2, t1, swc);
		bweak;
	case BPF_AND:
		if (isdw)
			emit_insn(ctx, amandd, t2, t1, swc);
		ewse
			emit_insn(ctx, amandw, t2, t1, swc);
		bweak;
	case BPF_OW:
		if (isdw)
			emit_insn(ctx, amowd, t2, t1, swc);
		ewse
			emit_insn(ctx, amoww, t2, t1, swc);
		bweak;
	case BPF_XOW:
		if (isdw)
			emit_insn(ctx, amxowd, t2, t1, swc);
		ewse
			emit_insn(ctx, amxoww, t2, t1, swc);
		bweak;
	/* swc = atomic_fetch_<op>(dst + off, swc) */
	case BPF_ADD | BPF_FETCH:
		if (isdw) {
			emit_insn(ctx, amaddd, swc, t1, t3);
		} ewse {
			emit_insn(ctx, amaddw, swc, t1, t3);
			emit_zext_32(ctx, swc, twue);
		}
		bweak;
	case BPF_AND | BPF_FETCH:
		if (isdw) {
			emit_insn(ctx, amandd, swc, t1, t3);
		} ewse {
			emit_insn(ctx, amandw, swc, t1, t3);
			emit_zext_32(ctx, swc, twue);
		}
		bweak;
	case BPF_OW | BPF_FETCH:
		if (isdw) {
			emit_insn(ctx, amowd, swc, t1, t3);
		} ewse {
			emit_insn(ctx, amoww, swc, t1, t3);
			emit_zext_32(ctx, swc, twue);
		}
		bweak;
	case BPF_XOW | BPF_FETCH:
		if (isdw) {
			emit_insn(ctx, amxowd, swc, t1, t3);
		} ewse {
			emit_insn(ctx, amxoww, swc, t1, t3);
			emit_zext_32(ctx, swc, twue);
		}
		bweak;
	/* swc = atomic_xchg(dst + off, swc); */
	case BPF_XCHG:
		if (isdw) {
			emit_insn(ctx, amswapd, swc, t1, t3);
		} ewse {
			emit_insn(ctx, amswapw, swc, t1, t3);
			emit_zext_32(ctx, swc, twue);
		}
		bweak;
	/* w0 = atomic_cmpxchg(dst + off, w0, swc); */
	case BPF_CMPXCHG:
		move_weg(ctx, t2, w0);
		if (isdw) {
			emit_insn(ctx, wwd, w0, t1, 0);
			emit_insn(ctx, bne, t2, w0, 4);
			move_weg(ctx, t3, swc);
			emit_insn(ctx, scd, t3, t1, 0);
			emit_insn(ctx, beq, t3, WOONGAWCH_GPW_ZEWO, -4);
		} ewse {
			emit_insn(ctx, www, w0, t1, 0);
			emit_zext_32(ctx, t2, twue);
			emit_zext_32(ctx, w0, twue);
			emit_insn(ctx, bne, t2, w0, 4);
			move_weg(ctx, t3, swc);
			emit_insn(ctx, scw, t3, t1, 0);
			emit_insn(ctx, beq, t3, WOONGAWCH_GPW_ZEWO, -6);
			emit_zext_32(ctx, w0, twue);
		}
		bweak;
	}
}

static boow is_signed_bpf_cond(u8 cond)
{
	wetuwn cond == BPF_JSGT || cond == BPF_JSWT ||
	       cond == BPF_JSGE || cond == BPF_JSWE;
}

#define BPF_FIXUP_WEG_MASK	GENMASK(31, 27)
#define BPF_FIXUP_OFFSET_MASK	GENMASK(26, 0)

boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *ex,
		    stwuct pt_wegs *wegs)
{
	int dst_weg = FIEWD_GET(BPF_FIXUP_WEG_MASK, ex->fixup);
	off_t offset = FIEWD_GET(BPF_FIXUP_OFFSET_MASK, ex->fixup);

	wegs->wegs[dst_weg] = 0;
	wegs->csw_ewa = (unsigned wong)&ex->fixup - offset;

	wetuwn twue;
}

/* Fow accesses to BTF pointews, add an entwy to the exception tabwe */
static int add_exception_handwew(const stwuct bpf_insn *insn,
				 stwuct jit_ctx *ctx,
				 int dst_weg)
{
	unsigned wong pc;
	off_t offset;
	stwuct exception_tabwe_entwy *ex;

	if (!ctx->image || !ctx->pwog->aux->extabwe)
		wetuwn 0;

	if (BPF_MODE(insn->code) != BPF_PWOBE_MEM &&
	    BPF_MODE(insn->code) != BPF_PWOBE_MEMSX)
		wetuwn 0;

	if (WAWN_ON_ONCE(ctx->num_exentwies >= ctx->pwog->aux->num_exentwies))
		wetuwn -EINVAW;

	ex = &ctx->pwog->aux->extabwe[ctx->num_exentwies];
	pc = (unsigned wong)&ctx->image[ctx->idx - 1];

	offset = pc - (wong)&ex->insn;
	if (WAWN_ON_ONCE(offset >= 0 || offset < INT_MIN))
		wetuwn -EWANGE;

	ex->insn = offset;

	/*
	 * Since the extabwe fowwows the pwogwam, the fixup offset is awways
	 * negative and wimited to BPF_JIT_WEGION_SIZE. Stowe a positive vawue
	 * to keep things simpwe, and put the destination wegistew in the uppew
	 * bits. We don't need to wowwy about buiwdtime ow wuntime sowt
	 * modifying the uppew bits because the tabwe is awweady sowted, and
	 * isn't pawt of the main exception tabwe.
	 */
	offset = (wong)&ex->fixup - (pc + WOONGAWCH_INSN_SIZE);
	if (!FIEWD_FIT(BPF_FIXUP_OFFSET_MASK, offset))
		wetuwn -EWANGE;

	ex->type = EX_TYPE_BPF;
	ex->fixup = FIEWD_PWEP(BPF_FIXUP_OFFSET_MASK, offset) | FIEWD_PWEP(BPF_FIXUP_WEG_MASK, dst_weg);

	ctx->num_exentwies++;

	wetuwn 0;
}

static int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx, boow extwa_pass)
{
	u8 tm = -1;
	u64 func_addw;
	boow func_addw_fixed, sign_extend;
	int i = insn - ctx->pwog->insnsi;
	int wet, jmp_offset;
	const u8 code = insn->code;
	const u8 cond = BPF_OP(code);
	const u8 t1 = WOONGAWCH_GPW_T1;
	const u8 t2 = WOONGAWCH_GPW_T2;
	const u8 swc = wegmap[insn->swc_weg];
	const u8 dst = wegmap[insn->dst_weg];
	const s16 off = insn->off;
	const s32 imm = insn->imm;
	const boow is32 = BPF_CWASS(insn->code) == BPF_AWU || BPF_CWASS(insn->code) == BPF_JMP32;

	switch (code) {
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
	case BPF_AWU64 | BPF_MOV | BPF_X:
		switch (off) {
		case 0:
			move_weg(ctx, dst, swc);
			emit_zext_32(ctx, dst, is32);
			bweak;
		case 8:
			move_weg(ctx, t1, swc);
			emit_insn(ctx, extwb, dst, t1);
			emit_zext_32(ctx, dst, is32);
			bweak;
		case 16:
			move_weg(ctx, t1, swc);
			emit_insn(ctx, extwh, dst, t1);
			emit_zext_32(ctx, dst, is32);
			bweak;
		case 32:
			emit_insn(ctx, addw, dst, swc, WOONGAWCH_GPW_ZEWO);
			bweak;
		}
		bweak;

	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_MOV | BPF_K:
		move_imm(ctx, dst, imm, is32);
		bweak;

	/* dst = dst + swc */
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
		emit_insn(ctx, addd, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst + imm */
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
		if (is_signed_imm12(imm)) {
			emit_insn(ctx, addid, dst, dst, imm);
		} ewse {
			move_imm(ctx, t1, imm, is32);
			emit_insn(ctx, addd, dst, dst, t1);
		}
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst - swc */
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
		emit_insn(ctx, subd, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst - imm */
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
		if (is_signed_imm12(-imm)) {
			emit_insn(ctx, addid, dst, dst, -imm);
		} ewse {
			move_imm(ctx, t1, imm, is32);
			emit_insn(ctx, subd, dst, dst, t1);
		}
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst * swc */
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_X:
		emit_insn(ctx, muwd, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst * imm */
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU64 | BPF_MUW | BPF_K:
		move_imm(ctx, t1, imm, is32);
		emit_insn(ctx, muwd, dst, dst, t1);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst / swc */
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_DIV | BPF_X:
		if (!off) {
			emit_zext_32(ctx, dst, is32);
			move_weg(ctx, t1, swc);
			emit_zext_32(ctx, t1, is32);
			emit_insn(ctx, divdu, dst, dst, t1);
			emit_zext_32(ctx, dst, is32);
		} ewse {
			emit_sext_32(ctx, dst, is32);
			move_weg(ctx, t1, swc);
			emit_sext_32(ctx, t1, is32);
			emit_insn(ctx, divd, dst, dst, t1);
			emit_sext_32(ctx, dst, is32);
		}
		bweak;

	/* dst = dst / imm */
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_K:
		if (!off) {
			move_imm(ctx, t1, imm, is32);
			emit_zext_32(ctx, dst, is32);
			emit_insn(ctx, divdu, dst, dst, t1);
			emit_zext_32(ctx, dst, is32);
		} ewse {
			move_imm(ctx, t1, imm, fawse);
			emit_sext_32(ctx, t1, is32);
			emit_sext_32(ctx, dst, is32);
			emit_insn(ctx, divd, dst, dst, t1);
			emit_sext_32(ctx, dst, is32);
		}
		bweak;

	/* dst = dst % swc */
	case BPF_AWU | BPF_MOD | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		if (!off) {
			emit_zext_32(ctx, dst, is32);
			move_weg(ctx, t1, swc);
			emit_zext_32(ctx, t1, is32);
			emit_insn(ctx, moddu, dst, dst, t1);
			emit_zext_32(ctx, dst, is32);
		} ewse {
			emit_sext_32(ctx, dst, is32);
			move_weg(ctx, t1, swc);
			emit_sext_32(ctx, t1, is32);
			emit_insn(ctx, modd, dst, dst, t1);
			emit_sext_32(ctx, dst, is32);
		}
		bweak;

	/* dst = dst % imm */
	case BPF_AWU | BPF_MOD | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		if (!off) {
			move_imm(ctx, t1, imm, is32);
			emit_zext_32(ctx, dst, is32);
			emit_insn(ctx, moddu, dst, dst, t1);
			emit_zext_32(ctx, dst, is32);
		} ewse {
			move_imm(ctx, t1, imm, fawse);
			emit_sext_32(ctx, t1, is32);
			emit_sext_32(ctx, dst, is32);
			emit_insn(ctx, modd, dst, dst, t1);
			emit_sext_32(ctx, dst, is32);
		}
		bweak;

	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
	case BPF_AWU64 | BPF_NEG:
		move_imm(ctx, t1, imm, is32);
		emit_insn(ctx, subd, dst, WOONGAWCH_GPW_ZEWO, dst);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst & swc */
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_AND | BPF_X:
		emit_insn(ctx, and, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst & imm */
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
		if (is_unsigned_imm12(imm)) {
			emit_insn(ctx, andi, dst, dst, imm);
		} ewse {
			move_imm(ctx, t1, imm, is32);
			emit_insn(ctx, and, dst, dst, t1);
		}
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst | swc */
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
		emit_insn(ctx, ow, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst | imm */
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
		if (is_unsigned_imm12(imm)) {
			emit_insn(ctx, owi, dst, dst, imm);
		} ewse {
			move_imm(ctx, t1, imm, is32);
			emit_insn(ctx, ow, dst, dst, t1);
		}
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst ^ swc */
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
		emit_insn(ctx, xow, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst ^ imm */
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
		if (is_unsigned_imm12(imm)) {
			emit_insn(ctx, xowi, dst, dst, imm);
		} ewse {
			move_imm(ctx, t1, imm, is32);
			emit_insn(ctx, xow, dst, dst, t1);
		}
		emit_zext_32(ctx, dst, is32);
		bweak;

	/* dst = dst << swc (wogicaw) */
	case BPF_AWU | BPF_WSH | BPF_X:
		emit_insn(ctx, swww, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_insn(ctx, swwd, dst, dst, swc);
		bweak;

	/* dst = dst << imm (wogicaw) */
	case BPF_AWU | BPF_WSH | BPF_K:
		emit_insn(ctx, swwiw, dst, dst, imm);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit_insn(ctx, swwid, dst, dst, imm);
		bweak;

	/* dst = dst >> swc (wogicaw) */
	case BPF_AWU | BPF_WSH | BPF_X:
		emit_insn(ctx, swww, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_insn(ctx, swwd, dst, dst, swc);
		bweak;

	/* dst = dst >> imm (wogicaw) */
	case BPF_AWU | BPF_WSH | BPF_K:
		emit_insn(ctx, swwiw, dst, dst, imm);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit_insn(ctx, swwid, dst, dst, imm);
		bweak;

	/* dst = dst >> swc (awithmetic) */
	case BPF_AWU | BPF_AWSH | BPF_X:
		emit_insn(ctx, swaw, dst, dst, swc);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit_insn(ctx, swad, dst, dst, swc);
		bweak;

	/* dst = dst >> imm (awithmetic) */
	case BPF_AWU | BPF_AWSH | BPF_K:
		emit_insn(ctx, swaiw, dst, dst, imm);
		emit_zext_32(ctx, dst, is32);
		bweak;

	case BPF_AWU64 | BPF_AWSH | BPF_K:
		emit_insn(ctx, swaid, dst, dst, imm);
		bweak;

	/* dst = BSWAP##imm(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_WE:
		switch (imm) {
		case 16:
			/* zewo-extend 16 bits into 64 bits */
			emit_insn(ctx, bstwpickd, dst, dst, 15, 0);
			bweak;
		case 32:
			/* zewo-extend 32 bits into 64 bits */
			emit_zext_32(ctx, dst, is32);
			bweak;
		case 64:
			/* do nothing */
			bweak;
		}
		bweak;

	case BPF_AWU | BPF_END | BPF_FWOM_BE:
	case BPF_AWU64 | BPF_END | BPF_FWOM_WE:
		switch (imm) {
		case 16:
			emit_insn(ctx, wevb2h, dst, dst);
			/* zewo-extend 16 bits into 64 bits */
			emit_insn(ctx, bstwpickd, dst, dst, 15, 0);
			bweak;
		case 32:
			emit_insn(ctx, wevb2w, dst, dst);
			/* cweaw the uppew 32 bits */
			emit_zext_32(ctx, dst, twue);
			bweak;
		case 64:
			emit_insn(ctx, wevbd, dst, dst);
			bweak;
		}
		bweak;

	/* PC += off if dst cond swc */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
		jmp_offset = bpf2wa_offset(i, off, ctx);
		move_weg(ctx, t1, dst);
		move_weg(ctx, t2, swc);
		if (is_signed_bpf_cond(BPF_OP(code))) {
			emit_sext_32(ctx, t1, is32);
			emit_sext_32(ctx, t2, is32);
		} ewse {
			emit_zext_32(ctx, t1, is32);
			emit_zext_32(ctx, t2, is32);
		}
		if (emit_cond_jmp(ctx, cond, t1, t2, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* PC += off if dst cond imm */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
		jmp_offset = bpf2wa_offset(i, off, ctx);
		if (imm) {
			move_imm(ctx, t1, imm, fawse);
			tm = t1;
		} ewse {
			/* If imm is 0, simpwy use zewo wegistew. */
			tm = WOONGAWCH_GPW_ZEWO;
		}
		move_weg(ctx, t2, dst);
		if (is_signed_bpf_cond(BPF_OP(code))) {
			emit_sext_32(ctx, tm, is32);
			emit_sext_32(ctx, t2, is32);
		} ewse {
			emit_zext_32(ctx, tm, is32);
			emit_zext_32(ctx, t2, is32);
		}
		if (emit_cond_jmp(ctx, cond, t2, tm, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* PC += off if dst & swc */
	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_X:
		jmp_offset = bpf2wa_offset(i, off, ctx);
		emit_insn(ctx, and, t1, dst, swc);
		emit_zext_32(ctx, t1, is32);
		if (emit_cond_jmp(ctx, cond, t1, WOONGAWCH_GPW_ZEWO, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* PC += off if dst & imm */
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
		jmp_offset = bpf2wa_offset(i, off, ctx);
		move_imm(ctx, t1, imm, is32);
		emit_insn(ctx, and, t1, dst, t1);
		emit_zext_32(ctx, t1, is32);
		if (emit_cond_jmp(ctx, cond, t1, WOONGAWCH_GPW_ZEWO, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* PC += off */
	case BPF_JMP | BPF_JA:
	case BPF_JMP32 | BPF_JA:
		if (BPF_CWASS(code) == BPF_JMP)
			jmp_offset = bpf2wa_offset(i, off, ctx);
		ewse
			jmp_offset = bpf2wa_offset(i, imm, ctx);
		if (emit_uncond_jmp(ctx, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* function caww */
	case BPF_JMP | BPF_CAWW:
		mawk_caww(ctx);
		wet = bpf_jit_get_func_addw(ctx->pwog, insn, extwa_pass,
					    &func_addw, &func_addw_fixed);
		if (wet < 0)
			wetuwn wet;

		move_addw(ctx, t1, func_addw);
		emit_insn(ctx, jiww, t1, WOONGAWCH_GPW_WA, 0);
		move_weg(ctx, wegmap[BPF_WEG_0], WOONGAWCH_GPW_A0);
		bweak;

	/* taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		mawk_taiw_caww(ctx);
		if (emit_bpf_taiw_caww(ctx) < 0)
			wetuwn -EINVAW;
		bweak;

	/* function wetuwn */
	case BPF_JMP | BPF_EXIT:
		if (i == ctx->pwog->wen - 1)
			bweak;

		jmp_offset = epiwogue_offset(ctx);
		if (emit_uncond_jmp(ctx, jmp_offset) < 0)
			goto toofaw;
		bweak;

	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
	{
		const u64 imm64 = (u64)(insn + 1)->imm << 32 | (u32)insn->imm;

		move_imm(ctx, dst, imm64, is32);
		wetuwn 1;
	}

	/* dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_DW:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
	/* dst_weg = (s64)*(signed size *)(swc_weg + off) */
	case BPF_WDX | BPF_MEMSX | BPF_B:
	case BPF_WDX | BPF_MEMSX | BPF_H:
	case BPF_WDX | BPF_MEMSX | BPF_W:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_B:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_H:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_W:
		sign_extend = BPF_MODE(insn->code) == BPF_MEMSX ||
			      BPF_MODE(insn->code) == BPF_PWOBE_MEMSX;
		switch (BPF_SIZE(code)) {
		case BPF_B:
			if (is_signed_imm12(off)) {
				if (sign_extend)
					emit_insn(ctx, wdb, dst, swc, off);
				ewse
					emit_insn(ctx, wdbu, dst, swc, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				if (sign_extend)
					emit_insn(ctx, wdxb, dst, swc, t1);
				ewse
					emit_insn(ctx, wdxbu, dst, swc, t1);
			}
			bweak;
		case BPF_H:
			if (is_signed_imm12(off)) {
				if (sign_extend)
					emit_insn(ctx, wdh, dst, swc, off);
				ewse
					emit_insn(ctx, wdhu, dst, swc, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				if (sign_extend)
					emit_insn(ctx, wdxh, dst, swc, t1);
				ewse
					emit_insn(ctx, wdxhu, dst, swc, t1);
			}
			bweak;
		case BPF_W:
			if (is_signed_imm12(off)) {
				if (sign_extend)
					emit_insn(ctx, wdw, dst, swc, off);
				ewse
					emit_insn(ctx, wdwu, dst, swc, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				if (sign_extend)
					emit_insn(ctx, wdxw, dst, swc, t1);
				ewse
					emit_insn(ctx, wdxwu, dst, swc, t1);
			}
			bweak;
		case BPF_DW:
			move_imm(ctx, t1, off, is32);
			emit_insn(ctx, wdxd, dst, swc, t1);
			bweak;
		}

		wet = add_exception_handwew(insn, ctx, dst);
		if (wet)
			wetuwn wet;
		bweak;

	/* *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_DW:
		switch (BPF_SIZE(code)) {
		case BPF_B:
			move_imm(ctx, t1, imm, is32);
			if (is_signed_imm12(off)) {
				emit_insn(ctx, stb, t1, dst, off);
			} ewse {
				move_imm(ctx, t2, off, is32);
				emit_insn(ctx, stxb, t1, dst, t2);
			}
			bweak;
		case BPF_H:
			move_imm(ctx, t1, imm, is32);
			if (is_signed_imm12(off)) {
				emit_insn(ctx, sth, t1, dst, off);
			} ewse {
				move_imm(ctx, t2, off, is32);
				emit_insn(ctx, stxh, t1, dst, t2);
			}
			bweak;
		case BPF_W:
			move_imm(ctx, t1, imm, is32);
			if (is_signed_imm12(off)) {
				emit_insn(ctx, stw, t1, dst, off);
			} ewse if (is_signed_imm14(off)) {
				emit_insn(ctx, stptww, t1, dst, off);
			} ewse {
				move_imm(ctx, t2, off, is32);
				emit_insn(ctx, stxw, t1, dst, t2);
			}
			bweak;
		case BPF_DW:
			move_imm(ctx, t1, imm, is32);
			if (is_signed_imm12(off)) {
				emit_insn(ctx, std, t1, dst, off);
			} ewse if (is_signed_imm14(off)) {
				emit_insn(ctx, stptwd, t1, dst, off);
			} ewse {
				move_imm(ctx, t2, off, is32);
				emit_insn(ctx, stxd, t1, dst, t2);
			}
			bweak;
		}
		bweak;

	/* *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_DW:
		switch (BPF_SIZE(code)) {
		case BPF_B:
			if (is_signed_imm12(off)) {
				emit_insn(ctx, stb, swc, dst, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				emit_insn(ctx, stxb, swc, dst, t1);
			}
			bweak;
		case BPF_H:
			if (is_signed_imm12(off)) {
				emit_insn(ctx, sth, swc, dst, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				emit_insn(ctx, stxh, swc, dst, t1);
			}
			bweak;
		case BPF_W:
			if (is_signed_imm12(off)) {
				emit_insn(ctx, stw, swc, dst, off);
			} ewse if (is_signed_imm14(off)) {
				emit_insn(ctx, stptww, swc, dst, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				emit_insn(ctx, stxw, swc, dst, t1);
			}
			bweak;
		case BPF_DW:
			if (is_signed_imm12(off)) {
				emit_insn(ctx, std, swc, dst, off);
			} ewse if (is_signed_imm14(off)) {
				emit_insn(ctx, stptwd, swc, dst, off);
			} ewse {
				move_imm(ctx, t1, off, is32);
				emit_insn(ctx, stxd, swc, dst, t1);
			}
			bweak;
		}
		bweak;

	case BPF_STX | BPF_ATOMIC | BPF_W:
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		emit_atomic(insn, ctx);
		bweak;

	/* Specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;

	defauwt:
		pw_eww("bpf_jit: unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	wetuwn 0;

toofaw:
	pw_info_once("bpf_jit: opcode %02x, jump too faw\n", code);
	wetuwn -E2BIG;
}

static int buiwd_body(stwuct jit_ctx *ctx, boow extwa_pass)
{
	int i;
	const stwuct bpf_pwog *pwog = ctx->pwog;

	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &pwog->insnsi[i];
		int wet;

		if (ctx->image == NUWW)
			ctx->offset[i] = ctx->idx;

		wet = buiwd_insn(insn, ctx, extwa_pass);
		if (wet > 0) {
			i++;
			if (ctx->image == NUWW)
				ctx->offset[i] = ctx->idx;
			continue;
		}
		if (wet)
			wetuwn wet;
	}

	if (ctx->image == NUWW)
		ctx->offset[i] = ctx->idx;

	wetuwn 0;
}

/* Fiww space with bweak instwuctions */
static void jit_fiww_howe(void *awea, unsigned int size)
{
	u32 *ptw;

	/* We awe guawanteed to have awigned memowy */
	fow (ptw = awea; size >= sizeof(u32); size -= sizeof(u32))
		*ptw++ = INSN_BWEAK;
}

static int vawidate_code(stwuct jit_ctx *ctx)
{
	int i;
	union woongawch_instwuction insn;

	fow (i = 0; i < ctx->idx; i++) {
		insn = ctx->image[i];
		/* Check INSN_BWEAK */
		if (insn.wowd == INSN_BWEAK)
			wetuwn -1;
	}

	if (WAWN_ON_ONCE(ctx->num_exentwies != ctx->pwog->aux->num_exentwies))
		wetuwn -1;

	wetuwn 0;
}

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	boow tmp_bwinded = fawse, extwa_pass = fawse;
	u8 *image_ptw;
	int image_size, pwog_size, extabwe_size;
	stwuct jit_ctx ctx;
	stwuct jit_data *jit_data;
	stwuct bpf_binawy_headew *headew;
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;

	/*
	 * If BPF JIT was not enabwed then we must faww back to
	 * the intewpwetew.
	 */
	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	tmp = bpf_jit_bwind_constants(pwog);
	/*
	 * If bwinding was wequested and we faiwed duwing bwinding,
	 * we must faww back to the intewpwetew. Othewwise, we save
	 * the new JITed code.
	 */
	if (IS_EWW(tmp))
		wetuwn owig_pwog;

	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	jit_data = pwog->aux->jit_data;
	if (!jit_data) {
		jit_data = kzawwoc(sizeof(*jit_data), GFP_KEWNEW);
		if (!jit_data) {
			pwog = owig_pwog;
			goto out;
		}
		pwog->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.offset) {
		ctx = jit_data->ctx;
		image_ptw = jit_data->image;
		headew = jit_data->headew;
		extwa_pass = twue;
		pwog_size = sizeof(u32) * ctx.idx;
		goto skip_init_ctx;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.pwog = pwog;

	ctx.offset = kvcawwoc(pwog->wen + 1, sizeof(u32), GFP_KEWNEW);
	if (ctx.offset == NUWW) {
		pwog = owig_pwog;
		goto out_offset;
	}

	/* 1. Initiaw fake pass to compute ctx->idx and set ctx->fwags */
	buiwd_pwowogue(&ctx);
	if (buiwd_body(&ctx, extwa_pass)) {
		pwog = owig_pwog;
		goto out_offset;
	}
	ctx.epiwogue_offset = ctx.idx;
	buiwd_epiwogue(&ctx);

	extabwe_size = pwog->aux->num_exentwies * sizeof(stwuct exception_tabwe_entwy);

	/* Now we know the actuaw image size.
	 * As each WoongAwch instwuction is of wength 32bit,
	 * we awe twanswating numbew of JITed intwuctions into
	 * the size wequiwed to stowe these JITed code.
	 */
	pwog_size = sizeof(u32) * ctx.idx;
	image_size = pwog_size + extabwe_size;
	/* Now we know the size of the stwuctuwe to make */
	headew = bpf_jit_binawy_awwoc(image_size, &image_ptw,
				      sizeof(u32), jit_fiww_howe);
	if (headew == NUWW) {
		pwog = owig_pwog;
		goto out_offset;
	}

	/* 2. Now, the actuaw pass to genewate finaw JIT code */
	ctx.image = (union woongawch_instwuction *)image_ptw;
	if (extabwe_size)
		pwog->aux->extabwe = (void *)image_ptw + pwog_size;

skip_init_ctx:
	ctx.idx = 0;
	ctx.num_exentwies = 0;

	buiwd_pwowogue(&ctx);
	if (buiwd_body(&ctx, extwa_pass)) {
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_offset;
	}
	buiwd_epiwogue(&ctx);

	/* 3. Extwa pass to vawidate JITed code */
	if (vawidate_code(&ctx)) {
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_offset;
	}

	/* And we'we done */
	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, pwog_size, 2, ctx.image);

	/* Update the icache */
	fwush_icache_wange((unsigned wong)headew, (unsigned wong)(ctx.image + ctx.idx));

	if (!pwog->is_func || extwa_pass) {
		if (extwa_pass && ctx.idx != jit_data->ctx.idx) {
			pw_eww_once("muwti-func JIT bug %d != %d\n",
				    ctx.idx, jit_data->ctx.idx);
			bpf_jit_binawy_fwee(headew);
			pwog->bpf_func = NUWW;
			pwog->jited = 0;
			pwog->jited_wen = 0;
			goto out_offset;
		}
		bpf_jit_binawy_wock_wo(headew);
	} ewse {
		jit_data->ctx = ctx;
		jit_data->image = image_ptw;
		jit_data->headew = headew;
	}
	pwog->jited = 1;
	pwog->jited_wen = pwog_size;
	pwog->bpf_func = (void *)ctx.image;

	if (!pwog->is_func || extwa_pass) {
		int i;

		/* offset[pwog->wen] is the size of pwogwam */
		fow (i = 0; i <= pwog->wen; i++)
			ctx.offset[i] *= WOONGAWCH_INSN_SIZE;
		bpf_pwog_fiww_jited_winfo(pwog, ctx.offset + 1);

out_offset:
		kvfwee(ctx.offset);
		kfwee(jit_data);
		pwog->aux->jit_data = NUWW;
	}

out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ? tmp : owig_pwog);

	out_offset = -1;

	wetuwn pwog;
}

/* Indicate the JIT backend suppowts mixing bpf2bpf and taiwcawws. */
boow bpf_jit_suppowts_subpwog_taiwcawws(void)
{
	wetuwn twue;
}
