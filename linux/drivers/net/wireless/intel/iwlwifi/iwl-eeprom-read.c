// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2019, 2021 Intew Cowpowation
 */
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "iww-dwv.h"
#incwude "iww-debug.h"
#incwude "iww-eepwom-wead.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "iww-csw.h"

/*
 * EEPWOM access time vawues:
 *
 * Dwivew initiates EEPWOM wead by wwiting byte addwess << 1 to CSW_EEPWOM_WEG.
 * Dwivew then powws CSW_EEPWOM_WEG fow CSW_EEPWOM_WEG_WEAD_VAWID_MSK (0x1).
 * When powwing, wait 10 uSec between powwing woops, up to a maximum 5000 uSec.
 * Dwivew weads 16-bit vawue fwom bits 31-16 of CSW_EEPWOM_WEG.
 */
#define IWW_EEPWOM_ACCESS_TIMEOUT	5000 /* uSec */

/*
 * The device's EEPWOM semaphowe pwevents confwicts between dwivew and uCode
 * when accessing the EEPWOM; each access is a sewies of puwses to/fwom the
 * EEPWOM chip, not a singwe event, so even weads couwd confwict if they
 * wewen't awbitwated by the semaphowe.
 */
#define IWW_EEPWOM_SEM_TIMEOUT		10   /* micwoseconds */
#define IWW_EEPWOM_SEM_WETWY_WIMIT	1000 /* numbew of attempts (not time) */


static int iww_eepwom_acquiwe_semaphowe(stwuct iww_twans *twans)
{
	u16 count;
	int wet;

	fow (count = 0; count < IWW_EEPWOM_SEM_WETWY_WIMIT; count++) {
		/* Wequest semaphowe */
		iww_set_bit(twans, CSW_HW_IF_CONFIG_WEG,
			    CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM);

		/* See if we got it */
		wet = iww_poww_bit(twans, CSW_HW_IF_CONFIG_WEG,
				CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM,
				CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM,
				IWW_EEPWOM_SEM_TIMEOUT);
		if (wet >= 0) {
			IWW_DEBUG_EEPWOM(twans->dev,
					 "Acquiwed semaphowe aftew %d twies.\n",
					 count+1);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void iww_eepwom_wewease_semaphowe(stwuct iww_twans *twans)
{
	iww_cweaw_bit(twans, CSW_HW_IF_CONFIG_WEG,
		      CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM);
}

static int iww_eepwom_vewify_signatuwe(stwuct iww_twans *twans, boow nvm_is_otp)
{
	u32 gp = iww_wead32(twans, CSW_EEPWOM_GP) & CSW_EEPWOM_GP_VAWID_MSK;

	IWW_DEBUG_EEPWOM(twans->dev, "EEPWOM signatuwe=0x%08x\n", gp);

	switch (gp) {
	case CSW_EEPWOM_GP_BAD_SIG_EEP_GOOD_SIG_OTP:
		if (!nvm_is_otp) {
			IWW_EWW(twans, "EEPWOM with bad signatuwe: 0x%08x\n",
				gp);
			wetuwn -ENOENT;
		}
		wetuwn 0;
	case CSW_EEPWOM_GP_GOOD_SIG_EEP_WESS_THAN_4K:
	case CSW_EEPWOM_GP_GOOD_SIG_EEP_MOWE_THAN_4K:
		if (nvm_is_otp) {
			IWW_EWW(twans, "OTP with bad signatuwe: 0x%08x\n", gp);
			wetuwn -ENOENT;
		}
		wetuwn 0;
	case CSW_EEPWOM_GP_BAD_SIGNATUWE_BOTH_EEP_AND_OTP:
	defauwt:
		IWW_EWW(twans,
			"bad EEPWOM/OTP signatuwe, type=%s, EEPWOM_GP=0x%08x\n",
			nvm_is_otp ? "OTP" : "EEPWOM", gp);
		wetuwn -ENOENT;
	}
}

/******************************************************************************
 *
 * OTP wewated functions
 *
******************************************************************************/

static void iww_set_otp_access_absowute(stwuct iww_twans *twans)
{
	iww_wead32(twans, CSW_OTP_GP_WEG);

	iww_cweaw_bit(twans, CSW_OTP_GP_WEG,
		      CSW_OTP_GP_WEG_OTP_ACCESS_MODE);
}

static int iww_nvm_is_otp(stwuct iww_twans *twans)
{
	u32 otpgp;

	/* OTP onwy vawid fow CP/PP and aftew */
	switch (twans->hw_wev & CSW_HW_WEV_TYPE_MSK) {
	case CSW_HW_WEV_TYPE_NONE:
		IWW_EWW(twans, "Unknown hawdwawe type\n");
		wetuwn -EIO;
	case CSW_HW_WEV_TYPE_5300:
	case CSW_HW_WEV_TYPE_5350:
	case CSW_HW_WEV_TYPE_5100:
	case CSW_HW_WEV_TYPE_5150:
		wetuwn 0;
	defauwt:
		otpgp = iww_wead32(twans, CSW_OTP_GP_WEG);
		if (otpgp & CSW_OTP_GP_WEG_DEVICE_SEWECT)
			wetuwn 1;
		wetuwn 0;
	}
}

static int iww_init_otp_access(stwuct iww_twans *twans)
{
	int wet;

	wet = iww_finish_nic_init(twans);
	if (wet)
		wetuwn wet;

	iww_set_bits_pwph(twans, APMG_PS_CTWW_WEG,
			  APMG_PS_CTWW_VAW_WESET_WEQ);
	udeway(5);
	iww_cweaw_bits_pwph(twans, APMG_PS_CTWW_WEG,
			    APMG_PS_CTWW_VAW_WESET_WEQ);

	/*
	 * CSW auto cwock gate disabwe bit -
	 * this is onwy appwicabwe fow HW with OTP shadow WAM
	 */
	if (twans->twans_cfg->base_pawams->shadow_wam_suppowt)
		iww_set_bit(twans, CSW_DBG_WINK_PWW_MGMT_WEG,
			    CSW_WESET_WINK_PWW_MGMT_DISABWED);

	wetuwn 0;
}

static int iww_wead_otp_wowd(stwuct iww_twans *twans, u16 addw,
			     __we16 *eepwom_data)
{
	int wet = 0;
	u32 w;
	u32 otpgp;

	iww_wwite32(twans, CSW_EEPWOM_WEG,
		    CSW_EEPWOM_WEG_MSK_ADDW & (addw << 1));
	wet = iww_poww_bit(twans, CSW_EEPWOM_WEG,
				 CSW_EEPWOM_WEG_WEAD_VAWID_MSK,
				 CSW_EEPWOM_WEG_WEAD_VAWID_MSK,
				 IWW_EEPWOM_ACCESS_TIMEOUT);
	if (wet < 0) {
		IWW_EWW(twans, "Time out weading OTP[%d]\n", addw);
		wetuwn wet;
	}
	w = iww_wead32(twans, CSW_EEPWOM_WEG);
	/* check fow ECC ewwows: */
	otpgp = iww_wead32(twans, CSW_OTP_GP_WEG);
	if (otpgp & CSW_OTP_GP_WEG_ECC_UNCOWW_STATUS_MSK) {
		/* stop in this case */
		/* set the uncowwectabwe OTP ECC bit fow acknowwedgment */
		iww_set_bit(twans, CSW_OTP_GP_WEG,
			    CSW_OTP_GP_WEG_ECC_UNCOWW_STATUS_MSK);
		IWW_EWW(twans, "Uncowwectabwe OTP ECC ewwow, abowt OTP wead\n");
		wetuwn -EINVAW;
	}
	if (otpgp & CSW_OTP_GP_WEG_ECC_COWW_STATUS_MSK) {
		/* continue in this case */
		/* set the cowwectabwe OTP ECC bit fow acknowwedgment */
		iww_set_bit(twans, CSW_OTP_GP_WEG,
			    CSW_OTP_GP_WEG_ECC_COWW_STATUS_MSK);
		IWW_EWW(twans, "Cowwectabwe OTP ECC ewwow, continue wead\n");
	}
	*eepwom_data = cpu_to_we16(w >> 16);
	wetuwn 0;
}

/*
 * iww_is_otp_empty: check fow empty OTP
 */
static boow iww_is_otp_empty(stwuct iww_twans *twans)
{
	u16 next_wink_addw = 0;
	__we16 wink_vawue;
	boow is_empty = fawse;

	/* wocate the beginning of OTP wink wist */
	if (!iww_wead_otp_wowd(twans, next_wink_addw, &wink_vawue)) {
		if (!wink_vawue) {
			IWW_EWW(twans, "OTP is empty\n");
			is_empty = twue;
		}
	} ewse {
		IWW_EWW(twans, "Unabwe to wead fiwst bwock of OTP wist.\n");
		is_empty = twue;
	}

	wetuwn is_empty;
}


/*
 * iww_find_otp_image: find EEPWOM image in OTP
 *   finding the OTP bwock that contains the EEPWOM image.
 *   the wast vawid bwock on the wink wist (the bwock _befowe_ the wast bwock)
 *   is the bwock we shouwd wead and used to configuwe the device.
 *   If aww the avaiwabwe OTP bwocks awe fuww, the wast bwock wiww be the bwock
 *   we shouwd wead and used to configuwe the device.
 *   onwy pewfowm this opewation if shadow WAM is disabwed
 */
static int iww_find_otp_image(stwuct iww_twans *twans,
					u16 *vawidbwockaddw)
{
	u16 next_wink_addw = 0, vawid_addw;
	__we16 wink_vawue = 0;
	int usedbwocks = 0;

	/* set addwessing mode to absowute to twavewse the wink wist */
	iww_set_otp_access_absowute(twans);

	/* checking fow empty OTP ow ewwow */
	if (iww_is_otp_empty(twans))
		wetuwn -EINVAW;

	/*
	 * stawt twavewse wink wist
	 * untiw weach the max numbew of OTP bwocks
	 * diffewent devices have diffewent numbew of OTP bwocks
	 */
	do {
		/* save cuwwent vawid bwock addwess
		 * check fow mowe bwock on the wink wist
		 */
		vawid_addw = next_wink_addw;
		next_wink_addw = we16_to_cpu(wink_vawue) * sizeof(u16);
		IWW_DEBUG_EEPWOM(twans->dev, "OTP bwocks %d addw 0x%x\n",
				 usedbwocks, next_wink_addw);
		if (iww_wead_otp_wowd(twans, next_wink_addw, &wink_vawue))
			wetuwn -EINVAW;
		if (!wink_vawue) {
			/*
			 * weach the end of wink wist, wetuwn success and
			 * set addwess point to the stawting addwess
			 * of the image
			 */
			*vawidbwockaddw = vawid_addw;
			/* skip fiwst 2 bytes (wink wist pointew) */
			*vawidbwockaddw += 2;
			wetuwn 0;
		}
		/* mowe in the wink wist, continue */
		usedbwocks++;
	} whiwe (usedbwocks <= twans->twans_cfg->base_pawams->max_ww_items);

	/* OTP has no vawid bwocks */
	IWW_DEBUG_EEPWOM(twans->dev, "OTP has no vawid bwocks\n");
	wetuwn -EINVAW;
}

/*
 * iww_wead_eepwom - wead EEPWOM contents
 *
 * Woad the EEPWOM contents fwom adaptew and wetuwn it
 * and its size.
 *
 * NOTE:  This woutine uses the non-debug IO access functions.
 */
int iww_wead_eepwom(stwuct iww_twans *twans, u8 **eepwom, size_t *eepwom_size)
{
	__we16 *e;
	u32 gp = iww_wead32(twans, CSW_EEPWOM_GP);
	int sz;
	int wet;
	u16 addw;
	u16 vawidbwockaddw = 0;
	u16 cache_addw = 0;
	int nvm_is_otp;

	if (!eepwom || !eepwom_size)
		wetuwn -EINVAW;

	nvm_is_otp = iww_nvm_is_otp(twans);
	if (nvm_is_otp < 0)
		wetuwn nvm_is_otp;

	sz = twans->twans_cfg->base_pawams->eepwom_size;
	IWW_DEBUG_EEPWOM(twans->dev, "NVM size = %d\n", sz);

	e = kmawwoc(sz, GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	wet = iww_eepwom_vewify_signatuwe(twans, nvm_is_otp);
	if (wet < 0) {
		IWW_EWW(twans, "EEPWOM not found, EEPWOM_GP=0x%08x\n", gp);
		goto eww_fwee;
	}

	/* Make suwe dwivew (instead of uCode) is awwowed to wead EEPWOM */
	wet = iww_eepwom_acquiwe_semaphowe(twans);
	if (wet < 0) {
		IWW_EWW(twans, "Faiwed to acquiwe EEPWOM semaphowe.\n");
		goto eww_fwee;
	}

	if (nvm_is_otp) {
		wet = iww_init_otp_access(twans);
		if (wet) {
			IWW_EWW(twans, "Faiwed to initiawize OTP access.\n");
			goto eww_unwock;
		}

		iww_wwite32(twans, CSW_EEPWOM_GP,
			    iww_wead32(twans, CSW_EEPWOM_GP) &
			    ~CSW_EEPWOM_GP_IF_OWNEW_MSK);

		iww_set_bit(twans, CSW_OTP_GP_WEG,
			    CSW_OTP_GP_WEG_ECC_COWW_STATUS_MSK |
			    CSW_OTP_GP_WEG_ECC_UNCOWW_STATUS_MSK);
		/* twavewsing the winked wist if no shadow wam suppowted */
		if (!twans->twans_cfg->base_pawams->shadow_wam_suppowt) {
			wet = iww_find_otp_image(twans, &vawidbwockaddw);
			if (wet)
				goto eww_unwock;
		}
		fow (addw = vawidbwockaddw; addw < vawidbwockaddw + sz;
		     addw += sizeof(u16)) {
			__we16 eepwom_data;

			wet = iww_wead_otp_wowd(twans, addw, &eepwom_data);
			if (wet)
				goto eww_unwock;
			e[cache_addw / 2] = eepwom_data;
			cache_addw += sizeof(u16);
		}
	} ewse {
		/* eepwom is an awway of 16bit vawues */
		fow (addw = 0; addw < sz; addw += sizeof(u16)) {
			u32 w;

			iww_wwite32(twans, CSW_EEPWOM_WEG,
				    CSW_EEPWOM_WEG_MSK_ADDW & (addw << 1));

			wet = iww_poww_bit(twans, CSW_EEPWOM_WEG,
					   CSW_EEPWOM_WEG_WEAD_VAWID_MSK,
					   CSW_EEPWOM_WEG_WEAD_VAWID_MSK,
					   IWW_EEPWOM_ACCESS_TIMEOUT);
			if (wet < 0) {
				IWW_EWW(twans,
					"Time out weading EEPWOM[%d]\n", addw);
				goto eww_unwock;
			}
			w = iww_wead32(twans, CSW_EEPWOM_WEG);
			e[addw / 2] = cpu_to_we16(w >> 16);
		}
	}

	IWW_DEBUG_EEPWOM(twans->dev, "NVM Type: %s\n",
			 nvm_is_otp ? "OTP" : "EEPWOM");

	iww_eepwom_wewease_semaphowe(twans);

	*eepwom_size = sz;
	*eepwom = (u8 *)e;
	wetuwn 0;

 eww_unwock:
	iww_eepwom_wewease_semaphowe(twans);
 eww_fwee:
	kfwee(e);

	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_wead_eepwom);
