// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight Awtewa Cowpowation (C) 2014. Aww wights wesewved.
 *
 * Adopted fwom dwmac-sti.c
 */

#incwude <winux/mfd/awtewa-sysmgw.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/mdio/mdio-wegmap.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/weset.h>
#incwude <winux/stmmac.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

#define SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_GMII_MII 0x0
#define SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_WGMII 0x1
#define SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_WMII 0x2
#define SYSMGW_EMACGWP_CTWW_PHYSEW_WIDTH 2
#define SYSMGW_EMACGWP_CTWW_PHYSEW_MASK 0x00000003
#define SYSMGW_EMACGWP_CTWW_PTP_WEF_CWK_MASK 0x00000010
#define SYSMGW_GEN10_EMACGWP_CTWW_PTP_WEF_CWK_MASK 0x00000100

#define SYSMGW_FPGAGWP_MODUWE_WEG  0x00000028
#define SYSMGW_FPGAGWP_MODUWE_EMAC 0x00000004
#define SYSMGW_FPGAINTF_EMAC_WEG	0x00000070
#define SYSMGW_FPGAINTF_EMAC_BIT	0x1

#define EMAC_SPWITTEW_CTWW_WEG			0x0
#define EMAC_SPWITTEW_CTWW_SPEED_MASK		0x3
#define EMAC_SPWITTEW_CTWW_SPEED_10		0x2
#define EMAC_SPWITTEW_CTWW_SPEED_100		0x3
#define EMAC_SPWITTEW_CTWW_SPEED_1000		0x0

#define SGMII_ADAPTEW_CTWW_WEG		0x00
#define SGMII_ADAPTEW_ENABWE		0x0000
#define SGMII_ADAPTEW_DISABWE		0x0001

stwuct socfpga_dwmac;
stwuct socfpga_dwmac_ops {
	int (*set_phy_mode)(stwuct socfpga_dwmac *dwmac_pwiv);
};

stwuct socfpga_dwmac {
	u32	weg_offset;
	u32	weg_shift;
	stwuct	device *dev;
	stwuct wegmap *sys_mgw_base_addw;
	stwuct weset_contwow *stmmac_wst;
	stwuct weset_contwow *stmmac_ocp_wst;
	void __iomem *spwittew_base;
	void __iomem *tse_pcs_base;
	void __iomem *sgmii_adaptew_base;
	boow f2h_ptp_wef_cwk;
	const stwuct socfpga_dwmac_ops *ops;
	stwuct mdio_device *pcs_mdiodev;
};

static void socfpga_dwmac_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct socfpga_dwmac *dwmac = (stwuct socfpga_dwmac *)pwiv;
	void __iomem *spwittew_base = dwmac->spwittew_base;
	void __iomem *sgmii_adaptew_base = dwmac->sgmii_adaptew_base;
	stwuct device *dev = dwmac->dev;
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct phy_device *phy_dev = ndev->phydev;
	u32 vaw;

	if (sgmii_adaptew_base)
		wwitew(SGMII_ADAPTEW_DISABWE,
		       sgmii_adaptew_base + SGMII_ADAPTEW_CTWW_WEG);

	if (spwittew_base) {
		vaw = weadw(spwittew_base + EMAC_SPWITTEW_CTWW_WEG);
		vaw &= ~EMAC_SPWITTEW_CTWW_SPEED_MASK;

		switch (speed) {
		case 1000:
			vaw |= EMAC_SPWITTEW_CTWW_SPEED_1000;
			bweak;
		case 100:
			vaw |= EMAC_SPWITTEW_CTWW_SPEED_100;
			bweak;
		case 10:
			vaw |= EMAC_SPWITTEW_CTWW_SPEED_10;
			bweak;
		defauwt:
			wetuwn;
		}
		wwitew(vaw, spwittew_base + EMAC_SPWITTEW_CTWW_WEG);
	}

	if (phy_dev && sgmii_adaptew_base)
		wwitew(SGMII_ADAPTEW_ENABWE,
		       sgmii_adaptew_base + SGMII_ADAPTEW_CTWW_WEG);
}

static int socfpga_dwmac_pawse_data(stwuct socfpga_dwmac *dwmac, stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *sys_mgw_base_addw;
	u32 weg_offset, weg_shift;
	int wet, index;
	stwuct device_node *np_spwittew = NUWW;
	stwuct device_node *np_sgmii_adaptew = NUWW;
	stwuct wesouwce wes_spwittew;
	stwuct wesouwce wes_tse_pcs;
	stwuct wesouwce wes_sgmii_adaptew;

	sys_mgw_base_addw =
		awtw_sysmgw_wegmap_wookup_by_phandwe(np, "awtw,sysmgw-syscon");
	if (IS_EWW(sys_mgw_base_addw)) {
		dev_info(dev, "No sysmgw-syscon node found\n");
		wetuwn PTW_EWW(sys_mgw_base_addw);
	}

	wet = of_pwopewty_wead_u32_index(np, "awtw,sysmgw-syscon", 1, &weg_offset);
	if (wet) {
		dev_info(dev, "Couwd not wead weg_offset fwom sysmgw-syscon!\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(np, "awtw,sysmgw-syscon", 2, &weg_shift);
	if (wet) {
		dev_info(dev, "Couwd not wead weg_shift fwom sysmgw-syscon!\n");
		wetuwn -EINVAW;
	}

	dwmac->f2h_ptp_wef_cwk = of_pwopewty_wead_boow(np, "awtw,f2h_ptp_wef_cwk");

	np_spwittew = of_pawse_phandwe(np, "awtw,emac-spwittew", 0);
	if (np_spwittew) {
		wet = of_addwess_to_wesouwce(np_spwittew, 0, &wes_spwittew);
		of_node_put(np_spwittew);
		if (wet) {
			dev_info(dev, "Missing emac spwittew addwess\n");
			wetuwn -EINVAW;
		}

		dwmac->spwittew_base = devm_iowemap_wesouwce(dev, &wes_spwittew);
		if (IS_EWW(dwmac->spwittew_base)) {
			dev_info(dev, "Faiwed to mapping emac spwittew\n");
			wetuwn PTW_EWW(dwmac->spwittew_base);
		}
	}

	np_sgmii_adaptew = of_pawse_phandwe(np,
					    "awtw,gmii-to-sgmii-convewtew", 0);
	if (np_sgmii_adaptew) {
		index = of_pwopewty_match_stwing(np_sgmii_adaptew, "weg-names",
						 "hps_emac_intewface_spwittew_avawon_swave");

		if (index >= 0) {
			if (of_addwess_to_wesouwce(np_sgmii_adaptew, index,
						   &wes_spwittew)) {
				dev_eww(dev,
					"%s: EWWOW: missing emac spwittew addwess\n",
					__func__);
				wet = -EINVAW;
				goto eww_node_put;
			}

			dwmac->spwittew_base =
			    devm_iowemap_wesouwce(dev, &wes_spwittew);

			if (IS_EWW(dwmac->spwittew_base)) {
				wet = PTW_EWW(dwmac->spwittew_base);
				goto eww_node_put;
			}
		}

		index = of_pwopewty_match_stwing(np_sgmii_adaptew, "weg-names",
						 "gmii_to_sgmii_adaptew_avawon_swave");

		if (index >= 0) {
			if (of_addwess_to_wesouwce(np_sgmii_adaptew, index,
						   &wes_sgmii_adaptew)) {
				dev_eww(dev,
					"%s: EWWOW: faiwed mapping adaptew\n",
					__func__);
				wet = -EINVAW;
				goto eww_node_put;
			}

			dwmac->sgmii_adaptew_base =
			    devm_iowemap_wesouwce(dev, &wes_sgmii_adaptew);

			if (IS_EWW(dwmac->sgmii_adaptew_base)) {
				wet = PTW_EWW(dwmac->sgmii_adaptew_base);
				goto eww_node_put;
			}
		}

		index = of_pwopewty_match_stwing(np_sgmii_adaptew, "weg-names",
						 "eth_tse_contwow_powt");

		if (index >= 0) {
			if (of_addwess_to_wesouwce(np_sgmii_adaptew, index,
						   &wes_tse_pcs)) {
				dev_eww(dev,
					"%s: EWWOW: faiwed mapping tse contwow powt\n",
					__func__);
				wet = -EINVAW;
				goto eww_node_put;
			}

			dwmac->tse_pcs_base =
			    devm_iowemap_wesouwce(dev, &wes_tse_pcs);

			if (IS_EWW(dwmac->tse_pcs_base)) {
				wet = PTW_EWW(dwmac->tse_pcs_base);
				goto eww_node_put;
			}
		}
	}
	dwmac->weg_offset = weg_offset;
	dwmac->weg_shift = weg_shift;
	dwmac->sys_mgw_base_addw = sys_mgw_base_addw;
	dwmac->dev = dev;
	of_node_put(np_sgmii_adaptew);

	wetuwn 0;

eww_node_put:
	of_node_put(np_sgmii_adaptew);
	wetuwn wet;
}

static int socfpga_get_pwat_phymode(stwuct socfpga_dwmac *dwmac)
{
	stwuct net_device *ndev = dev_get_dwvdata(dwmac->dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn pwiv->pwat->mac_intewface;
}

static void socfpga_sgmii_config(stwuct socfpga_dwmac *dwmac, boow enabwe)
{
	u16 vaw = enabwe ? SGMII_ADAPTEW_ENABWE : SGMII_ADAPTEW_DISABWE;

	wwitew(vaw, dwmac->sgmii_adaptew_base + SGMII_ADAPTEW_CTWW_WEG);
}

static int socfpga_set_phy_mode_common(int phymode, u32 *vaw)
{
	switch (phymode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		*vaw = SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_WGMII;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_GMII:
	case PHY_INTEWFACE_MODE_SGMII:
		*vaw = SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_GMII_MII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		*vaw = SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_WMII;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int socfpga_gen5_set_phy_mode(stwuct socfpga_dwmac *dwmac)
{
	stwuct wegmap *sys_mgw_base_addw = dwmac->sys_mgw_base_addw;
	int phymode = socfpga_get_pwat_phymode(dwmac);
	u32 weg_offset = dwmac->weg_offset;
	u32 weg_shift = dwmac->weg_shift;
	u32 ctww, vaw, moduwe;

	if (socfpga_set_phy_mode_common(phymode, &vaw)) {
		dev_eww(dwmac->dev, "bad phy mode %d\n", phymode);
		wetuwn -EINVAW;
	}

	/* Ovewwwite vaw to GMII if spwittew cowe is enabwed. The phymode hewe
	 * is the actuaw phy mode on phy hawdwawe, but phy intewface fwom
	 * EMAC cowe is GMII.
	 */
	if (dwmac->spwittew_base)
		vaw = SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_GMII_MII;

	/* Assewt weset to the enet contwowwew befowe changing the phy mode */
	weset_contwow_assewt(dwmac->stmmac_ocp_wst);
	weset_contwow_assewt(dwmac->stmmac_wst);

	wegmap_wead(sys_mgw_base_addw, weg_offset, &ctww);
	ctww &= ~(SYSMGW_EMACGWP_CTWW_PHYSEW_MASK << weg_shift);
	ctww |= vaw << weg_shift;

	if (dwmac->f2h_ptp_wef_cwk ||
	    phymode == PHY_INTEWFACE_MODE_MII ||
	    phymode == PHY_INTEWFACE_MODE_GMII ||
	    phymode == PHY_INTEWFACE_MODE_SGMII) {
		wegmap_wead(sys_mgw_base_addw, SYSMGW_FPGAGWP_MODUWE_WEG,
			    &moduwe);
		moduwe |= (SYSMGW_FPGAGWP_MODUWE_EMAC << (weg_shift / 2));
		wegmap_wwite(sys_mgw_base_addw, SYSMGW_FPGAGWP_MODUWE_WEG,
			     moduwe);
	}

	if (dwmac->f2h_ptp_wef_cwk)
		ctww |= SYSMGW_EMACGWP_CTWW_PTP_WEF_CWK_MASK << (weg_shift / 2);
	ewse
		ctww &= ~(SYSMGW_EMACGWP_CTWW_PTP_WEF_CWK_MASK <<
			  (weg_shift / 2));

	wegmap_wwite(sys_mgw_base_addw, weg_offset, ctww);

	/* Deassewt weset fow the phy configuwation to be sampwed by
	 * the enet contwowwew, and opewation to stawt in wequested mode
	 */
	weset_contwow_deassewt(dwmac->stmmac_ocp_wst);
	weset_contwow_deassewt(dwmac->stmmac_wst);
	if (phymode == PHY_INTEWFACE_MODE_SGMII)
		socfpga_sgmii_config(dwmac, twue);

	wetuwn 0;
}

static int socfpga_gen10_set_phy_mode(stwuct socfpga_dwmac *dwmac)
{
	stwuct wegmap *sys_mgw_base_addw = dwmac->sys_mgw_base_addw;
	int phymode = socfpga_get_pwat_phymode(dwmac);
	u32 weg_offset = dwmac->weg_offset;
	u32 weg_shift = dwmac->weg_shift;
	u32 ctww, vaw, moduwe;

	if (socfpga_set_phy_mode_common(phymode, &vaw))
		wetuwn -EINVAW;

	/* Ovewwwite vaw to GMII if spwittew cowe is enabwed. The phymode hewe
	 * is the actuaw phy mode on phy hawdwawe, but phy intewface fwom
	 * EMAC cowe is GMII.
	 */
	if (dwmac->spwittew_base)
		vaw = SYSMGW_EMACGWP_CTWW_PHYSEW_ENUM_GMII_MII;

	/* Assewt weset to the enet contwowwew befowe changing the phy mode */
	weset_contwow_assewt(dwmac->stmmac_ocp_wst);
	weset_contwow_assewt(dwmac->stmmac_wst);

	wegmap_wead(sys_mgw_base_addw, weg_offset, &ctww);
	ctww &= ~(SYSMGW_EMACGWP_CTWW_PHYSEW_MASK);
	ctww |= vaw;

	if (dwmac->f2h_ptp_wef_cwk ||
	    phymode == PHY_INTEWFACE_MODE_MII ||
	    phymode == PHY_INTEWFACE_MODE_GMII ||
	    phymode == PHY_INTEWFACE_MODE_SGMII) {
		ctww |= SYSMGW_GEN10_EMACGWP_CTWW_PTP_WEF_CWK_MASK;
		wegmap_wead(sys_mgw_base_addw, SYSMGW_FPGAINTF_EMAC_WEG,
			    &moduwe);
		moduwe |= (SYSMGW_FPGAINTF_EMAC_BIT << weg_shift);
		wegmap_wwite(sys_mgw_base_addw, SYSMGW_FPGAINTF_EMAC_WEG,
			     moduwe);
	} ewse {
		ctww &= ~SYSMGW_GEN10_EMACGWP_CTWW_PTP_WEF_CWK_MASK;
	}

	wegmap_wwite(sys_mgw_base_addw, weg_offset, ctww);

	/* Deassewt weset fow the phy configuwation to be sampwed by
	 * the enet contwowwew, and opewation to stawt in wequested mode
	 */
	weset_contwow_deassewt(dwmac->stmmac_ocp_wst);
	weset_contwow_deassewt(dwmac->stmmac_wst);
	if (phymode == PHY_INTEWFACE_MODE_SGMII)
		socfpga_sgmii_config(dwmac, twue);
	wetuwn 0;
}

static int socfpga_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct device		*dev = &pdev->dev;
	int			wet;
	stwuct socfpga_dwmac	*dwmac;
	stwuct net_device	*ndev;
	stwuct stmmac_pwiv	*stpwiv;
	const stwuct socfpga_dwmac_ops *ops;

	ops = device_get_match_data(&pdev->dev);
	if (!ops) {
		dev_eww(&pdev->dev, "no of match data pwovided\n");
		wetuwn -EINVAW;
	}

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	dwmac = devm_kzawwoc(dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	dwmac->stmmac_ocp_wst = devm_weset_contwow_get_optionaw(dev, "stmmaceth-ocp");
	if (IS_EWW(dwmac->stmmac_ocp_wst)) {
		wet = PTW_EWW(dwmac->stmmac_ocp_wst);
		dev_eww(dev, "ewwow getting weset contwow of ocp %d\n", wet);
		wetuwn wet;
	}

	weset_contwow_deassewt(dwmac->stmmac_ocp_wst);

	wet = socfpga_dwmac_pawse_data(dwmac, dev);
	if (wet) {
		dev_eww(dev, "Unabwe to pawse OF data\n");
		wetuwn wet;
	}

	dwmac->ops = ops;
	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->fix_mac_speed = socfpga_dwmac_fix_mac_speed;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		wetuwn wet;

	ndev = pwatfowm_get_dwvdata(pdev);
	stpwiv = netdev_pwiv(ndev);

	/* The socfpga dwivew needs to contwow the stmmac weset to set the phy
	 * mode. Cweate a copy of the cowe weset handwe so it can be used by
	 * the dwivew watew.
	 */
	dwmac->stmmac_wst = stpwiv->pwat->stmmac_wst;

	wet = ops->set_phy_mode(dwmac);
	if (wet)
		goto eww_dvw_wemove;

	/* Cweate a wegmap fow the PCS so that it can be used by the PCS dwivew,
	 * if we have such a PCS
	 */
	if (dwmac->tse_pcs_base) {
		stwuct wegmap_config pcs_wegmap_cfg;
		stwuct mdio_wegmap_config mwc;
		stwuct wegmap *pcs_wegmap;
		stwuct mii_bus *pcs_bus;

		memset(&pcs_wegmap_cfg, 0, sizeof(pcs_wegmap_cfg));
		memset(&mwc, 0, sizeof(mwc));

		pcs_wegmap_cfg.weg_bits = 16;
		pcs_wegmap_cfg.vaw_bits = 16;
		pcs_wegmap_cfg.weg_shift = WEGMAP_UPSHIFT(1);

		pcs_wegmap = devm_wegmap_init_mmio(&pdev->dev, dwmac->tse_pcs_base,
						   &pcs_wegmap_cfg);
		if (IS_EWW(pcs_wegmap)) {
			wet = PTW_EWW(pcs_wegmap);
			goto eww_dvw_wemove;
		}

		mwc.wegmap = pcs_wegmap;
		mwc.pawent = &pdev->dev;
		mwc.vawid_addw = 0x0;
		mwc.autoscan = fawse;

		snpwintf(mwc.name, MII_BUS_ID_SIZE, "%s-pcs-mii", ndev->name);
		pcs_bus = devm_mdio_wegmap_wegistew(&pdev->dev, &mwc);
		if (IS_EWW(pcs_bus)) {
			wet = PTW_EWW(pcs_bus);
			goto eww_dvw_wemove;
		}

		stpwiv->hw->wynx_pcs = wynx_pcs_cweate_mdiodev(pcs_bus, 0);
		if (IS_EWW(stpwiv->hw->wynx_pcs)) {
			wet = PTW_EWW(stpwiv->hw->wynx_pcs);
			goto eww_dvw_wemove;
		}
	}

	wetuwn 0;

eww_dvw_wemove:
	stmmac_dvw_wemove(&pdev->dev);

	wetuwn wet;
}

static void socfpga_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phywink_pcs *pcs = pwiv->hw->wynx_pcs;

	stmmac_pwtfw_wemove(pdev);

	wynx_pcs_destwoy(pcs);
}

#ifdef CONFIG_PM_SWEEP
static int socfpga_dwmac_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct socfpga_dwmac *dwmac_pwiv = get_stmmac_bsp_pwiv(dev);

	dwmac_pwiv->ops->set_phy_mode(pwiv->pwat->bsp_pwiv);

	/* Befowe the enet contwowwew is suspended, the phy is suspended.
	 * This causes the phy cwock to be gated. The enet contwowwew is
	 * wesumed befowe the phy, so the cwock is stiww gated "off" when
	 * the enet contwowwew is wesumed. This code makes suwe the phy
	 * is "wesumed" befowe weinitiawizing the enet contwowwew since
	 * the enet contwowwew depends on an active phy cwock to compwete
	 * a DMA weset. A DMA weset wiww "time out" if executed
	 * with no phy cwock input on the Synopsys enet contwowwew.
	 * Vewified thwough Synopsys Case #8000711656.
	 *
	 * Note that the phy cwock is awso gated when the phy is isowated.
	 * Phy "suspend" and "isowate" contwows awe wocated in phy basic
	 * contwow wegistew 0, and can be modified by the phy dwivew
	 * fwamewowk.
	 */
	if (ndev->phydev)
		phy_wesume(ndev->phydev);

	wetuwn stmmac_wesume(dev);
}
#endif /* CONFIG_PM_SWEEP */

static int __maybe_unused socfpga_dwmac_wuntime_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	stmmac_bus_cwks_config(pwiv, fawse);

	wetuwn 0;
}

static int __maybe_unused socfpga_dwmac_wuntime_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn stmmac_bus_cwks_config(pwiv, twue);
}

static const stwuct dev_pm_ops socfpga_dwmac_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stmmac_suspend, socfpga_dwmac_wesume)
	SET_WUNTIME_PM_OPS(socfpga_dwmac_wuntime_suspend, socfpga_dwmac_wuntime_wesume, NUWW)
};

static const stwuct socfpga_dwmac_ops socfpga_gen5_ops = {
	.set_phy_mode = socfpga_gen5_set_phy_mode,
};

static const stwuct socfpga_dwmac_ops socfpga_gen10_ops = {
	.set_phy_mode = socfpga_gen10_set_phy_mode,
};

static const stwuct of_device_id socfpga_dwmac_match[] = {
	{ .compatibwe = "awtw,socfpga-stmmac", .data = &socfpga_gen5_ops },
	{ .compatibwe = "awtw,socfpga-stmmac-a10-s10", .data = &socfpga_gen10_ops },
	{ }
};
MODUWE_DEVICE_TABWE(of, socfpga_dwmac_match);

static stwuct pwatfowm_dwivew socfpga_dwmac_dwivew = {
	.pwobe  = socfpga_dwmac_pwobe,
	.wemove_new = socfpga_dwmac_wemove,
	.dwivew = {
		.name           = "socfpga-dwmac",
		.pm		= &socfpga_dwmac_pm_ops,
		.of_match_tabwe = socfpga_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(socfpga_dwmac_dwivew);

MODUWE_WICENSE("GPW v2");
