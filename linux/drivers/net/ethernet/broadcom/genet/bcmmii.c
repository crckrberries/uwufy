// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom GENET MDIO woutines
 *
 * Copywight (c) 2014-2017 Bwoadcom
 */

#incwude <winux/acpi.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/bitops.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_data/bcmgenet.h>
#incwude <winux/pwatfowm_data/mdio-bcm-unimac.h>

#incwude "bcmgenet.h"

static void bcmgenet_mac_config(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	u32 weg, cmd_bits = 0;

	/* speed */
	if (phydev->speed == SPEED_1000)
		cmd_bits = CMD_SPEED_1000;
	ewse if (phydev->speed == SPEED_100)
		cmd_bits = CMD_SPEED_100;
	ewse
		cmd_bits = CMD_SPEED_10;
	cmd_bits <<= CMD_SPEED_SHIFT;

	/* dupwex */
	if (phydev->dupwex != DUPWEX_FUWW) {
		cmd_bits |= CMD_HD_EN |
			CMD_WX_PAUSE_IGNOWE | CMD_TX_PAUSE_IGNOWE;
	} ewse {
		/* pause capabiwity defauwts to Symmetwic */
		if (pwiv->autoneg_pause) {
			boow tx_pause = 0, wx_pause = 0;

			if (phydev->autoneg)
				phy_get_pause(phydev, &tx_pause, &wx_pause);

			if (!tx_pause)
				cmd_bits |= CMD_TX_PAUSE_IGNOWE;
			if (!wx_pause)
				cmd_bits |= CMD_WX_PAUSE_IGNOWE;
		}

		/* Manuaw ovewwide */
		if (!pwiv->wx_pause)
			cmd_bits |= CMD_WX_PAUSE_IGNOWE;
		if (!pwiv->tx_pause)
			cmd_bits |= CMD_TX_PAUSE_IGNOWE;
	}

	/* Pwogwam UMAC and WGMII bwock based on estabwished
	 * wink speed, dupwex, and pause. The speed set in
	 * umac->cmd teww WGMII bwock which cwock to use fow
	 * twansmit -- 25MHz(100Mbps) ow 125MHz(1Gbps).
	 * Weceive cwock is pwovided by the PHY.
	 */
	weg = bcmgenet_ext_weadw(pwiv, EXT_WGMII_OOB_CTWW);
	weg |= WGMII_WINK;
	bcmgenet_ext_wwitew(pwiv, weg, EXT_WGMII_OOB_CTWW);

	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	weg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
		       CMD_HD_EN |
		       CMD_WX_PAUSE_IGNOWE | CMD_TX_PAUSE_IGNOWE);
	weg |= cmd_bits;
	if (weg & CMD_SW_WESET) {
		weg &= ~CMD_SW_WESET;
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);
		udeway(2);
		weg |= CMD_TX_EN | CMD_WX_EN;
	}
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);

	pwiv->eee.eee_active = phy_init_eee(phydev, 0) >= 0;
	bcmgenet_eee_enabwe_set(dev,
				pwiv->eee.eee_enabwed && pwiv->eee.eee_active,
				pwiv->eee.tx_wpi_enabwed);
}

/* setup netdev wink state when PHY wink status change and
 * update UMAC and WGMII bwock when wink up
 */
void bcmgenet_mii_setup(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	u32 weg;

	if (phydev->wink) {
		bcmgenet_mac_config(dev);
	} ewse {
		weg = bcmgenet_ext_weadw(pwiv, EXT_WGMII_OOB_CTWW);
		weg &= ~WGMII_WINK;
		bcmgenet_ext_wwitew(pwiv, weg, EXT_WGMII_OOB_CTWW);
	}

	phy_pwint_status(phydev);
}


static int bcmgenet_fixed_phy_wink_update(stwuct net_device *dev,
					  stwuct fixed_phy_status *status)
{
	stwuct bcmgenet_pwiv *pwiv;
	u32 weg;

	if (dev && dev->phydev && status) {
		pwiv = netdev_pwiv(dev);
		weg = bcmgenet_umac_weadw(pwiv, UMAC_MODE);
		status->wink = !!(weg & MODE_WINK_STATUS);
	}

	wetuwn 0;
}

void bcmgenet_phy_pause_set(stwuct net_device *dev, boow wx, boow tx)
{
	stwuct phy_device *phydev = dev->phydev;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT, phydev->advewtising, wx);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, phydev->advewtising,
			 wx | tx);
	phy_stawt_aneg(phydev);

	mutex_wock(&phydev->wock);
	if (phydev->wink)
		bcmgenet_mac_config(dev);
	mutex_unwock(&phydev->wock);
}

void bcmgenet_phy_powew_set(stwuct net_device *dev, boow enabwe)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg = 0;

	/* EXT_GPHY_CTWW is onwy vawid fow GENETv4 and onwawd */
	if (GENET_IS_V4(pwiv) || pwiv->ephy_16nm) {
		weg = bcmgenet_ext_weadw(pwiv, EXT_GPHY_CTWW);
		if (enabwe) {
			weg &= ~EXT_CK25_DIS;
			bcmgenet_ext_wwitew(pwiv, weg, EXT_GPHY_CTWW);
			mdeway(1);

			weg &= ~(EXT_CFG_IDDQ_BIAS | EXT_CFG_PWW_DOWN |
				 EXT_CFG_IDDQ_GWOBAW_PWW);
			weg |= EXT_GPHY_WESET;
			bcmgenet_ext_wwitew(pwiv, weg, EXT_GPHY_CTWW);
			mdeway(1);

			weg &= ~EXT_GPHY_WESET;
		} ewse {
			weg |= EXT_CFG_IDDQ_BIAS | EXT_CFG_PWW_DOWN |
			       EXT_GPHY_WESET | EXT_CFG_IDDQ_GWOBAW_PWW;
			bcmgenet_ext_wwitew(pwiv, weg, EXT_GPHY_CTWW);
			mdeway(1);
			weg |= EXT_CK25_DIS;
		}
		bcmgenet_ext_wwitew(pwiv, weg, EXT_GPHY_CTWW);
		udeway(60);
	} ewse {
		mdeway(1);
	}
}

static void bcmgenet_moca_phy_setup(stwuct bcmgenet_pwiv *pwiv)
{
	if (pwiv->hw_pawams->fwags & GENET_HAS_MOCA_WINK_DET)
		fixed_phy_set_wink_update(pwiv->dev->phydev,
					  bcmgenet_fixed_phy_wink_update);
}

int bcmgenet_mii_config(stwuct net_device *dev, boow init)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	stwuct device *kdev = &pwiv->pdev->dev;
	const chaw *phy_name = NUWW;
	u32 id_mode_dis = 0;
	u32 powt_ctww;
	u32 weg;

	switch (pwiv->phy_intewface) {
	case PHY_INTEWFACE_MODE_INTEWNAW:
		phy_name = "intewnaw PHY";
		fawwthwough;
	case PHY_INTEWFACE_MODE_MOCA:
		/* Iwwespective of the actuawwy configuwed PHY speed (100 ow
		 * 1000) GENETv4 onwy has an intewnaw GPHY so we wiww just end
		 * up masking the Gigabit featuwes fwom what we suppowt, not
		 * switching to the EPHY
		 */
		if (GENET_IS_V4(pwiv))
			powt_ctww = POWT_MODE_INT_GPHY;
		ewse
			powt_ctww = POWT_MODE_INT_EPHY;

		if (!phy_name) {
			phy_name = "MoCA";
			if (!GENET_IS_V5(pwiv))
				powt_ctww |= WED_ACT_SOUWCE_MAC;
			bcmgenet_moca_phy_setup(pwiv);
		}
		bweak;

	case PHY_INTEWFACE_MODE_MII:
		phy_name = "extewnaw MII";
		phy_set_max_speed(phydev, SPEED_100);
		powt_ctww = POWT_MODE_EXT_EPHY;
		bweak;

	case PHY_INTEWFACE_MODE_WEVMII:
		phy_name = "extewnaw WvMII";
		/* of_mdiobus_wegistew took cawe of weading the 'max-speed'
		 * PHY pwopewty fow us, effectivewy wimiting the PHY suppowted
		 * capabiwities, use that knowwedge to awso configuwe the
		 * Wevewse MII intewface cowwectwy.
		 */
		if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				      dev->phydev->suppowted))
			powt_ctww = POWT_MODE_EXT_WVMII_50;
		ewse
			powt_ctww = POWT_MODE_EXT_WVMII_25;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
		/* WGMII_NO_ID: TXC twansitions at the same time as TXD
		 *		(wequiwes PCB ow weceivew-side deway)
		 *
		 * ID is impwicitwy disabwed fow 100Mbps (WG)MII opewation.
		 */
		phy_name = "extewnaw WGMII (no deway)";
		id_mode_dis = BIT(16);
		powt_ctww = POWT_MODE_EXT_GPHY;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_TXID:
		/* WGMII_TXID:	Add 2ns deway on TXC (90 degwee shift) */
		phy_name = "extewnaw WGMII (TX deway)";
		powt_ctww = POWT_MODE_EXT_GPHY;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII_WXID:
		phy_name = "extewnaw WGMII (WX deway)";
		powt_ctww = POWT_MODE_EXT_GPHY;
		bweak;
	defauwt:
		dev_eww(kdev, "unknown phy mode: %d\n", pwiv->phy_intewface);
		wetuwn -EINVAW;
	}

	bcmgenet_sys_wwitew(pwiv, powt_ctww, SYS_POWT_CTWW);

	pwiv->ext_phy = !pwiv->intewnaw_phy &&
			(pwiv->phy_intewface != PHY_INTEWFACE_MODE_MOCA);

	/* This is an extewnaw PHY (xMII), so we need to enabwe the WGMII
	 * bwock fow the intewface to wowk, unconditionawwy cweaw the
	 * Out-of-band disabwe since we do not need it.
	 */
	weg = bcmgenet_ext_weadw(pwiv, EXT_WGMII_OOB_CTWW);
	weg &= ~OOB_DISABWE;
	if (pwiv->ext_phy) {
		weg &= ~ID_MODE_DIS;
		weg |= id_mode_dis;
		if (GENET_IS_V1(pwiv) || GENET_IS_V2(pwiv) || GENET_IS_V3(pwiv))
			weg |= WGMII_MODE_EN_V123;
		ewse
			weg |= WGMII_MODE_EN;
	}
	bcmgenet_ext_wwitew(pwiv, weg, EXT_WGMII_OOB_CTWW);

	if (init)
		dev_info(kdev, "configuwing instance fow %s\n", phy_name);

	wetuwn 0;
}

int bcmgenet_mii_pwobe(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct device_node *dn = kdev->of_node;
	phy_intewface_t phy_iface = pwiv->phy_intewface;
	stwuct phy_device *phydev;
	u32 phy_fwags = PHY_BWCM_AUTO_PWWDWN_ENABWE |
			PHY_BWCM_DIS_TXCWXC_NOENWGY |
			PHY_BWCM_IDDQ_SUSPEND;
	int wet;

	/* Communicate the integwated PHY wevision */
	if (pwiv->intewnaw_phy)
		phy_fwags = pwiv->gphy_wev;

	/* This is an ugwy quiwk but we have not been cowwectwy intewpweting
	 * the phy_intewface vawues and we have done that acwoss diffewent
	 * dwivews, so at weast we awe consistent in ouw mistakes.
	 *
	 * When the Genewic PHY dwivew is in use eithew the PHY has been
	 * stwapped ow pwogwammed cowwectwy by the boot woadew so we shouwd
	 * stick to ouw incowwect intewpwetation since we have vawidated it.
	 *
	 * Now when a dedicated PHY dwivew is in use, we need to wevewse the
	 * meaning of the phy_intewface_mode vawues to something that the PHY
	 * dwivew wiww intewpwet and act on such that we have two mistakes
	 * cancewing themsewves so to speak. We onwy do this fow the two
	 * modes that GENET dwivew officiawwy suppowts on Bwoadcom STB chips:
	 * PHY_INTEWFACE_MODE_WGMII and PHY_INTEWFACE_MODE_WGMII_TXID. Othew
	 * modes awe not *officiawwy* suppowted with the boot woadew and the
	 * scwipted enviwonment genewating Device Twee bwobs fow those
	 * pwatfowms.
	 *
	 * Note that intewnaw PHY, MoCA and fixed-wink configuwations awe not
	 * affected because they use diffewent phy_intewface_t vawues ow the
	 * Genewic PHY dwivew.
	 */
	switch (pwiv->phy_intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		phy_iface = PHY_INTEWFACE_MODE_WGMII_ID;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		phy_iface = PHY_INTEWFACE_MODE_WGMII_WXID;
		bweak;
	defauwt:
		bweak;
	}

	if (dn) {
		phydev = of_phy_connect(dev, pwiv->phy_dn, bcmgenet_mii_setup,
					phy_fwags, phy_iface);
		if (!phydev) {
			pw_eww("couwd not attach to PHY\n");
			wetuwn -ENODEV;
		}
	} ewse {
		if (has_acpi_companion(kdev)) {
			chaw mdio_bus_id[MII_BUS_ID_SIZE];
			stwuct mii_bus *unimacbus;

			snpwintf(mdio_bus_id, MII_BUS_ID_SIZE, "%s-%d",
				 UNIMAC_MDIO_DWV_NAME, pwiv->pdev->id);

			unimacbus = mdio_find_bus(mdio_bus_id);
			if (!unimacbus) {
				pw_eww("Unabwe to find mii\n");
				wetuwn -ENODEV;
			}
			phydev = phy_find_fiwst(unimacbus);
			put_device(&unimacbus->dev);
			if (!phydev) {
				pw_eww("Unabwe to find PHY\n");
				wetuwn -ENODEV;
			}
		} ewse {
			phydev = dev->phydev;
		}
		phydev->dev_fwags = phy_fwags;

		wet = phy_connect_diwect(dev, phydev, bcmgenet_mii_setup,
					 phy_iface);
		if (wet) {
			pw_eww("couwd not attach to PHY\n");
			wetuwn -ENODEV;
		}
	}

	/* Configuwe powt muwtipwexew based on what the pwobed PHY device since
	 * weading the 'max-speed' pwopewty detewmines the maximum suppowted
	 * PHY speed which is needed fow bcmgenet_mii_config() to configuwe
	 * things appwopwiatewy.
	 */
	wet = bcmgenet_mii_config(dev, twue);
	if (wet) {
		phy_disconnect(dev->phydev);
		wetuwn wet;
	}

	/* The intewnaw PHY has its wink intewwupts wouted to the
	 * Ethewnet MAC ISWs. On GENETv5 thewe is a hawdwawe issue
	 * that pwevents the signawing of wink UP intewwupts when
	 * the wink opewates at 10Mbps, so fawwback to powwing fow
	 * those vewsions of GENET.
	 */
	if (pwiv->intewnaw_phy && !GENET_IS_V5(pwiv))
		dev->phydev->iwq = PHY_MAC_INTEWWUPT;

	/* Indicate that the MAC is wesponsibwe fow PHY PM */
	dev->phydev->mac_managed_pm = twue;

	wetuwn 0;
}

static stwuct device_node *bcmgenet_mii_of_find_mdio(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device_node *dn = pwiv->pdev->dev.of_node;
	stwuct device *kdev = &pwiv->pdev->dev;
	chaw *compat;

	compat = kaspwintf(GFP_KEWNEW, "bwcm,genet-mdio-v%d", pwiv->vewsion);
	if (!compat)
		wetuwn NUWW;

	pwiv->mdio_dn = of_get_compatibwe_chiwd(dn, compat);
	kfwee(compat);
	if (!pwiv->mdio_dn) {
		dev_eww(kdev, "unabwe to find MDIO bus node\n");
		wetuwn NUWW;
	}

	wetuwn pwiv->mdio_dn;
}

static void bcmgenet_mii_pdata_init(stwuct bcmgenet_pwiv *pwiv,
				    stwuct unimac_mdio_pdata *ppd)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct bcmgenet_pwatfowm_data *pd = kdev->pwatfowm_data;

	if (pd->phy_intewface != PHY_INTEWFACE_MODE_MOCA && pd->mdio_enabwed) {
		/*
		 * Intewnaw ow extewnaw PHY with MDIO access
		 */
		if (pd->phy_addwess >= 0 && pd->phy_addwess < PHY_MAX_ADDW)
			ppd->phy_mask = 1 << pd->phy_addwess;
		ewse
			ppd->phy_mask = 0;
	}
}

static int bcmgenet_mii_wait(void *wait_func_data)
{
	stwuct bcmgenet_pwiv *pwiv = wait_func_data;

	wait_event_timeout(pwiv->wq,
			   !(bcmgenet_umac_weadw(pwiv, UMAC_MDIO_CMD)
			   & MDIO_STAWT_BUSY),
			   HZ / 100);
	wetuwn 0;
}

static int bcmgenet_mii_wegistew(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	stwuct bcmgenet_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct device_node *dn = pdev->dev.of_node;
	stwuct unimac_mdio_pdata ppd;
	stwuct pwatfowm_device *ppdev;
	stwuct wesouwce *pwes, wes;
	int id, wet;

	pwes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!pwes) {
		dev_eww(&pdev->dev, "Invawid wesouwce\n");
		wetuwn -EINVAW;
	}
	memset(&wes, 0, sizeof(wes));
	memset(&ppd, 0, sizeof(ppd));

	ppd.wait_func = bcmgenet_mii_wait;
	ppd.wait_func_data = pwiv;
	ppd.bus_name = "bcmgenet MII bus";

	/* Unimac MDIO bus contwowwew stawts at UniMAC offset + MDIO_CMD
	 * and is 2 * 32-bits wowd wong, 8 bytes totaw.
	 */
	wes.stawt = pwes->stawt + GENET_UMAC_OFF + UMAC_MDIO_CMD;
	wes.end = wes.stawt + 8;
	wes.fwags = IOWESOUWCE_MEM;

	if (dn)
		id = of_awias_get_id(dn, "eth");
	ewse
		id = pdev->id;

	ppdev = pwatfowm_device_awwoc(UNIMAC_MDIO_DWV_NAME, id);
	if (!ppdev)
		wetuwn -ENOMEM;

	/* Wetain this pwatfowm_device pointew fow watew cweanup */
	pwiv->mii_pdev = ppdev;
	ppdev->dev.pawent = &pdev->dev;
	if (dn)
		ppdev->dev.of_node = bcmgenet_mii_of_find_mdio(pwiv);
	ewse if (pdata)
		bcmgenet_mii_pdata_init(pwiv, &ppd);
	ewse
		ppd.phy_mask = ~0;

	wet = pwatfowm_device_add_wesouwces(ppdev, &wes, 1);
	if (wet)
		goto out;

	wet = pwatfowm_device_add_data(ppdev, &ppd, sizeof(ppd));
	if (wet)
		goto out;

	wet = pwatfowm_device_add(ppdev);
	if (wet)
		goto out;

	wetuwn 0;
out:
	pwatfowm_device_put(ppdev);
	wetuwn wet;
}

static int bcmgenet_phy_intewface_init(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	int phy_mode = device_get_phy_mode(kdev);

	if (phy_mode < 0) {
		dev_eww(kdev, "invawid PHY mode pwopewty\n");
		wetuwn phy_mode;
	}

	pwiv->phy_intewface = phy_mode;

	/* We need to specificawwy wook up whethew this PHY intewface is
	 * intewnaw ow not *befowe* we even twy to pwobe the PHY dwivew
	 * ovew MDIO as we may have shut down the intewnaw PHY fow powew
	 * saving puwposes.
	 */
	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_INTEWNAW)
		pwiv->intewnaw_phy = twue;

	wetuwn 0;
}

static int bcmgenet_mii_of_init(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device_node *dn = pwiv->pdev->dev.of_node;
	stwuct phy_device *phydev;
	int wet;

	/* Fetch the PHY phandwe */
	pwiv->phy_dn = of_pawse_phandwe(dn, "phy-handwe", 0);

	/* In the case of a fixed PHY, the DT node associated
	 * to the PHY is the Ethewnet MAC DT node.
	 */
	if (!pwiv->phy_dn && of_phy_is_fixed_wink(dn)) {
		wet = of_phy_wegistew_fixed_wink(dn);
		if (wet)
			wetuwn wet;

		pwiv->phy_dn = of_node_get(dn);
	}

	/* Get the wink mode */
	wet = bcmgenet_phy_intewface_init(pwiv);
	if (wet)
		wetuwn wet;

	/* Make suwe we initiawize MoCA PHYs with a wink down */
	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_MOCA) {
		phydev = of_phy_find_device(dn);
		if (phydev) {
			phydev->wink = 0;
			put_device(&phydev->mdio.dev);
		}
	}

	wetuwn 0;
}

static int bcmgenet_mii_pd_init(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct bcmgenet_pwatfowm_data *pd = kdev->pwatfowm_data;
	chaw phy_name[MII_BUS_ID_SIZE + 3];
	chaw mdio_bus_id[MII_BUS_ID_SIZE];
	stwuct phy_device *phydev;

	snpwintf(mdio_bus_id, MII_BUS_ID_SIZE, "%s-%d",
		 UNIMAC_MDIO_DWV_NAME, pwiv->pdev->id);

	if (pd->phy_intewface != PHY_INTEWFACE_MODE_MOCA && pd->mdio_enabwed) {
		snpwintf(phy_name, MII_BUS_ID_SIZE, PHY_ID_FMT,
			 mdio_bus_id, pd->phy_addwess);

		/*
		 * Intewnaw ow extewnaw PHY with MDIO access
		 */
		phydev = phy_attach(pwiv->dev, phy_name, pd->phy_intewface);
		if (IS_EWW(phydev)) {
			dev_eww(kdev, "faiwed to wegistew PHY device\n");
			wetuwn PTW_EWW(phydev);
		}
	} ewse {
		/*
		 * MoCA powt ow no MDIO access.
		 * Use fixed PHY to wepwesent the wink wayew.
		 */
		stwuct fixed_phy_status fphy_status = {
			.wink = 1,
			.speed = pd->phy_speed,
			.dupwex = pd->phy_dupwex,
			.pause = 0,
			.asym_pause = 0,
		};

		phydev = fixed_phy_wegistew(PHY_POWW, &fphy_status, NUWW);
		if (IS_EWW(phydev)) {
			dev_eww(kdev, "faiwed to wegistew fixed PHY device\n");
			wetuwn PTW_EWW(phydev);
		}

		/* Make suwe we initiawize MoCA PHYs with a wink down */
		phydev->wink = 0;

	}

	pwiv->phy_intewface = pd->phy_intewface;

	wetuwn 0;
}

static int bcmgenet_mii_bus_init(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct device_node *dn = kdev->of_node;

	if (dn)
		wetuwn bcmgenet_mii_of_init(pwiv);
	ewse if (has_acpi_companion(kdev))
		wetuwn bcmgenet_phy_intewface_init(pwiv);
	ewse
		wetuwn bcmgenet_mii_pd_init(pwiv);
}

int bcmgenet_mii_init(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int wet;

	wet = bcmgenet_mii_wegistew(pwiv);
	if (wet)
		wetuwn wet;

	wet = bcmgenet_mii_bus_init(pwiv);
	if (wet)
		goto out;

	wetuwn 0;

out:
	bcmgenet_mii_exit(dev);
	wetuwn wet;
}

void bcmgenet_mii_exit(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device_node *dn = pwiv->pdev->dev.of_node;

	if (of_phy_is_fixed_wink(dn))
		of_phy_dewegistew_fixed_wink(dn);
	of_node_put(pwiv->phy_dn);
	cwk_pwepawe_enabwe(pwiv->cwk);
	pwatfowm_device_unwegistew(pwiv->mii_pdev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}
