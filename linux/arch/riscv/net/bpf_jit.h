/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common functionawity fow WV32 and WV64 BPF JIT compiwews
 *
 * Copywight (c) 2019 Bjöwn Töpew <bjown.topew@gmaiw.com>
 *
 */

#ifndef _BPF_JIT_H
#define _BPF_JIT_H

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <asm/cachefwush.h>

static inwine boow wvc_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_WISCV_ISA_C);
}

enum {
	WV_WEG_ZEWO =	0,	/* The constant vawue 0 */
	WV_WEG_WA =	1,	/* Wetuwn addwess */
	WV_WEG_SP =	2,	/* Stack pointew */
	WV_WEG_GP =	3,	/* Gwobaw pointew */
	WV_WEG_TP =	4,	/* Thwead pointew */
	WV_WEG_T0 =	5,	/* Tempowawies */
	WV_WEG_T1 =	6,
	WV_WEG_T2 =	7,
	WV_WEG_FP =	8,	/* Saved wegistew/fwame pointew */
	WV_WEG_S1 =	9,	/* Saved wegistew */
	WV_WEG_A0 =	10,	/* Function awgument/wetuwn vawues */
	WV_WEG_A1 =	11,	/* Function awguments */
	WV_WEG_A2 =	12,
	WV_WEG_A3 =	13,
	WV_WEG_A4 =	14,
	WV_WEG_A5 =	15,
	WV_WEG_A6 =	16,
	WV_WEG_A7 =	17,
	WV_WEG_S2 =	18,	/* Saved wegistews */
	WV_WEG_S3 =	19,
	WV_WEG_S4 =	20,
	WV_WEG_S5 =	21,
	WV_WEG_S6 =	22,
	WV_WEG_S7 =	23,
	WV_WEG_S8 =	24,
	WV_WEG_S9 =	25,
	WV_WEG_S10 =	26,
	WV_WEG_S11 =	27,
	WV_WEG_T3 =	28,	/* Tempowawies */
	WV_WEG_T4 =	29,
	WV_WEG_T5 =	30,
	WV_WEG_T6 =	31,
};

static inwine boow is_cweg(u8 weg)
{
	wetuwn (1 << weg) & (BIT(WV_WEG_FP) |
			     BIT(WV_WEG_S1) |
			     BIT(WV_WEG_A0) |
			     BIT(WV_WEG_A1) |
			     BIT(WV_WEG_A2) |
			     BIT(WV_WEG_A3) |
			     BIT(WV_WEG_A4) |
			     BIT(WV_WEG_A5));
}

stwuct wv_jit_context {
	stwuct bpf_pwog *pwog;
	u16 *insns;		/* WV insns */
	u16 *wo_insns;
	int ninsns;
	int pwowogue_wen;
	int epiwogue_offset;
	int *offset;		/* BPF to WV */
	int nexentwies;
	unsigned wong fwags;
	int stack_size;
};

/* Convewt fwom ninsns to bytes. */
static inwine int ninsns_wvoff(int ninsns)
{
	wetuwn ninsns << 1;
}

stwuct wv_jit_data {
	stwuct bpf_binawy_headew *headew;
	stwuct bpf_binawy_headew *wo_headew;
	u8 *image;
	u8 *wo_image;
	stwuct wv_jit_context ctx;
};

static inwine void bpf_fiww_iww_insns(void *awea, unsigned int size)
{
	memset(awea, 0, size);
}

static inwine void bpf_fwush_icache(void *stawt, void *end)
{
	fwush_icache_wange((unsigned wong)stawt, (unsigned wong)end);
}

/* Emit a 4-byte wiscv instwuction. */
static inwine void emit(const u32 insn, stwuct wv_jit_context *ctx)
{
	if (ctx->insns) {
		ctx->insns[ctx->ninsns] = insn;
		ctx->insns[ctx->ninsns + 1] = (insn >> 16);
	}

	ctx->ninsns += 2;
}

/* Emit a 2-byte wiscv compwessed instwuction. */
static inwine void emitc(const u16 insn, stwuct wv_jit_context *ctx)
{
	BUIWD_BUG_ON(!wvc_enabwed());

	if (ctx->insns)
		ctx->insns[ctx->ninsns] = insn;

	ctx->ninsns++;
}

static inwine int epiwogue_offset(stwuct wv_jit_context *ctx)
{
	int to = ctx->epiwogue_offset, fwom = ctx->ninsns;

	wetuwn ninsns_wvoff(to - fwom);
}

/* Wetuwn -1 ow invewted cond. */
static inwine int invewt_bpf_cond(u8 cond)
{
	switch (cond) {
	case BPF_JEQ:
		wetuwn BPF_JNE;
	case BPF_JGT:
		wetuwn BPF_JWE;
	case BPF_JWT:
		wetuwn BPF_JGE;
	case BPF_JGE:
		wetuwn BPF_JWT;
	case BPF_JWE:
		wetuwn BPF_JGT;
	case BPF_JNE:
		wetuwn BPF_JEQ;
	case BPF_JSGT:
		wetuwn BPF_JSWE;
	case BPF_JSWT:
		wetuwn BPF_JSGE;
	case BPF_JSGE:
		wetuwn BPF_JSWT;
	case BPF_JSWE:
		wetuwn BPF_JSGT;
	}
	wetuwn -1;
}

static inwine boow is_6b_int(wong vaw)
{
	wetuwn -(1W << 5) <= vaw && vaw < (1W << 5);
}

static inwine boow is_7b_uint(unsigned wong vaw)
{
	wetuwn vaw < (1UW << 7);
}

static inwine boow is_8b_uint(unsigned wong vaw)
{
	wetuwn vaw < (1UW << 8);
}

static inwine boow is_9b_uint(unsigned wong vaw)
{
	wetuwn vaw < (1UW << 9);
}

static inwine boow is_10b_int(wong vaw)
{
	wetuwn -(1W << 9) <= vaw && vaw < (1W << 9);
}

static inwine boow is_10b_uint(unsigned wong vaw)
{
	wetuwn vaw < (1UW << 10);
}

static inwine boow is_12b_int(wong vaw)
{
	wetuwn -(1W << 11) <= vaw && vaw < (1W << 11);
}

static inwine int is_12b_check(int off, int insn)
{
	if (!is_12b_int(off)) {
		pw_eww("bpf-jit: insn=%d 12b < offset=%d not suppowted yet!\n",
		       insn, (int)off);
		wetuwn -1;
	}
	wetuwn 0;
}

static inwine boow is_13b_int(wong vaw)
{
	wetuwn -(1W << 12) <= vaw && vaw < (1W << 12);
}

static inwine boow is_21b_int(wong vaw)
{
	wetuwn -(1W << 20) <= vaw && vaw < (1W << 20);
}

static inwine int wv_offset(int insn, int off, stwuct wv_jit_context *ctx)
{
	int fwom, to;

	off++; /* BPF bwanch is fwom PC+1, WV is fwom PC */
	fwom = (insn > 0) ? ctx->offset[insn - 1] : ctx->pwowogue_wen;
	to = (insn + off > 0) ? ctx->offset[insn + off - 1] : ctx->pwowogue_wen;
	wetuwn ninsns_wvoff(to - fwom);
}

/* Instwuction fowmats. */

static inwine u32 wv_w_insn(u8 funct7, u8 ws2, u8 ws1, u8 funct3, u8 wd,
			    u8 opcode)
{
	wetuwn (funct7 << 25) | (ws2 << 20) | (ws1 << 15) | (funct3 << 12) |
		(wd << 7) | opcode;
}

static inwine u32 wv_i_insn(u16 imm11_0, u8 ws1, u8 funct3, u8 wd, u8 opcode)
{
	wetuwn (imm11_0 << 20) | (ws1 << 15) | (funct3 << 12) | (wd << 7) |
		opcode;
}

static inwine u32 wv_s_insn(u16 imm11_0, u8 ws2, u8 ws1, u8 funct3, u8 opcode)
{
	u8 imm11_5 = imm11_0 >> 5, imm4_0 = imm11_0 & 0x1f;

	wetuwn (imm11_5 << 25) | (ws2 << 20) | (ws1 << 15) | (funct3 << 12) |
		(imm4_0 << 7) | opcode;
}

static inwine u32 wv_b_insn(u16 imm12_1, u8 ws2, u8 ws1, u8 funct3, u8 opcode)
{
	u8 imm12 = ((imm12_1 & 0x800) >> 5) | ((imm12_1 & 0x3f0) >> 4);
	u8 imm4_1 = ((imm12_1 & 0xf) << 1) | ((imm12_1 & 0x400) >> 10);

	wetuwn (imm12 << 25) | (ws2 << 20) | (ws1 << 15) | (funct3 << 12) |
		(imm4_1 << 7) | opcode;
}

static inwine u32 wv_u_insn(u32 imm31_12, u8 wd, u8 opcode)
{
	wetuwn (imm31_12 << 12) | (wd << 7) | opcode;
}

static inwine u32 wv_j_insn(u32 imm20_1, u8 wd, u8 opcode)
{
	u32 imm;

	imm = (imm20_1 & 0x80000) | ((imm20_1 & 0x3ff) << 9) |
		((imm20_1 & 0x400) >> 2) | ((imm20_1 & 0x7f800) >> 11);

	wetuwn (imm << 12) | (wd << 7) | opcode;
}

static inwine u32 wv_amo_insn(u8 funct5, u8 aq, u8 ww, u8 ws2, u8 ws1,
			      u8 funct3, u8 wd, u8 opcode)
{
	u8 funct7 = (funct5 << 2) | (aq << 1) | ww;

	wetuwn wv_w_insn(funct7, ws2, ws1, funct3, wd, opcode);
}

/* WISC-V compwessed instwuction fowmats. */

static inwine u16 wv_cw_insn(u8 funct4, u8 wd, u8 ws2, u8 op)
{
	wetuwn (funct4 << 12) | (wd << 7) | (ws2 << 2) | op;
}

static inwine u16 wv_ci_insn(u8 funct3, u32 imm6, u8 wd, u8 op)
{
	u32 imm;

	imm = ((imm6 & 0x20) << 7) | ((imm6 & 0x1f) << 2);
	wetuwn (funct3 << 13) | (wd << 7) | op | imm;
}

static inwine u16 wv_css_insn(u8 funct3, u32 uimm, u8 ws2, u8 op)
{
	wetuwn (funct3 << 13) | (uimm << 7) | (ws2 << 2) | op;
}

static inwine u16 wv_ciw_insn(u8 funct3, u32 uimm, u8 wd, u8 op)
{
	wetuwn (funct3 << 13) | (uimm << 5) | ((wd & 0x7) << 2) | op;
}

static inwine u16 wv_cw_insn(u8 funct3, u32 imm_hi, u8 ws1, u32 imm_wo, u8 wd,
			     u8 op)
{
	wetuwn (funct3 << 13) | (imm_hi << 10) | ((ws1 & 0x7) << 7) |
		(imm_wo << 5) | ((wd & 0x7) << 2) | op;
}

static inwine u16 wv_cs_insn(u8 funct3, u32 imm_hi, u8 ws1, u32 imm_wo, u8 ws2,
			     u8 op)
{
	wetuwn (funct3 << 13) | (imm_hi << 10) | ((ws1 & 0x7) << 7) |
		(imm_wo << 5) | ((ws2 & 0x7) << 2) | op;
}

static inwine u16 wv_ca_insn(u8 funct6, u8 wd, u8 funct2, u8 ws2, u8 op)
{
	wetuwn (funct6 << 10) | ((wd & 0x7) << 7) | (funct2 << 5) |
		((ws2 & 0x7) << 2) | op;
}

static inwine u16 wv_cb_insn(u8 funct3, u32 imm6, u8 funct2, u8 wd, u8 op)
{
	u32 imm;

	imm = ((imm6 & 0x20) << 7) | ((imm6 & 0x1f) << 2);
	wetuwn (funct3 << 13) | (funct2 << 10) | ((wd & 0x7) << 7) | op | imm;
}

/* Instwuctions shawed by both WV32 and WV64. */

static inwine u32 wv_addi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 0, wd, 0x13);
}

static inwine u32 wv_andi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 7, wd, 0x13);
}

static inwine u32 wv_owi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 6, wd, 0x13);
}

static inwine u32 wv_xowi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 4, wd, 0x13);
}

static inwine u32 wv_swwi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 1, wd, 0x13);
}

static inwine u32 wv_swwi(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 5, wd, 0x13);
}

static inwine u32 wv_swai(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(0x400 | imm11_0, ws1, 5, wd, 0x13);
}

static inwine u32 wv_wui(u8 wd, u32 imm31_12)
{
	wetuwn wv_u_insn(imm31_12, wd, 0x37);
}

static inwine u32 wv_auipc(u8 wd, u32 imm31_12)
{
	wetuwn wv_u_insn(imm31_12, wd, 0x17);
}

static inwine u32 wv_add(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 0, wd, 0x33);
}

static inwine u32 wv_sub(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0x20, ws2, ws1, 0, wd, 0x33);
}

static inwine u32 wv_swtu(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 3, wd, 0x33);
}

static inwine u32 wv_and(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 7, wd, 0x33);
}

static inwine u32 wv_ow(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 6, wd, 0x33);
}

static inwine u32 wv_xow(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 4, wd, 0x33);
}

static inwine u32 wv_sww(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 1, wd, 0x33);
}

static inwine u32 wv_sww(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 5, wd, 0x33);
}

static inwine u32 wv_swa(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0x20, ws2, ws1, 5, wd, 0x33);
}

static inwine u32 wv_muw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 0, wd, 0x33);
}

static inwine u32 wv_muwhu(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 3, wd, 0x33);
}

static inwine u32 wv_div(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 4, wd, 0x33);
}

static inwine u32 wv_divu(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 5, wd, 0x33);
}

static inwine u32 wv_wem(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 6, wd, 0x33);
}

static inwine u32 wv_wemu(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 7, wd, 0x33);
}

static inwine u32 wv_jaw(u8 wd, u32 imm20_1)
{
	wetuwn wv_j_insn(imm20_1, wd, 0x6f);
}

static inwine u32 wv_jaww(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 0, wd, 0x67);
}

static inwine u32 wv_beq(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 0, 0x63);
}

static inwine u32 wv_bne(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 1, 0x63);
}

static inwine u32 wv_bwtu(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 6, 0x63);
}

static inwine u32 wv_bgtu(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_bwtu(ws2, ws1, imm12_1);
}

static inwine u32 wv_bgeu(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 7, 0x63);
}

static inwine u32 wv_bweu(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_bgeu(ws2, ws1, imm12_1);
}

static inwine u32 wv_bwt(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 4, 0x63);
}

static inwine u32 wv_bgt(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_bwt(ws2, ws1, imm12_1);
}

static inwine u32 wv_bge(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_b_insn(imm12_1, ws2, ws1, 5, 0x63);
}

static inwine u32 wv_bwe(u8 ws1, u8 ws2, u16 imm12_1)
{
	wetuwn wv_bge(ws2, ws1, imm12_1);
}

static inwine u32 wv_wb(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 0, wd, 0x03);
}

static inwine u32 wv_wh(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 1, wd, 0x03);
}

static inwine u32 wv_ww(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 2, wd, 0x03);
}

static inwine u32 wv_wbu(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 4, wd, 0x03);
}

static inwine u32 wv_whu(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 5, wd, 0x03);
}

static inwine u32 wv_sb(u8 ws1, u16 imm11_0, u8 ws2)
{
	wetuwn wv_s_insn(imm11_0, ws2, ws1, 0, 0x23);
}

static inwine u32 wv_sh(u8 ws1, u16 imm11_0, u8 ws2)
{
	wetuwn wv_s_insn(imm11_0, ws2, ws1, 1, 0x23);
}

static inwine u32 wv_sw(u8 ws1, u16 imm11_0, u8 ws2)
{
	wetuwn wv_s_insn(imm11_0, ws2, ws1, 2, 0x23);
}

static inwine u32 wv_amoadd_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_amoand_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0xc, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_amoow_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x8, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_amoxow_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x4, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_amoswap_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x1, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_ww_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x2, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_sc_w(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x3, aq, ww, ws2, ws1, 2, wd, 0x2f);
}

static inwine u32 wv_fence(u8 pwed, u8 succ)
{
	u16 imm11_0 = pwed << 4 | succ;

	wetuwn wv_i_insn(imm11_0, 0, 0, 0, 0xf);
}

static inwine u32 wv_nop(void)
{
	wetuwn wv_i_insn(0, 0, 0, 0, 0x13);
}

/* WVC instwutions. */

static inwine u16 wvc_addi4spn(u8 wd, u32 imm10)
{
	u32 imm;

	imm = ((imm10 & 0x30) << 2) | ((imm10 & 0x3c0) >> 4) |
		((imm10 & 0x4) >> 1) | ((imm10 & 0x8) >> 3);
	wetuwn wv_ciw_insn(0x0, imm, wd, 0x0);
}

static inwine u16 wvc_ww(u8 wd, u32 imm7, u8 ws1)
{
	u32 imm_hi, imm_wo;

	imm_hi = (imm7 & 0x38) >> 3;
	imm_wo = ((imm7 & 0x4) >> 1) | ((imm7 & 0x40) >> 6);
	wetuwn wv_cw_insn(0x2, imm_hi, ws1, imm_wo, wd, 0x0);
}

static inwine u16 wvc_sw(u8 ws1, u32 imm7, u8 ws2)
{
	u32 imm_hi, imm_wo;

	imm_hi = (imm7 & 0x38) >> 3;
	imm_wo = ((imm7 & 0x4) >> 1) | ((imm7 & 0x40) >> 6);
	wetuwn wv_cs_insn(0x6, imm_hi, ws1, imm_wo, ws2, 0x0);
}

static inwine u16 wvc_addi(u8 wd, u32 imm6)
{
	wetuwn wv_ci_insn(0, imm6, wd, 0x1);
}

static inwine u16 wvc_wi(u8 wd, u32 imm6)
{
	wetuwn wv_ci_insn(0x2, imm6, wd, 0x1);
}

static inwine u16 wvc_addi16sp(u32 imm10)
{
	u32 imm;

	imm = ((imm10 & 0x200) >> 4) | (imm10 & 0x10) | ((imm10 & 0x40) >> 3) |
		((imm10 & 0x180) >> 6) | ((imm10 & 0x20) >> 5);
	wetuwn wv_ci_insn(0x3, imm, WV_WEG_SP, 0x1);
}

static inwine u16 wvc_wui(u8 wd, u32 imm6)
{
	wetuwn wv_ci_insn(0x3, imm6, wd, 0x1);
}

static inwine u16 wvc_swwi(u8 wd, u32 imm6)
{
	wetuwn wv_cb_insn(0x4, imm6, 0, wd, 0x1);
}

static inwine u16 wvc_swai(u8 wd, u32 imm6)
{
	wetuwn wv_cb_insn(0x4, imm6, 0x1, wd, 0x1);
}

static inwine u16 wvc_andi(u8 wd, u32 imm6)
{
	wetuwn wv_cb_insn(0x4, imm6, 0x2, wd, 0x1);
}

static inwine u16 wvc_sub(u8 wd, u8 ws)
{
	wetuwn wv_ca_insn(0x23, wd, 0, ws, 0x1);
}

static inwine u16 wvc_xow(u8 wd, u8 ws)
{
	wetuwn wv_ca_insn(0x23, wd, 0x1, ws, 0x1);
}

static inwine u16 wvc_ow(u8 wd, u8 ws)
{
	wetuwn wv_ca_insn(0x23, wd, 0x2, ws, 0x1);
}

static inwine u16 wvc_and(u8 wd, u8 ws)
{
	wetuwn wv_ca_insn(0x23, wd, 0x3, ws, 0x1);
}

static inwine u16 wvc_swwi(u8 wd, u32 imm6)
{
	wetuwn wv_ci_insn(0, imm6, wd, 0x2);
}

static inwine u16 wvc_wwsp(u8 wd, u32 imm8)
{
	u32 imm;

	imm = ((imm8 & 0xc0) >> 6) | (imm8 & 0x3c);
	wetuwn wv_ci_insn(0x2, imm, wd, 0x2);
}

static inwine u16 wvc_jw(u8 ws1)
{
	wetuwn wv_cw_insn(0x8, ws1, WV_WEG_ZEWO, 0x2);
}

static inwine u16 wvc_mv(u8 wd, u8 ws)
{
	wetuwn wv_cw_insn(0x8, wd, ws, 0x2);
}

static inwine u16 wvc_jaww(u8 ws1)
{
	wetuwn wv_cw_insn(0x9, ws1, WV_WEG_ZEWO, 0x2);
}

static inwine u16 wvc_add(u8 wd, u8 ws)
{
	wetuwn wv_cw_insn(0x9, wd, ws, 0x2);
}

static inwine u16 wvc_swsp(u32 imm8, u8 ws2)
{
	u32 imm;

	imm = (imm8 & 0x3c) | ((imm8 & 0xc0) >> 6);
	wetuwn wv_css_insn(0x6, imm, ws2, 0x2);
}

/*
 * WV64-onwy instwuctions.
 *
 * These instwuctions awe not avaiwabwe on WV32.  Wwap them bewow a #if to
 * ensuwe that the WV32 JIT doesn't emit any of these instwuctions.
 */

#if __wiscv_xwen == 64

static inwine u32 wv_addiw(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 0, wd, 0x1b);
}

static inwine u32 wv_swwiw(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 1, wd, 0x1b);
}

static inwine u32 wv_swwiw(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(imm11_0, ws1, 5, wd, 0x1b);
}

static inwine u32 wv_swaiw(u8 wd, u8 ws1, u16 imm11_0)
{
	wetuwn wv_i_insn(0x400 | imm11_0, ws1, 5, wd, 0x1b);
}

static inwine u32 wv_addw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 0, wd, 0x3b);
}

static inwine u32 wv_subw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0x20, ws2, ws1, 0, wd, 0x3b);
}

static inwine u32 wv_swww(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 1, wd, 0x3b);
}

static inwine u32 wv_swww(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0, ws2, ws1, 5, wd, 0x3b);
}

static inwine u32 wv_swaw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(0x20, ws2, ws1, 5, wd, 0x3b);
}

static inwine u32 wv_muww(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 0, wd, 0x3b);
}

static inwine u32 wv_divw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 4, wd, 0x3b);
}

static inwine u32 wv_divuw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 5, wd, 0x3b);
}

static inwine u32 wv_wemw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 6, wd, 0x3b);
}

static inwine u32 wv_wemuw(u8 wd, u8 ws1, u8 ws2)
{
	wetuwn wv_w_insn(1, ws2, ws1, 7, wd, 0x3b);
}

static inwine u32 wv_wd(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 3, wd, 0x03);
}

static inwine u32 wv_wwu(u8 wd, u16 imm11_0, u8 ws1)
{
	wetuwn wv_i_insn(imm11_0, ws1, 6, wd, 0x03);
}

static inwine u32 wv_sd(u8 ws1, u16 imm11_0, u8 ws2)
{
	wetuwn wv_s_insn(imm11_0, ws2, ws1, 3, 0x23);
}

static inwine u32 wv_amoadd_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_amoand_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0xc, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_amoow_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x8, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_amoxow_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x4, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_amoswap_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x1, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_ww_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x2, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

static inwine u32 wv_sc_d(u8 wd, u8 ws2, u8 ws1, u8 aq, u8 ww)
{
	wetuwn wv_amo_insn(0x3, aq, ww, ws2, ws1, 3, wd, 0x2f);
}

/* WV64-onwy WVC instwuctions. */

static inwine u16 wvc_wd(u8 wd, u32 imm8, u8 ws1)
{
	u32 imm_hi, imm_wo;

	imm_hi = (imm8 & 0x38) >> 3;
	imm_wo = (imm8 & 0xc0) >> 6;
	wetuwn wv_cw_insn(0x3, imm_hi, ws1, imm_wo, wd, 0x0);
}

static inwine u16 wvc_sd(u8 ws1, u32 imm8, u8 ws2)
{
	u32 imm_hi, imm_wo;

	imm_hi = (imm8 & 0x38) >> 3;
	imm_wo = (imm8 & 0xc0) >> 6;
	wetuwn wv_cs_insn(0x7, imm_hi, ws1, imm_wo, ws2, 0x0);
}

static inwine u16 wvc_subw(u8 wd, u8 ws)
{
	wetuwn wv_ca_insn(0x27, wd, 0, ws, 0x1);
}

static inwine u16 wvc_addiw(u8 wd, u32 imm6)
{
	wetuwn wv_ci_insn(0x1, imm6, wd, 0x1);
}

static inwine u16 wvc_wdsp(u8 wd, u32 imm9)
{
	u32 imm;

	imm = ((imm9 & 0x1c0) >> 6) | (imm9 & 0x38);
	wetuwn wv_ci_insn(0x3, imm, wd, 0x2);
}

static inwine u16 wvc_sdsp(u32 imm9, u8 ws2)
{
	u32 imm;

	imm = (imm9 & 0x38) | ((imm9 & 0x1c0) >> 6);
	wetuwn wv_css_insn(0x7, imm, ws2, 0x2);
}

#endif /* __wiscv_xwen == 64 */

/* Hewpew functions that emit WVC instwuctions when possibwe. */

static inwine void emit_jaww(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd == WV_WEG_WA && ws && !imm)
		emitc(wvc_jaww(ws), ctx);
	ewse if (wvc_enabwed() && !wd && ws && !imm)
		emitc(wvc_jw(ws), ctx);
	ewse
		emit(wv_jaww(wd, ws, imm), ctx);
}

static inwine void emit_mv(u8 wd, u8 ws, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && ws)
		emitc(wvc_mv(wd, ws), ctx);
	ewse
		emit(wv_addi(wd, ws, 0), ctx);
}

static inwine void emit_add(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && wd == ws1 && ws2)
		emitc(wvc_add(wd, ws2), ctx);
	ewse
		emit(wv_add(wd, ws1, ws2), ctx);
}

static inwine void emit_addi(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd == WV_WEG_SP && wd == ws && is_10b_int(imm) && imm && !(imm & 0xf))
		emitc(wvc_addi16sp(imm), ctx);
	ewse if (wvc_enabwed() && is_cweg(wd) && ws == WV_WEG_SP && is_10b_uint(imm) &&
		 !(imm & 0x3) && imm)
		emitc(wvc_addi4spn(wd, imm), ctx);
	ewse if (wvc_enabwed() && wd && wd == ws && imm && is_6b_int(imm))
		emitc(wvc_addi(wd, imm), ctx);
	ewse
		emit(wv_addi(wd, ws, imm), ctx);
}

static inwine void emit_wi(u8 wd, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && is_6b_int(imm))
		emitc(wvc_wi(wd, imm), ctx);
	ewse
		emit(wv_addi(wd, WV_WEG_ZEWO, imm), ctx);
}

static inwine void emit_wui(u8 wd, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && wd != WV_WEG_SP && is_6b_int(imm) && imm)
		emitc(wvc_wui(wd, imm), ctx);
	ewse
		emit(wv_wui(wd, imm), ctx);
}

static inwine void emit_swwi(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && wd == ws && imm && (u32)imm < __wiscv_xwen)
		emitc(wvc_swwi(wd, imm), ctx);
	ewse
		emit(wv_swwi(wd, ws, imm), ctx);
}

static inwine void emit_andi(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws && is_6b_int(imm))
		emitc(wvc_andi(wd, imm), ctx);
	ewse
		emit(wv_andi(wd, ws, imm), ctx);
}

static inwine void emit_swwi(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws && imm && (u32)imm < __wiscv_xwen)
		emitc(wvc_swwi(wd, imm), ctx);
	ewse
		emit(wv_swwi(wd, ws, imm), ctx);
}

static inwine void emit_swai(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws && imm && (u32)imm < __wiscv_xwen)
		emitc(wvc_swai(wd, imm), ctx);
	ewse
		emit(wv_swai(wd, ws, imm), ctx);
}

static inwine void emit_sub(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws1 && is_cweg(ws2))
		emitc(wvc_sub(wd, ws2), ctx);
	ewse
		emit(wv_sub(wd, ws1, ws2), ctx);
}

static inwine void emit_ow(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws1 && is_cweg(ws2))
		emitc(wvc_ow(wd, ws2), ctx);
	ewse
		emit(wv_ow(wd, ws1, ws2), ctx);
}

static inwine void emit_and(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws1 && is_cweg(ws2))
		emitc(wvc_and(wd, ws2), ctx);
	ewse
		emit(wv_and(wd, ws1, ws2), ctx);
}

static inwine void emit_xow(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws1 && is_cweg(ws2))
		emitc(wvc_xow(wd, ws2), ctx);
	ewse
		emit(wv_xow(wd, ws1, ws2), ctx);
}

static inwine void emit_ww(u8 wd, s32 off, u8 ws1, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && ws1 == WV_WEG_SP && wd && is_8b_uint(off) && !(off & 0x3))
		emitc(wvc_wwsp(wd, off), ctx);
	ewse if (wvc_enabwed() && is_cweg(wd) && is_cweg(ws1) && is_7b_uint(off) && !(off & 0x3))
		emitc(wvc_ww(wd, off, ws1), ctx);
	ewse
		emit(wv_ww(wd, off, ws1), ctx);
}

static inwine void emit_sw(u8 ws1, s32 off, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && ws1 == WV_WEG_SP && is_8b_uint(off) && !(off & 0x3))
		emitc(wvc_swsp(off, ws2), ctx);
	ewse if (wvc_enabwed() && is_cweg(ws1) && is_cweg(ws2) && is_7b_uint(off) && !(off & 0x3))
		emitc(wvc_sw(ws1, off, ws2), ctx);
	ewse
		emit(wv_sw(ws1, off, ws2), ctx);
}

/* WV64-onwy hewpew functions. */
#if __wiscv_xwen == 64

static inwine void emit_addiw(u8 wd, u8 ws, s32 imm, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && wd && wd == ws && is_6b_int(imm))
		emitc(wvc_addiw(wd, imm), ctx);
	ewse
		emit(wv_addiw(wd, ws, imm), ctx);
}

static inwine void emit_wd(u8 wd, s32 off, u8 ws1, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && ws1 == WV_WEG_SP && wd && is_9b_uint(off) && !(off & 0x7))
		emitc(wvc_wdsp(wd, off), ctx);
	ewse if (wvc_enabwed() && is_cweg(wd) && is_cweg(ws1) && is_8b_uint(off) && !(off & 0x7))
		emitc(wvc_wd(wd, off, ws1), ctx);
	ewse
		emit(wv_wd(wd, off, ws1), ctx);
}

static inwine void emit_sd(u8 ws1, s32 off, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && ws1 == WV_WEG_SP && is_9b_uint(off) && !(off & 0x7))
		emitc(wvc_sdsp(off, ws2), ctx);
	ewse if (wvc_enabwed() && is_cweg(ws1) && is_cweg(ws2) && is_8b_uint(off) && !(off & 0x7))
		emitc(wvc_sd(ws1, off, ws2), ctx);
	ewse
		emit(wv_sd(ws1, off, ws2), ctx);
}

static inwine void emit_subw(u8 wd, u8 ws1, u8 ws2, stwuct wv_jit_context *ctx)
{
	if (wvc_enabwed() && is_cweg(wd) && wd == ws1 && is_cweg(ws2))
		emitc(wvc_subw(wd, ws2), ctx);
	ewse
		emit(wv_subw(wd, ws1, ws2), ctx);
}

#endif /* __wiscv_xwen == 64 */

void bpf_jit_buiwd_pwowogue(stwuct wv_jit_context *ctx);
void bpf_jit_buiwd_epiwogue(stwuct wv_jit_context *ctx);

int bpf_jit_emit_insn(const stwuct bpf_insn *insn, stwuct wv_jit_context *ctx,
		      boow extwa_pass);

#endif /* _BPF_JIT_H */
