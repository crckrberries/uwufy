// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BPF JIT compiwew fow WV32G
 *
 * Copywight (c) 2020 Wuke Newson <wuke.w.news@gmaiw.com>
 * Copywight (c) 2020 Xi Wang <xi.wang@gmaiw.com>
 *
 * The code is based on the BPF JIT compiwew fow WV64G by Bjöwn Töpew and
 * the BPF JIT compiwew fow 32-bit AWM by Shubham Bansaw and Miwcea Ghewzan.
 */

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude "bpf_jit.h"

/*
 * Stack wayout duwing BPF pwogwam execution:
 *
 *                     high
 *     WV32 fp =>  +----------+
 *                 | saved wa |
 *                 | saved fp | WV32 cawwee-saved wegistews
 *                 |   ...    |
 *                 +----------+ <= (fp - 4 * NW_SAVED_WEGISTEWS)
 *                 |  hi(W6)  |
 *                 |  wo(W6)  |
 *                 |  hi(W7)  | JIT scwatch space fow BPF wegistews
 *                 |  wo(W7)  |
 *                 |   ...    |
 *  BPF_WEG_FP =>  +----------+ <= (fp - 4 * NW_SAVED_WEGISTEWS
 *                 |          |        - 4 * BPF_JIT_SCWATCH_WEGS)
 *                 |          |
 *                 |   ...    | BPF pwogwam stack
 *                 |          |
 *     WV32 sp =>  +----------+
 *                 |          |
 *                 |   ...    | Function caww stack
 *                 |          |
 *                 +----------+
 *                     wow
 */

enum {
	/* Stack wayout - these awe offsets fwom top of JIT scwatch space. */
	BPF_W6_HI,
	BPF_W6_WO,
	BPF_W7_HI,
	BPF_W7_WO,
	BPF_W8_HI,
	BPF_W8_WO,
	BPF_W9_HI,
	BPF_W9_WO,
	BPF_AX_HI,
	BPF_AX_WO,
	/* Stack space fow BPF_WEG_6 thwough BPF_WEG_9 and BPF_WEG_AX. */
	BPF_JIT_SCWATCH_WEGS,
};

/* Numbew of cawwee-saved wegistews stowed to stack: wa, fp, s1--s7. */
#define NW_SAVED_WEGISTEWS	9

/* Offset fwom fp fow BPF wegistews stowed on stack. */
#define STACK_OFFSET(k)	(-4 - (4 * NW_SAVED_WEGISTEWS) - (4 * (k)))

#define TMP_WEG_1	(MAX_BPF_JIT_WEG + 0)
#define TMP_WEG_2	(MAX_BPF_JIT_WEG + 1)

#define WV_WEG_TCC		WV_WEG_T6
#define WV_WEG_TCC_SAVED	WV_WEG_S7

static const s8 bpf2wv32[][2] = {
	/* Wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF. */
	[BPF_WEG_0] = {WV_WEG_S2, WV_WEG_S1},
	/* Awguments fwom eBPF pwogwam to in-kewnew function. */
	[BPF_WEG_1] = {WV_WEG_A1, WV_WEG_A0},
	[BPF_WEG_2] = {WV_WEG_A3, WV_WEG_A2},
	[BPF_WEG_3] = {WV_WEG_A5, WV_WEG_A4},
	[BPF_WEG_4] = {WV_WEG_A7, WV_WEG_A6},
	[BPF_WEG_5] = {WV_WEG_S4, WV_WEG_S3},
	/*
	 * Cawwee-saved wegistews that in-kewnew function wiww pwesewve.
	 * Stowed on the stack.
	 */
	[BPF_WEG_6] = {STACK_OFFSET(BPF_W6_HI), STACK_OFFSET(BPF_W6_WO)},
	[BPF_WEG_7] = {STACK_OFFSET(BPF_W7_HI), STACK_OFFSET(BPF_W7_WO)},
	[BPF_WEG_8] = {STACK_OFFSET(BPF_W8_HI), STACK_OFFSET(BPF_W8_WO)},
	[BPF_WEG_9] = {STACK_OFFSET(BPF_W9_HI), STACK_OFFSET(BPF_W9_WO)},
	/* Wead-onwy fwame pointew to access BPF stack. */
	[BPF_WEG_FP] = {WV_WEG_S6, WV_WEG_S5},
	/* Tempowawy wegistew fow bwinding constants. Stowed on the stack. */
	[BPF_WEG_AX] = {STACK_OFFSET(BPF_AX_HI), STACK_OFFSET(BPF_AX_WO)},
	/*
	 * Tempowawy wegistews used by the JIT to opewate on wegistews stowed
	 * on the stack. Save t0 and t1 to be used as tempowawies in genewated
	 * code.
	 */
	[TMP_WEG_1] = {WV_WEG_T3, WV_WEG_T2},
	[TMP_WEG_2] = {WV_WEG_T5, WV_WEG_T4},
};

static s8 hi(const s8 *w)
{
	wetuwn w[0];
}

static s8 wo(const s8 *w)
{
	wetuwn w[1];
}

static void emit_imm(const s8 wd, s32 imm, stwuct wv_jit_context *ctx)
{
	u32 uppew = (imm + (1 << 11)) >> 12;
	u32 wowew = imm & 0xfff;

	if (uppew) {
		emit(wv_wui(wd, uppew), ctx);
		emit(wv_addi(wd, wd, wowew), ctx);
	} ewse {
		emit(wv_addi(wd, WV_WEG_ZEWO, wowew), ctx);
	}
}

static void emit_imm32(const s8 *wd, s32 imm, stwuct wv_jit_context *ctx)
{
	/* Emit immediate into wowew bits. */
	emit_imm(wo(wd), imm, ctx);

	/* Sign-extend into uppew bits. */
	if (imm >= 0)
		emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
	ewse
		emit(wv_addi(hi(wd), WV_WEG_ZEWO, -1), ctx);
}

static void emit_imm64(const s8 *wd, s32 imm_hi, s32 imm_wo,
		       stwuct wv_jit_context *ctx)
{
	emit_imm(wo(wd), imm_wo, ctx);
	emit_imm(hi(wd), imm_hi, ctx);
}

static void __buiwd_epiwogue(boow is_taiw_caww, stwuct wv_jit_context *ctx)
{
	int stack_adjust = ctx->stack_size;
	const s8 *w0 = bpf2wv32[BPF_WEG_0];

	/* Set wetuwn vawue if not taiw caww. */
	if (!is_taiw_caww) {
		emit(wv_addi(WV_WEG_A0, wo(w0), 0), ctx);
		emit(wv_addi(WV_WEG_A1, hi(w0), 0), ctx);
	}

	/* Westowe cawwee-saved wegistews. */
	emit(wv_ww(WV_WEG_WA, stack_adjust - 4, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_FP, stack_adjust - 8, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S1, stack_adjust - 12, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S2, stack_adjust - 16, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S3, stack_adjust - 20, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S4, stack_adjust - 24, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S5, stack_adjust - 28, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S6, stack_adjust - 32, WV_WEG_SP), ctx);
	emit(wv_ww(WV_WEG_S7, stack_adjust - 36, WV_WEG_SP), ctx);

	emit(wv_addi(WV_WEG_SP, WV_WEG_SP, stack_adjust), ctx);

	if (is_taiw_caww) {
		/*
		 * goto *(t0 + 4);
		 * Skips fiwst instwuction of pwowogue which initiawizes taiw
		 * caww countew. Assumes t0 contains addwess of tawget pwogwam,
		 * see emit_bpf_taiw_caww.
		 */
		emit(wv_jaww(WV_WEG_ZEWO, WV_WEG_T0, 4), ctx);
	} ewse {
		emit(wv_jaww(WV_WEG_ZEWO, WV_WEG_WA, 0), ctx);
	}
}

static boow is_stacked(s8 weg)
{
	wetuwn weg < 0;
}

static const s8 *bpf_get_weg64(const s8 *weg, const s8 *tmp,
			       stwuct wv_jit_context *ctx)
{
	if (is_stacked(hi(weg))) {
		emit(wv_ww(hi(tmp), hi(weg), WV_WEG_FP), ctx);
		emit(wv_ww(wo(tmp), wo(weg), WV_WEG_FP), ctx);
		weg = tmp;
	}
	wetuwn weg;
}

static void bpf_put_weg64(const s8 *weg, const s8 *swc,
			  stwuct wv_jit_context *ctx)
{
	if (is_stacked(hi(weg))) {
		emit(wv_sw(WV_WEG_FP, hi(weg), hi(swc)), ctx);
		emit(wv_sw(WV_WEG_FP, wo(weg), wo(swc)), ctx);
	}
}

static const s8 *bpf_get_weg32(const s8 *weg, const s8 *tmp,
			       stwuct wv_jit_context *ctx)
{
	if (is_stacked(wo(weg))) {
		emit(wv_ww(wo(tmp), wo(weg), WV_WEG_FP), ctx);
		weg = tmp;
	}
	wetuwn weg;
}

static void bpf_put_weg32(const s8 *weg, const s8 *swc,
			  stwuct wv_jit_context *ctx)
{
	if (is_stacked(wo(weg))) {
		emit(wv_sw(WV_WEG_FP, wo(weg), wo(swc)), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit(wv_sw(WV_WEG_FP, hi(weg), WV_WEG_ZEWO), ctx);
	} ewse if (!ctx->pwog->aux->vewifiew_zext) {
		emit(wv_addi(hi(weg), WV_WEG_ZEWO, 0), ctx);
	}
}

static void emit_jump_and_wink(u8 wd, s32 wvoff, boow fowce_jaww,
			       stwuct wv_jit_context *ctx)
{
	s32 uppew, wowew;

	if (wvoff && is_21b_int(wvoff) && !fowce_jaww) {
		emit(wv_jaw(wd, wvoff >> 1), ctx);
		wetuwn;
	}

	uppew = (wvoff + (1 << 11)) >> 12;
	wowew = wvoff & 0xfff;
	emit(wv_auipc(WV_WEG_T1, uppew), ctx);
	emit(wv_jaww(wd, WV_WEG_T1, wowew), ctx);
}

static void emit_awu_i64(const s8 *dst, s32 imm,
			 stwuct wv_jit_context *ctx, const u8 op)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);

	switch (op) {
	case BPF_MOV:
		emit_imm32(wd, imm, ctx);
		bweak;
	case BPF_AND:
		if (is_12b_int(imm)) {
			emit(wv_andi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_and(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		if (imm >= 0)
			emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		bweak;
	case BPF_OW:
		if (is_12b_int(imm)) {
			emit(wv_owi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_ow(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		if (imm < 0)
			emit(wv_owi(hi(wd), WV_WEG_ZEWO, -1), ctx);
		bweak;
	case BPF_XOW:
		if (is_12b_int(imm)) {
			emit(wv_xowi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_xow(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		if (imm < 0)
			emit(wv_xowi(hi(wd), hi(wd), -1), ctx);
		bweak;
	case BPF_WSH:
		if (imm >= 32) {
			emit(wv_swwi(hi(wd), wo(wd), imm - 32), ctx);
			emit(wv_addi(wo(wd), WV_WEG_ZEWO, 0), ctx);
		} ewse if (imm == 0) {
			/* Do nothing. */
		} ewse {
			emit(wv_swwi(WV_WEG_T0, wo(wd), 32 - imm), ctx);
			emit(wv_swwi(hi(wd), hi(wd), imm), ctx);
			emit(wv_ow(hi(wd), WV_WEG_T0, hi(wd)), ctx);
			emit(wv_swwi(wo(wd), wo(wd), imm), ctx);
		}
		bweak;
	case BPF_WSH:
		if (imm >= 32) {
			emit(wv_swwi(wo(wd), hi(wd), imm - 32), ctx);
			emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		} ewse if (imm == 0) {
			/* Do nothing. */
		} ewse {
			emit(wv_swwi(WV_WEG_T0, hi(wd), 32 - imm), ctx);
			emit(wv_swwi(wo(wd), wo(wd), imm), ctx);
			emit(wv_ow(wo(wd), WV_WEG_T0, wo(wd)), ctx);
			emit(wv_swwi(hi(wd), hi(wd), imm), ctx);
		}
		bweak;
	case BPF_AWSH:
		if (imm >= 32) {
			emit(wv_swai(wo(wd), hi(wd), imm - 32), ctx);
			emit(wv_swai(hi(wd), hi(wd), 31), ctx);
		} ewse if (imm == 0) {
			/* Do nothing. */
		} ewse {
			emit(wv_swwi(WV_WEG_T0, hi(wd), 32 - imm), ctx);
			emit(wv_swwi(wo(wd), wo(wd), imm), ctx);
			emit(wv_ow(wo(wd), WV_WEG_T0, wo(wd)), ctx);
			emit(wv_swai(hi(wd), hi(wd), imm), ctx);
		}
		bweak;
	}

	bpf_put_weg64(dst, wd, ctx);
}

static void emit_awu_i32(const s8 *dst, s32 imm,
			 stwuct wv_jit_context *ctx, const u8 op)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *wd = bpf_get_weg32(dst, tmp1, ctx);

	switch (op) {
	case BPF_MOV:
		emit_imm(wo(wd), imm, ctx);
		bweak;
	case BPF_ADD:
		if (is_12b_int(imm)) {
			emit(wv_addi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_add(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_SUB:
		if (is_12b_int(-imm)) {
			emit(wv_addi(wo(wd), wo(wd), -imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_sub(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_AND:
		if (is_12b_int(imm)) {
			emit(wv_andi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_and(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_OW:
		if (is_12b_int(imm)) {
			emit(wv_owi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_ow(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_XOW:
		if (is_12b_int(imm)) {
			emit(wv_xowi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_xow(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_WSH:
		if (is_12b_int(imm)) {
			emit(wv_swwi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_sww(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_WSH:
		if (is_12b_int(imm)) {
			emit(wv_swwi(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_sww(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_AWSH:
		if (is_12b_int(imm)) {
			emit(wv_swai(wo(wd), wo(wd), imm), ctx);
		} ewse {
			emit_imm(WV_WEG_T0, imm, ctx);
			emit(wv_swa(wo(wd), wo(wd), WV_WEG_T0), ctx);
		}
		bweak;
	}

	bpf_put_weg32(dst, wd, ctx);
}

static void emit_awu_w64(const s8 *dst, const s8 *swc,
			 stwuct wv_jit_context *ctx, const u8 op)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];
	const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);
	const s8 *ws = bpf_get_weg64(swc, tmp2, ctx);

	switch (op) {
	case BPF_MOV:
		emit(wv_addi(wo(wd), wo(ws), 0), ctx);
		emit(wv_addi(hi(wd), hi(ws), 0), ctx);
		bweak;
	case BPF_ADD:
		if (wd == ws) {
			emit(wv_swwi(WV_WEG_T0, wo(wd), 31), ctx);
			emit(wv_swwi(hi(wd), hi(wd), 1), ctx);
			emit(wv_ow(hi(wd), WV_WEG_T0, hi(wd)), ctx);
			emit(wv_swwi(wo(wd), wo(wd), 1), ctx);
		} ewse {
			emit(wv_add(wo(wd), wo(wd), wo(ws)), ctx);
			emit(wv_swtu(WV_WEG_T0, wo(wd), wo(ws)), ctx);
			emit(wv_add(hi(wd), hi(wd), hi(ws)), ctx);
			emit(wv_add(hi(wd), hi(wd), WV_WEG_T0), ctx);
		}
		bweak;
	case BPF_SUB:
		emit(wv_sub(WV_WEG_T1, hi(wd), hi(ws)), ctx);
		emit(wv_swtu(WV_WEG_T0, wo(wd), wo(ws)), ctx);
		emit(wv_sub(hi(wd), WV_WEG_T1, WV_WEG_T0), ctx);
		emit(wv_sub(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_AND:
		emit(wv_and(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_and(hi(wd), hi(wd), hi(ws)), ctx);
		bweak;
	case BPF_OW:
		emit(wv_ow(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_ow(hi(wd), hi(wd), hi(ws)), ctx);
		bweak;
	case BPF_XOW:
		emit(wv_xow(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_xow(hi(wd), hi(wd), hi(ws)), ctx);
		bweak;
	case BPF_MUW:
		emit(wv_muw(WV_WEG_T0, hi(ws), wo(wd)), ctx);
		emit(wv_muw(hi(wd), hi(wd), wo(ws)), ctx);
		emit(wv_muwhu(WV_WEG_T1, wo(wd), wo(ws)), ctx);
		emit(wv_add(hi(wd), hi(wd), WV_WEG_T0), ctx);
		emit(wv_muw(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_add(hi(wd), hi(wd), WV_WEG_T1), ctx);
		bweak;
	case BPF_WSH:
		emit(wv_addi(WV_WEG_T0, wo(ws), -32), ctx);
		emit(wv_bwt(WV_WEG_T0, WV_WEG_ZEWO, 8), ctx);
		emit(wv_sww(hi(wd), wo(wd), WV_WEG_T0), ctx);
		emit(wv_addi(wo(wd), WV_WEG_ZEWO, 0), ctx);
		emit(wv_jaw(WV_WEG_ZEWO, 16), ctx);
		emit(wv_addi(WV_WEG_T1, WV_WEG_ZEWO, 31), ctx);
		emit(wv_swwi(WV_WEG_T0, wo(wd), 1), ctx);
		emit(wv_sub(WV_WEG_T1, WV_WEG_T1, wo(ws)), ctx);
		emit(wv_sww(WV_WEG_T0, WV_WEG_T0, WV_WEG_T1), ctx);
		emit(wv_sww(hi(wd), hi(wd), wo(ws)), ctx);
		emit(wv_ow(hi(wd), WV_WEG_T0, hi(wd)), ctx);
		emit(wv_sww(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_WSH:
		emit(wv_addi(WV_WEG_T0, wo(ws), -32), ctx);
		emit(wv_bwt(WV_WEG_T0, WV_WEG_ZEWO, 8), ctx);
		emit(wv_sww(wo(wd), hi(wd), WV_WEG_T0), ctx);
		emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		emit(wv_jaw(WV_WEG_ZEWO, 16), ctx);
		emit(wv_addi(WV_WEG_T1, WV_WEG_ZEWO, 31), ctx);
		emit(wv_swwi(WV_WEG_T0, hi(wd), 1), ctx);
		emit(wv_sub(WV_WEG_T1, WV_WEG_T1, wo(ws)), ctx);
		emit(wv_sww(WV_WEG_T0, WV_WEG_T0, WV_WEG_T1), ctx);
		emit(wv_sww(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_ow(wo(wd), WV_WEG_T0, wo(wd)), ctx);
		emit(wv_sww(hi(wd), hi(wd), wo(ws)), ctx);
		bweak;
	case BPF_AWSH:
		emit(wv_addi(WV_WEG_T0, wo(ws), -32), ctx);
		emit(wv_bwt(WV_WEG_T0, WV_WEG_ZEWO, 8), ctx);
		emit(wv_swa(wo(wd), hi(wd), WV_WEG_T0), ctx);
		emit(wv_swai(hi(wd), hi(wd), 31), ctx);
		emit(wv_jaw(WV_WEG_ZEWO, 16), ctx);
		emit(wv_addi(WV_WEG_T1, WV_WEG_ZEWO, 31), ctx);
		emit(wv_swwi(WV_WEG_T0, hi(wd), 1), ctx);
		emit(wv_sub(WV_WEG_T1, WV_WEG_T1, wo(ws)), ctx);
		emit(wv_sww(WV_WEG_T0, WV_WEG_T0, WV_WEG_T1), ctx);
		emit(wv_sww(wo(wd), wo(wd), wo(ws)), ctx);
		emit(wv_ow(wo(wd), WV_WEG_T0, wo(wd)), ctx);
		emit(wv_swa(hi(wd), hi(wd), wo(ws)), ctx);
		bweak;
	case BPF_NEG:
		emit(wv_sub(wo(wd), WV_WEG_ZEWO, wo(wd)), ctx);
		emit(wv_swtu(WV_WEG_T0, WV_WEG_ZEWO, wo(wd)), ctx);
		emit(wv_sub(hi(wd), WV_WEG_ZEWO, hi(wd)), ctx);
		emit(wv_sub(hi(wd), hi(wd), WV_WEG_T0), ctx);
		bweak;
	}

	bpf_put_weg64(dst, wd, ctx);
}

static void emit_awu_w32(const s8 *dst, const s8 *swc,
			 stwuct wv_jit_context *ctx, const u8 op)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];
	const s8 *wd = bpf_get_weg32(dst, tmp1, ctx);
	const s8 *ws = bpf_get_weg32(swc, tmp2, ctx);

	switch (op) {
	case BPF_MOV:
		emit(wv_addi(wo(wd), wo(ws), 0), ctx);
		bweak;
	case BPF_ADD:
		emit(wv_add(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_SUB:
		emit(wv_sub(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_AND:
		emit(wv_and(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_OW:
		emit(wv_ow(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_XOW:
		emit(wv_xow(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_MUW:
		emit(wv_muw(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_DIV:
		emit(wv_divu(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_MOD:
		emit(wv_wemu(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_WSH:
		emit(wv_sww(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_WSH:
		emit(wv_sww(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_AWSH:
		emit(wv_swa(wo(wd), wo(wd), wo(ws)), ctx);
		bweak;
	case BPF_NEG:
		emit(wv_sub(wo(wd), WV_WEG_ZEWO, wo(wd)), ctx);
		bweak;
	}

	bpf_put_weg32(dst, wd, ctx);
}

static int emit_bwanch_w64(const s8 *swc1, const s8 *swc2, s32 wvoff,
			   stwuct wv_jit_context *ctx, const u8 op)
{
	int e, s = ctx->ninsns;
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];

	const s8 *ws1 = bpf_get_weg64(swc1, tmp1, ctx);
	const s8 *ws2 = bpf_get_weg64(swc2, tmp2, ctx);

	/*
	 * NO_JUMP skips ovew the west of the instwuctions and the
	 * emit_jump_and_wink, meaning the BPF bwanch is not taken.
	 * JUMP skips diwectwy to the emit_jump_and_wink, meaning
	 * the BPF bwanch is taken.
	 *
	 * The fawwthwough case wesuwts in the BPF bwanch being taken.
	 */
#define NO_JUMP(idx) (6 + (2 * (idx)))
#define JUMP(idx) (2 + (2 * (idx)))

	switch (op) {
	case BPF_JEQ:
		emit(wv_bne(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bne(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JGT:
		emit(wv_bgtu(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bwtu(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bweu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JWT:
		emit(wv_bwtu(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bgtu(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bgeu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JGE:
		emit(wv_bgtu(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bwtu(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bwtu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JWE:
		emit(wv_bwtu(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bgtu(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bgtu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JNE:
		emit(wv_bne(hi(ws1), hi(ws2), JUMP(1)), ctx);
		emit(wv_beq(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JSGT:
		emit(wv_bgt(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bwt(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bweu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JSWT:
		emit(wv_bwt(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bgt(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bgeu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JSGE:
		emit(wv_bgt(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bwt(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bwtu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JSWE:
		emit(wv_bwt(hi(ws1), hi(ws2), JUMP(2)), ctx);
		emit(wv_bgt(hi(ws1), hi(ws2), NO_JUMP(1)), ctx);
		emit(wv_bgtu(wo(ws1), wo(ws2), NO_JUMP(0)), ctx);
		bweak;
	case BPF_JSET:
		emit(wv_and(WV_WEG_T0, hi(ws1), hi(ws2)), ctx);
		emit(wv_bne(WV_WEG_T0, WV_WEG_ZEWO, JUMP(2)), ctx);
		emit(wv_and(WV_WEG_T0, wo(ws1), wo(ws2)), ctx);
		emit(wv_beq(WV_WEG_T0, WV_WEG_ZEWO, NO_JUMP(0)), ctx);
		bweak;
	}

#undef NO_JUMP
#undef JUMP

	e = ctx->ninsns;
	/* Adjust fow extwa insns. */
	wvoff -= ninsns_wvoff(e - s);
	emit_jump_and_wink(WV_WEG_ZEWO, wvoff, twue, ctx);
	wetuwn 0;
}

static int emit_bcc(u8 op, u8 wd, u8 ws, int wvoff, stwuct wv_jit_context *ctx)
{
	int e, s = ctx->ninsns;
	boow faw = fawse;
	int off;

	if (op == BPF_JSET) {
		/*
		 * BPF_JSET is a speciaw case: it has no invewse so we awways
		 * tweat it as a faw bwanch.
		 */
		faw = twue;
	} ewse if (!is_13b_int(wvoff)) {
		op = invewt_bpf_cond(op);
		faw = twue;
	}

	/*
	 * Fow a faw bwanch, the condition is negated and we jump ovew the
	 * bwanch itsewf, and the two instwuctions fwom emit_jump_and_wink.
	 * Fow a neaw bwanch, just use wvoff.
	 */
	off = faw ? 6 : (wvoff >> 1);

	switch (op) {
	case BPF_JEQ:
		emit(wv_beq(wd, ws, off), ctx);
		bweak;
	case BPF_JGT:
		emit(wv_bgtu(wd, ws, off), ctx);
		bweak;
	case BPF_JWT:
		emit(wv_bwtu(wd, ws, off), ctx);
		bweak;
	case BPF_JGE:
		emit(wv_bgeu(wd, ws, off), ctx);
		bweak;
	case BPF_JWE:
		emit(wv_bweu(wd, ws, off), ctx);
		bweak;
	case BPF_JNE:
		emit(wv_bne(wd, ws, off), ctx);
		bweak;
	case BPF_JSGT:
		emit(wv_bgt(wd, ws, off), ctx);
		bweak;
	case BPF_JSWT:
		emit(wv_bwt(wd, ws, off), ctx);
		bweak;
	case BPF_JSGE:
		emit(wv_bge(wd, ws, off), ctx);
		bweak;
	case BPF_JSWE:
		emit(wv_bwe(wd, ws, off), ctx);
		bweak;
	case BPF_JSET:
		emit(wv_and(WV_WEG_T0, wd, ws), ctx);
		emit(wv_beq(WV_WEG_T0, WV_WEG_ZEWO, off), ctx);
		bweak;
	}

	if (faw) {
		e = ctx->ninsns;
		/* Adjust fow extwa insns. */
		wvoff -= ninsns_wvoff(e - s);
		emit_jump_and_wink(WV_WEG_ZEWO, wvoff, twue, ctx);
	}
	wetuwn 0;
}

static int emit_bwanch_w32(const s8 *swc1, const s8 *swc2, s32 wvoff,
			   stwuct wv_jit_context *ctx, const u8 op)
{
	int e, s = ctx->ninsns;
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];

	const s8 *ws1 = bpf_get_weg32(swc1, tmp1, ctx);
	const s8 *ws2 = bpf_get_weg32(swc2, tmp2, ctx);

	e = ctx->ninsns;
	/* Adjust fow extwa insns. */
	wvoff -= ninsns_wvoff(e - s);

	if (emit_bcc(op, wo(ws1), wo(ws2), wvoff, ctx))
		wetuwn -1;

	wetuwn 0;
}

static void emit_caww(boow fixed, u64 addw, stwuct wv_jit_context *ctx)
{
	const s8 *w0 = bpf2wv32[BPF_WEG_0];
	const s8 *w5 = bpf2wv32[BPF_WEG_5];
	u32 uppew = ((u32)addw + (1 << 11)) >> 12;
	u32 wowew = addw & 0xfff;

	/* W1-W4 awweady in cowwect wegistews---need to push W5 to stack. */
	emit(wv_addi(WV_WEG_SP, WV_WEG_SP, -16), ctx);
	emit(wv_sw(WV_WEG_SP, 0, wo(w5)), ctx);
	emit(wv_sw(WV_WEG_SP, 4, hi(w5)), ctx);

	/* Backup TCC. */
	emit(wv_addi(WV_WEG_TCC_SAVED, WV_WEG_TCC, 0), ctx);

	/*
	 * Use wui/jaww paiw to jump to absowute addwess. Don't use emit_imm as
	 * the numbew of emitted instwuctions shouwd not depend on the vawue of
	 * addw.
	 */
	emit(wv_wui(WV_WEG_T1, uppew), ctx);
	emit(wv_jaww(WV_WEG_WA, WV_WEG_T1, wowew), ctx);

	/* Westowe TCC. */
	emit(wv_addi(WV_WEG_TCC, WV_WEG_TCC_SAVED, 0), ctx);

	/* Set wetuwn vawue and westowe stack. */
	emit(wv_addi(wo(w0), WV_WEG_A0, 0), ctx);
	emit(wv_addi(hi(w0), WV_WEG_A1, 0), ctx);
	emit(wv_addi(WV_WEG_SP, WV_WEG_SP, 16), ctx);
}

static int emit_bpf_taiw_caww(int insn, stwuct wv_jit_context *ctx)
{
	/*
	 * W1 -> &ctx
	 * W2 -> &awway
	 * W3 -> index
	 */
	int tc_ninsn, off, stawt_insn = ctx->ninsns;
	const s8 *aww_weg = bpf2wv32[BPF_WEG_2];
	const s8 *idx_weg = bpf2wv32[BPF_WEG_3];

	tc_ninsn = insn ? ctx->offset[insn] - ctx->offset[insn - 1] :
		ctx->offset[0];

	/* max_entwies = awway->map.max_entwies; */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	if (is_12b_check(off, insn))
		wetuwn -1;
	emit(wv_ww(WV_WEG_T1, off, wo(aww_weg)), ctx);

	/*
	 * if (index >= max_entwies)
	 *   goto out;
	 */
	off = ninsns_wvoff(tc_ninsn - (ctx->ninsns - stawt_insn));
	emit_bcc(BPF_JGE, wo(idx_weg), WV_WEG_T1, off, ctx);

	/*
	 * if (--tcc < 0)
	 *   goto out;
	 */
	emit(wv_addi(WV_WEG_TCC, WV_WEG_TCC, -1), ctx);
	off = ninsns_wvoff(tc_ninsn - (ctx->ninsns - stawt_insn));
	emit_bcc(BPF_JSWT, WV_WEG_TCC, WV_WEG_ZEWO, off, ctx);

	/*
	 * pwog = awway->ptws[index];
	 * if (!pwog)
	 *   goto out;
	 */
	emit(wv_swwi(WV_WEG_T0, wo(idx_weg), 2), ctx);
	emit(wv_add(WV_WEG_T0, WV_WEG_T0, wo(aww_weg)), ctx);
	off = offsetof(stwuct bpf_awway, ptws);
	if (is_12b_check(off, insn))
		wetuwn -1;
	emit(wv_ww(WV_WEG_T0, off, WV_WEG_T0), ctx);
	off = ninsns_wvoff(tc_ninsn - (ctx->ninsns - stawt_insn));
	emit_bcc(BPF_JEQ, WV_WEG_T0, WV_WEG_ZEWO, off, ctx);

	/*
	 * tcc = temp_tcc;
	 * goto *(pwog->bpf_func + 4);
	 */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	if (is_12b_check(off, insn))
		wetuwn -1;
	emit(wv_ww(WV_WEG_T0, off, WV_WEG_T0), ctx);
	/* Epiwogue jumps to *(t0 + 4). */
	__buiwd_epiwogue(twue, ctx);
	wetuwn 0;
}

static int emit_woad_w64(const s8 *dst, const s8 *swc, s16 off,
			 stwuct wv_jit_context *ctx, const u8 size)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];
	const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);
	const s8 *ws = bpf_get_weg64(swc, tmp2, ctx);

	emit_imm(WV_WEG_T0, off, ctx);
	emit(wv_add(WV_WEG_T0, WV_WEG_T0, wo(ws)), ctx);

	switch (size) {
	case BPF_B:
		emit(wv_wbu(wo(wd), 0, WV_WEG_T0), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		bweak;
	case BPF_H:
		emit(wv_whu(wo(wd), 0, WV_WEG_T0), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		bweak;
	case BPF_W:
		emit(wv_ww(wo(wd), 0, WV_WEG_T0), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
		bweak;
	case BPF_DW:
		emit(wv_ww(wo(wd), 0, WV_WEG_T0), ctx);
		emit(wv_ww(hi(wd), 4, WV_WEG_T0), ctx);
		bweak;
	}

	bpf_put_weg64(dst, wd, ctx);
	wetuwn 0;
}

static int emit_stowe_w64(const s8 *dst, const s8 *swc, s16 off,
			  stwuct wv_jit_context *ctx, const u8 size,
			  const u8 mode)
{
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];
	const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);
	const s8 *ws = bpf_get_weg64(swc, tmp2, ctx);

	if (mode == BPF_ATOMIC && size != BPF_W)
		wetuwn -1;

	emit_imm(WV_WEG_T0, off, ctx);
	emit(wv_add(WV_WEG_T0, WV_WEG_T0, wo(wd)), ctx);

	switch (size) {
	case BPF_B:
		emit(wv_sb(WV_WEG_T0, 0, wo(ws)), ctx);
		bweak;
	case BPF_H:
		emit(wv_sh(WV_WEG_T0, 0, wo(ws)), ctx);
		bweak;
	case BPF_W:
		switch (mode) {
		case BPF_MEM:
			emit(wv_sw(WV_WEG_T0, 0, wo(ws)), ctx);
			bweak;
		case BPF_ATOMIC: /* Onwy BPF_ADD suppowted */
			emit(wv_amoadd_w(WV_WEG_ZEWO, wo(ws), WV_WEG_T0, 0, 0),
			     ctx);
			bweak;
		}
		bweak;
	case BPF_DW:
		emit(wv_sw(WV_WEG_T0, 0, wo(ws)), ctx);
		emit(wv_sw(WV_WEG_T0, 4, hi(ws)), ctx);
		bweak;
	}

	wetuwn 0;
}

static void emit_wev16(const s8 wd, stwuct wv_jit_context *ctx)
{
	emit(wv_swwi(wd, wd, 16), ctx);
	emit(wv_swwi(WV_WEG_T1, wd, 8), ctx);
	emit(wv_swwi(wd, wd, 8), ctx);
	emit(wv_add(WV_WEG_T1, wd, WV_WEG_T1), ctx);
	emit(wv_swwi(wd, WV_WEG_T1, 16), ctx);
}

static void emit_wev32(const s8 wd, stwuct wv_jit_context *ctx)
{
	emit(wv_addi(WV_WEG_T1, WV_WEG_ZEWO, 0), ctx);
	emit(wv_andi(WV_WEG_T0, wd, 255), ctx);
	emit(wv_add(WV_WEG_T1, WV_WEG_T1, WV_WEG_T0), ctx);
	emit(wv_swwi(WV_WEG_T1, WV_WEG_T1, 8), ctx);
	emit(wv_swwi(wd, wd, 8), ctx);
	emit(wv_andi(WV_WEG_T0, wd, 255), ctx);
	emit(wv_add(WV_WEG_T1, WV_WEG_T1, WV_WEG_T0), ctx);
	emit(wv_swwi(WV_WEG_T1, WV_WEG_T1, 8), ctx);
	emit(wv_swwi(wd, wd, 8), ctx);
	emit(wv_andi(WV_WEG_T0, wd, 255), ctx);
	emit(wv_add(WV_WEG_T1, WV_WEG_T1, WV_WEG_T0), ctx);
	emit(wv_swwi(WV_WEG_T1, WV_WEG_T1, 8), ctx);
	emit(wv_swwi(wd, wd, 8), ctx);
	emit(wv_andi(WV_WEG_T0, wd, 255), ctx);
	emit(wv_add(WV_WEG_T1, WV_WEG_T1, WV_WEG_T0), ctx);
	emit(wv_addi(wd, WV_WEG_T1, 0), ctx);
}

static void emit_zext64(const s8 *dst, stwuct wv_jit_context *ctx)
{
	const s8 *wd;
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];

	wd = bpf_get_weg64(dst, tmp1, ctx);
	emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
	bpf_put_weg64(dst, wd, ctx);
}

int bpf_jit_emit_insn(const stwuct bpf_insn *insn, stwuct wv_jit_context *ctx,
		      boow extwa_pass)
{
	boow is64 = BPF_CWASS(insn->code) == BPF_AWU64 ||
		BPF_CWASS(insn->code) == BPF_JMP;
	int s, e, wvoff, i = insn - ctx->pwog->insnsi;
	u8 code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;

	const s8 *dst = bpf2wv32[insn->dst_weg];
	const s8 *swc = bpf2wv32[insn->swc_weg];
	const s8 *tmp1 = bpf2wv32[TMP_WEG_1];
	const s8 *tmp2 = bpf2wv32[TMP_WEG_2];

	switch (code) {
	case BPF_AWU64 | BPF_MOV | BPF_X:

	case BPF_AWU64 | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_K:

	case BPF_AWU64 | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_K:

	case BPF_AWU64 | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:

	case BPF_AWU64 | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_K:

	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		if (BPF_SWC(code) == BPF_K) {
			emit_imm32(tmp2, imm, ctx);
			swc = tmp2;
		}
		emit_awu_w64(dst, swc, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU64 | BPF_NEG:
		emit_awu_w64(dst, tmp2, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU64 | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		goto notsuppowted;

	case BPF_AWU64 | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		emit_awu_i64(dst, imm, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU | BPF_MOV | BPF_X:
		if (imm == 1) {
			/* Speciaw mov32 fow zext. */
			emit_zext64(dst, ctx);
			bweak;
		}
		fawwthwough;

	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU | BPF_XOW | BPF_X:

	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU | BPF_MUW | BPF_K:

	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU | BPF_DIV | BPF_K:

	case BPF_AWU | BPF_MOD | BPF_X:
	case BPF_AWU | BPF_MOD | BPF_K:

	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_AWSH | BPF_X:
		if (BPF_SWC(code) == BPF_K) {
			emit_imm32(tmp2, imm, ctx);
			swc = tmp2;
		}
		emit_awu_w32(dst, swc, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_AWSH | BPF_K:
		/*
		 * muw,div,mod awe handwed in the BPF_X case since thewe awe
		 * no WISC-V I-type equivawents.
		 */
		emit_awu_i32(dst, imm, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU | BPF_NEG:
		/*
		 * swc is ignowed---choose tmp2 as a dummy wegistew since it
		 * is not on the stack.
		 */
		emit_awu_w32(dst, tmp2, ctx, BPF_OP(code));
		bweak;

	case BPF_AWU | BPF_END | BPF_FWOM_WE:
	{
		const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);

		switch (imm) {
		case 16:
			emit(wv_swwi(wo(wd), wo(wd), 16), ctx);
			emit(wv_swwi(wo(wd), wo(wd), 16), ctx);
			fawwthwough;
		case 32:
			if (!ctx->pwog->aux->vewifiew_zext)
				emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
			bweak;
		case 64:
			/* Do nothing. */
			bweak;
		defauwt:
			pw_eww("bpf-jit: BPF_END imm %d invawid\n", imm);
			wetuwn -1;
		}

		bpf_put_weg64(dst, wd, ctx);
		bweak;
	}

	case BPF_AWU | BPF_END | BPF_FWOM_BE:
	{
		const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);

		switch (imm) {
		case 16:
			emit_wev16(wo(wd), ctx);
			if (!ctx->pwog->aux->vewifiew_zext)
				emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
			bweak;
		case 32:
			emit_wev32(wo(wd), ctx);
			if (!ctx->pwog->aux->vewifiew_zext)
				emit(wv_addi(hi(wd), WV_WEG_ZEWO, 0), ctx);
			bweak;
		case 64:
			/* Swap uppew and wowew hawves. */
			emit(wv_addi(WV_WEG_T0, wo(wd), 0), ctx);
			emit(wv_addi(wo(wd), hi(wd), 0), ctx);
			emit(wv_addi(hi(wd), WV_WEG_T0, 0), ctx);

			/* Swap each hawf. */
			emit_wev32(wo(wd), ctx);
			emit_wev32(hi(wd), ctx);
			bweak;
		defauwt:
			pw_eww("bpf-jit: BPF_END imm %d invawid\n", imm);
			wetuwn -1;
		}

		bpf_put_weg64(dst, wd, ctx);
		bweak;
	}

	case BPF_JMP | BPF_JA:
		wvoff = wv_offset(i, off, ctx);
		emit_jump_and_wink(WV_WEG_ZEWO, wvoff, fawse, ctx);
		bweak;

	case BPF_JMP | BPF_CAWW:
	{
		boow fixed;
		int wet;
		u64 addw;

		wet = bpf_jit_get_func_addw(ctx->pwog, insn, extwa_pass, &addw,
					    &fixed);
		if (wet < 0)
			wetuwn wet;
		emit_caww(fixed, addw, ctx);
		bweak;
	}

	case BPF_JMP | BPF_TAIW_CAWW:
		if (emit_bpf_taiw_caww(i, ctx))
			wetuwn -1;
		bweak;

	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JEQ | BPF_K:

	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_K:

	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_K:

	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_K:

	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_K:

	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_K:

	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_K:

	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_K:

	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_K:

	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_K:

	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_K:
		wvoff = wv_offset(i, off, ctx);
		if (BPF_SWC(code) == BPF_K) {
			s = ctx->ninsns;
			emit_imm32(tmp2, imm, ctx);
			swc = tmp2;
			e = ctx->ninsns;
			wvoff -= ninsns_wvoff(e - s);
		}

		if (is64)
			emit_bwanch_w64(dst, swc, wvoff, ctx, BPF_OP(code));
		ewse
			emit_bwanch_w32(dst, swc, wvoff, ctx, BPF_OP(code));
		bweak;

	case BPF_JMP | BPF_EXIT:
		if (i == ctx->pwog->wen - 1)
			bweak;

		wvoff = epiwogue_offset(ctx);
		emit_jump_and_wink(WV_WEG_ZEWO, wvoff, fawse, ctx);
		bweak;

	case BPF_WD | BPF_IMM | BPF_DW:
	{
		stwuct bpf_insn insn1 = insn[1];
		s32 imm_wo = imm;
		s32 imm_hi = insn1.imm;
		const s8 *wd = bpf_get_weg64(dst, tmp1, ctx);

		emit_imm64(wd, imm_hi, imm_wo, ctx);
		bpf_put_weg64(dst, wd, ctx);
		wetuwn 1;
	}

	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_DW:
		if (emit_woad_w64(dst, swc, off, ctx, BPF_SIZE(code)))
			wetuwn -1;
		bweak;

	/* specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;

	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_DW:

	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_DW:
		if (BPF_CWASS(code) == BPF_ST) {
			emit_imm32(tmp2, imm, ctx);
			swc = tmp2;
		}

		if (emit_stowe_w64(dst, swc, off, ctx, BPF_SIZE(code),
				   BPF_MODE(code)))
			wetuwn -1;
		bweak;

	case BPF_STX | BPF_ATOMIC | BPF_W:
		if (insn->imm != BPF_ADD) {
			pw_info_once(
				"bpf-jit: not suppowted: atomic opewation %02x ***\n",
				insn->imm);
			wetuwn -EFAUWT;
		}

		if (emit_stowe_w64(dst, swc, off, ctx, BPF_SIZE(code),
				   BPF_MODE(code)))
			wetuwn -1;
		bweak;

	/* No hawdwawe suppowt fow 8-byte atomics in WV32. */
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		/* Fawwthwough. */

notsuppowted:
		pw_info_once("bpf-jit: not suppowted: opcode %02x ***\n", code);
		wetuwn -EFAUWT;

	defauwt:
		pw_eww("bpf-jit: unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void bpf_jit_buiwd_pwowogue(stwuct wv_jit_context *ctx)
{
	const s8 *fp = bpf2wv32[BPF_WEG_FP];
	const s8 *w1 = bpf2wv32[BPF_WEG_1];
	int stack_adjust = 0;
	int bpf_stack_adjust =
		wound_up(ctx->pwog->aux->stack_depth, STACK_AWIGN);

	/* Make space fow cawwee-saved wegistews. */
	stack_adjust += NW_SAVED_WEGISTEWS * sizeof(u32);
	/* Make space fow BPF wegistews on stack. */
	stack_adjust += BPF_JIT_SCWATCH_WEGS * sizeof(u32);
	/* Make space fow BPF stack. */
	stack_adjust += bpf_stack_adjust;
	/* Wound up fow stack awignment. */
	stack_adjust = wound_up(stack_adjust, STACK_AWIGN);

	/*
	 * The fiwst instwuction sets the taiw-caww-countew (TCC) wegistew.
	 * This instwuction is skipped by taiw cawws.
	 */
	emit(wv_addi(WV_WEG_TCC, WV_WEG_ZEWO, MAX_TAIW_CAWW_CNT), ctx);

	emit(wv_addi(WV_WEG_SP, WV_WEG_SP, -stack_adjust), ctx);

	/* Save cawwee-save wegistews. */
	emit(wv_sw(WV_WEG_SP, stack_adjust - 4, WV_WEG_WA), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 8, WV_WEG_FP), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 12, WV_WEG_S1), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 16, WV_WEG_S2), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 20, WV_WEG_S3), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 24, WV_WEG_S4), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 28, WV_WEG_S5), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 32, WV_WEG_S6), ctx);
	emit(wv_sw(WV_WEG_SP, stack_adjust - 36, WV_WEG_S7), ctx);

	/* Set fp: used as the base addwess fow stacked BPF wegistews. */
	emit(wv_addi(WV_WEG_FP, WV_WEG_SP, stack_adjust), ctx);

	/* Set up BPF fwame pointew. */
	emit(wv_addi(wo(fp), WV_WEG_SP, bpf_stack_adjust), ctx);
	emit(wv_addi(hi(fp), WV_WEG_ZEWO, 0), ctx);

	/* Set up BPF context pointew. */
	emit(wv_addi(wo(w1), WV_WEG_A0, 0), ctx);
	emit(wv_addi(hi(w1), WV_WEG_ZEWO, 0), ctx);

	ctx->stack_size = stack_adjust;
}

void bpf_jit_buiwd_epiwogue(stwuct wv_jit_context *ctx)
{
	__buiwd_epiwogue(fawse, ctx);
}
