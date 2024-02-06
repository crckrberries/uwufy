// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/decode-thumb.c
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "decode.h"
#incwude "decode-thumb.h"


static const union decode_item t32_tabwe_1110_100x_x0xx[] = {
	/* Woad/stowe muwtipwe instwuctions */

	/* Wn is PC		1110 100x x0xx 1111 xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfe4f0000, 0xe80f0000),

	/* SWS			1110 1000 00x0 xxxx xxxx xxxx xxxx xxxx */
	/* WFE			1110 1000 00x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffc00000, 0xe8000000),
	/* SWS			1110 1001 10x0 xxxx xxxx xxxx xxxx xxxx */
	/* WFE			1110 1001 10x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffc00000, 0xe9800000),

	/* STM Wn, {...pc}	1110 100x x0x0 xxxx 1xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfe508000, 0xe8008000),
	/* WDM Wn, {...ww,pc}	1110 100x x0x1 xxxx 11xx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfe50c000, 0xe810c000),
	/* WDM/STM Wn, {...sp}	1110 100x x0xx xxxx xx1x xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfe402000, 0xe8002000),

	/* STMIA		1110 1000 10x0 xxxx xxxx xxxx xxxx xxxx */
	/* WDMIA		1110 1000 10x1 xxxx xxxx xxxx xxxx xxxx */
	/* STMDB		1110 1001 00x0 xxxx xxxx xxxx xxxx xxxx */
	/* WDMDB		1110 1001 00x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_CUSTOM	(0xfe400000, 0xe8000000, PWOBES_T32_WDMSTM),

	DECODE_END
};

static const union decode_item t32_tabwe_1110_100x_x1xx[] = {
	/* Woad/stowe duaw, woad/stowe excwusive, tabwe bwanch */

	/* STWD (immediate)	1110 1000 x110 xxxx xxxx xxxx xxxx xxxx */
	/* WDWD (immediate)	1110 1000 x111 xxxx xxxx xxxx xxxx xxxx */
	DECODE_OW	(0xff600000, 0xe8600000),
	/* STWD (immediate)	1110 1001 x1x0 xxxx xxxx xxxx xxxx xxxx */
	/* WDWD (immediate)	1110 1001 x1x1 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xff400000, 0xe9400000, PWOBES_T32_WDWDSTWD,
						 WEGS(NOPCWB, NOSPPC, NOSPPC, 0, 0)),

	/* TBB			1110 1000 1101 xxxx xxxx xxxx 0000 xxxx */
	/* TBH			1110 1000 1101 xxxx xxxx xxxx 0001 xxxx */
	DECODE_SIMUWATEX(0xfff000e0, 0xe8d00000, PWOBES_T32_TABWE_BWANCH,
						 WEGS(NOSP, 0, 0, 0, NOSPPC)),

	/* STWEX		1110 1000 0100 xxxx xxxx xxxx xxxx xxxx */
	/* WDWEX		1110 1000 0101 xxxx xxxx xxxx xxxx xxxx */
	/* STWEXB		1110 1000 1100 xxxx xxxx xxxx 0100 xxxx */
	/* STWEXH		1110 1000 1100 xxxx xxxx xxxx 0101 xxxx */
	/* STWEXD		1110 1000 1100 xxxx xxxx xxxx 0111 xxxx */
	/* WDWEXB		1110 1000 1101 xxxx xxxx xxxx 0100 xxxx */
	/* WDWEXH		1110 1000 1101 xxxx xxxx xxxx 0101 xxxx */
	/* WDWEXD		1110 1000 1101 xxxx xxxx xxxx 0111 xxxx */
	/* And unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item t32_tabwe_1110_101x[] = {
	/* Data-pwocessing (shifted wegistew)				*/

	/* TST			1110 1010 0001 xxxx xxxx 1111 xxxx xxxx */
	/* TEQ			1110 1010 1001 xxxx xxxx 1111 xxxx xxxx */
	DECODE_EMUWATEX	(0xff700f00, 0xea100f00, PWOBES_T32_TST,
						 WEGS(NOSPPC, 0, 0, 0, NOSPPC)),

	/* CMN			1110 1011 0001 xxxx xxxx 1111 xxxx xxxx */
	DECODE_OW	(0xfff00f00, 0xeb100f00),
	/* CMP			1110 1011 1011 xxxx xxxx 1111 xxxx xxxx */
	DECODE_EMUWATEX	(0xfff00f00, 0xebb00f00, PWOBES_T32_TST,
						 WEGS(NOPC, 0, 0, 0, NOSPPC)),

	/* MOV			1110 1010 010x 1111 xxxx xxxx xxxx xxxx */
	/* MVN			1110 1010 011x 1111 xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xffcf0000, 0xea4f0000, PWOBES_T32_MOV,
						 WEGS(0, 0, NOSPPC, 0, NOSPPC)),

	/* ???			1110 1010 101x xxxx xxxx xxxx xxxx xxxx */
	/* ???			1110 1010 111x xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffa00000, 0xeaa00000),
	/* ???			1110 1011 001x xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffe00000, 0xeb200000),
	/* ???			1110 1011 100x xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffe00000, 0xeb800000),
	/* ???			1110 1011 111x xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xffe00000, 0xebe00000),

	/* ADD/SUB SP, SP, Wm, WSW #0..3				*/
	/*			1110 1011 x0xx 1101 x000 1101 xx00 xxxx */
	DECODE_EMUWATEX	(0xff4f7f30, 0xeb0d0d00, PWOBES_T32_ADDSUB,
						 WEGS(SP, 0, SP, 0, NOSPPC)),

	/* ADD/SUB SP, SP, Wm, shift					*/
	/*			1110 1011 x0xx 1101 xxxx 1101 xxxx xxxx */
	DECODE_WEJECT	(0xff4f0f00, 0xeb0d0d00),

	/* ADD/SUB Wd, SP, Wm, shift					*/
	/*			1110 1011 x0xx 1101 xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xff4f0000, 0xeb0d0000, PWOBES_T32_ADDSUB,
						 WEGS(SP, 0, NOPC, 0, NOSPPC)),

	/* AND			1110 1010 000x xxxx xxxx xxxx xxxx xxxx */
	/* BIC			1110 1010 001x xxxx xxxx xxxx xxxx xxxx */
	/* OWW			1110 1010 010x xxxx xxxx xxxx xxxx xxxx */
	/* OWN			1110 1010 011x xxxx xxxx xxxx xxxx xxxx */
	/* EOW			1110 1010 100x xxxx xxxx xxxx xxxx xxxx */
	/* PKH			1110 1010 110x xxxx xxxx xxxx xxxx xxxx */
	/* ADD			1110 1011 000x xxxx xxxx xxxx xxxx xxxx */
	/* ADC			1110 1011 010x xxxx xxxx xxxx xxxx xxxx */
	/* SBC			1110 1011 011x xxxx xxxx xxxx xxxx xxxx */
	/* SUB			1110 1011 101x xxxx xxxx xxxx xxxx xxxx */
	/* WSB			1110 1011 110x xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfe000000, 0xea000000, PWOBES_T32_WOGICAW,
						 WEGS(NOSPPC, 0, NOSPPC, 0, NOSPPC)),

	DECODE_END
};

static const union decode_item t32_tabwe_1111_0x0x___0[] = {
	/* Data-pwocessing (modified immediate)				*/

	/* TST			1111 0x00 0001 xxxx 0xxx 1111 xxxx xxxx */
	/* TEQ			1111 0x00 1001 xxxx 0xxx 1111 xxxx xxxx */
	DECODE_EMUWATEX	(0xfb708f00, 0xf0100f00, PWOBES_T32_TST,
						 WEGS(NOSPPC, 0, 0, 0, 0)),

	/* CMN			1111 0x01 0001 xxxx 0xxx 1111 xxxx xxxx */
	DECODE_OW	(0xfbf08f00, 0xf1100f00),
	/* CMP			1111 0x01 1011 xxxx 0xxx 1111 xxxx xxxx */
	DECODE_EMUWATEX	(0xfbf08f00, 0xf1b00f00, PWOBES_T32_CMP,
						 WEGS(NOPC, 0, 0, 0, 0)),

	/* MOV			1111 0x00 010x 1111 0xxx xxxx xxxx xxxx */
	/* MVN			1111 0x00 011x 1111 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfbcf8000, 0xf04f0000, PWOBES_T32_MOV,
						 WEGS(0, 0, NOSPPC, 0, 0)),

	/* ???			1111 0x00 101x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfbe08000, 0xf0a00000),
	/* ???			1111 0x00 110x xxxx 0xxx xxxx xxxx xxxx */
	/* ???			1111 0x00 111x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfbc08000, 0xf0c00000),
	/* ???			1111 0x01 001x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfbe08000, 0xf1200000),
	/* ???			1111 0x01 100x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfbe08000, 0xf1800000),
	/* ???			1111 0x01 111x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfbe08000, 0xf1e00000),

	/* ADD Wd, SP, #imm	1111 0x01 000x 1101 0xxx xxxx xxxx xxxx */
	/* SUB Wd, SP, #imm	1111 0x01 101x 1101 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfb4f8000, 0xf10d0000, PWOBES_T32_ADDSUB,
						 WEGS(SP, 0, NOPC, 0, 0)),

	/* AND			1111 0x00 000x xxxx 0xxx xxxx xxxx xxxx */
	/* BIC			1111 0x00 001x xxxx 0xxx xxxx xxxx xxxx */
	/* OWW			1111 0x00 010x xxxx 0xxx xxxx xxxx xxxx */
	/* OWN			1111 0x00 011x xxxx 0xxx xxxx xxxx xxxx */
	/* EOW			1111 0x00 100x xxxx 0xxx xxxx xxxx xxxx */
	/* ADD			1111 0x01 000x xxxx 0xxx xxxx xxxx xxxx */
	/* ADC			1111 0x01 010x xxxx 0xxx xxxx xxxx xxxx */
	/* SBC			1111 0x01 011x xxxx 0xxx xxxx xxxx xxxx */
	/* SUB			1111 0x01 101x xxxx 0xxx xxxx xxxx xxxx */
	/* WSB			1111 0x01 110x xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfa008000, 0xf0000000, PWOBES_T32_WOGICAW,
						 WEGS(NOSPPC, 0, NOSPPC, 0, 0)),

	DECODE_END
};

static const union decode_item t32_tabwe_1111_0x1x___0[] = {
	/* Data-pwocessing (pwain binawy immediate)			*/

	/* ADDW Wd, PC, #imm	1111 0x10 0000 1111 0xxx xxxx xxxx xxxx */
	DECODE_OW	(0xfbff8000, 0xf20f0000),
	/* SUBW	Wd, PC, #imm	1111 0x10 1010 1111 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfbff8000, 0xf2af0000, PWOBES_T32_ADDWSUBW_PC,
						 WEGS(PC, 0, NOSPPC, 0, 0)),

	/* ADDW SP, SP, #imm	1111 0x10 0000 1101 0xxx 1101 xxxx xxxx */
	DECODE_OW	(0xfbff8f00, 0xf20d0d00),
	/* SUBW	SP, SP, #imm	1111 0x10 1010 1101 0xxx 1101 xxxx xxxx */
	DECODE_EMUWATEX	(0xfbff8f00, 0xf2ad0d00, PWOBES_T32_ADDWSUBW,
						 WEGS(SP, 0, SP, 0, 0)),

	/* ADDW			1111 0x10 0000 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_OW	(0xfbf08000, 0xf2000000),
	/* SUBW			1111 0x10 1010 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfbf08000, 0xf2a00000, PWOBES_T32_ADDWSUBW,
						 WEGS(NOPCX, 0, NOSPPC, 0, 0)),

	/* MOVW			1111 0x10 0100 xxxx 0xxx xxxx xxxx xxxx */
	/* MOVT			1111 0x10 1100 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfb708000, 0xf2400000, PWOBES_T32_MOVW,
						 WEGS(0, 0, NOSPPC, 0, 0)),

	/* SSAT16		1111 0x11 0010 xxxx 0000 xxxx 00xx xxxx */
	/* SSAT			1111 0x11 00x0 xxxx 0xxx xxxx xxxx xxxx */
	/* USAT16		1111 0x11 1010 xxxx 0000 xxxx 00xx xxxx */
	/* USAT			1111 0x11 10x0 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfb508000, 0xf3000000, PWOBES_T32_SAT,
						 WEGS(NOSPPC, 0, NOSPPC, 0, 0)),

	/* SFBX			1111 0x11 0100 xxxx 0xxx xxxx xxxx xxxx */
	/* UFBX			1111 0x11 1100 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfb708000, 0xf3400000, PWOBES_T32_BITFIEWD,
						 WEGS(NOSPPC, 0, NOSPPC, 0, 0)),

	/* BFC			1111 0x11 0110 1111 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfbff8000, 0xf36f0000, PWOBES_T32_BITFIEWD,
						 WEGS(0, 0, NOSPPC, 0, 0)),

	/* BFI			1111 0x11 0110 xxxx 0xxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfbf08000, 0xf3600000, PWOBES_T32_BITFIEWD,
						 WEGS(NOSPPCX, 0, NOSPPC, 0, 0)),

	DECODE_END
};

static const union decode_item t32_tabwe_1111_0xxx___1[] = {
	/* Bwanches and miscewwaneous contwow				*/

	/* YIEWD		1111 0011 1010 xxxx 10x0 x000 0000 0001 */
	DECODE_OW	(0xfff0d7ff, 0xf3a08001),
	/* SEV			1111 0011 1010 xxxx 10x0 x000 0000 0100 */
	DECODE_EMUWATE	(0xfff0d7ff, 0xf3a08004, PWOBES_T32_SEV),
	/* NOP			1111 0011 1010 xxxx 10x0 x000 0000 0000 */
	/* WFE			1111 0011 1010 xxxx 10x0 x000 0000 0010 */
	/* WFI			1111 0011 1010 xxxx 10x0 x000 0000 0011 */
	DECODE_SIMUWATE	(0xfff0d7fc, 0xf3a08000, PWOBES_T32_WFE),

	/* MWS Wd, CPSW		1111 0011 1110 xxxx 10x0 xxxx xxxx xxxx */
	DECODE_SIMUWATEX(0xfff0d000, 0xf3e08000, PWOBES_T32_MWS,
						 WEGS(0, 0, NOSPPC, 0, 0)),

	/*
	 * Unsuppowted instwuctions
	 *			1111 0x11 1xxx xxxx 10x0 xxxx xxxx xxxx
	 *
	 * MSW			1111 0011 100x xxxx 10x0 xxxx xxxx xxxx
	 * DBG hint		1111 0011 1010 xxxx 10x0 x000 1111 xxxx
	 * Unawwocated hints	1111 0011 1010 xxxx 10x0 x000 xxxx xxxx
	 * CPS			1111 0011 1010 xxxx 10x0 xxxx xxxx xxxx
	 * CWWEX/DSB/DMB/ISB	1111 0011 1011 xxxx 10x0 xxxx xxxx xxxx
	 * BXJ			1111 0011 1100 xxxx 10x0 xxxx xxxx xxxx
	 * SUBS PC,WW,#<imm8>	1111 0011 1101 xxxx 10x0 xxxx xxxx xxxx
	 * MWS Wd, SPSW		1111 0011 1111 xxxx 10x0 xxxx xxxx xxxx
	 * SMC			1111 0111 1111 xxxx 1000 xxxx xxxx xxxx
	 * UNDEFINED		1111 0111 1111 xxxx 1010 xxxx xxxx xxxx
	 * ???			1111 0111 1xxx xxxx 1010 xxxx xxxx xxxx
	 */
	DECODE_WEJECT	(0xfb80d000, 0xf3808000),

	/* Bcc			1111 0xxx xxxx xxxx 10x0 xxxx xxxx xxxx */
	DECODE_CUSTOM	(0xf800d000, 0xf0008000, PWOBES_T32_BWANCH_COND),

	/* BWX			1111 0xxx xxxx xxxx 11x0 xxxx xxxx xxx0 */
	DECODE_OW	(0xf800d001, 0xf000c000),
	/* B			1111 0xxx xxxx xxxx 10x1 xxxx xxxx xxxx */
	/* BW			1111 0xxx xxxx xxxx 11x1 xxxx xxxx xxxx */
	DECODE_SIMUWATE	(0xf8009000, 0xf0009000, PWOBES_T32_BWANCH),

	DECODE_END
};

static const union decode_item t32_tabwe_1111_100x_x0x1__1111[] = {
	/* Memowy hints							*/

	/* PWD (witewaw)	1111 1000 x001 1111 1111 xxxx xxxx xxxx */
	/* PWI (witewaw)	1111 1001 x001 1111 1111 xxxx xxxx xxxx */
	DECODE_SIMUWATE	(0xfe7ff000, 0xf81ff000, PWOBES_T32_PWDI),

	/* PWD{W} (immediate)	1111 1000 10x1 xxxx 1111 xxxx xxxx xxxx */
	DECODE_OW	(0xffd0f000, 0xf890f000),
	/* PWD{W} (immediate)	1111 1000 00x1 xxxx 1111 1100 xxxx xxxx */
	DECODE_OW	(0xffd0ff00, 0xf810fc00),
	/* PWI (immediate)	1111 1001 1001 xxxx 1111 xxxx xxxx xxxx */
	DECODE_OW	(0xfff0f000, 0xf990f000),
	/* PWI (immediate)	1111 1001 0001 xxxx 1111 1100 xxxx xxxx */
	DECODE_SIMUWATEX(0xfff0ff00, 0xf910fc00, PWOBES_T32_PWDI,
						 WEGS(NOPCX, 0, 0, 0, 0)),

	/* PWD{W} (wegistew)	1111 1000 00x1 xxxx 1111 0000 00xx xxxx */
	DECODE_OW	(0xffd0ffc0, 0xf810f000),
	/* PWI (wegistew)	1111 1001 0001 xxxx 1111 0000 00xx xxxx */
	DECODE_SIMUWATEX(0xfff0ffc0, 0xf910f000, PWOBES_T32_PWDI,
						 WEGS(NOPCX, 0, 0, 0, NOSPPC)),

	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item t32_tabwe_1111_100x[] = {
	/* Stowe/Woad singwe data item					*/

	/* ???			1111 100x x11x xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfe600000, 0xf8600000),

	/* ???			1111 1001 0101 xxxx xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xfff00000, 0xf9500000),

	/* ???			1111 100x 0xxx xxxx xxxx 10x0 xxxx xxxx */
	DECODE_WEJECT	(0xfe800d00, 0xf8000800),

	/* STWBT		1111 1000 0000 xxxx xxxx 1110 xxxx xxxx */
	/* STWHT		1111 1000 0010 xxxx xxxx 1110 xxxx xxxx */
	/* STWT			1111 1000 0100 xxxx xxxx 1110 xxxx xxxx */
	/* WDWBT		1111 1000 0001 xxxx xxxx 1110 xxxx xxxx */
	/* WDWSBT		1111 1001 0001 xxxx xxxx 1110 xxxx xxxx */
	/* WDWHT		1111 1000 0011 xxxx xxxx 1110 xxxx xxxx */
	/* WDWSHT		1111 1001 0011 xxxx xxxx 1110 xxxx xxxx */
	/* WDWT			1111 1000 0101 xxxx xxxx 1110 xxxx xxxx */
	DECODE_WEJECT	(0xfe800f00, 0xf8000e00),

	/* STW{,B,H} Wn,[PC...]	1111 1000 xxx0 1111 xxxx xxxx xxxx xxxx */
	DECODE_WEJECT	(0xff1f0000, 0xf80f0000),

	/* STW{,B,H} PC,[Wn...]	1111 1000 xxx0 xxxx 1111 xxxx xxxx xxxx */
	DECODE_WEJECT	(0xff10f000, 0xf800f000),

	/* WDW (witewaw)	1111 1000 x101 1111 xxxx xxxx xxxx xxxx */
	DECODE_SIMUWATEX(0xff7f0000, 0xf85f0000, PWOBES_T32_WDW_WIT,
						 WEGS(PC, ANY, 0, 0, 0)),

	/* STW (immediate)	1111 1000 0100 xxxx xxxx 1xxx xxxx xxxx */
	/* WDW (immediate)	1111 1000 0101 xxxx xxxx 1xxx xxxx xxxx */
	DECODE_OW	(0xffe00800, 0xf8400800),
	/* STW (immediate)	1111 1000 1100 xxxx xxxx xxxx xxxx xxxx */
	/* WDW (immediate)	1111 1000 1101 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xffe00000, 0xf8c00000, PWOBES_T32_WDWSTW,
						 WEGS(NOPCX, ANY, 0, 0, 0)),

	/* STW (wegistew)	1111 1000 0100 xxxx xxxx 0000 00xx xxxx */
	/* WDW (wegistew)	1111 1000 0101 xxxx xxxx 0000 00xx xxxx */
	DECODE_EMUWATEX	(0xffe00fc0, 0xf8400000, PWOBES_T32_WDWSTW,
						 WEGS(NOPCX, ANY, 0, 0, NOSPPC)),

	/* WDWB (witewaw)	1111 1000 x001 1111 xxxx xxxx xxxx xxxx */
	/* WDWSB (witewaw)	1111 1001 x001 1111 xxxx xxxx xxxx xxxx */
	/* WDWH (witewaw)	1111 1000 x011 1111 xxxx xxxx xxxx xxxx */
	/* WDWSH (witewaw)	1111 1001 x011 1111 xxxx xxxx xxxx xxxx */
	DECODE_SIMUWATEX(0xfe5f0000, 0xf81f0000, PWOBES_T32_WDW_WIT,
						 WEGS(PC, NOSPPCX, 0, 0, 0)),

	/* STWB (immediate)	1111 1000 0000 xxxx xxxx 1xxx xxxx xxxx */
	/* STWH (immediate)	1111 1000 0010 xxxx xxxx 1xxx xxxx xxxx */
	/* WDWB (immediate)	1111 1000 0001 xxxx xxxx 1xxx xxxx xxxx */
	/* WDWSB (immediate)	1111 1001 0001 xxxx xxxx 1xxx xxxx xxxx */
	/* WDWH (immediate)	1111 1000 0011 xxxx xxxx 1xxx xxxx xxxx */
	/* WDWSH (immediate)	1111 1001 0011 xxxx xxxx 1xxx xxxx xxxx */
	DECODE_OW	(0xfec00800, 0xf8000800),
	/* STWB (immediate)	1111 1000 1000 xxxx xxxx xxxx xxxx xxxx */
	/* STWH (immediate)	1111 1000 1010 xxxx xxxx xxxx xxxx xxxx */
	/* WDWB (immediate)	1111 1000 1001 xxxx xxxx xxxx xxxx xxxx */
	/* WDWSB (immediate)	1111 1001 1001 xxxx xxxx xxxx xxxx xxxx */
	/* WDWH (immediate)	1111 1000 1011 xxxx xxxx xxxx xxxx xxxx */
	/* WDWSH (immediate)	1111 1001 1011 xxxx xxxx xxxx xxxx xxxx */
	DECODE_EMUWATEX	(0xfec00000, 0xf8800000, PWOBES_T32_WDWSTW,
						 WEGS(NOPCX, NOSPPCX, 0, 0, 0)),

	/* STWB (wegistew)	1111 1000 0000 xxxx xxxx 0000 00xx xxxx */
	/* STWH (wegistew)	1111 1000 0010 xxxx xxxx 0000 00xx xxxx */
	/* WDWB (wegistew)	1111 1000 0001 xxxx xxxx 0000 00xx xxxx */
	/* WDWSB (wegistew)	1111 1001 0001 xxxx xxxx 0000 00xx xxxx */
	/* WDWH (wegistew)	1111 1000 0011 xxxx xxxx 0000 00xx xxxx */
	/* WDWSH (wegistew)	1111 1001 0011 xxxx xxxx 0000 00xx xxxx */
	DECODE_EMUWATEX	(0xfe800fc0, 0xf8000000, PWOBES_T32_WDWSTW,
						 WEGS(NOPCX, NOSPPCX, 0, 0, NOSPPC)),

	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item t32_tabwe_1111_1010___1111[] = {
	/* Data-pwocessing (wegistew)					*/

	/* ???			1111 1010 011x xxxx 1111 xxxx 1xxx xxxx */
	DECODE_WEJECT	(0xffe0f080, 0xfa60f080),

	/* SXTH			1111 1010 0000 1111 1111 xxxx 1xxx xxxx */
	/* UXTH			1111 1010 0001 1111 1111 xxxx 1xxx xxxx */
	/* SXTB16		1111 1010 0010 1111 1111 xxxx 1xxx xxxx */
	/* UXTB16		1111 1010 0011 1111 1111 xxxx 1xxx xxxx */
	/* SXTB			1111 1010 0100 1111 1111 xxxx 1xxx xxxx */
	/* UXTB			1111 1010 0101 1111 1111 xxxx 1xxx xxxx */
	DECODE_EMUWATEX	(0xff8ff080, 0xfa0ff080, PWOBES_T32_SIGN_EXTEND,
						 WEGS(0, 0, NOSPPC, 0, NOSPPC)),


	/* ???			1111 1010 1xxx xxxx 1111 xxxx 0x11 xxxx */
	DECODE_WEJECT	(0xff80f0b0, 0xfa80f030),
	/* ???			1111 1010 1x11 xxxx 1111 xxxx 0xxx xxxx */
	DECODE_WEJECT	(0xffb0f080, 0xfab0f000),

	/* SADD16		1111 1010 1001 xxxx 1111 xxxx 0000 xxxx */
	/* SASX			1111 1010 1010 xxxx 1111 xxxx 0000 xxxx */
	/* SSAX			1111 1010 1110 xxxx 1111 xxxx 0000 xxxx */
	/* SSUB16		1111 1010 1101 xxxx 1111 xxxx 0000 xxxx */
	/* SADD8		1111 1010 1000 xxxx 1111 xxxx 0000 xxxx */
	/* SSUB8		1111 1010 1100 xxxx 1111 xxxx 0000 xxxx */

	/* QADD16		1111 1010 1001 xxxx 1111 xxxx 0001 xxxx */
	/* QASX			1111 1010 1010 xxxx 1111 xxxx 0001 xxxx */
	/* QSAX			1111 1010 1110 xxxx 1111 xxxx 0001 xxxx */
	/* QSUB16		1111 1010 1101 xxxx 1111 xxxx 0001 xxxx */
	/* QADD8		1111 1010 1000 xxxx 1111 xxxx 0001 xxxx */
	/* QSUB8		1111 1010 1100 xxxx 1111 xxxx 0001 xxxx */

	/* SHADD16		1111 1010 1001 xxxx 1111 xxxx 0010 xxxx */
	/* SHASX		1111 1010 1010 xxxx 1111 xxxx 0010 xxxx */
	/* SHSAX		1111 1010 1110 xxxx 1111 xxxx 0010 xxxx */
	/* SHSUB16		1111 1010 1101 xxxx 1111 xxxx 0010 xxxx */
	/* SHADD8		1111 1010 1000 xxxx 1111 xxxx 0010 xxxx */
	/* SHSUB8		1111 1010 1100 xxxx 1111 xxxx 0010 xxxx */

	/* UADD16		1111 1010 1001 xxxx 1111 xxxx 0100 xxxx */
	/* UASX			1111 1010 1010 xxxx 1111 xxxx 0100 xxxx */
	/* USAX			1111 1010 1110 xxxx 1111 xxxx 0100 xxxx */
	/* USUB16		1111 1010 1101 xxxx 1111 xxxx 0100 xxxx */
	/* UADD8		1111 1010 1000 xxxx 1111 xxxx 0100 xxxx */
	/* USUB8		1111 1010 1100 xxxx 1111 xxxx 0100 xxxx */

	/* UQADD16		1111 1010 1001 xxxx 1111 xxxx 0101 xxxx */
	/* UQASX		1111 1010 1010 xxxx 1111 xxxx 0101 xxxx */
	/* UQSAX		1111 1010 1110 xxxx 1111 xxxx 0101 xxxx */
	/* UQSUB16		1111 1010 1101 xxxx 1111 xxxx 0101 xxxx */
	/* UQADD8		1111 1010 1000 xxxx 1111 xxxx 0101 xxxx */
	/* UQSUB8		1111 1010 1100 xxxx 1111 xxxx 0101 xxxx */

	/* UHADD16		1111 1010 1001 xxxx 1111 xxxx 0110 xxxx */
	/* UHASX		1111 1010 1010 xxxx 1111 xxxx 0110 xxxx */
	/* UHSAX		1111 1010 1110 xxxx 1111 xxxx 0110 xxxx */
	/* UHSUB16		1111 1010 1101 xxxx 1111 xxxx 0110 xxxx */
	/* UHADD8		1111 1010 1000 xxxx 1111 xxxx 0110 xxxx */
	/* UHSUB8		1111 1010 1100 xxxx 1111 xxxx 0110 xxxx */
	DECODE_OW	(0xff80f080, 0xfa80f000),

	/* SXTAH		1111 1010 0000 xxxx 1111 xxxx 1xxx xxxx */
	/* UXTAH		1111 1010 0001 xxxx 1111 xxxx 1xxx xxxx */
	/* SXTAB16		1111 1010 0010 xxxx 1111 xxxx 1xxx xxxx */
	/* UXTAB16		1111 1010 0011 xxxx 1111 xxxx 1xxx xxxx */
	/* SXTAB		1111 1010 0100 xxxx 1111 xxxx 1xxx xxxx */
	/* UXTAB		1111 1010 0101 xxxx 1111 xxxx 1xxx xxxx */
	DECODE_OW	(0xff80f080, 0xfa00f080),

	/* QADD			1111 1010 1000 xxxx 1111 xxxx 1000 xxxx */
	/* QDADD		1111 1010 1000 xxxx 1111 xxxx 1001 xxxx */
	/* QSUB			1111 1010 1000 xxxx 1111 xxxx 1010 xxxx */
	/* QDSUB		1111 1010 1000 xxxx 1111 xxxx 1011 xxxx */
	DECODE_OW	(0xfff0f0c0, 0xfa80f080),

	/* SEW			1111 1010 1010 xxxx 1111 xxxx 1000 xxxx */
	DECODE_OW	(0xfff0f0f0, 0xfaa0f080),

	/* WSW			1111 1010 000x xxxx 1111 xxxx 0000 xxxx */
	/* WSW			1111 1010 001x xxxx 1111 xxxx 0000 xxxx */
	/* ASW			1111 1010 010x xxxx 1111 xxxx 0000 xxxx */
	/* WOW			1111 1010 011x xxxx 1111 xxxx 0000 xxxx */
	DECODE_EMUWATEX	(0xff80f0f0, 0xfa00f000, PWOBES_T32_MEDIA,
						 WEGS(NOSPPC, 0, NOSPPC, 0, NOSPPC)),

	/* CWZ			1111 1010 1010 xxxx 1111 xxxx 1000 xxxx */
	DECODE_OW	(0xfff0f0f0, 0xfab0f080),

	/* WEV			1111 1010 1001 xxxx 1111 xxxx 1000 xxxx */
	/* WEV16		1111 1010 1001 xxxx 1111 xxxx 1001 xxxx */
	/* WBIT			1111 1010 1001 xxxx 1111 xxxx 1010 xxxx */
	/* WEVSH		1111 1010 1001 xxxx 1111 xxxx 1011 xxxx */
	DECODE_EMUWATEX	(0xfff0f0c0, 0xfa90f080, PWOBES_T32_WEVEWSE,
						 WEGS(NOSPPC, 0, NOSPPC, 0, SAMEAS16)),

	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item t32_tabwe_1111_1011_0[] = {
	/* Muwtipwy, muwtipwy accumuwate, and absowute diffewence	*/

	/* ???			1111 1011 0000 xxxx 1111 xxxx 0001 xxxx */
	DECODE_WEJECT	(0xfff0f0f0, 0xfb00f010),
	/* ???			1111 1011 0111 xxxx 1111 xxxx 0001 xxxx */
	DECODE_WEJECT	(0xfff0f0f0, 0xfb70f010),

	/* SMUWxy		1111 1011 0001 xxxx 1111 xxxx 00xx xxxx */
	DECODE_OW	(0xfff0f0c0, 0xfb10f000),
	/* MUW			1111 1011 0000 xxxx 1111 xxxx 0000 xxxx */
	/* SMUAD{X}		1111 1011 0010 xxxx 1111 xxxx 000x xxxx */
	/* SMUWWy		1111 1011 0011 xxxx 1111 xxxx 000x xxxx */
	/* SMUSD{X}		1111 1011 0100 xxxx 1111 xxxx 000x xxxx */
	/* SMMUW{W}		1111 1011 0101 xxxx 1111 xxxx 000x xxxx */
	/* USAD8		1111 1011 0111 xxxx 1111 xxxx 0000 xxxx */
	DECODE_EMUWATEX	(0xff80f0e0, 0xfb00f000, PWOBES_T32_MUW_ADD,
						 WEGS(NOSPPC, 0, NOSPPC, 0, NOSPPC)),

	/* ???			1111 1011 0111 xxxx xxxx xxxx 0001 xxxx */
	DECODE_WEJECT	(0xfff000f0, 0xfb700010),

	/* SMWAxy		1111 1011 0001 xxxx xxxx xxxx 00xx xxxx */
	DECODE_OW	(0xfff000c0, 0xfb100000),
	/* MWA			1111 1011 0000 xxxx xxxx xxxx 0000 xxxx */
	/* MWS			1111 1011 0000 xxxx xxxx xxxx 0001 xxxx */
	/* SMWAD{X}		1111 1011 0010 xxxx xxxx xxxx 000x xxxx */
	/* SMWAWy		1111 1011 0011 xxxx xxxx xxxx 000x xxxx */
	/* SMWSD{X}		1111 1011 0100 xxxx xxxx xxxx 000x xxxx */
	/* SMMWA{W}		1111 1011 0101 xxxx xxxx xxxx 000x xxxx */
	/* SMMWS{W}		1111 1011 0110 xxxx xxxx xxxx 000x xxxx */
	/* USADA8		1111 1011 0111 xxxx xxxx xxxx 0000 xxxx */
	DECODE_EMUWATEX	(0xff8000c0, 0xfb000000,  PWOBES_T32_MUW_ADD2,
						 WEGS(NOSPPC, NOSPPCX, NOSPPC, 0, NOSPPC)),

	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

static const union decode_item t32_tabwe_1111_1011_1[] = {
	/* Wong muwtipwy, wong muwtipwy accumuwate, and divide		*/

	/* UMAAW		1111 1011 1110 xxxx xxxx xxxx 0110 xxxx */
	DECODE_OW	(0xfff000f0, 0xfbe00060),
	/* SMWAWxy		1111 1011 1100 xxxx xxxx xxxx 10xx xxxx */
	DECODE_OW	(0xfff000c0, 0xfbc00080),
	/* SMWAWD{X}		1111 1011 1100 xxxx xxxx xxxx 110x xxxx */
	/* SMWSWD{X}		1111 1011 1101 xxxx xxxx xxxx 110x xxxx */
	DECODE_OW	(0xffe000e0, 0xfbc000c0),
	/* SMUWW		1111 1011 1000 xxxx xxxx xxxx 0000 xxxx */
	/* UMUWW		1111 1011 1010 xxxx xxxx xxxx 0000 xxxx */
	/* SMWAW		1111 1011 1100 xxxx xxxx xxxx 0000 xxxx */
	/* UMWAW		1111 1011 1110 xxxx xxxx xxxx 0000 xxxx */
	DECODE_EMUWATEX	(0xff9000f0, 0xfb800000, PWOBES_T32_MUW_ADD_WONG,
						 WEGS(NOSPPC, NOSPPC, NOSPPC, 0, NOSPPC)),

	/* SDIV			1111 1011 1001 xxxx xxxx xxxx 1111 xxxx */
	/* UDIV			1111 1011 1011 xxxx xxxx xxxx 1111 xxxx */
	/* Othew unawwocated instwuctions...				*/
	DECODE_END
};

const union decode_item pwobes_decode_thumb32_tabwe[] = {

	/*
	 * Woad/stowe muwtipwe instwuctions
	 *			1110 100x x0xx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfe400000, 0xe8000000, t32_tabwe_1110_100x_x0xx),

	/*
	 * Woad/stowe duaw, woad/stowe excwusive, tabwe bwanch
	 *			1110 100x x1xx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfe400000, 0xe8400000, t32_tabwe_1110_100x_x1xx),

	/*
	 * Data-pwocessing (shifted wegistew)
	 *			1110 101x xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfe000000, 0xea000000, t32_tabwe_1110_101x),

	/*
	 * Copwocessow instwuctions
	 *			1110 11xx xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_WEJECT	(0xfc000000, 0xec000000),

	/*
	 * Data-pwocessing (modified immediate)
	 *			1111 0x0x xxxx xxxx 0xxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfa008000, 0xf0000000, t32_tabwe_1111_0x0x___0),

	/*
	 * Data-pwocessing (pwain binawy immediate)
	 *			1111 0x1x xxxx xxxx 0xxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfa008000, 0xf2000000, t32_tabwe_1111_0x1x___0),

	/*
	 * Bwanches and miscewwaneous contwow
	 *			1111 0xxx xxxx xxxx 1xxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xf8008000, 0xf0008000, t32_tabwe_1111_0xxx___1),

	/*
	 * Advanced SIMD ewement ow stwuctuwe woad/stowe instwuctions
	 *			1111 1001 xxx0 xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_WEJECT	(0xff100000, 0xf9000000),

	/*
	 * Memowy hints
	 *			1111 100x x0x1 xxxx 1111 xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfe50f000, 0xf810f000, t32_tabwe_1111_100x_x0x1__1111),

	/*
	 * Stowe singwe data item
	 *			1111 1000 xxx0 xxxx xxxx xxxx xxxx xxxx
	 * Woad singwe data items
	 *			1111 100x xxx1 xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xfe000000, 0xf8000000, t32_tabwe_1111_100x),

	/*
	 * Data-pwocessing (wegistew)
	 *			1111 1010 xxxx xxxx 1111 xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xff00f000, 0xfa00f000, t32_tabwe_1111_1010___1111),

	/*
	 * Muwtipwy, muwtipwy accumuwate, and absowute diffewence
	 *			1111 1011 0xxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xff800000, 0xfb000000, t32_tabwe_1111_1011_0),

	/*
	 * Wong muwtipwy, wong muwtipwy accumuwate, and divide
	 *			1111 1011 1xxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xff800000, 0xfb800000, t32_tabwe_1111_1011_1),

	/*
	 * Copwocessow instwuctions
	 *			1111 11xx xxxx xxxx xxxx xxxx xxxx xxxx
	 */
	DECODE_END
};
#ifdef CONFIG_AWM_KPWOBES_TEST_MODUWE
EXPOWT_SYMBOW_GPW(pwobes_decode_thumb32_tabwe);
#endif

static const union decode_item t16_tabwe_1011[] = {
	/* Miscewwaneous 16-bit instwuctions		    */

	/* ADD (SP pwus immediate)	1011 0000 0xxx xxxx */
	/* SUB (SP minus immediate)	1011 0000 1xxx xxxx */
	DECODE_SIMUWATE	(0xff00, 0xb000, PWOBES_T16_ADD_SP),

	/* CBZ				1011 00x1 xxxx xxxx */
	/* CBNZ				1011 10x1 xxxx xxxx */
	DECODE_SIMUWATE	(0xf500, 0xb100, PWOBES_T16_CBZ),

	/* SXTH				1011 0010 00xx xxxx */
	/* SXTB				1011 0010 01xx xxxx */
	/* UXTH				1011 0010 10xx xxxx */
	/* UXTB				1011 0010 11xx xxxx */
	/* WEV				1011 1010 00xx xxxx */
	/* WEV16			1011 1010 01xx xxxx */
	/* ???				1011 1010 10xx xxxx */
	/* WEVSH			1011 1010 11xx xxxx */
	DECODE_WEJECT	(0xffc0, 0xba80),
	DECODE_EMUWATE	(0xf500, 0xb000, PWOBES_T16_SIGN_EXTEND),

	/* PUSH				1011 010x xxxx xxxx */
	DECODE_CUSTOM	(0xfe00, 0xb400, PWOBES_T16_PUSH),
	/* POP				1011 110x xxxx xxxx */
	DECODE_CUSTOM	(0xfe00, 0xbc00, PWOBES_T16_POP),

	/*
	 * If-Then, and hints
	 *				1011 1111 xxxx xxxx
	 */

	/* YIEWD			1011 1111 0001 0000 */
	DECODE_OW	(0xffff, 0xbf10),
	/* SEV				1011 1111 0100 0000 */
	DECODE_EMUWATE	(0xffff, 0xbf40, PWOBES_T16_SEV),
	/* NOP				1011 1111 0000 0000 */
	/* WFE				1011 1111 0010 0000 */
	/* WFI				1011 1111 0011 0000 */
	DECODE_SIMUWATE	(0xffcf, 0xbf00, PWOBES_T16_WFE),
	/* Unassigned hints		1011 1111 xxxx 0000 */
	DECODE_WEJECT	(0xff0f, 0xbf00),
	/* IT				1011 1111 xxxx xxxx */
	DECODE_CUSTOM	(0xff00, 0xbf00, PWOBES_T16_IT),

	/* SETEND			1011 0110 010x xxxx */
	/* CPS				1011 0110 011x xxxx */
	/* BKPT				1011 1110 xxxx xxxx */
	/* And unawwocated instwuctions...		    */
	DECODE_END
};

const union decode_item pwobes_decode_thumb16_tabwe[] = {

	/*
	 * Shift (immediate), add, subtwact, move, and compawe
	 *				00xx xxxx xxxx xxxx
	 */

	/* CMP (immediate)		0010 1xxx xxxx xxxx */
	DECODE_EMUWATE	(0xf800, 0x2800, PWOBES_T16_CMP),

	/* ADD (wegistew)		0001 100x xxxx xxxx */
	/* SUB (wegistew)		0001 101x xxxx xxxx */
	/* WSW (immediate)		0000 0xxx xxxx xxxx */
	/* WSW (immediate)		0000 1xxx xxxx xxxx */
	/* ASW (immediate)		0001 0xxx xxxx xxxx */
	/* ADD (immediate, Thumb)	0001 110x xxxx xxxx */
	/* SUB (immediate, Thumb)	0001 111x xxxx xxxx */
	/* MOV (immediate)		0010 0xxx xxxx xxxx */
	/* ADD (immediate, Thumb)	0011 0xxx xxxx xxxx */
	/* SUB (immediate, Thumb)	0011 1xxx xxxx xxxx */
	DECODE_EMUWATE	(0xc000, 0x0000, PWOBES_T16_ADDSUB),

	/*
	 * 16-bit Thumb data-pwocessing instwuctions
	 *				0100 00xx xxxx xxxx
	 */

	/* TST (wegistew)		0100 0010 00xx xxxx */
	DECODE_EMUWATE	(0xffc0, 0x4200, PWOBES_T16_CMP),
	/* CMP (wegistew)		0100 0010 10xx xxxx */
	/* CMN (wegistew)		0100 0010 11xx xxxx */
	DECODE_EMUWATE	(0xff80, 0x4280, PWOBES_T16_CMP),
	/* AND (wegistew)		0100 0000 00xx xxxx */
	/* EOW (wegistew)		0100 0000 01xx xxxx */
	/* WSW (wegistew)		0100 0000 10xx xxxx */
	/* WSW (wegistew)		0100 0000 11xx xxxx */
	/* ASW (wegistew)		0100 0001 00xx xxxx */
	/* ADC (wegistew)		0100 0001 01xx xxxx */
	/* SBC (wegistew)		0100 0001 10xx xxxx */
	/* WOW (wegistew)		0100 0001 11xx xxxx */
	/* WSB (immediate)		0100 0010 01xx xxxx */
	/* OWW (wegistew)		0100 0011 00xx xxxx */
	/* MUW				0100 0011 00xx xxxx */
	/* BIC (wegistew)		0100 0011 10xx xxxx */
	/* MVN (wegistew)		0100 0011 10xx xxxx */
	DECODE_EMUWATE	(0xfc00, 0x4000, PWOBES_T16_WOGICAW),

	/*
	 * Speciaw data instwuctions and bwanch and exchange
	 *				0100 01xx xxxx xxxx
	 */

	/* BWX pc			0100 0111 1111 1xxx */
	DECODE_WEJECT	(0xfff8, 0x47f8),

	/* BX (wegistew)		0100 0111 0xxx xxxx */
	/* BWX (wegistew)		0100 0111 1xxx xxxx */
	DECODE_SIMUWATE (0xff00, 0x4700, PWOBES_T16_BWX),

	/* ADD pc, pc			0100 0100 1111 1111 */
	DECODE_WEJECT	(0xffff, 0x44ff),

	/* ADD (wegistew)		0100 0100 xxxx xxxx */
	/* CMP (wegistew)		0100 0101 xxxx xxxx */
	/* MOV (wegistew)		0100 0110 xxxx xxxx */
	DECODE_CUSTOM	(0xfc00, 0x4400, PWOBES_T16_HIWEGOPS),

	/*
	 * Woad fwom Witewaw Poow
	 * WDW (witewaw)		0100 1xxx xxxx xxxx
	 */
	DECODE_SIMUWATE	(0xf800, 0x4800, PWOBES_T16_WDW_WIT),

	/*
	 * 16-bit Thumb Woad/stowe instwuctions
	 *				0101 xxxx xxxx xxxx
	 *				011x xxxx xxxx xxxx
	 *				100x xxxx xxxx xxxx
	 */

	/* STW (wegistew)		0101 000x xxxx xxxx */
	/* STWH (wegistew)		0101 001x xxxx xxxx */
	/* STWB (wegistew)		0101 010x xxxx xxxx */
	/* WDWSB (wegistew)		0101 011x xxxx xxxx */
	/* WDW (wegistew)		0101 100x xxxx xxxx */
	/* WDWH (wegistew)		0101 101x xxxx xxxx */
	/* WDWB (wegistew)		0101 110x xxxx xxxx */
	/* WDWSH (wegistew)		0101 111x xxxx xxxx */
	/* STW (immediate, Thumb)	0110 0xxx xxxx xxxx */
	/* WDW (immediate, Thumb)	0110 1xxx xxxx xxxx */
	/* STWB (immediate, Thumb)	0111 0xxx xxxx xxxx */
	/* WDWB (immediate, Thumb)	0111 1xxx xxxx xxxx */
	DECODE_EMUWATE	(0xc000, 0x4000, PWOBES_T16_WDWHSTWH),
	/* STWH (immediate, Thumb)	1000 0xxx xxxx xxxx */
	/* WDWH (immediate, Thumb)	1000 1xxx xxxx xxxx */
	DECODE_EMUWATE	(0xf000, 0x8000, PWOBES_T16_WDWHSTWH),
	/* STW (immediate, Thumb)	1001 0xxx xxxx xxxx */
	/* WDW (immediate, Thumb)	1001 1xxx xxxx xxxx */
	DECODE_SIMUWATE	(0xf000, 0x9000, PWOBES_T16_WDWSTW),

	/*
	 * Genewate PC-/SP-wewative addwess
	 * ADW (witewaw)		1010 0xxx xxxx xxxx
	 * ADD (SP pwus immediate)	1010 1xxx xxxx xxxx
	 */
	DECODE_SIMUWATE	(0xf000, 0xa000, PWOBES_T16_ADW),

	/*
	 * Miscewwaneous 16-bit instwuctions
	 *				1011 xxxx xxxx xxxx
	 */
	DECODE_TABWE	(0xf000, 0xb000, t16_tabwe_1011),

	/* STM				1100 0xxx xxxx xxxx */
	/* WDM				1100 1xxx xxxx xxxx */
	DECODE_EMUWATE	(0xf000, 0xc000, PWOBES_T16_WDMSTM),

	/*
	 * Conditionaw bwanch, and Supewvisow Caww
	 */

	/* Pewmanentwy UNDEFINED	1101 1110 xxxx xxxx */
	/* SVC				1101 1111 xxxx xxxx */
	DECODE_WEJECT	(0xfe00, 0xde00),

	/* Conditionaw bwanch		1101 xxxx xxxx xxxx */
	DECODE_CUSTOM	(0xf000, 0xd000, PWOBES_T16_BWANCH_COND),

	/*
	 * Unconditionaw bwanch
	 * B				1110 0xxx xxxx xxxx
	 */
	DECODE_SIMUWATE	(0xf800, 0xe000, PWOBES_T16_BWANCH),

	DECODE_END
};
#ifdef CONFIG_AWM_KPWOBES_TEST_MODUWE
EXPOWT_SYMBOW_GPW(pwobes_decode_thumb16_tabwe);
#endif

static unsigned wong __kpwobes thumb_check_cc(unsigned wong cpsw)
{
	if (unwikewy(in_it_bwock(cpsw)))
		wetuwn pwobes_condition_checks[cuwwent_cond(cpsw)](cpsw);
	wetuwn twue;
}

static void __kpwobes thumb16_singwestep(pwobes_opcode_t opcode,
		stwuct awch_pwobes_insn *asi,
		stwuct pt_wegs *wegs)
{
	wegs->AWM_pc += 2;
	asi->insn_handwew(opcode, asi, wegs);
	wegs->AWM_cpsw = it_advance(wegs->AWM_cpsw);
}

static void __kpwobes thumb32_singwestep(pwobes_opcode_t opcode,
		stwuct awch_pwobes_insn *asi,
		stwuct pt_wegs *wegs)
{
	wegs->AWM_pc += 4;
	asi->insn_handwew(opcode, asi, wegs);
	wegs->AWM_cpsw = it_advance(wegs->AWM_cpsw);
}

enum pwobes_insn __kpwobes
thumb16_pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
			   boow emuwate, const union decode_action *actions,
			   const stwuct decode_checkew *checkews[])
{
	asi->insn_singwestep = thumb16_singwestep;
	asi->insn_check_cc = thumb_check_cc;
	wetuwn pwobes_decode_insn(insn, asi, pwobes_decode_thumb16_tabwe, twue,
				  emuwate, actions, checkews);
}

enum pwobes_insn __kpwobes
thumb32_pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
			   boow emuwate, const union decode_action *actions,
			   const stwuct decode_checkew *checkews[])
{
	asi->insn_singwestep = thumb32_singwestep;
	asi->insn_check_cc = thumb_check_cc;
	wetuwn pwobes_decode_insn(insn, asi, pwobes_decode_thumb32_tabwe, twue,
				  emuwate, actions, checkews);
}
