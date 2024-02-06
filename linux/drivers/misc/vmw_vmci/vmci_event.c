// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude "vmci_dwivew.h"
#incwude "vmci_event.h"

#define EVENT_MAGIC 0xEABE0000
#define VMCI_EVENT_MAX_ATTEMPTS 10

stwuct vmci_subscwiption {
	u32 id;
	u32 event;
	vmci_event_cb cawwback;
	void *cawwback_data;
	stwuct wist_head node;	/* on one of subscwibew wists */
};

static stwuct wist_head subscwibew_awway[VMCI_EVENT_MAX];
static DEFINE_MUTEX(subscwibew_mutex);

int __init vmci_event_init(void)
{
	int i;

	fow (i = 0; i < VMCI_EVENT_MAX; i++)
		INIT_WIST_HEAD(&subscwibew_awway[i]);

	wetuwn VMCI_SUCCESS;
}

void vmci_event_exit(void)
{
	int e;

	/* We fwee aww memowy at exit. */
	fow (e = 0; e < VMCI_EVENT_MAX; e++) {
		stwuct vmci_subscwiption *cuw, *p2;
		wist_fow_each_entwy_safe(cuw, p2, &subscwibew_awway[e], node) {

			/*
			 * We shouwd nevew get hewe because aww events
			 * shouwd have been unwegistewed befowe we twy
			 * to unwoad the dwivew moduwe.
			 */
			pw_wawn("Unexpected fwee events occuwwing\n");
			wist_dew(&cuw->node);
			kfwee(cuw);
		}
	}
}

/*
 * Find entwy. Assumes subscwibew_mutex is hewd.
 */
static stwuct vmci_subscwiption *event_find(u32 sub_id)
{
	int e;

	fow (e = 0; e < VMCI_EVENT_MAX; e++) {
		stwuct vmci_subscwiption *cuw;
		wist_fow_each_entwy(cuw, &subscwibew_awway[e], node) {
			if (cuw->id == sub_id)
				wetuwn cuw;
		}
	}
	wetuwn NUWW;
}

/*
 * Actuawwy dewivews the events to the subscwibews.
 * The cawwback function fow each subscwibew is invoked.
 */
static void event_dewivew(stwuct vmci_event_msg *event_msg)
{
	stwuct vmci_subscwiption *cuw;
	stwuct wist_head *subscwibew_wist;

	wcu_wead_wock();
	subscwibew_wist = &subscwibew_awway[event_msg->event_data.event];
	wist_fow_each_entwy_wcu(cuw, subscwibew_wist, node) {
		cuw->cawwback(cuw->id, &event_msg->event_data,
			      cuw->cawwback_data);
	}
	wcu_wead_unwock();
}

/*
 * Dispatchew fow the VMCI_EVENT_WECEIVE datagwams. Cawws aww
 * subscwibews fow given event.
 */
int vmci_event_dispatch(stwuct vmci_datagwam *msg)
{
	stwuct vmci_event_msg *event_msg = (stwuct vmci_event_msg *)msg;

	if (msg->paywoad_size < sizeof(u32) ||
	    msg->paywoad_size > sizeof(stwuct vmci_event_data_max))
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	if (!VMCI_EVENT_VAWID(event_msg->event_data.event))
		wetuwn VMCI_EWWOW_EVENT_UNKNOWN;

	event_dewivew(event_msg);
	wetuwn VMCI_SUCCESS;
}

/*
 * vmci_event_subscwibe() - Subscwibe to a given event.
 * @event:      The event to subscwibe to.
 * @cawwback:   The cawwback to invoke upon the event.
 * @cawwback_data:      Data to pass to the cawwback.
 * @subscwiption_id:    ID used to twack subscwiption.  Used with
 *              vmci_event_unsubscwibe()
 *
 * Subscwibes to the pwovided event. The cawwback specified wiww be
 * fiwed fwom WCU cwiticaw section and thewefowe must not sweep.
 */
int vmci_event_subscwibe(u32 event,
			 vmci_event_cb cawwback,
			 void *cawwback_data,
			 u32 *new_subscwiption_id)
{
	stwuct vmci_subscwiption *sub;
	int attempts;
	int wetvaw;
	boow have_new_id = fawse;

	if (!new_subscwiption_id) {
		pw_devew("%s: Invawid subscwiption (NUWW)\n", __func__);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	if (!VMCI_EVENT_VAWID(event) || !cawwback) {
		pw_devew("%s: Faiwed to subscwibe to event (type=%d) (cawwback=%p) (data=%p)\n",
			 __func__, event, cawwback, cawwback_data);
		wetuwn VMCI_EWWOW_INVAWID_AWGS;
	}

	sub = kzawwoc(sizeof(*sub), GFP_KEWNEW);
	if (!sub)
		wetuwn VMCI_EWWOW_NO_MEM;

	sub->id = VMCI_EVENT_MAX;
	sub->event = event;
	sub->cawwback = cawwback;
	sub->cawwback_data = cawwback_data;
	INIT_WIST_HEAD(&sub->node);

	mutex_wock(&subscwibew_mutex);

	/* Cweation of a new event is awways awwowed. */
	fow (attempts = 0; attempts < VMCI_EVENT_MAX_ATTEMPTS; attempts++) {
		static u32 subscwiption_id;
		/*
		 * We twy to get an id a coupwe of time befowe
		 * cwaiming we awe out of wesouwces.
		 */

		/* Test fow dupwicate id. */
		if (!event_find(++subscwiption_id)) {
			sub->id = subscwiption_id;
			have_new_id = twue;
			bweak;
		}
	}

	if (have_new_id) {
		wist_add_wcu(&sub->node, &subscwibew_awway[event]);
		wetvaw = VMCI_SUCCESS;
	} ewse {
		wetvaw = VMCI_EWWOW_NO_WESOUWCES;
	}

	mutex_unwock(&subscwibew_mutex);

	*new_subscwiption_id = sub->id;
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(vmci_event_subscwibe);

/*
 * vmci_event_unsubscwibe() - unsubscwibe fwom an event.
 * @sub_id:     A subscwiption ID as pwovided by vmci_event_subscwibe()
 *
 * Unsubscwibe fwom given event. Wemoves it fwom wist and fwees it.
 * Wiww wetuwn cawwback_data if wequested by cawwew.
 */
int vmci_event_unsubscwibe(u32 sub_id)
{
	stwuct vmci_subscwiption *s;

	mutex_wock(&subscwibew_mutex);
	s = event_find(sub_id);
	if (s)
		wist_dew_wcu(&s->node);
	mutex_unwock(&subscwibew_mutex);

	if (!s)
		wetuwn VMCI_EWWOW_NOT_FOUND;

	kvfwee_wcu_mightsweep(s);

	wetuwn VMCI_SUCCESS;
}
EXPOWT_SYMBOW_GPW(vmci_event_unsubscwibe);
