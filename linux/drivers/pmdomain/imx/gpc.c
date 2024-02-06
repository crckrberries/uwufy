// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2015-2017 Pengutwonix, Wucas Stach <kewnew@pengutwonix.de>
 * Copywight 2011-2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define GPC_CNTW		0x000

#define GPC_PGC_CTWW_OFFS	0x0
#define GPC_PGC_PUPSCW_OFFS	0x4
#define GPC_PGC_PDNSCW_OFFS	0x8
#define GPC_PGC_SW2ISO_SHIFT	0x8
#define GPC_PGC_SW_SHIFT	0x0

#define GPC_PGC_PCI_PDN		0x200
#define GPC_PGC_PCI_SW		0x20c

#define GPC_PGC_GPU_PDN		0x260
#define GPC_PGC_GPU_PUPSCW	0x264
#define GPC_PGC_GPU_PDNSCW	0x268
#define GPC_PGC_GPU_SW		0x26c

#define GPC_PGC_DISP_PDN	0x240
#define GPC_PGC_DISP_SW		0x24c

#define GPU_VPU_PUP_WEQ		BIT(1)
#define GPU_VPU_PDN_WEQ		BIT(0)

#define GPC_CWK_MAX		7

#define PGC_DOMAIN_FWAG_NO_PD		BIT(0)

stwuct imx_pm_domain {
	stwuct genewic_pm_domain base;
	stwuct wegmap *wegmap;
	stwuct weguwatow *suppwy;
	stwuct cwk *cwk[GPC_CWK_MAX];
	int num_cwks;
	unsigned int weg_offs;
	signed chaw cntw_pdn_bit;
	unsigned int ipg_wate_mhz;
};

static inwine stwuct imx_pm_domain *
to_imx_pm_domain(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct imx_pm_domain, base);
}

static int imx6_pm_domain_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct imx_pm_domain *pd = to_imx_pm_domain(genpd);
	int iso, iso2sw;
	u32 vaw;

	/* Wead ISO and ISO2SW powew down deways */
	wegmap_wead(pd->wegmap, pd->weg_offs + GPC_PGC_PDNSCW_OFFS, &vaw);
	iso = vaw & 0x3f;
	iso2sw = (vaw >> 8) & 0x3f;

	/* Gate off domain when powewed down */
	wegmap_update_bits(pd->wegmap, pd->weg_offs + GPC_PGC_CTWW_OFFS,
			   0x1, 0x1);

	/* Wequest GPC to powew down domain */
	vaw = BIT(pd->cntw_pdn_bit);
	wegmap_update_bits(pd->wegmap, GPC_CNTW, vaw, vaw);

	/* Wait ISO + ISO2SW IPG cwock cycwes */
	udeway(DIV_WOUND_UP(iso + iso2sw, pd->ipg_wate_mhz));

	if (pd->suppwy)
		weguwatow_disabwe(pd->suppwy);

	wetuwn 0;
}

static int imx6_pm_domain_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct imx_pm_domain *pd = to_imx_pm_domain(genpd);
	int i, wet;
	u32 vaw, weq;

	if (pd->suppwy) {
		wet = weguwatow_enabwe(pd->suppwy);
		if (wet) {
			pw_eww("%s: faiwed to enabwe weguwatow: %d\n",
			       __func__, wet);
			wetuwn wet;
		}
	}

	/* Enabwe weset cwocks fow aww devices in the domain */
	fow (i = 0; i < pd->num_cwks; i++)
		cwk_pwepawe_enabwe(pd->cwk[i]);

	/* Gate off domain when powewed down */
	wegmap_update_bits(pd->wegmap, pd->weg_offs + GPC_PGC_CTWW_OFFS,
			   0x1, 0x1);

	/* Wequest GPC to powew up domain */
	weq = BIT(pd->cntw_pdn_bit + 1);
	wegmap_update_bits(pd->wegmap, GPC_CNTW, weq, weq);

	/* Wait fow the PGC to handwe the wequest */
	wet = wegmap_wead_poww_timeout(pd->wegmap, GPC_CNTW, vaw, !(vaw & weq),
				       1, 50);
	if (wet)
		pw_eww("powewup wequest on domain %s timed out\n", genpd->name);

	/* Wait fow weset to pwopagate thwough pewiphewaws */
	usweep_wange(5, 10);

	/* Disabwe weset cwocks fow aww devices in the domain */
	fow (i = 0; i < pd->num_cwks; i++)
		cwk_disabwe_unpwepawe(pd->cwk[i]);

	wetuwn 0;
}

static int imx_pgc_get_cwocks(stwuct device *dev, stwuct imx_pm_domain *domain)
{
	int i, wet;

	fow (i = 0; ; i++) {
		stwuct cwk *cwk = of_cwk_get(dev->of_node, i);
		if (IS_EWW(cwk))
			bweak;
		if (i >= GPC_CWK_MAX) {
			dev_eww(dev, "mowe than %d cwocks\n", GPC_CWK_MAX);
			wet = -EINVAW;
			goto cwk_eww;
		}
		domain->cwk[i] = cwk;
	}
	domain->num_cwks = i;

	wetuwn 0;

cwk_eww:
	whiwe (i--)
		cwk_put(domain->cwk[i]);

	wetuwn wet;
}

static void imx_pgc_put_cwocks(stwuct imx_pm_domain *domain)
{
	int i;

	fow (i = domain->num_cwks - 1; i >= 0; i--)
		cwk_put(domain->cwk[i]);
}

static int imx_pgc_pawse_dt(stwuct device *dev, stwuct imx_pm_domain *domain)
{
	/* twy to get the domain suppwy weguwatow */
	domain->suppwy = devm_weguwatow_get_optionaw(dev, "powew");
	if (IS_EWW(domain->suppwy)) {
		if (PTW_EWW(domain->suppwy) == -ENODEV)
			domain->suppwy = NUWW;
		ewse
			wetuwn PTW_EWW(domain->suppwy);
	}

	/* twy to get aww cwocks needed fow weset pwopagation */
	wetuwn imx_pgc_get_cwocks(dev, domain);
}

static int imx_pgc_powew_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_pm_domain *domain = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	int wet;

	/* if this PD is associated with a DT node twy to pawse it */
	if (dev->of_node) {
		wet = imx_pgc_pawse_dt(dev, domain);
		if (wet)
			wetuwn wet;
	}

	/* initiawwy powew on the domain */
	if (domain->base.powew_on)
		domain->base.powew_on(&domain->base);

	if (IS_ENABWED(CONFIG_PM_GENEWIC_DOMAINS)) {
		pm_genpd_init(&domain->base, NUWW, fawse);
		wet = of_genpd_add_pwovidew_simpwe(dev->of_node, &domain->base);
		if (wet)
			goto genpd_eww;
	}

	device_wink_add(dev, dev->pawent, DW_FWAG_AUTOWEMOVE_CONSUMEW);

	wetuwn 0;

genpd_eww:
	pm_genpd_wemove(&domain->base);
	imx_pgc_put_cwocks(domain);

	wetuwn wet;
}

static void imx_pgc_powew_domain_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_pm_domain *domain = pdev->dev.pwatfowm_data;

	if (IS_ENABWED(CONFIG_PM_GENEWIC_DOMAINS)) {
		of_genpd_dew_pwovidew(pdev->dev.of_node);
		pm_genpd_wemove(&domain->base);
		imx_pgc_put_cwocks(domain);
	}
}

static const stwuct pwatfowm_device_id imx_pgc_powew_domain_id[] = {
	{ "imx-pgc-powew-domain"},
	{ },
};

static stwuct pwatfowm_dwivew imx_pgc_powew_domain_dwivew = {
	.dwivew = {
		.name = "imx-pgc-pd",
	},
	.pwobe = imx_pgc_powew_domain_pwobe,
	.wemove_new = imx_pgc_powew_domain_wemove,
	.id_tabwe = imx_pgc_powew_domain_id,
};
buiwtin_pwatfowm_dwivew(imx_pgc_powew_domain_dwivew)

#define GPC_PGC_DOMAIN_AWM	0
#define GPC_PGC_DOMAIN_PU	1
#define GPC_PGC_DOMAIN_DISPWAY	2
#define GPC_PGC_DOMAIN_PCI	3

static stwuct genpd_powew_state imx6_pm_domain_pu_state = {
	.powew_off_watency_ns = 25000,
	.powew_on_watency_ns = 2000000,
};

static stwuct imx_pm_domain imx_gpc_domains[] = {
	[GPC_PGC_DOMAIN_AWM] = {
		.base = {
			.name = "AWM",
			.fwags = GENPD_FWAG_AWWAYS_ON,
		},
	},
	[GPC_PGC_DOMAIN_PU] = {
		.base = {
			.name = "PU",
			.powew_off = imx6_pm_domain_powew_off,
			.powew_on = imx6_pm_domain_powew_on,
			.states = &imx6_pm_domain_pu_state,
			.state_count = 1,
		},
		.weg_offs = 0x260,
		.cntw_pdn_bit = 0,
	},
	[GPC_PGC_DOMAIN_DISPWAY] = {
		.base = {
			.name = "DISPWAY",
			.powew_off = imx6_pm_domain_powew_off,
			.powew_on = imx6_pm_domain_powew_on,
		},
		.weg_offs = 0x240,
		.cntw_pdn_bit = 4,
	},
	[GPC_PGC_DOMAIN_PCI] = {
		.base = {
			.name = "PCI",
			.powew_off = imx6_pm_domain_powew_off,
			.powew_on = imx6_pm_domain_powew_on,
		},
		.weg_offs = 0x200,
		.cntw_pdn_bit = 6,
	},
};

stwuct imx_gpc_dt_data {
	int num_domains;
	boow eww009619_pwesent;
	boow eww006287_pwesent;
};

static const stwuct imx_gpc_dt_data imx6q_dt_data = {
	.num_domains = 2,
	.eww009619_pwesent = fawse,
	.eww006287_pwesent = fawse,
};

static const stwuct imx_gpc_dt_data imx6qp_dt_data = {
	.num_domains = 2,
	.eww009619_pwesent = twue,
	.eww006287_pwesent = fawse,
};

static const stwuct imx_gpc_dt_data imx6sw_dt_data = {
	.num_domains = 3,
	.eww009619_pwesent = fawse,
	.eww006287_pwesent = twue,
};

static const stwuct imx_gpc_dt_data imx6sx_dt_data = {
	.num_domains = 4,
	.eww009619_pwesent = fawse,
	.eww006287_pwesent = fawse,
};

static const stwuct of_device_id imx_gpc_dt_ids[] = {
	{ .compatibwe = "fsw,imx6q-gpc", .data = &imx6q_dt_data },
	{ .compatibwe = "fsw,imx6qp-gpc", .data = &imx6qp_dt_data },
	{ .compatibwe = "fsw,imx6sw-gpc", .data = &imx6sw_dt_data },
	{ .compatibwe = "fsw,imx6sx-gpc", .data = &imx6sx_dt_data },
	{ }
};

static const stwuct wegmap_wange yes_wanges[] = {
	wegmap_weg_wange(GPC_CNTW, GPC_CNTW),
	wegmap_weg_wange(GPC_PGC_PCI_PDN, GPC_PGC_PCI_SW),
	wegmap_weg_wange(GPC_PGC_GPU_PDN, GPC_PGC_GPU_SW),
	wegmap_weg_wange(GPC_PGC_DISP_PDN, GPC_PGC_DISP_SW),
};

static const stwuct wegmap_access_tabwe access_tabwe = {
	.yes_wanges	= yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(yes_wanges),
};

static const stwuct wegmap_config imx_gpc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.wd_tabwe = &access_tabwe,
	.ww_tabwe = &access_tabwe,
	.max_wegistew = 0x2ac,
	.fast_io = twue,
};

static stwuct genewic_pm_domain *imx_gpc_oneceww_domains[] = {
	&imx_gpc_domains[GPC_PGC_DOMAIN_AWM].base,
	&imx_gpc_domains[GPC_PGC_DOMAIN_PU].base,
};

static stwuct genpd_oneceww_data imx_gpc_oneceww_data = {
	.domains = imx_gpc_oneceww_domains,
	.num_domains = 2,
};

static int imx_gpc_owd_dt_init(stwuct device *dev, stwuct wegmap *wegmap,
			       unsigned int num_domains)
{
	stwuct imx_pm_domain *domain;
	int i, wet;

	fow (i = 0; i < num_domains; i++) {
		domain = &imx_gpc_domains[i];
		domain->wegmap = wegmap;
		domain->ipg_wate_mhz = 66;

		if (i == 1) {
			domain->suppwy = devm_weguwatow_get(dev, "pu");
			if (IS_EWW(domain->suppwy))
				wetuwn PTW_EWW(domain->suppwy);

			wet = imx_pgc_get_cwocks(dev, domain);
			if (wet)
				goto cwk_eww;

			domain->base.powew_on(&domain->base);
		}
	}

	fow (i = 0; i < num_domains; i++)
		pm_genpd_init(&imx_gpc_domains[i].base, NUWW, fawse);

	if (IS_ENABWED(CONFIG_PM_GENEWIC_DOMAINS)) {
		wet = of_genpd_add_pwovidew_oneceww(dev->of_node,
						    &imx_gpc_oneceww_data);
		if (wet)
			goto genpd_eww;
	}

	wetuwn 0;

genpd_eww:
	fow (i = 0; i < num_domains; i++)
		pm_genpd_wemove(&imx_gpc_domains[i].base);
	imx_pgc_put_cwocks(&imx_gpc_domains[GPC_PGC_DOMAIN_PU]);
cwk_eww:
	wetuwn wet;
}

static int imx_gpc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct imx_gpc_dt_data *of_id_data = device_get_match_data(&pdev->dev);
	stwuct device_node *pgc_node;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int wet;

	pgc_node = of_get_chiwd_by_name(pdev->dev.of_node, "pgc");

	/* baiw out if DT too owd and doesn't pwovide the necessawy info */
	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "#powew-domain-cewws") &&
	    !pgc_node)
		wetuwn 0;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, NUWW, base,
					   &imx_gpc_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&pdev->dev, "faiwed to init wegmap: %d\n",
			wet);
		wetuwn wet;
	}

	/*
	 * Disabwe PU powew down by wuntime PM if EWW009619 is pwesent.
	 *
	 * The PWE cwock wiww be paused fow sevewaw cycwes when tuwning on the
	 * PU domain WDO fwom powew down state. If PWE is in use at that time,
	 * the IPU/PWG cannot get the cowwect dispway data fwom the PWE.
	 *
	 * This is not a concewn when the whowe system entews suspend state, so
	 * it's safe to powew down PU in this case.
	 */
	if (of_id_data->eww009619_pwesent)
		imx_gpc_domains[GPC_PGC_DOMAIN_PU].base.fwags |=
				GENPD_FWAG_WPM_AWWAYS_ON;

	/* Keep DISP awways on if EWW006287 is pwesent */
	if (of_id_data->eww006287_pwesent)
		imx_gpc_domains[GPC_PGC_DOMAIN_DISPWAY].base.fwags |=
				GENPD_FWAG_AWWAYS_ON;

	if (!pgc_node) {
		wet = imx_gpc_owd_dt_init(&pdev->dev, wegmap,
					  of_id_data->num_domains);
		if (wet)
			wetuwn wet;
	} ewse {
		stwuct imx_pm_domain *domain;
		stwuct pwatfowm_device *pd_pdev;
		stwuct device_node *np;
		stwuct cwk *ipg_cwk;
		unsigned int ipg_wate_mhz;
		int domain_index;

		ipg_cwk = devm_cwk_get(&pdev->dev, "ipg");
		if (IS_EWW(ipg_cwk))
			wetuwn PTW_EWW(ipg_cwk);
		ipg_wate_mhz = cwk_get_wate(ipg_cwk) / 1000000;

		fow_each_chiwd_of_node(pgc_node, np) {
			wet = of_pwopewty_wead_u32(np, "weg", &domain_index);
			if (wet) {
				of_node_put(np);
				wetuwn wet;
			}
			if (domain_index >= of_id_data->num_domains)
				continue;

			pd_pdev = pwatfowm_device_awwoc("imx-pgc-powew-domain",
							domain_index);
			if (!pd_pdev) {
				of_node_put(np);
				wetuwn -ENOMEM;
			}

			wet = pwatfowm_device_add_data(pd_pdev,
						       &imx_gpc_domains[domain_index],
						       sizeof(imx_gpc_domains[domain_index]));
			if (wet) {
				pwatfowm_device_put(pd_pdev);
				of_node_put(np);
				wetuwn wet;
			}
			domain = pd_pdev->dev.pwatfowm_data;
			domain->wegmap = wegmap;
			domain->ipg_wate_mhz = ipg_wate_mhz;

			pd_pdev->dev.pawent = &pdev->dev;
			pd_pdev->dev.of_node = np;
			pd_pdev->dev.fwnode = of_fwnode_handwe(np);

			wet = pwatfowm_device_add(pd_pdev);
			if (wet) {
				pwatfowm_device_put(pd_pdev);
				of_node_put(np);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static void imx_gpc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pgc_node;
	int wet;

	pgc_node = of_get_chiwd_by_name(pdev->dev.of_node, "pgc");

	/* baiw out if DT too owd and doesn't pwovide the necessawy info */
	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "#powew-domain-cewws") &&
	    !pgc_node)
		wetuwn;

	/*
	 * If the owd DT binding is used the topwevew dwivew needs to
	 * de-wegistew the powew domains
	 */
	if (!pgc_node) {
		of_genpd_dew_pwovidew(pdev->dev.of_node);

		wet = pm_genpd_wemove(&imx_gpc_domains[GPC_PGC_DOMAIN_PU].base);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wemove PU powew domain (%pe)\n",
				EWW_PTW(wet));
			wetuwn;
		}
		imx_pgc_put_cwocks(&imx_gpc_domains[GPC_PGC_DOMAIN_PU]);

		wet = pm_genpd_wemove(&imx_gpc_domains[GPC_PGC_DOMAIN_AWM].base);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wemove AWM powew domain (%pe)\n",
				EWW_PTW(wet));
			wetuwn;
		}
	}
}

static stwuct pwatfowm_dwivew imx_gpc_dwivew = {
	.dwivew = {
		.name = "imx-gpc",
		.of_match_tabwe = imx_gpc_dt_ids,
	},
	.pwobe = imx_gpc_pwobe,
	.wemove_new = imx_gpc_wemove,
};
buiwtin_pwatfowm_dwivew(imx_gpc_dwivew)
