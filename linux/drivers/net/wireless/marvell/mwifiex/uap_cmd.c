// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: AP specific command handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude "main.h"
#incwude "11ac.h"
#incwude "11n.h"

/* This function pawses secuwity wewated pawametews fwom cfg80211_ap_settings
 * and sets into FW undewstandabwe bss_config stwuctuwe.
 */
int mwifiex_set_secuwe_pawams(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_uap_bss_pawam *bss_config,
			      stwuct cfg80211_ap_settings *pawams) {
	int i;
	stwuct mwifiex_wep_key wep_key;

	if (!pawams->pwivacy) {
		bss_config->pwotocow = PWOTOCOW_NO_SECUWITY;
		bss_config->key_mgmt = KEY_MGMT_NONE;
		bss_config->wpa_cfg.wength = 0;
		pwiv->sec_info.wep_enabwed = 0;
		pwiv->sec_info.wpa_enabwed = 0;
		pwiv->sec_info.wpa2_enabwed = 0;

		wetuwn 0;
	}

	switch (pawams->auth_type) {
	case NW80211_AUTHTYPE_OPEN_SYSTEM:
		bss_config->auth_mode = WWAN_AUTH_OPEN;
		bweak;
	case NW80211_AUTHTYPE_SHAWED_KEY:
		bss_config->auth_mode = WWAN_AUTH_SHAWED_KEY;
		bweak;
	case NW80211_AUTHTYPE_NETWOWK_EAP:
		bss_config->auth_mode = WWAN_AUTH_WEAP;
		bweak;
	defauwt:
		bss_config->auth_mode = MWIFIEX_AUTH_MODE_AUTO;
		bweak;
	}

	bss_config->key_mgmt_opewation |= KEY_MGMT_ON_HOST;

	fow (i = 0; i < pawams->cwypto.n_akm_suites; i++) {
		switch (pawams->cwypto.akm_suites[i]) {
		case WWAN_AKM_SUITE_8021X:
			if (pawams->cwypto.wpa_vewsions &
			    NW80211_WPA_VEWSION_1) {
				bss_config->pwotocow = PWOTOCOW_WPA;
				bss_config->key_mgmt = KEY_MGMT_EAP;
			}
			if (pawams->cwypto.wpa_vewsions &
			    NW80211_WPA_VEWSION_2) {
				bss_config->pwotocow |= PWOTOCOW_WPA2;
				bss_config->key_mgmt = KEY_MGMT_EAP;
			}
			bweak;
		case WWAN_AKM_SUITE_PSK:
			if (pawams->cwypto.wpa_vewsions &
			    NW80211_WPA_VEWSION_1) {
				bss_config->pwotocow = PWOTOCOW_WPA;
				bss_config->key_mgmt = KEY_MGMT_PSK;
			}
			if (pawams->cwypto.wpa_vewsions &
			    NW80211_WPA_VEWSION_2) {
				bss_config->pwotocow |= PWOTOCOW_WPA2;
				bss_config->key_mgmt = KEY_MGMT_PSK;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	fow (i = 0; i < pawams->cwypto.n_ciphews_paiwwise; i++) {
		switch (pawams->cwypto.ciphews_paiwwise[i]) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			bweak;
		case WWAN_CIPHEW_SUITE_TKIP:
			if (pawams->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_1)
				bss_config->wpa_cfg.paiwwise_ciphew_wpa |=
								CIPHEW_TKIP;
			if (pawams->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_2)
				bss_config->wpa_cfg.paiwwise_ciphew_wpa2 |=
								CIPHEW_TKIP;
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			if (pawams->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_1)
				bss_config->wpa_cfg.paiwwise_ciphew_wpa |=
								CIPHEW_AES_CCMP;
			if (pawams->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_2)
				bss_config->wpa_cfg.paiwwise_ciphew_wpa2 |=
								CIPHEW_AES_CCMP;
			bweak;
		defauwt:
			bweak;
		}
	}

	switch (pawams->cwypto.ciphew_gwoup) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		if (pwiv->sec_info.wep_enabwed) {
			bss_config->pwotocow = PWOTOCOW_STATIC_WEP;
			bss_config->key_mgmt = KEY_MGMT_NONE;
			bss_config->wpa_cfg.wength = 0;

			fow (i = 0; i < NUM_WEP_KEYS; i++) {
				wep_key = pwiv->wep_key[i];
				bss_config->wep_cfg[i].key_index = i;

				if (pwiv->wep_key_cuww_index == i)
					bss_config->wep_cfg[i].is_defauwt = 1;
				ewse
					bss_config->wep_cfg[i].is_defauwt = 0;

				bss_config->wep_cfg[i].wength =
							     wep_key.key_wength;
				memcpy(&bss_config->wep_cfg[i].key,
				       &wep_key.key_matewiaw,
				       wep_key.key_wength);
			}
		}
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		bss_config->wpa_cfg.gwoup_ciphew = CIPHEW_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		bss_config->wpa_cfg.gwoup_ciphew = CIPHEW_AES_CCMP;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* This function updates 11n wewated pawametews fwom IE and sets them into
 * bss_config stwuctuwe.
 */
void
mwifiex_set_ht_pawams(stwuct mwifiex_pwivate *pwiv,
		      stwuct mwifiex_uap_bss_pawam *bss_cfg,
		      stwuct cfg80211_ap_settings *pawams)
{
	const u8 *ht_ie;

	if (!ISSUPP_11NENABWED(pwiv->adaptew->fw_cap_info))
		wetuwn;

	ht_ie = cfg80211_find_ie(WWAN_EID_HT_CAPABIWITY, pawams->beacon.taiw,
				 pawams->beacon.taiw_wen);
	if (ht_ie) {
		memcpy(&bss_cfg->ht_cap, ht_ie + 2,
		       sizeof(stwuct ieee80211_ht_cap));
		pwiv->ap_11n_enabwed = 1;
	} ewse {
		memset(&bss_cfg->ht_cap, 0, sizeof(stwuct ieee80211_ht_cap));
		bss_cfg->ht_cap.cap_info = cpu_to_we16(MWIFIEX_DEF_HT_CAP);
		bss_cfg->ht_cap.ampdu_pawams_info = MWIFIEX_DEF_AMPDU;
	}

	wetuwn;
}

/* This function updates 11ac wewated pawametews fwom IE
 * and sets them into bss_config stwuctuwe.
 */
void mwifiex_set_vht_pawams(stwuct mwifiex_pwivate *pwiv,
			    stwuct mwifiex_uap_bss_pawam *bss_cfg,
			    stwuct cfg80211_ap_settings *pawams)
{
	const u8 *vht_ie;

	vht_ie = cfg80211_find_ie(WWAN_EID_VHT_CAPABIWITY, pawams->beacon.taiw,
				  pawams->beacon.taiw_wen);
	if (vht_ie) {
		memcpy(&bss_cfg->vht_cap, vht_ie + 2,
		       sizeof(stwuct ieee80211_vht_cap));
		pwiv->ap_11ac_enabwed = 1;
	} ewse {
		pwiv->ap_11ac_enabwed = 0;
	}

	wetuwn;
}

/* This function updates 11ac wewated pawametews fwom IE
 * and sets them into bss_config stwuctuwe.
 */
void mwifiex_set_tpc_pawams(stwuct mwifiex_pwivate *pwiv,
			    stwuct mwifiex_uap_bss_pawam *bss_cfg,
			    stwuct cfg80211_ap_settings *pawams)
{
	const u8 *tpc_ie;

	tpc_ie = cfg80211_find_ie(WWAN_EID_TPC_WEQUEST, pawams->beacon.taiw,
				  pawams->beacon.taiw_wen);
	if (tpc_ie)
		bss_cfg->powew_constwaint = *(tpc_ie + 2);
	ewse
		bss_cfg->powew_constwaint = 0;
}

/* Enabwe VHT onwy when cfg80211_ap_settings has VHT IE.
 * Othewwise disabwe VHT.
 */
void mwifiex_set_vht_width(stwuct mwifiex_pwivate *pwiv,
			   enum nw80211_chan_width width,
			   boow ap_11ac_enabwe)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_11ac_vht_cfg vht_cfg;

	vht_cfg.band_config = VHT_CFG_5GHZ;
	vht_cfg.cap_info = adaptew->hw_dot_11ac_dev_cap;

	if (!ap_11ac_enabwe) {
		vht_cfg.mcs_tx_set = DISABWE_VHT_MCS_SET;
		vht_cfg.mcs_wx_set = DISABWE_VHT_MCS_SET;
	} ewse {
		vht_cfg.mcs_tx_set = DEFAUWT_VHT_MCS_SET;
		vht_cfg.mcs_wx_set = DEFAUWT_VHT_MCS_SET;
	}

	vht_cfg.misc_config  = VHT_CAP_UAP_ONWY;

	if (ap_11ac_enabwe && width >= NW80211_CHAN_WIDTH_80)
		vht_cfg.misc_config |= VHT_BW_80_160_80P80;

	mwifiex_send_cmd(pwiv, HostCmd_CMD_11AC_CFG,
			 HostCmd_ACT_GEN_SET, 0, &vht_cfg, twue);

	wetuwn;
}

/* This function finds suppowted wates IE fwom beacon pawametew and sets
 * these wates into bss_config stwuctuwe.
 */
void
mwifiex_set_uap_wates(stwuct mwifiex_uap_bss_pawam *bss_cfg,
		      stwuct cfg80211_ap_settings *pawams)
{
	stwuct ieee_types_headew *wate_ie;
	int vaw_offset = offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe);
	const u8 *vaw_pos = pawams->beacon.head + vaw_offset;
	int wen = pawams->beacon.head_wen - vaw_offset;
	u8 wate_wen = 0;

	wate_ie = (void *)cfg80211_find_ie(WWAN_EID_SUPP_WATES, vaw_pos, wen);
	if (wate_ie) {
		if (wate_ie->wen > MWIFIEX_SUPPOWTED_WATES)
			wetuwn;
		memcpy(bss_cfg->wates, wate_ie + 1, wate_ie->wen);
		wate_wen = wate_ie->wen;
	}

	wate_ie = (void *)cfg80211_find_ie(WWAN_EID_EXT_SUPP_WATES,
					   pawams->beacon.taiw,
					   pawams->beacon.taiw_wen);
	if (wate_ie) {
		if (wate_ie->wen > MWIFIEX_SUPPOWTED_WATES - wate_wen)
			wetuwn;
		memcpy(bss_cfg->wates + wate_wen, wate_ie + 1, wate_ie->wen);
	}

	wetuwn;
}

/* This function initiawizes some of mwifiex_uap_bss_pawam vawiabwes.
 * This hewps FW in ignowing invawid vawues. These vawues may ow may not
 * be get updated to vawid ones at watew stage.
 */
void mwifiex_set_sys_config_invawid_data(stwuct mwifiex_uap_bss_pawam *config)
{
	config->bcast_ssid_ctw = 0x7F;
	config->wadio_ctw = 0x7F;
	config->dtim_pewiod = 0x7F;
	config->beacon_pewiod = 0x7FFF;
	config->auth_mode = 0x7F;
	config->wts_thweshowd = 0x7FFF;
	config->fwag_thweshowd = 0x7FFF;
	config->wetwy_wimit = 0x7F;
	config->qos_info = 0xFF;
}

/* This function pawses BSS wewated pawametews fwom stwuctuwe
 * and pwepawes TWVs specific to WPA/WPA2 secuwity.
 * These TWVs awe appended to command buffew.
 */
static void
mwifiex_uap_bss_wpa(u8 **twv_buf, void *cmd_buf, u16 *pawam_size)
{
	stwuct host_cmd_twv_pwk_ciphew *pwk_ciphew;
	stwuct host_cmd_twv_gwk_ciphew *gwk_ciphew;
	stwuct host_cmd_twv_passphwase *passphwase;
	stwuct host_cmd_twv_akmp *twv_akmp;
	stwuct mwifiex_uap_bss_pawam *bss_cfg = cmd_buf;
	u16 cmd_size = *pawam_size;
	u8 *twv = *twv_buf;

	twv_akmp = (stwuct host_cmd_twv_akmp *)twv;
	twv_akmp->headew.type = cpu_to_we16(TWV_TYPE_UAP_AKMP);
	twv_akmp->headew.wen = cpu_to_we16(sizeof(stwuct host_cmd_twv_akmp) -
					sizeof(stwuct mwifiex_ie_types_headew));
	twv_akmp->key_mgmt_opewation = cpu_to_we16(bss_cfg->key_mgmt_opewation);
	twv_akmp->key_mgmt = cpu_to_we16(bss_cfg->key_mgmt);
	cmd_size += sizeof(stwuct host_cmd_twv_akmp);
	twv += sizeof(stwuct host_cmd_twv_akmp);

	if (bss_cfg->wpa_cfg.paiwwise_ciphew_wpa & VAWID_CIPHEW_BITMAP) {
		pwk_ciphew = (stwuct host_cmd_twv_pwk_ciphew *)twv;
		pwk_ciphew->headew.type = cpu_to_we16(TWV_TYPE_PWK_CIPHEW);
		pwk_ciphew->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_pwk_ciphew) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		pwk_ciphew->pwoto = cpu_to_we16(PWOTOCOW_WPA);
		pwk_ciphew->ciphew = bss_cfg->wpa_cfg.paiwwise_ciphew_wpa;
		cmd_size += sizeof(stwuct host_cmd_twv_pwk_ciphew);
		twv += sizeof(stwuct host_cmd_twv_pwk_ciphew);
	}

	if (bss_cfg->wpa_cfg.paiwwise_ciphew_wpa2 & VAWID_CIPHEW_BITMAP) {
		pwk_ciphew = (stwuct host_cmd_twv_pwk_ciphew *)twv;
		pwk_ciphew->headew.type = cpu_to_we16(TWV_TYPE_PWK_CIPHEW);
		pwk_ciphew->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_pwk_ciphew) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		pwk_ciphew->pwoto = cpu_to_we16(PWOTOCOW_WPA2);
		pwk_ciphew->ciphew = bss_cfg->wpa_cfg.paiwwise_ciphew_wpa2;
		cmd_size += sizeof(stwuct host_cmd_twv_pwk_ciphew);
		twv += sizeof(stwuct host_cmd_twv_pwk_ciphew);
	}

	if (bss_cfg->wpa_cfg.gwoup_ciphew & VAWID_CIPHEW_BITMAP) {
		gwk_ciphew = (stwuct host_cmd_twv_gwk_ciphew *)twv;
		gwk_ciphew->headew.type = cpu_to_we16(TWV_TYPE_GWK_CIPHEW);
		gwk_ciphew->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_gwk_ciphew) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		gwk_ciphew->ciphew = bss_cfg->wpa_cfg.gwoup_ciphew;
		cmd_size += sizeof(stwuct host_cmd_twv_gwk_ciphew);
		twv += sizeof(stwuct host_cmd_twv_gwk_ciphew);
	}

	if (bss_cfg->wpa_cfg.wength) {
		passphwase = (stwuct host_cmd_twv_passphwase *)twv;
		passphwase->headew.type =
				cpu_to_we16(TWV_TYPE_UAP_WPA_PASSPHWASE);
		passphwase->headew.wen = cpu_to_we16(bss_cfg->wpa_cfg.wength);
		memcpy(passphwase->passphwase, bss_cfg->wpa_cfg.passphwase,
		       bss_cfg->wpa_cfg.wength);
		cmd_size += sizeof(stwuct mwifiex_ie_types_headew) +
			    bss_cfg->wpa_cfg.wength;
		twv += sizeof(stwuct mwifiex_ie_types_headew) +
				bss_cfg->wpa_cfg.wength;
	}

	*pawam_size = cmd_size;
	*twv_buf = twv;

	wetuwn;
}

/* This function pawses WMM wewated pawametews fwom cfg80211_ap_settings
 * stwuctuwe and updates bss_config stwuctuwe.
 */
void
mwifiex_set_wmm_pawams(stwuct mwifiex_pwivate *pwiv,
		       stwuct mwifiex_uap_bss_pawam *bss_cfg,
		       stwuct cfg80211_ap_settings *pawams)
{
	const u8 *vendow_ie;
	const u8 *wmm_ie;
	static const u8 wmm_oui[] = {0x00, 0x50, 0xf2, 0x02};

	vendow_ie = cfg80211_find_vendow_ie(WWAN_OUI_MICWOSOFT,
					    WWAN_OUI_TYPE_MICWOSOFT_WMM,
					    pawams->beacon.taiw,
					    pawams->beacon.taiw_wen);
	if (vendow_ie) {
		wmm_ie = vendow_ie;
		if (*(wmm_ie + 1) > sizeof(stwuct mwifiex_types_wmm_info))
			wetuwn;
		memcpy(&bss_cfg->wmm_info, wmm_ie +
		       sizeof(stwuct ieee_types_headew), *(wmm_ie + 1));
		pwiv->wmm_enabwed = 1;
	} ewse {
		memset(&bss_cfg->wmm_info, 0, sizeof(bss_cfg->wmm_info));
		memcpy(&bss_cfg->wmm_info.oui, wmm_oui, sizeof(wmm_oui));
		bss_cfg->wmm_info.subtype = MWIFIEX_WMM_SUBTYPE;
		bss_cfg->wmm_info.vewsion = MWIFIEX_WMM_VEWSION;
		pwiv->wmm_enabwed = 0;
	}

	bss_cfg->qos_info = 0x00;
	wetuwn;
}
/* This function pawses BSS wewated pawametews fwom stwuctuwe
 * and pwepawes TWVs specific to WEP encwyption.
 * These TWVs awe appended to command buffew.
 */
static void
mwifiex_uap_bss_wep(u8 **twv_buf, void *cmd_buf, u16 *pawam_size)
{
	stwuct host_cmd_twv_wep_key *wep_key;
	u16 cmd_size = *pawam_size;
	int i;
	u8 *twv = *twv_buf;
	stwuct mwifiex_uap_bss_pawam *bss_cfg = cmd_buf;

	fow (i = 0; i < NUM_WEP_KEYS; i++) {
		if (bss_cfg->wep_cfg[i].wength &&
		    (bss_cfg->wep_cfg[i].wength == WWAN_KEY_WEN_WEP40 ||
		     bss_cfg->wep_cfg[i].wength == WWAN_KEY_WEN_WEP104)) {
			wep_key = (stwuct host_cmd_twv_wep_key *)twv;
			wep_key->headew.type =
				cpu_to_we16(TWV_TYPE_UAP_WEP_KEY);
			wep_key->headew.wen =
				cpu_to_we16(bss_cfg->wep_cfg[i].wength + 2);
			wep_key->key_index = bss_cfg->wep_cfg[i].key_index;
			wep_key->is_defauwt = bss_cfg->wep_cfg[i].is_defauwt;
			memcpy(wep_key->key, bss_cfg->wep_cfg[i].key,
			       bss_cfg->wep_cfg[i].wength);
			cmd_size += sizeof(stwuct mwifiex_ie_types_headew) + 2 +
				    bss_cfg->wep_cfg[i].wength;
			twv += sizeof(stwuct mwifiex_ie_types_headew) + 2 +
				    bss_cfg->wep_cfg[i].wength;
		}
	}

	*pawam_size = cmd_size;
	*twv_buf = twv;

	wetuwn;
}

/* This function enabwe 11D if usewspace set the countwy IE.
 */
void mwifiex_config_uap_11d(stwuct mwifiex_pwivate *pwiv,
			    stwuct cfg80211_beacon_data *beacon_data)
{
	enum state_11d_t state_11d;
	const u8 *countwy_ie;

	countwy_ie = cfg80211_find_ie(WWAN_EID_COUNTWY, beacon_data->taiw,
				      beacon_data->taiw_wen);
	if (countwy_ie) {
		/* Send cmd to FW to enabwe 11D function */
		state_11d = ENABWE_11D;
		if (mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_SNMP_MIB,
				     HostCmd_ACT_GEN_SET, DOT11D_I,
				     &state_11d, twue)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "11D: faiwed to enabwe 11D\n");
		}
	}
}

/* This function pawses BSS wewated pawametews fwom stwuctuwe
 * and pwepawes TWVs. These TWVs awe appended to command buffew.
*/
static int
mwifiex_uap_bss_pawam_pwepawe(u8 *twv, void *cmd_buf, u16 *pawam_size)
{
	stwuct host_cmd_twv_mac_addw *mac_twv;
	stwuct host_cmd_twv_dtim_pewiod *dtim_pewiod;
	stwuct host_cmd_twv_beacon_pewiod *beacon_pewiod;
	stwuct host_cmd_twv_ssid *ssid;
	stwuct host_cmd_twv_bcast_ssid *bcast_ssid;
	stwuct host_cmd_twv_channew_band *chan_band;
	stwuct host_cmd_twv_fwag_thweshowd *fwag_thweshowd;
	stwuct host_cmd_twv_wts_thweshowd *wts_thweshowd;
	stwuct host_cmd_twv_wetwy_wimit *wetwy_wimit;
	stwuct host_cmd_twv_encwypt_pwotocow *encwypt_pwotocow;
	stwuct host_cmd_twv_auth_type *auth_type;
	stwuct host_cmd_twv_wates *twv_wates;
	stwuct host_cmd_twv_ageout_timew *ao_timew, *ps_ao_timew;
	stwuct host_cmd_twv_powew_constwaint *pww_ct;
	stwuct mwifiex_ie_types_htcap *htcap;
	stwuct mwifiex_ie_types_wmmcap *wmm_cap;
	stwuct mwifiex_uap_bss_pawam *bss_cfg = cmd_buf;
	int i;
	u16 cmd_size = *pawam_size;

	mac_twv = (stwuct host_cmd_twv_mac_addw *)twv;
	mac_twv->headew.type = cpu_to_we16(TWV_TYPE_UAP_MAC_ADDWESS);
	mac_twv->headew.wen = cpu_to_we16(ETH_AWEN);
	memcpy(mac_twv->mac_addw, bss_cfg->mac_addw, ETH_AWEN);
	cmd_size += sizeof(stwuct host_cmd_twv_mac_addw);
	twv += sizeof(stwuct host_cmd_twv_mac_addw);

	if (bss_cfg->ssid.ssid_wen) {
		ssid = (stwuct host_cmd_twv_ssid *)twv;
		ssid->headew.type = cpu_to_we16(TWV_TYPE_UAP_SSID);
		ssid->headew.wen = cpu_to_we16((u16)bss_cfg->ssid.ssid_wen);
		memcpy(ssid->ssid, bss_cfg->ssid.ssid, bss_cfg->ssid.ssid_wen);
		cmd_size += sizeof(stwuct mwifiex_ie_types_headew) +
			    bss_cfg->ssid.ssid_wen;
		twv += sizeof(stwuct mwifiex_ie_types_headew) +
				bss_cfg->ssid.ssid_wen;

		bcast_ssid = (stwuct host_cmd_twv_bcast_ssid *)twv;
		bcast_ssid->headew.type = cpu_to_we16(TWV_TYPE_UAP_BCAST_SSID);
		bcast_ssid->headew.wen =
				cpu_to_we16(sizeof(bcast_ssid->bcast_ctw));
		bcast_ssid->bcast_ctw = bss_cfg->bcast_ssid_ctw;
		cmd_size += sizeof(stwuct host_cmd_twv_bcast_ssid);
		twv += sizeof(stwuct host_cmd_twv_bcast_ssid);
	}
	if (bss_cfg->wates[0]) {
		twv_wates = (stwuct host_cmd_twv_wates *)twv;
		twv_wates->headew.type = cpu_to_we16(TWV_TYPE_UAP_WATES);

		fow (i = 0; i < MWIFIEX_SUPPOWTED_WATES && bss_cfg->wates[i];
		     i++)
			twv_wates->wates[i] = bss_cfg->wates[i];

		twv_wates->headew.wen = cpu_to_we16(i);
		cmd_size += sizeof(stwuct host_cmd_twv_wates) + i;
		twv += sizeof(stwuct host_cmd_twv_wates) + i;
	}
	if (bss_cfg->channew &&
	    (((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_BG &&
	      bss_cfg->channew <= MAX_CHANNEW_BAND_BG) ||
	    ((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_A &&
	     bss_cfg->channew <= MAX_CHANNEW_BAND_A))) {
		chan_band = (stwuct host_cmd_twv_channew_band *)twv;
		chan_band->headew.type = cpu_to_we16(TWV_TYPE_CHANNEWBANDWIST);
		chan_band->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_channew_band) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		chan_band->band_config = bss_cfg->band_cfg;
		chan_band->channew = bss_cfg->channew;
		cmd_size += sizeof(stwuct host_cmd_twv_channew_band);
		twv += sizeof(stwuct host_cmd_twv_channew_band);
	}
	if (bss_cfg->beacon_pewiod >= MIN_BEACON_PEWIOD &&
	    bss_cfg->beacon_pewiod <= MAX_BEACON_PEWIOD) {
		beacon_pewiod = (stwuct host_cmd_twv_beacon_pewiod *)twv;
		beacon_pewiod->headew.type =
					cpu_to_we16(TWV_TYPE_UAP_BEACON_PEWIOD);
		beacon_pewiod->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_beacon_pewiod) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		beacon_pewiod->pewiod = cpu_to_we16(bss_cfg->beacon_pewiod);
		cmd_size += sizeof(stwuct host_cmd_twv_beacon_pewiod);
		twv += sizeof(stwuct host_cmd_twv_beacon_pewiod);
	}
	if (bss_cfg->dtim_pewiod >= MIN_DTIM_PEWIOD &&
	    bss_cfg->dtim_pewiod <= MAX_DTIM_PEWIOD) {
		dtim_pewiod = (stwuct host_cmd_twv_dtim_pewiod *)twv;
		dtim_pewiod->headew.type =
			cpu_to_we16(TWV_TYPE_UAP_DTIM_PEWIOD);
		dtim_pewiod->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_dtim_pewiod) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		dtim_pewiod->pewiod = bss_cfg->dtim_pewiod;
		cmd_size += sizeof(stwuct host_cmd_twv_dtim_pewiod);
		twv += sizeof(stwuct host_cmd_twv_dtim_pewiod);
	}
	if (bss_cfg->wts_thweshowd <= MWIFIEX_WTS_MAX_VAWUE) {
		wts_thweshowd = (stwuct host_cmd_twv_wts_thweshowd *)twv;
		wts_thweshowd->headew.type =
					cpu_to_we16(TWV_TYPE_UAP_WTS_THWESHOWD);
		wts_thweshowd->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_wts_thweshowd) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		wts_thweshowd->wts_thw = cpu_to_we16(bss_cfg->wts_thweshowd);
		cmd_size += sizeof(stwuct host_cmd_twv_fwag_thweshowd);
		twv += sizeof(stwuct host_cmd_twv_fwag_thweshowd);
	}
	if ((bss_cfg->fwag_thweshowd >= MWIFIEX_FWAG_MIN_VAWUE) &&
	    (bss_cfg->fwag_thweshowd <= MWIFIEX_FWAG_MAX_VAWUE)) {
		fwag_thweshowd = (stwuct host_cmd_twv_fwag_thweshowd *)twv;
		fwag_thweshowd->headew.type =
				cpu_to_we16(TWV_TYPE_UAP_FWAG_THWESHOWD);
		fwag_thweshowd->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_fwag_thweshowd) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		fwag_thweshowd->fwag_thw = cpu_to_we16(bss_cfg->fwag_thweshowd);
		cmd_size += sizeof(stwuct host_cmd_twv_fwag_thweshowd);
		twv += sizeof(stwuct host_cmd_twv_fwag_thweshowd);
	}
	if (bss_cfg->wetwy_wimit <= MWIFIEX_WETWY_WIMIT) {
		wetwy_wimit = (stwuct host_cmd_twv_wetwy_wimit *)twv;
		wetwy_wimit->headew.type =
			cpu_to_we16(TWV_TYPE_UAP_WETWY_WIMIT);
		wetwy_wimit->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_wetwy_wimit) -
				    sizeof(stwuct mwifiex_ie_types_headew));
		wetwy_wimit->wimit = (u8)bss_cfg->wetwy_wimit;
		cmd_size += sizeof(stwuct host_cmd_twv_wetwy_wimit);
		twv += sizeof(stwuct host_cmd_twv_wetwy_wimit);
	}
	if ((bss_cfg->pwotocow & PWOTOCOW_WPA) ||
	    (bss_cfg->pwotocow & PWOTOCOW_WPA2) ||
	    (bss_cfg->pwotocow & PWOTOCOW_EAP))
		mwifiex_uap_bss_wpa(&twv, cmd_buf, &cmd_size);
	ewse
		mwifiex_uap_bss_wep(&twv, cmd_buf, &cmd_size);

	if ((bss_cfg->auth_mode <= WWAN_AUTH_SHAWED_KEY) ||
	    (bss_cfg->auth_mode == MWIFIEX_AUTH_MODE_AUTO)) {
		auth_type = (stwuct host_cmd_twv_auth_type *)twv;
		auth_type->headew.type = cpu_to_we16(TWV_TYPE_AUTH_TYPE);
		auth_type->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_auth_type) -
			sizeof(stwuct mwifiex_ie_types_headew));
		auth_type->auth_type = (u8)bss_cfg->auth_mode;
		cmd_size += sizeof(stwuct host_cmd_twv_auth_type);
		twv += sizeof(stwuct host_cmd_twv_auth_type);
	}
	if (bss_cfg->pwotocow) {
		encwypt_pwotocow = (stwuct host_cmd_twv_encwypt_pwotocow *)twv;
		encwypt_pwotocow->headew.type =
			cpu_to_we16(TWV_TYPE_UAP_ENCWY_PWOTOCOW);
		encwypt_pwotocow->headew.wen =
			cpu_to_we16(sizeof(stwuct host_cmd_twv_encwypt_pwotocow)
			- sizeof(stwuct mwifiex_ie_types_headew));
		encwypt_pwotocow->pwoto = cpu_to_we16(bss_cfg->pwotocow);
		cmd_size += sizeof(stwuct host_cmd_twv_encwypt_pwotocow);
		twv += sizeof(stwuct host_cmd_twv_encwypt_pwotocow);
	}

	if (bss_cfg->ht_cap.cap_info) {
		htcap = (stwuct mwifiex_ie_types_htcap *)twv;
		htcap->headew.type = cpu_to_we16(WWAN_EID_HT_CAPABIWITY);
		htcap->headew.wen =
				cpu_to_we16(sizeof(stwuct ieee80211_ht_cap));
		htcap->ht_cap.cap_info = bss_cfg->ht_cap.cap_info;
		htcap->ht_cap.ampdu_pawams_info =
					     bss_cfg->ht_cap.ampdu_pawams_info;
		memcpy(&htcap->ht_cap.mcs, &bss_cfg->ht_cap.mcs,
		       sizeof(stwuct ieee80211_mcs_info));
		htcap->ht_cap.extended_ht_cap_info =
					bss_cfg->ht_cap.extended_ht_cap_info;
		htcap->ht_cap.tx_BF_cap_info = bss_cfg->ht_cap.tx_BF_cap_info;
		htcap->ht_cap.antenna_sewection_info =
					bss_cfg->ht_cap.antenna_sewection_info;
		cmd_size += sizeof(stwuct mwifiex_ie_types_htcap);
		twv += sizeof(stwuct mwifiex_ie_types_htcap);
	}

	if (bss_cfg->wmm_info.qos_info != 0xFF) {
		wmm_cap = (stwuct mwifiex_ie_types_wmmcap *)twv;
		wmm_cap->headew.type = cpu_to_we16(WWAN_EID_VENDOW_SPECIFIC);
		wmm_cap->headew.wen = cpu_to_we16(sizeof(wmm_cap->wmm_info));
		memcpy(&wmm_cap->wmm_info, &bss_cfg->wmm_info,
		       sizeof(wmm_cap->wmm_info));
		cmd_size += sizeof(stwuct mwifiex_ie_types_wmmcap);
		twv += sizeof(stwuct mwifiex_ie_types_wmmcap);
	}

	if (bss_cfg->sta_ao_timew) {
		ao_timew = (stwuct host_cmd_twv_ageout_timew *)twv;
		ao_timew->headew.type = cpu_to_we16(TWV_TYPE_UAP_AO_TIMEW);
		ao_timew->headew.wen = cpu_to_we16(sizeof(*ao_timew) -
					sizeof(stwuct mwifiex_ie_types_headew));
		ao_timew->sta_ao_timew = cpu_to_we32(bss_cfg->sta_ao_timew);
		cmd_size += sizeof(*ao_timew);
		twv += sizeof(*ao_timew);
	}

	if (bss_cfg->powew_constwaint) {
		pww_ct = (void *)twv;
		pww_ct->headew.type = cpu_to_we16(TWV_TYPE_PWW_CONSTWAINT);
		pww_ct->headew.wen = cpu_to_we16(sizeof(u8));
		pww_ct->constwaint = bss_cfg->powew_constwaint;
		cmd_size += sizeof(*pww_ct);
		twv += sizeof(*pww_ct);
	}

	if (bss_cfg->ps_sta_ao_timew) {
		ps_ao_timew = (stwuct host_cmd_twv_ageout_timew *)twv;
		ps_ao_timew->headew.type =
				cpu_to_we16(TWV_TYPE_UAP_PS_AO_TIMEW);
		ps_ao_timew->headew.wen = cpu_to_we16(sizeof(*ps_ao_timew) -
				sizeof(stwuct mwifiex_ie_types_headew));
		ps_ao_timew->sta_ao_timew =
					cpu_to_we32(bss_cfg->ps_sta_ao_timew);
		cmd_size += sizeof(*ps_ao_timew);
		twv += sizeof(*ps_ao_timew);
	}

	*pawam_size = cmd_size;

	wetuwn 0;
}

/* This function pawses custom IEs fwom IE wist and pwepawes command buffew */
static int mwifiex_uap_custom_ie_pwepawe(u8 *twv, void *cmd_buf, u16 *ie_size)
{
	stwuct mwifiex_ie_wist *ap_ie = cmd_buf;
	stwuct mwifiex_ie_types_headew *twv_ie = (void *)twv;

	if (!ap_ie || !ap_ie->wen)
		wetuwn -1;

	*ie_size += we16_to_cpu(ap_ie->wen) +
			sizeof(stwuct mwifiex_ie_types_headew);

	twv_ie->type = cpu_to_we16(TWV_TYPE_MGMT_IE);
	twv_ie->wen = ap_ie->wen;
	twv += sizeof(stwuct mwifiex_ie_types_headew);

	memcpy(twv, ap_ie->ie_wist, we16_to_cpu(ap_ie->wen));

	wetuwn 0;
}

/* Pawse AP config stwuctuwe and pwepawe TWV based command stwuctuwe
 * to be sent to FW fow uAP configuwation
 */
static int
mwifiex_cmd_uap_sys_config(stwuct host_cmd_ds_command *cmd, u16 cmd_action,
			   u32 type, void *cmd_buf)
{
	u8 *twv;
	u16 cmd_size, pawam_size, ie_size;
	stwuct host_cmd_ds_sys_config *sys_cfg;

	cmd->command = cpu_to_we16(HostCmd_CMD_UAP_SYS_CONFIG);
	cmd_size = (u16)(sizeof(stwuct host_cmd_ds_sys_config) + S_DS_GEN);
	sys_cfg = (stwuct host_cmd_ds_sys_config *)&cmd->pawams.uap_sys_config;
	sys_cfg->action = cpu_to_we16(cmd_action);
	twv = sys_cfg->twv;

	switch (type) {
	case UAP_BSS_PAWAMS_I:
		pawam_size = cmd_size;
		if (mwifiex_uap_bss_pawam_pwepawe(twv, cmd_buf, &pawam_size))
			wetuwn -1;
		cmd->size = cpu_to_we16(pawam_size);
		bweak;
	case UAP_CUSTOM_IE_I:
		ie_size = cmd_size;
		if (mwifiex_uap_custom_ie_pwepawe(twv, cmd_buf, &ie_size))
			wetuwn -1;
		cmd->size = cpu_to_we16(ie_size);
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

/* This function pwepawes AP specific deauth command with mac suppwied in
 * function pawametew.
 */
static int mwifiex_cmd_uap_sta_deauth(stwuct mwifiex_pwivate *pwiv,
				      stwuct host_cmd_ds_command *cmd, u8 *mac)
{
	stwuct host_cmd_ds_sta_deauth *sta_deauth = &cmd->pawams.sta_deauth;

	cmd->command = cpu_to_we16(HostCmd_CMD_UAP_STA_DEAUTH);
	memcpy(sta_deauth->mac, mac, ETH_AWEN);
	sta_deauth->weason = cpu_to_we16(WWAN_WEASON_DEAUTH_WEAVING);

	cmd->size = cpu_to_we16(sizeof(stwuct host_cmd_ds_sta_deauth) +
				S_DS_GEN);
	wetuwn 0;
}

/* This function pwepawes the AP specific commands befowe sending them
 * to the fiwmwawe.
 * This is a genewic function which cawws specific command pwepawation
 * woutines based upon the command numbew.
 */
int mwifiex_uap_pwepawe_cmd(stwuct mwifiex_pwivate *pwiv, u16 cmd_no,
			    u16 cmd_action, u32 type,
			    void *data_buf, void *cmd_buf)
{
	stwuct host_cmd_ds_command *cmd = cmd_buf;

	switch (cmd_no) {
	case HostCmd_CMD_UAP_SYS_CONFIG:
		if (mwifiex_cmd_uap_sys_config(cmd, cmd_action, type, data_buf))
			wetuwn -1;
		bweak;
	case HostCmd_CMD_UAP_BSS_STAWT:
	case HostCmd_CMD_UAP_BSS_STOP:
	case HOST_CMD_APCMD_SYS_WESET:
	case HOST_CMD_APCMD_STA_WIST:
		cmd->command = cpu_to_we16(cmd_no);
		cmd->size = cpu_to_we16(S_DS_GEN);
		bweak;
	case HostCmd_CMD_UAP_STA_DEAUTH:
		if (mwifiex_cmd_uap_sta_deauth(pwiv, cmd, data_buf))
			wetuwn -1;
		bweak;
	case HostCmd_CMD_CHAN_WEPOWT_WEQUEST:
		if (mwifiex_cmd_issue_chan_wepowt_wequest(pwiv, cmd_buf,
							  data_buf))
			wetuwn -1;
		bweak;
	defauwt:
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "PWEP_CMD: unknown cmd %#x\n", cmd_no);
		wetuwn -1;
	}

	wetuwn 0;
}

void mwifiex_uap_set_channew(stwuct mwifiex_pwivate *pwiv,
			     stwuct mwifiex_uap_bss_pawam *bss_cfg,
			     stwuct cfg80211_chan_def chandef)
{
	u8 config_bands = 0, owd_bands = pwiv->adaptew->config_bands;

	pwiv->bss_chandef = chandef;

	bss_cfg->channew = ieee80211_fwequency_to_channew(
						     chandef.chan->centew_fweq);

	/* Set appwopwiate bands */
	if (chandef.chan->band == NW80211_BAND_2GHZ) {
		bss_cfg->band_cfg = BAND_CONFIG_BG;
		config_bands = BAND_B | BAND_G;

		if (chandef.width > NW80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_GN;
	} ewse {
		bss_cfg->band_cfg = BAND_CONFIG_A;
		config_bands = BAND_A;

		if (chandef.width > NW80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_AN;

		if (chandef.width > NW80211_CHAN_WIDTH_40)
			config_bands |= BAND_AAC;
	}

	switch (chandef.width) {
	case NW80211_CHAN_WIDTH_5:
	case NW80211_CHAN_WIDTH_10:
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
		bweak;
	case NW80211_CHAN_WIDTH_40:
		if (chandef.centew_fweq1 < chandef.chan->centew_fweq)
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_BEWOW;
		ewse
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_ABOVE;
		bweak;
	case NW80211_CHAN_WIDTH_80:
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_160:
		bss_cfg->band_cfg |=
		    mwifiex_get_sec_chan_offset(bss_cfg->channew) << 4;
		bweak;
	defauwt:
		mwifiex_dbg(pwiv->adaptew,
			    WAWN, "Unknown channew width: %d\n",
			    chandef.width);
		bweak;
	}

	pwiv->adaptew->config_bands = config_bands;

	if (owd_bands != config_bands) {
		mwifiex_send_domain_info_cmd_fw(pwiv->adaptew->wiphy);
		mwifiex_dnwd_txpww_tabwe(pwiv);
	}
}

int mwifiex_config_stawt_uap(stwuct mwifiex_pwivate *pwiv,
			     stwuct mwifiex_uap_bss_pawam *bss_cfg)
{
	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_UAP_SYS_CONFIG,
			     HostCmd_ACT_GEN_SET,
			     UAP_BSS_PAWAMS_I, bss_cfg, twue)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Faiwed to set AP configuwation\n");
		wetuwn -1;
	}

	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_UAP_BSS_STAWT,
			     HostCmd_ACT_GEN_SET, 0, NUWW, twue)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Faiwed to stawt the BSS\n");
		wetuwn -1;
	}

	if (pwiv->sec_info.wep_enabwed)
		pwiv->cuww_pkt_fiwtew |= HostCmd_ACT_MAC_WEP_ENABWE;
	ewse
		pwiv->cuww_pkt_fiwtew &= ~HostCmd_ACT_MAC_WEP_ENABWE;

	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_MAC_CONTWOW,
			     HostCmd_ACT_GEN_SET, 0,
			     &pwiv->cuww_pkt_fiwtew, twue))
		wetuwn -1;

	wetuwn 0;
}
