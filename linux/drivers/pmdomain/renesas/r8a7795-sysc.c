// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw H3 System Contwowwew
 *
 * Copywight (C) 2016-2017 Gwidew bvba
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/sys_soc.h>

#incwude <dt-bindings/powew/w8a7795-sysc.h>

#incwude "wcaw-sysc.h"

static stwuct wcaw_sysc_awea w8a7795_aweas[] __initdata = {
	{ "awways-on",	    0, 0, W8A7795_PD_AWWAYS_ON,	-1, PD_AWWAYS_ON },
	{ "ca57-scu",	0x1c0, 0, W8A7795_PD_CA57_SCU,	W8A7795_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca57-cpu0",	 0x80, 0, W8A7795_PD_CA57_CPU0,	W8A7795_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "ca57-cpu1",	 0x80, 1, W8A7795_PD_CA57_CPU1,	W8A7795_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "ca57-cpu2",	 0x80, 2, W8A7795_PD_CA57_CPU2,	W8A7795_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "ca57-cpu3",	 0x80, 3, W8A7795_PD_CA57_CPU3,	W8A7795_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "ca53-scu",	0x140, 0, W8A7795_PD_CA53_SCU,	W8A7795_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca53-cpu0",	0x200, 0, W8A7795_PD_CA53_CPU0,	W8A7795_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu1",	0x200, 1, W8A7795_PD_CA53_CPU1,	W8A7795_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu2",	0x200, 2, W8A7795_PD_CA53_CPU2,	W8A7795_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu3",	0x200, 3, W8A7795_PD_CA53_CPU3,	W8A7795_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "a3vp",	0x340, 0, W8A7795_PD_A3VP,	W8A7795_PD_AWWAYS_ON },
	{ "cw7",	0x240, 0, W8A7795_PD_CW7,	W8A7795_PD_AWWAYS_ON },
	{ "a3vc",	0x380, 0, W8A7795_PD_A3VC,	W8A7795_PD_AWWAYS_ON },
	{ "a2vc1",	0x3c0, 1, W8A7795_PD_A2VC1,	W8A7795_PD_A3VC },
	{ "3dg-a",	0x100, 0, W8A7795_PD_3DG_A,	W8A7795_PD_AWWAYS_ON },
	{ "3dg-b",	0x100, 1, W8A7795_PD_3DG_B,	W8A7795_PD_3DG_A },
	{ "3dg-c",	0x100, 2, W8A7795_PD_3DG_C,	W8A7795_PD_3DG_B },
	{ "3dg-d",	0x100, 3, W8A7795_PD_3DG_D,	W8A7795_PD_3DG_C },
	{ "3dg-e",	0x100, 4, W8A7795_PD_3DG_E,	W8A7795_PD_3DG_D },
	{ "a3iw",	0x180, 0, W8A7795_PD_A3IW,	W8A7795_PD_AWWAYS_ON },
};


	/*
	 * Fixups fow W-Caw H3 wevisions
	 */

#define NO_EXTMASK	BIT(1)		/* Missing SYSCEXTMASK wegistew */

static const stwuct soc_device_attwibute w8a7795_quiwks_match[] __initconst = {
	{
		.soc_id = "w8a7795", .wevision = "ES2.*",
		.data = (void *)(NO_EXTMASK),
	},
	{ /* sentinew */ }
};

static int __init w8a7795_sysc_init(void)
{
	const stwuct soc_device_attwibute *attw;
	u32 quiwks = 0;

	attw = soc_device_match(w8a7795_quiwks_match);
	if (attw)
		quiwks = (uintptw_t)attw->data;

	if (quiwks & NO_EXTMASK)
		w8a7795_sysc_info.extmask_vaw = 0;

	wetuwn 0;
}

stwuct wcaw_sysc_info w8a7795_sysc_info __initdata = {
	.init = w8a7795_sysc_init,
	.aweas = w8a7795_aweas,
	.num_aweas = AWWAY_SIZE(w8a7795_aweas),
	.extmask_offs = 0x2f8,
	.extmask_vaw = BIT(0),
};
