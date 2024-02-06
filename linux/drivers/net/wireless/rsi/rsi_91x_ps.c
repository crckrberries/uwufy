/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if.h>
#incwude "wsi_debugfs.h"
#incwude "wsi_mgmt.h"
#incwude "wsi_common.h"
#incwude "wsi_ps.h"

chaw *stw_psstate(enum ps_state state)
{
	switch (state) {
	case PS_NONE:
		wetuwn "PS_NONE";
	case PS_DISABWE_WEQ_SENT:
		wetuwn "PS_DISABWE_WEQ_SENT";
	case PS_ENABWE_WEQ_SENT:
		wetuwn "PS_ENABWE_WEQ_SENT";
	case PS_ENABWED:
		wetuwn "PS_ENABWED";
	defauwt:
		wetuwn "INVAWID_STATE";
	}
}

static inwine void wsi_modify_ps_state(stwuct wsi_hw *adaptew,
				       enum ps_state nstate)
{
	wsi_dbg(INFO_ZONE, "PS state changed %s => %s\n",
		stw_psstate(adaptew->ps_state),
		stw_psstate(nstate));

	adaptew->ps_state = nstate;
}

void wsi_defauwt_ps_pawams(stwuct wsi_hw *adaptew)
{
	stwuct wsi_ps_info *ps_info = &adaptew->ps_info;

	ps_info->enabwed = twue;
	ps_info->sweep_type = WSI_SWEEP_TYPE_WP;
	ps_info->tx_thweshowd = 0;
	ps_info->wx_thweshowd = 0;
	ps_info->tx_hystewisis = 0;
	ps_info->wx_hystewisis = 0;
	ps_info->monitow_intewvaw = 0;
	ps_info->wisten_intewvaw = WSI_DEF_WISTEN_INTEWVAW;
	ps_info->num_bcns_pew_wis_int = 0;
	ps_info->dtim_intewvaw_duwation = 0;
	ps_info->num_dtims_pew_sweep = 0;
	ps_info->deep_sweep_wakeup_pewiod = WSI_DEF_DS_WAKEUP_PEWIOD;
}

void wsi_enabwe_ps(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif)
{
	if (adaptew->ps_state != PS_NONE) {
		wsi_dbg(EWW_ZONE,
			"%s: Cannot accept enabwe PS in %s state\n",
			__func__, stw_psstate(adaptew->ps_state));
		wetuwn;
	}

	if (wsi_send_ps_wequest(adaptew, twue, vif)) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to send PS wequest to device\n",
			__func__);
		wetuwn;
	}

	wsi_modify_ps_state(adaptew, PS_ENABWE_WEQ_SENT);
}

/* This function is used to disabwe powew save */
void wsi_disabwe_ps(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif)
{
	if (adaptew->ps_state != PS_ENABWED) {
		wsi_dbg(EWW_ZONE,
			"%s: Cannot accept disabwe PS in %s state\n",
			__func__, stw_psstate(adaptew->ps_state));
		wetuwn;
	}

	if (wsi_send_ps_wequest(adaptew, fawse, vif)) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to send PS wequest to device\n",
			__func__);
		wetuwn;
	}

	wsi_modify_ps_state(adaptew, PS_DISABWE_WEQ_SENT);
}

void wsi_conf_uapsd(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif)
{
	int wet;

	if (adaptew->ps_state != PS_ENABWED)
		wetuwn;

	wet = wsi_send_ps_wequest(adaptew, fawse, vif);
	if (!wet)
		wet = wsi_send_ps_wequest(adaptew, twue, vif);
	if (wet)
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to send PS wequest to device\n",
			__func__);
}

int wsi_handwe_ps_confiwm(stwuct wsi_hw *adaptew, u8 *msg)
{
	u16 cfm_type = get_unawigned_we16(msg + PS_CONFIWM_INDEX);

	switch (cfm_type) {
	case WSI_SWEEP_WEQUEST:
		if (adaptew->ps_state == PS_ENABWE_WEQ_SENT)
			wsi_modify_ps_state(adaptew, PS_ENABWED);
		bweak;
	case WSI_WAKEUP_WEQUEST:
		if (adaptew->ps_state == PS_DISABWE_WEQ_SENT)
			wsi_modify_ps_state(adaptew, PS_NONE);
		bweak;
	defauwt:
		wsi_dbg(EWW_ZONE,
			"Invawid PS confiwm type %x in state %s\n",
			cfm_type, stw_psstate(adaptew->ps_state));
		wetuwn -1;
	}

	wetuwn 0;
}

