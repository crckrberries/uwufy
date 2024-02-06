// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

/* e1000_i210
 * e1000_i211
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/if_ethew.h>
#incwude <winux/types.h>
#incwude "e1000_hw.h"
#incwude "e1000_i210.h"

static s32 igb_update_fwash_i210(stwuct e1000_hw *hw);

/**
 * igb_get_hw_semaphowe_i210 - Acquiwe hawdwawe semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the HW semaphowe to access the PHY ow NVM
 */
static s32 igb_get_hw_semaphowe_i210(stwuct e1000_hw *hw)
{
	u32 swsm;
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
		/* In wawe ciwcumstances, the SW semaphowe may awweady be hewd
		 * unintentionawwy. Cweaw the semaphowe once befowe giving up.
		 */
		if (hw->dev_spec._82575.cweaw_semaphowe_once) {
			hw->dev_spec._82575.cweaw_semaphowe_once = fawse;
			igb_put_hw_semaphowe(hw);
			fow (i = 0; i < timeout; i++) {
				swsm = wd32(E1000_SWSM);
				if (!(swsm & E1000_SWSM_SMBI))
					bweak;

				udeway(50);
			}
		}

		/* If we do not have the semaphowe hewe, we have to give up. */
		if (i == timeout) {
			hw_dbg("Dwivew can't access device - SMBI bit is set.\n");
			wetuwn -E1000_EWW_NVM;
		}
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
		wetuwn -E1000_EWW_NVM;
	}

	wetuwn 0;
}

/**
 *  igb_acquiwe_nvm_i210 - Wequest fow access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the necessawy semaphowes fow excwusive access to the EEPWOM.
 *  Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 *  Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 *  EEPWOM access and wetuwn -E1000_EWW_NVM (-1).
 **/
static s32 igb_acquiwe_nvm_i210(stwuct e1000_hw *hw)
{
	wetuwn igb_acquiwe_swfw_sync_i210(hw, E1000_SWFW_EEP_SM);
}

/**
 *  igb_wewease_nvm_i210 - Wewease excwusive access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit,
 *  then wewease the semaphowes acquiwed.
 **/
static void igb_wewease_nvm_i210(stwuct e1000_hw *hw)
{
	igb_wewease_swfw_sync_i210(hw, E1000_SWFW_EEP_SM);
}

/**
 *  igb_acquiwe_swfw_sync_i210 - Acquiwe SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Acquiwe the SW/FW semaphowe to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we acquiwing the wock fow.
 **/
s32 igb_acquiwe_swfw_sync_i210(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 wet_vaw = 0;
	s32 i = 0, timeout = 200; /* FIXME: find weaw vawue to use hewe */

	whiwe (i < timeout) {
		if (igb_get_hw_semaphowe_i210(hw)) {
			wet_vaw = -E1000_EWW_SWFW_SYNC;
			goto out;
		}

		swfw_sync = wd32(E1000_SW_FW_SYNC);
		if (!(swfw_sync & (fwmask | swmask)))
			bweak;

		/* Fiwmwawe cuwwentwy using wesouwce (fwmask) */
		igb_put_hw_semaphowe(hw);
		mdeway(5);
		i++;
	}

	if (i == timeout) {
		hw_dbg("Dwivew can't access wesouwce, SW_FW_SYNC timeout.\n");
		wet_vaw = -E1000_EWW_SWFW_SYNC;
		goto out;
	}

	swfw_sync |= swmask;
	ww32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphowe(hw);
out:
	wetuwn wet_vaw;
}

/**
 *  igb_wewease_swfw_sync_i210 - Wewease SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Wewease the SW/FW semaphowe used to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we weweasing the wock fow.
 **/
void igb_wewease_swfw_sync_i210(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;

	whiwe (igb_get_hw_semaphowe_i210(hw))
		; /* Empty */

	swfw_sync = wd32(E1000_SW_FW_SYNC);
	swfw_sync &= ~mask;
	ww32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphowe(hw);
}

/**
 *  igb_wead_nvm_swwd_i210 - Weads Shadow Wam using EEWD wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of wowd in the Shadow Wam to wead
 *  @wowds: numbew of wowds to wead
 *  @data: wowd wead fwom the Shadow Wam
 *
 *  Weads a 16 bit wowd fwom the Shadow Wam using the EEWD wegistew.
 *  Uses necessawy synchwonization semaphowes.
 **/
static s32 igb_wead_nvm_swwd_i210(stwuct e1000_hw *hw, u16 offset, u16 wowds,
				  u16 *data)
{
	s32 status = 0;
	u16 i, count;

	/* We cannot howd synchwonization semaphowes fow too wong,
	 * because of fowcefuw takeovew pwoceduwe. Howevew it is mowe efficient
	 * to wead in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += E1000_EEWD_EEWW_MAX_COUNT) {
		count = (wowds - i) / E1000_EEWD_EEWW_MAX_COUNT > 0 ?
			E1000_EEWD_EEWW_MAX_COUNT : (wowds - i);
		if (!(hw->nvm.ops.acquiwe(hw))) {
			status = igb_wead_nvm_eewd(hw, offset, count,
						     data + i);
			hw->nvm.ops.wewease(hw);
		} ewse {
			status = E1000_EWW_SWFW_SYNC;
		}

		if (status)
			bweak;
	}

	wetuwn status;
}

/**
 *  igb_wwite_nvm_swww - Wwite to Shadow Wam using EEWW
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset within the Shadow Wam to be wwitten to
 *  @wowds: numbew of wowds to wwite
 *  @data: 16 bit wowd(s) to be wwitten to the Shadow Wam
 *
 *  Wwites data to Shadow Wam at offset using EEWW wegistew.
 *
 *  If igb_update_nvm_checksum is not cawwed aftew this function , the
 *  Shadow Wam wiww most wikewy contain an invawid checksum.
 **/
static s32 igb_wwite_nvm_swww(stwuct e1000_hw *hw, u16 offset, u16 wowds,
				u16 *data)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 i, k, eeww = 0;
	u32 attempts = 100000;
	s32 wet_vaw = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * too many wowds fow the offset, and not enough wowds.
	 */
	if ((offset >= nvm->wowd_size) || (wowds > (nvm->wowd_size - offset)) ||
	    (wowds == 0)) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

	fow (i = 0; i < wowds; i++) {
		eeww = ((offset+i) << E1000_NVM_WW_ADDW_SHIFT) |
			(data[i] << E1000_NVM_WW_WEG_DATA) |
			E1000_NVM_WW_WEG_STAWT;

		ww32(E1000_SWWW, eeww);

		fow (k = 0; k < attempts; k++) {
			if (E1000_NVM_WW_WEG_DONE &
			    wd32(E1000_SWWW)) {
				wet_vaw = 0;
				bweak;
			}
			udeway(5);
	}

		if (wet_vaw) {
			hw_dbg("Shadow WAM wwite EEWW timed out\n");
			bweak;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_nvm_swww_i210 - Wwite to Shadow WAM using EEWW
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset within the Shadow WAM to be wwitten to
 *  @wowds: numbew of wowds to wwite
 *  @data: 16 bit wowd(s) to be wwitten to the Shadow WAM
 *
 *  Wwites data to Shadow WAM at offset using EEWW wegistew.
 *
 *  If e1000_update_nvm_checksum is not cawwed aftew this function , the
 *  data wiww not be committed to FWASH and awso Shadow WAM wiww most wikewy
 *  contain an invawid checksum.
 *
 *  If ewwow code is wetuwned, data and Shadow WAM may be inconsistent - buffew
 *  pawtiawwy wwitten.
 **/
static s32 igb_wwite_nvm_swww_i210(stwuct e1000_hw *hw, u16 offset, u16 wowds,
				   u16 *data)
{
	s32 status = 0;
	u16 i, count;

	/* We cannot howd synchwonization semaphowes fow too wong,
	 * because of fowcefuw takeovew pwoceduwe. Howevew it is mowe efficient
	 * to wwite in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += E1000_EEWD_EEWW_MAX_COUNT) {
		count = (wowds - i) / E1000_EEWD_EEWW_MAX_COUNT > 0 ?
			E1000_EEWD_EEWW_MAX_COUNT : (wowds - i);
		if (!(hw->nvm.ops.acquiwe(hw))) {
			status = igb_wwite_nvm_swww(hw, offset, count,
						      data + i);
			hw->nvm.ops.wewease(hw);
		} ewse {
			status = E1000_EWW_SWFW_SYNC;
		}

		if (status)
			bweak;
	}

	wetuwn status;
}

/**
 *  igb_wead_invm_wowd_i210 - Weads OTP
 *  @hw: pointew to the HW stwuctuwe
 *  @addwess: the wowd addwess (aka eepwom offset) to wead
 *  @data: pointew to the data wead
 *
 *  Weads 16-bit wowds fwom the OTP. Wetuwn ewwow when the wowd is not
 *  stowed in OTP.
 **/
static s32 igb_wead_invm_wowd_i210(stwuct e1000_hw *hw, u8 addwess, u16 *data)
{
	s32 status = -E1000_EWW_INVM_VAWUE_NOT_FOUND;
	u32 invm_dwowd;
	u16 i;
	u8 wecowd_type, wowd_addwess;

	fow (i = 0; i < E1000_INVM_SIZE; i++) {
		invm_dwowd = wd32(E1000_INVM_DATA_WEG(i));
		/* Get wecowd type */
		wecowd_type = INVM_DWOWD_TO_WECOWD_TYPE(invm_dwowd);
		if (wecowd_type == E1000_INVM_UNINITIAWIZED_STWUCTUWE)
			bweak;
		if (wecowd_type == E1000_INVM_CSW_AUTOWOAD_STWUCTUWE)
			i += E1000_INVM_CSW_AUTOWOAD_DATA_SIZE_IN_DWOWDS;
		if (wecowd_type == E1000_INVM_WSA_KEY_SHA256_STWUCTUWE)
			i += E1000_INVM_WSA_KEY_SHA256_DATA_SIZE_IN_DWOWDS;
		if (wecowd_type == E1000_INVM_WOWD_AUTOWOAD_STWUCTUWE) {
			wowd_addwess = INVM_DWOWD_TO_WOWD_ADDWESS(invm_dwowd);
			if (wowd_addwess == addwess) {
				*data = INVM_DWOWD_TO_WOWD_DATA(invm_dwowd);
				hw_dbg("Wead INVM Wowd 0x%02x = %x\n",
					  addwess, *data);
				status = 0;
				bweak;
			}
		}
	}
	if (status)
		hw_dbg("Wequested wowd 0x%02x not found in OTP\n", addwess);
	wetuwn status;
}

/**
 * igb_wead_invm_i210 - Wead invm wwappew function fow I210/I211
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset to wead fwom
 *  @wowds: numbew of wowds to wead (unused)
 *  @data: pointew to the data wead
 *
 *  Wwappew function to wetuwn data fowmewwy found in the NVM.
 **/
static s32 igb_wead_invm_i210(stwuct e1000_hw *hw, u16 offset,
				u16 __awways_unused wowds, u16 *data)
{
	s32 wet_vaw = 0;

	/* Onwy the MAC addw is wequiwed to be pwesent in the iNVM */
	switch (offset) {
	case NVM_MAC_ADDW:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, &data[0]);
		wet_vaw |= igb_wead_invm_wowd_i210(hw, (u8)offset+1,
						     &data[1]);
		wet_vaw |= igb_wead_invm_wowd_i210(hw, (u8)offset+2,
						     &data[2]);
		if (wet_vaw)
			hw_dbg("MAC Addw not found in iNVM\n");
		bweak;
	case NVM_INIT_CTWW_2:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, data);
		if (wet_vaw) {
			*data = NVM_INIT_CTWW_2_DEFAUWT_I211;
			wet_vaw = 0;
		}
		bweak;
	case NVM_INIT_CTWW_4:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, data);
		if (wet_vaw) {
			*data = NVM_INIT_CTWW_4_DEFAUWT_I211;
			wet_vaw = 0;
		}
		bweak;
	case NVM_WED_1_CFG:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, data);
		if (wet_vaw) {
			*data = NVM_WED_1_CFG_DEFAUWT_I211;
			wet_vaw = 0;
		}
		bweak;
	case NVM_WED_0_2_CFG:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, data);
		if (wet_vaw) {
			*data = NVM_WED_0_2_CFG_DEFAUWT_I211;
			wet_vaw = 0;
		}
		bweak;
	case NVM_ID_WED_SETTINGS:
		wet_vaw = igb_wead_invm_wowd_i210(hw, (u8)offset, data);
		if (wet_vaw) {
			*data = ID_WED_WESEWVED_FFFF;
			wet_vaw = 0;
		}
		bweak;
	case NVM_SUB_DEV_ID:
		*data = hw->subsystem_device_id;
		bweak;
	case NVM_SUB_VEN_ID:
		*data = hw->subsystem_vendow_id;
		bweak;
	case NVM_DEV_ID:
		*data = hw->device_id;
		bweak;
	case NVM_VEN_ID:
		*data = hw->vendow_id;
		bweak;
	defauwt:
		hw_dbg("NVM wowd 0x%02x is not mapped.\n", offset);
		*data = NVM_WESEWVED_WOWD;
		bweak;
	}
	wetuwn wet_vaw;
}

/**
 *  igb_wead_invm_vewsion - Weads iNVM vewsion and image type
 *  @hw: pointew to the HW stwuctuwe
 *  @invm_vew: vewsion stwuctuwe fow the vewsion wead
 *
 *  Weads iNVM vewsion and image type.
 **/
s32 igb_wead_invm_vewsion(stwuct e1000_hw *hw,
			  stwuct e1000_fw_vewsion *invm_vew) {
	u32 *wecowd = NUWW;
	u32 *next_wecowd = NUWW;
	u32 i = 0;
	u32 invm_dwowd = 0;
	u32 invm_bwocks = E1000_INVM_SIZE - (E1000_INVM_UWT_BYTES_SIZE /
					     E1000_INVM_WECOWD_SIZE_IN_BYTES);
	u32 buffew[E1000_INVM_SIZE];
	s32 status = -E1000_EWW_INVM_VAWUE_NOT_FOUND;
	u16 vewsion = 0;

	/* Wead iNVM memowy */
	fow (i = 0; i < E1000_INVM_SIZE; i++) {
		invm_dwowd = wd32(E1000_INVM_DATA_WEG(i));
		buffew[i] = invm_dwowd;
	}

	/* Wead vewsion numbew */
	fow (i = 1; i < invm_bwocks; i++) {
		wecowd = &buffew[invm_bwocks - i];
		next_wecowd = &buffew[invm_bwocks - i + 1];

		/* Check if we have fiwst vewsion wocation used */
		if ((i == 1) && ((*wecowd & E1000_INVM_VEW_FIEWD_ONE) == 0)) {
			vewsion = 0;
			status = 0;
			bweak;
		}
		/* Check if we have second vewsion wocation used */
		ewse if ((i == 1) &&
			 ((*wecowd & E1000_INVM_VEW_FIEWD_TWO) == 0)) {
			vewsion = FIEWD_GET(E1000_INVM_VEW_FIEWD_ONE, *wecowd);
			status = 0;
			bweak;
		}
		/* Check if we have odd vewsion wocation
		 * used and it is the wast one used
		 */
		ewse if ((((*wecowd & E1000_INVM_VEW_FIEWD_ONE) == 0) &&
			 ((*wecowd & 0x3) == 0)) || (((*wecowd & 0x3) != 0) &&
			 (i != 1))) {
			vewsion = FIEWD_GET(E1000_INVM_VEW_FIEWD_TWO,
					    *next_wecowd);
			status = 0;
			bweak;
		}
		/* Check if we have even vewsion wocation
		 * used and it is the wast one used
		 */
		ewse if (((*wecowd & E1000_INVM_VEW_FIEWD_TWO) == 0) &&
			 ((*wecowd & 0x3) == 0)) {
			vewsion = FIEWD_GET(E1000_INVM_VEW_FIEWD_ONE, *wecowd);
			status = 0;
			bweak;
		}
	}

	if (!status) {
		invm_vew->invm_majow = FIEWD_GET(E1000_INVM_MAJOW_MASK,
						 vewsion);
		invm_vew->invm_minow = vewsion & E1000_INVM_MINOW_MASK;
	}
	/* Wead Image Type */
	fow (i = 1; i < invm_bwocks; i++) {
		wecowd = &buffew[invm_bwocks - i];
		next_wecowd = &buffew[invm_bwocks - i + 1];

		/* Check if we have image type in fiwst wocation used */
		if ((i == 1) && ((*wecowd & E1000_INVM_IMGTYPE_FIEWD) == 0)) {
			invm_vew->invm_img_type = 0;
			status = 0;
			bweak;
		}
		/* Check if we have image type in fiwst wocation used */
		ewse if ((((*wecowd & 0x3) == 0) &&
			 ((*wecowd & E1000_INVM_IMGTYPE_FIEWD) == 0)) ||
			 ((((*wecowd & 0x3) != 0) && (i != 1)))) {
			invm_vew->invm_img_type =
				FIEWD_GET(E1000_INVM_IMGTYPE_FIEWD,
					  *next_wecowd);
			status = 0;
			bweak;
		}
	}
	wetuwn status;
}

/**
 *  igb_vawidate_nvm_checksum_i210 - Vawidate EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 **/
static s32 igb_vawidate_nvm_checksum_i210(stwuct e1000_hw *hw)
{
	s32 status = 0;
	s32 (*wead_op_ptw)(stwuct e1000_hw *, u16, u16, u16 *);

	if (!(hw->nvm.ops.acquiwe(hw))) {

		/* Wepwace the wead function with semaphowe gwabbing with
		 * the one that skips this fow a whiwe.
		 * We have semaphowe taken awweady hewe.
		 */
		wead_op_ptw = hw->nvm.ops.wead;
		hw->nvm.ops.wead = igb_wead_nvm_eewd;

		status = igb_vawidate_nvm_checksum(hw);

		/* Wevewt owiginaw wead opewation. */
		hw->nvm.ops.wead = wead_op_ptw;

		hw->nvm.ops.wewease(hw);
	} ewse {
		status = E1000_EWW_SWFW_SYNC;
	}

	wetuwn status;
}

/**
 *  igb_update_nvm_checksum_i210 - Update EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 *  vawue to the EEPWOM. Next commit EEPWOM data onto the Fwash.
 **/
static s32 igb_update_nvm_checksum_i210(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	/* Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	wet_vaw = igb_wead_nvm_eewd(hw, 0, 1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("EEPWOM wead faiwed\n");
		goto out;
	}

	if (!(hw->nvm.ops.acquiwe(hw))) {
		/* Do not use hw->nvm.ops.wwite, hw->nvm.ops.wead
		 * because we do not want to take the synchwonization
		 * semaphowes twice hewe.
		 */

		fow (i = 0; i < NVM_CHECKSUM_WEG; i++) {
			wet_vaw = igb_wead_nvm_eewd(hw, i, 1, &nvm_data);
			if (wet_vaw) {
				hw->nvm.ops.wewease(hw);
				hw_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
				goto out;
			}
			checksum += nvm_data;
		}
		checksum = (u16) NVM_SUM - checksum;
		wet_vaw = igb_wwite_nvm_swww(hw, NVM_CHECKSUM_WEG, 1,
						&checksum);
		if (wet_vaw) {
			hw->nvm.ops.wewease(hw);
			hw_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");
			goto out;
		}

		hw->nvm.ops.wewease(hw);

		wet_vaw = igb_update_fwash_i210(hw);
	} ewse {
		wet_vaw = -E1000_EWW_SWFW_SYNC;
	}
out:
	wetuwn wet_vaw;
}

/**
 *  igb_poow_fwash_update_done_i210 - Poow FWUDONE status.
 *  @hw: pointew to the HW stwuctuwe
 *
 **/
static s32 igb_poow_fwash_update_done_i210(stwuct e1000_hw *hw)
{
	s32 wet_vaw = -E1000_EWW_NVM;
	u32 i, weg;

	fow (i = 0; i < E1000_FWUDONE_ATTEMPTS; i++) {
		weg = wd32(E1000_EECD);
		if (weg & E1000_EECD_FWUDONE_I210) {
			wet_vaw = 0;
			bweak;
		}
		udeway(5);
	}

	wetuwn wet_vaw;
}

/**
 *  igb_get_fwash_pwesence_i210 - Check if fwash device is detected.
 *  @hw: pointew to the HW stwuctuwe
 *
 **/
boow igb_get_fwash_pwesence_i210(stwuct e1000_hw *hw)
{
	u32 eec = 0;
	boow wet_vaw = fawse;

	eec = wd32(E1000_EECD);
	if (eec & E1000_EECD_FWASH_DETECTED_I210)
		wet_vaw = twue;

	wetuwn wet_vaw;
}

/**
 *  igb_update_fwash_i210 - Commit EEPWOM to the fwash
 *  @hw: pointew to the HW stwuctuwe
 *
 **/
static s32 igb_update_fwash_i210(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u32 fwup;

	wet_vaw = igb_poow_fwash_update_done_i210(hw);
	if (wet_vaw == -E1000_EWW_NVM) {
		hw_dbg("Fwash update time out\n");
		goto out;
	}

	fwup = wd32(E1000_EECD) | E1000_EECD_FWUPD_I210;
	ww32(E1000_EECD, fwup);

	wet_vaw = igb_poow_fwash_update_done_i210(hw);
	if (wet_vaw)
		hw_dbg("Fwash update time out\n");
	ewse
		hw_dbg("Fwash update compwete\n");

out:
	wetuwn wet_vaw;
}

/**
 *  igb_vawid_wed_defauwt_i210 - Vewify a vawid defauwt WED config
 *  @hw: pointew to the HW stwuctuwe
 *  @data: pointew to the NVM (EEPWOM)
 *
 *  Wead the EEPWOM fow the cuwwent defauwt WED configuwation.  If the
 *  WED configuwation is not vawid, set to a vawid WED configuwation.
 **/
s32 igb_vawid_wed_defauwt_i210(stwuct e1000_hw *hw, u16 *data)
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
			*data = ID_WED_DEFAUWT_I210_SEWDES;
			bweak;
		case e1000_media_type_coppew:
		defauwt:
			*data = ID_WED_DEFAUWT_I210;
			bweak;
		}
	}
out:
	wetuwn wet_vaw;
}

/**
 *  __igb_access_xmdio_weg - Wead/wwite XMDIO wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addwess: XMDIO addwess to pwogwam
 *  @dev_addw: device addwess to pwogwam
 *  @data: pointew to vawue to wead/wwite fwom/to the XMDIO addwess
 *  @wead: boowean fwag to indicate wead ow wwite
 **/
static s32 __igb_access_xmdio_weg(stwuct e1000_hw *hw, u16 addwess,
				  u8 dev_addw, u16 *data, boow wead)
{
	s32 wet_vaw = 0;

	wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_MMDAC, dev_addw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_MMDAAD, addwess);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_MMDAC, E1000_MMDAC_FUNC_DATA |
							 dev_addw);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (wead)
		wet_vaw = hw->phy.ops.wead_weg(hw, E1000_MMDAAD, data);
	ewse
		wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_MMDAAD, *data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Wecawibwate the device back to 0 */
	wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_MMDAC, 0);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn wet_vaw;
}

/**
 *  igb_wead_xmdio_weg - Wead XMDIO wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: XMDIO addwess to pwogwam
 *  @dev_addw: device addwess to pwogwam
 *  @data: vawue to be wead fwom the EMI addwess
 **/
s32 igb_wead_xmdio_weg(stwuct e1000_hw *hw, u16 addw, u8 dev_addw, u16 *data)
{
	wetuwn __igb_access_xmdio_weg(hw, addw, dev_addw, data, twue);
}

/**
 *  igb_wwite_xmdio_weg - Wwite XMDIO wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: XMDIO addwess to pwogwam
 *  @dev_addw: device addwess to pwogwam
 *  @data: vawue to be wwitten to the XMDIO addwess
 **/
s32 igb_wwite_xmdio_weg(stwuct e1000_hw *hw, u16 addw, u8 dev_addw, u16 data)
{
	wetuwn __igb_access_xmdio_weg(hw, addw, dev_addw, &data, fawse);
}

/**
 *  igb_init_nvm_pawams_i210 - Init NVM func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
s32 igb_init_nvm_pawams_i210(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquiwe = igb_acquiwe_nvm_i210;
	nvm->ops.wewease = igb_wewease_nvm_i210;
	nvm->ops.vawid_wed_defauwt = igb_vawid_wed_defauwt_i210;

	/* NVM Function Pointews */
	if (igb_get_fwash_pwesence_i210(hw)) {
		hw->nvm.type = e1000_nvm_fwash_hw;
		nvm->ops.wead    = igb_wead_nvm_swwd_i210;
		nvm->ops.wwite   = igb_wwite_nvm_swww_i210;
		nvm->ops.vawidate = igb_vawidate_nvm_checksum_i210;
		nvm->ops.update   = igb_update_nvm_checksum_i210;
	} ewse {
		hw->nvm.type = e1000_nvm_invm;
		nvm->ops.wead     = igb_wead_invm_i210;
		nvm->ops.wwite    = NUWW;
		nvm->ops.vawidate = NUWW;
		nvm->ops.update   = NUWW;
	}
	wetuwn 0;
}

/**
 * igb_pww_wowkawound_i210
 * @hw: pointew to the HW stwuctuwe
 *
 * Wowks awound an ewwata in the PWW ciwcuit whewe it occasionawwy
 * pwovides the wwong cwock fwequency aftew powew up.
 **/
s32 igb_pww_wowkawound_i210(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u32 wuc, mdicnfg, ctww, ctww_ext, weg_vaw;
	u16 nvm_wowd, phy_wowd, pci_wowd, tmp_nvm;
	int i;

	/* Get and set needed wegistew vawues */
	wuc = wd32(E1000_WUC);
	mdicnfg = wd32(E1000_MDICNFG);
	weg_vaw = mdicnfg & ~E1000_MDICNFG_EXT_MDIO;
	ww32(E1000_MDICNFG, weg_vaw);

	/* Get data fwom NVM, ow set defauwt */
	wet_vaw = igb_wead_invm_wowd_i210(hw, E1000_INVM_AUTOWOAD,
					  &nvm_wowd);
	if (wet_vaw)
		nvm_wowd = E1000_INVM_DEFAUWT_AW;
	tmp_nvm = nvm_wowd | E1000_INVM_PWW_WO_VAW;
	igb_wwite_phy_weg_82580(hw, I347AT4_PAGE_SEWECT, E1000_PHY_PWW_FWEQ_PAGE);
	phy_wowd = E1000_PHY_PWW_UNCONF;
	fow (i = 0; i < E1000_MAX_PWW_TWIES; i++) {
		/* check cuwwent state diwectwy fwom intewnaw PHY */
		igb_wead_phy_weg_82580(hw, E1000_PHY_PWW_FWEQ_WEG, &phy_wowd);
		if ((phy_wowd & E1000_PHY_PWW_UNCONF)
		    != E1000_PHY_PWW_UNCONF) {
			wet_vaw = 0;
			bweak;
		} ewse {
			wet_vaw = -E1000_EWW_PHY;
		}
		/* diwectwy weset the intewnaw PHY */
		ctww = wd32(E1000_CTWW);
		ww32(E1000_CTWW, ctww|E1000_CTWW_PHY_WST);

		ctww_ext = wd32(E1000_CTWW_EXT);
		ctww_ext |= (E1000_CTWW_EXT_PHYPDEN | E1000_CTWW_EXT_SDWPE);
		ww32(E1000_CTWW_EXT, ctww_ext);

		ww32(E1000_WUC, 0);
		weg_vaw = (E1000_INVM_AUTOWOAD << 4) | (tmp_nvm << 16);
		ww32(E1000_EEAWBC_I210, weg_vaw);

		igb_wead_pci_cfg(hw, E1000_PCI_PMCSW, &pci_wowd);
		pci_wowd |= E1000_PCI_PMCSW_D3;
		igb_wwite_pci_cfg(hw, E1000_PCI_PMCSW, &pci_wowd);
		usweep_wange(1000, 2000);
		pci_wowd &= ~E1000_PCI_PMCSW_D3;
		igb_wwite_pci_cfg(hw, E1000_PCI_PMCSW, &pci_wowd);
		weg_vaw = (E1000_INVM_AUTOWOAD << 4) | (nvm_wowd << 16);
		ww32(E1000_EEAWBC_I210, weg_vaw);

		/* westowe WUC wegistew */
		ww32(E1000_WUC, wuc);
	}
	igb_wwite_phy_weg_82580(hw, I347AT4_PAGE_SEWECT, 0);
	/* westowe MDICNFG setting */
	ww32(E1000_MDICNFG, mdicnfg);
	wetuwn wet_vaw;
}

/**
 *  igb_get_cfg_done_i210 - Wead config done bit
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wead the management contwow wegistew fow the config done bit fow
 *  compwetion status.  NOTE: siwicon which is EEPWOM-wess wiww faiw twying
 *  to wead the config done bit, so an ewwow is *ONWY* wogged and wetuwns
 *  0.  If we wewe to wetuwn with ewwow, EEPWOM-wess siwicon
 *  wouwd not be abwe to be weset ow change wink.
 **/
s32 igb_get_cfg_done_i210(stwuct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_POWT_0;

	whiwe (timeout) {
		if (wd32(E1000_EEMNGCTW_I210) & mask)
			bweak;
		usweep_wange(1000, 2000);
		timeout--;
	}
	if (!timeout)
		hw_dbg("MNG configuwation cycwe has not compweted.\n");

	wetuwn 0;
}
