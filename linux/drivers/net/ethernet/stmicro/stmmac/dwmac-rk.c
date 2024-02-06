// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/**
 * DOC: dwmac-wk.c - Wockchip WK3288 DWMAC specific gwue wayew
 *
 * Copywight (C) 2014 Chen-Zhi (Wogew Chen)
 *
 * Chen-Zhi (Wogew Chen)  <wogew.chen@wock-chips.com>
 */

#incwude <winux/stmmac.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/phy.h>
#incwude <winux/of_net.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm_wuntime.h>

#incwude "stmmac_pwatfowm.h"

stwuct wk_pwiv_data;
stwuct wk_gmac_ops {
	void (*set_to_wgmii)(stwuct wk_pwiv_data *bsp_pwiv,
			     int tx_deway, int wx_deway);
	void (*set_to_wmii)(stwuct wk_pwiv_data *bsp_pwiv);
	void (*set_wgmii_speed)(stwuct wk_pwiv_data *bsp_pwiv, int speed);
	void (*set_wmii_speed)(stwuct wk_pwiv_data *bsp_pwiv, int speed);
	void (*set_cwock_sewection)(stwuct wk_pwiv_data *bsp_pwiv, boow input,
				    boow enabwe);
	void (*integwated_phy_powewup)(stwuct wk_pwiv_data *bsp_pwiv);
	boow wegs_vawid;
	u32 wegs[];
};

static const chaw * const wk_cwocks[] = {
	"acwk_mac", "pcwk_mac", "mac_cwk_tx", "cwk_mac_speed",
};

static const chaw * const wk_wmii_cwocks[] = {
	"mac_cwk_wx", "cwk_mac_wef", "cwk_mac_wefout",
};

enum wk_cwocks_index {
	WK_ACWK_MAC = 0,
	WK_PCWK_MAC,
	WK_MAC_CWK_TX,
	WK_CWK_MAC_SPEED,
	WK_MAC_CWK_WX,
	WK_CWK_MAC_WEF,
	WK_CWK_MAC_WEFOUT,
};

stwuct wk_pwiv_data {
	stwuct pwatfowm_device *pdev;
	phy_intewface_t phy_iface;
	int id;
	stwuct weguwatow *weguwatow;
	boow suspended;
	const stwuct wk_gmac_ops *ops;

	boow cwk_enabwed;
	boow cwock_input;
	boow integwated_phy;

	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	stwuct cwk *cwk_mac;
	stwuct cwk *cwk_phy;

	stwuct weset_contwow *phy_weset;

	int tx_deway;
	int wx_deway;

	stwuct wegmap *gwf;
	stwuct wegmap *php_gwf;
};

#define HIWOWD_UPDATE(vaw, mask, shift) \
		((vaw) << (shift) | (mask) << ((shift) + 16))

#define GWF_BIT(nw)	(BIT(nw) | BIT(nw+16))
#define GWF_CWW_BIT(nw)	(BIT(nw+16))

#define DEWAY_ENABWE(soc, tx, wx) \
	(((tx) ? soc##_GMAC_TXCWK_DWY_ENABWE : soc##_GMAC_TXCWK_DWY_DISABWE) | \
	 ((wx) ? soc##_GMAC_WXCWK_DWY_ENABWE : soc##_GMAC_WXCWK_DWY_DISABWE))

#define PX30_GWF_GMAC_CON1		0x0904

/* PX30_GWF_GMAC_CON1 */
#define PX30_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | \
					 GWF_BIT(6))
#define PX30_GMAC_SPEED_10M		GWF_CWW_BIT(2)
#define PX30_GMAC_SPEED_100M		GWF_BIT(2)

static void px30_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, PX30_GWF_GMAC_CON1,
		     PX30_GMAC_PHY_INTF_SEW_WMII);
}

static void px30_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct cwk *cwk_mac_speed = bsp_pwiv->cwks[WK_CWK_MAC_SPEED].cwk;
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	int wet;

	if (!cwk_mac_speed) {
		dev_eww(dev, "%s: Missing cwk_mac_speed cwock\n", __func__);
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, PX30_GWF_GMAC_CON1,
			     PX30_GMAC_SPEED_10M);

		wet = cwk_set_wate(cwk_mac_speed, 2500000);
		if (wet)
			dev_eww(dev, "%s: set cwk_mac_speed wate 2500000 faiwed: %d\n",
				__func__, wet);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, PX30_GWF_GMAC_CON1,
			     PX30_GMAC_SPEED_100M);

		wet = cwk_set_wate(cwk_mac_speed, 25000000);
		if (wet)
			dev_eww(dev, "%s: set cwk_mac_speed wate 25000000 faiwed: %d\n",
				__func__, wet);

	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops px30_ops = {
	.set_to_wmii = px30_set_to_wmii,
	.set_wmii_speed = px30_set_wmii_speed,
};

#define WK3128_GWF_MAC_CON0	0x0168
#define WK3128_GWF_MAC_CON1	0x016c

/* WK3128_GWF_MAC_CON0 */
#define WK3128_GMAC_TXCWK_DWY_ENABWE   GWF_BIT(14)
#define WK3128_GMAC_TXCWK_DWY_DISABWE  GWF_CWW_BIT(14)
#define WK3128_GMAC_WXCWK_DWY_ENABWE   GWF_BIT(15)
#define WK3128_GMAC_WXCWK_DWY_DISABWE  GWF_CWW_BIT(15)
#define WK3128_GMAC_CWK_WX_DW_CFG(vaw) HIWOWD_UPDATE(vaw, 0x7F, 7)
#define WK3128_GMAC_CWK_TX_DW_CFG(vaw) HIWOWD_UPDATE(vaw, 0x7F, 0)

/* WK3128_GWF_MAC_CON1 */
#define WK3128_GMAC_PHY_INTF_SEW_WGMII	\
		(GWF_BIT(6) | GWF_CWW_BIT(7) | GWF_CWW_BIT(8))
#define WK3128_GMAC_PHY_INTF_SEW_WMII	\
		(GWF_CWW_BIT(6) | GWF_CWW_BIT(7) | GWF_BIT(8))
#define WK3128_GMAC_FWOW_CTWW          GWF_BIT(9)
#define WK3128_GMAC_FWOW_CTWW_CWW      GWF_CWW_BIT(9)
#define WK3128_GMAC_SPEED_10M          GWF_CWW_BIT(10)
#define WK3128_GMAC_SPEED_100M         GWF_BIT(10)
#define WK3128_GMAC_WMII_CWK_25M       GWF_BIT(11)
#define WK3128_GMAC_WMII_CWK_2_5M      GWF_CWW_BIT(11)
#define WK3128_GMAC_CWK_125M           (GWF_CWW_BIT(12) | GWF_CWW_BIT(13))
#define WK3128_GMAC_CWK_25M            (GWF_BIT(12) | GWF_BIT(13))
#define WK3128_GMAC_CWK_2_5M           (GWF_CWW_BIT(12) | GWF_BIT(13))
#define WK3128_GMAC_WMII_MODE          GWF_BIT(14)
#define WK3128_GMAC_WMII_MODE_CWW      GWF_CWW_BIT(14)

static void wk3128_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
		     WK3128_GMAC_PHY_INTF_SEW_WGMII |
		     WK3128_GMAC_WMII_MODE_CWW);
	wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON0,
		     DEWAY_ENABWE(WK3128, tx_deway, wx_deway) |
		     WK3128_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3128_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3128_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
		     WK3128_GMAC_PHY_INTF_SEW_WMII | WK3128_GMAC_WMII_MODE);
}

static void wk3128_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
			     WK3128_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
			     WK3128_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
			     WK3128_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3128_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
			     WK3128_GMAC_WMII_CWK_2_5M |
			     WK3128_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3128_GWF_MAC_CON1,
			     WK3128_GMAC_WMII_CWK_25M |
			     WK3128_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3128_ops = {
	.set_to_wgmii = wk3128_set_to_wgmii,
	.set_to_wmii = wk3128_set_to_wmii,
	.set_wgmii_speed = wk3128_set_wgmii_speed,
	.set_wmii_speed = wk3128_set_wmii_speed,
};

#define WK3228_GWF_MAC_CON0	0x0900
#define WK3228_GWF_MAC_CON1	0x0904

#define WK3228_GWF_CON_MUX	0x50

/* WK3228_GWF_MAC_CON0 */
#define WK3228_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 7)
#define WK3228_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

/* WK3228_GWF_MAC_CON1 */
#define WK3228_GMAC_PHY_INTF_SEW_WGMII	\
		(GWF_BIT(4) | GWF_CWW_BIT(5) | GWF_CWW_BIT(6))
#define WK3228_GMAC_PHY_INTF_SEW_WMII	\
		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | GWF_BIT(6))
#define WK3228_GMAC_FWOW_CTWW		GWF_BIT(3)
#define WK3228_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(3)
#define WK3228_GMAC_SPEED_10M		GWF_CWW_BIT(2)
#define WK3228_GMAC_SPEED_100M		GWF_BIT(2)
#define WK3228_GMAC_WMII_CWK_25M	GWF_BIT(7)
#define WK3228_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(7)
#define WK3228_GMAC_CWK_125M		(GWF_CWW_BIT(8) | GWF_CWW_BIT(9))
#define WK3228_GMAC_CWK_25M		(GWF_BIT(8) | GWF_BIT(9))
#define WK3228_GMAC_CWK_2_5M		(GWF_CWW_BIT(8) | GWF_BIT(9))
#define WK3228_GMAC_WMII_MODE		GWF_BIT(10)
#define WK3228_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(10)
#define WK3228_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(0)
#define WK3228_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(0)
#define WK3228_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(1)
#define WK3228_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(1)

/* WK3228_GWF_COM_MUX */
#define WK3228_GWF_CON_MUX_GMAC_INTEGWATED_PHY	GWF_BIT(15)

static void wk3228_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
		     WK3228_GMAC_PHY_INTF_SEW_WGMII |
		     WK3228_GMAC_WMII_MODE_CWW |
		     DEWAY_ENABWE(WK3228, tx_deway, wx_deway));

	wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON0,
		     WK3228_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3228_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3228_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
		     WK3228_GMAC_PHY_INTF_SEW_WMII |
		     WK3228_GMAC_WMII_MODE);

	/* set MAC to WMII mode */
	wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1, GWF_BIT(11));
}

static void wk3228_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
			     WK3228_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
			     WK3228_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
			     WK3228_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3228_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
			     WK3228_GMAC_WMII_CWK_2_5M |
			     WK3228_GMAC_SPEED_10M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3228_GWF_MAC_CON1,
			     WK3228_GMAC_WMII_CWK_25M |
			     WK3228_GMAC_SPEED_100M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
}

static void wk3228_integwated_phy_powewup(stwuct wk_pwiv_data *pwiv)
{
	wegmap_wwite(pwiv->gwf, WK3228_GWF_CON_MUX,
		     WK3228_GWF_CON_MUX_GMAC_INTEGWATED_PHY);
}

static const stwuct wk_gmac_ops wk3228_ops = {
	.set_to_wgmii = wk3228_set_to_wgmii,
	.set_to_wmii = wk3228_set_to_wmii,
	.set_wgmii_speed = wk3228_set_wgmii_speed,
	.set_wmii_speed = wk3228_set_wmii_speed,
	.integwated_phy_powewup =  wk3228_integwated_phy_powewup,
};

#define WK3288_GWF_SOC_CON1	0x0248
#define WK3288_GWF_SOC_CON3	0x0250

/*WK3288_GWF_SOC_CON1*/
#define WK3288_GMAC_PHY_INTF_SEW_WGMII	(GWF_BIT(6) | GWF_CWW_BIT(7) | \
					 GWF_CWW_BIT(8))
#define WK3288_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(6) | GWF_CWW_BIT(7) | \
					 GWF_BIT(8))
#define WK3288_GMAC_FWOW_CTWW		GWF_BIT(9)
#define WK3288_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(9)
#define WK3288_GMAC_SPEED_10M		GWF_CWW_BIT(10)
#define WK3288_GMAC_SPEED_100M		GWF_BIT(10)
#define WK3288_GMAC_WMII_CWK_25M	GWF_BIT(11)
#define WK3288_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(11)
#define WK3288_GMAC_CWK_125M		(GWF_CWW_BIT(12) | GWF_CWW_BIT(13))
#define WK3288_GMAC_CWK_25M		(GWF_BIT(12) | GWF_BIT(13))
#define WK3288_GMAC_CWK_2_5M		(GWF_CWW_BIT(12) | GWF_BIT(13))
#define WK3288_GMAC_WMII_MODE		GWF_BIT(14)
#define WK3288_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(14)

/*WK3288_GWF_SOC_CON3*/
#define WK3288_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(14)
#define WK3288_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(14)
#define WK3288_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(15)
#define WK3288_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(15)
#define WK3288_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 7)
#define WK3288_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wk3288_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
		     WK3288_GMAC_PHY_INTF_SEW_WGMII |
		     WK3288_GMAC_WMII_MODE_CWW);
	wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON3,
		     DEWAY_ENABWE(WK3288, tx_deway, wx_deway) |
		     WK3288_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3288_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3288_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
		     WK3288_GMAC_PHY_INTF_SEW_WMII | WK3288_GMAC_WMII_MODE);
}

static void wk3288_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
			     WK3288_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
			     WK3288_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
			     WK3288_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3288_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
			     WK3288_GMAC_WMII_CWK_2_5M |
			     WK3288_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3288_GWF_SOC_CON1,
			     WK3288_GMAC_WMII_CWK_25M |
			     WK3288_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3288_ops = {
	.set_to_wgmii = wk3288_set_to_wgmii,
	.set_to_wmii = wk3288_set_to_wmii,
	.set_wgmii_speed = wk3288_set_wgmii_speed,
	.set_wmii_speed = wk3288_set_wmii_speed,
};

#define WK3308_GWF_MAC_CON0		0x04a0

/* WK3308_GWF_MAC_CON0 */
#define WK3308_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(2) | GWF_CWW_BIT(3) | \
					GWF_BIT(4))
#define WK3308_GMAC_FWOW_CTWW		GWF_BIT(3)
#define WK3308_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(3)
#define WK3308_GMAC_SPEED_10M		GWF_CWW_BIT(0)
#define WK3308_GMAC_SPEED_100M		GWF_BIT(0)

static void wk3308_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3308_GWF_MAC_CON0,
		     WK3308_GMAC_PHY_INTF_SEW_WMII);
}

static void wk3308_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3308_GWF_MAC_CON0,
			     WK3308_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3308_GWF_MAC_CON0,
			     WK3308_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3308_ops = {
	.set_to_wmii = wk3308_set_to_wmii,
	.set_wmii_speed = wk3308_set_wmii_speed,
};

#define WK3328_GWF_MAC_CON0	0x0900
#define WK3328_GWF_MAC_CON1	0x0904
#define WK3328_GWF_MAC_CON2	0x0908
#define WK3328_GWF_MACPHY_CON1	0xb04

/* WK3328_GWF_MAC_CON0 */
#define WK3328_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 7)
#define WK3328_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

/* WK3328_GWF_MAC_CON1 */
#define WK3328_GMAC_PHY_INTF_SEW_WGMII	\
		(GWF_BIT(4) | GWF_CWW_BIT(5) | GWF_CWW_BIT(6))
#define WK3328_GMAC_PHY_INTF_SEW_WMII	\
		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | GWF_BIT(6))
#define WK3328_GMAC_FWOW_CTWW		GWF_BIT(3)
#define WK3328_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(3)
#define WK3328_GMAC_SPEED_10M		GWF_CWW_BIT(2)
#define WK3328_GMAC_SPEED_100M		GWF_BIT(2)
#define WK3328_GMAC_WMII_CWK_25M	GWF_BIT(7)
#define WK3328_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(7)
#define WK3328_GMAC_CWK_125M		(GWF_CWW_BIT(11) | GWF_CWW_BIT(12))
#define WK3328_GMAC_CWK_25M		(GWF_BIT(11) | GWF_BIT(12))
#define WK3328_GMAC_CWK_2_5M		(GWF_CWW_BIT(11) | GWF_BIT(12))
#define WK3328_GMAC_WMII_MODE		GWF_BIT(9)
#define WK3328_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(9)
#define WK3328_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(0)
#define WK3328_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(0)
#define WK3328_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(1)
#define WK3328_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(0)

/* WK3328_GWF_MACPHY_CON1 */
#define WK3328_MACPHY_WMII_MODE		GWF_BIT(9)

static void wk3328_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3328_GWF_MAC_CON1,
		     WK3328_GMAC_PHY_INTF_SEW_WGMII |
		     WK3328_GMAC_WMII_MODE_CWW |
		     WK3328_GMAC_WXCWK_DWY_ENABWE |
		     WK3328_GMAC_TXCWK_DWY_ENABWE);

	wegmap_wwite(bsp_pwiv->gwf, WK3328_GWF_MAC_CON0,
		     WK3328_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3328_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3328_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned int weg;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	weg = bsp_pwiv->integwated_phy ? WK3328_GWF_MAC_CON2 :
		  WK3328_GWF_MAC_CON1;

	wegmap_wwite(bsp_pwiv->gwf, weg,
		     WK3328_GMAC_PHY_INTF_SEW_WMII |
		     WK3328_GMAC_WMII_MODE);
}

static void wk3328_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3328_GWF_MAC_CON1,
			     WK3328_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3328_GWF_MAC_CON1,
			     WK3328_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3328_GWF_MAC_CON1,
			     WK3328_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3328_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned int weg;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	weg = bsp_pwiv->integwated_phy ? WK3328_GWF_MAC_CON2 :
		  WK3328_GWF_MAC_CON1;

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, weg,
			     WK3328_GMAC_WMII_CWK_2_5M |
			     WK3328_GMAC_SPEED_10M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, weg,
			     WK3328_GMAC_WMII_CWK_25M |
			     WK3328_GMAC_SPEED_100M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
}

static void wk3328_integwated_phy_powewup(stwuct wk_pwiv_data *pwiv)
{
	wegmap_wwite(pwiv->gwf, WK3328_GWF_MACPHY_CON1,
		     WK3328_MACPHY_WMII_MODE);
}

static const stwuct wk_gmac_ops wk3328_ops = {
	.set_to_wgmii = wk3328_set_to_wgmii,
	.set_to_wmii = wk3328_set_to_wmii,
	.set_wgmii_speed = wk3328_set_wgmii_speed,
	.set_wmii_speed = wk3328_set_wmii_speed,
	.integwated_phy_powewup =  wk3328_integwated_phy_powewup,
};

#define WK3366_GWF_SOC_CON6	0x0418
#define WK3366_GWF_SOC_CON7	0x041c

/* WK3366_GWF_SOC_CON6 */
#define WK3366_GMAC_PHY_INTF_SEW_WGMII	(GWF_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_CWW_BIT(11))
#define WK3366_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_BIT(11))
#define WK3366_GMAC_FWOW_CTWW		GWF_BIT(8)
#define WK3366_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(8)
#define WK3366_GMAC_SPEED_10M		GWF_CWW_BIT(7)
#define WK3366_GMAC_SPEED_100M		GWF_BIT(7)
#define WK3366_GMAC_WMII_CWK_25M	GWF_BIT(3)
#define WK3366_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(3)
#define WK3366_GMAC_CWK_125M		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5))
#define WK3366_GMAC_CWK_25M		(GWF_BIT(4) | GWF_BIT(5))
#define WK3366_GMAC_CWK_2_5M		(GWF_CWW_BIT(4) | GWF_BIT(5))
#define WK3366_GMAC_WMII_MODE		GWF_BIT(6)
#define WK3366_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(6)

/* WK3366_GWF_SOC_CON7 */
#define WK3366_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(7)
#define WK3366_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(7)
#define WK3366_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(15)
#define WK3366_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(15)
#define WK3366_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WK3366_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wk3366_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
		     WK3366_GMAC_PHY_INTF_SEW_WGMII |
		     WK3366_GMAC_WMII_MODE_CWW);
	wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON7,
		     DEWAY_ENABWE(WK3366, tx_deway, wx_deway) |
		     WK3366_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3366_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3366_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
		     WK3366_GMAC_PHY_INTF_SEW_WMII | WK3366_GMAC_WMII_MODE);
}

static void wk3366_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
			     WK3366_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
			     WK3366_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
			     WK3366_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3366_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
			     WK3366_GMAC_WMII_CWK_2_5M |
			     WK3366_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3366_GWF_SOC_CON6,
			     WK3366_GMAC_WMII_CWK_25M |
			     WK3366_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3366_ops = {
	.set_to_wgmii = wk3366_set_to_wgmii,
	.set_to_wmii = wk3366_set_to_wmii,
	.set_wgmii_speed = wk3366_set_wgmii_speed,
	.set_wmii_speed = wk3366_set_wmii_speed,
};

#define WK3368_GWF_SOC_CON15	0x043c
#define WK3368_GWF_SOC_CON16	0x0440

/* WK3368_GWF_SOC_CON15 */
#define WK3368_GMAC_PHY_INTF_SEW_WGMII	(GWF_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_CWW_BIT(11))
#define WK3368_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_BIT(11))
#define WK3368_GMAC_FWOW_CTWW		GWF_BIT(8)
#define WK3368_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(8)
#define WK3368_GMAC_SPEED_10M		GWF_CWW_BIT(7)
#define WK3368_GMAC_SPEED_100M		GWF_BIT(7)
#define WK3368_GMAC_WMII_CWK_25M	GWF_BIT(3)
#define WK3368_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(3)
#define WK3368_GMAC_CWK_125M		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5))
#define WK3368_GMAC_CWK_25M		(GWF_BIT(4) | GWF_BIT(5))
#define WK3368_GMAC_CWK_2_5M		(GWF_CWW_BIT(4) | GWF_BIT(5))
#define WK3368_GMAC_WMII_MODE		GWF_BIT(6)
#define WK3368_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(6)

/* WK3368_GWF_SOC_CON16 */
#define WK3368_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(7)
#define WK3368_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(7)
#define WK3368_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(15)
#define WK3368_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(15)
#define WK3368_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WK3368_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wk3368_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
		     WK3368_GMAC_PHY_INTF_SEW_WGMII |
		     WK3368_GMAC_WMII_MODE_CWW);
	wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON16,
		     DEWAY_ENABWE(WK3368, tx_deway, wx_deway) |
		     WK3368_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3368_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3368_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
		     WK3368_GMAC_PHY_INTF_SEW_WMII | WK3368_GMAC_WMII_MODE);
}

static void wk3368_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
			     WK3368_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
			     WK3368_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
			     WK3368_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3368_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
			     WK3368_GMAC_WMII_CWK_2_5M |
			     WK3368_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3368_GWF_SOC_CON15,
			     WK3368_GMAC_WMII_CWK_25M |
			     WK3368_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3368_ops = {
	.set_to_wgmii = wk3368_set_to_wgmii,
	.set_to_wmii = wk3368_set_to_wmii,
	.set_wgmii_speed = wk3368_set_wgmii_speed,
	.set_wmii_speed = wk3368_set_wmii_speed,
};

#define WK3399_GWF_SOC_CON5	0xc214
#define WK3399_GWF_SOC_CON6	0xc218

/* WK3399_GWF_SOC_CON5 */
#define WK3399_GMAC_PHY_INTF_SEW_WGMII	(GWF_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_CWW_BIT(11))
#define WK3399_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(9) | GWF_CWW_BIT(10) | \
					 GWF_BIT(11))
#define WK3399_GMAC_FWOW_CTWW		GWF_BIT(8)
#define WK3399_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(8)
#define WK3399_GMAC_SPEED_10M		GWF_CWW_BIT(7)
#define WK3399_GMAC_SPEED_100M		GWF_BIT(7)
#define WK3399_GMAC_WMII_CWK_25M	GWF_BIT(3)
#define WK3399_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(3)
#define WK3399_GMAC_CWK_125M		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5))
#define WK3399_GMAC_CWK_25M		(GWF_BIT(4) | GWF_BIT(5))
#define WK3399_GMAC_CWK_2_5M		(GWF_CWW_BIT(4) | GWF_BIT(5))
#define WK3399_GMAC_WMII_MODE		GWF_BIT(6)
#define WK3399_GMAC_WMII_MODE_CWW	GWF_CWW_BIT(6)

/* WK3399_GWF_SOC_CON6 */
#define WK3399_GMAC_TXCWK_DWY_ENABWE	GWF_BIT(7)
#define WK3399_GMAC_TXCWK_DWY_DISABWE	GWF_CWW_BIT(7)
#define WK3399_GMAC_WXCWK_DWY_ENABWE	GWF_BIT(15)
#define WK3399_GMAC_WXCWK_DWY_DISABWE	GWF_CWW_BIT(15)
#define WK3399_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WK3399_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wk3399_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
		     WK3399_GMAC_PHY_INTF_SEW_WGMII |
		     WK3399_GMAC_WMII_MODE_CWW);
	wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON6,
		     DEWAY_ENABWE(WK3399, tx_deway, wx_deway) |
		     WK3399_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3399_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3399_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
		     WK3399_GMAC_PHY_INTF_SEW_WMII | WK3399_GMAC_WMII_MODE);
}

static void wk3399_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10)
		wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
			     WK3399_GMAC_CWK_2_5M);
	ewse if (speed == 100)
		wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
			     WK3399_GMAC_CWK_25M);
	ewse if (speed == 1000)
		wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
			     WK3399_GMAC_CWK_125M);
	ewse
		dev_eww(dev, "unknown speed vawue fow WGMII! speed=%d", speed);
}

static void wk3399_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
			     WK3399_GMAC_WMII_CWK_2_5M |
			     WK3399_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WK3399_GWF_SOC_CON5,
			     WK3399_GMAC_WMII_CWK_25M |
			     WK3399_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wk3399_ops = {
	.set_to_wgmii = wk3399_set_to_wgmii,
	.set_to_wmii = wk3399_set_to_wmii,
	.set_wgmii_speed = wk3399_set_wgmii_speed,
	.set_wmii_speed = wk3399_set_wmii_speed,
};

#define WK3568_GWF_GMAC0_CON0		0x0380
#define WK3568_GWF_GMAC0_CON1		0x0384
#define WK3568_GWF_GMAC1_CON0		0x0388
#define WK3568_GWF_GMAC1_CON1		0x038c

/* WK3568_GWF_GMAC0_CON1 && WK3568_GWF_GMAC1_CON1 */
#define WK3568_GMAC_PHY_INTF_SEW_WGMII	\
		(GWF_BIT(4) | GWF_CWW_BIT(5) | GWF_CWW_BIT(6))
#define WK3568_GMAC_PHY_INTF_SEW_WMII	\
		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | GWF_BIT(6))
#define WK3568_GMAC_FWOW_CTWW			GWF_BIT(3)
#define WK3568_GMAC_FWOW_CTWW_CWW		GWF_CWW_BIT(3)
#define WK3568_GMAC_WXCWK_DWY_ENABWE		GWF_BIT(1)
#define WK3568_GMAC_WXCWK_DWY_DISABWE		GWF_CWW_BIT(1)
#define WK3568_GMAC_TXCWK_DWY_ENABWE		GWF_BIT(0)
#define WK3568_GMAC_TXCWK_DWY_DISABWE		GWF_CWW_BIT(0)

/* WK3568_GWF_GMAC0_CON0 && WK3568_GWF_GMAC1_CON0 */
#define WK3568_GMAC_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WK3568_GMAC_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wk3568_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	u32 con0, con1;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	con0 = (bsp_pwiv->id == 1) ? WK3568_GWF_GMAC1_CON0 :
				     WK3568_GWF_GMAC0_CON0;
	con1 = (bsp_pwiv->id == 1) ? WK3568_GWF_GMAC1_CON1 :
				     WK3568_GWF_GMAC0_CON1;

	wegmap_wwite(bsp_pwiv->gwf, con0,
		     WK3568_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3568_GMAC_CWK_TX_DW_CFG(tx_deway));

	wegmap_wwite(bsp_pwiv->gwf, con1,
		     WK3568_GMAC_PHY_INTF_SEW_WGMII |
		     WK3568_GMAC_WXCWK_DWY_ENABWE |
		     WK3568_GMAC_TXCWK_DWY_ENABWE);
}

static void wk3568_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	u32 con1;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	con1 = (bsp_pwiv->id == 1) ? WK3568_GWF_GMAC1_CON1 :
				     WK3568_GWF_GMAC0_CON1;
	wegmap_wwite(bsp_pwiv->gwf, con1, WK3568_GMAC_PHY_INTF_SEW_WMII);
}

static void wk3568_set_gmac_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct cwk *cwk_mac_speed = bsp_pwiv->cwks[WK_CWK_MAC_SPEED].cwk;
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned wong wate;
	int wet;

	switch (speed) {
	case 10:
		wate = 2500000;
		bweak;
	case 100:
		wate = 25000000;
		bweak;
	case 1000:
		wate = 125000000;
		bweak;
	defauwt:
		dev_eww(dev, "unknown speed vawue fow GMAC speed=%d", speed);
		wetuwn;
	}

	wet = cwk_set_wate(cwk_mac_speed, wate);
	if (wet)
		dev_eww(dev, "%s: set cwk_mac_speed wate %wd faiwed %d\n",
			__func__, wate, wet);
}

static const stwuct wk_gmac_ops wk3568_ops = {
	.set_to_wgmii = wk3568_set_to_wgmii,
	.set_to_wmii = wk3568_set_to_wmii,
	.set_wgmii_speed = wk3568_set_gmac_speed,
	.set_wmii_speed = wk3568_set_gmac_speed,
	.wegs_vawid = twue,
	.wegs = {
		0xfe2a0000, /* gmac0 */
		0xfe010000, /* gmac1 */
		0x0, /* sentinew */
	},
};

/* sys_gwf */
#define WK3588_GWF_GMAC_CON7			0X031c
#define WK3588_GWF_GMAC_CON8			0X0320
#define WK3588_GWF_GMAC_CON9			0X0324

#define WK3588_GMAC_WXCWK_DWY_ENABWE(id)	GWF_BIT(2 * (id) + 3)
#define WK3588_GMAC_WXCWK_DWY_DISABWE(id)	GWF_CWW_BIT(2 * (id) + 3)
#define WK3588_GMAC_TXCWK_DWY_ENABWE(id)	GWF_BIT(2 * (id) + 2)
#define WK3588_GMAC_TXCWK_DWY_DISABWE(id)	GWF_CWW_BIT(2 * (id) + 2)

#define WK3588_GMAC_CWK_WX_DW_CFG(vaw)		HIWOWD_UPDATE(vaw, 0xFF, 8)
#define WK3588_GMAC_CWK_TX_DW_CFG(vaw)		HIWOWD_UPDATE(vaw, 0xFF, 0)

/* php_gwf */
#define WK3588_GWF_GMAC_CON0			0X0008
#define WK3588_GWF_CWK_CON1			0X0070

#define WK3588_GMAC_PHY_INTF_SEW_WGMII(id)	\
	(GWF_BIT(3 + (id) * 6) | GWF_CWW_BIT(4 + (id) * 6) | GWF_CWW_BIT(5 + (id) * 6))
#define WK3588_GMAC_PHY_INTF_SEW_WMII(id)	\
	(GWF_CWW_BIT(3 + (id) * 6) | GWF_CWW_BIT(4 + (id) * 6) | GWF_BIT(5 + (id) * 6))

#define WK3588_GMAC_CWK_WMII_MODE(id)		GWF_BIT(5 * (id))
#define WK3588_GMAC_CWK_WGMII_MODE(id)		GWF_CWW_BIT(5 * (id))

#define WK3588_GMAC_CWK_SEWET_CWU(id)		GWF_BIT(5 * (id) + 4)
#define WK3588_GMAC_CWK_SEWET_IO(id)		GWF_CWW_BIT(5 * (id) + 4)

#define WK3588_GMA_CWK_WMII_DIV2(id)		GWF_BIT(5 * (id) + 2)
#define WK3588_GMA_CWK_WMII_DIV20(id)		GWF_CWW_BIT(5 * (id) + 2)

#define WK3588_GMAC_CWK_WGMII_DIV1(id)		\
			(GWF_CWW_BIT(5 * (id) + 2) | GWF_CWW_BIT(5 * (id) + 3))
#define WK3588_GMAC_CWK_WGMII_DIV5(id)		\
			(GWF_BIT(5 * (id) + 2) | GWF_BIT(5 * (id) + 3))
#define WK3588_GMAC_CWK_WGMII_DIV50(id)		\
			(GWF_CWW_BIT(5 * (id) + 2) | GWF_BIT(5 * (id) + 3))

#define WK3588_GMAC_CWK_WMII_GATE(id)		GWF_BIT(5 * (id) + 1)
#define WK3588_GMAC_CWK_WMII_NOGATE(id)		GWF_CWW_BIT(5 * (id) + 1)

static void wk3588_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	u32 offset_con, id = bsp_pwiv->id;

	if (IS_EWW(bsp_pwiv->gwf) || IS_EWW(bsp_pwiv->php_gwf)) {
		dev_eww(dev, "Missing wockchip,gwf ow wockchip,php_gwf pwopewty\n");
		wetuwn;
	}

	offset_con = bsp_pwiv->id == 1 ? WK3588_GWF_GMAC_CON9 :
					 WK3588_GWF_GMAC_CON8;

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_GMAC_CON0,
		     WK3588_GMAC_PHY_INTF_SEW_WGMII(id));

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_CWK_CON1,
		     WK3588_GMAC_CWK_WGMII_MODE(id));

	wegmap_wwite(bsp_pwiv->gwf, WK3588_GWF_GMAC_CON7,
		     WK3588_GMAC_WXCWK_DWY_ENABWE(id) |
		     WK3588_GMAC_TXCWK_DWY_ENABWE(id));

	wegmap_wwite(bsp_pwiv->gwf, offset_con,
		     WK3588_GMAC_CWK_WX_DW_CFG(wx_deway) |
		     WK3588_GMAC_CWK_TX_DW_CFG(tx_deway));
}

static void wk3588_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->php_gwf)) {
		dev_eww(dev, "%s: Missing wockchip,php_gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_GMAC_CON0,
		     WK3588_GMAC_PHY_INTF_SEW_WMII(bsp_pwiv->id));

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_CWK_CON1,
		     WK3588_GMAC_CWK_WMII_MODE(bsp_pwiv->id));
}

static void wk3588_set_gmac_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned int vaw = 0, id = bsp_pwiv->id;

	switch (speed) {
	case 10:
		if (bsp_pwiv->phy_iface == PHY_INTEWFACE_MODE_WMII)
			vaw = WK3588_GMA_CWK_WMII_DIV20(id);
		ewse
			vaw = WK3588_GMAC_CWK_WGMII_DIV50(id);
		bweak;
	case 100:
		if (bsp_pwiv->phy_iface == PHY_INTEWFACE_MODE_WMII)
			vaw = WK3588_GMA_CWK_WMII_DIV2(id);
		ewse
			vaw = WK3588_GMAC_CWK_WGMII_DIV5(id);
		bweak;
	case 1000:
		if (bsp_pwiv->phy_iface != PHY_INTEWFACE_MODE_WMII)
			vaw = WK3588_GMAC_CWK_WGMII_DIV1(id);
		ewse
			goto eww;
		bweak;
	defauwt:
		goto eww;
	}

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_CWK_CON1, vaw);

	wetuwn;
eww:
	dev_eww(dev, "unknown speed vawue fow GMAC speed=%d", speed);
}

static void wk3588_set_cwock_sewection(stwuct wk_pwiv_data *bsp_pwiv, boow input,
				       boow enabwe)
{
	unsigned int vaw = input ? WK3588_GMAC_CWK_SEWET_IO(bsp_pwiv->id) :
				   WK3588_GMAC_CWK_SEWET_CWU(bsp_pwiv->id);

	vaw |= enabwe ? WK3588_GMAC_CWK_WMII_NOGATE(bsp_pwiv->id) :
			WK3588_GMAC_CWK_WMII_GATE(bsp_pwiv->id);

	wegmap_wwite(bsp_pwiv->php_gwf, WK3588_GWF_CWK_CON1, vaw);
}

static const stwuct wk_gmac_ops wk3588_ops = {
	.set_to_wgmii = wk3588_set_to_wgmii,
	.set_to_wmii = wk3588_set_to_wmii,
	.set_wgmii_speed = wk3588_set_gmac_speed,
	.set_wmii_speed = wk3588_set_gmac_speed,
	.set_cwock_sewection = wk3588_set_cwock_sewection,
	.wegs_vawid = twue,
	.wegs = {
		0xfe1b0000, /* gmac0 */
		0xfe1c0000, /* gmac1 */
		0x0, /* sentinew */
	},
};

#define WV1108_GWF_GMAC_CON0		0X0900

/* WV1108_GWF_GMAC_CON0 */
#define WV1108_GMAC_PHY_INTF_SEW_WMII	(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | \
					GWF_BIT(6))
#define WV1108_GMAC_FWOW_CTWW		GWF_BIT(3)
#define WV1108_GMAC_FWOW_CTWW_CWW	GWF_CWW_BIT(3)
#define WV1108_GMAC_SPEED_10M		GWF_CWW_BIT(2)
#define WV1108_GMAC_SPEED_100M		GWF_BIT(2)
#define WV1108_GMAC_WMII_CWK_25M	GWF_BIT(7)
#define WV1108_GMAC_WMII_CWK_2_5M	GWF_CWW_BIT(7)

static void wv1108_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WV1108_GWF_GMAC_CON0,
		     WV1108_GMAC_PHY_INTF_SEW_WMII);
}

static void wv1108_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	if (speed == 10) {
		wegmap_wwite(bsp_pwiv->gwf, WV1108_GWF_GMAC_CON0,
			     WV1108_GMAC_WMII_CWK_2_5M |
			     WV1108_GMAC_SPEED_10M);
	} ewse if (speed == 100) {
		wegmap_wwite(bsp_pwiv->gwf, WV1108_GWF_GMAC_CON0,
			     WV1108_GMAC_WMII_CWK_25M |
			     WV1108_GMAC_SPEED_100M);
	} ewse {
		dev_eww(dev, "unknown speed vawue fow WMII! speed=%d", speed);
	}
}

static const stwuct wk_gmac_ops wv1108_ops = {
	.set_to_wmii = wv1108_set_to_wmii,
	.set_wmii_speed = wv1108_set_wmii_speed,
};

#define WV1126_GWF_GMAC_CON0		0X0070
#define WV1126_GWF_GMAC_CON1		0X0074
#define WV1126_GWF_GMAC_CON2		0X0078

/* WV1126_GWF_GMAC_CON0 */
#define WV1126_GMAC_PHY_INTF_SEW_WGMII	\
		(GWF_BIT(4) | GWF_CWW_BIT(5) | GWF_CWW_BIT(6))
#define WV1126_GMAC_PHY_INTF_SEW_WMII	\
		(GWF_CWW_BIT(4) | GWF_CWW_BIT(5) | GWF_BIT(6))
#define WV1126_GMAC_FWOW_CTWW			GWF_BIT(7)
#define WV1126_GMAC_FWOW_CTWW_CWW		GWF_CWW_BIT(7)
#define WV1126_GMAC_M0_WXCWK_DWY_ENABWE		GWF_BIT(1)
#define WV1126_GMAC_M0_WXCWK_DWY_DISABWE	GWF_CWW_BIT(1)
#define WV1126_GMAC_M0_TXCWK_DWY_ENABWE		GWF_BIT(0)
#define WV1126_GMAC_M0_TXCWK_DWY_DISABWE	GWF_CWW_BIT(0)
#define WV1126_GMAC_M1_WXCWK_DWY_ENABWE		GWF_BIT(3)
#define WV1126_GMAC_M1_WXCWK_DWY_DISABWE	GWF_CWW_BIT(3)
#define WV1126_GMAC_M1_TXCWK_DWY_ENABWE		GWF_BIT(2)
#define WV1126_GMAC_M1_TXCWK_DWY_DISABWE	GWF_CWW_BIT(2)

/* WV1126_GWF_GMAC_CON1 */
#define WV1126_GMAC_M0_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WV1126_GMAC_M0_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)
/* WV1126_GWF_GMAC_CON2 */
#define WV1126_GMAC_M1_CWK_WX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 8)
#define WV1126_GMAC_M1_CWK_TX_DW_CFG(vaw)	HIWOWD_UPDATE(vaw, 0x7F, 0)

static void wv1126_set_to_wgmii(stwuct wk_pwiv_data *bsp_pwiv,
				int tx_deway, int wx_deway)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WV1126_GWF_GMAC_CON0,
		     WV1126_GMAC_PHY_INTF_SEW_WGMII |
		     WV1126_GMAC_M0_WXCWK_DWY_ENABWE |
		     WV1126_GMAC_M0_TXCWK_DWY_ENABWE |
		     WV1126_GMAC_M1_WXCWK_DWY_ENABWE |
		     WV1126_GMAC_M1_TXCWK_DWY_ENABWE);

	wegmap_wwite(bsp_pwiv->gwf, WV1126_GWF_GMAC_CON1,
		     WV1126_GMAC_M0_CWK_WX_DW_CFG(wx_deway) |
		     WV1126_GMAC_M0_CWK_TX_DW_CFG(tx_deway));

	wegmap_wwite(bsp_pwiv->gwf, WV1126_GWF_GMAC_CON2,
		     WV1126_GMAC_M1_CWK_WX_DW_CFG(wx_deway) |
		     WV1126_GMAC_M1_CWK_TX_DW_CFG(tx_deway));
}

static void wv1126_set_to_wmii(stwuct wk_pwiv_data *bsp_pwiv)
{
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (IS_EWW(bsp_pwiv->gwf)) {
		dev_eww(dev, "%s: Missing wockchip,gwf pwopewty\n", __func__);
		wetuwn;
	}

	wegmap_wwite(bsp_pwiv->gwf, WV1126_GWF_GMAC_CON0,
		     WV1126_GMAC_PHY_INTF_SEW_WMII);
}

static void wv1126_set_wgmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct cwk *cwk_mac_speed = bsp_pwiv->cwks[WK_CWK_MAC_SPEED].cwk;
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned wong wate;
	int wet;

	switch (speed) {
	case 10:
		wate = 2500000;
		bweak;
	case 100:
		wate = 25000000;
		bweak;
	case 1000:
		wate = 125000000;
		bweak;
	defauwt:
		dev_eww(dev, "unknown speed vawue fow WGMII speed=%d", speed);
		wetuwn;
	}

	wet = cwk_set_wate(cwk_mac_speed, wate);
	if (wet)
		dev_eww(dev, "%s: set cwk_mac_speed wate %wd faiwed %d\n",
			__func__, wate, wet);
}

static void wv1126_set_wmii_speed(stwuct wk_pwiv_data *bsp_pwiv, int speed)
{
	stwuct cwk *cwk_mac_speed = bsp_pwiv->cwks[WK_CWK_MAC_SPEED].cwk;
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	unsigned wong wate;
	int wet;

	switch (speed) {
	case 10:
		wate = 2500000;
		bweak;
	case 100:
		wate = 25000000;
		bweak;
	defauwt:
		dev_eww(dev, "unknown speed vawue fow WGMII speed=%d", speed);
		wetuwn;
	}

	wet = cwk_set_wate(cwk_mac_speed, wate);
	if (wet)
		dev_eww(dev, "%s: set cwk_mac_speed wate %wd faiwed %d\n",
			__func__, wate, wet);
}

static const stwuct wk_gmac_ops wv1126_ops = {
	.set_to_wgmii = wv1126_set_to_wgmii,
	.set_to_wmii = wv1126_set_to_wmii,
	.set_wgmii_speed = wv1126_set_wgmii_speed,
	.set_wmii_speed = wv1126_set_wmii_speed,
};

#define WK_GWF_MACPHY_CON0		0xb00
#define WK_GWF_MACPHY_CON1		0xb04
#define WK_GWF_MACPHY_CON2		0xb08
#define WK_GWF_MACPHY_CON3		0xb0c

#define WK_MACPHY_ENABWE		GWF_BIT(0)
#define WK_MACPHY_DISABWE		GWF_CWW_BIT(0)
#define WK_MACPHY_CFG_CWK_50M		GWF_BIT(14)
#define WK_GMAC2PHY_WMII_MODE		(GWF_BIT(6) | GWF_CWW_BIT(7))
#define WK_GWF_CON2_MACPHY_ID		HIWOWD_UPDATE(0x1234, 0xffff, 0)
#define WK_GWF_CON3_MACPHY_ID		HIWOWD_UPDATE(0x35, 0x3f, 0)

static void wk_gmac_integwated_phy_powewup(stwuct wk_pwiv_data *pwiv)
{
	if (pwiv->ops->integwated_phy_powewup)
		pwiv->ops->integwated_phy_powewup(pwiv);

	wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON0, WK_MACPHY_CFG_CWK_50M);
	wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON0, WK_GMAC2PHY_WMII_MODE);

	wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON2, WK_GWF_CON2_MACPHY_ID);
	wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON3, WK_GWF_CON3_MACPHY_ID);

	if (pwiv->phy_weset) {
		/* PHY needs to be disabwed befowe twying to weset it */
		wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON0, WK_MACPHY_DISABWE);
		if (pwiv->phy_weset)
			weset_contwow_assewt(pwiv->phy_weset);
		usweep_wange(10, 20);
		if (pwiv->phy_weset)
			weset_contwow_deassewt(pwiv->phy_weset);
		usweep_wange(10, 20);
		wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON0, WK_MACPHY_ENABWE);
		msweep(30);
	}
}

static void wk_gmac_integwated_phy_powewdown(stwuct wk_pwiv_data *pwiv)
{
	wegmap_wwite(pwiv->gwf, WK_GWF_MACPHY_CON0, WK_MACPHY_DISABWE);
	if (pwiv->phy_weset)
		weset_contwow_assewt(pwiv->phy_weset);
}

static int wk_gmac_cwk_init(stwuct pwat_stmmacenet_data *pwat)
{
	stwuct wk_pwiv_data *bsp_pwiv = pwat->bsp_pwiv;
	stwuct device *dev = &bsp_pwiv->pdev->dev;
	int phy_iface = bsp_pwiv->phy_iface;
	int i, j, wet;

	bsp_pwiv->cwk_enabwed = fawse;

	bsp_pwiv->num_cwks = AWWAY_SIZE(wk_cwocks);
	if (phy_iface == PHY_INTEWFACE_MODE_WMII)
		bsp_pwiv->num_cwks += AWWAY_SIZE(wk_wmii_cwocks);

	bsp_pwiv->cwks = devm_kcawwoc(dev, bsp_pwiv->num_cwks,
				      sizeof(*bsp_pwiv->cwks), GFP_KEWNEW);
	if (!bsp_pwiv->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wk_cwocks); i++)
		bsp_pwiv->cwks[i].id = wk_cwocks[i];

	if (phy_iface == PHY_INTEWFACE_MODE_WMII) {
		fow (j = 0; j < AWWAY_SIZE(wk_wmii_cwocks); j++)
			bsp_pwiv->cwks[i++].id = wk_wmii_cwocks[j];
	}

	wet = devm_cwk_buwk_get_optionaw(dev, bsp_pwiv->num_cwks,
					 bsp_pwiv->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get cwocks\n");

	/* "stmmaceth" wiww be enabwed by the cowe */
	bsp_pwiv->cwk_mac = devm_cwk_get(dev, "stmmaceth");
	wet = PTW_EWW_OW_ZEWO(bsp_pwiv->cwk_mac);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot get stmmaceth cwock\n");

	if (bsp_pwiv->cwock_input) {
		dev_info(dev, "cwock input fwom PHY\n");
	} ewse if (phy_iface == PHY_INTEWFACE_MODE_WMII) {
		cwk_set_wate(bsp_pwiv->cwk_mac, 50000000);
	}

	if (pwat->phy_node && bsp_pwiv->integwated_phy) {
		bsp_pwiv->cwk_phy = of_cwk_get(pwat->phy_node, 0);
		wet = PTW_EWW_OW_ZEWO(bsp_pwiv->cwk_phy);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Cannot get PHY cwock\n");
		cwk_set_wate(bsp_pwiv->cwk_phy, 50000000);
	}

	wetuwn 0;
}

static int gmac_cwk_enabwe(stwuct wk_pwiv_data *bsp_pwiv, boow enabwe)
{
	int wet;

	if (enabwe) {
		if (!bsp_pwiv->cwk_enabwed) {
			wet = cwk_buwk_pwepawe_enabwe(bsp_pwiv->num_cwks,
						      bsp_pwiv->cwks);
			if (wet)
				wetuwn wet;

			wet = cwk_pwepawe_enabwe(bsp_pwiv->cwk_phy);
			if (wet)
				wetuwn wet;

			if (bsp_pwiv->ops && bsp_pwiv->ops->set_cwock_sewection)
				bsp_pwiv->ops->set_cwock_sewection(bsp_pwiv,
					       bsp_pwiv->cwock_input, twue);

			mdeway(5);
			bsp_pwiv->cwk_enabwed = twue;
		}
	} ewse {
		if (bsp_pwiv->cwk_enabwed) {
			cwk_buwk_disabwe_unpwepawe(bsp_pwiv->num_cwks,
						   bsp_pwiv->cwks);
			cwk_disabwe_unpwepawe(bsp_pwiv->cwk_phy);

			if (bsp_pwiv->ops && bsp_pwiv->ops->set_cwock_sewection)
				bsp_pwiv->ops->set_cwock_sewection(bsp_pwiv,
					      bsp_pwiv->cwock_input, fawse);

			bsp_pwiv->cwk_enabwed = fawse;
		}
	}

	wetuwn 0;
}

static int phy_powew_on(stwuct wk_pwiv_data *bsp_pwiv, boow enabwe)
{
	stwuct weguwatow *wdo = bsp_pwiv->weguwatow;
	int wet;
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	if (enabwe) {
		wet = weguwatow_enabwe(wdo);
		if (wet)
			dev_eww(dev, "faiw to enabwe phy-suppwy\n");
	} ewse {
		wet = weguwatow_disabwe(wdo);
		if (wet)
			dev_eww(dev, "faiw to disabwe phy-suppwy\n");
	}

	wetuwn 0;
}

static stwuct wk_pwiv_data *wk_gmac_setup(stwuct pwatfowm_device *pdev,
					  stwuct pwat_stmmacenet_data *pwat,
					  const stwuct wk_gmac_ops *ops)
{
	stwuct wk_pwiv_data *bsp_pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int wet;
	const chaw *stwings = NUWW;
	int vawue;

	bsp_pwiv = devm_kzawwoc(dev, sizeof(*bsp_pwiv), GFP_KEWNEW);
	if (!bsp_pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	of_get_phy_mode(dev->of_node, &bsp_pwiv->phy_iface);
	bsp_pwiv->ops = ops;

	/* Some SoCs have muwtipwe MAC contwowwews, which need
	 * to be distinguished.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes && ops->wegs_vawid) {
		int i = 0;

		whiwe (ops->wegs[i]) {
			if (ops->wegs[i] == wes->stawt) {
				bsp_pwiv->id = i;
				bweak;
			}
			i++;
		}
	}

	bsp_pwiv->weguwatow = devm_weguwatow_get(dev, "phy");
	if (IS_EWW(bsp_pwiv->weguwatow)) {
		wet = PTW_EWW(bsp_pwiv->weguwatow);
		dev_eww_pwobe(dev, wet, "faiwed to get phy weguwatow\n");
		wetuwn EWW_PTW(wet);
	}

	wet = of_pwopewty_wead_stwing(dev->of_node, "cwock_in_out", &stwings);
	if (wet) {
		dev_eww(dev, "Can not wead pwopewty: cwock_in_out.\n");
		bsp_pwiv->cwock_input = twue;
	} ewse {
		dev_info(dev, "cwock input ow output? (%s).\n",
			 stwings);
		if (!stwcmp(stwings, "input"))
			bsp_pwiv->cwock_input = twue;
		ewse
			bsp_pwiv->cwock_input = fawse;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "tx_deway", &vawue);
	if (wet) {
		bsp_pwiv->tx_deway = 0x30;
		dev_eww(dev, "Can not wead pwopewty: tx_deway.");
		dev_eww(dev, "set tx_deway to 0x%x\n",
			bsp_pwiv->tx_deway);
	} ewse {
		dev_info(dev, "TX deway(0x%x).\n", vawue);
		bsp_pwiv->tx_deway = vawue;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "wx_deway", &vawue);
	if (wet) {
		bsp_pwiv->wx_deway = 0x10;
		dev_eww(dev, "Can not wead pwopewty: wx_deway.");
		dev_eww(dev, "set wx_deway to 0x%x\n",
			bsp_pwiv->wx_deway);
	} ewse {
		dev_info(dev, "WX deway(0x%x).\n", vawue);
		bsp_pwiv->wx_deway = vawue;
	}

	bsp_pwiv->gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							"wockchip,gwf");
	bsp_pwiv->php_gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							    "wockchip,php-gwf");

	if (pwat->phy_node) {
		bsp_pwiv->integwated_phy = of_pwopewty_wead_boow(pwat->phy_node,
								 "phy-is-integwated");
		if (bsp_pwiv->integwated_phy) {
			bsp_pwiv->phy_weset = of_weset_contwow_get(pwat->phy_node, NUWW);
			if (IS_EWW(bsp_pwiv->phy_weset)) {
				dev_eww(&pdev->dev, "No PHY weset contwow found.\n");
				bsp_pwiv->phy_weset = NUWW;
			}
		}
	}
	dev_info(dev, "integwated PHY? (%s).\n",
		 bsp_pwiv->integwated_phy ? "yes" : "no");

	bsp_pwiv->pdev = pdev;

	wetuwn bsp_pwiv;
}

static int wk_gmac_check_ops(stwuct wk_pwiv_data *bsp_pwiv)
{
	switch (bsp_pwiv->phy_iface) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		if (!bsp_pwiv->ops->set_to_wgmii)
			wetuwn -EINVAW;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		if (!bsp_pwiv->ops->set_to_wmii)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		dev_eww(&bsp_pwiv->pdev->dev,
			"unsuppowted intewface %d", bsp_pwiv->phy_iface);
	}
	wetuwn 0;
}

static int wk_gmac_powewup(stwuct wk_pwiv_data *bsp_pwiv)
{
	int wet;
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	wet = wk_gmac_check_ops(bsp_pwiv);
	if (wet)
		wetuwn wet;

	wet = gmac_cwk_enabwe(bsp_pwiv, twue);
	if (wet)
		wetuwn wet;

	/*wmii ow wgmii*/
	switch (bsp_pwiv->phy_iface) {
	case PHY_INTEWFACE_MODE_WGMII:
		dev_info(dev, "init fow WGMII\n");
		bsp_pwiv->ops->set_to_wgmii(bsp_pwiv, bsp_pwiv->tx_deway,
					    bsp_pwiv->wx_deway);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		dev_info(dev, "init fow WGMII_ID\n");
		bsp_pwiv->ops->set_to_wgmii(bsp_pwiv, 0, 0);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		dev_info(dev, "init fow WGMII_WXID\n");
		bsp_pwiv->ops->set_to_wgmii(bsp_pwiv, bsp_pwiv->tx_deway, 0);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		dev_info(dev, "init fow WGMII_TXID\n");
		bsp_pwiv->ops->set_to_wgmii(bsp_pwiv, 0, bsp_pwiv->wx_deway);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		dev_info(dev, "init fow WMII\n");
		bsp_pwiv->ops->set_to_wmii(bsp_pwiv);
		bweak;
	defauwt:
		dev_eww(dev, "NO intewface defined!\n");
	}

	wet = phy_powew_on(bsp_pwiv, twue);
	if (wet) {
		gmac_cwk_enabwe(bsp_pwiv, fawse);
		wetuwn wet;
	}

	pm_wuntime_get_sync(dev);

	if (bsp_pwiv->integwated_phy)
		wk_gmac_integwated_phy_powewup(bsp_pwiv);

	wetuwn 0;
}

static void wk_gmac_powewdown(stwuct wk_pwiv_data *gmac)
{
	if (gmac->integwated_phy)
		wk_gmac_integwated_phy_powewdown(gmac);

	pm_wuntime_put_sync(&gmac->pdev->dev);

	phy_powew_on(gmac, fawse);
	gmac_cwk_enabwe(gmac, fawse);
}

static void wk_fix_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct wk_pwiv_data *bsp_pwiv = pwiv;
	stwuct device *dev = &bsp_pwiv->pdev->dev;

	switch (bsp_pwiv->phy_iface) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		if (bsp_pwiv->ops->set_wgmii_speed)
			bsp_pwiv->ops->set_wgmii_speed(bsp_pwiv, speed);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		if (bsp_pwiv->ops->set_wmii_speed)
			bsp_pwiv->ops->set_wmii_speed(bsp_pwiv, speed);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted intewface %d", bsp_pwiv->phy_iface);
	}
}

static int wk_gmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	const stwuct wk_gmac_ops *data;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "no of match data pwovided\n");
		wetuwn -EINVAW;
	}

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	/* If the stmmac is not awweady sewected as gmac4,
	 * then make suwe we fawwback to gmac.
	 */
	if (!pwat_dat->has_gmac4)
		pwat_dat->has_gmac = twue;
	pwat_dat->fix_mac_speed = wk_fix_speed;

	pwat_dat->bsp_pwiv = wk_gmac_setup(pdev, pwat_dat, data);
	if (IS_EWW(pwat_dat->bsp_pwiv))
		wetuwn PTW_EWW(pwat_dat->bsp_pwiv);

	wet = wk_gmac_cwk_init(pwat_dat);
	if (wet)
		wetuwn wet;

	wet = wk_gmac_powewup(pwat_dat->bsp_pwiv);
	if (wet)
		wetuwn wet;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto eww_gmac_powewdown;

	wetuwn 0;

eww_gmac_powewdown:
	wk_gmac_powewdown(pwat_dat->bsp_pwiv);

	wetuwn wet;
}

static void wk_gmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk_pwiv_data *bsp_pwiv = get_stmmac_bsp_pwiv(&pdev->dev);

	stmmac_dvw_wemove(&pdev->dev);

	wk_gmac_powewdown(bsp_pwiv);
}

#ifdef CONFIG_PM_SWEEP
static int wk_gmac_suspend(stwuct device *dev)
{
	stwuct wk_pwiv_data *bsp_pwiv = get_stmmac_bsp_pwiv(dev);
	int wet = stmmac_suspend(dev);

	/* Keep the PHY up if we use Wake-on-Wan. */
	if (!device_may_wakeup(dev)) {
		wk_gmac_powewdown(bsp_pwiv);
		bsp_pwiv->suspended = twue;
	}

	wetuwn wet;
}

static int wk_gmac_wesume(stwuct device *dev)
{
	stwuct wk_pwiv_data *bsp_pwiv = get_stmmac_bsp_pwiv(dev);

	/* The PHY was up fow Wake-on-Wan. */
	if (bsp_pwiv->suspended) {
		wk_gmac_powewup(bsp_pwiv);
		bsp_pwiv->suspended = fawse;
	}

	wetuwn stmmac_wesume(dev);
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(wk_gmac_pm_ops, wk_gmac_suspend, wk_gmac_wesume);

static const stwuct of_device_id wk_gmac_dwmac_match[] = {
	{ .compatibwe = "wockchip,px30-gmac",	.data = &px30_ops   },
	{ .compatibwe = "wockchip,wk3128-gmac", .data = &wk3128_ops },
	{ .compatibwe = "wockchip,wk3228-gmac", .data = &wk3228_ops },
	{ .compatibwe = "wockchip,wk3288-gmac", .data = &wk3288_ops },
	{ .compatibwe = "wockchip,wk3308-gmac", .data = &wk3308_ops },
	{ .compatibwe = "wockchip,wk3328-gmac", .data = &wk3328_ops },
	{ .compatibwe = "wockchip,wk3366-gmac", .data = &wk3366_ops },
	{ .compatibwe = "wockchip,wk3368-gmac", .data = &wk3368_ops },
	{ .compatibwe = "wockchip,wk3399-gmac", .data = &wk3399_ops },
	{ .compatibwe = "wockchip,wk3568-gmac", .data = &wk3568_ops },
	{ .compatibwe = "wockchip,wk3588-gmac", .data = &wk3588_ops },
	{ .compatibwe = "wockchip,wv1108-gmac", .data = &wv1108_ops },
	{ .compatibwe = "wockchip,wv1126-gmac", .data = &wv1126_ops },
	{ }
};
MODUWE_DEVICE_TABWE(of, wk_gmac_dwmac_match);

static stwuct pwatfowm_dwivew wk_gmac_dwmac_dwivew = {
	.pwobe  = wk_gmac_pwobe,
	.wemove_new = wk_gmac_wemove,
	.dwivew = {
		.name           = "wk_gmac-dwmac",
		.pm		= &wk_gmac_pm_ops,
		.of_match_tabwe = wk_gmac_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(wk_gmac_dwmac_dwivew);

MODUWE_AUTHOW("Chen-Zhi (Wogew Chen) <wogew.chen@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip WK3288 DWMAC specific gwue wayew");
MODUWE_WICENSE("GPW");
