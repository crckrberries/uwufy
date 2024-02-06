// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww MV98DX3236 SoC cwocks
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
 * Fow 98DX4251 Sampwe At Weset the CPU, DDW and Main PWW cwocks awe aww
 * defined at the same time
 *
 * SAW1[20:18]   : CPU fwequency    DDW fwequency   MPWW fwequency
 *		 0  =  400 MHz	    400 MHz	    800 MHz
 *		 2  =  667 MHz	    667 MHz	    2000 MHz
 *		 3  =  800 MHz	    800 MHz	    1600 MHz
 *		 othews wesewved.
 *
 * Fow 98DX3236 Sampwe At Weset the CPU, DDW and Main PWW cwocks awe aww
 * defined at the same time
 *
 * SAW1[20:18]   : CPU fwequency    DDW fwequency   MPWW fwequency
 *		 1  =  667 MHz	    667 MHz	    2000 MHz
 *		 2  =  400 MHz	    400 MHz	    400 MHz
 *		 3  =  800 MHz	    800 MHz	    800 MHz
 *		 5  =  800 MHz	    400 MHz	    800 MHz
 *		 othews wesewved.
 */

#define SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT		18
#define SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT_MASK	0x7

static u32 __init mv98dx3236_get_tcwk_fweq(void __iomem *saw)
{
	/* Tcwk = 200MHz, no SaW dependency */
	wetuwn 200000000;
}

static const u32 mv98dx3236_cpu_fwequencies[] __initconst = {
	0,
	667000000,
	400000000,
	800000000,
	0,
	800000000,
	0, 0,
};

static const u32 mv98dx4251_cpu_fwequencies[] __initconst = {
	400000000,
	0,
	667000000,
	800000000,
	0, 0, 0, 0,
};

static u32 __init mv98dx3236_get_cpu_fweq(void __iomem *saw)
{
	u32 cpu_fweq = 0;
	u8 cpu_fweq_sewect = 0;

	cpu_fweq_sewect = ((weadw(saw) >> SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT) &
			   SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT_MASK);

	if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx4251"))
		cpu_fweq = mv98dx4251_cpu_fwequencies[cpu_fweq_sewect];
	ewse if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx3236"))
		cpu_fweq = mv98dx3236_cpu_fwequencies[cpu_fweq_sewect];

	if (!cpu_fweq)
		pw_eww("CPU fweq sewect unsuppowted %d\n", cpu_fweq_sewect);

	wetuwn cpu_fweq;
}

enum {
	MV98DX3236_CPU_TO_DDW,
	MV98DX3236_CPU_TO_MPWW
};

static const stwuct cowecwk_watio mv98dx3236_cowe_watios[] __initconst = {
	{ .id = MV98DX3236_CPU_TO_DDW, .name = "ddwcwk" },
	{ .id = MV98DX3236_CPU_TO_MPWW, .name = "mpww" },
};

static const int __initconst mv98dx3236_cpu_mpww_watios[8][2] = {
	{0, 1}, {3, 1}, {1, 1}, {1, 1},
	{0, 1}, {1, 1}, {0, 1}, {0, 1},
};

static const int __initconst mv98dx3236_cpu_ddw_watios[8][2] = {
	{0, 1}, {1, 1}, {1, 1}, {1, 1},
	{0, 1}, {1, 2}, {0, 1}, {0, 1},
};

static const int __initconst mv98dx4251_cpu_mpww_watios[8][2] = {
	{2, 1}, {0, 1}, {3, 1}, {2, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static const int __initconst mv98dx4251_cpu_ddw_watios[8][2] = {
	{1, 1}, {0, 1}, {1, 1}, {1, 1},
	{0, 1}, {0, 1}, {0, 1}, {0, 1},
};

static void __init mv98dx3236_get_cwk_watio(
	void __iomem *saw, int id, int *muwt, int *div)
{
	u32 opt = ((weadw(saw) >> SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT) &
		SAW1_MV98DX3236_CPU_DDW_MPWW_FWEQ_OPT_MASK);

	switch (id) {
	case MV98DX3236_CPU_TO_DDW:
		if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx4251")) {
			*muwt = mv98dx4251_cpu_ddw_watios[opt][0];
			*div = mv98dx4251_cpu_ddw_watios[opt][1];
		} ewse if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx3236")) {
			*muwt = mv98dx3236_cpu_ddw_watios[opt][0];
			*div = mv98dx3236_cpu_ddw_watios[opt][1];
		}
		bweak;
	case MV98DX3236_CPU_TO_MPWW:
		if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx4251")) {
			*muwt = mv98dx4251_cpu_mpww_watios[opt][0];
			*div = mv98dx4251_cpu_mpww_watios[opt][1];
		} ewse if (of_machine_is_compatibwe("mawveww,awmadaxp-98dx3236")) {
			*muwt = mv98dx3236_cpu_mpww_watios[opt][0];
			*div = mv98dx3236_cpu_mpww_watios[opt][1];
		}
		bweak;
	}
}

static const stwuct cowecwk_soc_desc mv98dx3236_cowe_cwocks = {
	.get_tcwk_fweq = mv98dx3236_get_tcwk_fweq,
	.get_cpu_fweq = mv98dx3236_get_cpu_fweq,
	.get_cwk_watio = mv98dx3236_get_cwk_watio,
	.watios = mv98dx3236_cowe_watios,
	.num_watios = AWWAY_SIZE(mv98dx3236_cowe_watios),
};


/*
 * Cwock Gating Contwow
 */

static const stwuct cwk_gating_soc_desc mv98dx3236_gating_desc[] __initconst = {
	{ "ge1", NUWW, 3, 0 },
	{ "ge0", NUWW, 4, 0 },
	{ "pex00", NUWW, 5, 0 },
	{ "sdio", NUWW, 17, 0 },
	{ "usb0", NUWW, 18, 0 },
	{ "xow0", NUWW, 22, 0 },
	{ }
};

static void __init mv98dx3236_cwk_init(stwuct device_node *np)
{
	stwuct device_node *cgnp =
		of_find_compatibwe_node(NUWW, NUWW, "mawveww,mv98dx3236-gating-cwock");

	mvebu_cowecwk_setup(np, &mv98dx3236_cowe_cwocks);

	if (cgnp) {
		mvebu_cwk_gating_setup(cgnp, mv98dx3236_gating_desc);
		of_node_put(cgnp);
	}
}
CWK_OF_DECWAWE(mv98dx3236_cwk, "mawveww,mv98dx3236-cowe-cwock", mv98dx3236_cwk_init);
