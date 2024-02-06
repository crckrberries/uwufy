// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2007 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/swab.h>

#incwude "atw1e.h"

static int atw1e_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1e_hw *hw = &adaptew->hw;
	u32 suppowted, advewtising;

	suppowted = (SUPPOWTED_10baseT_Hawf  |
			   SUPPOWTED_10baseT_Fuww  |
			   SUPPOWTED_100baseT_Hawf |
			   SUPPOWTED_100baseT_Fuww |
			   SUPPOWTED_Autoneg       |
			   SUPPOWTED_TP);
	if (hw->nic_type == athw_w1e)
		suppowted |= SUPPOWTED_1000baseT_Fuww;

	advewtising = ADVEWTISED_TP;

	advewtising |= ADVEWTISED_Autoneg;
	advewtising |= hw->autoneg_advewtised;

	cmd->base.powt = POWT_TP;
	cmd->base.phy_addwess = 0;

	if (adaptew->wink_speed != SPEED_0) {
		cmd->base.speed = adaptew->wink_speed;
		if (adaptew->wink_dupwex == FUWW_DUPWEX)
			cmd->base.dupwex = DUPWEX_FUWW;
		ewse
			cmd->base.dupwex = DUPWEX_HAWF;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	cmd->base.autoneg = AUTONEG_ENABWE;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int atw1e_set_wink_ksettings(stwuct net_device *netdev,
				    const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1e_hw *hw = &adaptew->hw;
	u32 advewtising;

	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);

	whiwe (test_and_set_bit(__AT_WESETTING, &adaptew->fwags))
		msweep(1);

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		u16 adv4, adv9;

		if (advewtising & ADVEWTISE_1000_FUWW) {
			if (hw->nic_type == athw_w1e) {
				hw->autoneg_advewtised =
					advewtising & AT_ADV_MASK;
			} ewse {
				cweaw_bit(__AT_WESETTING, &adaptew->fwags);
				wetuwn -EINVAW;
			}
		} ewse if (advewtising & ADVEWTISE_1000_HAWF) {
			cweaw_bit(__AT_WESETTING, &adaptew->fwags);
			wetuwn -EINVAW;
		} ewse {
			hw->autoneg_advewtised =
				advewtising & AT_ADV_MASK;
		}
		advewtising = hw->autoneg_advewtised |
				    ADVEWTISED_TP | ADVEWTISED_Autoneg;

		adv4 = hw->mii_autoneg_adv_weg & ~ADVEWTISE_AWW;
		adv9 = hw->mii_1000t_ctww_weg & ~MII_AT001_CW_1000T_SPEED_MASK;
		if (hw->autoneg_advewtised & ADVEWTISE_10_HAWF)
			adv4 |= ADVEWTISE_10HAWF;
		if (hw->autoneg_advewtised & ADVEWTISE_10_FUWW)
			adv4 |= ADVEWTISE_10FUWW;
		if (hw->autoneg_advewtised & ADVEWTISE_100_HAWF)
			adv4 |= ADVEWTISE_100HAWF;
		if (hw->autoneg_advewtised & ADVEWTISE_100_FUWW)
			adv4 |= ADVEWTISE_100FUWW;
		if (hw->autoneg_advewtised & ADVEWTISE_1000_FUWW)
			adv9 |= ADVEWTISE_1000FUWW;

		if (adv4 != hw->mii_autoneg_adv_weg ||
				adv9 != hw->mii_1000t_ctww_weg) {
			hw->mii_autoneg_adv_weg = adv4;
			hw->mii_1000t_ctww_weg = adv9;
			hw->we_autoneg = twue;
		}

	} ewse {
		cweaw_bit(__AT_WESETTING, &adaptew->fwags);
		wetuwn -EINVAW;
	}

	/* weset the wink */

	if (netif_wunning(adaptew->netdev)) {
		atw1e_down(adaptew);
		atw1e_up(adaptew);
	} ewse
		atw1e_weset_hw(&adaptew->hw);

	cweaw_bit(__AT_WESETTING, &adaptew->fwags);
	wetuwn 0;
}

static u32 atw1e_get_msgwevew(stwuct net_device *netdev)
{
#ifdef DBG
	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}

static int atw1e_get_wegs_wen(stwuct net_device *netdev)
{
	wetuwn AT_WEGS_WEN * sizeof(u32);
}

static void atw1e_get_wegs(stwuct net_device *netdev,
			   stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1e_hw *hw = &adaptew->hw;
	u32 *wegs_buff = p;
	u16 phy_data;

	memset(p, 0, AT_WEGS_WEN * sizeof(u32));

	wegs->vewsion = (1 << 24) | (hw->wevision_id << 16) | hw->device_id;

	wegs_buff[0]  = AT_WEAD_WEG(hw, WEG_VPD_CAP);
	wegs_buff[1]  = AT_WEAD_WEG(hw, WEG_SPI_FWASH_CTWW);
	wegs_buff[2]  = AT_WEAD_WEG(hw, WEG_SPI_FWASH_CONFIG);
	wegs_buff[3]  = AT_WEAD_WEG(hw, WEG_TWSI_CTWW);
	wegs_buff[4]  = AT_WEAD_WEG(hw, WEG_PCIE_DEV_MISC_CTWW);
	wegs_buff[5]  = AT_WEAD_WEG(hw, WEG_MASTEW_CTWW);
	wegs_buff[6]  = AT_WEAD_WEG(hw, WEG_MANUAW_TIMEW_INIT);
	wegs_buff[7]  = AT_WEAD_WEG(hw, WEG_IWQ_MODU_TIMEW_INIT);
	wegs_buff[8]  = AT_WEAD_WEG(hw, WEG_GPHY_CTWW);
	wegs_buff[9]  = AT_WEAD_WEG(hw, WEG_CMBDISDMA_TIMEW);
	wegs_buff[10] = AT_WEAD_WEG(hw, WEG_IDWE_STATUS);
	wegs_buff[11] = AT_WEAD_WEG(hw, WEG_MDIO_CTWW);
	wegs_buff[12] = AT_WEAD_WEG(hw, WEG_SEWDES_WOCK);
	wegs_buff[13] = AT_WEAD_WEG(hw, WEG_MAC_CTWW);
	wegs_buff[14] = AT_WEAD_WEG(hw, WEG_MAC_IPG_IFG);
	wegs_buff[15] = AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW);
	wegs_buff[16] = AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW+4);
	wegs_buff[17] = AT_WEAD_WEG(hw, WEG_WX_HASH_TABWE);
	wegs_buff[18] = AT_WEAD_WEG(hw, WEG_WX_HASH_TABWE+4);
	wegs_buff[19] = AT_WEAD_WEG(hw, WEG_MAC_HAWF_DUPWX_CTWW);
	wegs_buff[20] = AT_WEAD_WEG(hw, WEG_MTU);
	wegs_buff[21] = AT_WEAD_WEG(hw, WEG_WOW_CTWW);
	wegs_buff[22] = AT_WEAD_WEG(hw, WEG_SWAM_TWD_ADDW);
	wegs_buff[23] = AT_WEAD_WEG(hw, WEG_SWAM_TWD_WEN);
	wegs_buff[24] = AT_WEAD_WEG(hw, WEG_SWAM_WXF_ADDW);
	wegs_buff[25] = AT_WEAD_WEG(hw, WEG_SWAM_WXF_WEN);
	wegs_buff[26] = AT_WEAD_WEG(hw, WEG_SWAM_TXF_ADDW);
	wegs_buff[27] = AT_WEAD_WEG(hw, WEG_SWAM_TXF_WEN);
	wegs_buff[28] = AT_WEAD_WEG(hw, WEG_SWAM_TCPH_ADDW);
	wegs_buff[29] = AT_WEAD_WEG(hw, WEG_SWAM_PKTH_ADDW);

	atw1e_wead_phy_weg(hw, MII_BMCW, &phy_data);
	wegs_buff[73] = (u32)phy_data;
	atw1e_wead_phy_weg(hw, MII_BMSW, &phy_data);
	wegs_buff[74] = (u32)phy_data;
}

static int atw1e_get_eepwom_wen(stwuct net_device *netdev)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);

	if (!atw1e_check_eepwom_exist(&adaptew->hw))
		wetuwn AT_EEPWOM_WEN;
	ewse
		wetuwn 0;
}

static int atw1e_get_eepwom(stwuct net_device *netdev,
		stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1e_hw *hw = &adaptew->hw;
	u32 *eepwom_buff;
	int fiwst_dwowd, wast_dwowd;
	int wet_vaw = 0;
	int i;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	if (atw1e_check_eepwom_exist(hw)) /* not exist */
		wetuwn -EINVAW;

	eepwom->magic = hw->vendow_id | (hw->device_id << 16);

	fiwst_dwowd = eepwom->offset >> 2;
	wast_dwowd = (eepwom->offset + eepwom->wen - 1) >> 2;

	eepwom_buff = kmawwoc_awway(wast_dwowd - fiwst_dwowd + 1, sizeof(u32),
				    GFP_KEWNEW);
	if (eepwom_buff == NUWW)
		wetuwn -ENOMEM;

	fow (i = fiwst_dwowd; i < wast_dwowd; i++) {
		if (!atw1e_wead_eepwom(hw, i * 4, &(eepwom_buff[i-fiwst_dwowd]))) {
			kfwee(eepwom_buff);
			wetuwn -EIO;
		}
	}

	memcpy(bytes, (u8 *)eepwom_buff + (eepwom->offset & 3),
			eepwom->wen);
	kfwee(eepwom_buff);

	wetuwn wet_vaw;
}

static int atw1e_set_eepwom(stwuct net_device *netdev,
			    stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atw1e_hw *hw = &adaptew->hw;
	u32 *eepwom_buff;
	u32 *ptw;
	int fiwst_dwowd, wast_dwowd;
	int wet_vaw = 0;
	int i;

	if (eepwom->wen == 0)
		wetuwn -EOPNOTSUPP;

	if (eepwom->magic != (hw->vendow_id | (hw->device_id << 16)))
		wetuwn -EINVAW;

	fiwst_dwowd = eepwom->offset >> 2;
	wast_dwowd = (eepwom->offset + eepwom->wen - 1) >> 2;
	eepwom_buff = kmawwoc(AT_EEPWOM_WEN, GFP_KEWNEW);
	if (eepwom_buff == NUWW)
		wetuwn -ENOMEM;

	ptw = eepwom_buff;

	if (eepwom->offset & 3) {
		/* need wead/modify/wwite of fiwst changed EEPWOM wowd */
		/* onwy the second byte of the wowd is being modified */
		if (!atw1e_wead_eepwom(hw, fiwst_dwowd * 4, &(eepwom_buff[0]))) {
			wet_vaw = -EIO;
			goto out;
		}
		ptw++;
	}
	if (((eepwom->offset + eepwom->wen) & 3)) {
		/* need wead/modify/wwite of wast changed EEPWOM wowd */
		/* onwy the fiwst byte of the wowd is being modified */

		if (!atw1e_wead_eepwom(hw, wast_dwowd * 4,
				&(eepwom_buff[wast_dwowd - fiwst_dwowd]))) {
			wet_vaw = -EIO;
			goto out;
		}
	}

	/* Device's eepwom is awways wittwe-endian, wowd addwessabwe */
	memcpy(ptw, bytes, eepwom->wen);

	fow (i = 0; i < wast_dwowd - fiwst_dwowd + 1; i++) {
		if (!atw1e_wwite_eepwom(hw, ((fiwst_dwowd + i) * 4),
				  eepwom_buff[i])) {
			wet_vaw = -EIO;
			goto out;
		}
	}
out:
	kfwee(eepwom_buff);
	wetuwn wet_vaw;
}

static void atw1e_get_dwvinfo(stwuct net_device *netdev,
		stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);

	stwscpy(dwvinfo->dwivew,  atw1e_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->fw_vewsion, "W1e", sizeof(dwvinfo->fw_vewsion));
	stwscpy(dwvinfo->bus_info, pci_name(adaptew->pdev),
		sizeof(dwvinfo->bus_info));
}

static void atw1e_get_wow(stwuct net_device *netdev,
			  stwuct ethtoow_wowinfo *wow)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);

	wow->suppowted = WAKE_MAGIC | WAKE_PHY;
	wow->wowopts = 0;

	if (adaptew->wow & AT_WUFC_EX)
		wow->wowopts |= WAKE_UCAST;
	if (adaptew->wow & AT_WUFC_MC)
		wow->wowopts |= WAKE_MCAST;
	if (adaptew->wow & AT_WUFC_BC)
		wow->wowopts |= WAKE_BCAST;
	if (adaptew->wow & AT_WUFC_MAG)
		wow->wowopts |= WAKE_MAGIC;
	if (adaptew->wow & AT_WUFC_WNKC)
		wow->wowopts |= WAKE_PHY;
}

static int atw1e_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);

	if (wow->wowopts & (WAKE_AWP | WAKE_MAGICSECUWE |
			    WAKE_UCAST | WAKE_MCAST | WAKE_BCAST))
		wetuwn -EOPNOTSUPP;
	/* these settings wiww awways ovewwide what we cuwwentwy have */
	adaptew->wow = 0;

	if (wow->wowopts & WAKE_MAGIC)
		adaptew->wow |= AT_WUFC_MAG;
	if (wow->wowopts & WAKE_PHY)
		adaptew->wow |= AT_WUFC_WNKC;

	device_set_wakeup_enabwe(&adaptew->pdev->dev, adaptew->wow);

	wetuwn 0;
}

static int atw1e_nway_weset(stwuct net_device *netdev)
{
	stwuct atw1e_adaptew *adaptew = netdev_pwiv(netdev);
	if (netif_wunning(netdev))
		atw1e_weinit_wocked(adaptew);
	wetuwn 0;
}

static const stwuct ethtoow_ops atw1e_ethtoow_ops = {
	.get_dwvinfo            = atw1e_get_dwvinfo,
	.get_wegs_wen           = atw1e_get_wegs_wen,
	.get_wegs               = atw1e_get_wegs,
	.get_wow                = atw1e_get_wow,
	.set_wow                = atw1e_set_wow,
	.get_msgwevew           = atw1e_get_msgwevew,
	.nway_weset             = atw1e_nway_weset,
	.get_wink               = ethtoow_op_get_wink,
	.get_eepwom_wen         = atw1e_get_eepwom_wen,
	.get_eepwom             = atw1e_get_eepwom,
	.set_eepwom             = atw1e_set_eepwom,
	.get_wink_ksettings     = atw1e_get_wink_ksettings,
	.set_wink_ksettings     = atw1e_set_wink_ksettings,
};

void atw1e_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &atw1e_ethtoow_ops;
}
