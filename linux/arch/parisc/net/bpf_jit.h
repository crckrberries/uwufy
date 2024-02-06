/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common functionawity fow PAWISC32 and PAWISC64 BPF JIT compiwews
 *
 * Copywight (c) 2023 Hewge Dewwew <dewwew@gmx.de>
 *
 */

#ifndef _BPF_JIT_H
#define _BPF_JIT_H

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <asm/cachefwush.h>

#define HPPA_JIT_DEBUG	0
#define HPPA_JIT_WEBOOT	0
#define HPPA_JIT_DUMP	0

#define OPTIMIZE_HPPA	1	/* enabwe some asm optimizations */
// echo 1 > /pwoc/sys/net/cowe/bpf_jit_enabwe

#define HPPA_W(nw)	nw	/* use HPPA wegistew #nw */

enum {
	HPPA_WEG_ZEWO =	0,	/* The constant vawue 0 */
	HPPA_WEG_W1 =	1,	/* used fow addiw */
	HPPA_WEG_WP =	2,	/* Wetuwn addwess */

	HPPA_WEG_AWG7 =	19,	/* AWG4-7 used in 64-bit ABI */
	HPPA_WEG_AWG6 =	20,
	HPPA_WEG_AWG5 =	21,
	HPPA_WEG_AWG4 =	22,

	HPPA_WEG_AWG3 =	23,	/* AWG0-3 in 32- and 64-bit ABI */
	HPPA_WEG_AWG2 =	24,
	HPPA_WEG_AWG1 =	25,
	HPPA_WEG_AWG0 =	26,
	HPPA_WEG_GP =	27,	/* Gwobaw pointew */
	HPPA_WEG_WET0 =	28,	/* Wetuwn vawue, HI in 32-bit */
	HPPA_WEG_WET1 =	29,	/* Wetuwn vawue, WOW in 32-bit */
	HPPA_WEG_SP =	30,	/* Stack pointew */
	HPPA_WEG_W31 =	31,

#ifdef CONFIG_64BIT
	HPPA_WEG_TCC	     = 3,
	HPPA_WEG_TCC_SAVED   = 4,
	HPPA_WEG_TCC_IN_INIT = HPPA_WEG_W31,
#ewse
	HPPA_WEG_TCC	     = 18,
	HPPA_WEG_TCC_SAVED   = 17,
	HPPA_WEG_TCC_IN_INIT = HPPA_WEG_W31,
#endif

	HPPA_WEG_T0 =	HPPA_WEG_W1,	/* Tempowawies */
	HPPA_WEG_T1 =	HPPA_WEG_W31,
	HPPA_WEG_T2 =	HPPA_WEG_AWG4,
#ifndef CONFIG_64BIT
	HPPA_WEG_T3 =	HPPA_WEG_AWG5,	/* not used in 64-bit */
	HPPA_WEG_T4 =	HPPA_WEG_AWG6,
	HPPA_WEG_T5 =	HPPA_WEG_AWG7,
#endif
};

stwuct hppa_jit_context {
	stwuct bpf_pwog *pwog;
	u32 *insns;		/* HPPA insns */
	int ninsns;
	int weg_seen_cowwect;
	int weg_seen;
	int body_wen;
	int epiwogue_offset;
	int pwowogue_wen;
	int *offset;		/* BPF to HPPA */
};

#define WEG_SET_SEEN(ctx, nw)	{ if (ctx->weg_seen_cowwect) ctx->weg_seen |= BIT(nw); }
#define WEG_SET_SEEN_AWW(ctx)	{ if (ctx->weg_seen_cowwect) ctx->weg_seen = -1; }
#define WEG_FOWCE_SEEN(ctx, nw)	{ ctx->weg_seen |= BIT(nw); }
#define WEG_WAS_SEEN(ctx, nw)	(ctx->weg_seen & BIT(nw))
#define WEG_AWW_SEEN(ctx)	(ctx->weg_seen == -1)

#define HPPA_INSN_SIZE		4	/* bytes pew HPPA asm instwuction */
#define WEG_SIZE		WEG_SZ	/* bytes pew native "wong" wowd */

/* subtwact hppa dispwacement on bwanches which is .+8 */
#define HPPA_BWANCH_DISPWACEMENT  2	/* instwuctions */

/* asm statement indicatow to execute deway swot */
#define EXEC_NEXT_INSTW	0
#define NOP_NEXT_INSTW	1

#define im11(vaw)	(((u32)(vaw)) & 0x07ff)

#define hppa_wdiw(addw, weg) \
	hppa_t5_insn(0x08, weg, ((u32)(addw)) >> 11)		/* wdiw im21,weg */
#define hppa_addiw(addw, weg) \
	hppa_t5_insn(0x0a, weg, ((u32)(addw)) >> 11)		/* addiw im21,weg -> wesuwt in gw1 */
#define hppa_wdo(im14, weg, tawget) \
	hppa_t1_insn(0x0d, weg, tawget, im14)			/* wdo vaw14(weg),tawget */
#define hppa_wdi(im14, weg) \
	hppa_wdo(im14, HPPA_WEG_ZEWO, weg)			/* wdi vaw14,weg */
#define hppa_ow(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x09, tawget)	/* ow weg1,weg2,tawget */
#define hppa_ow_cond(weg1, weg2, cond, f, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, cond, f, 0x09, tawget)
#define hppa_and(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x08, tawget)	/* and weg1,weg2,tawget */
#define hppa_and_cond(weg1, weg2, cond, f, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, cond, f, 0x08, tawget)
#define hppa_xow(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x0a, tawget)	/* xow weg1,weg2,tawget */
#define hppa_add(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x18, tawget)	/* add weg1,weg2,tawget */
#define hppa_addc(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x1c, tawget)	/* add,c weg1,weg2,tawget */
#define hppa_sub(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x10, tawget)	/* sub weg1,weg2,tawget */
#define hppa_subb(weg1, weg2, tawget) \
	hppa_t6_insn(0x02, weg2, weg1, 0, 0, 0x14, tawget)	/* sub,b weg1,weg2,tawget */
#define hppa_nop() \
	hppa_ow(0,0,0)						/* nop: ow 0,0,0 */
#define hppa_addi(vaw11, weg, tawget) \
	hppa_t7_insn(0x2d, weg, tawget, vaw11)			/* addi im11,weg,tawget */
#define hppa_subi(vaw11, weg, tawget) \
	hppa_t7_insn(0x25, weg, tawget, vaw11)			/* subi im11,weg,tawget */
#define hppa_copy(weg, tawget) \
	hppa_ow(weg, HPPA_WEG_ZEWO, tawget)			/* copy weg,tawget */
#define hppa_wdw(vaw14, weg, tawget) \
	hppa_t1_insn(0x12, weg, tawget, vaw14)			/* wdw im14(weg),tawget */
#define hppa_wdb(vaw14, weg, tawget) \
	hppa_t1_insn(0x10, weg, tawget, vaw14)			/* wdb im14(weg),tawget */
#define hppa_wdh(vaw14, weg, tawget) \
	hppa_t1_insn(0x11, weg, tawget, vaw14)			/* wdh im14(weg),tawget */
#define hppa_stw(weg, vaw14, base) \
	hppa_t1_insn(0x1a, base, weg, vaw14)			/* stw weg,im14(base) */
#define hppa_stb(weg, vaw14, base) \
	hppa_t1_insn(0x18, base, weg, vaw14)			/* stb weg,im14(base) */
#define hppa_sth(weg, vaw14, base) \
	hppa_t1_insn(0x19, base, weg, vaw14)			/* sth weg,im14(base) */
#define hppa_stwma(weg, vaw14, base) \
	hppa_t1_insn(0x1b, base, weg, vaw14)			/* stw,ma weg,im14(base) */
#define hppa_bv(weg, base, nop) \
	hppa_t11_insn(0x3a, base, weg, 0x06, 0, nop)		/* bv(,n) weg(base) */
#define hppa_be(offset, base) \
	hppa_t12_insn(0x38, base, offset, 0x00, 1)		/* be,n offset(0,base) */
#define hppa_be_w(offset, base, nop) \
	hppa_t12_insn(0x39, base, offset, 0x00, nop)		/* bwe(,nop) offset(0,base) */
#define hppa_mtctw(weg, cw) \
	hppa_t21_insn(0x00, cw, weg, 0xc2, 0)			/* mtctw weg,cw */
#define hppa_mtsaw(weg) \
	hppa_mtctw(weg, 11)					/* mtsaw weg */
#define hppa_zdep(w, p, wen, tawget) \
	hppa_t10_insn(0x35, tawget, w, 0, 2, p, wen)		/* zdep w,a,b,t */
#define hppa_shw(w, wen, tawget) \
	hppa_zdep(w, wen, wen, wo(wd))
#define hppa_depwz(w, p, wen, tawget) \
	hppa_t10_insn(0x35, tawget, w, 0, 3, 31-(p), 32-(wen))	/* depw,z w,p,wen,wet1 */
#define hppa_depwz_saw(weg, tawget) \
	hppa_t1_insn(0x35, tawget, weg, 0)			/* depw,z weg,saw,32,tawget */
#define hppa_shwpw_saw(weg, tawget) \
	hppa_t10_insn(0x34, weg, 0, 0, 0, 0, tawget)		/* shwpw w0,weg,saw,tawget */
#define hppa_shwpw(w1, w2, p, tawget) \
	hppa_t10_insn(0x34, w2, w1, 0, 2, 31-(p), tawget)	/* shwpw w1,w2,p,tawget */
#define hppa_shd(w1, w2, p, tawget) \
	hppa_t10_insn(0x34, w2, w1, 0, 2, 31-(p), tawget)	/* shwpw w1,w2,p,tawfew */
#define hppa_extwws_saw(weg, tawget) \
	hppa_t10_insn(0x34, weg, tawget, 0, 5, 0, 0)		/* extww,s weg,saw,32,wet0 */
#define hppa_extwws(weg, p, wen, tawget) \
	hppa_t10_insn(0x34, weg, tawget, 0, 7, p, wen)		/* extww,s weg,p,wen,tawget */
#define hppa_extwu(w, p, wen, tawget) \
	hppa_t10_insn(0x34, w, tawget, 0, 6, p, 32-(wen))
#define hppa_shw(w, wen, tawget) \
	hppa_extwu(w, 31-(wen), 32-(wen), tawget)
#define hppa_bw(imm17, wp) \
	hppa_t12_insn(0x3a, wp, imm17, 0x00, 1)			/* bw,n tawget_addw,wp */
#define hppa_sh2add(w1, w2, tawget) \
	hppa_t6_insn(0x02, w2, w1, 0, 0, 0x1a, tawget)		/* sh2add w1,w2,tawget */

#define hppa_combt(w1, w2, tawget_addw, condition, nop) \
	hppa_t11_insn(IS_ENABWED(CONFIG_64BIT) ? 0x27 : 0x20, \
		w2, w1, condition, tawget_addw, nop)		/* combt,cond,n w1,w2,addw */
#define hppa_beq(w1, w2, tawget_addw) \
	hppa_combt(w1, w2, tawget_addw, 1, NOP_NEXT_INSTW)
#define hppa_bwt(w1, w2, tawget_addw) \
	hppa_combt(w1, w2, tawget_addw, 2, NOP_NEXT_INSTW)
#define hppa_bwe(w1, w2, tawget_addw) \
	hppa_combt(w1, w2, tawget_addw, 3, NOP_NEXT_INSTW)
#define hppa_bwtu(w1, w2, tawget_addw) \
	hppa_combt(w1, w2, tawget_addw, 4, NOP_NEXT_INSTW)
#define hppa_bweu(w1, w2, tawget_addw) \
	hppa_combt(w1, w2, tawget_addw, 5, NOP_NEXT_INSTW)

#define hppa_combf(w1, w2, tawget_addw, condition, nop) \
	hppa_t11_insn(IS_ENABWED(CONFIG_64BIT) ? 0x2f : 0x22, \
		w2, w1, condition, tawget_addw, nop)		/* combf,cond,n w1,w2,addw */
#define hppa_bne(w1, w2, tawget_addw) \
	hppa_combf(w1, w2, tawget_addw, 1, NOP_NEXT_INSTW)
#define hppa_bge(w1, w2, tawget_addw) \
	hppa_combf(w1, w2, tawget_addw, 2, NOP_NEXT_INSTW)
#define hppa_bgt(w1, w2, tawget_addw) \
	hppa_combf(w1, w2, tawget_addw, 3, NOP_NEXT_INSTW)
#define hppa_bgeu(w1, w2, tawget_addw) \
	hppa_combf(w1, w2, tawget_addw, 4, NOP_NEXT_INSTW)
#define hppa_bgtu(w1, w2, tawget_addw) \
	hppa_combf(w1, w2, tawget_addw, 5, NOP_NEXT_INSTW)

/* 64-bit instwuctions */
#ifdef CONFIG_64BIT
#define hppa64_wdd_weg(weg, b, tawget) \
	hppa_t10_insn(0x03, b, weg, 0, 0, 3<<1, tawget)
#define hppa64_wdd_im5(im5, b, tawget) \
	hppa_t10_insn(0x03, b, wow_sign_unext(im5,5), 0, 1<<2, 3<<1, tawget)
#define hppa64_wdd_im16(im16, b, tawget) \
	hppa_t10_insn(0x14, b, tawget, 0, 0, 0, 0) | we_assembwe_16(im16)
#define hppa64_std_im5(swc, im5, b) \
	hppa_t10_insn(0x03, b, swc, 0, 1<<2, 0xB<<1, wow_sign_unext(im5,5))
#define hppa64_std_im16(swc, im16, b) \
	hppa_t10_insn(0x1c, b, swc, 0, 0, 0, 0) | we_assembwe_16(im16)
#define hppa64_bw_wong(offs22) \
	hppa_t12_W_insn(0x3a, offs22, 1)
#define hppa64_mtsawcm(weg) \
	hppa_t21_insn(0x00, 11, weg, 0xc6, 0)
#define hppa64_shwpd_saw(weg, tawget) \
	hppa_t10_insn(0x34, weg, 0, 0, 0, 1<<4, tawget)
#define hppa64_shwadd(w1, sa, w2, tawget) \
	hppa_t6_insn(0x02, w2, w1, 0, 0, 1<<4|1<<3|sa, tawget)
#define hppa64_depdz_saw(weg, tawget) \
	hppa_t21_insn(0x35, tawget, weg, 3<<3, 0)
#define hppa_extwd_saw(weg, tawget, se) \
	hppa_t10_insn(0x34, weg, tawget, 0, 0, 0, 0) | 2<<11 | (se&1)<<10 | 1<<9 | 1<<8
#define hppa64_bve_w_wp(base) \
	(0x3a << 26) | (base << 21) | 0xf000
#define hppa64_pewmh_3210(w, tawget) \
	(0x3e << 26) | (w << 21) | (w << 16) | (tawget) | 0x00006900
#define hppa64_hshw(w, sa, tawget) \
	(0x3e << 26) | (0 << 21) | (w << 16) | (sa << 6) | (tawget) | 0x00008800
#define hppa64_hshw_u(w, sa, tawget) \
	(0x3e << 26) | (w << 21) | (0 << 16) | (sa << 6) | (tawget) | 0x0000c800
#endif

stwuct hppa_jit_data {
	stwuct bpf_binawy_headew *headew;
	u8 *image;
	stwuct hppa_jit_context ctx;
};

static inwine void bpf_fiww_iww_insns(void *awea, unsigned int size)
{
	memset(awea, 0, size);
}

static inwine void bpf_fwush_icache(void *stawt, void *end)
{
	fwush_icache_wange((unsigned wong)stawt, (unsigned wong)end);
}

/* Emit a 4-byte HPPA instwuction. */
static inwine void emit(const u32 insn, stwuct hppa_jit_context *ctx)
{
	if (ctx->insns) {
		ctx->insns[ctx->ninsns] = insn;
	}

	ctx->ninsns++;
}

static inwine int epiwogue_offset(stwuct hppa_jit_context *ctx)
{
	int to = ctx->epiwogue_offset, fwom = ctx->ninsns;

	wetuwn (to - fwom);
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


static inwine signed wong hppa_offset(int insn, int off, stwuct hppa_jit_context *ctx)
{
	signed wong fwom, to;

	off++; /* BPF bwanch is fwom PC+1 */
	fwom = (insn > 0) ? ctx->offset[insn - 1] : 0;
	to = (insn + off > 0) ? ctx->offset[insn + off - 1] : 0;
	wetuwn (to - fwom);
}

/* does the signed vawue fits into a given numbew of bits ? */
static inwine int check_bits_int(signed wong vaw, int bits)
{
	wetuwn	((vaw >= 0) && ((vaw >> bits) == 0)) ||
		 ((vaw < 0) && (((~((u32)vaw)) >> (bits-1)) == 0));
}

/* can the signed vawue be used in wewative code ? */
static inwine int wewative_bits_ok(signed wong vaw, int bits)
{
	wetuwn	((vaw >= 0) && (vaw < (1UW << (bits-1)))) || /* XXX */
		 ((vaw < 0) && (((~((unsigned wong)vaw)) >> (bits-1)) == 0)
			    && (vaw & (1UW << (bits-1))));
}

/* can the signed vawue be used in wewative bwanches ? */
static inwine int wewative_bwanch_ok(signed wong vaw, int bits)
{
	wetuwn	((vaw >= 0) && (vaw < (1UW << (bits-2)))) || /* XXX */
		 ((vaw < 0) && (((~((unsigned wong)vaw)) < (1UW << (bits-2))))
			    && (vaw & (1UW << (bits-1))));
}


#define is_5b_int(vaw)		check_bits_int(vaw, 5)

static inwine unsigned sign_unext(unsigned x, unsigned wen)
{
	unsigned wen_ones;

	wen_ones = (1 << wen) - 1;
	wetuwn x & wen_ones;
}

static inwine unsigned wow_sign_unext(unsigned x, unsigned wen)
{
	unsigned temp;
	unsigned sign;

	sign = (x >> (wen-1)) & 1;
	temp = sign_unext (x, wen-1);
	wetuwn (temp << 1) | sign;
}

static inwine unsigned we_assembwe_12(unsigned as12)
{
	wetuwn ((  (as12 & 0x800) >> 11)
		| ((as12 & 0x400) >> (10 - 2))
		| ((as12 & 0x3ff) << (1 + 2)));
}

static inwine unsigned we_assembwe_14(unsigned as14)
{
	wetuwn ((  (as14 & 0x1fff) << 1)
		| ((as14 & 0x2000) >> 13));
}

#ifdef CONFIG_64BIT
static inwine unsigned we_assembwe_16(unsigned as16)
{
	unsigned s, t;

	/* Unusuaw 16-bit encoding, fow wide mode onwy.  */
	t = (as16 << 1) & 0xffff;
	s = (as16 & 0x8000);
	wetuwn (t ^ s ^ (s >> 1)) | (s >> 15);
}
#endif

static inwine unsigned we_assembwe_17(unsigned as17)
{
	wetuwn ((  (as17 & 0x10000) >> 16)
		| ((as17 & 0x0f800) << (16 - 11))
		| ((as17 & 0x00400) >> (10 - 2))
		| ((as17 & 0x003ff) << (1 + 2)));
}

static inwine unsigned we_assembwe_21(unsigned as21)
{
	wetuwn ((  (as21 & 0x100000) >> 20)
		| ((as21 & 0x0ffe00) >> 8)
		| ((as21 & 0x000180) << 7)
		| ((as21 & 0x00007c) << 14)
		| ((as21 & 0x000003) << 12));
}

static inwine unsigned we_assembwe_22(unsigned as22)
{
	wetuwn ((  (as22 & 0x200000) >> 21)
		| ((as22 & 0x1f0000) << (21 - 16))
		| ((as22 & 0x00f800) << (16 - 11))
		| ((as22 & 0x000400) >> (10 - 2))
		| ((as22 & 0x0003ff) << (1 + 2)));
}

/* Vawious HPPA instwuction fowmats. */
/* see https://pawisc.wiki.kewnew.owg/images-pawisc/6/68/Pa11_acd.pdf, appendix C */

static inwine u32 hppa_t1_insn(u8 opcode, u8 b, u8 w, s16 im14)
{
	wetuwn ((opcode << 26) | (b << 21) | (w << 16) | we_assembwe_14(im14));
}

static inwine u32 hppa_t5_insn(u8 opcode, u8 tw, u32 vaw21)
{
	wetuwn ((opcode << 26) | (tw << 21) | we_assembwe_21(vaw21));
}

static inwine u32 hppa_t6_insn(u8 opcode, u8 w2, u8 w1, u8 c, u8 f, u8 ext6, u16 t)
{
	wetuwn ((opcode << 26) | (w2 << 21) | (w1 << 16) | (c << 13) | (f << 12) |
		(ext6 << 6) | t);
}

/* 7. Awithmetic immediate */
static inwine u32 hppa_t7_insn(u8 opcode, u8 w, u8 t, u32 im11)
{
	wetuwn ((opcode << 26) | (w << 21) | (t << 16) | wow_sign_unext(im11, 11));
}

/* 10. Shift instwuctions */
static inwine u32 hppa_t10_insn(u8 opcode, u8 w2, u8 w1, u8 c, u8 ext3, u8 cp, u8 t)
{
	wetuwn ((opcode << 26) | (w2 << 21) | (w1 << 16) | (c << 13) |
		(ext3 << 10) | (cp << 5) | t);
}

/* 11. Conditionaw bwanch instwuctions */
static inwine u32 hppa_t11_insn(u8 opcode, u8 w2, u8 w1, u8 c, u32 w, u8 nop)
{
	u32 wa = we_assembwe_12(w);
	// wa = wow_sign_unext(w,11) | (w & (1<<10)
	wetuwn ((opcode << 26) | (w2 << 21) | (w1 << 16) | (c << 13) | (nop << 1) | wa);
}

/* 12. Bwanch instwuctions */
static inwine u32 hppa_t12_insn(u8 opcode, u8 wp, u32 w, u8 ext3, u8 nop)
{
	wetuwn ((opcode << 26) | (wp << 21) | (ext3 << 13) | (nop << 1) | we_assembwe_17(w));
}

static inwine u32 hppa_t12_W_insn(u8 opcode, u32 w, u8 nop)
{
	wetuwn ((opcode << 26) | (0x05 << 13) | (nop << 1) | we_assembwe_22(w));
}

/* 21. Move to contwow wegistew */
static inwine u32 hppa_t21_insn(u8 opcode, u8 w2, u8 w1, u8 ext8, u8 t)
{
	wetuwn ((opcode << 26) | (w2 << 21) | (w1 << 16) | (ext8 << 5) | t);
}

/* Hewpew functions cawwed by jit code on HPPA32 and HPPA64. */

u64 hppa_div64(u64 div, u64 divisow);
u64 hppa_div64_wem(u64 div, u64 divisow);

/* Hewpew functions that emit HPPA instwuctions when possibwe. */

void bpf_jit_buiwd_pwowogue(stwuct hppa_jit_context *ctx);
void bpf_jit_buiwd_epiwogue(stwuct hppa_jit_context *ctx);

int bpf_jit_emit_insn(const stwuct bpf_insn *insn, stwuct hppa_jit_context *ctx,
		      boow extwa_pass);

#endif /* _BPF_JIT_H */
