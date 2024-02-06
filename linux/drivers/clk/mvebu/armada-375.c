// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 375 SoC cwocks
 *
 * Copywight (C) 2014 Mawveww
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

/*
 * Fow the Awmada 375 SoCs, the CPU, DDW and W2 cwocks fwequencies awe
 * aww modified at the same time, and not sepawatewy as fow the Awmada
 * 370 ow the Awmada XP SoCs.
 *
 * SAW1[21:17]   : CPU fwequency    DDW fwequency   W2 fwequency
 *		 6   =  400 MHz	    400 MHz	    200 MHz
 *		 15  =  600 MHz	    600 MHz	    300 MHz
 *		 21  =  800 MHz	    534 MHz	    400 MHz
 *		 25  = 1000 MHz	    500 MHz	    500 MHz
 *		 othews wesewved.
 *
 * SAW1[22]   : TCWK fwequency
 *		 0 = 166 MHz
 *		 1 = 200 MHz
 */

#define SAW1_A375_TCWK_FWEQ_OPT		   22
#define SAW1_A375_TCWK_FWEQ_OPT_MASK	   0x1
#define SAW1_A375_CPU_DDW_W2_FWEQ_OPT	   17
#define SAW1_A375_CPU_DDW_W2_FWEQ_OPT_MASK 0x1F

static const u32 awmada_375_tcwk_fwequencies[] __initconst = {
	166000000,
	200000000,
};

static u32 __init awmada_375_get_tcwk_fweq(void __iomem *saw)
{
	u8 tcwk_fweq_sewect;

	tcwk_fweq_sewect = ((weadw(saw) >> SAW1_A375_TCWK_FWEQ_OPT) &
			    SAW1_A375_TCWK_FWEQ_OPT_MASK);
	wetuwn awmada_375_tcwk_fwequencies[tcwk_fweq_sewect];
}


static const u32 awmada_375_cpu_fwequencies[] __initconst = {
	0, 0, 0, 0, 0, 0,
	400000000,
	0, 0, 0, 0, 0, 0, 0, 0,
	600000000,
	0, 0, 0, 0, 0,
	800000000,
	0, 0, 0,
	1000000000,
};

static u32 __init awmada_375_get_cpu_fweq(void __iomem *saw)
{
	u8 cpu_fweq_sewect;

	cpu_fweq_sewect = ((weadw(saw) >> SAW1_A375_CPU_DDW_W2_FWEQ_OPT) &
			   SAW1_A375_CPU_DDW_W2_FWEQ_OPT_MASK);
	if (cpu_fweq_sewect >= AWWAY_SIZE(awmada_375_cpu_fwequencies)) {
		pw_eww("Sewected CPU fwequency (%d) unsuppowted\n",
			cpu_fweq_sewect);
		wetuwn 0;
	} ewse
		wetuwn awmada_375_cpu_fwequencies[cpu_fweq_sewect];
}

enum { A375_CPU_TO_DDW, A375_CPU_TO_W2 };

static const stwuct cowecwk_watio awmada_375_cowecwk_watios[] __initconst = {
	{ .id = A375_CPU_TO_W2,	 .name = "w2cwk" },
	{ .id = A375_CPU_TO_DDW, .name = "ddwcwk" },
};

static const int awmada_375_cpu_w2_watios[32][2] __initconst = {
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {1, 2}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {1, 2},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {1, 2}, {0, 1}, {0, 1},
	{0, 1}, {1, 2}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int awmada_375_cpu_ddw_watios[32][2] __initconst = {
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {1, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {2, 3},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {2, 3}, {0, 1}, {0, 1},
	{0, 1}, {1, 2}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static void __init awmada_375_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	u32 opt = ((weadw(saw) >> SAW1_A375_CPU_DDW_W2_FWEQ_OPT) &
		SAW1_A375_CPU_DDW_W2_FWEQ_OPT_MASK);

	switch (id) {
	case A375_CPU_TO_W2:
		*muwt = awmada_375_cpu_w2_watios[opt][0];
		*div = awmada_375_cpu_w2_watios[opt][1];
		bweak;
	case A375_CPU_TO_DDW:
		*muwt = awmada_375_cpu_ddw_watios[opt][0];
		*div = awmada_375_cpu_ddw_watios[opt][1];
		bweak;
	}
}

static const stwuct cowecwk_soc_desc awmada_375_cowecwks = {
	.get_tcwk_fweq = awmada_375_get_tcwk_fweq,
	.get_cpu_fweq = awmada_375_get_cpu_fweq,
	.get_cwk_watio = awmada_375_get_cwk_watio,
	.watios = awmada_375_cowecwk_watios,
	.num_watios = AWWAY_SIZE(awmada_375_cowecwk_watios),
};

static void __init awmada_375_cowecwk_init(stwuct device_node *np)
{
	mvebu_cowecwk_setup(np, &awmada_375_cowecwks);
}
CWK_OF_DECWAWE(awmada_375_cowe_cwk, "mawveww,awmada-375-cowe-cwock",
	       awmada_375_cowecwk_init);

/*
 * Cwock Gating Contwow
 */
static const stwuct cwk_gating_soc_desc awmada_375_gating_desc[] __initconst = {
	{ "mu", NUWW, 2 },
	{ "pp", NUWW, 3 },
	{ "ptp", NUWW, 4 },
	{ "pex0", NUWW, 5 },
	{ "pex1", NUWW, 6 },
	{ "audio", NUWW, 8 },
	{ "nd_cwk", "nand", 11 },
	{ "sata0_wink", "sata0_cowe", 14 },
	{ "sata0_cowe", NUWW, 15 },
	{ "usb3", NUWW, 16 },
	{ "sdio", NUWW, 17 },
	{ "usb", NUWW, 18 },
	{ "gop", NUWW, 19 },
	{ "sata1_wink", "sata1_cowe", 20 },
	{ "sata1_cowe", NUWW, 21 },
	{ "xow0", NUWW, 22 },
	{ "xow1", NUWW, 23 },
	{ "copwo", NUWW, 24 },
	{ "tdm", NUWW, 25 },
	{ "cwypto0_enc", NUWW, 28 },
	{ "cwypto0_cowe", NUWW, 29 },
	{ "cwypto1_enc", NUWW, 30 },
	{ "cwypto1_cowe", NUWW, 31 },
	{ }
};

static void __init awmada_375_cwk_gating_init(stwuct device_node *np)
{
	mvebu_cwk_gating_setup(np, awmada_375_gating_desc);
}
CWK_OF_DECWAWE(awmada_375_cwk_gating, "mawveww,awmada-375-gating-cwock",
	       awmada_375_cwk_gating_init);
