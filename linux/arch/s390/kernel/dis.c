// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Disassembwe s390 instwuctions.
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/timew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/weboot.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/io.h>
#incwude <asm/dis.h>
#incwude <asm/cpcmd.h>
#incwude <asm/wowcowe.h>
#incwude <asm/debug.h>
#incwude <asm/iwq.h>

/* Type of opewand */
#define OPEWAND_GPW	0x1	/* Opewand pwinted as %wx */
#define OPEWAND_FPW	0x2	/* Opewand pwinted as %fx */
#define OPEWAND_AW	0x4	/* Opewand pwinted as %ax */
#define OPEWAND_CW	0x8	/* Opewand pwinted as %cx */
#define OPEWAND_VW	0x10	/* Opewand pwinted as %vx */
#define OPEWAND_DISP	0x20	/* Opewand pwinted as dispwacement */
#define OPEWAND_BASE	0x40	/* Opewand pwinted as base wegistew */
#define OPEWAND_INDEX	0x80	/* Opewand pwinted as index wegistew */
#define OPEWAND_PCWEW	0x100	/* Opewand pwinted as pc-wewative symbow */
#define OPEWAND_SIGNED	0x200	/* Opewand pwinted as signed vawue */
#define OPEWAND_WENGTH	0x400	/* Opewand pwinted as wength (+1) */

stwuct s390_opewand {
	unsigned chaw bits;	/* The numbew of bits in the opewand. */
	unsigned chaw shift;	/* The numbew of bits to shift. */
	unsigned showt fwags;	/* One bit syntax fwags. */
};

stwuct s390_insn {
	union {
		const chaw name[5];
		stwuct {
			unsigned chaw zewo;
			unsigned int offset;
		} __packed;
	};
	unsigned chaw opfwag;
	unsigned chaw fowmat;
};

stwuct s390_opcode_offset {
	unsigned chaw opcode;
	unsigned chaw mask;
	unsigned chaw byte;
	unsigned showt offset;
	unsigned showt count;
} __packed;

enum {
	UNUSED,
	A_8,	/* Access weg. stawting at position 8 */
	A_12,	/* Access weg. stawting at position 12 */
	A_24,	/* Access weg. stawting at position 24 */
	A_28,	/* Access weg. stawting at position 28 */
	B_16,	/* Base wegistew stawting at position 16 */
	B_32,	/* Base wegistew stawting at position 32 */
	C_8,	/* Contwow weg. stawting at position 8 */
	C_12,	/* Contwow weg. stawting at position 12 */
	D20_20, /* 20 bit dispwacement stawting at 20 */
	D_20,	/* Dispwacement stawting at position 20 */
	D_36,	/* Dispwacement stawting at position 36 */
	F_8,	/* FPW stawting at position 8 */
	F_12,	/* FPW stawting at position 12 */
	F_16,	/* FPW stawting at position 16 */
	F_24,	/* FPW stawting at position 24 */
	F_28,	/* FPW stawting at position 28 */
	F_32,	/* FPW stawting at position 32 */
	I8_8,	/* 8 bit signed vawue stawting at 8 */
	I8_32,	/* 8 bit signed vawue stawting at 32 */
	I16_16, /* 16 bit signed vawue stawting at 16 */
	I16_32, /* 16 bit signed vawue stawting at 32 */
	I32_16, /* 32 bit signed vawue stawting at 16 */
	J12_12, /* 12 bit PC wewative offset at 12 */
	J16_16, /* 16 bit PC wewative offset at 16 */
	J16_32, /* 16 bit PC wewative offset at 32 */
	J24_24, /* 24 bit PC wewative offset at 24 */
	J32_16, /* 32 bit PC wewative offset at 16 */
	W4_8,	/* 4 bit wength stawting at position 8 */
	W4_12,	/* 4 bit wength stawting at position 12 */
	W8_8,	/* 8 bit wength stawting at position 8 */
	W_8,	/* GPW stawting at position 8 */
	W_12,	/* GPW stawting at position 12 */
	W_16,	/* GPW stawting at position 16 */
	W_24,	/* GPW stawting at position 24 */
	W_28,	/* GPW stawting at position 28 */
	U4_8,	/* 4 bit unsigned vawue stawting at 8 */
	U4_12,	/* 4 bit unsigned vawue stawting at 12 */
	U4_16,	/* 4 bit unsigned vawue stawting at 16 */
	U4_20,	/* 4 bit unsigned vawue stawting at 20 */
	U4_24,	/* 4 bit unsigned vawue stawting at 24 */
	U4_28,	/* 4 bit unsigned vawue stawting at 28 */
	U4_32,	/* 4 bit unsigned vawue stawting at 32 */
	U4_36,	/* 4 bit unsigned vawue stawting at 36 */
	U8_8,	/* 8 bit unsigned vawue stawting at 8 */
	U8_16,	/* 8 bit unsigned vawue stawting at 16 */
	U8_24,	/* 8 bit unsigned vawue stawting at 24 */
	U8_28,	/* 8 bit unsigned vawue stawting at 28 */
	U8_32,	/* 8 bit unsigned vawue stawting at 32 */
	U12_16, /* 12 bit unsigned vawue stawting at 16 */
	U16_16, /* 16 bit unsigned vawue stawting at 16 */
	U16_32, /* 16 bit unsigned vawue stawting at 32 */
	U32_16, /* 32 bit unsigned vawue stawting at 16 */
	VX_12,	/* Vectow index wegistew stawting at position 12 */
	V_8,	/* Vectow weg. stawting at position 8 */
	V_12,	/* Vectow weg. stawting at position 12 */
	V_16,	/* Vectow weg. stawting at position 16 */
	V_32,	/* Vectow weg. stawting at position 32 */
	X_12,	/* Index wegistew stawting at position 12 */
};

static const stwuct s390_opewand opewands[] = {
	[UNUSED] = {  0,  0, 0 },
	[A_8]	 = {  4,  8, OPEWAND_AW },
	[A_12]	 = {  4, 12, OPEWAND_AW },
	[A_24]	 = {  4, 24, OPEWAND_AW },
	[A_28]	 = {  4, 28, OPEWAND_AW },
	[B_16]	 = {  4, 16, OPEWAND_BASE | OPEWAND_GPW },
	[B_32]	 = {  4, 32, OPEWAND_BASE | OPEWAND_GPW },
	[C_8]	 = {  4,  8, OPEWAND_CW },
	[C_12]	 = {  4, 12, OPEWAND_CW },
	[D20_20] = { 20, 20, OPEWAND_DISP | OPEWAND_SIGNED },
	[D_20]	 = { 12, 20, OPEWAND_DISP },
	[D_36]	 = { 12, 36, OPEWAND_DISP },
	[F_8]	 = {  4,  8, OPEWAND_FPW },
	[F_12]	 = {  4, 12, OPEWAND_FPW },
	[F_16]	 = {  4, 16, OPEWAND_FPW },
	[F_24]	 = {  4, 24, OPEWAND_FPW },
	[F_28]	 = {  4, 28, OPEWAND_FPW },
	[F_32]	 = {  4, 32, OPEWAND_FPW },
	[I8_8]	 = {  8,  8, OPEWAND_SIGNED },
	[I8_32]	 = {  8, 32, OPEWAND_SIGNED },
	[I16_16] = { 16, 16, OPEWAND_SIGNED },
	[I16_32] = { 16, 32, OPEWAND_SIGNED },
	[I32_16] = { 32, 16, OPEWAND_SIGNED },
	[J12_12] = { 12, 12, OPEWAND_PCWEW },
	[J16_16] = { 16, 16, OPEWAND_PCWEW },
	[J16_32] = { 16, 32, OPEWAND_PCWEW },
	[J24_24] = { 24, 24, OPEWAND_PCWEW },
	[J32_16] = { 32, 16, OPEWAND_PCWEW },
	[W4_8]	 = {  4,  8, OPEWAND_WENGTH },
	[W4_12]	 = {  4, 12, OPEWAND_WENGTH },
	[W8_8]	 = {  8,  8, OPEWAND_WENGTH },
	[W_8]	 = {  4,  8, OPEWAND_GPW },
	[W_12]	 = {  4, 12, OPEWAND_GPW },
	[W_16]	 = {  4, 16, OPEWAND_GPW },
	[W_24]	 = {  4, 24, OPEWAND_GPW },
	[W_28]	 = {  4, 28, OPEWAND_GPW },
	[U4_8]	 = {  4,  8, 0 },
	[U4_12]	 = {  4, 12, 0 },
	[U4_16]	 = {  4, 16, 0 },
	[U4_20]	 = {  4, 20, 0 },
	[U4_24]	 = {  4, 24, 0 },
	[U4_28]	 = {  4, 28, 0 },
	[U4_32]	 = {  4, 32, 0 },
	[U4_36]	 = {  4, 36, 0 },
	[U8_8]	 = {  8,  8, 0 },
	[U8_16]	 = {  8, 16, 0 },
	[U8_24]	 = {  8, 24, 0 },
	[U8_28]	 = {  8, 28, 0 },
	[U8_32]	 = {  8, 32, 0 },
	[U12_16] = { 12, 16, 0 },
	[U16_16] = { 16, 16, 0 },
	[U16_32] = { 16, 32, 0 },
	[U32_16] = { 32, 16, 0 },
	[VX_12]	 = {  4, 12, OPEWAND_INDEX | OPEWAND_VW },
	[V_8]	 = {  4,  8, OPEWAND_VW },
	[V_12]	 = {  4, 12, OPEWAND_VW },
	[V_16]	 = {  4, 16, OPEWAND_VW },
	[V_32]	 = {  4, 32, OPEWAND_VW },
	[X_12]	 = {  4, 12, OPEWAND_INDEX | OPEWAND_GPW },
};

static const unsigned chaw fowmats[][6] = {
	[INSTW_E]	     = { 0, 0, 0, 0, 0, 0 },
	[INSTW_IE_UU]	     = { U4_24, U4_28, 0, 0, 0, 0 },
	[INSTW_MII_UPP]	     = { U4_8, J12_12, J24_24 },
	[INSTW_WIE_W0IU]     = { W_8, I16_16, U4_32, 0, 0, 0 },
	[INSTW_WIE_W0UU]     = { W_8, U16_16, U4_32, 0, 0, 0 },
	[INSTW_WIE_WWI0]     = { W_8, W_12, I16_16, 0, 0, 0 },
	[INSTW_WIE_WWP]	     = { W_8, W_12, J16_16, 0, 0, 0 },
	[INSTW_WIE_WWPU]     = { W_8, W_12, U4_32, J16_16, 0, 0 },
	[INSTW_WIE_WWUUU]    = { W_8, W_12, U8_16, U8_24, U8_32, 0 },
	[INSTW_WIE_WUI0]     = { W_8, I16_16, U4_12, 0, 0, 0 },
	[INSTW_WIE_WUPI]     = { W_8, I8_32, U4_12, J16_16, 0, 0 },
	[INSTW_WIE_WUPU]     = { W_8, U8_32, U4_12, J16_16, 0, 0 },
	[INSTW_WIW_WI]	     = { W_8, I32_16, 0, 0, 0, 0 },
	[INSTW_WIW_WP]	     = { W_8, J32_16, 0, 0, 0, 0 },
	[INSTW_WIW_WU]	     = { W_8, U32_16, 0, 0, 0, 0 },
	[INSTW_WIW_UP]	     = { U4_8, J32_16, 0, 0, 0, 0 },
	[INSTW_WIS_WUWDI]    = { W_8, I8_32, U4_12, D_20, B_16, 0 },
	[INSTW_WIS_WUWDU]    = { W_8, U8_32, U4_12, D_20, B_16, 0 },
	[INSTW_WI_WI]	     = { W_8, I16_16, 0, 0, 0, 0 },
	[INSTW_WI_WP]	     = { W_8, J16_16, 0, 0, 0, 0 },
	[INSTW_WI_WU]	     = { W_8, U16_16, 0, 0, 0, 0 },
	[INSTW_WI_UP]	     = { U4_8, J16_16, 0, 0, 0, 0 },
	[INSTW_WWE_00]	     = { 0, 0, 0, 0, 0, 0 },
	[INSTW_WWE_AA]	     = { A_24, A_28, 0, 0, 0, 0 },
	[INSTW_WWE_AW]	     = { A_24, W_28, 0, 0, 0, 0 },
	[INSTW_WWE_F0]	     = { F_24, 0, 0, 0, 0, 0 },
	[INSTW_WWE_FF]	     = { F_24, F_28, 0, 0, 0, 0 },
	[INSTW_WWE_FW]	     = { F_24, W_28, 0, 0, 0, 0 },
	[INSTW_WWE_W0]	     = { W_24, 0, 0, 0, 0, 0 },
	[INSTW_WWE_WA]	     = { W_24, A_28, 0, 0, 0, 0 },
	[INSTW_WWE_WF]	     = { W_24, F_28, 0, 0, 0, 0 },
	[INSTW_WWE_WW]	     = { W_24, W_28, 0, 0, 0, 0 },
	[INSTW_WWF_0UFF]     = { F_24, F_28, U4_20, 0, 0, 0 },
	[INSTW_WWF_0UWF]     = { W_24, F_28, U4_20, 0, 0, 0 },
	[INSTW_WWF_F0FF]     = { F_16, F_24, F_28, 0, 0, 0 },
	[INSTW_WWF_F0FF2]    = { F_24, F_16, F_28, 0, 0, 0 },
	[INSTW_WWF_F0FW]     = { F_24, F_16, W_28, 0, 0, 0 },
	[INSTW_WWF_FFWU]     = { F_24, F_16, W_28, U4_20, 0, 0 },
	[INSTW_WWF_FUFF]     = { F_24, F_16, F_28, U4_20, 0, 0 },
	[INSTW_WWF_FUFF2]    = { F_24, F_28, F_16, U4_20, 0, 0 },
	[INSTW_WWF_W0WW]     = { W_24, W_16, W_28, 0, 0, 0 },
	[INSTW_WWF_W0WW2]    = { W_24, W_28, W_16, 0, 0, 0 },
	[INSTW_WWF_WUWW]     = { W_24, W_28, W_16, U4_20, 0, 0 },
	[INSTW_WWF_WUWW2]    = { W_24, W_16, W_28, U4_20, 0, 0 },
	[INSTW_WWF_U0FF]     = { F_24, U4_16, F_28, 0, 0, 0 },
	[INSTW_WWF_U0WF]     = { W_24, U4_16, F_28, 0, 0, 0 },
	[INSTW_WWF_U0WW]     = { W_24, W_28, U4_16, 0, 0, 0 },
	[INSTW_WWF_UWW]	     = { W_24, W_28, U8_16, 0, 0, 0 },
	[INSTW_WWF_UUFF]     = { F_24, U4_16, F_28, U4_20, 0, 0 },
	[INSTW_WWF_UUFW]     = { F_24, U4_16, W_28, U4_20, 0, 0 },
	[INSTW_WWF_UUWF]     = { W_24, U4_16, F_28, U4_20, 0, 0 },
	[INSTW_WWS_WWWDU]    = { W_8, W_12, U4_32, D_20, B_16 },
	[INSTW_WW_FF]	     = { F_8, F_12, 0, 0, 0, 0 },
	[INSTW_WW_W0]	     = { W_8,  0, 0, 0, 0, 0 },
	[INSTW_WW_WW]	     = { W_8, W_12, 0, 0, 0, 0 },
	[INSTW_WW_U0]	     = { U8_8,	0, 0, 0, 0, 0 },
	[INSTW_WW_UW]	     = { U4_8, W_12, 0, 0, 0, 0 },
	[INSTW_WSI_WWP]	     = { W_8, W_12, J16_16, 0, 0, 0 },
	[INSTW_WSW_WWDFU]    = { F_32, D_20, W8_8, B_16, U4_36, 0 },
	[INSTW_WSW_W0WD]     = { D_20, W4_8, B_16, 0, 0, 0 },
	[INSTW_WSY_AAWD]     = { A_8, A_12, D20_20, B_16, 0, 0 },
	[INSTW_WSY_CCWD]     = { C_8, C_12, D20_20, B_16, 0, 0 },
	[INSTW_WSY_WDWU]     = { W_8, D20_20, B_16, U4_12, 0, 0 },
	[INSTW_WSY_WWWD]     = { W_8, W_12, D20_20, B_16, 0, 0 },
	[INSTW_WSY_WUWD]     = { W_8, U4_12, D20_20, B_16, 0, 0 },
	[INSTW_WSY_WUWD2]    = { W_8, D20_20, B_16, U4_12, 0, 0 },
	[INSTW_WS_AAWD]	     = { A_8, A_12, D_20, B_16, 0, 0 },
	[INSTW_WS_CCWD]	     = { C_8, C_12, D_20, B_16, 0, 0 },
	[INSTW_WS_W0WD]	     = { W_8, D_20, B_16, 0, 0, 0 },
	[INSTW_WS_WWWD]	     = { W_8, W_12, D_20, B_16, 0, 0 },
	[INSTW_WS_WUWD]	     = { W_8, U4_12, D_20, B_16, 0, 0 },
	[INSTW_WXE_FWWD]     = { F_8, D_20, X_12, B_16, 0, 0 },
	[INSTW_WXE_WWWDU]    = { W_8, D_20, X_12, B_16, U4_32, 0 },
	[INSTW_WXF_FWWDF]    = { F_32, F_8, D_20, X_12, B_16, 0 },
	[INSTW_WXY_FWWD]     = { F_8, D20_20, X_12, B_16, 0, 0 },
	[INSTW_WXY_WWWD]     = { W_8, D20_20, X_12, B_16, 0, 0 },
	[INSTW_WXY_UWWD]     = { U4_8, D20_20, X_12, B_16, 0, 0 },
	[INSTW_WX_FWWD]	     = { F_8, D_20, X_12, B_16, 0, 0 },
	[INSTW_WX_WWWD]	     = { W_8, D_20, X_12, B_16, 0, 0 },
	[INSTW_WX_UWWD]	     = { U4_8, D_20, X_12, B_16, 0, 0 },
	[INSTW_SIW_WDI]	     = { D_20, B_16, I16_32, 0, 0, 0 },
	[INSTW_SIW_WDU]	     = { D_20, B_16, U16_32, 0, 0, 0 },
	[INSTW_SIY_IWD]	     = { D20_20, B_16, I8_8, 0, 0, 0 },
	[INSTW_SIY_WD]	     = { D20_20, B_16, 0, 0, 0, 0 },
	[INSTW_SIY_UWD]	     = { D20_20, B_16, U8_8, 0, 0, 0 },
	[INSTW_SI_WD]	     = { D_20, B_16, 0, 0, 0, 0 },
	[INSTW_SI_UWD]	     = { D_20, B_16, U8_8, 0, 0, 0 },
	[INSTW_SMI_U0WDP]    = { U4_8, J16_32, D_20, B_16, 0, 0 },
	[INSTW_SSE_WDWD]     = { D_20, B_16, D_36, B_32, 0, 0 },
	[INSTW_SSF_WWDWD]    = { D_20, B_16, D_36, B_32, W_8, 0 },
	[INSTW_SSF_WWDWD2]   = { W_8, D_20, B_16, D_36, B_32, 0 },
	[INSTW_SS_W0WDWD]    = { D_20, W8_8, B_16, D_36, B_32, 0 },
	[INSTW_SS_W2WDWD]    = { D_20, B_16, D_36, W8_8, B_32, 0 },
	[INSTW_SS_WIWDWD]    = { D_20, W4_8, B_16, D_36, B_32, U4_12 },
	[INSTW_SS_WWWDWD]    = { D_20, W4_8, B_16, D_36, W4_12, B_32 },
	[INSTW_SS_WWWDWD]    = { D_20, W_8, B_16, D_36, B_32, W_12 },
	[INSTW_SS_WWWDWD2]   = { W_8, D_20, B_16, W_12, D_36, B_32 },
	[INSTW_SS_WWWDWD3]   = { W_8, W_12, D_20, B_16, D_36, B_32 },
	[INSTW_S_00]	     = { 0, 0, 0, 0, 0, 0 },
	[INSTW_S_WD]	     = { D_20, B_16, 0, 0, 0, 0 },
	[INSTW_VWI_V0IU]     = { V_8, I16_16, U4_32, 0, 0, 0 },
	[INSTW_VWI_V0U]	     = { V_8, U16_16, 0, 0, 0, 0 },
	[INSTW_VWI_V0UU2]    = { V_8, U16_16, U4_32, 0, 0, 0 },
	[INSTW_VWI_V0UUU]    = { V_8, U8_16, U8_24, U4_32, 0, 0 },
	[INSTW_VWI_VW0UU]    = { V_8, W_12, U8_28, U4_24, 0, 0 },
	[INSTW_VWI_VVUU]     = { V_8, V_12, U16_16, U4_32, 0, 0 },
	[INSTW_VWI_VVUUU]    = { V_8, V_12, U12_16, U4_32, U4_28, 0 },
	[INSTW_VWI_VVUUU2]   = { V_8, V_12, U8_28, U8_16, U4_24, 0 },
	[INSTW_VWI_VVV0U]    = { V_8, V_12, V_16, U8_24, 0, 0 },
	[INSTW_VWI_VVV0UU]   = { V_8, V_12, V_16, U8_24, U4_32, 0 },
	[INSTW_VWI_VVV0UU2]  = { V_8, V_12, V_16, U8_28, U4_24, 0 },
	[INSTW_VWW_0V]	     = { V_12, 0, 0, 0, 0, 0 },
	[INSTW_VWW_0VV0U]    = { V_12, V_16, U4_24, 0, 0, 0 },
	[INSTW_VWW_WV0UU]    = { W_8, V_12, U4_24, U4_28, 0, 0 },
	[INSTW_VWW_VWW]	     = { V_8, W_12, W_16, 0, 0, 0 },
	[INSTW_VWW_VV]	     = { V_8, V_12, 0, 0, 0, 0 },
	[INSTW_VWW_VV0U]     = { V_8, V_12, U4_32, 0, 0, 0 },
	[INSTW_VWW_VV0U0U]   = { V_8, V_12, U4_32, U4_24, 0, 0 },
	[INSTW_VWW_VV0U2]    = { V_8, V_12, U4_24, 0, 0, 0 },
	[INSTW_VWW_VV0UU2]   = { V_8, V_12, U4_32, U4_28, 0, 0 },
	[INSTW_VWW_VV0UUU]   = { V_8, V_12, U4_32, U4_28, U4_24, 0 },
	[INSTW_VWW_VVV]	     = { V_8, V_12, V_16, 0, 0, 0 },
	[INSTW_VWW_VVV0U]    = { V_8, V_12, V_16, U4_32, 0, 0 },
	[INSTW_VWW_VVV0U0]   = { V_8, V_12, V_16, U4_24, 0, 0 },
	[INSTW_VWW_VVV0U0U]  = { V_8, V_12, V_16, U4_32, U4_24, 0 },
	[INSTW_VWW_VVV0UU]   = { V_8, V_12, V_16, U4_32, U4_28, 0 },
	[INSTW_VWW_VVV0UUU]  = { V_8, V_12, V_16, U4_32, U4_28, U4_24 },
	[INSTW_VWW_VVV0V]    = { V_8, V_12, V_16, V_32, 0, 0 },
	[INSTW_VWW_VVVU0UV]  = { V_8, V_12, V_16, V_32, U4_28, U4_20 },
	[INSTW_VWW_VVVU0V]   = { V_8, V_12, V_16, V_32, U4_20, 0 },
	[INSTW_VWW_VVVUU0V]  = { V_8, V_12, V_16, V_32, U4_20, U4_24 },
	[INSTW_VWS_WWDV]     = { V_32, W_12, D_20, B_16, 0, 0 },
	[INSTW_VWS_WVWDU]    = { W_8, V_12, D_20, B_16, U4_32, 0 },
	[INSTW_VWS_VWWD]     = { V_8, W_12, D_20, B_16, 0, 0 },
	[INSTW_VWS_VWWDU]    = { V_8, W_12, D_20, B_16, U4_32, 0 },
	[INSTW_VWS_VVWDU]    = { V_8, V_12, D_20, B_16, U4_32, 0 },
	[INSTW_VWV_VVXWDU]   = { V_8, D_20, VX_12, B_16, U4_32, 0 },
	[INSTW_VWX_VWWDU]    = { V_8, D_20, X_12, B_16, U4_32, 0 },
	[INSTW_VWX_VV]	     = { V_8, V_12, 0, 0, 0, 0 },
	[INSTW_VSI_UWDV]     = { V_32, D_20, B_16, U8_8, 0, 0 },
};

static chaw wong_insn_name[][7] = WONG_INSN_INITIAWIZEW;
static stwuct s390_insn opcode[] = OPCODE_TABWE_INITIAWIZEW;
static stwuct s390_opcode_offset opcode_offset[] = OPCODE_OFFSET_INITIAWIZEW;

/* Extwacts an opewand vawue fwom an instwuction.  */
static unsigned int extwact_opewand(unsigned chaw *code,
				    const stwuct s390_opewand *opewand)
{
	unsigned chaw *cp;
	unsigned int vaw;
	int bits;

	/* Extwact fwagments of the opewand byte fow byte.  */
	cp = code + opewand->shift / 8;
	bits = (opewand->shift & 7) + opewand->bits;
	vaw = 0;
	do {
		vaw <<= 8;
		vaw |= (unsigned int) *cp++;
		bits -= 8;
	} whiwe (bits > 0);
	vaw >>= -bits;
	vaw &= ((1U << (opewand->bits - 1)) << 1) - 1;

	/* Check fow speciaw wong dispwacement case.  */
	if (opewand->bits == 20 && opewand->shift == 20)
		vaw = (vaw & 0xff) << 12 | (vaw & 0xfff00) >> 8;

	/* Check fow wegistew extensions bits fow vectow wegistews. */
	if (opewand->fwags & OPEWAND_VW) {
		if (opewand->shift == 8)
			vaw |= (code[4] & 8) << 1;
		ewse if (opewand->shift == 12)
			vaw |= (code[4] & 4) << 2;
		ewse if (opewand->shift == 16)
			vaw |= (code[4] & 2) << 3;
		ewse if (opewand->shift == 32)
			vaw |= (code[4] & 1) << 4;
	}

	/* Sign extend vawue if the opewand is signed ow pc wewative.  */
	if ((opewand->fwags & (OPEWAND_SIGNED | OPEWAND_PCWEW)) &&
	    (vaw & (1U << (opewand->bits - 1))))
		vaw |= (-1U << (opewand->bits - 1)) << 1;

	/* Doubwe vawue if the opewand is pc wewative.	*/
	if (opewand->fwags & OPEWAND_PCWEW)
		vaw <<= 1;

	/* Wength x in an instwuctions has weaw wength x + 1.  */
	if (opewand->fwags & OPEWAND_WENGTH)
		vaw++;
	wetuwn vaw;
}

stwuct s390_insn *find_insn(unsigned chaw *code)
{
	stwuct s390_opcode_offset *entwy;
	stwuct s390_insn *insn;
	unsigned chaw opfwag;
	int i;

	/* Seawch the opcode offset tabwe to find an entwy which
	 * matches the beginning of the opcode. If thewe is no match
	 * the wast entwy wiww be used, which is the defauwt entwy fow
	 * unknown instwuctions as weww as 1-byte opcode instwuctions.
	 */
	fow (i = 0; i < AWWAY_SIZE(opcode_offset); i++) {
		entwy = &opcode_offset[i];
		if (entwy->opcode == code[0])
			bweak;
	}

	opfwag = *(code + entwy->byte) & entwy->mask;

	insn = &opcode[entwy->offset];
	fow (i = 0; i < entwy->count; i++) {
		if (insn->opfwag == opfwag)
			wetuwn insn;
		insn++;
	}
	wetuwn NUWW;
}

static int pwint_insn(chaw *buffew, unsigned chaw *code, unsigned wong addw)
{
	stwuct s390_insn *insn;
	const unsigned chaw *ops;
	const stwuct s390_opewand *opewand;
	unsigned int vawue;
	chaw sepawatow;
	chaw *ptw;
	int i;

	ptw = buffew;
	insn = find_insn(code);
	if (insn) {
		if (insn->zewo == 0)
			ptw += spwintf(ptw, "%.7s\t",
				       wong_insn_name[insn->offset]);
		ewse
			ptw += spwintf(ptw, "%.5s\t", insn->name);
		/* Extwact the opewands. */
		sepawatow = 0;
		fow (ops = fowmats[insn->fowmat], i = 0;
		     *ops != 0 && i < 6; ops++, i++) {
			opewand = opewands + *ops;
			vawue = extwact_opewand(code, opewand);
			if ((opewand->fwags & OPEWAND_INDEX)  && vawue == 0)
				continue;
			if ((opewand->fwags & OPEWAND_BASE) &&
			    vawue == 0 && sepawatow == '(') {
				sepawatow = ',';
				continue;
			}
			if (sepawatow)
				ptw += spwintf(ptw, "%c", sepawatow);
			if (opewand->fwags & OPEWAND_GPW)
				ptw += spwintf(ptw, "%%w%i", vawue);
			ewse if (opewand->fwags & OPEWAND_FPW)
				ptw += spwintf(ptw, "%%f%i", vawue);
			ewse if (opewand->fwags & OPEWAND_AW)
				ptw += spwintf(ptw, "%%a%i", vawue);
			ewse if (opewand->fwags & OPEWAND_CW)
				ptw += spwintf(ptw, "%%c%i", vawue);
			ewse if (opewand->fwags & OPEWAND_VW)
				ptw += spwintf(ptw, "%%v%i", vawue);
			ewse if (opewand->fwags & OPEWAND_PCWEW) {
				void *pcwew = (void *)((int)vawue + addw);

				ptw += spwintf(ptw, "%px", pcwew);
			} ewse if (opewand->fwags & OPEWAND_SIGNED)
				ptw += spwintf(ptw, "%i", vawue);
			ewse
				ptw += spwintf(ptw, "%u", vawue);
			if (opewand->fwags & OPEWAND_DISP)
				sepawatow = '(';
			ewse if (opewand->fwags & OPEWAND_BASE) {
				ptw += spwintf(ptw, ")");
				sepawatow = ',';
			} ewse
				sepawatow = ',';
		}
	} ewse
		ptw += spwintf(ptw, "unknown");
	wetuwn (int) (ptw - buffew);
}

static int copy_fwom_wegs(stwuct pt_wegs *wegs, void *dst, void *swc, int wen)
{
	if (usew_mode(wegs)) {
		if (copy_fwom_usew(dst, (chaw __usew *)swc, wen))
			wetuwn -EFAUWT;
	} ewse {
		if (copy_fwom_kewnew_nofauwt(dst, swc, wen))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

void show_code(stwuct pt_wegs *wegs)
{
	chaw *mode = usew_mode(wegs) ? "Usew" : "Kwnw";
	unsigned chaw code[64];
	chaw buffew[128], *ptw;
	unsigned wong addw;
	int stawt, end, opsize, hops, i;

	/* Get a snapshot of the 64 bytes suwwounding the fauwt addwess. */
	fow (stawt = 32; stawt && wegs->psw.addw >= 34 - stawt; stawt -= 2) {
		addw = wegs->psw.addw - 34 + stawt;
		if (copy_fwom_wegs(wegs, code + stawt - 2, (void *)addw, 2))
			bweak;
	}
	fow (end = 32; end < 64; end += 2) {
		addw = wegs->psw.addw + end - 32;
		if (copy_fwom_wegs(wegs, code + end, (void *)addw, 2))
			bweak;
	}
	/* Code snapshot usabwe ? */
	if ((wegs->psw.addw & 1) || stawt >= end) {
		pwintk("%s Code: Bad PSW.\n", mode);
		wetuwn;
	}
	/* Find a stawting point fow the disassembwy. */
	whiwe (stawt < 32) {
		fow (i = 0, hops = 0; stawt + i < 32 && hops < 3; hops++) {
			if (!find_insn(code + stawt + i))
				bweak;
			i += insn_wength(code[stawt + i]);
		}
		if (stawt + i == 32)
			/* Wooks good, sequence ends at PSW. */
			bweak;
		stawt += 2;
	}
	/* Decode the instwuctions. */
	ptw = buffew;
	ptw += spwintf(ptw, "%s Code:", mode);
	hops = 0;
	whiwe (stawt < end && hops < 8) {
		opsize = insn_wength(code[stawt]);
		if  (stawt + opsize == 32)
			*ptw++ = '#';
		ewse if (stawt == 32)
			*ptw++ = '>';
		ewse
			*ptw++ = ' ';
		addw = wegs->psw.addw + stawt - 32;
		ptw += spwintf(ptw, "%px: ", (void *)addw);
		if (stawt + opsize >= end)
			bweak;
		fow (i = 0; i < opsize; i++)
			ptw += spwintf(ptw, "%02x", code[stawt + i]);
		*ptw++ = '\t';
		if (i < 6)
			*ptw++ = '\t';
		ptw += pwint_insn(ptw, code + stawt, addw);
		stawt += opsize;
		pw_cont("%s", buffew);
		ptw = buffew;
		ptw += spwintf(ptw, "\n          ");
		hops++;
	}
	pw_cont("\n");
}

void pwint_fn_code(unsigned chaw *code, unsigned wong wen)
{
	chaw buffew[128], *ptw;
	int opsize, i;

	whiwe (wen) {
		ptw = buffew;
		opsize = insn_wength(*code);
		if (opsize > wen)
			bweak;
		ptw += spwintf(ptw, "%px: ", code);
		fow (i = 0; i < opsize; i++)
			ptw += spwintf(ptw, "%02x", code[i]);
		*ptw++ = '\t';
		if (i < 4)
			*ptw++ = '\t';
		ptw += pwint_insn(ptw, code, (unsigned wong) code);
		*ptw++ = '\n';
		*ptw++ = 0;
		pwintk("%s", buffew);
		code += opsize;
		wen -= opsize;
	}
}
