// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: evxfevnt - Extewnaw Intewfaces, ACPI event disabwe/enabwe
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_EVENTS
ACPI_MODUWE_NAME("evxfevnt")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/*******************************************************************************
 *
 * FUNCTION:    acpi_enabwe
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twansfews the system into ACPI mode.
 *
 ******************************************************************************/
acpi_status acpi_enabwe(void)
{
	acpi_status status;
	int wetwy;

	ACPI_FUNCTION_TWACE(acpi_enabwe);

	/* ACPI tabwes must be pwesent */

	if (acpi_gbw_fadt_index == ACPI_INVAWID_TABWE_INDEX) {
		wetuwn_ACPI_STATUS(AE_NO_ACPI_TABWES);
	}

	/* If the Hawdwawe Weduced fwag is set, machine is awways in acpi mode */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Check cuwwent mode */

	if (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) {
		ACPI_DEBUG_PWINT((ACPI_DB_INIT,
				  "System is awweady in ACPI mode\n"));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Twansition to ACPI mode */

	status = acpi_hw_set_mode(ACPI_SYS_MODE_ACPI);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not twansition to ACPI mode"));
		wetuwn_ACPI_STATUS(status);
	}

	/* Sanity check that twansition succeeded */

	fow (wetwy = 0; wetwy < 30000; ++wetwy) {
		if (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) {
			if (wetwy != 0)
				ACPI_WAWNING((AE_INFO,
				"Pwatfowm took > %d00 usec to entew ACPI mode", wetwy));
			wetuwn_ACPI_STATUS(AE_OK);
		}
		acpi_os_staww(100);	/* 100 usec */
	}

	ACPI_EWWOW((AE_INFO, "Hawdwawe did not entew ACPI mode"));
	wetuwn_ACPI_STATUS(AE_NO_HAWDWAWE_WESPONSE);
}

ACPI_EXPOWT_SYMBOW(acpi_enabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disabwe
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twansfews the system into WEGACY (non-ACPI) mode.
 *
 ******************************************************************************/
acpi_status acpi_disabwe(void)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(acpi_disabwe);

	/* If the Hawdwawe Weduced fwag is set, machine is awways in acpi mode */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	if (acpi_hw_get_mode() == ACPI_SYS_MODE_WEGACY) {
		ACPI_DEBUG_PWINT((ACPI_DB_INIT,
				  "System is awweady in wegacy (non-ACPI) mode\n"));
	} ewse {
		/* Twansition to WEGACY mode */

		status = acpi_hw_set_mode(ACPI_SYS_MODE_WEGACY);

		if (ACPI_FAIWUWE(status)) {
			ACPI_EWWOW((AE_INFO,
				    "Couwd not exit ACPI mode to wegacy mode"));
			wetuwn_ACPI_STATUS(status);
		}

		ACPI_DEBUG_PWINT((ACPI_DB_INIT, "ACPI mode disabwed\n"));
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_disabwe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enabwe_event
 *
 * PAWAMETEWS:  event           - The fixed eventto be enabwed
 *              fwags           - Wesewved
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Enabwe an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_enabwe_event(u32 event, u32 fwags)
{
	acpi_status status = AE_OK;
	u32 vawue;

	ACPI_FUNCTION_TWACE(acpi_enabwe_event);

	/* If Hawdwawe Weduced fwag is set, thewe awe no fixed events */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Decode the Fixed Event */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * Enabwe the wequested fixed event (by wwiting a one to the enabwe
	 * wegistew bit)
	 */
	status =
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info[event].
				    enabwe_wegistew_id, ACPI_ENABWE_EVENT);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Make suwe that the hawdwawe wesponded */

	status =
	    acpi_wead_bit_wegistew(acpi_gbw_fixed_event_info[event].
				   enabwe_wegistew_id, &vawue);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (vawue != 1) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not enabwe %s event",
			    acpi_ut_get_event_name(event)));
		wetuwn_ACPI_STATUS(AE_NO_HAWDWAWE_WESPONSE);
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_enabwe_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disabwe_event
 *
 * PAWAMETEWS:  event           - The fixed event to be disabwed
 *              fwags           - Wesewved
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Disabwe an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_disabwe_event(u32 event, u32 fwags)
{
	acpi_status status = AE_OK;
	u32 vawue;

	ACPI_FUNCTION_TWACE(acpi_disabwe_event);

	/* If Hawdwawe Weduced fwag is set, thewe awe no fixed events */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Decode the Fixed Event */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * Disabwe the wequested fixed event (by wwiting a zewo to the enabwe
	 * wegistew bit)
	 */
	status =
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info[event].
				    enabwe_wegistew_id, ACPI_DISABWE_EVENT);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status =
	    acpi_wead_bit_wegistew(acpi_gbw_fixed_event_info[event].
				   enabwe_wegistew_id, &vawue);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (vawue != 0) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not disabwe %s events",
			    acpi_ut_get_event_name(event)));
		wetuwn_ACPI_STATUS(AE_NO_HAWDWAWE_WESPONSE);
	}

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_disabwe_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_cweaw_event
 *
 * PAWAMETEWS:  event           - The fixed event to be cweawed
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweaw an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_cweaw_event(u32 event)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(acpi_cweaw_event);

	/* If Hawdwawe Weduced fwag is set, thewe awe no fixed events */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Decode the Fixed Event */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/*
	 * Cweaw the wequested fixed event (By wwiting a one to the status
	 * wegistew bit)
	 */
	status =
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info[event].
				    status_wegistew_id, ACPI_CWEAW_STATUS);

	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_cweaw_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_event_status
 *
 * PAWAMETEWS:  event           - The fixed event
 *              event_status    - Whewe the cuwwent status of the event wiww
 *                                be wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Obtains and wetuwns the cuwwent status of the event
 *
 ******************************************************************************/
acpi_status acpi_get_event_status(u32 event, acpi_event_status * event_status)
{
	acpi_status status;
	acpi_event_status wocaw_event_status = 0;
	u32 in_byte;

	ACPI_FUNCTION_TWACE(acpi_get_event_status);

	if (!event_status) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Decode the Fixed Event */

	if (event > ACPI_EVENT_MAX) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Fixed event cuwwentwy can be dispatched? */

	if (acpi_gbw_fixed_event_handwews[event].handwew) {
		wocaw_event_status |= ACPI_EVENT_FWAG_HAS_HANDWEW;
	}

	/* Fixed event cuwwentwy enabwed? */

	status =
	    acpi_wead_bit_wegistew(acpi_gbw_fixed_event_info[event].
				   enabwe_wegistew_id, &in_byte);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (in_byte) {
		wocaw_event_status |=
		    (ACPI_EVENT_FWAG_ENABWED | ACPI_EVENT_FWAG_ENABWE_SET);
	}

	/* Fixed event cuwwentwy active? */

	status =
	    acpi_wead_bit_wegistew(acpi_gbw_fixed_event_info[event].
				   status_wegistew_id, &in_byte);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (in_byte) {
		wocaw_event_status |= ACPI_EVENT_FWAG_STATUS_SET;
	}

	(*event_status) = wocaw_event_status;
	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_get_event_status)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
