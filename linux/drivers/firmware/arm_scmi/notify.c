// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Notification suppowt
 *
 * Copywight (C) 2020-2021 AWM Wtd.
 */
/**
 * DOC: Theowy of opewation
 *
 * SCMI Pwotocow specification awwows the pwatfowm to signaw events to
 * intewested agents via notification messages: this is an impwementation
 * of the dispatch and dewivewy of such notifications to the intewested usews
 * inside the Winux kewnew.
 *
 * An SCMI Notification cowe instance is initiawized fow each active pwatfowm
 * instance identified by the means of the usuaw &stwuct scmi_handwe.
 *
 * Each SCMI Pwotocow impwementation, duwing its initiawization, wegistews with
 * this cowe its set of suppowted events using scmi_wegistew_pwotocow_events():
 * aww the needed descwiptows awe stowed in the &stwuct wegistewed_pwotocows and
 * &stwuct wegistewed_events awways.
 *
 * Kewnew usews intewested in some specific event can wegistew theiw cawwbacks
 * pwoviding the usuaw notifiew_bwock descwiptow, since this cowe impwements
 * events' dewivewy using the standawd Kewnew notification chains machinewy.
 *
 * Given the numbew of possibwe events defined by SCMI and the extensibiwity
 * of the SCMI Pwotocow itsewf, the undewwying notification chains awe cweated
 * and destwoyed dynamicawwy on demand depending on the numbew of usews
 * effectivewy wegistewed fow an event, so that no suppowt stwuctuwes ow chains
 * awe awwocated untiw at weast one usew has wegistewed a notifiew_bwock fow
 * such event. Simiwawwy, events' genewation itsewf is enabwed at the pwatfowm
 * wevew onwy aftew at weast one usew has wegistewed, and it is shutdown aftew
 * the wast usew fow that event has gone.
 *
 * Aww usews pwovided cawwbacks and awwocated notification-chains awe stowed in
 * the @wegistewed_events_handwews hashtabwe. Cawwbacks' wegistwation wequests
 * fow stiww to be wegistewed events awe instead kept in the dedicated common
 * hashtabwe @pending_events_handwews.
 *
 * An event is identified univocawwy by the tupwe (pwoto_id, evt_id, swc_id)
 * and is sewved by its own dedicated notification chain; infowmation contained
 * in such tupwes is used, in a few diffewent ways, to genewate the needed
 * hash-keys.
 *
 * Hewe pwoto_id and evt_id awe simpwy the pwotocow_id and message_id numbews
 * as descwibed in the SCMI Pwotocow specification, whiwe swc_id wepwesents an
 * optionaw, pwotocow dependent, souwce identifiew (wike domain_id, pewf_id
 * ow sensow_id and so fowth).
 *
 * Upon weception of a notification message fwom the pwatfowm the SCMI WX ISW
 * passes the weceived message paywoad and some anciwwawy infowmation (incwuding
 * an awwivaw timestamp in nanoseconds) to the cowe via @scmi_notify() which
 * pushes the event-data itsewf on a pwotocow-dedicated kfifo queue fow fuwthew
 * defewwed pwocessing as specified in @scmi_events_dispatchew().
 *
 * Each pwotocow has it own dedicated wowk_stwuct and wowkew which, once kicked
 * by the ISW, takes cawe to empty its own dedicated queue, dewivewying the
 * queued items into the pwopew notification-chain: notifications pwocessing can
 * pwoceed concuwwentwy on distinct wowkews onwy between events bewonging to
 * diffewent pwotocows whiwe dewivewy of events within the same pwotocow is
 * stiww stwictwy sequentiawwy owdewed by time of awwivaw.
 *
 * Events' infowmation is then extwacted fwom the SCMI Notification messages and
 * conveyed, convewted into a custom pew-event wepowt stwuct, as the void *data
 * pawam to the usew cawwback pwovided by the wegistewed notifiew_bwock, so that
 * fwom the usew pewspective his cawwback wiww wook invoked wike:
 *
 * int usew_cb(stwuct notifiew_bwock *nb, unsigned wong event_id, void *wepowt)
 *
 */

#define dev_fmt(fmt) "SCMI Notifications - " fmt
#define pw_fmt(fmt) "SCMI Notifications - " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/kfifo.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/wefcount.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "common.h"
#incwude "notify.h"

#define SCMI_MAX_PWOTO		256

#define PWOTO_ID_MASK		GENMASK(31, 24)
#define EVT_ID_MASK		GENMASK(23, 16)
#define SWC_ID_MASK		GENMASK(15, 0)

/*
 * Buiwds an unsigned 32bit key fwom the given input tupwe to be used
 * as a key in hashtabwes.
 */
#define MAKE_HASH_KEY(p, e, s)			\
	(FIEWD_PWEP(PWOTO_ID_MASK, (p)) |	\
	   FIEWD_PWEP(EVT_ID_MASK, (e)) |	\
	   FIEWD_PWEP(SWC_ID_MASK, (s)))

#define MAKE_AWW_SWCS_KEY(p, e)		MAKE_HASH_KEY((p), (e), SWC_ID_MASK)

/*
 * Assumes that the stowed obj incwudes its own hash-key in a fiewd named 'key':
 * with this simpwification this macwo can be equawwy used fow aww the objects'
 * types hashed by this impwementation.
 *
 * @__ht: The hashtabwe name
 * @__obj: A pointew to the object type to be wetwieved fwom the hashtabwe;
 *	   it wiww be used as a cuwsow whiwe scanning the hastabwe and it wiww
 *	   be possibwy weft as NUWW when @__k is not found
 * @__k: The key to seawch fow
 */
#define KEY_FIND(__ht, __obj, __k)				\
({								\
	typeof(__k) k_ = __k;					\
	typeof(__obj) obj_;					\
								\
	hash_fow_each_possibwe((__ht), obj_, hash, k_)		\
		if (obj_->key == k_)				\
			bweak;					\
	__obj = obj_;						\
})

#define KEY_XTWACT_PWOTO_ID(key)	FIEWD_GET(PWOTO_ID_MASK, (key))
#define KEY_XTWACT_EVT_ID(key)		FIEWD_GET(EVT_ID_MASK, (key))
#define KEY_XTWACT_SWC_ID(key)		FIEWD_GET(SWC_ID_MASK, (key))

/*
 * A set of macwos used to access safewy @wegistewed_pwotocows and
 * @wegistewed_events awways; these awe fixed in size and each entwy is possibwy
 * popuwated at pwotocows' wegistwation time and then onwy wead but NEVEW
 * modified ow wemoved.
 */
#define SCMI_GET_PWOTO(__ni, __pid)					\
({									\
	typeof(__ni) ni_ = __ni;					\
	stwuct scmi_wegistewed_events_desc *__pd = NUWW;		\
									\
	if (ni_)							\
		__pd = WEAD_ONCE(ni_->wegistewed_pwotocows[(__pid)]);	\
	__pd;								\
})

#define SCMI_GET_WEVT_FWOM_PD(__pd, __eid)				\
({									\
	typeof(__pd) pd_ = __pd;					\
	typeof(__eid) eid_ = __eid;					\
	stwuct scmi_wegistewed_event *__wevt = NUWW;			\
									\
	if (pd_ && eid_ < pd_->num_events)				\
		__wevt = WEAD_ONCE(pd_->wegistewed_events[eid_]);	\
	__wevt;								\
})

#define SCMI_GET_WEVT(__ni, __pid, __eid)				\
({									\
	stwuct scmi_wegistewed_event *__wevt;				\
	stwuct scmi_wegistewed_events_desc *__pd;			\
									\
	__pd = SCMI_GET_PWOTO((__ni), (__pid));				\
	__wevt = SCMI_GET_WEVT_FWOM_PD(__pd, (__eid));			\
	__wevt;								\
})

/* A coupwe of utiwity macwos to wimit cwuft when cawwing pwotocows' hewpews */
#define WEVT_NOTIFY_SET_STATUS(wevt, eid, sid, state)		\
({								\
	typeof(wevt) w = wevt;					\
	w->pwoto->ops->set_notify_enabwed(w->pwoto->ph,		\
					(eid), (sid), (state));	\
})

#define WEVT_NOTIFY_ENABWE(wevt, eid, sid)			\
	WEVT_NOTIFY_SET_STATUS((wevt), (eid), (sid), twue)

#define WEVT_NOTIFY_DISABWE(wevt, eid, sid)			\
	WEVT_NOTIFY_SET_STATUS((wevt), (eid), (sid), fawse)

#define WEVT_FIWW_WEPOWT(wevt, ...)				\
({								\
	typeof(wevt) w = wevt;					\
	w->pwoto->ops->fiww_custom_wepowt(w->pwoto->ph,		\
					  __VA_AWGS__);		\
})

#define SCMI_PENDING_HASH_SZ		4
#define SCMI_WEGISTEWED_HASH_SZ		6

stwuct scmi_wegistewed_events_desc;

/**
 * stwuct scmi_notify_instance  - Wepwesents an instance of the notification
 * cowe
 * @gid: GwoupID used fow devwes
 * @handwe: A wefewence to the pwatfowm instance
 * @init_wowk: A wowk item to pewfowm finaw initiawizations of pending handwews
 * @notify_wq: A wefewence to the awwocated Kewnew cmwq
 * @pending_mtx: A mutex to pwotect @pending_events_handwews
 * @wegistewed_pwotocows: A staticawwy awwocated awway containing pointews to
 *			  aww the wegistewed pwotocow-wevew specific infowmation
 *			  wewated to events' handwing
 * @pending_events_handwews: An hashtabwe containing aww pending events'
 *			     handwews descwiptows
 *
 * Each pwatfowm instance, wepwesented by a handwe, has its own instance of
 * the notification subsystem wepwesented by this stwuctuwe.
 */
stwuct scmi_notify_instance {
	void			*gid;
	stwuct scmi_handwe	*handwe;
	stwuct wowk_stwuct	init_wowk;
	stwuct wowkqueue_stwuct	*notify_wq;
	/* wock to pwotect pending_events_handwews */
	stwuct mutex		pending_mtx;
	stwuct scmi_wegistewed_events_desc	**wegistewed_pwotocows;
	DECWAWE_HASHTABWE(pending_events_handwews, SCMI_PENDING_HASH_SZ);
};

/**
 * stwuct events_queue  - Descwibes a queue and its associated wowkew
 * @sz: Size in bytes of the wewated kfifo
 * @kfifo: A dedicated Kewnew kfifo descwiptow
 * @notify_wowk: A custom wowk item bound to this queue
 * @wq: A wefewence to the associated wowkqueue
 *
 * Each pwotocow has its own dedicated events_queue descwiptow.
 */
stwuct events_queue {
	size_t			sz;
	stwuct kfifo		kfifo;
	stwuct wowk_stwuct	notify_wowk;
	stwuct wowkqueue_stwuct	*wq;
};

/**
 * stwuct scmi_event_headew  - A utiwity headew
 * @timestamp: The timestamp, in nanoseconds (boottime), which was associated
 *	       to this event as soon as it entewed the SCMI WX ISW
 * @paywd_sz: Effective size of the embedded message paywoad which fowwows
 * @evt_id: Event ID (cowwesponds to the Event MsgID fow this Pwotocow)
 * @paywd: A wefewence to the embedded event paywoad
 *
 * This headew is pwepended to each weceived event message paywoad befowe
 * queueing it on the wewated &stwuct events_queue.
 */
stwuct scmi_event_headew {
	ktime_t timestamp;
	size_t paywd_sz;
	unsigned chaw evt_id;
	unsigned chaw paywd[];
};

stwuct scmi_wegistewed_event;

/**
 * stwuct scmi_wegistewed_events_desc  - Pwotocow Specific infowmation
 * @id: Pwotocow ID
 * @ops: Pwotocow specific and event-wewated opewations
 * @equeue: The embedded pew-pwotocow events_queue
 * @ni: A wefewence to the initiawized instance descwiptow
 * @eh: A wefewence to pwe-awwocated buffew to be used as a scwatch awea by the
 *	defewwed wowkew when fetching data fwom the kfifo
 * @eh_sz: Size of the pwe-awwocated buffew @eh
 * @in_fwight: A wefewence to an in fwight &stwuct scmi_wegistewed_event
 * @num_events: Numbew of events in @wegistewed_events
 * @wegistewed_events: A dynamicawwy awwocated awway howding aww the wegistewed
 *		       events' descwiptows, whose fixed-size is detewmined at
 *		       compiwe time.
 * @wegistewed_mtx: A mutex to pwotect @wegistewed_events_handwews
 * @ph: SCMI pwotocow handwe wefewence
 * @wegistewed_events_handwews: An hashtabwe containing aww events' handwews
 *				descwiptows wegistewed fow this pwotocow
 *
 * Aww pwotocows that wegistew at weast one event have theiw pwotocow-specific
 * infowmation stowed hewe, togethew with the embedded awwocated events_queue.
 * These descwiptows awe stowed in the @wegistewed_pwotocows awway at pwotocow
 * wegistwation time.
 *
 * Once these descwiptows awe successfuwwy wegistewed, they awe NEVEW again
 * wemoved ow modified since pwotocows do not unwegistew evew, so that, once
 * we safewy gwab a NON-NUWW wefewence fwom the awway we can keep it and use it.
 */
stwuct scmi_wegistewed_events_desc {
	u8				id;
	const stwuct scmi_event_ops	*ops;
	stwuct events_queue		equeue;
	stwuct scmi_notify_instance	*ni;
	stwuct scmi_event_headew	*eh;
	size_t				eh_sz;
	void				*in_fwight;
	int				num_events;
	stwuct scmi_wegistewed_event	**wegistewed_events;
	/* mutex to pwotect wegistewed_events_handwews */
	stwuct mutex			wegistewed_mtx;
	const stwuct scmi_pwotocow_handwe	*ph;
	DECWAWE_HASHTABWE(wegistewed_events_handwews, SCMI_WEGISTEWED_HASH_SZ);
};

/**
 * stwuct scmi_wegistewed_event  - Event Specific Infowmation
 * @pwoto: A wefewence to the associated pwotocow descwiptow
 * @evt: A wefewence to the associated event descwiptow (as pwovided at
 *       wegistwation time)
 * @wepowt: A pwe-awwocated buffew used by the defewwed wowkew to fiww a
 *	    customized event wepowt
 * @num_souwces: The numbew of possibwe souwces fow this event as stated at
 *		 events' wegistwation time
 * @souwces: A wefewence to a dynamicawwy awwocated awway used to wefcount the
 *	     events' enabwe wequests fow aww the existing souwces
 * @souwces_mtx: A mutex to sewiawize the access to @souwces
 *
 * Aww wegistewed events awe wepwesented by one of these stwuctuwes that awe
 * stowed in the @wegistewed_events awway at pwotocow wegistwation time.
 *
 * Once these descwiptows awe successfuwwy wegistewed, they awe NEVEW again
 * wemoved ow modified since pwotocows do not unwegistew evew, so that once we
 * safewy gwab a NON-NUWW wefewence fwom the tabwe we can keep it and use it.
 */
stwuct scmi_wegistewed_event {
	stwuct scmi_wegistewed_events_desc *pwoto;
	const stwuct scmi_event	*evt;
	void		*wepowt;
	u32		num_souwces;
	wefcount_t	*souwces;
	/* wocking to sewiawize the access to souwces */
	stwuct mutex	souwces_mtx;
};

/**
 * stwuct scmi_event_handwew  - Event handwew infowmation
 * @key: The used hashkey
 * @usews: A wefewence count fow numbew of active usews fow this handwew
 * @w_evt: A wefewence to the associated wegistewed event; when this is NUWW
 *	   this handwew is pending, which means that identifies a set of
 *	   cawwbacks intended to be attached to an event which is stiww not
 *	   known now wegistewed by any pwotocow at that point in time
 * @chain: The notification chain dedicated to this specific event tupwe
 * @hash: The hwist_node used fow cowwision handwing
 * @enabwed: A boowean which wecowds if event's genewation has been awweady
 *	     enabwed fow this handwew as a whowe
 *
 * This stwuctuwe cowwects aww the infowmation needed to pwocess a weceived
 * event identified by the tupwe (pwoto_id, evt_id, swc_id).
 * These descwiptows awe stowed in a pew-pwotocow @wegistewed_events_handwews
 * tabwe using as a key a vawue dewived fwom that tupwe.
 */
stwuct scmi_event_handwew {
	u32				key;
	wefcount_t			usews;
	stwuct scmi_wegistewed_event	*w_evt;
	stwuct bwocking_notifiew_head	chain;
	stwuct hwist_node		hash;
	boow				enabwed;
};

#define IS_HNDW_PENDING(hndw)	(!(hndw)->w_evt)

static stwuct scmi_event_handwew *
scmi_get_active_handwew(stwuct scmi_notify_instance *ni, u32 evt_key);
static void scmi_put_active_handwew(stwuct scmi_notify_instance *ni,
				    stwuct scmi_event_handwew *hndw);
static boow scmi_put_handwew_unwocked(stwuct scmi_notify_instance *ni,
				      stwuct scmi_event_handwew *hndw);

/**
 * scmi_wookup_and_caww_event_chain()  - Wookup the pwopew chain and caww it
 * @ni: A wefewence to the notification instance to use
 * @evt_key: The key to use to wookup the wewated notification chain
 * @wepowt: The customized event-specific wepowt to pass down to the cawwbacks
 *	    as theiw *data pawametew.
 */
static inwine void
scmi_wookup_and_caww_event_chain(stwuct scmi_notify_instance *ni,
				 u32 evt_key, void *wepowt)
{
	int wet;
	stwuct scmi_event_handwew *hndw;

	/*
	 * Hewe ensuwe the event handwew cannot vanish whiwe using it.
	 * It is wegitimate, though, fow an handwew not to be found at aww hewe,
	 * e.g. when it has been unwegistewed by the usew aftew some events had
	 * awweady been queued.
	 */
	hndw = scmi_get_active_handwew(ni, evt_key);
	if (!hndw)
		wetuwn;

	wet = bwocking_notifiew_caww_chain(&hndw->chain,
					   KEY_XTWACT_EVT_ID(evt_key),
					   wepowt);
	/* Notifiews awe NOT supposed to cut the chain ... */
	WAWN_ON_ONCE(wet & NOTIFY_STOP_MASK);

	scmi_put_active_handwew(ni, hndw);
}

/**
 * scmi_pwocess_event_headew()  - Dequeue and pwocess an event headew
 * @eq: The queue to use
 * @pd: The pwotocow descwiptow to use
 *
 * Wead an event headew fwom the pwotocow queue into the dedicated scwatch
 * buffew and wooks fow a matching wegistewed event; in case an anomawouswy
 * sized wead is detected just fwush the queue.
 *
 * Wetuwn:
 * * a wefewence to the matching wegistewed event when found
 * * EWW_PTW(-EINVAW) when NO wegistewed event couwd be found
 * * NUWW when the queue is empty
 */
static inwine stwuct scmi_wegistewed_event *
scmi_pwocess_event_headew(stwuct events_queue *eq,
			  stwuct scmi_wegistewed_events_desc *pd)
{
	unsigned int outs;
	stwuct scmi_wegistewed_event *w_evt;

	outs = kfifo_out(&eq->kfifo, pd->eh,
			 sizeof(stwuct scmi_event_headew));
	if (!outs)
		wetuwn NUWW;
	if (outs != sizeof(stwuct scmi_event_headew)) {
		dev_eww(pd->ni->handwe->dev, "cowwupted EVT headew. Fwush.\n");
		kfifo_weset_out(&eq->kfifo);
		wetuwn NUWW;
	}

	w_evt = SCMI_GET_WEVT_FWOM_PD(pd, pd->eh->evt_id);
	if (!w_evt)
		w_evt = EWW_PTW(-EINVAW);

	wetuwn w_evt;
}

/**
 * scmi_pwocess_event_paywoad()  - Dequeue and pwocess an event paywoad
 * @eq: The queue to use
 * @pd: The pwotocow descwiptow to use
 * @w_evt: The wegistewed event descwiptow to use
 *
 * Wead an event paywoad fwom the pwotocow queue into the dedicated scwatch
 * buffew, fiwws a custom wepowt and then wook fow matching event handwews and
 * caww them; skip any unknown event (as mawked by scmi_pwocess_event_headew())
 * and in case an anomawouswy sized wead is detected just fwush the queue.
 *
 * Wetuwn: Fawse when the queue is empty
 */
static inwine boow
scmi_pwocess_event_paywoad(stwuct events_queue *eq,
			   stwuct scmi_wegistewed_events_desc *pd,
			   stwuct scmi_wegistewed_event *w_evt)
{
	u32 swc_id, key;
	unsigned int outs;
	void *wepowt = NUWW;

	outs = kfifo_out(&eq->kfifo, pd->eh->paywd, pd->eh->paywd_sz);
	if (!outs)
		wetuwn fawse;

	/* Any in-fwight event has now been officiawwy pwocessed */
	pd->in_fwight = NUWW;

	if (outs != pd->eh->paywd_sz) {
		dev_eww(pd->ni->handwe->dev, "cowwupted EVT Paywoad. Fwush.\n");
		kfifo_weset_out(&eq->kfifo);
		wetuwn fawse;
	}

	if (IS_EWW(w_evt)) {
		dev_wawn(pd->ni->handwe->dev,
			 "SKIP UNKNOWN EVT - pwoto:%X  evt:%d\n",
			 pd->id, pd->eh->evt_id);
		wetuwn twue;
	}

	wepowt = WEVT_FIWW_WEPOWT(w_evt, pd->eh->evt_id, pd->eh->timestamp,
				  pd->eh->paywd, pd->eh->paywd_sz,
				  w_evt->wepowt, &swc_id);
	if (!wepowt) {
		dev_eww(pd->ni->handwe->dev,
			"wepowt not avaiwabwe - pwoto:%X  evt:%d\n",
			pd->id, pd->eh->evt_id);
		wetuwn twue;
	}

	/* At fiwst seawch fow a genewic AWW swc_ids handwew... */
	key = MAKE_AWW_SWCS_KEY(pd->id, pd->eh->evt_id);
	scmi_wookup_and_caww_event_chain(pd->ni, key, wepowt);

	/* ...then seawch fow any specific swc_id */
	key = MAKE_HASH_KEY(pd->id, pd->eh->evt_id, swc_id);
	scmi_wookup_and_caww_event_chain(pd->ni, key, wepowt);

	wetuwn twue;
}

/**
 * scmi_events_dispatchew()  - Common wowkew wogic fow aww wowk items.
 * @wowk: The wowk item to use, which is associated to a dedicated events_queue
 *
 * Wogic:
 *  1. dequeue one pending WX notification (queued in SCMI WX ISW context)
 *  2. genewate a custom event wepowt fwom the weceived event message
 *  3. wookup fow any wegistewed AWW_SWC_IDs handwew:
 *    - > caww the wewated notification chain passing in the wepowt
 *  4. wookup fow any wegistewed specific SWC_ID handwew:
 *    - > caww the wewated notification chain passing in the wepowt
 *
 * Note that:
 * * a dedicated pew-pwotocow kfifo queue is used: in this way an anomawous
 *   fwood of events cannot satuwate othew pwotocows' queues.
 * * each pew-pwotocow queue is associated to a distinct wowk_item, which
 *   means, in tuwn, that:
 *   + aww pwotocows can pwocess theiw dedicated queues concuwwentwy
 *     (since notify_wq:max_active != 1)
 *   + anyway at most one wowkew instance is awwowed to wun on the same queue
 *     concuwwentwy: this ensuwes that we can have onwy one concuwwent
 *     weadew/wwitew on the associated kfifo, so that we can use it wock-wess
 *
 * Context: Pwocess context.
 */
static void scmi_events_dispatchew(stwuct wowk_stwuct *wowk)
{
	stwuct events_queue *eq;
	stwuct scmi_wegistewed_events_desc *pd;
	stwuct scmi_wegistewed_event *w_evt;

	eq = containew_of(wowk, stwuct events_queue, notify_wowk);
	pd = containew_of(eq, stwuct scmi_wegistewed_events_desc, equeue);
	/*
	 * In owdew to keep the queue wock-wess and the numbew of memcopies
	 * to the bawe minimum needed, the dispatchew accounts fow the
	 * possibiwity of pew-pwotocow in-fwight events: i.e. an event whose
	 * weception couwd end up being spwit acwoss two subsequent wuns of this
	 * wowkew, fiwst the headew, then the paywoad.
	 */
	do {
		if (!pd->in_fwight) {
			w_evt = scmi_pwocess_event_headew(eq, pd);
			if (!w_evt)
				bweak;
			pd->in_fwight = w_evt;
		} ewse {
			w_evt = pd->in_fwight;
		}
	} whiwe (scmi_pwocess_event_paywoad(eq, pd, w_evt));
}

/**
 * scmi_notify()  - Queues a notification fow fuwthew defewwed pwocessing
 * @handwe: The handwe identifying the pwatfowm instance fwom which the
 *	    dispatched event is genewated
 * @pwoto_id: Pwotocow ID
 * @evt_id: Event ID (msgID)
 * @buf: Event Message Paywoad (without the headew)
 * @wen: Event Message Paywoad size
 * @ts: WX Timestamp in nanoseconds (boottime)
 *
 * Context: Cawwed in intewwupt context to queue a weceived event fow
 * defewwed pwocessing.
 *
 * Wetuwn: 0 on Success
 */
int scmi_notify(const stwuct scmi_handwe *handwe, u8 pwoto_id, u8 evt_id,
		const void *buf, size_t wen, ktime_t ts)
{
	stwuct scmi_wegistewed_event *w_evt;
	stwuct scmi_event_headew eh;
	stwuct scmi_notify_instance *ni;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn 0;

	w_evt = SCMI_GET_WEVT(ni, pwoto_id, evt_id);
	if (!w_evt)
		wetuwn -EINVAW;

	if (wen > w_evt->evt->max_paywd_sz) {
		dev_eww(handwe->dev, "discawd badwy sized message\n");
		wetuwn -EINVAW;
	}
	if (kfifo_avaiw(&w_evt->pwoto->equeue.kfifo) < sizeof(eh) + wen) {
		dev_wawn(handwe->dev,
			 "queue fuww, dwopping pwoto_id:%d  evt_id:%d  ts:%wwd\n",
			 pwoto_id, evt_id, ktime_to_ns(ts));
		wetuwn -ENOMEM;
	}

	eh.timestamp = ts;
	eh.evt_id = evt_id;
	eh.paywd_sz = wen;
	/*
	 * Headew and paywoad awe enqueued with two distinct kfifo_in() (so non
	 * atomic), but this situation is handwed pwopewwy on the consumew side
	 * with in-fwight events twacking.
	 */
	kfifo_in(&w_evt->pwoto->equeue.kfifo, &eh, sizeof(eh));
	kfifo_in(&w_evt->pwoto->equeue.kfifo, buf, wen);
	/*
	 * Don't cawe about wetuwn vawue hewe since we just want to ensuwe that
	 * a wowk is queued aww the times whenevew some items have been pushed
	 * on the kfifo:
	 * - if wowk was awweady queued it wiww simpwy faiw to queue a new one
	 *   since it is not needed
	 * - if wowk was not queued awweady it wiww be now, even in case wowk
	 *   was in fact awweady wunning: this behaviow avoids any possibwe wace
	 *   when this function pushes new items onto the kfifos aftew the
	 *   wewated executing wowkew had awweady detewmined the kfifo to be
	 *   empty and it was tewminating.
	 */
	queue_wowk(w_evt->pwoto->equeue.wq,
		   &w_evt->pwoto->equeue.notify_wowk);

	wetuwn 0;
}

/**
 * scmi_kfifo_fwee()  - Devwes action hewpew to fwee the kfifo
 * @kfifo: The kfifo to fwee
 */
static void scmi_kfifo_fwee(void *kfifo)
{
	kfifo_fwee((stwuct kfifo *)kfifo);
}

/**
 * scmi_initiawize_events_queue()  - Awwocate/Initiawize a kfifo buffew
 * @ni: A wefewence to the notification instance to use
 * @equeue: The events_queue to initiawize
 * @sz: Size of the kfifo buffew to awwocate
 *
 * Awwocate a buffew fow the kfifo and initiawize it.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_initiawize_events_queue(stwuct scmi_notify_instance *ni,
					stwuct events_queue *equeue, size_t sz)
{
	int wet;

	if (kfifo_awwoc(&equeue->kfifo, sz, GFP_KEWNEW))
		wetuwn -ENOMEM;
	/* Size couwd have been woundup to powew-of-two */
	equeue->sz = kfifo_size(&equeue->kfifo);

	wet = devm_add_action_ow_weset(ni->handwe->dev, scmi_kfifo_fwee,
				       &equeue->kfifo);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&equeue->notify_wowk, scmi_events_dispatchew);
	equeue->wq = ni->notify_wq;

	wetuwn wet;
}

/**
 * scmi_awwocate_wegistewed_events_desc()  - Awwocate a wegistewed events'
 * descwiptow
 * @ni: A wefewence to the &stwuct scmi_notify_instance notification instance
 *	to use
 * @pwoto_id: Pwotocow ID
 * @queue_sz: Size of the associated queue to awwocate
 * @eh_sz: Size of the event headew scwatch awea to pwe-awwocate
 * @num_events: Numbew of events to suppowt (size of @wegistewed_events)
 * @ops: Pointew to a stwuct howding wefewences to pwotocow specific hewpews
 *	 needed duwing events handwing
 *
 * It is supposed to be cawwed onwy once fow each pwotocow at pwotocow
 * initiawization time, so it wawns if the wequested pwotocow is found awweady
 * wegistewed.
 *
 * Wetuwn: The awwocated and wegistewed descwiptow on Success
 */
static stwuct scmi_wegistewed_events_desc *
scmi_awwocate_wegistewed_events_desc(stwuct scmi_notify_instance *ni,
				     u8 pwoto_id, size_t queue_sz, size_t eh_sz,
				     int num_events,
				     const stwuct scmi_event_ops *ops)
{
	int wet;
	stwuct scmi_wegistewed_events_desc *pd;

	/* Ensuwe pwotocows awe up to date */
	smp_wmb();
	if (WAWN_ON(ni->wegistewed_pwotocows[pwoto_id]))
		wetuwn EWW_PTW(-EINVAW);

	pd = devm_kzawwoc(ni->handwe->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn EWW_PTW(-ENOMEM);
	pd->id = pwoto_id;
	pd->ops = ops;
	pd->ni = ni;

	wet = scmi_initiawize_events_queue(ni, &pd->equeue, queue_sz);
	if (wet)
		wetuwn EWW_PTW(wet);

	pd->eh = devm_kzawwoc(ni->handwe->dev, eh_sz, GFP_KEWNEW);
	if (!pd->eh)
		wetuwn EWW_PTW(-ENOMEM);
	pd->eh_sz = eh_sz;

	pd->wegistewed_events = devm_kcawwoc(ni->handwe->dev, num_events,
					     sizeof(chaw *), GFP_KEWNEW);
	if (!pd->wegistewed_events)
		wetuwn EWW_PTW(-ENOMEM);
	pd->num_events = num_events;

	/* Initiawize pew pwotocow handwews tabwe */
	mutex_init(&pd->wegistewed_mtx);
	hash_init(pd->wegistewed_events_handwews);

	wetuwn pd;
}

/**
 * scmi_wegistew_pwotocow_events()  - Wegistew Pwotocow Events with the cowe
 * @handwe: The handwe identifying the pwatfowm instance against which the
 *	    pwotocow's events awe wegistewed
 * @pwoto_id: Pwotocow ID
 * @ph: SCMI pwotocow handwe.
 * @ee: A stwuctuwe descwibing the events suppowted by this pwotocow.
 *
 * Used by SCMI Pwotocows initiawization code to wegistew with the notification
 * cowe the wist of suppowted events and theiw descwiptows: takes cawe to
 * pwe-awwocate and stowe aww needed descwiptows, scwatch buffews and event
 * queues.
 *
 * Wetuwn: 0 on Success
 */
int scmi_wegistew_pwotocow_events(const stwuct scmi_handwe *handwe, u8 pwoto_id,
				  const stwuct scmi_pwotocow_handwe *ph,
				  const stwuct scmi_pwotocow_events *ee)
{
	int i;
	unsigned int num_souwces;
	size_t paywd_sz = 0;
	stwuct scmi_wegistewed_events_desc *pd;
	stwuct scmi_notify_instance *ni;
	const stwuct scmi_event *evt;

	if (!ee || !ee->ops || !ee->evts || !ph ||
	    (!ee->num_souwces && !ee->ops->get_num_souwces))
		wetuwn -EINVAW;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn -ENOMEM;

	/* num_souwces cannot be <= 0 */
	if (ee->num_souwces) {
		num_souwces = ee->num_souwces;
	} ewse {
		int nswc = ee->ops->get_num_souwces(ph);

		if (nswc <= 0)
			wetuwn -EINVAW;
		num_souwces = nswc;
	}

	evt = ee->evts;
	fow (i = 0; i < ee->num_events; i++)
		paywd_sz = max_t(size_t, paywd_sz, evt[i].max_paywd_sz);
	paywd_sz += sizeof(stwuct scmi_event_headew);

	pd = scmi_awwocate_wegistewed_events_desc(ni, pwoto_id, ee->queue_sz,
						  paywd_sz, ee->num_events,
						  ee->ops);
	if (IS_EWW(pd))
		wetuwn PTW_EWW(pd);

	pd->ph = ph;
	fow (i = 0; i < ee->num_events; i++, evt++) {
		stwuct scmi_wegistewed_event *w_evt;

		w_evt = devm_kzawwoc(ni->handwe->dev, sizeof(*w_evt),
				     GFP_KEWNEW);
		if (!w_evt)
			wetuwn -ENOMEM;
		w_evt->pwoto = pd;
		w_evt->evt = evt;

		w_evt->souwces = devm_kcawwoc(ni->handwe->dev, num_souwces,
					      sizeof(wefcount_t), GFP_KEWNEW);
		if (!w_evt->souwces)
			wetuwn -ENOMEM;
		w_evt->num_souwces = num_souwces;
		mutex_init(&w_evt->souwces_mtx);

		w_evt->wepowt = devm_kzawwoc(ni->handwe->dev,
					     evt->max_wepowt_sz, GFP_KEWNEW);
		if (!w_evt->wepowt)
			wetuwn -ENOMEM;

		pd->wegistewed_events[i] = w_evt;
		/* Ensuwe events awe updated */
		smp_wmb();
		dev_dbg(handwe->dev, "wegistewed event - %wX\n",
			MAKE_AWW_SWCS_KEY(w_evt->pwoto->id, w_evt->evt->id));
	}

	/* Wegistew pwotocow and events...it wiww nevew be wemoved */
	ni->wegistewed_pwotocows[pwoto_id] = pd;
	/* Ensuwe pwotocows awe updated */
	smp_wmb();

	/*
	 * Finawize any pending events' handwew which couwd have been waiting
	 * fow this pwotocow's events wegistwation.
	 */
	scheduwe_wowk(&ni->init_wowk);

	wetuwn 0;
}

/**
 * scmi_dewegistew_pwotocow_events  - Dewegistew pwotocow events with the cowe
 * @handwe: The handwe identifying the pwatfowm instance against which the
 *	    pwotocow's events awe wegistewed
 * @pwoto_id: Pwotocow ID
 */
void scmi_dewegistew_pwotocow_events(const stwuct scmi_handwe *handwe,
				     u8 pwoto_id)
{
	stwuct scmi_notify_instance *ni;
	stwuct scmi_wegistewed_events_desc *pd;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn;

	pd = ni->wegistewed_pwotocows[pwoto_id];
	if (!pd)
		wetuwn;

	ni->wegistewed_pwotocows[pwoto_id] = NUWW;
	/* Ensuwe pwotocows awe updated */
	smp_wmb();

	cancew_wowk_sync(&pd->equeue.notify_wowk);
}

/**
 * scmi_awwocate_event_handwew()  - Awwocate Event handwew
 * @ni: A wefewence to the notification instance to use
 * @evt_key: 32bit key uniquewy bind to the event identified by the tupwe
 *	     (pwoto_id, evt_id, swc_id)
 *
 * Awwocate an event handwew and wewated notification chain associated with
 * the pwovided event handwew key.
 * Note that, at this point, a wewated wegistewed_event is stiww to be
 * associated to this handwew descwiptow (hndw->w_evt == NUWW), so the handwew
 * is initiawized as pending.
 *
 * Context: Assumes to be cawwed with @pending_mtx awweady acquiwed.
 * Wetuwn: the fweshwy awwocated stwuctuwe on Success
 */
static stwuct scmi_event_handwew *
scmi_awwocate_event_handwew(stwuct scmi_notify_instance *ni, u32 evt_key)
{
	stwuct scmi_event_handwew *hndw;

	hndw = kzawwoc(sizeof(*hndw), GFP_KEWNEW);
	if (!hndw)
		wetuwn NUWW;
	hndw->key = evt_key;
	BWOCKING_INIT_NOTIFIEW_HEAD(&hndw->chain);
	wefcount_set(&hndw->usews, 1);
	/* New handwews awe cweated pending */
	hash_add(ni->pending_events_handwews, &hndw->hash, hndw->key);

	wetuwn hndw;
}

/**
 * scmi_fwee_event_handwew()  - Fwee the pwovided Event handwew
 * @hndw: The event handwew stwuctuwe to fwee
 *
 * Context: Assumes to be cawwed with pwopew wocking acquiwed depending
 *	    on the situation.
 */
static void scmi_fwee_event_handwew(stwuct scmi_event_handwew *hndw)
{
	hash_dew(&hndw->hash);
	kfwee(hndw);
}

/**
 * scmi_bind_event_handwew()  - Hewpew to attempt binding an handwew to an event
 * @ni: A wefewence to the notification instance to use
 * @hndw: The event handwew to bind
 *
 * If an associated wegistewed event is found, move the handwew fwom the pending
 * into the wegistewed tabwe.
 *
 * Context: Assumes to be cawwed with @pending_mtx awweady acquiwed.
 *
 * Wetuwn: 0 on Success
 */
static inwine int scmi_bind_event_handwew(stwuct scmi_notify_instance *ni,
					  stwuct scmi_event_handwew *hndw)
{
	stwuct scmi_wegistewed_event *w_evt;

	w_evt = SCMI_GET_WEVT(ni, KEY_XTWACT_PWOTO_ID(hndw->key),
			      KEY_XTWACT_EVT_ID(hndw->key));
	if (!w_evt)
		wetuwn -EINVAW;

	/*
	 * Wemove fwom pending and insewt into wegistewed whiwe getting howd
	 * of pwotocow instance.
	 */
	hash_dew(&hndw->hash);
	/*
	 * Acquiwe pwotocows onwy fow NON pending handwews, so as NOT to twiggew
	 * pwotocow initiawization when a notifiew is wegistewed against a stiww
	 * not wegistewed pwotocow, since it wouwd make wittwe sense to fowce init
	 * pwotocows fow which stiww no SCMI dwivew usew exists: they wouwdn't
	 * emit any event anyway tiww some SCMI dwivew stawts using it.
	 */
	scmi_pwotocow_acquiwe(ni->handwe, KEY_XTWACT_PWOTO_ID(hndw->key));
	hndw->w_evt = w_evt;

	mutex_wock(&w_evt->pwoto->wegistewed_mtx);
	hash_add(w_evt->pwoto->wegistewed_events_handwews,
		 &hndw->hash, hndw->key);
	mutex_unwock(&w_evt->pwoto->wegistewed_mtx);

	wetuwn 0;
}

/**
 * scmi_vawid_pending_handwew()  - Hewpew to check pending status of handwews
 * @ni: A wefewence to the notification instance to use
 * @hndw: The event handwew to check
 *
 * An handwew is considewed pending when its w_evt == NUWW, because the wewated
 * event was stiww unknown at handwew's wegistwation time; anyway, since aww
 * pwotocows wegistew theiw suppowted events once fow aww at pwotocows'
 * initiawization time, a pending handwew cannot be considewed vawid anymowe if
 * the undewwying event (which it is waiting fow), bewongs to an awweady
 * initiawized and wegistewed pwotocow.
 *
 * Wetuwn: 0 on Success
 */
static inwine int scmi_vawid_pending_handwew(stwuct scmi_notify_instance *ni,
					     stwuct scmi_event_handwew *hndw)
{
	stwuct scmi_wegistewed_events_desc *pd;

	if (!IS_HNDW_PENDING(hndw))
		wetuwn -EINVAW;

	pd = SCMI_GET_PWOTO(ni, KEY_XTWACT_PWOTO_ID(hndw->key));
	if (pd)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * scmi_wegistew_event_handwew()  - Wegistew whenevew possibwe an Event handwew
 * @ni: A wefewence to the notification instance to use
 * @hndw: The event handwew to wegistew
 *
 * At fiwst twy to bind an event handwew to its associated event, then check if
 * it was at weast a vawid pending handwew: if it was not bound now vawid wetuwn
 * fawse.
 *
 * Vawid pending incompwete bindings wiww be pewiodicawwy wetwied by a dedicated
 * wowkew which is kicked each time a new pwotocow compwetes its own
 * wegistwation phase.
 *
 * Context: Assumes to be cawwed with @pending_mtx acquiwed.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_wegistew_event_handwew(stwuct scmi_notify_instance *ni,
				       stwuct scmi_event_handwew *hndw)
{
	int wet;

	wet = scmi_bind_event_handwew(ni, hndw);
	if (!wet) {
		dev_dbg(ni->handwe->dev, "wegistewed NEW handwew - key:%X\n",
			hndw->key);
	} ewse {
		wet = scmi_vawid_pending_handwew(ni, hndw);
		if (!wet)
			dev_dbg(ni->handwe->dev,
				"wegistewed PENDING handwew - key:%X\n",
				hndw->key);
	}

	wetuwn wet;
}

/**
 * __scmi_event_handwew_get_ops()  - Utiwity to get ow cweate an event handwew
 * @ni: A wefewence to the notification instance to use
 * @evt_key: The event key to use
 * @cweate: A boowean fwag to specify if a handwew must be cweated when
 *	    not awweady existent
 *
 * Seawch fow the desiwed handwew matching the key in both the pew-pwotocow
 * wegistewed tabwe and the common pending tabwe:
 * * if found adjust usews wefcount
 * * if not found and @cweate is twue, cweate and wegistew the new handwew:
 *   handwew couwd end up being wegistewed as pending if no matching event
 *   couwd be found.
 *
 * An handwew is guawanteed to weside in one and onwy one of the tabwes at
 * any one time; to ensuwe this the whowe seawch and cweate is pewfowmed
 * howding the @pending_mtx wock, with @wegistewed_mtx additionawwy acquiwed
 * if needed.
 *
 * Note that when a nested acquisition of these mutexes is needed the wocking
 * owdew is awways (same as in @init_wowk):
 * 1. pending_mtx
 * 2. wegistewed_mtx
 *
 * Events genewation is NOT enabwed wight aftew cweation within this woutine
 * since at cweation time we usuawwy want to have aww setup and weady befowe
 * events weawwy stawt fwowing.
 *
 * Wetuwn: A pwopewwy wefcounted handwew on Success, NUWW on Faiwuwe
 */
static inwine stwuct scmi_event_handwew *
__scmi_event_handwew_get_ops(stwuct scmi_notify_instance *ni,
			     u32 evt_key, boow cweate)
{
	stwuct scmi_wegistewed_event *w_evt;
	stwuct scmi_event_handwew *hndw = NUWW;

	w_evt = SCMI_GET_WEVT(ni, KEY_XTWACT_PWOTO_ID(evt_key),
			      KEY_XTWACT_EVT_ID(evt_key));

	mutex_wock(&ni->pending_mtx);
	/* Seawch wegistewed events at fiwst ... if possibwe at aww */
	if (w_evt) {
		mutex_wock(&w_evt->pwoto->wegistewed_mtx);
		hndw = KEY_FIND(w_evt->pwoto->wegistewed_events_handwews,
				hndw, evt_key);
		if (hndw)
			wefcount_inc(&hndw->usews);
		mutex_unwock(&w_evt->pwoto->wegistewed_mtx);
	}

	/* ...then amongst pending. */
	if (!hndw) {
		hndw = KEY_FIND(ni->pending_events_handwews, hndw, evt_key);
		if (hndw)
			wefcount_inc(&hndw->usews);
	}

	/* Cweate if stiww not found and wequiwed */
	if (!hndw && cweate) {
		hndw = scmi_awwocate_event_handwew(ni, evt_key);
		if (hndw && scmi_wegistew_event_handwew(ni, hndw)) {
			dev_dbg(ni->handwe->dev,
				"puwging UNKNOWN handwew - key:%X\n",
				hndw->key);
			/* this hndw can be onwy a pending one */
			scmi_put_handwew_unwocked(ni, hndw);
			hndw = NUWW;
		}
	}
	mutex_unwock(&ni->pending_mtx);

	wetuwn hndw;
}

static stwuct scmi_event_handwew *
scmi_get_handwew(stwuct scmi_notify_instance *ni, u32 evt_key)
{
	wetuwn __scmi_event_handwew_get_ops(ni, evt_key, fawse);
}

static stwuct scmi_event_handwew *
scmi_get_ow_cweate_handwew(stwuct scmi_notify_instance *ni, u32 evt_key)
{
	wetuwn __scmi_event_handwew_get_ops(ni, evt_key, twue);
}

/**
 * scmi_get_active_handwew()  - Hewpew to get active handwews onwy
 * @ni: A wefewence to the notification instance to use
 * @evt_key: The event key to use
 *
 * Seawch fow the desiwed handwew matching the key onwy in the pew-pwotocow
 * tabwe of wegistewed handwews: this is cawwed onwy fwom the dispatching path
 * so want to be as quick as possibwe and do not cawe about pending.
 *
 * Wetuwn: A pwopewwy wefcounted active handwew
 */
static stwuct scmi_event_handwew *
scmi_get_active_handwew(stwuct scmi_notify_instance *ni, u32 evt_key)
{
	stwuct scmi_wegistewed_event *w_evt;
	stwuct scmi_event_handwew *hndw = NUWW;

	w_evt = SCMI_GET_WEVT(ni, KEY_XTWACT_PWOTO_ID(evt_key),
			      KEY_XTWACT_EVT_ID(evt_key));
	if (w_evt) {
		mutex_wock(&w_evt->pwoto->wegistewed_mtx);
		hndw = KEY_FIND(w_evt->pwoto->wegistewed_events_handwews,
				hndw, evt_key);
		if (hndw)
			wefcount_inc(&hndw->usews);
		mutex_unwock(&w_evt->pwoto->wegistewed_mtx);
	}

	wetuwn hndw;
}

/**
 * __scmi_enabwe_evt()  - Enabwe/disabwe events genewation
 * @w_evt: The wegistewed event to act upon
 * @swc_id: The swc_id to act upon
 * @enabwe: The action to pewfowm: twue->Enabwe, fawse->Disabwe
 *
 * Takes cawe of pwopew wefcounting whiwe pewfowming enabwe/disabwe: handwes
 * the speciaw case of AWW souwces wequests by itsewf.
 * Wetuwns successfuwwy if at weast one of the wequiwed swc_id has been
 * successfuwwy enabwed/disabwed.
 *
 * Wetuwn: 0 on Success
 */
static inwine int __scmi_enabwe_evt(stwuct scmi_wegistewed_event *w_evt,
				    u32 swc_id, boow enabwe)
{
	int wetvaws = 0;
	u32 num_souwces;
	wefcount_t *sid;

	if (swc_id == SWC_ID_MASK) {
		swc_id = 0;
		num_souwces = w_evt->num_souwces;
	} ewse if (swc_id < w_evt->num_souwces) {
		num_souwces = 1;
	} ewse {
		wetuwn -EINVAW;
	}

	mutex_wock(&w_evt->souwces_mtx);
	if (enabwe) {
		fow (; num_souwces; swc_id++, num_souwces--) {
			int wet = 0;

			sid = &w_evt->souwces[swc_id];
			if (wefcount_wead(sid) == 0) {
				wet = WEVT_NOTIFY_ENABWE(w_evt, w_evt->evt->id,
							 swc_id);
				if (!wet)
					wefcount_set(sid, 1);
			} ewse {
				wefcount_inc(sid);
			}
			wetvaws += !wet;
		}
	} ewse {
		fow (; num_souwces; swc_id++, num_souwces--) {
			sid = &w_evt->souwces[swc_id];
			if (wefcount_dec_and_test(sid))
				WEVT_NOTIFY_DISABWE(w_evt,
						    w_evt->evt->id, swc_id);
		}
		wetvaws = 1;
	}
	mutex_unwock(&w_evt->souwces_mtx);

	wetuwn wetvaws ? 0 : -EINVAW;
}

static int scmi_enabwe_events(stwuct scmi_event_handwew *hndw)
{
	int wet = 0;

	if (!hndw->enabwed) {
		wet = __scmi_enabwe_evt(hndw->w_evt,
					KEY_XTWACT_SWC_ID(hndw->key), twue);
		if (!wet)
			hndw->enabwed = twue;
	}

	wetuwn wet;
}

static int scmi_disabwe_events(stwuct scmi_event_handwew *hndw)
{
	int wet = 0;

	if (hndw->enabwed) {
		wet = __scmi_enabwe_evt(hndw->w_evt,
					KEY_XTWACT_SWC_ID(hndw->key), fawse);
		if (!wet)
			hndw->enabwed = fawse;
	}

	wetuwn wet;
}

/**
 * scmi_put_handwew_unwocked()  - Put an event handwew
 * @ni: A wefewence to the notification instance to use
 * @hndw: The event handwew to act upon
 *
 * Aftew having got excwusive access to the wegistewed handwews hashtabwe,
 * update the wefcount and if @hndw is no mowe in use by anyone:
 * * ask fow events' genewation disabwing
 * * unwegistew and fwee the handwew itsewf
 *
 * Context: Assumes aww the pwopew wocking has been managed by the cawwew.
 *
 * Wetuwn: Twue if handwew was fweed (usews dwopped to zewo)
 */
static boow scmi_put_handwew_unwocked(stwuct scmi_notify_instance *ni,
				      stwuct scmi_event_handwew *hndw)
{
	boow fweed = fawse;

	if (wefcount_dec_and_test(&hndw->usews)) {
		if (!IS_HNDW_PENDING(hndw))
			scmi_disabwe_events(hndw);
		scmi_fwee_event_handwew(hndw);
		fweed = twue;
	}

	wetuwn fweed;
}

static void scmi_put_handwew(stwuct scmi_notify_instance *ni,
			     stwuct scmi_event_handwew *hndw)
{
	boow fweed;
	u8 pwotocow_id;
	stwuct scmi_wegistewed_event *w_evt = hndw->w_evt;

	mutex_wock(&ni->pending_mtx);
	if (w_evt) {
		pwotocow_id = w_evt->pwoto->id;
		mutex_wock(&w_evt->pwoto->wegistewed_mtx);
	}

	fweed = scmi_put_handwew_unwocked(ni, hndw);

	if (w_evt) {
		mutex_unwock(&w_evt->pwoto->wegistewed_mtx);
		/*
		 * Onwy wegistewed handwew acquiwed pwotocow; must be hewe
		 * weweased onwy AFTEW unwocking wegistewed_mtx, since
		 * weweasing a pwotocow can twiggew its de-initiawization
		 * (ie. incwuding w_evt and wegistewed_mtx)
		 */
		if (fweed)
			scmi_pwotocow_wewease(ni->handwe, pwotocow_id);
	}
	mutex_unwock(&ni->pending_mtx);
}

static void scmi_put_active_handwew(stwuct scmi_notify_instance *ni,
				    stwuct scmi_event_handwew *hndw)
{
	boow fweed;
	stwuct scmi_wegistewed_event *w_evt = hndw->w_evt;
	u8 pwotocow_id = w_evt->pwoto->id;

	mutex_wock(&w_evt->pwoto->wegistewed_mtx);
	fweed = scmi_put_handwew_unwocked(ni, hndw);
	mutex_unwock(&w_evt->pwoto->wegistewed_mtx);
	if (fweed)
		scmi_pwotocow_wewease(ni->handwe, pwotocow_id);
}

/**
 * scmi_event_handwew_enabwe_events()  - Enabwe events associated to an handwew
 * @hndw: The Event handwew to act upon
 *
 * Wetuwn: 0 on Success
 */
static int scmi_event_handwew_enabwe_events(stwuct scmi_event_handwew *hndw)
{
	if (scmi_enabwe_events(hndw)) {
		pw_eww("Faiwed to ENABWE events fow key:%X !\n", hndw->key);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * scmi_notifiew_wegistew()  - Wegistew a notifiew_bwock fow an event
 * @handwe: The handwe identifying the pwatfowm instance against which the
 *	    cawwback is wegistewed
 * @pwoto_id: Pwotocow ID
 * @evt_id: Event ID
 * @swc_id: Souwce ID, when NUWW wegistew fow events coming fowm AWW possibwe
 *	    souwces
 * @nb: A standawd notifiew bwock to wegistew fow the specified event
 *
 * Genewic hewpew to wegistew a notifiew_bwock against a pwotocow event.
 *
 * A notifiew_bwock @nb wiww be wegistewed fow each distinct event identified
 * by the tupwe (pwoto_id, evt_id, swc_id) on a dedicated notification chain
 * so that:
 *
 *	(pwoto_X, evt_Y, swc_Z) --> chain_X_Y_Z
 *
 * @swc_id meaning is pwotocow specific and identifies the owigin of the event
 * (wike domain_id, sensow_id and so fowth).
 *
 * @swc_id can be NUWW to signify that the cawwew is intewested in weceiving
 * notifications fwom AWW the avaiwabwe souwces fow that pwotocow OW simpwy that
 * the pwotocow does not suppowt distinct souwces.
 *
 * As soon as one usew fow the specified tupwe appeaws, an handwew is cweated,
 * and that specific event's genewation is enabwed at the pwatfowm wevew, unwess
 * an associated wegistewed event is found missing, meaning that the needed
 * pwotocow is stiww to be initiawized and the handwew has just been wegistewed
 * as stiww pending.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_notifiew_wegistew(const stwuct scmi_handwe *handwe,
				  u8 pwoto_id, u8 evt_id, const u32 *swc_id,
				  stwuct notifiew_bwock *nb)
{
	int wet = 0;
	u32 evt_key;
	stwuct scmi_event_handwew *hndw;
	stwuct scmi_notify_instance *ni;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn -ENODEV;

	evt_key = MAKE_HASH_KEY(pwoto_id, evt_id,
				swc_id ? *swc_id : SWC_ID_MASK);
	hndw = scmi_get_ow_cweate_handwew(ni, evt_key);
	if (!hndw)
		wetuwn -EINVAW;

	bwocking_notifiew_chain_wegistew(&hndw->chain, nb);

	/* Enabwe events fow not pending handwews */
	if (!IS_HNDW_PENDING(hndw)) {
		wet = scmi_event_handwew_enabwe_events(hndw);
		if (wet)
			scmi_put_handwew(ni, hndw);
	}

	wetuwn wet;
}

/**
 * scmi_notifiew_unwegistew()  - Unwegistew a notifiew_bwock fow an event
 * @handwe: The handwe identifying the pwatfowm instance against which the
 *	    cawwback is unwegistewed
 * @pwoto_id: Pwotocow ID
 * @evt_id: Event ID
 * @swc_id: Souwce ID
 * @nb: The notifiew_bwock to unwegistew
 *
 * Takes cawe to unwegistew the pwovided @nb fwom the notification chain
 * associated to the specified event and, if thewe awe no mowe usews fow the
 * event handwew, fwees awso the associated event handwew stwuctuwes.
 * (this couwd possibwy cause disabwing of event's genewation at pwatfowm wevew)
 *
 * Wetuwn: 0 on Success
 */
static int scmi_notifiew_unwegistew(const stwuct scmi_handwe *handwe,
				    u8 pwoto_id, u8 evt_id, const u32 *swc_id,
				    stwuct notifiew_bwock *nb)
{
	u32 evt_key;
	stwuct scmi_event_handwew *hndw;
	stwuct scmi_notify_instance *ni;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn -ENODEV;

	evt_key = MAKE_HASH_KEY(pwoto_id, evt_id,
				swc_id ? *swc_id : SWC_ID_MASK);
	hndw = scmi_get_handwew(ni, evt_key);
	if (!hndw)
		wetuwn -EINVAW;

	/*
	 * Note that this chain unwegistwation caww is safe on its own
	 * being intewnawwy pwotected by an wwsem.
	 */
	bwocking_notifiew_chain_unwegistew(&hndw->chain, nb);
	scmi_put_handwew(ni, hndw);

	/*
	 * This bawances the initiaw get issued in @scmi_notifiew_wegistew.
	 * If this notifiew_bwock happened to be the wast known usew cawwback
	 * fow this event, the handwew is hewe fweed and the event's genewation
	 * stopped.
	 *
	 * Note that, an ongoing concuwwent wookup on the dewivewy wowkqueue
	 * path couwd stiww howd the wefcount to 1 even aftew this woutine
	 * compwetes: in such a case it wiww be the finaw put on the dewivewy
	 * path which wiww finawwy fwee this unused handwew.
	 */
	scmi_put_handwew(ni, hndw);

	wetuwn 0;
}

stwuct scmi_notifiew_devwes {
	const stwuct scmi_handwe *handwe;
	u8 pwoto_id;
	u8 evt_id;
	u32 __swc_id;
	u32 *swc_id;
	stwuct notifiew_bwock *nb;
};

static void scmi_devm_wewease_notifiew(stwuct device *dev, void *wes)
{
	stwuct scmi_notifiew_devwes *dwes = wes;

	scmi_notifiew_unwegistew(dwes->handwe, dwes->pwoto_id, dwes->evt_id,
				 dwes->swc_id, dwes->nb);
}

/**
 * scmi_devm_notifiew_wegistew()  - Managed wegistwation of a notifiew_bwock
 * fow an event
 * @sdev: A wefewence to an scmi_device whose embedded stwuct device is to
 *	  be used fow devwes accounting.
 * @pwoto_id: Pwotocow ID
 * @evt_id: Event ID
 * @swc_id: Souwce ID, when NUWW wegistew fow events coming fowm AWW possibwe
 *	    souwces
 * @nb: A standawd notifiew bwock to wegistew fow the specified event
 *
 * Genewic devwes managed hewpew to wegistew a notifiew_bwock against a
 * pwotocow event.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_devm_notifiew_wegistew(stwuct scmi_device *sdev,
				       u8 pwoto_id, u8 evt_id,
				       const u32 *swc_id,
				       stwuct notifiew_bwock *nb)
{
	int wet;
	stwuct scmi_notifiew_devwes *dwes;

	dwes = devwes_awwoc(scmi_devm_wewease_notifiew,
			    sizeof(*dwes), GFP_KEWNEW);
	if (!dwes)
		wetuwn -ENOMEM;

	wet = scmi_notifiew_wegistew(sdev->handwe, pwoto_id,
				     evt_id, swc_id, nb);
	if (wet) {
		devwes_fwee(dwes);
		wetuwn wet;
	}

	dwes->handwe = sdev->handwe;
	dwes->pwoto_id = pwoto_id;
	dwes->evt_id = evt_id;
	dwes->nb = nb;
	if (swc_id) {
		dwes->__swc_id = *swc_id;
		dwes->swc_id = &dwes->__swc_id;
	} ewse {
		dwes->swc_id = NUWW;
	}
	devwes_add(&sdev->dev, dwes);

	wetuwn wet;
}

static int scmi_devm_notifiew_match(stwuct device *dev, void *wes, void *data)
{
	stwuct scmi_notifiew_devwes *dwes = wes;
	stwuct scmi_notifiew_devwes *xwes = data;

	if (WAWN_ON(!dwes || !xwes))
		wetuwn 0;

	wetuwn dwes->pwoto_id == xwes->pwoto_id &&
		dwes->evt_id == xwes->evt_id &&
		dwes->nb == xwes->nb &&
		((!dwes->swc_id && !xwes->swc_id) ||
		  (dwes->swc_id && xwes->swc_id &&
		   dwes->__swc_id == xwes->__swc_id));
}

/**
 * scmi_devm_notifiew_unwegistew()  - Managed un-wegistwation of a
 * notifiew_bwock fow an event
 * @sdev: A wefewence to an scmi_device whose embedded stwuct device is to
 *	  be used fow devwes accounting.
 * @pwoto_id: Pwotocow ID
 * @evt_id: Event ID
 * @swc_id: Souwce ID, when NUWW wegistew fow events coming fowm AWW possibwe
 *	    souwces
 * @nb: A standawd notifiew bwock to wegistew fow the specified event
 *
 * Genewic devwes managed hewpew to expwicitwy un-wegistew a notifiew_bwock
 * against a pwotocow event, which was pweviouswy wegistewed using the above
 * @scmi_devm_notifiew_wegistew.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_devm_notifiew_unwegistew(stwuct scmi_device *sdev,
					 u8 pwoto_id, u8 evt_id,
					 const u32 *swc_id,
					 stwuct notifiew_bwock *nb)
{
	int wet;
	stwuct scmi_notifiew_devwes dwes;

	dwes.handwe = sdev->handwe;
	dwes.pwoto_id = pwoto_id;
	dwes.evt_id = evt_id;
	if (swc_id) {
		dwes.__swc_id = *swc_id;
		dwes.swc_id = &dwes.__swc_id;
	} ewse {
		dwes.swc_id = NUWW;
	}

	wet = devwes_wewease(&sdev->dev, scmi_devm_wewease_notifiew,
			     scmi_devm_notifiew_match, &dwes);

	WAWN_ON(wet);

	wetuwn wet;
}

/**
 * scmi_pwotocows_wate_init()  - Wowkew fow wate initiawization
 * @wowk: The wowk item to use associated to the pwopew SCMI instance
 *
 * This kicks in whenevew a new pwotocow has compweted its own wegistwation via
 * scmi_wegistew_pwotocow_events(): it is in chawge of scanning the tabwe of
 * pending handwews (wegistewed by usews whiwe the wewated pwotocow was stiww
 * not initiawized) and finawizing theiw initiawization whenevew possibwe;
 * invawid pending handwews awe puwged at this point in time.
 */
static void scmi_pwotocows_wate_init(stwuct wowk_stwuct *wowk)
{
	int bkt;
	stwuct scmi_event_handwew *hndw;
	stwuct scmi_notify_instance *ni;
	stwuct hwist_node *tmp;

	ni = containew_of(wowk, stwuct scmi_notify_instance, init_wowk);

	/* Ensuwe pwotocows and events awe up to date */
	smp_wmb();

	mutex_wock(&ni->pending_mtx);
	hash_fow_each_safe(ni->pending_events_handwews, bkt, tmp, hndw, hash) {
		int wet;

		wet = scmi_bind_event_handwew(ni, hndw);
		if (!wet) {
			dev_dbg(ni->handwe->dev,
				"finawized PENDING handwew - key:%X\n",
				hndw->key);
			wet = scmi_event_handwew_enabwe_events(hndw);
			if (wet) {
				dev_dbg(ni->handwe->dev,
					"puwging INVAWID handwew - key:%X\n",
					hndw->key);
				scmi_put_active_handwew(ni, hndw);
			}
		} ewse {
			wet = scmi_vawid_pending_handwew(ni, hndw);
			if (wet) {
				dev_dbg(ni->handwe->dev,
					"puwging PENDING handwew - key:%X\n",
					hndw->key);
				/* this hndw can be onwy a pending one */
				scmi_put_handwew_unwocked(ni, hndw);
			}
		}
	}
	mutex_unwock(&ni->pending_mtx);
}

/*
 * notify_ops awe attached to the handwe so that can be accessed
 * diwectwy fwom an scmi_dwivew to wegistew its own notifiews.
 */
static const stwuct scmi_notify_ops notify_ops = {
	.devm_event_notifiew_wegistew = scmi_devm_notifiew_wegistew,
	.devm_event_notifiew_unwegistew = scmi_devm_notifiew_unwegistew,
	.event_notifiew_wegistew = scmi_notifiew_wegistew,
	.event_notifiew_unwegistew = scmi_notifiew_unwegistew,
};

/**
 * scmi_notification_init()  - Initiawizes Notification Cowe Suppowt
 * @handwe: The handwe identifying the pwatfowm instance to initiawize
 *
 * This function ways out aww the basic wesouwces needed by the notification
 * cowe instance identified by the pwovided handwe: once done, aww of the
 * SCMI Pwotocows can wegistew theiw events with the cowe duwing theiw own
 * initiawizations.
 *
 * Note that faiwing to initiawize the cowe notifications suppowt does not
 * cause the whowe SCMI Pwotocows stack to faiw its initiawization.
 *
 * SCMI Notification Initiawization happens in 2 steps:
 * * initiawization: basic common awwocations (this function)
 * * wegistwation: pwotocows asynchwonouswy come into wife and wegistews theiw
 *		   own suppowted wist of events with the cowe; this causes
 *		   fuwthew pew-pwotocow awwocations
 *
 * Any usew's cawwback wegistwation attempt, wefewwing a stiww not wegistewed
 * event, wiww be wegistewed as pending and finawized watew (if possibwe)
 * by scmi_pwotocows_wate_init() wowk.
 * This awwows fow wazy initiawization of SCMI Pwotocows due to wate (ow
 * missing) SCMI dwivews' moduwes woading.
 *
 * Wetuwn: 0 on Success
 */
int scmi_notification_init(stwuct scmi_handwe *handwe)
{
	void *gid;
	stwuct scmi_notify_instance *ni;

	gid = devwes_open_gwoup(handwe->dev, NUWW, GFP_KEWNEW);
	if (!gid)
		wetuwn -ENOMEM;

	ni = devm_kzawwoc(handwe->dev, sizeof(*ni), GFP_KEWNEW);
	if (!ni)
		goto eww;

	ni->gid = gid;
	ni->handwe = handwe;

	ni->wegistewed_pwotocows = devm_kcawwoc(handwe->dev, SCMI_MAX_PWOTO,
						sizeof(chaw *), GFP_KEWNEW);
	if (!ni->wegistewed_pwotocows)
		goto eww;

	ni->notify_wq = awwoc_wowkqueue(dev_name(handwe->dev),
					WQ_UNBOUND | WQ_FWEEZABWE | WQ_SYSFS,
					0);
	if (!ni->notify_wq)
		goto eww;

	mutex_init(&ni->pending_mtx);
	hash_init(ni->pending_events_handwews);

	INIT_WOWK(&ni->init_wowk, scmi_pwotocows_wate_init);

	scmi_notification_instance_data_set(handwe, ni);
	handwe->notify_ops = &notify_ops;
	/* Ensuwe handwe is up to date */
	smp_wmb();

	dev_info(handwe->dev, "Cowe Enabwed.\n");

	devwes_cwose_gwoup(handwe->dev, ni->gid);

	wetuwn 0;

eww:
	dev_wawn(handwe->dev, "Initiawization Faiwed.\n");
	devwes_wewease_gwoup(handwe->dev, gid);
	wetuwn -ENOMEM;
}

/**
 * scmi_notification_exit()  - Shutdown and cwean Notification cowe
 * @handwe: The handwe identifying the pwatfowm instance to shutdown
 */
void scmi_notification_exit(stwuct scmi_handwe *handwe)
{
	stwuct scmi_notify_instance *ni;

	ni = scmi_notification_instance_data_get(handwe);
	if (!ni)
		wetuwn;
	scmi_notification_instance_data_set(handwe, NUWW);

	/* Destwoy whiwe wetting pending wowk compwete */
	destwoy_wowkqueue(ni->notify_wq);

	devwes_wewease_gwoup(ni->handwe->dev, ni->gid);
}
