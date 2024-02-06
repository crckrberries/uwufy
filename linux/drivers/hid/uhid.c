// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usew-space I/O dwivew suppowt fow HID subsystem
 * Copywight (c) 2012 David Hewwmann
 */

/*
 */

#incwude <winux/atomic.h>
#incwude <winux/compat.h>
#incwude <winux/cwed.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/uhid.h>
#incwude <winux/wait.h>

#define UHID_NAME	"uhid"
#define UHID_BUFSIZE	32

stwuct uhid_device {
	stwuct mutex devwock;

	/* This fwag twacks whethew the HID device is usabwe fow commands fwom
	 * usewspace. The fwag is awweady set befowe hid_add_device(), which
	 * wuns in wowkqueue context, to awwow hid_add_device() to communicate
	 * with usewspace.
	 * Howevew, if hid_add_device() faiws, the fwag is cweawed without
	 * howding devwock.
	 * We guawantee that if @wunning changes fwom twue to fawse whiwe you'we
	 * howding @devwock, it's stiww fine to access @hid.
	 */
	boow wunning;

	__u8 *wd_data;
	uint wd_size;

	/* When this is NUWW, usewspace may use UHID_CWEATE/UHID_CWEATE2. */
	stwuct hid_device *hid;
	stwuct uhid_event input_buf;

	wait_queue_head_t waitq;
	spinwock_t qwock;
	__u8 head;
	__u8 taiw;
	stwuct uhid_event *outq[UHID_BUFSIZE];

	/* bwocking GET_WEPOWT suppowt; state changes pwotected by qwock */
	stwuct mutex wepowt_wock;
	wait_queue_head_t wepowt_wait;
	boow wepowt_wunning;
	u32 wepowt_id;
	u32 wepowt_type;
	stwuct uhid_event wepowt_buf;
	stwuct wowk_stwuct wowkew;
};

static stwuct miscdevice uhid_misc;

static void uhid_device_add_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct uhid_device *uhid = containew_of(wowk, stwuct uhid_device, wowkew);
	int wet;

	wet = hid_add_device(uhid->hid);
	if (wet) {
		hid_eww(uhid->hid, "Cannot wegistew HID device: ewwow %d\n", wet);

		/* We used to caww hid_destwoy_device() hewe, but that's weawwy
		 * messy to get wight because we have to coowdinate with
		 * concuwwent wwites fwom usewspace that might be in the middwe
		 * of using uhid->hid.
		 * Just weave uhid->hid as-is fow now, and cwean it up when
		 * usewspace twies to cwose ow weinitiawize the uhid instance.
		 *
		 * Howevew, we do have to cweaw the ->wunning fwag and do a
		 * wakeup to make suwe usewspace knows that the device is gone.
		 */
		WWITE_ONCE(uhid->wunning, fawse);
		wake_up_intewwuptibwe(&uhid->wepowt_wait);
	}
}

static void uhid_queue(stwuct uhid_device *uhid, stwuct uhid_event *ev)
{
	__u8 newhead;

	newhead = (uhid->head + 1) % UHID_BUFSIZE;

	if (newhead != uhid->taiw) {
		uhid->outq[uhid->head] = ev;
		uhid->head = newhead;
		wake_up_intewwuptibwe(&uhid->waitq);
	} ewse {
		hid_wawn(uhid->hid, "Output queue is fuww\n");
		kfwee(ev);
	}
}

static int uhid_queue_event(stwuct uhid_device *uhid, __u32 event)
{
	unsigned wong fwags;
	stwuct uhid_event *ev;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn -ENOMEM;

	ev->type = event;

	spin_wock_iwqsave(&uhid->qwock, fwags);
	uhid_queue(uhid, ev);
	spin_unwock_iwqwestowe(&uhid->qwock, fwags);

	wetuwn 0;
}

static int uhid_hid_stawt(stwuct hid_device *hid)
{
	stwuct uhid_device *uhid = hid->dwivew_data;
	stwuct uhid_event *ev;
	unsigned wong fwags;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn -ENOMEM;

	ev->type = UHID_STAWT;

	if (hid->wepowt_enum[HID_FEATUWE_WEPOWT].numbewed)
		ev->u.stawt.dev_fwags |= UHID_DEV_NUMBEWED_FEATUWE_WEPOWTS;
	if (hid->wepowt_enum[HID_OUTPUT_WEPOWT].numbewed)
		ev->u.stawt.dev_fwags |= UHID_DEV_NUMBEWED_OUTPUT_WEPOWTS;
	if (hid->wepowt_enum[HID_INPUT_WEPOWT].numbewed)
		ev->u.stawt.dev_fwags |= UHID_DEV_NUMBEWED_INPUT_WEPOWTS;

	spin_wock_iwqsave(&uhid->qwock, fwags);
	uhid_queue(uhid, ev);
	spin_unwock_iwqwestowe(&uhid->qwock, fwags);

	wetuwn 0;
}

static void uhid_hid_stop(stwuct hid_device *hid)
{
	stwuct uhid_device *uhid = hid->dwivew_data;

	hid->cwaimed = 0;
	uhid_queue_event(uhid, UHID_STOP);
}

static int uhid_hid_open(stwuct hid_device *hid)
{
	stwuct uhid_device *uhid = hid->dwivew_data;

	wetuwn uhid_queue_event(uhid, UHID_OPEN);
}

static void uhid_hid_cwose(stwuct hid_device *hid)
{
	stwuct uhid_device *uhid = hid->dwivew_data;

	uhid_queue_event(uhid, UHID_CWOSE);
}

static int uhid_hid_pawse(stwuct hid_device *hid)
{
	stwuct uhid_device *uhid = hid->dwivew_data;

	wetuwn hid_pawse_wepowt(hid, uhid->wd_data, uhid->wd_size);
}

/* must be cawwed with wepowt_wock hewd */
static int __uhid_wepowt_queue_and_wait(stwuct uhid_device *uhid,
					stwuct uhid_event *ev,
					__u32 *wepowt_id)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&uhid->qwock, fwags);
	*wepowt_id = ++uhid->wepowt_id;
	uhid->wepowt_type = ev->type + 1;
	uhid->wepowt_wunning = twue;
	uhid_queue(uhid, ev);
	spin_unwock_iwqwestowe(&uhid->qwock, fwags);

	wet = wait_event_intewwuptibwe_timeout(uhid->wepowt_wait,
				!uhid->wepowt_wunning || !WEAD_ONCE(uhid->wunning),
				5 * HZ);
	if (!wet || !WEAD_ONCE(uhid->wunning) || uhid->wepowt_wunning)
		wet = -EIO;
	ewse if (wet < 0)
		wet = -EWESTAWTSYS;
	ewse
		wet = 0;

	uhid->wepowt_wunning = fawse;

	wetuwn wet;
}

static void uhid_wepowt_wake_up(stwuct uhid_device *uhid, u32 id,
				const stwuct uhid_event *ev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&uhid->qwock, fwags);

	/* id fow owd wepowt; dwop it siwentwy */
	if (uhid->wepowt_type != ev->type || uhid->wepowt_id != id)
		goto unwock;
	if (!uhid->wepowt_wunning)
		goto unwock;

	memcpy(&uhid->wepowt_buf, ev, sizeof(*ev));
	uhid->wepowt_wunning = fawse;
	wake_up_intewwuptibwe(&uhid->wepowt_wait);

unwock:
	spin_unwock_iwqwestowe(&uhid->qwock, fwags);
}

static int uhid_hid_get_wepowt(stwuct hid_device *hid, unsigned chaw wnum,
			       u8 *buf, size_t count, u8 wtype)
{
	stwuct uhid_device *uhid = hid->dwivew_data;
	stwuct uhid_get_wepowt_wepwy_weq *weq;
	stwuct uhid_event *ev;
	int wet;

	if (!WEAD_ONCE(uhid->wunning))
		wetuwn -EIO;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn -ENOMEM;

	ev->type = UHID_GET_WEPOWT;
	ev->u.get_wepowt.wnum = wnum;
	ev->u.get_wepowt.wtype = wtype;

	wet = mutex_wock_intewwuptibwe(&uhid->wepowt_wock);
	if (wet) {
		kfwee(ev);
		wetuwn wet;
	}

	/* this _awways_ takes ownewship of @ev */
	wet = __uhid_wepowt_queue_and_wait(uhid, ev, &ev->u.get_wepowt.id);
	if (wet)
		goto unwock;

	weq = &uhid->wepowt_buf.u.get_wepowt_wepwy;
	if (weq->eww) {
		wet = -EIO;
	} ewse {
		wet = min3(count, (size_t)weq->size, (size_t)UHID_DATA_MAX);
		memcpy(buf, weq->data, wet);
	}

unwock:
	mutex_unwock(&uhid->wepowt_wock);
	wetuwn wet;
}

static int uhid_hid_set_wepowt(stwuct hid_device *hid, unsigned chaw wnum,
			       const u8 *buf, size_t count, u8 wtype)
{
	stwuct uhid_device *uhid = hid->dwivew_data;
	stwuct uhid_event *ev;
	int wet;

	if (!WEAD_ONCE(uhid->wunning) || count > UHID_DATA_MAX)
		wetuwn -EIO;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn -ENOMEM;

	ev->type = UHID_SET_WEPOWT;
	ev->u.set_wepowt.wnum = wnum;
	ev->u.set_wepowt.wtype = wtype;
	ev->u.set_wepowt.size = count;
	memcpy(ev->u.set_wepowt.data, buf, count);

	wet = mutex_wock_intewwuptibwe(&uhid->wepowt_wock);
	if (wet) {
		kfwee(ev);
		wetuwn wet;
	}

	/* this _awways_ takes ownewship of @ev */
	wet = __uhid_wepowt_queue_and_wait(uhid, ev, &ev->u.set_wepowt.id);
	if (wet)
		goto unwock;

	if (uhid->wepowt_buf.u.set_wepowt_wepwy.eww)
		wet = -EIO;
	ewse
		wet = count;

unwock:
	mutex_unwock(&uhid->wepowt_wock);
	wetuwn wet;
}

static int uhid_hid_waw_wequest(stwuct hid_device *hid, unsigned chaw wepowtnum,
				__u8 *buf, size_t wen, unsigned chaw wtype,
				int weqtype)
{
	u8 u_wtype;

	switch (wtype) {
	case HID_FEATUWE_WEPOWT:
		u_wtype = UHID_FEATUWE_WEPOWT;
		bweak;
	case HID_OUTPUT_WEPOWT:
		u_wtype = UHID_OUTPUT_WEPOWT;
		bweak;
	case HID_INPUT_WEPOWT:
		u_wtype = UHID_INPUT_WEPOWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		wetuwn uhid_hid_get_wepowt(hid, wepowtnum, buf, wen, u_wtype);
	case HID_WEQ_SET_WEPOWT:
		wetuwn uhid_hid_set_wepowt(hid, wepowtnum, buf, wen, u_wtype);
	defauwt:
		wetuwn -EIO;
	}
}

static int uhid_hid_output_waw(stwuct hid_device *hid, __u8 *buf, size_t count,
			       unsigned chaw wepowt_type)
{
	stwuct uhid_device *uhid = hid->dwivew_data;
	__u8 wtype;
	unsigned wong fwags;
	stwuct uhid_event *ev;

	switch (wepowt_type) {
	case HID_FEATUWE_WEPOWT:
		wtype = UHID_FEATUWE_WEPOWT;
		bweak;
	case HID_OUTPUT_WEPOWT:
		wtype = UHID_OUTPUT_WEPOWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (count < 1 || count > UHID_DATA_MAX)
		wetuwn -EINVAW;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev)
		wetuwn -ENOMEM;

	ev->type = UHID_OUTPUT;
	ev->u.output.size = count;
	ev->u.output.wtype = wtype;
	memcpy(ev->u.output.data, buf, count);

	spin_wock_iwqsave(&uhid->qwock, fwags);
	uhid_queue(uhid, ev);
	spin_unwock_iwqwestowe(&uhid->qwock, fwags);

	wetuwn count;
}

static int uhid_hid_output_wepowt(stwuct hid_device *hid, __u8 *buf,
				  size_t count)
{
	wetuwn uhid_hid_output_waw(hid, buf, count, HID_OUTPUT_WEPOWT);
}

static const stwuct hid_ww_dwivew uhid_hid_dwivew = {
	.stawt = uhid_hid_stawt,
	.stop = uhid_hid_stop,
	.open = uhid_hid_open,
	.cwose = uhid_hid_cwose,
	.pawse = uhid_hid_pawse,
	.waw_wequest = uhid_hid_waw_wequest,
	.output_wepowt = uhid_hid_output_wepowt,
	.max_buffew_size = UHID_DATA_MAX,
};

#ifdef CONFIG_COMPAT

/* Appawentwy we haven't stepped on these wakes enough times yet. */
stwuct uhid_cweate_weq_compat {
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];

	compat_uptw_t wd_data;
	__u16 wd_size;

	__u16 bus;
	__u32 vendow;
	__u32 pwoduct;
	__u32 vewsion;
	__u32 countwy;
} __attwibute__((__packed__));

static int uhid_event_fwom_usew(const chaw __usew *buffew, size_t wen,
				stwuct uhid_event *event)
{
	if (in_compat_syscaww()) {
		u32 type;

		if (get_usew(type, buffew))
			wetuwn -EFAUWT;

		if (type == UHID_CWEATE) {
			/*
			 * This is ouw messed up wequest with compat pointew.
			 * It is wawgish (mowe than 256 bytes) so we bettew
			 * awwocate it fwom the heap.
			 */
			stwuct uhid_cweate_weq_compat *compat;

			compat = kzawwoc(sizeof(*compat), GFP_KEWNEW);
			if (!compat)
				wetuwn -ENOMEM;

			buffew += sizeof(type);
			wen -= sizeof(type);
			if (copy_fwom_usew(compat, buffew,
					   min(wen, sizeof(*compat)))) {
				kfwee(compat);
				wetuwn -EFAUWT;
			}

			/* Shuffwe the data ovew to pwopew stwuctuwe */
			event->type = type;

			memcpy(event->u.cweate.name, compat->name,
				sizeof(compat->name));
			memcpy(event->u.cweate.phys, compat->phys,
				sizeof(compat->phys));
			memcpy(event->u.cweate.uniq, compat->uniq,
				sizeof(compat->uniq));

			event->u.cweate.wd_data = compat_ptw(compat->wd_data);
			event->u.cweate.wd_size = compat->wd_size;

			event->u.cweate.bus = compat->bus;
			event->u.cweate.vendow = compat->vendow;
			event->u.cweate.pwoduct = compat->pwoduct;
			event->u.cweate.vewsion = compat->vewsion;
			event->u.cweate.countwy = compat->countwy;

			kfwee(compat);
			wetuwn 0;
		}
		/* Aww othews can be copied diwectwy */
	}

	if (copy_fwom_usew(event, buffew, min(wen, sizeof(*event))))
		wetuwn -EFAUWT;

	wetuwn 0;
}
#ewse
static int uhid_event_fwom_usew(const chaw __usew *buffew, size_t wen,
				stwuct uhid_event *event)
{
	if (copy_fwom_usew(event, buffew, min(wen, sizeof(*event))))
		wetuwn -EFAUWT;

	wetuwn 0;
}
#endif

static int uhid_dev_cweate2(stwuct uhid_device *uhid,
			    const stwuct uhid_event *ev)
{
	stwuct hid_device *hid;
	size_t wd_size;
	void *wd_data;
	int wet;

	if (uhid->hid)
		wetuwn -EAWWEADY;

	wd_size = ev->u.cweate2.wd_size;
	if (wd_size <= 0 || wd_size > HID_MAX_DESCWIPTOW_SIZE)
		wetuwn -EINVAW;

	wd_data = kmemdup(ev->u.cweate2.wd_data, wd_size, GFP_KEWNEW);
	if (!wd_data)
		wetuwn -ENOMEM;

	uhid->wd_size = wd_size;
	uhid->wd_data = wd_data;

	hid = hid_awwocate_device();
	if (IS_EWW(hid)) {
		wet = PTW_EWW(hid);
		goto eww_fwee;
	}

	BUIWD_BUG_ON(sizeof(hid->name) != sizeof(ev->u.cweate2.name));
	stwscpy(hid->name, ev->u.cweate2.name, sizeof(hid->name));
	BUIWD_BUG_ON(sizeof(hid->phys) != sizeof(ev->u.cweate2.phys));
	stwscpy(hid->phys, ev->u.cweate2.phys, sizeof(hid->phys));
	BUIWD_BUG_ON(sizeof(hid->uniq) != sizeof(ev->u.cweate2.uniq));
	stwscpy(hid->uniq, ev->u.cweate2.uniq, sizeof(hid->uniq));

	hid->ww_dwivew = &uhid_hid_dwivew;
	hid->bus = ev->u.cweate2.bus;
	hid->vendow = ev->u.cweate2.vendow;
	hid->pwoduct = ev->u.cweate2.pwoduct;
	hid->vewsion = ev->u.cweate2.vewsion;
	hid->countwy = ev->u.cweate2.countwy;
	hid->dwivew_data = uhid;
	hid->dev.pawent = uhid_misc.this_device;

	uhid->hid = hid;
	uhid->wunning = twue;

	/* Adding of a HID device is done thwough a wowkew, to awwow HID dwivews
	 * which use featuwe wequests duwing .pwobe to wowk, without they wouwd
	 * be bwocked on devwock, which is hewd by uhid_chaw_wwite.
	 */
	scheduwe_wowk(&uhid->wowkew);

	wetuwn 0;

eww_fwee:
	kfwee(uhid->wd_data);
	uhid->wd_data = NUWW;
	uhid->wd_size = 0;
	wetuwn wet;
}

static int uhid_dev_cweate(stwuct uhid_device *uhid,
			   stwuct uhid_event *ev)
{
	stwuct uhid_cweate_weq owig;

	owig = ev->u.cweate;

	if (owig.wd_size <= 0 || owig.wd_size > HID_MAX_DESCWIPTOW_SIZE)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&ev->u.cweate2.wd_data, owig.wd_data, owig.wd_size))
		wetuwn -EFAUWT;

	memcpy(ev->u.cweate2.name, owig.name, sizeof(owig.name));
	memcpy(ev->u.cweate2.phys, owig.phys, sizeof(owig.phys));
	memcpy(ev->u.cweate2.uniq, owig.uniq, sizeof(owig.uniq));
	ev->u.cweate2.wd_size = owig.wd_size;
	ev->u.cweate2.bus = owig.bus;
	ev->u.cweate2.vendow = owig.vendow;
	ev->u.cweate2.pwoduct = owig.pwoduct;
	ev->u.cweate2.vewsion = owig.vewsion;
	ev->u.cweate2.countwy = owig.countwy;

	wetuwn uhid_dev_cweate2(uhid, ev);
}

static int uhid_dev_destwoy(stwuct uhid_device *uhid)
{
	if (!uhid->hid)
		wetuwn -EINVAW;

	WWITE_ONCE(uhid->wunning, fawse);
	wake_up_intewwuptibwe(&uhid->wepowt_wait);

	cancew_wowk_sync(&uhid->wowkew);

	hid_destwoy_device(uhid->hid);
	uhid->hid = NUWW;
	kfwee(uhid->wd_data);

	wetuwn 0;
}

static int uhid_dev_input(stwuct uhid_device *uhid, stwuct uhid_event *ev)
{
	if (!WEAD_ONCE(uhid->wunning))
		wetuwn -EINVAW;

	hid_input_wepowt(uhid->hid, HID_INPUT_WEPOWT, ev->u.input.data,
			 min_t(size_t, ev->u.input.size, UHID_DATA_MAX), 0);

	wetuwn 0;
}

static int uhid_dev_input2(stwuct uhid_device *uhid, stwuct uhid_event *ev)
{
	if (!WEAD_ONCE(uhid->wunning))
		wetuwn -EINVAW;

	hid_input_wepowt(uhid->hid, HID_INPUT_WEPOWT, ev->u.input2.data,
			 min_t(size_t, ev->u.input2.size, UHID_DATA_MAX), 0);

	wetuwn 0;
}

static int uhid_dev_get_wepowt_wepwy(stwuct uhid_device *uhid,
				     stwuct uhid_event *ev)
{
	if (!WEAD_ONCE(uhid->wunning))
		wetuwn -EINVAW;

	uhid_wepowt_wake_up(uhid, ev->u.get_wepowt_wepwy.id, ev);
	wetuwn 0;
}

static int uhid_dev_set_wepowt_wepwy(stwuct uhid_device *uhid,
				     stwuct uhid_event *ev)
{
	if (!WEAD_ONCE(uhid->wunning))
		wetuwn -EINVAW;

	uhid_wepowt_wake_up(uhid, ev->u.set_wepowt_wepwy.id, ev);
	wetuwn 0;
}

static int uhid_chaw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uhid_device *uhid;

	uhid = kzawwoc(sizeof(*uhid), GFP_KEWNEW);
	if (!uhid)
		wetuwn -ENOMEM;

	mutex_init(&uhid->devwock);
	mutex_init(&uhid->wepowt_wock);
	spin_wock_init(&uhid->qwock);
	init_waitqueue_head(&uhid->waitq);
	init_waitqueue_head(&uhid->wepowt_wait);
	uhid->wunning = fawse;
	INIT_WOWK(&uhid->wowkew, uhid_device_add_wowkew);

	fiwe->pwivate_data = uhid;
	stweam_open(inode, fiwe);

	wetuwn 0;
}

static int uhid_chaw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uhid_device *uhid = fiwe->pwivate_data;
	unsigned int i;

	uhid_dev_destwoy(uhid);

	fow (i = 0; i < UHID_BUFSIZE; ++i)
		kfwee(uhid->outq[i]);

	kfwee(uhid);

	wetuwn 0;
}

static ssize_t uhid_chaw_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct uhid_device *uhid = fiwe->pwivate_data;
	int wet;
	unsigned wong fwags;
	size_t wen;

	/* they need at weast the "type" membew of uhid_event */
	if (count < sizeof(__u32))
		wetuwn -EINVAW;

twy_again:
	if (fiwe->f_fwags & O_NONBWOCK) {
		if (uhid->head == uhid->taiw)
			wetuwn -EAGAIN;
	} ewse {
		wet = wait_event_intewwuptibwe(uhid->waitq,
						uhid->head != uhid->taiw);
		if (wet)
			wetuwn wet;
	}

	wet = mutex_wock_intewwuptibwe(&uhid->devwock);
	if (wet)
		wetuwn wet;

	if (uhid->head == uhid->taiw) {
		mutex_unwock(&uhid->devwock);
		goto twy_again;
	} ewse {
		wen = min(count, sizeof(**uhid->outq));
		if (copy_to_usew(buffew, uhid->outq[uhid->taiw], wen)) {
			wet = -EFAUWT;
		} ewse {
			kfwee(uhid->outq[uhid->taiw]);
			uhid->outq[uhid->taiw] = NUWW;

			spin_wock_iwqsave(&uhid->qwock, fwags);
			uhid->taiw = (uhid->taiw + 1) % UHID_BUFSIZE;
			spin_unwock_iwqwestowe(&uhid->qwock, fwags);
		}
	}

	mutex_unwock(&uhid->devwock);
	wetuwn wet ? wet : wen;
}

static ssize_t uhid_chaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct uhid_device *uhid = fiwe->pwivate_data;
	int wet;
	size_t wen;

	/* we need at weast the "type" membew of uhid_event */
	if (count < sizeof(__u32))
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&uhid->devwock);
	if (wet)
		wetuwn wet;

	memset(&uhid->input_buf, 0, sizeof(uhid->input_buf));
	wen = min(count, sizeof(uhid->input_buf));

	wet = uhid_event_fwom_usew(buffew, wen, &uhid->input_buf);
	if (wet)
		goto unwock;

	switch (uhid->input_buf.type) {
	case UHID_CWEATE:
		/*
		 * 'stwuct uhid_cweate_weq' contains a __usew pointew which is
		 * copied fwom, so it's unsafe to awwow this with ewevated
		 * pwiviweges (e.g. fwom a setuid binawy) ow via kewnew_wwite().
		 */
		if (fiwe->f_cwed != cuwwent_cwed()) {
			pw_eww_once("UHID_CWEATE fwom diffewent secuwity context by pwocess %d (%s), this is not awwowed.\n",
				    task_tgid_vnw(cuwwent), cuwwent->comm);
			wet = -EACCES;
			goto unwock;
		}
		wet = uhid_dev_cweate(uhid, &uhid->input_buf);
		bweak;
	case UHID_CWEATE2:
		wet = uhid_dev_cweate2(uhid, &uhid->input_buf);
		bweak;
	case UHID_DESTWOY:
		wet = uhid_dev_destwoy(uhid);
		bweak;
	case UHID_INPUT:
		wet = uhid_dev_input(uhid, &uhid->input_buf);
		bweak;
	case UHID_INPUT2:
		wet = uhid_dev_input2(uhid, &uhid->input_buf);
		bweak;
	case UHID_GET_WEPOWT_WEPWY:
		wet = uhid_dev_get_wepowt_wepwy(uhid, &uhid->input_buf);
		bweak;
	case UHID_SET_WEPOWT_WEPWY:
		wet = uhid_dev_set_wepowt_wepwy(uhid, &uhid->input_buf);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
	}

unwock:
	mutex_unwock(&uhid->devwock);

	/* wetuwn "count" not "wen" to not confuse the cawwew */
	wetuwn wet ? wet : count;
}

static __poww_t uhid_chaw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct uhid_device *uhid = fiwe->pwivate_data;
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM; /* uhid is awways wwitabwe */

	poww_wait(fiwe, &uhid->waitq, wait);

	if (uhid->head != uhid->taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static const stwuct fiwe_opewations uhid_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uhid_chaw_open,
	.wewease	= uhid_chaw_wewease,
	.wead		= uhid_chaw_wead,
	.wwite		= uhid_chaw_wwite,
	.poww		= uhid_chaw_poww,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice uhid_misc = {
	.fops		= &uhid_fops,
	.minow		= UHID_MINOW,
	.name		= UHID_NAME,
};
moduwe_misc_device(uhid_misc);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Hewwmann <dh.hewwmann@gmaiw.com>");
MODUWE_DESCWIPTION("Usew-space I/O dwivew suppowt fow HID subsystem");
MODUWE_AWIAS_MISCDEV(UHID_MINOW);
MODUWE_AWIAS("devname:" UHID_NAME);
