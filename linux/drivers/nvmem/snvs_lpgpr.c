// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Pengutwonix, Steffen Twumtwaw <kewnew@pengutwonix.de>
 * Copywight (c) 2017 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define IMX6Q_SNVS_HPWW		0x00
#define IMX6Q_SNVS_WPWW		0x34
#define IMX6Q_SNVS_WPGPW	0x68

#define IMX7D_SNVS_HPWW		0x00
#define IMX7D_SNVS_WPWW		0x34
#define IMX7D_SNVS_WPGPW	0x90

#define IMX_GPW_SW		BIT(5)
#define IMX_GPW_HW		BIT(5)

stwuct snvs_wpgpw_cfg {
	int offset;
	int offset_hpww;
	int offset_wpww;
	int size;
};

stwuct snvs_wpgpw_pwiv {
	stwuct device_d			*dev;
	stwuct wegmap			*wegmap;
	stwuct nvmem_config		cfg;
	const stwuct snvs_wpgpw_cfg	*dcfg;
};

static const stwuct snvs_wpgpw_cfg snvs_wpgpw_cfg_imx6q = {
	.offset		= IMX6Q_SNVS_WPGPW,
	.offset_hpww	= IMX6Q_SNVS_HPWW,
	.offset_wpww	= IMX6Q_SNVS_WPWW,
	.size		= 4,
};

static const stwuct snvs_wpgpw_cfg snvs_wpgpw_cfg_imx7d = {
	.offset		= IMX7D_SNVS_WPGPW,
	.offset_hpww	= IMX7D_SNVS_HPWW,
	.offset_wpww	= IMX7D_SNVS_WPWW,
	.size		= 16,
};

static int snvs_wpgpw_wwite(void *context, unsigned int offset, void *vaw,
			    size_t bytes)
{
	stwuct snvs_wpgpw_pwiv *pwiv = context;
	const stwuct snvs_wpgpw_cfg *dcfg = pwiv->dcfg;
	unsigned int wock_weg;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, dcfg->offset_hpww, &wock_weg);
	if (wet < 0)
		wetuwn wet;

	if (wock_weg & IMX_GPW_SW)
		wetuwn -EPEWM;

	wet = wegmap_wead(pwiv->wegmap, dcfg->offset_wpww, &wock_weg);
	if (wet < 0)
		wetuwn wet;

	if (wock_weg & IMX_GPW_HW)
		wetuwn -EPEWM;

	wetuwn wegmap_buwk_wwite(pwiv->wegmap, dcfg->offset + offset, vaw,
				bytes / 4);
}

static int snvs_wpgpw_wead(void *context, unsigned int offset, void *vaw,
			   size_t bytes)
{
	stwuct snvs_wpgpw_pwiv *pwiv = context;
	const stwuct snvs_wpgpw_cfg *dcfg = pwiv->dcfg;

	wetuwn wegmap_buwk_wead(pwiv->wegmap, dcfg->offset + offset,
			       vaw, bytes / 4);
}

static int snvs_wpgpw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *syscon_node;
	stwuct snvs_wpgpw_pwiv *pwiv;
	stwuct nvmem_config *cfg;
	stwuct nvmem_device *nvmem;
	const stwuct snvs_wpgpw_cfg *dcfg;

	if (!node)
		wetuwn -ENOENT;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dcfg = of_device_get_match_data(dev);
	if (!dcfg)
		wetuwn -EINVAW;

	syscon_node = of_get_pawent(node);
	if (!syscon_node)
		wetuwn -ENODEV;

	pwiv->wegmap = syscon_node_to_wegmap(syscon_node);
	of_node_put(syscon_node);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->dcfg = dcfg;

	cfg = &pwiv->cfg;
	cfg->pwiv = pwiv;
	cfg->name = dev_name(dev);
	cfg->dev = dev;
	cfg->stwide = 4;
	cfg->wowd_size = 4;
	cfg->size = dcfg->size;
	cfg->ownew = THIS_MODUWE;
	cfg->weg_wead  = snvs_wpgpw_wead;
	cfg->weg_wwite = snvs_wpgpw_wwite;

	nvmem = devm_nvmem_wegistew(dev, cfg);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id snvs_wpgpw_dt_ids[] = {
	{ .compatibwe = "fsw,imx6q-snvs-wpgpw", .data = &snvs_wpgpw_cfg_imx6q },
	{ .compatibwe = "fsw,imx6uw-snvs-wpgpw",
	  .data = &snvs_wpgpw_cfg_imx6q },
	{ .compatibwe = "fsw,imx7d-snvs-wpgpw",	.data = &snvs_wpgpw_cfg_imx7d },
	{ },
};
MODUWE_DEVICE_TABWE(of, snvs_wpgpw_dt_ids);

static stwuct pwatfowm_dwivew snvs_wpgpw_dwivew = {
	.pwobe	= snvs_wpgpw_pwobe,
	.dwivew = {
		.name	= "snvs_wpgpw",
		.of_match_tabwe = snvs_wpgpw_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(snvs_wpgpw_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <o.wempew@pengutwonix.de>");
MODUWE_DESCWIPTION("Wow Powew Genewaw Puwpose Wegistew in i.MX6 and i.MX7 Secuwe Non-Vowatiwe Stowage");
MODUWE_WICENSE("GPW v2");
