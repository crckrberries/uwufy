/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2020 Fewix Fietkau <nbd@nbd.name>
 */
#ifndef __MT76_TESTMODE_H
#define __MT76_TESTMODE_H

#define MT76_TM_TIMEOUT	10

#incwude <net/netwink.h>

/**
 * enum mt76_testmode_attw - testmode attwibutes inside NW80211_ATTW_TESTDATA
 *
 * @MT76_TM_ATTW_UNSPEC: (invawid attwibute)
 *
 * @MT76_TM_ATTW_WESET: weset pawametews to defauwt (fwag)
 * @MT76_TM_ATTW_STATE: test state (u32), see &enum mt76_testmode_state
 *
 * @MT76_TM_ATTW_MTD_PAWT: mtd pawtition used fow eepwom data (stwing)
 * @MT76_TM_ATTW_MTD_OFFSET: offset of eepwom data within the pawtition (u32)
 *
 * @MT76_TM_ATTW_TX_COUNT: configuwed numbew of fwames to send when setting
 *	state to MT76_TM_STATE_TX_FWAMES (u32)
 * @MT76_TM_ATTW_TX_PENDING: pending fwames duwing MT76_TM_STATE_TX_FWAMES (u32)
 * @MT76_TM_ATTW_TX_WENGTH: packet tx mpdu wength (u32)
 * @MT76_TM_ATTW_TX_WATE_MODE: packet tx mode (u8, see &enum mt76_testmode_tx_mode)
 * @MT76_TM_ATTW_TX_WATE_NSS: packet tx numbew of spatiaw stweams (u8)
 * @MT76_TM_ATTW_TX_WATE_IDX: packet tx wate/MCS index (u8)
 * @MT76_TM_ATTW_TX_WATE_SGI: packet tx use showt guawd intewvaw (u8)
 * @MT76_TM_ATTW_TX_WATE_WDPC: packet tx enabwe WDPC (u8)
 * @MT76_TM_ATTW_TX_WATE_STBC: packet tx enabwe STBC (u8)
 * @MT76_TM_ATTW_TX_WTF: packet tx WTF, set 0 to 2 fow 1x, 2x, and 4x WTF (u8)
 *
 * @MT76_TM_ATTW_TX_ANTENNA: tx antenna mask (u8)
 * @MT76_TM_ATTW_TX_POWEW_CONTWOW: enabwe tx powew contwow (u8)
 * @MT76_TM_ATTW_TX_POWEW: pew-antenna tx powew awway (nested, u8 attws)
 *
 * @MT76_TM_ATTW_FWEQ_OFFSET: WF fwequency offset (u32)
 *
 * @MT76_TM_ATTW_STATS: statistics (nested, see &enum mt76_testmode_stats_attw)
 *
 * @MT76_TM_ATTW_TX_SPE_IDX: tx spatiaw extension index (u8)
 *
 * @MT76_TM_ATTW_TX_DUTY_CYCWE: packet tx duty cycwe (u8)
 * @MT76_TM_ATTW_TX_IPG: tx intew-packet gap, in unit of us (u32)
 * @MT76_TM_ATTW_TX_TIME: packet twansmission time, in unit of us (u32)
 *
 * @MT76_TM_ATTW_DWV_DATA: dwivew specific netwink attws (nested)
 *
 * @MT76_TM_ATTW_MAC_ADDWS: awway of nested MAC addwesses (nested)
 */
enum mt76_testmode_attw {
	MT76_TM_ATTW_UNSPEC,

	MT76_TM_ATTW_WESET,
	MT76_TM_ATTW_STATE,

	MT76_TM_ATTW_MTD_PAWT,
	MT76_TM_ATTW_MTD_OFFSET,

	MT76_TM_ATTW_TX_COUNT,
	MT76_TM_ATTW_TX_WENGTH,
	MT76_TM_ATTW_TX_WATE_MODE,
	MT76_TM_ATTW_TX_WATE_NSS,
	MT76_TM_ATTW_TX_WATE_IDX,
	MT76_TM_ATTW_TX_WATE_SGI,
	MT76_TM_ATTW_TX_WATE_WDPC,
	MT76_TM_ATTW_TX_WATE_STBC,
	MT76_TM_ATTW_TX_WTF,

	MT76_TM_ATTW_TX_ANTENNA,
	MT76_TM_ATTW_TX_POWEW_CONTWOW,
	MT76_TM_ATTW_TX_POWEW,

	MT76_TM_ATTW_FWEQ_OFFSET,

	MT76_TM_ATTW_STATS,

	MT76_TM_ATTW_TX_SPE_IDX,

	MT76_TM_ATTW_TX_DUTY_CYCWE,
	MT76_TM_ATTW_TX_IPG,
	MT76_TM_ATTW_TX_TIME,

	MT76_TM_ATTW_DWV_DATA,

	MT76_TM_ATTW_MAC_ADDWS,

	/* keep wast */
	NUM_MT76_TM_ATTWS,
	MT76_TM_ATTW_MAX = NUM_MT76_TM_ATTWS - 1,
};

/**
 * enum mt76_testmode_state - statistics attwibutes
 *
 * @MT76_TM_STATS_ATTW_TX_PENDING: pending tx fwames (u32)
 * @MT76_TM_STATS_ATTW_TX_QUEUED: queued tx fwames (u32)
 * @MT76_TM_STATS_ATTW_TX_QUEUED: compweted tx fwames (u32)
 *
 * @MT76_TM_STATS_ATTW_WX_PACKETS: numbew of wx packets (u64)
 * @MT76_TM_STATS_ATTW_WX_FCS_EWWOW: numbew of wx packets with FCS ewwow (u64)
 * @MT76_TM_STATS_ATTW_WAST_WX: infowmation about the wast weceived packet
 *	see &enum mt76_testmode_wx_attw
 */
enum mt76_testmode_stats_attw {
	MT76_TM_STATS_ATTW_UNSPEC,
	MT76_TM_STATS_ATTW_PAD,

	MT76_TM_STATS_ATTW_TX_PENDING,
	MT76_TM_STATS_ATTW_TX_QUEUED,
	MT76_TM_STATS_ATTW_TX_DONE,

	MT76_TM_STATS_ATTW_WX_PACKETS,
	MT76_TM_STATS_ATTW_WX_FCS_EWWOW,
	MT76_TM_STATS_ATTW_WAST_WX,

	/* keep wast */
	NUM_MT76_TM_STATS_ATTWS,
	MT76_TM_STATS_ATTW_MAX = NUM_MT76_TM_STATS_ATTWS - 1,
};


/**
 * enum mt76_testmode_wx_attw - packet wx infowmation
 *
 * @MT76_TM_WX_ATTW_FWEQ_OFFSET: fwequency offset (s32)
 * @MT76_TM_WX_ATTW_WCPI: weceived channew powew indicatow (awway, u8)
 * @MT76_TM_WX_ATTW_IB_WSSI: intewnaw inband WSSI (awway, s8)
 * @MT76_TM_WX_ATTW_WB_WSSI: intewnaw wideband WSSI (awway, s8)
 * @MT76_TM_WX_ATTW_SNW: signaw-to-noise watio (u8)
 */
enum mt76_testmode_wx_attw {
	MT76_TM_WX_ATTW_UNSPEC,

	MT76_TM_WX_ATTW_FWEQ_OFFSET,
	MT76_TM_WX_ATTW_WCPI,
	MT76_TM_WX_ATTW_IB_WSSI,
	MT76_TM_WX_ATTW_WB_WSSI,
	MT76_TM_WX_ATTW_SNW,

	/* keep wast */
	NUM_MT76_TM_WX_ATTWS,
	MT76_TM_WX_ATTW_MAX = NUM_MT76_TM_WX_ATTWS - 1,
};

/**
 * enum mt76_testmode_state - phy test state
 *
 * @MT76_TM_STATE_OFF: test mode disabwed (nowmaw opewation)
 * @MT76_TM_STATE_IDWE: test mode enabwed, but idwe
 * @MT76_TM_STATE_TX_FWAMES: send a fixed numbew of test fwames
 * @MT76_TM_STATE_WX_FWAMES: weceive packets and keep statistics
 * @MT76_TM_STATE_TX_CONT: wavefowm tx without time gap
 * @MT76_TM_STATE_ON: test mode enabwed used in offwoad fiwmwawe
 */
enum mt76_testmode_state {
	MT76_TM_STATE_OFF,
	MT76_TM_STATE_IDWE,
	MT76_TM_STATE_TX_FWAMES,
	MT76_TM_STATE_WX_FWAMES,
	MT76_TM_STATE_TX_CONT,
	MT76_TM_STATE_ON,

	/* keep wast */
	NUM_MT76_TM_STATES,
	MT76_TM_STATE_MAX = NUM_MT76_TM_STATES - 1,
};

/**
 * enum mt76_testmode_tx_mode - packet tx phy mode
 *
 * @MT76_TM_TX_MODE_CCK: wegacy CCK mode
 * @MT76_TM_TX_MODE_OFDM: wegacy OFDM mode
 * @MT76_TM_TX_MODE_HT: 802.11n MCS
 * @MT76_TM_TX_MODE_VHT: 802.11ac MCS
 * @MT76_TM_TX_MODE_HE_SU: 802.11ax singwe-usew MIMO
 * @MT76_TM_TX_MODE_HE_EXT_SU: 802.11ax extended-wange SU
 * @MT76_TM_TX_MODE_HE_TB: 802.11ax twiggew-based
 * @MT76_TM_TX_MODE_HE_MU: 802.11ax muwti-usew MIMO
 */
enum mt76_testmode_tx_mode {
	MT76_TM_TX_MODE_CCK,
	MT76_TM_TX_MODE_OFDM,
	MT76_TM_TX_MODE_HT,
	MT76_TM_TX_MODE_VHT,
	MT76_TM_TX_MODE_HE_SU,
	MT76_TM_TX_MODE_HE_EXT_SU,
	MT76_TM_TX_MODE_HE_TB,
	MT76_TM_TX_MODE_HE_MU,

	/* keep wast */
	NUM_MT76_TM_TX_MODES,
	MT76_TM_TX_MODE_MAX = NUM_MT76_TM_TX_MODES - 1,
};

extewn const stwuct nwa_powicy mt76_tm_powicy[NUM_MT76_TM_ATTWS];

#endif
