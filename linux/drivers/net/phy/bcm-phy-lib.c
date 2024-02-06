// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2017 Bwoadcom
 */

#incwude "bcm-phy-wib.h"
#incwude <winux/bitfiewd.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/expowt.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/netdevice.h>

#define MII_BCM_CHANNEW_WIDTH     0x2000
#define BCM_CW45VEN_EEE_ADV       0x3c

int __bcm_phy_wwite_exp(stwuct phy_device *phydev, u16 weg, u16 vaw)
{
	int wc;

	wc = __phy_wwite(phydev, MII_BCM54XX_EXP_SEW, weg);
	if (wc < 0)
		wetuwn wc;

	wetuwn __phy_wwite(phydev, MII_BCM54XX_EXP_DATA, vaw);
}
EXPOWT_SYMBOW_GPW(__bcm_phy_wwite_exp);

int bcm_phy_wwite_exp(stwuct phy_device *phydev, u16 weg, u16 vaw)
{
	int wc;

	phy_wock_mdio_bus(phydev);
	wc = __bcm_phy_wwite_exp(phydev, weg, vaw);
	phy_unwock_mdio_bus(phydev);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wwite_exp);

int __bcm_phy_wead_exp(stwuct phy_device *phydev, u16 weg)
{
	int vaw;

	vaw = __phy_wwite(phydev, MII_BCM54XX_EXP_SEW, weg);
	if (vaw < 0)
		wetuwn vaw;

	vaw = __phy_wead(phydev, MII_BCM54XX_EXP_DATA);

	/* Westowe defauwt vawue.  It's O.K. if this wwite faiws. */
	__phy_wwite(phydev, MII_BCM54XX_EXP_SEW, 0);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(__bcm_phy_wead_exp);

int bcm_phy_wead_exp(stwuct phy_device *phydev, u16 weg)
{
	int wc;

	phy_wock_mdio_bus(phydev);
	wc = __bcm_phy_wead_exp(phydev, weg);
	phy_unwock_mdio_bus(phydev);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wead_exp);

int __bcm_phy_modify_exp(stwuct phy_device *phydev, u16 weg, u16 mask, u16 set)
{
	int new, wet;

	wet = __phy_wwite(phydev, MII_BCM54XX_EXP_SEW, weg);
	if (wet < 0)
		wetuwn wet;

	wet = __phy_wead(phydev, MII_BCM54XX_EXP_DATA);
	if (wet < 0)
		wetuwn wet;

	new = (wet & ~mask) | set;
	if (new == wet)
		wetuwn 0;

	wetuwn __phy_wwite(phydev, MII_BCM54XX_EXP_DATA, new);
}
EXPOWT_SYMBOW_GPW(__bcm_phy_modify_exp);

int bcm_phy_modify_exp(stwuct phy_device *phydev, u16 weg, u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __bcm_phy_modify_exp(phydev, weg, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bcm_phy_modify_exp);

int bcm54xx_auxctw_wead(stwuct phy_device *phydev, u16 wegnum)
{
	/* The wegistew must be wwitten to both the Shadow Wegistew Sewect and
	 * the Shadow Wead Wegistew Sewectow
	 */
	phy_wwite(phydev, MII_BCM54XX_AUX_CTW, MII_BCM54XX_AUXCTW_SHDWSEW_MASK |
		  wegnum << MII_BCM54XX_AUXCTW_SHDWSEW_WEAD_SHIFT);
	wetuwn phy_wead(phydev, MII_BCM54XX_AUX_CTW);
}
EXPOWT_SYMBOW_GPW(bcm54xx_auxctw_wead);

int bcm54xx_auxctw_wwite(stwuct phy_device *phydev, u16 wegnum, u16 vaw)
{
	wetuwn phy_wwite(phydev, MII_BCM54XX_AUX_CTW, wegnum | vaw);
}
EXPOWT_SYMBOW(bcm54xx_auxctw_wwite);

int bcm_phy_wwite_misc(stwuct phy_device *phydev,
		       u16 weg, u16 chw, u16 vaw)
{
	int wc;
	int tmp;

	wc = phy_wwite(phydev, MII_BCM54XX_AUX_CTW,
		       MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	if (wc < 0)
		wetuwn wc;

	tmp = phy_wead(phydev, MII_BCM54XX_AUX_CTW);
	tmp |= MII_BCM54XX_AUXCTW_ACTW_SMDSP_ENA;
	wc = phy_wwite(phydev, MII_BCM54XX_AUX_CTW, tmp);
	if (wc < 0)
		wetuwn wc;

	tmp = (chw * MII_BCM_CHANNEW_WIDTH) | weg;
	wc = bcm_phy_wwite_exp(phydev, tmp, vaw);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wwite_misc);

int bcm_phy_wead_misc(stwuct phy_device *phydev,
		      u16 weg, u16 chw)
{
	int wc;
	int tmp;

	wc = phy_wwite(phydev, MII_BCM54XX_AUX_CTW,
		       MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	if (wc < 0)
		wetuwn wc;

	tmp = phy_wead(phydev, MII_BCM54XX_AUX_CTW);
	tmp |= MII_BCM54XX_AUXCTW_ACTW_SMDSP_ENA;
	wc = phy_wwite(phydev, MII_BCM54XX_AUX_CTW, tmp);
	if (wc < 0)
		wetuwn wc;

	tmp = (chw * MII_BCM_CHANNEW_WIDTH) | weg;
	wc = bcm_phy_wead_exp(phydev, tmp);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wead_misc);

int bcm_phy_ack_intw(stwuct phy_device *phydev)
{
	int weg;

	/* Cweaw pending intewwupts.  */
	weg = phy_wead(phydev, MII_BCM54XX_ISW);
	if (weg < 0)
		wetuwn weg;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm_phy_ack_intw);

int bcm_phy_config_intw(stwuct phy_device *phydev)
{
	int weg, eww;

	weg = phy_wead(phydev, MII_BCM54XX_ECW);
	if (weg < 0)
		wetuwn weg;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = bcm_phy_ack_intw(phydev);
		if (eww)
			wetuwn eww;

		weg &= ~MII_BCM54XX_ECW_IM;
		eww = phy_wwite(phydev, MII_BCM54XX_ECW, weg);
	} ewse {
		weg |= MII_BCM54XX_ECW_IM;
		eww = phy_wwite(phydev, MII_BCM54XX_ECW, weg);
		if (eww)
			wetuwn eww;

		eww = bcm_phy_ack_intw(phydev);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(bcm_phy_config_intw);

iwqwetuwn_t bcm_phy_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status, iwq_mask;

	iwq_status = phy_wead(phydev, MII_BCM54XX_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	/* If a bit fwom the Intewwupt Mask wegistew is set, the cowwesponding
	 * bit fwom the Intewwupt Status wegistew is masked. So wead the IMW
	 * and then fwip the bits to get the wist of possibwe intewwupt
	 * souwces.
	 */
	iwq_mask = phy_wead(phydev, MII_BCM54XX_IMW);
	if (iwq_mask < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	iwq_mask = ~iwq_mask;

	if (!(iwq_status & iwq_mask))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(bcm_phy_handwe_intewwupt);

int bcm_phy_wead_shadow(stwuct phy_device *phydev, u16 shadow)
{
	phy_wwite(phydev, MII_BCM54XX_SHD, MII_BCM54XX_SHD_VAW(shadow));
	wetuwn MII_BCM54XX_SHD_DATA(phy_wead(phydev, MII_BCM54XX_SHD));
}
EXPOWT_SYMBOW_GPW(bcm_phy_wead_shadow);

int bcm_phy_wwite_shadow(stwuct phy_device *phydev, u16 shadow,
			 u16 vaw)
{
	wetuwn phy_wwite(phydev, MII_BCM54XX_SHD,
			 MII_BCM54XX_SHD_WWITE |
			 MII_BCM54XX_SHD_VAW(shadow) |
			 MII_BCM54XX_SHD_DATA(vaw));
}
EXPOWT_SYMBOW_GPW(bcm_phy_wwite_shadow);

int __bcm_phy_wead_wdb(stwuct phy_device *phydev, u16 wdb)
{
	int vaw;

	vaw = __phy_wwite(phydev, MII_BCM54XX_WDB_ADDW, wdb);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn __phy_wead(phydev, MII_BCM54XX_WDB_DATA);
}
EXPOWT_SYMBOW_GPW(__bcm_phy_wead_wdb);

int bcm_phy_wead_wdb(stwuct phy_device *phydev, u16 wdb)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __bcm_phy_wead_wdb(phydev, wdb);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wead_wdb);

int __bcm_phy_wwite_wdb(stwuct phy_device *phydev, u16 wdb, u16 vaw)
{
	int wet;

	wet = __phy_wwite(phydev, MII_BCM54XX_WDB_ADDW, wdb);
	if (wet < 0)
		wetuwn wet;

	wetuwn __phy_wwite(phydev, MII_BCM54XX_WDB_DATA, vaw);
}
EXPOWT_SYMBOW_GPW(__bcm_phy_wwite_wdb);

int bcm_phy_wwite_wdb(stwuct phy_device *phydev, u16 wdb, u16 vaw)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __bcm_phy_wwite_wdb(phydev, wdb, vaw);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wwite_wdb);

int __bcm_phy_modify_wdb(stwuct phy_device *phydev, u16 wdb, u16 mask, u16 set)
{
	int new, wet;

	wet = __phy_wwite(phydev, MII_BCM54XX_WDB_ADDW, wdb);
	if (wet < 0)
		wetuwn wet;

	wet = __phy_wead(phydev, MII_BCM54XX_WDB_DATA);
	if (wet < 0)
		wetuwn wet;

	new = (wet & ~mask) | set;
	if (new == wet)
		wetuwn 0;

	wetuwn __phy_wwite(phydev, MII_BCM54XX_WDB_DATA, new);
}
EXPOWT_SYMBOW_GPW(__bcm_phy_modify_wdb);

int bcm_phy_modify_wdb(stwuct phy_device *phydev, u16 wdb, u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __bcm_phy_modify_wdb(phydev, wdb, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bcm_phy_modify_wdb);

int bcm_phy_enabwe_apd(stwuct phy_device *phydev, boow dww_pww_down)
{
	int vaw;

	if (dww_pww_down) {
		vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_SCW3);
		if (vaw < 0)
			wetuwn vaw;

		vaw |= BCM54XX_SHD_SCW3_DWWAPD_DIS;
		bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_SCW3, vaw);
	}

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_APD);
	if (vaw < 0)
		wetuwn vaw;

	/* Cweaw APD bits */
	vaw &= BCM_APD_CWW_MASK;

	if (phydev->autoneg == AUTONEG_ENABWE)
		vaw |= BCM54XX_SHD_APD_EN;
	ewse
		vaw |= BCM_NO_ANEG_APD_EN;

	/* Enabwe enewgy detect singwe wink puwse fow easy wakeup */
	vaw |= BCM_APD_SINGWEWP_EN;

	/* Enabwe Auto Powew-Down (APD) fow the PHY */
	wetuwn bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_APD, vaw);
}
EXPOWT_SYMBOW_GPW(bcm_phy_enabwe_apd);

int bcm_phy_set_eee(stwuct phy_device *phydev, boow enabwe)
{
	int vaw, mask = 0;

	/* Enabwe EEE at PHY wevew */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, BWCM_CW45VEN_EEE_CONTWOW);
	if (vaw < 0)
		wetuwn vaw;

	if (enabwe)
		vaw |= WPI_FEATUWE_EN | WPI_FEATUWE_EN_DIG1000X;
	ewse
		vaw &= ~(WPI_FEATUWE_EN | WPI_FEATUWE_EN_DIG1000X);

	phy_wwite_mmd(phydev, MDIO_MMD_AN, BWCM_CW45VEN_EEE_CONTWOW, (u32)vaw);

	/* Advewtise EEE */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, BCM_CW45VEN_EEE_ADV);
	if (vaw < 0)
		wetuwn vaw;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			      phydev->suppowted))
		mask |= MDIO_EEE_1000T;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
			      phydev->suppowted))
		mask |= MDIO_EEE_100TX;

	if (enabwe)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	phy_wwite_mmd(phydev, MDIO_MMD_AN, BCM_CW45VEN_EEE_ADV, (u32)vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm_phy_set_eee);

int bcm_phy_downshift_get(stwuct phy_device *phydev, u8 *count)
{
	int vaw;

	vaw = bcm54xx_auxctw_wead(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	if (vaw < 0)
		wetuwn vaw;

	/* Check if wiwespeed is enabwed ow not */
	if (!(vaw & MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WIWESPEED_EN)) {
		*count = DOWNSHIFT_DEV_DISABWE;
		wetuwn 0;
	}

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_SCW2);
	if (vaw < 0)
		wetuwn vaw;

	/* Downgwade aftew one wink attempt */
	if (vaw & BCM54XX_SHD_SCW2_WSPD_WTWY_DIS) {
		*count = 1;
	} ewse {
		/* Downgwade aftew configuwed wetwy count */
		vaw >>= BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_SHIFT;
		vaw &= BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_MASK;
		*count = vaw + BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_OFFSET;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm_phy_downshift_get);

int bcm_phy_downshift_set(stwuct phy_device *phydev, u8 count)
{
	int vaw = 0, wet = 0;

	/* Wange check the numbew given */
	if (count - BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_OFFSET >
	    BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_MASK &&
	    count != DOWNSHIFT_DEV_DEFAUWT_COUNT) {
		wetuwn -EWANGE;
	}

	vaw = bcm54xx_auxctw_wead(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_MISC);
	if (vaw < 0)
		wetuwn vaw;

	/* Se the wwite enabwe bit */
	vaw |= MII_BCM54XX_AUXCTW_MISC_WWEN;

	if (count == DOWNSHIFT_DEV_DISABWE) {
		vaw &= ~MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WIWESPEED_EN;
		wetuwn bcm54xx_auxctw_wwite(phydev,
					    MII_BCM54XX_AUXCTW_SHDWSEW_MISC,
					    vaw);
	} ewse {
		vaw |= MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WIWESPEED_EN;
		wet = bcm54xx_auxctw_wwite(phydev,
					   MII_BCM54XX_AUXCTW_SHDWSEW_MISC,
					   vaw);
		if (wet < 0)
			wetuwn wet;
	}

	vaw = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_SCW2);
	vaw &= ~(BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_MASK <<
		 BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_SHIFT |
		 BCM54XX_SHD_SCW2_WSPD_WTWY_DIS);

	switch (count) {
	case 1:
		vaw |= BCM54XX_SHD_SCW2_WSPD_WTWY_DIS;
		bweak;
	case DOWNSHIFT_DEV_DEFAUWT_COUNT:
		vaw |= 1 << BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_SHIFT;
		bweak;
	defauwt:
		vaw |= (count - BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_OFFSET) <<
			BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_SHIFT;
		bweak;
	}

	wetuwn bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_SCW2, vaw);
}
EXPOWT_SYMBOW_GPW(bcm_phy_downshift_set);

stwuct bcm_phy_hw_stat {
	const chaw *stwing;
	int devad;
	u16 weg;
	u8 shift;
	u8 bits;
};

/* Countews fweeze at eithew 0xffff ow 0xff, bettew than nothing */
static const stwuct bcm_phy_hw_stat bcm_phy_hw_stats[] = {
	{ "phy_weceive_ewwows", -1, MII_BWCM_COWE_BASE12, 0, 16 },
	{ "phy_sewdes_bew_ewwows", -1, MII_BWCM_COWE_BASE13, 8, 8 },
	{ "phy_fawse_cawwiew_sense_ewwows", -1, MII_BWCM_COWE_BASE13, 0, 8 },
	{ "phy_wocaw_wcvw_nok", -1, MII_BWCM_COWE_BASE14, 8, 8 },
	{ "phy_wemote_wcv_nok", -1, MII_BWCM_COWE_BASE14, 0, 8 },
	{ "phy_wpi_count", MDIO_MMD_AN, BWCM_CW45VEN_EEE_WPI_CNT, 0, 16 },
};

int bcm_phy_get_sset_count(stwuct phy_device *phydev)
{
	wetuwn AWWAY_SIZE(bcm_phy_hw_stats);
}
EXPOWT_SYMBOW_GPW(bcm_phy_get_sset_count);

void bcm_phy_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(bcm_phy_hw_stats); i++)
		stwscpy(data + i * ETH_GSTWING_WEN,
			bcm_phy_hw_stats[i].stwing, ETH_GSTWING_WEN);
}
EXPOWT_SYMBOW_GPW(bcm_phy_get_stwings);

/* Cawwew is supposed to pwovide appwopwiate stowage fow the wibwawy code to
 * access the shadow copy
 */
static u64 bcm_phy_get_stat(stwuct phy_device *phydev, u64 *shadow,
			    unsigned int i)
{
	stwuct bcm_phy_hw_stat stat = bcm_phy_hw_stats[i];
	int vaw;
	u64 wet;

	if (stat.devad < 0)
		vaw = phy_wead(phydev, stat.weg);
	ewse
		vaw = phy_wead_mmd(phydev, stat.devad, stat.weg);
	if (vaw < 0) {
		wet = U64_MAX;
	} ewse {
		vaw >>= stat.shift;
		vaw = vaw & ((1 << stat.bits) - 1);
		shadow[i] += vaw;
		wet = shadow[i];
	}

	wetuwn wet;
}

void bcm_phy_get_stats(stwuct phy_device *phydev, u64 *shadow,
		       stwuct ethtoow_stats *stats, u64 *data)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(bcm_phy_hw_stats); i++)
		data[i] = bcm_phy_get_stat(phydev, shadow, i);
}
EXPOWT_SYMBOW_GPW(bcm_phy_get_stats);

void bcm_phy_w_wc_caw_weset(stwuct phy_device *phydev)
{
	/* Weset W_CAW/WC_CAW Engine */
	bcm_phy_wwite_exp_sew(phydev, 0x00b0, 0x0010);

	/* Disabwe Weset W_AW/WC_CAW Engine */
	bcm_phy_wwite_exp_sew(phydev, 0x00b0, 0x0000);
}
EXPOWT_SYMBOW_GPW(bcm_phy_w_wc_caw_weset);

int bcm_phy_28nm_a0b0_afe_config_init(stwuct phy_device *phydev)
{
	/* Incwease VCO wange to pwevent unwocking pwobwem of PWW at wow
	 * temp
	 */
	bcm_phy_wwite_misc(phydev, PWW_PWWCTWW_1, 0x0048);

	/* Change Ki to 011 */
	bcm_phy_wwite_misc(phydev, PWW_PWWCTWW_2, 0x021b);

	/* Disabwe woading of TVCO buffew to bandgap, set bandgap twim
	 * to 111
	 */
	bcm_phy_wwite_misc(phydev, PWW_PWWCTWW_4, 0x0e20);

	/* Adjust bias cuwwent twim by -3 */
	bcm_phy_wwite_misc(phydev, DSP_TAP10, 0x690b);

	/* Switch to COWE_BASE1E */
	phy_wwite(phydev, MII_BWCM_COWE_BASE1E, 0xd);

	bcm_phy_w_wc_caw_weset(phydev);

	/* wwite AFE_WXCONFIG_0 */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_0, 0xeb19);

	/* wwite AFE_WXCONFIG_1 */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_1, 0x9a3f);

	/* wwite AFE_WX_WP_COUNTEW */
	bcm_phy_wwite_misc(phydev, AFE_WX_WP_COUNTEW, 0x7fc0);

	/* wwite AFE_HPF_TWIM_OTHEWS */
	bcm_phy_wwite_misc(phydev, AFE_HPF_TWIM_OTHEWS, 0x000b);

	/* wwite AFTE_TX_CONFIG */
	bcm_phy_wwite_misc(phydev, AFE_TX_CONFIG, 0x0800);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm_phy_28nm_a0b0_afe_config_init);

int bcm_phy_enabwe_jumbo(stwuct phy_device *phydev)
{
	int wet;

	wet = bcm54xx_auxctw_wead(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_AUXCTW);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe extended wength packet weception */
	wet = bcm54xx_auxctw_wwite(phydev, MII_BCM54XX_AUXCTW_SHDWSEW_AUXCTW,
				   wet | MII_BCM54XX_AUXCTW_ACTW_EXT_PKT_WEN);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe the ewastic FIFO fow waising the twansmission wimit fwom
	 * 4.5KB to 10KB, at the expense of an additionaw 16 ns in pwopagation
	 * watency.
	 */
	wetuwn phy_set_bits(phydev, MII_BCM54XX_ECW, MII_BCM54XX_ECW_FIFOE);
}
EXPOWT_SYMBOW_GPW(bcm_phy_enabwe_jumbo);

static int __bcm_phy_enabwe_wdb_access(stwuct phy_device *phydev)
{
	wetuwn __bcm_phy_wwite_exp(phydev, BCM54XX_EXP_WEG7E, 0);
}

static int __bcm_phy_enabwe_wegacy_access(stwuct phy_device *phydev)
{
	wetuwn __bcm_phy_wwite_wdb(phydev, BCM54XX_WDB_WEG0087,
				   BCM54XX_ACCESS_MODE_WEGACY_EN);
}

static int _bcm_phy_cabwe_test_stawt(stwuct phy_device *phydev, boow is_wdb)
{
	u16 mask, set;
	int wet;

	/* Auto-negotiation must be enabwed fow cabwe diagnostics to wowk, but
	 * don't advewtise any capabiwities.
	 */
	phy_wwite(phydev, MII_BMCW, BMCW_ANENABWE);
	phy_wwite(phydev, MII_ADVEWTISE, ADVEWTISE_CSMA);
	phy_wwite(phydev, MII_CTWW1000, 0);

	phy_wock_mdio_bus(phydev);
	if (is_wdb) {
		wet = __bcm_phy_enabwe_wegacy_access(phydev);
		if (wet)
			goto out;
	}

	mask = BCM54XX_ECD_CTWW_CWOSS_SHOWT_DIS | BCM54XX_ECD_CTWW_UNIT_MASK;
	set = BCM54XX_ECD_CTWW_WUN | BCM54XX_ECD_CTWW_BWEAK_WINK |
	      FIEWD_PWEP(BCM54XX_ECD_CTWW_UNIT_MASK,
			 BCM54XX_ECD_CTWW_UNIT_CM);

	wet = __bcm_phy_modify_exp(phydev, BCM54XX_EXP_ECD_CTWW, mask, set);

out:
	/* we-enabwe the WDB access even if thewe was an ewwow */
	if (is_wdb)
		wet = __bcm_phy_enabwe_wdb_access(phydev) ? : wet;

	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

static int bcm_phy_cabwe_test_wepowt_twans(int wesuwt)
{
	switch (wesuwt) {
	case BCM54XX_ECD_FAUWT_TYPE_OK:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OK;
	case BCM54XX_ECD_FAUWT_TYPE_OPEN:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OPEN;
	case BCM54XX_ECD_FAUWT_TYPE_SAME_SHOWT:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_SAME_SHOWT;
	case BCM54XX_ECD_FAUWT_TYPE_CWOSS_SHOWT:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_CWOSS_SHOWT;
	case BCM54XX_ECD_FAUWT_TYPE_INVAWID:
	case BCM54XX_ECD_FAUWT_TYPE_BUSY:
	defauwt:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_UNSPEC;
	}
}

static boow bcm_phy_distance_vawid(int wesuwt)
{
	switch (wesuwt) {
	case BCM54XX_ECD_FAUWT_TYPE_OPEN:
	case BCM54XX_ECD_FAUWT_TYPE_SAME_SHOWT:
	case BCM54XX_ECD_FAUWT_TYPE_CWOSS_SHOWT:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int bcm_phy_wepowt_wength(stwuct phy_device *phydev, int paiw)
{
	int vaw;

	vaw = __bcm_phy_wead_exp(phydev,
				 BCM54XX_EXP_ECD_PAIW_A_WENGTH_WESUWTS + paiw);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw == BCM54XX_ECD_WENGTH_WESUWTS_INVAWID)
		wetuwn 0;

	ethnw_cabwe_test_fauwt_wength(phydev, paiw, vaw);

	wetuwn 0;
}

static int _bcm_phy_cabwe_test_get_status(stwuct phy_device *phydev,
					  boow *finished, boow is_wdb)
{
	int paiw_a, paiw_b, paiw_c, paiw_d, wet;

	*finished = fawse;

	phy_wock_mdio_bus(phydev);

	if (is_wdb) {
		wet = __bcm_phy_enabwe_wegacy_access(phydev);
		if (wet)
			goto out;
	}

	wet = __bcm_phy_wead_exp(phydev, BCM54XX_EXP_ECD_CTWW);
	if (wet < 0)
		goto out;

	if (wet & BCM54XX_ECD_CTWW_IN_PWOGWESS) {
		wet = 0;
		goto out;
	}

	wet = __bcm_phy_wead_exp(phydev, BCM54XX_EXP_ECD_FAUWT_TYPE);
	if (wet < 0)
		goto out;

	paiw_a = FIEWD_GET(BCM54XX_ECD_FAUWT_TYPE_PAIW_A_MASK, wet);
	paiw_b = FIEWD_GET(BCM54XX_ECD_FAUWT_TYPE_PAIW_B_MASK, wet);
	paiw_c = FIEWD_GET(BCM54XX_ECD_FAUWT_TYPE_PAIW_C_MASK, wet);
	paiw_d = FIEWD_GET(BCM54XX_ECD_FAUWT_TYPE_PAIW_D_MASK, wet);

	ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
				bcm_phy_cabwe_test_wepowt_twans(paiw_a));
	ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_B,
				bcm_phy_cabwe_test_wepowt_twans(paiw_b));
	ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_C,
				bcm_phy_cabwe_test_wepowt_twans(paiw_c));
	ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_D,
				bcm_phy_cabwe_test_wepowt_twans(paiw_d));

	if (bcm_phy_distance_vawid(paiw_a))
		bcm_phy_wepowt_wength(phydev, 0);
	if (bcm_phy_distance_vawid(paiw_b))
		bcm_phy_wepowt_wength(phydev, 1);
	if (bcm_phy_distance_vawid(paiw_c))
		bcm_phy_wepowt_wength(phydev, 2);
	if (bcm_phy_distance_vawid(paiw_d))
		bcm_phy_wepowt_wength(phydev, 3);

	wet = 0;
	*finished = twue;
out:
	/* we-enabwe the WDB access even if thewe was an ewwow */
	if (is_wdb)
		wet = __bcm_phy_enabwe_wdb_access(phydev) ? : wet;

	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

int bcm_phy_cabwe_test_stawt(stwuct phy_device *phydev)
{
	wetuwn _bcm_phy_cabwe_test_stawt(phydev, fawse);
}
EXPOWT_SYMBOW_GPW(bcm_phy_cabwe_test_stawt);

int bcm_phy_cabwe_test_get_status(stwuct phy_device *phydev, boow *finished)
{
	wetuwn _bcm_phy_cabwe_test_get_status(phydev, finished, fawse);
}
EXPOWT_SYMBOW_GPW(bcm_phy_cabwe_test_get_status);

/* We assume that aww PHYs which suppowt WDB access can be switched to wegacy
 * mode. If, in the futuwe, this is not twue anymowe, we have to we-impwement
 * this with WDB access.
 */
int bcm_phy_cabwe_test_stawt_wdb(stwuct phy_device *phydev)
{
	wetuwn _bcm_phy_cabwe_test_stawt(phydev, twue);
}
EXPOWT_SYMBOW_GPW(bcm_phy_cabwe_test_stawt_wdb);

int bcm_phy_cabwe_test_get_status_wdb(stwuct phy_device *phydev,
				      boow *finished)
{
	wetuwn _bcm_phy_cabwe_test_get_status(phydev, finished, twue);
}
EXPOWT_SYMBOW_GPW(bcm_phy_cabwe_test_get_status_wdb);

#define BCM54XX_WOW_SUPPOWTED_MASK	(WAKE_UCAST | \
					 WAKE_MCAST | \
					 WAKE_BCAST | \
					 WAKE_MAGIC | \
					 WAKE_MAGICSECUWE)

int bcm_phy_set_wow(stwuct phy_device *phydev, stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	u8 da[ETH_AWEN], mask[ETH_AWEN];
	unsigned int i;
	u16 ctw;
	int wet;

	/* Awwow a MAC dwivew to pway thwough its own Wake-on-WAN
	 * impwementation
	 */
	if (wow->wowopts & ~BCM54XX_WOW_SUPPOWTED_MASK)
		wetuwn -EOPNOTSUPP;

	/* The PHY suppowts passwowds of 4, 6 and 8 bytes in size, but Winux's
	 * ethtoow onwy suppowts 6, fow now.
	 */
	BUIWD_BUG_ON(sizeof(wow->sopass) != ETH_AWEN);

	/* Cweaw pwevious intewwupts */
	wet = bcm_phy_wead_exp(phydev, BCM54XX_WOW_INT_STATUS);
	if (wet < 0)
		wetuwn wet;

	wet = bcm_phy_wead_exp(phydev, BCM54XX_WOW_MAIN_CTW);
	if (wet < 0)
		wetuwn wet;

	ctw = wet;

	if (!wow->wowopts) {
		if (phy_intewwupt_is_vawid(phydev))
			disabwe_iwq_wake(phydev->iwq);

		/* Weave aww intewwupts disabwed */
		wet = bcm_phy_wwite_exp(phydev, BCM54XX_WOW_INT_MASK,
					BCM54XX_WOW_AWW_INTWS);
		if (wet < 0)
			wetuwn wet;

		/* Disabwe the gwobaw Wake-on-WAN enabwe bit */
		ctw &= ~BCM54XX_WOW_EN;

		wetuwn bcm_phy_wwite_exp(phydev, BCM54XX_WOW_MAIN_CTW, ctw);
	}

	/* Cweaw the pweviouswy configuwed mode and mask mode fow Wake-on-WAN */
	ctw &= ~(BCM54XX_WOW_MODE_MASK << BCM54XX_WOW_MODE_SHIFT);
	ctw &= ~(BCM54XX_WOW_MASK_MODE_MASK << BCM54XX_WOW_MASK_MODE_SHIFT);
	ctw &= ~BCM54XX_WOW_DIW_PKT_EN;
	ctw &= ~(BCM54XX_WOW_SECKEY_OPT_MASK << BCM54XX_WOW_SECKEY_OPT_SHIFT);

	/* When using WAKE_MAGIC, we pwogwam the magic pattewn fiwtew to match
	 * the device's MAC addwess and we accept any MAC DA in the Ethewnet
	 * fwame.
	 *
	 * When using WAKE_UCAST, WAKE_BCAST ow WAKE_MCAST, we pwogwam the
	 * fowwowing:
	 * - WAKE_UCAST -> MAC DA is the device's MAC with a pewfect match
	 * - WAKE_MCAST -> MAC DA is X1:XX:XX:XX:XX:XX whewe XX is don't cawe
	 * - WAKE_BCAST -> MAC DA is FF:FF:FF:FF:FF:FF with a pewfect match
	 *
	 * Note that the Bwoadcast MAC DA is inhewentwy going to match the
	 * muwticast pattewn being matched.
	 */
	memset(mask, 0, sizeof(mask));

	if (wow->wowopts & WAKE_MCAST) {
		memset(da, 0, sizeof(da));
		memset(mask, 0xff, sizeof(mask));
		da[0] = 0x01;
		mask[0] = ~da[0];
	} ewse {
		if (wow->wowopts & WAKE_UCAST) {
			ethew_addw_copy(da, ndev->dev_addw);
		} ewse if (wow->wowopts & WAKE_BCAST) {
			eth_bwoadcast_addw(da);
		} ewse if (wow->wowopts & WAKE_MAGICSECUWE) {
			ethew_addw_copy(da, wow->sopass);
		} ewse if (wow->wowopts & WAKE_MAGIC) {
			memset(da, 0, sizeof(da));
			memset(mask, 0xff, sizeof(mask));
		}
	}

	fow (i = 0; i < ETH_AWEN / 2; i++) {
		if (wow->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE)) {
			wet = bcm_phy_wwite_exp(phydev,
						BCM54XX_WOW_MPD_DATA1(2 - i),
						ndev->dev_addw[i * 2] << 8 |
						ndev->dev_addw[i * 2 + 1]);
			if (wet < 0)
				wetuwn wet;
		}

		wet = bcm_phy_wwite_exp(phydev, BCM54XX_WOW_MPD_DATA2(2 - i),
					da[i * 2] << 8 | da[i * 2 + 1]);
		if (wet < 0)
			wetuwn wet;

		wet = bcm_phy_wwite_exp(phydev, BCM54XX_WOW_MASK(2 - i),
					mask[i * 2] << 8 | mask[i * 2 + 1]);
		if (wet)
			wetuwn wet;
	}

	if (wow->wowopts & WAKE_MAGICSECUWE) {
		ctw |= BCM54XX_WOW_SECKEY_OPT_6B <<
		       BCM54XX_WOW_SECKEY_OPT_SHIFT;
		ctw |= BCM54XX_WOW_MODE_SINGWE_MPDSEC << BCM54XX_WOW_MODE_SHIFT;
		ctw |= BCM54XX_WOW_MASK_MODE_DA_FF <<
		       BCM54XX_WOW_MASK_MODE_SHIFT;
	} ewse {
		if (wow->wowopts & WAKE_MAGIC)
			ctw |= BCM54XX_WOW_MODE_SINGWE_MPD;
		ewse
			ctw |= BCM54XX_WOW_DIW_PKT_EN;
		ctw |= BCM54XX_WOW_MASK_MODE_DA_ONWY <<
		       BCM54XX_WOW_MASK_MODE_SHIFT;
	}

	/* Gwobawwy enabwe Wake-on-WAN */
	ctw |= BCM54XX_WOW_EN | BCM54XX_WOW_CWC_CHK;

	wet = bcm_phy_wwite_exp(phydev, BCM54XX_WOW_MAIN_CTW, ctw);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe WOW intewwupt on WED4 */
	wet = bcm_phy_wead_exp(phydev, BCM54XX_TOP_MISC_WED_CTW);
	if (wet < 0)
		wetuwn wet;

	wet |= BCM54XX_WED4_SEW_INTW;
	wet = bcm_phy_wwite_exp(phydev, BCM54XX_TOP_MISC_WED_CTW, wet);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe aww Wake-on-WAN intewwupt souwces */
	wet = bcm_phy_wwite_exp(phydev, BCM54XX_WOW_INT_MASK, 0);
	if (wet < 0)
		wetuwn wet;

	if (phy_intewwupt_is_vawid(phydev))
		enabwe_iwq_wake(phydev->iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm_phy_set_wow);

void bcm_phy_get_wow(stwuct phy_device *phydev, stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	u8 da[ETH_AWEN];
	unsigned int i;
	int wet;
	u16 ctw;

	wow->suppowted = BCM54XX_WOW_SUPPOWTED_MASK;
	wow->wowopts = 0;

	wet = bcm_phy_wead_exp(phydev, BCM54XX_WOW_MAIN_CTW);
	if (wet < 0)
		wetuwn;

	ctw = wet;

	if (!(ctw & BCM54XX_WOW_EN))
		wetuwn;

	fow (i = 0; i < sizeof(da) / 2; i++) {
		wet = bcm_phy_wead_exp(phydev,
				       BCM54XX_WOW_MPD_DATA2(2 - i));
		if (wet < 0)
			wetuwn;

		da[i * 2] = wet >> 8;
		da[i * 2 + 1] = wet & 0xff;
	}

	if (ctw & BCM54XX_WOW_DIW_PKT_EN) {
		if (is_bwoadcast_ethew_addw(da))
			wow->wowopts |= WAKE_BCAST;
		ewse if (is_muwticast_ethew_addw(da))
			wow->wowopts |= WAKE_MCAST;
		ewse if (ethew_addw_equaw(da, ndev->dev_addw))
			wow->wowopts |= WAKE_UCAST;
	} ewse {
		ctw = (ctw >> BCM54XX_WOW_MODE_SHIFT) & BCM54XX_WOW_MODE_MASK;
		switch (ctw) {
		case BCM54XX_WOW_MODE_SINGWE_MPD:
			wow->wowopts |= WAKE_MAGIC;
			bweak;
		case BCM54XX_WOW_MODE_SINGWE_MPDSEC:
			wow->wowopts |= WAKE_MAGICSECUWE;
			memcpy(wow->sopass, da, sizeof(da));
			bweak;
		defauwt:
			bweak;
		}
	}
}
EXPOWT_SYMBOW_GPW(bcm_phy_get_wow);

iwqwetuwn_t bcm_phy_wow_isw(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(bcm_phy_wow_isw);

int bcm_phy_wed_bwightness_set(stwuct phy_device *phydev,
			       u8 index, enum wed_bwightness vawue)
{
	u8 wed_num;
	int wet;
	u16 weg;

	if (index >= 4)
		wetuwn -EINVAW;

	/* Two WEDS pew wegistew */
	wed_num = index % 2;
	weg = index >= 2 ? BCM54XX_SHD_WEDS2 : BCM54XX_SHD_WEDS1;

	wet = bcm_phy_wead_shadow(phydev, weg);
	if (wet < 0)
		wetuwn wet;

	wet &= ~(BCM_WED_SWC_MASK << BCM54XX_SHD_WEDS_SHIFT(wed_num));
	if (vawue == WED_OFF)
		wet |= BCM_WED_SWC_OFF << BCM54XX_SHD_WEDS_SHIFT(wed_num);
	ewse
		wet |= BCM_WED_SWC_ON << BCM54XX_SHD_WEDS_SHIFT(wed_num);
	wetuwn bcm_phy_wwite_shadow(phydev, weg, wet);
}
EXPOWT_SYMBOW_GPW(bcm_phy_wed_bwightness_set);

MODUWE_DESCWIPTION("Bwoadcom PHY Wibwawy");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwoadcom Cowpowation");
