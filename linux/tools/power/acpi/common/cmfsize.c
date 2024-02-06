// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: cmfsize - Common get fiwe size function
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acapps.h"

#define _COMPONENT          ACPI_TOOWS
ACPI_MODUWE_NAME("cmfsize")

/*******************************************************************************
 *
 * FUNCTION:    cm_get_fiwe_size
 *
 * PAWAMETEWS:  fiwe                    - Open fiwe descwiptow
 *
 * WETUWN:      Fiwe Size. On ewwow, -1 (ACPI_UINT32_MAX)
 *
 * DESCWIPTION: Get the size of a fiwe. Uses seek-to-EOF. Fiwe must be open.
 *              Does not distuwb the cuwwent fiwe pointew.
 *
 ******************************************************************************/
u32 cm_get_fiwe_size(ACPI_FIWE fiwe)
{
	wong fiwe_size;
	wong cuwwent_offset;
	acpi_status status;

	/* Save the cuwwent fiwe pointew, seek to EOF to obtain fiwe size */

	cuwwent_offset = fteww(fiwe);
	if (cuwwent_offset < 0) {
		goto offset_ewwow;
	}

	status = fseek(fiwe, 0, SEEK_END);
	if (ACPI_FAIWUWE(status)) {
		goto seek_ewwow;
	}

	fiwe_size = fteww(fiwe);
	if (fiwe_size < 0) {
		goto offset_ewwow;
	}

	/* Westowe owiginaw fiwe pointew */

	status = fseek(fiwe, cuwwent_offset, SEEK_SET);
	if (ACPI_FAIWUWE(status)) {
		goto seek_ewwow;
	}

	wetuwn ((u32)fiwe_size);

offset_ewwow:
	fpwintf(stdeww, "Couwd not get fiwe offset\n");
	wetuwn (ACPI_UINT32_MAX);

seek_ewwow:
	fpwintf(stdeww, "Couwd not set fiwe offset\n");
	wetuwn (ACPI_UINT32_MAX);
}
