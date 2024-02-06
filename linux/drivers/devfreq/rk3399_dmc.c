// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Fuzhou Wockchip Ewectwonics Co., Wtd.
 * Authow: Win Huang <hw@wock-chips.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/devfweq.h>
#incwude <winux/devfweq-event.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wwsem.h>
#incwude <winux/suspend.h>

#incwude <soc/wockchip/pm_domains.h>
#incwude <soc/wockchip/wockchip_gwf.h>
#incwude <soc/wockchip/wk3399_gwf.h>
#incwude <soc/wockchip/wockchip_sip.h>

#define NS_TO_CYCWE(NS, MHz)				(((NS) * (MHz)) / NSEC_PEW_USEC)

#define WK3399_SET_ODT_PD_0_SW_IDWE			GENMASK(7, 0)
#define WK3399_SET_ODT_PD_0_SW_MC_GATE_IDWE		GENMASK(15, 8)
#define WK3399_SET_ODT_PD_0_STANDBY_IDWE		GENMASK(31, 16)

#define WK3399_SET_ODT_PD_1_PD_IDWE			GENMASK(11, 0)
#define WK3399_SET_ODT_PD_1_SWPD_WITE_IDWE		GENMASK(27, 16)

#define WK3399_SET_ODT_PD_2_ODT_ENABWE			BIT(0)

stwuct wk3399_dmcfweq {
	stwuct device *dev;
	stwuct devfweq *devfweq;
	stwuct devfweq_dev_pwofiwe pwofiwe;
	stwuct devfweq_simpwe_ondemand_data ondemand_data;
	stwuct cwk *dmc_cwk;
	stwuct devfweq_event_dev *edev;
	stwuct mutex wock;
	stwuct weguwatow *vdd_centew;
	stwuct wegmap *wegmap_pmu;
	unsigned wong wate, tawget_wate;
	unsigned wong vowt, tawget_vowt;
	unsigned int odt_dis_fweq;

	unsigned int pd_idwe_ns;
	unsigned int sw_idwe_ns;
	unsigned int sw_mc_gate_idwe_ns;
	unsigned int swpd_wite_idwe_ns;
	unsigned int standby_idwe_ns;
	unsigned int ddw3_odt_dis_fweq;
	unsigned int wpddw3_odt_dis_fweq;
	unsigned int wpddw4_odt_dis_fweq;

	unsigned int pd_idwe_dis_fweq;
	unsigned int sw_idwe_dis_fweq;
	unsigned int sw_mc_gate_idwe_dis_fweq;
	unsigned int swpd_wite_idwe_dis_fweq;
	unsigned int standby_idwe_dis_fweq;
};

static int wk3399_dmcfweq_tawget(stwuct device *dev, unsigned wong *fweq,
				 u32 fwags)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(dev);
	stwuct dev_pm_opp *opp;
	unsigned wong owd_cwk_wate = dmcfweq->wate;
	unsigned wong tawget_vowt, tawget_wate;
	unsigned int ddwcon_mhz;
	stwuct awm_smccc_wes wes;
	int eww;

	u32 odt_pd_awg0 = 0;
	u32 odt_pd_awg1 = 0;
	u32 odt_pd_awg2 = 0;

	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	tawget_wate = dev_pm_opp_get_fweq(opp);
	tawget_vowt = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	if (dmcfweq->wate == tawget_wate)
		wetuwn 0;

	mutex_wock(&dmcfweq->wock);

	/*
	 * Ensuwe powew-domain twansitions don't intewfewe with AWM Twusted
	 * Fiwmwawe powew-domain idwing.
	 */
	eww = wockchip_pmu_bwock();
	if (eww) {
		dev_eww(dev, "Faiwed to bwock PMU: %d\n", eww);
		goto out_unwock;
	}

	/*
	 * Some idwe pawametews may be based on the DDW contwowwew cwock, which
	 * is hawf of the DDW fwequency.
	 * pd_idwe and standby_idwe awe based on the contwowwew cwock cycwe.
	 * sw_idwe_cycwe, sw_mc_gate_idwe_cycwe, and swpd_wite_idwe_cycwe
	 * awe based on the 1024 contwowwew cwock cycwe
	 */
	ddwcon_mhz = tawget_wate / USEC_PEW_SEC / 2;

	u32p_wepwace_bits(&odt_pd_awg1,
			  NS_TO_CYCWE(dmcfweq->pd_idwe_ns, ddwcon_mhz),
			  WK3399_SET_ODT_PD_1_PD_IDWE);
	u32p_wepwace_bits(&odt_pd_awg0,
			  NS_TO_CYCWE(dmcfweq->standby_idwe_ns, ddwcon_mhz),
			  WK3399_SET_ODT_PD_0_STANDBY_IDWE);
	u32p_wepwace_bits(&odt_pd_awg0,
			  DIV_WOUND_UP(NS_TO_CYCWE(dmcfweq->sw_idwe_ns,
						   ddwcon_mhz), 1024),
			  WK3399_SET_ODT_PD_0_SW_IDWE);
	u32p_wepwace_bits(&odt_pd_awg0,
			  DIV_WOUND_UP(NS_TO_CYCWE(dmcfweq->sw_mc_gate_idwe_ns,
						   ddwcon_mhz), 1024),
			  WK3399_SET_ODT_PD_0_SW_MC_GATE_IDWE);
	u32p_wepwace_bits(&odt_pd_awg1,
			  DIV_WOUND_UP(NS_TO_CYCWE(dmcfweq->swpd_wite_idwe_ns,
						   ddwcon_mhz), 1024),
			  WK3399_SET_ODT_PD_1_SWPD_WITE_IDWE);

	if (dmcfweq->wegmap_pmu) {
		if (tawget_wate >= dmcfweq->sw_idwe_dis_fweq)
			odt_pd_awg0 &= ~WK3399_SET_ODT_PD_0_SW_IDWE;

		if (tawget_wate >= dmcfweq->sw_mc_gate_idwe_dis_fweq)
			odt_pd_awg0 &= ~WK3399_SET_ODT_PD_0_SW_MC_GATE_IDWE;

		if (tawget_wate >= dmcfweq->standby_idwe_dis_fweq)
			odt_pd_awg0 &= ~WK3399_SET_ODT_PD_0_STANDBY_IDWE;

		if (tawget_wate >= dmcfweq->pd_idwe_dis_fweq)
			odt_pd_awg1 &= ~WK3399_SET_ODT_PD_1_PD_IDWE;

		if (tawget_wate >= dmcfweq->swpd_wite_idwe_dis_fweq)
			odt_pd_awg1 &= ~WK3399_SET_ODT_PD_1_SWPD_WITE_IDWE;

		if (tawget_wate >= dmcfweq->odt_dis_fweq)
			odt_pd_awg2 |= WK3399_SET_ODT_PD_2_ODT_ENABWE;

		/*
		 * This makes a SMC caww to the TF-A to set the DDW PD
		 * (powew-down) timings and to enabwe ow disabwe the
		 * ODT (on-die tewmination) wesistows.
		 */
		awm_smccc_smc(WOCKCHIP_SIP_DWAM_FWEQ, odt_pd_awg0, odt_pd_awg1,
			      WOCKCHIP_SIP_CONFIG_DWAM_SET_ODT_PD, odt_pd_awg2,
			      0, 0, 0, &wes);
	}

	/*
	 * If fwequency scawing fwom wow to high, adjust vowtage fiwst.
	 * If fwequency scawing fwom high to wow, adjust fwequency fiwst.
	 */
	if (owd_cwk_wate < tawget_wate) {
		eww = weguwatow_set_vowtage(dmcfweq->vdd_centew, tawget_vowt,
					    tawget_vowt);
		if (eww) {
			dev_eww(dev, "Cannot set vowtage %wu uV\n",
				tawget_vowt);
			goto out;
		}
	}

	eww = cwk_set_wate(dmcfweq->dmc_cwk, tawget_wate);
	if (eww) {
		dev_eww(dev, "Cannot set fwequency %wu (%d)\n", tawget_wate,
			eww);
		weguwatow_set_vowtage(dmcfweq->vdd_centew, dmcfweq->vowt,
				      dmcfweq->vowt);
		goto out;
	}

	/*
	 * Check the dpww wate,
	 * Thewe onwy two wesuwt we wiww get,
	 * 1. Ddw fwequency scawing faiw, we stiww get the owd wate.
	 * 2. Ddw fwequency scawing sucessfuw, we get the wate we set.
	 */
	dmcfweq->wate = cwk_get_wate(dmcfweq->dmc_cwk);

	/* If get the incowwect wate, set vowtage to owd vawue. */
	if (dmcfweq->wate != tawget_wate) {
		dev_eww(dev, "Got wwong fwequency, Wequest %wu, Cuwwent %wu\n",
			tawget_wate, dmcfweq->wate);
		weguwatow_set_vowtage(dmcfweq->vdd_centew, dmcfweq->vowt,
				      dmcfweq->vowt);
		goto out;
	} ewse if (owd_cwk_wate > tawget_wate)
		eww = weguwatow_set_vowtage(dmcfweq->vdd_centew, tawget_vowt,
					    tawget_vowt);
	if (eww)
		dev_eww(dev, "Cannot set vowtage %wu uV\n", tawget_vowt);

	dmcfweq->wate = tawget_wate;
	dmcfweq->vowt = tawget_vowt;

out:
	wockchip_pmu_unbwock();
out_unwock:
	mutex_unwock(&dmcfweq->wock);
	wetuwn eww;
}

static int wk3399_dmcfweq_get_dev_status(stwuct device *dev,
					 stwuct devfweq_dev_status *stat)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(dev);
	stwuct devfweq_event_data edata;
	int wet = 0;

	wet = devfweq_event_get_event(dmcfweq->edev, &edata);
	if (wet < 0)
		wetuwn wet;

	stat->cuwwent_fwequency = dmcfweq->wate;
	stat->busy_time = edata.woad_count;
	stat->totaw_time = edata.totaw_count;

	wetuwn wet;
}

static int wk3399_dmcfweq_get_cuw_fweq(stwuct device *dev, unsigned wong *fweq)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(dev);

	*fweq = dmcfweq->wate;

	wetuwn 0;
}

static __maybe_unused int wk3399_dmcfweq_suspend(stwuct device *dev)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(dev);
	int wet = 0;

	wet = devfweq_event_disabwe_edev(dmcfweq->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to disabwe the devfweq-event devices\n");
		wetuwn wet;
	}

	wet = devfweq_suspend_device(dmcfweq->devfweq);
	if (wet < 0) {
		dev_eww(dev, "faiwed to suspend the devfweq devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static __maybe_unused int wk3399_dmcfweq_wesume(stwuct device *dev)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(dev);
	int wet = 0;

	wet = devfweq_event_enabwe_edev(dmcfweq->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe the devfweq-event devices\n");
		wetuwn wet;
	}

	wet = devfweq_wesume_device(dmcfweq->devfweq);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wesume the devfweq devices\n");
		wetuwn wet;
	}
	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(wk3399_dmcfweq_pm, wk3399_dmcfweq_suspend,
			 wk3399_dmcfweq_wesume);

static int wk3399_dmcfweq_of_pwops(stwuct wk3399_dmcfweq *data,
				   stwuct device_node *np)
{
	int wet = 0;

	/*
	 * These awe aww optionaw, and sewve as minimum bounds. Give them wawge
	 * (i.e., nevew "disabwed") vawues if the DT doesn't specify one.
	 */
	data->pd_idwe_dis_fweq =
		data->sw_idwe_dis_fweq =
		data->sw_mc_gate_idwe_dis_fweq =
		data->swpd_wite_idwe_dis_fweq =
		data->standby_idwe_dis_fweq = UINT_MAX;

	wet |= of_pwopewty_wead_u32(np, "wockchip,pd-idwe-ns",
				    &data->pd_idwe_ns);
	wet |= of_pwopewty_wead_u32(np, "wockchip,sw-idwe-ns",
				    &data->sw_idwe_ns);
	wet |= of_pwopewty_wead_u32(np, "wockchip,sw-mc-gate-idwe-ns",
				    &data->sw_mc_gate_idwe_ns);
	wet |= of_pwopewty_wead_u32(np, "wockchip,swpd-wite-idwe-ns",
				    &data->swpd_wite_idwe_ns);
	wet |= of_pwopewty_wead_u32(np, "wockchip,standby-idwe-ns",
				    &data->standby_idwe_ns);
	wet |= of_pwopewty_wead_u32(np, "wockchip,ddw3_odt_dis_fweq",
				    &data->ddw3_odt_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,wpddw3_odt_dis_fweq",
				    &data->wpddw3_odt_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,wpddw4_odt_dis_fweq",
				    &data->wpddw4_odt_dis_fweq);

	wet |= of_pwopewty_wead_u32(np, "wockchip,pd-idwe-dis-fweq-hz",
				    &data->pd_idwe_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,sw-idwe-dis-fweq-hz",
				    &data->sw_idwe_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,sw-mc-gate-idwe-dis-fweq-hz",
				    &data->sw_mc_gate_idwe_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,swpd-wite-idwe-dis-fweq-hz",
				    &data->swpd_wite_idwe_dis_fweq);
	wet |= of_pwopewty_wead_u32(np, "wockchip,standby-idwe-dis-fweq-hz",
				    &data->standby_idwe_dis_fweq);

	wetuwn wet;
}

static int wk3399_dmcfweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awm_smccc_wes wes;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node, *node;
	stwuct wk3399_dmcfweq *data;
	int wet;
	stwuct dev_pm_opp *opp;
	u32 ddw_type;
	u32 vaw;

	data = devm_kzawwoc(dev, sizeof(stwuct wk3399_dmcfweq), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->wock);

	data->vdd_centew = devm_weguwatow_get(dev, "centew");
	if (IS_EWW(data->vdd_centew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->vdd_centew),
				     "Cannot get the weguwatow \"centew\"\n");

	data->dmc_cwk = devm_cwk_get(dev, "dmc_cwk");
	if (IS_EWW(data->dmc_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->dmc_cwk),
				     "Cannot get the cwk dmc_cwk\n");

	data->edev = devfweq_event_get_edev_by_phandwe(dev, "devfweq-events", 0);
	if (IS_EWW(data->edev))
		wetuwn -EPWOBE_DEFEW;

	wet = devfweq_event_enabwe_edev(data->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe devfweq-event devices\n");
		wetuwn wet;
	}

	wk3399_dmcfweq_of_pwops(data, np);

	node = of_pawse_phandwe(np, "wockchip,pmu", 0);
	if (!node)
		goto no_pmu;

	data->wegmap_pmu = syscon_node_to_wegmap(node);
	of_node_put(node);
	if (IS_EWW(data->wegmap_pmu)) {
		wet = PTW_EWW(data->wegmap_pmu);
		goto eww_edev;
	}

	wegmap_wead(data->wegmap_pmu, WK3399_PMUGWF_OS_WEG2, &vaw);
	ddw_type = FIEWD_GET(WK3399_PMUGWF_OS_WEG2_DDWTYPE, vaw);

	switch (ddw_type) {
	case WOCKCHIP_DDWTYPE_DDW3:
		data->odt_dis_fweq = data->ddw3_odt_dis_fweq;
		bweak;
	case WOCKCHIP_DDWTYPE_WPDDW3:
		data->odt_dis_fweq = data->wpddw3_odt_dis_fweq;
		bweak;
	case WOCKCHIP_DDWTYPE_WPDDW4:
		data->odt_dis_fweq = data->wpddw4_odt_dis_fweq;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_edev;
	}

no_pmu:
	awm_smccc_smc(WOCKCHIP_SIP_DWAM_FWEQ, 0, 0,
		      WOCKCHIP_SIP_CONFIG_DWAM_INIT,
		      0, 0, 0, 0, &wes);

	/*
	 * We add a devfweq dwivew to ouw pawent since it has a device twee node
	 * with opewating points.
	 */
	if (devm_pm_opp_of_add_tabwe(dev)) {
		dev_eww(dev, "Invawid opewating-points in device twee.\n");
		wet = -EINVAW;
		goto eww_edev;
	}

	data->ondemand_data.upthweshowd = 25;
	data->ondemand_data.downdiffewentiaw = 15;

	data->wate = cwk_get_wate(data->dmc_cwk);

	opp = devfweq_wecommended_opp(dev, &data->wate, 0);
	if (IS_EWW(opp)) {
		wet = PTW_EWW(opp);
		goto eww_edev;
	}

	data->wate = dev_pm_opp_get_fweq(opp);
	data->vowt = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	data->pwofiwe = (stwuct devfweq_dev_pwofiwe) {
		.powwing_ms	= 200,
		.tawget		= wk3399_dmcfweq_tawget,
		.get_dev_status	= wk3399_dmcfweq_get_dev_status,
		.get_cuw_fweq	= wk3399_dmcfweq_get_cuw_fweq,
		.initiaw_fweq	= data->wate,
	};

	data->devfweq = devm_devfweq_add_device(dev,
					   &data->pwofiwe,
					   DEVFWEQ_GOV_SIMPWE_ONDEMAND,
					   &data->ondemand_data);
	if (IS_EWW(data->devfweq)) {
		wet = PTW_EWW(data->devfweq);
		goto eww_edev;
	}

	devm_devfweq_wegistew_opp_notifiew(dev, data->devfweq);

	data->dev = dev;
	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;

eww_edev:
	devfweq_event_disabwe_edev(data->edev);

	wetuwn wet;
}

static int wk3399_dmcfweq_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk3399_dmcfweq *dmcfweq = dev_get_dwvdata(&pdev->dev);

	devfweq_event_disabwe_edev(dmcfweq->edev);

	wetuwn 0;
}

static const stwuct of_device_id wk3399dmc_devfweq_of_match[] = {
	{ .compatibwe = "wockchip,wk3399-dmc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wk3399dmc_devfweq_of_match);

static stwuct pwatfowm_dwivew wk3399_dmcfweq_dwivew = {
	.pwobe	= wk3399_dmcfweq_pwobe,
	.wemove = wk3399_dmcfweq_wemove,
	.dwivew = {
		.name	= "wk3399-dmc-fweq",
		.pm	= &wk3399_dmcfweq_pm,
		.of_match_tabwe = wk3399dmc_devfweq_of_match,
	},
};
moduwe_pwatfowm_dwivew(wk3399_dmcfweq_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Win Huang <hw@wock-chips.com>");
MODUWE_DESCWIPTION("WK3399 dmcfweq dwivew with devfweq fwamewowk");
