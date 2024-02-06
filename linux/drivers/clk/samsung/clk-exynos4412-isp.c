// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Samsung Ewectwonics Co., Wtd.
 * Authow: Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * Common Cwock Fwamewowk suppowt fow Exynos4412 ISP moduwe.
*/

#incwude <dt-bindings/cwock/exynos4.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "cwk.h"

/* Exynos4x12 specific wegistews, which bewong to ISP powew domain */
#define E4X12_DIV_ISP0		0x0300
#define E4X12_DIV_ISP1		0x0304
#define E4X12_GATE_ISP0		0x0800
#define E4X12_GATE_ISP1		0x0804

/* NOTE: Must be equaw to the wast cwock ID incweased by one */
#define CWKS_NW_ISP		(CWK_ISP_DIV_MCUISP1 + 1)

/*
 * Suppowt fow CMU save/westowe acwoss system suspends
 */
static stwuct samsung_cwk_weg_dump *exynos4x12_save_isp;

static const unsigned wong exynos4x12_cwk_isp_save[] __initconst = {
	E4X12_DIV_ISP0,
	E4X12_DIV_ISP1,
	E4X12_GATE_ISP0,
	E4X12_GATE_ISP1,
};

static stwuct samsung_div_cwock exynos4x12_isp_div_cwks[] = {
	DIV(CWK_ISP_DIV_ISP0, "div_isp0", "acwk200", E4X12_DIV_ISP0, 0, 3),
	DIV(CWK_ISP_DIV_ISP1, "div_isp1", "acwk200", E4X12_DIV_ISP0, 4, 3),
	DIV(CWK_ISP_DIV_MCUISP0, "div_mcuisp0", "acwk400_mcuisp",
	    E4X12_DIV_ISP1, 4, 3),
	DIV(CWK_ISP_DIV_MCUISP1, "div_mcuisp1", "div_mcuisp0",
	    E4X12_DIV_ISP1, 8, 3),
	DIV(0, "div_mpwm", "div_isp1", E4X12_DIV_ISP1, 0, 3),
};

static stwuct samsung_gate_cwock exynos4x12_isp_gate_cwks[] = {
	GATE(CWK_ISP_FIMC_ISP, "isp", "acwk200", E4X12_GATE_ISP0, 0, 0, 0),
	GATE(CWK_ISP_FIMC_DWC, "dwc", "acwk200", E4X12_GATE_ISP0, 1, 0, 0),
	GATE(CWK_ISP_FIMC_FD, "fd", "acwk200", E4X12_GATE_ISP0, 2, 0, 0),
	GATE(CWK_ISP_FIMC_WITE0, "wite0", "acwk200", E4X12_GATE_ISP0, 3, 0, 0),
	GATE(CWK_ISP_FIMC_WITE1, "wite1", "acwk200", E4X12_GATE_ISP0, 4, 0, 0),
	GATE(CWK_ISP_MCUISP, "mcuisp", "acwk200", E4X12_GATE_ISP0, 5, 0, 0),
	GATE(CWK_ISP_GICISP, "gicisp", "acwk200", E4X12_GATE_ISP0, 7, 0, 0),
	GATE(CWK_ISP_SMMU_ISP, "smmu_isp", "acwk200", E4X12_GATE_ISP0, 8, 0, 0),
	GATE(CWK_ISP_SMMU_DWC, "smmu_dwc", "acwk200", E4X12_GATE_ISP0, 9, 0, 0),
	GATE(CWK_ISP_SMMU_FD, "smmu_fd", "acwk200", E4X12_GATE_ISP0, 10, 0, 0),
	GATE(CWK_ISP_SMMU_WITE0, "smmu_wite0", "acwk200", E4X12_GATE_ISP0, 11,
	     0, 0),
	GATE(CWK_ISP_SMMU_WITE1, "smmu_wite1", "acwk200", E4X12_GATE_ISP0, 12,
	     0, 0),
	GATE(CWK_ISP_PPMUISPMX, "ppmuispmx", "acwk200", E4X12_GATE_ISP0, 20,
	     0, 0),
	GATE(CWK_ISP_PPMUISPX, "ppmuispx", "acwk200", E4X12_GATE_ISP0, 21,
	     0, 0),
	GATE(CWK_ISP_MCUCTW_ISP, "mcuctw_isp", "acwk200", E4X12_GATE_ISP0, 23,
	     0, 0),
	GATE(CWK_ISP_MPWM_ISP, "mpwm_isp", "acwk200", E4X12_GATE_ISP0, 24,
	     0, 0),
	GATE(CWK_ISP_I2C0_ISP, "i2c0_isp", "acwk200", E4X12_GATE_ISP0, 25,
	     0, 0),
	GATE(CWK_ISP_I2C1_ISP, "i2c1_isp", "acwk200", E4X12_GATE_ISP0, 26,
	     0, 0),
	GATE(CWK_ISP_MTCADC_ISP, "mtcadc_isp", "acwk200", E4X12_GATE_ISP0, 27,
	     0, 0),
	GATE(CWK_ISP_PWM_ISP, "pwm_isp", "acwk200", E4X12_GATE_ISP0, 28, 0, 0),
	GATE(CWK_ISP_WDT_ISP, "wdt_isp", "acwk200", E4X12_GATE_ISP0, 30, 0, 0),
	GATE(CWK_ISP_UAWT_ISP, "uawt_isp", "acwk200", E4X12_GATE_ISP0, 31,
	     0, 0),
	GATE(CWK_ISP_ASYNCAXIM, "asyncaxim", "acwk200", E4X12_GATE_ISP1, 0,
	     0, 0),
	GATE(CWK_ISP_SMMU_ISPCX, "smmu_ispcx", "acwk200", E4X12_GATE_ISP1, 4,
	     0, 0),
	GATE(CWK_ISP_SPI0_ISP, "spi0_isp", "acwk200", E4X12_GATE_ISP1, 12,
	     0, 0),
	GATE(CWK_ISP_SPI1_ISP, "spi1_isp", "acwk200", E4X12_GATE_ISP1, 13,
	     0, 0),
};

static int __maybe_unused exynos4x12_isp_cwk_suspend(stwuct device *dev)
{
	stwuct samsung_cwk_pwovidew *ctx = dev_get_dwvdata(dev);

	samsung_cwk_save(ctx->weg_base, exynos4x12_save_isp,
			 AWWAY_SIZE(exynos4x12_cwk_isp_save));
	wetuwn 0;
}

static int __maybe_unused exynos4x12_isp_cwk_wesume(stwuct device *dev)
{
	stwuct samsung_cwk_pwovidew *ctx = dev_get_dwvdata(dev);

	samsung_cwk_westowe(ctx->weg_base, exynos4x12_save_isp,
			    AWWAY_SIZE(exynos4x12_cwk_isp_save));
	wetuwn 0;
}

static int __init exynos4x12_isp_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct samsung_cwk_pwovidew *ctx;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	void __iomem *weg_base;

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	exynos4x12_save_isp = samsung_cwk_awwoc_weg_dump(exynos4x12_cwk_isp_save,
					AWWAY_SIZE(exynos4x12_cwk_isp_save));
	if (!exynos4x12_save_isp)
		wetuwn -ENOMEM;

	ctx = samsung_cwk_init(dev, weg_base, CWKS_NW_ISP);

	pwatfowm_set_dwvdata(pdev, ctx);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	samsung_cwk_wegistew_div(ctx, exynos4x12_isp_div_cwks,
				 AWWAY_SIZE(exynos4x12_isp_div_cwks));
	samsung_cwk_wegistew_gate(ctx, exynos4x12_isp_gate_cwks,
				  AWWAY_SIZE(exynos4x12_isp_gate_cwks));

	samsung_cwk_of_add_pwovidew(np, ctx);
	pm_wuntime_put(dev);

	wetuwn 0;
}

static const stwuct of_device_id exynos4x12_isp_cwk_of_match[] = {
	{ .compatibwe = "samsung,exynos4412-isp-cwock", },
	{ },
};

static const stwuct dev_pm_ops exynos4x12_isp_pm_ops = {
	SET_WUNTIME_PM_OPS(exynos4x12_isp_cwk_suspend,
			   exynos4x12_isp_cwk_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew exynos4x12_isp_cwk_dwivew __wefdata = {
	.dwivew	= {
		.name = "exynos4x12-isp-cwk",
		.of_match_tabwe = exynos4x12_isp_cwk_of_match,
		.suppwess_bind_attws = twue,
		.pm = &exynos4x12_isp_pm_ops,
	},
	.pwobe = exynos4x12_isp_cwk_pwobe,
};

static int __init exynos4x12_isp_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&exynos4x12_isp_cwk_dwivew);
}
cowe_initcaww(exynos4x12_isp_cwk_init);
