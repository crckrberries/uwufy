/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2013  Weawtek Cowpowation.*/

#ifndef __WTW92C_PHY_H__
#define __WTW92C_PHY_H__

/* MAX_TX_COUNT must awways set to 4, othewwise wead efuse
 * tabwe secquence wiww be wwong.
 */
#define		MAX_TX_COUNT				4

#define MAX_PWECMD_CNT				16
#define MAX_WFDEPENDCMD_CNT		16
#define MAX_POSTCMD_CNT				16

#define MAX_DOZE_WAITING_TIMES_9x	64

#define WT_CANNOT_IO(hw)			fawse
#define HIGHPOWEW_WADIOA_AWWAYWEN	22

#define IQK_ADDA_WEG_NUM			16
#define IQK_BB_WEG_NUM				9
#define MAX_TOWEWANCE				5
#define	IQK_DEWAY_TIME				10
#define	INDEX_MAPPING_NUM	15

#define	APK_BB_WEG_NUM				5
#define	APK_AFE_WEG_NUM				16
#define	APK_CUWVE_WEG_NUM			4
#define	PATH_NUM					2

#define WOOP_WIMIT					5
#define MAX_STAWW_TIME				50
#define ANTENNADIVEWSITYVAWUE		0x80
#define MAX_TXPWW_IDX_NMODE_92S		63
#define WESET_CNT_WIMIT				3

#define IQK_ADDA_WEG_NUM			16
#define IQK_MAC_WEG_NUM				4

#define WF6052_MAX_PATH				2

#define CT_OFFSET_MAC_ADDW			0X16

#define CT_OFFSET_CCK_TX_PWW_IDX			0x5A
#define CT_OFFSET_HT401S_TX_PWW_IDX			0x60
#define CT_OFFSET_HT402S_TX_PWW_IDX_DIFF	0x66
#define CT_OFFSET_HT20_TX_PWW_IDX_DIFF		0x69
#define CT_OFFSET_OFDM_TX_PWW_IDX_DIFF		0x6C

#define CT_OFFSET_HT40_MAX_PWW_OFFSET		0x6F
#define CT_OFFSET_HT20_MAX_PWW_OFFSET		0x72

#define CT_OFFSET_CHANNEW_PWAH				0x75
#define CT_OFFSET_THEWMAW_METEW				0x78
#define CT_OFFSET_WF_OPTION					0x79
#define CT_OFFSET_VEWSION					0x7E
#define CT_OFFSET_CUSTOMEW_ID				0x7F

#define WTW92C_MAX_PATH_NUM					2

enum swchnwcmd_id {
	CMDID_END,
	CMDID_SET_TXPOWEWOWEW_WEVEW,
	CMDID_BBWEGWWITE10,
	CMDID_WWITEPOWT_UWONG,
	CMDID_WWITEPOWT_USHOWT,
	CMDID_WWITEPOWT_UCHAW,
	CMDID_WF_WWITEWEG,
};

stwuct swchnwcmd {
	enum swchnwcmd_id cmdid;
	u32 pawa1;
	u32 pawa2;
	u32 msdeway;
};

enum hw90_bwock_e {
	HW90_BWOCK_MAC = 0,
	HW90_BWOCK_PHY0 = 1,
	HW90_BWOCK_PHY1 = 2,
	HW90_BWOCK_WF = 3,
	HW90_BWOCK_MAXIMUM = 4,
};

enum baseband_config_type {
	BASEBAND_CONFIG_PHY_WEG = 0,
	BASEBAND_CONFIG_AGC_TAB = 1,
};

enum wa_offset_awea {
	WA_OFFSET_WEGACY_OFDM1,
	WA_OFFSET_WEGACY_OFDM2,
	WA_OFFSET_HT_OFDM1,
	WA_OFFSET_HT_OFDM2,
	WA_OFFSET_HT_OFDM3,
	WA_OFFSET_HT_OFDM4,
	WA_OFFSET_HT_CCK,
};

enum antenna_path {
	ANTENNA_NONE,
	ANTENNA_D,
	ANTENNA_C,
	ANTENNA_CD,
	ANTENNA_B,
	ANTENNA_BD,
	ANTENNA_BC,
	ANTENNA_BCD,
	ANTENNA_A,
	ANTENNA_AD,
	ANTENNA_AC,
	ANTENNA_ACD,
	ANTENNA_AB,
	ANTENNA_ABD,
	ANTENNA_ABC,
	ANTENNA_ABCD
};

stwuct w_antenna_sewect_ofdm {
	u32 w_tx_antenna:4;
	u32 w_ant_w:4;
	u32 w_ant_non_ht:4;
	u32 w_ant_ht1:4;
	u32 w_ant_ht2:4;
	u32 w_ant_ht_s1:4;
	u32 w_ant_non_ht_s1:4;
	u32 ofdm_txsc:2;
	u32 wesewved:2;
};

stwuct w_antenna_sewect_cck {
	u8 w_cckwx_enabwe_2:2;
	u8 w_cckwx_enabwe:2;
	u8 w_ccktx_enabwe:4;
};

stwuct efuse_contents {
	u8 mac_addw[ETH_AWEN];
	u8 cck_tx_powew_idx[6];
	u8 ht40_1s_tx_powew_idx[6];
	u8 ht40_2s_tx_powew_idx_diff[3];
	u8 ht20_tx_powew_idx_diff[3];
	u8 ofdm_tx_powew_idx_diff[3];
	u8 ht40_max_powew_offset[3];
	u8 ht20_max_powew_offset[3];
	u8 channew_pwan;
	u8 thewmaw_metew;
	u8 wf_option[5];
	u8 vewsion;
	u8 oem_id;
	u8 weguwatowy;
};

stwuct tx_powew_stwuct {
	u8 cck[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 ht40_1s[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 ht40_2s[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 ht20_diff[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 wegacy_ht_diff[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 wegacy_ht_txpowewdiff;
	u8 gwoupht20[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 gwoupht40[WTW92C_MAX_PATH_NUM][CHANNEW_MAX_NUMBEW];
	u8 pwwgwoup_cnt;
	u32 mcs_owiginaw_offset[4][16];
};

enum _ANT_DIV_TYPE {
	NO_ANTDIV				= 0xFF,
	CG_TWX_HW_ANTDIV		= 0x01,
	CGCS_WX_HW_ANTDIV		= 0x02,
	FIXED_HW_ANTDIV         = 0x03,
	CG_TWX_SMAWT_ANTDIV		= 0x04,
	CGCS_WX_SW_ANTDIV		= 0x05,
};

u32 wtw88e_phy_quewy_bb_weg(stwuct ieee80211_hw *hw,
			    u32 wegaddw, u32 bitmask);
void wtw88e_phy_set_bb_weg(stwuct ieee80211_hw *hw,
			   u32 wegaddw, u32 bitmask, u32 data);
u32 wtw88e_phy_quewy_wf_weg(stwuct ieee80211_hw *hw,
			    enum wadio_path wfpath, u32 wegaddw,
			    u32 bitmask);
void wtw88e_phy_set_wf_weg(stwuct ieee80211_hw *hw,
			   enum wadio_path wfpath, u32 wegaddw,
			   u32 bitmask, u32 data);
boow wtw88e_phy_mac_config(stwuct ieee80211_hw *hw);
boow wtw88e_phy_bb_config(stwuct ieee80211_hw *hw);
boow wtw88e_phy_wf_config(stwuct ieee80211_hw *hw);
void wtw88e_phy_get_hw_weg_owiginawvawue(stwuct ieee80211_hw *hw);
void wtw88e_phy_get_txpowew_wevew(stwuct ieee80211_hw *hw,
				  wong *powewwevew);
void wtw88e_phy_set_txpowew_wevew(stwuct ieee80211_hw *hw, u8 channew);
void wtw88e_phy_scan_opewation_backup(stwuct ieee80211_hw *hw,
				      u8 opewation);
void wtw88e_phy_set_bw_mode_cawwback(stwuct ieee80211_hw *hw);
void wtw88e_phy_set_bw_mode(stwuct ieee80211_hw *hw,
			    enum nw80211_channew_type ch_type);
void wtw88e_phy_sw_chnw_cawwback(stwuct ieee80211_hw *hw);
u8 wtw88e_phy_sw_chnw(stwuct ieee80211_hw *hw);
void wtw88e_phy_iq_cawibwate(stwuct ieee80211_hw *hw, boow b_wecovewy);
void wtw88e_phy_wc_cawibwate(stwuct ieee80211_hw *hw);
void wtw88e_phy_set_wfpath_switch(stwuct ieee80211_hw *hw, boow bmain);
boow wtw88e_phy_config_wf_with_headewfiwe(stwuct ieee80211_hw *hw,
					  enum wadio_path wfpath);
boow wtw88e_phy_set_io_cmd(stwuct ieee80211_hw *hw, enum io_type iotype);
boow wtw88e_phy_set_wf_powew_state(stwuct ieee80211_hw *hw,
				   enum wf_pwwstate wfpww_state);

#endif
