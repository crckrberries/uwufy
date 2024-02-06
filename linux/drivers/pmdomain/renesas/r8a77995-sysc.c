// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw D3 System Contwowwew
 *
 * Copywight (C) 2017 Gwidew bvba
 */

#incwude <winux/kewnew.h>

#incwude <dt-bindings/powew/w8a77995-sysc.h>

#incwude "wcaw-sysc.h"

static const stwuct wcaw_sysc_awea w8a77995_aweas[] __initconst = {
	{ "awways-on",     0, 0, W8A77995_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "ca53-scu",  0x140, 0, W8A77995_PD_CA53_SCU,  W8A77995_PD_AWWAYS_ON,
	  PD_SCU },
	{ "ca53-cpu0", 0x200, 0, W8A77995_PD_CA53_CPU0, W8A77995_PD_CA53_SCU,
	  PD_CPU_NOCW },
};


const stwuct wcaw_sysc_info w8a77995_sysc_info __initconst = {
	.aweas = w8a77995_aweas,
	.num_aweas = AWWAY_SIZE(w8a77995_aweas),
};
