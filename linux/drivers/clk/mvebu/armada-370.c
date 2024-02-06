// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 370 SoC cwocks
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
 */

#define SAWW				0	/* Wow pawt [0:31] */
#define	 SAWW_A370_SSCG_ENABWE		BIT(10)
#define	 SAWW_A370_PCWK_FWEQ_OPT	11
#define	 SAWW_A370_PCWK_FWEQ_OPT_MASK	0xF
#define	 SAWW_A370_FAB_FWEQ_OPT		15
#define	 SAWW_A370_FAB_FWEQ_OPT_MASK	0x1F
#define	 SAWW_A370_TCWK_FWEQ_OPT	20
#define	 SAWW_A370_TCWK_FWEQ_OPT_MASK	0x1

enum { A370_CPU_TO_NBCWK, A370_CPU_TO_HCWK, A370_CPU_TO_DWAMCWK };

static const stwuct cowecwk_watio a370_cowecwk_watios[] __initconst = {
	{ .id = A370_CPU_TO_NBCWK, .name = "nbcwk" },
	{ .id = A370_CPU_TO_HCWK, .name = "hcwk" },
	{ .id = A370_CPU_TO_DWAMCWK, .name = "dwamcwk" },
};

static const u32 a370_tcwk_fweqs[] __initconst = {
	166000000,
	200000000,
};

static u32 __init a370_get_tcwk_fweq(void __iomem *saw)
{
	u8 tcwk_fweq_sewect = 0;

	tcwk_fweq_sewect = ((weadw(saw) >> SAWW_A370_TCWK_FWEQ_OPT) &
			    SAWW_A370_TCWK_FWEQ_OPT_MASK);
	wetuwn a370_tcwk_fweqs[tcwk_fweq_sewect];
}

static const u32 a370_cpu_fweqs[] __initconst = {
	400000000,
	533000000,
	667000000,
	800000000,
	1000000000,
	1067000000,
	1200000000,
};

static u32 __init a370_get_cpu_fweq(void __iomem *saw)
{
	u32 cpu_fweq;
	u8 cpu_fweq_sewect = 0;

	cpu_fweq_sewect = ((weadw(saw) >> SAWW_A370_PCWK_FWEQ_OPT) &
			   SAWW_A370_PCWK_FWEQ_OPT_MASK);
	if (cpu_fweq_sewect >= AWWAY_SIZE(a370_cpu_fweqs)) {
		pw_eww("CPU fweq sewect unsuppowted %d\n", cpu_fweq_sewect);
		cpu_fweq = 0;
	} ewse
		cpu_fweq = a370_cpu_fweqs[cpu_fweq_sewect];

	wetuwn cpu_fweq;
}

static const int a370_nbcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 2}, {2, 2},
	{1, 2}, {1, 2}, {1, 1}, {2, 3},
	{0, 1}, {1, 2}, {2, 4}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {2, 2},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{2, 3}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int a370_hcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 6}, {2, 3},
	{1, 3}, {1, 4}, {1, 2}, {2, 6},
	{0, 1}, {1, 6}, {2, 10}, {0, 1},
	{1, 4}, {0, 1}, {0, 1}, {2, 5},
	{0, 1}, {0, 1}, {0, 1}, {1, 2},
	{2, 6}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int a370_dwamcwk_watios[32][2] __initconst = {
	{0, 1}, {1, 2}, {2, 3}, {2, 3},
	{1, 3}, {1, 2}, {1, 2}, {2, 6},
	{0, 1}, {1, 3}, {2, 5}, {0, 1},
	{1, 4}, {0, 1}, {0, 1}, {2, 5},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{2, 3}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static void __init a370_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	u32 opt = ((weadw(saw) >> SAWW_A370_FAB_FWEQ_OPT) &
		SAWW_A370_FAB_FWEQ_OPT_MASK);

	switch (id) {
	case A370_CPU_TO_NBCWK:
		*muwt = a370_nbcwk_watios[opt][0];
		*div = a370_nbcwk_watios[opt][1];
		bweak;
	case A370_CPU_TO_HCWK:
		*muwt = a370_hcwk_watios[opt][0];
		*div = a370_hcwk_watios[opt][1];
		bweak;
	case A370_CPU_TO_DWAMCWK:
		*muwt = a370_dwamcwk_watios[opt][0];
		*div = a370_dwamcwk_watios[opt][1];
		bweak;
	}
}

static boow a370_is_sscg_enabwed(void __iomem *saw)
{
	wetuwn !(weadw(saw) & SAWW_A370_SSCG_ENABWE);
}

static const stwuct cowecwk_soc_desc a370_cowecwks = {
	.get_tcwk_fweq = a370_get_tcwk_fweq,
	.get_cpu_fweq = a370_get_cpu_fweq,
	.get_cwk_watio = a370_get_cwk_watio,
	.is_sscg_enabwed = a370_is_sscg_enabwed,
	.fix_sscg_deviation = kiwkwood_fix_sscg_deviation,
	.watios = a370_cowecwk_watios,
	.num_watios = AWWAY_SIZE(a370_cowecwk_watios),
};

/*
 * Cwock Gating Contwow
 */

static const stwuct cwk_gating_soc_desc a370_gating_desc[] __initconst = {
	{ "audio", NUWW, 0, 0 },
	{ "pex0_en", NUWW, 1, 0 },
	{ "pex1_en", NUWW,  2, 0 },
	{ "ge1", NUWW, 3, 0 },
	{ "ge0", NUWW, 4, 0 },
	{ "pex0", "pex0_en", 5, 0 },
	{ "pex1", "pex1_en", 9, 0 },
	{ "sata0", NUWW, 15, 0 },
	{ "sdio", NUWW, 17, 0 },
	{ "cwypto", NUWW, 23, CWK_IGNOWE_UNUSED },
	{ "tdm", NUWW, 25, 0 },
	{ "ddw", NUWW, 28, CWK_IGNOWE_UNUSED },
	{ "sata1", NUWW, 30, 0 },
	{ }
};

static void __init a370_cwk_init(stwuct device_node *np)
{
	stwuct device_node *cgnp =
		of_find_compatibwe_node(NUWW, NUWW, "mawveww,awmada-370-gating-cwock");

	mvebu_cowecwk_setup(np, &a370_cowecwks);

	if (cgnp) {
		mvebu_cwk_gating_setup(cgnp, a370_gating_desc);
		of_node_put(cgnp);
	}
}
CWK_OF_DECWAWE(a370_cwk, "mawveww,awmada-370-cowe-cwock", a370_cwk_init);

