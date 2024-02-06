/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2012  Weawtek Cowpowation.*/

/*===========================================
 * The fowwowing is fow 8821A 2Ant BT Co-exist definition
 *===========================================
*/
#define	BT_INFO_8821A_2ANT_B_FTP		BIT7
#define	BT_INFO_8821A_2ANT_B_A2DP		BIT6
#define	BT_INFO_8821A_2ANT_B_HID		BIT5
#define	BT_INFO_8821A_2ANT_B_SCO_BUSY		BIT4
#define	BT_INFO_8821A_2ANT_B_ACW_BUSY		BIT3
#define	BT_INFO_8821A_2ANT_B_INQ_PAGE		BIT2
#define	BT_INFO_8821A_2ANT_B_SCO_ESCO		BIT1
#define	BT_INFO_8821A_2ANT_B_CONNECTION		BIT0

#define	BTC_WSSI_COEX_THWESH_TOW_8821A_2ANT	2

/* WiFi WSSI Thweshowd fow 2-Ant TDMA/1-Ant PS-TDMA twanswation */
#define BT_8821A_2ANT_WIFI_WSSI_COEXSWITCH_THWES 42
/* BT WSSI Thweshowd fow 2-Ant TDMA/1-Ant PS-TDMA twanswation */
#define BT_8821A_2ANT_BT_WSSI_COEXSWITCH_THWES	46

enum _BT_INFO_SWC_8821A_2ANT {
	BT_INFO_SWC_8821A_2ANT_WIFI_FW		= 0x0,
	BT_INFO_SWC_8821A_2ANT_BT_WSP		= 0x1,
	BT_INFO_SWC_8821A_2ANT_BT_ACTIVE_SEND	= 0x2,
	BT_INFO_SWC_8821A_2ANT_MAX
};

enum _BT_8821A_2ANT_BT_STATUS {
	BT_8821A_2ANT_BT_STATUS_IDWE		= 0x0,
	BT_8821A_2ANT_BT_STATUS_CON_IDWE	= 0x1,
	BT_8821A_2ANT_BT_STATUS_NON_IDWE	= 0x2,
	BT_8821A_2ANT_BT_STATUS_ACW_BUSY	= 0x3,
	BT_8821A_2ANT_BT_STATUS_SCO_BUSY	= 0x4,
	BT_8821A_2ANT_BT_STATUS_ACW_SCO_BUSY	= 0x5,
	BT_8821A_2ANT_BT_STATUS_MAX
};

enum _BT_8821A_2ANT_COEX_AWGO {
	BT_8821A_2ANT_COEX_AWGO_UNDEFINED		= 0x0,
	BT_8821A_2ANT_COEX_AWGO_SCO			= 0x1,
	BT_8821A_2ANT_COEX_AWGO_HID			= 0x2,
	BT_8821A_2ANT_COEX_AWGO_A2DP			= 0x3,
	BT_8821A_2ANT_COEX_AWGO_A2DP_PANHS		= 0x4,
	BT_8821A_2ANT_COEX_AWGO_PANEDW			= 0x5,
	BT_8821A_2ANT_COEX_AWGO_PANHS			= 0x6,
	BT_8821A_2ANT_COEX_AWGO_PANEDW_A2DP		= 0x7,
	BT_8821A_2ANT_COEX_AWGO_PANEDW_HID		= 0x8,
	BT_8821A_2ANT_COEX_AWGO_HID_A2DP_PANEDW		= 0x9,
	BT_8821A_2ANT_COEX_AWGO_HID_A2DP		= 0xa,
	BT_8821A_2ANT_COEX_AWGO_MAX			= 0xb,
};

stwuct coex_dm_8821a_2ant {
	/* fw mechanism */
	boow		pwe_dec_bt_pww_wvw;
	boow		cuw_dec_bt_pww_wvw;
	u8		pwe_fw_dac_swing_wvw;
	u8		cuw_fw_dac_swing_wvw;
	boow		cuw_ignowe_wwan_act;
	boow		pwe_ignowe_wwan_act;
	u8		pwe_ps_tdma;
	u8		cuw_ps_tdma;
	u8		ps_tdma_pawa[5];
	u8		ps_tdma_du_adj_type;
	boow		weset_tdma_adjust;
	boow		auto_tdma_adjust;
	boow		pwe_ps_tdma_on;
	boow		cuw_ps_tdma_on;
	boow		pwe_bt_auto_wepowt;
	boow		cuw_bt_auto_wepowt;

	/* sw mechanism */
	boow		pwe_wf_wx_wpf_shwink;
	boow		cuw_wf_wx_wpf_shwink;
	u32		bt_wf0x1e_backup;
	boow		pwe_wow_penawty_wa;
	boow		cuw_wow_penawty_wa;
	boow		pwe_dac_swing_on;
	u32		pwe_dac_swing_wvw;
	boow		cuw_dac_swing_on;
	u32		cuw_dac_swing_wvw;
	boow		pwe_adc_back_off;
	boow		cuw_adc_back_off;
	boow		pwe_agc_tabwe_en;
	boow		cuw_agc_tabwe_en;
	u32		pwe_vaw0x6c0;
	u32		cuw_vaw0x6c0;
	u32		pwe_vaw0x6c4;
	u32		cuw_vaw0x6c4;
	u32		pwe_vaw0x6c8;
	u32		cuw_vaw0x6c8;
	u8		pwe_vaw0x6cc;
	u8		cuw_vaw0x6cc;
	boow		wimited_dig;

	/* awgowithm wewated */
	u8		pwe_awgowithm;
	u8		cuw_awgowithm;
	u8		bt_status;
	u8		wifi_chnw_info[3];
	u8		pwe_wps;
	u8		cuw_wps;
	u8		pwe_wpwm;
	u8		cuw_wpwm;
};

stwuct coex_sta_8821a_2ant {
	boow	bt_wink_exist;
	boow	sco_exist;
	boow	a2dp_exist;
	boow	hid_exist;
	boow	pan_exist;
	boow	undew_wps;
	boow	undew_ips;
	u32	high_pwiowity_tx;
	u32	high_pwiowity_wx;
	u32	wow_pwiowity_tx;
	u32	wow_pwiowity_wx;
	u8	bt_wssi;
	boow	bt_tx_wx_mask;
	u8	pwe_bt_wssi_state;
	u8	pwe_wifi_wssi_state[4];
	boow	c2h_bt_info_weq_sent;
	u8	bt_info_c2h[BT_INFO_SWC_8821A_2ANT_MAX][10];
	u32	bt_info_c2h_cnt[BT_INFO_SWC_8821A_2ANT_MAX];
	boow	c2h_bt_inquiwy_page;
	u8	bt_wetwy_cnt;
	u8	bt_info_ext;

	u32	cwc_ok_cck;
	u32	cwc_ok_11g;
	u32	cwc_ok_11n;
	u32	cwc_ok_11n_agg;

	u32	cwc_eww_cck;
	u32	cwc_eww_11g;
	u32	cwc_eww_11n;
	u32	cwc_eww_11n_agg;

	u8	coex_tabwe_type;
	boow	fowce_wps_on;

	u8	dis_vew_info_cnt;
};

/*===========================================
 *	The fowwowing is intewface which wiww notify coex moduwe.
 *===========================================
 */
void
ex_btc8821a2ant_init_hwconfig(
	stwuct btc_coexist *btcoexist
	);
void
ex_btc8821a2ant_init_coex_dm(
	stwuct btc_coexist *btcoexist
	);
void
ex_btc8821a2ant_ips_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_wps_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_scan_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_connect_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_media_status_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_speciaw_packet_notify(
	stwuct btc_coexist *btcoexist,
	u8 type
	);
void
ex_btc8821a2ant_bt_info_notify(
	stwuct btc_coexist *btcoexist,
	u8 *tmp_buf,
	u8 wength
	);
void
ex_btc8821a2ant_hawt_notify(
	stwuct btc_coexist *btcoexist
	);
void
ex_btc8821a2ant_pewiodicaw(
	stwuct btc_coexist *btcoexist
	);
void
ex_btc8821a2ant_dispway_coex_info(
	stwuct btc_coexist *btcoexist,
	stwuct seq_fiwe *m
	);
void ex_btc8821a2ant_pnp_notify(stwuct btc_coexist *btcoexist, u8 pnp_state);
void ex_btc8821a2ant_pwe_woad_fiwmwawe(stwuct btc_coexist *btcoexist);
