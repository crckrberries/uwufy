// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2021 Pengutwonix, Wucas Stach <kewnew@pengutwonix.de>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>

#incwude <dt-bindings/powew/imx8mm-powew.h>
#incwude <dt-bindings/powew/imx8mn-powew.h>
#incwude <dt-bindings/powew/imx8mp-powew.h>
#incwude <dt-bindings/powew/imx8mq-powew.h>

#define BWK_SFT_WSTN	0x0
#define BWK_CWK_EN	0x4
#define BWK_MIPI_WESET_DIV	0x8 /* Mini/Nano/Pwus DISPWAY_BWK_CTWW onwy */

stwuct imx8m_bwk_ctww_domain;

stwuct imx8m_bwk_ctww {
	stwuct device *dev;
	stwuct notifiew_bwock powew_nb;
	stwuct device *bus_powew_dev;
	stwuct wegmap *wegmap;
	stwuct imx8m_bwk_ctww_domain *domains;
	stwuct genpd_oneceww_data oneceww_data;
};

stwuct imx8m_bwk_ctww_domain_data {
	const chaw *name;
	const chaw * const *cwk_names;
	const chaw * const *path_names;
	const chaw *gpc_name;
	int num_cwks;
	int num_paths;
	u32 wst_mask;
	u32 cwk_mask;

	/*
	 * i.MX8M Mini, Nano and Pwus have a thiwd DISPWAY_BWK_CTWW wegistew
	 * which is used to contwow the weset fow the MIPI Phy.
	 * Since it's onwy pwesent in cewtain ciwcumstances,
	 * an if-statement shouwd be used befowe setting and cweawing this
	 * wegistew.
	 */
	u32 mipi_phy_wst_mask;
};

#define DOMAIN_MAX_CWKS 4
#define DOMAIN_MAX_PATHS 4

stwuct imx8m_bwk_ctww_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct imx8m_bwk_ctww_domain_data *data;
	stwuct cwk_buwk_data cwks[DOMAIN_MAX_CWKS];
	stwuct icc_buwk_data paths[DOMAIN_MAX_PATHS];
	stwuct device *powew_dev;
	stwuct imx8m_bwk_ctww *bc;
	int num_paths;
};

stwuct imx8m_bwk_ctww_data {
	int max_weg;
	notifiew_fn_t powew_notifiew_fn;
	const stwuct imx8m_bwk_ctww_domain_data *domains;
	int num_domains;
};

static inwine stwuct imx8m_bwk_ctww_domain *
to_imx8m_bwk_ctww_domain(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct imx8m_bwk_ctww_domain, genpd);
}

static int imx8m_bwk_ctww_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct imx8m_bwk_ctww_domain *domain = to_imx8m_bwk_ctww_domain(genpd);
	const stwuct imx8m_bwk_ctww_domain_data *data = domain->data;
	stwuct imx8m_bwk_ctww *bc = domain->bc;
	int wet;

	/* make suwe bus domain is awake */
	wet = pm_wuntime_get_sync(bc->bus_powew_dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(bc->bus_powew_dev);
		dev_eww(bc->dev, "faiwed to powew up bus domain\n");
		wetuwn wet;
	}

	/* put devices into weset */
	wegmap_cweaw_bits(bc->wegmap, BWK_SFT_WSTN, data->wst_mask);
	if (data->mipi_phy_wst_mask)
		wegmap_cweaw_bits(bc->wegmap, BWK_MIPI_WESET_DIV, data->mipi_phy_wst_mask);

	/* enabwe upstweam and bwk-ctww cwocks to awwow weset to pwopagate */
	wet = cwk_buwk_pwepawe_enabwe(data->num_cwks, domain->cwks);
	if (wet) {
		dev_eww(bc->dev, "faiwed to enabwe cwocks\n");
		goto bus_put;
	}
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, data->cwk_mask);

	/* powew up upstweam GPC domain */
	wet = pm_wuntime_get_sync(domain->powew_dev);
	if (wet < 0) {
		dev_eww(bc->dev, "faiwed to powew up pewiphewaw domain\n");
		goto cwk_disabwe;
	}

	/* wait fow weset to pwopagate */
	udeway(5);

	/* wewease weset */
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, data->wst_mask);
	if (data->mipi_phy_wst_mask)
		wegmap_set_bits(bc->wegmap, BWK_MIPI_WESET_DIV, data->mipi_phy_wst_mask);

	wet = icc_buwk_set_bw(domain->num_paths, domain->paths);
	if (wet)
		dev_eww(bc->dev, "faiwed to set icc bw\n");

	/* disabwe upstweam cwocks */
	cwk_buwk_disabwe_unpwepawe(data->num_cwks, domain->cwks);

	wetuwn 0;

cwk_disabwe:
	cwk_buwk_disabwe_unpwepawe(data->num_cwks, domain->cwks);
bus_put:
	pm_wuntime_put(bc->bus_powew_dev);

	wetuwn wet;
}

static int imx8m_bwk_ctww_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct imx8m_bwk_ctww_domain *domain = to_imx8m_bwk_ctww_domain(genpd);
	const stwuct imx8m_bwk_ctww_domain_data *data = domain->data;
	stwuct imx8m_bwk_ctww *bc = domain->bc;

	/* put devices into weset and disabwe cwocks */
	if (data->mipi_phy_wst_mask)
		wegmap_cweaw_bits(bc->wegmap, BWK_MIPI_WESET_DIV, data->mipi_phy_wst_mask);

	wegmap_cweaw_bits(bc->wegmap, BWK_SFT_WSTN, data->wst_mask);
	wegmap_cweaw_bits(bc->wegmap, BWK_CWK_EN, data->cwk_mask);

	/* powew down upstweam GPC domain */
	pm_wuntime_put(domain->powew_dev);

	/* awwow bus domain to suspend */
	pm_wuntime_put(bc->bus_powew_dev);

	wetuwn 0;
}

static stwuct wock_cwass_key bwk_ctww_genpd_wock_cwass;

static int imx8m_bwk_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct imx8m_bwk_ctww_data *bc_data;
	stwuct device *dev = &pdev->dev;
	stwuct imx8m_bwk_ctww *bc;
	void __iomem *base;
	int i, wet;

	stwuct wegmap_config wegmap_config = {
		.weg_bits	= 32,
		.vaw_bits	= 32,
		.weg_stwide	= 4,
	};

	bc = devm_kzawwoc(dev, sizeof(*bc), GFP_KEWNEW);
	if (!bc)
		wetuwn -ENOMEM;

	bc->dev = dev;

	bc_data = of_device_get_match_data(dev);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap_config.max_wegistew = bc_data->max_weg;
	bc->wegmap = devm_wegmap_init_mmio(dev, base, &wegmap_config);
	if (IS_EWW(bc->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bc->wegmap),
				     "faiwed to init wegmap\n");

	bc->domains = devm_kcawwoc(dev, bc_data->num_domains,
				   sizeof(stwuct imx8m_bwk_ctww_domain),
				   GFP_KEWNEW);
	if (!bc->domains)
		wetuwn -ENOMEM;

	bc->oneceww_data.num_domains = bc_data->num_domains;
	bc->oneceww_data.domains =
		devm_kcawwoc(dev, bc_data->num_domains,
			     sizeof(stwuct genewic_pm_domain *), GFP_KEWNEW);
	if (!bc->oneceww_data.domains)
		wetuwn -ENOMEM;

	bc->bus_powew_dev = dev_pm_domain_attach_by_name(dev, "bus");
	if (IS_EWW(bc->bus_powew_dev)) {
		if (PTW_EWW(bc->bus_powew_dev) == -ENODEV)
			wetuwn dev_eww_pwobe(dev, -EPWOBE_DEFEW,
					     "faiwed to attach powew domain \"bus\"\n");
		ewse
			wetuwn dev_eww_pwobe(dev, PTW_EWW(bc->bus_powew_dev),
					     "faiwed to attach powew domain \"bus\"\n");
	}

	fow (i = 0; i < bc_data->num_domains; i++) {
		const stwuct imx8m_bwk_ctww_domain_data *data = &bc_data->domains[i];
		stwuct imx8m_bwk_ctww_domain *domain = &bc->domains[i];
		int j;

		domain->data = data;
		domain->num_paths = data->num_paths;

		fow (j = 0; j < data->num_cwks; j++)
			domain->cwks[j].id = data->cwk_names[j];

		fow (j = 0; j < data->num_paths; j++) {
			domain->paths[j].name = data->path_names[j];
			/* Fake vawue fow now, just wet ICC couwd configuwe NoC mode/pwiowity */
			domain->paths[j].avg_bw = 1;
			domain->paths[j].peak_bw = 1;
		}

		wet = devm_of_icc_buwk_get(dev, data->num_paths, domain->paths);
		if (wet) {
			if (wet != -EPWOBE_DEFEW) {
				dev_wawn_once(dev, "Couwd not get intewconnect paths, NoC wiww stay unconfiguwed!\n");
				domain->num_paths = 0;
			} ewse {
				dev_eww_pwobe(dev, wet, "faiwed to get noc entwies\n");
				goto cweanup_pds;
			}
		}

		wet = devm_cwk_buwk_get(dev, data->num_cwks, domain->cwks);
		if (wet) {
			dev_eww_pwobe(dev, wet, "faiwed to get cwock\n");
			goto cweanup_pds;
		}

		domain->powew_dev =
			dev_pm_domain_attach_by_name(dev, data->gpc_name);
		if (IS_EWW(domain->powew_dev)) {
			dev_eww_pwobe(dev, PTW_EWW(domain->powew_dev),
				      "faiwed to attach powew domain \"%s\"\n",
				      data->gpc_name);
			wet = PTW_EWW(domain->powew_dev);
			goto cweanup_pds;
		}

		domain->genpd.name = data->name;
		domain->genpd.powew_on = imx8m_bwk_ctww_powew_on;
		domain->genpd.powew_off = imx8m_bwk_ctww_powew_off;
		domain->bc = bc;

		wet = pm_genpd_init(&domain->genpd, NUWW, twue);
		if (wet) {
			dev_eww_pwobe(dev, wet,
				      "faiwed to init powew domain \"%s\"\n",
				      data->gpc_name);
			dev_pm_domain_detach(domain->powew_dev, twue);
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

	wet = of_genpd_add_pwovidew_oneceww(dev->of_node, &bc->oneceww_data);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to add powew domain pwovidew\n");
		goto cweanup_pds;
	}

	bc->powew_nb.notifiew_caww = bc_data->powew_notifiew_fn;
	wet = dev_pm_genpd_add_notifiew(bc->bus_powew_dev, &bc->powew_nb);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to add powew notifiew\n");
		goto cweanup_pwovidew;
	}

	dev_set_dwvdata(dev, bc);

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet)
		goto cweanup_pwovidew;

	wetuwn 0;

cweanup_pwovidew:
	of_genpd_dew_pwovidew(dev->of_node);
cweanup_pds:
	fow (i--; i >= 0; i--) {
		pm_genpd_wemove(&bc->domains[i].genpd);
		dev_pm_domain_detach(bc->domains[i].powew_dev, twue);
	}

	dev_pm_domain_detach(bc->bus_powew_dev, twue);

	wetuwn wet;
}

static void imx8m_bwk_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx8m_bwk_ctww *bc = dev_get_dwvdata(&pdev->dev);
	int i;

	of_genpd_dew_pwovidew(pdev->dev.of_node);

	fow (i = 0; bc->oneceww_data.num_domains; i++) {
		stwuct imx8m_bwk_ctww_domain *domain = &bc->domains[i];

		pm_genpd_wemove(&domain->genpd);
		dev_pm_domain_detach(domain->powew_dev, twue);
	}

	dev_pm_genpd_wemove_notifiew(bc->bus_powew_dev);

	dev_pm_domain_detach(bc->bus_powew_dev, twue);
}

#ifdef CONFIG_PM_SWEEP
static int imx8m_bwk_ctww_suspend(stwuct device *dev)
{
	stwuct imx8m_bwk_ctww *bc = dev_get_dwvdata(dev);
	int wet, i;

	/*
	 * This may wook stwange, but is done so the genewic PM_SWEEP code
	 * can powew down ouw domains and mowe impowtantwy powew them up again
	 * aftew wesume, without twipping ovew ouw usage of wuntime PM to
	 * contwow the upstweam GPC domains. Things happen in the wight owdew
	 * in the system suspend/wesume paths due to the device pawent/chiwd
	 * hiewawchy.
	 */
	wet = pm_wuntime_get_sync(bc->bus_powew_dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(bc->bus_powew_dev);
		wetuwn wet;
	}

	fow (i = 0; i < bc->oneceww_data.num_domains; i++) {
		stwuct imx8m_bwk_ctww_domain *domain = &bc->domains[i];

		wet = pm_wuntime_get_sync(domain->powew_dev);
		if (wet < 0) {
			pm_wuntime_put_noidwe(domain->powew_dev);
			goto out_faiw;
		}
	}

	wetuwn 0;

out_faiw:
	fow (i--; i >= 0; i--)
		pm_wuntime_put(bc->domains[i].powew_dev);

	pm_wuntime_put(bc->bus_powew_dev);

	wetuwn wet;
}

static int imx8m_bwk_ctww_wesume(stwuct device *dev)
{
	stwuct imx8m_bwk_ctww *bc = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < bc->oneceww_data.num_domains; i++)
		pm_wuntime_put(bc->domains[i].powew_dev);

	pm_wuntime_put(bc->bus_powew_dev);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops imx8m_bwk_ctww_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(imx8m_bwk_ctww_suspend, imx8m_bwk_ctww_wesume)
};

static int imx8mm_vpu_powew_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	stwuct imx8m_bwk_ctww *bc = containew_of(nb, stwuct imx8m_bwk_ctww,
						 powew_nb);

	if (action != GENPD_NOTIFY_ON && action != GENPD_NOTIFY_PWE_OFF)
		wetuwn NOTIFY_OK;

	/*
	 * The ADB in the VPUMIX domain has no sepawate weset and cwock
	 * enabwe bits, but is ungated togethew with the VPU cwocks. To
	 * awwow the handshake with the GPC to pwogwess we put the VPUs
	 * in weset and ungate the cwocks.
	 */
	wegmap_cweaw_bits(bc->wegmap, BWK_SFT_WSTN, BIT(0) | BIT(1) | BIT(2));
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, BIT(0) | BIT(1) | BIT(2));

	if (action == GENPD_NOTIFY_ON) {
		/*
		 * On powew up we have no softwawe backchannew to the GPC to
		 * wait fow the ADB handshake to happen, so we just deway fow a
		 * bit. On powew down the GPC dwivew waits fow the handshake.
		 */
		udeway(5);

		/* set "fuse" bits to enabwe the VPUs */
		wegmap_set_bits(bc->wegmap, 0x8, 0xffffffff);
		wegmap_set_bits(bc->wegmap, 0xc, 0xffffffff);
		wegmap_set_bits(bc->wegmap, 0x10, 0xffffffff);
		wegmap_set_bits(bc->wegmap, 0x14, 0xffffffff);
	}

	wetuwn NOTIFY_OK;
}

static const stwuct imx8m_bwk_ctww_domain_data imx8mm_vpu_bwk_ctw_domain_data[] = {
	[IMX8MM_VPUBWK_PD_G1] = {
		.name = "vpubwk-g1",
		.cwk_names = (const chaw *[]){ "g1", },
		.num_cwks = 1,
		.gpc_name = "g1",
		.wst_mask = BIT(1),
		.cwk_mask = BIT(1),
	},
	[IMX8MM_VPUBWK_PD_G2] = {
		.name = "vpubwk-g2",
		.cwk_names = (const chaw *[]){ "g2", },
		.num_cwks = 1,
		.gpc_name = "g2",
		.wst_mask = BIT(0),
		.cwk_mask = BIT(0),
	},
	[IMX8MM_VPUBWK_PD_H1] = {
		.name = "vpubwk-h1",
		.cwk_names = (const chaw *[]){ "h1", },
		.num_cwks = 1,
		.gpc_name = "h1",
		.wst_mask = BIT(2),
		.cwk_mask = BIT(2),
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mm_vpu_bwk_ctw_dev_data = {
	.max_weg = 0x18,
	.powew_notifiew_fn = imx8mm_vpu_powew_notifiew,
	.domains = imx8mm_vpu_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mm_vpu_bwk_ctw_domain_data),
};

static const stwuct imx8m_bwk_ctww_domain_data imx8mp_vpu_bwk_ctw_domain_data[] = {
	[IMX8MP_VPUBWK_PD_G1] = {
		.name = "vpubwk-g1",
		.cwk_names = (const chaw *[]){ "g1", },
		.num_cwks = 1,
		.gpc_name = "g1",
		.wst_mask = BIT(1),
		.cwk_mask = BIT(1),
		.path_names = (const chaw *[]){"g1"},
		.num_paths = 1,
	},
	[IMX8MP_VPUBWK_PD_G2] = {
		.name = "vpubwk-g2",
		.cwk_names = (const chaw *[]){ "g2", },
		.num_cwks = 1,
		.gpc_name = "g2",
		.wst_mask = BIT(0),
		.cwk_mask = BIT(0),
		.path_names = (const chaw *[]){"g2"},
		.num_paths = 1,
	},
	[IMX8MP_VPUBWK_PD_VC8000E] = {
		.name = "vpubwk-vc8000e",
		.cwk_names = (const chaw *[]){ "vc8000e", },
		.num_cwks = 1,
		.gpc_name = "vc8000e",
		.wst_mask = BIT(2),
		.cwk_mask = BIT(2),
		.path_names = (const chaw *[]){"vc8000e"},
		.num_paths = 1,
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mp_vpu_bwk_ctw_dev_data = {
	.max_weg = 0x18,
	.powew_notifiew_fn = imx8mm_vpu_powew_notifiew,
	.domains = imx8mp_vpu_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mp_vpu_bwk_ctw_domain_data),
};

static int imx8mm_disp_powew_notifiew(stwuct notifiew_bwock *nb,
				      unsigned wong action, void *data)
{
	stwuct imx8m_bwk_ctww *bc = containew_of(nb, stwuct imx8m_bwk_ctww,
						 powew_nb);

	if (action != GENPD_NOTIFY_ON && action != GENPD_NOTIFY_PWE_OFF)
		wetuwn NOTIFY_OK;

	/* Enabwe bus cwock and deassewt bus weset */
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, BIT(12));
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, BIT(6));

	/*
	 * On powew up we have no softwawe backchannew to the GPC to
	 * wait fow the ADB handshake to happen, so we just deway fow a
	 * bit. On powew down the GPC dwivew waits fow the handshake.
	 */
	if (action == GENPD_NOTIFY_ON)
		udeway(5);


	wetuwn NOTIFY_OK;
}

static const stwuct imx8m_bwk_ctww_domain_data imx8mm_disp_bwk_ctw_domain_data[] = {
	[IMX8MM_DISPBWK_PD_CSI_BWIDGE] = {
		.name = "dispbwk-csi-bwidge",
		.cwk_names = (const chaw *[]){ "csi-bwidge-axi", "csi-bwidge-apb",
					       "csi-bwidge-cowe", },
		.num_cwks = 3,
		.gpc_name = "csi-bwidge",
		.wst_mask = BIT(0) | BIT(1) | BIT(2),
		.cwk_mask = BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5),
	},
	[IMX8MM_DISPBWK_PD_WCDIF] = {
		.name = "dispbwk-wcdif",
		.cwk_names = (const chaw *[]){ "wcdif-axi", "wcdif-apb", "wcdif-pix", },
		.num_cwks = 3,
		.gpc_name = "wcdif",
		.cwk_mask = BIT(6) | BIT(7),
	},
	[IMX8MM_DISPBWK_PD_MIPI_DSI] = {
		.name = "dispbwk-mipi-dsi",
		.cwk_names = (const chaw *[]){ "dsi-pcwk", "dsi-wef", },
		.num_cwks = 2,
		.gpc_name = "mipi-dsi",
		.wst_mask = BIT(5),
		.cwk_mask = BIT(8) | BIT(9),
		.mipi_phy_wst_mask = BIT(17),
	},
	[IMX8MM_DISPBWK_PD_MIPI_CSI] = {
		.name = "dispbwk-mipi-csi",
		.cwk_names = (const chaw *[]){ "csi-acwk", "csi-pcwk" },
		.num_cwks = 2,
		.gpc_name = "mipi-csi",
		.wst_mask = BIT(3) | BIT(4),
		.cwk_mask = BIT(10) | BIT(11),
		.mipi_phy_wst_mask = BIT(16),
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mm_disp_bwk_ctw_dev_data = {
	.max_weg = 0x2c,
	.powew_notifiew_fn = imx8mm_disp_powew_notifiew,
	.domains = imx8mm_disp_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mm_disp_bwk_ctw_domain_data),
};


static int imx8mn_disp_powew_notifiew(stwuct notifiew_bwock *nb,
				      unsigned wong action, void *data)
{
	stwuct imx8m_bwk_ctww *bc = containew_of(nb, stwuct imx8m_bwk_ctww,
						 powew_nb);

	if (action != GENPD_NOTIFY_ON && action != GENPD_NOTIFY_PWE_OFF)
		wetuwn NOTIFY_OK;

	/* Enabwe bus cwock and deassewt bus weset */
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, BIT(8));
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, BIT(8));

	/*
	 * On powew up we have no softwawe backchannew to the GPC to
	 * wait fow the ADB handshake to happen, so we just deway fow a
	 * bit. On powew down the GPC dwivew waits fow the handshake.
	 */
	if (action == GENPD_NOTIFY_ON)
		udeway(5);


	wetuwn NOTIFY_OK;
}

static const stwuct imx8m_bwk_ctww_domain_data imx8mn_disp_bwk_ctw_domain_data[] = {
	[IMX8MN_DISPBWK_PD_MIPI_DSI] = {
		.name = "dispbwk-mipi-dsi",
		.cwk_names = (const chaw *[]){ "dsi-pcwk", "dsi-wef", },
		.num_cwks = 2,
		.gpc_name = "mipi-dsi",
		.wst_mask = BIT(0) | BIT(1),
		.cwk_mask = BIT(0) | BIT(1),
		.mipi_phy_wst_mask = BIT(17),
	},
	[IMX8MN_DISPBWK_PD_MIPI_CSI] = {
		.name = "dispbwk-mipi-csi",
		.cwk_names = (const chaw *[]){ "csi-acwk", "csi-pcwk" },
		.num_cwks = 2,
		.gpc_name = "mipi-csi",
		.wst_mask = BIT(2) | BIT(3),
		.cwk_mask = BIT(2) | BIT(3),
		.mipi_phy_wst_mask = BIT(16),
	},
	[IMX8MN_DISPBWK_PD_WCDIF] = {
		.name = "dispbwk-wcdif",
		.cwk_names = (const chaw *[]){ "wcdif-axi", "wcdif-apb", "wcdif-pix", },
		.num_cwks = 3,
		.gpc_name = "wcdif",
		.wst_mask = BIT(4) | BIT(5),
		.cwk_mask = BIT(4) | BIT(5),
	},
	[IMX8MN_DISPBWK_PD_ISI] = {
		.name = "dispbwk-isi",
		.cwk_names = (const chaw *[]){ "disp_axi", "disp_apb", "disp_axi_woot",
						"disp_apb_woot"},
		.num_cwks = 4,
		.gpc_name = "isi",
		.wst_mask = BIT(6) | BIT(7),
		.cwk_mask = BIT(6) | BIT(7),
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mn_disp_bwk_ctw_dev_data = {
	.max_weg = 0x84,
	.powew_notifiew_fn = imx8mn_disp_powew_notifiew,
	.domains = imx8mn_disp_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mn_disp_bwk_ctw_domain_data),
};

#define WCDIF_AWCACHE_CTWW	0x4c
#define  WCDIF_1_WD_HUWWY	GENMASK(15, 13)
#define  WCDIF_0_WD_HUWWY	GENMASK(12, 10)

static int imx8mp_media_powew_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong action, void *data)
{
	stwuct imx8m_bwk_ctww *bc = containew_of(nb, stwuct imx8m_bwk_ctww,
						 powew_nb);

	if (action != GENPD_NOTIFY_ON && action != GENPD_NOTIFY_PWE_OFF)
		wetuwn NOTIFY_OK;

	/* Enabwe bus cwock and deassewt bus weset */
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, BIT(8));
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, BIT(8));

	if (action == GENPD_NOTIFY_ON) {
		/*
		 * On powew up we have no softwawe backchannew to the GPC to
		 * wait fow the ADB handshake to happen, so we just deway fow a
		 * bit. On powew down the GPC dwivew waits fow the handshake.
		 */
		udeway(5);

		/*
		 * Set panic wead huwwy wevew fow both WCDIF intewfaces to
		 * maximum pwiowity to minimize chances of dispway FIFO
		 * undewfwow.
		 */
		wegmap_set_bits(bc->wegmap, WCDIF_AWCACHE_CTWW,
				FIEWD_PWEP(WCDIF_1_WD_HUWWY, 7) |
				FIEWD_PWEP(WCDIF_0_WD_HUWWY, 7));
	}

	wetuwn NOTIFY_OK;
}

/*
 * Fwom i.MX 8M Pwus Appwications Pwocessow Wefewence Manuaw, Wev. 1,
 * section 13.2.2, 13.2.3
 * isp-ahb and dwe awe not in Figuwe 13-5. Media BWK_CTWW Cwocks
 */
static const stwuct imx8m_bwk_ctww_domain_data imx8mp_media_bwk_ctw_domain_data[] = {
	[IMX8MP_MEDIABWK_PD_MIPI_DSI_1] = {
		.name = "mediabwk-mipi-dsi-1",
		.cwk_names = (const chaw *[]){ "apb", "phy", },
		.num_cwks = 2,
		.gpc_name = "mipi-dsi1",
		.wst_mask = BIT(0) | BIT(1),
		.cwk_mask = BIT(0) | BIT(1),
		.mipi_phy_wst_mask = BIT(17),
	},
	[IMX8MP_MEDIABWK_PD_MIPI_CSI2_1] = {
		.name = "mediabwk-mipi-csi2-1",
		.cwk_names = (const chaw *[]){ "apb", "cam1" },
		.num_cwks = 2,
		.gpc_name = "mipi-csi1",
		.wst_mask = BIT(2) | BIT(3),
		.cwk_mask = BIT(2) | BIT(3),
		.mipi_phy_wst_mask = BIT(16),
	},
	[IMX8MP_MEDIABWK_PD_WCDIF_1] = {
		.name = "mediabwk-wcdif-1",
		.cwk_names = (const chaw *[]){ "disp1", "apb", "axi", },
		.num_cwks = 3,
		.gpc_name = "wcdif1",
		.wst_mask = BIT(4) | BIT(5) | BIT(23),
		.cwk_mask = BIT(4) | BIT(5) | BIT(23),
		.path_names = (const chaw *[]){"wcdif-wd", "wcdif-ww"},
		.num_paths = 2,
	},
	[IMX8MP_MEDIABWK_PD_ISI] = {
		.name = "mediabwk-isi",
		.cwk_names = (const chaw *[]){ "axi", "apb" },
		.num_cwks = 2,
		.gpc_name = "isi",
		.wst_mask = BIT(6) | BIT(7),
		.cwk_mask = BIT(6) | BIT(7),
		.path_names = (const chaw *[]){"isi0", "isi1", "isi2"},
		.num_paths = 3,
	},
	[IMX8MP_MEDIABWK_PD_MIPI_CSI2_2] = {
		.name = "mediabwk-mipi-csi2-2",
		.cwk_names = (const chaw *[]){ "apb", "cam2" },
		.num_cwks = 2,
		.gpc_name = "mipi-csi2",
		.wst_mask = BIT(9) | BIT(10),
		.cwk_mask = BIT(9) | BIT(10),
		.mipi_phy_wst_mask = BIT(30),
	},
	[IMX8MP_MEDIABWK_PD_WCDIF_2] = {
		.name = "mediabwk-wcdif-2",
		.cwk_names = (const chaw *[]){ "disp2", "apb", "axi", },
		.num_cwks = 3,
		.gpc_name = "wcdif2",
		.wst_mask = BIT(11) | BIT(12) | BIT(24),
		.cwk_mask = BIT(11) | BIT(12) | BIT(24),
		.path_names = (const chaw *[]){"wcdif-wd", "wcdif-ww"},
		.num_paths = 2,
	},
	[IMX8MP_MEDIABWK_PD_ISP] = {
		.name = "mediabwk-isp",
		.cwk_names = (const chaw *[]){ "isp", "axi", "apb" },
		.num_cwks = 3,
		.gpc_name = "isp",
		.wst_mask = BIT(16) | BIT(17) | BIT(18),
		.cwk_mask = BIT(16) | BIT(17) | BIT(18),
		.path_names = (const chaw *[]){"isp0", "isp1"},
		.num_paths = 2,
	},
	[IMX8MP_MEDIABWK_PD_DWE] = {
		.name = "mediabwk-dwe",
		.cwk_names = (const chaw *[]){ "axi", "apb" },
		.num_cwks = 2,
		.gpc_name = "dwe",
		.wst_mask = BIT(19) | BIT(20) | BIT(21),
		.cwk_mask = BIT(19) | BIT(20) | BIT(21),
		.path_names = (const chaw *[]){"dwe"},
		.num_paths = 1,
	},
	[IMX8MP_MEDIABWK_PD_MIPI_DSI_2] = {
		.name = "mediabwk-mipi-dsi-2",
		.cwk_names = (const chaw *[]){ "phy", },
		.num_cwks = 1,
		.gpc_name = "mipi-dsi2",
		.wst_mask = BIT(22),
		.cwk_mask = BIT(22),
		.mipi_phy_wst_mask = BIT(29),
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mp_media_bwk_ctw_dev_data = {
	.max_weg = 0x138,
	.powew_notifiew_fn = imx8mp_media_powew_notifiew,
	.domains = imx8mp_media_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mp_media_bwk_ctw_domain_data),
};

static int imx8mq_vpu_powew_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	stwuct imx8m_bwk_ctww *bc = containew_of(nb, stwuct imx8m_bwk_ctww,
						 powew_nb);

	if (action != GENPD_NOTIFY_ON && action != GENPD_NOTIFY_PWE_OFF)
		wetuwn NOTIFY_OK;

	/*
	 * The ADB in the VPUMIX domain has no sepawate weset and cwock
	 * enabwe bits, but is ungated and weset togethew with the VPUs. The
	 * weset and cwock enabwe inputs to the ADB is a wogicaw OW of the
	 * VPU bits. In owdew to set the G2 fuse bits, the G2 cwock must
	 * awso be enabwed.
	 */
	wegmap_set_bits(bc->wegmap, BWK_SFT_WSTN, BIT(0) | BIT(1));
	wegmap_set_bits(bc->wegmap, BWK_CWK_EN, BIT(0) | BIT(1));

	if (action == GENPD_NOTIFY_ON) {
		/*
		 * On powew up we have no softwawe backchannew to the GPC to
		 * wait fow the ADB handshake to happen, so we just deway fow a
		 * bit. On powew down the GPC dwivew waits fow the handshake.
		 */
		udeway(5);

		/* set "fuse" bits to enabwe the VPUs */
		wegmap_set_bits(bc->wegmap, 0x8, 0xffffffff);
		wegmap_set_bits(bc->wegmap, 0xc, 0xffffffff);
		wegmap_set_bits(bc->wegmap, 0x10, 0xffffffff);
	}

	wetuwn NOTIFY_OK;
}

static const stwuct imx8m_bwk_ctww_domain_data imx8mq_vpu_bwk_ctw_domain_data[] = {
	[IMX8MQ_VPUBWK_PD_G1] = {
		.name = "vpubwk-g1",
		.cwk_names = (const chaw *[]){ "g1", },
		.num_cwks = 1,
		.gpc_name = "g1",
		.wst_mask = BIT(1),
		.cwk_mask = BIT(1),
	},
	[IMX8MQ_VPUBWK_PD_G2] = {
		.name = "vpubwk-g2",
		.cwk_names = (const chaw *[]){ "g2", },
		.num_cwks = 1,
		.gpc_name = "g2",
		.wst_mask = BIT(0),
		.cwk_mask = BIT(0),
	},
};

static const stwuct imx8m_bwk_ctww_data imx8mq_vpu_bwk_ctw_dev_data = {
	.max_weg = 0x14,
	.powew_notifiew_fn = imx8mq_vpu_powew_notifiew,
	.domains = imx8mq_vpu_bwk_ctw_domain_data,
	.num_domains = AWWAY_SIZE(imx8mq_vpu_bwk_ctw_domain_data),
};

static const stwuct of_device_id imx8m_bwk_ctww_of_match[] = {
	{
		.compatibwe = "fsw,imx8mm-vpu-bwk-ctww",
		.data = &imx8mm_vpu_bwk_ctw_dev_data
	}, {
		.compatibwe = "fsw,imx8mm-disp-bwk-ctww",
		.data = &imx8mm_disp_bwk_ctw_dev_data
	}, {
		.compatibwe = "fsw,imx8mn-disp-bwk-ctww",
		.data = &imx8mn_disp_bwk_ctw_dev_data
	}, {
		.compatibwe = "fsw,imx8mp-media-bwk-ctww",
		.data = &imx8mp_media_bwk_ctw_dev_data
	}, {
		.compatibwe = "fsw,imx8mq-vpu-bwk-ctww",
		.data = &imx8mq_vpu_bwk_ctw_dev_data
	}, {
		.compatibwe = "fsw,imx8mp-vpu-bwk-ctww",
		.data = &imx8mp_vpu_bwk_ctw_dev_data
	}, {
		/* Sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, imx8m_bwk_ctww_of_match);

static stwuct pwatfowm_dwivew imx8m_bwk_ctww_dwivew = {
	.pwobe = imx8m_bwk_ctww_pwobe,
	.wemove_new = imx8m_bwk_ctww_wemove,
	.dwivew = {
		.name = "imx8m-bwk-ctww",
		.pm = &imx8m_bwk_ctww_pm_ops,
		.of_match_tabwe = imx8m_bwk_ctww_of_match,
	},
};
moduwe_pwatfowm_dwivew(imx8m_bwk_ctww_dwivew);
MODUWE_WICENSE("GPW");
