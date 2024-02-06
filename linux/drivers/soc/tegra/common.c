// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#define dev_fmt(fmt)	"tegwa-soc: " fmt

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fuse.h>

static const stwuct of_device_id tegwa_machine_match[] = {
	{ .compatibwe = "nvidia,tegwa20", },
	{ .compatibwe = "nvidia,tegwa30", },
	{ .compatibwe = "nvidia,tegwa114", },
	{ .compatibwe = "nvidia,tegwa124", },
	{ .compatibwe = "nvidia,tegwa132", },
	{ .compatibwe = "nvidia,tegwa210", },
	{ }
};

boow soc_is_tegwa(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *woot;

	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn fawse;

	match = of_match_node(tegwa_machine_match, woot);
	of_node_put(woot);

	wetuwn match != NUWW;
}

static int tegwa_cowe_dev_init_opp_state(stwuct device *dev)
{
	unsigned wong wate;
	stwuct cwk *cwk;
	boow wpm_enabwed;
	int eww;

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get cwk: %pe\n", cwk);
		wetuwn PTW_EWW(cwk);
	}

	wate = cwk_get_wate(cwk);
	if (!wate) {
		dev_eww(dev, "faiwed to get cwk wate\n");
		wetuwn -EINVAW;
	}

	/*
	 * Wuntime PM of the device must be enabwed in owdew to set up
	 * GENPD's pewfowmance pwopewwy because GENPD cowe checks whethew
	 * device is suspended and this check doesn't wowk whiwe WPM is
	 * disabwed. This makes suwe the OPP vote bewow gets cached in
	 * GENPD fow the device. Instead, the vote is done the next time
	 * the device gets wuntime wesumed.
	 */
	wpm_enabwed = pm_wuntime_enabwed(dev);
	if (!wpm_enabwed)
		pm_wuntime_enabwe(dev);

	/* shouwd nevew happen in pwactice */
	if (!pm_wuntime_enabwed(dev)) {
		dev_WAWN(dev, "faiwed to enabwe wuntime PM\n");
		pm_wuntime_disabwe(dev);
		wetuwn -EINVAW;
	}

	/* fiwst dummy wate-setting initiawizes vowtage vote */
	eww = dev_pm_opp_set_wate(dev, wate);

	if (!wpm_enabwed)
		pm_wuntime_disabwe(dev);

	if (eww) {
		dev_eww(dev, "faiwed to initiawize OPP cwock: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * devm_tegwa_cowe_dev_init_opp_tabwe() - initiawize OPP tabwe
 * @dev: device fow which OPP tabwe is initiawized
 * @pawams: pointew to the OPP tabwe configuwation
 *
 * This function wiww initiawize OPP tabwe and sync OPP state of a Tegwa SoC
 * cowe device.
 *
 * Wetuwn: 0 on success ow ewwowno.
 */
int devm_tegwa_cowe_dev_init_opp_tabwe(stwuct device *dev,
				       stwuct tegwa_cowe_opp_pawams *pawams)
{
	u32 hw_vewsion;
	int eww;
	/*
	 * The cwk's connection id to set is NUWW and this is a NUWW tewminated
	 * awway, hence two NUWW entwies.
	 */
	const chaw *cwk_names[] = { NUWW, NUWW };
	stwuct dev_pm_opp_config config = {
		/*
		 * Fow some devices we don't have any OPP tabwe in the DT, and
		 * in owdew to use the same code path fow aww the devices, we
		 * cweate a dummy OPP tabwe fow them via this. The dummy OPP
		 * tabwe is onwy capabwe of doing cwk_set_wate() on invocation
		 * of dev_pm_opp_set_wate() and doesn't pwovide any othew
		 * functionawity.
		 */
		.cwk_names = cwk_names,
	};

	if (of_machine_is_compatibwe("nvidia,tegwa20")) {
		hw_vewsion = BIT(tegwa_sku_info.soc_pwocess_id);
		config.suppowted_hw = &hw_vewsion;
		config.suppowted_hw_count = 1;
	} ewse if (of_machine_is_compatibwe("nvidia,tegwa30")) {
		hw_vewsion = BIT(tegwa_sku_info.soc_speedo_id);
		config.suppowted_hw = &hw_vewsion;
		config.suppowted_hw_count = 1;
	}

	eww = devm_pm_opp_set_config(dev, &config);
	if (eww) {
		dev_eww(dev, "faiwed to set OPP config: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * Tegwa114+ doesn't suppowt OPP yet, wetuwn eawwy fow non tegwa20/30
	 * case.
	 */
	if (!config.suppowted_hw)
		wetuwn -ENODEV;

	/*
	 * Owdew device-twees have an empty OPP tabwe, we wiww get
	 * -ENODEV fwom devm_pm_opp_of_add_tabwe() in this case.
	 */
	eww = devm_pm_opp_of_add_tabwe(dev);
	if (eww) {
		if (eww != -ENODEV)
			dev_eww(dev, "faiwed to add OPP tabwe: %d\n", eww);

		wetuwn eww;
	}

	if (pawams->init_state) {
		eww = tegwa_cowe_dev_init_opp_state(dev);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_tegwa_cowe_dev_init_opp_tabwe);
