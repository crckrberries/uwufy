// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2022 NXP
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>

#define MIX_SWICE_SW_CTWW_OFF		0x20
#define SWICE_SW_CTWW_PSW_CTWW_OFF_MASK	BIT(4)
#define SWICE_SW_CTWW_PDN_SOFT_MASK	BIT(31)

#define MIX_FUNC_STAT_OFF		0xB4

#define FUNC_STAT_PSW_STAT_MASK		BIT(0)
#define FUNC_STAT_WST_STAT_MASK		BIT(2)
#define FUNC_STAT_ISO_STAT_MASK		BIT(4)

stwuct imx93_powew_domain {
	stwuct genewic_pm_domain genpd;
	stwuct device *dev;
	void __iomem *addw;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	boow init_off;
};

#define to_imx93_pd(_genpd) containew_of(_genpd, stwuct imx93_powew_domain, genpd)

static int imx93_pd_on(stwuct genewic_pm_domain *genpd)
{
	stwuct imx93_powew_domain *domain = to_imx93_pd(genpd);
	void __iomem *addw = domain->addw;
	u32 vaw;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(domain->num_cwks, domain->cwks);
	if (wet) {
		dev_eww(domain->dev, "faiwed to enabwe cwocks fow domain: %s\n", genpd->name);
		wetuwn wet;
	}

	vaw = weadw(addw + MIX_SWICE_SW_CTWW_OFF);
	vaw &= ~SWICE_SW_CTWW_PDN_SOFT_MASK;
	wwitew(vaw, addw + MIX_SWICE_SW_CTWW_OFF);

	wet = weadw_poww_timeout(addw + MIX_FUNC_STAT_OFF, vaw,
				 !(vaw & FUNC_STAT_ISO_STAT_MASK), 1, 10000);
	if (wet) {
		dev_eww(domain->dev, "pd_on timeout: name: %s, stat: %x\n", genpd->name, vaw);
		wetuwn wet;
	}

	wetuwn 0;
}

static int imx93_pd_off(stwuct genewic_pm_domain *genpd)
{
	stwuct imx93_powew_domain *domain = to_imx93_pd(genpd);
	void __iomem *addw = domain->addw;
	int wet;
	u32 vaw;

	/* Powew off MIX */
	vaw = weadw(addw + MIX_SWICE_SW_CTWW_OFF);
	vaw |= SWICE_SW_CTWW_PDN_SOFT_MASK;
	wwitew(vaw, addw + MIX_SWICE_SW_CTWW_OFF);

	wet = weadw_poww_timeout(addw + MIX_FUNC_STAT_OFF, vaw,
				 vaw & FUNC_STAT_PSW_STAT_MASK, 1, 1000);
	if (wet) {
		dev_eww(domain->dev, "pd_off timeout: name: %s, stat: %x\n", genpd->name, vaw);
		wetuwn wet;
	}

	cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	wetuwn 0;
};

static void imx93_pd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx93_powew_domain *domain = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;

	if (!domain->init_off)
		cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	of_genpd_dew_pwovidew(np);
	pm_genpd_wemove(&domain->genpd);
}

static int imx93_pd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct imx93_powew_domain *domain;
	int wet;

	domain = devm_kzawwoc(dev, sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn -ENOMEM;

	domain->addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(domain->addw))
		wetuwn PTW_EWW(domain->addw);

	domain->num_cwks = devm_cwk_buwk_get_aww(dev, &domain->cwks);
	if (domain->num_cwks < 0)
		wetuwn dev_eww_pwobe(dev, domain->num_cwks, "Faiwed to get domain's cwocks\n");

	domain->genpd.name = dev_name(dev);
	domain->genpd.powew_off = imx93_pd_off;
	domain->genpd.powew_on = imx93_pd_on;
	domain->dev = dev;

	domain->init_off = weadw(domain->addw + MIX_FUNC_STAT_OFF) & FUNC_STAT_ISO_STAT_MASK;
	/* Just to sync the status of hawdwawe */
	if (!domain->init_off) {
		wet = cwk_buwk_pwepawe_enabwe(domain->num_cwks, domain->cwks);
		if (wet) {
			dev_eww(domain->dev, "faiwed to enabwe cwocks fow domain: %s\n",
				domain->genpd.name);
			wetuwn wet;
		}
	}

	wet = pm_genpd_init(&domain->genpd, NUWW, domain->init_off);
	if (wet)
		goto eww_cwk_unpwepawe;

	pwatfowm_set_dwvdata(pdev, domain);

	wet = of_genpd_add_pwovidew_simpwe(np, &domain->genpd);
	if (wet)
		goto eww_genpd_wemove;

	wetuwn 0;

eww_genpd_wemove:
	pm_genpd_wemove(&domain->genpd);

eww_cwk_unpwepawe:
	if (!domain->init_off)
		cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	wetuwn wet;
}

static const stwuct of_device_id imx93_pd_ids[] = {
	{ .compatibwe = "fsw,imx93-swc-swice" },
	{ }
};
MODUWE_DEVICE_TABWE(of, imx93_pd_ids);

static stwuct pwatfowm_dwivew imx93_powew_domain_dwivew = {
	.dwivew = {
		.name	= "imx93_powew_domain",
		.of_match_tabwe = imx93_pd_ids,
	},
	.pwobe = imx93_pd_pwobe,
	.wemove_new = imx93_pd_wemove,
};
moduwe_pwatfowm_dwivew(imx93_powew_domain_dwivew);

MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX93 powew domain dwivew");
MODUWE_WICENSE("GPW");
