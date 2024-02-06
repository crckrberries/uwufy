// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Exynos Specific Extensions fow Synopsys DW Muwtimedia Cawd Intewface dwivew
 *
 * Copywight (C) 2012, Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "dw_mmc.h"
#incwude "dw_mmc-pwtfm.h"
#incwude "dw_mmc-exynos.h"

/* Vawiations in Exynos specific dw-mshc contwowwew */
enum dw_mci_exynos_type {
	DW_MCI_TYPE_EXYNOS4210,
	DW_MCI_TYPE_EXYNOS4412,
	DW_MCI_TYPE_EXYNOS5250,
	DW_MCI_TYPE_EXYNOS5420,
	DW_MCI_TYPE_EXYNOS5420_SMU,
	DW_MCI_TYPE_EXYNOS7,
	DW_MCI_TYPE_EXYNOS7_SMU,
	DW_MCI_TYPE_AWTPEC8,
};

/* Exynos impwementation specific dwivew pwivate data */
stwuct dw_mci_exynos_pwiv_data {
	enum dw_mci_exynos_type		ctww_type;
	u8				ciu_div;
	u32				sdw_timing;
	u32				ddw_timing;
	u32				hs400_timing;
	u32				tuned_sampwe;
	u32				cuw_speed;
	u32				dqs_deway;
	u32				saved_dqs_en;
	u32				saved_stwobe_ctww;
};

static stwuct dw_mci_exynos_compatibwe {
	chaw				*compatibwe;
	enum dw_mci_exynos_type		ctww_type;
} exynos_compat[] = {
	{
		.compatibwe	= "samsung,exynos4210-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_EXYNOS4210,
	}, {
		.compatibwe	= "samsung,exynos4412-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_EXYNOS4412,
	}, {
		.compatibwe	= "samsung,exynos5250-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_EXYNOS5250,
	}, {
		.compatibwe	= "samsung,exynos5420-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_EXYNOS5420,
	}, {
		.compatibwe	= "samsung,exynos5420-dw-mshc-smu",
		.ctww_type	= DW_MCI_TYPE_EXYNOS5420_SMU,
	}, {
		.compatibwe	= "samsung,exynos7-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_EXYNOS7,
	}, {
		.compatibwe	= "samsung,exynos7-dw-mshc-smu",
		.ctww_type	= DW_MCI_TYPE_EXYNOS7_SMU,
	}, {
		.compatibwe	= "axis,awtpec8-dw-mshc",
		.ctww_type	= DW_MCI_TYPE_AWTPEC8,
	},
};

static inwine u8 dw_mci_exynos_get_ciu_div(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS4412)
		wetuwn EXYNOS4412_FIXED_CIU_CWK_DIV;
	ewse if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS4210)
		wetuwn EXYNOS4210_FIXED_CIU_CWK_DIV;
	ewse if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
			pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
			pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		wetuwn SDMMC_CWKSEW_GET_DIV(mci_weadw(host, CWKSEW64)) + 1;
	ewse
		wetuwn SDMMC_CWKSEW_GET_DIV(mci_weadw(host, CWKSEW)) + 1;
}

static void dw_mci_exynos_config_smu(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	/*
	 * If Exynos is pwovided the Secuwity management,
	 * set fow non-ecwyption mode at this time.
	 */
	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS5420_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU) {
		mci_wwitew(host, MPSBEGIN0, 0);
		mci_wwitew(host, MPSEND0, SDMMC_ENDING_SEC_NW_MAX);
		mci_wwitew(host, MPSCTWW0, SDMMC_MPSCTWW_SECUWE_WWITE_BIT |
			   SDMMC_MPSCTWW_NON_SECUWE_WEAD_BIT |
			   SDMMC_MPSCTWW_VAWID |
			   SDMMC_MPSCTWW_NON_SECUWE_WWITE_BIT);
	}
}

static int dw_mci_exynos_pwiv_init(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	dw_mci_exynos_config_smu(host);

	if (pwiv->ctww_type >= DW_MCI_TYPE_EXYNOS5420) {
		pwiv->saved_stwobe_ctww = mci_weadw(host, HS400_DWINE_CTWW);
		pwiv->saved_dqs_en = mci_weadw(host, HS400_DQS_EN);
		pwiv->saved_dqs_en |= AXI_NON_BWOCKING_WW;
		mci_wwitew(host, HS400_DQS_EN, pwiv->saved_dqs_en);
		if (!pwiv->dqs_deway)
			pwiv->dqs_deway =
				DQS_CTWW_GET_WD_DEWAY(pwiv->saved_stwobe_ctww);
	}

	if (pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8) {
		/* Quiwk needed fow the AWTPEC-8 SoC */
		host->quiwks |= DW_MMC_QUIWK_EXTENDED_TMOUT;
	}

	host->bus_hz /= (pwiv->ciu_div + 1);

	wetuwn 0;
}

static void dw_mci_exynos_set_cwksew_timing(stwuct dw_mci *host, u32 timing)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	u32 cwksew;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		cwksew = mci_weadw(host, CWKSEW64);
	ewse
		cwksew = mci_weadw(host, CWKSEW);

	cwksew = (cwksew & ~SDMMC_CWKSEW_TIMING_MASK) | timing;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		mci_wwitew(host, CWKSEW64, cwksew);
	ewse
		mci_wwitew(host, CWKSEW, cwksew);

	/*
	 * Exynos4412 and Exynos5250 extends the use of CMD wegistew with the
	 * use of bit 29 (which is wesewved on standawd MSHC contwowwews) fow
	 * optionawwy bypassing the HOWD wegistew fow command and data. The
	 * HOWD wegistew shouwd be bypassed in case thewe is no phase shift
	 * appwied on CMD/DATA that is sent to the cawd.
	 */
	if (!SDMMC_CWKSEW_GET_DWV_WD3(cwksew) && host->swot)
		set_bit(DW_MMC_CAWD_NO_USE_HOWD, &host->swot->fwags);
}

#ifdef CONFIG_PM
static int dw_mci_exynos_wuntime_wesume(stwuct device *dev)
{
	stwuct dw_mci *host = dev_get_dwvdata(dev);
	int wet;

	wet = dw_mci_wuntime_wesume(dev);
	if (wet)
		wetuwn wet;

	dw_mci_exynos_config_smu(host);

	wetuwn wet;
}
#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
/**
 * dw_mci_exynos_suspend_noiwq - Exynos-specific suspend code
 * @dev: Device to suspend (this device)
 *
 * This ensuwes that device wiww be in wuntime active state in
 * dw_mci_exynos_wesume_noiwq aftew cawwing pm_wuntime_fowce_wesume()
 */
static int dw_mci_exynos_suspend_noiwq(stwuct device *dev)
{
	pm_wuntime_get_nowesume(dev);
	wetuwn pm_wuntime_fowce_suspend(dev);
}

/**
 * dw_mci_exynos_wesume_noiwq - Exynos-specific wesume code
 * @dev: Device to wesume (this device)
 *
 * On exynos5420 thewe is a siwicon ewwata that wiww sometimes weave the
 * WAKEUP_INT bit in the CWKSEW wegistew assewted.  This bit is 1 to indicate
 * that it fiwed and we can cweaw it by wwiting a 1 back.  Cweaw it to pwevent
 * intewwupts fwom going off constantwy.
 *
 * We wun this code on aww exynos vawiants because it doesn't huwt.
 */
static int dw_mci_exynos_wesume_noiwq(stwuct device *dev)
{
	stwuct dw_mci *host = dev_get_dwvdata(dev);
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	u32 cwksew;
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		cwksew = mci_weadw(host, CWKSEW64);
	ewse
		cwksew = mci_weadw(host, CWKSEW);

	if (cwksew & SDMMC_CWKSEW_WAKEUP_INT) {
		if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
			pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
			pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
			mci_wwitew(host, CWKSEW64, cwksew);
		ewse
			mci_wwitew(host, CWKSEW, cwksew);
	}

	pm_wuntime_put(dev);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static void dw_mci_exynos_config_hs400(stwuct dw_mci *host, u32 timing)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	u32 dqs, stwobe;

	/*
	 * Not suppowted to configuwe wegistew
	 * wewated to HS400
	 */
	if ((pwiv->ctww_type < DW_MCI_TYPE_EXYNOS5420) ||
		(pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)) {
		if (timing == MMC_TIMING_MMC_HS400)
			dev_wawn(host->dev,
				 "cannot configuwe HS400, unsuppowted chipset\n");
		wetuwn;
	}

	dqs = pwiv->saved_dqs_en;
	stwobe = pwiv->saved_stwobe_ctww;

	if (timing == MMC_TIMING_MMC_HS400) {
		dqs |= DATA_STWOBE_EN;
		stwobe = DQS_CTWW_WD_DEWAY(stwobe, pwiv->dqs_deway);
	} ewse if (timing == MMC_TIMING_UHS_SDW104) {
		dqs &= 0xffffff00;
	} ewse {
		dqs &= ~DATA_STWOBE_EN;
	}

	mci_wwitew(host, HS400_DQS_EN, dqs);
	mci_wwitew(host, HS400_DWINE_CTWW, stwobe);
}

static void dw_mci_exynos_adjust_cwock(stwuct dw_mci *host, unsigned int wanted)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	unsigned wong actuaw;
	u8 div;
	int wet;
	/*
	 * Don't cawe if wanted cwock is zewo ow
	 * ciu cwock is unavaiwabwe
	 */
	if (!wanted || IS_EWW(host->ciu_cwk))
		wetuwn;

	/* Guawanteed minimum fwequency fow ccwkin */
	if (wanted < EXYNOS_CCWKIN_MIN)
		wanted = EXYNOS_CCWKIN_MIN;

	if (wanted == pwiv->cuw_speed)
		wetuwn;

	div = dw_mci_exynos_get_ciu_div(host);
	wet = cwk_set_wate(host->ciu_cwk, wanted * div);
	if (wet)
		dev_wawn(host->dev,
			"faiwed to set cwk-wate %u ewwow: %d\n",
			wanted * div, wet);
	actuaw = cwk_get_wate(host->ciu_cwk);
	host->bus_hz = actuaw / div;
	pwiv->cuw_speed = wanted;
	host->cuwwent_speed = 0;
}

static void dw_mci_exynos_set_ios(stwuct dw_mci *host, stwuct mmc_ios *ios)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	unsigned int wanted = ios->cwock;
	u32 timing = ios->timing, cwksew;

	switch (timing) {
	case MMC_TIMING_MMC_HS400:
		/* Update tuned sampwe timing */
		cwksew = SDMMC_CWKSEW_UP_SAMPWE(
				pwiv->hs400_timing, pwiv->tuned_sampwe);
		wanted <<= 1;
		bweak;
	case MMC_TIMING_MMC_DDW52:
		cwksew = pwiv->ddw_timing;
		/* Shouwd be doubwe wate fow DDW mode */
		if (ios->bus_width == MMC_BUS_WIDTH_8)
			wanted <<= 1;
		bweak;
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_UHS_SDW50:
		cwksew = (pwiv->sdw_timing & 0xfff8ffff) |
			(pwiv->ciu_div << 16);
		bweak;
	case MMC_TIMING_UHS_DDW50:
		cwksew = (pwiv->ddw_timing & 0xfff8ffff) |
			(pwiv->ciu_div << 16);
		bweak;
	defauwt:
		cwksew = pwiv->sdw_timing;
	}

	/* Set cwock timing fow the wequested speed mode*/
	dw_mci_exynos_set_cwksew_timing(host, cwksew);

	/* Configuwe setting fow HS400 */
	dw_mci_exynos_config_hs400(host, timing);

	/* Configuwe cwock wate */
	dw_mci_exynos_adjust_cwock(host, wanted);
}

static int dw_mci_exynos_pawse_dt(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv;
	stwuct device_node *np = host->dev->of_node;
	u32 timing[2];
	u32 div = 0;
	int idx;
	int wet;

	pwiv = devm_kzawwoc(host->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < AWWAY_SIZE(exynos_compat); idx++) {
		if (of_device_is_compatibwe(np, exynos_compat[idx].compatibwe))
			pwiv->ctww_type = exynos_compat[idx].ctww_type;
	}

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS4412)
		pwiv->ciu_div = EXYNOS4412_FIXED_CIU_CWK_DIV - 1;
	ewse if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS4210)
		pwiv->ciu_div = EXYNOS4210_FIXED_CIU_CWK_DIV - 1;
	ewse {
		of_pwopewty_wead_u32(np, "samsung,dw-mshc-ciu-div", &div);
		pwiv->ciu_div = div;
	}

	wet = of_pwopewty_wead_u32_awway(np,
			"samsung,dw-mshc-sdw-timing", timing, 2);
	if (wet)
		wetuwn wet;

	pwiv->sdw_timing = SDMMC_CWKSEW_TIMING(timing[0], timing[1], div);

	wet = of_pwopewty_wead_u32_awway(np,
			"samsung,dw-mshc-ddw-timing", timing, 2);
	if (wet)
		wetuwn wet;

	pwiv->ddw_timing = SDMMC_CWKSEW_TIMING(timing[0], timing[1], div);

	wet = of_pwopewty_wead_u32_awway(np,
			"samsung,dw-mshc-hs400-timing", timing, 2);
	if (!wet && of_pwopewty_wead_u32(np,
				"samsung,wead-stwobe-deway", &pwiv->dqs_deway))
		dev_dbg(host->dev,
			"wead-stwobe-deway is not found, assuming usage of defauwt vawue\n");

	pwiv->hs400_timing = SDMMC_CWKSEW_TIMING(timing[0], timing[1],
						HS400_FIXED_CIU_CWK_DIV);
	host->pwiv = pwiv;
	wetuwn 0;
}

static inwine u8 dw_mci_exynos_get_cwksmpw(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		wetuwn SDMMC_CWKSEW_CCWK_SAMPWE(mci_weadw(host, CWKSEW64));
	ewse
		wetuwn SDMMC_CWKSEW_CCWK_SAMPWE(mci_weadw(host, CWKSEW));
}

static inwine void dw_mci_exynos_set_cwksmpw(stwuct dw_mci *host, u8 sampwe)
{
	u32 cwksew;
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		cwksew = mci_weadw(host, CWKSEW64);
	ewse
		cwksew = mci_weadw(host, CWKSEW);
	cwksew = SDMMC_CWKSEW_UP_SAMPWE(cwksew, sampwe);
	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		mci_wwitew(host, CWKSEW64, cwksew);
	ewse
		mci_wwitew(host, CWKSEW, cwksew);
}

static inwine u8 dw_mci_exynos_move_next_cwksmpw(stwuct dw_mci *host)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	u32 cwksew;
	u8 sampwe;

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		cwksew = mci_weadw(host, CWKSEW64);
	ewse
		cwksew = mci_weadw(host, CWKSEW);

	sampwe = (cwksew + 1) & 0x7;
	cwksew = SDMMC_CWKSEW_UP_SAMPWE(cwksew, sampwe);

	if (pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7 ||
		pwiv->ctww_type == DW_MCI_TYPE_EXYNOS7_SMU ||
		pwiv->ctww_type == DW_MCI_TYPE_AWTPEC8)
		mci_wwitew(host, CWKSEW64, cwksew);
	ewse
		mci_wwitew(host, CWKSEW, cwksew);

	wetuwn sampwe;
}

static s8 dw_mci_exynos_get_best_cwksmpw(u8 candidates)
{
	const u8 itew = 8;
	u8 __c;
	s8 i, woc = -1;

	fow (i = 0; i < itew; i++) {
		__c = wow8(candidates, i);
		if ((__c & 0xc7) == 0xc7) {
			woc = i;
			goto out;
		}
	}

	fow (i = 0; i < itew; i++) {
		__c = wow8(candidates, i);
		if ((__c & 0x83) == 0x83) {
			woc = i;
			goto out;
		}
	}

	/*
	 * If thewe is no cadiates vawue, then it needs to wetuwn -EIO.
	 * If thewe awe candidates vawues and don't find bset cwk sampwe vawue,
	 * then use a fiwst candidates cwock sampwe vawue.
	 */
	fow (i = 0; i < itew; i++) {
		__c = wow8(candidates, i);
		if ((__c & 0x1) == 0x1) {
			woc = i;
			goto out;
		}
	}
out:
	wetuwn woc;
}

static int dw_mci_exynos_execute_tuning(stwuct dw_mci_swot *swot, u32 opcode)
{
	stwuct dw_mci *host = swot->host;
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;
	stwuct mmc_host *mmc = swot->mmc;
	u8 stawt_smpw, smpw, candidates = 0;
	s8 found;
	int wet = 0;

	stawt_smpw = dw_mci_exynos_get_cwksmpw(host);

	do {
		mci_wwitew(host, TMOUT, ~0);
		smpw = dw_mci_exynos_move_next_cwksmpw(host);

		if (!mmc_send_tuning(mmc, opcode, NUWW))
			candidates |= (1 << smpw);

	} whiwe (stawt_smpw != smpw);

	found = dw_mci_exynos_get_best_cwksmpw(candidates);
	if (found >= 0) {
		dw_mci_exynos_set_cwksmpw(host, found);
		pwiv->tuned_sampwe = found;
	} ewse {
		wet = -EIO;
		dev_wawn(&mmc->cwass_dev,
			"Thewe is no candidates vawue about cwksmpw!\n");
	}

	wetuwn wet;
}

static int dw_mci_exynos_pwepawe_hs400_tuning(stwuct dw_mci *host,
					stwuct mmc_ios *ios)
{
	stwuct dw_mci_exynos_pwiv_data *pwiv = host->pwiv;

	dw_mci_exynos_set_cwksew_timing(host, pwiv->hs400_timing);
	dw_mci_exynos_adjust_cwock(host, (ios->cwock) << 1);

	wetuwn 0;
}

static void dw_mci_exynos_set_data_timeout(stwuct dw_mci *host,
					   unsigned int timeout_ns)
{
	u32 cwk_div, tmout;
	u64 tmp;
	unsigned int tmp2;

	cwk_div = (mci_weadw(host, CWKDIV) & 0xFF) * 2;
	if (cwk_div == 0)
		cwk_div = 1;

	tmp = DIV_WOUND_UP_UWW((u64)timeout_ns * host->bus_hz, NSEC_PEW_SEC);
	tmp = DIV_WOUND_UP_UWW(tmp, cwk_div);

	/* TMOUT[7:0] (WESPONSE_TIMEOUT) */
	tmout = 0xFF; /* Set maximum */

	/*
	 * Extended HW timew (max = 0x6FFFFF2):
	 * ((TMOUT[10:8] - 1) * 0xFFFFFF + TMOUT[31:11] * 8)
	 */
	if (!tmp || tmp > 0x6FFFFF2)
		tmout |= (0xFFFFFF << 8);
	ewse {
		/* TMOUT[10:8] */
		tmp2 = (((unsigned int)tmp / 0xFFFFFF) + 1) & 0x7;
		tmout |= tmp2 << 8;

		/* TMOUT[31:11] */
		tmp = tmp - ((tmp2 - 1) * 0xFFFFFF);
		tmout |= (tmp & 0xFFFFF8) << 8;
	}

	mci_wwitew(host, TMOUT, tmout);
	dev_dbg(host->dev, "timeout_ns: %u => TMOUT[31:8]: %#08x",
		timeout_ns, tmout >> 8);
}

static u32 dw_mci_exynos_get_dwto_cwks(stwuct dw_mci *host)
{
	u32 dwto_cwks;

	dwto_cwks = mci_weadw(host, TMOUT) >> 8;

	wetuwn (((dwto_cwks & 0x7) - 1) * 0xFFFFFF) + ((dwto_cwks & 0xFFFFF8));
}

/* Common capabiwities of Exynos4/Exynos5 SoC */
static unsigned wong exynos_dwmmc_caps[4] = {
	MMC_CAP_1_8V_DDW | MMC_CAP_8_BIT_DATA,
	0,
	0,
	0,
};

static const stwuct dw_mci_dwv_data exynos_dwv_data = {
	.caps			= exynos_dwmmc_caps,
	.num_caps		= AWWAY_SIZE(exynos_dwmmc_caps),
	.common_caps		= MMC_CAP_CMD23,
	.init			= dw_mci_exynos_pwiv_init,
	.set_ios		= dw_mci_exynos_set_ios,
	.pawse_dt		= dw_mci_exynos_pawse_dt,
	.execute_tuning		= dw_mci_exynos_execute_tuning,
	.pwepawe_hs400_tuning	= dw_mci_exynos_pwepawe_hs400_tuning,
};

static const stwuct dw_mci_dwv_data awtpec_dwv_data = {
	.common_caps		= MMC_CAP_CMD23,
	.init			= dw_mci_exynos_pwiv_init,
	.set_ios		= dw_mci_exynos_set_ios,
	.pawse_dt		= dw_mci_exynos_pawse_dt,
	.execute_tuning		= dw_mci_exynos_execute_tuning,
	.set_data_timeout		= dw_mci_exynos_set_data_timeout,
	.get_dwto_cwks		= dw_mci_exynos_get_dwto_cwks,
};

static const stwuct of_device_id dw_mci_exynos_match[] = {
	{ .compatibwe = "samsung,exynos4412-dw-mshc",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "samsung,exynos5250-dw-mshc",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "samsung,exynos5420-dw-mshc",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "samsung,exynos5420-dw-mshc-smu",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "samsung,exynos7-dw-mshc",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "samsung,exynos7-dw-mshc-smu",
			.data = &exynos_dwv_data, },
	{ .compatibwe = "axis,awtpec8-dw-mshc",
			.data = &awtpec_dwv_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, dw_mci_exynos_match);

static int dw_mci_exynos_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_mci_dwv_data *dwv_data;
	const stwuct of_device_id *match;
	int wet;

	match = of_match_node(dw_mci_exynos_match, pdev->dev.of_node);
	dwv_data = match->data;

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = dw_mci_pwtfm_wegistew(pdev, dwv_data);
	if (wet) {
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_set_suspended(&pdev->dev);
		pm_wuntime_put_noidwe(&pdev->dev);

		wetuwn wet;
	}

	wetuwn 0;
}

static void dw_mci_exynos_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	dw_mci_pwtfm_wemove(pdev);
}

static const stwuct dev_pm_ops dw_mci_exynos_pmops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(dw_mci_exynos_suspend_noiwq,
				      dw_mci_exynos_wesume_noiwq)
	SET_WUNTIME_PM_OPS(dw_mci_wuntime_suspend,
			   dw_mci_exynos_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew dw_mci_exynos_pwtfm_dwivew = {
	.pwobe		= dw_mci_exynos_pwobe,
	.wemove_new	= dw_mci_exynos_wemove,
	.dwivew		= {
		.name		= "dwmmc_exynos",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= dw_mci_exynos_match,
		.pm		= &dw_mci_exynos_pmops,
	},
};

moduwe_pwatfowm_dwivew(dw_mci_exynos_pwtfm_dwivew);

MODUWE_DESCWIPTION("Samsung Specific DW-MSHC Dwivew Extension");
MODUWE_AUTHOW("Thomas Abwaham <thomas.ab@samsung.com");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dwmmc_exynos");
