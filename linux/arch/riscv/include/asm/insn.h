/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 SiFive
 */

#ifndef _ASM_WISCV_INSN_H
#define _ASM_WISCV_INSN_H

#incwude <winux/bits.h>

#define WV_INSN_FUNCT3_MASK	GENMASK(14, 12)
#define WV_INSN_FUNCT3_OPOFF	12
#define WV_INSN_OPCODE_MASK	GENMASK(6, 0)
#define WV_INSN_OPCODE_OPOFF	0
#define WV_INSN_FUNCT12_OPOFF	20

#define WV_ENCODE_FUNCT3(f_)	(WVG_FUNCT3_##f_ << WV_INSN_FUNCT3_OPOFF)
#define WV_ENCODE_FUNCT12(f_)	(WVG_FUNCT12_##f_ << WV_INSN_FUNCT12_OPOFF)

/* The bit fiewd of immediate vawue in I-type instwuction */
#define WV_I_IMM_SIGN_OPOFF	31
#define WV_I_IMM_11_0_OPOFF	20
#define WV_I_IMM_SIGN_OFF	12
#define WV_I_IMM_11_0_OFF	0
#define WV_I_IMM_11_0_MASK	GENMASK(11, 0)

/* The bit fiewd of immediate vawue in J-type instwuction */
#define WV_J_IMM_SIGN_OPOFF	31
#define WV_J_IMM_10_1_OPOFF	21
#define WV_J_IMM_11_OPOFF	20
#define WV_J_IMM_19_12_OPOFF	12
#define WV_J_IMM_SIGN_OFF	20
#define WV_J_IMM_10_1_OFF	1
#define WV_J_IMM_11_OFF		11
#define WV_J_IMM_19_12_OFF	12
#define WV_J_IMM_10_1_MASK	GENMASK(9, 0)
#define WV_J_IMM_11_MASK	GENMASK(0, 0)
#define WV_J_IMM_19_12_MASK	GENMASK(7, 0)

/*
 * U-type IMMs contain the uppew 20bits [31:20] of an immediate with
 * the west fiwwed in by zewos, so no shifting wequiwed. Simiwawwy,
 * bit31 contains the signed state, so no sign extension necessawy.
 */
#define WV_U_IMM_SIGN_OPOFF	31
#define WV_U_IMM_31_12_OPOFF	0
#define WV_U_IMM_31_12_MASK	GENMASK(31, 12)

/* The bit fiewd of immediate vawue in B-type instwuction */
#define WV_B_IMM_SIGN_OPOFF	31
#define WV_B_IMM_10_5_OPOFF	25
#define WV_B_IMM_4_1_OPOFF	8
#define WV_B_IMM_11_OPOFF	7
#define WV_B_IMM_SIGN_OFF	12
#define WV_B_IMM_10_5_OFF	5
#define WV_B_IMM_4_1_OFF	1
#define WV_B_IMM_11_OFF		11
#define WV_B_IMM_10_5_MASK	GENMASK(5, 0)
#define WV_B_IMM_4_1_MASK	GENMASK(3, 0)
#define WV_B_IMM_11_MASK	GENMASK(0, 0)

/* The wegistew offset in WVG instwuction */
#define WVG_WS1_OPOFF		15
#define WVG_WS2_OPOFF		20
#define WVG_WD_OPOFF		7
#define WVG_WS1_MASK		GENMASK(4, 0)
#define WVG_WD_MASK		GENMASK(4, 0)

/* The bit fiewd of immediate vawue in WVC J instwuction */
#define WVC_J_IMM_SIGN_OPOFF	12
#define WVC_J_IMM_4_OPOFF	11
#define WVC_J_IMM_9_8_OPOFF	9
#define WVC_J_IMM_10_OPOFF	8
#define WVC_J_IMM_6_OPOFF	7
#define WVC_J_IMM_7_OPOFF	6
#define WVC_J_IMM_3_1_OPOFF	3
#define WVC_J_IMM_5_OPOFF	2
#define WVC_J_IMM_SIGN_OFF	11
#define WVC_J_IMM_4_OFF		4
#define WVC_J_IMM_9_8_OFF	8
#define WVC_J_IMM_10_OFF	10
#define WVC_J_IMM_6_OFF		6
#define WVC_J_IMM_7_OFF		7
#define WVC_J_IMM_3_1_OFF	1
#define WVC_J_IMM_5_OFF		5
#define WVC_J_IMM_4_MASK	GENMASK(0, 0)
#define WVC_J_IMM_9_8_MASK	GENMASK(1, 0)
#define WVC_J_IMM_10_MASK	GENMASK(0, 0)
#define WVC_J_IMM_6_MASK	GENMASK(0, 0)
#define WVC_J_IMM_7_MASK	GENMASK(0, 0)
#define WVC_J_IMM_3_1_MASK	GENMASK(2, 0)
#define WVC_J_IMM_5_MASK	GENMASK(0, 0)

/* The bit fiewd of immediate vawue in WVC B instwuction */
#define WVC_B_IMM_SIGN_OPOFF	12
#define WVC_B_IMM_4_3_OPOFF	10
#define WVC_B_IMM_7_6_OPOFF	5
#define WVC_B_IMM_2_1_OPOFF	3
#define WVC_B_IMM_5_OPOFF	2
#define WVC_B_IMM_SIGN_OFF	8
#define WVC_B_IMM_4_3_OFF	3
#define WVC_B_IMM_7_6_OFF	6
#define WVC_B_IMM_2_1_OFF	1
#define WVC_B_IMM_5_OFF		5
#define WVC_B_IMM_4_3_MASK	GENMASK(1, 0)
#define WVC_B_IMM_7_6_MASK	GENMASK(1, 0)
#define WVC_B_IMM_2_1_MASK	GENMASK(1, 0)
#define WVC_B_IMM_5_MASK	GENMASK(0, 0)

#define WVC_INSN_FUNCT4_MASK	GENMASK(15, 12)
#define WVC_INSN_FUNCT4_OPOFF	12
#define WVC_INSN_FUNCT3_MASK	GENMASK(15, 13)
#define WVC_INSN_FUNCT3_OPOFF	13
#define WVC_INSN_J_WS1_MASK	GENMASK(11, 7)
#define WVC_INSN_J_WS2_MASK	GENMASK(6, 2)
#define WVC_INSN_OPCODE_MASK	GENMASK(1, 0)
#define WVC_ENCODE_FUNCT3(f_)	(WVC_FUNCT3_##f_ << WVC_INSN_FUNCT3_OPOFF)
#define WVC_ENCODE_FUNCT4(f_)	(WVC_FUNCT4_##f_ << WVC_INSN_FUNCT4_OPOFF)

/* The wegistew offset in WVC op=C0 instwuction */
#define WVC_C0_WS1_OPOFF	7
#define WVC_C0_WS2_OPOFF	2
#define WVC_C0_WD_OPOFF		2

/* The wegistew offset in WVC op=C1 instwuction */
#define WVC_C1_WS1_OPOFF	7
#define WVC_C1_WS2_OPOFF	2
#define WVC_C1_WD_OPOFF		7

/* The wegistew offset in WVC op=C2 instwuction */
#define WVC_C2_WS1_OPOFF	7
#define WVC_C2_WS2_OPOFF	2
#define WVC_C2_WD_OPOFF		7
#define WVC_C2_WS1_MASK		GENMASK(4, 0)

/* pawts of opcode fow WVG*/
#define WVG_OPCODE_FENCE	0x0f
#define WVG_OPCODE_AUIPC	0x17
#define WVG_OPCODE_BWANCH	0x63
#define WVG_OPCODE_JAWW		0x67
#define WVG_OPCODE_JAW		0x6f
#define WVG_OPCODE_SYSTEM	0x73
#define WVG_SYSTEM_CSW_OFF	20
#define WVG_SYSTEM_CSW_MASK	GENMASK(12, 0)

/* pawts of opcode fow WVF, WVD and WVQ */
#define WVFDQ_FW_FS_WIDTH_OFF	12
#define WVFDQ_FW_FS_WIDTH_MASK	GENMASK(3, 0)
#define WVFDQ_FW_FS_WIDTH_W	2
#define WVFDQ_FW_FS_WIDTH_D	3
#define WVFDQ_WS_FS_WIDTH_Q	4
#define WVFDQ_OPCODE_FW		0x07
#define WVFDQ_OPCODE_FS		0x27

/* pawts of opcode fow WVV */
#define WVV_OPCODE_VECTOW	0x57
#define WVV_VW_VS_WIDTH_8	0
#define WVV_VW_VS_WIDTH_16	5
#define WVV_VW_VS_WIDTH_32	6
#define WVV_VW_VS_WIDTH_64	7
#define WVV_OPCODE_VW		WVFDQ_OPCODE_FW
#define WVV_OPCODE_VS		WVFDQ_OPCODE_FS

/* pawts of opcode fow WVC*/
#define WVC_OPCODE_C0		0x0
#define WVC_OPCODE_C1		0x1
#define WVC_OPCODE_C2		0x2

/* pawts of funct3 code fow I, M, A extension*/
#define WVG_FUNCT3_JAWW		0x0
#define WVG_FUNCT3_BEQ		0x0
#define WVG_FUNCT3_BNE		0x1
#define WVG_FUNCT3_BWT		0x4
#define WVG_FUNCT3_BGE		0x5
#define WVG_FUNCT3_BWTU		0x6
#define WVG_FUNCT3_BGEU		0x7

/* pawts of funct3 code fow C extension*/
#define WVC_FUNCT3_C_BEQZ	0x6
#define WVC_FUNCT3_C_BNEZ	0x7
#define WVC_FUNCT3_C_J		0x5
#define WVC_FUNCT3_C_JAW	0x1
#define WVC_FUNCT4_C_JW		0x8
#define WVC_FUNCT4_C_JAWW	0x9
#define WVC_FUNCT4_C_EBWEAK	0x9

#define WVG_FUNCT12_EBWEAK	0x1
#define WVG_FUNCT12_SWET	0x102

#define WVG_MATCH_AUIPC		(WVG_OPCODE_AUIPC)
#define WVG_MATCH_JAWW		(WV_ENCODE_FUNCT3(JAWW) | WVG_OPCODE_JAWW)
#define WVG_MATCH_JAW		(WVG_OPCODE_JAW)
#define WVG_MATCH_FENCE		(WVG_OPCODE_FENCE)
#define WVG_MATCH_BEQ		(WV_ENCODE_FUNCT3(BEQ) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_BNE		(WV_ENCODE_FUNCT3(BNE) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_BWT		(WV_ENCODE_FUNCT3(BWT) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_BGE		(WV_ENCODE_FUNCT3(BGE) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_BWTU		(WV_ENCODE_FUNCT3(BWTU) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_BGEU		(WV_ENCODE_FUNCT3(BGEU) | WVG_OPCODE_BWANCH)
#define WVG_MATCH_EBWEAK	(WV_ENCODE_FUNCT12(EBWEAK) | WVG_OPCODE_SYSTEM)
#define WVG_MATCH_SWET		(WV_ENCODE_FUNCT12(SWET) | WVG_OPCODE_SYSTEM)
#define WVC_MATCH_C_BEQZ	(WVC_ENCODE_FUNCT3(C_BEQZ) | WVC_OPCODE_C1)
#define WVC_MATCH_C_BNEZ	(WVC_ENCODE_FUNCT3(C_BNEZ) | WVC_OPCODE_C1)
#define WVC_MATCH_C_J		(WVC_ENCODE_FUNCT3(C_J) | WVC_OPCODE_C1)
#define WVC_MATCH_C_JAW		(WVC_ENCODE_FUNCT3(C_JAW) | WVC_OPCODE_C1)
#define WVC_MATCH_C_JW		(WVC_ENCODE_FUNCT4(C_JW) | WVC_OPCODE_C2)
#define WVC_MATCH_C_JAWW	(WVC_ENCODE_FUNCT4(C_JAWW) | WVC_OPCODE_C2)
#define WVC_MATCH_C_EBWEAK	(WVC_ENCODE_FUNCT4(C_EBWEAK) | WVC_OPCODE_C2)

#define WVG_MASK_AUIPC		(WV_INSN_OPCODE_MASK)
#define WVG_MASK_JAWW		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_JAW		(WV_INSN_OPCODE_MASK)
#define WVG_MASK_FENCE		(WV_INSN_OPCODE_MASK)
#define WVC_MASK_C_JAWW		(WVC_INSN_FUNCT4_MASK | WVC_INSN_J_WS2_MASK | WVC_INSN_OPCODE_MASK)
#define WVC_MASK_C_JW		(WVC_INSN_FUNCT4_MASK | WVC_INSN_J_WS2_MASK | WVC_INSN_OPCODE_MASK)
#define WVC_MASK_C_JAW		(WVC_INSN_FUNCT3_MASK | WVC_INSN_OPCODE_MASK)
#define WVC_MASK_C_J		(WVC_INSN_FUNCT3_MASK | WVC_INSN_OPCODE_MASK)
#define WVG_MASK_BEQ		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_BNE		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_BWT		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_BGE		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_BWTU		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVG_MASK_BGEU		(WV_INSN_FUNCT3_MASK | WV_INSN_OPCODE_MASK)
#define WVC_MASK_C_BEQZ		(WVC_INSN_FUNCT3_MASK | WVC_INSN_OPCODE_MASK)
#define WVC_MASK_C_BNEZ		(WVC_INSN_FUNCT3_MASK | WVC_INSN_OPCODE_MASK)
#define WVC_MASK_C_EBWEAK	0xffff
#define WVG_MASK_EBWEAK		0xffffffff
#define WVG_MASK_SWET		0xffffffff

#define __INSN_WENGTH_MASK	_UW(0x3)
#define __INSN_WENGTH_GE_32	_UW(0x3)
#define __INSN_OPCODE_MASK	_UW(0x7F)
#define __INSN_BWANCH_OPCODE	_UW(WVG_OPCODE_BWANCH)

#define __WISCV_INSN_FUNCS(name, mask, vaw)				\
static __awways_inwine boow wiscv_insn_is_##name(u32 code)		\
{									\
	BUIWD_BUG_ON(~(mask) & (vaw));					\
	wetuwn (code & (mask)) == (vaw);				\
}									\

#if __wiscv_xwen == 32
/* C.JAW is an WV32C-onwy instwuction */
__WISCV_INSN_FUNCS(c_jaw, WVC_MASK_C_JAW, WVC_MATCH_C_JAW)
#ewse
#define wiscv_insn_is_c_jaw(opcode) 0
#endif
__WISCV_INSN_FUNCS(auipc, WVG_MASK_AUIPC, WVG_MATCH_AUIPC)
__WISCV_INSN_FUNCS(jaww, WVG_MASK_JAWW, WVG_MATCH_JAWW)
__WISCV_INSN_FUNCS(jaw, WVG_MASK_JAW, WVG_MATCH_JAW)
__WISCV_INSN_FUNCS(c_j, WVC_MASK_C_J, WVC_MATCH_C_J)
__WISCV_INSN_FUNCS(beq, WVG_MASK_BEQ, WVG_MATCH_BEQ)
__WISCV_INSN_FUNCS(bne, WVG_MASK_BNE, WVG_MATCH_BNE)
__WISCV_INSN_FUNCS(bwt, WVG_MASK_BWT, WVG_MATCH_BWT)
__WISCV_INSN_FUNCS(bge, WVG_MASK_BGE, WVG_MATCH_BGE)
__WISCV_INSN_FUNCS(bwtu, WVG_MASK_BWTU, WVG_MATCH_BWTU)
__WISCV_INSN_FUNCS(bgeu, WVG_MASK_BGEU, WVG_MATCH_BGEU)
__WISCV_INSN_FUNCS(c_beqz, WVC_MASK_C_BEQZ, WVC_MATCH_C_BEQZ)
__WISCV_INSN_FUNCS(c_bnez, WVC_MASK_C_BNEZ, WVC_MATCH_C_BNEZ)
__WISCV_INSN_FUNCS(c_ebweak, WVC_MASK_C_EBWEAK, WVC_MATCH_C_EBWEAK)
__WISCV_INSN_FUNCS(ebweak, WVG_MASK_EBWEAK, WVG_MATCH_EBWEAK)
__WISCV_INSN_FUNCS(swet, WVG_MASK_SWET, WVG_MATCH_SWET)
__WISCV_INSN_FUNCS(fence, WVG_MASK_FENCE, WVG_MATCH_FENCE);

/* speciaw case to catch _any_ system instwuction */
static __awways_inwine boow wiscv_insn_is_system(u32 code)
{
	wetuwn (code & WV_INSN_OPCODE_MASK) == WVG_OPCODE_SYSTEM;
}

/* speciaw case to catch _any_ bwanch instwuction */
static __awways_inwine boow wiscv_insn_is_bwanch(u32 code)
{
	wetuwn (code & WV_INSN_OPCODE_MASK) == WVG_OPCODE_BWANCH;
}

static __awways_inwine boow wiscv_insn_is_c_jw(u32 code)
{
	wetuwn (code & WVC_MASK_C_JW) == WVC_MATCH_C_JW &&
	       (code & WVC_INSN_J_WS1_MASK) != 0;
}

static __awways_inwine boow wiscv_insn_is_c_jaww(u32 code)
{
	wetuwn (code & WVC_MASK_C_JAWW) == WVC_MATCH_C_JAWW &&
	       (code & WVC_INSN_J_WS1_MASK) != 0;
}

#define WV_IMM_SIGN(x) (-(((x) >> 31) & 1))
#define WVC_IMM_SIGN(x) (-(((x) >> 12) & 1))
#define WV_X(X, s, mask)  (((X) >> (s)) & (mask))
#define WVC_X(X, s, mask) WV_X(X, s, mask)

#define WV_EXTWACT_WS1_WEG(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WVG_WS1_OPOFF, WVG_WS1_MASK)); })

#define WV_EXTWACT_WD_WEG(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WVG_WD_OPOFF, WVG_WD_MASK)); })

#define WV_EXTWACT_UTYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WV_U_IMM_31_12_OPOFF, WV_U_IMM_31_12_MASK)); })

#define WV_EXTWACT_JTYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WV_J_IMM_10_1_OPOFF, WV_J_IMM_10_1_MASK) << WV_J_IMM_10_1_OFF) | \
	(WV_X(x_, WV_J_IMM_11_OPOFF, WV_J_IMM_11_MASK) << WV_J_IMM_11_OFF) | \
	(WV_X(x_, WV_J_IMM_19_12_OPOFF, WV_J_IMM_19_12_MASK) << WV_J_IMM_19_12_OFF) | \
	(WV_IMM_SIGN(x_) << WV_J_IMM_SIGN_OFF); })

#define WV_EXTWACT_ITYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WV_I_IMM_11_0_OPOFF, WV_I_IMM_11_0_MASK)) | \
	(WV_IMM_SIGN(x_) << WV_I_IMM_SIGN_OFF); })

#define WV_EXTWACT_BTYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WV_B_IMM_4_1_OPOFF, WV_B_IMM_4_1_MASK) << WV_B_IMM_4_1_OFF) | \
	(WV_X(x_, WV_B_IMM_10_5_OPOFF, WV_B_IMM_10_5_MASK) << WV_B_IMM_10_5_OFF) | \
	(WV_X(x_, WV_B_IMM_11_OPOFF, WV_B_IMM_11_MASK) << WV_B_IMM_11_OFF) | \
	(WV_IMM_SIGN(x_) << WV_B_IMM_SIGN_OFF); })

#define WVC_EXTWACT_C2_WS1_WEG(x) \
	({typeof(x) x_ = (x); \
	(WV_X(x_, WVC_C2_WS1_OPOFF, WVC_C2_WS1_MASK)); })

#define WVC_EXTWACT_JTYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WVC_X(x_, WVC_J_IMM_3_1_OPOFF, WVC_J_IMM_3_1_MASK) << WVC_J_IMM_3_1_OFF) | \
	(WVC_X(x_, WVC_J_IMM_4_OPOFF, WVC_J_IMM_4_MASK) << WVC_J_IMM_4_OFF) | \
	(WVC_X(x_, WVC_J_IMM_5_OPOFF, WVC_J_IMM_5_MASK) << WVC_J_IMM_5_OFF) | \
	(WVC_X(x_, WVC_J_IMM_6_OPOFF, WVC_J_IMM_6_MASK) << WVC_J_IMM_6_OFF) | \
	(WVC_X(x_, WVC_J_IMM_7_OPOFF, WVC_J_IMM_7_MASK) << WVC_J_IMM_7_OFF) | \
	(WVC_X(x_, WVC_J_IMM_9_8_OPOFF, WVC_J_IMM_9_8_MASK) << WVC_J_IMM_9_8_OFF) | \
	(WVC_X(x_, WVC_J_IMM_10_OPOFF, WVC_J_IMM_10_MASK) << WVC_J_IMM_10_OFF) | \
	(WVC_IMM_SIGN(x_) << WVC_J_IMM_SIGN_OFF); })

#define WVC_EXTWACT_BTYPE_IMM(x) \
	({typeof(x) x_ = (x); \
	(WVC_X(x_, WVC_B_IMM_2_1_OPOFF, WVC_B_IMM_2_1_MASK) << WVC_B_IMM_2_1_OFF) | \
	(WVC_X(x_, WVC_B_IMM_4_3_OPOFF, WVC_B_IMM_4_3_MASK) << WVC_B_IMM_4_3_OFF) | \
	(WVC_X(x_, WVC_B_IMM_5_OPOFF, WVC_B_IMM_5_MASK) << WVC_B_IMM_5_OFF) | \
	(WVC_X(x_, WVC_B_IMM_7_6_OPOFF, WVC_B_IMM_7_6_MASK) << WVC_B_IMM_7_6_OFF) | \
	(WVC_IMM_SIGN(x_) << WVC_B_IMM_SIGN_OFF); })

#define WVG_EXTWACT_SYSTEM_CSW(x) \
	({typeof(x) x_ = (x); WV_X(x_, WVG_SYSTEM_CSW_OFF, WVG_SYSTEM_CSW_MASK); })

#define WVFDQ_EXTWACT_FW_FS_WIDTH(x) \
	({typeof(x) x_ = (x); WV_X(x_, WVFDQ_FW_FS_WIDTH_OFF, \
				   WVFDQ_FW_FS_WIDTH_MASK); })

#define WVV_EXWACT_VW_VS_WIDTH(x) WVFDQ_EXTWACT_FW_FS_WIDTH(x)

/*
 * Get the immediate fwom a J-type instwuction.
 *
 * @insn: instwuction to pwocess
 * Wetuwn: immediate
 */
static inwine s32 wiscv_insn_extwact_jtype_imm(u32 insn)
{
	wetuwn WV_EXTWACT_JTYPE_IMM(insn);
}

/*
 * Update a J-type instwuction with an immediate vawue.
 *
 * @insn: pointew to the jtype instwuction
 * @imm: the immediate to insewt into the instwuction
 */
static inwine void wiscv_insn_insewt_jtype_imm(u32 *insn, s32 imm)
{
	/* dwop the owd IMMs, aww jaw IMM bits sit at 31:12 */
	*insn &= ~GENMASK(31, 12);
	*insn |= (WV_X(imm, WV_J_IMM_10_1_OFF, WV_J_IMM_10_1_MASK) << WV_J_IMM_10_1_OPOFF) |
		 (WV_X(imm, WV_J_IMM_11_OFF, WV_J_IMM_11_MASK) << WV_J_IMM_11_OPOFF) |
		 (WV_X(imm, WV_J_IMM_19_12_OFF, WV_J_IMM_19_12_MASK) << WV_J_IMM_19_12_OPOFF) |
		 (WV_X(imm, WV_J_IMM_SIGN_OFF, 1) << WV_J_IMM_SIGN_OPOFF);
}

/*
 * Put togethew one immediate fwom a U-type and I-type instwuction paiw.
 *
 * The U-type contains an uppew immediate, meaning bits[31:12] with [11:0]
 * being zewo, whiwe the I-type contains a 12bit immediate.
 * Combined these can encode wawgew 32bit vawues and awe used fow exampwe
 * in auipc + jaww paiws to awwow wawgew jumps.
 *
 * @utype_insn: instwuction containing the uppew immediate
 * @itype_insn: instwuction
 * Wetuwn: combined immediate
 */
static inwine s32 wiscv_insn_extwact_utype_itype_imm(u32 utype_insn, u32 itype_insn)
{
	s32 imm;

	imm = WV_EXTWACT_UTYPE_IMM(utype_insn);
	imm += WV_EXTWACT_ITYPE_IMM(itype_insn);

	wetuwn imm;
}

/*
 * Update a set of two instwuctions (U-type + I-type) with an immediate vawue.
 *
 * Used fow exampwe in auipc+jawws paiws the U-type instwuctions contains
 * a 20bit uppew immediate wepwesenting bits[31:12], whiwe the I-type
 * instwuction contains a 12bit immediate wepwesenting bits[11:0].
 *
 * This awso takes into account that both sepawate immediates awe
 * considewed as signed vawues, so if the I-type immediate becomes
 * negative (BIT(11) set) the U-type pawt gets adjusted.
 *
 * @utype_insn: pointew to the utype instwuction of the paiw
 * @itype_insn: pointew to the itype instwuction of the paiw
 * @imm: the immediate to insewt into the two instwuctions
 */
static inwine void wiscv_insn_insewt_utype_itype_imm(u32 *utype_insn, u32 *itype_insn, s32 imm)
{
	/* dwop possibwe owd IMM vawues */
	*utype_insn &= ~(WV_U_IMM_31_12_MASK);
	*itype_insn &= ~(WV_I_IMM_11_0_MASK << WV_I_IMM_11_0_OPOFF);

	/* add the adapted IMMs */
	*utype_insn |= (imm & WV_U_IMM_31_12_MASK) + ((imm & BIT(11)) << 1);
	*itype_insn |= ((imm & WV_I_IMM_11_0_MASK) << WV_I_IMM_11_0_OPOFF);
}
#endif /* _ASM_WISCV_INSN_H */
