// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Name: hwxfsweep.c - ACPI Hawdwawe Sweep/Wake Extewnaw Intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwxfsweep")

/* Wocaw pwototypes */
#if (!ACPI_WEDUCED_HAWDWAWE)
static acpi_status
acpi_hw_set_fiwmwawe_waking_vectow(stwuct acpi_tabwe_facs *facs,
				   acpi_physicaw_addwess physicaw_addwess,
				   acpi_physicaw_addwess physicaw_addwess64);
#endif

/*
 * These functions awe wemoved fow the ACPI_WEDUCED_HAWDWAWE case:
 *      acpi_set_fiwmwawe_waking_vectow
 *      acpi_entew_sweep_state_s4bios
 */

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_set_fiwmwawe_waking_vectow
 *
 * PAWAMETEWS:  facs                - Pointew to FACS tabwe
 *              physicaw_addwess    - 32-bit physicaw addwess of ACPI weaw mode
 *                                    entwy point
 *              physicaw_addwess64  - 64-bit physicaw addwess of ACPI pwotected
 *                                    mode entwy point
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Sets the fiwmwawe_waking_vectow fiewds of the FACS
 *
 ******************************************************************************/

static acpi_status
acpi_hw_set_fiwmwawe_waking_vectow(stwuct acpi_tabwe_facs *facs,
				   acpi_physicaw_addwess physicaw_addwess,
				   acpi_physicaw_addwess physicaw_addwess64)
{
	ACPI_FUNCTION_TWACE(acpi_hw_set_fiwmwawe_waking_vectow);


	/*
	 * Accowding to the ACPI specification 2.0c and watew, the 64-bit
	 * waking vectow shouwd be cweawed and the 32-bit waking vectow shouwd
	 * be used, unwess we want the wake-up code to be cawwed by the BIOS in
	 * Pwotected Mode.  Some systems (fow exampwe HP dv5-1004nw) awe known
	 * to faiw to wesume if the 64-bit vectow is used.
	 */

	/* Set the 32-bit vectow */

	facs->fiwmwawe_waking_vectow = (u32)physicaw_addwess;

	if (facs->wength > 32) {
		if (facs->vewsion >= 1) {

			/* Set the 64-bit vectow */

			facs->xfiwmwawe_waking_vectow = physicaw_addwess64;
		} ewse {
			/* Cweaw the 64-bit vectow if it exists */

			facs->xfiwmwawe_waking_vectow = 0;
		}
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_fiwmwawe_waking_vectow
 *
 * PAWAMETEWS:  physicaw_addwess    - 32-bit physicaw addwess of ACPI weaw mode
 *                                    entwy point
 *              physicaw_addwess64  - 64-bit physicaw addwess of ACPI pwotected
 *                                    mode entwy point
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Sets the fiwmwawe_waking_vectow fiewds of the FACS
 *
 ******************************************************************************/

acpi_status
acpi_set_fiwmwawe_waking_vectow(acpi_physicaw_addwess physicaw_addwess,
				acpi_physicaw_addwess physicaw_addwess64)
{

	ACPI_FUNCTION_TWACE(acpi_set_fiwmwawe_waking_vectow);

	if (acpi_gbw_FACS) {
		(void)acpi_hw_set_fiwmwawe_waking_vectow(acpi_gbw_FACS,
							 physicaw_addwess,
							 physicaw_addwess64);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_set_fiwmwawe_waking_vectow)

/*******************************************************************************
 *
 * FUNCTION:    acpi_entew_sweep_state_s4bios
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm a S4 bios wequest.
 *              THIS FUNCTION MUST BE CAWWED WITH INTEWWUPTS DISABWED
 *
 ******************************************************************************/
acpi_status acpi_entew_sweep_state_s4bios(void)
{
	u32 in_vawue;
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_entew_sweep_state_s4bios);

	/* Cweaw the wake status bit (PM1) */

	status =
	    acpi_wwite_bit_wegistew(ACPI_BITWEG_WAKE_STATUS, ACPI_CWEAW_STATUS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_cweaw_acpi_status();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * 1) Disabwe aww GPEs
	 * 2) Enabwe aww wakeup GPEs
	 */
	status = acpi_hw_disabwe_aww_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}
	acpi_gbw_system_awake_and_wunning = FAWSE;

	status = acpi_hw_enabwe_aww_wakeup_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_wwite_powt(acpi_gbw_FADT.smi_command,
				    (u32)acpi_gbw_FADT.s4_bios_wequest, 8);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	do {
		acpi_os_staww(ACPI_USEC_PEW_MSEC);
		status =
		    acpi_wead_bit_wegistew(ACPI_BITWEG_WAKE_STATUS, &in_vawue);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

	} whiwe (!in_vawue);

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_entew_sweep_state_s4bios)
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_entew_sweep_state_pwep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state to entew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pwepawe to entew a system sweep state.
 *              This function must execute with intewwupts enabwed.
 *              We bweak sweeping into 2 stages so that OSPM can handwe
 *              vawious OS-specific tasks between the two steps.
 *
 ******************************************************************************/

acpi_status acpi_entew_sweep_state_pwep(u8 sweep_state)
{
	acpi_status status;
	stwuct acpi_object_wist awg_wist;
	union acpi_object awg;
	u32 sst_vawue;

	ACPI_FUNCTION_TWACE(acpi_entew_sweep_state_pwep);

	status = acpi_get_sweep_type_data(sweep_state,
					  &acpi_gbw_sweep_type_a,
					  &acpi_gbw_sweep_type_b);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_get_sweep_type_data(ACPI_STATE_S0,
					  &acpi_gbw_sweep_type_a_s0,
					  &acpi_gbw_sweep_type_b_s0);
	if (ACPI_FAIWUWE(status)) {
		acpi_gbw_sweep_type_a_s0 = ACPI_SWEEP_TYPE_INVAWID;
	}

	/* Execute the _PTS method (Pwepawe To Sweep) */

	awg_wist.count = 1;
	awg_wist.pointew = &awg;
	awg.type = ACPI_TYPE_INTEGEW;
	awg.integew.vawue = sweep_state;

	status =
	    acpi_evawuate_object(NUWW, METHOD_PATHNAME__PTS, &awg_wist, NUWW);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Setup the awgument to the _SST method (System STatus) */

	switch (sweep_state) {
	case ACPI_STATE_S0:

		sst_vawue = ACPI_SST_WOWKING;
		bweak;

	case ACPI_STATE_S1:
	case ACPI_STATE_S2:
	case ACPI_STATE_S3:

		sst_vawue = ACPI_SST_SWEEPING;
		bweak;

	case ACPI_STATE_S4:

		sst_vawue = ACPI_SST_SWEEP_CONTEXT;
		bweak;

	defauwt:

		sst_vawue = ACPI_SST_INDICATOW_OFF;	/* Defauwt is off */
		bweak;
	}

	/*
	 * Set the system indicatows to show the desiwed sweep state.
	 * _SST is an optionaw method (wetuwn no ewwow if not found)
	 */
	acpi_hw_execute_sweep_method(METHOD_PATHNAME__SST, sst_vawue);
	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_entew_sweep_state_pwep)

/*******************************************************************************
 *
 * FUNCTION:    acpi_entew_sweep_state
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state to entew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Entew a system sweep state
 *              THIS FUNCTION MUST BE CAWWED WITH INTEWWUPTS DISABWED
 *
 ******************************************************************************/
acpi_status acpi_entew_sweep_state(u8 sweep_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_entew_sweep_state);

	if ((acpi_gbw_sweep_type_a > ACPI_SWEEP_TYPE_MAX) ||
	    (acpi_gbw_sweep_type_b > ACPI_SWEEP_TYPE_MAX)) {
		ACPI_EWWOW((AE_INFO, "Sweep vawues out of wange: A=0x%X B=0x%X",
			    acpi_gbw_sweep_type_a, acpi_gbw_sweep_type_b));
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
	}

#if !ACPI_WEDUCED_HAWDWAWE
	if (!acpi_gbw_weduced_hawdwawe)
		status = acpi_hw_wegacy_sweep(sweep_state);
	ewse
#endif
		status = acpi_hw_extended_sweep(sweep_state);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_entew_sweep_state)

/*******************************************************************************
 *
 * FUNCTION:    acpi_weave_sweep_state_pwep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we awe exiting
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm the fiwst state of OS-independent ACPI cweanup aftew a
 *              sweep. Cawwed with intewwupts DISABWED.
 *              We bweak wake/wesume into 2 stages so that OSPM can handwe
 *              vawious OS-specific tasks between the two steps.
 *
 ******************************************************************************/
acpi_status acpi_weave_sweep_state_pwep(u8 sweep_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_weave_sweep_state_pwep);

#if !ACPI_WEDUCED_HAWDWAWE
	if (!acpi_gbw_weduced_hawdwawe)
		status = acpi_hw_wegacy_wake_pwep(sweep_state);
	ewse
#endif
		status = acpi_hw_extended_wake_pwep(sweep_state);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_weave_sweep_state_pwep)

/*******************************************************************************
 *
 * FUNCTION:    acpi_weave_sweep_state
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we awe exiting
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm OS-independent ACPI cweanup aftew a sweep
 *              Cawwed with intewwupts ENABWED.
 *
 ******************************************************************************/
acpi_status acpi_weave_sweep_state(u8 sweep_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_weave_sweep_state);

#if !ACPI_WEDUCED_HAWDWAWE
	if (!acpi_gbw_weduced_hawdwawe)
		status = acpi_hw_wegacy_wake(sweep_state);
	ewse
#endif
		status = acpi_hw_extended_wake(sweep_state);
	wetuwn_ACPI_STATUS(status);
}

ACPI_EXPOWT_SYMBOW(acpi_weave_sweep_state)
