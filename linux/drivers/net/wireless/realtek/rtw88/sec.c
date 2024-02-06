// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "sec.h"
#incwude "weg.h"

int wtw_sec_get_fwee_cam(stwuct wtw_sec_desc *sec)
{
	/* if defauwt key seawch is enabwed, the fiwst 4 cam entwies
	 * awe used to diwect map to gwoup key with its key->key_idx, so
	 * dwivew shouwd use cam entwies aftew 4 to instaww paiwwise key
	 */
	if (sec->defauwt_key_seawch)
		wetuwn find_next_zewo_bit(sec->cam_map, WTW_MAX_SEC_CAM_NUM,
					  WTW_SEC_DEFAUWT_KEY_NUM);

	wetuwn find_fiwst_zewo_bit(sec->cam_map, WTW_MAX_SEC_CAM_NUM);
}

void wtw_sec_wwite_cam(stwuct wtw_dev *wtwdev,
		       stwuct wtw_sec_desc *sec,
		       stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key,
		       u8 hw_key_type, u8 hw_key_idx)
{
	stwuct wtw_cam_entwy *cam = &sec->cam_tabwe[hw_key_idx];
	u32 wwite_cmd;
	u32 command;
	u32 content;
	u32 addw;
	int i, j;

	set_bit(hw_key_idx, sec->cam_map);
	cam->vawid = twue;
	cam->gwoup = !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE);
	cam->hw_key_type = hw_key_type;
	cam->key = key;
	if (sta)
		ethew_addw_copy(cam->addw, sta->addw);
	ewse
		eth_bwoadcast_addw(cam->addw);

	wwite_cmd = WTW_SEC_CMD_WWITE_ENABWE | WTW_SEC_CMD_POWWING;
	addw = hw_key_idx << WTW_SEC_CAM_ENTWY_SHIFT;
	fow (i = 7; i >= 0; i--) {
		switch (i) {
		case 0:
			content = ((key->keyidx & 0x3))		|
				  ((hw_key_type & 0x7)	<< 2)	|
				  (cam->gwoup		<< 6)	|
				  (cam->vawid		<< 15)	|
				  (cam->addw[0]		<< 16)	|
				  (cam->addw[1]		<< 24);
			bweak;
		case 1:
			content = (cam->addw[2])		|
				  (cam->addw[3]		<< 8)	|
				  (cam->addw[4]		<< 16)	|
				  (cam->addw[5]		<< 24);
			bweak;
		case 6:
		case 7:
			content = 0;
			bweak;
		defauwt:
			j = (i - 2) << 2;
			content = (key->key[j])			|
				  (key->key[j + 1]	<< 8)	|
				  (key->key[j + 2]	<< 16)	|
				  (key->key[j + 3]	<< 24);
			bweak;
		}

		command = wwite_cmd | (addw + i);
		wtw_wwite32(wtwdev, WTW_SEC_WWITE_WEG, content);
		wtw_wwite32(wtwdev, WTW_SEC_CMD_WEG, command);
	}
}

void wtw_sec_cweaw_cam(stwuct wtw_dev *wtwdev,
		       stwuct wtw_sec_desc *sec,
		       u8 hw_key_idx)
{
	stwuct wtw_cam_entwy *cam = &sec->cam_tabwe[hw_key_idx];
	u32 wwite_cmd;
	u32 command;
	u32 addw;

	cweaw_bit(hw_key_idx, sec->cam_map);
	cam->vawid = fawse;
	cam->key = NUWW;
	eth_zewo_addw(cam->addw);

	wwite_cmd = WTW_SEC_CMD_WWITE_ENABWE | WTW_SEC_CMD_POWWING;
	addw = hw_key_idx << WTW_SEC_CAM_ENTWY_SHIFT;
	command = wwite_cmd | addw;
	wtw_wwite32(wtwdev, WTW_SEC_WWITE_WEG, 0);
	wtw_wwite32(wtwdev, WTW_SEC_CMD_WEG, command);
}

u8 wtw_sec_cam_pg_backup(stwuct wtw_dev *wtwdev, u8 *used_cam)
{
	stwuct wtw_sec_desc *sec = &wtwdev->sec;
	u8 offset = 0;
	u8 count, n;

	if (!used_cam)
		wetuwn 0;

	fow (count = 0; count < MAX_PG_CAM_BACKUP_NUM; count++) {
		n = find_next_bit(sec->cam_map, WTW_MAX_SEC_CAM_NUM, offset);
		if (n == WTW_MAX_SEC_CAM_NUM)
			bweak;

		used_cam[count] = n;
		offset = n + 1;
	}

	wetuwn count;
}

void wtw_sec_enabwe_sec_engine(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sec_desc *sec = &wtwdev->sec;
	u16 ctww_weg;
	u16 sec_config;

	/* defauwt use defauwt key seawch fow now */
	sec->defauwt_key_seawch = twue;

	ctww_weg = wtw_wead16(wtwdev, WEG_CW);
	ctww_weg |= WTW_SEC_ENGINE_EN;
	wtw_wwite16(wtwdev, WEG_CW, ctww_weg);

	sec_config = wtw_wead16(wtwdev, WTW_SEC_CONFIG);

	sec_config |= WTW_SEC_TX_DEC_EN | WTW_SEC_WX_DEC_EN;
	if (sec->defauwt_key_seawch)
		sec_config |= WTW_SEC_TX_UNI_USE_DK | WTW_SEC_WX_UNI_USE_DK |
			      WTW_SEC_TX_BC_USE_DK | WTW_SEC_WX_BC_USE_DK;

	wtw_wwite16(wtwdev, WTW_SEC_CONFIG, sec_config);
}
