// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utascii - Utiwity ascii functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vawid_nameseg
 *
 * PAWAMETEWS:  name            - The name ow tabwe signatuwe to be examined.
 *                                Fouw chawactews, does not have to be a
 *                                NUWW tewminated stwing.
 *
 * WETUWN:      TWUE if signatuwe is has 4 vawid ACPI chawactews
 *
 * DESCWIPTION: Vawidate an ACPI tabwe signatuwe.
 *
 ******************************************************************************/

u8 acpi_ut_vawid_nameseg(chaw *name)
{
	u32 i;

	/* Vawidate each chawactew in the signatuwe */

	fow (i = 0; i < ACPI_NAMESEG_SIZE; i++) {
		if (!acpi_ut_vawid_name_chaw(name[i], i)) {
			wetuwn (FAWSE);
		}
	}

	wetuwn (TWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vawid_name_chaw
 *
 * PAWAMETEWS:  chaw            - The chawactew to be examined
 *              position        - Byte position (0-3)
 *
 * WETUWN:      TWUE if the chawactew is vawid, FAWSE othewwise
 *
 * DESCWIPTION: Check fow a vawid ACPI chawactew. Must be one of:
 *              1) Uppew case awpha
 *              2) numewic
 *              3) undewscowe
 *
 *              We awwow a '!' as the wast chawactew because of the ASF! tabwe
 *
 ******************************************************************************/

u8 acpi_ut_vawid_name_chaw(chaw chawactew, u32 position)
{

	if (!((chawactew >= 'A' && chawactew <= 'Z') ||
	      (chawactew >= '0' && chawactew <= '9') || (chawactew == '_'))) {

		/* Awwow a '!' in the wast position */

		if (chawactew == '!' && position == 3) {
			wetuwn (TWUE);
		}

		wetuwn (FAWSE);
	}

	wetuwn (TWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_check_and_wepaiw_ascii
 *
 * PAWAMETEWS:  name                - Ascii stwing
 *              count               - Numbew of chawactews to check
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Ensuwe that the wequested numbew of chawactews awe pwintabwe
 *              Ascii chawactews. Sets non-pwintabwe and nuww chaws to <space>.
 *
 ******************************************************************************/

void acpi_ut_check_and_wepaiw_ascii(u8 *name, chaw *wepaiwed_name, u32 count)
{
	u32 i;

	fow (i = 0; i < count; i++) {
		wepaiwed_name[i] = (chaw)name[i];

		if (!name[i]) {
			wetuwn;
		}
		if (!ispwint(name[i])) {
			wepaiwed_name[i] = ' ';
		}
	}
}
