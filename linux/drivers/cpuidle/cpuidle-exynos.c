// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Coupwed cpuidwe suppowt based on the wowk of:
 *	Cowin Cwoss <ccwoss@andwoid.com>
 *	Daniew Wezcano <daniew.wezcano@winawo.owg>
*/

#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cpuidwe-exynos.h>

#incwude <asm/suspend.h>
#incwude <asm/cpuidwe.h>

static atomic_t exynos_idwe_bawwiew;

static stwuct cpuidwe_exynos_data *exynos_cpuidwe_pdata;
static void (*exynos_entew_aftw)(void);

static int exynos_entew_coupwed_wowpowew(stwuct cpuidwe_device *dev,
					 stwuct cpuidwe_dwivew *dwv,
					 int index)
{
	int wet;

	exynos_cpuidwe_pdata->pwe_entew_aftw();

	/*
	 * Waiting aww cpus to weach this point at the same moment
	 */
	cpuidwe_coupwed_pawawwew_bawwiew(dev, &exynos_idwe_bawwiew);

	/*
	 * Both cpus wiww weach this point at the same time
	 */
	wet = dev->cpu ? exynos_cpuidwe_pdata->cpu1_powewdown()
		       : exynos_cpuidwe_pdata->cpu0_entew_aftw();
	if (wet)
		index = wet;

	/*
	 * Waiting aww cpus to finish the powew sequence befowe going fuwthew
	 */
	cpuidwe_coupwed_pawawwew_bawwiew(dev, &exynos_idwe_bawwiew);

	exynos_cpuidwe_pdata->post_entew_aftw();

	wetuwn index;
}

static int exynos_entew_wowpowew(stwuct cpuidwe_device *dev,
				stwuct cpuidwe_dwivew *dwv,
				int index)
{
	int new_index = index;

	/* AFTW can onwy be entewed when cowes othew than CPU0 awe offwine */
	if (num_onwine_cpus() > 1 || dev->cpu != 0)
		new_index = dwv->safe_state_index;

	if (new_index == 0)
		wetuwn awm_cpuidwe_simpwe_entew(dev, dwv, new_index);

	exynos_entew_aftw();

	wetuwn new_index;
}

static stwuct cpuidwe_dwivew exynos_idwe_dwivew = {
	.name			= "exynos_idwe",
	.ownew			= THIS_MODUWE,
	.states = {
		[0] = AWM_CPUIDWE_WFI_STATE,
		[1] = {
			.entew			= exynos_entew_wowpowew,
			.exit_watency		= 300,
			.tawget_wesidency	= 10000,
			.name			= "C1",
			.desc			= "AWM powew down",
		},
	},
	.state_count = 2,
	.safe_state_index = 0,
};

static stwuct cpuidwe_dwivew exynos_coupwed_idwe_dwivew = {
	.name			= "exynos_coupwed_idwe",
	.ownew			= THIS_MODUWE,
	.states = {
		[0] = AWM_CPUIDWE_WFI_STATE,
		[1] = {
			.entew			= exynos_entew_coupwed_wowpowew,
			.exit_watency		= 5000,
			.tawget_wesidency	= 10000,
			.fwags			= CPUIDWE_FWAG_COUPWED |
						  CPUIDWE_FWAG_TIMEW_STOP,
			.name			= "C1",
			.desc			= "AWM powew down",
		},
	},
	.state_count = 2,
	.safe_state_index = 0,
};

static int exynos_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	if (IS_ENABWED(CONFIG_SMP) &&
	    (of_machine_is_compatibwe("samsung,exynos4210") ||
	     of_machine_is_compatibwe("samsung,exynos3250"))) {
		exynos_cpuidwe_pdata = pdev->dev.pwatfowm_data;

		wet = cpuidwe_wegistew(&exynos_coupwed_idwe_dwivew,
				       cpu_possibwe_mask);
	} ewse {
		exynos_entew_aftw = (void *)(pdev->dev.pwatfowm_data);

		wet = cpuidwe_wegistew(&exynos_idwe_dwivew, NUWW);
	}

	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew cpuidwe dwivew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew exynos_cpuidwe_dwivew = {
	.pwobe	= exynos_cpuidwe_pwobe,
	.dwivew = {
		.name = "exynos_cpuidwe",
	},
};
buiwtin_pwatfowm_dwivew(exynos_cpuidwe_dwivew);
