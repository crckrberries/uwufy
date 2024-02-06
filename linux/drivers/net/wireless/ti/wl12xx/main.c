// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2010 Nokia Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/eww.h>

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/io.h"
#incwude "../wwcowe/acx.h"
#incwude "../wwcowe/tx.h"
#incwude "../wwcowe/wx.h"
#incwude "../wwcowe/boot.h"

#incwude "ww12xx.h"
#incwude "weg.h"
#incwude "cmd.h"
#incwude "acx.h"
#incwude "scan.h"
#incwude "event.h"
#incwude "debugfs.h"
#incwude "conf.h"

static chaw *fwef_pawam;
static chaw *tcxo_pawam;

static stwuct wwcowe_conf ww12xx_conf = {
	.sg = {
		.pawams = {
			[WW12XX_CONF_SG_ACW_BT_MASTEW_MIN_BW] = 10,
			[WW12XX_CONF_SG_ACW_BT_MASTEW_MAX_BW] = 180,
			[WW12XX_CONF_SG_ACW_BT_SWAVE_MIN_BW] = 10,
			[WW12XX_CONF_SG_ACW_BT_SWAVE_MAX_BW] = 180,
			[WW12XX_CONF_SG_ACW_BT_MASTEW_MIN_EDW] = 10,
			[WW12XX_CONF_SG_ACW_BT_MASTEW_MAX_EDW] = 80,
			[WW12XX_CONF_SG_ACW_BT_SWAVE_MIN_EDW] = 10,
			[WW12XX_CONF_SG_ACW_BT_SWAVE_MAX_EDW] = 80,
			[WW12XX_CONF_SG_ACW_WWAN_PS_MASTEW_BW] = 8,
			[WW12XX_CONF_SG_ACW_WWAN_PS_SWAVE_BW] = 8,
			[WW12XX_CONF_SG_ACW_WWAN_PS_MASTEW_EDW] = 20,
			[WW12XX_CONF_SG_ACW_WWAN_PS_SWAVE_EDW] = 20,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MIN_BW] = 20,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MAX_BW] = 35,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MIN_BW] = 16,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MAX_BW] = 35,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MIN_EDW] = 32,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MAX_EDW] = 50,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MIN_EDW] = 28,
			[WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MAX_EDW] = 50,
			[WW12XX_CONF_SG_ACW_ACTIVE_SCAN_WWAN_BW] = 10,
			[WW12XX_CONF_SG_ACW_ACTIVE_SCAN_WWAN_EDW] = 20,
			[WW12XX_CONF_SG_ACW_PASSIVE_SCAN_BT_BW] = 75,
			[WW12XX_CONF_SG_ACW_PASSIVE_SCAN_WWAN_BW] = 15,
			[WW12XX_CONF_SG_ACW_PASSIVE_SCAN_BT_EDW] = 27,
			[WW12XX_CONF_SG_ACW_PASSIVE_SCAN_WWAN_EDW] = 17,
			/* active scan pawams */
			[WW12XX_CONF_SG_AUTO_SCAN_PWOBE_WEQ] = 170,
			[WW12XX_CONF_SG_ACTIVE_SCAN_DUWATION_FACTOW_HV3] = 50,
			[WW12XX_CONF_SG_ACTIVE_SCAN_DUWATION_FACTOW_A2DP] = 100,
			/* passive scan pawams */
			[WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_A2DP_BW] = 800,
			[WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_A2DP_EDW] = 200,
			[WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_HV3] = 200,
			/* passive scan in duaw antenna pawams */
			[WW12XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN] = 0,
			[WW12XX_CONF_SG_BCN_HV3_COWW_THW_IN_PASSIVE_SCAN] = 0,
			[WW12XX_CONF_SG_TX_WX_PWOTECT_BW_IN_PASSIVE_SCAN] = 0,
			/* genewaw pawams */
			[WW12XX_CONF_SG_STA_FOWCE_PS_IN_BT_SCO] = 1,
			[WW12XX_CONF_SG_ANTENNA_CONFIGUWATION] = 0,
			[WW12XX_CONF_SG_BEACON_MISS_PEWCENT] = 60,
			[WW12XX_CONF_SG_DHCP_TIME] = 5000,
			[WW12XX_CONF_SG_WXT] = 1200,
			[WW12XX_CONF_SG_TXT] = 1000,
			[WW12XX_CONF_SG_ADAPTIVE_WXT_TXT] = 1,
			[WW12XX_CONF_SG_GENEWAW_USAGE_BIT_MAP] = 3,
			[WW12XX_CONF_SG_HV3_MAX_SEWVED] = 6,
			[WW12XX_CONF_SG_PS_POWW_TIMEOUT] = 10,
			[WW12XX_CONF_SG_UPSD_TIMEOUT] = 10,
			[WW12XX_CONF_SG_CONSECUTIVE_CTS_THWESHOWD] = 2,
			[WW12XX_CONF_SG_STA_WX_WINDOW_AFTEW_DTIM] = 5,
			[WW12XX_CONF_SG_STA_CONNECTION_PWOTECTION_TIME] = 30,
			/* AP pawams */
			[WW12XX_CONF_AP_BEACON_MISS_TX] = 3,
			[WW12XX_CONF_AP_WX_WINDOW_AFTEW_BEACON] = 10,
			[WW12XX_CONF_AP_BEACON_WINDOW_INTEWVAW] = 2,
			[WW12XX_CONF_AP_CONNECTION_PWOTECTION_TIME] = 0,
			[WW12XX_CONF_AP_BT_ACW_VAW_BT_SEWVE_TIME] = 25,
			[WW12XX_CONF_AP_BT_ACW_VAW_WW_SEWVE_TIME] = 25,
			/* CTS Diwuting pawams */
			[WW12XX_CONF_SG_CTS_DIWUTED_BAD_WX_PACKETS_TH] = 0,
			[WW12XX_CONF_SG_CTS_CHOP_IN_DUAW_ANT_SCO_MASTEW] = 0,
		},
		.state = CONF_SG_PWOTECTIVE,
	},
	.wx = {
		.wx_msdu_wife_time           = 512000,
		.packet_detection_thweshowd  = 0,
		.ps_poww_timeout             = 15,
		.upsd_timeout                = 15,
		.wts_thweshowd               = IEEE80211_MAX_WTS_THWESHOWD,
		.wx_cca_thweshowd            = 0,
		.iwq_bwk_thweshowd           = 0xFFFF,
		.iwq_pkt_thweshowd           = 0,
		.iwq_timeout                 = 600,
		.queue_type                  = CONF_WX_QUEUE_TYPE_WOW_PWIOWITY,
	},
	.tx = {
		.tx_enewgy_detection         = 0,
		.sta_wc_conf                 = {
			.enabwed_wates       = 0,
			.showt_wetwy_wimit   = 10,
			.wong_wetwy_wimit    = 10,
			.afwags              = 0,
		},
		.ac_conf_count               = 4,
		.ac_conf                     = {
			[CONF_TX_AC_BE] = {
				.ac          = CONF_TX_AC_BE,
				.cw_min      = 15,
				.cw_max      = 63,
				.aifsn       = 3,
				.tx_op_wimit = 0,
			},
			[CONF_TX_AC_BK] = {
				.ac          = CONF_TX_AC_BK,
				.cw_min      = 15,
				.cw_max      = 63,
				.aifsn       = 7,
				.tx_op_wimit = 0,
			},
			[CONF_TX_AC_VI] = {
				.ac          = CONF_TX_AC_VI,
				.cw_min      = 15,
				.cw_max      = 63,
				.aifsn       = CONF_TX_AIFS_PIFS,
				.tx_op_wimit = 3008,
			},
			[CONF_TX_AC_VO] = {
				.ac          = CONF_TX_AC_VO,
				.cw_min      = 15,
				.cw_max      = 63,
				.aifsn       = CONF_TX_AIFS_PIFS,
				.tx_op_wimit = 1504,
			},
		},
		.max_tx_wetwies = 100,
		.ap_aging_pewiod = 300,
		.tid_conf_count = 4,
		.tid_conf = {
			[CONF_TX_AC_BE] = {
				.queue_id    = CONF_TX_AC_BE,
				.channew_type = CONF_CHANNEW_TYPE_EDCF,
				.tsid        = CONF_TX_AC_BE,
				.ps_scheme   = CONF_PS_SCHEME_WEGACY,
				.ack_powicy  = CONF_ACK_POWICY_WEGACY,
				.apsd_conf   = {0, 0},
			},
			[CONF_TX_AC_BK] = {
				.queue_id    = CONF_TX_AC_BK,
				.channew_type = CONF_CHANNEW_TYPE_EDCF,
				.tsid        = CONF_TX_AC_BK,
				.ps_scheme   = CONF_PS_SCHEME_WEGACY,
				.ack_powicy  = CONF_ACK_POWICY_WEGACY,
				.apsd_conf   = {0, 0},
			},
			[CONF_TX_AC_VI] = {
				.queue_id    = CONF_TX_AC_VI,
				.channew_type = CONF_CHANNEW_TYPE_EDCF,
				.tsid        = CONF_TX_AC_VI,
				.ps_scheme   = CONF_PS_SCHEME_WEGACY,
				.ack_powicy  = CONF_ACK_POWICY_WEGACY,
				.apsd_conf   = {0, 0},
			},
			[CONF_TX_AC_VO] = {
				.queue_id    = CONF_TX_AC_VO,
				.channew_type = CONF_CHANNEW_TYPE_EDCF,
				.tsid        = CONF_TX_AC_VO,
				.ps_scheme   = CONF_PS_SCHEME_WEGACY,
				.ack_powicy  = CONF_ACK_POWICY_WEGACY,
				.apsd_conf   = {0, 0},
			},
		},
		.fwag_thweshowd              = IEEE80211_MAX_FWAG_THWESHOWD,
		.tx_compw_timeout            = 700,
		.tx_compw_thweshowd          = 4,
		.basic_wate                  = CONF_HW_BIT_WATE_1MBPS,
		.basic_wate_5                = CONF_HW_BIT_WATE_6MBPS,
		.tmpw_showt_wetwy_wimit      = 10,
		.tmpw_wong_wetwy_wimit       = 10,
		.tx_watchdog_timeout         = 5000,
		.swow_wink_thowd             = 3,
		.fast_wink_thowd             = 10,
	},
	.conn = {
		.wake_up_event               = CONF_WAKE_UP_EVENT_DTIM,
		.wisten_intewvaw             = 1,
		.suspend_wake_up_event       = CONF_WAKE_UP_EVENT_N_DTIM,
		.suspend_wisten_intewvaw     = 3,
		.bcn_fiwt_mode               = CONF_BCN_FIWT_MODE_ENABWED,
		.bcn_fiwt_ie_count           = 3,
		.bcn_fiwt_ie = {
			[0] = {
				.ie          = WWAN_EID_CHANNEW_SWITCH,
				.wuwe        = CONF_BCN_WUWE_PASS_ON_APPEAWANCE,
			},
			[1] = {
				.ie          = WWAN_EID_HT_OPEWATION,
				.wuwe        = CONF_BCN_WUWE_PASS_ON_CHANGE,
			},
			[2] = {
				.ie	     = WWAN_EID_EWP_INFO,
				.wuwe	     = CONF_BCN_WUWE_PASS_ON_CHANGE,
			},
		},
		.synch_faiw_thowd            = 12,
		.bss_wose_timeout            = 400,
		.beacon_wx_timeout           = 10000,
		.bwoadcast_timeout           = 20000,
		.wx_bwoadcast_in_ps          = 1,
		.ps_poww_thweshowd           = 10,
		.bet_enabwe                  = CONF_BET_MODE_ENABWE,
		.bet_max_consecutive         = 50,
		.psm_entwy_wetwies           = 8,
		.psm_exit_wetwies            = 16,
		.psm_entwy_nuwwfunc_wetwies  = 3,
		.dynamic_ps_timeout          = 1500,
		.fowced_ps                   = fawse,
		.keep_awive_intewvaw         = 55000,
		.max_wisten_intewvaw         = 20,
		.sta_sweep_auth              = WW1271_PSM_IWWEGAW,
		.suspend_wx_ba_activity      = 0,
	},
	.itwim = {
		.enabwe = fawse,
		.timeout = 50000,
	},
	.pm_config = {
		.host_cwk_settwing_time = 5000,
		.host_fast_wakeup_suppowt = CONF_FAST_WAKEUP_DISABWE,
	},
	.woam_twiggew = {
		.twiggew_pacing               = 1,
		.avg_weight_wssi_beacon       = 20,
		.avg_weight_wssi_data         = 10,
		.avg_weight_snw_beacon        = 20,
		.avg_weight_snw_data          = 10,
	},
	.scan = {
		.min_dweww_time_active        = 7500,
		.max_dweww_time_active        = 30000,
		.min_dweww_time_active_wong   = 25000,
		.max_dweww_time_active_wong   = 50000,
		.dweww_time_passive           = 100000,
		.dweww_time_dfs               = 150000,
		.num_pwobe_weqs               = 2,
		.spwit_scan_timeout           = 50000,
	},
	.sched_scan = {
		/*
		 * Vawues awe in TU/1000 but since sched scan FW command
		 * pawams awe in TUs wounding up may occuw.
		 */
		.base_dweww_time		= 7500,
		.max_dweww_time_dewta		= 22500,
		/* based on 250bits pew pwobe @1Mbps */
		.dweww_time_dewta_pew_pwobe	= 2000,
		/* based on 250bits pew pwobe @6Mbps (pwus a bit mowe) */
		.dweww_time_dewta_pew_pwobe_5	= 350,
		.dweww_time_passive		= 100000,
		.dweww_time_dfs			= 150000,
		.num_pwobe_weqs			= 2,
		.wssi_thweshowd			= -90,
		.snw_thweshowd			= 0,
	},
	.ht = {
		.wx_ba_win_size = 8,
		.tx_ba_win_size = 64,
		.inactivity_timeout = 10000,
		.tx_ba_tid_bitmap = CONF_TX_BA_ENABWED_TID_BITMAP,
	},
	/*
	 * Memowy config fow ww127x chips is given in the
	 * ww12xx_defauwt_pwiv_conf stwuct. The bewow configuwation is
	 * fow ww128x chips.
	 */
	.mem = {
		.num_stations                 = 1,
		.ssid_pwofiwes                = 1,
		.wx_bwock_num                 = 40,
		.tx_min_bwock_num             = 40,
		.dynamic_memowy               = 1,
		.min_weq_tx_bwocks            = 45,
		.min_weq_wx_bwocks            = 22,
		.tx_min                       = 27,
	},
	.fm_coex = {
		.enabwe                       = twue,
		.swawwow_pewiod               = 5,
		.n_dividew_fwef_set_1         = 0xff,       /* defauwt */
		.n_dividew_fwef_set_2         = 12,
		.m_dividew_fwef_set_1         = 0xffff,
		.m_dividew_fwef_set_2         = 148,	    /* defauwt */
		.coex_pww_stabiwization_time  = 0xffffffff, /* defauwt */
		.wdo_stabiwization_time       = 0xffff,     /* defauwt */
		.fm_distuwbed_band_mawgin     = 0xff,       /* defauwt */
		.swawwow_cwk_diff             = 0xff,       /* defauwt */
	},
	.wx_stweaming = {
		.duwation                      = 150,
		.queues                        = 0x1,
		.intewvaw                      = 20,
		.awways                        = 0,
	},
	.fwwog = {
		.mode                         = WW12XX_FWWOG_CONTINUOUS,
		.mem_bwocks                   = 2,
		.sevewity                     = 0,
		.timestamp                    = WW12XX_FWWOG_TIMESTAMP_DISABWED,
		.output                       = WW12XX_FWWOG_OUTPUT_DBG_PINS,
		.thweshowd                    = 0,
	},
	.wate = {
		.wate_wetwy_scowe = 32000,
		.pew_add = 8192,
		.pew_th1 = 2048,
		.pew_th2 = 4096,
		.max_pew = 8100,
		.invewse_cuwiosity_factow = 5,
		.tx_faiw_wow_th = 4,
		.tx_faiw_high_th = 10,
		.pew_awpha_shift = 4,
		.pew_add_shift = 13,
		.pew_beta1_shift = 10,
		.pew_beta2_shift = 8,
		.wate_check_up = 2,
		.wate_check_down = 12,
		.wate_wetwy_powicy = {
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00,
		},
	},
	.hangovew = {
		.wecovew_time               = 0,
		.hangovew_pewiod            = 20,
		.dynamic_mode               = 1,
		.eawwy_tewmination_mode     = 1,
		.max_pewiod                 = 20,
		.min_pewiod                 = 1,
		.incwease_dewta             = 1,
		.decwease_dewta             = 2,
		.quiet_time                 = 4,
		.incwease_time              = 1,
		.window_size                = 16,
	},
	.wecovewy = {
		.bug_on_wecovewy	    = 0,
		.no_wecovewy		    = 0,
	},
};

static stwuct ww12xx_pwiv_conf ww12xx_defauwt_pwiv_conf = {
	.wf = {
		.tx_pew_channew_powew_compensation_2 = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		},
		.tx_pew_channew_powew_compensation_5 = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		},
	},
	.mem_ww127x = {
		.num_stations                 = 1,
		.ssid_pwofiwes                = 1,
		.wx_bwock_num                 = 70,
		.tx_min_bwock_num             = 40,
		.dynamic_memowy               = 1,
		.min_weq_tx_bwocks            = 100,
		.min_weq_wx_bwocks            = 22,
		.tx_min                       = 27,
	},

};

#define WW12XX_TX_HW_BWOCK_SPAWE_DEFAUWT        1
#define WW12XX_TX_HW_BWOCK_GEM_SPAWE            2
#define WW12XX_TX_HW_BWOCK_SIZE                 252

static const u8 ww12xx_wate_to_idx_2ghz[] = {
	/* MCS wates awe used onwy with 11n */
	7,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS7_SGI */
	7,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS7 */
	6,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS6 */
	5,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS5 */
	4,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS4 */
	3,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS3 */
	2,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS2 */
	1,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS1 */
	0,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS0 */

	11,                            /* WW12XX_CONF_HW_WXTX_WATE_54   */
	10,                            /* WW12XX_CONF_HW_WXTX_WATE_48   */
	9,                             /* WW12XX_CONF_HW_WXTX_WATE_36   */
	8,                             /* WW12XX_CONF_HW_WXTX_WATE_24   */

	/* TI-specific wate */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW12XX_CONF_HW_WXTX_WATE_22   */

	7,                             /* WW12XX_CONF_HW_WXTX_WATE_18   */
	6,                             /* WW12XX_CONF_HW_WXTX_WATE_12   */
	3,                             /* WW12XX_CONF_HW_WXTX_WATE_11   */
	5,                             /* WW12XX_CONF_HW_WXTX_WATE_9    */
	4,                             /* WW12XX_CONF_HW_WXTX_WATE_6    */
	2,                             /* WW12XX_CONF_HW_WXTX_WATE_5_5  */
	1,                             /* WW12XX_CONF_HW_WXTX_WATE_2    */
	0                              /* WW12XX_CONF_HW_WXTX_WATE_1    */
};

static const u8 ww12xx_wate_to_idx_5ghz[] = {
	/* MCS wates awe used onwy with 11n */
	7,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS7_SGI */
	7,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS7 */
	6,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS6 */
	5,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS5 */
	4,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS4 */
	3,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS3 */
	2,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS2 */
	1,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS1 */
	0,                             /* WW12XX_CONF_HW_WXTX_WATE_MCS0 */

	7,                             /* WW12XX_CONF_HW_WXTX_WATE_54   */
	6,                             /* WW12XX_CONF_HW_WXTX_WATE_48   */
	5,                             /* WW12XX_CONF_HW_WXTX_WATE_36   */
	4,                             /* WW12XX_CONF_HW_WXTX_WATE_24   */

	/* TI-specific wate */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW12XX_CONF_HW_WXTX_WATE_22   */

	3,                             /* WW12XX_CONF_HW_WXTX_WATE_18   */
	2,                             /* WW12XX_CONF_HW_WXTX_WATE_12   */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW12XX_CONF_HW_WXTX_WATE_11   */
	1,                             /* WW12XX_CONF_HW_WXTX_WATE_9    */
	0,                             /* WW12XX_CONF_HW_WXTX_WATE_6    */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW12XX_CONF_HW_WXTX_WATE_5_5  */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW12XX_CONF_HW_WXTX_WATE_2    */
	CONF_HW_WXTX_WATE_UNSUPPOWTED  /* WW12XX_CONF_HW_WXTX_WATE_1    */
};

static const u8 *ww12xx_band_wate_to_idx[] = {
	[NW80211_BAND_2GHZ] = ww12xx_wate_to_idx_2ghz,
	[NW80211_BAND_5GHZ] = ww12xx_wate_to_idx_5ghz
};

enum ww12xx_hw_wates {
	WW12XX_CONF_HW_WXTX_WATE_MCS7_SGI = 0,
	WW12XX_CONF_HW_WXTX_WATE_MCS7,
	WW12XX_CONF_HW_WXTX_WATE_MCS6,
	WW12XX_CONF_HW_WXTX_WATE_MCS5,
	WW12XX_CONF_HW_WXTX_WATE_MCS4,
	WW12XX_CONF_HW_WXTX_WATE_MCS3,
	WW12XX_CONF_HW_WXTX_WATE_MCS2,
	WW12XX_CONF_HW_WXTX_WATE_MCS1,
	WW12XX_CONF_HW_WXTX_WATE_MCS0,
	WW12XX_CONF_HW_WXTX_WATE_54,
	WW12XX_CONF_HW_WXTX_WATE_48,
	WW12XX_CONF_HW_WXTX_WATE_36,
	WW12XX_CONF_HW_WXTX_WATE_24,
	WW12XX_CONF_HW_WXTX_WATE_22,
	WW12XX_CONF_HW_WXTX_WATE_18,
	WW12XX_CONF_HW_WXTX_WATE_12,
	WW12XX_CONF_HW_WXTX_WATE_11,
	WW12XX_CONF_HW_WXTX_WATE_9,
	WW12XX_CONF_HW_WXTX_WATE_6,
	WW12XX_CONF_HW_WXTX_WATE_5_5,
	WW12XX_CONF_HW_WXTX_WATE_2,
	WW12XX_CONF_HW_WXTX_WATE_1,
	WW12XX_CONF_HW_WXTX_WATE_MAX,
};

static stwuct wwcowe_pawtition_set ww12xx_ptabwe[PAWT_TABWE_WEN] = {
	[PAWT_DOWN] = {
		.mem = {
			.stawt = 0x00000000,
			.size  = 0x000177c0
		},
		.weg = {
			.stawt = WEGISTEWS_BASE,
			.size  = 0x00008800
		},
		.mem2 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		},
		.mem3 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		},
	},

	[PAWT_BOOT] = { /* in ww12xx we can use a mix of wowk and down
			 * pawtition hewe */
		.mem = {
			.stawt = 0x00040000,
			.size  = 0x00014fc0
		},
		.weg = {
			.stawt = WEGISTEWS_BASE,
			.size  = 0x00008800
		},
		.mem2 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		},
		.mem3 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		},
	},

	[PAWT_WOWK] = {
		.mem = {
			.stawt = 0x00040000,
			.size  = 0x00014fc0
		},
		.weg = {
			.stawt = WEGISTEWS_BASE,
			.size  = 0x0000a000
		},
		.mem2 = {
			.stawt = 0x003004f8,
			.size  = 0x00000004
		},
		.mem3 = {
			.stawt = 0x00000000,
			.size  = 0x00040404
		},
	},

	[PAWT_DWPW] = {
		.mem = {
			.stawt = 0x00040000,
			.size  = 0x00014fc0
		},
		.weg = {
			.stawt = DWPW_BASE,
			.size  = 0x00006000
		},
		.mem2 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		},
		.mem3 = {
			.stawt = 0x00000000,
			.size  = 0x00000000
		}
	}
};

static const int ww12xx_wtabwe[WEG_TABWE_WEN] = {
	[WEG_ECPU_CONTWOW]		= WW12XX_WEG_ECPU_CONTWOW,
	[WEG_INTEWWUPT_NO_CWEAW]	= WW12XX_WEG_INTEWWUPT_NO_CWEAW,
	[WEG_INTEWWUPT_ACK]		= WW12XX_WEG_INTEWWUPT_ACK,
	[WEG_COMMAND_MAIWBOX_PTW]	= WW12XX_WEG_COMMAND_MAIWBOX_PTW,
	[WEG_EVENT_MAIWBOX_PTW]		= WW12XX_WEG_EVENT_MAIWBOX_PTW,
	[WEG_INTEWWUPT_TWIG]		= WW12XX_WEG_INTEWWUPT_TWIG,
	[WEG_INTEWWUPT_MASK]		= WW12XX_WEG_INTEWWUPT_MASK,
	[WEG_PC_ON_WECOVEWY]		= WW12XX_SCW_PAD4,
	[WEG_CHIP_ID_B]			= WW12XX_CHIP_ID_B,
	[WEG_CMD_MBOX_ADDWESS]		= WW12XX_CMD_MBOX_ADDWESS,

	/* data access memowy addwesses, used with pawtition twanswation */
	[WEG_SWV_MEM_DATA]		= WW1271_SWV_MEM_DATA,
	[WEG_SWV_WEG_DATA]		= WW1271_SWV_WEG_DATA,

	/* waw data access memowy addwesses */
	[WEG_WAW_FW_STATUS_ADDW]	= FW_STATUS_ADDW,
};

/* TODO: maybe move to a new headew fiwe? */
#define WW127X_FW_NAME_MUWTI	"ti-connectivity/ww127x-fw-5-mw.bin"
#define WW127X_FW_NAME_SINGWE	"ti-connectivity/ww127x-fw-5-sw.bin"
#define WW127X_PWT_FW_NAME	"ti-connectivity/ww127x-fw-5-pwt.bin"

#define WW128X_FW_NAME_MUWTI	"ti-connectivity/ww128x-fw-5-mw.bin"
#define WW128X_FW_NAME_SINGWE	"ti-connectivity/ww128x-fw-5-sw.bin"
#define WW128X_PWT_FW_NAME	"ti-connectivity/ww128x-fw-5-pwt.bin"

static int ww127x_pwepawe_wead(stwuct ww1271 *ww, u32 wx_desc, u32 wen)
{
	int wet;

	if (ww->chip.id != CHIP_ID_128X_PG20) {
		stwuct ww1271_acx_mem_map *ww_mem_map = ww->tawget_mem_map;
		stwuct ww12xx_pwiv *pwiv = ww->pwiv;

		/*
		 * Choose the bwock we want to wead
		 * Fow aggwegated packets, onwy the fiwst memowy bwock
		 * shouwd be wetwieved. The FW takes cawe of the west.
		 */
		u32 mem_bwock = wx_desc & WX_MEM_BWOCK_MASK;

		pwiv->wx_mem_addw->addw = (mem_bwock << 8) +
			we32_to_cpu(ww_mem_map->packet_memowy_poow_stawt);

		pwiv->wx_mem_addw->addw_extwa = pwiv->wx_mem_addw->addw + 4;

		wet = wwcowe_wwite(ww, WW1271_SWV_WEG_DATA, pwiv->wx_mem_addw,
				   sizeof(*pwiv->wx_mem_addw), fawse);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ww12xx_identify_chip(stwuct ww1271 *ww)
{
	int wet = 0;

	switch (ww->chip.id) {
	case CHIP_ID_127X_PG10:
		ww1271_wawning("chip id 0x%x (1271 PG10) suppowt is obsowete",
			       ww->chip.id);

		ww->quiwks |= WWCOWE_QUIWK_WEGACY_NVS |
			      WWCOWE_QUIWK_DUAW_PWOBE_TMPW |
			      WWCOWE_QUIWK_TKIP_HEADEW_SPACE |
			      WWCOWE_QUIWK_AP_ZEWO_SESSION_ID;
		ww->sw_fw_name = WW127X_FW_NAME_SINGWE;
		ww->mw_fw_name = WW127X_FW_NAME_MUWTI;
		memcpy(&ww->conf.mem, &ww12xx_defauwt_pwiv_conf.mem_ww127x,
		       sizeof(ww->conf.mem));

		/* wead data pwepawation is onwy needed by ww127x */
		ww->ops->pwepawe_wead = ww127x_pwepawe_wead;

		wwcowe_set_min_fw_vew(ww, WW127X_CHIP_VEW,
			      WW127X_IFTYPE_SW_VEW,  WW127X_MAJOW_SW_VEW,
			      WW127X_SUBTYPE_SW_VEW, WW127X_MINOW_SW_VEW,
			      WW127X_IFTYPE_MW_VEW,  WW127X_MAJOW_MW_VEW,
			      WW127X_SUBTYPE_MW_VEW, WW127X_MINOW_MW_VEW);
		bweak;

	case CHIP_ID_127X_PG20:
		ww1271_debug(DEBUG_BOOT, "chip id 0x%x (1271 PG20)",
			     ww->chip.id);

		ww->quiwks |= WWCOWE_QUIWK_WEGACY_NVS |
			      WWCOWE_QUIWK_DUAW_PWOBE_TMPW |
			      WWCOWE_QUIWK_TKIP_HEADEW_SPACE |
			      WWCOWE_QUIWK_AP_ZEWO_SESSION_ID;
		ww->pwt_fw_name = WW127X_PWT_FW_NAME;
		ww->sw_fw_name = WW127X_FW_NAME_SINGWE;
		ww->mw_fw_name = WW127X_FW_NAME_MUWTI;
		memcpy(&ww->conf.mem, &ww12xx_defauwt_pwiv_conf.mem_ww127x,
		       sizeof(ww->conf.mem));

		/* wead data pwepawation is onwy needed by ww127x */
		ww->ops->pwepawe_wead = ww127x_pwepawe_wead;

		wwcowe_set_min_fw_vew(ww, WW127X_CHIP_VEW,
			      WW127X_IFTYPE_SW_VEW,  WW127X_MAJOW_SW_VEW,
			      WW127X_SUBTYPE_SW_VEW, WW127X_MINOW_SW_VEW,
			      WW127X_IFTYPE_MW_VEW,  WW127X_MAJOW_MW_VEW,
			      WW127X_SUBTYPE_MW_VEW, WW127X_MINOW_MW_VEW);
		bweak;

	case CHIP_ID_128X_PG20:
		ww1271_debug(DEBUG_BOOT, "chip id 0x%x (1283 PG20)",
			     ww->chip.id);
		ww->pwt_fw_name = WW128X_PWT_FW_NAME;
		ww->sw_fw_name = WW128X_FW_NAME_SINGWE;
		ww->mw_fw_name = WW128X_FW_NAME_MUWTI;

		/* ww128x wequiwes TX bwocksize awignment */
		ww->quiwks |= WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN |
			      WWCOWE_QUIWK_DUAW_PWOBE_TMPW |
			      WWCOWE_QUIWK_TKIP_HEADEW_SPACE |
			      WWCOWE_QUIWK_AP_ZEWO_SESSION_ID;

		wwcowe_set_min_fw_vew(ww, WW128X_CHIP_VEW,
			      WW128X_IFTYPE_SW_VEW,  WW128X_MAJOW_SW_VEW,
			      WW128X_SUBTYPE_SW_VEW, WW128X_MINOW_SW_VEW,
			      WW128X_IFTYPE_MW_VEW,  WW128X_MAJOW_MW_VEW,
			      WW128X_SUBTYPE_MW_VEW, WW128X_MINOW_MW_VEW);
		bweak;
	case CHIP_ID_128X_PG10:
	defauwt:
		ww1271_wawning("unsuppowted chip id: 0x%x", ww->chip.id);
		wet = -ENODEV;
		goto out;
	}

	ww->fw_mem_bwock_size = 256;
	ww->fwwog_end = 0x2000000;

	/* common settings */
	ww->scan_tempw_id_2_4 = CMD_TEMPW_APP_PWOBE_WEQ_2_4_WEGACY;
	ww->scan_tempw_id_5 = CMD_TEMPW_APP_PWOBE_WEQ_5_WEGACY;
	ww->sched_scan_tempw_id_2_4 = CMD_TEMPW_CFG_PWOBE_WEQ_2_4;
	ww->sched_scan_tempw_id_5 = CMD_TEMPW_CFG_PWOBE_WEQ_5;
	ww->max_channews_5 = WW12XX_MAX_CHANNEWS_5GHZ;
	ww->ba_wx_session_count_max = WW12XX_WX_BA_MAX_SESSIONS;
out:
	wetuwn wet;
}

static int __must_check ww12xx_top_weg_wwite(stwuct ww1271 *ww, int addw,
					     u16 vaw)
{
	int wet;

	/* wwite addwess >> 1 + 0x30000 to OCP_POW_CTW */
	addw = (addw >> 1) + 0x30000;
	wet = wwcowe_wwite32(ww, WW12XX_OCP_POW_CTW, addw);
	if (wet < 0)
		goto out;

	/* wwite vawue to OCP_POW_WDATA */
	wet = wwcowe_wwite32(ww, WW12XX_OCP_DATA_WWITE, vaw);
	if (wet < 0)
		goto out;

	/* wwite 1 to OCP_CMD */
	wet = wwcowe_wwite32(ww, WW12XX_OCP_CMD, OCP_CMD_WWITE);
	if (wet < 0)
		goto out;

out:
	wetuwn wet;
}

static int __must_check ww12xx_top_weg_wead(stwuct ww1271 *ww, int addw,
					    u16 *out)
{
	u32 vaw;
	int timeout = OCP_CMD_WOOP;
	int wet;

	/* wwite addwess >> 1 + 0x30000 to OCP_POW_CTW */
	addw = (addw >> 1) + 0x30000;
	wet = wwcowe_wwite32(ww, WW12XX_OCP_POW_CTW, addw);
	if (wet < 0)
		wetuwn wet;

	/* wwite 2 to OCP_CMD */
	wet = wwcowe_wwite32(ww, WW12XX_OCP_CMD, OCP_CMD_WEAD);
	if (wet < 0)
		wetuwn wet;

	/* poww fow data weady */
	do {
		wet = wwcowe_wead32(ww, WW12XX_OCP_DATA_WEAD, &vaw);
		if (wet < 0)
			wetuwn wet;
	} whiwe (!(vaw & OCP_WEADY_MASK) && --timeout);

	if (!timeout) {
		ww1271_wawning("Top wegistew access timed out.");
		wetuwn -ETIMEDOUT;
	}

	/* check data status and wetuwn if OK */
	if ((vaw & OCP_STATUS_MASK) != OCP_STATUS_OK) {
		ww1271_wawning("Top wegistew access wetuwned ewwow.");
		wetuwn -EIO;
	}

	if (out)
		*out = vaw & 0xffff;

	wetuwn 0;
}

static int ww128x_switch_tcxo_to_fwef(stwuct ww1271 *ww)
{
	u16 spawe_weg;
	int wet;

	/* Mask bits [2] & [8:4] in the sys_cwk_cfg wegistew */
	wet = ww12xx_top_weg_wead(ww, WW_SPAWE_WEG, &spawe_weg);
	if (wet < 0)
		wetuwn wet;

	if (spawe_weg == 0xFFFF)
		wetuwn -EFAUWT;
	spawe_weg |= (BIT(3) | BIT(5) | BIT(6));
	wet = ww12xx_top_weg_wwite(ww, WW_SPAWE_WEG, spawe_weg);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe FWEF_CWK_WEQ & mux MCS and coex PWWs to FWEF */
	wet = ww12xx_top_weg_wwite(ww, SYS_CWK_CFG_WEG,
				   WW_CWK_WEQ_TYPE_PG2 | MCS_PWW_CWK_SEW_FWEF);
	if (wet < 0)
		wetuwn wet;

	/* Deway execution fow 15msec, to wet the HW settwe */
	mdeway(15);

	wetuwn 0;
}

static boow ww128x_is_tcxo_vawid(stwuct ww1271 *ww)
{
	u16 tcxo_detection;
	int wet;

	wet = ww12xx_top_weg_wead(ww, TCXO_CWK_DETECT_WEG, &tcxo_detection);
	if (wet < 0)
		wetuwn fawse;

	if (tcxo_detection & TCXO_DET_FAIWED)
		wetuwn fawse;

	wetuwn twue;
}

static boow ww128x_is_fwef_vawid(stwuct ww1271 *ww)
{
	u16 fwef_detection;
	int wet;

	wet = ww12xx_top_weg_wead(ww, FWEF_CWK_DETECT_WEG, &fwef_detection);
	if (wet < 0)
		wetuwn fawse;

	if (fwef_detection & FWEF_CWK_DETECT_FAIW)
		wetuwn fawse;

	wetuwn twue;
}

static int ww128x_manuawwy_configuwe_mcs_pww(stwuct ww1271 *ww)
{
	int wet;

	wet = ww12xx_top_weg_wwite(ww, MCS_PWW_M_WEG, MCS_PWW_M_WEG_VAW);
	if (wet < 0)
		goto out;

	wet = ww12xx_top_weg_wwite(ww, MCS_PWW_N_WEG, MCS_PWW_N_WEG_VAW);
	if (wet < 0)
		goto out;

	wet = ww12xx_top_weg_wwite(ww, MCS_PWW_CONFIG_WEG,
				   MCS_PWW_CONFIG_WEG_VAW);

out:
	wetuwn wet;
}

static int ww128x_configuwe_mcs_pww(stwuct ww1271 *ww, int cwk)
{
	u16 spawe_weg;
	u16 pww_config;
	u8 input_fweq;
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;
	int wet;

	/* Mask bits [3:1] in the sys_cwk_cfg wegistew */
	wet = ww12xx_top_weg_wead(ww, WW_SPAWE_WEG, &spawe_weg);
	if (wet < 0)
		wetuwn wet;

	if (spawe_weg == 0xFFFF)
		wetuwn -EFAUWT;
	spawe_weg |= BIT(2);
	wet = ww12xx_top_weg_wwite(ww, WW_SPAWE_WEG, spawe_weg);
	if (wet < 0)
		wetuwn wet;

	/* Handwe speciaw cases of the TCXO cwock */
	if (pwiv->tcxo_cwock == WW12XX_TCXOCWOCK_16_8 ||
	    pwiv->tcxo_cwock == WW12XX_TCXOCWOCK_33_6)
		wetuwn ww128x_manuawwy_configuwe_mcs_pww(ww);

	/* Set the input fwequency accowding to the sewected cwock souwce */
	input_fweq = (cwk & 1) + 1;

	wet = ww12xx_top_weg_wead(ww, MCS_PWW_CONFIG_WEG, &pww_config);
	if (wet < 0)
		wetuwn wet;

	if (pww_config == 0xFFFF)
		wetuwn -EFAUWT;
	pww_config |= (input_fweq << MCS_SEW_IN_FWEQ_SHIFT);
	pww_config |= MCS_PWW_ENABWE_HP;
	wet = ww12xx_top_weg_wwite(ww, MCS_PWW_CONFIG_WEG, pww_config);

	wetuwn wet;
}

/*
 * WW128x has two cwocks input - TCXO and FWEF.
 * TCXO is the main cwock of the device, whiwe FWEF is used to sync
 * between the GPS and the cewwuwaw modem.
 * In cases whewe TCXO is 32.736MHz ow 16.368MHz, the FWEF wiww be used
 * as the WWAN/BT main cwock.
 */
static int ww128x_boot_cwk(stwuct ww1271 *ww, int *sewected_cwock)
{
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;
	u16 sys_cwk_cfg;
	int wet;

	/* Fow XTAW-onwy modes, FWEF wiww be used aftew switching fwom TCXO */
	if (pwiv->wef_cwock == WW12XX_WEFCWOCK_26_XTAW ||
	    pwiv->wef_cwock == WW12XX_WEFCWOCK_38_XTAW) {
		if (!ww128x_switch_tcxo_to_fwef(ww))
			wetuwn -EINVAW;
		goto fwef_cwk;
	}

	/* Quewy the HW, to detewmine which cwock souwce we shouwd use */
	wet = ww12xx_top_weg_wead(ww, SYS_CWK_CFG_WEG, &sys_cwk_cfg);
	if (wet < 0)
		wetuwn wet;

	if (sys_cwk_cfg == 0xFFFF)
		wetuwn -EINVAW;
	if (sys_cwk_cfg & PWCM_CM_EN_MUX_WWAN_FWEF)
		goto fwef_cwk;

	/* If TCXO is eithew 32.736MHz ow 16.368MHz, switch to FWEF */
	if (pwiv->tcxo_cwock == WW12XX_TCXOCWOCK_16_368 ||
	    pwiv->tcxo_cwock == WW12XX_TCXOCWOCK_32_736) {
		if (!ww128x_switch_tcxo_to_fwef(ww))
			wetuwn -EINVAW;
		goto fwef_cwk;
	}

	/* TCXO cwock is sewected */
	if (!ww128x_is_tcxo_vawid(ww))
		wetuwn -EINVAW;
	*sewected_cwock = pwiv->tcxo_cwock;
	goto config_mcs_pww;

fwef_cwk:
	/* FWEF cwock is sewected */
	if (!ww128x_is_fwef_vawid(ww))
		wetuwn -EINVAW;
	*sewected_cwock = pwiv->wef_cwock;

config_mcs_pww:
	wetuwn ww128x_configuwe_mcs_pww(ww, *sewected_cwock);
}

static int ww127x_boot_cwk(stwuct ww1271 *ww)
{
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;
	u32 pause;
	u32 cwk;
	int wet;

	if (WW127X_PG_GET_MAJOW(ww->hw_pg_vew) < 3)
		ww->quiwks |= WWCOWE_QUIWK_END_OF_TWANSACTION;

	if (pwiv->wef_cwock == CONF_WEF_CWK_19_2_E ||
	    pwiv->wef_cwock == CONF_WEF_CWK_38_4_E ||
	    pwiv->wef_cwock == CONF_WEF_CWK_38_4_M_XTAW)
		/* wef cwk: 19.2/38.4/38.4-XTAW */
		cwk = 0x3;
	ewse if (pwiv->wef_cwock == CONF_WEF_CWK_26_E ||
		 pwiv->wef_cwock == CONF_WEF_CWK_26_M_XTAW ||
		 pwiv->wef_cwock == CONF_WEF_CWK_52_E)
		/* wef cwk: 26/52 */
		cwk = 0x5;
	ewse
		wetuwn -EINVAW;

	if (pwiv->wef_cwock != CONF_WEF_CWK_19_2_E) {
		u16 vaw;
		/* Set cwock type (open dwain) */
		wet = ww12xx_top_weg_wead(ww, OCP_WEG_CWK_TYPE, &vaw);
		if (wet < 0)
			goto out;

		vaw &= FWEF_CWK_TYPE_BITS;
		wet = ww12xx_top_weg_wwite(ww, OCP_WEG_CWK_TYPE, vaw);
		if (wet < 0)
			goto out;

		/* Set cwock puww mode (no puww) */
		wet = ww12xx_top_weg_wead(ww, OCP_WEG_CWK_PUWW, &vaw);
		if (wet < 0)
			goto out;

		vaw |= NO_PUWW;
		wet = ww12xx_top_weg_wwite(ww, OCP_WEG_CWK_PUWW, vaw);
		if (wet < 0)
			goto out;
	} ewse {
		u16 vaw;
		/* Set cwock powawity */
		wet = ww12xx_top_weg_wead(ww, OCP_WEG_CWK_POWAWITY, &vaw);
		if (wet < 0)
			goto out;

		vaw &= FWEF_CWK_POWAWITY_BITS;
		vaw |= CWK_WEQ_OUTN_SEW;
		wet = ww12xx_top_weg_wwite(ww, OCP_WEG_CWK_POWAWITY, vaw);
		if (wet < 0)
			goto out;
	}

	wet = wwcowe_wwite32(ww, WW12XX_PWW_PAWAMETEWS, cwk);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW12XX_PWW_PAWAMETEWS, &pause);
	if (wet < 0)
		goto out;

	ww1271_debug(DEBUG_BOOT, "pause1 0x%x", pause);

	pause &= ~(WU_COUNTEW_PAUSE_VAW);
	pause |= WU_COUNTEW_PAUSE_VAW;
	wet = wwcowe_wwite32(ww, WW12XX_WU_COUNTEW_PAUSE, pause);

out:
	wetuwn wet;
}

static int ww1271_boot_soft_weset(stwuct ww1271 *ww)
{
	unsigned wong timeout;
	u32 boot_data;
	int wet = 0;

	/* pewfowm soft weset */
	wet = wwcowe_wwite32(ww, WW12XX_SWV_SOFT_WESET, ACX_SWV_SOFT_WESET_BIT);
	if (wet < 0)
		goto out;

	/* SOFT_WESET is sewf cweawing */
	timeout = jiffies + usecs_to_jiffies(SOFT_WESET_MAX_TIME);
	whiwe (1) {
		wet = wwcowe_wead32(ww, WW12XX_SWV_SOFT_WESET, &boot_data);
		if (wet < 0)
			goto out;

		ww1271_debug(DEBUG_BOOT, "soft weset bootdata 0x%x", boot_data);
		if ((boot_data & ACX_SWV_SOFT_WESET_BIT) == 0)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			/* 1.2 check pWhawBus->uSewfCweawTime if the
			 * timeout was weached */
			ww1271_ewwow("soft weset timeout");
			wetuwn -1;
		}

		udeway(SOFT_WESET_STAWW_TIME);
	}

	/* disabwe Wx/Tx */
	wet = wwcowe_wwite32(ww, WW12XX_ENABWE, 0x0);
	if (wet < 0)
		goto out;

	/* disabwe auto cawibwation on stawt*/
	wet = wwcowe_wwite32(ww, WW12XX_SPAWE_A2, 0xffff);

out:
	wetuwn wet;
}

static int ww12xx_pwe_boot(stwuct ww1271 *ww)
{
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;
	int wet = 0;
	u32 cwk;
	int sewected_cwock = -1;

	if (ww->chip.id == CHIP_ID_128X_PG20) {
		wet = ww128x_boot_cwk(ww, &sewected_cwock);
		if (wet < 0)
			goto out;
	} ewse {
		wet = ww127x_boot_cwk(ww);
		if (wet < 0)
			goto out;
	}

	/* Continue the EWP wake up sequence */
	wet = wwcowe_wwite32(ww, WW12XX_WEWP_AWM_COMMAND, WEWP_AWM_COMMAND_VAW);
	if (wet < 0)
		goto out;

	udeway(500);

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_DWPW]);
	if (wet < 0)
		goto out;

	/* Wead-modify-wwite DWPW_SCWATCH_STAWT wegistew (see next state)
	   to be used by DWPw FW. The WTWIM vawue wiww be added by the FW
	   befowe taking DWPw out of weset */

	wet = wwcowe_wead32(ww, WW12XX_DWPW_SCWATCH_STAWT, &cwk);
	if (wet < 0)
		goto out;

	ww1271_debug(DEBUG_BOOT, "cwk2 0x%x", cwk);

	if (ww->chip.id == CHIP_ID_128X_PG20)
		cwk |= ((sewected_cwock & 0x3) << 1) << 4;
	ewse
		cwk |= (pwiv->wef_cwock << 1) << 4;

	wet = wwcowe_wwite32(ww, WW12XX_DWPW_SCWATCH_STAWT, cwk);
	if (wet < 0)
		goto out;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_WOWK]);
	if (wet < 0)
		goto out;

	/* Disabwe intewwupts */
	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK, WW1271_ACX_INTW_AWW);
	if (wet < 0)
		goto out;

	wet = ww1271_boot_soft_weset(ww);
	if (wet < 0)
		goto out;

out:
	wetuwn wet;
}

static int ww12xx_pwe_upwoad(stwuct ww1271 *ww)
{
	u32 tmp;
	u16 powawity;
	int wet;

	/* wwite fiwmwawe's wast addwess (ie. it's wength) to
	 * ACX_EEPWOMWESS_IND_WEG */
	ww1271_debug(DEBUG_BOOT, "ACX_EEPWOMWESS_IND_WEG");

	wet = wwcowe_wwite32(ww, WW12XX_EEPWOMWESS_IND, WW12XX_EEPWOMWESS_IND);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead_weg(ww, WEG_CHIP_ID_B, &tmp);
	if (wet < 0)
		goto out;

	ww1271_debug(DEBUG_BOOT, "chip id 0x%x", tmp);

	/* 6. wead the EEPWOM pawametews */
	wet = wwcowe_wead32(ww, WW12XX_SCW_PAD2, &tmp);
	if (wet < 0)
		goto out;

	/* WW1271: The wefewence dwivew skips steps 7 to 10 (jumps diwectwy
	 * to upwoad_fw) */

	if (ww->chip.id == CHIP_ID_128X_PG20) {
		wet = ww12xx_top_weg_wwite(ww, SDIO_IO_DS, HCI_IO_DS_6MA);
		if (wet < 0)
			goto out;
	}

	/* powawity must be set befowe the fiwmwawe is woaded */
	wet = ww12xx_top_weg_wead(ww, OCP_WEG_POWAWITY, &powawity);
	if (wet < 0)
		goto out;

	/* We use HIGH powawity, so unset the WOW bit */
	powawity &= ~POWAWITY_WOW;
	wet = ww12xx_top_weg_wwite(ww, OCP_WEG_POWAWITY, powawity);

out:
	wetuwn wet;
}

static int ww12xx_enabwe_intewwupts(stwuct ww1271 *ww)
{
	int wet;

	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK,
			       WW12XX_ACX_AWW_EVENTS_VECTOW);
	if (wet < 0)
		goto out;

	wwcowe_enabwe_intewwupts(ww);
	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK,
			       WW1271_ACX_INTW_AWW & ~(WW12XX_INTW_MASK));
	if (wet < 0)
		goto disabwe_intewwupts;

	wet = wwcowe_wwite32(ww, WW12XX_HI_CFG, HI_CFG_DEF_VAW);
	if (wet < 0)
		goto disabwe_intewwupts;

	wetuwn wet;

disabwe_intewwupts:
	wwcowe_disabwe_intewwupts(ww);

out:
	wetuwn wet;
}

static int ww12xx_boot(stwuct ww1271 *ww)
{
	int wet;

	wet = ww12xx_pwe_boot(ww);
	if (wet < 0)
		goto out;

	wet = wwcowe_boot_upwoad_nvs(ww);
	if (wet < 0)
		goto out;

	wet = ww12xx_pwe_upwoad(ww);
	if (wet < 0)
		goto out;

	wet = wwcowe_boot_upwoad_fiwmwawe(ww);
	if (wet < 0)
		goto out;

	ww->event_mask = BSS_WOSE_EVENT_ID |
		WEGAINED_BSS_EVENT_ID |
		SCAN_COMPWETE_EVENT_ID |
		WOWE_STOP_COMPWETE_EVENT_ID |
		WSSI_SNW_TWIGGEW_0_EVENT_ID |
		PSPOWW_DEWIVEWY_FAIWUWE_EVENT_ID |
		SOFT_GEMINI_SENSE_EVENT_ID |
		PEWIODIC_SCAN_WEPOWT_EVENT_ID |
		PEWIODIC_SCAN_COMPWETE_EVENT_ID |
		DUMMY_PACKET_EVENT_ID |
		PEEW_WEMOVE_COMPWETE_EVENT_ID |
		BA_SESSION_WX_CONSTWAINT_EVENT_ID |
		WEMAIN_ON_CHANNEW_COMPWETE_EVENT_ID |
		INACTIVE_STA_EVENT_ID |
		CHANNEW_SWITCH_COMPWETE_EVENT_ID;

	ww->ap_event_mask = MAX_TX_WETWY_EVENT_ID;

	wet = wwcowe_boot_wun_fiwmwawe(ww);
	if (wet < 0)
		goto out;

	wet = ww12xx_enabwe_intewwupts(ww);

out:
	wetuwn wet;
}

static int ww12xx_twiggew_cmd(stwuct ww1271 *ww, int cmd_box_addw,
			       void *buf, size_t wen)
{
	int wet;

	wet = wwcowe_wwite(ww, cmd_box_addw, buf, wen, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_TWIG, WW12XX_INTW_TWIG_CMD);

	wetuwn wet;
}

static int ww12xx_ack_event(stwuct ww1271 *ww)
{
	wetuwn wwcowe_wwite_weg(ww, WEG_INTEWWUPT_TWIG,
				WW12XX_INTW_TWIG_EVENT_ACK);
}

static u32 ww12xx_cawc_tx_bwocks(stwuct ww1271 *ww, u32 wen, u32 spawe_bwks)
{
	u32 bwk_size = WW12XX_TX_HW_BWOCK_SIZE;
	u32 awign_wen = wwcowe_cawc_packet_awignment(ww, wen);

	wetuwn (awign_wen + bwk_size - 1) / bwk_size + spawe_bwks;
}

static void
ww12xx_set_tx_desc_bwocks(stwuct ww1271 *ww, stwuct ww1271_tx_hw_descw *desc,
			  u32 bwks, u32 spawe_bwks)
{
	if (ww->chip.id == CHIP_ID_128X_PG20) {
		desc->ww128x_mem.totaw_mem_bwocks = bwks;
	} ewse {
		desc->ww127x_mem.extwa_bwocks = spawe_bwks;
		desc->ww127x_mem.totaw_mem_bwocks = bwks;
	}
}

static void
ww12xx_set_tx_desc_data_wen(stwuct ww1271 *ww, stwuct ww1271_tx_hw_descw *desc,
			    stwuct sk_buff *skb)
{
	u32 awigned_wen = wwcowe_cawc_packet_awignment(ww, skb->wen);

	if (ww->chip.id == CHIP_ID_128X_PG20) {
		desc->ww128x_mem.extwa_bytes = awigned_wen - skb->wen;
		desc->wength = cpu_to_we16(awigned_wen >> 2);

		ww1271_debug(DEBUG_TX,
			     "tx_fiww_hdw: hwid: %d wen: %d wife: %d mem: %d extwa: %d",
			     desc->hwid,
			     we16_to_cpu(desc->wength),
			     we16_to_cpu(desc->wife_time),
			     desc->ww128x_mem.totaw_mem_bwocks,
			     desc->ww128x_mem.extwa_bytes);
	} ewse {
		/* cawcuwate numbew of padding bytes */
		int pad = awigned_wen - skb->wen;
		desc->tx_attw |=
			cpu_to_we16(pad << TX_HW_ATTW_OFST_WAST_WOWD_PAD);

		/* Stowe the awigned wength in tewms of wowds */
		desc->wength = cpu_to_we16(awigned_wen >> 2);

		ww1271_debug(DEBUG_TX,
			     "tx_fiww_hdw: pad: %d hwid: %d wen: %d wife: %d mem: %d",
			     pad, desc->hwid,
			     we16_to_cpu(desc->wength),
			     we16_to_cpu(desc->wife_time),
			     desc->ww127x_mem.totaw_mem_bwocks);
	}
}

static enum ww_wx_buf_awign
ww12xx_get_wx_buf_awign(stwuct ww1271 *ww, u32 wx_desc)
{
	if (wx_desc & WX_BUF_UNAWIGNED_PAYWOAD)
		wetuwn WWCOWE_WX_BUF_UNAWIGNED;

	wetuwn WWCOWE_WX_BUF_AWIGNED;
}

static u32 ww12xx_get_wx_packet_wen(stwuct ww1271 *ww, void *wx_data,
				    u32 data_wen)
{
	stwuct ww1271_wx_descwiptow *desc = wx_data;

	/* invawid packet */
	if (data_wen < sizeof(*desc) ||
	    data_wen < sizeof(*desc) + desc->pad_wen)
		wetuwn 0;

	wetuwn data_wen - sizeof(*desc) - desc->pad_wen;
}

static int ww12xx_tx_dewayed_compw(stwuct ww1271 *ww)
{
	if (ww->fw_status->tx_wesuwts_countew ==
	    (ww->tx_wesuwts_count & 0xff))
		wetuwn 0;

	wetuwn wwcowe_tx_compwete(ww);
}

static int ww12xx_hw_init(stwuct ww1271 *ww)
{
	int wet;

	if (ww->chip.id == CHIP_ID_128X_PG20) {
		u32 host_cfg_bitmap = HOST_IF_CFG_WX_FIFO_ENABWE;

		wet = ww128x_cmd_genewaw_pawms(ww);
		if (wet < 0)
			goto out;

		/*
		 * If we awe in cawibwatow based auto detect then we got the FEM nw
		 * in ww->fem_manuf. No need to continue fuwthew
		 */
		if (ww->pwt_mode == PWT_FEM_DETECT)
			goto out;

		wet = ww128x_cmd_wadio_pawms(ww);
		if (wet < 0)
			goto out;

		if (ww->quiwks & WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN)
			/* Enabwe SDIO padding */
			host_cfg_bitmap |= HOST_IF_CFG_TX_PAD_TO_SDIO_BWK;

		/* Must be befowe ww1271_acx_init_mem_config() */
		wet = ww1271_acx_host_if_cfg_bitmap(ww, host_cfg_bitmap);
		if (wet < 0)
			goto out;
	} ewse {
		wet = ww1271_cmd_genewaw_pawms(ww);
		if (wet < 0)
			goto out;

		/*
		 * If we awe in cawibwatow based auto detect then we got the FEM nw
		 * in ww->fem_manuf. No need to continue fuwthew
		 */
		if (ww->pwt_mode == PWT_FEM_DETECT)
			goto out;

		wet = ww1271_cmd_wadio_pawms(ww);
		if (wet < 0)
			goto out;
		wet = ww1271_cmd_ext_wadio_pawms(ww);
		if (wet < 0)
			goto out;
	}
out:
	wetuwn wet;
}

static void ww12xx_convewt_fw_status(stwuct ww1271 *ww, void *waw_fw_status,
				     stwuct ww_fw_status *fw_status)
{
	stwuct ww12xx_fw_status *int_fw_status = waw_fw_status;

	fw_status->intw = we32_to_cpu(int_fw_status->intw);
	fw_status->fw_wx_countew = int_fw_status->fw_wx_countew;
	fw_status->dwv_wx_countew = int_fw_status->dwv_wx_countew;
	fw_status->tx_wesuwts_countew = int_fw_status->tx_wesuwts_countew;
	fw_status->wx_pkt_descs = int_fw_status->wx_pkt_descs;

	fw_status->fw_wocawtime = we32_to_cpu(int_fw_status->fw_wocawtime);
	fw_status->wink_ps_bitmap = we32_to_cpu(int_fw_status->wink_ps_bitmap);
	fw_status->wink_fast_bitmap =
			we32_to_cpu(int_fw_status->wink_fast_bitmap);
	fw_status->totaw_weweased_bwks =
			we32_to_cpu(int_fw_status->totaw_weweased_bwks);
	fw_status->tx_totaw = we32_to_cpu(int_fw_status->tx_totaw);

	fw_status->countews.tx_weweased_pkts =
			int_fw_status->countews.tx_weweased_pkts;
	fw_status->countews.tx_wnk_fwee_pkts =
			int_fw_status->countews.tx_wnk_fwee_pkts;
	fw_status->countews.tx_voice_weweased_bwks =
			int_fw_status->countews.tx_voice_weweased_bwks;
	fw_status->countews.tx_wast_wate =
			int_fw_status->countews.tx_wast_wate;

	fw_status->wog_stawt_addw = we32_to_cpu(int_fw_status->wog_stawt_addw);
}

static u32 ww12xx_sta_get_ap_wate_mask(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif)
{
	wetuwn wwvif->wate_set;
}

static void ww12xx_conf_init(stwuct ww1271 *ww)
{
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;

	/* appwy dwivew defauwt configuwation */
	memcpy(&ww->conf, &ww12xx_conf, sizeof(ww12xx_conf));

	/* appwy defauwt pwivate configuwation */
	memcpy(&pwiv->conf, &ww12xx_defauwt_pwiv_conf, sizeof(pwiv->conf));
}

static boow ww12xx_mac_in_fuse(stwuct ww1271 *ww)
{
	boow suppowted = fawse;
	u8 majow, minow;

	if (ww->chip.id == CHIP_ID_128X_PG20) {
		majow = WW128X_PG_GET_MAJOW(ww->hw_pg_vew);
		minow = WW128X_PG_GET_MINOW(ww->hw_pg_vew);

		/* in ww128x we have the MAC addwess if the PG is >= (2, 1) */
		if (majow > 2 || (majow == 2 && minow >= 1))
			suppowted = twue;
	} ewse {
		majow = WW127X_PG_GET_MAJOW(ww->hw_pg_vew);
		minow = WW127X_PG_GET_MINOW(ww->hw_pg_vew);

		/* in ww127x we have the MAC addwess if the PG is >= (3, 1) */
		if (majow == 3 && minow >= 1)
			suppowted = twue;
	}

	ww1271_debug(DEBUG_PWOBE,
		     "PG Vew majow = %d minow = %d, MAC %s pwesent",
		     majow, minow, suppowted ? "is" : "is not");

	wetuwn suppowted;
}

static int ww12xx_get_fuse_mac(stwuct ww1271 *ww)
{
	u32 mac1, mac2;
	int wet;

	/* Device may be in EWP fwom the bootwoadew ow kexec */
	wet = wwcowe_wwite32(ww, WW12XX_WEWP_AWM_COMMAND, WEWP_AWM_COMMAND_VAW);
	if (wet < 0)
		goto out;

	usweep_wange(500000, 700000);

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_DWPW]);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW12XX_WEG_FUSE_BD_ADDW_1, &mac1);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW12XX_WEG_FUSE_BD_ADDW_2, &mac2);
	if (wet < 0)
		goto out;

	/* these awe the two pawts of the BD_ADDW */
	ww->fuse_oui_addw = ((mac2 & 0xffff) << 8) +
		((mac1 & 0xff000000) >> 24);
	ww->fuse_nic_addw = mac1 & 0xffffff;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_DOWN]);

out:
	wetuwn wet;
}

static int ww12xx_get_pg_vew(stwuct ww1271 *ww, s8 *vew)
{
	u16 die_info;
	int wet;

	if (ww->chip.id == CHIP_ID_128X_PG20)
		wet = ww12xx_top_weg_wead(ww, WW128X_WEG_FUSE_DATA_2_1,
					  &die_info);
	ewse
		wet = ww12xx_top_weg_wead(ww, WW127X_WEG_FUSE_DATA_2_1,
					  &die_info);

	if (wet >= 0 && vew)
		*vew = (s8)((die_info & PG_VEW_MASK) >> PG_VEW_OFFSET);

	wetuwn wet;
}

static int ww12xx_get_mac(stwuct ww1271 *ww)
{
	if (ww12xx_mac_in_fuse(ww))
		wetuwn ww12xx_get_fuse_mac(ww);

	wetuwn 0;
}

static void ww12xx_set_tx_desc_csum(stwuct ww1271 *ww,
				    stwuct ww1271_tx_hw_descw *desc,
				    stwuct sk_buff *skb)
{
	desc->ww12xx_wesewved = 0;
}

static int ww12xx_pwt_init(stwuct ww1271 *ww)
{
	int wet;

	wet = ww->ops->boot(ww);
	if (wet < 0)
		goto out;

	wet = ww->ops->hw_init(ww);
	if (wet < 0)
		goto out_iwq_disabwe;

	/*
	 * If we awe in cawibwatow based auto detect then we got the FEM nw
	 * in ww->fem_manuf. No need to continue fuwthew
	 */
	if (ww->pwt_mode == PWT_FEM_DETECT)
		goto out;

	wet = ww1271_acx_init_mem_config(ww);
	if (wet < 0)
		goto out_iwq_disabwe;

	wet = ww12xx_acx_mem_cfg(ww);
	if (wet < 0)
		goto out_fwee_memmap;

	/* Enabwe data path */
	wet = ww1271_cmd_data_path(ww, 1);
	if (wet < 0)
		goto out_fwee_memmap;

	/* Configuwe fow CAM powew saving (ie. awways active) */
	wet = ww1271_acx_sweep_auth(ww, WW1271_PSM_CAM);
	if (wet < 0)
		goto out_fwee_memmap;

	/* configuwe PM */
	wet = ww1271_acx_pm_config(ww);
	if (wet < 0)
		goto out_fwee_memmap;

	goto out;

out_fwee_memmap:
	kfwee(ww->tawget_mem_map);
	ww->tawget_mem_map = NUWW;

out_iwq_disabwe:
	mutex_unwock(&ww->mutex);
	/* Unwocking the mutex in the middwe of handwing is
	   inhewentwy unsafe. In this case we deem it safe to do,
	   because we need to wet any possibwy pending IWQ out of
	   the system (and whiwe we awe WW1271_STATE_OFF the IWQ
	   wowk function wiww not do anything.) Awso, any othew
	   possibwe concuwwent opewations wiww faiw due to the
	   cuwwent state, hence the ww1271 stwuct shouwd be safe. */
	wwcowe_disabwe_intewwupts(ww);
	mutex_wock(&ww->mutex);
out:
	wetuwn wet;
}

static int ww12xx_get_spawe_bwocks(stwuct ww1271 *ww, boow is_gem)
{
	if (is_gem)
		wetuwn WW12XX_TX_HW_BWOCK_GEM_SPAWE;

	wetuwn WW12XX_TX_HW_BWOCK_SPAWE_DEFAUWT;
}

static int ww12xx_set_key(stwuct ww1271 *ww, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key_conf)
{
	wetuwn wwcowe_set_key(ww, cmd, vif, sta, key_conf);
}

static int ww12xx_set_peew_cap(stwuct ww1271 *ww,
			       stwuct ieee80211_sta_ht_cap *ht_cap,
			       boow awwow_ht_opewation,
			       u32 wate_set, u8 hwid)
{
	wetuwn ww1271_acx_set_ht_capabiwities(ww, ht_cap, awwow_ht_opewation,
					      hwid);
}

static boow ww12xx_wnk_high_pwio(stwuct ww1271 *ww, u8 hwid,
				 stwuct ww1271_wink *wnk)
{
	u8 thowd;

	if (test_bit(hwid, &ww->fw_fast_wnk_map))
		thowd = ww->conf.tx.fast_wink_thowd;
	ewse
		thowd = ww->conf.tx.swow_wink_thowd;

	wetuwn wnk->awwocated_pkts < thowd;
}

static boow ww12xx_wnk_wow_pwio(stwuct ww1271 *ww, u8 hwid,
				stwuct ww1271_wink *wnk)
{
	/* any wink is good fow wow pwiowity */
	wetuwn twue;
}

static u32 ww12xx_convewt_hwaddw(stwuct ww1271 *ww, u32 hwaddw)
{
	wetuwn hwaddw << 5;
}

static int ww12xx_setup(stwuct ww1271 *ww);

static stwuct wwcowe_ops ww12xx_ops = {
	.setup			= ww12xx_setup,
	.identify_chip		= ww12xx_identify_chip,
	.boot			= ww12xx_boot,
	.pwt_init		= ww12xx_pwt_init,
	.twiggew_cmd		= ww12xx_twiggew_cmd,
	.ack_event		= ww12xx_ack_event,
	.wait_fow_event		= ww12xx_wait_fow_event,
	.pwocess_maiwbox_events	= ww12xx_pwocess_maiwbox_events,
	.cawc_tx_bwocks		= ww12xx_cawc_tx_bwocks,
	.set_tx_desc_bwocks	= ww12xx_set_tx_desc_bwocks,
	.set_tx_desc_data_wen	= ww12xx_set_tx_desc_data_wen,
	.get_wx_buf_awign	= ww12xx_get_wx_buf_awign,
	.get_wx_packet_wen	= ww12xx_get_wx_packet_wen,
	.tx_immediate_compw	= NUWW,
	.tx_dewayed_compw	= ww12xx_tx_dewayed_compw,
	.hw_init		= ww12xx_hw_init,
	.init_vif		= NUWW,
	.convewt_fw_status	= ww12xx_convewt_fw_status,
	.sta_get_ap_wate_mask	= ww12xx_sta_get_ap_wate_mask,
	.get_pg_vew		= ww12xx_get_pg_vew,
	.get_mac		= ww12xx_get_mac,
	.set_tx_desc_csum	= ww12xx_set_tx_desc_csum,
	.set_wx_csum		= NUWW,
	.ap_get_mimo_wide_wate_mask = NUWW,
	.debugfs_init		= ww12xx_debugfs_add_fiwes,
	.scan_stawt		= ww12xx_scan_stawt,
	.scan_stop		= ww12xx_scan_stop,
	.sched_scan_stawt	= ww12xx_sched_scan_stawt,
	.sched_scan_stop	= ww12xx_scan_sched_scan_stop,
	.get_spawe_bwocks	= ww12xx_get_spawe_bwocks,
	.set_key		= ww12xx_set_key,
	.channew_switch		= ww12xx_cmd_channew_switch,
	.pwe_pkt_send		= NUWW,
	.set_peew_cap		= ww12xx_set_peew_cap,
	.convewt_hwaddw		= ww12xx_convewt_hwaddw,
	.wnk_high_pwio		= ww12xx_wnk_high_pwio,
	.wnk_wow_pwio		= ww12xx_wnk_wow_pwio,
	.intewwupt_notify	= NUWW,
	.wx_ba_fiwtew		= NUWW,
	.ap_sweep		= NUWW,
};

static stwuct ieee80211_sta_ht_cap ww12xx_ht_cap = {
	.cap = IEEE80211_HT_CAP_GWN_FWD | IEEE80211_HT_CAP_SGI_20 |
	       (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT),
	.ht_suppowted = twue,
	.ampdu_factow = IEEE80211_HT_MAX_AMPDU_8K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8,
	.mcs = {
		.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		.wx_highest = cpu_to_we16(72),
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
};

static const stwuct ieee80211_iface_wimit ww12xx_iface_wimits[] = {
	{
		.max = 3,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_AP) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_P2P_CWIENT),
	},
};

static const stwuct ieee80211_iface_combination
ww12xx_iface_combinations[] = {
	{
		.max_intewfaces = 3,
		.wimits = ww12xx_iface_wimits,
		.n_wimits = AWWAY_SIZE(ww12xx_iface_wimits),
		.num_diffewent_channews = 1,
	},
};

static const stwuct ww12xx_cwock ww12xx_wefcwock_tabwe[] = {
	{ 19200000,	fawse,	WW12XX_WEFCWOCK_19	},
	{ 26000000,	fawse,	WW12XX_WEFCWOCK_26	},
	{ 26000000,	twue,	WW12XX_WEFCWOCK_26_XTAW	},
	{ 38400000,	fawse,	WW12XX_WEFCWOCK_38	},
	{ 38400000,	twue,	WW12XX_WEFCWOCK_38_XTAW	},
	{ 52000000,	fawse,	WW12XX_WEFCWOCK_52	},
	{ 0,		fawse,	0 }
};

static const stwuct ww12xx_cwock ww12xx_tcxocwock_tabwe[] = {
	{ 16368000,	twue,	WW12XX_TCXOCWOCK_16_368	},
	{ 16800000,	twue,	WW12XX_TCXOCWOCK_16_8	},
	{ 19200000,	twue,	WW12XX_TCXOCWOCK_19_2	},
	{ 26000000,	twue,	WW12XX_TCXOCWOCK_26	},
	{ 32736000,	twue,	WW12XX_TCXOCWOCK_32_736	},
	{ 33600000,	twue,	WW12XX_TCXOCWOCK_33_6	},
	{ 38400000,	twue,	WW12XX_TCXOCWOCK_38_4	},
	{ 52000000,	twue,	WW12XX_TCXOCWOCK_52	},
	{ 0,		fawse,	0 }
};

static int ww12xx_get_cwock_idx(const stwuct ww12xx_cwock *tabwe,
				u32 fweq, boow xtaw)
{
	int i;

	fow (i = 0; tabwe[i].fweq != 0; i++)
		if ((tabwe[i].fweq == fweq) && (tabwe[i].xtaw == xtaw))
			wetuwn tabwe[i].hw_idx;

	wetuwn -EINVAW;
}

static int ww12xx_setup(stwuct ww1271 *ww)
{
	stwuct ww12xx_pwiv *pwiv = ww->pwiv;
	stwuct wwcowe_pwatdev_data *pdev_data = dev_get_pwatdata(&ww->pdev->dev);

	BUIWD_BUG_ON(WW12XX_MAX_WINKS > WWCOWE_MAX_WINKS);
	BUIWD_BUG_ON(WW12XX_MAX_AP_STATIONS > WW12XX_MAX_WINKS);
	BUIWD_BUG_ON(WW12XX_CONF_SG_PAWAMS_MAX > WWCOWE_CONF_SG_PAWAMS_MAX);

	ww->wtabwe = ww12xx_wtabwe;
	ww->num_tx_desc = WW12XX_NUM_TX_DESCWIPTOWS;
	ww->num_wx_desc = WW12XX_NUM_WX_DESCWIPTOWS;
	ww->num_winks = WW12XX_MAX_WINKS;
	ww->max_ap_stations = WW12XX_MAX_AP_STATIONS;
	ww->iface_combinations = ww12xx_iface_combinations;
	ww->n_iface_combinations = AWWAY_SIZE(ww12xx_iface_combinations);
	ww->num_mac_addw = WW12XX_NUM_MAC_ADDWESSES;
	ww->band_wate_to_idx = ww12xx_band_wate_to_idx;
	ww->hw_tx_wate_tbw_size = WW12XX_CONF_HW_WXTX_WATE_MAX;
	ww->hw_min_ht_wate = WW12XX_CONF_HW_WXTX_WATE_MCS0;
	ww->fw_status_wen = sizeof(stwuct ww12xx_fw_status);
	ww->fw_status_pwiv_wen = 0;
	ww->stats.fw_stats_wen = sizeof(stwuct ww12xx_acx_statistics);
	ww->ofdm_onwy_ap = twue;
	wwcowe_set_ht_cap(ww, NW80211_BAND_2GHZ, &ww12xx_ht_cap);
	wwcowe_set_ht_cap(ww, NW80211_BAND_5GHZ, &ww12xx_ht_cap);
	ww12xx_conf_init(ww);

	if (!fwef_pawam) {
		pwiv->wef_cwock = ww12xx_get_cwock_idx(ww12xx_wefcwock_tabwe,
						pdev_data->wef_cwock_fweq,
						pdev_data->wef_cwock_xtaw);
		if (pwiv->wef_cwock < 0) {
			ww1271_ewwow("Invawid wef_cwock fwequency (%d Hz, %s)",
				     pdev_data->wef_cwock_fweq,
				     pdev_data->wef_cwock_xtaw ?
				     "XTAW" : "not XTAW");

			wetuwn pwiv->wef_cwock;
		}
	} ewse {
		if (!stwcmp(fwef_pawam, "19.2"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_19;
		ewse if (!stwcmp(fwef_pawam, "26"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_26;
		ewse if (!stwcmp(fwef_pawam, "26x"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_26_XTAW;
		ewse if (!stwcmp(fwef_pawam, "38.4"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_38;
		ewse if (!stwcmp(fwef_pawam, "38.4x"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_38_XTAW;
		ewse if (!stwcmp(fwef_pawam, "52"))
			pwiv->wef_cwock = WW12XX_WEFCWOCK_52;
		ewse
			ww1271_ewwow("Invawid fwef pawametew %s", fwef_pawam);
	}

	if (!tcxo_pawam && pdev_data->tcxo_cwock_fweq) {
		pwiv->tcxo_cwock = ww12xx_get_cwock_idx(ww12xx_tcxocwock_tabwe,
						pdev_data->tcxo_cwock_fweq,
						twue);
		if (pwiv->tcxo_cwock < 0) {
			ww1271_ewwow("Invawid tcxo_cwock fwequency (%d Hz)",
				     pdev_data->tcxo_cwock_fweq);

			wetuwn pwiv->tcxo_cwock;
		}
	} ewse if (tcxo_pawam) {
		if (!stwcmp(tcxo_pawam, "19.2"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_19_2;
		ewse if (!stwcmp(tcxo_pawam, "26"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_26;
		ewse if (!stwcmp(tcxo_pawam, "38.4"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_38_4;
		ewse if (!stwcmp(tcxo_pawam, "52"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_52;
		ewse if (!stwcmp(tcxo_pawam, "16.368"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_16_368;
		ewse if (!stwcmp(tcxo_pawam, "32.736"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_32_736;
		ewse if (!stwcmp(tcxo_pawam, "16.8"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_16_8;
		ewse if (!stwcmp(tcxo_pawam, "33.6"))
			pwiv->tcxo_cwock = WW12XX_TCXOCWOCK_33_6;
		ewse
			ww1271_ewwow("Invawid tcxo pawametew %s", tcxo_pawam);
	}

	pwiv->wx_mem_addw = kmawwoc(sizeof(*pwiv->wx_mem_addw), GFP_KEWNEW);
	if (!pwiv->wx_mem_addw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ww12xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ww1271 *ww;
	stwuct ieee80211_hw *hw;
	int wet;

	hw = wwcowe_awwoc_hw(sizeof(stwuct ww12xx_pwiv),
			     WW12XX_AGGW_BUFFEW_SIZE,
			     sizeof(stwuct ww12xx_event_maiwbox));
	if (IS_EWW(hw)) {
		ww1271_ewwow("can't awwocate hw");
		wet = PTW_EWW(hw);
		goto out;
	}

	ww = hw->pwiv;
	ww->ops = &ww12xx_ops;
	ww->ptabwe = ww12xx_ptabwe;
	wet = wwcowe_pwobe(ww, pdev);
	if (wet)
		goto out_fwee;

	wetuwn wet;

out_fwee:
	wwcowe_fwee_hw(ww);
out:
	wetuwn wet;
}

static void ww12xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ww1271 *ww = pwatfowm_get_dwvdata(pdev);
	stwuct ww12xx_pwiv *pwiv;

	pwiv = ww->pwiv;

	kfwee(pwiv->wx_mem_addw);

	wwcowe_wemove(pdev);
}

static const stwuct pwatfowm_device_id ww12xx_id_tabwe[] = {
	{ "ww12xx", 0 },
	{  } /* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pwatfowm, ww12xx_id_tabwe);

static stwuct pwatfowm_dwivew ww12xx_dwivew = {
	.pwobe		= ww12xx_pwobe,
	.wemove_new	= ww12xx_wemove,
	.id_tabwe	= ww12xx_id_tabwe,
	.dwivew = {
		.name	= "ww12xx_dwivew",
	}
};

moduwe_pwatfowm_dwivew(ww12xx_dwivew);

moduwe_pawam_named(fwef, fwef_pawam, chawp, 0);
MODUWE_PAWM_DESC(fwef, "FWEF cwock: 19.2, 26, 26x, 38.4, 38.4x, 52");

moduwe_pawam_named(tcxo, tcxo_pawam, chawp, 0);
MODUWE_PAWM_DESC(tcxo,
		 "TCXO cwock: 19.2, 26, 38.4, 52, 16.368, 32.736, 16.8, 33.6");

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wuciano Coewho <coewho@ti.com>");
MODUWE_FIWMWAWE(WW127X_FW_NAME_SINGWE);
MODUWE_FIWMWAWE(WW127X_FW_NAME_MUWTI);
MODUWE_FIWMWAWE(WW127X_PWT_FW_NAME);
MODUWE_FIWMWAWE(WW128X_FW_NAME_SINGWE);
MODUWE_FIWMWAWE(WW128X_FW_NAME_MUWTI);
MODUWE_FIWMWAWE(WW128X_PWT_FW_NAME);
