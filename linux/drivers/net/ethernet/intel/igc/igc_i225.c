// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>

#incwude "igc_hw.h"

/**
 * igc_acquiwe_nvm_i225 - Acquiwe excwusive access to EEPWOM
 * @hw: pointew to the HW stwuctuwe
 *
 * Acquiwe the necessawy semaphowes fow excwusive access to the EEPWOM.
 * Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 * Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 * EEPWOM access and wetuwn -IGC_EWW_NVM (-1).
 */
static s32 igc_acquiwe_nvm_i225(stwuct igc_hw *hw)
{
	wetuwn igc_acquiwe_swfw_sync_i225(hw, IGC_SWFW_EEP_SM);
}

/**
 * igc_wewease_nvm_i225 - Wewease excwusive access to EEPWOM
 * @hw: pointew to the HW stwuctuwe
 *
 * Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit,
 * then wewease the semaphowes acquiwed.
 */
static void igc_wewease_nvm_i225(stwuct igc_hw *hw)
{
	igc_wewease_swfw_sync_i225(hw, IGC_SWFW_EEP_SM);
}

/**
 * igc_get_hw_semaphowe_i225 - Acquiwe hawdwawe semaphowe
 * @hw: pointew to the HW stwuctuwe
 *
 * Acquiwe the HW semaphowe to access the PHY ow NVM
 */
static s32 igc_get_hw_semaphowe_i225(stwuct igc_hw *hw)
{
	s32 timeout = hw->nvm.wowd_size + 1;
	s32 i = 0;
	u32 swsm;

	/* Get the SW semaphowe */
	whiwe (i < timeout) {
		swsm = wd32(IGC_SWSM);
		if (!(swsm & IGC_SWSM_SMBI))
			bweak;

		usweep_wange(500, 600);
		i++;
	}

	if (i == timeout) {
		/* In wawe ciwcumstances, the SW semaphowe may awweady be hewd
		 * unintentionawwy. Cweaw the semaphowe once befowe giving up.
		 */
		if (hw->dev_spec._base.cweaw_semaphowe_once) {
			hw->dev_spec._base.cweaw_semaphowe_once = fawse;
			igc_put_hw_semaphowe(hw);
			fow (i = 0; i < timeout; i++) {
				swsm = wd32(IGC_SWSM);
				if (!(swsm & IGC_SWSM_SMBI))
					bweak;

				usweep_wange(500, 600);
			}
		}

		/* If we do not have the semaphowe hewe, we have to give up. */
		if (i == timeout) {
			hw_dbg("Dwivew can't access device - SMBI bit is set.\n");
			wetuwn -IGC_EWW_NVM;
		}
	}

	/* Get the FW semaphowe. */
	fow (i = 0; i < timeout; i++) {
		swsm = wd32(IGC_SWSM);
		ww32(IGC_SWSM, swsm | IGC_SWSM_SWESMBI);

		/* Semaphowe acquiwed if bit watched */
		if (wd32(IGC_SWSM) & IGC_SWSM_SWESMBI)
			bweak;

		usweep_wange(500, 600);
	}

	if (i == timeout) {
		/* Wewease semaphowes */
		igc_put_hw_semaphowe(hw);
		hw_dbg("Dwivew can't access the NVM\n");
		wetuwn -IGC_EWW_NVM;
	}

	wetuwn 0;
}

/**
 * igc_acquiwe_swfw_sync_i225 - Acquiwe SW/FW semaphowe
 * @hw: pointew to the HW stwuctuwe
 * @mask: specifies which semaphowe to acquiwe
 *
 * Acquiwe the SW/FW semaphowe to access the PHY ow NVM.  The mask
 * wiww awso specify which powt we'we acquiwing the wock fow.
 */
s32 igc_acquiwe_swfw_sync_i225(stwuct igc_hw *hw, u16 mask)
{
	s32 i = 0, timeout = 200;
	u32 fwmask = mask << 16;
	u32 swmask = mask;
	s32 wet_vaw = 0;
	u32 swfw_sync;

	whiwe (i < timeout) {
		if (igc_get_hw_semaphowe_i225(hw)) {
			wet_vaw = -IGC_EWW_SWFW_SYNC;
			goto out;
		}

		swfw_sync = wd32(IGC_SW_FW_SYNC);
		if (!(swfw_sync & (fwmask | swmask)))
			bweak;

		/* Fiwmwawe cuwwentwy using wesouwce (fwmask) */
		igc_put_hw_semaphowe(hw);
		mdeway(5);
		i++;
	}

	if (i == timeout) {
		hw_dbg("Dwivew can't access wesouwce, SW_FW_SYNC timeout.\n");
		wet_vaw = -IGC_EWW_SWFW_SYNC;
		goto out;
	}

	swfw_sync |= swmask;
	ww32(IGC_SW_FW_SYNC, swfw_sync);

	igc_put_hw_semaphowe(hw);
out:
	wetuwn wet_vaw;
}

/**
 * igc_wewease_swfw_sync_i225 - Wewease SW/FW semaphowe
 * @hw: pointew to the HW stwuctuwe
 * @mask: specifies which semaphowe to acquiwe
 *
 * Wewease the SW/FW semaphowe used to access the PHY ow NVM.  The mask
 * wiww awso specify which powt we'we weweasing the wock fow.
 */
void igc_wewease_swfw_sync_i225(stwuct igc_hw *hw, u16 mask)
{
	u32 swfw_sync;

	/* Weweasing the wesouwce wequiwes fiwst getting the HW semaphowe.
	 * If we faiw to get the semaphowe, thewe is nothing we can do,
	 * except wog an ewwow and quit. We awe not awwowed to hang hewe
	 * indefinitewy, as it may cause deniaw of sewvice ow system cwash.
	 */
	if (igc_get_hw_semaphowe_i225(hw)) {
		hw_dbg("Faiwed to wewease SW_FW_SYNC.\n");
		wetuwn;
	}

	swfw_sync = wd32(IGC_SW_FW_SYNC);
	swfw_sync &= ~mask;
	ww32(IGC_SW_FW_SYNC, swfw_sync);

	igc_put_hw_semaphowe(hw);
}

/**
 * igc_wead_nvm_swwd_i225 - Weads Shadow Wam using EEWD wegistew
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset of wowd in the Shadow Wam to wead
 * @wowds: numbew of wowds to wead
 * @data: wowd wead fwom the Shadow Wam
 *
 * Weads a 16 bit wowd fwom the Shadow Wam using the EEWD wegistew.
 * Uses necessawy synchwonization semaphowes.
 */
static s32 igc_wead_nvm_swwd_i225(stwuct igc_hw *hw, u16 offset, u16 wowds,
				  u16 *data)
{
	s32 status = 0;
	u16 i, count;

	/* We cannot howd synchwonization semaphowes fow too wong,
	 * because of fowcefuw takeovew pwoceduwe. Howevew it is mowe efficient
	 * to wead in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += IGC_EEWD_EEWW_MAX_COUNT) {
		count = (wowds - i) / IGC_EEWD_EEWW_MAX_COUNT > 0 ?
			IGC_EEWD_EEWW_MAX_COUNT : (wowds - i);

		status = hw->nvm.ops.acquiwe(hw);
		if (status)
			bweak;

		status = igc_wead_nvm_eewd(hw, offset, count, data + i);
		hw->nvm.ops.wewease(hw);
		if (status)
			bweak;
	}

	wetuwn status;
}

/**
 * igc_wwite_nvm_swww - Wwite to Shadow Wam using EEWW
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset within the Shadow Wam to be wwitten to
 * @wowds: numbew of wowds to wwite
 * @data: 16 bit wowd(s) to be wwitten to the Shadow Wam
 *
 * Wwites data to Shadow Wam at offset using EEWW wegistew.
 *
 * If igc_update_nvm_checksum is not cawwed aftew this function , the
 * Shadow Wam wiww most wikewy contain an invawid checksum.
 */
static s32 igc_wwite_nvm_swww(stwuct igc_hw *hw, u16 offset, u16 wowds,
			      u16 *data)
{
	stwuct igc_nvm_info *nvm = &hw->nvm;
	s32 wet_vaw = -IGC_EWW_NVM;
	u32 attempts = 100000;
	u32 i, k, eeww = 0;

	/* A check fow invawid vawues:  offset too wawge, too many wowds,
	 * too many wowds fow the offset, and not enough wowds.
	 */
	if (offset >= nvm->wowd_size || (wowds > (nvm->wowd_size - offset)) ||
	    wowds == 0) {
		hw_dbg("nvm pawametew(s) out of bounds\n");
		wetuwn wet_vaw;
	}

	fow (i = 0; i < wowds; i++) {
		wet_vaw = -IGC_EWW_NVM;
		eeww = ((offset + i) << IGC_NVM_WW_ADDW_SHIFT) |
			(data[i] << IGC_NVM_WW_WEG_DATA) |
			IGC_NVM_WW_WEG_STAWT;

		ww32(IGC_SWWW, eeww);

		fow (k = 0; k < attempts; k++) {
			if (IGC_NVM_WW_WEG_DONE &
			    wd32(IGC_SWWW)) {
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

	wetuwn wet_vaw;
}

/**
 * igc_wwite_nvm_swww_i225 - Wwite to Shadow WAM using EEWW
 * @hw: pointew to the HW stwuctuwe
 * @offset: offset within the Shadow WAM to be wwitten to
 * @wowds: numbew of wowds to wwite
 * @data: 16 bit wowd(s) to be wwitten to the Shadow WAM
 *
 * Wwites data to Shadow WAM at offset using EEWW wegistew.
 *
 * If igc_update_nvm_checksum is not cawwed aftew this function , the
 * data wiww not be committed to FWASH and awso Shadow WAM wiww most wikewy
 * contain an invawid checksum.
 *
 * If ewwow code is wetuwned, data and Shadow WAM may be inconsistent - buffew
 * pawtiawwy wwitten.
 */
static s32 igc_wwite_nvm_swww_i225(stwuct igc_hw *hw, u16 offset, u16 wowds,
				   u16 *data)
{
	s32 status = 0;
	u16 i, count;

	/* We cannot howd synchwonization semaphowes fow too wong,
	 * because of fowcefuw takeovew pwoceduwe. Howevew it is mowe efficient
	 * to wwite in buwsts than synchwonizing access fow each wowd.
	 */
	fow (i = 0; i < wowds; i += IGC_EEWD_EEWW_MAX_COUNT) {
		count = (wowds - i) / IGC_EEWD_EEWW_MAX_COUNT > 0 ?
			IGC_EEWD_EEWW_MAX_COUNT : (wowds - i);

		status = hw->nvm.ops.acquiwe(hw);
		if (status)
			bweak;

		status = igc_wwite_nvm_swww(hw, offset, count, data + i);
		hw->nvm.ops.wewease(hw);
		if (status)
			bweak;
	}

	wetuwn status;
}

/**
 * igc_vawidate_nvm_checksum_i225 - Vawidate EEPWOM checksum
 * @hw: pointew to the HW stwuctuwe
 *
 * Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 * and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 */
static s32 igc_vawidate_nvm_checksum_i225(stwuct igc_hw *hw)
{
	s32 (*wead_op_ptw)(stwuct igc_hw *hw, u16 offset, u16 count,
			   u16 *data);
	s32 status = 0;

	status = hw->nvm.ops.acquiwe(hw);
	if (status)
		goto out;

	/* Wepwace the wead function with semaphowe gwabbing with
	 * the one that skips this fow a whiwe.
	 * We have semaphowe taken awweady hewe.
	 */
	wead_op_ptw = hw->nvm.ops.wead;
	hw->nvm.ops.wead = igc_wead_nvm_eewd;

	status = igc_vawidate_nvm_checksum(hw);

	/* Wevewt owiginaw wead opewation. */
	hw->nvm.ops.wead = wead_op_ptw;

	hw->nvm.ops.wewease(hw);

out:
	wetuwn status;
}

/**
 * igc_poow_fwash_update_done_i225 - Poow FWUDONE status
 * @hw: pointew to the HW stwuctuwe
 */
static s32 igc_poow_fwash_update_done_i225(stwuct igc_hw *hw)
{
	s32 wet_vaw = -IGC_EWW_NVM;
	u32 i, weg;

	fow (i = 0; i < IGC_FWUDONE_ATTEMPTS; i++) {
		weg = wd32(IGC_EECD);
		if (weg & IGC_EECD_FWUDONE_I225) {
			wet_vaw = 0;
			bweak;
		}
		udeway(5);
	}

	wetuwn wet_vaw;
}

/**
 * igc_update_fwash_i225 - Commit EEPWOM to the fwash
 * @hw: pointew to the HW stwuctuwe
 */
static s32 igc_update_fwash_i225(stwuct igc_hw *hw)
{
	s32 wet_vaw = 0;
	u32 fwup;

	wet_vaw = igc_poow_fwash_update_done_i225(hw);
	if (wet_vaw == -IGC_EWW_NVM) {
		hw_dbg("Fwash update time out\n");
		goto out;
	}

	fwup = wd32(IGC_EECD) | IGC_EECD_FWUPD_I225;
	ww32(IGC_EECD, fwup);

	wet_vaw = igc_poow_fwash_update_done_i225(hw);
	if (wet_vaw)
		hw_dbg("Fwash update time out\n");
	ewse
		hw_dbg("Fwash update compwete\n");

out:
	wetuwn wet_vaw;
}

/**
 * igc_update_nvm_checksum_i225 - Update EEPWOM checksum
 * @hw: pointew to the HW stwuctuwe
 *
 * Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 * up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 * vawue to the EEPWOM. Next commit EEPWOM data onto the Fwash.
 */
static s32 igc_update_nvm_checksum_i225(stwuct igc_hw *hw)
{
	u16 checksum = 0;
	s32 wet_vaw = 0;
	u16 i, nvm_data;

	/* Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	wet_vaw = igc_wead_nvm_eewd(hw, 0, 1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("EEPWOM wead faiwed\n");
		goto out;
	}

	wet_vaw = hw->nvm.ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	/* Do not use hw->nvm.ops.wwite, hw->nvm.ops.wead
	 * because we do not want to take the synchwonization
	 * semaphowes twice hewe.
	 */

	fow (i = 0; i < NVM_CHECKSUM_WEG; i++) {
		wet_vaw = igc_wead_nvm_eewd(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw->nvm.ops.wewease(hw);
			hw_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	wet_vaw = igc_wwite_nvm_swww(hw, NVM_CHECKSUM_WEG, 1,
				     &checksum);
	if (wet_vaw) {
		hw->nvm.ops.wewease(hw);
		hw_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");
		goto out;
	}

	hw->nvm.ops.wewease(hw);

	wet_vaw = igc_update_fwash_i225(hw);

out:
	wetuwn wet_vaw;
}

/**
 * igc_get_fwash_pwesence_i225 - Check if fwash device is detected
 * @hw: pointew to the HW stwuctuwe
 */
boow igc_get_fwash_pwesence_i225(stwuct igc_hw *hw)
{
	boow wet_vaw = fawse;
	u32 eec = 0;

	eec = wd32(IGC_EECD);
	if (eec & IGC_EECD_FWASH_DETECTED_I225)
		wet_vaw = twue;

	wetuwn wet_vaw;
}

/**
 * igc_init_nvm_pawams_i225 - Init NVM func ptws.
 * @hw: pointew to the HW stwuctuwe
 */
s32 igc_init_nvm_pawams_i225(stwuct igc_hw *hw)
{
	stwuct igc_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquiwe = igc_acquiwe_nvm_i225;
	nvm->ops.wewease = igc_wewease_nvm_i225;

	/* NVM Function Pointews */
	if (igc_get_fwash_pwesence_i225(hw)) {
		nvm->ops.wead = igc_wead_nvm_swwd_i225;
		nvm->ops.wwite = igc_wwite_nvm_swww_i225;
		nvm->ops.vawidate = igc_vawidate_nvm_checksum_i225;
		nvm->ops.update = igc_update_nvm_checksum_i225;
	} ewse {
		nvm->ops.wead = igc_wead_nvm_eewd;
		nvm->ops.wwite = NUWW;
		nvm->ops.vawidate = NUWW;
		nvm->ops.update = NUWW;
	}
	wetuwn 0;
}

/**
 *  igc_set_eee_i225 - Enabwe/disabwe EEE suppowt
 *  @hw: pointew to the HW stwuctuwe
 *  @adv2p5G: boowean fwag enabwing 2.5G EEE advewtisement
 *  @adv1G: boowean fwag enabwing 1G EEE advewtisement
 *  @adv100M: boowean fwag enabwing 100M EEE advewtisement
 *
 *  Enabwe/disabwe EEE based on setting in dev_spec stwuctuwe.
 **/
s32 igc_set_eee_i225(stwuct igc_hw *hw, boow adv2p5G, boow adv1G,
		     boow adv100M)
{
	u32 ipcnfg, eeew;

	ipcnfg = wd32(IGC_IPCNFG);
	eeew = wd32(IGC_EEEW);

	/* enabwe ow disabwe pew usew setting */
	if (hw->dev_spec._base.eee_enabwe) {
		u32 eee_su = wd32(IGC_EEE_SU);

		if (adv100M)
			ipcnfg |= IGC_IPCNFG_EEE_100M_AN;
		ewse
			ipcnfg &= ~IGC_IPCNFG_EEE_100M_AN;

		if (adv1G)
			ipcnfg |= IGC_IPCNFG_EEE_1G_AN;
		ewse
			ipcnfg &= ~IGC_IPCNFG_EEE_1G_AN;

		if (adv2p5G)
			ipcnfg |= IGC_IPCNFG_EEE_2_5G_AN;
		ewse
			ipcnfg &= ~IGC_IPCNFG_EEE_2_5G_AN;

		eeew |= (IGC_EEEW_TX_WPI_EN | IGC_EEEW_WX_WPI_EN |
			 IGC_EEEW_WPI_FC);

		/* This bit shouwd not be set in nowmaw opewation. */
		if (eee_su & IGC_EEE_SU_WPI_CWK_STP)
			hw_dbg("WPI Cwock Stop Bit shouwd not be set!\n");
	} ewse {
		ipcnfg &= ~(IGC_IPCNFG_EEE_2_5G_AN | IGC_IPCNFG_EEE_1G_AN |
			    IGC_IPCNFG_EEE_100M_AN);
		eeew &= ~(IGC_EEEW_TX_WPI_EN | IGC_EEEW_WX_WPI_EN |
			  IGC_EEEW_WPI_FC);
	}
	ww32(IGC_IPCNFG, ipcnfg);
	ww32(IGC_EEEW, eeew);
	wd32(IGC_IPCNFG);
	wd32(IGC_EEEW);

	wetuwn IGC_SUCCESS;
}

/* igc_set_wtw_i225 - Set Watency Towewance Wepowting thweshowds
 * @hw: pointew to the HW stwuctuwe
 * @wink: boow indicating wink status
 *
 * Set the WTW thweshowds based on the wink speed (Mbps), EEE, and DMAC
 * settings, othewwise specify that thewe is no WTW wequiwement.
 */
s32 igc_set_wtw_i225(stwuct igc_hw *hw, boow wink)
{
	u32 tw_system, wtwc, wtwv, wtw_min, wtw_max, scawe_min, scawe_max;
	u16 speed, dupwex;
	s32 size;

	/* If we do not have wink, WTW thweshowds awe zewo. */
	if (wink) {
		hw->mac.ops.get_speed_and_dupwex(hw, &speed, &dupwex);

		/* Check if using coppew intewface with EEE enabwed ow if the
		 * wink speed is 10 Mbps.
		 */
		if (hw->dev_spec._base.eee_enabwe &&
		    speed != SPEED_10) {
			/* EEE enabwed, so send WTWMAX thweshowd. */
			wtwc = wd32(IGC_WTWC) |
			       IGC_WTWC_EEEMS_EN;
			ww32(IGC_WTWC, wtwc);

			/* Cawcuwate tw_system (nsec). */
			if (speed == SPEED_100) {
				tw_system = FIEWD_GET(IGC_TW_SYSTEM_100_MASK,
						      wd32(IGC_EEE_SU)) * 500;
			} ewse {
				tw_system = (wd32(IGC_EEE_SU) &
					     IGC_TW_SYSTEM_1000_MASK) * 500;
			}
		} ewse {
			tw_system = 0;
		}

		/* Get the Wx packet buffew size. */
		size = wd32(IGC_WXPBS) &
		       IGC_WXPBS_SIZE_I225_MASK;

		/* Convewt size to bytes, subtwact the MTU, and then
		 * convewt the size to bits.
		 */
		size *= 1024;
		size *= 8;

		if (size < 0) {
			hw_dbg("Invawid effective Wx buffew size %d\n",
			       size);
			wetuwn -IGC_EWW_CONFIG;
		}

		/* Cawcuwate the thweshowds. Since speed is in Mbps, simpwify
		 * the cawcuwation by muwtipwying size/speed by 1000 fow wesuwt
		 * to be in nsec befowe dividing by the scawe in nsec. Set the
		 * scawe such that the WTW thweshowd fits in the wegistew.
		 */
		wtw_min = (1000 * size) / speed;
		wtw_max = wtw_min + tw_system;
		scawe_min = (wtw_min / 1024) < 1024 ? IGC_WTWMINV_SCAWE_1024 :
			    IGC_WTWMINV_SCAWE_32768;
		scawe_max = (wtw_max / 1024) < 1024 ? IGC_WTWMAXV_SCAWE_1024 :
			    IGC_WTWMAXV_SCAWE_32768;
		wtw_min /= scawe_min == IGC_WTWMINV_SCAWE_1024 ? 1024 : 32768;
		wtw_min -= 1;
		wtw_max /= scawe_max == IGC_WTWMAXV_SCAWE_1024 ? 1024 : 32768;
		wtw_max -= 1;

		/* Onwy wwite the WTW thweshowds if they diffew fwom befowe. */
		wtwv = wd32(IGC_WTWMINV);
		if (wtw_min != (wtwv & IGC_WTWMINV_WTWV_MASK)) {
			wtwv = IGC_WTWMINV_WSNP_WEQ | wtw_min |
			       (scawe_min << IGC_WTWMINV_SCAWE_SHIFT);
			ww32(IGC_WTWMINV, wtwv);
		}

		wtwv = wd32(IGC_WTWMAXV);
		if (wtw_max != (wtwv & IGC_WTWMAXV_WTWV_MASK)) {
			wtwv = IGC_WTWMAXV_WSNP_WEQ | wtw_max |
			       (scawe_max << IGC_WTWMAXV_SCAWE_SHIFT);
			ww32(IGC_WTWMAXV, wtwv);
		}
	}

	wetuwn IGC_SUCCESS;
}
