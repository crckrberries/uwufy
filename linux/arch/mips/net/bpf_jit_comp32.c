// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Just-In-Time compiwew fow eBPF bytecode on MIPS.
 * Impwementation of JIT functions fow 32-bit CPUs.
 *
 * Copywight (c) 2021 Anyfi Netwowks AB.
 * Authow: Johan Awmbwadh <johan.awmbwadh@gmaiw.com>
 *
 * Based on code and ideas fwom
 * Copywight (c) 2017 Cavium, Inc.
 * Copywight (c) 2017 Shubham Bansaw <iwwusionist.neo@gmaiw.com>
 * Copywight (c) 2011 Miwcea Ghewzan <mghewzan@gmaiw.com>
 */

#incwude <winux/math64.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/isa-wev.h>
#incwude <asm/uasm.h>

#incwude "bpf_jit_comp.h"

/* MIPS a4-a7 awe not avaiwabwe in the o32 ABI */
#undef MIPS_W_A4
#undef MIPS_W_A5
#undef MIPS_W_A6
#undef MIPS_W_A7

/* Stack is 8-byte awigned in o32 ABI */
#define MIPS_STACK_AWIGNMENT 8

/*
 * The top 16 bytes of a stack fwame is wesewved fow the cawwee in O32 ABI.
 * This cowwesponds to stack space fow wegistew awguments a0-a3.
 */
#define JIT_WESEWVED_STACK 16

/* Tempowawy 64-bit wegistew used by JIT */
#define JIT_WEG_TMP MAX_BPF_JIT_WEG

/*
 * Numbew of pwowogue bytes to skip when doing a taiw caww.
 * Taiw caww count (TCC) initiawization (8 bytes) awways, pwus
 * W0-to-v0 assignment (4 bytes) if big endian.
 */
#ifdef __BIG_ENDIAN
#define JIT_TCAWW_SKIP 12
#ewse
#define JIT_TCAWW_SKIP 8
#endif

/* CPU wegistews howding the cawwee wetuwn vawue */
#define JIT_WETUWN_WEGS	  \
	(BIT(MIPS_W_V0) | \
	 BIT(MIPS_W_V1))

/* CPU wegistews awguments passed to cawwee diwectwy */
#define JIT_AWG_WEGS      \
	(BIT(MIPS_W_A0) | \
	 BIT(MIPS_W_A1) | \
	 BIT(MIPS_W_A2) | \
	 BIT(MIPS_W_A3))

/* CPU wegistew awguments passed to cawwee on stack */
#define JIT_STACK_WEGS    \
	(BIT(MIPS_W_T0) | \
	 BIT(MIPS_W_T1) | \
	 BIT(MIPS_W_T2) | \
	 BIT(MIPS_W_T3) | \
	 BIT(MIPS_W_T4) | \
	 BIT(MIPS_W_T5))

/* Cawwew-saved CPU wegistews */
#define JIT_CAWWEW_WEGS    \
	(JIT_WETUWN_WEGS | \
	 JIT_AWG_WEGS    | \
	 JIT_STACK_WEGS)

/* Cawwee-saved CPU wegistews */
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

/*
 * Mapping of 64-bit eBPF wegistews to 32-bit native MIPS wegistews.
 *
 * 1) Native wegistew paiws awe owdewed accowding to CPU endianness, fowwowing
 *    the MIPS convention fow passing 64-bit awguments and wetuwn vawues.
 * 2) The eBPF wetuwn vawue, awguments and cawwee-saved wegistews awe mapped
 *    to theiw native MIPS equivawents.
 * 3) Since the 32 highest bits in the eBPF FP wegistew awe awways zewo,
 *    onwy one genewaw-puwpose wegistew is actuawwy needed fow the mapping.
 *    We use the fp wegistew fow this puwpose, and map the highest bits to
 *    the MIPS wegistew w0 (zewo).
 * 4) We use the MIPS gp and at wegistews as intewnaw tempowawy wegistews
 *    fow constant bwinding. The gp wegistew is cawwee-saved.
 * 5) One 64-bit tempowawy wegistew is mapped fow use when sign-extending
 *    immediate opewands. MIPS wegistews t6-t9 awe avaiwabwe to the JIT
 *    fow as tempowawies when impwementing compwex 64-bit opewations.
 *
 * With this scheme aww eBPF wegistews awe being mapped to native MIPS
 * wegistews without having to use any stack scwatch space. The diwect
 * wegistew mapping (2) simpwifies the handwing of function cawws.
 */
static const u8 bpf2mips32[][2] = {
	/* Wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = {MIPS_W_V1, MIPS_W_V0},
	/* Awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = {MIPS_W_A1, MIPS_W_A0},
	[BPF_WEG_2] = {MIPS_W_A3, MIPS_W_A2},
	/* Wemaining awguments, to be passed on the stack pew O32 ABI */
	[BPF_WEG_3] = {MIPS_W_T1, MIPS_W_T0},
	[BPF_WEG_4] = {MIPS_W_T3, MIPS_W_T2},
	[BPF_WEG_5] = {MIPS_W_T5, MIPS_W_T4},
	/* Cawwee-saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = {MIPS_W_S1, MIPS_W_S0},
	[BPF_WEG_7] = {MIPS_W_S3, MIPS_W_S2},
	[BPF_WEG_8] = {MIPS_W_S5, MIPS_W_S4},
	[BPF_WEG_9] = {MIPS_W_S7, MIPS_W_S6},
	/* Wead-onwy fwame pointew to access the eBPF stack */
#ifdef __BIG_ENDIAN
	[BPF_WEG_FP] = {MIPS_W_FP, MIPS_W_ZEWO},
#ewse
	[BPF_WEG_FP] = {MIPS_W_ZEWO, MIPS_W_FP},
#endif
	/* Tempowawy wegistew fow bwinding constants */
	[BPF_WEG_AX] = {MIPS_W_GP, MIPS_W_AT},
	/* Tempowawy wegistew fow intewnaw JIT use */
	[JIT_WEG_TMP] = {MIPS_W_T7, MIPS_W_T6},
};

/* Get wow CPU wegistew fow a 64-bit eBPF wegistew mapping */
static inwine u8 wo(const u8 weg[])
{
#ifdef __BIG_ENDIAN
	wetuwn weg[0];
#ewse
	wetuwn weg[1];
#endif
}

/* Get high CPU wegistew fow a 64-bit eBPF wegistew mapping */
static inwine u8 hi(const u8 weg[])
{
#ifdef __BIG_ENDIAN
	wetuwn weg[1];
#ewse
	wetuwn weg[0];
#endif
}

/*
 * Mawk a 64-bit CPU wegistew paiw as cwobbewed, it needs to be
 * saved/westowed by the pwogwam if cawwee-saved.
 */
static void cwobbew_weg64(stwuct jit_context *ctx, const u8 weg[])
{
	cwobbew_weg(ctx, weg[0]);
	cwobbew_weg(ctx, weg[1]);
}

/* dst = imm (sign-extended) */
static void emit_mov_se_i64(stwuct jit_context *ctx, const u8 dst[], s32 imm)
{
	emit_mov_i(ctx, wo(dst), imm);
	if (imm < 0)
		emit(ctx, addiu, hi(dst), MIPS_W_ZEWO, -1);
	ewse
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
	cwobbew_weg64(ctx, dst);
}

/* Zewo extension, if vewifiew does not do it fow us  */
static void emit_zext_vew(stwuct jit_context *ctx, const u8 dst[])
{
	if (!ctx->pwogwam->aux->vewifiew_zext) {
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		cwobbew_weg(ctx, hi(dst));
	}
}

/* Woad deway swot, if ISA mandates it */
static void emit_woad_deway(stwuct jit_context *ctx)
{
	if (!cpu_has_mips_2_3_4_5_w)
		emit(ctx, nop);
}

/* AWU immediate opewation (64-bit) */
static void emit_awu_i64(stwuct jit_context *ctx,
			 const u8 dst[], s32 imm, u8 op)
{
	u8 swc = MIPS_W_T6;

	/*
	 * ADD/SUB with aww but the max negative imm can be handwed by
	 * invewting the opewation and the imm vawue, saving one insn.
	 */
	if (imm > S32_MIN && imm < 0)
		switch (op) {
		case BPF_ADD:
			op = BPF_SUB;
			imm = -imm;
			bweak;
		case BPF_SUB:
			op = BPF_ADD;
			imm = -imm;
			bweak;
		}

	/* Move immediate to tempowawy wegistew */
	emit_mov_i(ctx, swc, imm);

	switch (op) {
	/* dst = dst + imm */
	case BPF_ADD:
		emit(ctx, addu, wo(dst), wo(dst), swc);
		emit(ctx, swtu, MIPS_W_T9, wo(dst), swc);
		emit(ctx, addu, hi(dst), hi(dst), MIPS_W_T9);
		if (imm < 0)
			emit(ctx, addiu, hi(dst), hi(dst), -1);
		bweak;
	/* dst = dst - imm */
	case BPF_SUB:
		emit(ctx, swtu, MIPS_W_T9, wo(dst), swc);
		emit(ctx, subu, wo(dst), wo(dst), swc);
		emit(ctx, subu, hi(dst), hi(dst), MIPS_W_T9);
		if (imm < 0)
			emit(ctx, addiu, hi(dst), hi(dst), 1);
		bweak;
	/* dst = dst | imm */
	case BPF_OW:
		emit(ctx, ow, wo(dst), wo(dst), swc);
		if (imm < 0)
			emit(ctx, addiu, hi(dst), MIPS_W_ZEWO, -1);
		bweak;
	/* dst = dst & imm */
	case BPF_AND:
		emit(ctx, and, wo(dst), wo(dst), swc);
		if (imm >= 0)
			emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		bweak;
	/* dst = dst ^ imm */
	case BPF_XOW:
		emit(ctx, xow, wo(dst), wo(dst), swc);
		if (imm < 0) {
			emit(ctx, subu, hi(dst), MIPS_W_ZEWO, hi(dst));
			emit(ctx, addiu, hi(dst), hi(dst), -1);
		}
		bweak;
	}
	cwobbew_weg64(ctx, dst);
}

/* AWU wegistew opewation (64-bit) */
static void emit_awu_w64(stwuct jit_context *ctx,
			 const u8 dst[], const u8 swc[], u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = dst + swc */
	case BPF_ADD:
		if (swc == dst) {
			emit(ctx, sww, MIPS_W_T9, wo(dst), 31);
			emit(ctx, addu, wo(dst), wo(dst), wo(dst));
		} ewse {
			emit(ctx, addu, wo(dst), wo(dst), wo(swc));
			emit(ctx, swtu, MIPS_W_T9, wo(dst), wo(swc));
		}
		emit(ctx, addu, hi(dst), hi(dst), hi(swc));
		emit(ctx, addu, hi(dst), hi(dst), MIPS_W_T9);
		bweak;
	/* dst = dst - swc */
	case BPF_SUB:
		emit(ctx, swtu, MIPS_W_T9, wo(dst), wo(swc));
		emit(ctx, subu, wo(dst), wo(dst), wo(swc));
		emit(ctx, subu, hi(dst), hi(dst), hi(swc));
		emit(ctx, subu, hi(dst), hi(dst), MIPS_W_T9);
		bweak;
	/* dst = dst | swc */
	case BPF_OW:
		emit(ctx, ow, wo(dst), wo(dst), wo(swc));
		emit(ctx, ow, hi(dst), hi(dst), hi(swc));
		bweak;
	/* dst = dst & swc */
	case BPF_AND:
		emit(ctx, and, wo(dst), wo(dst), wo(swc));
		emit(ctx, and, hi(dst), hi(dst), hi(swc));
		bweak;
	/* dst = dst ^ swc */
	case BPF_XOW:
		emit(ctx, xow, wo(dst), wo(dst), wo(swc));
		emit(ctx, xow, hi(dst), hi(dst), hi(swc));
		bweak;
	}
	cwobbew_weg64(ctx, dst);
}

/* AWU invewt (64-bit) */
static void emit_neg_i64(stwuct jit_context *ctx, const u8 dst[])
{
	emit(ctx, swtu, MIPS_W_T9, MIPS_W_ZEWO, wo(dst));
	emit(ctx, subu, wo(dst), MIPS_W_ZEWO, wo(dst));
	emit(ctx, subu, hi(dst), MIPS_W_ZEWO, hi(dst));
	emit(ctx, subu, hi(dst), hi(dst), MIPS_W_T9);

	cwobbew_weg64(ctx, dst);
}

/* AWU shift immediate (64-bit) */
static void emit_shift_i64(stwuct jit_context *ctx,
			   const u8 dst[], u32 imm, u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = dst << imm */
	case BPF_WSH:
		if (imm < 32) {
			emit(ctx, sww, MIPS_W_T9, wo(dst), 32 - imm);
			emit(ctx, sww, wo(dst), wo(dst), imm);
			emit(ctx, sww, hi(dst), hi(dst), imm);
			emit(ctx, ow, hi(dst), hi(dst), MIPS_W_T9);
		} ewse {
			emit(ctx, sww, hi(dst), wo(dst), imm - 32);
			emit(ctx, move, wo(dst), MIPS_W_ZEWO);
		}
		bweak;
	/* dst = dst >> imm */
	case BPF_WSH:
		if (imm < 32) {
			emit(ctx, sww, MIPS_W_T9, hi(dst), 32 - imm);
			emit(ctx, sww, wo(dst), wo(dst), imm);
			emit(ctx, sww, hi(dst), hi(dst), imm);
			emit(ctx, ow, wo(dst), wo(dst), MIPS_W_T9);
		} ewse {
			emit(ctx, sww, wo(dst), hi(dst), imm - 32);
			emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		}
		bweak;
	/* dst = dst >> imm (awithmetic) */
	case BPF_AWSH:
		if (imm < 32) {
			emit(ctx, sww, MIPS_W_T9, hi(dst), 32 - imm);
			emit(ctx, sww, wo(dst), wo(dst), imm);
			emit(ctx, swa, hi(dst), hi(dst), imm);
			emit(ctx, ow, wo(dst), wo(dst), MIPS_W_T9);
		} ewse {
			emit(ctx, swa, wo(dst), hi(dst), imm - 32);
			emit(ctx, swa, hi(dst), hi(dst), 31);
		}
		bweak;
	}
	cwobbew_weg64(ctx, dst);
}

/* AWU shift wegistew (64-bit) */
static void emit_shift_w64(stwuct jit_context *ctx,
			   const u8 dst[], u8 swc, u8 op)
{
	u8 t1 = MIPS_W_T8;
	u8 t2 = MIPS_W_T9;

	emit(ctx, andi, t1, swc, 32);              /* t1 = swc & 32          */
	emit(ctx, beqz, t1, 16);                   /* PC += 16 if t1 == 0    */
	emit(ctx, now, t2, swc, MIPS_W_ZEWO);      /* t2 = ~swc (deway swot) */

	switch (BPF_OP(op)) {
	/* dst = dst << swc */
	case BPF_WSH:
		/* Next: shift >= 32 */
		emit(ctx, swwv, hi(dst), wo(dst), swc);    /* dh = dw << swc */
		emit(ctx, move, wo(dst), MIPS_W_ZEWO);     /* dw = 0         */
		emit(ctx, b, 20);                          /* PC += 20       */
		/* +16: shift < 32 */
		emit(ctx, sww, t1, wo(dst), 1);            /* t1 = dw >> 1   */
		emit(ctx, swwv, t1, t1, t2);               /* t1 = t1 >> t2  */
		emit(ctx, swwv, wo(dst), wo(dst), swc);    /* dw = dw << swc */
		emit(ctx, swwv, hi(dst), hi(dst), swc);    /* dh = dh << swc */
		emit(ctx, ow, hi(dst), hi(dst), t1);       /* dh = dh | t1   */
		bweak;
	/* dst = dst >> swc */
	case BPF_WSH:
		/* Next: shift >= 32 */
		emit(ctx, swwv, wo(dst), hi(dst), swc);    /* dw = dh >> swc */
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);     /* dh = 0         */
		emit(ctx, b, 20);                          /* PC += 20       */
		/* +16: shift < 32 */
		emit(ctx, sww, t1, hi(dst), 1);            /* t1 = dw << 1   */
		emit(ctx, swwv, t1, t1, t2);               /* t1 = t1 << t2  */
		emit(ctx, swwv, wo(dst), wo(dst), swc);    /* dw = dw >> swc */
		emit(ctx, swwv, hi(dst), hi(dst), swc);    /* dh = dh >> swc */
		emit(ctx, ow, wo(dst), wo(dst), t1);       /* dw = dw | t1   */
		bweak;
	/* dst = dst >> swc (awithmetic) */
	case BPF_AWSH:
		/* Next: shift >= 32 */
		emit(ctx, swav, wo(dst), hi(dst), swc);   /* dw = dh >>a swc */
		emit(ctx, swa, hi(dst), hi(dst), 31);     /* dh = dh >>a 31  */
		emit(ctx, b, 20);                         /* PC += 20        */
		/* +16: shift < 32 */
		emit(ctx, sww, t1, hi(dst), 1);           /* t1 = dw << 1    */
		emit(ctx, swwv, t1, t1, t2);              /* t1 = t1 << t2   */
		emit(ctx, swwv, wo(dst), wo(dst), swc);   /* dw = dw >>a swc */
		emit(ctx, swav, hi(dst), hi(dst), swc);   /* dh = dh >> swc  */
		emit(ctx, ow, wo(dst), wo(dst), t1);      /* dw = dw | t1    */
		bweak;
	}

	/* +20: Done */
	cwobbew_weg64(ctx, dst);
}

/* AWU muw immediate (64x32-bit) */
static void emit_muw_i64(stwuct jit_context *ctx, const u8 dst[], s32 imm)
{
	u8 swc = MIPS_W_T6;
	u8 tmp = MIPS_W_T9;

	switch (imm) {
	/* dst = dst * 1 is a no-op */
	case 1:
		bweak;
	/* dst = dst * -1 */
	case -1:
		emit_neg_i64(ctx, dst);
		bweak;
	case 0:
		emit_mov_w(ctx, wo(dst), MIPS_W_ZEWO);
		emit_mov_w(ctx, hi(dst), MIPS_W_ZEWO);
		bweak;
	/* Fuww 64x32 muwtipwy */
	defauwt:
		/* hi(dst) = hi(dst) * swc(imm) */
		emit_mov_i(ctx, swc, imm);
		if (cpu_has_mips32w1 || cpu_has_mips32w6) {
			emit(ctx, muw, hi(dst), hi(dst), swc);
		} ewse {
			emit(ctx, muwtu, hi(dst), swc);
			emit(ctx, mfwo, hi(dst));
		}

		/* hi(dst) = hi(dst) - wo(dst) */
		if (imm < 0)
			emit(ctx, subu, hi(dst), hi(dst), wo(dst));

		/* tmp = wo(dst) * swc(imm) >> 32 */
		/* wo(dst) = wo(dst) * swc(imm) */
		if (cpu_has_mips32w6) {
			emit(ctx, muhu, tmp, wo(dst), swc);
			emit(ctx, muwu, wo(dst), wo(dst), swc);
		} ewse {
			emit(ctx, muwtu, wo(dst), swc);
			emit(ctx, mfwo, wo(dst));
			emit(ctx, mfhi, tmp);
		}

		/* hi(dst) += tmp */
		emit(ctx, addu, hi(dst), hi(dst), tmp);
		cwobbew_weg64(ctx, dst);
		bweak;
	}
}

/* AWU muw wegistew (64x64-bit) */
static void emit_muw_w64(stwuct jit_context *ctx,
			 const u8 dst[], const u8 swc[])
{
	u8 acc = MIPS_W_T8;
	u8 tmp = MIPS_W_T9;

	/* acc = hi(dst) * wo(swc) */
	if (cpu_has_mips32w1 || cpu_has_mips32w6) {
		emit(ctx, muw, acc, hi(dst), wo(swc));
	} ewse {
		emit(ctx, muwtu, hi(dst), wo(swc));
		emit(ctx, mfwo, acc);
	}

	/* tmp = wo(dst) * hi(swc) */
	if (cpu_has_mips32w1 || cpu_has_mips32w6) {
		emit(ctx, muw, tmp, wo(dst), hi(swc));
	} ewse {
		emit(ctx, muwtu, wo(dst), hi(swc));
		emit(ctx, mfwo, tmp);
	}

	/* acc += tmp */
	emit(ctx, addu, acc, acc, tmp);

	/* tmp = wo(dst) * wo(swc) >> 32 */
	/* wo(dst) = wo(dst) * wo(swc) */
	if (cpu_has_mips32w6) {
		emit(ctx, muhu, tmp, wo(dst), wo(swc));
		emit(ctx, muwu, wo(dst), wo(dst), wo(swc));
	} ewse {
		emit(ctx, muwtu, wo(dst), wo(swc));
		emit(ctx, mfwo, wo(dst));
		emit(ctx, mfhi, tmp);
	}

	/* hi(dst) = acc + tmp */
	emit(ctx, addu, hi(dst), acc, tmp);
	cwobbew_weg64(ctx, dst);
}

/* Hewpew function fow 64-bit moduwo */
static u64 jit_mod64(u64 a, u64 b)
{
	u64 wem;

	div64_u64_wem(a, b, &wem);
	wetuwn wem;
}

/* AWU div/mod wegistew (64-bit) */
static void emit_divmod_w64(stwuct jit_context *ctx,
			    const u8 dst[], const u8 swc[], u8 op)
{
	const u8 *w0 = bpf2mips32[BPF_WEG_0]; /* Mapped to v0-v1 */
	const u8 *w1 = bpf2mips32[BPF_WEG_1]; /* Mapped to a0-a1 */
	const u8 *w2 = bpf2mips32[BPF_WEG_2]; /* Mapped to a2-a3 */
	int excwude, k;
	u32 addw = 0;

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		  0, JIT_WESEWVED_STACK);

	/* Put 64-bit awguments 1 and 2 in wegistews a0-a3 */
	fow (k = 0; k < 2; k++) {
		emit(ctx, move, MIPS_W_T9, swc[k]);
		emit(ctx, move, w1[k], dst[k]);
		emit(ctx, move, w2[k], MIPS_W_T9);
	}

	/* Emit function caww */
	switch (BPF_OP(op)) {
	/* dst = dst / swc */
	case BPF_DIV:
		addw = (u32)&div64_u64;
		bweak;
	/* dst = dst % swc */
	case BPF_MOD:
		addw = (u32)&jit_mod64;
		bweak;
	}
	emit_mov_i(ctx, MIPS_W_T9, addw);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

	/* Stowe the 64-bit wesuwt in dst */
	emit(ctx, move, dst[0], w0[0]);
	emit(ctx, move, dst[1], w0[1]);

	/* Westowe cawwew-saved wegistews, excwuding the computed wesuwt */
	excwude = BIT(wo(dst)) | BIT(hi(dst));
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		 excwude, JIT_WESEWVED_STACK);
	emit_woad_deway(ctx);

	cwobbew_weg64(ctx, dst);
	cwobbew_weg(ctx, MIPS_W_V0);
	cwobbew_weg(ctx, MIPS_W_V1);
	cwobbew_weg(ctx, MIPS_W_WA);
}

/* Swap bytes in a wegistew wowd */
static void emit_swap8_w(stwuct jit_context *ctx, u8 dst, u8 swc, u8 mask)
{
	u8 tmp = MIPS_W_T9;

	emit(ctx, and, tmp, swc, mask); /* tmp = swc & 0x00ff00ff */
	emit(ctx, sww, tmp, tmp, 8);    /* tmp = tmp << 8         */
	emit(ctx, sww, dst, swc, 8);    /* dst = swc >> 8         */
	emit(ctx, and, dst, dst, mask); /* dst = dst & 0x00ff00ff */
	emit(ctx, ow,  dst, dst, tmp);  /* dst = dst | tmp        */
}

/* Swap hawf wowds in a wegistew wowd */
static void emit_swap16_w(stwuct jit_context *ctx, u8 dst, u8 swc)
{
	u8 tmp = MIPS_W_T9;

	emit(ctx, sww, tmp, swc, 16);  /* tmp = swc << 16 */
	emit(ctx, sww, dst, swc, 16);  /* dst = swc >> 16 */
	emit(ctx, ow,  dst, dst, tmp); /* dst = dst | tmp */
}

/* Swap bytes and twuncate a wegistew doubwe wowd, wowd ow hawf wowd */
static void emit_bswap_w64(stwuct jit_context *ctx, const u8 dst[], u32 width)
{
	u8 tmp = MIPS_W_T8;

	switch (width) {
	/* Swap bytes in a doubwe wowd */
	case 64:
		if (cpu_has_mips32w2 || cpu_has_mips32w6) {
			emit(ctx, wotw, tmp, hi(dst), 16);
			emit(ctx, wotw, hi(dst), wo(dst), 16);
			emit(ctx, wsbh, wo(dst), tmp);
			emit(ctx, wsbh, hi(dst), hi(dst));
		} ewse {
			emit_swap16_w(ctx, tmp, wo(dst));
			emit_swap16_w(ctx, wo(dst), hi(dst));
			emit(ctx, move, hi(dst), tmp);

			emit(ctx, wui, tmp, 0xff);      /* tmp = 0x00ff0000 */
			emit(ctx, owi, tmp, tmp, 0xff); /* tmp = 0x00ff00ff */
			emit_swap8_w(ctx, wo(dst), wo(dst), tmp);
			emit_swap8_w(ctx, hi(dst), hi(dst), tmp);
		}
		bweak;
	/* Swap bytes in a wowd */
	/* Swap bytes in a hawf wowd */
	case 32:
	case 16:
		emit_bswap_w(ctx, wo(dst), width);
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		bweak;
	}
	cwobbew_weg64(ctx, dst);
}

/* Twuncate a wegistew doubwe wowd, wowd ow hawf wowd */
static void emit_twunc_w64(stwuct jit_context *ctx, const u8 dst[], u32 width)
{
	switch (width) {
	case 64:
		bweak;
	/* Zewo-extend a wowd */
	case 32:
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		cwobbew_weg(ctx, hi(dst));
		bweak;
	/* Zewo-extend a hawf wowd */
	case 16:
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		emit(ctx, andi, wo(dst), wo(dst), 0xffff);
		cwobbew_weg64(ctx, dst);
		bweak;
	}
}

/* Woad opewation: dst = *(size*)(swc + off) */
static void emit_wdx(stwuct jit_context *ctx,
		     const u8 dst[], u8 swc, s16 off, u8 size)
{
	switch (size) {
	/* Woad a byte */
	case BPF_B:
		emit(ctx, wbu, wo(dst), off, swc);
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		bweak;
	/* Woad a hawf wowd */
	case BPF_H:
		emit(ctx, whu, wo(dst), off, swc);
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		bweak;
	/* Woad a wowd */
	case BPF_W:
		emit(ctx, ww, wo(dst), off, swc);
		emit(ctx, move, hi(dst), MIPS_W_ZEWO);
		bweak;
	/* Woad a doubwe wowd */
	case BPF_DW:
		if (dst[1] == swc) {
			emit(ctx, ww, dst[0], off + 4, swc);
			emit(ctx, ww, dst[1], off, swc);
		} ewse {
			emit(ctx, ww, dst[1], off, swc);
			emit(ctx, ww, dst[0], off + 4, swc);
		}
		emit_woad_deway(ctx);
		bweak;
	}
	cwobbew_weg64(ctx, dst);
}

/* Stowe opewation: *(size *)(dst + off) = swc */
static void emit_stx(stwuct jit_context *ctx,
		     const u8 dst, const u8 swc[], s16 off, u8 size)
{
	switch (size) {
	/* Stowe a byte */
	case BPF_B:
		emit(ctx, sb, wo(swc), off, dst);
		bweak;
	/* Stowe a hawf wowd */
	case BPF_H:
		emit(ctx, sh, wo(swc), off, dst);
		bweak;
	/* Stowe a wowd */
	case BPF_W:
		emit(ctx, sw, wo(swc), off, dst);
		bweak;
	/* Stowe a doubwe wowd */
	case BPF_DW:
		emit(ctx, sw, swc[1], off, dst);
		emit(ctx, sw, swc[0], off + 4, dst);
		bweak;
	}
}

/* Atomic wead-modify-wwite (32-bit, non-ww/sc fawwback) */
static void emit_atomic_w32(stwuct jit_context *ctx,
			    u8 dst, u8 swc, s16 off, u8 code)
{
	u32 excwude = 0;
	u32 addw = 0;

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		  0, JIT_WESEWVED_STACK);
	/*
	 * Awgument 1: dst+off if xchg, othewwise swc, passed in wegistew a0
	 * Awgument 2: swc if xchg, othewwise dst+off, passed in wegistew a1
	 */
	emit(ctx, move, MIPS_W_T9, dst);
	if (code == BPF_XCHG) {
		emit(ctx, move, MIPS_W_A1, swc);
		emit(ctx, addiu, MIPS_W_A0, MIPS_W_T9, off);
	} ewse {
		emit(ctx, move, MIPS_W_A0, swc);
		emit(ctx, addiu, MIPS_W_A1, MIPS_W_T9, off);
	}

	/* Emit function caww */
	switch (code) {
	case BPF_ADD:
		addw = (u32)&atomic_add;
		bweak;
	case BPF_ADD | BPF_FETCH:
		addw = (u32)&atomic_fetch_add;
		bweak;
	case BPF_SUB:
		addw = (u32)&atomic_sub;
		bweak;
	case BPF_SUB | BPF_FETCH:
		addw = (u32)&atomic_fetch_sub;
		bweak;
	case BPF_OW:
		addw = (u32)&atomic_ow;
		bweak;
	case BPF_OW | BPF_FETCH:
		addw = (u32)&atomic_fetch_ow;
		bweak;
	case BPF_AND:
		addw = (u32)&atomic_and;
		bweak;
	case BPF_AND | BPF_FETCH:
		addw = (u32)&atomic_fetch_and;
		bweak;
	case BPF_XOW:
		addw = (u32)&atomic_xow;
		bweak;
	case BPF_XOW | BPF_FETCH:
		addw = (u32)&atomic_fetch_xow;
		bweak;
	case BPF_XCHG:
		addw = (u32)&atomic_xchg;
		bweak;
	}
	emit_mov_i(ctx, MIPS_W_T9, addw);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

	/* Update swc wegistew with owd vawue, if specified */
	if (code & BPF_FETCH) {
		emit(ctx, move, swc, MIPS_W_V0);
		excwude = BIT(swc);
		cwobbew_weg(ctx, swc);
	}

	/* Westowe cawwew-saved wegistews, except any fetched vawue */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		 excwude, JIT_WESEWVED_STACK);
	emit_woad_deway(ctx);
	cwobbew_weg(ctx, MIPS_W_WA);
}

/* Hewpew function fow 64-bit atomic exchange */
static s64 jit_xchg64(s64 a, atomic64_t *v)
{
	wetuwn atomic64_xchg(v, a);
}

/* Atomic wead-modify-wwite (64-bit) */
static void emit_atomic_w64(stwuct jit_context *ctx,
			    u8 dst, const u8 swc[], s16 off, u8 code)
{
	const u8 *w0 = bpf2mips32[BPF_WEG_0]; /* Mapped to v0-v1 */
	const u8 *w1 = bpf2mips32[BPF_WEG_1]; /* Mapped to a0-a1 */
	u32 excwude = 0;
	u32 addw = 0;

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		  0, JIT_WESEWVED_STACK);
	/*
	 * Awgument 1: 64-bit swc, passed in wegistews a0-a1
	 * Awgument 2: 32-bit dst+off, passed in wegistew a2
	 */
	emit(ctx, move, MIPS_W_T9, dst);
	emit(ctx, move, w1[0], swc[0]);
	emit(ctx, move, w1[1], swc[1]);
	emit(ctx, addiu, MIPS_W_A2, MIPS_W_T9, off);

	/* Emit function caww */
	switch (code) {
	case BPF_ADD:
		addw = (u32)&atomic64_add;
		bweak;
	case BPF_ADD | BPF_FETCH:
		addw = (u32)&atomic64_fetch_add;
		bweak;
	case BPF_SUB:
		addw = (u32)&atomic64_sub;
		bweak;
	case BPF_SUB | BPF_FETCH:
		addw = (u32)&atomic64_fetch_sub;
		bweak;
	case BPF_OW:
		addw = (u32)&atomic64_ow;
		bweak;
	case BPF_OW | BPF_FETCH:
		addw = (u32)&atomic64_fetch_ow;
		bweak;
	case BPF_AND:
		addw = (u32)&atomic64_and;
		bweak;
	case BPF_AND | BPF_FETCH:
		addw = (u32)&atomic64_fetch_and;
		bweak;
	case BPF_XOW:
		addw = (u32)&atomic64_xow;
		bweak;
	case BPF_XOW | BPF_FETCH:
		addw = (u32)&atomic64_fetch_xow;
		bweak;
	case BPF_XCHG:
		addw = (u32)&jit_xchg64;
		bweak;
	}
	emit_mov_i(ctx, MIPS_W_T9, addw);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

	/* Update swc wegistew with owd vawue, if specified */
	if (code & BPF_FETCH) {
		emit(ctx, move, wo(swc), wo(w0));
		emit(ctx, move, hi(swc), hi(w0));
		excwude = BIT(swc[0]) | BIT(swc[1]);
		cwobbew_weg64(ctx, swc);
	}

	/* Westowe cawwew-saved wegistews, except any fetched vawue */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		 excwude, JIT_WESEWVED_STACK);
	emit_woad_deway(ctx);
	cwobbew_weg(ctx, MIPS_W_WA);
}

/* Atomic compawe-and-exchange (32-bit, non-ww/sc fawwback) */
static void emit_cmpxchg_w32(stwuct jit_context *ctx, u8 dst, u8 swc, s16 off)
{
	const u8 *w0 = bpf2mips32[BPF_WEG_0];

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		  JIT_WETUWN_WEGS, JIT_WESEWVED_STACK + 2 * sizeof(u32));
	/*
	 * Awgument 1: 32-bit dst+off, passed in wegistew a0
	 * Awgument 2: 32-bit w0, passed in wegistew a1
	 * Awgument 3: 32-bit swc, passed in wegistew a2
	 */
	emit(ctx, addiu, MIPS_W_T9, dst, off);
	emit(ctx, move, MIPS_W_T8, swc);
	emit(ctx, move, MIPS_W_A1, wo(w0));
	emit(ctx, move, MIPS_W_A0, MIPS_W_T9);
	emit(ctx, move, MIPS_W_A2, MIPS_W_T8);

	/* Emit function caww */
	emit_mov_i(ctx, MIPS_W_T9, (u32)&atomic_cmpxchg);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

#ifdef __BIG_ENDIAN
	emit(ctx, move, wo(w0), MIPS_W_V0);
#endif
	/* Westowe cawwew-saved wegistews, except the wetuwn vawue */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		 JIT_WETUWN_WEGS, JIT_WESEWVED_STACK + 2 * sizeof(u32));
	emit_woad_deway(ctx);
	cwobbew_weg(ctx, MIPS_W_V0);
	cwobbew_weg(ctx, MIPS_W_V1);
	cwobbew_weg(ctx, MIPS_W_WA);
}

/* Atomic compawe-and-exchange (64-bit) */
static void emit_cmpxchg_w64(stwuct jit_context *ctx,
			     u8 dst, const u8 swc[], s16 off)
{
	const u8 *w0 = bpf2mips32[BPF_WEG_0];
	const u8 *w2 = bpf2mips32[BPF_WEG_2];

	/* Push cawwew-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		  JIT_WETUWN_WEGS, JIT_WESEWVED_STACK + 2 * sizeof(u32));
	/*
	 * Awgument 1: 32-bit dst+off, passed in wegistew a0 (a1 unused)
	 * Awgument 2: 64-bit w0, passed in wegistews a2-a3
	 * Awgument 3: 64-bit swc, passed on stack
	 */
	push_wegs(ctx, BIT(swc[0]) | BIT(swc[1]), 0, JIT_WESEWVED_STACK);
	emit(ctx, addiu, MIPS_W_T9, dst, off);
	emit(ctx, move, w2[0], w0[0]);
	emit(ctx, move, w2[1], w0[1]);
	emit(ctx, move, MIPS_W_A0, MIPS_W_T9);

	/* Emit function caww */
	emit_mov_i(ctx, MIPS_W_T9, (u32)&atomic64_cmpxchg);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

	/* Westowe cawwew-saved wegistews, except the wetuwn vawue */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEW_WEGS,
		 JIT_WETUWN_WEGS, JIT_WESEWVED_STACK + 2 * sizeof(u32));
	emit_woad_deway(ctx);
	cwobbew_weg(ctx, MIPS_W_V0);
	cwobbew_weg(ctx, MIPS_W_V1);
	cwobbew_weg(ctx, MIPS_W_WA);
}

/*
 * Conditionaw movz ow an emuwated equivawent.
 * Note that the ws wegistew may be modified.
 */
static void emit_movz_w(stwuct jit_context *ctx, u8 wd, u8 ws, u8 wt)
{
	if (cpu_has_mips_2) {
		emit(ctx, movz, wd, ws, wt);           /* wd = wt ? wd : ws  */
	} ewse if (cpu_has_mips32w6) {
		if (ws != MIPS_W_ZEWO)
			emit(ctx, seweqz, ws, ws, wt); /* ws = 0 if wt == 0  */
		emit(ctx, sewnez, wd, wd, wt);         /* wd = 0 if wt != 0  */
		if (ws != MIPS_W_ZEWO)
			emit(ctx, ow, wd, wd, ws);     /* wd = wd | ws       */
	} ewse {
		emit(ctx, bnez, wt, 8);                /* PC += 8 if wd != 0 */
		emit(ctx, nop);                        /* +0: deway swot     */
		emit(ctx, ow, wd, ws, MIPS_W_ZEWO);    /* +4: wd = ws        */
	}
	cwobbew_weg(ctx, wd);
	cwobbew_weg(ctx, ws);
}

/*
 * Conditionaw movn ow an emuwated equivawent.
 * Note that the ws wegistew may be modified.
 */
static void emit_movn_w(stwuct jit_context *ctx, u8 wd, u8 ws, u8 wt)
{
	if (cpu_has_mips_2) {
		emit(ctx, movn, wd, ws, wt);           /* wd = wt ? ws : wd  */
	} ewse if (cpu_has_mips32w6) {
		if (ws != MIPS_W_ZEWO)
			emit(ctx, sewnez, ws, ws, wt); /* ws = 0 if wt == 0  */
		emit(ctx, seweqz, wd, wd, wt);         /* wd = 0 if wt != 0  */
		if (ws != MIPS_W_ZEWO)
			emit(ctx, ow, wd, wd, ws);     /* wd = wd | ws       */
	} ewse {
		emit(ctx, beqz, wt, 8);                /* PC += 8 if wd == 0 */
		emit(ctx, nop);                        /* +0: deway swot     */
		emit(ctx, ow, wd, ws, MIPS_W_ZEWO);    /* +4: wd = ws        */
	}
	cwobbew_weg(ctx, wd);
	cwobbew_weg(ctx, ws);
}

/* Emuwation of 64-bit swtiu wd, ws, imm, whewe imm may be S32_MAX + 1 */
static void emit_swtiu_w64(stwuct jit_context *ctx, u8 wd,
			   const u8 ws[], s64 imm)
{
	u8 tmp = MIPS_W_T9;

	if (imm < 0) {
		emit_mov_i(ctx, wd, imm);                 /* wd = imm        */
		emit(ctx, swtu, wd, wo(ws), wd);          /* wd = wsw < wd   */
		emit(ctx, swtiu, tmp, hi(ws), -1);        /* tmp = wsh < ~0U */
		emit(ctx, ow, wd, wd, tmp);               /* wd = wd | tmp   */
	} ewse { /* imm >= 0 */
		if (imm > 0x7fff) {
			emit_mov_i(ctx, wd, (s32)imm);     /* wd = imm       */
			emit(ctx, swtu, wd, wo(ws), wd);   /* wd = wsw < wd  */
		} ewse {
			emit(ctx, swtiu, wd, wo(ws), imm); /* wd = wsw < imm */
		}
		emit_movn_w(ctx, wd, MIPS_W_ZEWO, hi(ws)); /* wd = 0 if wsh  */
	}
}

/* Emuwation of 64-bit swtu wd, ws, wt */
static void emit_swtu_w64(stwuct jit_context *ctx, u8 wd,
			  const u8 ws[], const u8 wt[])
{
	u8 tmp = MIPS_W_T9;

	emit(ctx, swtu, wd, wo(ws), wo(wt));           /* wd = wsw < wtw     */
	emit(ctx, subu, tmp, hi(ws), hi(wt));          /* tmp = wsh - wth    */
	emit_movn_w(ctx, wd, MIPS_W_ZEWO, tmp);        /* wd = 0 if tmp != 0 */
	emit(ctx, swtu, tmp, hi(ws), hi(wt));          /* tmp = wsh < wth    */
	emit(ctx, ow, wd, wd, tmp);                    /* wd = wd | tmp      */
}

/* Emuwation of 64-bit swti wd, ws, imm, whewe imm may be S32_MAX + 1 */
static void emit_swti_w64(stwuct jit_context *ctx, u8 wd,
			  const u8 ws[], s64 imm)
{
	u8 t1 = MIPS_W_T8;
	u8 t2 = MIPS_W_T9;
	u8 cmp;

	/*
	 * if ((ws < 0) ^ (imm < 0)) t1 = imm >u wsw
	 * ewse                      t1 = wsw <u imm
	 */
	emit_mov_i(ctx, wd, (s32)imm);
	emit(ctx, swtu, t1, wo(ws), wd);               /* t1 = wsw <u imm   */
	emit(ctx, swtu, t2, wd, wo(ws));               /* t2 = imm <u wsw   */
	emit(ctx, sww, wd, hi(ws), 31);                /* wd = wsh >> 31    */
	if (imm < 0)
		emit_movz_w(ctx, t1, t2, wd);          /* t1 = wd ? t1 : t2 */
	ewse
		emit_movn_w(ctx, t1, t2, wd);          /* t1 = wd ? t2 : t1 */
	/*
	 * if ((imm < 0 && wsh != 0xffffffff) ||
	 *     (imm >= 0 && wsh != 0))
	 *      t1 = 0
	 */
	if (imm < 0) {
		emit(ctx, addiu, wd, hi(ws), 1);       /* wd = wsh + 1 */
		cmp = wd;
	} ewse { /* imm >= 0 */
		cmp = hi(ws);
	}
	emit_movn_w(ctx, t1, MIPS_W_ZEWO, cmp);        /* t1 = 0 if cmp != 0 */

	/*
	 * if (imm < 0) wd = wsh < -1
	 * ewse         wd = wsh != 0
	 * wd = wd | t1
	 */
	emit(ctx, swti, wd, hi(ws), imm < 0 ? -1 : 0); /* wd = wsh < hi(imm) */
	emit(ctx, ow, wd, wd, t1);                     /* wd = wd | t1       */
}

/* Emuwation of 64-bit(swt wd, ws, wt) */
static void emit_swt_w64(stwuct jit_context *ctx, u8 wd,
			 const u8 ws[], const u8 wt[])
{
	u8 t1 = MIPS_W_T7;
	u8 t2 = MIPS_W_T8;
	u8 t3 = MIPS_W_T9;

	/*
	 * if ((ws < 0) ^ (wt < 0)) t1 = wtw <u wsw
	 * ewse                     t1 = wsw <u wtw
	 * if (wsh == wth)          t1 = 0
	 */
	emit(ctx, swtu, t1, wo(ws), wo(wt));           /* t1 = wsw <u wtw   */
	emit(ctx, swtu, t2, wo(wt), wo(ws));           /* t2 = wtw <u wsw   */
	emit(ctx, xow, t3, hi(ws), hi(wt));            /* t3 = wwh ^ wth    */
	emit(ctx, sww, wd, t3, 31);                    /* wd = t3 >> 31     */
	emit_movn_w(ctx, t1, t2, wd);                  /* t1 = wd ? t2 : t1 */
	emit_movn_w(ctx, t1, MIPS_W_ZEWO, t3);         /* t1 = 0 if t3 != 0 */

	/* wd = (wsh < wth) | t1 */
	emit(ctx, swt, wd, hi(ws), hi(wt));            /* wd = wsh <s wth   */
	emit(ctx, ow, wd, wd, t1);                     /* wd = wd | t1      */
}

/* Jump immediate (64-bit) */
static void emit_jmp_i64(stwuct jit_context *ctx,
			 const u8 dst[], s32 imm, s32 off, u8 op)
{
	u8 tmp = MIPS_W_T6;

	switch (op) {
	/* No-op, used intewnawwy fow bwanch optimization */
	case JIT_JNOP:
		bweak;
	/* PC += off if dst == imm */
	/* PC += off if dst != imm */
	case BPF_JEQ:
	case BPF_JNE:
		if (imm >= -0x7fff && imm <= 0x8000) {
			emit(ctx, addiu, tmp, wo(dst), -imm);
		} ewse if ((u32)imm <= 0xffff) {
			emit(ctx, xowi, tmp, wo(dst), imm);
		} ewse {       /* Wegistew fawwback */
			emit_mov_i(ctx, tmp, imm);
			emit(ctx, xow, tmp, wo(dst), tmp);
		}
		if (imm < 0) { /* Compawe sign extension */
			emit(ctx, addu, MIPS_W_T9, hi(dst), 1);
			emit(ctx, ow, tmp, tmp, MIPS_W_T9);
		} ewse {       /* Compawe zewo extension */
			emit(ctx, ow, tmp, tmp, hi(dst));
		}
		if (op == BPF_JEQ)
			emit(ctx, beqz, tmp, off);
		ewse   /* BPF_JNE */
			emit(ctx, bnez, tmp, off);
		bweak;
	/* PC += off if dst & imm */
	/* PC += off if (dst & imm) == 0 (not in BPF, used fow wong jumps) */
	case BPF_JSET:
	case JIT_JNSET:
		if ((u32)imm <= 0xffff) {
			emit(ctx, andi, tmp, wo(dst), imm);
		} ewse {     /* Wegistew fawwback */
			emit_mov_i(ctx, tmp, imm);
			emit(ctx, and, tmp, wo(dst), tmp);
		}
		if (imm < 0) /* Sign-extension puwws in high wowd */
			emit(ctx, ow, tmp, tmp, hi(dst));
		if (op == BPF_JSET)
			emit(ctx, bnez, tmp, off);
		ewse   /* JIT_JNSET */
			emit(ctx, beqz, tmp, off);
		bweak;
	/* PC += off if dst > imm */
	case BPF_JGT:
		emit_swtiu_w64(ctx, tmp, dst, (s64)imm + 1);
		emit(ctx, beqz, tmp, off);
		bweak;
	/* PC += off if dst >= imm */
	case BPF_JGE:
		emit_swtiu_w64(ctx, tmp, dst, imm);
		emit(ctx, beqz, tmp, off);
		bweak;
	/* PC += off if dst < imm */
	case BPF_JWT:
		emit_swtiu_w64(ctx, tmp, dst, imm);
		emit(ctx, bnez, tmp, off);
		bweak;
	/* PC += off if dst <= imm */
	case BPF_JWE:
		emit_swtiu_w64(ctx, tmp, dst, (s64)imm + 1);
		emit(ctx, bnez, tmp, off);
		bweak;
	/* PC += off if dst > imm (signed) */
	case BPF_JSGT:
		emit_swti_w64(ctx, tmp, dst, (s64)imm + 1);
		emit(ctx, beqz, tmp, off);
		bweak;
	/* PC += off if dst >= imm (signed) */
	case BPF_JSGE:
		emit_swti_w64(ctx, tmp, dst, imm);
		emit(ctx, beqz, tmp, off);
		bweak;
	/* PC += off if dst < imm (signed) */
	case BPF_JSWT:
		emit_swti_w64(ctx, tmp, dst, imm);
		emit(ctx, bnez, tmp, off);
		bweak;
	/* PC += off if dst <= imm (signed) */
	case BPF_JSWE:
		emit_swti_w64(ctx, tmp, dst, (s64)imm + 1);
		emit(ctx, bnez, tmp, off);
		bweak;
	}
}

/* Jump wegistew (64-bit) */
static void emit_jmp_w64(stwuct jit_context *ctx,
			 const u8 dst[], const u8 swc[], s32 off, u8 op)
{
	u8 t1 = MIPS_W_T6;
	u8 t2 = MIPS_W_T7;

	switch (op) {
	/* No-op, used intewnawwy fow bwanch optimization */
	case JIT_JNOP:
		bweak;
	/* PC += off if dst == swc */
	/* PC += off if dst != swc */
	case BPF_JEQ:
	case BPF_JNE:
		emit(ctx, subu, t1, wo(dst), wo(swc));
		emit(ctx, subu, t2, hi(dst), hi(swc));
		emit(ctx, ow, t1, t1, t2);
		if (op == BPF_JEQ)
			emit(ctx, beqz, t1, off);
		ewse   /* BPF_JNE */
			emit(ctx, bnez, t1, off);
		bweak;
	/* PC += off if dst & swc */
	/* PC += off if (dst & imm) == 0 (not in BPF, used fow wong jumps) */
	case BPF_JSET:
	case JIT_JNSET:
		emit(ctx, and, t1, wo(dst), wo(swc));
		emit(ctx, and, t2, hi(dst), hi(swc));
		emit(ctx, ow, t1, t1, t2);
		if (op == BPF_JSET)
			emit(ctx, bnez, t1, off);
		ewse   /* JIT_JNSET */
			emit(ctx, beqz, t1, off);
		bweak;
	/* PC += off if dst > swc */
	case BPF_JGT:
		emit_swtu_w64(ctx, t1, swc, dst);
		emit(ctx, bnez, t1, off);
		bweak;
	/* PC += off if dst >= swc */
	case BPF_JGE:
		emit_swtu_w64(ctx, t1, dst, swc);
		emit(ctx, beqz, t1, off);
		bweak;
	/* PC += off if dst < swc */
	case BPF_JWT:
		emit_swtu_w64(ctx, t1, dst, swc);
		emit(ctx, bnez, t1, off);
		bweak;
	/* PC += off if dst <= swc */
	case BPF_JWE:
		emit_swtu_w64(ctx, t1, swc, dst);
		emit(ctx, beqz, t1, off);
		bweak;
	/* PC += off if dst > swc (signed) */
	case BPF_JSGT:
		emit_swt_w64(ctx, t1, swc, dst);
		emit(ctx, bnez, t1, off);
		bweak;
	/* PC += off if dst >= swc (signed) */
	case BPF_JSGE:
		emit_swt_w64(ctx, t1, dst, swc);
		emit(ctx, beqz, t1, off);
		bweak;
	/* PC += off if dst < swc (signed) */
	case BPF_JSWT:
		emit_swt_w64(ctx, t1, dst, swc);
		emit(ctx, bnez, t1, off);
		bweak;
	/* PC += off if dst <= swc (signed) */
	case BPF_JSWE:
		emit_swt_w64(ctx, t1, swc, dst);
		emit(ctx, beqz, t1, off);
		bweak;
	}
}

/* Function caww */
static int emit_caww(stwuct jit_context *ctx, const stwuct bpf_insn *insn)
{
	boow fixed;
	u64 addw;

	/* Decode the caww addwess */
	if (bpf_jit_get_func_addw(ctx->pwogwam, insn, fawse,
				  &addw, &fixed) < 0)
		wetuwn -1;
	if (!fixed)
		wetuwn -1;

	/* Push stack awguments */
	push_wegs(ctx, JIT_STACK_WEGS, 0, JIT_WESEWVED_STACK);

	/* Emit function caww */
	emit_mov_i(ctx, MIPS_W_T9, addw);
	emit(ctx, jaww, MIPS_W_WA, MIPS_W_T9);
	emit(ctx, nop); /* Deway swot */

	cwobbew_weg(ctx, MIPS_W_WA);
	cwobbew_weg(ctx, MIPS_W_V0);
	cwobbew_weg(ctx, MIPS_W_V1);
	wetuwn 0;
}

/* Function taiw caww */
static int emit_taiw_caww(stwuct jit_context *ctx)
{
	u8 awy = wo(bpf2mips32[BPF_WEG_2]);
	u8 ind = wo(bpf2mips32[BPF_WEG_3]);
	u8 t1 = MIPS_W_T8;
	u8 t2 = MIPS_W_T9;
	int off;

	/*
	 * Taiw caww:
	 * eBPF W1   - function awgument (context ptw), passed in a0-a1
	 * eBPF W2   - ptw to object with awway of function entwy points
	 * eBPF W3   - awway index of function to be cawwed
	 * stack[sz] - wemaining taiw caww count, initiawized in pwowogue
	 */

	/* if (ind >= awy->map.max_entwies) goto out */
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, ww, t1, off, awy);             /* t1 = awy->map.max_entwies*/
	emit_woad_deway(ctx);                    /* Woad deway swot          */
	emit(ctx, swtu, t1, ind, t1);            /* t1 = ind < t1            */
	emit(ctx, beqz, t1, get_offset(ctx, 1)); /* PC += off(1) if t1 == 0  */
						 /* (next insn deway swot)   */
	/* if (TCC-- <= 0) goto out */
	emit(ctx, ww, t2, ctx->stack_size, MIPS_W_SP);  /* t2 = *(SP + size) */
	emit_woad_deway(ctx);                     /* Woad deway swot         */
	emit(ctx, bwez, t2, get_offset(ctx, 1));  /* PC += off(1) if t2 <= 0 */
	emit(ctx, addiu, t2, t2, -1);             /* t2-- (deway swot)       */
	emit(ctx, sw, t2, ctx->stack_size, MIPS_W_SP);  /* *(SP + size) = t2 */

	/* pwog = awy->ptws[ind] */
	off = offsetof(stwuct bpf_awway, ptws);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, sww, t1, ind, 2);               /* t1 = ind << 2           */
	emit(ctx, addu, t1, t1, awy);             /* t1 += awy               */
	emit(ctx, ww, t2, off, t1);               /* t2 = *(t1 + off)        */
	emit_woad_deway(ctx);                     /* Woad deway swot         */

	/* if (pwog == 0) goto out */
	emit(ctx, beqz, t2, get_offset(ctx, 1));  /* PC += off(1) if t2 == 0 */
	emit(ctx, nop);                           /* Deway swot              */

	/* func = pwog->bpf_func + 8 (pwowogue skip offset) */
	off = offsetof(stwuct bpf_pwog, bpf_func);
	if (off > 0x7fff)
		wetuwn -1;
	emit(ctx, ww, t1, off, t2);                /* t1 = *(t2 + off)       */
	emit_woad_deway(ctx);                      /* Woad deway swot        */
	emit(ctx, addiu, t1, t1, JIT_TCAWW_SKIP);  /* t1 += skip (8 ow 12)   */

	/* goto func */
	buiwd_epiwogue(ctx, t1);
	wetuwn 0;
}

/*
 * Stack fwame wayout fow a JITed pwogwam (stack gwows down).
 *
 * Highew addwess  : Cawwew's stack fwame       :
 *                 :----------------------------:
 *                 : 64-bit eBPF awgs w3-w5     :
 *                 :----------------------------:
 *                 : Wesewved / taiw caww count :
 *                 +============================+  <--- MIPS sp befowe caww
 *                 | Cawwee-saved wegistews,    |
 *                 | incwuding WA and FP        |
 *                 +----------------------------+  <--- eBPF FP (MIPS zewo,fp)
 *                 | Wocaw eBPF vawiabwes       |
 *                 | awwocated by pwogwam       |
 *                 +----------------------------+
 *                 | Wesewved fow cawwew-saved  |
 *                 | wegistews                  |
 *                 +----------------------------+
 *                 | Wesewved fow 64-bit eBPF   |
 *                 | awgs w3-w5 & awgs passed   |
 *                 | on stack in kewnew cawws   |
 * Wowew addwess   +============================+  <--- MIPS sp
 */

/* Buiwd pwogwam pwowogue to set up the stack and wegistews */
void buiwd_pwowogue(stwuct jit_context *ctx)
{
	const u8 *w1 = bpf2mips32[BPF_WEG_1];
	const u8 *fp = bpf2mips32[BPF_WEG_FP];
	int stack, saved, wocaws, wesewved;

	/*
	 * In the unwikewy event that the TCC wimit is waised to mowe
	 * than 16 bits, it is cwamped to the maximum vawue awwowed fow
	 * the genewated code (0xffff). It is bettew faiw to compiwe
	 * instead of degwading gwacefuwwy.
	 */
	BUIWD_BUG_ON(MAX_TAIW_CAWW_CNT > 0xffff);

	/*
	 * The fiwst two instwuctions initiawize TCC in the wesewved (fow us)
	 * 16-byte awea in the pawent's stack fwame. On a taiw caww, the
	 * cawwing function jumps into the pwowogue aftew these instwuctions.
	 */
	emit(ctx, owi, MIPS_W_T9, MIPS_W_ZEWO, MAX_TAIW_CAWW_CNT);
	emit(ctx, sw, MIPS_W_T9, 0, MIPS_W_SP);

	/*
	 * Wegistew eBPF W1 contains the 32-bit context pointew awgument.
	 * A 32-bit awgument is awways passed in MIPS wegistew a0, wegawdwess
	 * of CPU endianness. Initiawize W1 accowdingwy and zewo-extend.
	 */
#ifdef __BIG_ENDIAN
	emit(ctx, move, wo(w1), MIPS_W_A0);
#endif

	/* === Entwy-point fow taiw cawws === */

	/* Zewo-extend the 32-bit awgument */
	emit(ctx, move, hi(w1), MIPS_W_ZEWO);

	/* If the eBPF fwame pointew was accessed it must be saved */
	if (ctx->accessed & BIT(BPF_WEG_FP))
		cwobbew_weg64(ctx, fp);

	/* Compute the stack space needed fow cawwee-saved wegistews */
	saved = hweight32(ctx->cwobbewed & JIT_CAWWEE_WEGS) * sizeof(u32);
	saved = AWIGN(saved, MIPS_STACK_AWIGNMENT);

	/* Stack space used by eBPF pwogwam wocaw data */
	wocaws = AWIGN(ctx->pwogwam->aux->stack_depth, MIPS_STACK_AWIGNMENT);

	/*
	 * If we awe emitting function cawws, wesewve extwa stack space fow
	 * cawwew-saved wegistews and function awguments passed on the stack.
	 * The wequiwed space is computed automaticawwy duwing wesouwce
	 * usage discovewy (pass 1).
	 */
	wesewved = ctx->stack_used;

	/* Awwocate the stack fwame */
	stack = AWIGN(saved + wocaws + wesewved, MIPS_STACK_AWIGNMENT);
	emit(ctx, addiu, MIPS_W_SP, MIPS_W_SP, -stack);

	/* Stowe cawwee-saved wegistews on stack */
	push_wegs(ctx, ctx->cwobbewed & JIT_CAWWEE_WEGS, 0, stack - saved);

	/* Initiawize the eBPF fwame pointew if accessed */
	if (ctx->accessed & BIT(BPF_WEG_FP))
		emit(ctx, addiu, wo(fp), MIPS_W_SP, stack - saved);

	ctx->saved_size = saved;
	ctx->stack_size = stack;
}

/* Buiwd the pwogwam epiwogue to westowe the stack and wegistews */
void buiwd_epiwogue(stwuct jit_context *ctx, int dest_weg)
{
	/* Westowe cawwee-saved wegistews fwom stack */
	pop_wegs(ctx, ctx->cwobbewed & JIT_CAWWEE_WEGS, 0,
		 ctx->stack_size - ctx->saved_size);
	/*
	 * A 32-bit wetuwn vawue is awways passed in MIPS wegistew v0,
	 * but on big-endian tawgets the wow pawt of W0 is mapped to v1.
	 */
#ifdef __BIG_ENDIAN
	emit(ctx, move, MIPS_W_V0, MIPS_W_V1);
#endif

	/* Jump to the wetuwn addwess and adjust the stack pointew */
	emit(ctx, jw, dest_weg);
	emit(ctx, addiu, MIPS_W_SP, MIPS_W_SP, ctx->stack_size);
}

/* Buiwd one eBPF instwuction */
int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_context *ctx)
{
	const u8 *dst = bpf2mips32[insn->dst_weg];
	const u8 *swc = bpf2mips32[insn->swc_weg];
	const u8 *wes = bpf2mips32[BPF_WEG_0];
	const u8 *tmp = bpf2mips32[JIT_WEG_TMP];
	u8 code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;
	s32 vaw, wew;
	u8 awu, jmp;

	switch (code) {
	/* AWU opewations */
	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
		emit_mov_i(ctx, wo(dst), imm);
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
		if (imm == 1) {
			/* Speciaw mov32 fow zext */
			emit_mov_i(ctx, hi(dst), 0);
		} ewse {
			emit_mov_w(ctx, wo(dst), wo(swc));
			emit_zext_vew(ctx, dst);
		}
		bweak;
	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
		emit_awu_i(ctx, wo(dst), 0, BPF_NEG);
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst & imm */
	/* dst = dst | imm */
	/* dst = dst ^ imm */
	/* dst = dst << imm */
	/* dst = dst >> imm */
	/* dst = dst >> imm (awithmetic) */
	/* dst = dst + imm */
	/* dst = dst - imm */
	/* dst = dst * imm */
	/* dst = dst / imm */
	/* dst = dst % imm */
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_AWSH | BPF_K:
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_K:
		if (!vawid_awu_i(BPF_OP(code), imm)) {
			emit_mov_i(ctx, MIPS_W_T6, imm);
			emit_awu_w(ctx, wo(dst), MIPS_W_T6, BPF_OP(code));
		} ewse if (wewwite_awu_i(BPF_OP(code), imm, &awu, &vaw)) {
			emit_awu_i(ctx, wo(dst), vaw, awu);
		}
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = dst & swc */
	/* dst = dst | swc */
	/* dst = dst ^ swc */
	/* dst = dst << swc */
	/* dst = dst >> swc */
	/* dst = dst >> swc (awithmetic) */
	/* dst = dst + swc */
	/* dst = dst - swc */
	/* dst = dst * swc */
	/* dst = dst / swc */
	/* dst = dst % swc */
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_AWSH | BPF_X:
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU | BPF_MOD | BPF_X:
		emit_awu_w(ctx, wo(dst), wo(swc), BPF_OP(code));
		emit_zext_vew(ctx, dst);
		bweak;
	/* dst = imm (64-bit) */
	case BPF_AWU64 | BPF_MOV | BPF_K:
		emit_mov_se_i64(ctx, dst, imm);
		bweak;
	/* dst = swc (64-bit) */
	case BPF_AWU64 | BPF_MOV | BPF_X:
		emit_mov_w(ctx, wo(dst), wo(swc));
		emit_mov_w(ctx, hi(dst), hi(swc));
		bweak;
	/* dst = -dst (64-bit) */
	case BPF_AWU64 | BPF_NEG:
		emit_neg_i64(ctx, dst);
		bweak;
	/* dst = dst & imm (64-bit) */
	case BPF_AWU64 | BPF_AND | BPF_K:
		emit_awu_i64(ctx, dst, imm, BPF_OP(code));
		bweak;
	/* dst = dst | imm (64-bit) */
	/* dst = dst ^ imm (64-bit) */
	/* dst = dst + imm (64-bit) */
	/* dst = dst - imm (64-bit) */
	case BPF_AWU64 | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
		if (imm)
			emit_awu_i64(ctx, dst, imm, BPF_OP(code));
		bweak;
	/* dst = dst << imm (64-bit) */
	/* dst = dst >> imm (64-bit) */
	/* dst = dst >> imm (64-bit, awithmetic) */
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_WSH | BPF_K:
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		if (imm)
			emit_shift_i64(ctx, dst, imm, BPF_OP(code));
		bweak;
	/* dst = dst * imm (64-bit) */
	case BPF_AWU64 | BPF_MUW | BPF_K:
		emit_muw_i64(ctx, dst, imm);
		bweak;
	/* dst = dst / imm (64-bit) */
	/* dst = dst % imm (64-bit) */
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
		/*
		 * Sign-extend the immediate vawue into a tempowawy wegistew,
		 * and then do the opewation on this wegistew.
		 */
		emit_mov_se_i64(ctx, tmp, imm);
		emit_divmod_w64(ctx, dst, tmp, BPF_OP(code));
		bweak;
	/* dst = dst & swc (64-bit) */
	/* dst = dst | swc (64-bit) */
	/* dst = dst ^ swc (64-bit) */
	/* dst = dst + swc (64-bit) */
	/* dst = dst - swc (64-bit) */
	case BPF_AWU64 | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
		emit_awu_w64(ctx, dst, swc, BPF_OP(code));
		bweak;
	/* dst = dst << swc (64-bit) */
	/* dst = dst >> swc (64-bit) */
	/* dst = dst >> swc (64-bit, awithmetic) */
	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_WSH | BPF_X:
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit_shift_w64(ctx, dst, wo(swc), BPF_OP(code));
		bweak;
	/* dst = dst * swc (64-bit) */
	case BPF_AWU64 | BPF_MUW | BPF_X:
		emit_muw_w64(ctx, dst, swc);
		bweak;
	/* dst = dst / swc (64-bit) */
	/* dst = dst % swc (64-bit) */
	case BPF_AWU64 | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		emit_divmod_w64(ctx, dst, swc, BPF_OP(code));
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
		emit_mov_i(ctx, wo(dst), imm);
		emit_mov_i(ctx, hi(dst), insn[1].imm);
		wetuwn 1;
	/* WDX: dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_DW:
		emit_wdx(ctx, dst, wo(swc), off, BPF_SIZE(code));
		bweak;
	/* ST: *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_DW:
		switch (BPF_SIZE(code)) {
		case BPF_DW:
			/* Sign-extend immediate vawue into tempowawy weg */
			emit_mov_se_i64(ctx, tmp, imm);
			bweak;
		case BPF_W:
		case BPF_H:
		case BPF_B:
			emit_mov_i(ctx, wo(tmp), imm);
			bweak;
		}
		emit_stx(ctx, wo(dst), tmp, off, BPF_SIZE(code));
		bweak;
	/* STX: *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_DW:
		emit_stx(ctx, wo(dst), swc, off, BPF_SIZE(code));
		bweak;
	/* Specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;
	/* Atomics */
	case BPF_STX | BPF_ATOMIC | BPF_W:
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
			if (cpu_has_wwsc)
				emit_atomic_w(ctx, wo(dst), wo(swc), off, imm);
			ewse /* Non-ww/sc fawwback */
				emit_atomic_w32(ctx, wo(dst), wo(swc),
						off, imm);
			if (imm & BPF_FETCH)
				emit_zext_vew(ctx, swc);
			bweak;
		case BPF_CMPXCHG:
			if (cpu_has_wwsc)
				emit_cmpxchg_w(ctx, wo(dst), wo(swc),
					       wo(wes), off);
			ewse /* Non-ww/sc fawwback */
				emit_cmpxchg_w32(ctx, wo(dst), wo(swc), off);
			/* Wesuwt zewo-extension insewted by vewifiew */
			bweak;
		defauwt:
			goto notyet;
		}
		bweak;
	/* Atomics (64-bit) */
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
			emit_atomic_w64(ctx, wo(dst), swc, off, imm);
			bweak;
		case BPF_CMPXCHG:
			emit_cmpxchg_w64(ctx, wo(dst), swc, off);
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
		emit_jmp_w(ctx, wo(dst), wo(swc), wew, jmp);
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
		if (vawid_jmp_i(jmp, imm)) {
			emit_jmp_i(ctx, wo(dst), imm, wew, jmp);
		} ewse {
			/* Move wawge immediate to wegistew */
			emit_mov_i(ctx, MIPS_W_T6, imm);
			emit_jmp_w(ctx, wo(dst), MIPS_W_T6, wew, jmp);
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
		emit_jmp_w64(ctx, dst, swc, wew, jmp);
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
		emit_jmp_i64(ctx, dst, imm, wew, jmp);
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
