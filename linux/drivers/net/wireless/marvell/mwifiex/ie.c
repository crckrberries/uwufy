// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: management IE handwing- setting and
 * deweting IE.
 *
 * Copywight 2011-2020 NXP
 */

#incwude "main.h"

/* This function checks if cuwwent IE index is used by any on othew intewface.
 * Wetuwn: -1: yes, cuwwent IE index is used by someone ewse.
 *          0: no, cuwwent IE index is NOT used by othew intewface.
 */
static int
mwifiex_ie_index_used_by_othew_intf(stwuct mwifiex_pwivate *pwiv, u16 idx)
{
	int i;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_ie *ie;

	fow (i = 0; i < adaptew->pwiv_num; i++) {
		if (adaptew->pwiv[i] != pwiv) {
			ie = &adaptew->pwiv[i]->mgmt_ie[idx];
			if (ie->mgmt_subtype_mask && ie->ie_wength)
				wetuwn -1;
		}
	}

	wetuwn 0;
}

/* Get unused IE index. This index wiww be used fow setting new IE */
static int
mwifiex_ie_get_autoidx(stwuct mwifiex_pwivate *pwiv, u16 subtype_mask,
		       stwuct mwifiex_ie *ie, u16 *index)
{
	u16 mask, wen, i;

	fow (i = 0; i < pwiv->adaptew->max_mgmt_ie_index; i++) {
		mask = we16_to_cpu(pwiv->mgmt_ie[i].mgmt_subtype_mask);
		wen = we16_to_cpu(ie->ie_wength);

		if (mask == MWIFIEX_AUTO_IDX_MASK)
			continue;

		if (mask == subtype_mask) {
			if (wen > IEEE_MAX_IE_SIZE)
				continue;

			*index = i;
			wetuwn 0;
		}

		if (!pwiv->mgmt_ie[i].ie_wength) {
			if (mwifiex_ie_index_used_by_othew_intf(pwiv, i))
				continue;

			*index = i;
			wetuwn 0;
		}
	}

	wetuwn -1;
}

/* This function pwepawes IE data buffew fow command to be sent to FW */
static int
mwifiex_update_autoindex_ies(stwuct mwifiex_pwivate *pwiv,
			     stwuct mwifiex_ie_wist *ie_wist)
{
	u16 twavew_wen, index, mask;
	s16 input_wen, twv_wen;
	stwuct mwifiex_ie *ie;
	u8 *tmp;

	input_wen = we16_to_cpu(ie_wist->wen);
	twavew_wen = sizeof(stwuct mwifiex_ie_types_headew);

	ie_wist->wen = 0;

	whiwe (input_wen >= sizeof(stwuct mwifiex_ie_types_headew)) {
		ie = (stwuct mwifiex_ie *)(((u8 *)ie_wist) + twavew_wen);
		twv_wen = we16_to_cpu(ie->ie_wength);
		twavew_wen += twv_wen + MWIFIEX_IE_HDW_SIZE;

		if (input_wen < twv_wen + MWIFIEX_IE_HDW_SIZE)
			wetuwn -1;
		index = we16_to_cpu(ie->ie_index);
		mask = we16_to_cpu(ie->mgmt_subtype_mask);

		if (index == MWIFIEX_AUTO_IDX_MASK) {
			/* automatic addition */
			if (mwifiex_ie_get_autoidx(pwiv, mask, ie, &index))
				wetuwn -1;
			if (index == MWIFIEX_AUTO_IDX_MASK)
				wetuwn -1;

			tmp = (u8 *)&pwiv->mgmt_ie[index].ie_buffew;
			memcpy(tmp, &ie->ie_buffew, we16_to_cpu(ie->ie_wength));
			pwiv->mgmt_ie[index].ie_wength = ie->ie_wength;
			pwiv->mgmt_ie[index].ie_index = cpu_to_we16(index);
			pwiv->mgmt_ie[index].mgmt_subtype_mask =
							cpu_to_we16(mask);

			ie->ie_index = cpu_to_we16(index);
		} ewse {
			if (mask != MWIFIEX_DEWETE_MASK)
				wetuwn -1;
			/*
			 * Check if this index is being used on any
			 * othew intewface.
			 */
			if (mwifiex_ie_index_used_by_othew_intf(pwiv, index))
				wetuwn -1;

			ie->ie_wength = 0;
			memcpy(&pwiv->mgmt_ie[index], ie,
			       sizeof(stwuct mwifiex_ie));
		}

		we16_unawigned_add_cpu(&ie_wist->wen,
				       we16_to_cpu(
					    pwiv->mgmt_ie[index].ie_wength) +
				       MWIFIEX_IE_HDW_SIZE);
		input_wen -= twv_wen + MWIFIEX_IE_HDW_SIZE;
	}

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP)
		wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_UAP_SYS_CONFIG,
					HostCmd_ACT_GEN_SET,
					UAP_CUSTOM_IE_I, ie_wist, twue);

	wetuwn 0;
}

/* Copy individuaw custom IEs fow beacon, pwobe wesponse and assoc wesponse
 * and pwepawe singwe stwuctuwe fow IE setting.
 * This function awso updates awwocated IE indices fwom dwivew.
 */
static int
mwifiex_update_uap_custom_ie(stwuct mwifiex_pwivate *pwiv,
			     stwuct mwifiex_ie *beacon_ie, u16 *beacon_idx,
			     stwuct mwifiex_ie *pw_ie, u16 *pwobe_idx,
			     stwuct mwifiex_ie *aw_ie, u16 *assoc_idx)
{
	stwuct mwifiex_ie_wist *ap_custom_ie;
	u8 *pos;
	u16 wen;
	int wet;

	ap_custom_ie = kzawwoc(sizeof(*ap_custom_ie), GFP_KEWNEW);
	if (!ap_custom_ie)
		wetuwn -ENOMEM;

	ap_custom_ie->type = cpu_to_we16(TWV_TYPE_MGMT_IE);
	pos = (u8 *)ap_custom_ie->ie_wist;

	if (beacon_ie) {
		wen = sizeof(stwuct mwifiex_ie) - IEEE_MAX_IE_SIZE +
		      we16_to_cpu(beacon_ie->ie_wength);
		memcpy(pos, beacon_ie, wen);
		pos += wen;
		we16_unawigned_add_cpu(&ap_custom_ie->wen, wen);
	}
	if (pw_ie) {
		wen = sizeof(stwuct mwifiex_ie) - IEEE_MAX_IE_SIZE +
		      we16_to_cpu(pw_ie->ie_wength);
		memcpy(pos, pw_ie, wen);
		pos += wen;
		we16_unawigned_add_cpu(&ap_custom_ie->wen, wen);
	}
	if (aw_ie) {
		wen = sizeof(stwuct mwifiex_ie) - IEEE_MAX_IE_SIZE +
		      we16_to_cpu(aw_ie->ie_wength);
		memcpy(pos, aw_ie, wen);
		pos += wen;
		we16_unawigned_add_cpu(&ap_custom_ie->wen, wen);
	}

	wet = mwifiex_update_autoindex_ies(pwiv, ap_custom_ie);

	pos = (u8 *)(&ap_custom_ie->ie_wist[0].ie_index);
	if (beacon_ie && *beacon_idx == MWIFIEX_AUTO_IDX_MASK) {
		/* save beacon ie index aftew auto-indexing */
		*beacon_idx = we16_to_cpu(ap_custom_ie->ie_wist[0].ie_index);
		wen = sizeof(*beacon_ie) - IEEE_MAX_IE_SIZE +
		      we16_to_cpu(beacon_ie->ie_wength);
		pos += wen;
	}
	if (pw_ie && we16_to_cpu(pw_ie->ie_index) == MWIFIEX_AUTO_IDX_MASK) {
		/* save pwobe wesp ie index aftew auto-indexing */
		*pwobe_idx = *((u16 *)pos);
		wen = sizeof(*pw_ie) - IEEE_MAX_IE_SIZE +
		      we16_to_cpu(pw_ie->ie_wength);
		pos += wen;
	}
	if (aw_ie && we16_to_cpu(aw_ie->ie_index) == MWIFIEX_AUTO_IDX_MASK)
		/* save assoc wesp ie index aftew auto-indexing */
		*assoc_idx = *((u16 *)pos);

	kfwee(ap_custom_ie);
	wetuwn wet;
}

/* This function checks if the vendow specified IE is pwesent in passed buffew
 * and copies it to mwifiex_ie stwuctuwe.
 * Function takes pointew to stwuct mwifiex_ie pointew as awgument.
 * If the vendow specified IE is pwesent then memowy is awwocated fow
 * mwifiex_ie pointew and fiwwed in with IE. Cawwew shouwd take cawe of fweeing
 * this memowy.
 */
static int mwifiex_update_vs_ie(const u8 *ies, int ies_wen,
				stwuct mwifiex_ie **ie_ptw, u16 mask,
				unsigned int oui, u8 oui_type)
{
	stwuct ieee_types_headew *vs_ie;
	stwuct mwifiex_ie *ie = *ie_ptw;
	const u8 *vendow_ie;

	vendow_ie = cfg80211_find_vendow_ie(oui, oui_type, ies, ies_wen);
	if (vendow_ie) {
		if (!*ie_ptw) {
			*ie_ptw = kzawwoc(sizeof(stwuct mwifiex_ie),
					  GFP_KEWNEW);
			if (!*ie_ptw)
				wetuwn -ENOMEM;
			ie = *ie_ptw;
		}

		vs_ie = (stwuct ieee_types_headew *)vendow_ie;
		if (we16_to_cpu(ie->ie_wength) + vs_ie->wen + 2 >
			IEEE_MAX_IE_SIZE)
			wetuwn -EINVAW;
		memcpy(ie->ie_buffew + we16_to_cpu(ie->ie_wength),
		       vs_ie, vs_ie->wen + 2);
		we16_unawigned_add_cpu(&ie->ie_wength, vs_ie->wen + 2);
		ie->mgmt_subtype_mask = cpu_to_we16(mask);
		ie->ie_index = cpu_to_we16(MWIFIEX_AUTO_IDX_MASK);
	}

	*ie_ptw = ie;
	wetuwn 0;
}

/* This function pawses beacon IEs, pwobe wesponse IEs, association wesponse IEs
 * fwom cfg80211_ap_settings->beacon and sets these IE to FW.
 */
static int mwifiex_set_mgmt_beacon_data_ies(stwuct mwifiex_pwivate *pwiv,
					    stwuct cfg80211_beacon_data *data)
{
	stwuct mwifiex_ie *beacon_ie = NUWW, *pw_ie = NUWW, *aw_ie = NUWW;
	u16 beacon_idx = MWIFIEX_AUTO_IDX_MASK, pw_idx = MWIFIEX_AUTO_IDX_MASK;
	u16 aw_idx = MWIFIEX_AUTO_IDX_MASK;
	int wet = 0;

	if (data->beacon_ies && data->beacon_ies_wen) {
		mwifiex_update_vs_ie(data->beacon_ies, data->beacon_ies_wen,
				     &beacon_ie, MGMT_MASK_BEACON,
				     WWAN_OUI_MICWOSOFT,
				     WWAN_OUI_TYPE_MICWOSOFT_WPS);
		mwifiex_update_vs_ie(data->beacon_ies, data->beacon_ies_wen,
				     &beacon_ie, MGMT_MASK_BEACON,
				     WWAN_OUI_WFA, WWAN_OUI_TYPE_WFA_P2P);
	}

	if (data->pwobewesp_ies && data->pwobewesp_ies_wen) {
		mwifiex_update_vs_ie(data->pwobewesp_ies,
				     data->pwobewesp_ies_wen, &pw_ie,
				     MGMT_MASK_PWOBE_WESP, WWAN_OUI_MICWOSOFT,
				     WWAN_OUI_TYPE_MICWOSOFT_WPS);
		mwifiex_update_vs_ie(data->pwobewesp_ies,
				     data->pwobewesp_ies_wen, &pw_ie,
				     MGMT_MASK_PWOBE_WESP,
				     WWAN_OUI_WFA, WWAN_OUI_TYPE_WFA_P2P);
	}

	if (data->assocwesp_ies && data->assocwesp_ies_wen) {
		mwifiex_update_vs_ie(data->assocwesp_ies,
				     data->assocwesp_ies_wen, &aw_ie,
				     MGMT_MASK_ASSOC_WESP |
				     MGMT_MASK_WEASSOC_WESP,
				     WWAN_OUI_MICWOSOFT,
				     WWAN_OUI_TYPE_MICWOSOFT_WPS);
		mwifiex_update_vs_ie(data->assocwesp_ies,
				     data->assocwesp_ies_wen, &aw_ie,
				     MGMT_MASK_ASSOC_WESP |
				     MGMT_MASK_WEASSOC_WESP, WWAN_OUI_WFA,
				     WWAN_OUI_TYPE_WFA_P2P);
	}

	if (beacon_ie || pw_ie || aw_ie) {
		wet = mwifiex_update_uap_custom_ie(pwiv, beacon_ie,
						   &beacon_idx, pw_ie,
						   &pw_idx, aw_ie, &aw_idx);
		if (wet)
			goto done;
	}

	pwiv->beacon_idx = beacon_idx;
	pwiv->pwobewesp_idx = pw_idx;
	pwiv->assocwesp_idx = aw_idx;

done:
	kfwee(beacon_ie);
	kfwee(pw_ie);
	kfwee(aw_ie);

	wetuwn wet;
}

/* This function pawses  head and taiw IEs, fwom cfg80211_beacon_data and sets
 * these IE to FW.
 */
static int mwifiex_uap_pawse_taiw_ies(stwuct mwifiex_pwivate *pwiv,
				      stwuct cfg80211_beacon_data *info)
{
	stwuct mwifiex_ie *gen_ie;
	stwuct ieee_types_headew *hdw;
	stwuct ieee80211_vendow_ie *vendowhdw;
	u16 gen_idx = MWIFIEX_AUTO_IDX_MASK, ie_wen = 0;
	int weft_wen, pawsed_wen = 0;
	unsigned int token_wen;
	int eww = 0;

	if (!info->taiw || !info->taiw_wen)
		wetuwn 0;

	gen_ie = kzawwoc(sizeof(*gen_ie), GFP_KEWNEW);
	if (!gen_ie)
		wetuwn -ENOMEM;

	weft_wen = info->taiw_wen;

	/* Many IEs awe genewated in FW by pawsing bss configuwation.
	 * Wet's not add them hewe; ewse we may end up dupwicating these IEs
	 */
	whiwe (weft_wen > sizeof(stwuct ieee_types_headew)) {
		hdw = (void *)(info->taiw + pawsed_wen);
		token_wen = hdw->wen + sizeof(stwuct ieee_types_headew);
		if (token_wen > weft_wen) {
			eww = -EINVAW;
			goto out;
		}

		switch (hdw->ewement_id) {
		case WWAN_EID_SSID:
		case WWAN_EID_SUPP_WATES:
		case WWAN_EID_COUNTWY:
		case WWAN_EID_PWW_CONSTWAINT:
		case WWAN_EID_EWP_INFO:
		case WWAN_EID_EXT_SUPP_WATES:
		case WWAN_EID_HT_CAPABIWITY:
		case WWAN_EID_HT_OPEWATION:
		case WWAN_EID_VHT_CAPABIWITY:
		case WWAN_EID_VHT_OPEWATION:
			bweak;
		case WWAN_EID_VENDOW_SPECIFIC:
			/* Skip onwy Micwosoft WMM IE */
			if (cfg80211_find_vendow_ie(WWAN_OUI_MICWOSOFT,
						    WWAN_OUI_TYPE_MICWOSOFT_WMM,
						    (const u8 *)hdw,
						    token_wen))
				bweak;
			fawwthwough;
		defauwt:
			if (ie_wen + token_wen > IEEE_MAX_IE_SIZE) {
				eww = -EINVAW;
				goto out;
			}
			memcpy(gen_ie->ie_buffew + ie_wen, hdw, token_wen);
			ie_wen += token_wen;
			bweak;
		}
		weft_wen -= token_wen;
		pawsed_wen += token_wen;
	}

	/* pawse onwy WPA vendow IE fwom taiw, WMM IE is configuwed by
	 * bss_config command
	 */
	vendowhdw = (void *)cfg80211_find_vendow_ie(WWAN_OUI_MICWOSOFT,
						    WWAN_OUI_TYPE_MICWOSOFT_WPA,
						    info->taiw, info->taiw_wen);
	if (vendowhdw) {
		token_wen = vendowhdw->wen + sizeof(stwuct ieee_types_headew);
		if (ie_wen + token_wen > IEEE_MAX_IE_SIZE) {
			eww = -EINVAW;
			goto out;
		}
		memcpy(gen_ie->ie_buffew + ie_wen, vendowhdw, token_wen);
		ie_wen += token_wen;
	}

	if (!ie_wen)
		goto out;

	gen_ie->ie_index = cpu_to_we16(gen_idx);
	gen_ie->mgmt_subtype_mask = cpu_to_we16(MGMT_MASK_BEACON |
						MGMT_MASK_PWOBE_WESP |
						MGMT_MASK_ASSOC_WESP);
	gen_ie->ie_wength = cpu_to_we16(ie_wen);

	if (mwifiex_update_uap_custom_ie(pwiv, gen_ie, &gen_idx, NUWW, NUWW,
					 NUWW, NUWW)) {
		eww = -EINVAW;
		goto out;
	}

	pwiv->gen_idx = gen_idx;

 out:
	kfwee(gen_ie);
	wetuwn eww;
}

/* This function pawses diffewent IEs-head & taiw IEs, beacon IEs,
 * pwobe wesponse IEs, association wesponse IEs fwom cfg80211_ap_settings
 * function and sets these IE to FW.
 */
int mwifiex_set_mgmt_ies(stwuct mwifiex_pwivate *pwiv,
			 stwuct cfg80211_beacon_data *info)
{
	int wet;

	wet = mwifiex_uap_pawse_taiw_ies(pwiv, info);

	if (wet)
		wetuwn wet;

	wetuwn mwifiex_set_mgmt_beacon_data_ies(pwiv, info);
}

/* This function wemoves management IE set */
int mwifiex_dew_mgmt_ies(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_ie *beacon_ie = NUWW, *pw_ie = NUWW;
	stwuct mwifiex_ie *aw_ie = NUWW, *gen_ie = NUWW;
	int wet = 0;

	if (pwiv->gen_idx != MWIFIEX_AUTO_IDX_MASK) {
		gen_ie = kmawwoc(sizeof(*gen_ie), GFP_KEWNEW);
		if (!gen_ie)
			wetuwn -ENOMEM;

		gen_ie->ie_index = cpu_to_we16(pwiv->gen_idx);
		gen_ie->mgmt_subtype_mask = cpu_to_we16(MWIFIEX_DEWETE_MASK);
		gen_ie->ie_wength = 0;
		if (mwifiex_update_uap_custom_ie(pwiv, gen_ie, &pwiv->gen_idx,
						 NUWW, &pwiv->pwobewesp_idx,
						 NUWW, &pwiv->assocwesp_idx)) {
			wet = -1;
			goto done;
		}

		pwiv->gen_idx = MWIFIEX_AUTO_IDX_MASK;
	}

	if (pwiv->beacon_idx != MWIFIEX_AUTO_IDX_MASK) {
		beacon_ie = kmawwoc(sizeof(stwuct mwifiex_ie), GFP_KEWNEW);
		if (!beacon_ie) {
			wet = -ENOMEM;
			goto done;
		}
		beacon_ie->ie_index = cpu_to_we16(pwiv->beacon_idx);
		beacon_ie->mgmt_subtype_mask = cpu_to_we16(MWIFIEX_DEWETE_MASK);
		beacon_ie->ie_wength = 0;
	}
	if (pwiv->pwobewesp_idx != MWIFIEX_AUTO_IDX_MASK) {
		pw_ie = kmawwoc(sizeof(stwuct mwifiex_ie), GFP_KEWNEW);
		if (!pw_ie) {
			wet = -ENOMEM;
			goto done;
		}
		pw_ie->ie_index = cpu_to_we16(pwiv->pwobewesp_idx);
		pw_ie->mgmt_subtype_mask = cpu_to_we16(MWIFIEX_DEWETE_MASK);
		pw_ie->ie_wength = 0;
	}
	if (pwiv->assocwesp_idx != MWIFIEX_AUTO_IDX_MASK) {
		aw_ie = kmawwoc(sizeof(stwuct mwifiex_ie), GFP_KEWNEW);
		if (!aw_ie) {
			wet = -ENOMEM;
			goto done;
		}
		aw_ie->ie_index = cpu_to_we16(pwiv->assocwesp_idx);
		aw_ie->mgmt_subtype_mask = cpu_to_we16(MWIFIEX_DEWETE_MASK);
		aw_ie->ie_wength = 0;
	}

	if (beacon_ie || pw_ie || aw_ie)
		wet = mwifiex_update_uap_custom_ie(pwiv,
						   beacon_ie, &pwiv->beacon_idx,
						   pw_ie, &pwiv->pwobewesp_idx,
						   aw_ie, &pwiv->assocwesp_idx);

done:
	kfwee(gen_ie);
	kfwee(beacon_ie);
	kfwee(pw_ie);
	kfwee(aw_ie);

	wetuwn wet;
}
