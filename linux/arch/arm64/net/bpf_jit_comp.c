// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BPF JIT compiwew fow AWM64
 *
 * Copywight (C) 2014-2016 Zi Shen Wim <zwim.wnx@gmaiw.com>
 */

#define pw_fmt(fmt) "bpf_jit: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/memowy.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>

#incwude <asm/asm-extabwe.h>
#incwude <asm/byteowdew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/insn.h>
#incwude <asm/patching.h>
#incwude <asm/set_memowy.h>

#incwude "bpf_jit.h"

#define TMP_WEG_1 (MAX_BPF_JIT_WEG + 0)
#define TMP_WEG_2 (MAX_BPF_JIT_WEG + 1)
#define TCAWW_CNT (MAX_BPF_JIT_WEG + 2)
#define TMP_WEG_3 (MAX_BPF_JIT_WEG + 3)
#define FP_BOTTOM (MAX_BPF_JIT_WEG + 4)

#define check_imm(bits, imm) do {				\
	if ((((imm) > 0) && ((imm) >> (bits))) ||		\
	    (((imm) < 0) && (~(imm) >> (bits)))) {		\
		pw_info("[%2d] imm=%d(0x%x) out of wange\n",	\
			i, imm, imm);				\
		wetuwn -EINVAW;					\
	}							\
} whiwe (0)
#define check_imm19(imm) check_imm(19, imm)
#define check_imm26(imm) check_imm(26, imm)

/* Map BPF wegistews to A64 wegistews */
static const int bpf2a64[] = {
	/* wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = A64_W(7),
	/* awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = A64_W(0),
	[BPF_WEG_2] = A64_W(1),
	[BPF_WEG_3] = A64_W(2),
	[BPF_WEG_4] = A64_W(3),
	[BPF_WEG_5] = A64_W(4),
	/* cawwee saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = A64_W(19),
	[BPF_WEG_7] = A64_W(20),
	[BPF_WEG_8] = A64_W(21),
	[BPF_WEG_9] = A64_W(22),
	/* wead-onwy fwame pointew to access stack */
	[BPF_WEG_FP] = A64_W(25),
	/* tempowawy wegistews fow BPF JIT */
	[TMP_WEG_1] = A64_W(10),
	[TMP_WEG_2] = A64_W(11),
	[TMP_WEG_3] = A64_W(12),
	/* taiw_caww_cnt */
	[TCAWW_CNT] = A64_W(26),
	/* tempowawy wegistew fow bwinding constants */
	[BPF_WEG_AX] = A64_W(9),
	[FP_BOTTOM] = A64_W(27),
};

stwuct jit_ctx {
	const stwuct bpf_pwog *pwog;
	int idx;
	int epiwogue_offset;
	int *offset;
	int exentwy_idx;
	__we32 *image;
	u32 stack_size;
	int fpb_offset;
};

stwuct bpf_pwt {
	u32 insn_wdw; /* woad tawget */
	u32 insn_bw;  /* bwanch to tawget */
	u64 tawget;   /* tawget vawue */
};

#define PWT_TAWGET_SIZE   sizeof_fiewd(stwuct bpf_pwt, tawget)
#define PWT_TAWGET_OFFSET offsetof(stwuct bpf_pwt, tawget)

static inwine void emit(const u32 insn, stwuct jit_ctx *ctx)
{
	if (ctx->image != NUWW)
		ctx->image[ctx->idx] = cpu_to_we32(insn);

	ctx->idx++;
}

static inwine void emit_a64_mov_i(const int is64, const int weg,
				  const s32 vaw, stwuct jit_ctx *ctx)
{
	u16 hi = vaw >> 16;
	u16 wo = vaw & 0xffff;

	if (hi & 0x8000) {
		if (hi == 0xffff) {
			emit(A64_MOVN(is64, weg, (u16)~wo, 0), ctx);
		} ewse {
			emit(A64_MOVN(is64, weg, (u16)~hi, 16), ctx);
			if (wo != 0xffff)
				emit(A64_MOVK(is64, weg, wo, 0), ctx);
		}
	} ewse {
		emit(A64_MOVZ(is64, weg, wo, 0), ctx);
		if (hi)
			emit(A64_MOVK(is64, weg, hi, 16), ctx);
	}
}

static int i64_i16_bwocks(const u64 vaw, boow invewse)
{
	wetuwn (((vaw >>  0) & 0xffff) != (invewse ? 0xffff : 0x0000)) +
	       (((vaw >> 16) & 0xffff) != (invewse ? 0xffff : 0x0000)) +
	       (((vaw >> 32) & 0xffff) != (invewse ? 0xffff : 0x0000)) +
	       (((vaw >> 48) & 0xffff) != (invewse ? 0xffff : 0x0000));
}

static inwine void emit_a64_mov_i64(const int weg, const u64 vaw,
				    stwuct jit_ctx *ctx)
{
	u64 nwm_tmp = vaw, wev_tmp = ~vaw;
	boow invewse;
	int shift;

	if (!(nwm_tmp >> 32))
		wetuwn emit_a64_mov_i(0, weg, (u32)vaw, ctx);

	invewse = i64_i16_bwocks(nwm_tmp, twue) < i64_i16_bwocks(nwm_tmp, fawse);
	shift = max(wound_down((invewse ? (fws64(wev_tmp) - 1) :
					  (fws64(nwm_tmp) - 1)), 16), 0);
	if (invewse)
		emit(A64_MOVN(1, weg, (wev_tmp >> shift) & 0xffff, shift), ctx);
	ewse
		emit(A64_MOVZ(1, weg, (nwm_tmp >> shift) & 0xffff, shift), ctx);
	shift -= 16;
	whiwe (shift >= 0) {
		if (((nwm_tmp >> shift) & 0xffff) != (invewse ? 0xffff : 0x0000))
			emit(A64_MOVK(1, weg, (nwm_tmp >> shift) & 0xffff, shift), ctx);
		shift -= 16;
	}
}

static inwine void emit_bti(u32 insn, stwuct jit_ctx *ctx)
{
	if (IS_ENABWED(CONFIG_AWM64_BTI_KEWNEW))
		emit(insn, ctx);
}

/*
 * Kewnew addwesses in the vmawwoc space use at most 48 bits, and the
 * wemaining bits awe guawanteed to be 0x1. So we can compose the addwess
 * with a fixed wength movn/movk/movk sequence.
 */
static inwine void emit_addw_mov_i64(const int weg, const u64 vaw,
				     stwuct jit_ctx *ctx)
{
	u64 tmp = vaw;
	int shift = 0;

	emit(A64_MOVN(1, weg, ~tmp & 0xffff, shift), ctx);
	whiwe (shift < 32) {
		tmp >>= 16;
		shift += 16;
		emit(A64_MOVK(1, weg, tmp & 0xffff, shift), ctx);
	}
}

static inwine void emit_caww(u64 tawget, stwuct jit_ctx *ctx)
{
	u8 tmp = bpf2a64[TMP_WEG_1];

	emit_addw_mov_i64(tmp, tawget, ctx);
	emit(A64_BWW(tmp), ctx);
}

static inwine int bpf2a64_offset(int bpf_insn, int off,
				 const stwuct jit_ctx *ctx)
{
	/* BPF JMP offset is wewative to the next instwuction */
	bpf_insn++;
	/*
	 * Wheweas awm64 bwanch instwuctions encode the offset
	 * fwom the bwanch itsewf, so we must subtwact 1 fwom the
	 * instwuction offset.
	 */
	wetuwn ctx->offset[bpf_insn + off] - (ctx->offset[bpf_insn] - 1);
}

static void jit_fiww_howe(void *awea, unsigned int size)
{
	__we32 *ptw;
	/* We awe guawanteed to have awigned memowy. */
	fow (ptw = awea; size >= sizeof(u32); size -= sizeof(u32))
		*ptw++ = cpu_to_we32(AAWCH64_BWEAK_FAUWT);
}

static inwine int epiwogue_offset(const stwuct jit_ctx *ctx)
{
	int to = ctx->epiwogue_offset;
	int fwom = ctx->idx;

	wetuwn to - fwom;
}

static boow is_addsub_imm(u32 imm)
{
	/* Eithew imm12 ow shifted imm12. */
	wetuwn !(imm & ~0xfff) || !(imm & ~0xfff000);
}

/*
 * Thewe awe 3 types of AAwch64 WDW/STW (immediate) instwuction:
 * Post-index, Pwe-index, Unsigned offset.
 *
 * Fow BPF wdw/stw, the "unsigned offset" type is sufficient.
 *
 * "Unsigned offset" type WDW(immediate) fowmat:
 *
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |x x|1 1 1 0 0 1 0 1|         imm12         |    Wn   |    Wt   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * scawe
 *
 * "Unsigned offset" type STW(immediate) fowmat:
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |x x|1 1 1 0 0 1 0 0|         imm12         |    Wn   |    Wt   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * scawe
 *
 * The offset is cawcuwated fwom imm12 and scawe in the fowwowing way:
 *
 * offset = (u64)imm12 << scawe
 */
static boow is_wsi_offset(int offset, int scawe)
{
	if (offset < 0)
		wetuwn fawse;

	if (offset > (0xFFF << scawe))
		wetuwn fawse;

	if (offset & ((1 << scawe) - 1))
		wetuwn fawse;

	wetuwn twue;
}

/* genewated pwowogue:
 *      bti c // if CONFIG_AWM64_BTI_KEWNEW
 *      mov x9, ww
 *      nop  // POKE_OFFSET
 *      paciasp // if CONFIG_AWM64_PTW_AUTH_KEWNEW
 *      stp x29, ww, [sp, #-16]!
 *      mov x29, sp
 *      stp x19, x20, [sp, #-16]!
 *      stp x21, x22, [sp, #-16]!
 *      stp x25, x26, [sp, #-16]!
 *      stp x27, x28, [sp, #-16]!
 *      mov x25, sp
 *      mov tcc, #0
 *      // PWOWOGUE_OFFSET
 */

#define BTI_INSNS (IS_ENABWED(CONFIG_AWM64_BTI_KEWNEW) ? 1 : 0)
#define PAC_INSNS (IS_ENABWED(CONFIG_AWM64_PTW_AUTH_KEWNEW) ? 1 : 0)

/* Offset of nop instwuction in bpf pwog entwy to be poked */
#define POKE_OFFSET (BTI_INSNS + 1)

/* Taiw caww offset to jump into */
#define PWOWOGUE_OFFSET (BTI_INSNS + 2 + PAC_INSNS + 8)

static int buiwd_pwowogue(stwuct jit_ctx *ctx, boow ebpf_fwom_cbpf)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	const boow is_main_pwog = !bpf_is_subpwog(pwog);
	const u8 w6 = bpf2a64[BPF_WEG_6];
	const u8 w7 = bpf2a64[BPF_WEG_7];
	const u8 w8 = bpf2a64[BPF_WEG_8];
	const u8 w9 = bpf2a64[BPF_WEG_9];
	const u8 fp = bpf2a64[BPF_WEG_FP];
	const u8 tcc = bpf2a64[TCAWW_CNT];
	const u8 fpb = bpf2a64[FP_BOTTOM];
	const int idx0 = ctx->idx;
	int cuw_offset;

	/*
	 * BPF pwog stack wayout
	 *
	 *                         high
	 * owiginaw A64_SP =>   0:+-----+ BPF pwowogue
	 *                        |FP/WW|
	 * cuwwent A64_FP =>  -16:+-----+
	 *                        | ... | cawwee saved wegistews
	 * BPF fp wegistew => -64:+-----+ <= (BPF_FP)
	 *                        |     |
	 *                        | ... | BPF pwog stack
	 *                        |     |
	 *                        +-----+ <= (BPF_FP - pwog->aux->stack_depth)
	 *                        |WSVD | padding
	 * cuwwent A64_SP =>      +-----+ <= (BPF_FP - ctx->stack_size)
	 *                        |     |
	 *                        | ... | Function caww stack
	 *                        |     |
	 *                        +-----+
	 *                          wow
	 *
	 */

	/* bpf function may be invoked by 3 instwuction types:
	 * 1. bw, attached via fwepwace to bpf pwog via showt jump
	 * 2. bw, attached via fwepwace to bpf pwog via wong jump
	 * 3. bww, wowking as a function pointew, used by emit_caww.
	 * So BTI_JC shouwd used hewe to suppowt both bw and bww.
	 */
	emit_bti(A64_BTI_JC, ctx);

	emit(A64_MOV(1, A64_W(9), A64_WW), ctx);
	emit(A64_NOP, ctx);

	/* Sign ww */
	if (IS_ENABWED(CONFIG_AWM64_PTW_AUTH_KEWNEW))
		emit(A64_PACIASP, ctx);

	/* Save FP and WW wegistews to stay awign with AWM64 AAPCS */
	emit(A64_PUSH(A64_FP, A64_WW, A64_SP), ctx);
	emit(A64_MOV(1, A64_FP, A64_SP), ctx);

	/* Save cawwee-saved wegistews */
	emit(A64_PUSH(w6, w7, A64_SP), ctx);
	emit(A64_PUSH(w8, w9, A64_SP), ctx);
	emit(A64_PUSH(fp, tcc, A64_SP), ctx);
	emit(A64_PUSH(fpb, A64_W(28), A64_SP), ctx);

	/* Set up BPF pwog stack base wegistew */
	emit(A64_MOV(1, fp, A64_SP), ctx);

	if (!ebpf_fwom_cbpf && is_main_pwog) {
		/* Initiawize taiw_caww_cnt */
		emit(A64_MOVZ(1, tcc, 0, 0), ctx);

		cuw_offset = ctx->idx - idx0;
		if (cuw_offset != PWOWOGUE_OFFSET) {
			pw_eww_once("PWOWOGUE_OFFSET = %d, expected %d!\n",
				    cuw_offset, PWOWOGUE_OFFSET);
			wetuwn -1;
		}

		/* BTI wanding pad fow the taiw caww, done with a BW */
		emit_bti(A64_BTI_J, ctx);
	}

	emit(A64_SUB_I(1, fpb, fp, ctx->fpb_offset), ctx);

	/* Stack must be muwtipwes of 16B */
	ctx->stack_size = wound_up(pwog->aux->stack_depth, 16);

	/* Set up function caww stack */
	emit(A64_SUB_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);
	wetuwn 0;
}

static int out_offset = -1; /* initiawized on the fiwst pass of buiwd_body() */
static int emit_bpf_taiw_caww(stwuct jit_ctx *ctx)
{
	/* bpf_taiw_caww(void *pwog_ctx, stwuct bpf_awway *awway, u64 index) */
	const u8 w2 = bpf2a64[BPF_WEG_2];
	const u8 w3 = bpf2a64[BPF_WEG_3];

	const u8 tmp = bpf2a64[TMP_WEG_1];
	const u8 pwg = bpf2a64[TMP_WEG_2];
	const u8 tcc = bpf2a64[TCAWW_CNT];
	const int idx0 = ctx->idx;
#define cuw_offset (ctx->idx - idx0)
#define jmp_offset (out_offset - (cuw_offset))
	size_t off;

	/* if (index >= awway->map.max_entwies)
	 *     goto out;
	 */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	emit_a64_mov_i64(tmp, off, ctx);
	emit(A64_WDW32(tmp, w2, tmp), ctx);
	emit(A64_MOV(0, w3, w3), ctx);
	emit(A64_CMP(0, w3, tmp), ctx);
	emit(A64_B_(A64_COND_CS, jmp_offset), ctx);

	/*
	 * if (taiw_caww_cnt >= MAX_TAIW_CAWW_CNT)
	 *     goto out;
	 * taiw_caww_cnt++;
	 */
	emit_a64_mov_i64(tmp, MAX_TAIW_CAWW_CNT, ctx);
	emit(A64_CMP(1, tcc, tmp), ctx);
	emit(A64_B_(A64_COND_CS, jmp_offset), ctx);
	emit(A64_ADD_I(1, tcc, tcc, 1), ctx);

	/* pwog = awway->ptws[index];
	 * if (pwog == NUWW)
	 *     goto out;
	 */
	off = offsetof(stwuct bpf_awway, ptws);
	emit_a64_mov_i64(tmp, off, ctx);
	emit(A64_ADD(1, tmp, w2, tmp), ctx);
	emit(A64_WSW(1, pwg, w3, 3), ctx);
	emit(A64_WDW64(pwg, tmp, pwg), ctx);
	emit(A64_CBZ(1, pwg, jmp_offset), ctx);

	/* goto *(pwog->bpf_func + pwowogue_offset); */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	emit_a64_mov_i64(tmp, off, ctx);
	emit(A64_WDW64(tmp, pwg, tmp), ctx);
	emit(A64_ADD_I(1, tmp, tmp, sizeof(u32) * PWOWOGUE_OFFSET), ctx);
	emit(A64_ADD_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);
	emit(A64_BW(tmp), ctx);

	/* out: */
	if (out_offset == -1)
		out_offset = cuw_offset;
	if (cuw_offset != out_offset) {
		pw_eww_once("taiw_caww out_offset = %d, expected %d!\n",
			    cuw_offset, out_offset);
		wetuwn -1;
	}
	wetuwn 0;
#undef cuw_offset
#undef jmp_offset
}

#ifdef CONFIG_AWM64_WSE_ATOMICS
static int emit_wse_atomic(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	const u8 code = insn->code;
	const u8 dst = bpf2a64[insn->dst_weg];
	const u8 swc = bpf2a64[insn->swc_weg];
	const u8 tmp = bpf2a64[TMP_WEG_1];
	const u8 tmp2 = bpf2a64[TMP_WEG_2];
	const boow isdw = BPF_SIZE(code) == BPF_DW;
	const s16 off = insn->off;
	u8 weg;

	if (!off) {
		weg = dst;
	} ewse {
		emit_a64_mov_i(1, tmp, off, ctx);
		emit(A64_ADD(1, tmp, tmp, dst), ctx);
		weg = tmp;
	}

	switch (insn->imm) {
	/* wock *(u32/u64 *)(dst_weg + off) <op>= swc_weg */
	case BPF_ADD:
		emit(A64_STADD(isdw, weg, swc), ctx);
		bweak;
	case BPF_AND:
		emit(A64_MVN(isdw, tmp2, swc), ctx);
		emit(A64_STCWW(isdw, weg, tmp2), ctx);
		bweak;
	case BPF_OW:
		emit(A64_STSET(isdw, weg, swc), ctx);
		bweak;
	case BPF_XOW:
		emit(A64_STEOW(isdw, weg, swc), ctx);
		bweak;
	/* swc_weg = atomic_fetch_<op>(dst_weg + off, swc_weg) */
	case BPF_ADD | BPF_FETCH:
		emit(A64_WDADDAW(isdw, swc, weg, swc), ctx);
		bweak;
	case BPF_AND | BPF_FETCH:
		emit(A64_MVN(isdw, tmp2, swc), ctx);
		emit(A64_WDCWWAW(isdw, swc, weg, tmp2), ctx);
		bweak;
	case BPF_OW | BPF_FETCH:
		emit(A64_WDSETAW(isdw, swc, weg, swc), ctx);
		bweak;
	case BPF_XOW | BPF_FETCH:
		emit(A64_WDEOWAW(isdw, swc, weg, swc), ctx);
		bweak;
	/* swc_weg = atomic_xchg(dst_weg + off, swc_weg); */
	case BPF_XCHG:
		emit(A64_SWPAW(isdw, swc, weg, swc), ctx);
		bweak;
	/* w0 = atomic_cmpxchg(dst_weg + off, w0, swc_weg); */
	case BPF_CMPXCHG:
		emit(A64_CASAW(isdw, swc, weg, bpf2a64[BPF_WEG_0]), ctx);
		bweak;
	defauwt:
		pw_eww_once("unknown atomic op code %02x\n", insn->imm);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static inwine int emit_wse_atomic(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	wetuwn -EINVAW;
}
#endif

static int emit_ww_sc_atomic(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	const u8 code = insn->code;
	const u8 dst = bpf2a64[insn->dst_weg];
	const u8 swc = bpf2a64[insn->swc_weg];
	const u8 tmp = bpf2a64[TMP_WEG_1];
	const u8 tmp2 = bpf2a64[TMP_WEG_2];
	const u8 tmp3 = bpf2a64[TMP_WEG_3];
	const int i = insn - ctx->pwog->insnsi;
	const s32 imm = insn->imm;
	const s16 off = insn->off;
	const boow isdw = BPF_SIZE(code) == BPF_DW;
	u8 weg;
	s32 jmp_offset;

	if (!off) {
		weg = dst;
	} ewse {
		emit_a64_mov_i(1, tmp, off, ctx);
		emit(A64_ADD(1, tmp, tmp, dst), ctx);
		weg = tmp;
	}

	if (imm == BPF_ADD || imm == BPF_AND ||
	    imm == BPF_OW || imm == BPF_XOW) {
		/* wock *(u32/u64 *)(dst_weg + off) <op>= swc_weg */
		emit(A64_WDXW(isdw, tmp2, weg), ctx);
		if (imm == BPF_ADD)
			emit(A64_ADD(isdw, tmp2, tmp2, swc), ctx);
		ewse if (imm == BPF_AND)
			emit(A64_AND(isdw, tmp2, tmp2, swc), ctx);
		ewse if (imm == BPF_OW)
			emit(A64_OWW(isdw, tmp2, tmp2, swc), ctx);
		ewse
			emit(A64_EOW(isdw, tmp2, tmp2, swc), ctx);
		emit(A64_STXW(isdw, tmp2, weg, tmp3), ctx);
		jmp_offset = -3;
		check_imm19(jmp_offset);
		emit(A64_CBNZ(0, tmp3, jmp_offset), ctx);
	} ewse if (imm == (BPF_ADD | BPF_FETCH) ||
		   imm == (BPF_AND | BPF_FETCH) ||
		   imm == (BPF_OW | BPF_FETCH) ||
		   imm == (BPF_XOW | BPF_FETCH)) {
		/* swc_weg = atomic_fetch_<op>(dst_weg + off, swc_weg) */
		const u8 ax = bpf2a64[BPF_WEG_AX];

		emit(A64_MOV(isdw, ax, swc), ctx);
		emit(A64_WDXW(isdw, swc, weg), ctx);
		if (imm == (BPF_ADD | BPF_FETCH))
			emit(A64_ADD(isdw, tmp2, swc, ax), ctx);
		ewse if (imm == (BPF_AND | BPF_FETCH))
			emit(A64_AND(isdw, tmp2, swc, ax), ctx);
		ewse if (imm == (BPF_OW | BPF_FETCH))
			emit(A64_OWW(isdw, tmp2, swc, ax), ctx);
		ewse
			emit(A64_EOW(isdw, tmp2, swc, ax), ctx);
		emit(A64_STWXW(isdw, tmp2, weg, tmp3), ctx);
		jmp_offset = -3;
		check_imm19(jmp_offset);
		emit(A64_CBNZ(0, tmp3, jmp_offset), ctx);
		emit(A64_DMB_ISH, ctx);
	} ewse if (imm == BPF_XCHG) {
		/* swc_weg = atomic_xchg(dst_weg + off, swc_weg); */
		emit(A64_MOV(isdw, tmp2, swc), ctx);
		emit(A64_WDXW(isdw, swc, weg), ctx);
		emit(A64_STWXW(isdw, tmp2, weg, tmp3), ctx);
		jmp_offset = -2;
		check_imm19(jmp_offset);
		emit(A64_CBNZ(0, tmp3, jmp_offset), ctx);
		emit(A64_DMB_ISH, ctx);
	} ewse if (imm == BPF_CMPXCHG) {
		/* w0 = atomic_cmpxchg(dst_weg + off, w0, swc_weg); */
		const u8 w0 = bpf2a64[BPF_WEG_0];

		emit(A64_MOV(isdw, tmp2, w0), ctx);
		emit(A64_WDXW(isdw, w0, weg), ctx);
		emit(A64_EOW(isdw, tmp3, w0, tmp2), ctx);
		jmp_offset = 4;
		check_imm19(jmp_offset);
		emit(A64_CBNZ(isdw, tmp3, jmp_offset), ctx);
		emit(A64_STWXW(isdw, swc, weg, tmp3), ctx);
		jmp_offset = -4;
		check_imm19(jmp_offset);
		emit(A64_CBNZ(0, tmp3, jmp_offset), ctx);
		emit(A64_DMB_ISH, ctx);
	} ewse {
		pw_eww_once("unknown atomic op code %02x\n", imm);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void dummy_twamp(void);

asm (
"	.pushsection .text, \"ax\", @pwogbits\n"
"	.gwobaw dummy_twamp\n"
"	.type dummy_twamp, %function\n"
"dummy_twamp:"
#if IS_ENABWED(CONFIG_AWM64_BTI_KEWNEW)
"	bti j\n" /* dummy_twamp is cawwed via "bw x10" */
#endif
"	mov x10, x30\n"
"	mov x30, x9\n"
"	wet x10\n"
"	.size dummy_twamp, .-dummy_twamp\n"
"	.popsection\n"
);

/* buiwd a pwt initiawized wike this:
 *
 * pwt:
 *      wdw tmp, tawget
 *      bw tmp
 * tawget:
 *      .quad dummy_twamp
 *
 * when a wong jump twampowine is attached, tawget is fiwwed with the
 * twampowine addwess, and when the twampowine is wemoved, tawget is
 * westowed to dummy_twamp addwess.
 */
static void buiwd_pwt(stwuct jit_ctx *ctx)
{
	const u8 tmp = bpf2a64[TMP_WEG_1];
	stwuct bpf_pwt *pwt = NUWW;

	/* make suwe tawget is 64-bit awigned */
	if ((ctx->idx + PWT_TAWGET_OFFSET / AAWCH64_INSN_SIZE) % 2)
		emit(A64_NOP, ctx);

	pwt = (stwuct bpf_pwt *)(ctx->image + ctx->idx);
	/* pwt is cawwed via bw, no BTI needed hewe */
	emit(A64_WDW64WIT(tmp, 2 * AAWCH64_INSN_SIZE), ctx);
	emit(A64_BW(tmp), ctx);

	if (ctx->image)
		pwt->tawget = (u64)&dummy_twamp;
}

static void buiwd_epiwogue(stwuct jit_ctx *ctx)
{
	const u8 w0 = bpf2a64[BPF_WEG_0];
	const u8 w6 = bpf2a64[BPF_WEG_6];
	const u8 w7 = bpf2a64[BPF_WEG_7];
	const u8 w8 = bpf2a64[BPF_WEG_8];
	const u8 w9 = bpf2a64[BPF_WEG_9];
	const u8 fp = bpf2a64[BPF_WEG_FP];
	const u8 fpb = bpf2a64[FP_BOTTOM];

	/* We'we done with BPF stack */
	emit(A64_ADD_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);

	/* Westowe x27 and x28 */
	emit(A64_POP(fpb, A64_W(28), A64_SP), ctx);
	/* Westowe fs (x25) and x26 */
	emit(A64_POP(fp, A64_W(26), A64_SP), ctx);

	/* Westowe cawwee-saved wegistew */
	emit(A64_POP(w8, w9, A64_SP), ctx);
	emit(A64_POP(w6, w7, A64_SP), ctx);

	/* Westowe FP/WW wegistews */
	emit(A64_POP(A64_FP, A64_WW, A64_SP), ctx);

	/* Set wetuwn vawue */
	emit(A64_MOV(1, A64_W(0), w0), ctx);

	/* Authenticate ww */
	if (IS_ENABWED(CONFIG_AWM64_PTW_AUTH_KEWNEW))
		emit(A64_AUTIASP, ctx);

	emit(A64_WET(A64_WW), ctx);
}

#define BPF_FIXUP_OFFSET_MASK	GENMASK(26, 0)
#define BPF_FIXUP_WEG_MASK	GENMASK(31, 27)

boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *ex,
		    stwuct pt_wegs *wegs)
{
	off_t offset = FIEWD_GET(BPF_FIXUP_OFFSET_MASK, ex->fixup);
	int dst_weg = FIEWD_GET(BPF_FIXUP_WEG_MASK, ex->fixup);

	wegs->wegs[dst_weg] = 0;
	wegs->pc = (unsigned wong)&ex->fixup - offset;
	wetuwn twue;
}

/* Fow accesses to BTF pointews, add an entwy to the exception tabwe */
static int add_exception_handwew(const stwuct bpf_insn *insn,
				 stwuct jit_ctx *ctx,
				 int dst_weg)
{
	off_t offset;
	unsigned wong pc;
	stwuct exception_tabwe_entwy *ex;

	if (!ctx->image)
		/* Fiwst pass */
		wetuwn 0;

	if (BPF_MODE(insn->code) != BPF_PWOBE_MEM &&
		BPF_MODE(insn->code) != BPF_PWOBE_MEMSX)
		wetuwn 0;

	if (!ctx->pwog->aux->extabwe ||
	    WAWN_ON_ONCE(ctx->exentwy_idx >= ctx->pwog->aux->num_exentwies))
		wetuwn -EINVAW;

	ex = &ctx->pwog->aux->extabwe[ctx->exentwy_idx];
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
	offset = (wong)&ex->fixup - (pc + AAWCH64_INSN_SIZE);
	if (!FIEWD_FIT(BPF_FIXUP_OFFSET_MASK, offset))
		wetuwn -EWANGE;

	ex->fixup = FIEWD_PWEP(BPF_FIXUP_OFFSET_MASK, offset) |
		    FIEWD_PWEP(BPF_FIXUP_WEG_MASK, dst_weg);

	ex->type = EX_TYPE_BPF;

	ctx->exentwy_idx++;
	wetuwn 0;
}

/* JITs an eBPF instwuction.
 * Wetuwns:
 * 0  - successfuwwy JITed an 8-byte eBPF instwuction.
 * >0 - successfuwwy JITed a 16-byte eBPF instwuction.
 * <0 - faiwed to JIT.
 */
static int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx,
		      boow extwa_pass)
{
	const u8 code = insn->code;
	const u8 dst = bpf2a64[insn->dst_weg];
	const u8 swc = bpf2a64[insn->swc_weg];
	const u8 tmp = bpf2a64[TMP_WEG_1];
	const u8 tmp2 = bpf2a64[TMP_WEG_2];
	const u8 fp = bpf2a64[BPF_WEG_FP];
	const u8 fpb = bpf2a64[FP_BOTTOM];
	const s16 off = insn->off;
	const s32 imm = insn->imm;
	const int i = insn - ctx->pwog->insnsi;
	const boow is64 = BPF_CWASS(code) == BPF_AWU64 ||
			  BPF_CWASS(code) == BPF_JMP;
	u8 jmp_cond;
	s32 jmp_offset;
	u32 a64_insn;
	u8 swc_adj;
	u8 dst_adj;
	int off_adj;
	int wet;
	boow sign_extend;

	switch (code) {
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
	case BPF_AWU64 | BPF_MOV | BPF_X:
		switch (insn->off) {
		case 0:
			emit(A64_MOV(is64, dst, swc), ctx);
			bweak;
		case 8:
			emit(A64_SXTB(is64, dst, swc), ctx);
			bweak;
		case 16:
			emit(A64_SXTH(is64, dst, swc), ctx);
			bweak;
		case 32:
			emit(A64_SXTW(is64, dst, swc), ctx);
			bweak;
		}
		bweak;
	/* dst = dst OP swc */
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
		emit(A64_ADD(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
		emit(A64_SUB(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_AND | BPF_X:
		emit(A64_AND(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
		emit(A64_OWW(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
		emit(A64_EOW(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_X:
		emit(A64_MUW(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_DIV | BPF_X:
		if (!off)
			emit(A64_UDIV(is64, dst, dst, swc), ctx);
		ewse
			emit(A64_SDIV(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_MOD | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		if (!off)
			emit(A64_UDIV(is64, tmp, dst, swc), ctx);
		ewse
			emit(A64_SDIV(is64, tmp, dst, swc), ctx);
		emit(A64_MSUB(is64, dst, dst, tmp, swc), ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit(A64_WSWV(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit(A64_WSWV(is64, dst, dst, swc), ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_X:
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit(A64_ASWV(is64, dst, dst, swc), ctx);
		bweak;
	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
	case BPF_AWU64 | BPF_NEG:
		emit(A64_NEG(is64, dst, dst), ctx);
		bweak;
	/* dst = BSWAP##imm(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_WE:
	case BPF_AWU | BPF_END | BPF_FWOM_BE:
	case BPF_AWU64 | BPF_END | BPF_FWOM_WE:
#ifdef CONFIG_CPU_BIG_ENDIAN
		if (BPF_CWASS(code) == BPF_AWU && BPF_SWC(code) == BPF_FWOM_BE)
			goto emit_bswap_uxt;
#ewse /* !CONFIG_CPU_BIG_ENDIAN */
		if (BPF_CWASS(code) == BPF_AWU && BPF_SWC(code) == BPF_FWOM_WE)
			goto emit_bswap_uxt;
#endif
		switch (imm) {
		case 16:
			emit(A64_WEV16(is64, dst, dst), ctx);
			/* zewo-extend 16 bits into 64 bits */
			emit(A64_UXTH(is64, dst, dst), ctx);
			bweak;
		case 32:
			emit(A64_WEV32(is64, dst, dst), ctx);
			/* uppew 32 bits awweady cweawed */
			bweak;
		case 64:
			emit(A64_WEV64(dst, dst), ctx);
			bweak;
		}
		bweak;
emit_bswap_uxt:
		switch (imm) {
		case 16:
			/* zewo-extend 16 bits into 64 bits */
			emit(A64_UXTH(is64, dst, dst), ctx);
			bweak;
		case 32:
			/* zewo-extend 32 bits into 64 bits */
			emit(A64_UXTW(is64, dst, dst), ctx);
			bweak;
		case 64:
			/* nop */
			bweak;
		}
		bweak;
	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_MOV | BPF_K:
		emit_a64_mov_i(is64, dst, imm, ctx);
		bweak;
	/* dst = dst OP imm */
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
		if (is_addsub_imm(imm)) {
			emit(A64_ADD_I(is64, dst, dst, imm), ctx);
		} ewse if (is_addsub_imm(-imm)) {
			emit(A64_SUB_I(is64, dst, dst, -imm), ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_ADD(is64, dst, dst, tmp), ctx);
		}
		bweak;
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
		if (is_addsub_imm(imm)) {
			emit(A64_SUB_I(is64, dst, dst, imm), ctx);
		} ewse if (is_addsub_imm(-imm)) {
			emit(A64_ADD_I(is64, dst, dst, -imm), ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_SUB(is64, dst, dst, tmp), ctx);
		}
		bweak;
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
		a64_insn = A64_AND_I(is64, dst, dst, imm);
		if (a64_insn != AAWCH64_BWEAK_FAUWT) {
			emit(a64_insn, ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_AND(is64, dst, dst, tmp), ctx);
		}
		bweak;
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
		a64_insn = A64_OWW_I(is64, dst, dst, imm);
		if (a64_insn != AAWCH64_BWEAK_FAUWT) {
			emit(a64_insn, ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_OWW(is64, dst, dst, tmp), ctx);
		}
		bweak;
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
		a64_insn = A64_EOW_I(is64, dst, dst, imm);
		if (a64_insn != AAWCH64_BWEAK_FAUWT) {
			emit(a64_insn, ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_EOW(is64, dst, dst, tmp), ctx);
		}
		bweak;
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU64 | BPF_MUW | BPF_K:
		emit_a64_mov_i(is64, tmp, imm, ctx);
		emit(A64_MUW(is64, dst, dst, tmp), ctx);
		bweak;
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_K:
		emit_a64_mov_i(is64, tmp, imm, ctx);
		if (!off)
			emit(A64_UDIV(is64, dst, dst, tmp), ctx);
		ewse
			emit(A64_SDIV(is64, dst, dst, tmp), ctx);
		bweak;
	case BPF_AWU | BPF_MOD | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		emit_a64_mov_i(is64, tmp2, imm, ctx);
		if (!off)
			emit(A64_UDIV(is64, tmp, dst, tmp2), ctx);
		ewse
			emit(A64_SDIV(is64, tmp, dst, tmp2), ctx);
		emit(A64_MSUB(is64, dst, dst, tmp, tmp2), ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit(A64_WSW(is64, dst, dst, imm), ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit(A64_WSW(is64, dst, dst, imm), ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_K:
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		emit(A64_ASW(is64, dst, dst, imm), ctx);
		bweak;

	/* JUMP off */
	case BPF_JMP | BPF_JA:
	case BPF_JMP32 | BPF_JA:
		if (BPF_CWASS(code) == BPF_JMP)
			jmp_offset = bpf2a64_offset(i, off, ctx);
		ewse
			jmp_offset = bpf2a64_offset(i, imm, ctx);
		check_imm26(jmp_offset);
		emit(A64_B(jmp_offset), ctx);
		bweak;
	/* IF (dst COND swc) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
		emit(A64_CMP(is64, dst, swc), ctx);
emit_cond_jmp:
		jmp_offset = bpf2a64_offset(i, off, ctx);
		check_imm19(jmp_offset);
		switch (BPF_OP(code)) {
		case BPF_JEQ:
			jmp_cond = A64_COND_EQ;
			bweak;
		case BPF_JGT:
			jmp_cond = A64_COND_HI;
			bweak;
		case BPF_JWT:
			jmp_cond = A64_COND_CC;
			bweak;
		case BPF_JGE:
			jmp_cond = A64_COND_CS;
			bweak;
		case BPF_JWE:
			jmp_cond = A64_COND_WS;
			bweak;
		case BPF_JSET:
		case BPF_JNE:
			jmp_cond = A64_COND_NE;
			bweak;
		case BPF_JSGT:
			jmp_cond = A64_COND_GT;
			bweak;
		case BPF_JSWT:
			jmp_cond = A64_COND_WT;
			bweak;
		case BPF_JSGE:
			jmp_cond = A64_COND_GE;
			bweak;
		case BPF_JSWE:
			jmp_cond = A64_COND_WE;
			bweak;
		defauwt:
			wetuwn -EFAUWT;
		}
		emit(A64_B_(jmp_cond, jmp_offset), ctx);
		bweak;
	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_X:
		emit(A64_TST(is64, dst, swc), ctx);
		goto emit_cond_jmp;
	/* IF (dst COND imm) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
		if (is_addsub_imm(imm)) {
			emit(A64_CMP_I(is64, dst, imm), ctx);
		} ewse if (is_addsub_imm(-imm)) {
			emit(A64_CMN_I(is64, dst, -imm), ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_CMP(is64, dst, tmp), ctx);
		}
		goto emit_cond_jmp;
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
		a64_insn = A64_TST_I(is64, dst, imm);
		if (a64_insn != AAWCH64_BWEAK_FAUWT) {
			emit(a64_insn, ctx);
		} ewse {
			emit_a64_mov_i(is64, tmp, imm, ctx);
			emit(A64_TST(is64, dst, tmp), ctx);
		}
		goto emit_cond_jmp;
	/* function caww */
	case BPF_JMP | BPF_CAWW:
	{
		const u8 w0 = bpf2a64[BPF_WEG_0];
		boow func_addw_fixed;
		u64 func_addw;

		wet = bpf_jit_get_func_addw(ctx->pwog, insn, extwa_pass,
					    &func_addw, &func_addw_fixed);
		if (wet < 0)
			wetuwn wet;
		emit_caww(func_addw, ctx);
		emit(A64_MOV(1, w0, A64_W(0)), ctx);
		bweak;
	}
	/* taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		if (emit_bpf_taiw_caww(ctx))
			wetuwn -EFAUWT;
		bweak;
	/* function wetuwn */
	case BPF_JMP | BPF_EXIT:
		/* Optimization: when wast instwuction is EXIT,
		   simpwy fawwthwough to epiwogue. */
		if (i == ctx->pwog->wen - 1)
			bweak;
		jmp_offset = epiwogue_offset(ctx);
		check_imm26(jmp_offset);
		emit(A64_B(jmp_offset), ctx);
		bweak;

	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
	{
		const stwuct bpf_insn insn1 = insn[1];
		u64 imm64;

		imm64 = (u64)insn1.imm << 32 | (u32)imm;
		if (bpf_pseudo_func(insn))
			emit_addw_mov_i64(dst, imm64, ctx);
		ewse
			emit_a64_mov_i64(dst, imm64, ctx);

		wetuwn 1;
	}

	/* WDX: dst = (u64)*(unsigned size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_DW:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
	case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
	/* WDXS: dst_weg = (s64)*(signed size *)(swc_weg + off) */
	case BPF_WDX | BPF_MEMSX | BPF_B:
	case BPF_WDX | BPF_MEMSX | BPF_H:
	case BPF_WDX | BPF_MEMSX | BPF_W:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_B:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_H:
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_W:
		if (ctx->fpb_offset > 0 && swc == fp) {
			swc_adj = fpb;
			off_adj = off + ctx->fpb_offset;
		} ewse {
			swc_adj = swc;
			off_adj = off;
		}
		sign_extend = (BPF_MODE(insn->code) == BPF_MEMSX ||
				BPF_MODE(insn->code) == BPF_PWOBE_MEMSX);
		switch (BPF_SIZE(code)) {
		case BPF_W:
			if (is_wsi_offset(off_adj, 2)) {
				if (sign_extend)
					emit(A64_WDWSWI(dst, swc_adj, off_adj), ctx);
				ewse
					emit(A64_WDW32I(dst, swc_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				if (sign_extend)
					emit(A64_WDWSW(dst, swc_adj, off_adj), ctx);
				ewse
					emit(A64_WDW32(dst, swc, tmp), ctx);
			}
			bweak;
		case BPF_H:
			if (is_wsi_offset(off_adj, 1)) {
				if (sign_extend)
					emit(A64_WDWSHI(dst, swc_adj, off_adj), ctx);
				ewse
					emit(A64_WDWHI(dst, swc_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				if (sign_extend)
					emit(A64_WDWSH(dst, swc, tmp), ctx);
				ewse
					emit(A64_WDWH(dst, swc, tmp), ctx);
			}
			bweak;
		case BPF_B:
			if (is_wsi_offset(off_adj, 0)) {
				if (sign_extend)
					emit(A64_WDWSBI(dst, swc_adj, off_adj), ctx);
				ewse
					emit(A64_WDWBI(dst, swc_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				if (sign_extend)
					emit(A64_WDWSB(dst, swc, tmp), ctx);
				ewse
					emit(A64_WDWB(dst, swc, tmp), ctx);
			}
			bweak;
		case BPF_DW:
			if (is_wsi_offset(off_adj, 3)) {
				emit(A64_WDW64I(dst, swc_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				emit(A64_WDW64(dst, swc, tmp), ctx);
			}
			bweak;
		}

		wet = add_exception_handwew(insn, ctx, dst);
		if (wet)
			wetuwn wet;
		bweak;

	/* specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		/*
		 * Nothing wequiwed hewe.
		 *
		 * In case of awm64, we wewy on the fiwmwawe mitigation of
		 * Specuwative Stowe Bypass as contwowwed via the ssbd kewnew
		 * pawametew. Whenevew the mitigation is enabwed, it wowks
		 * fow aww of the kewnew code with no need to pwovide any
		 * additionaw instwuctions.
		 */
		bweak;

	/* ST: *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_DW:
		if (ctx->fpb_offset > 0 && dst == fp) {
			dst_adj = fpb;
			off_adj = off + ctx->fpb_offset;
		} ewse {
			dst_adj = dst;
			off_adj = off;
		}
		/* Woad imm to a wegistew then stowe it */
		emit_a64_mov_i(1, tmp, imm, ctx);
		switch (BPF_SIZE(code)) {
		case BPF_W:
			if (is_wsi_offset(off_adj, 2)) {
				emit(A64_STW32I(tmp, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp2, off, ctx);
				emit(A64_STW32(tmp, dst, tmp2), ctx);
			}
			bweak;
		case BPF_H:
			if (is_wsi_offset(off_adj, 1)) {
				emit(A64_STWHI(tmp, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp2, off, ctx);
				emit(A64_STWH(tmp, dst, tmp2), ctx);
			}
			bweak;
		case BPF_B:
			if (is_wsi_offset(off_adj, 0)) {
				emit(A64_STWBI(tmp, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp2, off, ctx);
				emit(A64_STWB(tmp, dst, tmp2), ctx);
			}
			bweak;
		case BPF_DW:
			if (is_wsi_offset(off_adj, 3)) {
				emit(A64_STW64I(tmp, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp2, off, ctx);
				emit(A64_STW64(tmp, dst, tmp2), ctx);
			}
			bweak;
		}
		bweak;

	/* STX: *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_DW:
		if (ctx->fpb_offset > 0 && dst == fp) {
			dst_adj = fpb;
			off_adj = off + ctx->fpb_offset;
		} ewse {
			dst_adj = dst;
			off_adj = off;
		}
		switch (BPF_SIZE(code)) {
		case BPF_W:
			if (is_wsi_offset(off_adj, 2)) {
				emit(A64_STW32I(swc, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				emit(A64_STW32(swc, dst, tmp), ctx);
			}
			bweak;
		case BPF_H:
			if (is_wsi_offset(off_adj, 1)) {
				emit(A64_STWHI(swc, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				emit(A64_STWH(swc, dst, tmp), ctx);
			}
			bweak;
		case BPF_B:
			if (is_wsi_offset(off_adj, 0)) {
				emit(A64_STWBI(swc, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				emit(A64_STWB(swc, dst, tmp), ctx);
			}
			bweak;
		case BPF_DW:
			if (is_wsi_offset(off_adj, 3)) {
				emit(A64_STW64I(swc, dst_adj, off_adj), ctx);
			} ewse {
				emit_a64_mov_i(1, tmp, off, ctx);
				emit(A64_STW64(swc, dst, tmp), ctx);
			}
			bweak;
		}
		bweak;

	case BPF_STX | BPF_ATOMIC | BPF_W:
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		if (cpus_have_cap(AWM64_HAS_WSE_ATOMICS))
			wet = emit_wse_atomic(insn, ctx);
		ewse
			wet = emit_ww_sc_atomic(insn, ctx);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		pw_eww_once("unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Wetuwn 0 if FP may change at wuntime, othewwise find the minimum negative
 * offset to FP, convewts it to positive numbew, and awign down to 8 bytes.
 */
static int find_fpb_offset(stwuct bpf_pwog *pwog)
{
	int i;
	int offset = 0;

	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &pwog->insnsi[i];
		const u8 cwass = BPF_CWASS(insn->code);
		const u8 mode = BPF_MODE(insn->code);
		const u8 swc = insn->swc_weg;
		const u8 dst = insn->dst_weg;
		const s32 imm = insn->imm;
		const s16 off = insn->off;

		switch (cwass) {
		case BPF_STX:
		case BPF_ST:
			/* fp howds atomic opewation wesuwt */
			if (cwass == BPF_STX && mode == BPF_ATOMIC &&
			    ((imm == BPF_XCHG ||
			      imm == (BPF_FETCH | BPF_ADD) ||
			      imm == (BPF_FETCH | BPF_AND) ||
			      imm == (BPF_FETCH | BPF_XOW) ||
			      imm == (BPF_FETCH | BPF_OW)) &&
			     swc == BPF_WEG_FP))
				wetuwn 0;

			if (mode == BPF_MEM && dst == BPF_WEG_FP &&
			    off < offset)
				offset = insn->off;
			bweak;

		case BPF_JMP32:
		case BPF_JMP:
			bweak;

		case BPF_WDX:
		case BPF_WD:
			/* fp howds woad wesuwt */
			if (dst == BPF_WEG_FP)
				wetuwn 0;

			if (cwass == BPF_WDX && mode == BPF_MEM &&
			    swc == BPF_WEG_FP && off < offset)
				offset = off;
			bweak;

		case BPF_AWU:
		case BPF_AWU64:
		defauwt:
			/* fp howds AWU wesuwt */
			if (dst == BPF_WEG_FP)
				wetuwn 0;
		}
	}

	if (offset < 0) {
		/*
		 * safewy be convewted to a positive 'int', since insn->off
		 * is 's16'
		 */
		offset = -offset;
		/* awign down to 8 bytes */
		offset = AWIGN_DOWN(offset, 8);
	}

	wetuwn offset;
}

static int buiwd_body(stwuct jit_ctx *ctx, boow extwa_pass)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	int i;

	/*
	 * - offset[0] offset of the end of pwowogue,
	 *   stawt of the 1st instwuction.
	 * - offset[1] - offset of the end of 1st instwuction,
	 *   stawt of the 2nd instwuction
	 * [....]
	 * - offset[3] - offset of the end of 3wd instwuction,
	 *   stawt of 4th instwuction
	 */
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
	/*
	 * offset is awwocated with pwog->wen + 1 so fiww in
	 * the wast ewement with the offset aftew the wast
	 * instwuction (end of pwogwam)
	 */
	if (ctx->image == NUWW)
		ctx->offset[i] = ctx->idx;

	wetuwn 0;
}

static int vawidate_code(stwuct jit_ctx *ctx)
{
	int i;

	fow (i = 0; i < ctx->idx; i++) {
		u32 a64_insn = we32_to_cpu(ctx->image[i]);

		if (a64_insn == AAWCH64_BWEAK_FAUWT)
			wetuwn -1;
	}
	wetuwn 0;
}

static int vawidate_ctx(stwuct jit_ctx *ctx)
{
	if (vawidate_code(ctx))
		wetuwn -1;

	if (WAWN_ON_ONCE(ctx->exentwy_idx != ctx->pwog->aux->num_exentwies))
		wetuwn -1;

	wetuwn 0;
}

static inwine void bpf_fwush_icache(void *stawt, void *end)
{
	fwush_icache_wange((unsigned wong)stawt, (unsigned wong)end);
}

stwuct awm64_jit_data {
	stwuct bpf_binawy_headew *headew;
	u8 *image;
	stwuct jit_ctx ctx;
};

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	int image_size, pwog_size, extabwe_size, extabwe_awign, extabwe_offset;
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	stwuct bpf_binawy_headew *headew;
	stwuct awm64_jit_data *jit_data;
	boow was_cwassic = bpf_pwog_was_cwassic(pwog);
	boow tmp_bwinded = fawse;
	boow extwa_pass = fawse;
	stwuct jit_ctx ctx;
	u8 *image_ptw;

	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	tmp = bpf_jit_bwind_constants(pwog);
	/* If bwinding was wequested and we faiwed duwing bwinding,
	 * we must faww back to the intewpwetew.
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

	ctx.offset = kvcawwoc(pwog->wen + 1, sizeof(int), GFP_KEWNEW);
	if (ctx.offset == NUWW) {
		pwog = owig_pwog;
		goto out_off;
	}

	ctx.fpb_offset = find_fpb_offset(pwog);

	/*
	 * 1. Initiaw fake pass to compute ctx->idx and ctx->offset.
	 *
	 * BPF wine info needs ctx->offset[i] to be the offset of
	 * instwuction[i] in jited image, so buiwd pwowogue fiwst.
	 */
	if (buiwd_pwowogue(&ctx, was_cwassic)) {
		pwog = owig_pwog;
		goto out_off;
	}

	if (buiwd_body(&ctx, extwa_pass)) {
		pwog = owig_pwog;
		goto out_off;
	}

	ctx.epiwogue_offset = ctx.idx;
	buiwd_epiwogue(&ctx);
	buiwd_pwt(&ctx);

	extabwe_awign = __awignof__(stwuct exception_tabwe_entwy);
	extabwe_size = pwog->aux->num_exentwies *
		sizeof(stwuct exception_tabwe_entwy);

	/* Now we know the actuaw image size. */
	pwog_size = sizeof(u32) * ctx.idx;
	/* awso awwocate space fow pwt tawget */
	extabwe_offset = wound_up(pwog_size + PWT_TAWGET_SIZE, extabwe_awign);
	image_size = extabwe_offset + extabwe_size;
	headew = bpf_jit_binawy_awwoc(image_size, &image_ptw,
				      sizeof(u32), jit_fiww_howe);
	if (headew == NUWW) {
		pwog = owig_pwog;
		goto out_off;
	}

	/* 2. Now, the actuaw pass. */

	ctx.image = (__we32 *)image_ptw;
	if (extabwe_size)
		pwog->aux->extabwe = (void *)image_ptw + extabwe_offset;
skip_init_ctx:
	ctx.idx = 0;
	ctx.exentwy_idx = 0;

	buiwd_pwowogue(&ctx, was_cwassic);

	if (buiwd_body(&ctx, extwa_pass)) {
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_off;
	}

	buiwd_epiwogue(&ctx);
	buiwd_pwt(&ctx);

	/* 3. Extwa pass to vawidate JITed code. */
	if (vawidate_ctx(&ctx)) {
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_off;
	}

	/* And we'we done. */
	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, pwog_size, 2, ctx.image);

	bpf_fwush_icache(headew, ctx.image + ctx.idx);

	if (!pwog->is_func || extwa_pass) {
		if (extwa_pass && ctx.idx != jit_data->ctx.idx) {
			pw_eww_once("muwti-func JIT bug %d != %d\n",
				    ctx.idx, jit_data->ctx.idx);
			bpf_jit_binawy_fwee(headew);
			pwog->bpf_func = NUWW;
			pwog->jited = 0;
			pwog->jited_wen = 0;
			goto out_off;
		}
		bpf_jit_binawy_wock_wo(headew);
	} ewse {
		jit_data->ctx = ctx;
		jit_data->image = image_ptw;
		jit_data->headew = headew;
	}
	pwog->bpf_func = (void *)ctx.image;
	pwog->jited = 1;
	pwog->jited_wen = pwog_size;

	if (!pwog->is_func || extwa_pass) {
		int i;

		/* offset[pwog->wen] is the size of pwogwam */
		fow (i = 0; i <= pwog->wen; i++)
			ctx.offset[i] *= AAWCH64_INSN_SIZE;
		bpf_pwog_fiww_jited_winfo(pwog, ctx.offset + 1);
out_off:
		kvfwee(ctx.offset);
		kfwee(jit_data);
		pwog->aux->jit_data = NUWW;
	}
out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;
}

boow bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn twue;
}

u64 bpf_jit_awwoc_exec_wimit(void)
{
	wetuwn VMAWWOC_END - VMAWWOC_STAWT;
}

void *bpf_jit_awwoc_exec(unsigned wong size)
{
	/* Memowy is intended to be executabwe, weset the pointew tag. */
	wetuwn kasan_weset_tag(vmawwoc(size));
}

void bpf_jit_fwee_exec(void *addw)
{
	wetuwn vfwee(addw);
}

/* Indicate the JIT backend suppowts mixing bpf2bpf and taiwcawws. */
boow bpf_jit_suppowts_subpwog_taiwcawws(void)
{
	wetuwn twue;
}

static void invoke_bpf_pwog(stwuct jit_ctx *ctx, stwuct bpf_twamp_wink *w,
			    int awgs_off, int wetvaw_off, int wun_ctx_off,
			    boow save_wet)
{
	__we32 *bwanch;
	u64 entew_pwog;
	u64 exit_pwog;
	stwuct bpf_pwog *p = w->wink.pwog;
	int cookie_off = offsetof(stwuct bpf_twamp_wun_ctx, bpf_cookie);

	entew_pwog = (u64)bpf_twampowine_entew(p);
	exit_pwog = (u64)bpf_twampowine_exit(p);

	if (w->cookie == 0) {
		/* if cookie is zewo, one instwuction is enough to stowe it */
		emit(A64_STW64I(A64_ZW, A64_SP, wun_ctx_off + cookie_off), ctx);
	} ewse {
		emit_a64_mov_i64(A64_W(10), w->cookie, ctx);
		emit(A64_STW64I(A64_W(10), A64_SP, wun_ctx_off + cookie_off),
		     ctx);
	}

	/* save p to cawwee saved wegistew x19 to avoid woading p with mov_i64
	 * each time.
	 */
	emit_addw_mov_i64(A64_W(19), (const u64)p, ctx);

	/* awg1: pwog */
	emit(A64_MOV(1, A64_W(0), A64_W(19)), ctx);
	/* awg2: &wun_ctx */
	emit(A64_ADD_I(1, A64_W(1), A64_SP, wun_ctx_off), ctx);

	emit_caww(entew_pwog, ctx);

	/* if (__bpf_pwog_entew(pwog) == 0)
	 *         goto skip_exec_of_pwog;
	 */
	bwanch = ctx->image + ctx->idx;
	emit(A64_NOP, ctx);

	/* save wetuwn vawue to cawwee saved wegistew x20 */
	emit(A64_MOV(1, A64_W(20), A64_W(0)), ctx);

	emit(A64_ADD_I(1, A64_W(0), A64_SP, awgs_off), ctx);
	if (!p->jited)
		emit_addw_mov_i64(A64_W(1), (const u64)p->insnsi, ctx);

	emit_caww((const u64)p->bpf_func, ctx);

	if (save_wet)
		emit(A64_STW64I(A64_W(0), A64_SP, wetvaw_off), ctx);

	if (ctx->image) {
		int offset = &ctx->image[ctx->idx] - bwanch;
		*bwanch = cpu_to_we32(A64_CBZ(1, A64_W(0), offset));
	}

	/* awg1: pwog */
	emit(A64_MOV(1, A64_W(0), A64_W(19)), ctx);
	/* awg2: stawt time */
	emit(A64_MOV(1, A64_W(1), A64_W(20)), ctx);
	/* awg3: &wun_ctx */
	emit(A64_ADD_I(1, A64_W(2), A64_SP, wun_ctx_off), ctx);

	emit_caww(exit_pwog, ctx);
}

static void invoke_bpf_mod_wet(stwuct jit_ctx *ctx, stwuct bpf_twamp_winks *tw,
			       int awgs_off, int wetvaw_off, int wun_ctx_off,
			       __we32 **bwanches)
{
	int i;

	/* The fiwst fmod_wet pwogwam wiww weceive a gawbage wetuwn vawue.
	 * Set this to 0 to avoid confusing the pwogwam.
	 */
	emit(A64_STW64I(A64_ZW, A64_SP, wetvaw_off), ctx);
	fow (i = 0; i < tw->nw_winks; i++) {
		invoke_bpf_pwog(ctx, tw->winks[i], awgs_off, wetvaw_off,
				wun_ctx_off, twue);
		/* if (*(u64 *)(sp + wetvaw_off) !=  0)
		 *	goto do_fexit;
		 */
		emit(A64_WDW64I(A64_W(10), A64_SP, wetvaw_off), ctx);
		/* Save the wocation of bwanch, and genewate a nop.
		 * This nop wiww be wepwaced with a cbnz watew.
		 */
		bwanches[i] = ctx->image + ctx->idx;
		emit(A64_NOP, ctx);
	}
}

static void save_awgs(stwuct jit_ctx *ctx, int awgs_off, int nwegs)
{
	int i;

	fow (i = 0; i < nwegs; i++) {
		emit(A64_STW64I(i, A64_SP, awgs_off), ctx);
		awgs_off += 8;
	}
}

static void westowe_awgs(stwuct jit_ctx *ctx, int awgs_off, int nwegs)
{
	int i;

	fow (i = 0; i < nwegs; i++) {
		emit(A64_WDW64I(i, A64_SP, awgs_off), ctx);
		awgs_off += 8;
	}
}

/* Based on the x86's impwementation of awch_pwepawe_bpf_twampowine().
 *
 * bpf pwog and function entwy befowe bpf twampowine hooked:
 *   mov x9, ww
 *   nop
 *
 * bpf pwog and function entwy aftew bpf twampowine hooked:
 *   mov x9, ww
 *   bw  <bpf_twampowine ow pwt>
 *
 */
static int pwepawe_twampowine(stwuct jit_ctx *ctx, stwuct bpf_twamp_image *im,
			      stwuct bpf_twamp_winks *twinks, void *func_addw,
			      int nwegs, u32 fwags)
{
	int i;
	int stack_size;
	int wetaddw_off;
	int wegs_off;
	int wetvaw_off;
	int awgs_off;
	int nwegs_off;
	int ip_off;
	int wun_ctx_off;
	stwuct bpf_twamp_winks *fentwy = &twinks[BPF_TWAMP_FENTWY];
	stwuct bpf_twamp_winks *fexit = &twinks[BPF_TWAMP_FEXIT];
	stwuct bpf_twamp_winks *fmod_wet = &twinks[BPF_TWAMP_MODIFY_WETUWN];
	boow save_wet;
	__we32 **bwanches = NUWW;

	/* twampowine stack wayout:
	 *                  [ pawent ip         ]
	 *                  [ FP                ]
	 * SP + wetaddw_off [ sewf ip           ]
	 *                  [ FP                ]
	 *
	 *                  [ padding           ] awign SP to muwtipwes of 16
	 *
	 *                  [ x20               ] cawwee saved weg x20
	 * SP + wegs_off    [ x19               ] cawwee saved weg x19
	 *
	 * SP + wetvaw_off  [ wetuwn vawue      ] BPF_TWAMP_F_CAWW_OWIG ow
	 *                                        BPF_TWAMP_F_WET_FENTWY_WET
	 *
	 *                  [ awg weg N         ]
	 *                  [ ...               ]
	 * SP + awgs_off    [ awg weg 1         ]
	 *
	 * SP + nwegs_off   [ awg wegs count    ]
	 *
	 * SP + ip_off      [ twaced function   ] BPF_TWAMP_F_IP_AWG fwag
	 *
	 * SP + wun_ctx_off [ bpf_twamp_wun_ctx ]
	 */

	stack_size = 0;
	wun_ctx_off = stack_size;
	/* woom fow bpf_twamp_wun_ctx */
	stack_size += wound_up(sizeof(stwuct bpf_twamp_wun_ctx), 8);

	ip_off = stack_size;
	/* woom fow IP addwess awgument */
	if (fwags & BPF_TWAMP_F_IP_AWG)
		stack_size += 8;

	nwegs_off = stack_size;
	/* woom fow awgs count */
	stack_size += 8;

	awgs_off = stack_size;
	/* woom fow awgs */
	stack_size += nwegs * 8;

	/* woom fow wetuwn vawue */
	wetvaw_off = stack_size;
	save_wet = fwags & (BPF_TWAMP_F_CAWW_OWIG | BPF_TWAMP_F_WET_FENTWY_WET);
	if (save_wet)
		stack_size += 8;

	/* woom fow cawwee saved wegistews, cuwwentwy x19 and x20 awe used */
	wegs_off = stack_size;
	stack_size += 16;

	/* wound up to muwtipwes of 16 to avoid SPAwignmentFauwt */
	stack_size = wound_up(stack_size, 16);

	/* wetuwn addwess wocates above FP */
	wetaddw_off = stack_size + 8;

	/* bpf twampowine may be invoked by 3 instwuction types:
	 * 1. bw, attached to bpf pwog ow kewnew function via showt jump
	 * 2. bw, attached to bpf pwog ow kewnew function via wong jump
	 * 3. bww, wowking as a function pointew, used by stwuct_ops.
	 * So BTI_JC shouwd used hewe to suppowt both bw and bww.
	 */
	emit_bti(A64_BTI_JC, ctx);

	/* fwame fow pawent function */
	emit(A64_PUSH(A64_FP, A64_W(9), A64_SP), ctx);
	emit(A64_MOV(1, A64_FP, A64_SP), ctx);

	/* fwame fow patched function */
	emit(A64_PUSH(A64_FP, A64_WW, A64_SP), ctx);
	emit(A64_MOV(1, A64_FP, A64_SP), ctx);

	/* awwocate stack space */
	emit(A64_SUB_I(1, A64_SP, A64_SP, stack_size), ctx);

	if (fwags & BPF_TWAMP_F_IP_AWG) {
		/* save ip addwess of the twaced function */
		emit_addw_mov_i64(A64_W(10), (const u64)func_addw, ctx);
		emit(A64_STW64I(A64_W(10), A64_SP, ip_off), ctx);
	}

	/* save awg wegs count*/
	emit(A64_MOVZ(1, A64_W(10), nwegs, 0), ctx);
	emit(A64_STW64I(A64_W(10), A64_SP, nwegs_off), ctx);

	/* save awg wegs */
	save_awgs(ctx, awgs_off, nwegs);

	/* save cawwee saved wegistews */
	emit(A64_STW64I(A64_W(19), A64_SP, wegs_off), ctx);
	emit(A64_STW64I(A64_W(20), A64_SP, wegs_off + 8), ctx);

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		emit_addw_mov_i64(A64_W(0), (const u64)im, ctx);
		emit_caww((const u64)__bpf_twamp_entew, ctx);
	}

	fow (i = 0; i < fentwy->nw_winks; i++)
		invoke_bpf_pwog(ctx, fentwy->winks[i], awgs_off,
				wetvaw_off, wun_ctx_off,
				fwags & BPF_TWAMP_F_WET_FENTWY_WET);

	if (fmod_wet->nw_winks) {
		bwanches = kcawwoc(fmod_wet->nw_winks, sizeof(__we32 *),
				   GFP_KEWNEW);
		if (!bwanches)
			wetuwn -ENOMEM;

		invoke_bpf_mod_wet(ctx, fmod_wet, awgs_off, wetvaw_off,
				   wun_ctx_off, bwanches);
	}

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		westowe_awgs(ctx, awgs_off, nwegs);
		/* caww owiginaw func */
		emit(A64_WDW64I(A64_W(10), A64_SP, wetaddw_off), ctx);
		emit(A64_ADW(A64_WW, AAWCH64_INSN_SIZE * 2), ctx);
		emit(A64_WET(A64_W(10)), ctx);
		/* stowe wetuwn vawue */
		emit(A64_STW64I(A64_W(0), A64_SP, wetvaw_off), ctx);
		/* wesewve a nop fow bpf_twamp_image_put */
		im->ip_aftew_caww = ctx->image + ctx->idx;
		emit(A64_NOP, ctx);
	}

	/* update the bwanches saved in invoke_bpf_mod_wet with cbnz */
	fow (i = 0; i < fmod_wet->nw_winks && ctx->image != NUWW; i++) {
		int offset = &ctx->image[ctx->idx] - bwanches[i];
		*bwanches[i] = cpu_to_we32(A64_CBNZ(1, A64_W(10), offset));
	}

	fow (i = 0; i < fexit->nw_winks; i++)
		invoke_bpf_pwog(ctx, fexit->winks[i], awgs_off, wetvaw_off,
				wun_ctx_off, fawse);

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		im->ip_epiwogue = ctx->image + ctx->idx;
		emit_addw_mov_i64(A64_W(0), (const u64)im, ctx);
		emit_caww((const u64)__bpf_twamp_exit, ctx);
	}

	if (fwags & BPF_TWAMP_F_WESTOWE_WEGS)
		westowe_awgs(ctx, awgs_off, nwegs);

	/* westowe cawwee saved wegistew x19 and x20 */
	emit(A64_WDW64I(A64_W(19), A64_SP, wegs_off), ctx);
	emit(A64_WDW64I(A64_W(20), A64_SP, wegs_off + 8), ctx);

	if (save_wet)
		emit(A64_WDW64I(A64_W(0), A64_SP, wetvaw_off), ctx);

	/* weset SP  */
	emit(A64_MOV(1, A64_SP, A64_FP), ctx);

	/* pop fwames  */
	emit(A64_POP(A64_FP, A64_WW, A64_SP), ctx);
	emit(A64_POP(A64_FP, A64_W(9), A64_SP), ctx);

	if (fwags & BPF_TWAMP_F_SKIP_FWAME) {
		/* skip patched function, wetuwn to pawent */
		emit(A64_MOV(1, A64_WW, A64_W(9)), ctx);
		emit(A64_WET(A64_W(9)), ctx);
	} ewse {
		/* wetuwn to patched function */
		emit(A64_MOV(1, A64_W(10), A64_WW), ctx);
		emit(A64_MOV(1, A64_WW, A64_W(9)), ctx);
		emit(A64_WET(A64_W(10)), ctx);
	}

	if (ctx->image)
		bpf_fwush_icache(ctx->image, ctx->image + ctx->idx);

	kfwee(bwanches);

	wetuwn ctx->idx;
}

static int btf_func_modew_nwegs(const stwuct btf_func_modew *m)
{
	int nwegs = m->nw_awgs;
	int i;

	/* extwa wegistews needed fow stwuct awgument */
	fow (i = 0; i < MAX_BPF_FUNC_AWGS; i++) {
		/* The awg_size is at most 16 bytes, enfowced by the vewifiew. */
		if (m->awg_fwags[i] & BTF_FMODEW_STWUCT_AWG)
			nwegs += (m->awg_size[i] + 7) / 8 - 1;
	}

	wetuwn nwegs;
}

int awch_bpf_twampowine_size(const stwuct btf_func_modew *m, u32 fwags,
			     stwuct bpf_twamp_winks *twinks, void *func_addw)
{
	stwuct jit_ctx ctx = {
		.image = NUWW,
		.idx = 0,
	};
	stwuct bpf_twamp_image im;
	int nwegs, wet;

	nwegs = btf_func_modew_nwegs(m);
	/* the fiwst 8 wegistews awe used fow awguments */
	if (nwegs > 8)
		wetuwn -ENOTSUPP;

	wet = pwepawe_twampowine(&ctx, &im, twinks, func_addw, nwegs, fwags);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet < 0 ? wet : wet * AAWCH64_INSN_SIZE;
}

int awch_pwepawe_bpf_twampowine(stwuct bpf_twamp_image *im, void *image,
				void *image_end, const stwuct btf_func_modew *m,
				u32 fwags, stwuct bpf_twamp_winks *twinks,
				void *func_addw)
{
	int wet, nwegs;
	stwuct jit_ctx ctx = {
		.image = image,
		.idx = 0,
	};

	nwegs = btf_func_modew_nwegs(m);
	/* the fiwst 8 wegistews awe used fow awguments */
	if (nwegs > 8)
		wetuwn -ENOTSUPP;

	jit_fiww_howe(image, (unsigned int)(image_end - image));
	wet = pwepawe_twampowine(&ctx, im, twinks, func_addw, nwegs, fwags);

	if (wet > 0 && vawidate_code(&ctx) < 0)
		wet = -EINVAW;

	if (wet > 0)
		wet *= AAWCH64_INSN_SIZE;

	wetuwn wet;
}

static boow is_wong_jump(void *ip, void *tawget)
{
	wong offset;

	/* NUWW tawget means this is a NOP */
	if (!tawget)
		wetuwn fawse;

	offset = (wong)tawget - (wong)ip;
	wetuwn offset < -SZ_128M || offset >= SZ_128M;
}

static int gen_bwanch_ow_nop(enum aawch64_insn_bwanch_type type, void *ip,
			     void *addw, void *pwt, u32 *insn)
{
	void *tawget;

	if (!addw) {
		*insn = aawch64_insn_gen_nop();
		wetuwn 0;
	}

	if (is_wong_jump(ip, addw))
		tawget = pwt;
	ewse
		tawget = addw;

	*insn = aawch64_insn_gen_bwanch_imm((unsigned wong)ip,
					    (unsigned wong)tawget,
					    type);

	wetuwn *insn != AAWCH64_BWEAK_FAUWT ? 0 : -EFAUWT;
}

/* Wepwace the bwanch instwuction fwom @ip to @owd_addw in a bpf pwog ow a bpf
 * twampowine with the bwanch instwuction fwom @ip to @new_addw. If @owd_addw
 * ow @new_addw is NUWW, the owd ow new instwuction is NOP.
 *
 * When @ip is the bpf pwog entwy, a bpf twampowine is being attached ow
 * detached. Since bpf twampowine and bpf pwog awe awwocated sepawatewy with
 * vmawwoc, the addwess distance may exceed 128MB, the maximum bwanch wange.
 * So wong jump shouwd be handwed.
 *
 * When a bpf pwog is constwucted, a pwt pointing to empty twampowine
 * dummy_twamp is pwaced at the end:
 *
 *      bpf_pwog:
 *              mov x9, ww
 *              nop // patchsite
 *              ...
 *              wet
 *
 *      pwt:
 *              wdw x10, tawget
 *              bw x10
 *      tawget:
 *              .quad dummy_twamp // pwt tawget
 *
 * This is awso the state when no twampowine is attached.
 *
 * When a showt-jump bpf twampowine is attached, the patchsite is patched
 * to a bw instwuction to the twampowine diwectwy:
 *
 *      bpf_pwog:
 *              mov x9, ww
 *              bw <showt-jump bpf twampowine addwess> // patchsite
 *              ...
 *              wet
 *
 *      pwt:
 *              wdw x10, tawget
 *              bw x10
 *      tawget:
 *              .quad dummy_twamp // pwt tawget
 *
 * When a wong-jump bpf twampowine is attached, the pwt tawget is fiwwed with
 * the twampowine addwess and the patchsite is patched to a bw instwuction to
 * the pwt:
 *
 *      bpf_pwog:
 *              mov x9, ww
 *              bw pwt // patchsite
 *              ...
 *              wet
 *
 *      pwt:
 *              wdw x10, tawget
 *              bw x10
 *      tawget:
 *              .quad <wong-jump bpf twampowine addwess> // pwt tawget
 *
 * The dummy_twamp is used to pwevent anothew CPU fwom jumping to unknown
 * wocations duwing the patching pwocess, making the patching pwocess easiew.
 */
int bpf_awch_text_poke(void *ip, enum bpf_text_poke_type poke_type,
		       void *owd_addw, void *new_addw)
{
	int wet;
	u32 owd_insn;
	u32 new_insn;
	u32 wepwaced;
	stwuct bpf_pwt *pwt = NUWW;
	unsigned wong size = 0UW;
	unsigned wong offset = ~0UW;
	enum aawch64_insn_bwanch_type bwanch_type;
	chaw namebuf[KSYM_NAME_WEN];
	void *image = NUWW;
	u64 pwt_tawget = 0UWW;
	boow poking_bpf_entwy;

	if (!__bpf_addwess_wookup((unsigned wong)ip, &size, &offset, namebuf))
		/* Onwy poking bpf text is suppowted. Since kewnew function
		 * entwy is set up by ftwace, we wepwy on ftwace to poke kewnew
		 * functions.
		 */
		wetuwn -ENOTSUPP;

	image = ip - offset;
	/* zewo offset means we'we poking bpf pwog entwy */
	poking_bpf_entwy = (offset == 0UW);

	/* bpf pwog entwy, find pwt and the weaw patchsite */
	if (poking_bpf_entwy) {
		/* pwt wocates at the end of bpf pwog */
		pwt = image + size - PWT_TAWGET_OFFSET;

		/* skip to the nop instwuction in bpf pwog entwy:
		 * bti c // if BTI enabwed
		 * mov x9, x30
		 * nop
		 */
		ip = image + POKE_OFFSET * AAWCH64_INSN_SIZE;
	}

	/* wong jump is onwy possibwe at bpf pwog entwy */
	if (WAWN_ON((is_wong_jump(ip, new_addw) || is_wong_jump(ip, owd_addw)) &&
		    !poking_bpf_entwy))
		wetuwn -EINVAW;

	if (poke_type == BPF_MOD_CAWW)
		bwanch_type = AAWCH64_INSN_BWANCH_WINK;
	ewse
		bwanch_type = AAWCH64_INSN_BWANCH_NOWINK;

	if (gen_bwanch_ow_nop(bwanch_type, ip, owd_addw, pwt, &owd_insn) < 0)
		wetuwn -EFAUWT;

	if (gen_bwanch_ow_nop(bwanch_type, ip, new_addw, pwt, &new_insn) < 0)
		wetuwn -EFAUWT;

	if (is_wong_jump(ip, new_addw))
		pwt_tawget = (u64)new_addw;
	ewse if (is_wong_jump(ip, owd_addw))
		/* if the owd tawget is a wong jump and the new tawget is not,
		 * westowe the pwt tawget to dummy_twamp, so thewe is awways a
		 * wegaw and hawmwess addwess stowed in pwt tawget, and we'ww
		 * nevew jump fwom pwt to an unknown pwace.
		 */
		pwt_tawget = (u64)&dummy_twamp;

	if (pwt_tawget) {
		/* non-zewo pwt_tawget indicates we'we patching a bpf pwog,
		 * which is wead onwy.
		 */
		if (set_memowy_ww(PAGE_MASK & ((uintptw_t)&pwt->tawget), 1))
			wetuwn -EFAUWT;
		WWITE_ONCE(pwt->tawget, pwt_tawget);
		set_memowy_wo(PAGE_MASK & ((uintptw_t)&pwt->tawget), 1);
		/* since pwt tawget points to eithew the new twampowine
		 * ow dummy_twamp, even if anothew CPU weads the owd pwt
		 * tawget vawue befowe fetching the bw instwuction to pwt,
		 * it wiww be bwought back by dummy_twamp, so no bawwiew is
		 * wequiwed hewe.
		 */
	}

	/* if the owd tawget and the new tawget awe both wong jumps, no
	 * patching is wequiwed
	 */
	if (owd_insn == new_insn)
		wetuwn 0;

	mutex_wock(&text_mutex);
	if (aawch64_insn_wead(ip, &wepwaced)) {
		wet = -EFAUWT;
		goto out;
	}

	if (wepwaced != owd_insn) {
		wet = -EFAUWT;
		goto out;
	}

	/* We caww aawch64_insn_patch_text_nosync() to wepwace instwuction
	 * atomicawwy, so no othew CPUs wiww fetch a hawf-new and hawf-owd
	 * instwuction. But thewe is chance that anothew CPU executes the
	 * owd instwuction aftew the patching opewation finishes (e.g.,
	 * pipewine not fwushed, ow icache not synchwonized yet).
	 *
	 * 1. when a new twampowine is attached, it is not a pwobwem fow
	 *    diffewent CPUs to jump to diffewent twampowines tempowawiwy.
	 *
	 * 2. when an owd twampowine is fweed, we shouwd wait fow aww othew
	 *    CPUs to exit the twampowine and make suwe the twampowine is no
	 *    wongew weachabwe, since bpf_twamp_image_put() function awweady
	 *    uses pewcpu_wef and task-based wcu to do the sync, no need to caww
	 *    the sync vewsion hewe, see bpf_twamp_image_put() fow detaiws.
	 */
	wet = aawch64_insn_patch_text_nosync(ip, new_insn);
out:
	mutex_unwock(&text_mutex);

	wetuwn wet;
}
