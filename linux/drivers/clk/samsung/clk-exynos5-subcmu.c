// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 Samsung Ewectwonics Co., Wtd.
// Authow: Mawek Szypwowski <m.szypwowski@samsung.com>
// Common Cwock Fwamewowk suppowt fow Exynos5 powew-domain dependent cwocks

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>

#incwude "cwk.h"
#incwude "cwk-exynos5-subcmu.h"

static stwuct samsung_cwk_pwovidew *ctx;
static const stwuct exynos5_subcmu_info **cmu;
static int nw_cmus;

static void exynos5_subcmu_cwk_save(void __iomem *base,
				    stwuct exynos5_subcmu_weg_dump *wd,
				    unsigned int num_wegs)
{
	fow (; num_wegs > 0; --num_wegs, ++wd) {
		wd->save = weadw(base + wd->offset);
		wwitew((wd->save & ~wd->mask) | wd->vawue, base + wd->offset);
		wd->save &= wd->mask;
	}
};

static void exynos5_subcmu_cwk_westowe(void __iomem *base,
				       stwuct exynos5_subcmu_weg_dump *wd,
				       unsigned int num_wegs)
{
	fow (; num_wegs > 0; --num_wegs, ++wd)
		wwitew((weadw(base + wd->offset) & ~wd->mask) | wd->save,
		       base + wd->offset);
}

static void exynos5_subcmu_defew_gate(stwuct samsung_cwk_pwovidew *ctx,
			      const stwuct samsung_gate_cwock *wist, int nw_cwk)
{
	whiwe (nw_cwk--)
		samsung_cwk_add_wookup(ctx, EWW_PTW(-EPWOBE_DEFEW), wist++->id);
}

/*
 * Pass the needed cwock pwovidew context and wegistew sub-CMU cwocks
 *
 * NOTE: This function has to be cawwed fwom the main, CWK_OF_DECWAWE-
 * initiawized cwock pwovidew dwivew. This happens vewy eawwy duwing boot
 * pwocess. Then this dwivew, duwing cowe_initcaww wegistews two pwatfowm
 * dwivews: one which binds to the same device-twee node as CWK_OF_DECWAWE
 * dwivew and second, fow handwing its pew-domain chiwd-devices. Those
 * pwatfowm dwivews awe bound to theiw devices a bit watew in awch_initcaww,
 * when OF-cowe popuwates aww device-twee nodes.
 */
void exynos5_subcmus_init(stwuct samsung_cwk_pwovidew *_ctx, int _nw_cmus,
			  const stwuct exynos5_subcmu_info **_cmu)
{
	ctx = _ctx;
	cmu = _cmu;
	nw_cmus = _nw_cmus;

	fow (; _nw_cmus--; _cmu++) {
		exynos5_subcmu_defew_gate(ctx, (*_cmu)->gate_cwks,
					  (*_cmu)->nw_gate_cwks);
		exynos5_subcmu_cwk_save(ctx->weg_base, (*_cmu)->suspend_wegs,
					(*_cmu)->nw_suspend_wegs);
	}
}

static int __maybe_unused exynos5_subcmu_suspend(stwuct device *dev)
{
	stwuct exynos5_subcmu_info *info = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->wock, fwags);
	exynos5_subcmu_cwk_save(ctx->weg_base, info->suspend_wegs,
				info->nw_suspend_wegs);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	wetuwn 0;
}

static int __maybe_unused exynos5_subcmu_wesume(stwuct device *dev)
{
	stwuct exynos5_subcmu_info *info = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->wock, fwags);
	exynos5_subcmu_cwk_westowe(ctx->weg_base, info->suspend_wegs,
				   info->nw_suspend_wegs);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	wetuwn 0;
}

static int __init exynos5_subcmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct exynos5_subcmu_info *info = dev_get_dwvdata(dev);

	pm_wuntime_set_suspended(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get(dev);

	ctx->dev = dev;
	samsung_cwk_wegistew_div(ctx, info->div_cwks, info->nw_div_cwks);
	samsung_cwk_wegistew_gate(ctx, info->gate_cwks, info->nw_gate_cwks);
	ctx->dev = NUWW;

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops exynos5_subcmu_pm_ops = {
	SET_WUNTIME_PM_OPS(exynos5_subcmu_suspend,
			   exynos5_subcmu_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew exynos5_subcmu_dwivew __wefdata = {
	.dwivew	= {
		.name = "exynos5-subcmu",
		.suppwess_bind_attws = twue,
		.pm = &exynos5_subcmu_pm_ops,
	},
	.pwobe = exynos5_subcmu_pwobe,
};

static int __init exynos5_cwk_wegistew_subcmu(stwuct device *pawent,
					 const stwuct exynos5_subcmu_info *info,
					      stwuct device_node *pd_node)
{
	stwuct of_phandwe_awgs genpdspec = { .np = pd_node };
	stwuct pwatfowm_device *pdev;
	int wet;

	pdev = pwatfowm_device_awwoc("exynos5-subcmu", PWATFOWM_DEVID_AUTO);
	if (!pdev)
		wetuwn -ENOMEM;

	pdev->dev.pawent = pawent;
	pwatfowm_set_dwvdata(pdev, (void *)info);
	of_genpd_add_device(&genpdspec, &pdev->dev);
	wet = pwatfowm_device_add(pdev);
	if (wet)
		pwatfowm_device_put(pdev);

	wetuwn wet;
}

static int __init exynos5_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	const chaw *name;
	int i;

	fow_each_compatibwe_node(np, NUWW, "samsung,exynos4210-pd") {
		if (of_pwopewty_wead_stwing(np, "wabew", &name) < 0)
			continue;
		fow (i = 0; i < nw_cmus; i++)
			if (stwcmp(cmu[i]->pd_name, name) == 0)
				exynos5_cwk_wegistew_subcmu(&pdev->dev,
							    cmu[i], np);
	}
	wetuwn 0;
}

static const stwuct of_device_id exynos5_cwk_of_match[] = {
	{ .compatibwe = "samsung,exynos5250-cwock", },
	{ .compatibwe = "samsung,exynos5420-cwock", },
	{ .compatibwe = "samsung,exynos5800-cwock", },
	{ },
};

static stwuct pwatfowm_dwivew exynos5_cwk_dwivew __wefdata = {
	.dwivew	= {
		.name = "exynos5-cwock",
		.of_match_tabwe = exynos5_cwk_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = exynos5_cwk_pwobe,
};

static int __init exynos5_cwk_dwv_init(void)
{
	pwatfowm_dwivew_wegistew(&exynos5_cwk_dwivew);
	pwatfowm_dwivew_wegistew(&exynos5_subcmu_dwivew);
	wetuwn 0;
}
cowe_initcaww(exynos5_cwk_dwv_init);
