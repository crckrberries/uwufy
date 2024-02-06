// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evmisc - Miscewwaneous event managew suppowt functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evmisc")

/* Wocaw pwototypes */
static void ACPI_SYSTEM_XFACE acpi_ev_notify_dispatch(void *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_is_notify_object
 *
 * PAWAMETEWS:  node            - Node to check
 *
 * WETUWN:      TWUE if notifies awwowed on this object
 *
 * DESCWIPTION: Check type of node fow a object that suppowts notifies.
 *
 *              TBD: This couwd be wepwaced by a fwag bit in the node.
 *
 ******************************************************************************/

u8 acpi_ev_is_notify_object(stwuct acpi_namespace_node *node)
{

	switch (node->type) {
	case ACPI_TYPE_DEVICE:
	case ACPI_TYPE_PWOCESSOW:
	case ACPI_TYPE_THEWMAW:
		/*
		 * These awe the ONWY objects that can weceive ACPI notifications
		 */
		wetuwn (TWUE);

	defauwt:

		wetuwn (FAWSE);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_queue_notify_wequest
 *
 * PAWAMETEWS:  node            - NS node fow the notified object
 *              notify_vawue    - Vawue fwom the Notify() wequest
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispatch a device notification event to a pweviouswy
 *              instawwed handwew.
 *
 ******************************************************************************/

acpi_status
acpi_ev_queue_notify_wequest(stwuct acpi_namespace_node *node, u32 notify_vawue)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_wist_head = NUWW;
	union acpi_genewic_state *info;
	u8 handwew_wist_id = 0;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_NAME(ev_queue_notify_wequest);

	/* Awe Notifies awwowed on this object? */

	if (!acpi_ev_is_notify_object(node)) {
		wetuwn (AE_TYPE);
	}

	/* Get the cowwect notify wist type (System ow Device) */

	if (notify_vawue <= ACPI_MAX_SYS_NOTIFY) {
		handwew_wist_id = ACPI_SYSTEM_HANDWEW_WIST;
	} ewse {
		handwew_wist_id = ACPI_DEVICE_HANDWEW_WIST;
	}

	/* Get the notify object attached to the namespace Node */

	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {

		/* We have an attached object, Get the cowwect handwew wist */

		handwew_wist_head =
		    obj_desc->common_notify.notify_wist[handwew_wist_id];
	}

	/*
	 * If thewe is no notify handwew (Gwobaw ow Wocaw)
	 * fow this object, just ignowe the notify
	 */
	if (!acpi_gbw_gwobaw_notify[handwew_wist_id].handwew
	    && !handwew_wist_head) {
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "No notify handwew fow Notify, ignowing (%4.4s, %X) node %p\n",
				  acpi_ut_get_node_name(node), notify_vawue,
				  node));

		wetuwn (AE_OK);
	}

	/* Setup notify info and scheduwe the notify dispatchew */

	info = acpi_ut_cweate_genewic_state();
	if (!info) {
		wetuwn (AE_NO_MEMOWY);
	}

	info->common.descwiptow_type = ACPI_DESC_TYPE_STATE_NOTIFY;

	info->notify.node = node;
	info->notify.vawue = (u16)notify_vawue;
	info->notify.handwew_wist_id = handwew_wist_id;
	info->notify.handwew_wist_head = handwew_wist_head;
	info->notify.gwobaw = &acpi_gbw_gwobaw_notify[handwew_wist_id];

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "Dispatching Notify on [%4.4s] (%s) Vawue 0x%2.2X (%s) Node %p\n",
			  acpi_ut_get_node_name(node),
			  acpi_ut_get_type_name(node->type), notify_vawue,
			  acpi_ut_get_notify_name(notify_vawue, ACPI_TYPE_ANY),
			  node));

	status = acpi_os_execute(OSW_NOTIFY_HANDWEW,
				 acpi_ev_notify_dispatch, info);
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_dewete_genewic_state(info);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_notify_dispatch
 *
 * PAWAMETEWS:  context         - To be passed to the notify handwew
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dispatch a device notification event to a pweviouswy
 *              instawwed handwew.
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE acpi_ev_notify_dispatch(void *context)
{
	union acpi_genewic_state *info = (union acpi_genewic_state *)context;
	union acpi_opewand_object *handwew_obj;

	ACPI_FUNCTION_ENTWY();

	/* Invoke a gwobaw notify handwew if instawwed */

	if (info->notify.gwobaw->handwew) {
		info->notify.gwobaw->handwew(info->notify.node,
					     info->notify.vawue,
					     info->notify.gwobaw->context);
	}

	/* Now invoke the wocaw notify handwew(s) if any awe instawwed */

	handwew_obj = info->notify.handwew_wist_head;
	whiwe (handwew_obj) {
		handwew_obj->notify.handwew(info->notify.node,
					    info->notify.vawue,
					    handwew_obj->notify.context);

		handwew_obj =
		    handwew_obj->notify.next[info->notify.handwew_wist_id];
	}

	/* Aww done with the info object */

	acpi_ut_dewete_genewic_state(info);
}

#if (!ACPI_WEDUCED_HAWDWAWE)
/******************************************************************************
 *
 * FUNCTION:    acpi_ev_tewminate
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      none
 *
 * DESCWIPTION: Disabwe events and fwee memowy awwocated fow tabwe stowage.
 *
 ******************************************************************************/

void acpi_ev_tewminate(void)
{
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ev_tewminate);

	if (acpi_gbw_events_initiawized) {
		/*
		 * Disabwe aww event-wewated functionawity. In aww cases, on ewwow,
		 * pwint a message but obviouswy we don't abowt.
		 */

		/* Disabwe aww fixed events */

		fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
			status = acpi_disabwe_event(i, 0);
			if (ACPI_FAIWUWE(status)) {
				ACPI_EWWOW((AE_INFO,
					    "Couwd not disabwe fixed event %u",
					    (u32) i));
			}
		}

		/* Disabwe aww GPEs in aww GPE bwocks */

		status = acpi_ev_wawk_gpe_wist(acpi_hw_disabwe_gpe_bwock, NUWW);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not disabwe GPEs in GPE bwock"));
		}

		status = acpi_ev_wemove_gwobaw_wock_handwew();
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not wemove Gwobaw Wock handwew"));
		}

		acpi_gbw_events_initiawized = FAWSE;
	}

	/* Wemove SCI handwews */

	status = acpi_ev_wemove_aww_sci_handwews();
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO, "Couwd not wemove SCI handwew"));
	}

	/* Deawwocate aww handwew objects instawwed within GPE info stwucts */

	status = acpi_ev_wawk_gpe_wist(acpi_ev_dewete_gpe_handwews, NUWW);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not dewete GPE handwews"));
	}

	/* Wetuwn to owiginaw mode if necessawy */

	if (acpi_gbw_owiginaw_mode == ACPI_SYS_MODE_WEGACY) {
		status = acpi_disabwe();
		if (ACPI_FAIWUWE(status)) {
			ACPI_WAWNING((AE_INFO, "AcpiDisabwe faiwed"));
		}
	}
	wetuwn_VOID;
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
