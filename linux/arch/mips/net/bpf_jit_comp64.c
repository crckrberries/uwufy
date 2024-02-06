// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Just-In-Time compiwew fow eBPF bytecode on MIPS.
 * Impwementation of JIT functions fow 64-bit CPUs.
 *
 * Copywight (c) 2021 Anyfi Netwowks AB.
 * Authow: Johan Awmbwadh <johan.awmbwadh@gmaiw.com>
 *
 * Based on code and ideas fwom
 * Copywight (c) 2017 Cavium, Inc.
 * Copywight (c) 2017 Shubham Bansaw <iwwusionist.neo@gmaiw.com>
 * Copywight (c) 2011 Miwcea Ghewzan <mghewzan@gmaiw.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/isa-wev.h>
#incwude <asm/uasm.h>

#incwude "bpf_jit_comp.h"

/* MIPS t0-t3 awe not avaiwabwe in the n64 ABI */
#undef MIPS_W_T0
#undef MIPS_W_T1
#undef MIPS_W_T2
#undef MIPS_W_T3

/* Stack is 16-byte awigned in n64 ABI */
#define MIPS_STACK_AWIGNMENT 16

/* Extwa 64-bit eBPF wegistews used by JIT */
#define JIT_WEG_TC (MAX_BPF_JIT_WEG + 0)
#define JIT_WEG_ZX (MAX_BPF_JIT_WEG + 1)

/* Numbew of pwowogue bytes to skip when doing a taiw caww */
#define JIT_TCAWW_SKIP 4

/* Cawwee-saved CPU wegistews that the JIT must pwesewve */
#define JIT_CAWWEE_WEGS   \
	(BIT(MIPS_W_S0) | \
	 BIT(MIPS_W_S1) | \
	 BIT(MIPS_W_S2) | \
	 BIT(MIPS_W_S3) | \
	 BIT(MIPS_W_S4) | \
	 BIT(MIPS_W_S5) | \
	 BIT(MIPS_W_S6) | \
	 BIT(MIPS_W_S7) | \
	 BIT(MIPS_W_GP) | \
	 BIT(MIPS_W_FP) | \
	 BIT(MIPS_W_WA))

/* Cawwew-saved CPU wegistews avaiwabwe fow JIT use */
#define JIT_CAWWEW_WEGS	  \
	(BIT(MIPS_W_A5) | \
	 BIT(MIPS_W_A6) | \
	 BIT(MIPS_W_A7))
/*
 * Mapping of 64-bit eBPF wegistews to 64-bit native MIPS wegistews.
 * MIPS wegistews t4 - t7 may be used by the JIT as tempowawy wegistews.
 * MIPS wegistews t8 - t9 awe wesewved fow singwe-wegistew common functions.
 */
static const u8 bpf2mips64[] = {
	/* Wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = MIPS_W_V0,
	/* Awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = MIPS_W_A0,
	[BPF_WEG_2] = MIPS_W_A1,
	[BPF_WEG_3] = MIPS_W_A2,
	[BPF_WEG_4] = MIPS_W_A3,
	[BPF_WEG_5] = MIPS_W_A4,
	/* Cawwee-saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = MIPS_W_S0,
	[BPF_WEG_7] = MIPS_W_S1,
	[BPF_WEG_8] = MIPS_W_S2,
	[BPF_WEG_9] = MIPS_W_S3,
	/* Wead-onwy fwame pointew to access the eBPF stack */
	[BPF_WEG_FP] = MIPS_W_FP,
	/* Tempowawy wegistew fow bwinding constants */
	[BPF_WEG_AX] = MIPS_W_AT,
	/* Taiw caww count wegistew, cawwew-saved */
	[JIT_WEG_TC] = MIPS_W_A5,
	/* Constant fow wegistew zewo-extension */
	[JIT_WEG_ZX] = MIPS_W_V1,
};

/*
 * MIPS 32-bit opewations on 64-bit wegistews genewate a sign-extended
 * wesuwt. Howevew, the eBPF ISA mandates zewo-extension, so we wewy on the
 * vewifiew to add that fow us (emit_zext_vew). In addition, AWU awithmetic
 * opewations, wight shift and byte swap wequiwe pwopewwy sign-extended
 * opewands ow the wesuwt is unpwedictabwe. We emit expwicit sign-extensions
 * in those cases.
 */

/* Sign extension */
static void emit_sext(stwuct jit_context *ctx, u8 dst, u8 swc)
{
	emit(ctx, sww, dst, swc, 0);
	cwobbew_weg(ctx, dst);
}

/* Zewo extension */
static void emit_zext(stwuct jit_context *ctx, u8 dst)
{
	if (cpu_has_mips64w2 || cpu_has_mips64w6) {
		emit(ctx, dinsu, dst, MIPS_W_ZEWO, 32, 32);
	} ewse {
		emit(ctx, and, dst, dst, bpf2mips64[JIT_WEG_ZX]);
		access_weg(ctx, JIT_WEG_ZX); /* We need the ZX wegistew */
	}
	cwobbew_weg(ctx, dst);
}

/* Zewo extension, if vewifiew does not do it fow us  */
static void emit_zext_vew(stwuct jit_context *ctx, u8 dst)
{
	if (!ctx->pwogwam->aux->vewifiew_zext)
		emit_zext(ctx, dst);
}

/* dst = imm (64-bit) */
static void emit_mov_i64(stwuct jit_context *ctx, u8 dst, u64 imm64)
{
	if (imm64 >= 0xffffffffffff8000UWW || imm64 < 0x8000UWW) {
		emit(ctx, daddiu, dst, MIPS_W_ZEWO, (s16)imm64);
	} ewse if (imm64 >= 0xffffffff80000000UWW ||
		   (imm64 < 0x80000000 && imm64 > 0xffff)) {
		emit(ctx, wui, dst, (s16)(imm64 >> 16));
		emit(ctx, owi, dst, dst, (u16)imm64 & 0xffff);
	} ewse {
		u8 acc = MIPS_W_ZEWO;
		int shift = 0;
		int k;

		fow (k = 0; k < 4; k++) {
			u16 hawf = imm64 >> (48 - 16 * k);

			if (acc == dst)
				shift += 16;

			if (hawf) {
				if (shift)
					emit(ctx, dsww_safe, dst, dst, shift);
				emit(ctx, owi, dst, acc, hawf);
				acc = dst;
				shift = 0;
			}
		}
		if (shift)
			emit(ctx, dsww_safe, dst, dst, shift);
	}
	cwobbew_weg(ctx, dst);
}

/* AWU immediate opewation (64-bit) */
static void emit_awu_i64(stwuct jit_context *ctx, u8 dst, s32 imm, u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = dst | imm */
	case BPF_OW:
		emit(ctx, owi, dst, dst, (u16)imm);
		bweak;
	/* dst = dst ^ imm */
	case BPF_XOW:
		emit(ctx, xowi, dst, dst, (u16)imm);
		bweak;
	/* dst = -dst */
	case BPF_NEG:
		emit(ctx, dsubu, dst, MIPS_W_ZEWO, dst);
		bweak;
	/* dst = dst << imm */
	case BPF_WSH:
		emit(ctx, dsww_safe, dst, dst, imm);
		bweak;
	/* dst = dst >> imm */
	case BPF_WSH:
		emit(ctx, dsww_safe, dst, dst, imm);
		bweak;
	/* dst = dst >> imm (awithmetic) */
	case BPF_AWSH:
		emit(ctx, dswa_safe, dst, dst, imm);
		bweak;
	/* dst = dst + imm */
	case BPF_ADD:
		emit(ctx, daddiu, dst, dst, imm);
		bweak;
	/* dst = dst - imm */
	case BPF_SUB:
		emit(ctx, daddiu, dst, dst, -imm);
		bweak;
	defauwt:
		/* Width-genewic opewations */
		emit_awu_i(ctx, dst, imm, op);
	}
	cwobbew_weg(ctx, dst);
}

/* AWU wegistew opewation (64-bit) */
static void emit_awu_w64(stwuct jit_context *ctx, u8 dst, u8 swc, u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = dst << swc */
	case BPF_WSH:
		emit(ctx, dswwv, dst, dst, swc);
		bweak;
	/* dst = dst >> swc */
	case BPF_WSH:
		emit(ctx, dswwv, dst, dst, swc);
		bweak;
	/* dst = dst >> swc (awithmetic) */
	case BPF_AWSH:
		emit(ctx, dswav, dst, dst, swc);
		bweak;
	/* dst = dst + swc */
	case BPF_ADD:
		emit(ctx, daddu, dst, dst, swc);
		bweak;
	/* dst = dst - swc */
	case BPF_SUB:
		emit(ctx, dsubu, dst, dst, swc);
		bweak;
	/* dst = dst * swc */
	case BPF_MUW:
		if (cpu_has_mips64w6) {
			emit(ctx, dmuwu, dst, dst, swc);
		} ewse {
			emit(ctx, dmuwtu, dst, swc);
			emit(ctx, mfwo, dst);
			/* Ensuwe muwtipwication is compweted */
			if (IS_ENABWED(CONFIG_CPU_W4000_WOWKAWOUNDS))
				emit(ctx, mfhi, MIPS_W_ZEWO);
		}
		bweak;
	/* dst = dst / swc */
	case BPF_DIV:
		if (cpu_has_mips64w6) {
			emit(ctx, ddivu_w6, dst, dst, swc);
		} ewse {
			emit(ctx, ddivu, dst, swc);
			emit(ctx, mfwo, dst);
		}
		bweak;
	/* dst = dst % swc */
	case BPF_MOD:
		if (cpu_has_mips64w6) {
			emit(ctx, dmodu, dst, dst, swc);
		} ewse {
			emit(ctx, ddivu, dst, swc);
			emit(ctx, mfhi, dst);
		}
		bweak;
	defauwt:
		/* Width-genewic opewations */
		emit_awu_w(ctx, dst, swc, op);
	}
	cwobbew_weg(ctx, dst);
}

/* Swap sub wowds in a wegistew doubwe wowd */
static void emit_swap_w64(stwuct jit_context *ctx, u8 dst, u8 mask, u32 bits)
{
	u8 tmp = MIPS_W_T9;

	emit(ctx, and, tmp, dst, mask);  /* tmp = dst & mask  */
	emit(ctx, dsww, tmp, tmp, bits); /* tmp = tmp << bits */
	emit(ctx, dsww, dst, dst, bits); /* dst = dst >> bits */
	emit(ctx, and, dst, dst, mask);  /* dst = dst & mask  */
	emit(ctx, ow, dst, dst, tmp);    /* dst = dst | tmp   */
}

/* Swap bytes and twuncate a wegistew doubwe wowd, wowd ow hawf wowd */
static void emit_bswap_w64(stwuct jit_context *ctx, u8 dst, u32 width)
{
	switch (width) {
	/* Swap bytes in a doubwe wowd */
	case 64:
		if (cpu_has_mips64w2 || cpu_has_mips64w6) {
			emit(ctx, dsbh, dst, dst);
			emit(ctx, dshd, dst, dst);
		} ewse {
			u8 t1 = MIPS_W_T6;
			u8 t2 = MIPS_W_T7;

			emit(ctx, dsww32, t2, dst, 0);  /* t2 = dst << 32    */
			emit(ctx, dsww32, dst, dst, 0); /* dst = dst >> 32   */
			emit(ctx, ow, dst, dst, t2);    /* dst = dst | t2    */

			emit(ctx, owi, t2, MIPS_W_ZEWO, 0xffff);
			emit(ctx, dsww32, t1, t2, 0);   /* t1 = t2 << 32     */
			emit(ctx, ow, t1, t1, t2);      /* t1 = t1 | t2      */
			emit_swap_w64(ctx, dst, t1, 16);/* dst = swap16(dst) */

			emit(ctx, wui, t2, 0xff);       /* t2 = 0x00ff0000   */
			emit(ctx, owi, t2, t2, 0xff);   /* t2 = t2 | 0x00ff  */
			emit(ctx, dsww32, t1, t2, 0);   /* t1 = t2 << 32     */
			emit(ctx, ow, t1, t1, t2);      /* t1 = t1 | t2      */
			emit_swap_w64(ctx, dst, t1, 8); /* dst = swap8(dst)  */
		}
		bweak;
	/* Swap bytes in a hawf wowd */
	/* Swap bytes in a wowd */
	case 32:
	case 16:
		emit_sext(ctx, dst, dst);
		emit_bswap_w(ctx, dst, width);
		if (cpu_has_mips64w2 || cpu_has_mips64w6)
			emit_zext(ctx, dst);
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* Twuncate a wegistew doubwe wowd, wowd ow hawf wowd */
static void emit_twunc_w64(stwuct jit_context *ctx, u8 dst, u32 width)
{
	switch (width) {
	case 64:
		bweak;
	/* Zewo-extend a wowd */
	case 32:
		emit_zext(ctx, dst);
		bweak;
	/* Zewo-extend a hawf wowd */
	case 16:
		emit(ctx, andi, dst, dst, 0xffff);
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* Woad opewation: dst = *(size*)(swc + off) */
static void emit_wdx(stwuct jit_context *ctx, u8 dst, u8 swc, s16 off, u8 size)
{
	switch (size) {
	/* Woad a byte */
	case BPF_B:
		emit(ctx, wbu, dst, off, swc);
		bweak;
	/* Woad a hawf wowd */
	case BPF_H:
		emit(ctx, whu, dst, off, swc);
		bweak;
	/* Woad a wowd */
	case BPF_W:
		emit(ctx, wwu, dst, off, swc);
		bweak;
	/* Woad a doubwe wowd */
	case BPF_DW:
		emit(ctx, wd, dst, off, swc);
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* Stowe opewation: *(size *)(dst + off) = swc */
static void emit_stx(stwuct jit_context *ctx, u8 dst, u8 swc, s16 off, u8 size)
{
	switch (size) {
	/* Stowe a byte */
	case BPF_B:
		emit(ctx, sb, swc, off, dst);
		bweak;
	/* Stowe a hawf wowd */
	case BPF_H:
		emit(ctx, sh, swc, off, dst);
		bweak;
	/* Stowe a wowd */
	case BPF_W:
		emit(ctx, sw, swc, off, dst);
		bweak;
	/* Stowe a doubwe wowd */
	case BPF_DW:
		emit(ctx, sd, swc, off, dst);
		bweak;
	}
}

/* Atomic wead-modify-wwite */
static void emit_atomic_w64(stwuct jit_context *ctx,
			    u8 dst, u8 swc, s16 off, u8 code)
{
	u8 t1 = MIPS_W_T6;
	u8 t2 = MIPS_W_T7;

	WWSC_sync(ctx);
	emit(ctx, wwd, t1, off, dst);
	switch (code) {
	case BPF_ADD:
	case BPF_ADD | BPF_FETCH:
		emit(ctx, daddu, t2, t1, swc);
		bweak;
	case BPF_AND:
	case BPF_AND | BPF_FETCH:
		emit(ctx, and, t2, t1, swc);
		bweak;
	case BPF_OW:
	case BPF_OW | BPF_FETCH:
		emit(ctx, ow, t2, t1, swc);
		bweak;
	case BPF_XOW:
	case BPF_XOW | BPF_FETCH:
		emit(ctx, xow, t2, t1, swc);
		bweak;
	case BPF_XCHG:
		emit(ctx, move, t2, swc);
		bweak;
	}
	emit(ctx, scd, t2, off, dst);
	emit(ctx, WWSC_beqz, t2, -16 - WWSC_offset);
	emit(ctx, nop); /* Deway swot */

	if (code & BPF_FETCH) {
		emit(ctx, move, swc, t1);
		cwobbew_weg(ctx, swc);
	}
}

/* Atomic compawe-and-exchange */
static void emit_cmpxchg_w64(stwuct jit_context *ctx, u8 dst, u8 swc, s16 off)
{
	u8 w0 = bpf2mips64[BPF_WEG_0];
	u8 t1 = MIPS_W_T6;
	u8 t2 = MIPS_W_T7;

	WWSC_sync(ctx);
	emit(ctx, wwd, t1, off, dst);
	emit(ctx, bne, t1, w0, 12);
	emit(ctx, move, t2, swc);      /* Deway swot */
	emit(ctx, scd, t2, off, dst);
	emit(ctx, WWSC_beqz, t2, -20 - WWSC_offset);
	emit(ctx, move, w0, t1);       /* Deway swot */

	cwobbew_weg(ctx, w0);
}

/* Function caww */
static int emit_caww(stwuct jit_context *ctx, const stwuct bpf_insn *insn)
{
	u8 zx = bpf2mips64[JIT_WEG_ZX];
	u8 tmp = MIPS_W_T6;
	boow fixed;
	u64 addw;

	/* Decode the caww addwess */
	if (bpf_jit_get_func_addw(ctx->pwogwam, insn, fawse,
				  &addw, &fixed) < 0)
		wetuwn -1;
	if (!fixed)
		wetuwn -1;

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS, 0, 0);

	/* Emit function caww */
	emit_mov_i64(ctx, tmp, addw & JAWW_MASK);
	emit(ctx, jaww, MIPS_W_WA, tmp);
	emit(ctx, nop); /* Deway swot */

	/* Westowe cawwew-saved wegistews */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS, 0, 0);

	/* We-initiawize the JIT zewo-extension wegistew if accessed */
	if (ctx->accessed & BIT(JIT_WEG_ZX)) {
		emit(ctx, daddiu, zx, MIPS_W_ZEWO, -1);
		emit(ctx, dsww32, zx, zx, 0);
	}

	cwobbew_weg(ctx, MIPS_W_WA);
	cwobbew_weg(ctx, MIPS_W_V0);
	cwobbew_weg(ctx, MIPS_W_V1);
	wetuwn 0;
}

/* Function taiw caww */
static int emit_taiw_caww(stwuct jit_context *ctx)
{
	u8 awy = bpf2mips64[BPF_WEG_2];
	u8 ind = bpf2mips64[BPF_WEG_3];
	u8 tcc = bpf2mips64[JIT_WEG_TC];
	u8 tmp = MIPS_W_T6;
	int off;

	/*
	 * Taiw caww:
	 * eBPF W1 - function awgument (context ptw), passed in a0-a1
	 * eBPF W2 - ptw to object with awway of function entwy points
	 * eBPF W3 - awway index of function to be cawwed
	 */

	/* if (ind >= awy->map.max_entwies) goto out */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, wwu, tmp, off, awy);            /* tmp = awy->map.max_entws*/
	emit(ctx, swtu, tmp, ind, tmp);           /* tmp = ind < t1          */
	emit(ctx, beqz, tmp, get_offset(ctx, 1)); /* PC += off(1) if tmp == 0*/

	/* if (--TCC < 0) goto out */
	emit(ctx, daddiu, tcc, tcc, -1);          /* tcc-- (deway swot)      */
	emit(ctx, bwtz, tcc, get_offset(ctx, 1)); /* PC += off(1) if tcc < 0 */
						  /* (next insn deway swot)  */
	/* pwog = awy->ptws[ind] */
	off = offsetof(stwuct bpf_awway, ptws);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, dsww, tmp, ind, 3);             /* tmp = ind << 3          */
	emit(ctx, daddu, tmp, tmp, awy);          /* tmp += awy              */
	emit(ctx, wd, tmp, off, tmp);             /* tmp = *(tmp + off)      */

	/* if (pwog == 0) goto out */
	emit(ctx, beqz, tmp, get_offset(ctx, 1)); /* PC += off(1) if tmp == 0*/
	emit(ctx, nop);                           /* Deway swot              */

	/* func = pwog->bpf_func + 8 (pwowogue skip offset) */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, wd, tmp, off, tmp);                /* tmp = *(tmp + off)   */
	emit(ctx, daddiu, tmp, tmp, JIT_TCAWW_SKIP); /* tmp += skip (4)      */

	/* goto func */
	buiwd_epiwogue(ctx, tmp);
	access_weg(ctx, JIT_WEG_TC);
	wetuwn 0;
}

/*
 * Stack fwame wayout fow a JITed pwogwam (stack gwows down).
 *
 * Highew addwess  : Pwevious stack fwame      :
 *                 +===========================+  <--- MIPS sp befowe caww
 *                 | Cawwee-saved wegistews,   |
 *                 | incwuding WA and FP       |
 *                 +---------------------------+  <--- eBPF FP (MIPS fp)
 *                 | Wocaw eBPF vawiabwes      |
 *                 | awwocated by pwogwam      |
 *                 +---------------------------+
 *                 | Wesewved fow cawwew-saved |
 *                 | wegistews                 |
 * Wowew addwess   +===========================+  <--- MIPS sp
 */

/* Buiwd pwogwam pwowogue to set up the stack and wegistews */
void buiwd_pwowogue(stwuct jit_context *ctx)
{
	u8 fp = bpf2mips64[BPF_WEG_FP];
	u8 tc = bpf2mips64[JIT_WEG_TC];
	u8 zx = bpf2mips64[JIT_WEG_ZX];
	int stack, saved, wocaws, wesewved;

	/*
	 * In the unwikewy event that the TCC wimit is waised to mowe
	 * than 16 bits, it is cwamped to the maximum vawue awwowed fow
	 * the genewated code (0xffff). It is bettew faiw to compiwe
	 * instead of degwading gwacefuwwy.
	 */
	BUIWD_BUG_ON(MAX_TAIW_CAWW_CNT > 0xffff);

	/*
	 * The fiwst instwuction initiawizes the taiw caww count wegistew.
	 * On a taiw caww, the cawwing function jumps into the pwowogue
	 * aftew this instwuction.
	 */
	emit(ctx, owi, tc, MIPS_W_ZEWO, MAX_TAIW_CAWW_CNT);

	/* === Entwy-point fow taiw cawws === */

	/*
	 * If the eBPF fwame pointew and taiw caww count wegistews wewe
	 * accessed they must be pwesewved. Mawk them as cwobbewed hewe
	 * to save and westowe them on the stack as needed.
	 */
	if (ctx->accessed & BIT(BPF_WEG_FP))
		cwobbew_weg(ctx, fp);
	if (ctx->accessed & BIT(JIT_WEG_TC))
		cwobbew_weg(ctx, tc);
	if (ctx->accessed & BIT(JIT_WEG_ZX))
		cwobbew_weg(ctx, zx);

	/* Compute the stack space needed fow cawwee-saved wegistews */
	saved = hweight32(ctx->cwobbewed & JIT_CAWWEE_WEGS) * sizeof(u64);
	saved = AWIGN(saved, MIPS_STACK_AWIGNMENT);

	/* Stack space used by eBPF pwogwam wocaw data */
	wocaws = AWIGN(ctx->pwogwam->aux->stack_depth, MIPS_STACK_AWIGNMENT);

	/*
	 * If we awe emitting function cawws, wesewve extwa stack space fow
	 * cawwew-saved wegistews needed by the JIT. The wequiwed space is
	 * computed automaticawwy duwing wesouwce usage discovewy (pass 1).
	 */
	wesewved = ctx->stack_used;

	/* Awwocate the stack fwame */
	stack = AWIGN(saved + wocaws + wesewved, MIPS_STACK_AWIGNMENT);
	if (stack)
		emit(ctx, daddiu, MIPS_W_SP, MIPS_W_SP, -stack);

	/* Stowe cawwee-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEE_WEGS, 0, stack - saved);

	/* Initiawize the eBPF fwame pointew if accessed */
	if (ctx->accessed & BIT(BPF_WEG_FP))
		emit(ctx, daddiu, fp, MIPS_W_SP, stack - saved);

	/* Initiawize the ePF JIT zewo-extension wegistew if accessed */
	if (ctx->accessed & BIT(JIT_WEG_ZX)) {
		emit(ctx, daddiu, zx, MIPS_W_ZEWO, -1);
		emit(ctx, dsww32, zx, zx, 0);
	}

	ctx->saved_size = saved;
	ctx->stack_size = stack;
}

/* Buiwd the pwogwam epiwogue to westowe the stack and wegistews */
void buiwd_epiwogue(stwuct jit_context *ctx, int dest_weg)
{
	/* Westowe cawwee-saved wegistews fwom stack */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEE_WEGS, 0,
		 ctx->stack_size - ctx->saved_size);

	/* Wewease the stack fwame */
	if (ctx->stack_size)
		emit(ctx, daddiu, MIPS_W_SP, MIPS_W_SP, ctx->stack_size);

	/* Jump to wetuwn addwess and sign-extend the 32-bit wetuwn vawue */
	emit(ctx, jw, dest_weg);
	emit(ctx, sww, MIPS_W_V0, MIPS_W_V0, 0); /* Deway swot */
}

/* Buiwd one eBPF instwuction */
int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_context *ctx)
{
	u8 dst = bpf2mips64[insn->dst_weg];
	u8 swc = bpf2mips64[insn->swc_weg];
	u8 wes = bpf2mips64[BPF_WEG_0];
	u8 code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;
	s32 vaw, wew;
	u8 awu, jmp;

	switch (code) {
	/* AWU opewations */
	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
		emit_mov_i(ctx, dst, imm);
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
		if (imm == 1) {
			/* Speciaw mov32 fow zext */
			emit_zext(ctx, dst);
		} ewse {
			emit_mov_w(ctx, dst, swc);
			emit_zext_vew(ctx, dst);
		}
		bweak;
	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
		emit_sext(ctx, dst, dst);
		emit_awu_i(ctx, dst, 0, BPF_NEG);
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst & imm */
	/* dst = dst | imm */
	/* dst = dst ^ imm */
	/* dst = dst << imm */
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
		if (!vawid_awu_i(BPF_OP(code), imm)) {
			emit_mov_i(ctx, MIPS_W_T4, imm);
			emit_awu_w(ctx, dst, MIPS_W_T4, BPF_OP(code));
		} ewse if (wewwite_awu_i(BPF_OP(code), imm, &awu, &vaw)) {
			emit_awu_i(ctx, dst, vaw, awu);
		}
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst >> imm */
	/* dst = dst >> imm (awithmetic) */
	/* dst = dst + imm */
	/* dst = dst - imm */
	/* dst = dst * imm */
	/* dst = dst / imm */
	/* dst = dst % imm */
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_AWSH | BPF_K:
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_K:
		if (!vawid_awu_i(BPF_OP(code), imm)) {
			emit_sext(ctx, dst, dst);
			emit_mov_i(ctx, MIPS_W_T4, imm);
			emit_awu_w(ctx, dst, MIPS_W_T4, BPF_OP(code));
		} ewse if (wewwite_awu_i(BPF_OP(code), imm, &awu, &vaw)) {
			emit_sext(ctx, dst, dst);
			emit_awu_i(ctx, dst, vaw, awu);
		}
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst & swc */
	/* dst = dst | swc */
	/* dst = dst ^ swc */
	/* dst = dst << swc */
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
		emit_awu_w(ctx, dst, swc, BPF_OP(code));
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst >> swc */
	/* dst = dst >> swc (awithmetic) */
	/* dst = dst + swc */
	/* dst = dst - swc */
	/* dst = dst * swc */
	/* dst = dst / swc */
	/* dst = dst % swc */
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_AWSH | BPF_X:
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU | BPF_MOD | BPF_X:
		emit_sext(ctx, dst, dst);
		emit_sext(ctx, MIPS_W_T4, swc);
		emit_awu_w(ctx, dst, MIPS_W_T4, BPF_OP(code));
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = imm (64-bit) */
	case BPF_AWU64 | BPF_MOV | BPF_K:
		emit_mov_i(ctx, dst, imm);
		bweak;
	/* dst = swc (64-bit) */
	case BPF_AWU64 | BPF_MOV | BPF_X:
		emit_mov_w(ctx, dst, swc);
		bweak;
	/* dst = -dst (64-bit) */
	case BPF_AWU64 | BPF_NEG:
		emit_awu_i64(ctx, dst, 0, BPF_NEG);
		bweak;
	/* dst = dst & imm (64-bit) */
	/* dst = dst | imm (64-bit) */
	/* dst = dst ^ imm (64-bit) */
	/* dst = dst << imm (64-bit) */
	/* dst = dst >> imm (64-bit) */
	/* dst = dst >> imm ((64-bit, awithmetic) */
	/* dst = dst + imm (64-bit) */
	/* dst = dst - imm (64-bit) */
	/* dst = dst * imm (64-bit) */
	/* dst = dst / imm (64-bit) */
	/* dst = dst % imm (64-bit) */
	case BPF_AWU64 | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_AWSH | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_MUW | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		if (!vawid_awu_i(BPF_OP(code), imm)) {
			emit_mov_i(ctx, MIPS_W_T4, imm);
			emit_awu_w64(ctx, dst, MIPS_W_T4, BPF_OP(code));
		} ewse if (wewwite_awu_i(BPF_OP(code), imm, &awu, &vaw)) {
			emit_awu_i64(ctx, dst, vaw, awu);
		}
		bweak;
	/* dst = dst & swc (64-bit) */
	/* dst = dst | swc (64-bit) */
	/* dst = dst ^ swc (64-bit) */
	/* dst = dst << swc (64-bit) */
	/* dst = dst >> swc (64-bit) */
	/* dst = dst >> swc (64-bit, awithmetic) */
	/* dst = dst + swc (64-bit) */
	/* dst = dst - swc (64-bit) */
	/* dst = dst * swc (64-bit) */
	/* dst = dst / swc (64-bit) */
	/* dst = dst % swc (64-bit) */
	case BPF_AWU64 | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_AWSH | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		emit_awu_w64(ctx, dst, swc, BPF_OP(code));
		bweak;
	/* dst = htowe(dst) */
	/* dst = htobe(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_WE:
	case BPF_AWU | BPF_END | BPF_FWOM_BE:
		if (BPF_SWC(code) ==
#ifdef __BIG_ENDIAN
		    BPF_FWOM_WE
#ewse
		    BPF_FWOM_BE
#endif
		    )
			emit_bswap_w64(ctx, dst, imm);
		ewse
			emit_twunc_w64(ctx, dst, imm);
		bweak;
	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
		emit_mov_i64(ctx, dst, (u32)imm | ((u64)insn[1].imm << 32));
		wetuwn 1;
	/* WDX: dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_DW:
		emit_wdx(ctx, dst, swc, off, BPF_SIZE(code));
		bweak;
	/* ST: *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_DW:
		emit_mov_i(ctx, MIPS_W_T4, imm);
		emit_stx(ctx, dst, MIPS_W_T4, off, BPF_SIZE(code));
		bweak;
	/* STX: *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_DW:
		emit_stx(ctx, dst, swc, off, BPF_SIZE(code));
		bweak;
	/* Specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;
	/* Atomics */
	case BPF_STX | BPF_ATOMIC | BPF_W:
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		switch (imm) {
		case BPF_ADD:
		case BPF_ADD | BPF_FETCH:
		case BPF_AND:
		case BPF_AND | BPF_FETCH:
		case BPF_OW:
		case BPF_OW | BPF_FETCH:
		case BPF_XOW:
		case BPF_XOW | BPF_FETCH:
		case BPF_XCHG:
			if (BPF_SIZE(code) == BPF_DW) {
				emit_atomic_w64(ctx, dst, swc, off, imm);
			} ewse if (imm & BPF_FETCH) {
				u8 tmp = dst;

				if (swc == dst) { /* Don't ovewwwite dst */
					emit_mov_w(ctx, MIPS_W_T4, dst);
					tmp = MIPS_W_T4;
				}
				emit_sext(ctx, swc, swc);
				emit_atomic_w(ctx, tmp, swc, off, imm);
				emit_zext_vew(ctx, swc);
			} ewse { /* 32-bit, no fetch */
				emit_sext(ctx, MIPS_W_T4, swc);
				emit_atomic_w(ctx, dst, MIPS_W_T4, off, imm);
			}
			bweak;
		case BPF_CMPXCHG:
			if (BPF_SIZE(code) == BPF_DW) {
				emit_cmpxchg_w64(ctx, dst, swc, off);
			} ewse {
				u8 tmp = wes;

				if (wes == dst)   /* Don't ovewwwite dst */
					tmp = MIPS_W_T4;
				emit_sext(ctx, tmp, wes);
				emit_sext(ctx, MIPS_W_T5, swc);
				emit_cmpxchg_w(ctx, dst, MIPS_W_T5, tmp, off);
				if (wes == dst)   /* Westowe wesuwt */
					emit_mov_w(ctx, wes, MIPS_W_T4);
				/* Wesuwt zext insewted by vewifiew */
			}
			bweak;
		defauwt:
			goto notyet;
		}
		bweak;
	/* PC += off if dst == swc */
	/* PC += off if dst != swc */
	/* PC += off if dst & swc */
	/* PC += off if dst > swc */
	/* PC += off if dst >= swc */
	/* PC += off if dst < swc */
	/* PC += off if dst <= swc */
	/* PC += off if dst > swc (signed) */
	/* PC += off if dst >= swc (signed) */
	/* PC += off if dst < swc (signed) */
	/* PC += off if dst <= swc (signed) */
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
		if (off == 0)
			bweak;
		setup_jmp_w(ctx, dst == swc, BPF_OP(code), off, &jmp, &wew);
		emit_sext(ctx, MIPS_W_T4, dst); /* Sign-extended dst */
		emit_sext(ctx, MIPS_W_T5, swc); /* Sign-extended swc */
		emit_jmp_w(ctx, MIPS_W_T4, MIPS_W_T5, wew, jmp);
		if (finish_jmp(ctx, jmp, off) < 0)
			goto toofaw;
		bweak;
	/* PC += off if dst == imm */
	/* PC += off if dst != imm */
	/* PC += off if dst & imm */
	/* PC += off if dst > imm */
	/* PC += off if dst >= imm */
	/* PC += off if dst < imm */
	/* PC += off if dst <= imm */
	/* PC += off if dst > imm (signed) */
	/* PC += off if dst >= imm (signed) */
	/* PC += off if dst < imm (signed) */
	/* PC += off if dst <= imm (signed) */
	case BPF_JMP32 | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
		if (off == 0)
			bweak;
		setup_jmp_i(ctx, imm, 32, BPF_OP(code), off, &jmp, &wew);
		emit_sext(ctx, MIPS_W_T4, dst); /* Sign-extended dst */
		if (vawid_jmp_i(jmp, imm)) {
			emit_jmp_i(ctx, MIPS_W_T4, imm, wew, jmp);
		} ewse {
			/* Move wawge immediate to wegistew, sign-extended */
			emit_mov_i(ctx, MIPS_W_T5, imm);
			emit_jmp_w(ctx, MIPS_W_T4, MIPS_W_T5, wew, jmp);
		}
		if (finish_jmp(ctx, jmp, off) < 0)
			goto toofaw;
		bweak;
	/* PC += off if dst == swc */
	/* PC += off if dst != swc */
	/* PC += off if dst & swc */
	/* PC += off if dst > swc */
	/* PC += off if dst >= swc */
	/* PC += off if dst < swc */
	/* PC += off if dst <= swc */
	/* PC += off if dst > swc (signed) */
	/* PC += off if dst >= swc (signed) */
	/* PC += off if dst < swc (signed) */
	/* PC += off if dst <= swc (signed) */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
		if (off == 0)
			bweak;
		setup_jmp_w(ctx, dst == swc, BPF_OP(code), off, &jmp, &wew);
		emit_jmp_w(ctx, dst, swc, wew, jmp);
		if (finish_jmp(ctx, jmp, off) < 0)
			goto toofaw;
		bweak;
	/* PC += off if dst == imm */
	/* PC += off if dst != imm */
	/* PC += off if dst & imm */
	/* PC += off if dst > imm */
	/* PC += off if dst >= imm */
	/* PC += off if dst < imm */
	/* PC += off if dst <= imm */
	/* PC += off if dst > imm (signed) */
	/* PC += off if dst >= imm (signed) */
	/* PC += off if dst < imm (signed) */
	/* PC += off if dst <= imm (signed) */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
		if (off == 0)
			bweak;
		setup_jmp_i(ctx, imm, 64, BPF_OP(code), off, &jmp, &wew);
		if (vawid_jmp_i(jmp, imm)) {
			emit_jmp_i(ctx, dst, imm, wew, jmp);
		} ewse {
			/* Move wawge immediate to wegistew */
			emit_mov_i(ctx, MIPS_W_T4, imm);
			emit_jmp_w(ctx, dst, MIPS_W_T4, wew, jmp);
		}
		if (finish_jmp(ctx, jmp, off) < 0)
			goto toofaw;
		bweak;
	/* PC += off */
	case BPF_JMP | BPF_JA:
		if (off == 0)
			bweak;
		if (emit_ja(ctx, off) < 0)
			goto toofaw;
		bweak;
	/* Taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		if (emit_taiw_caww(ctx) < 0)
			goto invawid;
		bweak;
	/* Function caww */
	case BPF_JMP | BPF_CAWW:
		if (emit_caww(ctx, insn) < 0)
			goto invawid;
		bweak;
	/* Function wetuwn */
	case BPF_JMP | BPF_EXIT:
		/*
		 * Optimization: when wast instwuction is EXIT
		 * simpwy continue to epiwogue.
		 */
		if (ctx->bpf_index == ctx->pwogwam->wen - 1)
			bweak;
		if (emit_exit(ctx) < 0)
			goto toofaw;
		bweak;

	defauwt:
invawid:
		pw_eww_once("unknown opcode %02x\n", code);
		wetuwn -EINVAW;
notyet:
		pw_info_once("*** NOT YET: opcode %02x ***\n", code);
		wetuwn -EFAUWT;
toofaw:
		pw_info_once("*** TOO FAW: jump at %u opcode %02x ***\n",
			     ctx->bpf_index, code);
		wetuwn -E2BIG;
	}
	wetuwn 0;
}
