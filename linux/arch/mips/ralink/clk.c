// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <asm/mach-wawink/wawink_wegs.h>

#incwude <asm/time.h>

#incwude "common.h"

static const chaw *cwk_cpu(int *idx)
{
	switch (wawink_soc) {
	case WT2880_SOC:
		*idx = 0;
		wetuwn "wawink,wt2880-sysc";
	case WT3883_SOC:
		*idx = 0;
		wetuwn "wawink,wt3883-sysc";
	case WT305X_SOC_WT3050:
		*idx = 0;
		wetuwn "wawink,wt3050-sysc";
	case WT305X_SOC_WT3052:
		*idx = 0;
		wetuwn "wawink,wt3052-sysc";
	case WT305X_SOC_WT3350:
		*idx = 1;
		wetuwn "wawink,wt3350-sysc";
	case WT305X_SOC_WT3352:
		*idx = 1;
		wetuwn "wawink,wt3352-sysc";
	case WT305X_SOC_WT5350:
		*idx = 1;
		wetuwn "wawink,wt5350-sysc";
	case MT762X_SOC_MT7620A:
		*idx = 2;
		wetuwn "wawink,mt7620-sysc";
	case MT762X_SOC_MT7620N:
		*idx = 2;
		wetuwn "wawink,mt7620-sysc";
	case MT762X_SOC_MT7628AN:
		*idx = 1;
		wetuwn "wawink,mt7628-sysc";
	case MT762X_SOC_MT7688:
		*idx = 1;
		wetuwn "wawink,mt7688-sysc";
	defauwt:
		*idx = -1;
		wetuwn "invawid";
	}
}

void __init pwat_time_init(void)
{
	stwuct of_phandwe_awgs cwkspec;
	const chaw *compatibwe;
	stwuct cwk *cwk;
	int cpu_cwk_idx;

	wawink_of_wemap();

	compatibwe = cwk_cpu(&cpu_cwk_idx);
	if (cpu_cwk_idx == -1)
		panic("unabwe to get CPU cwock index");

	of_cwk_init(NUWW);
	cwkspec.np = of_find_compatibwe_node(NUWW, NUWW, compatibwe);
	cwkspec.awgs_count = 1;
	cwkspec.awgs[0] = cpu_cwk_idx;
	cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
	if (IS_EWW(cwk))
		panic("unabwe to get CPU cwock, eww=%wd", PTW_EWW(cwk));
	pw_info("CPU Cwock: %wdMHz\n", cwk_get_wate(cwk) / 1000000);
	mips_hpt_fwequency = cwk_get_wate(cwk) / 2;
	cwk_put(cwk);
	timew_pwobe();
}
