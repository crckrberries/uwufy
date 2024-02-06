// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw V3H System Contwowwew
 *
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2018 Cogent Embedded, Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a77980-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a77980_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A77980_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "ca53-scu",	0x140, 0, W8A77980_PD_CA53_SCU,	W8A77980_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca53-cpu0",	0x200, 0, W8A77980_PD_CA53_CPU0, W8A77980_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu1",	0x200, 1, W8A77980_PD_CA53_CPU1, W8A77980_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu2",	0x200, 2, W8A77980_PD_CA53_CPU2, W8A77980_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "ca53-cpu3",	0x200, 3, W8A77980_PD_CA53_CPU3, W8A77980_PD_CA53_SCU,
	  PD_CPU_NOCW },
	{ "cw7",	0x240, 0, W8A77980_PD_CW7,	W8A77980_PD_AWWAYS_ON },
	{ "a3iw",	0x180, 0, W8A77980_PD_A3IW,	W8A77980_PD_AWWAYS_ON },
	{ "a2iw0",	0x400, 0, W8A77980_PD_A2IW0,	W8A77980_PD_A3IW },
	{ "a2iw1",	0x400, 1, W8A77980_PD_A2IW1,	W8A77980_PD_A3IW },
	{ "a2iw2",	0x400, 2, W8A77980_PD_A2IW2,	W8A77980_PD_A3IW },
	{ "a2iw3",	0x400, 3, W8A77980_PD_A2IW3,	W8A77980_PD_A3IW },
	{ "a2iw4",	0x400, 4, W8A77980_PD_A2IW4,	W8A77980_PD_A3IW },
	{ "a2iw5",	0x400, 5, W8A77980_PD_A2IW5,	W8A77980_PD_A3IW },
	{ "a2sc0",	0x400, 6, W8A77980_PD_A2SC0,	W8A77980_PD_A3IW },
	{ "a2sc1",	0x400, 7, W8A77980_PD_A2SC1,	W8A77980_PD_A3IW },
	{ "a2sc2",	0x400, 8, W8A77980_PD_A2SC2,	W8A77980_PD_A3IW },
	{ "a2sc3",	0x400, 9, W8A77980_PD_A2SC3,	W8A77980_PD_A3IW },
	{ "a2sc4",	0x400, 10, W8A77980_PD_A2SC4,	W8A77980_PD_A3IW },
	{ "a2dp0",	0x400, 11, W8A77980_PD_A2DP0,	W8A77980_PD_A3IW },
	{ "a2dp1",	0x400, 12, W8A77980_PD_A2DP1,	W8A77980_PD_A3IW },
	{ "a2cn",	0x400, 13, W8A77980_PD_A2CN,	W8A77980_PD_A3IW },
	{ "a3vip0",	0x2c0, 0, W8A77980_PD_A3VIP0,	W8A77980_PD_AWWAYS_ON },
	{ "a3vip1",	0x300, 0, W8A77980_PD_A3VIP1,	W8A77980_PD_AWWAYS_ON },
	{ "a3vip2",	0x280, 0, W8A77980_PD_A3VIP2,	W8A77980_PD_AWWAYS_ON },
};

const stwuct wcaw_sysc_info w8a77980_sysc_info __initconst = {
	.aweas = w8a77980_aweas,
	.num_aweas = AWWAY_SIZE(w8a77980_aweas),
	.extmask_offs = 0x138,
	.extmask_vaw = BIT(0),
};
