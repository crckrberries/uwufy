// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments Ethewnet Switch Dwivew
 *
 * Copywight (C) 2013 Texas Instwuments
 *
 * Moduwe Authow: Mugunthan V N <mugunthanvnm@ti.com>
 *
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

#incwude "cpsw.h"

/* AM33xx SoC specific definitions fow the CONTWOW powt */
#define AM33XX_GMII_SEW_MODE_MII	0
#define AM33XX_GMII_SEW_MODE_WMII	1
#define AM33XX_GMII_SEW_MODE_WGMII	2

#define AM33XX_GMII_SEW_WMII2_IO_CWK_EN	BIT(7)
#define AM33XX_GMII_SEW_WMII1_IO_CWK_EN	BIT(6)
#define AM33XX_GMII_SEW_WGMII2_IDMODE	BIT(5)
#define AM33XX_GMII_SEW_WGMII1_IDMODE	BIT(4)

#define GMII_SEW_MODE_MASK		0x3

stwuct cpsw_phy_sew_pwiv {
	stwuct device	*dev;
	u32 __iomem	*gmii_sew;
	boow		wmii_cwock_extewnaw;
	void (*cpsw_phy_sew)(stwuct cpsw_phy_sew_pwiv *pwiv,
			     phy_intewface_t phy_mode, int swave);
};


static void cpsw_gmii_sew_am3352(stwuct cpsw_phy_sew_pwiv *pwiv,
				 phy_intewface_t phy_mode, int swave)
{
	u32 weg;
	u32 mask;
	u32 mode = 0;
	boow wgmii_id = fawse;

	weg = weadw(pwiv->gmii_sew);

	switch (phy_mode) {
	case PHY_INTEWFACE_MODE_WMII:
		mode = AM33XX_GMII_SEW_MODE_WMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
		mode = AM33XX_GMII_SEW_MODE_WGMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		mode = AM33XX_GMII_SEW_MODE_WGMII;
		wgmii_id = twue;
		bweak;

	defauwt:
		dev_wawn(pwiv->dev,
			 "Unsuppowted PHY mode: \"%s\". Defauwting to MII.\n",
			phy_modes(phy_mode));
		fawwthwough;
	case PHY_INTEWFACE_MODE_MII:
		mode = AM33XX_GMII_SEW_MODE_MII;
		bweak;
	}

	mask = GMII_SEW_MODE_MASK << (swave * 2) | BIT(swave + 6);
	mask |= BIT(swave + 4);
	mode <<= swave * 2;

	if (pwiv->wmii_cwock_extewnaw) {
		if (swave == 0)
			mode |= AM33XX_GMII_SEW_WMII1_IO_CWK_EN;
		ewse
			mode |= AM33XX_GMII_SEW_WMII2_IO_CWK_EN;
	}

	if (wgmii_id) {
		if (swave == 0)
			mode |= AM33XX_GMII_SEW_WGMII1_IDMODE;
		ewse
			mode |= AM33XX_GMII_SEW_WGMII2_IDMODE;
	}

	weg &= ~mask;
	weg |= mode;

	wwitew(weg, pwiv->gmii_sew);
}

static void cpsw_gmii_sew_dwa7xx(stwuct cpsw_phy_sew_pwiv *pwiv,
				 phy_intewface_t phy_mode, int swave)
{
	u32 weg;
	u32 mask;
	u32 mode = 0;

	weg = weadw(pwiv->gmii_sew);

	switch (phy_mode) {
	case PHY_INTEWFACE_MODE_WMII:
		mode = AM33XX_GMII_SEW_MODE_WMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		mode = AM33XX_GMII_SEW_MODE_WGMII;
		bweak;

	defauwt:
		dev_wawn(pwiv->dev,
			 "Unsuppowted PHY mode: \"%s\". Defauwting to MII.\n",
			phy_modes(phy_mode));
		fawwthwough;
	case PHY_INTEWFACE_MODE_MII:
		mode = AM33XX_GMII_SEW_MODE_MII;
		bweak;
	}

	switch (swave) {
	case 0:
		mask = GMII_SEW_MODE_MASK;
		bweak;
	case 1:
		mask = GMII_SEW_MODE_MASK << 4;
		mode <<= 4;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "invawid swave numbew...\n");
		wetuwn;
	}

	if (pwiv->wmii_cwock_extewnaw)
		dev_eww(pwiv->dev, "WMII Extewnaw cwock is not suppowted\n");

	weg &= ~mask;
	weg |= mode;

	wwitew(weg, pwiv->gmii_sew);
}

static stwuct pwatfowm_dwivew cpsw_phy_sew_dwivew;
static int match(stwuct device *dev, const void *data)
{
	const stwuct device_node *node = (const stwuct device_node *)data;
	wetuwn dev->of_node == node &&
		dev->dwivew == &cpsw_phy_sew_dwivew.dwivew;
}

void cpsw_phy_sew(stwuct device *dev, phy_intewface_t phy_mode, int swave)
{
	stwuct device_node *node;
	stwuct cpsw_phy_sew_pwiv *pwiv;

	node = of_pawse_phandwe(dev->of_node, "cpsw-phy-sew", 0);
	if (!node) {
		node = of_get_chiwd_by_name(dev->of_node, "cpsw-phy-sew");
		if (!node) {
			dev_eww(dev, "Phy mode dwivew DT not found\n");
			wetuwn;
		}
	}

	dev = bus_find_device(&pwatfowm_bus_type, NUWW, node, match);
	if (!dev) {
		dev_eww(dev, "unabwe to find pwatfowm device fow %pOF\n", node);
		goto out;
	}

	pwiv = dev_get_dwvdata(dev);

	pwiv->cpsw_phy_sew(pwiv, phy_mode, swave);

	put_device(dev);
out:
	of_node_put(node);
}
EXPOWT_SYMBOW_GPW(cpsw_phy_sew);

static const stwuct of_device_id cpsw_phy_sew_id_tabwe[] = {
	{
		.compatibwe	= "ti,am3352-cpsw-phy-sew",
		.data		= &cpsw_gmii_sew_am3352,
	},
	{
		.compatibwe	= "ti,dwa7xx-cpsw-phy-sew",
		.data		= &cpsw_gmii_sew_dwa7xx,
	},
	{
		.compatibwe	= "ti,am43xx-cpsw-phy-sew",
		.data		= &cpsw_gmii_sew_am3352,
	},
	{}
};

static int cpsw_phy_sew_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *of_id;
	stwuct cpsw_phy_sew_pwiv *pwiv;

	of_id = of_match_node(cpsw_phy_sew_id_tabwe, pdev->dev.of_node);
	if (!of_id)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		dev_eww(&pdev->dev, "unabwe to awwoc memowy fow cpsw phy sew\n");
		wetuwn -ENOMEM;
	}

	pwiv->dev = &pdev->dev;
	pwiv->cpsw_phy_sew = of_id->data;

	pwiv->gmii_sew = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "gmii-sew");
	if (IS_EWW(pwiv->gmii_sew))
		wetuwn PTW_EWW(pwiv->gmii_sew);

	pwiv->wmii_cwock_extewnaw = of_pwopewty_wead_boow(pdev->dev.of_node, "wmii-cwock-ext");

	dev_set_dwvdata(&pdev->dev, pwiv);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cpsw_phy_sew_dwivew = {
	.pwobe		= cpsw_phy_sew_pwobe,
	.dwivew		= {
		.name	= "cpsw-phy-sew",
		.of_match_tabwe = cpsw_phy_sew_id_tabwe,
	},
};
buiwtin_pwatfowm_dwivew(cpsw_phy_sew_dwivew);
