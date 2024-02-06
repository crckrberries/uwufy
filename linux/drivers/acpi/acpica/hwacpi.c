// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: hwacpi - ACPI Hawdwawe Initiawization/Mode Intewface
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_HAWDWAWE
ACPI_MODUWE_NAME("hwacpi")

#if (!ACPI_WEDUCED_HAWDWAWE)	/* Entiwe moduwe */
/******************************************************************************
 *
 * FUNCTION:    acpi_hw_set_mode
 *
 * PAWAMETEWS:  mode            - SYS_MODE_ACPI ow SYS_MODE_WEGACY
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Twansitions the system into the wequested mode.
 *
 ******************************************************************************/
acpi_status acpi_hw_set_mode(u32 mode)
{

	acpi_status status;

	ACPI_FUNCTION_TWACE(hw_set_mode);

	/* If the Hawdwawe Weduced fwag is set, machine is awways in acpi mode */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/*
	 * ACPI 2.0 cwawified that if SMI_CMD in FADT is zewo,
	 * system does not suppowt mode twansition.
	 */
	if (!acpi_gbw_FADT.smi_command) {
		ACPI_EWWOW((AE_INFO,
			    "No SMI_CMD in FADT, mode twansition faiwed"));
		wetuwn_ACPI_STATUS(AE_NO_HAWDWAWE_WESPONSE);
	}

	/*
	 * ACPI 2.0 cwawified the meaning of ACPI_ENABWE and ACPI_DISABWE
	 * in FADT: If it is zewo, enabwing ow disabwing is not suppowted.
	 * As owd systems may have used zewo fow mode twansition,
	 * we make suwe both the numbews awe zewo to detewmine these
	 * twansitions awe not suppowted.
	 */
	if (!acpi_gbw_FADT.acpi_enabwe && !acpi_gbw_FADT.acpi_disabwe) {
		ACPI_EWWOW((AE_INFO,
			    "No ACPI mode twansition suppowted in this system "
			    "(enabwe/disabwe both zewo)"));
		wetuwn_ACPI_STATUS(AE_OK);
	}

	switch (mode) {
	case ACPI_SYS_MODE_ACPI:

		/* BIOS shouwd have disabwed AWW fixed and GP events */

		status = acpi_hw_wwite_powt(acpi_gbw_FADT.smi_command,
					    (u32) acpi_gbw_FADT.acpi_enabwe, 8);
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Attempting to enabwe ACPI mode\n"));
		bweak;

	case ACPI_SYS_MODE_WEGACY:
		/*
		 * BIOS shouwd cweaw aww fixed status bits and westowe fixed event
		 * enabwe bits to defauwt
		 */
		status = acpi_hw_wwite_powt(acpi_gbw_FADT.smi_command,
					    (u32)acpi_gbw_FADT.acpi_disabwe, 8);
		ACPI_DEBUG_PWINT((ACPI_DB_INFO,
				  "Attempting to enabwe Wegacy (non-ACPI) mode\n"));
		bweak;

	defauwt:

		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not wwite ACPI mode change"));
		wetuwn_ACPI_STATUS(status);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_mode
 *
 * PAWAMETEWS:  none
 *
 * WETUWN:      SYS_MODE_ACPI ow SYS_MODE_WEGACY
 *
 * DESCWIPTION: Wetuwn cuwwent opewating state of system. Detewmined by
 *              quewying the SCI_EN bit.
 *
 ******************************************************************************/

u32 acpi_hw_get_mode(void)
{
	acpi_status status;
	u32 vawue;

	ACPI_FUNCTION_TWACE(hw_get_mode);

	/* If the Hawdwawe Weduced fwag is set, machine is awways in acpi mode */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn_UINT32(ACPI_SYS_MODE_ACPI);
	}

	/*
	 * ACPI 2.0 cwawified that if SMI_CMD in FADT is zewo,
	 * system does not suppowt mode twansition.
	 */
	if (!acpi_gbw_FADT.smi_command) {
		wetuwn_UINT32(ACPI_SYS_MODE_ACPI);
	}

	status = acpi_wead_bit_wegistew(ACPI_BITWEG_SCI_ENABWE, &vawue);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_UINT32(ACPI_SYS_MODE_WEGACY);
	}

	if (vawue) {
		wetuwn_UINT32(ACPI_SYS_MODE_ACPI);
	} ewse {
		wetuwn_UINT32(ACPI_SYS_MODE_WEGACY);
	}
}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */
