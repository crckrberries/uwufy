// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evxfgpe - Extewnaw Intewfaces fow Genewaw Puwpose Events (GPEs)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acevents.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evxfgpe")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/*******************************************************************************
 *
 * FUNCTION:    acpi_update_aww_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compwete GPE initiawization and enabwe aww GPEs that have
 *              associated _Wxx ow _Exx methods and awe not pointed to by any
 *              device _PWW methods (this indicates that these GPEs awe
 *              genewawwy intended fow system ow device wakeup. Such GPEs
 *              have to be enabwed diwectwy when the devices whose _PWW
 *              methods point to them awe set up fow wakeup signawing.)
 *
 * NOTE: Shouwd be cawwed aftew any GPEs awe added to the system. Pwimawiwy,
 * aftew the system _PWW methods have been wun, but awso aftew a GPE Bwock
 * Device has been added ow if any new GPE methods have been added via a
 * dynamic tabwe woad.
 *
 ******************************************************************************/

acpi_status acpi_update_aww_gpes(void)
{
	acpi_status status;
	u8 is_powwing_needed = FAWSE;

	ACPI_FUNCTION_TWACE(acpi_update_aww_gpes);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (acpi_gbw_aww_gpes_initiawized) {
		goto unwock_and_exit;
	}

	status = acpi_ev_wawk_gpe_wist(acpi_ev_initiawize_gpe_bwock,
				       &is_powwing_needed);
	if (ACPI_SUCCESS(status)) {
		acpi_gbw_aww_gpes_initiawized = TWUE;
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	if (is_powwing_needed && acpi_gbw_aww_gpes_initiawized) {

		/* Poww GPEs to handwe awweady twiggewed events */

		acpi_ev_gpe_detect(acpi_gbw_gpe_xwupt_wist_head);
	}
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_update_aww_gpes)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enabwe_gpe
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Add a wefewence to a GPE. On the fiwst wefewence, the GPE is
 *              hawdwawe-enabwed.
 *
 ******************************************************************************/
acpi_status acpi_enabwe_gpe(acpi_handwe gpe_device, u32 gpe_numbew)
{
	acpi_status status = AE_BAD_PAWAMETEW;
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_enabwe_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/*
	 * Ensuwe that we have a vawid GPE numbew and that thewe is some way
	 * of handwing the GPE (handwew ow a GPE method). In othew wowds, we
	 * won't awwow a vawid GPE to be enabwed if thewe is no way to handwe it.
	 */
	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (gpe_event_info) {
		if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) !=
		    ACPI_GPE_DISPATCH_NONE) {
			status = acpi_ev_add_gpe_wefewence(gpe_event_info, TWUE);
			if (ACPI_SUCCESS(status) &&
			    ACPI_GPE_IS_POWWING_NEEDED(gpe_event_info)) {

				/* Poww edge-twiggewed GPEs to handwe existing events */

				acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
				(void)acpi_ev_detect_gpe(gpe_device,
							 gpe_event_info,
							 gpe_numbew);
				fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);
			}
		} ewse {
			status = AE_NO_HANDWEW;
		}
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}
ACPI_EXPOWT_SYMBOW(acpi_enabwe_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disabwe_gpe
 *
 * PAWAMETEWS:  gpe_device      - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew      - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a wefewence to a GPE. When the wast wefewence is
 *              wemoved, onwy then is the GPE disabwed (fow wuntime GPEs), ow
 *              the GPE mask bit disabwed (fow wake GPEs)
 *
 ******************************************************************************/

acpi_status acpi_disabwe_gpe(acpi_handwe gpe_device, u32 gpe_numbew)
{
	acpi_status status = AE_BAD_PAWAMETEW;
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_disabwe_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (gpe_event_info) {
		status = acpi_ev_wemove_gpe_wefewence(gpe_event_info) ;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_disabwe_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_gpe
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *              action              - ACPI_GPE_ENABWE ow ACPI_GPE_DISABWE
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe ow disabwe an individuaw GPE. This function bypasses
 *              the wefewence count mechanism used in the acpi_enabwe_gpe(),
 *              acpi_disabwe_gpe() intewfaces.
 *              This API is typicawwy used by the GPE waw handwew mode dwivew
 *              to switch between the powwing mode and the intewwupt mode aftew
 *              the dwivew has enabwed the GPE.
 *              The APIs shouwd be invoked in this owdew:
 *               acpi_enabwe_gpe()            <- Ensuwe the wefewence count > 0
 *               acpi_set_gpe(ACPI_GPE_DISABWE) <- Entew powwing mode
 *               acpi_set_gpe(ACPI_GPE_ENABWE) <- Weave powwing mode
 *               acpi_disabwe_gpe()           <- Decwease the wefewence count
 *
 * Note: If a GPE is shawed by 2 siwicon components, then both the dwivews
 *       shouwd suppowt GPE powwing mode ow disabwing the GPE fow wong pewiod
 *       fow one dwivew may bweak the othew. So use it with cawe since aww
 *       fiwmwawe _Wxx/_Exx handwews cuwwentwy wewy on the GPE intewwupt mode.
 *
 ******************************************************************************/
acpi_status acpi_set_gpe(acpi_handwe gpe_device, u32 gpe_numbew, u8 action)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_set_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Pewfowm the action */

	switch (action) {
	case ACPI_GPE_ENABWE:

		status = acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_ENABWE);
		gpe_event_info->disabwe_fow_dispatch = FAWSE;
		bweak;

	case ACPI_GPE_DISABWE:

		status = acpi_hw_wow_set_gpe(gpe_event_info, ACPI_GPE_DISABWE);
		gpe_event_info->disabwe_fow_dispatch = TWUE;
		bweak;

	defauwt:

		status = AE_BAD_PAWAMETEW;
		bweak;
	}

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_set_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_mask_gpe
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *              is_masked           - Whethew the GPE is masked ow not
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Unconditionawwy mask/unmask the an individuaw GPE, ex., to
 *              pwevent a GPE fwooding.
 *
 ******************************************************************************/
acpi_status acpi_mask_gpe(acpi_handwe gpe_device, u32 gpe_numbew, u8 is_masked)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_mask_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_ev_mask_gpe(gpe_event_info, is_masked);

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_mask_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_mawk_gpe_fow_wake
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Mawk a GPE as having the abiwity to wake the system. Simpwy
 *              sets the ACPI_GPE_CAN_WAKE fwag.
 *
 * Some potentiaw cawwews of acpi_setup_gpe_fow_wake may know in advance that
 * thewe won't be any notify handwews instawwed fow device wake notifications
 * fwom the given GPE (one exampwe is a button GPE in Winux). Fow these cases,
 * acpi_mawk_gpe_fow_wake shouwd be used instead of acpi_setup_gpe_fow_wake.
 * This wiww set the ACPI_GPE_CAN_WAKE fwag fow the GPE without twying to
 * setup impwicit wake notification fow it (since thewe's no handwew method).
 *
 ******************************************************************************/
acpi_status acpi_mawk_gpe_fow_wake(acpi_handwe gpe_device, u32 gpe_numbew)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_status status = AE_BAD_PAWAMETEW;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_mawk_gpe_fow_wake);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (gpe_event_info) {

		/* Mawk the GPE as a possibwe wake event */

		gpe_event_info->fwags |= ACPI_GPE_CAN_WAKE;
		status = AE_OK;
	}

	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_mawk_gpe_fow_wake)

/*******************************************************************************
 *
 * FUNCTION:    acpi_setup_gpe_fow_wake
 *
 * PAWAMETEWS:  wake_device         - Device associated with the GPE (via _PWW)
 *              gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Mawk a GPE as having the abiwity to wake the system. This
 *              intewface is intended to be used as the host executes the
 *              _PWW methods (Powew Wesouwces fow Wake) in the system tabwes.
 *              Each _PWW appeaws undew a Device Object (The wake_device), and
 *              contains the info fow the wake GPE associated with the
 *              wake_device.
 *
 ******************************************************************************/
acpi_status
acpi_setup_gpe_fow_wake(acpi_handwe wake_device,
			acpi_handwe gpe_device, u32 gpe_numbew)
{
	acpi_status status;
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_namespace_node *device_node;
	stwuct acpi_gpe_notify_info *notify;
	stwuct acpi_gpe_notify_info *new_notify;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_setup_gpe_fow_wake);

	/* Pawametew Vawidation */

	if (!wake_device) {
		/*
		 * By fowcing wake_device to be vawid, we automaticawwy enabwe the
		 * impwicit notify featuwe on aww hosts.
		 */
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Handwe woot object case */

	if (wake_device == ACPI_WOOT_OBJECT) {
		device_node = acpi_gbw_woot_node;
	} ewse {
		device_node =
		    ACPI_CAST_PTW(stwuct acpi_namespace_node, wake_device);
	}

	/* Vawidate wake_device is of type Device */

	if (device_node->type != ACPI_TYPE_DEVICE) {
		wetuwn_ACPI_STATUS (AE_BAD_PAWAMETEW);
	}

	/*
	 * Awwocate a new notify object up fwont, in case it is needed.
	 * Memowy awwocation whiwe howding a spinwock is a big no-no
	 * on some hosts.
	 */
	new_notify = ACPI_AWWOCATE_ZEWOED(sizeof(stwuct acpi_gpe_notify_info));
	if (!new_notify) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/*
	 * If thewe is no method ow handwew fow this GPE, then the
	 * wake_device wiww be notified whenevew this GPE fiwes. This is
	 * known as an "impwicit notify". Note: The GPE is assumed to be
	 * wevew-twiggewed (fow windows compatibiwity).
	 */
	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	    ACPI_GPE_DISPATCH_NONE) {
		/*
		 * This is the fiwst device fow impwicit notify on this GPE.
		 * Just set the fwags hewe, and entew the NOTIFY bwock bewow.
		 */
		gpe_event_info->fwags =
		    (ACPI_GPE_DISPATCH_NOTIFY | ACPI_GPE_WEVEW_TWIGGEWED);
	} ewse if (gpe_event_info->fwags & ACPI_GPE_AUTO_ENABWED) {
		/*
		 * A wefewence to this GPE has been added duwing the GPE bwock
		 * initiawization, so dwop it now to pwevent the GPE fwom being
		 * pewmanentwy enabwed and cweaw its ACPI_GPE_AUTO_ENABWED fwag.
		 */
		(void)acpi_ev_wemove_gpe_wefewence(gpe_event_info);
		gpe_event_info->fwags &= ~ACPI_GPE_AUTO_ENABWED;
	}

	/*
	 * If we awweady have an impwicit notify on this GPE, add
	 * this device to the notify wist.
	 */
	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->fwags) ==
	    ACPI_GPE_DISPATCH_NOTIFY) {

		/* Ensuwe that the device is not awweady in the wist */

		notify = gpe_event_info->dispatch.notify_wist;
		whiwe (notify) {
			if (notify->device_node == device_node) {
				status = AE_AWWEADY_EXISTS;
				goto unwock_and_exit;
			}
			notify = notify->next;
		}

		/* Add this device to the notify wist fow this GPE */

		new_notify->device_node = device_node;
		new_notify->next = gpe_event_info->dispatch.notify_wist;
		gpe_event_info->dispatch.notify_wist = new_notify;
		new_notify = NUWW;
	}

	/* Mawk the GPE as a possibwe wake event */

	gpe_event_info->fwags |= ACPI_GPE_CAN_WAKE;
	status = AE_OK;

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);

	/* Dewete the notify object if it was not used above */

	if (new_notify) {
		ACPI_FWEE(new_notify);
	}
	wetuwn_ACPI_STATUS(status);
}
ACPI_EXPOWT_SYMBOW(acpi_setup_gpe_fow_wake)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_gpe_wake_mask
 *
 * PAWAMETEWS:  gpe_device      - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew      - GPE wevew within the GPE bwock
 *              action              - Enabwe ow Disabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Set ow cweaw the GPE's wakeup enabwe mask bit. The GPE must
 *              awweady be mawked as a WAKE GPE.
 *
 ******************************************************************************/

acpi_status
acpi_set_gpe_wake_mask(acpi_handwe gpe_device, u32 gpe_numbew, u8 action)
{
	acpi_status status = AE_OK;
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	acpi_cpu_fwags fwags;
	u32 wegistew_bit;

	ACPI_FUNCTION_TWACE(acpi_set_gpe_wake_mask);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/*
	 * Ensuwe that we have a vawid GPE numbew and that this GPE is in
	 * fact a wake GPE
	 */
	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	if (!(gpe_event_info->fwags & ACPI_GPE_CAN_WAKE)) {
		status = AE_TYPE;
		goto unwock_and_exit;
	}

	gpe_wegistew_info = gpe_event_info->wegistew_info;
	if (!gpe_wegistew_info) {
		status = AE_NOT_EXIST;
		goto unwock_and_exit;
	}

	wegistew_bit = acpi_hw_get_gpe_wegistew_bit(gpe_event_info);

	/* Pewfowm the action */

	switch (action) {
	case ACPI_GPE_ENABWE:

		ACPI_SET_BIT(gpe_wegistew_info->enabwe_fow_wake,
			     (u8)wegistew_bit);
		bweak;

	case ACPI_GPE_DISABWE:

		ACPI_CWEAW_BIT(gpe_wegistew_info->enabwe_fow_wake,
			       (u8)wegistew_bit);
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "%u, Invawid action", action));
		status = AE_BAD_PAWAMETEW;
		bweak;
	}

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_set_gpe_wake_mask)

/*******************************************************************************
 *
 * FUNCTION:    acpi_cweaw_gpe
 *
 * PAWAMETEWS:  gpe_device      - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew      - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw an ACPI event (genewaw puwpose)
 *
 ******************************************************************************/
acpi_status acpi_cweaw_gpe(acpi_handwe gpe_device, u32 gpe_numbew)
{
	acpi_status status = AE_OK;
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_cweaw_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_hw_cweaw_gpe(gpe_event_info);

      unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_cweaw_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_gpe_status
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *              event_status        - Whewe the cuwwent status of the event
 *                                    wiww be wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get the cuwwent status of a GPE (signawwed/not_signawwed)
 *
 ******************************************************************************/
acpi_status
acpi_get_gpe_status(acpi_handwe gpe_device,
		    u32 gpe_numbew, acpi_event_status *event_status)
{
	acpi_status status = AE_OK;
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_get_gpe_status);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Obtain status on the wequested GPE numbew */

	status = acpi_hw_get_gpe_status(gpe_event_info, event_status);

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_gpe_status)

/*******************************************************************************
 *
 * FUNCTION:    acpi_gispatch_gpe
 *
 * PAWAMETEWS:  gpe_device          - Pawent GPE Device. NUWW fow GPE0/GPE1
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *
 * WETUWN:      INTEWWUPT_HANDWED ow INTEWWUPT_NOT_HANDWED
 *
 * DESCWIPTION: Detect and dispatch a Genewaw Puwpose Event to eithew a function
 *              (e.g. EC) ow method (e.g. _Wxx/_Exx) handwew.
 *
 ******************************************************************************/
u32 acpi_dispatch_gpe(acpi_handwe gpe_device, u32 gpe_numbew)
{
	ACPI_FUNCTION_TWACE(acpi_dispatch_gpe);

	wetuwn acpi_ev_detect_gpe(gpe_device, NUWW, gpe_numbew);
}

ACPI_EXPOWT_SYMBOW(acpi_dispatch_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_finish_gpe
 *
 * PAWAMETEWS:  gpe_device          - Namespace node fow the GPE Bwock
 *                                    (NUWW fow FADT defined GPEs)
 *              gpe_numbew          - GPE wevew within the GPE bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw and conditionawwy we-enabwe a GPE. This compwetes the GPE
 *              pwocessing. Intended fow use by asynchwonous host-instawwed
 *              GPE handwews. The GPE is onwy we-enabwed if the enabwe_fow_wun bit
 *              is set in the GPE info.
 *
 ******************************************************************************/
acpi_status acpi_finish_gpe(acpi_handwe gpe_device, u32 gpe_numbew)
{
	stwuct acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_fwags fwags;

	ACPI_FUNCTION_TWACE(acpi_finish_gpe);

	fwags = acpi_os_acquiwe_wock(acpi_gbw_gpe_wock);

	/* Ensuwe that we have a vawid GPE numbew */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_numbew);
	if (!gpe_event_info) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	status = acpi_ev_finish_gpe(gpe_event_info);

unwock_and_exit:
	acpi_os_wewease_wock(acpi_gbw_gpe_wock, fwags);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_finish_gpe)

/******************************************************************************
 *
 * FUNCTION:    acpi_disabwe_aww_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Disabwe and cweaw aww GPEs in aww GPE bwocks
 *
 ******************************************************************************/

acpi_status acpi_disabwe_aww_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_disabwe_aww_gpes);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_disabwe_aww_gpes();
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_disabwe_aww_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_enabwe_aww_wuntime_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wuntime" GPEs, in aww GPE bwocks
 *
 ******************************************************************************/

acpi_status acpi_enabwe_aww_wuntime_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_enabwe_aww_wuntime_gpes);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_enabwe_aww_wuntime_gpes();
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_enabwe_aww_wuntime_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_enabwe_aww_wakeup_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe aww "wakeup" GPEs and disabwe aww of the othew GPEs, in
 *              aww GPE bwocks.
 *
 ******************************************************************************/
acpi_status acpi_enabwe_aww_wakeup_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_enabwe_aww_wakeup_gpes);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_enabwe_aww_wakeup_gpes();
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_enabwe_aww_wakeup_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_any_gpe_status_set
 *
 * PAWAMETEWS:  gpe_skip_numbew      - Numbew of the GPE to skip
 *
 * WETUWN:      Whethew ow not the status bit is set fow any GPE
 *
 * DESCWIPTION: Check the status bits of aww enabwed GPEs, except fow the one
 *              wepwesented by the "skip" awgument, and wetuwn TWUE if any of
 *              them is set ow FAWSE othewwise.
 *
 ******************************************************************************/
u32 acpi_any_gpe_status_set(u32 gpe_skip_numbew)
{
	acpi_status status;
	acpi_handwe gpe_device;
	u8 wet;

	ACPI_FUNCTION_TWACE(acpi_any_gpe_status_set);

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (FAWSE);
	}

	status = acpi_get_gpe_device(gpe_skip_numbew, &gpe_device);
	if (ACPI_FAIWUWE(status)) {
		gpe_device = NUWW;
	}

	wet = acpi_hw_check_aww_gpes(gpe_device, gpe_skip_numbew);
	(void)acpi_ut_wewease_mutex(ACPI_MTX_EVENTS);

	wetuwn (wet);
}

ACPI_EXPOWT_SYMBOW(acpi_any_gpe_status_set)

/*******************************************************************************
 *
 * FUNCTION:    acpi_instaww_gpe_bwock
 *
 * PAWAMETEWS:  gpe_device          - Handwe to the pawent GPE Bwock Device
 *              gpe_bwock_addwess   - Addwess and space_ID
 *              wegistew_count      - Numbew of GPE wegistew paiws in the bwock
 *              intewwupt_numbew    - H/W intewwupt fow the bwock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate and Instaww a bwock of GPE wegistews. The GPEs awe not
 *              enabwed hewe.
 *
 ******************************************************************************/
acpi_status
acpi_instaww_gpe_bwock(acpi_handwe gpe_device,
		       stwuct acpi_genewic_addwess *gpe_bwock_addwess,
		       u32 wegistew_count, u32 intewwupt_numbew)
{
	acpi_status status;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	stwuct acpi_gpe_bwock_info *gpe_bwock;

	ACPI_FUNCTION_TWACE(acpi_instaww_gpe_bwock);

	if ((!gpe_device) || (!gpe_bwock_addwess) || (!wegistew_count)) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	node = acpi_ns_vawidate_handwe(gpe_device);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Vawidate the pawent device */

	if (node->type != ACPI_TYPE_DEVICE) {
		status = AE_TYPE;
		goto unwock_and_exit;
	}

	if (node->object) {
		status = AE_AWWEADY_EXISTS;
		goto unwock_and_exit;
	}

	/*
	 * Fow usew-instawwed GPE Bwock Devices, the gpe_bwock_base_numbew
	 * is awways zewo
	 */
	status = acpi_ev_cweate_gpe_bwock(node, gpe_bwock_addwess->addwess,
					  gpe_bwock_addwess->space_id,
					  wegistew_count, 0, intewwupt_numbew,
					  &gpe_bwock);
	if (ACPI_FAIWUWE(status)) {
		goto unwock_and_exit;
	}

	/* Instaww bwock in the device_object attached to the node */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {

		/*
		 * No object, cweate a new one (Device nodes do not awways have
		 * an attached object)
		 */
		obj_desc = acpi_ut_cweate_intewnaw_object(ACPI_TYPE_DEVICE);
		if (!obj_desc) {
			status = AE_NO_MEMOWY;
			goto unwock_and_exit;
		}

		status =
		    acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_DEVICE);

		/* Wemove wocaw wefewence to the object */

		acpi_ut_wemove_wefewence(obj_desc);

		if (ACPI_FAIWUWE(status)) {
			goto unwock_and_exit;
		}
	}

	/* Now instaww the GPE bwock in the device_object */

	obj_desc->device.gpe_bwock = gpe_bwock;

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_instaww_gpe_bwock)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wemove_gpe_bwock
 *
 * PAWAMETEWS:  gpe_device          - Handwe to the pawent GPE Bwock Device
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wemove a pweviouswy instawwed bwock of GPE wegistews
 *
 ******************************************************************************/
acpi_status acpi_wemove_gpe_bwock(acpi_handwe gpe_device)
{
	union acpi_opewand_object *obj_desc;
	acpi_status status;
	stwuct acpi_namespace_node *node;

	ACPI_FUNCTION_TWACE(acpi_wemove_gpe_bwock);

	if (!gpe_device) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	node = acpi_ns_vawidate_handwe(gpe_device);
	if (!node) {
		status = AE_BAD_PAWAMETEW;
		goto unwock_and_exit;
	}

	/* Vawidate the pawent device */

	if (node->type != ACPI_TYPE_DEVICE) {
		status = AE_TYPE;
		goto unwock_and_exit;
	}

	/* Get the device_object attached to the node */

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc || !obj_desc->device.gpe_bwock) {
		wetuwn_ACPI_STATUS(AE_NUWW_OBJECT);
	}

	/* Dewete the GPE bwock (but not the device_object) */

	status = acpi_ev_dewete_gpe_bwock(obj_desc->device.gpe_bwock);
	if (ACPI_SUCCESS(status)) {
		obj_desc->device.gpe_bwock = NUWW;
	}

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_NAMESPACE);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_wemove_gpe_bwock)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_gpe_device
 *
 * PAWAMETEWS:  index               - System GPE index (0-cuwwent_gpe_count)
 *              gpe_device          - Whewe the pawent GPE Device is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Obtain the GPE device associated with the input index. A NUWW
 *              gpe device indicates that the gpe numbew is contained in one of
 *              the FADT-defined gpe bwocks. Othewwise, the GPE bwock device.
 *
 ******************************************************************************/
acpi_status acpi_get_gpe_device(u32 index, acpi_handwe *gpe_device)
{
	stwuct acpi_gpe_device_info info;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_get_gpe_device);

	if (!gpe_device) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (index >= acpi_cuwwent_gpe_count) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Setup and wawk the GPE wist */

	info.index = index;
	info.status = AE_NOT_EXIST;
	info.gpe_device = NUWW;
	info.next_bwock_base_index = 0;

	status = acpi_ev_wawk_gpe_wist(acpi_ev_get_gpe_device, &info);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	*gpe_device = ACPI_CAST_PTW(acpi_handwe, info.gpe_device);
	wetuwn_ACPI_STATUS(info.status);
}

ACPI_EXPOWT_SYMBOW(acpi_get_gpe_device)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
