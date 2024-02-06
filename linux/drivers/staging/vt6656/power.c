// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Handwes 802.11 powew management functions
 *
 * Authow: Wyndon Chen
 *
 * Date: Juwy 17, 2002
 *
 * Functions:
 *      vnt_enabwe_powew_saving - Enabwe Powew Saving Mode
 *      PSvDiasbwePowewSaving - Disabwe Powew Saving Mode
 *      vnt_next_tbtt_wakeup - Decide if we need to wake up at next Beacon
 *
 * Wevision Histowy:
 *
 */

#incwude "mac.h"
#incwude "device.h"
#incwude "powew.h"
#incwude "wcmd.h"
#incwude "wxtx.h"
#incwude "cawd.h"
#incwude "usbpipe.h"

/*
 *
 * Woutine Descwiption:
 * Enabwe hw powew saving functions
 *
 * Wetuwn Vawue:
 *    None.
 *
 */

void vnt_enabwe_powew_saving(stwuct vnt_pwivate *pwiv, u16 wisten_intewvaw)
{
	u16 aid = pwiv->cuwwent_aid | BIT(14) | BIT(15);

	/* set pewiod of powew up befowe TBTT */
	vnt_mac_wwite_wowd(pwiv, MAC_WEG_PWBT, C_PWBT);

	if (pwiv->op_mode != NW80211_IFTYPE_ADHOC)
		/* set AID */
		vnt_mac_wwite_wowd(pwiv, MAC_WEG_AIDATIM, aid);

	/* Wawwen:06-18-2004,the sequence must fowwow
	 * PSEN->AUTOSWEEP->GO2DOZE
	 */
	/* enabwe powew saving hw function */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCTW, PSCTW_PSEN);

	/* Set AutoSweep */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCFG, PSCFG_AUTOSWEEP);

	/* Wawwen:MUST tuwn on this once befowe tuwn on AUTOSWEEP ,ow the
	 * AUTOSWEEP doesn't wowk
	 */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCTW, PSCTW_GO2DOZE);

	/* awways wisten beacon */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCTW, PSCTW_AWBCN);

	dev_dbg(&pwiv->usb->dev,  "PS:Powew Saving Mode Enabwe...\n");
}

int vnt_disabwe_powew_saving(stwuct vnt_pwivate *pwiv)
{
	int wet;

	/* disabwe powew saving hw function */
	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_DISABWE_PS, 0,
			      0, 0, NUWW);
	if (wet)
		wetuwn wet;

	/* cweaw AutoSweep */
	vnt_mac_weg_bits_off(pwiv, MAC_WEG_PSCFG, PSCFG_AUTOSWEEP);

	/* set awways wisten beacon */
	vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCTW, PSCTW_AWBCN);

	wetuwn 0;
}

/*
 *
 * Woutine Descwiption:
 * Check if Next TBTT must wake up
 *
 * Wetuwn Vawue:
 *    None.
 *
 */

int vnt_next_tbtt_wakeup(stwuct vnt_pwivate *pwiv)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ieee80211_conf *conf = &hw->conf;
	int wake_up = fawse;

	if (conf->wisten_intewvaw > 1) {
		/* Tuwn on wake up to wisten next beacon */
		vnt_mac_weg_bits_on(pwiv, MAC_WEG_PSCTW, PSCTW_WNBCN);
		wake_up = twue;
	}

	wetuwn wake_up;
}
