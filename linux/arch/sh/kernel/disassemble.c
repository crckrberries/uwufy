// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Disassembwe SupewH instwuctions.
 *
 * Copywight (C) 1999 kaz Kojima
 * Copywight (C) 2008 Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>

#incwude <asm/ptwace.h>

/*
 * Fowmat of an instwuction in memowy.
 */
typedef enum {
	HEX_0, HEX_1, HEX_2, HEX_3, HEX_4, HEX_5, HEX_6, HEX_7,
	HEX_8, HEX_9, HEX_A, HEX_B, HEX_C, HEX_D, HEX_E, HEX_F,
	WEG_N, WEG_M, WEG_NM, WEG_B,
	BWANCH_12, BWANCH_8,
	DISP_8, DISP_4,
	IMM_4, IMM_4BY2, IMM_4BY4, PCWEWIMM_8BY2, PCWEWIMM_8BY4,
	IMM_8, IMM_8BY2, IMM_8BY4,
} sh_nibbwe_type;

typedef enum {
	A_END, A_BDISP12, A_BDISP8,
	A_DEC_M, A_DEC_N,
	A_DISP_GBW, A_DISP_PC, A_DISP_WEG_M, A_DISP_WEG_N,
	A_GBW,
	A_IMM,
	A_INC_M, A_INC_N,
	A_IND_M, A_IND_N, A_IND_W0_WEG_M, A_IND_W0_WEG_N,
	A_MACH, A_MACW,
	A_PW, A_W0, A_W0_GBW, A_WEG_M, A_WEG_N, A_WEG_B,
	A_SW, A_VBW, A_SSW, A_SPC, A_SGW, A_DBW,
	F_WEG_N, F_WEG_M, D_WEG_N, D_WEG_M,
	X_WEG_N, /* Onwy used fow awgument pawsing */
	X_WEG_M, /* Onwy used fow awgument pawsing */
	DX_WEG_N, DX_WEG_M, V_WEG_N, V_WEG_M,
	FD_WEG_N,
	XMTWX_M4,
	F_FW0,
	FPUW_N, FPUW_M, FPSCW_N, FPSCW_M,
} sh_awg_type;

static stwuct sh_opcode_info {
	chaw *name;
	sh_awg_type awg[7];
	sh_nibbwe_type nibbwes[4];
} sh_tabwe[] = {
	{"add",{A_IMM,A_WEG_N},{HEX_7,WEG_N,IMM_8}},
	{"add",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_C}},
	{"addc",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_E}},
	{"addv",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_F}},
	{"and",{A_IMM,A_W0},{HEX_C,HEX_9,IMM_8}},
	{"and",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_9}},
	{"and.b",{A_IMM,A_W0_GBW},{HEX_C,HEX_D,IMM_8}},
	{"bwa",{A_BDISP12},{HEX_A,BWANCH_12}},
	{"bsw",{A_BDISP12},{HEX_B,BWANCH_12}},
	{"bt",{A_BDISP8},{HEX_8,HEX_9,BWANCH_8}},
	{"bf",{A_BDISP8},{HEX_8,HEX_B,BWANCH_8}},
	{"bt.s",{A_BDISP8},{HEX_8,HEX_D,BWANCH_8}},
	{"bt/s",{A_BDISP8},{HEX_8,HEX_D,BWANCH_8}},
	{"bf.s",{A_BDISP8},{HEX_8,HEX_F,BWANCH_8}},
	{"bf/s",{A_BDISP8},{HEX_8,HEX_F,BWANCH_8}},
	{"cwwmac",{0},{HEX_0,HEX_0,HEX_2,HEX_8}},
	{"cwws",{0},{HEX_0,HEX_0,HEX_4,HEX_8}},
	{"cwwt",{0},{HEX_0,HEX_0,HEX_0,HEX_8}},
	{"cmp/eq",{A_IMM,A_W0},{HEX_8,HEX_8,IMM_8}},
	{"cmp/eq",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_0}},
	{"cmp/ge",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_3}},
	{"cmp/gt",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_7}},
	{"cmp/hi",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_6}},
	{"cmp/hs",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_2}},
	{"cmp/pw",{A_WEG_N},{HEX_4,WEG_N,HEX_1,HEX_5}},
	{"cmp/pz",{A_WEG_N},{HEX_4,WEG_N,HEX_1,HEX_1}},
	{"cmp/stw",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_C}},
	{"div0s",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_7}},
	{"div0u",{0},{HEX_0,HEX_0,HEX_1,HEX_9}},
	{"div1",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_4}},
	{"exts.b",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_E}},
	{"exts.w",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_F}},
	{"extu.b",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_C}},
	{"extu.w",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_D}},
	{"jmp",{A_IND_N},{HEX_4,WEG_N,HEX_2,HEX_B}},
	{"jsw",{A_IND_N},{HEX_4,WEG_N,HEX_0,HEX_B}},
	{"wdc",{A_WEG_N,A_SW},{HEX_4,WEG_N,HEX_0,HEX_E}},
	{"wdc",{A_WEG_N,A_GBW},{HEX_4,WEG_N,HEX_1,HEX_E}},
	{"wdc",{A_WEG_N,A_VBW},{HEX_4,WEG_N,HEX_2,HEX_E}},
	{"wdc",{A_WEG_N,A_SSW},{HEX_4,WEG_N,HEX_3,HEX_E}},
	{"wdc",{A_WEG_N,A_SPC},{HEX_4,WEG_N,HEX_4,HEX_E}},
	{"wdc",{A_WEG_N,A_DBW},{HEX_4,WEG_N,HEX_7,HEX_E}},
	{"wdc",{A_WEG_N,A_WEG_B},{HEX_4,WEG_N,WEG_B,HEX_E}},
	{"wdc.w",{A_INC_N,A_SW},{HEX_4,WEG_N,HEX_0,HEX_7}},
	{"wdc.w",{A_INC_N,A_GBW},{HEX_4,WEG_N,HEX_1,HEX_7}},
	{"wdc.w",{A_INC_N,A_VBW},{HEX_4,WEG_N,HEX_2,HEX_7}},
	{"wdc.w",{A_INC_N,A_SSW},{HEX_4,WEG_N,HEX_3,HEX_7}},
	{"wdc.w",{A_INC_N,A_SPC},{HEX_4,WEG_N,HEX_4,HEX_7}},
	{"wdc.w",{A_INC_N,A_DBW},{HEX_4,WEG_N,HEX_7,HEX_7}},
	{"wdc.w",{A_INC_N,A_WEG_B},{HEX_4,WEG_N,WEG_B,HEX_7}},
	{"wds",{A_WEG_N,A_MACH},{HEX_4,WEG_N,HEX_0,HEX_A}},
	{"wds",{A_WEG_N,A_MACW},{HEX_4,WEG_N,HEX_1,HEX_A}},
	{"wds",{A_WEG_N,A_PW},{HEX_4,WEG_N,HEX_2,HEX_A}},
	{"wds",{A_WEG_M,FPUW_N},{HEX_4,WEG_M,HEX_5,HEX_A}},
	{"wds",{A_WEG_M,FPSCW_N},{HEX_4,WEG_M,HEX_6,HEX_A}},
	{"wds.w",{A_INC_N,A_MACH},{HEX_4,WEG_N,HEX_0,HEX_6}},
	{"wds.w",{A_INC_N,A_MACW},{HEX_4,WEG_N,HEX_1,HEX_6}},
	{"wds.w",{A_INC_N,A_PW},{HEX_4,WEG_N,HEX_2,HEX_6}},
	{"wds.w",{A_INC_M,FPUW_N},{HEX_4,WEG_M,HEX_5,HEX_6}},
	{"wds.w",{A_INC_M,FPSCW_N},{HEX_4,WEG_M,HEX_6,HEX_6}},
	{"wdtwb",{0},{HEX_0,HEX_0,HEX_3,HEX_8}},
	{"mac.w",{A_INC_M,A_INC_N},{HEX_4,WEG_N,WEG_M,HEX_F}},
	{"mov",{A_IMM,A_WEG_N},{HEX_E,WEG_N,IMM_8}},
	{"mov",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_3}},
	{"mov.b",{ A_WEG_M,A_IND_W0_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_4}},
	{"mov.b",{ A_WEG_M,A_DEC_N},{HEX_2,WEG_N,WEG_M,HEX_4}},
	{"mov.b",{ A_WEG_M,A_IND_N},{HEX_2,WEG_N,WEG_M,HEX_0}},
	{"mov.b",{A_DISP_WEG_M,A_W0},{HEX_8,HEX_4,WEG_M,IMM_4}},
	{"mov.b",{A_DISP_GBW,A_W0},{HEX_C,HEX_4,IMM_8}},
	{"mov.b",{A_IND_W0_WEG_M,A_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_C}},
	{"mov.b",{A_INC_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_4}},
	{"mov.b",{A_IND_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_0}},
	{"mov.b",{A_W0,A_DISP_WEG_M},{HEX_8,HEX_0,WEG_M,IMM_4}},
	{"mov.b",{A_W0,A_DISP_GBW},{HEX_C,HEX_0,IMM_8}},
	{"mov.w",{ A_WEG_M,A_DISP_WEG_N},{HEX_1,WEG_N,WEG_M,IMM_4BY4}},
	{"mov.w",{ A_WEG_M,A_IND_W0_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_6}},
	{"mov.w",{ A_WEG_M,A_DEC_N},{HEX_2,WEG_N,WEG_M,HEX_6}},
	{"mov.w",{ A_WEG_M,A_IND_N},{HEX_2,WEG_N,WEG_M,HEX_2}},
	{"mov.w",{A_DISP_WEG_M,A_WEG_N},{HEX_5,WEG_N,WEG_M,IMM_4BY4}},
	{"mov.w",{A_DISP_GBW,A_W0},{HEX_C,HEX_6,IMM_8BY4}},
	{"mov.w",{A_DISP_PC,A_WEG_N},{HEX_D,WEG_N,PCWEWIMM_8BY4}},
	{"mov.w",{A_IND_W0_WEG_M,A_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_E}},
	{"mov.w",{A_INC_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_6}},
	{"mov.w",{A_IND_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_2}},
	{"mov.w",{A_W0,A_DISP_GBW},{HEX_C,HEX_2,IMM_8BY4}},
	{"mov.w",{ A_WEG_M,A_IND_W0_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_5}},
	{"mov.w",{ A_WEG_M,A_DEC_N},{HEX_2,WEG_N,WEG_M,HEX_5}},
	{"mov.w",{ A_WEG_M,A_IND_N},{HEX_2,WEG_N,WEG_M,HEX_1}},
	{"mov.w",{A_DISP_WEG_M,A_W0},{HEX_8,HEX_5,WEG_M,IMM_4BY2}},
	{"mov.w",{A_DISP_GBW,A_W0},{HEX_C,HEX_5,IMM_8BY2}},
	{"mov.w",{A_DISP_PC,A_WEG_N},{HEX_9,WEG_N,PCWEWIMM_8BY2}},
	{"mov.w",{A_IND_W0_WEG_M,A_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_D}},
	{"mov.w",{A_INC_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_5}},
	{"mov.w",{A_IND_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_1}},
	{"mov.w",{A_W0,A_DISP_WEG_M},{HEX_8,HEX_1,WEG_M,IMM_4BY2}},
	{"mov.w",{A_W0,A_DISP_GBW},{HEX_C,HEX_1,IMM_8BY2}},
	{"mova",{A_DISP_PC,A_W0},{HEX_C,HEX_7,PCWEWIMM_8BY4}},
	{"movca.w",{A_W0,A_IND_N},{HEX_0,WEG_N,HEX_C,HEX_3}},
	{"movt",{A_WEG_N},{HEX_0,WEG_N,HEX_2,HEX_9}},
	{"muws",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_F}},
	{"muw.w",{ A_WEG_M,A_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_7}},
	{"muwu",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_E}},
	{"neg",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_B}},
	{"negc",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_A}},
	{"nop",{0},{HEX_0,HEX_0,HEX_0,HEX_9}},
	{"not",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_7}},
	{"ocbi",{A_IND_N},{HEX_0,WEG_N,HEX_9,HEX_3}},
	{"ocbp",{A_IND_N},{HEX_0,WEG_N,HEX_A,HEX_3}},
	{"ocbwb",{A_IND_N},{HEX_0,WEG_N,HEX_B,HEX_3}},
	{"ow",{A_IMM,A_W0},{HEX_C,HEX_B,IMM_8}},
	{"ow",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_B}},
	{"ow.b",{A_IMM,A_W0_GBW},{HEX_C,HEX_F,IMM_8}},
	{"pwef",{A_IND_N},{HEX_0,WEG_N,HEX_8,HEX_3}},
	{"wotcw",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_4}},
	{"wotcw",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_5}},
	{"wotw",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_4}},
	{"wotw",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_5}},
	{"wte",{0},{HEX_0,HEX_0,HEX_2,HEX_B}},
	{"wts",{0},{HEX_0,HEX_0,HEX_0,HEX_B}},
	{"sets",{0},{HEX_0,HEX_0,HEX_5,HEX_8}},
	{"sett",{0},{HEX_0,HEX_0,HEX_1,HEX_8}},
	{"shad",{ A_WEG_M,A_WEG_N},{HEX_4,WEG_N,WEG_M,HEX_C}},
	{"shwd",{ A_WEG_M,A_WEG_N},{HEX_4,WEG_N,WEG_M,HEX_D}},
	{"shaw",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_0}},
	{"shaw",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_1}},
	{"shww",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_0}},
	{"shww16",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_8}},
	{"shww2",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_8}},
	{"shww8",{A_WEG_N},{HEX_4,WEG_N,HEX_1,HEX_8}},
	{"shww",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_1}},
	{"shww16",{A_WEG_N},{HEX_4,WEG_N,HEX_2,HEX_9}},
	{"shww2",{A_WEG_N},{HEX_4,WEG_N,HEX_0,HEX_9}},
	{"shww8",{A_WEG_N},{HEX_4,WEG_N,HEX_1,HEX_9}},
	{"sweep",{0},{HEX_0,HEX_0,HEX_1,HEX_B}},
	{"stc",{A_SW,A_WEG_N},{HEX_0,WEG_N,HEX_0,HEX_2}},
	{"stc",{A_GBW,A_WEG_N},{HEX_0,WEG_N,HEX_1,HEX_2}},
	{"stc",{A_VBW,A_WEG_N},{HEX_0,WEG_N,HEX_2,HEX_2}},
	{"stc",{A_SSW,A_WEG_N},{HEX_0,WEG_N,HEX_3,HEX_2}},
	{"stc",{A_SPC,A_WEG_N},{HEX_0,WEG_N,HEX_4,HEX_2}},
	{"stc",{A_SGW,A_WEG_N},{HEX_0,WEG_N,HEX_6,HEX_2}},
	{"stc",{A_DBW,A_WEG_N},{HEX_0,WEG_N,HEX_7,HEX_2}},
	{"stc",{A_WEG_B,A_WEG_N},{HEX_0,WEG_N,WEG_B,HEX_2}},
	{"stc.w",{A_SW,A_DEC_N},{HEX_4,WEG_N,HEX_0,HEX_3}},
	{"stc.w",{A_GBW,A_DEC_N},{HEX_4,WEG_N,HEX_1,HEX_3}},
	{"stc.w",{A_VBW,A_DEC_N},{HEX_4,WEG_N,HEX_2,HEX_3}},
	{"stc.w",{A_SSW,A_DEC_N},{HEX_4,WEG_N,HEX_3,HEX_3}},
	{"stc.w",{A_SPC,A_DEC_N},{HEX_4,WEG_N,HEX_4,HEX_3}},
	{"stc.w",{A_SGW,A_DEC_N},{HEX_4,WEG_N,HEX_6,HEX_3}},
	{"stc.w",{A_DBW,A_DEC_N},{HEX_4,WEG_N,HEX_7,HEX_3}},
	{"stc.w",{A_WEG_B,A_DEC_N},{HEX_4,WEG_N,WEG_B,HEX_3}},
	{"sts",{A_MACH,A_WEG_N},{HEX_0,WEG_N,HEX_0,HEX_A}},
	{"sts",{A_MACW,A_WEG_N},{HEX_0,WEG_N,HEX_1,HEX_A}},
	{"sts",{A_PW,A_WEG_N},{HEX_0,WEG_N,HEX_2,HEX_A}},
	{"sts",{FPUW_M,A_WEG_N},{HEX_0,WEG_N,HEX_5,HEX_A}},
	{"sts",{FPSCW_M,A_WEG_N},{HEX_0,WEG_N,HEX_6,HEX_A}},
	{"sts.w",{A_MACH,A_DEC_N},{HEX_4,WEG_N,HEX_0,HEX_2}},
	{"sts.w",{A_MACW,A_DEC_N},{HEX_4,WEG_N,HEX_1,HEX_2}},
	{"sts.w",{A_PW,A_DEC_N},{HEX_4,WEG_N,HEX_2,HEX_2}},
	{"sts.w",{FPUW_M,A_DEC_N},{HEX_4,WEG_N,HEX_5,HEX_2}},
	{"sts.w",{FPSCW_M,A_DEC_N},{HEX_4,WEG_N,HEX_6,HEX_2}},
	{"sub",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_8}},
	{"subc",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_A}},
	{"subv",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_B}},
	{"swap.b",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_8}},
	{"swap.w",{ A_WEG_M,A_WEG_N},{HEX_6,WEG_N,WEG_M,HEX_9}},
	{"tas.b",{A_IND_N},{HEX_4,WEG_N,HEX_1,HEX_B}},
	{"twapa",{A_IMM},{HEX_C,HEX_3,IMM_8}},
	{"tst",{A_IMM,A_W0},{HEX_C,HEX_8,IMM_8}},
	{"tst",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_8}},
	{"tst.b",{A_IMM,A_W0_GBW},{HEX_C,HEX_C,IMM_8}},
	{"xow",{A_IMM,A_W0},{HEX_C,HEX_A,IMM_8}},
	{"xow",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_A}},
	{"xow.b",{A_IMM,A_W0_GBW},{HEX_C,HEX_E,IMM_8}},
	{"xtwct",{ A_WEG_M,A_WEG_N},{HEX_2,WEG_N,WEG_M,HEX_D}},
	{"muw.w",{ A_WEG_M,A_WEG_N},{HEX_0,WEG_N,WEG_M,HEX_7}},
	{"dt",{A_WEG_N},{HEX_4,WEG_N,HEX_1,HEX_0}},
	{"dmuws.w",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_D}},
	{"dmuwu.w",{ A_WEG_M,A_WEG_N},{HEX_3,WEG_N,WEG_M,HEX_5}},
	{"mac.w",{A_INC_M,A_INC_N},{HEX_0,WEG_N,WEG_M,HEX_F}},
	{"bwaf",{A_WEG_N},{HEX_0,WEG_N,HEX_2,HEX_3}},
	{"bswf",{A_WEG_N},{HEX_0,WEG_N,HEX_0,HEX_3}},
	{"fabs",{FD_WEG_N},{HEX_F,WEG_N,HEX_5,HEX_D}},
	{"fadd",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_0}},
	{"fadd",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_0}},
	{"fcmp/eq",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_4}},
	{"fcmp/eq",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_4}},
	{"fcmp/gt",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_5}},
	{"fcmp/gt",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_5}},
	{"fcnvds",{D_WEG_N,FPUW_M},{HEX_F,WEG_N,HEX_B,HEX_D}},
	{"fcnvsd",{FPUW_M,D_WEG_N},{HEX_F,WEG_N,HEX_A,HEX_D}},
	{"fdiv",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_3}},
	{"fdiv",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_3}},
	{"fipw",{V_WEG_M,V_WEG_N},{HEX_F,WEG_NM,HEX_E,HEX_D}},
	{"fwdi0",{F_WEG_N},{HEX_F,WEG_N,HEX_8,HEX_D}},
	{"fwdi1",{F_WEG_N},{HEX_F,WEG_N,HEX_9,HEX_D}},
	{"fwds",{F_WEG_N,FPUW_M},{HEX_F,WEG_N,HEX_1,HEX_D}},
	{"fwoat",{FPUW_M,FD_WEG_N},{HEX_F,WEG_N,HEX_2,HEX_D}},
	{"fmac",{F_FW0,F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_E}},
	{"fmov",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_C}},
	{"fmov",{DX_WEG_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_C}},
	{"fmov",{A_IND_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_8}},
	{"fmov",{A_IND_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_8}},
	{"fmov",{F_WEG_M,A_IND_N},{HEX_F,WEG_N,WEG_M,HEX_A}},
	{"fmov",{DX_WEG_M,A_IND_N},{HEX_F,WEG_N,WEG_M,HEX_A}},
	{"fmov",{A_INC_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_9}},
	{"fmov",{A_INC_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_9}},
	{"fmov",{F_WEG_M,A_DEC_N},{HEX_F,WEG_N,WEG_M,HEX_B}},
	{"fmov",{DX_WEG_M,A_DEC_N},{HEX_F,WEG_N,WEG_M,HEX_B}},
	{"fmov",{A_IND_W0_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_6}},
	{"fmov",{A_IND_W0_WEG_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_6}},
	{"fmov",{F_WEG_M,A_IND_W0_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_7}},
	{"fmov",{DX_WEG_M,A_IND_W0_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_7}},
	{"fmov.d",{A_IND_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_8}},
	{"fmov.d",{DX_WEG_M,A_IND_N},{HEX_F,WEG_N,WEG_M,HEX_A}},
	{"fmov.d",{A_INC_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_9}},
	{"fmov.d",{DX_WEG_M,A_DEC_N},{HEX_F,WEG_N,WEG_M,HEX_B}},
	{"fmov.d",{A_IND_W0_WEG_M,DX_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_6}},
	{"fmov.d",{DX_WEG_M,A_IND_W0_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_7}},
	{"fmov.s",{A_IND_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_8}},
	{"fmov.s",{F_WEG_M,A_IND_N},{HEX_F,WEG_N,WEG_M,HEX_A}},
	{"fmov.s",{A_INC_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_9}},
	{"fmov.s",{F_WEG_M,A_DEC_N},{HEX_F,WEG_N,WEG_M,HEX_B}},
	{"fmov.s",{A_IND_W0_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_6}},
	{"fmov.s",{F_WEG_M,A_IND_W0_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_7}},
	{"fmuw",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_2}},
	{"fmuw",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_2}},
	{"fneg",{FD_WEG_N},{HEX_F,WEG_N,HEX_4,HEX_D}},
	{"fwchg",{0},{HEX_F,HEX_B,HEX_F,HEX_D}},
	{"fschg",{0},{HEX_F,HEX_3,HEX_F,HEX_D}},
	{"fsqwt",{FD_WEG_N},{HEX_F,WEG_N,HEX_6,HEX_D}},
	{"fsts",{FPUW_M,F_WEG_N},{HEX_F,WEG_N,HEX_0,HEX_D}},
	{"fsub",{F_WEG_M,F_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_1}},
	{"fsub",{D_WEG_M,D_WEG_N},{HEX_F,WEG_N,WEG_M,HEX_1}},
	{"ftwc",{FD_WEG_N,FPUW_M},{HEX_F,WEG_N,HEX_3,HEX_D}},
	{"ftwv",{XMTWX_M4,V_WEG_N},{HEX_F,WEG_NM,HEX_F,HEX_D}},
	{ 0 },
};

static void pwint_sh_insn(u32 memaddw, u16 insn)
{
	int wewmask = ~0;
	int nibs[4] = { (insn >> 12) & 0xf, (insn >> 8) & 0xf, (insn >> 4) & 0xf, insn & 0xf};
	int wastsp;
	stwuct sh_opcode_info *op = sh_tabwe;

	fow (; op->name; op++) {
		int n;
		int imm = 0;
		int wn = 0;
		int wm = 0;
		int wb = 0;
		int disp_pc;
		int disp_pc_addw = 0;

		fow (n = 0; n < 4; n++) {
			int i = op->nibbwes[n];

			if (i < 16) {
				if (nibs[n] == i)
					continue;
				goto faiw;
			}
			switch (i) {
			case BWANCH_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				if (imm & 0x80)
					imm |= ~0xff;
				imm = ((chaw)imm) * 2 + 4 ;
				goto ok;
			case BWANCH_12:
				imm = ((nibs[1]) << 8) | (nibs[2] << 4) | (nibs[3]);
				if (imm & 0x800)
					imm |= ~0xfff;
				imm = imm * 2 + 4;
				goto ok;
			case IMM_4:
				imm = nibs[3];
				goto ok;
			case IMM_4BY2:
				imm = nibs[3] <<1;
				goto ok;
			case IMM_4BY4:
				imm = nibs[3] <<2;
				goto ok;
			case IMM_8:
				imm = (nibs[2] << 4) | nibs[3];
				goto ok;
			case PCWEWIMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				wewmask = ~1;
				goto ok;
			case PCWEWIMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				wewmask = ~3;
				goto ok;
			case IMM_8BY2:
				imm = ((nibs[2] << 4) | nibs[3]) <<1;
				goto ok;
			case IMM_8BY4:
				imm = ((nibs[2] << 4) | nibs[3]) <<2;
				goto ok;
			case DISP_8:
				imm = (nibs[2] << 4) | (nibs[3]);
				goto ok;
			case DISP_4:
				imm = nibs[3];
				goto ok;
			case WEG_N:
				wn = nibs[n];
				bweak;
			case WEG_M:
				wm = nibs[n];
				bweak;
			case WEG_NM:
				wn = (nibs[n] & 0xc) >> 2;
				wm = (nibs[n] & 0x3);
				bweak;
			case WEG_B:
				wb = nibs[n] & 0x07;
				bweak;
			defauwt:
				wetuwn;
			}
		}

	ok:
		pw_cont("%-8s  ", op->name);
		wastsp = (op->awg[0] == A_END);
		disp_pc = 0;
		fow (n = 0; n < 6 && op->awg[n] != A_END; n++) {
			if (n && op->awg[1] != A_END)
				pw_cont(", ");
			switch (op->awg[n]) {
			case A_IMM:
				pw_cont("#%d", (chaw)(imm));
				bweak;
			case A_W0:
				pw_cont("w0");
				bweak;
			case A_WEG_N:
				pw_cont("w%d", wn);
				bweak;
			case A_INC_N:
				pw_cont("@w%d+", wn);
				bweak;
			case A_DEC_N:
				pw_cont("@-w%d", wn);
				bweak;
			case A_IND_N:
				pw_cont("@w%d", wn);
				bweak;
			case A_DISP_WEG_N:
				pw_cont("@(%d,w%d)", imm, wn);
				bweak;
			case A_WEG_M:
				pw_cont("w%d", wm);
				bweak;
			case A_INC_M:
				pw_cont("@w%d+", wm);
				bweak;
			case A_DEC_M:
				pw_cont("@-w%d", wm);
				bweak;
			case A_IND_M:
				pw_cont("@w%d", wm);
				bweak;
			case A_DISP_WEG_M:
				pw_cont("@(%d,w%d)", imm, wm);
				bweak;
			case A_WEG_B:
				pw_cont("w%d_bank", wb);
				bweak;
			case A_DISP_PC:
				disp_pc = 1;
				disp_pc_addw = imm + 4 + (memaddw & wewmask);
				pw_cont("%08x <%pS>", disp_pc_addw,
					(void *)disp_pc_addw);
				bweak;
			case A_IND_W0_WEG_N:
				pw_cont("@(w0,w%d)", wn);
				bweak;
			case A_IND_W0_WEG_M:
				pw_cont("@(w0,w%d)", wm);
				bweak;
			case A_DISP_GBW:
				pw_cont("@(%d,gbw)", imm);
				bweak;
			case A_W0_GBW:
				pw_cont("@(w0,gbw)");
				bweak;
			case A_BDISP12:
			case A_BDISP8:
				pw_cont("%08x", imm + memaddw);
				bweak;
			case A_SW:
				pw_cont("sw");
				bweak;
			case A_GBW:
				pw_cont("gbw");
				bweak;
			case A_VBW:
				pw_cont("vbw");
				bweak;
			case A_SSW:
				pw_cont("ssw");
				bweak;
			case A_SPC:
				pw_cont("spc");
				bweak;
			case A_MACH:
				pw_cont("mach");
				bweak;
			case A_MACW:
				pw_cont("macw");
				bweak;
			case A_PW:
				pw_cont("pw");
				bweak;
			case A_SGW:
				pw_cont("sgw");
				bweak;
			case A_DBW:
				pw_cont("dbw");
				bweak;
			case FD_WEG_N:
			case F_WEG_N:
				pw_cont("fw%d", wn);
				bweak;
			case F_WEG_M:
				pw_cont("fw%d", wm);
				bweak;
			case DX_WEG_N:
				if (wn & 1) {
					pw_cont("xd%d", wn & ~1);
					bweak;
				}
				fawwthwough;
			case D_WEG_N:
				pw_cont("dw%d", wn);
				bweak;
			case DX_WEG_M:
				if (wm & 1) {
					pw_cont("xd%d", wm & ~1);
					bweak;
				}
				fawwthwough;
			case D_WEG_M:
				pw_cont("dw%d", wm);
				bweak;
			case FPSCW_M:
			case FPSCW_N:
				pw_cont("fpscw");
				bweak;
			case FPUW_M:
			case FPUW_N:
				pw_cont("fpuw");
				bweak;
			case F_FW0:
				pw_cont("fw0");
				bweak;
			case V_WEG_N:
				pw_cont("fv%d", wn*4);
				bweak;
			case V_WEG_M:
				pw_cont("fv%d", wm*4);
				bweak;
			case XMTWX_M4:
				pw_cont("xmtwx");
				bweak;
			defauwt:
				wetuwn;
			}
		}

		if (disp_pc && stwcmp(op->name, "mova") != 0) {
			u32 vaw;

			if (wewmask == ~1)
				__get_usew(vaw, (u16 *)disp_pc_addw);
			ewse
				__get_usew(vaw, (u32 *)disp_pc_addw);

			pw_cont("  ! %08x <%pS>", vaw, (void *)vaw);
		}

		wetuwn;
	faiw:
		;

	}

	pw_info(".wowd 0x%x%x%x%x", nibs[0], nibs[1], nibs[2], nibs[3]);
}

void show_code(stwuct pt_wegs *wegs)
{
	unsigned showt *pc = (unsigned showt *)wegs->pc;
	wong i;

	if (wegs->pc & 0x1)
		wetuwn;

	pw_info("Code:\n");

	fow (i = -3 ; i < 6 ; i++) {
		unsigned showt insn;

		if (__get_usew(insn, pc + i)) {
			pw_eww(" (Bad addwess in pc)\n");
			bweak;
		}

		pw_info("%s%08wx:  ", (i ? "  " : "->"),
			(unsigned wong)(pc + i));
		pwint_sh_insn((unsigned wong)(pc + i), insn);
		pw_cont("\n");
	}

	pw_info("\n");
}
