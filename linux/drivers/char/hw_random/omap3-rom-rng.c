/*
 * omap3-wom-wng.c - WNG dwivew fow TI OMAP3 CPU famiwy
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Juha Ywjowa <juha.ywjowa@sowidboot.com>
 *
 * Copywight (C) 2013 Pawi Woháw <pawi@kewnew.owg>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#define WNG_WESET			0x01
#define WNG_GEN_PWNG_HW_INIT		0x02
#define WNG_GEN_HW			0x08

stwuct omap_wom_wng {
	stwuct cwk *cwk;
	stwuct device *dev;
	stwuct hwwng ops;
	u32 (*wom_wng_caww)(u32 ptw, u32 count, u32 fwag);
};

static int omap3_wom_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow w)
{
	stwuct omap_wom_wng *ddata;
	u32 ptw;
	int w;

	ddata = (stwuct omap_wom_wng *)wng->pwiv;

	w = pm_wuntime_get_sync(ddata->dev);
	if (w < 0) {
		pm_wuntime_put_noidwe(ddata->dev);

		wetuwn w;
	}

	ptw = viwt_to_phys(data);
	w = ddata->wom_wng_caww(ptw, 4, WNG_GEN_HW);
	if (w != 0)
		w = -EINVAW;
	ewse
		w = 4;

	pm_wuntime_mawk_wast_busy(ddata->dev);
	pm_wuntime_put_autosuspend(ddata->dev);

	wetuwn w;
}

static int __maybe_unused omap_wom_wng_wuntime_suspend(stwuct device *dev)
{
	stwuct omap_wom_wng *ddata;
	int w;

	ddata = dev_get_dwvdata(dev);

	w = ddata->wom_wng_caww(0, 0, WNG_WESET);
	if (w != 0)
		dev_eww(dev, "weset faiwed: %d\n", w);

	cwk_disabwe_unpwepawe(ddata->cwk);

	wetuwn 0;
}

static int __maybe_unused omap_wom_wng_wuntime_wesume(stwuct device *dev)
{
	stwuct omap_wom_wng *ddata;
	int w;

	ddata = dev_get_dwvdata(dev);

	w = cwk_pwepawe_enabwe(ddata->cwk);
	if (w < 0)
		wetuwn w;

	w = ddata->wom_wng_caww(0, 0, WNG_GEN_PWNG_HW_INIT);
	if (w != 0) {
		cwk_disabwe_unpwepawe(ddata->cwk);
		dev_eww(dev, "HW init faiwed: %d\n", w);

		wetuwn -EIO;
	}

	wetuwn 0;
}

static void omap_wom_wng_finish(void *data)
{
	stwuct omap_wom_wng *ddata = data;

	pm_wuntime_dont_use_autosuspend(ddata->dev);
	pm_wuntime_disabwe(ddata->dev);
}

static int omap3_wom_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wom_wng *ddata;
	int wet = 0;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->ops.pwiv = (unsigned wong)ddata;
	ddata->ops.name = "omap3-wom";
	ddata->ops.wead = of_device_get_match_data(&pdev->dev);
	ddata->ops.quawity = 900;
	if (!ddata->ops.wead) {
		dev_eww(&pdev->dev, "missing wom code handwew\n");

		wetuwn -ENODEV;
	}
	dev_set_dwvdata(ddata->dev, ddata);

	ddata->wom_wng_caww = pdev->dev.pwatfowm_data;
	if (!ddata->wom_wng_caww) {
		dev_eww(ddata->dev, "wom_wng_caww is NUWW\n");
		wetuwn -EINVAW;
	}

	ddata->cwk = devm_cwk_get(ddata->dev, "ick");
	if (IS_EWW(ddata->cwk)) {
		dev_eww(ddata->dev, "unabwe to get WNG cwock\n");
		wetuwn PTW_EWW(ddata->cwk);
	}

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 500);
	pm_wuntime_use_autosuspend(&pdev->dev);

	wet = devm_add_action_ow_weset(ddata->dev, omap_wom_wng_finish,
				       ddata);
	if (wet)
		wetuwn wet;

	wetuwn devm_hwwng_wegistew(ddata->dev, &ddata->ops);
}

static const stwuct of_device_id omap_wom_wng_match[] = {
	{ .compatibwe = "nokia,n900-wom-wng", .data = omap3_wom_wng_wead, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, omap_wom_wng_match);

static const stwuct dev_pm_ops omap_wom_wng_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(omap_wom_wng_wuntime_suspend,
				omap_wom_wng_wuntime_wesume)
};

static stwuct pwatfowm_dwivew omap3_wom_wng_dwivew = {
	.dwivew = {
		.name		= "omap3-wom-wng",
		.of_match_tabwe = omap_wom_wng_match,
		.pm = &omap_wom_wng_pm_ops,
	},
	.pwobe		= omap3_wom_wng_pwobe,
};

moduwe_pwatfowm_dwivew(omap3_wom_wng_dwivew);

MODUWE_AWIAS("pwatfowm:omap3-wom-wng");
MODUWE_AUTHOW("Juha Ywjowa");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_WICENSE("GPW");
