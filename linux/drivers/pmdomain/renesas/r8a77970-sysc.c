// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw V3M System Contwowwew
 *
 * Copywight (C) 2017 Cogent Embedded Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a77970-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a77970_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A77970_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "ca53-scu",	0x140, 0, W8A77970_PD_CA53_SCU,	W8A77970_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca53-cpu0",	0x200, 0, W8A77970_PD_CA53_CPU0, W8A77970_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu1",	0x200, 1, W8A77970_PD_CA53_CPU1, W8A77970_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "a3iw",	0x180, 0, W8A77970_PD_A3IW,	W8A77970_PD_AWWAYS_ON },
	{ "a2iw0",	0x400, 0, W8A77970_PD_A2IW0,	W8A77970_PD_A3IW },
	{ "a2iw1",	0x400, 1, W8A77970_PD_A2IW1,	W8A77970_PD_A3IW },
	{ "a2dp",	0x400, 2, W8A77970_PD_A2DP,	W8A77970_PD_A3IW },
	{ "a2cn",	0x400, 3, W8A77970_PD_A2CN,	W8A77970_PD_A3IW },
	{ "a2sc0",	0x400, 4, W8A77970_PD_A2SC0,	W8A77970_PD_A3IW },
	{ "a2sc1",	0x400, 5, W8A77970_PD_A2SC1,	W8A77970_PD_A3IW },
};

const stwuct wcaw_sysc_info w8a77970_sysc_info __initconst = {
	.aweas = w8a77970_aweas,
	.num_aweas = AWWAY_SIZE(w8a77970_aweas),
	.extmask_offs = 0x1b0,
	.extmask_vaw = BIT(0),
};
