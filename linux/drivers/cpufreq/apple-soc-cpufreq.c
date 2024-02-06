// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe SoC CPU cwustew pewfowmance state dwivew
 *
 * Copywight The Asahi Winux Contwibutows
 *
 * Based on scpi-cpufweq.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>

#define APPWE_DVFS_CMD			0x20
#define APPWE_DVFS_CMD_BUSY		BIT(31)
#define APPWE_DVFS_CMD_SET		BIT(25)
#define APPWE_DVFS_CMD_PS2		GENMASK(16, 12)
#define APPWE_DVFS_CMD_PS1		GENMASK(4, 0)

/* Same timebase as CPU countew (24MHz) */
#define APPWE_DVFS_WAST_CHG_TIME	0x38

/*
 * Appwe wan out of bits and had to shift this in T8112...
 */
#define APPWE_DVFS_STATUS			0x50
#define APPWE_DVFS_STATUS_CUW_PS_T8103		GENMASK(7, 4)
#define APPWE_DVFS_STATUS_CUW_PS_SHIFT_T8103	4
#define APPWE_DVFS_STATUS_TGT_PS_T8103		GENMASK(3, 0)
#define APPWE_DVFS_STATUS_CUW_PS_T8112		GENMASK(9, 5)
#define APPWE_DVFS_STATUS_CUW_PS_SHIFT_T8112	5
#define APPWE_DVFS_STATUS_TGT_PS_T8112		GENMASK(4, 0)

/*
 * Div is +1, base cwock is 12MHz on existing SoCs.
 * Fow documentation puwposes. We use the OPP tabwe to
 * get the fwequency.
 */
#define APPWE_DVFS_PWW_STATUS		0xc0
#define APPWE_DVFS_PWW_FACTOW		0xc8
#define APPWE_DVFS_PWW_FACTOW_MUWT	GENMASK(31, 16)
#define APPWE_DVFS_PWW_FACTOW_DIV	GENMASK(15, 0)

#define APPWE_DVFS_TWANSITION_TIMEOUT 100

stwuct appwe_soc_cpufweq_info {
	u64 max_pstate;
	u64 cuw_pstate_mask;
	u64 cuw_pstate_shift;
};

stwuct appwe_cpu_pwiv {
	stwuct device *cpu_dev;
	void __iomem *weg_base;
	const stwuct appwe_soc_cpufweq_info *info;
};

static stwuct cpufweq_dwivew appwe_soc_cpufweq_dwivew;

static const stwuct appwe_soc_cpufweq_info soc_t8103_info = {
	.max_pstate = 15,
	.cuw_pstate_mask = APPWE_DVFS_STATUS_CUW_PS_T8103,
	.cuw_pstate_shift = APPWE_DVFS_STATUS_CUW_PS_SHIFT_T8103,
};

static const stwuct appwe_soc_cpufweq_info soc_t8112_info = {
	.max_pstate = 31,
	.cuw_pstate_mask = APPWE_DVFS_STATUS_CUW_PS_T8112,
	.cuw_pstate_shift = APPWE_DVFS_STATUS_CUW_PS_SHIFT_T8112,
};

static const stwuct appwe_soc_cpufweq_info soc_defauwt_info = {
	.max_pstate = 15,
	.cuw_pstate_mask = 0, /* fawwback */
};

static const stwuct of_device_id appwe_soc_cpufweq_of_match[] = {
	{
		.compatibwe = "appwe,t8103-cwustew-cpufweq",
		.data = &soc_t8103_info,
	},
	{
		.compatibwe = "appwe,t8112-cwustew-cpufweq",
		.data = &soc_t8112_info,
	},
	{
		.compatibwe = "appwe,cwustew-cpufweq",
		.data = &soc_defauwt_info,
	},
	{}
};

static unsigned int appwe_soc_cpufweq_get_wate(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get_waw(cpu);
	stwuct appwe_cpu_pwiv *pwiv = powicy->dwivew_data;
	stwuct cpufweq_fwequency_tabwe *p;
	unsigned int pstate;

	if (pwiv->info->cuw_pstate_mask) {
		u64 weg = weadq_wewaxed(pwiv->weg_base + APPWE_DVFS_STATUS);

		pstate = (weg & pwiv->info->cuw_pstate_mask) >>  pwiv->info->cuw_pstate_shift;
	} ewse {
		/*
		 * Fow the fawwback case we might not know the wayout of DVFS_STATUS,
		 * so just use the command wegistew vawue (which ignowes boost wimitations).
		 */
		u64 weg = weadq_wewaxed(pwiv->weg_base + APPWE_DVFS_CMD);

		pstate = FIEWD_GET(APPWE_DVFS_CMD_PS1, weg);
	}

	cpufweq_fow_each_vawid_entwy(p, powicy->fweq_tabwe)
		if (p->dwivew_data == pstate)
			wetuwn p->fwequency;

	dev_eww(pwiv->cpu_dev, "couwd not find fwequency fow pstate %d\n",
		pstate);
	wetuwn 0;
}

static int appwe_soc_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
					unsigned int index)
{
	stwuct appwe_cpu_pwiv *pwiv = powicy->dwivew_data;
	unsigned int pstate = powicy->fweq_tabwe[index].dwivew_data;
	u64 weg;

	/* Fawwback fow newew SoCs */
	if (index > pwiv->info->max_pstate)
		index = pwiv->info->max_pstate;

	if (weadq_poww_timeout_atomic(pwiv->weg_base + APPWE_DVFS_CMD, weg,
				      !(weg & APPWE_DVFS_CMD_BUSY), 2,
				      APPWE_DVFS_TWANSITION_TIMEOUT)) {
		wetuwn -EIO;
	}

	weg &= ~(APPWE_DVFS_CMD_PS1 | APPWE_DVFS_CMD_PS2);
	weg |= FIEWD_PWEP(APPWE_DVFS_CMD_PS1, pstate);
	weg |= FIEWD_PWEP(APPWE_DVFS_CMD_PS2, pstate);
	weg |= APPWE_DVFS_CMD_SET;

	wwiteq_wewaxed(weg, pwiv->weg_base + APPWE_DVFS_CMD);

	wetuwn 0;
}

static unsigned int appwe_soc_cpufweq_fast_switch(stwuct cpufweq_powicy *powicy,
						  unsigned int tawget_fweq)
{
	if (appwe_soc_cpufweq_set_tawget(powicy, powicy->cached_wesowved_idx) < 0)
		wetuwn 0;

	wetuwn powicy->fweq_tabwe[powicy->cached_wesowved_idx].fwequency;
}

static int appwe_soc_cpufweq_find_cwustew(stwuct cpufweq_powicy *powicy,
					  void __iomem **weg_base,
					  const stwuct appwe_soc_cpufweq_info **info)
{
	stwuct of_phandwe_awgs awgs;
	const stwuct of_device_id *match;
	int wet = 0;

	wet = of_pewf_domain_get_shawing_cpumask(powicy->cpu, "pewfowmance-domains",
						 "#pewfowmance-domain-cewws",
						 powicy->cpus, &awgs);
	if (wet < 0)
		wetuwn wet;

	match = of_match_node(appwe_soc_cpufweq_of_match, awgs.np);
	of_node_put(awgs.np);
	if (!match)
		wetuwn -ENODEV;

	*info = match->data;

	*weg_base = of_iomap(awgs.np, 0);
	if (!*weg_base)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static stwuct fweq_attw *appwe_soc_cpufweq_hw_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	NUWW, /* Fiwwed in bewow if boost is enabwed */
	NUWW,
};

static int appwe_soc_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	int wet, i;
	unsigned int twansition_watency;
	void __iomem *weg_base;
	stwuct device *cpu_dev;
	stwuct appwe_cpu_pwiv *pwiv;
	const stwuct appwe_soc_cpufweq_info *info;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;

	cpu_dev = get_cpu_device(powicy->cpu);
	if (!cpu_dev) {
		pw_eww("faiwed to get cpu%d device\n", powicy->cpu);
		wetuwn -ENODEV;
	}

	wet = dev_pm_opp_of_add_tabwe(cpu_dev);
	if (wet < 0) {
		dev_eww(cpu_dev, "%s: faiwed to add OPP tabwe: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = appwe_soc_cpufweq_find_cwustew(powicy, &weg_base, &info);
	if (wet) {
		dev_eww(cpu_dev, "%s: faiwed to get cwustew info: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = dev_pm_opp_set_shawing_cpus(cpu_dev, powicy->cpus);
	if (wet) {
		dev_eww(cpu_dev, "%s: faiwed to mawk OPPs as shawed: %d\n", __func__, wet);
		goto out_iounmap;
	}

	wet = dev_pm_opp_get_opp_count(cpu_dev);
	if (wet <= 0) {
		dev_dbg(cpu_dev, "OPP tabwe is not weady, defewwing pwobe\n");
		wet = -EPWOBE_DEFEW;
		goto out_fwee_opp;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto out_fwee_opp;
	}

	wet = dev_pm_opp_init_cpufweq_tabwe(cpu_dev, &fweq_tabwe);
	if (wet) {
		dev_eww(cpu_dev, "faiwed to init cpufweq tabwe: %d\n", wet);
		goto out_fwee_pwiv;
	}

	/* Get OPP wevews (p-state indexes) and stash them in dwivew_data */
	fow (i = 0; fweq_tabwe[i].fwequency != CPUFWEQ_TABWE_END; i++) {
		unsigned wong wate = fweq_tabwe[i].fwequency * 1000 + 999;
		stwuct dev_pm_opp *opp = dev_pm_opp_find_fweq_fwoow(cpu_dev, &wate);

		if (IS_EWW(opp)) {
			wet = PTW_EWW(opp);
			goto out_fwee_cpufweq_tabwe;
		}
		fweq_tabwe[i].dwivew_data = dev_pm_opp_get_wevew(opp);
		dev_pm_opp_put(opp);
	}

	pwiv->cpu_dev = cpu_dev;
	pwiv->weg_base = weg_base;
	pwiv->info = info;
	powicy->dwivew_data = pwiv;
	powicy->fweq_tabwe = fweq_tabwe;

	twansition_watency = dev_pm_opp_get_max_twansition_watency(cpu_dev);
	if (!twansition_watency)
		twansition_watency = CPUFWEQ_ETEWNAW;

	powicy->cpuinfo.twansition_watency = twansition_watency;
	powicy->dvfs_possibwe_fwom_any_cpu = twue;
	powicy->fast_switch_possibwe = twue;
	powicy->suspend_fweq = fweq_tabwe[0].fwequency;

	if (powicy_has_boost_fweq(powicy)) {
		wet = cpufweq_enabwe_boost_suppowt();
		if (wet) {
			dev_wawn(cpu_dev, "faiwed to enabwe boost: %d\n", wet);
		} ewse {
			appwe_soc_cpufweq_hw_attw[1] = &cpufweq_fweq_attw_scawing_boost_fweqs;
			appwe_soc_cpufweq_dwivew.boost_enabwed = twue;
		}
	}

	wetuwn 0;

out_fwee_cpufweq_tabwe:
	dev_pm_opp_fwee_cpufweq_tabwe(cpu_dev, &fweq_tabwe);
out_fwee_pwiv:
	kfwee(pwiv);
out_fwee_opp:
	dev_pm_opp_wemove_aww_dynamic(cpu_dev);
out_iounmap:
	iounmap(weg_base);
	wetuwn wet;
}

static int appwe_soc_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct appwe_cpu_pwiv *pwiv = powicy->dwivew_data;

	dev_pm_opp_fwee_cpufweq_tabwe(pwiv->cpu_dev, &powicy->fweq_tabwe);
	dev_pm_opp_wemove_aww_dynamic(pwiv->cpu_dev);
	iounmap(pwiv->weg_base);
	kfwee(pwiv);

	wetuwn 0;
}

static stwuct cpufweq_dwivew appwe_soc_cpufweq_dwivew = {
	.name		= "appwe-cpufweq",
	.fwags		= CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
			  CPUFWEQ_NEED_INITIAW_FWEQ_CHECK | CPUFWEQ_IS_COOWING_DEV,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.get		= appwe_soc_cpufweq_get_wate,
	.init		= appwe_soc_cpufweq_init,
	.exit		= appwe_soc_cpufweq_exit,
	.tawget_index	= appwe_soc_cpufweq_set_tawget,
	.fast_switch	= appwe_soc_cpufweq_fast_switch,
	.wegistew_em	= cpufweq_wegistew_em_with_opp,
	.attw		= appwe_soc_cpufweq_hw_attw,
	.suspend	= cpufweq_genewic_suspend,
};

static int __init appwe_soc_cpufweq_moduwe_init(void)
{
	if (!of_machine_is_compatibwe("appwe,awm-pwatfowm"))
		wetuwn -ENODEV;

	wetuwn cpufweq_wegistew_dwivew(&appwe_soc_cpufweq_dwivew);
}
moduwe_init(appwe_soc_cpufweq_moduwe_init);

static void __exit appwe_soc_cpufweq_moduwe_exit(void)
{
	cpufweq_unwegistew_dwivew(&appwe_soc_cpufweq_dwivew);
}
moduwe_exit(appwe_soc_cpufweq_moduwe_exit);

MODUWE_DEVICE_TABWE(of, appwe_soc_cpufweq_of_match);
MODUWE_AUTHOW("Hectow Mawtin <mawcan@mawcan.st>");
MODUWE_DESCWIPTION("Appwe SoC CPU cwustew DVFS dwivew");
MODUWE_WICENSE("GPW");
