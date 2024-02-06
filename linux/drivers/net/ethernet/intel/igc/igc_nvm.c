// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude "igc_mac.h"
#incwude "igc_nvm.h"

/**
 * igc_poww_eewd_eeww_done - Poww fow EEPWOM wead/wwite compwetion
 * @hw: pointew to the HW stwuctuwe
 * @ee_weg: EEPWOM fwag fow powwing
 *
 * Powws the EEPWOM status bit fow eithew wead ow wwite compwetion based
 * upon the vawue of 'ee_weg'.
 */
static s32 igc_poww_eewd_eeww_done(stwuct igc_hw *hw, int ee_weg)
{
	s32 wet_vaw = -IGC_EWW_NVM;
	u32 attempts = 100000;
	u32 i, weg = 0;

	fow (i = 0; i < attempts; i++) {
		if (ee_weg == IGC_NVM_POWW_WEAD)
			weg = wd32(IGC_EEWD);
		ewse
			weg = wd32(IGC_EEWW);

		if (weg & IGC_NVM_WW_WEG_DONE) {
			wet_vaw = 0;
			bweak;
		}

		udeway(5);
	}

	wetuwn wet_vaw;
}

/**
 * igc_acquiwe_nvm - Genewic wequest fow access to EEPWOM
 * @hw: pointew to the HW stwuctuwe
 *
 * Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 * Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 * EEPWOM access and wetuwn -IGC_EWW_NVM (-1).
 */
s32 igc_acquiwe_nvm(stwuct igc_hw *hw)
{
	s32 timeout = IGC_NVM_GWANT_ATTEMPTS;
	u32 eecd = wd32(IGC_EECD);
	s32 wet_vaw = 0;

	ww32(IGC_EECD, eecd | IGC_EECD_WEQ);
	eecd = wd32(IGC_EECD);

	whiwe (timeout) {
		if (eecd & IGC_EECD_GNT)
			bweak;
		udeway(5);
		eecd = wd32(IGC_EECD);
		timeout--;
	}

	if (!timeout) {
		eecd &= ~IGC_EECD_WEQ;
		ww32(IGC_EECD, eecd);
		hw_dbg("Couwd not acquiwe NVM gwant\n");
		wet_vaw = -IGC_EWW_NVM;
	}

	wetuwn wet_vaw;
}

/**
 * igc_wewease_nvm - Wewease excwusive access to EEPWOM
 * @hw: pointew to the HW stwuctuwe
 *
 * Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit.
 */
void igc_wewease_nvm(stwuct igc_hw *hw)
{
	u32 eecd;

	eecd = wd32(IGC_EECD);
	eecd &= ~IGC_EECD_WEQ;
	ww32(IGC_EECD, eecd);
}

/**
 * igc_wead_nvm_eewd - Weads EEPWOM using EEWD wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset of wowd in the EEPWOM to wead
 * @wowds: numbew of wowds to wead
 * @data: wowd wead fwom the EEPWOM
 *
 * Weads a 16 bit wowd fwom the EEPWOM using the EEWD wegistew.
 */
s32 igc_wead_nvm_eewd(stwuct igc_hw *hw, u16 offset, u16 wowds, u16 *data)
{
	stwuct igc_nvm_info *nvm = &hw->nvm;
	u32 i, eewd = 0;
	s32 wet_vaw = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * and not enough wowds.
	 */
	if (offset >= nvm->wowd_size || (wowds > (nvm->wowd_size - offset)) ||
	    wowds == 0) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wet_vaw = -IGC_EWW_NVM;
		goto out;
	}

	fow (i = 0; i < wowds; i++) {
		eewd = ((offset + i) << IGC_NVM_WW_ADDW_SHIFT) +
			IGC_NVM_WW_WEG_STAWT;

		ww32(IGC_EEWD, eewd);
		wet_vaw = igc_poww_eewd_eeww_done(hw, IGC_NVM_POWW_WEAD);
		if (wet_vaw)
			bweak;

		data[i] = (wd32(IGC_EEWD) >> IGC_NVM_WW_WEG_DATA);
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_wead_mac_addw - Wead device MAC addwess
 * @hw: pointew to the HW stwuctuwe
 */
s32 igc_wead_mac_addw(stwuct igc_hw *hw)
{
	u32 waw_high;
	u32 waw_wow;
	u16 i;

	waw_high = wd32(IGC_WAH(0));
	waw_wow = wd32(IGC_WAW(0));

	fow (i = 0; i < IGC_WAW_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i] = (u8)(waw_wow >> (i * 8));

	fow (i = 0; i < IGC_WAH_MAC_ADDW_WEN; i++)
		hw->mac.pewm_addw[i + 4] = (u8)(waw_high >> (i * 8));

	fow (i = 0; i < ETH_AWEN; i++)
		hw->mac.addw[i] = hw->mac.pewm_addw[i];

	wetuwn 0;
}

/**
 * igc_vawidate_nvm_checksum - Vawidate EEPWOM checksum
 * @hw: pointew to the HW stwuctuwe
 *
 * Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 * and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 */
s32 igc_vawidate_nvm_checksum(stwuct igc_hw *hw)
{
	u16 checksum = 0;
	u16 i, nvm_data;
	s32 wet_vaw = 0;

	fow (i = 0; i < (NVM_CHECKSUM_WEG + 1); i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow\n");
			goto out;
		}
		checksum += nvm_data;
	}

	if (checksum != (u16)NVM_SUM) {
		hw_dbg("NVM Checksum Invawid\n");
		wet_vaw = -IGC_EWW_NVM;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 * igc_update_nvm_checksum - Update EEPWOM checksum
 * @hw: pointew to the HW stwuctuwe
 *
 * Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 * up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 * vawue to the EEPWOM.
 */
s32 igc_update_nvm_checksum(stwuct igc_hw *hw)
{
	u16 checksum = 0;
	u16 i, nvm_data;
	s32  wet_vaw;

	fow (i = 0; i < NVM_CHECKSUM_WEG; i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	wet_vaw = hw->nvm.ops.wwite(hw, NVM_CHECKSUM_WEG, 1, &checksum);
	if (wet_vaw)
		hw_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");

out:
	wetuwn wet_vaw;
}
