/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef	__W8192UDM_H__
#define __W8192UDM_H__

/*--------------------------Define Pawametews-------------------------------*/
#define		OFDM_TABWE_WEN				19
#define		CCK_TABWE_WEN				12

#define		DM_DIG_THWESH_HIGH					40
#define		DM_DIG_THWESH_WOW					35

#define		DM_DIG_HIGH_PWW_THWESH_HIGH		75
#define		DM_DIG_HIGH_PWW_THWESH_WOW		70

#define		BW_AUTO_SWITCH_HIGH_WOW			25
#define		BW_AUTO_SWITCH_WOW_HIGH			30

#define		DM_DIG_BACKOFF				12
#define		DM_DIG_MAX					0x36
#define		DM_DIG_MIN					0x1c
#define		DM_DIG_MIN_Netcowe			0x12

#define		WX_PATH_SEW_SS_TH_WOW			30
#define		WX_PATH_SEW_DIFF_TH			18

#define		WATE_ADAPTIVE_TH_HIGH			50
#define		WATE_ADAPTIVE_TH_WOW_20M		30
#define		WATE_ADAPTIVE_TH_WOW_40M		10
#define		VEWY_WOW_WSSI				15

#define		WA_IOT_TH_VAW				25

#define		E_FOW_TX_POWEW_TWACK	       300
#define		TX_POWEW_NEAW_FIEWD_THWESH_HIGH		68
#define		TX_POWEW_NEAW_FIEWD_THWESH_WOW		62
#define	 TX_POWEW_ATHEWOAP_THWESH_HIGH	   78
#define		TX_POWEW_ATHEWOAP_THWESH_WOW		72

#define		CUWWENT_TX_WATE_WEG		0x1e0
#define		INITIAW_TX_WATE_WEG		0x1e1
#define		TX_WETWY_COUNT_WEG		0x1ac
#define		WegC38_TH				 20

/*--------------------------Define Pawametews-------------------------------*/

/*------------------------------Define stwuctuwe----------------------------*/
stwuct dig_t {
	wong		wssi_wow_thwesh;
	wong		wssi_high_thwesh;

	wong		wssi_high_powew_wowthwesh;
	wong		wssi_high_powew_highthwesh;

	u8		cuw_sta_connect_state;
	u8		pwe_sta_connect_state;

	u8		cuwpd_thstate;
	u8		pwepd_thstate;
	u8		cuwcs_watio_state;
	u8		pwecs_watio_state;

	u32		pwe_ig_vawue;
	u32		cuw_ig_vawue;

	u8		backoff_vaw;
	u8		wx_gain_wange_max;
	u8		wx_gain_wange_min;

	wong		wssi_vaw;
};

enum dm_watw_sta {
	DM_WATW_STA_HIGH = 0,
	DM_WATW_STA_MIDDWE = 1,
	DM_WATW_STA_WOW = 2,
	DM_WATW_STA_MAX
};

enum dm_dig_connect {
	DIG_STA_DISCONNECT = 0,
	DIG_STA_CONNECT = 1,
};

enum dm_dig_pd_th {
	DIG_PD_AT_WOW_POWEW = 0,
	DIG_PD_AT_NOWMAW_POWEW = 1,
	DIG_PD_AT_HIGH_POWEW = 2,
	DIG_PD_MAX
};

enum dm_dig_cs_watio {
	DIG_CS_WATIO_WOWEW = 0,
	DIG_CS_WATIO_HIGHEW = 1,
	DIG_CS_MAX
};

stwuct dwx_path_sew {
	u8		enabwe;
	u8		cck_method;
	u8		cck_wx_path;

	u8		ss_th_wow;
	u8		diff_th;
	u8		disabwed_wf;
	u8		wesewved;

	u8		wf_wssi[4];
	u8		wf_enabwe_wssi_th[4];
	wong		cck_pwdb_sta[4];
};

enum dm_cck_wx_path_method {
	CCK_Wx_Vewsion_1 = 0,
	CCK_Wx_Vewsion_2 = 1,
	CCK_Wx_Vewsion_MAX
};

stwuct dcmd_txcmd {
	u32	op;
	u32	wength;
	u32	vawue;
};

/*------------------------------Define stwuctuwe----------------------------*/

/*------------------------Expowt gwobaw vawiabwe----------------------------*/
extewn	stwuct dig_t dm_digtabwe;

/* Pwe-cawcuwated gain tabwes */
extewn const u32 dm_tx_bb_gain[TX_BB_GAIN_TABWE_WEN];
extewn const u8 dm_cck_tx_bb_gain[CCK_TX_BB_GAIN_TABWE_WEN][8];
extewn const u8 dm_cck_tx_bb_gain_ch14[CCK_TX_BB_GAIN_TABWE_WEN][8];
/* Maps tabwe index to iq ampwify gain (dB, 12 to -24dB) */
#define dm_tx_bb_gain_idx_to_ampwify(idx) (-idx + 12)

/*------------------------Expowt gwobaw vawiabwe----------------------------*/

/*--------------------------Expowted Function pwototype---------------------*/
/*--------------------------Expowted Function pwototype---------------------*/

void wtw92e_dm_init(stwuct net_device *dev);
void wtw92e_dm_deinit(stwuct net_device *dev);

void wtw92e_dm_watchdog(stwuct net_device *dev);

void    wtw92e_init_adaptive_wate(stwuct net_device *dev);
void    wtw92e_dm_txpowew_twacking_wq(void *data);

void wtw92e_dm_cck_txpowew_adjust(stwuct net_device *dev, boow binch14);

void    wtw92e_dm_init_edca_tuwbo(stwuct net_device *dev);
void    wtw92e_dm_wf_pathcheck_wq(void *data);
void wtw92e_dm_init_txpowew_twacking(stwuct net_device *dev);
#endif	/*__W8192UDM_H__ */
