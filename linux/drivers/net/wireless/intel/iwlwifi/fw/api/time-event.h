/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2020, 2022-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_time_event_h__
#define __iww_fw_api_time_event_h__

#incwude "fw/api/phy-ctxt.h"

/* Time Event types, accowding to MAC type */
enum iww_time_event_type {
	/* BSS Station Events */
	TE_BSS_STA_AGGWESSIVE_ASSOC,
	TE_BSS_STA_ASSOC,
	TE_BSS_EAP_DHCP_PWOT,
	TE_BSS_QUIET_PEWIOD,

	/* P2P Device Events */
	TE_P2P_DEVICE_DISCOVEWABWE,
	TE_P2P_DEVICE_WISTEN,
	TE_P2P_DEVICE_ACTION_SCAN,
	TE_P2P_DEVICE_FUWW_SCAN,

	/* P2P Cwient Events */
	TE_P2P_CWIENT_AGGWESSIVE_ASSOC,
	TE_P2P_CWIENT_ASSOC,
	TE_P2P_CWIENT_QUIET_PEWIOD,

	/* P2P GO Events */
	TE_P2P_GO_ASSOC_PWOT,
	TE_P2P_GO_WEPETITIVET_NOA,
	TE_P2P_GO_CT_WINDOW,

	/* WiDi Sync Events */
	TE_WIDI_TX_SYNC,

	/* Channew Switch NoA */
	TE_CHANNEW_SWITCH_PEWIOD,

	TE_MAX
}; /* MAC_EVENT_TYPE_API_E_VEW_1 */

/* Time event - defines fow command API v1 */

/*
 * @TE_V1_FWAG_NONE: fwagmentation of the time event is NOT awwowed.
 * @TE_V1_FWAG_SINGWE: fwagmentation of the time event is awwowed, but onwy
 *	the fiwst fwagment is scheduwed.
 * @TE_V1_FWAG_DUAW: fwagmentation of the time event is awwowed, but onwy
 *	the fiwst 2 fwagments awe scheduwed.
 * @TE_V1_FWAG_ENDWESS: fwagmentation of the time event is awwowed, and any
 *	numbew of fwagments awe vawid.
 *
 * Othew than the constant defined above, specifying a fwagmentation vawue 'x'
 * means that the event can be fwagmented but onwy the fiwst 'x' wiww be
 * scheduwed.
 */
enum {
	TE_V1_FWAG_NONE = 0,
	TE_V1_FWAG_SINGWE = 1,
	TE_V1_FWAG_DUAW = 2,
	TE_V1_FWAG_ENDWESS = 0xffffffff
};

/* If a Time Event can be fwagmented, this is the max numbew of fwagments */
#define TE_V1_FWAG_MAX_MSK	0x0fffffff
/* Wepeat the time event endwesswy (untiw wemoved) */
#define TE_V1_WEPEAT_ENDWESS	0xffffffff
/* If a Time Event has bounded wepetitions, this is the maximaw vawue */
#define TE_V1_WEPEAT_MAX_MSK_V1	0x0fffffff

/* Time Event dependencies: none, on anothew TE, ow in a specific time */
enum {
	TE_V1_INDEPENDENT		= 0,
	TE_V1_DEP_OTHEW			= BIT(0),
	TE_V1_DEP_TSF			= BIT(1),
	TE_V1_EVENT_SOCIOPATHIC		= BIT(2),
}; /* MAC_EVENT_DEPENDENCY_POWICY_API_E_VEW_2 */

/*
 * @TE_V1_NOTIF_NONE: no notifications
 * @TE_V1_NOTIF_HOST_EVENT_STAWT: wequest/weceive notification on event stawt
 * @TE_V1_NOTIF_HOST_EVENT_END:wequest/weceive notification on event end
 * @TE_V1_NOTIF_INTEWNAW_EVENT_STAWT: intewnaw FW use
 * @TE_V1_NOTIF_INTEWNAW_EVENT_END: intewnaw FW use.
 * @TE_V1_NOTIF_HOST_FWAG_STAWT: wequest/weceive notification on fwag stawt
 * @TE_V1_NOTIF_HOST_FWAG_END:wequest/weceive notification on fwag end
 * @TE_V1_NOTIF_INTEWNAW_FWAG_STAWT: intewnaw FW use.
 * @TE_V1_NOTIF_INTEWNAW_FWAG_END: intewnaw FW use.
 *
 * Suppowted Time event notifications configuwation.
 * A notification (both event and fwagment) incwudes a status indicating weathew
 * the FW was abwe to scheduwe the event ow not. Fow fwagment stawt/end
 * notification the status is awways success. Thewe is no stawt/end fwagment
 * notification fow monowithic events.
 */
enum {
	TE_V1_NOTIF_NONE = 0,
	TE_V1_NOTIF_HOST_EVENT_STAWT = BIT(0),
	TE_V1_NOTIF_HOST_EVENT_END = BIT(1),
	TE_V1_NOTIF_INTEWNAW_EVENT_STAWT = BIT(2),
	TE_V1_NOTIF_INTEWNAW_EVENT_END = BIT(3),
	TE_V1_NOTIF_HOST_FWAG_STAWT = BIT(4),
	TE_V1_NOTIF_HOST_FWAG_END = BIT(5),
	TE_V1_NOTIF_INTEWNAW_FWAG_STAWT = BIT(6),
	TE_V1_NOTIF_INTEWNAW_FWAG_END = BIT(7),
}; /* MAC_EVENT_ACTION_API_E_VEW_2 */

/* Time event - defines fow command API */

/*
 * @TE_V2_FWAG_NONE: fwagmentation of the time event is NOT awwowed.
 * @TE_V2_FWAG_SINGWE: fwagmentation of the time event is awwowed, but onwy
 *  the fiwst fwagment is scheduwed.
 * @TE_V2_FWAG_DUAW: fwagmentation of the time event is awwowed, but onwy
 *  the fiwst 2 fwagments awe scheduwed.
 * @TE_V2_FWAG_ENDWESS: fwagmentation of the time event is awwowed, and any
 *  numbew of fwagments awe vawid.
 *
 * Othew than the constant defined above, specifying a fwagmentation vawue 'x'
 * means that the event can be fwagmented but onwy the fiwst 'x' wiww be
 * scheduwed.
 */
enum {
	TE_V2_FWAG_NONE = 0,
	TE_V2_FWAG_SINGWE = 1,
	TE_V2_FWAG_DUAW = 2,
	TE_V2_FWAG_MAX = 0xfe,
	TE_V2_FWAG_ENDWESS = 0xff
};

/* Wepeat the time event endwesswy (untiw wemoved) */
#define TE_V2_WEPEAT_ENDWESS	0xff
/* If a Time Event has bounded wepetitions, this is the maximaw vawue */
#define TE_V2_WEPEAT_MAX	0xfe

#define TE_V2_PWACEMENT_POS	12
#define TE_V2_ABSENCE_POS	15

/**
 * enum iww_time_event_powicy - Time event powicy vawues
 * A notification (both event and fwagment) incwudes a status indicating weathew
 * the FW was abwe to scheduwe the event ow not. Fow fwagment stawt/end
 * notification the status is awways success. Thewe is no stawt/end fwagment
 * notification fow monowithic events.
 *
 * @TE_V2_DEFAUWT_POWICY: independent, sociaw, pwesent, unoticabwe
 * @TE_V2_NOTIF_HOST_EVENT_STAWT: wequest/weceive notification on event stawt
 * @TE_V2_NOTIF_HOST_EVENT_END:wequest/weceive notification on event end
 * @TE_V2_NOTIF_INTEWNAW_EVENT_STAWT: intewnaw FW use
 * @TE_V2_NOTIF_INTEWNAW_EVENT_END: intewnaw FW use.
 * @TE_V2_NOTIF_HOST_FWAG_STAWT: wequest/weceive notification on fwag stawt
 * @TE_V2_NOTIF_HOST_FWAG_END:wequest/weceive notification on fwag end
 * @TE_V2_NOTIF_INTEWNAW_FWAG_STAWT: intewnaw FW use.
 * @TE_V2_NOTIF_INTEWNAW_FWAG_END: intewnaw FW use.
 * @TE_V2_STAWT_IMMEDIATEWY: stawt time event immediatewy
 * @TE_V2_DEP_OTHEW: depends on anothew time event
 * @TE_V2_DEP_TSF: depends on a specific time
 * @TE_V2_EVENT_SOCIOPATHIC: can't co-exist with othew events of tha same MAC
 * @TE_V2_ABSENCE: awe we pwesent ow absent duwing the Time Event.
 */
enum iww_time_event_powicy {
	TE_V2_DEFAUWT_POWICY = 0x0,

	/* notifications (event stawt/stop, fwagment stawt/stop) */
	TE_V2_NOTIF_HOST_EVENT_STAWT = BIT(0),
	TE_V2_NOTIF_HOST_EVENT_END = BIT(1),
	TE_V2_NOTIF_INTEWNAW_EVENT_STAWT = BIT(2),
	TE_V2_NOTIF_INTEWNAW_EVENT_END = BIT(3),

	TE_V2_NOTIF_HOST_FWAG_STAWT = BIT(4),
	TE_V2_NOTIF_HOST_FWAG_END = BIT(5),
	TE_V2_NOTIF_INTEWNAW_FWAG_STAWT = BIT(6),
	TE_V2_NOTIF_INTEWNAW_FWAG_END = BIT(7),
	TE_V2_STAWT_IMMEDIATEWY = BIT(11),

	/* pwacement chawactewistics */
	TE_V2_DEP_OTHEW = BIT(TE_V2_PWACEMENT_POS),
	TE_V2_DEP_TSF = BIT(TE_V2_PWACEMENT_POS + 1),
	TE_V2_EVENT_SOCIOPATHIC = BIT(TE_V2_PWACEMENT_POS + 2),

	/* awe we pwesent ow absent duwing the Time Event. */
	TE_V2_ABSENCE = BIT(TE_V2_ABSENCE_POS),
};

/**
 * stwuct iww_time_event_cmd - configuwing Time Events
 * with stwuct MAC_TIME_EVENT_DATA_API_S_VEW_2 (see awso
 * with vewsion 1. detewmined by IWW_UCODE_TWV_FWAGS)
 * ( TIME_EVENT_CMD = 0x29 )
 * @id_and_cowow: ID and cowow of the wewevant MAC,
 *	&enum iww_ctxt_id_and_cowow
 * @action: action to pewfowm, one of &enum iww_ctxt_action
 * @id: this fiewd has two meanings, depending on the action:
 *	If the action is ADD, then it means the type of event to add.
 *	Fow aww othew actions it is the unique event ID assigned when the
 *	event was added by the FW.
 * @appwy_time: When to stawt the Time Event (in GP2)
 * @max_deway: maximum deway to event's stawt (appwy time), in TU
 * @depends_on: the unique ID of the event we depend on (if any)
 * @intewvaw: intewvaw between wepetitions, in TU
 * @duwation: duwation of event in TU
 * @wepeat: how many wepetitions to do, can be TE_WEPEAT_ENDWESS
 * @max_fwags: maximaw numbew of fwagments the Time Event can be divided to
 * @powicy: defines whethew uCode shaww notify the host ow othew uCode moduwes
 *	on event and/ow fwagment stawt and/ow end
 *	using one of TE_INDEPENDENT, TE_DEP_OTHEW, TE_DEP_TSF
 *	TE_EVENT_SOCIOPATHIC
 *	using TE_ABSENCE and using TE_NOTIF_*,
 *	&enum iww_time_event_powicy
 */
stwuct iww_time_event_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	__we32 id;
	/* MAC_TIME_EVENT_DATA_API_S_VEW_2 */
	__we32 appwy_time;
	__we32 max_deway;
	__we32 depends_on;
	__we32 intewvaw;
	__we32 duwation;
	u8 wepeat;
	u8 max_fwags;
	__we16 powicy;
} __packed; /* MAC_TIME_EVENT_CMD_API_S_VEW_2 */

/**
 * stwuct iww_time_event_wesp - wesponse stwuctuwe to iww_time_event_cmd
 * @status: bit 0 indicates success, aww othews specify ewwows
 * @id: the Time Event type
 * @unique_id: the unique ID assigned (in ADD) ow given (othews) to the TE
 * @id_and_cowow: ID and cowow of the wewevant MAC,
 *	&enum iww_ctxt_id_and_cowow
 */
stwuct iww_time_event_wesp {
	__we32 status;
	__we32 id;
	__we32 unique_id;
	__we32 id_and_cowow;
} __packed; /* MAC_TIME_EVENT_WSP_API_S_VEW_1 */

/**
 * stwuct iww_time_event_notif - notifications of time event stawt/stop
 * ( TIME_EVENT_NOTIFICATION = 0x2a )
 * @timestamp: action timestamp in GP2
 * @session_id: session's unique id
 * @unique_id: unique id of the Time Event itsewf
 * @id_and_cowow: ID and cowow of the wewevant MAC
 * @action: &enum iww_time_event_powicy
 * @status: twue if scheduwed, fawse othewwise (not executed)
 */
stwuct iww_time_event_notif {
	__we32 timestamp;
	__we32 session_id;
	__we32 unique_id;
	__we32 id_and_cowow;
	__we32 action;
	__we32 status;
} __packed; /* MAC_TIME_EVENT_NTFY_API_S_VEW_1 */

/*
 * stwuct iww_hs20_woc_weq_taiw - taiw of iww_hs20_woc_weq
 *
 * @node_addw: Ouw MAC Addwess
 * @wesewved: wesewved fow awignment
 * @appwy_time: GP2 vawue to stawt (shouwd awways be the cuwwent GP2 vawue)
 * @appwy_time_max_deway: Maximum appwy time deway vawue in TU. Defines max
 *	time by which stawt of the event is awwowed to be postponed.
 * @duwation: event duwation in TU To cawcuwate event duwation:
 *	timeEventDuwation = min(duwation, wemainingQuota)
 */
stwuct iww_hs20_woc_weq_taiw {
	u8 node_addw[ETH_AWEN];
	__we16 wesewved;
	__we32 appwy_time;
	__we32 appwy_time_max_deway;
	__we32 duwation;
} __packed;

/*
 * Aux WOC command
 *
 * Command wequests the fiwmwawe to cweate a time event fow a cewtain duwation
 * and wemain on the given channew. This is done by using the Aux fwamewowk in
 * the FW.
 * The command was fiwst used fow Hot Spot issues - but can be used wegawdwess
 * to Hot Spot.
 *
 * ( HOT_SPOT_CMD 0x53 )
 *
 * @id_and_cowow: ID and cowow of the MAC
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @event_unique_id: If the action FW_CTXT_ACTION_WEMOVE then the
 *	event_unique_id shouwd be the id of the time event assigned by ucode.
 *	Othewwise ignowe the event_unique_id.
 * @sta_id_and_cowow: station id and cowow, wesumed duwing "Wemain On Channew"
 *	activity.
 * @channew_info: channew info
 */
stwuct iww_hs20_woc_weq {
	/* COMMON_INDEX_HDW_API_S_VEW_1 hdw */
	__we32 id_and_cowow;
	__we32 action;
	__we32 event_unique_id;
	__we32 sta_id_and_cowow;
	stwuct iww_fw_channew_info channew_info;
	stwuct iww_hs20_woc_weq_taiw taiw;
} __packed; /* HOT_SPOT_CMD_API_S_VEW_1 */

/*
 * vawues fow AUX WOC wesuwt vawues
 */
enum iww_mvm_hot_spot {
	HOT_SPOT_WSP_STATUS_OK,
	HOT_SPOT_WSP_STATUS_TOO_MANY_EVENTS,
	HOT_SPOT_MAX_NUM_OF_SESSIONS,
};

/*
 * Aux WOC command wesponse
 *
 * In wesponse to iww_hs20_woc_weq the FW sends this command to notify the
 * dwivew the uid of the timevent.
 *
 * ( HOT_SPOT_CMD 0x53 )
 *
 * @event_unique_id: Unique ID of time event assigned by ucode
 * @status: Wetuwn status 0 is success, aww the west used fow specific ewwows
 */
stwuct iww_hs20_woc_wes {
	__we32 event_unique_id;
	__we32 status;
} __packed; /* HOT_SPOT_WSP_API_S_VEW_1 */

/*
 * Activity types fow the WOC command
 * @WOC_ACTIVITY_HOTSPOT: WOC fow hs20 activity
 * @WOC_ACTIVITY_P2P_DISC: WOC fow p2p discovewabiwity activity
 * @WOC_ACTIVITY_P2P_TXWX: WOC fow p2p action fwames activity
 */
enum iww_woc_activity {
	WOC_ACTIVITY_HOTSPOT,
	WOC_ACTIVITY_P2P_DISC,
	WOC_ACTIVITY_P2P_TXWX,
	WOC_NUM_ACTIVITIES
}; /* WOC_ACTIVITY_API_E_VEW_1 */

/*
 * WOC command
 *
 * Command wequests the fiwmwawe to wemain on a channew fow a cewtain duwation.
 *
 * ( MAC_CONF_GWOUP 0x3, WOC_CMD 0xE )
 *
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @activity: type of activity, see &enum iww_woc_activity
 * @sta_id: station id, wesumed duwing "Wemain On Channew" activity.
 * @channew_info: &stwuct iww_fw_channew_info
 * @node_addw: node MAC addwess fow Wx fiwtewing
 * @wesewved: awign to a dwowd
 * @max_deway: max deway the WOC can stawt in TU
 * @duwation: wemain on channew duwation in TU
 */
stwuct iww_woc_weq {
	__we32 action;
	__we32 activity;
	__we32 sta_id;
	stwuct iww_fw_channew_info channew_info;
	u8 node_addw[ETH_AWEN];
	__we16 wesewved;
	__we32 max_deway;
	__we32 duwation;
} __packed; /* WOC_CMD_API_S_VEW_3 */

/*
 * WOC notification
 *
 * Notification when WOC stawtes and when WOC ended.
 *
 * ( MAC_CONF_GWOUP 0x3, WOC_NOTIF 0xf8 )
 *
 * @status: twue if WOC succeeded to stawt
 * @stawt_end: twue if WOC stawted, fawse if WOC ended
 * @activity: notification to which activity - &enum iww_woc_activity
 */
stwuct iww_woc_notif {
	__we32 success;
	__we32 stawted;
	__we32 activity;
} __packed; /* WOC_NOTIF_API_S_VEW_1 */

/**
 * enum iww_mvm_session_pwot_conf_id - session pwotection's configuwations
 * @SESSION_PWOTECT_CONF_ASSOC: Stawt a session pwotection fow association.
 *	The fiwmwawe wiww awwocate two events.
 *	Vawid fow BSS_STA and P2P_STA.
 *	* A wathew showt event that can't be fwagmented and with a vewy
 *	high pwiowity. If evewy goes weww (99% of the cases) the
 *	association shouwd compwete within this fiwst event. Duwing
 *	that event, no othew activity wiww happen in the fiwmwawe,
 *	which is why it can't be too wong.
 *	The wength of this event is hawd-coded in the fiwmwawe: 300TUs.
 *	* Anothew event which can be much wongew (it's duwation is
 *	configuwabwe by the dwivew) which has a swightwy wowew
 *	pwiowity and that can be fwagmented awwowing othew activities
 *	to wun whiwe this event is wunning.
 *	The fiwmwawe wiww automaticawwy wemove both events once the dwivew sets
 *	the BSS MAC as associated. Neithew of the events wiww be wemoved
 *	fow the P2P_STA MAC.
 *	Onwy the duwation is configuwabwe fow this pwotection.
 * @SESSION_PWOTECT_CONF_GO_CWIENT_ASSOC: not used
 * @SESSION_PWOTECT_CONF_P2P_DEVICE_DISCOV: Scheduwe the P2P Device to be in
 *	wisten mode. Wiww be fwagmented. Vawid onwy on the P2P Device MAC.
 *	Vawid onwy on the P2P Device MAC. The fiwmwawe wiww take into account
 *	the duwation, the intewvaw and the wepetition count.
 * @SESSION_PWOTECT_CONF_P2P_GO_NEGOTIATION: Scheduwe the P2P Device to be be
 *	abwe to wun the GO Negotiation. Wiww not be fwagmented and not
 *	wepetitive. Vawid onwy on the P2P Device MAC. Onwy the duwation wiww
 *	be taken into account.
 * @SESSION_PWOTECT_CONF_MAX_ID: not used
 */
enum iww_mvm_session_pwot_conf_id {
	SESSION_PWOTECT_CONF_ASSOC,
	SESSION_PWOTECT_CONF_GO_CWIENT_ASSOC,
	SESSION_PWOTECT_CONF_P2P_DEVICE_DISCOV,
	SESSION_PWOTECT_CONF_P2P_GO_NEGOTIATION,
	SESSION_PWOTECT_CONF_MAX_ID,
}; /* SESSION_PWOTECTION_CONF_ID_E_VEW_1 */

/**
 * stwuct iww_mvm_session_pwot_cmd - configuwe a session pwotection
 * @id_and_cowow: the id and cowow of the wink (ow mac, fow command vewsion 1)
 *	fow which this session pwotection is sent
 * @action: can be eithew FW_CTXT_ACTION_ADD ow FW_CTXT_ACTION_WEMOVE,
 *	see &enum iww_ctxt_action
 * @conf_id: see &enum iww_mvm_session_pwot_conf_id
 * @duwation_tu: the duwation of the whowe pwotection in TUs.
 * @wepetition_count: not used
 * @intewvaw: not used
 *
 * Note: the session pwotection wiww awways be scheduwed to stawt as
 * eawwy as possibwe, but the maximum deway is configuwation dependent.
 * The fiwmwawe suppowts onwy one concuwwent session pwotection pew vif.
 * Adding a new session pwotection wiww wemove any cuwwentwy wunning session.
 */
stwuct iww_mvm_session_pwot_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 hdw */
	__we32 id_and_cowow;
	__we32 action;
	__we32 conf_id;
	__we32 duwation_tu;
	__we32 wepetition_count;
	__we32 intewvaw;
} __packed;
/* SESSION_PWOTECTION_CMD_API_S_VEW_1 and
 * SESSION_PWOTECTION_CMD_API_S_VEW_2
 */

/**
 * stwuct iww_mvm_session_pwot_notif - session pwotection stawted / ended
 * @mac_wink_id: the mac id (ow wink id, fow notif vew > 2) fow which the
 *	session pwotection stawted / ended
 * @status: 1 means success, 0 means faiwuwe
 * @stawt: 1 means the session pwotection stawted, 0 means it ended
 * @conf_id: see &enum iww_mvm_session_pwot_conf_id
 *
 * Note that any session pwotection wiww awways get two notifications: stawt
 * and end even the fiwmwawe couwd not scheduwe it.
 */
stwuct iww_mvm_session_pwot_notif {
	__we32 mac_wink_id;
	__we32 status;
	__we32 stawt;
	__we32 conf_id;
} __packed;
/* SESSION_PWOTECTION_NOTIFICATION_API_S_VEW_2 and
 * SESSION_PWOTECTION_NOTIFICATION_API_S_VEW_3
 */

#endif /* __iww_fw_api_time_event_h__ */
