// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "e1000.h"

/**
 *  e1000_cawcuwate_checksum - Cawcuwate checksum fow buffew
 *  @buffew: pointew to EEPWOM
 *  @wength: size of EEPWOM to cawcuwate a checksum fow
 *
 *  Cawcuwates the checksum fow some buffew on a specified wength.  The
 *  checksum cawcuwated is wetuwned.
 **/
static u8 e1000_cawcuwate_checksum(u8 *buffew, u32 wength)
{
	u32 i;
	u8 sum = 0;

	if (!buffew)
		wetuwn 0;

	fow (i = 0; i < wength; i++)
		sum += buffew[i];

	wetuwn (u8)(0 - sum);
}

/**
 *  e1000_mng_enabwe_host_if - Checks host intewface is enabwed
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetuwns 0 upon success, ewse -E1000_EWW_HOST_INTEWFACE_COMMAND
 *
 *  This function checks whethew the HOST IF is enabwed fow command opewation
 *  and awso checks whethew the pwevious command is compweted.  It busy waits
 *  in case of pwevious command is not compweted.
 **/
static s32 e1000_mng_enabwe_host_if(stwuct e1000_hw *hw)
{
	u32 hicw;
	u8 i;

	if (!hw->mac.awc_subsystem_vawid) {
		e_dbg("AWC subsystem not vawid.\n");
		wetuwn -E1000_EWW_HOST_INTEWFACE_COMMAND;
	}

	/* Check that the host intewface is enabwed. */
	hicw = ew32(HICW);
	if (!(hicw & E1000_HICW_EN)) {
		e_dbg("E1000_HOST_EN bit disabwed.\n");
		wetuwn -E1000_EWW_HOST_INTEWFACE_COMMAND;
	}
	/* check the pwevious command is compweted */
	fow (i = 0; i < E1000_MNG_DHCP_COMMAND_TIMEOUT; i++) {
		hicw = ew32(HICW);
		if (!(hicw & E1000_HICW_C))
			bweak;
		mdeway(1);
	}

	if (i == E1000_MNG_DHCP_COMMAND_TIMEOUT) {
		e_dbg("Pwevious command timeout faiwed.\n");
		wetuwn -E1000_EWW_HOST_INTEWFACE_COMMAND;
	}

	wetuwn 0;
}

/**
 *  e1000e_check_mng_mode_genewic - Genewic check management mode
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Weads the fiwmwawe semaphowe wegistew and wetuwns twue (>0) if
 *  manageabiwity is enabwed, ewse fawse (0).
 **/
boow e1000e_check_mng_mode_genewic(stwuct e1000_hw *hw)
{
	u32 fwsm = ew32(FWSM);

	wetuwn (fwsm & E1000_FWSM_MODE_MASK) ==
	    (E1000_MNG_IAMT_MODE << E1000_FWSM_MODE_SHIFT);
}

/**
 *  e1000e_enabwe_tx_pkt_fiwtewing - Enabwe packet fiwtewing on Tx
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Enabwes packet fiwtewing on twansmit packets if manageabiwity is enabwed
 *  and host intewface is enabwed.
 **/
boow e1000e_enabwe_tx_pkt_fiwtewing(stwuct e1000_hw *hw)
{
	stwuct e1000_host_mng_dhcp_cookie *hdw = &hw->mng_cookie;
	u32 *buffew = (u32 *)&hw->mng_cookie;
	u32 offset;
	s32 wet_vaw, hdw_csum, csum;
	u8 i, wen;

	hw->mac.tx_pkt_fiwtewing = twue;

	/* No manageabiwity, no fiwtewing */
	if (!hw->mac.ops.check_mng_mode(hw)) {
		hw->mac.tx_pkt_fiwtewing = fawse;
		wetuwn hw->mac.tx_pkt_fiwtewing;
	}

	/* If we can't wead fwom the host intewface fow whatevew
	 * weason, disabwe fiwtewing.
	 */
	wet_vaw = e1000_mng_enabwe_host_if(hw);
	if (wet_vaw) {
		hw->mac.tx_pkt_fiwtewing = fawse;
		wetuwn hw->mac.tx_pkt_fiwtewing;
	}

	/* Wead in the headew.  Wength and offset awe in dwowds. */
	wen = E1000_MNG_DHCP_COOKIE_WENGTH >> 2;
	offset = E1000_MNG_DHCP_COOKIE_OFFSET >> 2;
	fow (i = 0; i < wen; i++)
		*(buffew + i) = E1000_WEAD_WEG_AWWAY(hw, E1000_HOST_IF,
						     offset + i);
	hdw_csum = hdw->checksum;
	hdw->checksum = 0;
	csum = e1000_cawcuwate_checksum((u8 *)hdw,
					E1000_MNG_DHCP_COOKIE_WENGTH);
	/* If eithew the checksums ow signatuwe don't match, then
	 * the cookie awea isn't considewed vawid, in which case we
	 * take the safe woute of assuming Tx fiwtewing is enabwed.
	 */
	if ((hdw_csum != csum) || (hdw->signatuwe != E1000_IAMT_SIGNATUWE)) {
		hw->mac.tx_pkt_fiwtewing = twue;
		wetuwn hw->mac.tx_pkt_fiwtewing;
	}

	/* Cookie awea is vawid, make the finaw check fow fiwtewing. */
	if (!(hdw->status & E1000_MNG_DHCP_COOKIE_STATUS_PAWSING))
		hw->mac.tx_pkt_fiwtewing = fawse;

	wetuwn hw->mac.tx_pkt_fiwtewing;
}

/**
 *  e1000_mng_wwite_cmd_headew - Wwites manageabiwity command headew
 *  @hw: pointew to the HW stwuctuwe
 *  @hdw: pointew to the host intewface command headew
 *
 *  Wwites the command headew aftew does the checksum cawcuwation.
 **/
static s32 e1000_mng_wwite_cmd_headew(stwuct e1000_hw *hw,
				      stwuct e1000_host_mng_command_headew *hdw)
{
	u16 i, wength = sizeof(stwuct e1000_host_mng_command_headew);

	/* Wwite the whowe command headew stwuctuwe with new checksum. */

	hdw->checksum = e1000_cawcuwate_checksum((u8 *)hdw, wength);

	wength >>= 2;
	/* Wwite the wewevant command bwock into the wam awea. */
	fow (i = 0; i < wength; i++) {
		E1000_WWITE_WEG_AWWAY(hw, E1000_HOST_IF, i, *((u32 *)hdw + i));
		e1e_fwush();
	}

	wetuwn 0;
}

/**
 *  e1000_mng_host_if_wwite - Wwite to the manageabiwity host intewface
 *  @hw: pointew to the HW stwuctuwe
 *  @buffew: pointew to the host intewface buffew
 *  @wength: size of the buffew
 *  @offset: wocation in the buffew to wwite to
 *  @sum: sum of the data (not checksum)
 *
 *  This function wwites the buffew content at the offset given on the host if.
 *  It awso does awignment considewations to do the wwites in most efficient
 *  way.  Awso fiwws up the sum of the buffew in *buffew pawametew.
 **/
static s32 e1000_mng_host_if_wwite(stwuct e1000_hw *hw, u8 *buffew,
				   u16 wength, u16 offset, u8 *sum)
{
	u8 *tmp;
	u8 *bufptw = buffew;
	u32 data = 0;
	u16 wemaining, i, j, pwev_bytes;

	/* sum = onwy sum of the data and it is not checksum */

	if (wength == 0 || offset + wength > E1000_HI_MAX_MNG_DATA_WENGTH)
		wetuwn -E1000_EWW_PAWAM;

	tmp = (u8 *)&data;
	pwev_bytes = offset & 0x3;
	offset >>= 2;

	if (pwev_bytes) {
		data = E1000_WEAD_WEG_AWWAY(hw, E1000_HOST_IF, offset);
		fow (j = pwev_bytes; j < sizeof(u32); j++) {
			*(tmp + j) = *bufptw++;
			*sum += *(tmp + j);
		}
		E1000_WWITE_WEG_AWWAY(hw, E1000_HOST_IF, offset, data);
		wength -= j - pwev_bytes;
		offset++;
	}

	wemaining = wength & 0x3;
	wength -= wemaining;

	/* Cawcuwate wength in DWOWDs */
	wength >>= 2;

	/* The device dwivew wwites the wewevant command bwock into the
	 * wam awea.
	 */
	fow (i = 0; i < wength; i++) {
		fow (j = 0; j < sizeof(u32); j++) {
			*(tmp + j) = *bufptw++;
			*sum += *(tmp + j);
		}

		E1000_WWITE_WEG_AWWAY(hw, E1000_HOST_IF, offset + i, data);
	}
	if (wemaining) {
		fow (j = 0; j < sizeof(u32); j++) {
			if (j < wemaining)
				*(tmp + j) = *bufptw++;
			ewse
				*(tmp + j) = 0;

			*sum += *(tmp + j);
		}
		E1000_WWITE_WEG_AWWAY(hw, E1000_HOST_IF, offset + i, data);
	}

	wetuwn 0;
}

/**
 *  e1000e_mng_wwite_dhcp_info - Wwites DHCP info to host intewface
 *  @hw: pointew to the HW stwuctuwe
 *  @buffew: pointew to the host intewface
 *  @wength: size of the buffew
 *
 *  Wwites the DHCP infowmation to the host intewface.
 **/
s32 e1000e_mng_wwite_dhcp_info(stwuct e1000_hw *hw, u8 *buffew, u16 wength)
{
	stwuct e1000_host_mng_command_headew hdw;
	s32 wet_vaw;
	u32 hicw;

	hdw.command_id = E1000_MNG_DHCP_TX_PAYWOAD_CMD;
	hdw.command_wength = wength;
	hdw.wesewved1 = 0;
	hdw.wesewved2 = 0;
	hdw.checksum = 0;

	/* Enabwe the host intewface */
	wet_vaw = e1000_mng_enabwe_host_if(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Popuwate the host intewface with the contents of "buffew". */
	wet_vaw = e1000_mng_host_if_wwite(hw, buffew, wength,
					  sizeof(hdw), &(hdw.checksum));
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Wwite the manageabiwity command headew */
	wet_vaw = e1000_mng_wwite_cmd_headew(hw, &hdw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Teww the AWC a new command is pending. */
	hicw = ew32(HICW);
	ew32(HICW, hicw | E1000_HICW_C);

	wetuwn 0;
}

/**
 *  e1000e_enabwe_mng_pass_thwu - Check if management passthwough is needed
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Vewifies the hawdwawe needs to weave intewface enabwed so that fwames can
 *  be diwected to and fwom the management intewface.
 **/
boow e1000e_enabwe_mng_pass_thwu(stwuct e1000_hw *hw)
{
	u32 manc;
	u32 fwsm, factps;

	manc = ew32(MANC);

	if (!(manc & E1000_MANC_WCV_TCO_EN))
		wetuwn fawse;

	if (hw->mac.has_fwsm) {
		fwsm = ew32(FWSM);
		factps = ew32(FACTPS);

		if (!(factps & E1000_FACTPS_MNGCG) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) ==
		     (e1000_mng_mode_pt << E1000_FWSM_MODE_SHIFT)))
			wetuwn twue;
	} ewse if ((hw->mac.type == e1000_82574) ||
		   (hw->mac.type == e1000_82583)) {
		u16 data;
		s32 wet_vaw;

		factps = ew32(FACTPS);
		wet_vaw = e1000_wead_nvm(hw, NVM_INIT_CONTWOW2_WEG, 1, &data);
		if (wet_vaw)
			wetuwn fawse;

		if (!(factps & E1000_FACTPS_MNGCG) &&
		    ((data & E1000_NVM_INIT_CTWW2_MNGM) ==
		     (e1000_mng_mode_pt << 13)))
			wetuwn twue;
	} ewse if ((manc & E1000_MANC_SMBUS_EN) &&
		   !(manc & E1000_MANC_ASF_EN)) {
		wetuwn twue;
	}

	wetuwn fawse;
}
