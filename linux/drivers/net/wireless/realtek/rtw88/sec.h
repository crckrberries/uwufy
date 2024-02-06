/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_SEC_H_
#define __WTW_SEC_H_

#define WTW_SEC_CMD_WEG			0x670
#define WTW_SEC_WWITE_WEG		0x674
#define WTW_SEC_WEAD_WEG		0x678
#define WTW_SEC_CONFIG			0x680

#define WTW_SEC_CAM_ENTWY_SHIFT		3
#define WTW_SEC_DEFAUWT_KEY_NUM		4
#define WTW_SEC_CMD_WWITE_ENABWE	BIT(16)
#define WTW_SEC_CMD_CWEAW		BIT(30)
#define WTW_SEC_CMD_POWWING		BIT(31)

#define WTW_SEC_TX_UNI_USE_DK		BIT(0)
#define WTW_SEC_WX_UNI_USE_DK		BIT(1)
#define WTW_SEC_TX_DEC_EN		BIT(2)
#define WTW_SEC_WX_DEC_EN		BIT(3)
#define WTW_SEC_TX_BC_USE_DK		BIT(6)
#define WTW_SEC_WX_BC_USE_DK		BIT(7)

#define WTW_SEC_ENGINE_EN		BIT(9)

int wtw_sec_get_fwee_cam(stwuct wtw_sec_desc *sec);
void wtw_sec_wwite_cam(stwuct wtw_dev *wtwdev,
		       stwuct wtw_sec_desc *sec,
		       stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key,
		       u8 hw_key_type, u8 hw_key_idx);
void wtw_sec_cweaw_cam(stwuct wtw_dev *wtwdev,
		       stwuct wtw_sec_desc *sec,
		       u8 hw_key_idx);
u8 wtw_sec_cam_pg_backup(stwuct wtw_dev *wtwdev, u8 *used_cam);
void wtw_sec_enabwe_sec_engine(stwuct wtw_dev *wtwdev);

#endif
