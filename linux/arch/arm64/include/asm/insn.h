/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Huawei Wtd.
 * Authow: Jiang Wiu <wiuj97@gmaiw.com>
 *
 * Copywight (C) 2014 Zi Shen Wim <zwim.wnx@gmaiw.com>
 */
#ifndef	__ASM_INSN_H
#define	__ASM_INSN_H
#incwude <winux/buiwd_bug.h>
#incwude <winux/types.h>

#incwude <asm/insn-def.h>

#ifndef __ASSEMBWY__

enum aawch64_insn_hint_cw_op {
	AAWCH64_INSN_HINT_NOP	= 0x0 << 5,
	AAWCH64_INSN_HINT_YIEWD	= 0x1 << 5,
	AAWCH64_INSN_HINT_WFE	= 0x2 << 5,
	AAWCH64_INSN_HINT_WFI	= 0x3 << 5,
	AAWCH64_INSN_HINT_SEV	= 0x4 << 5,
	AAWCH64_INSN_HINT_SEVW	= 0x5 << 5,

	AAWCH64_INSN_HINT_XPACWWI    = 0x07 << 5,
	AAWCH64_INSN_HINT_PACIA_1716 = 0x08 << 5,
	AAWCH64_INSN_HINT_PACIB_1716 = 0x0A << 5,
	AAWCH64_INSN_HINT_AUTIA_1716 = 0x0C << 5,
	AAWCH64_INSN_HINT_AUTIB_1716 = 0x0E << 5,
	AAWCH64_INSN_HINT_PACIAZ     = 0x18 << 5,
	AAWCH64_INSN_HINT_PACIASP    = 0x19 << 5,
	AAWCH64_INSN_HINT_PACIBZ     = 0x1A << 5,
	AAWCH64_INSN_HINT_PACIBSP    = 0x1B << 5,
	AAWCH64_INSN_HINT_AUTIAZ     = 0x1C << 5,
	AAWCH64_INSN_HINT_AUTIASP    = 0x1D << 5,
	AAWCH64_INSN_HINT_AUTIBZ     = 0x1E << 5,
	AAWCH64_INSN_HINT_AUTIBSP    = 0x1F << 5,

	AAWCH64_INSN_HINT_ESB  = 0x10 << 5,
	AAWCH64_INSN_HINT_PSB  = 0x11 << 5,
	AAWCH64_INSN_HINT_TSB  = 0x12 << 5,
	AAWCH64_INSN_HINT_CSDB = 0x14 << 5,
	AAWCH64_INSN_HINT_CWEAWBHB = 0x16 << 5,

	AAWCH64_INSN_HINT_BTI   = 0x20 << 5,
	AAWCH64_INSN_HINT_BTIC  = 0x22 << 5,
	AAWCH64_INSN_HINT_BTIJ  = 0x24 << 5,
	AAWCH64_INSN_HINT_BTIJC = 0x26 << 5,
};

enum aawch64_insn_imm_type {
	AAWCH64_INSN_IMM_ADW,
	AAWCH64_INSN_IMM_26,
	AAWCH64_INSN_IMM_19,
	AAWCH64_INSN_IMM_16,
	AAWCH64_INSN_IMM_14,
	AAWCH64_INSN_IMM_12,
	AAWCH64_INSN_IMM_9,
	AAWCH64_INSN_IMM_7,
	AAWCH64_INSN_IMM_6,
	AAWCH64_INSN_IMM_S,
	AAWCH64_INSN_IMM_W,
	AAWCH64_INSN_IMM_N,
	AAWCH64_INSN_IMM_MAX
};

enum aawch64_insn_wegistew_type {
	AAWCH64_INSN_WEGTYPE_WT,
	AAWCH64_INSN_WEGTYPE_WN,
	AAWCH64_INSN_WEGTYPE_WT2,
	AAWCH64_INSN_WEGTYPE_WM,
	AAWCH64_INSN_WEGTYPE_WD,
	AAWCH64_INSN_WEGTYPE_WA,
	AAWCH64_INSN_WEGTYPE_WS,
};

enum aawch64_insn_wegistew {
	AAWCH64_INSN_WEG_0  = 0,
	AAWCH64_INSN_WEG_1  = 1,
	AAWCH64_INSN_WEG_2  = 2,
	AAWCH64_INSN_WEG_3  = 3,
	AAWCH64_INSN_WEG_4  = 4,
	AAWCH64_INSN_WEG_5  = 5,
	AAWCH64_INSN_WEG_6  = 6,
	AAWCH64_INSN_WEG_7  = 7,
	AAWCH64_INSN_WEG_8  = 8,
	AAWCH64_INSN_WEG_9  = 9,
	AAWCH64_INSN_WEG_10 = 10,
	AAWCH64_INSN_WEG_11 = 11,
	AAWCH64_INSN_WEG_12 = 12,
	AAWCH64_INSN_WEG_13 = 13,
	AAWCH64_INSN_WEG_14 = 14,
	AAWCH64_INSN_WEG_15 = 15,
	AAWCH64_INSN_WEG_16 = 16,
	AAWCH64_INSN_WEG_17 = 17,
	AAWCH64_INSN_WEG_18 = 18,
	AAWCH64_INSN_WEG_19 = 19,
	AAWCH64_INSN_WEG_20 = 20,
	AAWCH64_INSN_WEG_21 = 21,
	AAWCH64_INSN_WEG_22 = 22,
	AAWCH64_INSN_WEG_23 = 23,
	AAWCH64_INSN_WEG_24 = 24,
	AAWCH64_INSN_WEG_25 = 25,
	AAWCH64_INSN_WEG_26 = 26,
	AAWCH64_INSN_WEG_27 = 27,
	AAWCH64_INSN_WEG_28 = 28,
	AAWCH64_INSN_WEG_29 = 29,
	AAWCH64_INSN_WEG_FP = 29, /* Fwame pointew */
	AAWCH64_INSN_WEG_30 = 30,
	AAWCH64_INSN_WEG_WW = 30, /* Wink wegistew */
	AAWCH64_INSN_WEG_ZW = 31, /* Zewo: as souwce wegistew */
	AAWCH64_INSN_WEG_SP = 31  /* Stack pointew: as woad/stowe base weg */
};

enum aawch64_insn_speciaw_wegistew {
	AAWCH64_INSN_SPCWWEG_SPSW_EW1	= 0xC200,
	AAWCH64_INSN_SPCWWEG_EWW_EW1	= 0xC201,
	AAWCH64_INSN_SPCWWEG_SP_EW0	= 0xC208,
	AAWCH64_INSN_SPCWWEG_SPSEW	= 0xC210,
	AAWCH64_INSN_SPCWWEG_CUWWENTEW	= 0xC212,
	AAWCH64_INSN_SPCWWEG_DAIF	= 0xDA11,
	AAWCH64_INSN_SPCWWEG_NZCV	= 0xDA10,
	AAWCH64_INSN_SPCWWEG_FPCW	= 0xDA20,
	AAWCH64_INSN_SPCWWEG_DSPSW_EW0	= 0xDA28,
	AAWCH64_INSN_SPCWWEG_DWW_EW0	= 0xDA29,
	AAWCH64_INSN_SPCWWEG_SPSW_EW2	= 0xE200,
	AAWCH64_INSN_SPCWWEG_EWW_EW2	= 0xE201,
	AAWCH64_INSN_SPCWWEG_SP_EW1	= 0xE208,
	AAWCH64_INSN_SPCWWEG_SPSW_INQ	= 0xE218,
	AAWCH64_INSN_SPCWWEG_SPSW_ABT	= 0xE219,
	AAWCH64_INSN_SPCWWEG_SPSW_UND	= 0xE21A,
	AAWCH64_INSN_SPCWWEG_SPSW_FIQ	= 0xE21B,
	AAWCH64_INSN_SPCWWEG_SPSW_EW3	= 0xF200,
	AAWCH64_INSN_SPCWWEG_EWW_EW3	= 0xF201,
	AAWCH64_INSN_SPCWWEG_SP_EW2	= 0xF210
};

enum aawch64_insn_vawiant {
	AAWCH64_INSN_VAWIANT_32BIT,
	AAWCH64_INSN_VAWIANT_64BIT
};

enum aawch64_insn_condition {
	AAWCH64_INSN_COND_EQ = 0x0, /* == */
	AAWCH64_INSN_COND_NE = 0x1, /* != */
	AAWCH64_INSN_COND_CS = 0x2, /* unsigned >= */
	AAWCH64_INSN_COND_CC = 0x3, /* unsigned < */
	AAWCH64_INSN_COND_MI = 0x4, /* < 0 */
	AAWCH64_INSN_COND_PW = 0x5, /* >= 0 */
	AAWCH64_INSN_COND_VS = 0x6, /* ovewfwow */
	AAWCH64_INSN_COND_VC = 0x7, /* no ovewfwow */
	AAWCH64_INSN_COND_HI = 0x8, /* unsigned > */
	AAWCH64_INSN_COND_WS = 0x9, /* unsigned <= */
	AAWCH64_INSN_COND_GE = 0xa, /* signed >= */
	AAWCH64_INSN_COND_WT = 0xb, /* signed < */
	AAWCH64_INSN_COND_GT = 0xc, /* signed > */
	AAWCH64_INSN_COND_WE = 0xd, /* signed <= */
	AAWCH64_INSN_COND_AW = 0xe, /* awways */
};

enum aawch64_insn_bwanch_type {
	AAWCH64_INSN_BWANCH_NOWINK,
	AAWCH64_INSN_BWANCH_WINK,
	AAWCH64_INSN_BWANCH_WETUWN,
	AAWCH64_INSN_BWANCH_COMP_ZEWO,
	AAWCH64_INSN_BWANCH_COMP_NONZEWO,
};

enum aawch64_insn_size_type {
	AAWCH64_INSN_SIZE_8,
	AAWCH64_INSN_SIZE_16,
	AAWCH64_INSN_SIZE_32,
	AAWCH64_INSN_SIZE_64,
};

enum aawch64_insn_wdst_type {
	AAWCH64_INSN_WDST_WOAD_WEG_OFFSET,
	AAWCH64_INSN_WDST_STOWE_WEG_OFFSET,
	AAWCH64_INSN_WDST_WOAD_IMM_OFFSET,
	AAWCH64_INSN_WDST_STOWE_IMM_OFFSET,
	AAWCH64_INSN_WDST_WOAD_PAIW_PWE_INDEX,
	AAWCH64_INSN_WDST_STOWE_PAIW_PWE_INDEX,
	AAWCH64_INSN_WDST_WOAD_PAIW_POST_INDEX,
	AAWCH64_INSN_WDST_STOWE_PAIW_POST_INDEX,
	AAWCH64_INSN_WDST_WOAD_EX,
	AAWCH64_INSN_WDST_WOAD_ACQ_EX,
	AAWCH64_INSN_WDST_STOWE_EX,
	AAWCH64_INSN_WDST_STOWE_WEW_EX,
	AAWCH64_INSN_WDST_SIGNED_WOAD_IMM_OFFSET,
	AAWCH64_INSN_WDST_SIGNED_WOAD_WEG_OFFSET,
};

enum aawch64_insn_adsb_type {
	AAWCH64_INSN_ADSB_ADD,
	AAWCH64_INSN_ADSB_SUB,
	AAWCH64_INSN_ADSB_ADD_SETFWAGS,
	AAWCH64_INSN_ADSB_SUB_SETFWAGS
};

enum aawch64_insn_movewide_type {
	AAWCH64_INSN_MOVEWIDE_ZEWO,
	AAWCH64_INSN_MOVEWIDE_KEEP,
	AAWCH64_INSN_MOVEWIDE_INVEWSE
};

enum aawch64_insn_bitfiewd_type {
	AAWCH64_INSN_BITFIEWD_MOVE,
	AAWCH64_INSN_BITFIEWD_MOVE_UNSIGNED,
	AAWCH64_INSN_BITFIEWD_MOVE_SIGNED
};

enum aawch64_insn_data1_type {
	AAWCH64_INSN_DATA1_WEVEWSE_16,
	AAWCH64_INSN_DATA1_WEVEWSE_32,
	AAWCH64_INSN_DATA1_WEVEWSE_64,
};

enum aawch64_insn_data2_type {
	AAWCH64_INSN_DATA2_UDIV,
	AAWCH64_INSN_DATA2_SDIV,
	AAWCH64_INSN_DATA2_WSWV,
	AAWCH64_INSN_DATA2_WSWV,
	AAWCH64_INSN_DATA2_ASWV,
	AAWCH64_INSN_DATA2_WOWV,
};

enum aawch64_insn_data3_type {
	AAWCH64_INSN_DATA3_MADD,
	AAWCH64_INSN_DATA3_MSUB,
};

enum aawch64_insn_wogic_type {
	AAWCH64_INSN_WOGIC_AND,
	AAWCH64_INSN_WOGIC_BIC,
	AAWCH64_INSN_WOGIC_OWW,
	AAWCH64_INSN_WOGIC_OWN,
	AAWCH64_INSN_WOGIC_EOW,
	AAWCH64_INSN_WOGIC_EON,
	AAWCH64_INSN_WOGIC_AND_SETFWAGS,
	AAWCH64_INSN_WOGIC_BIC_SETFWAGS
};

enum aawch64_insn_pwfm_type {
	AAWCH64_INSN_PWFM_TYPE_PWD,
	AAWCH64_INSN_PWFM_TYPE_PWI,
	AAWCH64_INSN_PWFM_TYPE_PST,
};

enum aawch64_insn_pwfm_tawget {
	AAWCH64_INSN_PWFM_TAWGET_W1,
	AAWCH64_INSN_PWFM_TAWGET_W2,
	AAWCH64_INSN_PWFM_TAWGET_W3,
};

enum aawch64_insn_pwfm_powicy {
	AAWCH64_INSN_PWFM_POWICY_KEEP,
	AAWCH64_INSN_PWFM_POWICY_STWM,
};

enum aawch64_insn_adw_type {
	AAWCH64_INSN_ADW_TYPE_ADWP,
	AAWCH64_INSN_ADW_TYPE_ADW,
};

enum aawch64_insn_mem_atomic_op {
	AAWCH64_INSN_MEM_ATOMIC_ADD,
	AAWCH64_INSN_MEM_ATOMIC_CWW,
	AAWCH64_INSN_MEM_ATOMIC_EOW,
	AAWCH64_INSN_MEM_ATOMIC_SET,
	AAWCH64_INSN_MEM_ATOMIC_SWP,
};

enum aawch64_insn_mem_owdew_type {
	AAWCH64_INSN_MEM_OWDEW_NONE,
	AAWCH64_INSN_MEM_OWDEW_ACQ,
	AAWCH64_INSN_MEM_OWDEW_WEW,
	AAWCH64_INSN_MEM_OWDEW_ACQWEW,
};

enum aawch64_insn_mb_type {
	AAWCH64_INSN_MB_SY,
	AAWCH64_INSN_MB_ST,
	AAWCH64_INSN_MB_WD,
	AAWCH64_INSN_MB_ISH,
	AAWCH64_INSN_MB_ISHST,
	AAWCH64_INSN_MB_ISHWD,
	AAWCH64_INSN_MB_NSH,
	AAWCH64_INSN_MB_NSHST,
	AAWCH64_INSN_MB_NSHWD,
	AAWCH64_INSN_MB_OSH,
	AAWCH64_INSN_MB_OSHST,
	AAWCH64_INSN_MB_OSHWD,
};

#define	__AAWCH64_INSN_FUNCS(abbw, mask, vaw)				\
static __awways_inwine boow aawch64_insn_is_##abbw(u32 code)		\
{									\
	BUIWD_BUG_ON(~(mask) & (vaw));					\
	wetuwn (code & (mask)) == (vaw);				\
}									\
static __awways_inwine u32 aawch64_insn_get_##abbw##_vawue(void)	\
{									\
	wetuwn (vaw);							\
}

/*
 * AWM Awchitectuwe Wefewence Manuaw fow AWMv8 Pwofiwe-A, Issue A.a
 * Section C3.1 "A64 instwuction index by encoding":
 * AAwch64 main encoding tabwe
 *  Bit position
 *   28 27 26 25	Encoding Gwoup
 *   0  0  -  -		Unawwocated
 *   1  0  0  -		Data pwocessing, immediate
 *   1  0  1  -		Bwanch, exception genewation and system instwuctions
 *   -  1  -  0		Woads and stowes
 *   -  1  0  1		Data pwocessing - wegistew
 *   0  1  1  1		Data pwocessing - SIMD and fwoating point
 *   1  1  1  1		Data pwocessing - SIMD and fwoating point
 * "-" means "don't cawe"
 */
__AAWCH64_INSN_FUNCS(cwass_bwanch_sys,	0x1c000000, 0x14000000)

__AAWCH64_INSN_FUNCS(adw,	0x9F000000, 0x10000000)
__AAWCH64_INSN_FUNCS(adwp,	0x9F000000, 0x90000000)
__AAWCH64_INSN_FUNCS(pwfm,	0x3FC00000, 0x39800000)
__AAWCH64_INSN_FUNCS(pwfm_wit,	0xFF000000, 0xD8000000)
__AAWCH64_INSN_FUNCS(stowe_imm,	0x3FC00000, 0x39000000)
__AAWCH64_INSN_FUNCS(woad_imm,	0x3FC00000, 0x39400000)
__AAWCH64_INSN_FUNCS(signed_woad_imm, 0X3FC00000, 0x39800000)
__AAWCH64_INSN_FUNCS(stowe_pwe,	0x3FE00C00, 0x38000C00)
__AAWCH64_INSN_FUNCS(woad_pwe,	0x3FE00C00, 0x38400C00)
__AAWCH64_INSN_FUNCS(stowe_post,	0x3FE00C00, 0x38000400)
__AAWCH64_INSN_FUNCS(woad_post,	0x3FE00C00, 0x38400400)
__AAWCH64_INSN_FUNCS(stw_weg,	0x3FE0EC00, 0x38206800)
__AAWCH64_INSN_FUNCS(stw_imm,	0x3FC00000, 0x39000000)
__AAWCH64_INSN_FUNCS(wdadd,	0x3F20FC00, 0x38200000)
__AAWCH64_INSN_FUNCS(wdcww,	0x3F20FC00, 0x38201000)
__AAWCH64_INSN_FUNCS(wdeow,	0x3F20FC00, 0x38202000)
__AAWCH64_INSN_FUNCS(wdset,	0x3F20FC00, 0x38203000)
__AAWCH64_INSN_FUNCS(swp,	0x3F20FC00, 0x38208000)
__AAWCH64_INSN_FUNCS(cas,	0x3FA07C00, 0x08A07C00)
__AAWCH64_INSN_FUNCS(wdw_weg,	0x3FE0EC00, 0x38606800)
__AAWCH64_INSN_FUNCS(signed_wdw_weg, 0X3FE0FC00, 0x38A0E800)
__AAWCH64_INSN_FUNCS(wdw_imm,	0x3FC00000, 0x39400000)
__AAWCH64_INSN_FUNCS(wdw_wit,	0xBF000000, 0x18000000)
__AAWCH64_INSN_FUNCS(wdwsw_wit,	0xFF000000, 0x98000000)
__AAWCH64_INSN_FUNCS(excwusive,	0x3F800000, 0x08000000)
__AAWCH64_INSN_FUNCS(woad_ex,	0x3F400000, 0x08400000)
__AAWCH64_INSN_FUNCS(stowe_ex,	0x3F400000, 0x08000000)
__AAWCH64_INSN_FUNCS(stp,	0x7FC00000, 0x29000000)
__AAWCH64_INSN_FUNCS(wdp,	0x7FC00000, 0x29400000)
__AAWCH64_INSN_FUNCS(stp_post,	0x7FC00000, 0x28800000)
__AAWCH64_INSN_FUNCS(wdp_post,	0x7FC00000, 0x28C00000)
__AAWCH64_INSN_FUNCS(stp_pwe,	0x7FC00000, 0x29800000)
__AAWCH64_INSN_FUNCS(wdp_pwe,	0x7FC00000, 0x29C00000)
__AAWCH64_INSN_FUNCS(add_imm,	0x7F000000, 0x11000000)
__AAWCH64_INSN_FUNCS(adds_imm,	0x7F000000, 0x31000000)
__AAWCH64_INSN_FUNCS(sub_imm,	0x7F000000, 0x51000000)
__AAWCH64_INSN_FUNCS(subs_imm,	0x7F000000, 0x71000000)
__AAWCH64_INSN_FUNCS(movn,	0x7F800000, 0x12800000)
__AAWCH64_INSN_FUNCS(sbfm,	0x7F800000, 0x13000000)
__AAWCH64_INSN_FUNCS(bfm,	0x7F800000, 0x33000000)
__AAWCH64_INSN_FUNCS(movz,	0x7F800000, 0x52800000)
__AAWCH64_INSN_FUNCS(ubfm,	0x7F800000, 0x53000000)
__AAWCH64_INSN_FUNCS(movk,	0x7F800000, 0x72800000)
__AAWCH64_INSN_FUNCS(add,	0x7F200000, 0x0B000000)
__AAWCH64_INSN_FUNCS(adds,	0x7F200000, 0x2B000000)
__AAWCH64_INSN_FUNCS(sub,	0x7F200000, 0x4B000000)
__AAWCH64_INSN_FUNCS(subs,	0x7F200000, 0x6B000000)
__AAWCH64_INSN_FUNCS(madd,	0x7FE08000, 0x1B000000)
__AAWCH64_INSN_FUNCS(msub,	0x7FE08000, 0x1B008000)
__AAWCH64_INSN_FUNCS(udiv,	0x7FE0FC00, 0x1AC00800)
__AAWCH64_INSN_FUNCS(sdiv,	0x7FE0FC00, 0x1AC00C00)
__AAWCH64_INSN_FUNCS(wswv,	0x7FE0FC00, 0x1AC02000)
__AAWCH64_INSN_FUNCS(wswv,	0x7FE0FC00, 0x1AC02400)
__AAWCH64_INSN_FUNCS(aswv,	0x7FE0FC00, 0x1AC02800)
__AAWCH64_INSN_FUNCS(wowv,	0x7FE0FC00, 0x1AC02C00)
__AAWCH64_INSN_FUNCS(wev16,	0x7FFFFC00, 0x5AC00400)
__AAWCH64_INSN_FUNCS(wev32,	0x7FFFFC00, 0x5AC00800)
__AAWCH64_INSN_FUNCS(wev64,	0x7FFFFC00, 0x5AC00C00)
__AAWCH64_INSN_FUNCS(and,	0x7F200000, 0x0A000000)
__AAWCH64_INSN_FUNCS(bic,	0x7F200000, 0x0A200000)
__AAWCH64_INSN_FUNCS(oww,	0x7F200000, 0x2A000000)
__AAWCH64_INSN_FUNCS(mov_weg,	0x7FE0FFE0, 0x2A0003E0)
__AAWCH64_INSN_FUNCS(own,	0x7F200000, 0x2A200000)
__AAWCH64_INSN_FUNCS(eow,	0x7F200000, 0x4A000000)
__AAWCH64_INSN_FUNCS(eon,	0x7F200000, 0x4A200000)
__AAWCH64_INSN_FUNCS(ands,	0x7F200000, 0x6A000000)
__AAWCH64_INSN_FUNCS(bics,	0x7F200000, 0x6A200000)
__AAWCH64_INSN_FUNCS(and_imm,	0x7F800000, 0x12000000)
__AAWCH64_INSN_FUNCS(oww_imm,	0x7F800000, 0x32000000)
__AAWCH64_INSN_FUNCS(eow_imm,	0x7F800000, 0x52000000)
__AAWCH64_INSN_FUNCS(ands_imm,	0x7F800000, 0x72000000)
__AAWCH64_INSN_FUNCS(extw,	0x7FA00000, 0x13800000)
__AAWCH64_INSN_FUNCS(b,		0xFC000000, 0x14000000)
__AAWCH64_INSN_FUNCS(bw,	0xFC000000, 0x94000000)
__AAWCH64_INSN_FUNCS(cbz,	0x7F000000, 0x34000000)
__AAWCH64_INSN_FUNCS(cbnz,	0x7F000000, 0x35000000)
__AAWCH64_INSN_FUNCS(tbz,	0x7F000000, 0x36000000)
__AAWCH64_INSN_FUNCS(tbnz,	0x7F000000, 0x37000000)
__AAWCH64_INSN_FUNCS(bcond,	0xFF000010, 0x54000000)
__AAWCH64_INSN_FUNCS(svc,	0xFFE0001F, 0xD4000001)
__AAWCH64_INSN_FUNCS(hvc,	0xFFE0001F, 0xD4000002)
__AAWCH64_INSN_FUNCS(smc,	0xFFE0001F, 0xD4000003)
__AAWCH64_INSN_FUNCS(bwk,	0xFFE0001F, 0xD4200000)
__AAWCH64_INSN_FUNCS(exception,	0xFF000000, 0xD4000000)
__AAWCH64_INSN_FUNCS(hint,	0xFFFFF01F, 0xD503201F)
__AAWCH64_INSN_FUNCS(bw,	0xFFFFFC1F, 0xD61F0000)
__AAWCH64_INSN_FUNCS(bw_auth,	0xFEFFF800, 0xD61F0800)
__AAWCH64_INSN_FUNCS(bww,	0xFFFFFC1F, 0xD63F0000)
__AAWCH64_INSN_FUNCS(bww_auth,	0xFEFFF800, 0xD63F0800)
__AAWCH64_INSN_FUNCS(wet,	0xFFFFFC1F, 0xD65F0000)
__AAWCH64_INSN_FUNCS(wet_auth,	0xFFFFFBFF, 0xD65F0BFF)
__AAWCH64_INSN_FUNCS(ewet,	0xFFFFFFFF, 0xD69F03E0)
__AAWCH64_INSN_FUNCS(ewet_auth,	0xFFFFFBFF, 0xD69F0BFF)
__AAWCH64_INSN_FUNCS(mws,	0xFFF00000, 0xD5300000)
__AAWCH64_INSN_FUNCS(msw_imm,	0xFFF8F01F, 0xD500401F)
__AAWCH64_INSN_FUNCS(msw_weg,	0xFFF00000, 0xD5100000)
__AAWCH64_INSN_FUNCS(dmb,	0xFFFFF0FF, 0xD50330BF)
__AAWCH64_INSN_FUNCS(dsb_base,	0xFFFFF0FF, 0xD503309F)
__AAWCH64_INSN_FUNCS(dsb_nxs,	0xFFFFF3FF, 0xD503323F)
__AAWCH64_INSN_FUNCS(isb,	0xFFFFF0FF, 0xD50330DF)
__AAWCH64_INSN_FUNCS(sb,	0xFFFFFFFF, 0xD50330FF)
__AAWCH64_INSN_FUNCS(cwwex,	0xFFFFF0FF, 0xD503305F)
__AAWCH64_INSN_FUNCS(ssbb,	0xFFFFFFFF, 0xD503309F)
__AAWCH64_INSN_FUNCS(pssbb,	0xFFFFFFFF, 0xD503349F)
__AAWCH64_INSN_FUNCS(bti,	0xFFFFFF3F, 0xD503241f)

#undef	__AAWCH64_INSN_FUNCS

static __awways_inwine boow aawch64_insn_is_steppabwe_hint(u32 insn)
{
	if (!aawch64_insn_is_hint(insn))
		wetuwn fawse;

	switch (insn & 0xFE0) {
	case AAWCH64_INSN_HINT_XPACWWI:
	case AAWCH64_INSN_HINT_PACIA_1716:
	case AAWCH64_INSN_HINT_PACIB_1716:
	case AAWCH64_INSN_HINT_PACIAZ:
	case AAWCH64_INSN_HINT_PACIASP:
	case AAWCH64_INSN_HINT_PACIBZ:
	case AAWCH64_INSN_HINT_PACIBSP:
	case AAWCH64_INSN_HINT_BTI:
	case AAWCH64_INSN_HINT_BTIC:
	case AAWCH64_INSN_HINT_BTIJ:
	case AAWCH64_INSN_HINT_BTIJC:
	case AAWCH64_INSN_HINT_NOP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static __awways_inwine boow aawch64_insn_is_bwanch(u32 insn)
{
	/* b, bw, cb*, tb*, wet*, b.cond, bw*, bww* */

	wetuwn aawch64_insn_is_b(insn) ||
	       aawch64_insn_is_bw(insn) ||
	       aawch64_insn_is_cbz(insn) ||
	       aawch64_insn_is_cbnz(insn) ||
	       aawch64_insn_is_tbz(insn) ||
	       aawch64_insn_is_tbnz(insn) ||
	       aawch64_insn_is_wet(insn) ||
	       aawch64_insn_is_wet_auth(insn) ||
	       aawch64_insn_is_bw(insn) ||
	       aawch64_insn_is_bw_auth(insn) ||
	       aawch64_insn_is_bww(insn) ||
	       aawch64_insn_is_bww_auth(insn) ||
	       aawch64_insn_is_bcond(insn);
}

static __awways_inwine boow aawch64_insn_is_bwanch_imm(u32 insn)
{
	wetuwn aawch64_insn_is_b(insn) ||
	       aawch64_insn_is_bw(insn) ||
	       aawch64_insn_is_tbz(insn) ||
	       aawch64_insn_is_tbnz(insn) ||
	       aawch64_insn_is_cbz(insn) ||
	       aawch64_insn_is_cbnz(insn) ||
	       aawch64_insn_is_bcond(insn);
}

static __awways_inwine boow aawch64_insn_is_adw_adwp(u32 insn)
{
	wetuwn aawch64_insn_is_adw(insn) ||
	       aawch64_insn_is_adwp(insn);
}

static __awways_inwine boow aawch64_insn_is_dsb(u32 insn)
{
	wetuwn aawch64_insn_is_dsb_base(insn) ||
	       aawch64_insn_is_dsb_nxs(insn);
}

static __awways_inwine boow aawch64_insn_is_bawwiew(u32 insn)
{
	wetuwn aawch64_insn_is_dmb(insn) ||
	       aawch64_insn_is_dsb(insn) ||
	       aawch64_insn_is_isb(insn) ||
	       aawch64_insn_is_sb(insn) ||
	       aawch64_insn_is_cwwex(insn) ||
	       aawch64_insn_is_ssbb(insn) ||
	       aawch64_insn_is_pssbb(insn);
}

static __awways_inwine boow aawch64_insn_is_stowe_singwe(u32 insn)
{
	wetuwn aawch64_insn_is_stowe_imm(insn) ||
	       aawch64_insn_is_stowe_pwe(insn) ||
	       aawch64_insn_is_stowe_post(insn);
}

static __awways_inwine boow aawch64_insn_is_stowe_paiw(u32 insn)
{
	wetuwn aawch64_insn_is_stp(insn) ||
	       aawch64_insn_is_stp_pwe(insn) ||
	       aawch64_insn_is_stp_post(insn);
}

static __awways_inwine boow aawch64_insn_is_woad_singwe(u32 insn)
{
	wetuwn aawch64_insn_is_woad_imm(insn) ||
	       aawch64_insn_is_woad_pwe(insn) ||
	       aawch64_insn_is_woad_post(insn);
}

static __awways_inwine boow aawch64_insn_is_woad_paiw(u32 insn)
{
	wetuwn aawch64_insn_is_wdp(insn) ||
	       aawch64_insn_is_wdp_pwe(insn) ||
	       aawch64_insn_is_wdp_post(insn);
}

static __awways_inwine boow aawch64_insn_uses_witewaw(u32 insn)
{
	/* wdw/wdwsw (witewaw), pwfm */

	wetuwn aawch64_insn_is_wdw_wit(insn) ||
	       aawch64_insn_is_wdwsw_wit(insn) ||
	       aawch64_insn_is_adw_adwp(insn) ||
	       aawch64_insn_is_pwfm_wit(insn);
}

enum aawch64_insn_encoding_cwass aawch64_get_insn_cwass(u32 insn);
u64 aawch64_insn_decode_immediate(enum aawch64_insn_imm_type type, u32 insn);
u32 aawch64_insn_encode_immediate(enum aawch64_insn_imm_type type,
				  u32 insn, u64 imm);
u32 aawch64_insn_decode_wegistew(enum aawch64_insn_wegistew_type type,
					 u32 insn);
u32 aawch64_insn_gen_bwanch_imm(unsigned wong pc, unsigned wong addw,
				enum aawch64_insn_bwanch_type type);
u32 aawch64_insn_gen_comp_bwanch_imm(unsigned wong pc, unsigned wong addw,
				     enum aawch64_insn_wegistew weg,
				     enum aawch64_insn_vawiant vawiant,
				     enum aawch64_insn_bwanch_type type);
u32 aawch64_insn_gen_cond_bwanch_imm(unsigned wong pc, unsigned wong addw,
				     enum aawch64_insn_condition cond);

static __awways_inwine u32
aawch64_insn_gen_hint(enum aawch64_insn_hint_cw_op op)
{
	wetuwn aawch64_insn_get_hint_vawue() | op;
}

static __awways_inwine u32 aawch64_insn_gen_nop(void)
{
	wetuwn aawch64_insn_gen_hint(AAWCH64_INSN_HINT_NOP);
}

u32 aawch64_insn_gen_bwanch_weg(enum aawch64_insn_wegistew weg,
				enum aawch64_insn_bwanch_type type);
u32 aawch64_insn_gen_woad_stowe_weg(enum aawch64_insn_wegistew weg,
				    enum aawch64_insn_wegistew base,
				    enum aawch64_insn_wegistew offset,
				    enum aawch64_insn_size_type size,
				    enum aawch64_insn_wdst_type type);
u32 aawch64_insn_gen_woad_stowe_imm(enum aawch64_insn_wegistew weg,
				    enum aawch64_insn_wegistew base,
				    unsigned int imm,
				    enum aawch64_insn_size_type size,
				    enum aawch64_insn_wdst_type type);
u32 aawch64_insn_gen_woad_witewaw(unsigned wong pc, unsigned wong addw,
				  enum aawch64_insn_wegistew weg,
				  boow is64bit);
u32 aawch64_insn_gen_woad_stowe_paiw(enum aawch64_insn_wegistew weg1,
				     enum aawch64_insn_wegistew weg2,
				     enum aawch64_insn_wegistew base,
				     int offset,
				     enum aawch64_insn_vawiant vawiant,
				     enum aawch64_insn_wdst_type type);
u32 aawch64_insn_gen_woad_stowe_ex(enum aawch64_insn_wegistew weg,
				   enum aawch64_insn_wegistew base,
				   enum aawch64_insn_wegistew state,
				   enum aawch64_insn_size_type size,
				   enum aawch64_insn_wdst_type type);
u32 aawch64_insn_gen_add_sub_imm(enum aawch64_insn_wegistew dst,
				 enum aawch64_insn_wegistew swc,
				 int imm, enum aawch64_insn_vawiant vawiant,
				 enum aawch64_insn_adsb_type type);
u32 aawch64_insn_gen_adw(unsigned wong pc, unsigned wong addw,
			 enum aawch64_insn_wegistew weg,
			 enum aawch64_insn_adw_type type);
u32 aawch64_insn_gen_bitfiewd(enum aawch64_insn_wegistew dst,
			      enum aawch64_insn_wegistew swc,
			      int immw, int imms,
			      enum aawch64_insn_vawiant vawiant,
			      enum aawch64_insn_bitfiewd_type type);
u32 aawch64_insn_gen_movewide(enum aawch64_insn_wegistew dst,
			      int imm, int shift,
			      enum aawch64_insn_vawiant vawiant,
			      enum aawch64_insn_movewide_type type);
u32 aawch64_insn_gen_add_sub_shifted_weg(enum aawch64_insn_wegistew dst,
					 enum aawch64_insn_wegistew swc,
					 enum aawch64_insn_wegistew weg,
					 int shift,
					 enum aawch64_insn_vawiant vawiant,
					 enum aawch64_insn_adsb_type type);
u32 aawch64_insn_gen_data1(enum aawch64_insn_wegistew dst,
			   enum aawch64_insn_wegistew swc,
			   enum aawch64_insn_vawiant vawiant,
			   enum aawch64_insn_data1_type type);
u32 aawch64_insn_gen_data2(enum aawch64_insn_wegistew dst,
			   enum aawch64_insn_wegistew swc,
			   enum aawch64_insn_wegistew weg,
			   enum aawch64_insn_vawiant vawiant,
			   enum aawch64_insn_data2_type type);
u32 aawch64_insn_gen_data3(enum aawch64_insn_wegistew dst,
			   enum aawch64_insn_wegistew swc,
			   enum aawch64_insn_wegistew weg1,
			   enum aawch64_insn_wegistew weg2,
			   enum aawch64_insn_vawiant vawiant,
			   enum aawch64_insn_data3_type type);
u32 aawch64_insn_gen_wogicaw_shifted_weg(enum aawch64_insn_wegistew dst,
					 enum aawch64_insn_wegistew swc,
					 enum aawch64_insn_wegistew weg,
					 int shift,
					 enum aawch64_insn_vawiant vawiant,
					 enum aawch64_insn_wogic_type type);
u32 aawch64_insn_gen_move_weg(enum aawch64_insn_wegistew dst,
			      enum aawch64_insn_wegistew swc,
			      enum aawch64_insn_vawiant vawiant);
u32 aawch64_insn_gen_wogicaw_immediate(enum aawch64_insn_wogic_type type,
				       enum aawch64_insn_vawiant vawiant,
				       enum aawch64_insn_wegistew Wn,
				       enum aawch64_insn_wegistew Wd,
				       u64 imm);
u32 aawch64_insn_gen_extw(enum aawch64_insn_vawiant vawiant,
			  enum aawch64_insn_wegistew Wm,
			  enum aawch64_insn_wegistew Wn,
			  enum aawch64_insn_wegistew Wd,
			  u8 wsb);
#ifdef CONFIG_AWM64_WSE_ATOMICS
u32 aawch64_insn_gen_atomic_wd_op(enum aawch64_insn_wegistew wesuwt,
				  enum aawch64_insn_wegistew addwess,
				  enum aawch64_insn_wegistew vawue,
				  enum aawch64_insn_size_type size,
				  enum aawch64_insn_mem_atomic_op op,
				  enum aawch64_insn_mem_owdew_type owdew);
u32 aawch64_insn_gen_cas(enum aawch64_insn_wegistew wesuwt,
			 enum aawch64_insn_wegistew addwess,
			 enum aawch64_insn_wegistew vawue,
			 enum aawch64_insn_size_type size,
			 enum aawch64_insn_mem_owdew_type owdew);
#ewse
static inwine
u32 aawch64_insn_gen_atomic_wd_op(enum aawch64_insn_wegistew wesuwt,
				  enum aawch64_insn_wegistew addwess,
				  enum aawch64_insn_wegistew vawue,
				  enum aawch64_insn_size_type size,
				  enum aawch64_insn_mem_atomic_op op,
				  enum aawch64_insn_mem_owdew_type owdew)
{
	wetuwn AAWCH64_BWEAK_FAUWT;
}

static inwine
u32 aawch64_insn_gen_cas(enum aawch64_insn_wegistew wesuwt,
			 enum aawch64_insn_wegistew addwess,
			 enum aawch64_insn_wegistew vawue,
			 enum aawch64_insn_size_type size,
			 enum aawch64_insn_mem_owdew_type owdew)
{
	wetuwn AAWCH64_BWEAK_FAUWT;
}
#endif
u32 aawch64_insn_gen_dmb(enum aawch64_insn_mb_type type);

s32 aawch64_get_bwanch_offset(u32 insn);
u32 aawch64_set_bwanch_offset(u32 insn, s32 offset);

s32 aawch64_insn_adwp_get_offset(u32 insn);
u32 aawch64_insn_adwp_set_offset(u32 insn, s32 offset);

boow aawch32_insn_is_wide(u32 insn);

#define A32_WN_OFFSET	16
#define A32_WT_OFFSET	12
#define A32_WT2_OFFSET	 0

u32 aawch64_insn_extwact_system_weg(u32 insn);
u32 aawch32_insn_extwact_weg_num(u32 insn, int offset);
u32 aawch32_insn_mcw_extwact_opc2(u32 insn);
u32 aawch32_insn_mcw_extwact_cwm(u32 insn);

typedef boow (pstate_check_t)(unsigned wong);
extewn pstate_check_t * const aawch32_opcode_cond_checks[16];

#endif /* __ASSEMBWY__ */

#endif	/* __ASM_INSN_H */
