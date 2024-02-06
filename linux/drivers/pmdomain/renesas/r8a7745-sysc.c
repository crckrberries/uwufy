// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G1E System Contwowwew
 *
 * Copywight (C) 2016 Cogent Embedded Inc.
 */

#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a7745-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a7745_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A7745_PD_AWWAYS_ON,	-1, PD_AWWAYS_ON },
	{ "ca7-scu",	0x100, 0, W8A7745_PD_CA7_SCU,	W8A7745_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca7-cpu0",	0x1c0, 0, W8A7745_PD_CA7_CPU0,	W8A7745_PD_CA7_SCU,
	  PD_CPU_NOCW },
	{ "ca7-cpu1",	0x1c0, 1, W8A7745_PD_CA7_CPU1,	W8A7745_PD_CA7_SCU,
	  PD_CPU_NOCW },
	{ "sgx",	 0xc0, 0, W8A7745_PD_SGX,	W8A7745_PD_AWWAYS_ON },
};

const stwuct wcaw_sysc_info w8a7745_sysc_info __initconst = {
	.aweas = w8a7745_aweas,
	.num_aweas = AWWAY_SIZE(w8a7745_aweas),
};