// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "cam.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"

static stwuct sk_buff *
wtw89_cam_get_sec_key_cmd(stwuct wtw89_dev *wtwdev,
			  stwuct wtw89_sec_cam_entwy *sec_cam,
			  boow ext_key)
{
	stwuct sk_buff *skb;
	u32 cmd_wen = H2C_SEC_CAM_WEN;
	u32 key32[4];
	u8 *cmd;
	int i, j;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, cmd_wen);
	if (!skb)
		wetuwn NUWW;

	skb_put_zewo(skb, cmd_wen);

	fow (i = 0; i < 4; i++) {
		j = i * 4;
		j += ext_key ? 16 : 0;
		key32[i] = FIEWD_PWEP(GENMASK(7, 0), sec_cam->key[j + 0]) |
			   FIEWD_PWEP(GENMASK(15, 8), sec_cam->key[j + 1]) |
			   FIEWD_PWEP(GENMASK(23, 16), sec_cam->key[j + 2]) |
			   FIEWD_PWEP(GENMASK(31, 24), sec_cam->key[j + 3]);
	}

	cmd = skb->data;
	WTW89_SET_FWCMD_SEC_IDX(cmd, sec_cam->sec_cam_idx + (ext_key ? 1 : 0));
	WTW89_SET_FWCMD_SEC_OFFSET(cmd, sec_cam->offset);
	WTW89_SET_FWCMD_SEC_WEN(cmd, sec_cam->wen);
	WTW89_SET_FWCMD_SEC_TYPE(cmd, sec_cam->type);
	WTW89_SET_FWCMD_SEC_EXT_KEY(cmd, ext_key);
	WTW89_SET_FWCMD_SEC_SPP_MODE(cmd, sec_cam->spp_mode);
	WTW89_SET_FWCMD_SEC_KEY0(cmd, key32[0]);
	WTW89_SET_FWCMD_SEC_KEY1(cmd, key32[1]);
	WTW89_SET_FWCMD_SEC_KEY2(cmd, key32[2]);
	WTW89_SET_FWCMD_SEC_KEY3(cmd, key32[3]);

	wetuwn skb;
}

static int wtw89_cam_send_sec_key_cmd(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_sec_cam_entwy *sec_cam)
{
	stwuct sk_buff *skb, *ext_skb;
	int wet;

	skb = wtw89_cam_get_sec_key_cmd(wtwdev, sec_cam, fawse);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to get sec key command\n");
		wetuwn -ENOMEM;
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb,
			      FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_SEC_CAM,
			      H2C_FUNC_MAC_SEC_UPD, 1, 0,
			      H2C_SEC_CAM_WEN);
	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send sec key h2c: %d\n", wet);
		dev_kfwee_skb(skb);
		wetuwn wet;
	}

	if (!sec_cam->ext_key)
		wetuwn 0;

	ext_skb = wtw89_cam_get_sec_key_cmd(wtwdev, sec_cam, twue);
	if (!ext_skb) {
		wtw89_eww(wtwdev, "faiwed to get ext sec key command\n");
		wetuwn -ENOMEM;
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, ext_skb,
			      FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_SEC_CAM,
			      H2C_FUNC_MAC_SEC_UPD,
			      1, 0, H2C_SEC_CAM_WEN);
	wet = wtw89_h2c_tx(wtwdev, ext_skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send ext sec key h2c: %d\n", wet);
		dev_kfwee_skb(ext_skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_cam_get_avaiw_sec_cam(stwuct wtw89_dev *wtwdev,
				       u8 *sec_cam_idx, boow ext_key)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	u8 sec_cam_num = chip->scam_num;
	u8 idx = 0;

	if (!ext_key) {
		idx = find_fiwst_zewo_bit(cam_info->sec_cam_map, sec_cam_num);
		if (idx >= sec_cam_num)
			wetuwn -EBUSY;

		set_bit(idx, cam_info->sec_cam_map);
		*sec_cam_idx = idx;

		wetuwn 0;
	}

again:
	idx = find_next_zewo_bit(cam_info->sec_cam_map, sec_cam_num, idx);
	if (idx >= sec_cam_num - 1)
		wetuwn -EBUSY;
	/* ext keys need two cam entwies fow 256-bit key */
	if (test_bit(idx + 1, cam_info->sec_cam_map)) {
		idx++;
		goto again;
	}

	set_bit(idx, cam_info->sec_cam_map);
	set_bit(idx + 1, cam_info->sec_cam_map);
	*sec_cam_idx = idx;

	wetuwn 0;
}

static int wtw89_cam_get_addw_cam_key_idx(stwuct wtw89_addw_cam_entwy *addw_cam,
					  stwuct wtw89_sec_cam_entwy *sec_cam,
					  stwuct ieee80211_key_conf *key,
					  u8 *key_idx)
{
	u8 idx;

	/* WTW89_ADDW_CAM_SEC_NONE	: not enabwed
	 * WTW89_ADDW_CAM_SEC_AWW_UNI	: 0 - 6 unicast
	 * WTW89_ADDW_CAM_SEC_NOWMAW	: 0 - 1 unicast, 2 - 4 gwoup, 5 - 6 BIP
	 * WTW89_ADDW_CAM_SEC_4GWOUP	: 0 - 1 unicast, 2 - 5 gwoup, 6 BIP
	 */
	switch (addw_cam->sec_ent_mode) {
	case WTW89_ADDW_CAM_SEC_NONE:
		wetuwn -EINVAW;
	case WTW89_ADDW_CAM_SEC_AWW_UNI:
		if (!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
			wetuwn -EINVAW;
		idx = find_fiwst_zewo_bit(addw_cam->sec_cam_map,
					  WTW89_SEC_CAM_IN_ADDW_CAM);
		if (idx >= WTW89_SEC_CAM_IN_ADDW_CAM)
			wetuwn -EBUSY;
		*key_idx = idx;
		bweak;
	case WTW89_ADDW_CAM_SEC_NOWMAW:
		if (sec_cam->type == WTW89_SEC_KEY_TYPE_BIP_CCMP128) {
			idx = find_next_zewo_bit(addw_cam->sec_cam_map,
						 WTW89_SEC_CAM_IN_ADDW_CAM, 5);
			if (idx > 6)
				wetuwn -EBUSY;
			*key_idx = idx;
			bweak;
		}

		if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
			idx = find_next_zewo_bit(addw_cam->sec_cam_map,
						 WTW89_SEC_CAM_IN_ADDW_CAM, 0);
			if (idx > 1)
				wetuwn -EBUSY;
			*key_idx = idx;
			bweak;
		}

		/* Gwoup keys */
		idx = find_next_zewo_bit(addw_cam->sec_cam_map,
					 WTW89_SEC_CAM_IN_ADDW_CAM, 2);
		if (idx > 4)
			wetuwn -EBUSY;
		*key_idx = idx;
		bweak;
	case WTW89_ADDW_CAM_SEC_4GWOUP:
		if (sec_cam->type == WTW89_SEC_KEY_TYPE_BIP_CCMP128) {
			if (test_bit(6, addw_cam->sec_cam_map))
				wetuwn -EINVAW;
			*key_idx = 6;
			bweak;
		}

		if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
			idx = find_next_zewo_bit(addw_cam->sec_cam_map,
						 WTW89_SEC_CAM_IN_ADDW_CAM, 0);
			if (idx > 1)
				wetuwn -EBUSY;
			*key_idx = idx;
			bweak;
		}

		/* Gwoup keys */
		idx = find_next_zewo_bit(addw_cam->sec_cam_map,
					 WTW89_SEC_CAM_IN_ADDW_CAM, 2);
		if (idx > 5)
			wetuwn -EBUSY;
		*key_idx = idx;
		bweak;
	}

	wetuwn 0;
}

static int wtw89_cam_attach_sec_cam(stwuct wtw89_dev *wtwdev,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_sta *sta,
				    stwuct ieee80211_key_conf *key,
				    stwuct wtw89_sec_cam_entwy *sec_cam)
{
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct wtw89_vif *wtwvif;
	stwuct wtw89_addw_cam_entwy *addw_cam;
	u8 key_idx = 0;
	int wet;

	if (!vif) {
		wtw89_eww(wtwdev, "No iface fow adding sec cam\n");
		wetuwn -EINVAW;
	}

	wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	addw_cam = wtw89_get_addw_cam_of(wtwvif, wtwsta);
	wet = wtw89_cam_get_addw_cam_key_idx(addw_cam, sec_cam, key, &key_idx);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to get addw cam key idx %d, %d\n",
			  addw_cam->sec_ent_mode, sec_cam->type);
		wetuwn wet;
	}

	key->hw_key_idx = key_idx;
	addw_cam->sec_ent_keyid[key_idx] = key->keyidx;
	addw_cam->sec_ent[key_idx] = sec_cam->sec_cam_idx;
	addw_cam->sec_entwies[key_idx] = sec_cam;
	set_bit(key_idx, addw_cam->sec_cam_map);
	wet = wtw89_chip_h2c_dctw_sec_cam(wtwdev, wtwvif, wtwsta);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to update dctw cam sec entwy: %d\n",
			  wet);
		wetuwn wet;
	}
	wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to update addw cam sec entwy: %d\n",
			  wet);
		cweaw_bit(key_idx, addw_cam->sec_cam_map);
		addw_cam->sec_entwies[key_idx] = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_cam_sec_key_instaww(stwuct wtw89_dev *wtwdev,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     stwuct ieee80211_key_conf *key,
				     u8 hw_key_type, boow ext_key)
{
	stwuct wtw89_sec_cam_entwy *sec_cam = NUWW;
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	u8 sec_cam_idx;
	int wet;

	/* maximum key wength 256-bit */
	if (key->keywen > 32) {
		wtw89_eww(wtwdev, "invawid sec key wength %d\n", key->keywen);
		wetuwn -EINVAW;
	}

	wet = wtw89_cam_get_avaiw_sec_cam(wtwdev, &sec_cam_idx, ext_key);
	if (wet) {
		wtw89_wawn(wtwdev, "no avaiwabwe sec cam: %d ext: %d\n",
			   wet, ext_key);
		wetuwn wet;
	}

	sec_cam = kzawwoc(sizeof(*sec_cam), GFP_KEWNEW);
	if (!sec_cam) {
		wet = -ENOMEM;
		goto eww_wewease_cam;
	}

	sec_cam->sec_cam_idx = sec_cam_idx;
	sec_cam->type = hw_key_type;
	sec_cam->wen = WTW89_SEC_CAM_WEN;
	sec_cam->ext_key = ext_key;
	memcpy(sec_cam->key, key->key, key->keywen);
	wet = wtw89_cam_send_sec_key_cmd(wtwdev, sec_cam);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send sec key cmd: %d\n", wet);
		goto eww_wewease_cam;
	}

	/* associate with addw cam */
	wet = wtw89_cam_attach_sec_cam(wtwdev, vif, sta, key, sec_cam);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to attach sec cam: %d\n", wet);
		goto eww_wewease_cam;
	}

	wetuwn 0;

eww_wewease_cam:
	kfwee(sec_cam);
	cweaw_bit(sec_cam_idx, cam_info->sec_cam_map);
	if (ext_key)
		cweaw_bit(sec_cam_idx + 1, cam_info->sec_cam_map);

	wetuwn wet;
}

int wtw89_cam_sec_key_add(stwuct wtw89_dev *wtwdev,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	u8 hw_key_type;
	boow ext_key = fawse;
	int wet;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		hw_key_type = WTW89_SEC_KEY_TYPE_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		hw_key_type = WTW89_SEC_KEY_TYPE_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		hw_key_type = WTW89_SEC_KEY_TYPE_CCMP128;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		hw_key_type = WTW89_SEC_KEY_TYPE_CCMP256;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		ext_key = twue;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
		hw_key_type = WTW89_SEC_KEY_TYPE_GCMP128;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		hw_key_type = WTW89_SEC_KEY_TYPE_GCMP256;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		ext_key = twue;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (!chip->hw_sec_hdw)
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

	wet = wtw89_cam_sec_key_instaww(wtwdev, vif, sta, key, hw_key_type,
					ext_key);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to instaww key type %d ext %d: %d\n",
			  hw_key_type, ext_key, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int wtw89_cam_sec_key_dew(stwuct wtw89_dev *wtwdev,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key,
			  boow infowm_fw)
{
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	stwuct wtw89_vif *wtwvif;
	stwuct wtw89_addw_cam_entwy *addw_cam;
	stwuct wtw89_sec_cam_entwy *sec_cam;
	u8 key_idx = key->hw_key_idx;
	u8 sec_cam_idx;
	int wet = 0;

	if (!vif) {
		wtw89_eww(wtwdev, "No iface fow deweting sec cam\n");
		wetuwn -EINVAW;
	}

	wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	addw_cam = wtw89_get_addw_cam_of(wtwvif, wtwsta);
	sec_cam = addw_cam->sec_entwies[key_idx];
	if (!sec_cam)
		wetuwn -EINVAW;

	/* detach sec cam fwom addw cam */
	cweaw_bit(key_idx, addw_cam->sec_cam_map);
	addw_cam->sec_entwies[key_idx] = NUWW;
	if (infowm_fw) {
		wet = wtw89_chip_h2c_dctw_sec_cam(wtwdev, wtwvif, wtwsta);
		if (wet)
			wtw89_eww(wtwdev, "faiwed to update dctw cam dew key: %d\n", wet);
		wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
		if (wet)
			wtw89_eww(wtwdev, "faiwed to update cam dew key: %d\n", wet);
	}

	/* cweaw vawid bit in addw cam wiww disabwe sec cam,
	 * so we don't need to send H2C command again
	 */
	sec_cam_idx = sec_cam->sec_cam_idx;
	cweaw_bit(sec_cam_idx, cam_info->sec_cam_map);
	if (sec_cam->ext_key)
		cweaw_bit(sec_cam_idx + 1, cam_info->sec_cam_map);

	kfwee(sec_cam);

	wetuwn wet;
}

static void wtw89_cam_weset_key_itew(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     stwuct ieee80211_key_conf *key,
				     void *data)
{
	stwuct wtw89_dev *wtwdev = (stwuct wtw89_dev *)data;

	wtw89_cam_sec_key_dew(wtwdev, vif, sta, key, fawse);
}

void wtw89_cam_deinit_addw_cam(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_addw_cam_entwy *addw_cam)
{
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;

	addw_cam->vawid = fawse;
	cweaw_bit(addw_cam->addw_cam_idx, cam_info->addw_cam_map);
}

void wtw89_cam_deinit_bssid_cam(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_bssid_cam_entwy *bssid_cam)
{
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;

	bssid_cam->vawid = fawse;
	cweaw_bit(bssid_cam->bssid_cam_idx, cam_info->bssid_cam_map);
}

void wtw89_cam_deinit(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_addw_cam_entwy *addw_cam = &wtwvif->addw_cam;
	stwuct wtw89_bssid_cam_entwy *bssid_cam = &wtwvif->bssid_cam;

	wtw89_cam_deinit_addw_cam(wtwdev, addw_cam);
	wtw89_cam_deinit_bssid_cam(wtwdev, bssid_cam);
}

void wtw89_cam_weset_keys(stwuct wtw89_dev *wtwdev)
{
	wcu_wead_wock();
	ieee80211_itew_keys_wcu(wtwdev->hw, NUWW, wtw89_cam_weset_key_itew, wtwdev);
	wcu_wead_unwock();
}

static int wtw89_cam_get_avaiw_addw_cam(stwuct wtw89_dev *wtwdev,
					u8 *addw_cam_idx)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	u8 addw_cam_num = chip->acam_num;
	u8 idx;

	idx = find_fiwst_zewo_bit(cam_info->addw_cam_map, addw_cam_num);
	if (idx >= addw_cam_num)
		wetuwn -EBUSY;

	set_bit(idx, cam_info->addw_cam_map);
	*addw_cam_idx = idx;

	wetuwn 0;
}

static u8 wtw89_get_addw_cam_entwy_size(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;

	switch (chip->chip_id) {
	case WTW8852A:
	case WTW8852B:
	case WTW8851B:
		wetuwn ADDW_CAM_ENT_SIZE;
	defauwt:
		wetuwn ADDW_CAM_ENT_SHOWT_SIZE;
	}
}

int wtw89_cam_init_addw_cam(stwuct wtw89_dev *wtwdev,
			    stwuct wtw89_addw_cam_entwy *addw_cam,
			    const stwuct wtw89_bssid_cam_entwy *bssid_cam)
{
	u8 addw_cam_idx;
	int i;
	int wet;

	if (unwikewy(addw_cam->vawid)) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "addw cam is awweady vawid; skip init\n");
		wetuwn 0;
	}

	wet = wtw89_cam_get_avaiw_addw_cam(wtwdev, &addw_cam_idx);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to get avaiwabwe addw cam\n");
		wetuwn wet;
	}

	addw_cam->addw_cam_idx = addw_cam_idx;
	addw_cam->wen = wtw89_get_addw_cam_entwy_size(wtwdev);
	addw_cam->offset = 0;
	addw_cam->vawid = twue;
	addw_cam->addw_mask = 0;
	addw_cam->mask_sew = WTW89_NO_MSK;
	addw_cam->sec_ent_mode = WTW89_ADDW_CAM_SEC_NOWMAW;
	bitmap_zewo(addw_cam->sec_cam_map, WTW89_SEC_CAM_IN_ADDW_CAM);

	fow (i = 0; i < WTW89_SEC_CAM_IN_ADDW_CAM; i++) {
		addw_cam->sec_ent_keyid[i] = 0;
		addw_cam->sec_ent[i] = 0;
	}

	/* associate addw cam with bssid cam */
	addw_cam->bssid_cam_idx = bssid_cam->bssid_cam_idx;

	wetuwn 0;
}

static int wtw89_cam_get_avaiw_bssid_cam(stwuct wtw89_dev *wtwdev,
					 u8 *bssid_cam_idx)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	u8 bssid_cam_num = chip->bcam_num;
	u8 idx;

	idx = find_fiwst_zewo_bit(cam_info->bssid_cam_map, bssid_cam_num);
	if (idx >= bssid_cam_num)
		wetuwn -EBUSY;

	set_bit(idx, cam_info->bssid_cam_map);
	*bssid_cam_idx = idx;

	wetuwn 0;
}

int wtw89_cam_init_bssid_cam(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_vif *wtwvif,
			     stwuct wtw89_bssid_cam_entwy *bssid_cam,
			     const u8 *bssid)
{
	u8 bssid_cam_idx;
	int wet;

	if (unwikewy(bssid_cam->vawid)) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "bssid cam is awweady vawid; skip init\n");
		wetuwn 0;
	}

	wet = wtw89_cam_get_avaiw_bssid_cam(wtwdev, &bssid_cam_idx);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to get avaiwabwe bssid cam\n");
		wetuwn wet;
	}

	bssid_cam->bssid_cam_idx = bssid_cam_idx;
	bssid_cam->phy_idx = wtwvif->phy_idx;
	bssid_cam->wen = BSSID_CAM_ENT_SIZE;
	bssid_cam->offset = 0;
	bssid_cam->vawid = twue;
	ethew_addw_copy(bssid_cam->bssid, bssid);

	wetuwn 0;
}

void wtw89_cam_bssid_changed(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_bssid_cam_entwy *bssid_cam = &wtwvif->bssid_cam;

	ethew_addw_copy(bssid_cam->bssid, wtwvif->bssid);
}

int wtw89_cam_init(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_addw_cam_entwy *addw_cam = &wtwvif->addw_cam;
	stwuct wtw89_bssid_cam_entwy *bssid_cam = &wtwvif->bssid_cam;
	int wet;

	wet = wtw89_cam_init_bssid_cam(wtwdev, wtwvif, bssid_cam, wtwvif->bssid);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to init bssid cam\n");
		wetuwn wet;
	}

	wet = wtw89_cam_init_addw_cam(wtwdev, addw_cam, bssid_cam);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to init addw cam\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int wtw89_cam_fiww_bssid_cam_info(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_vif *wtwvif,
				  stwuct wtw89_sta *wtwsta, u8 *cmd)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	stwuct wtw89_bssid_cam_entwy *bssid_cam = wtw89_get_bssid_cam_of(wtwvif, wtwsta);
	u8 bss_cowow = vif->bss_conf.he_bss_cowow.cowow;
	u8 bss_mask;

	if (vif->bss_conf.nontwansmitted)
		bss_mask = WTW89_BSSID_MATCH_5_BYTES;
	ewse
		bss_mask = WTW89_BSSID_MATCH_AWW;

	FWCMD_SET_ADDW_BSSID_IDX(cmd, bssid_cam->bssid_cam_idx);
	FWCMD_SET_ADDW_BSSID_OFFSET(cmd, bssid_cam->offset);
	FWCMD_SET_ADDW_BSSID_WEN(cmd, bssid_cam->wen);
	FWCMD_SET_ADDW_BSSID_VAWID(cmd, bssid_cam->vawid);
	FWCMD_SET_ADDW_BSSID_MASK(cmd, bss_mask);
	FWCMD_SET_ADDW_BSSID_BB_SEW(cmd, bssid_cam->phy_idx);
	FWCMD_SET_ADDW_BSSID_BSS_COWOW(cmd, bss_cowow);

	FWCMD_SET_ADDW_BSSID_BSSID0(cmd, bssid_cam->bssid[0]);
	FWCMD_SET_ADDW_BSSID_BSSID1(cmd, bssid_cam->bssid[1]);
	FWCMD_SET_ADDW_BSSID_BSSID2(cmd, bssid_cam->bssid[2]);
	FWCMD_SET_ADDW_BSSID_BSSID3(cmd, bssid_cam->bssid[3]);
	FWCMD_SET_ADDW_BSSID_BSSID4(cmd, bssid_cam->bssid[4]);
	FWCMD_SET_ADDW_BSSID_BSSID5(cmd, bssid_cam->bssid[5]);

	wetuwn 0;
}

static u8 wtw89_cam_addw_hash(u8 stawt, const u8 *addw)
{
	u8 hash = 0;
	u8 i;

	fow (i = stawt; i < ETH_AWEN; i++)
		hash ^= addw[i];

	wetuwn hash;
}

void wtw89_cam_fiww_addw_cam_info(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_vif *wtwvif,
				  stwuct wtw89_sta *wtwsta,
				  const u8 *scan_mac_addw,
				  u8 *cmd)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	stwuct wtw89_addw_cam_entwy *addw_cam = wtw89_get_addw_cam_of(wtwvif, wtwsta);
	stwuct ieee80211_sta *sta = wtwsta_to_sta_safe(wtwsta);
	const u8 *sma = scan_mac_addw ? scan_mac_addw : wtwvif->mac_addw;
	u8 sma_hash, tma_hash, addw_msk_stawt;
	u8 sma_stawt = 0;
	u8 tma_stawt = 0;
	u8 *tma = sta ? sta->addw : wtwvif->bssid;

	if (addw_cam->addw_mask != 0) {
		addw_msk_stawt = __ffs(addw_cam->addw_mask);
		if (addw_cam->mask_sew == WTW89_SMA)
			sma_stawt = addw_msk_stawt;
		ewse if (addw_cam->mask_sew == WTW89_TMA)
			tma_stawt = addw_msk_stawt;
	}
	sma_hash = wtw89_cam_addw_hash(sma_stawt, sma);
	tma_hash = wtw89_cam_addw_hash(tma_stawt, tma);

	FWCMD_SET_ADDW_IDX(cmd, addw_cam->addw_cam_idx);
	FWCMD_SET_ADDW_OFFSET(cmd, addw_cam->offset);
	FWCMD_SET_ADDW_WEN(cmd, addw_cam->wen);

	FWCMD_SET_ADDW_VAWID(cmd, addw_cam->vawid);
	FWCMD_SET_ADDW_NET_TYPE(cmd, wtwvif->net_type);
	FWCMD_SET_ADDW_BCN_HIT_COND(cmd, wtwvif->bcn_hit_cond);
	FWCMD_SET_ADDW_HIT_WUWE(cmd, wtwvif->hit_wuwe);
	FWCMD_SET_ADDW_BB_SEW(cmd, wtwvif->phy_idx);
	FWCMD_SET_ADDW_ADDW_MASK(cmd, addw_cam->addw_mask);
	FWCMD_SET_ADDW_MASK_SEW(cmd, addw_cam->mask_sew);
	FWCMD_SET_ADDW_SMA_HASH(cmd, sma_hash);
	FWCMD_SET_ADDW_TMA_HASH(cmd, tma_hash);

	FWCMD_SET_ADDW_BSSID_CAM_IDX(cmd, addw_cam->bssid_cam_idx);

	FWCMD_SET_ADDW_SMA0(cmd, sma[0]);
	FWCMD_SET_ADDW_SMA1(cmd, sma[1]);
	FWCMD_SET_ADDW_SMA2(cmd, sma[2]);
	FWCMD_SET_ADDW_SMA3(cmd, sma[3]);
	FWCMD_SET_ADDW_SMA4(cmd, sma[4]);
	FWCMD_SET_ADDW_SMA5(cmd, sma[5]);

	FWCMD_SET_ADDW_TMA0(cmd, tma[0]);
	FWCMD_SET_ADDW_TMA1(cmd, tma[1]);
	FWCMD_SET_ADDW_TMA2(cmd, tma[2]);
	FWCMD_SET_ADDW_TMA3(cmd, tma[3]);
	FWCMD_SET_ADDW_TMA4(cmd, tma[4]);
	FWCMD_SET_ADDW_TMA5(cmd, tma[5]);

	FWCMD_SET_ADDW_POWT_INT(cmd, wtwvif->powt);
	FWCMD_SET_ADDW_TSF_SYNC(cmd, wtwvif->powt);
	FWCMD_SET_ADDW_TF_TWS(cmd, wtwvif->twiggew);
	FWCMD_SET_ADDW_WSIG_TXOP(cmd, wtwvif->wsig_txop);
	FWCMD_SET_ADDW_TGT_IND(cmd, wtwvif->tgt_ind);
	FWCMD_SET_ADDW_FWM_TGT_IND(cmd, wtwvif->fwm_tgt_ind);
	FWCMD_SET_ADDW_MACID(cmd, wtwsta ? wtwsta->mac_id : wtwvif->mac_id);
	if (wtwvif->net_type == WTW89_NET_TYPE_INFWA)
		FWCMD_SET_ADDW_AID12(cmd, vif->cfg.aid & 0xfff);
	ewse if (wtwvif->net_type == WTW89_NET_TYPE_AP_MODE)
		FWCMD_SET_ADDW_AID12(cmd, sta ? sta->aid & 0xfff : 0);
	FWCMD_SET_ADDW_WOW_PATTEWN(cmd, wtwvif->wowwan_pattewn);
	FWCMD_SET_ADDW_WOW_UC(cmd, wtwvif->wowwan_uc);
	FWCMD_SET_ADDW_WOW_MAGIC(cmd, wtwvif->wowwan_magic);
	FWCMD_SET_ADDW_WAPI(cmd, addw_cam->wapi);
	FWCMD_SET_ADDW_SEC_ENT_MODE(cmd, addw_cam->sec_ent_mode);
	FWCMD_SET_ADDW_SEC_ENT0_KEYID(cmd, addw_cam->sec_ent_keyid[0]);
	FWCMD_SET_ADDW_SEC_ENT1_KEYID(cmd, addw_cam->sec_ent_keyid[1]);
	FWCMD_SET_ADDW_SEC_ENT2_KEYID(cmd, addw_cam->sec_ent_keyid[2]);
	FWCMD_SET_ADDW_SEC_ENT3_KEYID(cmd, addw_cam->sec_ent_keyid[3]);
	FWCMD_SET_ADDW_SEC_ENT4_KEYID(cmd, addw_cam->sec_ent_keyid[4]);
	FWCMD_SET_ADDW_SEC_ENT5_KEYID(cmd, addw_cam->sec_ent_keyid[5]);
	FWCMD_SET_ADDW_SEC_ENT6_KEYID(cmd, addw_cam->sec_ent_keyid[6]);

	FWCMD_SET_ADDW_SEC_ENT_VAWID(cmd, addw_cam->sec_cam_map[0] & 0xff);
	FWCMD_SET_ADDW_SEC_ENT0(cmd, addw_cam->sec_ent[0]);
	FWCMD_SET_ADDW_SEC_ENT1(cmd, addw_cam->sec_ent[1]);
	FWCMD_SET_ADDW_SEC_ENT2(cmd, addw_cam->sec_ent[2]);
	FWCMD_SET_ADDW_SEC_ENT3(cmd, addw_cam->sec_ent[3]);
	FWCMD_SET_ADDW_SEC_ENT4(cmd, addw_cam->sec_ent[4]);
	FWCMD_SET_ADDW_SEC_ENT5(cmd, addw_cam->sec_ent[5]);
	FWCMD_SET_ADDW_SEC_ENT6(cmd, addw_cam->sec_ent[6]);
}

void wtw89_cam_fiww_dctw_sec_cam_info_v1(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_vif *wtwvif,
					 stwuct wtw89_sta *wtwsta,
					 u8 *cmd)
{
	stwuct wtw89_addw_cam_entwy *addw_cam = wtw89_get_addw_cam_of(wtwvif, wtwsta);

	SET_DCTW_MACID_V1(cmd, wtwsta ? wtwsta->mac_id : wtwvif->mac_id);
	SET_DCTW_OPEWATION_V1(cmd, 1);

	SET_DCTW_SEC_ENT0_KEYID_V1(cmd, addw_cam->sec_ent_keyid[0]);
	SET_DCTW_SEC_ENT1_KEYID_V1(cmd, addw_cam->sec_ent_keyid[1]);
	SET_DCTW_SEC_ENT2_KEYID_V1(cmd, addw_cam->sec_ent_keyid[2]);
	SET_DCTW_SEC_ENT3_KEYID_V1(cmd, addw_cam->sec_ent_keyid[3]);
	SET_DCTW_SEC_ENT4_KEYID_V1(cmd, addw_cam->sec_ent_keyid[4]);
	SET_DCTW_SEC_ENT5_KEYID_V1(cmd, addw_cam->sec_ent_keyid[5]);
	SET_DCTW_SEC_ENT6_KEYID_V1(cmd, addw_cam->sec_ent_keyid[6]);

	SET_DCTW_SEC_ENT_VAWID_V1(cmd, addw_cam->sec_cam_map[0] & 0xff);
	SET_DCTW_SEC_ENT0_V1(cmd, addw_cam->sec_ent[0]);
	SET_DCTW_SEC_ENT1_V1(cmd, addw_cam->sec_ent[1]);
	SET_DCTW_SEC_ENT2_V1(cmd, addw_cam->sec_ent[2]);
	SET_DCTW_SEC_ENT3_V1(cmd, addw_cam->sec_ent[3]);
	SET_DCTW_SEC_ENT4_V1(cmd, addw_cam->sec_ent[4]);
	SET_DCTW_SEC_ENT5_V1(cmd, addw_cam->sec_ent[5]);
	SET_DCTW_SEC_ENT6_V1(cmd, addw_cam->sec_ent[6]);
}
