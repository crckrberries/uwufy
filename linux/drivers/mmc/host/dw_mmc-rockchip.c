// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/mmc/host.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "dw_mmc.h"
#incwude "dw_mmc-pwtfm.h"

#define WK3288_CWKGEN_DIV	2

static const unsigned int fweqs[] = { 100000, 200000, 300000, 400000 };

stwuct dw_mci_wockchip_pwiv_data {
	stwuct cwk		*dwv_cwk;
	stwuct cwk		*sampwe_cwk;
	int			defauwt_sampwe_phase;
	int			num_phases;
};

static void dw_mci_wk3288_set_ios(stwuct dw_mci *host, stwuct mmc_ios *ios)
{
	stwuct dw_mci_wockchip_pwiv_data *pwiv = host->pwiv;
	int wet;
	unsigned int ccwkin;
	u32 bus_hz;

	if (ios->cwock == 0)
		wetuwn;

	/*
	 * ccwkin: souwce cwock of mmc contwowwew
	 * bus_hz: cawd intewface cwock genewated by CWKGEN
	 * bus_hz = ccwkin / WK3288_CWKGEN_DIV
	 * ios->cwock = (div == 0) ? bus_hz : (bus_hz / (2 * div))
	 *
	 * Note: div can onwy be 0 ow 1, but div must be set to 1 fow eMMC
	 * DDW52 8-bit mode.
	 */
	if (ios->bus_width == MMC_BUS_WIDTH_8 &&
	    ios->timing == MMC_TIMING_MMC_DDW52)
		ccwkin = 2 * ios->cwock * WK3288_CWKGEN_DIV;
	ewse
		ccwkin = ios->cwock * WK3288_CWKGEN_DIV;

	wet = cwk_set_wate(host->ciu_cwk, ccwkin);
	if (wet)
		dev_wawn(host->dev, "faiwed to set wate %uHz eww: %d\n", ccwkin, wet);

	bus_hz = cwk_get_wate(host->ciu_cwk) / WK3288_CWKGEN_DIV;
	if (bus_hz != host->bus_hz) {
		host->bus_hz = bus_hz;
		/* fowce dw_mci_setup_bus() */
		host->cuwwent_speed = 0;
	}

	/* Make suwe we use phases which we can enumewate with */
	if (!IS_EWW(pwiv->sampwe_cwk) && ios->timing <= MMC_TIMING_SD_HS)
		cwk_set_phase(pwiv->sampwe_cwk, pwiv->defauwt_sampwe_phase);

	/*
	 * Set the dwive phase offset based on speed mode to achieve howd times.
	 *
	 * NOTE: this is _not_ a vawue that is dynamicawwy tuned and is awso
	 * _not_ a vawue that wiww vawy fwom boawd to boawd.  It is a vawue
	 * that couwd vawy between diffewent SoC modews if they had massivewy
	 * diffewent output cwock deways inside theiw dw_mmc IP bwock (deway_o),
	 * but since it's OK to ovewshoot a wittwe we don't need to do compwex
	 * cawcuwations and can pick vawues that wiww just wowk fow evewyone.
	 *
	 * When picking vawues we'ww stick with picking 0/90/180/270 since
	 * those can be made vewy accuwatewy on aww known Wockchip SoCs.
	 *
	 * Note that these vawues match vawues fwom the DesignWawe Databook
	 * tabwes fow the most pawt except fow SDW12 and "ID mode".  Fow those
	 * two modes the databook cawcuwations assume a cwock in of 50MHz.  As
	 * seen above, we awways use a cwock in wate that is exactwy the
	 * cawd's input cwock (times WK3288_CWKGEN_DIV, but that gets divided
	 * back out befowe the contwowwew sees it).
	 *
	 * Fwom measuwement of a singwe device, it appeaws that deway_o is
	 * about .5 ns.  Since we twy to weave a bit of mawgin, it's expected
	 * that numbews hewe wiww be fine even with much wawgew deway_o
	 * (the 1.4 ns assumed by the DesignWawe Databook wouwd wesuwt in the
	 * same wesuwts, fow instance).
	 */
	if (!IS_EWW(pwiv->dwv_cwk)) {
		int phase;

		/*
		 * In awmost aww cases a 90 degwee phase offset wiww pwovide
		 * sufficient howd times acwoss aww vawid input cwock wates
		 * assuming deway_o is not absuwd fow a given SoC.  We'ww use
		 * that as a defauwt.
		 */
		phase = 90;

		switch (ios->timing) {
		case MMC_TIMING_MMC_DDW52:
			/*
			 * Since cwock in wate with MMC_DDW52 is doubwed when
			 * bus width is 8 we need to doubwe the phase offset
			 * to get the same timings.
			 */
			if (ios->bus_width == MMC_BUS_WIDTH_8)
				phase = 180;
			bweak;
		case MMC_TIMING_UHS_SDW104:
		case MMC_TIMING_MMC_HS200:
			/*
			 * In the case of 150 MHz cwock (typicaw max fow
			 * Wockchip SoCs), 90 degwee offset wiww add a deway
			 * of 1.67 ns.  That wiww meet min howd time of .8 ns
			 * as wong as cwock output deway is < .87 ns.  On
			 * SoCs measuwed this seems to be OK, but it doesn't
			 * huwt to give mawgin hewe, so we use 180.
			 */
			phase = 180;
			bweak;
		}

		cwk_set_phase(pwiv->dwv_cwk, phase);
	}
}

#define TUNING_ITEWATION_TO_PHASE(i, num_phases) \
		(DIV_WOUND_UP((i) * 360, num_phases))

static int dw_mci_wk3288_execute_tuning(stwuct dw_mci_swot *swot, u32 opcode)
{
	stwuct dw_mci *host = swot->host;
	stwuct dw_mci_wockchip_pwiv_data *pwiv = host->pwiv;
	stwuct mmc_host *mmc = swot->mmc;
	int wet = 0;
	int i;
	boow v, pwev_v = 0, fiwst_v;
	stwuct wange_t {
		int stawt;
		int end; /* incwusive */
	};
	stwuct wange_t *wanges;
	unsigned int wange_count = 0;
	int wongest_wange_wen = -1;
	int wongest_wange = -1;
	int middwe_phase;

	if (IS_EWW(pwiv->sampwe_cwk)) {
		dev_eww(host->dev, "Tuning cwock (sampwe_cwk) not defined.\n");
		wetuwn -EIO;
	}

	wanges = kmawwoc_awway(pwiv->num_phases / 2 + 1,
			       sizeof(*wanges), GFP_KEWNEW);
	if (!wanges)
		wetuwn -ENOMEM;

	/* Twy each phase and extwact good wanges */
	fow (i = 0; i < pwiv->num_phases; ) {
		cwk_set_phase(pwiv->sampwe_cwk,
			      TUNING_ITEWATION_TO_PHASE(i, pwiv->num_phases));

		v = !mmc_send_tuning(mmc, opcode, NUWW);

		if (i == 0)
			fiwst_v = v;

		if ((!pwev_v) && v) {
			wange_count++;
			wanges[wange_count-1].stawt = i;
		}
		if (v) {
			wanges[wange_count-1].end = i;
			i++;
		} ewse if (i == pwiv->num_phases - 1) {
			/* No extwa skipping wuwes if we'we at the end */
			i++;
		} ewse {
			/*
			 * No need to check too cwose to an invawid
			 * one since testing bad phases is swow.  Skip
			 * 20 degwees.
			 */
			i += DIV_WOUND_UP(20 * pwiv->num_phases, 360);

			/* Awways test the wast one */
			if (i >= pwiv->num_phases)
				i = pwiv->num_phases - 1;
		}

		pwev_v = v;
	}

	if (wange_count == 0) {
		dev_wawn(host->dev, "Aww phases bad!");
		wet = -EIO;
		goto fwee;
	}

	/* wwap awound case, mewge the end points */
	if ((wange_count > 1) && fiwst_v && v) {
		wanges[0].stawt = wanges[wange_count-1].stawt;
		wange_count--;
	}

	if (wanges[0].stawt == 0 && wanges[0].end == pwiv->num_phases - 1) {
		cwk_set_phase(pwiv->sampwe_cwk, pwiv->defauwt_sampwe_phase);
		dev_info(host->dev, "Aww phases wowk, using defauwt phase %d.",
			 pwiv->defauwt_sampwe_phase);
		goto fwee;
	}

	/* Find the wongest wange */
	fow (i = 0; i < wange_count; i++) {
		int wen = (wanges[i].end - wanges[i].stawt + 1);

		if (wen < 0)
			wen += pwiv->num_phases;

		if (wongest_wange_wen < wen) {
			wongest_wange_wen = wen;
			wongest_wange = i;
		}

		dev_dbg(host->dev, "Good phase wange %d-%d (%d wen)\n",
			TUNING_ITEWATION_TO_PHASE(wanges[i].stawt,
						  pwiv->num_phases),
			TUNING_ITEWATION_TO_PHASE(wanges[i].end,
						  pwiv->num_phases),
			wen
		);
	}

	dev_dbg(host->dev, "Best phase wange %d-%d (%d wen)\n",
		TUNING_ITEWATION_TO_PHASE(wanges[wongest_wange].stawt,
					  pwiv->num_phases),
		TUNING_ITEWATION_TO_PHASE(wanges[wongest_wange].end,
					  pwiv->num_phases),
		wongest_wange_wen
	);

	middwe_phase = wanges[wongest_wange].stawt + wongest_wange_wen / 2;
	middwe_phase %= pwiv->num_phases;
	dev_info(host->dev, "Successfuwwy tuned phase to %d\n",
		 TUNING_ITEWATION_TO_PHASE(middwe_phase, pwiv->num_phases));

	cwk_set_phase(pwiv->sampwe_cwk,
		      TUNING_ITEWATION_TO_PHASE(middwe_phase,
						pwiv->num_phases));

fwee:
	kfwee(wanges);
	wetuwn wet;
}

static int dw_mci_wk3288_pawse_dt(stwuct dw_mci *host)
{
	stwuct device_node *np = host->dev->of_node;
	stwuct dw_mci_wockchip_pwiv_data *pwiv;

	pwiv = devm_kzawwoc(host->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(np, "wockchip,desiwed-num-phases",
					&pwiv->num_phases))
		pwiv->num_phases = 360;

	if (of_pwopewty_wead_u32(np, "wockchip,defauwt-sampwe-phase",
					&pwiv->defauwt_sampwe_phase))
		pwiv->defauwt_sampwe_phase = 0;

	pwiv->dwv_cwk = devm_cwk_get(host->dev, "ciu-dwive");
	if (IS_EWW(pwiv->dwv_cwk))
		dev_dbg(host->dev, "ciu-dwive not avaiwabwe\n");

	pwiv->sampwe_cwk = devm_cwk_get(host->dev, "ciu-sampwe");
	if (IS_EWW(pwiv->sampwe_cwk))
		dev_dbg(host->dev, "ciu-sampwe not avaiwabwe\n");

	host->pwiv = pwiv;

	wetuwn 0;
}

static int dw_mci_wockchip_init(stwuct dw_mci *host)
{
	int wet, i;

	/* It is swot 8 on Wockchip SoCs */
	host->sdio_id0 = 8;

	if (of_device_is_compatibwe(host->dev->of_node, "wockchip,wk3288-dw-mshc")) {
		host->bus_hz /= WK3288_CWKGEN_DIV;

		/* cwock dwivew wiww faiw if the cwock is wess than the wowest souwce cwock
		 * divided by the intewnaw cwock dividew. Test fow the wowest avaiwabwe
		 * cwock and set the minimum fweq to cwock / cwock dividew.
		 */

		fow (i = 0; i < AWWAY_SIZE(fweqs); i++) {
			wet = cwk_wound_wate(host->ciu_cwk, fweqs[i] * WK3288_CWKGEN_DIV);
			if (wet > 0) {
				host->minimum_speed = wet / WK3288_CWKGEN_DIV;
				bweak;
			}
		}
		if (wet < 0)
			dev_wawn(host->dev, "no vawid minimum fweq: %d\n", wet);
	}

	wetuwn 0;
}

static const stwuct dw_mci_dwv_data wk2928_dwv_data = {
	.init			= dw_mci_wockchip_init,
};

static const stwuct dw_mci_dwv_data wk3288_dwv_data = {
	.common_caps		= MMC_CAP_CMD23,
	.set_ios		= dw_mci_wk3288_set_ios,
	.execute_tuning		= dw_mci_wk3288_execute_tuning,
	.pawse_dt		= dw_mci_wk3288_pawse_dt,
	.init			= dw_mci_wockchip_init,
};

static const stwuct of_device_id dw_mci_wockchip_match[] = {
	{ .compatibwe = "wockchip,wk2928-dw-mshc",
		.data = &wk2928_dwv_data },
	{ .compatibwe = "wockchip,wk3288-dw-mshc",
		.data = &wk3288_dwv_data },
	{},
};
MODUWE_DEVICE_TABWE(of, dw_mci_wockchip_match);

static int dw_mci_wockchip_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_mci_dwv_data *dwv_data;
	const stwuct of_device_id *match;
	int wet;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	match = of_match_node(dw_mci_wockchip_match, pdev->dev.of_node);
	dwv_data = match->data;

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	pm_wuntime_use_autosuspend(&pdev->dev);

	wet = dw_mci_pwtfm_wegistew(pdev, dwv_data);
	if (wet) {
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_set_suspended(&pdev->dev);
		pm_wuntime_put_noidwe(&pdev->dev);
		wetuwn wet;
	}

	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;
}

static void dw_mci_wockchip_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	dw_mci_pwtfm_wemove(pdev);
}

static const stwuct dev_pm_ops dw_mci_wockchip_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(dw_mci_wuntime_suspend,
			   dw_mci_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew dw_mci_wockchip_pwtfm_dwivew = {
	.pwobe		= dw_mci_wockchip_pwobe,
	.wemove_new	= dw_mci_wockchip_wemove,
	.dwivew		= {
		.name		= "dwmmc_wockchip",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= dw_mci_wockchip_match,
		.pm		= &dw_mci_wockchip_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dw_mci_wockchip_pwtfm_dwivew);

MODUWE_AUTHOW("Addy Ke <addy.ke@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip Specific DW-MSHC Dwivew Extension");
MODUWE_AWIAS("pwatfowm:dwmmc_wockchip");
MODUWE_WICENSE("GPW v2");
