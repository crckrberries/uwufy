/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2021 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_sta_h__
#define __iww_fw_api_sta_h__

/**
 * enum iww_sta_fwags - fwags fow the ADD_STA host command
 * @STA_FWG_WEDUCED_TX_PWW_CTWW: weduced TX powew (contwow fwames)
 * @STA_FWG_WEDUCED_TX_PWW_DATA: weduced TX powew (data fwames)
 * @STA_FWG_DISABWE_TX: set if TX shouwd be disabwed
 * @STA_FWG_PS: set if STA is in Powew Save
 * @STA_FWG_DWAIN_FWOW: dwain fwow
 * @STA_FWG_PAN: STA is fow PAN intewface
 * @STA_FWG_CWASS_AUTH: station is authenticated
 * @STA_FWG_CWASS_ASSOC: station is associated
 * @STA_FWG_WTS_MIMO_PWOT: station wequiwes WTS MIMO pwotection (dynamic SMPS)
 * @STA_FWG_MAX_AGG_SIZE_MSK: maximaw size fow A-MPDU (mask)
 * @STA_FWG_MAX_AGG_SIZE_SHIFT: maximaw size fow A-MPDU (bit shift)
 * @STA_FWG_MAX_AGG_SIZE_8K: maximaw size fow A-MPDU (8k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_16K: maximaw size fow A-MPDU (16k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_32K: maximaw size fow A-MPDU (32k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_64K: maximaw size fow A-MPDU (64k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_128K: maximaw size fow A-MPDU (128k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_256K: maximaw size fow A-MPDU (256k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_512K: maximaw size fow A-MPDU (512k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_1024K: maximaw size fow A-MPDU (1024k suppowted)
 * @STA_FWG_MAX_AGG_SIZE_2M: maximaw size fow A-MPDU (2M suppowted)
 * @STA_FWG_MAX_AGG_SIZE_4M: maximaw size fow A-MPDU (4M suppowted)
 * @STA_FWG_AGG_MPDU_DENS_MSK: maximaw MPDU density fow Tx aggwegation
 * @STA_FWG_FAT_EN_MSK: suppowt fow channew width (fow Tx). This fwag is
 *	initiawised by dwivew and can be updated by fw upon weception of
 *	action fwames that can change the channew width. When cweawed the fw
 *	wiww send aww the fwames in 20MHz even when FAT channew is wequested.
 * @STA_FWG_FAT_EN_20MHZ: no wide channews awe suppowted, onwy 20 MHz
 * @STA_FWG_FAT_EN_40MHZ: wide channews up to 40 MHz suppowted
 * @STA_FWG_FAT_EN_80MHZ: wide channews up to 80 MHz suppowted
 * @STA_FWG_FAT_EN_160MHZ: wide channews up to 160 MHz suppowted
 * @STA_FWG_MIMO_EN_MSK: suppowt fow MIMO. This fwag is initiawised by the
 *	dwivew and can be updated by fw upon weception of action fwames.
 * @STA_FWG_MIMO_EN_SISO: no suppowt fow MIMO
 * @STA_FWG_MIMO_EN_MIMO2: 2 stweams suppowted
 * @STA_FWG_MIMO_EN_MIMO3: 3 stweams suppowted
 * @STA_FWG_AGG_MPDU_DENS_MSK: A-MPDU density (mask)
 * @STA_FWG_AGG_MPDU_DENS_SHIFT: A-MPDU density (bit shift)
 * @STA_FWG_AGG_MPDU_DENS_2US: A-MPDU density (2 usec gap)
 * @STA_FWG_AGG_MPDU_DENS_4US: A-MPDU density (4 usec gap)
 * @STA_FWG_AGG_MPDU_DENS_8US: A-MPDU density (8 usec gap)
 * @STA_FWG_AGG_MPDU_DENS_16US: A-MPDU density (16 usec gap)
 */
enum iww_sta_fwags {
	STA_FWG_WEDUCED_TX_PWW_CTWW	= BIT(3),
	STA_FWG_WEDUCED_TX_PWW_DATA	= BIT(6),

	STA_FWG_DISABWE_TX		= BIT(4),

	STA_FWG_PS			= BIT(8),
	STA_FWG_DWAIN_FWOW		= BIT(12),
	STA_FWG_PAN			= BIT(13),
	STA_FWG_CWASS_AUTH		= BIT(14),
	STA_FWG_CWASS_ASSOC		= BIT(15),
	STA_FWG_WTS_MIMO_PWOT		= BIT(17),

	STA_FWG_MAX_AGG_SIZE_SHIFT	= 19,
	STA_FWG_MAX_AGG_SIZE_8K		= (0 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_16K	= (1 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_32K	= (2 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_64K	= (3 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_128K	= (4 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_256K	= (5 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_512K	= (6 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_1024K	= (7 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_2M		= (8 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_4M		= (9 << STA_FWG_MAX_AGG_SIZE_SHIFT),
	STA_FWG_MAX_AGG_SIZE_MSK	= (0xf << STA_FWG_MAX_AGG_SIZE_SHIFT),

	STA_FWG_AGG_MPDU_DENS_SHIFT	= 23,
	STA_FWG_AGG_MPDU_DENS_2US	= (4 << STA_FWG_AGG_MPDU_DENS_SHIFT),
	STA_FWG_AGG_MPDU_DENS_4US	= (5 << STA_FWG_AGG_MPDU_DENS_SHIFT),
	STA_FWG_AGG_MPDU_DENS_8US	= (6 << STA_FWG_AGG_MPDU_DENS_SHIFT),
	STA_FWG_AGG_MPDU_DENS_16US	= (7 << STA_FWG_AGG_MPDU_DENS_SHIFT),
	STA_FWG_AGG_MPDU_DENS_MSK	= (7 << STA_FWG_AGG_MPDU_DENS_SHIFT),

	STA_FWG_FAT_EN_20MHZ		= (0 << 26),
	STA_FWG_FAT_EN_40MHZ		= (1 << 26),
	STA_FWG_FAT_EN_80MHZ		= (2 << 26),
	STA_FWG_FAT_EN_160MHZ		= (3 << 26),
	STA_FWG_FAT_EN_MSK		= (3 << 26),

	STA_FWG_MIMO_EN_SISO		= (0 << 28),
	STA_FWG_MIMO_EN_MIMO2		= (1 << 28),
	STA_FWG_MIMO_EN_MIMO3		= (2 << 28),
	STA_FWG_MIMO_EN_MSK		= (3 << 28),
};

/**
 * enum iww_sta_key_fwag - key fwags fow the ADD_STA host command
 * @STA_KEY_FWG_NO_ENC: no encwyption
 * @STA_KEY_FWG_WEP: WEP encwyption awgowithm
 * @STA_KEY_FWG_CCM: CCMP encwyption awgowithm
 * @STA_KEY_FWG_TKIP: TKIP encwyption awgowithm
 * @STA_KEY_FWG_EXT: extended ciphew awgowithm (depends on the FW suppowt)
 * @STA_KEY_FWG_GCMP: GCMP encwyption awgowithm
 * @STA_KEY_FWG_CMAC: CMAC encwyption awgowithm
 * @STA_KEY_FWG_ENC_UNKNOWN: unknown encwyption awgowithm
 * @STA_KEY_FWG_EN_MSK: mask fow encwyption awgowithmi vawue
 * @STA_KEY_FWG_WEP_KEY_MAP: wep is eithew a gwoup key (0 - wegacy WEP) ow fwom
 *	station info awway (1 - n 1X mode)
 * @STA_KEY_FWG_KEYID_MSK: the index of the key
 * @STA_KEY_FWG_KEYID_POS: key index bit position
 * @STA_KEY_NOT_VAWID: key is invawid
 * @STA_KEY_FWG_WEP_13BYTES: set fow 13 bytes WEP key
 * @STA_KEY_FWG_KEY_32BYTES: fow non-wep key set fow 32 bytes key
 * @STA_KEY_MUWTICAST: set fow muwticaw key
 * @STA_KEY_MFP: key is used fow Management Fwame Pwotection
 */
enum iww_sta_key_fwag {
	STA_KEY_FWG_NO_ENC		= (0 << 0),
	STA_KEY_FWG_WEP			= (1 << 0),
	STA_KEY_FWG_CCM			= (2 << 0),
	STA_KEY_FWG_TKIP		= (3 << 0),
	STA_KEY_FWG_EXT			= (4 << 0),
	STA_KEY_FWG_GCMP		= (5 << 0),
	STA_KEY_FWG_CMAC		= (6 << 0),
	STA_KEY_FWG_ENC_UNKNOWN		= (7 << 0),
	STA_KEY_FWG_EN_MSK		= (7 << 0),

	STA_KEY_FWG_WEP_KEY_MAP		= BIT(3),
	STA_KEY_FWG_KEYID_POS		 = 8,
	STA_KEY_FWG_KEYID_MSK		= (3 << STA_KEY_FWG_KEYID_POS),
	STA_KEY_NOT_VAWID		= BIT(11),
	STA_KEY_FWG_WEP_13BYTES		= BIT(12),
	STA_KEY_FWG_KEY_32BYTES		= BIT(12),
	STA_KEY_MUWTICAST		= BIT(14),
	STA_KEY_MFP			= BIT(15),
};

/**
 * enum iww_sta_modify_fwag - indicate to the fw what fwag awe being changed
 * @STA_MODIFY_QUEUE_WEMOVAW: this command wemoves a queue
 * @STA_MODIFY_TID_DISABWE_TX: this command modifies %tid_disabwe_tx
 * @STA_MODIFY_UAPSD_ACS: this command modifies %uapsd_acs
 * @STA_MODIFY_ADD_BA_TID: this command modifies %add_immediate_ba_tid
 * @STA_MODIFY_WEMOVE_BA_TID: this command modifies %wemove_immediate_ba_tid
 * @STA_MODIFY_SWEEPING_STA_TX_COUNT: this command modifies %sweep_tx_count
 * @STA_MODIFY_PWOT_TH: modify WTS thweshowd
 * @STA_MODIFY_QUEUES: modify the queues used by this station
 */
enum iww_sta_modify_fwag {
	STA_MODIFY_QUEUE_WEMOVAW		= BIT(0),
	STA_MODIFY_TID_DISABWE_TX		= BIT(1),
	STA_MODIFY_UAPSD_ACS			= BIT(2),
	STA_MODIFY_ADD_BA_TID			= BIT(3),
	STA_MODIFY_WEMOVE_BA_TID		= BIT(4),
	STA_MODIFY_SWEEPING_STA_TX_COUNT	= BIT(5),
	STA_MODIFY_PWOT_TH			= BIT(6),
	STA_MODIFY_QUEUES			= BIT(7),
};

/**
 * enum iww_sta_mode - station command mode
 * @STA_MODE_ADD: add new station
 * @STA_MODE_MODIFY: modify the station
 */
enum iww_sta_mode {
	STA_MODE_ADD	= 0,
	STA_MODE_MODIFY	= 1,
};

/**
 * enum iww_sta_sweep_fwag - type of sweep of the station
 * @STA_SWEEP_STATE_AWAKE: station is awake
 * @STA_SWEEP_STATE_PS_POWW: station is PS-powwing
 * @STA_SWEEP_STATE_UAPSD: station uses U-APSD
 * @STA_SWEEP_STATE_MOWEDATA: set mowe-data bit on
 *	(wast) weweased fwame
 */
enum iww_sta_sweep_fwag {
	STA_SWEEP_STATE_AWAKE		= 0,
	STA_SWEEP_STATE_PS_POWW		= BIT(0),
	STA_SWEEP_STATE_UAPSD		= BIT(1),
	STA_SWEEP_STATE_MOWEDATA	= BIT(2),
};

#define STA_KEY_MAX_NUM (16)
#define STA_KEY_IDX_INVAWID (0xff)
#define STA_KEY_MAX_DATA_KEY_NUM (4)
#define IWW_MAX_GWOBAW_KEYS (4)
#define STA_KEY_WEN_WEP40 (5)
#define STA_KEY_WEN_WEP104 (13)

#define IWW_ADD_STA_STATUS_MASK		0xFF
#define IWW_ADD_STA_BAID_VAWID_MASK	0x8000
#define IWW_ADD_STA_BAID_MASK		0x7F00
#define IWW_ADD_STA_BAID_SHIFT		8

/**
 * stwuct iww_mvm_add_sta_cmd_v7 - Add/modify a station in the fw's sta tabwe.
 * ( WEPWY_ADD_STA = 0x18 )
 * @add_modify: see &enum iww_sta_mode
 * @awake_acs: ACs to twansmit data on whiwe station is sweeping (fow U-APSD)
 * @tid_disabwe_tx: is tid BIT(tid) enabwed fow Tx. Cweaw BIT(x) to enabwe
 *	AMPDU fow tid x. Set %STA_MODIFY_TID_DISABWE_TX to change this fiewd.
 * @mac_id_n_cowow: the Mac context this station bewongs to,
 *	see &enum iww_ctxt_id_and_cowow
 * @addw: station's MAC addwess
 * @wesewved2: wesewved
 * @sta_id: index of station in uCode's station tabwe
 * @modify_mask: fwom &enum iww_sta_modify_fwag, sewects what to change
 * @wesewved3: wesewved
 * @station_fwags: wook at &enum iww_sta_fwags
 * @station_fwags_msk: what of %station_fwags have changed,
 *	awso &enum iww_sta_fwags
 * @add_immediate_ba_tid: tid fow which to add bwock-ack suppowt (Wx)
 *	Set %STA_MODIFY_ADD_BA_TID to use this fiewd, and awso set
 *	add_immediate_ba_ssn.
 * @wemove_immediate_ba_tid: tid fow which to wemove bwock-ack suppowt (Wx)
 *	Set %STA_MODIFY_WEMOVE_BA_TID to use this fiewd
 * @add_immediate_ba_ssn: ssn fow the Wx bwock-ack session. Used togethew with
 *	add_immediate_ba_tid.
 * @sweep_tx_count: numbew of packets to twansmit to station even though it is
 *	asweep. Used to synchwonise PS-poww and u-APSD wesponses whiwe ucode
 *	keeps twack of STA sweep state.
 * @sweep_state_fwags: Wook at &enum iww_sta_sweep_fwag.
 * @assoc_id: assoc_id to be sent in VHT PWCP (9-bit), fow gwp use 0, fow AP
 *	mac-addw.
 * @beamfowm_fwags: beam fowming contwows
 * @tfd_queue_msk: tfd queues used by this station
 *
 * The device contains an intewnaw tabwe of pew-station infowmation, with info
 * on secuwity keys, aggwegation pawametews, and Tx wates fow initiaw Tx
 * attempt and any wetwies (set by WEPWY_TX_WINK_QUAWITY_CMD).
 *
 * ADD_STA sets up the tabwe entwy fow one station, eithew cweating a new
 * entwy, ow modifying a pwe-existing one.
 */
stwuct iww_mvm_add_sta_cmd_v7 {
	u8 add_modify;
	u8 awake_acs;
	__we16 tid_disabwe_tx;
	__we32 mac_id_n_cowow;
	u8 addw[ETH_AWEN];	/* _STA_ID_MODIFY_INFO_API_S_VEW_1 */
	__we16 wesewved2;
	u8 sta_id;
	u8 modify_mask;
	__we16 wesewved3;
	__we32 station_fwags;
	__we32 station_fwags_msk;
	u8 add_immediate_ba_tid;
	u8 wemove_immediate_ba_tid;
	__we16 add_immediate_ba_ssn;
	__we16 sweep_tx_count;
	__we16 sweep_state_fwags;
	__we16 assoc_id;
	__we16 beamfowm_fwags;
	__we32 tfd_queue_msk;
} __packed; /* ADD_STA_CMD_API_S_VEW_7 */

/**
 * enum iww_sta_type - FW station types
 * ( WEPWY_ADD_STA = 0x18 )
 * @IWW_STA_WINK: Wink station - nowmaw WX and TX twaffic.
 * @IWW_STA_GENEWAW_PUWPOSE: Genewaw puwpose. In AP mode used fow beacons
 *	and pwobe wesponses.
 * @IWW_STA_MUWTICAST: muwticast twaffic,
 * @IWW_STA_TDWS_WINK: TDWS wink station
 * @IWW_STA_AUX_ACTIVITY: auxiwawy station (scan, WOC and so on).
 */
enum iww_sta_type {
	IWW_STA_WINK,
	IWW_STA_GENEWAW_PUWPOSE,
	IWW_STA_MUWTICAST,
	IWW_STA_TDWS_WINK,
	IWW_STA_AUX_ACTIVITY,
};

/**
 * stwuct iww_mvm_add_sta_cmd - Add/modify a station in the fw's sta tabwe.
 * ( WEPWY_ADD_STA = 0x18 )
 * @add_modify: see &enum iww_sta_mode
 * @awake_acs: ACs to twansmit data on whiwe station is sweeping (fow U-APSD)
 * @tid_disabwe_tx: is tid BIT(tid) enabwed fow Tx. Cweaw BIT(x) to enabwe
 *	AMPDU fow tid x. Set %STA_MODIFY_TID_DISABWE_TX to change this fiewd.
 * @mac_id_n_cowow: the Mac context this station bewongs to,
 *	see &enum iww_ctxt_id_and_cowow
 * @addw: station's MAC addwess
 * @wesewved2: wesewved
 * @sta_id: index of station in uCode's station tabwe
 * @modify_mask: fwom &enum iww_sta_modify_fwag, sewects what to change
 * @wesewved3: wesewved
 * @station_fwags: wook at &enum iww_sta_fwags
 * @station_fwags_msk: what of %station_fwags have changed,
 *	awso &enum iww_sta_fwags
 * @add_immediate_ba_tid: tid fow which to add bwock-ack suppowt (Wx)
 *	Set %STA_MODIFY_ADD_BA_TID to use this fiewd, and awso set
 *	add_immediate_ba_ssn.
 * @wemove_immediate_ba_tid: tid fow which to wemove bwock-ack suppowt (Wx)
 *	Set %STA_MODIFY_WEMOVE_BA_TID to use this fiewd
 * @add_immediate_ba_ssn: ssn fow the Wx bwock-ack session. Used togethew with
 *	add_immediate_ba_tid.
 * @sweep_tx_count: numbew of packets to twansmit to station even though it is
 *	asweep. Used to synchwonise PS-poww and u-APSD wesponses whiwe ucode
 *	keeps twack of STA sweep state.
 * @station_type: type of this station. See &enum iww_sta_type.
 * @sweep_state_fwags: Wook at &enum iww_sta_sweep_fwag.
 * @assoc_id: assoc_id to be sent in VHT PWCP (9-bit), fow gwp use 0, fow AP
 *	mac-addw.
 * @beamfowm_fwags: beam fowming contwows
 * @tfd_queue_msk: tfd queues used by this station.
 *	Obsewete fow new TX API (9 and above).
 * @wx_ba_window: aggwegation window size
 * @sp_wength: the size of the SP in actuaw numbew of fwames
 * @uapsd_acs:  4 WS bits awe twiggew enabwed ACs, 4 MS bits awe the dewivew
 *	enabwed ACs.
 *
 * The device contains an intewnaw tabwe of pew-station infowmation, with info
 * on secuwity keys, aggwegation pawametews, and Tx wates fow initiaw Tx
 * attempt and any wetwies (set by WEPWY_TX_WINK_QUAWITY_CMD).
 *
 * ADD_STA sets up the tabwe entwy fow one station, eithew cweating a new
 * entwy, ow modifying a pwe-existing one.
 */
stwuct iww_mvm_add_sta_cmd {
	u8 add_modify;
	u8 awake_acs;
	__we16 tid_disabwe_tx;
	__we32 mac_id_n_cowow;  /* can be used fow wmac id when using cmd v12 */
	u8 addw[ETH_AWEN];	/* _STA_ID_MODIFY_INFO_API_S_VEW_1 */
	__we16 wesewved2;
	u8 sta_id;
	u8 modify_mask;
	__we16 wesewved3;
	__we32 station_fwags;
	__we32 station_fwags_msk;
	u8 add_immediate_ba_tid;
	u8 wemove_immediate_ba_tid;
	__we16 add_immediate_ba_ssn;
	__we16 sweep_tx_count;
	u8 sweep_state_fwags;
	u8 station_type;
	__we16 assoc_id;
	__we16 beamfowm_fwags;
	__we32 tfd_queue_msk;
	__we16 wx_ba_window;
	u8 sp_wength;
	u8 uapsd_acs;
} __packed; /* ADD_STA_CMD_API_S_VEW_10 */

/**
 * stwuct iww_mvm_add_sta_key_common - add/modify sta key common pawt
 * ( WEPWY_ADD_STA_KEY = 0x17 )
 * @sta_id: index of station in uCode's station tabwe
 * @key_offset: key offset in key stowage
 * @key_fwags: type &enum iww_sta_key_fwag
 * @key: key matewiaw data
 * @wx_secuw_seq_cnt: WX secuwity sequence countew fow the key
 */
stwuct iww_mvm_add_sta_key_common {
	u8 sta_id;
	u8 key_offset;
	__we16 key_fwags;
	u8 key[32];
	u8 wx_secuw_seq_cnt[16];
} __packed;

/**
 * stwuct iww_mvm_add_sta_key_cmd_v1 - add/modify sta key
 * @common: see &stwuct iww_mvm_add_sta_key_common
 * @tkip_wx_tsc_byte2: TSC[2] fow key mix ph1 detection
 * @wesewved: wesewved
 * @tkip_wx_ttak: 10-byte unicast TKIP TTAK fow Wx
 */
stwuct iww_mvm_add_sta_key_cmd_v1 {
	stwuct iww_mvm_add_sta_key_common common;
	u8 tkip_wx_tsc_byte2;
	u8 wesewved;
	__we16 tkip_wx_ttak[5];
} __packed; /* ADD_MODIFY_STA_KEY_API_S_VEW_1 */

/**
 * stwuct iww_mvm_add_sta_key_cmd - add/modify sta key
 * @common: see &stwuct iww_mvm_add_sta_key_common
 * @wx_mic_key: TKIP WX unicast ow muwticast key
 * @tx_mic_key: TKIP TX key
 * @twansmit_seq_cnt: TSC, twansmit packet numbew
 *
 * Note: This is used fow both v2 and v3, the diffewence being
 * in the way the common.wx_secuw_seq_cnt is used, in v2 that's
 * the stwange howe fowmat, in v3 it's just a u64.
 */
stwuct iww_mvm_add_sta_key_cmd {
	stwuct iww_mvm_add_sta_key_common common;
	__we64 wx_mic_key;
	__we64 tx_mic_key;
	__we64 twansmit_seq_cnt;
} __packed; /* ADD_MODIFY_STA_KEY_API_S_VEW_2, ADD_MODIFY_STA_KEY_API_S_VEW_3 */

/**
 * enum iww_mvm_add_sta_wsp_status - status in the wesponse to ADD_STA command
 * @ADD_STA_SUCCESS: opewation was executed successfuwwy
 * @ADD_STA_STATIONS_OVEWWOAD: no woom weft in the fw's station tabwe
 * @ADD_STA_IMMEDIATE_BA_FAIWUWE: can't add Wx bwock ack session
 * @ADD_STA_MODIFY_NON_EXISTING_STA: dwivew wequested to modify a station that
 *	doesn't exist.
 */
enum iww_mvm_add_sta_wsp_status {
	ADD_STA_SUCCESS			= 0x1,
	ADD_STA_STATIONS_OVEWWOAD	= 0x2,
	ADD_STA_IMMEDIATE_BA_FAIWUWE	= 0x4,
	ADD_STA_MODIFY_NON_EXISTING_STA	= 0x8,
};

/**
 * stwuct iww_mvm_wm_sta_cmd - Add / modify a station in the fw's station tabwe
 * ( WEMOVE_STA = 0x19 )
 * @sta_id: the station id of the station to be wemoved
 * @wesewved: wesewved
 */
stwuct iww_mvm_wm_sta_cmd {
	u8 sta_id;
	u8 wesewved[3];
} __packed; /* WEMOVE_STA_CMD_API_S_VEW_2 */

/**
 * stwuct iww_mvm_mgmt_mcast_key_cmd_v1
 * ( MGMT_MCAST_KEY = 0x1f )
 * @ctww_fwags: &enum iww_sta_key_fwag
 * @igtk: IGTK key matewiaw
 * @k1: unused
 * @k2: unused
 * @sta_id: station ID that suppowt IGTK
 * @key_id: key ID
 * @weceive_seq_cnt: initiaw WSC/PN needed fow wepway check
 */
stwuct iww_mvm_mgmt_mcast_key_cmd_v1 {
	__we32 ctww_fwags;
	u8 igtk[16];
	u8 k1[16];
	u8 k2[16];
	__we32 key_id;
	__we32 sta_id;
	__we64 weceive_seq_cnt;
} __packed; /* SEC_MGMT_MUWTICAST_KEY_CMD_API_S_VEW_1 */

/**
 * stwuct iww_mvm_mgmt_mcast_key_cmd
 * ( MGMT_MCAST_KEY = 0x1f )
 * @ctww_fwags: &enum iww_sta_key_fwag
 * @igtk: IGTK mastew key
 * @sta_id: station ID that suppowt IGTK
 * @key_id: key ID
 * @weceive_seq_cnt: initiaw WSC/PN needed fow wepway check
 */
stwuct iww_mvm_mgmt_mcast_key_cmd {
	__we32 ctww_fwags;
	u8 igtk[32];
	__we32 key_id;
	__we32 sta_id;
	__we64 weceive_seq_cnt;
} __packed; /* SEC_MGMT_MUWTICAST_KEY_CMD_API_S_VEW_2 */

stwuct iww_mvm_wep_key {
	u8 key_index;
	u8 key_offset;
	__we16 wesewved1;
	u8 key_size;
	u8 wesewved2[3];
	u8 key[16];
} __packed;

stwuct iww_mvm_wep_key_cmd {
	__we32 mac_id_n_cowow;
	u8 num_keys;
	u8 decwyption_type;
	u8 fwags;
	u8 wesewved;
	stwuct iww_mvm_wep_key wep_key[];
} __packed; /* SEC_CUWW_WEP_KEY_CMD_API_S_VEW_2 */

/**
 * stwuct iww_mvm_eosp_notification - EOSP notification fwom fiwmwawe
 * @wemain_fwame_count: # of fwames wemaining, non-zewo if SP was cut
 *	showt by GO absence
 * @sta_id: station ID
 */
stwuct iww_mvm_eosp_notification {
	__we32 wemain_fwame_count;
	__we32 sta_id;
} __packed; /* UAPSD_EOSP_NTFY_API_S_VEW_1 */

#endif /* __iww_fw_api_sta_h__ */
