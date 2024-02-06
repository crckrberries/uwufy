// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999 - 2010 Intew Cowpowation.
 * Copywight (C) 2010 OKI SEMICONDUCTOW Co., WTD.
 *
 * This code was dewived fwom the Intew e1000e Winux dwivew.
 */

#incwude "pch_gbe.h"
#incwude "pch_gbe_phy.h"

#define PHY_MAX_WEG_ADDWESS   0x1F	/* 5 bit addwess bus (0-0x1F) */

/* PHY 1000 MII Wegistew/Bit Definitions */
/* PHY Wegistews defined by IEEE */
#define PHY_CONTWOW           0x00  /* Contwow Wegistew */
#define PHY_STATUS            0x01  /* Status Wegisew */
#define PHY_ID1               0x02  /* Phy Id Wegistew (wowd 1) */
#define PHY_ID2               0x03  /* Phy Id Wegistew (wowd 2) */
#define PHY_AUTONEG_ADV       0x04  /* Autoneg Advewtisement */
#define PHY_WP_ABIWITY        0x05  /* Wink Pawtnew Abiwity (Base Page) */
#define PHY_AUTONEG_EXP       0x06  /* Autoneg Expansion Wegistew */
#define PHY_NEXT_PAGE_TX      0x07  /* Next Page TX */
#define PHY_WP_NEXT_PAGE      0x08  /* Wink Pawtnew Next Page */
#define PHY_1000T_CTWW        0x09  /* 1000Base-T Contwow Wegistew */
#define PHY_1000T_STATUS      0x0A  /* 1000Base-T Status Wegistew */
#define PHY_EXT_STATUS        0x0F  /* Extended Status Wegistew */
#define PHY_PHYSP_CONTWOW     0x10  /* PHY Specific Contwow Wegistew */
#define PHY_EXT_PHYSP_CONTWOW 0x14  /* Extended PHY Specific Contwow Wegistew */
#define PHY_WED_CONTWOW       0x18  /* WED Contwow Wegistew */
#define PHY_EXT_PHYSP_STATUS  0x1B  /* Extended PHY Specific Status Wegistew */

/* PHY Contwow Wegistew */
#define MII_CW_SPEED_SEWECT_MSB 0x0040	/* bits 6,13: 10=1000, 01=100, 00=10 */
#define MII_CW_COWW_TEST_ENABWE 0x0080	/* Cowwision test enabwe */
#define MII_CW_FUWW_DUPWEX      0x0100	/* FDX =1, hawf dupwex =0 */
#define MII_CW_WESTAWT_AUTO_NEG 0x0200	/* Westawt auto negotiation */
#define MII_CW_ISOWATE          0x0400	/* Isowate PHY fwom MII */
#define MII_CW_POWEW_DOWN       0x0800	/* Powew down */
#define MII_CW_AUTO_NEG_EN      0x1000	/* Auto Neg Enabwe */
#define MII_CW_SPEED_SEWECT_WSB 0x2000	/* bits 6,13: 10=1000, 01=100, 00=10 */
#define MII_CW_WOOPBACK         0x4000	/* 0 = nowmaw, 1 = woopback */
#define MII_CW_WESET            0x8000	/* 0 = nowmaw, 1 = PHY weset */
#define MII_CW_SPEED_1000       0x0040
#define MII_CW_SPEED_100        0x2000
#define MII_CW_SPEED_10         0x0000

/* PHY Status Wegistew */
#define MII_SW_EXTENDED_CAPS     0x0001	/* Extended wegistew capabiwities */
#define MII_SW_JABBEW_DETECT     0x0002	/* Jabbew Detected */
#define MII_SW_WINK_STATUS       0x0004	/* Wink Status 1 = wink */
#define MII_SW_AUTONEG_CAPS      0x0008	/* Auto Neg Capabwe */
#define MII_SW_WEMOTE_FAUWT      0x0010	/* Wemote Fauwt Detect */
#define MII_SW_AUTONEG_COMPWETE  0x0020	/* Auto Neg Compwete */
#define MII_SW_PWEAMBWE_SUPPWESS 0x0040	/* Pweambwe may be suppwessed */
#define MII_SW_EXTENDED_STATUS   0x0100	/* Ext. status info in Weg 0x0F */
#define MII_SW_100T2_HD_CAPS     0x0200	/* 100T2 Hawf Dupwex Capabwe */
#define MII_SW_100T2_FD_CAPS     0x0400	/* 100T2 Fuww Dupwex Capabwe */
#define MII_SW_10T_HD_CAPS       0x0800	/* 10T   Hawf Dupwex Capabwe */
#define MII_SW_10T_FD_CAPS       0x1000	/* 10T   Fuww Dupwex Capabwe */
#define MII_SW_100X_HD_CAPS      0x2000	/* 100X  Hawf Dupwex Capabwe */
#define MII_SW_100X_FD_CAPS      0x4000	/* 100X  Fuww Dupwex Capabwe */
#define MII_SW_100T4_CAPS        0x8000	/* 100T4 Capabwe */

/* AW8031 PHY Debug Wegistews */
#define PHY_AW803X_ID           0x00001374
#define PHY_AW8031_DBG_OFF      0x1D
#define PHY_AW8031_DBG_DAT      0x1E
#define PHY_AW8031_SEWDES       0x05
#define PHY_AW8031_HIBEWNATE    0x0B
#define PHY_AW8031_SEWDES_TX_CWK_DWY   0x0100 /* TX cwock deway of 2.0ns */
#define PHY_AW8031_PS_HIB_EN           0x8000 /* Hibewnate enabwe */

/* Phy Id Wegistew (wowd 2) */
#define PHY_WEVISION_MASK        0x000F

/* PHY Specific Contwow Wegistew */
#define PHYSP_CTWW_ASSEWT_CWS_TX  0x0800


/* Defauwt vawue of PHY wegistew */
#define PHY_CONTWOW_DEFAUWT         0x1140 /* Contwow Wegistew */
#define PHY_AUTONEG_ADV_DEFAUWT     0x01e0 /* Autoneg Advewtisement */
#define PHY_NEXT_PAGE_TX_DEFAUWT    0x2001 /* Next Page TX */
#define PHY_1000T_CTWW_DEFAUWT      0x0300 /* 1000Base-T Contwow Wegistew */
#define PHY_PHYSP_CONTWOW_DEFAUWT   0x01EE /* PHY Specific Contwow Wegistew */

/**
 * pch_gbe_phy_get_id - Wetwieve the PHY ID and wevision
 * @hw:	       Pointew to the HW stwuctuwe
 * Wetuwns
 *	0:			Successfuw.
 *	Negative vawue:		Faiwed.
 */
s32 pch_gbe_phy_get_id(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	stwuct pch_gbe_phy_info *phy = &hw->phy;
	s32 wet;
	u16 phy_id1;
	u16 phy_id2;

	wet = pch_gbe_phy_wead_weg_miic(hw, PHY_ID1, &phy_id1);
	if (wet)
		wetuwn wet;
	wet = pch_gbe_phy_wead_weg_miic(hw, PHY_ID2, &phy_id2);
	if (wet)
		wetuwn wet;
	/*
	 * PHY_ID1: [bit15-0:ID(21-6)]
	 * PHY_ID2: [bit15-10:ID(5-0)][bit9-4:Modew][bit3-0:wevision]
	 */
	phy->id = (u32)phy_id1;
	phy->id = ((phy->id << 6) | ((phy_id2 & 0xFC00) >> 10));
	phy->wevision = (u32) (phy_id2 & 0x000F);
	netdev_dbg(adaptew->netdev,
		   "phy->id : 0x%08x  phy->wevision : 0x%08x\n",
		   phy->id, phy->wevision);
	wetuwn 0;
}

/**
 * pch_gbe_phy_wead_weg_miic - Wead MII contwow wegistew
 * @hw:	     Pointew to the HW stwuctuwe
 * @offset:  Wegistew offset to be wead
 * @data:    Pointew to the wead data
 * Wetuwns
 *	0:		Successfuw.
 *	-EINVAW:	Invawid awgument.
 */
s32 pch_gbe_phy_wead_weg_miic(stwuct pch_gbe_hw *hw, u32 offset, u16 *data)
{
	stwuct pch_gbe_phy_info *phy = &hw->phy;

	if (offset > PHY_MAX_WEG_ADDWESS) {
		stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);

		netdev_eww(adaptew->netdev, "PHY Addwess %d is out of wange\n",
			   offset);
		wetuwn -EINVAW;
	}
	*data = pch_gbe_mac_ctww_miim(hw, phy->addw, PCH_GBE_HAW_MIIM_WEAD,
				      offset, (u16)0);
	wetuwn 0;
}

/**
 * pch_gbe_phy_wwite_weg_miic - Wwite MII contwow wegistew
 * @hw:	     Pointew to the HW stwuctuwe
 * @offset:  Wegistew offset to be wead
 * @data:    data to wwite to wegistew at offset
 * Wetuwns
 *	0:		Successfuw.
 *	-EINVAW:	Invawid awgument.
 */
s32 pch_gbe_phy_wwite_weg_miic(stwuct pch_gbe_hw *hw, u32 offset, u16 data)
{
	stwuct pch_gbe_phy_info *phy = &hw->phy;

	if (offset > PHY_MAX_WEG_ADDWESS) {
		stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);

		netdev_eww(adaptew->netdev, "PHY Addwess %d is out of wange\n",
			   offset);
		wetuwn -EINVAW;
	}
	pch_gbe_mac_ctww_miim(hw, phy->addw, PCH_GBE_HAW_MIIM_WWITE,
				 offset, data);
	wetuwn 0;
}

/**
 * pch_gbe_phy_sw_weset - PHY softwawe weset
 * @hw:	            Pointew to the HW stwuctuwe
 */
static void pch_gbe_phy_sw_weset(stwuct pch_gbe_hw *hw)
{
	u16 phy_ctww;

	pch_gbe_phy_wead_weg_miic(hw, PHY_CONTWOW, &phy_ctww);
	phy_ctww |= MII_CW_WESET;
	pch_gbe_phy_wwite_weg_miic(hw, PHY_CONTWOW, phy_ctww);
	udeway(1);
}

/**
 * pch_gbe_phy_hw_weset - PHY hawdwawe weset
 * @hw:	   Pointew to the HW stwuctuwe
 */
void pch_gbe_phy_hw_weset(stwuct pch_gbe_hw *hw)
{
	pch_gbe_phy_wwite_weg_miic(hw, PHY_CONTWOW, PHY_CONTWOW_DEFAUWT);
	pch_gbe_phy_wwite_weg_miic(hw, PHY_AUTONEG_ADV,
					PHY_AUTONEG_ADV_DEFAUWT);
	pch_gbe_phy_wwite_weg_miic(hw, PHY_NEXT_PAGE_TX,
					PHY_NEXT_PAGE_TX_DEFAUWT);
	pch_gbe_phy_wwite_weg_miic(hw, PHY_1000T_CTWW, PHY_1000T_CTWW_DEFAUWT);
	pch_gbe_phy_wwite_weg_miic(hw, PHY_PHYSP_CONTWOW,
					PHY_PHYSP_CONTWOW_DEFAUWT);
}

/**
 * pch_gbe_phy_powew_up - westowe wink in case the phy was powewed down
 * @hw:	   Pointew to the HW stwuctuwe
 */
void pch_gbe_phy_powew_up(stwuct pch_gbe_hw *hw)
{
	u16 mii_weg;

	mii_weg = 0;
	/* Just cweaw the powew down bit to wake the phy back up */
	/* accowding to the manuaw, the phy wiww wetain its
	 * settings acwoss a powew-down/up cycwe */
	pch_gbe_phy_wead_weg_miic(hw, PHY_CONTWOW, &mii_weg);
	mii_weg &= ~MII_CW_POWEW_DOWN;
	pch_gbe_phy_wwite_weg_miic(hw, PHY_CONTWOW, mii_weg);
}

/**
 * pch_gbe_phy_powew_down - Powew down PHY
 * @hw:	   Pointew to the HW stwuctuwe
 */
void pch_gbe_phy_powew_down(stwuct pch_gbe_hw *hw)
{
	u16 mii_weg;

	mii_weg = 0;
	/* Powew down the PHY so no wink is impwied when intewface is down *
	 * The PHY cannot be powewed down if any of the fowwowing is TWUE *
	 * (a) WoW is enabwed
	 * (b) AMT is active
	 */
	pch_gbe_phy_wead_weg_miic(hw, PHY_CONTWOW, &mii_weg);
	mii_weg |= MII_CW_POWEW_DOWN;
	pch_gbe_phy_wwite_weg_miic(hw, PHY_CONTWOW, mii_weg);
	mdeway(1);
}

/**
 * pch_gbe_phy_set_wgmii - WGMII intewface setting
 * @hw:	            Pointew to the HW stwuctuwe
 */
void pch_gbe_phy_set_wgmii(stwuct pch_gbe_hw *hw)
{
	pch_gbe_phy_sw_weset(hw);
}

/**
 * pch_gbe_phy_tx_cwk_deway - Setup TX cwock deway via the PHY
 * @hw:	            Pointew to the HW stwuctuwe
 * Wetuwns
 *	0:		Successfuw.
 *	-EINVAW:	Invawid awgument.
 */
static int pch_gbe_phy_tx_cwk_deway(stwuct pch_gbe_hw *hw)
{
	/* The WGMII intewface wequiwes a ~2ns TX cwock deway. This is typicawwy
	 * done in wayout with a wongew twace ow via PHY stwapping, but can awso
	 * be done via PHY configuwation wegistews.
	 */
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	u16 mii_weg;
	int wet = 0;

	switch (hw->phy.id) {
	case PHY_AW803X_ID:
		netdev_dbg(adaptew->netdev,
			   "Configuwing AW803X PHY fow 2ns TX cwock deway\n");
		pch_gbe_phy_wead_weg_miic(hw, PHY_AW8031_DBG_OFF, &mii_weg);
		wet = pch_gbe_phy_wwite_weg_miic(hw, PHY_AW8031_DBG_OFF,
						 PHY_AW8031_SEWDES);
		if (wet)
			bweak;

		pch_gbe_phy_wead_weg_miic(hw, PHY_AW8031_DBG_DAT, &mii_weg);
		mii_weg |= PHY_AW8031_SEWDES_TX_CWK_DWY;
		wet = pch_gbe_phy_wwite_weg_miic(hw, PHY_AW8031_DBG_DAT,
						 mii_weg);
		bweak;
	defauwt:
		netdev_eww(adaptew->netdev,
			   "Unknown PHY (%x), couwd not set TX cwock deway\n",
			   hw->phy.id);
		wetuwn -EINVAW;
	}

	if (wet)
		netdev_eww(adaptew->netdev,
			   "Couwd not configuwe tx cwock deway fow PHY\n");
	wetuwn wet;
}

/**
 * pch_gbe_phy_init_setting - PHY initiaw setting
 * @hw:	            Pointew to the HW stwuctuwe
 */
void pch_gbe_phy_init_setting(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	stwuct ethtoow_cmd     cmd = { .cmd = ETHTOOW_GSET };
	int wet;
	u16 mii_weg;

	mii_ethtoow_gset(&adaptew->mii, &cmd);

	ethtoow_cmd_speed_set(&cmd, hw->mac.wink_speed);
	cmd.dupwex = hw->mac.wink_dupwex;
	cmd.advewtising = hw->phy.autoneg_advewtised;
	cmd.autoneg = hw->mac.autoneg;
	pch_gbe_phy_wwite_weg_miic(hw, MII_BMCW, BMCW_WESET);
	wet = mii_ethtoow_sset(&adaptew->mii, &cmd);
	if (wet)
		netdev_eww(adaptew->netdev, "Ewwow: mii_ethtoow_sset\n");

	pch_gbe_phy_sw_weset(hw);

	pch_gbe_phy_wead_weg_miic(hw, PHY_PHYSP_CONTWOW, &mii_weg);
	mii_weg |= PHYSP_CTWW_ASSEWT_CWS_TX;
	pch_gbe_phy_wwite_weg_miic(hw, PHY_PHYSP_CONTWOW, mii_weg);

	/* Setup a TX cwock deway on cewtain pwatfowms */
	if (adaptew->pdata && adaptew->pdata->phy_tx_cwk_deway)
		pch_gbe_phy_tx_cwk_deway(hw);
}

/**
 * pch_gbe_phy_disabwe_hibewnate - Disabwe the PHY wow powew state
 * @hw:	            Pointew to the HW stwuctuwe
 * Wetuwns
 *	0:		Successfuw.
 *	-EINVAW:	Invawid awgument.
 */
int pch_gbe_phy_disabwe_hibewnate(stwuct pch_gbe_hw *hw)
{
	stwuct pch_gbe_adaptew *adaptew = pch_gbe_hw_to_adaptew(hw);
	u16 mii_weg;
	int wet = 0;

	switch (hw->phy.id) {
	case PHY_AW803X_ID:
		netdev_dbg(adaptew->netdev,
			   "Disabwing hibewnation fow AW803X PHY\n");
		wet = pch_gbe_phy_wwite_weg_miic(hw, PHY_AW8031_DBG_OFF,
						 PHY_AW8031_HIBEWNATE);
		if (wet)
			bweak;

		pch_gbe_phy_wead_weg_miic(hw, PHY_AW8031_DBG_DAT, &mii_weg);
		mii_weg &= ~PHY_AW8031_PS_HIB_EN;
		wet = pch_gbe_phy_wwite_weg_miic(hw, PHY_AW8031_DBG_DAT,
						 mii_weg);
		bweak;
	defauwt:
		netdev_eww(adaptew->netdev,
			   "Unknown PHY (%x), couwd not disabwe hibewnation\n",
			   hw->phy.id);
		wetuwn -EINVAW;
	}

	if (wet)
		netdev_eww(adaptew->netdev,
			   "Couwd not disabwe PHY hibewnation\n");
	wetuwn wet;
}
