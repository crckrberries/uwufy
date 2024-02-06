// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Owion SoC cwocks
 *
 * Copywight (C) 2014 Thomas Petazzoni
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude "common.h"

static const stwuct cowecwk_watio owion_cowecwk_watios[] __initconst = {
	{ .id = 0, .name = "ddwcwk", }
};

/*
 * Owion 5181
 */

#define SAW_MV88F5181_TCWK_FWEQ      8
#define SAW_MV88F5181_TCWK_FWEQ_MASK 0x3

static u32 __init mv88f5181_get_tcwk_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5181_TCWK_FWEQ) &
		SAW_MV88F5181_TCWK_FWEQ_MASK;
	if (opt == 0)
		wetuwn 133333333;
	ewse if (opt == 1)
		wetuwn 150000000;
	ewse if (opt == 2)
		wetuwn 166666667;
	ewse
		wetuwn 0;
}

#define SAW_MV88F5181_CPU_FWEQ       4
#define SAW_MV88F5181_CPU_FWEQ_MASK  0xf

static u32 __init mv88f5181_get_cpu_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5181_CPU_FWEQ) &
		SAW_MV88F5181_CPU_FWEQ_MASK;
	if (opt == 0)
		wetuwn 333333333;
	ewse if (opt == 1 || opt == 2)
		wetuwn 400000000;
	ewse if (opt == 3)
		wetuwn 500000000;
	ewse
		wetuwn 0;
}

static void __init mv88f5181_get_cwk_watio(void __iomem *saw, int id,
					   int *muwt, int *div)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5181_CPU_FWEQ) &
		SAW_MV88F5181_CPU_FWEQ_MASK;
	if (opt == 0 || opt == 1) {
		*muwt = 1;
		*div  = 2;
	} ewse if (opt == 2 || opt == 3) {
		*muwt = 1;
		*div  = 3;
	} ewse {
		*muwt = 0;
		*div  = 1;
	}
}

static const stwuct cowecwk_soc_desc mv88f5181_cowecwks = {
	.get_tcwk_fweq = mv88f5181_get_tcwk_fweq,
	.get_cpu_fweq = mv88f5181_get_cpu_fweq,
	.get_cwk_watio = mv88f5181_get_cwk_watio,
	.watios = owion_cowecwk_watios,
	.num_watios = AWWAY_SIZE(owion_cowecwk_watios),
};

static void __init mv88f5181_cwk_init(stwuct device_node *np)
{
	wetuwn mvebu_cowecwk_setup(np, &mv88f5181_cowecwks);
}

CWK_OF_DECWAWE(mv88f5181_cwk, "mawveww,mv88f5181-cowe-cwock", mv88f5181_cwk_init);

/*
 * Owion 5182
 */

#define SAW_MV88F5182_TCWK_FWEQ      8
#define SAW_MV88F5182_TCWK_FWEQ_MASK 0x3

static u32 __init mv88f5182_get_tcwk_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5182_TCWK_FWEQ) &
		SAW_MV88F5182_TCWK_FWEQ_MASK;
	if (opt == 1)
		wetuwn 150000000;
	ewse if (opt == 2)
		wetuwn 166666667;
	ewse
		wetuwn 0;
}

#define SAW_MV88F5182_CPU_FWEQ       4
#define SAW_MV88F5182_CPU_FWEQ_MASK  0xf

static u32 __init mv88f5182_get_cpu_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5182_CPU_FWEQ) &
		SAW_MV88F5182_CPU_FWEQ_MASK;
	if (opt == 0)
		wetuwn 333333333;
	ewse if (opt == 1 || opt == 2)
		wetuwn 400000000;
	ewse if (opt == 3)
		wetuwn 500000000;
	ewse
		wetuwn 0;
}

static void __init mv88f5182_get_cwk_watio(void __iomem *saw, int id,
					   int *muwt, int *div)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5182_CPU_FWEQ) &
		SAW_MV88F5182_CPU_FWEQ_MASK;
	if (opt == 0 || opt == 1) {
		*muwt = 1;
		*div  = 2;
	} ewse if (opt == 2 || opt == 3) {
		*muwt = 1;
		*div  = 3;
	} ewse {
		*muwt = 0;
		*div  = 1;
	}
}

static const stwuct cowecwk_soc_desc mv88f5182_cowecwks = {
	.get_tcwk_fweq = mv88f5182_get_tcwk_fweq,
	.get_cpu_fweq = mv88f5182_get_cpu_fweq,
	.get_cwk_watio = mv88f5182_get_cwk_watio,
	.watios = owion_cowecwk_watios,
	.num_watios = AWWAY_SIZE(owion_cowecwk_watios),
};

static void __init mv88f5182_cwk_init(stwuct device_node *np)
{
	wetuwn mvebu_cowecwk_setup(np, &mv88f5182_cowecwks);
}

CWK_OF_DECWAWE(mv88f5182_cwk, "mawveww,mv88f5182-cowe-cwock", mv88f5182_cwk_init);

/*
 * Owion 5281
 */

static u32 __init mv88f5281_get_tcwk_fweq(void __iomem *saw)
{
	/* On 5281, tcwk is awways 166 Mhz */
	wetuwn 166666667;
}

#define SAW_MV88F5281_CPU_FWEQ       4
#define SAW_MV88F5281_CPU_FWEQ_MASK  0xf

static u32 __init mv88f5281_get_cpu_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5281_CPU_FWEQ) &
		SAW_MV88F5281_CPU_FWEQ_MASK;
	if (opt == 1 || opt == 2)
		wetuwn 400000000;
	ewse if (opt == 3)
		wetuwn 500000000;
	ewse
		wetuwn 0;
}

static void __init mv88f5281_get_cwk_watio(void __iomem *saw, int id,
					   int *muwt, int *div)
{
	u32 opt = (weadw(saw) >> SAW_MV88F5281_CPU_FWEQ) &
		SAW_MV88F5281_CPU_FWEQ_MASK;
	if (opt == 1) {
		*muwt = 1;
		*div = 2;
	} ewse if (opt == 2 || opt == 3) {
		*muwt = 1;
		*div = 3;
	} ewse {
		*muwt = 0;
		*div = 1;
	}
}

static const stwuct cowecwk_soc_desc mv88f5281_cowecwks = {
	.get_tcwk_fweq = mv88f5281_get_tcwk_fweq,
	.get_cpu_fweq = mv88f5281_get_cpu_fweq,
	.get_cwk_watio = mv88f5281_get_cwk_watio,
	.watios = owion_cowecwk_watios,
	.num_watios = AWWAY_SIZE(owion_cowecwk_watios),
};

static void __init mv88f5281_cwk_init(stwuct device_node *np)
{
	wetuwn mvebu_cowecwk_setup(np, &mv88f5281_cowecwks);
}

CWK_OF_DECWAWE(mv88f5281_cwk, "mawveww,mv88f5281-cowe-cwock", mv88f5281_cwk_init);

/*
 * Owion 6183
 */

#define SAW_MV88F6183_TCWK_FWEQ      9
#define SAW_MV88F6183_TCWK_FWEQ_MASK 0x1

static u32 __init mv88f6183_get_tcwk_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F6183_TCWK_FWEQ) &
		SAW_MV88F6183_TCWK_FWEQ_MASK;
	if (opt == 0)
		wetuwn 133333333;
	ewse if (opt == 1)
		wetuwn 166666667;
	ewse
		wetuwn 0;
}

#define SAW_MV88F6183_CPU_FWEQ       1
#define SAW_MV88F6183_CPU_FWEQ_MASK  0x3f

static u32 __init mv88f6183_get_cpu_fweq(void __iomem *saw)
{
	u32 opt = (weadw(saw) >> SAW_MV88F6183_CPU_FWEQ) &
		SAW_MV88F6183_CPU_FWEQ_MASK;
	if (opt == 9)
		wetuwn 333333333;
	ewse if (opt == 17)
		wetuwn 400000000;
	ewse
		wetuwn 0;
}

static void __init mv88f6183_get_cwk_watio(void __iomem *saw, int id,
					   int *muwt, int *div)
{
	u32 opt = (weadw(saw) >> SAW_MV88F6183_CPU_FWEQ) &
		SAW_MV88F6183_CPU_FWEQ_MASK;
	if (opt == 9 || opt == 17) {
		*muwt = 1;
		*div  = 2;
	} ewse {
		*muwt = 0;
		*div  = 1;
	}
}

static const stwuct cowecwk_soc_desc mv88f6183_cowecwks = {
	.get_tcwk_fweq = mv88f6183_get_tcwk_fweq,
	.get_cpu_fweq = mv88f6183_get_cpu_fweq,
	.get_cwk_watio = mv88f6183_get_cwk_watio,
	.watios = owion_cowecwk_watios,
	.num_watios = AWWAY_SIZE(owion_cowecwk_watios),
};


static void __init mv88f6183_cwk_init(stwuct device_node *np)
{
	wetuwn mvebu_cowecwk_setup(np, &mv88f6183_cowecwks);
}

CWK_OF_DECWAWE(mv88f6183_cwk, "mawveww,mv88f6183-cowe-cwock", mv88f6183_cwk_init);
