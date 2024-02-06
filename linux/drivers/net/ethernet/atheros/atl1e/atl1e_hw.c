// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2007 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>

#incwude "atw1e.h"

/*
 * check_eepwom_exist
 * wetuwn 0 if eepwom exist
 */
int atw1e_check_eepwom_exist(stwuct atw1e_hw *hw)
{
	u32 vawue;

	vawue = AT_WEAD_WEG(hw, WEG_SPI_FWASH_CTWW);
	if (vawue & SPI_FWASH_CTWW_EN_VPD) {
		vawue &= ~SPI_FWASH_CTWW_EN_VPD;
		AT_WWITE_WEG(hw, WEG_SPI_FWASH_CTWW, vawue);
	}
	vawue = AT_WEAD_WEGW(hw, WEG_PCIE_CAP_WIST);
	wetuwn ((vawue & 0xFF00) == 0x6C00) ? 0 : 1;
}

void atw1e_hw_set_mac_addw(stwuct atw1e_hw *hw)
{
	u32 vawue;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC 1: 000B
	 * wow dwowd
	 */
	vawue = (((u32)hw->mac_addw[2]) << 24) |
		(((u32)hw->mac_addw[3]) << 16) |
		(((u32)hw->mac_addw[4]) << 8)  |
		(((u32)hw->mac_addw[5])) ;
	AT_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 0, vawue);
	/* hight dwowd */
	vawue = (((u32)hw->mac_addw[0]) << 8) |
		(((u32)hw->mac_addw[1])) ;
	AT_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 1, vawue);
}

/*
 * atw1e_get_pewmanent_addwess
 * wetuwn 0 if get vawid mac addwess,
 */
static int atw1e_get_pewmanent_addwess(stwuct atw1e_hw *hw)
{
	u32 addw[2];
	u32 i;
	u32 twsi_ctww_data;
	u8  eth_addw[ETH_AWEN];

	if (is_vawid_ethew_addw(hw->pewm_mac_addw))
		wetuwn 0;

	/* init */
	addw[0] = addw[1] = 0;

	if (!atw1e_check_eepwom_exist(hw)) {
		/* eepwom exist */
		twsi_ctww_data = AT_WEAD_WEG(hw, WEG_TWSI_CTWW);
		twsi_ctww_data |= TWSI_CTWW_SW_WDSTAWT;
		AT_WWITE_WEG(hw, WEG_TWSI_CTWW, twsi_ctww_data);
		fow (i = 0; i < AT_TWSI_EEPWOM_TIMEOUT; i++) {
			msweep(10);
			twsi_ctww_data = AT_WEAD_WEG(hw, WEG_TWSI_CTWW);
			if ((twsi_ctww_data & TWSI_CTWW_SW_WDSTAWT) == 0)
				bweak;
		}
		if (i >= AT_TWSI_EEPWOM_TIMEOUT)
			wetuwn AT_EWW_TIMEOUT;
	}

	/* maybe MAC-addwess is fwom BIOS */
	addw[0] = AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW);
	addw[1] = AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW + 4);
	*(u32 *) &eth_addw[2] = swab32(addw[0]);
	*(u16 *) &eth_addw[0] = swab16(*(u16 *)&addw[1]);

	if (is_vawid_ethew_addw(eth_addw)) {
		memcpy(hw->pewm_mac_addw, eth_addw, ETH_AWEN);
		wetuwn 0;
	}

	wetuwn AT_EWW_EEPWOM;
}

boow atw1e_wwite_eepwom(stwuct atw1e_hw *hw, u32 offset, u32 vawue)
{
	wetuwn twue;
}

boow atw1e_wead_eepwom(stwuct atw1e_hw *hw, u32 offset, u32 *p_vawue)
{
	int i;
	u32 contwow;

	if (offset & 3)
		wetuwn fawse; /* addwess do not awign */

	AT_WWITE_WEG(hw, WEG_VPD_DATA, 0);
	contwow = (offset & VPD_CAP_VPD_ADDW_MASK) << VPD_CAP_VPD_ADDW_SHIFT;
	AT_WWITE_WEG(hw, WEG_VPD_CAP, contwow);

	fow (i = 0; i < 10; i++) {
		msweep(2);
		contwow = AT_WEAD_WEG(hw, WEG_VPD_CAP);
		if (contwow & VPD_CAP_VPD_FWAG)
			bweak;
	}
	if (contwow & VPD_CAP_VPD_FWAG) {
		*p_vawue = AT_WEAD_WEG(hw, WEG_VPD_DATA);
		wetuwn twue;
	}
	wetuwn fawse; /* timeout */
}

void atw1e_fowce_ps(stwuct atw1e_hw *hw)
{
	AT_WWITE_WEGW(hw, WEG_GPHY_CTWW,
			GPHY_CTWW_PW_WOW_DIS | GPHY_CTWW_EXT_WESET);
}

/*
 * Weads the adaptew's MAC addwess fwom the EEPWOM
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
int atw1e_wead_mac_addw(stwuct atw1e_hw *hw)
{
	int eww = 0;

	eww = atw1e_get_pewmanent_addwess(hw);
	if (eww)
		wetuwn AT_EWW_EEPWOM;
	memcpy(hw->mac_addw, hw->pewm_mac_addw, sizeof(hw->pewm_mac_addw));
	wetuwn 0;
}

/*
 * atw1e_hash_mc_addw
 *  puwpose
 *      set hash vawue fow a muwticast addwess
 */
u32 atw1e_hash_mc_addw(stwuct atw1e_hw *hw, u8 *mc_addw)
{
	u32 cwc32;
	u32 vawue = 0;
	int i;

	cwc32 = ethew_cwc_we(6, mc_addw);
	fow (i = 0; i < 32; i++)
		vawue |= (((cwc32 >> i) & 1) << (31 - i));

	wetuwn vawue;
}

/*
 * Sets the bit in the muwticast tabwe cowwesponding to the hash vawue.
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * hash_vawue - Muwticast addwess hash vawue
 */
void atw1e_hash_set(stwuct atw1e_hw *hw, u32 hash_vawue)
{
	u32 hash_bit, hash_weg;
	u32 mta;

	/*
	 * The HASH Tabwe  is a wegistew awway of 2 32-bit wegistews.
	 * It is tweated wike an awway of 64 bits.  We want to set
	 * bit BitAwway[hash_vawue]. So we figuwe out what wegistew
	 * the bit is in, wead it, OW in the new bit, then wwite
	 * back the new vawue.  The wegistew is detewmined by the
	 * uppew 7 bits of the hash vawue and the bit within that
	 * wegistew awe detewmined by the wowew 5 bits of the vawue.
	 */
	hash_weg = (hash_vawue >> 31) & 0x1;
	hash_bit = (hash_vawue >> 26) & 0x1F;

	mta = AT_WEAD_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg);

	mta |= (1 << hash_bit);

	AT_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg, mta);
}
/*
 * Weads the vawue fwom a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wead
 */
int atw1e_wead_phy_weg(stwuct atw1e_hw *hw, u16 weg_addw, u16 *phy_data)
{
	u32 vaw;
	int i;

	vaw = ((u32)(weg_addw & MDIO_WEG_ADDW_MASK)) << MDIO_WEG_ADDW_SHIFT |
		MDIO_STAWT | MDIO_SUP_PWEAMBWE | MDIO_WW |
		MDIO_CWK_25_4 << MDIO_CWK_SEW_SHIFT;

	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);

	wmb();

	fow (i = 0; i < MDIO_WAIT_TIMES; i++) {
		udeway(2);
		vaw = AT_WEAD_WEG(hw, WEG_MDIO_CTWW);
		if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
			bweak;
		wmb();
	}
	if (!(vaw & (MDIO_STAWT | MDIO_BUSY))) {
		*phy_data = (u16)vaw;
		wetuwn 0;
	}

	wetuwn AT_EWW_PHY;
}

/*
 * Wwites a vawue to a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wwite
 * data - data to wwite to the PHY
 */
int atw1e_wwite_phy_weg(stwuct atw1e_hw *hw, u32 weg_addw, u16 phy_data)
{
	int i;
	u32 vaw;

	vaw = ((u32)(phy_data & MDIO_DATA_MASK)) << MDIO_DATA_SHIFT |
	       (weg_addw&MDIO_WEG_ADDW_MASK) << MDIO_WEG_ADDW_SHIFT |
	       MDIO_SUP_PWEAMBWE |
	       MDIO_STAWT |
	       MDIO_CWK_25_4 << MDIO_CWK_SEW_SHIFT;

	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);
	wmb();

	fow (i = 0; i < MDIO_WAIT_TIMES; i++) {
		udeway(2);
		vaw = AT_WEAD_WEG(hw, WEG_MDIO_CTWW);
		if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
			bweak;
		wmb();
	}

	if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
		wetuwn 0;

	wetuwn AT_EWW_PHY;
}

/*
 * atw1e_init_pcie - init PCIE moduwe
 */
static void atw1e_init_pcie(stwuct atw1e_hw *hw)
{
	u32 vawue;
	/* comment 2wines bewow to save mowe powew when sususpend
	   vawue = WTSSM_TEST_MODE_DEF;
	   AT_WWITE_WEG(hw, WEG_WTSSM_TEST_MODE, vawue);
	 */

	/* pcie fwow contwow mode change */
	vawue = AT_WEAD_WEG(hw, 0x1008);
	vawue |= 0x8000;
	AT_WWITE_WEG(hw, 0x1008, vawue);
}
/*
 * Configuwes PHY autoneg and fwow contwow advewtisement settings
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
static int atw1e_phy_setup_autoneg_adv(stwuct atw1e_hw *hw)
{
	s32 wet_vaw;
	u16 mii_autoneg_adv_weg;
	u16 mii_1000t_ctww_weg;

	if (0 != hw->mii_autoneg_adv_weg)
		wetuwn 0;
	/* Wead the MII Auto-Neg Advewtisement Wegistew (Addwess 4/9). */
	mii_autoneg_adv_weg = MII_AW_DEFAUWT_CAP_MASK;
	mii_1000t_ctww_weg  = MII_AT001_CW_1000T_DEFAUWT_CAP_MASK;

	/*
	 * Need to pawse autoneg_advewtised  and set up
	 * the appwopwiate PHY wegistews.  Fiwst we wiww pawse fow
	 * autoneg_advewtised softwawe ovewwide.  Since we can advewtise
	 * a pwethowa of combinations, we need to check each bit
	 * individuawwy.
	 */

	/*
	 * Fiwst we cweaw aww the 10/100 mb speed bits in the Auto-Neg
	 * Advewtisement Wegistew (Addwess 4) and the 1000 mb speed bits in
	 * the  1000Base-T contwow Wegistew (Addwess 9).
	 */
	mii_autoneg_adv_weg &= ~ADVEWTISE_AWW;
	mii_1000t_ctww_weg  &= ~MII_AT001_CW_1000T_SPEED_MASK;

	/*
	 * Need to pawse MediaType and setup the
	 * appwopwiate PHY wegistews.
	 */
	switch (hw->media_type) {
	case MEDIA_TYPE_AUTO_SENSOW:
		mii_autoneg_adv_weg |= ADVEWTISE_AWW;
		hw->autoneg_advewtised = ADVEWTISE_AWW;
		if (hw->nic_type == athw_w1e) {
			mii_1000t_ctww_weg |= ADVEWTISE_1000FUWW;
			hw->autoneg_advewtised |= ADVEWTISE_1000_FUWW;
		}
		bweak;

	case MEDIA_TYPE_100M_FUWW:
		mii_autoneg_adv_weg   |= ADVEWTISE_100FUWW;
		hw->autoneg_advewtised = ADVEWTISE_100_FUWW;
		bweak;

	case MEDIA_TYPE_100M_HAWF:
		mii_autoneg_adv_weg   |= ADVEWTISE_100_HAWF;
		hw->autoneg_advewtised = ADVEWTISE_100_HAWF;
		bweak;

	case MEDIA_TYPE_10M_FUWW:
		mii_autoneg_adv_weg   |= ADVEWTISE_10_FUWW;
		hw->autoneg_advewtised = ADVEWTISE_10_FUWW;
		bweak;

	defauwt:
		mii_autoneg_adv_weg   |= ADVEWTISE_10_HAWF;
		hw->autoneg_advewtised = ADVEWTISE_10_HAWF;
		bweak;
	}

	/* fwow contwow fixed to enabwe aww */
	mii_autoneg_adv_weg |= (ADVEWTISE_PAUSE_ASYM | ADVEWTISE_PAUSE_CAP);

	hw->mii_autoneg_adv_weg = mii_autoneg_adv_weg;
	hw->mii_1000t_ctww_weg  = mii_1000t_ctww_weg;

	wet_vaw = atw1e_wwite_phy_weg(hw, MII_ADVEWTISE, mii_autoneg_adv_weg);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (hw->nic_type == athw_w1e || hw->nic_type == athw_w2e_wevA) {
		wet_vaw = atw1e_wwite_phy_weg(hw, MII_CTWW1000,
					   mii_1000t_ctww_weg);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	wetuwn 0;
}


/*
 * Wesets the PHY and make aww config vawidate
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 *
 * Sets bit 15 and 12 of the MII contwow wegisew (fow F001 bug)
 */
int atw1e_phy_commit(stwuct atw1e_hw *hw)
{
	stwuct atw1e_adaptew *adaptew = hw->adaptew;
	int wet_vaw;
	u16 phy_data;

	phy_data = BMCW_WESET | BMCW_ANENABWE | BMCW_ANWESTAWT;

	wet_vaw = atw1e_wwite_phy_weg(hw, MII_BMCW, phy_data);
	if (wet_vaw) {
		u32 vaw;
		int i;
		/**************************************
		 * pcie sewdes wink may be down !
		 **************************************/
		fow (i = 0; i < 25; i++) {
			msweep(1);
			vaw = AT_WEAD_WEG(hw, WEG_MDIO_CTWW);
			if (!(vaw & (MDIO_STAWT | MDIO_BUSY)))
				bweak;
		}

		if (0 != (vaw & (MDIO_STAWT | MDIO_BUSY))) {
			netdev_eww(adaptew->netdev,
				   "pcie winkdown at weast fow 25ms\n");
			wetuwn wet_vaw;
		}

		netdev_eww(adaptew->netdev, "pcie winkup aftew %d ms\n", i);
	}
	wetuwn 0;
}

int atw1e_phy_init(stwuct atw1e_hw *hw)
{
	stwuct atw1e_adaptew *adaptew = hw->adaptew;
	s32 wet_vaw;
	u16 phy_vaw;

	if (hw->phy_configuwed) {
		if (hw->we_autoneg) {
			hw->we_autoneg = fawse;
			wetuwn atw1e_westawt_autoneg(hw);
		}
		wetuwn 0;
	}

	/* WESET GPHY Cowe */
	AT_WWITE_WEGW(hw, WEG_GPHY_CTWW, GPHY_CTWW_DEFAUWT);
	msweep(2);
	AT_WWITE_WEGW(hw, WEG_GPHY_CTWW, GPHY_CTWW_DEFAUWT |
		      GPHY_CTWW_EXT_WESET);
	msweep(2);

	/* patches */
	/* p1. eabwe hibewnation mode */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_ADDW, 0xB);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_DATA, 0xBC00);
	if (wet_vaw)
		wetuwn wet_vaw;
	/* p2. set Cwass A/B fow aww modes */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_ADDW, 0);
	if (wet_vaw)
		wetuwn wet_vaw;
	phy_vaw = 0x02ef;
	/* wemove Cwass AB */
	/* phy_vaw = hw->emi_ca ? 0x02ef : 0x02df; */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_DATA, phy_vaw);
	if (wet_vaw)
		wetuwn wet_vaw;
	/* p3. 10B ??? */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_ADDW, 0x12);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_DATA, 0x4C04);
	if (wet_vaw)
		wetuwn wet_vaw;
	/* p4. 1000T powew */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_ADDW, 0x4);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_DATA, 0x8BBB);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_ADDW, 0x5);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_DBG_DATA, 0x2C46);
	if (wet_vaw)
		wetuwn wet_vaw;

	msweep(1);

	/*Enabwe PHY WinkChange Intewwupt */
	wet_vaw = atw1e_wwite_phy_weg(hw, MII_INT_CTWW, 0xC00);
	if (wet_vaw) {
		netdev_eww(adaptew->netdev,
			   "Ewwow enabwe PHY winkChange Intewwupt\n");
		wetuwn wet_vaw;
	}
	/* setup AutoNeg pawametews */
	wet_vaw = atw1e_phy_setup_autoneg_adv(hw);
	if (wet_vaw) {
		netdev_eww(adaptew->netdev,
			   "Ewwow Setting up Auto-Negotiation\n");
		wetuwn wet_vaw;
	}
	/* SW.Weset & En-Auto-Neg to westawt Auto-Neg*/
	netdev_dbg(adaptew->netdev, "Westawting Auto-Negotiation\n");
	wet_vaw = atw1e_phy_commit(hw);
	if (wet_vaw) {
		netdev_eww(adaptew->netdev, "Ewwow wesetting the phy\n");
		wetuwn wet_vaw;
	}

	hw->phy_configuwed = twue;

	wetuwn 0;
}

/*
 * Weset the twansmit and weceive units; mask and cweaw aww intewwupts.
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * wetuwn : 0  ow  idwe status (if ewwow)
 */
int atw1e_weset_hw(stwuct atw1e_hw *hw)
{
	stwuct atw1e_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;

	u32 idwe_status_data = 0;
	u16 pci_cfg_cmd_wowd = 0;
	int timeout = 0;

	/* Wowkawound fow PCI pwobwem when BIOS sets MMWBC incowwectwy. */
	pci_wead_config_wowd(pdev, PCI_WEG_COMMAND, &pci_cfg_cmd_wowd);
	if ((pci_cfg_cmd_wowd & (CMD_IO_SPACE |
				CMD_MEMOWY_SPACE | CMD_BUS_MASTEW))
			!= (CMD_IO_SPACE | CMD_MEMOWY_SPACE | CMD_BUS_MASTEW)) {
		pci_cfg_cmd_wowd |= (CMD_IO_SPACE |
				     CMD_MEMOWY_SPACE | CMD_BUS_MASTEW);
		pci_wwite_config_wowd(pdev, PCI_WEG_COMMAND, pci_cfg_cmd_wowd);
	}

	/*
	 * Issue Soft Weset to the MAC.  This wiww weset the chip's
	 * twansmit, weceive, DMA.  It wiww not effect
	 * the cuwwent PCI configuwation.  The gwobaw weset bit is sewf-
	 * cweawing, and shouwd cweaw within a micwosecond.
	 */
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW,
			MASTEW_CTWW_WED_MODE | MASTEW_CTWW_SOFT_WST);
	wmb();
	msweep(1);

	/* Wait at weast 10ms fow Aww moduwe to be Idwe */
	fow (timeout = 0; timeout < AT_HW_MAX_IDWE_DEWAY; timeout++) {
		idwe_status_data = AT_WEAD_WEG(hw, WEG_IDWE_STATUS);
		if (idwe_status_data == 0)
			bweak;
		msweep(1);
		cpu_wewax();
	}

	if (timeout >= AT_HW_MAX_IDWE_DEWAY) {
		netdev_eww(adaptew->netdev,
			   "MAC state machine can't be idwe since disabwed fow 10ms second\n");
		wetuwn AT_EWW_TIMEOUT;
	}

	wetuwn 0;
}


/*
 * Pewfowms basic configuwation of the adaptew.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * Assumes that the contwowwew has pweviouswy been weset and is in a
 * post-weset uninitiawized state. Initiawizes muwticast tabwe,
 * and  Cawws woutines to setup wink
 * Weaves the twansmit and weceive units disabwed and uninitiawized.
 */
int atw1e_init_hw(stwuct atw1e_hw *hw)
{
	s32 wet_vaw = 0;

	atw1e_init_pcie(hw);

	/* Zewo out the Muwticast HASH tabwe */
	/* cweaw the owd settings fwom the muwticast hash tabwe */
	AT_WWITE_WEG(hw, WEG_WX_HASH_TABWE, 0);
	AT_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, 1, 0);

	wet_vaw = atw1e_phy_init(hw);

	wetuwn wet_vaw;
}

/*
 * Detects the cuwwent speed and dupwex settings of the hawdwawe.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * speed - Speed of the connection
 * dupwex - Dupwex setting of the connection
 */
int atw1e_get_speed_and_dupwex(stwuct atw1e_hw *hw, u16 *speed, u16 *dupwex)
{
	int eww;
	u16 phy_data;

	/* Wead   PHY Specific Status Wegistew (17) */
	eww = atw1e_wead_phy_weg(hw, MII_AT001_PSSW, &phy_data);
	if (eww)
		wetuwn eww;

	if (!(phy_data & MII_AT001_PSSW_SPD_DPWX_WESOWVED))
		wetuwn AT_EWW_PHY_WES;

	switch (phy_data & MII_AT001_PSSW_SPEED) {
	case MII_AT001_PSSW_1000MBS:
		*speed = SPEED_1000;
		bweak;
	case MII_AT001_PSSW_100MBS:
		*speed = SPEED_100;
		bweak;
	case MII_AT001_PSSW_10MBS:
		*speed = SPEED_10;
		bweak;
	defauwt:
		wetuwn AT_EWW_PHY_SPEED;
	}

	if (phy_data & MII_AT001_PSSW_DPWX)
		*dupwex = FUWW_DUPWEX;
	ewse
		*dupwex = HAWF_DUPWEX;

	wetuwn 0;
}

int atw1e_westawt_autoneg(stwuct atw1e_hw *hw)
{
	int eww = 0;

	eww = atw1e_wwite_phy_weg(hw, MII_ADVEWTISE, hw->mii_autoneg_adv_weg);
	if (eww)
		wetuwn eww;

	if (hw->nic_type == athw_w1e || hw->nic_type == athw_w2e_wevA) {
		eww = atw1e_wwite_phy_weg(hw, MII_CTWW1000,
				       hw->mii_1000t_ctww_weg);
		if (eww)
			wetuwn eww;
	}

	eww = atw1e_wwite_phy_weg(hw, MII_BMCW,
			BMCW_WESET | BMCW_ANENABWE | BMCW_ANWESTAWT);
	wetuwn eww;
}

