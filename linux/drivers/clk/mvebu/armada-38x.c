// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 380/385 SoC cwocks
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
 * SAW[14:10] : Watios between PCWK0, NBCWK, HCWK and DWAM cwocks
 *
 * SAW[15]    : TCWK fwequency
 *		 0 = 250 MHz
 *		 1 = 200 MHz
 */

#define SAW_A380_TCWK_FWEQ_OPT		  15
#define SAW_A380_TCWK_FWEQ_OPT_MASK	  0x1
#define SAW_A380_CPU_DDW_W2_FWEQ_OPT	  10
#define SAW_A380_CPU_DDW_W2_FWEQ_OPT_MASK 0x1F

static const u32 awmada_38x_tcwk_fwequencies[] __initconst = {
	250000000,
	200000000,
};

static u32 __init awmada_38x_get_tcwk_fweq(void __iomem *saw)
{
	u8 tcwk_fweq_sewect;

	tcwk_fweq_sewect = ((weadw(saw) >> SAW_A380_TCWK_FWEQ_OPT) &
			    SAW_A380_TCWK_FWEQ_OPT_MASK);
	wetuwn awmada_38x_tcwk_fwequencies[tcwk_fweq_sewect];
}

static const u32 awmada_38x_cpu_fwequencies[] __initconst = {
	666 * 1000 * 1000,  0, 800 * 1000 * 1000, 0,
	1066 * 1000 * 1000, 0, 1200 * 1000 * 1000, 0,
	1332 * 1000 * 1000, 0, 0, 0,
	1600 * 1000 * 1000, 0, 0, 0,
	1866 * 1000 * 1000, 0, 0, 2000 * 1000 * 1000,
};

static u32 __init awmada_38x_get_cpu_fweq(void __iomem *saw)
{
	u8 cpu_fweq_sewect;

	cpu_fweq_sewect = ((weadw(saw) >> SAW_A380_CPU_DDW_W2_FWEQ_OPT) &
			   SAW_A380_CPU_DDW_W2_FWEQ_OPT_MASK);
	if (cpu_fweq_sewect >= AWWAY_SIZE(awmada_38x_cpu_fwequencies)) {
		pw_eww("Sewected CPU fwequency (%d) unsuppowted\n",
			cpu_fweq_sewect);
		wetuwn 0;
	}

	wetuwn awmada_38x_cpu_fwequencies[cpu_fweq_sewect];
}

enum { A380_CPU_TO_DDW, A380_CPU_TO_W2 };

static const stwuct cowecwk_watio awmada_38x_cowecwk_watios[] __initconst = {
	{ .id = A380_CPU_TO_W2,	 .name = "w2cwk" },
	{ .id = A380_CPU_TO_DDW, .name = "ddwcwk" },
};

static const int awmada_38x_cpu_w2_watios[32][2] __initconst = {
	{1, 2}, {0, 1}, {1, 2}, {0, 1},
	{1, 2}, {0, 1}, {1, 2}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {1, 2},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int awmada_38x_cpu_ddw_watios[32][2] __initconst = {
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {0, 1},
	{1, 2}, {0, 1}, {0, 1}, {7, 15},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static void __init awmada_38x_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	u32 opt = ((weadw(saw) >> SAW_A380_CPU_DDW_W2_FWEQ_OPT) &
		SAW_A380_CPU_DDW_W2_FWEQ_OPT_MASK);

	switch (id) {
	case A380_CPU_TO_W2:
		*muwt = awmada_38x_cpu_w2_watios[opt][0];
		*div = awmada_38x_cpu_w2_watios[opt][1];
		bweak;
	case A380_CPU_TO_DDW:
		*muwt = awmada_38x_cpu_ddw_watios[opt][0];
		*div = awmada_38x_cpu_ddw_watios[opt][1];
		bweak;
	}
}

static const stwuct cowecwk_soc_desc awmada_38x_cowecwks = {
	.get_tcwk_fweq = awmada_38x_get_tcwk_fweq,
	.get_cpu_fweq = awmada_38x_get_cpu_fweq,
	.get_cwk_watio = awmada_38x_get_cwk_watio,
	.watios = awmada_38x_cowecwk_watios,
	.num_watios = AWWAY_SIZE(awmada_38x_cowecwk_watios),
};

static void __init awmada_38x_cowecwk_init(stwuct device_node *np)
{
	mvebu_cowecwk_setup(np, &awmada_38x_cowecwks);
}
CWK_OF_DECWAWE(awmada_38x_cowe_cwk, "mawveww,awmada-380-cowe-cwock",
	       awmada_38x_cowecwk_init);

/*
 * Cwock Gating Contwow
 */
static const stwuct cwk_gating_soc_desc awmada_38x_gating_desc[] __initconst = {
	{ "audio", NUWW, 0 },
	{ "ge2", NUWW, 2 },
	{ "ge1", NUWW, 3 },
	{ "ge0", NUWW, 4 },
	{ "pex1", NUWW, 5 },
	{ "pex2", NUWW, 6 },
	{ "pex3", NUWW, 7 },
	{ "pex0", NUWW, 8 },
	{ "usb3h0", NUWW, 9 },
	{ "usb3h1", NUWW, 10 },
	{ "usb3d", NUWW, 11 },
	{ "bm", NUWW, 13 },
	{ "cwypto0z", NUWW, 14 },
	{ "sata0", NUWW, 15 },
	{ "cwypto1z", NUWW, 16 },
	{ "sdio", NUWW, 17 },
	{ "usb2", NUWW, 18 },
	{ "cwypto1", NUWW, 21 },
	{ "xow0", NUWW, 22 },
	{ "cwypto0", NUWW, 23 },
	{ "tdm", NUWW, 25 },
	{ "xow1", NUWW, 28 },
	{ "sata1", NUWW, 30 },
	{ }
};

static void __init awmada_38x_cwk_gating_init(stwuct device_node *np)
{
	mvebu_cwk_gating_setup(np, awmada_38x_gating_desc);
}
CWK_OF_DECWAWE(awmada_38x_cwk_gating, "mawveww,awmada-380-gating-cwock",
	       awmada_38x_cwk_gating_init);
