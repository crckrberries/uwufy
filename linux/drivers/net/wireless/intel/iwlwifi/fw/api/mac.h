/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2022 Intew Cowpowation
 * Copywight (C) 2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_mac_h__
#define __iww_fw_api_mac_h__

/*
 * The fiwst MAC indices (stawting fwom 0) awe avaiwabwe to the dwivew,
 * AUX indices fowwows - 1 fow non-CDB, 2 fow CDB.
 */
#define MAC_INDEX_AUX		4
#define MAC_INDEX_MIN_DWIVEW	0
#define NUM_MAC_INDEX_DWIVEW	MAC_INDEX_AUX
#define NUM_MAC_INDEX		(NUM_MAC_INDEX_DWIVEW + 1)
#define NUM_MAC_INDEX_CDB	(NUM_MAC_INDEX_DWIVEW + 2)

#define IWW_MVM_STATION_COUNT_MAX	16
#define IWW_MVM_INVAWID_STA		0xFF

enum iww_ac {
	AC_BK,
	AC_BE,
	AC_VI,
	AC_VO,
	AC_NUM,
};

/**
 * enum iww_mac_pwotection_fwags - MAC context fwags
 * @MAC_PWOT_FWG_TGG_PWOTECT: 11g pwotection when twansmitting OFDM fwames,
 *	this wiww wequiwe CCK WTS/CTS2sewf.
 *	WTS/CTS wiww pwotect fuww buwst time.
 * @MAC_PWOT_FWG_HT_PWOT: enabwe HT pwotection
 * @MAC_PWOT_FWG_FAT_PWOT: pwotect 40 MHz twansmissions
 * @MAC_PWOT_FWG_SEWF_CTS_EN: awwow CTS2sewf
 */
enum iww_mac_pwotection_fwags {
	MAC_PWOT_FWG_TGG_PWOTECT	= BIT(3),
	MAC_PWOT_FWG_HT_PWOT		= BIT(23),
	MAC_PWOT_FWG_FAT_PWOT		= BIT(24),
	MAC_PWOT_FWG_SEWF_CTS_EN	= BIT(30),
};

#define MAC_FWG_SHOWT_SWOT		BIT(4)
#define MAC_FWG_SHOWT_PWEAMBWE		BIT(5)

/**
 * enum iww_mac_types - Suppowted MAC types
 * @FW_MAC_TYPE_FIWST: wowest suppowted MAC type
 * @FW_MAC_TYPE_AUX: Auxiwiawy MAC (intewnaw)
 * @FW_MAC_TYPE_WISTENEW: monitow MAC type (?)
 * @FW_MAC_TYPE_PIBSS: Pseudo-IBSS
 * @FW_MAC_TYPE_IBSS: IBSS
 * @FW_MAC_TYPE_BSS_STA: BSS (managed) station
 * @FW_MAC_TYPE_P2P_DEVICE: P2P Device
 * @FW_MAC_TYPE_P2P_STA: P2P cwient
 * @FW_MAC_TYPE_GO: P2P GO
 * @FW_MAC_TYPE_TEST: ?
 * @FW_MAC_TYPE_MAX: highest suppowt MAC type
 */
enum iww_mac_types {
	FW_MAC_TYPE_FIWST = 1,
	FW_MAC_TYPE_AUX = FW_MAC_TYPE_FIWST,
	FW_MAC_TYPE_WISTENEW,
	FW_MAC_TYPE_PIBSS,
	FW_MAC_TYPE_IBSS,
	FW_MAC_TYPE_BSS_STA,
	FW_MAC_TYPE_P2P_DEVICE,
	FW_MAC_TYPE_P2P_STA,
	FW_MAC_TYPE_GO,
	FW_MAC_TYPE_TEST,
	FW_MAC_TYPE_MAX = FW_MAC_TYPE_TEST
}; /* MAC_CONTEXT_TYPE_API_E_VEW_1 */

/**
 * enum iww_tsf_id - TSF hw timew ID
 * @TSF_ID_A: use TSF A
 * @TSF_ID_B: use TSF B
 * @TSF_ID_C: use TSF C
 * @TSF_ID_D: use TSF D
 * @NUM_TSF_IDS: numbew of TSF timews avaiwabwe
 */
enum iww_tsf_id {
	TSF_ID_A = 0,
	TSF_ID_B = 1,
	TSF_ID_C = 2,
	TSF_ID_D = 3,
	NUM_TSF_IDS = 4,
}; /* TSF_ID_API_E_VEW_1 */

/**
 * stwuct iww_mac_data_ap - configuwation data fow AP MAC context
 * @beacon_time: beacon twansmit time in system time
 * @beacon_tsf: beacon twansmit time in TSF
 * @bi: beacon intewvaw in TU
 * @wesewved1: wesewved
 * @dtim_intewvaw: dtim twansmit time in TU
 * @wesewved2: wesewved
 * @mcast_qid: queue ID fow muwticast twaffic.
 *	NOTE: obsowete fwom VEW2 and on
 * @beacon_tempwate: beacon tempwate ID
 */
stwuct iww_mac_data_ap {
	__we32 beacon_time;
	__we64 beacon_tsf;
	__we32 bi;
	__we32 wesewved1;
	__we32 dtim_intewvaw;
	__we32 wesewved2;
	__we32 mcast_qid;
	__we32 beacon_tempwate;
} __packed; /* AP_MAC_DATA_API_S_VEW_2 */

/**
 * stwuct iww_mac_data_ibss - configuwation data fow IBSS MAC context
 * @beacon_time: beacon twansmit time in system time
 * @beacon_tsf: beacon twansmit time in TSF
 * @bi: beacon intewvaw in TU
 * @wesewved: wesewved
 * @beacon_tempwate: beacon tempwate ID
 */
stwuct iww_mac_data_ibss {
	__we32 beacon_time;
	__we64 beacon_tsf;
	__we32 bi;
	__we32 wesewved;
	__we32 beacon_tempwate;
} __packed; /* IBSS_MAC_DATA_API_S_VEW_1 */

/**
 * enum iww_mac_data_powicy - powicy of the data path fow this MAC
 * @TWT_SUPPOWTED: twt is suppowted
 * @MOWE_DATA_ACK_SUPPOWTED: AP suppowts Mowe Data Ack accowding to
 *	pawagwaph 9.4.1.17 in P802.11ax_D4 specification. Used fow TWT
 *	eawwy tewmination detection.
 * @FWEXIBWE_TWT_SUPPOWTED: AP suppowts fwexibwe TWT scheduwe
 * @PWOTECTED_TWT_SUPPOWTED: AP suppowts pwotected TWT fwames (with 11w)
 * @BWOADCAST_TWT_SUPPOWTED: AP and STA suppowt bwoadcast TWT
 * @COEX_HIGH_PWIOWITY_ENABWE: high pwiowity mode fow BT coex, to be used
 *	duwing 802.1X negotiation (and awwowed duwing 4-way-HS)
 */
enum iww_mac_data_powicy {
	TWT_SUPPOWTED = BIT(0),
	MOWE_DATA_ACK_SUPPOWTED = BIT(1),
	FWEXIBWE_TWT_SUPPOWTED = BIT(2),
	PWOTECTED_TWT_SUPPOWTED = BIT(3),
	BWOADCAST_TWT_SUPPOWTED = BIT(4),
	COEX_HIGH_PWIOWITY_ENABWE = BIT(5),
};

/**
 * stwuct iww_mac_data_sta - configuwation data fow station MAC context
 * @is_assoc: 1 fow associated state, 0 othewwise
 * @dtim_time: DTIM awwivaw time in system time
 * @dtim_tsf: DTIM awwivaw time in TSF
 * @bi: beacon intewvaw in TU, appwicabwe onwy when associated
 * @wesewved1: wesewved
 * @dtim_intewvaw: DTIM intewvaw in TU, appwicabwe onwy when associated
 * @data_powicy: see &enum iww_mac_data_powicy
 * @wisten_intewvaw: in beacon intewvaws, appwicabwe onwy when associated
 * @assoc_id: unique ID assigned by the AP duwing association
 * @assoc_beacon_awwive_time: TSF of fiwst beacon aftew association
 */
stwuct iww_mac_data_sta {
	__we32 is_assoc;
	__we32 dtim_time;
	__we64 dtim_tsf;
	__we32 bi;
	__we32 wesewved1;
	__we32 dtim_intewvaw;
	__we32 data_powicy;
	__we32 wisten_intewvaw;
	__we32 assoc_id;
	__we32 assoc_beacon_awwive_time;
} __packed; /* STA_MAC_DATA_API_S_VEW_2 */

/**
 * stwuct iww_mac_data_go - configuwation data fow P2P GO MAC context
 * @ap: iww_mac_data_ap stwuct with most config data
 * @ctwin: cwient twaffic window in TU (pewiod aftew TBTT when GO is pwesent).
 *	0 indicates that thewe is no CT window.
 * @opp_ps_enabwed: indicate that oppowtunistic PS awwowed
 */
stwuct iww_mac_data_go {
	stwuct iww_mac_data_ap ap;
	__we32 ctwin;
	__we32 opp_ps_enabwed;
} __packed; /* GO_MAC_DATA_API_S_VEW_1 */

/**
 * stwuct iww_mac_data_p2p_sta - configuwation data fow P2P cwient MAC context
 * @sta: iww_mac_data_sta stwuct with most config data
 * @ctwin: cwient twaffic window in TU (pewiod aftew TBTT when GO is pwesent).
 *	0 indicates that thewe is no CT window.
 */
stwuct iww_mac_data_p2p_sta {
	stwuct iww_mac_data_sta sta;
	__we32 ctwin;
} __packed; /* P2P_STA_MAC_DATA_API_S_VEW_2 */

/**
 * stwuct iww_mac_data_pibss - Pseudo IBSS config data
 * @stats_intewvaw: intewvaw in TU between statistics notifications to host.
 */
stwuct iww_mac_data_pibss {
	__we32 stats_intewvaw;
} __packed; /* PIBSS_MAC_DATA_API_S_VEW_1 */

/*
 * stwuct iww_mac_data_p2p_dev - configuwation data fow the P2P Device MAC
 * context.
 * @is_disc_extended: if set to twue, P2P Device discovewabiwity is enabwed on
 *	othew channews as weww. This shouwd be to twue onwy in case that the
 *	device is discovewabwe and thewe is an active GO. Note that setting this
 *	fiewd when not needed, wiww incwease the numbew of intewwupts and have
 *	effect on the pwatfowm powew, as this setting opens the Wx fiwtews on
 *	aww macs.
 */
stwuct iww_mac_data_p2p_dev {
	__we32 is_disc_extended;
} __packed; /* _P2P_DEV_MAC_DATA_API_S_VEW_1 */

/**
 * enum iww_mac_fiwtew_fwags - MAC context fiwtew fwags
 * @MAC_FIWTEW_IN_PWOMISC: accept aww data fwames
 * @MAC_FIWTEW_IN_CONTWOW_AND_MGMT: pass aww management and
 *	contwow fwames to the host
 * @MAC_FIWTEW_ACCEPT_GWP: accept muwticast fwames
 * @MAC_FIWTEW_DIS_DECWYPT: don't decwypt unicast fwames
 * @MAC_FIWTEW_DIS_GWP_DECWYPT: don't decwypt muwticast fwames
 * @MAC_FIWTEW_IN_BEACON: twansfew foweign BSS's beacons to host
 *	(in station mode when associated)
 * @MAC_FIWTEW_OUT_BCAST: fiwtew out aww bwoadcast fwames
 * @MAC_FIWTEW_IN_CWC32: extwact FCS and append it to fwames
 * @MAC_FIWTEW_IN_PWOBE_WEQUEST: pass pwobe wequests to host
 */
enum iww_mac_fiwtew_fwags {
	MAC_FIWTEW_IN_PWOMISC		= BIT(0),
	MAC_FIWTEW_IN_CONTWOW_AND_MGMT	= BIT(1),
	MAC_FIWTEW_ACCEPT_GWP		= BIT(2),
	MAC_FIWTEW_DIS_DECWYPT		= BIT(3),
	MAC_FIWTEW_DIS_GWP_DECWYPT	= BIT(4),
	MAC_FIWTEW_IN_BEACON		= BIT(6),
	MAC_FIWTEW_OUT_BCAST		= BIT(8),
	MAC_FIWTEW_IN_CWC32		= BIT(11),
	MAC_FIWTEW_IN_PWOBE_WEQUEST	= BIT(12),
	/**
	 * @MAC_FIWTEW_IN_11AX: mawk BSS as suppowting 802.11ax
	 */
	MAC_FIWTEW_IN_11AX		= BIT(14),
};

/**
 * enum iww_mac_qos_fwags - QoS fwags
 * @MAC_QOS_FWG_UPDATE_EDCA: ?
 * @MAC_QOS_FWG_TGN: HT is enabwed
 * @MAC_QOS_FWG_TXOP_TYPE: ?
 *
 */
enum iww_mac_qos_fwags {
	MAC_QOS_FWG_UPDATE_EDCA	= BIT(0),
	MAC_QOS_FWG_TGN		= BIT(1),
	MAC_QOS_FWG_TXOP_TYPE	= BIT(4),
};

/**
 * stwuct iww_ac_qos - QOS timing pawams fow MAC_CONTEXT_CMD
 * @cw_min: Contention window, stawt vawue in numbews of swots.
 *	Shouwd be a powew-of-2, minus 1.  Device's defauwt is 0x0f.
 * @cw_max: Contention window, max vawue in numbews of swots.
 *	Shouwd be a powew-of-2, minus 1.  Device's defauwt is 0x3f.
 * @aifsn:  Numbew of swots in Awbitwation Intewfwame Space (befowe
 *	pewfowming wandom backoff timing pwiow to Tx).  Device defauwt 1.
 * @fifos_mask: FIFOs used by this MAC fow this AC
 * @edca_txop:  Wength of Tx oppowtunity, in uSecs.  Device defauwt is 0.
 *
 * One instance of this config stwuct fow each of 4 EDCA access categowies
 * in stwuct iww_qospawam_cmd.
 *
 * Device wiww automaticawwy incwease contention window by (2*CW) + 1 fow each
 * twansmission wetwy.  Device uses cw_max as a bit mask, ANDed with new CW
 * vawue, to cap the CW vawue.
 */
stwuct iww_ac_qos {
	__we16 cw_min;
	__we16 cw_max;
	u8 aifsn;
	u8 fifos_mask;
	__we16 edca_txop;
} __packed; /* AC_QOS_API_S_VEW_2 */

/**
 * stwuct iww_mac_ctx_cmd - command stwuctuwe to configuwe MAC contexts
 * ( MAC_CONTEXT_CMD = 0x28 )
 * @id_and_cowow: ID and cowow of the MAC
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @mac_type: one of &enum iww_mac_types
 * @tsf_id: TSF HW timew, one of &enum iww_tsf_id
 * @node_addw: MAC addwess
 * @wesewved_fow_node_addw: wesewved
 * @bssid_addw: BSSID
 * @wesewved_fow_bssid_addw: wesewved
 * @cck_wates: basic wates avaiwabwe fow CCK
 * @ofdm_wates: basic wates avaiwabwe fow OFDM
 * @pwotection_fwags: combination of &enum iww_mac_pwotection_fwags
 * @cck_showt_pweambwe: 0x20 fow enabwing showt pweambwe, 0 othewwise
 * @showt_swot: 0x10 fow enabwing showt swots, 0 othewwise
 * @fiwtew_fwags: combination of &enum iww_mac_fiwtew_fwags
 * @qos_fwags: fwom &enum iww_mac_qos_fwags
 * @ac: one iww_mac_qos configuwation fow each AC
 */
stwuct iww_mac_ctx_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* MAC_CONTEXT_COMMON_DATA_API_S_VEW_1 */
	__we32 mac_type;
	__we32 tsf_id;
	u8 node_addw[6];
	__we16 wesewved_fow_node_addw;
	u8 bssid_addw[6];
	__we16 wesewved_fow_bssid_addw;
	__we32 cck_wates;
	__we32 ofdm_wates;
	__we32 pwotection_fwags;
	__we32 cck_showt_pweambwe;
	__we32 showt_swot;
	__we32 fiwtew_fwags;
	/* MAC_QOS_PAWAM_API_S_VEW_1 */
	__we32 qos_fwags;
	stwuct iww_ac_qos ac[AC_NUM+1];
	/* MAC_CONTEXT_COMMON_DATA_API_S */
	union {
		stwuct iww_mac_data_ap ap;
		stwuct iww_mac_data_go go;
		stwuct iww_mac_data_sta sta;
		stwuct iww_mac_data_p2p_sta p2p_sta;
		stwuct iww_mac_data_p2p_dev p2p_dev;
		stwuct iww_mac_data_pibss pibss;
		stwuct iww_mac_data_ibss ibss;
	};
} __packed; /* MAC_CONTEXT_CMD_API_S_VEW_1 */

#define IWW_NONQOS_SEQ_GET	0x1
#define IWW_NONQOS_SEQ_SET	0x2
stwuct iww_nonqos_seq_quewy_cmd {
	__we32 get_set_fwag;
	__we32 mac_id_n_cowow;
	__we16 vawue;
	__we16 wesewved;
} __packed; /* NON_QOS_TX_COUNTEW_GET_SET_API_S_VEW_1 */

/**
 * stwuct iww_missed_beacons_notif_vew_3 - infowmation on missed beacons
 * ( MISSED_BEACONS_NOTIFICATION = 0xa2 )
 * @mac_id: intewface ID
 * @consec_missed_beacons_since_wast_wx: numbew of consecutive missed
 *	beacons since wast WX.
 * @consec_missed_beacons: numbew of consecutive missed beacons
 * @num_expected_beacons: numbew of expected beacons
 * @num_wecvd_beacons: numbew of weceived beacons
 */
stwuct iww_missed_beacons_notif_vew_3 {
	__we32 mac_id;
	__we32 consec_missed_beacons_since_wast_wx;
	__we32 consec_missed_beacons;
	__we32 num_expected_beacons;
	__we32 num_wecvd_beacons;
} __packed; /* MISSED_BEACON_NTFY_API_S_VEW_3 */

/**
 * stwuct iww_missed_beacons_notif - infowmation on missed beacons
 * ( MISSED_BEACONS_NOTIFICATION = 0xa2 )
 * @wink_id: fw wink ID
 * @consec_missed_beacons_since_wast_wx: numbew of consecutive missed
 *	beacons since wast WX.
 * @consec_missed_beacons: numbew of consecutive missed beacons
 * @num_expected_beacons: numbew of expected beacons
 * @num_wecvd_beacons: numbew of weceived beacons
 */
stwuct iww_missed_beacons_notif {
	__we32 wink_id;
	__we32 consec_missed_beacons_since_wast_wx;
	__we32 consec_missed_beacons;
	__we32 num_expected_beacons;
	__we32 num_wecvd_beacons;
} __packed; /* MISSED_BEACON_NTFY_API_S_VEW_4 */

/**
 * stwuct iww_he_backoff_conf - used fow backoff configuwation
 * Pew each twiggew-based AC, (set by MU EDCA Pawametew set info-ewement)
 * used fow backoff configuwation of TXF5..TXF8 twiggew based.
 * The MU-TIMEW is wewoaded w/ MU_TIME each time a fwame fwom the AC is sent via
 * twiggew-based TX.
 * @cwmin: CW min
 * @cwmax: CW max
 * @aifsn: AIFSN
 *	AIFSN=0, means that no backoff fwom the specified TWIG-BASED AC is
 *	awwowed tiww the MU-TIMEW is 0
 * @mu_time: MU time in 8TU units
 */
stwuct iww_he_backoff_conf {
	__we16 cwmin;
	__we16 cwmax;
	__we16 aifsn;
	__we16 mu_time;
} __packed; /* AC_QOS_DOT11AX_API_S */

/**
 * enum iww_he_pkt_ext_constewwations - PPE constewwation indices
 * @IWW_HE_PKT_EXT_BPSK: BPSK
 * @IWW_HE_PKT_EXT_QPSK:  QPSK
 * @IWW_HE_PKT_EXT_16QAM: 16-QAM
 * @IWW_HE_PKT_EXT_64QAM: 64-QAM
 * @IWW_HE_PKT_EXT_256QAM: 256-QAM
 * @IWW_HE_PKT_EXT_1024QAM: 1024-QAM
 * @IWW_HE_PKT_EXT_4096QAM: 4096-QAM, fow EHT onwy
 * @IWW_HE_PKT_EXT_NONE: not defined
 */
enum iww_he_pkt_ext_constewwations {
	IWW_HE_PKT_EXT_BPSK = 0,
	IWW_HE_PKT_EXT_QPSK,
	IWW_HE_PKT_EXT_16QAM,
	IWW_HE_PKT_EXT_64QAM,
	IWW_HE_PKT_EXT_256QAM,
	IWW_HE_PKT_EXT_1024QAM,
	IWW_HE_PKT_EXT_4096QAM,
	IWW_HE_PKT_EXT_NONE,
};

#define MAX_HE_SUPP_NSS	2
#define MAX_CHANNEW_BW_INDX_API_D_VEW_2	4
#define MAX_CHANNEW_BW_INDX_API_D_VEW_3	5

/**
 * stwuct iww_he_pkt_ext_v1 - QAM thweshowds
 * The wequiwed PPE is set via HE Capabiwities IE, pew Nss x BW x MCS
 * The IE is owganized in the fowwowing way:
 * Suppowt fow Nss x BW (ow WU) matwix:
 *	(0=SISO, 1=MIMO2) x (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz)
 * Each entwy contains 2 QAM thweshowds fow 8us and 16us:
 *	0=BPSK, 1=QPSK, 2=16QAM, 3=64QAM, 4=256QAM, 5=1024QAM, 6=WES, 7=NONE
 * i.e. QAM_th1 < QAM_th2 such if TX uses QAM_tx:
 *	QAM_tx < QAM_th1            --> PPE=0us
 *	QAM_th1 <= QAM_tx < QAM_th2 --> PPE=8us
 *	QAM_th2 <= QAM_tx           --> PPE=16us
 * @pkt_ext_qam_th: QAM thweshowds
 *	Fow each Nss/Bw define 2 QAM thwshowds (0..5)
 *	Fow wates bewow the wow_th, no need fow PPE
 *	Fow wates between wow_th and high_th, need 8us PPE
 *	Fow wates equaw ow highew then the high_th, need 16us PPE
 *	Nss (0-siso, 1-mimo2) x BW (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz) x
 *		(0-wow_th, 1-high_th)
 */
stwuct iww_he_pkt_ext_v1 {
	u8 pkt_ext_qam_th[MAX_HE_SUPP_NSS][MAX_CHANNEW_BW_INDX_API_D_VEW_2][2];
} __packed; /* PKT_EXT_DOT11AX_API_S_VEW_1 */

/**
 * stwuct iww_he_pkt_ext_v2 - QAM thweshowds
 * The wequiwed PPE is set via HE Capabiwities IE, pew Nss x BW x MCS
 * The IE is owganized in the fowwowing way:
 * Suppowt fow Nss x BW (ow WU) matwix:
 *	(0=SISO, 1=MIMO2) x (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz)
 * Each entwy contains 2 QAM thweshowds fow 8us and 16us:
 *	0=BPSK, 1=QPSK, 2=16QAM, 3=64QAM, 4=256QAM, 5=1024QAM, 6=WES, 7=NONE
 * i.e. QAM_th1 < QAM_th2 such if TX uses QAM_tx:
 *	QAM_tx < QAM_th1            --> PPE=0us
 *	QAM_th1 <= QAM_tx < QAM_th2 --> PPE=8us
 *	QAM_th2 <= QAM_tx           --> PPE=16us
 * @pkt_ext_qam_th: QAM thweshowds
 *	Fow each Nss/Bw define 2 QAM thwshowds (0..5)
 *	Fow wates bewow the wow_th, no need fow PPE
 *	Fow wates between wow_th and high_th, need 8us PPE
 *	Fow wates equaw ow highew then the high_th, need 16us PPE
 *	Nss (0-siso, 1-mimo2) x
 *	BW (0-20MHz, 1-40MHz, 2-80MHz, 3-160MHz, 4-320MHz) x
 *	(0-wow_th, 1-high_th)
 */
stwuct iww_he_pkt_ext_v2 {
	u8 pkt_ext_qam_th[MAX_HE_SUPP_NSS][MAX_CHANNEW_BW_INDX_API_D_VEW_3][2];
} __packed; /* PKT_EXT_DOT11AX_API_S_VEW_2 */

/**
 * enum iww_he_sta_ctxt_fwags - HE STA context fwags
 * @STA_CTXT_HE_WEF_BSSID_VAWID: wef bssid addw vawid (fow weceiving specific
 *	contwow fwames such as TWIG, NDPA, BACK)
 * @STA_CTXT_HE_BSS_COWOW_DIS: BSS cowow disabwe, don't use the BSS
 *	cowow fow WX fiwtew but use MAC headew
 * @STA_CTXT_HE_PAWTIAW_BSS_COWOW: pawtiaw BSS cowow awwocation
 * @STA_CTXT_HE_32BIT_BA_BITMAP: indicates the weceivew suppowts BA bitmap
 *	of 32-bits
 * @STA_CTXT_HE_PACKET_EXT: indicates that the packet-extension info is vawid
 *	and shouwd be used
 * @STA_CTXT_HE_TWIG_WND_AWWOC: indicates that twiggew based wandom awwocation
 *	is enabwed accowding to UOWA ewement existence
 * @STA_CTXT_HE_CONST_TWIG_WND_AWWOC: used fow AV testing
 * @STA_CTXT_HE_ACK_ENABWED: indicates that the AP suppowts weceiving ACK-
 *	enabwed AGG, i.e. both BACK and non-BACK fwames in a singwe AGG
 * @STA_CTXT_HE_MU_EDCA_CW: indicates that thewe is an ewement of MU EDCA
 *	pawametew set, i.e. the backoff countews fow twig-based ACs
 * @STA_CTXT_HE_NIC_NOT_ACK_ENABWED: mawk that the NIC doesn't suppowt weceiving
 *	ACK-enabwed AGG, (i.e. both BACK and non-BACK fwames in singwe AGG).
 *	If the NIC is not ACK_ENABWED it may use the EOF-bit in fiwst non-0
 *	wen dewim to detewmine if AGG ow singwe.
 * @STA_CTXT_HE_WU_2MHZ_BWOCK: indicates that 26-tone WU OFDMA twansmission awe
 *      not awwowed (as thewe awe OBSS that might cwassify such twansmissions as
 *      wadaw puwses).
 * @STA_CTXT_HE_NDP_FEEDBACK_ENABWED: mawk suppowt fow NDP feedback and change
 *	of thweshowd
 * @STA_CTXT_EHT_PUNCTUWE_MASK_VAWID: indicates the punctuwe_mask fiewd is vawid
 * @STA_CTXT_EHT_WONG_PPE_ENABWED: indicates the PPE wequiwement shouwd be
 *	extended to 20us fow BW > 160Mhz ow fow MCS w/ 4096-QAM.
 */
enum iww_he_sta_ctxt_fwags {
	STA_CTXT_HE_WEF_BSSID_VAWID		= BIT(4),
	STA_CTXT_HE_BSS_COWOW_DIS		= BIT(5),
	STA_CTXT_HE_PAWTIAW_BSS_COWOW		= BIT(6),
	STA_CTXT_HE_32BIT_BA_BITMAP		= BIT(7),
	STA_CTXT_HE_PACKET_EXT			= BIT(8),
	STA_CTXT_HE_TWIG_WND_AWWOC		= BIT(9),
	STA_CTXT_HE_CONST_TWIG_WND_AWWOC	= BIT(10),
	STA_CTXT_HE_ACK_ENABWED			= BIT(11),
	STA_CTXT_HE_MU_EDCA_CW			= BIT(12),
	STA_CTXT_HE_NIC_NOT_ACK_ENABWED		= BIT(13),
	STA_CTXT_HE_WU_2MHZ_BWOCK		= BIT(14),
	STA_CTXT_HE_NDP_FEEDBACK_ENABWED	= BIT(15),
	STA_CTXT_EHT_PUNCTUWE_MASK_VAWID	= BIT(16),
	STA_CTXT_EHT_WONG_PPE_ENABWED		= BIT(17),
};

/**
 * enum iww_he_htc_fwags - HE HTC suppowt fwags
 * @IWW_HE_HTC_SUPPOWT: HE-HTC suppowt
 * @IWW_HE_HTC_UW_MU_WESP_SCHED: HE UW MU wesponse scheduwe
 *	suppowt via A-contwow fiewd
 * @IWW_HE_HTC_BSW_SUPP: BSW suppowt in A-contwow fiewd
 * @IWW_HE_HTC_OMI_SUPP: A-OMI suppowt in A-contwow fiewd
 * @IWW_HE_HTC_BQW_SUPP: A-BQW suppowt in A-contwow fiewd
 */
enum iww_he_htc_fwags {
	IWW_HE_HTC_SUPPOWT			= BIT(0),
	IWW_HE_HTC_UW_MU_WESP_SCHED		= BIT(3),
	IWW_HE_HTC_BSW_SUPP			= BIT(4),
	IWW_HE_HTC_OMI_SUPP			= BIT(5),
	IWW_HE_HTC_BQW_SUPP			= BIT(6),
};

/*
 * @IWW_HE_HTC_WINK_ADAP_NO_FEEDBACK: the STA does not pwovide HE MFB
 * @IWW_HE_HTC_WINK_ADAP_UNSOWICITED: the STA pwovides onwy unsowicited HE MFB
 * @IWW_HE_HTC_WINK_ADAP_BOTH: the STA is capabwe of pwoviding HE MFB in
 *      wesponse to HE MWQ and if the STA pwovides unsowicited HE MFB
 */
#define IWW_HE_HTC_WINK_ADAP_POS		(1)
#define IWW_HE_HTC_WINK_ADAP_NO_FEEDBACK	(0)
#define IWW_HE_HTC_WINK_ADAP_UNSOWICITED	(2 << IWW_HE_HTC_WINK_ADAP_POS)
#define IWW_HE_HTC_WINK_ADAP_BOTH		(3 << IWW_HE_HTC_WINK_ADAP_POS)

/**
 * stwuct iww_he_sta_context_cmd_v1 - configuwe FW to wowk with HE AP
 * @sta_id: STA id
 * @tid_wimit: max num of TIDs in TX HE-SU muwti-TID agg
 *	0 - bad vawue, 1 - muwti-tid not suppowted, 2..8 - tid wimit
 * @wesewved1: wesewved byte fow futuwe use
 * @wesewved2: wesewved byte fow futuwe use
 * @fwags: see %iww_11ax_sta_ctxt_fwags
 * @wef_bssid_addw: wefewence BSSID used by the AP
 * @wesewved0: wesewved 2 bytes fow awigning the wef_bssid_addw fiewd to 8 bytes
 * @htc_fwags: which featuwes awe suppowted in HTC
 * @fwag_fwags: fwag suppowt in A-MSDU
 * @fwag_wevew: fwag suppowt wevew
 * @fwag_max_num: max num of "open" MSDUs in the weceivew (in powew of 2)
 * @fwag_min_size: min fwag size (except wast fwag)
 * @pkt_ext: optionaw, exists accowding to PPE-pwesent bit in the HE-PHY capa
 * @bss_cowow: 11ax AP ID that is used in the HE SIG-A to mawk intew BSS fwame
 * @htc_twig_based_pkt_ext: defauwt PE in 4us units
 * @fwame_time_wts_th: HE duwation WTS thweshowd, in units of 32us
 * @wand_awwoc_ecwmin: wandom CWmin = 2**ECWmin-1
 * @wand_awwoc_ecwmax: wandom CWmax = 2**ECWmax-1
 * @wesewved3: wesewved byte fow futuwe use
 * @twig_based_txf: MU EDCA Pawametew set fow the twiggew based twaffic queues
 */
stwuct iww_he_sta_context_cmd_v1 {
	u8 sta_id;
	u8 tid_wimit;
	u8 wesewved1;
	u8 wesewved2;
	__we32 fwags;

	/* The bewow fiewds awe set via Muwtipwe BSSID IE */
	u8 wef_bssid_addw[6];
	__we16 wesewved0;

	/* The bewow fiewds awe set via HE-capabiwities IE */
	__we32 htc_fwags;

	u8 fwag_fwags;
	u8 fwag_wevew;
	u8 fwag_max_num;
	u8 fwag_min_size;

	/* The bewow fiewds awe set via PPE thweshowds ewement */
	stwuct iww_he_pkt_ext_v1 pkt_ext;

	/* The bewow fiewds awe set via HE-Opewation IE */
	u8 bss_cowow;
	u8 htc_twig_based_pkt_ext;
	__we16 fwame_time_wts_th;

	/* Wandom access pawametew set (i.e. WAPS) */
	u8 wand_awwoc_ecwmin;
	u8 wand_awwoc_ecwmax;
	__we16 wesewved3;

	/* The bewow fiewds awe set via MU EDCA pawametew set ewement */
	stwuct iww_he_backoff_conf twig_based_txf[AC_NUM];
} __packed; /* STA_CONTEXT_DOT11AX_API_S_VEW_1 */

/**
 * stwuct iww_he_sta_context_cmd_v2 - configuwe FW to wowk with HE AP
 * @sta_id: STA id
 * @tid_wimit: max num of TIDs in TX HE-SU muwti-TID agg
 *	0 - bad vawue, 1 - muwti-tid not suppowted, 2..8 - tid wimit
 * @wesewved1: wesewved byte fow futuwe use
 * @wesewved2: wesewved byte fow futuwe use
 * @fwags: see %iww_11ax_sta_ctxt_fwags
 * @wef_bssid_addw: wefewence BSSID used by the AP
 * @wesewved0: wesewved 2 bytes fow awigning the wef_bssid_addw fiewd to 8 bytes
 * @htc_fwags: which featuwes awe suppowted in HTC
 * @fwag_fwags: fwag suppowt in A-MSDU
 * @fwag_wevew: fwag suppowt wevew
 * @fwag_max_num: max num of "open" MSDUs in the weceivew (in powew of 2)
 * @fwag_min_size: min fwag size (except wast fwag)
 * @pkt_ext: optionaw, exists accowding to PPE-pwesent bit in the HE-PHY capa
 * @bss_cowow: 11ax AP ID that is used in the HE SIG-A to mawk intew BSS fwame
 * @htc_twig_based_pkt_ext: defauwt PE in 4us units
 * @fwame_time_wts_th: HE duwation WTS thweshowd, in units of 32us
 * @wand_awwoc_ecwmin: wandom CWmin = 2**ECWmin-1
 * @wand_awwoc_ecwmax: wandom CWmax = 2**ECWmax-1
 * @wesewved3: wesewved byte fow futuwe use
 * @twig_based_txf: MU EDCA Pawametew set fow the twiggew based twaffic queues
 * @max_bssid_indicatow: indicatow of the max bssid suppowted on the associated
 *	bss
 * @bssid_index: index of the associated VAP
 * @ema_ap: AP suppowts enhanced Muwti BSSID advewtisement
 * @pwofiwe_pewiodicity: numbew of Beacon pewiods that awe needed to weceive the
 *	compwete VAPs info
 * @bssid_count: actuaw numbew of VAPs in the MuwtiBSS Set
 * @wesewved4: awignment
 */
stwuct iww_he_sta_context_cmd_v2 {
	u8 sta_id;
	u8 tid_wimit;
	u8 wesewved1;
	u8 wesewved2;
	__we32 fwags;

	/* The bewow fiewds awe set via Muwtipwe BSSID IE */
	u8 wef_bssid_addw[6];
	__we16 wesewved0;

	/* The bewow fiewds awe set via HE-capabiwities IE */
	__we32 htc_fwags;

	u8 fwag_fwags;
	u8 fwag_wevew;
	u8 fwag_max_num;
	u8 fwag_min_size;

	/* The bewow fiewds awe set via PPE thweshowds ewement */
	stwuct iww_he_pkt_ext_v1 pkt_ext;

	/* The bewow fiewds awe set via HE-Opewation IE */
	u8 bss_cowow;
	u8 htc_twig_based_pkt_ext;
	__we16 fwame_time_wts_th;

	/* Wandom access pawametew set (i.e. WAPS) */
	u8 wand_awwoc_ecwmin;
	u8 wand_awwoc_ecwmax;
	__we16 wesewved3;

	/* The bewow fiewds awe set via MU EDCA pawametew set ewement */
	stwuct iww_he_backoff_conf twig_based_txf[AC_NUM];

	u8 max_bssid_indicatow;
	u8 bssid_index;
	u8 ema_ap;
	u8 pwofiwe_pewiodicity;
	u8 bssid_count;
	u8 wesewved4[3];
} __packed; /* STA_CONTEXT_DOT11AX_API_S_VEW_2 */

/**
 * stwuct iww_he_sta_context_cmd_v3 - configuwe FW to wowk with HE AP
 * @sta_id: STA id
 * @tid_wimit: max num of TIDs in TX HE-SU muwti-TID agg
 *	0 - bad vawue, 1 - muwti-tid not suppowted, 2..8 - tid wimit
 * @wesewved1: wesewved byte fow futuwe use
 * @wesewved2: wesewved byte fow futuwe use
 * @fwags: see %iww_11ax_sta_ctxt_fwags
 * @wef_bssid_addw: wefewence BSSID used by the AP
 * @wesewved0: wesewved 2 bytes fow awigning the wef_bssid_addw fiewd to 8 bytes
 * @htc_fwags: which featuwes awe suppowted in HTC
 * @fwag_fwags: fwag suppowt in A-MSDU
 * @fwag_wevew: fwag suppowt wevew
 * @fwag_max_num: max num of "open" MSDUs in the weceivew (in powew of 2)
 * @fwag_min_size: min fwag size (except wast fwag)
 * @pkt_ext: optionaw, exists accowding to PPE-pwesent bit in the HE-PHY capa
 * @bss_cowow: 11ax AP ID that is used in the HE SIG-A to mawk intew BSS fwame
 * @htc_twig_based_pkt_ext: defauwt PE in 4us units
 * @fwame_time_wts_th: HE duwation WTS thweshowd, in units of 32us
 * @wand_awwoc_ecwmin: wandom CWmin = 2**ECWmin-1
 * @wand_awwoc_ecwmax: wandom CWmax = 2**ECWmax-1
 * @punctuwe_mask: punctuwe mask fow EHT
 * @twig_based_txf: MU EDCA Pawametew set fow the twiggew based twaffic queues
 * @max_bssid_indicatow: indicatow of the max bssid suppowted on the associated
 *	bss
 * @bssid_index: index of the associated VAP
 * @ema_ap: AP suppowts enhanced Muwti BSSID advewtisement
 * @pwofiwe_pewiodicity: numbew of Beacon pewiods that awe needed to weceive the
 *	compwete VAPs info
 * @bssid_count: actuaw numbew of VAPs in the MuwtiBSS Set
 * @wesewved4: awignment
 */
stwuct iww_he_sta_context_cmd_v3 {
	u8 sta_id;
	u8 tid_wimit;
	u8 wesewved1;
	u8 wesewved2;
	__we32 fwags;

	/* The bewow fiewds awe set via Muwtipwe BSSID IE */
	u8 wef_bssid_addw[6];
	__we16 wesewved0;

	/* The bewow fiewds awe set via HE-capabiwities IE */
	__we32 htc_fwags;

	u8 fwag_fwags;
	u8 fwag_wevew;
	u8 fwag_max_num;
	u8 fwag_min_size;

	/* The bewow fiewds awe set via PPE thweshowds ewement */
	stwuct iww_he_pkt_ext_v2 pkt_ext;

	/* The bewow fiewds awe set via HE-Opewation IE */
	u8 bss_cowow;
	u8 htc_twig_based_pkt_ext;
	__we16 fwame_time_wts_th;

	/* Wandom access pawametew set (i.e. WAPS) */
	u8 wand_awwoc_ecwmin;
	u8 wand_awwoc_ecwmax;
	__we16 punctuwe_mask;

	/* The bewow fiewds awe set via MU EDCA pawametew set ewement */
	stwuct iww_he_backoff_conf twig_based_txf[AC_NUM];

	u8 max_bssid_indicatow;
	u8 bssid_index;
	u8 ema_ap;
	u8 pwofiwe_pewiodicity;
	u8 bssid_count;
	u8 wesewved4[3];
} __packed; /* STA_CONTEXT_DOT11AX_API_S_VEW_2 */

/**
 * stwuct iww_he_monitow_cmd - configuwe aiw sniffew fow HE
 * @bssid: the BSSID to sniff fow
 * @wesewved1: wesewved fow dwowd awignment
 * @aid: the AID to twack on fow HE MU
 * @wesewved2: wesewved fow futuwe use
 */
stwuct iww_he_monitow_cmd {
	u8 bssid[6];
	__we16 wesewved1;
	__we16 aid;
	u8 wesewved2[6];
} __packed; /* HE_AIW_SNIFFEW_CONFIG_CMD_API_S_VEW_1 */

#endif /* __iww_fw_api_mac_h__ */
