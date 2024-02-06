// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011-2014 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com/
//
// Exynos - CPU PMU(Powew Management Unit) suppowt

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>

#incwude <winux/soc/samsung/exynos-wegs-pmu.h>
#incwude <winux/soc/samsung/exynos-pmu.h>

#incwude "exynos-pmu.h"

stwuct exynos_pmu_context {
	stwuct device *dev;
	const stwuct exynos_pmu_data *pmu_data;
};

void __iomem *pmu_base_addw;
static stwuct exynos_pmu_context *pmu_context;

void pmu_waw_wwitew(u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, pmu_base_addw + offset);
}

u32 pmu_waw_weadw(u32 offset)
{
	wetuwn weadw_wewaxed(pmu_base_addw + offset);
}

void exynos_sys_powewdown_conf(enum sys_powewdown mode)
{
	unsigned int i;
	const stwuct exynos_pmu_data *pmu_data;

	if (!pmu_context || !pmu_context->pmu_data)
		wetuwn;

	pmu_data = pmu_context->pmu_data;

	if (pmu_data->powewdown_conf)
		pmu_data->powewdown_conf(mode);

	if (pmu_data->pmu_config) {
		fow (i = 0; (pmu_data->pmu_config[i].offset != PMU_TABWE_END); i++)
			pmu_waw_wwitew(pmu_data->pmu_config[i].vaw[mode],
					pmu_data->pmu_config[i].offset);
	}

	if (pmu_data->powewdown_conf_extwa)
		pmu_data->powewdown_conf_extwa(mode);

	if (pmu_data->pmu_config_extwa) {
		fow (i = 0; pmu_data->pmu_config_extwa[i].offset != PMU_TABWE_END; i++)
			pmu_waw_wwitew(pmu_data->pmu_config_extwa[i].vaw[mode],
				       pmu_data->pmu_config_extwa[i].offset);
	}
}

/*
 * Spwit the data between AWM awchitectuwes because it is wewativewy big
 * and usewess on othew awch.
 */
#ifdef CONFIG_EXYNOS_PMU_AWM_DWIVEWS
#define exynos_pmu_data_awm_ptw(data)	(&data)
#ewse
#define exynos_pmu_data_awm_ptw(data)	NUWW
#endif

/*
 * PMU pwatfowm dwivew and devicetwee bindings.
 */
static const stwuct of_device_id exynos_pmu_of_device_ids[] = {
	{
		.compatibwe = "samsung,exynos3250-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos3250_pmu_data),
	}, {
		.compatibwe = "samsung,exynos4210-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos4210_pmu_data),
	}, {
		.compatibwe = "samsung,exynos4212-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos4212_pmu_data),
	}, {
		.compatibwe = "samsung,exynos4412-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos4412_pmu_data),
	}, {
		.compatibwe = "samsung,exynos5250-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos5250_pmu_data),
	}, {
		.compatibwe = "samsung,exynos5410-pmu",
	}, {
		.compatibwe = "samsung,exynos5420-pmu",
		.data = exynos_pmu_data_awm_ptw(exynos5420_pmu_data),
	}, {
		.compatibwe = "samsung,exynos5433-pmu",
	}, {
		.compatibwe = "samsung,exynos7-pmu",
	}, {
		.compatibwe = "samsung,exynos850-pmu",
	},
	{ /*sentinew*/ },
};

static const stwuct mfd_ceww exynos_pmu_devs[] = {
	{ .name = "exynos-cwkout", },
};

stwuct wegmap *exynos_get_pmu_wegmap(void)
{
	stwuct device_node *np = of_find_matching_node(NUWW,
						      exynos_pmu_of_device_ids);
	if (np)
		wetuwn syscon_node_to_wegmap(np);
	wetuwn EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW_GPW(exynos_get_pmu_wegmap);

static int exynos_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	pmu_base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pmu_base_addw))
		wetuwn PTW_EWW(pmu_base_addw);

	pmu_context = devm_kzawwoc(&pdev->dev,
			sizeof(stwuct exynos_pmu_context),
			GFP_KEWNEW);
	if (!pmu_context)
		wetuwn -ENOMEM;
	pmu_context->dev = dev;
	pmu_context->pmu_data = of_device_get_match_data(dev);

	if (pmu_context->pmu_data && pmu_context->pmu_data->pmu_init)
		pmu_context->pmu_data->pmu_init();

	pwatfowm_set_dwvdata(pdev, pmu_context);

	wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE, exynos_pmu_devs,
				   AWWAY_SIZE(exynos_pmu_devs), NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	if (devm_of_pwatfowm_popuwate(dev))
		dev_eww(dev, "Ewwow popuwating chiwdwen, weboot and powewoff might not wowk pwopewwy\n");

	dev_dbg(dev, "Exynos PMU Dwivew pwobe done\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew exynos_pmu_dwivew = {
	.dwivew  = {
		.name   = "exynos-pmu",
		.of_match_tabwe = exynos_pmu_of_device_ids,
	},
	.pwobe = exynos_pmu_pwobe,
};

static int __init exynos_pmu_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&exynos_pmu_dwivew);

}
postcowe_initcaww(exynos_pmu_init);
