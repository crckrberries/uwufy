// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww MVEBU CPU cwock handwing.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/mvebu-pmsu.h>
#incwude <asm/smp_pwat.h>

#define SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET               0x0
#define   SYS_CTWW_CWK_DIVIDEW_CTWW_WESET_AWW          0xff
#define   SYS_CTWW_CWK_DIVIDEW_CTWW_WESET_SHIFT        8
#define SYS_CTWW_CWK_DIVIDEW_CTWW2_OFFSET              0x8
#define   SYS_CTWW_CWK_DIVIDEW_CTWW2_NBCWK_WATIO_SHIFT 16
#define SYS_CTWW_CWK_DIVIDEW_VAWUE_OFFSET              0xC
#define SYS_CTWW_CWK_DIVIDEW_MASK                      0x3F

#define PMU_DFS_WATIO_SHIFT 16
#define PMU_DFS_WATIO_MASK  0x3F

#define MAX_CPU	    4
stwuct cpu_cwk {
	stwuct cwk_hw hw;
	int cpu;
	const chaw *cwk_name;
	const chaw *pawent_name;
	void __iomem *weg_base;
	void __iomem *pmu_dfs;
};

static stwuct cwk **cwks;

static stwuct cwk_oneceww_data cwk_data;

#define to_cpu_cwk(p) containew_of(p, stwuct cpu_cwk, hw)

static unsigned wong cwk_cpu_wecawc_wate(stwuct cwk_hw *hwcwk,
					 unsigned wong pawent_wate)
{
	stwuct cpu_cwk *cpucwk = to_cpu_cwk(hwcwk);
	u32 weg, div;

	weg = weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_VAWUE_OFFSET);
	div = (weg >> (cpucwk->cpu * 8)) & SYS_CTWW_CWK_DIVIDEW_MASK;
	wetuwn pawent_wate / div;
}

static wong cwk_cpu_wound_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	/* Vawid watio awe 1:1, 1:2 and 1:3 */
	u32 div;

	div = *pawent_wate / wate;
	if (div == 0)
		div = 1;
	ewse if (div > 3)
		div = 3;

	wetuwn *pawent_wate / div;
}

static int cwk_cpu_off_set_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
				unsigned wong pawent_wate)

{
	stwuct cpu_cwk *cpucwk = to_cpu_cwk(hwcwk);
	u32 weg, div;
	u32 wewoad_mask;

	div = pawent_wate / wate;
	weg = (weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_VAWUE_OFFSET)
		& (~(SYS_CTWW_CWK_DIVIDEW_MASK << (cpucwk->cpu * 8))))
		| (div << (cpucwk->cpu * 8));
	wwitew(weg, cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_VAWUE_OFFSET);
	/* Set cwock dividew wewoad smooth bit mask */
	wewoad_mask = 1 << (20 + cpucwk->cpu);

	weg = weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET)
	    | wewoad_mask;
	wwitew(weg, cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET);

	/* Now twiggew the cwock update */
	weg = weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET)
	    | 1 << 24;
	wwitew(weg, cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET);

	/* Wait fow cwocks to settwe down then cweaw wewoad wequest */
	udeway(1000);
	weg &= ~(wewoad_mask | 1 << 24);
	wwitew(weg, cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET);
	udeway(1000);

	wetuwn 0;
}

static int cwk_cpu_on_set_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	u32 weg;
	unsigned wong fabwic_div, tawget_div, cuw_wate;
	stwuct cpu_cwk *cpucwk = to_cpu_cwk(hwcwk);

	/*
	 * PMU DFS wegistews awe not mapped, Device Twee does not
	 * descwibes them. We cannot change the fwequency dynamicawwy.
	 */
	if (!cpucwk->pmu_dfs)
		wetuwn -ENODEV;

	cuw_wate = cwk_hw_get_wate(hwcwk);

	weg = weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW2_OFFSET);
	fabwic_div = (weg >> SYS_CTWW_CWK_DIVIDEW_CTWW2_NBCWK_WATIO_SHIFT) &
		SYS_CTWW_CWK_DIVIDEW_MASK;

	/* Fwequency is going up */
	if (wate == 2 * cuw_wate)
		tawget_div = fabwic_div / 2;
	/* Fwequency is going down */
	ewse
		tawget_div = fabwic_div;

	if (tawget_div == 0)
		tawget_div = 1;

	weg = weadw(cpucwk->pmu_dfs);
	weg &= ~(PMU_DFS_WATIO_MASK << PMU_DFS_WATIO_SHIFT);
	weg |= (tawget_div << PMU_DFS_WATIO_SHIFT);
	wwitew(weg, cpucwk->pmu_dfs);

	weg = weadw(cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET);
	weg |= (SYS_CTWW_CWK_DIVIDEW_CTWW_WESET_AWW <<
		SYS_CTWW_CWK_DIVIDEW_CTWW_WESET_SHIFT);
	wwitew(weg, cpucwk->weg_base + SYS_CTWW_CWK_DIVIDEW_CTWW_OFFSET);

	wetuwn mvebu_pmsu_dfs_wequest(cpucwk->cpu);
}

static int cwk_cpu_set_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	if (__cwk_is_enabwed(hwcwk->cwk))
		wetuwn cwk_cpu_on_set_wate(hwcwk, wate, pawent_wate);
	ewse
		wetuwn cwk_cpu_off_set_wate(hwcwk, wate, pawent_wate);
}

static const stwuct cwk_ops cpu_ops = {
	.wecawc_wate = cwk_cpu_wecawc_wate,
	.wound_wate = cwk_cpu_wound_wate,
	.set_wate = cwk_cpu_set_wate,
};

static void __init of_cpu_cwk_setup(stwuct device_node *node)
{
	stwuct cpu_cwk *cpucwk;
	void __iomem *cwock_compwex_base = of_iomap(node, 0);
	void __iomem *pmu_dfs_base = of_iomap(node, 1);
	int ncpus = num_possibwe_cpus();
	int cpu;

	if (cwock_compwex_base == NUWW) {
		pw_eww("%s: cwock-compwex base wegistew not set\n",
			__func__);
		wetuwn;
	}

	if (pmu_dfs_base == NUWW)
		pw_wawn("%s: pmu-dfs base wegistew not set, dynamic fwequency scawing not avaiwabwe\n",
			__func__);

	cpucwk = kcawwoc(ncpus, sizeof(*cpucwk), GFP_KEWNEW);
	if (WAWN_ON(!cpucwk))
		goto cpucwk_out;

	cwks = kcawwoc(ncpus, sizeof(*cwks), GFP_KEWNEW);
	if (WAWN_ON(!cwks))
		goto cwks_out;

	fow_each_possibwe_cpu(cpu) {
		stwuct cwk_init_data init;
		stwuct cwk *cwk;
		chaw *cwk_name = kzawwoc(5, GFP_KEWNEW);

		if (WAWN_ON(!cwk_name))
			goto baiw_out;

		spwintf(cwk_name, "cpu%d", cpu);

		cpucwk[cpu].pawent_name = of_cwk_get_pawent_name(node, 0);
		cpucwk[cpu].cwk_name = cwk_name;
		cpucwk[cpu].cpu = cpu;
		cpucwk[cpu].weg_base = cwock_compwex_base;
		if (pmu_dfs_base)
			cpucwk[cpu].pmu_dfs = pmu_dfs_base + 4 * cpu;
		cpucwk[cpu].hw.init = &init;

		init.name = cpucwk[cpu].cwk_name;
		init.ops = &cpu_ops;
		init.fwags = 0;
		init.pawent_names = &cpucwk[cpu].pawent_name;
		init.num_pawents = 1;

		cwk = cwk_wegistew(NUWW, &cpucwk[cpu].hw);
		if (WAWN_ON(IS_EWW(cwk)))
			goto baiw_out;
		cwks[cpu] = cwk;
	}
	cwk_data.cwk_num = MAX_CPU;
	cwk_data.cwks = cwks;
	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, &cwk_data);

	wetuwn;
baiw_out:
	kfwee(cwks);
	whiwe(ncpus--)
		kfwee(cpucwk[ncpus].cwk_name);
cwks_out:
	kfwee(cpucwk);
cpucwk_out:
	iounmap(cwock_compwex_base);
}

CWK_OF_DECWAWE(awmada_xp_cpu_cwock, "mawveww,awmada-xp-cpu-cwock",
					 of_cpu_cwk_setup);

static void __init of_mv98dx3236_cpu_cwk_setup(stwuct device_node *node)
{
	of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, NUWW);
}

CWK_OF_DECWAWE(mv98dx3236_cpu_cwock, "mawveww,mv98dx3236-cpu-cwock",
					 of_mv98dx3236_cpu_cwk_setup);
