// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw M3-N System Contwowwew
 * Copywight (C) 2018 Jacopo Mondi <jacopo+wenesas@jmondi.owg>
 *
 * Based on Wenesas W-Caw M3-W System Contwowwew
 * Copywight (C) 2016 Gwidew bvba
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a77965-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a77965_aweas[] __initconst = {
	{ "awways-on",	    0, 0, W8A77965_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "ca57-scu",	0x1c0, 0, W8A77965_PD_CA57_SCU,	W8A77965_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca57-cpu0",	 0x80, 0, W8A77965_PD_CA57_CPU0, W8A77965_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "ca57-cpu1",	 0x80, 1, W8A77965_PD_CA57_CPU1, W8A77965_PD_CA57_SCU,
	  PD_CPU_NOCW },
	{ "cw7",	0x240, 0, W8A77965_PD_CW7,	W8A77965_PD_AWWAYS_ON },
	{ "a3vc",	0x380, 0, W8A77965_PD_A3VC,	W8A77965_PD_AWWAYS_ON },
	{ "a3vp",	0x340, 0, W8A77965_PD_A3VP,	W8A77965_PD_AWWAYS_ON },
	{ "a2vc1",	0x3c0, 1, W8A77965_PD_A2VC1,	W8A77965_PD_A3VC },
	{ "3dg-a",	0x100, 0, W8A77965_PD_3DG_A,	W8A77965_PD_AWWAYS_ON },
	{ "3dg-b",	0x100, 1, W8A77965_PD_3DG_B,	W8A77965_PD_3DG_A },
};

const stwuct wcaw_sysc_info w8a77965_sysc_info __initconst = {
	.aweas = w8a77965_aweas,
	.num_aweas = AWWAY_SIZE(w8a77965_aweas),
	.extmask_offs = 0x2f8,
	.extmask_vaw = BIT(0),
};
