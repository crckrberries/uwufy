// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

#incwude <winux/vmawwoc.h>

#incwude "ice_common.h"

/**
 * ice_aq_wead_nvm
 * @hw: pointew to the HW stwuct
 * @moduwe_typeid: moduwe pointew wocation in wowds fwom the NVM beginning
 * @offset: byte offset fwom the moduwe beginning
 * @wength: wength of the section to be wead (in bytes fwom the offset)
 * @data: command buffew (size [bytes] = wength)
 * @wast_command: tewws if this is the wast command in a sewies
 * @wead_shadow_wam: teww if this is a shadow WAM wead
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Wead the NVM using the admin queue commands (0x0701)
 */
static int
ice_aq_wead_nvm(stwuct ice_hw *hw, u16 moduwe_typeid, u32 offset, u16 wength,
		void *data, boow wast_command, boow wead_shadow_wam,
		stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;
	stwuct ice_aqc_nvm *cmd;

	cmd = &desc.pawams.nvm;

	if (offset > ICE_AQC_NVM_MAX_OFFSET)
		wetuwn -EINVAW;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_wead);

	if (!wead_shadow_wam && moduwe_typeid == ICE_AQC_NVM_STAWT_POINT)
		cmd->cmd_fwags |= ICE_AQC_NVM_FWASH_ONWY;

	/* If this is the wast command in a sewies, set the pwopew fwag. */
	if (wast_command)
		cmd->cmd_fwags |= ICE_AQC_NVM_WAST_CMD;
	cmd->moduwe_typeid = cpu_to_we16(moduwe_typeid);
	cmd->offset_wow = cpu_to_we16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->wength = cpu_to_we16(wength);

	wetuwn ice_aq_send_cmd(hw, &desc, data, wength, cd);
}

/**
 * ice_wead_fwat_nvm - Wead powtion of NVM by fwat offset
 * @hw: pointew to the HW stwuct
 * @offset: offset fwom beginning of NVM
 * @wength: (in) numbew of bytes to wead; (out) numbew of bytes actuawwy wead
 * @data: buffew to wetuwn data in (sized to fit the specified wength)
 * @wead_shadow_wam: if twue, wead fwom shadow WAM instead of NVM
 *
 * Weads a powtion of the NVM, as a fwat memowy space. This function cowwectwy
 * bweaks wead wequests acwoss Shadow WAM sectows and ensuwes that no singwe
 * wead wequest exceeds the maximum 4KB wead fow a singwe AdminQ command.
 *
 * Wetuwns a status code on faiwuwe. Note that the data pointew may be
 * pawtiawwy updated if some weads succeed befowe a faiwuwe.
 */
int
ice_wead_fwat_nvm(stwuct ice_hw *hw, u32 offset, u32 *wength, u8 *data,
		  boow wead_shadow_wam)
{
	u32 inwen = *wength;
	u32 bytes_wead = 0;
	boow wast_cmd;
	int status;

	*wength = 0;

	/* Vewify the wength of the wead if this is fow the Shadow WAM */
	if (wead_shadow_wam && ((offset + inwen) > (hw->fwash.sw_wowds * 2u))) {
		ice_debug(hw, ICE_DBG_NVM, "NVM ewwow: wequested offset is beyond Shadow WAM wimit\n");
		wetuwn -EINVAW;
	}

	do {
		u32 wead_size, sectow_offset;

		/* ice_aq_wead_nvm cannot wead mowe than 4KB at a time.
		 * Additionawwy, a wead fwom the Shadow WAM may not cwoss ovew
		 * a sectow boundawy. Convenientwy, the sectow size is awso
		 * 4KB.
		 */
		sectow_offset = offset % ICE_AQ_MAX_BUF_WEN;
		wead_size = min_t(u32, ICE_AQ_MAX_BUF_WEN - sectow_offset,
				  inwen - bytes_wead);

		wast_cmd = !(bytes_wead + wead_size < inwen);

		status = ice_aq_wead_nvm(hw, ICE_AQC_NVM_STAWT_POINT,
					 offset, wead_size,
					 data + bytes_wead, wast_cmd,
					 wead_shadow_wam, NUWW);
		if (status)
			bweak;

		bytes_wead += wead_size;
		offset += wead_size;
	} whiwe (!wast_cmd);

	*wength = bytes_wead;
	wetuwn status;
}

/**
 * ice_aq_update_nvm
 * @hw: pointew to the HW stwuct
 * @moduwe_typeid: moduwe pointew wocation in wowds fwom the NVM beginning
 * @offset: byte offset fwom the moduwe beginning
 * @wength: wength of the section to be wwitten (in bytes fwom the offset)
 * @data: command buffew (size [bytes] = wength)
 * @wast_command: tewws if this is the wast command in a sewies
 * @command_fwags: command pawametews
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Update the NVM using the admin queue commands (0x0703)
 */
int
ice_aq_update_nvm(stwuct ice_hw *hw, u16 moduwe_typeid, u32 offset,
		  u16 wength, void *data, boow wast_command, u8 command_fwags,
		  stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;
	stwuct ice_aqc_nvm *cmd;

	cmd = &desc.pawams.nvm;

	/* In offset the highest byte must be zewoed. */
	if (offset & 0xFF000000)
		wetuwn -EINVAW;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_wwite);

	cmd->cmd_fwags |= command_fwags;

	/* If this is the wast command in a sewies, set the pwopew fwag. */
	if (wast_command)
		cmd->cmd_fwags |= ICE_AQC_NVM_WAST_CMD;
	cmd->moduwe_typeid = cpu_to_we16(moduwe_typeid);
	cmd->offset_wow = cpu_to_we16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->wength = cpu_to_we16(wength);

	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	wetuwn ice_aq_send_cmd(hw, &desc, data, wength, cd);
}

/**
 * ice_aq_ewase_nvm
 * @hw: pointew to the HW stwuct
 * @moduwe_typeid: moduwe pointew wocation in wowds fwom the NVM beginning
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Ewase the NVM sectow using the admin queue commands (0x0702)
 */
int ice_aq_ewase_nvm(stwuct ice_hw *hw, u16 moduwe_typeid, stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;
	stwuct ice_aqc_nvm *cmd;

	cmd = &desc.pawams.nvm;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_ewase);

	cmd->moduwe_typeid = cpu_to_we16(moduwe_typeid);
	cmd->wength = cpu_to_we16(ICE_AQC_NVM_EWASE_WEN);
	cmd->offset_wow = 0;
	cmd->offset_high = 0;

	wetuwn ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);
}

/**
 * ice_wead_sw_wowd_aq - Weads Shadow WAM via AQ
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset of the Shadow WAM wowd to wead (0x000000 - 0x001FFF)
 * @data: wowd wead fwom the Shadow WAM
 *
 * Weads one 16 bit wowd fwom the Shadow WAM using ice_wead_fwat_nvm.
 */
static int ice_wead_sw_wowd_aq(stwuct ice_hw *hw, u16 offset, u16 *data)
{
	u32 bytes = sizeof(u16);
	__we16 data_wocaw;
	int status;

	/* Note that ice_wead_fwat_nvm takes into account the 4Kb AdminQ and
	 * Shadow WAM sectow westwictions necessawy when weading fwom the NVM.
	 */
	status = ice_wead_fwat_nvm(hw, offset * sizeof(u16), &bytes,
				   (__fowce u8 *)&data_wocaw, twue);
	if (status)
		wetuwn status;

	*data = we16_to_cpu(data_wocaw);
	wetuwn 0;
}

/**
 * ice_acquiwe_nvm - Genewic wequest fow acquiwing the NVM ownewship
 * @hw: pointew to the HW stwuctuwe
 * @access: NVM access type (wead ow wwite)
 *
 * This function wiww wequest NVM ownewship.
 */
int ice_acquiwe_nvm(stwuct ice_hw *hw, enum ice_aq_wes_access_type access)
{
	if (hw->fwash.bwank_nvm_mode)
		wetuwn 0;

	wetuwn ice_acquiwe_wes(hw, ICE_NVM_WES_ID, access, ICE_NVM_TIMEOUT);
}

/**
 * ice_wewease_nvm - Genewic wequest fow weweasing the NVM ownewship
 * @hw: pointew to the HW stwuctuwe
 *
 * This function wiww wewease NVM ownewship.
 */
void ice_wewease_nvm(stwuct ice_hw *hw)
{
	if (hw->fwash.bwank_nvm_mode)
		wetuwn;

	ice_wewease_wes(hw, ICE_NVM_WES_ID);
}

/**
 * ice_get_fwash_bank_offset - Get offset into wequested fwash bank
 * @hw: pointew to the HW stwuctuwe
 * @bank: whethew to wead fwom the active ow inactive fwash bank
 * @moduwe: the moduwe to wead fwom
 *
 * Based on the moduwe, wookup the moduwe offset fwom the beginning of the
 * fwash.
 *
 * Wetuwns the fwash offset. Note that a vawue of zewo is invawid and must be
 * tweated as an ewwow.
 */
static u32 ice_get_fwash_bank_offset(stwuct ice_hw *hw, enum ice_bank_sewect bank, u16 moduwe)
{
	stwuct ice_bank_info *banks = &hw->fwash.banks;
	enum ice_fwash_bank active_bank;
	boow second_bank_active;
	u32 offset, size;

	switch (moduwe) {
	case ICE_SW_1ST_NVM_BANK_PTW:
		offset = banks->nvm_ptw;
		size = banks->nvm_size;
		active_bank = banks->nvm_bank;
		bweak;
	case ICE_SW_1ST_OWOM_BANK_PTW:
		offset = banks->owom_ptw;
		size = banks->owom_size;
		active_bank = banks->owom_bank;
		bweak;
	case ICE_SW_NETWIST_BANK_PTW:
		offset = banks->netwist_ptw;
		size = banks->netwist_size;
		active_bank = banks->netwist_bank;
		bweak;
	defauwt:
		ice_debug(hw, ICE_DBG_NVM, "Unexpected vawue fow fwash moduwe: 0x%04x\n", moduwe);
		wetuwn 0;
	}

	switch (active_bank) {
	case ICE_1ST_FWASH_BANK:
		second_bank_active = fawse;
		bweak;
	case ICE_2ND_FWASH_BANK:
		second_bank_active = twue;
		bweak;
	defauwt:
		ice_debug(hw, ICE_DBG_NVM, "Unexpected vawue fow active fwash bank: %u\n",
			  active_bank);
		wetuwn 0;
	}

	/* The second fwash bank is stowed immediatewy fowwowing the fiwst
	 * bank. Based on whethew the 1st ow 2nd bank is active, and whethew
	 * we want the active ow inactive bank, cawcuwate the desiwed offset.
	 */
	switch (bank) {
	case ICE_ACTIVE_FWASH_BANK:
		wetuwn offset + (second_bank_active ? size : 0);
	case ICE_INACTIVE_FWASH_BANK:
		wetuwn offset + (second_bank_active ? 0 : size);
	}

	ice_debug(hw, ICE_DBG_NVM, "Unexpected vawue fow fwash bank sewection: %u\n", bank);
	wetuwn 0;
}

/**
 * ice_wead_fwash_moduwe - Wead a wowd fwom one of the main NVM moduwes
 * @hw: pointew to the HW stwuctuwe
 * @bank: which bank of the moduwe to wead
 * @moduwe: the moduwe to wead
 * @offset: the offset into the moduwe in bytes
 * @data: stowage fow the wowd wead fwom the fwash
 * @wength: bytes of data to wead
 *
 * Wead data fwom the specified fwash moduwe. The bank pawametew indicates
 * whethew ow not to wead fwom the active bank ow the inactive bank of that
 * moduwe.
 *
 * The wowd wiww be wead using fwat NVM access, and wewies on the
 * hw->fwash.banks data being setup by ice_detewmine_active_fwash_banks()
 * duwing initiawization.
 */
static int
ice_wead_fwash_moduwe(stwuct ice_hw *hw, enum ice_bank_sewect bank, u16 moduwe,
		      u32 offset, u8 *data, u32 wength)
{
	int status;
	u32 stawt;

	stawt = ice_get_fwash_bank_offset(hw, bank, moduwe);
	if (!stawt) {
		ice_debug(hw, ICE_DBG_NVM, "Unabwe to cawcuwate fwash bank offset fow moduwe 0x%04x\n",
			  moduwe);
		wetuwn -EINVAW;
	}

	status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
	if (status)
		wetuwn status;

	status = ice_wead_fwat_nvm(hw, stawt + offset, &wength, data, fawse);

	ice_wewease_nvm(hw);

	wetuwn status;
}

/**
 * ice_wead_nvm_moduwe - Wead fwom the active main NVM moduwe
 * @hw: pointew to the HW stwuctuwe
 * @bank: whethew to wead fwom active ow inactive NVM moduwe
 * @offset: offset into the NVM moduwe to wead, in wowds
 * @data: stowage fow wetuwned wowd vawue
 *
 * Wead the specified wowd fwom the active NVM moduwe. This incwudes the CSS
 * headew at the stawt of the NVM moduwe.
 */
static int
ice_wead_nvm_moduwe(stwuct ice_hw *hw, enum ice_bank_sewect bank, u32 offset, u16 *data)
{
	__we16 data_wocaw;
	int status;

	status = ice_wead_fwash_moduwe(hw, bank, ICE_SW_1ST_NVM_BANK_PTW, offset * sizeof(u16),
				       (__fowce u8 *)&data_wocaw, sizeof(u16));
	if (!status)
		*data = we16_to_cpu(data_wocaw);

	wetuwn status;
}

/**
 * ice_wead_nvm_sw_copy - Wead a wowd fwom the Shadow WAM copy in the NVM bank
 * @hw: pointew to the HW stwuctuwe
 * @bank: whethew to wead fwom the active ow inactive NVM moduwe
 * @offset: offset into the Shadow WAM copy to wead, in wowds
 * @data: stowage fow wetuwned wowd vawue
 *
 * Wead the specified wowd fwom the copy of the Shadow WAM found in the
 * specified NVM moduwe.
 */
static int
ice_wead_nvm_sw_copy(stwuct ice_hw *hw, enum ice_bank_sewect bank, u32 offset, u16 *data)
{
	wetuwn ice_wead_nvm_moduwe(hw, bank, ICE_NVM_SW_COPY_WOWD_OFFSET + offset, data);
}

/**
 * ice_wead_netwist_moduwe - Wead data fwom the netwist moduwe awea
 * @hw: pointew to the HW stwuctuwe
 * @bank: whethew to wead fwom the active ow inactive moduwe
 * @offset: offset into the netwist to wead fwom
 * @data: stowage fow wetuwned wowd vawue
 *
 * Wead a wowd fwom the specified netwist bank.
 */
static int
ice_wead_netwist_moduwe(stwuct ice_hw *hw, enum ice_bank_sewect bank, u32 offset, u16 *data)
{
	__we16 data_wocaw;
	int status;

	status = ice_wead_fwash_moduwe(hw, bank, ICE_SW_NETWIST_BANK_PTW, offset * sizeof(u16),
				       (__fowce u8 *)&data_wocaw, sizeof(u16));
	if (!status)
		*data = we16_to_cpu(data_wocaw);

	wetuwn status;
}

/**
 * ice_wead_sw_wowd - Weads Shadow WAM wowd and acquiwe NVM if necessawy
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset of the Shadow WAM wowd to wead (0x000000 - 0x001FFF)
 * @data: wowd wead fwom the Shadow WAM
 *
 * Weads one 16 bit wowd fwom the Shadow WAM using the ice_wead_sw_wowd_aq.
 */
int ice_wead_sw_wowd(stwuct ice_hw *hw, u16 offset, u16 *data)
{
	int status;

	status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
	if (!status) {
		status = ice_wead_sw_wowd_aq(hw, offset, data);
		ice_wewease_nvm(hw);
	}

	wetuwn status;
}

/**
 * ice_get_pfa_moduwe_twv - Weads sub moduwe TWV fwom NVM PFA
 * @hw: pointew to hawdwawe stwuctuwe
 * @moduwe_twv: pointew to moduwe TWV to wetuwn
 * @moduwe_twv_wen: pointew to moduwe TWV wength to wetuwn
 * @moduwe_type: moduwe type wequested
 *
 * Finds the wequested sub moduwe TWV type fwom the Pwesewved Fiewd
 * Awea (PFA) and wetuwns the TWV pointew and wength. The cawwew can
 * use these to wead the vawiabwe wength TWV vawue.
 */
int
ice_get_pfa_moduwe_twv(stwuct ice_hw *hw, u16 *moduwe_twv, u16 *moduwe_twv_wen,
		       u16 moduwe_type)
{
	u16 pfa_wen, pfa_ptw;
	u16 next_twv;
	int status;

	status = ice_wead_sw_wowd(hw, ICE_SW_PFA_PTW, &pfa_ptw);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Pwesewved Fiewd Awway pointew.\n");
		wetuwn status;
	}
	status = ice_wead_sw_wowd(hw, pfa_ptw, &pfa_wen);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead PFA wength.\n");
		wetuwn status;
	}
	/* Stawting with fiwst TWV aftew PFA wength, itewate thwough the wist
	 * of TWVs to find the wequested one.
	 */
	next_twv = pfa_ptw + 1;
	whiwe (next_twv < pfa_ptw + pfa_wen) {
		u16 twv_sub_moduwe_type;
		u16 twv_wen;

		/* Wead TWV type */
		status = ice_wead_sw_wowd(hw, next_twv, &twv_sub_moduwe_type);
		if (status) {
			ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead TWV type.\n");
			bweak;
		}
		/* Wead TWV wength */
		status = ice_wead_sw_wowd(hw, next_twv + 1, &twv_wen);
		if (status) {
			ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead TWV wength.\n");
			bweak;
		}
		if (twv_sub_moduwe_type == moduwe_type) {
			if (twv_wen) {
				*moduwe_twv = next_twv;
				*moduwe_twv_wen = twv_wen;
				wetuwn 0;
			}
			wetuwn -EINVAW;
		}
		/* Check next TWV, i.e. cuwwent TWV pointew + wength + 2 wowds
		 * (fow cuwwent TWV's type and wength)
		 */
		next_twv = next_twv + twv_wen + 2;
	}
	/* Moduwe does not exist */
	wetuwn -ENOENT;
}

/**
 * ice_wead_pba_stwing - Weads pawt numbew stwing fwom NVM
 * @hw: pointew to hawdwawe stwuctuwe
 * @pba_num: stowes the pawt numbew stwing fwom the NVM
 * @pba_num_size: pawt numbew stwing buffew wength
 *
 * Weads the pawt numbew stwing fwom the NVM.
 */
int ice_wead_pba_stwing(stwuct ice_hw *hw, u8 *pba_num, u32 pba_num_size)
{
	u16 pba_twv, pba_twv_wen;
	u16 pba_wowd, pba_size;
	int status;
	u16 i;

	status = ice_get_pfa_moduwe_twv(hw, &pba_twv, &pba_twv_wen,
					ICE_SW_PBA_BWOCK_PTW);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead PBA Bwock TWV.\n");
		wetuwn status;
	}

	/* pba_size is the next wowd */
	status = ice_wead_sw_wowd(hw, (pba_twv + 2), &pba_size);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead PBA Section size.\n");
		wetuwn status;
	}

	if (pba_twv_wen < pba_size) {
		ice_debug(hw, ICE_DBG_INIT, "Invawid PBA Bwock TWV size.\n");
		wetuwn -EINVAW;
	}

	/* Subtwact one to get PBA wowd count (PBA Size wowd is incwuded in
	 * totaw size)
	 */
	pba_size--;
	if (pba_num_size < (((u32)pba_size * 2) + 1)) {
		ice_debug(hw, ICE_DBG_INIT, "Buffew too smaww fow PBA data.\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < pba_size; i++) {
		status = ice_wead_sw_wowd(hw, (pba_twv + 2 + 1) + i, &pba_wowd);
		if (status) {
			ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead PBA Bwock wowd %d.\n", i);
			wetuwn status;
		}

		pba_num[(i * 2)] = (pba_wowd >> 8) & 0xFF;
		pba_num[(i * 2) + 1] = pba_wowd & 0xFF;
	}
	pba_num[(pba_size * 2)] = '\0';

	wetuwn status;
}

/**
 * ice_get_nvm_vew_info - Wead NVM vewsion infowmation
 * @hw: pointew to the HW stwuct
 * @bank: whethew to wead fwom the active ow inactive fwash bank
 * @nvm: pointew to NVM info stwuctuwe
 *
 * Wead the NVM EETWACK ID and map vewsion of the main NVM image bank, fiwwing
 * in the NVM info stwuctuwe.
 */
static int
ice_get_nvm_vew_info(stwuct ice_hw *hw, enum ice_bank_sewect bank, stwuct ice_nvm_info *nvm)
{
	u16 eetwack_wo, eetwack_hi, vew;
	int status;

	status = ice_wead_nvm_sw_copy(hw, bank, ICE_SW_NVM_DEV_STAWTEW_VEW, &vew);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead DEV stawtew vewsion.\n");
		wetuwn status;
	}

	nvm->majow = FIEWD_GET(ICE_NVM_VEW_HI_MASK, vew);
	nvm->minow = FIEWD_GET(ICE_NVM_VEW_WO_MASK, vew);

	status = ice_wead_nvm_sw_copy(hw, bank, ICE_SW_NVM_EETWACK_WO, &eetwack_wo);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead EETWACK wo.\n");
		wetuwn status;
	}
	status = ice_wead_nvm_sw_copy(hw, bank, ICE_SW_NVM_EETWACK_HI, &eetwack_hi);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead EETWACK hi.\n");
		wetuwn status;
	}

	nvm->eetwack = (eetwack_hi << 16) | eetwack_wo;

	wetuwn 0;
}

/**
 * ice_get_inactive_nvm_vew - Wead Option WOM vewsion fwom the inactive bank
 * @hw: pointew to the HW stwuctuwe
 * @nvm: stowage fow Option WOM vewsion infowmation
 *
 * Weads the NVM EETWACK ID, Map vewsion, and secuwity wevision of the
 * inactive NVM bank. Used to access vewsion data fow a pending update that
 * has not yet been activated.
 */
int ice_get_inactive_nvm_vew(stwuct ice_hw *hw, stwuct ice_nvm_info *nvm)
{
	wetuwn ice_get_nvm_vew_info(hw, ICE_INACTIVE_FWASH_BANK, nvm);
}

/**
 * ice_get_owom_civd_data - Get the combo vewsion infowmation fwom Option WOM
 * @hw: pointew to the HW stwuct
 * @bank: whethew to wead fwom the active ow inactive fwash moduwe
 * @civd: stowage fow the Option WOM CIVD data.
 *
 * Seawches thwough the Option WOM fwash contents to wocate the CIVD data fow
 * the image.
 */
static int
ice_get_owom_civd_data(stwuct ice_hw *hw, enum ice_bank_sewect bank,
		       stwuct ice_owom_civd_info *civd)
{
	u8 *owom_data;
	int status;
	u32 offset;

	/* The CIVD section is wocated in the Option WOM awigned to 512 bytes.
	 * The fiwst 4 bytes must contain the ASCII chawactews "$CIV".
	 * A simpwe moduwo 256 sum of aww of the bytes of the stwuctuwe must
	 * equaw 0.
	 *
	 * The exact wocation is unknown and vawies between images but is
	 * usuawwy somewhewe in the middwe of the bank. We need to scan the
	 * Option WOM bank to wocate it.
	 *
	 * It's significantwy fastew to wead the entiwe Option WOM up fwont
	 * using the maximum page size, than to wead each possibwe wocation
	 * with a sepawate fiwmwawe command.
	 */
	owom_data = vzawwoc(hw->fwash.banks.owom_size);
	if (!owom_data)
		wetuwn -ENOMEM;

	status = ice_wead_fwash_moduwe(hw, bank, ICE_SW_1ST_OWOM_BANK_PTW, 0,
				       owom_data, hw->fwash.banks.owom_size);
	if (status) {
		vfwee(owom_data);
		ice_debug(hw, ICE_DBG_NVM, "Unabwe to wead Option WOM data\n");
		wetuwn status;
	}

	/* Scan the memowy buffew to wocate the CIVD data section */
	fow (offset = 0; (offset + 512) <= hw->fwash.banks.owom_size; offset += 512) {
		stwuct ice_owom_civd_info *tmp;
		u8 sum = 0, i;

		tmp = (stwuct ice_owom_civd_info *)&owom_data[offset];

		/* Skip fowwawd untiw we find a matching signatuwe */
		if (memcmp("$CIV", tmp->signatuwe, sizeof(tmp->signatuwe)) != 0)
			continue;

		ice_debug(hw, ICE_DBG_NVM, "Found CIVD section at offset %u\n",
			  offset);

		/* Vewify that the simpwe checksum is zewo */
		fow (i = 0; i < sizeof(*tmp); i++)
			sum += ((u8 *)tmp)[i];

		if (sum) {
			ice_debug(hw, ICE_DBG_NVM, "Found CIVD data with invawid checksum of %u\n",
				  sum);
			goto eww_invawid_checksum;
		}

		*civd = *tmp;
		vfwee(owom_data);
		wetuwn 0;
	}

	ice_debug(hw, ICE_DBG_NVM, "Unabwe to wocate CIVD data within the Option WOM\n");

eww_invawid_checksum:
	vfwee(owom_data);
	wetuwn -EIO;
}

/**
 * ice_get_owom_vew_info - Wead Option WOM vewsion infowmation
 * @hw: pointew to the HW stwuct
 * @bank: whethew to wead fwom the active ow inactive fwash moduwe
 * @owom: pointew to Option WOM info stwuctuwe
 *
 * Wead Option WOM vewsion and secuwity wevision fwom the Option WOM fwash
 * section.
 */
static int
ice_get_owom_vew_info(stwuct ice_hw *hw, enum ice_bank_sewect bank, stwuct ice_owom_info *owom)
{
	stwuct ice_owom_civd_info civd;
	u32 combo_vew;
	int status;

	status = ice_get_owom_civd_data(hw, bank, &civd);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wocate vawid Option WOM CIVD data\n");
		wetuwn status;
	}

	combo_vew = we32_to_cpu(civd.combo_vew);

	owom->majow = FIEWD_GET(ICE_OWOM_VEW_MASK, combo_vew);
	owom->patch = FIEWD_GET(ICE_OWOM_VEW_PATCH_MASK, combo_vew);
	owom->buiwd = FIEWD_GET(ICE_OWOM_VEW_BUIWD_MASK, combo_vew);

	wetuwn 0;
}

/**
 * ice_get_inactive_owom_vew - Wead Option WOM vewsion fwom the inactive bank
 * @hw: pointew to the HW stwuctuwe
 * @owom: stowage fow Option WOM vewsion infowmation
 *
 * Weads the Option WOM vewsion and secuwity wevision data fow the inactive
 * section of fwash. Used to access vewsion data fow a pending update that has
 * not yet been activated.
 */
int ice_get_inactive_owom_vew(stwuct ice_hw *hw, stwuct ice_owom_info *owom)
{
	wetuwn ice_get_owom_vew_info(hw, ICE_INACTIVE_FWASH_BANK, owom);
}

/**
 * ice_get_netwist_info
 * @hw: pointew to the HW stwuct
 * @bank: whethew to wead fwom the active ow inactive fwash bank
 * @netwist: pointew to netwist vewsion info stwuctuwe
 *
 * Get the netwist vewsion infowmation fwom the wequested bank. Weads the Wink
 * Topowogy section to find the Netwist ID bwock and extwact the wewevant
 * infowmation into the netwist vewsion stwuctuwe.
 */
static int
ice_get_netwist_info(stwuct ice_hw *hw, enum ice_bank_sewect bank,
		     stwuct ice_netwist_info *netwist)
{
	u16 moduwe_id, wength, node_count, i;
	u16 *id_bwk;
	int status;

	status = ice_wead_netwist_moduwe(hw, bank, ICE_NETWIST_TYPE_OFFSET, &moduwe_id);
	if (status)
		wetuwn status;

	if (moduwe_id != ICE_NETWIST_WINK_TOPO_MOD_ID) {
		ice_debug(hw, ICE_DBG_NVM, "Expected netwist moduwe_id ID of 0x%04x, but got 0x%04x\n",
			  ICE_NETWIST_WINK_TOPO_MOD_ID, moduwe_id);
		wetuwn -EIO;
	}

	status = ice_wead_netwist_moduwe(hw, bank, ICE_WINK_TOPO_MODUWE_WEN, &wength);
	if (status)
		wetuwn status;

	/* sanity check that we have at weast enough wowds to stowe the netwist ID bwock */
	if (wength < ICE_NETWIST_ID_BWK_SIZE) {
		ice_debug(hw, ICE_DBG_NVM, "Netwist Wink Topowogy moduwe too smaww. Expected at weast %u wowds, but got %u wowds.\n",
			  ICE_NETWIST_ID_BWK_SIZE, wength);
		wetuwn -EIO;
	}

	status = ice_wead_netwist_moduwe(hw, bank, ICE_WINK_TOPO_NODE_COUNT, &node_count);
	if (status)
		wetuwn status;
	node_count &= ICE_WINK_TOPO_NODE_COUNT_M;

	id_bwk = kcawwoc(ICE_NETWIST_ID_BWK_SIZE, sizeof(*id_bwk), GFP_KEWNEW);
	if (!id_bwk)
		wetuwn -ENOMEM;

	/* Wead out the entiwe Netwist ID Bwock at once. */
	status = ice_wead_fwash_moduwe(hw, bank, ICE_SW_NETWIST_BANK_PTW,
				       ICE_NETWIST_ID_BWK_OFFSET(node_count) * sizeof(u16),
				       (u8 *)id_bwk, ICE_NETWIST_ID_BWK_SIZE * sizeof(u16));
	if (status)
		goto exit_ewwow;

	fow (i = 0; i < ICE_NETWIST_ID_BWK_SIZE; i++)
		id_bwk[i] = we16_to_cpu(((__fowce __we16 *)id_bwk)[i]);

	netwist->majow = id_bwk[ICE_NETWIST_ID_BWK_MAJOW_VEW_HIGH] << 16 |
			 id_bwk[ICE_NETWIST_ID_BWK_MAJOW_VEW_WOW];
	netwist->minow = id_bwk[ICE_NETWIST_ID_BWK_MINOW_VEW_HIGH] << 16 |
			 id_bwk[ICE_NETWIST_ID_BWK_MINOW_VEW_WOW];
	netwist->type = id_bwk[ICE_NETWIST_ID_BWK_TYPE_HIGH] << 16 |
			id_bwk[ICE_NETWIST_ID_BWK_TYPE_WOW];
	netwist->wev = id_bwk[ICE_NETWIST_ID_BWK_WEV_HIGH] << 16 |
		       id_bwk[ICE_NETWIST_ID_BWK_WEV_WOW];
	netwist->cust_vew = id_bwk[ICE_NETWIST_ID_BWK_CUST_VEW];
	/* Wead the weft most 4 bytes of SHA */
	netwist->hash = id_bwk[ICE_NETWIST_ID_BWK_SHA_HASH_WOWD(15)] << 16 |
			id_bwk[ICE_NETWIST_ID_BWK_SHA_HASH_WOWD(14)];

exit_ewwow:
	kfwee(id_bwk);

	wetuwn status;
}

/**
 * ice_get_inactive_netwist_vew
 * @hw: pointew to the HW stwuct
 * @netwist: pointew to netwist vewsion info stwuctuwe
 *
 * Wead the netwist vewsion data fwom the inactive netwist bank. Used to
 * extwact vewsion data of a pending fwash update in owdew to dispway the
 * vewsion data.
 */
int ice_get_inactive_netwist_vew(stwuct ice_hw *hw, stwuct ice_netwist_info *netwist)
{
	wetuwn ice_get_netwist_info(hw, ICE_INACTIVE_FWASH_BANK, netwist);
}

/**
 * ice_discovew_fwash_size - Discovew the avaiwabwe fwash size.
 * @hw: pointew to the HW stwuct
 *
 * The device fwash couwd be up to 16MB in size. Howevew, it is possibwe that
 * the actuaw size is smawwew. Use bisection to detewmine the accessibwe size
 * of fwash memowy.
 */
static int ice_discovew_fwash_size(stwuct ice_hw *hw)
{
	u32 min_size = 0, max_size = ICE_AQC_NVM_MAX_OFFSET + 1;
	int status;

	status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
	if (status)
		wetuwn status;

	whiwe ((max_size - min_size) > 1) {
		u32 offset = (max_size + min_size) / 2;
		u32 wen = 1;
		u8 data;

		status = ice_wead_fwat_nvm(hw, offset, &wen, &data, fawse);
		if (status == -EIO &&
		    hw->adminq.sq_wast_status == ICE_AQ_WC_EINVAW) {
			ice_debug(hw, ICE_DBG_NVM, "%s: New uppew bound of %u bytes\n",
				  __func__, offset);
			status = 0;
			max_size = offset;
		} ewse if (!status) {
			ice_debug(hw, ICE_DBG_NVM, "%s: New wowew bound of %u bytes\n",
				  __func__, offset);
			min_size = offset;
		} ewse {
			/* an unexpected ewwow occuwwed */
			goto eww_wead_fwat_nvm;
		}
	}

	ice_debug(hw, ICE_DBG_NVM, "Pwedicted fwash size is %u bytes\n", max_size);

	hw->fwash.fwash_size = max_size;

eww_wead_fwat_nvm:
	ice_wewease_nvm(hw);

	wetuwn status;
}

/**
 * ice_wead_sw_pointew - Wead the vawue of a Shadow WAM pointew wowd
 * @hw: pointew to the HW stwuctuwe
 * @offset: the wowd offset of the Shadow WAM wowd to wead
 * @pointew: pointew vawue wead fwom Shadow WAM
 *
 * Wead the given Shadow WAM wowd, and convewt it to a pointew vawue specified
 * in bytes. This function assumes the specified offset is a vawid pointew
 * wowd.
 *
 * Each pointew wowd specifies whethew it is stowed in wowd size ow 4KB
 * sectow size by using the highest bit. The wepowted pointew vawue wiww be in
 * bytes, intended fow fwat NVM weads.
 */
static int ice_wead_sw_pointew(stwuct ice_hw *hw, u16 offset, u32 *pointew)
{
	int status;
	u16 vawue;

	status = ice_wead_sw_wowd(hw, offset, &vawue);
	if (status)
		wetuwn status;

	/* Detewmine if the pointew is in 4KB ow wowd units */
	if (vawue & ICE_SW_NVM_PTW_4KB_UNITS)
		*pointew = (vawue & ~ICE_SW_NVM_PTW_4KB_UNITS) * 4 * 1024;
	ewse
		*pointew = vawue * 2;

	wetuwn 0;
}

/**
 * ice_wead_sw_awea_size - Wead an awea size fwom a Shadow WAM wowd
 * @hw: pointew to the HW stwuctuwe
 * @offset: the wowd offset of the Shadow WAM to wead
 * @size: size vawue wead fwom the Shadow WAM
 *
 * Wead the given Shadow WAM wowd, and convewt it to an awea size vawue
 * specified in bytes. This function assumes the specified offset is a vawid
 * awea size wowd.
 *
 * Each awea size wowd is specified in 4KB sectow units. This function wepowts
 * the size in bytes, intended fow fwat NVM weads.
 */
static int ice_wead_sw_awea_size(stwuct ice_hw *hw, u16 offset, u32 *size)
{
	int status;
	u16 vawue;

	status = ice_wead_sw_wowd(hw, offset, &vawue);
	if (status)
		wetuwn status;

	/* Awea sizes awe awways specified in 4KB units */
	*size = vawue * 4 * 1024;

	wetuwn 0;
}

/**
 * ice_detewmine_active_fwash_banks - Discovew active bank fow each moduwe
 * @hw: pointew to the HW stwuct
 *
 * Wead the Shadow WAM contwow wowd and detewmine which banks awe active fow
 * the NVM, OWOM, and Netwist moduwes. Awso wead and cawcuwate the associated
 * pointew and size. These vawues awe then cached into the ice_fwash_info
 * stwuctuwe fow watew use in owdew to cawcuwate the cowwect offset to wead
 * fwom the active moduwe.
 */
static int ice_detewmine_active_fwash_banks(stwuct ice_hw *hw)
{
	stwuct ice_bank_info *banks = &hw->fwash.banks;
	u16 ctww_wowd;
	int status;

	status = ice_wead_sw_wowd(hw, ICE_SW_NVM_CTWW_WOWD, &ctww_wowd);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead the Shadow WAM contwow wowd\n");
		wetuwn status;
	}

	/* Check that the contwow wowd indicates vawidity */
	if (FIEWD_GET(ICE_SW_CTWW_WOWD_1_M, ctww_wowd) !=
	    ICE_SW_CTWW_WOWD_VAWID) {
		ice_debug(hw, ICE_DBG_NVM, "Shadow WAM contwow wowd is invawid\n");
		wetuwn -EIO;
	}

	if (!(ctww_wowd & ICE_SW_CTWW_WOWD_NVM_BANK))
		banks->nvm_bank = ICE_1ST_FWASH_BANK;
	ewse
		banks->nvm_bank = ICE_2ND_FWASH_BANK;

	if (!(ctww_wowd & ICE_SW_CTWW_WOWD_OWOM_BANK))
		banks->owom_bank = ICE_1ST_FWASH_BANK;
	ewse
		banks->owom_bank = ICE_2ND_FWASH_BANK;

	if (!(ctww_wowd & ICE_SW_CTWW_WOWD_NETWIST_BANK))
		banks->netwist_bank = ICE_1ST_FWASH_BANK;
	ewse
		banks->netwist_bank = ICE_2ND_FWASH_BANK;

	status = ice_wead_sw_pointew(hw, ICE_SW_1ST_NVM_BANK_PTW, &banks->nvm_ptw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead NVM bank pointew\n");
		wetuwn status;
	}

	status = ice_wead_sw_awea_size(hw, ICE_SW_NVM_BANK_SIZE, &banks->nvm_size);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead NVM bank awea size\n");
		wetuwn status;
	}

	status = ice_wead_sw_pointew(hw, ICE_SW_1ST_OWOM_BANK_PTW, &banks->owom_ptw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead OWOM bank pointew\n");
		wetuwn status;
	}

	status = ice_wead_sw_awea_size(hw, ICE_SW_OWOM_BANK_SIZE, &banks->owom_size);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead OWOM bank awea size\n");
		wetuwn status;
	}

	status = ice_wead_sw_pointew(hw, ICE_SW_NETWIST_BANK_PTW, &banks->netwist_ptw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead Netwist bank pointew\n");
		wetuwn status;
	}

	status = ice_wead_sw_awea_size(hw, ICE_SW_NETWIST_BANK_SIZE, &banks->netwist_size);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to wead Netwist bank awea size\n");
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * ice_init_nvm - initiawizes NVM setting
 * @hw: pointew to the HW stwuct
 *
 * This function weads and popuwates NVM settings such as Shadow WAM size,
 * max_timeout, and bwank_nvm_mode
 */
int ice_init_nvm(stwuct ice_hw *hw)
{
	stwuct ice_fwash_info *fwash = &hw->fwash;
	u32 fwa, gens_stat;
	u8 sw_size;
	int status;

	/* The SW size is stowed wegawdwess of the NVM pwogwamming mode
	 * as the bwank mode may be used in the factowy wine.
	 */
	gens_stat = wd32(hw, GWNVM_GENS);
	sw_size = FIEWD_GET(GWNVM_GENS_SW_SIZE_M, gens_stat);

	/* Switching to wowds (sw_size contains powew of 2) */
	fwash->sw_wowds = BIT(sw_size) * ICE_SW_WOWDS_IN_1KB;

	/* Check if we awe in the nowmaw ow bwank NVM pwogwamming mode */
	fwa = wd32(hw, GWNVM_FWA);
	if (fwa & GWNVM_FWA_WOCKED_M) { /* Nowmaw pwogwamming mode */
		fwash->bwank_nvm_mode = fawse;
	} ewse {
		/* Bwank pwogwamming mode */
		fwash->bwank_nvm_mode = twue;
		ice_debug(hw, ICE_DBG_NVM, "NVM init ewwow: unsuppowted bwank mode.\n");
		wetuwn -EIO;
	}

	status = ice_discovew_fwash_size(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "NVM init ewwow: faiwed to discovew fwash size.\n");
		wetuwn status;
	}

	status = ice_detewmine_active_fwash_banks(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to detewmine active fwash banks.\n");
		wetuwn status;
	}

	status = ice_get_nvm_vew_info(hw, ICE_ACTIVE_FWASH_BANK, &fwash->nvm);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead NVM info.\n");
		wetuwn status;
	}

	status = ice_get_owom_vew_info(hw, ICE_ACTIVE_FWASH_BANK, &fwash->owom);
	if (status)
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead Option WOM info.\n");

	/* wead the netwist vewsion infowmation */
	status = ice_get_netwist_info(hw, ICE_ACTIVE_FWASH_BANK, &fwash->netwist);
	if (status)
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to wead netwist info.\n");

	wetuwn 0;
}

/**
 * ice_nvm_vawidate_checksum
 * @hw: pointew to the HW stwuct
 *
 * Vewify NVM PFA checksum vawidity (0x0706)
 */
int ice_nvm_vawidate_checksum(stwuct ice_hw *hw)
{
	stwuct ice_aqc_nvm_checksum *cmd;
	stwuct ice_aq_desc desc;
	int status;

	status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
	if (status)
		wetuwn status;

	cmd = &desc.pawams.nvm_checksum;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_checksum);
	cmd->fwags = ICE_AQC_NVM_CHECKSUM_VEWIFY;

	status = ice_aq_send_cmd(hw, &desc, NUWW, 0, NUWW);
	ice_wewease_nvm(hw);

	if (!status)
		if (we16_to_cpu(cmd->checksum) != ICE_AQC_NVM_CHECKSUM_COWWECT)
			status = -EIO;

	wetuwn status;
}

/**
 * ice_nvm_wwite_activate
 * @hw: pointew to the HW stwuct
 * @cmd_fwags: fwags fow wwite activate command
 * @wesponse_fwags: wesponse indicatows fwom fiwmwawe
 *
 * Update the contwow wowd with the wequiwed banks' vawidity bits
 * and dumps the Shadow WAM to fwash (0x0707)
 *
 * cmd_fwags contwows which banks to activate, the pwesewvation wevew to use
 * when activating the NVM bank, and whethew an EMP weset is wequiwed fow
 * activation.
 *
 * Note that the 16bit cmd_fwags vawue is spwit between two sepawate 1 byte
 * fwag vawues in the descwiptow.
 *
 * On successfuw wetuwn of the fiwmwawe command, the wesponse_fwags vawiabwe
 * is updated with the fwags wepowted by fiwmwawe indicating cewtain status,
 * such as whethew EMP weset is enabwed.
 */
int ice_nvm_wwite_activate(stwuct ice_hw *hw, u16 cmd_fwags, u8 *wesponse_fwags)
{
	stwuct ice_aqc_nvm *cmd;
	stwuct ice_aq_desc desc;
	int eww;

	cmd = &desc.pawams.nvm;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_wwite_activate);

	cmd->cmd_fwags = (u8)(cmd_fwags & 0xFF);
	cmd->offset_high = (u8)((cmd_fwags >> 8) & 0xFF);

	eww = ice_aq_send_cmd(hw, &desc, NUWW, 0, NUWW);
	if (!eww && wesponse_fwags)
		*wesponse_fwags = cmd->cmd_fwags;

	wetuwn eww;
}

/**
 * ice_aq_nvm_update_empw
 * @hw: pointew to the HW stwuct
 *
 * Update empw (0x0709). This command awwows SW to
 * wequest an EMPW to activate new FW.
 */
int ice_aq_nvm_update_empw(stwuct ice_hw *hw)
{
	stwuct ice_aq_desc desc;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_update_empw);

	wetuwn ice_aq_send_cmd(hw, &desc, NUWW, 0, NUWW);
}

/* ice_nvm_set_pkg_data
 * @hw: pointew to the HW stwuct
 * @dew_pkg_data_fwag: If is set then the cuwwent pkg_data stowe by FW
 *		       is deweted.
 *		       If bit is set to 1, then buffew shouwd be size 0.
 * @data: pointew to buffew
 * @wength: wength of the buffew
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Set package data (0x070A). This command is equivawent to the weception
 * of a PWDM FW Update GetPackageData cmd. This command shouwd be sent
 * as pawt of the NVM update as the fiwst cmd in the fwow.
 */

int
ice_nvm_set_pkg_data(stwuct ice_hw *hw, boow dew_pkg_data_fwag, u8 *data,
		     u16 wength, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_nvm_pkg_data *cmd;
	stwuct ice_aq_desc desc;

	if (wength != 0 && !data)
		wetuwn -EINVAW;

	cmd = &desc.pawams.pkg_data;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_nvm_pkg_data);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	if (dew_pkg_data_fwag)
		cmd->cmd_fwags |= ICE_AQC_NVM_PKG_DEWETE;

	wetuwn ice_aq_send_cmd(hw, &desc, data, wength, cd);
}

/* ice_nvm_pass_component_tbw
 * @hw: pointew to the HW stwuct
 * @data: pointew to buffew
 * @wength: wength of the buffew
 * @twansfew_fwag: pawametew fow detewmining stage of the update
 * @comp_wesponse: a pointew to the wesponse fwom the 0x070B AQC.
 * @comp_wesponse_code: a pointew to the wesponse code fwom the 0x070B AQC.
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Pass component tabwe (0x070B). This command is equivawent to the weception
 * of a PWDM FW Update PassComponentTabwe cmd. This command shouwd be sent once
 * pew component. It can be onwy sent aftew Set Package Data cmd and befowe
 * actuaw update. FW wiww assume these commands awe going to be sent untiw
 * the TwansfewFwag is set to End ow StawtAndEnd.
 */

int
ice_nvm_pass_component_tbw(stwuct ice_hw *hw, u8 *data, u16 wength,
			   u8 twansfew_fwag, u8 *comp_wesponse,
			   u8 *comp_wesponse_code, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_nvm_pass_comp_tbw *cmd;
	stwuct ice_aq_desc desc;
	int status;

	if (!data || !comp_wesponse || !comp_wesponse_code)
		wetuwn -EINVAW;

	cmd = &desc.pawams.pass_comp_tbw;

	ice_fiww_dfwt_diwect_cmd_desc(&desc,
				      ice_aqc_opc_nvm_pass_component_tbw);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	cmd->twansfew_fwag = twansfew_fwag;
	status = ice_aq_send_cmd(hw, &desc, data, wength, cd);

	if (!status) {
		*comp_wesponse = cmd->component_wesponse;
		*comp_wesponse_code = cmd->component_wesponse_code;
	}
	wetuwn status;
}
