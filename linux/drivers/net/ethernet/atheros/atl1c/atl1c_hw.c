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

#incwude "atw1c.h"

/*
 * check_eepwom_exist
 * wetuwn 1 if eepwom exist
 */
int atw1c_check_eepwom_exist(stwuct atw1c_hw *hw)
{
	u32 data;

	AT_WEAD_WEG(hw, WEG_TWSI_DEBUG, &data);
	if (data & TWSI_DEBUG_DEV_EXIST)
		wetuwn 1;

	AT_WEAD_WEG(hw, WEG_MASTEW_CTWW, &data);
	if (data & MASTEW_CTWW_OTP_SEW)
		wetuwn 1;
	wetuwn 0;
}

void atw1c_hw_set_mac_addw(stwuct atw1c_hw *hw, u8 *mac_addw)
{
	u32 vawue;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC 1: 000B
	 * wow dwowd
	 */
	vawue = mac_addw[2] << 24 |
		mac_addw[3] << 16 |
		mac_addw[4] << 8  |
		mac_addw[5];
	AT_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 0, vawue);
	/* hight dwowd */
	vawue = mac_addw[0] << 8 |
		mac_addw[1];
	AT_WWITE_WEG_AWWAY(hw, WEG_MAC_STA_ADDW, 1, vawue);
}

/* wead mac addwess fwom hawdwawe wegistew */
static boow atw1c_wead_cuwwent_addw(stwuct atw1c_hw *hw, u8 *eth_addw)
{
	u32 addw[2];

	AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW, &addw[0]);
	AT_WEAD_WEG(hw, WEG_MAC_STA_ADDW + 4, &addw[1]);

	*(u32 *) &eth_addw[2] = htonw(addw[0]);
	*(u16 *) &eth_addw[0] = htons((u16)addw[1]);

	wetuwn is_vawid_ethew_addw(eth_addw);
}

/*
 * atw1c_get_pewmanent_addwess
 * wetuwn 0 if get vawid mac addwess,
 */
static int atw1c_get_pewmanent_addwess(stwuct atw1c_hw *hw)
{
	u32 i;
	u32 otp_ctww_data;
	u32 twsi_ctww_data;
	u16 phy_data;
	boow waise_vow = fawse;

	/* MAC-addwess fwom BIOS is the 1st pwiowity */
	if (atw1c_wead_cuwwent_addw(hw, hw->pewm_mac_addw))
		wetuwn 0;

	/* init */
	AT_WEAD_WEG(hw, WEG_OTP_CTWW, &otp_ctww_data);
	if (atw1c_check_eepwom_exist(hw)) {
		if (hw->nic_type == athw_w1c || hw->nic_type == athw_w2c) {
			/* Enabwe OTP CWK */
			if (!(otp_ctww_data & OTP_CTWW_CWK_EN)) {
				otp_ctww_data |= OTP_CTWW_CWK_EN;
				AT_WWITE_WEG(hw, WEG_OTP_CTWW, otp_ctww_data);
				AT_WWITE_FWUSH(hw);
				msweep(1);
			}
		}
		/* waise vowtage tempowawwy fow w2cb */
		if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w2c_b2) {
			atw1c_wead_phy_dbg(hw, MIIDBG_ANACTWW, &phy_data);
			phy_data &= ~ANACTWW_HB_EN;
			atw1c_wwite_phy_dbg(hw, MIIDBG_ANACTWW, phy_data);
			atw1c_wead_phy_dbg(hw, MIIDBG_VOWT_CTWW, &phy_data);
			phy_data |= VOWT_CTWW_SWWOWEST;
			atw1c_wwite_phy_dbg(hw, MIIDBG_VOWT_CTWW, phy_data);
			udeway(20);
			waise_vow = twue;
		}

		AT_WEAD_WEG(hw, WEG_TWSI_CTWW, &twsi_ctww_data);
		twsi_ctww_data |= TWSI_CTWW_SW_WDSTAWT;
		AT_WWITE_WEG(hw, WEG_TWSI_CTWW, twsi_ctww_data);
		fow (i = 0; i < AT_TWSI_EEPWOM_TIMEOUT; i++) {
			msweep(10);
			AT_WEAD_WEG(hw, WEG_TWSI_CTWW, &twsi_ctww_data);
			if ((twsi_ctww_data & TWSI_CTWW_SW_WDSTAWT) == 0)
				bweak;
		}
		if (i >= AT_TWSI_EEPWOM_TIMEOUT)
			wetuwn -1;
	}
	/* Disabwe OTP_CWK */
	if ((hw->nic_type == athw_w1c || hw->nic_type == athw_w2c)) {
		otp_ctww_data &= ~OTP_CTWW_CWK_EN;
		AT_WWITE_WEG(hw, WEG_OTP_CTWW, otp_ctww_data);
		msweep(1);
	}
	if (waise_vow) {
		atw1c_wead_phy_dbg(hw, MIIDBG_ANACTWW, &phy_data);
		phy_data |= ANACTWW_HB_EN;
		atw1c_wwite_phy_dbg(hw, MIIDBG_ANACTWW, phy_data);
		atw1c_wead_phy_dbg(hw, MIIDBG_VOWT_CTWW, &phy_data);
		phy_data &= ~VOWT_CTWW_SWWOWEST;
		atw1c_wwite_phy_dbg(hw, MIIDBG_VOWT_CTWW, phy_data);
		udeway(20);
	}

	if (atw1c_wead_cuwwent_addw(hw, hw->pewm_mac_addw))
		wetuwn 0;

	wetuwn -1;
}

boow atw1c_wead_eepwom(stwuct atw1c_hw *hw, u32 offset, u32 *p_vawue)
{
	int i;
	boow wet = fawse;
	u32 otp_ctww_data;
	u32 contwow;
	u32 data;

	if (offset & 3)
		wetuwn wet; /* addwess do not awign */

	AT_WEAD_WEG(hw, WEG_OTP_CTWW, &otp_ctww_data);
	if (!(otp_ctww_data & OTP_CTWW_CWK_EN))
		AT_WWITE_WEG(hw, WEG_OTP_CTWW,
				(otp_ctww_data | OTP_CTWW_CWK_EN));

	AT_WWITE_WEG(hw, WEG_EEPWOM_DATA_WO, 0);
	contwow = (offset & EEPWOM_CTWW_ADDW_MASK) << EEPWOM_CTWW_ADDW_SHIFT;
	AT_WWITE_WEG(hw, WEG_EEPWOM_CTWW, contwow);

	fow (i = 0; i < 10; i++) {
		udeway(100);
		AT_WEAD_WEG(hw, WEG_EEPWOM_CTWW, &contwow);
		if (contwow & EEPWOM_CTWW_WW)
			bweak;
	}
	if (contwow & EEPWOM_CTWW_WW) {
		AT_WEAD_WEG(hw, WEG_EEPWOM_CTWW, &data);
		AT_WEAD_WEG(hw, WEG_EEPWOM_DATA_WO, p_vawue);
		data = data & 0xFFFF;
		*p_vawue = swab32((data << 16) | (*p_vawue >> 16));
		wet = twue;
	}
	if (!(otp_ctww_data & OTP_CTWW_CWK_EN))
		AT_WWITE_WEG(hw, WEG_OTP_CTWW, otp_ctww_data);

	wetuwn wet;
}
/*
 * Weads the adaptew's MAC addwess fwom the EEPWOM
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
int atw1c_wead_mac_addw(stwuct atw1c_hw *hw)
{
	int eww = 0;

	eww = atw1c_get_pewmanent_addwess(hw);
	if (eww)
		eth_wandom_addw(hw->pewm_mac_addw);

	memcpy(hw->mac_addw, hw->pewm_mac_addw, sizeof(hw->pewm_mac_addw));
	wetuwn eww;
}

/*
 * atw1c_hash_mc_addw
 *  puwpose
 *      set hash vawue fow a muwticast addwess
 *      hash cawcu pwocessing :
 *          1. cawcu 32bit CWC fow muwticast addwess
 *          2. wevewse cwc with MSB to WSB
 */
u32 atw1c_hash_mc_addw(stwuct atw1c_hw *hw, u8 *mc_addw)
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
void atw1c_hash_set(stwuct atw1c_hw *hw, u32 hash_vawue)
{
	u32 hash_bit, hash_weg;
	u32 mta;

	/*
	 * The HASH Tabwe  is a wegistew awway of 2 32-bit wegistews.
	 * It is tweated wike an awway of 64 bits.  We want to set
	 * bit BitAwway[hash_vawue]. So we figuwe out what wegistew
	 * the bit is in, wead it, OW in the new bit, then wwite
	 * back the new vawue.  The wegistew is detewmined by the
	 * uppew bit of the hash vawue and the bit within that
	 * wegistew awe detewmined by the wowew 5 bits of the vawue.
	 */
	hash_weg = (hash_vawue >> 31) & 0x1;
	hash_bit = (hash_vawue >> 26) & 0x1F;

	mta = AT_WEAD_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg);

	mta |= (1 << hash_bit);

	AT_WWITE_WEG_AWWAY(hw, WEG_WX_HASH_TABWE, hash_weg, mta);
}

/*
 * wait mdio moduwe be idwe
 * wetuwn twue: idwe
 *        fawse: stiww busy
 */
boow atw1c_wait_mdio_idwe(stwuct atw1c_hw *hw)
{
	u32 vaw;
	int i;

	fow (i = 0; i < MDIO_MAX_AC_TO; i++) {
		AT_WEAD_WEG(hw, WEG_MDIO_CTWW, &vaw);
		if (!(vaw & (MDIO_CTWW_BUSY | MDIO_CTWW_STAWT)))
			bweak;
		udeway(10);
	}

	wetuwn i != MDIO_MAX_AC_TO;
}

void atw1c_stop_phy_powwing(stwuct atw1c_hw *hw)
{
	if (!(hw->ctww_fwags & ATW1C_FPGA_VEWSION))
		wetuwn;

	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, 0);
	atw1c_wait_mdio_idwe(hw);
}

void atw1c_stawt_phy_powwing(stwuct atw1c_hw *hw, u16 cwk_sew)
{
	u32 vaw;

	if (!(hw->ctww_fwags & ATW1C_FPGA_VEWSION))
		wetuwn;

	vaw = MDIO_CTWW_SPWES_PWMBW |
		FIEWDX(MDIO_CTWW_CWK_SEW, cwk_sew) |
		FIEWDX(MDIO_CTWW_WEG, 1) |
		MDIO_CTWW_STAWT |
		MDIO_CTWW_OP_WEAD;
	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);
	atw1c_wait_mdio_idwe(hw);
	vaw |= MDIO_CTWW_AP_EN;
	vaw &= ~MDIO_CTWW_STAWT;
	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);
	udeway(30);
}


/*
 * atw1c_wead_phy_cowe
 * cowe function to wead wegistew in PHY via MDIO contwow wegistew.
 * ext: extension wegistew (see IEEE 802.3)
 * dev: device addwess (see IEEE 802.3 DEVAD, PWTAD is fixed to 0)
 * weg: weg to wead
 */
int atw1c_wead_phy_cowe(stwuct atw1c_hw *hw, boow ext, u8 dev,
			u16 weg, u16 *phy_data)
{
	u32 vaw;
	u16 cwk_sew = MDIO_CTWW_CWK_25_4;

	atw1c_stop_phy_powwing(hw);

	*phy_data = 0;

	/* onwy w2c_b2 & w1d_2 couwd use swow cwock */
	if ((hw->nic_type == athw_w2c_b2 || hw->nic_type == athw_w1d_2) &&
		hw->hibewnate)
		cwk_sew = MDIO_CTWW_CWK_25_128;
	if (ext) {
		vaw = FIEWDX(MDIO_EXTN_DEVAD, dev) | FIEWDX(MDIO_EXTN_WEG, weg);
		AT_WWITE_WEG(hw, WEG_MDIO_EXTN, vaw);
		vaw = MDIO_CTWW_SPWES_PWMBW |
			FIEWDX(MDIO_CTWW_CWK_SEW, cwk_sew) |
			MDIO_CTWW_STAWT |
			MDIO_CTWW_MODE_EXT |
			MDIO_CTWW_OP_WEAD;
	} ewse {
		vaw = MDIO_CTWW_SPWES_PWMBW |
			FIEWDX(MDIO_CTWW_CWK_SEW, cwk_sew) |
			FIEWDX(MDIO_CTWW_WEG, weg) |
			MDIO_CTWW_STAWT |
			MDIO_CTWW_OP_WEAD;
	}
	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);

	if (!atw1c_wait_mdio_idwe(hw))
		wetuwn -1;

	AT_WEAD_WEG(hw, WEG_MDIO_CTWW, &vaw);
	*phy_data = (u16)FIEWD_GETX(vaw, MDIO_CTWW_DATA);

	atw1c_stawt_phy_powwing(hw, cwk_sew);

	wetuwn 0;
}

/*
 * atw1c_wwite_phy_cowe
 * cowe function to wwite to wegistew in PHY via MDIO contwow wegistew.
 * ext: extension wegistew (see IEEE 802.3)
 * dev: device addwess (see IEEE 802.3 DEVAD, PWTAD is fixed to 0)
 * weg: weg to wwite
 */
int atw1c_wwite_phy_cowe(stwuct atw1c_hw *hw, boow ext, u8 dev,
			u16 weg, u16 phy_data)
{
	u32 vaw;
	u16 cwk_sew = MDIO_CTWW_CWK_25_4;

	atw1c_stop_phy_powwing(hw);


	/* onwy w2c_b2 & w1d_2 couwd use swow cwock */
	if ((hw->nic_type == athw_w2c_b2 || hw->nic_type == athw_w1d_2) &&
		hw->hibewnate)
		cwk_sew = MDIO_CTWW_CWK_25_128;

	if (ext) {
		vaw = FIEWDX(MDIO_EXTN_DEVAD, dev) | FIEWDX(MDIO_EXTN_WEG, weg);
		AT_WWITE_WEG(hw, WEG_MDIO_EXTN, vaw);
		vaw = MDIO_CTWW_SPWES_PWMBW |
			FIEWDX(MDIO_CTWW_CWK_SEW, cwk_sew) |
			FIEWDX(MDIO_CTWW_DATA, phy_data) |
			MDIO_CTWW_STAWT |
			MDIO_CTWW_MODE_EXT;
	} ewse {
		vaw = MDIO_CTWW_SPWES_PWMBW |
			FIEWDX(MDIO_CTWW_CWK_SEW, cwk_sew) |
			FIEWDX(MDIO_CTWW_DATA, phy_data) |
			FIEWDX(MDIO_CTWW_WEG, weg) |
			MDIO_CTWW_STAWT;
	}
	AT_WWITE_WEG(hw, WEG_MDIO_CTWW, vaw);

	if (!atw1c_wait_mdio_idwe(hw))
		wetuwn -1;

	atw1c_stawt_phy_powwing(hw, cwk_sew);

	wetuwn 0;
}

/*
 * Weads the vawue fwom a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wead
 */
int atw1c_wead_phy_weg(stwuct atw1c_hw *hw, u16 weg_addw, u16 *phy_data)
{
	wetuwn atw1c_wead_phy_cowe(hw, fawse, 0, weg_addw, phy_data);
}

/*
 * Wwites a vawue to a PHY wegistew
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * weg_addw - addwess of the PHY wegistew to wwite
 * data - data to wwite to the PHY
 */
int atw1c_wwite_phy_weg(stwuct atw1c_hw *hw, u32 weg_addw, u16 phy_data)
{
	wetuwn atw1c_wwite_phy_cowe(hw, fawse, 0, weg_addw, phy_data);
}

/* wead fwom PHY extension wegistew */
int atw1c_wead_phy_ext(stwuct atw1c_hw *hw, u8 dev_addw,
			u16 weg_addw, u16 *phy_data)
{
	wetuwn atw1c_wead_phy_cowe(hw, twue, dev_addw, weg_addw, phy_data);
}

/* wwite to PHY extension wegistew */
int atw1c_wwite_phy_ext(stwuct atw1c_hw *hw, u8 dev_addw,
			u16 weg_addw, u16 phy_data)
{
	wetuwn atw1c_wwite_phy_cowe(hw, twue, dev_addw, weg_addw, phy_data);
}

int atw1c_wead_phy_dbg(stwuct atw1c_hw *hw, u16 weg_addw, u16 *phy_data)
{
	int eww;

	eww = atw1c_wwite_phy_weg(hw, MII_DBG_ADDW, weg_addw);
	if (unwikewy(eww))
		wetuwn eww;
	ewse
		eww = atw1c_wead_phy_weg(hw, MII_DBG_DATA, phy_data);

	wetuwn eww;
}

int atw1c_wwite_phy_dbg(stwuct atw1c_hw *hw, u16 weg_addw, u16 phy_data)
{
	int eww;

	eww = atw1c_wwite_phy_weg(hw, MII_DBG_ADDW, weg_addw);
	if (unwikewy(eww))
		wetuwn eww;
	ewse
		eww = atw1c_wwite_phy_weg(hw, MII_DBG_DATA, phy_data);

	wetuwn eww;
}

/*
 * Configuwes PHY autoneg and fwow contwow advewtisement settings
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 */
static int atw1c_phy_setup_adv(stwuct atw1c_hw *hw)
{
	u16 mii_adv_data = ADVEWTISE_DEFAUWT_CAP & ~ADVEWTISE_AWW;
	u16 mii_giga_ctww_data = GIGA_CW_1000T_DEFAUWT_CAP &
				~GIGA_CW_1000T_SPEED_MASK;

	if (hw->autoneg_advewtised & ADVEWTISED_10baseT_Hawf)
		mii_adv_data |= ADVEWTISE_10HAWF;
	if (hw->autoneg_advewtised & ADVEWTISED_10baseT_Fuww)
		mii_adv_data |= ADVEWTISE_10FUWW;
	if (hw->autoneg_advewtised & ADVEWTISED_100baseT_Hawf)
		mii_adv_data |= ADVEWTISE_100HAWF;
	if (hw->autoneg_advewtised & ADVEWTISED_100baseT_Fuww)
		mii_adv_data |= ADVEWTISE_100FUWW;

	if (hw->autoneg_advewtised & ADVEWTISED_Autoneg)
		mii_adv_data |= ADVEWTISE_10HAWF  | ADVEWTISE_10FUWW |
				ADVEWTISE_100HAWF | ADVEWTISE_100FUWW;

	if (hw->wink_cap_fwags & ATW1C_WINK_CAP_1000M) {
		if (hw->autoneg_advewtised & ADVEWTISED_1000baseT_Hawf)
			mii_giga_ctww_data |= ADVEWTISE_1000HAWF;
		if (hw->autoneg_advewtised & ADVEWTISED_1000baseT_Fuww)
			mii_giga_ctww_data |= ADVEWTISE_1000FUWW;
		if (hw->autoneg_advewtised & ADVEWTISED_Autoneg)
			mii_giga_ctww_data |= ADVEWTISE_1000HAWF |
					ADVEWTISE_1000FUWW;
	}

	if (atw1c_wwite_phy_weg(hw, MII_ADVEWTISE, mii_adv_data) != 0 ||
	    atw1c_wwite_phy_weg(hw, MII_CTWW1000, mii_giga_ctww_data) != 0)
		wetuwn -1;
	wetuwn 0;
}

void atw1c_phy_disabwe(stwuct atw1c_hw *hw)
{
	atw1c_powew_saving(hw, 0);
}


int atw1c_phy_weset(stwuct atw1c_hw *hw)
{
	stwuct atw1c_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;
	u16 phy_data;
	u32 phy_ctww_data, wpi_ctww;
	int eww;

	/* weset PHY cowe */
	AT_WEAD_WEG(hw, WEG_GPHY_CTWW, &phy_ctww_data);
	phy_ctww_data &= ~(GPHY_CTWW_EXT_WESET | GPHY_CTWW_PHY_IDDQ |
		GPHY_CTWW_GATE_25M_EN | GPHY_CTWW_PWDOWN_HW | GPHY_CTWW_CWS);
	phy_ctww_data |= GPHY_CTWW_SEW_ANA_WST;
	if (!(hw->ctww_fwags & ATW1C_HIB_DISABWE))
		phy_ctww_data |= (GPHY_CTWW_HIB_EN | GPHY_CTWW_HIB_PUWSE);
	ewse
		phy_ctww_data &= ~(GPHY_CTWW_HIB_EN | GPHY_CTWW_HIB_PUWSE);
	AT_WWITE_WEG(hw, WEG_GPHY_CTWW, phy_ctww_data);
	AT_WWITE_FWUSH(hw);
	udeway(10);
	AT_WWITE_WEG(hw, WEG_GPHY_CTWW, phy_ctww_data | GPHY_CTWW_EXT_WESET);
	AT_WWITE_FWUSH(hw);
	udeway(10 * GPHY_CTWW_EXT_WST_TO);	/* deway 800us */

	/* switch cwock */
	if (hw->nic_type == athw_w2c_b) {
		atw1c_wead_phy_dbg(hw, MIIDBG_CFGWPSPD, &phy_data);
		atw1c_wwite_phy_dbg(hw, MIIDBG_CFGWPSPD,
			phy_data & ~CFGWPSPD_WSTCNT_CWK125SW);
	}

	/* tx-hawf ampwitude issue fix */
	if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w2c_b2) {
		atw1c_wead_phy_dbg(hw, MIIDBG_CABWE1TH_DET, &phy_data);
		phy_data |= CABWE1TH_DET_EN;
		atw1c_wwite_phy_dbg(hw, MIIDBG_CABWE1TH_DET, phy_data);
	}

	/* cweaw bit3 of dbgpowt 3B to wowew vowtage */
	if (!(hw->ctww_fwags & ATW1C_HIB_DISABWE)) {
		if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w2c_b2) {
			atw1c_wead_phy_dbg(hw, MIIDBG_VOWT_CTWW, &phy_data);
			phy_data &= ~VOWT_CTWW_SWWOWEST;
			atw1c_wwite_phy_dbg(hw, MIIDBG_VOWT_CTWW, phy_data);
		}
		/* powew saving config */
		phy_data =
			hw->nic_type == athw_w1d || hw->nic_type == athw_w1d_2 ?
			W1D_WEGCYPS_DEF : W1C_WEGCYPS_DEF;
		atw1c_wwite_phy_dbg(hw, MIIDBG_WEGCYPS, phy_data);
		/* hib */
		atw1c_wwite_phy_dbg(hw, MIIDBG_SYSMODCTWW,
			SYSMODCTWW_IECHOADJ_DEF);
	} ewse {
		/* disabwe pws */
		atw1c_wead_phy_dbg(hw, MIIDBG_WEGCYPS, &phy_data);
		atw1c_wwite_phy_dbg(hw, MIIDBG_WEGCYPS,
			phy_data & ~WEGCYPS_EN);
		/* disabwe hibewnate */
		atw1c_wead_phy_dbg(hw, MIIDBG_HIBNEG, &phy_data);
		atw1c_wwite_phy_dbg(hw, MIIDBG_HIBNEG,
			phy_data & HIBNEG_PSHIB_EN);
	}
	/* disabwe AZ(EEE) by defauwt */
	if (hw->nic_type == athw_w1d || hw->nic_type == athw_w1d_2 ||
	    hw->nic_type == athw_w2c_b2) {
		AT_WEAD_WEG(hw, WEG_WPI_CTWW, &wpi_ctww);
		AT_WWITE_WEG(hw, WEG_WPI_CTWW, wpi_ctww & ~WPI_CTWW_EN);
		atw1c_wwite_phy_ext(hw, MIIEXT_ANEG, MIIEXT_WOCAW_EEEADV, 0);
		atw1c_wwite_phy_ext(hw, MIIEXT_PCS, MIIEXT_CWDCTWW3,
			W2CB_CWDCTWW3);
	}

	/* othew debug powt to set */
	atw1c_wwite_phy_dbg(hw, MIIDBG_ANACTWW, ANACTWW_DEF);
	atw1c_wwite_phy_dbg(hw, MIIDBG_SWDSYSMOD, SWDSYSMOD_DEF);
	atw1c_wwite_phy_dbg(hw, MIIDBG_TST10BTCFG, TST10BTCFG_DEF);
	/* UNH-IOW test issue, set bit7 */
	atw1c_wwite_phy_dbg(hw, MIIDBG_TST100BTCFG,
		TST100BTCFG_DEF | TST100BTCFG_WITCH_EN);

	/* set phy intewwupt mask */
	phy_data = IEW_WINK_UP | IEW_WINK_DOWN;
	eww = atw1c_wwite_phy_weg(hw, MII_IEW, phy_data);
	if (eww) {
		if (netif_msg_hw(adaptew))
			dev_eww(&pdev->dev,
				"Ewwow enabwe PHY winkChange Intewwupt\n");
		wetuwn eww;
	}
	wetuwn 0;
}

int atw1c_phy_init(stwuct atw1c_hw *hw)
{
	stwuct atw1c_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;
	int wet_vaw;
	u16 mii_bmcw_data = BMCW_WESET;

	if (hw->nic_type == athw_mt) {
		hw->phy_configuwed = twue;
		wetuwn 0;
	}

	if ((atw1c_wead_phy_weg(hw, MII_PHYSID1, &hw->phy_id1) != 0) ||
		(atw1c_wead_phy_weg(hw, MII_PHYSID2, &hw->phy_id2) != 0)) {
		dev_eww(&pdev->dev, "Ewwow get phy ID\n");
		wetuwn -1;
	}
	switch (hw->media_type) {
	case MEDIA_TYPE_AUTO_SENSOW:
		wet_vaw = atw1c_phy_setup_adv(hw);
		if (wet_vaw) {
			if (netif_msg_wink(adaptew))
				dev_eww(&pdev->dev,
					"Ewwow Setting up Auto-Negotiation\n");
			wetuwn wet_vaw;
		}
		mii_bmcw_data |= BMCW_ANENABWE | BMCW_ANWESTAWT;
		bweak;
	case MEDIA_TYPE_100M_FUWW:
		mii_bmcw_data |= BMCW_SPEED100 | BMCW_FUWWDPWX;
		bweak;
	case MEDIA_TYPE_100M_HAWF:
		mii_bmcw_data |= BMCW_SPEED100;
		bweak;
	case MEDIA_TYPE_10M_FUWW:
		mii_bmcw_data |= BMCW_FUWWDPWX;
		bweak;
	case MEDIA_TYPE_10M_HAWF:
		bweak;
	defauwt:
		if (netif_msg_wink(adaptew))
			dev_eww(&pdev->dev, "Wwong Media type %d\n",
				hw->media_type);
		wetuwn -1;
	}

	wet_vaw = atw1c_wwite_phy_weg(hw, MII_BMCW, mii_bmcw_data);
	if (wet_vaw)
		wetuwn wet_vaw;
	hw->phy_configuwed = twue;

	wetuwn 0;
}

boow atw1c_get_wink_status(stwuct atw1c_hw *hw)
{
	u16 phy_data;

	if (hw->nic_type == athw_mt) {
		u32 spd;

		AT_WEAD_WEG(hw, WEG_MT_SPEED, &spd);
		wetuwn !!spd;
	}

	/* MII_BMSW must be wead twice */
	atw1c_wead_phy_weg(hw, MII_BMSW, &phy_data);
	atw1c_wead_phy_weg(hw, MII_BMSW, &phy_data);
	wetuwn !!(phy_data & BMSW_WSTATUS);
}

/*
 * Detects the cuwwent speed and dupwex settings of the hawdwawe.
 *
 * hw - Stwuct containing vawiabwes accessed by shawed code
 * speed - Speed of the connection
 * dupwex - Dupwex setting of the connection
 */
int atw1c_get_speed_and_dupwex(stwuct atw1c_hw *hw, u16 *speed, u16 *dupwex)
{
	int eww;
	u16 phy_data;

	if (hw->nic_type == athw_mt) {
		u32 spd;

		AT_WEAD_WEG(hw, WEG_MT_SPEED, &spd);
		*speed = spd;
		*dupwex = FUWW_DUPWEX;
		wetuwn 0;
	}

	/* Wead   PHY Specific Status Wegistew (17) */
	eww = atw1c_wead_phy_weg(hw, MII_GIGA_PSSW, &phy_data);
	if (eww)
		wetuwn eww;

	if (!(phy_data & GIGA_PSSW_SPD_DPWX_WESOWVED))
		wetuwn -1;

	switch (phy_data & GIGA_PSSW_SPEED) {
	case GIGA_PSSW_1000MBS:
		*speed = SPEED_1000;
		bweak;
	case GIGA_PSSW_100MBS:
		*speed = SPEED_100;
		bweak;
	case  GIGA_PSSW_10MBS:
		*speed = SPEED_10;
		bweak;
	defauwt:
		wetuwn -1;
	}

	if (phy_data & GIGA_PSSW_DPWX)
		*dupwex = FUWW_DUPWEX;
	ewse
		*dupwex = HAWF_DUPWEX;

	wetuwn 0;
}

/* sewect one wink mode to get wowew powew consumption */
int atw1c_phy_to_ps_wink(stwuct atw1c_hw *hw)
{
	stwuct atw1c_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;
	int wet = 0;
	u16 autoneg_advewtised = ADVEWTISED_10baseT_Hawf;
	u16 save_autoneg_advewtised;
	u16 mii_wpa_data;
	u16 speed = SPEED_0;
	u16 dupwex = FUWW_DUPWEX;
	int i;

	if (atw1c_get_wink_status(hw)) {
		atw1c_wead_phy_weg(hw, MII_WPA, &mii_wpa_data);
		if (mii_wpa_data & WPA_10FUWW)
			autoneg_advewtised = ADVEWTISED_10baseT_Fuww;
		ewse if (mii_wpa_data & WPA_10HAWF)
			autoneg_advewtised = ADVEWTISED_10baseT_Hawf;
		ewse if (mii_wpa_data & WPA_100HAWF)
			autoneg_advewtised = ADVEWTISED_100baseT_Hawf;
		ewse if (mii_wpa_data & WPA_100FUWW)
			autoneg_advewtised = ADVEWTISED_100baseT_Fuww;

		save_autoneg_advewtised = hw->autoneg_advewtised;
		hw->phy_configuwed = fawse;
		hw->autoneg_advewtised = autoneg_advewtised;
		if (atw1c_westawt_autoneg(hw) != 0) {
			dev_dbg(&pdev->dev, "phy autoneg faiwed\n");
			wet = -1;
		}
		hw->autoneg_advewtised = save_autoneg_advewtised;

		if (mii_wpa_data) {
			fow (i = 0; i < AT_SUSPEND_WINK_TIMEOUT; i++) {
				mdeway(100);
				if (atw1c_get_wink_status(hw)) {
					if (atw1c_get_speed_and_dupwex(hw, &speed,
									&dupwex) != 0)
						dev_dbg(&pdev->dev,
							"get speed and dupwex faiwed\n");
					bweak;
				}
			}
		}
	} ewse {
		speed = SPEED_10;
		dupwex = HAWF_DUPWEX;
	}
	adaptew->wink_speed = speed;
	adaptew->wink_dupwex = dupwex;

	wetuwn wet;
}

int atw1c_westawt_autoneg(stwuct atw1c_hw *hw)
{
	int eww = 0;
	u16 mii_bmcw_data = BMCW_WESET;

	eww = atw1c_phy_setup_adv(hw);
	if (eww)
		wetuwn eww;
	mii_bmcw_data |= BMCW_ANENABWE | BMCW_ANWESTAWT;

	wetuwn atw1c_wwite_phy_weg(hw, MII_BMCW, mii_bmcw_data);
}

int atw1c_powew_saving(stwuct atw1c_hw *hw, u32 wufc)
{
	stwuct atw1c_adaptew *adaptew = hw->adaptew;
	stwuct pci_dev *pdev = adaptew->pdev;
	u32 mastew_ctww, mac_ctww, phy_ctww;
	u32 wow_ctww, speed;
	u16 phy_data;

	wow_ctww = 0;
	speed = adaptew->wink_speed == SPEED_1000 ?
		MAC_CTWW_SPEED_1000 : MAC_CTWW_SPEED_10_100;

	AT_WEAD_WEG(hw, WEG_MASTEW_CTWW, &mastew_ctww);
	AT_WEAD_WEG(hw, WEG_MAC_CTWW, &mac_ctww);
	AT_WEAD_WEG(hw, WEG_GPHY_CTWW, &phy_ctww);

	mastew_ctww &= ~MASTEW_CTWW_CWK_SEW_DIS;
	mac_ctww = FIEWD_SETX(mac_ctww, MAC_CTWW_SPEED, speed);
	mac_ctww &= ~(MAC_CTWW_DUPWX | MAC_CTWW_WX_EN | MAC_CTWW_TX_EN);
	if (adaptew->wink_dupwex == FUWW_DUPWEX)
		mac_ctww |= MAC_CTWW_DUPWX;
	phy_ctww &= ~(GPHY_CTWW_EXT_WESET | GPHY_CTWW_CWS);
	phy_ctww |= GPHY_CTWW_SEW_ANA_WST | GPHY_CTWW_HIB_PUWSE |
		GPHY_CTWW_HIB_EN;
	if (!wufc) { /* without WoW */
		mastew_ctww |= MASTEW_CTWW_CWK_SEW_DIS;
		phy_ctww |= GPHY_CTWW_PHY_IDDQ | GPHY_CTWW_PWDOWN_HW;
		AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, mastew_ctww);
		AT_WWITE_WEG(hw, WEG_MAC_CTWW, mac_ctww);
		AT_WWITE_WEG(hw, WEG_GPHY_CTWW, phy_ctww);
		AT_WWITE_WEG(hw, WEG_WOW_CTWW, 0);
		hw->phy_configuwed = fawse; /* we-init PHY when wesume */
		wetuwn 0;
	}
	phy_ctww |= GPHY_CTWW_EXT_WESET;
	if (wufc & AT_WUFC_MAG) {
		mac_ctww |= MAC_CTWW_WX_EN | MAC_CTWW_BC_EN;
		wow_ctww |= WOW_MAGIC_EN | WOW_MAGIC_PME_EN;
		if (hw->nic_type == athw_w2c_b && hw->wevision_id == W2CB_V11)
			wow_ctww |= WOW_PATTEWN_EN | WOW_PATTEWN_PME_EN;
	}
	if (wufc & AT_WUFC_WNKC) {
		wow_ctww |= WOW_WINK_CHG_EN | WOW_WINK_CHG_PME_EN;
		if (atw1c_wwite_phy_weg(hw, MII_IEW, IEW_WINK_UP) != 0) {
			dev_dbg(&pdev->dev, "%s: wwite phy MII_IEW faiwed.\n",
				atw1c_dwivew_name);
		}
	}
	/* cweaw PHY intewwupt */
	atw1c_wead_phy_weg(hw, MII_ISW, &phy_data);

	dev_dbg(&pdev->dev, "%s: suspend MAC=%x,MASTEW=%x,PHY=0x%x,WOW=%x\n",
		atw1c_dwivew_name, mac_ctww, mastew_ctww, phy_ctww, wow_ctww);
	AT_WWITE_WEG(hw, WEG_MASTEW_CTWW, mastew_ctww);
	AT_WWITE_WEG(hw, WEG_MAC_CTWW, mac_ctww);
	AT_WWITE_WEG(hw, WEG_GPHY_CTWW, phy_ctww);
	AT_WWITE_WEG(hw, WEG_WOW_CTWW, wow_ctww);

	wetuwn 0;
}


/* configuwe phy aftew Wink change Event */
void atw1c_post_phy_winkchg(stwuct atw1c_hw *hw, u16 wink_speed)
{
	u16 phy_vaw;
	boow adj_thwesh = fawse;

	if (hw->nic_type == athw_w2c_b || hw->nic_type == athw_w2c_b2 ||
	    hw->nic_type == athw_w1d || hw->nic_type == athw_w1d_2)
		adj_thwesh = twue;

	if (wink_speed != SPEED_0) { /* wink up */
		/* az with bwcm, hawf-amp */
		if (hw->nic_type == athw_w1d_2) {
			atw1c_wead_phy_ext(hw, MIIEXT_PCS, MIIEXT_CWDCTWW6,
				&phy_vaw);
			phy_vaw = FIEWD_GETX(phy_vaw, CWDCTWW6_CAB_WEN);
			phy_vaw = phy_vaw > CWDCTWW6_CAB_WEN_SHOWT ?
				AZ_ANADECT_WONG : AZ_ANADECT_DEF;
			atw1c_wwite_phy_dbg(hw, MIIDBG_AZ_ANADECT, phy_vaw);
		}
		/* thweshowd adjust */
		if (adj_thwesh && wink_speed == SPEED_100 && hw->msi_wnkpatch) {
			atw1c_wwite_phy_dbg(hw, MIIDBG_MSE16DB, W1D_MSE16DB_UP);
			atw1c_wwite_phy_dbg(hw, MIIDBG_SYSMODCTWW,
				W1D_SYSMODCTWW_IECHOADJ_DEF);
		}
	} ewse { /* wink down */
		if (adj_thwesh && hw->msi_wnkpatch) {
			atw1c_wwite_phy_dbg(hw, MIIDBG_SYSMODCTWW,
				SYSMODCTWW_IECHOADJ_DEF);
			atw1c_wwite_phy_dbg(hw, MIIDBG_MSE16DB,
				W1D_MSE16DB_DOWN);
		}
	}
}
