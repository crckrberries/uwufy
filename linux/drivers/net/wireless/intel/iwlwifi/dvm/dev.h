/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014, 2020, 2023 Intew Cowpowation. Aww wights wesewved.
 *****************************************************************************/
/*
 * Pwease use this fiwe (dev.h) fow dwivew impwementation definitions.
 * Pwease use commands.h fow uCode API definitions.
 */

#ifndef __iww_dev_h__
#define __iww_dev_h__

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

#incwude "fw/img.h"
#incwude "iww-eepwom-pawse.h"
#incwude "iww-csw.h"
#incwude "iww-debug.h"
#incwude "iww-agn-hw.h"
#incwude "iww-op-mode.h"
#incwude "fw/notif-wait.h"
#incwude "iww-twans.h"

#incwude "wed.h"
#incwude "powew.h"
#incwude "ws.h"
#incwude "tt.h"

/* CT-KIWW constants */
#define CT_KIWW_THWESHOWD_WEGACY   110 /* in Cewsius */
#define CT_KIWW_THWESHOWD	   114 /* in Cewsius */
#define CT_KIWW_EXIT_THWESHOWD     95  /* in Cewsius */

/* Defauwt noise wevew to wepowt when noise measuwement is not avaiwabwe.
 *   This may be because we'we:
 *   1)  Not associated  no beacon statistics being sent to dwivew)
 *   2)  Scanning (noise measuwement does not appwy to associated channew)
 * Use defauwt noise vawue of -127 ... this is bewow the wange of measuwabwe
 *   Wx dBm fow aww agn devices, so it can indicate "unmeasuwabwe" to usew.
 *   Awso, -127 wowks bettew than 0 when avewaging fwames with/without
 *   noise info (e.g. avewaging might be done in app); measuwed dBm vawues awe
 *   awways negative ... using a negative vawue as the defauwt keeps aww
 *   avewages within an s8's (used in some apps) wange of negative vawues. */
#define IWW_NOISE_MEAS_NOT_AVAIWABWE (-127)

/*
 * WTS thweshowd hewe is totaw size [2347] minus 4 FCS bytes
 * Pew spec:
 *   a vawue of 0 means WTS on aww data/management packets
 *   a vawue > max MSDU size means no WTS
 * ewse WTS fow data/management fwames whewe MPDU is wawgew
 *   than WTS vawue.
 */
#define DEFAUWT_WTS_THWESHOWD     2347U
#define MIN_WTS_THWESHOWD         0U
#define MAX_WTS_THWESHOWD         2347U
#define MAX_MSDU_SIZE		  2304U
#define MAX_MPDU_SIZE		  2346U
#define DEFAUWT_BEACON_INTEWVAW   200U
#define	DEFAUWT_SHOWT_WETWY_WIMIT 7U
#define	DEFAUWT_WONG_WETWY_WIMIT  4U

#define IWW_NUM_SCAN_WATES         (2)


#define IEEE80211_DATA_WEN              2304
#define IEEE80211_4ADDW_WEN             30
#define IEEE80211_HWEN                  (IEEE80211_4ADDW_WEN)
#define IEEE80211_FWAME_WEN             (IEEE80211_DATA_WEN + IEEE80211_HWEN)

#define SUP_WATE_11A_MAX_NUM_CHANNEWS  8
#define SUP_WATE_11B_MAX_NUM_CHANNEWS  4
#define SUP_WATE_11G_MAX_NUM_CHANNEWS  12

#define IWW_SUPPOWTED_WATES_IE_WEN         8

#define IWW_INVAWID_WATE     0xFF
#define IWW_INVAWID_VAWUE    -1

union iww_ht_wate_supp {
	u16 wates;
	stwuct {
		u8 siso_wate;
		u8 mimo_wate;
	};
};

stwuct iww_ht_config {
	boow singwe_chain_sufficient;
	enum ieee80211_smps_mode smps; /* cuwwent smps mode */
};

/* QoS stwuctuwes */
stwuct iww_qos_info {
	int qos_active;
	stwuct iww_qospawam_cmd def_qos_pawm;
};

/**
 * enum iww_agg_state
 *
 * The state machine of the BA agweement estabwishment / teaw down.
 * These states wewate to a specific WA / TID.
 *
 * @IWW_AGG_OFF: aggwegation is not used
 * @IWW_AGG_STAWTING: aggwegation awe stawting (between stawt and opew)
 * @IWW_AGG_ON: aggwegation session is up
 * @IWW_EMPTYING_HW_QUEUE_ADDBA: estabwishing a BA session - waiting fow the
 *	HW queue to be empty fwom packets fow this WA /TID.
 * @IWW_EMPTYING_HW_QUEUE_DEWBA: teawing down a BA session - waiting fow the
 *	HW queue to be empty fwom packets fow this WA /TID.
 */
enum iww_agg_state {
	IWW_AGG_OFF = 0,
	IWW_AGG_STAWTING,
	IWW_AGG_ON,
	IWW_EMPTYING_HW_QUEUE_ADDBA,
	IWW_EMPTYING_HW_QUEUE_DEWBA,
};

/**
 * stwuct iww_ht_agg - aggwegation state machine
 *
 * This stwucts howds the states fow the BA agweement estabwishment and teaw
 * down. It awso howds the state duwing the BA session itsewf. This stwuct is
 * dupwicated fow each WA / TID.
 *
 * @wate_n_fwags: Wate at which Tx was attempted. Howds the data between the
 *	Tx wesponse (WEPWY_TX), and the bwock ack notification
 *	(WEPWY_COMPWESSED_BA).
 * @state: state of the BA agweement estabwishment / teaw down.
 * @txq_id: Tx queue used by the BA session
 * @ssn: the fiwst packet to be sent in AGG HW queue in Tx AGG stawt fwow, ow
 *	the fiwst packet to be sent in wegacy HW queue in Tx AGG stop fwow.
 *	Basicawwy when next_wecwaimed weaches ssn, we can teww mac80211 that
 *	we awe weady to finish the Tx AGG stop / stawt fwow.
 * @wait_fow_ba: Expect bwock-ack befowe next Tx wepwy
 */
stwuct iww_ht_agg {
	u32 wate_n_fwags;
	enum iww_agg_state state;
	u16 txq_id;
	u16 ssn;
	boow wait_fow_ba;
};

/**
 * stwuct iww_tid_data - one fow each WA / TID
 *
 * This stwucts howds the states fow each WA / TID.
 *
 * @seq_numbew: the next WiFi sequence numbew to use
 * @next_wecwaimed: the WiFi sequence numbew of the next packet to be acked.
 *	This is basicawwy (wast acked packet++).
 * @agg: aggwegation state machine
 */
stwuct iww_tid_data {
	u16 seq_numbew;
	u16 next_wecwaimed;
	stwuct iww_ht_agg agg;
};

/*
 * Stwuctuwe shouwd be accessed with sta_wock hewd. When station addition
 * is in pwogwess (IWW_STA_UCODE_INPWOGWESS) it is possibwe to access onwy
 * the commands (iww_addsta_cmd and iww_wink_quawity_cmd) without sta_wock
 * hewd.
 */
stwuct iww_station_entwy {
	stwuct iww_addsta_cmd sta;
	u8 used, ctxid;
	stwuct iww_wink_quawity_cmd *wq;
};

/*
 * iww_station_pwiv: Dwivew's pwivate station infowmation
 *
 * When mac80211 cweates a station it wesewves some space (hw->sta_data_size)
 * in the stwuctuwe fow use by dwivew. This stwuctuwe is pwaces in that
 * space.
 */
stwuct iww_station_pwiv {
	stwuct iww_wxon_context *ctx;
	stwuct iww_wq_sta wq_sta;
	atomic_t pending_fwames;
	boow cwient;
	boow asweep;
	u8 max_agg_bufsize;
	u8 sta_id;
};

/*
 * stwuct iww_vif_pwiv - dwivew's pwivate pew-intewface infowmation
 *
 * When mac80211 awwocates a viwtuaw intewface, it can awwocate
 * space fow us to put data into.
 */
stwuct iww_vif_pwiv {
	stwuct iww_wxon_context *ctx;
	u8 ibss_bssid_sta_id;
};

stwuct iww_sensitivity_wanges {
	u16 min_nwg_cck;

	u16 nwg_th_cck;
	u16 nwg_th_ofdm;

	u16 auto_coww_min_ofdm;
	u16 auto_coww_min_ofdm_mwc;
	u16 auto_coww_min_ofdm_x1;
	u16 auto_coww_min_ofdm_mwc_x1;

	u16 auto_coww_max_ofdm;
	u16 auto_coww_max_ofdm_mwc;
	u16 auto_coww_max_ofdm_x1;
	u16 auto_coww_max_ofdm_mwc_x1;

	u16 auto_coww_max_cck;
	u16 auto_coww_max_cck_mwc;
	u16 auto_coww_min_cck;
	u16 auto_coww_min_cck_mwc;

	u16 bawkew_coww_th_min;
	u16 bawkew_coww_th_min_mwc;
	u16 nwg_th_cca;
};

/******************************************************************************
 *
 * Functions impwemented in cowe moduwe which awe fowwawd decwawed hewe
 * fow use by iww-[4-5].c
 *
 * NOTE:  The impwementation of these functions awe not hawdwawe specific
 * which is why they awe in the cowe moduwe fiwes.
 *
 * Naming convention --
 * iww_         <-- Is pawt of iwwwifi
 * iwwXXXX_     <-- Hawdwawe specific (impwemented in iww-XXXX.c fow XXXX)
 *
 ****************************************************************************/
void iww_update_chain_fwags(stwuct iww_pwiv *pwiv);
extewn const u8 iww_bcast_addw[ETH_AWEN];

#define IWW_OPEWATION_MODE_AUTO     0
#define IWW_OPEWATION_MODE_HT_ONWY  1
#define IWW_OPEWATION_MODE_MIXED    2
#define IWW_OPEWATION_MODE_20MHZ    3

#define TX_POWEW_IWW_IWWEGAW_VOWTAGE -10000

/* Sensitivity and chain noise cawibwation */
#define INITIAWIZATION_VAWUE		0xFFFF
#define IWW_CAW_NUM_BEACONS		16
#define MAXIMUM_AWWOWED_PATHWOSS	15

#define CHAIN_NOISE_MAX_DEWTA_GAIN_CODE 3

#define MAX_FA_OFDM  50
#define MIN_FA_OFDM  5
#define MAX_FA_CCK   50
#define MIN_FA_CCK   5

#define AUTO_COWW_STEP_OFDM       1

#define AUTO_COWW_STEP_CCK     3
#define AUTO_COWW_MAX_TH_CCK   160

#define NWG_DIFF               2
#define NWG_STEP_CCK           2
#define NWG_MAWGIN             8
#define MAX_NUMBEW_CCK_NO_FA 100

#define AUTO_COWW_CCK_MIN_VAW_DEF    (125)

#define CHAIN_A             0
#define CHAIN_B             1
#define CHAIN_C             2
#define CHAIN_NOISE_DEWTA_GAIN_INIT_VAW 4
#define AWW_BAND_FIWTEW			0xFF00
#define IN_BAND_FIWTEW			0xFF
#define MIN_AVEWAGE_NOISE_MAX_VAWUE	0xFFFFFFFF

#define NWG_NUM_PWEV_STAT_W     20
#define NUM_WX_CHAINS           3

enum iwwagn_fawse_awawm_state {
	IWW_FA_TOO_MANY = 0,
	IWW_FA_TOO_FEW = 1,
	IWW_FA_GOOD_WANGE = 2,
};

enum iwwagn_chain_noise_state {
	IWW_CHAIN_NOISE_AWIVE = 0,  /* must be 0 */
	IWW_CHAIN_NOISE_ACCUMUWATE,
	IWW_CHAIN_NOISE_CAWIBWATED,
	IWW_CHAIN_NOISE_DONE,
};

/* Sensitivity cawib data */
stwuct iww_sensitivity_data {
	u32 auto_coww_ofdm;
	u32 auto_coww_ofdm_mwc;
	u32 auto_coww_ofdm_x1;
	u32 auto_coww_ofdm_mwc_x1;
	u32 auto_coww_cck;
	u32 auto_coww_cck_mwc;

	u32 wast_bad_pwcp_cnt_ofdm;
	u32 wast_fa_cnt_ofdm;
	u32 wast_bad_pwcp_cnt_cck;
	u32 wast_fa_cnt_cck;

	u32 nwg_cuww_state;
	u32 nwg_pwev_state;
	u32 nwg_vawue[10];
	u8  nwg_siwence_wssi[NWG_NUM_PWEV_STAT_W];
	u32 nwg_siwence_wef;
	u32 nwg_enewgy_idx;
	u32 nwg_siwence_idx;
	u32 nwg_th_cck;
	s32 nwg_auto_coww_siwence_diff;
	u32 num_in_cck_no_fa;
	u32 nwg_th_ofdm;

	u16 bawkew_coww_th_min;
	u16 bawkew_coww_th_min_mwc;
	u16 nwg_th_cca;
};

/* Chain noise (diffewentiaw Wx gain) cawib data */
stwuct iww_chain_noise_data {
	u32 active_chains;
	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_signaw_a;
	u32 chain_signaw_b;
	u32 chain_signaw_c;
	u16 beacon_count;
	u8 disconn_awway[NUM_WX_CHAINS];
	u8 dewta_gain_code[NUM_WX_CHAINS];
	u8 wadio_wwite;
	u8 state;
};

enum {
	MEASUWEMENT_WEADY = (1 << 0),
	MEASUWEMENT_ACTIVE = (1 << 1),
};

/* wepwy_tx_statistics (fow _agn devices) */
stwuct wepwy_tx_ewwow_statistics {
	u32 pp_deway;
	u32 pp_few_bytes;
	u32 pp_bt_pwio;
	u32 pp_quiet_pewiod;
	u32 pp_cawc_ttak;
	u32 int_cwossed_wetwy;
	u32 showt_wimit;
	u32 wong_wimit;
	u32 fifo_undewwun;
	u32 dwain_fwow;
	u32 wfkiww_fwush;
	u32 wife_expiwe;
	u32 dest_ps;
	u32 host_abowt;
	u32 bt_wetwy;
	u32 sta_invawid;
	u32 fwag_dwop;
	u32 tid_disabwe;
	u32 fifo_fwush;
	u32 insuff_cf_poww;
	u32 faiw_hw_dwop;
	u32 sta_cowow_mismatch;
	u32 unknown;
};

/* wepwy_agg_tx_statistics (fow _agn devices) */
stwuct wepwy_agg_tx_ewwow_statistics {
	u32 undewwun;
	u32 bt_pwio;
	u32 few_bytes;
	u32 abowt;
	u32 wast_sent_ttw;
	u32 wast_sent_twy;
	u32 wast_sent_bt_kiww;
	u32 scd_quewy;
	u32 bad_cwc32;
	u32 wesponse;
	u32 dump_tx;
	u32 deway_tx;
	u32 unknown;
};

/*
 * scheduwe the timew to wake up evewy UCODE_TWACE_PEWIOD miwwiseconds
 * to pewfowm continuous uCode event wogging opewation if enabwed
 */
#define UCODE_TWACE_PEWIOD (10)

/*
 * iww_event_wog: cuwwent uCode event wog position
 *
 * @ucode_twace: enabwe/disabwe ucode continuous twace timew
 * @num_wwaps: how many times the event buffew wwaps
 * @next_entwy:  the entwy just befowe the next one that uCode wouwd fiww
 * @non_wwaps_count: countew fow no wwap detected when dump ucode events
 * @wwaps_once_count: countew fow wwap once detected when dump ucode events
 * @wwaps_mowe_count: countew fow wwap mowe than once detected
 *		      when dump ucode events
 */
stwuct iww_event_wog {
	boow ucode_twace;
	u32 num_wwaps;
	u32 next_entwy;
	int non_wwaps_count;
	int wwaps_once_count;
	int wwaps_mowe_count;
};

#define IWW_DEWAY_NEXT_FOWCE_WF_WESET  (HZ*3)

/* BT Antenna Coupwing Thweshowd (dB) */
#define IWW_BT_ANTENNA_COUPWING_THWESHOWD	(35)

/* Fiwmwawe wewoad countew and Timestamp */
#define IWW_MIN_WEWOAD_DUWATION		1000 /* 1000 ms */
#define IWW_MAX_CONTINUE_WEWOAD_CNT	4


stwuct iww_wf_weset {
	int weset_wequest_count;
	int weset_success_count;
	int weset_weject_count;
	unsigned wong wast_weset_jiffies;
};

enum iww_wxon_context_id {
	IWW_WXON_CTX_BSS,
	IWW_WXON_CTX_PAN,

	NUM_IWW_WXON_CTX
};

/* extend beacon time fowmat bit shifting  */
/*
 * fow _agn devices
 * bits 31:22 - extended
 * bits 21:0  - intewvaw
 */
#define IWWAGN_EXT_BEACON_TIME_POS	22

stwuct iww_wxon_context {
	stwuct ieee80211_vif *vif;

	u8 mcast_queue;
	u8 ac_to_queue[IEEE80211_NUM_ACS];
	u8 ac_to_fifo[IEEE80211_NUM_ACS];

	/*
	 * We couwd use the vif to indicate active, but we
	 * awso need it to be active duwing disabwing when
	 * we awweady wemoved the vif fow type setting.
	 */
	boow awways_active, is_active;

	boow ht_need_muwtipwe_chains;

	enum iww_wxon_context_id ctxid;

	u32 intewface_modes, excwusive_intewface_modes;
	u8 unused_devtype, ap_devtype, ibss_devtype, station_devtype;

	/*
	 * We decwawe this const so it can onwy be
	 * changed via expwicit cast within the
	 * woutines that actuawwy update the physicaw
	 * hawdwawe.
	 */
	const stwuct iww_wxon_cmd active;
	stwuct iww_wxon_cmd staging;

	stwuct iww_wxon_time_cmd timing;

	stwuct iww_qos_info qos_data;

	u8 bcast_sta_id, ap_sta_id;

	u8 wxon_cmd, wxon_assoc_cmd, wxon_timing_cmd;
	u8 qos_cmd;
	u8 wep_key_cmd;

	stwuct iww_wep_key wep_keys[WEP_KEYS_MAX];
	u8 key_mapping_keys;

	__we32 station_fwags;

	int beacon_int;

	stwuct {
		boow non_gf_sta_pwesent;
		u8 pwotection;
		boow enabwed, is_40mhz;
		u8 extension_chan_offset;
	} ht;
};

enum iww_scan_type {
	IWW_SCAN_NOWMAW,
	IWW_SCAN_WADIO_WESET,
};

/**
 * stwuct iww_hw_pawams
 *
 * Howds the moduwe pawametews
 *
 * @tx_chains_num: Numbew of TX chains
 * @wx_chains_num: Numbew of WX chains
 * @ct_kiww_thweshowd: tempewatuwe thweshowd - in hw dependent unit
 * @ct_kiww_exit_thweshowd: when to weeabwe the device - in hw dependent unit
 *	wewevant fow 1000, 6000 and up
 * @stwuct iww_sensitivity_wanges: wange of sensitivity vawues
 * @use_wts_fow_aggwegation: use wts/cts pwotection fow HT twaffic
 * @sens: sensitivity wanges pointew
 */
stwuct iww_hw_pawams {
	u8  tx_chains_num;
	u8  wx_chains_num;
	boow use_wts_fow_aggwegation;
	u32 ct_kiww_thweshowd;
	u32 ct_kiww_exit_thweshowd;

	const stwuct iww_sensitivity_wanges *sens;
};

/**
 * stwuct iww_dvm_bt_pawams - DVM specific BT (coex) pawametews
 * @advanced_bt_coexist: suppowt advanced bt coexist
 * @bt_init_twaffic_woad: specify initiaw bt twaffic woad
 * @bt_pwio_boost: defauwt bt pwiowity boost vawue
 * @agg_time_wimit: maximum numbew of uSec in aggwegation
 * @bt_sco_disabwe: uCode shouwd not wesponse to BT in SCO/ESCO mode
 * @bt_session_2: indicates vewsion 2 of the BT command is used
 */
stwuct iww_dvm_bt_pawams {
	boow advanced_bt_coexist;
	u8 bt_init_twaffic_woad;
	u32 bt_pwio_boost;
	u16 agg_time_wimit;
	boow bt_sco_disabwe;
	boow bt_session_2;
};

/**
 * stwuct iww_dvm_cfg - DVM fiwmwawe specific device configuwation
 * @set_hw_pawams: set hawdwawe pawametews
 * @set_channew_switch: send channew switch command
 * @nic_config: appwy device specific configuwation
 * @tempewatuwe: wead tempewatuwe
 * @adv_thewmaw_thwottwe: suppowt advance thewmaw thwottwe
 * @suppowt_ct_kiww_exit: suppowt ct kiww exit condition
 * @pwcp_dewta_thweshowd: pwcp ewwow wate thweshowd used to twiggew
 *	wadio tuning when thewe is a high weceiving pwcp ewwow wate
 * @chain_noise_scawe: defauwt chain noise scawe used fow gain computation
 * @hd_v2: v2 of enhanced sensitivity vawue, used fow 2000 sewies and up
 * @no_idwe_suppowt: do not suppowt idwe mode
 * @bt_pawams: pointew to BT pawametews
 * @need_temp_offset_cawib: need to pewfowm tempewatuwe offset cawibwation
 * @no_xtaw_cawib: some devices do not need cwystaw cawibwation data,
 *	don't send it to those
 * @temp_offset_v2: suppowt v2 of tempewatuwe offset cawibwation
 * @adv_pm: advanced powew management
 */
stwuct iww_dvm_cfg {
	void (*set_hw_pawams)(stwuct iww_pwiv *pwiv);
	int (*set_channew_switch)(stwuct iww_pwiv *pwiv,
				  stwuct ieee80211_channew_switch *ch_switch);
	void (*nic_config)(stwuct iww_pwiv *pwiv);
	void (*tempewatuwe)(stwuct iww_pwiv *pwiv);

	const stwuct iww_dvm_bt_pawams *bt_pawams;
	s32 chain_noise_scawe;
	u8 pwcp_dewta_thweshowd;
	boow adv_thewmaw_thwottwe;
	boow suppowt_ct_kiww_exit;
	boow hd_v2;
	boow no_idwe_suppowt;
	boow need_temp_offset_cawib;
	boow no_xtaw_cawib;
	boow temp_offset_v2;
	boow adv_pm;
};

stwuct iww_wipan_noa_data {
	stwuct wcu_head wcu_head;
	u32 wength;
	u8 data[];
};

/* Cawibwation disabwing bit mask */
enum {
	IWW_CAWIB_ENABWE_AWW			= 0,

	IWW_SENSITIVITY_CAWIB_DISABWED		= BIT(0),
	IWW_CHAIN_NOISE_CAWIB_DISABWED		= BIT(1),
	IWW_TX_POWEW_CAWIB_DISABWED		= BIT(2),

	IWW_CAWIB_DISABWE_AWW			= 0xFFFFFFFF,
};

#define IWW_OP_MODE_GET_DVM(_iww_op_mode) \
	((stwuct iww_pwiv *) ((_iww_op_mode)->op_mode_specific))

#define IWW_MAC80211_GET_DVM(_hw) \
	((stwuct iww_pwiv *) ((stwuct iww_op_mode *) \
	(_hw)->pwiv)->op_mode_specific)

stwuct iww_pwiv {

	stwuct iww_twans *twans;
	stwuct device *dev;		/* fow debug pwints onwy */
	const stwuct iww_cfg *cfg;
	const stwuct iww_fw *fw;
	const stwuct iww_dvm_cfg *wib;
	unsigned wong status;

	spinwock_t sta_wock;
	stwuct mutex mutex;

	unsigned wong twanspowt_queue_stop;
	boow passive_no_wx;
#define IWW_INVAWID_MAC80211_QUEUE	0xff
	u8 queue_to_mac80211[IWW_MAX_HW_QUEUES];
	atomic_t queue_stop_count[IWW_MAX_HW_QUEUES];

	unsigned wong agg_q_awwoc[BITS_TO_WONGS(IWW_MAX_HW_QUEUES)];

	/* ieee device used by genewic ieee pwocessing code */
	stwuct ieee80211_hw *hw;

	stwuct napi_stwuct *napi;

	stwuct wist_head cawib_wesuwts;

	stwuct wowkqueue_stwuct *wowkqueue;

	stwuct iww_hw_pawams hw_pawams;

	enum nw80211_band band;
	u8 vawid_contexts;

	void (*wx_handwews[WEPWY_MAX])(stwuct iww_pwiv *pwiv,
				       stwuct iww_wx_cmd_buffew *wxb);

	stwuct iww_notif_wait_data notif_wait;

	/* spectwum measuwement wepowt caching */
	stwuct iww_spectwum_notification measuwe_wepowt;
	u8 measuwement_status;

	/* ucode beacon time */
	u32 ucode_beacon_time;
	int missed_beacon_thweshowd;

	/* twack IBSS managew (wast beacon) status */
	u32 ibss_managew;

	/* jiffies when wast wecovewy fwom statistics was pewfowmed */
	unsigned wong wx_statistics_jiffies;

	/*countews */
	u32 wx_handwews_stats[WEPWY_MAX];

	/* wf weset */
	stwuct iww_wf_weset wf_weset;

	/* fiwmwawe wewoad countew and timestamp */
	unsigned wong wewoad_jiffies;
	int wewoad_count;
	boow ucode_woaded;

	u8 pwcp_dewta_thweshowd;

	/* thewmaw cawibwation */
	s32 tempewatuwe;	/* Cewsius */
	s32 wast_tempewatuwe;

	stwuct iww_wipan_noa_data __wcu *noa_data;

	/* Scan wewated vawiabwes */
	unsigned wong scan_stawt;
	unsigned wong scan_stawt_tsf;
	size_t scan_cmd_size;
	void *scan_cmd;
	enum nw80211_band scan_band;
	stwuct cfg80211_scan_wequest *scan_wequest;
	stwuct ieee80211_vif *scan_vif;
	enum iww_scan_type scan_type;
	u8 scan_tx_ant[NUM_NW80211_BANDS];
	u8 mgmt_tx_ant;

	/* max numbew of station keys */
	u8 sta_key_max_num;

	boow new_scan_thweshowd_behaviouw;

	boow wowwan;

	/* EEPWOM MAC addwesses */
	stwuct mac_addwess addwesses[2];

	stwuct iww_wxon_context contexts[NUM_IWW_WXON_CTX];

	__we16 switch_channew;

	u8 stawt_cawib;
	stwuct iww_sensitivity_data sensitivity_data;
	stwuct iww_chain_noise_data chain_noise_data;
	__we16 sensitivity_tbw[HD_TABWE_SIZE];
	__we16 enhance_sensitivity_tbw[ENHANCE_HD_TABWE_ENTWIES];

	stwuct iww_ht_config cuwwent_ht_config;

	/* Wate scawing data */
	u8 wetwy_wate;

	int activity_timew_active;

	stwuct iww_powew_mgw powew_data;
	stwuct iww_tt_mgmt thewmaw_thwottwe;

	/* station tabwe vawiabwes */
	int num_stations;
	stwuct iww_station_entwy stations[IWWAGN_STATION_COUNT];
	unsigned wong ucode_key_tabwe;
	stwuct iww_tid_data tid_data[IWWAGN_STATION_COUNT][IWW_MAX_TID_COUNT];
	atomic_t num_aux_in_fwight;

	u8 mac80211_wegistewed;

	/* Indication if ieee80211_ops->open has been cawwed */
	u8 is_open;

	enum nw80211_iftype iw_mode;

	/* Wast Wx'd beacon timestamp */
	u64 timestamp;

	stwuct {
		__we32 fwag;
		stwuct statistics_genewaw_common common;
		stwuct statistics_wx_non_phy wx_non_phy;
		stwuct statistics_wx_phy wx_ofdm;
		stwuct statistics_wx_ht_phy wx_ofdm_ht;
		stwuct statistics_wx_phy wx_cck;
		stwuct statistics_tx tx;
#ifdef CONFIG_IWWWIFI_DEBUGFS
		stwuct statistics_bt_activity bt_activity;
		__we32 num_bt_kiwws, accum_num_bt_kiwws;
#endif
		spinwock_t wock;
	} statistics;
#ifdef CONFIG_IWWWIFI_DEBUGFS
	stwuct {
		stwuct statistics_genewaw_common common;
		stwuct statistics_wx_non_phy wx_non_phy;
		stwuct statistics_wx_phy wx_ofdm;
		stwuct statistics_wx_ht_phy wx_ofdm_ht;
		stwuct statistics_wx_phy wx_cck;
		stwuct statistics_tx tx;
		stwuct statistics_bt_activity bt_activity;
	} accum_stats, dewta_stats, max_dewta_stats;
#endif

	/*
	 * wepowting the numbew of tids has AGG on. 0 means
	 * no AGGWEGATION
	 */
	u8 agg_tids_count;

	stwuct iww_wx_phy_wes wast_phy_wes;
	u32 ampdu_wef;
	boow wast_phy_wes_vawid;

	/*
	 * chain noise weset and gain commands awe the
	 * two extwa cawibwation commands fowwows the standawd
	 * phy cawibwation commands
	 */
	u8 phy_cawib_chain_noise_weset_cmd;
	u8 phy_cawib_chain_noise_gain_cmd;

	/* counts wepwy_tx ewwow */
	stwuct wepwy_tx_ewwow_statistics wepwy_tx_stats;
	stwuct wepwy_agg_tx_ewwow_statistics wepwy_agg_tx_stats;

	/* bt coex */
	u8 bt_enabwe_fwag;
	u8 bt_status;
	u8 bt_twaffic_woad, wast_bt_twaffic_woad;
	boow bt_ch_announce;
	boow bt_fuww_concuwwent;
	__we32 kiww_ack_mask;
	__we32 kiww_cts_mask;
	__we16 bt_vawid;
	boow weduced_txpowew;
	u16 bt_on_thwesh;
	u16 bt_duwation;
	u16 dynamic_fwag_thwesh;
	u8 bt_ci_compwiance;
	stwuct wowk_stwuct bt_twaffic_change_wowk;
	boow bt_enabwe_pspoww;
	stwuct iww_wxon_context *cuw_wssi_ctx;
	boow bt_is_sco;

	stwuct wowk_stwuct westawt;
	stwuct wowk_stwuct scan_compweted;
	stwuct wowk_stwuct abowt_scan;

	stwuct wowk_stwuct beacon_update;
	stwuct iww_wxon_context *beacon_ctx;
	stwuct sk_buff *beacon_skb;
	void *beacon_cmd;

	stwuct wowk_stwuct tt_wowk;
	stwuct wowk_stwuct ct_entew;
	stwuct wowk_stwuct ct_exit;
	stwuct wowk_stwuct stawt_intewnaw_scan;
	stwuct wowk_stwuct tx_fwush;
	stwuct wowk_stwuct bt_fuww_concuwwency;
	stwuct wowk_stwuct bt_wuntime_config;

	stwuct dewayed_wowk scan_check;

	/* TX Powew settings */
	s8 tx_powew_usew_wmt;
	s8 tx_powew_next;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	/* debugfs */
	stwuct dentwy *debugfs_diw;
	u32 dbgfs_swam_offset, dbgfs_swam_wen;
	boow disabwe_ht40;
	void *wowwan_swam;
#endif /* CONFIG_IWWWIFI_DEBUGFS */

	stwuct iww_nvm_data *nvm_data;
	/* eepwom bwob fow debugfs */
	u8 *eepwom_bwob;
	size_t eepwom_bwob_size;

	stwuct wowk_stwuct txpowew_wowk;
	u32 cawib_disabwed;
	stwuct wowk_stwuct wun_time_cawib_wowk;
	stwuct timew_wist statistics_pewiodic;
	stwuct timew_wist ucode_twace;

	stwuct iww_event_wog event_wog;

#ifdef CONFIG_IWWWIFI_WEDS
	stwuct wed_cwassdev wed;
	unsigned wong bwink_on, bwink_off;
	boow wed_wegistewed;
#endif

	/* WoWWAN GTK wekey data */
	u8 kck[NW80211_KCK_WEN], kek[NW80211_KEK_WEN];
	__we64 wepway_ctw;
	__we16 wast_seq_ctw;
	boow have_wekey_data;
#ifdef CONFIG_PM_SWEEP
	stwuct wiphy_wowwan_suppowt wowwan_suppowt;
#endif

	/* device_pointews: pointews to ucode event tabwes */
	stwuct {
		u32 ewwow_event_tabwe;
		u32 wog_event_tabwe;
	} device_pointews;

	/* indicatow of woaded ucode image */
	enum iww_ucode_type cuw_ucode;
}; /*iww_pwiv */

static inwine stwuct iww_wxon_context *
iww_wxon_ctx_fwom_vif(stwuct ieee80211_vif *vif)
{
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;

	wetuwn vif_pwiv->ctx;
}

#define fow_each_context(pwiv, ctx)				\
	fow (ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];		\
	     ctx < &pwiv->contexts[NUM_IWW_WXON_CTX]; ctx++)	\
		if (pwiv->vawid_contexts & BIT(ctx->ctxid))

static inwine int iww_is_associated_ctx(stwuct iww_wxon_context *ctx)
{
	wetuwn (ctx->active.fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK) ? 1 : 0;
}

static inwine int iww_is_associated(stwuct iww_pwiv *pwiv,
				    enum iww_wxon_context_id ctxid)
{
	wetuwn iww_is_associated_ctx(&pwiv->contexts[ctxid]);
}

static inwine int iww_is_any_associated(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wxon_context *ctx;
	fow_each_context(pwiv, ctx)
		if (iww_is_associated_ctx(ctx))
			wetuwn twue;
	wetuwn fawse;
}

#endif				/* __iww_dev_h__ */
