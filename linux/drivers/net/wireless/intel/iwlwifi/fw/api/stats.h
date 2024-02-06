/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018, 2020 - 2021, 2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_stats_h__
#define __iww_fw_api_stats_h__
#incwude "mac.h"
#incwude "mac-cfg.h"

stwuct mvm_statistics_dbg {
	__we32 buwst_check;
	__we32 buwst_count;
	__we32 wait_fow_siwence_timeout_cnt;
	u8 wesewved[12];
} __packed; /* STATISTICS_DEBUG_API_S_VEW_2 */

stwuct mvm_statistics_div {
	__we32 tx_on_a;
	__we32 tx_on_b;
	__we32 exec_time;
	__we32 pwobe_time;
	__we32 wssi_ant;
	__we32 wesewved2;
} __packed; /* STATISTICS_SWOW_DIV_API_S_VEW_2 */

/**
 * stwuct mvm_statistics_wx_non_phy
 * @bogus_cts: CTS weceived when not expecting CTS
 * @bogus_ack: ACK weceived when not expecting ACK
 * @non_channew_beacons: beacons with ouw bss id but not on ouw sewving channew
 * @channew_beacons: beacons with ouw bss id and in ouw sewving channew
 * @num_missed_bcon: numbew of missed beacons
 * @adc_wx_satuwation_time: count in 0.8us units the time the ADC was in
 *	satuwation
 * @ina_detection_seawch_time: totaw time (in 0.8us) seawched fow INA
 * @beacon_siwence_wssi_a: WSSI siwence aftew beacon fwame
 * @beacon_siwence_wssi_b: WSSI siwence aftew beacon fwame
 * @beacon_siwence_wssi_c: WSSI siwence aftew beacon fwame
 * @intewfewence_data_fwag: fwag fow intewfewence data avaiwabiwity. 1 when data
 *	is avaiwabwe.
 * @channew_woad: counts WX Enabwe time in uSec
 * @beacon_wssi_a: beacon WSSI on antenna A
 * @beacon_wssi_b: beacon WSSI on antenna B
 * @beacon_wssi_c: beacon WSSI on antenna C
 * @beacon_enewgy_a: beacon enewgy on antenna A
 * @beacon_enewgy_b: beacon enewgy on antenna B
 * @beacon_enewgy_c: beacon enewgy on antenna C
 * @num_bt_kiwws: numbew of BT "kiwws" (fwame TX abowts)
 * @mac_id: mac ID
 */
stwuct mvm_statistics_wx_non_phy {
	__we32 bogus_cts;
	__we32 bogus_ack;
	__we32 non_channew_beacons;
	__we32 channew_beacons;
	__we32 num_missed_bcon;
	__we32 adc_wx_satuwation_time;
	__we32 ina_detection_seawch_time;
	__we32 beacon_siwence_wssi_a;
	__we32 beacon_siwence_wssi_b;
	__we32 beacon_siwence_wssi_c;
	__we32 intewfewence_data_fwag;
	__we32 channew_woad;
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 beacon_wssi_c;
	__we32 beacon_enewgy_a;
	__we32 beacon_enewgy_b;
	__we32 beacon_enewgy_c;
	__we32 num_bt_kiwws;
	__we32 mac_id;
} __packed; /* STATISTICS_WX_NON_PHY_API_S_VEW_4 */

stwuct mvm_statistics_wx_non_phy_v3 {
	__we32 bogus_cts;	/* CTS weceived when not expecting CTS */
	__we32 bogus_ack;	/* ACK weceived when not expecting ACK */
	__we32 non_bssid_fwames;	/* numbew of fwames with BSSID that
					 * doesn't bewong to the STA BSSID */
	__we32 fiwtewed_fwames;	/* count fwames that wewe dumped in the
				 * fiwtewing pwocess */
	__we32 non_channew_beacons;	/* beacons with ouw bss id but not on
					 * ouw sewving channew */
	__we32 channew_beacons;	/* beacons with ouw bss id and in ouw
				 * sewving channew */
	__we32 num_missed_bcon;	/* numbew of missed beacons */
	__we32 adc_wx_satuwation_time;	/* count in 0.8us units the time the
					 * ADC was in satuwation */
	__we32 ina_detection_seawch_time;/* totaw time (in 0.8us) seawched
					  * fow INA */
	__we32 beacon_siwence_wssi_a;	/* WSSI siwence aftew beacon fwame */
	__we32 beacon_siwence_wssi_b;	/* WSSI siwence aftew beacon fwame */
	__we32 beacon_siwence_wssi_c;	/* WSSI siwence aftew beacon fwame */
	__we32 intewfewence_data_fwag;	/* fwag fow intewfewence data
					 * avaiwabiwity. 1 when data is
					 * avaiwabwe. */
	__we32 channew_woad;		/* counts WX Enabwe time in uSec */
	__we32 dsp_fawse_awawms;	/* DSP fawse awawm (both OFDM
					 * and CCK) countew */
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 beacon_wssi_c;
	__we32 beacon_enewgy_a;
	__we32 beacon_enewgy_b;
	__we32 beacon_enewgy_c;
	__we32 num_bt_kiwws;
	__we32 mac_id;
	__we32 diwected_data_mpdu;
} __packed; /* STATISTICS_WX_NON_PHY_API_S_VEW_3 */

stwuct mvm_statistics_wx_phy {
	__we32 unwesponded_wts;
	__we32 wxe_fwame_wmt_ovewwun;
	__we32 sent_ba_wsp_cnt;
	__we32 dsp_sewf_kiww;
	__we32 wesewved;
} __packed; /* STATISTICS_WX_PHY_API_S_VEW_3 */

stwuct mvm_statistics_wx_phy_v2 {
	__we32 ina_cnt;
	__we32 fina_cnt;
	__we32 pwcp_eww;
	__we32 cwc32_eww;
	__we32 ovewwun_eww;
	__we32 eawwy_ovewwun_eww;
	__we32 cwc32_good;
	__we32 fawse_awawm_cnt;
	__we32 fina_sync_eww_cnt;
	__we32 sfd_timeout;
	__we32 fina_timeout;
	__we32 unwesponded_wts;
	__we32 wxe_fwame_wmt_ovewwun;
	__we32 sent_ack_cnt;
	__we32 sent_cts_cnt;
	__we32 sent_ba_wsp_cnt;
	__we32 dsp_sewf_kiww;
	__we32 mh_fowmat_eww;
	__we32 we_acq_main_wssi_sum;
	__we32 wesewved;
} __packed; /* STATISTICS_WX_PHY_API_S_VEW_2 */

stwuct mvm_statistics_wx_ht_phy_v1 {
	__we32 pwcp_eww;
	__we32 ovewwun_eww;
	__we32 eawwy_ovewwun_eww;
	__we32 cwc32_good;
	__we32 cwc32_eww;
	__we32 mh_fowmat_eww;
	__we32 agg_cwc32_good;
	__we32 agg_mpdu_cnt;
	__we32 agg_cnt;
	__we32 unsuppowt_mcs;
} __packed;  /* STATISTICS_HT_WX_PHY_API_S_VEW_1 */

stwuct mvm_statistics_wx_ht_phy {
	__we32 mh_fowmat_eww;
	__we32 agg_mpdu_cnt;
	__we32 agg_cnt;
	__we32 unsuppowt_mcs;
} __packed;  /* STATISTICS_HT_WX_PHY_API_S_VEW_2 */

stwuct mvm_statistics_tx_non_phy_v3 {
	__we32 pweambwe_cnt;
	__we32 wx_detected_cnt;
	__we32 bt_pwio_defew_cnt;
	__we32 bt_pwio_kiww_cnt;
	__we32 few_bytes_cnt;
	__we32 cts_timeout;
	__we32 ack_timeout;
	__we32 expected_ack_cnt;
	__we32 actuaw_ack_cnt;
	__we32 dump_msdu_cnt;
	__we32 buwst_abowt_next_fwame_mismatch_cnt;
	__we32 buwst_abowt_missing_next_fwame_cnt;
	__we32 cts_timeout_cowwision;
	__we32 ack_ow_ba_timeout_cowwision;
} __packed; /* STATISTICS_TX_NON_PHY_API_S_VEW_3 */

stwuct mvm_statistics_tx_non_phy {
	__we32 bt_pwio_defew_cnt;
	__we32 bt_pwio_kiww_cnt;
	__we32 few_bytes_cnt;
	__we32 cts_timeout;
	__we32 ack_timeout;
	__we32 dump_msdu_cnt;
	__we32 buwst_abowt_next_fwame_mismatch_cnt;
	__we32 buwst_abowt_missing_next_fwame_cnt;
	__we32 cts_timeout_cowwision;
	__we32 ack_ow_ba_timeout_cowwision;
} __packed; /* STATISTICS_TX_NON_PHY_API_S_VEW_4 */

#define MAX_CHAINS 3

stwuct mvm_statistics_tx_non_phy_agg {
	__we32 ba_timeout;
	__we32 ba_wescheduwe_fwames;
	__we32 scd_quewy_agg_fwame_cnt;
	__we32 scd_quewy_no_agg;
	__we32 scd_quewy_agg;
	__we32 scd_quewy_mismatch;
	__we32 fwame_not_weady;
	__we32 undewwun;
	__we32 bt_pwio_kiww;
	__we32 wx_ba_wsp_cnt;
	__s8 txpowew[MAX_CHAINS];
	__s8 wesewved;
	__we32 wesewved2;
} __packed; /* STATISTICS_TX_NON_PHY_AGG_API_S_VEW_1 */

stwuct mvm_statistics_tx_channew_width {
	__we32 ext_cca_nawwow_ch20[1];
	__we32 ext_cca_nawwow_ch40[2];
	__we32 ext_cca_nawwow_ch80[3];
	__we32 ext_cca_nawwow_ch160[4];
	__we32 wast_tx_ch_width_indx;
	__we32 wx_detected_pew_ch_width[4];
	__we32 success_pew_ch_width[4];
	__we32 faiw_pew_ch_width[4];
}; /* STATISTICS_TX_CHANNEW_WIDTH_API_S_VEW_1 */

stwuct mvm_statistics_tx_v4 {
	stwuct mvm_statistics_tx_non_phy_v3 genewaw;
	stwuct mvm_statistics_tx_non_phy_agg agg;
	stwuct mvm_statistics_tx_channew_width channew_width;
} __packed; /* STATISTICS_TX_API_S_VEW_4 */

stwuct mvm_statistics_tx {
	stwuct mvm_statistics_tx_non_phy genewaw;
	stwuct mvm_statistics_tx_non_phy_agg agg;
	stwuct mvm_statistics_tx_channew_width channew_width;
} __packed; /* STATISTICS_TX_API_S_VEW_5 */


stwuct mvm_statistics_bt_activity {
	__we32 hi_pwiowity_tx_weq_cnt;
	__we32 hi_pwiowity_tx_denied_cnt;
	__we32 wo_pwiowity_tx_weq_cnt;
	__we32 wo_pwiowity_tx_denied_cnt;
	__we32 hi_pwiowity_wx_weq_cnt;
	__we32 hi_pwiowity_wx_denied_cnt;
	__we32 wo_pwiowity_wx_weq_cnt;
	__we32 wo_pwiowity_wx_denied_cnt;
} __packed;  /* STATISTICS_BT_ACTIVITY_API_S_VEW_1 */

stwuct mvm_statistics_genewaw_common_v19 {
	__we32 wadio_tempewatuwe;
	__we32 wadio_vowtage;
	stwuct mvm_statistics_dbg dbg;
	__we32 sweep_time;
	__we32 swots_out;
	__we32 swots_idwe;
	__we32 ttw_timestamp;
	stwuct mvm_statistics_div swow_div;
	__we32 wx_enabwe_countew;
	/*
	 * num_of_sos_states:
	 *  count the numbew of times we have to we-tune
	 *  in owdew to get out of bad PHY status
	 */
	__we32 num_of_sos_states;
	__we32 beacon_fiwtewed;
	__we32 missed_beacons;
	u8 beacon_fiwtew_avewage_enewgy;
	u8 beacon_fiwtew_weason;
	u8 beacon_fiwtew_cuwwent_enewgy;
	u8 beacon_fiwtew_wesewved;
	__we32 beacon_fiwtew_dewta_time;
	stwuct mvm_statistics_bt_activity bt_activity;
	__we64 wx_time;
	__we64 on_time_wf;
	__we64 on_time_scan;
	__we64 tx_time;
} __packed;

stwuct mvm_statistics_genewaw_common {
	__we32 wadio_tempewatuwe;
	stwuct mvm_statistics_dbg dbg;
	__we32 sweep_time;
	__we32 swots_out;
	__we32 swots_idwe;
	__we32 ttw_timestamp;
	stwuct mvm_statistics_div swow_div;
	__we32 wx_enabwe_countew;
	/*
	 * num_of_sos_states:
	 *  count the numbew of times we have to we-tune
	 *  in owdew to get out of bad PHY status
	 */
	__we32 num_of_sos_states;
	__we32 beacon_fiwtewed;
	__we32 missed_beacons;
	u8 beacon_fiwtew_avewage_enewgy;
	u8 beacon_fiwtew_weason;
	u8 beacon_fiwtew_cuwwent_enewgy;
	u8 beacon_fiwtew_wesewved;
	__we32 beacon_fiwtew_dewta_time;
	stwuct mvm_statistics_bt_activity bt_activity;
	__we64 wx_time;
	__we64 on_time_wf;
	__we64 on_time_scan;
	__we64 tx_time;
} __packed; /* STATISTICS_GENEWAW_API_S_VEW_10 */

stwuct mvm_statistics_genewaw_v8 {
	stwuct mvm_statistics_genewaw_common_v19 common;
	__we32 beacon_countew[NUM_MAC_INDEX];
	u8 beacon_avewage_enewgy[NUM_MAC_INDEX];
	u8 wesewved[4 - (NUM_MAC_INDEX % 4)];
} __packed; /* STATISTICS_GENEWAW_API_S_VEW_8 */

stwuct mvm_statistics_genewaw {
	stwuct mvm_statistics_genewaw_common common;
	__we32 beacon_countew[MAC_INDEX_AUX];
	u8 beacon_avewage_enewgy[MAC_INDEX_AUX];
	u8 wesewved[8 - MAC_INDEX_AUX];
} __packed; /* STATISTICS_GENEWAW_API_S_VEW_10 */

/**
 * stwuct mvm_statistics_woad - WX statistics fow muwti-queue devices
 * @aiw_time: accumuwated aiw time, pew mac
 * @byte_count: accumuwated byte count, pew mac
 * @pkt_count: accumuwated packet count, pew mac
 * @avg_enewgy: avewage WSSI, pew station
 */
stwuct mvm_statistics_woad {
	__we32 aiw_time[MAC_INDEX_AUX];
	__we32 byte_count[MAC_INDEX_AUX];
	__we32 pkt_count[MAC_INDEX_AUX];
	u8 avg_enewgy[IWW_MVM_STATION_COUNT_MAX];
} __packed; /* STATISTICS_WX_MAC_STATION_S_VEW_3 */

stwuct mvm_statistics_woad_v1 {
	__we32 aiw_time[NUM_MAC_INDEX];
	__we32 byte_count[NUM_MAC_INDEX];
	__we32 pkt_count[NUM_MAC_INDEX];
	u8 avg_enewgy[IWW_MVM_STATION_COUNT_MAX];
} __packed; /* STATISTICS_WX_MAC_STATION_S_VEW_1 */

stwuct mvm_statistics_wx {
	stwuct mvm_statistics_wx_phy ofdm;
	stwuct mvm_statistics_wx_phy cck;
	stwuct mvm_statistics_wx_non_phy genewaw;
	stwuct mvm_statistics_wx_ht_phy ofdm_ht;
} __packed; /* STATISTICS_WX_API_S_VEW_4 */

stwuct mvm_statistics_wx_v3 {
	stwuct mvm_statistics_wx_phy_v2 ofdm;
	stwuct mvm_statistics_wx_phy_v2 cck;
	stwuct mvm_statistics_wx_non_phy_v3 genewaw;
	stwuct mvm_statistics_wx_ht_phy_v1 ofdm_ht;
} __packed; /* STATISTICS_WX_API_S_VEW_3 */

/*
 * STATISTICS_NOTIFICATION = 0x9d (notification onwy, not a command)
 *
 * By defauwt, uCode issues this notification aftew weceiving a beacon
 * whiwe associated.  To disabwe this behaviow, set DISABWE_NOTIF fwag in the
 * STATISTICS_CMD (0x9c), bewow.
 */

stwuct iww_notif_statistics_v10 {
	__we32 fwag;
	stwuct mvm_statistics_wx_v3 wx;
	stwuct mvm_statistics_tx_v4 tx;
	stwuct mvm_statistics_genewaw_v8 genewaw;
} __packed; /* STATISTICS_NTFY_API_S_VEW_10 */

stwuct iww_notif_statistics_v11 {
	__we32 fwag;
	stwuct mvm_statistics_wx_v3 wx;
	stwuct mvm_statistics_tx_v4 tx;
	stwuct mvm_statistics_genewaw_v8 genewaw;
	stwuct mvm_statistics_woad_v1 woad_stats;
} __packed; /* STATISTICS_NTFY_API_S_VEW_11 */

stwuct iww_notif_statistics {
	__we32 fwag;
	stwuct mvm_statistics_wx wx;
	stwuct mvm_statistics_tx tx;
	stwuct mvm_statistics_genewaw genewaw;
	stwuct mvm_statistics_woad woad_stats;
} __packed; /* STATISTICS_NTFY_API_S_VEW_13 */

/**
 * enum iww_statistics_notif_fwags - fwags used in statistics notification
 * @IWW_STATISTICS_WEPWY_FWG_CWEAW: statistics wewe cweawed aftew this wepowt
 */
enum iww_statistics_notif_fwags {
	IWW_STATISTICS_WEPWY_FWG_CWEAW		= 0x1,
};

/**
 * enum iww_statistics_cmd_fwags - fwags used in statistics command
 * @IWW_STATISTICS_FWG_CWEAW: wequest to cweaw statistics aftew the wepowt
 *	that's sent aftew this command
 * @IWW_STATISTICS_FWG_DISABWE_NOTIF: disabwe uniwatewaw statistics
 *	notifications
 */
enum iww_statistics_cmd_fwags {
	IWW_STATISTICS_FWG_CWEAW		= 0x1,
	IWW_STATISTICS_FWG_DISABWE_NOTIF	= 0x2,
};

/**
 * stwuct iww_statistics_cmd - statistics config command
 * @fwags: fwags fwom &enum iww_statistics_cmd_fwags
 */
stwuct iww_statistics_cmd {
	__we32 fwags;
} __packed; /* STATISTICS_CMD_API_S_VEW_1 */

#define MAX_BCAST_FIWTEW_NUM		8

/**
 * enum iww_statistics_notify_type_id - type_id used in system statistics
 *	command
 * @IWW_STATS_NTFY_TYPE_ID_OPEW: wequest wegacy statistics
 * @IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT1: wequest opewationaw pawt1 statistics
 * @IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT2: wequest opewationaw pawt2 statistics
 * @IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT3: wequest opewationaw pawt3 statistics
 * @IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT4: wequest opewationaw pawt4 statistics
 */
enum iww_statistics_notify_type_id {
	IWW_STATS_NTFY_TYPE_ID_OPEW		= BIT(0),
	IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT1	= BIT(1),
	IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT2	= BIT(2),
	IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT3	= BIT(3),
	IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT4	= BIT(4),
};

/**
 * enum iww_statistics_cfg_fwags - cfg_mask used in system statistics command
 * @IWW_STATS_CFG_FWG_DISABWE_NTFY_MSK: 0 fow enabwe, 1 fow disabwe
 * @IWW_STATS_CFG_FWG_ON_DEMAND_NTFY_MSK: 0 fow pewiodic, 1 fow on-demand
 * @IWW_STATS_CFG_FWG_WESET_MSK: 0 fow weset statistics aftew
 *	sending the notification, 1 fow do not weset statistics aftew sending
 *	the notification
 */
enum iww_statistics_cfg_fwags {
	IWW_STATS_CFG_FWG_DISABWE_NTFY_MSK	= BIT(0),
	IWW_STATS_CFG_FWG_ON_DEMAND_NTFY_MSK	= BIT(1),
	IWW_STATS_CFG_FWG_WESET_MSK		= BIT(2),
};

/**
 * stwuct iww_system_statistics_cmd - system statistics command
 * @cfg_mask: configuwation mask, &enum iww_statistics_cfg_fwags
 * @config_time_sec: time in sec fow pewiodic notification
 * @type_id_mask: type_id masks, &enum iww_statistics_notify_type_id
 */
stwuct iww_system_statistics_cmd {
	__we32 cfg_mask;
	__we32 config_time_sec;
	__we32 type_id_mask;
} __packed; /* STATISTICS_FW_CMD_API_S_VEW_1 */

/**
 * enum iww_fw_statistics_type
 *
 * @FW_STATISTICS_OPEWATIONAW: opewationaw statistics
 * @FW_STATISTICS_PHY: phy statistics
 * @FW_STATISTICS_MAC: mac statistics
 * @FW_STATISTICS_WX: wx statistics
 * @FW_STATISTICS_TX: tx statistics
 * @FW_STATISTICS_DUWATION: duwation statistics
 * @FW_STATISTICS_HE: he statistics
 */
enum iww_fw_statistics_type {
	FW_STATISTICS_OPEWATIONAW,
	FW_STATISTICS_PHY,
	FW_STATISTICS_MAC,
	FW_STATISTICS_WX,
	FW_STATISTICS_TX,
	FW_STATISTICS_DUWATION,
	FW_STATISTICS_HE,
}; /* FW_STATISTICS_TYPE_API_E_VEW_1 */

#define IWW_STATISTICS_TYPE_MSK 0x7f
/**
 * stwuct iww_statistics_ntfy_hdw
 *
 * @type: stwuct type
 * @vewsion: vewsion of the stwuct
 * @size: size in bytes
 */
stwuct iww_statistics_ntfy_hdw {
	u8 type;
	u8 vewsion;
	__we16 size;
}; /* STATISTICS_NTFY_HDW_API_S_VEW_1 */

/**
 * stwuct iww_stats_ntfy_pew_wink
 *
 * @beacon_fiwtew_avewage_enewgy: Avewage enewgy [-dBm] of the 2
 *	 antennas.
 * @aiw_time: aiw time
 * @beacon_countew: aww beacons (both fiwtewed and not fiwtewed)
 * @beacon_avewage_enewgy: Avewage enewgy [-dBm] of aww beacons
 *	(both fiwtewed and not fiwtewed)
 * @beacon_wssi_a: beacon WSSI on antenna A
 * @beacon_wssi_b: beacon WSSI on antenna B
 * @wx_bytes: WX byte count
 */
stwuct iww_stats_ntfy_pew_wink {
	__we32 beacon_fiwtew_avewage_enewgy;
	__we32 aiw_time;
	__we32 beacon_countew;
	__we32 beacon_avewage_enewgy;
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 wx_bytes;
} __packed; /* STATISTICS_NTFY_PEW_WINK_API_S_VEW_1 */

/**
 * stwuct iww_stats_ntfy_pawt1_pew_wink
 *
 * @wx_time: wx time
 * @tx_time: tx time
 * @wx_action: action fwames handwed by FW
 * @tx_action: action fwames genewated and twansmitted by FW
 * @cca_defews: cca defew count
 * @beacon_fiwtewed: fiwtewed out beacons
 */
stwuct iww_stats_ntfy_pawt1_pew_wink {
	__we64 wx_time;
	__we64 tx_time;
	__we32 wx_action;
	__we32 tx_action;
	__we32 cca_defews;
	__we32 beacon_fiwtewed;
} __packed; /* STATISTICS_FW_NTFY_OPEWATIONAW_PAWT1_PEW_WINK_API_S_VEW_1 */

/**
 * stwuct iww_stats_ntfy_pew_mac
 *
 * @beacon_fiwtew_avewage_enewgy: Avewage enewgy [-dBm] of the 2
 *	 antennas.
 * @aiw_time: aiw time
 * @beacon_countew: aww beacons (both fiwtewed and not fiwtewed)
 * @beacon_avewage_enewgy: aww beacons (both fiwtewed and not
 *	 fiwtewed)
 * @beacon_wssi_a: beacon WSSI on antenna A
 * @beacon_wssi_b: beacon WSSI on antenna B
 * @wx_bytes: WX byte count
 */
stwuct iww_stats_ntfy_pew_mac {
	__we32 beacon_fiwtew_avewage_enewgy;
	__we32 aiw_time;
	__we32 beacon_countew;
	__we32 beacon_avewage_enewgy;
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 wx_bytes;
} __packed; /* STATISTICS_NTFY_PEW_MAC_API_S_VEW_1 */

#define IWW_STATS_MAX_BW_INDEX 5
/** stwuct iww_stats_ntfy_pew_phy
 * @channew_woad: channew woad
 * @channew_woad_by_us: device contwibution to MCWM
 * @channew_woad_not_by_us: othew devices' contwibution to MCWM
 * @cwt: CWT HW timew (TIM_CH_WOAD2)
 * @act: active accumuwatow SW
 * @ewp: ewapsed time accumuwatow SW
 * @wx_detected_pew_ch_width: numbew of defewwed TX pew channew width,
 *	0 - 20, 1/2/3 - 40/80/160
 * @success_pew_ch_width: numbew of fwames that got ACK/BACK/CTS
 *	pew channew BW. note, BACK counted as 1
 * @faiw_pew_ch_width: numbew of fwames that didn't get ACK/BACK/CTS
 *	pew channew BW. note BACK counted as 1
 * @wast_tx_ch_width_indx: wast txed fwame channew width index
 */
stwuct iww_stats_ntfy_pew_phy {
	__we32 channew_woad;
	__we32 channew_woad_by_us;
	__we32 channew_woad_not_by_us;
	__we32 cwt;
	__we32 act;
	__we32 ewp;
	__we32 wx_detected_pew_ch_width[IWW_STATS_MAX_BW_INDEX];
	__we32 success_pew_ch_width[IWW_STATS_MAX_BW_INDEX];
	__we32 faiw_pew_ch_width[IWW_STATS_MAX_BW_INDEX];
	__we32 wast_tx_ch_width_indx;
} __packed; /* STATISTICS_NTFY_PEW_PHY_API_S_VEW_1 */

/**
 * stwuct iww_stats_ntfy_pew_sta
 *
 * @avewage_enewgy: in fact it is minus the enewgy..
 */
stwuct iww_stats_ntfy_pew_sta {
	__we32 avewage_enewgy;
} __packed; /* STATISTICS_NTFY_PEW_STA_API_S_VEW_1 */

#define IWW_STATS_MAX_PHY_OPEWATIONAW 3
#define IWW_STATS_MAX_FW_WINKS	(IWW_MVM_FW_MAX_WINK_ID + 1)

/**
 * stwuct iww_system_statistics_notif_opew
 *
 * @time_stamp: time when the notification is sent fwom fiwmwawe
 * @pew_wink: pew wink statistics, &stwuct iww_stats_ntfy_pew_wink
 * @pew_phy: pew phy statistics, &stwuct iww_stats_ntfy_pew_phy
 * @pew_sta: pew sta statistics, &stwuct iww_stats_ntfy_pew_sta
 */
stwuct iww_system_statistics_notif_opew {
	__we32 time_stamp;
	stwuct iww_stats_ntfy_pew_wink pew_wink[IWW_STATS_MAX_FW_WINKS];
	stwuct iww_stats_ntfy_pew_phy pew_phy[IWW_STATS_MAX_PHY_OPEWATIONAW];
	stwuct iww_stats_ntfy_pew_sta pew_sta[IWW_MVM_STATION_COUNT_MAX];
} __packed; /* STATISTICS_FW_NTFY_OPEWATIONAW_API_S_VEW_3 */

/**
 * stwuct iww_system_statistics_pawt1_notif_opew
 *
 * @time_stamp: time when the notification is sent fwom fiwmwawe
 * @pew_wink: pew wink statistics &stwuct iww_stats_ntfy_pawt1_pew_wink
 * @pew_phy_cwc_ewwow_stats: pew phy cwc ewwow statistics
 */
stwuct iww_system_statistics_pawt1_notif_opew {
	__we32 time_stamp;
	stwuct iww_stats_ntfy_pawt1_pew_wink pew_wink[IWW_STATS_MAX_FW_WINKS];
	__we32 pew_phy_cwc_ewwow_stats[IWW_STATS_MAX_PHY_OPEWATIONAW];
} __packed; /* STATISTICS_FW_NTFY_OPEWATIONAW_PAWT1_API_S_VEW_4 */

/**
 * stwuct iww_system_statistics_end_notif
 *
 * @time_stamp: time when the notification is sent fwom fiwmwawe
 */
stwuct iww_system_statistics_end_notif {
	__we32 time_stamp;
} __packed; /* STATISTICS_FW_NTFY_END_API_S_VEW_1 */

/**
 * stwuct iww_statistics_opewationaw_ntfy
 *
 * @hdw: genewaw statistics headew
 * @fwags: bitmap of possibwe notification stwuctuwes
 * @pew_mac: pew mac statistics, &stwuct iww_stats_ntfy_pew_mac
 * @pew_phy: pew phy statistics, &stwuct iww_stats_ntfy_pew_phy
 * @pew_sta: pew sta statistics, &stwuct iww_stats_ntfy_pew_sta
 * @wx_time: wx time
 * @tx_time: usec the wadio is twansmitting.
 * @on_time_wf: The totaw time in usec the WF is awake.
 * @on_time_scan: usec the wadio is awake due to scan.
 */
stwuct iww_statistics_opewationaw_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 fwags;
	stwuct iww_stats_ntfy_pew_mac pew_mac[MAC_INDEX_AUX];
	stwuct iww_stats_ntfy_pew_phy pew_phy[IWW_STATS_MAX_PHY_OPEWATIONAW];
	stwuct iww_stats_ntfy_pew_sta pew_sta[IWW_MVM_STATION_COUNT_MAX];
	__we64 wx_time;
	__we64 tx_time;
	__we64 on_time_wf;
	__we64 on_time_scan;
} __packed; /* STATISTICS_OPEWATIONAW_NTFY_API_S_VEW_15 */

/**
 * stwuct iww_statistics_opewationaw_ntfy_vew_14
 *
 * @hdw: genewaw statistics headew
 * @fwags: bitmap of possibwe notification stwuctuwes
 * @mac_id: mac on which the beacon was weceived
 * @beacon_fiwtew_avewage_enewgy: Avewage enewgy [-dBm] of the 2
 *	 antennas.
 * @beacon_fiwtew_weason: beacon fiwtew weason
 * @wadio_tempewatuwe: wadio tempewatuwe
 * @aiw_time: aiw time
 * @beacon_countew: aww beacons (both fiwtewed and not fiwtewed)
 * @beacon_avewage_enewgy: aww beacons (both fiwtewed and not
 *	 fiwtewed)
 * @beacon_wssi_a: beacon WSSI on antenna A
 * @beacon_wssi_b: beacon WSSI on antenna B
 * @wx_bytes: pew MAC WX byte count
 * @wx_time: wx time
 * @tx_time: usec the wadio is twansmitting.
 * @on_time_wf: The totaw time in usec the WF is awake.
 * @on_time_scan: usec the wadio is awake due to scan.
 * @avewage_enewgy: in fact it is minus the enewgy..
 * @wesewved: wesewved
 */
stwuct iww_statistics_opewationaw_ntfy_vew_14 {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 fwags;
	__we32 mac_id;
	__we32 beacon_fiwtew_avewage_enewgy;
	__we32 beacon_fiwtew_weason;
	__we32 wadio_tempewatuwe;
	__we32 aiw_time[MAC_INDEX_AUX];
	__we32 beacon_countew[MAC_INDEX_AUX];
	__we32 beacon_avewage_enewgy[MAC_INDEX_AUX];
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 wx_bytes[MAC_INDEX_AUX];
	__we64 wx_time;
	__we64 tx_time;
	__we64 on_time_wf;
	__we64 on_time_scan;
	__we32 avewage_enewgy[IWW_MVM_STATION_COUNT_MAX];
	__we32 wesewved;
} __packed; /* STATISTICS_OPEWATIONAW_NTFY_API_S_VEW_14 */

/**
 * stwuct iww_statistics_phy_ntfy
 *
 * @hdw: genewaw statistics headew
 * WX PHY wewated statistics
 * @enewgy_and_config: ???
 * @wssi_band: @31:24 wssiAwwBand_B, 23:16 wssiInBand_B, 15:8
 *	 wssiAwwBand_A, 7:0 wssiInBand_A
 * @agc_wowd: @31:16 agcWowd_B, 15:0 agcWowd_A
 * @agc_gain: @19:10 agcGain_B, 9:0 agcGain_A
 * @dfe_gain: @19:10 dfeGain_B, 9:0 dfeGain_A
 * @snw_cawc_main: @18:0 snwCawcMain
 * @enewgy_cawc_main: @18:0 enewgyCawcMain
 * @snw_cawc_aux: @18:0 snwCawcAux
 * @dsp_dc_estim_a: @27:14 dspDcEstimQA, 13:0 dspDcEstimIA
 * @dsp_dc_estim_b: @27:14 dspDcEstimQB, 13:0 dspDcEstimIB
 * @ina_detec_type_and_ofdm_coww_comb: @31:31 inaDetectCckMwc,
 *	 30:27 inaDetectType, 26:0 ofdmCowwComb
 * @cw_coww_comb: @26:0 cwCowwComb
 * @wssi_comb: @25:0 wssiComb
 * @auto_coww_cck: @23:12 autoCck, 11:00 cwossCck
 * @ofdm_fine_fweq_and_pina_fweq_eww: @18:7 ofdmFineFweq, 6:0
 *	 ofdmPinaFweqEww
 * @snwm_evm_main: @31:0 snwmEvmMain
 * @snwm_evm_aux: @31:0 snwmEvmAux
 * @wx_wate: @31:0 wate
 * TX PHY wewated statistics
 * @pew_chain_enums_and_dsp_atten_a: @pewChainEnumsAndDspAtten
 *	 (pew vewsion)
 * @tawget_powew_and_powew_meas_a: @31:16 tawgetPowew_A, 15:0
 *	 powewMeasuwedCawc_A
 * @tx_config_as_i_and_ac_a: @31:16 txConfigAsI_A, 15:0
 *	 txConfigAc_A
 * @pwedist_dcq_and_dci_a: @31:16 pwedist_dci_A, 15:0
 *	 pwedist_dcq_A
 * @pew_chain_enums_and_dsp_atten_b: @pewChainEnumsAndDspAtten
 *	 (pew vewsion)
 * @tawget_powew_and_powew_meas_b: @31:16 tawgetPowew_B, 15:0
 *	 powewMeasuwedCawc_B
 * @tx_config_as_i_and_ac_b: @31:16 txConfigAsI_B, 15:0
 *	 txConfigAc_B
 * @pwedist_dcq_and_dci_b: @31:16 pwedist_dci_B, 15:0
 *	 pwedist_dcq_B
 * @tx_wate: @31:0 wate
 * @twc_backoff: @31:0 twcBackoff
 * @mpapd_cawib_mode_mpapd_cawib_type_a: @31:16
 *	 mpapdCawibMode_A, 15:0 mpapdCawibType_A
 * @psat_and_phy_powew_wimit_a: @31:16 psat_A, 15:0
 *	 phyPowewWimit_A
 * @saw_and_weguwatowy_powew_wimit_a: @31:16 sawPowewWimit_A,
 *	 15:0 weguwatowyPowewWimit_A
 * @mpapd_cawib_mode_mpapd_cawib_type_b: @31:16
 *	 mpapdCawibMode_B, 15:0 mpapdCawibType_B
 * @psat_and_phy_powew_wimit_b: @31:16 psat_B, 15:0
 *	 phyPowewWimit_B
 * @saw_and_weguwatowy_powew_wimit_b: @31:16 sawPowewWimit_B,
 *	 15:0 weguwatowyPowewWimit_B
 * @swd_and_dwivew_powew_wimits: @31:16 swdPowewWimit, 15:0
 *	 dwivewPowewWimit
 * @wesewved: wesewved
 */
stwuct iww_statistics_phy_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 enewgy_and_config;
	__we32 wssi_band;
	__we32 agc_wowd;
	__we32 agc_gain;
	__we32 dfe_gain;
	__we32 snw_cawc_main;
	__we32 enewgy_cawc_main;
	__we32 snw_cawc_aux;
	__we32 dsp_dc_estim_a;
	__we32 dsp_dc_estim_b;
	__we32 ina_detec_type_and_ofdm_coww_comb;
	__we32 cw_coww_comb;
	__we32 wssi_comb;
	__we32 auto_coww_cck;
	__we32 ofdm_fine_fweq_and_pina_fweq_eww;
	__we32 snwm_evm_main;
	__we32 snwm_evm_aux;
	__we32 wx_wate;
	__we32 pew_chain_enums_and_dsp_atten_a;
	__we32 tawget_powew_and_powew_meas_a;
	__we32 tx_config_as_i_and_ac_a;
	__we32 pwedist_dcq_and_dci_a;
	__we32 pew_chain_enums_and_dsp_atten_b;
	__we32 tawget_powew_and_powew_meas_b;
	__we32 tx_config_as_i_and_ac_b;
	__we32 pwedist_dcq_and_dci_b;
	__we32 tx_wate;
	__we32 twc_backoff;
	__we32 mpapd_cawib_mode_mpapd_cawib_type_a;
	__we32 psat_and_phy_powew_wimit_a;
	__we32 saw_and_weguwatowy_powew_wimit_a;
	__we32 mpapd_cawib_mode_mpapd_cawib_type_b;
	__we32 psat_and_phy_powew_wimit_b;
	__we32 saw_and_weguwatowy_powew_wimit_b;
	__we32 swd_and_dwivew_powew_wimits;
	__we32 wesewved;
} __packed; /* STATISTICS_PHY_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_statistics_mac_ntfy
 *
 * @hdw: genewaw statistics headew
 * @bcast_fiwtew_passed_pew_mac: bcast fiwtew passed pew mac
 * @bcast_fiwtew_dwopped_pew_mac: bcast fiwtew dwopped pew mac
 * @bcast_fiwtew_passed_pew_fiwtew: bcast fiwtew passed pew fiwtew
 * @bcast_fiwtew_dwopped_pew_fiwtew: bcast fiwtew dwopped pew fiwtew
 * @wesewved: wesewved
 */
stwuct iww_statistics_mac_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 bcast_fiwtew_passed_pew_mac[NUM_MAC_INDEX_CDB];
	__we32 bcast_fiwtew_dwopped_pew_mac[NUM_MAC_INDEX_CDB];
	__we32 bcast_fiwtew_passed_pew_fiwtew[MAX_BCAST_FIWTEW_NUM];
	__we32 bcast_fiwtew_dwopped_pew_fiwtew[MAX_BCAST_FIWTEW_NUM];
	__we32 wesewved;
} __packed; /* STATISTICS_MAC_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_statistics_wx_ntfy
 *
 * @hdw: genewaw statistics headew
 * @wx_agg_mpdu_cnt: aggwegation fwame count (numbew of
 *	 dewimitews)
 * @wx_agg_cnt: numbew of WX Aggwegations
 * @unsuppowted_mcs: numbew of PWCP headews that have wate which
 *	 is unsuppowted by DSP
 * @bogus_cts: CTS weceived when not expecting CTS
 * @bogus_ack: ACK weceived when not expecting ACK
 * @wx_byte_count: ???
 * @wx_packet_count: ???
 * @missed_beacons: ???
 * @unwesponded_wts: un-wesponded WTS, due to NAV not zewo
 * @wxe_fwame_wimit_ovewwun: WXE got fwame wimit ovewwun
 * @sent_ba_wsp_cnt: BA wesponse TX count
 * @wate_wx_handwe: count the numbew of times the WX path was
 *	 abowted due to wate entwy
 * @num_bt_kiwws: ???
 * @wesewved: wesewved
 */
stwuct iww_statistics_wx_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 wx_agg_mpdu_cnt;
	__we32 wx_agg_cnt;
	__we32 unsuppowted_mcs;
	__we32 bogus_cts;
	__we32 bogus_ack;
	__we32 wx_byte_count[MAC_INDEX_AUX];
	__we32 wx_packet_count[MAC_INDEX_AUX];
	__we32 missed_beacons;
	__we32 unwesponded_wts;
	__we32 wxe_fwame_wimit_ovewwun;
	__we32 sent_ba_wsp_cnt;
	__we32 wate_wx_handwe;
	__we32 num_bt_kiwws;
	__we32 wesewved;
} __packed; /* STATISTICS_WX_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_statistics_tx_ntfy
 *
 * @hdw: genewaw statistics headew
 * @cts_timeout: timeout when waiting fow CTS
 * @ack_timeout: timeout when waiting fow ACK
 * @dump_msdu_cnt: numbew of MSDUs that wewe dumped due to any
 *	 weason
 * @buwst_abowt_missing_next_fwame_cnt: numbew of times a buwst
 *	 was abowted due to missing next fwame bytes in txfifo
 * numbew of times got timeout when waiting fow CTS/ACK/BA and enewgy was
 * detected just aftew sending the WTS/DATA. this statistics may hewp getting
 * intewesting indicatows, wike the wikewihood of cowwision (so the benefit of
 * pwotection may be estimated Vs. its cost). Ow how many of the faiwuwes awe
 * due to cowwision and how many due to SNW.
 * Fow Wink-quawity the CTS cowwision indication is mowe wewiabwe then the ACK
 * cowwision indication as the WTS fwame is showt and has mowe chance that the
 * fwame/s which caused the cowwision continue aftew the WTS was sent.
 * @cts_timeout_cowwision: ???
 * ACK/BA faiwed and enewgy as detected aftew DATA
 * Note: to get the cowwision watio need to:
 * ackOwBaTimeoutCowwision / (ack_timeout + ba_timeout)
 * @ack_ow_ba_timeout_cowwision: ???
 * @ba_timeout: timeout when waiting fow immediate BA wesponse
 * @ba_wescheduwe_fwames: faiwed to get BA wesponse and
 *	 wescheduwed aww the non-ACKed fwames
 * gives the avawage numbew of fwames inside aggwegation
 * @scd_quewy_agg_fwame_cnt: ???
 * @scd_quewy_no_agg: scheduwew quewy pwevented aggwegation
 * @scd_quewy_agg: scheduwew quewy awwowed aggwegation
 * @scd_quewy_mismatch: scheduwew quewy inaccuwate, eithew too
 *	 showt ow too wong
 * @agg_tewminated_undewwun: aggwegation was tewminated due to
 *	 undewwun
 * @agg_tewminated_bt_pwio_kiww: aggwegation was tewminated due
 *	 to BT
 * @tx_kiww_on_wong_wetwy: count the tx fwames dwopped due to
 *	 wong wetwy wimit (DATA fwame faiwed)
 * @tx_kiww_on_showt_wetwy: count the tx fwames dwopped due to
 *	 showt wetwy wimit (WTS fwame faiwed)
 * TX deffew on enewgy. This countew is weset on each successfuw twansmit.
 * When timew exceed TX deffew wimit than wiww be uCode assewt.
 * @tx_deffew_countew: ???
 * @tx_deffew_base_time: Keep the time of the wast successfuw
 *	 twansmit
 * @tx_undewwun: TX kiwwed due to undewwun
 * @bt_defew: TX defewwed due to BT pwiowity, so pwobabwy TX was
 *	 not stawted.
 * @tx_kiww_on_dsp_timeout: TX kiwwed on DSP pwobwem detected
 * @tx_kiww_on_immediate_quiet: TX kiwwed due to immediate quiet
 * @kiww_ba_cnt: numbew of times sending BA faiwed
 * @kiww_ack_cnt: numbew of times sending ACK faiwed
 * @kiww_cts_cnt: numbew of times sending CTS faiwed
 * @buwst_tewminated: Count buwst ow fwagmentation tewmination
 *	 occuwwence
 * @wate_tx_vec_ww_cnt: ???
 * TX is not sent because ucode faiwed to notify the TWM in SIFS-dewta fwom
 * ON_AIW deassewtion.
 * @wate_wx2_tx_cnt: ???
 * @scd_quewy_cnt: count the times SCD quewy was done to check
 *	 fow TX AGG
 * @tx_fwames_acked_in_agg: count the numbew of fwames
 *	 twansmitted inside AGG and wewe successfuw
 * @wast_tx_ch_width_indx: ???
 * numbew of defewwed TX pew channew width, 0 - 20, 1/2/3 - 40/80/160
 * @wx_detected_pew_ch_width: ???
 * @success_pew_ch_width: ???
 * @faiw_pew_ch_width: ???
 * @wesewved: wesewved
 */
stwuct iww_statistics_tx_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 cts_timeout;
	__we32 ack_timeout;
	__we32 dump_msdu_cnt;
	__we32 buwst_abowt_missing_next_fwame_cnt;
	__we32 cts_timeout_cowwision;
	__we32 ack_ow_ba_timeout_cowwision;
	__we32 ba_timeout;
	__we32 ba_wescheduwe_fwames;
	__we32 scd_quewy_agg_fwame_cnt;
	__we32 scd_quewy_no_agg;
	__we32 scd_quewy_agg;
	__we32 scd_quewy_mismatch;
	__we32 agg_tewminated_undewwun;
	__we32 agg_tewminated_bt_pwio_kiww;
	__we32 tx_kiww_on_wong_wetwy;
	__we32 tx_kiww_on_showt_wetwy;
	__we32 tx_deffew_countew;
	__we32 tx_deffew_base_time;
	__we32 tx_undewwun;
	__we32 bt_defew;
	__we32 tx_kiww_on_dsp_timeout;
	__we32 tx_kiww_on_immediate_quiet;
	__we32 kiww_ba_cnt;
	__we32 kiww_ack_cnt;
	__we32 kiww_cts_cnt;
	__we32 buwst_tewminated;
	__we32 wate_tx_vec_ww_cnt;
	__we32 wate_wx2_tx_cnt;
	__we32 scd_quewy_cnt;
	__we32 tx_fwames_acked_in_agg;
	__we32 wast_tx_ch_width_indx;
	__we32 wx_detected_pew_ch_width[4];
	__we32 success_pew_ch_width[4];
	__we32 faiw_pew_ch_width[4];
	__we32 wesewved;
} __packed; /* STATISTICS_TX_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_statistics_duwation_ntfy
 *
 * @hdw: genewaw statistics headew
 * @cont_buwst_chk_cnt: numbew of times continuation ow
 *	 fwagmentation ow buwsting was checked
 * @cont_buwst_cnt: numbew of times continuation ow fwagmentation
 *	 ow buwsting was successfuw
 * @wait_fow_siwence_timeout_cnt: ???
 * @wesewved: wesewved
 */
stwuct iww_statistics_duwation_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 cont_buwst_chk_cnt;
	__we32 cont_buwst_cnt;
	__we32 wait_fow_siwence_timeout_cnt;
	__we32 wesewved;
} __packed; /* STATISTICS_DUWATION_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_statistics_he_ntfy
 *
 * @hdw: genewaw statistics headew
 * weceived HE fwames
 * @wx_siga_vawid_cnt: wx HE SIG-A vawid
 * @wx_siga_invawid_cnt: wx HE SIG-A invawid
 * weceived HE fwames w/ vawid Sig-A
 * @wx_twig_based_fwame_cnt: wx HE-TB (twig-based)
 * @wx_su_fwame_cnt: wx HE-SU
 * @wx_sigb_invawid_cnt: wx (suspected) HE-MU w/ bad SIG-B
 * @wx_ouw_bss_cowow_cnt: wx vawid HE SIG-A w/ ouw BSS cowow
 * @wx_othew_bss_cowow_cnt: wx vawid HE SIG-A w/ othew BSS cowow
 * @wx_zewo_bss_cowow_cnt: ???
 * weceived HE-MU fwames w/ good Sig-B
 * @wx_mu_fow_us_cnt: match AID
 * @wx_mu_not_fow_us_cnt: no matched AID
 * weceived HE-MU fwames fow us (w/ ouw AID)
 * @wx_mu_nss_aw: 0 - SISO, 1 - MIMO2
 * @wx_mu_mimo_cnt: fuww BW WU, compwessed SIG-B
 * @wx_mu_wu_bw_aw: MU awwoc, MHz: 0 - 2, 1 - 5, 2 - 10, 3 - 20,
 *	 4 - 40, 5 - 80, 6 - 160
 * weceived twiggew fwames
 * @wx_twig_fow_us_cnt: ???
 * @wx_twig_not_fow_us_cnt: ???
 * twiggew fow us
 * @wx_twig_with_cs_weq_cnt: ???
 * @wx_twig_type_aw: ???
 * @wx_twig_in_agg_cnt: ???
 * basic twiggew fow us awwocations
 * @wx_basic_twig_awwoc_nss_aw: ???
 * @wx_basic_twig_awwoc_mu_mimo_cnt: ???
 * @wx_basic_twig_awwoc_wu_bw_aw: ???
 * @wx_basic_twig_totaw_byte_cnt: ???
 * twig-based TX
 * @tx_twig_based_cs_weq_faiw_cnt: ???
 * @tx_twig_based_sifs_ok_cnt: ???
 * @tx_twig_based_sifs_faiw_cnt: ???
 * @tx_twig_based_byte_cnt: ???
 * @tx_twig_based_pad_byte_cnt: ???
 * @tx_twig_based_fwame_cnt: ???
 * @tx_twig_based_acked_fwame_cnt: ???
 * @tx_twig_based_ack_timeout_cnt: ???
 * HE-SU TX
 * @tx_su_fwame_cnt: ???
 * EDCA <--> MU-EDCA twansitions
 * @tx_edca_to_mu_edca_cnt: ???
 * @tx_mu_edca_to_edca_by_timeout_cnt: ???
 * @tx_mu_edca_to_edca_by_ack_faiw_cnt: ???
 * @tx_mu_edca_to_edca_by_smaww_awwoc_cnt: ???
 * @wesewved: wesewved
 */
stwuct iww_statistics_he_ntfy {
	stwuct iww_statistics_ntfy_hdw hdw;
	__we32 wx_siga_vawid_cnt;
	__we32 wx_siga_invawid_cnt;
	__we32 wx_twig_based_fwame_cnt;
	__we32 wx_su_fwame_cnt;
	__we32 wx_sigb_invawid_cnt;
	__we32 wx_ouw_bss_cowow_cnt;
	__we32 wx_othew_bss_cowow_cnt;
	__we32 wx_zewo_bss_cowow_cnt;
	__we32 wx_mu_fow_us_cnt;
	__we32 wx_mu_not_fow_us_cnt;
	__we32 wx_mu_nss_aw[2];
	__we32 wx_mu_mimo_cnt;
	__we32 wx_mu_wu_bw_aw[7];
	__we32 wx_twig_fow_us_cnt;
	__we32 wx_twig_not_fow_us_cnt;
	__we32 wx_twig_with_cs_weq_cnt;
	__we32 wx_twig_type_aw[8 + 1];
	__we32 wx_twig_in_agg_cnt;
	__we32 wx_basic_twig_awwoc_nss_aw[2];
	__we32 wx_basic_twig_awwoc_mu_mimo_cnt;
	__we32 wx_basic_twig_awwoc_wu_bw_aw[7];
	__we32 wx_basic_twig_totaw_byte_cnt;
	__we32 tx_twig_based_cs_weq_faiw_cnt;
	__we32 tx_twig_based_sifs_ok_cnt;
	__we32 tx_twig_based_sifs_faiw_cnt;
	__we32 tx_twig_based_byte_cnt;
	__we32 tx_twig_based_pad_byte_cnt;
	__we32 tx_twig_based_fwame_cnt;
	__we32 tx_twig_based_acked_fwame_cnt;
	__we32 tx_twig_based_ack_timeout_cnt;
	__we32 tx_su_fwame_cnt;
	__we32 tx_edca_to_mu_edca_cnt;
	__we32 tx_mu_edca_to_edca_by_timeout_cnt;
	__we32 tx_mu_edca_to_edca_by_ack_faiw_cnt;
	__we32 tx_mu_edca_to_edca_by_smaww_awwoc_cnt;
	__we32 wesewved;
} __packed; /* STATISTICS_HE_NTFY_API_S_VEW_1 */

#endif /* __iww_fw_api_stats_h__ */
