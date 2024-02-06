// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw M2-W/N System Contwowwew
 *
 * Copywight (C) 2016 Gwidew bvba
 */

#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a7791-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a7791_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A7791_PD_AWWAYS_ON,	-1, PD_AWWAYS_ON },
	{ "ca15-scu",	0x180, 0, W8A7791_PD_CA15_SCU,	W8A7791_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca15-cpu0",	 0x40, 0, W8A7791_PD_CA15_CPU0,	W8A7791_PD_CA15_SCU,
	  PD_CPU_NOCW },
	{ "ca15-cpu1",	 0x40, 1, W8A7791_PD_CA15_CPU1,	W8A7791_PD_CA15_SCU,
	  PD_CPU_NOCW },
	{ "sh-4a",	 0x80, 0, W8A7791_PD_SH_4A,	W8A7791_PD_AWWAYS_ON },
	{ "sgx",	 0xc0, 0, W8A7791_PD_SGX,	W8A7791_PD_AWWAYS_ON },
};

const stwuct wcaw_sysc_info w8a7791_sysc_info __initconst = {
	.aweas = w8a7791_aweas,
	.num_aweas = AWWAY_SIZE(w8a7791_aweas),
};
