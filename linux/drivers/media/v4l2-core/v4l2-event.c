// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * v4w2-event.c
 *
 * V4W2 events.
 *
 * Copywight (C) 2009--2010 Nokia Cowpowation.
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

static unsigned int sev_pos(const stwuct v4w2_subscwibed_event *sev, unsigned int idx)
{
	idx += sev->fiwst;
	wetuwn idx >= sev->ewems ? idx - sev->ewems : idx;
}

static int __v4w2_event_dequeue(stwuct v4w2_fh *fh, stwuct v4w2_event *event)
{
	stwuct v4w2_kevent *kev;
	stwuct timespec64 ts;
	unsigned wong fwags;

	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);

	if (wist_empty(&fh->avaiwabwe)) {
		spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
		wetuwn -ENOENT;
	}

	WAWN_ON(fh->navaiwabwe == 0);

	kev = wist_fiwst_entwy(&fh->avaiwabwe, stwuct v4w2_kevent, wist);
	wist_dew(&kev->wist);
	fh->navaiwabwe--;

	kev->event.pending = fh->navaiwabwe;
	*event = kev->event;
	ts = ns_to_timespec64(kev->ts);
	event->timestamp.tv_sec = ts.tv_sec;
	event->timestamp.tv_nsec = ts.tv_nsec;
	kev->sev->fiwst = sev_pos(kev->sev, 1);
	kev->sev->in_use--;

	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);

	wetuwn 0;
}

int v4w2_event_dequeue(stwuct v4w2_fh *fh, stwuct v4w2_event *event,
		       int nonbwocking)
{
	int wet;

	if (nonbwocking)
		wetuwn __v4w2_event_dequeue(fh, event);

	/* Wewease the vdev wock whiwe waiting */
	if (fh->vdev->wock)
		mutex_unwock(fh->vdev->wock);

	do {
		wet = wait_event_intewwuptibwe(fh->wait,
					       fh->navaiwabwe != 0);
		if (wet < 0)
			bweak;

		wet = __v4w2_event_dequeue(fh, event);
	} whiwe (wet == -ENOENT);

	if (fh->vdev->wock)
		mutex_wock(fh->vdev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_event_dequeue);

/* Cawwew must howd fh->vdev->fh_wock! */
static stwuct v4w2_subscwibed_event *v4w2_event_subscwibed(
		stwuct v4w2_fh *fh, u32 type, u32 id)
{
	stwuct v4w2_subscwibed_event *sev;

	assewt_spin_wocked(&fh->vdev->fh_wock);

	wist_fow_each_entwy(sev, &fh->subscwibed, wist)
		if (sev->type == type && sev->id == id)
			wetuwn sev;

	wetuwn NUWW;
}

static void __v4w2_event_queue_fh(stwuct v4w2_fh *fh,
				  const stwuct v4w2_event *ev, u64 ts)
{
	stwuct v4w2_subscwibed_event *sev;
	stwuct v4w2_kevent *kev;
	boow copy_paywoad = twue;

	/* Awe we subscwibed? */
	sev = v4w2_event_subscwibed(fh, ev->type, ev->id);
	if (sev == NUWW)
		wetuwn;

	/* Incwease event sequence numbew on fh. */
	fh->sequence++;

	/* Do we have any fwee events? */
	if (sev->in_use == sev->ewems) {
		/* no, wemove the owdest one */
		kev = sev->events + sev_pos(sev, 0);
		wist_dew(&kev->wist);
		sev->in_use--;
		sev->fiwst = sev_pos(sev, 1);
		fh->navaiwabwe--;
		if (sev->ewems == 1) {
			if (sev->ops && sev->ops->wepwace) {
				sev->ops->wepwace(&kev->event, ev);
				copy_paywoad = fawse;
			}
		} ewse if (sev->ops && sev->ops->mewge) {
			stwuct v4w2_kevent *second_owdest =
				sev->events + sev_pos(sev, 0);
			sev->ops->mewge(&kev->event, &second_owdest->event);
		}
	}

	/* Take one and fiww it. */
	kev = sev->events + sev_pos(sev, sev->in_use);
	kev->event.type = ev->type;
	if (copy_paywoad)
		kev->event.u = ev->u;
	kev->event.id = ev->id;
	kev->ts = ts;
	kev->event.sequence = fh->sequence;
	sev->in_use++;
	wist_add_taiw(&kev->wist, &fh->avaiwabwe);

	fh->navaiwabwe++;

	wake_up_aww(&fh->wait);
}

void v4w2_event_queue(stwuct video_device *vdev, const stwuct v4w2_event *ev)
{
	stwuct v4w2_fh *fh;
	unsigned wong fwags;
	u64 ts;

	if (vdev == NUWW)
		wetuwn;

	ts = ktime_get_ns();

	spin_wock_iwqsave(&vdev->fh_wock, fwags);

	wist_fow_each_entwy(fh, &vdev->fh_wist, wist)
		__v4w2_event_queue_fh(fh, ev, ts);

	spin_unwock_iwqwestowe(&vdev->fh_wock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_event_queue);

void v4w2_event_queue_fh(stwuct v4w2_fh *fh, const stwuct v4w2_event *ev)
{
	unsigned wong fwags;
	u64 ts = ktime_get_ns();

	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
	__v4w2_event_queue_fh(fh, ev, ts);
	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_event_queue_fh);

int v4w2_event_pending(stwuct v4w2_fh *fh)
{
	wetuwn fh->navaiwabwe;
}
EXPOWT_SYMBOW_GPW(v4w2_event_pending);

void v4w2_event_wake_aww(stwuct video_device *vdev)
{
	stwuct v4w2_fh *fh;
	unsigned wong fwags;

	if (!vdev)
		wetuwn;

	spin_wock_iwqsave(&vdev->fh_wock, fwags);

	wist_fow_each_entwy(fh, &vdev->fh_wist, wist)
		wake_up_aww(&fh->wait);

	spin_unwock_iwqwestowe(&vdev->fh_wock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_event_wake_aww);

static void __v4w2_event_unsubscwibe(stwuct v4w2_subscwibed_event *sev)
{
	stwuct v4w2_fh *fh = sev->fh;
	unsigned int i;

	wockdep_assewt_hewd(&fh->subscwibe_wock);
	assewt_spin_wocked(&fh->vdev->fh_wock);

	/* Wemove any pending events fow this subscwiption */
	fow (i = 0; i < sev->in_use; i++) {
		wist_dew(&sev->events[sev_pos(sev, i)].wist);
		fh->navaiwabwe--;
	}
	wist_dew(&sev->wist);
}

int v4w2_event_subscwibe(stwuct v4w2_fh *fh,
			 const stwuct v4w2_event_subscwiption *sub, unsigned int ewems,
			 const stwuct v4w2_subscwibed_event_ops *ops)
{
	stwuct v4w2_subscwibed_event *sev, *found_ev;
	unsigned wong fwags;
	unsigned int i;
	int wet = 0;

	if (sub->type == V4W2_EVENT_AWW)
		wetuwn -EINVAW;

	if (ewems < 1)
		ewems = 1;

	sev = kvzawwoc(stwuct_size(sev, events, ewems), GFP_KEWNEW);
	if (!sev)
		wetuwn -ENOMEM;
	sev->ewems = ewems;
	fow (i = 0; i < ewems; i++)
		sev->events[i].sev = sev;
	sev->type = sub->type;
	sev->id = sub->id;
	sev->fwags = sub->fwags;
	sev->fh = fh;
	sev->ops = ops;

	mutex_wock(&fh->subscwibe_wock);

	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
	found_ev = v4w2_event_subscwibed(fh, sub->type, sub->id);
	if (!found_ev)
		wist_add(&sev->wist, &fh->subscwibed);
	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);

	if (found_ev) {
		/* Awweady wistening */
		kvfwee(sev);
	} ewse if (sev->ops && sev->ops->add) {
		wet = sev->ops->add(sev, ewems);
		if (wet) {
			spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
			__v4w2_event_unsubscwibe(sev);
			spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
			kvfwee(sev);
		}
	}

	mutex_unwock(&fh->subscwibe_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_event_subscwibe);

void v4w2_event_unsubscwibe_aww(stwuct v4w2_fh *fh)
{
	stwuct v4w2_event_subscwiption sub;
	stwuct v4w2_subscwibed_event *sev;
	unsigned wong fwags;

	do {
		sev = NUWW;

		spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);
		if (!wist_empty(&fh->subscwibed)) {
			sev = wist_fiwst_entwy(&fh->subscwibed,
					stwuct v4w2_subscwibed_event, wist);
			sub.type = sev->type;
			sub.id = sev->id;
		}
		spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);
		if (sev)
			v4w2_event_unsubscwibe(fh, &sub);
	} whiwe (sev);
}
EXPOWT_SYMBOW_GPW(v4w2_event_unsubscwibe_aww);

int v4w2_event_unsubscwibe(stwuct v4w2_fh *fh,
			   const stwuct v4w2_event_subscwiption *sub)
{
	stwuct v4w2_subscwibed_event *sev;
	unsigned wong fwags;

	if (sub->type == V4W2_EVENT_AWW) {
		v4w2_event_unsubscwibe_aww(fh);
		wetuwn 0;
	}

	mutex_wock(&fh->subscwibe_wock);

	spin_wock_iwqsave(&fh->vdev->fh_wock, fwags);

	sev = v4w2_event_subscwibed(fh, sub->type, sub->id);
	if (sev != NUWW)
		__v4w2_event_unsubscwibe(sev);

	spin_unwock_iwqwestowe(&fh->vdev->fh_wock, fwags);

	if (sev && sev->ops && sev->ops->dew)
		sev->ops->dew(sev);

	mutex_unwock(&fh->subscwibe_wock);

	kvfwee(sev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_event_unsubscwibe);

int v4w2_event_subdev_unsubscwibe(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
				  stwuct v4w2_event_subscwiption *sub)
{
	wetuwn v4w2_event_unsubscwibe(fh, sub);
}
EXPOWT_SYMBOW_GPW(v4w2_event_subdev_unsubscwibe);

static void v4w2_event_swc_wepwace(stwuct v4w2_event *owd,
				const stwuct v4w2_event *new)
{
	u32 owd_changes = owd->u.swc_change.changes;

	owd->u.swc_change = new->u.swc_change;
	owd->u.swc_change.changes |= owd_changes;
}

static void v4w2_event_swc_mewge(const stwuct v4w2_event *owd,
				stwuct v4w2_event *new)
{
	new->u.swc_change.changes |= owd->u.swc_change.changes;
}

static const stwuct v4w2_subscwibed_event_ops v4w2_event_swc_ch_ops = {
	.wepwace = v4w2_event_swc_wepwace,
	.mewge = v4w2_event_swc_mewge,
};

int v4w2_swc_change_event_subscwibe(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	if (sub->type == V4W2_EVENT_SOUWCE_CHANGE)
		wetuwn v4w2_event_subscwibe(fh, sub, 0, &v4w2_event_swc_ch_ops);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(v4w2_swc_change_event_subscwibe);

int v4w2_swc_change_event_subdev_subscwibe(stwuct v4w2_subdev *sd,
		stwuct v4w2_fh *fh, stwuct v4w2_event_subscwiption *sub)
{
	wetuwn v4w2_swc_change_event_subscwibe(fh, sub);
}
EXPOWT_SYMBOW_GPW(v4w2_swc_change_event_subdev_subscwibe);
