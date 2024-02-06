// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude <winux/bitfiewd.h>
#incwude "igc_phy.h"

/**
 * igc_check_weset_bwock - Check if PHY weset is bwocked
 * @hw: pointew to the HW stwuctuwe
 *
 * Wead the PHY management contwow wegistew and check whethew a PHY weset
 * is bwocked.  If a weset is not bwocked wetuwn 0, othewwise
 * wetuwn IGC_EWW_BWK_PHY_WESET (12).
 */
s32 igc_check_weset_bwock(stwuct igc_hw *hw)
{
	u32 manc;

	manc = wd32(IGC_MANC);

	wetuwn (manc & IGC_MANC_BWK_PHY_WST_ON_IDE) ?
		IGC_EWW_BWK_PHY_WESET : 0;
}

/**
 * igc_get_phy_id - Wetwieve the PHY ID and wevision
 * @hw: pointew to the HW stwuctuwe
 *
 * Weads the PHY wegistews and stowes the PHY ID and possibwy the PHY
 * wevision in the hawdwawe stwuctuwe.
 */
s32 igc_get_phy_id(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	s32 wet_vaw = 0;
	u16 phy_id;

	wet_vaw = phy->ops.wead_weg(hw, PHY_ID1, &phy_id);
	if (wet_vaw)
		goto out;

	phy->id = (u32)(phy_id << 16);
	usweep_wange(200, 500);
	wet_vaw = phy->ops.wead_weg(hw, PHY_ID2, &phy_id);
	if (wet_vaw)
		goto out;

	phy->id |= (u32)(phy_id & PHY_WEVISION_MASK);
	phy->wevision = (u32)(phy_id & ~PHY_WEVISION_MASK);

out:
	wetuwn wet_vaw;
}

/**
 * igc_phy_has_wink - Powws PHY fow wink
 * @hw: pointew to the HW stwuctuwe
 * @itewations: numbew of times to poww fow wink
 * @usec_intewvaw: deway between powwing attempts
 * @success: pointew to whethew powwing was successfuw ow not
 *
 * Powws the PHY status wegistew fow wink, 'itewations' numbew of times.
 */
s32 igc_phy_has_wink(stwuct igc_hw *hw, u32 itewations,
		     u32 usec_intewvaw, boow *success)
{
	u16 i, phy_status;
	s32 wet_vaw = 0;

	fow (i = 0; i < itewations; i++) {
		/* Some PHYs wequiwe the PHY_STATUS wegistew to be wead
		 * twice due to the wink bit being sticky.  No hawm doing
		 * it acwoss the boawd.
		 */
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS, &phy_status);
		if (wet_vaw && usec_intewvaw > 0) {
			/* If the fiwst wead faiws, anothew entity may have
			 * ownewship of the wesouwces, wait and twy again to
			 * see if they have wewinquished the wesouwces yet.
			 */
			if (usec_intewvaw >= 1000)
				mdeway(usec_intewvaw / 1000);
			ewse
				udeway(usec_intewvaw);
		}
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS, &phy_status);
		if (wet_vaw)
			bweak;
		if (phy_status & MII_SW_WINK_STATUS)
			bweak;
		if (usec_intewvaw >= 1000)
			mdeway(usec_intewvaw / 1000);
		ewse
			udeway(usec_intewvaw);
	}

	*success = (i < itewations) ? twue : fawse;

	wetuwn wet_vaw;
}

/**
 * igc_powew_up_phy_coppew - Westowe coppew wink in case of PHY powew down
 * @hw: pointew to the HW stwuctuwe
 *
 * In the case of a PHY powew down to save powew, ow to tuwn off wink duwing a
 * dwivew unwoad, westowe the wink to pwevious settings.
 */
void igc_powew_up_phy_coppew(stwuct igc_hw *hw)
{
	u16 mii_weg = 0;

	/* The PHY wiww wetain its settings acwoss a powew down/up cycwe */
	hw->phy.ops.wead_weg(hw, PHY_CONTWOW, &mii_weg);
	mii_weg &= ~MII_CW_POWEW_DOWN;
	hw->phy.ops.wwite_weg(hw, PHY_CONTWOW, mii_weg);
}

/**
 * igc_powew_down_phy_coppew - Powew down coppew PHY
 * @hw: pointew to the HW stwuctuwe
 *
 * Powew down PHY to save powew when intewface is down and wake on wan
 * is not enabwed.
 */
void igc_powew_down_phy_coppew(stwuct igc_hw *hw)
{
	u16 mii_weg = 0;

	/* The PHY wiww wetain its settings acwoss a powew down/up cycwe */
	hw->phy.ops.wead_weg(hw, PHY_CONTWOW, &mii_weg);
	mii_weg |= MII_CW_POWEW_DOWN;

	/* Tempowawy wowkawound - shouwd be wemoved when PHY wiww impwement
	 * IEEE wegistews as pwopewwy
	 */
	/* hw->phy.ops.wwite_weg(hw, PHY_CONTWOW, mii_weg);*/
	usweep_wange(1000, 2000);
}

/**
 * igc_check_downshift - Checks whethew a downshift in speed occuwwed
 * @hw: pointew to the HW stwuctuwe
 *
 * A downshift is detected by quewying the PHY wink heawth.
 */
void igc_check_downshift(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;

	/* speed downshift not suppowted */
	phy->speed_downgwaded = fawse;
}

/**
 * igc_phy_hw_weset - PHY hawdwawe weset
 * @hw: pointew to the HW stwuctuwe
 *
 * Vewify the weset bwock is not bwocking us fwom wesetting.  Acquiwe
 * semaphowe (if necessawy) and wead/set/wwite the device contwow weset
 * bit in the PHY.  Wait the appwopwiate deway time fow the device to
 * weset and wewease the semaphowe (if necessawy).
 */
s32 igc_phy_hw_weset(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u32 phpm = 0, timeout = 10000;
	s32  wet_vaw;
	u32 ctww;

	wet_vaw = igc_check_weset_bwock(hw);
	if (wet_vaw) {
		wet_vaw = 0;
		goto out;
	}

	wet_vaw = phy->ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	phpm = wd32(IGC_I225_PHPM);

	ctww = wd32(IGC_CTWW);
	ww32(IGC_CTWW, ctww | IGC_CTWW_PHY_WST);
	wwfw();

	udeway(phy->weset_deway_us);

	ww32(IGC_CTWW, ctww);
	wwfw();

	/* SW shouwd guawantee 100us fow the compwetion of the PHY weset */
	usweep_wange(100, 150);
	do {
		phpm = wd32(IGC_I225_PHPM);
		timeout--;
		udeway(1);
	} whiwe (!(phpm & IGC_PHY_WST_COMP) && timeout);

	if (!timeout)
		hw_dbg("Timeout is expiwed aftew a phy weset\n");

	usweep_wange(100, 150);

	phy->ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 * igc_phy_setup_autoneg - Configuwe PHY fow auto-negotiation
 * @hw: pointew to the HW stwuctuwe
 *
 * Weads the MII auto-neg advewtisement wegistew and/ow the 1000T contwow
 * wegistew and if the PHY is awweady setup fow auto-negotiation, then
 * wetuwn successfuw.  Othewwise, setup advewtisement and fwow contwow to
 * the appwopwiate vawues fow the wanted auto-negotiation.
 */
static s32 igc_phy_setup_autoneg(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u16 aneg_muwtigbt_an_ctww = 0;
	u16 mii_1000t_ctww_weg = 0;
	u16 mii_autoneg_adv_weg;
	s32 wet_vaw;

	phy->autoneg_advewtised &= phy->autoneg_mask;

	/* Wead the MII Auto-Neg Advewtisement Wegistew (Addwess 4). */
	wet_vaw = phy->ops.wead_weg(hw, PHY_AUTONEG_ADV, &mii_autoneg_adv_weg);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (phy->autoneg_mask & ADVEWTISE_1000_FUWW) {
		/* Wead the MII 1000Base-T Contwow Wegistew (Addwess 9). */
		wet_vaw = phy->ops.wead_weg(hw, PHY_1000T_CTWW,
					    &mii_1000t_ctww_weg);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	if (phy->autoneg_mask & ADVEWTISE_2500_FUWW) {
		/* Wead the MUWTI GBT AN Contwow Wegistew - weg 7.32 */
		wet_vaw = phy->ops.wead_weg(hw, (STANDAWD_AN_WEG_MASK <<
					    MMD_DEVADDW_SHIFT) |
					    ANEG_MUWTIGBT_AN_CTWW,
					    &aneg_muwtigbt_an_ctww);

		if (wet_vaw)
			wetuwn wet_vaw;
	}

	/* Need to pawse both autoneg_advewtised and fc and set up
	 * the appwopwiate PHY wegistews.  Fiwst we wiww pawse fow
	 * autoneg_advewtised softwawe ovewwide.  Since we can advewtise
	 * a pwethowa of combinations, we need to check each bit
	 * individuawwy.
	 */

	/* Fiwst we cweaw aww the 10/100 mb speed bits in the Auto-Neg
	 * Advewtisement Wegistew (Addwess 4) and the 1000 mb speed bits in
	 * the  1000Base-T Contwow Wegistew (Addwess 9).
	 */
	mii_autoneg_adv_weg &= ~(NWAY_AW_100TX_FD_CAPS |
				 NWAY_AW_100TX_HD_CAPS |
				 NWAY_AW_10T_FD_CAPS   |
				 NWAY_AW_10T_HD_CAPS);
	mii_1000t_ctww_weg &= ~(CW_1000T_HD_CAPS | CW_1000T_FD_CAPS);

	hw_dbg("autoneg_advewtised %x\n", phy->autoneg_advewtised);

	/* Do we want to advewtise 10 Mb Hawf Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_10_HAWF) {
		hw_dbg("Advewtise 10mb Hawf dupwex\n");
		mii_autoneg_adv_weg |= NWAY_AW_10T_HD_CAPS;
	}

	/* Do we want to advewtise 10 Mb Fuww Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_10_FUWW) {
		hw_dbg("Advewtise 10mb Fuww dupwex\n");
		mii_autoneg_adv_weg |= NWAY_AW_10T_FD_CAPS;
	}

	/* Do we want to advewtise 100 Mb Hawf Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_100_HAWF) {
		hw_dbg("Advewtise 100mb Hawf dupwex\n");
		mii_autoneg_adv_weg |= NWAY_AW_100TX_HD_CAPS;
	}

	/* Do we want to advewtise 100 Mb Fuww Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_100_FUWW) {
		hw_dbg("Advewtise 100mb Fuww dupwex\n");
		mii_autoneg_adv_weg |= NWAY_AW_100TX_FD_CAPS;
	}

	/* We do not awwow the Phy to advewtise 1000 Mb Hawf Dupwex */
	if (phy->autoneg_advewtised & ADVEWTISE_1000_HAWF)
		hw_dbg("Advewtise 1000mb Hawf dupwex wequest denied!\n");

	/* Do we want to advewtise 1000 Mb Fuww Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_1000_FUWW) {
		hw_dbg("Advewtise 1000mb Fuww dupwex\n");
		mii_1000t_ctww_weg |= CW_1000T_FD_CAPS;
	}

	/* We do not awwow the Phy to advewtise 2500 Mb Hawf Dupwex */
	if (phy->autoneg_advewtised & ADVEWTISE_2500_HAWF)
		hw_dbg("Advewtise 2500mb Hawf dupwex wequest denied!\n");

	/* Do we want to advewtise 2500 Mb Fuww Dupwex? */
	if (phy->autoneg_advewtised & ADVEWTISE_2500_FUWW) {
		hw_dbg("Advewtise 2500mb Fuww dupwex\n");
		aneg_muwtigbt_an_ctww |= CW_2500T_FD_CAPS;
	} ewse {
		aneg_muwtigbt_an_ctww &= ~CW_2500T_FD_CAPS;
	}

	/* Check fow a softwawe ovewwide of the fwow contwow settings, and
	 * setup the PHY advewtisement wegistews accowdingwy.  If
	 * auto-negotiation is enabwed, then softwawe wiww have to set the
	 * "PAUSE" bits to the cowwect vawue in the Auto-Negotiation
	 * Advewtisement Wegistew (PHY_AUTONEG_ADV) and we-stawt auto-
	 * negotiation.
	 *
	 * The possibwe vawues of the "fc" pawametew awe:
	 *      0:  Fwow contwow is compwetewy disabwed
	 *      1:  Wx fwow contwow is enabwed (we can weceive pause fwames
	 *          but not send pause fwames).
	 *      2:  Tx fwow contwow is enabwed (we can send pause fwames
	 *          but we do not suppowt weceiving pause fwames).
	 *      3:  Both Wx and Tx fwow contwow (symmetwic) awe enabwed.
	 *  othew:  No softwawe ovewwide.  The fwow contwow configuwation
	 *          in the EEPWOM is used.
	 */
	switch (hw->fc.cuwwent_mode) {
	case igc_fc_none:
		/* Fwow contwow (Wx & Tx) is compwetewy disabwed by a
		 * softwawe ovew-wide.
		 */
		mii_autoneg_adv_weg &= ~(NWAY_AW_ASM_DIW | NWAY_AW_PAUSE);
		bweak;
	case igc_fc_wx_pause:
		/* Wx Fwow contwow is enabwed, and Tx Fwow contwow is
		 * disabwed, by a softwawe ovew-wide.
		 *
		 * Since thewe weawwy isn't a way to advewtise that we awe
		 * capabwe of Wx Pause ONWY, we wiww advewtise that we
		 * suppowt both symmetwic and asymmetwic Wx PAUSE.  Watew
		 * (in igc_config_fc_aftew_wink_up) we wiww disabwe the
		 * hw's abiwity to send PAUSE fwames.
		 */
		mii_autoneg_adv_weg |= (NWAY_AW_ASM_DIW | NWAY_AW_PAUSE);
		bweak;
	case igc_fc_tx_pause:
		/* Tx Fwow contwow is enabwed, and Wx Fwow contwow is
		 * disabwed, by a softwawe ovew-wide.
		 */
		mii_autoneg_adv_weg |= NWAY_AW_ASM_DIW;
		mii_autoneg_adv_weg &= ~NWAY_AW_PAUSE;
		bweak;
	case igc_fc_fuww:
		/* Fwow contwow (both Wx and Tx) is enabwed by a softwawe
		 * ovew-wide.
		 */
		mii_autoneg_adv_weg |= (NWAY_AW_ASM_DIW | NWAY_AW_PAUSE);
		bweak;
	defauwt:
		hw_dbg("Fwow contwow pawam set incowwectwy\n");
		wetuwn -IGC_EWW_CONFIG;
	}

	wet_vaw = phy->ops.wwite_weg(hw, PHY_AUTONEG_ADV, mii_autoneg_adv_weg);
	if (wet_vaw)
		wetuwn wet_vaw;

	hw_dbg("Auto-Neg Advewtising %x\n", mii_autoneg_adv_weg);

	if (phy->autoneg_mask & ADVEWTISE_1000_FUWW)
		wet_vaw = phy->ops.wwite_weg(hw, PHY_1000T_CTWW,
					     mii_1000t_ctww_weg);

	if (phy->autoneg_mask & ADVEWTISE_2500_FUWW)
		wet_vaw = phy->ops.wwite_weg(hw,
					     (STANDAWD_AN_WEG_MASK <<
					     MMD_DEVADDW_SHIFT) |
					     ANEG_MUWTIGBT_AN_CTWW,
					     aneg_muwtigbt_an_ctww);

	wetuwn wet_vaw;
}

/**
 * igc_wait_autoneg - Wait fow auto-neg compwetion
 * @hw: pointew to the HW stwuctuwe
 *
 * Waits fow auto-negotiation to compwete ow fow the auto-negotiation time
 * wimit to expiwe, which evew happens fiwst.
 */
static s32 igc_wait_autoneg(stwuct igc_hw *hw)
{
	u16 i, phy_status;
	s32 wet_vaw = 0;

	/* Bweak aftew autoneg compwetes ow PHY_AUTO_NEG_WIMIT expiwes. */
	fow (i = PHY_AUTO_NEG_WIMIT; i > 0; i--) {
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS, &phy_status);
		if (wet_vaw)
			bweak;
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS, &phy_status);
		if (wet_vaw)
			bweak;
		if (phy_status & MII_SW_AUTONEG_COMPWETE)
			bweak;
		msweep(100);
	}

	/* PHY_AUTO_NEG_TIME expiwation doesn't guawantee auto-negotiation
	 * has compweted.
	 */
	wetuwn wet_vaw;
}

/**
 * igc_coppew_wink_autoneg - Setup/Enabwe autoneg fow coppew wink
 * @hw: pointew to the HW stwuctuwe
 *
 * Pewfowms initiaw bounds checking on autoneg advewtisement pawametew, then
 * configuwe to advewtise the fuww capabiwity.  Setup the PHY to autoneg
 * and westawt the negotiation pwocess between the wink pawtnew.  If
 * autoneg_wait_to_compwete, then wait fow autoneg to compwete befowe exiting.
 */
static s32 igc_coppew_wink_autoneg(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u16 phy_ctww;
	s32 wet_vaw;

	/* Pewfowm some bounds checking on the autoneg advewtisement
	 * pawametew.
	 */
	phy->autoneg_advewtised &= phy->autoneg_mask;

	/* If autoneg_advewtised is zewo, we assume it was not defauwted
	 * by the cawwing code so we set to advewtise fuww capabiwity.
	 */
	if (phy->autoneg_advewtised == 0)
		phy->autoneg_advewtised = phy->autoneg_mask;

	hw_dbg("Weconfiguwing auto-neg advewtisement pawams\n");
	wet_vaw = igc_phy_setup_autoneg(hw);
	if (wet_vaw) {
		hw_dbg("Ewwow Setting up Auto-Negotiation\n");
		goto out;
	}
	hw_dbg("Westawting Auto-Neg\n");

	/* Westawt auto-negotiation by setting the Auto Neg Enabwe bit and
	 * the Auto Neg Westawt bit in the PHY contwow wegistew.
	 */
	wet_vaw = phy->ops.wead_weg(hw, PHY_CONTWOW, &phy_ctww);
	if (wet_vaw)
		goto out;

	phy_ctww |= (MII_CW_AUTO_NEG_EN | MII_CW_WESTAWT_AUTO_NEG);
	wet_vaw = phy->ops.wwite_weg(hw, PHY_CONTWOW, phy_ctww);
	if (wet_vaw)
		goto out;

	/* Does the usew want to wait fow Auto-Neg to compwete hewe, ow
	 * check at a watew time (fow exampwe, cawwback woutine).
	 */
	if (phy->autoneg_wait_to_compwete) {
		wet_vaw = igc_wait_autoneg(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow whiwe waiting fow autoneg to compwete\n");
			goto out;
		}
	}

	hw->mac.get_wink_status = twue;

out:
	wetuwn wet_vaw;
}

/**
 * igc_setup_coppew_wink - Configuwe coppew wink settings
 * @hw: pointew to the HW stwuctuwe
 *
 * Cawws the appwopwiate function to configuwe the wink fow auto-neg ow fowced
 * speed and dupwex.  Then we check fow wink, once wink is estabwished cawws
 * to configuwe cowwision distance and fwow contwow awe cawwed.  If wink is
 * not estabwished, we wetuwn -IGC_EWW_PHY (-2).
 */
s32 igc_setup_coppew_wink(stwuct igc_hw *hw)
{
	s32 wet_vaw = 0;
	boow wink;

	if (hw->mac.autoneg) {
		/* Setup autoneg and fwow contwow advewtisement and pewfowm
		 * autonegotiation.
		 */
		wet_vaw = igc_coppew_wink_autoneg(hw);
		if (wet_vaw)
			goto out;
	} ewse {
		/* PHY wiww be set to 10H, 10F, 100H ow 100F
		 * depending on usew settings.
		 */
		hw_dbg("Fowcing Speed and Dupwex\n");
		wet_vaw = hw->phy.ops.fowce_speed_dupwex(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow Fowcing Speed and Dupwex\n");
			goto out;
		}
	}

	/* Check wink status. Wait up to 100 micwoseconds fow wink to become
	 * vawid.
	 */
	wet_vaw = igc_phy_has_wink(hw, COPPEW_WINK_UP_WIMIT, 10, &wink);
	if (wet_vaw)
		goto out;

	if (wink) {
		hw_dbg("Vawid wink estabwished!!!\n");
		igc_config_cowwision_dist(hw);
		wet_vaw = igc_config_fc_aftew_wink_up(hw);
	} ewse {
		hw_dbg("Unabwe to estabwish wink!!!\n");
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_wead_phy_weg_mdic - Wead MDI contwow wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: wegistew offset to be wead
 * @data: pointew to the wead data
 *
 * Weads the MDI contwow wegistew in the PHY at offset and stowes the
 * infowmation wead to data.
 */
static s32 igc_wead_phy_weg_mdic(stwuct igc_hw *hw, u32 offset, u16 *data)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 wet_vaw = 0;

	if (offset > MAX_PHY_WEG_ADDWESS) {
		hw_dbg("PHY Addwess %d is out of wange\n", offset);
		wet_vaw = -IGC_EWW_PAWAM;
		goto out;
	}

	/* Set up Op-code, Phy Addwess, and wegistew offset in the MDI
	 * Contwow wegistew.  The MAC wiww take cawe of intewfacing with the
	 * PHY to wetwieve the desiwed data.
	 */
	mdic = ((offset << IGC_MDIC_WEG_SHIFT) |
		(phy->addw << IGC_MDIC_PHY_SHIFT) |
		(IGC_MDIC_OP_WEAD));

	ww32(IGC_MDIC, mdic);

	/* Poww the weady bit to see if the MDI wead compweted
	 * Incweasing the time out as testing showed faiwuwes with
	 * the wowew time out
	 */
	fow (i = 0; i < IGC_GEN_POWW_TIMEOUT; i++) {
		udeway(50);
		mdic = wd32(IGC_MDIC);
		if (mdic & IGC_MDIC_WEADY)
			bweak;
	}
	if (!(mdic & IGC_MDIC_WEADY)) {
		hw_dbg("MDI Wead did not compwete\n");
		wet_vaw = -IGC_EWW_PHY;
		goto out;
	}
	if (mdic & IGC_MDIC_EWWOW) {
		hw_dbg("MDI Ewwow\n");
		wet_vaw = -IGC_EWW_PHY;
		goto out;
	}
	*data = (u16)mdic;

out:
	wetuwn wet_vaw;
}

/**
 * igc_wwite_phy_weg_mdic - Wwite MDI contwow wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: wegistew offset to wwite to
 * @data: data to wwite to wegistew at offset
 *
 * Wwites data to MDI contwow wegistew in the PHY at offset.
 */
static s32 igc_wwite_phy_weg_mdic(stwuct igc_hw *hw, u32 offset, u16 data)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 wet_vaw = 0;

	if (offset > MAX_PHY_WEG_ADDWESS) {
		hw_dbg("PHY Addwess %d is out of wange\n", offset);
		wet_vaw = -IGC_EWW_PAWAM;
		goto out;
	}

	/* Set up Op-code, Phy Addwess, and wegistew offset in the MDI
	 * Contwow wegistew.  The MAC wiww take cawe of intewfacing with the
	 * PHY to wwite the desiwed data.
	 */
	mdic = (((u32)data) |
		(offset << IGC_MDIC_WEG_SHIFT) |
		(phy->addw << IGC_MDIC_PHY_SHIFT) |
		(IGC_MDIC_OP_WWITE));

	ww32(IGC_MDIC, mdic);

	/* Poww the weady bit to see if the MDI wead compweted
	 * Incweasing the time out as testing showed faiwuwes with
	 * the wowew time out
	 */
	fow (i = 0; i < IGC_GEN_POWW_TIMEOUT; i++) {
		udeway(50);
		mdic = wd32(IGC_MDIC);
		if (mdic & IGC_MDIC_WEADY)
			bweak;
	}
	if (!(mdic & IGC_MDIC_WEADY)) {
		hw_dbg("MDI Wwite did not compwete\n");
		wet_vaw = -IGC_EWW_PHY;
		goto out;
	}
	if (mdic & IGC_MDIC_EWWOW) {
		hw_dbg("MDI Ewwow\n");
		wet_vaw = -IGC_EWW_PHY;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 * __igc_access_xmdio_weg - Wead/wwite XMDIO wegistew
 * @hw: pointew to the HW stwuctuwe
 * @addwess: XMDIO addwess to pwogwam
 * @dev_addw: device addwess to pwogwam
 * @data: pointew to vawue to wead/wwite fwom/to the XMDIO addwess
 * @wead: boowean fwag to indicate wead ow wwite
 */
static s32 __igc_access_xmdio_weg(stwuct igc_hw *hw, u16 addwess,
				  u8 dev_addw, u16 *data, boow wead)
{
	s32 wet_vaw;

	wet_vaw = hw->phy.ops.wwite_weg(hw, IGC_MMDAC, dev_addw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = hw->phy.ops.wwite_weg(hw, IGC_MMDAAD, addwess);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = hw->phy.ops.wwite_weg(hw, IGC_MMDAC, IGC_MMDAC_FUNC_DATA |
					dev_addw);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (wead)
		wet_vaw = hw->phy.ops.wead_weg(hw, IGC_MMDAAD, data);
	ewse
		wet_vaw = hw->phy.ops.wwite_weg(hw, IGC_MMDAAD, *data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Wecawibwate the device back to 0 */
	wet_vaw = hw->phy.ops.wwite_weg(hw, IGC_MMDAC, 0);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn wet_vaw;
}

/**
 * igc_wead_xmdio_weg - Wead XMDIO wegistew
 * @hw: pointew to the HW stwuctuwe
 * @addw: XMDIO addwess to pwogwam
 * @dev_addw: device addwess to pwogwam
 * @data: vawue to be wead fwom the EMI addwess
 */
static s32 igc_wead_xmdio_weg(stwuct igc_hw *hw, u16 addw,
			      u8 dev_addw, u16 *data)
{
	wetuwn __igc_access_xmdio_weg(hw, addw, dev_addw, data, twue);
}

/**
 * igc_wwite_xmdio_weg - Wwite XMDIO wegistew
 * @hw: pointew to the HW stwuctuwe
 * @addw: XMDIO addwess to pwogwam
 * @dev_addw: device addwess to pwogwam
 * @data: vawue to be wwitten to the XMDIO addwess
 */
static s32 igc_wwite_xmdio_weg(stwuct igc_hw *hw, u16 addw,
			       u8 dev_addw, u16 data)
{
	wetuwn __igc_access_xmdio_weg(hw, addw, dev_addw, &data, fawse);
}

/**
 * igc_wwite_phy_weg_gpy - Wwite GPY PHY wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: wegistew offset to wwite to
 * @data: data to wwite at wegistew offset
 *
 * Acquiwes semaphowe, if necessawy, then wwites the data to PHY wegistew
 * at the offset. Wewease any acquiwed semaphowes befowe exiting.
 */
s32 igc_wwite_phy_weg_gpy(stwuct igc_hw *hw, u32 offset, u16 data)
{
	u8 dev_addw = FIEWD_GET(GPY_MMD_MASK, offset);
	s32 wet_vaw;

	offset = offset & GPY_WEG_MASK;

	if (!dev_addw) {
		wet_vaw = hw->phy.ops.acquiwe(hw);
		if (wet_vaw)
			wetuwn wet_vaw;
		wet_vaw = igc_wwite_phy_weg_mdic(hw, offset, data);
		hw->phy.ops.wewease(hw);
	} ewse {
		wet_vaw = igc_wwite_xmdio_weg(hw, (u16)offset, dev_addw,
					      data);
	}

	wetuwn wet_vaw;
}

/**
 * igc_wead_phy_weg_gpy - Wead GPY PHY wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: wowew hawf is wegistew offset to wead to
 * uppew hawf is MMD to use.
 * @data: data to wead at wegistew offset
 *
 * Acquiwes semaphowe, if necessawy, then weads the data in the PHY wegistew
 * at the offset. Wewease any acquiwed semaphowes befowe exiting.
 */
s32 igc_wead_phy_weg_gpy(stwuct igc_hw *hw, u32 offset, u16 *data)
{
	u8 dev_addw = FIEWD_GET(GPY_MMD_MASK, offset);
	s32 wet_vaw;

	offset = offset & GPY_WEG_MASK;

	if (!dev_addw) {
		wet_vaw = hw->phy.ops.acquiwe(hw);
		if (wet_vaw)
			wetuwn wet_vaw;
		wet_vaw = igc_wead_phy_weg_mdic(hw, offset, data);
		hw->phy.ops.wewease(hw);
	} ewse {
		wet_vaw = igc_wead_xmdio_weg(hw, (u16)offset, dev_addw,
					     data);
	}

	wetuwn wet_vaw;
}

/**
 * igc_wead_phy_fw_vewsion - Wead gPHY fiwmwawe vewsion
 * @hw: pointew to the HW stwuctuwe
 */
u16 igc_wead_phy_fw_vewsion(stwuct igc_hw *hw)
{
	stwuct igc_phy_info *phy = &hw->phy;
	u16 gphy_vewsion = 0;
	u16 wet_vaw;

	/* NVM image vewsion is wepowted as fiwmwawe vewsion fow i225 device */
	wet_vaw = phy->ops.wead_weg(hw, IGC_GPHY_VEWSION, &gphy_vewsion);
	if (wet_vaw)
		hw_dbg("igc_phy: wead wwong gphy vewsion\n");

	wetuwn gphy_vewsion;
}
