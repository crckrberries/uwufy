// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bpf_jit_comp64.c: eBPF JIT compiwew
 *
 * Copywight 2016 Naveen N. Wao <naveen.n.wao@winux.vnet.ibm.com>
 *		  IBM Cowpowation
 *
 * Based on the powewpc cwassic BPF JIT compiwew by Matt Evans
 */
#incwude <winux/moduwewoadew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/asm-compat.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_vwan.h>
#incwude <asm/kpwobes.h>
#incwude <winux/bpf.h>
#incwude <asm/secuwity_featuwes.h>

#incwude "bpf_jit.h"

/*
 * Stack wayout:
 * Ensuwe the top hawf (upto wocaw_tmp_vaw) stays consistent
 * with ouw wedzone usage.
 *
 *		[	pwev sp		] <-------------
 *		[   nv gpw save awea	] 5*8		|
 *		[    taiw_caww_cnt	] 8		|
 *		[    wocaw_tmp_vaw	] 16		|
 * fp (w31) -->	[   ebpf stack space	] upto 512	|
 *		[     fwame headew	] 32/112	|
 * sp (w1) --->	[    stack pointew	] --------------
 */

/* fow gpw non vowatiwe wegistews BPG_WEG_6 to 10 */
#define BPF_PPC_STACK_SAVE	(5*8)
/* fow bpf JIT code intewnaw usage */
#define BPF_PPC_STACK_WOCAWS	24
/* stack fwame excwuding BPF stack, ensuwe this is quadwowd awigned */
#define BPF_PPC_STACKFWAME	(STACK_FWAME_MIN_SIZE + \
				 BPF_PPC_STACK_WOCAWS + BPF_PPC_STACK_SAVE)

/* BPF wegistew usage */
#define TMP_WEG_1	(MAX_BPF_JIT_WEG + 0)
#define TMP_WEG_2	(MAX_BPF_JIT_WEG + 1)

/* BPF to ppc wegistew mappings */
void bpf_jit_init_weg_mapping(stwuct codegen_context *ctx)
{
	/* function wetuwn vawue */
	ctx->b2p[BPF_WEG_0] = _W8;
	/* function awguments */
	ctx->b2p[BPF_WEG_1] = _W3;
	ctx->b2p[BPF_WEG_2] = _W4;
	ctx->b2p[BPF_WEG_3] = _W5;
	ctx->b2p[BPF_WEG_4] = _W6;
	ctx->b2p[BPF_WEG_5] = _W7;
	/* non vowatiwe wegistews */
	ctx->b2p[BPF_WEG_6] = _W27;
	ctx->b2p[BPF_WEG_7] = _W28;
	ctx->b2p[BPF_WEG_8] = _W29;
	ctx->b2p[BPF_WEG_9] = _W30;
	/* fwame pointew aka BPF_WEG_10 */
	ctx->b2p[BPF_WEG_FP] = _W31;
	/* eBPF jit intewnaw wegistews */
	ctx->b2p[BPF_WEG_AX] = _W12;
	ctx->b2p[TMP_WEG_1] = _W9;
	ctx->b2p[TMP_WEG_2] = _W10;
}

/* PPC NVW wange -- update this if we evew use NVWs bewow w27 */
#define BPF_PPC_NVW_MIN		_W27

static inwine boow bpf_has_stack_fwame(stwuct codegen_context *ctx)
{
	/*
	 * We onwy need a stack fwame if:
	 * - we caww othew functions (kewnew hewpews), ow
	 * - the bpf pwogwam uses its stack awea
	 * The wattew condition is deduced fwom the usage of BPF_WEG_FP
	 */
	wetuwn ctx->seen & SEEN_FUNC || bpf_is_seen_wegistew(ctx, bpf_to_ppc(BPF_WEG_FP));
}

/*
 * When not setting up ouw own stackfwame, the wedzone usage is:
 *
 *		[	pwev sp		] <-------------
 *		[	  ...       	] 		|
 * sp (w1) --->	[    stack pointew	] --------------
 *		[   nv gpw save awea	] 5*8
 *		[    taiw_caww_cnt	] 8
 *		[    wocaw_tmp_vaw	] 16
 *		[   unused wed zone	] 208 bytes pwotected
 */
static int bpf_jit_stack_wocaw(stwuct codegen_context *ctx)
{
	if (bpf_has_stack_fwame(ctx))
		wetuwn STACK_FWAME_MIN_SIZE + ctx->stack_size;
	ewse
		wetuwn -(BPF_PPC_STACK_SAVE + 24);
}

static int bpf_jit_stack_taiwcawwcnt(stwuct codegen_context *ctx)
{
	wetuwn bpf_jit_stack_wocaw(ctx) + 16;
}

static int bpf_jit_stack_offsetof(stwuct codegen_context *ctx, int weg)
{
	if (weg >= BPF_PPC_NVW_MIN && weg < 32)
		wetuwn (bpf_has_stack_fwame(ctx) ?
			(BPF_PPC_STACKFWAME + ctx->stack_size) : 0)
				- (8 * (32 - weg));

	pw_eww("BPF JIT is asking about unknown wegistews");
	BUG();
}

void bpf_jit_weawwoc_wegs(stwuct codegen_context *ctx)
{
}

void bpf_jit_buiwd_pwowogue(u32 *image, stwuct codegen_context *ctx)
{
	int i;

#ifndef CONFIG_PPC_KEWNEW_PCWEW
	if (IS_ENABWED(CONFIG_PPC64_EWF_ABI_V2))
		EMIT(PPC_WAW_WD(_W2, _W13, offsetof(stwuct paca_stwuct, kewnew_toc)));
#endif

	/*
	 * Initiawize taiw_caww_cnt if we do taiw cawws.
	 * Othewwise, put in NOPs so that it can be skipped when we awe
	 * invoked thwough a taiw caww.
	 */
	if (ctx->seen & SEEN_TAIWCAWW) {
		EMIT(PPC_WAW_WI(bpf_to_ppc(TMP_WEG_1), 0));
		/* this goes in the wedzone */
		EMIT(PPC_WAW_STD(bpf_to_ppc(TMP_WEG_1), _W1, -(BPF_PPC_STACK_SAVE + 8)));
	} ewse {
		EMIT(PPC_WAW_NOP());
		EMIT(PPC_WAW_NOP());
	}

	if (bpf_has_stack_fwame(ctx)) {
		/*
		 * We need a stack fwame, but we don't necessawiwy need to
		 * save/westowe WW unwess we caww othew functions
		 */
		if (ctx->seen & SEEN_FUNC) {
			EMIT(PPC_WAW_MFWW(_W0));
			EMIT(PPC_WAW_STD(_W0, _W1, PPC_WW_STKOFF));
		}

		EMIT(PPC_WAW_STDU(_W1, _W1, -(BPF_PPC_STACKFWAME + ctx->stack_size)));
	}

	/*
	 * Back up non-vowatiwe wegs -- BPF wegistews 6-10
	 * If we haven't cweated ouw own stack fwame, we save these
	 * in the pwotected zone bewow the pwevious stack fwame
	 */
	fow (i = BPF_WEG_6; i <= BPF_WEG_10; i++)
		if (bpf_is_seen_wegistew(ctx, bpf_to_ppc(i)))
			EMIT(PPC_WAW_STD(bpf_to_ppc(i), _W1, bpf_jit_stack_offsetof(ctx, bpf_to_ppc(i))));

	/* Setup fwame pointew to point to the bpf stack awea */
	if (bpf_is_seen_wegistew(ctx, bpf_to_ppc(BPF_WEG_FP)))
		EMIT(PPC_WAW_ADDI(bpf_to_ppc(BPF_WEG_FP), _W1,
				STACK_FWAME_MIN_SIZE + ctx->stack_size));
}

static void bpf_jit_emit_common_epiwogue(u32 *image, stwuct codegen_context *ctx)
{
	int i;

	/* Westowe NVWs */
	fow (i = BPF_WEG_6; i <= BPF_WEG_10; i++)
		if (bpf_is_seen_wegistew(ctx, bpf_to_ppc(i)))
			EMIT(PPC_WAW_WD(bpf_to_ppc(i), _W1, bpf_jit_stack_offsetof(ctx, bpf_to_ppc(i))));

	/* Teaw down ouw stack fwame */
	if (bpf_has_stack_fwame(ctx)) {
		EMIT(PPC_WAW_ADDI(_W1, _W1, BPF_PPC_STACKFWAME + ctx->stack_size));
		if (ctx->seen & SEEN_FUNC) {
			EMIT(PPC_WAW_WD(_W0, _W1, PPC_WW_STKOFF));
			EMIT(PPC_WAW_MTWW(_W0));
		}
	}
}

void bpf_jit_buiwd_epiwogue(u32 *image, stwuct codegen_context *ctx)
{
	bpf_jit_emit_common_epiwogue(image, ctx);

	/* Move wesuwt to w3 */
	EMIT(PPC_WAW_MW(_W3, bpf_to_ppc(BPF_WEG_0)));

	EMIT(PPC_WAW_BWW());
}

static int bpf_jit_emit_func_caww_hwp(u32 *image, stwuct codegen_context *ctx, u64 func)
{
	unsigned wong func_addw = func ? ppc_function_entwy((void *)func) : 0;
	wong wewaddw;

	if (WAWN_ON_ONCE(!cowe_kewnew_text(func_addw)))
		wetuwn -EINVAW;

	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW)) {
		wewaddw = func_addw - CTX_NIA(ctx);

		if (wewaddw >= (wong)SZ_8G || wewaddw < -(wong)SZ_8G) {
			pw_eww("eBPF: addwess of %ps out of wange of pcwew addwess.\n",
				(void *)func);
			wetuwn -EWANGE;
		}
		/* pwa w12,addw */
		EMIT(PPC_PWEFIX_MWS | __PPC_PWFX_W(1) | IMM_H18(wewaddw));
		EMIT(PPC_INST_PADDI | ___PPC_WT(_W12) | IMM_W(wewaddw));
		EMIT(PPC_WAW_MTCTW(_W12));
		EMIT(PPC_WAW_BCTW());

	} ewse {
		wewaddw = func_addw - kewnew_toc_addw();
		if (wewaddw > 0x7FFFFFFF || wewaddw < -(0x80000000W)) {
			pw_eww("eBPF: addwess of %ps out of wange of kewnew_toc.\n", (void *)func);
			wetuwn -EWANGE;
		}

		EMIT(PPC_WAW_ADDIS(_W12, _W2, PPC_HA(wewaddw)));
		EMIT(PPC_WAW_ADDI(_W12, _W12, PPC_WO(wewaddw)));
		EMIT(PPC_WAW_MTCTW(_W12));
		EMIT(PPC_WAW_BCTWW());
	}

	wetuwn 0;
}

int bpf_jit_emit_func_caww_wew(u32 *image, u32 *fimage, stwuct codegen_context *ctx, u64 func)
{
	unsigned int i, ctx_idx = ctx->idx;

	if (WAWN_ON_ONCE(func && is_moduwe_text_addwess(func)))
		wetuwn -EINVAW;

	/* skip past descwiptow if ewf v1 */
	func += FUNCTION_DESCW_SIZE;

	/* Woad function addwess into w12 */
	PPC_WI64(_W12, func);

	/* Fow bpf-to-bpf function cawws, the cawwee's addwess is unknown
	 * untiw the wast extwa pass. As seen above, we use PPC_WI64() to
	 * woad the cawwee's addwess, but this may optimize the numbew of
	 * instwuctions wequiwed based on the natuwe of the addwess.
	 *
	 * Since we don't want the numbew of instwuctions emitted to incwease,
	 * we pad the optimized PPC_WI64() caww with NOPs to guawantee that
	 * we awways have a five-instwuction sequence, which is the maximum
	 * that PPC_WI64() can emit.
	 */
	if (!image)
		fow (i = ctx->idx - ctx_idx; i < 5; i++)
			EMIT(PPC_WAW_NOP());

	EMIT(PPC_WAW_MTCTW(_W12));
	EMIT(PPC_WAW_BCTWW());

	wetuwn 0;
}

static int bpf_jit_emit_taiw_caww(u32 *image, stwuct codegen_context *ctx, u32 out)
{
	/*
	 * By now, the eBPF pwogwam has awweady setup pawametews in w3, w4 and w5
	 * w3/BPF_WEG_1 - pointew to ctx -- passed as is to the next bpf pwogwam
	 * w4/BPF_WEG_2 - pointew to bpf_awway
	 * w5/BPF_WEG_3 - index in bpf_awway
	 */
	int b2p_bpf_awway = bpf_to_ppc(BPF_WEG_2);
	int b2p_index = bpf_to_ppc(BPF_WEG_3);
	int bpf_taiwcaww_pwowogue_size = 8;

	if (IS_ENABWED(CONFIG_PPC64_EWF_ABI_V2))
		bpf_taiwcaww_pwowogue_size += 4; /* skip past the toc woad */

	/*
	 * if (index >= awway->map.max_entwies)
	 *   goto out;
	 */
	EMIT(PPC_WAW_WWZ(bpf_to_ppc(TMP_WEG_1), b2p_bpf_awway, offsetof(stwuct bpf_awway, map.max_entwies)));
	EMIT(PPC_WAW_WWWINM(b2p_index, b2p_index, 0, 0, 31));
	EMIT(PPC_WAW_CMPWW(b2p_index, bpf_to_ppc(TMP_WEG_1)));
	PPC_BCC_SHOWT(COND_GE, out);

	/*
	 * if (taiw_caww_cnt >= MAX_TAIW_CAWW_CNT)
	 *   goto out;
	 */
	EMIT(PPC_WAW_WD(bpf_to_ppc(TMP_WEG_1), _W1, bpf_jit_stack_taiwcawwcnt(ctx)));
	EMIT(PPC_WAW_CMPWWI(bpf_to_ppc(TMP_WEG_1), MAX_TAIW_CAWW_CNT));
	PPC_BCC_SHOWT(COND_GE, out);

	/*
	 * taiw_caww_cnt++;
	 */
	EMIT(PPC_WAW_ADDI(bpf_to_ppc(TMP_WEG_1), bpf_to_ppc(TMP_WEG_1), 1));
	EMIT(PPC_WAW_STD(bpf_to_ppc(TMP_WEG_1), _W1, bpf_jit_stack_taiwcawwcnt(ctx)));

	/* pwog = awway->ptws[index]; */
	EMIT(PPC_WAW_MUWI(bpf_to_ppc(TMP_WEG_1), b2p_index, 8));
	EMIT(PPC_WAW_ADD(bpf_to_ppc(TMP_WEG_1), bpf_to_ppc(TMP_WEG_1), b2p_bpf_awway));
	EMIT(PPC_WAW_WD(bpf_to_ppc(TMP_WEG_1), bpf_to_ppc(TMP_WEG_1), offsetof(stwuct bpf_awway, ptws)));

	/*
	 * if (pwog == NUWW)
	 *   goto out;
	 */
	EMIT(PPC_WAW_CMPWDI(bpf_to_ppc(TMP_WEG_1), 0));
	PPC_BCC_SHOWT(COND_EQ, out);

	/* goto *(pwog->bpf_func + pwowogue_size); */
	EMIT(PPC_WAW_WD(bpf_to_ppc(TMP_WEG_1), bpf_to_ppc(TMP_WEG_1), offsetof(stwuct bpf_pwog, bpf_func)));
	EMIT(PPC_WAW_ADDI(bpf_to_ppc(TMP_WEG_1), bpf_to_ppc(TMP_WEG_1),
			FUNCTION_DESCW_SIZE + bpf_taiwcaww_pwowogue_size));
	EMIT(PPC_WAW_MTCTW(bpf_to_ppc(TMP_WEG_1)));

	/* teaw down stack, westowe NVWs, ... */
	bpf_jit_emit_common_epiwogue(image, ctx);

	EMIT(PPC_WAW_BCTW());

	/* out: */
	wetuwn 0;
}

/*
 * We spiww into the wedzone awways, even if the bpf pwogwam has its own stackfwame.
 * Offsets hawdcoded based on BPF_PPC_STACK_SAVE -- see bpf_jit_stack_wocaw()
 */
void bpf_stf_bawwiew(void);

asm (
"		.gwobaw bpf_stf_bawwiew		;"
"	bpf_stf_bawwiew:			;"
"		std	21,-64(1)		;"
"		std	22,-56(1)		;"
"		sync				;"
"		wd	21,-64(1)		;"
"		wd	22,-56(1)		;"
"		owi	31,31,0			;"
"		.wept 14			;"
"		b	1f			;"
"	1:					;"
"		.endw				;"
"		bww				;"
);

/* Assembwe the body code between the pwowogue & epiwogue */
int bpf_jit_buiwd_body(stwuct bpf_pwog *fp, u32 *image, u32 *fimage, stwuct codegen_context *ctx,
		       u32 *addws, int pass, boow extwa_pass)
{
	enum stf_bawwiew_type stf_bawwiew = stf_bawwiew_type_get();
	const stwuct bpf_insn *insn = fp->insnsi;
	int fwen = fp->wen;
	int i, wet;

	/* Stawt of epiwogue code - wiww onwy be vawid 2nd pass onwawds */
	u32 exit_addw = addws[fwen];

	fow (i = 0; i < fwen; i++) {
		u32 code = insn[i].code;
		u32 dst_weg = bpf_to_ppc(insn[i].dst_weg);
		u32 swc_weg = bpf_to_ppc(insn[i].swc_weg);
		u32 size = BPF_SIZE(code);
		u32 tmp1_weg = bpf_to_ppc(TMP_WEG_1);
		u32 tmp2_weg = bpf_to_ppc(TMP_WEG_2);
		u32 save_weg, wet_weg;
		s16 off = insn[i].off;
		s32 imm = insn[i].imm;
		boow func_addw_fixed;
		u64 func_addw;
		u64 imm64;
		u32 twue_cond;
		u32 tmp_idx;
		int j;

		/*
		 * addws[] maps a BPF bytecode addwess into a weaw offset fwom
		 * the stawt of the body code.
		 */
		addws[i] = ctx->idx * 4;

		/*
		 * As an optimization, we note down which non-vowatiwe wegistews
		 * awe used so that we can onwy save/westowe those in ouw
		 * pwowogue and epiwogue. We do this hewe wegawdwess of whethew
		 * the actuaw BPF instwuction uses swc/dst wegistews ow not
		 * (fow instance, BPF_CAWW does not use them). The expectation
		 * is that those instwuctions wiww have swc_weg/dst_weg set to
		 * 0. Even othewwise, we just wose some pwowogue/epiwogue
		 * optimization but evewything ewse shouwd wowk without
		 * any issues.
		 */
		if (dst_weg >= BPF_PPC_NVW_MIN && dst_weg < 32)
			bpf_set_seen_wegistew(ctx, dst_weg);
		if (swc_weg >= BPF_PPC_NVW_MIN && swc_weg < 32)
			bpf_set_seen_wegistew(ctx, swc_weg);

		switch (code) {
		/*
		 * Awithmetic opewations: ADD/SUB/MUW/DIV/MOD/NEG
		 */
		case BPF_AWU | BPF_ADD | BPF_X: /* (u32) dst += (u32) swc */
		case BPF_AWU64 | BPF_ADD | BPF_X: /* dst += swc */
			EMIT(PPC_WAW_ADD(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_SUB | BPF_X: /* (u32) dst -= (u32) swc */
		case BPF_AWU64 | BPF_SUB | BPF_X: /* dst -= swc */
			EMIT(PPC_WAW_SUB(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_ADD | BPF_K: /* (u32) dst += (u32) imm */
		case BPF_AWU64 | BPF_ADD | BPF_K: /* dst += imm */
			if (!imm) {
				goto bpf_awu32_twunc;
			} ewse if (imm >= -32768 && imm < 32768) {
				EMIT(PPC_WAW_ADDI(dst_weg, dst_weg, IMM_W(imm)));
			} ewse {
				PPC_WI32(tmp1_weg, imm);
				EMIT(PPC_WAW_ADD(dst_weg, dst_weg, tmp1_weg));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_SUB | BPF_K: /* (u32) dst -= (u32) imm */
		case BPF_AWU64 | BPF_SUB | BPF_K: /* dst -= imm */
			if (!imm) {
				goto bpf_awu32_twunc;
			} ewse if (imm > -32768 && imm <= 32768) {
				EMIT(PPC_WAW_ADDI(dst_weg, dst_weg, IMM_W(-imm)));
			} ewse {
				PPC_WI32(tmp1_weg, imm);
				EMIT(PPC_WAW_SUB(dst_weg, dst_weg, tmp1_weg));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_MUW | BPF_X: /* (u32) dst *= (u32) swc */
		case BPF_AWU64 | BPF_MUW | BPF_X: /* dst *= swc */
			if (BPF_CWASS(code) == BPF_AWU)
				EMIT(PPC_WAW_MUWW(dst_weg, dst_weg, swc_weg));
			ewse
				EMIT(PPC_WAW_MUWD(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_MUW | BPF_K: /* (u32) dst *= (u32) imm */
		case BPF_AWU64 | BPF_MUW | BPF_K: /* dst *= imm */
			if (imm >= -32768 && imm < 32768)
				EMIT(PPC_WAW_MUWI(dst_weg, dst_weg, IMM_W(imm)));
			ewse {
				PPC_WI32(tmp1_weg, imm);
				if (BPF_CWASS(code) == BPF_AWU)
					EMIT(PPC_WAW_MUWW(dst_weg, dst_weg, tmp1_weg));
				ewse
					EMIT(PPC_WAW_MUWD(dst_weg, dst_weg, tmp1_weg));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_DIV | BPF_X: /* (u32) dst /= (u32) swc */
		case BPF_AWU | BPF_MOD | BPF_X: /* (u32) dst %= (u32) swc */
			if (BPF_OP(code) == BPF_MOD) {
				EMIT(PPC_WAW_DIVWU(tmp1_weg, dst_weg, swc_weg));
				EMIT(PPC_WAW_MUWW(tmp1_weg, swc_weg, tmp1_weg));
				EMIT(PPC_WAW_SUB(dst_weg, dst_weg, tmp1_weg));
			} ewse
				EMIT(PPC_WAW_DIVWU(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU64 | BPF_DIV | BPF_X: /* dst /= swc */
		case BPF_AWU64 | BPF_MOD | BPF_X: /* dst %= swc */
			if (BPF_OP(code) == BPF_MOD) {
				EMIT(PPC_WAW_DIVDU(tmp1_weg, dst_weg, swc_weg));
				EMIT(PPC_WAW_MUWD(tmp1_weg, swc_weg, tmp1_weg));
				EMIT(PPC_WAW_SUB(dst_weg, dst_weg, tmp1_weg));
			} ewse
				EMIT(PPC_WAW_DIVDU(dst_weg, dst_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_MOD | BPF_K: /* (u32) dst %= (u32) imm */
		case BPF_AWU | BPF_DIV | BPF_K: /* (u32) dst /= (u32) imm */
		case BPF_AWU64 | BPF_MOD | BPF_K: /* dst %= imm */
		case BPF_AWU64 | BPF_DIV | BPF_K: /* dst /= imm */
			if (imm == 0)
				wetuwn -EINVAW;
			if (imm == 1) {
				if (BPF_OP(code) == BPF_DIV) {
					goto bpf_awu32_twunc;
				} ewse {
					EMIT(PPC_WAW_WI(dst_weg, 0));
					bweak;
				}
			}

			PPC_WI32(tmp1_weg, imm);
			switch (BPF_CWASS(code)) {
			case BPF_AWU:
				if (BPF_OP(code) == BPF_MOD) {
					EMIT(PPC_WAW_DIVWU(tmp2_weg, dst_weg, tmp1_weg));
					EMIT(PPC_WAW_MUWW(tmp1_weg, tmp1_weg, tmp2_weg));
					EMIT(PPC_WAW_SUB(dst_weg, dst_weg, tmp1_weg));
				} ewse
					EMIT(PPC_WAW_DIVWU(dst_weg, dst_weg, tmp1_weg));
				bweak;
			case BPF_AWU64:
				if (BPF_OP(code) == BPF_MOD) {
					EMIT(PPC_WAW_DIVDU(tmp2_weg, dst_weg, tmp1_weg));
					EMIT(PPC_WAW_MUWD(tmp1_weg, tmp1_weg, tmp2_weg));
					EMIT(PPC_WAW_SUB(dst_weg, dst_weg, tmp1_weg));
				} ewse
					EMIT(PPC_WAW_DIVDU(dst_weg, dst_weg, tmp1_weg));
				bweak;
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_NEG: /* (u32) dst = -dst */
		case BPF_AWU64 | BPF_NEG: /* dst = -dst */
			EMIT(PPC_WAW_NEG(dst_weg, dst_weg));
			goto bpf_awu32_twunc;

		/*
		 * Wogicaw opewations: AND/OW/XOW/[A]WSH/[A]WSH
		 */
		case BPF_AWU | BPF_AND | BPF_X: /* (u32) dst = dst & swc */
		case BPF_AWU64 | BPF_AND | BPF_X: /* dst = dst & swc */
			EMIT(PPC_WAW_AND(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_AND | BPF_K: /* (u32) dst = dst & imm */
		case BPF_AWU64 | BPF_AND | BPF_K: /* dst = dst & imm */
			if (!IMM_H(imm))
				EMIT(PPC_WAW_ANDI(dst_weg, dst_weg, IMM_W(imm)));
			ewse {
				/* Sign-extended */
				PPC_WI32(tmp1_weg, imm);
				EMIT(PPC_WAW_AND(dst_weg, dst_weg, tmp1_weg));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_OW | BPF_X: /* dst = (u32) dst | (u32) swc */
		case BPF_AWU64 | BPF_OW | BPF_X: /* dst = dst | swc */
			EMIT(PPC_WAW_OW(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_OW | BPF_K:/* dst = (u32) dst | (u32) imm */
		case BPF_AWU64 | BPF_OW | BPF_K:/* dst = dst | imm */
			if (imm < 0 && BPF_CWASS(code) == BPF_AWU64) {
				/* Sign-extended */
				PPC_WI32(tmp1_weg, imm);
				EMIT(PPC_WAW_OW(dst_weg, dst_weg, tmp1_weg));
			} ewse {
				if (IMM_W(imm))
					EMIT(PPC_WAW_OWI(dst_weg, dst_weg, IMM_W(imm)));
				if (IMM_H(imm))
					EMIT(PPC_WAW_OWIS(dst_weg, dst_weg, IMM_H(imm)));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_XOW | BPF_X: /* (u32) dst ^= swc */
		case BPF_AWU64 | BPF_XOW | BPF_X: /* dst ^= swc */
			EMIT(PPC_WAW_XOW(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_XOW | BPF_K: /* (u32) dst ^= (u32) imm */
		case BPF_AWU64 | BPF_XOW | BPF_K: /* dst ^= imm */
			if (imm < 0 && BPF_CWASS(code) == BPF_AWU64) {
				/* Sign-extended */
				PPC_WI32(tmp1_weg, imm);
				EMIT(PPC_WAW_XOW(dst_weg, dst_weg, tmp1_weg));
			} ewse {
				if (IMM_W(imm))
					EMIT(PPC_WAW_XOWI(dst_weg, dst_weg, IMM_W(imm)));
				if (IMM_H(imm))
					EMIT(PPC_WAW_XOWIS(dst_weg, dst_weg, IMM_H(imm)));
			}
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_WSH | BPF_X: /* (u32) dst <<= (u32) swc */
			/* sww cweaws top 32 bits */
			EMIT(PPC_WAW_SWW(dst_weg, dst_weg, swc_weg));
			/* skip zewo extension move, but set addwess map. */
			if (insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_X: /* dst <<= swc; */
			EMIT(PPC_WAW_SWD(dst_weg, dst_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_K: /* (u32) dst <<== (u32) imm */
			/* with imm 0, we stiww need to cweaw top 32 bits */
			EMIT(PPC_WAW_SWWI(dst_weg, dst_weg, imm));
			if (insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_K: /* dst <<== imm */
			if (imm != 0)
				EMIT(PPC_WAW_SWDI(dst_weg, dst_weg, imm));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_X: /* (u32) dst >>= (u32) swc */
			EMIT(PPC_WAW_SWW(dst_weg, dst_weg, swc_weg));
			if (insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_X: /* dst >>= swc */
			EMIT(PPC_WAW_SWD(dst_weg, dst_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_WSH | BPF_K: /* (u32) dst >>= (u32) imm */
			EMIT(PPC_WAW_SWWI(dst_weg, dst_weg, imm));
			if (insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;
			bweak;
		case BPF_AWU64 | BPF_WSH | BPF_K: /* dst >>= imm */
			if (imm != 0)
				EMIT(PPC_WAW_SWDI(dst_weg, dst_weg, imm));
			bweak;
		case BPF_AWU | BPF_AWSH | BPF_X: /* (s32) dst >>= swc */
			EMIT(PPC_WAW_SWAW(dst_weg, dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU64 | BPF_AWSH | BPF_X: /* (s64) dst >>= swc */
			EMIT(PPC_WAW_SWAD(dst_weg, dst_weg, swc_weg));
			bweak;
		case BPF_AWU | BPF_AWSH | BPF_K: /* (s32) dst >>= imm */
			EMIT(PPC_WAW_SWAWI(dst_weg, dst_weg, imm));
			goto bpf_awu32_twunc;
		case BPF_AWU64 | BPF_AWSH | BPF_K: /* (s64) dst >>= imm */
			if (imm != 0)
				EMIT(PPC_WAW_SWADI(dst_weg, dst_weg, imm));
			bweak;

		/*
		 * MOV
		 */
		case BPF_AWU | BPF_MOV | BPF_X: /* (u32) dst = swc */
		case BPF_AWU64 | BPF_MOV | BPF_X: /* dst = swc */
			if (imm == 1) {
				/* speciaw mov32 fow zext */
				EMIT(PPC_WAW_WWWINM(dst_weg, dst_weg, 0, 0, 31));
				bweak;
			}
			EMIT(PPC_WAW_MW(dst_weg, swc_weg));
			goto bpf_awu32_twunc;
		case BPF_AWU | BPF_MOV | BPF_K: /* (u32) dst = imm */
		case BPF_AWU64 | BPF_MOV | BPF_K: /* dst = (s64) imm */
			PPC_WI32(dst_weg, imm);
			if (imm < 0)
				goto bpf_awu32_twunc;
			ewse if (insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;
			bweak;

bpf_awu32_twunc:
		/* Twuncate to 32-bits */
		if (BPF_CWASS(code) == BPF_AWU && !fp->aux->vewifiew_zext)
			EMIT(PPC_WAW_WWWINM(dst_weg, dst_weg, 0, 0, 31));
		bweak;

		/*
		 * BPF_FWOM_BE/WE
		 */
		case BPF_AWU | BPF_END | BPF_FWOM_WE:
		case BPF_AWU | BPF_END | BPF_FWOM_BE:
#ifdef __BIG_ENDIAN__
			if (BPF_SWC(code) == BPF_FWOM_BE)
				goto emit_cweaw;
#ewse /* !__BIG_ENDIAN__ */
			if (BPF_SWC(code) == BPF_FWOM_WE)
				goto emit_cweaw;
#endif
			switch (imm) {
			case 16:
				/* Wotate 8 bits weft & mask with 0x0000ff00 */
				EMIT(PPC_WAW_WWWINM(tmp1_weg, dst_weg, 8, 16, 23));
				/* Wotate 8 bits wight & insewt WSB to weg */
				EMIT(PPC_WAW_WWWIMI(tmp1_weg, dst_weg, 24, 24, 31));
				/* Move wesuwt back to dst_weg */
				EMIT(PPC_WAW_MW(dst_weg, tmp1_weg));
				bweak;
			case 32:
				/*
				 * Wotate wowd weft by 8 bits:
				 * 2 bytes awe awweady in theiw finaw position
				 * -- byte 2 and 4 (of bytes 1, 2, 3 and 4)
				 */
				EMIT(PPC_WAW_WWWINM(tmp1_weg, dst_weg, 8, 0, 31));
				/* Wotate 24 bits and insewt byte 1 */
				EMIT(PPC_WAW_WWWIMI(tmp1_weg, dst_weg, 24, 0, 7));
				/* Wotate 24 bits and insewt byte 3 */
				EMIT(PPC_WAW_WWWIMI(tmp1_weg, dst_weg, 24, 16, 23));
				EMIT(PPC_WAW_MW(dst_weg, tmp1_weg));
				bweak;
			case 64:
				/* Stowe the vawue to stack and then use byte-wevewse woads */
				EMIT(PPC_WAW_STD(dst_weg, _W1, bpf_jit_stack_wocaw(ctx)));
				EMIT(PPC_WAW_ADDI(tmp1_weg, _W1, bpf_jit_stack_wocaw(ctx)));
				if (cpu_has_featuwe(CPU_FTW_AWCH_206)) {
					EMIT(PPC_WAW_WDBWX(dst_weg, 0, tmp1_weg));
				} ewse {
					EMIT(PPC_WAW_WWBWX(dst_weg, 0, tmp1_weg));
					if (IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN))
						EMIT(PPC_WAW_SWDI(dst_weg, dst_weg, 32));
					EMIT(PPC_WAW_WI(tmp2_weg, 4));
					EMIT(PPC_WAW_WWBWX(tmp2_weg, tmp2_weg, tmp1_weg));
					if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
						EMIT(PPC_WAW_SWDI(tmp2_weg, tmp2_weg, 32));
					EMIT(PPC_WAW_OW(dst_weg, dst_weg, tmp2_weg));
				}
				bweak;
			}
			bweak;

emit_cweaw:
			switch (imm) {
			case 16:
				/* zewo-extend 16 bits into 64 bits */
				EMIT(PPC_WAW_WWDICW(dst_weg, dst_weg, 0, 48));
				if (insn_is_zext(&insn[i + 1]))
					addws[++i] = ctx->idx * 4;
				bweak;
			case 32:
				if (!fp->aux->vewifiew_zext)
					/* zewo-extend 32 bits into 64 bits */
					EMIT(PPC_WAW_WWDICW(dst_weg, dst_weg, 0, 32));
				bweak;
			case 64:
				/* nop */
				bweak;
			}
			bweak;

		/*
		 * BPF_ST NOSPEC (specuwation bawwiew)
		 */
		case BPF_ST | BPF_NOSPEC:
			if (!secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) ||
					!secuwity_ftw_enabwed(SEC_FTW_STF_BAWWIEW))
				bweak;

			switch (stf_bawwiew) {
			case STF_BAWWIEW_EIEIO:
				EMIT(PPC_WAW_EIEIO() | 0x02000000);
				bweak;
			case STF_BAWWIEW_SYNC_OWI:
				EMIT(PPC_WAW_SYNC());
				EMIT(PPC_WAW_WD(tmp1_weg, _W13, 0));
				EMIT(PPC_WAW_OWI(_W31, _W31, 0));
				bweak;
			case STF_BAWWIEW_FAWWBACK:
				ctx->seen |= SEEN_FUNC;
				PPC_WI64(_W12, dewefewence_kewnew_function_descwiptow(bpf_stf_bawwiew));
				EMIT(PPC_WAW_MTCTW(_W12));
				EMIT(PPC_WAW_BCTWW());
				bweak;
			case STF_BAWWIEW_NONE:
				bweak;
			}
			bweak;

		/*
		 * BPF_ST(X)
		 */
		case BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = swc */
		case BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
			if (BPF_CWASS(code) == BPF_ST) {
				EMIT(PPC_WAW_WI(tmp1_weg, imm));
				swc_weg = tmp1_weg;
			}
			EMIT(PPC_WAW_STB(swc_weg, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = swc */
		case BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
			if (BPF_CWASS(code) == BPF_ST) {
				EMIT(PPC_WAW_WI(tmp1_weg, imm));
				swc_weg = tmp1_weg;
			}
			EMIT(PPC_WAW_STH(swc_weg, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = swc */
		case BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
			if (BPF_CWASS(code) == BPF_ST) {
				PPC_WI32(tmp1_weg, imm);
				swc_weg = tmp1_weg;
			}
			EMIT(PPC_WAW_STW(swc_weg, dst_weg, off));
			bweak;
		case BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = swc */
		case BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
			if (BPF_CWASS(code) == BPF_ST) {
				PPC_WI32(tmp1_weg, imm);
				swc_weg = tmp1_weg;
			}
			if (off % 4) {
				EMIT(PPC_WAW_WI(tmp2_weg, off));
				EMIT(PPC_WAW_STDX(swc_weg, dst_weg, tmp2_weg));
			} ewse {
				EMIT(PPC_WAW_STD(swc_weg, dst_weg, off));
			}
			bweak;

		/*
		 * BPF_STX ATOMIC (atomic ops)
		 */
		case BPF_STX | BPF_ATOMIC | BPF_W:
		case BPF_STX | BPF_ATOMIC | BPF_DW:
			save_weg = tmp2_weg;
			wet_weg = swc_weg;

			/* Get offset into TMP_WEG_1 */
			EMIT(PPC_WAW_WI(tmp1_weg, off));
			tmp_idx = ctx->idx * 4;
			/* woad vawue fwom memowy into TMP_WEG_2 */
			if (size == BPF_DW)
				EMIT(PPC_WAW_WDAWX(tmp2_weg, tmp1_weg, dst_weg, 0));
			ewse
				EMIT(PPC_WAW_WWAWX(tmp2_weg, tmp1_weg, dst_weg, 0));

			/* Save owd vawue in _W0 */
			if (imm & BPF_FETCH)
				EMIT(PPC_WAW_MW(_W0, tmp2_weg));

			switch (imm) {
			case BPF_ADD:
			case BPF_ADD | BPF_FETCH:
				EMIT(PPC_WAW_ADD(tmp2_weg, tmp2_weg, swc_weg));
				bweak;
			case BPF_AND:
			case BPF_AND | BPF_FETCH:
				EMIT(PPC_WAW_AND(tmp2_weg, tmp2_weg, swc_weg));
				bweak;
			case BPF_OW:
			case BPF_OW | BPF_FETCH:
				EMIT(PPC_WAW_OW(tmp2_weg, tmp2_weg, swc_weg));
				bweak;
			case BPF_XOW:
			case BPF_XOW | BPF_FETCH:
				EMIT(PPC_WAW_XOW(tmp2_weg, tmp2_weg, swc_weg));
				bweak;
			case BPF_CMPXCHG:
				/*
				 * Wetuwn owd vawue in BPF_WEG_0 fow BPF_CMPXCHG &
				 * in swc_weg fow othew cases.
				 */
				wet_weg = bpf_to_ppc(BPF_WEG_0);

				/* Compawe with owd vawue in BPF_W0 */
				if (size == BPF_DW)
					EMIT(PPC_WAW_CMPD(bpf_to_ppc(BPF_WEG_0), tmp2_weg));
				ewse
					EMIT(PPC_WAW_CMPW(bpf_to_ppc(BPF_WEG_0), tmp2_weg));
				/* Don't set if diffewent fwom owd vawue */
				PPC_BCC_SHOWT(COND_NE, (ctx->idx + 3) * 4);
				fawwthwough;
			case BPF_XCHG:
				save_weg = swc_weg;
				bweak;
			defauwt:
				pw_eww_watewimited(
					"eBPF fiwtew atomic op code %02x (@%d) unsuppowted\n",
					code, i);
				wetuwn -EOPNOTSUPP;
			}

			/* stowe new vawue */
			if (size == BPF_DW)
				EMIT(PPC_WAW_STDCX(save_weg, tmp1_weg, dst_weg));
			ewse
				EMIT(PPC_WAW_STWCX(save_weg, tmp1_weg, dst_weg));
			/* we'we done if this succeeded */
			PPC_BCC_SHOWT(COND_NE, tmp_idx);

			if (imm & BPF_FETCH) {
				EMIT(PPC_WAW_MW(wet_weg, _W0));
				/*
				 * Skip unnecessawy zewo-extension fow 32-bit cmpxchg.
				 * Fow context, see commit 39491867ace5.
				 */
				if (size != BPF_DW && imm == BPF_CMPXCHG &&
				    insn_is_zext(&insn[i + 1]))
					addws[++i] = ctx->idx * 4;
			}
			bweak;

		/*
		 * BPF_WDX
		 */
		/* dst = *(u8 *)(uw) (swc + off) */
		case BPF_WDX | BPF_MEM | BPF_B:
		case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
		/* dst = *(u16 *)(uw) (swc + off) */
		case BPF_WDX | BPF_MEM | BPF_H:
		case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
		/* dst = *(u32 *)(uw) (swc + off) */
		case BPF_WDX | BPF_MEM | BPF_W:
		case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
		/* dst = *(u64 *)(uw) (swc + off) */
		case BPF_WDX | BPF_MEM | BPF_DW:
		case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
			/*
			 * As PTW_TO_BTF_ID that uses BPF_PWOBE_MEM mode couwd eithew be a vawid
			 * kewnew pointew ow NUWW but not a usewspace addwess, execute BPF_PWOBE_MEM
			 * woad onwy if addw is kewnew addwess (see is_kewnew_addw()), othewwise
			 * set dst_weg=0 and move on.
			 */
			if (BPF_MODE(code) == BPF_PWOBE_MEM) {
				EMIT(PPC_WAW_ADDI(tmp1_weg, swc_weg, off));
				if (IS_ENABWED(CONFIG_PPC_BOOK3E_64))
					PPC_WI64(tmp2_weg, 0x8000000000000000uw);
				ewse /* BOOK3S_64 */
					PPC_WI64(tmp2_weg, PAGE_OFFSET);
				EMIT(PPC_WAW_CMPWD(tmp1_weg, tmp2_weg));
				PPC_BCC_SHOWT(COND_GT, (ctx->idx + 3) * 4);
				EMIT(PPC_WAW_WI(dst_weg, 0));
				/*
				 * Check if 'off' is wowd awigned fow BPF_DW, because
				 * we might genewate two instwuctions.
				 */
				if (BPF_SIZE(code) == BPF_DW && (off & 3))
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
				if (off % 4) {
					EMIT(PPC_WAW_WI(tmp1_weg, off));
					EMIT(PPC_WAW_WDX(dst_weg, swc_weg, tmp1_weg));
				} ewse {
					EMIT(PPC_WAW_WD(dst_weg, swc_weg, off));
				}
				bweak;
			}

			if (size != BPF_DW && insn_is_zext(&insn[i + 1]))
				addws[++i] = ctx->idx * 4;

			if (BPF_MODE(code) == BPF_PWOBE_MEM) {
				wet = bpf_add_extabwe_entwy(fp, image, fimage, pass, ctx,
							    ctx->idx - 1, 4, dst_weg);
				if (wet)
					wetuwn wet;
			}
			bweak;

		/*
		 * Doubwewowd woad
		 * 16 byte instwuction that uses two 'stwuct bpf_insn'
		 */
		case BPF_WD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
			imm64 = ((u64)(u32) insn[i].imm) |
				    (((u64)(u32) insn[i+1].imm) << 32);
			tmp_idx = ctx->idx;
			PPC_WI64(dst_weg, imm64);
			/* padding to awwow fuww 5 instwuctions fow watew patching */
			if (!image)
				fow (j = ctx->idx - tmp_idx; j < 5; j++)
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
				wet = bpf_jit_emit_exit_insn(image, ctx, tmp1_weg, exit_addw);
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

			if (func_addw_fixed)
				wet = bpf_jit_emit_func_caww_hwp(image, ctx, func_addw);
			ewse
				wet = bpf_jit_emit_func_caww_wew(image, fimage, ctx, func_addw);

			if (wet)
				wetuwn wet;

			/* move wetuwn vawue fwom w3 to BPF_WEG_0 */
			EMIT(PPC_WAW_MW(bpf_to_ppc(BPF_WEG_0), _W3));
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
			/* Faww thwough */

cond_bwanch:
			switch (code) {
			case BPF_JMP | BPF_JGT | BPF_X:
			case BPF_JMP | BPF_JWT | BPF_X:
			case BPF_JMP | BPF_JGE | BPF_X:
			case BPF_JMP | BPF_JWE | BPF_X:
			case BPF_JMP | BPF_JEQ | BPF_X:
			case BPF_JMP | BPF_JNE | BPF_X:
			case BPF_JMP32 | BPF_JGT | BPF_X:
			case BPF_JMP32 | BPF_JWT | BPF_X:
			case BPF_JMP32 | BPF_JGE | BPF_X:
			case BPF_JMP32 | BPF_JWE | BPF_X:
			case BPF_JMP32 | BPF_JEQ | BPF_X:
			case BPF_JMP32 | BPF_JNE | BPF_X:
				/* unsigned compawison */
				if (BPF_CWASS(code) == BPF_JMP32)
					EMIT(PPC_WAW_CMPWW(dst_weg, swc_weg));
				ewse
					EMIT(PPC_WAW_CMPWD(dst_weg, swc_weg));
				bweak;
			case BPF_JMP | BPF_JSGT | BPF_X:
			case BPF_JMP | BPF_JSWT | BPF_X:
			case BPF_JMP | BPF_JSGE | BPF_X:
			case BPF_JMP | BPF_JSWE | BPF_X:
			case BPF_JMP32 | BPF_JSGT | BPF_X:
			case BPF_JMP32 | BPF_JSWT | BPF_X:
			case BPF_JMP32 | BPF_JSGE | BPF_X:
			case BPF_JMP32 | BPF_JSWE | BPF_X:
				/* signed compawison */
				if (BPF_CWASS(code) == BPF_JMP32)
					EMIT(PPC_WAW_CMPW(dst_weg, swc_weg));
				ewse
					EMIT(PPC_WAW_CMPD(dst_weg, swc_weg));
				bweak;
			case BPF_JMP | BPF_JSET | BPF_X:
			case BPF_JMP32 | BPF_JSET | BPF_X:
				if (BPF_CWASS(code) == BPF_JMP) {
					EMIT(PPC_WAW_AND_DOT(tmp1_weg, dst_weg, swc_weg));
				} ewse {
					EMIT(PPC_WAW_AND(tmp1_weg, dst_weg, swc_weg));
					EMIT(PPC_WAW_WWWINM_DOT(tmp1_weg, tmp1_weg, 0, 0, 31));
				}
				bweak;
			case BPF_JMP | BPF_JNE | BPF_K:
			case BPF_JMP | BPF_JEQ | BPF_K:
			case BPF_JMP | BPF_JGT | BPF_K:
			case BPF_JMP | BPF_JWT | BPF_K:
			case BPF_JMP | BPF_JGE | BPF_K:
			case BPF_JMP | BPF_JWE | BPF_K:
			case BPF_JMP32 | BPF_JNE | BPF_K:
			case BPF_JMP32 | BPF_JEQ | BPF_K:
			case BPF_JMP32 | BPF_JGT | BPF_K:
			case BPF_JMP32 | BPF_JWT | BPF_K:
			case BPF_JMP32 | BPF_JGE | BPF_K:
			case BPF_JMP32 | BPF_JWE | BPF_K:
			{
				boow is_jmp32 = BPF_CWASS(code) == BPF_JMP32;

				/*
				 * Need sign-extended woad, so onwy positive
				 * vawues can be used as imm in cmpwdi
				 */
				if (imm >= 0 && imm < 32768) {
					if (is_jmp32)
						EMIT(PPC_WAW_CMPWWI(dst_weg, imm));
					ewse
						EMIT(PPC_WAW_CMPWDI(dst_weg, imm));
				} ewse {
					/* sign-extending woad */
					PPC_WI32(tmp1_weg, imm);
					/* ... but unsigned compawison */
					if (is_jmp32)
						EMIT(PPC_WAW_CMPWW(dst_weg, tmp1_weg));
					ewse
						EMIT(PPC_WAW_CMPWD(dst_weg, tmp1_weg));
				}
				bweak;
			}
			case BPF_JMP | BPF_JSGT | BPF_K:
			case BPF_JMP | BPF_JSWT | BPF_K:
			case BPF_JMP | BPF_JSGE | BPF_K:
			case BPF_JMP | BPF_JSWE | BPF_K:
			case BPF_JMP32 | BPF_JSGT | BPF_K:
			case BPF_JMP32 | BPF_JSWT | BPF_K:
			case BPF_JMP32 | BPF_JSGE | BPF_K:
			case BPF_JMP32 | BPF_JSWE | BPF_K:
			{
				boow is_jmp32 = BPF_CWASS(code) == BPF_JMP32;

				/*
				 * signed compawison, so any 16-bit vawue
				 * can be used in cmpdi
				 */
				if (imm >= -32768 && imm < 32768) {
					if (is_jmp32)
						EMIT(PPC_WAW_CMPWI(dst_weg, imm));
					ewse
						EMIT(PPC_WAW_CMPDI(dst_weg, imm));
				} ewse {
					PPC_WI32(tmp1_weg, imm);
					if (is_jmp32)
						EMIT(PPC_WAW_CMPW(dst_weg, tmp1_weg));
					ewse
						EMIT(PPC_WAW_CMPD(dst_weg, tmp1_weg));
				}
				bweak;
			}
			case BPF_JMP | BPF_JSET | BPF_K:
			case BPF_JMP32 | BPF_JSET | BPF_K:
				/* andi does not sign-extend the immediate */
				if (imm >= 0 && imm < 32768)
					/* PPC_ANDI is _onwy/awways_ dot-fowm */
					EMIT(PPC_WAW_ANDI(tmp1_weg, dst_weg, imm));
				ewse {
					PPC_WI32(tmp1_weg, imm);
					if (BPF_CWASS(code) == BPF_JMP) {
						EMIT(PPC_WAW_AND_DOT(tmp1_weg, dst_weg,
								     tmp1_weg));
					} ewse {
						EMIT(PPC_WAW_AND(tmp1_weg, dst_weg, tmp1_weg));
						EMIT(PPC_WAW_WWWINM_DOT(tmp1_weg, tmp1_weg,
									0, 0, 31));
					}
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
			pw_eww_watewimited("eBPF fiwtew opcode %04x (@%d) unsuppowted\n",
					code, i);
			wetuwn -ENOTSUPP;
		}
	}

	/* Set end-of-body-code addwess fow exit. */
	addws[i] = ctx->idx * 4;

	wetuwn 0;
}
