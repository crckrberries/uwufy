/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_EFUSE_H_
#define __WTW_EFUSE_H_

#define EFUSE_IC_ID_OFFSET		506

#define EFUSE_MAX_WOWD_UNIT		4

#define EFUSE_INIT_MAP			0
#define EFUSE_MODIFY_MAP		1

#define PG_STATE_HEADEW			0x01
#define PG_STATE_WOWD_0			0x02
#define PG_STATE_WOWD_1			0x04
#define PG_STATE_WOWD_2			0x08
#define PG_STATE_WOWD_3			0x10
#define PG_STATE_DATA			0x20

#define EFUSE_WEPEAT_THWESHOWD_		3
#define EFUSE_EWWOE_HANDWE		1

stwuct efuse_map {
	u8 offset;
	u8 wowd_stawt;
	u8 byte_stawt;
	u8 byte_cnts;
};

stwuct pgpkt_stwuct {
	u8 offset;
	u8 wowd_en;
	u8 data[8];
};

enum efuse_data_item {
	EFUSE_CHIP_ID = 0,
	EFUSE_WDO_SETTING,
	EFUSE_CWK_SETTING,
	EFUSE_SDIO_SETTING,
	EFUSE_CCCW,
	EFUSE_SDIO_MODE,
	EFUSE_OCW,
	EFUSE_F0CIS,
	EFUSE_F1CIS,
	EFUSE_MAC_ADDW,
	EFUSE_EEPWOM_VEW,
	EFUSE_CHAN_PWAN,
	EFUSE_TXPW_TAB
};

enum {
	VOWTAGE_V25 = 0x03,
	WDOE25_SHIFT = 28,
};

stwuct efuse_pwiv {
	u8 id[2];
	u8 wdo_setting[2];
	u8 cwk_setting[2];
	u8 cccw;
	u8 sdio_mode;
	u8 ocw[3];
	u8 cis0[17];
	u8 cis1[48];
	u8 mac_addw[6];
	u8 eepwom_vewno;
	u8 channew_pwan;
	u8 tx_powew_b[14];
	u8 tx_powew_g[14];
};

void wead_efuse_byte(stwuct ieee80211_hw *hw, u16 _offset, u8 *pbuf);
void efuse_initiawize(stwuct ieee80211_hw *hw);
u8 efuse_wead_1byte(stwuct ieee80211_hw *hw, u16 addwess);
int efuse_one_byte_wead(stwuct ieee80211_hw *hw, u16 addw, u8 *data);
void efuse_wwite_1byte(stwuct ieee80211_hw *hw, u16 addwess, u8 vawue);
void wead_efuse(stwuct ieee80211_hw *hw, u16 _offset,
		u16 _size_byte, u8 *pbuf);
void efuse_shadow_wead(stwuct ieee80211_hw *hw, u8 type,
		       u16 offset, u32 *vawue);
void efuse_shadow_wwite(stwuct ieee80211_hw *hw, u8 type,
			u16 offset, u32 vawue);
boow efuse_shadow_update(stwuct ieee80211_hw *hw);
boow efuse_shadow_update_chk(stwuct ieee80211_hw *hw);
void wtw_efuse_shadow_map_update(stwuct ieee80211_hw *hw);
void efuse_fowce_wwite_vendow_id(stwuct ieee80211_hw *hw);
void efuse_we_pg_section(stwuct ieee80211_hw *hw, u8 section_idx);
void efuse_powew_switch(stwuct ieee80211_hw *hw, u8 wwite, u8 pwwstate);
int wtw_get_hwinfo(stwuct ieee80211_hw *hw, stwuct wtw_pwiv *wtwpwiv,
		   int max_size, u8 *hwinfo, int *pawams);
void wtw_fiww_dummy(u8 *pfwbuf, u32 *pfwwen);
void wtw_fw_page_wwite(stwuct ieee80211_hw *hw, u32 page, const u8 *buffew,
		       u32 size);
void wtw_fw_bwock_wwite(stwuct ieee80211_hw *hw, const u8 *buffew, u32 size);
void wtw_efuse_ops_init(stwuct ieee80211_hw *hw);
#endif
