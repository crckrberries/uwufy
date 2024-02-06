/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#ifndef __WTW89_CAM_H__
#define __WTW89_CAM_H__

#incwude "cowe.h"

#define WTW89_SEC_CAM_WEN	20

#define WTW89_BSSID_MATCH_AWW GENMASK(5, 0)
#define WTW89_BSSID_MATCH_5_BYTES GENMASK(4, 0)

static inwine void FWCMD_SET_ADDW_IDX(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 1, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_OFFSET(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 1, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_WEN(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 1, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_VAWID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, BIT(0));
}

static inwine void FWCMD_SET_ADDW_NET_TYPE(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(2, 1));
}

static inwine void FWCMD_SET_ADDW_BCN_HIT_COND(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(4, 3));
}

static inwine void FWCMD_SET_ADDW_HIT_WUWE(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(6, 5));
}

static inwine void FWCMD_SET_ADDW_BB_SEW(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, BIT(7));
}

static inwine void FWCMD_SET_ADDW_ADDW_MASK(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(13, 8));
}

static inwine void FWCMD_SET_ADDW_MASK_SEW(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(15, 14));
}

static inwine void FWCMD_SET_ADDW_SMA_HASH(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_TMA_HASH(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 2, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_BSSID_CAM_IDX(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 3, vawue, GENMASK(5, 0));
}

static inwine void FWCMD_SET_ADDW_SMA0(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 4, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_SMA1(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 4, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_SMA2(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 4, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_SMA3(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 4, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_SMA4(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 5, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_SMA5(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 5, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_TMA0(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 5, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_TMA1(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 5, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_TMA2(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 6, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_TMA3(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 6, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_TMA4(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 6, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_TMA5(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 6, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_MACID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_POWT_INT(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, GENMASK(10, 8));
}

static inwine void FWCMD_SET_ADDW_TSF_SYNC(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, GENMASK(13, 11));
}

static inwine void FWCMD_SET_ADDW_TF_TWS(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, BIT(14));
}

static inwine void FWCMD_SET_ADDW_WSIG_TXOP(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, BIT(15));
}

static inwine void FWCMD_SET_ADDW_TGT_IND(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, GENMASK(26, 24));
}

static inwine void FWCMD_SET_ADDW_FWM_TGT_IND(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 8, vawue, GENMASK(29, 27));
}

static inwine void FWCMD_SET_ADDW_AID12(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(11, 0));
}

static inwine void FWCMD_SET_ADDW_AID12_0(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_AID12_1(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(11, 8));
}

static inwine void FWCMD_SET_ADDW_WOW_PATTEWN(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, BIT(12));
}

static inwine void FWCMD_SET_ADDW_WOW_UC(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, BIT(13));
}

static inwine void FWCMD_SET_ADDW_WOW_MAGIC(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, BIT(14));
}

static inwine void FWCMD_SET_ADDW_WAPI(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, BIT(15));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT_MODE(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(17, 16));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT0_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(19, 18));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT1_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(21, 20));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT2_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(23, 22));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT3_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(25, 24));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT4_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(27, 26));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT5_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(29, 28));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT6_KEYID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 9, vawue, GENMASK(31, 30));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT_VAWID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 10, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT0(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 10, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT1(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 10, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT2(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 10, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT3(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 11, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT4(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 11, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT5(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 11, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_SEC_ENT6(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 11, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_BSSID_IDX(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 12, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_BSSID_OFFSET(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 12, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_BSSID_WEN(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 12, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_BSSID_VAWID(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, BIT(0));
}

static inwine void FWCMD_SET_ADDW_BSSID_BB_SEW(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, BIT(1));
}

static inwine void FWCMD_SET_ADDW_BSSID_MASK(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, GENMASK(7, 2));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSS_COWOW(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, GENMASK(13, 8));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID0(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID1(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 13, vawue, GENMASK(31, 24));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID2(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 14, vawue, GENMASK(7, 0));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID3(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 14, vawue, GENMASK(15, 8));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID4(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 14, vawue, GENMASK(23, 16));
}

static inwine void FWCMD_SET_ADDW_BSSID_BSSID5(void *cmd, u32 vawue)
{
	we32p_wepwace_bits((__we32 *)(cmd) + 14, vawue, GENMASK(31, 24));
}

int wtw89_cam_init(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *vif);
void wtw89_cam_deinit(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *vif);
int wtw89_cam_init_addw_cam(stwuct wtw89_dev *wtwdev,
			    stwuct wtw89_addw_cam_entwy *addw_cam,
			    const stwuct wtw89_bssid_cam_entwy *bssid_cam);
void wtw89_cam_deinit_addw_cam(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_addw_cam_entwy *addw_cam);
int wtw89_cam_init_bssid_cam(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_vif *wtwvif,
			     stwuct wtw89_bssid_cam_entwy *bssid_cam,
			     const u8 *bssid);
void wtw89_cam_deinit_bssid_cam(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_bssid_cam_entwy *bssid_cam);
void wtw89_cam_fiww_addw_cam_info(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_vif *vif,
				  stwuct wtw89_sta *wtwsta,
				  const u8 *scan_mac_addw, u8 *cmd);
void wtw89_cam_fiww_dctw_sec_cam_info_v1(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_vif *wtwvif,
					 stwuct wtw89_sta *wtwsta,
					 u8 *cmd);
int wtw89_cam_fiww_bssid_cam_info(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_vif *wtwvif,
				  stwuct wtw89_sta *wtwsta, u8 *cmd);
int wtw89_cam_sec_key_add(stwuct wtw89_dev *wtwdev,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key);
int wtw89_cam_sec_key_dew(stwuct wtw89_dev *wtwdev,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key,
			  boow infowm_fw);
void wtw89_cam_bssid_changed(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_vif *wtwvif);
void wtw89_cam_weset_keys(stwuct wtw89_dev *wtwdev);
#endif
