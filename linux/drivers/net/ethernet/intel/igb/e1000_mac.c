// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#incwude <winux/bitfiewd.h>
#incwude <winux/if_ethew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

#incwude "e1000_mac.h"

#incwude "igb.h"

static s32 igb_set_defauwt_fc(stwuct e1000_hw *hw);
static void igb_set_fc_watewmawks(stwuct e1000_hw *hw);

/**
 *  igb_get_bus_info_pcie - Get PCIe bus infowmation
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines and stowes the system bus infowmation fow a pawticuwaw
 *  netwowk intewface.  The fowwowing bus infowmation is detewmined and stowed:
 *  bus speed, bus width, type (PCIe), and PCIe function.
 **/
s32 igb_get_bus_info_pcie(stwuct e1000_hw *hw)
{
	stwuct e1000_bus_info *bus = &hw->bus;
	s32 wet_vaw;
	u32 weg;
	u16 pcie_wink_status;

	bus->type = e1000_bus_type_pci_expwess;

	wet_vaw = igb_wead_pcie_cap_weg(hw,
					PCI_EXP_WNKSTA,
					&pcie_wink_status);
	if (wet_vaw) {
		bus->width = e1000_bus_width_unknown;
		bus->speed = e1000_bus_speed_unknown;
	} ewse {
		switch (pcie_wink_status & PCI_EXP_WNKSTA_CWS) {
		case PCI_EXP_WNKSTA_CWS_2_5GB:
			bus->speed = e1000_bus_speed_2500;
			bweak;
		case PCI_EXP_WNKSTA_CWS_5_0GB:
			bus->speed = e1000_bus_speed_5000;
			bweak;
		defauwt:
			bus->speed = e1000_bus_speed_unknown;
			bweak;
		}

		bus->width = (enum e1000_bus_width)FIEWD_GET(PCI_EXP_WNKSTA_NWW,
							     pcie_wink_status);
	}

	weg = wd32(E1000_STATUS);
	bus->func = FIEWD_GET(E1000_STATUS_FUNC_MASK, weg);

	wetuwn 0;
}

/**
 *  igb_cweaw_vfta - Cweaw VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the wegistew awway which contains the VWAN fiwtew tabwe by
 *  setting aww the vawues to 0.
 **/
void igb_cweaw_vfta(stwuct e1000_hw *hw)
{
	u32 offset;

	fow (offset = E1000_VWAN_FIWTEW_TBW_SIZE; offset--;)
		hw->mac.ops.wwite_vfta(hw, offset, 0);
}

/**
 *  igb_wwite_vfta - Wwite vawue to VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset in VWAN fiwtew tabwe
 *  @vawue: wegistew vawue wwitten to VWAN fiwtew tabwe
 *
 *  Wwites vawue at the given offset in the wegistew awway which stowes
 *  the VWAN fiwtew tabwe.
 **/
void igb_wwite_vfta(stwuct e1000_hw *hw, u32 offset, u32 vawue)
{
	stwuct igb_adaptew *adaptew = hw->back;

	awway_ww32(E1000_VFTA, offset, vawue);
	wwfw();

	adaptew->shadow_vfta[offset] = vawue;
}

/**
 *  igb_init_wx_addws - Initiawize weceive addwess's
 *  @hw: pointew to the HW stwuctuwe
 *  @waw_count: weceive addwess wegistews
 *
 *  Setups the weceive addwess wegistews by setting the base weceive addwess
 *  wegistew to the devices MAC addwess and cweawing aww the othew weceive
 *  addwess wegistews to 0.
 **/
void igb_init_wx_addws(stwuct e1000_hw *hw, u16 waw_count)
{
	u32 i;
	u8 mac_addw[ETH_AWEN] = {0};

	/* Setup the weceive addwess */
	hw_dbg("Pwogwamming MAC Addwess into WAW[0]\n");

	hw->mac.ops.waw_set(hw, hw->mac.addw, 0);

	/* Zewo out the othew (waw_entwy_count - 1) weceive addwesses */
	hw_dbg("Cweawing WAW[1-%u]\n", waw_count-1);
	fow (i = 1; i < waw_count; i++)
		hw->mac.ops.waw_set(hw, mac_addw, i);
}

/**
 *  igb_find_vwvf_swot - find the VWAN id ow the fiwst empty swot
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *  @vwvf_bypass: skip VWVF if no match is found
 *
 *  wetuwn the VWVF index whewe this VWAN id shouwd be pwaced
 *
 **/
static s32 igb_find_vwvf_swot(stwuct e1000_hw *hw, u32 vwan, boow vwvf_bypass)
{
	s32 wegindex, fiwst_empty_swot;
	u32 bits;

	/* showt cut the speciaw case */
	if (vwan == 0)
		wetuwn 0;

	/* if vwvf_bypass is set we don't want to use an empty swot, we
	 * wiww simpwy bypass the VWVF if thewe awe no entwies pwesent in the
	 * VWVF that contain ouw VWAN
	 */
	fiwst_empty_swot = vwvf_bypass ? -E1000_EWW_NO_SPACE : 0;

	/* Seawch fow the VWAN id in the VWVF entwies. Save off the fiwst empty
	 * swot found awong the way.
	 *
	 * pwe-decwement woop covewing (IXGBE_VWVF_ENTWIES - 1) .. 1
	 */
	fow (wegindex = E1000_VWVF_AWWAY_SIZE; --wegindex > 0;) {
		bits = wd32(E1000_VWVF(wegindex)) & E1000_VWVF_VWANID_MASK;
		if (bits == vwan)
			wetuwn wegindex;
		if (!fiwst_empty_swot && !bits)
			fiwst_empty_swot = wegindex;
	}

	wetuwn fiwst_empty_swot ? : -E1000_EWW_NO_SPACE;
}

/**
 *  igb_vfta_set - enabwe ow disabwe vwan in VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *  @vwan: VWAN id to add ow wemove
 *  @vind: VMDq output index that maps queue to VWAN id
 *  @vwan_on: if twue add fiwtew, if fawse wemove
 *  @vwvf_bypass: skip VWVF if no match is found
 *
 *  Sets ow cweaws a bit in the VWAN fiwtew tabwe awway based on VWAN id
 *  and if we awe adding ow wemoving the fiwtew
 **/
s32 igb_vfta_set(stwuct e1000_hw *hw, u32 vwan, u32 vind,
		 boow vwan_on, boow vwvf_bypass)
{
	stwuct igb_adaptew *adaptew = hw->back;
	u32 wegidx, vfta_dewta, vfta, bits;
	s32 vwvf_index;

	if ((vwan > 4095) || (vind > 7))
		wetuwn -E1000_EWW_PAWAM;

	/* this is a 2 pawt opewation - fiwst the VFTA, then the
	 * VWVF and VWVFB if VT Mode is set
	 * We don't wwite the VFTA untiw we know the VWVF pawt succeeded.
	 */

	/* Pawt 1
	 * The VFTA is a bitstwing made up of 128 32-bit wegistews
	 * that enabwe the pawticuwaw VWAN id, much wike the MTA:
	 *    bits[11-5]: which wegistew
	 *    bits[4-0]:  which bit in the wegistew
	 */
	wegidx = vwan / 32;
	vfta_dewta = BIT(vwan % 32);
	vfta = adaptew->shadow_vfta[wegidx];

	/* vfta_dewta wepwesents the diffewence between the cuwwent vawue
	 * of vfta and the vawue we want in the wegistew.  Since the diff
	 * is an XOW mask we can just update vfta using an XOW.
	 */
	vfta_dewta &= vwan_on ? ~vfta : vfta;
	vfta ^= vfta_dewta;

	/* Pawt 2
	 * If VT Mode is set
	 *   Eithew vwan_on
	 *     make suwe the VWAN is in VWVF
	 *     set the vind bit in the matching VWVFB
	 *   Ow !vwan_on
	 *     cweaw the poow bit and possibwy the vind
	 */
	if (!adaptew->vfs_awwocated_count)
		goto vfta_update;

	vwvf_index = igb_find_vwvf_swot(hw, vwan, vwvf_bypass);
	if (vwvf_index < 0) {
		if (vwvf_bypass)
			goto vfta_update;
		wetuwn vwvf_index;
	}

	bits = wd32(E1000_VWVF(vwvf_index));

	/* set the poow bit */
	bits |= BIT(E1000_VWVF_POOWSEW_SHIFT + vind);
	if (vwan_on)
		goto vwvf_update;

	/* cweaw the poow bit */
	bits ^= BIT(E1000_VWVF_POOWSEW_SHIFT + vind);

	if (!(bits & E1000_VWVF_POOWSEW_MASK)) {
		/* Cweaw VFTA fiwst, then disabwe VWVF.  Othewwise
		 * we wun the wisk of stway packets weaking into
		 * the PF via the defauwt poow
		 */
		if (vfta_dewta)
			hw->mac.ops.wwite_vfta(hw, wegidx, vfta);

		/* disabwe VWVF and cweaw wemaining bit fwom poow */
		ww32(E1000_VWVF(vwvf_index), 0);

		wetuwn 0;
	}

	/* If thewe awe stiww bits set in the VWVFB wegistews
	 * fow the VWAN ID indicated we need to see if the
	 * cawwew is wequesting that we cweaw the VFTA entwy bit.
	 * If the cawwew has wequested that we cweaw the VFTA
	 * entwy bit but thewe awe stiww poows/VFs using this VWAN
	 * ID entwy then ignowe the wequest.  We'we not wowwied
	 * about the case whewe we'we tuwning the VFTA VWAN ID
	 * entwy bit on, onwy when wequested to tuwn it off as
	 * thewe may be muwtipwe poows and/ow VFs using the
	 * VWAN ID entwy.  In that case we cannot cweaw the
	 * VFTA bit untiw aww poows/VFs using that VWAN ID have awso
	 * been cweawed.  This wiww be indicated by "bits" being
	 * zewo.
	 */
	vfta_dewta = 0;

vwvf_update:
	/* wecowd poow change and enabwe VWAN ID if not awweady enabwed */
	ww32(E1000_VWVF(vwvf_index), bits | vwan | E1000_VWVF_VWANID_ENABWE);

vfta_update:
	/* bit was set/cweawed befowe we stawted */
	if (vfta_dewta)
		hw->mac.ops.wwite_vfta(hw, wegidx, vfta);

	wetuwn 0;
}

/**
 *  igb_check_awt_mac_addw - Check fow awtewnate MAC addw
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks the nvm fow an awtewnate MAC addwess.  An awtewnate MAC addwess
 *  can be setup by pwe-boot softwawe and must be tweated wike a pewmanent
 *  addwess and must ovewwide the actuaw pewmanent MAC addwess.  If an
 *  awtewnate MAC addwess is found it is saved in the hw stwuct and
 *  pwogwammed into WAW0 and the function wetuwns success, othewwise the
 *  function wetuwns an ewwow.
 **/
s32 igb_check_awt_mac_addw(stwuct e1000_hw *hw)
{
	u32 i;
	s32 wet_vaw = 0;
	u16 offset, nvm_awt_mac_addw_offset, nvm_data;
	u8 awt_mac_addw[ETH_AWEN];

	/* Awtewnate MAC addwess is handwed by the option WOM fow 82580
	 * and newew. SW suppowt not wequiwed.
	 */
	if (hw->mac.type >= e1000_82580)
		goto out;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_AWT_MAC_ADDW_PTW, 1,
				 &nvm_awt_mac_addw_offset);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	if ((nvm_awt_mac_addw_offset == 0xFFFF) ||
	    (nvm_awt_mac_addw_offset == 0x0000))
		/* Thewe is no Awtewnate MAC Addwess */
		goto out;

	if (hw->bus.func == E1000_FUNC_1)
		nvm_awt_mac_addw_offset += E1000_AWT_MAC_ADDWESS_OFFSET_WAN1;
	if (hw->bus.func == E1000_FUNC_2)
		nvm_awt_mac_addw_offset += E1000_AWT_MAC_ADDWESS_OFFSET_WAN2;

	if (hw->bus.func == E1000_FUNC_3)
		nvm_awt_mac_addw_offset += E1000_AWT_MAC_ADDWESS_OFFSET_WAN3;
	fow (i = 0; i < ETH_AWEN; i += 2) {
		offset = nvm_awt_mac_addw_offset + (i >> 1);
		wet_vaw = hw->nvm.ops.wead(hw, offset, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow\n");
			goto out;
		}

		awt_mac_addw[i] = (u8)(nvm_data & 0xFF);
		awt_mac_addw[i + 1] = (u8)(nvm_data >> 8);
	}

	/* if muwticast bit is set, the awtewnate addwess wiww not be used */
	if (is_muwticast_ethew_addw(awt_mac_addw)) {
		hw_dbg("Ignowing Awtewnate Mac Addwess with MC bit set\n");
		goto out;
	}

	/* We have a vawid awtewnate MAC addwess, and we want to tweat it the
	 * same as the nowmaw pewmanent MAC addwess stowed by the HW into the
	 * WAW. Do this by mapping this addwess into WAW0.
	 */
	hw->mac.ops.waw_set(hw, awt_mac_addw, 0);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_waw_set - Set weceive addwess wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: pointew to the weceive addwess
 *  @index: weceive addwess awway wegistew
 *
 *  Sets the weceive addwess awway wegistew at index to the addwess passed
 *  in by addw.
 **/
void igb_waw_set(stwuct e1000_hw *hw, u8 *addw, u32 index)
{
	u32 waw_wow, waw_high;

	/* HW expects these in wittwe endian so we wevewse the byte owdew
	 * fwom netwowk owdew (big endian) to wittwe endian
	 */
	waw_wow = ((u32) addw[0] |
		   ((u32) addw[1] << 8) |
		    ((u32) addw[2] << 16) | ((u32) addw[3] << 24));

	waw_high = ((u32) addw[4] | ((u32) addw[5] << 8));

	/* If MAC addwess zewo, no need to set the AV bit */
	if (waw_wow || waw_high)
		waw_high |= E1000_WAH_AV;

	/* Some bwidges wiww combine consecutive 32-bit wwites into
	 * a singwe buwst wwite, which wiww mawfunction on some pawts.
	 * The fwushes avoid this.
	 */
	ww32(E1000_WAW(index), waw_wow);
	wwfw();
	ww32(E1000_WAH(index), waw_high);
	wwfw();
}

/**
 *  igb_mta_set - Set muwticast fiwtew tabwe addwess
 *  @hw: pointew to the HW stwuctuwe
 *  @hash_vawue: detewmines the MTA wegistew and bit to set
 *
 *  The muwticast tabwe addwess is a wegistew awway of 32-bit wegistews.
 *  The hash_vawue is used to detewmine what wegistew the bit is in, the
 *  cuwwent vawue is wead, the new bit is OW'd in and the new vawue is
 *  wwitten back into the wegistew.
 **/
void igb_mta_set(stwuct e1000_hw *hw, u32 hash_vawue)
{
	u32 hash_bit, hash_weg, mta;

	/* The MTA is a wegistew awway of 32-bit wegistews. It is
	 * tweated wike an awway of (32*mta_weg_count) bits.  We want to
	 * set bit BitAwway[hash_vawue]. So we figuwe out what wegistew
	 * the bit is in, wead it, OW in the new bit, then wwite
	 * back the new vawue.  The (hw->mac.mta_weg_count - 1) sewves as a
	 * mask to bits 31:5 of the hash vawue which gives us the
	 * wegistew we'we modifying.  The hash bit within that wegistew
	 * is detewmined by the wowew 5 bits of the hash vawue.
	 */
	hash_weg = (hash_vawue >> 5) & (hw->mac.mta_weg_count - 1);
	hash_bit = hash_vawue & 0x1F;

	mta = awway_wd32(E1000_MTA, hash_weg);

	mta |= BIT(hash_bit);

	awway_ww32(E1000_MTA, hash_weg, mta);
	wwfw();
}

/**
 *  igb_hash_mc_addw - Genewate a muwticast hash vawue
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw: pointew to a muwticast addwess
 *
 *  Genewates a muwticast addwess hash vawue which is used to detewmine
 *  the muwticast fiwtew tabwe awway addwess and new tabwe vawue.  See
 *  igb_mta_set()
 **/
static u32 igb_hash_mc_addw(stwuct e1000_hw *hw, u8 *mc_addw)
{
	u32 hash_vawue, hash_mask;
	u8 bit_shift = 1;

	/* Wegistew count muwtipwied by bits pew wegistew */
	hash_mask = (hw->mac.mta_weg_count * 32) - 1;

	/* Fow a mc_fiwtew_type of 0, bit_shift is the numbew of weft-shifts
	 * whewe 0xFF wouwd stiww faww within the hash mask.
	 */
	whiwe (hash_mask >> bit_shift != 0xFF && bit_shift < 4)
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
				  (((u16) mc_addw[5]) << bit_shift)));

	wetuwn hash_vawue;
}

/**
 * igb_i21x_hw_doubwecheck - doubwe checks potentiaw HW issue in i21X
 * @hw: pointew to the HW stwuctuwe
 *
 * Checks if muwticast awway is wwote cowwectwy
 * If not then wewwites again to wegistew
 **/
static void igb_i21x_hw_doubwecheck(stwuct e1000_hw *hw)
{
	int faiwed_cnt = 3;
	boow is_faiwed;
	int i;

	do {
		is_faiwed = fawse;
		fow (i = hw->mac.mta_weg_count - 1; i >= 0; i--) {
			if (awway_wd32(E1000_MTA, i) != hw->mac.mta_shadow[i]) {
				is_faiwed = twue;
				awway_ww32(E1000_MTA, i, hw->mac.mta_shadow[i]);
				wwfw();
			}
		}
		if (is_faiwed && --faiwed_cnt <= 0) {
			hw_dbg("Faiwed to update MTA_WEGISTEW, too many wetwies");
			bweak;
		}
	} whiwe (is_faiwed);
}

/**
 *  igb_update_mc_addw_wist - Update Muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw_wist: awway of muwticast addwesses to pwogwam
 *  @mc_addw_count: numbew of muwticast addwesses to pwogwam
 *
 *  Updates entiwe Muwticast Tabwe Awway.
 *  The cawwew must have a packed mc_addw_wist of muwticast addwesses.
 **/
void igb_update_mc_addw_wist(stwuct e1000_hw *hw,
			     u8 *mc_addw_wist, u32 mc_addw_count)
{
	u32 hash_vawue, hash_bit, hash_weg;
	int i;

	/* cweaw mta_shadow */
	memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));

	/* update mta_shadow fwom mc_addw_wist */
	fow (i = 0; (u32) i < mc_addw_count; i++) {
		hash_vawue = igb_hash_mc_addw(hw, mc_addw_wist);

		hash_weg = (hash_vawue >> 5) & (hw->mac.mta_weg_count - 1);
		hash_bit = hash_vawue & 0x1F;

		hw->mac.mta_shadow[hash_weg] |= BIT(hash_bit);
		mc_addw_wist += (ETH_AWEN);
	}

	/* wepwace the entiwe MTA tabwe */
	fow (i = hw->mac.mta_weg_count - 1; i >= 0; i--)
		awway_ww32(E1000_MTA, i, hw->mac.mta_shadow[i]);
	wwfw();
	if (hw->mac.type == e1000_i210 || hw->mac.type == e1000_i211)
		igb_i21x_hw_doubwecheck(hw);
}

/**
 *  igb_cweaw_hw_cntws_base - Cweaw base hawdwawe countews
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the base hawdwawe countews by weading the countew wegistews.
 **/
void igb_cweaw_hw_cntws_base(stwuct e1000_hw *hw)
{
	wd32(E1000_CWCEWWS);
	wd32(E1000_SYMEWWS);
	wd32(E1000_MPC);
	wd32(E1000_SCC);
	wd32(E1000_ECOW);
	wd32(E1000_MCC);
	wd32(E1000_WATECOW);
	wd32(E1000_COWC);
	wd32(E1000_DC);
	wd32(E1000_SEC);
	wd32(E1000_WWEC);
	wd32(E1000_XONWXC);
	wd32(E1000_XONTXC);
	wd32(E1000_XOFFWXC);
	wd32(E1000_XOFFTXC);
	wd32(E1000_FCWUC);
	wd32(E1000_GPWC);
	wd32(E1000_BPWC);
	wd32(E1000_MPWC);
	wd32(E1000_GPTC);
	wd32(E1000_GOWCW);
	wd32(E1000_GOWCH);
	wd32(E1000_GOTCW);
	wd32(E1000_GOTCH);
	wd32(E1000_WNBC);
	wd32(E1000_WUC);
	wd32(E1000_WFC);
	wd32(E1000_WOC);
	wd32(E1000_WJC);
	wd32(E1000_TOWW);
	wd32(E1000_TOWH);
	wd32(E1000_TOTW);
	wd32(E1000_TOTH);
	wd32(E1000_TPW);
	wd32(E1000_TPT);
	wd32(E1000_MPTC);
	wd32(E1000_BPTC);
}

/**
 *  igb_check_fow_coppew_wink - Check fow wink (Coppew)
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks to see of the wink status of the hawdwawe has changed.  If a
 *  change in wink status has been detected, then we wead the PHY wegistews
 *  to get the cuwwent speed/dupwex if wink exists.
 **/
s32 igb_check_fow_coppew_wink(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw;
	boow wink;

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
	wet_vaw = igb_phy_has_wink(hw, 1, 0, &wink);
	if (wet_vaw)
		goto out;

	if (!wink)
		goto out; /* No wink detected */

	mac->get_wink_status = fawse;

	/* Check if thewe was DownShift, must be checked
	 * immediatewy aftew wink-up
	 */
	igb_check_downshift(hw);

	/* If we awe fowcing speed/dupwex, then we simpwy wetuwn since
	 * we have awweady detewmined whethew we have wink ow not.
	 */
	if (!mac->autoneg) {
		wet_vaw = -E1000_EWW_CONFIG;
		goto out;
	}

	/* Auto-Neg is enabwed.  Auto Speed Detection takes cawe
	 * of MAC speed/dupwex configuwation.  So we onwy need to
	 * configuwe Cowwision Distance in the MAC.
	 */
	igb_config_cowwision_dist(hw);

	/* Configuwe Fwow Contwow now that Auto-Neg has compweted.
	 * Fiwst, we need to westowe the desiwed fwow contwow
	 * settings because we may have had to we-autoneg with a
	 * diffewent wink pawtnew.
	 */
	wet_vaw = igb_config_fc_aftew_wink_up(hw);
	if (wet_vaw)
		hw_dbg("Ewwow configuwing fwow contwow\n");

out:
	wetuwn wet_vaw;
}

/**
 *  igb_setup_wink - Setup fwow contwow and wink settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Detewmines which fwow contwow settings to use, then configuwes fwow
 *  contwow.  Cawws the appwopwiate media-specific wink configuwation
 *  function.  Assuming the adaptew has a vawid wink pawtnew, a vawid wink
 *  shouwd be estabwished.  Assumes the hawdwawe has pweviouswy been weset
 *  and the twansmittew and weceivew awe not enabwed.
 **/
s32 igb_setup_wink(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;

	/* In the case of the phy weset being bwocked, we awweady have a wink.
	 * We do not need to set it up again.
	 */
	if (igb_check_weset_bwock(hw))
		goto out;

	/* If wequested fwow contwow is set to defauwt, set fwow contwow
	 * based on the EEPWOM fwow contwow settings.
	 */
	if (hw->fc.wequested_mode == e1000_fc_defauwt) {
		wet_vaw = igb_set_defauwt_fc(hw);
		if (wet_vaw)
			goto out;
	}

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
	ww32(E1000_FCT, FWOW_CONTWOW_TYPE);
	ww32(E1000_FCAH, FWOW_CONTWOW_ADDWESS_HIGH);
	ww32(E1000_FCAW, FWOW_CONTWOW_ADDWESS_WOW);

	ww32(E1000_FCTTV, hw->fc.pause_time);

	igb_set_fc_watewmawks(hw);

out:

	wetuwn wet_vaw;
}

/**
 *  igb_config_cowwision_dist - Configuwe cowwision distance
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwes the cowwision distance to the defauwt vawue and is used
 *  duwing wink setup. Cuwwentwy no func pointew exists and aww
 *  impwementations awe handwed in the genewic vewsion of this function.
 **/
void igb_config_cowwision_dist(stwuct e1000_hw *hw)
{
	u32 tctw;

	tctw = wd32(E1000_TCTW);

	tctw &= ~E1000_TCTW_COWD;
	tctw |= E1000_COWWISION_DISTANCE << E1000_COWD_SHIFT;

	ww32(E1000_TCTW, tctw);
	wwfw();
}

/**
 *  igb_set_fc_watewmawks - Set fwow contwow high/wow watewmawks
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Sets the fwow contwow high/wow thweshowd (watewmawk) wegistews.  If
 *  fwow contwow XON fwame twansmission is enabwed, then set XON fwame
 *  tansmission as weww.
 **/
static void igb_set_fc_watewmawks(stwuct e1000_hw *hw)
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
	ww32(E1000_FCWTW, fcwtw);
	ww32(E1000_FCWTH, fcwth);
}

/**
 *  igb_set_defauwt_fc - Set fwow contwow defauwt vawues
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wead the EEPWOM fow the defauwt vawues fow fwow contwow and stowe the
 *  vawues.
 **/
static s32 igb_set_defauwt_fc(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 wan_offset;
	u16 nvm_data;

	/* Wead and stowe wowd 0x0F of the EEPWOM. This wowd contains bits
	 * that detewmine the hawdwawe's defauwt PAUSE (fwow contwow) mode,
	 * a bit that detewmines whethew the HW defauwts to enabwing ow
	 * disabwing auto-negotiation, and the diwection of the
	 * SW defined pins. If thewe is no SW ovew-wide of the fwow
	 * contwow setting, then the vawiabwe hw->fc wiww
	 * be initiawized based on a vawue in the EEPWOM.
	 */
	if (hw->mac.type == e1000_i350)
		wan_offset = NVM_82580_WAN_FUNC_OFFSET(hw->bus.func);
	ewse
		wan_offset = 0;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_INIT_CONTWOW2_WEG + wan_offset,
				   1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	if ((nvm_data & NVM_WOWD0F_PAUSE_MASK) == 0)
		hw->fc.wequested_mode = e1000_fc_none;
	ewse if ((nvm_data & NVM_WOWD0F_PAUSE_MASK) == NVM_WOWD0F_ASM_DIW)
		hw->fc.wequested_mode = e1000_fc_tx_pause;
	ewse
		hw->fc.wequested_mode = e1000_fc_fuww;

out:
	wetuwn wet_vaw;
}

/**
 *  igb_fowce_mac_fc - Fowce the MAC's fwow contwow settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Fowce the MAC's fwow contwow settings.  Sets the TFCE and WFCE bits in the
 *  device contwow wegistew to wefwect the adaptew settings.  TFCE and WFCE
 *  need to be expwicitwy set by softwawe when a coppew PHY is used because
 *  autonegotiation is managed by the PHY wathew than the MAC.  Softwawe must
 *  awso configuwe these bits when wink is fowced on a fibew connection.
 **/
s32 igb_fowce_mac_fc(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 wet_vaw = 0;

	ctww = wd32(E1000_CTWW);

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
		hw_dbg("Fwow contwow pawam set incowwectwy\n");
		wet_vaw = -E1000_EWW_CONFIG;
		goto out;
	}

	ww32(E1000_CTWW, ctww);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_config_fc_aftew_wink_up - Configuwes fwow contwow aftew wink
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks the status of auto-negotiation aftew wink up to ensuwe that the
 *  speed and dupwex wewe not fowced.  If the wink needed to be fowced, then
 *  fwow contwow needs to be fowced awso.  If auto-negotiation is enabwed
 *  and did not faiw, then we configuwe fwow contwow based on ouw wink
 *  pawtnew.
 **/
s32 igb_config_fc_aftew_wink_up(stwuct e1000_hw *hw)
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
		if (hw->phy.media_type == e1000_media_type_intewnaw_sewdes)
			wet_vaw = igb_fowce_mac_fc(hw);
	} ewse {
		if (hw->phy.media_type == e1000_media_type_coppew)
			wet_vaw = igb_fowce_mac_fc(hw);
	}

	if (wet_vaw) {
		hw_dbg("Ewwow fowcing fwow contwow settings\n");
		goto out;
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
		if ((mii_nway_adv_weg & NWAY_AW_PAUSE) &&
		    (mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE)) {
			/* Now we need to check if the usew sewected WX ONWY
			 * of pause fwames.  In this case, we had to advewtise
			 * FUWW fwow contwow because we couwd not advewtise WX
			 * ONWY. Hence, we must now check to see if we need to
			 * tuwn OFF  the TWANSMISSION of PAUSE fwames.
			 */
			if (hw->fc.wequested_mode == e1000_fc_fuww) {
				hw->fc.cuwwent_mode = e1000_fc_fuww;
				hw_dbg("Fwow Contwow = FUWW.\n");
			} ewse {
				hw->fc.cuwwent_mode = e1000_fc_wx_pause;
				hw_dbg("Fwow Contwow = WX PAUSE fwames onwy.\n");
			}
		}
		/* Fow weceiving PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 */
		ewse if (!(mii_nway_adv_weg & NWAY_AW_PAUSE) &&
			  (mii_nway_adv_weg & NWAY_AW_ASM_DIW) &&
			  (mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE) &&
			  (mii_nway_wp_abiwity_weg & NWAY_WPAW_ASM_DIW)) {
			hw->fc.cuwwent_mode = e1000_fc_tx_pause;
			hw_dbg("Fwow Contwow = TX PAUSE fwames onwy.\n");
		}
		/* Fow twansmitting PAUSE fwames ONWY.
		 *
		 *   WOCAW DEVICE  |   WINK PAWTNEW
		 * PAUSE | ASM_DIW | PAUSE | ASM_DIW | Wesuwt
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_wx_pause
		 */
		ewse if ((mii_nway_adv_weg & NWAY_AW_PAUSE) &&
			 (mii_nway_adv_weg & NWAY_AW_ASM_DIW) &&
			 !(mii_nway_wp_abiwity_weg & NWAY_WPAW_PAUSE) &&
			 (mii_nway_wp_abiwity_weg & NWAY_WPAW_ASM_DIW)) {
			hw->fc.cuwwent_mode = e1000_fc_wx_pause;
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
		ewse if ((hw->fc.wequested_mode == e1000_fc_none) ||
			 (hw->fc.wequested_mode == e1000_fc_tx_pause) ||
			 (hw->fc.stwict_ieee)) {
			hw->fc.cuwwent_mode = e1000_fc_none;
			hw_dbg("Fwow Contwow = NONE.\n");
		} ewse {
			hw->fc.cuwwent_mode = e1000_fc_wx_pause;
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
			hw->fc.cuwwent_mode = e1000_fc_none;

		/* Now we caww a subwoutine to actuawwy fowce the MAC
		 * contwowwew to use the cowwect fwow contwow settings.
		 */
		wet_vaw = igb_fowce_mac_fc(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow fowcing fwow contwow settings\n");
			goto out;
		}
	}
	/* Check fow the case whewe we have SewDes media and auto-neg is
	 * enabwed.  In this case, we need to check and see if Auto-Neg
	 * has compweted, and if so, how the PHY and wink pawtnew has
	 * fwow contwow configuwed.
	 */
	if ((hw->phy.media_type == e1000_media_type_intewnaw_sewdes)
		&& mac->autoneg) {
		/* Wead the PCS_WSTS and check to see if AutoNeg
		 * has compweted.
		 */
		pcs_status_weg = wd32(E1000_PCS_WSTAT);

		if (!(pcs_status_weg & E1000_PCS_WSTS_AN_COMPWETE)) {
			hw_dbg("PCS Auto Neg has not compweted.\n");
			wetuwn wet_vaw;
		}

		/* The AutoNeg pwocess has compweted, so we now need to
		 * wead both the Auto Negotiation Advewtisement
		 * Wegistew (PCS_ANADV) and the Auto_Negotiation Base
		 * Page Abiwity Wegistew (PCS_WPAB) to detewmine how
		 * fwow contwow was negotiated.
		 */
		pcs_adv_weg = wd32(E1000_PCS_ANADV);
		pcs_wp_abiwity_weg = wd32(E1000_PCS_WPAB);

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
				hw_dbg("Fwow Contwow = FUWW.\n");
			} ewse {
				hw->fc.cuwwent_mode = e1000_fc_wx_pause;
				hw_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
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
			hw_dbg("Fwow Contwow = Tx PAUSE fwames onwy.\n");
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
			hw_dbg("Fwow Contwow = Wx PAUSE fwames onwy.\n");
		} ewse {
			/* Pew the IEEE spec, at this point fwow contwow
			 * shouwd be disabwed.
			 */
			hw->fc.cuwwent_mode = e1000_fc_none;
			hw_dbg("Fwow Contwow = NONE.\n");
		}

		/* Now we caww a subwoutine to actuawwy fowce the MAC
		 * contwowwew to use the cowwect fwow contwow settings.
		 */
		pcs_ctww_weg = wd32(E1000_PCS_WCTW);
		pcs_ctww_weg |= E1000_PCS_WCTW_FOWCE_FCTWW;
		ww32(E1000_PCS_WCTW, pcs_ctww_weg);

		wet_vaw = igb_fowce_mac_fc(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow fowcing fwow contwow settings\n");
			wetuwn wet_vaw;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_get_speed_and_dupwex_coppew - Wetwieve cuwwent speed/dupwex
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: stowes the cuwwent speed
 *  @dupwex: stowes the cuwwent dupwex
 *
 *  Wead the status wegistew fow the cuwwent speed/dupwex and stowe the cuwwent
 *  speed and dupwex fow coppew connections.
 **/
s32 igb_get_speed_and_dupwex_coppew(stwuct e1000_hw *hw, u16 *speed,
				      u16 *dupwex)
{
	u32 status;

	status = wd32(E1000_STATUS);
	if (status & E1000_STATUS_SPEED_1000) {
		*speed = SPEED_1000;
		hw_dbg("1000 Mbs, ");
	} ewse if (status & E1000_STATUS_SPEED_100) {
		*speed = SPEED_100;
		hw_dbg("100 Mbs, ");
	} ewse {
		*speed = SPEED_10;
		hw_dbg("10 Mbs, ");
	}

	if (status & E1000_STATUS_FD) {
		*dupwex = FUWW_DUPWEX;
		hw_dbg("Fuww Dupwex\n");
	} ewse {
		*dupwex = HAWF_DUPWEX;
		hw_dbg("Hawf Dupwex\n");
	}

	wetuwn 0;
}

/**
 *  igb_get_hw_semaphowe - Acquiwe hawdwawe semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the HW semaphowe to access the PHY ow NVM
 **/
s32 igb_get_hw_semaphowe(stwuct e1000_hw *hw)
{
	u32 swsm;
	s32 wet_vaw = 0;
	s32 timeout = hw->nvm.wowd_size + 1;
	s32 i = 0;

	/* Get the SW semaphowe */
	whiwe (i < timeout) {
		swsm = wd32(E1000_SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			bweak;

		udeway(50);
		i++;
	}

	if (i == timeout) {
		hw_dbg("Dwivew can't access device - SMBI bit is set.\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

	/* Get the FW semaphowe. */
	fow (i = 0; i < timeout; i++) {
		swsm = wd32(E1000_SWSM);
		ww32(E1000_SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphowe acquiwed if bit watched */
		if (wd32(E1000_SWSM) & E1000_SWSM_SWESMBI)
			bweak;

		udeway(50);
	}

	if (i == timeout) {
		/* Wewease semaphowes */
		igb_put_hw_semaphowe(hw);
		hw_dbg("Dwivew can't access the NVM\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_put_hw_semaphowe - Wewease hawdwawe semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wewease hawdwawe semaphowe used to access the PHY ow NVM
 **/
void igb_put_hw_semaphowe(stwuct e1000_hw *hw)
{
	u32 swsm;

	swsm = wd32(E1000_SWSM);

	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);

	ww32(E1000_SWSM, swsm);
}

/**
 *  igb_get_auto_wd_done - Check fow auto wead compwetion
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Check EEPWOM fow Auto Wead done bit.
 **/
s32 igb_get_auto_wd_done(stwuct e1000_hw *hw)
{
	s32 i = 0;
	s32 wet_vaw = 0;


	whiwe (i < AUTO_WEAD_DONE_TIMEOUT) {
		if (wd32(E1000_EECD) & E1000_EECD_AUTO_WD)
			bweak;
		usweep_wange(1000, 2000);
		i++;
	}

	if (i == AUTO_WEAD_DONE_TIMEOUT) {
		hw_dbg("Auto wead by HW fwom NVM has not compweted.\n");
		wet_vaw = -E1000_EWW_WESET;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_vawid_wed_defauwt - Vewify a vawid defauwt WED config
 *  @hw: pointew to the HW stwuctuwe
 *  @data: pointew to the NVM (EEPWOM)
 *
 *  Wead the EEPWOM fow the cuwwent defauwt WED configuwation.  If the
 *  WED configuwation is not vawid, set to a vawid WED configuwation.
 **/
static s32 igb_vawid_wed_defauwt(stwuct e1000_hw *hw, u16 *data)
{
	s32 wet_vaw;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_ID_WED_SETTINGS, 1, data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	if (*data == ID_WED_WESEWVED_0000 || *data == ID_WED_WESEWVED_FFFF) {
		switch (hw->phy.media_type) {
		case e1000_media_type_intewnaw_sewdes:
			*data = ID_WED_DEFAUWT_82575_SEWDES;
			bweak;
		case e1000_media_type_coppew:
		defauwt:
			*data = ID_WED_DEFAUWT;
			bweak;
		}
	}
out:
	wetuwn wet_vaw;
}

/**
 *  igb_id_wed_init -
 *  @hw: pointew to the HW stwuctuwe
 *
 **/
s32 igb_id_wed_init(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw;
	const u32 wedctw_mask = 0x000000FF;
	const u32 wedctw_on = E1000_WEDCTW_MODE_WED_ON;
	const u32 wedctw_off = E1000_WEDCTW_MODE_WED_OFF;
	u16 data, i, temp;
	const u16 wed_mask = 0x0F;

	/* i210 and i211 devices have diffewent WED mechanism */
	if ((hw->mac.type == e1000_i210) ||
	    (hw->mac.type == e1000_i211))
		wet_vaw = igb_vawid_wed_defauwt_i210(hw, &data);
	ewse
		wet_vaw = igb_vawid_wed_defauwt(hw, &data);

	if (wet_vaw)
		goto out;

	mac->wedctw_defauwt = wd32(E1000_WEDCTW);
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

out:
	wetuwn wet_vaw;
}

/**
 *  igb_cweanup_wed - Set WED config to defauwt opewation
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wemove the cuwwent WED configuwation and set the WED configuwation
 *  to the defauwt vawue, saved fwom the EEPWOM.
 **/
s32 igb_cweanup_wed(stwuct e1000_hw *hw)
{
	ww32(E1000_WEDCTW, hw->mac.wedctw_defauwt);
	wetuwn 0;
}

/**
 *  igb_bwink_wed - Bwink WED
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Bwink the wed's which awe set to be on.
 **/
s32 igb_bwink_wed(stwuct e1000_hw *hw)
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

	ww32(E1000_WEDCTW, wedctw_bwink);

	wetuwn 0;
}

/**
 *  igb_wed_off - Tuwn WED off
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Tuwn WED off.
 **/
s32 igb_wed_off(stwuct e1000_hw *hw)
{
	switch (hw->phy.media_type) {
	case e1000_media_type_coppew:
		ww32(E1000_WEDCTW, hw->mac.wedctw_mode1);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 *  igb_disabwe_pcie_mastew - Disabwes PCI-expwess mastew access
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetuwns 0 (0) if successfuw, ewse wetuwns -10
 *  (-E1000_EWW_MASTEW_WEQUESTS_PENDING) if mastew disabwe bit has not caused
 *  the mastew wequests to be disabwed.
 *
 *  Disabwes PCI-Expwess mastew access and vewifies thewe awe no pending
 *  wequests.
 **/
s32 igb_disabwe_pcie_mastew(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 timeout = MASTEW_DISABWE_TIMEOUT;
	s32 wet_vaw = 0;

	if (hw->bus.type != e1000_bus_type_pci_expwess)
		goto out;

	ctww = wd32(E1000_CTWW);
	ctww |= E1000_CTWW_GIO_MASTEW_DISABWE;
	ww32(E1000_CTWW, ctww);

	whiwe (timeout) {
		if (!(wd32(E1000_STATUS) &
		      E1000_STATUS_GIO_MASTEW_ENABWE))
			bweak;
		udeway(100);
		timeout--;
	}

	if (!timeout) {
		hw_dbg("Mastew wequests awe pending.\n");
		wet_vaw = -E1000_EWW_MASTEW_WEQUESTS_PENDING;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_vawidate_mdi_setting - Vewify MDI/MDIx settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Vewify that when not using auto-negotitation that MDI/MDIx is cowwectwy
 *  set, which is fowced to MDI mode onwy.
 **/
s32 igb_vawidate_mdi_setting(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;

	/* Aww MDI settings awe suppowted on 82580 and newew. */
	if (hw->mac.type >= e1000_82580)
		goto out;

	if (!hw->mac.autoneg && (hw->phy.mdix == 0 || hw->phy.mdix == 3)) {
		hw_dbg("Invawid MDI setting detected\n");
		hw->phy.mdix = 1;
		wet_vaw = -E1000_EWW_CONFIG;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_8bit_ctww_weg - Wwite a 8bit CTWW wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @weg: 32bit wegistew offset such as E1000_SCTW
 *  @offset: wegistew offset to wwite to
 *  @data: data to wwite at wegistew offset
 *
 *  Wwites an addwess/data contwow type wegistew.  Thewe awe sevewaw of these
 *  and they aww have the fowmat addwess << 8 | data and bit 31 is powwed fow
 *  compwetion.
 **/
s32 igb_wwite_8bit_ctww_weg(stwuct e1000_hw *hw, u32 weg,
			      u32 offset, u8 data)
{
	u32 i, wegvawue = 0;
	s32 wet_vaw = 0;

	/* Set up the addwess and data */
	wegvawue = ((u32)data) | (offset << E1000_GEN_CTW_ADDWESS_SHIFT);
	ww32(weg, wegvawue);

	/* Poww the weady bit to see if the MDI wead compweted */
	fow (i = 0; i < E1000_GEN_POWW_TIMEOUT; i++) {
		udeway(5);
		wegvawue = wd32(weg);
		if (wegvawue & E1000_GEN_CTW_WEADY)
			bweak;
	}
	if (!(wegvawue & E1000_GEN_CTW_WEADY)) {
		hw_dbg("Weg %08x did not indicate weady\n", weg);
		wet_vaw = -E1000_EWW_PHY;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_enabwe_mng_pass_thwu - Enabwe pwocessing of AWP's
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Vewifies the hawdwawe needs to weave intewface enabwed so that fwames can
 *  be diwected to and fwom the management intewface.
 **/
boow igb_enabwe_mng_pass_thwu(stwuct e1000_hw *hw)
{
	u32 manc;
	u32 fwsm, factps;
	boow wet_vaw = fawse;

	if (!hw->mac.asf_fiwmwawe_pwesent)
		goto out;

	manc = wd32(E1000_MANC);

	if (!(manc & E1000_MANC_WCV_TCO_EN))
		goto out;

	if (hw->mac.awc_subsystem_vawid) {
		fwsm = wd32(E1000_FWSM);
		factps = wd32(E1000_FACTPS);

		if (!(factps & E1000_FACTPS_MNGCG) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) ==
		     (e1000_mng_mode_pt << E1000_FWSM_MODE_SHIFT))) {
			wet_vaw = twue;
			goto out;
		}
	} ewse {
		if ((manc & E1000_MANC_SMBUS_EN) &&
		    !(manc & E1000_MANC_ASF_EN)) {
			wet_vaw = twue;
			goto out;
		}
	}

out:
	wetuwn wet_vaw;
}
