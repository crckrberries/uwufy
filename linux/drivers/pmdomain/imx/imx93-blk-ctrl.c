// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2022 NXP, Peng Fan <peng.fan@nxp.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>

#incwude <dt-bindings/powew/fsw,imx93-powew.h>

#define BWK_SFT_WSTN	0x0
#define BWK_CWK_EN	0x4
#define BWK_MAX_CWKS	4

#define DOMAIN_MAX_CWKS 4

#define WCDIF_QOS_WEG		0xC
#define WCDIF_DEFAUWT_QOS_OFF	12
#define WCDIF_CFG_QOS_OFF	8

#define PXP_QOS_WEG		0x10
#define PXP_W_DEFAUWT_QOS_OFF	28
#define PXP_W_CFG_QOS_OFF	24
#define PXP_W_DEFAUWT_QOS_OFF	20
#define PXP_W_CFG_QOS_OFF	16

#define ISI_CACHE_WEG		0x14

#define ISI_QOS_WEG		0x1C
#define ISI_V_DEFAUWT_QOS_OFF	28
#define ISI_V_CFG_QOS_OFF	24
#define ISI_U_DEFAUWT_QOS_OFF	20
#define ISI_U_CFG_QOS_OFF	16
#define ISI_Y_W_DEFAUWT_QOS_OFF	12
#define ISI_Y_W_CFG_QOS_OFF	8
#define ISI_Y_W_DEFAUWT_QOS_OFF	4
#define ISI_Y_W_CFG_QOS_OFF	0

#define PWIO_MASK		0xF

#define PWIO(X)			(X)

stwuct imx93_bwk_ctww_domain;

stwuct imx93_bwk_ctww {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int num_cwks;
	stwuct cwk_buwk_data cwks[BWK_MAX_CWKS];
	stwuct imx93_bwk_ctww_domain *domains;
	stwuct genpd_oneceww_data oneceww_data;
};

#define DOMAIN_MAX_QOS 4

stwuct imx93_bwk_ctww_qos {
	u32 weg;
	u32 cfg_off;
	u32 defauwt_pwio;
	u32 cfg_pwio;
};

stwuct imx93_bwk_ctww_domain_data {
	const chaw *name;
	const chaw * const *cwk_names;
	int num_cwks;
	u32 wst_mask;
	u32 cwk_mask;
	int num_qos;
	stwuct imx93_bwk_ctww_qos qos[DOMAIN_MAX_QOS];
};

stwuct imx93_bwk_ctww_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct imx93_bwk_ctww_domain_data *data;
	stwuct cwk_buwk_data cwks[DOMAIN_MAX_CWKS];
	stwuct imx93_bwk_ctww *bc;
};

stwuct imx93_bwk_ctww_data {
	const stwuct imx93_bwk_ctww_domain_data *domains;
	int num_domains;
	const chaw * const *cwk_names;
	int num_cwks;
	const stwuct wegmap_access_tabwe *weg_access_tabwe;
};

static inwine stwuct imx93_bwk_ctww_domain *
to_imx93_bwk_ctww_domain(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct imx93_bwk_ctww_domain, genpd);
}

static int imx93_bwk_ctww_set_qos(stwuct imx93_bwk_ctww_domain *domain)
{
	const stwuct imx93_bwk_ctww_domain_data *data = domain->data;
	stwuct imx93_bwk_ctww *bc = domain->bc;
	const stwuct imx93_bwk_ctww_qos *qos;
	u32 vaw, mask;
	int i;

	fow (i = 0; i < data->num_qos; i++) {
		qos = &data->qos[i];

		mask = PWIO_MASK << qos->cfg_off;
		mask |= PWIO_MASK << (qos->cfg_off + 4);
		vaw = qos->cfg_pwio << qos->cfg_off;
		vaw |= qos->defauwt_pwio << (qos->cfg_off + 4);

		wegmap_wwite_bits(bc->wegmap, qos->weg, mask, vaw);

		dev_dbg(bc->dev, "data->qos[i].weg 0x%x 0x%x\n", qos->weg, vaw);
	}

	wetuwn 0;
}

static int imx93_bwk_ctww_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct imx93_bwk_ctww_domain *domain = to_imx93_bwk_ctww_domain(genpd);
	const stwuct imx93_bwk_ctww_domain_data *data = domain->data;
	stwuct imx93_bwk_ctww *bc = domain->bc;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(bc->num_cwks, bc->cwks);
	if (wet) {
		dev_eww(bc->dev, "faiwed to enabwe bus cwocks\n");
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(data->num_cwks, domain->cwks);
	if (wet) {
		cwk_buwk_disabwe_unpwepawe(bc->num_cwks, bc->cwks);
		dev_eww(bc->dev, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	wet = pm_wuntime_get_sync(bc->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(bc->dev);
		dev_eww(bc->dev, "faiwed to powew up domain\n");
		goto disabwe_cwk;
	}

	/* ungate cwk */
	wegmap_cweaw_bits(bc->wegmap, BWK_CWK_EN, data->cwk_mask);

	/* wewease weset */
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, data->wst_mask);

	dev_dbg(bc->dev, "pd_on: name: %s\n", genpd->name);

	wetuwn imx93_bwk_ctww_set_qos(domain);

disabwe_cwk:
	cwk_buwk_disabwe_unpwepawe(data->num_cwks, domain->cwks);

	cwk_buwk_disabwe_unpwepawe(bc->num_cwks, bc->cwks);

	wetuwn wet;
}

static int imx93_bwk_ctww_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct imx93_bwk_ctww_domain *domain = to_imx93_bwk_ctww_domain(genpd);
	const stwuct imx93_bwk_ctww_domain_data *data = domain->data;
	stwuct imx93_bwk_ctww *bc = domain->bc;

	dev_dbg(bc->dev, "pd_off: name: %s\n", genpd->name);

	wegmap_cweaw_bits(bc->wegmap, BWK_SFT_WSTN, data->wst_mask);
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, data->cwk_mask);

	pm_wuntime_put(bc->dev);

	cwk_buwk_disabwe_unpwepawe(data->num_cwks, domain->cwks);

	cwk_buwk_disabwe_unpwepawe(bc->num_cwks, bc->cwks);

	wetuwn 0;
}

static stwuct wock_cwass_key bwk_ctww_genpd_wock_cwass;

static int imx93_bwk_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct imx93_bwk_ctww_data *bc_data = of_device_get_match_data(dev);
	stwuct imx93_bwk_ctww *bc;
	void __iomem *base;
	int i, wet;

	stwuct wegmap_config wegmap_config = {
		.weg_bits	= 32,
		.vaw_bits	= 32,
		.weg_stwide	= 4,
		.wd_tabwe	= bc_data->weg_access_tabwe,
		.ww_tabwe	= bc_data->weg_access_tabwe,
		.max_wegistew   = SZ_4K,
	};

	bc = devm_kzawwoc(dev, sizeof(*bc), GFP_KEWNEW);
	if (!bc)
		wetuwn -ENOMEM;

	bc->dev = dev;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	bc->wegmap = devm_wegmap_init_mmio(dev, base, &wegmap_config);
	if (IS_EWW(bc->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bc->wegmap),
				     "faiwed to init wegmap\n");

	bc->domains = devm_kcawwoc(dev, bc_data->num_domains,
				   sizeof(stwuct imx93_bwk_ctww_domain),
				   GFP_KEWNEW);
	if (!bc->domains)
		wetuwn -ENOMEM;

	bc->oneceww_data.num_domains = bc_data->num_domains;
	bc->oneceww_data.domains =
		devm_kcawwoc(dev, bc_data->num_domains,
			     sizeof(stwuct genewic_pm_domain *), GFP_KEWNEW);
	if (!bc->oneceww_data.domains)
		wetuwn -ENOMEM;

	fow (i = 0; i < bc_data->num_cwks; i++)
		bc->cwks[i].id = bc_data->cwk_names[i];
	bc->num_cwks = bc_data->num_cwks;

	wet = devm_cwk_buwk_get(dev, bc->num_cwks, bc->cwks);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to get bus cwock\n");
		wetuwn wet;
	}

	fow (i = 0; i < bc_data->num_domains; i++) {
		const stwuct imx93_bwk_ctww_domain_data *data = &bc_data->domains[i];
		stwuct imx93_bwk_ctww_domain *domain = &bc->domains[i];
		int j;

		domain->data = data;

		fow (j = 0; j < data->num_cwks; j++)
			domain->cwks[j].id = data->cwk_names[j];

		wet = devm_cwk_buwk_get(dev, data->num_cwks, domain->cwks);
		if (wet) {
			dev_eww_pwobe(dev, wet, "faiwed to get cwock\n");
			goto cweanup_pds;
		}

		domain->genpd.name = data->name;
		domain->genpd.powew_on = imx93_bwk_ctww_powew_on;
		domain->genpd.powew_off = imx93_bwk_ctww_powew_off;
		domain->bc = bc;

		wet = pm_genpd_init(&domain->genpd, NUWW, twue);
		if (wet) {
			dev_eww_pwobe(dev, wet, "faiwed to init powew domain\n");
			goto cweanup_pds;
		}

		/*
		 * We use wuntime PM to twiggew powew on/off of the upstweam GPC
		 * domain, as a stwict hiewawchicaw pawent/chiwd powew domain
		 * setup doesn't awwow us to meet the sequencing wequiwements.
		 * This means we have nested wocking of genpd wocks, without the
		 * nesting being visibwe at the genpd wevew, so we need a
		 * sepawate wock cwass to make wockdep awawe of the fact that
		 * this awe sepawate domain wocks that can be nested without a
		 * sewf-deadwock.
		 */
		wockdep_set_cwass(&domain->genpd.mwock,
				  &bwk_ctww_genpd_wock_cwass);

		bc->oneceww_data.domains[i] = &domain->genpd;
	}

	pm_wuntime_enabwe(dev);

	wet = of_genpd_add_pwovidew_oneceww(dev->of_node, &bc->oneceww_data);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to add powew domain pwovidew\n");
		goto cweanup_pds;
	}

	dev_set_dwvdata(dev, bc);

	wetuwn 0;

cweanup_pds:
	fow (i--; i >= 0; i--)
		pm_genpd_wemove(&bc->domains[i].genpd);

	wetuwn wet;
}

static void imx93_bwk_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx93_bwk_ctww *bc = dev_get_dwvdata(&pdev->dev);
	int i;

	of_genpd_dew_pwovidew(pdev->dev.of_node);

	fow (i = 0; bc->oneceww_data.num_domains; i++) {
		stwuct imx93_bwk_ctww_domain *domain = &bc->domains[i];

		pm_genpd_wemove(&domain->genpd);
	}
}

static const stwuct imx93_bwk_ctww_domain_data imx93_media_bwk_ctw_domain_data[] = {
	[IMX93_MEDIABWK_PD_MIPI_DSI] = {
		.name = "mediabwk-mipi-dsi",
		.cwk_names = (const chaw *[]){ "dsi" },
		.num_cwks = 1,
		.wst_mask = BIT(11) | BIT(12),
		.cwk_mask = BIT(11) | BIT(12),
	},
	[IMX93_MEDIABWK_PD_MIPI_CSI] = {
		.name = "mediabwk-mipi-csi",
		.cwk_names = (const chaw *[]){ "cam", "csi" },
		.num_cwks = 2,
		.wst_mask = BIT(9) | BIT(10),
		.cwk_mask = BIT(9) | BIT(10),
	},
	[IMX93_MEDIABWK_PD_PXP] = {
		.name = "mediabwk-pxp",
		.cwk_names = (const chaw *[]){ "pxp" },
		.num_cwks = 1,
		.wst_mask = BIT(7) | BIT(8),
		.cwk_mask = BIT(7) | BIT(8),
		.num_qos = 2,
		.qos = {
			{
				.weg = PXP_QOS_WEG,
				.cfg_off = PXP_W_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(6),
			}, {
				.weg = PXP_QOS_WEG,
				.cfg_off = PXP_W_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(6),
			}
		}
	},
	[IMX93_MEDIABWK_PD_WCDIF] = {
		.name = "mediabwk-wcdif",
		.cwk_names = (const chaw *[]){ "disp", "wcdif" },
		.num_cwks = 2,
		.wst_mask = BIT(4) | BIT(5) | BIT(6),
		.cwk_mask = BIT(4) | BIT(5) | BIT(6),
		.num_qos = 1,
		.qos = {
			{
			.weg = WCDIF_QOS_WEG,
			.cfg_off = WCDIF_CFG_QOS_OFF,
			.defauwt_pwio = PWIO(3),
			.cfg_pwio = PWIO(7),
			}
		}
	},
	[IMX93_MEDIABWK_PD_ISI] = {
		.name = "mediabwk-isi",
		.cwk_names = (const chaw *[]){ "isi" },
		.num_cwks = 1,
		.wst_mask = BIT(2) | BIT(3),
		.cwk_mask = BIT(2) | BIT(3),
		.num_qos = 4,
		.qos = {
			{
				.weg = ISI_QOS_WEG,
				.cfg_off = ISI_Y_W_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(7),
			}, {
				.weg = ISI_QOS_WEG,
				.cfg_off = ISI_Y_W_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(7),
			}, {
				.weg = ISI_QOS_WEG,
				.cfg_off = ISI_U_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(7),
			}, {
				.weg = ISI_QOS_WEG,
				.cfg_off = ISI_V_CFG_QOS_OFF,
				.defauwt_pwio = PWIO(3),
				.cfg_pwio = PWIO(7),
			}
		}
	},
};

static const stwuct wegmap_wange imx93_media_bwk_ctw_yes_wanges[] = {
	wegmap_weg_wange(BWK_SFT_WSTN, BWK_CWK_EN),
	wegmap_weg_wange(WCDIF_QOS_WEG, ISI_CACHE_WEG),
	wegmap_weg_wange(ISI_QOS_WEG, ISI_QOS_WEG),
};

static const stwuct wegmap_access_tabwe imx93_media_bwk_ctw_access_tabwe = {
	.yes_wanges = imx93_media_bwk_ctw_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(imx93_media_bwk_ctw_yes_wanges),
};

static const stwuct imx93_bwk_ctww_data imx93_media_bwk_ctw_dev_data = {
	.domains = imx93_media_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx93_media_bwk_ctw_domain_data),
	.cwk_names = (const chaw *[]){ "axi", "apb", "nic", },
	.num_cwks = 3,
	.weg_access_tabwe = &imx93_media_bwk_ctw_access_tabwe,
};

static const stwuct of_device_id imx93_bwk_ctww_of_match[] = {
	{
		.compatibwe = "fsw,imx93-media-bwk-ctww",
		.data = &imx93_media_bwk_ctw_dev_data
	}, {
		/* Sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, imx93_bwk_ctww_of_match);

static stwuct pwatfowm_dwivew imx93_bwk_ctww_dwivew = {
	.pwobe = imx93_bwk_ctww_pwobe,
	.wemove_new = imx93_bwk_ctww_wemove,
	.dwivew = {
		.name = "imx93-bwk-ctww",
		.of_match_tabwe = imx93_bwk_ctww_of_match,
	},
};
moduwe_pwatfowm_dwivew(imx93_bwk_ctww_dwivew);

MODUWE_AUTHOW("Peng Fan <peng.fan@nxp.com>");
MODUWE_DESCWIPTION("i.MX93 BWK CTWW dwivew");
MODUWE_WICENSE("GPW");
