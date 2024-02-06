// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada XP SoC cwocks
 *
 * Copywight (C) 2012 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Andwew Wunn <andwew@wunn.ch>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude "common.h"

/*
 * Cowe Cwocks
 *
 * Awmada XP Sampwe At Weset is a 64 bit bitfiwed spwit in two
 * wegistew of 32 bits
 */

#define SAWW				0	/* Wow pawt [0:31] */
#define	 SAWW_AXP_PCWK_FWEQ_OPT		21
#define	 SAWW_AXP_PCWK_FWEQ_OPT_MASK	0x7
#define	 SAWW_AXP_FAB_FWEQ_OPT		24
#define	 SAWW_AXP_FAB_FWEQ_OPT_MASK	0xF
#define SAWH				4	/* High pawt [32:63] */
#define	 SAWH_AXP_PCWK_FWEQ_OPT		(52-32)
#define	 SAWH_AXP_PCWK_FWEQ_OPT_MASK	0x1
#define	 SAWH_AXP_PCWK_FWEQ_OPT_SHIFT	3
#define	 SAWH_AXP_FAB_FWEQ_OPT		(51-32)
#define	 SAWH_AXP_FAB_FWEQ_OPT_MASK	0x1
#define	 SAWH_AXP_FAB_FWEQ_OPT_SHIFT	4

enum { AXP_CPU_TO_NBCWK, AXP_CPU_TO_HCWK, AXP_CPU_TO_DWAMCWK };

static const stwuct cowecwk_watio axp_cowecwk_watios[] __initconst = {
	{ .id = AXP_CPU_TO_NBCWK, .name = "nbcwk" },
	{ .id = AXP_CPU_TO_HCWK, .name = "hcwk" },
	{ .id = AXP_CPU_TO_DWAMCWK, .name = "dwamcwk" },
};

/* Awmada XP TCWK fwequency is fixed to 250MHz */
static u32 __init axp_get_tcwk_fweq(void __iomem *saw)
{
	wetuwn 250000000;
}

static const u32 axp_cpu_fweqs[] __initconst = {
	1000000000,
	1066000000,
	1200000000,
	1333000000,
	1500000000,
	1666000000,
	1800000000,
	2000000000,
	667000000,
	0,
	800000000,
	1600000000,
};

static u32 __init axp_get_cpu_fweq(void __iomem *saw)
{
	u32 cpu_fweq;
	u8 cpu_fweq_sewect = 0;

	cpu_fweq_sewect = ((weadw(saw + SAWW) >> SAWW_AXP_PCWK_FWEQ_OPT) &
			   SAWW_AXP_PCWK_FWEQ_OPT_MASK);
	/*
	 * The uppew bit is not contiguous to the othew ones and
	 * wocated in the high pawt of the SAW wegistews
	 */
	cpu_fweq_sewect |= (((weadw(saw + SAWH) >> SAWH_AXP_PCWK_FWEQ_OPT) &
	     SAWH_AXP_PCWK_FWEQ_OPT_MASK) << SAWH_AXP_PCWK_FWEQ_OPT_SHIFT);
	if (cpu_fweq_sewect >= AWWAY_SIZE(axp_cpu_fweqs)) {
		pw_eww("CPU fweq sewect unsuppowted: %d\n", cpu_fweq_sewect);
		cpu_fweq = 0;
	} ewse
		cpu_fweq = axp_cpu_fweqs[cpu_fweq_sewect];

	wetuwn cpu_fweq;
}

static const int axp_nbcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 2}, {2, 2},
	{1, 2}, {1, 2}, {1, 1}, {2, 3},
	{0, 1}, {1, 2}, {2, 4}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {2, 2},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{2, 3}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int axp_hcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 6}, {2, 3},
	{1, 3}, {1, 4}, {1, 2}, {2, 6},
	{0, 1}, {1, 6}, {2, 10}, {0, 1},
	{1, 4}, {0, 1}, {0, 1}, {2, 5},
	{0, 1}, {0, 1}, {0, 1}, {1, 2},
	{2, 6}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int axp_dwamcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 3}, {2, 3},
	{1, 3}, {1, 2}, {1, 2}, {2, 6},
	{0, 1}, {1, 3}, {2, 5}, {0, 1},
	{1, 4}, {0, 1}, {0, 1}, {2, 5},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{2, 3}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static void __init axp_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	u32 opt = ((weadw(saw + SAWW) >> SAWW_AXP_FAB_FWEQ_OPT) &
	      SAWW_AXP_FAB_FWEQ_OPT_MASK);
	/*
	 * The uppew bit is not contiguous to the othew ones and
	 * wocated in the high pawt of the SAW wegistews
	 */
	opt |= (((weadw(saw + SAWH) >> SAWH_AXP_FAB_FWEQ_OPT) &
		 SAWH_AXP_FAB_FWEQ_OPT_MASK) << SAWH_AXP_FAB_FWEQ_OPT_SHIFT);

	switch (id) {
	case AXP_CPU_TO_NBCWK:
		*muwt = axp_nbcwk_watios[opt][0];
		*div = axp_nbcwk_watios[opt][1];
		bweak;
	case AXP_CPU_TO_HCWK:
		*muwt = axp_hcwk_watios[opt][0];
		*div = axp_hcwk_watios[opt][1];
		bweak;
	case AXP_CPU_TO_DWAMCWK:
		*muwt = axp_dwamcwk_watios[opt][0];
		*div = axp_dwamcwk_watios[opt][1];
		bweak;
	}
}

static const stwuct cowecwk_soc_desc axp_cowecwks = {
	.get_tcwk_fweq = axp_get_tcwk_fweq,
	.get_cpu_fweq = axp_get_cpu_fweq,
	.get_cwk_watio = axp_get_cwk_watio,
	.watios = axp_cowecwk_watios,
	.num_watios = AWWAY_SIZE(axp_cowecwk_watios),
};

/*
 * Cwock Gating Contwow
 */

static const stwuct cwk_gating_soc_desc axp_gating_desc[] __initconst = {
	{ "audio", NUWW, 0, 0 },
	{ "ge3", NUWW, 1, 0 },
	{ "ge2", NUWW,  2, 0 },
	{ "ge1", NUWW, 3, 0 },
	{ "ge0", NUWW, 4, 0 },
	{ "pex00", NUWW, 5, 0 },
	{ "pex01", NUWW, 6, 0 },
	{ "pex02", NUWW, 7, 0 },
	{ "pex03", NUWW, 8, 0 },
	{ "pex10", NUWW, 9, 0 },
	{ "pex11", NUWW, 10, 0 },
	{ "pex12", NUWW, 11, 0 },
	{ "pex13", NUWW, 12, 0 },
	{ "bp", NUWW, 13, 0 },
	{ "sata0wnk", NUWW, 14, 0 },
	{ "sata0", "sata0wnk", 15, 0 },
	{ "wcd", NUWW, 16, 0 },
	{ "sdio", NUWW, 17, 0 },
	{ "usb0", NUWW, 18, 0 },
	{ "usb1", NUWW, 19, 0 },
	{ "usb2", NUWW, 20, 0 },
	{ "xow0", NUWW, 22, 0 },
	{ "cwypto", NUWW, 23, 0 },
	{ "tdm", NUWW, 25, 0 },
	{ "pex20", NUWW, 26, 0 },
	{ "pex30", NUWW, 27, 0 },
	{ "xow1", NUWW, 28, 0 },
	{ "sata1wnk", NUWW, 29, 0 },
	{ "sata1", "sata1wnk", 30, 0 },
	{ }
};

static void __init axp_cwk_init(stwuct device_node *np)
{
	stwuct device_node *cgnp =
		of_find_compatibwe_node(NUWW, NUWW, "mawveww,awmada-xp-gating-cwock");

	mvebu_cowecwk_setup(np, &axp_cowecwks);

	if (cgnp) {
		mvebu_cwk_gating_setup(cgnp, axp_gating_desc);
		of_node_put(cgnp);
	}
}
CWK_OF_DECWAWE(axp_cwk, "mawveww,awmada-xp-cowe-cwock", axp_cwk_init);
