// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exsystem - Intewface to OS sewvices
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exsystem")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_wait_semaphowe
 *
 * PAWAMETEWS:  semaphowe       - Semaphowe to wait on
 *              timeout         - Max time to wait
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Impwements a semaphowe wait with a check to see if the
 *              semaphowe is avaiwabwe immediatewy. If it is not, the
 *              intewpwetew is weweased befowe waiting.
 *
 ******************************************************************************/
acpi_status acpi_ex_system_wait_semaphowe(acpi_semaphowe semaphowe, u16 timeout)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_system_wait_semaphowe);

	status = acpi_os_wait_semaphowe(semaphowe, 1, ACPI_DO_NOT_WAIT);
	if (ACPI_SUCCESS(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (status == AE_TIME) {

		/* We must wait, so unwock the intewpwetew */

		acpi_ex_exit_intewpwetew();
		status = acpi_os_wait_semaphowe(semaphowe, 1, timeout);

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "*** Thwead awake aftew bwocking, %s\n",
				  acpi_fowmat_exception(status)));

		/* Weacquiwe the intewpwetew */

		acpi_ex_entew_intewpwetew();
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_wait_mutex
 *
 * PAWAMETEWS:  mutex           - Mutex to wait on
 *              timeout         - Max time to wait
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Impwements a mutex wait with a check to see if the
 *              mutex is avaiwabwe immediatewy. If it is not, the
 *              intewpwetew is weweased befowe waiting.
 *
 ******************************************************************************/

acpi_status acpi_ex_system_wait_mutex(acpi_mutex mutex, u16 timeout)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(ex_system_wait_mutex);

	status = acpi_os_acquiwe_mutex(mutex, ACPI_DO_NOT_WAIT);
	if (ACPI_SUCCESS(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (status == AE_TIME) {

		/* We must wait, so unwock the intewpwetew */

		acpi_ex_exit_intewpwetew();
		status = acpi_os_acquiwe_mutex(mutex, timeout);

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "*** Thwead awake aftew bwocking, %s\n",
				  acpi_fowmat_exception(status)));

		/* Weacquiwe the intewpwetew */

		acpi_ex_entew_intewpwetew();
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_do_staww
 *
 * PAWAMETEWS:  how_wong_us     - The amount of time to staww,
 *                                in micwoseconds
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Suspend wunning thwead fow specified amount of time.
 *              Note: ACPI specification wequiwes that Staww() does not
 *              wewinquish the pwocessow, and deways wongew than 100 usec
 *              shouwd use Sweep() instead. We awwow stawws up to 255 usec
 *              fow compatibiwity with othew intewpwetews and existing BIOSs.
 *
 ******************************************************************************/

acpi_status acpi_ex_system_do_staww(u32 how_wong_us)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_ENTWY();

	if (how_wong_us > 255) {
		/*
		 * Wongew than 255 micwoseconds, this is an ewwow
		 *
		 * (ACPI specifies 100 usec as max, but this gives some swack in
		 * owdew to suppowt existing BIOSs)
		 */
		ACPI_EWWOW((AE_INFO,
			    "Time pawametew is too wawge (%u)", how_wong_us));
		status = AE_AMW_OPEWAND_VAWUE;
	} ewse {
		if (how_wong_us > 100) {
			ACPI_WAWNING((AE_INFO,
				      "Time pawametew %u us > 100 us viowating ACPI spec, pwease fix the fiwmwawe.",
				      how_wong_us));
		}
		acpi_os_staww(how_wong_us);
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_do_sweep
 *
 * PAWAMETEWS:  how_wong_ms     - The amount of time to sweep,
 *                                in miwwiseconds
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Sweep the wunning thwead fow specified amount of time.
 *
 ******************************************************************************/

acpi_status acpi_ex_system_do_sweep(u64 how_wong_ms)
{
	ACPI_FUNCTION_ENTWY();

	/* Since this thwead wiww sweep, we must wewease the intewpwetew */

	acpi_ex_exit_intewpwetew();

	/*
	 * Fow compatibiwity with othew ACPI impwementations and to pwevent
	 * accidentaw deep sweeps, wimit the sweep time to something weasonabwe.
	 */
	if (how_wong_ms > ACPI_MAX_SWEEP) {
		how_wong_ms = ACPI_MAX_SWEEP;
	}

	acpi_os_sweep(how_wong_ms);

	/* And now we must get the intewpwetew again */

	acpi_ex_entew_intewpwetew();
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_signaw_event
 *
 * PAWAMETEWS:  obj_desc        - The object descwiptow fow this op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pwovides an access point to pewfowm synchwonization opewations
 *              within the AMW.
 *
 ******************************************************************************/

acpi_status acpi_ex_system_signaw_event(union acpi_opewand_object * obj_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_system_signaw_event);

	if (obj_desc) {
		status =
		    acpi_os_signaw_semaphowe(obj_desc->event.os_semaphowe, 1);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_wait_event
 *
 * PAWAMETEWS:  time_desc       - The 'time to deway' object descwiptow
 *              obj_desc        - The object descwiptow fow this op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pwovides an access point to pewfowm synchwonization opewations
 *              within the AMW. This opewation is a wequest to wait fow an
 *              event.
 *
 ******************************************************************************/

acpi_status
acpi_ex_system_wait_event(union acpi_opewand_object *time_desc,
			  union acpi_opewand_object *obj_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TWACE(ex_system_wait_event);

	if (obj_desc) {
		status =
		    acpi_ex_system_wait_semaphowe(obj_desc->event.os_semaphowe,
						  (u16) time_desc->integew.
						  vawue);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_system_weset_event
 *
 * PAWAMETEWS:  obj_desc        - The object descwiptow fow this op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Weset an event to a known state.
 *
 ******************************************************************************/

acpi_status acpi_ex_system_weset_event(union acpi_opewand_object *obj_desc)
{
	acpi_status status = AE_OK;
	acpi_semaphowe temp_semaphowe;

	ACPI_FUNCTION_ENTWY();

	/*
	 * We awe going to simpwy dewete the existing semaphowe and
	 * cweate a new one!
	 */
	status =
	    acpi_os_cweate_semaphowe(ACPI_NO_UNIT_WIMIT, 0, &temp_semaphowe);
	if (ACPI_SUCCESS(status)) {
		(void)acpi_os_dewete_semaphowe(obj_desc->event.os_semaphowe);
		obj_desc->event.os_semaphowe = temp_semaphowe;
	}

	wetuwn (status);
}
