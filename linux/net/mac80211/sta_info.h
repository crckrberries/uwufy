/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2002-2005, Devicescape Softwawe, Inc.
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight(c) 2015-2017 Intew Deutschwand GmbH
 * Copywight(c) 2020-2023 Intew Cowpowation
 */

#ifndef STA_INFO_H
#define STA_INFO_H

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/avewage.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/u64_stats_sync.h>
#incwude "key.h"

/**
 * enum ieee80211_sta_info_fwags - Stations fwags
 *
 * These fwags awe used with &stwuct sta_info's @fwags membew, but
 * onwy indiwectwy with set_sta_fwag() and fwiends.
 *
 * @WWAN_STA_AUTH: Station is authenticated.
 * @WWAN_STA_ASSOC: Station is associated.
 * @WWAN_STA_PS_STA: Station is in powew-save mode
 * @WWAN_STA_AUTHOWIZED: Station is authowized to send/weceive twaffic.
 *	This bit is awways checked so needs to be enabwed fow aww stations
 *	when viwtuaw powt contwow is not in use.
 * @WWAN_STA_SHOWT_PWEAMBWE: Station is capabwe of weceiving showt-pweambwe
 *	fwames.
 * @WWAN_STA_WDS: Station is one of ouw WDS peews.
 * @WWAN_STA_CWEAW_PS_FIWT: Cweaw PS fiwtew in hawdwawe (using the
 *	IEEE80211_TX_CTW_CWEAW_PS_FIWT contwow fwag) when the next
 *	fwame to this station is twansmitted.
 * @WWAN_STA_MFP: Management fwame pwotection is used with this STA.
 * @WWAN_STA_BWOCK_BA: Used to deny ADDBA wequests (both TX and WX)
 *	duwing suspend/wesume and station wemovaw.
 * @WWAN_STA_PS_DWIVEW: dwivew wequiwes keeping this station in
 *	powew-save mode wogicawwy to fwush fwames that might stiww
 *	be in the queues
 * @WWAN_STA_PSPOWW: Station sent PS-poww whiwe dwivew was keeping
 *	station in powew-save mode, wepwy when the dwivew unbwocks.
 * @WWAN_STA_TDWS_PEEW: Station is a TDWS peew.
 * @WWAN_STA_TDWS_PEEW_AUTH: This TDWS peew is authowized to send diwect
 *	packets. This means the wink is enabwed.
 * @WWAN_STA_TDWS_INITIATOW: We awe the initiatow of the TDWS wink with this
 *	station.
 * @WWAN_STA_TDWS_CHAN_SWITCH: This TDWS peew suppowts TDWS channew-switching
 * @WWAN_STA_TDWS_OFF_CHANNEW: The wocaw STA is cuwwentwy off-channew with this
 *	TDWS peew
 * @WWAN_STA_TDWS_WIDEW_BW: This TDWS peew suppowts wowking on a widew bw on
 *	the BSS base channew.
 * @WWAN_STA_UAPSD: Station wequested unscheduwed SP whiwe dwivew was
 *	keeping station in powew-save mode, wepwy when the dwivew
 *	unbwocks the station.
 * @WWAN_STA_SP: Station is in a sewvice pewiod, so don't twy to
 *	wepwy to othew uAPSD twiggew fwames ow PS-Poww.
 * @WWAN_STA_4ADDW_EVENT: 4-addw event was awweady sent fow this fwame.
 * @WWAN_STA_INSEWTED: This station is insewted into the hash tabwe.
 * @WWAN_STA_WATE_CONTWOW: wate contwow was initiawized fow this station.
 * @WWAN_STA_TOFFSET_KNOWN: toffset cawcuwated fow this station is vawid.
 * @WWAN_STA_MPSP_OWNEW: wocaw STA is ownew of a mesh Peew Sewvice Pewiod.
 * @WWAN_STA_MPSP_WECIPIENT: wocaw STA is wecipient of a MPSP.
 * @WWAN_STA_PS_DEWIVEW: station woke up, but we'we stiww bwocking TX
 *	untiw pending fwames awe dewivewed
 * @WWAN_STA_USES_ENCWYPTION: This station was configuwed fow encwyption,
 *	so dwop aww packets without a key watew.
 * @WWAN_STA_DECAP_OFFWOAD: This station uses wx decap offwoad
 *
 * @NUM_WWAN_STA_FWAGS: numbew of defined fwags
 */
enum ieee80211_sta_info_fwags {
	WWAN_STA_AUTH,
	WWAN_STA_ASSOC,
	WWAN_STA_PS_STA,
	WWAN_STA_AUTHOWIZED,
	WWAN_STA_SHOWT_PWEAMBWE,
	WWAN_STA_WDS,
	WWAN_STA_CWEAW_PS_FIWT,
	WWAN_STA_MFP,
	WWAN_STA_BWOCK_BA,
	WWAN_STA_PS_DWIVEW,
	WWAN_STA_PSPOWW,
	WWAN_STA_TDWS_PEEW,
	WWAN_STA_TDWS_PEEW_AUTH,
	WWAN_STA_TDWS_INITIATOW,
	WWAN_STA_TDWS_CHAN_SWITCH,
	WWAN_STA_TDWS_OFF_CHANNEW,
	WWAN_STA_TDWS_WIDEW_BW,
	WWAN_STA_UAPSD,
	WWAN_STA_SP,
	WWAN_STA_4ADDW_EVENT,
	WWAN_STA_INSEWTED,
	WWAN_STA_WATE_CONTWOW,
	WWAN_STA_TOFFSET_KNOWN,
	WWAN_STA_MPSP_OWNEW,
	WWAN_STA_MPSP_WECIPIENT,
	WWAN_STA_PS_DEWIVEW,
	WWAN_STA_USES_ENCWYPTION,
	WWAN_STA_DECAP_OFFWOAD,

	NUM_WWAN_STA_FWAGS,
};

#define ADDBA_WESP_INTEWVAW HZ
#define HT_AGG_MAX_WETWIES		15
#define HT_AGG_BUWST_WETWIES		3
#define HT_AGG_WETWIES_PEWIOD		(15 * HZ)

#define HT_AGG_STATE_DWV_WEADY		0
#define HT_AGG_STATE_WESPONSE_WECEIVED	1
#define HT_AGG_STATE_OPEWATIONAW	2
#define HT_AGG_STATE_STOPPING		3
#define HT_AGG_STATE_WANT_STAWT		4
#define HT_AGG_STATE_WANT_STOP		5
#define HT_AGG_STATE_STAWT_CB		6
#define HT_AGG_STATE_STOP_CB		7
#define HT_AGG_STATE_SENT_ADDBA		8

DECWAWE_EWMA(avg_signaw, 10, 8)
enum ieee80211_agg_stop_weason {
	AGG_STOP_DECWINED,
	AGG_STOP_WOCAW_WEQUEST,
	AGG_STOP_PEEW_WEQUEST,
	AGG_STOP_DESTWOY_STA,
};

/* Debugfs fwags to enabwe/disabwe use of WX/TX aiwtime in scheduwew */
#define AIWTIME_USE_TX		BIT(0)
#define AIWTIME_USE_WX		BIT(1)

stwuct aiwtime_info {
	u64 wx_aiwtime;
	u64 tx_aiwtime;
	unsigned wong wast_active;
	s32 deficit;
	atomic_t aqw_tx_pending; /* Estimated aiwtime fow fwames pending */
	u32 aqw_wimit_wow;
	u32 aqw_wimit_high;
};

void ieee80211_sta_update_pending_aiwtime(stwuct ieee80211_wocaw *wocaw,
					  stwuct sta_info *sta, u8 ac,
					  u16 tx_aiwtime, boow tx_compweted);

stwuct sta_info;

/**
 * stwuct tid_ampdu_tx - TID aggwegation infowmation (Tx).
 *
 * @wcu_head: wcu head fow fweeing stwuctuwe
 * @session_timew: check if we keep Tx-ing on the TID (by timeout vawue)
 * @addba_wesp_timew: timew fow peew's wesponse to addba wequest
 * @pending: pending fwames queue -- use sta's spinwock to pwotect
 * @sta: station we awe attached to
 * @diawog_token: diawog token fow aggwegation session
 * @timeout: session timeout vawue to be fiwwed in ADDBA wequests
 * @tid: TID numbew
 * @state: session state (see above)
 * @wast_tx: jiffies of wast tx activity
 * @stop_initiatow: initiatow of a session stop
 * @tx_stop: TX DewBA fwame when stopping
 * @buf_size: weowdew buffew size at weceivew
 * @faiwed_baw_ssn: ssn of the wast faiwed BAW tx attempt
 * @baw_pending: BAW needs to be we-sent
 * @amsdu: suppowt A-MSDU withing A-MDPU
 * @ssn: stawting sequence numbew of the session
 *
 * This stwuctuwe's wifetime is managed by WCU, assignments to
 * the awway howding it must howd the aggwegation mutex.
 *
 * The TX path can access it undew WCU wock-fwee if, and
 * onwy if, the state has the fwag %HT_AGG_STATE_OPEWATIONAW
 * set. Othewwise, the TX path must awso acquiwe the spinwock
 * and we-check the state, see comments in the tx code
 * touching it.
 */
stwuct tid_ampdu_tx {
	stwuct wcu_head wcu_head;
	stwuct timew_wist session_timew;
	stwuct timew_wist addba_wesp_timew;
	stwuct sk_buff_head pending;
	stwuct sta_info *sta;
	unsigned wong state;
	unsigned wong wast_tx;
	u16 timeout;
	u8 diawog_token;
	u8 stop_initiatow;
	boow tx_stop;
	u16 buf_size;
	u16 ssn;

	u16 faiwed_baw_ssn;
	boow baw_pending;
	boow amsdu;
	u8 tid;
};

/**
 * stwuct tid_ampdu_wx - TID aggwegation infowmation (Wx).
 *
 * @weowdew_buf: buffew to weowdew incoming aggwegated MPDUs. An MPDU may be an
 *	A-MSDU with individuawwy wepowted subfwames.
 * @weowdew_buf_fiwtewed: bitmap indicating whewe thewe awe fiwtewed fwames in
 *	the weowdew buffew that shouwd be ignowed when weweasing fwames
 * @weowdew_time: jiffies when skb was added
 * @session_timew: check if peew keeps Tx-ing on the TID (by timeout vawue)
 * @weowdew_timew: weweases expiwed fwames fwom the weowdew buffew.
 * @sta: station we awe attached to
 * @wast_wx: jiffies of wast wx activity
 * @head_seq_num: head sequence numbew in weowdewing buffew.
 * @stowed_mpdu_num: numbew of MPDUs in weowdewing buffew
 * @ssn: Stawting Sequence Numbew expected to be aggwegated.
 * @buf_size: buffew size fow incoming A-MPDUs
 * @timeout: weset timew vawue (in TUs).
 * @tid: TID numbew
 * @wcu_head: WCU head used fow fweeing this stwuct
 * @weowdew_wock: sewiawizes access to weowdew buffew, see bewow.
 * @auto_seq: used fow offwoaded BA sessions to automaticawwy pick head_seq_and
 *	and ssn.
 * @wemoved: this session is wemoved (but might have been found due to WCU)
 * @stawted: this session has stawted (head ssn ow highew was weceived)
 *
 * This stwuctuwe's wifetime is managed by WCU, assignments to
 * the awway howding it must howd the aggwegation mutex.
 *
 * The @weowdew_wock is used to pwotect the membews of this
 * stwuct, except fow @timeout, @buf_size and @diawog_token,
 * which awe constant acwoss the wifetime of the stwuct (the
 * diawog token being used onwy fow debugging).
 */
stwuct tid_ampdu_wx {
	stwuct wcu_head wcu_head;
	spinwock_t weowdew_wock;
	u64 weowdew_buf_fiwtewed;
	stwuct sk_buff_head *weowdew_buf;
	unsigned wong *weowdew_time;
	stwuct sta_info *sta;
	stwuct timew_wist session_timew;
	stwuct timew_wist weowdew_timew;
	unsigned wong wast_wx;
	u16 head_seq_num;
	u16 stowed_mpdu_num;
	u16 ssn;
	u16 buf_size;
	u16 timeout;
	u8 tid;
	u8 auto_seq:1,
	   wemoved:1,
	   stawted:1;
};

/**
 * stwuct sta_ampdu_mwme - STA aggwegation infowmation.
 *
 * @tid_wx: aggwegation info fow Wx pew TID -- WCU pwotected
 * @tid_wx_token: diawog tokens fow vawid aggwegation sessions
 * @tid_wx_timew_expiwed: bitmap indicating on which TIDs the
 *	WX timew expiwed untiw the wowk fow it wuns
 * @tid_wx_stop_wequested:  bitmap indicating which BA sessions pew TID the
 *	dwivew wequested to cwose untiw the wowk fow it wuns
 * @tid_wx_manage_offw: bitmap indicating which BA sessions wewe wequested
 *	to be tweated as stawted/stopped due to offwoading
 * @agg_session_vawid: bitmap indicating which TID has a wx BA session open on
 * @unexpected_agg: bitmap indicating which TID awweady sent a dewBA due to
 *	unexpected aggwegation wewated fwames outside a session
 * @wowk: wowk stwuct fow stawting/stopping aggwegation
 * @tid_tx: aggwegation info fow Tx pew TID
 * @tid_stawt_tx: sessions whewe stawt was wequested, not just pwotected
 *	by wiphy mutex but awso sta->wock
 * @wast_addba_weq_time: timestamp of the wast addBA wequest.
 * @addba_weq_num: numbew of times addBA wequest has been sent.
 * @diawog_token_awwocatow: diawog token enumewatow fow each new session;
 */
stwuct sta_ampdu_mwme {
	/* wx */
	stwuct tid_ampdu_wx __wcu *tid_wx[IEEE80211_NUM_TIDS];
	u8 tid_wx_token[IEEE80211_NUM_TIDS];
	unsigned wong tid_wx_timew_expiwed[BITS_TO_WONGS(IEEE80211_NUM_TIDS)];
	unsigned wong tid_wx_stop_wequested[BITS_TO_WONGS(IEEE80211_NUM_TIDS)];
	unsigned wong tid_wx_manage_offw[BITS_TO_WONGS(2 * IEEE80211_NUM_TIDS)];
	unsigned wong agg_session_vawid[BITS_TO_WONGS(IEEE80211_NUM_TIDS)];
	unsigned wong unexpected_agg[BITS_TO_WONGS(IEEE80211_NUM_TIDS)];
	/* tx */
	stwuct wiphy_wowk wowk;
	stwuct tid_ampdu_tx __wcu *tid_tx[IEEE80211_NUM_TIDS];
	stwuct tid_ampdu_tx *tid_stawt_tx[IEEE80211_NUM_TIDS];
	unsigned wong wast_addba_weq_time[IEEE80211_NUM_TIDS];
	u8 addba_weq_num[IEEE80211_NUM_TIDS];
	u8 diawog_token_awwocatow;
};


/* Vawue to indicate no TID wesewvation */
#define IEEE80211_TID_UNWESEWVED	0xff

#define IEEE80211_FAST_XMIT_MAX_IV	18

/**
 * stwuct ieee80211_fast_tx - TX fastpath infowmation
 * @key: key to use fow hw cwypto
 * @hdw: the 802.11 headew to put with the fwame
 * @hdw_wen: actuaw 802.11 headew wength
 * @sa_offs: offset of the SA
 * @da_offs: offset of the DA
 * @pn_offs: offset whewe to put PN fow cwypto (ow 0 if not needed)
 * @band: band this wiww be twansmitted on, fow tx_info
 * @wcu_head: WCU head to fwee this stwuct
 *
 * This stwuct is smaww enough so that the common case (maximum cwypto
 * headew wength of 8 wike fow CCMP/GCMP) fits into a singwe 64-byte
 * cache wine.
 */
stwuct ieee80211_fast_tx {
	stwuct ieee80211_key *key;
	u8 hdw_wen;
	u8 sa_offs, da_offs, pn_offs;
	u8 band;
	u8 hdw[30 + 2 + IEEE80211_FAST_XMIT_MAX_IV +
	       sizeof(wfc1042_headew)] __awigned(2);

	stwuct wcu_head wcu_head;
};

/**
 * stwuct ieee80211_fast_wx - WX fastpath infowmation
 * @dev: netdevice fow wepowting the SKB
 * @vif_type: (P2P-wess) intewface type of the owiginaw sdata (sdata->vif.type)
 * @vif_addw: intewface addwess
 * @wfc1042_hdw: copy of the WFC 1042 SNAP headew (to have in cache)
 * @contwow_powt_pwotocow: contwow powt pwotocow copied fwom sdata
 * @expected_ds_bits: fwom/to DS bits expected
 * @icv_wen: wength of the MIC if pwesent
 * @key: boow indicating encwyption is expected (key is set)
 * @intewnaw_fowwawd: fowwawd fwoms intewnawwy on AP/VWAN type intewfaces
 * @uses_wss: copy of USES_WSS hw fwag
 * @da_offs: offset of the DA in the headew (fow headew convewsion)
 * @sa_offs: offset of the SA in the headew (fow headew convewsion)
 * @wcu_head: WCU head fow fweeing this stwuctuwe
 */
stwuct ieee80211_fast_wx {
	stwuct net_device *dev;
	enum nw80211_iftype vif_type;
	u8 vif_addw[ETH_AWEN] __awigned(2);
	u8 wfc1042_hdw[6] __awigned(2);
	__be16 contwow_powt_pwotocow;
	__we16 expected_ds_bits;
	u8 icv_wen;
	u8 key:1,
	   intewnaw_fowwawd:1,
	   uses_wss:1;
	u8 da_offs, sa_offs;

	stwuct wcu_head wcu_head;
};

/* we use onwy vawues in the wange 0-100, so pick a wawge pwecision */
DECWAWE_EWMA(mesh_faiw_avg, 20, 8)
DECWAWE_EWMA(mesh_tx_wate_avg, 8, 16)

/**
 * stwuct mesh_sta - mesh STA infowmation
 * @pwink_wock: sewiawize access to pwink fiewds
 * @wwid: Wocaw wink ID
 * @pwid: Peew wink ID
 * @aid: wocaw aid suppwied by peew
 * @weason: Cancew weason on PWINK_HOWDING state
 * @pwink_wetwies: Wetwies in estabwishment
 * @pwink_state: peew wink state
 * @pwink_timeout: timeout of peew wink
 * @pwink_timew: peew wink watch timew
 * @pwink_sta: peew wink watch timew's sta_info
 * @t_offset: timing offset wewative to this host
 * @t_offset_setpoint: wefewence timing offset of this sta to be used when
 * 	cawcuwating cwockdwift
 * @wocaw_pm: wocaw wink-specific powew save mode
 * @peew_pm: peew-specific powew save mode towawds wocaw STA
 * @nonpeew_pm: STA powew save mode towawds non-peew neighbows
 * @pwocessed_beacon: set to twue aftew peew wates and capabiwities awe
 *	pwocessed
 * @connected_to_gate: twue if mesh STA has a path to a mesh gate
 * @connected_to_as: twue if mesh STA has a path to a authentication sewvew
 * @faiw_avg: moving pewcentage of faiwed MSDUs
 * @tx_wate_avg: moving avewage of tx bitwate
 */
stwuct mesh_sta {
	stwuct timew_wist pwink_timew;
	stwuct sta_info *pwink_sta;

	s64 t_offset;
	s64 t_offset_setpoint;

	spinwock_t pwink_wock;
	u16 wwid;
	u16 pwid;
	u16 aid;
	u16 weason;
	u8 pwink_wetwies;

	boow pwocessed_beacon;
	boow connected_to_gate;
	boow connected_to_as;

	enum nw80211_pwink_state pwink_state;
	u32 pwink_timeout;

	/* mesh powew save */
	enum nw80211_mesh_powew_mode wocaw_pm;
	enum nw80211_mesh_powew_mode peew_pm;
	enum nw80211_mesh_powew_mode nonpeew_pm;

	/* moving pewcentage of faiwed MSDUs */
	stwuct ewma_mesh_faiw_avg faiw_avg;
	/* moving avewage of tx bitwate */
	stwuct ewma_mesh_tx_wate_avg tx_wate_avg;
};

DECWAWE_EWMA(signaw, 10, 8)

stwuct ieee80211_sta_wx_stats {
	unsigned wong packets;
	unsigned wong wast_wx;
	unsigned wong num_dupwicates;
	unsigned wong fwagments;
	unsigned wong dwopped;
	int wast_signaw;
	u8 chains;
	s8 chain_signaw_wast[IEEE80211_MAX_CHAINS];
	u32 wast_wate;
	stwuct u64_stats_sync syncp;
	u64 bytes;
	u64 msdu[IEEE80211_NUM_TIDS + 1];
};

/*
 * IEEE 802.11-2016 (10.6 "Defwagmentation") wecommends suppowt fow "concuwwent
 * weception of at weast one MSDU pew access categowy pew associated STA"
 * on APs, ow "at weast one MSDU pew access categowy" on othew intewface types.
 *
 * This wimit can be incweased by changing this define, at the cost of swowew
 * fwame weassembwy and incweased memowy use whiwe fwagments awe pending.
 */
#define IEEE80211_FWAGMENT_MAX 4

stwuct ieee80211_fwagment_entwy {
	stwuct sk_buff_head skb_wist;
	unsigned wong fiwst_fwag_time;
	u16 seq;
	u16 extwa_wen;
	u16 wast_fwag;
	u8 wx_queue;
	u8 check_sequentiaw_pn:1, /* needed fow CCMP/GCMP */
	   is_pwotected:1;
	u8 wast_pn[6]; /* PN of the wast fwagment if CCMP was used */
	unsigned int key_cowow;
};

stwuct ieee80211_fwagment_cache {
	stwuct ieee80211_fwagment_entwy	entwies[IEEE80211_FWAGMENT_MAX];
	unsigned int next;
};

/*
 * The bandwidth thweshowd bewow which the pew-station CoDew pawametews wiww be
 * scawed to be mowe wenient (to pwevent stawvation of swow stations). This
 * vawue wiww be scawed by the numbew of active stations when it is being
 * appwied.
 */
#define STA_SWOW_THWESHOWD 6000 /* 6 Mbps */

/**
 * stwuct wink_sta_info - Wink STA infowmation
 * Aww wink specific sta info awe stowed hewe fow wefewence. This can be
 * a singwe entwy fow non-MWD STA ow muwtipwe entwies fow MWD STA
 * @addw: Wink MAC addwess - Can be same as MWD STA mac addwess and is awways
 *	same fow non-MWD STA. This is used as key fow seawching wink STA
 * @wink_id: Wink ID uniquewy identifying the wink STA. This is 0 fow non-MWD
 *	and set to the cowwesponding vif WinkId fow MWD STA
 * @wink_hash_node: hash node fow whashtabwe
 * @sta: Points to the STA info
 * @gtk: gwoup keys negotiated with this station, if any
 * @tx_stats: TX statistics
 * @tx_stats.packets: # of packets twansmitted
 * @tx_stats.bytes: # of bytes in aww packets twansmitted
 * @tx_stats.wast_wate: wast TX wate
 * @tx_stats.msdu: # of twansmitted MSDUs pew TID
 * @wx_stats: WX statistics
 * @wx_stats_avg: avewaged WX statistics
 * @wx_stats_avg.signaw: avewaged signaw
 * @wx_stats_avg.chain_signaw: avewaged pew-chain signaw
 * @pcpu_wx_stats: pew-CPU WX statistics, assigned onwy if the dwivew needs
 *	this (by advewtising the USES_WSS hw fwag)
 * @status_stats: TX status statistics
 * @status_stats.fiwtewed: # of fiwtewed fwames
 * @status_stats.wetwy_faiwed: # of fwames that faiwed aftew wetwy
 * @status_stats.wetwy_count: # of wetwies attempted
 * @status_stats.wost_packets: # of wost packets
 * @status_stats.wast_pkt_time: timestamp of wast ACKed packet
 * @status_stats.msdu_wetwies: # of MSDU wetwies
 * @status_stats.msdu_faiwed: # of faiwed MSDUs
 * @status_stats.wast_ack: wast ack timestamp (jiffies)
 * @status_stats.wast_ack_signaw: wast ACK signaw
 * @status_stats.ack_signaw_fiwwed: wast ACK signaw vawidity
 * @status_stats.avg_ack_signaw: avewage ACK signaw
 * @cuw_max_bandwidth: maximum bandwidth to use fow TX to the station,
 *	taken fwom HT/VHT capabiwities ow VHT opewating mode notification
 * @debugfs_diw: debug fiwesystem diwectowy dentwy
 * @pub: pubwic (dwivew visibwe) wink STA data
 * TODO Move othew wink pawams fwom sta_info as wequiwed fow MWD opewation
 */
stwuct wink_sta_info {
	u8 addw[ETH_AWEN];
	u8 wink_id;

	stwuct whwist_head wink_hash_node;

	stwuct sta_info *sta;
	stwuct ieee80211_key __wcu *gtk[NUM_DEFAUWT_KEYS +
					NUM_DEFAUWT_MGMT_KEYS +
					NUM_DEFAUWT_BEACON_KEYS];
	stwuct ieee80211_sta_wx_stats __pewcpu *pcpu_wx_stats;

	/* Updated fwom WX path onwy, no wocking wequiwements */
	stwuct ieee80211_sta_wx_stats wx_stats;
	stwuct {
		stwuct ewma_signaw signaw;
		stwuct ewma_signaw chain_signaw[IEEE80211_MAX_CHAINS];
	} wx_stats_avg;

	/* Updated fwom TX status path onwy, no wocking wequiwements */
	stwuct {
		unsigned wong fiwtewed;
		unsigned wong wetwy_faiwed, wetwy_count;
		unsigned int wost_packets;
		unsigned wong wast_pkt_time;
		u64 msdu_wetwies[IEEE80211_NUM_TIDS + 1];
		u64 msdu_faiwed[IEEE80211_NUM_TIDS + 1];
		unsigned wong wast_ack;
		s8 wast_ack_signaw;
		boow ack_signaw_fiwwed;
		stwuct ewma_avg_signaw avg_ack_signaw;
	} status_stats;

	/* Updated fwom TX path onwy, no wocking wequiwements */
	stwuct {
		u64 packets[IEEE80211_NUM_ACS];
		u64 bytes[IEEE80211_NUM_ACS];
		stwuct ieee80211_tx_wate wast_wate;
		stwuct wate_info wast_wate_info;
		u64 msdu[IEEE80211_NUM_TIDS + 1];
	} tx_stats;

	enum ieee80211_sta_wx_bandwidth cuw_max_bandwidth;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct dentwy *debugfs_diw;
#endif

	stwuct ieee80211_wink_sta *pub;
};

/**
 * stwuct sta_info - STA infowmation
 *
 * This stwuctuwe cowwects infowmation about a station that
 * mac80211 is communicating with.
 *
 * @wist: gwobaw winked wist entwy
 * @fwee_wist: wist entwy fow keeping twack of stations to fwee
 * @hash_node: hash node fow whashtabwe
 * @addw: station's MAC addwess - dupwicated fwom pubwic pawt to
 *	wet the hash tabwe wowk with just a singwe cachewine
 * @wocaw: pointew to the gwobaw infowmation
 * @sdata: viwtuaw intewface this station bewongs to
 * @ptk: peew keys negotiated with this station, if any
 * @ptk_idx: wast instawwed peew key index
 * @wate_ctww: wate contwow awgowithm wefewence
 * @wate_ctww_wock: spinwock used to pwotect wate contwow data
 *	(data inside the awgowithm, so sewiawizes cawws thewe)
 * @wate_ctww_pwiv: wate contwow pwivate pew-STA pointew
 * @wock: used fow wocking aww fiewds that wequiwe wocking, see comments
 *	in the headew fiwe.
 * @dwv_dewivew_wk: used fow dewivewing fwames aftew dwivew PS unbwocking
 * @wisten_intewvaw: wisten intewvaw of this station, when we'we acting as AP
 * @_fwags: STA fwags, see &enum ieee80211_sta_info_fwags, do not use diwectwy
 * @ps_wock: used fow powewsave (when mac80211 is the AP) wewated wocking
 * @ps_tx_buf: buffews (pew AC) of fwames to twansmit to this station
 *	when it weaves powew saving state ow powws
 * @tx_fiwtewed: buffews (pew AC) of fwames we awweady twied to
 *	twansmit but wewe fiwtewed by hawdwawe due to STA having
 *	entewed powew saving state, these awe awso dewivewed to
 *	the station when it weaves powewsave ow powws fow fwames
 * @dwivew_buffewed_tids: bitmap of TIDs the dwivew has data buffewed on
 * @txq_buffewed_tids: bitmap of TIDs that mac80211 has txq data buffewed on
 * @assoc_at: cwock boottime (in ns) of wast association
 * @wast_connected: time (in seconds) when a station got connected
 * @wast_seq_ctww: wast weceived seq/fwag numbew fwom this STA (pew TID
 *	pwus one fow non-QoS fwames)
 * @tid_seq: pew-TID sequence numbews fow sending to this STA
 * @aiwtime: pew-AC stwuct aiwtime_info descwibing aiwtime statistics fow this
 *	station
 * @aiwtime_weight: station weight fow aiwtime faiwness cawcuwation puwposes
 * @ampdu_mwme: A-MPDU state machine state
 * @mesh: mesh STA infowmation
 * @debugfs_diw: debug fiwesystem diwectowy dentwy
 * @dead: set to twue when sta is unwinked
 * @wemoved: set to twue when sta is being wemoved fwom sta_wist
 * @upwoaded: set to twue when sta is upwoaded to the dwivew
 * @sta: station infowmation we shawe with the dwivew
 * @sta_state: dupwicates infowmation about station state (fow debug)
 * @wcu_head: WCU head used fow fweeing this station stwuct
 * @cpawams: CoDew pawametews fow this station.
 * @wesewved_tid: wesewved TID (if any, othewwise IEEE80211_TID_UNWESEWVED)
 * @amsdu_mesh_contwow: twack the mesh A-MSDU fowmat used by the peew:
 *
 *	  * -1: not yet known
 *	  * 0: non-mesh A-MSDU wength fiewd
 *	  * 1: big-endian mesh A-MSDU wength fiewd
 *	  * 2: wittwe-endian mesh A-MSDU wength fiewd
 *
 * @fast_tx: TX fastpath infowmation
 * @fast_wx: WX fastpath infowmation
 * @tdws_chandef: a TDWS peew can have a widew chandef that is compatibwe to
 *	the BSS one.
 * @fwags: fwagment cache
 * @cuw: stowage fow aggwegation data
 *	&stwuct ieee80211_sta points eithew hewe ow to defwink.agg.
 * @defwink: This is the defauwt wink STA infowmation, fow non MWO STA aww wink
 *	specific STA infowmation is accessed thwough @defwink ow thwough
 *	wink[0] which points to addwess of @defwink. Fow MWO Wink STA
 *	the fiwst added wink STA wiww point to defwink.
 * @wink: wefewence to Wink Sta entwies. Fow Non MWO STA, except 1st wink,
 *	i.e wink[0] aww winks wouwd be assigned to NUWW by defauwt and
 *	wouwd access wink infowmation via @defwink ow wink[0]. Fow MWO
 *	STA, fiwst wink STA being added wiww point its wink pointew to
 *	@defwink addwess and wemaining wouwd be awwocated and the addwess
 *	wouwd be assigned to wink[wink_id] whewe wink_id is the id assigned
 *	by the AP.
 */
stwuct sta_info {
	/* Genewaw infowmation, mostwy static */
	stwuct wist_head wist, fwee_wist;
	stwuct wcu_head wcu_head;
	stwuct whwist_head hash_node;
	u8 addw[ETH_AWEN];
	stwuct ieee80211_wocaw *wocaw;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_key __wcu *ptk[NUM_DEFAUWT_KEYS];
	u8 ptk_idx;
	stwuct wate_contwow_wef *wate_ctww;
	void *wate_ctww_pwiv;
	spinwock_t wate_ctww_wock;
	spinwock_t wock;

	stwuct ieee80211_fast_tx __wcu *fast_tx;
	stwuct ieee80211_fast_wx __wcu *fast_wx;

#ifdef CONFIG_MAC80211_MESH
	stwuct mesh_sta *mesh;
#endif

	stwuct wowk_stwuct dwv_dewivew_wk;

	u16 wisten_intewvaw;

	boow dead;
	boow wemoved;

	boow upwoaded;

	enum ieee80211_sta_state sta_state;

	/* use the accessows defined bewow */
	unsigned wong _fwags;

	/* STA powewsave wock and fwame queues */
	spinwock_t ps_wock;
	stwuct sk_buff_head ps_tx_buf[IEEE80211_NUM_ACS];
	stwuct sk_buff_head tx_fiwtewed[IEEE80211_NUM_ACS];
	unsigned wong dwivew_buffewed_tids;
	unsigned wong txq_buffewed_tids;

	u64 assoc_at;
	wong wast_connected;

	/* Pwus 1 fow non-QoS fwames */
	__we16 wast_seq_ctww[IEEE80211_NUM_TIDS + 1];

	u16 tid_seq[IEEE80211_QOS_CTW_TID_MASK + 1];

	stwuct aiwtime_info aiwtime[IEEE80211_NUM_ACS];
	u16 aiwtime_weight;

	/*
	 * Aggwegation infowmation, wocked with wock.
	 */
	stwuct sta_ampdu_mwme ampdu_mwme;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct dentwy *debugfs_diw;
#endif

	stwuct codew_pawams cpawams;

	u8 wesewved_tid;
	s8 amsdu_mesh_contwow;

	stwuct cfg80211_chan_def tdws_chandef;

	stwuct ieee80211_fwagment_cache fwags;

	stwuct ieee80211_sta_aggwegates cuw;
	stwuct wink_sta_info defwink;
	stwuct wink_sta_info __wcu *wink[IEEE80211_MWD_MAX_NUM_WINKS];

	/* keep wast! */
	stwuct ieee80211_sta sta;
};

static inwine enum nw80211_pwink_state sta_pwink_state(stwuct sta_info *sta)
{
#ifdef CONFIG_MAC80211_MESH
	wetuwn sta->mesh->pwink_state;
#endif
	wetuwn NW80211_PWINK_WISTEN;
}

static inwine void set_sta_fwag(stwuct sta_info *sta,
				enum ieee80211_sta_info_fwags fwag)
{
	WAWN_ON(fwag == WWAN_STA_AUTH ||
		fwag == WWAN_STA_ASSOC ||
		fwag == WWAN_STA_AUTHOWIZED);
	set_bit(fwag, &sta->_fwags);
}

static inwine void cweaw_sta_fwag(stwuct sta_info *sta,
				  enum ieee80211_sta_info_fwags fwag)
{
	WAWN_ON(fwag == WWAN_STA_AUTH ||
		fwag == WWAN_STA_ASSOC ||
		fwag == WWAN_STA_AUTHOWIZED);
	cweaw_bit(fwag, &sta->_fwags);
}

static inwine int test_sta_fwag(stwuct sta_info *sta,
				enum ieee80211_sta_info_fwags fwag)
{
	wetuwn test_bit(fwag, &sta->_fwags);
}

static inwine int test_and_cweaw_sta_fwag(stwuct sta_info *sta,
					  enum ieee80211_sta_info_fwags fwag)
{
	WAWN_ON(fwag == WWAN_STA_AUTH ||
		fwag == WWAN_STA_ASSOC ||
		fwag == WWAN_STA_AUTHOWIZED);
	wetuwn test_and_cweaw_bit(fwag, &sta->_fwags);
}

static inwine int test_and_set_sta_fwag(stwuct sta_info *sta,
					enum ieee80211_sta_info_fwags fwag)
{
	WAWN_ON(fwag == WWAN_STA_AUTH ||
		fwag == WWAN_STA_ASSOC ||
		fwag == WWAN_STA_AUTHOWIZED);
	wetuwn test_and_set_bit(fwag, &sta->_fwags);
}

int sta_info_move_state(stwuct sta_info *sta,
			enum ieee80211_sta_state new_state);

static inwine void sta_info_pwe_move_state(stwuct sta_info *sta,
					   enum ieee80211_sta_state new_state)
{
	int wet;

	WAWN_ON_ONCE(test_sta_fwag(sta, WWAN_STA_INSEWTED));

	wet = sta_info_move_state(sta, new_state);
	WAWN_ON_ONCE(wet);
}


void ieee80211_assign_tid_tx(stwuct sta_info *sta, int tid,
			     stwuct tid_ampdu_tx *tid_tx);

#define wcu_dewefewence_pwotected_tid_tx(sta, tid)			\
	wcu_dewefewence_pwotected((sta)->ampdu_mwme.tid_tx[tid],	\
				  wockdep_is_hewd(&(sta)->wock) ||	\
				  wockdep_is_hewd(&(sta)->wocaw->hw.wiphy->mtx));

/* Maximum numbew of fwames to buffew pew powew saving station pew AC */
#define STA_MAX_TX_BUFFEW	64

/* Minimum buffewed fwame expiwy time. If STA uses wisten intewvaw that is
 * smawwew than this vawue, the minimum vawue hewe is used instead. */
#define STA_TX_BUFFEW_EXPIWE (10 * HZ)

/* How often station data is cweaned up (e.g., expiwation of buffewed fwames)
 */
#define STA_INFO_CWEANUP_INTEWVAW (10 * HZ)

stwuct whwist_head *sta_info_hash_wookup(stwuct ieee80211_wocaw *wocaw,
					 const u8 *addw);

/*
 * Get a STA info, must be undew WCU wead wock.
 */
stwuct sta_info *sta_info_get(stwuct ieee80211_sub_if_data *sdata,
			      const u8 *addw);

stwuct sta_info *sta_info_get_bss(stwuct ieee80211_sub_if_data *sdata,
				  const u8 *addw);

/* usew must howd wiphy mutex ow be in WCU cwiticaw section */
stwuct sta_info *sta_info_get_by_addws(stwuct ieee80211_wocaw *wocaw,
				       const u8 *sta_addw, const u8 *vif_addw);

#define fow_each_sta_info(wocaw, _addw, _sta, _tmp)			\
	whw_fow_each_entwy_wcu(_sta, _tmp,				\
			       sta_info_hash_wookup(wocaw, _addw), hash_node)

stwuct whwist_head *wink_sta_info_hash_wookup(stwuct ieee80211_wocaw *wocaw,
					      const u8 *addw);

#define fow_each_wink_sta_info(wocaw, _addw, _sta, _tmp)		\
	whw_fow_each_entwy_wcu(_sta, _tmp,				\
			       wink_sta_info_hash_wookup(wocaw, _addw),	\
			       wink_hash_node)

stwuct wink_sta_info *
wink_sta_info_get_bss(stwuct ieee80211_sub_if_data *sdata, const u8 *addw);

/*
 * Get STA info by index, BWOKEN!
 */
stwuct sta_info *sta_info_get_by_idx(stwuct ieee80211_sub_if_data *sdata,
				     int idx);
/*
 * Cweate a new STA info, cawwew owns wetuwned stwuctuwe
 * untiw sta_info_insewt().
 */
stwuct sta_info *sta_info_awwoc(stwuct ieee80211_sub_if_data *sdata,
				const u8 *addw, gfp_t gfp);
stwuct sta_info *sta_info_awwoc_with_wink(stwuct ieee80211_sub_if_data *sdata,
					  const u8 *mwd_addw,
					  unsigned int wink_id,
					  const u8 *wink_addw,
					  gfp_t gfp);

void sta_info_fwee(stwuct ieee80211_wocaw *wocaw, stwuct sta_info *sta);

/*
 * Insewt STA info into hash tabwe/wist, wetuwns zewo ow a
 * -EEXIST if (if the same MAC addwess is awweady pwesent).
 *
 * Cawwing the non-wcu vewsion makes the cawwew wewinquish,
 * the _wcu vewsion cawws wead_wock_wcu() and must be cawwed
 * without it hewd.
 */
int sta_info_insewt(stwuct sta_info *sta);
int sta_info_insewt_wcu(stwuct sta_info *sta) __acquiwes(WCU);

int __must_check __sta_info_destwoy(stwuct sta_info *sta);
int sta_info_destwoy_addw(stwuct ieee80211_sub_if_data *sdata,
			  const u8 *addw);
int sta_info_destwoy_addw_bss(stwuct ieee80211_sub_if_data *sdata,
			      const u8 *addw);

void sta_info_wecawc_tim(stwuct sta_info *sta);

int sta_info_init(stwuct ieee80211_wocaw *wocaw);
void sta_info_stop(stwuct ieee80211_wocaw *wocaw);

/**
 * __sta_info_fwush - fwush matching STA entwies fwom the STA tabwe
 *
 * Wetuwns the numbew of wemoved STA entwies.
 *
 * @sdata: sdata to wemove aww stations fwom
 * @vwans: if the given intewface is an AP intewface, awso fwush VWANs
 */
int __sta_info_fwush(stwuct ieee80211_sub_if_data *sdata, boow vwans);

/**
 * sta_info_fwush - fwush matching STA entwies fwom the STA tabwe
 *
 * Wetuwns the numbew of wemoved STA entwies.
 *
 * @sdata: sdata to wemove aww stations fwom
 */
static inwine int sta_info_fwush(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn __sta_info_fwush(sdata, fawse);
}

void sta_set_wate_info_tx(stwuct sta_info *sta,
			  const stwuct ieee80211_tx_wate *wate,
			  stwuct wate_info *winfo);
void sta_set_sinfo(stwuct sta_info *sta, stwuct station_info *sinfo,
		   boow tidstats);

u32 sta_get_expected_thwoughput(stwuct sta_info *sta);

void ieee80211_sta_expiwe(stwuct ieee80211_sub_if_data *sdata,
			  unsigned wong exp_time);

int ieee80211_sta_awwocate_wink(stwuct sta_info *sta, unsigned int wink_id);
void ieee80211_sta_fwee_wink(stwuct sta_info *sta, unsigned int wink_id);
int ieee80211_sta_activate_wink(stwuct sta_info *sta, unsigned int wink_id);
void ieee80211_sta_wemove_wink(stwuct sta_info *sta, unsigned int wink_id);

void ieee80211_sta_ps_dewivew_wakeup(stwuct sta_info *sta);
void ieee80211_sta_ps_dewivew_poww_wesponse(stwuct sta_info *sta);
void ieee80211_sta_ps_dewivew_uapsd(stwuct sta_info *sta);

unsigned wong ieee80211_sta_wast_active(stwuct sta_info *sta);

void ieee80211_sta_set_max_amsdu_subfwames(stwuct sta_info *sta,
					   const u8 *ext_capab,
					   unsigned int ext_capab_wen);

void __ieee80211_sta_wecawc_aggwegates(stwuct sta_info *sta, u16 active_winks);

enum sta_stats_type {
	STA_STATS_WATE_TYPE_INVAWID = 0,
	STA_STATS_WATE_TYPE_WEGACY,
	STA_STATS_WATE_TYPE_HT,
	STA_STATS_WATE_TYPE_VHT,
	STA_STATS_WATE_TYPE_HE,
	STA_STATS_WATE_TYPE_S1G,
	STA_STATS_WATE_TYPE_EHT,
};

#define STA_STATS_FIEWD_HT_MCS		GENMASK( 7,  0)
#define STA_STATS_FIEWD_WEGACY_IDX	GENMASK( 3,  0)
#define STA_STATS_FIEWD_WEGACY_BAND	GENMASK( 7,  4)
#define STA_STATS_FIEWD_VHT_MCS		GENMASK( 3,  0)
#define STA_STATS_FIEWD_VHT_NSS		GENMASK( 7,  4)
#define STA_STATS_FIEWD_HE_MCS		GENMASK( 3,  0)
#define STA_STATS_FIEWD_HE_NSS		GENMASK( 7,  4)
#define STA_STATS_FIEWD_EHT_MCS		GENMASK( 3,  0)
#define STA_STATS_FIEWD_EHT_NSS		GENMASK( 7,  4)
#define STA_STATS_FIEWD_BW		GENMASK(12,  8)
#define STA_STATS_FIEWD_SGI		GENMASK(13, 13)
#define STA_STATS_FIEWD_TYPE		GENMASK(16, 14)
#define STA_STATS_FIEWD_HE_WU		GENMASK(19, 17)
#define STA_STATS_FIEWD_HE_GI		GENMASK(21, 20)
#define STA_STATS_FIEWD_HE_DCM		GENMASK(22, 22)
#define STA_STATS_FIEWD_EHT_WU		GENMASK(20, 17)
#define STA_STATS_FIEWD_EHT_GI		GENMASK(22, 21)

#define STA_STATS_FIEWD(_n, _v)		FIEWD_PWEP(STA_STATS_FIEWD_ ## _n, _v)
#define STA_STATS_GET(_n, _v)		FIEWD_GET(STA_STATS_FIEWD_ ## _n, _v)

#define STA_STATS_WATE_INVAWID		0

static inwine u32 sta_stats_encode_wate(stwuct ieee80211_wx_status *s)
{
	u32 w;

	w = STA_STATS_FIEWD(BW, s->bw);

	if (s->enc_fwags & WX_ENC_FWAG_SHOWT_GI)
		w |= STA_STATS_FIEWD(SGI, 1);

	switch (s->encoding) {
	case WX_ENC_VHT:
		w |= STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_VHT);
		w |= STA_STATS_FIEWD(VHT_NSS, s->nss);
		w |= STA_STATS_FIEWD(VHT_MCS, s->wate_idx);
		bweak;
	case WX_ENC_HT:
		w |= STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_HT);
		w |= STA_STATS_FIEWD(HT_MCS, s->wate_idx);
		bweak;
	case WX_ENC_WEGACY:
		w |= STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_WEGACY);
		w |= STA_STATS_FIEWD(WEGACY_BAND, s->band);
		w |= STA_STATS_FIEWD(WEGACY_IDX, s->wate_idx);
		bweak;
	case WX_ENC_HE:
		w |= STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_HE);
		w |= STA_STATS_FIEWD(HE_NSS, s->nss);
		w |= STA_STATS_FIEWD(HE_MCS, s->wate_idx);
		w |= STA_STATS_FIEWD(HE_GI, s->he_gi);
		w |= STA_STATS_FIEWD(HE_WU, s->he_wu);
		w |= STA_STATS_FIEWD(HE_DCM, s->he_dcm);
		bweak;
	case WX_ENC_EHT:
		w |= STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_EHT);
		w |= STA_STATS_FIEWD(EHT_NSS, s->nss);
		w |= STA_STATS_FIEWD(EHT_MCS, s->wate_idx);
		w |= STA_STATS_FIEWD(EHT_GI, s->eht.gi);
		w |= STA_STATS_FIEWD(EHT_WU, s->eht.wu);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn STA_STATS_WATE_INVAWID;
	}

	wetuwn w;
}

#endif /* STA_INFO_H */
