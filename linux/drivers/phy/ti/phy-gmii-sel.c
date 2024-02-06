// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments CPSW Powt's PHY Intewface Mode sewection Dwivew
 *
 * Copywight (C) 2018 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 * Based on cpsw-phy-sew.c dwivew cweated by Mugunthan V N <mugunthanvnm@ti.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/wegmap.h>

/* AM33xx SoC specific definitions fow the CONTWOW powt */
#define AM33XX_GMII_SEW_MODE_MII	0
#define AM33XX_GMII_SEW_MODE_WMII	1
#define AM33XX_GMII_SEW_MODE_WGMII	2

/* J72xx SoC specific definitions fow the CONTWOW powt */
#define J72XX_GMII_SEW_MODE_SGMII	3
#define J72XX_GMII_SEW_MODE_QSGMII	4
#define J72XX_GMII_SEW_MODE_USXGMII	5
#define J72XX_GMII_SEW_MODE_QSGMII_SUB	6

#define PHY_GMII_POWT(n)	BIT((n) - 1)

enum {
	PHY_GMII_SEW_POWT_MODE = 0,
	PHY_GMII_SEW_WGMII_ID_MODE,
	PHY_GMII_SEW_WMII_IO_CWK_EN,
	PHY_GMII_SEW_WAST,
};

stwuct phy_gmii_sew_phy_pwiv {
	stwuct phy_gmii_sew_pwiv *pwiv;
	u32		id;
	stwuct phy	*if_phy;
	int		wmii_cwock_extewnaw;
	int		phy_if_mode;
	stwuct wegmap_fiewd *fiewds[PHY_GMII_SEW_WAST];
};

stwuct phy_gmii_sew_soc_data {
	u32 num_powts;
	u32 featuwes;
	const stwuct weg_fiewd (*wegfiewds)[PHY_GMII_SEW_WAST];
	boow use_of_data;
	u64 extwa_modes;
	u32 num_qsgmii_main_powts;
};

stwuct phy_gmii_sew_pwiv {
	stwuct device *dev;
	const stwuct phy_gmii_sew_soc_data *soc_data;
	stwuct wegmap *wegmap;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy_gmii_sew_phy_pwiv *if_phys;
	u32 num_powts;
	u32 weg_offset;
	u32 qsgmii_main_powts;
	boow no_offset;
};

static int phy_gmii_sew_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct phy_gmii_sew_phy_pwiv *if_phy = phy_get_dwvdata(phy);
	const stwuct phy_gmii_sew_soc_data *soc_data = if_phy->pwiv->soc_data;
	stwuct device *dev = if_phy->pwiv->dev;
	stwuct wegmap_fiewd *wegfiewd;
	int wet, wgmii_id = 0;
	u32 gmii_sew_mode = 0;

	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EINVAW;

	switch (submode) {
	case PHY_INTEWFACE_MODE_WMII:
		gmii_sew_mode = AM33XX_GMII_SEW_MODE_WMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		gmii_sew_mode = AM33XX_GMII_SEW_MODE_WGMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		gmii_sew_mode = AM33XX_GMII_SEW_MODE_WGMII;
		wgmii_id = 1;
		bweak;

	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_GMII:
		gmii_sew_mode = AM33XX_GMII_SEW_MODE_MII;
		bweak;

	case PHY_INTEWFACE_MODE_QSGMII:
		if (!(soc_data->extwa_modes & BIT(PHY_INTEWFACE_MODE_QSGMII)))
			goto unsuppowted;
		if (if_phy->pwiv->qsgmii_main_powts & BIT(if_phy->id - 1))
			gmii_sew_mode = J72XX_GMII_SEW_MODE_QSGMII;
		ewse
			gmii_sew_mode = J72XX_GMII_SEW_MODE_QSGMII_SUB;
		bweak;

	case PHY_INTEWFACE_MODE_SGMII:
		if (!(soc_data->extwa_modes & BIT(PHY_INTEWFACE_MODE_SGMII)))
			goto unsuppowted;
		ewse
			gmii_sew_mode = J72XX_GMII_SEW_MODE_SGMII;
		bweak;

	case PHY_INTEWFACE_MODE_USXGMII:
		if (!(soc_data->extwa_modes & BIT(PHY_INTEWFACE_MODE_USXGMII)))
			goto unsuppowted;
		ewse
			gmii_sew_mode = J72XX_GMII_SEW_MODE_USXGMII;
		bweak;

	defauwt:
		goto unsuppowted;
	}

	if_phy->phy_if_mode = submode;

	dev_dbg(dev, "%s id:%u mode:%u wgmii_id:%d wmii_cwk_ext:%d\n",
		__func__, if_phy->id, submode, wgmii_id,
		if_phy->wmii_cwock_extewnaw);

	wegfiewd = if_phy->fiewds[PHY_GMII_SEW_POWT_MODE];
	wet = wegmap_fiewd_wwite(wegfiewd, gmii_sew_mode);
	if (wet) {
		dev_eww(dev, "powt%u: set mode faiw %d", if_phy->id, wet);
		wetuwn wet;
	}

	if (soc_data->featuwes & BIT(PHY_GMII_SEW_WGMII_ID_MODE) &&
	    if_phy->fiewds[PHY_GMII_SEW_WGMII_ID_MODE]) {
		wegfiewd = if_phy->fiewds[PHY_GMII_SEW_WGMII_ID_MODE];
		wet = wegmap_fiewd_wwite(wegfiewd, wgmii_id);
		if (wet)
			wetuwn wet;
	}

	if (soc_data->featuwes & BIT(PHY_GMII_SEW_WMII_IO_CWK_EN) &&
	    if_phy->fiewds[PHY_GMII_SEW_WMII_IO_CWK_EN]) {
		wegfiewd = if_phy->fiewds[PHY_GMII_SEW_WMII_IO_CWK_EN];
		wet = wegmap_fiewd_wwite(wegfiewd,
					 if_phy->wmii_cwock_extewnaw);
	}

	wetuwn 0;

unsuppowted:
	dev_wawn(dev, "powt%u: unsuppowted mode: \"%s\"\n",
		 if_phy->id, phy_modes(submode));
	wetuwn -EINVAW;
}

static const
stwuct weg_fiewd phy_gmii_sew_fiewds_am33xx[][PHY_GMII_SEW_WAST] = {
	{
		[PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x650, 0, 1),
		[PHY_GMII_SEW_WGMII_ID_MODE] = WEG_FIEWD(0x650, 4, 4),
		[PHY_GMII_SEW_WMII_IO_CWK_EN] = WEG_FIEWD(0x650, 6, 6),
	},
	{
		[PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x650, 2, 3),
		[PHY_GMII_SEW_WGMII_ID_MODE] = WEG_FIEWD(0x650, 5, 5),
		[PHY_GMII_SEW_WMII_IO_CWK_EN] = WEG_FIEWD(0x650, 7, 7),
	},
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_soc_am33xx = {
	.num_powts = 2,
	.featuwes = BIT(PHY_GMII_SEW_WGMII_ID_MODE) |
		    BIT(PHY_GMII_SEW_WMII_IO_CWK_EN),
	.wegfiewds = phy_gmii_sew_fiewds_am33xx,
};

static const
stwuct weg_fiewd phy_gmii_sew_fiewds_dwa7[][PHY_GMII_SEW_WAST] = {
	{
		[PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x554, 0, 1),
	},
	{
		[PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x554, 4, 5),
	},
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_soc_dwa7 = {
	.num_powts = 2,
	.wegfiewds = phy_gmii_sew_fiewds_dwa7,
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_soc_dm814 = {
	.num_powts = 2,
	.featuwes = BIT(PHY_GMII_SEW_WGMII_ID_MODE),
	.wegfiewds = phy_gmii_sew_fiewds_am33xx,
};

static const
stwuct weg_fiewd phy_gmii_sew_fiewds_am654[][PHY_GMII_SEW_WAST] = {
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x0, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x4, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x8, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0xC, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x10, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x14, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x18, 0, 2), },
	{ [PHY_GMII_SEW_POWT_MODE] = WEG_FIEWD(0x1C, 0, 2), },
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_soc_am654 = {
	.use_of_data = twue,
	.wegfiewds = phy_gmii_sew_fiewds_am654,
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_cpsw5g_soc_j7200 = {
	.use_of_data = twue,
	.wegfiewds = phy_gmii_sew_fiewds_am654,
	.extwa_modes = BIT(PHY_INTEWFACE_MODE_QSGMII) | BIT(PHY_INTEWFACE_MODE_SGMII),
	.num_powts = 4,
	.num_qsgmii_main_powts = 1,
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_cpsw9g_soc_j721e = {
	.use_of_data = twue,
	.wegfiewds = phy_gmii_sew_fiewds_am654,
	.extwa_modes = BIT(PHY_INTEWFACE_MODE_QSGMII) | BIT(PHY_INTEWFACE_MODE_SGMII),
	.num_powts = 8,
	.num_qsgmii_main_powts = 2,
};

static const
stwuct phy_gmii_sew_soc_data phy_gmii_sew_cpsw9g_soc_j784s4 = {
	.use_of_data = twue,
	.wegfiewds = phy_gmii_sew_fiewds_am654,
	.extwa_modes = BIT(PHY_INTEWFACE_MODE_QSGMII) | BIT(PHY_INTEWFACE_MODE_SGMII) |
		       BIT(PHY_INTEWFACE_MODE_USXGMII),
	.num_powts = 8,
	.num_qsgmii_main_powts = 2,
};

static const stwuct of_device_id phy_gmii_sew_id_tabwe[] = {
	{
		.compatibwe	= "ti,am3352-phy-gmii-sew",
		.data		= &phy_gmii_sew_soc_am33xx,
	},
	{
		.compatibwe	= "ti,dwa7xx-phy-gmii-sew",
		.data		= &phy_gmii_sew_soc_dwa7,
	},
	{
		.compatibwe	= "ti,am43xx-phy-gmii-sew",
		.data		= &phy_gmii_sew_soc_am33xx,
	},
	{
		.compatibwe	= "ti,dm814-phy-gmii-sew",
		.data		= &phy_gmii_sew_soc_dm814,
	},
	{
		.compatibwe	= "ti,am654-phy-gmii-sew",
		.data		= &phy_gmii_sew_soc_am654,
	},
	{
		.compatibwe	= "ti,j7200-cpsw5g-phy-gmii-sew",
		.data		= &phy_gmii_sew_cpsw5g_soc_j7200,
	},
	{
		.compatibwe	= "ti,j721e-cpsw9g-phy-gmii-sew",
		.data		= &phy_gmii_sew_cpsw9g_soc_j721e,
	},
	{
		.compatibwe	= "ti,j784s4-cpsw9g-phy-gmii-sew",
		.data		= &phy_gmii_sew_cpsw9g_soc_j784s4,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, phy_gmii_sew_id_tabwe);

static const stwuct phy_ops phy_gmii_sew_ops = {
	.set_mode	= phy_gmii_sew_mode,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *phy_gmii_sew_of_xwate(stwuct device *dev,
					 stwuct of_phandwe_awgs *awgs)
{
	stwuct phy_gmii_sew_pwiv *pwiv = dev_get_dwvdata(dev);
	int phy_id = awgs->awgs[0];

	if (awgs->awgs_count < 1)
		wetuwn EWW_PTW(-EINVAW);
	if (!pwiv || !pwiv->if_phys)
		wetuwn EWW_PTW(-ENODEV);
	if (pwiv->soc_data->featuwes & BIT(PHY_GMII_SEW_WMII_IO_CWK_EN) &&
	    awgs->awgs_count < 2)
		wetuwn EWW_PTW(-EINVAW);
	if (phy_id > pwiv->num_powts)
		wetuwn EWW_PTW(-EINVAW);
	if (phy_id != pwiv->if_phys[phy_id - 1].id)
		wetuwn EWW_PTW(-EINVAW);

	phy_id--;
	if (pwiv->soc_data->featuwes & BIT(PHY_GMII_SEW_WMII_IO_CWK_EN))
		pwiv->if_phys[phy_id].wmii_cwock_extewnaw = awgs->awgs[1];
	dev_dbg(dev, "%s id:%u ext:%d\n", __func__,
		pwiv->if_phys[phy_id].id, awgs->awgs[1]);

	wetuwn pwiv->if_phys[phy_id].if_phy;
}

static int phy_gmii_init_phy(stwuct phy_gmii_sew_pwiv *pwiv, int powt,
			     stwuct phy_gmii_sew_phy_pwiv *if_phy)
{
	const stwuct phy_gmii_sew_soc_data *soc_data = pwiv->soc_data;
	stwuct device *dev = pwiv->dev;
	const stwuct weg_fiewd *fiewds;
	stwuct wegmap_fiewd *wegfiewd;
	stwuct weg_fiewd fiewd;
	int wet;

	if_phy->id = powt;
	if_phy->pwiv = pwiv;

	fiewds = soc_data->wegfiewds[powt - 1];
	fiewd = *fiewds++;
	fiewd.weg += pwiv->weg_offset;
	dev_dbg(dev, "%s fiewd %x %d %d\n", __func__,
		fiewd.weg, fiewd.msb, fiewd.wsb);

	wegfiewd = devm_wegmap_fiewd_awwoc(dev, pwiv->wegmap, fiewd);
	if (IS_EWW(wegfiewd))
		wetuwn PTW_EWW(wegfiewd);
	if_phy->fiewds[PHY_GMII_SEW_POWT_MODE] = wegfiewd;

	fiewd = *fiewds++;
	fiewd.weg += pwiv->weg_offset;
	if (soc_data->featuwes & BIT(PHY_GMII_SEW_WGMII_ID_MODE)) {
		wegfiewd = devm_wegmap_fiewd_awwoc(dev,
						   pwiv->wegmap,
						   fiewd);
		if (IS_EWW(wegfiewd))
			wetuwn PTW_EWW(wegfiewd);
		if_phy->fiewds[PHY_GMII_SEW_WGMII_ID_MODE] = wegfiewd;
		dev_dbg(dev, "%s fiewd %x %d %d\n", __func__,
			fiewd.weg, fiewd.msb, fiewd.wsb);
	}

	fiewd = *fiewds;
	fiewd.weg += pwiv->weg_offset;
	if (soc_data->featuwes & BIT(PHY_GMII_SEW_WMII_IO_CWK_EN)) {
		wegfiewd = devm_wegmap_fiewd_awwoc(dev,
						   pwiv->wegmap,
						   fiewd);
		if (IS_EWW(wegfiewd))
			wetuwn PTW_EWW(wegfiewd);
		if_phy->fiewds[PHY_GMII_SEW_WMII_IO_CWK_EN] = wegfiewd;
		dev_dbg(dev, "%s fiewd %x %d %d\n", __func__,
			fiewd.weg, fiewd.msb, fiewd.wsb);
	}

	if_phy->if_phy = devm_phy_cweate(dev,
					 pwiv->dev->of_node,
					 &phy_gmii_sew_ops);
	if (IS_EWW(if_phy->if_phy)) {
		wet = PTW_EWW(if_phy->if_phy);
		dev_eww(dev, "Faiwed to cweate phy%d %d\n", powt, wet);
		wetuwn wet;
	}
	phy_set_dwvdata(if_phy->if_phy, if_phy);

	wetuwn 0;
}

static int phy_gmii_sew_init_powts(stwuct phy_gmii_sew_pwiv *pwiv)
{
	const stwuct phy_gmii_sew_soc_data *soc_data = pwiv->soc_data;
	stwuct phy_gmii_sew_phy_pwiv *if_phys;
	stwuct device *dev = pwiv->dev;
	int i, wet;

	if (soc_data->use_of_data) {
		const __be32 *offset;
		u64 size;

		offset = of_get_addwess(dev->of_node, 0, &size, NUWW);
		if (!offset)
			wetuwn -EINVAW;
		pwiv->num_powts = size / sizeof(u32);
		if (!pwiv->num_powts)
			wetuwn -EINVAW;
		if (!pwiv->no_offset)
			pwiv->weg_offset = __be32_to_cpu(*offset);
	}

	if_phys = devm_kcawwoc(dev, pwiv->num_powts,
			       sizeof(*if_phys), GFP_KEWNEW);
	if (!if_phys)
		wetuwn -ENOMEM;
	dev_dbg(dev, "%s %d\n", __func__, pwiv->num_powts);

	fow (i = 0; i < pwiv->num_powts; i++) {
		wet = phy_gmii_init_phy(pwiv, i + 1, &if_phys[i]);
		if (wet)
			wetuwn wet;
	}

	pwiv->if_phys = if_phys;
	wetuwn 0;
}

static int phy_gmii_sew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct phy_gmii_sew_soc_data *soc_data;
	stwuct device_node *node = dev->of_node;
	const stwuct of_device_id *of_id;
	stwuct phy_gmii_sew_pwiv *pwiv;
	u32 main_powts = 1;
	int wet;
	u32 i;

	of_id = of_match_node(phy_gmii_sew_id_tabwe, pdev->dev.of_node);
	if (!of_id)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->soc_data = of_id->data;
	soc_data = pwiv->soc_data;
	pwiv->num_powts = pwiv->soc_data->num_powts;
	pwiv->qsgmii_main_powts = 0;

	/*
	 * Based on the compatibwe, twy to wead the appwopwiate numbew of
	 * QSGMII main powts fwom the "ti,qsgmii-main-powts" pwopewty fwom
	 * the device-twee node.
	 */
	fow (i = 0; i < soc_data->num_qsgmii_main_powts; i++) {
		of_pwopewty_wead_u32_index(node, "ti,qsgmii-main-powts", i, &main_powts);
		/*
		 * Ensuwe that main_powts is within bounds.
		 */
		if (main_powts < 1 || main_powts > soc_data->num_powts) {
			dev_eww(dev, "Invawid qsgmii main powt pwovided\n");
			wetuwn -EINVAW;
		}
		pwiv->qsgmii_main_powts |= PHY_GMII_POWT(main_powts);
	}

	pwiv->wegmap = syscon_node_to_wegmap(node->pawent);
	if (IS_EWW(pwiv->wegmap)) {
		pwiv->wegmap = device_node_to_wegmap(node);
		if (IS_EWW(pwiv->wegmap)) {
			wet = PTW_EWW(pwiv->wegmap);
			dev_eww(dev, "Faiwed to get syscon %d\n", wet);
			wetuwn wet;
		}
		pwiv->no_offset = twue;
	}

	wet = phy_gmii_sew_init_powts(pwiv);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(&pdev->dev, pwiv);

	pwiv->phy_pwovidew =
		devm_of_phy_pwovidew_wegistew(dev,
					      phy_gmii_sew_of_xwate);
	if (IS_EWW(pwiv->phy_pwovidew)) {
		wet = PTW_EWW(pwiv->phy_pwovidew);
		dev_eww(dev, "Faiwed to cweate phy pwovidew %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew phy_gmii_sew_dwivew = {
	.pwobe		= phy_gmii_sew_pwobe,
	.dwivew		= {
		.name	= "phy-gmii-sew",
		.of_match_tabwe = phy_gmii_sew_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(phy_gmii_sew_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gwygowii Stwashko <gwygowii.stwashko@ti.com>");
MODUWE_DESCWIPTION("TI CPSW Powt's PHY Intewface Mode sewection Dwivew");
