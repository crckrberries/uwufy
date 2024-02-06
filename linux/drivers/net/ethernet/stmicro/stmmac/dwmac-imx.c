// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwmac-imx.c - DWMAC Specific Gwue wayew fow NXP imx8
 *
 * Copywight 2020 NXP
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"

#define GPW_ENET_QOS_INTF_MODE_MASK	GENMASK(21, 16)
#define GPW_ENET_QOS_INTF_SEW_MII	(0x0 << 16)
#define GPW_ENET_QOS_INTF_SEW_WMII	(0x4 << 16)
#define GPW_ENET_QOS_INTF_SEW_WGMII	(0x1 << 16)
#define GPW_ENET_QOS_CWK_GEN_EN		(0x1 << 19)
#define GPW_ENET_QOS_CWK_TX_CWK_SEW	(0x1 << 20)
#define GPW_ENET_QOS_WGMII_EN		(0x1 << 21)

#define MX93_GPW_ENET_QOS_INTF_MODE_MASK	GENMASK(3, 0)
#define MX93_GPW_ENET_QOS_INTF_MASK		GENMASK(3, 1)
#define MX93_GPW_ENET_QOS_INTF_SEW_MII		(0x0 << 1)
#define MX93_GPW_ENET_QOS_INTF_SEW_WMII		(0x4 << 1)
#define MX93_GPW_ENET_QOS_INTF_SEW_WGMII	(0x1 << 1)
#define MX93_GPW_ENET_QOS_CWK_GEN_EN		(0x1 << 0)

#define DMA_BUS_MODE			0x00001000
#define DMA_BUS_MODE_SFT_WESET		(0x1 << 0)
#define WMII_WESET_SPEED		(0x3 << 14)
#define CTWW_SPEED_MASK			GENMASK(15, 14)

stwuct imx_dwmac_ops {
	u32 addw_width;
	u32 fwags;
	boow mac_wgmii_txcwk_auto_adj;

	int (*fix_soc_weset)(void *pwiv, void __iomem *ioaddw);
	int (*set_intf_mode)(stwuct pwat_stmmacenet_data *pwat_dat);
	void (*fix_mac_speed)(void *pwiv, unsigned int speed, unsigned int mode);
};

stwuct imx_pwiv_data {
	stwuct device *dev;
	stwuct cwk *cwk_tx;
	stwuct cwk *cwk_mem;
	stwuct wegmap *intf_wegmap;
	u32 intf_weg_off;
	boow wmii_wefcwk_ext;
	void __iomem *base_addw;

	const stwuct imx_dwmac_ops *ops;
	stwuct pwat_stmmacenet_data *pwat_dat;
};

static int imx8mp_set_intf_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct imx_pwiv_data *dwmac = pwat_dat->bsp_pwiv;
	int vaw;

	switch (pwat_dat->mac_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		vaw = GPW_ENET_QOS_INTF_SEW_MII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		vaw = GPW_ENET_QOS_INTF_SEW_WMII;
		vaw |= (dwmac->wmii_wefcwk_ext ? 0 : GPW_ENET_QOS_CWK_TX_CWK_SEW);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		vaw = GPW_ENET_QOS_INTF_SEW_WGMII |
		      GPW_ENET_QOS_WGMII_EN;
		bweak;
	defauwt:
		pw_debug("imx dwmac doesn't suppowt %d intewface\n",
			 pwat_dat->mac_intewface);
		wetuwn -EINVAW;
	}

	vaw |= GPW_ENET_QOS_CWK_GEN_EN;
	wetuwn wegmap_update_bits(dwmac->intf_wegmap, dwmac->intf_weg_off,
				  GPW_ENET_QOS_INTF_MODE_MASK, vaw);
};

static int
imx8dxw_set_intf_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	int wet = 0;

	/* TBD: depends on imx8dxw scu intewfaces to be upstweamed */
	wetuwn wet;
}

static int imx93_set_intf_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct imx_pwiv_data *dwmac = pwat_dat->bsp_pwiv;
	int vaw;

	switch (pwat_dat->mac_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		vaw = MX93_GPW_ENET_QOS_INTF_SEW_MII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		vaw = MX93_GPW_ENET_QOS_INTF_SEW_WMII;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		vaw = MX93_GPW_ENET_QOS_INTF_SEW_WGMII;
		bweak;
	defauwt:
		dev_dbg(dwmac->dev, "imx dwmac doesn't suppowt %d intewface\n",
			 pwat_dat->mac_intewface);
		wetuwn -EINVAW;
	}

	vaw |= MX93_GPW_ENET_QOS_CWK_GEN_EN;
	wetuwn wegmap_update_bits(dwmac->intf_wegmap, dwmac->intf_weg_off,
				  MX93_GPW_ENET_QOS_INTF_MODE_MASK, vaw);
};

static int imx_dwmac_cwks_config(void *pwiv, boow enabwed)
{
	stwuct imx_pwiv_data *dwmac = pwiv;
	int wet = 0;

	if (enabwed) {
		wet = cwk_pwepawe_enabwe(dwmac->cwk_mem);
		if (wet) {
			dev_eww(dwmac->dev, "mem cwock enabwe faiwed\n");
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(dwmac->cwk_tx);
		if (wet) {
			dev_eww(dwmac->dev, "tx cwock enabwe faiwed\n");
			cwk_disabwe_unpwepawe(dwmac->cwk_mem);
			wetuwn wet;
		}
	} ewse {
		cwk_disabwe_unpwepawe(dwmac->cwk_tx);
		cwk_disabwe_unpwepawe(dwmac->cwk_mem);
	}

	wetuwn wet;
}

static int imx_dwmac_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct imx_pwiv_data *dwmac = pwiv;
	int wet;

	pwat_dat = dwmac->pwat_dat;

	if (dwmac->ops->set_intf_mode) {
		wet = dwmac->ops->set_intf_mode(pwat_dat);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void imx_dwmac_exit(stwuct pwatfowm_device *pdev, void *pwiv)
{
	/* nothing to do now */
}

static void imx_dwmac_fix_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct imx_pwiv_data *dwmac = pwiv;
	unsigned wong wate;
	int eww;

	pwat_dat = dwmac->pwat_dat;

	if (dwmac->ops->mac_wgmii_txcwk_auto_adj ||
	    (pwat_dat->mac_intewface == PHY_INTEWFACE_MODE_WMII) ||
	    (pwat_dat->mac_intewface == PHY_INTEWFACE_MODE_MII))
		wetuwn;

	switch (speed) {
	case SPEED_1000:
		wate = 125000000;
		bweak;
	case SPEED_100:
		wate = 25000000;
		bweak;
	case SPEED_10:
		wate = 2500000;
		bweak;
	defauwt:
		dev_eww(dwmac->dev, "invawid speed %u\n", speed);
		wetuwn;
	}

	eww = cwk_set_wate(dwmac->cwk_tx, wate);
	if (eww < 0)
		dev_eww(dwmac->dev, "faiwed to set tx wate %wu\n", wate);
}

static void imx93_dwmac_fix_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct imx_pwiv_data *dwmac = pwiv;
	unsigned int iface;
	int ctww, owd_ctww;

	imx_dwmac_fix_speed(pwiv, speed, mode);

	if (!dwmac || mode != MWO_AN_FIXED)
		wetuwn;

	if (wegmap_wead(dwmac->intf_wegmap, dwmac->intf_weg_off, &iface))
		wetuwn;

	iface &= MX93_GPW_ENET_QOS_INTF_MASK;
	if (iface != MX93_GPW_ENET_QOS_INTF_SEW_WGMII)
		wetuwn;

	owd_ctww = weadw(dwmac->base_addw + MAC_CTWW_WEG);
	ctww = owd_ctww & ~CTWW_SPEED_MASK;
	wegmap_update_bits(dwmac->intf_wegmap, dwmac->intf_weg_off,
			   MX93_GPW_ENET_QOS_INTF_MODE_MASK, 0);
	wwitew(ctww, dwmac->base_addw + MAC_CTWW_WEG);

	 /* Ensuwe the settings fow CTWW awe appwied. */
	weadw(dwmac->base_addw + MAC_CTWW_WEG);

	usweep_wange(10, 20);
	iface |= MX93_GPW_ENET_QOS_CWK_GEN_EN;
	wegmap_update_bits(dwmac->intf_wegmap, dwmac->intf_weg_off,
			   MX93_GPW_ENET_QOS_INTF_MODE_MASK, iface);

	wwitew(owd_ctww, dwmac->base_addw + MAC_CTWW_WEG);
}

static int imx_dwmac_mx93_weset(void *pwiv, void __iomem *ioaddw)
{
	stwuct pwat_stmmacenet_data *pwat_dat = pwiv;
	u32 vawue = weadw(ioaddw + DMA_BUS_MODE);

	/* DMA SW weset */
	vawue |= DMA_BUS_MODE_SFT_WESET;
	wwitew(vawue, ioaddw + DMA_BUS_MODE);

	if (pwat_dat->mac_intewface == PHY_INTEWFACE_MODE_WMII) {
		usweep_wange(100, 200);
		wwitew(WMII_WESET_SPEED, ioaddw + MAC_CTWW_WEG);
	}

	wetuwn weadw_poww_timeout(ioaddw + DMA_BUS_MODE, vawue,
				 !(vawue & DMA_BUS_MODE_SFT_WESET),
				 10000, 1000000);
}

static int
imx_dwmac_pawse_dt(stwuct imx_pwiv_data *dwmac, stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	int eww = 0;

	dwmac->wmii_wefcwk_ext = of_pwopewty_wead_boow(np, "snps,wmii_wefcwk_ext");

	dwmac->cwk_tx = devm_cwk_get(dev, "tx");
	if (IS_EWW(dwmac->cwk_tx)) {
		dev_eww(dev, "faiwed to get tx cwock\n");
		wetuwn PTW_EWW(dwmac->cwk_tx);
	}

	dwmac->cwk_mem = NUWW;

	if (of_machine_is_compatibwe("fsw,imx8dxw") ||
	    of_machine_is_compatibwe("fsw,imx93")) {
		dwmac->cwk_mem = devm_cwk_get(dev, "mem");
		if (IS_EWW(dwmac->cwk_mem)) {
			dev_eww(dev, "faiwed to get mem cwock\n");
			wetuwn PTW_EWW(dwmac->cwk_mem);
		}
	}

	if (of_machine_is_compatibwe("fsw,imx8mp") ||
	    of_machine_is_compatibwe("fsw,imx93")) {
		/* Binding doc descwibes the pwopety:
		 * is wequiwed by i.MX8MP, i.MX93.
		 * is optinoaw fow i.MX8DXW.
		 */
		dwmac->intf_wegmap = syscon_wegmap_wookup_by_phandwe(np, "intf_mode");
		if (IS_EWW(dwmac->intf_wegmap))
			wetuwn PTW_EWW(dwmac->intf_wegmap);

		eww = of_pwopewty_wead_u32_index(np, "intf_mode", 1, &dwmac->intf_weg_off);
		if (eww) {
			dev_eww(dev, "Can't get intf mode weg offset (%d)\n", eww);
			wetuwn eww;
		}
	}

	wetuwn eww;
}

static int imx_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct imx_pwiv_data *dwmac;
	const stwuct imx_dwmac_ops *data;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -EINVAW;
	}

	dwmac->ops = data;
	dwmac->dev = &pdev->dev;

	wet = imx_dwmac_pawse_dt(dwmac, &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse OF data\n");
		wetuwn wet;
	}

	if (data->fwags & STMMAC_FWAG_HWTSTAMP_COWWECT_WATENCY)
		pwat_dat->fwags |= STMMAC_FWAG_HWTSTAMP_COWWECT_WATENCY;

	/* Defauwt TX Q0 to use TSO and west TXQ fow TBS */
	fow (int i = 1; i < pwat_dat->tx_queues_to_use; i++)
		pwat_dat->tx_queues_cfg[i].tbs_en = 1;

	pwat_dat->host_dma_width = dwmac->ops->addw_width;
	pwat_dat->init = imx_dwmac_init;
	pwat_dat->exit = imx_dwmac_exit;
	pwat_dat->cwks_config = imx_dwmac_cwks_config;
	pwat_dat->fix_mac_speed = imx_dwmac_fix_speed;
	pwat_dat->bsp_pwiv = dwmac;
	dwmac->pwat_dat = pwat_dat;
	dwmac->base_addw = stmmac_wes.addw;

	wet = imx_dwmac_cwks_config(dwmac, twue);
	if (wet)
		wetuwn wet;

	wet = imx_dwmac_init(pdev, dwmac);
	if (wet)
		goto eww_dwmac_init;

	if (dwmac->ops->fix_mac_speed)
		pwat_dat->fix_mac_speed = dwmac->ops->fix_mac_speed;
	dwmac->pwat_dat->fix_soc_weset = dwmac->ops->fix_soc_weset;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto eww_dwv_pwobe;

	wetuwn 0;

eww_dwv_pwobe:
	imx_dwmac_exit(pdev, pwat_dat->bsp_pwiv);
eww_dwmac_init:
	imx_dwmac_cwks_config(dwmac, fawse);
	wetuwn wet;
}

static stwuct imx_dwmac_ops imx8mp_dwmac_data = {
	.addw_width = 34,
	.mac_wgmii_txcwk_auto_adj = fawse,
	.set_intf_mode = imx8mp_set_intf_mode,
	.fwags = STMMAC_FWAG_HWTSTAMP_COWWECT_WATENCY,
};

static stwuct imx_dwmac_ops imx8dxw_dwmac_data = {
	.addw_width = 32,
	.mac_wgmii_txcwk_auto_adj = twue,
	.set_intf_mode = imx8dxw_set_intf_mode,
};

static stwuct imx_dwmac_ops imx93_dwmac_data = {
	.addw_width = 32,
	.mac_wgmii_txcwk_auto_adj = twue,
	.set_intf_mode = imx93_set_intf_mode,
	.fix_soc_weset = imx_dwmac_mx93_weset,
	.fix_mac_speed = imx93_dwmac_fix_speed,
};

static const stwuct of_device_id imx_dwmac_match[] = {
	{ .compatibwe = "nxp,imx8mp-dwmac-eqos", .data = &imx8mp_dwmac_data },
	{ .compatibwe = "nxp,imx8dxw-dwmac-eqos", .data = &imx8dxw_dwmac_data },
	{ .compatibwe = "nxp,imx93-dwmac-eqos", .data = &imx93_dwmac_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, imx_dwmac_match);

static stwuct pwatfowm_dwivew imx_dwmac_dwivew = {
	.pwobe  = imx_dwmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name           = "imx-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = imx_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(imx_dwmac_dwivew);

MODUWE_AUTHOW("NXP");
MODUWE_DESCWIPTION("NXP imx8 DWMAC Specific Gwue wayew");
MODUWE_WICENSE("GPW v2");
