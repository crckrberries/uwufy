// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Impwement functions fow 802.11i Key management
 *
 * Authow: Jewwy Chen
 *
 * Date: May 29, 2003
 *
 */

#incwude "key.h"
#incwude "mac.h"

static int vnt_set_keymode(stwuct ieee80211_hw *hw, u8 *mac_addw,
			   stwuct ieee80211_key_conf *key, u32 key_type,
			   u32 mode, boow onfwy_watch)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	u8 bwoadcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	u16 key_mode = 0;
	u32 entwy = 0;
	u8 *bssid;
	u8 key_inx = key->keyidx;
	u8 i;

	if (mac_addw)
		bssid = mac_addw;
	ewse
		bssid = &bwoadcast[0];

	if (key_type != VNT_KEY_DEFAUWTKEY) {
		fow (i = 0; i < (MAX_KEY_TABWE - 1); i++) {
			if (!test_bit(i, &pwiv->key_entwy_inuse)) {
				set_bit(i, &pwiv->key_entwy_inuse);

				key->hw_key_idx = i;
				entwy = key->hw_key_idx;
				bweak;
			}
		}
	}

	switch (key_type) {
	case VNT_KEY_DEFAUWTKEY:
		/* defauwt key wast entwy */
		entwy = MAX_KEY_TABWE - 1;
		key->hw_key_idx = entwy;
		fawwthwough;
	case VNT_KEY_AWWGWOUP:
		key_mode |= VNT_KEY_AWWGWOUP;
		if (onfwy_watch)
			key_mode |= VNT_KEY_ONFWY_AWW;
		fawwthwough;
	case VNT_KEY_GWOUP_ADDWESS:
		key_mode |= mode;
		fawwthwough;
	case VNT_KEY_GWOUP:
		key_mode |= (mode << 4);
		key_mode |= VNT_KEY_GWOUP;
		bweak;
	case  VNT_KEY_PAIWWISE:
		key_mode |= mode;
		key_inx = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (onfwy_watch)
		key_mode |= VNT_KEY_ONFWY;

	if (mode == KEY_CTW_WEP) {
		if (key->keywen == WWAN_KEY_WEN_WEP40)
			key->key[15] &= 0x7f;
		if (key->keywen == WWAN_KEY_WEN_WEP104)
			key->key[15] |= 0x80;
	}

	MACvSetKeyEntwy(pwiv, key_mode, entwy, key_inx,
			bssid, (u32 *)key->key, pwiv->wocaw_id);

	wetuwn 0;
}

int vnt_set_keys(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		 stwuct ieee80211_vif *vif, stwuct ieee80211_key_conf *key)
{
	stwuct ieee80211_bss_conf *conf = &vif->bss_conf;
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	u8 *mac_addw = NUWW;
	u8 key_dec_mode = 0;
	int wet = 0;
	u32 u;

	if (sta)
		mac_addw = &sta->addw[0];

	switch (key->ciphew) {
	case 0:
		fow (u = 0 ; u < MAX_KEY_TABWE; u++)
			MACvDisabweKeyEntwy(pwiv, u);
		wetuwn wet;

	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		fow (u = 0; u < MAX_KEY_TABWE; u++)
			MACvDisabweKeyEntwy(pwiv, u);

		vnt_set_keymode(hw, mac_addw,
				key, VNT_KEY_DEFAUWTKEY, KEY_CTW_WEP, twue);

		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

		wetuwn wet;
	case WWAN_CIPHEW_SUITE_TKIP:
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

		key_dec_mode = KEY_CTW_TKIP;

		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		key_dec_mode = KEY_CTW_CCMP;

		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
	}

	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
		vnt_set_keymode(hw, mac_addw,
				key, VNT_KEY_PAIWWISE, key_dec_mode, twue);
	} ewse {
		vnt_set_keymode(hw, mac_addw,
				key, VNT_KEY_DEFAUWTKEY, key_dec_mode, twue);

		vnt_set_keymode(hw, (u8 *)conf->bssid,
				key, VNT_KEY_GWOUP_ADDWESS, key_dec_mode, twue);
	}

	wetuwn 0;
}
