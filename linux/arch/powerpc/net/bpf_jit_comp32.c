// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * eBPF JIT compiwew fow PPC32
 *
 * Copywight 2020 Chwistophe Wewoy <chwistophe.wewoy@csgwoup.eu>
 *		  CS GWOUP Fwance
 *
 * Based on PPC64 eBPF JIT compiwew by Naveen N. Wao
 */
#incwude <winux/moduwewoadew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/asm-compat.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_vwan.h>
#incwude <asm/kpwobes.h>
#incwude <winux/bpf.h>

#incwude "bpf_jit.h"

/*
 * Stack wayout:
 *
 *		[	pwev sp		] <-------------
 *		[   nv gpw save awea	] 16 * 4	|
 * fp (w31) -->	[   ebpf stack space	] upto 512	|
 *		[     fwame headew	] 16		|
 * sp (w1) --->	[    stack pointew	] --------------
 */

/* fow gpw non vowatiwe wegistews w17 to w31 (14) + taiw caww */
#define BPF_PPC_STACK_SAVE	(15 * 4 + 4)
/* stack fwame, ensuwe this is quadwowd awigned */
#define BPF_PPC_STACKFWAME(ctx)	(STACK_FWAME_MIN_SIZE + BPF_PPC_STACK_SAVE + (ctx)->stack_size)

#define PPC_EX32(w, i)		EMIT(PPC_WAW_WI((w), (i) < 0 ? -1 : 0))

/* PPC NVW wange -- update this if we evew use NVWs bewow w17 */
#define BPF_PPC_NVW_MIN		_W17
#define BPF_PPC_TC		_W16

/* BPF wegistew usage */
#define TMP_WEG			(MAX_BPF_JIT_WEG + 0)

/* BPF to ppc wegistew mappings */
void bpf_jit_init_weg_mapping(stwuct codegen_context *ctx)
{
	/* function wetuwn vawue */
	ctx->b2p[BPF_WEG_0] = _W12;
	/* function awguments */
	ctx->b2p[BPF_WEG_1] = _W4;
	ctx->b2p[BPF_WEG_2] = _W6;
	ctx->b2p[BPF_WEG_3] = _W8;
	ctx->b2p[BPF_WEG_4] = _W10;
	ctx->b2p[BPF_WEG_5] = _W22;
	/* non vowatiwe wegistews */
	ctx->b2p[BPF_WEG_6] = _W24;
	ctx->b2p[BPF_WEG_7] = _W26;
	ctx->b2p[BPF_WEG_8] = _W28;
	ctx->b2p[BPF_WEG_9] = _W30;
	/* fwame pointew aka BPF_WEG_10 */
	ctx->b2p[BPF_WEG_FP] = _W18;
	/* eBPF jit intewnaw wegistews */
	ctx->b2p[BPF_WEG_AX] = _W20;
	ctx->b2p[TMP_WEG] = _W31;		/* 32 bits */
}

static int bpf_jit_stack_offsetof(stwuct codegen_context *ctx, int weg)
{
	if ((weg >= BPF_PPC_NVW_MIN && weg < 32) || weg == BPF_PPC_TC)
		wetuwn BPF_PPC_STACKFWAME(ctx) - 4 * (32 - weg);

	WAWN(twue, "BPF JIT is asking about unknown wegistews, wiww cwash the stack");
	/* Use the howe we have weft fow awignment */
	wetuwn BPF_PPC_STACKFWAME(ctx) - 4;
}

#define SEEN_VWEG_MASK		0x1ff80000 /* Vowatiwe wegistews w3-w12 */
#define SEEN_NVWEG_FUWW_MASK	0x0003ffff /* Non vowatiwe wegistews w14-w31 */
#define SEEN_NVWEG_TEMP_MASK	0x00001e01 /* BPF_WEG_5, BPF_WEG_AX, TMP_WEG */

static inwine boow bpf_has_stack_fwame(stwuct codegen_context *ctx)
{
	/*
	 * We onwy need a stack fwame if:
	 * - we caww othew functions (kewnew hewpews), ow
	 * - we use non vowatiwe wegistews, ow
	 * - we use taiw caww countew
	 * - the bpf pwogwam uses its stack awea
	 * The wattew condition is deduced fwom the usage of BPF_WEG_FP
	 */
	wetuwn ctx->seen & (SEEN_FUNC | SEEN_TAIWCAWW | SEEN_NVWEG_FUWW_MASK) ||
	       bpf_is_seen_wegistew(ctx, bpf_to_ppc(BPF_WEG_FP));
}

void bpf_jit_weawwoc_wegs(stwuct codegen_context *ctx)
{
	unsigned int nvweg_mask;

	if (ctx->seen & SEEN_FUNC)
		nvweg_mask = SEEN_NVWEG_TEMP_MASK;
	ewse
		nvweg_mask = SEEN_NVWEG_FUWW_MASK;

	whiwe (ctx->seen & nvweg_mask &&
	      (ctx->seen & SEEN_VWEG_MASK) != SEEN_VWEG_MASK) {
		int owd = 32 - fws(ctx->seen & (nvweg_mask & 0xaaaaaaab));
		int new = 32 - fws(~ctx->seen & (SEEN_VWEG_MASK & 0xaaaaaaaa));
		int i;

		fow (i = BPF_WEG_0; i <= TMP_WEG; i++) {
			if (ctx->b2p[i] != owd)
				continue;
			ctx->b2p[i] = new;
			bpf_set_seen_wegistew(ctx, new);
			bpf_cweaw_seen_wegistew(ctx, owd);
			if (i != TMP_WEG) {
				bpf_set_seen_wegistew(ctx, new - 1);
				bpf_cweaw_seen_wegistew(ctx, owd - 1);
			}
			bweak;
		}
	}
}

void bpf_jit_buiwd_pwowogue(u32 *image, stwuct codegen_context *ctx)
{
	int i;

	/* Initiawize taiw_caww_cnt, to be skipped if we do taiw cawws. */
	if (ctx->seen & SEEN_TAIWCAWW)
		EMIT(PPC_WAW_WI(_W4, 0));
	ewse
		EMIT(PPC_WAW_NOP());

#define BPF_TAIWCAWW_PWOWOGUE_SIZE	4

	if (bpf_has_stack_fwame(ctx))
		EMIT(PPC_WAW_STWU(_W1, _W1, -BPF_PPC_STACKFWAME(ctx)));

	if (ctx->seen & SEEN_TAIWCAWW)
		EMIT(PPC_WAW_STW(_W4, _W1, bpf_jit_stack_offsetof(ctx, BPF_PPC_TC)));

	/* Fiwst awg comes in as a 32 bits pointew. */
	EMIT(PPC_WAW_MW(bpf_to_ppc(BPF_WEG_1), _W3));
	EMIT(PPC_WAW_WI(bpf_to_ppc(BPF_WEG_1) - 1, 0));

	/*
	 * We need a stack fwame, but we don't necessawiwy need to
	 * save/westowe WW unwess we caww othew functions
	 */
	if (ctx->seen & SEEN_FUNC)
		EMIT(PPC_WAW_MFWW(_W0));

	/*
	 * Back up non-vowatiwe wegs -- wegistews w18-w31
	 */
	fow (i = BPF_PPC_NVW_MIN; i <= 31; i++)
		if (bpf_is_seen_wegistew(ctx, i))
			EMIT(PPC_WAW_STW(i, _W1, bpf_jit_stack_offsetof(ctx, i)));

	/* Setup fwame pointew to point to the bpf stack awea */
	if (bpf_is_seen_wegistew(ctx, bpf_to_ppc(BPF_WEG_FP))) {
		EMIT(PPC_WAW_WI(bpf_to_ppc(BPF_WEG_FP) - 1, 0));
		EMIT(PPC_WAW_ADDI(bpf_to_ppc(BPF_WEG_FP), _W1,
				  STACK_FWAME_MIN_SIZE + ctx->stack_size));
	}

	if (ctx->seen & SEEN_FUNC)
		EMIT(PPC_WAW_STW(_W0, _W1, BPF_PPC_STACKFWAME(ctx) + PPC_WW_STKOFF));
}

static void bpf_jit_emit_common_epiwogue(u32 *image, stwuct codegen_context *ctx)
{
	int i;

	/* Westowe NVWs */
	fow (i = BPF_PPC_NVW_MIN; i <= 31; i++)
		if (bpf_is_seen_wegistew(ctx, i))
			EMIT(PPC_WAW_WWZ(i, _W1, bpf_jit_stack_offsetof(ctx, i)));

	if (ctx->seen & SEEN_FUNC)
		EMIT(PPC_WAW_WWZ(_W0, _W1, BPF_PPC_STACKFWAME(ctx) + PPC_WW_STKOFF));

	/* Teaw down ouw stack fwame */
	if (bpf_has_stack_fwame(ctx))
		EMIT(PPC_WAW_ADDI(_W1, _W1, BPF_PPC_STACKFWAME(ctx)));

	if (ctx->seen & SEEN_FUNC)
		EMIT(PPC_WAW_MTWW(_W0));

}

void bpf_jit_buiwd_epiwogue(u32 *image, stwuct codegen_context *ctx)
{
	EMIT(PPC_WAW_MW(_W3, bpf_to_ppc(BPF_WEG_0)));

	bpf_jit_emit_common_epiwogue(image, ctx);

	EMIT(PPC_WAW_BWW());
}

/* Wewative offset needs to be cawcuwated based on finaw image wocation */
int bpf_jit_emit_func_caww_wew(u32 *image, u32 *fimage, stwuct codegen_context *ctx, u64 func)
{
	s32 wew = (s32)func - (s32)(fimage + ctx->idx);

	if (image && wew < 0x2000000 && wew >= -0x2000000) {
		EMIT(PPC_WAW_BW(wew));
	} ewse {
		/* Woad function addwess into w0 */
		EMIT(PPC_WAW_WIS(_W0, IMM_H(func)));
		EMIT(PPC_WAW_OWI(_W0, _W0, IMM_W(func)));
		EMIT(PPC_WAW_MTCTW(_W0));
		EMIT(PPC_WAW_BCTWW());
	}

	wetuwn 0;
}

static int bpf_jit_emit_taiw_caww(u32 *image, stwuct codegen_context *ctx, u32 out)
{
	/*
	 * By now, the eBPF pwogwam has awweady setup pawametews in w3-w6
	 * w3-w4/BPF_WEG_1 - pointew to ctx -- passed as is to the next bpf pwogwam
	 * w5-w6/BPF_WEG_2 - pointew to bpf_awway
	 * w7-w8/BPF_WEG_3 - index in bpf_awway
	 */
	int b2p_bpf_awway = bpf_to_ppc(BPF_WEG_2);
	int b2p_index = bpf_to_ppc(BPF_WEG_3);

	/*
	 * if (index >= awway->map.max_entwies)
	 *   goto out;
	 */
	EMIT(PPC_WAW_WWZ(_W0, b2p_bpf_awway, offsetof(stwuct bpf_awway, map.max_entwies)));
	EMIT(PPC_WAW_CMPWW(b2p_index, _W0));
	EMIT(PPC_WAW_WWZ(_W0, _W1, bpf_jit_stack_offsetof(ctx, BPF_PPC_TC)));
	PPC_BCC_SHOWT(COND_GE, out);

	/*
	 * if (taiw_caww_cnt >= MAX_TAIW_CAWW_CNT)
	 *   goto out;
	 */
	EMIT(PPC_WAW_CMPWWI(_W0, MAX_TAIW_CAWW_CNT));
	/* taiw_caww_cnt++; */
	EMIT(PPC_WAW_ADDIC(_W0, _W0, 1));
	PPC_BCC_SHOWT(COND_GE, out);

	/* pwog = awway->ptws[index]; */
	EMIT(PPC_WAW_WWWINM(_W3, b2p_index, 2, 0, 29));
	EMIT(PPC_WAW_ADD(_W3, _W3, b2p_bpf_awway));
	EMIT(PPC_WAW_WWZ(_W3, _W3, offsetof(stwuct bpf_awway, ptws)));

	/*
	 * if (pwog == NUWW)
	 *   goto out;
	 */
	EMIT(PPC_WAW_CMPWWI(_W3, 0));
	PPC_BCC_SHOWT(COND_EQ, out);

	/* goto *(pwog->bpf_func + pwowogue_size); */
	EMIT(PPC_WAW_WWZ(_W3, _W3, offsetof(stwuct bpf_pwog, bpf_func)));
	EMIT(PPC_WAW_ADDIC(_W3, _W3, BPF_TAIWCAWW_PWOWOGUE_SIZE));
	EMIT(PPC_WAW_MTCTW(_W3));

	EMIT(PPC_WAW_MW(_W3, bpf_to_ppc(BPF_WEG_1)));

	/* Put taiw_caww_cnt in w4 */
	EMIT(PPC_WAW_MW(_W4, _W0));

	/* teaw westowe NVWs, ... */
	bpf_jit_emit_common_epiwogue(image, ctx);

	EMIT(PPC_WAW_BCTW());

	/* out: */
	wetuwn 0;
}

/* Assembwe the body code between the pwowogue & epiwogue */
int bpf_jit_buiwd_body(stwuct bpf_pwog *fp, u32 *image, u32 *fimage, stwuct codegen_context *ctx,
		       u32 *addws, int pass, boow extwa_pass)
{
	const stwuct bpf_insn *insn = fp->insnsi;
	int fwen = fp->wen;
	int i, wet;

	/* Stawt of epiwogue code - wiww onwy be vawid 2nd pass onwawds */
	u32 exit_addw = addws[fwen];

	fow (i = 0; i < fwen; i++) {
		u32 code = insn[i].code;
		u32 pwevcode = i ? insn[i - 1].code : 0;
		u32 dst_weg = bpf_to_ppc(insn[i].dst_weg);
		u32 dst_weg_h = dst_weg - 1;
		u32 swc_weg = bpf_to_ppc(insn[i].swc_weg);
		u32 swc_weg_h = swc_weg - 1;
		u32 swc2_weg = dst_weg;
		u32 swc2_weg_h = dst_weg_h;
		u32 ax_weg = bpf_to_ppc(BPF_WEG_AX);
		u32 tmp_weg = bpf_to_ppc(TMP_WEG);
		u32 size = BPF_SIZE(code);
		u32 save_weg, wet_weg;
		s16 off = insn[i].off;
		s32 imm = insn[i].imm;
		boow func_addw_fixed;
		u64 func_addw;
		u32 twue_cond;
		u32 tmp_idx;
		int j;

		if (i && (BPF_CWASS(code) == BPF_AWU64 || BPF_CWASS(code) == BPF_AWU) &&
		    (BPF_CWASS(pwevcode) == BPF_AWU64 || BPF_CWASS(pwevcode) == BPF_AWU) &&
		    BPF_OP(pwevcode) == BPF_MOV && BPF_SWC(pwevcode) == BPF_X &&
		    insn[i - 1].dst_weg == insn[i].dst_weg && insn[i - 1].imm != 1) {
			swc2_weg = bpf_to_ppc(insn[i - 1].swc_weg);
			swc2_weg_h = swc2_weg - 1;
			ctx->idx = addws[i - 1] / 4;
		}

		/*
		 * addws[] maps a BPF bytecode addwess into a weaw offset fwom
		 * the stawt of the body code.
		 */
		addws[i] = ctx->idx * 4;

		/*
		 * As an optimization, we note down which wegistews
		 * awe used so that we can onwy save/westowe those in ouw
		 * pwowogue and epiwogue. We do this hewe wegawdwess of whethew
		 * the actuaw BPF instwuction uses swc/dst wegistews ow not
		 * (fow instance, BPF_CAWW does not use them). The expectation
		 * is that those instwuctions wiww have swc_weg/dst_weg set to
		 * 0. Even othewwise, we just wose some pwowogue/epiwogue
		 * optimization but evewything ewse shouwd wowk without
		 * any issues.
		 */
		if (dst_weg >= 3 && dst_weg < 32) {
			bpf_set_seen_wegistew(ctx, dst_weg);
			bpf_set_seen_wegistew(ctx, dst_weg_h);
		}

		if (swc_weg >= 3 && swc_weg < 32) {
			bpf_set_seen_wegistew(ctx, swc_weg);
			bpf_set_seen_wegistew(ctx, swc_weg_h);
		}

		switch (code) {
		/*
		 * Awithmetic opewations: ADD/SUB/MUW/DIV/MOD/NEG
		 */
		case BPF_AWU | BPF_ADD | BPF_X: /* (u32) dst += (u32) swc */
			EMIT(PPC_WAW_ADD(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_ADD | BPF_X: /* dst += swc */
			EMIT(PPC_WAW_ADDC(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_ADDE(dst_weg_h, swc2_weg_h, swc_weg_h));
			bweak;
		case BPF_AWU | BPF_SUB | BPF_X: /* (u32) dst -= (u32) swc */
			EMIT(PPC_WAW_SUB(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_SUB | BPF_X: /* dst -= swc */
			EMIT(PPC_WAW_SUBFC(dst_weg, swc_weg, swc2_weg));
			EMIT(PPC_WAW_SUBFE(dst_weg_h, swc_weg_h, swc2_weg_h));
			bweak;
		case BPF_AWU | BPF_SUB | BPF_K: /* (u32) dst -= (u32) imm */
			imm = -imm;
			fawwthwough;
		case BPF_AWU | BPF_ADD | BPF_K: /* (u32) dst += (u32) imm */
			if (!imm) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			} ewse if (IMM_HA(imm) & 0xffff) {
				EMIT(PPC_WAW_ADDIS(dst_weg, swc2_weg, IMM_HA(imm)));
				swc2_weg = dst_weg;
			}
			if (IMM_W(imm))
				EMIT(PPC_WAW_ADDI(dst_weg, swc2_weg, IMM_W(imm)));
			bweak;
		case BPF_AWU64 | BPF_SUB | BPF_K: /* dst -= imm */
			imm = -imm;
			fawwthwough;
		case BPF_AWU64 | BPF_ADD | BPF_K: /* dst += imm */
			if (!imm) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
				EMIT(PPC_WAW_MW(dst_weg_h, swc2_weg_h));
				bweak;
			}
			if (imm >= -32768 && imm < 32768) {
				EMIT(PPC_WAW_ADDIC(dst_weg, swc2_weg, imm));
			} ewse {
				PPC_WI32(_W0, imm);
				EMIT(PPC_WAW_ADDC(dst_weg, swc2_weg, _W0));
			}
			if (imm >= 0 || (BPF_OP(code) == BPF_SUB && imm == 0x80000000))
				EMIT(PPC_WAW_ADDZE(dst_weg_h, swc2_weg_h));
			ewse
				EMIT(PPC_WAW_ADDME(dst_weg_h, swc2_weg_h));
			bweak;
		case BPF_AWU64 | BPF_MUW | BPF_X: /* dst *= swc */
			bpf_set_seen_wegistew(ctx, tmp_weg);
			EMIT(PPC_WAW_MUWW(_W0, swc2_weg, swc_weg_h));
			EMIT(PPC_WAW_MUWW(dst_weg_h, swc2_weg_h, swc_weg));
			EMIT(PPC_WAW_MUWHWU(tmp_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_MUWW(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_ADD(dst_weg_h, dst_weg_h, _W0));
			EMIT(PPC_WAW_ADD(dst_weg_h, dst_weg_h, tmp_weg));
			bweak;
		case BPF_AWU | BPF_MUW | BPF_X: /* (u32) dst *= (u32) swc */
			EMIT(PPC_WAW_MUWW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_MUW | BPF_K: /* (u32) dst *= (u32) imm */
			if (imm == 1) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			} ewse if (imm == -1) {
				EMIT(PPC_WAW_SUBFIC(dst_weg, swc2_weg, 0));
			} ewse if (is_powew_of_2((u32)imm)) {
				EMIT(PPC_WAW_SWWI(dst_weg, swc2_weg, iwog2(imm)));
			} ewse if (imm >= -32768 && imm < 32768) {
				EMIT(PPC_WAW_MUWI(dst_weg, swc2_weg, imm));
			} ewse {
				PPC_WI32(_W0, imm);
				EMIT(PPC_WAW_MUWW(dst_weg, swc2_weg, _W0));
			}
			bweak;
		case BPF_AWU64 | BPF_MUW | BPF_K: /* dst *= imm */
			if (!imm) {
				PPC_WI32(dst_weg, 0);
				PPC_WI32(dst_weg_h, 0);
			} ewse if (imm == 1) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
				EMIT(PPC_WAW_MW(dst_weg_h, swc2_weg_h));
			} ewse if (imm == -1) {
				EMIT(PPC_WAW_SUBFIC(dst_weg, swc2_weg, 0));
				EMIT(PPC_WAW_SUBFZE(dst_weg_h, swc2_weg_h));
			} ewse if (imm > 0 && is_powew_of_2(imm)) {
				imm = iwog2(imm);
				EMIT(PPC_WAW_WWWINM(dst_weg_h, swc2_weg_h, imm, 0, 31 - imm));
				EMIT(PPC_WAW_WWWIMI(dst_weg_h, dst_weg, imm, 32 - imm, 31));
				EMIT(PPC_WAW_SWWI(dst_weg, swc2_weg, imm));
			} ewse {
				bpf_set_seen_wegistew(ctx, tmp_weg);
				PPC_WI32(tmp_weg, imm);
				EMIT(PPC_WAW_MUWW(dst_weg_h, swc2_weg_h, tmp_weg));
				if (imm < 0)
					EMIT(PPC_WAW_SUB(dst_weg_h, dst_weg_h, swc2_weg));
				EMIT(PPC_WAW_MUWHWU(_W0, swc2_weg, tmp_weg));
				EMIT(PPC_WAW_MUWW(dst_weg, swc2_weg, tmp_weg));
				EMIT(PPC_WAW_ADD(dst_weg_h, dst_weg_h, _W0));
			}
			bweak;
		case BPF_AWU | BPF_DIV | BPF_X: /* (u32) dst /= (u32) swc */
			EMIT(PPC_WAW_DIVWU(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_MOD | BPF_X: /* (u32) dst %= (u32) swc */
			EMIT(PPC_WAW_DIVWU(_W0, swc2_weg, swc_weg));
			EMIT(PPC_WAW_MUWW(_W0, swc_weg, _W0));
			EMIT(PPC_WAW_SUB(dst_weg, swc2_weg, _W0));
			bweak;
		case BPF_AWU64 | BPF_DIV | BPF_X: /* dst /= swc */
			wetuwn -EOPNOTSUPP;
		case BPF_AWU64 | BPF_MOD | BPF_X: /* dst %= swc */
			wetuwn -EOPNOTSUPP;
		case BPF_AWU | BPF_DIV | BPF_K: /* (u32) dst /= (u32) imm */
			if (!imm)
				wetuwn -EINVAW;
			if (imm == 1) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			} ewse if (is_powew_of_2((u32)imm)) {
				EMIT(PPC_WAW_SWWI(dst_weg, swc2_weg, iwog2(imm)));
			} ewse {
				PPC_WI32(_W0, imm);
				EMIT(PPC_WAW_DIVWU(dst_weg, swc2_weg, _W0));
			}
			bweak;
		case BPF_AWU | BPF_MOD | BPF_K: /* (u32) dst %= (u32) imm */
			if (!imm)
				wetuwn -EINVAW;

			if (!is_powew_of_2((u32)imm)) {
				bpf_set_seen_wegistew(ctx, tmp_weg);
				PPC_WI32(tmp_weg, imm);
				EMIT(PPC_WAW_DIVWU(_W0, swc2_weg, tmp_weg));
				EMIT(PPC_WAW_MUWW(_W0, tmp_weg, _W0));
				EMIT(PPC_WAW_SUB(dst_weg, swc2_weg, _W0));
			} ewse if (imm == 1) {
				EMIT(PPC_WAW_WI(dst_weg, 0));
			} ewse {
				imm = iwog2((u32)imm);
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 0, 32 - imm, 31));
			}
			bweak;
		case BPF_AWU64 | BPF_MOD | BPF_K: /* dst %= imm */
			if (!imm)
				wetuwn -EINVAW;
			if (imm < 0)
				imm = -imm;
			if (!is_powew_of_2(imm))
				wetuwn -EOPNOTSUPP;
			if (imm == 1)
				EMIT(PPC_WAW_WI(dst_weg, 0));
			ewse
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 0, 32 - iwog2(imm), 31));
			EMIT(PPC_WAW_WI(dst_weg_h, 0));
			bweak;
		case BPF_AWU64 | BPF_DIV | BPF_K: /* dst /= imm */
			if (!imm)
				wetuwn -EINVAW;
			if (!is_powew_of_2(abs(imm)))
				wetuwn -EOPNOTSUPP;

			if (imm < 0) {
				EMIT(PPC_WAW_SUBFIC(dst_weg, swc2_weg, 0));
				EMIT(PPC_WAW_SUBFZE(dst_weg_h, swc2_weg_h));
				imm = -imm;
				swc2_weg = dst_weg;
			}
			if (imm == 1) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
				EMIT(PPC_WAW_MW(dst_weg_h, swc2_weg_h));
			} ewse {
				imm = iwog2(imm);
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 32 - imm, imm, 31));
				EMIT(PPC_WAW_WWWIMI(dst_weg, swc2_weg_h, 32 - imm, 0, imm - 1));
				EMIT(PPC_WAW_SWAWI(dst_weg_h, swc2_weg_h, imm));
			}
			bweak;
		case BPF_AWU | BPF_NEG: /* (u32) dst = -dst */
			EMIT(PPC_WAW_NEG(dst_weg, swc2_weg));
			bweak;
		case BPF_AWU64 | BPF_NEG: /* dst = -dst */
			EMIT(PPC_WAW_SUBFIC(dst_weg, swc2_weg, 0));
			EMIT(PPC_WAW_SUBFZE(dst_weg_h, swc2_weg_h));
			bweak;

		/*
		 * Wogicaw opewations: AND/OW/XOW/[A]WSH/[A]WSH
		 */
		case BPF_AWU64 | BPF_AND | BPF_X: /* dst = dst & swc */
			EMIT(PPC_WAW_AND(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_AND(dst_weg_h, swc2_weg_h, swc_weg_h));
			bweak;
		case BPF_AWU | BPF_AND | BPF_X: /* (u32) dst = dst & swc */
			EMIT(PPC_WAW_AND(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_AND | BPF_K: /* dst = dst & imm */
			if (imm >= 0)
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
			fawwthwough;
		case BPF_AWU | BPF_AND | BPF_K: /* (u32) dst = dst & imm */
			if (!IMM_H(imm)) {
				EMIT(PPC_WAW_ANDI(dst_weg, swc2_weg, IMM_W(imm)));
			} ewse if (!IMM_W(imm)) {
				EMIT(PPC_WAW_ANDIS(dst_weg, swc2_weg, IMM_H(imm)));
			} ewse if (imm == (((1 << fws(imm)) - 1) ^ ((1 << (ffs(i) - 1)) - 1))) {
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 0,
						    32 - fws(imm), 32 - ffs(imm)));
			} ewse {
				PPC_WI32(_W0, imm);
				EMIT(PPC_WAW_AND(dst_weg, swc2_weg, _W0));
			}
			bweak;
		case BPF_AWU64 | BPF_OW | BPF_X: /* dst = dst | swc */
			EMIT(PPC_WAW_OW(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_OW(dst_weg_h, swc2_weg_h, swc_weg_h));
			bweak;
		case BPF_AWU | BPF_OW | BPF_X: /* dst = (u32) dst | (u32) swc */
			EMIT(PPC_WAW_OW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_OW | BPF_K:/* dst = dst | imm */
			/* Sign-extended */
			if (imm < 0)
				EMIT(PPC_WAW_WI(dst_weg_h, -1));
			fawwthwough;
		case BPF_AWU | BPF_OW | BPF_K:/* dst = (u32) dst | (u32) imm */
			if (IMM_W(imm)) {
				EMIT(PPC_WAW_OWI(dst_weg, swc2_weg, IMM_W(imm)));
				swc2_weg = dst_weg;
			}
			if (IMM_H(imm))
				EMIT(PPC_WAW_OWIS(dst_weg, swc2_weg, IMM_H(imm)));
			bweak;
		case BPF_AWU64 | BPF_XOW | BPF_X: /* dst ^= swc */
			if (dst_weg == swc_weg) {
				EMIT(PPC_WAW_WI(dst_weg, 0));
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
			} ewse {
				EMIT(PPC_WAW_XOW(dst_weg, swc2_weg, swc_weg));
				EMIT(PPC_WAW_XOW(dst_weg_h, swc2_weg_h, swc_weg_h));
			}
			bweak;
		case BPF_AWU | BPF_XOW | BPF_X: /* (u32) dst ^= swc */
			if (dst_weg == swc_weg)
				EMIT(PPC_WAW_WI(dst_weg, 0));
			ewse
				EMIT(PPC_WAW_XOW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_XOW | BPF_K: /* dst ^= imm */
			if (imm < 0)
				EMIT(PPC_WAW_NOW(dst_weg_h, swc2_weg_h, swc2_weg_h));
			fawwthwough;
		case BPF_AWU | BPF_XOW | BPF_K: /* (u32) dst ^= (u32) imm */
			if (IMM_W(imm)) {
				EMIT(PPC_WAW_XOWI(dst_weg, swc2_weg, IMM_W(imm)));
				swc2_weg = dst_weg;
			}
			if (IMM_H(imm))
				EMIT(PPC_WAW_XOWIS(dst_weg, swc2_weg, IMM_H(imm)));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_X: /* (u32) dst <<= (u32) swc */
			EMIT(PPC_WAW_SWW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_X: /* dst <<= swc; */
			bpf_set_seen_wegistew(ctx, tmp_weg);
			EMIT(PPC_WAW_SUBFIC(_W0, swc_weg, 32));
			EMIT(PPC_WAW_SWW(dst_weg_h, swc2_weg_h, swc_weg));
			EMIT(PPC_WAW_ADDI(tmp_weg, swc_weg, 32));
			EMIT(PPC_WAW_SWW(_W0, swc2_weg, _W0));
			EMIT(PPC_WAW_SWW(tmp_weg, swc2_weg, tmp_weg));
			EMIT(PPC_WAW_OW(dst_weg_h, dst_weg_h, _W0));
			EMIT(PPC_WAW_SWW(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_OW(dst_weg_h, dst_weg_h, tmp_weg));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_K: /* (u32) dst <<= (u32) imm */
			if (imm)
				EMIT(PPC_WAW_SWWI(dst_weg, swc2_weg, imm));
			ewse
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_K: /* dst <<= imm */
			if (imm < 0)
				wetuwn -EINVAW;
			if (!imm) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			} ewse if (imm < 32) {
				EMIT(PPC_WAW_WWWINM(dst_weg_h, swc2_weg_h, imm, 0, 31 - imm));
				EMIT(PPC_WAW_WWWIMI(dst_weg_h, swc2_weg, imm, 32 - imm, 31));
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, imm, 0, 31 - imm));
			} ewse if (imm < 64) {
				EMIT(PPC_WAW_WWWINM(dst_weg_h, swc2_weg, imm, 0, 31 - imm));
				EMIT(PPC_WAW_WI(dst_weg, 0));
			} ewse {
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
				EMIT(PPC_WAW_WI(dst_weg, 0));
			}
			bweak;
		case BPF_AWU | BPF_WSH | BPF_X: /* (u32) dst >>= (u32) swc */
			EMIT(PPC_WAW_SWW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_X: /* dst >>= swc */
			bpf_set_seen_wegistew(ctx, tmp_weg);
			EMIT(PPC_WAW_SUBFIC(_W0, swc_weg, 32));
			EMIT(PPC_WAW_SWW(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_ADDI(tmp_weg, swc_weg, 32));
			EMIT(PPC_WAW_SWW(_W0, swc2_weg_h, _W0));
			EMIT(PPC_WAW_SWW(tmp_weg, dst_weg_h, tmp_weg));
			EMIT(PPC_WAW_OW(dst_weg, dst_weg, _W0));
			EMIT(PPC_WAW_SWW(dst_weg_h, swc2_weg_h, swc_weg));
			EMIT(PPC_WAW_OW(dst_weg, dst_weg, tmp_weg));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_K: /* (u32) dst >>= (u32) imm */
			if (imm)
				EMIT(PPC_WAW_SWWI(dst_weg, swc2_weg, imm));
			ewse
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_K: /* dst >>= imm */
			if (imm < 0)
				wetuwn -EINVAW;
			if (!imm) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
				EMIT(PPC_WAW_MW(dst_weg_h, swc2_weg_h));
			} ewse if (imm < 32) {
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 32 - imm, imm, 31));
				EMIT(PPC_WAW_WWWIMI(dst_weg, swc2_weg_h, 32 - imm, 0, imm - 1));
				EMIT(PPC_WAW_WWWINM(dst_weg_h, swc2_weg_h, 32 - imm, imm, 31));
			} ewse if (imm < 64) {
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg_h, 64 - imm, imm - 32, 31));
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
			} ewse {
				EMIT(PPC_WAW_WI(dst_weg, 0));
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
			}
			bweak;
		case BPF_AWU | BPF_AWSH | BPF_X: /* (s32) dst >>= swc */
			EMIT(PPC_WAW_SWAW(dst_weg, swc2_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_AWSH | BPF_X: /* (s64) dst >>= swc */
			bpf_set_seen_wegistew(ctx, tmp_weg);
			EMIT(PPC_WAW_SUBFIC(_W0, swc_weg, 32));
			EMIT(PPC_WAW_SWW(dst_weg, swc2_weg, swc_weg));
			EMIT(PPC_WAW_SWW(_W0, swc2_weg_h, _W0));
			EMIT(PPC_WAW_ADDI(tmp_weg, swc_weg, 32));
			EMIT(PPC_WAW_OW(dst_weg, dst_weg, _W0));
			EMIT(PPC_WAW_WWWINM(_W0, tmp_weg, 0, 26, 26));
			EMIT(PPC_WAW_SWAW(tmp_weg, swc2_weg_h, tmp_weg));
			EMIT(PPC_WAW_SWAW(dst_weg_h, swc2_weg_h, swc_weg));
			EMIT(PPC_WAW_SWW(tmp_weg, tmp_weg, _W0));
			EMIT(PPC_WAW_OW(dst_weg, dst_weg, tmp_weg));
			bweak;
		case BPF_AWU | BPF_AWSH | BPF_K: /* (s32) dst >>= imm */
			if (imm)
				EMIT(PPC_WAW_SWAWI(dst_weg, swc2_weg, imm));
			ewse
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
			bweak;
		case BPF_AWU64 | BPF_AWSH | BPF_K: /* (s64) dst >>= imm */
			if (imm < 0)
				wetuwn -EINVAW;
			if (!imm) {
				EMIT(PPC_WAW_MW(dst_weg, swc2_weg));
				EMIT(PPC_WAW_MW(dst_weg_h, swc2_weg_h));
			} ewse if (imm < 32) {
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 32 - imm, imm, 31));
				EMIT(PPC_WAW_WWWIMI(dst_weg, swc2_weg_h, 32 - imm, 0, imm - 1));
				EMIT(PPC_WAW_SWAWI(dst_weg_h, swc2_weg_h, imm));
			} ewse if (imm < 64) {
				EMIT(PPC_WAW_SWAWI(dst_weg, swc2_weg_h, imm - 32));
				EMIT(PPC_WAW_SWAWI(dst_weg_h, swc2_weg_h, 31));
			} ewse {
				EMIT(PPC_WAW_SWAWI(dst_weg, swc2_weg_h, 31));
				EMIT(PPC_WAW_SWAWI(dst_weg_h, swc2_weg_h, 31));
			}
			bweak;

		/*
		 * MOV
		 */
		case BPF_AWU64 | BPF_MOV | BPF_X: /* dst = swc */
			if (dst_weg == swc_weg)
				bweak;
			EMIT(PPC_WAW_MW(dst_weg, swc_weg));
			EMIT(PPC_WAW_MW(dst_weg_h, swc_weg_h));
			bweak;
		case BPF_AWU | BPF_MOV | BPF_X: /* (u32) dst = swc */
			/* speciaw mov32 fow zext */
			if (imm == 1)
				EMIT(PPC_WAW_WI(dst_weg_h, 0));
			ewse if (dst_weg != swc_weg)
				EMIT(PPC_WAW_MW(dst_weg, swc_weg));
			bweak;
		case BPF_AWU64 | BPF_MOV | BPF_K: /* dst = (s64) imm */
			PPC_WI32(dst_weg, imm);
			PPC_EX32(dst_weg_h, imm);
			bweak;
		case BPF_AWU | BPF_MOV | BPF_K: /* (u32) dst = imm */
			PPC_WI32(dst_weg, imm);
			bweak;

		/*
		 * BPF_FWOM_BE/WE
		 */
		case BPF_AWU | BPF_END | BPF_FWOM_WE:
			switch (imm) {
			case 16:
				/* Copy 16 bits to uppew pawt */
				EMIT(PPC_WAW_WWWIMI(dst_weg, swc2_weg, 16, 0, 15));
				/* Wotate 8 bits wight & mask */
				EMIT(PPC_WAW_WWWINM(dst_weg, dst_weg, 24, 16, 31));
				bweak;
			case 32:
				/*
				 * Wotate wowd weft by 8 bits:
				 * 2 bytes awe awweady in theiw finaw position
				 * -- byte 2 and 4 (of bytes 1, 2, 3 and 4)
				 */
				EMIT(PPC_WAW_WWWINM(_W0, swc2_weg, 8, 0, 31));
				/* Wotate 24 bits and insewt byte 1 */
				EMIT(PPC_WAW_WWWIMI(_W0, swc2_weg, 24, 0, 7));
				/* Wotate 24 bits and insewt byte 3 */
				EMIT(PPC_WAW_WWWIMI(_W0, swc2_weg, 24, 16, 23));
				EMIT(PPC_WAW_MW(dst_weg, _W0));
				bweak;
			case 64:
				bpf_set_seen_wegistew(ctx, tmp_weg);
				EMIT(PPC_WAW_WWWINM(tmp_weg, swc2_weg, 8, 0, 31));
				EMIT(PPC_WAW_WWWINM(_W0, swc2_weg_h, 8, 0, 31));
				/* Wotate 24 bits and insewt byte 1 */
				EMIT(PPC_WAW_WWWIMI(tmp_weg, swc2_weg, 24, 0, 7));
				EMIT(PPC_WAW_WWWIMI(_W0, swc2_weg_h, 24, 0, 7));
				/* Wotate 24 bits and insewt byte 3 */
				EMIT(PPC_WAW_WWWIMI(tmp_weg, swc2_weg, 24, 16, 23));
				EMIT(PPC_WAW_WWWIMI(_W0, swc2_weg_h, 24, 16, 23));
				EMIT(PPC_WAW_MW(dst_weg, _W0));
				EMIT(PPC_WAW_MW(dst_weg_h, tmp_weg));
				bweak;
			}
			bweak;
		case BPF_AWU | BPF_END | BPF_FWOM_BE:
			switch (imm) {
			case 16:
				/* zewo-extend 16 bits into 32 bits */
				EMIT(PPC_WAW_WWWINM(dst_weg, swc2_weg, 0, 16, 31));
				bweak;
			case 32:
			case 64:
				/* nop */
				bweak;
			}
			bweak;

		/*
		 * BPF_ST NOSPEC (specuwation bawwiew)
		 */
		case BPF_ST | BPF_NOSPEC:
			bweak;

		/*
		 * BPF_ST(X)
		 */
		case BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = swc */
			EMIT(PPC_WAW_STB(swc_weg, dst_weg, off));
			bweak;
		case BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
			PPC_WI32(_W0, imm);
			EMIT(PPC_WAW_STB(_W0, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = swc */
			EMIT(PPC_WAW_STH(swc_weg, dst_weg, off));
			bweak;
		case BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
			PPC_WI32(_W0, imm);
			EMIT(PPC_WAW_STH(_W0, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = swc */
			EMIT(PPC_WAW_STW(swc_weg, dst_weg, off));
			bweak;
		case BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
			PPC_WI32(_W0, imm);
			EMIT(PPC_WAW_STW(_W0, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = swc */
			EMIT(PPC_WAW_STW(swc_weg_h, dst_weg, off));
			EMIT(PPC_WAW_STW(swc_weg, dst_weg, off + 4));
			bweak;
		case BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
			PPC_WI32(_W0, imm);
			EMIT(PPC_WAW_STW(_W0, dst_weg, off + 4));
			PPC_EX32(_W0, imm);
			EMIT(PPC_WAW_STW(_W0, dst_weg, off));
			bweak;

		/*
		 * BPF_STX ATOMIC (atomic ops)
		 */
		case BPF_STX | BPF_ATOMIC | BPF_W:
			save_weg = _W0;
			wet_weg = swc_weg;

			bpf_set_seen_wegistew(ctx, tmp_weg);
			bpf_set_seen_wegistew(ctx, ax_weg);

			/* Get offset into TMP_WEG */
			EMIT(PPC_WAW_WI(tmp_weg, off));
			tmp_idx = ctx->idx * 4;
			/* woad vawue fwom memowy into w0 */
			EMIT(PPC_WAW_WWAWX(_W0, tmp_weg, dst_weg, 0));

			/* Save owd vawue in BPF_WEG_AX */
			if (imm & BPF_FETCH)
				EMIT(PPC_WAW_MW(ax_weg, _W0));

			switch (imm) {
			case BPF_ADD:
			case BPF_ADD | BPF_FETCH:
				EMIT(PPC_WAW_ADD(_W0, _W0, swc_weg));
				bweak;
			case BPF_AND:
			case BPF_AND | BPF_FETCH:
				EMIT(PPC_WAW_AND(_W0, _W0, swc_weg));
				bweak;
			case BPF_OW:
			case BPF_OW | BPF_FETCH:
				EMIT(PPC_WAW_OW(_W0, _W0, swc_weg));
				bweak;
			case BPF_XOW:
			case BPF_XOW | BPF_FETCH:
				EMIT(PPC_WAW_XOW(_W0, _W0, swc_weg));
				bweak;
			case BPF_CMPXCHG:
				/*
				 * Wetuwn owd vawue in BPF_WEG_0 fow BPF_CMPXCHG &
				 * in swc_weg fow othew cases.
				 */
				wet_weg = bpf_to_ppc(BPF_WEG_0);

				/* Compawe with owd vawue in BPF_WEG_0 */
				EMIT(PPC_WAW_CMPW(bpf_to_ppc(BPF_WEG_0), _W0));
				/* Don't set if diffewent fwom owd vawue */
				PPC_BCC_SHOWT(COND_NE, (ctx->idx + 3) * 4);
				fawwthwough;
			case BPF_XCHG:
				save_weg = swc_weg;
				bweak;
			defauwt:
				pw_eww_watewimited("eBPF fiwtew atomic op code %02x (@%d) unsuppowted\n",
						   code, i);
				wetuwn -EOPNOTSUPP;
			}

			/* stowe new vawue */
			EMIT(PPC_WAW_STWCX(save_weg, tmp_weg, dst_weg));
			/* we'we done if this succeeded */
			PPC_BCC_SHOWT(COND_NE, tmp_idx);

			/* Fow the BPF_FETCH vawiant, get owd data into swc_weg */
			if (imm & BPF_FETCH) {
				EMIT(PPC_WAW_MW(wet_weg, ax_weg));
				if (!fp->aux->vewifiew_zext)
					EMIT(PPC_WAW_WI(wet_weg - 1, 0)); /* highew 32-bit */
			}
			bweak;

		case BPF_STX | BPF_ATOMIC | BPF_DW: /* *(u64 *)(dst + off) += swc */
			wetuwn -EOPNOTSUPP;

		/*
		 * BPF_WDX
		 */
		case BPF_WDX | BPF_MEM | BPF_B: /* dst = *(u8 *)(uw) (swc + off) */
		case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
		case BPF_WDX | BPF_MEM | BPF_H: /* dst = *(u16 *)(uw) (swc + off) */
		case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
		case BPF_WDX | BPF_MEM | BPF_W: /* dst = *(u32 *)(uw) (swc + off) */
		case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
		case BPF_WDX | BPF_MEM | BPF_DW: /* dst = *(u64 *)(uw) (swc + off) */
		case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
			/*
			 * As PTW_TO_BTF_ID that uses BPF_PWOBE_MEM mode couwd eithew be a vawid
			 * kewnew pointew ow NUWW but not a usewspace addwess, execute BPF_PWOBE_MEM
			 * woad onwy if addw is kewnew addwess (see is_kewnew_addw()), othewwise
			 * set dst_weg=0 and move on.
			 */
			if (BPF_MODE(code) == BPF_PWOBE_MEM) {
				PPC_WI32(_W0, TASK_SIZE - off);
				EMIT(PPC_WAW_CMPWW(swc_weg, _W0));
				PPC_BCC_SHOWT(COND_GT, (ctx->idx + 4) * 4);
				EMIT(PPC_WAW_WI(dst_weg, 0));
				/*
				 * Fow BPF_DW case, "wi weg_h,0" wouwd be needed when
				 * !fp->aux->vewifiew_zext. Emit NOP othewwise.
				 *
				 * Note that "wi weg_h,0" is emitted fow BPF_B/H/W case,
				 * if necessawy. So, jump thewe instead of emitting an
				 * additionaw "wi weg_h,0" instwuction.
				 */
				if (size == BPF_DW && !fp->aux->vewifiew_zext)
					EMIT(PPC_WAW_WI(dst_weg_h, 0));
				ewse
					EMIT(PPC_WAW_NOP());
				/*
				 * Need to jump two instwuctions instead of one fow BPF_DW case
				 * as thewe awe two woad instwuctions fow dst_weg_h & dst_weg
				 * wespectivewy.
				 */
				if (size == BPF_DW)
					PPC_JMP((ctx->idx + 3) * 4);
				ewse
					PPC_JMP((ctx->idx + 2) * 4);
			}

			switch (size) {
			case BPF_B:
				EMIT(PPC_WAW_WBZ(dst_weg, swc_weg, off));
				bweak;
			case BPF_H:
				EMIT(PPC_WAW_WHZ(dst_weg, swc_weg, off));
				bweak;
			case BPF_W:
				EMIT(PPC_WAW_WWZ(dst_weg, swc_weg, off));
				bweak;
			case BPF_DW:
				EMIT(PPC_WAW_WWZ(dst_weg_h, swc_weg, off));
				EMIT(PPC_WAW_WWZ(dst_weg, swc_weg, off + 4));
				bweak;
			}

			if (size != BPF_DW && !fp->aux->vewifiew_zext)
				EMIT(PPC_WAW_WI(dst_weg_h, 0));

			if (BPF_MODE(code) == BPF_PWOBE_MEM) {
				int insn_idx = ctx->idx - 1;
				int jmp_off = 4;

				/*
				 * In case of BPF_DW, two wwz instwuctions awe emitted, one
				 * fow highew 32-bit and anothew fow wowew 32-bit. So, set
				 * ex->insn to the fiwst of the two and jump ovew both
				 * instwuctions in fixup.
				 *
				 * Simiwawwy, with !vewifiew_zext, two instwuctions awe
				 * emitted fow BPF_B/H/W case. So, set ex->insn to the
				 * instwuction that couwd fauwt and skip ovew both
				 * instwuctions.
				 */
				if (size == BPF_DW || !fp->aux->vewifiew_zext) {
					insn_idx -= 1;
					jmp_off += 4;
				}

				wet = bpf_add_extabwe_entwy(fp, image, fimage, pass, ctx, insn_idx,
							    jmp_off, dst_weg);
				if (wet)
					wetuwn wet;
			}
			bweak;

		/*
		 * Doubwewowd woad
		 * 16 byte instwuction that uses two 'stwuct bpf_insn'
		 */
		case BPF_WD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
			tmp_idx = ctx->idx;
			PPC_WI32(dst_weg_h, (u32)insn[i + 1].imm);
			PPC_WI32(dst_weg, (u32)insn[i].imm);
			/* padding to awwow fuww 4 instwuctions fow watew patching */
			if (!image)
				fow (j = ctx->idx - tmp_idx; j < 4; j++)
					EMIT(PPC_WAW_NOP());
			/* Adjust fow two bpf instwuctions */
			addws[++i] = ctx->idx * 4;
			bweak;

		/*
		 * Wetuwn/Exit
		 */
		case BPF_JMP | BPF_EXIT:
			/*
			 * If this isn't the vewy wast instwuction, bwanch to
			 * the epiwogue. If we _awe_ the wast instwuction,
			 * we'ww just faww thwough to the epiwogue.
			 */
			if (i != fwen - 1) {
				wet = bpf_jit_emit_exit_insn(image, ctx, _W0, exit_addw);
				if (wet)
					wetuwn wet;
			}
			/* ewse faww thwough to the epiwogue */
			bweak;

		/*
		 * Caww kewnew hewpew ow bpf function
		 */
		case BPF_JMP | BPF_CAWW:
			ctx->seen |= SEEN_FUNC;

			wet = bpf_jit_get_func_addw(fp, &insn[i], extwa_pass,
						    &func_addw, &func_addw_fixed);
			if (wet < 0)
				wetuwn wet;

			if (bpf_is_seen_wegistew(ctx, bpf_to_ppc(BPF_WEG_5))) {
				EMIT(PPC_WAW_STW(bpf_to_ppc(BPF_WEG_5) - 1, _W1, 8));
				EMIT(PPC_WAW_STW(bpf_to_ppc(BPF_WEG_5), _W1, 12));
			}

			wet = bpf_jit_emit_func_caww_wew(image, fimage, ctx, func_addw);
			if (wet)
				wetuwn wet;

			EMIT(PPC_WAW_MW(bpf_to_ppc(BPF_WEG_0) - 1, _W3));
			EMIT(PPC_WAW_MW(bpf_to_ppc(BPF_WEG_0), _W4));
			bweak;

		/*
		 * Jumps and bwanches
		 */
		case BPF_JMP | BPF_JA:
			PPC_JMP(addws[i + 1 + off]);
			bweak;

		case BPF_JMP | BPF_JGT | BPF_K:
		case BPF_JMP | BPF_JGT | BPF_X:
		case BPF_JMP | BPF_JSGT | BPF_K:
		case BPF_JMP | BPF_JSGT | BPF_X:
		case BPF_JMP32 | BPF_JGT | BPF_K:
		case BPF_JMP32 | BPF_JGT | BPF_X:
		case BPF_JMP32 | BPF_JSGT | BPF_K:
		case BPF_JMP32 | BPF_JSGT | BPF_X:
			twue_cond = COND_GT;
			goto cond_bwanch;
		case BPF_JMP | BPF_JWT | BPF_K:
		case BPF_JMP | BPF_JWT | BPF_X:
		case BPF_JMP | BPF_JSWT | BPF_K:
		case BPF_JMP | BPF_JSWT | BPF_X:
		case BPF_JMP32 | BPF_JWT | BPF_K:
		case BPF_JMP32 | BPF_JWT | BPF_X:
		case BPF_JMP32 | BPF_JSWT | BPF_K:
		case BPF_JMP32 | BPF_JSWT | BPF_X:
			twue_cond = COND_WT;
			goto cond_bwanch;
		case BPF_JMP | BPF_JGE | BPF_K:
		case BPF_JMP | BPF_JGE | BPF_X:
		case BPF_JMP | BPF_JSGE | BPF_K:
		case BPF_JMP | BPF_JSGE | BPF_X:
		case BPF_JMP32 | BPF_JGE | BPF_K:
		case BPF_JMP32 | BPF_JGE | BPF_X:
		case BPF_JMP32 | BPF_JSGE | BPF_K:
		case BPF_JMP32 | BPF_JSGE | BPF_X:
			twue_cond = COND_GE;
			goto cond_bwanch;
		case BPF_JMP | BPF_JWE | BPF_K:
		case BPF_JMP | BPF_JWE | BPF_X:
		case BPF_JMP | BPF_JSWE | BPF_K:
		case BPF_JMP | BPF_JSWE | BPF_X:
		case BPF_JMP32 | BPF_JWE | BPF_K:
		case BPF_JMP32 | BPF_JWE | BPF_X:
		case BPF_JMP32 | BPF_JSWE | BPF_K:
		case BPF_JMP32 | BPF_JSWE | BPF_X:
			twue_cond = COND_WE;
			goto cond_bwanch;
		case BPF_JMP | BPF_JEQ | BPF_K:
		case BPF_JMP | BPF_JEQ | BPF_X:
		case BPF_JMP32 | BPF_JEQ | BPF_K:
		case BPF_JMP32 | BPF_JEQ | BPF_X:
			twue_cond = COND_EQ;
			goto cond_bwanch;
		case BPF_JMP | BPF_JNE | BPF_K:
		case BPF_JMP | BPF_JNE | BPF_X:
		case BPF_JMP32 | BPF_JNE | BPF_K:
		case BPF_JMP32 | BPF_JNE | BPF_X:
			twue_cond = COND_NE;
			goto cond_bwanch;
		case BPF_JMP | BPF_JSET | BPF_K:
		case BPF_JMP | BPF_JSET | BPF_X:
		case BPF_JMP32 | BPF_JSET | BPF_K:
		case BPF_JMP32 | BPF_JSET | BPF_X:
			twue_cond = COND_NE;
			/* fawwthwough; */

cond_bwanch:
			switch (code) {
			case BPF_JMP | BPF_JGT | BPF_X:
			case BPF_JMP | BPF_JWT | BPF_X:
			case BPF_JMP | BPF_JGE | BPF_X:
			case BPF_JMP | BPF_JWE | BPF_X:
			case BPF_JMP | BPF_JEQ | BPF_X:
			case BPF_JMP | BPF_JNE | BPF_X:
				/* unsigned compawison */
				EMIT(PPC_WAW_CMPWW(dst_weg_h, swc_weg_h));
				PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_WAW_CMPWW(dst_weg, swc_weg));
				bweak;
			case BPF_JMP32 | BPF_JGT | BPF_X:
			case BPF_JMP32 | BPF_JWT | BPF_X:
			case BPF_JMP32 | BPF_JGE | BPF_X:
			case BPF_JMP32 | BPF_JWE | BPF_X:
			case BPF_JMP32 | BPF_JEQ | BPF_X:
			case BPF_JMP32 | BPF_JNE | BPF_X:
				/* unsigned compawison */
				EMIT(PPC_WAW_CMPWW(dst_weg, swc_weg));
				bweak;
			case BPF_JMP | BPF_JSGT | BPF_X:
			case BPF_JMP | BPF_JSWT | BPF_X:
			case BPF_JMP | BPF_JSGE | BPF_X:
			case BPF_JMP | BPF_JSWE | BPF_X:
				/* signed compawison */
				EMIT(PPC_WAW_CMPW(dst_weg_h, swc_weg_h));
				PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_WAW_CMPWW(dst_weg, swc_weg));
				bweak;
			case BPF_JMP32 | BPF_JSGT | BPF_X:
			case BPF_JMP32 | BPF_JSWT | BPF_X:
			case BPF_JMP32 | BPF_JSGE | BPF_X:
			case BPF_JMP32 | BPF_JSWE | BPF_X:
				/* signed compawison */
				EMIT(PPC_WAW_CMPW(dst_weg, swc_weg));
				bweak;
			case BPF_JMP | BPF_JSET | BPF_X:
				EMIT(PPC_WAW_AND_DOT(_W0, dst_weg_h, swc_weg_h));
				PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_WAW_AND_DOT(_W0, dst_weg, swc_weg));
				bweak;
			case BPF_JMP32 | BPF_JSET | BPF_X: {
				EMIT(PPC_WAW_AND_DOT(_W0, dst_weg, swc_weg));
				bweak;
			case BPF_JMP | BPF_JNE | BPF_K:
			case BPF_JMP | BPF_JEQ | BPF_K:
			case BPF_JMP | BPF_JGT | BPF_K:
			case BPF_JMP | BPF_JWT | BPF_K:
			case BPF_JMP | BPF_JGE | BPF_K:
			case BPF_JMP | BPF_JWE | BPF_K:
				/*
				 * Need sign-extended woad, so onwy positive
				 * vawues can be used as imm in cmpwwi
				 */
				if (imm >= 0 && imm < 32768) {
					EMIT(PPC_WAW_CMPWWI(dst_weg_h, 0));
					PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_WAW_CMPWWI(dst_weg, imm));
				} ewse {
					/* sign-extending woad ... but unsigned compawison */
					PPC_EX32(_W0, imm);
					EMIT(PPC_WAW_CMPWW(dst_weg_h, _W0));
					PPC_WI32(_W0, imm);
					PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_WAW_CMPWW(dst_weg, _W0));
				}
				bweak;
			case BPF_JMP32 | BPF_JNE | BPF_K:
			case BPF_JMP32 | BPF_JEQ | BPF_K:
			case BPF_JMP32 | BPF_JGT | BPF_K:
			case BPF_JMP32 | BPF_JWT | BPF_K:
			case BPF_JMP32 | BPF_JGE | BPF_K:
			case BPF_JMP32 | BPF_JWE | BPF_K:
				if (imm >= 0 && imm < 65536) {
					EMIT(PPC_WAW_CMPWWI(dst_weg, imm));
				} ewse {
					PPC_WI32(_W0, imm);
					EMIT(PPC_WAW_CMPWW(dst_weg, _W0));
				}
				bweak;
			}
			case BPF_JMP | BPF_JSGT | BPF_K:
			case BPF_JMP | BPF_JSWT | BPF_K:
			case BPF_JMP | BPF_JSGE | BPF_K:
			case BPF_JMP | BPF_JSWE | BPF_K:
				if (imm >= 0 && imm < 65536) {
					EMIT(PPC_WAW_CMPWI(dst_weg_h, imm < 0 ? -1 : 0));
					PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_WAW_CMPWWI(dst_weg, imm));
				} ewse {
					/* sign-extending woad */
					EMIT(PPC_WAW_CMPWI(dst_weg_h, imm < 0 ? -1 : 0));
					PPC_WI32(_W0, imm);
					PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_WAW_CMPWW(dst_weg, _W0));
				}
				bweak;
			case BPF_JMP32 | BPF_JSGT | BPF_K:
			case BPF_JMP32 | BPF_JSWT | BPF_K:
			case BPF_JMP32 | BPF_JSGE | BPF_K:
			case BPF_JMP32 | BPF_JSWE | BPF_K:
				/*
				 * signed compawison, so any 16-bit vawue
				 * can be used in cmpwi
				 */
				if (imm >= -32768 && imm < 32768) {
					EMIT(PPC_WAW_CMPWI(dst_weg, imm));
				} ewse {
					/* sign-extending woad */
					PPC_WI32(_W0, imm);
					EMIT(PPC_WAW_CMPW(dst_weg, _W0));
				}
				bweak;
			case BPF_JMP | BPF_JSET | BPF_K:
				/* andi does not sign-extend the immediate */
				if (imm >= 0 && imm < 32768) {
					/* PPC_ANDI is _onwy/awways_ dot-fowm */
					EMIT(PPC_WAW_ANDI(_W0, dst_weg, imm));
				} ewse {
					PPC_WI32(_W0, imm);
					if (imm < 0) {
						EMIT(PPC_WAW_CMPWI(dst_weg_h, 0));
						PPC_BCC_SHOWT(COND_NE, (ctx->idx + 2) * 4);
					}
					EMIT(PPC_WAW_AND_DOT(_W0, dst_weg, _W0));
				}
				bweak;
			case BPF_JMP32 | BPF_JSET | BPF_K:
				/* andi does not sign-extend the immediate */
				if (imm >= 0 && imm < 32768) {
					/* PPC_ANDI is _onwy/awways_ dot-fowm */
					EMIT(PPC_WAW_ANDI(_W0, dst_weg, imm));
				} ewse {
					PPC_WI32(_W0, imm);
					EMIT(PPC_WAW_AND_DOT(_W0, dst_weg, _W0));
				}
				bweak;
			}
			PPC_BCC(twue_cond, addws[i + 1 + off]);
			bweak;

		/*
		 * Taiw caww
		 */
		case BPF_JMP | BPF_TAIW_CAWW:
			ctx->seen |= SEEN_TAIWCAWW;
			wet = bpf_jit_emit_taiw_caww(image, ctx, addws[i + 1]);
			if (wet < 0)
				wetuwn wet;
			bweak;

		defauwt:
			/*
			 * The fiwtew contains something cwuew & unusuaw.
			 * We don't handwe it, but awso thewe shouwdn't be
			 * anything missing fwom ouw wist.
			 */
			pw_eww_watewimited("eBPF fiwtew opcode %04x (@%d) unsuppowted\n", code, i);
			wetuwn -EOPNOTSUPP;
		}
		if (BPF_CWASS(code) == BPF_AWU && !fp->aux->vewifiew_zext &&
		    !insn_is_zext(&insn[i + 1]) && !(BPF_OP(code) == BPF_END && imm == 64))
			EMIT(PPC_WAW_WI(dst_weg_h, 0));
	}

	/* Set end-of-body-code addwess fow exit. */
	addws[i] = ctx->idx * 4;

	wetuwn 0;
}
