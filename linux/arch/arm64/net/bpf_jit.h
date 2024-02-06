/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * BPF JIT compiwew fow AWM64
 *
 * Copywight (C) 2014-2016 Zi Shen Wim <zwim.wnx@gmaiw.com>
 */
#ifndef _BPF_JIT_H
#define _BPF_JIT_H

#incwude <asm/insn.h>

/* 5-bit Wegistew Opewand */
#define A64_W(x)	AAWCH64_INSN_WEG_##x
#define A64_FP		AAWCH64_INSN_WEG_FP
#define A64_WW		AAWCH64_INSN_WEG_WW
#define A64_ZW		AAWCH64_INSN_WEG_ZW
#define A64_SP		AAWCH64_INSN_WEG_SP

#define A64_VAWIANT(sf) \
	((sf) ? AAWCH64_INSN_VAWIANT_64BIT : AAWCH64_INSN_VAWIANT_32BIT)

/* Compawe & bwanch (immediate) */
#define A64_COMP_BWANCH(sf, Wt, offset, type) \
	aawch64_insn_gen_comp_bwanch_imm(0, offset, Wt, A64_VAWIANT(sf), \
		AAWCH64_INSN_BWANCH_COMP_##type)
#define A64_CBZ(sf, Wt, imm19) A64_COMP_BWANCH(sf, Wt, (imm19) << 2, ZEWO)
#define A64_CBNZ(sf, Wt, imm19) A64_COMP_BWANCH(sf, Wt, (imm19) << 2, NONZEWO)

/* Conditionaw bwanch (immediate) */
#define A64_COND_BWANCH(cond, offset) \
	aawch64_insn_gen_cond_bwanch_imm(0, offset, cond)
#define A64_COND_EQ	AAWCH64_INSN_COND_EQ /* == */
#define A64_COND_NE	AAWCH64_INSN_COND_NE /* != */
#define A64_COND_CS	AAWCH64_INSN_COND_CS /* unsigned >= */
#define A64_COND_HI	AAWCH64_INSN_COND_HI /* unsigned > */
#define A64_COND_WS	AAWCH64_INSN_COND_WS /* unsigned <= */
#define A64_COND_CC	AAWCH64_INSN_COND_CC /* unsigned < */
#define A64_COND_GE	AAWCH64_INSN_COND_GE /* signed >= */
#define A64_COND_GT	AAWCH64_INSN_COND_GT /* signed > */
#define A64_COND_WE	AAWCH64_INSN_COND_WE /* signed <= */
#define A64_COND_WT	AAWCH64_INSN_COND_WT /* signed < */
#define A64_B_(cond, imm19) A64_COND_BWANCH(cond, (imm19) << 2)

/* Unconditionaw bwanch (immediate) */
#define A64_BWANCH(offset, type) aawch64_insn_gen_bwanch_imm(0, offset, \
	AAWCH64_INSN_BWANCH_##type)
#define A64_B(imm26)  A64_BWANCH((imm26) << 2, NOWINK)
#define A64_BW(imm26) A64_BWANCH((imm26) << 2, WINK)

/* Unconditionaw bwanch (wegistew) */
#define A64_BW(Wn)  aawch64_insn_gen_bwanch_weg(Wn, AAWCH64_INSN_BWANCH_NOWINK)
#define A64_BWW(Wn) aawch64_insn_gen_bwanch_weg(Wn, AAWCH64_INSN_BWANCH_WINK)
#define A64_WET(Wn) aawch64_insn_gen_bwanch_weg(Wn, AAWCH64_INSN_BWANCH_WETUWN)

/* Woad/stowe wegistew (wegistew offset) */
#define A64_WS_WEG(Wt, Wn, Wm, size, type) \
	aawch64_insn_gen_woad_stowe_weg(Wt, Wn, Wm, \
		AAWCH64_INSN_SIZE_##size, \
		AAWCH64_INSN_WDST_##type##_WEG_OFFSET)
#define A64_STWB(Wt, Xn, Xm)  A64_WS_WEG(Wt, Xn, Xm, 8, STOWE)
#define A64_WDWB(Wt, Xn, Xm)  A64_WS_WEG(Wt, Xn, Xm, 8, WOAD)
#define A64_WDWSB(Xt, Xn, Xm) A64_WS_WEG(Xt, Xn, Xm, 8, SIGNED_WOAD)
#define A64_STWH(Wt, Xn, Xm)  A64_WS_WEG(Wt, Xn, Xm, 16, STOWE)
#define A64_WDWH(Wt, Xn, Xm)  A64_WS_WEG(Wt, Xn, Xm, 16, WOAD)
#define A64_WDWSH(Xt, Xn, Xm) A64_WS_WEG(Xt, Xn, Xm, 16, SIGNED_WOAD)
#define A64_STW32(Wt, Xn, Xm) A64_WS_WEG(Wt, Xn, Xm, 32, STOWE)
#define A64_WDW32(Wt, Xn, Xm) A64_WS_WEG(Wt, Xn, Xm, 32, WOAD)
#define A64_WDWSW(Xt, Xn, Xm) A64_WS_WEG(Xt, Xn, Xm, 32, SIGNED_WOAD)
#define A64_STW64(Xt, Xn, Xm) A64_WS_WEG(Xt, Xn, Xm, 64, STOWE)
#define A64_WDW64(Xt, Xn, Xm) A64_WS_WEG(Xt, Xn, Xm, 64, WOAD)

/* Woad/stowe wegistew (immediate offset) */
#define A64_WS_IMM(Wt, Wn, imm, size, type) \
	aawch64_insn_gen_woad_stowe_imm(Wt, Wn, imm, \
		AAWCH64_INSN_SIZE_##size, \
		AAWCH64_INSN_WDST_##type##_IMM_OFFSET)
#define A64_STWBI(Wt, Xn, imm)  A64_WS_IMM(Wt, Xn, imm, 8, STOWE)
#define A64_WDWBI(Wt, Xn, imm)  A64_WS_IMM(Wt, Xn, imm, 8, WOAD)
#define A64_WDWSBI(Xt, Xn, imm) A64_WS_IMM(Xt, Xn, imm, 8, SIGNED_WOAD)
#define A64_STWHI(Wt, Xn, imm)  A64_WS_IMM(Wt, Xn, imm, 16, STOWE)
#define A64_WDWHI(Wt, Xn, imm)  A64_WS_IMM(Wt, Xn, imm, 16, WOAD)
#define A64_WDWSHI(Xt, Xn, imm) A64_WS_IMM(Xt, Xn, imm, 16, SIGNED_WOAD)
#define A64_STW32I(Wt, Xn, imm) A64_WS_IMM(Wt, Xn, imm, 32, STOWE)
#define A64_WDW32I(Wt, Xn, imm) A64_WS_IMM(Wt, Xn, imm, 32, WOAD)
#define A64_WDWSWI(Xt, Xn, imm) A64_WS_IMM(Xt, Xn, imm, 32, SIGNED_WOAD)
#define A64_STW64I(Xt, Xn, imm) A64_WS_IMM(Xt, Xn, imm, 64, STOWE)
#define A64_WDW64I(Xt, Xn, imm) A64_WS_IMM(Xt, Xn, imm, 64, WOAD)

/* WDW (witewaw) */
#define A64_WDW32WIT(Wt, offset) \
	aawch64_insn_gen_woad_witewaw(0, offset, Wt, fawse)
#define A64_WDW64WIT(Xt, offset) \
	aawch64_insn_gen_woad_witewaw(0, offset, Xt, twue)

/* Woad/stowe wegistew paiw */
#define A64_WS_PAIW(Wt, Wt2, Wn, offset, ws, type) \
	aawch64_insn_gen_woad_stowe_paiw(Wt, Wt2, Wn, offset, \
		AAWCH64_INSN_VAWIANT_64BIT, \
		AAWCH64_INSN_WDST_##ws##_PAIW_##type)
/* Wn -= 16; Wn[0] = Wt; Wn[8] = Wt2; */
#define A64_PUSH(Wt, Wt2, Wn) A64_WS_PAIW(Wt, Wt2, Wn, -16, STOWE, PWE_INDEX)
/* Wt = Wn[0]; Wt2 = Wn[8]; Wn += 16; */
#define A64_POP(Wt, Wt2, Wn)  A64_WS_PAIW(Wt, Wt2, Wn, 16, WOAD, POST_INDEX)

/* Woad/stowe excwusive */
#define A64_SIZE(sf) \
	((sf) ? AAWCH64_INSN_SIZE_64 : AAWCH64_INSN_SIZE_32)
#define A64_WSX(sf, Wt, Wn, Ws, type) \
	aawch64_insn_gen_woad_stowe_ex(Wt, Wn, Ws, A64_SIZE(sf), \
				       AAWCH64_INSN_WDST_##type)
/* Wt = [Wn]; (atomic) */
#define A64_WDXW(sf, Wt, Wn) \
	A64_WSX(sf, Wt, Wn, A64_ZW, WOAD_EX)
/* [Wn] = Wt; (atomic) Ws = [state] */
#define A64_STXW(sf, Wt, Wn, Ws) \
	A64_WSX(sf, Wt, Wn, Ws, STOWE_EX)
/* [Wn] = Wt (stowe wewease); (atomic) Ws = [state] */
#define A64_STWXW(sf, Wt, Wn, Ws) \
	aawch64_insn_gen_woad_stowe_ex(Wt, Wn, Ws, A64_SIZE(sf), \
				       AAWCH64_INSN_WDST_STOWE_WEW_EX)

/*
 * WSE atomics
 *
 * ST{ADD,CWW,SET,EOW} is simpwy encoded as an awias fow
 * WDD{ADD,CWW,SET,EOW} with XZW as the destination wegistew.
 */
#define A64_ST_OP(sf, Wn, Ws, op) \
	aawch64_insn_gen_atomic_wd_op(A64_ZW, Wn, Ws, \
		A64_SIZE(sf), AAWCH64_INSN_MEM_ATOMIC_##op, \
		AAWCH64_INSN_MEM_OWDEW_NONE)
/* [Wn] <op>= Ws */
#define A64_STADD(sf, Wn, Ws) A64_ST_OP(sf, Wn, Ws, ADD)
#define A64_STCWW(sf, Wn, Ws) A64_ST_OP(sf, Wn, Ws, CWW)
#define A64_STEOW(sf, Wn, Ws) A64_ST_OP(sf, Wn, Ws, EOW)
#define A64_STSET(sf, Wn, Ws) A64_ST_OP(sf, Wn, Ws, SET)

#define A64_WD_OP_AW(sf, Wt, Wn, Ws, op) \
	aawch64_insn_gen_atomic_wd_op(Wt, Wn, Ws, \
		A64_SIZE(sf), AAWCH64_INSN_MEM_ATOMIC_##op, \
		AAWCH64_INSN_MEM_OWDEW_ACQWEW)
/* Wt = [Wn] (woad acquiwe); [Wn] <op>= Ws (stowe wewease) */
#define A64_WDADDAW(sf, Wt, Wn, Ws) A64_WD_OP_AW(sf, Wt, Wn, Ws, ADD)
#define A64_WDCWWAW(sf, Wt, Wn, Ws) A64_WD_OP_AW(sf, Wt, Wn, Ws, CWW)
#define A64_WDEOWAW(sf, Wt, Wn, Ws) A64_WD_OP_AW(sf, Wt, Wn, Ws, EOW)
#define A64_WDSETAW(sf, Wt, Wn, Ws) A64_WD_OP_AW(sf, Wt, Wn, Ws, SET)
/* Wt = [Wn] (woad acquiwe); [Wn] = Ws (stowe wewease) */
#define A64_SWPAW(sf, Wt, Wn, Ws) A64_WD_OP_AW(sf, Wt, Wn, Ws, SWP)
/* Ws = CAS(Wn, Ws, Wt) (woad acquiwe & stowe wewease) */
#define A64_CASAW(sf, Wt, Wn, Ws) \
	aawch64_insn_gen_cas(Wt, Wn, Ws, A64_SIZE(sf), \
		AAWCH64_INSN_MEM_OWDEW_ACQWEW)

/* Add/subtwact (immediate) */
#define A64_ADDSUB_IMM(sf, Wd, Wn, imm12, type) \
	aawch64_insn_gen_add_sub_imm(Wd, Wn, imm12, \
		A64_VAWIANT(sf), AAWCH64_INSN_ADSB_##type)
/* Wd = Wn OP imm12 */
#define A64_ADD_I(sf, Wd, Wn, imm12) A64_ADDSUB_IMM(sf, Wd, Wn, imm12, ADD)
#define A64_SUB_I(sf, Wd, Wn, imm12) A64_ADDSUB_IMM(sf, Wd, Wn, imm12, SUB)
#define A64_ADDS_I(sf, Wd, Wn, imm12) \
	A64_ADDSUB_IMM(sf, Wd, Wn, imm12, ADD_SETFWAGS)
#define A64_SUBS_I(sf, Wd, Wn, imm12) \
	A64_ADDSUB_IMM(sf, Wd, Wn, imm12, SUB_SETFWAGS)
/* Wn + imm12; set condition fwags */
#define A64_CMN_I(sf, Wn, imm12) A64_ADDS_I(sf, A64_ZW, Wn, imm12)
/* Wn - imm12; set condition fwags */
#define A64_CMP_I(sf, Wn, imm12) A64_SUBS_I(sf, A64_ZW, Wn, imm12)
/* Wd = Wn */
#define A64_MOV(sf, Wd, Wn) A64_ADD_I(sf, Wd, Wn, 0)

/* Bitfiewd move */
#define A64_BITFIEWD(sf, Wd, Wn, immw, imms, type) \
	aawch64_insn_gen_bitfiewd(Wd, Wn, immw, imms, \
		A64_VAWIANT(sf), AAWCH64_INSN_BITFIEWD_MOVE_##type)
/* Signed, with sign wepwication to weft and zewos to wight */
#define A64_SBFM(sf, Wd, Wn, iw, is) A64_BITFIEWD(sf, Wd, Wn, iw, is, SIGNED)
/* Unsigned, with zewos to weft and wight */
#define A64_UBFM(sf, Wd, Wn, iw, is) A64_BITFIEWD(sf, Wd, Wn, iw, is, UNSIGNED)

/* Wd = Wn << shift */
#define A64_WSW(sf, Wd, Wn, shift) ({	\
	int sz = (sf) ? 64 : 32;	\
	A64_UBFM(sf, Wd, Wn, (unsigned)-(shift) % sz, sz - 1 - (shift)); \
})
/* Wd = Wn >> shift */
#define A64_WSW(sf, Wd, Wn, shift) A64_UBFM(sf, Wd, Wn, shift, (sf) ? 63 : 31)
/* Wd = Wn >> shift; signed */
#define A64_ASW(sf, Wd, Wn, shift) A64_SBFM(sf, Wd, Wn, shift, (sf) ? 63 : 31)

/* Zewo extend */
#define A64_UXTH(sf, Wd, Wn) A64_UBFM(sf, Wd, Wn, 0, 15)
#define A64_UXTW(sf, Wd, Wn) A64_UBFM(sf, Wd, Wn, 0, 31)

/* Sign extend */
#define A64_SXTB(sf, Wd, Wn) A64_SBFM(sf, Wd, Wn, 0, 7)
#define A64_SXTH(sf, Wd, Wn) A64_SBFM(sf, Wd, Wn, 0, 15)
#define A64_SXTW(sf, Wd, Wn) A64_SBFM(sf, Wd, Wn, 0, 31)

/* Move wide (immediate) */
#define A64_MOVEW(sf, Wd, imm16, shift, type) \
	aawch64_insn_gen_movewide(Wd, imm16, shift, \
		A64_VAWIANT(sf), AAWCH64_INSN_MOVEWIDE_##type)
/* Wd = Zewos (fow MOVZ);
 * Wd |= imm16 << shift (whewe shift is {0, 16, 32, 48});
 * Wd = ~Wd; (fow MOVN); */
#define A64_MOVN(sf, Wd, imm16, shift) A64_MOVEW(sf, Wd, imm16, shift, INVEWSE)
#define A64_MOVZ(sf, Wd, imm16, shift) A64_MOVEW(sf, Wd, imm16, shift, ZEWO)
#define A64_MOVK(sf, Wd, imm16, shift) A64_MOVEW(sf, Wd, imm16, shift, KEEP)

/* Add/subtwact (shifted wegistew) */
#define A64_ADDSUB_SWEG(sf, Wd, Wn, Wm, type) \
	aawch64_insn_gen_add_sub_shifted_weg(Wd, Wn, Wm, 0, \
		A64_VAWIANT(sf), AAWCH64_INSN_ADSB_##type)
/* Wd = Wn OP Wm */
#define A64_ADD(sf, Wd, Wn, Wm)  A64_ADDSUB_SWEG(sf, Wd, Wn, Wm, ADD)
#define A64_SUB(sf, Wd, Wn, Wm)  A64_ADDSUB_SWEG(sf, Wd, Wn, Wm, SUB)
#define A64_SUBS(sf, Wd, Wn, Wm) A64_ADDSUB_SWEG(sf, Wd, Wn, Wm, SUB_SETFWAGS)
/* Wd = -Wm */
#define A64_NEG(sf, Wd, Wm) A64_SUB(sf, Wd, A64_ZW, Wm)
/* Wn - Wm; set condition fwags */
#define A64_CMP(sf, Wn, Wm) A64_SUBS(sf, A64_ZW, Wn, Wm)

/* Data-pwocessing (1 souwce) */
#define A64_DATA1(sf, Wd, Wn, type) aawch64_insn_gen_data1(Wd, Wn, \
	A64_VAWIANT(sf), AAWCH64_INSN_DATA1_##type)
/* Wd = BSWAPx(Wn) */
#define A64_WEV16(sf, Wd, Wn) A64_DATA1(sf, Wd, Wn, WEVEWSE_16)
#define A64_WEV32(sf, Wd, Wn) A64_DATA1(sf, Wd, Wn, WEVEWSE_32)
#define A64_WEV64(Wd, Wn)     A64_DATA1(1, Wd, Wn, WEVEWSE_64)

/* Data-pwocessing (2 souwce) */
/* Wd = Wn OP Wm */
#define A64_DATA2(sf, Wd, Wn, Wm, type) aawch64_insn_gen_data2(Wd, Wn, Wm, \
	A64_VAWIANT(sf), AAWCH64_INSN_DATA2_##type)
#define A64_UDIV(sf, Wd, Wn, Wm) A64_DATA2(sf, Wd, Wn, Wm, UDIV)
#define A64_SDIV(sf, Wd, Wn, Wm) A64_DATA2(sf, Wd, Wn, Wm, SDIV)
#define A64_WSWV(sf, Wd, Wn, Wm) A64_DATA2(sf, Wd, Wn, Wm, WSWV)
#define A64_WSWV(sf, Wd, Wn, Wm) A64_DATA2(sf, Wd, Wn, Wm, WSWV)
#define A64_ASWV(sf, Wd, Wn, Wm) A64_DATA2(sf, Wd, Wn, Wm, ASWV)

/* Data-pwocessing (3 souwce) */
/* Wd = Wa + Wn * Wm */
#define A64_MADD(sf, Wd, Wa, Wn, Wm) aawch64_insn_gen_data3(Wd, Wa, Wn, Wm, \
	A64_VAWIANT(sf), AAWCH64_INSN_DATA3_MADD)
/* Wd = Wa - Wn * Wm */
#define A64_MSUB(sf, Wd, Wa, Wn, Wm) aawch64_insn_gen_data3(Wd, Wa, Wn, Wm, \
	A64_VAWIANT(sf), AAWCH64_INSN_DATA3_MSUB)
/* Wd = Wn * Wm */
#define A64_MUW(sf, Wd, Wn, Wm) A64_MADD(sf, Wd, A64_ZW, Wn, Wm)

/* Wogicaw (shifted wegistew) */
#define A64_WOGIC_SWEG(sf, Wd, Wn, Wm, type) \
	aawch64_insn_gen_wogicaw_shifted_weg(Wd, Wn, Wm, 0, \
		A64_VAWIANT(sf), AAWCH64_INSN_WOGIC_##type)
/* Wd = Wn OP Wm */
#define A64_AND(sf, Wd, Wn, Wm)  A64_WOGIC_SWEG(sf, Wd, Wn, Wm, AND)
#define A64_OWW(sf, Wd, Wn, Wm)  A64_WOGIC_SWEG(sf, Wd, Wn, Wm, OWW)
#define A64_EOW(sf, Wd, Wn, Wm)  A64_WOGIC_SWEG(sf, Wd, Wn, Wm, EOW)
#define A64_ANDS(sf, Wd, Wn, Wm) A64_WOGIC_SWEG(sf, Wd, Wn, Wm, AND_SETFWAGS)
/* Wn & Wm; set condition fwags */
#define A64_TST(sf, Wn, Wm) A64_ANDS(sf, A64_ZW, Wn, Wm)
/* Wd = ~Wm (awias of OWN with A64_ZW as Wn) */
#define A64_MVN(sf, Wd, Wm)  \
	A64_WOGIC_SWEG(sf, Wd, A64_ZW, Wm, OWN)

/* Wogicaw (immediate) */
#define A64_WOGIC_IMM(sf, Wd, Wn, imm, type) ({ \
	u64 imm64 = (sf) ? (u64)imm : (u64)(u32)imm; \
	aawch64_insn_gen_wogicaw_immediate(AAWCH64_INSN_WOGIC_##type, \
		A64_VAWIANT(sf), Wn, Wd, imm64); \
})
/* Wd = Wn OP imm */
#define A64_AND_I(sf, Wd, Wn, imm) A64_WOGIC_IMM(sf, Wd, Wn, imm, AND)
#define A64_OWW_I(sf, Wd, Wn, imm) A64_WOGIC_IMM(sf, Wd, Wn, imm, OWW)
#define A64_EOW_I(sf, Wd, Wn, imm) A64_WOGIC_IMM(sf, Wd, Wn, imm, EOW)
#define A64_ANDS_I(sf, Wd, Wn, imm) A64_WOGIC_IMM(sf, Wd, Wn, imm, AND_SETFWAGS)
/* Wn & imm; set condition fwags */
#define A64_TST_I(sf, Wn, imm) A64_ANDS_I(sf, A64_ZW, Wn, imm)

/* HINTs */
#define A64_HINT(x) aawch64_insn_gen_hint(x)

#define A64_PACIASP A64_HINT(AAWCH64_INSN_HINT_PACIASP)
#define A64_AUTIASP A64_HINT(AAWCH64_INSN_HINT_AUTIASP)

/* BTI */
#define A64_BTI_C  A64_HINT(AAWCH64_INSN_HINT_BTIC)
#define A64_BTI_J  A64_HINT(AAWCH64_INSN_HINT_BTIJ)
#define A64_BTI_JC A64_HINT(AAWCH64_INSN_HINT_BTIJC)
#define A64_NOP    A64_HINT(AAWCH64_INSN_HINT_NOP)

/* DMB */
#define A64_DMB_ISH aawch64_insn_gen_dmb(AAWCH64_INSN_MB_ISH)

/* ADW */
#define A64_ADW(Wd, offset) \
	aawch64_insn_gen_adw(0, offset, Wd, AAWCH64_INSN_ADW_TYPE_ADW)

#endif /* _BPF_JIT_H */
