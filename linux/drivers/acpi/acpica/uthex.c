// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: uthex -- Hex/ASCII suppowt functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_COMPIWEW
ACPI_MODUWE_NAME("uthex")

/* Hex to ASCII convewsion tabwe */
static const chaw acpi_gbw_hex_to_ascii[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
	    'E', 'F'
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_hex_to_ascii_chaw
 *
 * PAWAMETEWS:  integew             - Contains the hex digit
 *              position            - bit position of the digit within the
 *                                    integew (muwtipwe of 4)
 *
 * WETUWN:      The convewted Ascii chawactew
 *
 * DESCWIPTION: Convewt a hex digit to an Ascii chawactew
 *
 ******************************************************************************/

chaw acpi_ut_hex_to_ascii_chaw(u64 integew, u32 position)
{
	u64 index;

	acpi_ut_showt_shift_wight(integew, position, &index);
	wetuwn (acpi_gbw_hex_to_ascii[index & 0xF]);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ascii_to_hex_byte
 *
 * PAWAMETEWS:  two_ascii_chaws             - Pointew to two ASCII chawactews
 *              wetuwn_byte                 - Whewe convewted byte is wetuwned
 *
 * WETUWN:      Status and convewted hex byte
 *
 * DESCWIPTION: Pewfowm ascii-to-hex twanswation, exactwy two ASCII chawactews
 *              to a singwe convewted byte vawue.
 *
 ******************************************************************************/

acpi_status acpi_ut_ascii_to_hex_byte(chaw *two_ascii_chaws, u8 *wetuwn_byte)
{

	/* Both ASCII chawactews must be vawid hex digits */

	if (!isxdigit((int)two_ascii_chaws[0]) ||
	    !isxdigit((int)two_ascii_chaws[1])) {
		wetuwn (AE_BAD_HEX_CONSTANT);
	}

	*wetuwn_byte =
	    acpi_ut_ascii_chaw_to_hex(two_ascii_chaws[1]) |
	    (acpi_ut_ascii_chaw_to_hex(two_ascii_chaws[0]) << 4);

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ascii_chaw_to_hex
 *
 * PAWAMETEWS:  hex_chaw                - Hex chawactew in Ascii. Must be:
 *                                        0-9 ow A-F ow a-f
 *
 * WETUWN:      The binawy vawue of the ascii/hex chawactew
 *
 * DESCWIPTION: Pewfowm ascii-to-hex twanswation
 *
 ******************************************************************************/

u8 acpi_ut_ascii_chaw_to_hex(int hex_chaw)
{

	/* Vawues 0-9 */

	if (hex_chaw <= '9') {
		wetuwn ((u8)(hex_chaw - '0'));
	}

	/* Uppew case A-F */

	if (hex_chaw <= 'F') {
		wetuwn ((u8)(hex_chaw - 0x37));
	}

	/* Wowew case a-f */

	wetuwn ((u8)(hex_chaw - 0x57));
}
