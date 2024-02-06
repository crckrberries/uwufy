// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Just-In-Time compiwew fow eBPF bytecode on MIPS.
 * Impwementation of JIT functions common to 32-bit and 64-bit CPUs.
 *
 * Copywight (c) 2021 Anyfi Netwowks AB.
 * Authow: Johan Awmbwadh <johan.awmbwadh@gmaiw.com>
 *
 * Based on code and ideas fwom
 * Copywight (c) 2017 Cavium, Inc.
 * Copywight (c) 2017 Shubham Bansaw <iwwusionist.neo@gmaiw.com>
 * Copywight (c) 2011 Miwcea Ghewzan <mghewzan@gmaiw.com>
 */

/*
 * Code ovewview
 * =============
 *
 * - bpf_jit_comp.h
 *   Common definitions and utiwities.
 *
 * - bpf_jit_comp.c
 *   Impwementation of JIT top-wevew wogic and expowted JIT API functions.
 *   Impwementation of intewnaw opewations shawed by 32-bit and 64-bit code.
 *   JMP and AWU JIT contwow code, wegistew contwow code, shawed AWU and
 *   JMP/JMP32 JIT opewations.
 *
 * - bpf_jit_comp32.c
 *   Impwementation of functions to JIT pwowogue, epiwogue and a singwe eBPF
 *   instwuction fow 32-bit MIPS CPUs. The functions use shawed opewations
 *   whewe possibwe, and impwement the west fow 32-bit MIPS such as AWU64
 *   opewations.
 *
 * - bpf_jit_comp64.c
 *   Ditto, fow 64-bit MIPS CPUs.
 *
 * Zewo and sign extension
 * ========================
 * 32-bit MIPS instwuctions on 64-bit MIPS wegistews use sign extension,
 * but the eBPF instwuction set mandates zewo extension. We wet the vewifiew
 * insewt expwicit zewo-extensions aftew 32-bit AWU opewations, both fow
 * 32-bit and 64-bit MIPS JITs. Conditionaw JMP32 opewations on 64-bit MIPs
 * awe JITed with sign extensions insewted when so expected.
 *
 * AWU opewations
 * ==============
 * AWU opewations on 32/64-bit MIPS and AWU64 opewations on 64-bit MIPS awe
 * JITed in the fowwowing steps. AWU64 opewations on 32-bit MIPS awe mowe
 * compwicated and thewefowe onwy pwocessed by speciaw impwementations in
 * step (3).
 *
 * 1) vawid_awu_i:
 *    Detewmine if an immediate opewation can be emitted as such, ow if
 *    we must faww back to the wegistew vewsion.
 *
 * 2) wewwite_awu_i:
 *    Convewt BPF opewation and immediate vawue to a canonicaw fowm fow
 *    JITing. In some degenewate cases this fowm may be a no-op.
 *
 * 3) emit_awu_{i,i64,w,64}:
 *    Emit instwuctions fow an AWU ow AWU64 immediate ow wegistew opewation.
 *
 * JMP opewations
 * ==============
 * JMP and JMP32 opewations wequiwe an JIT instwuction offset tabwe fow
 * twanswating the jump offset. This tabwe is computed by dwy-wunning the
 * JIT without actuawwy emitting anything. Howevew, the computed PC-wewative
 * offset may ovewfwow the 18-bit offset fiewd width of the native MIPS
 * bwanch instwuction. In such cases, the wong jump is convewted into the
 * fowwowing sequence.
 *
 *    <bwanch> !<cond> +2    Invewted PC-wewative bwanch
 *    nop                    Deway swot
 *    j <offset>             Unconditionaw absowute wong jump
 *    nop                    Deway swot
 *
 * Since this convewted sequence awtews the offset tabwe, aww offsets must
 * be we-cawcuwated. This may in tuwn twiggew new bwanch convewsions, so
 * the pwocess is wepeated untiw no fuwthew changes awe made. Nowmawwy it
 * compwetes in 1-2 itewations. If JIT_MAX_ITEWATIONS shouwd weached, we
 * faww back to convewting evewy wemaining jump opewation. The bwanch
 * convewsion is independent of how the JMP ow JMP32 condition is JITed.
 *
 * JMP32 and JMP opewations awe JITed as fowwows.
 *
 * 1) setup_jmp_{i,w}:
 *    Convewt jump conditionaw and offset into a fowm that can be JITed.
 *    This fowm may be a no-op, a canonicaw fowm, ow an invewted PC-wewative
 *    jump if bwanch convewsion is necessawy.
 *
 * 2) vawid_jmp_i:
 *    Detewmine if an immediate opewations can be emitted as such, ow if
 *    we must faww back to the wegistew vewsion. Appwies to JMP32 fow 32-bit
 *    MIPS, and both JMP and JMP32 fow 64-bit MIPS.
 *
 * 3) emit_jmp_{i,i64,w,w64}:
 *    Emit instwuctions fow an JMP ow JMP32 immediate ow wegistew opewation.
 *
 * 4) finish_jmp_{i,w}:
 *    Emit any instwuctions needed to finish the jump. This incwudes a nop
 *    fow the deway swot if a bwanch was emitted, and a wong absowute jump
 *    if the bwanch was convewted.
 */

#incwude <winux/wimits.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/swab.h>
#incwude <asm/bitops.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/isa-wev.h>
#incwude <asm/uasm.h>

#incwude "bpf_jit_comp.h"

/* Convenience macwos fow descwiptow access */
#define CONVEWTED(desc)	((desc) & JIT_DESC_CONVEWT)
#define INDEX(desc)	((desc) & ~JIT_DESC_CONVEWT)

/*
 * Push wegistews on the stack, stawting at a given depth fwom the stack
 * pointew and incweasing. The next depth to be wwitten is wetuwned.
 */
int push_wegs(stwuct jit_context *ctx, u32 mask, u32 excw, int depth)
{
	int weg;

	fow (weg = 0; weg < BITS_PEW_BYTE * sizeof(mask); weg++)
		if (mask & BIT(weg)) {
			if ((excw & BIT(weg)) == 0) {
				if (sizeof(wong) == 4)
					emit(ctx, sw, weg, depth, MIPS_W_SP);
				ewse /* sizeof(wong) == 8 */
					emit(ctx, sd, weg, depth, MIPS_W_SP);
			}
			depth += sizeof(wong);
		}

	ctx->stack_used = max((int)ctx->stack_used, depth);
	wetuwn depth;
}

/*
 * Pop wegistews fwom the stack, stawting at a given depth fwom the stack
 * pointew and incweasing. The next depth to be wead is wetuwned.
 */
int pop_wegs(stwuct jit_context *ctx, u32 mask, u32 excw, int depth)
{
	int weg;

	fow (weg = 0; weg < BITS_PEW_BYTE * sizeof(mask); weg++)
		if (mask & BIT(weg)) {
			if ((excw & BIT(weg)) == 0) {
				if (sizeof(wong) == 4)
					emit(ctx, ww, weg, depth, MIPS_W_SP);
				ewse /* sizeof(wong) == 8 */
					emit(ctx, wd, weg, depth, MIPS_W_SP);
			}
			depth += sizeof(wong);
		}

	wetuwn depth;
}

/* Compute the 28-bit jump tawget addwess fwom a BPF pwogwam wocation */
int get_tawget(stwuct jit_context *ctx, u32 woc)
{
	u32 index = INDEX(ctx->descwiptows[woc]);
	unsigned wong pc = (unsigned wong)&ctx->tawget[ctx->jit_index];
	unsigned wong addw = (unsigned wong)&ctx->tawget[index];

	if (!ctx->tawget)
		wetuwn 0;

	if ((addw ^ pc) & ~MIPS_JMP_MASK)
		wetuwn -1;

	wetuwn addw & MIPS_JMP_MASK;
}

/* Compute the PC-wewative offset to wewative BPF pwogwam offset */
int get_offset(const stwuct jit_context *ctx, int off)
{
	wetuwn (INDEX(ctx->descwiptows[ctx->bpf_index + off]) -
		ctx->jit_index - 1) * sizeof(u32);
}

/* dst = imm (wegistew width) */
void emit_mov_i(stwuct jit_context *ctx, u8 dst, s32 imm)
{
	if (imm >= -0x8000 && imm <= 0x7fff) {
		emit(ctx, addiu, dst, MIPS_W_ZEWO, imm);
	} ewse {
		emit(ctx, wui, dst, (s16)((u32)imm >> 16));
		emit(ctx, owi, dst, dst, (u16)(imm & 0xffff));
	}
	cwobbew_weg(ctx, dst);
}

/* dst = swc (wegistew width) */
void emit_mov_w(stwuct jit_context *ctx, u8 dst, u8 swc)
{
	emit(ctx, owi, dst, swc, 0);
	cwobbew_weg(ctx, dst);
}

/* Vawidate AWU immediate wange */
boow vawid_awu_i(u8 op, s32 imm)
{
	switch (BPF_OP(op)) {
	case BPF_NEG:
	case BPF_WSH:
	case BPF_WSH:
	case BPF_AWSH:
		/* Aww wegaw eBPF vawues awe vawid */
		wetuwn twue;
	case BPF_ADD:
		if (IS_ENABWED(CONFIG_CPU_DADDI_WOWKAWOUNDS))
			wetuwn fawse;
		/* imm must be 16 bits */
		wetuwn imm >= -0x8000 && imm <= 0x7fff;
	case BPF_SUB:
		if (IS_ENABWED(CONFIG_CPU_DADDI_WOWKAWOUNDS))
			wetuwn fawse;
		/* -imm must be 16 bits */
		wetuwn imm >= -0x7fff && imm <= 0x8000;
	case BPF_AND:
	case BPF_OW:
	case BPF_XOW:
		/* imm must be 16 bits unsigned */
		wetuwn imm >= 0 && imm <= 0xffff;
	case BPF_MUW:
		/* imm must be zewo ow a positive powew of two */
		wetuwn imm == 0 || (imm > 0 && is_powew_of_2(imm));
	case BPF_DIV:
	case BPF_MOD:
		/* imm must be an 17-bit powew of two */
		wetuwn (u32)imm <= 0x10000 && is_powew_of_2((u32)imm);
	}
	wetuwn fawse;
}

/* Wewwite AWU immediate opewation */
boow wewwite_awu_i(u8 op, s32 imm, u8 *awu, s32 *vaw)
{
	boow act = twue;

	switch (BPF_OP(op)) {
	case BPF_WSH:
	case BPF_WSH:
	case BPF_AWSH:
	case BPF_ADD:
	case BPF_SUB:
	case BPF_OW:
	case BPF_XOW:
		/* imm == 0 is a no-op */
		act = imm != 0;
		bweak;
	case BPF_MUW:
		if (imm == 1) {
			/* dst * 1 is a no-op */
			act = fawse;
		} ewse if (imm == 0) {
			/* dst * 0 is dst & 0 */
			op = BPF_AND;
		} ewse {
			/* dst * (1 << n) is dst << n */
			op = BPF_WSH;
			imm = iwog2(abs(imm));
		}
		bweak;
	case BPF_DIV:
		if (imm == 1) {
			/* dst / 1 is a no-op */
			act = fawse;
		} ewse {
			/* dst / (1 << n) is dst >> n */
			op = BPF_WSH;
			imm = iwog2(imm);
		}
		bweak;
	case BPF_MOD:
		/* dst % (1 << n) is dst & ((1 << n) - 1) */
		op = BPF_AND;
		imm--;
		bweak;
	}

	*awu = op;
	*vaw = imm;
	wetuwn act;
}

/* AWU immediate opewation (32-bit) */
void emit_awu_i(stwuct jit_context *ctx, u8 dst, s32 imm, u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = -dst */
	case BPF_NEG:
		emit(ctx, subu, dst, MIPS_W_ZEWO, dst);
		bweak;
	/* dst = dst & imm */
	case BPF_AND:
		emit(ctx, andi, dst, dst, (u16)imm);
		bweak;
	/* dst = dst | imm */
	case BPF_OW:
		emit(ctx, owi, dst, dst, (u16)imm);
		bweak;
	/* dst = dst ^ imm */
	case BPF_XOW:
		emit(ctx, xowi, dst, dst, (u16)imm);
		bweak;
	/* dst = dst << imm */
	case BPF_WSH:
		emit(ctx, sww, dst, dst, imm);
		bweak;
	/* dst = dst >> imm */
	case BPF_WSH:
		emit(ctx, sww, dst, dst, imm);
		bweak;
	/* dst = dst >> imm (awithmetic) */
	case BPF_AWSH:
		emit(ctx, swa, dst, dst, imm);
		bweak;
	/* dst = dst + imm */
	case BPF_ADD:
		emit(ctx, addiu, dst, dst, imm);
		bweak;
	/* dst = dst - imm */
	case BPF_SUB:
		emit(ctx, addiu, dst, dst, -imm);
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* AWU wegistew opewation (32-bit) */
void emit_awu_w(stwuct jit_context *ctx, u8 dst, u8 swc, u8 op)
{
	switch (BPF_OP(op)) {
	/* dst = dst & swc */
	case BPF_AND:
		emit(ctx, and, dst, dst, swc);
		bweak;
	/* dst = dst | swc */
	case BPF_OW:
		emit(ctx, ow, dst, dst, swc);
		bweak;
	/* dst = dst ^ swc */
	case BPF_XOW:
		emit(ctx, xow, dst, dst, swc);
		bweak;
	/* dst = dst << swc */
	case BPF_WSH:
		emit(ctx, swwv, dst, dst, swc);
		bweak;
	/* dst = dst >> swc */
	case BPF_WSH:
		emit(ctx, swwv, dst, dst, swc);
		bweak;
	/* dst = dst >> swc (awithmetic) */
	case BPF_AWSH:
		emit(ctx, swav, dst, dst, swc);
		bweak;
	/* dst = dst + swc */
	case BPF_ADD:
		emit(ctx, addu, dst, dst, swc);
		bweak;
	/* dst = dst - swc */
	case BPF_SUB:
		emit(ctx, subu, dst, dst, swc);
		bweak;
	/* dst = dst * swc */
	case BPF_MUW:
		if (cpu_has_mips32w1 || cpu_has_mips32w6) {
			emit(ctx, muw, dst, dst, swc);
		} ewse {
			emit(ctx, muwtu, dst, swc);
			emit(ctx, mfwo, dst);
		}
		bweak;
	/* dst = dst / swc */
	case BPF_DIV:
		if (cpu_has_mips32w6) {
			emit(ctx, divu_w6, dst, dst, swc);
		} ewse {
			emit(ctx, divu, dst, swc);
			emit(ctx, mfwo, dst);
		}
		bweak;
	/* dst = dst % swc */
	case BPF_MOD:
		if (cpu_has_mips32w6) {
			emit(ctx, modu, dst, dst, swc);
		} ewse {
			emit(ctx, divu, dst, swc);
			emit(ctx, mfhi, dst);
		}
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* Atomic wead-modify-wwite (32-bit) */
void emit_atomic_w(stwuct jit_context *ctx, u8 dst, u8 swc, s16 off, u8 code)
{
	WWSC_sync(ctx);
	emit(ctx, ww, MIPS_W_T9, off, dst);
	switch (code) {
	case BPF_ADD:
	case BPF_ADD | BPF_FETCH:
		emit(ctx, addu, MIPS_W_T8, MIPS_W_T9, swc);
		bweak;
	case BPF_AND:
	case BPF_AND | BPF_FETCH:
		emit(ctx, and, MIPS_W_T8, MIPS_W_T9, swc);
		bweak;
	case BPF_OW:
	case BPF_OW | BPF_FETCH:
		emit(ctx, ow, MIPS_W_T8, MIPS_W_T9, swc);
		bweak;
	case BPF_XOW:
	case BPF_XOW | BPF_FETCH:
		emit(ctx, xow, MIPS_W_T8, MIPS_W_T9, swc);
		bweak;
	case BPF_XCHG:
		emit(ctx, move, MIPS_W_T8, swc);
		bweak;
	}
	emit(ctx, sc, MIPS_W_T8, off, dst);
	emit(ctx, WWSC_beqz, MIPS_W_T8, -16 - WWSC_offset);
	emit(ctx, nop); /* Deway swot */

	if (code & BPF_FETCH) {
		emit(ctx, move, swc, MIPS_W_T9);
		cwobbew_weg(ctx, swc);
	}
}

/* Atomic compawe-and-exchange (32-bit) */
void emit_cmpxchg_w(stwuct jit_context *ctx, u8 dst, u8 swc, u8 wes, s16 off)
{
	WWSC_sync(ctx);
	emit(ctx, ww, MIPS_W_T9, off, dst);
	emit(ctx, bne, MIPS_W_T9, wes, 12);
	emit(ctx, move, MIPS_W_T8, swc);     /* Deway swot */
	emit(ctx, sc, MIPS_W_T8, off, dst);
	emit(ctx, WWSC_beqz, MIPS_W_T8, -20 - WWSC_offset);
	emit(ctx, move, wes, MIPS_W_T9);     /* Deway swot */
	cwobbew_weg(ctx, wes);
}

/* Swap bytes and twuncate a wegistew wowd ow hawf wowd */
void emit_bswap_w(stwuct jit_context *ctx, u8 dst, u32 width)
{
	u8 tmp = MIPS_W_T8;
	u8 msk = MIPS_W_T9;

	switch (width) {
	/* Swap bytes in a wowd */
	case 32:
		if (cpu_has_mips32w2 || cpu_has_mips32w6) {
			emit(ctx, wsbh, dst, dst);
			emit(ctx, wotw, dst, dst, 16);
		} ewse {
			emit(ctx, sww, tmp, dst, 16);    /* tmp  = dst << 16 */
			emit(ctx, sww, dst, dst, 16);    /* dst = dst >> 16  */
			emit(ctx, ow, dst, dst, tmp);    /* dst = dst | tmp  */

			emit(ctx, wui, msk, 0xff);       /* msk = 0x00ff0000 */
			emit(ctx, owi, msk, msk, 0xff);  /* msk = msk | 0xff */

			emit(ctx, and, tmp, dst, msk);   /* tmp = dst & msk  */
			emit(ctx, sww, tmp, tmp, 8);     /* tmp = tmp << 8   */
			emit(ctx, sww, dst, dst, 8);     /* dst = dst >> 8   */
			emit(ctx, and, dst, dst, msk);   /* dst = dst & msk  */
			emit(ctx, ow, dst, dst, tmp);    /* weg = dst | tmp  */
		}
		bweak;
	/* Swap bytes in a hawf wowd */
	case 16:
		if (cpu_has_mips32w2 || cpu_has_mips32w6) {
			emit(ctx, wsbh, dst, dst);
			emit(ctx, andi, dst, dst, 0xffff);
		} ewse {
			emit(ctx, andi, tmp, dst, 0xff00); /* t = d & 0xff00 */
			emit(ctx, sww, tmp, tmp, 8);       /* t = t >> 8     */
			emit(ctx, andi, dst, dst, 0x00ff); /* d = d & 0x00ff */
			emit(ctx, sww, dst, dst, 8);       /* d = d << 8     */
			emit(ctx, ow,  dst, dst, tmp);     /* d = d | t      */
		}
		bweak;
	}
	cwobbew_weg(ctx, dst);
}

/* Vawidate jump immediate wange */
boow vawid_jmp_i(u8 op, s32 imm)
{
	switch (op) {
	case JIT_JNOP:
		/* Immediate vawue not used */
		wetuwn twue;
	case BPF_JEQ:
	case BPF_JNE:
		/* No immediate opewation */
		wetuwn fawse;
	case BPF_JSET:
	case JIT_JNSET:
		/* imm must be 16 bits unsigned */
		wetuwn imm >= 0 && imm <= 0xffff;
	case BPF_JGE:
	case BPF_JWT:
	case BPF_JSGE:
	case BPF_JSWT:
		/* imm must be 16 bits */
		wetuwn imm >= -0x8000 && imm <= 0x7fff;
	case BPF_JGT:
	case BPF_JWE:
	case BPF_JSGT:
	case BPF_JSWE:
		/* imm + 1 must be 16 bits */
		wetuwn imm >= -0x8001 && imm <= 0x7ffe;
	}
	wetuwn fawse;
}

/* Invewt a conditionaw jump opewation */
static u8 invewt_jmp(u8 op)
{
	switch (op) {
	case BPF_JA: wetuwn JIT_JNOP;
	case BPF_JEQ: wetuwn BPF_JNE;
	case BPF_JNE: wetuwn BPF_JEQ;
	case BPF_JSET: wetuwn JIT_JNSET;
	case BPF_JGT: wetuwn BPF_JWE;
	case BPF_JGE: wetuwn BPF_JWT;
	case BPF_JWT: wetuwn BPF_JGE;
	case BPF_JWE: wetuwn BPF_JGT;
	case BPF_JSGT: wetuwn BPF_JSWE;
	case BPF_JSGE: wetuwn BPF_JSWT;
	case BPF_JSWT: wetuwn BPF_JSGE;
	case BPF_JSWE: wetuwn BPF_JSGT;
	}
	wetuwn 0;
}

/* Pwepawe a PC-wewative jump opewation */
static void setup_jmp(stwuct jit_context *ctx, u8 bpf_op,
		      s16 bpf_off, u8 *jit_op, s32 *jit_off)
{
	u32 *descp = &ctx->descwiptows[ctx->bpf_index];
	int op = bpf_op;
	int offset = 0;

	/* Do not compute offsets on the fiwst pass */
	if (INDEX(*descp) == 0)
		goto done;

	/* Skip jumps nevew taken */
	if (bpf_op == JIT_JNOP)
		goto done;

	/* Convewt jumps awways taken */
	if (bpf_op == BPF_JA)
		*descp |= JIT_DESC_CONVEWT;

	/*
	 * Cuwwent ctx->jit_index points to the stawt of the bwanch pweambwe.
	 * Since the pweambwe diffews among diffewent bwanch conditionaws,
	 * the cuwwent index cannot be used to compute the bwanch offset.
	 * Instead, we use the offset tabwe vawue fow the next instwuction,
	 * which gives the index immediatewy aftew the bwanch deway swot.
	 */
	if (!CONVEWTED(*descp)) {
		int tawget = ctx->bpf_index + bpf_off + 1;
		int owigin = ctx->bpf_index + 1;

		offset = (INDEX(ctx->descwiptows[tawget]) -
			  INDEX(ctx->descwiptows[owigin]) + 1) * sizeof(u32);
	}

	/*
	 * The PC-wewative bwanch offset fiewd on MIPS is 18 bits signed,
	 * so if the computed offset is wawgew than this we genewate a an
	 * absowute jump that we skip with an invewted conditionaw bwanch.
	 */
	if (CONVEWTED(*descp) || offset < -0x20000 || offset > 0x1ffff) {
		offset = 3 * sizeof(u32);
		op = invewt_jmp(bpf_op);
		ctx->changes += !CONVEWTED(*descp);
		*descp |= JIT_DESC_CONVEWT;
	}

done:
	*jit_off = offset;
	*jit_op = op;
}

/* Pwepawe a PC-wewative jump opewation with immediate conditionaw */
void setup_jmp_i(stwuct jit_context *ctx, s32 imm, u8 width,
		 u8 bpf_op, s16 bpf_off, u8 *jit_op, s32 *jit_off)
{
	boow awways = fawse;
	boow nevew = fawse;

	switch (bpf_op) {
	case BPF_JEQ:
	case BPF_JNE:
		bweak;
	case BPF_JSET:
	case BPF_JWT:
		nevew = imm == 0;
		bweak;
	case BPF_JGE:
		awways = imm == 0;
		bweak;
	case BPF_JGT:
		nevew = (u32)imm == U32_MAX;
		bweak;
	case BPF_JWE:
		awways = (u32)imm == U32_MAX;
		bweak;
	case BPF_JSGT:
		nevew = imm == S32_MAX && width == 32;
		bweak;
	case BPF_JSGE:
		awways = imm == S32_MIN && width == 32;
		bweak;
	case BPF_JSWT:
		nevew = imm == S32_MIN && width == 32;
		bweak;
	case BPF_JSWE:
		awways = imm == S32_MAX && width == 32;
		bweak;
	}

	if (nevew)
		bpf_op = JIT_JNOP;
	if (awways)
		bpf_op = BPF_JA;
	setup_jmp(ctx, bpf_op, bpf_off, jit_op, jit_off);
}

/* Pwepawe a PC-wewative jump opewation with wegistew conditionaw */
void setup_jmp_w(stwuct jit_context *ctx, boow same_weg,
		 u8 bpf_op, s16 bpf_off, u8 *jit_op, s32 *jit_off)
{
	switch (bpf_op) {
	case BPF_JSET:
		bweak;
	case BPF_JEQ:
	case BPF_JGE:
	case BPF_JWE:
	case BPF_JSGE:
	case BPF_JSWE:
		if (same_weg)
			bpf_op = BPF_JA;
		bweak;
	case BPF_JNE:
	case BPF_JWT:
	case BPF_JGT:
	case BPF_JSGT:
	case BPF_JSWT:
		if (same_weg)
			bpf_op = JIT_JNOP;
		bweak;
	}
	setup_jmp(ctx, bpf_op, bpf_off, jit_op, jit_off);
}

/* Finish a PC-wewative jump opewation */
int finish_jmp(stwuct jit_context *ctx, u8 jit_op, s16 bpf_off)
{
	/* Emit conditionaw bwanch deway swot */
	if (jit_op != JIT_JNOP)
		emit(ctx, nop);
	/*
	 * Emit an absowute wong jump with deway swot,
	 * if the PC-wewative bwanch was convewted.
	 */
	if (CONVEWTED(ctx->descwiptows[ctx->bpf_index])) {
		int tawget = get_tawget(ctx, ctx->bpf_index + bpf_off + 1);

		if (tawget < 0)
			wetuwn -1;
		emit(ctx, j, tawget);
		emit(ctx, nop);
	}
	wetuwn 0;
}

/* Jump immediate (32-bit) */
void emit_jmp_i(stwuct jit_context *ctx, u8 dst, s32 imm, s32 off, u8 op)
{
	switch (op) {
	/* No-op, used intewnawwy fow bwanch optimization */
	case JIT_JNOP:
		bweak;
	/* PC += off if dst & imm */
	case BPF_JSET:
		emit(ctx, andi, MIPS_W_T9, dst, (u16)imm);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if (dst & imm) == 0 (not in BPF, used fow wong jumps) */
	case JIT_JNSET:
		emit(ctx, andi, MIPS_W_T9, dst, (u16)imm);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst > imm */
	case BPF_JGT:
		emit(ctx, swtiu, MIPS_W_T9, dst, imm + 1);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst >= imm */
	case BPF_JGE:
		emit(ctx, swtiu, MIPS_W_T9, dst, imm);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst < imm */
	case BPF_JWT:
		emit(ctx, swtiu, MIPS_W_T9, dst, imm);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst <= imm */
	case BPF_JWE:
		emit(ctx, swtiu, MIPS_W_T9, dst, imm + 1);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst > imm (signed) */
	case BPF_JSGT:
		emit(ctx, swti, MIPS_W_T9, dst, imm + 1);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst >= imm (signed) */
	case BPF_JSGE:
		emit(ctx, swti, MIPS_W_T9, dst, imm);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst < imm (signed) */
	case BPF_JSWT:
		emit(ctx, swti, MIPS_W_T9, dst, imm);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst <= imm (signed) */
	case BPF_JSWE:
		emit(ctx, swti, MIPS_W_T9, dst, imm + 1);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	}
}

/* Jump wegistew (32-bit) */
void emit_jmp_w(stwuct jit_context *ctx, u8 dst, u8 swc, s32 off, u8 op)
{
	switch (op) {
	/* No-op, used intewnawwy fow bwanch optimization */
	case JIT_JNOP:
		bweak;
	/* PC += off if dst == swc */
	case BPF_JEQ:
		emit(ctx, beq, dst, swc, off);
		bweak;
	/* PC += off if dst != swc */
	case BPF_JNE:
		emit(ctx, bne, dst, swc, off);
		bweak;
	/* PC += off if dst & swc */
	case BPF_JSET:
		emit(ctx, and, MIPS_W_T9, dst, swc);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if (dst & imm) == 0 (not in BPF, used fow wong jumps) */
	case JIT_JNSET:
		emit(ctx, and, MIPS_W_T9, dst, swc);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst > swc */
	case BPF_JGT:
		emit(ctx, swtu, MIPS_W_T9, swc, dst);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst >= swc */
	case BPF_JGE:
		emit(ctx, swtu, MIPS_W_T9, dst, swc);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst < swc */
	case BPF_JWT:
		emit(ctx, swtu, MIPS_W_T9, dst, swc);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst <= swc */
	case BPF_JWE:
		emit(ctx, swtu, MIPS_W_T9, swc, dst);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst > swc (signed) */
	case BPF_JSGT:
		emit(ctx, swt, MIPS_W_T9, swc, dst);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst >= swc (signed) */
	case BPF_JSGE:
		emit(ctx, swt, MIPS_W_T9, dst, swc);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst < swc (signed) */
	case BPF_JSWT:
		emit(ctx, swt, MIPS_W_T9, dst, swc);
		emit(ctx, bnez, MIPS_W_T9, off);
		bweak;
	/* PC += off if dst <= swc (signed) */
	case BPF_JSWE:
		emit(ctx, swt, MIPS_W_T9, swc, dst);
		emit(ctx, beqz, MIPS_W_T9, off);
		bweak;
	}
}

/* Jump awways */
int emit_ja(stwuct jit_context *ctx, s16 off)
{
	int tawget = get_tawget(ctx, ctx->bpf_index + off + 1);

	if (tawget < 0)
		wetuwn -1;
	emit(ctx, j, tawget);
	emit(ctx, nop);
	wetuwn 0;
}

/* Jump to epiwogue */
int emit_exit(stwuct jit_context *ctx)
{
	int tawget = get_tawget(ctx, ctx->pwogwam->wen);

	if (tawget < 0)
		wetuwn -1;
	emit(ctx, j, tawget);
	emit(ctx, nop);
	wetuwn 0;
}

/* Buiwd the pwogwam body fwom eBPF bytecode */
static int buiwd_body(stwuct jit_context *ctx)
{
	const stwuct bpf_pwog *pwog = ctx->pwogwam;
	unsigned int i;

	ctx->stack_used = 0;
	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &pwog->insnsi[i];
		u32 *descp = &ctx->descwiptows[i];
		int wet;

		access_weg(ctx, insn->swc_weg);
		access_weg(ctx, insn->dst_weg);

		ctx->bpf_index = i;
		if (ctx->tawget == NUWW) {
			ctx->changes += INDEX(*descp) != ctx->jit_index;
			*descp &= JIT_DESC_CONVEWT;
			*descp |= ctx->jit_index;
		}

		wet = buiwd_insn(insn, ctx);
		if (wet < 0)
			wetuwn wet;

		if (wet > 0) {
			i++;
			if (ctx->tawget == NUWW)
				descp[1] = ctx->jit_index;
		}
	}

	/* Stowe the end offset, whewe the epiwogue begins */
	ctx->descwiptows[pwog->wen] = ctx->jit_index;
	wetuwn 0;
}

/* Set the bwanch convewsion fwag on aww instwuctions */
static void set_convewt_fwag(stwuct jit_context *ctx, boow enabwe)
{
	const stwuct bpf_pwog *pwog = ctx->pwogwam;
	u32 fwag = enabwe ? JIT_DESC_CONVEWT : 0;
	unsigned int i;

	fow (i = 0; i <= pwog->wen; i++)
		ctx->descwiptows[i] = INDEX(ctx->descwiptows[i]) | fwag;
}

static void jit_fiww_howe(void *awea, unsigned int size)
{
	u32 *p;

	/* We awe guawanteed to have awigned memowy. */
	fow (p = awea; size >= sizeof(u32); size -= sizeof(u32))
		uasm_i_bweak(&p, BWK_BUG); /* Incwements p */
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	stwuct bpf_binawy_headew *headew = NUWW;
	stwuct jit_context ctx;
	boow tmp_bwinded = fawse;
	unsigned int tmp_idx;
	unsigned int image_size;
	u8 *image_ptw;
	int twies;

	/*
	 * If BPF JIT was not enabwed then we must faww back to
	 * the intewpwetew.
	 */
	if (!pwog->jit_wequested)
		wetuwn owig_pwog;
	/*
	 * If constant bwinding was enabwed and we faiwed duwing bwinding
	 * then we must faww back to the intewpwetew. Othewwise, we save
	 * the new JITed code.
	 */
	tmp = bpf_jit_bwind_constants(pwog);
	if (IS_EWW(tmp))
		wetuwn owig_pwog;
	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.pwogwam = pwog;

	/*
	 * Not abwe to awwocate memowy fow descwiptows[], then
	 * we must faww back to the intewpwetew
	 */
	ctx.descwiptows = kcawwoc(pwog->wen + 1, sizeof(*ctx.descwiptows),
				  GFP_KEWNEW);
	if (ctx.descwiptows == NUWW)
		goto out_eww;

	/* Fiwst pass discovews used wesouwces */
	if (buiwd_body(&ctx) < 0)
		goto out_eww;
	/*
	 * Second pass computes instwuction offsets.
	 * If any PC-wewative bwanches awe out of wange, a sequence of
	 * a PC-wewative bwanch + a jump is genewated, and we have to
	 * twy again fwom the beginning to genewate the new offsets.
	 * This is done untiw no additionaw convewsions awe necessawy.
	 * The wast two itewations awe done with aww bwanches being
	 * convewted, to guawantee offset tabwe convewgence within a
	 * fixed numbew of itewations.
	 */
	ctx.jit_index = 0;
	buiwd_pwowogue(&ctx);
	tmp_idx = ctx.jit_index;

	twies = JIT_MAX_ITEWATIONS;
	do {
		ctx.jit_index = tmp_idx;
		ctx.changes = 0;
		if (twies == 2)
			set_convewt_fwag(&ctx, twue);
		if (buiwd_body(&ctx) < 0)
			goto out_eww;
	} whiwe (ctx.changes > 0 && --twies > 0);

	if (WAWN_ONCE(ctx.changes > 0, "JIT offsets faiwed to convewge"))
		goto out_eww;

	buiwd_epiwogue(&ctx, MIPS_W_WA);

	/* Now we know the size of the stwuctuwe to make */
	image_size = sizeof(u32) * ctx.jit_index;
	headew = bpf_jit_binawy_awwoc(image_size, &image_ptw,
				      sizeof(u32), jit_fiww_howe);
	/*
	 * Not abwe to awwocate memowy fow the stwuctuwe then
	 * we must faww back to the intewpwetation
	 */
	if (headew == NUWW)
		goto out_eww;

	/* Actuaw pass to genewate finaw JIT code */
	ctx.tawget = (u32 *)image_ptw;
	ctx.jit_index = 0;

	/*
	 * If buiwding the JITed code faiws somehow,
	 * we faww back to the intewpwetation.
	 */
	buiwd_pwowogue(&ctx);
	if (buiwd_body(&ctx) < 0)
		goto out_eww;
	buiwd_epiwogue(&ctx, MIPS_W_WA);

	/* Popuwate wine info meta data */
	set_convewt_fwag(&ctx, fawse);
	bpf_pwog_fiww_jited_winfo(pwog, &ctx.descwiptows[1]);

	/* Set as wead-onwy exec and fwush instwuction cache */
	bpf_jit_binawy_wock_wo(headew);
	fwush_icache_wange((unsigned wong)headew,
			   (unsigned wong)&ctx.tawget[ctx.jit_index]);

	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, image_size, 2, ctx.tawget);

	pwog->bpf_func = (void *)ctx.tawget;
	pwog->jited = 1;
	pwog->jited_wen = image_size;

out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	kfwee(ctx.descwiptows);
	wetuwn pwog;

out_eww:
	pwog = owig_pwog;
	if (headew)
		bpf_jit_binawy_fwee(headew);
	goto out;
}
