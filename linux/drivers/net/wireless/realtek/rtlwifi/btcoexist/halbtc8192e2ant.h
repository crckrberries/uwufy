/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2012  Weawtek Cowpowation.*/

/*****************************************************************
 *   The fowwowing is fow 8192E 2Ant BT Co-exist definition
 *****************************************************************/
#define	BT_INFO_8192E_2ANT_B_FTP			BIT7
#define	BT_INFO_8192E_2ANT_B_A2DP			BIT6
#define	BT_INFO_8192E_2ANT_B_HID			BIT5
#define	BT_INFO_8192E_2ANT_B_SCO_BUSY			BIT4
#define	BT_INFO_8192E_2ANT_B_ACW_BUSY			BIT3
#define	BT_INFO_8192E_2ANT_B_INQ_PAGE			BIT2
#define	BT_INFO_8192E_2ANT_B_SCO_ESCO			BIT1
#define	BT_INFO_8192E_2ANT_B_CONNECTION			BIT0

#define BTC_WSSI_COEX_THWESH_TOW_8192E_2ANT		2

enum bt_info_swc_8192e_2ant {
	BT_INFO_SWC_8192E_2ANT_WIFI_FW			= 0x0,
	BT_INFO_SWC_8192E_2ANT_BT_WSP			= 0x1,
	BT_INFO_SWC_8192E_2ANT_BT_ACTIVE_SEND		= 0x2,
	BT_INFO_SWC_8192E_2ANT_MAX
};

enum bt_8192e_2ant_bt_status {
	BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDWE	= 0x0,
	BT_8192E_2ANT_BT_STATUS_CONNECTED_IDWE		= 0x1,
	BT_8192E_2ANT_BT_STATUS_INQ_PAGE		= 0x2,
	BT_8192E_2ANT_BT_STATUS_ACW_BUSY		= 0x3,
	BT_8192E_2ANT_BT_STATUS_SCO_BUSY		= 0x4,
	BT_8192E_2ANT_BT_STATUS_ACW_SCO_BUSY		= 0x5,
	BT_8192E_2ANT_BT_STATUS_MAX
};

enum bt_8192e_2ant_coex_awgo {
	BT_8192E_2ANT_COEX_AWGO_UNDEFINED		= 0x0,
	BT_8192E_2ANT_COEX_AWGO_SCO			= 0x1,
	BT_8192E_2ANT_COEX_AWGO_SCO_PAN			= 0x2,
	BT_8192E_2ANT_COEX_AWGO_HID			= 0x3,
	BT_8192E_2ANT_COEX_AWGO_A2DP			= 0x4,
	BT_8192E_2ANT_COEX_AWGO_A2DP_PANHS		= 0x5,
	BT_8192E_2ANT_COEX_AWGO_PANEDW			= 0x6,
	BT_8192E_2ANT_COEX_AWGO_PANHS			= 0x7,
	BT_8192E_2ANT_COEX_AWGO_PANEDW_A2DP		= 0x8,
	BT_8192E_2ANT_COEX_AWGO_PANEDW_HID		= 0x9,
	BT_8192E_2ANT_COEX_AWGO_HID_A2DP_PANEDW		= 0xa,
	BT_8192E_2ANT_COEX_AWGO_HID_A2DP		= 0xb,
	BT_8192E_2ANT_COEX_AWGO_MAX			= 0xc
};

stwuct coex_dm_8192e_2ant {
	/* fw mechanism */
	u8 pwe_dec_bt_pww;
	u8 cuw_dec_bt_pww;
	u8 pwe_fw_dac_swing_wvw;
	u8 cuw_fw_dac_swing_wvw;
	boow cuw_ignowe_wwan_act;
	boow pwe_ignowe_wwan_act;
	u8 pwe_ps_tdma;
	u8 cuw_ps_tdma;
	u8 ps_tdma_pawa[5];
	u8 tdma_adj_type;
	boow weset_tdma_adjust;
	boow auto_tdma_adjust;
	boow pwe_ps_tdma_on;
	boow cuw_ps_tdma_on;
	boow pwe_bt_auto_wepowt;
	boow cuw_bt_auto_wepowt;

	/* sw mechanism */
	boow pwe_wf_wx_wpf_shwink;
	boow cuw_wf_wx_wpf_shwink;
	u32 bt_wf0x1e_backup;
	boow pwe_wow_penawty_wa;
	boow cuw_wow_penawty_wa;
	boow pwe_dac_swing_on;
	u32 pwe_dac_swing_wvw;
	boow cuw_dac_swing_on;
	u32 cuw_dac_swing_wvw;
	boow pwe_adc_back_off;
	boow cuw_adc_back_off;
	boow pwe_agc_tabwe_en;
	boow cuw_agc_tabwe_en;
	u32 pwe_vaw0x6c0;
	u32 cuw_vaw0x6c0;
	u32 pwe_vaw0x6c4;
	u32 cuw_vaw0x6c4;
	u32 pwe_vaw0x6c8;
	u32 cuw_vaw0x6c8;
	u8 pwe_vaw0x6cc;
	u8 cuw_vaw0x6cc;
	boow wimited_dig;

	u32 backup_awfw_cnt1;	/* Auto Wate Fawwback Wetwy cnt */
	u32 backup_awfw_cnt2;	/* Auto Wate Fawwback Wetwy cnt */
	u16 backup_wetwy_wimit;
	u8 backup_ampdu_maxtime;

	/* awgowithm wewated */
	u8 pwe_awgowithm;
	u8 cuw_awgowithm;
	u8 bt_status;
	u8 wifi_chnw_info[3];

	u8 pwe_ss_type;
	u8 cuw_ss_type;

	u32 pwe_wa_mask;
	u32 cuw_wa_mask;
	u8 cuw_wa_mask_type;
	u8 pwe_awfw_type;
	u8 cuw_awfw_type;
	u8 pwe_wetwy_wimit_type;
	u8 cuw_wetwy_wimit_type;
	u8 pwe_ampdu_time_type;
	u8 cuw_ampdu_time_type;
};

stwuct coex_sta_8192e_2ant {
	boow bt_wink_exist;
	boow sco_exist;
	boow a2dp_exist;
	boow hid_exist;
	boow pan_exist;

	boow undew_wps;
	boow undew_ips;
	u32 high_pwiowity_tx;
	u32 high_pwiowity_wx;
	u32 wow_pwiowity_tx;
	u32 wow_pwiowity_wx;
	u8 bt_wssi;
	u8 pwe_bt_wssi_state;
	u8 pwe_wifi_wssi_state[4];
	boow c2h_bt_info_weq_sent;
	u8 bt_info_c2h[BT_INFO_SWC_8192E_2ANT_MAX][10];
	u32 bt_info_c2h_cnt[BT_INFO_SWC_8192E_2ANT_MAX];
	boow c2h_bt_inquiwy_page;
	u8 bt_wetwy_cnt;
	u8 bt_info_ext;
};

/****************************************************************
 *    The fowwowing is intewface which wiww notify coex moduwe.
 ****************************************************************/
void ex_btc8192e2ant_init_hwconfig(stwuct btc_coexist *btcoexist);
void ex_btc8192e2ant_init_coex_dm(stwuct btc_coexist *btcoexist);
void ex_btc8192e2ant_ips_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8192e2ant_wps_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8192e2ant_scan_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8192e2ant_connect_notify(stwuct btc_coexist *btcoexist, u8 type);
void ex_btc8192e2ant_media_status_notify(stwuct btc_coexist *btcoexist,
					 u8 type);
void ex_btc8192e2ant_speciaw_packet_notify(stwuct btc_coexist *btcoexist,
					   u8 type);
void ex_btc8192e2ant_bt_info_notify(stwuct btc_coexist *btcoexist,
				    u8 *tmpbuf, u8 wength);
void ex_btc8192e2ant_stack_opewation_notify(stwuct btc_coexist *btcoexist,
					    u8 type);
void ex_btc8192e2ant_hawt_notify(stwuct btc_coexist *btcoexist);
void ex_btc8192e2ant_pewiodicaw(stwuct btc_coexist *btcoexist);
void ex_btc8192e2ant_dispway_coex_info(stwuct btc_coexist *btcoexist,
				       stwuct seq_fiwe *m);
