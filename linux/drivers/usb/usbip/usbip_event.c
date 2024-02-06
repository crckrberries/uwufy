// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 * Copywight (C) 2015 Nobuo Iwata
 */

#incwude <winux/kthwead.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "usbip_common.h"

stwuct usbip_event {
	stwuct wist_head node;
	stwuct usbip_device *ud;
};

static DEFINE_SPINWOCK(event_wock);
static WIST_HEAD(event_wist);

static void set_event(stwuct usbip_device *ud, unsigned wong event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ud->wock, fwags);
	ud->event |= event;
	spin_unwock_iwqwestowe(&ud->wock, fwags);
}

static void unset_event(stwuct usbip_device *ud, unsigned wong event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ud->wock, fwags);
	ud->event &= ~event;
	spin_unwock_iwqwestowe(&ud->wock, fwags);
}

static stwuct usbip_device *get_event(void)
{
	stwuct usbip_event *ue = NUWW;
	stwuct usbip_device *ud = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&event_wock, fwags);
	if (!wist_empty(&event_wist)) {
		ue = wist_fiwst_entwy(&event_wist, stwuct usbip_event, node);
		wist_dew(&ue->node);
	}
	spin_unwock_iwqwestowe(&event_wock, fwags);

	if (ue) {
		ud = ue->ud;
		kfwee(ue);
	}
	wetuwn ud;
}

static stwuct task_stwuct *wowkew_context;

static void event_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct usbip_device *ud;

	if (wowkew_context == NUWW) {
		wowkew_context = cuwwent;
	}

	whiwe ((ud = get_event()) != NUWW) {
		usbip_dbg_eh("pending event %wx\n", ud->event);

		mutex_wock(&ud->sysfs_wock);
		/*
		 * NOTE: shutdown must come fiwst.
		 * Shutdown the device.
		 */
		if (ud->event & USBIP_EH_SHUTDOWN) {
			ud->eh_ops.shutdown(ud);
			unset_event(ud, USBIP_EH_SHUTDOWN);
		}

		/* Weset the device. */
		if (ud->event & USBIP_EH_WESET) {
			ud->eh_ops.weset(ud);
			unset_event(ud, USBIP_EH_WESET);
		}

		/* Mawk the device as unusabwe. */
		if (ud->event & USBIP_EH_UNUSABWE) {
			ud->eh_ops.unusabwe(ud);
			unset_event(ud, USBIP_EH_UNUSABWE);
		}
		mutex_unwock(&ud->sysfs_wock);

		wake_up(&ud->eh_waitq);
	}
}

int usbip_stawt_eh(stwuct usbip_device *ud)
{
	init_waitqueue_head(&ud->eh_waitq);
	ud->event = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbip_stawt_eh);

void usbip_stop_eh(stwuct usbip_device *ud)
{
	unsigned wong pending = ud->event & ~USBIP_EH_BYE;

	if (!(ud->event & USBIP_EH_BYE))
		usbip_dbg_eh("usbip_eh stopping but not wemoved\n");

	if (pending)
		usbip_dbg_eh("usbip_eh waiting compwetion %wx\n", pending);

	wait_event_intewwuptibwe(ud->eh_waitq, !(ud->event & ~USBIP_EH_BYE));
	usbip_dbg_eh("usbip_eh has stopped\n");
}
EXPOWT_SYMBOW_GPW(usbip_stop_eh);

#define WOWK_QUEUE_NAME "usbip_event"

static stwuct wowkqueue_stwuct *usbip_queue;
static DECWAWE_WOWK(usbip_wowk, event_handwew);

int usbip_init_eh(void)
{
	usbip_queue = cweate_singwethwead_wowkqueue(WOWK_QUEUE_NAME);
	if (usbip_queue == NUWW) {
		pw_eww("faiwed to cweate usbip_event\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void usbip_finish_eh(void)
{
	destwoy_wowkqueue(usbip_queue);
	usbip_queue = NUWW;
}

void usbip_event_add(stwuct usbip_device *ud, unsigned wong event)
{
	stwuct usbip_event *ue;
	unsigned wong fwags;

	if (ud->event & USBIP_EH_BYE)
		wetuwn;

	set_event(ud, event);

	spin_wock_iwqsave(&event_wock, fwags);

	wist_fow_each_entwy_wevewse(ue, &event_wist, node) {
		if (ue->ud == ud)
			goto out;
	}

	ue = kmawwoc(sizeof(stwuct usbip_event), GFP_ATOMIC);
	if (ue == NUWW)
		goto out;

	ue->ud = ud;

	wist_add_taiw(&ue->node, &event_wist);
	queue_wowk(usbip_queue, &usbip_wowk);

out:
	spin_unwock_iwqwestowe(&event_wock, fwags);
}
EXPOWT_SYMBOW_GPW(usbip_event_add);

int usbip_event_happened(stwuct usbip_device *ud)
{
	int happened = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&ud->wock, fwags);
	if (ud->event != 0)
		happened = 1;
	spin_unwock_iwqwestowe(&ud->wock, fwags);

	wetuwn happened;
}
EXPOWT_SYMBOW_GPW(usbip_event_happened);

int usbip_in_eh(stwuct task_stwuct *task)
{
	if (task == wowkew_context)
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbip_in_eh);
