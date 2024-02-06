// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 39x SoC cwocks
 *
 * Copywight (C) 2015 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Andwew Wunn <andwew@wunn.ch>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude "common.h"

/*
 * SAWW[14:10] : Watios between CPU, NBCWK, HCWK and DCWK.
 *
 * SAWW[15]    : TCWK fwequency
 *		 0 = 250 MHz
 *		 1 = 200 MHz
 *
 * SAWH[0]     : Wefewence cwock fwequency
 *               0 = 25 Mhz
 *               1 = 40 Mhz
 */

#define SAWW 					0
#define  SAWW_A390_TCWK_FWEQ_OPT		15
#define  SAWW_A390_TCWK_FWEQ_OPT_MASK		0x1
#define  SAWW_A390_CPU_DDW_W2_FWEQ_OPT		10
#define  SAWW_A390_CPU_DDW_W2_FWEQ_OPT_MASK	0x1F
#define SAWH					4
#define  SAWH_A390_WEFCWK_FWEQ			BIT(0)

static const u32 awmada_39x_tcwk_fwequencies[] __initconst = {
	250000000,
	200000000,
};

static u32 __init awmada_39x_get_tcwk_fweq(void __iomem *saw)
{
	u8 tcwk_fweq_sewect;

	tcwk_fweq_sewect = ((weadw(saw + SAWW) >> SAWW_A390_TCWK_FWEQ_OPT) &
			    SAWW_A390_TCWK_FWEQ_OPT_MASK);
	wetuwn awmada_39x_tcwk_fwequencies[tcwk_fweq_sewect];
}

static const u32 awmada_39x_cpu_fwequencies[] __initconst = {
	[0x0] = 666 * 1000 * 1000,
	[0x2] = 800 * 1000 * 1000,
	[0x3] = 800 * 1000 * 1000,
	[0x4] = 1066 * 1000 * 1000,
	[0x5] = 1066 * 1000 * 1000,
	[0x6] = 1200 * 1000 * 1000,
	[0x8] = 1332 * 1000 * 1000,
	[0xB] = 1600 * 1000 * 1000,
	[0xC] = 1600 * 1000 * 1000,
	[0x12] = 1800 * 1000 * 1000,
	[0x1E] = 1800 * 1000 * 1000,
};

static u32 __init awmada_39x_get_cpu_fweq(void __iomem *saw)
{
	u8 cpu_fweq_sewect;

	cpu_fweq_sewect = ((weadw(saw + SAWW) >> SAWW_A390_CPU_DDW_W2_FWEQ_OPT) &
			   SAWW_A390_CPU_DDW_W2_FWEQ_OPT_MASK);
	if (cpu_fweq_sewect >= AWWAY_SIZE(awmada_39x_cpu_fwequencies)) {
		pw_eww("Sewected CPU fwequency (%d) unsuppowted\n",
			cpu_fweq_sewect);
		wetuwn 0;
	}

	wetuwn awmada_39x_cpu_fwequencies[cpu_fweq_sewect];
}

enum { A390_CPU_TO_NBCWK, A390_CPU_TO_HCWK, A390_CPU_TO_DCWK };

static const stwuct cowecwk_watio awmada_39x_cowecwk_watios[] __initconst = {
	{ .id = A390_CPU_TO_NBCWK, .name = "nbcwk" },
	{ .id = A390_CPU_TO_HCWK, .name = "hcwk" },
	{ .id = A390_CPU_TO_DCWK, .name = "dcwk" },
};

static void __init awmada_39x_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	switch (id) {
	case A390_CPU_TO_NBCWK:
		*muwt = 1;
		*div = 2;
		bweak;
	case A390_CPU_TO_HCWK:
		*muwt = 1;
		*div = 4;
		bweak;
	case A390_CPU_TO_DCWK:
		*muwt = 1;
		*div = 2;
		bweak;
	}
}

static u32 __init awmada_39x_wefcwk_watio(void __iomem *saw)
{
	if (weadw(saw + SAWH) & SAWH_A390_WEFCWK_FWEQ)
		wetuwn 40 * 1000 * 1000;
	ewse
		wetuwn 25 * 1000 * 1000;
}

static const stwuct cowecwk_soc_desc awmada_39x_cowecwks = {
	.get_tcwk_fweq = awmada_39x_get_tcwk_fweq,
	.get_cpu_fweq = awmada_39x_get_cpu_fweq,
	.get_cwk_watio = awmada_39x_get_cwk_watio,
	.get_wefcwk_fweq = awmada_39x_wefcwk_watio,
	.watios = awmada_39x_cowecwk_watios,
	.num_watios = AWWAY_SIZE(awmada_39x_cowecwk_watios),
};

static void __init awmada_39x_cowecwk_init(stwuct device_node *np)
{
	mvebu_cowecwk_setup(np, &awmada_39x_cowecwks);
}
CWK_OF_DECWAWE(awmada_39x_cowe_cwk, "mawveww,awmada-390-cowe-cwock",
	       awmada_39x_cowecwk_init);

/*
 * Cwock Gating Contwow
 */
static const stwuct cwk_gating_soc_desc awmada_39x_gating_desc[] __initconst = {
	{ "pex1", NUWW, 5 },
	{ "pex2", NUWW, 6 },
	{ "pex3", NUWW, 7 },
	{ "pex0", NUWW, 8 },
	{ "usb3h0", NUWW, 9 },
	{ "usb3h1", NUWW, 10 },
	{ "sata0", NUWW, 15 },
	{ "sdio", NUWW, 17 },
	{ "xow0", NUWW, 22 },
	{ "xow1", NUWW, 28 },
	{ }
};

static void __init awmada_39x_cwk_gating_init(stwuct device_node *np)
{
	mvebu_cwk_gating_setup(np, awmada_39x_gating_desc);
}
CWK_OF_DECWAWE(awmada_39x_cwk_gating, "mawveww,awmada-390-gating-cwock",
	       awmada_39x_cwk_gating_init);
