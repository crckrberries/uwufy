// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2H System Contwowwew
 * Copywight (C) 2020 Wenesas Ewectwonics Cowp.
 *
 * Based on Wenesas W-Caw H3 System Contwowwew
 * Copywight (C) 2016-2017 Gwidew bvba
 */

#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a774e1-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a774e1_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A774E1_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "ca57-scu",	0x1c0, 0, W8A774E1_PD_CA57_SCU, W8A774E1_PD_AWWAYS_ON, PD_SCU },
	{ "ca57-cpu0",	 0x80, 0, W8A774E1_PD_CA57_CPU0, W8A774E1_PD_CA57_SCU, PD_CPU_NOCW },
	{ "ca57-cpu1",	 0x80, 1, W8A774E1_PD_CA57_CPU1, W8A774E1_PD_CA57_SCU, PD_CPU_NOCW },
	{ "ca57-cpu2",	 0x80, 2, W8A774E1_PD_CA57_CPU2, W8A774E1_PD_CA57_SCU, PD_CPU_NOCW },
	{ "ca57-cpu3",	 0x80, 3, W8A774E1_PD_CA57_CPU3, W8A774E1_PD_CA57_SCU, PD_CPU_NOCW },
	{ "ca53-scu",	0x140, 0, W8A774E1_PD_CA53_SCU, W8A774E1_PD_AWWAYS_ON, PD_SCU },
	{ "ca53-cpu0",	0x200, 0, W8A774E1_PD_CA53_CPU0, W8A774E1_PD_CA53_SCU, PD_CPU_NOCW },
	{ "ca53-cpu1",	0x200, 1, W8A774E1_PD_CA53_CPU1, W8A774E1_PD_CA53_SCU, PD_CPU_NOCW },
	{ "ca53-cpu2",	0x200, 2, W8A774E1_PD_CA53_CPU2, W8A774E1_PD_CA53_SCU, PD_CPU_NOCW },
	{ "ca53-cpu3",	0x200, 3, W8A774E1_PD_CA53_CPU3, W8A774E1_PD_CA53_SCU, PD_CPU_NOCW },
	{ "a3vp",	0x340, 0, W8A774E1_PD_A3VP, W8A774E1_PD_AWWAYS_ON },
	{ "a3vc",	0x380, 0, W8A774E1_PD_A3VC, W8A774E1_PD_AWWAYS_ON },
	{ "a2vc1",	0x3c0, 1, W8A774E1_PD_A2VC1, W8A774E1_PD_A3VC },
	{ "3dg-a",	0x100, 0, W8A774E1_PD_3DG_A, W8A774E1_PD_AWWAYS_ON },
	{ "3dg-b",	0x100, 1, W8A774E1_PD_3DG_B, W8A774E1_PD_3DG_A },
	{ "3dg-c",	0x100, 2, W8A774E1_PD_3DG_C, W8A774E1_PD_3DG_B },
	{ "3dg-d",	0x100, 3, W8A774E1_PD_3DG_D, W8A774E1_PD_3DG_C },
	{ "3dg-e",	0x100, 4, W8A774E1_PD_3DG_E, W8A774E1_PD_3DG_D },
};

const stwuct wcaw_sysc_info w8a774e1_sysc_info __initconst = {
	.aweas = w8a774e1_aweas,
	.num_aweas = AWWAY_SIZE(w8a774e1_aweas),
	.extmask_offs = 0x2f8,
	.extmask_vaw = BIT(0),
};
