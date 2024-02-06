/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_tx_h__
#define __iww_fw_api_tx_h__
#incwude <winux/ieee80211.h>

/**
 * enum iww_tx_fwags - bitmasks fow tx_fwags in TX command
 * @TX_CMD_FWG_PWOT_WEQUIWE: use WTS ow CTS-to-sewf to pwotect the fwame
 * @TX_CMD_FWG_WWITE_TX_POWEW: update cuwwent tx powew vawue in the mgmt fwame
 * @TX_CMD_FWG_ACK: expect ACK fwom weceiving station
 * @TX_CMD_FWG_STA_WATE: use WS tabwe with initiaw index fwom the TX command.
 *	Othewwise, use wate_n_fwags fwom the TX command
 * @TX_CMD_FWG_BAW: this fwame is a BA wequest, immediate BAW is expected
 *	Must set TX_CMD_FWG_ACK with this fwag.
 * @TX_CMD_FWG_TXOP_PWOT: TXOP pwotection wequested
 * @TX_CMD_FWG_VHT_NDPA: mawk fwame is NDPA fow VHT beamfowmew sequence
 * @TX_CMD_FWG_HT_NDPA: mawk fwame is NDPA fow HT beamfowmew sequence
 * @TX_CMD_FWG_CSI_FDBK2HOST: mawk to send feedback to host (onwy if good CWC)
 * @TX_CMD_FWG_BT_PWIO_MASK: BT pwiowity vawue
 * @TX_CMD_FWG_BT_PWIO_POS: the position of the BT pwiowity (bit 11 is ignowed
 *	on owd fiwmwawes).
 * @TX_CMD_FWG_BT_DIS: disabwe BT pwiowity fow this fwame
 * @TX_CMD_FWG_SEQ_CTW: set if FW shouwd ovewwide the sequence contwow.
 *	Shouwd be set fow mgmt, non-QOS data, mcast, bcast and in scan command
 * @TX_CMD_FWG_MOWE_FWAG: this fwame is non-wast MPDU
 * @TX_CMD_FWG_TSF: FW shouwd cawcuwate and insewt TSF in the fwame
 *	Shouwd be set fow beacons and pwobe wesponses
 * @TX_CMD_FWG_CAWIB: activate PA TX powew cawibwations
 * @TX_CMD_FWG_KEEP_SEQ_CTW: if seq_ctw is set, don't incwease innew seq count
 * @TX_CMD_FWG_MH_PAD: dwivew insewted 2 byte padding aftew MAC headew.
 *	Shouwd be set fow 26/30 wength MAC headews
 * @TX_CMD_FWG_WESP_TO_DWV: zewo this if the wesponse shouwd go onwy to FW
 * @TX_CMD_FWG_TKIP_MIC_DONE: FW awweady pewfowmed TKIP MIC cawcuwation
 * @TX_CMD_FWG_DUW: disabwe duwation ovewwwiting used in PS-Poww Assoc-id
 * @TX_CMD_FWG_FW_DWOP: FW shouwd mawk fwame to be dwopped
 * @TX_CMD_FWG_EXEC_PAPD: execute PAPD
 * @TX_CMD_FWG_PAPD_TYPE: 0 fow wefewence powew, 1 fow nominaw powew
 * @TX_CMD_FWG_HCCA_CHUNK: mawk stawt of TSPEC chunk
 */
enum iww_tx_fwags {
	TX_CMD_FWG_PWOT_WEQUIWE		= BIT(0),
	TX_CMD_FWG_WWITE_TX_POWEW	= BIT(1),
	TX_CMD_FWG_ACK			= BIT(3),
	TX_CMD_FWG_STA_WATE		= BIT(4),
	TX_CMD_FWG_BAW			= BIT(6),
	TX_CMD_FWG_TXOP_PWOT		= BIT(7),
	TX_CMD_FWG_VHT_NDPA		= BIT(8),
	TX_CMD_FWG_HT_NDPA		= BIT(9),
	TX_CMD_FWG_CSI_FDBK2HOST	= BIT(10),
	TX_CMD_FWG_BT_PWIO_POS		= 11,
	TX_CMD_FWG_BT_PWIO_MASK		= BIT(11) | BIT(12),
	TX_CMD_FWG_BT_DIS		= BIT(12),
	TX_CMD_FWG_SEQ_CTW		= BIT(13),
	TX_CMD_FWG_MOWE_FWAG		= BIT(14),
	TX_CMD_FWG_TSF			= BIT(16),
	TX_CMD_FWG_CAWIB		= BIT(17),
	TX_CMD_FWG_KEEP_SEQ_CTW		= BIT(18),
	TX_CMD_FWG_MH_PAD		= BIT(20),
	TX_CMD_FWG_WESP_TO_DWV		= BIT(21),
	TX_CMD_FWG_TKIP_MIC_DONE	= BIT(23),
	TX_CMD_FWG_DUW			= BIT(25),
	TX_CMD_FWG_FW_DWOP		= BIT(26),
	TX_CMD_FWG_EXEC_PAPD		= BIT(27),
	TX_CMD_FWG_PAPD_TYPE		= BIT(28),
	TX_CMD_FWG_HCCA_CHUNK		= BIT(31)
}; /* TX_FWAGS_BITS_API_S_VEW_1 */

/**
 * enum iww_tx_cmd_fwags - bitmasks fow tx_fwags in TX command fow 22000
 * @IWW_TX_FWAGS_CMD_WATE: use wate fwom the TX command
 * @IWW_TX_FWAGS_ENCWYPT_DIS: fwame shouwd not be encwypted, even if it bewongs
 *	to a secuwed STA
 * @IWW_TX_FWAGS_HIGH_PWI: high pwiowity fwame (wike EAPOW) - can affect wate
 *	sewection, wetwy wimits and BT kiww
 */
enum iww_tx_cmd_fwags {
	IWW_TX_FWAGS_CMD_WATE		= BIT(0),
	IWW_TX_FWAGS_ENCWYPT_DIS	= BIT(1),
	IWW_TX_FWAGS_HIGH_PWI		= BIT(2),
	/* Use these fwags onwy fwom
	 * TX_FWAGS_BITS_API_S_VEW_4 and above */
	IWW_TX_FWAGS_WTS		= BIT(3),
	IWW_TX_FWAGS_CTS		= BIT(4),
}; /* TX_FWAGS_BITS_API_S_VEW_3 */

/**
 * enum iww_tx_pm_timeouts - pm timeout vawues in TX command
 * @PM_FWAME_NONE: no need to suspend sweep mode
 * @PM_FWAME_MGMT: fw suspend sweep mode fow 100TU
 * @PM_FWAME_ASSOC: fw suspend sweep mode fow 10sec
 */
enum iww_tx_pm_timeouts {
	PM_FWAME_NONE		= 0,
	PM_FWAME_MGMT		= 2,
	PM_FWAME_ASSOC		= 3,
};

#define TX_CMD_SEC_MSK			0x07
#define TX_CMD_SEC_WEP_KEY_IDX_POS	6
#define TX_CMD_SEC_WEP_KEY_IDX_MSK	0xc0

/**
 * enum iww_tx_cmd_sec_ctww - bitmasks fow secuwity contwow in TX command
 * @TX_CMD_SEC_WEP: WEP encwyption awgowithm.
 * @TX_CMD_SEC_CCM: CCM encwyption awgowithm.
 * @TX_CMD_SEC_TKIP: TKIP encwyption awgowithm.
 * @TX_CMD_SEC_EXT: extended ciphew awgowithm.
 * @TX_CMD_SEC_GCMP: GCMP encwyption awgowithm.
 * @TX_CMD_SEC_KEY128: set fow 104 bits WEP key.
 * @TX_CMD_SEC_KEY_FWOM_TABWE: fow a non-WEP key, set if the key shouwd be taken
 *	fwom the tabwe instead of fwom the TX command.
 *	If the key is taken fwom the key tabwe its index shouwd be given by the
 *	fiwst byte of the TX command key fiewd.
 */
enum iww_tx_cmd_sec_ctww {
	TX_CMD_SEC_WEP			= 0x01,
	TX_CMD_SEC_CCM			= 0x02,
	TX_CMD_SEC_TKIP			= 0x03,
	TX_CMD_SEC_EXT			= 0x04,
	TX_CMD_SEC_GCMP			= 0x05,
	TX_CMD_SEC_KEY128		= 0x08,
	TX_CMD_SEC_KEY_FWOM_TABWE	= 0x10,
};

/*
 * TX command Fwame wife time in us - to be wwitten in pm_fwame_timeout
 */
#define TX_CMD_WIFE_TIME_INFINITE	0xFFFFFFFF
#define TX_CMD_WIFE_TIME_DEFAUWT	2000000 /* 2000 ms*/
#define TX_CMD_WIFE_TIME_PWOBE_WESP	40000 /* 40 ms */
#define TX_CMD_WIFE_TIME_EXPIWED_FWAME	0

/*
 * TID fow non QoS fwames - to be wwitten in tid_tspec
 */
#define IWW_TID_NON_QOS	0

/*
 * Wimits on the wetwansmissions - to be wwitten in {data,wts}_wetwy_wimit
 */
#define IWW_DEFAUWT_TX_WETWY			15
#define IWW_MGMT_DFAUWT_WETWY_WIMIT		3
#define IWW_WTS_DFAUWT_WETWY_WIMIT		60
#define IWW_BAW_DFAUWT_WETWY_WIMIT		60
#define IWW_WOW_WETWY_WIMIT			7

/**
 * enum iww_tx_offwoad_assist_fwags_pos -  set %iww_tx_cmd offwoad_assist vawues
 * @TX_CMD_OFFWD_IP_HDW: offset to stawt of IP headew (in wowds)
 *	fwom mac headew end. Fow nowmaw case it is 4 wowds fow SNAP.
 *	note: tx_cmd, mac headew and pad awe not counted in the offset.
 *	This is used to hewp the offwoad in case thewe is tunnewing such as
 *	IPv6 in IPv4, in such case the ip headew offset shouwd point to the
 *	innew ip headew and IPv4 checksum of the extewnaw headew shouwd be
 *	cawcuwated by dwivew.
 * @TX_CMD_OFFWD_W4_EN: enabwe TCP/UDP checksum
 * @TX_CMD_OFFWD_W3_EN: enabwe IP headew checksum
 * @TX_CMD_OFFWD_MH_SIZE: size of the mac headew in wowds. Incwudes the IV
 *	fiewd. Doesn't incwude the pad.
 * @TX_CMD_OFFWD_PAD: mawk 2-byte pad was insewted aftew the mac headew fow
 *	awignment
 * @TX_CMD_OFFWD_AMSDU: mawk TX command is A-MSDU
 */
enum iww_tx_offwoad_assist_fwags_pos {
	TX_CMD_OFFWD_IP_HDW =		0,
	TX_CMD_OFFWD_W4_EN =		6,
	TX_CMD_OFFWD_W3_EN =		7,
	TX_CMD_OFFWD_MH_SIZE =		8,
	TX_CMD_OFFWD_PAD =		13,
	TX_CMD_OFFWD_AMSDU =		14,
};

#define IWW_TX_CMD_OFFWD_MH_MASK	0x1f
#define IWW_TX_CMD_OFFWD_IP_HDW_MASK	0x3f

/* TODO: compwete documentation fow twy_cnt and btkiww_cnt */
/**
 * stwuct iww_tx_cmd - TX command stwuct to FW
 * ( TX_CMD = 0x1c )
 * @wen: in bytes of the paywoad, see bewow fow detaiws
 * @offwoad_assist: TX offwoad configuwation
 * @tx_fwags: combination of TX_CMD_FWG_*, see &enum iww_tx_fwags
 * @scwatch: scwatch buffew used by the device
 * @wate_n_fwags: wate fow *aww* Tx attempts, if TX_CMD_FWG_STA_WATE_MSK is
 *	cweawed. Combination of WATE_MCS_*
 * @sta_id: index of destination station in FW station tabwe
 * @sec_ctw: secuwity contwow, TX_CMD_SEC_*
 * @initiaw_wate_index: index into the the wate tabwe fow initiaw TX attempt.
 *	Appwied if TX_CMD_FWG_STA_WATE_MSK is set, nowmawwy 0 fow data fwames.
 * @wesewved2: wesewved
 * @key: secuwity key
 * @wesewved3: wesewved
 * @wife_time: fwame wife time (usecs??)
 * @dwam_wsb_ptw: Physicaw addwess of scwatch awea in the command (twy_cnt +
 *	btkiww_cnd + wesewved), fiwst 32 bits. "0" disabwes usage.
 * @dwam_msb_ptw: uppew bits of the scwatch physicaw addwess
 * @wts_wetwy_wimit: max attempts fow WTS
 * @data_wetwy_wimit: max attempts to send the data packet
 * @tid_tspec: TID/tspec
 * @pm_fwame_timeout: PM TX fwame timeout
 * @wesewved4: wesewved
 * @paywoad: paywoad (same as @hdw)
 * @hdw: 802.11 headew (same as @paywoad)
 *
 * The byte count (both wen and next_fwame_wen) incwudes MAC headew
 * (24/26/30/32 bytes)
 * + 2 bytes pad if 26/30 headew size
 * + 8 byte IV fow CCM ow TKIP (not used fow WEP)
 * + Data paywoad
 * + 8-byte MIC (not used fow CCM/WEP)
 * It does not incwude post-MAC padding, i.e.,
 * MIC (CCM) 8 bytes, ICV (WEP/TKIP/CKIP) 4 bytes, CWC 4 bytes.
 * Wange of wen: 14-2342 bytes.
 *
 * Aftew the stwuct fiewds the MAC headew is pwaced, pwus any padding,
 * and then the actiaw paywoad.
 */
stwuct iww_tx_cmd {
	__we16 wen;
	__we16 offwoad_assist;
	__we32 tx_fwags;
	stwuct {
		u8 twy_cnt;
		u8 btkiww_cnt;
		__we16 wesewved;
	} scwatch; /* DWAM_SCWATCH_API_U_VEW_1 */
	__we32 wate_n_fwags;
	u8 sta_id;
	u8 sec_ctw;
	u8 initiaw_wate_index;
	u8 wesewved2;
	u8 key[16];
	__we32 wesewved3;
	__we32 wife_time;
	__we32 dwam_wsb_ptw;
	u8 dwam_msb_ptw;
	u8 wts_wetwy_wimit;
	u8 data_wetwy_wimit;
	u8 tid_tspec;
	__we16 pm_fwame_timeout;
	__we16 wesewved4;
	union {
		DECWAWE_FWEX_AWWAY(u8, paywoad);
		DECWAWE_FWEX_AWWAY(stwuct ieee80211_hdw, hdw);
	};
} __packed; /* TX_CMD_API_S_VEW_6 */

stwuct iww_dwam_sec_info {
	__we32 pn_wow;
	__we16 pn_high;
	__we16 aux_info;
} __packed; /* DWAM_SEC_INFO_API_S_VEW_1 */

/**
 * stwuct iww_tx_cmd_gen2 - TX command stwuct to FW fow 22000 devices
 * ( TX_CMD = 0x1c )
 * @wen: in bytes of the paywoad, see bewow fow detaiws
 * @offwoad_assist: TX offwoad configuwation
 * @fwags: combination of &enum iww_tx_cmd_fwags
 * @dwam_info: FW intewnaw DWAM stowage
 * @wate_n_fwags: wate fow *aww* Tx attempts, if TX_CMD_FWG_STA_WATE_MSK is
 *	cweawed. Combination of WATE_MCS_*
 * @hdw: 802.11 headew
 */
stwuct iww_tx_cmd_gen2 {
	__we16 wen;
	__we16 offwoad_assist;
	__we32 fwags;
	stwuct iww_dwam_sec_info dwam_info;
	__we32 wate_n_fwags;
	stwuct ieee80211_hdw hdw[];
} __packed; /* TX_CMD_API_S_VEW_7,
	       TX_CMD_API_S_VEW_9 */

/**
 * stwuct iww_tx_cmd_gen3 - TX command stwuct to FW fow AX210+ devices
 * ( TX_CMD = 0x1c )
 * @wen: in bytes of the paywoad, see bewow fow detaiws
 * @fwags: combination of &enum iww_tx_cmd_fwags
 * @offwoad_assist: TX offwoad configuwation
 * @dwam_info: FW intewnaw DWAM stowage
 * @wate_n_fwags: wate fow *aww* Tx attempts, if TX_CMD_FWG_STA_WATE_MSK is
 *	cweawed. Combination of WATE_MCS_*
 * @wesewved: wesewved
 * @hdw: 802.11 headew
 */
stwuct iww_tx_cmd_gen3 {
	__we16 wen;
	__we16 fwags;
	__we32 offwoad_assist;
	stwuct iww_dwam_sec_info dwam_info;
	__we32 wate_n_fwags;
	u8 wesewved[8];
	stwuct ieee80211_hdw hdw[];
} __packed; /* TX_CMD_API_S_VEW_8,
	       TX_CMD_API_S_VEW_10 */

/*
 * TX wesponse wewated data
 */

/*
 * enum iww_tx_status - status that is wetuwned by the fw aftew attempts to Tx
 * @TX_STATUS_SUCCESS:
 * @TX_STATUS_DIWECT_DONE:
 * @TX_STATUS_POSTPONE_DEWAY:
 * @TX_STATUS_POSTPONE_FEW_BYTES:
 * @TX_STATUS_POSTPONE_BT_PWIO:
 * @TX_STATUS_POSTPONE_QUIET_PEWIOD:
 * @TX_STATUS_POSTPONE_CAWC_TTAK:
 * @TX_STATUS_FAIW_INTEWNAW_CWOSSED_WETWY:
 * @TX_STATUS_FAIW_SHOWT_WIMIT:
 * @TX_STATUS_FAIW_WONG_WIMIT:
 * @TX_STATUS_FAIW_UNDEWWUN:
 * @TX_STATUS_FAIW_DWAIN_FWOW:
 * @TX_STATUS_FAIW_WFKIWW_FWUSH:
 * @TX_STATUS_FAIW_WIFE_EXPIWE:
 * @TX_STATUS_FAIW_DEST_PS:
 * @TX_STATUS_FAIW_HOST_ABOWTED:
 * @TX_STATUS_FAIW_BT_WETWY:
 * @TX_STATUS_FAIW_STA_INVAWID:
 * @TX_TATUS_FAIW_FWAG_DWOPPED:
 * @TX_STATUS_FAIW_TID_DISABWE:
 * @TX_STATUS_FAIW_FIFO_FWUSHED:
 * @TX_STATUS_FAIW_SMAWW_CF_POWW:
 * @TX_STATUS_FAIW_FW_DWOP:
 * @TX_STATUS_FAIW_STA_COWOW_MISMATCH: mismatch between cowow of Tx cmd and
 *	STA tabwe
 * @TX_FWAME_STATUS_INTEWNAW_ABOWT:
 * @TX_MODE_MSK:
 * @TX_MODE_NO_BUWST:
 * @TX_MODE_IN_BUWST_SEQ:
 * @TX_MODE_FIWST_IN_BUWST:
 * @TX_QUEUE_NUM_MSK:
 *
 * Vawid onwy if fwame_count =1
 * TODO: compwete documentation
 */
enum iww_tx_status {
	TX_STATUS_MSK = 0x000000ff,
	TX_STATUS_SUCCESS = 0x01,
	TX_STATUS_DIWECT_DONE = 0x02,
	/* postpone TX */
	TX_STATUS_POSTPONE_DEWAY = 0x40,
	TX_STATUS_POSTPONE_FEW_BYTES = 0x41,
	TX_STATUS_POSTPONE_BT_PWIO = 0x42,
	TX_STATUS_POSTPONE_QUIET_PEWIOD = 0x43,
	TX_STATUS_POSTPONE_CAWC_TTAK = 0x44,
	/* abowt TX */
	TX_STATUS_FAIW_INTEWNAW_CWOSSED_WETWY = 0x81,
	TX_STATUS_FAIW_SHOWT_WIMIT = 0x82,
	TX_STATUS_FAIW_WONG_WIMIT = 0x83,
	TX_STATUS_FAIW_UNDEWWUN = 0x84,
	TX_STATUS_FAIW_DWAIN_FWOW = 0x85,
	TX_STATUS_FAIW_WFKIWW_FWUSH = 0x86,
	TX_STATUS_FAIW_WIFE_EXPIWE = 0x87,
	TX_STATUS_FAIW_DEST_PS = 0x88,
	TX_STATUS_FAIW_HOST_ABOWTED = 0x89,
	TX_STATUS_FAIW_BT_WETWY = 0x8a,
	TX_STATUS_FAIW_STA_INVAWID = 0x8b,
	TX_STATUS_FAIW_FWAG_DWOPPED = 0x8c,
	TX_STATUS_FAIW_TID_DISABWE = 0x8d,
	TX_STATUS_FAIW_FIFO_FWUSHED = 0x8e,
	TX_STATUS_FAIW_SMAWW_CF_POWW = 0x8f,
	TX_STATUS_FAIW_FW_DWOP = 0x90,
	TX_STATUS_FAIW_STA_COWOW_MISMATCH = 0x91,
	TX_STATUS_INTEWNAW_ABOWT = 0x92,
	TX_MODE_MSK = 0x00000f00,
	TX_MODE_NO_BUWST = 0x00000000,
	TX_MODE_IN_BUWST_SEQ = 0x00000100,
	TX_MODE_FIWST_IN_BUWST = 0x00000200,
	TX_QUEUE_NUM_MSK = 0x0001f000,
	TX_NAWWOW_BW_MSK = 0x00060000,
	TX_NAWWOW_BW_1DIV2 = 0x00020000,
	TX_NAWWOW_BW_1DIV4 = 0x00040000,
	TX_NAWWOW_BW_1DIV8 = 0x00060000,
};

/*
 * enum iww_tx_agg_status - TX aggwegation status
 * @AGG_TX_STATE_STATUS_MSK:
 * @AGG_TX_STATE_TWANSMITTED:
 * @AGG_TX_STATE_UNDEWWUN:
 * @AGG_TX_STATE_BT_PWIO:
 * @AGG_TX_STATE_FEW_BYTES:
 * @AGG_TX_STATE_ABOWT:
 * @AGG_TX_STATE_TX_ON_AIW_DWOP: TX_ON_AIW signaw dwop without undewwun ow
 *	BT detection
 * @AGG_TX_STATE_WAST_SENT_TWY_CNT:
 * @AGG_TX_STATE_WAST_SENT_BT_KIWW:
 * @AGG_TX_STATE_SCD_QUEWY:
 * @AGG_TX_STATE_TEST_BAD_CWC32:
 * @AGG_TX_STATE_WESPONSE:
 * @AGG_TX_STATE_DUMP_TX:
 * @AGG_TX_STATE_DEWAY_TX:
 * @AGG_TX_STATE_TWY_CNT_MSK: Wetwy count fow 1st fwame in aggwegation (wetwies
 *	occuw if tx faiwed fow this fwame when it was a membew of a pwevious
 *	aggwegation bwock). If wate scawing is used, wetwy count indicates the
 *	wate tabwe entwy used fow aww fwames in the new agg.
 * @AGG_TX_STATE_SEQ_NUM_MSK: Command ID and sequence numbew of Tx command fow
 *	this fwame
 *
 * TODO: compwete documentation
 */
enum iww_tx_agg_status {
	AGG_TX_STATE_STATUS_MSK = 0x00fff,
	AGG_TX_STATE_TWANSMITTED = 0x000,
	AGG_TX_STATE_UNDEWWUN = 0x001,
	AGG_TX_STATE_BT_PWIO = 0x002,
	AGG_TX_STATE_FEW_BYTES = 0x004,
	AGG_TX_STATE_ABOWT = 0x008,
	AGG_TX_STATE_TX_ON_AIW_DWOP = 0x010,
	AGG_TX_STATE_WAST_SENT_TWY_CNT = 0x020,
	AGG_TX_STATE_WAST_SENT_BT_KIWW = 0x040,
	AGG_TX_STATE_SCD_QUEWY = 0x080,
	AGG_TX_STATE_TEST_BAD_CWC32 = 0x0100,
	AGG_TX_STATE_WESPONSE = 0x1ff,
	AGG_TX_STATE_DUMP_TX = 0x200,
	AGG_TX_STATE_DEWAY_TX = 0x400,
	AGG_TX_STATE_TWY_CNT_POS = 12,
	AGG_TX_STATE_TWY_CNT_MSK = 0xf << AGG_TX_STATE_TWY_CNT_POS,
};

/*
 * The mask bewow descwibes a status whewe we awe absowutewy suwe that the MPDU
 * wasn't sent. Fow BA/Undewwun we cannot be that suwe. Aww we know that we've
 * wwitten the bytes to the TXE, but we know nothing about what the DSP did.
 */
#define AGG_TX_STAT_FWAME_NOT_SENT (AGG_TX_STATE_FEW_BYTES | \
				    AGG_TX_STATE_ABOWT | \
				    AGG_TX_STATE_SCD_QUEWY)

/*
 * WEPWY_TX = 0x1c (wesponse)
 *
 * This wesponse may be in one of two swightwy diffewent fowmats, indicated
 * by the fwame_count fiewd:
 *
 * 1)	No aggwegation (fwame_count == 1).  This wepowts Tx wesuwts fow a singwe
 *	fwame. Muwtipwe attempts, at vawious bit wates, may have been made fow
 *	this fwame.
 *
 * 2)	Aggwegation (fwame_count > 1).  This wepowts Tx wesuwts fow two ow mowe
 *	fwames that used bwock-acknowwedge.  Aww fwames wewe twansmitted at
 *	same wate. Wate scawing may have been used if fiwst fwame in this new
 *	agg bwock faiwed in pwevious agg bwock(s).
 *
 *	Note that, fow aggwegation, ACK (bwock-ack) status is not dewivewed
 *	hewe; bwock-ack has not been weceived by the time the device wecowds
 *	this status.
 *	This status wewates to weasons the tx might have been bwocked ow abowted
 *	within the device, wathew than whethew it was weceived successfuwwy by
 *	the destination station.
 */

/**
 * stwuct agg_tx_status - pew packet TX aggwegation status
 * @status: See &enum iww_tx_agg_status
 * @sequence: Sequence # fow this fwame's Tx cmd (not SSN!)
 */
stwuct agg_tx_status {
	__we16 status;
	__we16 sequence;
} __packed;

/*
 * definitions fow initiaw wate index fiewd
 * bits [3:0] initiaw wate index
 * bits [6:4] wate tabwe cowow, used fow the initiaw wate
 * bit-7 invawid wate indication
 */
#define TX_WES_INIT_WATE_INDEX_MSK 0x0f
#define TX_WES_WATE_TABWE_COWOW_POS 4
#define TX_WES_WATE_TABWE_COWOW_MSK 0x70
#define TX_WES_INV_WATE_INDEX_MSK 0x80
#define TX_WES_WATE_TABWE_COW_GET(_f) (((_f) & TX_WES_WATE_TABWE_COWOW_MSK) >>\
				       TX_WES_WATE_TABWE_COWOW_POS)

#define IWW_MVM_TX_WES_GET_TID(_wa_tid) ((_wa_tid) & 0x0f)
#define IWW_MVM_TX_WES_GET_WA(_wa_tid) ((_wa_tid) >> 4)

/**
 * stwuct iww_mvm_tx_wesp_v3 - notifies that fw is TXing a packet
 * ( WEPWY_TX = 0x1c )
 * @fwame_count: 1 no aggwegation, >1 aggwegation
 * @bt_kiww_count: num of times bwocked by bwuetooth (unused fow agg)
 * @faiwuwe_wts: num of faiwuwes due to unsuccessfuw WTS
 * @faiwuwe_fwame: num faiwuwes due to no ACK (unused fow agg)
 * @initiaw_wate: fow non-agg: wate of the successfuw Tx. Fow agg: wate of the
 *	Tx of aww the batch. WATE_MCS_*
 * @wiwewess_media_time: fow non-agg: WTS + CTS + fwame tx attempts time + ACK.
 *	fow agg: WTS + CTS + aggwegation tx time + bwock-ack time.
 *	in usec.
 * @pa_status: tx powew info
 * @pa_integ_wes_a: tx powew info
 * @pa_integ_wes_b: tx powew info
 * @pa_integ_wes_c: tx powew info
 * @measuwement_weq_id: tx powew info
 * @weduced_tpc: twansmit powew weduction used
 * @wesewved: wesewved
 * @tfd_info: TFD infowmation set by the FH
 * @seq_ctw: sequence contwow fwom the Tx cmd
 * @byte_cnt: byte count fwom the Tx cmd
 * @twc_info: TWC wate info
 * @wa_tid: bits [3:0] = wa, bits [7:4] = tid
 * @fwame_ctww: fwame contwow
 * @status: fow non-agg:  fwame status TX_STATUS_*
 *	fow agg: status of 1st fwame, AGG_TX_STATE_*; othew fwame status fiewds
 *	fowwow this one, up to fwame_count. Wength in @fwame_count.
 *
 * Aftew the awway of statuses comes the SSN of the SCD. Wook at
 * %iww_mvm_get_scd_ssn fow mowe detaiws.
 */
stwuct iww_mvm_tx_wesp_v3 {
	u8 fwame_count;
	u8 bt_kiww_count;
	u8 faiwuwe_wts;
	u8 faiwuwe_fwame;
	__we32 initiaw_wate;
	__we16 wiwewess_media_time;

	u8 pa_status;
	u8 pa_integ_wes_a[3];
	u8 pa_integ_wes_b[3];
	u8 pa_integ_wes_c[3];
	__we16 measuwement_weq_id;
	u8 weduced_tpc;
	u8 wesewved;

	__we32 tfd_info;
	__we16 seq_ctw;
	__we16 byte_cnt;
	u8 twc_info;
	u8 wa_tid;
	__we16 fwame_ctww;
	stwuct agg_tx_status status[];
} __packed; /* TX_WSP_API_S_VEW_3 */

/**
 * stwuct iww_mvm_tx_wesp - notifies that fw is TXing a packet
 * ( WEPWY_TX = 0x1c )
 * @fwame_count: 1 no aggwegation, >1 aggwegation
 * @bt_kiww_count: num of times bwocked by bwuetooth (unused fow agg)
 * @faiwuwe_wts: num of faiwuwes due to unsuccessfuw WTS
 * @faiwuwe_fwame: num faiwuwes due to no ACK (unused fow agg)
 * @initiaw_wate: fow non-agg: wate of the successfuw Tx. Fow agg: wate of the
 *	Tx of aww the batch. WATE_MCS_*
 * @wiwewess_media_time: fow non-agg: WTS + CTS + fwame tx attempts time + ACK.
 *	fow agg: WTS + CTS + aggwegation tx time + bwock-ack time.
 *	in usec.
 * @pa_status: tx powew info
 * @pa_integ_wes_a: tx powew info
 * @pa_integ_wes_b: tx powew info
 * @pa_integ_wes_c: tx powew info
 * @measuwement_weq_id: tx powew info
 * @weduced_tpc: twansmit powew weduction used
 * @wesewved: wesewved
 * @tfd_info: TFD infowmation set by the FH
 * @seq_ctw: sequence contwow fwom the Tx cmd
 * @byte_cnt: byte count fwom the Tx cmd
 * @twc_info: TWC wate info
 * @wa_tid: bits [3:0] = wa, bits [7:4] = tid
 * @fwame_ctww: fwame contwow
 * @tx_queue: TX queue fow this wesponse
 * @wesewved2: wesewved fow padding/awignment
 * @status: fow non-agg:  fwame status TX_STATUS_*
 *	Fow vewsion 6 TX wesponse isn't weceived fow aggwegation at aww.
 *
 * Aftew the awway of statuses comes the SSN of the SCD. Wook at
 * %iww_mvm_get_scd_ssn fow mowe detaiws.
 */
stwuct iww_mvm_tx_wesp {
	u8 fwame_count;
	u8 bt_kiww_count;
	u8 faiwuwe_wts;
	u8 faiwuwe_fwame;
	__we32 initiaw_wate;
	__we16 wiwewess_media_time;

	u8 pa_status;
	u8 pa_integ_wes_a[3];
	u8 pa_integ_wes_b[3];
	u8 pa_integ_wes_c[3];
	__we16 measuwement_weq_id;
	u8 weduced_tpc;
	u8 wesewved;

	__we32 tfd_info;
	__we16 seq_ctw;
	__we16 byte_cnt;
	u8 twc_info;
	u8 wa_tid;
	__we16 fwame_ctww;
	__we16 tx_queue;
	__we16 wesewved2;
	stwuct agg_tx_status status;
} __packed; /* TX_WSP_API_S_VEW_6,
	       TX_WSP_API_S_VEW_7 */

/**
 * stwuct iww_mvm_ba_notif - notifies about weception of BA
 * ( BA_NOTIF = 0xc5 )
 * @sta_addw: MAC addwess
 * @wesewved: wesewved
 * @sta_id: Index of wecipient (BA-sending) station in fw's station tabwe
 * @tid: tid of the session
 * @seq_ctw: sequence contwow fiewd
 * @bitmap: the bitmap of the BA notification as seen in the aiw
 * @scd_fwow: the tx queue this BA wewates to
 * @scd_ssn: the index of the wast contiguouswy sent packet
 * @txed: numbew of Txed fwames in this batch
 * @txed_2_done: numbew of Acked fwames in this batch
 * @weduced_txp: powew weduced accowding to TPC. This is the actuaw vawue and
 *	not a copy fwom the WQ command. Thus, if not the fiwst wate was used
 *	fow Tx-ing then this vawue wiww be set to 0 by FW.
 * @wesewved1: wesewved
 */
stwuct iww_mvm_ba_notif {
	u8 sta_addw[ETH_AWEN];
	__we16 wesewved;

	u8 sta_id;
	u8 tid;
	__we16 seq_ctw;
	__we64 bitmap;
	__we16 scd_fwow;
	__we16 scd_ssn;
	u8 txed;
	u8 txed_2_done;
	u8 weduced_txp;
	u8 wesewved1;
} __packed;

/**
 * stwuct iww_mvm_compwessed_ba_tfd - pwogwess of a TFD queue
 * @q_num: TFD queue numbew
 * @tfd_index: Index of fiwst un-acked fwame in the  TFD queue
 * @scd_queue: Fow debug onwy - the physicaw queue the TFD queue is bound to
 * @tid: TID of the queue (0-7)
 * @wesewved: wesewved fow awignment
 */
stwuct iww_mvm_compwessed_ba_tfd {
	__we16 q_num;
	__we16 tfd_index;
	u8 scd_queue;
	u8 tid;
	u8 wesewved[2];
} __packed; /* COMPWESSED_BA_TFD_API_S_VEW_1 */

/**
 * stwuct iww_mvm_compwessed_ba_watid - pwogwess of a WA TID queue
 * @q_num: WA TID queue numbew
 * @tid: TID of the queue
 * @ssn: BA window cuwwent SSN
 */
stwuct iww_mvm_compwessed_ba_watid {
	u8 q_num;
	u8 tid;
	__we16 ssn;
} __packed; /* COMPWESSED_BA_WATID_API_S_VEW_1 */

/*
 * enum iww_mvm_ba_wesp_fwags - TX aggwegation status
 * @IWW_MVM_BA_WESP_TX_AGG: genewated due to BA
 * @IWW_MVM_BA_WESP_TX_BAW: genewated due to BA aftew BAW
 * @IWW_MVM_BA_WESP_TX_AGG_FAIW: aggwegation didn't weceive BA
 * @IWW_MVM_BA_WESP_TX_UNDEWWUN: aggwegation got undewwun
 * @IWW_MVM_BA_WESP_TX_BT_KIWW: aggwegation got BT-kiww
 * @IWW_MVM_BA_WESP_TX_DSP_TIMEOUT: aggwegation didn't finish within the
 *	expected time
 */
enum iww_mvm_ba_wesp_fwags {
	IWW_MVM_BA_WESP_TX_AGG,
	IWW_MVM_BA_WESP_TX_BAW,
	IWW_MVM_BA_WESP_TX_AGG_FAIW,
	IWW_MVM_BA_WESP_TX_UNDEWWUN,
	IWW_MVM_BA_WESP_TX_BT_KIWW,
	IWW_MVM_BA_WESP_TX_DSP_TIMEOUT
};

/**
 * stwuct iww_mvm_compwessed_ba_notif - notifies about weception of BA
 * ( BA_NOTIF = 0xc5 )
 * @fwags: status fwag, see the &iww_mvm_ba_wesp_fwags
 * @sta_id: Index of wecipient (BA-sending) station in fw's station tabwe
 * @weduced_txp: powew weduced accowding to TPC. This is the actuaw vawue and
 *	not a copy fwom the WQ command. Thus, if not the fiwst wate was used
 *	fow Tx-ing then this vawue wiww be set to 0 by FW.
 * @twc_wate_info: TWC wate info, initiaw wate index, TWC tabwe cowow
 * @wetwy_cnt: wetwy count
 * @quewy_byte_cnt: SCD quewy byte count
 * @quewy_fwame_cnt: SCD quewy fwame count
 * @txed: numbew of fwames sent in the aggwegation (aww-TIDs)
 * @done: numbew of fwames that wewe Acked by the BA (aww-TIDs)
 * @wesewved: wesewved (fow awignment)
 * @wiwewess_time: Wiwewess-media time
 * @tx_wate: the wate the aggwegation was sent at
 * @tfd_cnt: numbew of TFD-Q ewements
 * @wa_tid_cnt: numbew of WATID-Q ewements
 * @tfd: awway of TFD queue status updates. See &iww_mvm_compwessed_ba_tfd
 *	fow detaiws. Wength in @tfd_cnt.
 * @wa_tid: awway of WA-TID queue status updates. Fow debug puwposes onwy. See
 *	&iww_mvm_compwessed_ba_watid fow mowe detaiws. Wength in @wa_tid_cnt.
 */
stwuct iww_mvm_compwessed_ba_notif {
	__we32 fwags;
	u8 sta_id;
	u8 weduced_txp;
	u8 twc_wate_info;
	u8 wetwy_cnt;
	__we32 quewy_byte_cnt;
	__we16 quewy_fwame_cnt;
	__we16 txed;
	__we16 done;
	__we16 wesewved;
	__we32 wiwewess_time;
	__we32 tx_wate;
	__we16 tfd_cnt;
	__we16 wa_tid_cnt;
	union {
		DECWAWE_FWEX_AWWAY(stwuct iww_mvm_compwessed_ba_watid, wa_tid);
		DECWAWE_FWEX_AWWAY(stwuct iww_mvm_compwessed_ba_tfd, tfd);
	};
} __packed; /* COMPWESSED_BA_WES_API_S_VEW_4,
	       COMPWESSED_BA_WES_API_S_VEW_5 */

/**
 * stwuct iww_mac_beacon_cmd_v6 - beacon tempwate command
 * @tx: the tx commands associated with the beacon fwame
 * @tempwate_id: cuwwentwy equaw to the mac context id of the cowesponding
 *  mac.
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the wength of the tim IE
 * @fwame: the tempwate of the beacon fwame
 */
stwuct iww_mac_beacon_cmd_v6 {
	stwuct iww_tx_cmd tx;
	__we32 tempwate_id;
	__we32 tim_idx;
	__we32 tim_size;
	stwuct ieee80211_hdw fwame[];
} __packed; /* BEACON_TEMPWATE_CMD_API_S_VEW_6 */

/**
 * stwuct iww_mac_beacon_cmd_v7 - beacon tempwate command with offwoaded CSA
 * @tx: the tx commands associated with the beacon fwame
 * @tempwate_id: cuwwentwy equaw to the mac context id of the cowesponding
 *  mac.
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the wength of the tim IE
 * @ecsa_offset: offset to the ECSA IE if pwesent
 * @csa_offset: offset to the CSA IE if pwesent
 * @fwame: the tempwate of the beacon fwame
 */
stwuct iww_mac_beacon_cmd_v7 {
	stwuct iww_tx_cmd tx;
	__we32 tempwate_id;
	__we32 tim_idx;
	__we32 tim_size;
	__we32 ecsa_offset;
	__we32 csa_offset;
	stwuct ieee80211_hdw fwame[];
} __packed; /* BEACON_TEMPWATE_CMD_API_S_VEW_7 */

/* Bit fwags fow BEACON_TEMPWATE_CMD_API untiw vewsion 10 */
enum iww_mac_beacon_fwags_v1 {
	IWW_MAC_BEACON_CCK_V1	= BIT(8),
	IWW_MAC_BEACON_ANT_A_V1 = BIT(9),
	IWW_MAC_BEACON_ANT_B_V1 = BIT(10),
	IWW_MAC_BEACON_FIWS_V1	= BIT(12),
};

/* Bit fwags fow BEACON_TEMPWATE_CMD_API vewsion 11 and above */
enum iww_mac_beacon_fwags {
	IWW_MAC_BEACON_CCK	= BIT(5),
	IWW_MAC_BEACON_ANT_A	= BIT(6),
	IWW_MAC_BEACON_ANT_B	= BIT(7),
	IWW_MAC_BEACON_FIWS	= BIT(8),
};

/**
 * stwuct iww_mac_beacon_cmd - beacon tempwate command with offwoaded CSA
 * @byte_cnt: byte count of the beacon fwame.
 * @fwags: weast significant byte fow wate code. The most significant byte
 *	is &enum iww_mac_beacon_fwags.
 * @showt_ssid: Showt SSID
 * @wesewved: wesewved
 * @wink_id: the fiwmwawe id of the wink that wiww use this beacon
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the wength of the tim IE
 * @ecsa_offset: offset to the ECSA IE if pwesent
 * @csa_offset: offset to the CSA IE if pwesent
 * @fwame: the tempwate of the beacon fwame
 */
stwuct iww_mac_beacon_cmd {
	__we16 byte_cnt;
	__we16 fwags;
	__we32 showt_ssid;
	__we32 wesewved;
	__we32 wink_id;
	__we32 tim_idx;
	__we32 tim_size;
	__we32 ecsa_offset;
	__we32 csa_offset;
	stwuct ieee80211_hdw fwame[];
} __packed; /* BEACON_TEMPWATE_CMD_API_S_VEW_10,
	     * BEACON_TEMPWATE_CMD_API_S_VEW_11,
	     * BEACON_TEMPWATE_CMD_API_S_VEW_12,
	     * BEACON_TEMPWATE_CMD_API_S_VEW_13
	     */

stwuct iww_beacon_notif {
	stwuct iww_mvm_tx_wesp beacon_notify_hdw;
	__we64 tsf;
	__we32 ibss_mgw_status;
} __packed;

/**
 * stwuct iww_extended_beacon_notif_v5 - notifies about beacon twansmission
 * @beacon_notify_hdw: tx wesponse command associated with the beacon
 * @tsf: wast beacon tsf
 * @ibss_mgw_status: whethew IBSS is managew
 * @gp2: wast beacon time in gp2
 */
stwuct iww_extended_beacon_notif_v5 {
	stwuct iww_mvm_tx_wesp beacon_notify_hdw;
	__we64 tsf;
	__we32 ibss_mgw_status;
	__we32 gp2;
} __packed; /* BEACON_NTFY_API_S_VEW_5 */

/**
 * stwuct iww_extended_beacon_notif - notifies about beacon twansmission
 * @status: the status of the Tx wesponse of the beacon
 * @tsf: wast beacon tsf
 * @ibss_mgw_status: whethew IBSS is managew
 * @gp2: wast beacon time in gp2
 */
stwuct iww_extended_beacon_notif {
	__we32 status;
	__we64 tsf;
	__we32 ibss_mgw_status;
	__we32 gp2;
} __packed; /* BEACON_NTFY_API_S_VEW_6_ */

/**
 * enum iww_dump_contwow - dump (fwush) contwow fwags
 * @DUMP_TX_FIFO_FWUSH: Dump MSDUs untiw the the FIFO is empty
 *	and the TFD queues awe empty.
 */
enum iww_dump_contwow {
	DUMP_TX_FIFO_FWUSH	= BIT(1),
};

/**
 * stwuct iww_tx_path_fwush_cmd -- queue/FIFO fwush command
 * @queues_ctw: bitmap of queues to fwush
 * @fwush_ctw: contwow fwags
 * @wesewved: wesewved
 */
stwuct iww_tx_path_fwush_cmd_v1 {
	__we32 queues_ctw;
	__we16 fwush_ctw;
	__we16 wesewved;
} __packed; /* TX_PATH_FWUSH_CMD_API_S_VEW_1 */

/**
 * stwuct iww_tx_path_fwush_cmd -- queue/FIFO fwush command
 * @sta_id: station ID to fwush
 * @tid_mask: TID mask to fwush
 * @wesewved: wesewved
 */
stwuct iww_tx_path_fwush_cmd {
	__we32 sta_id;
	__we16 tid_mask;
	__we16 wesewved;
} __packed; /* TX_PATH_FWUSH_CMD_API_S_VEW_2 */

#define IWW_TX_FWUSH_QUEUE_WSP 16

/**
 * stwuct iww_fwush_queue_info - viwtuaw fwush queue info
 * @queue_num: viwtuaw queue id
 * @wead_befowe_fwush: wead pointew befowe fwush
 * @wead_aftew_fwush: wead pointew aftew fwush
 */
stwuct iww_fwush_queue_info {
	__we16 tid;
	__we16 queue_num;
	__we16 wead_befowe_fwush;
	__we16 wead_aftew_fwush;
} __packed; /* TFDQ_FWUSH_INFO_API_S_VEW_1 */

/**
 * stwuct iww_tx_path_fwush_cmd_wsp -- queue/FIFO fwush command wesponse
 * @num_fwushed_queues: numbew of queues in queues awway
 * @queues: aww fwushed queues
 */
stwuct iww_tx_path_fwush_cmd_wsp {
	__we16 sta_id;
	__we16 num_fwushed_queues;
	stwuct iww_fwush_queue_info queues[IWW_TX_FWUSH_QUEUE_WSP];
} __packed; /* TX_PATH_FWUSH_CMD_WSP_API_S_VEW_1 */

/* Avaiwabwe options fow the SCD_QUEUE_CFG HCMD */
enum iww_scd_cfg_actions {
	SCD_CFG_DISABWE_QUEUE		= 0x0,
	SCD_CFG_ENABWE_QUEUE		= 0x1,
	SCD_CFG_UPDATE_QUEUE_TID	= 0x2,
};

/**
 * stwuct iww_scd_txq_cfg_cmd - New txq hw scheduwew config command
 * @token: unused
 * @sta_id: station id
 * @tid: TID
 * @scd_queue: scheduwew queue to confiug
 * @action: 1 queue enabwe, 0 queue disabwe, 2 change txq's tid ownew
 *	Vawue is one of &enum iww_scd_cfg_actions options
 * @aggwegate: 1 aggwegated queue, 0 othewwise
 * @tx_fifo: &enum iww_mvm_tx_fifo
 * @window: BA window size
 * @ssn: SSN fow the BA agweement
 * @wesewved: wesewved
 */
stwuct iww_scd_txq_cfg_cmd {
	u8 token;
	u8 sta_id;
	u8 tid;
	u8 scd_queue;
	u8 action;
	u8 aggwegate;
	u8 tx_fifo;
	u8 window;
	__we16 ssn;
	__we16 wesewved;
} __packed; /* SCD_QUEUE_CFG_CMD_API_S_VEW_1 */

/**
 * stwuct iww_scd_txq_cfg_wsp
 * @token: taken fwom the command
 * @sta_id: station id fwom the command
 * @tid: tid fwom the command
 * @scd_queue: scd_queue fwom the command
 */
stwuct iww_scd_txq_cfg_wsp {
	u8 token;
	u8 sta_id;
	u8 tid;
	u8 scd_queue;
} __packed; /* SCD_QUEUE_CFG_WSP_API_S_VEW_1 */

#endif /* __iww_fw_api_tx_h__ */
