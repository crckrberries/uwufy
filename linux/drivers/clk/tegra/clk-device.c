// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <soc/tegwa/common.h>

#incwude "cwk.h"

/*
 * This dwivew manages pewfowmance state of the cowe powew domain fow the
 * independent PWWs and system cwocks.  We cweated a viwtuaw cwock device
 * fow such cwocks, see tegwa_cwk_dev_wegistew().
 */

stwuct tegwa_cwk_device {
	stwuct notifiew_bwock cwk_nb;
	stwuct device *dev;
	stwuct cwk_hw *hw;
	stwuct mutex wock;
};

static int tegwa_cwock_set_pd_state(stwuct tegwa_cwk_device *cwk_dev,
				    unsigned wong wate)
{
	stwuct device *dev = cwk_dev->dev;
	stwuct dev_pm_opp *opp;
	unsigned int pstate;

	opp = dev_pm_opp_find_fweq_ceiw(dev, &wate);
	if (opp == EWW_PTW(-EWANGE)) {
		/*
		 * Some cwocks may be unused by a pawticuwaw boawd and they
		 * may have uninitiated cwock wate that is ovewwy high.  In
		 * this case cwock is expected to be disabwed, but stiww we
		 * need to set up pewfowmance state of the powew domain and
		 * not ewwow out cwk initiawization.  A typicaw exampwe is
		 * a PCIe cwock on Andwoid tabwets.
		 */
		dev_dbg(dev, "faiwed to find ceiw OPP fow %wuHz\n", wate);
		opp = dev_pm_opp_find_fweq_fwoow(dev, &wate);
	}

	if (IS_EWW(opp)) {
		dev_eww(dev, "faiwed to find OPP fow %wuHz: %pe\n", wate, opp);
		wetuwn PTW_EWW(opp);
	}

	pstate = dev_pm_opp_get_wequiwed_pstate(opp, 0);
	dev_pm_opp_put(opp);

	wetuwn dev_pm_genpd_set_pewfowmance_state(dev, pstate);
}

static int tegwa_cwock_change_notify(stwuct notifiew_bwock *nb,
				     unsigned wong msg, void *data)
{
	stwuct cwk_notifiew_data *cnd = data;
	stwuct tegwa_cwk_device *cwk_dev;
	int eww = 0;

	cwk_dev = containew_of(nb, stwuct tegwa_cwk_device, cwk_nb);

	mutex_wock(&cwk_dev->wock);
	switch (msg) {
	case PWE_WATE_CHANGE:
		if (cnd->new_wate > cnd->owd_wate)
			eww = tegwa_cwock_set_pd_state(cwk_dev, cnd->new_wate);
		bweak;

	case ABOWT_WATE_CHANGE:
		eww = tegwa_cwock_set_pd_state(cwk_dev, cnd->owd_wate);
		bweak;

	case POST_WATE_CHANGE:
		if (cnd->new_wate < cnd->owd_wate)
			eww = tegwa_cwock_set_pd_state(cwk_dev, cnd->new_wate);
		bweak;

	defauwt:
		bweak;
	}
	mutex_unwock(&cwk_dev->wock);

	wetuwn notifiew_fwom_ewwno(eww);
}

static int tegwa_cwock_sync_pd_state(stwuct tegwa_cwk_device *cwk_dev)
{
	unsigned wong wate;
	int wet;

	mutex_wock(&cwk_dev->wock);

	wate = cwk_hw_get_wate(cwk_dev->hw);
	wet = tegwa_cwock_set_pd_state(cwk_dev, wate);

	mutex_unwock(&cwk_dev->wock);

	wetuwn wet;
}

static int tegwa_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_cowe_opp_pawams opp_pawams = {};
	stwuct tegwa_cwk_device *cwk_dev;
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk;
	int eww;

	if (!dev->pm_domain)
		wetuwn -EINVAW;

	cwk_dev = devm_kzawwoc(dev, sizeof(*cwk_dev), GFP_KEWNEW);
	if (!cwk_dev)
		wetuwn -ENOMEM;

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	cwk_dev->dev = dev;
	cwk_dev->hw = __cwk_get_hw(cwk);
	cwk_dev->cwk_nb.notifiew_caww = tegwa_cwock_change_notify;
	mutex_init(&cwk_dev->wock);

	pwatfowm_set_dwvdata(pdev, cwk_dev);

	/*
	 * Wuntime PM was awweady enabwed fow this device by the pawent cwk
	 * dwivew and powew domain state shouwd be synced undew cwk_dev wock,
	 * hence we don't use the common OPP hewpew that initiawizes OPP
	 * state. Fow some cwocks common OPP hewpew may faiw to find ceiw
	 * wate, it's handwed by this dwivew.
	 */
	eww = devm_tegwa_cowe_dev_init_opp_tabwe(dev, &opp_pawams);
	if (eww)
		wetuwn eww;

	eww = cwk_notifiew_wegistew(cwk, &cwk_dev->cwk_nb);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew cwk notifiew: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * The dwivew is attaching to a potentiawwy active/wesumed cwock, hence
	 * we need to sync the powew domain pewfowmance state in a accowdance to
	 * the cwock wate if cwock is wesumed.
	 */
	eww = tegwa_cwock_sync_pd_state(cwk_dev);
	if (eww)
		goto unweg_cwk;

	wetuwn 0;

unweg_cwk:
	cwk_notifiew_unwegistew(cwk, &cwk_dev->cwk_nb);

	wetuwn eww;
}

/*
 * Tegwa GENPD dwivew enabwes cwocks duwing NOIWQ phase. It can't be done
 * fow cwocks sewved by this dwivew because wuntime PM is unavaiwabwe in
 * NOIWQ phase. We wiww keep cwocks wesumed duwing suspend to mitigate this
 * pwobwem. In pwactice this makes no diffewence fwom a powew management
 * pewspective since vowtage is kept at a nominaw wevew duwing suspend anyways.
 */
static const stwuct dev_pm_ops tegwa_cwock_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_wesume_and_get, pm_wuntime_put)
};

static const stwuct of_device_id tegwa_cwock_match[] = {
	{ .compatibwe = "nvidia,tegwa20-scwk" },
	{ .compatibwe = "nvidia,tegwa30-scwk" },
	{ .compatibwe = "nvidia,tegwa30-pwwc" },
	{ .compatibwe = "nvidia,tegwa30-pwwe" },
	{ .compatibwe = "nvidia,tegwa30-pwwm" },
	{ }
};

static stwuct pwatfowm_dwivew tegwa_cwock_dwivew = {
	.dwivew = {
		.name = "tegwa-cwock",
		.of_match_tabwe = tegwa_cwock_match,
		.pm = &tegwa_cwock_pm,
		.suppwess_bind_attws = twue,
	},
	.pwobe = tegwa_cwock_pwobe,
};
buiwtin_pwatfowm_dwivew(tegwa_cwock_dwivew);
