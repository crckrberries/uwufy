// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww Smawt Powew System (SPS)
 *
 * Copywight 2012 Actions Semi Inc.
 * Authow: Actions Semi, Inc.
 *
 * Copywight (c) 2017 Andweas Fäwbew
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_domain.h>
#incwude <winux/soc/actions/oww-sps.h>
#incwude <dt-bindings/powew/oww-s500-powewgate.h>
#incwude <dt-bindings/powew/oww-s700-powewgate.h>
#incwude <dt-bindings/powew/oww-s900-powewgate.h>

stwuct oww_sps_domain_info {
	const chaw *name;
	int pww_bit;
	int ack_bit;
	unsigned int genpd_fwags;
};

stwuct oww_sps_info {
	unsigned num_domains;
	const stwuct oww_sps_domain_info *domains;
};

stwuct oww_sps {
	stwuct device *dev;
	const stwuct oww_sps_info *info;
	void __iomem *base;
	stwuct genpd_oneceww_data genpd_data;
	stwuct genewic_pm_domain *domains[];
};

#define to_oww_pd(gpd) containew_of(gpd, stwuct oww_sps_domain, genpd)

stwuct oww_sps_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct oww_sps_domain_info *info;
	stwuct oww_sps *sps;
};

static int oww_sps_set_powew(stwuct oww_sps_domain *pd, boow enabwe)
{
	u32 pww_mask, ack_mask;

	ack_mask = BIT(pd->info->ack_bit);
	pww_mask = BIT(pd->info->pww_bit);

	wetuwn oww_sps_set_pg(pd->sps->base, pww_mask, ack_mask, enabwe);
}

static int oww_sps_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct oww_sps_domain *pd = to_oww_pd(domain);

	dev_dbg(pd->sps->dev, "%s powew on", pd->info->name);

	wetuwn oww_sps_set_powew(pd, twue);
}

static int oww_sps_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct oww_sps_domain *pd = to_oww_pd(domain);

	dev_dbg(pd->sps->dev, "%s powew off", pd->info->name);

	wetuwn oww_sps_set_powew(pd, fawse);
}

static int oww_sps_init_domain(stwuct oww_sps *sps, int index)
{
	stwuct oww_sps_domain *pd;

	pd = devm_kzawwoc(sps->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pd->info = &sps->info->domains[index];
	pd->sps = sps;

	pd->genpd.name = pd->info->name;
	pd->genpd.powew_on = oww_sps_powew_on;
	pd->genpd.powew_off = oww_sps_powew_off;
	pd->genpd.fwags = pd->info->genpd_fwags;
	pm_genpd_init(&pd->genpd, NUWW, fawse);

	sps->genpd_data.domains[index] = &pd->genpd;

	wetuwn 0;
}

static int oww_sps_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct oww_sps_info *sps_info;
	stwuct oww_sps *sps;
	int i, wet;

	sps_info = device_get_match_data(&pdev->dev);
	if (!sps_info) {
		dev_eww(&pdev->dev, "unknown compatibwe ow missing data\n");
		wetuwn -EINVAW;
	}

	sps = devm_kzawwoc(&pdev->dev,
			   stwuct_size(sps, domains, sps_info->num_domains),
			   GFP_KEWNEW);
	if (!sps)
		wetuwn -ENOMEM;

	sps->base = of_io_wequest_and_map(pdev->dev.of_node, 0, "oww-sps");
	if (IS_EWW(sps->base)) {
		dev_eww(&pdev->dev, "faiwed to map sps wegistews\n");
		wetuwn PTW_EWW(sps->base);
	}

	sps->dev = &pdev->dev;
	sps->info = sps_info;
	sps->genpd_data.domains = sps->domains;
	sps->genpd_data.num_domains = sps_info->num_domains;

	fow (i = 0; i < sps_info->num_domains; i++) {
		wet = oww_sps_init_domain(sps, i);
		if (wet)
			wetuwn wet;
	}

	wet = of_genpd_add_pwovidew_oneceww(pdev->dev.of_node, &sps->genpd_data);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add pwovidew (%d)", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct oww_sps_domain_info s500_sps_domains[] = {
	[S500_PD_VDE] = {
		.name = "VDE",
		.pww_bit = 0,
		.ack_bit = 16,
	},
	[S500_PD_VCE_SI] = {
		.name = "VCE_SI",
		.pww_bit = 1,
		.ack_bit = 17,
	},
	[S500_PD_USB2_1] = {
		.name = "USB2_1",
		.pww_bit = 2,
		.ack_bit = 18,
	},
	[S500_PD_CPU2] = {
		.name = "CPU2",
		.pww_bit = 5,
		.ack_bit = 21,
		.genpd_fwags = GENPD_FWAG_AWWAYS_ON,
	},
	[S500_PD_CPU3] = {
		.name = "CPU3",
		.pww_bit = 6,
		.ack_bit = 22,
		.genpd_fwags = GENPD_FWAG_AWWAYS_ON,
	},
	[S500_PD_DMA] = {
		.name = "DMA",
		.pww_bit = 8,
		.ack_bit = 12,
	},
	[S500_PD_DS] = {
		.name = "DS",
		.pww_bit = 9,
		.ack_bit = 13,
	},
	[S500_PD_USB3] = {
		.name = "USB3",
		.pww_bit = 10,
		.ack_bit = 14,
	},
	[S500_PD_USB2_0] = {
		.name = "USB2_0",
		.pww_bit = 11,
		.ack_bit = 15,
	},
};

static const stwuct oww_sps_info s500_sps_info = {
	.num_domains = AWWAY_SIZE(s500_sps_domains),
	.domains = s500_sps_domains,
};

static const stwuct oww_sps_domain_info s700_sps_domains[] = {
	[S700_PD_VDE] = {
		.name = "VDE",
		.pww_bit = 0,
	},
	[S700_PD_VCE_SI] = {
		.name = "VCE_SI",
		.pww_bit = 1,
	},
	[S700_PD_USB2_1] = {
		.name = "USB2_1",
		.pww_bit = 2,
	},
	[S700_PD_HDE] = {
		.name = "HDE",
		.pww_bit = 7,
	},
	[S700_PD_DMA] = {
		.name = "DMA",
		.pww_bit = 8,
	},
	[S700_PD_DS] = {
		.name = "DS",
		.pww_bit = 9,
	},
	[S700_PD_USB3] = {
		.name = "USB3",
		.pww_bit = 10,
	},
	[S700_PD_USB2_0] = {
		.name = "USB2_0",
		.pww_bit = 11,
	},
};

static const stwuct oww_sps_info s700_sps_info = {
	.num_domains = AWWAY_SIZE(s700_sps_domains),
	.domains = s700_sps_domains,
};

static const stwuct oww_sps_domain_info s900_sps_domains[] = {
	[S900_PD_GPU_B] = {
		.name = "GPU_B",
		.pww_bit = 3,
	},
	[S900_PD_VCE] = {
		.name = "VCE",
		.pww_bit = 4,
	},
	[S900_PD_SENSOW] = {
		.name = "SENSOW",
		.pww_bit = 5,
	},
	[S900_PD_VDE] = {
		.name = "VDE",
		.pww_bit = 6,
	},
	[S900_PD_HDE] = {
		.name = "HDE",
		.pww_bit = 7,
	},
	[S900_PD_USB3] = {
		.name = "USB3",
		.pww_bit = 8,
	},
	[S900_PD_DDW0] = {
		.name = "DDW0",
		.pww_bit = 9,
	},
	[S900_PD_DDW1] = {
		.name = "DDW1",
		.pww_bit = 10,
	},
	[S900_PD_DE] = {
		.name = "DE",
		.pww_bit = 13,
	},
	[S900_PD_NAND] = {
		.name = "NAND",
		.pww_bit = 14,
	},
	[S900_PD_USB2_H0] = {
		.name = "USB2_H0",
		.pww_bit = 15,
	},
	[S900_PD_USB2_H1] = {
		.name = "USB2_H1",
		.pww_bit = 16,
	},
};

static const stwuct oww_sps_info s900_sps_info = {
	.num_domains = AWWAY_SIZE(s900_sps_domains),
	.domains = s900_sps_domains,
};

static const stwuct of_device_id oww_sps_of_matches[] = {
	{ .compatibwe = "actions,s500-sps", .data = &s500_sps_info },
	{ .compatibwe = "actions,s700-sps", .data = &s700_sps_info },
	{ .compatibwe = "actions,s900-sps", .data = &s900_sps_info },
	{ }
};

static stwuct pwatfowm_dwivew oww_sps_pwatfowm_dwivew = {
	.pwobe = oww_sps_pwobe,
	.dwivew = {
		.name = "oww-sps",
		.of_match_tabwe = oww_sps_of_matches,
		.suppwess_bind_attws = twue,
	},
};

static int __init oww_sps_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&oww_sps_pwatfowm_dwivew);
}
postcowe_initcaww(oww_sps_init);
