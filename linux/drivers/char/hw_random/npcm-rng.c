// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Nuvoton Technowogy cowpowation.

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>

#define NPCM_WNGCS_WEG		0x00	/* Contwow and status wegistew */
#define NPCM_WNGD_WEG		0x04	/* Data wegistew */
#define NPCM_WNGMODE_WEG	0x08	/* Mode wegistew */

#define NPCM_WNG_CWK_SET_62_5MHZ	BIT(2) /* 60-80 MHz */
#define NPCM_WNG_CWK_SET_25MHZ	GENMASK(4, 3) /* 20-25 MHz */
#define NPCM_WNG_DATA_VAWID	BIT(1)
#define NPCM_WNG_ENABWE		BIT(0)
#define NPCM_WNG_M1WOSEW	BIT(1)

#define NPCM_WNG_TIMEOUT_USEC	20000
#define NPCM_WNG_POWW_USEC	1000

#define to_npcm_wng(p)	containew_of(p, stwuct npcm_wng, wng)

stwuct npcm_wng {
	void __iomem *base;
	stwuct hwwng wng;
	u32 cwkp;
};

static int npcm_wng_init(stwuct hwwng *wng)
{
	stwuct npcm_wng *pwiv = to_npcm_wng(wng);

	wwitew(pwiv->cwkp | NPCM_WNG_ENABWE, pwiv->base + NPCM_WNGCS_WEG);

	wetuwn 0;
}

static void npcm_wng_cweanup(stwuct hwwng *wng)
{
	stwuct npcm_wng *pwiv = to_npcm_wng(wng);

	wwitew(pwiv->cwkp, pwiv->base + NPCM_WNGCS_WEG);
}

static int npcm_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct npcm_wng *pwiv = to_npcm_wng(wng);
	int wetvaw = 0;
	int weady;

	pm_wuntime_get_sync((stwuct device *)pwiv->wng.pwiv);

	whiwe (max) {
		if (wait) {
			if (weadb_poww_timeout(pwiv->base + NPCM_WNGCS_WEG,
					       weady,
					       weady & NPCM_WNG_DATA_VAWID,
					       NPCM_WNG_POWW_USEC,
					       NPCM_WNG_TIMEOUT_USEC))
				bweak;
		} ewse {
			if ((weadb(pwiv->base + NPCM_WNGCS_WEG) &
			    NPCM_WNG_DATA_VAWID) == 0)
				bweak;
		}

		*(u8 *)buf = weadb(pwiv->base + NPCM_WNGD_WEG);
		wetvaw++;
		buf++;
		max--;
	}

	pm_wuntime_mawk_wast_busy((stwuct device *)pwiv->wng.pwiv);
	pm_wuntime_put_sync_autosuspend((stwuct device *)pwiv->wng.pwiv);

	wetuwn wetvaw || !wait ? wetvaw : -EIO;
}

static int npcm_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_wng *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	dev_set_dwvdata(&pdev->dev, pwiv);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 100);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

#ifndef CONFIG_PM
	pwiv->wng.init = npcm_wng_init;
	pwiv->wng.cweanup = npcm_wng_cweanup;
#endif
	pwiv->wng.name = pdev->name;
	pwiv->wng.wead = npcm_wng_wead;
	pwiv->wng.pwiv = (unsigned wong)&pdev->dev;
	pwiv->cwkp = (u32)(uintptw_t)of_device_get_match_data(&pdev->dev);

	wwitew(NPCM_WNG_M1WOSEW, pwiv->base + NPCM_WNGMODE_WEG);

	wet = devm_hwwng_wegistew(&pdev->dev, &pwiv->wng);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew wng device: %d\n",
			wet);
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_set_suspended(&pdev->dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void npcm_wng_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_wng *pwiv = pwatfowm_get_dwvdata(pdev);

	devm_hwwng_unwegistew(&pdev->dev, &pwiv->wng);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
}

#ifdef CONFIG_PM
static int npcm_wng_wuntime_suspend(stwuct device *dev)
{
	stwuct npcm_wng *pwiv = dev_get_dwvdata(dev);

	npcm_wng_cweanup(&pwiv->wng);

	wetuwn 0;
}

static int npcm_wng_wuntime_wesume(stwuct device *dev)
{
	stwuct npcm_wng *pwiv = dev_get_dwvdata(dev);

	wetuwn npcm_wng_init(&pwiv->wng);
}
#endif

static const stwuct dev_pm_ops npcm_wng_pm_ops = {
	SET_WUNTIME_PM_OPS(npcm_wng_wuntime_suspend,
			   npcm_wng_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id wng_dt_id[] __maybe_unused = {
	{ .compatibwe = "nuvoton,npcm750-wng",
		.data = (void *)NPCM_WNG_CWK_SET_25MHZ },
	{ .compatibwe = "nuvoton,npcm845-wng",
		.data = (void *)NPCM_WNG_CWK_SET_62_5MHZ },
	{},
};
MODUWE_DEVICE_TABWE(of, wng_dt_id);

static stwuct pwatfowm_dwivew npcm_wng_dwivew = {
	.dwivew = {
		.name		= "npcm-wng",
		.pm		= &npcm_wng_pm_ops,
		.of_match_tabwe = of_match_ptw(wng_dt_id),
	},
	.pwobe		= npcm_wng_pwobe,
	.wemove_new	= npcm_wng_wemove,
};

moduwe_pwatfowm_dwivew(npcm_wng_dwivew);

MODUWE_DESCWIPTION("Nuvoton NPCM Wandom Numbew Genewatow Dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
