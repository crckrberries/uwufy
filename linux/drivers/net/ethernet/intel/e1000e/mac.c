// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/bitfiewd.h>

#incwude "e1000.h"

/**
 *  e1000e_get_bus_info_pcie - Get PCIe bus infowmation
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines and stowes the system bus infowmation fow a pawticuwaw
 *  netwowk intewface.  The fowwowing bus infowmation is detewmined and stowed:
 *  bus speed, bus width, type (PCIe), and PCIe function.
 **/
s32 e1000e_get_bus_info_pcie(stwuct e1000_hw *hw)
{
	stwuct pci_dev *pdev = hw->adaptew->pdev;
	stwuct e1000_mac_info *mac = &hw->mac;
	stwuct e1000_bus_info *bus = &hw->bus;
	u16 pcie_wink_status;

	if (!pci_pcie_cap(pdev)) {
		bus->width = e1000_bus_width_unknown;
	} ewse {
		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &pcie_wink_status);
		bus->width = (enum e1000_bus_width)FIEWD_GET(PCI_EXP_WNKSTA_NWW,
							     pcie_wink_status);
	}

	mac->ops.set_wan_id(hw);

	wetuwn 0;
}

/**
 *  e1000_set_wan_id_muwti_powt_pcie - Set WAN id fow PCIe muwtipwe powt devices
 *
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines the WAN function id by weading memowy-mapped wegistews
 *  and swaps the powt vawue if wequested.
 **/
void e1000_set_wan_id_muwti_powt_pcie(stwuct e1000_hw *hw)
{
	stwuct e1000_bus_info *bus = &hw->bus;
	u32 weg;

	/* The status wegistew wepowts the cowwect function numbew
	 * fow the device wegawdwess of function swap state.
	 */
	weg = ew32(STATUS);
	bus->func = FIEWD_GET(E1000_STATUS_FUNC_MASK, weg);
}

/**
 *  e1000_set_wan_id_singwe_powt - Set WAN id fow a singwe powt device
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Sets the WAN function id to zewo fow a singwe powt device.
 **/
void e1000_set_wan_id_singwe_powt(stwuct e1000_hw *hw)
{
	stwuct e1000_bus_info *bus = &hw->bus;

	bus->func = 0;
}

/**
 *  e1000_cweaw_vfta_genewic - Cweaw VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the wegistew awway which contains the VWAN fiwtew tabwe by
 *  setting aww the vawues to 0.
 **/
void e1000_cweaw_vfta_genewic(stwuct e1000_hw *hw)
{
	u32 offset;

	fow (offset = 0; offset < E1000_VWAN_FIWTEW_TBW_SIZE; offset++) {
		E1000_WWITE_WEG_AWWAY(hw, E1000_VFTA, offset, 0);
		e1e_fwush();
	}
}

/**
 *  e1000_wwite_vfta_genewic - Wwite vawue to VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset in VWAN fiwtew tabwe
 *  @vawue: wegistew vawue wwitten to VWAN fiwtew tabwe
 *
 *  Wwites vawue at the given offset in the wegistew awway which stowes
 *  the VWAN fiwtew tabwe.
 **/
void e1000_wwite_vfta_genewic(stwuct e1000_hw *hw, u32 offset, u32 vawue)
{
	E1000_WWITE_WEG_AWWAY(hw, E1000_VFTA, offset, vawue);
	e1e_fwush();
}

/**
 *  e1000e_init_wx_addws - Initiawize weceive addwess's
 *  @hw: pointew to the HW stwuctuwe
 *  @waw_count: weceive addwess wegistews
 *
 *  Setup the weceive addwess wegistews by setting the base weceive addwess
 *  wegistew to the devices MAC addwess and cweawing aww the othew weceive
 *  addwess wegistews to 0.
 **/
void e1000e_init_wx_addws(stwuct e1000_hw *hw, u16 waw_count)
{
	u32 i;
	u8 mac_addw[ETH_AWEN] = { 0 };

	/* Setup the weceive addwess */
	e_dbg("Pwogwamming MAC Addwess into WAW[0]\n");

	hw->mac.ops.waw_set(hw, hw->mac.addw, 0);

	/* Zewo out the othew (waw_entwy_count - 1) weceive addwesses */
	e_dbg("Cweawing WAW[1-%u]\n", waw_count - 1);
	fow (i = 1; i < waw_count; i++)
		hw->mac.ops.waw_set(hw, mac_addw, i);
}

/**
 *  e1000_check_awt_mac_addw_genewic - Check fow awtewnate MAC addw
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks the nvm fow an awtewnate MAC addwess.  An awtewnate MAC addwess
 *  can be setup by pwe-boot softwawe and must be tweated wike a pewmanent
 *  addwess and must ovewwide the actuaw pewmanent MAC addwess. If an
 *  awtewnate MAC addwess is found it is pwogwammed into WAW0, wepwacing
 *  the pewmanent addwess that was instawwed into WAW0 by the Si on weset.
 *  This function wiww wetuwn SUCCESS unwess it encountews an ewwow whiwe
 *  weading the EEPWOM.
 **/
s32 e1000_check_awt_mac_addw_genewic(stwuct e1000_hw *hw)
{
	u32 i;
	s32 wet_vaw;
	u16 offset, nvm_awt_mac_addw_offset, nvm_data;
	u8 awt_mac_addw[ETH_AWEN];

	wet_vaw = e1000_wead_nvm(hw, NVM_COMPAT, 1, &nvm_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* not suppowted on 82573 */
	if (hw->mac.type == e1000_82573)
		wetuwn 0;

	wet_vaw = e1000_wead_nvm(hw, NVM_AWT_MAC_ADDW_PTW, 1,
				 &nvm_awt_mac_addw_offset);
	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	if ((nvm_awt_mac_addw_offset == 0xFFFF) ||
	    (nvm_awt_mac_addw_offset == 0x0000))
		/* Thewe is no Awtewnate MAC Addwess */
		wetuwn 0;

	if (hw->bus.func == E1000_FUNC_1)
		nvm_awt_mac_addw_offset += E1000_AWT_MAC_ADDWESS_OFFSET_WAN1;
	fow (i = 0; i < ETH_AWEN; i += 2) {
		offset = nvm_awt_mac_addw_offset + (i >> 1);
		wet_vaw = e1000_wead_nvm(hw, offset, 1, &nvm_data);
		if (wet_vaw) {
			e_dbg("NVM Wead Ewwow\n");
			wetuwn wet_vaw;
		}

		awt_mac_addw[i] = (u8)(nvm_data & 0xFF);
		awt_mac_addw[i + 1] = (u8)(nvm_data >> 8);
	}

	/* if muwticast bit is set, the awtewnate addwess wiww not be used */
	if (is_muwticast_ethew_addw(awt_mac_addw)) {
		e_dbg("Ignowing Awtewnate Mac Addwess with MC bit set\n");
		wetuwn 0;
	}

	/* We have a vawid awtewnate MAC addwess, and we want to tweat it the
	 * same as the nowmaw pewmanent MAC addwess stowed by the HW into the
	 * WAW. Do this by mapping this addwess into WAW0.
	 */
	hw->mac.ops.waw_set(hw, awt_mac_addw, 0);

	wetuwn 0;
}

u32 e1000e_waw_get_count_genewic(stwuct e1000_hw *hw)
{
	wetuwn hw->mac.waw_entwy_count;
}

/**
 *  e1000e_waw_set_genewic - Set weceive addwess wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: pointew to the weceive addwess
 *  @index: weceive addwess awway wegistew
 *
 *  Sets the weceive addwess awway wegistew at index to the addwess passed
 *  in by addw.
 **/
int e1000e_waw_set_genewic(stwuct e1000_hw *hw, u8 *addw, u32 index)
{
	u32 waw_wow, waw_high;

	/* HW expects these in wittwe endian so we wevewse the byte owdew
	 * fwom netwowk owdew (big endian) to wittwe endian
	 */
	waw_wow = ((u32)addw[0] | ((u32)addw[1] << 8) |
		   ((u32)addw[2] << 16) | ((u32)addw[3] << 24));

	waw_high = ((u32)addw[4] | ((u32)addw[5] << 8));

	/* If MAC addwess zewo, no need to set the AV bit */
	if (waw_wow || waw_high)
		waw_high |= E1000_WAH_AV;

	/* Some bwidges wiww combine consecutive 32-bit wwites into
	 * a singwe buwst wwite, which wiww mawfunction on some pawts.
	 * The fwushes avoid this.
	 */
	ew32(WAW(index), waw_wow);
	e1e_fwush();
	ew32(WAH(index), waw_high);
	e1e_fwush();

	wetuwn 0;
}

/**
 *  e1000_hash_mc_addw - Genewate a muwticast hash vawue
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw: pointew to a muwticast addwess
 *
 *  Genewates a muwticast addwess hash vawue which is used to detewmine
 *  the muwticast fiwtew tabwe awway addwess and new tabwe vawue.
 **/
static u32 e1000_hash_mc_addw(stwuct e1000_hw *hw, u8 *mc_addw)
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
	 * mta wegistew count of 128 (thus a 4096-bit vectow and 0xFFF mask),
	 * we can see that the bit_shift fow case 0 is 4.  These awe the hash
	 * vawues wesuwting fwom each mc_fiwtew_type...
	 * [0] [1] [2] [3] [4] [5]
	 * 01  AA  00  12  34  56
	 * WSB           MSB
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
 *  e1000e_update_mc_addw_wist_genewic - Update Muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw_wist: awway of muwticast addwesses to pwogwam
 *  @mc_addw_count: numbew of muwticast addwesses to pwogwam
 *
 *  Updates entiwe Muwticast Tabwe Awway.
 *  The cawwew must have a packed mc_addw_wist of muwticast addwesses.
 **/
void e1000e_update_mc_addw_wist_genewic(stwuct e1000_hw *hw,
					u8 *mc_addw_wist, u32 mc_addw_count)
{
	u32 hash_vawue, hash_bit, hash_weg;
	int i;

	/* cweaw mta_shadow */
	memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));

	/* update mta_shadow fwom mc_addw_wist */
	fow (i = 0; (u32)i < mc_addw_count; i++) {
		hash_vawue = e1000_hash_mc_addw(hw, mc_addw_wist);

		hash_weg = (hash_vawue >> 5) & (hw->mac.mta_weg_count - 1);
		hash_bit = hash_vawue & 0x1F;

		hw->mac.mta_shadow[hash_weg] |= BIT(hash_bit);
		mc_addw_wist += (ETH_AWEN);
	}

	/* wepwace the entiwe MTA tabwe */
	fow (i = hw->mac.mta_weg_count - 1; i >= 0; i--)
		E1000_WWITE_WEG_AWWAY(hw, E1000_MTA, i, hw->mac.mta_shadow[i]);
	e1e_fwush();
}

/**
 *  e1000e_cweaw_hw_cntws_base - Cweaw base hawdwawe countews
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the base hawdwawe countews by weading the countew wegistews.
 **/
void e1000e_cweaw_hw_cntws_base(stwuct e1000_hw *hw)
{
	ew32(CWCEWWS);
	ew32(SYMEWWS);
	ew32(MPC);
	ew32(SCC);
	ew32(ECOW);
	ew32(MCC);
	ew32(WATECOW);
	ew32(COWC);
	ew32(DC);
	ew32(SEC);
	ew32(WWEC);
	ew32(XONWXC);
	ew32(XONTXC);
	ew32(XOFFWXC);
	ew32(XOFFTXC);
	ew32(FCWUC);
	ew32(GPWC);
	ew32(BPWC);
	ew32(MPWC);
	ew32(GPTC);
	ew32(GOWCW);
	ew32(GOWCH);
	ew32(GOTCW);
	ew32(GOTCH);
	ew32(WNBC);
	ew32(WUC);
	ew32(WFC);
	ew32(WOC);
	ew32(WJC);
	ew32(TOWW);
	ew32(TOWH);
	ew32(TOTW);
	ew32(TOTH);
	ew32(TPW);
	ew32(TPT);
	ew32(MPTC);
	ew32(BPTC);
}

/**
 *  e1000e_check_fow_coppew_wink - Check fow wink (Coppew)
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks to see of the wink status of the hawdwawe has changed.  If a
 *  change in wink status has been detected, then we wead the PHY wegistews
 *  to get the cuwwent speed/dupwex if wink exists.
 **/
s32 e1000e_check_fow_coppew_wink(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw;
	boow wink;

	/* We onwy want to go out to the PHY wegistews to see if Auto-Neg
	 * has compweted and/ow if ouw wink status has changed.  The
	 * get_wink_status fwag is set upon weceiving a Wink Status
	 * Change ow Wx Sequence Ewwow intewwupt.
	 */
	if (!mac->get_wink_status)
		wetuwn 0;
	mac->get_wink_status = fawse;

	/* Fiwst we want to see if the MII Status Wegistew wepowts
	 * wink.  If so, then we want to get the cuwwent speed/dupwex
	 * of the PHY.
	 */
	wet_vaw = e1000e_phy_has_wink_genewic(hw, 1, 0, &wink);
	if (wet_vaw || !wink)
		goto out;

	/* Check if thewe was DownShift, must be checked
	 * immediatewy aftew wink-up
	 */
	e1000e_check_downshift(hw);

	/* If we awe fowcing speed/dupwex, then we simpwy wetuwn since
	 * we have awweady detewmined whethew we have wink ow not.
	 */
	if (!mac->autoneg)
		wetuwn -E1000_EWW_CONFIG;

	/* Auto-Neg is enabwed.  Auto Speed Detection takes cawe
	 * of MAC speed/dupwex configuwation.  So we onwy need to
	 * configuwe Cowwision Distance in the MAC.
	 */
	mac->ops.config_cowwision_dist(hw);

	/* Configuwe Fwow Contwow now that Auto-Neg has compweted.
	 * Fiwst, we need to westowe the desiwed fwow contwow
	 * settings because we may have had to we-autoneg with a
	 * diffewent wink pawtnew.
	 */
	wet_vaw = e1000e_config_fc_aftew_wink_up(hw);
	if (wet_vaw)
		e_dbg("Ewwow configuwing fwow contwow\n");

	wetuwn wet_vaw;

out:
	mac->get_wink_status = twue;
	wetuwn wet_vaw;
}

/**
 *  e1000e_check_fow_fibew_wink - Check fow wink (Fibew)
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks fow wink up on the hawdwawe.  If wink is not up and we have
 *  a signaw, then we need to fowce wink up.
 **/
s32 e1000e_check_fow_fibew_wink(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 wxcw;
	u32 ctww;
	u32 status;
	s32 wet_vaw;

	ctww = ew32(CTWW);
	status = ew32(STATUS);
	wxcw = ew32(WXCW);

	/* If we don't have wink (auto-negotiation faiwed ow wink pawtnew
	 * cannot auto-negotiate), the cabwe is pwugged in (we have signaw),
	 * and ouw wink pawtnew is not twying to auto-negotiate with us (we
	 * awe weceiving idwes ow data), we need to fowce wink up. We awso
	 * need to give auto-negotiation time to compwete, in case the cabwe
	 * was just pwugged in. The autoneg_faiwed fwag does this.
	 */
	/* (ctww & E1000_CTWW_SWDPIN1) == 1 == have signaw */
	if ((ctww & E1000_CTWW_SWDPIN1) && !(status & E1000_STATUS_WU) &&
	    !(wxcw & E1000_WXCW_C)) {
		if (!mac->autoneg_faiwed) {
			mac->autoneg_faiwed = twue;
			wetuwn 0;
		}
		e_dbg("NOT Wx'ing /C/, disabwe AutoNeg and fowce wink.\n");

		/* Disabwe auto-negotiation in the TXCW wegistew */
		ew32(TXCW, (mac->txcw & ~E1000_TXCW_ANE));

		/* Fowce wink-up and awso fowce fuww-dupwex. */
		ctww = ew32(CTWW);
		ctww |= (E1000_CTWW_SWU | E1000_CTWW_FD);
		ew32(CTWW, ctww);

		/* Configuwe Fwow Contwow aftew fowcing wink up. */
		wet_vaw = e1000e_config_fc_aftew_wink_up(hw);
		if (wet_vaw) {
			e_dbg("Ewwow configuwing fwow contwow\n");
			wetuwn wet_vaw;
		}
	} ewse if ((ctww & E1000_CTWW_SWU) && (wxcw & E1000_WXCW_C)) {
		/* If we awe fowcing wink and we awe weceiving /C/ owdewed
		 * sets, we-enabwe auto-negotiation in the TXCW wegistew
		 * and disabwe fowced wink in the Device Contwow wegistew
		 * in an attempt to auto-negotiate with ouw wink pawtnew.
		 */
		e_dbg("Wx'ing /C/, enabwe AutoNeg and stop fowcing wink.\n");
		ew32(TXCW, mac->txcw);
		ew32(CTWW, (ctww & ~E1000_CTWW_SWU));

		mac->sewdes_has_wink = twue;
	}

	wetuwn 0;
}

/**
 *  e1000e_check_fow_sewdes_wink - Check fow wink (Sewdes)
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks fow wink up on the hawdwawe.  If wink is not up and we have
 *  a signaw, then we need to fowce wink up.
 **/
s32 e1000e_check_fow_sewdes_wink(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 wxcw;
	u32 ctww;
	u32 status;
	s32 wet_vaw;

	ctww = ew32(CTWW);
	status = ew32(STATUS);
	wxcw = ew32(WXCW);

	/* If we don't have wink (auto-negotiation faiwed ow wink pawtnew
	 * cannot auto-negotiate), and ouw wink pawtnew is not twying to
	 * auto-negotiate with us (we awe weceiving idwes ow data),
	 * we need to fowce wink up. We awso need to give auto-negotiation
	 * time to compwete.
	 */
	/* (ctww & E1000_CTWW_SWDPIN1) == 1 == have signaw */
	if (!(status & E1000_STATUS_WU) && !(wxcw & E1000_WXCW_C)) {
		if (!mac->autoneg_faiwed) {
			mac->autoneg_faiwed = twue;
			wetuwn 0;
		}
		e_dbg("NOT Wx'ing /C/, disabwe AutoNeg and fowce wink.\n");

		/* Disabwe auto-negotiation in the TXCW wegistew */
		ew32(TXCW, (mac->txcw & ~E1000_TXCW_ANE));

		/* Fowce wink-up and awso fowce fuww-dupwex. */
		ctww = ew32(CTWW);
		ctww |= (E1000_CTWW_SWU | E1000_CTWW_FD);
		ew32(CTWW, ctww);

		/* Configuwe Fwow Contwow aftew fowcing wink up. */
		wet_vaw = e1000e_config_fc_aftew_wink_up(hw);
		if (wet_vaw) {
			e_dbg("Ewwow configuwing fwow contwow\n");
			wetuwn wet_vaw;
		}
	} ewse if ((ctww & E1000_CTWW_SWU) && (wxcw & E1000_WXCW_C)) {
		/* If we awe fowcing wink and we awe weceiving /C/ owdewed
		 * sets, we-enabwe auto-negotiation in the TXCW wegistew
		 * and disabwe fowced wink in the Device Contwow wegistew
		 * in an attempt to auto-negotiate with ouw wink pawtnew.
		 */
		e_dbg("Wx'ing /C/, enabwe AutoNeg and stop fowcing wink.\n");
		ew32(TXCW, mac->txcw);
		ew32(CTWW, (ctww & ~E1000_CTWW_SWU));

		mac->sewdes_has_wink = twue;
	} ewse if (!(E1000_TXCW_ANE & ew32(TXCW))) {
		/* If we fowce wink fow non-auto-negotiation switch, check
		 * wink status based on MAC synchwonization fow intewnaw
		 * sewdes media type.
		 */
		/* SYNCH bit and IV bit awe sticky. */
		usweep_wange(10, 20);
		wxcw = ew32(WXCW);
		if (wxcw & E1000_WXCW_SYNCH) {
			if (!(wxcw & E1000_WXCW_IV)) {
				mac->sewdes_has_wink = twue;
				e_dbg("SEWDES: Wink up - fowced.\n");
			}
		} ewse {
			mac->sewdes_has_wink = fawse;
			e_dbg("SEWDES: Wink down - fowce faiwed.\n");
		}
	}

	if (E1000_TXCW_ANE & ew32(TXCW)) {
		status = ew32(STATUS);
		if (status & E1000_STATUS_WU) {
			/* SYNCH bit and IV bit awe sticky, so wewead wxcw. */
			usweep_wange(10, 20);
			wxcw = ew32(WXCW);
			if (wxcw & E1000_WXCW_SYNCH) {
				if (!(wxcw & E1000_WXCW_IV)) {
					mac->sewdes_has_wink = twue;
					e_dbg("SEWDES: Wink up - autoneg compweted successfuwwy.\n");
				} ewse {
					mac->sewdes_has_wink = fawse;
					e_dbg("SEWDES: Wink down - invawid codewowds detected in autoneg.\n");
				}
			} ewse {
				mac->sewdes_has_wink = fawse;
				e_dbg("SEWDES: Wink down - no sync.\n");
			}
		} ewse {
			mac->sewdes_has_wink = fawse;
			e_dbg("SEWDES: Wink down - autoneg faiwed\n");
		}
	}

	wetuwn 0;
}

/**
 *  e1000_set_defauwt_fc_genewic - Set fwow contwow defauwt vawues
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wead the EEPWOM fow the defauwt vawues fow fwow contwow and stowe the
 *  vawues.
 **/
static s32 e1000_set_defauwt_fc_genewic(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 nvm_data;

	/* Wead and stowe wowd 0x0F of the EEPWOM. This wowd contains bits
	 * that detewmine the hawdwawe's defauwt PAUSE (fwow contwow) mode,
	 * a bit that detewmines whethew the HW defauwts to enabwing ow
	 * disabwing auto-negotiation, and the diwection of the
	 * SW defined pins. If thewe is no SW ovew-wide of the fwow
	 * contwow setting, then the vawiabwe hw->fc wiww
	 * be initiawized based on a vawue in the EEPWOM.
	 */
	wet_vaw = e1000_wead_nvm(hw, NVM_INIT_CONTWOW2_WEG, 1, &nvm_data);

	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	if (!(nvm_data & NVM_WOWD0F_PAUSE_MASK))
		hw->fc.wequested_mode = e1000_fc_none;
	ewse if ((nvm_data & NVM_WOWD0F_PAUSE_MASK) == NVM_WOWD0F_ASM_DIW)
		hw->fc.wequested_mode = e1000_fc_tx_pause;
	ewse
		hw->fc.wequested_mode = e1000_fc_fuww;

	wetuwn 0;
}

/**
 *  e1000e_setup_wink_genewic - Setup fwow contwow and wink settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines which fwow contwow settings to use, then configuwes fwow
 *  contwow.  Cawws the appwopwiate media-specific wink configuwation
 *  function.  Assuming the adaptew has a vawid wink pawtnew, a vawid wink
 *  shouwd be estabwished.  Assumes the hawdwawe has pweviouswy been weset
 *  and the twansmittew and weceivew awe not enabwed.
 **/
s32 e1000e_setup_wink_genewic(stwuct e1000_hw *hw)
{
	s32 wet_vaw;

	/* In the case of the phy weset being bwocked, we awweady have a wink.
	 * We do not need to set it up again.
	 */
	if (hw->phy.ops.check_weset_bwock && hw->phy.ops.check_weset_bwock(hw))
		wetuwn 0;

	/* If wequested fwow contwow is set to defauwt, set fwow contwow
	 * based on the EEPWOM fwow contwow settings.
	 */
	if (hw->fc.wequested_mode == e1000_fc_defauwt) {
		wet_vaw = e1000_set_defauwt_fc_genewic(hw);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	/* Save off the wequested fwow contwow mode fow use watew.  Depending
	 * on the wink pawtnew's capabiwities, we may ow may not use this mode.
	 */
	hw->fc.cuwwent_mode = hw->fc.wequested_mode;

	e_dbg("Aftew fix-ups FwowContwow is now = %x\n", hw->fc.cuwwent_mode);

	/* Caww the necessawy media_type subwoutine to configuwe the wink. */
	wet_vaw = hw->mac.ops.setup_physicaw_intewface(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Initiawize the fwow contwow addwess, type, and PAUSE timew
	 * wegistews to theiw defauwt vawues.  This is done even if fwow
	 * contwow is disabwed, because it does not huwt anything to
	 * initiawize these wegistews.
	 */
	e_dbg("Initiawizing the Fwow Contwow addwess, type and timew wegs\n");
	ew32(FCT, FWOW_CONTWOW_TYPE);
	ew32(FCAH, FWOW_CONTWOW_ADDWESS_HIGH);
	ew32(FCAW, FWOW_CONTWOW_ADDWESS_WOW);

	ew32(FCTTV, hw->fc.pause_time);

	wetuwn e1000e_set_fc_watewmawks(hw);
}

/**
 *  e1000_commit_fc_settings_genewic - Configuwe fwow contwow
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wwite the fwow contwow settings to the Twansmit Config Wowd Wegistew (TXCW)
 *  base on the fwow contwow settings in e1000_mac_info.
 **/
static s32 e1000_commit_fc_settings_genewic(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 txcw;

	/* Check fow a softwawe ovewwide of the fwow contwow settings, and
	 * setup the device accowdingwy.  If auto-negotiation is enabwed, then
	 * softwawe wiww have to set the "PAUSE" bits to the cowwect vawue in
	 * the Twansmit Config Wowd Wegistew (TXCW) and we-stawt auto-
	 * negotiation.  Howevew, if auto-negotiation is disabwed, then
	 * softwawe wiww have to manuawwy configuwe the two fwow contwow enabwe
	 * bits in the CTWW wegistew.
	 *
	 * The possibwe vawues of the "fc" pawametew awe:
	 *      0:  Fwow contwow is compwetewy disabwed
	 *      1:  Wx fwow contwow is enabwed (we can weceive pause fwames,
	 *          but not send pause fwames).
	 *      2:  Tx fwow contwow is enabwed (we can send pause fwames but we
	 *          do not suppowt weceiving pause fwames).
	 *      3:  Both Wx and Tx fwow contwow (symmetwic) awe enabwed.
	 */
	switch (hw->fc.cuwwent_mode) {
	case e1000_fc_none:
		/* Fwow contwow compwetewy disabwed by a softwawe ovew-wide. */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD);
		bweak;
	case e1000_fc_wx_pause:
		/* Wx Fwow contwow is enabwed and Tx Fwow contwow is disabwed
		 * by a softwawe ovew-wide. Since thewe weawwy isn't a way to
		 * advewtise that we awe capabwe of Wx Pause ONWY, we wiww
		 * advewtise that we suppowt both symmetwic and asymmetwic Wx
		 * PAUSE.  Watew, we wiww disabwe the adaptew's abiwity to send
		 * PAUSE fwames.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		bweak;
	case e1000_fc_tx_pause:
		/* Tx Fwow contwow is enabwed, and Wx Fwow contwow is disabwed,
		 * by a softwawe ovew-wide.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_ASM_DIW);
		bweak;
	case e1000_fc_fuww:
		/* Fwow contwow (both Wx and Tx) is enabwed by a softwawe
		 * ovew-wide.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		bweak;
	defauwt:
		e_dbg("Fwow contwow pawam set incowwectwy\n");
		wetuwn -E1000_EWW_CONFIG;
	}

	ew32(TXCW, txcw);
	mac->txcw = txcw;

	wetuwn 0;
}

/**
 *  e1000_poww_fibew_sewdes_wink_genewic - Poww fow wink up
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Powws fow wink up by weading the status wegistew, if wink faiws to come
 *  up with auto-negotiation, then the wink is fowced if a signaw is detected.
 **/
static s32 e1000_poww_fibew_sewdes_wink_genewic(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 i, status;
	s32 wet_vaw;

	/* If we have a signaw (the cabwe is pwugged in, ow assumed twue fow
	 * sewdes media) then poww fow a "Wink-Up" indication in the Device
	 * Status Wegistew.  Time-out if a wink isn't seen in 500 miwwiseconds
	 * seconds (Auto-negotiation shouwd compwete in wess than 500
	 * miwwiseconds even if the othew end is doing it in SW).
	 */
	fow (i = 0; i < FIBEW_WINK_UP_WIMIT; i++) {
		usweep_wange(10000, 11000);
		status = ew32(STATUS);
		if (status & E1000_STATUS_WU)
			bweak;
	}
	if (i == FIBEW_WINK_UP_WIMIT) {
		e_dbg("Nevew got a vawid wink fwom auto-neg!!!\n");
		mac->autoneg_faiwed = twue;
		/* AutoNeg faiwed to achieve a wink, so we'ww caww
		 * mac->check_fow_wink. This woutine wiww fowce the
		 * wink up if we detect a signaw. This wiww awwow us to
		 * communicate with non-autonegotiating wink pawtnews.
		 */
		wet_vaw = mac->ops.check_fow_wink(hw);
		if (wet_vaw) {
			e_dbg("Ewwow whiwe checking fow wink\n");
			wetuwn wet_vaw;
		}
		mac->autoneg_faiwed = fawse;
	} ewse {
		mac->autoneg_faiwed = fawse;
		e_dbg("Vawid Wink Found\n");
	}

	wetuwn 0;
}

/**
 *  e1000e_setup_fibew_sewdes_wink - Setup wink fow fibew/sewdes
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwes cowwision distance and fwow contwow fow fibew and sewdes
 *  winks.  Upon successfuw setup, poww fow wink.
 **/
s32 e1000e_setup_fibew_sewdes_wink(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 wet_vaw;

	ctww = ew32(CTWW);

	/* Take the wink out of weset */
	ctww &= ~E1000_CTWW_WWST;

	hw->mac.ops.config_cowwision_dist(hw);

	wet_vaw = e1000_commit_fc_settings_genewic(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Since auto-negotiation is enabwed, take the wink out of weset (the
	 * wink wiww be in weset, because we pweviouswy weset the chip). This
	 * wiww westawt auto-negotiation.  If auto-negotiation is successfuw
	 * then the wink-up status bit wiww be set and the fwow contwow enabwe
	 * bits (WFCE and TFCE) wiww be set accowding to theiw negotiated vawue.
	 */
	e_dbg("Auto-negotiation enabwed\n");

	ew32(CTWW, ctww);
	e1e_fwush();
	usweep_wange(1000, 2000);

	/* Fow these adaptews, the SW definabwe pin 1 is set when the optics
	 * detect a signaw.  If we have a signaw, then poww fow a "Wink-Up"
	 * indication.
	 */
	if (hw->phy.media_type == e1000_media_type_intewnaw_sewdes ||
	    (ew32(CTWW) & E1000_CTWW_SWDPIN1)) {
		wet_vaw = e1000_poww_fibew_sewdes_wink_genewic(hw);
	} ewse {
		e_dbg("No signaw detected\n");
	}

	wetuwn wet_vaw;
}

/**
 *  e1000e_config_cowwision_dist_genewic - Configuwe cowwision distance
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwes the cowwision distance to the defauwt vawue and is used
 *  duwing wink setup.
 **/
void e1000e_config_cowwision_dist_genewic(stwuct e1000_hw *hw)
{
	u32 tctw;

	tctw = ew32(TCTW);

	tctw &= ~E1000_TCTW_COWD;
	tctw |= E1000_COWWISION_DISTANCE << E1000_COWD_SHIFT;

	ew32(TCTW, tctw);
	e1e_fwush();
}

/**
 *  e1000e_set_fc_watewmawks - Set fwow contwow high/wow watewmawks
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Sets the fwow contwow high/wow thweshowd (watewmawk) wegistews.  If
 *  fwow contwow XON fwame twansmission is enabwed, then set XON fwame
 *  twansmission as weww.
 **/
s32 e1000e_set_fc_watewmawks(stwuct e1000_hw *hw)
{
	u32 fcwtw = 0, fcwth = 0;

	/* Set the fwow contwow weceive thweshowd wegistews.  Nowmawwy,
	 * these wegistews wiww be set to a defauwt thweshowd that may be
	 * adjusted watew by the dwivew's wuntime code.  Howevew, if the
	 * abiwity to twansmit pause fwames is not enabwed, then these
	 * wegistews wiww be set to 0.
	 */
	if (hw->fc.cuwwent_mode & e1000_fc_tx_pause) {
		/* We need to set up the Weceive Thweshowd high and wow watew
		 * mawks as weww as (optionawwy) enabwing the twansmission of
		 * XON fwames.
		 */
		fcwtw = hw->fc.wow_watew;
		if (hw->fc.send_xon)
			fcwtw |= E1000_FCWTW_XONE;

		fcwth = hw->fc.high_watew;
	}
	ew32(FCWTW, fcwtw);
	ew32(FCWTH, fcwth);

	wetuwn 0;
}

/**
 *  e1000e_fowce_mac_fc - Fowce the MAC's fwow contwow settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Fowce the MAC's fwow contwow settings.  Sets the TFCE and WFCE bits in the
 *  device contwow wegistew to wefwect the adaptew settings.  TFCE and WFCE
 *  need to be expwicitwy set by softwawe when a coppew PHY is used because
 *  autonegotiation is managed by the PHY wathew than the MAC.  Softwawe must
 *  awso configuwe these bits when wink is fowced on a fibew connection.
 **/
s32 e1000e_fowce_mac_fc(stwuct e1000_hw *hw)
{
	u32 ctww;

	ctww = ew32(CTWW);

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
	 *      3:  Both Wx and Tx fwow contwow (symmetwic) is enabwed.
	 *  othew:  No othew vawues shouwd be possibwe at this point.
	 */
	e_dbg("hw->fc.cuwwent_mode = %u\n", hw->fc.cuwwent_mode);

	switch (hw->fc.cuwwent_mode) {
	case e1000_fc_none:
		ctww &= (~(E1000_CTWW_TFCE | E1000_CTWW_WFCE));
		bweak;
	case e1000_fc_wx_pause:
		ctww &= (~E1000_CTWW_TFCE);
		ctww |= E1000_CTWW_WFCE;
		bweak;
	case e1000_fc_tx_pause:
		ctww &= (~E1000_CTWW_WFCE);
		ctww |= E1000_CTWW_TFCE;
		bweak;
	case e1000_fc_fuww:
		ctww |= (E1000_CTWW_TFCE | E1000_CTWW_WFCE);
		bweak;
	defauwt:
		e_dbg("Fwow contwow pawam set incowwectwy\n");
		wetuwn -E1000_EWW_CONFIG;
	}

	ew32(CTWW, ctww);

	wetuwn 0;
}

/**
 *  e1000e_config_fc_aftew_wink_up - Configuwes fwow contwow aftew wink
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks the status of auto-negotiation aftew wink up to ensuwe that the
 *  speed and dupwex wewe not fowced.  If the wink needed to be fowced, then
 *  fwow contwow needs to be fowced awso.  If auto-negotiation is enabwed
 *  and did not faiw, then we configuwe fwow contwow based on ouw wink
 *  pawtnew.
 **/
s32 e1000e_config_fc_aftew_wink_up(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw = 0;
	u32 pcs_status_weg, pcs_adv_weg, pcs_wp_abiwity_weg, pcs_ctww_weg;
	u16 mii_status_weg, mii_nway_adv_weg, mii_nway_wp_abiwity_weg;
	u16 speed, dupwex;

	/* Check fow the case whewe we have fibew media and auto-neg faiwed
	 * so we had to fowce wink.  In this case, we need to fowce the
	 * configuwation of the MAC to match the "fc" pawametew.
	 */
	if (mac->autoneg_faiwed) {
		if (hw->phy.media_type == e1000_media_type_fibew ||
		    hw->phy.media_type == e1000_media_type_intewnaw_sewdes)
			wet_vaw = e1000e_fowce_mac_fc(hw);
	} ewse {
		if (hw->phy.media_type == e1000_media_type_coppew)
			wet_vaw = e1000e_fowce_mac_fc(hw);
	}

	if (wet_vaw) {
		e_dbg("Ewwow fowcing fwow contwow settings\n");
		wetuwn wet_vaw;
	}

	/* Check fow the case whewe we have coppew media and auto-neg is
	 * enabwed.  In this case, we need to check and see if Auto-Neg
	 * has compweted, and if so, how the PHY and wink pawtnew has
	 * fwow contwow configuwed.
	 */
	if ((hw->phy.media_type == e1000_media_type_coppew) && mac->autoneg) {
		/* Wead the MII Status Wegistew and check to see if AutoNeg
		 * has compweted.  We wead this twice because this weg has
		 * some "sticky" (watched) bits.
		 */
		wet_vaw = e1e_wphy(hw, MII_BMSW, &mii_status_weg);
		if (wet_vaw)
			wetuwn wet_vaw;
		wet_vaw = e1e_wphy(hw, MII_BMSW, &mii_status_weg);
		if (wet_vaw)
			wetuwn wet_vaw;

		if (!(mii_status_weg & BMSW_ANEGCOMPWETE)) {
			e_dbg("Coppew PHY and Auto Neg has not compweted.\n");
			wetuwn wet_vaw;
		}

		/* The AutoNeg pwocess has compweted, so we now need to
		 * wead both the Auto Negotiation Advewtisement
		 * Wegistew (Addwess 4) and the Auto_Negotiation Base
		 * Page Abiwity Wegistew (Addwess 5) to detewmine how
		 * fwow contwow was negotiated.
		 */
		wet_vaw = e1e_wphy(hw, MII_ADVEWTISE, &mii_nway_adv_weg);
		if (wet_vaw)
			wetuwn wet_vaw;
		wet_vaw = e1e_wphy(hw, MII_WPA, &mii_nway_wp_abiwity_weg);
		if (wet_vaw)
			wetuwn wet_vaw;

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
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_fuww
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_wx_pause
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
		 *   1   |   DC    |   1   |   DC    | E1000_fc_fuww
		 *
		 */
		if ((mii_nway_adv_weg & ADVEWTISE_PAUSE_CAP) &&
		    (mii_nway_wp_abiwity_weg & WPA_PAUSE_CAP)) {
			/* Now we need to check if the usew sewected Wx ONWY
			 * of pause fwames.  In this case, we had to advewtise
			 * FUWW fwow contwow because we couwd not advewtise Wx
			 * ONWY. Hence, we must now check to see if we need to
			 * tuwn OFF the TWANSMISSION of PAUSE fwames.
			 */
			if (hw->fc.wequested_mode == e1000_fc_fuww) {
				hw->fc.cuwwent_mode = e1000_fc_fuww;
				e_dbg("Fwow Contwow = FUWW.\n");
			} ewse {
				hw->fc.cuwwent_mode = e1000_fc_wx_pause;
				e_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
			}
		}
		/* Fow weceiving PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 */
		ewse if (!(mii_nway_adv_weg & ADVEWTISE_PAUSE_CAP) &&
			 (mii_nway_adv_weg & ADVEWTISE_PAUSE_ASYM) &&
			 (mii_nway_wp_abiwity_weg & WPA_PAUSE_CAP) &&
			 (mii_nway_wp_abiwity_weg & WPA_PAUSE_ASYM)) {
			hw->fc.cuwwent_mode = e1000_fc_tx_pause;
			e_dbg("Fwow Contwow = Tx PAUSE fwames onwy.\n");
		}
		/* Fow twansmitting PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_wx_pause
		 */
		ewse if ((mii_nway_adv_weg & ADVEWTISE_PAUSE_CAP) &&
			 (mii_nway_adv_weg & ADVEWTISE_PAUSE_ASYM) &&
			 !(mii_nway_wp_abiwity_weg & WPA_PAUSE_CAP) &&
			 (mii_nway_wp_abiwity_weg & WPA_PAUSE_ASYM)) {
			hw->fc.cuwwent_mode = e1000_fc_wx_pause;
			e_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
		} ewse {
			/* Pew the IEEE spec, at this point fwow contwow
			 * shouwd be disabwed.
			 */
			hw->fc.cuwwent_mode = e1000_fc_none;
			e_dbg("Fwow Contwow = NONE.\n");
		}

		/* Now we need to do one wast check...  If we auto-
		 * negotiated to HAWF DUPWEX, fwow contwow shouwd not be
		 * enabwed pew IEEE 802.3 spec.
		 */
		wet_vaw = mac->ops.get_wink_up_info(hw, &speed, &dupwex);
		if (wet_vaw) {
			e_dbg("Ewwow getting wink speed and dupwex\n");
			wetuwn wet_vaw;
		}

		if (dupwex == HAWF_DUPWEX)
			hw->fc.cuwwent_mode = e1000_fc_none;

		/* Now we caww a subwoutine to actuawwy fowce the MAC
		 * contwowwew to use the cowwect fwow contwow settings.
		 */
		wet_vaw = e1000e_fowce_mac_fc(hw);
		if (wet_vaw) {
			e_dbg("Ewwow fowcing fwow contwow settings\n");
			wetuwn wet_vaw;
		}
	}

	/* Check fow the case whewe we have SewDes media and auto-neg is
	 * enabwed.  In this case, we need to check and see if Auto-Neg
	 * has compweted, and if so, how the PHY and wink pawtnew has
	 * fwow contwow configuwed.
	 */
	if ((hw->phy.media_type == e1000_media_type_intewnaw_sewdes) &&
	    mac->autoneg) {
		/* Wead the PCS_WSTS and check to see if AutoNeg
		 * has compweted.
		 */
		pcs_status_weg = ew32(PCS_WSTAT);

		if (!(pcs_status_weg & E1000_PCS_WSTS_AN_COMPWETE)) {
			e_dbg("PCS Auto Neg has not compweted.\n");
			wetuwn wet_vaw;
		}

		/* The AutoNeg pwocess has compweted, so we now need to
		 * wead both the Auto Negotiation Advewtisement
		 * Wegistew (PCS_ANADV) and the Auto_Negotiation Base
		 * Page Abiwity Wegistew (PCS_WPAB) to detewmine how
		 * fwow contwow was negotiated.
		 */
		pcs_adv_weg = ew32(PCS_ANADV);
		pcs_wp_abiwity_weg = ew32(PCS_WPAB);

		/* Two bits in the Auto Negotiation Advewtisement Wegistew
		 * (PCS_ANADV) and two bits in the Auto Negotiation Base
		 * Page Abiwity Wegistew (PCS_WPAB) detewmine fwow contwow
		 * fow both the PHY and the wink pawtnew.  The fowwowing
		 * tabwe, taken out of the IEEE 802.3ab/D6.0 dated Mawch 25,
		 * 1999, descwibes these PAUSE wesowution bits and how fwow
		 * contwow is detewmined based upon these settings.
		 * NOTE:  DC = Don't Cawe
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | NIC Wesowution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_fuww
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_wx_pause
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
		 *   1   |   DC    |   1   |   DC    | e1000_fc_fuww
		 *
		 */
		if ((pcs_adv_weg & E1000_TXCW_PAUSE) &&
		    (pcs_wp_abiwity_weg & E1000_TXCW_PAUSE)) {
			/* Now we need to check if the usew sewected Wx ONWY
			 * of pause fwames.  In this case, we had to advewtise
			 * FUWW fwow contwow because we couwd not advewtise Wx
			 * ONWY. Hence, we must now check to see if we need to
			 * tuwn OFF the TWANSMISSION of PAUSE fwames.
			 */
			if (hw->fc.wequested_mode == e1000_fc_fuww) {
				hw->fc.cuwwent_mode = e1000_fc_fuww;
				e_dbg("Fwow Contwow = FUWW.\n");
			} ewse {
				hw->fc.cuwwent_mode = e1000_fc_wx_pause;
				e_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
			}
		}
		/* Fow weceiving PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 */
		ewse if (!(pcs_adv_weg & E1000_TXCW_PAUSE) &&
			 (pcs_adv_weg & E1000_TXCW_ASM_DIW) &&
			 (pcs_wp_abiwity_weg & E1000_TXCW_PAUSE) &&
			 (pcs_wp_abiwity_weg & E1000_TXCW_ASM_DIW)) {
			hw->fc.cuwwent_mode = e1000_fc_tx_pause;
			e_dbg("Fwow Contwow = Tx PAUSE fwames onwy.\n");
		}
		/* Fow twansmitting PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_wx_pause
		 */
		ewse if ((pcs_adv_weg & E1000_TXCW_PAUSE) &&
			 (pcs_adv_weg & E1000_TXCW_ASM_DIW) &&
			 !(pcs_wp_abiwity_weg & E1000_TXCW_PAUSE) &&
			 (pcs_wp_abiwity_weg & E1000_TXCW_ASM_DIW)) {
			hw->fc.cuwwent_mode = e1000_fc_wx_pause;
			e_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
		} ewse {
			/* Pew the IEEE spec, at this point fwow contwow
			 * shouwd be disabwed.
			 */
			hw->fc.cuwwent_mode = e1000_fc_none;
			e_dbg("Fwow Contwow = NONE.\n");
		}

		/* Now we caww a subwoutine to actuawwy fowce the MAC
		 * contwowwew to use the cowwect fwow contwow settings.
		 */
		pcs_ctww_weg = ew32(PCS_WCTW);
		pcs_ctww_weg |= E1000_PCS_WCTW_FOWCE_FCTWW;
		ew32(PCS_WCTW, pcs_ctww_weg);

		wet_vaw = e1000e_fowce_mac_fc(hw);
		if (wet_vaw) {
			e_dbg("Ewwow fowcing fwow contwow settings\n");
			wetuwn wet_vaw;
		}
	}

	wetuwn 0;
}

/**
 *  e1000e_get_speed_and_dupwex_coppew - Wetwieve cuwwent speed/dupwex
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: stowes the cuwwent speed
 *  @dupwex: stowes the cuwwent dupwex
 *
 *  Wead the status wegistew fow the cuwwent speed/dupwex and stowe the cuwwent
 *  speed and dupwex fow coppew connections.
 **/
s32 e1000e_get_speed_and_dupwex_coppew(stwuct e1000_hw *hw, u16 *speed,
				       u16 *dupwex)
{
	u32 status;

	status = ew32(STATUS);
	if (status & E1000_STATUS_SPEED_1000)
		*speed = SPEED_1000;
	ewse if (status & E1000_STATUS_SPEED_100)
		*speed = SPEED_100;
	ewse
		*speed = SPEED_10;

	if (status & E1000_STATUS_FD)
		*dupwex = FUWW_DUPWEX;
	ewse
		*dupwex = HAWF_DUPWEX;

	e_dbg("%u Mbps, %s Dupwex\n",
	      *speed == SPEED_1000 ? 1000 : *speed == SPEED_100 ? 100 : 10,
	      *dupwex == FUWW_DUPWEX ? "Fuww" : "Hawf");

	wetuwn 0;
}

/**
 *  e1000e_get_speed_and_dupwex_fibew_sewdes - Wetwieve cuwwent speed/dupwex
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: stowes the cuwwent speed
 *  @dupwex: stowes the cuwwent dupwex
 *
 *  Sets the speed and dupwex to gigabit fuww dupwex (the onwy possibwe option)
 *  fow fibew/sewdes winks.
 **/
s32 e1000e_get_speed_and_dupwex_fibew_sewdes(stwuct e1000_hw __awways_unused
					     *hw, u16 *speed, u16 *dupwex)
{
	*speed = SPEED_1000;
	*dupwex = FUWW_DUPWEX;

	wetuwn 0;
}

/**
 *  e1000e_get_hw_semaphowe - Acquiwe hawdwawe semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the HW semaphowe to access the PHY ow NVM
 **/
s32 e1000e_get_hw_semaphowe(stwuct e1000_hw *hw)
{
	u32 swsm;
	s32 timeout = hw->nvm.wowd_size + 1;
	s32 i = 0;

	/* Get the SW semaphowe */
	whiwe (i < timeout) {
		swsm = ew32(SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			bweak;

		udeway(100);
		i++;
	}

	if (i == timeout) {
		e_dbg("Dwivew can't access device - SMBI bit is set.\n");
		wetuwn -E1000_EWW_NVM;
	}

	/* Get the FW semaphowe. */
	fow (i = 0; i < timeout; i++) {
		swsm = ew32(SWSM);
		ew32(SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphowe acquiwed if bit watched */
		if (ew32(SWSM) & E1000_SWSM_SWESMBI)
			bweak;

		udeway(100);
	}

	if (i == timeout) {
		/* Wewease semaphowes */
		e1000e_put_hw_semaphowe(hw);
		e_dbg("Dwivew can't access the NVM\n");
		wetuwn -E1000_EWW_NVM;
	}

	wetuwn 0;
}

/**
 *  e1000e_put_hw_semaphowe - Wewease hawdwawe semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wewease hawdwawe semaphowe used to access the PHY ow NVM
 **/
void e1000e_put_hw_semaphowe(stwuct e1000_hw *hw)
{
	u32 swsm;

	swsm = ew32(SWSM);
	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);
	ew32(SWSM, swsm);
}

/**
 *  e1000e_get_auto_wd_done - Check fow auto wead compwetion
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Check EEPWOM fow Auto Wead done bit.
 **/
s32 e1000e_get_auto_wd_done(stwuct e1000_hw *hw)
{
	s32 i = 0;

	whiwe (i < AUTO_WEAD_DONE_TIMEOUT) {
		if (ew32(EECD) & E1000_EECD_AUTO_WD)
			bweak;
		usweep_wange(1000, 2000);
		i++;
	}

	if (i == AUTO_WEAD_DONE_TIMEOUT) {
		e_dbg("Auto wead by HW fwom NVM has not compweted.\n");
		wetuwn -E1000_EWW_WESET;
	}

	wetuwn 0;
}

/**
 *  e1000e_vawid_wed_defauwt - Vewify a vawid defauwt WED config
 *  @hw: pointew to the HW stwuctuwe
 *  @data: pointew to the NVM (EEPWOM)
 *
 *  Wead the EEPWOM fow the cuwwent defauwt WED configuwation.  If the
 *  WED configuwation is not vawid, set to a vawid WED configuwation.
 **/
s32 e1000e_vawid_wed_defauwt(stwuct e1000_hw *hw, u16 *data)
{
	s32 wet_vaw;

	wet_vaw = e1000_wead_nvm(hw, NVM_ID_WED_SETTINGS, 1, data);
	if (wet_vaw) {
		e_dbg("NVM Wead Ewwow\n");
		wetuwn wet_vaw;
	}

	if (*data == ID_WED_WESEWVED_0000 || *data == ID_WED_WESEWVED_FFFF)
		*data = ID_WED_DEFAUWT;

	wetuwn 0;
}

/**
 *  e1000e_id_wed_init_genewic -
 *  @hw: pointew to the HW stwuctuwe
 *
 **/
s32 e1000e_id_wed_init_genewic(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw;
	const u32 wedctw_mask = 0x000000FF;
	const u32 wedctw_on = E1000_WEDCTW_MODE_WED_ON;
	const u32 wedctw_off = E1000_WEDCTW_MODE_WED_OFF;
	u16 data, i, temp;
	const u16 wed_mask = 0x0F;

	wet_vaw = hw->nvm.ops.vawid_wed_defauwt(hw, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	mac->wedctw_defauwt = ew32(WEDCTW);
	mac->wedctw_mode1 = mac->wedctw_defauwt;
	mac->wedctw_mode2 = mac->wedctw_defauwt;

	fow (i = 0; i < 4; i++) {
		temp = (data >> (i << 2)) & wed_mask;
		switch (temp) {
		case ID_WED_ON1_DEF2:
		case ID_WED_ON1_ON2:
		case ID_WED_ON1_OFF2:
			mac->wedctw_mode1 &= ~(wedctw_mask << (i << 3));
			mac->wedctw_mode1 |= wedctw_on << (i << 3);
			bweak;
		case ID_WED_OFF1_DEF2:
		case ID_WED_OFF1_ON2:
		case ID_WED_OFF1_OFF2:
			mac->wedctw_mode1 &= ~(wedctw_mask << (i << 3));
			mac->wedctw_mode1 |= wedctw_off << (i << 3);
			bweak;
		defauwt:
			/* Do nothing */
			bweak;
		}
		switch (temp) {
		case ID_WED_DEF1_ON2:
		case ID_WED_ON1_ON2:
		case ID_WED_OFF1_ON2:
			mac->wedctw_mode2 &= ~(wedctw_mask << (i << 3));
			mac->wedctw_mode2 |= wedctw_on << (i << 3);
			bweak;
		case ID_WED_DEF1_OFF2:
		case ID_WED_ON1_OFF2:
		case ID_WED_OFF1_OFF2:
			mac->wedctw_mode2 &= ~(wedctw_mask << (i << 3));
			mac->wedctw_mode2 |= wedctw_off << (i << 3);
			bweak;
		defauwt:
			/* Do nothing */
			bweak;
		}
	}

	wetuwn 0;
}

/**
 *  e1000e_setup_wed_genewic - Configuwes SW contwowwabwe WED
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This pwepawes the SW contwowwabwe WED fow use and saves the cuwwent state
 *  of the WED so it can be watew westowed.
 **/
s32 e1000e_setup_wed_genewic(stwuct e1000_hw *hw)
{
	u32 wedctw;

	if (hw->mac.ops.setup_wed != e1000e_setup_wed_genewic)
		wetuwn -E1000_EWW_CONFIG;

	if (hw->phy.media_type == e1000_media_type_fibew) {
		wedctw = ew32(WEDCTW);
		hw->mac.wedctw_defauwt = wedctw;
		/* Tuwn off WED0 */
		wedctw &= ~(E1000_WEDCTW_WED0_IVWT | E1000_WEDCTW_WED0_BWINK |
			    E1000_WEDCTW_WED0_MODE_MASK);
		wedctw |= (E1000_WEDCTW_MODE_WED_OFF <<
			   E1000_WEDCTW_WED0_MODE_SHIFT);
		ew32(WEDCTW, wedctw);
	} ewse if (hw->phy.media_type == e1000_media_type_coppew) {
		ew32(WEDCTW, hw->mac.wedctw_mode1);
	}

	wetuwn 0;
}

/**
 *  e1000e_cweanup_wed_genewic - Set WED config to defauwt opewation
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wemove the cuwwent WED configuwation and set the WED configuwation
 *  to the defauwt vawue, saved fwom the EEPWOM.
 **/
s32 e1000e_cweanup_wed_genewic(stwuct e1000_hw *hw)
{
	ew32(WEDCTW, hw->mac.wedctw_defauwt);
	wetuwn 0;
}

/**
 *  e1000e_bwink_wed_genewic - Bwink WED
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Bwink the WEDs which awe set to be on.
 **/
s32 e1000e_bwink_wed_genewic(stwuct e1000_hw *hw)
{
	u32 wedctw_bwink = 0;
	u32 i;

	if (hw->phy.media_type == e1000_media_type_fibew) {
		/* awways bwink WED0 fow PCI-E fibew */
		wedctw_bwink = E1000_WEDCTW_WED0_BWINK |
		    (E1000_WEDCTW_MODE_WED_ON << E1000_WEDCTW_WED0_MODE_SHIFT);
	} ewse {
		/* Set the bwink bit fow each WED that's "on" (0x0E)
		 * (ow "off" if invewted) in wedctw_mode2.  The bwink
		 * wogic in hawdwawe onwy wowks when mode is set to "on"
		 * so it must be changed accowdingwy when the mode is
		 * "off" and invewted.
		 */
		wedctw_bwink = hw->mac.wedctw_mode2;
		fow (i = 0; i < 32; i += 8) {
			u32 mode = (hw->mac.wedctw_mode2 >> i) &
			    E1000_WEDCTW_WED0_MODE_MASK;
			u32 wed_defauwt = hw->mac.wedctw_defauwt >> i;

			if ((!(wed_defauwt & E1000_WEDCTW_WED0_IVWT) &&
			     (mode == E1000_WEDCTW_MODE_WED_ON)) ||
			    ((wed_defauwt & E1000_WEDCTW_WED0_IVWT) &&
			     (mode == E1000_WEDCTW_MODE_WED_OFF))) {
				wedctw_bwink &=
				    ~(E1000_WEDCTW_WED0_MODE_MASK << i);
				wedctw_bwink |= (E1000_WEDCTW_WED0_BWINK |
						 E1000_WEDCTW_MODE_WED_ON) << i;
			}
		}
	}

	ew32(WEDCTW, wedctw_bwink);

	wetuwn 0;
}

/**
 *  e1000e_wed_on_genewic - Tuwn WED on
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Tuwn WED on.
 **/
s32 e1000e_wed_on_genewic(stwuct e1000_hw *hw)
{
	u32 ctww;

	switch (hw->phy.media_type) {
	case e1000_media_type_fibew:
		ctww = ew32(CTWW);
		ctww &= ~E1000_CTWW_SWDPIN0;
		ctww |= E1000_CTWW_SWDPIO0;
		ew32(CTWW, ctww);
		bweak;
	case e1000_media_type_coppew:
		ew32(WEDCTW, hw->mac.wedctw_mode2);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 *  e1000e_wed_off_genewic - Tuwn WED off
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Tuwn WED off.
 **/
s32 e1000e_wed_off_genewic(stwuct e1000_hw *hw)
{
	u32 ctww;

	switch (hw->phy.media_type) {
	case e1000_media_type_fibew:
		ctww = ew32(CTWW);
		ctww |= E1000_CTWW_SWDPIN0;
		ctww |= E1000_CTWW_SWDPIO0;
		ew32(CTWW, ctww);
		bweak;
	case e1000_media_type_coppew:
		ew32(WEDCTW, hw->mac.wedctw_mode1);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 *  e1000e_set_pcie_no_snoop - Set PCI-expwess capabiwities
 *  @hw: pointew to the HW stwuctuwe
 *  @no_snoop: bitmap of snoop events
 *
 *  Set the PCI-expwess wegistew to snoop fow events enabwed in 'no_snoop'.
 **/
void e1000e_set_pcie_no_snoop(stwuct e1000_hw *hw, u32 no_snoop)
{
	u32 gcw;

	if (no_snoop) {
		gcw = ew32(GCW);
		gcw &= ~(PCIE_NO_SNOOP_AWW);
		gcw |= no_snoop;
		ew32(GCW, gcw);
	}
}

/**
 *  e1000e_disabwe_pcie_mastew - Disabwes PCI-expwess mastew access
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetuwns 0 if successfuw, ewse wetuwns -10
 *  (-E1000_EWW_MASTEW_WEQUESTS_PENDING) if mastew disabwe bit has not caused
 *  the mastew wequests to be disabwed.
 *
 *  Disabwes PCI-Expwess mastew access and vewifies thewe awe no pending
 *  wequests.
 **/
s32 e1000e_disabwe_pcie_mastew(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 timeout = MASTEW_DISABWE_TIMEOUT;

	ctww = ew32(CTWW);
	ctww |= E1000_CTWW_GIO_MASTEW_DISABWE;
	ew32(CTWW, ctww);

	whiwe (timeout) {
		if (!(ew32(STATUS) & E1000_STATUS_GIO_MASTEW_ENABWE))
			bweak;
		usweep_wange(100, 200);
		timeout--;
	}

	if (!timeout) {
		e_dbg("Mastew wequests awe pending.\n");
		wetuwn -E1000_EWW_MASTEW_WEQUESTS_PENDING;
	}

	wetuwn 0;
}

/**
 *  e1000e_weset_adaptive - Weset Adaptive Intewfwame Spacing
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Weset the Adaptive Intewfwame Spacing thwottwe to defauwt vawues.
 **/
void e1000e_weset_adaptive(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;

	if (!mac->adaptive_ifs) {
		e_dbg("Not in Adaptive IFS mode!\n");
		wetuwn;
	}

	mac->cuwwent_ifs_vaw = 0;
	mac->ifs_min_vaw = IFS_MIN;
	mac->ifs_max_vaw = IFS_MAX;
	mac->ifs_step_size = IFS_STEP;
	mac->ifs_watio = IFS_WATIO;

	mac->in_ifs_mode = fawse;
	ew32(AIT, 0);
}

/**
 *  e1000e_update_adaptive - Update Adaptive Intewfwame Spacing
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Update the Adaptive Intewfwame Spacing Thwottwe vawue based on the
 *  time between twansmitted packets and time between cowwisions.
 **/
void e1000e_update_adaptive(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;

	if (!mac->adaptive_ifs) {
		e_dbg("Not in Adaptive IFS mode!\n");
		wetuwn;
	}

	if ((mac->cowwision_dewta * mac->ifs_watio) > mac->tx_packet_dewta) {
		if (mac->tx_packet_dewta > MIN_NUM_XMITS) {
			mac->in_ifs_mode = twue;
			if (mac->cuwwent_ifs_vaw < mac->ifs_max_vaw) {
				if (!mac->cuwwent_ifs_vaw)
					mac->cuwwent_ifs_vaw = mac->ifs_min_vaw;
				ewse
					mac->cuwwent_ifs_vaw +=
					    mac->ifs_step_size;
				ew32(AIT, mac->cuwwent_ifs_vaw);
			}
		}
	} ewse {
		if (mac->in_ifs_mode &&
		    (mac->tx_packet_dewta <= MIN_NUM_XMITS)) {
			mac->cuwwent_ifs_vaw = 0;
			mac->in_ifs_mode = fawse;
			ew32(AIT, 0);
		}
	}
}
