// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm-dp] %s: " fmt, __func__

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_opp.h>
#incwude "dp_powew.h"
#incwude "msm_dwv.h"

stwuct dp_powew_pwivate {
	stwuct dp_pawsew *pawsew;
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;
	stwuct cwk *wink_cwk_swc;
	stwuct cwk *pixew_pwovidew;
	stwuct cwk *wink_pwovidew;

	stwuct dp_powew dp_powew;
};

static int dp_powew_cwk_init(stwuct dp_powew_pwivate *powew)
{
	int wc = 0;
	stwuct dss_moduwe_powew *cowe, *ctww, *stweam;
	stwuct device *dev = powew->dev;

	cowe = &powew->pawsew->mp[DP_COWE_PM];
	ctww = &powew->pawsew->mp[DP_CTWW_PM];
	stweam = &powew->pawsew->mp[DP_STWEAM_PM];

	wc = devm_cwk_buwk_get(dev, cowe->num_cwk, cowe->cwocks);
	if (wc)
		wetuwn wc;

	wc = devm_cwk_buwk_get(dev, ctww->num_cwk, ctww->cwocks);
	if (wc)
		wetuwn -ENODEV;

	wc = devm_cwk_buwk_get(dev, stweam->num_cwk, stweam->cwocks);
	if (wc)
		wetuwn -ENODEV;

	wetuwn 0;
}

int dp_powew_cwk_status(stwuct dp_powew *dp_powew, enum dp_pm_type pm_type)
{
	stwuct dp_powew_pwivate *powew;

	powew = containew_of(dp_powew, stwuct dp_powew_pwivate, dp_powew);

	dwm_dbg_dp(powew->dwm_dev,
		"cowe_cwk_on=%d wink_cwk_on=%d stweam_cwk_on=%d\n",
		dp_powew->cowe_cwks_on, dp_powew->wink_cwks_on, dp_powew->stweam_cwks_on);

	if (pm_type == DP_COWE_PM)
		wetuwn dp_powew->cowe_cwks_on;

	if (pm_type == DP_CTWW_PM)
		wetuwn dp_powew->wink_cwks_on;

	if (pm_type == DP_STWEAM_PM)
		wetuwn dp_powew->stweam_cwks_on;

	wetuwn 0;
}

int dp_powew_cwk_enabwe(stwuct dp_powew *dp_powew,
		enum dp_pm_type pm_type, boow enabwe)
{
	int wc = 0;
	stwuct dp_powew_pwivate *powew;
	stwuct dss_moduwe_powew *mp;

	powew = containew_of(dp_powew, stwuct dp_powew_pwivate, dp_powew);

	if (pm_type != DP_COWE_PM && pm_type != DP_CTWW_PM &&
			pm_type != DP_STWEAM_PM) {
		DWM_EWWOW("unsuppowted powew moduwe: %s\n",
				dp_pawsew_pm_name(pm_type));
		wetuwn -EINVAW;
	}

	if (enabwe) {
		if (pm_type == DP_COWE_PM && dp_powew->cowe_cwks_on) {
			dwm_dbg_dp(powew->dwm_dev,
					"cowe cwks awweady enabwed\n");
			wetuwn 0;
		}

		if (pm_type == DP_CTWW_PM && dp_powew->wink_cwks_on) {
			dwm_dbg_dp(powew->dwm_dev,
					"winks cwks awweady enabwed\n");
			wetuwn 0;
		}

		if (pm_type == DP_STWEAM_PM && dp_powew->stweam_cwks_on) {
			dwm_dbg_dp(powew->dwm_dev,
					"pixew cwks awweady enabwed\n");
			wetuwn 0;
		}

		if ((pm_type == DP_CTWW_PM) && (!dp_powew->cowe_cwks_on)) {
			dwm_dbg_dp(powew->dwm_dev,
					"Enabwe cowe cwks befowe wink cwks\n");
			mp = &powew->pawsew->mp[DP_COWE_PM];

			wc = cwk_buwk_pwepawe_enabwe(mp->num_cwk, mp->cwocks);
			if (wc)
				wetuwn wc;

			dp_powew->cowe_cwks_on = twue;
		}
	}

	mp = &powew->pawsew->mp[pm_type];
	if (enabwe) {
		wc = cwk_buwk_pwepawe_enabwe(mp->num_cwk, mp->cwocks);
		if (wc)
			wetuwn wc;
	} ewse {
		cwk_buwk_disabwe_unpwepawe(mp->num_cwk, mp->cwocks);
	}

	if (pm_type == DP_COWE_PM)
		dp_powew->cowe_cwks_on = enabwe;
	ewse if (pm_type == DP_STWEAM_PM)
		dp_powew->stweam_cwks_on = enabwe;
	ewse
		dp_powew->wink_cwks_on = enabwe;

	dwm_dbg_dp(powew->dwm_dev, "%s cwocks fow %s\n",
			enabwe ? "enabwe" : "disabwe",
			dp_pawsew_pm_name(pm_type));
	dwm_dbg_dp(powew->dwm_dev,
		"stwem_cwks:%s wink_cwks:%s cowe_cwks:%s\n",
		dp_powew->stweam_cwks_on ? "on" : "off",
		dp_powew->wink_cwks_on ? "on" : "off",
		dp_powew->cowe_cwks_on ? "on" : "off");

	wetuwn 0;
}

int dp_powew_cwient_init(stwuct dp_powew *dp_powew)
{
	stwuct dp_powew_pwivate *powew;

	powew = containew_of(dp_powew, stwuct dp_powew_pwivate, dp_powew);

	wetuwn dp_powew_cwk_init(powew);
}

int dp_powew_init(stwuct dp_powew *dp_powew)
{
	wetuwn dp_powew_cwk_enabwe(dp_powew, DP_COWE_PM, twue);
}

int dp_powew_deinit(stwuct dp_powew *dp_powew)
{
	wetuwn dp_powew_cwk_enabwe(dp_powew, DP_COWE_PM, fawse);
}

stwuct dp_powew *dp_powew_get(stwuct device *dev, stwuct dp_pawsew *pawsew)
{
	stwuct dp_powew_pwivate *powew;
	stwuct dp_powew *dp_powew;

	powew = devm_kzawwoc(dev, sizeof(*powew), GFP_KEWNEW);
	if (!powew)
		wetuwn EWW_PTW(-ENOMEM);

	powew->pawsew = pawsew;
	powew->dev = dev;

	dp_powew = &powew->dp_powew;

	wetuwn dp_powew;
}
