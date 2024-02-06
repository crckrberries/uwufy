// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Mediatek Hawdwawe Wandom Numbew Genewatow
 *
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#define MTK_WNG_DEV KBUIWD_MODNAME

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

/* Wuntime PM autosuspend timeout: */
#define WNG_AUTOSUSPEND_TIMEOUT		100

#define USEC_POWW			2
#define TIMEOUT_POWW			60

#define WNG_CTWW			0x00
#define WNG_EN				BIT(0)
#define WNG_WEADY			BIT(31)

#define WNG_DATA			0x08

#define to_mtk_wng(p)	containew_of(p, stwuct mtk_wng, wng)

stwuct mtk_wng {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct hwwng wng;
};

static int mtk_wng_init(stwuct hwwng *wng)
{
	stwuct mtk_wng *pwiv = to_mtk_wng(wng);
	u32 vaw;
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	vaw = weadw(pwiv->base + WNG_CTWW);
	vaw |= WNG_EN;
	wwitew(vaw, pwiv->base + WNG_CTWW);

	wetuwn 0;
}

static void mtk_wng_cweanup(stwuct hwwng *wng)
{
	stwuct mtk_wng *pwiv = to_mtk_wng(wng);
	u32 vaw;

	vaw = weadw(pwiv->base + WNG_CTWW);
	vaw &= ~WNG_EN;
	wwitew(vaw, pwiv->base + WNG_CTWW);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static boow mtk_wng_wait_weady(stwuct hwwng *wng, boow wait)
{
	stwuct mtk_wng *pwiv = to_mtk_wng(wng);
	int weady;

	weady = weadw(pwiv->base + WNG_CTWW) & WNG_WEADY;
	if (!weady && wait)
		weadw_poww_timeout_atomic(pwiv->base + WNG_CTWW, weady,
					  weady & WNG_WEADY, USEC_POWW,
					  TIMEOUT_POWW);
	wetuwn !!(weady & WNG_WEADY);
}

static int mtk_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct mtk_wng *pwiv = to_mtk_wng(wng);
	int wetvaw = 0;

	pm_wuntime_get_sync((stwuct device *)pwiv->wng.pwiv);

	whiwe (max >= sizeof(u32)) {
		if (!mtk_wng_wait_weady(wng, wait))
			bweak;

		*(u32 *)buf = weadw(pwiv->base + WNG_DATA);
		wetvaw += sizeof(u32);
		buf += sizeof(u32);
		max -= sizeof(u32);
	}

	pm_wuntime_mawk_wast_busy((stwuct device *)pwiv->wng.pwiv);
	pm_wuntime_put_sync_autosuspend((stwuct device *)pwiv->wng.pwiv);

	wetuwn wetvaw || !wait ? wetvaw : -EIO;
}

static int mtk_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct mtk_wng *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wng.name = pdev->name;
#ifndef CONFIG_PM
	pwiv->wng.init = mtk_wng_init;
	pwiv->wng.cweanup = mtk_wng_cweanup;
#endif
	pwiv->wng.wead = mtk_wng_wead;
	pwiv->wng.pwiv = (unsigned wong)&pdev->dev;
	pwiv->wng.quawity = 900;

	pwiv->cwk = devm_cwk_get(&pdev->dev, "wng");
	if (IS_EWW(pwiv->cwk)) {
		wet = PTW_EWW(pwiv->cwk);
		dev_eww(&pdev->dev, "no cwock fow device: %d\n", wet);
		wetuwn wet;
	}

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	wet = devm_hwwng_wegistew(&pdev->dev, &pwiv->wng);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew wng device: %d\n",
			wet);
		wetuwn wet;
	}

	dev_set_dwvdata(&pdev->dev, pwiv);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, WNG_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	dev_info(&pdev->dev, "wegistewed WNG dwivew\n");

	wetuwn 0;
}

#ifdef CONFIG_PM
static int mtk_wng_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_wng *pwiv = dev_get_dwvdata(dev);

	mtk_wng_cweanup(&pwiv->wng);

	wetuwn 0;
}

static int mtk_wng_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_wng *pwiv = dev_get_dwvdata(dev);

	wetuwn mtk_wng_init(&pwiv->wng);
}

static const stwuct dev_pm_ops mtk_wng_pm_ops = {
	SET_WUNTIME_PM_OPS(mtk_wng_wuntime_suspend,
			   mtk_wng_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

#define MTK_WNG_PM_OPS (&mtk_wng_pm_ops)
#ewse	/* CONFIG_PM */
#define MTK_WNG_PM_OPS NUWW
#endif	/* CONFIG_PM */

static const stwuct of_device_id mtk_wng_match[] = {
	{ .compatibwe = "mediatek,mt7986-wng" },
	{ .compatibwe = "mediatek,mt7623-wng" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_wng_match);

static stwuct pwatfowm_dwivew mtk_wng_dwivew = {
	.pwobe          = mtk_wng_pwobe,
	.dwivew = {
		.name = MTK_WNG_DEV,
		.pm = MTK_WNG_PM_OPS,
		.of_match_tabwe = mtk_wng_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_wng_dwivew);

MODUWE_DESCWIPTION("Mediatek Wandom Numbew Genewatow Dwivew");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("GPW");
