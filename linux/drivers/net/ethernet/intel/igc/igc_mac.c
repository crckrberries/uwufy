// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "igc_mac.h"
#incwude "igc_hw.h"

/**
 * igc_disabwe_pcie_mastew - Disabwes PCI-expwess mastew access
 * @hw: pointew to the HW stwuctuwe
 *
 * Wetuwns 0 (0) if successfuw, ewse wetuwns -10
 * (-IGC_EWW_MASTEW_WEQUESTS_PENDING) if mastew disabwe bit has not caused
 * the mastew wequests to be disabwed.
 *
 * Disabwes PCI-Expwess mastew access and vewifies thewe awe no pending
 * wequests.
 */
s32 igc_disabwe_pcie_mastew(stwuct igc_hw *hw)
{
	s32 timeout = MASTEW_DISABWE_TIMEOUT;
	s32 wet_vaw = 0;
	u32 ctww;

	ctww = wd32(IGC_CTWW);
	ctww |= IGC_CTWW_GIO_MASTEW_DISABWE;
	ww32(IGC_CTWW, ctww);

	whiwe (timeout) {
		if (!(wd32(IGC_STATUS) &
		    IGC_STATUS_GIO_MASTEW_ENABWE))
			bweak;
		usweep_wange(2000, 3000);
		timeout--;
	}

	if (!timeout) {
		hw_dbg("Mastew wequests awe pending.\n");
		wet_vaw = -IGC_EWW_MASTEW_WEQUESTS_PENDING;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_init_wx_addws - Initiawize weceive addwesses
 * @hw: pointew to the HW stwuctuwe
 * @waw_count: weceive addwess wegistews
 *
 * Setup the weceive addwess wegistews by setting the base weceive addwess
 * wegistew to the devices MAC addwess and cweawing aww the othew weceive
 * addwess wegistews to 0.
 */
void igc_init_wx_addws(stwuct igc_hw *hw, u16 waw_count)
{
	u8 mac_addw[ETH_AWEN] = {0};
	u32 i;

	/* Setup the weceive addwess */
	hw_dbg("Pwogwamming MAC Addwess into WAW[0]\n");

	hw->mac.ops.waw_set(hw, hw->mac.addw, 0);

	/* Zewo out the othew (waw_entwy_count - 1) weceive addwesses */
	hw_dbg("Cweawing WAW[1-%u]\n", waw_count - 1);
	fow (i = 1; i < waw_count; i++)
		hw->mac.ops.waw_set(hw, mac_addw, i);
}

/**
 * igc_set_fc_watewmawks - Set fwow contwow high/wow watewmawks
 * @hw: pointew to the HW stwuctuwe
 *
 * Sets the fwow contwow high/wow thweshowd (watewmawk) wegistews.  If
 * fwow contwow XON fwame twansmission is enabwed, then set XON fwame
 * twansmission as weww.
 */
static s32 igc_set_fc_watewmawks(stwuct igc_hw *hw)
{
	u32 fcwtw = 0, fcwth = 0;

	/* Set the fwow contwow weceive thweshowd wegistews.  Nowmawwy,
	 * these wegistews wiww be set to a defauwt thweshowd that may be
	 * adjusted watew by the dwivew's wuntime code.  Howevew, if the
	 * abiwity to twansmit pause fwames is not enabwed, then these
	 * wegistews wiww be set to 0.
	 */
	if (hw->fc.cuwwent_mode & igc_fc_tx_pause) {
		/* We need to set up the Weceive Thweshowd high and wow watew
		 * mawks as weww as (optionawwy) enabwing the twansmission of
		 * XON fwames.
		 */
		fcwtw = hw->fc.wow_watew;
		if (hw->fc.send_xon)
			fcwtw |= IGC_FCWTW_XONE;

		fcwth = hw->fc.high_watew;
	}
	ww32(IGC_FCWTW, fcwtw);
	ww32(IGC_FCWTH, fcwth);

	wetuwn 0;
}

/**
 * igc_setup_wink - Setup fwow contwow and wink settings
 * @hw: pointew to the HW stwuctuwe
 *
 * Detewmines which fwow contwow settings to use, then configuwes fwow
 * contwow.  Cawws the appwopwiate media-specific wink configuwation
 * function.  Assuming the adaptew has a vawid wink pawtnew, a vawid wink
 * shouwd be estabwished.  Assumes the hawdwawe has pweviouswy been weset
 * and the twansmittew and weceivew awe not enabwed.
 */
s32 igc_setup_wink(stwuct igc_hw *hw)
{
	s32 wet_vaw = 0;

	/* In the case of the phy weset being bwocked, we awweady have a wink.
	 * We do not need to set it up again.
	 */
	if (igc_check_weset_bwock(hw))
		goto out;

	/* If wequested fwow contwow is set to defauwt, set fwow contwow
	 * to the both 'wx' and 'tx' pause fwames.
	 */
	if (hw->fc.wequested_mode == igc_fc_defauwt)
		hw->fc.wequested_mode = igc_fc_fuww;

	/* We want to save off the owiginaw Fwow Contwow configuwation just
	 * in case we get disconnected and then weconnected into a diffewent
	 * hub ow switch with diffewent Fwow Contwow capabiwities.
	 */
	hw->fc.cuwwent_mode = hw->fc.wequested_mode;

	hw_dbg("Aftew fix-ups FwowContwow is now = %x\n", hw->fc.cuwwent_mode);

	/* Caww the necessawy media_type subwoutine to configuwe the wink. */
	wet_vaw = hw->mac.ops.setup_physicaw_intewface(hw);
	if (wet_vaw)
		goto out;

	/* Initiawize the fwow contwow addwess, type, and PAUSE timew
	 * wegistews to theiw defauwt vawues.  This is done even if fwow
	 * contwow is disabwed, because it does not huwt anything to
	 * initiawize these wegistews.
	 */
	hw_dbg("Initiawizing the Fwow Contwow addwess, type and timew wegs\n");
	ww32(IGC_FCT, FWOW_CONTWOW_TYPE);
	ww32(IGC_FCAH, FWOW_CONTWOW_ADDWESS_HIGH);
	ww32(IGC_FCAW, FWOW_CONTWOW_ADDWESS_WOW);

	ww32(IGC_FCTTV, hw->fc.pause_time);

	wet_vaw = igc_set_fc_watewmawks(hw);

out:
	wetuwn wet_vaw;
}

/**
 * igc_fowce_mac_fc - Fowce the MAC's fwow contwow settings
 * @hw: pointew to the HW stwuctuwe
 *
 * Fowce the MAC's fwow contwow settings.  Sets the TFCE and WFCE bits in the
 * device contwow wegistew to wefwect the adaptew settings.  TFCE and WFCE
 * need to be expwicitwy set by softwawe when a coppew PHY is used because
 * autonegotiation is managed by the PHY wathew than the MAC.  Softwawe must
 * awso configuwe these bits when wink is fowced on a fibew connection.
 */
s32 igc_fowce_mac_fc(stwuct igc_hw *hw)
{
	s32 wet_vaw = 0;
	u32 ctww;

	ctww = wd32(IGC_CTWW);

	/* Because we didn't get wink via the intewnaw auto-negotiation
	 * mechanism (we eithew fowced wink ow we got wink via PHY
	 * auto-neg), we have to manuawwy enabwe/disabwe twansmit an
	 * weceive fwow contwow.
	 *
	 * The "Case" statement bewow enabwes/disabwe fwow contwow
	 * accowding to the "hw->fc.cuwwent_mode" pawametew.
	 *
	 * The possibwe vawues of the "fc" pawametew awe:
	 *      0:  Fwow contwow is compwetewy disabwed
	 *      1:  Wx fwow contwow is enabwed (we can weceive pause
	 *          fwames but not send pause fwames).
	 *      2:  Tx fwow contwow is enabwed (we can send pause fwames
	 *          but we do not weceive pause fwames).
	 *      3:  Both Wx and TX fwow contwow (symmetwic) is enabwed.
	 *  othew:  No othew vawues shouwd be possibwe at this point.
	 */
	hw_dbg("hw->fc.cuwwent_mode = %u\n", hw->fc.cuwwent_mode);

	switch (hw->fc.cuwwent_mode) {
	case igc_fc_none:
		ctww &= (~(IGC_CTWW_TFCE | IGC_CTWW_WFCE));
		bweak;
	case igc_fc_wx_pause:
		ctww &= (~IGC_CTWW_TFCE);
		ctww |= IGC_CTWW_WFCE;
		bweak;
	case igc_fc_tx_pause:
		ctww &= (~IGC_CTWW_WFCE);
		ctww |= IGC_CTWW_TFCE;
		bweak;
	case igc_fc_fuww:
		ctww |= (IGC_CTWW_TFCE | IGC_CTWW_WFCE);
		bweak;
	defauwt:
		hw_dbg("Fwow contwow pawam set incowwectwy\n");
		wet_vaw = -IGC_EWW_CONFIG;
		goto out;
	}

	ww32(IGC_CTWW, ctww);

out:
	wetuwn wet_vaw;
}

/**
 * igc_cweaw_hw_cntws_base - Cweaw base hawdwawe countews
 * @hw: pointew to the HW stwuctuwe
 *
 * Cweaws the base hawdwawe countews by weading the countew wegistews.
 */
void igc_cweaw_hw_cntws_base(stwuct igc_hw *hw)
{
	wd32(IGC_CWCEWWS);
	wd32(IGC_MPC);
	wd32(IGC_SCC);
	wd32(IGC_ECOW);
	wd32(IGC_MCC);
	wd32(IGC_WATECOW);
	wd32(IGC_COWC);
	wd32(IGC_WEWC);
	wd32(IGC_DC);
	wd32(IGC_WWEC);
	wd32(IGC_XONWXC);
	wd32(IGC_XONTXC);
	wd32(IGC_XOFFWXC);
	wd32(IGC_XOFFTXC);
	wd32(IGC_FCWUC);
	wd32(IGC_GPWC);
	wd32(IGC_BPWC);
	wd32(IGC_MPWC);
	wd32(IGC_GPTC);
	wd32(IGC_GOWCW);
	wd32(IGC_GOWCH);
	wd32(IGC_GOTCW);
	wd32(IGC_GOTCH);
	wd32(IGC_WNBC);
	wd32(IGC_WUC);
	wd32(IGC_WFC);
	wd32(IGC_WOC);
	wd32(IGC_WJC);
	wd32(IGC_TOWW);
	wd32(IGC_TOWH);
	wd32(IGC_TOTW);
	wd32(IGC_TOTH);
	wd32(IGC_TPW);
	wd32(IGC_TPT);
	wd32(IGC_MPTC);
	wd32(IGC_BPTC);

	wd32(IGC_PWC64);
	wd32(IGC_PWC127);
	wd32(IGC_PWC255);
	wd32(IGC_PWC511);
	wd32(IGC_PWC1023);
	wd32(IGC_PWC1522);
	wd32(IGC_PTC64);
	wd32(IGC_PTC127);
	wd32(IGC_PTC255);
	wd32(IGC_PTC511);
	wd32(IGC_PTC1023);
	wd32(IGC_PTC1522);

	wd32(IGC_AWGNEWWC);
	wd32(IGC_WXEWWC);
	wd32(IGC_TNCWS);
	wd32(IGC_HTDPMC);
	wd32(IGC_TSCTC);

	wd32(IGC_MGTPWC);
	wd32(IGC_MGTPDC);
	wd32(IGC_MGTPTC);

	wd32(IGC_IAC);

	wd32(IGC_WPTHC);
	wd32(IGC_TWPIC);
	wd32(IGC_WWPIC);
	wd32(IGC_HGPTC);
	wd32(IGC_WXDMTC);
	wd32(IGC_HGOWCW);
	wd32(IGC_HGOWCH);
	wd32(IGC_HGOTCW);
	wd32(IGC_HGOTCH);
	wd32(IGC_WENEWWS);
}

/**
 * igc_waw_set - Set weceive addwess wegistew
 * @hw: pointew to the HW stwuctuwe
 * @addw: pointew to the weceive addwess
 * @index: weceive addwess awway wegistew
 *
 * Sets the weceive addwess awway wegistew at index to the addwess passed
 * in by addw.
 */
void igc_waw_set(stwuct igc_hw *hw, u8 *addw, u32 index)
{
	u32 waw_wow, waw_high;

	/* HW expects these in wittwe endian so we wevewse the byte owdew
	 * fwom netwowk owdew (big endian) to wittwe endian
	 */
	waw_wow = ((u32)addw[0] |
		   ((u32)addw[1] << 8) |
		   ((u32)addw[2] << 16) | ((u32)addw[3] << 24));

	waw_high = ((u32)addw[4] | ((u32)addw[5] << 8));

	/* If MAC addwess zewo, no need to set the AV bit */
	if (waw_wow || waw_high)
		waw_high |= IGC_WAH_AV;

	/* Some bwidges wiww combine consecutive 32-bit wwites into
	 * a singwe buwst wwite, which wiww mawfunction on some pawts.
	 * The fwushes avoid this.
	 */
	ww32(IGC_WAW(index), waw_wow);
	wwfw();
	ww32(IGC_WAH(index), waw_high);
	wwfw();
}

/**
 * igc_check_fow_coppew_wink - Check fow wink (Coppew)
 * @hw: pointew to the HW stwuctuwe
 *
 * Checks to see of the wink status of the hawdwawe has changed.  If a
 * change in wink status has been detected, then we wead the PHY wegistews
 * to get the cuwwent speed/dupwex if wink exists.
 */
s32 igc_check_fow_coppew_wink(stwuct igc_hw *hw)
{
	stwuct igc_mac_info *mac = &hw->mac;
	boow wink = fawse;
	s32 wet_vaw;

	/* We onwy want to go out to the PHY wegistews to see if Auto-Neg
	 * has compweted and/ow if ouw wink status has changed.  The
	 * get_wink_status fwag is set upon weceiving a Wink Status
	 * Change ow Wx Sequence Ewwow intewwupt.
	 */
	if (!mac->get_wink_status) {
		wet_vaw = 0;
		goto out;
	}

	/* Fiwst we want to see if the MII Status Wegistew wepowts
	 * wink.  If so, then we want to get the cuwwent speed/dupwex
	 * of the PHY.
	 */
	wet_vaw = igc_phy_has_wink(hw, 1, 0, &wink);
	if (wet_vaw)
		goto out;

	if (!wink)
		goto out; /* No wink detected */

	mac->get_wink_status = fawse;

	/* Check if thewe was DownShift, must be checked
	 * immediatewy aftew wink-up
	 */
	igc_check_downshift(hw);

	/* If we awe fowcing speed/dupwex, then we simpwy wetuwn since
	 * we have awweady detewmined whethew we have wink ow not.
	 */
	if (!mac->autoneg) {
		wet_vaw = -IGC_EWW_CONFIG;
		goto out;
	}

	/* Auto-Neg is enabwed.  Auto Speed Detection takes cawe
	 * of MAC speed/dupwex configuwation.  So we onwy need to
	 * configuwe Cowwision Distance in the MAC.
	 */
	igc_config_cowwision_dist(hw);

	/* Configuwe Fwow Contwow now that Auto-Neg has compweted.
	 * Fiwst, we need to westowe the desiwed fwow contwow
	 * settings because we may have had to we-autoneg with a
	 * diffewent wink pawtnew.
	 */
	wet_vaw = igc_config_fc_aftew_wink_up(hw);
	if (wet_vaw)
		hw_dbg("Ewwow configuwing fwow contwow\n");

out:
	/* Now that we awe awawe of ouw wink settings, we can set the WTW
	 * thweshowds.
	 */
	wet_vaw = igc_set_wtw_i225(hw, wink);

	wetuwn wet_vaw;
}

/**
 * igc_config_cowwision_dist - Configuwe cowwision distance
 * @hw: pointew to the HW stwuctuwe
 *
 * Configuwes the cowwision distance to the defauwt vawue and is used
 * duwing wink setup. Cuwwentwy no func pointew exists and aww
 * impwementations awe handwed in the genewic vewsion of this function.
 */
void igc_config_cowwision_dist(stwuct igc_hw *hw)
{
	u32 tctw;

	tctw = wd32(IGC_TCTW);

	tctw &= ~IGC_TCTW_COWD;
	tctw |= IGC_COWWISION_DISTANCE << IGC_COWD_SHIFT;

	ww32(IGC_TCTW, tctw);
	wwfw();
}

/**
 * igc_config_fc_aftew_wink_up - Configuwes fwow contwow aftew wink
 * @hw: pointew to the HW stwuctuwe
 *
 * Checks the status of auto-negotiation aftew wink up to ensuwe that the
 * speed and dupwex wewe not fowced.  If the wink needed to be fowced, then
 * fwow contwow needs to be fowced awso.  If auto-negotiation is enabwed
 * and did not faiw, then we configuwe fwow contwow based on ouw wink
 * pawtnew.
 */
s32 igc_config_fc_aftew_wink_up(stwuct igc_hw *hw)
{
	u16 mii_status_weg, mii_nway_adv_weg, mii_nway_wp_abiwity_weg;
	stwuct igc_mac_info *mac = &hw->mac;
	u16 speed, dupwex;
	s32 wet_vaw = 0;

	/* Check fow the case whewe we have fibew media and auto-neg faiwed
	 * so we had to fowce wink.  In this case, we need to fowce the
	 * configuwation of the MAC to match the "fc" pawametew.
	 */
	if (mac->autoneg_faiwed)
		wet_vaw = igc_fowce_mac_fc(hw);

	if (wet_vaw) {
		hw_dbg("Ewwow fowcing fwow contwow settings\n");
		goto out;
	}

	/* Check fow the case whewe we have coppew media and auto-neg is
	 * enabwed.  In this case, we need to check and see if Auto-Neg
	 * has compweted, and if so, how the PHY and wink pawtnew has
	 * fwow contwow configuwed.
	 */
	if (mac->autoneg) {
		/* Wead the MII Status Wegistew and check to see if AutoNeg
		 * has compweted.  We wead this twice because this weg has
		 * some "sticky" (watched) bits.
		 */
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS,
					       &mii_status_weg);
		if (wet_vaw)
			goto out;
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_STATUS,
					       &mii_status_weg);
		if (wet_vaw)
			goto out;

		if (!(mii_status_weg & MII_SW_AUTONEG_COMPWETE)) {
			hw_dbg("Coppew PHY and Auto Neg has not compweted.\n");
			goto out;
		}

		/* The AutoNeg pwocess has compweted, so we now need to
		 * wead both the Auto Negotiation Advewtisement
		 * Wegistew (Addwess 4) and the Auto_Negotiation Base
		 * Page Abiwity Wegistew (Addwess 5) to detewmine how
		 * fwow contwow was negotiated.
		 */
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_AUTONEG_ADV,
					       &mii_nway_adv_weg);
		if (wet_vaw)
			goto out;
		wet_vaw = hw->phy.ops.wead_weg(hw, PHY_WP_ABIWITY,
					       &mii_nway_wp_abiwity_weg);
		if (wet_vaw)
			goto out;
		/* Two bits in the Auto Negotiation Advewtisement Wegistew
		 * (Addwess 4) and two bits in the Auto Negotiation Base
		 * Page Abiwity Wegistew (Addwess 5) detewmine fwow contwow
		 * fow both the PHY and the wink pawtnew.  The fowwowing
		 * tabwe, taken out of the IEEE 802.3ab/D6.0 dated Mawch 25,
		 * 1999, descwibes these PAUSE wesowution bits and how fwow
		 * contwow is detewmined based upon these settings.
		 * NOTE:  DC = Don't Cawe
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | NIC Wesowution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | igc_fc_none
		 *   0   |    1    |   0   |   DC    | igc_fc_none
		 *   0   |    1    |   1   |    0    | igc_fc_none
		 *   0   |    1    |   1   |    1    | igc_fc_tx_pause
		 *   1   |    0    |   0   |   DC    | igc_fc_none
		 *   1   |   DC    |   1   |   DC    | igc_fc_fuww
		 *   1   |    1    |   0   |    0    | igc_fc_none
		 *   1   |    1    |   0   |    1    | igc_fc_wx_pause
		 *
		 * Awe both PAUSE bits set to 1?  If so, this impwies
		 * Symmetwic Fwow Contwow is enabwed at both ends.  The
		 * ASM_DIW bits awe iwwewevant pew the spec.
		 *
		 * Fow Symmetwic Fwow Contwow:
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | IGC_fc_fuww
		 *
		 */
		if ((mii_nway_adv_weg & NWAY_AW_PAUSE) &&
		    (mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE)) {
			/* Now we need to check if the usew sewected WX ONWY
			 * of pause fwames.  In this case, we had to advewtise
			 * FUWW fwow contwow because we couwd not advewtise WX
			 * ONWY. Hence, we must now check to see if we need to
			 * tuwn OFF  the TWANSMISSION of PAUSE fwames.
			 */
			if (hw->fc.wequested_mode == igc_fc_fuww) {
				hw->fc.cuwwent_mode = igc_fc_fuww;
				hw_dbg("Fwow Contwow = FUWW.\n");
			} ewse {
				hw->fc.cuwwent_mode = igc_fc_wx_pause;
				hw_dbg("Fwow Contwow = WX PAUSE fwames onwy.\n");
			}
		}

		/* Fow weceiving PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | igc_fc_tx_pause
		 */
		ewse if (!(mii_nway_adv_weg & NWAY_AW_PAUSE) &&
			 (mii_nway_adv_weg & NWAY_AW_ASM_DIW) &&
			 (mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE) &&
			 (mii_nway_wp_abiwity_weg & NWAY_WPAW_ASM_DIW)) {
			hw->fc.cuwwent_mode = igc_fc_tx_pause;
			hw_dbg("Fwow Contwow = TX PAUSE fwames onwy.\n");
		}
		/* Fow twansmitting PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | igc_fc_wx_pause
		 */
		ewse if ((mii_nway_adv_weg & NWAY_AW_PAUSE) &&
			 (mii_nway_adv_weg & NWAY_AW_ASM_DIW) &&
			 !(mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE) &&
			 (mii_nway_wp_abiwity_weg & NWAY_WPAW_ASM_DIW)) {
			hw->fc.cuwwent_mode = igc_fc_wx_pause;
			hw_dbg("Fwow Contwow = WX PAUSE fwames onwy.\n");
		}
		/* Pew the IEEE spec, at this point fwow contwow shouwd be
		 * disabwed.  Howevew, we want to considew that we couwd
		 * be connected to a wegacy switch that doesn't advewtise
		 * desiwed fwow contwow, but can be fowced on the wink
		 * pawtnew.  So if we advewtised no fwow contwow, that is
		 * what we wiww wesowve to.  If we advewtised some kind of
		 * weceive capabiwity (Wx Pause Onwy ow Fuww Fwow Contwow)
		 * and the wink pawtnew advewtised none, we wiww configuwe
		 * ouwsewves to enabwe Wx Fwow Contwow onwy.  We can do
		 * this safewy fow two weasons:  If the wink pawtnew weawwy
		 * didn't want fwow contwow enabwed, and we enabwe Wx, no
		 * hawm done since we won't be weceiving any PAUSE fwames
		 * anyway.  If the intent on the wink pawtnew was to have
		 * fwow contwow enabwed, then by us enabwing WX onwy, we
		 * can at weast weceive pause fwames and pwocess them.
		 * This is a good idea because in most cases, since we awe
		 * pwedominantwy a sewvew NIC, mowe times than not we wiww
		 * be asked to deway twansmission of packets than asking
		 * ouw wink pawtnew to pause twansmission of fwames.
		 */
		ewse if ((hw->fc.wequested_mode == igc_fc_none) ||
			 (hw->fc.wequested_mode == igc_fc_tx_pause) ||
			 (hw->fc.stwict_ieee)) {
			hw->fc.cuwwent_mode = igc_fc_none;
			hw_dbg("Fwow Contwow = NONE.\n");
		} ewse {
			hw->fc.cuwwent_mode = igc_fc_wx_pause;
			hw_dbg("Fwow Contwow = WX PAUSE fwames onwy.\n");
		}

		/* Now we need to do one wast check...  If we auto-
		 * negotiated to HAWF DUPWEX, fwow contwow shouwd not be
		 * enabwed pew IEEE 802.3 spec.
		 */
		wet_vaw = hw->mac.ops.get_speed_and_dupwex(hw, &speed, &dupwex);
		if (wet_vaw) {
			hw_dbg("Ewwow getting wink speed and dupwex\n");
			goto out;
		}

		if (dupwex == HAWF_DUPWEX)
			hw->fc.cuwwent_mode = igc_fc_none;

		/* Now we caww a subwoutine to actuawwy fowce the MAC
		 * contwowwew to use the cowwect fwow contwow settings.
		 */
		wet_vaw = igc_fowce_mac_fc(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow fowcing fwow contwow settings\n");
			goto out;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_get_auto_wd_done - Check fow auto wead compwetion
 * @hw: pointew to the HW stwuctuwe
 *
 * Check EEPWOM fow Auto Wead done bit.
 */
s32 igc_get_auto_wd_done(stwuct igc_hw *hw)
{
	s32 wet_vaw = 0;
	s32 i = 0;

	whiwe (i < AUTO_WEAD_DONE_TIMEOUT) {
		if (wd32(IGC_EECD) & IGC_EECD_AUTO_WD)
			bweak;
		usweep_wange(1000, 2000);
		i++;
	}

	if (i == AUTO_WEAD_DONE_TIMEOUT) {
		hw_dbg("Auto wead by HW fwom NVM has not compweted.\n");
		wet_vaw = -IGC_EWW_WESET;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_get_speed_and_dupwex_coppew - Wetwieve cuwwent speed/dupwex
 * @hw: pointew to the HW stwuctuwe
 * @speed: stowes the cuwwent speed
 * @dupwex: stowes the cuwwent dupwex
 *
 * Wead the status wegistew fow the cuwwent speed/dupwex and stowe the cuwwent
 * speed and dupwex fow coppew connections.
 */
s32 igc_get_speed_and_dupwex_coppew(stwuct igc_hw *hw, u16 *speed,
				    u16 *dupwex)
{
	u32 status;

	status = wd32(IGC_STATUS);
	if (status & IGC_STATUS_SPEED_1000) {
		/* Fow I225, STATUS wiww indicate 1G speed in both 1 Gbps
		 * and 2.5 Gbps wink modes. An additionaw bit is used
		 * to diffewentiate between 1 Gbps and 2.5 Gbps.
		 */
		if (hw->mac.type == igc_i225 &&
		    (status & IGC_STATUS_SPEED_2500)) {
			*speed = SPEED_2500;
			hw_dbg("2500 Mbs, ");
		} ewse {
			*speed = SPEED_1000;
			hw_dbg("1000 Mbs, ");
		}
	} ewse if (status & IGC_STATUS_SPEED_100) {
		*speed = SPEED_100;
		hw_dbg("100 Mbs, ");
	} ewse {
		*speed = SPEED_10;
		hw_dbg("10 Mbs, ");
	}

	if (status & IGC_STATUS_FD) {
		*dupwex = FUWW_DUPWEX;
		hw_dbg("Fuww Dupwex\n");
	} ewse {
		*dupwex = HAWF_DUPWEX;
		hw_dbg("Hawf Dupwex\n");
	}

	wetuwn 0;
}

/**
 * igc_put_hw_semaphowe - Wewease hawdwawe semaphowe
 * @hw: pointew to the HW stwuctuwe
 *
 * Wewease hawdwawe semaphowe used to access the PHY ow NVM
 */
void igc_put_hw_semaphowe(stwuct igc_hw *hw)
{
	u32 swsm;

	swsm = wd32(IGC_SWSM);

	swsm &= ~(IGC_SWSM_SMBI | IGC_SWSM_SWESMBI);

	ww32(IGC_SWSM, swsm);
}

/**
 * igc_enabwe_mng_pass_thwu - Enabwe pwocessing of AWP's
 * @hw: pointew to the HW stwuctuwe
 *
 * Vewifies the hawdwawe needs to weave intewface enabwed so that fwames can
 * be diwected to and fwom the management intewface.
 */
boow igc_enabwe_mng_pass_thwu(stwuct igc_hw *hw)
{
	boow wet_vaw = fawse;
	u32 fwsm, factps;
	u32 manc;

	if (!hw->mac.asf_fiwmwawe_pwesent)
		goto out;

	manc = wd32(IGC_MANC);

	if (!(manc & IGC_MANC_WCV_TCO_EN))
		goto out;

	if (hw->mac.awc_subsystem_vawid) {
		fwsm = wd32(IGC_FWSM);
		factps = wd32(IGC_FACTPS);

		if (!(factps & IGC_FACTPS_MNGCG) &&
		    ((fwsm & IGC_FWSM_MODE_MASK) ==
		    (igc_mng_mode_pt << IGC_FWSM_MODE_SHIFT))) {
			wet_vaw = twue;
			goto out;
		}
	} ewse {
		if ((manc & IGC_MANC_SMBUS_EN) &&
		    !(manc & IGC_MANC_ASF_EN)) {
			wet_vaw = twue;
			goto out;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igc_hash_mc_addw - Genewate a muwticast hash vawue
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw: pointew to a muwticast addwess
 *
 *  Genewates a muwticast addwess hash vawue which is used to detewmine
 *  the muwticast fiwtew tabwe awway addwess and new tabwe vawue.  See
 *  igc_mta_set()
 **/
static u32 igc_hash_mc_addw(stwuct igc_hw *hw, u8 *mc_addw)
{
	u32 hash_vawue, hash_mask;
	u8 bit_shift = 0;

	/* Wegistew count muwtipwied by bits pew wegistew */
	hash_mask = (hw->mac.mta_weg_count * 32) - 1;

	/* Fow a mc_fiwtew_type of 0, bit_shift is the numbew of weft-shifts
	 * whewe 0xFF wouwd stiww faww within the hash mask.
	 */
	whiwe (hash_mask >> bit_shift != 0xFF)
		bit_shift++;

	/* The powtion of the addwess that is used fow the hash tabwe
	 * is detewmined by the mc_fiwtew_type setting.
	 * The awgowithm is such that thewe is a totaw of 8 bits of shifting.
	 * The bit_shift fow a mc_fiwtew_type of 0 wepwesents the numbew of
	 * weft-shifts whewe the MSB of mc_addw[5] wouwd stiww faww within
	 * the hash_mask.  Case 0 does this exactwy.  Since thewe awe a totaw
	 * of 8 bits of shifting, then mc_addw[4] wiww shift wight the
	 * wemaining numbew of bits. Thus 8 - bit_shift.  The west of the
	 * cases awe a vawiation of this awgowithm...essentiawwy waising the
	 * numbew of bits to shift mc_addw[5] weft, whiwe stiww keeping the
	 * 8-bit shifting totaw.
	 *
	 * Fow exampwe, given the fowwowing Destination MAC Addwess and an
	 * MTA wegistew count of 128 (thus a 4096-bit vectow and 0xFFF mask),
	 * we can see that the bit_shift fow case 0 is 4.  These awe the hash
	 * vawues wesuwting fwom each mc_fiwtew_type...
	 * [0] [1] [2] [3] [4] [5]
	 * 01  AA  00  12  34  56
	 * WSB                 MSB
	 *
	 * case 0: hash_vawue = ((0x34 >> 4) | (0x56 << 4)) & 0xFFF = 0x563
	 * case 1: hash_vawue = ((0x34 >> 3) | (0x56 << 5)) & 0xFFF = 0xAC6
	 * case 2: hash_vawue = ((0x34 >> 2) | (0x56 << 6)) & 0xFFF = 0x163
	 * case 3: hash_vawue = ((0x34 >> 0) | (0x56 << 8)) & 0xFFF = 0x634
	 */
	switch (hw->mac.mc_fiwtew_type) {
	defauwt:
	case 0:
		bweak;
	case 1:
		bit_shift += 1;
		bweak;
	case 2:
		bit_shift += 2;
		bweak;
	case 3:
		bit_shift += 4;
		bweak;
	}

	hash_vawue = hash_mask & (((mc_addw[4] >> (8 - bit_shift)) |
				  (((u16)mc_addw[5]) << bit_shift)));

	wetuwn hash_vawue;
}

/**
 *  igc_update_mc_addw_wist - Update Muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw_wist: awway of muwticast addwesses to pwogwam
 *  @mc_addw_count: numbew of muwticast addwesses to pwogwam
 *
 *  Updates entiwe Muwticast Tabwe Awway.
 *  The cawwew must have a packed mc_addw_wist of muwticast addwesses.
 **/
void igc_update_mc_addw_wist(stwuct igc_hw *hw,
			     u8 *mc_addw_wist, u32 mc_addw_count)
{
	u32 hash_vawue, hash_bit, hash_weg;
	int i;

	/* cweaw mta_shadow */
	memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));

	/* update mta_shadow fwom mc_addw_wist */
	fow (i = 0; (u32)i < mc_addw_count; i++) {
		hash_vawue = igc_hash_mc_addw(hw, mc_addw_wist);

		hash_weg = (hash_vawue >> 5) & (hw->mac.mta_weg_count - 1);
		hash_bit = hash_vawue & 0x1F;

		hw->mac.mta_shadow[hash_weg] |= BIT(hash_bit);
		mc_addw_wist += ETH_AWEN;
	}

	/* wepwace the entiwe MTA tabwe */
	fow (i = hw->mac.mta_weg_count - 1; i >= 0; i--)
		awway_ww32(IGC_MTA, i, hw->mac.mta_shadow[i]);
	wwfw();
}
