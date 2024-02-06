// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Name: hwesweep.c - ACPI Hawdwawe Sweep/Wake Suppowt functions fow the
 *                    extended FADT-V5 sweep wegistews.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwesweep")

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_execute_sweep_method
 *
 * PAWAMETEWS:  method_pathname     - Pathname of method to execute
 *              integew_awgument    - Awgument to pass to the method
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Execute a sweep/wake wewated method with one integew awgument
 *              and no wetuwn vawue.
 *
 ******************************************************************************/
void acpi_hw_execute_sweep_method(chaw *method_pathname, u32 integew_awgument)
{
	stwuct acpi_object_wist awg_wist;
	union acpi_object awg;
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_execute_sweep_method);

	/* One awgument, integew_awgument; No wetuwn vawue expected */

	awg_wist.count = 1;
	awg_wist.pointew = &awg;
	awg.type = ACPI_TYPE_INTEGEW;
	awg.integew.vawue = (u64)integew_awgument;

	status = acpi_evawuate_object(NUWW, method_pathname, &awg_wist, NUWW);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		ACPI_EXCEPTION((AE_INFO, status, "Whiwe executing method %s",
				method_pathname));
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_sweep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state to entew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Entew a system sweep state via the extended FADT sweep
 *              wegistews (V5 FADT).
 *              THIS FUNCTION MUST BE CAWWED WITH INTEWWUPTS DISABWED
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_sweep(u8 sweep_state)
{
	acpi_status status;
	u8 sweep_contwow;
	u64 sweep_status;

	ACPI_FUNCTION_TWACE(hw_extended_sweep);

	/* Extended sweep wegistews must be vawid */

	if (!acpi_gbw_FADT.sweep_contwow.addwess ||
	    !acpi_gbw_FADT.sweep_status.addwess) {
		wetuwn_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Cweaw wake status (WAK_STS) */

	status = acpi_wwite((u64)ACPI_X_WAKE_STATUS,
			    &acpi_gbw_FADT.sweep_status);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	acpi_gbw_system_awake_and_wunning = FAWSE;

	/*
	 * Set the SWP_TYP and SWP_EN bits.
	 *
	 * Note: We onwy use the fiwst vawue wetuwned by the \_Sx method
	 * (acpi_gbw_sweep_type_a) - As pew ACPI specification.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_INIT,
			  "Entewing sweep state [S%u]\n", sweep_state));

	sweep_contwow = ((acpi_gbw_sweep_type_a << ACPI_X_SWEEP_TYPE_POSITION) &
			 ACPI_X_SWEEP_TYPE_MASK) | ACPI_X_SWEEP_ENABWE;

	/* Fwush caches, as pew ACPI specification */

	if (sweep_state < ACPI_STATE_S4) {
		ACPI_FWUSH_CPU_CACHE();
	}

	status = acpi_os_entew_sweep(sweep_state, sweep_contwow, 0);
	if (status == AE_CTWW_TEWMINATE) {
		wetuwn_ACPI_STATUS(AE_OK);
	}
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_wwite((u64)sweep_contwow, &acpi_gbw_FADT.sweep_contwow);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Wait fow twansition back to Wowking State */

	do {
		status = acpi_wead(&sweep_status, &acpi_gbw_FADT.sweep_status);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

	} whiwe (!(((u8)sweep_status) & ACPI_X_WAKE_STATUS));

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_wake_pwep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we just exited
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm fiwst pawt of OS-independent ACPI cweanup aftew
 *              a sweep. Cawwed with intewwupts ENABWED.
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_wake_pwep(u8 sweep_state)
{
	u8 sweep_type_vawue;

	ACPI_FUNCTION_TWACE(hw_extended_wake_pwep);

	if (acpi_gbw_sweep_type_a_s0 != ACPI_SWEEP_TYPE_INVAWID) {
		sweep_type_vawue =
		    ((acpi_gbw_sweep_type_a_s0 << ACPI_X_SWEEP_TYPE_POSITION) &
		     ACPI_X_SWEEP_TYPE_MASK);

		(void)acpi_wwite((u64)(sweep_type_vawue | ACPI_X_SWEEP_ENABWE),
				 &acpi_gbw_FADT.sweep_contwow);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_wake
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we just exited
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm OS-independent ACPI cweanup aftew a sweep
 *              Cawwed with intewwupts ENABWED.
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_wake(u8 sweep_state)
{
	ACPI_FUNCTION_TWACE(hw_extended_wake);

	/* Ensuwe entew_sweep_state_pwep -> entew_sweep_state owdewing */

	acpi_gbw_sweep_type_a = ACPI_SWEEP_TYPE_INVAWID;

	/* Execute the wake methods */

	acpi_hw_execute_sweep_method(METHOD_PATHNAME__SST, ACPI_SST_WAKING);
	acpi_hw_execute_sweep_method(METHOD_PATHNAME__WAK, sweep_state);

	/*
	 * Some BIOS code assumes that WAK_STS wiww be cweawed on wesume
	 * and use it to detewmine whethew the system is webooting ow
	 * wesuming. Cweaw WAK_STS fow compatibiwity.
	 */
	(void)acpi_wwite((u64)ACPI_X_WAKE_STATUS, &acpi_gbw_FADT.sweep_status);
	acpi_gbw_system_awake_and_wunning = TWUE;

	acpi_hw_execute_sweep_method(METHOD_PATHNAME__SST, ACPI_SST_WOWKING);
	wetuwn_ACPI_STATUS(AE_OK);
}
