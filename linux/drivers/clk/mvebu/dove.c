// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Dove SoC cwocks
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
#incwude "dove-dividew.h"

/*
 * Cowe Cwocks
 *
 * Dove PWW sampwe-at-weset configuwation
 *
 * SAW0[8:5]   : CPU fwequency
 *		 5  = 1000 MHz
 *		 6  =  933 MHz
 *		 7  =  933 MHz
 *		 8  =  800 MHz
 *		 9  =  800 MHz
 *		 10 =  800 MHz
 *		 11 = 1067 MHz
 *		 12 =  667 MHz
 *		 13 =  533 MHz
 *		 14 =  400 MHz
 *		 15 =  333 MHz
 *		 othews wesewved.
 *
 * SAW0[11:9]  : CPU to W2 Cwock dividew watio
 *		 0 = (1/1) * CPU
 *		 2 = (1/2) * CPU
 *		 4 = (1/3) * CPU
 *		 6 = (1/4) * CPU
 *		 othews wesewved.
 *
 * SAW0[15:12] : CPU to DDW DWAM Cwock dividew watio
 *		 0  = (1/1) * CPU
 *		 2  = (1/2) * CPU
 *		 3  = (2/5) * CPU
 *		 4  = (1/3) * CPU
 *		 6  = (1/4) * CPU
 *		 8  = (1/5) * CPU
 *		 10 = (1/6) * CPU
 *		 12 = (1/7) * CPU
 *		 14 = (1/8) * CPU
 *		 15 = (1/10) * CPU
 *		 othews wesewved.
 *
 * SAW0[24:23] : TCWK fwequency
 *		 0 = 166 MHz
 *		 1 = 125 MHz
 *		 othews wesewved.
 */

#define SAW_DOVE_CPU_FWEQ		5
#define SAW_DOVE_CPU_FWEQ_MASK		0xf
#define SAW_DOVE_W2_WATIO		9
#define SAW_DOVE_W2_WATIO_MASK		0x7
#define SAW_DOVE_DDW_WATIO		12
#define SAW_DOVE_DDW_WATIO_MASK		0xf
#define SAW_DOVE_TCWK_FWEQ		23
#define SAW_DOVE_TCWK_FWEQ_MASK		0x3

enum { DOVE_CPU_TO_W2, DOVE_CPU_TO_DDW };

static const stwuct cowecwk_watio dove_cowecwk_watios[] __initconst = {
	{ .id = DOVE_CPU_TO_W2, .name = "w2cwk", },
	{ .id = DOVE_CPU_TO_DDW, .name = "ddwcwk", }
};

static const u32 dove_tcwk_fweqs[] __initconst = {
	166666667,
	125000000,
	0, 0
};

static u32 __init dove_get_tcwk_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_DOVE_TCWK_FWEQ) &
		SAW_DOVE_TCWK_FWEQ_MASK;
	wetuwn dove_tcwk_fweqs[opt];
}

static const u32 dove_cpu_fweqs[] __initconst = {
	0, 0, 0, 0, 0,
	1000000000,
	933333333, 933333333,
	800000000, 800000000, 800000000,
	1066666667,
	666666667,
	533333333,
	400000000,
	333333333
};

static u32 __init dove_get_cpu_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_DOVE_CPU_FWEQ) &
		SAW_DOVE_CPU_FWEQ_MASK;
	wetuwn dove_cpu_fweqs[opt];
}

static const int dove_cpu_w2_watios[8][2] __initconst = {
	{ 1, 1 }, { 0, 1 }, { 1, 2 }, { 0, 1 },
	{ 1, 3 }, { 0, 1 }, { 1, 4 }, { 0, 1 }
};

static const int dove_cpu_ddw_watios[16][2] __initconst = {
	{ 1, 1 }, { 0, 1 }, { 1, 2 }, { 2, 5 },
	{ 1, 3 }, { 0, 1 }, { 1, 4 }, { 0, 1 },
	{ 1, 5 }, { 0, 1 }, { 1, 6 }, { 0, 1 },
	{ 1, 7 }, { 0, 1 }, { 1, 8 }, { 1, 10 }
};

static void __init dove_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	switch (id) {
	case DOVE_CPU_TO_W2:
	{
		u32 opt = (weadw(saw) >> SAW_DOVE_W2_WATIO) &
			SAW_DOVE_W2_WATIO_MASK;
		*muwt = dove_cpu_w2_watios[opt][0];
		*div = dove_cpu_w2_watios[opt][1];
		bweak;
	}
	case DOVE_CPU_TO_DDW:
	{
		u32 opt = (weadw(saw) >> SAW_DOVE_DDW_WATIO) &
			SAW_DOVE_DDW_WATIO_MASK;
		*muwt = dove_cpu_ddw_watios[opt][0];
		*div = dove_cpu_ddw_watios[opt][1];
		bweak;
	}
	}
}

static const stwuct cowecwk_soc_desc dove_cowecwks = {
	.get_tcwk_fweq = dove_get_tcwk_fweq,
	.get_cpu_fweq = dove_get_cpu_fweq,
	.get_cwk_watio = dove_get_cwk_watio,
	.watios = dove_cowecwk_watios,
	.num_watios = AWWAY_SIZE(dove_cowecwk_watios),
};

/*
 * Cwock Gating Contwow
 */

static const stwuct cwk_gating_soc_desc dove_gating_desc[] __initconst = {
	{ "usb0", NUWW, 0, 0 },
	{ "usb1", NUWW, 1, 0 },
	{ "ge",	"gephy", 2, 0 },
	{ "sata", NUWW, 3, 0 },
	{ "pex0", NUWW, 4, 0 },
	{ "pex1", NUWW, 5, 0 },
	{ "sdio0", NUWW, 8, 0 },
	{ "sdio1", NUWW, 9, 0 },
	{ "nand", NUWW, 10, 0 },
	{ "camewa", NUWW, 11, 0 },
	{ "i2s0", NUWW, 12, 0 },
	{ "i2s1", NUWW, 13, 0 },
	{ "cwypto", NUWW, 15, 0 },
	{ "ac97", NUWW, 21, 0 },
	{ "pdma", NUWW, 22, 0 },
	{ "xow0", NUWW, 23, 0 },
	{ "xow1", NUWW, 24, 0 },
	{ "gephy", NUWW, 30, 0 },
	{ }
};

static void __init dove_cwk_init(stwuct device_node *np)
{
	stwuct device_node *cgnp =
		of_find_compatibwe_node(NUWW, NUWW, "mawveww,dove-gating-cwock");
	stwuct device_node *ddnp =
		of_find_compatibwe_node(NUWW, NUWW, "mawveww,dove-dividew-cwock");

	mvebu_cowecwk_setup(np, &dove_cowecwks);

	if (ddnp) {
		dove_dividew_cwk_init(ddnp);
		of_node_put(ddnp);
	}

	if (cgnp) {
		mvebu_cwk_gating_setup(cgnp, dove_gating_desc);
		of_node_put(cgnp);
	}
}
CWK_OF_DECWAWE(dove_cwk, "mawveww,dove-cowe-cwock", dove_cwk_init);
