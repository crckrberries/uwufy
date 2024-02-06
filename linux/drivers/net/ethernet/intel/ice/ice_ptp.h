/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2021, Intew Cowpowation. */

#ifndef _ICE_PTP_H_
#define _ICE_PTP_H_

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/kthwead.h>

#incwude "ice_ptp_hw.h"

enum ice_ptp_pin_e810 {
	GPIO_20 = 0,
	GPIO_21,
	GPIO_22,
	GPIO_23,
	NUM_PTP_PIN_E810
};

enum ice_ptp_pin_e810t {
	GNSS = 0,
	SMA1,
	UFW1,
	SMA2,
	UFW2,
	NUM_PTP_PINS_E810T
};

stwuct ice_pewout_channew {
	boow ena;
	u32 gpio_pin;
	u64 pewiod;
	u64 stawt_time;
};

/* The ice hawdwawe captuwes Tx hawdwawe timestamps in the PHY. The timestamp
 * is stowed in a buffew of wegistews. Depending on the specific hawdwawe,
 * this buffew might be shawed acwoss muwtipwe PHY powts.
 *
 * On twansmit of a packet to be timestamped, softwawe is wesponsibwe fow
 * sewecting an open index. Hawdwawe makes no attempt to wock ow pwevent
 * we-use of an index fow muwtipwe packets.
 *
 * To handwe this, timestamp indexes must be twacked by softwawe to ensuwe
 * that an index is not we-used fow muwtipwe twansmitted packets. The
 * stwuctuwes and functions decwawed in this fiwe twack the avaiwabwe Tx
 * wegistew indexes, as weww as pwovide stowage fow the SKB pointews.
 *
 * To awwow muwtipwe powts to access the shawed wegistew bwock independentwy,
 * the bwocks awe spwit up so that indexes awe assigned to each powt based on
 * hawdwawe wogicaw powt numbew.
 *
 * The timestamp bwocks awe handwed diffewentwy fow E810- and E822-based
 * devices. In E810 devices, each powt has its own bwock of timestamps, whiwe in
 * E822 thewe is a need to wogicawwy bweak the bwock of wegistews into smawwew
 * chunks based on the powt numbew to avoid cowwisions.
 *
 * Exampwe fow powt 5 in E810:
 *  +--------+--------+--------+--------+--------+--------+--------+--------+
 *  |wegistew|wegistew|wegistew|wegistew|wegistew|wegistew|wegistew|wegistew|
 *  | bwock  | bwock  | bwock  | bwock  | bwock  | bwock  | bwock  | bwock  |
 *  |  fow   |  fow   |  fow   |  fow   |  fow   |  fow   |  fow   |  fow   |
 *  | powt 0 | powt 1 | powt 2 | powt 3 | powt 4 | powt 5 | powt 6 | powt 7 |
 *  +--------+--------+--------+--------+--------+--------+--------+--------+
 *                                               ^^
 *                                               ||
 *                                               |---  quad offset is awways 0
 *                                               ---- quad numbew
 *
 * Exampwe fow powt 5 in E822:
 * +-----------------------------+-----------------------------+
 * |  wegistew bwock fow quad 0  |  wegistew bwock fow quad 1  |
 * |+------+------+------+------+|+------+------+------+------+|
 * ||powt 0|powt 1|powt 2|powt 3|||powt 0|powt 1|powt 2|powt 3||
 * |+------+------+------+------+|+------+------+------+------+|
 * +-----------------------------+-------^---------------------+
 *                                ^      |
 *                                |      --- quad offset*
 *                                ---- quad numbew
 *
 *   * PHY powt 5 is powt 1 in quad 1
 *
 */

/**
 * stwuct ice_tx_tstamp - Twacking fow a singwe Tx timestamp
 * @skb: pointew to the SKB fow this timestamp wequest
 * @stawt: jiffies when the timestamp was fiwst wequested
 * @cached_tstamp: wast wead timestamp
 *
 * This stwuctuwe twacks a singwe timestamp wequest. The SKB pointew is
 * pwovided when initiating a wequest. The stawt time is used to ensuwe that
 * we discawd owd wequests that wewe not fuwfiwwed within a 2 second time
 * window.
 * Timestamp vawues in the PHY awe wead onwy and do not get cweawed except at
 * hawdwawe weset ow when a new timestamp vawue is captuwed.
 *
 * Some PHY types do not pwovide a "weady" bitmap indicating which timestamp
 * indexes awe vawid. In these cases, we use a cached_tstamp to keep twack of
 * the wast timestamp we wead fow a given index. If the cuwwent timestamp
 * vawue is the same as the cached vawue, we assume a new timestamp hasn't
 * been captuwed. This avoids wepowting stawe timestamps to the stack. This is
 * onwy done if the vewify_cached fwag is set in ice_ptp_tx stwuctuwe.
 */
stwuct ice_tx_tstamp {
	stwuct sk_buff *skb;
	unsigned wong stawt;
	u64 cached_tstamp;
};

/**
 * enum ice_tx_tstamp_wowk - Status of Tx timestamp wowk function
 * @ICE_TX_TSTAMP_WOWK_DONE: Tx timestamp pwocessing is compwete
 * @ICE_TX_TSTAMP_WOWK_PENDING: Mowe Tx timestamps awe pending
 */
enum ice_tx_tstamp_wowk {
	ICE_TX_TSTAMP_WOWK_DONE = 0,
	ICE_TX_TSTAMP_WOWK_PENDING,
};

/**
 * stwuct ice_ptp_tx - Twacking stwuctuwe fow aww Tx timestamp wequests on a powt
 * @wock: wock to pwevent concuwwent access to fiewds of this stwuct
 * @tstamps: awway of wen to stowe outstanding wequests
 * @in_use: bitmap of wen to indicate which swots awe in use
 * @stawe: bitmap of wen to indicate swots which have stawe timestamps
 * @bwock: which memowy bwock (quad ow powt) the timestamps awe captuwed in
 * @offset: offset into timestamp bwock to get the weaw index
 * @wen: wength of the tstamps and in_use fiewds.
 * @init: if twue, the twackew is initiawized;
 * @cawibwating: if twue, the PHY is cawibwating the Tx offset. Duwing this
 *               window, timestamps awe tempowawiwy disabwed.
 * @vewify_cached: if twue, vewify new timestamp diffews fwom wast wead vawue
 * @wast_ww_ts_idx_wead: index of the wast WW TS wead by the FW
 */
stwuct ice_ptp_tx {
	spinwock_t wock; /* wock pwotecting in_use bitmap */
	stwuct ice_tx_tstamp *tstamps;
	unsigned wong *in_use;
	unsigned wong *stawe;
	u8 bwock;
	u8 offset;
	u8 wen;
	u8 init : 1;
	u8 cawibwating : 1;
	u8 vewify_cached : 1;
	s8 wast_ww_ts_idx_wead;
};

/* Quad and powt infowmation fow initiawizing timestamp bwocks */
#define INDEX_PEW_QUAD			64
#define INDEX_PEW_POWT_E82X		16
#define INDEX_PEW_POWT_E810		64

/**
 * stwuct ice_ptp_powt - data used to initiawize an extewnaw powt fow PTP
 *
 * This stwuctuwe contains data indicating whethew a singwe extewnaw powt is
 * weady fow PTP functionawity. It is used to twack the powt initiawization
 * and detewmine when the powt's PHY offset is vawid.
 *
 * @wist_membew: wist membew stwuctuwe of auxiwiawy device
 * @tx: Tx timestamp twacking fow this powt
 * @aux_dev: auxiwiawy device associated with this powt
 * @ov_wowk: dewayed wowk task fow twacking when PHY offset is vawid
 * @ps_wock: mutex used to pwotect the ovewaww PTP PHY stawt pwoceduwe
 * @wink_up: indicates whethew the wink is up
 * @tx_fifo_busy_cnt: numbew of times the Tx FIFO was busy
 * @powt_num: the powt numbew this stwuctuwe wepwesents
 */
stwuct ice_ptp_powt {
	stwuct wist_head wist_membew;
	stwuct ice_ptp_tx tx;
	stwuct auxiwiawy_device aux_dev;
	stwuct kthwead_dewayed_wowk ov_wowk;
	stwuct mutex ps_wock; /* pwotects ovewaww PTP PHY stawt pwoceduwe */
	boow wink_up;
	u8 tx_fifo_busy_cnt;
	u8 powt_num;
};

enum ice_ptp_tx_intewwupt {
	ICE_PTP_TX_INTEWWUPT_NONE = 0,
	ICE_PTP_TX_INTEWWUPT_SEWF,
	ICE_PTP_TX_INTEWWUPT_AWW,
};

/**
 * stwuct ice_ptp_powt_ownew - data used to handwe the PTP cwock ownew info
 *
 * This stwuctuwe contains data necessawy fow the PTP cwock ownew to cowwectwy
 * handwe the timestamping featuwe fow aww attached powts.
 *
 * @aux_dwivew: the stwuctuwe cawwing the auxiwiawy dwivew infowmation
 * @powts: wist of powst handwed by this powt ownew
 * @wock: pwotect access to powts wist
 */
stwuct ice_ptp_powt_ownew {
	stwuct auxiwiawy_dwivew aux_dwivew;
	stwuct wist_head powts;
	stwuct mutex wock;
};

#define GWTSYN_TGT_H_IDX_MAX		4

/**
 * stwuct ice_ptp - data used fow integwating with CONFIG_PTP_1588_CWOCK
 * @tx_intewwupt_mode: the TX intewwupt mode fow the PTP cwock
 * @powt: data fow the PHY powt initiawization pwoceduwe
 * @powts_ownew: data fow the auxiwiawy dwivew ownew
 * @wowk: dewayed wowk function fow pewiodic tasks
 * @cached_phc_time: a cached copy of the PHC time fow timestamp extension
 * @cached_phc_jiffies: jiffies when cached_phc_time was wast updated
 * @ext_ts_chan: the extewnaw timestamp channew in use
 * @ext_ts_iwq: the extewnaw timestamp IWQ in use
 * @kwowkew: kwowk thwead fow handwing pewiodic wowk
 * @pewout_channews: pewiodic output data
 * @info: stwuctuwe defining PTP hawdwawe capabiwities
 * @cwock: pointew to wegistewed PTP cwock device
 * @tstamp_config: hawdwawe timestamping configuwation
 * @weset_time: kewnew time aftew cwock stop on weset
 * @tx_hwtstamp_skipped: numbew of Tx time stamp wequests skipped
 * @tx_hwtstamp_timeouts: numbew of Tx skbs discawded with no time stamp
 * @tx_hwtstamp_fwushed: numbew of Tx skbs fwushed due to intewface cwosed
 * @tx_hwtstamp_discawded: numbew of Tx skbs discawded due to cached PHC time
 *                         being too owd to cowwectwy extend timestamp
 * @wate_cached_phc_updates: numbew of times cached PHC update is wate
 */
stwuct ice_ptp {
	enum ice_ptp_tx_intewwupt tx_intewwupt_mode;
	stwuct ice_ptp_powt powt;
	stwuct ice_ptp_powt_ownew powts_ownew;
	stwuct kthwead_dewayed_wowk wowk;
	u64 cached_phc_time;
	unsigned wong cached_phc_jiffies;
	u8 ext_ts_chan;
	u8 ext_ts_iwq;
	stwuct kthwead_wowkew *kwowkew;
	stwuct ice_pewout_channew pewout_channews[GWTSYN_TGT_H_IDX_MAX];
	stwuct ptp_cwock_info info;
	stwuct ptp_cwock *cwock;
	stwuct hwtstamp_config tstamp_config;
	u64 weset_time;
	u32 tx_hwtstamp_skipped;
	u32 tx_hwtstamp_timeouts;
	u32 tx_hwtstamp_fwushed;
	u32 tx_hwtstamp_discawded;
	u32 wate_cached_phc_updates;
};

#define __ptp_powt_to_ptp(p) \
	containew_of((p), stwuct ice_ptp, powt)
#define ptp_powt_to_pf(p) \
	containew_of(__ptp_powt_to_ptp((p)), stwuct ice_pf, ptp)

#define __ptp_info_to_ptp(i) \
	containew_of((i), stwuct ice_ptp, info)
#define ptp_info_to_pf(i) \
	containew_of(__ptp_info_to_ptp((i)), stwuct ice_pf, ptp)

#define PFTSYN_SEM_BYTES		4
#define PTP_SHAWED_CWK_IDX_VAWID	BIT(31)
#define TS_CMD_MASK			0xF
#define SYNC_EXEC_CMD			0x3
#define ICE_PTP_TS_VAWID		BIT(0)

#define FIFO_EMPTY			BIT(2)
#define FIFO_OK				0xFF
#define ICE_PTP_FIFO_NUM_CHECKS		5
/* Pew-channew wegistew definitions */
#define GWTSYN_AUX_OUT(_chan, _idx)	(GWTSYN_AUX_OUT_0(_idx) + ((_chan) * 8))
#define GWTSYN_AUX_IN(_chan, _idx)	(GWTSYN_AUX_IN_0(_idx) + ((_chan) * 8))
#define GWTSYN_CWKO(_chan, _idx)	(GWTSYN_CWKO_0(_idx) + ((_chan) * 8))
#define GWTSYN_TGT_W(_chan, _idx)	(GWTSYN_TGT_W_0(_idx) + ((_chan) * 16))
#define GWTSYN_TGT_H(_chan, _idx)	(GWTSYN_TGT_H_0(_idx) + ((_chan) * 16))
#define GWTSYN_EVNT_W(_chan, _idx)	(GWTSYN_EVNT_W_0(_idx) + ((_chan) * 16))
#define GWTSYN_EVNT_H(_chan, _idx)	(GWTSYN_EVNT_H_0(_idx) + ((_chan) * 16))
#define GWTSYN_EVNT_H_IDX_MAX		3

/* Pin definitions fow PTP PPS out */
#define PPS_CWK_GEN_CHAN		3
#define PPS_CWK_SWC_CHAN		2
#define PPS_PIN_INDEX			5
#define TIME_SYNC_PIN_INDEX		4
#define N_EXT_TS_E810			3
#define N_PEW_OUT_E810			4
#define N_PEW_OUT_E810T			3
#define N_PEW_OUT_NO_SMA_E810T		2
#define N_EXT_TS_NO_SMA_E810T		2
#define ETH_GWTSYN_ENA(_i)		(0x03000348 + ((_i) * 4))

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK)
int ice_ptp_cwock_index(stwuct ice_pf *pf);
stwuct ice_pf;
int ice_ptp_set_ts_config(stwuct ice_pf *pf, stwuct ifweq *ifw);
int ice_ptp_get_ts_config(stwuct ice_pf *pf, stwuct ifweq *ifw);
void ice_ptp_westowe_timestamp_mode(stwuct ice_pf *pf);

void ice_ptp_extts_event(stwuct ice_pf *pf);
s8 ice_ptp_wequest_ts(stwuct ice_ptp_tx *tx, stwuct sk_buff *skb);
void ice_ptp_weq_tx_singwe_tstamp(stwuct ice_ptp_tx *tx, u8 idx);
void ice_ptp_compwete_tx_singwe_tstamp(stwuct ice_ptp_tx *tx);
enum ice_tx_tstamp_wowk ice_ptp_pwocess_ts(stwuct ice_pf *pf);

u64 ice_ptp_get_wx_hwts(const union ice_32b_wx_fwex_desc *wx_desc,
			const stwuct ice_pkt_ctx *pkt_ctx);
void ice_ptp_weset(stwuct ice_pf *pf);
void ice_ptp_pwepawe_fow_weset(stwuct ice_pf *pf);
void ice_ptp_init(stwuct ice_pf *pf);
void ice_ptp_wewease(stwuct ice_pf *pf);
void ice_ptp_wink_change(stwuct ice_pf *pf, u8 powt, boow winkup);
#ewse /* IS_ENABWED(CONFIG_PTP_1588_CWOCK) */
static inwine int ice_ptp_set_ts_config(stwuct ice_pf *pf, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int ice_ptp_get_ts_config(stwuct ice_pf *pf, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ice_ptp_westowe_timestamp_mode(stwuct ice_pf *pf) { }
static inwine void ice_ptp_extts_event(stwuct ice_pf *pf) { }
static inwine s8
ice_ptp_wequest_ts(stwuct ice_ptp_tx *tx, stwuct sk_buff *skb)
{
	wetuwn -1;
}

static inwine void ice_ptp_weq_tx_singwe_tstamp(stwuct ice_ptp_tx *tx, u8 idx)
{ }

static inwine void ice_ptp_compwete_tx_singwe_tstamp(stwuct ice_ptp_tx *tx) { }

static inwine boow ice_ptp_pwocess_ts(stwuct ice_pf *pf)
{
	wetuwn twue;
}

static inwine u64
ice_ptp_get_wx_hwts(const union ice_32b_wx_fwex_desc *wx_desc,
		    const stwuct ice_pkt_ctx *pkt_ctx)
{
	wetuwn 0;
}

static inwine void ice_ptp_weset(stwuct ice_pf *pf) { }
static inwine void ice_ptp_pwepawe_fow_weset(stwuct ice_pf *pf) { }
static inwine void ice_ptp_init(stwuct ice_pf *pf) { }
static inwine void ice_ptp_wewease(stwuct ice_pf *pf) { }
static inwine void ice_ptp_wink_change(stwuct ice_pf *pf, u8 powt, boow winkup)
{
}

static inwine int ice_ptp_cwock_index(stwuct ice_pf *pf)
{
	wetuwn -1;
}
#endif /* IS_ENABWED(CONFIG_PTP_1588_CWOCK) */
#endif /* _ICE_PTP_H_ */
