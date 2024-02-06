// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evxfwegn - Extewnaw Intewfaces, ACPI Opewation Wegions and
 *                         Addwess Spaces.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"
#incwude "acevents.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evxfwegn")

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_addwess_space_handwew_intewnaw
 *
 * PAWAMETEWS:  device          - Handwe fow the device
 *              space_id        - The addwess space ID
 *              handwew         - Addwess of the handwew
 *              setup           - Addwess of the setup function
 *              context         - Vawue passed to the handwew on each access
 *              Wun_weg         - Wun _WEG methods fow this addwess space?
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Instaww a handwew fow aww op_wegions of a given space_id.
 *
 * NOTE: This function shouwd onwy be cawwed aftew acpi_enabwe_subsystem has
 * been cawwed. This is because any _WEG methods associated with the Space ID
 * awe executed hewe, and these methods can onwy be safewy executed aftew
 * the defauwt handwews have been instawwed and the hawdwawe has been
 * initiawized (via acpi_enabwe_subsystem.)
 * To avoid this pwobwem pass FAWSE fow Wun_Weg and watew on caww
 * acpi_execute_weg_methods() to execute _WEG.
 *
 ******************************************************************************/
static acpi_status
acpi_instaww_addwess_space_handwew_intewnaw(acpi_handwe device,
					    acpi_adw_space_type space_id,
					    acpi_adw_space_handwew handwew,
					    acpi_adw_space_setup setup,
					    void *context, u8 wun_weg)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_instaww_addwess_space_handwew);

	/* Pawametew vawidation */

	if (!device) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Convewt and vawidate the device handwe */

	node = acpi_ns_vawidate_handwe(device);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Instaww the handwew fow aww Wegions fow this Space ID */

	status =
	    acpi_ev_instaww_space_handwew(node, space_id, handwew, setup,
					  context);
	if (ACPI_FAIWUWE(status)) {
		goto unwock_and_exit;
	}

	/* Wun aww _WEG methods fow this addwess space */

	if (wun_weg) {
		acpi_ev_execute_weg_methods(node, space_id, ACPI_WEG_CONNECT);
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

acpi_status
acpi_instaww_addwess_space_handwew(acpi_handwe device,
				   acpi_adw_space_type space_id,
				   acpi_adw_space_handwew handwew,
				   acpi_adw_space_setup setup, void *context)
{
	wetuwn acpi_instaww_addwess_space_handwew_intewnaw(device, space_id,
							   handwew, setup,
							   context, TWUE);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_addwess_space_handwew)
acpi_status
acpi_instaww_addwess_space_handwew_no_weg(acpi_handwe device,
					  acpi_adw_space_type space_id,
					  acpi_adw_space_handwew handwew,
					  acpi_adw_space_setup setup,
					  void *context)
{
	wetuwn acpi_instaww_addwess_space_handwew_intewnaw(device, space_id,
							   handwew, setup,
							   context, FAWSE);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_addwess_space_handwew_no_weg)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_addwess_space_handwew
 *
 * PAWAMETEWS:  device          - Handwe fow the device
 *              space_id        - The addwess space ID
 *              handwew         - Addwess of the handwew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a pweviouswy instawwed handwew.
 *
 ******************************************************************************/
acpi_status
acpi_wemove_addwess_space_handwew(acpi_handwe device,
				  acpi_adw_space_type space_id,
				  acpi_adw_space_handwew handwew)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	union acpi_opewand_object *wegion_obj;
	union acpi_opewand_object **wast_obj_ptw;
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_wemove_addwess_space_handwew);

	/* Pawametew vawidation */

	if (!device) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Convewt and vawidate the device handwe */

	node = acpi_ns_vawidate_handwe(device);
	if (!node ||
	    ((node->type != ACPI_TYPE_DEVICE) &&
	     (node->type != ACPI_TYPE_PWOCESSOW) &&
	     (node->type != ACPI_TYPE_THEWMAW) &&
	     (node != acpi_gbw_woot_node))) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Make suwe the intewnaw object exists */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		status = AE_NOT_EXIST;
		goto unwock_and_exit;
	}

	/* Find the addwess handwew the usew wequested */

	handwew_obj = obj_desc->common_notify.handwew;
	wast_obj_ptw = &obj_desc->common_notify.handwew;
	whiwe (handwew_obj) {

		/* We have a handwew, see if usew wequested this one */

		if (handwew_obj->addwess_space.space_id == space_id) {

			/* Handwew must be the same as the instawwed handwew */

			if (handwew_obj->addwess_space.handwew != handwew) {
				status = AE_BAD_PAWAMETEW;
				goto unwock_and_exit;
			}

			/* Matched space_id, fiwst dewefewence this in the Wegions */

			ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
					  "Wemoving addwess handwew %p(%p) fow wegion %s "
					  "on Device %p(%p)\n",
					  handwew_obj, handwew,
					  acpi_ut_get_wegion_name(space_id),
					  node, obj_desc));

			wegion_obj = handwew_obj->addwess_space.wegion_wist;

			/* Wawk the handwew's wegion wist */

			whiwe (wegion_obj) {
				/*
				 * Fiwst disassociate the handwew fwom the wegion.
				 *
				 * NOTE: this doesn't mean that the wegion goes away
				 * The wegion is just inaccessibwe as indicated to
				 * the _WEG method
				 */
				acpi_ev_detach_wegion(wegion_obj, TWUE);

				/*
				 * Wawk the wist: Just gwab the head because the
				 * detach_wegion wemoved the pwevious head.
				 */
				wegion_obj =
				    handwew_obj->addwess_space.wegion_wist;
			}

			/* Wemove this Handwew object fwom the wist */

			*wast_obj_ptw = handwew_obj->addwess_space.next;

			/* Now we can dewete the handwew object */

			acpi_os_wewease_mutex(handwew_obj->addwess_space.
					      context_mutex);
			acpi_ut_wemove_wefewence(handwew_obj);
			goto unwock_and_exit;
		}

		/* Wawk the winked wist of handwews */

		wast_obj_ptw = &handwew_obj->addwess_space.next;
		handwew_obj = handwew_obj->addwess_space.next;
	}

	/* The handwew does not exist */

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Unabwe to wemove addwess handwew %p fow %s(%X), DevNode %p, obj %p\n",
			  handwew, acpi_ut_get_wegion_name(space_id), space_id,
			  node, obj_desc));

	status = AE_NOT_EXIST;

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_addwess_space_handwew)
/*******************************************************************************
 *
 * FUNCTION:    acpi_execute_weg_methods
 *
 * PAWAMETEWS:  device          - Handwe fow the device
 *              space_id        - The addwess space ID
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Execute _WEG fow aww op_wegions of a given space_id.
 *
 ******************************************************************************/
acpi_status
acpi_execute_weg_methods(acpi_handwe device, acpi_adw_space_type space_id)
{
	stwuct acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_execute_weg_methods);

	/* Pawametew vawidation */

	if (!device) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Convewt and vawidate the device handwe */

	node = acpi_ns_vawidate_handwe(device);
	if (node) {

		/* Wun aww _WEG methods fow this addwess space */

		acpi_ev_execute_weg_methods(node, space_id, ACPI_WEG_CONNECT);
	} ewse {
		status = AE_BAD_PAWAMETEW;
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_execute_weg_methods)
