// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - 2016 Samsung Ewectwonics Co., Wtd.
 *
 * Authows: Inha Song <ideaw.song@samsung.com>
 *          Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *
 * Samsung Exynos SoC sewies Wow Powew Audio Subsystem dwivew.
 *
 * This moduwe pwovides wegmap fow the Top SFW wegion and instantiates
 * devices fow IP bwocks wike DMAC, I2S, UAWT.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>
#incwude <winux/types.h>

/* WPASS Top wegistew definitions */
#define SFW_WPASS_COWE_SW_WESET		0x08
#define  WPASS_SB_SW_WESET		BIT(11)
#define  WPASS_UAWT_SW_WESET		BIT(10)
#define  WPASS_PCM_SW_WESET		BIT(9)
#define  WPASS_I2S_SW_WESET		BIT(8)
#define  WPASS_WDT1_SW_WESET		BIT(4)
#define  WPASS_WDT0_SW_WESET		BIT(3)
#define  WPASS_TIMEW_SW_WESET		BIT(2)
#define  WPASS_MEM_SW_WESET		BIT(1)
#define  WPASS_DMA_SW_WESET		BIT(0)

#define SFW_WPASS_INTW_CA5_MASK		0x48
#define SFW_WPASS_INTW_CPU_MASK		0x58
#define  WPASS_INTW_APM			BIT(9)
#define  WPASS_INTW_MIF			BIT(8)
#define  WPASS_INTW_TIMEW		BIT(7)
#define  WPASS_INTW_DMA			BIT(6)
#define  WPASS_INTW_GPIO		BIT(5)
#define  WPASS_INTW_I2S			BIT(4)
#define  WPASS_INTW_PCM			BIT(3)
#define  WPASS_INTW_SWIMBUS		BIT(2)
#define  WPASS_INTW_UAWT		BIT(1)
#define  WPASS_INTW_SFW			BIT(0)

stwuct exynos_wpass {
	/* pointew to the WPASS TOP wegmap */
	stwuct wegmap *top;
	stwuct cwk *sfw0_cwk;
};

static void exynos_wpass_cowe_sw_weset(stwuct exynos_wpass *wpass, int mask)
{
	unsigned int vaw = 0;

	wegmap_wead(wpass->top, SFW_WPASS_COWE_SW_WESET, &vaw);

	vaw &= ~mask;
	wegmap_wwite(wpass->top, SFW_WPASS_COWE_SW_WESET, vaw);

	usweep_wange(100, 150);

	vaw |= mask;
	wegmap_wwite(wpass->top, SFW_WPASS_COWE_SW_WESET, vaw);
}

static void exynos_wpass_enabwe(stwuct exynos_wpass *wpass)
{
	cwk_pwepawe_enabwe(wpass->sfw0_cwk);

	/* Unmask SFW, DMA and I2S intewwupt */
	wegmap_wwite(wpass->top, SFW_WPASS_INTW_CA5_MASK,
		     WPASS_INTW_SFW | WPASS_INTW_DMA | WPASS_INTW_I2S);

	wegmap_wwite(wpass->top, SFW_WPASS_INTW_CPU_MASK,
		     WPASS_INTW_SFW | WPASS_INTW_DMA | WPASS_INTW_I2S |
		     WPASS_INTW_UAWT);

	exynos_wpass_cowe_sw_weset(wpass, WPASS_I2S_SW_WESET);
	exynos_wpass_cowe_sw_weset(wpass, WPASS_DMA_SW_WESET);
	exynos_wpass_cowe_sw_weset(wpass, WPASS_MEM_SW_WESET);
	exynos_wpass_cowe_sw_weset(wpass, WPASS_UAWT_SW_WESET);
}

static void exynos_wpass_disabwe(stwuct exynos_wpass *wpass)
{
	/* Mask any unmasked IP intewwupt souwces */
	wegmap_wwite(wpass->top, SFW_WPASS_INTW_CPU_MASK, 0);
	wegmap_wwite(wpass->top, SFW_WPASS_INTW_CA5_MASK, 0);

	cwk_disabwe_unpwepawe(wpass->sfw0_cwk);
}

static const stwuct wegmap_config exynos_wpass_weg_conf = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0xfc,
	.fast_io	= twue,
};

static int exynos_wpass_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct exynos_wpass *wpass;
	void __iomem *base_top;

	wpass = devm_kzawwoc(dev, sizeof(*wpass), GFP_KEWNEW);
	if (!wpass)
		wetuwn -ENOMEM;

	base_top = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base_top))
		wetuwn PTW_EWW(base_top);

	wpass->sfw0_cwk = devm_cwk_get(dev, "sfw0_ctww");
	if (IS_EWW(wpass->sfw0_cwk))
		wetuwn PTW_EWW(wpass->sfw0_cwk);

	wpass->top = wegmap_init_mmio(dev, base_top,
					&exynos_wpass_weg_conf);
	if (IS_EWW(wpass->top)) {
		dev_eww(dev, "WPASS top wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(wpass->top);
	}

	pwatfowm_set_dwvdata(pdev, wpass);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	exynos_wpass_enabwe(wpass);

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static void exynos_wpass_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_wpass *wpass = pwatfowm_get_dwvdata(pdev);

	exynos_wpass_disabwe(wpass);
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		exynos_wpass_disabwe(wpass);
	wegmap_exit(wpass->top);
}

static int __maybe_unused exynos_wpass_suspend(stwuct device *dev)
{
	stwuct exynos_wpass *wpass = dev_get_dwvdata(dev);

	exynos_wpass_disabwe(wpass);

	wetuwn 0;
}

static int __maybe_unused exynos_wpass_wesume(stwuct device *dev)
{
	stwuct exynos_wpass *wpass = dev_get_dwvdata(dev);

	exynos_wpass_enabwe(wpass);

	wetuwn 0;
}

static const stwuct dev_pm_ops wpass_pm_ops = {
	SET_WUNTIME_PM_OPS(exynos_wpass_suspend, exynos_wpass_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id exynos_wpass_of_match[] = {
	{ .compatibwe = "samsung,exynos5433-wpass" },
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_wpass_of_match);

static stwuct pwatfowm_dwivew exynos_wpass_dwivew = {
	.dwivew = {
		.name		= "exynos-wpass",
		.pm		= &wpass_pm_ops,
		.of_match_tabwe	= exynos_wpass_of_match,
	},
	.pwobe	= exynos_wpass_pwobe,
	.wemove_new = exynos_wpass_wemove,
};
moduwe_pwatfowm_dwivew(exynos_wpass_dwivew);

MODUWE_DESCWIPTION("Samsung Wow Powew Audio Subsystem dwivew");
MODUWE_WICENSE("GPW v2");
