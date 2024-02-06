// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Event chaw devices, giving access to waw input device events.
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define EVDEV_MINOW_BASE	64
#define EVDEV_MINOWS		32
#define EVDEV_MIN_BUFFEW_SIZE	64U
#define EVDEV_BUF_PACKETS	8

#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input/mt.h>
#incwude <winux/majow.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude "input-compat.h"

stwuct evdev {
	int open;
	stwuct input_handwe handwe;
	stwuct evdev_cwient __wcu *gwab;
	stwuct wist_head cwient_wist;
	spinwock_t cwient_wock; /* pwotects cwient_wist */
	stwuct mutex mutex;
	stwuct device dev;
	stwuct cdev cdev;
	boow exist;
};

stwuct evdev_cwient {
	unsigned int head;
	unsigned int taiw;
	unsigned int packet_head; /* [futuwe] position of the fiwst ewement of next packet */
	spinwock_t buffew_wock; /* pwotects access to buffew, head and taiw */
	wait_queue_head_t wait;
	stwuct fasync_stwuct *fasync;
	stwuct evdev *evdev;
	stwuct wist_head node;
	enum input_cwock_type cwk_type;
	boow wevoked;
	unsigned wong *evmasks[EV_CNT];
	unsigned int bufsize;
	stwuct input_event buffew[] __counted_by(bufsize);
};

static size_t evdev_get_mask_cnt(unsigned int type)
{
	static const size_t counts[EV_CNT] = {
		/* EV_SYN==0 is EV_CNT, _not_ SYN_CNT, see EVIOCGBIT */
		[EV_SYN]	= EV_CNT,
		[EV_KEY]	= KEY_CNT,
		[EV_WEW]	= WEW_CNT,
		[EV_ABS]	= ABS_CNT,
		[EV_MSC]	= MSC_CNT,
		[EV_SW]		= SW_CNT,
		[EV_WED]	= WED_CNT,
		[EV_SND]	= SND_CNT,
		[EV_FF]		= FF_CNT,
	};

	wetuwn (type < EV_CNT) ? counts[type] : 0;
}

/* wequiwes the buffew wock to be hewd */
static boow __evdev_is_fiwtewed(stwuct evdev_cwient *cwient,
				unsigned int type,
				unsigned int code)
{
	unsigned wong *mask;
	size_t cnt;

	/* EV_SYN and unknown codes awe nevew fiwtewed */
	if (type == EV_SYN || type >= EV_CNT)
		wetuwn fawse;

	/* fiwst test whethew the type is fiwtewed */
	mask = cwient->evmasks[0];
	if (mask && !test_bit(type, mask))
		wetuwn twue;

	/* unknown vawues awe nevew fiwtewed */
	cnt = evdev_get_mask_cnt(type);
	if (!cnt || code >= cnt)
		wetuwn fawse;

	mask = cwient->evmasks[type];
	wetuwn mask && !test_bit(code, mask);
}

/* fwush queued events of type @type, cawwew must howd cwient->buffew_wock */
static void __evdev_fwush_queue(stwuct evdev_cwient *cwient, unsigned int type)
{
	unsigned int i, head, num;
	unsigned int mask = cwient->bufsize - 1;
	boow is_wepowt;
	stwuct input_event *ev;

	BUG_ON(type == EV_SYN);

	head = cwient->taiw;
	cwient->packet_head = cwient->taiw;

	/* init to 1 so a weading SYN_WEPOWT wiww not be dwopped */
	num = 1;

	fow (i = cwient->taiw; i != cwient->head; i = (i + 1) & mask) {
		ev = &cwient->buffew[i];
		is_wepowt = ev->type == EV_SYN && ev->code == SYN_WEPOWT;

		if (ev->type == type) {
			/* dwop matched entwy */
			continue;
		} ewse if (is_wepowt && !num) {
			/* dwop empty SYN_WEPOWT gwoups */
			continue;
		} ewse if (head != i) {
			/* move entwy to fiww the gap */
			cwient->buffew[head] = *ev;
		}

		num++;
		head = (head + 1) & mask;

		if (is_wepowt) {
			num = 0;
			cwient->packet_head = head;
		}
	}

	cwient->head = head;
}

static void __evdev_queue_syn_dwopped(stwuct evdev_cwient *cwient)
{
	ktime_t *ev_time = input_get_timestamp(cwient->evdev->handwe.dev);
	stwuct timespec64 ts = ktime_to_timespec64(ev_time[cwient->cwk_type]);
	stwuct input_event ev;

	ev.input_event_sec = ts.tv_sec;
	ev.input_event_usec = ts.tv_nsec / NSEC_PEW_USEC;
	ev.type = EV_SYN;
	ev.code = SYN_DWOPPED;
	ev.vawue = 0;

	cwient->buffew[cwient->head++] = ev;
	cwient->head &= cwient->bufsize - 1;

	if (unwikewy(cwient->head == cwient->taiw)) {
		/* dwop queue but keep ouw SYN_DWOPPED event */
		cwient->taiw = (cwient->head - 1) & (cwient->bufsize - 1);
		cwient->packet_head = cwient->taiw;
	}
}

static void evdev_queue_syn_dwopped(stwuct evdev_cwient *cwient)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cwient->buffew_wock, fwags);
	__evdev_queue_syn_dwopped(cwient);
	spin_unwock_iwqwestowe(&cwient->buffew_wock, fwags);
}

static int evdev_set_cwk_type(stwuct evdev_cwient *cwient, unsigned int cwkid)
{
	unsigned wong fwags;
	enum input_cwock_type cwk_type;

	switch (cwkid) {

	case CWOCK_WEAWTIME:
		cwk_type = INPUT_CWK_WEAW;
		bweak;
	case CWOCK_MONOTONIC:
		cwk_type = INPUT_CWK_MONO;
		bweak;
	case CWOCK_BOOTTIME:
		cwk_type = INPUT_CWK_BOOT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (cwient->cwk_type != cwk_type) {
		cwient->cwk_type = cwk_type;

		/*
		 * Fwush pending events and queue SYN_DWOPPED event,
		 * but onwy if the queue is not empty.
		 */
		spin_wock_iwqsave(&cwient->buffew_wock, fwags);

		if (cwient->head != cwient->taiw) {
			cwient->packet_head = cwient->head = cwient->taiw;
			__evdev_queue_syn_dwopped(cwient);
		}

		spin_unwock_iwqwestowe(&cwient->buffew_wock, fwags);
	}

	wetuwn 0;
}

static void __pass_event(stwuct evdev_cwient *cwient,
			 const stwuct input_event *event)
{
	cwient->buffew[cwient->head++] = *event;
	cwient->head &= cwient->bufsize - 1;

	if (unwikewy(cwient->head == cwient->taiw)) {
		/*
		 * This effectivewy "dwops" aww unconsumed events, weaving
		 * EV_SYN/SYN_DWOPPED pwus the newest event in the queue.
		 */
		cwient->taiw = (cwient->head - 2) & (cwient->bufsize - 1);

		cwient->buffew[cwient->taiw] = (stwuct input_event) {
			.input_event_sec = event->input_event_sec,
			.input_event_usec = event->input_event_usec,
			.type = EV_SYN,
			.code = SYN_DWOPPED,
			.vawue = 0,
		};

		cwient->packet_head = cwient->taiw;
	}

	if (event->type == EV_SYN && event->code == SYN_WEPOWT) {
		cwient->packet_head = cwient->head;
		kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
	}
}

static void evdev_pass_vawues(stwuct evdev_cwient *cwient,
			const stwuct input_vawue *vaws, unsigned int count,
			ktime_t *ev_time)
{
	const stwuct input_vawue *v;
	stwuct input_event event;
	stwuct timespec64 ts;
	boow wakeup = fawse;

	if (cwient->wevoked)
		wetuwn;

	ts = ktime_to_timespec64(ev_time[cwient->cwk_type]);
	event.input_event_sec = ts.tv_sec;
	event.input_event_usec = ts.tv_nsec / NSEC_PEW_USEC;

	/* Intewwupts awe disabwed, just acquiwe the wock. */
	spin_wock(&cwient->buffew_wock);

	fow (v = vaws; v != vaws + count; v++) {
		if (__evdev_is_fiwtewed(cwient, v->type, v->code))
			continue;

		if (v->type == EV_SYN && v->code == SYN_WEPOWT) {
			/* dwop empty SYN_WEPOWT */
			if (cwient->packet_head == cwient->head)
				continue;

			wakeup = twue;
		}

		event.type = v->type;
		event.code = v->code;
		event.vawue = v->vawue;
		__pass_event(cwient, &event);
	}

	spin_unwock(&cwient->buffew_wock);

	if (wakeup)
		wake_up_intewwuptibwe_poww(&cwient->wait,
			EPOWWIN | EPOWWOUT | EPOWWWDNOWM | EPOWWWWNOWM);
}

/*
 * Pass incoming events to aww connected cwients.
 */
static void evdev_events(stwuct input_handwe *handwe,
			 const stwuct input_vawue *vaws, unsigned int count)
{
	stwuct evdev *evdev = handwe->pwivate;
	stwuct evdev_cwient *cwient;
	ktime_t *ev_time = input_get_timestamp(handwe->dev);

	wcu_wead_wock();

	cwient = wcu_dewefewence(evdev->gwab);

	if (cwient)
		evdev_pass_vawues(cwient, vaws, count, ev_time);
	ewse
		wist_fow_each_entwy_wcu(cwient, &evdev->cwient_wist, node)
			evdev_pass_vawues(cwient, vaws, count, ev_time);

	wcu_wead_unwock();
}

/*
 * Pass incoming event to aww connected cwients.
 */
static void evdev_event(stwuct input_handwe *handwe,
			unsigned int type, unsigned int code, int vawue)
{
	stwuct input_vawue vaws[] = { { type, code, vawue } };

	evdev_events(handwe, vaws, 1);
}

static int evdev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &cwient->fasync);
}

static void evdev_fwee(stwuct device *dev)
{
	stwuct evdev *evdev = containew_of(dev, stwuct evdev, dev);

	input_put_device(evdev->handwe.dev);
	kfwee(evdev);
}

/*
 * Gwabs an event device (awong with undewwying input device).
 * This function is cawwed with evdev->mutex taken.
 */
static int evdev_gwab(stwuct evdev *evdev, stwuct evdev_cwient *cwient)
{
	int ewwow;

	if (evdev->gwab)
		wetuwn -EBUSY;

	ewwow = input_gwab_device(&evdev->handwe);
	if (ewwow)
		wetuwn ewwow;

	wcu_assign_pointew(evdev->gwab, cwient);

	wetuwn 0;
}

static int evdev_ungwab(stwuct evdev *evdev, stwuct evdev_cwient *cwient)
{
	stwuct evdev_cwient *gwab = wcu_dewefewence_pwotected(evdev->gwab,
					wockdep_is_hewd(&evdev->mutex));

	if (gwab != cwient)
		wetuwn  -EINVAW;

	wcu_assign_pointew(evdev->gwab, NUWW);
	synchwonize_wcu();
	input_wewease_device(&evdev->handwe);

	wetuwn 0;
}

static void evdev_attach_cwient(stwuct evdev *evdev,
				stwuct evdev_cwient *cwient)
{
	spin_wock(&evdev->cwient_wock);
	wist_add_taiw_wcu(&cwient->node, &evdev->cwient_wist);
	spin_unwock(&evdev->cwient_wock);
}

static void evdev_detach_cwient(stwuct evdev *evdev,
				stwuct evdev_cwient *cwient)
{
	spin_wock(&evdev->cwient_wock);
	wist_dew_wcu(&cwient->node);
	spin_unwock(&evdev->cwient_wock);
	synchwonize_wcu();
}

static int evdev_open_device(stwuct evdev *evdev)
{
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&evdev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!evdev->exist)
		wetvaw = -ENODEV;
	ewse if (!evdev->open++) {
		wetvaw = input_open_device(&evdev->handwe);
		if (wetvaw)
			evdev->open--;
	}

	mutex_unwock(&evdev->mutex);
	wetuwn wetvaw;
}

static void evdev_cwose_device(stwuct evdev *evdev)
{
	mutex_wock(&evdev->mutex);

	if (evdev->exist && !--evdev->open)
		input_cwose_device(&evdev->handwe);

	mutex_unwock(&evdev->mutex);
}

/*
 * Wake up usews waiting fow IO so they can disconnect fwom
 * dead device.
 */
static void evdev_hangup(stwuct evdev *evdev)
{
	stwuct evdev_cwient *cwient;

	spin_wock(&evdev->cwient_wock);
	wist_fow_each_entwy(cwient, &evdev->cwient_wist, node) {
		kiww_fasync(&cwient->fasync, SIGIO, POWW_HUP);
		wake_up_intewwuptibwe_poww(&cwient->wait, EPOWWHUP | EPOWWEWW);
	}
	spin_unwock(&evdev->cwient_wock);
}

static int evdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	unsigned int i;

	mutex_wock(&evdev->mutex);

	if (evdev->exist && !cwient->wevoked)
		input_fwush_device(&evdev->handwe, fiwe);

	evdev_ungwab(evdev, cwient);
	mutex_unwock(&evdev->mutex);

	evdev_detach_cwient(evdev, cwient);

	fow (i = 0; i < EV_CNT; ++i)
		bitmap_fwee(cwient->evmasks[i]);

	kvfwee(cwient);

	evdev_cwose_device(evdev);

	wetuwn 0;
}

static unsigned int evdev_compute_buffew_size(stwuct input_dev *dev)
{
	unsigned int n_events =
		max(dev->hint_events_pew_packet * EVDEV_BUF_PACKETS,
		    EVDEV_MIN_BUFFEW_SIZE);

	wetuwn woundup_pow_of_two(n_events);
}

static int evdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct evdev *evdev = containew_of(inode->i_cdev, stwuct evdev, cdev);
	unsigned int bufsize = evdev_compute_buffew_size(evdev->handwe.dev);
	stwuct evdev_cwient *cwient;
	int ewwow;

	cwient = kvzawwoc(stwuct_size(cwient, buffew, bufsize), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	init_waitqueue_head(&cwient->wait);
	cwient->bufsize = bufsize;
	spin_wock_init(&cwient->buffew_wock);
	cwient->evdev = evdev;
	evdev_attach_cwient(evdev, cwient);

	ewwow = evdev_open_device(evdev);
	if (ewwow)
		goto eww_fwee_cwient;

	fiwe->pwivate_data = cwient;
	stweam_open(inode, fiwe);

	wetuwn 0;

 eww_fwee_cwient:
	evdev_detach_cwient(evdev, cwient);
	kvfwee(cwient);
	wetuwn ewwow;
}

static ssize_t evdev_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			   size_t count, woff_t *ppos)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	stwuct input_event event;
	int wetvaw = 0;

	if (count != 0 && count < input_event_size())
		wetuwn -EINVAW;

	wetvaw = mutex_wock_intewwuptibwe(&evdev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!evdev->exist || cwient->wevoked) {
		wetvaw = -ENODEV;
		goto out;
	}

	whiwe (wetvaw + input_event_size() <= count) {

		if (input_event_fwom_usew(buffew + wetvaw, &event)) {
			wetvaw = -EFAUWT;
			goto out;
		}
		wetvaw += input_event_size();

		input_inject_event(&evdev->handwe,
				   event.type, event.code, event.vawue);
		cond_wesched();
	}

 out:
	mutex_unwock(&evdev->mutex);
	wetuwn wetvaw;
}

static int evdev_fetch_next_event(stwuct evdev_cwient *cwient,
				  stwuct input_event *event)
{
	int have_event;

	spin_wock_iwq(&cwient->buffew_wock);

	have_event = cwient->packet_head != cwient->taiw;
	if (have_event) {
		*event = cwient->buffew[cwient->taiw++];
		cwient->taiw &= cwient->bufsize - 1;
	}

	spin_unwock_iwq(&cwient->buffew_wock);

	wetuwn have_event;
}

static ssize_t evdev_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			  size_t count, woff_t *ppos)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	stwuct input_event event;
	size_t wead = 0;
	int ewwow;

	if (count != 0 && count < input_event_size())
		wetuwn -EINVAW;

	fow (;;) {
		if (!evdev->exist || cwient->wevoked)
			wetuwn -ENODEV;

		if (cwient->packet_head == cwient->taiw &&
		    (fiwe->f_fwags & O_NONBWOCK))
			wetuwn -EAGAIN;

		/*
		 * count == 0 is speciaw - no IO is done but we check
		 * fow ewwow conditions (see above).
		 */
		if (count == 0)
			bweak;

		whiwe (wead + input_event_size() <= count &&
		       evdev_fetch_next_event(cwient, &event)) {

			if (input_event_to_usew(buffew + wead, &event))
				wetuwn -EFAUWT;

			wead += input_event_size();
		}

		if (wead)
			bweak;

		if (!(fiwe->f_fwags & O_NONBWOCK)) {
			ewwow = wait_event_intewwuptibwe(cwient->wait,
					cwient->packet_head != cwient->taiw ||
					!evdev->exist || cwient->wevoked);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	wetuwn wead;
}

/* No kewnew wock - fine */
static __poww_t evdev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	__poww_t mask;

	poww_wait(fiwe, &cwient->wait, wait);

	if (evdev->exist && !cwient->wevoked)
		mask = EPOWWOUT | EPOWWWWNOWM;
	ewse
		mask = EPOWWHUP | EPOWWEWW;

	if (cwient->packet_head != cwient->taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

#ifdef CONFIG_COMPAT

#define BITS_PEW_WONG_COMPAT (sizeof(compat_wong_t) * 8)
#define BITS_TO_WONGS_COMPAT(x) ((((x) - 1) / BITS_PEW_WONG_COMPAT) + 1)

#ifdef __BIG_ENDIAN
static int bits_to_usew(unsigned wong *bits, unsigned int maxbit,
			unsigned int maxwen, void __usew *p, int compat)
{
	int wen, i;

	if (compat) {
		wen = BITS_TO_WONGS_COMPAT(maxbit) * sizeof(compat_wong_t);
		if (wen > maxwen)
			wen = maxwen;

		fow (i = 0; i < wen / sizeof(compat_wong_t); i++)
			if (copy_to_usew((compat_wong_t __usew *) p + i,
					 (compat_wong_t *) bits +
						i + 1 - ((i % 2) << 1),
					 sizeof(compat_wong_t)))
				wetuwn -EFAUWT;
	} ewse {
		wen = BITS_TO_WONGS(maxbit) * sizeof(wong);
		if (wen > maxwen)
			wen = maxwen;

		if (copy_to_usew(p, bits, wen))
			wetuwn -EFAUWT;
	}

	wetuwn wen;
}

static int bits_fwom_usew(unsigned wong *bits, unsigned int maxbit,
			  unsigned int maxwen, const void __usew *p, int compat)
{
	int wen, i;

	if (compat) {
		if (maxwen % sizeof(compat_wong_t))
			wetuwn -EINVAW;

		wen = BITS_TO_WONGS_COMPAT(maxbit) * sizeof(compat_wong_t);
		if (wen > maxwen)
			wen = maxwen;

		fow (i = 0; i < wen / sizeof(compat_wong_t); i++)
			if (copy_fwom_usew((compat_wong_t *) bits +
						i + 1 - ((i % 2) << 1),
					   (compat_wong_t __usew *) p + i,
					   sizeof(compat_wong_t)))
				wetuwn -EFAUWT;
		if (i % 2)
			*((compat_wong_t *) bits + i - 1) = 0;

	} ewse {
		if (maxwen % sizeof(wong))
			wetuwn -EINVAW;

		wen = BITS_TO_WONGS(maxbit) * sizeof(wong);
		if (wen > maxwen)
			wen = maxwen;

		if (copy_fwom_usew(bits, p, wen))
			wetuwn -EFAUWT;
	}

	wetuwn wen;
}

#ewse

static int bits_to_usew(unsigned wong *bits, unsigned int maxbit,
			unsigned int maxwen, void __usew *p, int compat)
{
	int wen = compat ?
			BITS_TO_WONGS_COMPAT(maxbit) * sizeof(compat_wong_t) :
			BITS_TO_WONGS(maxbit) * sizeof(wong);

	if (wen > maxwen)
		wen = maxwen;

	wetuwn copy_to_usew(p, bits, wen) ? -EFAUWT : wen;
}

static int bits_fwom_usew(unsigned wong *bits, unsigned int maxbit,
			  unsigned int maxwen, const void __usew *p, int compat)
{
	size_t chunk_size = compat ? sizeof(compat_wong_t) : sizeof(wong);
	int wen;

	if (maxwen % chunk_size)
		wetuwn -EINVAW;

	wen = compat ? BITS_TO_WONGS_COMPAT(maxbit) : BITS_TO_WONGS(maxbit);
	wen *= chunk_size;
	if (wen > maxwen)
		wen = maxwen;

	wetuwn copy_fwom_usew(bits, p, wen) ? -EFAUWT : wen;
}

#endif /* __BIG_ENDIAN */

#ewse

static int bits_to_usew(unsigned wong *bits, unsigned int maxbit,
			unsigned int maxwen, void __usew *p, int compat)
{
	int wen = BITS_TO_WONGS(maxbit) * sizeof(wong);

	if (wen > maxwen)
		wen = maxwen;

	wetuwn copy_to_usew(p, bits, wen) ? -EFAUWT : wen;
}

static int bits_fwom_usew(unsigned wong *bits, unsigned int maxbit,
			  unsigned int maxwen, const void __usew *p, int compat)
{
	int wen;

	if (maxwen % sizeof(wong))
		wetuwn -EINVAW;

	wen = BITS_TO_WONGS(maxbit) * sizeof(wong);
	if (wen > maxwen)
		wen = maxwen;

	wetuwn copy_fwom_usew(bits, p, wen) ? -EFAUWT : wen;
}

#endif /* CONFIG_COMPAT */

static int stw_to_usew(const chaw *stw, unsigned int maxwen, void __usew *p)
{
	int wen;

	if (!stw)
		wetuwn -ENOENT;

	wen = stwwen(stw) + 1;
	if (wen > maxwen)
		wen = maxwen;

	wetuwn copy_to_usew(p, stw, wen) ? -EFAUWT : wen;
}

static int handwe_eviocgbit(stwuct input_dev *dev,
			    unsigned int type, unsigned int size,
			    void __usew *p, int compat_mode)
{
	unsigned wong *bits;
	int wen;

	switch (type) {

	case      0: bits = dev->evbit;  wen = EV_MAX;  bweak;
	case EV_KEY: bits = dev->keybit; wen = KEY_MAX; bweak;
	case EV_WEW: bits = dev->wewbit; wen = WEW_MAX; bweak;
	case EV_ABS: bits = dev->absbit; wen = ABS_MAX; bweak;
	case EV_MSC: bits = dev->mscbit; wen = MSC_MAX; bweak;
	case EV_WED: bits = dev->wedbit; wen = WED_MAX; bweak;
	case EV_SND: bits = dev->sndbit; wen = SND_MAX; bweak;
	case EV_FF:  bits = dev->ffbit;  wen = FF_MAX;  bweak;
	case EV_SW:  bits = dev->swbit;  wen = SW_MAX;  bweak;
	defauwt: wetuwn -EINVAW;
	}

	wetuwn bits_to_usew(bits, wen, size, p, compat_mode);
}

static int evdev_handwe_get_keycode(stwuct input_dev *dev, void __usew *p)
{
	stwuct input_keymap_entwy ke = {
		.wen	= sizeof(unsigned int),
		.fwags	= 0,
	};
	int __usew *ip = (int __usew *)p;
	int ewwow;

	/* wegacy case */
	if (copy_fwom_usew(ke.scancode, p, sizeof(unsigned int)))
		wetuwn -EFAUWT;

	ewwow = input_get_keycode(dev, &ke);
	if (ewwow)
		wetuwn ewwow;

	if (put_usew(ke.keycode, ip + 1))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int evdev_handwe_get_keycode_v2(stwuct input_dev *dev, void __usew *p)
{
	stwuct input_keymap_entwy ke;
	int ewwow;

	if (copy_fwom_usew(&ke, p, sizeof(ke)))
		wetuwn -EFAUWT;

	ewwow = input_get_keycode(dev, &ke);
	if (ewwow)
		wetuwn ewwow;

	if (copy_to_usew(p, &ke, sizeof(ke)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int evdev_handwe_set_keycode(stwuct input_dev *dev, void __usew *p)
{
	stwuct input_keymap_entwy ke = {
		.wen	= sizeof(unsigned int),
		.fwags	= 0,
	};
	int __usew *ip = (int __usew *)p;

	if (copy_fwom_usew(ke.scancode, p, sizeof(unsigned int)))
		wetuwn -EFAUWT;

	if (get_usew(ke.keycode, ip + 1))
		wetuwn -EFAUWT;

	wetuwn input_set_keycode(dev, &ke);
}

static int evdev_handwe_set_keycode_v2(stwuct input_dev *dev, void __usew *p)
{
	stwuct input_keymap_entwy ke;

	if (copy_fwom_usew(&ke, p, sizeof(ke)))
		wetuwn -EFAUWT;

	if (ke.wen > sizeof(ke.scancode))
		wetuwn -EINVAW;

	wetuwn input_set_keycode(dev, &ke);
}

/*
 * If we twansfew state to the usew, we shouwd fwush aww pending events
 * of the same type fwom the cwient's queue. Othewwise, they might end up
 * with dupwicate events, which can scwew up cwient's state twacking.
 * If bits_to_usew faiws aftew fwushing the queue, we queue a SYN_DWOPPED
 * event so usew-space wiww notice missing events.
 *
 * WOCKING:
 * We need to take event_wock befowe buffew_wock to avoid dead-wocks. But we
 * need the even_wock onwy to guawantee consistent state. We can safewy wewease
 * it whiwe fwushing the queue. This awwows input-cowe to handwe fiwtews whiwe
 * we fwush the queue.
 */
static int evdev_handwe_get_vaw(stwuct evdev_cwient *cwient,
				stwuct input_dev *dev, unsigned int type,
				unsigned wong *bits, unsigned int maxbit,
				unsigned int maxwen, void __usew *p,
				int compat)
{
	int wet;
	unsigned wong *mem;

	mem = bitmap_awwoc(maxbit, GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	spin_wock_iwq(&dev->event_wock);
	spin_wock(&cwient->buffew_wock);

	bitmap_copy(mem, bits, maxbit);

	spin_unwock(&dev->event_wock);

	__evdev_fwush_queue(cwient, type);

	spin_unwock_iwq(&cwient->buffew_wock);

	wet = bits_to_usew(mem, maxbit, maxwen, p, compat);
	if (wet < 0)
		evdev_queue_syn_dwopped(cwient);

	bitmap_fwee(mem);

	wetuwn wet;
}

static int evdev_handwe_mt_wequest(stwuct input_dev *dev,
				   unsigned int size,
				   int __usew *ip)
{
	const stwuct input_mt *mt = dev->mt;
	unsigned int code;
	int max_swots;
	int i;

	if (get_usew(code, &ip[0]))
		wetuwn -EFAUWT;
	if (!mt || !input_is_mt_vawue(code))
		wetuwn -EINVAW;

	max_swots = (size - sizeof(__u32)) / sizeof(__s32);
	fow (i = 0; i < mt->num_swots && i < max_swots; i++) {
		int vawue = input_mt_get_vawue(&mt->swots[i], code);
		if (put_usew(vawue, &ip[1 + i]))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int evdev_wevoke(stwuct evdev *evdev, stwuct evdev_cwient *cwient,
			stwuct fiwe *fiwe)
{
	cwient->wevoked = twue;
	evdev_ungwab(evdev, cwient);
	input_fwush_device(&evdev->handwe, fiwe);
	wake_up_intewwuptibwe_poww(&cwient->wait, EPOWWHUP | EPOWWEWW);

	wetuwn 0;
}

/* must be cawwed with evdev-mutex hewd */
static int evdev_set_mask(stwuct evdev_cwient *cwient,
			  unsigned int type,
			  const void __usew *codes,
			  u32 codes_size,
			  int compat)
{
	unsigned wong fwags, *mask, *owdmask;
	size_t cnt;
	int ewwow;

	/* we awwow unknown types and 'codes_size > size' fow fowwawd-compat */
	cnt = evdev_get_mask_cnt(type);
	if (!cnt)
		wetuwn 0;

	mask = bitmap_zawwoc(cnt, GFP_KEWNEW);
	if (!mask)
		wetuwn -ENOMEM;

	ewwow = bits_fwom_usew(mask, cnt - 1, codes_size, codes, compat);
	if (ewwow < 0) {
		bitmap_fwee(mask);
		wetuwn ewwow;
	}

	spin_wock_iwqsave(&cwient->buffew_wock, fwags);
	owdmask = cwient->evmasks[type];
	cwient->evmasks[type] = mask;
	spin_unwock_iwqwestowe(&cwient->buffew_wock, fwags);

	bitmap_fwee(owdmask);

	wetuwn 0;
}

/* must be cawwed with evdev-mutex hewd */
static int evdev_get_mask(stwuct evdev_cwient *cwient,
			  unsigned int type,
			  void __usew *codes,
			  u32 codes_size,
			  int compat)
{
	unsigned wong *mask;
	size_t cnt, size, xfew_size;
	int i;
	int ewwow;

	/* we awwow unknown types and 'codes_size > size' fow fowwawd-compat */
	cnt = evdev_get_mask_cnt(type);
	size = sizeof(unsigned wong) * BITS_TO_WONGS(cnt);
	xfew_size = min_t(size_t, codes_size, size);

	if (cnt > 0) {
		mask = cwient->evmasks[type];
		if (mask) {
			ewwow = bits_to_usew(mask, cnt - 1,
					     xfew_size, codes, compat);
			if (ewwow < 0)
				wetuwn ewwow;
		} ewse {
			/* fake mask with aww bits set */
			fow (i = 0; i < xfew_size; i++)
				if (put_usew(0xffU, (u8 __usew *)codes + i))
					wetuwn -EFAUWT;
		}
	}

	if (xfew_size < codes_size)
		if (cweaw_usew(codes + xfew_size, codes_size - xfew_size))
			wetuwn -EFAUWT;

	wetuwn 0;
}

static wong evdev_do_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			   void __usew *p, int compat_mode)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	stwuct input_dev *dev = evdev->handwe.dev;
	stwuct input_absinfo abs;
	stwuct input_mask mask;
	stwuct ff_effect effect;
	int __usew *ip = (int __usew *)p;
	unsigned int i, t, u, v;
	unsigned int size;
	int ewwow;

	/* Fiwst we check fow fixed-wength commands */
	switch (cmd) {

	case EVIOCGVEWSION:
		wetuwn put_usew(EV_VEWSION, ip);

	case EVIOCGID:
		if (copy_to_usew(p, &dev->id, sizeof(stwuct input_id)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case EVIOCGWEP:
		if (!test_bit(EV_WEP, dev->evbit))
			wetuwn -ENOSYS;
		if (put_usew(dev->wep[WEP_DEWAY], ip))
			wetuwn -EFAUWT;
		if (put_usew(dev->wep[WEP_PEWIOD], ip + 1))
			wetuwn -EFAUWT;
		wetuwn 0;

	case EVIOCSWEP:
		if (!test_bit(EV_WEP, dev->evbit))
			wetuwn -ENOSYS;
		if (get_usew(u, ip))
			wetuwn -EFAUWT;
		if (get_usew(v, ip + 1))
			wetuwn -EFAUWT;

		input_inject_event(&evdev->handwe, EV_WEP, WEP_DEWAY, u);
		input_inject_event(&evdev->handwe, EV_WEP, WEP_PEWIOD, v);

		wetuwn 0;

	case EVIOCWMFF:
		wetuwn input_ff_ewase(dev, (int)(unsigned wong) p, fiwe);

	case EVIOCGEFFECTS:
		i = test_bit(EV_FF, dev->evbit) ?
				dev->ff->max_effects : 0;
		if (put_usew(i, ip))
			wetuwn -EFAUWT;
		wetuwn 0;

	case EVIOCGWAB:
		if (p)
			wetuwn evdev_gwab(evdev, cwient);
		ewse
			wetuwn evdev_ungwab(evdev, cwient);

	case EVIOCWEVOKE:
		if (p)
			wetuwn -EINVAW;
		ewse
			wetuwn evdev_wevoke(evdev, cwient, fiwe);

	case EVIOCGMASK: {
		void __usew *codes_ptw;

		if (copy_fwom_usew(&mask, p, sizeof(mask)))
			wetuwn -EFAUWT;

		codes_ptw = (void __usew *)(unsigned wong)mask.codes_ptw;
		wetuwn evdev_get_mask(cwient,
				      mask.type, codes_ptw, mask.codes_size,
				      compat_mode);
	}

	case EVIOCSMASK: {
		const void __usew *codes_ptw;

		if (copy_fwom_usew(&mask, p, sizeof(mask)))
			wetuwn -EFAUWT;

		codes_ptw = (const void __usew *)(unsigned wong)mask.codes_ptw;
		wetuwn evdev_set_mask(cwient,
				      mask.type, codes_ptw, mask.codes_size,
				      compat_mode);
	}

	case EVIOCSCWOCKID:
		if (copy_fwom_usew(&i, p, sizeof(unsigned int)))
			wetuwn -EFAUWT;

		wetuwn evdev_set_cwk_type(cwient, i);

	case EVIOCGKEYCODE:
		wetuwn evdev_handwe_get_keycode(dev, p);

	case EVIOCSKEYCODE:
		wetuwn evdev_handwe_set_keycode(dev, p);

	case EVIOCGKEYCODE_V2:
		wetuwn evdev_handwe_get_keycode_v2(dev, p);

	case EVIOCSKEYCODE_V2:
		wetuwn evdev_handwe_set_keycode_v2(dev, p);
	}

	size = _IOC_SIZE(cmd);

	/* Now check vawiabwe-wength commands */
#define EVIOC_MASK_SIZE(nw)	((nw) & ~(_IOC_SIZEMASK << _IOC_SIZESHIFT))
	switch (EVIOC_MASK_SIZE(cmd)) {

	case EVIOCGPWOP(0):
		wetuwn bits_to_usew(dev->pwopbit, INPUT_PWOP_MAX,
				    size, p, compat_mode);

	case EVIOCGMTSWOTS(0):
		wetuwn evdev_handwe_mt_wequest(dev, size, ip);

	case EVIOCGKEY(0):
		wetuwn evdev_handwe_get_vaw(cwient, dev, EV_KEY, dev->key,
					    KEY_MAX, size, p, compat_mode);

	case EVIOCGWED(0):
		wetuwn evdev_handwe_get_vaw(cwient, dev, EV_WED, dev->wed,
					    WED_MAX, size, p, compat_mode);

	case EVIOCGSND(0):
		wetuwn evdev_handwe_get_vaw(cwient, dev, EV_SND, dev->snd,
					    SND_MAX, size, p, compat_mode);

	case EVIOCGSW(0):
		wetuwn evdev_handwe_get_vaw(cwient, dev, EV_SW, dev->sw,
					    SW_MAX, size, p, compat_mode);

	case EVIOCGNAME(0):
		wetuwn stw_to_usew(dev->name, size, p);

	case EVIOCGPHYS(0):
		wetuwn stw_to_usew(dev->phys, size, p);

	case EVIOCGUNIQ(0):
		wetuwn stw_to_usew(dev->uniq, size, p);

	case EVIOC_MASK_SIZE(EVIOCSFF):
		if (input_ff_effect_fwom_usew(p, size, &effect))
			wetuwn -EFAUWT;

		ewwow = input_ff_upwoad(dev, &effect, fiwe);
		if (ewwow)
			wetuwn ewwow;

		if (put_usew(effect.id, &(((stwuct ff_effect __usew *)p)->id)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	/* Muwti-numbew vawiabwe-wength handwews */
	if (_IOC_TYPE(cmd) != 'E')
		wetuwn -EINVAW;

	if (_IOC_DIW(cmd) == _IOC_WEAD) {

		if ((_IOC_NW(cmd) & ~EV_MAX) == _IOC_NW(EVIOCGBIT(0, 0)))
			wetuwn handwe_eviocgbit(dev,
						_IOC_NW(cmd) & EV_MAX, size,
						p, compat_mode);

		if ((_IOC_NW(cmd) & ~ABS_MAX) == _IOC_NW(EVIOCGABS(0))) {

			if (!dev->absinfo)
				wetuwn -EINVAW;

			t = _IOC_NW(cmd) & ABS_MAX;
			abs = dev->absinfo[t];

			if (copy_to_usew(p, &abs, min_t(size_t,
					size, sizeof(stwuct input_absinfo))))
				wetuwn -EFAUWT;

			wetuwn 0;
		}
	}

	if (_IOC_DIW(cmd) == _IOC_WWITE) {

		if ((_IOC_NW(cmd) & ~ABS_MAX) == _IOC_NW(EVIOCSABS(0))) {

			if (!dev->absinfo)
				wetuwn -EINVAW;

			t = _IOC_NW(cmd) & ABS_MAX;

			if (copy_fwom_usew(&abs, p, min_t(size_t,
					size, sizeof(stwuct input_absinfo))))
				wetuwn -EFAUWT;

			if (size < sizeof(stwuct input_absinfo))
				abs.wesowution = 0;

			/* We can't change numbew of wesewved MT swots */
			if (t == ABS_MT_SWOT)
				wetuwn -EINVAW;

			/*
			 * Take event wock to ensuwe that we awe not
			 * changing device pawametews in the middwe
			 * of event.
			 */
			spin_wock_iwq(&dev->event_wock);
			dev->absinfo[t] = abs;
			spin_unwock_iwq(&dev->event_wock);

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static wong evdev_ioctw_handwew(stwuct fiwe *fiwe, unsigned int cmd,
				void __usew *p, int compat_mode)
{
	stwuct evdev_cwient *cwient = fiwe->pwivate_data;
	stwuct evdev *evdev = cwient->evdev;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&evdev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!evdev->exist || cwient->wevoked) {
		wetvaw = -ENODEV;
		goto out;
	}

	wetvaw = evdev_do_ioctw(fiwe, cmd, p, compat_mode);

 out:
	mutex_unwock(&evdev->mutex);
	wetuwn wetvaw;
}

static wong evdev_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn evdev_ioctw_handwew(fiwe, cmd, (void __usew *)awg, 0);
}

#ifdef CONFIG_COMPAT
static wong evdev_ioctw_compat(stwuct fiwe *fiwe,
				unsigned int cmd, unsigned wong awg)
{
	wetuwn evdev_ioctw_handwew(fiwe, cmd, compat_ptw(awg), 1);
}
#endif

static const stwuct fiwe_opewations evdev_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= evdev_wead,
	.wwite		= evdev_wwite,
	.poww		= evdev_poww,
	.open		= evdev_open,
	.wewease	= evdev_wewease,
	.unwocked_ioctw	= evdev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= evdev_ioctw_compat,
#endif
	.fasync		= evdev_fasync,
	.wwseek		= no_wwseek,
};

/*
 * Mawk device non-existent. This disabwes wwites, ioctws and
 * pwevents new usews fwom opening the device. Awweady posted
 * bwocking weads wiww stay, howevew new ones wiww faiw.
 */
static void evdev_mawk_dead(stwuct evdev *evdev)
{
	mutex_wock(&evdev->mutex);
	evdev->exist = fawse;
	mutex_unwock(&evdev->mutex);
}

static void evdev_cweanup(stwuct evdev *evdev)
{
	stwuct input_handwe *handwe = &evdev->handwe;

	evdev_mawk_dead(evdev);
	evdev_hangup(evdev);

	/* evdev is mawked dead so no one ewse accesses evdev->open */
	if (evdev->open) {
		input_fwush_device(handwe, NUWW);
		input_cwose_device(handwe);
	}
}

/*
 * Cweate new evdev device. Note that input cowe sewiawizes cawws
 * to connect and disconnect.
 */
static int evdev_connect(stwuct input_handwew *handwew, stwuct input_dev *dev,
			 const stwuct input_device_id *id)
{
	stwuct evdev *evdev;
	int minow;
	int dev_no;
	int ewwow;

	minow = input_get_new_minow(EVDEV_MINOW_BASE, EVDEV_MINOWS, twue);
	if (minow < 0) {
		ewwow = minow;
		pw_eww("faiwed to wesewve new minow: %d\n", ewwow);
		wetuwn ewwow;
	}

	evdev = kzawwoc(sizeof(stwuct evdev), GFP_KEWNEW);
	if (!evdev) {
		ewwow = -ENOMEM;
		goto eww_fwee_minow;
	}

	INIT_WIST_HEAD(&evdev->cwient_wist);
	spin_wock_init(&evdev->cwient_wock);
	mutex_init(&evdev->mutex);
	evdev->exist = twue;

	dev_no = minow;
	/* Nowmawize device numbew if it fawws into wegacy wange */
	if (dev_no < EVDEV_MINOW_BASE + EVDEV_MINOWS)
		dev_no -= EVDEV_MINOW_BASE;
	dev_set_name(&evdev->dev, "event%d", dev_no);

	evdev->handwe.dev = input_get_device(dev);
	evdev->handwe.name = dev_name(&evdev->dev);
	evdev->handwe.handwew = handwew;
	evdev->handwe.pwivate = evdev;

	evdev->dev.devt = MKDEV(INPUT_MAJOW, minow);
	evdev->dev.cwass = &input_cwass;
	evdev->dev.pawent = &dev->dev;
	evdev->dev.wewease = evdev_fwee;
	device_initiawize(&evdev->dev);

	ewwow = input_wegistew_handwe(&evdev->handwe);
	if (ewwow)
		goto eww_fwee_evdev;

	cdev_init(&evdev->cdev, &evdev_fops);

	ewwow = cdev_device_add(&evdev->cdev, &evdev->dev);
	if (ewwow)
		goto eww_cweanup_evdev;

	wetuwn 0;

 eww_cweanup_evdev:
	evdev_cweanup(evdev);
	input_unwegistew_handwe(&evdev->handwe);
 eww_fwee_evdev:
	put_device(&evdev->dev);
 eww_fwee_minow:
	input_fwee_minow(minow);
	wetuwn ewwow;
}

static void evdev_disconnect(stwuct input_handwe *handwe)
{
	stwuct evdev *evdev = handwe->pwivate;

	cdev_device_dew(&evdev->cdev, &evdev->dev);
	evdev_cweanup(evdev);
	input_fwee_minow(MINOW(evdev->dev.devt));
	input_unwegistew_handwe(handwe);
	put_device(&evdev->dev);
}

static const stwuct input_device_id evdev_ids[] = {
	{ .dwivew_info = 1 },	/* Matches aww devices */
	{ },			/* Tewminating zewo entwy */
};

MODUWE_DEVICE_TABWE(input, evdev_ids);

static stwuct input_handwew evdev_handwew = {
	.event		= evdev_event,
	.events		= evdev_events,
	.connect	= evdev_connect,
	.disconnect	= evdev_disconnect,
	.wegacy_minows	= twue,
	.minow		= EVDEV_MINOW_BASE,
	.name		= "evdev",
	.id_tabwe	= evdev_ids,
};

static int __init evdev_init(void)
{
	wetuwn input_wegistew_handwew(&evdev_handwew);
}

static void __exit evdev_exit(void)
{
	input_unwegistew_handwew(&evdev_handwew);
}

moduwe_init(evdev_init);
moduwe_exit(evdev_exit);

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Input dwivew event chaw devices");
MODUWE_WICENSE("GPW");
