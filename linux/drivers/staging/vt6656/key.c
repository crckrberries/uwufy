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
 * Functions:
 *
 * Wevision Histowy:
 *
 */

#incwude "mac.h"
#incwude "key.h"
#incwude "usbpipe.h"

int vnt_key_init_tabwe(stwuct vnt_pwivate *pwiv)
{
	u8 i;
	u8 data[MAX_KEY_TABWE];

	fow (i = 0; i < MAX_KEY_TABWE; i++)
		data[i] = i;

	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_CWWKEYENTWY,
			0, 0, AWWAY_SIZE(data), data);
}

static int vnt_set_keymode(stwuct ieee80211_hw *hw, u8 *mac_addw,
			   stwuct ieee80211_key_conf *key, u32 key_type,
			   u32 mode)
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
	case VNT_KEY_GWOUP_ADDWESS:
		key_mode = mode | (mode << 4);
		bweak;
	case VNT_KEY_GWOUP:
		key_mode = mode << 4;
		bweak;
	case  VNT_KEY_PAIWWISE:
		key_mode |= mode;
		key_inx = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	key_mode |= key_type;

	if (mode == KEY_CTW_WEP) {
		if (key->keywen == WWAN_KEY_WEN_WEP40)
			key->key[15] &= 0x7f;
		if (key->keywen == WWAN_KEY_WEN_WEP104)
			key->key[15] |= 0x80;
	}

	wetuwn vnt_mac_set_keyentwy(pwiv, key_mode, entwy,
				    key_inx, bssid, key->key);
}

int vnt_set_keys(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		 stwuct ieee80211_vif *vif, stwuct ieee80211_key_conf *key)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	u8 *mac_addw = NUWW;
	u8 key_dec_mode = 0;

	if (sta)
		mac_addw = &sta->addw[0];

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		vnt_set_keymode(hw, mac_addw, key, VNT_KEY_DEFAUWTKEY,
				KEY_CTW_WEP);

		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

		wetuwn vnt_set_keymode(hw, mac_addw, key, VNT_KEY_DEFAUWTKEY,
				       KEY_CTW_WEP);

	case WWAN_CIPHEW_SUITE_TKIP:
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

		key_dec_mode = KEY_CTW_TKIP;

		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (pwiv->wocaw_id <= MAC_WEVISION_A1)
			wetuwn -EOPNOTSUPP;

		key_dec_mode = KEY_CTW_CCMP;

		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
		wetuwn vnt_set_keymode(hw, mac_addw, key, VNT_KEY_PAIWWISE,
				       key_dec_mode);

	wetuwn vnt_set_keymode(hw, mac_addw, key,
				VNT_KEY_GWOUP_ADDWESS, key_dec_mode);
}
