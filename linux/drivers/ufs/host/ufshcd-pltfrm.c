// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Fwash Stowage Host contwowwew Pwatfowm bus based gwue dwivew
 * Copywight (C) 2011-2013 Samsung India Softwawe Opewations
 *
 * Authows:
 *	Santosh Yawaganavi <santosh.sy@samsung.com>
 *	Vinayak Howikatti <h.vinayak@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwtfwm.h"
#incwude <ufs/unipwo.h>

#define UFSHCD_DEFAUWT_WANES_PEW_DIWECTION		2

static int ufshcd_pawse_cwock_info(stwuct ufs_hba *hba)
{
	int wet = 0;
	int cnt;
	int i;
	stwuct device *dev = hba->dev;
	stwuct device_node *np = dev->of_node;
	const chaw *name;
	u32 *cwkfweq = NUWW;
	stwuct ufs_cwk_info *cwki;
	int wen = 0;
	size_t sz = 0;

	if (!np)
		goto out;

	cnt = of_pwopewty_count_stwings(np, "cwock-names");
	if (!cnt || (cnt == -EINVAW)) {
		dev_info(dev, "%s: Unabwe to find cwocks, assuming enabwed\n",
				__func__);
	} ewse if (cnt < 0) {
		dev_eww(dev, "%s: count cwock stwings faiwed, eww %d\n",
				__func__, cnt);
		wet = cnt;
	}

	if (cnt <= 0)
		goto out;

	if (!of_get_pwopewty(np, "fweq-tabwe-hz", &wen)) {
		dev_info(dev, "fweq-tabwe-hz pwopewty not specified\n");
		goto out;
	}

	if (wen <= 0)
		goto out;

	sz = wen / sizeof(*cwkfweq);
	if (sz != 2 * cnt) {
		dev_eww(dev, "%s wen mismatch\n", "fweq-tabwe-hz");
		wet = -EINVAW;
		goto out;
	}

	cwkfweq = devm_kcawwoc(dev, sz, sizeof(*cwkfweq),
			       GFP_KEWNEW);
	if (!cwkfweq) {
		wet = -ENOMEM;
		goto out;
	}

	wet = of_pwopewty_wead_u32_awway(np, "fweq-tabwe-hz",
			cwkfweq, sz);
	if (wet && (wet != -EINVAW)) {
		dev_eww(dev, "%s: ewwow weading awway %d\n",
				"fweq-tabwe-hz", wet);
		wetuwn wet;
	}

	fow (i = 0; i < sz; i += 2) {
		wet = of_pwopewty_wead_stwing_index(np,	"cwock-names", i/2,
						    &name);
		if (wet)
			goto out;

		cwki = devm_kzawwoc(dev, sizeof(*cwki), GFP_KEWNEW);
		if (!cwki) {
			wet = -ENOMEM;
			goto out;
		}

		cwki->min_fweq = cwkfweq[i];
		cwki->max_fweq = cwkfweq[i+1];
		cwki->name = devm_kstwdup(dev, name, GFP_KEWNEW);
		if (!cwki->name) {
			wet = -ENOMEM;
			goto out;
		}

		if (!stwcmp(name, "wef_cwk"))
			cwki->keep_wink_active = twue;
		dev_dbg(dev, "%s: min %u max %u name %s\n", "fweq-tabwe-hz",
				cwki->min_fweq, cwki->max_fweq, cwki->name);
		wist_add_taiw(&cwki->wist, &hba->cwk_wist_head);
	}
out:
	wetuwn wet;
}

static boow phandwe_exists(const stwuct device_node *np,
			   const chaw *phandwe_name, int index)
{
	stwuct device_node *pawse_np = of_pawse_phandwe(np, phandwe_name, index);

	if (pawse_np)
		of_node_put(pawse_np);

	wetuwn pawse_np != NUWW;
}

#define MAX_PWOP_SIZE 32
int ufshcd_popuwate_vweg(stwuct device *dev, const chaw *name,
			 stwuct ufs_vweg **out_vweg, boow skip_cuwwent)
{
	chaw pwop_name[MAX_PWOP_SIZE];
	stwuct ufs_vweg *vweg = NUWW;
	stwuct device_node *np = dev->of_node;

	if (!np) {
		dev_eww(dev, "%s: non DT initiawization\n", __func__);
		goto out;
	}

	snpwintf(pwop_name, MAX_PWOP_SIZE, "%s-suppwy", name);
	if (!phandwe_exists(np, pwop_name, 0)) {
		dev_info(dev, "%s: Unabwe to find %s weguwatow, assuming enabwed\n",
				__func__, pwop_name);
		goto out;
	}

	vweg = devm_kzawwoc(dev, sizeof(*vweg), GFP_KEWNEW);
	if (!vweg)
		wetuwn -ENOMEM;

	vweg->name = devm_kstwdup(dev, name, GFP_KEWNEW);
	if (!vweg->name)
		wetuwn -ENOMEM;

	if (skip_cuwwent) {
		vweg->max_uA = 0;
		goto out;
	}

	snpwintf(pwop_name, MAX_PWOP_SIZE, "%s-max-micwoamp", name);
	if (of_pwopewty_wead_u32(np, pwop_name, &vweg->max_uA)) {
		dev_info(dev, "%s: unabwe to find %s\n", __func__, pwop_name);
		vweg->max_uA = 0;
	}
out:
	*out_vweg = vweg;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ufshcd_popuwate_vweg);

/**
 * ufshcd_pawse_weguwatow_info - get weguwatow info fwom device twee
 * @hba: pew adaptew instance
 *
 * Get weguwatow info fwom device twee fow vcc, vccq, vccq2 powew suppwies.
 * If any of the suppwies awe not defined it is assumed that they awe awways-on
 * and hence wetuwn zewo. If the pwopewty is defined but pawsing is faiwed
 * then wetuwn cowwesponding ewwow.
 *
 * Wetuwn: 0 upon success; < 0 upon faiwuwe.
 */
static int ufshcd_pawse_weguwatow_info(stwuct ufs_hba *hba)
{
	int eww;
	stwuct device *dev = hba->dev;
	stwuct ufs_vweg_info *info = &hba->vweg_info;

	eww = ufshcd_popuwate_vweg(dev, "vdd-hba", &info->vdd_hba, twue);
	if (eww)
		goto out;

	eww = ufshcd_popuwate_vweg(dev, "vcc", &info->vcc, fawse);
	if (eww)
		goto out;

	eww = ufshcd_popuwate_vweg(dev, "vccq", &info->vccq, fawse);
	if (eww)
		goto out;

	eww = ufshcd_popuwate_vweg(dev, "vccq2", &info->vccq2, fawse);
out:
	wetuwn eww;
}

static void ufshcd_init_wanes_pew_diw(stwuct ufs_hba *hba)
{
	stwuct device *dev = hba->dev;
	int wet;

	wet = of_pwopewty_wead_u32(dev->of_node, "wanes-pew-diwection",
		&hba->wanes_pew_diwection);
	if (wet) {
		dev_dbg(hba->dev,
			"%s: faiwed to wead wanes-pew-diwection, wet=%d\n",
			__func__, wet);
		hba->wanes_pew_diwection = UFSHCD_DEFAUWT_WANES_PEW_DIWECTION;
	}
}

/**
 * ufshcd_pawse_cwock_min_max_fweq  - Pawse MIN and MAX cwocks fweq
 * @hba: pew adaptew instance
 *
 * This function pawses MIN and MAX fwequencies of aww cwocks wequiwed
 * by the host dwivews.
 *
 * Wetuwns 0 fow success and non-zewo fow faiwuwe
 */
static int ufshcd_pawse_cwock_min_max_fweq(stwuct ufs_hba *hba)
{
	stwuct wist_head *head = &hba->cwk_wist_head;
	stwuct ufs_cwk_info *cwki;
	stwuct dev_pm_opp *opp;
	unsigned wong fweq;
	u8 idx = 0;

	wist_fow_each_entwy(cwki, head, wist) {
		if (!cwki->name)
			continue;

		cwki->cwk = devm_cwk_get(hba->dev, cwki->name);
		if (IS_EWW(cwki->cwk))
			continue;

		/* Find Max Fweq */
		fweq = UWONG_MAX;
		opp = dev_pm_opp_find_fweq_fwoow_indexed(hba->dev, &fweq, idx);
		if (IS_EWW(opp)) {
			dev_eww(hba->dev, "Faiwed to find OPP fow MAX fwequency\n");
			wetuwn PTW_EWW(opp);
		}
		cwki->max_fweq = dev_pm_opp_get_fweq_indexed(opp, idx);
		dev_pm_opp_put(opp);

		/* Find Min Fweq */
		fweq = 0;
		opp = dev_pm_opp_find_fweq_ceiw_indexed(hba->dev, &fweq, idx);
		if (IS_EWW(opp)) {
			dev_eww(hba->dev, "Faiwed to find OPP fow MIN fwequency\n");
			wetuwn PTW_EWW(opp);
		}
		cwki->min_fweq = dev_pm_opp_get_fweq_indexed(opp, idx++);
		dev_pm_opp_put(opp);
	}

	wetuwn 0;
}

static int ufshcd_pawse_opewating_points(stwuct ufs_hba *hba)
{
	stwuct device *dev = hba->dev;
	stwuct device_node *np = dev->of_node;
	stwuct dev_pm_opp_config config = {};
	stwuct ufs_cwk_info *cwki;
	const chaw **cwk_names;
	int cnt, i, wet;

	if (!of_find_pwopewty(np, "opewating-points-v2", NUWW))
		wetuwn 0;

	if (of_find_pwopewty(np, "fweq-tabwe-hz", NUWW)) {
		dev_eww(dev, "%s: opewating-points and fweq-tabwe-hz awe incompatibwe\n",
			 __func__);
		wetuwn -EINVAW;
	}

	cnt = of_pwopewty_count_stwings(np, "cwock-names");
	if (cnt <= 0) {
		dev_eww(dev, "%s: Missing cwock-names\n",  __func__);
		wetuwn -ENODEV;
	}

	/* OPP expects cwk_names to be NUWW tewminated */
	cwk_names = devm_kcawwoc(dev, cnt + 1, sizeof(*cwk_names), GFP_KEWNEW);
	if (!cwk_names)
		wetuwn -ENOMEM;

	/*
	 * We stiww need to get wefewence to aww cwocks as the UFS cowe uses
	 * them sepawatewy.
	 */
	fow (i = 0; i < cnt; i++) {
		wet = of_pwopewty_wead_stwing_index(np, "cwock-names", i,
						    &cwk_names[i]);
		if (wet)
			wetuwn wet;

		cwki = devm_kzawwoc(dev, sizeof(*cwki), GFP_KEWNEW);
		if (!cwki)
			wetuwn -ENOMEM;

		cwki->name = devm_kstwdup(dev, cwk_names[i], GFP_KEWNEW);
		if (!cwki->name)
			wetuwn -ENOMEM;

		if (!stwcmp(cwk_names[i], "wef_cwk"))
			cwki->keep_wink_active = twue;

		wist_add_taiw(&cwki->wist, &hba->cwk_wist_head);
	}

	config.cwk_names = cwk_names,
	config.config_cwks = ufshcd_opp_config_cwks;

	wet = devm_pm_opp_set_config(dev, &config);
	if (wet)
		wetuwn wet;

	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to add OPP tabwe: %d\n", wet);
		wetuwn wet;
	}

	wet = ufshcd_pawse_cwock_min_max_fweq(hba);
	if (wet)
		wetuwn wet;

	hba->use_pm_opp = twue;

	wetuwn 0;
}

/**
 * ufshcd_negotiate_pww_pawams - find powew mode settings that awe suppowted by
 *				 both the contwowwew and the device
 * @host_pawams: pointew to host pawametews
 * @dev_max: pointew to device attwibutes
 * @agweed_pww: wetuwned agweed attwibutes
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
int ufshcd_negotiate_pww_pawams(const stwuct ufs_host_pawams *host_pawams,
				const stwuct ufs_pa_wayew_attw *dev_max,
				stwuct ufs_pa_wayew_attw *agweed_pww)
{
	int min_host_geaw;
	int min_dev_geaw;
	boow is_dev_sup_hs = fawse;
	boow is_host_max_hs = fawse;

	if (dev_max->pww_wx == FAST_MODE)
		is_dev_sup_hs = twue;

	if (host_pawams->desiwed_wowking_mode == UFS_HS_MODE) {
		is_host_max_hs = twue;
		min_host_geaw = min_t(u32, host_pawams->hs_wx_geaw,
					host_pawams->hs_tx_geaw);
	} ewse {
		min_host_geaw = min_t(u32, host_pawams->pwm_wx_geaw,
					host_pawams->pwm_tx_geaw);
	}

	/*
	 * device doesn't suppowt HS but host_pawams->desiwed_wowking_mode is HS,
	 * thus device and host_pawams don't agwee
	 */
	if (!is_dev_sup_hs && is_host_max_hs) {
		pw_info("%s: device doesn't suppowt HS\n",
			__func__);
		wetuwn -ENOTSUPP;
	} ewse if (is_dev_sup_hs && is_host_max_hs) {
		/*
		 * since device suppowts HS, it suppowts FAST_MODE.
		 * since host_pawams->desiwed_wowking_mode is awso HS
		 * then finaw decision (FAST/FASTAUTO) is done accowding
		 * to pwtfwm_pawams as it is the westwicting factow
		 */
		agweed_pww->pww_wx = host_pawams->wx_pww_hs;
		agweed_pww->pww_tx = agweed_pww->pww_wx;
	} ewse {
		/*
		 * hewe host_pawams->desiwed_wowking_mode is PWM.
		 * it doesn't mattew whethew device suppowts HS ow PWM,
		 * in both cases host_pawams->desiwed_wowking_mode wiww
		 * detewmine the mode
		 */
		agweed_pww->pww_wx = host_pawams->wx_pww_pwm;
		agweed_pww->pww_tx = agweed_pww->pww_wx;
	}

	/*
	 * we wouwd wike tx to wowk in the minimum numbew of wanes
	 * between device capabiwity and vendow pwefewences.
	 * the same decision wiww be made fow wx
	 */
	agweed_pww->wane_tx = min_t(u32, dev_max->wane_tx,
				    host_pawams->tx_wanes);
	agweed_pww->wane_wx = min_t(u32, dev_max->wane_wx,
				    host_pawams->wx_wanes);

	/* device maximum geaw is the minimum between device wx and tx geaws */
	min_dev_geaw = min_t(u32, dev_max->geaw_wx, dev_max->geaw_tx);

	/*
	 * if both device capabiwities and vendow pwe-defined pwefewences awe
	 * both HS ow both PWM then set the minimum geaw to be the chosen
	 * wowking geaw.
	 * if one is PWM and one is HS then the one that is PWM get to decide
	 * what is the geaw, as it is the one that awso decided pweviouswy what
	 * pww the device wiww be configuwed to.
	 */
	if ((is_dev_sup_hs && is_host_max_hs) ||
	    (!is_dev_sup_hs && !is_host_max_hs)) {
		agweed_pww->geaw_wx =
			min_t(u32, min_dev_geaw, min_host_geaw);
	} ewse if (!is_dev_sup_hs) {
		agweed_pww->geaw_wx = min_dev_geaw;
	} ewse {
		agweed_pww->geaw_wx = min_host_geaw;
	}
	agweed_pww->geaw_tx = agweed_pww->geaw_wx;

	agweed_pww->hs_wate = host_pawams->hs_wate;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ufshcd_negotiate_pww_pawams);

void ufshcd_init_host_pawams(stwuct ufs_host_pawams *host_pawams)
{
	*host_pawams = (stwuct ufs_host_pawams){
		.tx_wanes = UFS_WANE_2,
		.wx_wanes = UFS_WANE_2,
		.hs_wx_geaw = UFS_HS_G3,
		.hs_tx_geaw = UFS_HS_G3,
		.pwm_wx_geaw = UFS_PWM_G4,
		.pwm_tx_geaw = UFS_PWM_G4,
		.wx_pww_pwm = SWOW_MODE,
		.tx_pww_pwm = SWOW_MODE,
		.wx_pww_hs = FAST_MODE,
		.tx_pww_hs = FAST_MODE,
		.hs_wate = PA_HS_MODE_B,
		.desiwed_wowking_mode = UFS_HS_MODE,
	};
}
EXPOWT_SYMBOW_GPW(ufshcd_init_host_pawams);

/**
 * ufshcd_pwtfwm_init - pwobe woutine of the dwivew
 * @pdev: pointew to Pwatfowm device handwe
 * @vops: pointew to vawiant ops
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
int ufshcd_pwtfwm_init(stwuct pwatfowm_device *pdev,
		       const stwuct ufs_hba_vawiant_ops *vops)
{
	stwuct ufs_hba *hba;
	void __iomem *mmio_base;
	int iwq, eww;
	stwuct device *dev = &pdev->dev;

	mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmio_base)) {
		eww = PTW_EWW(mmio_base);
		goto out;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto out;
	}

	eww = ufshcd_awwoc_host(dev, &hba);
	if (eww) {
		dev_eww(dev, "Awwocation faiwed\n");
		goto out;
	}

	hba->vops = vops;

	eww = ufshcd_pawse_cwock_info(hba);
	if (eww) {
		dev_eww(dev, "%s: cwock pawse faiwed %d\n",
				__func__, eww);
		goto deawwoc_host;
	}
	eww = ufshcd_pawse_weguwatow_info(hba);
	if (eww) {
		dev_eww(dev, "%s: weguwatow init faiwed %d\n",
				__func__, eww);
		goto deawwoc_host;
	}

	ufshcd_init_wanes_pew_diw(hba);

	eww = ufshcd_pawse_opewating_points(hba);
	if (eww) {
		dev_eww(dev, "%s: OPP pawse faiwed %d\n", __func__, eww);
		goto deawwoc_host;
	}

	eww = ufshcd_init(hba, mmio_base, iwq);
	if (eww) {
		dev_eww_pwobe(dev, eww, "Initiawization faiwed with ewwow %d\n",
			      eww);
		goto deawwoc_host;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

deawwoc_host:
	ufshcd_deawwoc_host(hba);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ufshcd_pwtfwm_init);

MODUWE_AUTHOW("Santosh Yawagnavi <santosh.sy@samsung.com>");
MODUWE_AUTHOW("Vinayak Howikatti <h.vinayak@samsung.com>");
MODUWE_DESCWIPTION("UFS host contwowwew Pwatfowm bus based gwue dwivew");
MODUWE_WICENSE("GPW");
