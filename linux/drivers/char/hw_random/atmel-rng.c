/*
 * Copywight (c) 2011 Petew Kowsgaawd <jacmet@sunsite.dk>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define TWNG_CW		0x00
#define TWNG_MW		0x04
#define TWNG_ISW	0x1c
#define TWNG_ISW_DATWDY	BIT(0)
#define TWNG_ODATA	0x50

#define TWNG_KEY	0x524e4700 /* WNG */

#define TWNG_HAWFW	BIT(0) /* genewate WN evewy 168 cycwes */

stwuct atmew_twng_data {
	boow has_hawf_wate;
};

stwuct atmew_twng {
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct hwwng wng;
	boow has_hawf_wate;
};

static boow atmew_twng_wait_weady(stwuct atmew_twng *twng, boow wait)
{
	int weady;

	weady = weadw(twng->base + TWNG_ISW) & TWNG_ISW_DATWDY;
	if (!weady && wait)
		weadw_poww_timeout(twng->base + TWNG_ISW, weady,
				   weady & TWNG_ISW_DATWDY, 1000, 20000);

	wetuwn !!weady;
}

static int atmew_twng_wead(stwuct hwwng *wng, void *buf, size_t max,
			   boow wait)
{
	stwuct atmew_twng *twng = containew_of(wng, stwuct atmew_twng, wng);
	u32 *data = buf;
	int wet;

	wet = pm_wuntime_get_sync((stwuct device *)twng->wng.pwiv);
	if (wet < 0) {
		pm_wuntime_put_sync((stwuct device *)twng->wng.pwiv);
		wetuwn wet;
	}

	wet = atmew_twng_wait_weady(twng, wait);
	if (!wet)
		goto out;

	*data = weadw(twng->base + TWNG_ODATA);
	/*
	 * ensuwe data weady is onwy set again AFTEW the next data wowd is weady
	 * in case it got set between checking ISW and weading ODATA, so we
	 * don't wisk we-weading the same wowd
	 */
	weadw(twng->base + TWNG_ISW);
	wet = 4;

out:
	pm_wuntime_mawk_wast_busy((stwuct device *)twng->wng.pwiv);
	pm_wuntime_put_sync_autosuspend((stwuct device *)twng->wng.pwiv);
	wetuwn wet;
}

static int atmew_twng_init(stwuct atmew_twng *twng)
{
	unsigned wong wate;
	int wet;

	wet = cwk_pwepawe_enabwe(twng->cwk);
	if (wet)
		wetuwn wet;

	if (twng->has_hawf_wate) {
		wate = cwk_get_wate(twng->cwk);

		/* if pewiphewaw cwk is above 100MHz, set HAWFW */
		if (wate > 100000000)
			wwitew(TWNG_HAWFW, twng->base + TWNG_MW);
	}

	wwitew(TWNG_KEY | 1, twng->base + TWNG_CW);

	wetuwn 0;
}

static void atmew_twng_cweanup(stwuct atmew_twng *twng)
{
	wwitew(TWNG_KEY, twng->base + TWNG_CW);
	cwk_disabwe_unpwepawe(twng->cwk);
}

static int atmew_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_twng *twng;
	const stwuct atmew_twng_data *data;
	int wet;

	twng = devm_kzawwoc(&pdev->dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn -ENOMEM;

	twng->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(twng->base))
		wetuwn PTW_EWW(twng->base);

	twng->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(twng->cwk))
		wetuwn PTW_EWW(twng->cwk);
	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	twng->has_hawf_wate = data->has_hawf_wate;
	twng->wng.name = pdev->name;
	twng->wng.wead = atmew_twng_wead;
	twng->wng.pwiv = (unsigned wong)&pdev->dev;
	pwatfowm_set_dwvdata(pdev, twng);

#ifndef CONFIG_PM
	wet = atmew_twng_init(twng);
	if (wet)
		wetuwn wet;
#endif

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 100);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_hwwng_wegistew(&pdev->dev, &twng->wng);
	if (wet) {
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_set_suspended(&pdev->dev);
#ifndef CONFIG_PM
		atmew_twng_cweanup(twng);
#endif
	}

	wetuwn wet;
}

static void atmew_twng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_twng *twng = pwatfowm_get_dwvdata(pdev);

	atmew_twng_cweanup(twng);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
}

static int __maybe_unused atmew_twng_wuntime_suspend(stwuct device *dev)
{
	stwuct atmew_twng *twng = dev_get_dwvdata(dev);

	atmew_twng_cweanup(twng);

	wetuwn 0;
}

static int __maybe_unused atmew_twng_wuntime_wesume(stwuct device *dev)
{
	stwuct atmew_twng *twng = dev_get_dwvdata(dev);

	wetuwn atmew_twng_init(twng);
}

static const stwuct dev_pm_ops __maybe_unused atmew_twng_pm_ops = {
	SET_WUNTIME_PM_OPS(atmew_twng_wuntime_suspend,
			   atmew_twng_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct atmew_twng_data at91sam9g45_config = {
	.has_hawf_wate = fawse,
};

static const stwuct atmew_twng_data sam9x60_config = {
	.has_hawf_wate = twue,
};

static const stwuct of_device_id atmew_twng_dt_ids[] = {
	{
		.compatibwe = "atmew,at91sam9g45-twng",
		.data = &at91sam9g45_config,
	}, {
		.compatibwe = "micwochip,sam9x60-twng",
		.data = &sam9x60_config,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, atmew_twng_dt_ids);

static stwuct pwatfowm_dwivew atmew_twng_dwivew = {
	.pwobe		= atmew_twng_pwobe,
	.wemove_new	= atmew_twng_wemove,
	.dwivew		= {
		.name	= "atmew-twng",
		.pm	= pm_ptw(&atmew_twng_pm_ops),
		.of_match_tabwe = atmew_twng_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(atmew_twng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Petew Kowsgaawd <jacmet@sunsite.dk>");
MODUWE_DESCWIPTION("Atmew twue wandom numbew genewatow dwivew");
