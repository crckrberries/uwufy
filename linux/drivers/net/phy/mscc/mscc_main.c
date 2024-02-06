// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Dwivew fow Micwosemi VSC85xx PHYs
 *
 * Authow: Nagawaju Wakkawaju
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2016 Micwosemi Cowpowation
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mdio.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <winux/netdevice.h>
#incwude <dt-bindings/net/mscc-phy-vsc8531.h>
#incwude "mscc_sewdes.h"
#incwude "mscc.h"

static const stwuct vsc85xx_hw_stat vsc85xx_hw_stats[] = {
	{
		.stwing	= "phy_weceive_ewwows",
		.weg	= MSCC_PHY_EWW_WX_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_fawse_cawwiew",
		.weg	= MSCC_PHY_EWW_FAWSE_CAWWIEW_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_cu_media_wink_disconnect",
		.weg	= MSCC_PHY_EWW_WINK_DISCONNECT_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_cu_media_cwc_good_count",
		.weg	= MSCC_PHY_CU_MEDIA_CWC_VAWID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= VAWID_CWC_CNT_CWC_MASK,
	}, {
		.stwing	= "phy_cu_media_cwc_ewwow_count",
		.weg	= MSCC_PHY_EXT_PHY_CNTW_4,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= EWW_CNT_MASK,
	},
};

static const stwuct vsc85xx_hw_stat vsc8584_hw_stats[] = {
	{
		.stwing	= "phy_weceive_ewwows",
		.weg	= MSCC_PHY_EWW_WX_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_fawse_cawwiew",
		.weg	= MSCC_PHY_EWW_FAWSE_CAWWIEW_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_cu_media_wink_disconnect",
		.weg	= MSCC_PHY_EWW_WINK_DISCONNECT_CNT,
		.page	= MSCC_PHY_PAGE_STANDAWD,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_cu_media_cwc_good_count",
		.weg	= MSCC_PHY_CU_MEDIA_CWC_VAWID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= VAWID_CWC_CNT_CWC_MASK,
	}, {
		.stwing	= "phy_cu_media_cwc_ewwow_count",
		.weg	= MSCC_PHY_EXT_PHY_CNTW_4,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_sewdes_tx_good_pkt_count",
		.weg	= MSCC_PHY_SEWDES_TX_VAWID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= VAWID_CWC_CNT_CWC_MASK,
	}, {
		.stwing	= "phy_sewdes_tx_bad_cwc_count",
		.weg	= MSCC_PHY_SEWDES_TX_CWC_EWW_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= EWW_CNT_MASK,
	}, {
		.stwing	= "phy_sewdes_wx_good_pkt_count",
		.weg	= MSCC_PHY_SEWDES_WX_VAWID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= VAWID_CWC_CNT_CWC_MASK,
	}, {
		.stwing	= "phy_sewdes_wx_bad_cwc_count",
		.weg	= MSCC_PHY_SEWDES_WX_CWC_EWW_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= EWW_CNT_MASK,
	},
};

#if IS_ENABWED(CONFIG_OF_MDIO)
static const stwuct vsc8531_edge_wate_tabwe edge_tabwe[] = {
	{MSCC_VDDMAC_3300, { 0, 2,  4,  7, 10, 17, 29, 53} },
	{MSCC_VDDMAC_2500, { 0, 3,  6, 10, 14, 23, 37, 63} },
	{MSCC_VDDMAC_1800, { 0, 5,  9, 16, 23, 35, 52, 76} },
	{MSCC_VDDMAC_1500, { 0, 6, 14, 21, 29, 42, 58, 77} },
};
#endif

static const int vsc85xx_intewnaw_deway[] = {200, 800, 1100, 1700, 2000, 2300,
					     2600, 3400};

static int vsc85xx_phy_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, MSCC_EXT_PAGE_ACCESS);
}

static int vsc85xx_phy_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, MSCC_EXT_PAGE_ACCESS, page);
}

static int vsc85xx_get_sset_count(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	if (!pwiv)
		wetuwn 0;

	wetuwn pwiv->nstats;
}

static void vsc85xx_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	int i;

	if (!pwiv)
		wetuwn;

	fow (i = 0; i < pwiv->nstats; i++)
		stwscpy(data + i * ETH_GSTWING_WEN, pwiv->hw_stats[i].stwing,
			ETH_GSTWING_WEN);
}

static u64 vsc85xx_get_stat(stwuct phy_device *phydev, int i)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	int vaw;

	vaw = phy_wead_paged(phydev, pwiv->hw_stats[i].page,
			     pwiv->hw_stats[i].weg);
	if (vaw < 0)
		wetuwn U64_MAX;

	vaw = vaw & pwiv->hw_stats[i].mask;
	pwiv->stats[i] += vaw;

	wetuwn pwiv->stats[i];
}

static void vsc85xx_get_stats(stwuct phy_device *phydev,
			      stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	int i;

	if (!pwiv)
		wetuwn;

	fow (i = 0; i < pwiv->nstats; i++)
		data[i] = vsc85xx_get_stat(phydev, i);
}

static int vsc85xx_wed_cntw_set(stwuct phy_device *phydev,
				u8 wed_num,
				u8 mode)
{
	int wc;
	u16 weg_vaw;

	mutex_wock(&phydev->wock);
	weg_vaw = phy_wead(phydev, MSCC_PHY_WED_MODE_SEW);
	weg_vaw &= ~WED_MODE_SEW_MASK(wed_num);
	weg_vaw |= WED_MODE_SEW(wed_num, (u16)mode);
	wc = phy_wwite(phydev, MSCC_PHY_WED_MODE_SEW, weg_vaw);
	mutex_unwock(&phydev->wock);

	wetuwn wc;
}

static int vsc85xx_mdix_get(stwuct phy_device *phydev, u8 *mdix)
{
	u16 weg_vaw;

	weg_vaw = phy_wead(phydev, MSCC_PHY_DEV_AUX_CNTW);
	if (weg_vaw & HP_AUTO_MDIX_X_OVEW_IND_MASK)
		*mdix = ETH_TP_MDI_X;
	ewse
		*mdix = ETH_TP_MDI;

	wetuwn 0;
}

static int vsc85xx_mdix_set(stwuct phy_device *phydev, u8 mdix)
{
	int wc;
	u16 weg_vaw;

	weg_vaw = phy_wead(phydev, MSCC_PHY_BYPASS_CONTWOW);
	if (mdix == ETH_TP_MDI || mdix == ETH_TP_MDI_X) {
		weg_vaw |= (DISABWE_PAIW_SWAP_COWW_MASK |
			    DISABWE_POWAWITY_COWW_MASK  |
			    DISABWE_HP_AUTO_MDIX_MASK);
	} ewse {
		weg_vaw &= ~(DISABWE_PAIW_SWAP_COWW_MASK |
			     DISABWE_POWAWITY_COWW_MASK  |
			     DISABWE_HP_AUTO_MDIX_MASK);
	}
	wc = phy_wwite(phydev, MSCC_PHY_BYPASS_CONTWOW, weg_vaw);
	if (wc)
		wetuwn wc;

	weg_vaw = 0;

	if (mdix == ETH_TP_MDI)
		weg_vaw = FOWCE_MDI_CWOSSOVEW_MDI;
	ewse if (mdix == ETH_TP_MDI_X)
		weg_vaw = FOWCE_MDI_CWOSSOVEW_MDIX;

	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
			      MSCC_PHY_EXT_MODE_CNTW, FOWCE_MDI_CWOSSOVEW_MASK,
			      weg_vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn genphy_westawt_aneg(phydev);
}

static int vsc85xx_downshift_get(stwuct phy_device *phydev, u8 *count)
{
	int weg_vaw;

	weg_vaw = phy_wead_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
				 MSCC_PHY_ACTIPHY_CNTW);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	weg_vaw &= DOWNSHIFT_CNTW_MASK;
	if (!(weg_vaw & DOWNSHIFT_EN))
		*count = DOWNSHIFT_DEV_DISABWE;
	ewse
		*count = ((weg_vaw & ~DOWNSHIFT_EN) >> DOWNSHIFT_CNTW_POS) + 2;

	wetuwn 0;
}

static int vsc85xx_downshift_set(stwuct phy_device *phydev, u8 count)
{
	if (count == DOWNSHIFT_DEV_DEFAUWT_COUNT) {
		/* Defauwt downshift count 3 (i.e. Bit3:2 = 0b01) */
		count = ((1 << DOWNSHIFT_CNTW_POS) | DOWNSHIFT_EN);
	} ewse if (count > DOWNSHIFT_COUNT_MAX || count == 1) {
		phydev_eww(phydev, "Downshift count shouwd be 2,3,4 ow 5\n");
		wetuwn -EWANGE;
	} ewse if (count) {
		/* Downshift count is eithew 2,3,4 ow 5 */
		count = (((count - 2) << DOWNSHIFT_CNTW_POS) | DOWNSHIFT_EN);
	}

	wetuwn phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
				MSCC_PHY_ACTIPHY_CNTW, DOWNSHIFT_CNTW_MASK,
				count);
}

static int vsc85xx_wow_set(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	const u8 *mac_addw = phydev->attached_dev->dev_addw;
	int wc;
	u16 weg_vaw;
	u8  i;
	u16 pwd[3] = {0, 0, 0};
	stwuct ethtoow_wowinfo *wow_conf = wow;

	wc = phy_sewect_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	if (wc < 0)
		wetuwn phy_westowe_page(phydev, wc, wc);

	if (wow->wowopts & WAKE_MAGIC) {
		/* Stowe the device addwess fow the magic packet */
		fow (i = 0; i < AWWAY_SIZE(pwd); i++)
			pwd[i] = mac_addw[5 - (i * 2 + 1)] << 8 |
				 mac_addw[5 - i * 2];
		__phy_wwite(phydev, MSCC_PHY_WOW_WOWEW_MAC_ADDW, pwd[0]);
		__phy_wwite(phydev, MSCC_PHY_WOW_MID_MAC_ADDW, pwd[1]);
		__phy_wwite(phydev, MSCC_PHY_WOW_UPPEW_MAC_ADDW, pwd[2]);
	} ewse {
		__phy_wwite(phydev, MSCC_PHY_WOW_WOWEW_MAC_ADDW, 0);
		__phy_wwite(phydev, MSCC_PHY_WOW_MID_MAC_ADDW, 0);
		__phy_wwite(phydev, MSCC_PHY_WOW_UPPEW_MAC_ADDW, 0);
	}

	if (wow_conf->wowopts & WAKE_MAGICSECUWE) {
		fow (i = 0; i < AWWAY_SIZE(pwd); i++)
			pwd[i] = wow_conf->sopass[5 - (i * 2 + 1)] << 8 |
				 wow_conf->sopass[5 - i * 2];
		__phy_wwite(phydev, MSCC_PHY_WOW_WOWEW_PASSWD, pwd[0]);
		__phy_wwite(phydev, MSCC_PHY_WOW_MID_PASSWD, pwd[1]);
		__phy_wwite(phydev, MSCC_PHY_WOW_UPPEW_PASSWD, pwd[2]);
	} ewse {
		__phy_wwite(phydev, MSCC_PHY_WOW_WOWEW_PASSWD, 0);
		__phy_wwite(phydev, MSCC_PHY_WOW_MID_PASSWD, 0);
		__phy_wwite(phydev, MSCC_PHY_WOW_UPPEW_PASSWD, 0);
	}

	weg_vaw = __phy_wead(phydev, MSCC_PHY_WOW_MAC_CONTWOW);
	if (wow_conf->wowopts & WAKE_MAGICSECUWE)
		weg_vaw |= SECUWE_ON_ENABWE;
	ewse
		weg_vaw &= ~SECUWE_ON_ENABWE;
	__phy_wwite(phydev, MSCC_PHY_WOW_MAC_CONTWOW, weg_vaw);

	wc = phy_westowe_page(phydev, wc, wc > 0 ? 0 : wc);
	if (wc < 0)
		wetuwn wc;

	if (wow->wowopts & WAKE_MAGIC) {
		/* Enabwe the WOW intewwupt */
		weg_vaw = phy_wead(phydev, MII_VSC85XX_INT_MASK);
		weg_vaw |= MII_VSC85XX_INT_MASK_WOW;
		wc = phy_wwite(phydev, MII_VSC85XX_INT_MASK, weg_vaw);
		if (wc)
			wetuwn wc;
	} ewse {
		/* Disabwe the WOW intewwupt */
		weg_vaw = phy_wead(phydev, MII_VSC85XX_INT_MASK);
		weg_vaw &= (~MII_VSC85XX_INT_MASK_WOW);
		wc = phy_wwite(phydev, MII_VSC85XX_INT_MASK, weg_vaw);
		if (wc)
			wetuwn wc;
	}
	/* Cweaw WOW itewwupt status */
	weg_vaw = phy_wead(phydev, MII_VSC85XX_INT_STATUS);

	wetuwn 0;
}

static void vsc85xx_wow_get(stwuct phy_device *phydev,
			    stwuct ethtoow_wowinfo *wow)
{
	int wc;
	u16 weg_vaw;
	u8  i;
	u16 pwd[3] = {0, 0, 0};
	stwuct ethtoow_wowinfo *wow_conf = wow;

	wc = phy_sewect_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	if (wc < 0)
		goto out_westowe_page;

	weg_vaw = __phy_wead(phydev, MSCC_PHY_WOW_MAC_CONTWOW);
	if (weg_vaw & SECUWE_ON_ENABWE)
		wow_conf->wowopts |= WAKE_MAGICSECUWE;
	if (wow_conf->wowopts & WAKE_MAGICSECUWE) {
		pwd[0] = __phy_wead(phydev, MSCC_PHY_WOW_WOWEW_PASSWD);
		pwd[1] = __phy_wead(phydev, MSCC_PHY_WOW_MID_PASSWD);
		pwd[2] = __phy_wead(phydev, MSCC_PHY_WOW_UPPEW_PASSWD);
		fow (i = 0; i < AWWAY_SIZE(pwd); i++) {
			wow_conf->sopass[5 - i * 2] = pwd[i] & 0x00ff;
			wow_conf->sopass[5 - (i * 2 + 1)] = (pwd[i] & 0xff00)
							    >> 8;
		}
	}

out_westowe_page:
	phy_westowe_page(phydev, wc, wc > 0 ? 0 : wc);
}

#if IS_ENABWED(CONFIG_OF_MDIO)
static int vsc85xx_edge_wate_magic_get(stwuct phy_device *phydev)
{
	u32 vdd, sd;
	int i, j;
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device_node *of_node = dev->of_node;
	u8 sd_awway_size = AWWAY_SIZE(edge_tabwe[0].swowdown);

	if (!of_node)
		wetuwn -ENODEV;

	if (of_pwopewty_wead_u32(of_node, "vsc8531,vddmac", &vdd))
		vdd = MSCC_VDDMAC_3300;

	if (of_pwopewty_wead_u32(of_node, "vsc8531,edge-swowdown", &sd))
		sd = 0;

	fow (i = 0; i < AWWAY_SIZE(edge_tabwe); i++)
		if (edge_tabwe[i].vddmac == vdd)
			fow (j = 0; j < sd_awway_size; j++)
				if (edge_tabwe[i].swowdown[j] == sd)
					wetuwn (sd_awway_size - j - 1);

	wetuwn -EINVAW;
}

static int vsc85xx_dt_wed_mode_get(stwuct phy_device *phydev,
				   chaw *wed,
				   u32 defauwt_mode)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device_node *of_node = dev->of_node;
	u32 wed_mode;
	int eww;

	if (!of_node)
		wetuwn -ENODEV;

	wed_mode = defauwt_mode;
	eww = of_pwopewty_wead_u32(of_node, wed, &wed_mode);
	if (!eww && !(BIT(wed_mode) & pwiv->supp_wed_modes)) {
		phydev_eww(phydev, "DT %s invawid\n", wed);
		wetuwn -EINVAW;
	}

	wetuwn wed_mode;
}

#ewse
static int vsc85xx_edge_wate_magic_get(stwuct phy_device *phydev)
{
	wetuwn 0;
}

static int vsc85xx_dt_wed_mode_get(stwuct phy_device *phydev,
				   chaw *wed,
				   u8 defauwt_mode)
{
	wetuwn defauwt_mode;
}
#endif /* CONFIG_OF_MDIO */

static int vsc85xx_dt_wed_modes_get(stwuct phy_device *phydev,
				    u32 *defauwt_mode)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	chaw wed_dt_pwop[28];
	int i, wet;

	fow (i = 0; i < pwiv->nweds; i++) {
		wet = spwintf(wed_dt_pwop, "vsc8531,wed-%d-mode", i);
		if (wet < 0)
			wetuwn wet;

		wet = vsc85xx_dt_wed_mode_get(phydev, wed_dt_pwop,
					      defauwt_mode[i]);
		if (wet < 0)
			wetuwn wet;
		pwiv->weds_mode[i] = wet;
	}

	wetuwn 0;
}

static int vsc85xx_edge_wate_cntw_set(stwuct phy_device *phydev, u8 edge_wate)
{
	int wc;

	mutex_wock(&phydev->wock);
	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
			      MSCC_PHY_WOW_MAC_CONTWOW, EDGE_WATE_CNTW_MASK,
			      edge_wate << EDGE_WATE_CNTW_POS);
	mutex_unwock(&phydev->wock);

	wetuwn wc;
}

static int vsc85xx_mac_if_set(stwuct phy_device *phydev,
			      phy_intewface_t intewface)
{
	int wc;
	u16 weg_vaw;

	mutex_wock(&phydev->wock);
	weg_vaw = phy_wead(phydev, MSCC_PHY_EXT_PHY_CNTW_1);
	weg_vaw &= ~(MAC_IF_SEWECTION_MASK);
	switch (intewface) {
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII:
		weg_vaw |= (MAC_IF_SEWECTION_WGMII << MAC_IF_SEWECTION_POS);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		weg_vaw |= (MAC_IF_SEWECTION_WMII << MAC_IF_SEWECTION_POS);
		bweak;
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_GMII:
		weg_vaw |= (MAC_IF_SEWECTION_GMII << MAC_IF_SEWECTION_POS);
		bweak;
	defauwt:
		wc = -EINVAW;
		goto out_unwock;
	}
	wc = phy_wwite(phydev, MSCC_PHY_EXT_PHY_CNTW_1, weg_vaw);
	if (wc)
		goto out_unwock;

	wc = genphy_soft_weset(phydev);

out_unwock:
	mutex_unwock(&phydev->wock);

	wetuwn wc;
}

/* Set the WGMII WX and TX cwock skews individuawwy, accowding to the PHY
 * intewface type, to:
 *  * 0.2 ns (theiw defauwt, and wowest, hawdwawe vawue) if deways shouwd
 *    not be enabwed
 *  * 2.0 ns (which causes the data to be sampwed at exactwy hawf way between
 *    cwock twansitions at 1000 Mbps) if deways shouwd be enabwed
 */
static int vsc85xx_update_wgmii_cntw(stwuct phy_device *phydev, u32 wgmii_cntw,
				     u16 wgmii_wx_deway_mask,
				     u16 wgmii_tx_deway_mask)
{
	u16 wgmii_wx_deway_pos = ffs(wgmii_wx_deway_mask) - 1;
	u16 wgmii_tx_deway_pos = ffs(wgmii_tx_deway_mask) - 1;
	int deway_size = AWWAY_SIZE(vsc85xx_intewnaw_deway);
	stwuct device *dev = &phydev->mdio.dev;
	u16 weg_vaw = 0;
	u16 mask = 0;
	s32 wx_deway;
	s32 tx_deway;
	int wc = 0;

	/* Fow twaffic to pass, the VSC8502 famiwy needs the WX_CWK disabwe bit
	 * to be unset fow aww PHY modes, so do that as pawt of the paged
	 * wegistew modification.
	 * Fow some famiwy membews (wike VSC8530/31/40/41) this bit is wesewved
	 * and wead-onwy, and the WX cwock is enabwed by defauwt.
	 */
	if (wgmii_cntw == VSC8502_WGMII_CNTW)
		mask |= VSC8502_WGMII_WX_CWK_DISABWE;

	if (phy_intewface_is_wgmii(phydev))
		mask |= wgmii_wx_deway_mask | wgmii_tx_deway_mask;

	wx_deway = phy_get_intewnaw_deway(phydev, dev, vsc85xx_intewnaw_deway,
					  deway_size, twue);
	if (wx_deway < 0) {
		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID ||
		    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
			wx_deway = WGMII_CWK_DEWAY_2_0_NS;
		ewse
			wx_deway = WGMII_CWK_DEWAY_0_2_NS;
	}

	tx_deway = phy_get_intewnaw_deway(phydev, dev, vsc85xx_intewnaw_deway,
					  deway_size, fawse);
	if (tx_deway < 0) {
		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID ||
		    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
			tx_deway = WGMII_CWK_DEWAY_2_0_NS;
		ewse
			tx_deway = WGMII_CWK_DEWAY_0_2_NS;
	}

	weg_vaw |= wx_deway << wgmii_wx_deway_pos;
	weg_vaw |= tx_deway << wgmii_tx_deway_pos;

	if (mask)
		wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
				      wgmii_cntw, mask, weg_vaw);

	wetuwn wc;
}

static int vsc85xx_defauwt_config(stwuct phy_device *phydev)
{
	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	wetuwn vsc85xx_update_wgmii_cntw(phydev, VSC8502_WGMII_CNTW,
					 VSC8502_WGMII_WX_DEWAY_MASK,
					 VSC8502_WGMII_TX_DEWAY_MASK);
}

static int vsc85xx_get_tunabwe(stwuct phy_device *phydev,
			       stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn vsc85xx_downshift_get(phydev, (u8 *)data);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vsc85xx_set_tunabwe(stwuct phy_device *phydev,
			       stwuct ethtoow_tunabwe *tuna,
			       const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn vsc85xx_downshift_set(phydev, *(u8 *)data);
	defauwt:
		wetuwn -EINVAW;
	}
}

/* mdiobus wock shouwd be wocked when using this function */
static void vsc85xx_tw_wwite(stwuct phy_device *phydev, u16 addw, u32 vaw)
{
	__phy_wwite(phydev, MSCC_PHY_TW_MSB, vaw >> 16);
	__phy_wwite(phydev, MSCC_PHY_TW_WSB, vaw & GENMASK(15, 0));
	__phy_wwite(phydev, MSCC_PHY_TW_CNTW, TW_WWITE | TW_ADDW(addw));
}

static int vsc8531_pwe_init_seq_set(stwuct phy_device *phydev)
{
	int wc;
	static const stwuct weg_vaw init_seq[] = {
		{0x0f90, 0x00688980},
		{0x0696, 0x00000003},
		{0x07fa, 0x0050100f},
		{0x1686, 0x00000004},
	};
	unsigned int i;
	int owdpage;

	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_STANDAWD,
			      MSCC_PHY_EXT_CNTW_STATUS, SMI_BWOADCAST_WW_EN,
			      SMI_BWOADCAST_WW_EN);
	if (wc < 0)
		wetuwn wc;
	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_24, 0, 0x0400);
	if (wc < 0)
		wetuwn wc;
	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_5, 0x0a00, 0x0e00);
	if (wc < 0)
		wetuwn wc;
	wc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_8, TW_CWK_DISABWE, TW_CWK_DISABWE);
	if (wc < 0)
		wetuwn wc;

	mutex_wock(&phydev->wock);
	owdpage = phy_sewect_page(phydev, MSCC_PHY_PAGE_TW);
	if (owdpage < 0)
		goto out_unwock;

	fow (i = 0; i < AWWAY_SIZE(init_seq); i++)
		vsc85xx_tw_wwite(phydev, init_seq[i].weg, init_seq[i].vaw);

out_unwock:
	owdpage = phy_westowe_page(phydev, owdpage, owdpage);
	mutex_unwock(&phydev->wock);

	wetuwn owdpage;
}

static int vsc85xx_eee_init_seq_set(stwuct phy_device *phydev)
{
	static const stwuct weg_vaw init_eee[] = {
		{0x0f82, 0x0012b00a},
		{0x1686, 0x00000004},
		{0x168c, 0x00d2c46f},
		{0x17a2, 0x00000620},
		{0x16a0, 0x00eeffdd},
		{0x16a6, 0x00071448},
		{0x16a4, 0x0013132f},
		{0x16a8, 0x00000000},
		{0x0ffc, 0x00c0a028},
		{0x0fe8, 0x0091b06c},
		{0x0fea, 0x00041600},
		{0x0f80, 0x00000af4},
		{0x0fec, 0x00901809},
		{0x0fee, 0x0000a6a1},
		{0x0ffe, 0x00b01007},
		{0x16b0, 0x00eeff00},
		{0x16b2, 0x00007000},
		{0x16b4, 0x00000814},
	};
	unsigned int i;
	int owdpage;

	mutex_wock(&phydev->wock);
	owdpage = phy_sewect_page(phydev, MSCC_PHY_PAGE_TW);
	if (owdpage < 0)
		goto out_unwock;

	fow (i = 0; i < AWWAY_SIZE(init_eee); i++)
		vsc85xx_tw_wwite(phydev, init_eee[i].weg, init_eee[i].vaw);

out_unwock:
	owdpage = phy_westowe_page(phydev, owdpage, owdpage);
	mutex_unwock(&phydev->wock);

	wetuwn owdpage;
}

/* phydev->bus->mdio_wock shouwd be wocked when using this function */
int phy_base_wwite(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	if (unwikewy(!mutex_is_wocked(&phydev->mdio.bus->mdio_wock))) {
		dev_eww(&phydev->mdio.dev, "MDIO bus wock not hewd!\n");
		dump_stack();
	}

	wetuwn __phy_package_wwite(phydev, VSC88XX_BASE_ADDW, wegnum, vaw);
}

/* phydev->bus->mdio_wock shouwd be wocked when using this function */
int phy_base_wead(stwuct phy_device *phydev, u32 wegnum)
{
	if (unwikewy(!mutex_is_wocked(&phydev->mdio.bus->mdio_wock))) {
		dev_eww(&phydev->mdio.dev, "MDIO bus wock not hewd!\n");
		dump_stack();
	}

	wetuwn __phy_package_wead(phydev, VSC88XX_BASE_ADDW, wegnum);
}

u32 vsc85xx_csw_wead(stwuct phy_device *phydev,
		     enum csw_tawget tawget, u32 weg)
{
	unsigned wong deadwine;
	u32 vaw, vaw_w, vaw_h;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_CSW_CNTW);

	/* CSW wegistews awe gwouped undew diffewent Tawget IDs.
	 * 6-bit Tawget_ID is spwit between MSCC_EXT_PAGE_CSW_CNTW_20 and
	 * MSCC_EXT_PAGE_CSW_CNTW_19 wegistews.
	 * Tawget_ID[5:2] maps to bits[3:0] of MSCC_EXT_PAGE_CSW_CNTW_20
	 * and Tawget_ID[1:0] maps to bits[13:12] of MSCC_EXT_PAGE_CSW_CNTW_19.
	 */

	/* Setup the Tawget ID */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_20,
		       MSCC_PHY_CSW_CNTW_20_TAWGET(tawget >> 2));

	if ((tawget >> 2 == 0x1) || (tawget >> 2 == 0x3))
		/* non-MACsec access */
		tawget &= 0x3;
	ewse
		tawget = 0;

	/* Twiggew CSW Action - Wead into the CSW's */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_19,
		       MSCC_PHY_CSW_CNTW_19_CMD | MSCC_PHY_CSW_CNTW_19_WEAD |
		       MSCC_PHY_CSW_CNTW_19_WEG_ADDW(weg) |
		       MSCC_PHY_CSW_CNTW_19_TAWGET(tawget));

	/* Wait fow wegistew access*/
	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		vaw = phy_base_wead(phydev, MSCC_EXT_PAGE_CSW_CNTW_19);
	} whiwe (time_befowe(jiffies, deadwine) &&
		!(vaw & MSCC_PHY_CSW_CNTW_19_CMD));

	if (!(vaw & MSCC_PHY_CSW_CNTW_19_CMD))
		wetuwn 0xffffffff;

	/* Wead the Weast Significant Wowd (WSW) (17) */
	vaw_w = phy_base_wead(phydev, MSCC_EXT_PAGE_CSW_CNTW_17);

	/* Wead the Most Significant Wowd (MSW) (18) */
	vaw_h = phy_base_wead(phydev, MSCC_EXT_PAGE_CSW_CNTW_18);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_STANDAWD);

	wetuwn (vaw_h << 16) | vaw_w;
}

int vsc85xx_csw_wwite(stwuct phy_device *phydev,
		      enum csw_tawget tawget, u32 weg, u32 vaw)
{
	unsigned wong deadwine;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_CSW_CNTW);

	/* CSW wegistews awe gwouped undew diffewent Tawget IDs.
	 * 6-bit Tawget_ID is spwit between MSCC_EXT_PAGE_CSW_CNTW_20 and
	 * MSCC_EXT_PAGE_CSW_CNTW_19 wegistews.
	 * Tawget_ID[5:2] maps to bits[3:0] of MSCC_EXT_PAGE_CSW_CNTW_20
	 * and Tawget_ID[1:0] maps to bits[13:12] of MSCC_EXT_PAGE_CSW_CNTW_19.
	 */

	/* Setup the Tawget ID */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_20,
		       MSCC_PHY_CSW_CNTW_20_TAWGET(tawget >> 2));

	/* Wwite the Weast Significant Wowd (WSW) (17) */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_17, (u16)vaw);

	/* Wwite the Most Significant Wowd (MSW) (18) */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_18, (u16)(vaw >> 16));

	if ((tawget >> 2 == 0x1) || (tawget >> 2 == 0x3))
		/* non-MACsec access */
		tawget &= 0x3;
	ewse
		tawget = 0;

	/* Twiggew CSW Action - Wwite into the CSW's */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_CSW_CNTW_19,
		       MSCC_PHY_CSW_CNTW_19_CMD |
		       MSCC_PHY_CSW_CNTW_19_WEG_ADDW(weg) |
		       MSCC_PHY_CSW_CNTW_19_TAWGET(tawget));

	/* Wait fow wegistew access */
	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		vaw = phy_base_wead(phydev, MSCC_EXT_PAGE_CSW_CNTW_19);
	} whiwe (time_befowe(jiffies, deadwine) &&
		 !(vaw & MSCC_PHY_CSW_CNTW_19_CMD));

	if (!(vaw & MSCC_PHY_CSW_CNTW_19_CMD))
		wetuwn -ETIMEDOUT;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_STANDAWD);

	wetuwn 0;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static void vsc8584_csw_wwite(stwuct phy_device *phydev, u16 addw, u32 vaw)
{
	phy_base_wwite(phydev, MSCC_PHY_TW_MSB, vaw >> 16);
	phy_base_wwite(phydev, MSCC_PHY_TW_WSB, vaw & GENMASK(15, 0));
	phy_base_wwite(phydev, MSCC_PHY_TW_CNTW, TW_WWITE | TW_ADDW(addw));
}

/* bus->mdio_wock shouwd be wocked when using this function */
int vsc8584_cmd(stwuct phy_device *phydev, u16 vaw)
{
	unsigned wong deadwine;
	u16 weg_vaw;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	phy_base_wwite(phydev, MSCC_PHY_PWOC_CMD, PWOC_CMD_NCOMPWETED | vaw);

	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		weg_vaw = phy_base_wead(phydev, MSCC_PHY_PWOC_CMD);
	} whiwe (time_befowe(jiffies, deadwine) &&
		 (weg_vaw & PWOC_CMD_NCOMPWETED) &&
		 !(weg_vaw & PWOC_CMD_FAIWED));

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	if (weg_vaw & PWOC_CMD_FAIWED)
		wetuwn -EIO;

	if (weg_vaw & PWOC_CMD_NCOMPWETED)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8584_micwo_deassewt_weset(stwuct phy_device *phydev,
					boow patch_en)
{
	u32 enabwe, wewease;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	enabwe = WUN_FWOM_INT_WOM | MICWO_CWK_EN | DW8051_CWK_EN;
	wewease = MICWO_NSOFT_WESET | WUN_FWOM_INT_WOM | DW8051_CWK_EN |
		MICWO_CWK_EN;

	if (patch_en) {
		enabwe |= MICWO_PATCH_EN;
		wewease |= MICWO_PATCH_EN;

		/* Cweaw aww patches */
		phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, WEAD_WAM);
	}

	/* Enabwe 8051 Micwo cwock; CWEAW/SET patch pwesent; disabwe PWAM cwock
	 * ovewwide and addw. auto-incw; opewate at 125 MHz
	 */
	phy_base_wwite(phydev, MSCC_DW8051_CNTW_STATUS, enabwe);
	/* Wewease 8051 Micwo SW weset */
	phy_base_wwite(phydev, MSCC_DW8051_CNTW_STATUS, wewease);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wetuwn 0;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8584_micwo_assewt_weset(stwuct phy_device *phydev)
{
	int wet;
	u16 weg;

	wet = vsc8584_cmd(phydev, PWOC_CMD_NOP);
	if (wet)
		wetuwn wet;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	weg &= ~EN_PATCH_WAM_TWAP_ADDW(4);
	phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, weg);

	phy_base_wwite(phydev, MSCC_TWAP_WOM_ADDW(4), 0x005b);
	phy_base_wwite(phydev, MSCC_PATCH_WAM_ADDW(4), 0x005b);

	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	weg |= EN_PATCH_WAM_TWAP_ADDW(4);
	phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, weg);

	phy_base_wwite(phydev, MSCC_PHY_PWOC_CMD, PWOC_CMD_NOP);

	weg = phy_base_wead(phydev, MSCC_DW8051_CNTW_STATUS);
	weg &= ~MICWO_NSOFT_WESET;
	phy_base_wwite(phydev, MSCC_DW8051_CNTW_STATUS, weg);

	phy_base_wwite(phydev, MSCC_PHY_PWOC_CMD, PWOC_CMD_MCB_ACCESS_MAC_CONF |
		       PWOC_CMD_SGMII_POWT(0) | PWOC_CMD_NO_MAC_CONF |
		       PWOC_CMD_WEAD);

	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	weg &= ~EN_PATCH_WAM_TWAP_ADDW(4);
	phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wetuwn 0;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8584_get_fw_cwc(stwuct phy_device *phydev, u16 stawt, u16 size,
			      u16 *cwc)
{
	int wet;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	phy_base_wwite(phydev, MSCC_PHY_VEWIPHY_CNTW_2, stawt);
	phy_base_wwite(phydev, MSCC_PHY_VEWIPHY_CNTW_3, size);

	/* Stawt Micwo command */
	wet = vsc8584_cmd(phydev, PWOC_CMD_CWC16);
	if (wet)
		goto out;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	*cwc = phy_base_wead(phydev, MSCC_PHY_VEWIPHY_CNTW_2);

out:
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wetuwn wet;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8584_patch_fw(stwuct phy_device *phydev,
			    const stwuct fiwmwawe *fw)
{
	int i, wet;

	wet = vsc8584_micwo_assewt_weset(phydev);
	if (wet) {
		dev_eww(&phydev->mdio.dev,
			"%s: faiwed to assewt weset of micwo\n", __func__);
		wetuwn wet;
	}

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	/* Howd 8051 Micwo in SW Weset, Enabwe auto incw addwess and patch cwock
	 * Disabwe the 8051 Micwo cwock
	 */
	phy_base_wwite(phydev, MSCC_DW8051_CNTW_STATUS, WUN_FWOM_INT_WOM |
		       AUTOINC_ADDW | PATCH_WAM_CWK | MICWO_CWK_EN |
		       MICWO_CWK_DIVIDE(2));
	phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, WEAD_PWAM | INT_MEM_WWITE_EN |
		       INT_MEM_DATA(2));
	phy_base_wwite(phydev, MSCC_INT_MEM_ADDW, 0x0000);

	fow (i = 0; i < fw->size; i++)
		phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, WEAD_PWAM |
			       INT_MEM_WWITE_EN | fw->data[i]);

	/* Cweaw intewnaw memowy access */
	phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, WEAD_WAM);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wetuwn 0;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static boow vsc8574_is_sewdes_init(stwuct phy_device *phydev)
{
	u16 weg;
	boow wet;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	weg = phy_base_wead(phydev, MSCC_TWAP_WOM_ADDW(1));
	if (weg != 0x3eb7) {
		wet = fawse;
		goto out;
	}

	weg = phy_base_wead(phydev, MSCC_PATCH_WAM_ADDW(1));
	if (weg != 0x4012) {
		wet = fawse;
		goto out;
	}

	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	if (weg != EN_PATCH_WAM_TWAP_ADDW(1)) {
		wet = fawse;
		goto out;
	}

	weg = phy_base_wead(phydev, MSCC_DW8051_CNTW_STATUS);
	if ((MICWO_NSOFT_WESET | WUN_FWOM_INT_WOM |  DW8051_CWK_EN |
	     MICWO_CWK_EN) != (weg & MSCC_DW8051_VWD_MASK)) {
		wet = fawse;
		goto out;
	}

	wet = twue;
out:
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wetuwn wet;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8574_config_pwe_init(stwuct phy_device *phydev)
{
	static const stwuct weg_vaw pwe_init1[] = {
		{0x0fae, 0x000401bd},
		{0x0fac, 0x000f000f},
		{0x17a0, 0x00a0f147},
		{0x0fe4, 0x00052f54},
		{0x1792, 0x0027303d},
		{0x07fe, 0x00000704},
		{0x0fe0, 0x00060150},
		{0x0f82, 0x0012b00a},
		{0x0f80, 0x00000d74},
		{0x02e0, 0x00000012},
		{0x03a2, 0x00050208},
		{0x03b2, 0x00009186},
		{0x0fb0, 0x000e3700},
		{0x1688, 0x00049f81},
		{0x0fd2, 0x0000ffff},
		{0x168a, 0x00039fa2},
		{0x1690, 0x0020640b},
		{0x0258, 0x00002220},
		{0x025a, 0x00002a20},
		{0x025c, 0x00003060},
		{0x025e, 0x00003fa0},
		{0x03a6, 0x0000e0f0},
		{0x0f92, 0x00001489},
		{0x16a2, 0x00007000},
		{0x16a6, 0x00071448},
		{0x16a0, 0x00eeffdd},
		{0x0fe8, 0x0091b06c},
		{0x0fea, 0x00041600},
		{0x16b0, 0x00eeff00},
		{0x16b2, 0x00007000},
		{0x16b4, 0x00000814},
		{0x0f90, 0x00688980},
		{0x03a4, 0x0000d8f0},
		{0x0fc0, 0x00000400},
		{0x07fa, 0x0050100f},
		{0x0796, 0x00000003},
		{0x07f8, 0x00c3ff98},
		{0x0fa4, 0x0018292a},
		{0x168c, 0x00d2c46f},
		{0x17a2, 0x00000620},
		{0x16a4, 0x0013132f},
		{0x16a8, 0x00000000},
		{0x0ffc, 0x00c0a028},
		{0x0fec, 0x00901c09},
		{0x0fee, 0x0004a6a1},
		{0x0ffe, 0x00b01807},
	};
	static const stwuct weg_vaw pwe_init2[] = {
		{0x0486, 0x0008a518},
		{0x0488, 0x006dc696},
		{0x048a, 0x00000912},
		{0x048e, 0x00000db6},
		{0x049c, 0x00596596},
		{0x049e, 0x00000514},
		{0x04a2, 0x00410280},
		{0x04a4, 0x00000000},
		{0x04a6, 0x00000000},
		{0x04a8, 0x00000000},
		{0x04aa, 0x00000000},
		{0x04ae, 0x007df7dd},
		{0x04b0, 0x006d95d4},
		{0x04b2, 0x00492410},
	};
	stwuct device *dev = &phydev->mdio.dev;
	const stwuct fiwmwawe *fw;
	unsigned int i;
	u16 cwc, weg;
	boow sewdes_init;
	int wet;

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* aww wwites bewow awe bwoadcasted to aww PHYs in the same package */
	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg |= SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	phy_base_wwite(phydev, MII_VSC85XX_INT_MASK, 0);

	/* The bewow wegistew wwites awe tweaking anawog and ewectwicaw
	 * configuwation that wewe detewmined thwough chawactewization by PHY
	 * engineews. These don't mean anything mowe than "these awe the best
	 * vawues".
	 */
	phy_base_wwite(phydev, MSCC_PHY_EXT_PHY_CNTW_2, 0x0040);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_20, 0x4320);
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_24, 0x0c00);
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_9, 0x18ca);
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_5, 0x1b20);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg |= TW_CWK_DISABWE;
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TW);

	fow (i = 0; i < AWWAY_SIZE(pwe_init1); i++)
		vsc8584_csw_wwite(phydev, pwe_init1[i].weg, pwe_init1[i].vaw);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);

	phy_base_wwite(phydev, MSCC_PHY_CU_PMD_TX_CNTW, 0x028e);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TW);

	fow (i = 0; i < AWWAY_SIZE(pwe_init2); i++)
		vsc8584_csw_wwite(phydev, pwe_init2[i].weg, pwe_init2[i].vaw);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg &= ~TW_CWK_DISABWE;
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* end of wwite bwoadcasting */
	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg &= ~SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	wet = wequest_fiwmwawe(&fw, MSCC_VSC8574_WEVB_INT8051_FW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to woad fiwmwawe %s, wet: %d\n",
			MSCC_VSC8574_WEVB_INT8051_FW, wet);
		wetuwn wet;
	}

	/* Add one byte to size fow the one added by the patch_fw function */
	wet = vsc8584_get_fw_cwc(phydev,
				 MSCC_VSC8574_WEVB_INT8051_FW_STAWT_ADDW,
				 fw->size + 1, &cwc);
	if (wet)
		goto out;

	if (cwc == MSCC_VSC8574_WEVB_INT8051_FW_CWC) {
		sewdes_init = vsc8574_is_sewdes_init(phydev);

		if (!sewdes_init) {
			wet = vsc8584_micwo_assewt_weset(phydev);
			if (wet) {
				dev_eww(dev,
					"%s: faiwed to assewt weset of micwo\n",
					__func__);
				goto out;
			}
		}
	} ewse {
		dev_dbg(dev, "FW CWC is not the expected one, patching FW\n");

		sewdes_init = fawse;

		if (vsc8584_patch_fw(phydev, fw))
			dev_wawn(dev,
				 "faiwed to patch FW, expect non-optimaw device\n");
	}

	if (!sewdes_init) {
		phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			       MSCC_PHY_PAGE_EXTENDED_GPIO);

		phy_base_wwite(phydev, MSCC_TWAP_WOM_ADDW(1), 0x3eb7);
		phy_base_wwite(phydev, MSCC_PATCH_WAM_ADDW(1), 0x4012);
		phy_base_wwite(phydev, MSCC_INT_MEM_CNTW,
			       EN_PATCH_WAM_TWAP_ADDW(1));

		vsc8584_micwo_deassewt_weset(phydev, fawse);

		/* Add one byte to size fow the one added by the patch_fw
		 * function
		 */
		wet = vsc8584_get_fw_cwc(phydev,
					 MSCC_VSC8574_WEVB_INT8051_FW_STAWT_ADDW,
					 fw->size + 1, &cwc);
		if (wet)
			goto out;

		if (cwc != MSCC_VSC8574_WEVB_INT8051_FW_CWC)
			dev_wawn(dev,
				 "FW CWC aftew patching is not the expected one, expect non-optimaw device\n");
	}

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	wet = vsc8584_cmd(phydev, PWOC_CMD_1588_DEFAUWT_INIT |
			  PWOC_CMD_PHY_INIT);

out:
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

/* Access WCPWW Cfg_2 */
static void vsc8584_pww5g_cfg2_ww(stwuct phy_device *phydev,
				  boow disabwe_fsm)
{
	u32 wd_dat;

	wd_dat = vsc85xx_csw_wead(phydev, MACWO_CTWW, PHY_S6G_PWW5G_CFG2);
	wd_dat &= ~BIT(PHY_S6G_CFG2_FSM_DIS);
	wd_dat |= (disabwe_fsm << PHY_S6G_CFG2_FSM_DIS);
	vsc85xx_csw_wwite(phydev, MACWO_CTWW, PHY_S6G_PWW5G_CFG2, wd_dat);
}

/* twiggew a wead to the spcified MCB */
static int vsc8584_mcb_wd_twig(stwuct phy_device *phydev,
			       u32 mcb_weg_addw, u8 mcb_swave_num)
{
	u32 wd_dat = 0;

	/* wead MCB */
	vsc85xx_csw_wwite(phydev, MACWO_CTWW, mcb_weg_addw,
			  (0x40000000 | (1W << mcb_swave_num)));

	wetuwn wead_poww_timeout(vsc85xx_csw_wead, wd_dat,
				 !(wd_dat & 0x40000000),
				 4000, 200000, 0,
				 phydev, MACWO_CTWW, mcb_weg_addw);
}

/* twiggew a wwite to the spcified MCB */
static int vsc8584_mcb_ww_twig(stwuct phy_device *phydev,
			       u32 mcb_weg_addw,
			       u8 mcb_swave_num)
{
	u32 wd_dat = 0;

	/* wwite back MCB */
	vsc85xx_csw_wwite(phydev, MACWO_CTWW, mcb_weg_addw,
			  (0x80000000 | (1W << mcb_swave_num)));

	wetuwn wead_poww_timeout(vsc85xx_csw_wead, wd_dat,
				 !(wd_dat & 0x80000000),
				 4000, 200000, 0,
				 phydev, MACWO_CTWW, mcb_weg_addw);
}

/* Sequence to Weset WCPWW fow the VIPEW and EWISE PHY */
static int vsc8584_pww5g_weset(stwuct phy_device *phydev)
{
	boow dis_fsm;
	int wet = 0;

	wet = vsc8584_mcb_wd_twig(phydev, 0x11, 0);
	if (wet < 0)
		goto done;
	dis_fsm = 1;

	/* Weset WCPWW */
	vsc8584_pww5g_cfg2_ww(phydev, dis_fsm);

	/* wwite back WCPWW MCB */
	wet = vsc8584_mcb_ww_twig(phydev, 0x11, 0);
	if (wet < 0)
		goto done;

	/* 10 mSec sweep whiwe WCPWW is howd in weset */
	usweep_wange(10000, 20000);

	/* wead WCPWW MCB into CSWs */
	wet = vsc8584_mcb_wd_twig(phydev, 0x11, 0);
	if (wet < 0)
		goto done;
	dis_fsm = 0;

	/* Wewease the Weset of WCPWW */
	vsc8584_pww5g_cfg2_ww(phydev, dis_fsm);

	/* wwite back WCPWW MCB */
	wet = vsc8584_mcb_ww_twig(phydev, 0x11, 0);
	if (wet < 0)
		goto done;

	usweep_wange(110000, 200000);
done:
	wetuwn wet;
}

/* bus->mdio_wock shouwd be wocked when using this function */
static int vsc8584_config_pwe_init(stwuct phy_device *phydev)
{
	static const stwuct weg_vaw pwe_init1[] = {
		{0x07fa, 0x0050100f},
		{0x1688, 0x00049f81},
		{0x0f90, 0x00688980},
		{0x03a4, 0x0000d8f0},
		{0x0fc0, 0x00000400},
		{0x0f82, 0x0012b002},
		{0x1686, 0x00000004},
		{0x168c, 0x00d2c46f},
		{0x17a2, 0x00000620},
		{0x16a0, 0x00eeffdd},
		{0x16a6, 0x00071448},
		{0x16a4, 0x0013132f},
		{0x16a8, 0x00000000},
		{0x0ffc, 0x00c0a028},
		{0x0fe8, 0x0091b06c},
		{0x0fea, 0x00041600},
		{0x0f80, 0x00fffaff},
		{0x0fec, 0x00901809},
		{0x0ffe, 0x00b01007},
		{0x16b0, 0x00eeff00},
		{0x16b2, 0x00007000},
		{0x16b4, 0x00000814},
	};
	static const stwuct weg_vaw pwe_init2[] = {
		{0x0486, 0x0008a518},
		{0x0488, 0x006dc696},
		{0x048a, 0x00000912},
	};
	const stwuct fiwmwawe *fw;
	stwuct device *dev = &phydev->mdio.dev;
	unsigned int i;
	u16 cwc, weg;
	int wet;

	wet = vsc8584_pww5g_weset(phydev);
	if (wet < 0) {
		dev_eww(dev, "faiwed WCPWW weset, wet: %d\n", wet);
		wetuwn wet;
	}

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* aww wwites bewow awe bwoadcasted to aww PHYs in the same package */
	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg |= SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	phy_base_wwite(phydev, MII_VSC85XX_INT_MASK, 0);

	weg = phy_base_wead(phydev,  MSCC_PHY_BYPASS_CONTWOW);
	weg |= PAWAWWEW_DET_IGNOWE_ADVEWTISED;
	phy_base_wwite(phydev, MSCC_PHY_BYPASS_CONTWOW, weg);

	/* The bewow wegistew wwites awe tweaking anawog and ewectwicaw
	 * configuwation that wewe detewmined thwough chawactewization by PHY
	 * engineews. These don't mean anything mowe than "these awe the best
	 * vawues".
	 */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_3);

	phy_base_wwite(phydev, MSCC_PHY_SEWDES_TX_CWC_EWW_CNT, 0x2000);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_5, 0x1f20);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg |= TW_CWK_DISABWE;
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TW);

	phy_base_wwite(phydev, MSCC_PHY_TW_CNTW, TW_WWITE | TW_ADDW(0x2fa4));

	weg = phy_base_wead(phydev, MSCC_PHY_TW_MSB);
	weg &= ~0x007f;
	weg |= 0x0019;
	phy_base_wwite(phydev, MSCC_PHY_TW_MSB, weg);

	phy_base_wwite(phydev, MSCC_PHY_TW_CNTW, TW_WWITE | TW_ADDW(0x0fa4));

	fow (i = 0; i < AWWAY_SIZE(pwe_init1); i++)
		vsc8584_csw_wwite(phydev, pwe_init1[i].weg, pwe_init1[i].vaw);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);

	phy_base_wwite(phydev, MSCC_PHY_CU_PMD_TX_CNTW, 0x028e);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TW);

	fow (i = 0; i < AWWAY_SIZE(pwe_init2); i++)
		vsc8584_csw_wwite(phydev, pwe_init2[i].weg, pwe_init2[i].vaw);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg &= ~TW_CWK_DISABWE;
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* end of wwite bwoadcasting */
	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg &= ~SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	wet = wequest_fiwmwawe(&fw, MSCC_VSC8584_WEVB_INT8051_FW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to woad fiwmwawe %s, wet: %d\n",
			MSCC_VSC8584_WEVB_INT8051_FW, wet);
		wetuwn wet;
	}

	/* Add one byte to size fow the one added by the patch_fw function */
	wet = vsc8584_get_fw_cwc(phydev,
				 MSCC_VSC8584_WEVB_INT8051_FW_STAWT_ADDW,
				 fw->size + 1, &cwc);
	if (wet)
		goto out;

	if (cwc != MSCC_VSC8584_WEVB_INT8051_FW_CWC) {
		dev_dbg(dev, "FW CWC is not the expected one, patching FW\n");
		if (vsc8584_patch_fw(phydev, fw))
			dev_wawn(dev,
				 "faiwed to patch FW, expect non-optimaw device\n");
	}

	vsc8584_micwo_deassewt_weset(phydev, fawse);

	/* Add one byte to size fow the one added by the patch_fw function */
	wet = vsc8584_get_fw_cwc(phydev,
				 MSCC_VSC8584_WEVB_INT8051_FW_STAWT_ADDW,
				 fw->size + 1, &cwc);
	if (wet)
		goto out;

	if (cwc != MSCC_VSC8584_WEVB_INT8051_FW_CWC)
		dev_wawn(dev,
			 "FW CWC aftew patching is not the expected one, expect non-optimaw device\n");

	wet = vsc8584_micwo_assewt_weset(phydev);
	if (wet)
		goto out;

	/* Wwite patch vectow 0, to skip IB caw powwing  */
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_GPIO);
	weg = MSCC_WOM_TWAP_SEWDES_6G_CFG; /* WOM addwess to twap, fow patch vectow 0 */
	wet = phy_base_wwite(phydev, MSCC_TWAP_WOM_ADDW(1), weg);
	if (wet)
		goto out;

	weg = MSCC_WAM_TWAP_SEWDES_6G_CFG; /* WAM addwess to jump to, when patch vectow 0 enabwed */
	wet = phy_base_wwite(phydev, MSCC_PATCH_WAM_ADDW(1), weg);
	if (wet)
		goto out;

	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	weg |= PATCH_VEC_ZEWO_EN; /* bit 8, enabwe patch vectow 0 */
	wet = phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, weg);
	if (wet)
		goto out;

	vsc8584_micwo_deassewt_weset(phydev, twue);

out:
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static void vsc8584_get_base_addw(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	u16 vaw, addw;

	phy_wock_mdio_bus(phydev);
	__phy_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	addw = __phy_wead(phydev, MSCC_PHY_EXT_PHY_CNTW_4);
	addw >>= PHY_CNTW_4_ADDW_POS;

	vaw = __phy_wead(phydev, MSCC_PHY_ACTIPHY_CNTW);

	__phy_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);
	phy_unwock_mdio_bus(phydev);

	/* In the package, thewe awe two paiws of PHYs (PHY0 + PHY2 and
	 * PHY1 + PHY3). The fiwst PHY of each paiw (PHY0 and PHY1) is
	 * the base PHY fow timestamping opewations.
	 */
	vsc8531->ts_base_addw = phydev->mdio.addw;
	vsc8531->ts_base_phy = addw;

	if (vaw & PHY_ADDW_WEVEWSED) {
		vsc8531->base_addw = phydev->mdio.addw + addw;
		if (addw > 1) {
			vsc8531->ts_base_addw += 2;
			vsc8531->ts_base_phy += 2;
		}
	} ewse {
		vsc8531->base_addw = phydev->mdio.addw - addw;
		if (addw > 1) {
			vsc8531->ts_base_addw -= 2;
			vsc8531->ts_base_phy -= 2;
		}
	}

	vsc8531->addw = addw;
}

static void vsc85xx_coma_mode_wewease(stwuct phy_device *phydev)
{
	/* The coma mode (pin ow weg) pwovides an optionaw featuwe that
	 * may be used to contwow when the PHYs become active.
	 * Awtewnativewy the COMA_MODE pin may be connected wow
	 * so that the PHYs awe fuwwy active once out of weset.
	 */

	/* Enabwe output (mode=0) and wwite zewo to it */
	vsc85xx_phy_wwite_page(phydev, MSCC_PHY_PAGE_EXTENDED_GPIO);
	__phy_modify(phydev, MSCC_PHY_GPIO_CONTWOW_2,
		     MSCC_PHY_COMA_MODE | MSCC_PHY_COMA_OUTPUT, 0);
	vsc85xx_phy_wwite_page(phydev, MSCC_PHY_PAGE_STANDAWD);
}

static int vsc8584_config_host_sewdes(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	int wet;
	u16 vaw;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	if (wet)
		wetuwn wet;

	vaw = phy_base_wead(phydev, MSCC_PHY_MAC_CFG_FASTWINK);
	vaw &= ~MAC_CFG_MASK;
	if (phydev->intewface == PHY_INTEWFACE_MODE_QSGMII) {
		vaw |= MAC_CFG_QSGMII;
	} ewse if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		vaw |= MAC_CFG_SGMII;
	} ewse {
		wet = -EINVAW;
		wetuwn wet;
	}

	wet = phy_base_wwite(phydev, MSCC_PHY_MAC_CFG_FASTWINK, vaw);
	if (wet)
		wetuwn wet;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDAWD);
	if (wet)
		wetuwn wet;

	vaw = PWOC_CMD_MCB_ACCESS_MAC_CONF | PWOC_CMD_WST_CONF_POWT |
		PWOC_CMD_WEAD_MOD_WWITE_POWT;
	if (phydev->intewface == PHY_INTEWFACE_MODE_QSGMII)
		vaw |= PWOC_CMD_QSGMII_MAC;
	ewse
		vaw |= PWOC_CMD_SGMII_MAC;

	wet = vsc8584_cmd(phydev, vaw);
	if (wet)
		wetuwn wet;

	usweep_wange(10000, 20000);

	/* Disabwe SewDes fow 100Base-FX */
	wet = vsc8584_cmd(phydev, PWOC_CMD_FIBEW_MEDIA_CONF |
			  PWOC_CMD_FIBEW_POWT(vsc8531->addw) |
			  PWOC_CMD_FIBEW_DISABWE |
			  PWOC_CMD_WEAD_MOD_WWITE_POWT |
			  PWOC_CMD_WST_CONF_POWT | PWOC_CMD_FIBEW_100BASE_FX);
	if (wet)
		wetuwn wet;

	/* Disabwe SewDes fow 1000Base-X */
	wet = vsc8584_cmd(phydev, PWOC_CMD_FIBEW_MEDIA_CONF |
			  PWOC_CMD_FIBEW_POWT(vsc8531->addw) |
			  PWOC_CMD_FIBEW_DISABWE |
			  PWOC_CMD_WEAD_MOD_WWITE_POWT |
			  PWOC_CMD_WST_CONF_POWT | PWOC_CMD_FIBEW_1000BASE_X);
	if (wet)
		wetuwn wet;

	wetuwn vsc85xx_sd6g_config_v2(phydev);
}

static int vsc8574_config_host_sewdes(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	int wet;
	u16 vaw;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	if (wet)
		wetuwn wet;

	vaw = phy_base_wead(phydev, MSCC_PHY_MAC_CFG_FASTWINK);
	vaw &= ~MAC_CFG_MASK;
	if (phydev->intewface == PHY_INTEWFACE_MODE_QSGMII) {
		vaw |= MAC_CFG_QSGMII;
	} ewse if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		vaw |= MAC_CFG_SGMII;
	} ewse if (phy_intewface_is_wgmii(phydev)) {
		vaw |= MAC_CFG_WGMII;
	} ewse {
		wet = -EINVAW;
		wetuwn wet;
	}

	wet = phy_base_wwite(phydev, MSCC_PHY_MAC_CFG_FASTWINK, vaw);
	if (wet)
		wetuwn wet;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDAWD);
	if (wet)
		wetuwn wet;

	if (!phy_intewface_is_wgmii(phydev)) {
		vaw = PWOC_CMD_MCB_ACCESS_MAC_CONF | PWOC_CMD_WST_CONF_POWT |
			PWOC_CMD_WEAD_MOD_WWITE_POWT;
		if (phydev->intewface == PHY_INTEWFACE_MODE_QSGMII)
			vaw |= PWOC_CMD_QSGMII_MAC;
		ewse
			vaw |= PWOC_CMD_SGMII_MAC;

		wet = vsc8584_cmd(phydev, vaw);
		if (wet)
			wetuwn wet;

		usweep_wange(10000, 20000);
	}

	/* Disabwe SewDes fow 100Base-FX */
	wet = vsc8584_cmd(phydev, PWOC_CMD_FIBEW_MEDIA_CONF |
			  PWOC_CMD_FIBEW_POWT(vsc8531->addw) |
			  PWOC_CMD_FIBEW_DISABWE |
			  PWOC_CMD_WEAD_MOD_WWITE_POWT |
			  PWOC_CMD_WST_CONF_POWT | PWOC_CMD_FIBEW_100BASE_FX);
	if (wet)
		wetuwn wet;

	/* Disabwe SewDes fow 1000Base-X */
	wetuwn vsc8584_cmd(phydev, PWOC_CMD_FIBEW_MEDIA_CONF |
			   PWOC_CMD_FIBEW_POWT(vsc8531->addw) |
			   PWOC_CMD_FIBEW_DISABWE |
			   PWOC_CMD_WEAD_MOD_WWITE_POWT |
			   PWOC_CMD_WST_CONF_POWT | PWOC_CMD_FIBEW_1000BASE_X);
}

static int vsc8584_config_init(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	int wet, i;
	u16 vaw;

	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	phy_wock_mdio_bus(phydev);

	/* Some pawts of the init sequence awe identicaw fow evewy PHY in the
	 * package. Some pawts awe modifying the GPIO wegistew bank which is a
	 * set of wegistews that awe affecting aww PHYs, a few wesetting the
	 * micwopwocessow common to aww PHYs. The CWC check wesponsibwe of the
	 * checking the fiwmwawe within the 8051 micwopwocessow can onwy be
	 * accessed via the PHY whose intewnaw addwess in the package is 0.
	 * Aww PHYs' intewwupts mask wegistew has to be zewoed befowe enabwing
	 * any PHY's intewwupt in this wegistew.
	 * Fow aww these weasons, we need to do the init sequence once and onwy
	 * once whatevew is the fiwst PHY in the package that is initiawized and
	 * do the cowwect init sequence fow aww PHYs that awe package-cwiticaw
	 * in this pwe-init function.
	 */
	if (phy_package_init_once(phydev)) {
		/* The fowwowing switch statement assumes that the wowest
		 * nibbwe of the phy_id_mask is awways 0. This wowks because
		 * the wowest nibbwe of the PHY_ID's bewow awe awso 0.
		 */
		WAWN_ON(phydev->dwv->phy_id_mask & 0xf);

		switch (phydev->phy_id & phydev->dwv->phy_id_mask) {
		case PHY_ID_VSC8504:
		case PHY_ID_VSC8552:
		case PHY_ID_VSC8572:
		case PHY_ID_VSC8574:
			wet = vsc8574_config_pwe_init(phydev);
			if (wet)
				goto eww;
			wet = vsc8574_config_host_sewdes(phydev);
			if (wet)
				goto eww;
			bweak;
		case PHY_ID_VSC856X:
		case PHY_ID_VSC8575:
		case PHY_ID_VSC8582:
		case PHY_ID_VSC8584:
			wet = vsc8584_config_pwe_init(phydev);
			if (wet)
				goto eww;
			wet = vsc8584_config_host_sewdes(phydev);
			if (wet)
				goto eww;
			vsc85xx_coma_mode_wewease(phydev);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		if (wet)
			goto eww;
	}

	phy_unwock_mdio_bus(phydev);

	wet = vsc8584_macsec_init(phydev);
	if (wet)
		wetuwn wet;

	wet = vsc8584_ptp_init(phydev);
	if (wet)
		wetuwn wet;

	vaw = phy_wead(phydev, MSCC_PHY_EXT_PHY_CNTW_1);
	vaw &= ~(MEDIA_OP_MODE_MASK | VSC8584_MAC_IF_SEWECTION_MASK);
	vaw |= (MEDIA_OP_MODE_COPPEW << MEDIA_OP_MODE_POS) |
	       (VSC8584_MAC_IF_SEWECTION_SGMII << VSC8584_MAC_IF_SEWECTION_POS);
	wet = phy_wwite(phydev, MSCC_PHY_EXT_PHY_CNTW_1, vaw);
	if (wet)
		wetuwn wet;

	wet = vsc85xx_update_wgmii_cntw(phydev, VSC8572_WGMII_CNTW,
					VSC8572_WGMII_WX_DEWAY_MASK,
					VSC8572_WGMII_TX_DEWAY_MASK);
	if (wet)
		wetuwn wet;

	wet = genphy_soft_weset(phydev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < vsc8531->nweds; i++) {
		wet = vsc85xx_wed_cntw_set(phydev, i, vsc8531->weds_mode[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;

eww:
	phy_unwock_mdio_bus(phydev);
	wetuwn wet;
}

static iwqwetuwn_t vsc8584_handwe_intewwupt(stwuct phy_device *phydev)
{
	iwqwetuwn_t wet;
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_VSC85XX_INT_STATUS);
	if (iwq_status < 0)
		wetuwn IWQ_NONE;

	/* Timestamping IWQ does not set a bit in the gwobaw INT_STATUS, so
	 * iwq_status wouwd be 0.
	 */
	wet = vsc8584_handwe_ts_intewwupt(phydev);
	if (!(iwq_status & MII_VSC85XX_INT_MASK_MASK))
		wetuwn wet;

	if (iwq_status & MII_VSC85XX_INT_MASK_EXT)
		vsc8584_handwe_macsec_intewwupt(phydev);

	if (iwq_status & MII_VSC85XX_INT_MASK_WINK_CHG)
		phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int vsc85xx_config_init(stwuct phy_device *phydev)
{
	int wc, i, phy_id;
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;

	wc = vsc85xx_defauwt_config(phydev);
	if (wc)
		wetuwn wc;

	wc = vsc85xx_mac_if_set(phydev, phydev->intewface);
	if (wc)
		wetuwn wc;

	wc = vsc85xx_edge_wate_cntw_set(phydev, vsc8531->wate_magic);
	if (wc)
		wetuwn wc;

	phy_id = phydev->dwv->phy_id & phydev->dwv->phy_id_mask;
	if (PHY_ID_VSC8531 == phy_id || PHY_ID_VSC8541 == phy_id ||
	    PHY_ID_VSC8530 == phy_id || PHY_ID_VSC8540 == phy_id) {
		wc = vsc8531_pwe_init_seq_set(phydev);
		if (wc)
			wetuwn wc;
	}

	wc = vsc85xx_eee_init_seq_set(phydev);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < vsc8531->nweds; i++) {
		wc = vsc85xx_wed_cntw_set(phydev, i, vsc8531->weds_mode[i]);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int __phy_wwite_mcb_s6g(stwuct phy_device *phydev, u32 weg, u8 mcb,
			       u32 op)
{
	unsigned wong deadwine;
	u32 vaw;
	int wet;

	wet = vsc85xx_csw_wwite(phydev, PHY_MCB_TAWGET, weg,
				op | (1 << mcb));
	if (wet)
		wetuwn -EINVAW;

	deadwine = jiffies + msecs_to_jiffies(PWOC_CMD_NCOMPWETED_TIMEOUT_MS);
	do {
		usweep_wange(500, 1000);
		vaw = vsc85xx_csw_wead(phydev, PHY_MCB_TAWGET, weg);

		if (vaw == 0xffffffff)
			wetuwn -EIO;

	} whiwe (time_befowe(jiffies, deadwine) && (vaw & op));

	if (vaw & op)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/* Twiggew a wead to the specified MCB */
int phy_update_mcb_s6g(stwuct phy_device *phydev, u32 weg, u8 mcb)
{
	wetuwn __phy_wwite_mcb_s6g(phydev, weg, mcb, PHY_MCB_S6G_WEAD);
}

/* Twiggew a wwite to the specified MCB */
int phy_commit_mcb_s6g(stwuct phy_device *phydev, u32 weg, u8 mcb)
{
	wetuwn __phy_wwite_mcb_s6g(phydev, weg, mcb, PHY_MCB_S6G_WWITE);
}

static int vsc8514_config_host_sewdes(stwuct phy_device *phydev)
{
	int wet;
	u16 vaw;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	if (wet)
		wetuwn wet;

	vaw = phy_base_wead(phydev, MSCC_PHY_MAC_CFG_FASTWINK);
	vaw &= ~MAC_CFG_MASK;
	vaw |= MAC_CFG_QSGMII;
	wet = phy_base_wwite(phydev, MSCC_PHY_MAC_CFG_FASTWINK, vaw);
	if (wet)
		wetuwn wet;

	wet = phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDAWD);
	if (wet)
		wetuwn wet;

	wet = vsc8584_cmd(phydev, PWOC_CMD_NOP);
	if (wet)
		wetuwn wet;

	wet = vsc8584_cmd(phydev,
			  PWOC_CMD_MCB_ACCESS_MAC_CONF |
			  PWOC_CMD_WST_CONF_POWT |
			  PWOC_CMD_WEAD_MOD_WWITE_POWT | PWOC_CMD_QSGMII_MAC);
	if (wet) {
		dev_eww(&phydev->mdio.dev, "%s: QSGMII ewwow: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	/* Appwy 6G SewDes FOJI Awgowithm
	 *  Initiaw condition wequiwement:
	 *  1. howd 8051 in weset
	 *  2. disabwe patch vectow 0, in owdew to awwow IB caw poww duwing FoJi
	 *  3. deassewt 8051 weset aftew change patch vectow status
	 *  4. pwoceed with FoJi (vsc85xx_sd6g_config_v2)
	 */
	vsc8584_micwo_assewt_weset(phydev);
	vaw = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	/* cweaw bit 8, to disabwe patch vectow 0 */
	vaw &= ~PATCH_VEC_ZEWO_EN;
	wet = phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, vaw);
	/* Enabwe 8051 cwock, don't set patch pwesent, disabwe PWAM cwock ovewwide */
	vsc8584_micwo_deassewt_weset(phydev, fawse);

	wetuwn vsc85xx_sd6g_config_v2(phydev);
}

static int vsc8514_config_pwe_init(stwuct phy_device *phydev)
{
	/* These awe the settings to ovewwide the siwicon defauwt
	 * vawues to handwe hawdwawe pewfowmance of PHY. They
	 * awe set at Powew-On state and wemain untiw PHY Weset.
	 */
	static const stwuct weg_vaw pwe_init1[] = {
		{0x0f90, 0x00688980},
		{0x0786, 0x00000003},
		{0x07fa, 0x0050100f},
		{0x0f82, 0x0012b002},
		{0x1686, 0x00000004},
		{0x168c, 0x00d2c46f},
		{0x17a2, 0x00000620},
		{0x16a0, 0x00eeffdd},
		{0x16a6, 0x00071448},
		{0x16a4, 0x0013132f},
		{0x16a8, 0x00000000},
		{0x0ffc, 0x00c0a028},
		{0x0fe8, 0x0091b06c},
		{0x0fea, 0x00041600},
		{0x0f80, 0x00fffaff},
		{0x0fec, 0x00901809},
		{0x0ffe, 0x00b01007},
		{0x16b0, 0x00eeff00},
		{0x16b2, 0x00007000},
		{0x16b4, 0x00000814},
	};
	stwuct device *dev = &phydev->mdio.dev;
	unsigned int i;
	u16 weg;
	int wet;

	wet = vsc8584_pww5g_weset(phydev);
	if (wet < 0) {
		dev_eww(dev, "faiwed WCPWW weset, wet: %d\n", wet);
		wetuwn wet;
	}

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	/* aww wwites bewow awe bwoadcasted to aww PHYs in the same package */
	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg |= SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg |= BIT(15);
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TW);

	fow (i = 0; i < AWWAY_SIZE(pwe_init1); i++)
		vsc8584_csw_wwite(phydev, pwe_init1[i].weg, pwe_init1[i].vaw);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	weg = phy_base_wead(phydev, MSCC_PHY_TEST_PAGE_8);
	weg &= ~BIT(15);
	phy_base_wwite(phydev, MSCC_PHY_TEST_PAGE_8, weg);

	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	weg = phy_base_wead(phydev, MSCC_PHY_EXT_CNTW_STATUS);
	weg &= ~SMI_BWOADCAST_WW_EN;
	phy_base_wwite(phydev, MSCC_PHY_EXT_CNTW_STATUS, weg);

	/* Add pwe-patching commands to:
	 * 1. enabwe 8051 cwock, opewate 8051 cwock at 125 MHz
	 * instead of HW defauwt 62.5MHz
	 * 2. wwite patch vectow 0, to skip IB caw powwing executed
	 * as pawt of the 0x80E0 WOM command
	 */
	vsc8584_micwo_deassewt_weset(phydev, fawse);

	vsc8584_micwo_assewt_weset(phydev);
	phy_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);
	/* WOM addwess to twap, fow patch vectow 0 */
	weg = MSCC_WOM_TWAP_SEWDES_6G_CFG;
	wet = phy_base_wwite(phydev, MSCC_TWAP_WOM_ADDW(1), weg);
	if (wet)
		goto eww;
	/* WAM addwess to jump to, when patch vectow 0 enabwed */
	weg = MSCC_WAM_TWAP_SEWDES_6G_CFG;
	wet = phy_base_wwite(phydev, MSCC_PATCH_WAM_ADDW(1), weg);
	if (wet)
		goto eww;
	weg = phy_base_wead(phydev, MSCC_INT_MEM_CNTW);
	weg |= PATCH_VEC_ZEWO_EN; /* bit 8, enabwe patch vectow 0 */
	wet = phy_base_wwite(phydev, MSCC_INT_MEM_CNTW, weg);
	if (wet)
		goto eww;

	/* Enabwe 8051 cwock, don't set patch pwesent
	 * yet, disabwe PWAM cwock ovewwide
	 */
	vsc8584_micwo_deassewt_weset(phydev, fawse);
	wetuwn wet;
 eww:
	/* westowe 8051 and baiw w ewwow */
	vsc8584_micwo_deassewt_weset(phydev, fawse);
	wetuwn wet;
}

static int vsc8514_config_init(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	int wet, i;

	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	phy_wock_mdio_bus(phydev);

	/* Some pawts of the init sequence awe identicaw fow evewy PHY in the
	 * package. Some pawts awe modifying the GPIO wegistew bank which is a
	 * set of wegistews that awe affecting aww PHYs, a few wesetting the
	 * micwopwocessow common to aww PHYs.
	 * Aww PHYs' intewwupts mask wegistew has to be zewoed befowe enabwing
	 * any PHY's intewwupt in this wegistew.
	 * Fow aww these weasons, we need to do the init sequence once and onwy
	 * once whatevew is the fiwst PHY in the package that is initiawized and
	 * do the cowwect init sequence fow aww PHYs that awe package-cwiticaw
	 * in this pwe-init function.
	 */
	if (phy_package_init_once(phydev)) {
		wet = vsc8514_config_pwe_init(phydev);
		if (wet)
			goto eww;
		wet = vsc8514_config_host_sewdes(phydev);
		if (wet)
			goto eww;
		vsc85xx_coma_mode_wewease(phydev);
	}

	phy_unwock_mdio_bus(phydev);

	wet = phy_modify(phydev, MSCC_PHY_EXT_PHY_CNTW_1, MEDIA_OP_MODE_MASK,
			 MEDIA_OP_MODE_COPPEW << MEDIA_OP_MODE_POS);

	if (wet)
		wetuwn wet;

	wet = genphy_soft_weset(phydev);

	if (wet)
		wetuwn wet;

	fow (i = 0; i < vsc8531->nweds; i++) {
		wet = vsc85xx_wed_cntw_set(phydev, i, vsc8531->weds_mode[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;

eww:
	phy_unwock_mdio_bus(phydev);
	wetuwn wet;
}

static int vsc85xx_ack_intewwupt(stwuct phy_device *phydev)
{
	int wc = 0;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED)
		wc = phy_wead(phydev, MII_VSC85XX_INT_STATUS);

	wetuwn (wc < 0) ? wc : 0;
}

static int vsc85xx_config_intw(stwuct phy_device *phydev)
{
	int wc;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		wc = vsc85xx_ack_intewwupt(phydev);
		if (wc)
			wetuwn wc;

		vsc8584_config_macsec_intw(phydev);
		vsc8584_config_ts_intw(phydev);

		wc = phy_wwite(phydev, MII_VSC85XX_INT_MASK,
			       MII_VSC85XX_INT_MASK_MASK);
	} ewse {
		wc = phy_wwite(phydev, MII_VSC85XX_INT_MASK, 0);
		if (wc < 0)
			wetuwn wc;
		wc = phy_wead(phydev, MII_VSC85XX_INT_STATUS);
		if (wc < 0)
			wetuwn wc;

		wc = vsc85xx_ack_intewwupt(phydev);
	}

	wetuwn wc;
}

static iwqwetuwn_t vsc85xx_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_VSC85XX_INT_STATUS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_VSC85XX_INT_MASK_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int vsc85xx_config_aneg(stwuct phy_device *phydev)
{
	int wc;

	wc = vsc85xx_mdix_set(phydev, phydev->mdix_ctww);
	if (wc < 0)
		wetuwn wc;

	wetuwn genphy_config_aneg(phydev);
}

static int vsc85xx_wead_status(stwuct phy_device *phydev)
{
	int wc;

	wc = vsc85xx_mdix_get(phydev, &phydev->mdix);
	if (wc < 0)
		wetuwn wc;

	wetuwn genphy_wead_status(phydev);
}

static int vsc8514_pwobe(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531;
	u32 defauwt_mode[4] = {VSC8531_WINK_1000_ACTIVITY,
	   VSC8531_WINK_100_ACTIVITY, VSC8531_WINK_ACTIVITY,
	   VSC8531_DUPWEX_COWWISION};

	vsc8531 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KEWNEW);
	if (!vsc8531)
		wetuwn -ENOMEM;

	phydev->pwiv = vsc8531;

	vsc8584_get_base_addw(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev,
			      vsc8531->base_addw, 0);

	vsc8531->nweds = 4;
	vsc8531->supp_wed_modes = VSC85XX_SUPP_WED_MODES;
	vsc8531->hw_stats = vsc85xx_hw_stats;
	vsc8531->nstats = AWWAY_SIZE(vsc85xx_hw_stats);
	vsc8531->stats = devm_kcawwoc(&phydev->mdio.dev, vsc8531->nstats,
				      sizeof(u64), GFP_KEWNEW);
	if (!vsc8531->stats)
		wetuwn -ENOMEM;

	wetuwn vsc85xx_dt_wed_modes_get(phydev, defauwt_mode);
}

static int vsc8574_pwobe(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531;
	u32 defauwt_mode[4] = {VSC8531_WINK_1000_ACTIVITY,
	   VSC8531_WINK_100_ACTIVITY, VSC8531_WINK_ACTIVITY,
	   VSC8531_DUPWEX_COWWISION};

	vsc8531 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KEWNEW);
	if (!vsc8531)
		wetuwn -ENOMEM;

	phydev->pwiv = vsc8531;

	vsc8584_get_base_addw(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev,
			      vsc8531->base_addw, 0);

	vsc8531->nweds = 4;
	vsc8531->supp_wed_modes = VSC8584_SUPP_WED_MODES;
	vsc8531->hw_stats = vsc8584_hw_stats;
	vsc8531->nstats = AWWAY_SIZE(vsc8584_hw_stats);
	vsc8531->stats = devm_kcawwoc(&phydev->mdio.dev, vsc8531->nstats,
				      sizeof(u64), GFP_KEWNEW);
	if (!vsc8531->stats)
		wetuwn -ENOMEM;

	wetuwn vsc85xx_dt_wed_modes_get(phydev, defauwt_mode);
}

static int vsc8584_pwobe(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531;
	u32 defauwt_mode[4] = {VSC8531_WINK_1000_ACTIVITY,
	   VSC8531_WINK_100_ACTIVITY, VSC8531_WINK_ACTIVITY,
	   VSC8531_DUPWEX_COWWISION};
	int wet;

	if ((phydev->phy_id & MSCC_DEV_WEV_MASK) != VSC8584_WEVB) {
		dev_eww(&phydev->mdio.dev, "Onwy VSC8584 wevB is suppowted.\n");
		wetuwn -ENOTSUPP;
	}

	vsc8531 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KEWNEW);
	if (!vsc8531)
		wetuwn -ENOMEM;

	phydev->pwiv = vsc8531;

	vsc8584_get_base_addw(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev, vsc8531->base_addw,
			      sizeof(stwuct vsc85xx_shawed_pwivate));

	vsc8531->nweds = 4;
	vsc8531->supp_wed_modes = VSC8584_SUPP_WED_MODES;
	vsc8531->hw_stats = vsc8584_hw_stats;
	vsc8531->nstats = AWWAY_SIZE(vsc8584_hw_stats);
	vsc8531->stats = devm_kcawwoc(&phydev->mdio.dev, vsc8531->nstats,
				      sizeof(u64), GFP_KEWNEW);
	if (!vsc8531->stats)
		wetuwn -ENOMEM;

	if (phy_package_pwobe_once(phydev)) {
		wet = vsc8584_ptp_pwobe_once(phydev);
		if (wet)
			wetuwn wet;
	}

	wet = vsc8584_ptp_pwobe(phydev);
	if (wet)
		wetuwn wet;

	wetuwn vsc85xx_dt_wed_modes_get(phydev, defauwt_mode);
}

static int vsc85xx_pwobe(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531;
	int wate_magic;
	u32 defauwt_mode[2] = {VSC8531_WINK_1000_ACTIVITY,
	   VSC8531_WINK_100_ACTIVITY};

	wate_magic = vsc85xx_edge_wate_magic_get(phydev);
	if (wate_magic < 0)
		wetuwn wate_magic;

	vsc8531 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KEWNEW);
	if (!vsc8531)
		wetuwn -ENOMEM;

	phydev->pwiv = vsc8531;

	vsc8531->wate_magic = wate_magic;
	vsc8531->nweds = 2;
	vsc8531->supp_wed_modes = VSC85XX_SUPP_WED_MODES;
	vsc8531->hw_stats = vsc85xx_hw_stats;
	vsc8531->nstats = AWWAY_SIZE(vsc85xx_hw_stats);
	vsc8531->stats = devm_kcawwoc(&phydev->mdio.dev, vsc8531->nstats,
				      sizeof(u64), GFP_KEWNEW);
	if (!vsc8531->stats)
		wetuwn -ENOMEM;

	wetuwn vsc85xx_dt_wed_modes_get(phydev, defauwt_mode);
}

/* Micwosemi VSC85xx PHYs */
static stwuct phy_dwivew vsc85xx_dwivew[] = {
{
	.phy_id		= PHY_ID_VSC8501,
	.name		= "Micwosemi GE VSC8501 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw	= &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8502,
	.name		= "Micwosemi GE VSC8502 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw	= &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8504,
	.name		= "Micwosemi GE VSC8504 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8574_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8514,
	.name		= "Micwosemi GE VSC8514 SyncE",
	.phy_id_mask	= 0xfffffff0,
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8514_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8514_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page      = &vsc85xx_phy_wead_page,
	.wwite_page     = &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8530,
	.name		= "Micwosemi FE VSC8530",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw	= &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8531,
	.name		= "Micwosemi VSC8531",
	.phy_id_mask    = 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8540,
	.name		= "Micwosemi FE VSC8540 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg	= &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw	= &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8541,
	.name		= "Micwosemi VSC8541 SyncE",
	.phy_id_mask    = 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc85xx_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8552,
	.name		= "Micwosemi GE VSC8552 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8574_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC856X,
	.name		= "Micwosemi GE VSC856X SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8584_pwobe,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8572,
	.name		= "Micwosemi GE VSC8572 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = &vsc8584_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8574_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8574,
	.name		= "Micwosemi GE VSC8574 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = vsc85xx_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8574_pwobe,
	.set_wow	= &vsc85xx_wow_set,
	.get_wow	= &vsc85xx_wow_get,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8575,
	.name		= "Micwosemi GE VSC8575 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = &vsc8584_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8584_pwobe,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8582,
	.name		= "Micwosemi GE VSC8582 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = &vsc8584_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8584_pwobe,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
},
{
	.phy_id		= PHY_ID_VSC8584,
	.name		= "Micwosemi GE VSC8584 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.soft_weset	= &genphy_soft_weset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_done	= &genphy_aneg_done,
	.wead_status	= &vsc85xx_wead_status,
	.handwe_intewwupt = &vsc8584_handwe_intewwupt,
	.config_intw    = &vsc85xx_config_intw,
	.suspend	= &genphy_suspend,
	.wesume		= &genphy_wesume,
	.pwobe		= &vsc8584_pwobe,
	.get_tunabwe	= &vsc85xx_get_tunabwe,
	.set_tunabwe	= &vsc85xx_set_tunabwe,
	.wead_page	= &vsc85xx_phy_wead_page,
	.wwite_page	= &vsc85xx_phy_wwite_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_stwings    = &vsc85xx_get_stwings,
	.get_stats      = &vsc85xx_get_stats,
	.wink_change_notify = &vsc85xx_wink_change_notify,
}

};

moduwe_phy_dwivew(vsc85xx_dwivew);

static stwuct mdio_device_id __maybe_unused vsc85xx_tbw[] = {
	{ PHY_ID_MATCH_VENDOW(PHY_VENDOW_MSCC) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, vsc85xx_tbw);

MODUWE_DESCWIPTION("Micwosemi VSC85xx PHY dwivew");
MODUWE_AUTHOW("Nagawaju Wakkawaju");
MODUWE_WICENSE("Duaw MIT/GPW");

MODUWE_FIWMWAWE(MSCC_VSC8584_WEVB_INT8051_FW);
MODUWE_FIWMWAWE(MSCC_VSC8574_WEVB_INT8051_FW);
