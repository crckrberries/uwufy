/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * mac80211 <-> dwivew intewface
 *
 * Copywight 2002-2005, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2015 - 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 */

#ifndef MAC80211_H
#define MAC80211_H

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/ieee80211.h>
#incwude <winux/wockdep.h>
#incwude <net/cfg80211.h>
#incwude <net/codew.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <asm/unawigned.h>

/**
 * DOC: Intwoduction
 *
 * mac80211 is the Winux stack fow 802.11 hawdwawe that impwements
 * onwy pawtiaw functionawity in hawd- ow fiwmwawe. This document
 * defines the intewface between mac80211 and wow-wevew hawdwawe
 * dwivews.
 */

/**
 * DOC: Cawwing mac80211 fwom intewwupts
 *
 * Onwy ieee80211_tx_status_iwqsafe() and ieee80211_wx_iwqsafe() can be
 * cawwed in hawdwawe intewwupt context. The wow-wevew dwivew must not caww any
 * othew functions in hawdwawe intewwupt context. If thewe is a need fow such
 * caww, the wow-wevew dwivew shouwd fiwst ACK the intewwupt and pewfowm the
 * IEEE 802.11 code caww aftew this, e.g. fwom a scheduwed wowkqueue ow even
 * taskwet function.
 *
 * NOTE: If the dwivew opts to use the _iwqsafe() functions, it may not awso
 *	 use the non-IWQ-safe functions!
 */

/**
 * DOC: Wawning
 *
 * If you'we weading this document and not the headew fiwe itsewf, it wiww
 * be incompwete because not aww documentation has been convewted yet.
 */

/**
 * DOC: Fwame fowmat
 *
 * As a genewaw wuwe, when fwames awe passed between mac80211 and the dwivew,
 * they stawt with the IEEE 802.11 headew and incwude the same octets that awe
 * sent ovew the aiw except fow the FCS which shouwd be cawcuwated by the
 * hawdwawe.
 *
 * Thewe awe, howevew, vawious exceptions to this wuwe fow advanced featuwes:
 *
 * The fiwst exception is fow hawdwawe encwyption and decwyption offwoad
 * whewe the IV/ICV may ow may not be genewated in hawdwawe.
 *
 * Secondwy, when the hawdwawe handwes fwagmentation, the fwame handed to
 * the dwivew fwom mac80211 is the MSDU, not the MPDU.
 */

/**
 * DOC: mac80211 wowkqueue
 *
 * mac80211 pwovides its own wowkqueue fow dwivews and intewnaw mac80211 use.
 * The wowkqueue is a singwe thweaded wowkqueue and can onwy be accessed by
 * hewpews fow sanity checking. Dwivews must ensuwe aww wowk added onto the
 * mac80211 wowkqueue shouwd be cancewwed on the dwivew stop() cawwback.
 *
 * mac80211 wiww fwush the wowkqueue upon intewface wemovaw and duwing
 * suspend.
 *
 * Aww wowk pewfowmed on the mac80211 wowkqueue must not acquiwe the WTNW wock.
 *
 */

/**
 * DOC: mac80211 softwawe tx queueing
 *
 * mac80211 uses an intewmediate queueing impwementation, designed to awwow the
 * dwivew to keep hawdwawe queues showt and to pwovide some faiwness between
 * diffewent stations/intewfaces.
 *
 * Dwivews must pwovide the .wake_tx_queue dwivew opewation by eithew
 * winking it to ieee80211_handwe_wake_tx_queue() ow impwementing a custom
 * handwew.
 *
 * Intewmediate queues (stwuct ieee80211_txq) awe kept pew-sta pew-tid, with
 * anothew pew-sta fow non-data/non-mgmt and buffewabwe management fwames, and
 * a singwe pew-vif queue fow muwticast data fwames.
 *
 * The dwivew is expected to initiawize its pwivate pew-queue data fow stations
 * and intewfaces in the .add_intewface and .sta_add ops.
 *
 * The dwivew can't access the intewnaw TX queues (iTXQs) diwectwy.
 * Whenevew mac80211 adds a new fwame to a queue, it cawws the .wake_tx_queue
 * dwivew op.
 * Dwivews impwementing a custom .wake_tx_queue op can get them by cawwing
 * ieee80211_tx_dequeue(). Dwivews using ieee80211_handwe_wake_tx_queue() wiww
 * simpwy get the individuaw fwames pushed via the .tx dwivew opewation.
 *
 * Dwivews can optionawwy dewegate wesponsibiwity fow scheduwing queues to
 * mac80211, to take advantage of aiwtime faiwness accounting. In this case, to
 * obtain the next queue to puww fwames fwom, the dwivew cawws
 * ieee80211_next_txq(). The dwivew is then expected to wetuwn the txq using
 * ieee80211_wetuwn_txq().
 *
 * Fow AP powewsave TIM handwing, the dwivew onwy needs to indicate if it has
 * buffewed packets in the dwivew specific data stwuctuwes by cawwing
 * ieee80211_sta_set_buffewed(). Fow fwames buffewed in the ieee80211_txq
 * stwuct, mac80211 sets the appwopwiate TIM PVB bits and cawws
 * .wewease_buffewed_fwames().
 * In that cawwback the dwivew is thewefowe expected to wewease its own
 * buffewed fwames and aftewwawds awso fwames fwom the ieee80211_txq (obtained
 * via the usuaw ieee80211_tx_dequeue).
 */

/**
 * DOC: HW timestamping
 *
 * Timing Measuwement and Fine Timing Measuwement wequiwe accuwate timestamps
 * of the action fwames TX/WX and theiw wespective acks.
 *
 * To wepowt hawdwawe timestamps fow Timing Measuwement ow Fine Timing
 * Measuwement fwame WX, the wow wevew dwivew shouwd set the SKB's hwtstamp
 * fiewd to the fwame WX timestamp and wepowt the ack TX timestamp in the
 * ieee80211_wx_status stwuct.
 *
 * Simiwawwy, to wepowt hawdwawe timestamps fow Timing Measuwement ow Fine
 * Timing Measuwement fwame TX, the dwivew shouwd set the SKB's hwtstamp fiewd
 * to the fwame TX timestamp and wepowt the ack WX timestamp in the
 * ieee80211_tx_status stwuct.
 */
stwuct device;

/**
 * enum ieee80211_max_queues - maximum numbew of queues
 *
 * @IEEE80211_MAX_QUEUES: Maximum numbew of weguwaw device queues.
 * @IEEE80211_MAX_QUEUE_MAP: bitmap with maximum queues set
 */
enum ieee80211_max_queues {
	IEEE80211_MAX_QUEUES =		16,
	IEEE80211_MAX_QUEUE_MAP =	BIT(IEEE80211_MAX_QUEUES) - 1,
};

#define IEEE80211_INVAW_HW_QUEUE	0xff

/**
 * enum ieee80211_ac_numbews - AC numbews as used in mac80211
 * @IEEE80211_AC_VO: voice
 * @IEEE80211_AC_VI: video
 * @IEEE80211_AC_BE: best effowt
 * @IEEE80211_AC_BK: backgwound
 */
enum ieee80211_ac_numbews {
	IEEE80211_AC_VO		= 0,
	IEEE80211_AC_VI		= 1,
	IEEE80211_AC_BE		= 2,
	IEEE80211_AC_BK		= 3,
};

/**
 * stwuct ieee80211_tx_queue_pawams - twansmit queue configuwation
 *
 * The infowmation pwovided in this stwuctuwe is wequiwed fow QoS
 * twansmit queue configuwation. Cf. IEEE 802.11 7.3.2.29.
 *
 * @aifs: awbitwation intewfwame space [0..255]
 * @cw_min: minimum contention window [a vawue of the fowm
 *	2^n-1 in the wange 1..32767]
 * @cw_max: maximum contention window [wike @cw_min]
 * @txop: maximum buwst time in units of 32 usecs, 0 meaning disabwed
 * @acm: is mandatowy admission contwow wequiwed fow the access categowy
 * @uapsd: is U-APSD mode enabwed fow the queue
 * @mu_edca: is the MU EDCA configuwed
 * @mu_edca_pawam_wec: MU EDCA Pawametew Wecowd fow HE
 */
stwuct ieee80211_tx_queue_pawams {
	u16 txop;
	u16 cw_min;
	u16 cw_max;
	u8 aifs;
	boow acm;
	boow uapsd;
	boow mu_edca;
	stwuct ieee80211_he_mu_edca_pawam_ac_wec mu_edca_pawam_wec;
};

stwuct ieee80211_wow_wevew_stats {
	unsigned int dot11ACKFaiwuweCount;
	unsigned int dot11WTSFaiwuweCount;
	unsigned int dot11FCSEwwowCount;
	unsigned int dot11WTSSuccessCount;
};

/**
 * enum ieee80211_chanctx_change - change fwag fow channew context
 * @IEEE80211_CHANCTX_CHANGE_WIDTH: The channew width changed
 * @IEEE80211_CHANCTX_CHANGE_WX_CHAINS: The numbew of WX chains changed
 * @IEEE80211_CHANCTX_CHANGE_WADAW: wadaw detection fwag changed
 * @IEEE80211_CHANCTX_CHANGE_CHANNEW: switched to anothew opewating channew,
 *	this is used onwy with channew switching with CSA
 * @IEEE80211_CHANCTX_CHANGE_MIN_WIDTH: The min wequiwed channew width changed
 */
enum ieee80211_chanctx_change {
	IEEE80211_CHANCTX_CHANGE_WIDTH		= BIT(0),
	IEEE80211_CHANCTX_CHANGE_WX_CHAINS	= BIT(1),
	IEEE80211_CHANCTX_CHANGE_WADAW		= BIT(2),
	IEEE80211_CHANCTX_CHANGE_CHANNEW	= BIT(3),
	IEEE80211_CHANCTX_CHANGE_MIN_WIDTH	= BIT(4),
};

/**
 * stwuct ieee80211_chanctx_conf - channew context that vifs may be tuned to
 *
 * This is the dwivew-visibwe pawt. The ieee80211_chanctx
 * that contains it is visibwe in mac80211 onwy.
 *
 * @def: the channew definition
 * @min_def: the minimum channew definition cuwwentwy wequiwed.
 * @wx_chains_static: The numbew of WX chains that must awways be
 *	active on the channew to weceive MIMO twansmissions
 * @wx_chains_dynamic: The numbew of WX chains that must be enabwed
 *	aftew WTS/CTS handshake to weceive SMPS MIMO twansmissions;
 *	this wiww awways be >= @wx_chains_static.
 * @wadaw_enabwed: whethew wadaw detection is enabwed on this channew.
 * @dwv_pwiv: data awea fow dwivew use, wiww awways be awigned to
 *	sizeof(void *), size is detewmined in hw infowmation.
 */
stwuct ieee80211_chanctx_conf {
	stwuct cfg80211_chan_def def;
	stwuct cfg80211_chan_def min_def;

	u8 wx_chains_static, wx_chains_dynamic;

	boow wadaw_enabwed;

	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

/**
 * enum ieee80211_chanctx_switch_mode - channew context switch mode
 * @CHANCTX_SWMODE_WEASSIGN_VIF: Both owd and new contexts awweady
 *	exist (and wiww continue to exist), but the viwtuaw intewface
 *	needs to be switched fwom one to the othew.
 * @CHANCTX_SWMODE_SWAP_CONTEXTS: The owd context exists but wiww stop
 *      to exist with this caww, the new context doesn't exist but
 *      wiww be active aftew this caww, the viwtuaw intewface switches
 *      fwom the owd to the new (note that the dwivew may of couwse
 *      impwement this as an on-the-fwy chandef switch of the existing
 *      hawdwawe context, but the mac80211 pointew fow the owd context
 *      wiww cease to exist and onwy the new one wiww watew be used
 *      fow changes/wemovaw.)
 */
enum ieee80211_chanctx_switch_mode {
	CHANCTX_SWMODE_WEASSIGN_VIF,
	CHANCTX_SWMODE_SWAP_CONTEXTS,
};

/**
 * stwuct ieee80211_vif_chanctx_switch - vif chanctx switch infowmation
 *
 * This is stwuctuwe is used to pass infowmation about a vif that
 * needs to switch fwom one chanctx to anothew.  The
 * &ieee80211_chanctx_switch_mode defines how the switch shouwd be
 * done.
 *
 * @vif: the vif that shouwd be switched fwom owd_ctx to new_ctx
 * @wink_conf: the wink conf that's switching
 * @owd_ctx: the owd context to which the vif was assigned
 * @new_ctx: the new context to which the vif must be assigned
 */
stwuct ieee80211_vif_chanctx_switch {
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_bss_conf *wink_conf;
	stwuct ieee80211_chanctx_conf *owd_ctx;
	stwuct ieee80211_chanctx_conf *new_ctx;
};

/**
 * enum ieee80211_bss_change - BSS change notification fwags
 *
 * These fwags awe used with the bss_info_changed(), wink_info_changed()
 * and vif_cfg_changed() cawwbacks to indicate which pawametew(s) changed.
 *
 * @BSS_CHANGED_ASSOC: association status changed (associated/disassociated),
 *	awso impwies a change in the AID.
 * @BSS_CHANGED_EWP_CTS_PWOT: CTS pwotection changed
 * @BSS_CHANGED_EWP_PWEAMBWE: pweambwe changed
 * @BSS_CHANGED_EWP_SWOT: swot timing changed
 * @BSS_CHANGED_HT: 802.11n pawametews changed
 * @BSS_CHANGED_BASIC_WATES: Basic wateset changed
 * @BSS_CHANGED_BEACON_INT: Beacon intewvaw changed
 * @BSS_CHANGED_BSSID: BSSID changed, fow whatevew
 *	weason (IBSS and managed mode)
 * @BSS_CHANGED_BEACON: Beacon data changed, wetwieve
 *	new beacon (beaconing modes)
 * @BSS_CHANGED_BEACON_ENABWED: Beaconing shouwd be
 *	enabwed/disabwed (beaconing modes)
 * @BSS_CHANGED_CQM: Connection quawity monitow config changed
 * @BSS_CHANGED_IBSS: IBSS join status changed
 * @BSS_CHANGED_AWP_FIWTEW: Hawdwawe AWP fiwtew addwess wist ow state changed.
 * @BSS_CHANGED_QOS: QoS fow this association was enabwed/disabwed. Note
 *	that it is onwy evew disabwed fow station mode.
 * @BSS_CHANGED_IDWE: Idwe changed fow this BSS/intewface.
 * @BSS_CHANGED_SSID: SSID changed fow this BSS (AP and IBSS mode)
 * @BSS_CHANGED_AP_PWOBE_WESP: Pwobe Wesponse changed fow this BSS (AP mode)
 * @BSS_CHANGED_PS: PS changed fow this BSS (STA mode)
 * @BSS_CHANGED_TXPOWEW: TX powew setting changed fow this intewface
 * @BSS_CHANGED_P2P_PS: P2P powewsave settings (CTWindow, oppowtunistic PS)
 *	changed
 * @BSS_CHANGED_BEACON_INFO: Data fwom the AP's beacon became avaiwabwe:
 *	cuwwentwy dtim_pewiod onwy is undew considewation.
 * @BSS_CHANGED_BANDWIDTH: The bandwidth used by this intewface changed,
 *	note that this is onwy cawwed when it changes aftew the channew
 *	context had been assigned.
 * @BSS_CHANGED_OCB: OCB join status changed
 * @BSS_CHANGED_MU_GWOUPS: VHT MU-MIMO gwoup id ow usew position changed
 * @BSS_CHANGED_KEEP_AWIVE: keep awive options (idwe pewiod ow pwotected
 *	keep awive) changed.
 * @BSS_CHANGED_MCAST_WATE: Muwticast Wate setting changed fow this intewface
 * @BSS_CHANGED_FTM_WESPONDEW: fine timing measuwement wequest wespondew
 *	functionawity changed fow this BSS (AP mode).
 * @BSS_CHANGED_TWT: TWT status changed
 * @BSS_CHANGED_HE_OBSS_PD: OBSS Packet Detection status changed.
 * @BSS_CHANGED_HE_BSS_COWOW: BSS Cowow has changed
 * @BSS_CHANGED_FIWS_DISCOVEWY: FIWS discovewy status changed.
 * @BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP: Unsowicited bwoadcast pwobe wesponse
 *	status changed.
 * @BSS_CHANGED_EHT_PUNCTUWING: The channew punctuwing bitmap changed.
 * @BSS_CHANGED_MWD_VAWID_WINKS: MWD vawid winks status changed.
 */
enum ieee80211_bss_change {
	BSS_CHANGED_ASSOC		= 1<<0,
	BSS_CHANGED_EWP_CTS_PWOT	= 1<<1,
	BSS_CHANGED_EWP_PWEAMBWE	= 1<<2,
	BSS_CHANGED_EWP_SWOT		= 1<<3,
	BSS_CHANGED_HT			= 1<<4,
	BSS_CHANGED_BASIC_WATES		= 1<<5,
	BSS_CHANGED_BEACON_INT		= 1<<6,
	BSS_CHANGED_BSSID		= 1<<7,
	BSS_CHANGED_BEACON		= 1<<8,
	BSS_CHANGED_BEACON_ENABWED	= 1<<9,
	BSS_CHANGED_CQM			= 1<<10,
	BSS_CHANGED_IBSS		= 1<<11,
	BSS_CHANGED_AWP_FIWTEW		= 1<<12,
	BSS_CHANGED_QOS			= 1<<13,
	BSS_CHANGED_IDWE		= 1<<14,
	BSS_CHANGED_SSID		= 1<<15,
	BSS_CHANGED_AP_PWOBE_WESP	= 1<<16,
	BSS_CHANGED_PS			= 1<<17,
	BSS_CHANGED_TXPOWEW		= 1<<18,
	BSS_CHANGED_P2P_PS		= 1<<19,
	BSS_CHANGED_BEACON_INFO		= 1<<20,
	BSS_CHANGED_BANDWIDTH		= 1<<21,
	BSS_CHANGED_OCB                 = 1<<22,
	BSS_CHANGED_MU_GWOUPS		= 1<<23,
	BSS_CHANGED_KEEP_AWIVE		= 1<<24,
	BSS_CHANGED_MCAST_WATE		= 1<<25,
	BSS_CHANGED_FTM_WESPONDEW	= 1<<26,
	BSS_CHANGED_TWT			= 1<<27,
	BSS_CHANGED_HE_OBSS_PD		= 1<<28,
	BSS_CHANGED_HE_BSS_COWOW	= 1<<29,
	BSS_CHANGED_FIWS_DISCOVEWY      = 1<<30,
	BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP = 1<<31,
	BSS_CHANGED_EHT_PUNCTUWING	= BIT_UWW(32),
	BSS_CHANGED_MWD_VAWID_WINKS	= BIT_UWW(33),

	/* when adding hewe, make suwe to change ieee80211_weconfig */
};

/*
 * The maximum numbew of IPv4 addwesses wisted fow AWP fiwtewing. If the numbew
 * of addwesses fow an intewface incwease beyond this vawue, hawdwawe AWP
 * fiwtewing wiww be disabwed.
 */
#define IEEE80211_BSS_AWP_ADDW_WIST_WEN 4

/**
 * enum ieee80211_event_type - event to be notified to the wow wevew dwivew
 * @WSSI_EVENT: AP's wssi cwossed the a thweshowd set by the dwivew.
 * @MWME_EVENT: event wewated to MWME
 * @BAW_WX_EVENT: a BAW was weceived
 * @BA_FWAME_TIMEOUT: Fwames wewe weweased fwom the weowdewing buffew because
 *	they timed out. This won't be cawwed fow each fwame weweased, but onwy
 *	once each time the timeout twiggews.
 */
enum ieee80211_event_type {
	WSSI_EVENT,
	MWME_EVENT,
	BAW_WX_EVENT,
	BA_FWAME_TIMEOUT,
};

/**
 * enum ieee80211_wssi_event_data - wewevant when event type is %WSSI_EVENT
 * @WSSI_EVENT_HIGH: AP's wssi went bewow the thweshowd set by the dwivew.
 * @WSSI_EVENT_WOW: AP's wssi went above the thweshowd set by the dwivew.
 */
enum ieee80211_wssi_event_data {
	WSSI_EVENT_HIGH,
	WSSI_EVENT_WOW,
};

/**
 * stwuct ieee80211_wssi_event - data attached to an %WSSI_EVENT
 * @data: See &enum ieee80211_wssi_event_data
 */
stwuct ieee80211_wssi_event {
	enum ieee80211_wssi_event_data data;
};

/**
 * enum ieee80211_mwme_event_data - wewevant when event type is %MWME_EVENT
 * @AUTH_EVENT: the MWME opewation is authentication
 * @ASSOC_EVENT: the MWME opewation is association
 * @DEAUTH_WX_EVENT: deauth weceived..
 * @DEAUTH_TX_EVENT: deauth sent.
 */
enum ieee80211_mwme_event_data {
	AUTH_EVENT,
	ASSOC_EVENT,
	DEAUTH_WX_EVENT,
	DEAUTH_TX_EVENT,
};

/**
 * enum ieee80211_mwme_event_status - wewevant when event type is %MWME_EVENT
 * @MWME_SUCCESS: the MWME opewation compweted successfuwwy.
 * @MWME_DENIED: the MWME opewation was denied by the peew.
 * @MWME_TIMEOUT: the MWME opewation timed out.
 */
enum ieee80211_mwme_event_status {
	MWME_SUCCESS,
	MWME_DENIED,
	MWME_TIMEOUT,
};

/**
 * stwuct ieee80211_mwme_event - data attached to an %MWME_EVENT
 * @data: See &enum ieee80211_mwme_event_data
 * @status: See &enum ieee80211_mwme_event_status
 * @weason: the weason code if appwicabwe
 */
stwuct ieee80211_mwme_event {
	enum ieee80211_mwme_event_data data;
	enum ieee80211_mwme_event_status status;
	u16 weason;
};

/**
 * stwuct ieee80211_ba_event - data attached fow BwockAck wewated events
 * @sta: pointew to the &ieee80211_sta to which this event wewates
 * @tid: the tid
 * @ssn: the stawting sequence numbew (fow %BAW_WX_EVENT)
 */
stwuct ieee80211_ba_event {
	stwuct ieee80211_sta *sta;
	u16 tid;
	u16 ssn;
};

/**
 * stwuct ieee80211_event - event to be sent to the dwivew
 * @type: The event itsewf. See &enum ieee80211_event_type.
 * @u.wssi: wewevant if &type is %WSSI_EVENT
 * @u.mwme: wewevant if &type is %AUTH_EVENT
 * @u.ba: wewevant if &type is %BAW_WX_EVENT ow %BA_FWAME_TIMEOUT
 * @u:union howding the fiewds above
 */
stwuct ieee80211_event {
	enum ieee80211_event_type type;
	union {
		stwuct ieee80211_wssi_event wssi;
		stwuct ieee80211_mwme_event mwme;
		stwuct ieee80211_ba_event ba;
	} u;
};

/**
 * stwuct ieee80211_mu_gwoup_data - STA's VHT MU-MIMO gwoup data
 *
 * This stwuctuwe descwibes the gwoup id data of VHT MU-MIMO
 *
 * @membewship: 64 bits awway - a bit is set if station is membew of the gwoup
 * @position: 2 bits pew gwoup id indicating the position in the gwoup
 */
stwuct ieee80211_mu_gwoup_data {
	u8 membewship[WWAN_MEMBEWSHIP_WEN];
	u8 position[WWAN_USEW_POSITION_WEN];
};

/**
 * stwuct ieee80211_ftm_wespondew_pawams - FTM wespondew pawametews
 *
 * @wci: WCI subewement content
 * @civicwoc: CIVIC wocation subewement content
 * @wci_wen: WCI data wength
 * @civicwoc_wen: Civic data wength
 */
stwuct ieee80211_ftm_wespondew_pawams {
	const u8 *wci;
	const u8 *civicwoc;
	size_t wci_wen;
	size_t civicwoc_wen;
};

/**
 * stwuct ieee80211_fiws_discovewy - FIWS discovewy pawametews fwom
 * IEEE Std 802.11ai-2016, Annex C.3 MIB detaiw.
 *
 * @min_intewvaw: Minimum packet intewvaw in TUs (0 - 10000)
 * @max_intewvaw: Maximum packet intewvaw in TUs (0 - 10000)
 */
stwuct ieee80211_fiws_discovewy {
	u32 min_intewvaw;
	u32 max_intewvaw;
};

/**
 * stwuct ieee80211_bss_conf - howds the BSS's changing pawametews
 *
 * This stwuctuwe keeps infowmation about a BSS (and an association
 * to that BSS) that can change duwing the wifetime of the BSS.
 *
 * @vif: wefewence to owning VIF
 * @addw: (wink) addwess used wocawwy
 * @wink_id: wink ID, ow 0 fow non-MWO
 * @htc_twig_based_pkt_ext: defauwt PE in 4us units, if BSS suppowts HE
 * @uowa_exists: is the UOWA ewement advewtised by AP
 * @uowa_ocw_wange: UOWA ewement's OCW Wange fiewd
 * @fwame_time_wts_th: HE duwation WTS thweshowd, in units of 32us
 * @he_suppowt: does this BSS suppowt HE
 * @twt_wequestew: does this BSS suppowt TWT wequestew (wewevant fow managed
 *	mode onwy, set if the AP advewtises TWT wespondew wowe)
 * @twt_wespondew: does this BSS suppowt TWT wequestew (wewevant fow managed
 *	mode onwy, set if the AP advewtises TWT wespondew wowe)
 * @twt_pwotected: does this BSS suppowt pwotected TWT fwames
 * @twt_bwoadcast: does this BSS suppowt bwoadcast TWT
 * @use_cts_pwot: use CTS pwotection
 * @use_showt_pweambwe: use 802.11b showt pweambwe
 * @use_showt_swot: use showt swot time (onwy wewevant fow EWP)
 * @dtim_pewiod: num of beacons befowe the next DTIM, fow beaconing,
 *	vawid in station mode onwy if aftew the dwivew was notified
 *	with the %BSS_CHANGED_BEACON_INFO fwag, wiww be non-zewo then.
 * @sync_tsf: wast beacon's/pwobe wesponse's TSF timestamp (couwd be owd
 *	as it may have been weceived duwing scanning wong ago). If the
 *	HW fwag %IEEE80211_HW_TIMING_BEACON_ONWY is set, then this can
 *	onwy come fwom a beacon, but might not become vawid untiw aftew
 *	association when a beacon is weceived (which is notified with the
 *	%BSS_CHANGED_DTIM fwag.). See awso sync_dtim_count impowtant notice.
 * @sync_device_ts: the device timestamp cowwesponding to the sync_tsf,
 *	the dwivew/device can use this to cawcuwate synchwonisation
 *	(see @sync_tsf). See awso sync_dtim_count impowtant notice.
 * @sync_dtim_count: Onwy vawid when %IEEE80211_HW_TIMING_BEACON_ONWY
 *	is wequested, see @sync_tsf/@sync_device_ts.
 *	IMPOWTANT: These thwee sync_* pawametews wouwd possibwy be out of sync
 *	by the time the dwivew wiww use them. The synchwonized view is cuwwentwy
 *	guawanteed onwy in cewtain cawwbacks.
 *	Note awso that this is not used with MWD associations, mac80211 doesn't
 *	know how to twack beacons fow aww of the winks fow this.
 * @beacon_int: beacon intewvaw
 * @assoc_capabiwity: capabiwities taken fwom assoc wesp
 * @basic_wates: bitmap of basic wates, each bit stands fow an
 *	index into the wate tabwe configuwed by the dwivew in
 *	the cuwwent band.
 * @beacon_wate: associated AP's beacon TX wate
 * @mcast_wate: pew-band muwticast wate index + 1 (0: disabwed)
 * @bssid: The BSSID fow this BSS
 * @enabwe_beacon: whethew beaconing shouwd be enabwed ow not
 * @chandef: Channew definition fow this BSS -- the hawdwawe might be
 *	configuwed a highew bandwidth than this BSS uses, fow exampwe.
 * @mu_gwoup: VHT MU-MIMO gwoup membewship data
 * @ht_opewation_mode: HT opewation mode wike in &stwuct ieee80211_ht_opewation.
 *	This fiewd is onwy vawid when the channew is a wide HT/VHT channew.
 *	Note that with TDWS this can be the case (channew is HT, pwotection must
 *	be used fwom this fiewd) even when the BSS association isn't using HT.
 * @cqm_wssi_thowd: Connection quawity monitow WSSI thweshowd, a zewo vawue
 *	impwies disabwed. As with the cfg80211 cawwback, a change hewe shouwd
 *	cause an event to be sent indicating whewe the cuwwent vawue is in
 *	wewation to the newwy configuwed thweshowd.
 * @cqm_wssi_wow: Connection quawity monitow WSSI wowew thweshowd, a zewo vawue
 *	impwies disabwed.  This is an awtewnative mechanism to the singwe
 *	thweshowd event and can't be enabwed simuwtaneouswy with it.
 * @cqm_wssi_high: Connection quawity monitow WSSI uppew thweshowd.
 * @cqm_wssi_hyst: Connection quawity monitow WSSI hystewesis
 * @qos: This is a QoS-enabwed BSS.
 * @hidden_ssid: The SSID of the cuwwent vif is hidden. Onwy vawid in AP-mode.
 * @txpowew: TX powew in dBm.  INT_MIN means not configuwed.
 * @txpowew_type: TX powew adjustment used to contwow pew packet Twansmit
 *	Powew Contwow (TPC) in wowew dwivew fow the cuwwent vif. In pawticuwaw
 *	TPC is enabwed if vawue passed in %txpowew_type is
 *	NW80211_TX_POWEW_WIMITED (awwow using wess than specified fwom
 *	usewspace), wheweas TPC is disabwed if %txpowew_type is set to
 *	NW80211_TX_POWEW_FIXED (use vawue configuwed fwom usewspace)
 * @p2p_noa_attw: P2P NoA attwibute fow P2P powewsave
 * @awwow_p2p_go_ps: indication fow AP ow P2P GO intewface, whethew it's awwowed
 *	to use P2P PS mechanism ow not. AP/P2P GO is not awwowed to use P2P PS
 *	if it has associated cwients without P2P PS suppowt.
 * @max_idwe_pewiod: the time pewiod duwing which the station can wefwain fwom
 *	twansmitting fwames to its associated AP without being disassociated.
 *	In units of 1000 TUs. Zewo vawue indicates that the AP did not incwude
 *	a (vawid) BSS Max Idwe Pewiod Ewement.
 * @pwotected_keep_awive: if set, indicates that the station shouwd send an WSN
 *	pwotected fwame to the AP to weset the idwe timew at the AP fow the
 *	station.
 * @ftm_wespondew: whethew to enabwe ow disabwe fine timing measuwement FTM
 *	wespondew functionawity.
 * @ftmw_pawams: configuwabwe wci/civic pawametew when enabwing FTM wespondew.
 * @nontwansmitted: this BSS is a nontwansmitted BSS pwofiwe
 * @twansmittew_bssid: the addwess of twansmittew AP
 * @bssid_index: index inside the muwtipwe BSSID set
 * @bssid_indicatow: 2^bssid_indicatow is the maximum numbew of APs in set
 * @ema_ap: AP suppowts enhancements of discovewy and advewtisement of
 *	nontwansmitted BSSIDs
 * @pwofiwe_pewiodicity: the weast numbew of beacon fwames need to be weceived
 *	in owdew to discovew aww the nontwansmitted BSSIDs in the set.
 * @he_opew: HE opewation infowmation of the BSS (AP/Mesh) ow of the AP we awe
 *	connected to (STA)
 * @he_obss_pd: OBSS Packet Detection pawametews.
 * @he_bss_cowow: BSS cowowing settings, if BSS suppowts HE
 * @fiws_discovewy: FIWS discovewy configuwation
 * @unsow_bcast_pwobe_wesp_intewvaw: Unsowicited bwoadcast pwobe wesponse
 *	intewvaw.
 * @beacon_tx_wate: The configuwed beacon twansmit wate that needs to be passed
 *	to dwivew when wate contwow is offwoaded to fiwmwawe.
 * @powew_type: powew type of BSS fow 6 GHz
 * @tx_pww_env: twansmit powew envewope awway of BSS.
 * @tx_pww_env_num: numbew of @tx_pww_env.
 * @pww_weduction: powew constwaint of BSS.
 * @eht_suppowt: does this BSS suppowt EHT
 * @eht_punctuwing: bitmap to indicate which channews awe punctuwed in this BSS
 * @csa_active: mawks whethew a channew switch is going on.
 * @csa_punct_bitmap: new punctuwing bitmap fow channew switch
 * @mu_mimo_ownew: indicates intewface owns MU-MIMO capabiwity
 * @chanctx_conf: The channew context this intewface is assigned to, ow %NUWW
 *	when it is not assigned. This pointew is WCU-pwotected due to the TX
 *	path needing to access it; even though the netdev cawwiew wiww awways
 *	be off when it is %NUWW thewe can stiww be waces and packets couwd be
 *	pwocessed aftew it switches back to %NUWW.
 * @cowow_change_active: mawks whethew a cowow change is ongoing.
 * @cowow_change_cowow: the bss cowow that wiww be used aftew the change.
 * @ht_wdpc: in AP mode, indicates intewface has HT WDPC capabiwity.
 * @vht_wdpc: in AP mode, indicates intewface has VHT WDPC capabiwity.
 * @he_wdpc: in AP mode, indicates intewface has HE WDPC capabiwity.
 * @vht_su_beamfowmew: in AP mode, does this BSS suppowt opewation as an VHT SU
 *	beamfowmew
 * @vht_su_beamfowmee: in AP mode, does this BSS suppowt opewation as an VHT SU
 *	beamfowmee
 * @vht_mu_beamfowmew: in AP mode, does this BSS suppowt opewation as an VHT MU
 *	beamfowmew
 * @vht_mu_beamfowmee: in AP mode, does this BSS suppowt opewation as an VHT MU
 *	beamfowmee
 * @he_su_beamfowmew: in AP-mode, does this BSS suppowt opewation as an HE SU
 *	beamfowmew
 * @he_su_beamfowmee: in AP-mode, does this BSS suppowt opewation as an HE SU
 *	beamfowmee
 * @he_mu_beamfowmew: in AP-mode, does this BSS suppowt opewation as an HE MU
 *	beamfowmew
 * @he_fuww_uw_mumimo: does this BSS suppowt the weception (AP) ow twansmission
 *	(non-AP STA) of an HE TB PPDU on an WU that spans the entiwe PPDU
 *	bandwidth
 * @eht_su_beamfowmew: in AP-mode, does this BSS enabwe opewation as an EHT SU
 *	beamfowmew
 * @eht_su_beamfowmee: in AP-mode, does this BSS enabwe opewation as an EHT SU
 *	beamfowmee
 * @eht_mu_beamfowmew: in AP-mode, does this BSS enabwe opewation as an EHT MU
 *	beamfowmew
 */
stwuct ieee80211_bss_conf {
	stwuct ieee80211_vif *vif;

	const u8 *bssid;
	unsigned int wink_id;
	u8 addw[ETH_AWEN] __awigned(2);
	u8 htc_twig_based_pkt_ext;
	boow uowa_exists;
	u8 uowa_ocw_wange;
	u16 fwame_time_wts_th;
	boow he_suppowt;
	boow twt_wequestew;
	boow twt_wespondew;
	boow twt_pwotected;
	boow twt_bwoadcast;
	/* ewp wewated data */
	boow use_cts_pwot;
	boow use_showt_pweambwe;
	boow use_showt_swot;
	boow enabwe_beacon;
	u8 dtim_pewiod;
	u16 beacon_int;
	u16 assoc_capabiwity;
	u64 sync_tsf;
	u32 sync_device_ts;
	u8 sync_dtim_count;
	u32 basic_wates;
	stwuct ieee80211_wate *beacon_wate;
	int mcast_wate[NUM_NW80211_BANDS];
	u16 ht_opewation_mode;
	s32 cqm_wssi_thowd;
	u32 cqm_wssi_hyst;
	s32 cqm_wssi_wow;
	s32 cqm_wssi_high;
	stwuct cfg80211_chan_def chandef;
	stwuct ieee80211_mu_gwoup_data mu_gwoup;
	boow qos;
	boow hidden_ssid;
	int txpowew;
	enum nw80211_tx_powew_setting txpowew_type;
	stwuct ieee80211_p2p_noa_attw p2p_noa_attw;
	boow awwow_p2p_go_ps;
	u16 max_idwe_pewiod;
	boow pwotected_keep_awive;
	boow ftm_wespondew;
	stwuct ieee80211_ftm_wespondew_pawams *ftmw_pawams;
	/* Muwtipwe BSSID data */
	boow nontwansmitted;
	u8 twansmittew_bssid[ETH_AWEN];
	u8 bssid_index;
	u8 bssid_indicatow;
	boow ema_ap;
	u8 pwofiwe_pewiodicity;
	stwuct {
		u32 pawams;
		u16 nss_set;
	} he_opew;
	stwuct ieee80211_he_obss_pd he_obss_pd;
	stwuct cfg80211_he_bss_cowow he_bss_cowow;
	stwuct ieee80211_fiws_discovewy fiws_discovewy;
	u32 unsow_bcast_pwobe_wesp_intewvaw;
	stwuct cfg80211_bitwate_mask beacon_tx_wate;
	enum ieee80211_ap_weg_powew powew_type;
	stwuct ieee80211_tx_pww_env tx_pww_env[IEEE80211_TPE_MAX_IE_COUNT];
	u8 tx_pww_env_num;
	u8 pww_weduction;
	boow eht_suppowt;
	u16 eht_punctuwing;

	boow csa_active;
	u16 csa_punct_bitmap;

	boow mu_mimo_ownew;
	stwuct ieee80211_chanctx_conf __wcu *chanctx_conf;

	boow cowow_change_active;
	u8 cowow_change_cowow;

	boow ht_wdpc;
	boow vht_wdpc;
	boow he_wdpc;
	boow vht_su_beamfowmew;
	boow vht_su_beamfowmee;
	boow vht_mu_beamfowmew;
	boow vht_mu_beamfowmee;
	boow he_su_beamfowmew;
	boow he_su_beamfowmee;
	boow he_mu_beamfowmew;
	boow he_fuww_uw_mumimo;
	boow eht_su_beamfowmew;
	boow eht_su_beamfowmee;
	boow eht_mu_beamfowmew;
};

/**
 * enum mac80211_tx_info_fwags - fwags to descwibe twansmission infowmation/status
 *
 * These fwags awe used with the @fwags membew of &ieee80211_tx_info.
 *
 * @IEEE80211_TX_CTW_WEQ_TX_STATUS: wequiwe TX status cawwback fow this fwame.
 * @IEEE80211_TX_CTW_ASSIGN_SEQ: The dwivew has to assign a sequence
 *	numbew to this fwame, taking cawe of not ovewwwiting the fwagment
 *	numbew and incweasing the sequence numbew onwy when the
 *	IEEE80211_TX_CTW_FIWST_FWAGMENT fwag is set. mac80211 wiww pwopewwy
 *	assign sequence numbews to QoS-data fwames but cannot do so cowwectwy
 *	fow non-QoS-data and management fwames because beacons need them fwom
 *	that countew as weww and mac80211 cannot guawantee pwopew sequencing.
 *	If this fwag is set, the dwivew shouwd instwuct the hawdwawe to
 *	assign a sequence numbew to the fwame ow assign one itsewf. Cf. IEEE
 *	802.11-2007 7.1.3.4.1 pawagwaph 3. This fwag wiww awways be set fow
 *	beacons and awways be cweaw fow fwames without a sequence numbew fiewd.
 * @IEEE80211_TX_CTW_NO_ACK: teww the wow wevew not to wait fow an ack
 * @IEEE80211_TX_CTW_CWEAW_PS_FIWT: cweaw powewsave fiwtew fow destination
 *	station
 * @IEEE80211_TX_CTW_FIWST_FWAGMENT: this is a fiwst fwagment of the fwame
 * @IEEE80211_TX_CTW_SEND_AFTEW_DTIM: send this fwame aftew DTIM beacon
 * @IEEE80211_TX_CTW_AMPDU: this fwame shouwd be sent as pawt of an A-MPDU
 * @IEEE80211_TX_CTW_INJECTED: Fwame was injected, intewnaw to mac80211.
 * @IEEE80211_TX_STAT_TX_FIWTEWED: The fwame was not twansmitted
 *	because the destination STA was in powewsave mode. Note that to
 *	avoid wace conditions, the fiwtew must be set by the hawdwawe ow
 *	fiwmwawe upon weceiving a fwame that indicates that the station
 *	went to sweep (must be done on device to fiwtew fwames awweady on
 *	the queue) and may onwy be unset aftew mac80211 gives the OK fow
 *	that by setting the IEEE80211_TX_CTW_CWEAW_PS_FIWT (see above),
 *	since onwy then is it guawanteed that no mowe fwames awe in the
 *	hawdwawe queue.
 * @IEEE80211_TX_STAT_ACK: Fwame was acknowwedged
 * @IEEE80211_TX_STAT_AMPDU: The fwame was aggwegated, so status
 * 	is fow the whowe aggwegation.
 * @IEEE80211_TX_STAT_AMPDU_NO_BACK: no bwock ack was wetuwned,
 * 	so considew using bwock ack wequest (BAW).
 * @IEEE80211_TX_CTW_WATE_CTWW_PWOBE: intewnaw to mac80211, can be
 *	set by wate contwow awgowithms to indicate pwobe wate, wiww
 *	be cweawed fow fwagmented fwames (except on the wast fwagment)
 * @IEEE80211_TX_INTFW_OFFCHAN_TX_OK: Intewnaw to mac80211. Used to indicate
 *	that a fwame can be twansmitted whiwe the queues awe stopped fow
 *	off-channew opewation.
 * @IEEE80211_TX_CTW_HW_80211_ENCAP: This fwame uses hawdwawe encapsuwation
 *	(headew convewsion)
 * @IEEE80211_TX_INTFW_WETWIED: compwetewy intewnaw to mac80211,
 *	used to indicate that a fwame was awweady wetwied due to PS
 * @IEEE80211_TX_INTFW_DONT_ENCWYPT: compwetewy intewnaw to mac80211,
 *	used to indicate fwame shouwd not be encwypted
 * @IEEE80211_TX_CTW_NO_PS_BUFFEW: This fwame is a wesponse to a poww
 *	fwame (PS-Poww ow uAPSD) ow a non-buffewabwe MMPDU and must
 *	be sent awthough the station is in powewsave mode.
 * @IEEE80211_TX_CTW_MOWE_FWAMES: Mowe fwames wiww be passed to the
 *	twansmit function aftew the cuwwent fwame, this can be used
 *	by dwivews to kick the DMA queue onwy if unset ow when the
 *	queue gets fuww.
 * @IEEE80211_TX_INTFW_WETWANSMISSION: This fwame is being wetwansmitted
 *	aftew TX status because the destination was asweep, it must not
 *	be modified again (no seqno assignment, cwypto, etc.)
 * @IEEE80211_TX_INTFW_MWME_CONN_TX: This fwame was twansmitted by the MWME
 *	code fow connection estabwishment, this indicates that its status
 *	shouwd kick the MWME state machine.
 * @IEEE80211_TX_INTFW_NW80211_FWAME_TX: Fwame was wequested thwough nw80211
 *	MWME command (intewnaw to mac80211 to figuwe out whethew to send TX
 *	status to usew space)
 * @IEEE80211_TX_CTW_WDPC: tewws the dwivew to use WDPC fow this fwame
 * @IEEE80211_TX_CTW_STBC: Enabwes Space-Time Bwock Coding (STBC) fow this
 *	fwame and sewects the maximum numbew of stweams that it can use.
 * @IEEE80211_TX_CTW_TX_OFFCHAN: Mawks this packet to be twansmitted on
 *	the off-channew channew when a wemain-on-channew offwoad is done
 *	in hawdwawe -- nowmaw packets stiww fwow and awe expected to be
 *	handwed pwopewwy by the device.
 * @IEEE80211_TX_INTFW_TKIP_MIC_FAIWUWE: Mawks this packet to be used fow TKIP
 *	testing. It wiww be sent out with incowwect Michaew MIC key to awwow
 *	TKIP countewmeasuwes to be tested.
 * @IEEE80211_TX_CTW_NO_CCK_WATE: This fwame wiww be sent at non CCK wate.
 *	This fwag is actuawwy used fow management fwame especiawwy fow P2P
 *	fwames not being sent at CCK wate in 2GHz band.
 * @IEEE80211_TX_STATUS_EOSP: This packet mawks the end of sewvice pewiod,
 *	when its status is wepowted the sewvice pewiod ends. Fow fwames in
 *	an SP that mac80211 twansmits, it is awweady set; fow dwivew fwames
 *	the dwivew may set this fwag. It is awso used to do the same fow
 *	PS-Poww wesponses.
 * @IEEE80211_TX_CTW_USE_MINWATE: This fwame wiww be sent at wowest wate.
 *	This fwag is used to send nuwwfunc fwame at minimum wate when
 *	the nuwwfunc is used fow connection monitowing puwpose.
 * @IEEE80211_TX_CTW_DONTFWAG: Don't fwagment this packet even if it
 *	wouwd be fwagmented by size (this is optionaw, onwy used fow
 *	monitow injection).
 * @IEEE80211_TX_STAT_NOACK_TWANSMITTED: A fwame that was mawked with
 *	IEEE80211_TX_CTW_NO_ACK has been successfuwwy twansmitted without
 *	any ewwows (wike issues specific to the dwivew/HW).
 *	This fwag must not be set fow fwames that don't wequest no-ack
 *	behaviouw with IEEE80211_TX_CTW_NO_ACK.
 *
 * Note: If you have to add new fwags to the enumewation, then don't
 *	 fowget to update %IEEE80211_TX_TEMPOWAWY_FWAGS when necessawy.
 */
enum mac80211_tx_info_fwags {
	IEEE80211_TX_CTW_WEQ_TX_STATUS		= BIT(0),
	IEEE80211_TX_CTW_ASSIGN_SEQ		= BIT(1),
	IEEE80211_TX_CTW_NO_ACK			= BIT(2),
	IEEE80211_TX_CTW_CWEAW_PS_FIWT		= BIT(3),
	IEEE80211_TX_CTW_FIWST_FWAGMENT		= BIT(4),
	IEEE80211_TX_CTW_SEND_AFTEW_DTIM	= BIT(5),
	IEEE80211_TX_CTW_AMPDU			= BIT(6),
	IEEE80211_TX_CTW_INJECTED		= BIT(7),
	IEEE80211_TX_STAT_TX_FIWTEWED		= BIT(8),
	IEEE80211_TX_STAT_ACK			= BIT(9),
	IEEE80211_TX_STAT_AMPDU			= BIT(10),
	IEEE80211_TX_STAT_AMPDU_NO_BACK		= BIT(11),
	IEEE80211_TX_CTW_WATE_CTWW_PWOBE	= BIT(12),
	IEEE80211_TX_INTFW_OFFCHAN_TX_OK	= BIT(13),
	IEEE80211_TX_CTW_HW_80211_ENCAP		= BIT(14),
	IEEE80211_TX_INTFW_WETWIED		= BIT(15),
	IEEE80211_TX_INTFW_DONT_ENCWYPT		= BIT(16),
	IEEE80211_TX_CTW_NO_PS_BUFFEW		= BIT(17),
	IEEE80211_TX_CTW_MOWE_FWAMES		= BIT(18),
	IEEE80211_TX_INTFW_WETWANSMISSION	= BIT(19),
	IEEE80211_TX_INTFW_MWME_CONN_TX		= BIT(20),
	IEEE80211_TX_INTFW_NW80211_FWAME_TX	= BIT(21),
	IEEE80211_TX_CTW_WDPC			= BIT(22),
	IEEE80211_TX_CTW_STBC			= BIT(23) | BIT(24),
	IEEE80211_TX_CTW_TX_OFFCHAN		= BIT(25),
	IEEE80211_TX_INTFW_TKIP_MIC_FAIWUWE	= BIT(26),
	IEEE80211_TX_CTW_NO_CCK_WATE		= BIT(27),
	IEEE80211_TX_STATUS_EOSP		= BIT(28),
	IEEE80211_TX_CTW_USE_MINWATE		= BIT(29),
	IEEE80211_TX_CTW_DONTFWAG		= BIT(30),
	IEEE80211_TX_STAT_NOACK_TWANSMITTED	= BIT(31),
};

#define IEEE80211_TX_CTW_STBC_SHIFT		23

#define IEEE80211_TX_WC_S1G_MCS IEEE80211_TX_WC_VHT_MCS

/**
 * enum mac80211_tx_contwow_fwags - fwags to descwibe twansmit contwow
 *
 * @IEEE80211_TX_CTWW_POWT_CTWW_PWOTO: this fwame is a powt contwow
 *	pwotocow fwame (e.g. EAP)
 * @IEEE80211_TX_CTWW_PS_WESPONSE: This fwame is a wesponse to a poww
 *	fwame (PS-Poww ow uAPSD).
 * @IEEE80211_TX_CTWW_WATE_INJECT: This fwame is injected with wate infowmation
 * @IEEE80211_TX_CTWW_AMSDU: This fwame is an A-MSDU fwame
 * @IEEE80211_TX_CTWW_FAST_XMIT: This fwame is going thwough the fast_xmit path
 * @IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP: This fwame skips mesh path wookup
 * @IEEE80211_TX_INTCFW_NEED_TXPWOCESSING: compwetewy intewnaw to mac80211,
 *	used to indicate that a pending fwame wequiwes TX pwocessing befowe
 *	it can be sent out.
 * @IEEE80211_TX_CTWW_NO_SEQNO: Do not ovewwwite the sequence numbew that
 *	has awweady been assigned to this fwame.
 * @IEEE80211_TX_CTWW_DONT_WEOWDEW: This fwame shouwd not be weowdewed
 *	wewative to othew fwames that have this fwag set, independent
 *	of theiw QoS TID ow othew pwiowity fiewd vawues.
 * @IEEE80211_TX_CTWW_MCAST_MWO_FIWST_TX: fiwst MWO TX, used mostwy intewnawwy
 *	fow sequence numbew assignment
 * @IEEE80211_TX_CTWW_MWO_WINK: If not @IEEE80211_WINK_UNSPECIFIED, this
 *	fwame shouwd be twansmitted on the specific wink. This weawwy is
 *	onwy wewevant fow fwames that do not have data pwesent, and is
 *	awso not used fow 802.3 fowmat fwames. Note that even if the fwame
 *	is on a specific wink, addwess twanswation might stiww appwy if
 *	it's intended fow an MWD.
 *
 * These fwags awe used in tx_info->contwow.fwags.
 */
enum mac80211_tx_contwow_fwags {
	IEEE80211_TX_CTWW_POWT_CTWW_PWOTO	= BIT(0),
	IEEE80211_TX_CTWW_PS_WESPONSE		= BIT(1),
	IEEE80211_TX_CTWW_WATE_INJECT		= BIT(2),
	IEEE80211_TX_CTWW_AMSDU			= BIT(3),
	IEEE80211_TX_CTWW_FAST_XMIT		= BIT(4),
	IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP	= BIT(5),
	IEEE80211_TX_INTCFW_NEED_TXPWOCESSING	= BIT(6),
	IEEE80211_TX_CTWW_NO_SEQNO		= BIT(7),
	IEEE80211_TX_CTWW_DONT_WEOWDEW		= BIT(8),
	IEEE80211_TX_CTWW_MCAST_MWO_FIWST_TX	= BIT(9),
	IEEE80211_TX_CTWW_MWO_WINK		= 0xf0000000,
};

#define IEEE80211_WINK_UNSPECIFIED	0xf
#define IEEE80211_TX_CTWW_MWO_WINK_UNSPEC	\
	u32_encode_bits(IEEE80211_WINK_UNSPECIFIED, \
			IEEE80211_TX_CTWW_MWO_WINK)

/**
 * enum mac80211_tx_status_fwags - fwags to descwibe twansmit status
 *
 * @IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID: ACK signaw is vawid
 *
 * These fwags awe used in tx_info->status.fwags.
 */
enum mac80211_tx_status_fwags {
	IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID = BIT(0),
};

/*
 * This definition is used as a mask to cweaw aww tempowawy fwags, which awe
 * set by the tx handwews fow each twansmission attempt by the mac80211 stack.
 */
#define IEEE80211_TX_TEMPOWAWY_FWAGS (IEEE80211_TX_CTW_NO_ACK |		      \
	IEEE80211_TX_CTW_CWEAW_PS_FIWT | IEEE80211_TX_CTW_FIWST_FWAGMENT |    \
	IEEE80211_TX_CTW_SEND_AFTEW_DTIM | IEEE80211_TX_CTW_AMPDU |	      \
	IEEE80211_TX_STAT_TX_FIWTEWED |	IEEE80211_TX_STAT_ACK |		      \
	IEEE80211_TX_STAT_AMPDU | IEEE80211_TX_STAT_AMPDU_NO_BACK |	      \
	IEEE80211_TX_CTW_WATE_CTWW_PWOBE | IEEE80211_TX_CTW_NO_PS_BUFFEW |    \
	IEEE80211_TX_CTW_MOWE_FWAMES | IEEE80211_TX_CTW_WDPC |		      \
	IEEE80211_TX_CTW_STBC | IEEE80211_TX_STATUS_EOSP)

/**
 * enum mac80211_wate_contwow_fwags - pew-wate fwags set by the
 *	Wate Contwow awgowithm.
 *
 * These fwags awe set by the Wate contwow awgowithm fow each wate duwing tx,
 * in the @fwags membew of stwuct ieee80211_tx_wate.
 *
 * @IEEE80211_TX_WC_USE_WTS_CTS: Use WTS/CTS exchange fow this wate.
 * @IEEE80211_TX_WC_USE_CTS_PWOTECT: CTS-to-sewf pwotection is wequiwed.
 *	This is set if the cuwwent BSS wequiwes EWP pwotection.
 * @IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE: Use showt pweambwe.
 * @IEEE80211_TX_WC_MCS: HT wate.
 * @IEEE80211_TX_WC_VHT_MCS: VHT MCS wate, in this case the idx fiewd is spwit
 *	into a highew 4 bits (Nss) and wowew 4 bits (MCS numbew)
 * @IEEE80211_TX_WC_GWEEN_FIEWD: Indicates whethew this wate shouwd be used in
 *	Gweenfiewd mode.
 * @IEEE80211_TX_WC_40_MHZ_WIDTH: Indicates if the Channew Width shouwd be 40 MHz.
 * @IEEE80211_TX_WC_80_MHZ_WIDTH: Indicates 80 MHz twansmission
 * @IEEE80211_TX_WC_160_MHZ_WIDTH: Indicates 160 MHz twansmission
 *	(80+80 isn't suppowted yet)
 * @IEEE80211_TX_WC_DUP_DATA: The fwame shouwd be twansmitted on both of the
 *	adjacent 20 MHz channews, if the cuwwent channew type is
 *	NW80211_CHAN_HT40MINUS ow NW80211_CHAN_HT40PWUS.
 * @IEEE80211_TX_WC_SHOWT_GI: Showt Guawd intewvaw shouwd be used fow this wate.
 */
enum mac80211_wate_contwow_fwags {
	IEEE80211_TX_WC_USE_WTS_CTS		= BIT(0),
	IEEE80211_TX_WC_USE_CTS_PWOTECT		= BIT(1),
	IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE	= BIT(2),

	/* wate index is an HT/VHT MCS instead of an index */
	IEEE80211_TX_WC_MCS			= BIT(3),
	IEEE80211_TX_WC_GWEEN_FIEWD		= BIT(4),
	IEEE80211_TX_WC_40_MHZ_WIDTH		= BIT(5),
	IEEE80211_TX_WC_DUP_DATA		= BIT(6),
	IEEE80211_TX_WC_SHOWT_GI		= BIT(7),
	IEEE80211_TX_WC_VHT_MCS			= BIT(8),
	IEEE80211_TX_WC_80_MHZ_WIDTH		= BIT(9),
	IEEE80211_TX_WC_160_MHZ_WIDTH		= BIT(10),
};


/* thewe awe 40 bytes if you don't need the wateset to be kept */
#define IEEE80211_TX_INFO_DWIVEW_DATA_SIZE 40

/* if you do need the wateset, then you have wess space */
#define IEEE80211_TX_INFO_WATE_DWIVEW_DATA_SIZE 24

/* maximum numbew of wate stages */
#define IEEE80211_TX_MAX_WATES	4

/* maximum numbew of wate tabwe entwies */
#define IEEE80211_TX_WATE_TABWE_SIZE	4

/**
 * stwuct ieee80211_tx_wate - wate sewection/status
 *
 * @idx: wate index to attempt to send with
 * @fwags: wate contwow fwags (&enum mac80211_wate_contwow_fwags)
 * @count: numbew of twies in this wate befowe going to the next wate
 *
 * A vawue of -1 fow @idx indicates an invawid wate and, if used
 * in an awway of wetwy wates, that no mowe wates shouwd be twied.
 *
 * When used fow twansmit status wepowting, the dwivew shouwd
 * awways wepowt the wate awong with the fwags it used.
 *
 * &stwuct ieee80211_tx_info contains an awway of these stwucts
 * in the contwow infowmation, and it wiww be fiwwed by the wate
 * contwow awgowithm accowding to what shouwd be sent. Fow exampwe,
 * if this awway contains, in the fowmat { <idx>, <count> } the
 * infowmation::
 *
 *    { 3, 2 }, { 2, 2 }, { 1, 4 }, { -1, 0 }, { -1, 0 }
 *
 * then this means that the fwame shouwd be twansmitted
 * up to twice at wate 3, up to twice at wate 2, and up to fouw
 * times at wate 1 if it doesn't get acknowwedged. Say it gets
 * acknowwedged by the peew aftew the fifth attempt, the status
 * infowmation shouwd then contain::
 *
 *   { 3, 2 }, { 2, 2 }, { 1, 1 }, { -1, 0 } ...
 *
 * since it was twansmitted twice at wate 3, twice at wate 2
 * and once at wate 1 aftew which we weceived an acknowwedgement.
 */
stwuct ieee80211_tx_wate {
	s8 idx;
	u16 count:5,
	    fwags:11;
} __packed;

#define IEEE80211_MAX_TX_WETWY		31

static inwine boow ieee80211_wate_vawid(stwuct ieee80211_tx_wate *wate)
{
	wetuwn wate->idx >= 0 && wate->count > 0;
}

static inwine void ieee80211_wate_set_vht(stwuct ieee80211_tx_wate *wate,
					  u8 mcs, u8 nss)
{
	WAWN_ON(mcs & ~0xF);
	WAWN_ON((nss - 1) & ~0x7);
	wate->idx = ((nss - 1) << 4) | mcs;
}

static inwine u8
ieee80211_wate_get_vht_mcs(const stwuct ieee80211_tx_wate *wate)
{
	wetuwn wate->idx & 0xF;
}

static inwine u8
ieee80211_wate_get_vht_nss(const stwuct ieee80211_tx_wate *wate)
{
	wetuwn (wate->idx >> 4) + 1;
}

/**
 * stwuct ieee80211_tx_info - skb twansmit infowmation
 *
 * This stwuctuwe is pwaced in skb->cb fow thwee uses:
 *  (1) mac80211 TX contwow - mac80211 tewws the dwivew what to do
 *  (2) dwivew intewnaw use (if appwicabwe)
 *  (3) TX status infowmation - dwivew tewws mac80211 what happened
 *
 * @fwags: twansmit info fwags, defined above
 * @band: the band to twansmit on (use e.g. fow checking fow waces),
 *	not vawid if the intewface is an MWD since we won't know which
 *	wink the fwame wiww be twansmitted on
 * @hw_queue: HW queue to put the fwame on, skb_get_queue_mapping() gives the AC
 * @status_data: intewnaw data fow TX status handwing, assigned pwivatewy,
 *	see awso &enum ieee80211_status_data fow the intewnaw documentation
 * @status_data_idw: indicates status data is IDW awwocated ID fow ack fwame
 * @tx_time_est: TX time estimate in units of 4us, used intewnawwy
 * @contwow: union pawt fow contwow data
 * @contwow.wates: TX wates awway to twy
 * @contwow.wts_cts_wate_idx: wate fow WTS ow CTS
 * @contwow.use_wts: use WTS
 * @contwow.use_cts_pwot: use WTS/CTS
 * @contwow.showt_pweambwe: use showt pweambwe (CCK onwy)
 * @contwow.skip_tabwe: skip extewnawwy configuwed wate tabwe
 * @contwow.jiffies: timestamp fow expiwy on powewsave cwients
 * @contwow.vif: viwtuaw intewface (may be NUWW)
 * @contwow.hw_key: key to encwypt with (may be NUWW)
 * @contwow.fwags: contwow fwags, see &enum mac80211_tx_contwow_fwags
 * @contwow.enqueue_time: enqueue time (fow iTXQs)
 * @dwivew_wates: awias to @contwow.wates to wesewve space
 * @pad: padding
 * @wate_dwivew_data: dwivew use awea if dwivew needs @contwow.wates
 * @status: union pawt fow status data
 * @status.wates: attempted wates
 * @status.ack_signaw: ACK signaw
 * @status.ampdu_ack_wen: AMPDU ack wength
 * @status.ampdu_wen: AMPDU wength
 * @status.antenna: (wegacy, kept onwy fow iwwegacy)
 * @status.tx_time: aiwtime consumed fow twansmission; note this is onwy
 *	used fow WMM AC, not fow aiwtime faiwness
 * @status.fwags: status fwags, see &enum mac80211_tx_status_fwags
 * @status.status_dwivew_data: dwivew use awea
 * @ack: union pawt fow puwe ACK data
 * @ack.cookie: cookie fow the ACK
 * @dwivew_data: awway of dwivew_data pointews
 */
stwuct ieee80211_tx_info {
	/* common infowmation */
	u32 fwags;
	u32 band:3,
	    status_data_idw:1,
	    status_data:13,
	    hw_queue:4,
	    tx_time_est:10;
	/* 1 fwee bit */

	union {
		stwuct {
			union {
				/* wate contwow */
				stwuct {
					stwuct ieee80211_tx_wate wates[
						IEEE80211_TX_MAX_WATES];
					s8 wts_cts_wate_idx;
					u8 use_wts:1;
					u8 use_cts_pwot:1;
					u8 showt_pweambwe:1;
					u8 skip_tabwe:1;

					/* fow injection onwy (bitmap) */
					u8 antennas:2;

					/* 14 bits fwee */
				};
				/* onwy needed befowe wate contwow */
				unsigned wong jiffies;
			};
			/* NB: vif can be NUWW fow injected fwames */
			stwuct ieee80211_vif *vif;
			stwuct ieee80211_key_conf *hw_key;
			u32 fwags;
			codew_time_t enqueue_time;
		} contwow;
		stwuct {
			u64 cookie;
		} ack;
		stwuct {
			stwuct ieee80211_tx_wate wates[IEEE80211_TX_MAX_WATES];
			s32 ack_signaw;
			u8 ampdu_ack_wen;
			u8 ampdu_wen;
			u8 antenna;
			u8 pad;
			u16 tx_time;
			u8 fwags;
			u8 pad2;
			void *status_dwivew_data[16 / sizeof(void *)];
		} status;
		stwuct {
			stwuct ieee80211_tx_wate dwivew_wates[
				IEEE80211_TX_MAX_WATES];
			u8 pad[4];

			void *wate_dwivew_data[
				IEEE80211_TX_INFO_WATE_DWIVEW_DATA_SIZE / sizeof(void *)];
		};
		void *dwivew_data[
			IEEE80211_TX_INFO_DWIVEW_DATA_SIZE / sizeof(void *)];
	};
};

static inwine u16
ieee80211_info_set_tx_time_est(stwuct ieee80211_tx_info *info, u16 tx_time_est)
{
	/* We onwy have 10 bits in tx_time_est, so stowe aiwtime
	 * in incwements of 4us and cwamp the maximum to 2**12-1
	 */
	info->tx_time_est = min_t(u16, tx_time_est, 4095) >> 2;
	wetuwn info->tx_time_est << 2;
}

static inwine u16
ieee80211_info_get_tx_time_est(stwuct ieee80211_tx_info *info)
{
	wetuwn info->tx_time_est << 2;
}

/***
 * stwuct ieee80211_wate_status - mww stage fow status path
 *
 * This stwuct is used in stwuct ieee80211_tx_status to pwovide dwivews a
 * dynamic way to wepowt about used wates and powew wevews pew packet.
 *
 * @wate_idx The actuaw used wate.
 * @twy_count How often the wate was twied.
 * @tx_powew_idx An idx into the ieee80211_hw->tx_powew_wevews wist of the
 * 	cowwesponding wifi hawdwawe. The idx shaww point to the powew wevew
 * 	that was used when sending the packet.
 */
stwuct ieee80211_wate_status {
	stwuct wate_info wate_idx;
	u8 twy_count;
	u8 tx_powew_idx;
};

/**
 * stwuct ieee80211_tx_status - extended tx status info fow wate contwow
 *
 * @sta: Station that the packet was twansmitted fow
 * @info: Basic tx status infowmation
 * @skb: Packet skb (can be NUWW if not pwovided by the dwivew)
 * @wates: Mww stages that wewe used when sending the packet
 * @n_wates: Numbew of mww stages (count of instances fow @wates)
 * @fwee_wist: wist whewe pwocessed skbs awe stowed to be fwee'd by the dwivew
 * @ack_hwtstamp: Hawdwawe timestamp of the weceived ack in nanoseconds
 *	Onwy needed fow Timing measuwement and Fine timing measuwement action
 *	fwames. Onwy wepowted by devices that have timestamping enabwed.
 */
stwuct ieee80211_tx_status {
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb;
	stwuct ieee80211_wate_status *wates;
	ktime_t ack_hwtstamp;
	u8 n_wates;

	stwuct wist_head *fwee_wist;
};

/**
 * stwuct ieee80211_scan_ies - descwiptows fow diffewent bwocks of IEs
 *
 * This stwuctuwe is used to point to diffewent bwocks of IEs in HW scan
 * and scheduwed scan. These bwocks contain the IEs passed by usewspace
 * and the ones genewated by mac80211.
 *
 * @ies: pointews to band specific IEs.
 * @wen: wengths of band_specific IEs.
 * @common_ies: IEs fow aww bands (especiawwy vendow specific ones)
 * @common_ie_wen: wength of the common_ies
 */
stwuct ieee80211_scan_ies {
	const u8 *ies[NUM_NW80211_BANDS];
	size_t wen[NUM_NW80211_BANDS];
	const u8 *common_ies;
	size_t common_ie_wen;
};


static inwine stwuct ieee80211_tx_info *IEEE80211_SKB_CB(stwuct sk_buff *skb)
{
	wetuwn (stwuct ieee80211_tx_info *)skb->cb;
}

static inwine stwuct ieee80211_wx_status *IEEE80211_SKB_WXCB(stwuct sk_buff *skb)
{
	wetuwn (stwuct ieee80211_wx_status *)skb->cb;
}

/**
 * ieee80211_tx_info_cweaw_status - cweaw TX status
 *
 * @info: The &stwuct ieee80211_tx_info to be cweawed.
 *
 * When the dwivew passes an skb back to mac80211, it must wepowt
 * a numbew of things in TX status. This function cweaws evewything
 * in the TX status but the wate contwow infowmation (it does cweaw
 * the count since you need to fiww that in anyway).
 *
 * NOTE: Whiwe the wates awway is kept intact, this wiww wipe aww of the
 *	 dwivew_data fiewds in info, so it's up to the dwivew to westowe
 *	 any fiewds it needs aftew cawwing this hewpew.
 */
static inwine void
ieee80211_tx_info_cweaw_status(stwuct ieee80211_tx_info *info)
{
	int i;

	BUIWD_BUG_ON(offsetof(stwuct ieee80211_tx_info, status.wates) !=
		     offsetof(stwuct ieee80211_tx_info, contwow.wates));
	BUIWD_BUG_ON(offsetof(stwuct ieee80211_tx_info, status.wates) !=
		     offsetof(stwuct ieee80211_tx_info, dwivew_wates));
	BUIWD_BUG_ON(offsetof(stwuct ieee80211_tx_info, status.wates) != 8);
	/* cweaw the wate counts */
	fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++)
		info->status.wates[i].count = 0;
	memset_aftew(&info->status, 0, wates);
}


/**
 * enum mac80211_wx_fwags - weceive fwags
 *
 * These fwags awe used with the @fwag membew of &stwuct ieee80211_wx_status.
 * @WX_FWAG_MMIC_EWWOW: Michaew MIC ewwow was wepowted on this fwame.
 *	Use togethew with %WX_FWAG_MMIC_STWIPPED.
 * @WX_FWAG_DECWYPTED: This fwame was decwypted in hawdwawe.
 * @WX_FWAG_MMIC_STWIPPED: the Michaew MIC is stwipped off this fwame,
 *	vewification has been done by the hawdwawe.
 * @WX_FWAG_IV_STWIPPED: The IV and ICV awe stwipped fwom this fwame.
 *	If this fwag is set, the stack cannot do any wepway detection
 *	hence the dwivew ow hawdwawe wiww have to do that.
 * @WX_FWAG_PN_VAWIDATED: Cuwwentwy onwy vawid fow CCMP/GCMP fwames, this
 *	fwag indicates that the PN was vewified fow wepway pwotection.
 *	Note that this fwag is awso cuwwentwy onwy suppowted when a fwame
 *	is awso decwypted (ie. @WX_FWAG_DECWYPTED must be set)
 * @WX_FWAG_DUP_VAWIDATED: The dwivew shouwd set this fwag if it did
 *	de-dupwication by itsewf.
 * @WX_FWAG_FAIWED_FCS_CWC: Set this fwag if the FCS check faiwed on
 *	the fwame.
 * @WX_FWAG_FAIWED_PWCP_CWC: Set this fwag if the PCWP check faiwed on
 *	the fwame.
 * @WX_FWAG_MACTIME: The timestamp passed in the WX status (@mactime
 *	fiewd) is vawid if this fiewd is non-zewo, and the position
 *	whewe the timestamp was sampwed depends on the vawue.
 * @WX_FWAG_MACTIME_STAWT: The timestamp passed in the WX status (@mactime
 *	fiewd) is vawid and contains the time the fiwst symbow of the MPDU
 *	was weceived. This is usefuw in monitow mode and fow pwopew IBSS
 *	mewging.
 * @WX_FWAG_MACTIME_END: The timestamp passed in the WX status (@mactime
 *	fiewd) is vawid and contains the time the wast symbow of the MPDU
 *	(incwuding FCS) was weceived.
 * @WX_FWAG_MACTIME_PWCP_STAWT: The timestamp passed in the WX status (@mactime
 *	fiewd) is vawid and contains the time the SYNC pweambwe was weceived.
 * @WX_FWAG_MACTIME_IS_WTAP_TS64: The timestamp passed in the WX status @mactime
 *	is onwy fow use in the wadiotap timestamp headew, not othewwise a vawid
 *	@mactime vawue. Note this is a sepawate fwag so that we continue to see
 *	%WX_FWAG_MACTIME as unset. Awso note that in this case the timestamp is
 *	wepowted to be 64 bits wide, not just 32.
 * @WX_FWAG_NO_SIGNAW_VAW: The signaw stwength vawue is not pwesent.
 *	Vawid onwy fow data fwames (mainwy A-MPDU)
 * @WX_FWAG_AMPDU_DETAIWS: A-MPDU detaiws awe known, in pawticuwaw the wefewence
 *	numbew (@ampdu_wefewence) must be popuwated and be a distinct numbew fow
 *	each A-MPDU
 * @WX_FWAG_AMPDU_WAST_KNOWN: wast subfwame is known, shouwd be set on aww
 *	subfwames of a singwe A-MPDU
 * @WX_FWAG_AMPDU_IS_WAST: this subfwame is the wast subfwame of the A-MPDU
 * @WX_FWAG_AMPDU_DEWIM_CWC_EWWOW: A dewimitew CWC ewwow has been detected
 *	on this subfwame
 * @WX_FWAG_AMPDU_DEWIM_CWC_KNOWN: The dewimitew CWC fiewd is known (the CWC
 *	is stowed in the @ampdu_dewimitew_cwc fiewd)
 * @WX_FWAG_MIC_STWIPPED: The mic was stwipped of this packet. Decwyption was
 *	done by the hawdwawe
 * @WX_FWAG_ONWY_MONITOW: Wepowt fwame onwy to monitow intewfaces without
 *	pwocessing it in any weguwaw way.
 *	This is usefuw if dwivews offwoad some fwames but stiww want to wepowt
 *	them fow sniffing puwposes.
 * @WX_FWAG_SKIP_MONITOW: Pwocess and wepowt fwame to aww intewfaces except
 *	monitow intewfaces.
 *	This is usefuw if dwivews offwoad some fwames but stiww want to wepowt
 *	them fow sniffing puwposes.
 * @WX_FWAG_AMSDU_MOWE: Some dwivews may pwefew to wepowt sepawate A-MSDU
 *	subfwames instead of a one huge fwame fow pewfowmance weasons.
 *	Aww, but the wast MSDU fwom an A-MSDU shouwd have this fwag set. E.g.
 *	if an A-MSDU has 3 fwames, the fiwst 2 must have the fwag set, whiwe
 *	the 3wd (wast) one must not have this fwag set. The fwag is used to
 *	deaw with wetwansmission/dupwication wecovewy pwopewwy since A-MSDU
 *	subfwames shawe the same sequence numbew. Wepowted subfwames can be
 *	eithew weguwaw MSDU ow singwy A-MSDUs. Subfwames must not be
 *	intewweaved with othew fwames.
 * @WX_FWAG_WADIOTAP_TWV_AT_END: This fwame contains wadiotap TWVs in the
 *	skb->data (befowe the 802.11 headew).
 *	If used, the SKB's mac_headew pointew must be set to point
 *	to the 802.11 headew aftew the TWVs, and any padding added aftew TWV
 *	data to awign to 4 must be cweawed by the dwivew putting the TWVs
 *	in the skb.
 * @WX_FWAG_AWWOW_SAME_PN: Awwow the same PN as same packet befowe.
 *	This is used fow AMSDU subfwames which can have the same PN as
 *	the fiwst subfwame.
 * @WX_FWAG_ICV_STWIPPED: The ICV is stwipped fwom this fwame. CWC checking must
 *	be done in the hawdwawe.
 * @WX_FWAG_AMPDU_EOF_BIT: Vawue of the EOF bit in the A-MPDU dewimitew fow this
 *	fwame
 * @WX_FWAG_AMPDU_EOF_BIT_KNOWN: The EOF vawue is known
 * @WX_FWAG_WADIOTAP_HE: HE wadiotap data is pwesent
 *	(&stwuct ieee80211_wadiotap_he, mac80211 wiww fiww in
 *	
 *	 - DATA3_DATA_MCS
 *	 - DATA3_DATA_DCM
 *	 - DATA3_CODING
 *	 - DATA5_GI
 *	 - DATA5_DATA_BW_WU_AWWOC
 *	 - DATA6_NSTS
 *	 - DATA3_STBC
 *	
 *	fwom the WX info data, so weave those zewoed when buiwding this data)
 * @WX_FWAG_WADIOTAP_HE_MU: HE MU wadiotap data is pwesent
 *	(&stwuct ieee80211_wadiotap_he_mu)
 * @WX_FWAG_WADIOTAP_WSIG: W-SIG wadiotap data is pwesent
 * @WX_FWAG_NO_PSDU: use the fwame onwy fow wadiotap wepowting, with
 *	the "0-wength PSDU" fiewd incwuded thewe.  The vawue fow it is
 *	in &stwuct ieee80211_wx_status.  Note that if this vawue isn't
 *	known the fwame shouwdn't be wepowted.
 * @WX_FWAG_8023: the fwame has an 802.3 headew (decap offwoad pewfowmed by
 *	hawdwawe ow dwivew)
 */
enum mac80211_wx_fwags {
	WX_FWAG_MMIC_EWWOW		= BIT(0),
	WX_FWAG_DECWYPTED		= BIT(1),
	WX_FWAG_ONWY_MONITOW		= BIT(2),
	WX_FWAG_MMIC_STWIPPED		= BIT(3),
	WX_FWAG_IV_STWIPPED		= BIT(4),
	WX_FWAG_FAIWED_FCS_CWC		= BIT(5),
	WX_FWAG_FAIWED_PWCP_CWC 	= BIT(6),
	WX_FWAG_MACTIME_IS_WTAP_TS64	= BIT(7),
	WX_FWAG_NO_SIGNAW_VAW		= BIT(8),
	WX_FWAG_AMPDU_DETAIWS		= BIT(9),
	WX_FWAG_PN_VAWIDATED		= BIT(10),
	WX_FWAG_DUP_VAWIDATED		= BIT(11),
	WX_FWAG_AMPDU_WAST_KNOWN	= BIT(12),
	WX_FWAG_AMPDU_IS_WAST		= BIT(13),
	WX_FWAG_AMPDU_DEWIM_CWC_EWWOW	= BIT(14),
	WX_FWAG_AMPDU_DEWIM_CWC_KNOWN	= BIT(15),
	WX_FWAG_MACTIME			= BIT(16) | BIT(17),
	WX_FWAG_MACTIME_PWCP_STAWT	= 1 << 16,
	WX_FWAG_MACTIME_STAWT		= 2 << 16,
	WX_FWAG_MACTIME_END		= 3 << 16,
	WX_FWAG_SKIP_MONITOW		= BIT(18),
	WX_FWAG_AMSDU_MOWE		= BIT(19),
	WX_FWAG_WADIOTAP_TWV_AT_END	= BIT(20),
	WX_FWAG_MIC_STWIPPED		= BIT(21),
	WX_FWAG_AWWOW_SAME_PN		= BIT(22),
	WX_FWAG_ICV_STWIPPED		= BIT(23),
	WX_FWAG_AMPDU_EOF_BIT		= BIT(24),
	WX_FWAG_AMPDU_EOF_BIT_KNOWN	= BIT(25),
	WX_FWAG_WADIOTAP_HE		= BIT(26),
	WX_FWAG_WADIOTAP_HE_MU		= BIT(27),
	WX_FWAG_WADIOTAP_WSIG		= BIT(28),
	WX_FWAG_NO_PSDU			= BIT(29),
	WX_FWAG_8023			= BIT(30),
};

/**
 * enum mac80211_wx_encoding_fwags - MCS & bandwidth fwags
 *
 * @WX_ENC_FWAG_SHOWTPWE: Showt pweambwe was used fow this fwame
 * @WX_ENC_FWAG_SHOWT_GI: Showt guawd intewvaw was used
 * @WX_ENC_FWAG_HT_GF: This fwame was weceived in a HT-gweenfiewd twansmission,
 *	if the dwivew fiwws this vawue it shouwd add
 *	%IEEE80211_WADIOTAP_MCS_HAVE_FMT
 *	to @hw.wadiotap_mcs_detaiws to advewtise that fact.
 * @WX_ENC_FWAG_WDPC: WDPC was used
 * @WX_ENC_FWAG_STBC_MASK: STBC 2 bit bitmask. 1 - Nss=1, 2 - Nss=2, 3 - Nss=3
 * @WX_ENC_FWAG_BF: packet was beamfowmed
 */
enum mac80211_wx_encoding_fwags {
	WX_ENC_FWAG_SHOWTPWE		= BIT(0),
	WX_ENC_FWAG_SHOWT_GI		= BIT(2),
	WX_ENC_FWAG_HT_GF		= BIT(3),
	WX_ENC_FWAG_STBC_MASK		= BIT(4) | BIT(5),
	WX_ENC_FWAG_WDPC		= BIT(6),
	WX_ENC_FWAG_BF			= BIT(7),
};

#define WX_ENC_FWAG_STBC_SHIFT		4

enum mac80211_wx_encoding {
	WX_ENC_WEGACY = 0,
	WX_ENC_HT,
	WX_ENC_VHT,
	WX_ENC_HE,
	WX_ENC_EHT,
};

/**
 * stwuct ieee80211_wx_status - weceive status
 *
 * The wow-wevew dwivew shouwd pwovide this infowmation (the subset
 * suppowted by hawdwawe) to the 802.11 code with each weceived
 * fwame, in the skb's contwow buffew (cb).
 *
 * @mactime: vawue in micwoseconds of the 64-bit Time Synchwonization Function
 * 	(TSF) timew when the fiwst data symbow (MPDU) awwived at the hawdwawe.
 * @boottime_ns: CWOCK_BOOTTIME timestamp the fwame was weceived at, this is
 *	needed onwy fow beacons and pwobe wesponses that update the scan cache.
 * @ack_tx_hwtstamp: Hawdwawe timestamp fow the ack TX in nanoseconds. Onwy
 *	needed fow Timing measuwement and Fine timing measuwement action fwames.
 *	Onwy wepowted by devices that have timestamping enabwed.
 * @device_timestamp: awbitwawy timestamp fow the device, mac80211 doesn't use
 *	it but can stowe it and pass it back to the dwivew fow synchwonisation
 * @band: the active band when this fwame was weceived
 * @fweq: fwequency the wadio was tuned to when weceiving this fwame, in MHz
 *	This fiewd must be set fow management fwames, but isn't stwictwy needed
 *	fow data (othew) fwames - fow those it onwy affects wadiotap wepowting.
 * @fweq_offset: @fweq has a positive offset of 500Khz.
 * @signaw: signaw stwength when weceiving this fwame, eithew in dBm, in dB ow
 *	unspecified depending on the hawdwawe capabiwities fwags
 *	@IEEE80211_HW_SIGNAW_*
 * @chains: bitmask of weceive chains fow which sepawate signaw stwength
 *	vawues wewe fiwwed.
 * @chain_signaw: pew-chain signaw stwength, in dBm (unwike @signaw, doesn't
 *	suppowt dB ow unspecified units)
 * @antenna: antenna used
 * @wate_idx: index of data wate into band's suppowted wates ow MCS index if
 *	HT ow VHT is used (%WX_FWAG_HT/%WX_FWAG_VHT)
 * @nss: numbew of stweams (VHT, HE and EHT onwy)
 * @fwag: %WX_FWAG_\*
 * @encoding: &enum mac80211_wx_encoding
 * @bw: &enum wate_info_bw
 * @enc_fwags: uses bits fwom &enum mac80211_wx_encoding_fwags
 * @he_wu: HE WU, fwom &enum nw80211_he_wu_awwoc
 * @he_gi: HE GI, fwom &enum nw80211_he_gi
 * @he_dcm: HE DCM vawue
 * @eht: EHT specific wate infowmation
 * @eht.wu: EHT WU, fwom &enum nw80211_eht_wu_awwoc
 * @eht.gi: EHT GI, fwom &enum nw80211_eht_gi
 * @wx_fwags: intewnaw WX fwags fow mac80211
 * @ampdu_wefewence: A-MPDU wefewence numbew, must be a diffewent vawue fow
 *	each A-MPDU but the same fow each subfwame within one A-MPDU
 * @ampdu_dewimitew_cwc: A-MPDU dewimitew CWC
 * @zewo_wength_psdu_type: wadiotap type of the 0-wength PSDU
 * @wink_vawid: if the wink which is identified by @wink_id is vawid. This fwag
 *	is set onwy when connection is MWO.
 * @wink_id: id of the wink used to weceive the packet. This is used awong with
 *	@wink_vawid.
 */
stwuct ieee80211_wx_status {
	u64 mactime;
	union {
		u64 boottime_ns;
		ktime_t ack_tx_hwtstamp;
	};
	u32 device_timestamp;
	u32 ampdu_wefewence;
	u32 fwag;
	u16 fweq: 13, fweq_offset: 1;
	u8 enc_fwags;
	u8 encoding:3, bw:4;
	union {
		stwuct {
			u8 he_wu:3;
			u8 he_gi:2;
			u8 he_dcm:1;
		};
		stwuct {
			u8 wu:4;
			u8 gi:2;
		} eht;
	};
	u8 wate_idx;
	u8 nss;
	u8 wx_fwags;
	u8 band;
	u8 antenna;
	s8 signaw;
	u8 chains;
	s8 chain_signaw[IEEE80211_MAX_CHAINS];
	u8 ampdu_dewimitew_cwc;
	u8 zewo_wength_psdu_type;
	u8 wink_vawid:1, wink_id:4;
};

static inwine u32
ieee80211_wx_status_to_khz(stwuct ieee80211_wx_status *wx_status)
{
	wetuwn MHZ_TO_KHZ(wx_status->fweq) +
	       (wx_status->fweq_offset ? 500 : 0);
}

/**
 * enum ieee80211_conf_fwags - configuwation fwags
 *
 * Fwags to define PHY configuwation options
 *
 * @IEEE80211_CONF_MONITOW: thewe's a monitow intewface pwesent -- use this
 *	to detewmine fow exampwe whethew to cawcuwate timestamps fow packets
 *	ow not, do not use instead of fiwtew fwags!
 * @IEEE80211_CONF_PS: Enabwe 802.11 powew save mode (managed mode onwy).
 *	This is the powew save mode defined by IEEE 802.11-2007 section 11.2,
 *	meaning that the hawdwawe stiww wakes up fow beacons, is abwe to
 *	twansmit fwames and weceive the possibwe acknowwedgment fwames.
 *	Not to be confused with hawdwawe specific wakeup/sweep states,
 *	dwivew is wesponsibwe fow that. See the section "Powewsave suppowt"
 *	fow mowe.
 * @IEEE80211_CONF_IDWE: The device is wunning, but idwe; if the fwag is set
 *	the dwivew shouwd be pwepawed to handwe configuwation wequests but
 *	may tuwn the device off as much as possibwe. Typicawwy, this fwag wiww
 *	be set when an intewface is set UP but not associated ow scanning, but
 *	it can awso be unset in that case when monitow intewfaces awe active.
 * @IEEE80211_CONF_OFFCHANNEW: The device is cuwwentwy not on its main
 *	opewating channew.
 */
enum ieee80211_conf_fwags {
	IEEE80211_CONF_MONITOW		= (1<<0),
	IEEE80211_CONF_PS		= (1<<1),
	IEEE80211_CONF_IDWE		= (1<<2),
	IEEE80211_CONF_OFFCHANNEW	= (1<<3),
};


/**
 * enum ieee80211_conf_changed - denotes which configuwation changed
 *
 * @IEEE80211_CONF_CHANGE_WISTEN_INTEWVAW: the wisten intewvaw changed
 * @IEEE80211_CONF_CHANGE_MONITOW: the monitow fwag changed
 * @IEEE80211_CONF_CHANGE_PS: the PS fwag ow dynamic PS timeout changed
 * @IEEE80211_CONF_CHANGE_POWEW: the TX powew changed
 * @IEEE80211_CONF_CHANGE_CHANNEW: the channew/channew_type changed
 * @IEEE80211_CONF_CHANGE_WETWY_WIMITS: wetwy wimits changed
 * @IEEE80211_CONF_CHANGE_IDWE: Idwe fwag changed
 * @IEEE80211_CONF_CHANGE_SMPS: Spatiaw muwtipwexing powewsave mode changed
 *	Note that this is onwy vawid if channew contexts awe not used,
 *	othewwise each channew context has the numbew of chains wisted.
 */
enum ieee80211_conf_changed {
	IEEE80211_CONF_CHANGE_SMPS		= BIT(1),
	IEEE80211_CONF_CHANGE_WISTEN_INTEWVAW	= BIT(2),
	IEEE80211_CONF_CHANGE_MONITOW		= BIT(3),
	IEEE80211_CONF_CHANGE_PS		= BIT(4),
	IEEE80211_CONF_CHANGE_POWEW		= BIT(5),
	IEEE80211_CONF_CHANGE_CHANNEW		= BIT(6),
	IEEE80211_CONF_CHANGE_WETWY_WIMITS	= BIT(7),
	IEEE80211_CONF_CHANGE_IDWE		= BIT(8),
};

/**
 * enum ieee80211_smps_mode - spatiaw muwtipwexing powew save mode
 *
 * @IEEE80211_SMPS_AUTOMATIC: automatic
 * @IEEE80211_SMPS_OFF: off
 * @IEEE80211_SMPS_STATIC: static
 * @IEEE80211_SMPS_DYNAMIC: dynamic
 * @IEEE80211_SMPS_NUM_MODES: intewnaw, don't use
 */
enum ieee80211_smps_mode {
	IEEE80211_SMPS_AUTOMATIC,
	IEEE80211_SMPS_OFF,
	IEEE80211_SMPS_STATIC,
	IEEE80211_SMPS_DYNAMIC,

	/* keep wast */
	IEEE80211_SMPS_NUM_MODES,
};

/**
 * stwuct ieee80211_conf - configuwation of the device
 *
 * This stwuct indicates how the dwivew shaww configuwe the hawdwawe.
 *
 * @fwags: configuwation fwags defined above
 *
 * @wisten_intewvaw: wisten intewvaw in units of beacon intewvaw
 * @ps_dtim_pewiod: The DTIM pewiod of the AP we'we connected to, fow use
 *	in powew saving. Powew saving wiww not be enabwed untiw a beacon
 *	has been weceived and the DTIM pewiod is known.
 * @dynamic_ps_timeout: The dynamic powewsave timeout (in ms), see the
 *	powewsave documentation bewow. This vawiabwe is vawid onwy when
 *	the CONF_PS fwag is set.
 *
 * @powew_wevew: wequested twansmit powew (in dBm), backwawd compatibiwity
 *	vawue onwy that is set to the minimum of aww intewfaces
 *
 * @chandef: the channew definition to tune to
 * @wadaw_enabwed: whethew wadaw detection is enabwed
 *
 * @wong_fwame_max_tx_count: Maximum numbew of twansmissions fow a "wong" fwame
 *	(a fwame not WTS pwotected), cawwed "dot11WongWetwyWimit" in 802.11,
 *	but actuawwy means the numbew of twansmissions not the numbew of wetwies
 * @showt_fwame_max_tx_count: Maximum numbew of twansmissions fow a "showt"
 *	fwame, cawwed "dot11ShowtWetwyWimit" in 802.11, but actuawwy means the
 *	numbew of twansmissions not the numbew of wetwies
 *
 * @smps_mode: spatiaw muwtipwexing powewsave mode; note that
 *	%IEEE80211_SMPS_STATIC is used when the device is not
 *	configuwed fow an HT channew.
 *	Note that this is onwy vawid if channew contexts awe not used,
 *	othewwise each channew context has the numbew of chains wisted.
 */
stwuct ieee80211_conf {
	u32 fwags;
	int powew_wevew, dynamic_ps_timeout;

	u16 wisten_intewvaw;
	u8 ps_dtim_pewiod;

	u8 wong_fwame_max_tx_count, showt_fwame_max_tx_count;

	stwuct cfg80211_chan_def chandef;
	boow wadaw_enabwed;
	enum ieee80211_smps_mode smps_mode;
};

/**
 * stwuct ieee80211_channew_switch - howds the channew switch data
 *
 * The infowmation pwovided in this stwuctuwe is wequiwed fow channew switch
 * opewation.
 *
 * @timestamp: vawue in micwoseconds of the 64-bit Time Synchwonization
 *	Function (TSF) timew when the fwame containing the channew switch
 *	announcement was weceived. This is simpwy the wx.mactime pawametew
 *	the dwivew passed into mac80211.
 * @device_timestamp: awbitwawy timestamp fow the device, this is the
 *	wx.device_timestamp pawametew the dwivew passed to mac80211.
 * @bwock_tx: Indicates whethew twansmission must be bwocked befowe the
 *	scheduwed channew switch, as indicated by the AP.
 * @chandef: the new channew to switch to
 * @count: the numbew of TBTT's untiw the channew switch event
 * @deway: maximum deway between the time the AP twansmitted the wast beacon in
  *	cuwwent channew and the expected time of the fiwst beacon in the new
  *	channew, expwessed in TU.
 */
stwuct ieee80211_channew_switch {
	u64 timestamp;
	u32 device_timestamp;
	boow bwock_tx;
	stwuct cfg80211_chan_def chandef;
	u8 count;
	u32 deway;
};

/**
 * enum ieee80211_vif_fwags - viwtuaw intewface fwags
 *
 * @IEEE80211_VIF_BEACON_FIWTEW: the device pewfowms beacon fiwtewing
 *	on this viwtuaw intewface to avoid unnecessawy CPU wakeups
 * @IEEE80211_VIF_SUPPOWTS_CQM_WSSI: the device can do connection quawity
 *	monitowing on this viwtuaw intewface -- i.e. it can monitow
 *	connection quawity wewated pawametews, such as the WSSI wevew and
 *	pwovide notifications if configuwed twiggew wevews awe weached.
 * @IEEE80211_VIF_SUPPOWTS_UAPSD: The device can do U-APSD fow this
 *	intewface. This fwag shouwd be set duwing intewface addition,
 *	but may be set/cweawed as wate as authentication to an AP. It is
 *	onwy vawid fow managed/station mode intewfaces.
 * @IEEE80211_VIF_GET_NOA_UPDATE: wequest to handwe NOA attwibutes
 *	and send P2P_PS notification to the dwivew if NOA changed, even
 *	this is not puwe P2P vif.
 * @IEEE80211_VIF_EMW_ACTIVE: The dwivew indicates that EMW opewation is
 *      enabwed fow the intewface.
 */
enum ieee80211_vif_fwags {
	IEEE80211_VIF_BEACON_FIWTEW		= BIT(0),
	IEEE80211_VIF_SUPPOWTS_CQM_WSSI		= BIT(1),
	IEEE80211_VIF_SUPPOWTS_UAPSD		= BIT(2),
	IEEE80211_VIF_GET_NOA_UPDATE		= BIT(3),
	IEEE80211_VIF_EMW_ACTIVE	        = BIT(4),
};


/**
 * enum ieee80211_offwoad_fwags - viwtuaw intewface offwoad fwags
 *
 * @IEEE80211_OFFWOAD_ENCAP_ENABWED: tx encapsuwation offwoad is enabwed
 *	The dwivew suppowts sending fwames passed as 802.3 fwames by mac80211.
 *	It must awso suppowt sending 802.11 packets fow the same intewface.
 * @IEEE80211_OFFWOAD_ENCAP_4ADDW: suppowt 4-addwess mode encapsuwation offwoad
 * @IEEE80211_OFFWOAD_DECAP_ENABWED: wx encapsuwation offwoad is enabwed
 *	The dwivew suppowts passing weceived 802.11 fwames as 802.3 fwames to
 *	mac80211.
 */

enum ieee80211_offwoad_fwags {
	IEEE80211_OFFWOAD_ENCAP_ENABWED		= BIT(0),
	IEEE80211_OFFWOAD_ENCAP_4ADDW		= BIT(1),
	IEEE80211_OFFWOAD_DECAP_ENABWED		= BIT(2),
};

/**
 * stwuct ieee80211_vif_cfg - intewface configuwation
 * @assoc: association status
 * @ibss_joined: indicates whethew this station is pawt of an IBSS ow not
 * @ibss_cweatow: indicates if a new IBSS netwowk is being cweated
 * @ps: powew-save mode (STA onwy). This fwag is NOT affected by
 *	offchannew/dynamic_ps opewations.
 * @aid: association ID numbew, vawid onwy when @assoc is twue
 * @emw_cap: EMW capabiwities as descwibed in P802.11be_D2.2 Figuwe 9-1002k.
 * @emw_med_sync_deway: Medium Synchwonization deway as descwibed in
 *	P802.11be_D2.2 Figuwe 9-1002j.
 * @awp_addw_wist: Wist of IPv4 addwesses fow hawdwawe AWP fiwtewing. The
 *	may fiwtew AWP quewies tawgeted fow othew addwesses than wisted hewe.
 *	The dwivew must awwow AWP quewies tawgeted fow aww addwess wisted hewe
 *	to pass thwough. An empty wist impwies no AWP quewies need to pass.
 * @awp_addw_cnt: Numbew of addwesses cuwwentwy on the wist. Note that this
 *	may be wawgew than %IEEE80211_BSS_AWP_ADDW_WIST_WEN (the awp_addw_wist
 *	awway size), it's up to the dwivew what to do in that case.
 * @ssid: The SSID of the cuwwent vif. Vawid in AP and IBSS mode.
 * @ssid_wen: Wength of SSID given in @ssid.
 * @s1g: BSS is S1G BSS (affects Association Wequest fowmat).
 * @idwe: This intewface is idwe. Thewe's awso a gwobaw idwe fwag in the
 *	hawdwawe config which may be mowe appwopwiate depending on what
 *	youw dwivew/device needs to do.
 * @ap_addw: AP MWD addwess, ow BSSID fow non-MWO connections
 *	(station mode onwy)
 */
stwuct ieee80211_vif_cfg {
	/* association wewated data */
	boow assoc, ibss_joined;
	boow ibss_cweatow;
	boow ps;
	u16 aid;
	u16 emw_cap;
	u16 emw_med_sync_deway;

	__be32 awp_addw_wist[IEEE80211_BSS_AWP_ADDW_WIST_WEN];
	int awp_addw_cnt;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	size_t ssid_wen;
	boow s1g;
	boow idwe;
	u8 ap_addw[ETH_AWEN] __awigned(2);
};

/**
 * stwuct ieee80211_vif - pew-intewface data
 *
 * Data in this stwuctuwe is continuawwy pwesent fow dwivew
 * use duwing the wife of a viwtuaw intewface.
 *
 * @type: type of this viwtuaw intewface
 * @cfg: vif configuwation, see &stwuct ieee80211_vif_cfg
 * @bss_conf: BSS configuwation fow this intewface, eithew ouw own
 *	ow the BSS we'we associated to
 * @wink_conf: in case of MWD, the pew-wink BSS configuwation,
 *	indexed by wink ID
 * @vawid_winks: bitmap of vawid winks, ow 0 fow non-MWO.
 * @active_winks: The bitmap of active winks, ow 0 fow non-MWO.
 *	The dwivew shouwdn't change this diwectwy, but use the
 *	API cawws meant fow that puwpose.
 * @dowmant_winks: bitmap of vawid but disabwed winks, ow 0 fow non-MWO.
 *	Must be a subset of vawid_winks.
 * @addw: addwess of this intewface
 * @p2p: indicates whethew this AP ow STA intewface is a p2p
 *	intewface, i.e. a GO ow p2p-sta wespectivewy
 * @netdev_featuwes: tx netdev featuwes suppowted by the hawdwawe fow this
 *	vif. mac80211 initiawizes this to hw->netdev_featuwes, and the dwivew
 *	can mask out specific tx featuwes. mac80211 wiww handwe softwawe fixup
 *	fow masked offwoads (GSO, CSUM)
 * @dwivew_fwags: fwags/capabiwities the dwivew has fow this intewface,
 *	these need to be set (ow cweawed) when the intewface is added
 *	ow, if suppowted by the dwivew, the intewface type is changed
 *	at wuntime, mac80211 wiww nevew touch this fiewd
 * @offwoad_fwags: hawdwawe offwoad capabiwities/fwags fow this intewface.
 *	These awe initiawized by mac80211 befowe cawwing .add_intewface,
 *	.change_intewface ow .update_vif_offwoad and updated by the dwivew
 *	within these ops, based on suppowted featuwes ow wuntime change
 *	westwictions.
 * @hw_queue: hawdwawe queue fow each AC
 * @cab_queue: content-aftew-beacon (DTIM beacon weawwy) queue, AP mode onwy
 * @debugfs_diw: debugfs dentwy, can be used by dwivews to cweate own pew
 *	intewface debug fiwes. Note that it wiww be NUWW fow the viwtuaw
 *	monitow intewface (if that is wequested.)
 * @pwobe_weq_weg: pwobe wequests shouwd be wepowted to mac80211 fow this
 *	intewface.
 * @wx_mcast_action_weg: muwticast Action fwames shouwd be wepowted to mac80211
 *	fow this intewface.
 * @dwv_pwiv: data awea fow dwivew use, wiww awways be awigned to
 *	sizeof(void \*).
 * @txq: the muwticast data TX queue
 * @offwoad_fwags: 802.3 -> 802.11 enapsuwation offwoad fwags, see
 *	&enum ieee80211_offwoad_fwags.
 * @mbssid_tx_vif: Pointew to the twansmitting intewface if MBSSID is enabwed.
 */
stwuct ieee80211_vif {
	enum nw80211_iftype type;
	stwuct ieee80211_vif_cfg cfg;
	stwuct ieee80211_bss_conf bss_conf;
	stwuct ieee80211_bss_conf __wcu *wink_conf[IEEE80211_MWD_MAX_NUM_WINKS];
	u16 vawid_winks, active_winks, dowmant_winks;
	u8 addw[ETH_AWEN] __awigned(2);
	boow p2p;

	u8 cab_queue;
	u8 hw_queue[IEEE80211_NUM_ACS];

	stwuct ieee80211_txq *txq;

	netdev_featuwes_t netdev_featuwes;
	u32 dwivew_fwags;
	u32 offwoad_fwags;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct dentwy *debugfs_diw;
#endif

	boow pwobe_weq_weg;
	boow wx_mcast_action_weg;

	stwuct ieee80211_vif *mbssid_tx_vif;

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

/**
 * ieee80211_vif_usabwe_winks - Wetuwn the usabwe winks fow the vif
 * @vif: the vif fow which the usabwe winks awe wequested
 * Wetuwn: the usabwe wink bitmap
 */
static inwine u16 ieee80211_vif_usabwe_winks(const stwuct ieee80211_vif *vif)
{
	wetuwn vif->vawid_winks & ~vif->dowmant_winks;
}

/**
 * ieee80211_vif_is_mwd - Wetuwns twue iff the vif is an MWD one
 * @vif: the vif
 * Wetuwn: %twue if the vif is an MWD, %fawse othewwise.
 */
static inwine boow ieee80211_vif_is_mwd(const stwuct ieee80211_vif *vif)
{
	/* vawid_winks != 0 indicates this vif is an MWD */
	wetuwn vif->vawid_winks != 0;
}

#define fow_each_vif_active_wink(vif, wink, wink_id)				\
	fow (wink_id = 0; wink_id < AWWAY_SIZE((vif)->wink_conf); wink_id++)	\
		if ((!(vif)->active_winks ||					\
		     (vif)->active_winks & BIT(wink_id)) &&			\
		    (wink = wink_conf_dewefewence_check(vif, wink_id)))

static inwine boow ieee80211_vif_is_mesh(stwuct ieee80211_vif *vif)
{
#ifdef CONFIG_MAC80211_MESH
	wetuwn vif->type == NW80211_IFTYPE_MESH_POINT;
#endif
	wetuwn fawse;
}

/**
 * wdev_to_ieee80211_vif - wetuwn a vif stwuct fwom a wdev
 * @wdev: the wdev to get the vif fow
 *
 * This can be used by mac80211 dwivews with diwect cfg80211 APIs
 * (wike the vendow commands) that get a wdev.
 *
 * Note that this function may wetuwn %NUWW if the given wdev isn't
 * associated with a vif that the dwivew knows about (e.g. monitow
 * ow AP_VWAN intewfaces.)
 */
stwuct ieee80211_vif *wdev_to_ieee80211_vif(stwuct wiwewess_dev *wdev);

/**
 * ieee80211_vif_to_wdev - wetuwn a wdev stwuct fwom a vif
 * @vif: the vif to get the wdev fow
 *
 * This can be used by mac80211 dwivews with diwect cfg80211 APIs
 * (wike the vendow commands) that needs to get the wdev fow a vif.
 * This can awso be usefuw to get the netdev associated to a vif.
 */
stwuct wiwewess_dev *ieee80211_vif_to_wdev(stwuct ieee80211_vif *vif);

static inwine boow wockdep_vif_wiphy_mutex_hewd(stwuct ieee80211_vif *vif)
{
	wetuwn wockdep_is_hewd(&ieee80211_vif_to_wdev(vif)->wiphy->mtx);
}

#define wink_conf_dewefewence_pwotected(vif, wink_id)		\
	wcu_dewefewence_pwotected((vif)->wink_conf[wink_id],	\
				  wockdep_vif_wiphy_mutex_hewd(vif))

#define wink_conf_dewefewence_check(vif, wink_id)		\
	wcu_dewefewence_check((vif)->wink_conf[wink_id],	\
			      wockdep_vif_wiphy_mutex_hewd(vif))

/**
 * enum ieee80211_key_fwags - key fwags
 *
 * These fwags awe used fow communication about keys between the dwivew
 * and mac80211, with the @fwags pawametew of &stwuct ieee80211_key_conf.
 *
 * @IEEE80211_KEY_FWAG_GENEWATE_IV: This fwag shouwd be set by the
 *	dwivew to indicate that it wequiwes IV genewation fow this
 *	pawticuwaw key. Setting this fwag does not necessawiwy mean that SKBs
 *	wiww have sufficient taiwwoom fow ICV ow MIC.
 * @IEEE80211_KEY_FWAG_GENEWATE_MMIC: This fwag shouwd be set by
 *	the dwivew fow a TKIP key if it wequiwes Michaew MIC
 *	genewation in softwawe.
 * @IEEE80211_KEY_FWAG_PAIWWISE: Set by mac80211, this fwag indicates
 *	that the key is paiwwise wathew then a shawed key.
 * @IEEE80211_KEY_FWAG_SW_MGMT_TX: This fwag shouwd be set by the dwivew fow a
 *	CCMP/GCMP key if it wequiwes CCMP/GCMP encwyption of management fwames
 *	(MFP) to be done in softwawe.
 * @IEEE80211_KEY_FWAG_PUT_IV_SPACE: This fwag shouwd be set by the dwivew
 *	if space shouwd be pwepawed fow the IV, but the IV
 *	itsewf shouwd not be genewated. Do not set togethew with
 *	@IEEE80211_KEY_FWAG_GENEWATE_IV on the same key. Setting this fwag does
 *	not necessawiwy mean that SKBs wiww have sufficient taiwwoom fow ICV ow
 *	MIC.
 * @IEEE80211_KEY_FWAG_WX_MGMT: This key wiww be used to decwypt weceived
 *	management fwames. The fwag can hewp dwivews that have a hawdwawe
 *	cwypto impwementation that doesn't deaw with management fwames
 *	pwopewwy by awwowing them to not upwoad the keys to hawdwawe and
 *	faww back to softwawe cwypto. Note that this fwag deaws onwy with
 *	WX, if youw cwypto engine can't deaw with TX you can awso set the
 *	%IEEE80211_KEY_FWAG_SW_MGMT_TX fwag to encwypt such fwames in SW.
 * @IEEE80211_KEY_FWAG_GENEWATE_IV_MGMT: This fwag shouwd be set by the
 *	dwivew fow a CCMP/GCMP key to indicate that is wequiwes IV genewation
 *	onwy fow management fwames (MFP).
 * @IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM: This fwag shouwd be set by the
 *	dwivew fow a key to indicate that sufficient taiwwoom must awways
 *	be wesewved fow ICV ow MIC, even when HW encwyption is enabwed.
 * @IEEE80211_KEY_FWAG_PUT_MIC_SPACE: This fwag shouwd be set by the dwivew fow
 *	a TKIP key if it onwy wequiwes MIC space. Do not set togethew with
 *	@IEEE80211_KEY_FWAG_GENEWATE_MMIC on the same key.
 * @IEEE80211_KEY_FWAG_NO_AUTO_TX: Key needs expwicit Tx activation.
 * @IEEE80211_KEY_FWAG_GENEWATE_MMIE: This fwag shouwd be set by the dwivew
 *	fow a AES_CMAC key to indicate that it wequiwes sequence numbew
 *	genewation onwy
 */
enum ieee80211_key_fwags {
	IEEE80211_KEY_FWAG_GENEWATE_IV_MGMT	= BIT(0),
	IEEE80211_KEY_FWAG_GENEWATE_IV		= BIT(1),
	IEEE80211_KEY_FWAG_GENEWATE_MMIC	= BIT(2),
	IEEE80211_KEY_FWAG_PAIWWISE		= BIT(3),
	IEEE80211_KEY_FWAG_SW_MGMT_TX		= BIT(4),
	IEEE80211_KEY_FWAG_PUT_IV_SPACE		= BIT(5),
	IEEE80211_KEY_FWAG_WX_MGMT		= BIT(6),
	IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM	= BIT(7),
	IEEE80211_KEY_FWAG_PUT_MIC_SPACE	= BIT(8),
	IEEE80211_KEY_FWAG_NO_AUTO_TX		= BIT(9),
	IEEE80211_KEY_FWAG_GENEWATE_MMIE	= BIT(10),
};

/**
 * stwuct ieee80211_key_conf - key infowmation
 *
 * This key infowmation is given by mac80211 to the dwivew by
 * the set_key() cawwback in &stwuct ieee80211_ops.
 *
 * @hw_key_idx: To be set by the dwivew, this is the key index the dwivew
 *	wants to be given when a fwame is twansmitted and needs to be
 *	encwypted in hawdwawe.
 * @ciphew: The key's ciphew suite sewectow.
 * @tx_pn: PN used fow TX keys, may be used by the dwivew as weww if it
 *	needs to do softwawe PN assignment by itsewf (e.g. due to TSO)
 * @fwags: key fwags, see &enum ieee80211_key_fwags.
 * @keyidx: the key index (0-3)
 * @keywen: key matewiaw wength
 * @key: key matewiaw. Fow AWG_TKIP the key is encoded as a 256-bit (32 byte)
 * 	data bwock:
 * 	- Tempowaw Encwyption Key (128 bits)
 * 	- Tempowaw Authenticatow Tx MIC Key (64 bits)
 * 	- Tempowaw Authenticatow Wx MIC Key (64 bits)
 * @icv_wen: The ICV wength fow this key type
 * @iv_wen: The IV wength fow this key type
 * @wink_id: the wink ID fow MWO, ow -1 fow non-MWO ow paiwwise keys
 */
stwuct ieee80211_key_conf {
	atomic64_t tx_pn;
	u32 ciphew;
	u8 icv_wen;
	u8 iv_wen;
	u8 hw_key_idx;
	s8 keyidx;
	u16 fwags;
	s8 wink_id;
	u8 keywen;
	u8 key[];
};

#define IEEE80211_MAX_PN_WEN	16

#define TKIP_PN_TO_IV16(pn) ((u16)(pn & 0xffff))
#define TKIP_PN_TO_IV32(pn) ((u32)((pn >> 16) & 0xffffffff))

/**
 * stwuct ieee80211_key_seq - key sequence countew
 *
 * @tkip: TKIP data, containing IV32 and IV16 in host byte owdew
 * @ccmp: PN data, most significant byte fiwst (big endian,
 *	wevewse owdew than in packet)
 * @aes_cmac: PN data, most significant byte fiwst (big endian,
 *	wevewse owdew than in packet)
 * @aes_gmac: PN data, most significant byte fiwst (big endian,
 *	wevewse owdew than in packet)
 * @gcmp: PN data, most significant byte fiwst (big endian,
 *	wevewse owdew than in packet)
 * @hw: data fow HW-onwy (e.g. ciphew scheme) keys
 */
stwuct ieee80211_key_seq {
	union {
		stwuct {
			u32 iv32;
			u16 iv16;
		} tkip;
		stwuct {
			u8 pn[6];
		} ccmp;
		stwuct {
			u8 pn[6];
		} aes_cmac;
		stwuct {
			u8 pn[6];
		} aes_gmac;
		stwuct {
			u8 pn[6];
		} gcmp;
		stwuct {
			u8 seq[IEEE80211_MAX_PN_WEN];
			u8 seq_wen;
		} hw;
	};
};

/**
 * enum set_key_cmd - key command
 *
 * Used with the set_key() cawwback in &stwuct ieee80211_ops, this
 * indicates whethew a key is being wemoved ow added.
 *
 * @SET_KEY: a key is set
 * @DISABWE_KEY: a key must be disabwed
 */
enum set_key_cmd {
	SET_KEY, DISABWE_KEY,
};

/**
 * enum ieee80211_sta_state - station state
 *
 * @IEEE80211_STA_NOTEXIST: station doesn't exist at aww,
 *	this is a speciaw state fow add/wemove twansitions
 * @IEEE80211_STA_NONE: station exists without speciaw state
 * @IEEE80211_STA_AUTH: station is authenticated
 * @IEEE80211_STA_ASSOC: station is associated
 * @IEEE80211_STA_AUTHOWIZED: station is authowized (802.1X)
 */
enum ieee80211_sta_state {
	/* NOTE: These need to be owdewed cowwectwy! */
	IEEE80211_STA_NOTEXIST,
	IEEE80211_STA_NONE,
	IEEE80211_STA_AUTH,
	IEEE80211_STA_ASSOC,
	IEEE80211_STA_AUTHOWIZED,
};

/**
 * enum ieee80211_sta_wx_bandwidth - station WX bandwidth
 * @IEEE80211_STA_WX_BW_20: station can onwy weceive 20 MHz
 * @IEEE80211_STA_WX_BW_40: station can weceive up to 40 MHz
 * @IEEE80211_STA_WX_BW_80: station can weceive up to 80 MHz
 * @IEEE80211_STA_WX_BW_160: station can weceive up to 160 MHz
 *	(incwuding 80+80 MHz)
 * @IEEE80211_STA_WX_BW_320: station can weceive up to 320 MHz
 *
 * Impwementation note: 20 must be zewo to be initiawized
 *	cowwectwy, the vawues must be sowted.
 */
enum ieee80211_sta_wx_bandwidth {
	IEEE80211_STA_WX_BW_20 = 0,
	IEEE80211_STA_WX_BW_40,
	IEEE80211_STA_WX_BW_80,
	IEEE80211_STA_WX_BW_160,
	IEEE80211_STA_WX_BW_320,
};

/**
 * stwuct ieee80211_sta_wates - station wate sewection tabwe
 *
 * @wcu_head: WCU head used fow fweeing the tabwe on update
 * @wate: twansmit wates/fwags to be used by defauwt.
 *	Ovewwiding entwies pew-packet is possibwe by using cb tx contwow.
 */
stwuct ieee80211_sta_wates {
	stwuct wcu_head wcu_head;
	stwuct {
		s8 idx;
		u8 count;
		u8 count_cts;
		u8 count_wts;
		u16 fwags;
	} wate[IEEE80211_TX_WATE_TABWE_SIZE];
};

/**
 * stwuct ieee80211_sta_txpww - station txpowew configuwation
 *
 * Used to configuwe txpowew fow station.
 *
 * @powew: indicates the tx powew, in dBm, to be used when sending data fwames
 *	to the STA.
 * @type: In pawticuwaw if TPC %type is NW80211_TX_POWEW_WIMITED then tx powew
 *	wiww be wess than ow equaw to specified fwom usewspace, wheweas if TPC
 *	%type is NW80211_TX_POWEW_AUTOMATIC then it indicates defauwt tx powew.
 *	NW80211_TX_POWEW_FIXED is not a vawid configuwation option fow
 *	pew peew TPC.
 */
stwuct ieee80211_sta_txpww {
	s16 powew;
	enum nw80211_tx_powew_setting type;
};

/**
 * stwuct ieee80211_sta_aggwegates - info that is aggwegated fwom active winks
 *
 * Used fow any pew-wink data that needs to be aggwegated and updated in the
 * main &stwuct ieee80211_sta when updated ow the active winks change.
 *
 * @max_amsdu_wen: indicates the maximaw wength of an A-MSDU in bytes.
 *	This fiewd is awways vawid fow packets with a VHT pweambwe.
 *	Fow packets with a HT pweambwe, additionaw wimits appwy:
 *
 *	* If the skb is twansmitted as pawt of a BA agweement, the
 *	  A-MSDU maximaw size is min(max_amsdu_wen, 4065) bytes.
 *	* If the skb is not pawt of a BA agweement, the A-MSDU maximaw
 *	  size is min(max_amsdu_wen, 7935) bytes.
 *
 * Both additionaw HT wimits must be enfowced by the wow wevew
 * dwivew. This is defined by the spec (IEEE 802.11-2012 section
 * 8.3.2.2 NOTE 2).
 * @max_wc_amsdu_wen: Maximum A-MSDU size in bytes wecommended by wate contwow.
 * @max_tid_amsdu_wen: Maximum A-MSDU size in bytes fow this TID
 */
stwuct ieee80211_sta_aggwegates {
	u16 max_amsdu_wen;

	u16 max_wc_amsdu_wen;
	u16 max_tid_amsdu_wen[IEEE80211_NUM_TIDS];
};

/**
 * stwuct ieee80211_wink_sta - station Wink specific info
 * Aww wink specific info fow a STA wink fow a non MWD STA(singwe)
 * ow a MWD STA(muwtipwe entwies) awe stowed hewe.
 *
 * @sta: wefewence to owning STA
 * @addw: MAC addwess of the Wink STA. Fow non-MWO STA this is same as the addw
 *	in ieee80211_sta. Fow MWO Wink STA this addw can be same ow diffewent
 *	fwom addw in ieee80211_sta (wepwesenting MWD STA addw)
 * @wink_id: the wink ID fow this wink STA (0 fow defwink)
 * @smps_mode: cuwwent SMPS mode (off, static ow dynamic)
 * @supp_wates: Bitmap of suppowted wates
 * @ht_cap: HT capabiwities of this STA; westwicted to ouw own capabiwities
 * @vht_cap: VHT capabiwities of this STA; westwicted to ouw own capabiwities
 * @he_cap: HE capabiwities of this STA
 * @he_6ghz_capa: on 6 GHz, howds the HE 6 GHz band capabiwities
 * @eht_cap: EHT capabiwities of this STA
 * @agg: pew-wink data fow muwti-wink aggwegation
 * @bandwidth: cuwwent bandwidth the station can weceive with
 * @wx_nss: in HT/VHT, the maximum numbew of spatiaw stweams the
 *	station can weceive at the moment, changed by opewating mode
 *	notifications and capabiwities. The vawue is onwy vawid aftew
 *	the station moves to associated state.
 * @txpww: the station tx powew configuwation
 *
 */
stwuct ieee80211_wink_sta {
	stwuct ieee80211_sta *sta;

	u8 addw[ETH_AWEN];
	u8 wink_id;
	enum ieee80211_smps_mode smps_mode;

	u32 supp_wates[NUM_NW80211_BANDS];
	stwuct ieee80211_sta_ht_cap ht_cap;
	stwuct ieee80211_sta_vht_cap vht_cap;
	stwuct ieee80211_sta_he_cap he_cap;
	stwuct ieee80211_he_6ghz_capa he_6ghz_capa;
	stwuct ieee80211_sta_eht_cap eht_cap;

	stwuct ieee80211_sta_aggwegates agg;

	u8 wx_nss;
	enum ieee80211_sta_wx_bandwidth bandwidth;
	stwuct ieee80211_sta_txpww txpww;
};

/**
 * stwuct ieee80211_sta - station tabwe entwy
 *
 * A station tabwe entwy wepwesents a station we awe possibwy
 * communicating with. Since stations awe WCU-managed in
 * mac80211, any ieee80211_sta pointew you get access to must
 * eithew be pwotected by wcu_wead_wock() expwicitwy ow impwicitwy,
 * ow you must take good cawe to not use such a pointew aftew a
 * caww to youw sta_wemove cawwback that wemoved it.
 * This awso wepwesents the MWD STA in case of MWO association
 * and howds pointews to vawious wink STA's
 *
 * @addw: MAC addwess
 * @aid: AID we assigned to the station if we'we an AP
 * @max_wx_aggwegation_subfwames: maximaw amount of fwames in a singwe AMPDU
 *	that this station is awwowed to twansmit to us.
 *	Can be modified by dwivew.
 * @wme: indicates whethew the STA suppowts QoS/WME (if wocaw devices does,
 *	othewwise awways fawse)
 * @dwv_pwiv: data awea fow dwivew use, wiww awways be awigned to
 *	sizeof(void \*), size is detewmined in hw infowmation.
 * @uapsd_queues: bitmap of queues configuwed fow uapsd. Onwy vawid
 *	if wme is suppowted. The bits owdew is wike in
 *	IEEE80211_WMM_IE_STA_QOSINFO_AC_*.
 * @max_sp: max Sewvice Pewiod. Onwy vawid if wme is suppowted.
 * @wates: wate contwow sewection tabwe
 * @tdws: indicates whethew the STA is a TDWS peew
 * @tdws_initiatow: indicates the STA is an initiatow of the TDWS wink. Onwy
 *	vawid if the STA is a TDWS peew in the fiwst pwace.
 * @mfp: indicates whethew the STA uses management fwame pwotection ow not.
 * @mwo: indicates whethew the STA is MWO station.
 * @max_amsdu_subfwames: indicates the maximaw numbew of MSDUs in a singwe
 *	A-MSDU. Taken fwom the Extended Capabiwities ewement. 0 means
 *	unwimited.
 * @cuw: cuwwentwy vawid data as aggwegated fwom the active winks
 *	Fow non MWO STA it wiww point to the defwink data. Fow MWO STA
 *	ieee80211_sta_wecawc_aggwegates() must be cawwed to update it.
 * @suppowt_p2p_ps: indicates whethew the STA suppowts P2P PS mechanism ow not.
 * @txq: pew-TID data TX queues; note that the wast entwy (%IEEE80211_NUM_TIDS)
 *	is used fow non-data fwames
 * @defwink: This howds the defauwt wink STA infowmation, fow non MWO STA aww wink
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
 * @vawid_winks: bitmap of vawid winks, ow 0 fow non-MWO
 */
stwuct ieee80211_sta {
	u8 addw[ETH_AWEN];
	u16 aid;
	u16 max_wx_aggwegation_subfwames;
	boow wme;
	u8 uapsd_queues;
	u8 max_sp;
	stwuct ieee80211_sta_wates __wcu *wates;
	boow tdws;
	boow tdws_initiatow;
	boow mfp;
	boow mwo;
	u8 max_amsdu_subfwames;

	stwuct ieee80211_sta_aggwegates *cuw;

	boow suppowt_p2p_ps;

	stwuct ieee80211_txq *txq[IEEE80211_NUM_TIDS + 1];

	u16 vawid_winks;
	stwuct ieee80211_wink_sta defwink;
	stwuct ieee80211_wink_sta __wcu *wink[IEEE80211_MWD_MAX_NUM_WINKS];

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

#ifdef CONFIG_WOCKDEP
boow wockdep_sta_mutex_hewd(stwuct ieee80211_sta *pubsta);
#ewse
static inwine boow wockdep_sta_mutex_hewd(stwuct ieee80211_sta *pubsta)
{
	wetuwn twue;
}
#endif

#define wink_sta_dewefewence_pwotected(sta, wink_id)		\
	wcu_dewefewence_pwotected((sta)->wink[wink_id],		\
				  wockdep_sta_mutex_hewd(sta))

#define wink_sta_dewefewence_check(sta, wink_id)		\
	wcu_dewefewence_check((sta)->wink[wink_id],		\
			      wockdep_sta_mutex_hewd(sta))

#define fow_each_sta_active_wink(vif, sta, wink_sta, wink_id)			\
	fow (wink_id = 0; wink_id < AWWAY_SIZE((sta)->wink); wink_id++)		\
		if ((!(vif)->active_winks ||					\
		     (vif)->active_winks & BIT(wink_id)) &&			\
		    ((wink_sta) = wink_sta_dewefewence_check(sta, wink_id)))

/**
 * enum sta_notify_cmd - sta notify command
 *
 * Used with the sta_notify() cawwback in &stwuct ieee80211_ops, this
 * indicates if an associated station made a powew state twansition.
 *
 * @STA_NOTIFY_SWEEP: a station is now sweeping
 * @STA_NOTIFY_AWAKE: a sweeping station woke up
 */
enum sta_notify_cmd {
	STA_NOTIFY_SWEEP, STA_NOTIFY_AWAKE,
};

/**
 * stwuct ieee80211_tx_contwow - TX contwow data
 *
 * @sta: station tabwe entwy, this sta pointew may be NUWW and
 * 	it is not awwowed to copy the pointew, due to WCU.
 */
stwuct ieee80211_tx_contwow {
	stwuct ieee80211_sta *sta;
};

/**
 * stwuct ieee80211_txq - Softwawe intewmediate tx queue
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @sta: station tabwe entwy, %NUWW fow pew-vif queue
 * @tid: the TID fow this queue (unused fow pew-vif queue),
 *	%IEEE80211_NUM_TIDS fow non-data (if enabwed)
 * @ac: the AC fow this queue
 * @dwv_pwiv: dwivew pwivate awea, sized by hw->txq_data_size
 *
 * The dwivew can obtain packets fwom this queue by cawwing
 * ieee80211_tx_dequeue().
 */
stwuct ieee80211_txq {
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_sta *sta;
	u8 tid;
	u8 ac;

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

/**
 * enum ieee80211_hw_fwags - hawdwawe fwags
 *
 * These fwags awe used to indicate hawdwawe capabiwities to
 * the stack. Genewawwy, fwags hewe shouwd have theiw meaning
 * done in a way that the simpwest hawdwawe doesn't need setting
 * any pawticuwaw fwags. Thewe awe some exceptions to this wuwe,
 * howevew, so you awe advised to weview these fwags cawefuwwy.
 *
 * @IEEE80211_HW_HAS_WATE_CONTWOW:
 *	The hawdwawe ow fiwmwawe incwudes wate contwow, and cannot be
 *	contwowwed by the stack. As such, no wate contwow awgowithm
 *	shouwd be instantiated, and the TX wate wepowted to usewspace
 *	wiww be taken fwom the TX status instead of the wate contwow
 *	awgowithm.
 *	Note that this wequiwes that the dwivew impwement a numbew of
 *	cawwbacks so it has the cowwect infowmation, it needs to have
 *	the @set_wts_thweshowd cawwback and must wook at the BSS config
 *	@use_cts_pwot fow G/N pwotection, @use_showt_swot fow swot
 *	timing in 2.4 GHz and @use_showt_pweambwe fow pweambwes fow
 *	CCK fwames.
 *
 * @IEEE80211_HW_WX_INCWUDES_FCS:
 *	Indicates that weceived fwames passed to the stack incwude
 *	the FCS at the end.
 *
 * @IEEE80211_HW_HOST_BWOADCAST_PS_BUFFEWING:
 *	Some wiwewess WAN chipsets buffew bwoadcast/muwticast fwames
 *	fow powew saving stations in the hawdwawe/fiwmwawe and othews
 *	wewy on the host system fow such buffewing. This option is used
 *	to configuwe the IEEE 802.11 uppew wayew to buffew bwoadcast and
 *	muwticast fwames when thewe awe powew saving stations so that
 *	the dwivew can fetch them with ieee80211_get_buffewed_bc().
 *
 * @IEEE80211_HW_SIGNAW_UNSPEC:
 *	Hawdwawe can pwovide signaw vawues but we don't know its units. We
 *	expect vawues between 0 and @max_signaw.
 *	If possibwe pwease pwovide dB ow dBm instead.
 *
 * @IEEE80211_HW_SIGNAW_DBM:
 *	Hawdwawe gives signaw vawues in dBm, decibew diffewence fwom
 *	one miwwiwatt. This is the pwefewwed method since it is standawdized
 *	between diffewent devices. @max_signaw does not need to be set.
 *
 * @IEEE80211_HW_SPECTWUM_MGMT:
 * 	Hawdwawe suppowts spectwum management defined in 802.11h
 * 	Measuwement, Channew Switch, Quieting, TPC
 *
 * @IEEE80211_HW_AMPDU_AGGWEGATION:
 *	Hawdwawe suppowts 11n A-MPDU aggwegation.
 *
 * @IEEE80211_HW_SUPPOWTS_PS:
 *	Hawdwawe has powew save suppowt (i.e. can go to sweep).
 *
 * @IEEE80211_HW_PS_NUWWFUNC_STACK:
 *	Hawdwawe wequiwes nuwwfunc fwame handwing in stack, impwies
 *	stack suppowt fow dynamic PS.
 *
 * @IEEE80211_HW_SUPPOWTS_DYNAMIC_PS:
 *	Hawdwawe has suppowt fow dynamic PS.
 *
 * @IEEE80211_HW_MFP_CAPABWE:
 *	Hawdwawe suppowts management fwame pwotection (MFP, IEEE 802.11w).
 *
 * @IEEE80211_HW_WEPOWTS_TX_ACK_STATUS:
 *	Hawdwawe can pwovide ack status wepowts of Tx fwames to
 *	the stack.
 *
 * @IEEE80211_HW_CONNECTION_MONITOW:
 *	The hawdwawe pewfowms its own connection monitowing, incwuding
 *	pewiodic keep-awives to the AP and pwobing the AP on beacon woss.
 *
 * @IEEE80211_HW_NEED_DTIM_BEFOWE_ASSOC:
 *	This device needs to get data fwom beacon befowe association (i.e.
 *	dtim_pewiod).
 *
 * @IEEE80211_HW_SUPPOWTS_PEW_STA_GTK: The device's cwypto engine suppowts
 *	pew-station GTKs as used by IBSS WSN ow duwing fast twansition. If
 *	the device doesn't suppowt pew-station GTKs, but can be asked not
 *	to decwypt gwoup addwessed fwames, then IBSS WSN suppowt is stiww
 *	possibwe but softwawe cwypto wiww be used. Advewtise the wiphy fwag
 *	onwy in that case.
 *
 * @IEEE80211_HW_AP_WINK_PS: When opewating in AP mode the device
 *	autonomouswy manages the PS status of connected stations. When
 *	this fwag is set mac80211 wiww not twiggew PS mode fow connected
 *	stations based on the PM bit of incoming fwames.
 *	Use ieee80211_stawt_ps()/ieee8021_end_ps() to manuawwy configuwe
 *	the PS mode of connected stations.
 *
 * @IEEE80211_HW_TX_AMPDU_SETUP_IN_HW: The device handwes TX A-MPDU session
 *	setup stwictwy in HW. mac80211 shouwd not attempt to do this in
 *	softwawe.
 *
 * @IEEE80211_HW_WANT_MONITOW_VIF: The dwivew wouwd wike to be infowmed of
 *	a viwtuaw monitow intewface when monitow intewfaces awe the onwy
 *	active intewfaces.
 *
 * @IEEE80211_HW_NO_AUTO_VIF: The dwivew wouwd wike fow no wwanX to
 *	be cweated.  It is expected usew-space wiww cweate vifs as
 *	desiwed (and thus have them named as desiwed).
 *
 * @IEEE80211_HW_SW_CWYPTO_CONTWOW: The dwivew wants to contwow which of the
 *	cwypto awgowithms can be done in softwawe - so don't automaticawwy
 *	twy to faww back to it if hawdwawe cwypto faiws, but do so onwy if
 *	the dwivew wetuwns 1. This awso fowces the dwivew to advewtise its
 *	suppowted ciphew suites.
 *
 * @IEEE80211_HW_SUPPOWT_FAST_XMIT: The dwivew/hawdwawe suppowts fast-xmit,
 *	this cuwwentwy wequiwes onwy the abiwity to cawcuwate the duwation
 *	fow fwames.
 *
 * @IEEE80211_HW_QUEUE_CONTWOW: The dwivew wants to contwow pew-intewface
 *	queue mapping in owdew to use diffewent queues (not just one pew AC)
 *	fow diffewent viwtuaw intewfaces. See the doc section on HW queue
 *	contwow fow mowe detaiws.
 *
 * @IEEE80211_HW_SUPPOWTS_WC_TABWE: The dwivew suppowts using a wate
 *	sewection tabwe pwovided by the wate contwow awgowithm.
 *
 * @IEEE80211_HW_P2P_DEV_ADDW_FOW_INTF: Use the P2P Device addwess fow any
 *	P2P Intewface. This wiww be honouwed even if mowe than one intewface
 *	is suppowted.
 *
 * @IEEE80211_HW_TIMING_BEACON_ONWY: Use sync timing fwom beacon fwames
 *	onwy, to awwow getting TBTT of a DTIM beacon.
 *
 * @IEEE80211_HW_SUPPOWTS_HT_CCK_WATES: Hawdwawe suppowts mixing HT/CCK wates
 *	and can cope with CCK wates in an aggwegation session (e.g. by not
 *	using aggwegation fow such fwames.)
 *
 * @IEEE80211_HW_CHANCTX_STA_CSA: Suppowt 802.11h based channew-switch (CSA)
 *	fow a singwe active channew whiwe using channew contexts. When suppowt
 *	is not enabwed the defauwt action is to disconnect when getting the
 *	CSA fwame.
 *
 * @IEEE80211_HW_SUPPOWTS_CWONED_SKBS: The dwivew wiww nevew modify the paywoad
 *	ow taiwwoom of TX skbs without copying them fiwst.
 *
 * @IEEE80211_HW_SINGWE_SCAN_ON_AWW_BANDS: The HW suppowts scanning on aww bands
 *	in one command, mac80211 doesn't have to wun sepawate scans pew band.
 *
 * @IEEE80211_HW_TDWS_WIDEW_BW: The device/dwivew suppowts widew bandwidth
 *	than then BSS bandwidth fow a TDWS wink on the base channew.
 *
 * @IEEE80211_HW_SUPPOWTS_AMSDU_IN_AMPDU: The dwivew suppowts weceiving A-MSDUs
 *	within A-MPDU.
 *
 * @IEEE80211_HW_BEACON_TX_STATUS: The device/dwivew pwovides TX status
 *	fow sent beacons.
 *
 * @IEEE80211_HW_NEEDS_UNIQUE_STA_ADDW: Hawdwawe (ow dwivew) wequiwes that each
 *	station has a unique addwess, i.e. each station entwy can be identified
 *	by just its MAC addwess; this pwevents, fow exampwe, the same station
 *	fwom connecting to two viwtuaw AP intewfaces at the same time.
 *
 * @IEEE80211_HW_SUPPOWTS_WEOWDEWING_BUFFEW: Hawdwawe (ow dwivew) manages the
 *	weowdewing buffew intewnawwy, guawanteeing mac80211 weceives fwames in
 *	owdew and does not need to manage its own weowdew buffew ow BA session
 *	timeout.
 *
 * @IEEE80211_HW_USES_WSS: The device uses WSS and thus wequiwes pawawwew WX,
 *	which impwies using pew-CPU station statistics.
 *
 * @IEEE80211_HW_TX_AMSDU: Hawdwawe (ow dwivew) suppowts softwawe aggwegated
 *	A-MSDU fwames. Wequiwes softwawe tx queueing and fast-xmit suppowt.
 *	When not using minstwew/minstwew_ht wate contwow, the dwivew must
 *	wimit the maximum A-MSDU size based on the cuwwent tx wate by setting
 *	max_wc_amsdu_wen in stwuct ieee80211_sta.
 *
 * @IEEE80211_HW_TX_FWAG_WIST: Hawdwawe (ow dwivew) suppowts sending fwag_wist
 *	skbs, needed fow zewo-copy softwawe A-MSDU.
 *
 * @IEEE80211_HW_WEPOWTS_WOW_ACK: The dwivew (ow fiwmwawe) wepowts wow ack event
 *	by ieee80211_wepowt_wow_ack() based on its own awgowithm. Fow such
 *	dwivews, mac80211 packet woss mechanism wiww not be twiggewed and dwivew
 *	is compwetewy depending on fiwmwawe event fow station kickout.
 *
 * @IEEE80211_HW_SUPPOWTS_TX_FWAG: Hawdwawe does fwagmentation by itsewf.
 *	The stack wiww not do fwagmentation.
 *	The cawwback fow @set_fwag_thweshowd shouwd be set as weww.
 *
 * @IEEE80211_HW_SUPPOWTS_TDWS_BUFFEW_STA: Hawdwawe suppowts buffew STA on
 *	TDWS winks.
 *
 * @IEEE80211_HW_DEAUTH_NEED_MGD_TX_PWEP: The dwivew wequiwes the
 *	mgd_pwepawe_tx() cawwback to be cawwed befowe twansmission of a
 *	deauthentication fwame in case the association was compweted but no
 *	beacon was heawd. This is wequiwed in muwti-channew scenawios, whewe the
 *	viwtuaw intewface might not be given aiw time fow the twansmission of
 *	the fwame, as it is not synced with the AP/P2P GO yet, and thus the
 *	deauthentication fwame might not be twansmitted.
 *
 * @IEEE80211_HW_DOESNT_SUPPOWT_QOS_NDP: The dwivew (ow fiwmwawe) doesn't
 *	suppowt QoS NDP fow AP pwobing - that's most wikewy a dwivew bug.
 *
 * @IEEE80211_HW_BUFF_MMPDU_TXQ: use the TXQ fow buffewabwe MMPDUs, this of
 *	couwse wequiwes the dwivew to use TXQs to stawt with.
 *
 * @IEEE80211_HW_SUPPOWTS_VHT_EXT_NSS_BW: (Hawdwawe) wate contwow suppowts VHT
 *	extended NSS BW (dot11VHTExtendedNSSBWCapabwe). This fwag wiww be set if
 *	the sewected wate contwow awgowithm sets %WATE_CTWW_CAPA_VHT_EXT_NSS_BW
 *	but if the wate contwow is buiwt-in then it must be set by the dwivew.
 *	See awso the documentation fow that fwag.
 *
 * @IEEE80211_HW_STA_MMPDU_TXQ: use the extwa non-TID pew-station TXQ fow aww
 *	MMPDUs on station intewfaces. This of couwse wequiwes the dwivew to use
 *	TXQs to stawt with.
 *
 * @IEEE80211_HW_TX_STATUS_NO_AMPDU_WEN: Dwivew does not wepowt accuwate A-MPDU
 *	wength in tx status infowmation
 *
 * @IEEE80211_HW_SUPPOWTS_MUWTI_BSSID: Hawdwawe suppowts muwti BSSID
 *
 * @IEEE80211_HW_SUPPOWTS_ONWY_HE_MUWTI_BSSID: Hawdwawe suppowts muwti BSSID
 *	onwy fow HE APs. Appwies if @IEEE80211_HW_SUPPOWTS_MUWTI_BSSID is set.
 *
 * @IEEE80211_HW_AMPDU_KEYBOWDEW_SUPPOWT: The cawd and dwivew is onwy
 *	aggwegating MPDUs with the same keyid, awwowing mac80211 to keep Tx
 *	A-MPDU sessions active whiwe wekeying with Extended Key ID.
 *
 * @IEEE80211_HW_SUPPOWTS_TX_ENCAP_OFFWOAD: Hawdwawe suppowts tx encapsuwation
 *	offwoad
 *
 * @IEEE80211_HW_SUPPOWTS_WX_DECAP_OFFWOAD: Hawdwawe suppowts wx decapsuwation
 *	offwoad
 *
 * @IEEE80211_HW_SUPPOWTS_CONC_MON_WX_DECAP: Hawdwawe suppowts concuwwent wx
 *	decapsuwation offwoad and passing waw 802.11 fwames fow monitow iface.
 *	If this is suppowted, the dwivew must pass both 802.3 fwames fow weaw
 *	usage and 802.11 fwames with %WX_FWAG_ONWY_MONITOW set fow monitow to
 *	the stack.
 *
 * @IEEE80211_HW_DETECTS_COWOW_COWWISION: HW/dwivew has suppowt fow BSS cowow
 *	cowwision detection and doesn't need it in softwawe.
 *
 * @IEEE80211_HW_MWO_MCAST_MUWTI_WINK_TX: Hawdwawe/dwivew handwes twansmitting
 *	muwticast fwames on aww winks, mac80211 shouwd not do that.
 *
 * @IEEE80211_HW_DISAWWOW_PUNCTUWING: HW wequiwes disabwing punctuwing in EHT
 *	and connecting with a wowew bandwidth instead
 *
 * @NUM_IEEE80211_HW_FWAGS: numbew of hawdwawe fwags, used fow sizing awways
 */
enum ieee80211_hw_fwags {
	IEEE80211_HW_HAS_WATE_CONTWOW,
	IEEE80211_HW_WX_INCWUDES_FCS,
	IEEE80211_HW_HOST_BWOADCAST_PS_BUFFEWING,
	IEEE80211_HW_SIGNAW_UNSPEC,
	IEEE80211_HW_SIGNAW_DBM,
	IEEE80211_HW_NEED_DTIM_BEFOWE_ASSOC,
	IEEE80211_HW_SPECTWUM_MGMT,
	IEEE80211_HW_AMPDU_AGGWEGATION,
	IEEE80211_HW_SUPPOWTS_PS,
	IEEE80211_HW_PS_NUWWFUNC_STACK,
	IEEE80211_HW_SUPPOWTS_DYNAMIC_PS,
	IEEE80211_HW_MFP_CAPABWE,
	IEEE80211_HW_WANT_MONITOW_VIF,
	IEEE80211_HW_NO_AUTO_VIF,
	IEEE80211_HW_SW_CWYPTO_CONTWOW,
	IEEE80211_HW_SUPPOWT_FAST_XMIT,
	IEEE80211_HW_WEPOWTS_TX_ACK_STATUS,
	IEEE80211_HW_CONNECTION_MONITOW,
	IEEE80211_HW_QUEUE_CONTWOW,
	IEEE80211_HW_SUPPOWTS_PEW_STA_GTK,
	IEEE80211_HW_AP_WINK_PS,
	IEEE80211_HW_TX_AMPDU_SETUP_IN_HW,
	IEEE80211_HW_SUPPOWTS_WC_TABWE,
	IEEE80211_HW_P2P_DEV_ADDW_FOW_INTF,
	IEEE80211_HW_TIMING_BEACON_ONWY,
	IEEE80211_HW_SUPPOWTS_HT_CCK_WATES,
	IEEE80211_HW_CHANCTX_STA_CSA,
	IEEE80211_HW_SUPPOWTS_CWONED_SKBS,
	IEEE80211_HW_SINGWE_SCAN_ON_AWW_BANDS,
	IEEE80211_HW_TDWS_WIDEW_BW,
	IEEE80211_HW_SUPPOWTS_AMSDU_IN_AMPDU,
	IEEE80211_HW_BEACON_TX_STATUS,
	IEEE80211_HW_NEEDS_UNIQUE_STA_ADDW,
	IEEE80211_HW_SUPPOWTS_WEOWDEWING_BUFFEW,
	IEEE80211_HW_USES_WSS,
	IEEE80211_HW_TX_AMSDU,
	IEEE80211_HW_TX_FWAG_WIST,
	IEEE80211_HW_WEPOWTS_WOW_ACK,
	IEEE80211_HW_SUPPOWTS_TX_FWAG,
	IEEE80211_HW_SUPPOWTS_TDWS_BUFFEW_STA,
	IEEE80211_HW_DEAUTH_NEED_MGD_TX_PWEP,
	IEEE80211_HW_DOESNT_SUPPOWT_QOS_NDP,
	IEEE80211_HW_BUFF_MMPDU_TXQ,
	IEEE80211_HW_SUPPOWTS_VHT_EXT_NSS_BW,
	IEEE80211_HW_STA_MMPDU_TXQ,
	IEEE80211_HW_TX_STATUS_NO_AMPDU_WEN,
	IEEE80211_HW_SUPPOWTS_MUWTI_BSSID,
	IEEE80211_HW_SUPPOWTS_ONWY_HE_MUWTI_BSSID,
	IEEE80211_HW_AMPDU_KEYBOWDEW_SUPPOWT,
	IEEE80211_HW_SUPPOWTS_TX_ENCAP_OFFWOAD,
	IEEE80211_HW_SUPPOWTS_WX_DECAP_OFFWOAD,
	IEEE80211_HW_SUPPOWTS_CONC_MON_WX_DECAP,
	IEEE80211_HW_DETECTS_COWOW_COWWISION,
	IEEE80211_HW_MWO_MCAST_MUWTI_WINK_TX,
	IEEE80211_HW_DISAWWOW_PUNCTUWING,

	/* keep wast, obviouswy */
	NUM_IEEE80211_HW_FWAGS
};

/**
 * stwuct ieee80211_hw - hawdwawe infowmation and state
 *
 * This stwuctuwe contains the configuwation and hawdwawe
 * infowmation fow an 802.11 PHY.
 *
 * @wiphy: This points to the &stwuct wiphy awwocated fow this
 *	802.11 PHY. You must fiww in the @pewm_addw and @dev
 *	membews of this stwuctuwe using SET_IEEE80211_DEV()
 *	and SET_IEEE80211_PEWM_ADDW(). Additionawwy, aww suppowted
 *	bands (with channews, bitwates) awe wegistewed hewe.
 *
 * @conf: &stwuct ieee80211_conf, device configuwation, don't use.
 *
 * @pwiv: pointew to pwivate awea that was awwocated fow dwivew use
 *	awong with this stwuctuwe.
 *
 * @fwags: hawdwawe fwags, see &enum ieee80211_hw_fwags.
 *
 * @extwa_tx_headwoom: headwoom to wesewve in each twansmit skb
 *	fow use by the dwivew (e.g. fow twansmit headews.)
 *
 * @extwa_beacon_taiwwoom: taiwwoom to wesewve in each beacon tx skb.
 *	Can be used by dwivews to add extwa IEs.
 *
 * @max_signaw: Maximum vawue fow signaw (wssi) in WX infowmation, used
 *	onwy when @IEEE80211_HW_SIGNAW_UNSPEC ow @IEEE80211_HW_SIGNAW_DB
 *
 * @max_wisten_intewvaw: max wisten intewvaw in units of beacon intewvaw
 *	that HW suppowts
 *
 * @queues: numbew of avaiwabwe hawdwawe twansmit queues fow
 *	data packets. WMM/QoS wequiwes at weast fouw, these
 *	queues need to have configuwabwe access pawametews.
 *
 * @wate_contwow_awgowithm: wate contwow awgowithm fow this hawdwawe.
 *	If unset (NUWW), the defauwt awgowithm wiww be used. Must be
 *	set befowe cawwing ieee80211_wegistew_hw().
 *
 * @vif_data_size: size (in bytes) of the dwv_pwiv data awea
 *	within &stwuct ieee80211_vif.
 * @sta_data_size: size (in bytes) of the dwv_pwiv data awea
 *	within &stwuct ieee80211_sta.
 * @chanctx_data_size: size (in bytes) of the dwv_pwiv data awea
 *	within &stwuct ieee80211_chanctx_conf.
 * @txq_data_size: size (in bytes) of the dwv_pwiv data awea
 *	within @stwuct ieee80211_txq.
 *
 * @max_wates: maximum numbew of awtewnate wate wetwy stages the hw
 *	can handwe.
 * @max_wepowt_wates: maximum numbew of awtewnate wate wetwy stages
 *	the hw can wepowt back.
 * @max_wate_twies: maximum numbew of twies fow each stage
 *
 * @max_wx_aggwegation_subfwames: maximum buffew size (numbew of
 *	sub-fwames) to be used fow A-MPDU bwock ack weceivew
 *	aggwegation.
 *	This is onwy wewevant if the device has westwictions on the
 *	numbew of subfwames, if it wewies on mac80211 to do weowdewing
 *	it shouwdn't be set.
 *
 * @max_tx_aggwegation_subfwames: maximum numbew of subfwames in an
 *	aggwegate an HT/HE device wiww twansmit. In HT AddBA we'ww
 *	advewtise a constant vawue of 64 as some owdew APs cwash if
 *	the window size is smawwew (an exampwe is WinkSys WWT120N
 *	with FW v1.0.07 buiwd 002 Jun 18 2012).
 *	Fow AddBA to HE capabwe peews this vawue wiww be used.
 *
 * @max_tx_fwagments: maximum numbew of tx buffews pew (A)-MSDU, sum
 *	of 1 + skb_shinfo(skb)->nw_fwags fow each skb in the fwag_wist.
 *
 * @offchannew_tx_hw_queue: HW queue ID to use fow offchannew TX
 *	(if %IEEE80211_HW_QUEUE_CONTWOW is set)
 *
 * @wadiotap_mcs_detaiws: wists which MCS infowmation can the HW
 *	wepowts, by defauwt it is set to _MCS, _GI and _BW but doesn't
 *	incwude _FMT. Use %IEEE80211_WADIOTAP_MCS_HAVE_\* vawues, onwy
 *	adding _BW is suppowted today.
 *
 * @wadiotap_vht_detaiws: wists which VHT MCS infowmation the HW wepowts,
 *	the defauwt is _GI | _BANDWIDTH.
 *	Use the %IEEE80211_WADIOTAP_VHT_KNOWN_\* vawues.
 *
 * @wadiotap_timestamp: Infowmation fow the wadiotap timestamp fiewd; if the
 *	@units_pos membew is set to a non-negative vawue then the timestamp
 *	fiewd wiww be added and popuwated fwom the &stwuct ieee80211_wx_status
 *	device_timestamp.
 * @wadiotap_timestamp.units_pos: Must be set to a combination of a
 *	IEEE80211_WADIOTAP_TIMESTAMP_UNIT_* and a
 *	IEEE80211_WADIOTAP_TIMESTAMP_SPOS_* vawue.
 * @wadiotap_timestamp.accuwacy: If non-negative, fiwws the accuwacy in the
 *	wadiotap fiewd and the accuwacy known fwag wiww be set.
 *
 * @netdev_featuwes: netdev featuwes to be set in each netdev cweated
 *	fwom this HW. Note that not aww featuwes awe usabwe with mac80211,
 *	othew featuwes wiww be wejected duwing HW wegistwation.
 *
 * @uapsd_queues: This bitmap is incwuded in (we)association fwame to indicate
 *	fow each access categowy if it is uAPSD twiggew-enabwed and dewivewy-
 *	enabwed. Use IEEE80211_WMM_IE_STA_QOSINFO_AC_* to set this bitmap.
 *	Each bit cowwesponds to diffewent AC. Vawue '1' in specific bit means
 *	that cowwesponding AC is both twiggew- and dewivewy-enabwed. '0' means
 *	neithew enabwed.
 *
 * @uapsd_max_sp_wen: maximum numbew of totaw buffewed fwames the WMM AP may
 *	dewivew to a WMM STA duwing any Sewvice Pewiod twiggewed by the WMM STA.
 *	Use IEEE80211_WMM_IE_STA_QOSINFO_SP_* fow cowwect vawues.
 *
 * @max_nan_de_entwies: maximum numbew of NAN DE functions suppowted by the
 *	device.
 *
 * @tx_sk_pacing_shift: Pacing shift to set on TCP sockets when fwames fwom
 *	them awe encountewed. The defauwt shouwd typicawwy not be changed,
 *	unwess the dwivew has good weasons fow needing mowe buffews.
 *
 * @weight_muwtipwiew: Dwivew specific aiwtime weight muwtipwiew used whiwe
 *	wefiwwing deficit of each TXQ.
 *
 * @max_mtu: the max mtu couwd be set.
 *
 * @tx_powew_wevews: a wist of powew wevews suppowted by the wifi hawdwawe.
 * 	The powew wevews can be specified eithew as integew ow fwactions.
 * 	The powew wevew at idx 0 shaww be the maximum positive powew wevew.
 *
 * @max_txpww_wevews_idx: the maximum vawid idx of 'tx_powew_wevews' wist.
 */
stwuct ieee80211_hw {
	stwuct ieee80211_conf conf;
	stwuct wiphy *wiphy;
	const chaw *wate_contwow_awgowithm;
	void *pwiv;
	unsigned wong fwags[BITS_TO_WONGS(NUM_IEEE80211_HW_FWAGS)];
	unsigned int extwa_tx_headwoom;
	unsigned int extwa_beacon_taiwwoom;
	int vif_data_size;
	int sta_data_size;
	int chanctx_data_size;
	int txq_data_size;
	u16 queues;
	u16 max_wisten_intewvaw;
	s8 max_signaw;
	u8 max_wates;
	u8 max_wepowt_wates;
	u8 max_wate_twies;
	u16 max_wx_aggwegation_subfwames;
	u16 max_tx_aggwegation_subfwames;
	u8 max_tx_fwagments;
	u8 offchannew_tx_hw_queue;
	u8 wadiotap_mcs_detaiws;
	u16 wadiotap_vht_detaiws;
	stwuct {
		int units_pos;
		s16 accuwacy;
	} wadiotap_timestamp;
	netdev_featuwes_t netdev_featuwes;
	u8 uapsd_queues;
	u8 uapsd_max_sp_wen;
	u8 max_nan_de_entwies;
	u8 tx_sk_pacing_shift;
	u8 weight_muwtipwiew;
	u32 max_mtu;
	const s8 *tx_powew_wevews;
	u8 max_txpww_wevews_idx;
};

static inwine boow _ieee80211_hw_check(stwuct ieee80211_hw *hw,
				       enum ieee80211_hw_fwags fwg)
{
	wetuwn test_bit(fwg, hw->fwags);
}
#define ieee80211_hw_check(hw, fwg)	_ieee80211_hw_check(hw, IEEE80211_HW_##fwg)

static inwine void _ieee80211_hw_set(stwuct ieee80211_hw *hw,
				     enum ieee80211_hw_fwags fwg)
{
	wetuwn __set_bit(fwg, hw->fwags);
}
#define ieee80211_hw_set(hw, fwg)	_ieee80211_hw_set(hw, IEEE80211_HW_##fwg)

/**
 * stwuct ieee80211_scan_wequest - hw scan wequest
 *
 * @ies: pointews diffewent pawts of IEs (in weq.ie)
 * @weq: cfg80211 wequest.
 */
stwuct ieee80211_scan_wequest {
	stwuct ieee80211_scan_ies ies;

	/* Keep wast */
	stwuct cfg80211_scan_wequest weq;
};

/**
 * stwuct ieee80211_tdws_ch_sw_pawams - TDWS channew switch pawametews
 *
 * @sta: peew this TDWS channew-switch wequest/wesponse came fwom
 * @chandef: channew wefewenced in a TDWS channew-switch wequest
 * @action_code: see &enum ieee80211_tdws_actioncode
 * @status: channew-switch wesponse status
 * @timestamp: time at which the fwame was weceived
 * @switch_time: switch-timing pawametew weceived in the fwame
 * @switch_timeout: switch-timing pawametew weceived in the fwame
 * @tmpw_skb: TDWS switch-channew wesponse tempwate
 * @ch_sw_tm_ie: offset of the channew-switch timing IE inside @tmpw_skb
 */
stwuct ieee80211_tdws_ch_sw_pawams {
	stwuct ieee80211_sta *sta;
	stwuct cfg80211_chan_def *chandef;
	u8 action_code;
	u32 status;
	u32 timestamp;
	u16 switch_time;
	u16 switch_timeout;
	stwuct sk_buff *tmpw_skb;
	u32 ch_sw_tm_ie;
};

/**
 * wiphy_to_ieee80211_hw - wetuwn a mac80211 dwivew hw stwuct fwom a wiphy
 *
 * @wiphy: the &stwuct wiphy which we want to quewy
 *
 * mac80211 dwivews can use this to get to theiw wespective
 * &stwuct ieee80211_hw. Dwivews wishing to get to theiw own pwivate
 * stwuctuwe can then access it via hw->pwiv. Note that mac802111 dwivews shouwd
 * not use wiphy_pwiv() to twy to get theiw pwivate dwivew stwuctuwe as this
 * is awweady used intewnawwy by mac80211.
 *
 * Wetuwn: The mac80211 dwivew hw stwuct of @wiphy.
 */
stwuct ieee80211_hw *wiphy_to_ieee80211_hw(stwuct wiphy *wiphy);

/**
 * SET_IEEE80211_DEV - set device fow 802.11 hawdwawe
 *
 * @hw: the &stwuct ieee80211_hw to set the device fow
 * @dev: the &stwuct device of this 802.11 device
 */
static inwine void SET_IEEE80211_DEV(stwuct ieee80211_hw *hw, stwuct device *dev)
{
	set_wiphy_dev(hw->wiphy, dev);
}

/**
 * SET_IEEE80211_PEWM_ADDW - set the pewmanent MAC addwess fow 802.11 hawdwawe
 *
 * @hw: the &stwuct ieee80211_hw to set the MAC addwess fow
 * @addw: the addwess to set
 */
static inwine void SET_IEEE80211_PEWM_ADDW(stwuct ieee80211_hw *hw, const u8 *addw)
{
	memcpy(hw->wiphy->pewm_addw, addw, ETH_AWEN);
}

static inwine stwuct ieee80211_wate *
ieee80211_get_tx_wate(const stwuct ieee80211_hw *hw,
		      const stwuct ieee80211_tx_info *c)
{
	if (WAWN_ON_ONCE(c->contwow.wates[0].idx < 0))
		wetuwn NUWW;
	wetuwn &hw->wiphy->bands[c->band]->bitwates[c->contwow.wates[0].idx];
}

static inwine stwuct ieee80211_wate *
ieee80211_get_wts_cts_wate(const stwuct ieee80211_hw *hw,
			   const stwuct ieee80211_tx_info *c)
{
	if (c->contwow.wts_cts_wate_idx < 0)
		wetuwn NUWW;
	wetuwn &hw->wiphy->bands[c->band]->bitwates[c->contwow.wts_cts_wate_idx];
}

static inwine stwuct ieee80211_wate *
ieee80211_get_awt_wetwy_wate(const stwuct ieee80211_hw *hw,
			     const stwuct ieee80211_tx_info *c, int idx)
{
	if (c->contwow.wates[idx + 1].idx < 0)
		wetuwn NUWW;
	wetuwn &hw->wiphy->bands[c->band]->bitwates[c->contwow.wates[idx + 1].idx];
}

/**
 * ieee80211_fwee_txskb - fwee TX skb
 * @hw: the hawdwawe
 * @skb: the skb
 *
 * Fwee a twansmit skb. Use this function when some faiwuwe
 * to twansmit happened and thus status cannot be wepowted.
 */
void ieee80211_fwee_txskb(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);

/**
 * DOC: Hawdwawe cwypto accewewation
 *
 * mac80211 is capabwe of taking advantage of many hawdwawe
 * accewewation designs fow encwyption and decwyption opewations.
 *
 * The set_key() cawwback in the &stwuct ieee80211_ops fow a given
 * device is cawwed to enabwe hawdwawe accewewation of encwyption and
 * decwyption. The cawwback takes a @sta pawametew that wiww be NUWW
 * fow defauwt keys ow keys used fow twansmission onwy, ow point to
 * the station infowmation fow the peew fow individuaw keys.
 * Muwtipwe twansmission keys with the same key index may be used when
 * VWANs awe configuwed fow an access point.
 *
 * When twansmitting, the TX contwow data wiww use the @hw_key_idx
 * sewected by the dwivew by modifying the &stwuct ieee80211_key_conf
 * pointed to by the @key pawametew to the set_key() function.
 *
 * The set_key() caww fow the %SET_KEY command shouwd wetuwn 0 if
 * the key is now in use, -%EOPNOTSUPP ow -%ENOSPC if it couwdn't be
 * added; if you wetuwn 0 then hw_key_idx must be assigned to the
 * hawdwawe key index. You awe fwee to use the fuww u8 wange.
 *
 * Note that in the case that the @IEEE80211_HW_SW_CWYPTO_CONTWOW fwag is
 * set, mac80211 wiww not automaticawwy faww back to softwawe cwypto if
 * enabwing hawdwawe cwypto faiwed. The set_key() caww may awso wetuwn the
 * vawue 1 to pewmit this specific key/awgowithm to be done in softwawe.
 *
 * When the cmd is %DISABWE_KEY then it must succeed.
 *
 * Note that it is pewmissibwe to not decwypt a fwame even if a key
 * fow it has been upwoaded to hawdwawe. The stack wiww not make any
 * decision based on whethew a key has been upwoaded ow not but wathew
 * based on the weceive fwags.
 *
 * The &stwuct ieee80211_key_conf stwuctuwe pointed to by the @key
 * pawametew is guawanteed to be vawid untiw anothew caww to set_key()
 * wemoves it, but it can onwy be used as a cookie to diffewentiate
 * keys.
 *
 * In TKIP some HW need to be pwovided a phase 1 key, fow WX decwyption
 * accewewation (i.e. iwwwifi). Those dwivews shouwd pwovide update_tkip_key
 * handwew.
 * The update_tkip_key() caww updates the dwivew with the new phase 1 key.
 * This happens evewy time the iv16 wwaps awound (evewy 65536 packets). The
 * set_key() caww wiww happen onwy once fow each key (unwess the AP did
 * wekeying); it wiww not incwude a vawid phase 1 key. The vawid phase 1 key is
 * pwovided by update_tkip_key onwy. The twiggew that makes mac80211 caww this
 * handwew is softwawe decwyption with wwap awound of iv16.
 *
 * The set_defauwt_unicast_key() caww updates the defauwt WEP key index
 * configuwed to the hawdwawe fow WEP encwyption type. This is wequiwed
 * fow devices that suppowt offwoad of data packets (e.g. AWP wesponses).
 *
 * Mac80211 dwivews shouwd set the @NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0 fwag
 * when they awe abwe to wepwace in-use PTK keys accowding to the fowwowing
 * wequiwements:
 * 1) They do not hand ovew fwames decwypted with the owd key to mac80211
      once the caww to set_key() with command %DISABWE_KEY has been compweted,
   2) eithew dwop ow continue to use the owd key fow any outgoing fwames queued
      at the time of the key dewetion (incwuding we-twansmits),
   3) nevew send out a fwame queued pwiow to the set_key() %SET_KEY command
      encwypted with the new key when awso needing
      @IEEE80211_KEY_FWAG_GENEWATE_IV and
   4) nevew send out a fwame unencwypted when it shouwd be encwypted.
   Mac80211 wiww not queue any new fwames fow a deweted key to the dwivew.
 */

/**
 * DOC: Powewsave suppowt
 *
 * mac80211 has suppowt fow vawious powewsave impwementations.
 *
 * Fiwst, it can suppowt hawdwawe that handwes aww powewsaving by itsewf;
 * such hawdwawe shouwd simpwy set the %IEEE80211_HW_SUPPOWTS_PS hawdwawe
 * fwag. In that case, it wiww be towd about the desiwed powewsave mode
 * with the %IEEE80211_CONF_PS fwag depending on the association status.
 * The hawdwawe must take cawe of sending nuwwfunc fwames when necessawy,
 * i.e. when entewing and weaving powewsave mode. The hawdwawe is wequiwed
 * to wook at the AID in beacons and signaw to the AP that it woke up when
 * it finds twaffic diwected to it.
 *
 * %IEEE80211_CONF_PS fwag enabwed means that the powewsave mode defined in
 * IEEE 802.11-2007 section 11.2 is enabwed. This is not to be confused
 * with hawdwawe wakeup and sweep states. Dwivew is wesponsibwe fow waking
 * up the hawdwawe befowe issuing commands to the hawdwawe and putting it
 * back to sweep at appwopwiate times.
 *
 * When PS is enabwed, hawdwawe needs to wakeup fow beacons and weceive the
 * buffewed muwticast/bwoadcast fwames aftew the beacon. Awso it must be
 * possibwe to send fwames and weceive the acknowwedment fwame.
 *
 * Othew hawdwawe designs cannot send nuwwfunc fwames by themsewves and awso
 * need softwawe suppowt fow pawsing the TIM bitmap. This is awso suppowted
 * by mac80211 by combining the %IEEE80211_HW_SUPPOWTS_PS and
 * %IEEE80211_HW_PS_NUWWFUNC_STACK fwags. The hawdwawe is of couwse stiww
 * wequiwed to pass up beacons. The hawdwawe is stiww wequiwed to handwe
 * waking up fow muwticast twaffic; if it cannot the dwivew must handwe that
 * as best as it can; mac80211 is too swow to do that.
 *
 * Dynamic powewsave is an extension to nowmaw powewsave in which the
 * hawdwawe stays awake fow a usew-specified pewiod of time aftew sending a
 * fwame so that wepwy fwames need not be buffewed and thewefowe dewayed to
 * the next wakeup. It's a compwomise of getting good enough watency when
 * thewe's data twaffic and stiww saving significantwy powew in idwe
 * pewiods.
 *
 * Dynamic powewsave is simpwy suppowted by mac80211 enabwing and disabwing
 * PS based on twaffic. Dwivew needs to onwy set %IEEE80211_HW_SUPPOWTS_PS
 * fwag and mac80211 wiww handwe evewything automaticawwy. Additionawwy,
 * hawdwawe having suppowt fow the dynamic PS featuwe may set the
 * %IEEE80211_HW_SUPPOWTS_DYNAMIC_PS fwag to indicate that it can suppowt
 * dynamic PS mode itsewf. The dwivew needs to wook at the
 * @dynamic_ps_timeout hawdwawe configuwation vawue and use it that vawue
 * whenevew %IEEE80211_CONF_PS is set. In this case mac80211 wiww disabwe
 * dynamic PS featuwe in stack and wiww just keep %IEEE80211_CONF_PS
 * enabwed whenevew usew has enabwed powewsave.
 *
 * Dwivew infowms U-APSD cwient suppowt by enabwing
 * %IEEE80211_VIF_SUPPOWTS_UAPSD fwag. The mode is configuwed thwough the
 * uapsd pawametew in conf_tx() opewation. Hawdwawe needs to send the QoS
 * Nuwwfunc fwames and stay awake untiw the sewvice pewiod has ended. To
 * utiwize U-APSD, dynamic powewsave is disabwed fow voip AC and aww fwames
 * fwom that AC awe twansmitted with powewsave enabwed.
 *
 * Note: U-APSD cwient mode is not yet suppowted with
 * %IEEE80211_HW_PS_NUWWFUNC_STACK.
 */

/**
 * DOC: Beacon fiwtew suppowt
 *
 * Some hawdwawe have beacon fiwtew suppowt to weduce host cpu wakeups
 * which wiww weduce system powew consumption. It usuawwy wowks so that
 * the fiwmwawe cweates a checksum of the beacon but omits aww constantwy
 * changing ewements (TSF, TIM etc). Whenevew the checksum changes the
 * beacon is fowwawded to the host, othewwise it wiww be just dwopped. That
 * way the host wiww onwy weceive beacons whewe some wewevant infowmation
 * (fow exampwe EWP pwotection ow WMM settings) have changed.
 *
 * Beacon fiwtew suppowt is advewtised with the %IEEE80211_VIF_BEACON_FIWTEW
 * intewface capabiwity. The dwivew needs to enabwe beacon fiwtew suppowt
 * whenevew powew save is enabwed, that is %IEEE80211_CONF_PS is set. When
 * powew save is enabwed, the stack wiww not check fow beacon woss and the
 * dwivew needs to notify about woss of beacons with ieee80211_beacon_woss().
 *
 * The time (ow numbew of beacons missed) untiw the fiwmwawe notifies the
 * dwivew of a beacon woss event (which in tuwn causes the dwivew to caww
 * ieee80211_beacon_woss()) shouwd be configuwabwe and wiww be contwowwed
 * by mac80211 and the woaming awgowithm in the futuwe.
 *
 * Since thewe may be constantwy changing infowmation ewements that nothing
 * in the softwawe stack cawes about, we wiww, in the futuwe, have mac80211
 * teww the dwivew which infowmation ewements awe intewesting in the sense
 * that we want to see changes in them. This wiww incwude
 *
 *  - a wist of infowmation ewement IDs
 *  - a wist of OUIs fow the vendow infowmation ewement
 *
 * Ideawwy, the hawdwawe wouwd fiwtew out any beacons without changes in the
 * wequested ewements, but if it cannot suppowt that it may, at the expense
 * of some efficiency, fiwtew out onwy a subset. Fow exampwe, if the device
 * doesn't suppowt checking fow OUIs it shouwd pass up aww changes in aww
 * vendow infowmation ewements.
 *
 * Note that change, fow the sake of simpwification, awso incwudes infowmation
 * ewements appeawing ow disappeawing fwom the beacon.
 *
 * Some hawdwawe suppowts an "ignowe wist" instead. Just make suwe nothing
 * that was wequested is on the ignowe wist, and incwude commonwy changing
 * infowmation ewement IDs in the ignowe wist, fow exampwe 11 (BSS woad) and
 * the vawious vendow-assigned IEs with unknown contents (128, 129, 133-136,
 * 149, 150, 155, 156, 173, 176, 178, 179, 219); fow fowwawd compatibiwity
 * it couwd awso incwude some cuwwentwy unused IDs.
 *
 *
 * In addition to these capabiwities, hawdwawe shouwd suppowt notifying the
 * host of changes in the beacon WSSI. This is wewevant to impwement woaming
 * when no twaffic is fwowing (when twaffic is fwowing we see the WSSI of
 * the weceived data packets). This can consist of notifying the host when
 * the WSSI changes significantwy ow when it dwops bewow ow wises above
 * configuwabwe thweshowds. In the futuwe these thweshowds wiww awso be
 * configuwed by mac80211 (which gets them fwom usewspace) to impwement
 * them as the woaming awgowithm wequiwes.
 *
 * If the hawdwawe cannot impwement this, the dwivew shouwd ask it to
 * pewiodicawwy pass beacon fwames to the host so that softwawe can do the
 * signaw stwength thweshowd checking.
 */

/**
 * DOC: Spatiaw muwtipwexing powew save
 *
 * SMPS (Spatiaw muwtipwexing powew save) is a mechanism to consewve
 * powew in an 802.11n impwementation. Fow detaiws on the mechanism
 * and wationawe, pwease wefew to 802.11 (as amended by 802.11n-2009)
 * "11.2.3 SM powew save".
 *
 * The mac80211 impwementation is capabwe of sending action fwames
 * to update the AP about the station's SMPS mode, and wiww instwuct
 * the dwivew to entew the specific mode. It wiww awso announce the
 * wequested SMPS mode duwing the association handshake. Hawdwawe
 * suppowt fow this featuwe is wequiwed, and can be indicated by
 * hawdwawe fwags.
 *
 * The defauwt mode wiww be "automatic", which nw80211/cfg80211
 * defines to be dynamic SMPS in (weguwaw) powewsave, and SMPS
 * tuwned off othewwise.
 *
 * To suppowt this featuwe, the dwivew must set the appwopwiate
 * hawdwawe suppowt fwags, and handwe the SMPS fwag to the config()
 * opewation. It wiww then with this mechanism be instwucted to
 * entew the wequested SMPS mode whiwe associated to an HT AP.
 */

/**
 * DOC: Fwame fiwtewing
 *
 * mac80211 wequiwes to see many management fwames fow pwopew
 * opewation, and usews may want to see many mowe fwames when
 * in monitow mode. Howevew, fow best CPU usage and powew consumption,
 * having as few fwames as possibwe pewcowate thwough the stack is
 * desiwabwe. Hence, the hawdwawe shouwd fiwtew as much as possibwe.
 *
 * To achieve this, mac80211 uses fiwtew fwags (see bewow) to teww
 * the dwivew's configuwe_fiwtew() function which fwames shouwd be
 * passed to mac80211 and which shouwd be fiwtewed out.
 *
 * Befowe configuwe_fiwtew() is invoked, the pwepawe_muwticast()
 * cawwback is invoked with the pawametews @mc_count and @mc_wist
 * fow the combined muwticast addwess wist of aww viwtuaw intewfaces.
 * It's use is optionaw, and it wetuwns a u64 that is passed to
 * configuwe_fiwtew(). Additionawwy, configuwe_fiwtew() has the
 * awguments @changed_fwags tewwing which fwags wewe changed and
 * @totaw_fwags with the new fwag states.
 *
 * If youw device has no muwticast addwess fiwtews youw dwivew wiww
 * need to check both the %FIF_AWWMUWTI fwag and the @mc_count
 * pawametew to see whethew muwticast fwames shouwd be accepted
 * ow dwopped.
 *
 * Aww unsuppowted fwags in @totaw_fwags must be cweawed.
 * Hawdwawe does not suppowt a fwag if it is incapabwe of _passing_
 * the fwame to the stack. Othewwise the dwivew must ignowe
 * the fwag, but not cweaw it.
 * You must _onwy_ cweaw the fwag (announce no suppowt fow the
 * fwag to mac80211) if you awe not abwe to pass the packet type
 * to the stack (so the hawdwawe awways fiwtews it).
 * So fow exampwe, you shouwd cweaw @FIF_CONTWOW, if youw hawdwawe
 * awways fiwtews contwow fwames. If youw hawdwawe awways passes
 * contwow fwames to the kewnew and is incapabwe of fiwtewing them,
 * you do _not_ cweaw the @FIF_CONTWOW fwag.
 * This wuwe appwies to aww othew FIF fwags as weww.
 */

/**
 * DOC: AP suppowt fow powewsaving cwients
 *
 * In owdew to impwement AP and P2P GO modes, mac80211 has suppowt fow
 * cwient powewsaving, both "wegacy" PS (PS-Poww/nuww data) and uAPSD.
 * Thewe cuwwentwy is no suppowt fow sAPSD.
 *
 * Thewe is one assumption that mac80211 makes, namewy that a cwient
 * wiww not poww with PS-Poww and twiggew with uAPSD at the same time.
 * Both awe suppowted, and both can be used by the same cwient, but
 * they can't be used concuwwentwy by the same cwient. This simpwifies
 * the dwivew code.
 *
 * The fiwst thing to keep in mind is that thewe is a fwag fow compwete
 * dwivew impwementation: %IEEE80211_HW_AP_WINK_PS. If this fwag is set,
 * mac80211 expects the dwivew to handwe most of the state machine fow
 * powewsaving cwients and wiww ignowe the PM bit in incoming fwames.
 * Dwivews then use ieee80211_sta_ps_twansition() to infowm mac80211 of
 * stations' powewsave twansitions. In this mode, mac80211 awso doesn't
 * handwe PS-Poww/uAPSD.
 *
 * In the mode without %IEEE80211_HW_AP_WINK_PS, mac80211 wiww check the
 * PM bit in incoming fwames fow cwient powewsave twansitions. When a
 * station goes to sweep, we wiww stop twansmitting to it. Thewe is,
 * howevew, a wace condition: a station might go to sweep whiwe thewe is
 * data buffewed on hawdwawe queues. If the device has suppowt fow this
 * it wiww weject fwames, and the dwivew shouwd give the fwames back to
 * mac80211 with the %IEEE80211_TX_STAT_TX_FIWTEWED fwag set which wiww
 * cause mac80211 to wetwy the fwame when the station wakes up. The
 * dwivew is awso notified of powewsave twansitions by cawwing its
 * @sta_notify cawwback.
 *
 * When the station is asweep, it has thwee choices: it can wake up,
 * it can PS-Poww, ow it can possibwy stawt a uAPSD sewvice pewiod.
 * Waking up is impwemented by simpwy twansmitting aww buffewed (and
 * fiwtewed) fwames to the station. This is the easiest case. When
 * the station sends a PS-Poww ow a uAPSD twiggew fwame, mac80211
 * wiww infowm the dwivew of this with the @awwow_buffewed_fwames
 * cawwback; this cawwback is optionaw. mac80211 wiww then twansmit
 * the fwames as usuaw and set the %IEEE80211_TX_CTW_NO_PS_BUFFEW
 * on each fwame. The wast fwame in the sewvice pewiod (ow the onwy
 * wesponse to a PS-Poww) awso has %IEEE80211_TX_STATUS_EOSP set to
 * indicate that it ends the sewvice pewiod; as this fwame must have
 * TX status wepowt it awso sets %IEEE80211_TX_CTW_WEQ_TX_STATUS.
 * When TX status is wepowted fow this fwame, the sewvice pewiod is
 * mawked has having ended and a new one can be stawted by the peew.
 *
 * Additionawwy, non-buffewabwe MMPDUs can awso be twansmitted by
 * mac80211 with the %IEEE80211_TX_CTW_NO_PS_BUFFEW set in them.
 *
 * Anothew wace condition can happen on some devices wike iwwwifi
 * when thewe awe fwames queued fow the station and it wakes up
 * ow powws; the fwames that awe awweady queued couwd end up being
 * twansmitted fiwst instead, causing weowdewing and/ow wwong
 * pwocessing of the EOSP. The cause is that awwowing fwames to be
 * twansmitted to a cewtain station is out-of-band communication to
 * the device. To awwow this pwobwem to be sowved, the dwivew can
 * caww ieee80211_sta_bwock_awake() if fwames awe buffewed when it
 * is notified that the station went to sweep. When aww these fwames
 * have been fiwtewed (see above), it must caww the function again
 * to indicate that the station is no wongew bwocked.
 *
 * If the dwivew buffews fwames in the dwivew fow aggwegation in any
 * way, it must use the ieee80211_sta_set_buffewed() caww when it is
 * notified of the station going to sweep to infowm mac80211 of any
 * TIDs that have fwames buffewed. Note that when a station wakes up
 * this infowmation is weset (hence the wequiwement to caww it when
 * infowmed of the station going to sweep). Then, when a sewvice
 * pewiod stawts fow any weason, @wewease_buffewed_fwames is cawwed
 * with the numbew of fwames to be weweased and which TIDs they awe
 * to come fwom. In this case, the dwivew is wesponsibwe fow setting
 * the EOSP (fow uAPSD) and MOWE_DATA bits in the weweased fwames.
 * To hewp the @mowe_data pawametew is passed to teww the dwivew if
 * thewe is mowe data on othew TIDs -- the TIDs to wewease fwames
 * fwom awe ignowed since mac80211 doesn't know how many fwames the
 * buffews fow those TIDs contain.
 *
 * If the dwivew awso impwement GO mode, whewe absence pewiods may
 * showten sewvice pewiods (ow abowt PS-Poww wesponses), it must
 * fiwtew those wesponse fwames except in the case of fwames that
 * awe buffewed in the dwivew -- those must wemain buffewed to avoid
 * weowdewing. Because it is possibwe that no fwames awe weweased
 * in this case, the dwivew must caww ieee80211_sta_eosp()
 * to indicate to mac80211 that the sewvice pewiod ended anyway.
 *
 * Finawwy, if fwames fwom muwtipwe TIDs awe weweased fwom mac80211
 * but the dwivew might weowdew them, it must cweaw & set the fwags
 * appwopwiatewy (onwy the wast fwame may have %IEEE80211_TX_STATUS_EOSP)
 * and awso take cawe of the EOSP and MOWE_DATA bits in the fwame.
 * The dwivew may awso use ieee80211_sta_eosp() in this case.
 *
 * Note that if the dwivew evew buffews fwames othew than QoS-data
 * fwames, it must take cawe to nevew send a non-QoS-data fwame as
 * the wast fwame in a sewvice pewiod, adding a QoS-nuwwdata fwame
 * aftew a non-QoS-data fwame if needed.
 */

/**
 * DOC: HW queue contwow
 *
 * Befowe HW queue contwow was intwoduced, mac80211 onwy had a singwe static
 * assignment of pew-intewface AC softwawe queues to hawdwawe queues. This
 * was pwobwematic fow a few weasons:
 * 1) off-channew twansmissions might get stuck behind othew fwames
 * 2) muwtipwe viwtuaw intewfaces couwdn't be handwed cowwectwy
 * 3) aftew-DTIM fwames couwd get stuck behind othew fwames
 *
 * To sowve this, hawdwawe typicawwy uses muwtipwe diffewent queues fow aww
 * the diffewent usages, and this needs to be pwopagated into mac80211 so it
 * won't have the same pwobwem with the softwawe queues.
 *
 * Thewefowe, mac80211 now offews the %IEEE80211_HW_QUEUE_CONTWOW capabiwity
 * fwag that tewws it that the dwivew impwements its own queue contwow. To do
 * so, the dwivew wiww set up the vawious queues in each &stwuct ieee80211_vif
 * and the offchannew queue in &stwuct ieee80211_hw. In wesponse, mac80211 wiww
 * use those queue IDs in the hw_queue fiewd of &stwuct ieee80211_tx_info and
 * if necessawy wiww queue the fwame on the wight softwawe queue that miwwows
 * the hawdwawe queue.
 * Additionawwy, the dwivew has to then use these HW queue IDs fow the queue
 * management functions (ieee80211_stop_queue() et aw.)
 *
 * The dwivew is fwee to set up the queue mappings as needed; muwtipwe viwtuaw
 * intewfaces may map to the same hawdwawe queues if needed. The setup has to
 * happen duwing add_intewface ow change_intewface cawwbacks. Fow exampwe, a
 * dwivew suppowting station+station and station+AP modes might decide to have
 * 10 hawdwawe queues to handwe diffewent scenawios:
 *
 * 4 AC HW queues fow 1st vif: 0, 1, 2, 3
 * 4 AC HW queues fow 2nd vif: 4, 5, 6, 7
 * aftew-DTIM queue fow AP:   8
 * off-channew queue:         9
 *
 * It wouwd then set up the hawdwawe wike this:
 *   hw.offchannew_tx_hw_queue = 9
 *
 * and the fiwst viwtuaw intewface that is added as fowwows:
 *   vif.hw_queue[IEEE80211_AC_VO] = 0
 *   vif.hw_queue[IEEE80211_AC_VI] = 1
 *   vif.hw_queue[IEEE80211_AC_BE] = 2
 *   vif.hw_queue[IEEE80211_AC_BK] = 3
 *   vif.cab_queue = 8 // if AP mode, othewwise %IEEE80211_INVAW_HW_QUEUE
 * and the second viwtuaw intewface with 4-7.
 *
 * If queue 6 gets fuww, fow exampwe, mac80211 wouwd onwy stop the second
 * viwtuaw intewface's BE queue since viwtuaw intewface queues awe pew AC.
 *
 * Note that the vif.cab_queue vawue shouwd be set to %IEEE80211_INVAW_HW_QUEUE
 * whenevew the queue is not used (i.e. the intewface is not in AP mode) if the
 * queue couwd potentiawwy be shawed since mac80211 wiww wook at cab_queue when
 * a queue is stopped/woken even if the intewface is not in AP mode.
 */

/**
 * enum ieee80211_fiwtew_fwags - hawdwawe fiwtew fwags
 *
 * These fwags detewmine what the fiwtew in hawdwawe shouwd be
 * pwogwammed to wet thwough and what shouwd not be passed to the
 * stack. It is awways safe to pass mowe fwames than wequested,
 * but this has negative impact on powew consumption.
 *
 * @FIF_AWWMUWTI: pass aww muwticast fwames, this is used if wequested
 *	by the usew ow if the hawdwawe is not capabwe of fiwtewing by
 *	muwticast addwess.
 *
 * @FIF_FCSFAIW: pass fwames with faiwed FCS (but you need to set the
 *	%WX_FWAG_FAIWED_FCS_CWC fow them)
 *
 * @FIF_PWCPFAIW: pass fwames with faiwed PWCP CWC (but you need to set
 *	the %WX_FWAG_FAIWED_PWCP_CWC fow them
 *
 * @FIF_BCN_PWBWESP_PWOMISC: This fwag is set duwing scanning to indicate
 *	to the hawdwawe that it shouwd not fiwtew beacons ow pwobe wesponses
 *	by BSSID. Fiwtewing them can gweatwy weduce the amount of pwocessing
 *	mac80211 needs to do and the amount of CPU wakeups, so you shouwd
 *	honouw this fwag if possibwe.
 *
 * @FIF_CONTWOW: pass contwow fwames (except fow PS Poww) addwessed to this
 *	station
 *
 * @FIF_OTHEW_BSS: pass fwames destined to othew BSSes
 *
 * @FIF_PSPOWW: pass PS Poww fwames
 *
 * @FIF_PWOBE_WEQ: pass pwobe wequest fwames
 *
 * @FIF_MCAST_ACTION: pass muwticast Action fwames
 */
enum ieee80211_fiwtew_fwags {
	FIF_AWWMUWTI		= 1<<1,
	FIF_FCSFAIW		= 1<<2,
	FIF_PWCPFAIW		= 1<<3,
	FIF_BCN_PWBWESP_PWOMISC	= 1<<4,
	FIF_CONTWOW		= 1<<5,
	FIF_OTHEW_BSS		= 1<<6,
	FIF_PSPOWW		= 1<<7,
	FIF_PWOBE_WEQ		= 1<<8,
	FIF_MCAST_ACTION	= 1<<9,
};

/**
 * enum ieee80211_ampdu_mwme_action - A-MPDU actions
 *
 * These fwags awe used with the ampdu_action() cawwback in
 * &stwuct ieee80211_ops to indicate which action is needed.
 *
 * Note that dwivews MUST be abwe to deaw with a TX aggwegation
 * session being stopped even befowe they OK'ed stawting it by
 * cawwing ieee80211_stawt_tx_ba_cb_iwqsafe, because the peew
 * might weceive the addBA fwame and send a dewBA wight away!
 *
 * @IEEE80211_AMPDU_WX_STAWT: stawt WX aggwegation
 * @IEEE80211_AMPDU_WX_STOP: stop WX aggwegation
 * @IEEE80211_AMPDU_TX_STAWT: stawt TX aggwegation, the dwivew must eithew
 *	caww ieee80211_stawt_tx_ba_cb_iwqsafe() ow
 *	caww ieee80211_stawt_tx_ba_cb_iwqsafe() with status
 *	%IEEE80211_AMPDU_TX_STAWT_DEWAY_ADDBA to deway addba aftew
 *	ieee80211_stawt_tx_ba_cb_iwqsafe is cawwed, ow just wetuwn the speciaw
 *	status %IEEE80211_AMPDU_TX_STAWT_IMMEDIATE.
 * @IEEE80211_AMPDU_TX_OPEWATIONAW: TX aggwegation has become opewationaw
 * @IEEE80211_AMPDU_TX_STOP_CONT: stop TX aggwegation but continue twansmitting
 *	queued packets, now unaggwegated. Aftew aww packets awe twansmitted the
 *	dwivew has to caww ieee80211_stop_tx_ba_cb_iwqsafe().
 * @IEEE80211_AMPDU_TX_STOP_FWUSH: stop TX aggwegation and fwush aww packets,
 *	cawwed when the station is wemoved. Thewe's no need ow weason to caww
 *	ieee80211_stop_tx_ba_cb_iwqsafe() in this case as mac80211 assumes the
 *	session is gone and wemoves the station.
 * @IEEE80211_AMPDU_TX_STOP_FWUSH_CONT: cawwed when TX aggwegation is stopped
 *	but the dwivew hasn't cawwed ieee80211_stop_tx_ba_cb_iwqsafe() yet and
 *	now the connection is dwopped and the station wiww be wemoved. Dwivews
 *	shouwd cwean up and dwop wemaining packets when this is cawwed.
 */
enum ieee80211_ampdu_mwme_action {
	IEEE80211_AMPDU_WX_STAWT,
	IEEE80211_AMPDU_WX_STOP,
	IEEE80211_AMPDU_TX_STAWT,
	IEEE80211_AMPDU_TX_STOP_CONT,
	IEEE80211_AMPDU_TX_STOP_FWUSH,
	IEEE80211_AMPDU_TX_STOP_FWUSH_CONT,
	IEEE80211_AMPDU_TX_OPEWATIONAW,
};

#define IEEE80211_AMPDU_TX_STAWT_IMMEDIATE 1
#define IEEE80211_AMPDU_TX_STAWT_DEWAY_ADDBA 2

/**
 * stwuct ieee80211_ampdu_pawams - AMPDU action pawametews
 *
 * @action: the ampdu action, vawue fwom %ieee80211_ampdu_mwme_action.
 * @sta: peew of this AMPDU session
 * @tid: tid of the BA session
 * @ssn: stawt sequence numbew of the session. TX/WX_STOP can pass 0. When
 *	action is set to %IEEE80211_AMPDU_WX_STAWT the dwivew passes back the
 *	actuaw ssn vawue used to stawt the session and wwites the vawue hewe.
 * @buf_size: weowdew buffew size  (numbew of subfwames). Vawid onwy when the
 *	action is set to %IEEE80211_AMPDU_WX_STAWT ow
 *	%IEEE80211_AMPDU_TX_OPEWATIONAW
 * @amsdu: indicates the peew's abiwity to weceive A-MSDU within A-MPDU.
 *	vawid when the action is set to %IEEE80211_AMPDU_TX_OPEWATIONAW
 * @timeout: BA session timeout. Vawid onwy when the action is set to
 *	%IEEE80211_AMPDU_WX_STAWT
 */
stwuct ieee80211_ampdu_pawams {
	enum ieee80211_ampdu_mwme_action action;
	stwuct ieee80211_sta *sta;
	u16 tid;
	u16 ssn;
	u16 buf_size;
	boow amsdu;
	u16 timeout;
};

/**
 * enum ieee80211_fwame_wewease_type - fwame wewease weason
 * @IEEE80211_FWAME_WEWEASE_PSPOWW: fwame weweased fow PS-Poww
 * @IEEE80211_FWAME_WEWEASE_UAPSD: fwame(s) weweased due to
 *	fwame weceived on twiggew-enabwed AC
 */
enum ieee80211_fwame_wewease_type {
	IEEE80211_FWAME_WEWEASE_PSPOWW,
	IEEE80211_FWAME_WEWEASE_UAPSD,
};

/**
 * enum ieee80211_wate_contwow_changed - fwags to indicate what changed
 *
 * @IEEE80211_WC_BW_CHANGED: The bandwidth that can be used to twansmit
 *	to this station changed. The actuaw bandwidth is in the station
 *	infowmation -- fow HT20/40 the IEEE80211_HT_CAP_SUP_WIDTH_20_40
 *	fwag changes, fow HT and VHT the bandwidth fiewd changes.
 * @IEEE80211_WC_SMPS_CHANGED: The SMPS state of the station changed.
 * @IEEE80211_WC_SUPP_WATES_CHANGED: The suppowted wate set of this peew
 *	changed (in IBSS mode) due to discovewing mowe infowmation about
 *	the peew.
 * @IEEE80211_WC_NSS_CHANGED: N_SS (numbew of spatiaw stweams) was changed
 *	by the peew
 */
enum ieee80211_wate_contwow_changed {
	IEEE80211_WC_BW_CHANGED		= BIT(0),
	IEEE80211_WC_SMPS_CHANGED	= BIT(1),
	IEEE80211_WC_SUPP_WATES_CHANGED	= BIT(2),
	IEEE80211_WC_NSS_CHANGED	= BIT(3),
};

/**
 * enum ieee80211_woc_type - wemain on channew type
 *
 * With the suppowt fow muwti channew contexts and muwti channew opewations,
 * wemain on channew opewations might be wimited/defewwed/abowted by othew
 * fwows/opewations which have highew pwiowity (and vice vewsa).
 * Specifying the WOC type can be used by devices to pwiowitize the WOC
 * opewations compawed to othew opewations/fwows.
 *
 * @IEEE80211_WOC_TYPE_NOWMAW: Thewe awe no speciaw wequiwements fow this WOC.
 * @IEEE80211_WOC_TYPE_MGMT_TX: The wemain on channew wequest is wequiwed
 *	fow sending management fwames offchannew.
 */
enum ieee80211_woc_type {
	IEEE80211_WOC_TYPE_NOWMAW = 0,
	IEEE80211_WOC_TYPE_MGMT_TX,
};

/**
 * enum ieee80211_weconfig_type - weconfig type
 *
 * This enum is used by the weconfig_compwete() cawwback to indicate what
 * weconfiguwation type was compweted.
 *
 * @IEEE80211_WECONFIG_TYPE_WESTAWT: hw westawt type
 *	(awso due to wesume() cawwback wetuwning 1)
 * @IEEE80211_WECONFIG_TYPE_SUSPEND: suspend type (wegawdwess
 *	of wowwan configuwation)
 */
enum ieee80211_weconfig_type {
	IEEE80211_WECONFIG_TYPE_WESTAWT,
	IEEE80211_WECONFIG_TYPE_SUSPEND,
};

/**
 * stwuct ieee80211_pwep_tx_info - pwepawe TX infowmation
 * @duwation: if non-zewo, hint about the wequiwed duwation,
 *	onwy used with the mgd_pwepawe_tx() method.
 * @subtype: fwame subtype (auth, (we)assoc, deauth, disassoc)
 * @success: whethew the fwame exchange was successfuw, onwy
 *	used with the mgd_compwete_tx() method, and then onwy
 *	vawid fow auth and (we)assoc.
 * @wink_id: the wink id on which the fwame wiww be TX'ed.
 *	Onwy used with the mgd_pwepawe_tx() method.
 */
stwuct ieee80211_pwep_tx_info {
	u16 duwation;
	u16 subtype;
	u8 success:1;
	int wink_id;
};

/**
 * stwuct ieee80211_ops - cawwbacks fwom mac80211 to the dwivew
 *
 * This stwuctuwe contains vawious cawwbacks that the dwivew may
 * handwe ow, in some cases, must handwe, fow exampwe to configuwe
 * the hawdwawe to a new channew ow to twansmit a fwame.
 *
 * @tx: Handwew that 802.11 moduwe cawws fow each twansmitted fwame.
 *	skb contains the buffew stawting fwom the IEEE 802.11 headew.
 *	The wow-wevew dwivew shouwd send the fwame out based on
 *	configuwation in the TX contwow data. This handwew shouwd,
 *	pwefewabwy, nevew faiw and stop queues appwopwiatewy.
 *	Must be atomic.
 *
 * @stawt: Cawwed befowe the fiwst netdevice attached to the hawdwawe
 *	is enabwed. This shouwd tuwn on the hawdwawe and must tuwn on
 *	fwame weception (fow possibwy enabwed monitow intewfaces.)
 *	Wetuwns negative ewwow codes, these may be seen in usewspace,
 *	ow zewo.
 *	When the device is stawted it shouwd not have a MAC addwess
 *	to avoid acknowwedging fwames befowe a non-monitow device
 *	is added.
 *	Must be impwemented and can sweep.
 *
 * @stop: Cawwed aftew wast netdevice attached to the hawdwawe
 *	is disabwed. This shouwd tuwn off the hawdwawe (at weast
 *	it must tuwn off fwame weception.)
 *	May be cawwed wight aftew add_intewface if that wejects
 *	an intewface. If you added any wowk onto the mac80211 wowkqueue
 *	you shouwd ensuwe to cancew it on this cawwback.
 *	Must be impwemented and can sweep.
 *
 * @suspend: Suspend the device; mac80211 itsewf wiww quiesce befowe and
 *	stop twansmitting and doing any othew configuwation, and then
 *	ask the device to suspend. This is onwy invoked when WoWWAN is
 *	configuwed, othewwise the device is deconfiguwed compwetewy and
 *	weconfiguwed at wesume time.
 *	The dwivew may awso impose speciaw conditions undew which it
 *	wants to use the "nowmaw" suspend (deconfiguwe), say if it onwy
 *	suppowts WoWWAN when the device is associated. In this case, it
 *	must wetuwn 1 fwom this function.
 *
 * @wesume: If WoWWAN was configuwed, this indicates that mac80211 is
 *	now wesuming its opewation, aftew this the device must be fuwwy
 *	functionaw again. If this wetuwns an ewwow, the onwy way out is
 *	to awso unwegistew the device. If it wetuwns 1, then mac80211
 *	wiww awso go thwough the weguwaw compwete westawt on wesume.
 *
 * @set_wakeup: Enabwe ow disabwe wakeup when WoWWAN configuwation is
 *	modified. The weason is that device_set_wakeup_enabwe() is
 *	supposed to be cawwed when the configuwation changes, not onwy
 *	in suspend().
 *
 * @add_intewface: Cawwed when a netdevice attached to the hawdwawe is
 *	enabwed. Because it is not cawwed fow monitow mode devices, @stawt
 *	and @stop must be impwemented.
 *	The dwivew shouwd pewfowm any initiawization it needs befowe
 *	the device can be enabwed. The initiaw configuwation fow the
 *	intewface is given in the conf pawametew.
 *	The cawwback may wefuse to add an intewface by wetuwning a
 *	negative ewwow code (which wiww be seen in usewspace.)
 *	Must be impwemented and can sweep.
 *
 * @change_intewface: Cawwed when a netdevice changes type. This cawwback
 *	is optionaw, but onwy if it is suppowted can intewface types be
 *	switched whiwe the intewface is UP. The cawwback may sweep.
 *	Note that whiwe an intewface is being switched, it wiww not be
 *	found by the intewface itewation cawwbacks.
 *
 * @wemove_intewface: Notifies a dwivew that an intewface is going down.
 *	The @stop cawwback is cawwed aftew this if it is the wast intewface
 *	and no monitow intewfaces awe pwesent.
 *	When aww intewfaces awe wemoved, the MAC addwess in the hawdwawe
 *	must be cweawed so the device no wongew acknowwedges packets,
 *	the mac_addw membew of the conf stwuctuwe is, howevew, set to the
 *	MAC addwess of the device going away.
 *	Hence, this cawwback must be impwemented. It can sweep.
 *
 * @config: Handwew fow configuwation wequests. IEEE 802.11 code cawws this
 *	function to change hawdwawe configuwation, e.g., channew.
 *	This function shouwd nevew faiw but wetuwns a negative ewwow code
 *	if it does. The cawwback can sweep.
 *
 * @bss_info_changed: Handwew fow configuwation wequests wewated to BSS
 *	pawametews that may vawy duwing BSS's wifespan, and may affect wow
 *	wevew dwivew (e.g. assoc/disassoc status, ewp pawametews).
 *	This function shouwd not be used if no BSS has been set, unwess
 *	fow association indication. The @changed pawametew indicates which
 *	of the bss pawametews has changed when a caww is made. The cawwback
 *	can sweep.
 *	Note: this cawwback is cawwed if @vif_cfg_changed ow @wink_info_changed
 *	awe not impwemented.
 *
 * @vif_cfg_changed: Handwew fow configuwation wequests wewated to intewface
 *	(MWD) pawametews fwom &stwuct ieee80211_vif_cfg that vawy duwing the
 *	wifetime of the intewface (e.g. assoc status, IP addwesses, etc.)
 *	The @changed pawametew indicates which vawue changed.
 *	The cawwback can sweep.
 *
 * @wink_info_changed: Handwew fow configuwation wequests wewated to wink
 *	pawametews fwom &stwuct ieee80211_bss_conf that awe wewated to an
 *	individuaw wink. e.g. wegacy/HT/VHT/... wate infowmation.
 *	The @changed pawametew indicates which vawue changed, and the @wink_id
 *	pawametew indicates the wink ID. Note that the @wink_id wiww be 0 fow
 *	non-MWO connections.
 *	The cawwback can sweep.
 *
 * @pwepawe_muwticast: Pwepawe fow muwticast fiwtew configuwation.
 *	This cawwback is optionaw, and its wetuwn vawue is passed
 *	to configuwe_fiwtew(). This cawwback must be atomic.
 *
 * @configuwe_fiwtew: Configuwe the device's WX fiwtew.
 *	See the section "Fwame fiwtewing" fow mowe infowmation.
 *	This cawwback must be impwemented and can sweep.
 *
 * @config_iface_fiwtew: Configuwe the intewface's WX fiwtew.
 *	This cawwback is optionaw and is used to configuwe which fwames
 *	shouwd be passed to mac80211. The fiwtew_fwags is the combination
 *	of FIF_* fwags. The changed_fwags is a bit mask that indicates
 *	which fwags awe changed.
 *	This cawwback can sweep.
 *
 * @set_tim: Set TIM bit. mac80211 cawws this function when a TIM bit
 * 	must be set ow cweawed fow a given STA. Must be atomic.
 *
 * @set_key: See the section "Hawdwawe cwypto accewewation"
 *	This cawwback is onwy cawwed between add_intewface and
 *	wemove_intewface cawws, i.e. whiwe the given viwtuaw intewface
 *	is enabwed.
 *	Wetuwns a negative ewwow code if the key can't be added.
 *	The cawwback can sweep.
 *
 * @update_tkip_key: See the section "Hawdwawe cwypto accewewation"
 * 	This cawwback wiww be cawwed in the context of Wx. Cawwed fow dwivews
 * 	which set IEEE80211_KEY_FWAG_TKIP_WEQ_WX_P1_KEY.
 *	The cawwback must be atomic.
 *
 * @set_wekey_data: If the device suppowts GTK wekeying, fow exampwe whiwe the
 *	host is suspended, it can assign this cawwback to wetwieve the data
 *	necessawy to do GTK wekeying, this is the KEK, KCK and wepway countew.
 *	Aftew wekeying was done it shouwd (fow exampwe duwing wesume) notify
 *	usewspace of the new wepway countew using ieee80211_gtk_wekey_notify().
 *
 * @set_defauwt_unicast_key: Set the defauwt (unicast) key index, usefuw fow
 *	WEP when the device sends data packets autonomouswy, e.g. fow AWP
 *	offwoading. The index can be 0-3, ow -1 fow unsetting it.
 *
 * @hw_scan: Ask the hawdwawe to sewvice the scan wequest, no need to stawt
 *	the scan state machine in stack. The scan must honouw the channew
 *	configuwation done by the weguwatowy agent in the wiphy's
 *	wegistewed bands. The hawdwawe (ow the dwivew) needs to make suwe
 *	that powew save is disabwed.
 *	The @weq ie/ie_wen membews awe wewwitten by mac80211 to contain the
 *	entiwe IEs aftew the SSID, so that dwivews need not wook at these
 *	at aww but just send them aftew the SSID -- mac80211 incwudes the
 *	(extended) suppowted wates and HT infowmation (whewe appwicabwe).
 *	When the scan finishes, ieee80211_scan_compweted() must be cawwed;
 *	note that it awso must be cawwed when the scan cannot finish due to
 *	any ewwow unwess this cawwback wetuwned a negative ewwow code.
 *	This cawwback is awso awwowed to wetuwn the speciaw wetuwn vawue 1,
 *	this indicates that hawdwawe scan isn't desiwabwe wight now and a
 *	softwawe scan shouwd be done instead. A dwivew wishing to use this
 *	capabiwity must ensuwe its (hawdwawe) scan capabiwities awen't
 *	advewtised as mowe capabwe than mac80211's softwawe scan is.
 *	The cawwback can sweep.
 *
 * @cancew_hw_scan: Ask the wow-wevew tp cancew the active hw scan.
 *	The dwivew shouwd ask the hawdwawe to cancew the scan (if possibwe),
 *	but the scan wiww be compweted onwy aftew the dwivew wiww caww
 *	ieee80211_scan_compweted().
 *	This cawwback is needed fow wowwan, to pwevent enqueueing a new
 *	scan_wowk aftew the wow-wevew dwivew was awweady suspended.
 *	The cawwback can sweep.
 *
 * @sched_scan_stawt: Ask the hawdwawe to stawt scanning wepeatedwy at
 *	specific intewvaws.  The dwivew must caww the
 *	ieee80211_sched_scan_wesuwts() function whenevew it finds wesuwts.
 *	This pwocess wiww continue untiw sched_scan_stop is cawwed.
 *
 * @sched_scan_stop: Teww the hawdwawe to stop an ongoing scheduwed scan.
 *	In this case, ieee80211_sched_scan_stopped() must not be cawwed.
 *
 * @sw_scan_stawt: Notifiew function that is cawwed just befowe a softwawe scan
 *	is stawted. Can be NUWW, if the dwivew doesn't need this notification.
 *	The mac_addw pawametew awwows suppowting NW80211_SCAN_FWAG_WANDOM_ADDW,
 *	the dwivew may set the NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW fwag if it
 *	can use this pawametew. The cawwback can sweep.
 *
 * @sw_scan_compwete: Notifiew function that is cawwed just aftew a
 *	softwawe scan finished. Can be NUWW, if the dwivew doesn't need
 *	this notification.
 *	The cawwback can sweep.
 *
 * @get_stats: Wetuwn wow-wevew statistics.
 * 	Wetuwns zewo if statistics awe avaiwabwe.
 *	The cawwback can sweep.
 *
 * @get_key_seq: If youw device impwements encwyption in hawdwawe and does
 *	IV/PN assignment then this cawwback shouwd be pwovided to wead the
 *	IV/PN fow the given key fwom hawdwawe.
 *	The cawwback must be atomic.
 *
 * @set_fwag_thweshowd: Configuwation of fwagmentation thweshowd. Assign this
 *	if the device does fwagmentation by itsewf. Note that to pwevent the
 *	stack fwom doing fwagmentation IEEE80211_HW_SUPPOWTS_TX_FWAG
 *	shouwd be set as weww.
 *	The cawwback can sweep.
 *
 * @set_wts_thweshowd: Configuwation of WTS thweshowd (if device needs it)
 *	The cawwback can sweep.
 *
 * @sta_add: Notifies wow wevew dwivew about addition of an associated station,
 *	AP, IBSS/WDS/mesh peew etc. This cawwback can sweep.
 *
 * @sta_wemove: Notifies wow wevew dwivew about wemovaw of an associated
 *	station, AP, IBSS/WDS/mesh peew etc. Note that aftew the cawwback
 *	wetuwns it isn't safe to use the pointew, not even WCU pwotected;
 *	no WCU gwace pewiod is guawanteed between wetuwning hewe and fweeing
 *	the station. See @sta_pwe_wcu_wemove if needed.
 *	This cawwback can sweep.
 *
 * @vif_add_debugfs: Dwivews can use this cawwback to add a debugfs vif
 *	diwectowy with its fiwes. This cawwback shouwd be within a
 *	CONFIG_MAC80211_DEBUGFS conditionaw. This cawwback can sweep.
 *
 * @wink_add_debugfs: Dwivews can use this cawwback to add debugfs fiwes
 *	when a wink is added to a mac80211 vif. This cawwback shouwd be within
 *	a CONFIG_MAC80211_DEBUGFS conditionaw. This cawwback can sweep.
 *	Fow non-MWO the cawwback wiww be cawwed once fow the defauwt bss_conf
 *	with the vif's diwectowy wathew than a sepawate subdiwectowy.
 *
 * @sta_add_debugfs: Dwivews can use this cawwback to add debugfs fiwes
 *	when a station is added to mac80211's station wist. This cawwback
 *	shouwd be within a CONFIG_MAC80211_DEBUGFS conditionaw. This
 *	cawwback can sweep.
 *
 * @wink_sta_add_debugfs: Dwivews can use this cawwback to add debugfs fiwes
 *	when a wink is added to a mac80211 station. This cawwback
 *	shouwd be within a CONFIG_MAC80211_DEBUGFS conditionaw. This
 *	cawwback can sweep.
 *	Fow non-MWO the cawwback wiww be cawwed once fow the defwink with the
 *	station's diwectowy wathew than a sepawate subdiwectowy.
 *
 * @sta_notify: Notifies wow wevew dwivew about powew state twansition of an
 *	associated station, AP,  IBSS/WDS/mesh peew etc. Fow a VIF opewating
 *	in AP mode, this cawwback wiww not be cawwed when the fwag
 *	%IEEE80211_HW_AP_WINK_PS is set. Must be atomic.
 *
 * @sta_set_txpww: Configuwe the station tx powew. This cawwback set the tx
 *	powew fow the station.
 *	This cawwback can sweep.
 *
 * @sta_state: Notifies wow wevew dwivew about state twansition of a
 *	station (which can be the AP, a cwient, IBSS/WDS/mesh peew etc.)
 *	This cawwback is mutuawwy excwusive with @sta_add/@sta_wemove.
 *	It must not faiw fow down twansitions but may faiw fow twansitions
 *	up the wist of states. Awso note that aftew the cawwback wetuwns it
 *	isn't safe to use the pointew, not even WCU pwotected - no WCU gwace
 *	pewiod is guawanteed between wetuwning hewe and fweeing the station.
 *	See @sta_pwe_wcu_wemove if needed.
 *	The cawwback can sweep.
 *
 * @sta_pwe_wcu_wemove: Notify dwivew about station wemovaw befowe WCU
 *	synchwonisation. This is usefuw if a dwivew needs to have station
 *	pointews pwotected using WCU, it can then use this caww to cweaw
 *	the pointews instead of waiting fow an WCU gwace pewiod to ewapse
 *	in @sta_state.
 *	The cawwback can sweep.
 *
 * @sta_wc_update: Notifies the dwivew of changes to the bitwates that can be
 *	used to twansmit to the station. The changes awe advewtised with bits
 *	fwom &enum ieee80211_wate_contwow_changed and the vawues awe wefwected
 *	in the station data. This cawwback shouwd onwy be used when the dwivew
 *	uses hawdwawe wate contwow (%IEEE80211_HW_HAS_WATE_CONTWOW) since
 *	othewwise the wate contwow awgowithm is notified diwectwy.
 *	Must be atomic.
 * @sta_wate_tbw_update: Notifies the dwivew that the wate tabwe changed. This
 *	is onwy used if the configuwed wate contwow awgowithm actuawwy uses
 *	the new wate tabwe API, and is thewefowe optionaw. Must be atomic.
 *
 * @sta_statistics: Get statistics fow this station. Fow exampwe with beacon
 *	fiwtewing, the statistics kept by mac80211 might not be accuwate, so
 *	wet the dwivew pwe-fiww the statistics. The dwivew can fiww most of
 *	the vawues (indicating which by setting the fiwwed bitmap), but not
 *	aww of them make sense - see the souwce fow which ones awe possibwe.
 *	Statistics that the dwivew doesn't fiww wiww be fiwwed by mac80211.
 *	The cawwback can sweep.
 *
 * @conf_tx: Configuwe TX queue pawametews (EDCF (aifs, cw_min, cw_max),
 *	buwsting) fow a hawdwawe TX queue.
 *	Wetuwns a negative ewwow code on faiwuwe.
 *	The cawwback can sweep.
 *
 * @get_tsf: Get the cuwwent TSF timew vawue fwom fiwmwawe/hawdwawe. Cuwwentwy,
 *	this is onwy used fow IBSS mode BSSID mewging and debugging. Is not a
 *	wequiwed function.
 *	The cawwback can sweep.
 *
 * @set_tsf: Set the TSF timew to the specified vawue in the fiwmwawe/hawdwawe.
 *	Cuwwentwy, this is onwy used fow IBSS mode debugging. Is not a
 *	wequiwed function.
 *	The cawwback can sweep.
 *
 * @offset_tsf: Offset the TSF timew by the specified vawue in the
 *	fiwmwawe/hawdwawe.  Pwefewwed to set_tsf as it avoids deway between
 *	cawwing set_tsf() and hawdwawe getting pwogwammed, which wiww show up
 *	as TSF deway. Is not a wequiwed function.
 *	The cawwback can sweep.
 *
 * @weset_tsf: Weset the TSF timew and awwow fiwmwawe/hawdwawe to synchwonize
 *	with othew STAs in the IBSS. This is onwy used in IBSS mode. This
 *	function is optionaw if the fiwmwawe/hawdwawe takes fuww cawe of
 *	TSF synchwonization.
 *	The cawwback can sweep.
 *
 * @tx_wast_beacon: Detewmine whethew the wast IBSS beacon was sent by us.
 *	This is needed onwy fow IBSS mode and the wesuwt of this function is
 *	used to detewmine whethew to wepwy to Pwobe Wequests.
 *	Wetuwns non-zewo if this device sent the wast beacon.
 *	The cawwback can sweep.
 *
 * @get_suwvey: Wetuwn pew-channew suwvey infowmation
 *
 * @wfkiww_poww: Poww wfkiww hawdwawe state. If you need this, you awso
 *	need to set wiphy->wfkiww_poww to %twue befowe wegistwation,
 *	and need to caww wiphy_wfkiww_set_hw_state() in the cawwback.
 *	The cawwback can sweep.
 *
 * @set_covewage_cwass: Set swot time fow given covewage cwass as specified
 *	in IEEE 802.11-2007 section 17.3.8.6 and modify ACK timeout
 *	accowdingwy; covewage cwass equaws to -1 to enabwe ACK timeout
 *	estimation awgowithm (dynack). To disabwe dynack set vawid vawue fow
 *	covewage cwass. This cawwback is not wequiwed and may sweep.
 *
 * @testmode_cmd: Impwement a cfg80211 test mode command. The passed @vif may
 *	be %NUWW. The cawwback can sweep.
 * @testmode_dump: Impwement a cfg80211 test mode dump. The cawwback can sweep.
 *
 * @fwush: Fwush aww pending fwames fwom the hawdwawe queue, making suwe
 *	that the hawdwawe queues awe empty. The @queues pawametew is a bitmap
 *	of queues to fwush, which is usefuw if diffewent viwtuaw intewfaces
 *	use diffewent hawdwawe queues; it may awso indicate aww queues.
 *	If the pawametew @dwop is set to %twue, pending fwames may be dwopped.
 *	Note that vif can be NUWW.
 *	The cawwback can sweep.
 *
 * @fwush_sta: Fwush ow dwop aww pending fwames fwom the hawdwawe queue(s) fow
 *	the given station, as it's about to be wemoved.
 *	The cawwback can sweep.
 *
 * @channew_switch: Dwivews that need (ow want) to offwoad the channew
 *	switch opewation fow CSAs weceived fwom the AP may impwement this
 *	cawwback. They must then caww ieee80211_chswitch_done() to indicate
 *	compwetion of the channew switch.
 *
 * @set_antenna: Set antenna configuwation (tx_ant, wx_ant) on the device.
 *	Pawametews awe bitmaps of awwowed antennas to use fow TX/WX. Dwivews may
 *	weject TX/WX mask combinations they cannot suppowt by wetuwning -EINVAW
 *	(awso see nw80211.h @NW80211_ATTW_WIPHY_ANTENNA_TX).
 *
 * @get_antenna: Get cuwwent antenna configuwation fwom device (tx_ant, wx_ant).
 *
 * @wemain_on_channew: Stawts an off-channew pewiod on the given channew, must
 *	caww back to ieee80211_weady_on_channew() when on that channew. Note
 *	that nowmaw channew twaffic is not stopped as this is intended fow hw
 *	offwoad. Fwames to twansmit on the off-channew channew awe twansmitted
 *	nowmawwy except fow the %IEEE80211_TX_CTW_TX_OFFCHAN fwag. When the
 *	duwation (which wiww awways be non-zewo) expiwes, the dwivew must caww
 *	ieee80211_wemain_on_channew_expiwed().
 *	Note that this cawwback may be cawwed whiwe the device is in IDWE and
 *	must be accepted in this case.
 *	This cawwback may sweep.
 * @cancew_wemain_on_channew: Wequests that an ongoing off-channew pewiod is
 *	abowted befowe it expiwes. This cawwback may sweep.
 *
 * @set_wingpawam: Set tx and wx wing sizes.
 *
 * @get_wingpawam: Get tx and wx wing cuwwent and maximum sizes.
 *
 * @tx_fwames_pending: Check if thewe is any pending fwame in the hawdwawe
 *	queues befowe entewing powew save.
 *
 * @set_bitwate_mask: Set a mask of wates to be used fow wate contwow sewection
 *	when twansmitting a fwame. Cuwwentwy onwy wegacy wates awe handwed.
 *	The cawwback can sweep.
 * @event_cawwback: Notify dwivew about any event in mac80211. See
 *	&enum ieee80211_event_type fow the diffewent types.
 *	The cawwback must be atomic.
 *
 * @wewease_buffewed_fwames: Wewease buffewed fwames accowding to the given
 *	pawametews. In the case whewe the dwivew buffews some fwames fow
 *	sweeping stations mac80211 wiww use this cawwback to teww the dwivew
 *	to wewease some fwames, eithew fow PS-poww ow uAPSD.
 *	Note that if the @mowe_data pawametew is %fawse the dwivew must check
 *	if thewe awe mowe fwames on the given TIDs, and if thewe awe mowe than
 *	the fwames being weweased then it must stiww set the mowe-data bit in
 *	the fwame. If the @mowe_data pawametew is %twue, then of couwse the
 *	mowe-data bit must awways be set.
 *	The @tids pawametew tewws the dwivew which TIDs to wewease fwames
 *	fwom, fow PS-poww it wiww awways have onwy a singwe bit set.
 *	In the case this is used fow a PS-poww initiated wewease, the
 *	@num_fwames pawametew wiww awways be 1 so code can be shawed. In
 *	this case the dwivew must awso set %IEEE80211_TX_STATUS_EOSP fwag
 *	on the TX status (and must wepowt TX status) so that the PS-poww
 *	pewiod is pwopewwy ended. This is used to avoid sending muwtipwe
 *	wesponses fow a wetwied PS-poww fwame.
 *	In the case this is used fow uAPSD, the @num_fwames pawametew may be
 *	biggew than one, but the dwivew may send fewew fwames (it must send
 *	at weast one, howevew). In this case it is awso wesponsibwe fow
 *	setting the EOSP fwag in the QoS headew of the fwames. Awso, when the
 *	sewvice pewiod ends, the dwivew must set %IEEE80211_TX_STATUS_EOSP
 *	on the wast fwame in the SP. Awtewnativewy, it may caww the function
 *	ieee80211_sta_eosp() to infowm mac80211 of the end of the SP.
 *	This cawwback must be atomic.
 * @awwow_buffewed_fwames: Pwepawe device to awwow the given numbew of fwames
 *	to go out to the given station. The fwames wiww be sent by mac80211
 *	via the usuaw TX path aftew this caww. The TX infowmation fow fwames
 *	weweased wiww awso have the %IEEE80211_TX_CTW_NO_PS_BUFFEW fwag set
 *	and the wast one wiww awso have %IEEE80211_TX_STATUS_EOSP set. In case
 *	fwames fwom muwtipwe TIDs awe weweased and the dwivew might weowdew
 *	them between the TIDs, it must set the %IEEE80211_TX_STATUS_EOSP fwag
 *	on the wast fwame and cweaw it on aww othews and awso handwe the EOSP
 *	bit in the QoS headew cowwectwy. Awtewnativewy, it can awso caww the
 *	ieee80211_sta_eosp() function.
 *	The @tids pawametew is a bitmap and tewws the dwivew which TIDs the
 *	fwames wiww be on; it wiww at most have two bits set.
 *	This cawwback must be atomic.
 *
 * @get_et_sset_count:  Ethtoow API to get stwing-set count.
 *	Note that the wiphy mutex is not hewd fow this cawwback since it's
 *	expected to wetuwn a static vawue.
 *
 * @get_et_stats:  Ethtoow API to get a set of u64 stats.
 *
 * @get_et_stwings:  Ethtoow API to get a set of stwings to descwibe stats
 *	and pewhaps othew suppowted types of ethtoow data-sets.
 *	Note that the wiphy mutex is not hewd fow this cawwback since it's
 *	expected to wetuwn a static vawue.
 *
 * @mgd_pwepawe_tx: Pwepawe fow twansmitting a management fwame fow association
 *	befowe associated. In muwti-channew scenawios, a viwtuaw intewface is
 *	bound to a channew befowe it is associated, but as it isn't associated
 *	yet it need not necessawiwy be given aiwtime, in pawticuwaw since any
 *	twansmission to a P2P GO needs to be synchwonized against the GO's
 *	powewsave state. mac80211 wiww caww this function befowe twansmitting a
 *	management fwame pwiow to having successfuwwy associated to awwow the
 *	dwivew to give it channew time fow the twansmission, to get a wesponse
 *	and to be abwe to synchwonize with the GO.
 *	Fow dwivews that set %IEEE80211_HW_DEAUTH_NEED_MGD_TX_PWEP, mac80211
 *	wouwd awso caww this function befowe twansmitting a deauthentication
 *	fwame in case that no beacon was heawd fwom the AP/P2P GO.
 *	The cawwback wiww be cawwed befowe each twansmission and upon wetuwn
 *	mac80211 wiww twansmit the fwame wight away.
 *	Additionaw infowmation is passed in the &stwuct ieee80211_pwep_tx_info
 *	data. If duwation thewe is gweatew than zewo, mac80211 hints to the
 *	dwivew the duwation fow which the opewation is wequested.
 *	The cawwback is optionaw and can (shouwd!) sweep.
 * @mgd_compwete_tx: Notify the dwivew that the wesponse fwame fow a pweviouswy
 *	twansmitted fwame announced with @mgd_pwepawe_tx was weceived, the data
 *	is fiwwed simiwawwy to @mgd_pwepawe_tx though the duwation is not used.
 *
 * @mgd_pwotect_tdws_discovew: Pwotect a TDWS discovewy session. Aftew sending
 *	a TDWS discovewy-wequest, we expect a wepwy to awwive on the AP's
 *	channew. We must stay on the channew (no PSM, scan, etc.), since a TDWS
 *	setup-wesponse is a diwect packet not buffewed by the AP.
 *	mac80211 wiww caww this function just befowe the twansmission of a TDWS
 *	discovewy-wequest. The wecommended pewiod of pwotection is at weast
 *	2 * (DTIM pewiod).
 *	The cawwback is optionaw and can sweep.
 *
 * @add_chanctx: Notifies device dwivew about new channew context cweation.
 *	This cawwback may sweep.
 * @wemove_chanctx: Notifies device dwivew about channew context destwuction.
 *	This cawwback may sweep.
 * @change_chanctx: Notifies device dwivew about channew context changes that
 *	may happen when combining diffewent viwtuaw intewfaces on the same
 *	channew context with diffewent settings
 *	This cawwback may sweep.
 * @assign_vif_chanctx: Notifies device dwivew about channew context being bound
 *	to vif. Possibwe use is fow hw queue wemapping.
 *	This cawwback may sweep.
 * @unassign_vif_chanctx: Notifies device dwivew about channew context being
 *	unbound fwom vif.
 *	This cawwback may sweep.
 * @switch_vif_chanctx: switch a numbew of vifs fwom one chanctx to
 *	anothew, as specified in the wist of
 *	@ieee80211_vif_chanctx_switch passed to the dwivew, accowding
 *	to the mode defined in &ieee80211_chanctx_switch_mode.
 *	This cawwback may sweep.
 *
 * @stawt_ap: Stawt opewation on the AP intewface, this is cawwed aftew aww the
 *	infowmation in bss_conf is set and beacon can be wetwieved. A channew
 *	context is bound befowe this is cawwed. Note that if the dwivew uses
 *	softwawe scan ow WOC, this (and @stop_ap) isn't cawwed when the AP is
 *	just "paused" fow scanning/WOC, which is indicated by the beacon being
 *	disabwed/enabwed via @bss_info_changed.
 * @stop_ap: Stop opewation on the AP intewface.
 *
 * @weconfig_compwete: Cawwed aftew a caww to ieee80211_westawt_hw() and
 *	duwing wesume, when the weconfiguwation has compweted.
 *	This can hewp the dwivew impwement the weconfiguwation step (and
 *	indicate mac80211 is weady to weceive fwames).
 *	This cawwback may sweep.
 *
 * @ipv6_addw_change: IPv6 addwess assignment on the given intewface changed.
 *	Cuwwentwy, this is onwy cawwed fow managed ow P2P cwient intewfaces.
 *	This cawwback is optionaw; it must not sweep.
 *
 * @channew_switch_beacon: Stawts a channew switch to a new channew.
 *	Beacons awe modified to incwude CSA ow ECSA IEs befowe cawwing this
 *	function. The cowwesponding count fiewds in these IEs must be
 *	decwemented, and when they weach 1 the dwivew must caww
 *	ieee80211_csa_finish(). Dwivews which use ieee80211_beacon_get()
 *	get the csa countew decwemented by mac80211, but must check if it is
 *	1 using ieee80211_beacon_countew_is_compwete() aftew the beacon has been
 *	twansmitted and then caww ieee80211_csa_finish().
 *	If the CSA count stawts as zewo ow 1, this function wiww not be cawwed,
 *	since thewe won't be any time to beacon befowe the switch anyway.
 * @pwe_channew_switch: This is an optionaw cawwback that is cawwed
 *	befowe a channew switch pwoceduwe is stawted (ie. when a STA
 *	gets a CSA ow a usewspace initiated channew-switch), awwowing
 *	the dwivew to pwepawe fow the channew switch.
 * @post_channew_switch: This is an optionaw cawwback that is cawwed
 *	aftew a channew switch pwoceduwe is compweted, awwowing the
 *	dwivew to go back to a nowmaw configuwation.
 * @abowt_channew_switch: This is an optionaw cawwback that is cawwed
 *	when channew switch pwoceduwe was compweted, awwowing the
 *	dwivew to go back to a nowmaw configuwation.
 * @channew_switch_wx_beacon: This is an optionaw cawwback that is cawwed
 *	when channew switch pwoceduwe is in pwogwess and additionaw beacon with
 *	CSA IE was weceived, awwowing dwivew to twack changes in count.
 * @join_ibss: Join an IBSS (on an IBSS intewface); this is cawwed aftew aww
 *	infowmation in bss_conf is set up and the beacon can be wetwieved. A
 *	channew context is bound befowe this is cawwed.
 * @weave_ibss: Weave the IBSS again.
 *
 * @get_expected_thwoughput: extwact the expected thwoughput towawds the
 *	specified station. The wetuwned vawue is expwessed in Kbps. It wetuwns 0
 *	if the WC awgowithm does not have pwopew data to pwovide.
 *
 * @get_txpowew: get cuwwent maximum tx powew (in dBm) based on configuwation
 *	and hawdwawe wimits.
 *
 * @tdws_channew_switch: Stawt channew-switching with a TDWS peew. The dwivew
 *	is wesponsibwe fow continuawwy initiating channew-switching opewations
 *	and wetuwning to the base channew fow communication with the AP. The
 *	dwivew weceives a channew-switch wequest tempwate and the wocation of
 *	the switch-timing IE within the tempwate as pawt of the invocation.
 *	The tempwate is vawid onwy within the caww, and the dwivew can
 *	optionawwy copy the skb fow fuwthew we-use.
 * @tdws_cancew_channew_switch: Stop channew-switching with a TDWS peew. Both
 *	peews must be on the base channew when the caww compwetes.
 * @tdws_wecv_channew_switch: a TDWS channew-switch wewated fwame (wequest ow
 *	wesponse) has been weceived fwom a wemote peew. The dwivew gets
 *	pawametews pawsed fwom the incoming fwame and may use them to continue
 *	an ongoing channew-switch opewation. In addition, a channew-switch
 *	wesponse tempwate is pwovided, togethew with the wocation of the
 *	switch-timing IE within the tempwate. The skb can onwy be used within
 *	the function caww.
 *
 * @wake_tx_queue: Cawwed when new packets have been added to the queue.
 * @sync_wx_queues: Pwocess aww pending fwames in WSS queues. This is a
 *	synchwonization which is needed in case dwivew has in its WSS queues
 *	pending fwames that wewe weceived pwiow to the contwow path action
 *	cuwwentwy taken (e.g. disassociation) but awe not pwocessed yet.
 *
 * @stawt_nan: join an existing NAN cwustew, ow cweate a new one.
 * @stop_nan: weave the NAN cwustew.
 * @nan_change_conf: change NAN configuwation. The data in cfg80211_nan_conf
 *	contains fuww new configuwation and changes specify which pawametews
 *	awe changed with wespect to the wast NAN config.
 *	The dwivew gets both fuww configuwation and the changed pawametews since
 *	some devices may need the fuww configuwation whiwe othews need onwy the
 *	changed pawametews.
 * @add_nan_func: Add a NAN function. Wetuwns 0 on success. The data in
 *	cfg80211_nan_func must not be wefewenced outside the scope of
 *	this caww.
 * @dew_nan_func: Wemove a NAN function. The dwivew must caww
 *	ieee80211_nan_func_tewminated() with
 *	NW80211_NAN_FUNC_TEWM_WEASON_USEW_WEQUEST weason code upon wemovaw.
 * @can_aggwegate_in_amsdu: Cawwed in owdew to detewmine if HW suppowts
 *	aggwegating two specific fwames in the same A-MSDU. The wewation
 *	between the skbs shouwd be symmetwic and twansitive. Note that whiwe
 *	skb is awways a weaw fwame, head may ow may not be an A-MSDU.
 * @get_ftm_wespondew_stats: Wetwieve FTM wespondew statistics, if avaiwabwe.
 *	Statistics shouwd be cumuwative, cuwwentwy no way to weset is pwovided.
 *
 * @stawt_pmsw: stawt peew measuwement (e.g. FTM) (this caww can sweep)
 * @abowt_pmsw: abowt peew measuwement (this caww can sweep)
 * @set_tid_config: Appwy TID specific configuwations. This cawwback may sweep.
 * @weset_tid_config: Weset TID specific configuwation fow the peew.
 *	This cawwback may sweep.
 * @update_vif_offwoad: Update viwtuaw intewface offwoad fwags
 *	This cawwback may sweep.
 * @sta_set_4addw: Cawwed to notify the dwivew when a station stawts/stops using
 *	4-addwess mode
 * @set_saw_specs: Update the SAW (TX powew) settings.
 * @sta_set_decap_offwoad: Cawwed to notify the dwivew when a station is awwowed
 *	to use wx decapsuwation offwoad
 * @add_twt_setup: Update hw with TWT agweement pawametews weceived fwom the peew.
 *	This cawwback awwows the hw to check if wequested pawametews
 *	awe suppowted and if thewe is enough woom fow a new agweement.
 *	The hw is expected to set agweement wesuwt in the weq_type fiewd of
 *	twt stwuctuwe.
 * @twt_teawdown_wequest: Update the hw with TWT teawdown wequest weceived
 *	fwom the peew.
 * @set_wadaw_backgwound: Configuwe dedicated offchannew chain avaiwabwe fow
 *	wadaw/CAC detection on some hw. This chain can't be used to twansmit
 *	ow weceive fwames and it is bounded to a wunning wdev.
 *	Backgwound wadaw/CAC detection awwows to avoid the CAC downtime
 *	switching to a diffewent channew duwing CAC detection on the sewected
 *	wadaw channew.
 *	The cawwew is expected to set chandef pointew to NUWW in owdew to
 *	disabwe backgwound CAC/wadaw detection.
 * @net_fiww_fowwawd_path: Cawwed fwom .ndo_fiww_fowwawd_path in owdew to
 *	wesowve a path fow hawdwawe fwow offwoading
 * @can_activate_winks: Checks if a specific active_winks bitmap is
 *	suppowted by the dwivew.
 * @change_vif_winks: Change the vawid winks on an intewface, note that whiwe
 *	wemoving the owd wink infowmation is stiww vawid (wink_conf pointew),
 *	but may immediatewy disappeaw aftew the function wetuwns. The owd ow
 *	new winks bitmaps may be 0 if going fwom/to a non-MWO situation.
 *	The @owd awway contains pointews to the owd bss_conf stwuctuwes
 *	that wewe awweady wemoved, in case they'we needed.
 *	This cawwback can sweep.
 * @change_sta_winks: Change the vawid winks of a station, simiwaw to
 *	@change_vif_winks. This cawwback can sweep.
 *	Note that a sta can awso be insewted ow wemoved with vawid winks,
 *	i.e. passed to @sta_add/@sta_state with sta->vawid_winks not zewo.
 *	In fact, cannot change fwom having vawid_winks and not having them.
 * @set_hw_timestamp: Enabwe/disabwe HW timestamping of TM/FTM fwames. This is
 *	not westowed at HW weset by mac80211 so dwivews need to take cawe of
 *	that.
 * @net_setup_tc: Cawwed fwom .ndo_setup_tc in owdew to pwepawe hawdwawe
 *	fwow offwoading fow fwows owiginating fwom the vif.
 *	Note that the dwivew must not assume that the vif dwivew_data is vawid
 *	at this point, since the cawwback can be cawwed duwing netdev teawdown.
 */
stwuct ieee80211_ops {
	void (*tx)(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_tx_contwow *contwow,
		   stwuct sk_buff *skb);
	int (*stawt)(stwuct ieee80211_hw *hw);
	void (*stop)(stwuct ieee80211_hw *hw);
#ifdef CONFIG_PM
	int (*suspend)(stwuct ieee80211_hw *hw, stwuct cfg80211_wowwan *wowwan);
	int (*wesume)(stwuct ieee80211_hw *hw);
	void (*set_wakeup)(stwuct ieee80211_hw *hw, boow enabwed);
#endif
	int (*add_intewface)(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif);
	int (*change_intewface)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				enum nw80211_iftype new_type, boow p2p);
	void (*wemove_intewface)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif);
	int (*config)(stwuct ieee80211_hw *hw, u32 changed);
	void (*bss_info_changed)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *info,
				 u64 changed);
	void (*vif_cfg_changed)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				u64 changed);
	void (*wink_info_changed)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_bss_conf *info,
				  u64 changed);

	int (*stawt_ap)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_bss_conf *wink_conf);
	void (*stop_ap)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_bss_conf *wink_conf);

	u64 (*pwepawe_muwticast)(stwuct ieee80211_hw *hw,
				 stwuct netdev_hw_addw_wist *mc_wist);
	void (*configuwe_fiwtew)(stwuct ieee80211_hw *hw,
				 unsigned int changed_fwags,
				 unsigned int *totaw_fwags,
				 u64 muwticast);
	void (*config_iface_fiwtew)(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    unsigned int fiwtew_fwags,
				    unsigned int changed_fwags);
	int (*set_tim)(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		       boow set);
	int (*set_key)(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key);
	void (*update_tkip_key)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_key_conf *conf,
				stwuct ieee80211_sta *sta,
				u32 iv32, u16 *phase1key);
	void (*set_wekey_data)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct cfg80211_gtk_wekey_data *data);
	void (*set_defauwt_unicast_key)(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif, int idx);
	int (*hw_scan)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_scan_wequest *weq);
	void (*cancew_hw_scan)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif);
	int (*sched_scan_stawt)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct cfg80211_sched_scan_wequest *weq,
				stwuct ieee80211_scan_ies *ies);
	int (*sched_scan_stop)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif);
	void (*sw_scan_stawt)(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      const u8 *mac_addw);
	void (*sw_scan_compwete)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif);
	int (*get_stats)(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_wow_wevew_stats *stats);
	void (*get_key_seq)(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_key_conf *key,
			    stwuct ieee80211_key_seq *seq);
	int (*set_fwag_thweshowd)(stwuct ieee80211_hw *hw, u32 vawue);
	int (*set_wts_thweshowd)(stwuct ieee80211_hw *hw, u32 vawue);
	int (*sta_add)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
	int (*sta_wemove)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta);
#ifdef CONFIG_MAC80211_DEBUGFS
	void (*vif_add_debugfs)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif);
	void (*wink_add_debugfs)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *wink_conf,
				 stwuct dentwy *diw);
	void (*sta_add_debugfs)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				stwuct dentwy *diw);
	void (*wink_sta_add_debugfs)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_wink_sta *wink_sta,
				     stwuct dentwy *diw);
#endif
	void (*sta_notify)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			enum sta_notify_cmd, stwuct ieee80211_sta *sta);
	int (*sta_set_txpww)(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta);
	int (*sta_state)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta,
			 enum ieee80211_sta_state owd_state,
			 enum ieee80211_sta_state new_state);
	void (*sta_pwe_wcu_wemove)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta);
	void (*sta_wc_update)(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta,
			      u32 changed);
	void (*sta_wate_tbw_update)(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_sta *sta);
	void (*sta_statistics)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta,
			       stwuct station_info *sinfo);
	int (*conf_tx)(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_vif *vif,
		       unsigned int wink_id, u16 ac,
		       const stwuct ieee80211_tx_queue_pawams *pawams);
	u64 (*get_tsf)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
	void (*set_tsf)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			u64 tsf);
	void (*offset_tsf)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   s64 offset);
	void (*weset_tsf)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
	int (*tx_wast_beacon)(stwuct ieee80211_hw *hw);

	/**
	 * @ampdu_action:
	 * Pewfowm a cewtain A-MPDU action.
	 * The WA/TID combination detewmines the destination and TID we want
	 * the ampdu action to be pewfowmed fow. The action is defined thwough
	 * ieee80211_ampdu_mwme_action.
	 * When the action is set to %IEEE80211_AMPDU_TX_OPEWATIONAW the dwivew
	 * may neithew send aggwegates containing mowe subfwames than @buf_size
	 * now send aggwegates in a way that wost fwames wouwd exceed the
	 * buffew size. If just wimiting the aggwegate size, this wouwd be
	 * possibwe with a buf_size of 8:
	 *
	 * - ``TX: 1.....7``
	 * - ``WX:  2....7`` (wost fwame #1)
	 * - ``TX:        8..1...``
	 *
	 * which is invawid since #1 was now we-twansmitted weww past the
	 * buffew size of 8. Cowwect ways to wetwansmit #1 wouwd be:
	 *
	 * - ``TX:        1   ow``
	 * - ``TX:        18  ow``
	 * - ``TX:        81``
	 *
	 * Even ``189`` wouwd be wwong since 1 couwd be wost again.
	 *
	 * Wetuwns a negative ewwow code on faiwuwe. The dwivew may wetuwn
	 * %IEEE80211_AMPDU_TX_STAWT_IMMEDIATE fow %IEEE80211_AMPDU_TX_STAWT
	 * if the session can stawt immediatewy.
	 *
	 * The cawwback can sweep.
	 */
	int (*ampdu_action)(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_ampdu_pawams *pawams);
	int (*get_suwvey)(stwuct ieee80211_hw *hw, int idx,
		stwuct suwvey_info *suwvey);
	void (*wfkiww_poww)(stwuct ieee80211_hw *hw);
	void (*set_covewage_cwass)(stwuct ieee80211_hw *hw, s16 covewage_cwass);
#ifdef CONFIG_NW80211_TESTMODE
	int (*testmode_cmd)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    void *data, int wen);
	int (*testmode_dump)(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     void *data, int wen);
#endif
	void (*fwush)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      u32 queues, boow dwop);
	void (*fwush_sta)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta);
	void (*channew_switch)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_channew_switch *ch_switch);
	int (*set_antenna)(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant);
	int (*get_antenna)(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant);

	int (*wemain_on_channew)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_channew *chan,
				 int duwation,
				 enum ieee80211_woc_type type);
	int (*cancew_wemain_on_channew)(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif);
	int (*set_wingpawam)(stwuct ieee80211_hw *hw, u32 tx, u32 wx);
	void (*get_wingpawam)(stwuct ieee80211_hw *hw,
			      u32 *tx, u32 *tx_max, u32 *wx, u32 *wx_max);
	boow (*tx_fwames_pending)(stwuct ieee80211_hw *hw);
	int (*set_bitwate_mask)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
				const stwuct cfg80211_bitwate_mask *mask);
	void (*event_cawwback)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       const stwuct ieee80211_event *event);

	void (*awwow_buffewed_fwames)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_sta *sta,
				      u16 tids, int num_fwames,
				      enum ieee80211_fwame_wewease_type weason,
				      boow mowe_data);
	void (*wewease_buffewed_fwames)(stwuct ieee80211_hw *hw,
					stwuct ieee80211_sta *sta,
					u16 tids, int num_fwames,
					enum ieee80211_fwame_wewease_type weason,
					boow mowe_data);

	int	(*get_et_sset_count)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif, int sset);
	void	(*get_et_stats)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ethtoow_stats *stats, u64 *data);
	void	(*get_et_stwings)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  u32 sset, u8 *data);

	void	(*mgd_pwepawe_tx)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_pwep_tx_info *info);
	void	(*mgd_compwete_tx)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_pwep_tx_info *info);

	void	(*mgd_pwotect_tdws_discovew)(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_vif *vif,
					     unsigned int wink_id);

	int (*add_chanctx)(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_chanctx_conf *ctx);
	void (*wemove_chanctx)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_chanctx_conf *ctx);
	void (*change_chanctx)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_chanctx_conf *ctx,
			       u32 changed);
	int (*assign_vif_chanctx)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_bss_conf *wink_conf,
				  stwuct ieee80211_chanctx_conf *ctx);
	void (*unassign_vif_chanctx)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *wink_conf,
				     stwuct ieee80211_chanctx_conf *ctx);
	int (*switch_vif_chanctx)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif_chanctx_switch *vifs,
				  int n_vifs,
				  enum ieee80211_chanctx_switch_mode mode);

	void (*weconfig_compwete)(stwuct ieee80211_hw *hw,
				  enum ieee80211_weconfig_type weconfig_type);

#if IS_ENABWED(CONFIG_IPV6)
	void (*ipv6_addw_change)(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct inet6_dev *idev);
#endif
	void (*channew_switch_beacon)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct cfg80211_chan_def *chandef);
	int (*pwe_channew_switch)(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_channew_switch *ch_switch);

	int (*post_channew_switch)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_bss_conf *wink_conf);
	void (*abowt_channew_switch)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif);
	void (*channew_switch_wx_beacon)(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_channew_switch *ch_switch);

	int (*join_ibss)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
	void (*weave_ibss)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
	u32 (*get_expected_thwoughput)(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_sta *sta);
	int (*get_txpowew)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   int *dbm);

	int (*tdws_channew_switch)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta, u8 opew_cwass,
				   stwuct cfg80211_chan_def *chandef,
				   stwuct sk_buff *tmpw_skb, u32 ch_sw_tm_ie);
	void (*tdws_cancew_channew_switch)(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_sta *sta);
	void (*tdws_wecv_channew_switch)(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_tdws_ch_sw_pawams *pawams);

	void (*wake_tx_queue)(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_txq *txq);
	void (*sync_wx_queues)(stwuct ieee80211_hw *hw);

	int (*stawt_nan)(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 stwuct cfg80211_nan_conf *conf);
	int (*stop_nan)(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif);
	int (*nan_change_conf)(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct cfg80211_nan_conf *conf, u32 changes);
	int (*add_nan_func)(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    const stwuct cfg80211_nan_func *nan_func);
	void (*dew_nan_func)(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    u8 instance_id);
	boow (*can_aggwegate_in_amsdu)(stwuct ieee80211_hw *hw,
				       stwuct sk_buff *head,
				       stwuct sk_buff *skb);
	int (*get_ftm_wespondew_stats)(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct cfg80211_ftm_wespondew_stats *ftm_stats);
	int (*stawt_pmsw)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct cfg80211_pmsw_wequest *wequest);
	void (*abowt_pmsw)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct cfg80211_pmsw_wequest *wequest);
	int (*set_tid_config)(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta,
			      stwuct cfg80211_tid_config *tid_conf);
	int (*weset_tid_config)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta, u8 tids);
	void (*update_vif_offwoad)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif);
	void (*sta_set_4addw)(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta, boow enabwed);
	int (*set_saw_specs)(stwuct ieee80211_hw *hw,
			     const stwuct cfg80211_saw_specs *saw);
	void (*sta_set_decap_offwoad)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta, boow enabwed);
	void (*add_twt_setup)(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *sta,
			      stwuct ieee80211_twt_setup *twt);
	void (*twt_teawdown_wequest)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_sta *sta, u8 fwowid);
	int (*set_wadaw_backgwound)(stwuct ieee80211_hw *hw,
				    stwuct cfg80211_chan_def *chandef);
	int (*net_fiww_fowwawd_path)(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     stwuct net_device_path_ctx *ctx,
				     stwuct net_device_path *path);
	boow (*can_activate_winks)(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   u16 active_winks);
	int (*change_vif_winks)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				u16 owd_winks, u16 new_winks,
				stwuct ieee80211_bss_conf *owd[IEEE80211_MWD_MAX_NUM_WINKS]);
	int (*change_sta_winks)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				u16 owd_winks, u16 new_winks);
	int (*set_hw_timestamp)(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct cfg80211_set_hw_timestamp *hwts);
	int (*net_setup_tc)(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct net_device *dev,
			    enum tc_setup_type type,
			    void *type_data);
};

/**
 * ieee80211_awwoc_hw_nm - Awwocate a new hawdwawe device
 *
 * This must be cawwed once fow each hawdwawe device. The wetuwned pointew
 * must be used to wefew to this device when cawwing othew functions.
 * mac80211 awwocates a pwivate data awea fow the dwivew pointed to by
 * @pwiv in &stwuct ieee80211_hw, the size of this awea is given as
 * @pwiv_data_wen.
 *
 * @pwiv_data_wen: wength of pwivate data
 * @ops: cawwbacks fow this device
 * @wequested_name: Wequested name fow this device.
 *	NUWW is vawid vawue, and means use the defauwt naming (phy%d)
 *
 * Wetuwn: A pointew to the new hawdwawe device, ow %NUWW on ewwow.
 */
stwuct ieee80211_hw *ieee80211_awwoc_hw_nm(size_t pwiv_data_wen,
					   const stwuct ieee80211_ops *ops,
					   const chaw *wequested_name);

/**
 * ieee80211_awwoc_hw - Awwocate a new hawdwawe device
 *
 * This must be cawwed once fow each hawdwawe device. The wetuwned pointew
 * must be used to wefew to this device when cawwing othew functions.
 * mac80211 awwocates a pwivate data awea fow the dwivew pointed to by
 * @pwiv in &stwuct ieee80211_hw, the size of this awea is given as
 * @pwiv_data_wen.
 *
 * @pwiv_data_wen: wength of pwivate data
 * @ops: cawwbacks fow this device
 *
 * Wetuwn: A pointew to the new hawdwawe device, ow %NUWW on ewwow.
 */
static inwine
stwuct ieee80211_hw *ieee80211_awwoc_hw(size_t pwiv_data_wen,
					const stwuct ieee80211_ops *ops)
{
	wetuwn ieee80211_awwoc_hw_nm(pwiv_data_wen, ops, NUWW);
}

/**
 * ieee80211_wegistew_hw - Wegistew hawdwawe device
 *
 * You must caww this function befowe any othew functions in
 * mac80211. Note that befowe a hawdwawe can be wegistewed, you
 * need to fiww the contained wiphy's infowmation.
 *
 * @hw: the device to wegistew as wetuwned by ieee80211_awwoc_hw()
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
int ieee80211_wegistew_hw(stwuct ieee80211_hw *hw);

/**
 * stwuct ieee80211_tpt_bwink - thwoughput bwink descwiption
 * @thwoughput: thwoughput in Kbit/sec
 * @bwink_time: bwink time in miwwiseconds
 *	(fuww cycwe, ie. one off + one on pewiod)
 */
stwuct ieee80211_tpt_bwink {
	int thwoughput;
	int bwink_time;
};

/**
 * enum ieee80211_tpt_wed_twiggew_fwags - thwoughput twiggew fwags
 * @IEEE80211_TPT_WEDTWIG_FW_WADIO: enabwe bwinking with wadio
 * @IEEE80211_TPT_WEDTWIG_FW_WOWK: enabwe bwinking when wowking
 * @IEEE80211_TPT_WEDTWIG_FW_CONNECTED: enabwe bwinking when at weast one
 *	intewface is connected in some way, incwuding being an AP
 */
enum ieee80211_tpt_wed_twiggew_fwags {
	IEEE80211_TPT_WEDTWIG_FW_WADIO		= BIT(0),
	IEEE80211_TPT_WEDTWIG_FW_WOWK		= BIT(1),
	IEEE80211_TPT_WEDTWIG_FW_CONNECTED	= BIT(2),
};

#ifdef CONFIG_MAC80211_WEDS
const chaw *__ieee80211_get_tx_wed_name(stwuct ieee80211_hw *hw);
const chaw *__ieee80211_get_wx_wed_name(stwuct ieee80211_hw *hw);
const chaw *__ieee80211_get_assoc_wed_name(stwuct ieee80211_hw *hw);
const chaw *__ieee80211_get_wadio_wed_name(stwuct ieee80211_hw *hw);
const chaw *
__ieee80211_cweate_tpt_wed_twiggew(stwuct ieee80211_hw *hw,
				   unsigned int fwags,
				   const stwuct ieee80211_tpt_bwink *bwink_tabwe,
				   unsigned int bwink_tabwe_wen);
#endif
/**
 * ieee80211_get_tx_wed_name - get name of TX WED
 *
 * mac80211 cweates a twansmit WED twiggew fow each wiwewess hawdwawe
 * that can be used to dwive WEDs if youw dwivew wegistews a WED device.
 * This function wetuwns the name (ow %NUWW if not configuwed fow WEDs)
 * of the twiggew so you can automaticawwy wink the WED device.
 *
 * @hw: the hawdwawe to get the WED twiggew name fow
 *
 * Wetuwn: The name of the WED twiggew. %NUWW if not configuwed fow WEDs.
 */
static inwine const chaw *ieee80211_get_tx_wed_name(stwuct ieee80211_hw *hw)
{
#ifdef CONFIG_MAC80211_WEDS
	wetuwn __ieee80211_get_tx_wed_name(hw);
#ewse
	wetuwn NUWW;
#endif
}

/**
 * ieee80211_get_wx_wed_name - get name of WX WED
 *
 * mac80211 cweates a weceive WED twiggew fow each wiwewess hawdwawe
 * that can be used to dwive WEDs if youw dwivew wegistews a WED device.
 * This function wetuwns the name (ow %NUWW if not configuwed fow WEDs)
 * of the twiggew so you can automaticawwy wink the WED device.
 *
 * @hw: the hawdwawe to get the WED twiggew name fow
 *
 * Wetuwn: The name of the WED twiggew. %NUWW if not configuwed fow WEDs.
 */
static inwine const chaw *ieee80211_get_wx_wed_name(stwuct ieee80211_hw *hw)
{
#ifdef CONFIG_MAC80211_WEDS
	wetuwn __ieee80211_get_wx_wed_name(hw);
#ewse
	wetuwn NUWW;
#endif
}

/**
 * ieee80211_get_assoc_wed_name - get name of association WED
 *
 * mac80211 cweates a association WED twiggew fow each wiwewess hawdwawe
 * that can be used to dwive WEDs if youw dwivew wegistews a WED device.
 * This function wetuwns the name (ow %NUWW if not configuwed fow WEDs)
 * of the twiggew so you can automaticawwy wink the WED device.
 *
 * @hw: the hawdwawe to get the WED twiggew name fow
 *
 * Wetuwn: The name of the WED twiggew. %NUWW if not configuwed fow WEDs.
 */
static inwine const chaw *ieee80211_get_assoc_wed_name(stwuct ieee80211_hw *hw)
{
#ifdef CONFIG_MAC80211_WEDS
	wetuwn __ieee80211_get_assoc_wed_name(hw);
#ewse
	wetuwn NUWW;
#endif
}

/**
 * ieee80211_get_wadio_wed_name - get name of wadio WED
 *
 * mac80211 cweates a wadio change WED twiggew fow each wiwewess hawdwawe
 * that can be used to dwive WEDs if youw dwivew wegistews a WED device.
 * This function wetuwns the name (ow %NUWW if not configuwed fow WEDs)
 * of the twiggew so you can automaticawwy wink the WED device.
 *
 * @hw: the hawdwawe to get the WED twiggew name fow
 *
 * Wetuwn: The name of the WED twiggew. %NUWW if not configuwed fow WEDs.
 */
static inwine const chaw *ieee80211_get_wadio_wed_name(stwuct ieee80211_hw *hw)
{
#ifdef CONFIG_MAC80211_WEDS
	wetuwn __ieee80211_get_wadio_wed_name(hw);
#ewse
	wetuwn NUWW;
#endif
}

/**
 * ieee80211_cweate_tpt_wed_twiggew - cweate thwoughput WED twiggew
 * @hw: the hawdwawe to cweate the twiggew fow
 * @fwags: twiggew fwags, see &enum ieee80211_tpt_wed_twiggew_fwags
 * @bwink_tabwe: the bwink tabwe -- needs to be owdewed by thwoughput
 * @bwink_tabwe_wen: size of the bwink tabwe
 *
 * Wetuwn: %NUWW (in case of ewwow, ow if no WED twiggews awe
 * configuwed) ow the name of the new twiggew.
 *
 * Note: This function must be cawwed befowe ieee80211_wegistew_hw().
 */
static inwine const chaw *
ieee80211_cweate_tpt_wed_twiggew(stwuct ieee80211_hw *hw, unsigned int fwags,
				 const stwuct ieee80211_tpt_bwink *bwink_tabwe,
				 unsigned int bwink_tabwe_wen)
{
#ifdef CONFIG_MAC80211_WEDS
	wetuwn __ieee80211_cweate_tpt_wed_twiggew(hw, fwags, bwink_tabwe,
						  bwink_tabwe_wen);
#ewse
	wetuwn NUWW;
#endif
}

/**
 * ieee80211_unwegistew_hw - Unwegistew a hawdwawe device
 *
 * This function instwucts mac80211 to fwee awwocated wesouwces
 * and unwegistew netdevices fwom the netwowking subsystem.
 *
 * @hw: the hawdwawe to unwegistew
 */
void ieee80211_unwegistew_hw(stwuct ieee80211_hw *hw);

/**
 * ieee80211_fwee_hw - fwee hawdwawe descwiptow
 *
 * This function fwees evewything that was awwocated, incwuding the
 * pwivate data fow the dwivew. You must caww ieee80211_unwegistew_hw()
 * befowe cawwing this function.
 *
 * @hw: the hawdwawe to fwee
 */
void ieee80211_fwee_hw(stwuct ieee80211_hw *hw);

/**
 * ieee80211_westawt_hw - westawt hawdwawe compwetewy
 *
 * Caww this function when the hawdwawe was westawted fow some weason
 * (hawdwawe ewwow, ...) and the dwivew is unabwe to westowe its state
 * by itsewf. mac80211 assumes that at this point the dwivew/hawdwawe
 * is compwetewy uninitiawised and stopped, it stawts the pwocess by
 * cawwing the ->stawt() opewation. The dwivew wiww need to weset aww
 * intewnaw state that it has pwiow to cawwing this function.
 *
 * @hw: the hawdwawe to westawt
 */
void ieee80211_westawt_hw(stwuct ieee80211_hw *hw);

/**
 * ieee80211_wx_wist - weceive fwame and stowe pwocessed skbs in a wist
 *
 * Use this function to hand weceived fwames to mac80211. The weceive
 * buffew in @skb must stawt with an IEEE 802.11 headew. In case of a
 * paged @skb is used, the dwivew is wecommended to put the ieee80211
 * headew of the fwame on the wineaw pawt of the @skb to avoid memowy
 * awwocation and/ow memcpy by the stack.
 *
 * This function may not be cawwed in IWQ context. Cawws to this function
 * fow a singwe hawdwawe must be synchwonized against each othew. Cawws to
 * this function, ieee80211_wx_ni() and ieee80211_wx_iwqsafe() may not be
 * mixed fow a singwe hawdwawe. Must not wun concuwwentwy with
 * ieee80211_tx_status_skb() ow ieee80211_tx_status_ni().
 *
 * This function must be cawwed with BHs disabwed and WCU wead wock
 *
 * @hw: the hawdwawe this fwame came in on
 * @sta: the station the fwame was weceived fwom, ow %NUWW
 * @skb: the buffew to weceive, owned by mac80211 aftew this caww
 * @wist: the destination wist
 */
void ieee80211_wx_wist(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		       stwuct sk_buff *skb, stwuct wist_head *wist);

/**
 * ieee80211_wx_napi - weceive fwame fwom NAPI context
 *
 * Use this function to hand weceived fwames to mac80211. The weceive
 * buffew in @skb must stawt with an IEEE 802.11 headew. In case of a
 * paged @skb is used, the dwivew is wecommended to put the ieee80211
 * headew of the fwame on the wineaw pawt of the @skb to avoid memowy
 * awwocation and/ow memcpy by the stack.
 *
 * This function may not be cawwed in IWQ context. Cawws to this function
 * fow a singwe hawdwawe must be synchwonized against each othew. Cawws to
 * this function, ieee80211_wx_ni() and ieee80211_wx_iwqsafe() may not be
 * mixed fow a singwe hawdwawe. Must not wun concuwwentwy with
 * ieee80211_tx_status_skb() ow ieee80211_tx_status_ni().
 *
 * This function must be cawwed with BHs disabwed.
 *
 * @hw: the hawdwawe this fwame came in on
 * @sta: the station the fwame was weceived fwom, ow %NUWW
 * @skb: the buffew to weceive, owned by mac80211 aftew this caww
 * @napi: the NAPI context
 */
void ieee80211_wx_napi(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		       stwuct sk_buff *skb, stwuct napi_stwuct *napi);

/**
 * ieee80211_wx - weceive fwame
 *
 * Use this function to hand weceived fwames to mac80211. The weceive
 * buffew in @skb must stawt with an IEEE 802.11 headew. In case of a
 * paged @skb is used, the dwivew is wecommended to put the ieee80211
 * headew of the fwame on the wineaw pawt of the @skb to avoid memowy
 * awwocation and/ow memcpy by the stack.
 *
 * This function may not be cawwed in IWQ context. Cawws to this function
 * fow a singwe hawdwawe must be synchwonized against each othew. Cawws to
 * this function, ieee80211_wx_ni() and ieee80211_wx_iwqsafe() may not be
 * mixed fow a singwe hawdwawe. Must not wun concuwwentwy with
 * ieee80211_tx_status_skb() ow ieee80211_tx_status_ni().
 *
 * In pwocess context use instead ieee80211_wx_ni().
 *
 * @hw: the hawdwawe this fwame came in on
 * @skb: the buffew to weceive, owned by mac80211 aftew this caww
 */
static inwine void ieee80211_wx(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	ieee80211_wx_napi(hw, NUWW, skb, NUWW);
}

/**
 * ieee80211_wx_iwqsafe - weceive fwame
 *
 * Wike ieee80211_wx() but can be cawwed in IWQ context
 * (intewnawwy defews to a taskwet.)
 *
 * Cawws to this function, ieee80211_wx() ow ieee80211_wx_ni() may not
 * be mixed fow a singwe hawdwawe.Must not wun concuwwentwy with
 * ieee80211_tx_status_skb() ow ieee80211_tx_status_ni().
 *
 * @hw: the hawdwawe this fwame came in on
 * @skb: the buffew to weceive, owned by mac80211 aftew this caww
 */
void ieee80211_wx_iwqsafe(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);

/**
 * ieee80211_wx_ni - weceive fwame (in pwocess context)
 *
 * Wike ieee80211_wx() but can be cawwed in pwocess context
 * (intewnawwy disabwes bottom hawves).
 *
 * Cawws to this function, ieee80211_wx() and ieee80211_wx_iwqsafe() may
 * not be mixed fow a singwe hawdwawe. Must not wun concuwwentwy with
 * ieee80211_tx_status_skb() ow ieee80211_tx_status_ni().
 *
 * @hw: the hawdwawe this fwame came in on
 * @skb: the buffew to weceive, owned by mac80211 aftew this caww
 */
static inwine void ieee80211_wx_ni(stwuct ieee80211_hw *hw,
				   stwuct sk_buff *skb)
{
	wocaw_bh_disabwe();
	ieee80211_wx(hw, skb);
	wocaw_bh_enabwe();
}

/**
 * ieee80211_sta_ps_twansition - PS twansition fow connected sta
 *
 * When opewating in AP mode with the %IEEE80211_HW_AP_WINK_PS
 * fwag set, use this function to infowm mac80211 about a connected station
 * entewing/weaving PS mode.
 *
 * This function may not be cawwed in IWQ context ow with softiwqs enabwed.
 *
 * Cawws to this function fow a singwe hawdwawe must be synchwonized against
 * each othew.
 *
 * @sta: cuwwentwy connected sta
 * @stawt: stawt ow stop PS
 *
 * Wetuwn: 0 on success. -EINVAW when the wequested PS mode is awweady set.
 */
int ieee80211_sta_ps_twansition(stwuct ieee80211_sta *sta, boow stawt);

/**
 * ieee80211_sta_ps_twansition_ni - PS twansition fow connected sta
 *                                  (in pwocess context)
 *
 * Wike ieee80211_sta_ps_twansition() but can be cawwed in pwocess context
 * (intewnawwy disabwes bottom hawves). Concuwwent caww westwiction stiww
 * appwies.
 *
 * @sta: cuwwentwy connected sta
 * @stawt: stawt ow stop PS
 *
 * Wetuwn: Wike ieee80211_sta_ps_twansition().
 */
static inwine int ieee80211_sta_ps_twansition_ni(stwuct ieee80211_sta *sta,
						  boow stawt)
{
	int wet;

	wocaw_bh_disabwe();
	wet = ieee80211_sta_ps_twansition(sta, stawt);
	wocaw_bh_enabwe();

	wetuwn wet;
}

/**
 * ieee80211_sta_pspoww - PS-Poww fwame weceived
 * @sta: cuwwentwy connected station
 *
 * When opewating in AP mode with the %IEEE80211_HW_AP_WINK_PS fwag set,
 * use this function to infowm mac80211 that a PS-Poww fwame fwom a
 * connected station was weceived.
 * This must be used in conjunction with ieee80211_sta_ps_twansition()
 * and possibwy ieee80211_sta_uapsd_twiggew(); cawws to aww thwee must
 * be sewiawized.
 */
void ieee80211_sta_pspoww(stwuct ieee80211_sta *sta);

/**
 * ieee80211_sta_uapsd_twiggew - (potentiaw) U-APSD twiggew fwame weceived
 * @sta: cuwwentwy connected station
 * @tid: TID of the weceived (potentiaw) twiggew fwame
 *
 * When opewating in AP mode with the %IEEE80211_HW_AP_WINK_PS fwag set,
 * use this function to infowm mac80211 that a (potentiaw) twiggew fwame
 * fwom a connected station was weceived.
 * This must be used in conjunction with ieee80211_sta_ps_twansition()
 * and possibwy ieee80211_sta_pspoww(); cawws to aww thwee must be
 * sewiawized.
 * %IEEE80211_NUM_TIDS can be passed as the tid if the tid is unknown.
 * In this case, mac80211 wiww not check that this tid maps to an AC
 * that is twiggew enabwed and assume that the cawwew did the pwopew
 * checks.
 */
void ieee80211_sta_uapsd_twiggew(stwuct ieee80211_sta *sta, u8 tid);

/*
 * The TX headwoom wesewved by mac80211 fow its own tx_status functions.
 * This is enough fow the wadiotap headew.
 */
#define IEEE80211_TX_STATUS_HEADWOOM	AWIGN(14, 4)

/**
 * ieee80211_sta_set_buffewed - infowm mac80211 about dwivew-buffewed fwames
 * @sta: &stwuct ieee80211_sta pointew fow the sweeping station
 * @tid: the TID that has buffewed fwames
 * @buffewed: indicates whethew ow not fwames awe buffewed fow this TID
 *
 * If a dwivew buffews fwames fow a powewsave station instead of passing
 * them back to mac80211 fow wetwansmission, the station may stiww need
 * to be towd that thewe awe buffewed fwames via the TIM bit.
 *
 * This function infowms mac80211 whethew ow not thewe awe fwames that awe
 * buffewed in the dwivew fow a given TID; mac80211 can then use this data
 * to set the TIM bit (NOTE: This may caww back into the dwivew's set_tim
 * caww! Bewawe of the wocking!)
 *
 * If aww fwames awe weweased to the station (due to PS-poww ow uAPSD)
 * then the dwivew needs to infowm mac80211 that thewe no wongew awe
 * fwames buffewed. Howevew, when the station wakes up mac80211 assumes
 * that aww buffewed fwames wiww be twansmitted and cweaws this data,
 * dwivews need to make suwe they infowm mac80211 about aww buffewed
 * fwames on the sweep twansition (sta_notify() with %STA_NOTIFY_SWEEP).
 *
 * Note that technicawwy mac80211 onwy needs to know this pew AC, not pew
 * TID, but since dwivew buffewing wiww inevitabwy happen pew TID (since
 * it is wewated to aggwegation) it is easiew to make mac80211 map the
 * TID to the AC as wequiwed instead of keeping twack in aww dwivews that
 * use this API.
 */
void ieee80211_sta_set_buffewed(stwuct ieee80211_sta *sta,
				u8 tid, boow buffewed);

/**
 * ieee80211_get_tx_wates - get the sewected twansmit wates fow a packet
 *
 * Caww this function in a dwivew with pew-packet wate sewection suppowt
 * to combine the wate info in the packet tx info with the most wecent
 * wate sewection tabwe fow the station entwy.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @sta: the weceivew station to which this packet is sent.
 * @skb: the fwame to be twansmitted.
 * @dest: buffew fow extwacted wate/wetwy infowmation
 * @max_wates: maximum numbew of wates to fetch
 */
void ieee80211_get_tx_wates(stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb,
			    stwuct ieee80211_tx_wate *dest,
			    int max_wates);

/**
 * ieee80211_sta_set_expected_thwoughput - set the expected tpt fow a station
 *
 * Caww this function to notify mac80211 about a change in expected thwoughput
 * to a station. A dwivew fow a device that does wate contwow in fiwmwawe can
 * caww this function when the expected thwoughput estimate towawds a station
 * changes. The infowmation is used to tune the CoDew AQM appwied to twaffic
 * going towawds that station (which can othewwise be too aggwessive and cause
 * swow stations to stawve).
 *
 * @pubsta: the station to set thwoughput fow.
 * @thw: the cuwwent expected thwoughput in kbps.
 */
void ieee80211_sta_set_expected_thwoughput(stwuct ieee80211_sta *pubsta,
					   u32 thw);

/**
 * ieee80211_tx_wate_update - twansmit wate update cawwback
 *
 * Dwivews shouwd caww this functions with a non-NUWW pub sta
 * This function can be used in dwivews that does not have pwovision
 * in updating the tx wate in data path.
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @pubsta: the station to update the tx wate fow.
 * @info: tx status infowmation
 */
void ieee80211_tx_wate_update(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *pubsta,
			      stwuct ieee80211_tx_info *info);

/**
 * ieee80211_tx_status_skb - twansmit status cawwback
 *
 * Caww this function fow aww twansmitted fwames aftew they have been
 * twansmitted. It is pewmissibwe to not caww this function fow
 * muwticast fwames but this can affect statistics.
 *
 * This function may not be cawwed in IWQ context. Cawws to this function
 * fow a singwe hawdwawe must be synchwonized against each othew. Cawws
 * to this function, ieee80211_tx_status_ni() and ieee80211_tx_status_iwqsafe()
 * may not be mixed fow a singwe hawdwawe. Must not wun concuwwentwy with
 * ieee80211_wx() ow ieee80211_wx_ni().
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @skb: the fwame that was twansmitted, owned by mac80211 aftew this caww
 */
void ieee80211_tx_status_skb(stwuct ieee80211_hw *hw,
			     stwuct sk_buff *skb);

/**
 * ieee80211_tx_status_ext - extended twansmit status cawwback
 *
 * This function can be used as a wepwacement fow ieee80211_tx_status_skb()
 * in dwivews that may want to pwovide extwa infowmation that does not
 * fit into &stwuct ieee80211_tx_info.
 *
 * Cawws to this function fow a singwe hawdwawe must be synchwonized
 * against each othew. Cawws to this function, ieee80211_tx_status_ni()
 * and ieee80211_tx_status_iwqsafe() may not be mixed fow a singwe hawdwawe.
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @status: tx status infowmation
 */
void ieee80211_tx_status_ext(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_tx_status *status);

/**
 * ieee80211_tx_status_noskb - twansmit status cawwback without skb
 *
 * This function can be used as a wepwacement fow ieee80211_tx_status_skb()
 * in dwivews that cannot wewiabwy map tx status infowmation back to
 * specific skbs.
 *
 * Cawws to this function fow a singwe hawdwawe must be synchwonized
 * against each othew. Cawws to this function, ieee80211_tx_status_ni()
 * and ieee80211_tx_status_iwqsafe() may not be mixed fow a singwe hawdwawe.
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @sta: the weceivew station to which this packet is sent
 *	(NUWW fow muwticast packets)
 * @info: tx status infowmation
 */
static inwine void ieee80211_tx_status_noskb(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_sta *sta,
					     stwuct ieee80211_tx_info *info)
{
	stwuct ieee80211_tx_status status = {
		.sta = sta,
		.info = info,
	};

	ieee80211_tx_status_ext(hw, &status);
}

/**
 * ieee80211_tx_status_ni - twansmit status cawwback (in pwocess context)
 *
 * Wike ieee80211_tx_status_skb() but can be cawwed in pwocess context.
 *
 * Cawws to this function, ieee80211_tx_status_skb() and
 * ieee80211_tx_status_iwqsafe() may not be mixed
 * fow a singwe hawdwawe.
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @skb: the fwame that was twansmitted, owned by mac80211 aftew this caww
 */
static inwine void ieee80211_tx_status_ni(stwuct ieee80211_hw *hw,
					  stwuct sk_buff *skb)
{
	wocaw_bh_disabwe();
	ieee80211_tx_status_skb(hw, skb);
	wocaw_bh_enabwe();
}

/**
 * ieee80211_tx_status_iwqsafe - IWQ-safe twansmit status cawwback
 *
 * Wike ieee80211_tx_status_skb() but can be cawwed in IWQ context
 * (intewnawwy defews to a taskwet.)
 *
 * Cawws to this function, ieee80211_tx_status_skb() and
 * ieee80211_tx_status_ni() may not be mixed fow a singwe hawdwawe.
 *
 * @hw: the hawdwawe the fwame was twansmitted by
 * @skb: the fwame that was twansmitted, owned by mac80211 aftew this caww
 */
void ieee80211_tx_status_iwqsafe(stwuct ieee80211_hw *hw,
				 stwuct sk_buff *skb);

/**
 * ieee80211_wepowt_wow_ack - wepowt non-wesponding station
 *
 * When opewating in AP-mode, caww this function to wepowt a non-wesponding
 * connected STA.
 *
 * @sta: the non-wesponding connected sta
 * @num_packets: numbew of packets sent to @sta without a wesponse
 */
void ieee80211_wepowt_wow_ack(stwuct ieee80211_sta *sta, u32 num_packets);

#define IEEE80211_MAX_CNTDWN_COUNTEWS_NUM 2

/**
 * stwuct ieee80211_mutabwe_offsets - mutabwe beacon offsets
 * @tim_offset: position of TIM ewement
 * @tim_wength: size of TIM ewement
 * @cntdwn_countew_offs: awway of IEEE80211_MAX_CNTDWN_COUNTEWS_NUM offsets
 *	to countdown countews.  This awway can contain zewo vawues which
 *	shouwd be ignowed.
 * @mbssid_off: position of the muwtipwe bssid ewement
 */
stwuct ieee80211_mutabwe_offsets {
	u16 tim_offset;
	u16 tim_wength;

	u16 cntdwn_countew_offs[IEEE80211_MAX_CNTDWN_COUNTEWS_NUM];
	u16 mbssid_off;
};

/**
 * ieee80211_beacon_get_tempwate - beacon tempwate genewation function
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @offs: &stwuct ieee80211_mutabwe_offsets pointew to stwuct that wiww
 *	weceive the offsets that may be updated by the dwivew.
 * @wink_id: the wink id to which the beacon bewongs (ow 0 fow an AP STA
 *	that is not associated with AP MWD).
 *
 * If the dwivew impwements beaconing modes, it must use this function to
 * obtain the beacon tempwate.
 *
 * This function shouwd be used if the beacon fwames awe genewated by the
 * device, and then the dwivew must use the wetuwned beacon as the tempwate
 * The dwivew ow the device awe wesponsibwe to update the DTIM and, when
 * appwicabwe, the CSA count.
 *
 * The dwivew is wesponsibwe fow fweeing the wetuwned skb.
 *
 * Wetuwn: The beacon tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *
ieee80211_beacon_get_tempwate(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_mutabwe_offsets *offs,
			      unsigned int wink_id);

/**
 * ieee80211_beacon_get_tempwate_ema_index - EMA beacon tempwate genewation
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @offs: &stwuct ieee80211_mutabwe_offsets pointew to stwuct that wiww
 *	weceive the offsets that may be updated by the dwivew.
 * @wink_id: the wink id to which the beacon bewongs (ow 0 fow a non-MWD AP).
 * @ema_index: index of the beacon in the EMA set.
 *
 * This function fowwows the same wuwes as ieee80211_beacon_get_tempwate()
 * but wetuwns a beacon tempwate which incwudes muwtipwe BSSID ewement at the
 * wequested index.
 *
 * Wetuwn: The beacon tempwate. %NUWW indicates the end of EMA tempwates.
 */
stwuct sk_buff *
ieee80211_beacon_get_tempwate_ema_index(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_mutabwe_offsets *offs,
					unsigned int wink_id, u8 ema_index);

/**
 * stwuct ieee80211_ema_beacons - Wist of EMA beacons
 * @cnt: count of EMA beacons.
 *
 * @bcn: awway of EMA beacons.
 * @bcn.skb: the skb containing this specific beacon
 * @bcn.offs: &stwuct ieee80211_mutabwe_offsets pointew to stwuct that wiww
 *	weceive the offsets that may be updated by the dwivew.
 */
stwuct ieee80211_ema_beacons {
	u8 cnt;
	stwuct {
		stwuct sk_buff *skb;
		stwuct ieee80211_mutabwe_offsets offs;
	} bcn[];
};

/**
 * ieee80211_beacon_get_tempwate_ema_wist - EMA beacon tempwate genewation
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wink_id: the wink id to which the beacon bewongs (ow 0 fow a non-MWD AP)
 *
 * This function fowwows the same wuwes as ieee80211_beacon_get_tempwate()
 * but awwocates and wetuwns a pointew to wist of aww beacon tempwates wequiwed
 * to covew aww pwofiwes in the muwtipwe BSSID set. Each tempwate incwudes onwy
 * one muwtipwe BSSID ewement.
 *
 * Dwivew must caww ieee80211_beacon_fwee_ema_wist() to fwee the memowy.
 *
 * Wetuwn: EMA beacon tempwates of type stwuct ieee80211_ema_beacons *.
 *	%NUWW on ewwow.
 */
stwuct ieee80211_ema_beacons *
ieee80211_beacon_get_tempwate_ema_wist(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       unsigned int wink_id);

/**
 * ieee80211_beacon_fwee_ema_wist - fwee an EMA beacon tempwate wist
 * @ema_beacons: wist of EMA beacons of type &stwuct ieee80211_ema_beacons pointews.
 *
 * This function wiww fwee a wist pweviouswy acquiwed by cawwing
 * ieee80211_beacon_get_tempwate_ema_wist()
 */
void ieee80211_beacon_fwee_ema_wist(stwuct ieee80211_ema_beacons *ema_beacons);

/**
 * ieee80211_beacon_get_tim - beacon genewation function
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @tim_offset: pointew to vawiabwe that wiww weceive the TIM IE offset.
 *	Set to 0 if invawid (in non-AP modes).
 * @tim_wength: pointew to vawiabwe that wiww weceive the TIM IE wength,
 *	(incwuding the ID and wength bytes!).
 *	Set to 0 if invawid (in non-AP modes).
 * @wink_id: the wink id to which the beacon bewongs (ow 0 fow an AP STA
 *	that is not associated with AP MWD).
 *
 * If the dwivew impwements beaconing modes, it must use this function to
 * obtain the beacon fwame.
 *
 * If the beacon fwames awe genewated by the host system (i.e., not in
 * hawdwawe/fiwmwawe), the dwivew uses this function to get each beacon
 * fwame fwom mac80211 -- it is wesponsibwe fow cawwing this function exactwy
 * once befowe the beacon is needed (e.g. based on hawdwawe intewwupt).
 *
 * The dwivew is wesponsibwe fow fweeing the wetuwned skb.
 *
 * Wetuwn: The beacon tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_beacon_get_tim(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 u16 *tim_offset, u16 *tim_wength,
					 unsigned int wink_id);

/**
 * ieee80211_beacon_get - beacon genewation function
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wink_id: the wink id to which the beacon bewongs (ow 0 fow an AP STA
 *	that is not associated with AP MWD).
 *
 * See ieee80211_beacon_get_tim().
 *
 * Wetuwn: See ieee80211_beacon_get_tim().
 */
static inwine stwuct sk_buff *ieee80211_beacon_get(stwuct ieee80211_hw *hw,
						   stwuct ieee80211_vif *vif,
						   unsigned int wink_id)
{
	wetuwn ieee80211_beacon_get_tim(hw, vif, NUWW, NUWW, wink_id);
}

/**
 * ieee80211_beacon_update_cntdwn - wequest mac80211 to decwement the beacon countdown
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * The beacon countew shouwd be updated aftew each beacon twansmission.
 * This function is cawwed impwicitwy when
 * ieee80211_beacon_get/ieee80211_beacon_get_tim awe cawwed, howevew if the
 * beacon fwames awe genewated by the device, the dwivew shouwd caww this
 * function aftew each beacon twansmission to sync mac80211's beacon countdown.
 *
 * Wetuwn: new countdown vawue
 */
u8 ieee80211_beacon_update_cntdwn(stwuct ieee80211_vif *vif);

/**
 * ieee80211_beacon_set_cntdwn - wequest mac80211 to set beacon countdown
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @countew: the new vawue fow the countew
 *
 * The beacon countdown can be changed by the device, this API shouwd be
 * used by the device dwivew to update csa countew in mac80211.
 *
 * It shouwd nevew be used togethew with ieee80211_beacon_update_cntdwn(),
 * as it wiww cause a wace condition awound the countew vawue.
 */
void ieee80211_beacon_set_cntdwn(stwuct ieee80211_vif *vif, u8 countew);

/**
 * ieee80211_csa_finish - notify mac80211 about channew switch
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Aftew a channew switch announcement was scheduwed and the countew in this
 * announcement hits 1, this function must be cawwed by the dwivew to
 * notify mac80211 that the channew can be changed.
 */
void ieee80211_csa_finish(stwuct ieee80211_vif *vif);

/**
 * ieee80211_beacon_cntdwn_is_compwete - find out if countdown weached 1
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * This function wetuwns whethew the countdown weached zewo.
 */
boow ieee80211_beacon_cntdwn_is_compwete(stwuct ieee80211_vif *vif);

/**
 * ieee80211_cowow_change_finish - notify mac80211 about cowow change
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Aftew a cowow change announcement was scheduwed and the countew in this
 * announcement hits 1, this function must be cawwed by the dwivew to
 * notify mac80211 that the cowow can be changed
 */
void ieee80211_cowow_change_finish(stwuct ieee80211_vif *vif);

/**
 * ieee80211_pwobewesp_get - wetwieve a Pwobe Wesponse tempwate
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Cweates a Pwobe Wesponse tempwate which can, fow exampwe, be upwoaded to
 * hawdwawe. The destination addwess shouwd be set by the cawwew.
 *
 * Can onwy be cawwed in AP mode.
 *
 * Wetuwn: The Pwobe Wesponse tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_pwobewesp_get(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif);

/**
 * ieee80211_pspoww_get - wetwieve a PS Poww tempwate
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Cweates a PS Poww a tempwate which can, fow exampwe, upwoaded to
 * hawdwawe. The tempwate must be updated aftew association so that cowwect
 * AID, BSSID and MAC addwess is used.
 *
 * Note: Cawwew (ow hawdwawe) is wesponsibwe fow setting the
 * &IEEE80211_FCTW_PM bit.
 *
 * Wetuwn: The PS Poww tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_pspoww_get(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif);

/**
 * ieee80211_nuwwfunc_get - wetwieve a nuwwfunc tempwate
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wink_id: If the vif is an MWD, get a fwame with the wink addwesses
 *	fow the given wink ID. Fow a wink_id < 0 you get a fwame with
 *	MWD addwesses, howevew usefuw that might be.
 * @qos_ok: QoS NDP is acceptabwe to the cawwew, this shouwd be set
 *	if at aww possibwe
 *
 * Cweates a Nuwwfunc tempwate which can, fow exampwe, upwoaded to
 * hawdwawe. The tempwate must be updated aftew association so that cowwect
 * BSSID and addwess is used.
 *
 * If @qos_ndp is set and the association is to an AP with QoS/WMM, the
 * wetuwned packet wiww be QoS NDP.
 *
 * Note: Cawwew (ow hawdwawe) is wesponsibwe fow setting the
 * &IEEE80211_FCTW_PM bit as weww as Duwation and Sequence Contwow fiewds.
 *
 * Wetuwn: The nuwwfunc tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_nuwwfunc_get(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       int wink_id, boow qos_ok);

/**
 * ieee80211_pwobeweq_get - wetwieve a Pwobe Wequest tempwate
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @swc_addw: souwce MAC addwess
 * @ssid: SSID buffew
 * @ssid_wen: wength of SSID
 * @taiwwoom: taiwwoom to wesewve at end of SKB fow IEs
 *
 * Cweates a Pwobe Wequest tempwate which can, fow exampwe, be upwoaded to
 * hawdwawe.
 *
 * Wetuwn: The Pwobe Wequest tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_pwobeweq_get(stwuct ieee80211_hw *hw,
				       const u8 *swc_addw,
				       const u8 *ssid, size_t ssid_wen,
				       size_t taiwwoom);

/**
 * ieee80211_wts_get - WTS fwame genewation function
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @fwame: pointew to the fwame that is going to be pwotected by the WTS.
 * @fwame_wen: the fwame wength (in octets).
 * @fwame_txctw: &stwuct ieee80211_tx_info of the fwame.
 * @wts: The buffew whewe to stowe the WTS fwame.
 *
 * If the WTS fwames awe genewated by the host system (i.e., not in
 * hawdwawe/fiwmwawe), the wow-wevew dwivew uses this function to weceive
 * the next WTS fwame fwom the 802.11 code. The wow-wevew is wesponsibwe
 * fow cawwing this function befowe and WTS fwame is needed.
 */
void ieee80211_wts_get(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       const void *fwame, size_t fwame_wen,
		       const stwuct ieee80211_tx_info *fwame_txctw,
		       stwuct ieee80211_wts *wts);

/**
 * ieee80211_wts_duwation - Get the duwation fiewd fow an WTS fwame
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @fwame_wen: the wength of the fwame that is going to be pwotected by the WTS.
 * @fwame_txctw: &stwuct ieee80211_tx_info of the fwame.
 *
 * If the WTS is genewated in fiwmwawe, but the host system must pwovide
 * the duwation fiewd, the wow-wevew dwivew uses this function to weceive
 * the duwation fiewd vawue in wittwe-endian byteowdew.
 *
 * Wetuwn: The duwation.
 */
__we16 ieee80211_wts_duwation(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif, size_t fwame_wen,
			      const stwuct ieee80211_tx_info *fwame_txctw);

/**
 * ieee80211_ctstosewf_get - CTS-to-sewf fwame genewation function
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @fwame: pointew to the fwame that is going to be pwotected by the CTS-to-sewf.
 * @fwame_wen: the fwame wength (in octets).
 * @fwame_txctw: &stwuct ieee80211_tx_info of the fwame.
 * @cts: The buffew whewe to stowe the CTS-to-sewf fwame.
 *
 * If the CTS-to-sewf fwames awe genewated by the host system (i.e., not in
 * hawdwawe/fiwmwawe), the wow-wevew dwivew uses this function to weceive
 * the next CTS-to-sewf fwame fwom the 802.11 code. The wow-wevew is wesponsibwe
 * fow cawwing this function befowe and CTS-to-sewf fwame is needed.
 */
void ieee80211_ctstosewf_get(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     const void *fwame, size_t fwame_wen,
			     const stwuct ieee80211_tx_info *fwame_txctw,
			     stwuct ieee80211_cts *cts);

/**
 * ieee80211_ctstosewf_duwation - Get the duwation fiewd fow a CTS-to-sewf fwame
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @fwame_wen: the wength of the fwame that is going to be pwotected by the CTS-to-sewf.
 * @fwame_txctw: &stwuct ieee80211_tx_info of the fwame.
 *
 * If the CTS-to-sewf is genewated in fiwmwawe, but the host system must pwovide
 * the duwation fiewd, the wow-wevew dwivew uses this function to weceive
 * the duwation fiewd vawue in wittwe-endian byteowdew.
 *
 * Wetuwn: The duwation.
 */
__we16 ieee80211_ctstosewf_duwation(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    size_t fwame_wen,
				    const stwuct ieee80211_tx_info *fwame_txctw);

/**
 * ieee80211_genewic_fwame_duwation - Cawcuwate the duwation fiewd fow a fwame
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @band: the band to cawcuwate the fwame duwation on
 * @fwame_wen: the wength of the fwame.
 * @wate: the wate at which the fwame is going to be twansmitted.
 *
 * Cawcuwate the duwation fiewd of some genewic fwame, given its
 * wength and twansmission wate (in 100kbps).
 *
 * Wetuwn: The duwation.
 */
__we16 ieee80211_genewic_fwame_duwation(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					enum nw80211_band band,
					size_t fwame_wen,
					stwuct ieee80211_wate *wate);

/**
 * ieee80211_get_buffewed_bc - accessing buffewed bwoadcast and muwticast fwames
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Function fow accessing buffewed bwoadcast and muwticast fwames. If
 * hawdwawe/fiwmwawe does not impwement buffewing of bwoadcast/muwticast
 * fwames when powew saving is used, 802.11 code buffews them in the host
 * memowy. The wow-wevew dwivew uses this function to fetch next buffewed
 * fwame. In most cases, this is used when genewating beacon fwame.
 *
 * Wetuwn: A pointew to the next buffewed skb ow NUWW if no mowe buffewed
 * fwames awe avaiwabwe.
 *
 * Note: buffewed fwames awe wetuwned onwy aftew DTIM beacon fwame was
 * genewated with ieee80211_beacon_get() and the wow-wevew dwivew must thus
 * caww ieee80211_beacon_get() fiwst. ieee80211_get_buffewed_bc() wetuwns
 * NUWW if the pwevious genewated beacon was not DTIM, so the wow-wevew dwivew
 * does not need to check fow DTIM beacons sepawatewy and shouwd be abwe to
 * use common code fow aww beacons.
 */
stwuct sk_buff *
ieee80211_get_buffewed_bc(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);

/**
 * ieee80211_get_tkip_p1k_iv - get a TKIP phase 1 key fow IV32
 *
 * This function wetuwns the TKIP phase 1 key fow the given IV32.
 *
 * @keyconf: the pawametew passed with the set key
 * @iv32: IV32 to get the P1K fow
 * @p1k: a buffew to which the key wiww be wwitten, as 5 u16 vawues
 */
void ieee80211_get_tkip_p1k_iv(stwuct ieee80211_key_conf *keyconf,
			       u32 iv32, u16 *p1k);

/**
 * ieee80211_get_tkip_p1k - get a TKIP phase 1 key
 *
 * This function wetuwns the TKIP phase 1 key fow the IV32 taken
 * fwom the given packet.
 *
 * @keyconf: the pawametew passed with the set key
 * @skb: the packet to take the IV32 vawue fwom that wiww be encwypted
 *	with this P1K
 * @p1k: a buffew to which the key wiww be wwitten, as 5 u16 vawues
 */
static inwine void ieee80211_get_tkip_p1k(stwuct ieee80211_key_conf *keyconf,
					  stwuct sk_buff *skb, u16 *p1k)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	const u8 *data = (u8 *)hdw + ieee80211_hdwwen(hdw->fwame_contwow);
	u32 iv32 = get_unawigned_we32(&data[4]);

	ieee80211_get_tkip_p1k_iv(keyconf, iv32, p1k);
}

/**
 * ieee80211_get_tkip_wx_p1k - get a TKIP phase 1 key fow WX
 *
 * This function wetuwns the TKIP phase 1 key fow the given IV32
 * and twansmittew addwess.
 *
 * @keyconf: the pawametew passed with the set key
 * @ta: TA that wiww be used with the key
 * @iv32: IV32 to get the P1K fow
 * @p1k: a buffew to which the key wiww be wwitten, as 5 u16 vawues
 */
void ieee80211_get_tkip_wx_p1k(stwuct ieee80211_key_conf *keyconf,
			       const u8 *ta, u32 iv32, u16 *p1k);

/**
 * ieee80211_get_tkip_p2k - get a TKIP phase 2 key
 *
 * This function computes the TKIP WC4 key fow the IV vawues
 * in the packet.
 *
 * @keyconf: the pawametew passed with the set key
 * @skb: the packet to take the IV32/IV16 vawues fwom that wiww be
 *	encwypted with this key
 * @p2k: a buffew to which the key wiww be wwitten, 16 bytes
 */
void ieee80211_get_tkip_p2k(stwuct ieee80211_key_conf *keyconf,
			    stwuct sk_buff *skb, u8 *p2k);

/**
 * ieee80211_tkip_add_iv - wwite TKIP IV and Ext. IV to pos
 *
 * @pos: stawt of cwypto headew
 * @keyconf: the pawametew passed with the set key
 * @pn: PN to add
 *
 * Wetuwns: pointew to the octet fowwowing IVs (i.e. beginning of
 * the packet paywoad)
 *
 * This function wwites the tkip IV vawue to pos (which shouwd
 * point to the cwypto headew)
 */
u8 *ieee80211_tkip_add_iv(u8 *pos, stwuct ieee80211_key_conf *keyconf, u64 pn);

/**
 * ieee80211_get_key_wx_seq - get key WX sequence countew
 *
 * @keyconf: the pawametew passed with the set key
 * @tid: The TID, ow -1 fow the management fwame vawue (CCMP/GCMP onwy);
 *	the vawue on TID 0 is awso used fow non-QoS fwames. Fow
 *	CMAC, onwy TID 0 is vawid.
 * @seq: buffew to weceive the sequence data
 *
 * This function awwows a dwivew to wetwieve the cuwwent WX IV/PNs
 * fow the given key. It must not be cawwed if IV checking is done
 * by the device and not by mac80211.
 *
 * Note that this function may onwy be cawwed when no WX pwocessing
 * can be done concuwwentwy.
 */
void ieee80211_get_key_wx_seq(stwuct ieee80211_key_conf *keyconf,
			      int tid, stwuct ieee80211_key_seq *seq);

/**
 * ieee80211_set_key_wx_seq - set key WX sequence countew
 *
 * @keyconf: the pawametew passed with the set key
 * @tid: The TID, ow -1 fow the management fwame vawue (CCMP/GCMP onwy);
 *	the vawue on TID 0 is awso used fow non-QoS fwames. Fow
 *	CMAC, onwy TID 0 is vawid.
 * @seq: new sequence data
 *
 * This function awwows a dwivew to set the cuwwent WX IV/PNs fow the
 * given key. This is usefuw when wesuming fwom WoWWAN sweep and GTK
 * wekey may have been done whiwe suspended. It shouwd not be cawwed
 * if IV checking is done by the device and not by mac80211.
 *
 * Note that this function may onwy be cawwed when no WX pwocessing
 * can be done concuwwentwy.
 */
void ieee80211_set_key_wx_seq(stwuct ieee80211_key_conf *keyconf,
			      int tid, stwuct ieee80211_key_seq *seq);

/**
 * ieee80211_wemove_key - wemove the given key
 * @keyconf: the pawametew passed with the set key
 *
 * Context: Must be cawwed with the wiphy mutex hewd.
 *
 * Wemove the given key. If the key was upwoaded to the hawdwawe at the
 * time this function is cawwed, it is not deweted in the hawdwawe but
 * instead assumed to have been wemoved awweady.
 */
void ieee80211_wemove_key(stwuct ieee80211_key_conf *keyconf);

/**
 * ieee80211_gtk_wekey_add - add a GTK key fwom wekeying duwing WoWWAN
 * @vif: the viwtuaw intewface to add the key on
 * @keyconf: new key data
 *
 * When GTK wekeying was done whiwe the system was suspended, (a) new
 * key(s) wiww be avaiwabwe. These wiww be needed by mac80211 fow pwopew
 * WX pwocessing, so this function awwows setting them.
 *
 * The function wetuwns the newwy awwocated key stwuctuwe, which wiww
 * have simiwaw contents to the passed key configuwation but point to
 * mac80211-owned memowy. In case of ewwows, the function wetuwns an
 * EWW_PTW(), use IS_EWW() etc.
 *
 * Note that this function assumes the key isn't added to hawdwawe
 * accewewation, so no TX wiww be done with the key. Since it's a GTK
 * on managed (station) netwowks, this is twue anyway. If the dwivew
 * cawws this function fwom the wesume cawwback and subsequentwy uses
 * the wetuwn code 1 to weconfiguwe the device, this key wiww be pawt
 * of the weconfiguwation.
 *
 * Note that the dwivew shouwd awso caww ieee80211_set_key_wx_seq()
 * fow the new key fow each TID to set up sequence countews pwopewwy.
 *
 * IMPOWTANT: If this wepwaces a key that is pwesent in the hawdwawe,
 * then it wiww attempt to wemove it duwing this caww. In many cases
 * this isn't what you want, so caww ieee80211_wemove_key() fiwst fow
 * the key that's being wepwaced.
 */
stwuct ieee80211_key_conf *
ieee80211_gtk_wekey_add(stwuct ieee80211_vif *vif,
			stwuct ieee80211_key_conf *keyconf);

/**
 * ieee80211_gtk_wekey_notify - notify usewspace suppwicant of wekeying
 * @vif: viwtuaw intewface the wekeying was done on
 * @bssid: The BSSID of the AP, fow checking association
 * @wepway_ctw: the new wepway countew aftew GTK wekeying
 * @gfp: awwocation fwags
 */
void ieee80211_gtk_wekey_notify(stwuct ieee80211_vif *vif, const u8 *bssid,
				const u8 *wepway_ctw, gfp_t gfp);

/**
 * ieee80211_key_mic_faiwuwe - incwement MIC faiwuwe countew fow the key
 *
 * Note: this is weawwy onwy safe if no othew WX function is cawwed
 * at the same time.
 *
 * @keyconf: the key in question
 */
void ieee80211_key_mic_faiwuwe(stwuct ieee80211_key_conf *keyconf);

/**
 * ieee80211_key_wepway - incwement wepway countew fow the key
 *
 * Note: this is weawwy onwy safe if no othew WX function is cawwed
 * at the same time.
 *
 * @keyconf: the key in question
 */
void ieee80211_key_wepway(stwuct ieee80211_key_conf *keyconf);

/**
 * ieee80211_wake_queue - wake specific queue
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 * @queue: queue numbew (counted fwom zewo).
 *
 * Dwivews must use this function instead of netif_wake_queue.
 */
void ieee80211_wake_queue(stwuct ieee80211_hw *hw, int queue);

/**
 * ieee80211_stop_queue - stop specific queue
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 * @queue: queue numbew (counted fwom zewo).
 *
 * Dwivews must use this function instead of netif_stop_queue.
 */
void ieee80211_stop_queue(stwuct ieee80211_hw *hw, int queue);

/**
 * ieee80211_queue_stopped - test status of the queue
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 * @queue: queue numbew (counted fwom zewo).
 *
 * Dwivews must use this function instead of netif_queue_stopped.
 *
 * Wetuwn: %twue if the queue is stopped. %fawse othewwise.
 */

int ieee80211_queue_stopped(stwuct ieee80211_hw *hw, int queue);

/**
 * ieee80211_stop_queues - stop aww queues
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 *
 * Dwivews must use this function instead of netif_tx_stop_aww_queues.
 */
void ieee80211_stop_queues(stwuct ieee80211_hw *hw);

/**
 * ieee80211_wake_queues - wake aww queues
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw().
 *
 * Dwivews must use this function instead of netif_tx_wake_aww_queues.
 */
void ieee80211_wake_queues(stwuct ieee80211_hw *hw);

/**
 * ieee80211_scan_compweted - compweted hawdwawe scan
 *
 * When hawdwawe scan offwoad is used (i.e. the hw_scan() cawwback is
 * assigned) this function needs to be cawwed by the dwivew to notify
 * mac80211 that the scan finished. This function can be cawwed fwom
 * any context, incwuding hawdiwq context.
 *
 * @hw: the hawdwawe that finished the scan
 * @info: infowmation about the compweted scan
 */
void ieee80211_scan_compweted(stwuct ieee80211_hw *hw,
			      stwuct cfg80211_scan_info *info);

/**
 * ieee80211_sched_scan_wesuwts - got wesuwts fwom scheduwed scan
 *
 * When a scheduwed scan is wunning, this function needs to be cawwed by the
 * dwivew whenevew thewe awe new scan wesuwts avaiwabwe.
 *
 * @hw: the hawdwawe that is pewfowming scheduwed scans
 */
void ieee80211_sched_scan_wesuwts(stwuct ieee80211_hw *hw);

/**
 * ieee80211_sched_scan_stopped - infowm that the scheduwed scan has stopped
 *
 * When a scheduwed scan is wunning, this function can be cawwed by
 * the dwivew if it needs to stop the scan to pewfowm anothew task.
 * Usuaw scenawios awe dwivews that cannot continue the scheduwed scan
 * whiwe associating, fow instance.
 *
 * @hw: the hawdwawe that is pewfowming scheduwed scans
 */
void ieee80211_sched_scan_stopped(stwuct ieee80211_hw *hw);

/**
 * enum ieee80211_intewface_itewation_fwags - intewface itewation fwags
 * @IEEE80211_IFACE_ITEW_NOWMAW: Itewate ovew aww intewfaces that have
 *	been added to the dwivew; Howevew, note that duwing hawdwawe
 *	weconfiguwation (aftew westawt_hw) it wiww itewate ovew a new
 *	intewface and ovew aww the existing intewfaces even if they
 *	haven't been we-added to the dwivew yet.
 * @IEEE80211_IFACE_ITEW_WESUME_AWW: Duwing wesume, itewate ovew aww
 *	intewfaces, even if they haven't been we-added to the dwivew yet.
 * @IEEE80211_IFACE_ITEW_ACTIVE: Itewate onwy active intewfaces (netdev is up).
 * @IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DWIVEW: Skip any intewfaces whewe SDATA
 *	is not in the dwivew.  This may fix cwashes duwing fiwmwawe wecovewy
 *	fow instance.
 */
enum ieee80211_intewface_itewation_fwags {
	IEEE80211_IFACE_ITEW_NOWMAW	= 0,
	IEEE80211_IFACE_ITEW_WESUME_AWW	= BIT(0),
	IEEE80211_IFACE_ITEW_ACTIVE	= BIT(1),
	IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DWIVEW	= BIT(2),
};

/**
 * ieee80211_itewate_intewfaces - itewate intewfaces
 *
 * This function itewates ovew the intewfaces associated with a given
 * hawdwawe and cawws the cawwback fow them. This incwudes active as weww as
 * inactive intewfaces. This function awwows the itewatow function to sweep.
 * Wiww itewate ovew a new intewface duwing add_intewface().
 *
 * @hw: the hawdwawe stwuct of which the intewfaces shouwd be itewated ovew
 * @itew_fwags: itewation fwags, see &enum ieee80211_intewface_itewation_fwags
 * @itewatow: the itewatow function to caww
 * @data: fiwst awgument of the itewatow function
 */
void ieee80211_itewate_intewfaces(stwuct ieee80211_hw *hw, u32 itew_fwags,
				  void (*itewatow)(void *data, u8 *mac,
						   stwuct ieee80211_vif *vif),
				  void *data);

/**
 * ieee80211_itewate_active_intewfaces - itewate active intewfaces
 *
 * This function itewates ovew the intewfaces associated with a given
 * hawdwawe that awe cuwwentwy active and cawws the cawwback fow them.
 * This function awwows the itewatow function to sweep, when the itewatow
 * function is atomic @ieee80211_itewate_active_intewfaces_atomic can
 * be used.
 * Does not itewate ovew a new intewface duwing add_intewface().
 *
 * @hw: the hawdwawe stwuct of which the intewfaces shouwd be itewated ovew
 * @itew_fwags: itewation fwags, see &enum ieee80211_intewface_itewation_fwags
 * @itewatow: the itewatow function to caww
 * @data: fiwst awgument of the itewatow function
 */
static inwine void
ieee80211_itewate_active_intewfaces(stwuct ieee80211_hw *hw, u32 itew_fwags,
				    void (*itewatow)(void *data, u8 *mac,
						     stwuct ieee80211_vif *vif),
				    void *data)
{
	ieee80211_itewate_intewfaces(hw,
				     itew_fwags | IEEE80211_IFACE_ITEW_ACTIVE,
				     itewatow, data);
}

/**
 * ieee80211_itewate_active_intewfaces_atomic - itewate active intewfaces
 *
 * This function itewates ovew the intewfaces associated with a given
 * hawdwawe that awe cuwwentwy active and cawws the cawwback fow them.
 * This function wequiwes the itewatow cawwback function to be atomic,
 * if that is not desiwed, use @ieee80211_itewate_active_intewfaces instead.
 * Does not itewate ovew a new intewface duwing add_intewface().
 *
 * @hw: the hawdwawe stwuct of which the intewfaces shouwd be itewated ovew
 * @itew_fwags: itewation fwags, see &enum ieee80211_intewface_itewation_fwags
 * @itewatow: the itewatow function to caww, cannot sweep
 * @data: fiwst awgument of the itewatow function
 */
void ieee80211_itewate_active_intewfaces_atomic(stwuct ieee80211_hw *hw,
						u32 itew_fwags,
						void (*itewatow)(void *data,
						    u8 *mac,
						    stwuct ieee80211_vif *vif),
						void *data);

/**
 * ieee80211_itewate_active_intewfaces_mtx - itewate active intewfaces
 *
 * This function itewates ovew the intewfaces associated with a given
 * hawdwawe that awe cuwwentwy active and cawws the cawwback fow them.
 * This vewsion can onwy be used whiwe howding the wiphy mutex.
 *
 * @hw: the hawdwawe stwuct of which the intewfaces shouwd be itewated ovew
 * @itew_fwags: itewation fwags, see &enum ieee80211_intewface_itewation_fwags
 * @itewatow: the itewatow function to caww, cannot sweep
 * @data: fiwst awgument of the itewatow function
 */
void ieee80211_itewate_active_intewfaces_mtx(stwuct ieee80211_hw *hw,
					     u32 itew_fwags,
					     void (*itewatow)(void *data,
						u8 *mac,
						stwuct ieee80211_vif *vif),
					     void *data);

/**
 * ieee80211_itewate_stations_atomic - itewate stations
 *
 * This function itewates ovew aww stations associated with a given
 * hawdwawe that awe cuwwentwy upwoaded to the dwivew and cawws the cawwback
 * function fow them.
 * This function wequiwes the itewatow cawwback function to be atomic,
 *
 * @hw: the hawdwawe stwuct of which the intewfaces shouwd be itewated ovew
 * @itewatow: the itewatow function to caww, cannot sweep
 * @data: fiwst awgument of the itewatow function
 */
void ieee80211_itewate_stations_atomic(stwuct ieee80211_hw *hw,
				       void (*itewatow)(void *data,
						stwuct ieee80211_sta *sta),
				       void *data);
/**
 * ieee80211_queue_wowk - add wowk onto the mac80211 wowkqueue
 *
 * Dwivews and mac80211 use this to add wowk onto the mac80211 wowkqueue.
 * This hewpew ensuwes dwivews awe not queueing wowk when they shouwd not be.
 *
 * @hw: the hawdwawe stwuct fow the intewface we awe adding wowk fow
 * @wowk: the wowk we want to add onto the mac80211 wowkqueue
 */
void ieee80211_queue_wowk(stwuct ieee80211_hw *hw, stwuct wowk_stwuct *wowk);

/**
 * ieee80211_queue_dewayed_wowk - add wowk onto the mac80211 wowkqueue
 *
 * Dwivews and mac80211 use this to queue dewayed wowk onto the mac80211
 * wowkqueue.
 *
 * @hw: the hawdwawe stwuct fow the intewface we awe adding wowk fow
 * @dwowk: dewayabwe wowk to queue onto the mac80211 wowkqueue
 * @deway: numbew of jiffies to wait befowe queueing
 */
void ieee80211_queue_dewayed_wowk(stwuct ieee80211_hw *hw,
				  stwuct dewayed_wowk *dwowk,
				  unsigned wong deway);

/**
 * ieee80211_wefwesh_tx_agg_session_timew - Wefwesh a tx agg session timew.
 * @sta: the station fow which to stawt a BA session
 * @tid: the TID to BA on.
 *
 * This function awwows wow wevew dwivew to wefwesh tx agg session timew
 * to maintain BA session, the session wevew wiww stiww be managed by the
 * mac80211.
 *
 * Note: must be cawwed in an WCU cwiticaw section.
 */
void ieee80211_wefwesh_tx_agg_session_timew(stwuct ieee80211_sta *sta,
					    u16 tid);

/**
 * ieee80211_stawt_tx_ba_session - Stawt a tx Bwock Ack session.
 * @sta: the station fow which to stawt a BA session
 * @tid: the TID to BA on.
 * @timeout: session timeout vawue (in TUs)
 *
 * Wetuwn: success if addBA wequest was sent, faiwuwe othewwise
 *
 * Awthough mac80211/wow wevew dwivew/usew space appwication can estimate
 * the need to stawt aggwegation on a cewtain WA/TID, the session wevew
 * wiww be managed by the mac80211.
 */
int ieee80211_stawt_tx_ba_session(stwuct ieee80211_sta *sta, u16 tid,
				  u16 timeout);

/**
 * ieee80211_stawt_tx_ba_cb_iwqsafe - wow wevew dwivew weady to aggwegate.
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @wa: weceivew addwess of the BA session wecipient.
 * @tid: the TID to BA on.
 *
 * This function must be cawwed by wow wevew dwivew once it has
 * finished with pwepawations fow the BA session. It can be cawwed
 * fwom any context.
 */
void ieee80211_stawt_tx_ba_cb_iwqsafe(stwuct ieee80211_vif *vif, const u8 *wa,
				      u16 tid);

/**
 * ieee80211_stop_tx_ba_session - Stop a Bwock Ack session.
 * @sta: the station whose BA session to stop
 * @tid: the TID to stop BA.
 *
 * Wetuwn: negative ewwow if the TID is invawid, ow no aggwegation active
 *
 * Awthough mac80211/wow wevew dwivew/usew space appwication can estimate
 * the need to stop aggwegation on a cewtain WA/TID, the session wevew
 * wiww be managed by the mac80211.
 */
int ieee80211_stop_tx_ba_session(stwuct ieee80211_sta *sta, u16 tid);

/**
 * ieee80211_stop_tx_ba_cb_iwqsafe - wow wevew dwivew weady to stop aggwegate.
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @wa: weceivew addwess of the BA session wecipient.
 * @tid: the desiwed TID to BA on.
 *
 * This function must be cawwed by wow wevew dwivew once it has
 * finished with pwepawations fow the BA session teaw down. It
 * can be cawwed fwom any context.
 */
void ieee80211_stop_tx_ba_cb_iwqsafe(stwuct ieee80211_vif *vif, const u8 *wa,
				     u16 tid);

/**
 * ieee80211_find_sta - find a station
 *
 * @vif: viwtuaw intewface to wook fow station on
 * @addw: station's addwess
 *
 * Wetuwn: The station, if found. %NUWW othewwise.
 *
 * Note: This function must be cawwed undew WCU wock and the
 * wesuwting pointew is onwy vawid undew WCU wock as weww.
 */
stwuct ieee80211_sta *ieee80211_find_sta(stwuct ieee80211_vif *vif,
					 const u8 *addw);

/**
 * ieee80211_find_sta_by_ifaddw - find a station on hawdwawe
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @addw: wemote station's addwess
 * @wocawaddw: wocaw addwess (vif->sdata->vif.addw). Use NUWW fow 'any'.
 *
 * Wetuwn: The station, if found. %NUWW othewwise.
 *
 * Note: This function must be cawwed undew WCU wock and the
 * wesuwting pointew is onwy vawid undew WCU wock as weww.
 *
 * NOTE: You may pass NUWW fow wocawaddw, but then you wiww just get
 *      the fiwst STA that matches the wemote addwess 'addw'.
 *      We can have muwtipwe STA associated with muwtipwe
 *      wogicaw stations (e.g. considew a station connecting to anothew
 *      BSSID on the same AP hawdwawe without disconnecting fiwst).
 *      In this case, the wesuwt of this method with wocawaddw NUWW
 *      is not wewiabwe.
 *
 * DO NOT USE THIS FUNCTION with wocawaddw NUWW if at aww possibwe.
 */
stwuct ieee80211_sta *ieee80211_find_sta_by_ifaddw(stwuct ieee80211_hw *hw,
					       const u8 *addw,
					       const u8 *wocawaddw);

/**
 * ieee80211_find_sta_by_wink_addws - find STA by wink addwesses
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @addw: wemote station's wink addwess
 * @wocawaddw: wocaw wink addwess, use %NUWW fow any (but avoid that)
 * @wink_id: pointew to obtain the wink ID if the STA is found,
 *	may be %NUWW if the wink ID is not needed
 *
 * Obtain the STA by wink addwess, must use WCU pwotection.
 */
stwuct ieee80211_sta *
ieee80211_find_sta_by_wink_addws(stwuct ieee80211_hw *hw,
				 const u8 *addw,
				 const u8 *wocawaddw,
				 unsigned int *wink_id);

/**
 * ieee80211_sta_bwock_awake - bwock station fwom waking up
 * @hw: the hawdwawe
 * @pubsta: the station
 * @bwock: whethew to bwock ow unbwock
 *
 * Some devices wequiwe that aww fwames that awe on the queues
 * fow a specific station that went to sweep awe fwushed befowe
 * a poww wesponse ow fwames aftew the station woke up can be
 * dewivewed to that it. Note that such fwames must be wejected
 * by the dwivew as fiwtewed, with the appwopwiate status fwag.
 *
 * This function awwows impwementing this mode in a wace-fwee
 * mannew.
 *
 * To do this, a dwivew must keep twack of the numbew of fwames
 * stiww enqueued fow a specific station. If this numbew is not
 * zewo when the station goes to sweep, the dwivew must caww
 * this function to fowce mac80211 to considew the station to
 * be asweep wegawdwess of the station's actuaw state. Once the
 * numbew of outstanding fwames weaches zewo, the dwivew must
 * caww this function again to unbwock the station. That wiww
 * cause mac80211 to be abwe to send ps-poww wesponses, and if
 * the station quewied in the meantime then fwames wiww awso
 * be sent out as a wesuwt of this. Additionawwy, the dwivew
 * wiww be notified that the station woke up some time aftew
 * it is unbwocked, wegawdwess of whethew the station actuawwy
 * woke up whiwe bwocked ow not.
 */
void ieee80211_sta_bwock_awake(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_sta *pubsta, boow bwock);

/**
 * ieee80211_sta_eosp - notify mac80211 about end of SP
 * @pubsta: the station
 *
 * When a device twansmits fwames in a way that it can't teww
 * mac80211 in the TX status about the EOSP, it must cweaw the
 * %IEEE80211_TX_STATUS_EOSP bit and caww this function instead.
 * This appwies fow PS-Poww as weww as uAPSD.
 *
 * Note that just wike with _tx_status() and _wx() dwivews must
 * not mix cawws to iwqsafe/non-iwqsafe vewsions, this function
 * must not be mixed with those eithew. Use the aww iwqsafe, ow
 * aww non-iwqsafe, don't mix!
 *
 * NB: the _iwqsafe vewsion of this function doesn't exist, no
 *     dwivew needs it wight now. Don't caww this function if
 *     you'd need the _iwqsafe vewsion, wook at the git histowy
 *     and westowe the _iwqsafe vewsion!
 */
void ieee80211_sta_eosp(stwuct ieee80211_sta *pubsta);

/**
 * ieee80211_send_eosp_nuwwfunc - ask mac80211 to send NDP with EOSP
 * @pubsta: the station
 * @tid: the tid of the NDP
 *
 * Sometimes the device undewstands that it needs to cwose
 * the Sewvice Pewiod unexpectedwy. This can happen when
 * sending fwames that awe fiwwing howes in the BA window.
 * In this case, the device can ask mac80211 to send a
 * Nuwwfunc fwame with EOSP set. When that happens, the
 * dwivew must have cawwed ieee80211_sta_set_buffewed() to
 * wet mac80211 know that thewe awe no buffewed fwames any
 * mowe, othewwise mac80211 wiww get the mowe_data bit wwong.
 * The wow wevew dwivew must have made suwe that the fwame
 * wiww be sent despite the station being in powew-save.
 * Mac80211 won't caww awwow_buffewed_fwames().
 * Note that cawwing this function, doesn't exempt the dwivew
 * fwom cwosing the EOSP pwopewwy, it wiww stiww have to caww
 * ieee80211_sta_eosp when the NDP is sent.
 */
void ieee80211_send_eosp_nuwwfunc(stwuct ieee80211_sta *pubsta, int tid);

/**
 * ieee80211_sta_wecawc_aggwegates - wecawcuwate aggwegate data aftew a change
 * @pubsta: the station
 *
 * Caww this function aftew changing a pew-wink aggwegate data as wefewenced in
 * &stwuct ieee80211_sta_aggwegates by accessing the agg fiewd of
 * &stwuct ieee80211_wink_sta.
 *
 * With non MWO the data in defwink wiww be wefewenced diwectwy. In that case
 * thewe is no need to caww this function.
 */
void ieee80211_sta_wecawc_aggwegates(stwuct ieee80211_sta *pubsta);

/**
 * ieee80211_sta_wegistew_aiwtime - wegistew aiwtime usage fow a sta/tid
 *
 * Wegistew aiwtime usage fow a given sta on a given tid. The dwivew must caww
 * this function to notify mac80211 that a station used a cewtain amount of
 * aiwtime. This infowmation wiww be used by the TXQ scheduwew to scheduwe
 * stations in a way that ensuwes aiwtime faiwness.
 *
 * The wepowted aiwtime shouwd as a minimum incwude aww time that is spent
 * twansmitting to the wemote station, incwuding ovewhead and padding, but not
 * incwuding time spent waiting fow a TXOP. If the time is not wepowted by the
 * hawdwawe it can in some cases be cawcuwated fwom the wate and known fwame
 * composition. When possibwe, the time shouwd incwude any faiwed twansmission
 * attempts.
 *
 * The dwivew can eithew caww this function synchwonouswy fow evewy packet ow
 * aggwegate, ow asynchwonouswy as aiwtime usage infowmation becomes avaiwabwe.
 * TX and WX aiwtime can be wepowted togethew, ow sepawatewy by setting one of
 * them to 0.
 *
 * @pubsta: the station
 * @tid: the TID to wegistew aiwtime fow
 * @tx_aiwtime: aiwtime used duwing TX (in usec)
 * @wx_aiwtime: aiwtime used duwing WX (in usec)
 */
void ieee80211_sta_wegistew_aiwtime(stwuct ieee80211_sta *pubsta, u8 tid,
				    u32 tx_aiwtime, u32 wx_aiwtime);

/**
 * ieee80211_txq_aiwtime_check - check if a txq can send fwame to device
 *
 * @hw: pointew obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface
 *
 * Wetuwn twue if the AQW's aiwtime wimit has not been weached and the txq can
 * continue to send mowe packets to the device. Othewwise wetuwn fawse.
 */
boow
ieee80211_txq_aiwtime_check(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *txq);

/**
 * ieee80211_itew_keys - itewate keys pwogwammed into the device
 * @hw: pointew obtained fwom ieee80211_awwoc_hw()
 * @vif: viwtuaw intewface to itewate, may be %NUWW fow aww
 * @itew: itewatow function that wiww be cawwed fow each key
 * @itew_data: custom data to pass to the itewatow function
 *
 * Context: Must be cawwed with wiphy mutex hewd; can sweep.
 *
 * This function can be used to itewate aww the keys known to
 * mac80211, even those that wewen't pweviouswy pwogwammed into
 * the device. This is intended fow use in WoWWAN if the device
 * needs wepwogwamming of the keys duwing suspend.
 *
 * The owdew in which the keys awe itewated matches the owdew
 * in which they wewe owiginawwy instawwed and handed to the
 * set_key cawwback.
 */
void ieee80211_itew_keys(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 void (*itew)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      stwuct ieee80211_key_conf *key,
				      void *data),
			 void *itew_data);

/**
 * ieee80211_itew_keys_wcu - itewate keys pwogwammed into the device
 * @hw: pointew obtained fwom ieee80211_awwoc_hw()
 * @vif: viwtuaw intewface to itewate, may be %NUWW fow aww
 * @itew: itewatow function that wiww be cawwed fow each key
 * @itew_data: custom data to pass to the itewatow function
 *
 * This function can be used to itewate aww the keys known to
 * mac80211, even those that wewen't pweviouswy pwogwammed into
 * the device. Note that due to wocking weasons, keys of station
 * in wemovaw pwocess wiww be skipped.
 *
 * This function wequiwes being cawwed in an WCU cwiticaw section,
 * and thus itew must be atomic.
 */
void ieee80211_itew_keys_wcu(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     void (*itew)(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_sta *sta,
					  stwuct ieee80211_key_conf *key,
					  void *data),
			     void *itew_data);

/**
 * ieee80211_itew_chan_contexts_atomic - itewate channew contexts
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @itew: itewatow function
 * @itew_data: data passed to itewatow function
 *
 * Itewate aww active channew contexts. This function is atomic and
 * doesn't acquiwe any wocks intewnawwy that might be hewd in othew
 * pwaces whiwe cawwing into the dwivew.
 *
 * The itewatow wiww not find a context that's being added (duwing
 * the dwivew cawwback to add it) but wiww find it whiwe it's being
 * wemoved.
 *
 * Note that duwing hawdwawe westawt, aww contexts that existed
 * befowe the westawt awe considewed awweady pwesent so wiww be
 * found whiwe itewating, whethew they've been we-added awweady
 * ow not.
 */
void ieee80211_itew_chan_contexts_atomic(
	stwuct ieee80211_hw *hw,
	void (*itew)(stwuct ieee80211_hw *hw,
		     stwuct ieee80211_chanctx_conf *chanctx_conf,
		     void *data),
	void *itew_data);

/**
 * ieee80211_ap_pwobeweq_get - wetwieve a Pwobe Wequest tempwate
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Cweates a Pwobe Wequest tempwate which can, fow exampwe, be upwoaded to
 * hawdwawe. The tempwate is fiwwed with bssid, ssid and suppowted wate
 * infowmation. This function must onwy be cawwed fwom within the
 * .bss_info_changed cawwback function and onwy in managed mode. The function
 * is onwy usefuw when the intewface is associated, othewwise it wiww wetuwn
 * %NUWW.
 *
 * Wetuwn: The Pwobe Wequest tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_ap_pwobeweq_get(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif);

/**
 * ieee80211_beacon_woss - infowm hawdwawe does not weceive beacons
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * When beacon fiwtewing is enabwed with %IEEE80211_VIF_BEACON_FIWTEW and
 * %IEEE80211_CONF_PS is set, the dwivew needs to infowm whenevew the
 * hawdwawe is not weceiving beacons with this function.
 */
void ieee80211_beacon_woss(stwuct ieee80211_vif *vif);

/**
 * ieee80211_connection_woss - infowm hawdwawe has wost connection to the AP
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * When beacon fiwtewing is enabwed with %IEEE80211_VIF_BEACON_FIWTEW, and
 * %IEEE80211_CONF_PS and %IEEE80211_HW_CONNECTION_MONITOW awe set, the dwivew
 * needs to infowm if the connection to the AP has been wost.
 * The function may awso be cawwed if the connection needs to be tewminated
 * fow some othew weason, even if %IEEE80211_HW_CONNECTION_MONITOW isn't set.
 *
 * This function wiww cause immediate change to disassociated state,
 * without connection wecovewy attempts.
 */
void ieee80211_connection_woss(stwuct ieee80211_vif *vif);

/**
 * ieee80211_disconnect - wequest disconnection
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @weconnect: immediate weconnect is desiwed
 *
 * Wequest disconnection fwom the cuwwent netwowk and, if enabwed, send a
 * hint to the highew wayews that immediate weconnect is desiwed.
 */
void ieee80211_disconnect(stwuct ieee80211_vif *vif, boow weconnect);

/**
 * ieee80211_wesume_disconnect - disconnect fwom AP aftew wesume
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Instwucts mac80211 to disconnect fwom the AP aftew wesume.
 * Dwivews can use this aftew WoWWAN if they know that the
 * connection cannot be kept up, fow exampwe because keys wewe
 * used whiwe the device was asweep but the wepway countews ow
 * simiwaw cannot be wetwieved fwom the device duwing wesume.
 *
 * Note that due to impwementation issues, if the dwivew uses
 * the weconfiguwation functionawity duwing wesume the intewface
 * wiww stiww be added as associated fiwst duwing wesume and then
 * disconnect nowmawwy watew.
 *
 * This function can onwy be cawwed fwom the wesume cawwback and
 * the dwivew must not be howding any of its own wocks whiwe it
 * cawws this function, ow at weast not any wocks it needs in the
 * key configuwation paths (if it suppowts HW cwypto).
 */
void ieee80211_wesume_disconnect(stwuct ieee80211_vif *vif);

/**
 * ieee80211_hw_westawt_disconnect - disconnect fwom AP aftew
 * hawdwawe westawt
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * Instwucts mac80211 to disconnect fwom the AP aftew
 * hawdwawe westawt.
 */
void ieee80211_hw_westawt_disconnect(stwuct ieee80211_vif *vif);

/**
 * ieee80211_cqm_wssi_notify - infowm a configuwed connection quawity monitowing
 *	wssi thweshowd twiggewed
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wssi_event: the WSSI twiggew event type
 * @wssi_wevew: new WSSI wevew vawue ow 0 if not avaiwabwe
 * @gfp: context fwags
 *
 * When the %IEEE80211_VIF_SUPPOWTS_CQM_WSSI is set, and a connection quawity
 * monitowing is configuwed with an wssi thweshowd, the dwivew wiww infowm
 * whenevew the wssi wevew weaches the thweshowd.
 */
void ieee80211_cqm_wssi_notify(stwuct ieee80211_vif *vif,
			       enum nw80211_cqm_wssi_thweshowd_event wssi_event,
			       s32 wssi_wevew,
			       gfp_t gfp);

/**
 * ieee80211_cqm_beacon_woss_notify - infowm CQM of beacon woss
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @gfp: context fwags
 */
void ieee80211_cqm_beacon_woss_notify(stwuct ieee80211_vif *vif, gfp_t gfp);

/**
 * ieee80211_wadaw_detected - infowm that a wadaw was detected
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 */
void ieee80211_wadaw_detected(stwuct ieee80211_hw *hw);

/**
 * ieee80211_chswitch_done - Compwete channew switch pwocess
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @success: make the channew switch successfuw ow not
 * @wink_id: the wink_id on which the switch was done. Ignowed if success is
 *	fawse.
 *
 * Compwete the channew switch post-pwocess: set the new opewationaw channew
 * and wake up the suspended queues.
 */
void ieee80211_chswitch_done(stwuct ieee80211_vif *vif, boow success,
			     unsigned int wink_id);

/**
 * ieee80211_channew_switch_disconnect - disconnect due to channew switch ewwow
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @bwock_tx: if %twue, do not send deauth fwame.
 *
 * Instwuct mac80211 to disconnect due to a channew switch ewwow. The channew
 * switch can wequest to bwock the tx and so, we need to make suwe we do not send
 * a deauth fwame in this case.
 */
void ieee80211_channew_switch_disconnect(stwuct ieee80211_vif *vif,
					 boow bwock_tx);

/**
 * ieee80211_wequest_smps - wequest SM PS twansition
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wink_id: wink ID fow MWO, ow 0
 * @smps_mode: new SM PS mode
 *
 * This awwows the dwivew to wequest an SM PS twansition in managed
 * mode. This is usefuw when the dwivew has mowe infowmation than
 * the stack about possibwe intewfewence, fow exampwe by bwuetooth.
 */
void ieee80211_wequest_smps(stwuct ieee80211_vif *vif, unsigned int wink_id,
			    enum ieee80211_smps_mode smps_mode);

/**
 * ieee80211_weady_on_channew - notification of wemain-on-channew stawt
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 */
void ieee80211_weady_on_channew(stwuct ieee80211_hw *hw);

/**
 * ieee80211_wemain_on_channew_expiwed - wemain_on_channew duwation expiwed
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 */
void ieee80211_wemain_on_channew_expiwed(stwuct ieee80211_hw *hw);

/**
 * ieee80211_stop_wx_ba_session - cawwback to stop existing BA sessions
 *
 * in owdew not to hawm the system pewfowmance and usew expewience, the device
 * may wequest not to awwow any wx ba session and teaw down existing wx ba
 * sessions based on system constwaints such as pewiodic BT activity that needs
 * to wimit wwan activity (eg.sco ow a2dp)."
 * in such cases, the intention is to wimit the duwation of the wx ppdu and
 * thewefowe pwevent the peew device to use a-mpdu aggwegation.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @ba_wx_bitmap: Bit map of open wx ba pew tid
 * @addw: & to bssid mac addwess
 */
void ieee80211_stop_wx_ba_session(stwuct ieee80211_vif *vif, u16 ba_wx_bitmap,
				  const u8 *addw);

/**
 * ieee80211_mawk_wx_ba_fiwtewed_fwames - move WX BA window and mawk fiwtewed
 * @pubsta: station stwuct
 * @tid: the session's TID
 * @ssn: stawting sequence numbew of the bitmap, aww fwames befowe this awe
 *	assumed to be out of the window aftew the caww
 * @fiwtewed: bitmap of fiwtewed fwames, BIT(0) is the @ssn entwy etc.
 * @weceived_mpdus: numbew of weceived mpdus in fiwmwawe
 *
 * This function moves the BA window and weweases aww fwames befowe @ssn, and
 * mawks fwames mawked in the bitmap as having been fiwtewed. Aftewwawds, it
 * checks if any fwames in the window stawting fwom @ssn can now be weweased
 * (in case they wewe onwy waiting fow fwames that wewe fiwtewed.)
 * (Onwy wowk cowwectwy if @max_wx_aggwegation_subfwames <= 64 fwames)
 */
void ieee80211_mawk_wx_ba_fiwtewed_fwames(stwuct ieee80211_sta *pubsta, u8 tid,
					  u16 ssn, u64 fiwtewed,
					  u16 weceived_mpdus);

/**
 * ieee80211_send_baw - send a BwockAckWeq fwame
 *
 * can be used to fwush pending fwames fwom the peew's aggwegation weowdew
 * buffew.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @wa: the peew's destination addwess
 * @tid: the TID of the aggwegation session
 * @ssn: the new stawting sequence numbew fow the weceivew
 */
void ieee80211_send_baw(stwuct ieee80211_vif *vif, u8 *wa, u16 tid, u16 ssn);

/**
 * ieee80211_manage_wx_ba_offw - hewpew to queue an WX BA wowk
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @addw: station mac addwess
 * @tid: the wx tid
 */
void ieee80211_manage_wx_ba_offw(stwuct ieee80211_vif *vif, const u8 *addw,
				 unsigned int tid);

/**
 * ieee80211_stawt_wx_ba_session_offw - stawt a Wx BA session
 *
 * Some device dwivews may offwoad pawt of the Wx aggwegation fwow incwuding
 * AddBa/DewBa negotiation but may othewwise be incapabwe of fuww Wx
 * weowdewing.
 *
 * Cweate stwuctuwes wesponsibwe fow weowdewing so device dwivews may caww hewe
 * when they compwete AddBa negotiation.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @addw: station mac addwess
 * @tid: the wx tid
 */
static inwine void ieee80211_stawt_wx_ba_session_offw(stwuct ieee80211_vif *vif,
						      const u8 *addw, u16 tid)
{
	if (WAWN_ON(tid >= IEEE80211_NUM_TIDS))
		wetuwn;
	ieee80211_manage_wx_ba_offw(vif, addw, tid);
}

/**
 * ieee80211_stop_wx_ba_session_offw - stop a Wx BA session
 *
 * Some device dwivews may offwoad pawt of the Wx aggwegation fwow incwuding
 * AddBa/DewBa negotiation but may othewwise be incapabwe of fuww Wx
 * weowdewing.
 *
 * Destwoy stwuctuwes wesponsibwe fow weowdewing so device dwivews may caww hewe
 * when they compwete DewBa negotiation.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @addw: station mac addwess
 * @tid: the wx tid
 */
static inwine void ieee80211_stop_wx_ba_session_offw(stwuct ieee80211_vif *vif,
						     const u8 *addw, u16 tid)
{
	if (WAWN_ON(tid >= IEEE80211_NUM_TIDS))
		wetuwn;
	ieee80211_manage_wx_ba_offw(vif, addw, tid + IEEE80211_NUM_TIDS);
}

/**
 * ieee80211_wx_ba_timew_expiwed - stop a Wx BA session due to timeout
 *
 * Some device dwivews do not offwoad AddBa/DewBa negotiation, but handwe wx
 * buffew weowding intewnawwy, and thewefowe awso handwe the session timew.
 *
 * Twiggew the timeout fwow, which sends a DewBa.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback
 * @addw: station mac addwess
 * @tid: the wx tid
 */
void ieee80211_wx_ba_timew_expiwed(stwuct ieee80211_vif *vif,
				   const u8 *addw, unsigned int tid);

/* Wate contwow API */

/**
 * stwuct ieee80211_tx_wate_contwow - wate contwow infowmation fow/fwom WC awgo
 *
 * @hw: The hawdwawe the awgowithm is invoked fow.
 * @sband: The band this fwame is being twansmitted on.
 * @bss_conf: the cuwwent BSS configuwation
 * @skb: the skb that wiww be twansmitted, the contwow infowmation in it needs
 *	to be fiwwed in
 * @wepowted_wate: The wate contwow awgowithm can fiww this in to indicate
 *	which wate shouwd be wepowted to usewspace as the cuwwent wate and
 *	used fow wate cawcuwations in the mesh netwowk.
 * @wts: whethew WTS wiww be used fow this fwame because it is wongew than the
 *	WTS thweshowd
 * @showt_pweambwe: whethew mac80211 wiww wequest showt-pweambwe twansmission
 *	if the sewected wate suppowts it
 * @wate_idx_mask: usew-wequested (wegacy) wate mask
 * @wate_idx_mcs_mask: usew-wequested MCS wate mask (NUWW if not in use)
 * @bss: whethew this fwame is sent out in AP ow IBSS mode
 */
stwuct ieee80211_tx_wate_contwow {
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_bss_conf *bss_conf;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_wate wepowted_wate;
	boow wts, showt_pweambwe;
	u32 wate_idx_mask;
	u8 *wate_idx_mcs_mask;
	boow bss;
};

/**
 * enum wate_contwow_capabiwities - wate contwow capabiwities
 */
enum wate_contwow_capabiwities {
	/**
	 * @WATE_CTWW_CAPA_VHT_EXT_NSS_BW:
	 * Suppowt fow extended NSS BW suppowt (dot11VHTExtendedNSSCapabwe)
	 * Note that this is onwy wooked at if the minimum numbew of chains
	 * that the AP uses is < the numbew of TX chains the hawdwawe has,
	 * othewwise the NSS diffewence doesn't bothew us.
	 */
	WATE_CTWW_CAPA_VHT_EXT_NSS_BW = BIT(0),
	/**
	 * @WATE_CTWW_CAPA_AMPDU_TWIGGEW:
	 * mac80211 shouwd stawt A-MPDU sessions on tx
	 */
	WATE_CTWW_CAPA_AMPDU_TWIGGEW = BIT(1),
};

stwuct wate_contwow_ops {
	unsigned wong capa;
	const chaw *name;
	void *(*awwoc)(stwuct ieee80211_hw *hw);
	void (*add_debugfs)(stwuct ieee80211_hw *hw, void *pwiv,
			    stwuct dentwy *debugfsdiw);
	void (*fwee)(void *pwiv);

	void *(*awwoc_sta)(void *pwiv, stwuct ieee80211_sta *sta, gfp_t gfp);
	void (*wate_init)(void *pwiv, stwuct ieee80211_suppowted_band *sband,
			  stwuct cfg80211_chan_def *chandef,
			  stwuct ieee80211_sta *sta, void *pwiv_sta);
	void (*wate_update)(void *pwiv, stwuct ieee80211_suppowted_band *sband,
			    stwuct cfg80211_chan_def *chandef,
			    stwuct ieee80211_sta *sta, void *pwiv_sta,
			    u32 changed);
	void (*fwee_sta)(void *pwiv, stwuct ieee80211_sta *sta,
			 void *pwiv_sta);

	void (*tx_status_ext)(void *pwiv,
			      stwuct ieee80211_suppowted_band *sband,
			      void *pwiv_sta, stwuct ieee80211_tx_status *st);
	void (*tx_status)(void *pwiv, stwuct ieee80211_suppowted_band *sband,
			  stwuct ieee80211_sta *sta, void *pwiv_sta,
			  stwuct sk_buff *skb);
	void (*get_wate)(void *pwiv, stwuct ieee80211_sta *sta, void *pwiv_sta,
			 stwuct ieee80211_tx_wate_contwow *txwc);

	void (*add_sta_debugfs)(void *pwiv, void *pwiv_sta,
				stwuct dentwy *diw);

	u32 (*get_expected_thwoughput)(void *pwiv_sta);
};

static inwine int wate_suppowted(stwuct ieee80211_sta *sta,
				 enum nw80211_band band,
				 int index)
{
	wetuwn (sta == NUWW || sta->defwink.supp_wates[band] & BIT(index));
}

static inwine s8
wate_wowest_index(stwuct ieee80211_suppowted_band *sband,
		  stwuct ieee80211_sta *sta)
{
	int i;

	fow (i = 0; i < sband->n_bitwates; i++)
		if (wate_suppowted(sta, sband->band, i))
			wetuwn i;

	/* wawn when we cannot find a wate. */
	WAWN_ON_ONCE(1);

	/* and wetuwn 0 (the wowest index) */
	wetuwn 0;
}

static inwine
boow wate_usabwe_index_exists(stwuct ieee80211_suppowted_band *sband,
			      stwuct ieee80211_sta *sta)
{
	unsigned int i;

	fow (i = 0; i < sband->n_bitwates; i++)
		if (wate_suppowted(sta, sband->band, i))
			wetuwn twue;
	wetuwn fawse;
}

/**
 * wate_contwow_set_wates - pass the sta wate sewection to mac80211/dwivew
 *
 * When not doing a wate contwow pwobe to test wates, wate contwow shouwd pass
 * its wate sewection to mac80211. If the dwivew suppowts weceiving a station
 * wate tabwe, it wiww use it to ensuwe that fwames awe awways sent based on
 * the most wecent wate contwow moduwe decision.
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @pubsta: &stwuct ieee80211_sta pointew to the tawget destination.
 * @wates: new tx wate set to be used fow this station.
 */
int wate_contwow_set_wates(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_sta *pubsta,
			   stwuct ieee80211_sta_wates *wates);

int ieee80211_wate_contwow_wegistew(const stwuct wate_contwow_ops *ops);
void ieee80211_wate_contwow_unwegistew(const stwuct wate_contwow_ops *ops);

static inwine boow
conf_is_ht20(stwuct ieee80211_conf *conf)
{
	wetuwn conf->chandef.width == NW80211_CHAN_WIDTH_20;
}

static inwine boow
conf_is_ht40_minus(stwuct ieee80211_conf *conf)
{
	wetuwn conf->chandef.width == NW80211_CHAN_WIDTH_40 &&
	       conf->chandef.centew_fweq1 < conf->chandef.chan->centew_fweq;
}

static inwine boow
conf_is_ht40_pwus(stwuct ieee80211_conf *conf)
{
	wetuwn conf->chandef.width == NW80211_CHAN_WIDTH_40 &&
	       conf->chandef.centew_fweq1 > conf->chandef.chan->centew_fweq;
}

static inwine boow
conf_is_ht40(stwuct ieee80211_conf *conf)
{
	wetuwn conf->chandef.width == NW80211_CHAN_WIDTH_40;
}

static inwine boow
conf_is_ht(stwuct ieee80211_conf *conf)
{
	wetuwn (conf->chandef.width != NW80211_CHAN_WIDTH_5) &&
		(conf->chandef.width != NW80211_CHAN_WIDTH_10) &&
		(conf->chandef.width != NW80211_CHAN_WIDTH_20_NOHT);
}

static inwine enum nw80211_iftype
ieee80211_iftype_p2p(enum nw80211_iftype type, boow p2p)
{
	if (p2p) {
		switch (type) {
		case NW80211_IFTYPE_STATION:
			wetuwn NW80211_IFTYPE_P2P_CWIENT;
		case NW80211_IFTYPE_AP:
			wetuwn NW80211_IFTYPE_P2P_GO;
		defauwt:
			bweak;
		}
	}
	wetuwn type;
}

static inwine enum nw80211_iftype
ieee80211_vif_type_p2p(stwuct ieee80211_vif *vif)
{
	wetuwn ieee80211_iftype_p2p(vif->type, vif->p2p);
}

/**
 * ieee80211_get_he_iftype_cap_vif - wetuwn HE capabiwities fow sband/vif
 * @sband: the sband to seawch fow the iftype on
 * @vif: the vif to get the iftype fwom
 *
 * Wetuwn: pointew to the stwuct ieee80211_sta_he_cap, ow %NUWW is none found
 */
static inwine const stwuct ieee80211_sta_he_cap *
ieee80211_get_he_iftype_cap_vif(const stwuct ieee80211_suppowted_band *sband,
				stwuct ieee80211_vif *vif)
{
	wetuwn ieee80211_get_he_iftype_cap(sband, ieee80211_vif_type_p2p(vif));
}

/**
 * ieee80211_get_he_6ghz_capa_vif - wetuwn HE 6 GHz capabiwities
 * @sband: the sband to seawch fow the STA on
 * @vif: the vif to get the iftype fwom
 *
 * Wetuwn: the 6GHz capabiwities
 */
static inwine __we16
ieee80211_get_he_6ghz_capa_vif(const stwuct ieee80211_suppowted_band *sband,
			       stwuct ieee80211_vif *vif)
{
	wetuwn ieee80211_get_he_6ghz_capa(sband, ieee80211_vif_type_p2p(vif));
}

/**
 * ieee80211_get_eht_iftype_cap_vif - wetuwn ETH capabiwities fow sband/vif
 * @sband: the sband to seawch fow the iftype on
 * @vif: the vif to get the iftype fwom
 *
 * Wetuwn: pointew to the stwuct ieee80211_sta_eht_cap, ow %NUWW is none found
 */
static inwine const stwuct ieee80211_sta_eht_cap *
ieee80211_get_eht_iftype_cap_vif(const stwuct ieee80211_suppowted_band *sband,
				 stwuct ieee80211_vif *vif)
{
	wetuwn ieee80211_get_eht_iftype_cap(sband, ieee80211_vif_type_p2p(vif));
}

/**
 * ieee80211_update_mu_gwoups - set the VHT MU-MIMO gwoud data
 *
 * @vif: the specified viwtuaw intewface
 * @wink_id: the wink ID fow MWO, othewwise 0
 * @membewship: 64 bits awway - a bit is set if station is membew of the gwoup
 * @position: 2 bits pew gwoup id indicating the position in the gwoup
 *
 * Note: This function assumes that the given vif is vawid and the position and
 * membewship data is of the cowwect size and awe in the same byte owdew as the
 * matching GwoupId management fwame.
 * Cawws to this function need to be sewiawized with WX path.
 */
void ieee80211_update_mu_gwoups(stwuct ieee80211_vif *vif, unsigned int wink_id,
				const u8 *membewship, const u8 *position);

void ieee80211_enabwe_wssi_wepowts(stwuct ieee80211_vif *vif,
				   int wssi_min_thowd,
				   int wssi_max_thowd);

void ieee80211_disabwe_wssi_wepowts(stwuct ieee80211_vif *vif);

/**
 * ieee80211_ave_wssi - wepowt the avewage WSSI fow the specified intewface
 *
 * @vif: the specified viwtuaw intewface
 *
 * Note: This function assumes that the given vif is vawid.
 *
 * Wetuwn: The avewage WSSI vawue fow the wequested intewface, ow 0 if not
 * appwicabwe.
 */
int ieee80211_ave_wssi(stwuct ieee80211_vif *vif);

/**
 * ieee80211_wepowt_wowwan_wakeup - wepowt WoWWAN wakeup
 * @vif: viwtuaw intewface
 * @wakeup: wakeup weason(s)
 * @gfp: awwocation fwags
 *
 * See cfg80211_wepowt_wowwan_wakeup().
 */
void ieee80211_wepowt_wowwan_wakeup(stwuct ieee80211_vif *vif,
				    stwuct cfg80211_wowwan_wakeup *wakeup,
				    gfp_t gfp);

/**
 * ieee80211_tx_pwepawe_skb - pwepawe an 802.11 skb fow twansmission
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @vif: viwtuaw intewface
 * @skb: fwame to be sent fwom within the dwivew
 * @band: the band to twansmit on
 * @sta: optionaw pointew to get the station to send the fwame to
 *
 * Note: must be cawwed undew WCU wock
 */
boow ieee80211_tx_pwepawe_skb(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif, stwuct sk_buff *skb,
			      int band, stwuct ieee80211_sta **sta);

/**
 * ieee80211_pawse_tx_wadiotap - Sanity-check and pawse the wadiotap headew
 *				 of injected fwames.
 *
 * To accuwatewy pawse and take into account wate and wetwansmission fiewds,
 * you must initiawize the chandef fiewd in the ieee80211_tx_info stwuctuwe
 * of the skb befowe cawwing this function.
 *
 * @skb: packet injected by usewspace
 * @dev: the &stwuct device of this 802.11 device
 */
boow ieee80211_pawse_tx_wadiotap(stwuct sk_buff *skb,
				 stwuct net_device *dev);

/**
 * stwuct ieee80211_noa_data - howds tempowawy data fow twacking P2P NoA state
 *
 * @next_tsf: TSF timestamp of the next absent state change
 * @has_next_tsf: next absent state change event pending
 *
 * @absent: descwiptow bitmask, set if GO is cuwwentwy absent
 *
 * pwivate:
 *
 * @count: count fiewds fwom the NoA descwiptows
 * @desc: adjusted data fwom the NoA
 */
stwuct ieee80211_noa_data {
	u32 next_tsf;
	boow has_next_tsf;

	u8 absent;

	u8 count[IEEE80211_P2P_NOA_DESC_MAX];
	stwuct {
		u32 stawt;
		u32 duwation;
		u32 intewvaw;
	} desc[IEEE80211_P2P_NOA_DESC_MAX];
};

/**
 * ieee80211_pawse_p2p_noa - initiawize NoA twacking data fwom P2P IE
 *
 * @attw: P2P NoA IE
 * @data: NoA twacking data
 * @tsf: cuwwent TSF timestamp
 *
 * Wetuwn: numbew of successfuwwy pawsed descwiptows
 */
int ieee80211_pawse_p2p_noa(const stwuct ieee80211_p2p_noa_attw *attw,
			    stwuct ieee80211_noa_data *data, u32 tsf);

/**
 * ieee80211_update_p2p_noa - get next pending P2P GO absent state change
 *
 * @data: NoA twacking data
 * @tsf: cuwwent TSF timestamp
 */
void ieee80211_update_p2p_noa(stwuct ieee80211_noa_data *data, u32 tsf);

/**
 * ieee80211_tdws_opew_wequest - wequest usewspace to pewfowm a TDWS opewation
 * @vif: viwtuaw intewface
 * @peew: the peew's destination addwess
 * @opew: the wequested TDWS opewation
 * @weason_code: weason code fow the opewation, vawid fow TDWS teawdown
 * @gfp: awwocation fwags
 *
 * See cfg80211_tdws_opew_wequest().
 */
void ieee80211_tdws_opew_wequest(stwuct ieee80211_vif *vif, const u8 *peew,
				 enum nw80211_tdws_opewation opew,
				 u16 weason_code, gfp_t gfp);

/**
 * ieee80211_wesewve_tid - wequest to wesewve a specific TID
 *
 * Thewe is sometimes a need (such as in TDWS) fow bwocking the dwivew fwom
 * using a specific TID so that the FW can use it fow cewtain opewations such
 * as sending PTI wequests. To make suwe that the dwivew doesn't use that TID,
 * this function must be cawwed as it fwushes out packets on this TID and mawks
 * it as bwocked, so that any twansmit fow the station on this TID wiww be
 * wediwected to the awtewnative TID in the same AC.
 *
 * Note that this function bwocks and may caww back into the dwivew, so it
 * shouwd be cawwed without dwivew wocks hewd. Awso note this function shouwd
 * onwy be cawwed fwom the dwivew's @sta_state cawwback.
 *
 * @sta: the station to wesewve the TID fow
 * @tid: the TID to wesewve
 *
 * Wetuwns: 0 on success, ewse on faiwuwe
 */
int ieee80211_wesewve_tid(stwuct ieee80211_sta *sta, u8 tid);

/**
 * ieee80211_unwesewve_tid - wequest to unwesewve a specific TID
 *
 * Once thewe is no wongew any need fow wesewving a cewtain TID, this function
 * shouwd be cawwed, and no wongew wiww packets have theiw TID modified fow
 * pweventing use of this TID in the dwivew.
 *
 * Note that this function bwocks and acquiwes a wock, so it shouwd be cawwed
 * without dwivew wocks hewd. Awso note this function shouwd onwy be cawwed
 * fwom the dwivew's @sta_state cawwback.
 *
 * @sta: the station
 * @tid: the TID to unwesewve
 */
void ieee80211_unwesewve_tid(stwuct ieee80211_sta *sta, u8 tid);

/**
 * ieee80211_tx_dequeue - dequeue a packet fwom a softwawe tx queue
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface, ow fwom
 *	ieee80211_next_txq()
 *
 * Wetuwns the skb if successfuw, %NUWW if no fwame was avaiwabwe.
 *
 * Note that this must be cawwed in an wcu_wead_wock() cwiticaw section,
 * which can onwy be weweased aftew the SKB was handwed. Some pointews in
 * skb->cb, e.g. the key pointew, awe pwotected by WCU and thus the
 * cwiticaw section must pewsist not just fow the duwation of this caww
 * but fow the duwation of the fwame handwing.
 * Howevew, awso note that whiwe in the wake_tx_queue() method,
 * wcu_wead_wock() is awweady hewd.
 *
 * softiwqs must awso be disabwed when this function is cawwed.
 * In pwocess context, use ieee80211_tx_dequeue_ni() instead.
 */
stwuct sk_buff *ieee80211_tx_dequeue(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_txq *txq);

/**
 * ieee80211_tx_dequeue_ni - dequeue a packet fwom a softwawe tx queue
 * (in pwocess context)
 *
 * Wike ieee80211_tx_dequeue() but can be cawwed in pwocess context
 * (intewnawwy disabwes bottom hawves).
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface, ow fwom
 *	ieee80211_next_txq()
 */
static inwine stwuct sk_buff *ieee80211_tx_dequeue_ni(stwuct ieee80211_hw *hw,
						      stwuct ieee80211_txq *txq)
{
	stwuct sk_buff *skb;

	wocaw_bh_disabwe();
	skb = ieee80211_tx_dequeue(hw, txq);
	wocaw_bh_enabwe();

	wetuwn skb;
}

/**
 * ieee80211_handwe_wake_tx_queue - mac80211 handwew fow wake_tx_queue cawwback
 *
 * @hw: pointew as obtained fwom wake_tx_queue() cawwback().
 * @txq: pointew as obtained fwom wake_tx_queue() cawwback().
 *
 * Dwivews can use this function fow the mandatowy mac80211 wake_tx_queue
 * cawwback in stwuct ieee80211_ops. They shouwd not caww this function.
 */
void ieee80211_handwe_wake_tx_queue(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_txq *txq);

/**
 * ieee80211_next_txq - get next tx queue to puww packets fwom
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @ac: AC numbew to wetuwn packets fwom.
 *
 * Wetuwns the next txq if successfuw, %NUWW if no queue is ewigibwe. If a txq
 * is wetuwned, it shouwd be wetuwned with ieee80211_wetuwn_txq() aftew the
 * dwivew has finished scheduwing it.
 */
stwuct ieee80211_txq *ieee80211_next_txq(stwuct ieee80211_hw *hw, u8 ac);

/**
 * ieee80211_txq_scheduwe_stawt - stawt new scheduwing wound fow TXQs
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @ac: AC numbew to acquiwe wocks fow
 *
 * Shouwd be cawwed befowe ieee80211_next_txq() ow ieee80211_wetuwn_txq().
 * The dwivew must not caww muwtipwe TXQ scheduwing wounds concuwwentwy.
 */
void ieee80211_txq_scheduwe_stawt(stwuct ieee80211_hw *hw, u8 ac);

/* (depwecated) */
static inwine void ieee80211_txq_scheduwe_end(stwuct ieee80211_hw *hw, u8 ac)
{
}

void __ieee80211_scheduwe_txq(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_txq *txq, boow fowce);

/**
 * ieee80211_scheduwe_txq - scheduwe a TXQ fow twansmission
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface
 *
 * Scheduwes a TXQ fow twansmission if it is not awweady scheduwed,
 * even if mac80211 does not have any packets buffewed.
 *
 * The dwivew may caww this function if it has buffewed packets fow
 * this TXQ intewnawwy.
 */
static inwine void
ieee80211_scheduwe_txq(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *txq)
{
	__ieee80211_scheduwe_txq(hw, txq, twue);
}

/**
 * ieee80211_wetuwn_txq - wetuwn a TXQ pweviouswy acquiwed by ieee80211_next_txq()
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface
 * @fowce: scheduwe txq even if mac80211 does not have any buffewed packets.
 *
 * The dwivew may set fowce=twue if it has buffewed packets fow this TXQ
 * intewnawwy.
 */
static inwine void
ieee80211_wetuwn_txq(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *txq,
		     boow fowce)
{
	__ieee80211_scheduwe_txq(hw, txq, fowce);
}

/**
 * ieee80211_txq_may_twansmit - check whethew TXQ is awwowed to twansmit
 *
 * This function is used to check whethew given txq is awwowed to twansmit by
 * the aiwtime scheduwew, and can be used by dwivews to access the aiwtime
 * faiwness accounting without using the scheduwing owdew enfowced by
 * next_txq().
 *
 * Wetuwns %twue if the aiwtime scheduwew thinks the TXQ shouwd be awwowed to
 * twansmit, and %fawse if it shouwd be thwottwed. This function can awso have
 * the side effect of wotating the TXQ in the scheduwew wotation, which wiww
 * eventuawwy bwing the deficit to positive and awwow the station to twansmit
 * again.
 *
 * The API ieee80211_txq_may_twansmit() awso ensuwes that TXQ wist wiww be
 * awigned against dwivew's own wound-wobin scheduwew wist. i.e it wotates
 * the TXQ wist tiww it makes the wequested node becomes the fiwst entwy
 * in TXQ wist. Thus both the TXQ wist and dwivew's wist awe in sync. If this
 * function wetuwns %twue, the dwivew is expected to scheduwe packets
 * fow twansmission, and then wetuwn the TXQ thwough ieee80211_wetuwn_txq().
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @txq: pointew obtained fwom station ow viwtuaw intewface
 */
boow ieee80211_txq_may_twansmit(stwuct ieee80211_hw *hw,
				stwuct ieee80211_txq *txq);

/**
 * ieee80211_txq_get_depth - get pending fwame/byte count of given txq
 *
 * The vawues awe not guawanteed to be cohewent with wegawd to each othew, i.e.
 * txq state can change hawf-way of this function and the cawwew may end up
 * with "new" fwame_cnt and "owd" byte_cnt ow vice-vewsa.
 *
 * @txq: pointew obtained fwom station ow viwtuaw intewface
 * @fwame_cnt: pointew to stowe fwame count
 * @byte_cnt: pointew to stowe byte count
 */
void ieee80211_txq_get_depth(stwuct ieee80211_txq *txq,
			     unsigned wong *fwame_cnt,
			     unsigned wong *byte_cnt);

/**
 * ieee80211_nan_func_tewminated - notify about NAN function tewmination.
 *
 * This function is used to notify mac80211 about NAN function tewmination.
 * Note that this function can't be cawwed fwom hawd iwq.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @inst_id: the wocaw instance id
 * @weason: tewmination weason (one of the NW80211_NAN_FUNC_TEWM_WEASON_*)
 * @gfp: awwocation fwags
 */
void ieee80211_nan_func_tewminated(stwuct ieee80211_vif *vif,
				   u8 inst_id,
				   enum nw80211_nan_func_tewm_weason weason,
				   gfp_t gfp);

/**
 * ieee80211_nan_func_match - notify about NAN function match event.
 *
 * This function is used to notify mac80211 about NAN function match. The
 * cookie inside the match stwuct wiww be assigned by mac80211.
 * Note that this function can't be cawwed fwom hawd iwq.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @match: match event infowmation
 * @gfp: awwocation fwags
 */
void ieee80211_nan_func_match(stwuct ieee80211_vif *vif,
			      stwuct cfg80211_nan_match_pawams *match,
			      gfp_t gfp);

/**
 * ieee80211_cawc_wx_aiwtime - cawcuwate estimated twansmission aiwtime fow WX.
 *
 * This function cawcuwates the estimated aiwtime usage of a fwame based on the
 * wate infowmation in the WX status stwuct and the fwame wength.
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @status: &stwuct ieee80211_wx_status containing the twansmission wate
 *          infowmation.
 * @wen: fwame wength in bytes
 */
u32 ieee80211_cawc_wx_aiwtime(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_wx_status *status,
			      int wen);

/**
 * ieee80211_cawc_tx_aiwtime - cawcuwate estimated twansmission aiwtime fow TX.
 *
 * This function cawcuwates the estimated aiwtime usage of a fwame based on the
 * wate infowmation in the TX info stwuct and the fwame wength.
 *
 * @hw: pointew as obtained fwom ieee80211_awwoc_hw()
 * @info: &stwuct ieee80211_tx_info of the fwame.
 * @wen: fwame wength in bytes
 */
u32 ieee80211_cawc_tx_aiwtime(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_tx_info *info,
			      int wen);
/**
 * ieee80211_set_hw_80211_encap - enabwe hawdwawe encapsuwation offwoading.
 *
 * This function is used to notify mac80211 that a vif can be passed waw 802.3
 * fwames. The dwivew needs to then handwe the 802.11 encapsuwation inside the
 * hawdwawe ow fiwmwawe.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @enabwe: indicate if the featuwe shouwd be tuwned on ow off
 */
boow ieee80211_set_hw_80211_encap(stwuct ieee80211_vif *vif, boow enabwe);

/**
 * ieee80211_get_fiws_discovewy_tmpw - Get FIWS discovewy tempwate.
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * The dwivew is wesponsibwe fow fweeing the wetuwned skb.
 *
 * Wetuwn: FIWS discovewy tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *ieee80211_get_fiws_discovewy_tmpw(stwuct ieee80211_hw *hw,
						  stwuct ieee80211_vif *vif);

/**
 * ieee80211_get_unsow_bcast_pwobe_wesp_tmpw - Get unsowicited bwoadcast
 *	pwobe wesponse tempwate.
 * @hw: pointew obtained fwom ieee80211_awwoc_hw().
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 *
 * The dwivew is wesponsibwe fow fweeing the wetuwned skb.
 *
 * Wetuwn: Unsowicited bwoadcast pwobe wesponse tempwate. %NUWW on ewwow.
 */
stwuct sk_buff *
ieee80211_get_unsow_bcast_pwobe_wesp_tmpw(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif);

/**
 * ieee80211_obss_cowow_cowwision_notify - notify usewwand about a BSS cowow
 * cowwision.
 *
 * @vif: &stwuct ieee80211_vif pointew fwom the add_intewface cawwback.
 * @cowow_bitmap: a 64 bit bitmap wepwesenting the cowows that the wocaw BSS is
 *	awawe of.
 * @gfp: awwocation fwags
 */
void
ieee80211_obss_cowow_cowwision_notify(stwuct ieee80211_vif *vif,
				      u64 cowow_bitmap, gfp_t gfp);

/**
 * ieee80211_is_tx_data - check if fwame is a data fwame
 *
 * The function is used to check if a fwame is a data fwame. Fwames with
 * hawdwawe encapsuwation enabwed awe data fwames.
 *
 * @skb: the fwame to be twansmitted.
 */
static inwine boow ieee80211_is_tx_data(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *) skb->data;

	wetuwn info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP ||
	       ieee80211_is_data(hdw->fwame_contwow);
}

/**
 * ieee80211_set_active_winks - set active winks in cwient mode
 * @vif: intewface to set active winks on
 * @active_winks: the new active winks bitmap
 *
 * Context: Must be cawwed with wiphy mutex hewd; may sweep; cawws
 *	back into the dwivew.
 *
 * This changes the active winks on an intewface. The intewface
 * must be in cwient mode (in AP mode, aww winks awe awways active),
 * and @active_winks must be a subset of the vif's vawid_winks.
 *
 * If a wink is switched off and anothew is switched on at the same
 * time (e.g. active_winks going fwom 0x1 to 0x10) then you wiww get
 * a sequence of cawws wike
 *
 *  - change_vif_winks(0x11)
 *  - unassign_vif_chanctx(wink_id=0)
 *  - change_sta_winks(0x11) fow each affected STA (the AP)
 *    (TDWS connections on now inactive winks shouwd be town down)
 *  - wemove gwoup keys on the owd wink (wink_id 0)
 *  - add new gwoup keys (GTK/IGTK/BIGTK) on the new wink (wink_id 4)
 *  - change_sta_winks(0x10) fow each affected STA (the AP)
 *  - assign_vif_chanctx(wink_id=4)
 *  - change_vif_winks(0x10)
 */
int ieee80211_set_active_winks(stwuct ieee80211_vif *vif, u16 active_winks);

/**
 * ieee80211_set_active_winks_async - asynchwonouswy set active winks
 * @vif: intewface to set active winks on
 * @active_winks: the new active winks bitmap
 *
 * See ieee80211_set_active_winks() fow mowe infowmation, the onwy
 * diffewence hewe is that the wink change is twiggewed async and
 * can be cawwed in any context, but the wink switch wiww onwy be
 * compweted aftew it wetuwns.
 */
void ieee80211_set_active_winks_async(stwuct ieee80211_vif *vif,
				      u16 active_winks);

#endif /* MAC80211_H */
