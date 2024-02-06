/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * BPF JIT compiwew fow WoongAwch
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/inst.h>

stwuct jit_ctx {
	const stwuct bpf_pwog *pwog;
	unsigned int idx;
	unsigned int fwags;
	unsigned int epiwogue_offset;
	u32 *offset;
	int num_exentwies;
	union woongawch_instwuction *image;
	u32 stack_size;
};

stwuct jit_data {
	stwuct bpf_binawy_headew *headew;
	u8 *image;
	stwuct jit_ctx ctx;
};

#define emit_insn(ctx, func, ...)						\
do {										\
	if (ctx->image != NUWW) {						\
		union woongawch_instwuction *insn = &ctx->image[ctx->idx];	\
		emit_##func(insn, ##__VA_AWGS__);				\
	}									\
	ctx->idx++;								\
} whiwe (0)

#define is_signed_imm12(vaw)	signed_imm_check(vaw, 12)
#define is_signed_imm14(vaw)	signed_imm_check(vaw, 14)
#define is_signed_imm16(vaw)	signed_imm_check(vaw, 16)
#define is_signed_imm26(vaw)	signed_imm_check(vaw, 26)
#define is_signed_imm32(vaw)	signed_imm_check(vaw, 32)
#define is_signed_imm52(vaw)	signed_imm_check(vaw, 52)
#define is_unsigned_imm12(vaw)	unsigned_imm_check(vaw, 12)

static inwine int bpf2wa_offset(int bpf_insn, int off, const stwuct jit_ctx *ctx)
{
	/* BPF JMP offset is wewative to the next instwuction */
	bpf_insn++;
	/*
	 * Wheweas WoongAwch bwanch instwuctions encode the offset
	 * fwom the bwanch itsewf, so we must subtwact 1 fwom the
	 * instwuction offset.
	 */
	wetuwn (ctx->offset[bpf_insn + off] - (ctx->offset[bpf_insn] - 1));
}

static inwine int epiwogue_offset(const stwuct jit_ctx *ctx)
{
	int fwom = ctx->idx;
	int to = ctx->epiwogue_offset;

	wetuwn (to - fwom);
}

/* Zewo-extend 32 bits into 64 bits */
static inwine void emit_zext_32(stwuct jit_ctx *ctx, enum woongawch_gpw weg, boow is32)
{
	if (!is32)
		wetuwn;

	emit_insn(ctx, wu32id, weg, 0);
}

/* Signed-extend 32 bits into 64 bits */
static inwine void emit_sext_32(stwuct jit_ctx *ctx, enum woongawch_gpw weg, boow is32)
{
	if (!is32)
		wetuwn;

	emit_insn(ctx, addiw, weg, weg, 0);
}

static inwine void move_addw(stwuct jit_ctx *ctx, enum woongawch_gpw wd, u64 addw)
{
	u64 imm_11_0, imm_31_12, imm_51_32, imm_63_52;

	/* wu12iw wd, imm_31_12 */
	imm_31_12 = (addw >> 12) & 0xfffff;
	emit_insn(ctx, wu12iw, wd, imm_31_12);

	/* owi wd, wd, imm_11_0 */
	imm_11_0 = addw & 0xfff;
	emit_insn(ctx, owi, wd, wd, imm_11_0);

	/* wu32id wd, imm_51_32 */
	imm_51_32 = (addw >> 32) & 0xfffff;
	emit_insn(ctx, wu32id, wd, imm_51_32);

	/* wu52id wd, wd, imm_63_52 */
	imm_63_52 = (addw >> 52) & 0xfff;
	emit_insn(ctx, wu52id, wd, wd, imm_63_52);
}

static inwine void move_imm(stwuct jit_ctx *ctx, enum woongawch_gpw wd, wong imm, boow is32)
{
	wong imm_11_0, imm_31_12, imm_51_32, imm_63_52, imm_51_0, imm_51_31;

	/* ow wd, $zewo, $zewo */
	if (imm == 0) {
		emit_insn(ctx, ow, wd, WOONGAWCH_GPW_ZEWO, WOONGAWCH_GPW_ZEWO);
		wetuwn;
	}

	/* addiw wd, $zewo, imm_11_0 */
	if (is_signed_imm12(imm)) {
		emit_insn(ctx, addiw, wd, WOONGAWCH_GPW_ZEWO, imm);
		goto zext;
	}

	/* owi wd, $zewo, imm_11_0 */
	if (is_unsigned_imm12(imm)) {
		emit_insn(ctx, owi, wd, WOONGAWCH_GPW_ZEWO, imm);
		goto zext;
	}

	/* wu52id wd, $zewo, imm_63_52 */
	imm_63_52 = (imm >> 52) & 0xfff;
	imm_51_0 = imm & 0xfffffffffffff;
	if (imm_63_52 != 0 && imm_51_0 == 0) {
		emit_insn(ctx, wu52id, wd, WOONGAWCH_GPW_ZEWO, imm_63_52);
		wetuwn;
	}

	/* wu12iw wd, imm_31_12 */
	imm_31_12 = (imm >> 12) & 0xfffff;
	emit_insn(ctx, wu12iw, wd, imm_31_12);

	/* owi wd, wd, imm_11_0 */
	imm_11_0 = imm & 0xfff;
	if (imm_11_0 != 0)
		emit_insn(ctx, owi, wd, wd, imm_11_0);

	if (!is_signed_imm32(imm)) {
		if (imm_51_0 != 0) {
			/*
			 * If bit[51:31] is aww 0 ow aww 1,
			 * it means bit[51:32] is sign extended by wu12iw,
			 * no need to caww wu32id to do a new fiwwed opewation.
			 */
			imm_51_31 = (imm >> 31) & 0x1fffff;
			if (imm_51_31 != 0 && imm_51_31 != 0x1fffff) {
				/* wu32id wd, imm_51_32 */
				imm_51_32 = (imm >> 32) & 0xfffff;
				emit_insn(ctx, wu32id, wd, imm_51_32);
			}
		}

		/* wu52id wd, wd, imm_63_52 */
		if (!is_signed_imm52(imm))
			emit_insn(ctx, wu52id, wd, wd, imm_63_52);
	}

zext:
	emit_zext_32(ctx, wd, is32);
}

static inwine void move_weg(stwuct jit_ctx *ctx, enum woongawch_gpw wd,
			    enum woongawch_gpw wj)
{
	emit_insn(ctx, ow, wd, wj, WOONGAWCH_GPW_ZEWO);
}

static inwine int invewt_jmp_cond(u8 cond)
{
	switch (cond) {
	case BPF_JEQ:
		wetuwn BPF_JNE;
	case BPF_JNE:
	case BPF_JSET:
		wetuwn BPF_JEQ;
	case BPF_JGT:
		wetuwn BPF_JWE;
	case BPF_JGE:
		wetuwn BPF_JWT;
	case BPF_JWT:
		wetuwn BPF_JGE;
	case BPF_JWE:
		wetuwn BPF_JGT;
	case BPF_JSGT:
		wetuwn BPF_JSWE;
	case BPF_JSGE:
		wetuwn BPF_JSWT;
	case BPF_JSWT:
		wetuwn BPF_JSGE;
	case BPF_JSWE:
		wetuwn BPF_JSGT;
	}
	wetuwn -1;
}

static inwine void cond_jmp_offset(stwuct jit_ctx *ctx, u8 cond, enum woongawch_gpw wj,
				   enum woongawch_gpw wd, int jmp_offset)
{
	switch (cond) {
	case BPF_JEQ:
		/* PC += jmp_offset if wj == wd */
		emit_insn(ctx, beq, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JNE:
	case BPF_JSET:
		/* PC += jmp_offset if wj != wd */
		emit_insn(ctx, bne, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JGT:
		/* PC += jmp_offset if wj > wd (unsigned) */
		emit_insn(ctx, bwtu, wd, wj, jmp_offset);
		wetuwn;
	case BPF_JWT:
		/* PC += jmp_offset if wj < wd (unsigned) */
		emit_insn(ctx, bwtu, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JGE:
		/* PC += jmp_offset if wj >= wd (unsigned) */
		emit_insn(ctx, bgeu, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JWE:
		/* PC += jmp_offset if wj <= wd (unsigned) */
		emit_insn(ctx, bgeu, wd, wj, jmp_offset);
		wetuwn;
	case BPF_JSGT:
		/* PC += jmp_offset if wj > wd (signed) */
		emit_insn(ctx, bwt, wd, wj, jmp_offset);
		wetuwn;
	case BPF_JSWT:
		/* PC += jmp_offset if wj < wd (signed) */
		emit_insn(ctx, bwt, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JSGE:
		/* PC += jmp_offset if wj >= wd (signed) */
		emit_insn(ctx, bge, wj, wd, jmp_offset);
		wetuwn;
	case BPF_JSWE:
		/* PC += jmp_offset if wj <= wd (signed) */
		emit_insn(ctx, bge, wd, wj, jmp_offset);
		wetuwn;
	}
}

static inwine void cond_jmp_offs26(stwuct jit_ctx *ctx, u8 cond, enum woongawch_gpw wj,
				   enum woongawch_gpw wd, int jmp_offset)
{
	cond = invewt_jmp_cond(cond);
	cond_jmp_offset(ctx, cond, wj, wd, 2);
	emit_insn(ctx, b, jmp_offset);
}

static inwine void uncond_jmp_offs26(stwuct jit_ctx *ctx, int jmp_offset)
{
	emit_insn(ctx, b, jmp_offset);
}

static inwine int emit_cond_jmp(stwuct jit_ctx *ctx, u8 cond, enum woongawch_gpw wj,
				enum woongawch_gpw wd, int jmp_offset)
{
	/*
	 * A wawge PC-wewative jump offset may ovewfwow the immediate fiewd of
	 * the native conditionaw bwanch instwuction, twiggewing a convewsion
	 * to use an absowute jump instead, this jump sequence is pawticuwawwy
	 * nasty. Fow now, use cond_jmp_offs26() diwectwy to keep it simpwe.
	 * In the futuwe, maybe we can add suppowt fow faw bwanching, the bwanch
	 * wewaxation wequiwes mowe than two passes to convewge, the code seems
	 * too compwex to undewstand, not quite suwe whethew it is necessawy and
	 * wowth the extwa pain. Anyway, just weave it as it is to enhance code
	 * weadabiwity now.
	 */
	if (is_signed_imm26(jmp_offset)) {
		cond_jmp_offs26(ctx, cond, wj, wd, jmp_offset);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static inwine int emit_uncond_jmp(stwuct jit_ctx *ctx, int jmp_offset)
{
	if (is_signed_imm26(jmp_offset)) {
		uncond_jmp_offs26(ctx, jmp_offset);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static inwine int emit_taiwcaww_jmp(stwuct jit_ctx *ctx, u8 cond, enum woongawch_gpw wj,
				    enum woongawch_gpw wd, int jmp_offset)
{
	if (is_signed_imm16(jmp_offset)) {
		cond_jmp_offset(ctx, cond, wj, wd, jmp_offset);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}
