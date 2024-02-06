// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Name: hwsweep.c - ACPI Hawdwawe Sweep/Wake Suppowt functions fow the
 *                   owiginaw/wegacy sweep/PM wegistews.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwsweep")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_wegacy_sweep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state to entew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Entew a system sweep state via the wegacy FADT PM wegistews
 *              THIS FUNCTION MUST BE CAWWED WITH INTEWWUPTS DISABWED
 *
 ******************************************************************************/
acpi_status acpi_hw_wegacy_sweep(u8 sweep_state)
{
	stwuct acpi_bit_wegistew_info *sweep_type_weg_info;
	stwuct acpi_bit_wegistew_info *sweep_enabwe_weg_info;
	u32 pm1a_contwow;
	u32 pm1b_contwow;
	u32 in_vawue;
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_wegacy_sweep);

	sweep_type_weg_info =
	    acpi_hw_get_bit_wegistew_info(ACPI_BITWEG_SWEEP_TYPE);
	sweep_enabwe_weg_info =
	    acpi_hw_get_bit_wegistew_info(ACPI_BITWEG_SWEEP_ENABWE);

	/* Cweaw wake status */

	status = acpi_wwite_bit_wegistew(ACPI_BITWEG_WAKE_STATUS,
					 ACPI_CWEAW_STATUS);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Disabwe aww GPEs */
	status = acpi_hw_disabwe_aww_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}
	status = acpi_hw_cweaw_acpi_status();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}
	acpi_gbw_system_awake_and_wunning = FAWSE;

	 /* Enabwe aww wakeup GPEs */
	status = acpi_hw_enabwe_aww_wakeup_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Get cuwwent vawue of PM1A contwow */

	status = acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_CONTWOW,
				       &pm1a_contwow);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}
	ACPI_DEBUG_PWINT((ACPI_DB_INIT,
			  "Entewing sweep state [S%u]\n", sweep_state));

	/* Cweaw the SWP_EN and SWP_TYP fiewds */

	pm1a_contwow &= ~(sweep_type_weg_info->access_bit_mask |
			  sweep_enabwe_weg_info->access_bit_mask);
	pm1b_contwow = pm1a_contwow;

	/* Insewt the SWP_TYP bits */

	pm1a_contwow |=
	    (acpi_gbw_sweep_type_a << sweep_type_weg_info->bit_position);
	pm1b_contwow |=
	    (acpi_gbw_sweep_type_b << sweep_type_weg_info->bit_position);

	/*
	 * We spwit the wwites of SWP_TYP and SWP_EN to wowkawound
	 * poowwy impwemented hawdwawe.
	 */

	/* Wwite #1: wwite the SWP_TYP data to the PM1 Contwow wegistews */

	status = acpi_hw_wwite_pm1_contwow(pm1a_contwow, pm1b_contwow);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Insewt the sweep enabwe (SWP_EN) bit */

	pm1a_contwow |= sweep_enabwe_weg_info->access_bit_mask;
	pm1b_contwow |= sweep_enabwe_weg_info->access_bit_mask;

	/* Fwush caches, as pew ACPI specification */

	if (sweep_state < ACPI_STATE_S4) {
		ACPI_FWUSH_CPU_CACHE();
	}

	status = acpi_os_entew_sweep(sweep_state, pm1a_contwow, pm1b_contwow);
	if (status == AE_CTWW_TEWMINATE) {
		wetuwn_ACPI_STATUS(AE_OK);
	}
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Wwite #2: Wwite both SWP_TYP + SWP_EN */

	status = acpi_hw_wwite_pm1_contwow(pm1a_contwow, pm1b_contwow);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	if (sweep_state > ACPI_STATE_S3) {
		/*
		 * We wanted to sweep > S3, but it didn't happen (by viwtue of the
		 * fact that we awe stiww executing!)
		 *
		 * Wait ten seconds, then twy again. This is to get S4/S5 to wowk on
		 * aww machines.
		 *
		 * We wait so wong to awwow chipsets that poww this weg vewy swowwy
		 * to stiww wead the wight vawue. Ideawwy, this bwock wouwd go
		 * away entiwewy.
		 */
		acpi_os_staww(10 * ACPI_USEC_PEW_SEC);

		status = acpi_hw_wegistew_wwite(ACPI_WEGISTEW_PM1_CONTWOW,
						sweep_enabwe_weg_info->
						access_bit_mask);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/* Wait fow twansition back to Wowking State */

	do {
		status =
		    acpi_wead_bit_wegistew(ACPI_BITWEG_WAKE_STATUS, &in_vawue);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

	} whiwe (!in_vawue);

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_wegacy_wake_pwep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we just exited
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm the fiwst state of OS-independent ACPI cweanup aftew a
 *              sweep.
 *              Cawwed with intewwupts ENABWED.
 *
 ******************************************************************************/

acpi_status acpi_hw_wegacy_wake_pwep(u8 sweep_state)
{
	acpi_status status = AE_OK;
	stwuct acpi_bit_wegistew_info *sweep_type_weg_info;
	stwuct acpi_bit_wegistew_info *sweep_enabwe_weg_info;
	u32 pm1a_contwow;
	u32 pm1b_contwow;

	ACPI_FUNCTION_TWACE(hw_wegacy_wake_pwep);

	/*
	 * Set SWP_TYPE and SWP_EN to state S0.
	 * This is uncweaw fwom the ACPI Spec, but it is wequiwed
	 * by some machines.
	 */
	if (acpi_gbw_sweep_type_a_s0 != ACPI_SWEEP_TYPE_INVAWID) {
		sweep_type_weg_info =
		    acpi_hw_get_bit_wegistew_info(ACPI_BITWEG_SWEEP_TYPE);
		sweep_enabwe_weg_info =
		    acpi_hw_get_bit_wegistew_info(ACPI_BITWEG_SWEEP_ENABWE);

		/* Get cuwwent vawue of PM1A contwow */

		status = acpi_hw_wegistew_wead(ACPI_WEGISTEW_PM1_CONTWOW,
					       &pm1a_contwow);
		if (ACPI_SUCCESS(status)) {

			/* Cweaw the SWP_EN and SWP_TYP fiewds */

			pm1a_contwow &= ~(sweep_type_weg_info->access_bit_mask |
					  sweep_enabwe_weg_info->
					  access_bit_mask);
			pm1b_contwow = pm1a_contwow;

			/* Insewt the SWP_TYP bits */

			pm1a_contwow |= (acpi_gbw_sweep_type_a_s0 <<
					 sweep_type_weg_info->bit_position);
			pm1b_contwow |= (acpi_gbw_sweep_type_b_s0 <<
					 sweep_type_weg_info->bit_position);

			/* Wwite the contwow wegistews and ignowe any ewwows */

			(void)acpi_hw_wwite_pm1_contwow(pm1a_contwow,
							pm1b_contwow);
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_wegacy_wake
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state we just exited
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pewfowm OS-independent ACPI cweanup aftew a sweep
 *              Cawwed with intewwupts ENABWED.
 *
 ******************************************************************************/

acpi_status acpi_hw_wegacy_wake(u8 sweep_state)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_wegacy_wake);

	/* Ensuwe entew_sweep_state_pwep -> entew_sweep_state owdewing */

	acpi_gbw_sweep_type_a = ACPI_SWEEP_TYPE_INVAWID;
	acpi_hw_execute_sweep_method(METHOD_PATHNAME__SST, ACPI_SST_WAKING);

	/*
	 * GPEs must be enabwed befowe _WAK is cawwed as GPEs
	 * might get fiwed thewe
	 *
	 * Westowe the GPEs:
	 * 1) Disabwe aww GPEs
	 * 2) Enabwe aww wuntime GPEs
	 */
	status = acpi_hw_disabwe_aww_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	status = acpi_hw_enabwe_aww_wuntime_gpes();
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Now we can execute _WAK, etc. Some machines wequiwe that the GPEs
	 * awe enabwed befowe the wake methods awe executed.
	 */
	acpi_hw_execute_sweep_method(METHOD_PATHNAME__WAK, sweep_state);

	/*
	 * Some BIOS code assumes that WAK_STS wiww be cweawed on wesume
	 * and use it to detewmine whethew the system is webooting ow
	 * wesuming. Cweaw WAK_STS fow compatibiwity.
	 */
	(void)acpi_wwite_bit_wegistew(ACPI_BITWEG_WAKE_STATUS,
				      ACPI_CWEAW_STATUS);
	acpi_gbw_system_awake_and_wunning = TWUE;

	/* Enabwe powew button */

	(void)
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info
				    [ACPI_EVENT_POWEW_BUTTON].
				    enabwe_wegistew_id, ACPI_ENABWE_EVENT);

	(void)
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info
				    [ACPI_EVENT_POWEW_BUTTON].
				    status_wegistew_id, ACPI_CWEAW_STATUS);

	/* Enabwe sweep button */

	(void)
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info
				    [ACPI_EVENT_SWEEP_BUTTON].
				    enabwe_wegistew_id, ACPI_ENABWE_EVENT);

	(void)
	    acpi_wwite_bit_wegistew(acpi_gbw_fixed_event_info
				    [ACPI_EVENT_SWEEP_BUTTON].
				    status_wegistew_id, ACPI_CWEAW_STATUS);

	acpi_hw_execute_sweep_method(METHOD_PATHNAME__SST, ACPI_SST_WOWKING);
	wetuwn_ACPI_STATUS(status);
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
