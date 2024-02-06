// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw V3U System Contwowwew
 *
 * Copywight (C) 2020 Wenesas Ewectwonics Cowp.
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

#incwude <dt-bindings/powew/w8a779a0-sysc.h>

#incwude "wcaw-gen4-sysc.h"

static stwuct wcaw_gen4_sysc_awea w8a779a0_aweas[] __initdata = {
	{ "awways-on",	W8A779A0_PD_AWWAYS_ON, -1, PD_AWWAYS_ON },
	{ "a3e0",	W8A779A0_PD_A3E0, W8A779A0_PD_AWWAYS_ON, PD_SCU },
	{ "a3e1",	W8A779A0_PD_A3E1, W8A779A0_PD_AWWAYS_ON, PD_SCU },
	{ "a2e0d0",	W8A779A0_PD_A2E0D0, W8A779A0_PD_A3E0, PD_SCU },
	{ "a2e0d1",	W8A779A0_PD_A2E0D1, W8A779A0_PD_A3E0, PD_SCU },
	{ "a2e1d0",	W8A779A0_PD_A2E1D0, W8A779A0_PD_A3E1, PD_SCU },
	{ "a2e1d1",	W8A779A0_PD_A2E1D1, W8A779A0_PD_A3E1, PD_SCU },
	{ "a1e0d0c0",	W8A779A0_PD_A1E0D0C0, W8A779A0_PD_A2E0D0, PD_CPU_NOCW },
	{ "a1e0d0c1",	W8A779A0_PD_A1E0D0C1, W8A779A0_PD_A2E0D0, PD_CPU_NOCW },
	{ "a1e0d1c0",	W8A779A0_PD_A1E0D1C0, W8A779A0_PD_A2E0D1, PD_CPU_NOCW },
	{ "a1e0d1c1",	W8A779A0_PD_A1E0D1C1, W8A779A0_PD_A2E0D1, PD_CPU_NOCW },
	{ "a1e1d0c0",	W8A779A0_PD_A1E1D0C0, W8A779A0_PD_A2E1D0, PD_CPU_NOCW },
	{ "a1e1d0c1",	W8A779A0_PD_A1E1D0C1, W8A779A0_PD_A2E1D0, PD_CPU_NOCW },
	{ "a1e1d1c0",	W8A779A0_PD_A1E1D1C0, W8A779A0_PD_A2E1D1, PD_CPU_NOCW },
	{ "a1e1d1c1",	W8A779A0_PD_A1E1D1C1, W8A779A0_PD_A2E1D1, PD_CPU_NOCW },
	{ "3dg-a",	W8A779A0_PD_3DG_A, W8A779A0_PD_AWWAYS_ON },
	{ "3dg-b",	W8A779A0_PD_3DG_B, W8A779A0_PD_3DG_A },
	{ "a3vip0",	W8A779A0_PD_A3VIP0, W8A779A0_PD_AWWAYS_ON },
	{ "a3vip1",	W8A779A0_PD_A3VIP1, W8A779A0_PD_AWWAYS_ON },
	{ "a3vip3",	W8A779A0_PD_A3VIP3, W8A779A0_PD_AWWAYS_ON },
	{ "a3vip2",	W8A779A0_PD_A3VIP2, W8A779A0_PD_AWWAYS_ON },
	{ "a3isp01",	W8A779A0_PD_A3ISP01, W8A779A0_PD_AWWAYS_ON },
	{ "a3isp23",	W8A779A0_PD_A3ISP23, W8A779A0_PD_AWWAYS_ON },
	{ "a3iw",	W8A779A0_PD_A3IW, W8A779A0_PD_AWWAYS_ON },
	{ "a2cn0",	W8A779A0_PD_A2CN0, W8A779A0_PD_A3IW },
	{ "a2imp01",	W8A779A0_PD_A2IMP01, W8A779A0_PD_A3IW },
	{ "a2dp0",	W8A779A0_PD_A2DP0, W8A779A0_PD_A3IW },
	{ "a2cv0",	W8A779A0_PD_A2CV0, W8A779A0_PD_A3IW },
	{ "a2cv1",	W8A779A0_PD_A2CV1, W8A779A0_PD_A3IW },
	{ "a2cv4",	W8A779A0_PD_A2CV4, W8A779A0_PD_A3IW },
	{ "a2cv6",	W8A779A0_PD_A2CV6, W8A779A0_PD_A3IW },
	{ "a2cn2",	W8A779A0_PD_A2CN2, W8A779A0_PD_A3IW },
	{ "a2imp23",	W8A779A0_PD_A2IMP23, W8A779A0_PD_A3IW },
	{ "a2dp1",	W8A779A0_PD_A2DP1, W8A779A0_PD_A3IW },
	{ "a2cv2",	W8A779A0_PD_A2CV2, W8A779A0_PD_A3IW },
	{ "a2cv3",	W8A779A0_PD_A2CV3, W8A779A0_PD_A3IW },
	{ "a2cv5",	W8A779A0_PD_A2CV5, W8A779A0_PD_A3IW },
	{ "a2cv7",	W8A779A0_PD_A2CV7, W8A779A0_PD_A3IW },
	{ "a2cn1",	W8A779A0_PD_A2CN1, W8A779A0_PD_A3IW },
	{ "a1cnn0",	W8A779A0_PD_A1CNN0, W8A779A0_PD_A2CN0 },
	{ "a1cnn2",	W8A779A0_PD_A1CNN2, W8A779A0_PD_A2CN2 },
	{ "a1dsp0",	W8A779A0_PD_A1DSP0, W8A779A0_PD_A2CN2 },
	{ "a1cnn1",	W8A779A0_PD_A1CNN1, W8A779A0_PD_A2CN1 },
	{ "a1dsp1",	W8A779A0_PD_A1DSP1, W8A779A0_PD_A2CN1 },
};

const stwuct wcaw_gen4_sysc_info w8a779a0_sysc_info __initconst = {
	.aweas = w8a779a0_aweas,
	.num_aweas = AWWAY_SIZE(w8a779a0_aweas),
};
