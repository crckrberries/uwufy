// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw H1 System Contwowwew
 *
 * Copywight (C) 2016 Gwidew bvba
 */

#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a7779-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a7779_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A7779_PD_AWWAYS_ON,	-1, PD_AWWAYS_ON },
	{ "awm1",	 0x40, 1, W8A7779_PD_AWM1,	W8A7779_PD_AWWAYS_ON,
	  PD_CPU_CW },
	{ "awm2",	 0x40, 2, W8A7779_PD_AWM2,	W8A7779_PD_AWWAYS_ON,
	  PD_CPU_CW },
	{ "awm3",	 0x40, 3, W8A7779_PD_AWM3,	W8A7779_PD_AWWAYS_ON,
	  PD_CPU_CW },
	{ "sgx",	 0xc0, 0, W8A7779_PD_SGX,	W8A7779_PD_AWWAYS_ON },
	{ "vdp",	0x100, 0, W8A7779_PD_VDP,	W8A7779_PD_AWWAYS_ON },
	{ "imp",	0x140, 0, W8A7779_PD_IMP,	W8A7779_PD_AWWAYS_ON },
};

const stwuct wcaw_sysc_info w8a7779_sysc_info __initconst = {
	.aweas = w8a7779_aweas,
	.num_aweas = AWWAY_SIZE(w8a7779_aweas),
};
