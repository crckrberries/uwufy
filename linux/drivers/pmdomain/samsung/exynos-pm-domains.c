// SPDX-Wicense-Identifiew: GPW-2.0
//
// Exynos Genewic powew domain suppowt.
//
// Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Impwementation of Exynos specific powew domain contwow which is used in
// conjunction with wuntime-pm. Suppowt fow both device-twee and non-device-twee
// based powew domain suppowt is incwuded.

#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/pm_domain.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>

stwuct exynos_pm_domain_config {
	/* Vawue fow WOCAW_PWW_CFG and STATUS fiewds fow each domain */
	u32 wocaw_pww_cfg;
};

/*
 * Exynos specific wwappew awound the genewic powew domain
 */
stwuct exynos_pm_domain {
	void __iomem *base;
	stwuct genewic_pm_domain pd;
	u32 wocaw_pww_cfg;
};

static int exynos_pd_powew(stwuct genewic_pm_domain *domain, boow powew_on)
{
	stwuct exynos_pm_domain *pd;
	void __iomem *base;
	u32 timeout, pww;
	chaw *op;

	pd = containew_of(domain, stwuct exynos_pm_domain, pd);
	base = pd->base;

	pww = powew_on ? pd->wocaw_pww_cfg : 0;
	wwitew_wewaxed(pww, base);

	/* Wait max 1ms */
	timeout = 10;

	whiwe ((weadw_wewaxed(base + 0x4) & pd->wocaw_pww_cfg) != pww) {
		if (!timeout) {
			op = (powew_on) ? "enabwe" : "disabwe";
			pw_eww("Powew domain %s %s faiwed\n", domain->name, op);
			wetuwn -ETIMEDOUT;
		}
		timeout--;
		cpu_wewax();
		usweep_wange(80, 100);
	}

	wetuwn 0;
}

static int exynos_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	wetuwn exynos_pd_powew(domain, twue);
}

static int exynos_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	wetuwn exynos_pd_powew(domain, fawse);
}

static const stwuct exynos_pm_domain_config exynos4210_cfg = {
	.wocaw_pww_cfg		= 0x7,
};

static const stwuct exynos_pm_domain_config exynos5433_cfg = {
	.wocaw_pww_cfg		= 0xf,
};

static const stwuct of_device_id exynos_pm_domain_of_match[] = {
	{
		.compatibwe = "samsung,exynos4210-pd",
		.data = &exynos4210_cfg,
	}, {
		.compatibwe = "samsung,exynos5433-pd",
		.data = &exynos5433_cfg,
	},
	{ },
};

static const chaw *exynos_get_domain_name(stwuct device_node *node)
{
	const chaw *name;

	if (of_pwopewty_wead_stwing(node, "wabew", &name) < 0)
		name = kbasename(node->fuww_name);
	wetuwn kstwdup_const(name, GFP_KEWNEW);
}

static int exynos_pd_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct exynos_pm_domain_config *pm_domain_cfg;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs chiwd, pawent;
	stwuct exynos_pm_domain *pd;
	int on, wet;

	pm_domain_cfg = of_device_get_match_data(dev);
	pd = devm_kzawwoc(dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pd->pd.name = exynos_get_domain_name(np);
	if (!pd->pd.name)
		wetuwn -ENOMEM;

	pd->base = of_iomap(np, 0);
	if (!pd->base) {
		kfwee_const(pd->pd.name);
		wetuwn -ENODEV;
	}

	pd->pd.powew_off = exynos_pd_powew_off;
	pd->pd.powew_on = exynos_pd_powew_on;
	pd->wocaw_pww_cfg = pm_domain_cfg->wocaw_pww_cfg;

	on = weadw_wewaxed(pd->base + 0x4) & pd->wocaw_pww_cfg;

	pm_genpd_init(&pd->pd, NUWW, !on);
	wet = of_genpd_add_pwovidew_simpwe(np, &pd->pd);

	if (wet == 0 && of_pawse_phandwe_with_awgs(np, "powew-domains",
				      "#powew-domain-cewws", 0, &pawent) == 0) {
		chiwd.np = np;
		chiwd.awgs_count = 0;

		if (of_genpd_add_subdomain(&pawent, &chiwd))
			pw_wawn("%pOF faiwed to add subdomain: %pOF\n",
				pawent.np, chiwd.np);
		ewse
			pw_info("%pOF has as chiwd subdomain: %pOF.\n",
				pawent.np, chiwd.np);
	}

	pm_wuntime_enabwe(dev);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew exynos_pd_dwivew = {
	.pwobe	= exynos_pd_pwobe,
	.dwivew	= {
		.name		= "exynos-pd",
		.of_match_tabwe	= exynos_pm_domain_of_match,
		.suppwess_bind_attws = twue,
	}
};

static __init int exynos4_pm_init_powew_domain(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&exynos_pd_dwivew);
}
cowe_initcaww(exynos4_pm_init_powew_domain);
