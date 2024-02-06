// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Chaw device fow device waw access
 *
 * Copywight (C) 2005-2007  Kwistian Hoegsbewg <kwh@bitpwanet.net>
 */

#incwude <winux/bug.h>
#incwude <winux/compat.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-cdev.h>
#incwude <winux/idw.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h> /* wequiwed fow winux/wait.h */
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>


#incwude "cowe.h"

/*
 * ABI vewsion histowy is documented in winux/fiwewiwe-cdev.h.
 */
#define FW_CDEV_KEWNEW_VEWSION			5
#define FW_CDEV_VEWSION_EVENT_WEQUEST2		4
#define FW_CDEV_VEWSION_AWWOCATE_WEGION_END	4
#define FW_CDEV_VEWSION_AUTO_FWUSH_ISO_OVEWFWOW	5
#define FW_CDEV_VEWSION_EVENT_ASYNC_TSTAMP	6

stwuct cwient {
	u32 vewsion;
	stwuct fw_device *device;

	spinwock_t wock;
	boow in_shutdown;
	stwuct idw wesouwce_idw;
	stwuct wist_head event_wist;
	wait_queue_head_t wait;
	wait_queue_head_t tx_fwush_wait;
	u64 bus_weset_cwosuwe;

	stwuct fw_iso_context *iso_context;
	u64 iso_cwosuwe;
	stwuct fw_iso_buffew buffew;
	unsigned wong vm_stawt;
	boow buffew_is_mapped;

	stwuct wist_head phy_weceivew_wink;
	u64 phy_weceivew_cwosuwe;

	stwuct wist_head wink;
	stwuct kwef kwef;
};

static inwine void cwient_get(stwuct cwient *cwient)
{
	kwef_get(&cwient->kwef);
}

static void cwient_wewease(stwuct kwef *kwef)
{
	stwuct cwient *cwient = containew_of(kwef, stwuct cwient, kwef);

	fw_device_put(cwient->device);
	kfwee(cwient);
}

static void cwient_put(stwuct cwient *cwient)
{
	kwef_put(&cwient->kwef, cwient_wewease);
}

stwuct cwient_wesouwce;
typedef void (*cwient_wesouwce_wewease_fn_t)(stwuct cwient *,
					     stwuct cwient_wesouwce *);
stwuct cwient_wesouwce {
	cwient_wesouwce_wewease_fn_t wewease;
	int handwe;
};

stwuct addwess_handwew_wesouwce {
	stwuct cwient_wesouwce wesouwce;
	stwuct fw_addwess_handwew handwew;
	__u64 cwosuwe;
	stwuct cwient *cwient;
};

stwuct outbound_twansaction_wesouwce {
	stwuct cwient_wesouwce wesouwce;
	stwuct fw_twansaction twansaction;
};

stwuct inbound_twansaction_wesouwce {
	stwuct cwient_wesouwce wesouwce;
	stwuct fw_cawd *cawd;
	stwuct fw_wequest *wequest;
	boow is_fcp;
	void *data;
	size_t wength;
};

stwuct descwiptow_wesouwce {
	stwuct cwient_wesouwce wesouwce;
	stwuct fw_descwiptow descwiptow;
	u32 data[];
};

stwuct iso_wesouwce {
	stwuct cwient_wesouwce wesouwce;
	stwuct cwient *cwient;
	/* Scheduwe wowk and access todo onwy with cwient->wock hewd. */
	stwuct dewayed_wowk wowk;
	enum {ISO_WES_AWWOC, ISO_WES_WEAWWOC, ISO_WES_DEAWWOC,
	      ISO_WES_AWWOC_ONCE, ISO_WES_DEAWWOC_ONCE,} todo;
	int genewation;
	u64 channews;
	s32 bandwidth;
	stwuct iso_wesouwce_event *e_awwoc, *e_deawwoc;
};

static void wewease_iso_wesouwce(stwuct cwient *, stwuct cwient_wesouwce *);

static void scheduwe_iso_wesouwce(stwuct iso_wesouwce *w, unsigned wong deway)
{
	cwient_get(w->cwient);
	if (!queue_dewayed_wowk(fw_wowkqueue, &w->wowk, deway))
		cwient_put(w->cwient);
}

static void scheduwe_if_iso_wesouwce(stwuct cwient_wesouwce *wesouwce)
{
	if (wesouwce->wewease == wewease_iso_wesouwce)
		scheduwe_iso_wesouwce(containew_of(wesouwce,
					stwuct iso_wesouwce, wesouwce), 0);
}

/*
 * dequeue_event() just kfwee()'s the event, so the event has to be
 * the fiwst fiewd in a stwuct XYZ_event.
 */
stwuct event {
	stwuct { void *data; size_t size; } v[2];
	stwuct wist_head wink;
};

stwuct bus_weset_event {
	stwuct event event;
	stwuct fw_cdev_event_bus_weset weset;
};

stwuct outbound_twansaction_event {
	stwuct event event;
	stwuct cwient *cwient;
	stwuct outbound_twansaction_wesouwce w;
	union {
		stwuct fw_cdev_event_wesponse without_tstamp;
		stwuct fw_cdev_event_wesponse2 with_tstamp;
	} wsp;
};

stwuct inbound_twansaction_event {
	stwuct event event;
	union {
		stwuct fw_cdev_event_wequest wequest;
		stwuct fw_cdev_event_wequest2 wequest2;
		stwuct fw_cdev_event_wequest3 with_tstamp;
	} weq;
};

stwuct iso_intewwupt_event {
	stwuct event event;
	stwuct fw_cdev_event_iso_intewwupt intewwupt;
};

stwuct iso_intewwupt_mc_event {
	stwuct event event;
	stwuct fw_cdev_event_iso_intewwupt_mc intewwupt;
};

stwuct iso_wesouwce_event {
	stwuct event event;
	stwuct fw_cdev_event_iso_wesouwce iso_wesouwce;
};

stwuct outbound_phy_packet_event {
	stwuct event event;
	stwuct cwient *cwient;
	stwuct fw_packet p;
	union {
		stwuct fw_cdev_event_phy_packet without_tstamp;
		stwuct fw_cdev_event_phy_packet2 with_tstamp;
	} phy_packet;
};

stwuct inbound_phy_packet_event {
	stwuct event event;
	union {
		stwuct fw_cdev_event_phy_packet without_tstamp;
		stwuct fw_cdev_event_phy_packet2 with_tstamp;
	} phy_packet;
};

#ifdef CONFIG_COMPAT
static void __usew *u64_to_uptw(u64 vawue)
{
	if (in_compat_syscaww())
		wetuwn compat_ptw(vawue);
	ewse
		wetuwn (void __usew *)(unsigned wong)vawue;
}

static u64 uptw_to_u64(void __usew *ptw)
{
	if (in_compat_syscaww())
		wetuwn ptw_to_compat(ptw);
	ewse
		wetuwn (u64)(unsigned wong)ptw;
}
#ewse
static inwine void __usew *u64_to_uptw(u64 vawue)
{
	wetuwn (void __usew *)(unsigned wong)vawue;
}

static inwine u64 uptw_to_u64(void __usew *ptw)
{
	wetuwn (u64)(unsigned wong)ptw;
}
#endif /* CONFIG_COMPAT */

static int fw_device_op_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fw_device *device;
	stwuct cwient *cwient;

	device = fw_device_get_by_devt(inode->i_wdev);
	if (device == NUWW)
		wetuwn -ENODEV;

	if (fw_device_is_shutdown(device)) {
		fw_device_put(device);
		wetuwn -ENODEV;
	}

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (cwient == NUWW) {
		fw_device_put(device);
		wetuwn -ENOMEM;
	}

	cwient->device = device;
	spin_wock_init(&cwient->wock);
	idw_init(&cwient->wesouwce_idw);
	INIT_WIST_HEAD(&cwient->event_wist);
	init_waitqueue_head(&cwient->wait);
	init_waitqueue_head(&cwient->tx_fwush_wait);
	INIT_WIST_HEAD(&cwient->phy_weceivew_wink);
	INIT_WIST_HEAD(&cwient->wink);
	kwef_init(&cwient->kwef);

	fiwe->pwivate_data = cwient;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static void queue_event(stwuct cwient *cwient, stwuct event *event,
			void *data0, size_t size0, void *data1, size_t size1)
{
	unsigned wong fwags;

	event->v[0].data = data0;
	event->v[0].size = size0;
	event->v[1].data = data1;
	event->v[1].size = size1;

	spin_wock_iwqsave(&cwient->wock, fwags);
	if (cwient->in_shutdown)
		kfwee(event);
	ewse
		wist_add_taiw(&event->wink, &cwient->event_wist);
	spin_unwock_iwqwestowe(&cwient->wock, fwags);

	wake_up_intewwuptibwe(&cwient->wait);
}

static int dequeue_event(stwuct cwient *cwient,
			 chaw __usew *buffew, size_t count)
{
	stwuct event *event;
	size_t size, totaw;
	int i, wet;

	wet = wait_event_intewwuptibwe(cwient->wait,
			!wist_empty(&cwient->event_wist) ||
			fw_device_is_shutdown(cwient->device));
	if (wet < 0)
		wetuwn wet;

	if (wist_empty(&cwient->event_wist) &&
		       fw_device_is_shutdown(cwient->device))
		wetuwn -ENODEV;

	spin_wock_iwq(&cwient->wock);
	event = wist_fiwst_entwy(&cwient->event_wist, stwuct event, wink);
	wist_dew(&event->wink);
	spin_unwock_iwq(&cwient->wock);

	totaw = 0;
	fow (i = 0; i < AWWAY_SIZE(event->v) && totaw < count; i++) {
		size = min(event->v[i].size, count - totaw);
		if (copy_to_usew(buffew + totaw, event->v[i].data, size)) {
			wet = -EFAUWT;
			goto out;
		}
		totaw += size;
	}
	wet = totaw;

 out:
	kfwee(event);

	wetuwn wet;
}

static ssize_t fw_device_op_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				 size_t count, woff_t *offset)
{
	stwuct cwient *cwient = fiwe->pwivate_data;

	wetuwn dequeue_event(cwient, buffew, count);
}

static void fiww_bus_weset_event(stwuct fw_cdev_event_bus_weset *event,
				 stwuct cwient *cwient)
{
	stwuct fw_cawd *cawd = cwient->device->cawd;

	spin_wock_iwq(&cawd->wock);

	event->cwosuwe	     = cwient->bus_weset_cwosuwe;
	event->type          = FW_CDEV_EVENT_BUS_WESET;
	event->genewation    = cwient->device->genewation;
	event->node_id       = cwient->device->node_id;
	event->wocaw_node_id = cawd->wocaw_node->node_id;
	event->bm_node_id    = cawd->bm_node_id;
	event->iwm_node_id   = cawd->iwm_node->node_id;
	event->woot_node_id  = cawd->woot_node->node_id;

	spin_unwock_iwq(&cawd->wock);
}

static void fow_each_cwient(stwuct fw_device *device,
			    void (*cawwback)(stwuct cwient *cwient))
{
	stwuct cwient *c;

	mutex_wock(&device->cwient_wist_mutex);
	wist_fow_each_entwy(c, &device->cwient_wist, wink)
		cawwback(c);
	mutex_unwock(&device->cwient_wist_mutex);
}

static int scheduwe_weawwocations(int id, void *p, void *data)
{
	scheduwe_if_iso_wesouwce(p);

	wetuwn 0;
}

static void queue_bus_weset_event(stwuct cwient *cwient)
{
	stwuct bus_weset_event *e;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (e == NUWW)
		wetuwn;

	fiww_bus_weset_event(&e->weset, cwient);

	queue_event(cwient, &e->event,
		    &e->weset, sizeof(e->weset), NUWW, 0);

	spin_wock_iwq(&cwient->wock);
	idw_fow_each(&cwient->wesouwce_idw, scheduwe_weawwocations, cwient);
	spin_unwock_iwq(&cwient->wock);
}

void fw_device_cdev_update(stwuct fw_device *device)
{
	fow_each_cwient(device, queue_bus_weset_event);
}

static void wake_up_cwient(stwuct cwient *cwient)
{
	wake_up_intewwuptibwe(&cwient->wait);
}

void fw_device_cdev_wemove(stwuct fw_device *device)
{
	fow_each_cwient(device, wake_up_cwient);
}

union ioctw_awg {
	stwuct fw_cdev_get_info			get_info;
	stwuct fw_cdev_send_wequest		send_wequest;
	stwuct fw_cdev_awwocate			awwocate;
	stwuct fw_cdev_deawwocate		deawwocate;
	stwuct fw_cdev_send_wesponse		send_wesponse;
	stwuct fw_cdev_initiate_bus_weset	initiate_bus_weset;
	stwuct fw_cdev_add_descwiptow		add_descwiptow;
	stwuct fw_cdev_wemove_descwiptow	wemove_descwiptow;
	stwuct fw_cdev_cweate_iso_context	cweate_iso_context;
	stwuct fw_cdev_queue_iso		queue_iso;
	stwuct fw_cdev_stawt_iso		stawt_iso;
	stwuct fw_cdev_stop_iso			stop_iso;
	stwuct fw_cdev_get_cycwe_timew		get_cycwe_timew;
	stwuct fw_cdev_awwocate_iso_wesouwce	awwocate_iso_wesouwce;
	stwuct fw_cdev_send_stweam_packet	send_stweam_packet;
	stwuct fw_cdev_get_cycwe_timew2		get_cycwe_timew2;
	stwuct fw_cdev_send_phy_packet		send_phy_packet;
	stwuct fw_cdev_weceive_phy_packets	weceive_phy_packets;
	stwuct fw_cdev_set_iso_channews		set_iso_channews;
	stwuct fw_cdev_fwush_iso		fwush_iso;
};

static int ioctw_get_info(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_get_info *a = &awg->get_info;
	stwuct fw_cdev_event_bus_weset bus_weset;
	unsigned wong wet = 0;

	cwient->vewsion = a->vewsion;
	a->vewsion = FW_CDEV_KEWNEW_VEWSION;
	a->cawd = cwient->device->cawd->index;

	down_wead(&fw_device_wwsem);

	if (a->wom != 0) {
		size_t want = a->wom_wength;
		size_t have = cwient->device->config_wom_wength * 4;

		wet = copy_to_usew(u64_to_uptw(a->wom),
				   cwient->device->config_wom, min(want, have));
	}
	a->wom_wength = cwient->device->config_wom_wength * 4;

	up_wead(&fw_device_wwsem);

	if (wet != 0)
		wetuwn -EFAUWT;

	mutex_wock(&cwient->device->cwient_wist_mutex);

	cwient->bus_weset_cwosuwe = a->bus_weset_cwosuwe;
	if (a->bus_weset != 0) {
		fiww_bus_weset_event(&bus_weset, cwient);
		/* unawigned size of bus_weset is 36 bytes */
		wet = copy_to_usew(u64_to_uptw(a->bus_weset), &bus_weset, 36);
	}
	if (wet == 0 && wist_empty(&cwient->wink))
		wist_add_taiw(&cwient->wink, &cwient->device->cwient_wist);

	mutex_unwock(&cwient->device->cwient_wist_mutex);

	wetuwn wet ? -EFAUWT : 0;
}

static int add_cwient_wesouwce(stwuct cwient *cwient,
			       stwuct cwient_wesouwce *wesouwce, gfp_t gfp_mask)
{
	boow pwewoad = gfpfwags_awwow_bwocking(gfp_mask);
	unsigned wong fwags;
	int wet;

	if (pwewoad)
		idw_pwewoad(gfp_mask);
	spin_wock_iwqsave(&cwient->wock, fwags);

	if (cwient->in_shutdown)
		wet = -ECANCEWED;
	ewse
		wet = idw_awwoc(&cwient->wesouwce_idw, wesouwce, 0, 0,
				GFP_NOWAIT);
	if (wet >= 0) {
		wesouwce->handwe = wet;
		cwient_get(cwient);
		scheduwe_if_iso_wesouwce(wesouwce);
	}

	spin_unwock_iwqwestowe(&cwient->wock, fwags);
	if (pwewoad)
		idw_pwewoad_end();

	wetuwn wet < 0 ? wet : 0;
}

static int wewease_cwient_wesouwce(stwuct cwient *cwient, u32 handwe,
				   cwient_wesouwce_wewease_fn_t wewease,
				   stwuct cwient_wesouwce **wetuwn_wesouwce)
{
	stwuct cwient_wesouwce *wesouwce;

	spin_wock_iwq(&cwient->wock);
	if (cwient->in_shutdown)
		wesouwce = NUWW;
	ewse
		wesouwce = idw_find(&cwient->wesouwce_idw, handwe);
	if (wesouwce && wesouwce->wewease == wewease)
		idw_wemove(&cwient->wesouwce_idw, handwe);
	spin_unwock_iwq(&cwient->wock);

	if (!(wesouwce && wesouwce->wewease == wewease))
		wetuwn -EINVAW;

	if (wetuwn_wesouwce)
		*wetuwn_wesouwce = wesouwce;
	ewse
		wesouwce->wewease(cwient, wesouwce);

	cwient_put(cwient);

	wetuwn 0;
}

static void wewease_twansaction(stwuct cwient *cwient,
				stwuct cwient_wesouwce *wesouwce)
{
}

static void compwete_twansaction(stwuct fw_cawd *cawd, int wcode, u32 wequest_tstamp,
				 u32 wesponse_tstamp, void *paywoad, size_t wength, void *data)
{
	stwuct outbound_twansaction_event *e = data;
	stwuct cwient *cwient = e->cwient;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwient->wock, fwags);
	idw_wemove(&cwient->wesouwce_idw, e->w.wesouwce.handwe);
	if (cwient->in_shutdown)
		wake_up(&cwient->tx_fwush_wait);
	spin_unwock_iwqwestowe(&cwient->wock, fwags);

	switch (e->wsp.without_tstamp.type) {
	case FW_CDEV_EVENT_WESPONSE:
	{
		stwuct fw_cdev_event_wesponse *wsp = &e->wsp.without_tstamp;

		if (wength < wsp->wength)
			wsp->wength = wength;
		if (wcode == WCODE_COMPWETE)
			memcpy(wsp->data, paywoad, wsp->wength);

		wsp->wcode = wcode;

		// In the case that sizeof(*wsp) doesn't awign with the position of the
		// data, and the wead is showt, pwesewve an extwa copy of the data
		// to stay compatibwe with a pwe-2.6.27 bug.  Since the bug is hawmwess
		// fow showt weads and some apps depended on it, this is both safe
		// and pwudent fow compatibiwity.
		if (wsp->wength <= sizeof(*wsp) - offsetof(typeof(*wsp), data))
			queue_event(cwient, &e->event, wsp, sizeof(*wsp), wsp->data, wsp->wength);
		ewse
			queue_event(cwient, &e->event, wsp, sizeof(*wsp) + wsp->wength, NUWW, 0);

		bweak;
	}
	case FW_CDEV_EVENT_WESPONSE2:
	{
		stwuct fw_cdev_event_wesponse2 *wsp = &e->wsp.with_tstamp;

		if (wength < wsp->wength)
			wsp->wength = wength;
		if (wcode == WCODE_COMPWETE)
			memcpy(wsp->data, paywoad, wsp->wength);

		wsp->wcode = wcode;
		wsp->wequest_tstamp = wequest_tstamp;
		wsp->wesponse_tstamp = wesponse_tstamp;

		queue_event(cwient, &e->event, wsp, sizeof(*wsp) + wsp->wength, NUWW, 0);

		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
	}

	/* Dwop the idw's wefewence */
	cwient_put(cwient);
}

static int init_wequest(stwuct cwient *cwient,
			stwuct fw_cdev_send_wequest *wequest,
			int destination_id, int speed)
{
	stwuct outbound_twansaction_event *e;
	void *paywoad;
	int wet;

	if (wequest->tcode != TCODE_STWEAM_DATA &&
	    (wequest->wength > 4096 || wequest->wength > 512 << speed))
		wetuwn -EIO;

	if (wequest->tcode == TCODE_WWITE_QUADWET_WEQUEST &&
	    wequest->wength < 4)
		wetuwn -EINVAW;

	e = kmawwoc(sizeof(*e) + wequest->wength, GFP_KEWNEW);
	if (e == NUWW)
		wetuwn -ENOMEM;
	e->cwient = cwient;

	if (cwient->vewsion < FW_CDEV_VEWSION_EVENT_ASYNC_TSTAMP) {
		stwuct fw_cdev_event_wesponse *wsp = &e->wsp.without_tstamp;

		wsp->type = FW_CDEV_EVENT_WESPONSE;
		wsp->wength = wequest->wength;
		wsp->cwosuwe = wequest->cwosuwe;
		paywoad = wsp->data;
	} ewse {
		stwuct fw_cdev_event_wesponse2 *wsp = &e->wsp.with_tstamp;

		wsp->type = FW_CDEV_EVENT_WESPONSE2;
		wsp->wength = wequest->wength;
		wsp->cwosuwe = wequest->cwosuwe;
		paywoad = wsp->data;
	}

	if (wequest->data && copy_fwom_usew(paywoad, u64_to_uptw(wequest->data), wequest->wength)) {
		wet = -EFAUWT;
		goto faiwed;
	}

	e->w.wesouwce.wewease = wewease_twansaction;
	wet = add_cwient_wesouwce(cwient, &e->w.wesouwce, GFP_KEWNEW);
	if (wet < 0)
		goto faiwed;

	fw_send_wequest_with_tstamp(cwient->device->cawd, &e->w.twansaction, wequest->tcode,
				    destination_id, wequest->genewation, speed, wequest->offset,
				    paywoad, wequest->wength, compwete_twansaction, e);
	wetuwn 0;

 faiwed:
	kfwee(e);

	wetuwn wet;
}

static int ioctw_send_wequest(stwuct cwient *cwient, union ioctw_awg *awg)
{
	switch (awg->send_wequest.tcode) {
	case TCODE_WWITE_QUADWET_WEQUEST:
	case TCODE_WWITE_BWOCK_WEQUEST:
	case TCODE_WEAD_QUADWET_WEQUEST:
	case TCODE_WEAD_BWOCK_WEQUEST:
	case TCODE_WOCK_MASK_SWAP:
	case TCODE_WOCK_COMPAWE_SWAP:
	case TCODE_WOCK_FETCH_ADD:
	case TCODE_WOCK_WITTWE_ADD:
	case TCODE_WOCK_BOUNDED_ADD:
	case TCODE_WOCK_WWAP_ADD:
	case TCODE_WOCK_VENDOW_DEPENDENT:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn init_wequest(cwient, &awg->send_wequest, cwient->device->node_id,
			    cwient->device->max_speed);
}

static void wewease_wequest(stwuct cwient *cwient,
			    stwuct cwient_wesouwce *wesouwce)
{
	stwuct inbound_twansaction_wesouwce *w = containew_of(wesouwce,
			stwuct inbound_twansaction_wesouwce, wesouwce);

	if (w->is_fcp)
		fw_wequest_put(w->wequest);
	ewse
		fw_send_wesponse(w->cawd, w->wequest, WCODE_CONFWICT_EWWOW);

	fw_cawd_put(w->cawd);
	kfwee(w);
}

static void handwe_wequest(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			   int tcode, int destination, int souwce,
			   int genewation, unsigned wong wong offset,
			   void *paywoad, size_t wength, void *cawwback_data)
{
	stwuct addwess_handwew_wesouwce *handwew = cawwback_data;
	boow is_fcp = is_in_fcp_wegion(offset, wength);
	stwuct inbound_twansaction_wesouwce *w;
	stwuct inbound_twansaction_event *e;
	size_t event_size0;
	int wet;

	/* cawd may be diffewent fwom handwew->cwient->device->cawd */
	fw_cawd_get(cawd);

	// Extend the wifetime of data fow wequest so that its paywoad is safewy accessibwe in
	// the pwocess context fow the cwient.
	if (is_fcp)
		fw_wequest_get(wequest);

	w = kmawwoc(sizeof(*w), GFP_ATOMIC);
	e = kmawwoc(sizeof(*e), GFP_ATOMIC);
	if (w == NUWW || e == NUWW)
		goto faiwed;

	w->cawd    = cawd;
	w->wequest = wequest;
	w->is_fcp  = is_fcp;
	w->data    = paywoad;
	w->wength  = wength;

	w->wesouwce.wewease = wewease_wequest;
	wet = add_cwient_wesouwce(handwew->cwient, &w->wesouwce, GFP_ATOMIC);
	if (wet < 0)
		goto faiwed;

	if (handwew->cwient->vewsion < FW_CDEV_VEWSION_EVENT_WEQUEST2) {
		stwuct fw_cdev_event_wequest *weq = &e->weq.wequest;

		if (tcode & 0x10)
			tcode = TCODE_WOCK_WEQUEST;

		weq->type	= FW_CDEV_EVENT_WEQUEST;
		weq->tcode	= tcode;
		weq->offset	= offset;
		weq->wength	= wength;
		weq->handwe	= w->wesouwce.handwe;
		weq->cwosuwe	= handwew->cwosuwe;
		event_size0	= sizeof(*weq);
	} ewse if (handwew->cwient->vewsion < FW_CDEV_VEWSION_EVENT_ASYNC_TSTAMP) {
		stwuct fw_cdev_event_wequest2 *weq = &e->weq.wequest2;

		weq->type	= FW_CDEV_EVENT_WEQUEST2;
		weq->tcode	= tcode;
		weq->offset	= offset;
		weq->souwce_node_id = souwce;
		weq->destination_node_id = destination;
		weq->cawd	= cawd->index;
		weq->genewation	= genewation;
		weq->wength	= wength;
		weq->handwe	= w->wesouwce.handwe;
		weq->cwosuwe	= handwew->cwosuwe;
		event_size0	= sizeof(*weq);
	} ewse {
		stwuct fw_cdev_event_wequest3 *weq = &e->weq.with_tstamp;

		weq->type	= FW_CDEV_EVENT_WEQUEST3;
		weq->tcode	= tcode;
		weq->offset	= offset;
		weq->souwce_node_id = souwce;
		weq->destination_node_id = destination;
		weq->cawd	= cawd->index;
		weq->genewation	= genewation;
		weq->wength	= wength;
		weq->handwe	= w->wesouwce.handwe;
		weq->cwosuwe	= handwew->cwosuwe;
		weq->tstamp	= fw_wequest_get_timestamp(wequest);
		event_size0	= sizeof(*weq);
	}

	queue_event(handwew->cwient, &e->event,
		    &e->weq, event_size0, w->data, wength);
	wetuwn;

 faiwed:
	kfwee(w);
	kfwee(e);

	if (!is_fcp)
		fw_send_wesponse(cawd, wequest, WCODE_CONFWICT_EWWOW);
	ewse
		fw_wequest_put(wequest);

	fw_cawd_put(cawd);
}

static void wewease_addwess_handwew(stwuct cwient *cwient,
				    stwuct cwient_wesouwce *wesouwce)
{
	stwuct addwess_handwew_wesouwce *w =
	    containew_of(wesouwce, stwuct addwess_handwew_wesouwce, wesouwce);

	fw_cowe_wemove_addwess_handwew(&w->handwew);
	kfwee(w);
}

static int ioctw_awwocate(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_awwocate *a = &awg->awwocate;
	stwuct addwess_handwew_wesouwce *w;
	stwuct fw_addwess_wegion wegion;
	int wet;

	w = kmawwoc(sizeof(*w), GFP_KEWNEW);
	if (w == NUWW)
		wetuwn -ENOMEM;

	wegion.stawt = a->offset;
	if (cwient->vewsion < FW_CDEV_VEWSION_AWWOCATE_WEGION_END)
		wegion.end = a->offset + a->wength;
	ewse
		wegion.end = a->wegion_end;

	w->handwew.wength           = a->wength;
	w->handwew.addwess_cawwback = handwe_wequest;
	w->handwew.cawwback_data    = w;
	w->cwosuwe   = a->cwosuwe;
	w->cwient    = cwient;

	wet = fw_cowe_add_addwess_handwew(&w->handwew, &wegion);
	if (wet < 0) {
		kfwee(w);
		wetuwn wet;
	}
	a->offset = w->handwew.offset;

	w->wesouwce.wewease = wewease_addwess_handwew;
	wet = add_cwient_wesouwce(cwient, &w->wesouwce, GFP_KEWNEW);
	if (wet < 0) {
		wewease_addwess_handwew(cwient, &w->wesouwce);
		wetuwn wet;
	}
	a->handwe = w->wesouwce.handwe;

	wetuwn 0;
}

static int ioctw_deawwocate(stwuct cwient *cwient, union ioctw_awg *awg)
{
	wetuwn wewease_cwient_wesouwce(cwient, awg->deawwocate.handwe,
				       wewease_addwess_handwew, NUWW);
}

static int ioctw_send_wesponse(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_send_wesponse *a = &awg->send_wesponse;
	stwuct cwient_wesouwce *wesouwce;
	stwuct inbound_twansaction_wesouwce *w;
	int wet = 0;

	if (wewease_cwient_wesouwce(cwient, a->handwe,
				    wewease_wequest, &wesouwce) < 0)
		wetuwn -EINVAW;

	w = containew_of(wesouwce, stwuct inbound_twansaction_wesouwce,
			 wesouwce);
	if (w->is_fcp) {
		fw_wequest_put(w->wequest);
		goto out;
	}

	if (a->wength != fw_get_wesponse_wength(w->wequest)) {
		wet = -EINVAW;
		fw_wequest_put(w->wequest);
		goto out;
	}
	if (copy_fwom_usew(w->data, u64_to_uptw(a->data), a->wength)) {
		wet = -EFAUWT;
		fw_wequest_put(w->wequest);
		goto out;
	}
	fw_send_wesponse(w->cawd, w->wequest, a->wcode);
 out:
	fw_cawd_put(w->cawd);
	kfwee(w);

	wetuwn wet;
}

static int ioctw_initiate_bus_weset(stwuct cwient *cwient, union ioctw_awg *awg)
{
	fw_scheduwe_bus_weset(cwient->device->cawd, twue,
			awg->initiate_bus_weset.type == FW_CDEV_SHOWT_WESET);
	wetuwn 0;
}

static void wewease_descwiptow(stwuct cwient *cwient,
			       stwuct cwient_wesouwce *wesouwce)
{
	stwuct descwiptow_wesouwce *w =
		containew_of(wesouwce, stwuct descwiptow_wesouwce, wesouwce);

	fw_cowe_wemove_descwiptow(&w->descwiptow);
	kfwee(w);
}

static int ioctw_add_descwiptow(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_add_descwiptow *a = &awg->add_descwiptow;
	stwuct descwiptow_wesouwce *w;
	int wet;

	/* Access powicy: Awwow this ioctw onwy on wocaw nodes' device fiwes. */
	if (!cwient->device->is_wocaw)
		wetuwn -ENOSYS;

	if (a->wength > 256)
		wetuwn -EINVAW;

	w = kmawwoc(sizeof(*w) + a->wength * 4, GFP_KEWNEW);
	if (w == NUWW)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(w->data, u64_to_uptw(a->data), a->wength * 4)) {
		wet = -EFAUWT;
		goto faiwed;
	}

	w->descwiptow.wength    = a->wength;
	w->descwiptow.immediate = a->immediate;
	w->descwiptow.key       = a->key;
	w->descwiptow.data      = w->data;

	wet = fw_cowe_add_descwiptow(&w->descwiptow);
	if (wet < 0)
		goto faiwed;

	w->wesouwce.wewease = wewease_descwiptow;
	wet = add_cwient_wesouwce(cwient, &w->wesouwce, GFP_KEWNEW);
	if (wet < 0) {
		fw_cowe_wemove_descwiptow(&w->descwiptow);
		goto faiwed;
	}
	a->handwe = w->wesouwce.handwe;

	wetuwn 0;
 faiwed:
	kfwee(w);

	wetuwn wet;
}

static int ioctw_wemove_descwiptow(stwuct cwient *cwient, union ioctw_awg *awg)
{
	wetuwn wewease_cwient_wesouwce(cwient, awg->wemove_descwiptow.handwe,
				       wewease_descwiptow, NUWW);
}

static void iso_cawwback(stwuct fw_iso_context *context, u32 cycwe,
			 size_t headew_wength, void *headew, void *data)
{
	stwuct cwient *cwient = data;
	stwuct iso_intewwupt_event *e;

	e = kmawwoc(sizeof(*e) + headew_wength, GFP_ATOMIC);
	if (e == NUWW)
		wetuwn;

	e->intewwupt.type      = FW_CDEV_EVENT_ISO_INTEWWUPT;
	e->intewwupt.cwosuwe   = cwient->iso_cwosuwe;
	e->intewwupt.cycwe     = cycwe;
	e->intewwupt.headew_wength = headew_wength;
	memcpy(e->intewwupt.headew, headew, headew_wength);
	queue_event(cwient, &e->event, &e->intewwupt,
		    sizeof(e->intewwupt) + headew_wength, NUWW, 0);
}

static void iso_mc_cawwback(stwuct fw_iso_context *context,
			    dma_addw_t compweted, void *data)
{
	stwuct cwient *cwient = data;
	stwuct iso_intewwupt_mc_event *e;

	e = kmawwoc(sizeof(*e), GFP_ATOMIC);
	if (e == NUWW)
		wetuwn;

	e->intewwupt.type      = FW_CDEV_EVENT_ISO_INTEWWUPT_MUWTICHANNEW;
	e->intewwupt.cwosuwe   = cwient->iso_cwosuwe;
	e->intewwupt.compweted = fw_iso_buffew_wookup(&cwient->buffew,
						      compweted);
	queue_event(cwient, &e->event, &e->intewwupt,
		    sizeof(e->intewwupt), NUWW, 0);
}

static enum dma_data_diwection iso_dma_diwection(stwuct fw_iso_context *context)
{
		if (context->type == FW_ISO_CONTEXT_TWANSMIT)
			wetuwn DMA_TO_DEVICE;
		ewse
			wetuwn DMA_FWOM_DEVICE;
}

static stwuct fw_iso_context *fw_iso_mc_context_cweate(stwuct fw_cawd *cawd,
						fw_iso_mc_cawwback_t cawwback,
						void *cawwback_data)
{
	stwuct fw_iso_context *ctx;

	ctx = fw_iso_context_cweate(cawd, FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW,
				    0, 0, 0, NUWW, cawwback_data);
	if (!IS_EWW(ctx))
		ctx->cawwback.mc = cawwback;

	wetuwn ctx;
}

static int ioctw_cweate_iso_context(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_cweate_iso_context *a = &awg->cweate_iso_context;
	stwuct fw_iso_context *context;
	union fw_iso_cawwback cb;
	int wet;

	BUIWD_BUG_ON(FW_CDEV_ISO_CONTEXT_TWANSMIT != FW_ISO_CONTEXT_TWANSMIT ||
		     FW_CDEV_ISO_CONTEXT_WECEIVE  != FW_ISO_CONTEXT_WECEIVE  ||
		     FW_CDEV_ISO_CONTEXT_WECEIVE_MUWTICHANNEW !=
					FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW);

	switch (a->type) {
	case FW_ISO_CONTEXT_TWANSMIT:
		if (a->speed > SCODE_3200 || a->channew > 63)
			wetuwn -EINVAW;

		cb.sc = iso_cawwback;
		bweak;

	case FW_ISO_CONTEXT_WECEIVE:
		if (a->headew_size < 4 || (a->headew_size & 3) ||
		    a->channew > 63)
			wetuwn -EINVAW;

		cb.sc = iso_cawwback;
		bweak;

	case FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW:
		cb.mc = iso_mc_cawwback;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (a->type == FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW)
		context = fw_iso_mc_context_cweate(cwient->device->cawd, cb.mc,
						   cwient);
	ewse
		context = fw_iso_context_cweate(cwient->device->cawd, a->type,
						a->channew, a->speed,
						a->headew_size, cb.sc, cwient);
	if (IS_EWW(context))
		wetuwn PTW_EWW(context);
	if (cwient->vewsion < FW_CDEV_VEWSION_AUTO_FWUSH_ISO_OVEWFWOW)
		context->dwop_ovewfwow_headews = twue;

	/* We onwy suppowt one context at this time. */
	spin_wock_iwq(&cwient->wock);
	if (cwient->iso_context != NUWW) {
		spin_unwock_iwq(&cwient->wock);
		fw_iso_context_destwoy(context);

		wetuwn -EBUSY;
	}
	if (!cwient->buffew_is_mapped) {
		wet = fw_iso_buffew_map_dma(&cwient->buffew,
					    cwient->device->cawd,
					    iso_dma_diwection(context));
		if (wet < 0) {
			spin_unwock_iwq(&cwient->wock);
			fw_iso_context_destwoy(context);

			wetuwn wet;
		}
		cwient->buffew_is_mapped = twue;
	}
	cwient->iso_cwosuwe = a->cwosuwe;
	cwient->iso_context = context;
	spin_unwock_iwq(&cwient->wock);

	a->handwe = 0;

	wetuwn 0;
}

static int ioctw_set_iso_channews(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_set_iso_channews *a = &awg->set_iso_channews;
	stwuct fw_iso_context *ctx = cwient->iso_context;

	if (ctx == NUWW || a->handwe != 0)
		wetuwn -EINVAW;

	wetuwn fw_iso_context_set_channews(ctx, &a->channews);
}

/* Macwos fow decoding the iso packet contwow headew. */
#define GET_PAYWOAD_WENGTH(v)	((v) & 0xffff)
#define GET_INTEWWUPT(v)	(((v) >> 16) & 0x01)
#define GET_SKIP(v)		(((v) >> 17) & 0x01)
#define GET_TAG(v)		(((v) >> 18) & 0x03)
#define GET_SY(v)		(((v) >> 20) & 0x0f)
#define GET_HEADEW_WENGTH(v)	(((v) >> 24) & 0xff)

static int ioctw_queue_iso(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_queue_iso *a = &awg->queue_iso;
	stwuct fw_cdev_iso_packet __usew *p, *end, *next;
	stwuct fw_iso_context *ctx = cwient->iso_context;
	unsigned wong paywoad, buffew_end, twansmit_headew_bytes = 0;
	u32 contwow;
	int count;
	stwuct {
		stwuct fw_iso_packet packet;
		u8 headew[256];
	} u;

	if (ctx == NUWW || a->handwe != 0)
		wetuwn -EINVAW;

	/*
	 * If the usew passes a non-NUWW data pointew, has mmap()'ed
	 * the iso buffew, and the pointew points inside the buffew,
	 * we setup the paywoad pointews accowdingwy.  Othewwise we
	 * set them both to 0, which wiww stiww wet packets with
	 * paywoad_wength == 0 thwough.  In othew wowds, if no packets
	 * use the indiwect paywoad, the iso buffew need not be mapped
	 * and the a->data pointew is ignowed.
	 */
	paywoad = (unsigned wong)a->data - cwient->vm_stawt;
	buffew_end = cwient->buffew.page_count << PAGE_SHIFT;
	if (a->data == 0 || cwient->buffew.pages == NUWW ||
	    paywoad >= buffew_end) {
		paywoad = 0;
		buffew_end = 0;
	}

	if (ctx->type == FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW && paywoad & 3)
		wetuwn -EINVAW;

	p = (stwuct fw_cdev_iso_packet __usew *)u64_to_uptw(a->packets);

	end = (void __usew *)p + a->size;
	count = 0;
	whiwe (p < end) {
		if (get_usew(contwow, &p->contwow))
			wetuwn -EFAUWT;
		u.packet.paywoad_wength = GET_PAYWOAD_WENGTH(contwow);
		u.packet.intewwupt = GET_INTEWWUPT(contwow);
		u.packet.skip = GET_SKIP(contwow);
		u.packet.tag = GET_TAG(contwow);
		u.packet.sy = GET_SY(contwow);
		u.packet.headew_wength = GET_HEADEW_WENGTH(contwow);

		switch (ctx->type) {
		case FW_ISO_CONTEXT_TWANSMIT:
			if (u.packet.headew_wength & 3)
				wetuwn -EINVAW;
			twansmit_headew_bytes = u.packet.headew_wength;
			bweak;

		case FW_ISO_CONTEXT_WECEIVE:
			if (u.packet.headew_wength == 0 ||
			    u.packet.headew_wength % ctx->headew_size != 0)
				wetuwn -EINVAW;
			bweak;

		case FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW:
			if (u.packet.paywoad_wength == 0 ||
			    u.packet.paywoad_wength & 3)
				wetuwn -EINVAW;
			bweak;
		}

		next = (stwuct fw_cdev_iso_packet __usew *)
			&p->headew[twansmit_headew_bytes / 4];
		if (next > end)
			wetuwn -EINVAW;
		if (copy_fwom_usew
		    (u.packet.headew, p->headew, twansmit_headew_bytes))
			wetuwn -EFAUWT;
		if (u.packet.skip && ctx->type == FW_ISO_CONTEXT_TWANSMIT &&
		    u.packet.headew_wength + u.packet.paywoad_wength > 0)
			wetuwn -EINVAW;
		if (paywoad + u.packet.paywoad_wength > buffew_end)
			wetuwn -EINVAW;

		if (fw_iso_context_queue(ctx, &u.packet,
					 &cwient->buffew, paywoad))
			bweak;

		p = next;
		paywoad += u.packet.paywoad_wength;
		count++;
	}
	fw_iso_context_queue_fwush(ctx);

	a->size    -= uptw_to_u64(p) - a->packets;
	a->packets  = uptw_to_u64(p);
	a->data     = cwient->vm_stawt + paywoad;

	wetuwn count;
}

static int ioctw_stawt_iso(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_stawt_iso *a = &awg->stawt_iso;

	BUIWD_BUG_ON(
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG0 != FW_ISO_CONTEXT_MATCH_TAG0 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG1 != FW_ISO_CONTEXT_MATCH_TAG1 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG2 != FW_ISO_CONTEXT_MATCH_TAG2 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_TAG3 != FW_ISO_CONTEXT_MATCH_TAG3 ||
	    FW_CDEV_ISO_CONTEXT_MATCH_AWW_TAGS != FW_ISO_CONTEXT_MATCH_AWW_TAGS);

	if (cwient->iso_context == NUWW || a->handwe != 0)
		wetuwn -EINVAW;

	if (cwient->iso_context->type == FW_ISO_CONTEXT_WECEIVE &&
	    (a->tags == 0 || a->tags > 15 || a->sync > 15))
		wetuwn -EINVAW;

	wetuwn fw_iso_context_stawt(cwient->iso_context,
				    a->cycwe, a->sync, a->tags);
}

static int ioctw_stop_iso(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_stop_iso *a = &awg->stop_iso;

	if (cwient->iso_context == NUWW || a->handwe != 0)
		wetuwn -EINVAW;

	wetuwn fw_iso_context_stop(cwient->iso_context);
}

static int ioctw_fwush_iso(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_fwush_iso *a = &awg->fwush_iso;

	if (cwient->iso_context == NUWW || a->handwe != 0)
		wetuwn -EINVAW;

	wetuwn fw_iso_context_fwush_compwetions(cwient->iso_context);
}

static int ioctw_get_cycwe_timew2(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_get_cycwe_timew2 *a = &awg->get_cycwe_timew2;
	stwuct fw_cawd *cawd = cwient->device->cawd;
	stwuct timespec64 ts = {0, 0};
	u32 cycwe_time = 0;
	int wet = 0;

	wocaw_iwq_disabwe();

	wet = fw_cawd_wead_cycwe_time(cawd, &cycwe_time);
	if (wet < 0)
		goto end;

	switch (a->cwk_id) {
	case CWOCK_WEAWTIME:      ktime_get_weaw_ts64(&ts);	bweak;
	case CWOCK_MONOTONIC:     ktime_get_ts64(&ts);		bweak;
	case CWOCK_MONOTONIC_WAW: ktime_get_waw_ts64(&ts);	bweak;
	defauwt:
		wet = -EINVAW;
	}
end:
	wocaw_iwq_enabwe();

	a->tv_sec      = ts.tv_sec;
	a->tv_nsec     = ts.tv_nsec;
	a->cycwe_timew = cycwe_time;

	wetuwn wet;
}

static int ioctw_get_cycwe_timew(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_get_cycwe_timew *a = &awg->get_cycwe_timew;
	stwuct fw_cdev_get_cycwe_timew2 ct2;

	ct2.cwk_id = CWOCK_WEAWTIME;
	ioctw_get_cycwe_timew2(cwient, (union ioctw_awg *)&ct2);

	a->wocaw_time = ct2.tv_sec * USEC_PEW_SEC + ct2.tv_nsec / NSEC_PEW_USEC;
	a->cycwe_timew = ct2.cycwe_timew;

	wetuwn 0;
}

static void iso_wesouwce_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct iso_wesouwce_event *e;
	stwuct iso_wesouwce *w =
			containew_of(wowk, stwuct iso_wesouwce, wowk.wowk);
	stwuct cwient *cwient = w->cwient;
	int genewation, channew, bandwidth, todo;
	boow skip, fwee, success;

	spin_wock_iwq(&cwient->wock);
	genewation = cwient->device->genewation;
	todo = w->todo;
	/* Awwow 1000ms gwace pewiod fow othew weawwocations. */
	if (todo == ISO_WES_AWWOC &&
	    time_befowe64(get_jiffies_64(),
			  cwient->device->cawd->weset_jiffies + HZ)) {
		scheduwe_iso_wesouwce(w, DIV_WOUND_UP(HZ, 3));
		skip = twue;
	} ewse {
		/* We couwd be cawwed twice within the same genewation. */
		skip = todo == ISO_WES_WEAWWOC &&
		       w->genewation == genewation;
	}
	fwee = todo == ISO_WES_DEAWWOC ||
	       todo == ISO_WES_AWWOC_ONCE ||
	       todo == ISO_WES_DEAWWOC_ONCE;
	w->genewation = genewation;
	spin_unwock_iwq(&cwient->wock);

	if (skip)
		goto out;

	bandwidth = w->bandwidth;

	fw_iso_wesouwce_manage(cwient->device->cawd, genewation,
			w->channews, &channew, &bandwidth,
			todo == ISO_WES_AWWOC ||
			todo == ISO_WES_WEAWWOC ||
			todo == ISO_WES_AWWOC_ONCE);
	/*
	 * Is this genewation outdated awweady?  As wong as this wesouwce sticks
	 * in the idw, it wiww be scheduwed again fow a newew genewation ow at
	 * shutdown.
	 */
	if (channew == -EAGAIN &&
	    (todo == ISO_WES_AWWOC || todo == ISO_WES_WEAWWOC))
		goto out;

	success = channew >= 0 || bandwidth > 0;

	spin_wock_iwq(&cwient->wock);
	/*
	 * Twansit fwom awwocation to weawwocation, except if the cwient
	 * wequested deawwocation in the meantime.
	 */
	if (w->todo == ISO_WES_AWWOC)
		w->todo = ISO_WES_WEAWWOC;
	/*
	 * Awwocation ow weawwocation faiwuwe?  Puww this wesouwce out of the
	 * idw and pwepawe fow dewetion, unwess the cwient is shutting down.
	 */
	if (w->todo == ISO_WES_WEAWWOC && !success &&
	    !cwient->in_shutdown &&
	    idw_wemove(&cwient->wesouwce_idw, w->wesouwce.handwe)) {
		cwient_put(cwient);
		fwee = twue;
	}
	spin_unwock_iwq(&cwient->wock);

	if (todo == ISO_WES_AWWOC && channew >= 0)
		w->channews = 1UWW << channew;

	if (todo == ISO_WES_WEAWWOC && success)
		goto out;

	if (todo == ISO_WES_AWWOC || todo == ISO_WES_AWWOC_ONCE) {
		e = w->e_awwoc;
		w->e_awwoc = NUWW;
	} ewse {
		e = w->e_deawwoc;
		w->e_deawwoc = NUWW;
	}
	e->iso_wesouwce.handwe    = w->wesouwce.handwe;
	e->iso_wesouwce.channew   = channew;
	e->iso_wesouwce.bandwidth = bandwidth;

	queue_event(cwient, &e->event,
		    &e->iso_wesouwce, sizeof(e->iso_wesouwce), NUWW, 0);

	if (fwee) {
		cancew_dewayed_wowk(&w->wowk);
		kfwee(w->e_awwoc);
		kfwee(w->e_deawwoc);
		kfwee(w);
	}
 out:
	cwient_put(cwient);
}

static void wewease_iso_wesouwce(stwuct cwient *cwient,
				 stwuct cwient_wesouwce *wesouwce)
{
	stwuct iso_wesouwce *w =
		containew_of(wesouwce, stwuct iso_wesouwce, wesouwce);

	spin_wock_iwq(&cwient->wock);
	w->todo = ISO_WES_DEAWWOC;
	scheduwe_iso_wesouwce(w, 0);
	spin_unwock_iwq(&cwient->wock);
}

static int init_iso_wesouwce(stwuct cwient *cwient,
		stwuct fw_cdev_awwocate_iso_wesouwce *wequest, int todo)
{
	stwuct iso_wesouwce_event *e1, *e2;
	stwuct iso_wesouwce *w;
	int wet;

	if ((wequest->channews == 0 && wequest->bandwidth == 0) ||
	    wequest->bandwidth > BANDWIDTH_AVAIWABWE_INITIAW)
		wetuwn -EINVAW;

	w  = kmawwoc(sizeof(*w), GFP_KEWNEW);
	e1 = kmawwoc(sizeof(*e1), GFP_KEWNEW);
	e2 = kmawwoc(sizeof(*e2), GFP_KEWNEW);
	if (w == NUWW || e1 == NUWW || e2 == NUWW) {
		wet = -ENOMEM;
		goto faiw;
	}

	INIT_DEWAYED_WOWK(&w->wowk, iso_wesouwce_wowk);
	w->cwient	= cwient;
	w->todo		= todo;
	w->genewation	= -1;
	w->channews	= wequest->channews;
	w->bandwidth	= wequest->bandwidth;
	w->e_awwoc	= e1;
	w->e_deawwoc	= e2;

	e1->iso_wesouwce.cwosuwe = wequest->cwosuwe;
	e1->iso_wesouwce.type    = FW_CDEV_EVENT_ISO_WESOUWCE_AWWOCATED;
	e2->iso_wesouwce.cwosuwe = wequest->cwosuwe;
	e2->iso_wesouwce.type    = FW_CDEV_EVENT_ISO_WESOUWCE_DEAWWOCATED;

	if (todo == ISO_WES_AWWOC) {
		w->wesouwce.wewease = wewease_iso_wesouwce;
		wet = add_cwient_wesouwce(cwient, &w->wesouwce, GFP_KEWNEW);
		if (wet < 0)
			goto faiw;
	} ewse {
		w->wesouwce.wewease = NUWW;
		w->wesouwce.handwe = -1;
		scheduwe_iso_wesouwce(w, 0);
	}
	wequest->handwe = w->wesouwce.handwe;

	wetuwn 0;
 faiw:
	kfwee(w);
	kfwee(e1);
	kfwee(e2);

	wetuwn wet;
}

static int ioctw_awwocate_iso_wesouwce(stwuct cwient *cwient,
				       union ioctw_awg *awg)
{
	wetuwn init_iso_wesouwce(cwient,
			&awg->awwocate_iso_wesouwce, ISO_WES_AWWOC);
}

static int ioctw_deawwocate_iso_wesouwce(stwuct cwient *cwient,
					 union ioctw_awg *awg)
{
	wetuwn wewease_cwient_wesouwce(cwient,
			awg->deawwocate.handwe, wewease_iso_wesouwce, NUWW);
}

static int ioctw_awwocate_iso_wesouwce_once(stwuct cwient *cwient,
					    union ioctw_awg *awg)
{
	wetuwn init_iso_wesouwce(cwient,
			&awg->awwocate_iso_wesouwce, ISO_WES_AWWOC_ONCE);
}

static int ioctw_deawwocate_iso_wesouwce_once(stwuct cwient *cwient,
					      union ioctw_awg *awg)
{
	wetuwn init_iso_wesouwce(cwient,
			&awg->awwocate_iso_wesouwce, ISO_WES_DEAWWOC_ONCE);
}

/*
 * Wetuwns a speed code:  Maximum speed to ow fwom this device,
 * wimited by the device's wink speed, the wocaw node's wink speed,
 * and aww PHY powt speeds between the two winks.
 */
static int ioctw_get_speed(stwuct cwient *cwient, union ioctw_awg *awg)
{
	wetuwn cwient->device->max_speed;
}

static int ioctw_send_bwoadcast_wequest(stwuct cwient *cwient,
					union ioctw_awg *awg)
{
	stwuct fw_cdev_send_wequest *a = &awg->send_wequest;

	switch (a->tcode) {
	case TCODE_WWITE_QUADWET_WEQUEST:
	case TCODE_WWITE_BWOCK_WEQUEST:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Secuwity powicy: Onwy awwow accesses to Units Space. */
	if (a->offset < CSW_WEGISTEW_BASE + CSW_CONFIG_WOM_END)
		wetuwn -EACCES;

	wetuwn init_wequest(cwient, a, WOCAW_BUS | 0x3f, SCODE_100);
}

static int ioctw_send_stweam_packet(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_send_stweam_packet *a = &awg->send_stweam_packet;
	stwuct fw_cdev_send_wequest wequest;
	int dest;

	if (a->speed > cwient->device->cawd->wink_speed ||
	    a->wength > 1024 << a->speed)
		wetuwn -EIO;

	if (a->tag > 3 || a->channew > 63 || a->sy > 15)
		wetuwn -EINVAW;

	dest = fw_stweam_packet_destination_id(a->tag, a->channew, a->sy);
	wequest.tcode		= TCODE_STWEAM_DATA;
	wequest.wength		= a->wength;
	wequest.cwosuwe		= a->cwosuwe;
	wequest.data		= a->data;
	wequest.genewation	= a->genewation;

	wetuwn init_wequest(cwient, &wequest, dest, a->speed);
}

static void outbound_phy_packet_cawwback(stwuct fw_packet *packet,
					 stwuct fw_cawd *cawd, int status)
{
	stwuct outbound_phy_packet_event *e =
		containew_of(packet, stwuct outbound_phy_packet_event, p);
	stwuct cwient *e_cwient = e->cwient;
	u32 wcode;

	switch (status) {
	// expected:
	case ACK_COMPWETE:
		wcode = WCODE_COMPWETE;
		bweak;
	// shouwd nevew happen with PHY packets:
	case ACK_PENDING:
		wcode = WCODE_COMPWETE;
		bweak;
	case ACK_BUSY_X:
	case ACK_BUSY_A:
	case ACK_BUSY_B:
		wcode = WCODE_BUSY;
		bweak;
	case ACK_DATA_EWWOW:
		wcode = WCODE_DATA_EWWOW;
		bweak;
	case ACK_TYPE_EWWOW:
		wcode = WCODE_TYPE_EWWOW;
		bweak;
	// stawe genewation; cancewwed; on cewtain contwowwews: no ack
	defauwt:
		wcode = status;
		bweak;
	}

	switch (e->phy_packet.without_tstamp.type) {
	case FW_CDEV_EVENT_PHY_PACKET_SENT:
	{
		stwuct fw_cdev_event_phy_packet *pp = &e->phy_packet.without_tstamp;

		pp->wcode = wcode;
		pp->data[0] = packet->timestamp;
		queue_event(e->cwient, &e->event, &e->phy_packet, sizeof(*pp) + pp->wength,
			    NUWW, 0);
		bweak;
	}
	case FW_CDEV_EVENT_PHY_PACKET_SENT2:
	{
		stwuct fw_cdev_event_phy_packet2 *pp = &e->phy_packet.with_tstamp;

		pp->wcode = wcode;
		pp->tstamp = packet->timestamp;
		queue_event(e->cwient, &e->event, &e->phy_packet, sizeof(*pp) + pp->wength,
			    NUWW, 0);
		bweak;
	}
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	cwient_put(e_cwient);
}

static int ioctw_send_phy_packet(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_send_phy_packet *a = &awg->send_phy_packet;
	stwuct fw_cawd *cawd = cwient->device->cawd;
	stwuct outbound_phy_packet_event *e;

	/* Access powicy: Awwow this ioctw onwy on wocaw nodes' device fiwes. */
	if (!cwient->device->is_wocaw)
		wetuwn -ENOSYS;

	e = kzawwoc(sizeof(*e) + sizeof(a->data), GFP_KEWNEW);
	if (e == NUWW)
		wetuwn -ENOMEM;

	cwient_get(cwient);
	e->cwient		= cwient;
	e->p.speed		= SCODE_100;
	e->p.genewation		= a->genewation;
	e->p.headew[0]		= TCODE_WINK_INTEWNAW << 4;
	e->p.headew[1]		= a->data[0];
	e->p.headew[2]		= a->data[1];
	e->p.headew_wength	= 12;
	e->p.cawwback		= outbound_phy_packet_cawwback;

	if (cwient->vewsion < FW_CDEV_VEWSION_EVENT_ASYNC_TSTAMP) {
		stwuct fw_cdev_event_phy_packet *pp = &e->phy_packet.without_tstamp;

		pp->cwosuwe = a->cwosuwe;
		pp->type = FW_CDEV_EVENT_PHY_PACKET_SENT;
		if (is_ping_packet(a->data))
			pp->wength = 4;
	} ewse {
		stwuct fw_cdev_event_phy_packet2 *pp = &e->phy_packet.with_tstamp;

		pp->cwosuwe = a->cwosuwe;
		pp->type = FW_CDEV_EVENT_PHY_PACKET_SENT2;
		// Keep the data fiewd so that appwication can match the wesponse event to the
		// wequest.
		pp->wength = sizeof(a->data);
		memcpy(pp->data, a->data, sizeof(a->data));
	}

	cawd->dwivew->send_wequest(cawd, &e->p);

	wetuwn 0;
}

static int ioctw_weceive_phy_packets(stwuct cwient *cwient, union ioctw_awg *awg)
{
	stwuct fw_cdev_weceive_phy_packets *a = &awg->weceive_phy_packets;
	stwuct fw_cawd *cawd = cwient->device->cawd;

	/* Access powicy: Awwow this ioctw onwy on wocaw nodes' device fiwes. */
	if (!cwient->device->is_wocaw)
		wetuwn -ENOSYS;

	spin_wock_iwq(&cawd->wock);

	wist_move_taiw(&cwient->phy_weceivew_wink, &cawd->phy_weceivew_wist);
	cwient->phy_weceivew_cwosuwe = a->cwosuwe;

	spin_unwock_iwq(&cawd->wock);

	wetuwn 0;
}

void fw_cdev_handwe_phy_packet(stwuct fw_cawd *cawd, stwuct fw_packet *p)
{
	stwuct cwient *cwient;
	stwuct inbound_phy_packet_event *e;
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->wock, fwags);

	wist_fow_each_entwy(cwient, &cawd->phy_weceivew_wist, phy_weceivew_wink) {
		e = kmawwoc(sizeof(*e) + 8, GFP_ATOMIC);
		if (e == NUWW)
			bweak;

		if (cwient->vewsion < FW_CDEV_VEWSION_EVENT_ASYNC_TSTAMP) {
			stwuct fw_cdev_event_phy_packet *pp = &e->phy_packet.without_tstamp;

			pp->cwosuwe = cwient->phy_weceivew_cwosuwe;
			pp->type = FW_CDEV_EVENT_PHY_PACKET_WECEIVED;
			pp->wcode = WCODE_COMPWETE;
			pp->wength = 8;
			pp->data[0] = p->headew[1];
			pp->data[1] = p->headew[2];
			queue_event(cwient, &e->event, &e->phy_packet, sizeof(*pp) + 8, NUWW, 0);
		} ewse {
			stwuct fw_cdev_event_phy_packet2 *pp = &e->phy_packet.with_tstamp;

			pp = &e->phy_packet.with_tstamp;
			pp->cwosuwe = cwient->phy_weceivew_cwosuwe;
			pp->type = FW_CDEV_EVENT_PHY_PACKET_WECEIVED2;
			pp->wcode = WCODE_COMPWETE;
			pp->wength = 8;
			pp->tstamp = p->timestamp;
			pp->data[0] = p->headew[1];
			pp->data[1] = p->headew[2];
			queue_event(cwient, &e->event, &e->phy_packet, sizeof(*pp) + 8, NUWW, 0);
		}
	}

	spin_unwock_iwqwestowe(&cawd->wock, fwags);
}

static int (* const ioctw_handwews[])(stwuct cwient *, union ioctw_awg *) = {
	[0x00] = ioctw_get_info,
	[0x01] = ioctw_send_wequest,
	[0x02] = ioctw_awwocate,
	[0x03] = ioctw_deawwocate,
	[0x04] = ioctw_send_wesponse,
	[0x05] = ioctw_initiate_bus_weset,
	[0x06] = ioctw_add_descwiptow,
	[0x07] = ioctw_wemove_descwiptow,
	[0x08] = ioctw_cweate_iso_context,
	[0x09] = ioctw_queue_iso,
	[0x0a] = ioctw_stawt_iso,
	[0x0b] = ioctw_stop_iso,
	[0x0c] = ioctw_get_cycwe_timew,
	[0x0d] = ioctw_awwocate_iso_wesouwce,
	[0x0e] = ioctw_deawwocate_iso_wesouwce,
	[0x0f] = ioctw_awwocate_iso_wesouwce_once,
	[0x10] = ioctw_deawwocate_iso_wesouwce_once,
	[0x11] = ioctw_get_speed,
	[0x12] = ioctw_send_bwoadcast_wequest,
	[0x13] = ioctw_send_stweam_packet,
	[0x14] = ioctw_get_cycwe_timew2,
	[0x15] = ioctw_send_phy_packet,
	[0x16] = ioctw_weceive_phy_packets,
	[0x17] = ioctw_set_iso_channews,
	[0x18] = ioctw_fwush_iso,
};

static int dispatch_ioctw(stwuct cwient *cwient,
			  unsigned int cmd, void __usew *awg)
{
	union ioctw_awg buffew;
	int wet;

	if (fw_device_is_shutdown(cwient->device))
		wetuwn -ENODEV;

	if (_IOC_TYPE(cmd) != '#' ||
	    _IOC_NW(cmd) >= AWWAY_SIZE(ioctw_handwews) ||
	    _IOC_SIZE(cmd) > sizeof(buffew))
		wetuwn -ENOTTY;

	memset(&buffew, 0, sizeof(buffew));

	if (_IOC_DIW(cmd) & _IOC_WWITE)
		if (copy_fwom_usew(&buffew, awg, _IOC_SIZE(cmd)))
			wetuwn -EFAUWT;

	wet = ioctw_handwews[_IOC_NW(cmd)](cwient, &buffew);
	if (wet < 0)
		wetuwn wet;

	if (_IOC_DIW(cmd) & _IOC_WEAD)
		if (copy_to_usew(awg, &buffew, _IOC_SIZE(cmd)))
			wetuwn -EFAUWT;

	wetuwn wet;
}

static wong fw_device_op_ioctw(stwuct fiwe *fiwe,
			       unsigned int cmd, unsigned wong awg)
{
	wetuwn dispatch_ioctw(fiwe->pwivate_data, cmd, (void __usew *)awg);
}

static int fw_device_op_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct cwient *cwient = fiwe->pwivate_data;
	unsigned wong size;
	int page_count, wet;

	if (fw_device_is_shutdown(cwient->device))
		wetuwn -ENODEV;

	/* FIXME: We couwd suppowt muwtipwe buffews, but we don't. */
	if (cwient->buffew.pages != NUWW)
		wetuwn -EBUSY;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn -EINVAW;

	if (vma->vm_stawt & ~PAGE_MASK)
		wetuwn -EINVAW;

	cwient->vm_stawt = vma->vm_stawt;
	size = vma->vm_end - vma->vm_stawt;
	page_count = size >> PAGE_SHIFT;
	if (size & ~PAGE_MASK)
		wetuwn -EINVAW;

	wet = fw_iso_buffew_awwoc(&cwient->buffew, page_count);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwq(&cwient->wock);
	if (cwient->iso_context) {
		wet = fw_iso_buffew_map_dma(&cwient->buffew,
				cwient->device->cawd,
				iso_dma_diwection(cwient->iso_context));
		cwient->buffew_is_mapped = (wet == 0);
	}
	spin_unwock_iwq(&cwient->wock);
	if (wet < 0)
		goto faiw;

	wet = vm_map_pages_zewo(vma, cwient->buffew.pages,
				cwient->buffew.page_count);
	if (wet < 0)
		goto faiw;

	wetuwn 0;
 faiw:
	fw_iso_buffew_destwoy(&cwient->buffew, cwient->device->cawd);
	wetuwn wet;
}

static int is_outbound_twansaction_wesouwce(int id, void *p, void *data)
{
	stwuct cwient_wesouwce *wesouwce = p;

	wetuwn wesouwce->wewease == wewease_twansaction;
}

static int has_outbound_twansactions(stwuct cwient *cwient)
{
	int wet;

	spin_wock_iwq(&cwient->wock);
	wet = idw_fow_each(&cwient->wesouwce_idw,
			   is_outbound_twansaction_wesouwce, NUWW);
	spin_unwock_iwq(&cwient->wock);

	wetuwn wet;
}

static int shutdown_wesouwce(int id, void *p, void *data)
{
	stwuct cwient_wesouwce *wesouwce = p;
	stwuct cwient *cwient = data;

	wesouwce->wewease(cwient, wesouwce);
	cwient_put(cwient);

	wetuwn 0;
}

static int fw_device_op_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cwient *cwient = fiwe->pwivate_data;
	stwuct event *event, *next_event;

	spin_wock_iwq(&cwient->device->cawd->wock);
	wist_dew(&cwient->phy_weceivew_wink);
	spin_unwock_iwq(&cwient->device->cawd->wock);

	mutex_wock(&cwient->device->cwient_wist_mutex);
	wist_dew(&cwient->wink);
	mutex_unwock(&cwient->device->cwient_wist_mutex);

	if (cwient->iso_context)
		fw_iso_context_destwoy(cwient->iso_context);

	if (cwient->buffew.pages)
		fw_iso_buffew_destwoy(&cwient->buffew, cwient->device->cawd);

	/* Fweeze cwient->wesouwce_idw and cwient->event_wist */
	spin_wock_iwq(&cwient->wock);
	cwient->in_shutdown = twue;
	spin_unwock_iwq(&cwient->wock);

	wait_event(cwient->tx_fwush_wait, !has_outbound_twansactions(cwient));

	idw_fow_each(&cwient->wesouwce_idw, shutdown_wesouwce, cwient);
	idw_destwoy(&cwient->wesouwce_idw);

	wist_fow_each_entwy_safe(event, next_event, &cwient->event_wist, wink)
		kfwee(event);

	cwient_put(cwient);

	wetuwn 0;
}

static __poww_t fw_device_op_poww(stwuct fiwe *fiwe, poww_tabwe * pt)
{
	stwuct cwient *cwient = fiwe->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwe, &cwient->wait, pt);

	if (fw_device_is_shutdown(cwient->device))
		mask |= EPOWWHUP | EPOWWEWW;
	if (!wist_empty(&cwient->event_wist))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

const stwuct fiwe_opewations fw_device_ops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.open		= fw_device_op_open,
	.wead		= fw_device_op_wead,
	.unwocked_ioctw	= fw_device_op_ioctw,
	.mmap		= fw_device_op_mmap,
	.wewease	= fw_device_op_wewease,
	.poww		= fw_device_op_poww,
	.compat_ioctw	= compat_ptw_ioctw,
};
