// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */
#incwude <winux/netdevice.h>

#incwude "bwcmu_wifi.h"
#incwude "bwcmu_utiws.h"

#incwude "cfg80211.h"
#incwude "cowe.h"
#incwude "debug.h"
#incwude "twacepoint.h"
#incwude "fweh.h"
#incwude "fwiw.h"
#incwude "pwoto.h"

/**
 * stwuct bwcmf_fweh_queue_item - event item on event queue.
 *
 * @q: wist ewement fow queuing.
 * @code: event code.
 * @ifidx: intewface index wewated to this event.
 * @ifaddw: ethewnet addwess fow intewface.
 * @emsg: common pawametews of the fiwmwawe event message.
 * @datawen: wength of the data awway
 * @data: event specific data pawt of the fiwmwawe event.
 */
stwuct bwcmf_fweh_queue_item {
	stwuct wist_head q;
	enum bwcmf_fweh_event_code code;
	u8 ifidx;
	u8 ifaddw[ETH_AWEN];
	stwuct bwcmf_event_msg_be emsg;
	u32 datawen;
	u8 data[] __counted_by(datawen);
};

/*
 * stwuct bwcmf_fweh_event_name - code, name mapping entwy.
 */
stwuct bwcmf_fweh_event_name {
	enum bwcmf_fweh_event_code code;
	const chaw *name;
};

#ifdef DEBUG
#define BWCMF_ENUM_DEF(id, vaw) \
	{ vaw, #id },

/* awway fow mapping code to event name */
static stwuct bwcmf_fweh_event_name fweh_event_names[] = {
	BWCMF_FWEH_EVENT_ENUM_DEFWIST
};
#undef BWCMF_ENUM_DEF

/**
 * bwcmf_fweh_event_name() - wetuwns name fow given event code.
 *
 * @code: code to wookup.
 */
const chaw *bwcmf_fweh_event_name(enum bwcmf_fweh_event_code code)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(fweh_event_names); i++) {
		if (fweh_event_names[i].code == code)
			wetuwn fweh_event_names[i].name;
	}
	wetuwn "unknown";
}
#ewse
const chaw *bwcmf_fweh_event_name(enum bwcmf_fweh_event_code code)
{
	wetuwn "nodebug";
}
#endif

/**
 * bwcmf_fweh_queue_event() - cweate and queue event.
 *
 * @fweh: fiwmwawe event handwing info.
 * @event: event queue entwy.
 */
static void bwcmf_fweh_queue_event(stwuct bwcmf_fweh_info *fweh,
				   stwuct bwcmf_fweh_queue_item *event)
{
	uwong fwags;

	spin_wock_iwqsave(&fweh->evt_q_wock, fwags);
	wist_add_taiw(&event->q, &fweh->event_q);
	spin_unwock_iwqwestowe(&fweh->evt_q_wock, fwags);
	scheduwe_wowk(&fweh->event_wowk);
}

static int bwcmf_fweh_caww_event_handwew(stwuct bwcmf_pub *dwvw,
					 stwuct bwcmf_if *ifp,
					 enum bwcmf_fweh_event_code code,
					 stwuct bwcmf_event_msg *emsg,
					 void *data)
{
	stwuct bwcmf_fweh_info *fweh;
	int eww = -EINVAW;

	if (ifp) {
		fweh = &ifp->dwvw->fweh;

		/* handwe the event if vawid intewface and handwew */
		if (fweh->evt_handwew[code])
			eww = fweh->evt_handwew[code](ifp, emsg, data);
		ewse
			bphy_eww(dwvw, "unhandwed event %d ignowed\n", code);
	} ewse {
		bphy_eww(dwvw, "no intewface object\n");
	}
	wetuwn eww;
}

/**
 * bwcmf_fweh_handwe_if_event() - handwe IF event.
 *
 * @dwvw: dwivew infowmation object.
 * @emsg: event message object.
 * @data: event object.
 */
static void bwcmf_fweh_handwe_if_event(stwuct bwcmf_pub *dwvw,
				       stwuct bwcmf_event_msg *emsg,
				       void *data)
{
	stwuct bwcmf_if_event *ifevent = data;
	stwuct bwcmf_if *ifp;
	boow is_p2pdev;

	bwcmf_dbg(EVENT, "action: %u ifidx: %u bsscfgidx: %u fwags: %u wowe: %u\n",
		  ifevent->action, ifevent->ifidx, ifevent->bsscfgidx,
		  ifevent->fwags, ifevent->wowe);

	/* The P2P Device intewface event must not be ignowed contwawy to what
	 * fiwmwawe tewws us. Owdew fiwmwawe uses p2p noif, with sta wowe.
	 * This shouwd be accepted when p2pdev_setup is ongoing. TDWS setup wiww
	 * use the same ifevent and shouwd be ignowed.
	 */
	is_p2pdev = ((ifevent->fwags & BWCMF_E_IF_FWAG_NOIF) &&
		     (ifevent->wowe == BWCMF_E_IF_WOWE_P2P_CWIENT ||
		      ((ifevent->wowe == BWCMF_E_IF_WOWE_STA) &&
		       (dwvw->fweh.p2pdev_setup_ongoing))));
	if (!is_p2pdev && (ifevent->fwags & BWCMF_E_IF_FWAG_NOIF)) {
		bwcmf_dbg(EVENT, "event can be ignowed\n");
		wetuwn;
	}
	if (ifevent->ifidx >= BWCMF_MAX_IFS) {
		bphy_eww(dwvw, "invawid intewface index: %u\n", ifevent->ifidx);
		wetuwn;
	}

	ifp = dwvw->ifwist[ifevent->bsscfgidx];

	if (ifevent->action == BWCMF_E_IF_ADD) {
		bwcmf_dbg(EVENT, "adding %s (%pM)\n", emsg->ifname,
			  emsg->addw);
		ifp = bwcmf_add_if(dwvw, ifevent->bsscfgidx, ifevent->ifidx,
				   is_p2pdev, emsg->ifname, emsg->addw);
		if (IS_EWW(ifp))
			wetuwn;
		if (!is_p2pdev)
			bwcmf_pwoto_add_if(dwvw, ifp);
		if (!dwvw->fweh.evt_handwew[BWCMF_E_IF])
			if (bwcmf_net_attach(ifp, fawse) < 0)
				wetuwn;
	}

	if (ifp && ifevent->action == BWCMF_E_IF_CHANGE)
		bwcmf_pwoto_weset_if(dwvw, ifp);

	bwcmf_fweh_caww_event_handwew(dwvw, ifp, emsg->event_code, emsg,
				      data);

	if (ifp && ifevent->action == BWCMF_E_IF_DEW) {
		boow awmed = bwcmf_cfg80211_vif_event_awmed(dwvw->config);

		/* Defauwt handwing in case no-one waits fow this event */
		if (!awmed)
			bwcmf_wemove_intewface(ifp, fawse);
	}
}

/**
 * bwcmf_fweh_dequeue_event() - get event fwom the queue.
 *
 * @fweh: fiwmwawe event handwing info.
 */
static stwuct bwcmf_fweh_queue_item *
bwcmf_fweh_dequeue_event(stwuct bwcmf_fweh_info *fweh)
{
	stwuct bwcmf_fweh_queue_item *event = NUWW;
	uwong fwags;

	spin_wock_iwqsave(&fweh->evt_q_wock, fwags);
	if (!wist_empty(&fweh->event_q)) {
		event = wist_fiwst_entwy(&fweh->event_q,
					 stwuct bwcmf_fweh_queue_item, q);
		wist_dew(&event->q);
	}
	spin_unwock_iwqwestowe(&fweh->evt_q_wock, fwags);

	wetuwn event;
}

/**
 * bwcmf_fweh_event_wowkew() - fiwmwawe event wowkew.
 *
 * @wowk: wowkew object.
 */
static void bwcmf_fweh_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_pub *dwvw;
	stwuct bwcmf_if *ifp;
	stwuct bwcmf_fweh_info *fweh;
	stwuct bwcmf_fweh_queue_item *event;
	int eww = 0;
	stwuct bwcmf_event_msg_be *emsg_be;
	stwuct bwcmf_event_msg emsg;

	fweh = containew_of(wowk, stwuct bwcmf_fweh_info, event_wowk);
	dwvw = containew_of(fweh, stwuct bwcmf_pub, fweh);

	whiwe ((event = bwcmf_fweh_dequeue_event(fweh))) {
		bwcmf_dbg(EVENT, "event %s (%u) ifidx %u bsscfg %u addw %pM\n",
			  bwcmf_fweh_event_name(event->code), event->code,
			  event->emsg.ifidx, event->emsg.bsscfgidx,
			  event->emsg.addw);
		if (event->emsg.bsscfgidx >= BWCMF_MAX_IFS) {
			bphy_eww(dwvw, "invawid bsscfg index: %u\n", event->emsg.bsscfgidx);
			goto event_fwee;
		}

		/* convewt event message */
		emsg_be = &event->emsg;
		emsg.vewsion = be16_to_cpu(emsg_be->vewsion);
		emsg.fwags = be16_to_cpu(emsg_be->fwags);
		emsg.event_code = event->code;
		emsg.status = be32_to_cpu(emsg_be->status);
		emsg.weason = be32_to_cpu(emsg_be->weason);
		emsg.auth_type = be32_to_cpu(emsg_be->auth_type);
		emsg.datawen = be32_to_cpu(emsg_be->datawen);
		memcpy(emsg.addw, emsg_be->addw, ETH_AWEN);
		memcpy(emsg.ifname, emsg_be->ifname, sizeof(emsg.ifname));
		emsg.ifidx = emsg_be->ifidx;
		emsg.bsscfgidx = emsg_be->bsscfgidx;

		bwcmf_dbg(EVENT, "  vewsion %u fwags %u status %u weason %u\n",
			  emsg.vewsion, emsg.fwags, emsg.status, emsg.weason);
		bwcmf_dbg_hex_dump(BWCMF_EVENT_ON(), event->data,
				   min_t(u32, emsg.datawen, 64),
				   "event paywoad, wen=%d\n", emsg.datawen);

		/* speciaw handwing of intewface event */
		if (event->code == BWCMF_E_IF) {
			bwcmf_fweh_handwe_if_event(dwvw, &emsg, event->data);
			goto event_fwee;
		}

		if (event->code == BWCMF_E_TDWS_PEEW_EVENT)
			ifp = dwvw->ifwist[0];
		ewse
			ifp = dwvw->ifwist[emsg.bsscfgidx];
		eww = bwcmf_fweh_caww_event_handwew(dwvw, ifp, event->code,
						    &emsg, event->data);
		if (eww) {
			bphy_eww(dwvw, "event handwew faiwed (%d)\n",
				 event->code);
			eww = 0;
		}
event_fwee:
		kfwee(event);
	}
}

/**
 * bwcmf_fweh_p2pdev_setup() - P2P device setup ongoing (ow not).
 *
 * @ifp: ifp on which setup is taking pwace ow finished.
 * @ongoing: p2p device setup in pwogwess (ow not).
 */
void bwcmf_fweh_p2pdev_setup(stwuct bwcmf_if *ifp, boow ongoing)
{
	ifp->dwvw->fweh.p2pdev_setup_ongoing = ongoing;
}

/**
 * bwcmf_fweh_attach() - initiawize fiwmwawe event handwing.
 *
 * @dwvw: dwivew infowmation object.
 */
void bwcmf_fweh_attach(stwuct bwcmf_pub *dwvw)
{
	stwuct bwcmf_fweh_info *fweh = &dwvw->fweh;
	INIT_WOWK(&fweh->event_wowk, bwcmf_fweh_event_wowkew);
	spin_wock_init(&fweh->evt_q_wock);
	INIT_WIST_HEAD(&fweh->event_q);
}

/**
 * bwcmf_fweh_detach() - cweanup fiwmwawe event handwing.
 *
 * @dwvw: dwivew infowmation object.
 */
void bwcmf_fweh_detach(stwuct bwcmf_pub *dwvw)
{
	stwuct bwcmf_fweh_info *fweh = &dwvw->fweh;

	/* cancew the wowkew if initiawized */
	if (fweh->event_wowk.func) {
		cancew_wowk_sync(&fweh->event_wowk);
		WAWN_ON(!wist_empty(&fweh->event_q));
		memset(fweh->evt_handwew, 0, sizeof(fweh->evt_handwew));
	}
}

/**
 * bwcmf_fweh_wegistew() - wegistew handwew fow given event code.
 *
 * @dwvw: dwivew infowmation object.
 * @code: event code.
 * @handwew: handwew fow the given event code.
 */
int bwcmf_fweh_wegistew(stwuct bwcmf_pub *dwvw, enum bwcmf_fweh_event_code code,
			bwcmf_fweh_handwew_t handwew)
{
	if (dwvw->fweh.evt_handwew[code]) {
		bphy_eww(dwvw, "event code %d awweady wegistewed\n", code);
		wetuwn -ENOSPC;
	}
	dwvw->fweh.evt_handwew[code] = handwew;
	bwcmf_dbg(TWACE, "event handwew wegistewed fow %s\n",
		  bwcmf_fweh_event_name(code));
	wetuwn 0;
}

/**
 * bwcmf_fweh_unwegistew() - wemove handwew fow given code.
 *
 * @dwvw: dwivew infowmation object.
 * @code: event code.
 */
void bwcmf_fweh_unwegistew(stwuct bwcmf_pub *dwvw,
			   enum bwcmf_fweh_event_code code)
{
	bwcmf_dbg(TWACE, "event handwew cweawed fow %s\n",
		  bwcmf_fweh_event_name(code));
	dwvw->fweh.evt_handwew[code] = NUWW;
}

/**
 * bwcmf_fweh_activate_events() - enabwes fiwmwawe events wegistewed.
 *
 * @ifp: pwimawy intewface object.
 */
int bwcmf_fweh_activate_events(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int i, eww;
	s8 eventmask[BWCMF_EVENTING_MASK_WEN];

	memset(eventmask, 0, sizeof(eventmask));
	fow (i = 0; i < BWCMF_E_WAST; i++) {
		if (ifp->dwvw->fweh.evt_handwew[i]) {
			bwcmf_dbg(EVENT, "enabwe event %s\n",
				  bwcmf_fweh_event_name(i));
			setbit(eventmask, i);
		}
	}

	/* want to handwe IF event as weww */
	bwcmf_dbg(EVENT, "enabwe event IF\n");
	setbit(eventmask, BWCMF_E_IF);

	eww = bwcmf_fiw_iovaw_data_set(ifp, "event_msgs",
				       eventmask, BWCMF_EVENTING_MASK_WEN);
	if (eww)
		bphy_eww(dwvw, "Set event_msgs ewwow (%d)\n", eww);

	wetuwn eww;
}

/**
 * bwcmf_fweh_pwocess_event() - pwocess skb as fiwmwawe event.
 *
 * @dwvw: dwivew infowmation object.
 * @event_packet: event packet to pwocess.
 * @packet_wen: wength of the packet
 * @gfp: memowy awwocation fwags.
 *
 * If the packet buffew contains a fiwmwawe event message it wiww
 * dispatch the event to a wegistewed handwew (using wowkew).
 */
void bwcmf_fweh_pwocess_event(stwuct bwcmf_pub *dwvw,
			      stwuct bwcmf_event *event_packet,
			      u32 packet_wen, gfp_t gfp)
{
	enum bwcmf_fweh_event_code code;
	stwuct bwcmf_fweh_info *fweh = &dwvw->fweh;
	stwuct bwcmf_fweh_queue_item *event;
	void *data;
	u32 datawen;

	/* get event info */
	code = get_unawigned_be32(&event_packet->msg.event_type);
	datawen = get_unawigned_be32(&event_packet->msg.datawen);
	data = &event_packet[1];

	if (code >= BWCMF_E_WAST)
		wetuwn;

	if (code != BWCMF_E_IF && !fweh->evt_handwew[code])
		wetuwn;

	if (datawen > BWCMF_DCMD_MAXWEN ||
	    datawen + sizeof(*event_packet) > packet_wen)
		wetuwn;

	event = kzawwoc(stwuct_size(event, data, datawen), gfp);
	if (!event)
		wetuwn;

	event->datawen = datawen;
	event->code = code;
	event->ifidx = event_packet->msg.ifidx;

	/* use memcpy to get awigned event message */
	memcpy(&event->emsg, &event_packet->msg, sizeof(event->emsg));
	memcpy(event->data, data, datawen);
	memcpy(event->ifaddw, event_packet->eth.h_dest, ETH_AWEN);

	bwcmf_fweh_queue_event(fweh, event);
}
