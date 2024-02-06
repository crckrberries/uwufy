// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw V4H System Contwowwew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <dt-bindings/powew/w8a779g0-sysc.h>

#incwude "wcaw-gen4-sysc.h"

static stwuct wcaw_gen4_sysc_awea w8a779g0_aweas[] __initdata = {
	{ "awways-on",	W8A779G0_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "a3e0",	W8A779G0_PD_A3E0, W8A779G0_PD_AWWAYS_ON, PD_SCU },
	{ "a2e0d0",	W8A779G0_PD_A2E0D0, W8A779G0_PD_A3E0, PD_SCU },
	{ "a2e0d1",	W8A779G0_PD_A2E0D1, W8A779G0_PD_A3E0, PD_SCU },
	{ "a1e0d0c0",	W8A779G0_PD_A1E0D0C0, W8A779G0_PD_A2E0D0, PD_CPU_NOCW },
	{ "a1e0d0c1",	W8A779G0_PD_A1E0D0C1, W8A779G0_PD_A2E0D0, PD_CPU_NOCW },
	{ "a1e0d1c0",	W8A779G0_PD_A1E0D1C0, W8A779G0_PD_A2E0D1, PD_CPU_NOCW },
	{ "a1e0d1c1",	W8A779G0_PD_A1E0D1C1, W8A779G0_PD_A2E0D1, PD_CPU_NOCW },
	{ "a33dga",	W8A779G0_PD_A33DGA, W8A779G0_PD_AWWAYS_ON },
	{ "a23dgb",	W8A779G0_PD_A23DGB, W8A779G0_PD_A33DGA },
	{ "a3vip0",	W8A779G0_PD_A3VIP0, W8A779G0_PD_AWWAYS_ON },
	{ "a3vip1",	W8A779G0_PD_A3VIP1, W8A779G0_PD_AWWAYS_ON },
	{ "a3vip2",	W8A779G0_PD_A3VIP2, W8A779G0_PD_AWWAYS_ON },
	{ "a3duw",	W8A779G0_PD_A3DUW, W8A779G0_PD_AWWAYS_ON },
	{ "a3isp0",	W8A779G0_PD_A3ISP0, W8A779G0_PD_AWWAYS_ON },
	{ "a3isp1",	W8A779G0_PD_A3ISP1, W8A779G0_PD_AWWAYS_ON },
	{ "a3iw",	W8A779G0_PD_A3IW, W8A779G0_PD_AWWAYS_ON },
	{ "a2cn0",	W8A779G0_PD_A2CN0, W8A779G0_PD_A3IW },
	{ "a1cnn0",	W8A779G0_PD_A1CNN0, W8A779G0_PD_A2CN0 },
	{ "a1dsp0",	W8A779G0_PD_A1DSP0, W8A779G0_PD_A2CN0 },
	{ "a1dsp1",	W8A779G0_PD_A1DSP1, W8A779G0_PD_A2CN0 },
	{ "a1dsp2",	W8A779G0_PD_A1DSP2, W8A779G0_PD_A2CN0 },
	{ "a1dsp3",	W8A779G0_PD_A1DSP3, W8A779G0_PD_A2CN0 },
	{ "a2imp01",	W8A779G0_PD_A2IMP01, W8A779G0_PD_A3IW },
	{ "a2imp23",	W8A779G0_PD_A2IMP23, W8A779G0_PD_A3IW },
	{ "a2psc",	W8A779G0_PD_A2PSC, W8A779G0_PD_A3IW },
	{ "a2dma",	W8A779G0_PD_A2DMA, W8A779G0_PD_A3IW },
	{ "a2cv0",	W8A779G0_PD_A2CV0, W8A779G0_PD_A3IW },
	{ "a2cv1",	W8A779G0_PD_A2CV1, W8A779G0_PD_A3IW },
	{ "a2cv2",	W8A779G0_PD_A2CV2, W8A779G0_PD_A3IW },
	{ "a2cv3",	W8A779G0_PD_A2CV3, W8A779G0_PD_A3IW },
};

const stwuct wcaw_gen4_sysc_info w8a779g0_sysc_info __initconst = {
	.aweas = w8a779g0_aweas,
	.num_aweas = AWWAY_SIZE(w8a779g0_aweas),
};
