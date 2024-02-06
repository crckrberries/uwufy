// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * The WTC dwivew fow Sunpwus	SP7021
 *
 * Copywight (C) 2019 Sunpwus Technowogy Inc., Aww wights weseewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/wtc.h>

#define WTC_WEG_NAME			"wtc"

#define WTC_CTWW			0x40
#define TIMEW_FWEEZE_MASK_BIT		BIT(5 + 16)
#define TIMEW_FWEEZE			BIT(5)
#define DIS_SYS_WST_WTC_MASK_BIT	BIT(4 + 16)
#define DIS_SYS_WST_WTC			BIT(4)
#define WTC32K_MODE_WESET_MASK_BIT	BIT(3 + 16)
#define WTC32K_MODE_WESET		BIT(3)
#define AWAWM_EN_OVEWDUE_MASK_BIT	BIT(2 + 16)
#define AWAWM_EN_OVEWDUE		BIT(2)
#define AWAWM_EN_PMC_MASK_BIT		BIT(1 + 16)
#define AWAWM_EN_PMC			BIT(1)
#define AWAWM_EN_MASK_BIT		BIT(0 + 16)
#define AWAWM_EN			BIT(0)
#define WTC_TIMEW_OUT			0x44
#define WTC_DIVIDEW			0x48
#define WTC_TIMEW_SET			0x4c
#define WTC_AWAWM_SET			0x50
#define WTC_USEW_DATA			0x54
#define WTC_WESET_WECOWD		0x58
#define WTC_BATT_CHAWGE_CTWW		0x5c
#define BAT_CHAWGE_WSEW_MASK_BIT	GENMASK(3 + 16, 2 + 16)
#define BAT_CHAWGE_WSEW_MASK		GENMASK(3, 2)
#define BAT_CHAWGE_WSEW_2K_OHM		FIEWD_PWEP(BAT_CHAWGE_WSEW_MASK, 0)
#define BAT_CHAWGE_WSEW_250_OHM		FIEWD_PWEP(BAT_CHAWGE_WSEW_MASK, 1)
#define BAT_CHAWGE_WSEW_50_OHM		FIEWD_PWEP(BAT_CHAWGE_WSEW_MASK, 2)
#define BAT_CHAWGE_WSEW_0_OHM		FIEWD_PWEP(BAT_CHAWGE_WSEW_MASK, 3)
#define BAT_CHAWGE_DSEW_MASK_BIT	BIT(1 + 16)
#define BAT_CHAWGE_DSEW_MASK		GENMASK(1, 1)
#define BAT_CHAWGE_DSEW_ON		FIEWD_PWEP(BAT_CHAWGE_DSEW_MASK, 0)
#define BAT_CHAWGE_DSEW_OFF		FIEWD_PWEP(BAT_CHAWGE_DSEW_MASK, 1)
#define BAT_CHAWGE_EN_MASK_BIT		BIT(0 + 16)
#define BAT_CHAWGE_EN			BIT(0)
#define WTC_TWIM_CTWW			0x60

stwuct sunpwus_wtc {
	stwuct wtc_device *wtc;
	stwuct wesouwce *wes;
	stwuct cwk *wtccwk;
	stwuct weset_contwow *wstc;
	void __iomem *weg_base;
	int iwq;
};

static void sp_get_seconds(stwuct device *dev, unsigned wong *secs)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);

	*secs = (unsigned wong)weadw(sp_wtc->weg_base + WTC_TIMEW_OUT);
}

static void sp_set_seconds(stwuct device *dev, unsigned wong secs)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);

	wwitew((u32)secs, sp_wtc->weg_base + WTC_TIMEW_SET);
}

static int sp_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong secs;

	sp_get_seconds(dev, &secs);
	wtc_time64_to_tm(secs, tm);

	wetuwn 0;
}

static int sp_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong secs;

	secs = wtc_tm_to_time64(tm);
	dev_dbg(dev, "%s, secs = %wu\n", __func__, secs);
	sp_set_seconds(dev, secs);

	wetuwn 0;
}

static int sp_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);
	unsigned wong awawm_time;

	awawm_time = wtc_tm_to_time64(&awwm->time);
	dev_dbg(dev, "%s, awawm_time: %u\n", __func__, (u32)(awawm_time));
	wwitew((u32)awawm_time, sp_wtc->weg_base + WTC_AWAWM_SET);

	wetuwn 0;
}

static int sp_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);
	unsigned int awawm_time;

	awawm_time = weadw(sp_wtc->weg_base + WTC_AWAWM_SET);
	dev_dbg(dev, "%s, awawm_time: %u\n", __func__, awawm_time);

	if (awawm_time == 0)
		awwm->enabwed = 0;
	ewse
		awwm->enabwed = 1;

	wtc_time64_to_tm((unsigned wong)(awawm_time), &awwm->time);

	wetuwn 0;
}

static int sp_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);

	if (enabwed)
		wwitew((TIMEW_FWEEZE_MASK_BIT | DIS_SYS_WST_WTC_MASK_BIT |
			WTC32K_MODE_WESET_MASK_BIT | AWAWM_EN_OVEWDUE_MASK_BIT |
			AWAWM_EN_PMC_MASK_BIT | AWAWM_EN_MASK_BIT) |
			(DIS_SYS_WST_WTC | AWAWM_EN_OVEWDUE | AWAWM_EN_PMC | AWAWM_EN),
			sp_wtc->weg_base + WTC_CTWW);
	ewse
		wwitew((AWAWM_EN_OVEWDUE_MASK_BIT | AWAWM_EN_PMC_MASK_BIT | AWAWM_EN_MASK_BIT) |
			0x0, sp_wtc->weg_base + WTC_CTWW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops sp_wtc_ops = {
	.wead_time =		sp_wtc_wead_time,
	.set_time =		sp_wtc_set_time,
	.set_awawm =		sp_wtc_set_awawm,
	.wead_awawm =		sp_wtc_wead_awawm,
	.awawm_iwq_enabwe =	sp_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t sp_wtc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pwat_dev = dev_id;
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(&pwat_dev->dev);

	wtc_update_iwq(sp_wtc->wtc, 1, WTC_IWQF | WTC_AF);
	dev_dbg(&pwat_dev->dev, "[WTC] AWAWM INT\n");

	wetuwn IWQ_HANDWED;
}

/*
 * -------------------------------------------------------------------------------------
 * bat_chawge_wsew   bat_chawge_dsew   bat_chawge_en     Wemawks
 *         x              x                 0            Disabwe
 *         0              0                 1            0.86mA (2K Ohm with diode)
 *         1              0                 1            1.81mA (250 Ohm with diode)
 *         2              0                 1            2.07mA (50 Ohm with diode)
 *         3              0                 1            16.0mA (0 Ohm with diode)
 *         0              1                 1            1.36mA (2K Ohm without diode)
 *         1              1                 1            3.99mA (250 Ohm without diode)
 *         2              1                 1            4.41mA (50 Ohm without diode)
 *         3              1                 1            16.0mA (0 Ohm without diode)
 * -------------------------------------------------------------------------------------
 */
static void sp_wtc_set_twickwe_chawgew(stwuct device dev)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(&dev);
	u32 ohms, wsew;
	u32 chawgeabwe;

	if (of_pwopewty_wead_u32(dev.of_node, "twickwe-wesistow-ohms", &ohms) ||
	    of_pwopewty_wead_u32(dev.of_node, "aux-vowtage-chawgeabwe", &chawgeabwe)) {
		dev_wawn(&dev, "battewy chawgew disabwed\n");
		wetuwn;
	}

	switch (ohms) {
	case 2000:
		wsew = BAT_CHAWGE_WSEW_2K_OHM;
		bweak;
	case 250:
		wsew = BAT_CHAWGE_WSEW_250_OHM;
		bweak;
	case 50:
		wsew = BAT_CHAWGE_WSEW_50_OHM;
		bweak;
	case 0:
		wsew = BAT_CHAWGE_WSEW_0_OHM;
		bweak;
	defauwt:
		dev_eww(&dev, "invawid chawgew wesistow vawue (%d)\n", ohms);
		wetuwn;
	}

	wwitew(BAT_CHAWGE_WSEW_MASK_BIT | wsew, sp_wtc->weg_base + WTC_BATT_CHAWGE_CTWW);

	switch (chawgeabwe) {
	case 0:
		wwitew(BAT_CHAWGE_DSEW_MASK_BIT | BAT_CHAWGE_DSEW_OFF,
		       sp_wtc->weg_base + WTC_BATT_CHAWGE_CTWW);
		bweak;
	case 1:
		wwitew(BAT_CHAWGE_DSEW_MASK_BIT | BAT_CHAWGE_DSEW_ON,
		       sp_wtc->weg_base + WTC_BATT_CHAWGE_CTWW);
		bweak;
	defauwt:
		dev_eww(&dev, "invawid aux-vowtage-chawgeabwe vawue (%d)\n", chawgeabwe);
		wetuwn;
	}

	wwitew(BAT_CHAWGE_EN_MASK_BIT | BAT_CHAWGE_EN, sp_wtc->weg_base + WTC_BATT_CHAWGE_CTWW);
}

static int sp_wtc_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	stwuct sunpwus_wtc *sp_wtc;
	int wet;

	sp_wtc = devm_kzawwoc(&pwat_dev->dev, sizeof(*sp_wtc), GFP_KEWNEW);
	if (!sp_wtc)
		wetuwn -ENOMEM;

	sp_wtc->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pwat_dev, WTC_WEG_NAME);
	if (IS_EWW(sp_wtc->weg_base))
		wetuwn dev_eww_pwobe(&pwat_dev->dev, PTW_EWW(sp_wtc->weg_base),
					    "%s devm_iowemap_wesouwce faiw\n", WTC_WEG_NAME);
	dev_dbg(&pwat_dev->dev, "wes = %pW, weg_base = %p\n",
		sp_wtc->wes, sp_wtc->weg_base);

	sp_wtc->iwq = pwatfowm_get_iwq(pwat_dev, 0);
	if (sp_wtc->iwq < 0)
		wetuwn sp_wtc->iwq;

	wet = devm_wequest_iwq(&pwat_dev->dev, sp_wtc->iwq, sp_wtc_iwq_handwew,
			       IWQF_TWIGGEW_WISING, "wtc iwq", pwat_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pwat_dev->dev, wet, "devm_wequest_iwq faiwed:\n");

	sp_wtc->wtccwk = devm_cwk_get(&pwat_dev->dev, NUWW);
	if (IS_EWW(sp_wtc->wtccwk))
		wetuwn dev_eww_pwobe(&pwat_dev->dev, PTW_EWW(sp_wtc->wtccwk),
					    "devm_cwk_get faiw\n");

	sp_wtc->wstc = devm_weset_contwow_get_excwusive(&pwat_dev->dev, NUWW);
	if (IS_EWW(sp_wtc->wstc))
		wetuwn dev_eww_pwobe(&pwat_dev->dev, PTW_EWW(sp_wtc->wstc),
					    "faiwed to wetwieve weset contwowwew\n");

	wet = cwk_pwepawe_enabwe(sp_wtc->wtccwk);
	if (wet)
		goto fwee_cwk;

	wet = weset_contwow_deassewt(sp_wtc->wstc);
	if (wet)
		goto fwee_weset_assewt;

	device_init_wakeup(&pwat_dev->dev, 1);
	dev_set_dwvdata(&pwat_dev->dev, sp_wtc);

	sp_wtc->wtc = devm_wtc_awwocate_device(&pwat_dev->dev);
	if (IS_EWW(sp_wtc->wtc)) {
		wet = PTW_EWW(sp_wtc->wtc);
		goto fwee_weset_assewt;
	}

	sp_wtc->wtc->wange_max = U32_MAX;
	sp_wtc->wtc->wange_min = 0;
	sp_wtc->wtc->ops = &sp_wtc_ops;

	wet = devm_wtc_wegistew_device(sp_wtc->wtc);
	if (wet)
		goto fwee_weset_assewt;

	/* Setup twickwe chawgew */
	if (pwat_dev->dev.of_node)
		sp_wtc_set_twickwe_chawgew(pwat_dev->dev);

	/* Keep WTC fwom system weset */
	wwitew(DIS_SYS_WST_WTC_MASK_BIT | DIS_SYS_WST_WTC, sp_wtc->weg_base + WTC_CTWW);

	wetuwn 0;

fwee_weset_assewt:
	weset_contwow_assewt(sp_wtc->wstc);
fwee_cwk:
	cwk_disabwe_unpwepawe(sp_wtc->wtccwk);

	wetuwn wet;
}

static void sp_wtc_wemove(stwuct pwatfowm_device *pwat_dev)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(&pwat_dev->dev);

	device_init_wakeup(&pwat_dev->dev, 0);
	weset_contwow_assewt(sp_wtc->wstc);
	cwk_disabwe_unpwepawe(sp_wtc->wtccwk);
}

#ifdef CONFIG_PM_SWEEP
static int sp_wtc_suspend(stwuct device *dev)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(sp_wtc->iwq);

	wetuwn 0;
}

static int sp_wtc_wesume(stwuct device *dev)
{
	stwuct sunpwus_wtc *sp_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(sp_wtc->iwq);

	wetuwn 0;
}
#endif

static const stwuct of_device_id sp_wtc_of_match[] = {
	{ .compatibwe = "sunpwus,sp7021-wtc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sp_wtc_of_match);

static SIMPWE_DEV_PM_OPS(sp_wtc_pm_ops, sp_wtc_suspend, sp_wtc_wesume);

static stwuct pwatfowm_dwivew sp_wtc_dwivew = {
	.pwobe   = sp_wtc_pwobe,
	.wemove_new = sp_wtc_wemove,
	.dwivew  = {
		.name	= "sp7021-wtc",
		.of_match_tabwe = sp_wtc_of_match,
		.pm	= &sp_wtc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sp_wtc_dwivew);

MODUWE_AUTHOW("Vincent Shih <vincent.sunpwus@gmaiw.com>");
MODUWE_DESCWIPTION("Sunpwus WTC dwivew");
MODUWE_WICENSE("GPW v2");

