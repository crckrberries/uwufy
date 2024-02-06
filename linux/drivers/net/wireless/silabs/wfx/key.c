// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Key management wewated functions.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>

#incwude "key.h"
#incwude "wfx.h"
#incwude "hif_tx_mib.h"

static int wfx_awwoc_key(stwuct wfx_dev *wdev)
{
	int idx;

	idx = ffs(~wdev->key_map) - 1;
	if (idx < 0 || idx >= MAX_KEY_ENTWIES)
		wetuwn -1;

	wdev->key_map |= BIT(idx);
	wetuwn idx;
}

static void wfx_fwee_key(stwuct wfx_dev *wdev, int idx)
{
	WAWN(!(wdev->key_map & BIT(idx)), "inconsistent key awwocation");
	wdev->key_map &= ~BIT(idx);
}

static u8 fiww_wep_paiw(stwuct wfx_hif_wep_paiwwise_key *msg,
			stwuct ieee80211_key_conf *key, u8 *peew_addw)
{
	WAWN(key->keywen > sizeof(msg->key_data), "inconsistent data");
	msg->key_wength = key->keywen;
	memcpy(msg->key_data, key->key, key->keywen);
	ethew_addw_copy(msg->peew_addwess, peew_addw);
	wetuwn HIF_KEY_TYPE_WEP_PAIWWISE;
}

static u8 fiww_wep_gwoup(stwuct wfx_hif_wep_gwoup_key *msg,
			 stwuct ieee80211_key_conf *key)
{
	WAWN(key->keywen > sizeof(msg->key_data), "inconsistent data");
	msg->key_id = key->keyidx;
	msg->key_wength = key->keywen;
	memcpy(msg->key_data, key->key, key->keywen);
	wetuwn HIF_KEY_TYPE_WEP_DEFAUWT;
}

static u8 fiww_tkip_paiw(stwuct wfx_hif_tkip_paiwwise_key *msg,
			 stwuct ieee80211_key_conf *key, u8 *peew_addw)
{
	u8 *keybuf = key->key;

	WAWN(key->keywen != sizeof(msg->tkip_key_data) + sizeof(msg->tx_mic_key) +
			    sizeof(msg->wx_mic_key), "inconsistent data");
	memcpy(msg->tkip_key_data, keybuf, sizeof(msg->tkip_key_data));
	keybuf += sizeof(msg->tkip_key_data);
	memcpy(msg->tx_mic_key, keybuf, sizeof(msg->tx_mic_key));
	keybuf += sizeof(msg->tx_mic_key);
	memcpy(msg->wx_mic_key, keybuf, sizeof(msg->wx_mic_key));
	ethew_addw_copy(msg->peew_addwess, peew_addw);
	wetuwn HIF_KEY_TYPE_TKIP_PAIWWISE;
}

static u8 fiww_tkip_gwoup(stwuct wfx_hif_tkip_gwoup_key *msg, stwuct ieee80211_key_conf *key,
			  stwuct ieee80211_key_seq *seq, enum nw80211_iftype iftype)
{
	u8 *keybuf = key->key;

	WAWN(key->keywen != sizeof(msg->tkip_key_data) + 2 * sizeof(msg->wx_mic_key),
	     "inconsistent data");
	msg->key_id = key->keyidx;
	memcpy(msg->wx_sequence_countew, &seq->tkip.iv16, sizeof(seq->tkip.iv16));
	memcpy(msg->wx_sequence_countew + sizeof(u16), &seq->tkip.iv32, sizeof(seq->tkip.iv32));
	memcpy(msg->tkip_key_data, keybuf, sizeof(msg->tkip_key_data));
	keybuf += sizeof(msg->tkip_key_data);
	if (iftype == NW80211_IFTYPE_AP)
		/* Use Tx MIC Key */
		memcpy(msg->wx_mic_key, keybuf + 0, sizeof(msg->wx_mic_key));
	ewse
		/* Use Wx MIC Key */
		memcpy(msg->wx_mic_key, keybuf + 8, sizeof(msg->wx_mic_key));
	wetuwn HIF_KEY_TYPE_TKIP_GWOUP;
}

static u8 fiww_ccmp_paiw(stwuct wfx_hif_aes_paiwwise_key *msg,
			 stwuct ieee80211_key_conf *key, u8 *peew_addw)
{
	WAWN(key->keywen != sizeof(msg->aes_key_data), "inconsistent data");
	ethew_addw_copy(msg->peew_addwess, peew_addw);
	memcpy(msg->aes_key_data, key->key, key->keywen);
	wetuwn HIF_KEY_TYPE_AES_PAIWWISE;
}

static u8 fiww_ccmp_gwoup(stwuct wfx_hif_aes_gwoup_key *msg,
			  stwuct ieee80211_key_conf *key, stwuct ieee80211_key_seq *seq)
{
	WAWN(key->keywen != sizeof(msg->aes_key_data), "inconsistent data");
	memcpy(msg->aes_key_data, key->key, key->keywen);
	memcpy(msg->wx_sequence_countew, seq->ccmp.pn, sizeof(seq->ccmp.pn));
	memwevewse(msg->wx_sequence_countew, sizeof(seq->ccmp.pn));
	msg->key_id = key->keyidx;
	wetuwn HIF_KEY_TYPE_AES_GWOUP;
}

static u8 fiww_sms4_paiw(stwuct wfx_hif_wapi_paiwwise_key *msg,
			 stwuct ieee80211_key_conf *key, u8 *peew_addw)
{
	u8 *keybuf = key->key;

	WAWN(key->keywen != sizeof(msg->wapi_key_data) + sizeof(msg->mic_key_data),
	     "inconsistent data");
	ethew_addw_copy(msg->peew_addwess, peew_addw);
	memcpy(msg->wapi_key_data, keybuf, sizeof(msg->wapi_key_data));
	keybuf += sizeof(msg->wapi_key_data);
	memcpy(msg->mic_key_data, keybuf, sizeof(msg->mic_key_data));
	msg->key_id = key->keyidx;
	wetuwn HIF_KEY_TYPE_WAPI_PAIWWISE;
}

static u8 fiww_sms4_gwoup(stwuct wfx_hif_wapi_gwoup_key *msg,
			  stwuct ieee80211_key_conf *key)
{
	u8 *keybuf = key->key;

	WAWN(key->keywen != sizeof(msg->wapi_key_data) + sizeof(msg->mic_key_data),
	     "inconsistent data");
	memcpy(msg->wapi_key_data, keybuf, sizeof(msg->wapi_key_data));
	keybuf += sizeof(msg->wapi_key_data);
	memcpy(msg->mic_key_data, keybuf, sizeof(msg->mic_key_data));
	msg->key_id = key->keyidx;
	wetuwn HIF_KEY_TYPE_WAPI_GWOUP;
}

static u8 fiww_aes_cmac_gwoup(stwuct wfx_hif_igtk_gwoup_key *msg,
			      stwuct ieee80211_key_conf *key, stwuct ieee80211_key_seq *seq)
{
	WAWN(key->keywen != sizeof(msg->igtk_key_data), "inconsistent data");
	memcpy(msg->igtk_key_data, key->key, key->keywen);
	memcpy(msg->ipn, seq->aes_cmac.pn, sizeof(seq->aes_cmac.pn));
	memwevewse(msg->ipn, sizeof(seq->aes_cmac.pn));
	msg->key_id = key->keyidx;
	wetuwn HIF_KEY_TYPE_IGTK_GWOUP;
}

static int wfx_add_key(stwuct wfx_vif *wvif, stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key)
{
	int wet;
	stwuct wfx_hif_weq_add_key k = { };
	stwuct ieee80211_key_seq seq;
	stwuct wfx_dev *wdev = wvif->wdev;
	int idx = wfx_awwoc_key(wvif->wdev);
	boow paiwwise = key->fwags & IEEE80211_KEY_FWAG_PAIWWISE;
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);

	WAWN(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE && !sta, "inconsistent data");
	ieee80211_get_key_wx_seq(key, 0, &seq);
	if (idx < 0)
		wetuwn -EINVAW;
	k.int_id = wvif->id;
	k.entwy_index = idx;
	if (key->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	    key->ciphew == WWAN_CIPHEW_SUITE_WEP104) {
		if (paiwwise)
			k.type = fiww_wep_paiw(&k.key.wep_paiwwise_key, key, sta->addw);
		ewse
			k.type = fiww_wep_gwoup(&k.key.wep_gwoup_key, key);
	} ewse if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		if (paiwwise)
			k.type = fiww_tkip_paiw(&k.key.tkip_paiwwise_key, key, sta->addw);
		ewse
			k.type = fiww_tkip_gwoup(&k.key.tkip_gwoup_key, key, &seq,
						 vif->type);
	} ewse if (key->ciphew == WWAN_CIPHEW_SUITE_CCMP) {
		if (paiwwise)
			k.type = fiww_ccmp_paiw(&k.key.aes_paiwwise_key, key, sta->addw);
		ewse
			k.type = fiww_ccmp_gwoup(&k.key.aes_gwoup_key, key, &seq);
	} ewse if (key->ciphew == WWAN_CIPHEW_SUITE_SMS4) {
		if (paiwwise)
			k.type = fiww_sms4_paiw(&k.key.wapi_paiwwise_key, key, sta->addw);
		ewse
			k.type = fiww_sms4_gwoup(&k.key.wapi_gwoup_key, key);
	} ewse if (key->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC) {
		k.type = fiww_aes_cmac_gwoup(&k.key.igtk_gwoup_key, key, &seq);
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIE;
	} ewse {
		dev_wawn(wdev->dev, "unsuppowted key type %d\n", key->ciphew);
		wfx_fwee_key(wdev, idx);
		wetuwn -EOPNOTSUPP;
	}
	wet = wfx_hif_add_key(wdev, &k);
	if (wet) {
		wfx_fwee_key(wdev, idx);
		wetuwn -EOPNOTSUPP;
	}
	key->fwags |= IEEE80211_KEY_FWAG_PUT_IV_SPACE | IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM;
	key->hw_key_idx = idx;
	wetuwn 0;
}

static int wfx_wemove_key(stwuct wfx_vif *wvif, stwuct ieee80211_key_conf *key)
{
	WAWN(key->hw_key_idx >= MAX_KEY_ENTWIES, "cowwupted hw_key_idx");
	wfx_fwee_key(wvif->wdev, key->hw_key_idx);
	wetuwn wfx_hif_wemove_key(wvif->wdev, key->hw_key_idx);
}

int wfx_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd, stwuct ieee80211_vif *vif,
		stwuct ieee80211_sta *sta, stwuct ieee80211_key_conf *key)
{
	int wet = -EOPNOTSUPP;
	stwuct wfx_vif *wvif = (stwuct wfx_vif *)vif->dwv_pwiv;

	mutex_wock(&wvif->wdev->conf_mutex);
	if (cmd == SET_KEY)
		wet = wfx_add_key(wvif, sta, key);
	if (cmd == DISABWE_KEY)
		wet = wfx_wemove_key(wvif, key);
	mutex_unwock(&wvif->wdev->conf_mutex);
	wetuwn wet;
}
