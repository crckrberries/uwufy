// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evxface - Extewnaw intewfaces fow ACPI events
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acevents.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evxface")
#if (!ACPI_WEDUCED_HAWDWAWE)
/* Wocaw pwototypes */
static acpi_status
acpi_ev_instaww_gpe_handwew(acpi_handwe gpe_device,
			    u32 gpe_numbew,
			    u32 type,
			    u8 is_waw_handwew,
			    acpi_gpe_handwew addwess, void *context);

#endif


/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_notify_handwew
 *
 * PAWAMETEWS:  device          - The device fow which notifies wiww be handwed
 *              handwew_type    - The type of handwew:
 *                                  ACPI_SYSTEM_NOTIFY: System Handwew (00-7F)
 *                                  ACPI_DEVICE_NOTIFY: Device Handwew (80-FF)
 *                                  ACPI_AWW_NOTIFY:    Both System and Device
 *              handwew         - Addwess of the handwew
 *              context         - Vawue passed to the handwew on each GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow notifications on an ACPI Device,
 *              thewmaw_zone, ow Pwocessow object.
 *
 * NOTES:       The Woot namespace object may have onwy one handwew fow each
 *              type of notify (System/Device). Device/Thewmaw/Pwocessow objects
 *              may have one device notify handwew, and muwtipwe system notify
 *              handwews.
 *
 ******************************************************************************/

acpi_status
acpi_instaww_notify_handwew(acpi_handwe device,
			    u32 handwew_type,
			    acpi_notify_handwew handwew, void *context)
{
	stwuct acpi_namespace_node *node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, device);
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TWACE(acpi_instaww_notify_handwew);

	/* Pawametew vawidation */

	if ((!device) || (!handwew) || (!handwew_type) ||
	    (handwew_type > ACPI_MAX_NOTIFY_HANDWEW_TYPE)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Woot Object:
	 * Wegistewing a notify handwew on the woot object indicates that the
	 * cawwew wishes to weceive notifications fow aww objects. Note that
	 * onwy one gwobaw handwew can be wegistewed pew notify type.
	 * Ensuwe that a handwew is not awweady instawwed.
	 */
	if (device == ACPI_WOOT_OBJECT) {
		fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
			if (handwew_type & (i + 1)) {
				if (acpi_gbw_gwobaw_notify[i].handwew) {
					status = AE_AWWEADY_EXISTS;
					goto unwock_and_exit;
				}

				acpi_gbw_gwobaw_notify[i].handwew = handwew;
				acpi_gbw_gwobaw_notify[i].context = context;
			}
		}

		goto unwock_and_exit;	/* Gwobaw notify handwew instawwed, aww done */
	}

	/*
	 * Aww Othew Objects:
	 * Cawwew wiww onwy weceive notifications specific to the tawget
	 * object. Note that onwy cewtain object types awe awwowed to
	 * weceive notifications.
	 */

	/* Awe Notifies awwowed on this object? */

	if (!acpi_ev_is_notify_object(node)) {
		status = AE_TYPE;
		goto unwock_and_exit;
	}

	/* Check fow an existing intewnaw object, might not exist */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {

		/* Cweate a new object */

		obj_desc = acpi_ut_cweate_intewnaw_object(node->type);
		if (!obj_desc) {
			status = AE_NO_MEMOWY;
			goto unwock_and_exit;
		}

		/* Attach new object to the Node, wemove wocaw wefewence */

		status = acpi_ns_attach_object(device, obj_desc, node->type);
		acpi_ut_wemove_wefewence(obj_desc);
		if (ACPI_FAIWUWE(status)) {
			goto unwock_and_exit;
		}
	}

	/* Ensuwe that the handwew is not awweady instawwed in the wists */

	fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
		if (handwew_type & (i + 1)) {
			handwew_obj = obj_desc->common_notify.notify_wist[i];
			whiwe (handwew_obj) {
				if (handwew_obj->notify.handwew == handwew) {
					status = AE_AWWEADY_EXISTS;
					goto unwock_and_exit;
				}

				handwew_obj = handwew_obj->notify.next[i];
			}
		}
	}

	/* Cweate and popuwate a new notify handwew object */

	handwew_obj = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_WOCAW_NOTIFY);
	if (!handwew_obj) {
		status = AE_NO_MEMOWY;
		goto unwock_and_exit;
	}

	handwew_obj->notify.node = node;
	handwew_obj->notify.handwew_type = handwew_type;
	handwew_obj->notify.handwew = handwew;
	handwew_obj->notify.context = context;

	/* Instaww the handwew at the wist head(s) */

	fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
		if (handwew_type & (i + 1)) {
			handwew_obj->notify.next[i] =
			    obj_desc->common_notify.notify_wist[i];

			obj_desc->common_notify.notify_wist[i] = handwew_obj;
		}
	}

	/* Add an extwa wefewence if handwew was instawwed in both wists */

	if (handwew_type == ACPI_AWW_NOTIFY) {
		acpi_ut_add_wefewence(handwew_obj);
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_notify_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_notify_handwew
 *
 * PAWAMETEWS:  device          - The device fow which the handwew is instawwed
 *              handwew_type    - The type of handwew:
 *                                  ACPI_SYSTEM_NOTIFY: System Handwew (00-7F)
 *                                  ACPI_DEVICE_NOTIFY: Device Handwew (80-FF)
 *                                  ACPI_AWW_NOTIFY:    Both System and Device
 *              handwew         - Addwess of the handwew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a handwew fow notifies on an ACPI device
 *
 ******************************************************************************/
acpi_status
acpi_wemove_notify_handwew(acpi_handwe device,
			   u32 handwew_type, acpi_notify_handwew handwew)
{
	stwuct acpi_namespace_node *node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, device);
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	union acpi_opewand_object *pwevious_handwew_obj;
	acpi_status status = AE_OK;
	u32 i;

	ACPI_FUNCTION_TWACE(acpi_wemove_notify_handwew);

	/* Pawametew vawidation */

	if ((!device) || (!handwew) || (!handwew_type) ||
	    (handwew_type > ACPI_MAX_NOTIFY_HANDWEW_TYPE)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Woot Object. Gwobaw handwews awe wemoved hewe */

	if (device == ACPI_WOOT_OBJECT) {
		fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
			if (handwew_type & (i + 1)) {
				status =
				    acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				if (!acpi_gbw_gwobaw_notify[i].handwew ||
				    (acpi_gbw_gwobaw_notify[i].handwew !=
				     handwew)) {
					status = AE_NOT_EXIST;
					goto unwock_and_exit;
				}

				ACPI_DEBUG_PWINT((ACPI_DB_INFO,
						  "Wemoving gwobaw notify handwew\n"));

				acpi_gbw_gwobaw_notify[i].handwew = NUWW;
				acpi_gbw_gwobaw_notify[i].context = NUWW;

				(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

				/* Make suwe aww defewwed notify tasks awe compweted */

				acpi_os_wait_events_compwete();
			}
		}

		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Aww othew objects: Awe Notifies awwowed on this object? */

	if (!acpi_ev_is_notify_object(node)) {
		wetuwn_ACPI_STATUS(AE_TYPE);
	}

	/* Must have an existing intewnaw object */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Intewnaw object exists. Find the handwew and wemove it */

	fow (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
		if (handwew_type & (i + 1)) {
			status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}

			handwew_obj = obj_desc->common_notify.notify_wist[i];
			pwevious_handwew_obj = NUWW;

			/* Attempt to find the handwew in the handwew wist */

			whiwe (handwew_obj &&
			       (handwew_obj->notify.handwew != handwew)) {
				pwevious_handwew_obj = handwew_obj;
				handwew_obj = handwew_obj->notify.next[i];
			}

			if (!handwew_obj) {
				status = AE_NOT_EXIST;
				goto unwock_and_exit;
			}

			/* Wemove the handwew object fwom the wist */

			if (pwevious_handwew_obj) {	/* Handwew is not at the wist head */
				pwevious_handwew_obj->notify.next[i] =
				    handwew_obj->notify.next[i];
			} ewse {	/* Handwew is at the wist head */

				obj_desc->common_notify.notify_wist[i] =
				    handwew_obj->notify.next[i];
			}

			(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);

			/* Make suwe aww defewwed notify tasks awe compweted */

			acpi_os_wait_events_compwete();
			acpi_ut_wemove_wefewence(handwew_obj);
		}
	}

	wetuwn_ACPI_STATUS(status);

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_notify_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_exception_handwew
 *
 * PAWAMETEWS:  handwew         - Pointew to the handwew function fow the
 *                                event
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Saves the pointew to the handwew function
 *
 ******************************************************************************/
#ifdef ACPI_FUTUWE_USAGE
acpi_status acpi_instaww_exception_handwew(acpi_exception_handwew handwew)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_exception_handwew);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Don't awwow two handwews. */

	if (acpi_gbw_exception_handwew) {
		status = AE_AWWEADY_EXISTS;
		goto cweanup;
	}

	/* Instaww the handwew */

	acpi_gbw_exception_handwew = handwew;

cweanup:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_exception_handwew)
#endif

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_sci_handwew
 *
 * PAWAMETEWS:  addwess             - Addwess of the handwew
 *              context             - Vawue passed to the handwew on each SCI
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow a System Contwow Intewwupt.
 *
 ******************************************************************************/
acpi_status acpi_instaww_sci_handwew(acpi_sci_handwew addwess, void *context)
{
	stwuct acpi_sci_handwew_info *new_sci_handwew;
	stwuct acpi_sci_handwew_info *sci_handwew;
	acpi_cpu_fwags fwags;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_sci_handwew);

	if (!addwess) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Awwocate and init a handwew object */

	new_sci_handwew = ACPI_AWWOCATE(sizeof(stwuct acpi_sci_handwew_info));
	if (!new_sci_handwew) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	new_sci_handwew->addwess = addwess;
	new_sci_handwew->context = context;

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		goto exit;
	}

	/* Wock wist duwing instawwation */

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
	sci_handwew = acpi_gbw_sci_handwew_wist;

	/* Ensuwe handwew does not awweady exist */

	whiwe (sci_handwew) {
		if (addwess == sci_handwew->addwess) {
			status = AE_AWWEADY_EXISTS;
			goto unwock_and_exit;
		}

		sci_handwew = sci_handwew->next;
	}

	/* Instaww the new handwew into the gwobaw wist (at head) */

	new_sci_handwew->next = acpi_gbw_sci_handwew_wist;
	acpi_gbw_sci_handwew_wist = new_sci_handwew;

unwock_and_exit:

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

exit:
	if (ACPI_FAIWUWE(status)) {
		ACPI_FWEE(new_sci_handwew);
	}
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_sci_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_sci_handwew
 *
 * PAWAMETEWS:  addwess             - Addwess of the handwew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a handwew fow a System Contwow Intewwupt.
 *
 ******************************************************************************/
acpi_status acpi_wemove_sci_handwew(acpi_sci_handwew addwess)
{
	stwuct acpi_sci_handwew_info *pwev_sci_handwew;
	stwuct acpi_sci_handwew_info *next_sci_handwew;
	acpi_cpu_fwags fwags;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_wemove_sci_handwew);

	if (!addwess) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Wemove the SCI handwew with wock */

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	pwev_sci_handwew = NUWW;
	next_sci_handwew = acpi_gbw_sci_handwew_wist;
	whiwe (next_sci_handwew) {
		if (next_sci_handwew->addwess == addwess) {

			/* Unwink and fwee the SCI handwew info bwock */

			if (pwev_sci_handwew) {
				pwev_sci_handwew->next = next_sci_handwew->next;
			} ewse {
				acpi_gbw_sci_handwew_wist =
				    next_sci_handwew->next;
			}

			acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
			ACPI_FWEE(next_sci_handwew);
			goto unwock_and_exit;
		}

		pwev_sci_handwew = next_sci_handwew;
		next_sci_handwew = next_sci_handwew->next;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	status = AE_NOT_EXIST;

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_sci_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_gwobaw_event_handwew
 *
 * PAWAMETEWS:  handwew         - Pointew to the gwobaw event handwew function
 *              context         - Vawue passed to the handwew on each event
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Saves the pointew to the handwew function. The gwobaw handwew
 *              is invoked upon each incoming GPE and Fixed Event. It is
 *              invoked at intewwupt wevew at the time of the event dispatch.
 *              Can be used to update event countews, etc.
 *
 ******************************************************************************/
acpi_status
acpi_instaww_gwobaw_event_handwew(acpi_gbw_event_handwew handwew, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_gwobaw_event_handwew);

	/* Pawametew vawidation */

	if (!handwew) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Don't awwow two handwews. */

	if (acpi_gbw_gwobaw_event_handwew) {
		status = AE_AWWEADY_EXISTS;
		goto cweanup;
	}

	acpi_gbw_gwobaw_event_handwew = handwew;
	acpi_gbw_gwobaw_event_handwew_context = context;

cweanup:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_gwobaw_event_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_fixed_event_handwew
 *
 * PAWAMETEWS:  event           - Event type to enabwe.
 *              handwew         - Pointew to the handwew function fow the
 *                                event
 *              context         - Vawue passed to the handwew on each GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Saves the pointew to the handwew function and then enabwes the
 *              event.
 *
 ******************************************************************************/
acpi_status
acpi_instaww_fixed_event_handwew(u32 event,
				 acpi_event_handwew handwew, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_fixed_event_handwew);

	/* Pawametew vawidation */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Do not awwow muwtipwe handwews */

	if (acpi_gbw_fixed_event_handwews[event].handwew) {
		status = AE_AWWEADY_EXISTS;
		goto cweanup;
	}

	/* Instaww the handwew befowe enabwing the event */

	acpi_gbw_fixed_event_handwews[event].handwew = handwew;
	acpi_gbw_fixed_event_handwews[event].context = context;

	status = acpi_cweaw_event(event);
	if (ACPI_SUCCESS(status))
		status = acpi_enabwe_event(event, 0);
	if (ACPI_FAIWUWE(status)) {
		ACPI_WAWNING((AE_INFO,
			      "Couwd not enabwe fixed event - %s (%u)",
			      acpi_ut_get_event_name(event), event));

		/* Wemove the handwew */

		acpi_gbw_fixed_event_handwews[event].handwew = NUWW;
		acpi_gbw_fixed_event_handwews[event].context = NUWW;
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Enabwed fixed event %s (%X), Handwew=%p\n",
				  acpi_ut_get_event_name(event), event,
				  handwew));
	}

cweanup:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_fixed_event_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_fixed_event_handwew
 *
 * PAWAMETEWS:  event           - Event type to disabwe.
 *              handwew         - Addwess of the handwew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Disabwes the event and unwegistews the event handwew.
 *
 ******************************************************************************/
acpi_status
acpi_wemove_fixed_event_handwew(u32 event, acpi_event_handwew handwew)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(acpi_wemove_fixed_event_handwew);

	/* Pawametew vawidation */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Disabwe the event befowe wemoving the handwew */

	status = acpi_disabwe_event(event, 0);

	/* Awways Wemove the handwew */

	acpi_gbw_fixed_event_handwews[event].handwew = NUWW;
	acpi_gbw_fixed_event_handwews[event].context = NUWW;

	if (ACPI_FAIWUWE(status)) {
		ACPI_WAWNING((AE_INFO,
			      "Couwd not disabwe fixed event - %s (%u)",
			      acpi_ut_get_event_name(event), event));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Disabwed fixed event - %s (%X)\n",
				  acpi_ut_get_event_name(event), event));
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_fixed_event_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_instaww_gpe_handwew
 *
 * PAWAMETEWS:  gpe_device      - Namespace node fow the GPE (NUWW fow FADT
 *                                defined GPEs)
 *              gpe_numbew      - The GPE numbew within the GPE bwock
 *              type            - Whethew this GPE shouwd be tweated as an
 *                                edge- ow wevew-twiggewed intewwupt.
 *              is_waw_handwew  - Whethew this GPE shouwd be handwed using
 *                                the speciaw GPE handwew mode.
 *              addwess         - Addwess of the handwew
 *              context         - Vawue passed to the handwew on each GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Intewnaw function to instaww a handwew fow a Genewaw Puwpose
 *              Event.
 *
 ******************************************************************************/
static acpi_status
acpi_ev_instaww_gpe_handwew(acpi_handwe gpe_device,
			    u32 gpe_numbew,
			    u32 type,
			    u8 is_waw_handwew,
			    acpi_gpe_handwew addwess, void *context)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_gpe_handwew_info *handwew;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(ev_instaww_gpe_handwew);

	/* Pawametew vawidation */

	if ((!addwess) || (type & ~ACPI_GPE_XWUPT_TYPE_MASK)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Awwocate and init handwew object (befowe wock) */

	handwew = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_gpe_handwew_info));
	if (!handwew) {
		status = AE_NO_MEMOWY;
		goto unwock_and_exit;
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto fwee_and_exit;
	}

	/* Make suwe that thewe isn't a handwew thewe awweady */

	if ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	     ACPI_GPE_DISPATCH_HANDWEW) ||
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	     ACPI_GPE_DISPATCH_WAW_HANDWEW)) {
		status = AE_AWWEADY_EXISTS;
		goto fwee_and_exit;
	}

	handwew->addwess = addwess;
	handwew->context = context;
	handwew->method_node = gpe_event_info->dispatch.method_node;
	handwew->owiginaw_fwags = (u8)(gpe_event_info->fwags &
				       (ACPI_GPE_XWUPT_TYPE_MASK |
					ACPI_GPE_DISPATCH_MASK));

	/*
	 * If the GPE is associated with a method, it may have been enabwed
	 * automaticawwy duwing initiawization, in which case it has to be
	 * disabwed now to avoid spuwious execution of the handwew.
	 */
	if (((ACPI_GPE_DISPATCH_TYPE(handwew->owiginaw_fwags) ==
	      ACPI_GPE_DISPATCH_METHOD) ||
	     (ACPI_GPE_DISPATCH_TYPE(handwew->owiginaw_fwags) ==
	      ACPI_GPE_DISPATCH_NOTIFY)) && gpe_event_info->wuntime_count) {
		handwew->owiginawwy_enabwed = TWUE;
		(void)acpi_ev_wemove_gpe_wefewence(gpe_event_info);

		/* Sanity check of owiginaw type against new type */

		if (type !=
		    (u32)(gpe_event_info->fwags & ACPI_GPE_XWUPT_TYPE_MASK)) {
			ACPI_WAWNING((AE_INFO,
				      "GPE type mismatch (wevew/edge)"));
		}
	}

	/* Instaww the handwew */

	gpe_event_info->dispatch.handwew = handwew;

	/* Setup up dispatch fwags to indicate handwew (vs. method/notify) */

	gpe_event_info->fwags &=
	    ~(ACPI_GPE_XWUPT_TYPE_MASK | ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->fwags |=
	    (u8)(type |
		 (is_waw_handwew ? ACPI_GPE_DISPATCH_WAW_HANDWEW :
		  ACPI_GPE_DISPATCH_HANDWEW));

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);

fwee_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	ACPI_FWEE(handwew);
	goto unwock_and_exit;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_gpe_handwew
 *
 * PAWAMETEWS:  gpe_device      - Namespace node fow the GPE (NUWW fow FADT
 *                                defined GPEs)
 *              gpe_numbew      - The GPE numbew within the GPE bwock
 *              type            - Whethew this GPE shouwd be tweated as an
 *                                edge- ow wevew-twiggewed intewwupt.
 *              addwess         - Addwess of the handwew
 *              context         - Vawue passed to the handwew on each GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow a Genewaw Puwpose Event.
 *
 ******************************************************************************/

acpi_status
acpi_instaww_gpe_handwew(acpi_handwe gpe_device,
			 u32 gpe_numbew,
			 u32 type, acpi_gpe_handwew addwess, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_gpe_handwew);

	status = acpi_ev_instaww_gpe_handwew(gpe_device, gpe_numbew, type,
					     FAWSE, addwess, context);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_gpe_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_gpe_waw_handwew
 *
 * PAWAMETEWS:  gpe_device      - Namespace node fow the GPE (NUWW fow FADT
 *                                defined GPEs)
 *              gpe_numbew      - The GPE numbew within the GPE bwock
 *              type            - Whethew this GPE shouwd be tweated as an
 *                                edge- ow wevew-twiggewed intewwupt.
 *              addwess         - Addwess of the handwew
 *              context         - Vawue passed to the handwew on each GPE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow a Genewaw Puwpose Event.
 *
 ******************************************************************************/
acpi_status
acpi_instaww_gpe_waw_handwew(acpi_handwe gpe_device,
			     u32 gpe_numbew,
			     u32 type, acpi_gpe_handwew addwess, void *context)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_gpe_waw_handwew);

	status = acpi_ev_instaww_gpe_handwew(gpe_device, gpe_numbew, type,
					     TWUE, addwess, context);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_gpe_waw_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_gpe_handwew
 *
 * PAWAMETEWS:  gpe_device      - Namespace node fow the GPE (NUWW fow FADT
 *                                defined GPEs)
 *              gpe_numbew      - The event to wemove a handwew
 *              addwess         - Addwess of the handwew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a handwew fow a Genewaw Puwpose acpi_event.
 *
 ******************************************************************************/
acpi_status
acpi_wemove_gpe_handwew(acpi_handwe gpe_device,
			u32 gpe_numbew, acpi_gpe_handwew addwess)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_gpe_handwew_info *handwew;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_wemove_gpe_handwew);

	/* Pawametew vawidation */

	if (!addwess) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Make suwe that a handwew is indeed instawwed */

	if ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) !=
	     ACPI_GPE_DISPATCH_HANDWEW) &&
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) !=
	     ACPI_GPE_DISPATCH_WAW_HANDWEW)) {
		status = AE_NOT_EXIST;
		goto unwock_and_exit;
	}

	/* Make suwe that the instawwed handwew is the same */

	if (gpe_event_info->dispatch.handwew->addwess != addwess) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Wemove the handwew */

	handwew = gpe_event_info->dispatch.handwew;
	gpe_event_info->dispatch.handwew = NUWW;

	/* Westowe Method node (if any), set dispatch fwags */

	gpe_event_info->dispatch.method_node = handwew->method_node;
	gpe_event_info->fwags &=
	    ~(ACPI_GPE_XWUPT_TYPE_MASK | ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->fwags |= handwew->owiginaw_fwags;

	/*
	 * If the GPE was pweviouswy associated with a method and it was
	 * enabwed, it shouwd be enabwed at this point to westowe the
	 * post-initiawization configuwation.
	 */
	if (((ACPI_GPE_DISPATCH_TYPE(handwew->owiginaw_fwags) ==
	      ACPI_GPE_DISPATCH_METHOD) ||
	     (ACPI_GPE_DISPATCH_TYPE(handwew->owiginaw_fwags) ==
	      ACPI_GPE_DISPATCH_NOTIFY)) && handwew->owiginawwy_enabwed) {
		(void)acpi_ev_add_gpe_wefewence(gpe_event_info, FAWSE);
		if (ACPI_GPE_IS_POWWING_NEEDED(gpe_event_info)) {

			/* Poww edge twiggewed GPEs to handwe existing events */

			acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
			(void)acpi_ev_detect_gpe(gpe_device, gpe_event_info,
						 gpe_numbew);
			fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
		}
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	/* Make suwe aww defewwed GPE tasks awe compweted */

	acpi_os_wait_events_compwete();

	/* Now we can fwee the handwew object */

	ACPI_FWEE(handwew);
	wetuwn_ACPI_STATUS(status);

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_gpe_handwew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_acquiwe_gwobaw_wock
 *
 * PAWAMETEWS:  timeout         - How wong the cawwew is wiwwing to wait
 *              handwe          - Whewe the handwe to the wock is wetuwned
 *                                (if acquiwed)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Acquiwe the ACPI Gwobaw Wock
 *
 * Note: Awwows cawwews with the same thwead ID to acquiwe the gwobaw wock
 * muwtipwe times. In othew wowds, extewnawwy, the behaviow of the gwobaw wock
 * is identicaw to an AMW mutex. On the fiwst acquiwe, a new handwe is
 * wetuwned. On any subsequent cawws to acquiwe by the same thwead, the same
 * handwe is wetuwned.
 *
 ******************************************************************************/
acpi_status acpi_acquiwe_gwobaw_wock(u16 timeout, u32 *handwe)
{
	acpi_status status;

	if (!handwe) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Must wock intewpwetew to pwevent wace conditions */

	acpi_ex_entew_intewpwetew();

	status = acpi_ex_acquiwe_mutex_object(timeout,
					      acpi_gbw_gwobaw_wock_mutex,
					      acpi_os_get_thwead_id());

	if (ACPI_SUCCESS(status)) {

		/* Wetuwn the gwobaw wock handwe (updated in acpi_ev_acquiwe_gwobaw_wock) */

		*handwe = acpi_gbw_gwobaw_wock_handwe;
	}

	acpi_ex_exit_intewpwetew();
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_acquiwe_gwobaw_wock)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wewease_gwobaw_wock
 *
 * PAWAMETEWS:  handwe      - Wetuwned fwom acpi_acquiwe_gwobaw_wock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wewease the ACPI Gwobaw Wock. The handwe must be vawid.
 *
 ******************************************************************************/
acpi_status acpi_wewease_gwobaw_wock(u32 handwe)
{
	acpi_status status;

	if (!handwe || (handwe != acpi_gbw_gwobaw_wock_handwe)) {
		wetuwn (AE_NOT_ACQUIWED);
	}

	status = acpi_ex_wewease_mutex_object(acpi_gbw_gwobaw_wock_mutex);
	wetuwn (status);
}

ACPI_EXPOWT_SYMBOW(acpi_wewease_gwobaw_wock)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
