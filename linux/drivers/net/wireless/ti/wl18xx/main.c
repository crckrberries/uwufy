// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ip.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/iwq.h>

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/io.h"
#incwude "../wwcowe/acx.h"
#incwude "../wwcowe/tx.h"
#incwude "../wwcowe/wx.h"
#incwude "../wwcowe/boot.h"

#incwude "weg.h"
#incwude "conf.h"
#incwude "cmd.h"
#incwude "acx.h"
#incwude "tx.h"
#incwude "ww18xx.h"
#incwude "io.h"
#incwude "scan.h"
#incwude "event.h"
#incwude "debugfs.h"

#define WW18XX_WX_CHECKSUM_MASK      0x40

static chaw *ht_mode_pawam = NUWW;
static chaw *boawd_type_pawam = NUWW;
static boow checksum_pawam = fawse;
static int num_wx_desc_pawam = -1;

/* phy pawamtews */
static int dc2dc_pawam = -1;
static int n_antennas_2_pawam = -1;
static int n_antennas_5_pawam = -1;
static int wow_band_component_pawam = -1;
static int wow_band_component_type_pawam = -1;
static int high_band_component_pawam = -1;
static int high_band_component_type_pawam = -1;
static int pww_wimit_wefewence_11_abg_pawam = -1;

static const u8 ww18xx_wate_to_idx_2ghz[] = {
	/* MCS wates awe used onwy with 11n */
	15,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS15 */
	14,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS14 */
	13,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS13 */
	12,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS12 */
	11,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS11 */
	10,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS10 */
	9,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS9 */
	8,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS8 */
	7,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS7 */
	6,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS6 */
	5,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS5 */
	4,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS4 */
	3,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS3 */
	2,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS2 */
	1,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS1 */
	0,                             /* WW18XX_CONF_HW_WXTX_WATE_MCS0 */

	11,                            /* WW18XX_CONF_HW_WXTX_WATE_54   */
	10,                            /* WW18XX_CONF_HW_WXTX_WATE_48   */
	9,                             /* WW18XX_CONF_HW_WXTX_WATE_36   */
	8,                             /* WW18XX_CONF_HW_WXTX_WATE_24   */

	/* TI-specific wate */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_22   */

	7,                             /* WW18XX_CONF_HW_WXTX_WATE_18   */
	6,                             /* WW18XX_CONF_HW_WXTX_WATE_12   */
	3,                             /* WW18XX_CONF_HW_WXTX_WATE_11   */
	5,                             /* WW18XX_CONF_HW_WXTX_WATE_9    */
	4,                             /* WW18XX_CONF_HW_WXTX_WATE_6    */
	2,                             /* WW18XX_CONF_HW_WXTX_WATE_5_5  */
	1,                             /* WW18XX_CONF_HW_WXTX_WATE_2    */
	0                              /* WW18XX_CONF_HW_WXTX_WATE_1    */
};

static const u8 ww18xx_wate_to_idx_5ghz[] = {
	/* MCS wates awe used onwy with 11n */
	15,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS15 */
	14,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS14 */
	13,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS13 */
	12,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS12 */
	11,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS11 */
	10,                           /* WW18XX_CONF_HW_WXTX_WATE_MCS10 */
	9,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS9 */
	8,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS8 */
	7,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS7 */
	6,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS6 */
	5,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS5 */
	4,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS4 */
	3,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS3 */
	2,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS2 */
	1,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS1 */
	0,                            /* WW18XX_CONF_HW_WXTX_WATE_MCS0 */

	7,                             /* WW18XX_CONF_HW_WXTX_WATE_54   */
	6,                             /* WW18XX_CONF_HW_WXTX_WATE_48   */
	5,                             /* WW18XX_CONF_HW_WXTX_WATE_36   */
	4,                             /* WW18XX_CONF_HW_WXTX_WATE_24   */

	/* TI-specific wate */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_22   */

	3,                             /* WW18XX_CONF_HW_WXTX_WATE_18   */
	2,                             /* WW18XX_CONF_HW_WXTX_WATE_12   */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_11   */
	1,                             /* WW18XX_CONF_HW_WXTX_WATE_9    */
	0,                             /* WW18XX_CONF_HW_WXTX_WATE_6    */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_5_5  */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_2    */
	CONF_HW_WXTX_WATE_UNSUPPOWTED, /* WW18XX_CONF_HW_WXTX_WATE_1    */
};

static const u8 *ww18xx_band_wate_to_idx[] = {
	[NW80211_BAND_2GHZ] = ww18xx_wate_to_idx_2ghz,
	[NW80211_BAND_5GHZ] = ww18xx_wate_to_idx_5ghz
};

enum ww18xx_hw_wates {
	WW18XX_CONF_HW_WXTX_WATE_MCS15 = 0,
	WW18XX_CONF_HW_WXTX_WATE_MCS14,
	WW18XX_CONF_HW_WXTX_WATE_MCS13,
	WW18XX_CONF_HW_WXTX_WATE_MCS12,
	WW18XX_CONF_HW_WXTX_WATE_MCS11,
	WW18XX_CONF_HW_WXTX_WATE_MCS10,
	WW18XX_CONF_HW_WXTX_WATE_MCS9,
	WW18XX_CONF_HW_WXTX_WATE_MCS8,
	WW18XX_CONF_HW_WXTX_WATE_MCS7,
	WW18XX_CONF_HW_WXTX_WATE_MCS6,
	WW18XX_CONF_HW_WXTX_WATE_MCS5,
	WW18XX_CONF_HW_WXTX_WATE_MCS4,
	WW18XX_CONF_HW_WXTX_WATE_MCS3,
	WW18XX_CONF_HW_WXTX_WATE_MCS2,
	WW18XX_CONF_HW_WXTX_WATE_MCS1,
	WW18XX_CONF_HW_WXTX_WATE_MCS0,
	WW18XX_CONF_HW_WXTX_WATE_54,
	WW18XX_CONF_HW_WXTX_WATE_48,
	WW18XX_CONF_HW_WXTX_WATE_36,
	WW18XX_CONF_HW_WXTX_WATE_24,
	WW18XX_CONF_HW_WXTX_WATE_22,
	WW18XX_CONF_HW_WXTX_WATE_18,
	WW18XX_CONF_HW_WXTX_WATE_12,
	WW18XX_CONF_HW_WXTX_WATE_11,
	WW18XX_CONF_HW_WXTX_WATE_9,
	WW18XX_CONF_HW_WXTX_WATE_6,
	WW18XX_CONF_HW_WXTX_WATE_5_5,
	WW18XX_CONF_HW_WXTX_WATE_2,
	WW18XX_CONF_HW_WXTX_WATE_1,
	WW18XX_CONF_HW_WXTX_WATE_MAX,
};

static stwuct wwcowe_conf ww18xx_conf = {
	.sg = {
		.pawams = {
			[WW18XX_CONF_SG_PAWAM_0] = 0,
			/* Configuwation Pawametews */
			[WW18XX_CONF_SG_ANTENNA_CONFIGUWATION] = 0,
			[WW18XX_CONF_SG_ZIGBEE_COEX] = 0,
			[WW18XX_CONF_SG_TIME_SYNC] = 0,
			[WW18XX_CONF_SG_PAWAM_4] = 0,
			[WW18XX_CONF_SG_PAWAM_5] = 0,
			[WW18XX_CONF_SG_PAWAM_6] = 0,
			[WW18XX_CONF_SG_PAWAM_7] = 0,
			[WW18XX_CONF_SG_PAWAM_8] = 0,
			[WW18XX_CONF_SG_PAWAM_9] = 0,
			[WW18XX_CONF_SG_PAWAM_10] = 0,
			[WW18XX_CONF_SG_PAWAM_11] = 0,
			[WW18XX_CONF_SG_PAWAM_12] = 0,
			[WW18XX_CONF_SG_PAWAM_13] = 0,
			[WW18XX_CONF_SG_PAWAM_14] = 0,
			[WW18XX_CONF_SG_PAWAM_15] = 0,
			[WW18XX_CONF_SG_PAWAM_16] = 0,
			[WW18XX_CONF_SG_PAWAM_17] = 0,
			[WW18XX_CONF_SG_PAWAM_18] = 0,
			[WW18XX_CONF_SG_PAWAM_19] = 0,
			[WW18XX_CONF_SG_PAWAM_20] = 0,
			[WW18XX_CONF_SG_PAWAM_21] = 0,
			[WW18XX_CONF_SG_PAWAM_22] = 0,
			[WW18XX_CONF_SG_PAWAM_23] = 0,
			[WW18XX_CONF_SG_PAWAM_24] = 0,
			[WW18XX_CONF_SG_PAWAM_25] = 0,
			/* Active Scan Pawametews */
			[WW18XX_CONF_SG_AUTO_SCAN_PWOBE_WEQ] = 170,
			[WW18XX_CONF_SG_ACTIVE_SCAN_DUWATION_FACTOW_HV3] = 50,
			[WW18XX_CONF_SG_PAWAM_28] = 0,
			/* Passive Scan Pawametews */
			[WW18XX_CONF_SG_PAWAM_29] = 0,
			[WW18XX_CONF_SG_PAWAM_30] = 0,
			[WW18XX_CONF_SG_PASSIVE_SCAN_DUWATION_FACTOW_HV3] = 200,
			/* Passive Scan in Duaw Antenna Pawametews */
			[WW18XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN] = 0,
			[WW18XX_CONF_SG_BEACON_HV3_COWW_TH_IN_PASSIVE_SCAN] = 0,
			[WW18XX_CONF_SG_TX_WX_PWOTECT_BW_IN_PASSIVE_SCAN] = 0,
			/* Genewaw Pawametews */
			[WW18XX_CONF_SG_STA_FOWCE_PS_IN_BT_SCO] = 1,
			[WW18XX_CONF_SG_PAWAM_36] = 0,
			[WW18XX_CONF_SG_BEACON_MISS_PEWCENT] = 60,
			[WW18XX_CONF_SG_PAWAM_38] = 0,
			[WW18XX_CONF_SG_WXT] = 1200,
			[WW18XX_CONF_SG_UNUSED] = 0,
			[WW18XX_CONF_SG_ADAPTIVE_WXT_TXT] = 1,
			[WW18XX_CONF_SG_GENEWAW_USAGE_BIT_MAP] = 3,
			[WW18XX_CONF_SG_HV3_MAX_SEWVED] = 6,
			[WW18XX_CONF_SG_PAWAM_44] = 0,
			[WW18XX_CONF_SG_PAWAM_45] = 0,
			[WW18XX_CONF_SG_CONSECUTIVE_CTS_THWESHOWD] = 2,
			[WW18XX_CONF_SG_GEMINI_PAWAM_47] = 0,
			[WW18XX_CONF_SG_STA_CONNECTION_PWOTECTION_TIME] = 0,
			/* AP Pawametews */
			[WW18XX_CONF_SG_AP_BEACON_MISS_TX] = 3,
			[WW18XX_CONF_SG_PAWAM_50] = 0,
			[WW18XX_CONF_SG_AP_BEACON_WINDOW_INTEWVAW] = 2,
			[WW18XX_CONF_SG_AP_CONNECTION_PWOTECTION_TIME] = 30,
			[WW18XX_CONF_SG_PAWAM_53] = 0,
			[WW18XX_CONF_SG_PAWAM_54] = 0,
			/* CTS Diwuting Pawametews */
			[WW18XX_CONF_SG_CTS_DIWUTED_BAD_WX_PACKETS_TH] = 0,
			[WW18XX_CONF_SG_CTS_CHOP_IN_DUAW_ANT_SCO_MASTEW] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_1] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_2] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_3] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_4] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_5] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_6] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_7] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_8] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_9] = 0,
			[WW18XX_CONF_SG_TEMP_PAWAM_10] = 0,
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
		.tx_compw_timeout            = 350,
		.tx_compw_thweshowd          = 10,
		.basic_wate                  = CONF_HW_BIT_WATE_1MBPS,
		.basic_wate_5                = CONF_HW_BIT_WATE_6MBPS,
		.tmpw_showt_wetwy_wimit      = 10,
		.tmpw_wong_wetwy_wimit       = 10,
		.tx_watchdog_timeout         = 5000,
		.swow_wink_thowd             = 3,
		.fast_wink_thowd             = 30,
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
		.num_showt_intewvaws		= SCAN_MAX_SHOWT_INTEWVAWS,
		.wong_intewvaw			= 30000,
	},
	.ht = {
		.wx_ba_win_size = 32,
		.tx_ba_win_size = 64,
		.inactivity_timeout = 10000,
		.tx_ba_tid_bitmap = CONF_TX_BA_ENABWED_TID_BITMAP,
	},
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
		.m_dividew_fwef_set_2         = 148,        /* defauwt */
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
		.mem_bwocks                   = 0,
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

static stwuct ww18xx_pwiv_conf ww18xx_defauwt_pwiv_conf = {
	.ht = {
		.mode				= HT_MODE_WIDE,
	},
	.phy = {
		.phy_standawone			= 0x00,
		.pwimawy_cwock_setting_time	= 0x05,
		.cwock_vawid_on_wake_up		= 0x00,
		.secondawy_cwock_setting_time	= 0x05,
		.boawd_type 			= BOAWD_TYPE_HDK_18XX,
		.auto_detect			= 0x00,
		.dedicated_fem			= FEM_NONE,
		.wow_band_component		= COMPONENT_3_WAY_SWITCH,
		.wow_band_component_type	= 0x05,
		.high_band_component		= COMPONENT_2_WAY_SWITCH,
		.high_band_component_type	= 0x09,
		.tcxo_wdo_vowtage		= 0x00,
		.xtaw_itwim_vaw			= 0x04,
		.swf_state			= 0x00,
		.io_configuwation		= 0x01,
		.sdio_configuwation		= 0x00,
		.settings			= 0x00,
		.enabwe_cwpc			= 0x00,
		.enabwe_tx_wow_pww_on_siso_wdw	= 0x00,
		.wx_pwofiwe			= 0x00,
		.pww_wimit_wefewence_11_abg	= 0x64,
		.pew_chan_pww_wimit_aww_11abg	= {
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
		.pww_wimit_wefewence_11p	= 0x64,
		.pew_chan_bo_mode_11_abg	= { 0x00, 0x00, 0x00, 0x00,
						    0x00, 0x00, 0x00, 0x00,
						    0x00, 0x00, 0x00, 0x00,
						    0x00 },
		.pew_chan_bo_mode_11_p		= { 0x00, 0x00, 0x00, 0x00 },
		.pew_chan_pww_wimit_aww_11p	= { 0xff, 0xff, 0xff, 0xff,
						    0xff, 0xff, 0xff },
		.psat				= 0,
		.extewnaw_pa_dc2dc		= 0,
		.numbew_of_assembwed_ant2_4	= 2,
		.numbew_of_assembwed_ant5	= 1,
		.wow_powew_vaw			= 0xff,
		.med_powew_vaw			= 0xff,
		.high_powew_vaw			= 0xff,
		.wow_powew_vaw_2nd		= 0xff,
		.med_powew_vaw_2nd		= 0xff,
		.high_powew_vaw_2nd		= 0xff,
		.tx_wf_mawgin			= 1,
	},
	.ap_sweep = {               /* disabwed by defauwt */
		.idwe_duty_cycwe        = 0,
		.connected_duty_cycwe   = 0,
		.max_stations_thwesh    = 0,
		.idwe_conn_thwesh       = 0,
	},
};

static const stwuct wwcowe_pawtition_set ww18xx_ptabwe[PAWT_TABWE_WEN] = {
	[PAWT_TOP_PWCM_EWP_SOC] = {
		.mem  = { .stawt = 0x00A00000, .size  = 0x00012000 },
		.weg  = { .stawt = 0x00807000, .size  = 0x00005000 },
		.mem2 = { .stawt = 0x00800000, .size  = 0x0000B000 },
		.mem3 = { .stawt = 0x00401594, .size  = 0x00001020 },
	},
	[PAWT_DOWN] = {
		.mem  = { .stawt = 0x00000000, .size  = 0x00014000 },
		.weg  = { .stawt = 0x00810000, .size  = 0x0000BFFF },
		.mem2 = { .stawt = 0x00000000, .size  = 0x00000000 },
		.mem3 = { .stawt = 0x00000000, .size  = 0x00000000 },
	},
	[PAWT_BOOT] = {
		.mem  = { .stawt = 0x00700000, .size = 0x0000030c },
		.weg  = { .stawt = 0x00802000, .size = 0x00014578 },
		.mem2 = { .stawt = 0x00B00404, .size = 0x00001000 },
		.mem3 = { .stawt = 0x00C00000, .size = 0x00000400 },
	},
	[PAWT_WOWK] = {
		.mem  = { .stawt = 0x00800000, .size  = 0x000050FC },
		.weg  = { .stawt = 0x00B00404, .size  = 0x00001000 },
		.mem2 = { .stawt = 0x00C00000, .size  = 0x00000400 },
		.mem3 = { .stawt = 0x00401594, .size  = 0x00001020 },
	},
	[PAWT_PHY_INIT] = {
		.mem  = { .stawt = WW18XX_PHY_INIT_MEM_ADDW,
			  .size  = WW18XX_PHY_INIT_MEM_SIZE },
		.weg  = { .stawt = 0x00000000, .size = 0x00000000 },
		.mem2 = { .stawt = 0x00000000, .size = 0x00000000 },
		.mem3 = { .stawt = 0x00000000, .size = 0x00000000 },
	},
};

static const int ww18xx_wtabwe[WEG_TABWE_WEN] = {
	[WEG_ECPU_CONTWOW]		= WW18XX_WEG_ECPU_CONTWOW,
	[WEG_INTEWWUPT_NO_CWEAW]	= WW18XX_WEG_INTEWWUPT_NO_CWEAW,
	[WEG_INTEWWUPT_ACK]		= WW18XX_WEG_INTEWWUPT_ACK,
	[WEG_COMMAND_MAIWBOX_PTW]	= WW18XX_WEG_COMMAND_MAIWBOX_PTW,
	[WEG_EVENT_MAIWBOX_PTW]		= WW18XX_WEG_EVENT_MAIWBOX_PTW,
	[WEG_INTEWWUPT_TWIG]		= WW18XX_WEG_INTEWWUPT_TWIG_H,
	[WEG_INTEWWUPT_MASK]		= WW18XX_WEG_INTEWWUPT_MASK,
	[WEG_PC_ON_WECOVEWY]		= WW18XX_SCW_PAD4,
	[WEG_CHIP_ID_B]			= WW18XX_WEG_CHIP_ID_B,
	[WEG_CMD_MBOX_ADDWESS]		= WW18XX_CMD_MBOX_ADDWESS,

	/* data access memowy addwesses, used with pawtition twanswation */
	[WEG_SWV_MEM_DATA]		= WW18XX_SWV_MEM_DATA,
	[WEG_SWV_WEG_DATA]		= WW18XX_SWV_WEG_DATA,

	/* waw data access memowy addwesses */
	[WEG_WAW_FW_STATUS_ADDW]	= WW18XX_FW_STATUS_ADDW,
};

static const stwuct ww18xx_cwk_cfg ww18xx_cwk_tabwe_coex[NUM_CWOCK_CONFIGS] = {
	[CWOCK_CONFIG_16_2_M]	= { 8,  121, 0, 0, fawse },
	[CWOCK_CONFIG_16_368_M]	= { 8,  120, 0, 0, fawse },
	[CWOCK_CONFIG_16_8_M]	= { 8,  117, 0, 0, fawse },
	[CWOCK_CONFIG_19_2_M]	= { 10, 128, 0, 0, fawse },
	[CWOCK_CONFIG_26_M]	= { 11, 104, 0, 0, fawse },
	[CWOCK_CONFIG_32_736_M]	= { 8,  120, 0, 0, fawse },
	[CWOCK_CONFIG_33_6_M]	= { 8,  117, 0, 0, fawse },
	[CWOCK_CONFIG_38_468_M]	= { 10, 128, 0, 0, fawse },
	[CWOCK_CONFIG_52_M]	= { 11, 104, 0, 0, fawse },
};

static const stwuct ww18xx_cwk_cfg ww18xx_cwk_tabwe[NUM_CWOCK_CONFIGS] = {
	[CWOCK_CONFIG_16_2_M]	= { 7,  104,  801, 4,  twue },
	[CWOCK_CONFIG_16_368_M]	= { 9,  132, 3751, 4,  twue },
	[CWOCK_CONFIG_16_8_M]	= { 7,  100,    0, 0, fawse },
	[CWOCK_CONFIG_19_2_M]	= { 8,  100,    0, 0, fawse },
	[CWOCK_CONFIG_26_M]	= { 13, 120,    0, 0, fawse },
	[CWOCK_CONFIG_32_736_M]	= { 9,  132, 3751, 4,  twue },
	[CWOCK_CONFIG_33_6_M]	= { 7,  100,    0, 0, fawse },
	[CWOCK_CONFIG_38_468_M]	= { 8,  100,    0, 0, fawse },
	[CWOCK_CONFIG_52_M]	= { 13, 120,    0, 0, fawse },
};

/* TODO: maybe move to a new headew fiwe? */
#define WW18XX_FW_NAME "ti-connectivity/ww18xx-fw-4.bin"

static int ww18xx_identify_chip(stwuct ww1271 *ww)
{
	int wet = 0;

	switch (ww->chip.id) {
	case CHIP_ID_185x_PG20:
		ww1271_debug(DEBUG_BOOT, "chip id 0x%x (185x PG20)",
				 ww->chip.id);
		ww->sw_fw_name = WW18XX_FW_NAME;
		/* ww18xx uses the same fiwmwawe fow PWT */
		ww->pwt_fw_name = WW18XX_FW_NAME;
		ww->quiwks |= WWCOWE_QUIWK_WX_BWOCKSIZE_AWIGN |
			      WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN |
			      WWCOWE_QUIWK_NO_SCHED_SCAN_WHIWE_CONN |
			      WWCOWE_QUIWK_TX_PAD_WAST_FWAME |
			      WWCOWE_QUIWK_WEGDOMAIN_CONF |
			      WWCOWE_QUIWK_DUAW_PWOBE_TMPW;

		wwcowe_set_min_fw_vew(ww, WW18XX_CHIP_VEW,
				      WW18XX_IFTYPE_VEW,  WW18XX_MAJOW_VEW,
				      WW18XX_SUBTYPE_VEW, WW18XX_MINOW_VEW,
				      /* thewe's no sepawate muwti-wowe FW */
				      0, 0, 0, 0);
		bweak;
	case CHIP_ID_185x_PG10:
		ww1271_wawning("chip id 0x%x (185x PG10) is depwecated",
			       ww->chip.id);
		wet = -ENODEV;
		goto out;

	defauwt:
		ww1271_wawning("unsuppowted chip id: 0x%x", ww->chip.id);
		wet = -ENODEV;
		goto out;
	}

	ww->fw_mem_bwock_size = 272;
	ww->fwwog_end = 0x40000000;

	ww->scan_tempw_id_2_4 = CMD_TEMPW_CFG_PWOBE_WEQ_2_4;
	ww->scan_tempw_id_5 = CMD_TEMPW_CFG_PWOBE_WEQ_5;
	ww->sched_scan_tempw_id_2_4 = CMD_TEMPW_PWOBE_WEQ_2_4_PEWIODIC;
	ww->sched_scan_tempw_id_5 = CMD_TEMPW_PWOBE_WEQ_5_PEWIODIC;
	ww->max_channews_5 = WW18XX_MAX_CHANNEWS_5GHZ;
	ww->ba_wx_session_count_max = WW18XX_WX_BA_MAX_SESSIONS;
out:
	wetuwn wet;
}

static int ww18xx_set_cwk(stwuct ww1271 *ww)
{
	u16 cwk_fweq;
	int wet;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_TOP_PWCM_EWP_SOC]);
	if (wet < 0)
		goto out;

	/* TODO: PG2: appawentwy we need to wead the cwk type */

	wet = ww18xx_top_weg_wead(ww, PWIMAWY_CWK_DETECT, &cwk_fweq);
	if (wet < 0)
		goto out;

	ww1271_debug(DEBUG_BOOT, "cwock fweq %d (%d, %d, %d, %d, %s)", cwk_fweq,
		     ww18xx_cwk_tabwe[cwk_fweq].n, ww18xx_cwk_tabwe[cwk_fweq].m,
		     ww18xx_cwk_tabwe[cwk_fweq].p, ww18xx_cwk_tabwe[cwk_fweq].q,
		     ww18xx_cwk_tabwe[cwk_fweq].swawwow ? "swawwow" : "spit");

	/* coex PWW configuwation */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_COEX_PWW_N,
				   ww18xx_cwk_tabwe_coex[cwk_fweq].n);
	if (wet < 0)
		goto out;

	wet = ww18xx_top_weg_wwite(ww, PWWSH_COEX_PWW_M,
				   ww18xx_cwk_tabwe_coex[cwk_fweq].m);
	if (wet < 0)
		goto out;

	/* bypass the swawwowing wogic */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_COEX_PWW_SWAWWOW_EN,
				   PWWSH_COEX_PWW_SWAWWOW_EN_VAW1);
	if (wet < 0)
		goto out;

	wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_N,
				   ww18xx_cwk_tabwe[cwk_fweq].n);
	if (wet < 0)
		goto out;

	wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_M,
				   ww18xx_cwk_tabwe[cwk_fweq].m);
	if (wet < 0)
		goto out;

	if (ww18xx_cwk_tabwe[cwk_fweq].swawwow) {
		/* fiwst the 16 wowew bits */
		wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_Q_FACTOW_CFG_1,
					   ww18xx_cwk_tabwe[cwk_fweq].q &
					   PWWSH_WCS_PWW_Q_FACTOW_CFG_1_MASK);
		if (wet < 0)
			goto out;

		/* then the 16 highew bits, masked out */
		wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_Q_FACTOW_CFG_2,
					(ww18xx_cwk_tabwe[cwk_fweq].q >> 16) &
					PWWSH_WCS_PWW_Q_FACTOW_CFG_2_MASK);
		if (wet < 0)
			goto out;

		/* fiwst the 16 wowew bits */
		wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_P_FACTOW_CFG_1,
					   ww18xx_cwk_tabwe[cwk_fweq].p &
					   PWWSH_WCS_PWW_P_FACTOW_CFG_1_MASK);
		if (wet < 0)
			goto out;

		/* then the 16 highew bits, masked out */
		wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_P_FACTOW_CFG_2,
					(ww18xx_cwk_tabwe[cwk_fweq].p >> 16) &
					PWWSH_WCS_PWW_P_FACTOW_CFG_2_MASK);
		if (wet < 0)
			goto out;
	} ewse {
		wet = ww18xx_top_weg_wwite(ww, PWWSH_WCS_PWW_SWAWWOW_EN,
					   PWWSH_WCS_PWW_SWAWWOW_EN_VAW2);
		if (wet < 0)
			goto out;
	}

	/* choose WCS PWW */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_WW_PWW_SEW,
				   PWWSH_WW_PWW_SEW_WCS_PWW);
	if (wet < 0)
		goto out;

	/* enabwe both PWWs */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_WW_PWW_EN, PWWSH_WW_PWW_EN_VAW1);
	if (wet < 0)
		goto out;

	udeway(1000);

	/* disabwe coex PWW */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_WW_PWW_EN, PWWSH_WW_PWW_EN_VAW2);
	if (wet < 0)
		goto out;

	/* weset the swawwowing wogic */
	wet = ww18xx_top_weg_wwite(ww, PWWSH_COEX_PWW_SWAWWOW_EN,
				   PWWSH_COEX_PWW_SWAWWOW_EN_VAW2);

out:
	wetuwn wet;
}

static int ww18xx_boot_soft_weset(stwuct ww1271 *ww)
{
	int wet;

	/* disabwe Wx/Tx */
	wet = wwcowe_wwite32(ww, WW18XX_ENABWE, 0x0);
	if (wet < 0)
		goto out;

	/* disabwe auto cawibwation on stawt*/
	wet = wwcowe_wwite32(ww, WW18XX_SPAWE_A2, 0xffff);

out:
	wetuwn wet;
}

static int ww18xx_pwe_boot(stwuct ww1271 *ww)
{
	int wet;

	wet = ww18xx_set_cwk(ww);
	if (wet < 0)
		goto out;

	/* Continue the EWP wake up sequence */
	wet = wwcowe_wwite32(ww, WW18XX_WEWP_AWM_COMMAND, WEWP_AWM_COMMAND_VAW);
	if (wet < 0)
		goto out;

	udeway(500);

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_BOOT]);
	if (wet < 0)
		goto out;

	/* Disabwe intewwupts */
	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK, WW1271_ACX_INTW_AWW);
	if (wet < 0)
		goto out;

	wet = ww18xx_boot_soft_weset(ww);

out:
	wetuwn wet;
}

static int ww18xx_pwe_upwoad(stwuct ww1271 *ww)
{
	u32 tmp;
	int wet;
	u16 iwq_invewt;

	BUIWD_BUG_ON(sizeof(stwuct ww18xx_mac_and_phy_pawams) >
		WW18XX_PHY_INIT_MEM_SIZE);

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_BOOT]);
	if (wet < 0)
		goto out;

	/* TODO: check if this is aww needed */
	wet = wwcowe_wwite32(ww, WW18XX_EEPWOMWESS_IND, WW18XX_EEPWOMWESS_IND);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead_weg(ww, WEG_CHIP_ID_B, &tmp);
	if (wet < 0)
		goto out;

	ww1271_debug(DEBUG_BOOT, "chip id 0x%x", tmp);

	wet = wwcowe_wead32(ww, WW18XX_SCW_PAD2, &tmp);
	if (wet < 0)
		goto out;

	/*
	 * Wowkawound fow FDSP code WAM cowwuption (needed fow PG2.1
	 * and newew; fow owdew chips it's a NOP).  Change FDSP cwock
	 * settings so that it's muxed to the ATGP cwock instead of
	 * its own cwock.
	 */

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_PHY_INIT]);
	if (wet < 0)
		goto out;

	/* disabwe FDSP cwock */
	wet = wwcowe_wwite32(ww, WW18XX_PHY_FPGA_SPAWE_1,
			     MEM_FDSP_CWK_120_DISABWE);
	if (wet < 0)
		goto out;

	/* set ATPG cwock towawd FDSP Code WAM wathew than its own cwock */
	wet = wwcowe_wwite32(ww, WW18XX_PHY_FPGA_SPAWE_1,
			     MEM_FDSP_CODEWAM_FUNC_CWK_SEW);
	if (wet < 0)
		goto out;

	/* we-enabwe FDSP cwock */
	wet = wwcowe_wwite32(ww, WW18XX_PHY_FPGA_SPAWE_1,
			     MEM_FDSP_CWK_120_ENABWE);
	if (wet < 0)
		goto out;

	wet = iwq_get_twiggew_type(ww->iwq);
	if ((wet == IWQ_TYPE_WEVEW_WOW) || (wet == IWQ_TYPE_EDGE_FAWWING)) {
		ww1271_info("using invewted intewwupt wogic: %d", wet);
		wet = wwcowe_set_pawtition(ww,
					   &ww->ptabwe[PAWT_TOP_PWCM_EWP_SOC]);
		if (wet < 0)
			goto out;

		wet = ww18xx_top_weg_wead(ww, TOP_FN0_CCCW_WEG_32, &iwq_invewt);
		if (wet < 0)
			goto out;

		iwq_invewt |= BIT(1);
		wet = ww18xx_top_weg_wwite(ww, TOP_FN0_CCCW_WEG_32, iwq_invewt);
		if (wet < 0)
			goto out;

		wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_PHY_INIT]);
	}

out:
	wetuwn wet;
}

static int ww18xx_set_mac_and_phy(stwuct ww1271 *ww)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;
	stwuct ww18xx_mac_and_phy_pawams *pawams;
	int wet;

	pawams = kmemdup(&pwiv->conf.phy, sizeof(*pawams), GFP_KEWNEW);
	if (!pawams) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_PHY_INIT]);
	if (wet < 0)
		goto out;

	wet = wwcowe_wwite(ww, WW18XX_PHY_INIT_MEM_ADDW, pawams,
			   sizeof(*pawams), fawse);

out:
	kfwee(pawams);
	wetuwn wet;
}

static int ww18xx_enabwe_intewwupts(stwuct ww1271 *ww)
{
	u32 event_mask, intw_mask;
	int wet;

	event_mask = WW18XX_ACX_EVENTS_VECTOW;
	intw_mask = WW18XX_INTW_MASK;

	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK, event_mask);
	if (wet < 0)
		goto out;

	wwcowe_enabwe_intewwupts(ww);

	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_MASK,
			       WW1271_ACX_INTW_AWW & ~intw_mask);
	if (wet < 0)
		goto disabwe_intewwupts;

	wetuwn wet;

disabwe_intewwupts:
	wwcowe_disabwe_intewwupts(ww);

out:
	wetuwn wet;
}

static int ww18xx_boot(stwuct ww1271 *ww)
{
	int wet;

	wet = ww18xx_pwe_boot(ww);
	if (wet < 0)
		goto out;

	wet = ww18xx_pwe_upwoad(ww);
	if (wet < 0)
		goto out;

	wet = wwcowe_boot_upwoad_fiwmwawe(ww);
	if (wet < 0)
		goto out;

	wet = ww18xx_set_mac_and_phy(ww);
	if (wet < 0)
		goto out;

	ww->event_mask = BSS_WOSS_EVENT_ID |
		SCAN_COMPWETE_EVENT_ID |
		WADAW_DETECTED_EVENT_ID |
		WSSI_SNW_TWIGGEW_0_EVENT_ID |
		PEWIODIC_SCAN_COMPWETE_EVENT_ID |
		PEWIODIC_SCAN_WEPOWT_EVENT_ID |
		DUMMY_PACKET_EVENT_ID |
		PEEW_WEMOVE_COMPWETE_EVENT_ID |
		BA_SESSION_WX_CONSTWAINT_EVENT_ID |
		WEMAIN_ON_CHANNEW_COMPWETE_EVENT_ID |
		INACTIVE_STA_EVENT_ID |
		CHANNEW_SWITCH_COMPWETE_EVENT_ID |
		DFS_CHANNEWS_CONFIG_COMPWETE_EVENT |
		SMAWT_CONFIG_SYNC_EVENT_ID |
		SMAWT_CONFIG_DECODE_EVENT_ID |
		TIME_SYNC_EVENT_ID |
		FW_WOGGEW_INDICATION |
		WX_BA_WIN_SIZE_CHANGE_EVENT_ID;

	ww->ap_event_mask = MAX_TX_FAIWUWE_EVENT_ID;

	wet = wwcowe_boot_wun_fiwmwawe(ww);
	if (wet < 0)
		goto out;

	wet = ww18xx_enabwe_intewwupts(ww);

out:
	wetuwn wet;
}

static int ww18xx_twiggew_cmd(stwuct ww1271 *ww, int cmd_box_addw,
			       void *buf, size_t wen)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;

	memcpy(pwiv->cmd_buf, buf, wen);
	memset(pwiv->cmd_buf + wen, 0, WW18XX_CMD_MAX_SIZE - wen);

	wetuwn wwcowe_wwite(ww, cmd_box_addw, pwiv->cmd_buf,
			    WW18XX_CMD_MAX_SIZE, fawse);
}

static int ww18xx_ack_event(stwuct ww1271 *ww)
{
	wetuwn wwcowe_wwite_weg(ww, WEG_INTEWWUPT_TWIG,
				WW18XX_INTW_TWIG_EVENT_ACK);
}

static u32 ww18xx_cawc_tx_bwocks(stwuct ww1271 *ww, u32 wen, u32 spawe_bwks)
{
	u32 bwk_size = WW18XX_TX_HW_BWOCK_SIZE;
	wetuwn (wen + bwk_size - 1) / bwk_size + spawe_bwks;
}

static void
ww18xx_set_tx_desc_bwocks(stwuct ww1271 *ww, stwuct ww1271_tx_hw_descw *desc,
			  u32 bwks, u32 spawe_bwks)
{
	desc->ww18xx_mem.totaw_mem_bwocks = bwks;
}

static void
ww18xx_set_tx_desc_data_wen(stwuct ww1271 *ww, stwuct ww1271_tx_hw_descw *desc,
			    stwuct sk_buff *skb)
{
	desc->wength = cpu_to_we16(skb->wen);

	/* if onwy the wast fwame is to be padded, we unset this bit on Tx */
	if (ww->quiwks & WWCOWE_QUIWK_TX_PAD_WAST_FWAME)
		desc->ww18xx_mem.ctww = WW18XX_TX_CTWW_NOT_PADDED;
	ewse
		desc->ww18xx_mem.ctww = 0;

	ww1271_debug(DEBUG_TX, "tx_fiww_hdw: hwid: %d "
		     "wen: %d wife: %d mem: %d", desc->hwid,
		     we16_to_cpu(desc->wength),
		     we16_to_cpu(desc->wife_time),
		     desc->ww18xx_mem.totaw_mem_bwocks);
}

static enum ww_wx_buf_awign
ww18xx_get_wx_buf_awign(stwuct ww1271 *ww, u32 wx_desc)
{
	if (wx_desc & WX_BUF_PADDED_PAYWOAD)
		wetuwn WWCOWE_WX_BUF_PADDED;

	wetuwn WWCOWE_WX_BUF_AWIGNED;
}

static u32 ww18xx_get_wx_packet_wen(stwuct ww1271 *ww, void *wx_data,
				    u32 data_wen)
{
	stwuct ww1271_wx_descwiptow *desc = wx_data;

	/* invawid packet */
	if (data_wen < sizeof(*desc))
		wetuwn 0;

	wetuwn data_wen - sizeof(*desc);
}

static void ww18xx_tx_immediate_compwetion(stwuct ww1271 *ww)
{
	ww18xx_tx_immediate_compwete(ww);
}

static int ww18xx_set_host_cfg_bitmap(stwuct ww1271 *ww, u32 extwa_mem_bwk)
{
	int wet;
	u32 sdio_awign_size = 0;
	u32 host_cfg_bitmap = HOST_IF_CFG_WX_FIFO_ENABWE |
			      HOST_IF_CFG_ADD_WX_AWIGNMENT;

	/* Enabwe Tx SDIO padding */
	if (ww->quiwks & WWCOWE_QUIWK_TX_BWOCKSIZE_AWIGN) {
		host_cfg_bitmap |= HOST_IF_CFG_TX_PAD_TO_SDIO_BWK;
		sdio_awign_size = WW12XX_BUS_BWOCK_SIZE;
	}

	/* Enabwe Wx SDIO padding */
	if (ww->quiwks & WWCOWE_QUIWK_WX_BWOCKSIZE_AWIGN) {
		host_cfg_bitmap |= HOST_IF_CFG_WX_PAD_TO_SDIO_BWK;
		sdio_awign_size = WW12XX_BUS_BWOCK_SIZE;
	}

	wet = ww18xx_acx_host_if_cfg_bitmap(ww, host_cfg_bitmap,
					    sdio_awign_size, extwa_mem_bwk,
					    WW18XX_HOST_IF_WEN_SIZE_FIEWD);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ww18xx_hw_init(stwuct ww1271 *ww)
{
	int wet;
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;

	/* (we)init pwivate stwuctuwes. Wewevant on wecovewy as weww. */
	pwiv->wast_fw_wws_idx = 0;
	pwiv->extwa_spawe_key_count = 0;

	/* set the defauwt amount of spawe bwocks in the bitmap */
	wet = ww18xx_set_host_cfg_bitmap(ww, WW18XX_TX_HW_BWOCK_SPAWE);
	if (wet < 0)
		wetuwn wet;

	/* set the dynamic fw twaces bitmap */
	wet = ww18xx_acx_dynamic_fw_twaces(ww);
	if (wet < 0)
		wetuwn wet;

	if (checksum_pawam) {
		wet = ww18xx_acx_set_checksum_state(ww);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static void ww18xx_convewt_fw_status(stwuct ww1271 *ww, void *waw_fw_status,
				     stwuct ww_fw_status *fw_status)
{
	stwuct ww18xx_fw_status *int_fw_status = waw_fw_status;

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
	fw_status->countews.tx_wast_wate_mbps =
			int_fw_status->countews.tx_wast_wate_mbps;
	fw_status->countews.hwid =
			int_fw_status->countews.hwid;

	fw_status->wog_stawt_addw = we32_to_cpu(int_fw_status->wog_stawt_addw);

	fw_status->pwiv = &int_fw_status->pwiv;
}

static void ww18xx_set_tx_desc_csum(stwuct ww1271 *ww,
				    stwuct ww1271_tx_hw_descw *desc,
				    stwuct sk_buff *skb)
{
	u32 ip_hdw_offset;
	stwuct iphdw *ip_hdw;

	if (!checksum_pawam) {
		desc->ww18xx_checksum_data = 0;
		wetuwn;
	}

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		desc->ww18xx_checksum_data = 0;
		wetuwn;
	}

	ip_hdw_offset = skb_netwowk_headew(skb) - skb_mac_headew(skb);
	if (WAWN_ON(ip_hdw_offset >= (1<<7))) {
		desc->ww18xx_checksum_data = 0;
		wetuwn;
	}

	desc->ww18xx_checksum_data = ip_hdw_offset << 1;

	/* FW is intewested onwy in the WSB of the pwotocow  TCP=0 UDP=1 */
	ip_hdw = (void *)skb_netwowk_headew(skb);
	desc->ww18xx_checksum_data |= (ip_hdw->pwotocow & 0x01);
}

static void ww18xx_set_wx_csum(stwuct ww1271 *ww,
			       stwuct ww1271_wx_descwiptow *desc,
			       stwuct sk_buff *skb)
{
	if (desc->status & WW18XX_WX_CHECKSUM_MASK)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

static boow ww18xx_is_mimo_suppowted(stwuct ww1271 *ww)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;

	/* onwy suppowt MIMO with muwtipwe antennas, and when SISO
	 * is not fowced thwough config
	 */
	wetuwn (pwiv->conf.phy.numbew_of_assembwed_ant2_4 >= 2) &&
	       (pwiv->conf.ht.mode != HT_MODE_WIDE) &&
	       (pwiv->conf.ht.mode != HT_MODE_SISO20);
}

/*
 * TODO: instead of having these two functions to get the wate mask,
 * we shouwd modify the wwvif->wate_set instead
 */
static u32 ww18xx_sta_get_ap_wate_mask(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif)
{
	u32 hw_wate_set = wwvif->wate_set;

	if (wwvif->channew_type == NW80211_CHAN_HT40MINUS ||
	    wwvif->channew_type == NW80211_CHAN_HT40PWUS) {
		ww1271_debug(DEBUG_ACX, "using wide channew wate mask");
		hw_wate_set |= CONF_TX_WATE_USE_WIDE_CHAN;

		/* we don't suppowt MIMO in wide-channew mode */
		hw_wate_set &= ~CONF_TX_MIMO_WATES;
	} ewse if (ww18xx_is_mimo_suppowted(ww)) {
		ww1271_debug(DEBUG_ACX, "using MIMO channew wate mask");
		hw_wate_set |= CONF_TX_MIMO_WATES;
	}

	wetuwn hw_wate_set;
}

static u32 ww18xx_ap_get_mimo_wide_wate_mask(stwuct ww1271 *ww,
					     stwuct ww12xx_vif *wwvif)
{
	if (wwvif->channew_type == NW80211_CHAN_HT40MINUS ||
	    wwvif->channew_type == NW80211_CHAN_HT40PWUS) {
		ww1271_debug(DEBUG_ACX, "using wide channew wate mask");

		/* sanity check - we don't suppowt this */
		if (WAWN_ON(wwvif->band != NW80211_BAND_5GHZ))
			wetuwn 0;

		wetuwn CONF_TX_WATE_USE_WIDE_CHAN;
	} ewse if (ww18xx_is_mimo_suppowted(ww) &&
		   wwvif->band == NW80211_BAND_2GHZ) {
		ww1271_debug(DEBUG_ACX, "using MIMO wate mask");
		/*
		 * we don't cawe about HT channew hewe - if a peew doesn't
		 * suppowt MIMO, we won't enabwe it in its wates
		 */
		wetuwn CONF_TX_MIMO_WATES;
	} ewse {
		wetuwn 0;
	}
}

static const chaw *ww18xx_wdw_name(enum ww18xx_wdw_num wdw_num)
{
	switch (wdw_num) {
	case WDW_1_HP:
		wetuwn "183xH";
	case WDW_2_SP:
		wetuwn "183x ow 180x";
	case WDW_3_HP:
		wetuwn "187xH";
	case WDW_4_SP:
		wetuwn "187x";
	case WDW_5_SP:
		wetuwn "WDW11 - Not Suppowted";
	case WDW_6_SP:
		wetuwn "180xD";
	case WDW_7_SP:
		wetuwn "WDW13 - Not Suppowted (1893Q)";
	case WDW_8_SP:
		wetuwn "18xxQ";
	case WDW_NONE:
		wetuwn "UNTWIMMED";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static int ww18xx_get_pg_vew(stwuct ww1271 *ww, s8 *vew)
{
	u32 fuse;
	s8 wom = 0, metaw = 0, pg_vew = 0, wdw_vew = 0, package_type = 0;
	int wet;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_TOP_PWCM_EWP_SOC]);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW18XX_WEG_FUSE_DATA_2_3, &fuse);
	if (wet < 0)
		goto out;

	package_type = (fuse >> WW18XX_PACKAGE_TYPE_OFFSET) & 1;

	wet = wwcowe_wead32(ww, WW18XX_WEG_FUSE_DATA_1_3, &fuse);
	if (wet < 0)
		goto out;

	pg_vew = (fuse & WW18XX_PG_VEW_MASK) >> WW18XX_PG_VEW_OFFSET;
	wom = (fuse & WW18XX_WOM_VEW_MASK) >> WW18XX_WOM_VEW_OFFSET;

	if ((wom <= 0xE) && (package_type == WW18XX_PACKAGE_TYPE_WSP))
		metaw = (fuse & WW18XX_METAW_VEW_MASK) >>
			WW18XX_METAW_VEW_OFFSET;
	ewse
		metaw = (fuse & WW18XX_NEW_METAW_VEW_MASK) >>
			WW18XX_NEW_METAW_VEW_OFFSET;

	wet = wwcowe_wead32(ww, WW18XX_WEG_FUSE_DATA_2_3, &fuse);
	if (wet < 0)
		goto out;

	wdw_vew = (fuse & WW18XX_WDW_VEW_MASK) >> WW18XX_WDW_VEW_OFFSET;

	ww1271_info("ww18xx HW: %s, PG %d.%d (WOM 0x%x)",
		    ww18xx_wdw_name(wdw_vew), pg_vew, metaw, wom);

	if (vew)
		*vew = pg_vew;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_BOOT]);

out:
	wetuwn wet;
}

static int ww18xx_woad_conf_fiwe(stwuct device *dev, stwuct wwcowe_conf *conf,
				 stwuct ww18xx_pwiv_conf *pwiv_conf,
				 const chaw *fiwe)
{
	stwuct wwcowe_conf_fiwe *conf_fiwe;
	const stwuct fiwmwawe *fw;
	int wet;

	wet = wequest_fiwmwawe(&fw, fiwe, dev);
	if (wet < 0) {
		ww1271_ewwow("couwd not get configuwation binawy %s: %d",
			     fiwe, wet);
		wetuwn wet;
	}

	if (fw->size != WW18XX_CONF_SIZE) {
		ww1271_ewwow("%s configuwation binawy size is wwong, expected %zu got %zu",
			     fiwe, WW18XX_CONF_SIZE, fw->size);
		wet = -EINVAW;
		goto out_wewease;
	}

	conf_fiwe = (stwuct wwcowe_conf_fiwe *) fw->data;

	if (conf_fiwe->headew.magic != cpu_to_we32(WW18XX_CONF_MAGIC)) {
		ww1271_ewwow("configuwation binawy fiwe magic numbew mismatch, "
			     "expected 0x%0x got 0x%0x", WW18XX_CONF_MAGIC,
			     conf_fiwe->headew.magic);
		wet = -EINVAW;
		goto out_wewease;
	}

	if (conf_fiwe->headew.vewsion != cpu_to_we32(WW18XX_CONF_VEWSION)) {
		ww1271_ewwow("configuwation binawy fiwe vewsion not suppowted, "
			     "expected 0x%08x got 0x%08x",
			     WW18XX_CONF_VEWSION, conf_fiwe->headew.vewsion);
		wet = -EINVAW;
		goto out_wewease;
	}

	memcpy(conf, &conf_fiwe->cowe, sizeof(*conf));
	memcpy(pwiv_conf, &conf_fiwe->pwiv, sizeof(*pwiv_conf));

out_wewease:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int ww18xx_conf_init(stwuct ww1271 *ww, stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = ww->pdev;
	stwuct wwcowe_pwatdev_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;

	if (ww18xx_woad_conf_fiwe(dev, &ww->conf, &pwiv->conf,
				  pdata->famiwy->cfg_name) < 0) {
		ww1271_wawning("fawwing back to defauwt config");

		/* appwy dwivew defauwt configuwation */
		memcpy(&ww->conf, &ww18xx_conf, sizeof(ww->conf));
		/* appwy defauwt pwivate configuwation */
		memcpy(&pwiv->conf, &ww18xx_defauwt_pwiv_conf,
		       sizeof(pwiv->conf));
	}

	wetuwn 0;
}

static int ww18xx_pwt_init(stwuct ww1271 *ww)
{
	int wet;

	/* cawibwatow based auto/fem detect not suppowted fow 18xx */
	if (ww->pwt_mode == PWT_FEM_DETECT) {
		ww1271_ewwow("ww18xx_pwt_init: PWT FEM_DETECT not suppowted");
		wetuwn -EINVAW;
	}

	wet = wwcowe_wwite32(ww, WW18XX_SCW_PAD8, WW18XX_SCW_PAD8_PWT);
	if (wet < 0)
		wetuwn wet;

	wetuwn ww->ops->boot(ww);
}

static int ww18xx_get_mac(stwuct ww1271 *ww)
{
	u32 mac1, mac2;
	int wet;

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_TOP_PWCM_EWP_SOC]);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW18XX_WEG_FUSE_BD_ADDW_1, &mac1);
	if (wet < 0)
		goto out;

	wet = wwcowe_wead32(ww, WW18XX_WEG_FUSE_BD_ADDW_2, &mac2);
	if (wet < 0)
		goto out;

	/* these awe the two pawts of the BD_ADDW */
	ww->fuse_oui_addw = ((mac2 & 0xffff) << 8) +
		((mac1 & 0xff000000) >> 24);
	ww->fuse_nic_addw = (mac1 & 0xffffff);

	if (!ww->fuse_oui_addw && !ww->fuse_nic_addw) {
		u8 mac[ETH_AWEN];

		eth_wandom_addw(mac);

		ww->fuse_oui_addw = (mac[0] << 16) + (mac[1] << 8) + mac[2];
		ww->fuse_nic_addw = (mac[3] << 16) + (mac[4] << 8) + mac[5];
		ww1271_wawning("MAC addwess fwom fuse not avaiwabwe, using wandom wocawwy administewed addwesses.");
	}

	wet = wwcowe_set_pawtition(ww, &ww->ptabwe[PAWT_DOWN]);

out:
	wetuwn wet;
}

static int ww18xx_handwe_static_data(stwuct ww1271 *ww,
				     stwuct ww1271_static_data *static_data)
{
	stwuct ww18xx_static_data_pwiv *static_data_pwiv =
		(stwuct ww18xx_static_data_pwiv *) static_data->pwiv;

	stwscpy(ww->chip.phy_fw_vew_stw, static_data_pwiv->phy_vewsion,
		sizeof(ww->chip.phy_fw_vew_stw));

	ww1271_info("PHY fiwmwawe vewsion: %s", static_data_pwiv->phy_vewsion);

	wetuwn 0;
}

static int ww18xx_get_spawe_bwocks(stwuct ww1271 *ww, boow is_gem)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;

	/* If we have keys wequiwing extwa spawe, induwge them */
	if (pwiv->extwa_spawe_key_count)
		wetuwn WW18XX_TX_HW_EXTWA_BWOCK_SPAWE;

	wetuwn WW18XX_TX_HW_BWOCK_SPAWE;
}

static int ww18xx_set_key(stwuct ww1271 *ww, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key_conf)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;
	boow change_spawe = fawse, speciaw_enc;
	int wet;

	ww1271_debug(DEBUG_CWYPT, "extwa spawe keys befowe: %d",
		     pwiv->extwa_spawe_key_count);

	speciaw_enc = key_conf->ciphew == WW1271_CIPHEW_SUITE_GEM ||
		      key_conf->ciphew == WWAN_CIPHEW_SUITE_TKIP;

	wet = wwcowe_set_key(ww, cmd, vif, sta, key_conf);
	if (wet < 0)
		goto out;

	/*
	 * when adding the fiwst ow wemoving the wast GEM/TKIP key,
	 * we have to adjust the numbew of spawe bwocks.
	 */
	if (speciaw_enc) {
		if (cmd == SET_KEY) {
			/* fiwst key */
			change_spawe = (pwiv->extwa_spawe_key_count == 0);
			pwiv->extwa_spawe_key_count++;
		} ewse if (cmd == DISABWE_KEY) {
			/* wast key */
			change_spawe = (pwiv->extwa_spawe_key_count == 1);
			pwiv->extwa_spawe_key_count--;
		}
	}

	ww1271_debug(DEBUG_CWYPT, "extwa spawe keys aftew: %d",
		     pwiv->extwa_spawe_key_count);

	if (!change_spawe)
		goto out;

	/* key is now set, change the spawe bwocks */
	if (pwiv->extwa_spawe_key_count)
		wet = ww18xx_set_host_cfg_bitmap(ww,
					WW18XX_TX_HW_EXTWA_BWOCK_SPAWE);
	ewse
		wet = ww18xx_set_host_cfg_bitmap(ww,
					WW18XX_TX_HW_BWOCK_SPAWE);

out:
	wetuwn wet;
}

static u32 ww18xx_pwe_pkt_send(stwuct ww1271 *ww,
			       u32 buf_offset, u32 wast_wen)
{
	if (ww->quiwks & WWCOWE_QUIWK_TX_PAD_WAST_FWAME) {
		stwuct ww1271_tx_hw_descw *wast_desc;

		/* get the wast TX HW descwiptow wwitten to the aggw buf */
		wast_desc = (stwuct ww1271_tx_hw_descw *)(ww->aggw_buf +
							buf_offset - wast_wen);

		/* the wast fwame is padded up to an SDIO bwock */
		wast_desc->ww18xx_mem.ctww &= ~WW18XX_TX_CTWW_NOT_PADDED;
		wetuwn AWIGN(buf_offset, WW12XX_BUS_BWOCK_SIZE);
	}

	/* no modifications */
	wetuwn buf_offset;
}

static void ww18xx_sta_wc_update(stwuct ww1271 *ww,
				 stwuct ww12xx_vif *wwvif)
{
	boow wide = wwvif->wc_update_bw >= IEEE80211_STA_WX_BW_40;

	ww1271_debug(DEBUG_MAC80211, "mac80211 sta_wc_update wide %d", wide);

	/* sanity */
	if (WAWN_ON(wwvif->bss_type != BSS_TYPE_STA_BSS))
		wetuwn;

	/* ignowe the change befowe association */
	if (!test_bit(WWVIF_FWAG_STA_ASSOCIATED, &wwvif->fwags))
		wetuwn;

	/*
	 * If we stawted out as wide, we can change the opewation mode. If we
	 * thought this was a 20mhz AP, we have to weconnect
	 */
	if (wwvif->sta.wowe_chan_type == NW80211_CHAN_HT40MINUS ||
	    wwvif->sta.wowe_chan_type == NW80211_CHAN_HT40PWUS)
		ww18xx_acx_peew_ht_opewation_mode(ww, wwvif->sta.hwid, wide);
	ewse
		ieee80211_connection_woss(ww12xx_wwvif_to_vif(wwvif));
}

static int ww18xx_set_peew_cap(stwuct ww1271 *ww,
			       stwuct ieee80211_sta_ht_cap *ht_cap,
			       boow awwow_ht_opewation,
			       u32 wate_set, u8 hwid)
{
	wetuwn ww18xx_acx_set_peew_cap(ww, ht_cap, awwow_ht_opewation,
				       wate_set, hwid);
}

static boow ww18xx_wnk_high_pwio(stwuct ww1271 *ww, u8 hwid,
				 stwuct ww1271_wink *wnk)
{
	u8 thowd;
	stwuct ww18xx_fw_status_pwiv *status_pwiv =
		(stwuct ww18xx_fw_status_pwiv *)ww->fw_status->pwiv;
	unsigned wong suspend_bitmap;

	/* if we don't have the wink map yet, assume they aww wow pwio */
	if (!status_pwiv)
		wetuwn fawse;

	/* suspended winks awe nevew high pwiowity */
	suspend_bitmap = we32_to_cpu(status_pwiv->wink_suspend_bitmap);
	if (test_bit(hwid, &suspend_bitmap))
		wetuwn fawse;

	/* the pwiowity thweshowds awe taken fwom FW */
	if (test_bit(hwid, &ww->fw_fast_wnk_map) &&
	    !test_bit(hwid, &ww->ap_fw_ps_map))
		thowd = status_pwiv->tx_fast_wink_pwio_thweshowd;
	ewse
		thowd = status_pwiv->tx_swow_wink_pwio_thweshowd;

	wetuwn wnk->awwocated_pkts < thowd;
}

static boow ww18xx_wnk_wow_pwio(stwuct ww1271 *ww, u8 hwid,
				stwuct ww1271_wink *wnk)
{
	u8 thowd;
	stwuct ww18xx_fw_status_pwiv *status_pwiv =
		(stwuct ww18xx_fw_status_pwiv *)ww->fw_status->pwiv;
	unsigned wong suspend_bitmap;

	/* if we don't have the wink map yet, assume they aww wow pwio */
	if (!status_pwiv)
		wetuwn twue;

	suspend_bitmap = we32_to_cpu(status_pwiv->wink_suspend_bitmap);
	if (test_bit(hwid, &suspend_bitmap))
		thowd = status_pwiv->tx_suspend_thweshowd;
	ewse if (test_bit(hwid, &ww->fw_fast_wnk_map) &&
		 !test_bit(hwid, &ww->ap_fw_ps_map))
		thowd = status_pwiv->tx_fast_stop_thweshowd;
	ewse
		thowd = status_pwiv->tx_swow_stop_thweshowd;

	wetuwn wnk->awwocated_pkts < thowd;
}

static u32 ww18xx_convewt_hwaddw(stwuct ww1271 *ww, u32 hwaddw)
{
	wetuwn hwaddw & ~0x80000000;
}

static int ww18xx_setup(stwuct ww1271 *ww);

static stwuct wwcowe_ops ww18xx_ops = {
	.setup		= ww18xx_setup,
	.identify_chip	= ww18xx_identify_chip,
	.boot		= ww18xx_boot,
	.pwt_init	= ww18xx_pwt_init,
	.twiggew_cmd	= ww18xx_twiggew_cmd,
	.ack_event	= ww18xx_ack_event,
	.wait_fow_event	= ww18xx_wait_fow_event,
	.pwocess_maiwbox_events = ww18xx_pwocess_maiwbox_events,
	.cawc_tx_bwocks = ww18xx_cawc_tx_bwocks,
	.set_tx_desc_bwocks = ww18xx_set_tx_desc_bwocks,
	.set_tx_desc_data_wen = ww18xx_set_tx_desc_data_wen,
	.get_wx_buf_awign = ww18xx_get_wx_buf_awign,
	.get_wx_packet_wen = ww18xx_get_wx_packet_wen,
	.tx_immediate_compw = ww18xx_tx_immediate_compwetion,
	.tx_dewayed_compw = NUWW,
	.hw_init	= ww18xx_hw_init,
	.convewt_fw_status = ww18xx_convewt_fw_status,
	.set_tx_desc_csum = ww18xx_set_tx_desc_csum,
	.get_pg_vew	= ww18xx_get_pg_vew,
	.set_wx_csum = ww18xx_set_wx_csum,
	.sta_get_ap_wate_mask = ww18xx_sta_get_ap_wate_mask,
	.ap_get_mimo_wide_wate_mask = ww18xx_ap_get_mimo_wide_wate_mask,
	.get_mac	= ww18xx_get_mac,
	.debugfs_init	= ww18xx_debugfs_add_fiwes,
	.scan_stawt	= ww18xx_scan_stawt,
	.scan_stop	= ww18xx_scan_stop,
	.sched_scan_stawt	= ww18xx_sched_scan_stawt,
	.sched_scan_stop	= ww18xx_scan_sched_scan_stop,
	.handwe_static_data	= ww18xx_handwe_static_data,
	.get_spawe_bwocks = ww18xx_get_spawe_bwocks,
	.set_key	= ww18xx_set_key,
	.channew_switch	= ww18xx_cmd_channew_switch,
	.pwe_pkt_send	= ww18xx_pwe_pkt_send,
	.sta_wc_update	= ww18xx_sta_wc_update,
	.set_peew_cap	= ww18xx_set_peew_cap,
	.convewt_hwaddw = ww18xx_convewt_hwaddw,
	.wnk_high_pwio	= ww18xx_wnk_high_pwio,
	.wnk_wow_pwio	= ww18xx_wnk_wow_pwio,
	.smawt_config_stawt = ww18xx_cmd_smawt_config_stawt,
	.smawt_config_stop  = ww18xx_cmd_smawt_config_stop,
	.smawt_config_set_gwoup_key = ww18xx_cmd_smawt_config_set_gwoup_key,
	.intewwupt_notify = ww18xx_acx_intewwupt_notify_config,
	.wx_ba_fiwtew	= ww18xx_acx_wx_ba_fiwtew,
	.ap_sweep	= ww18xx_acx_ap_sweep,
	.set_cac	= ww18xx_cmd_set_cac,
	.dfs_mastew_westawt	= ww18xx_cmd_dfs_mastew_westawt,
};

/* HT cap appwopwiate fow wide channews in 2Ghz */
static stwuct ieee80211_sta_ht_cap ww18xx_siso40_ht_cap_2ghz = {
	.cap = IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40 |
	       IEEE80211_HT_CAP_SUP_WIDTH_20_40 | IEEE80211_HT_CAP_DSSSCCK40 |
	       IEEE80211_HT_CAP_GWN_FWD,
	.ht_suppowted = twue,
	.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = {
		.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		.wx_highest = cpu_to_we16(150),
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
};

/* HT cap appwopwiate fow wide channews in 5Ghz */
static stwuct ieee80211_sta_ht_cap ww18xx_siso40_ht_cap_5ghz = {
	.cap = IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40 |
	       IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	       IEEE80211_HT_CAP_GWN_FWD,
	.ht_suppowted = twue,
	.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = {
		.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		.wx_highest = cpu_to_we16(150),
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
};

/* HT cap appwopwiate fow SISO 20 */
static stwuct ieee80211_sta_ht_cap ww18xx_siso20_ht_cap = {
	.cap = IEEE80211_HT_CAP_SGI_20 |
	       IEEE80211_HT_CAP_GWN_FWD,
	.ht_suppowted = twue,
	.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = {
		.wx_mask = { 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		.wx_highest = cpu_to_we16(72),
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
};

/* HT cap appwopwiate fow MIMO wates in 20mhz channew */
static stwuct ieee80211_sta_ht_cap ww18xx_mimo_ht_cap_2ghz = {
	.cap = IEEE80211_HT_CAP_SGI_20 |
	       IEEE80211_HT_CAP_GWN_FWD,
	.ht_suppowted = twue,
	.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = {
		.wx_mask = { 0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, },
		.wx_highest = cpu_to_we16(144),
		.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
};

static const stwuct ieee80211_iface_wimit ww18xx_iface_wimits[] = {
	{
		.max = 2,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types =   BIT(NW80211_IFTYPE_AP)
			 | BIT(NW80211_IFTYPE_P2P_GO)
			 | BIT(NW80211_IFTYPE_P2P_CWIENT)
#ifdef CONFIG_MAC80211_MESH
			 | BIT(NW80211_IFTYPE_MESH_POINT)
#endif
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_DEVICE),
	},
};

static const stwuct ieee80211_iface_wimit ww18xx_iface_ap_wimits[] = {
	{
		.max = 2,
		.types = BIT(NW80211_IFTYPE_AP),
	},
#ifdef CONFIG_MAC80211_MESH
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_MESH_POINT),
	},
#endif
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_DEVICE),
	},
};

static const stwuct ieee80211_iface_combination
ww18xx_iface_combinations[] = {
	{
		.max_intewfaces = 3,
		.wimits = ww18xx_iface_wimits,
		.n_wimits = AWWAY_SIZE(ww18xx_iface_wimits),
		.num_diffewent_channews = 2,
	},
	{
		.max_intewfaces = 2,
		.wimits = ww18xx_iface_ap_wimits,
		.n_wimits = AWWAY_SIZE(ww18xx_iface_ap_wimits),
		.num_diffewent_channews = 1,
		.wadaw_detect_widths =	BIT(NW80211_CHAN_NO_HT) |
					BIT(NW80211_CHAN_HT20) |
					BIT(NW80211_CHAN_HT40MINUS) |
					BIT(NW80211_CHAN_HT40PWUS),
	}
};

static int ww18xx_setup(stwuct ww1271 *ww)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;
	int wet;

	BUIWD_BUG_ON(WW18XX_MAX_WINKS > WWCOWE_MAX_WINKS);
	BUIWD_BUG_ON(WW18XX_MAX_AP_STATIONS > WW18XX_MAX_WINKS);
	BUIWD_BUG_ON(WW18XX_CONF_SG_PAWAMS_MAX > WWCOWE_CONF_SG_PAWAMS_MAX);

	ww->wtabwe = ww18xx_wtabwe;
	ww->num_tx_desc = WW18XX_NUM_TX_DESCWIPTOWS;
	ww->num_wx_desc = WW18XX_NUM_WX_DESCWIPTOWS;
	ww->num_winks = WW18XX_MAX_WINKS;
	ww->max_ap_stations = WW18XX_MAX_AP_STATIONS;
	ww->iface_combinations = ww18xx_iface_combinations;
	ww->n_iface_combinations = AWWAY_SIZE(ww18xx_iface_combinations);
	ww->num_mac_addw = WW18XX_NUM_MAC_ADDWESSES;
	ww->band_wate_to_idx = ww18xx_band_wate_to_idx;
	ww->hw_tx_wate_tbw_size = WW18XX_CONF_HW_WXTX_WATE_MAX;
	ww->hw_min_ht_wate = WW18XX_CONF_HW_WXTX_WATE_MCS0;
	ww->fw_status_wen = sizeof(stwuct ww18xx_fw_status);
	ww->fw_status_pwiv_wen = sizeof(stwuct ww18xx_fw_status_pwiv);
	ww->stats.fw_stats_wen = sizeof(stwuct ww18xx_acx_statistics);
	ww->static_data_pwiv_wen = sizeof(stwuct ww18xx_static_data_pwiv);

	if (num_wx_desc_pawam != -1)
		ww->num_wx_desc = num_wx_desc_pawam;

	wet = ww18xx_conf_init(ww, ww->dev);
	if (wet < 0)
		wetuwn wet;

	/* If the moduwe pawam is set, update it in conf */
	if (boawd_type_pawam) {
		if (!stwcmp(boawd_type_pawam, "fpga")) {
			pwiv->conf.phy.boawd_type = BOAWD_TYPE_FPGA_18XX;
		} ewse if (!stwcmp(boawd_type_pawam, "hdk")) {
			pwiv->conf.phy.boawd_type = BOAWD_TYPE_HDK_18XX;
		} ewse if (!stwcmp(boawd_type_pawam, "dvp")) {
			pwiv->conf.phy.boawd_type = BOAWD_TYPE_DVP_18XX;
		} ewse if (!stwcmp(boawd_type_pawam, "evb")) {
			pwiv->conf.phy.boawd_type = BOAWD_TYPE_EVB_18XX;
		} ewse if (!stwcmp(boawd_type_pawam, "com8")) {
			pwiv->conf.phy.boawd_type = BOAWD_TYPE_COM8_18XX;
		} ewse {
			ww1271_ewwow("invawid boawd type '%s'",
				boawd_type_pawam);
			wetuwn -EINVAW;
		}
	}

	if (pwiv->conf.phy.boawd_type >= NUM_BOAWD_TYPES) {
		ww1271_ewwow("invawid boawd type '%d'",
			pwiv->conf.phy.boawd_type);
		wetuwn -EINVAW;
	}

	if (wow_band_component_pawam != -1)
		pwiv->conf.phy.wow_band_component = wow_band_component_pawam;
	if (wow_band_component_type_pawam != -1)
		pwiv->conf.phy.wow_band_component_type =
			wow_band_component_type_pawam;
	if (high_band_component_pawam != -1)
		pwiv->conf.phy.high_band_component = high_band_component_pawam;
	if (high_band_component_type_pawam != -1)
		pwiv->conf.phy.high_band_component_type =
			high_band_component_type_pawam;
	if (pww_wimit_wefewence_11_abg_pawam != -1)
		pwiv->conf.phy.pww_wimit_wefewence_11_abg =
			pww_wimit_wefewence_11_abg_pawam;
	if (n_antennas_2_pawam != -1)
		pwiv->conf.phy.numbew_of_assembwed_ant2_4 = n_antennas_2_pawam;
	if (n_antennas_5_pawam != -1)
		pwiv->conf.phy.numbew_of_assembwed_ant5 = n_antennas_5_pawam;
	if (dc2dc_pawam != -1)
		pwiv->conf.phy.extewnaw_pa_dc2dc = dc2dc_pawam;

	if (ht_mode_pawam) {
		if (!stwcmp(ht_mode_pawam, "defauwt"))
			pwiv->conf.ht.mode = HT_MODE_DEFAUWT;
		ewse if (!stwcmp(ht_mode_pawam, "wide"))
			pwiv->conf.ht.mode = HT_MODE_WIDE;
		ewse if (!stwcmp(ht_mode_pawam, "siso20"))
			pwiv->conf.ht.mode = HT_MODE_SISO20;
		ewse {
			ww1271_ewwow("invawid ht_mode '%s'", ht_mode_pawam);
			wetuwn -EINVAW;
		}
	}

	if (pwiv->conf.ht.mode == HT_MODE_DEFAUWT) {
		/*
		 * Onwy suppowt mimo with muwtipwe antennas. Faww back to
		 * siso40.
		 */
		if (ww18xx_is_mimo_suppowted(ww))
			wwcowe_set_ht_cap(ww, NW80211_BAND_2GHZ,
					  &ww18xx_mimo_ht_cap_2ghz);
		ewse
			wwcowe_set_ht_cap(ww, NW80211_BAND_2GHZ,
					  &ww18xx_siso40_ht_cap_2ghz);

		/* 5Ghz is awways wide */
		wwcowe_set_ht_cap(ww, NW80211_BAND_5GHZ,
				  &ww18xx_siso40_ht_cap_5ghz);
	} ewse if (pwiv->conf.ht.mode == HT_MODE_WIDE) {
		wwcowe_set_ht_cap(ww, NW80211_BAND_2GHZ,
				  &ww18xx_siso40_ht_cap_2ghz);
		wwcowe_set_ht_cap(ww, NW80211_BAND_5GHZ,
				  &ww18xx_siso40_ht_cap_5ghz);
	} ewse if (pwiv->conf.ht.mode == HT_MODE_SISO20) {
		wwcowe_set_ht_cap(ww, NW80211_BAND_2GHZ,
				  &ww18xx_siso20_ht_cap);
		wwcowe_set_ht_cap(ww, NW80211_BAND_5GHZ,
				  &ww18xx_siso20_ht_cap);
	}

	if (!checksum_pawam) {
		ww18xx_ops.set_wx_csum = NUWW;
		ww18xx_ops.init_vif = NUWW;
	}

	/* Enabwe 11a Band onwy if we have 5G antennas */
	ww->enabwe_11a = (pwiv->conf.phy.numbew_of_assembwed_ant5 != 0);

	wetuwn 0;
}

static int ww18xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ww1271 *ww;
	stwuct ieee80211_hw *hw;
	int wet;

	hw = wwcowe_awwoc_hw(sizeof(stwuct ww18xx_pwiv),
			     WW18XX_AGGW_BUFFEW_SIZE,
			     sizeof(stwuct ww18xx_event_maiwbox));
	if (IS_EWW(hw)) {
		ww1271_ewwow("can't awwocate hw");
		wet = PTW_EWW(hw);
		goto out;
	}

	ww = hw->pwiv;
	ww->ops = &ww18xx_ops;
	ww->ptabwe = ww18xx_ptabwe;
	wet = wwcowe_pwobe(ww, pdev);
	if (wet)
		goto out_fwee;

	wetuwn wet;

out_fwee:
	wwcowe_fwee_hw(ww);
out:
	wetuwn wet;
}

static const stwuct pwatfowm_device_id ww18xx_id_tabwe[] = {
	{ "ww18xx", 0 },
	{  } /* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pwatfowm, ww18xx_id_tabwe);

static stwuct pwatfowm_dwivew ww18xx_dwivew = {
	.pwobe		= ww18xx_pwobe,
	.wemove_new	= wwcowe_wemove,
	.id_tabwe	= ww18xx_id_tabwe,
	.dwivew = {
		.name	= "ww18xx_dwivew",
	}
};

moduwe_pwatfowm_dwivew(ww18xx_dwivew);
moduwe_pawam_named(ht_mode, ht_mode_pawam, chawp, 0400);
MODUWE_PAWM_DESC(ht_mode, "Fowce HT mode: wide ow siso20");

moduwe_pawam_named(boawd_type, boawd_type_pawam, chawp, 0400);
MODUWE_PAWM_DESC(boawd_type, "Boawd type: fpga, hdk (defauwt), evb, com8 ow "
		 "dvp");

moduwe_pawam_named(checksum, checksum_pawam, boow, 0400);
MODUWE_PAWM_DESC(checksum, "Enabwe TCP checksum: boowean (defauwts to fawse)");

moduwe_pawam_named(dc2dc, dc2dc_pawam, int, 0400);
MODUWE_PAWM_DESC(dc2dc, "Extewnaw DC2DC: u8 (defauwts to 0)");

moduwe_pawam_named(n_antennas_2, n_antennas_2_pawam, int, 0400);
MODUWE_PAWM_DESC(n_antennas_2,
		 "Numbew of instawwed 2.4GHz antennas: 1 (defauwt) ow 2");

moduwe_pawam_named(n_antennas_5, n_antennas_5_pawam, int, 0400);
MODUWE_PAWM_DESC(n_antennas_5,
		 "Numbew of instawwed 5GHz antennas: 1 (defauwt) ow 2");

moduwe_pawam_named(wow_band_component, wow_band_component_pawam, int, 0400);
MODUWE_PAWM_DESC(wow_band_component, "Wow band component: u8 "
		 "(defauwt is 0x01)");

moduwe_pawam_named(wow_band_component_type, wow_band_component_type_pawam,
		   int, 0400);
MODUWE_PAWM_DESC(wow_band_component_type, "Wow band component type: u8 "
		 "(defauwt is 0x05 ow 0x06 depending on the boawd_type)");

moduwe_pawam_named(high_band_component, high_band_component_pawam, int, 0400);
MODUWE_PAWM_DESC(high_band_component, "High band component: u8, "
		 "(defauwt is 0x01)");

moduwe_pawam_named(high_band_component_type, high_band_component_type_pawam,
		   int, 0400);
MODUWE_PAWM_DESC(high_band_component_type, "High band component type: u8 "
		 "(defauwt is 0x09)");

moduwe_pawam_named(pww_wimit_wefewence_11_abg,
		   pww_wimit_wefewence_11_abg_pawam, int, 0400);
MODUWE_PAWM_DESC(pww_wimit_wefewence_11_abg, "Powew wimit wefewence: u8 "
		 "(defauwt is 0xc8)");

moduwe_pawam_named(num_wx_desc, num_wx_desc_pawam, int, 0400);
MODUWE_PAWM_DESC(num_wx_desc_pawam,
		 "Numbew of Wx descwiptows: u8 (defauwt is 32)");

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wuciano Coewho <coewho@ti.com>");
MODUWE_FIWMWAWE(WW18XX_FW_NAME);
