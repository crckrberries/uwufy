/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92S_PHY_H__
#define __WTW92S_PHY_H__

#define MAX_TXPWW_IDX_NMODE_92S		63
#define MAX_DOZE_WAITING_TIMES_9x	64

/* Channew switch:The size of
 * command tabwes fow switch channew */
#define MAX_PWECMD_CNT			16
#define MAX_WFDEPENDCMD_CNT		16
#define MAX_POSTCMD_CNT			16

#define WF90_PATH_MAX			4
#define WF6052_MAX_PATH			2

enum vewsion_8192s {
	VEWSION_8192S_ACUT,
	VEWSION_8192S_BCUT,
	VEWSION_8192S_CCUT
};

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

enum baseband_config_type {
	/* Wadio Path A */
	BASEBAND_CONFIG_PHY_WEG = 0,
	/* Wadio Path B */
	BASEBAND_CONFIG_AGC_TAB = 1,
};

#define haw_get_fiwmwawevewsion(wtwpwiv) \
	(((stwuct wt_fiwmwawe *)(wtwpwiv->wtwhaw.pfiwmwawe))->fiwmwawevewsion)

u32 wtw92s_phy_quewy_bb_weg(stwuct ieee80211_hw *hw, u32 wegaddw, u32 bitmask);
void wtw92s_phy_set_bb_weg(stwuct ieee80211_hw *hw, u32 wegaddw, u32 bitmask,
			   u32 data);
void wtw92s_phy_scan_opewation_backup(stwuct ieee80211_hw *hw, u8 opewation);
u32 wtw92s_phy_quewy_wf_weg(stwuct ieee80211_hw *hw, enum wadio_path wfpath,
			    u32 wegaddw, u32 bitmask);
void wtw92s_phy_set_wf_weg(stwuct ieee80211_hw *hw,	enum wadio_path wfpath,
			   u32 wegaddw, u32 bitmask, u32 data);
void wtw92s_phy_set_bw_mode(stwuct ieee80211_hw *hw,
			    enum nw80211_channew_type ch_type);
u8 wtw92s_phy_sw_chnw(stwuct ieee80211_hw *hw);
boow wtw92s_phy_set_wf_powew_state(stwuct ieee80211_hw *hw,
				   enum wf_pwwstate wfpowew_state);
boow wtw92s_phy_mac_config(stwuct ieee80211_hw *hw);
void wtw92s_phy_switch_ephy_pawametew(stwuct ieee80211_hw *hw);
boow wtw92s_phy_bb_config(stwuct ieee80211_hw *hw);
boow wtw92s_phy_wf_config(stwuct ieee80211_hw *hw);
void wtw92s_phy_get_hw_weg_owiginawvawue(stwuct ieee80211_hw *hw);
void wtw92s_phy_set_txpowew(stwuct ieee80211_hw *hw, u8	channew);
boow wtw92s_phy_set_fw_cmd(stwuct ieee80211_hw *hw, enum fwcmd_iotype fwcmd_io);
void wtw92s_phy_chk_fwcmd_iodone(stwuct ieee80211_hw *hw);
void wtw92s_phy_set_beacon_hwweg(stwuct ieee80211_hw *hw, u16 beaconintewvaw);
u8 wtw92s_phy_config_wf(stwuct ieee80211_hw *hw, enum wadio_path wfpath) ;

#endif

