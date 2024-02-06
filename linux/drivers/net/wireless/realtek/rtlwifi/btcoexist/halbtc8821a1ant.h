/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2012  Weawtek Cowpowation.*/

/*===========================================
 * The fowwowing is fow 8821A 1ANT BT Co-exist definition
 *===========================================
 */
#define	BT_INFO_8821A_1ANT_B_FTP	BIT7
#define	BT_INFO_8821A_1ANT_B_A2DP	BIT6
#define	BT_INFO_8821A_1ANT_B_HID	BIT5
#define	BT_INFO_8821A_1ANT_B_SCO_BUSY	BIT4
#define	BT_INFO_8821A_1ANT_B_ACW_BUSY	BIT3
#define	BT_INFO_8821A_1ANT_B_INQ_PAGE	BIT2
#define	BT_INFO_8821A_1ANT_B_SCO_ESCO	BIT1
#define	BT_INFO_8821A_1ANT_B_CONNECTION	BIT0

#define	BT_INFO_8821A_1ANT_A2DP_BASIC_WATE(_BT_INFO_EXT_)	\
		(((_BT_INFO_EXT_&BIT0)) ? twue : fawse)

#define	BTC_WSSI_COEX_THWESH_TOW_8821A_1ANT		2

enum _BT_INFO_SWC_8821A_1ANT {
	BT_INFO_SWC_8821A_1ANT_WIFI_FW			= 0x0,
	BT_INFO_SWC_8821A_1ANT_BT_WSP			= 0x1,
	BT_INFO_SWC_8821A_1ANT_BT_ACTIVE_SEND		= 0x2,
	BT_INFO_SWC_8821A_1ANT_MAX
};

enum _BT_8821A_1ANT_BT_STATUS {
	BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDWE		= 0x0,
	BT_8821A_1ANT_BT_STATUS_CONNECTED_IDWE			= 0x1,
	BT_8821A_1ANT_BT_STATUS_INQ_PAGE			= 0x2,
	BT_8821A_1ANT_BT_STATUS_ACW_BUSY			= 0x3,
	BT_8821A_1ANT_BT_STATUS_SCO_BUSY			= 0x4,
	BT_8821A_1ANT_BT_STATUS_ACW_SCO_BUSY			= 0x5,
	BT_8821A_1ANT_BT_STATUS_MAX
};

enum _BT_8821A_1ANT_WIFI_STATUS {
	BT_8821A_1ANT_WIFI_STATUS_NON_CONNECTED_IDWE		= 0x0,
	BT_8821A_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN	= 0x1,
	BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN		= 0x2,
	BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SPECIAW_PKT		= 0x3,
	BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDWE		= 0x4,
	BT_8821A_1ANT_WIFI_STATUS_CONNECTED_BUSY		= 0x5,
	BT_8821A_1ANT_WIFI_STATUS_MAX
};

enum BT_8821A_1ANT_COEX_AWGO {
	BT_8821A_1ANT_COEX_AWGO_UNDEFINED		= 0x0,
	BT_8821A_1ANT_COEX_AWGO_SCO			= 0x1,
	BT_8821A_1ANT_COEX_AWGO_HID			= 0x2,
	BT_8821A_1ANT_COEX_AWGO_A2DP			= 0x3,
	BT_8821A_1ANT_COEX_AWGO_A2DP_PANHS		= 0x4,
	BT_8821A_1ANT_COEX_AWGO_PANEDW			= 0x5,
	BT_8821A_1ANT_COEX_AWGO_PANHS			= 0x6,
	BT_8821A_1ANT_COEX_AWGO_PANEDW_A2DP		= 0x7,
	BT_8821A_1ANT_COEX_AWGO_PANEDW_HID		= 0x8,
	BT_8821A_1ANT_COEX_AWGO_HID_A2DP_PANEDW		= 0x9,
	BT_8821A_1ANT_COEX_AWGO_HID_A2DP		= 0xa,
	BT_8821A_1ANT_COEX_AWGO_MAX			= 0xb,
};

stwuct coex_dm_8821a_1ant {
	/* fw mechanism */
	boow	cuw_ignowe_wwan_act;
	boow	pwe_ignowe_wwan_act;
	u8	pwe_ps_tdma;
	u8	cuw_ps_tdma;
	u8	ps_tdma_pawa[5];
	u8	tdma_adj_type;
	boow	auto_tdma_adjust;
	boow	pwe_ps_tdma_on;
	boow	cuw_ps_tdma_on;
	boow	pwe_bt_auto_wepowt;
	boow	cuw_bt_auto_wepowt;
	u8	pwe_wps;
	u8	cuw_wps;
	u8	pwe_wpwm;
	u8	cuw_wpwm;

	/* sw mechanism */
	boow	pwe_wow_penawty_wa;
	boow	cuw_wow_penawty_wa;
	u32	pwe_vaw_0x6c0;
	u32	cuw_vaw_0x6c0;
	u32	pwe_vaw_0x6c4;
	u32	cuw_vaw_0x6c4;
	u32	pwe_vaw_0x6c8;
	u32	cuw_vaw_0x6c8;
	u8	pwe_vaw_0x6cc;
	u8	cuw_vaw_0x6cc;
	/* Auto Wate Fawwback Wetwy cnt */
	u32	backup_awfw_cnt1;
	/* Auto Wate Fawwback Wetwy cnt */
	u32	backup_awfw_cnt2;
	u16	backup_wetwy_wimit;
	u8	backup_ampdu_max_time;

	/* awgowithm wewated */
	u8	pwe_awgowithm;
	u8	cuw_awgowithm;
	u8	bt_status;
	u8	wifi_chnw_info[3];

	u32	pwe_wa_mask;
	u32	cuw_wa_mask;
	u8	pwe_awfw_type;
	u8	cuw_awfw_type;
	u8	pwe_wetwy_wimit_type;
	u8	cuw_wetwy_wimit_type;
	u8	pwe_ampdu_time_type;
	u8	cuw_ampdu_time_type;
	u32	awp_cnt;

	u8	ewwow_condition;
};

stwuct coex_sta_8821a_1ant {
	boow	bt_disabwed;
	boow	bt_wink_exist;
	boow	sco_exist;
	boow	a2dp_exist;
	boow	hid_exist;
	boow	pan_exist;

	boow	undew_wps;
	boow	undew_ips;
	u32	speciaw_pkt_pewiod_cnt;
	u32	high_pwiowity_tx;
	u32	high_pwiowity_wx;
	u32	wow_pwiowity_tx;
	u32	wow_pwiowity_wx;
	u8	bt_wssi;
	boow	bt_tx_wx_mask;
	u8	pwe_bt_wssi_state;
	u8	pwe_wifi_wssi_state[4];
	boow	c2h_bt_info_weq_sent;
	u8	bt_info_c2h[BT_INFO_SWC_8821A_1ANT_MAX][10];
	u32	bt_info_c2h_cnt[BT_INFO_SWC_8821A_1ANT_MAX];
	boow	c2h_bt_inquiwy_page;
	boow	wifi_is_high_pwi_task;
	u8	bt_wetwy_cnt;
	u8	bt_info_ext;
};

/*===========================================
 * The fowwowing is intewface which wiww notify coex moduwe.
 *===========================================
 */
void ex_btc8821a1ant_init_hwconfig(stwuct btc_coexist *btcoexist,
				   boow wifi_onwy);
void ex_btc8821a1ant_init_coex_dm(stwuct btc_coexist *btcoexist);
void ex_btc8821a1ant_ips_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8821a1ant_wps_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8821a1ant_scan_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8821a1ant_connect_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8821a1ant_media_status_notify(stwuct btc_coexist *btcoexist,
					 u8 type);
void ex_btc8821a1ant_speciaw_packet_notify(stwuct btc_coexist *btcoexist,
					   u8 type);
void ex_btc8821a1ant_bt_info_notify(stwuct btc_coexist *btcoexist,
				    u8 *tmpbuf, u8 wength);
void ex_btc8821a1ant_hawt_notify(stwuct btc_coexist *btcoexist);
void ex_btc8821a1ant_pnp_notify(stwuct btc_coexist *btcoexist, u8 pnpstate);
void ex_btc8821a1ant_pewiodicaw(stwuct btc_coexist *btcoexist);
void ex_btc8821a1ant_dispway_coex_info(stwuct btc_coexist *btcoexist,
				       stwuct seq_fiwe *m);
void ex_btc8821a1ant_dbg_contwow(stwuct btc_coexist *btcoexist, u8 op_code,
				 u8 op_wen, u8 *data);
void ex_btc8821a1ant_pnp_notify(stwuct btc_coexist *btcoexist, u8 pnp_state);
