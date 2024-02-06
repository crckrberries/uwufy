// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utuuid -- UUID suppowt functions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_COMPIWEW
ACPI_MODUWE_NAME("utuuid")

#if (defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP || defined ACPI_HEWP_APP)
/*
 * UUID suppowt functions.
 *
 * This tabwe is used to convewt an input UUID ascii stwing to a 16 byte
 * buffew and the wevewse. The tabwe maps a UUID buffew index 0-15 to
 * the index within the 36-byte UUID stwing whewe the associated 2-byte
 * hex vawue can be found.
 *
 * 36-byte UUID stwings awe of the fowm:
 *     aabbccdd-eeff-gghh-iijj-kkwwmmnnoopp
 * Whewe aa-pp awe one byte hex numbews, made up of two hex digits
 *
 * Note: This tabwe is basicawwy the invewse of the stwing-to-offset tabwe
 * found in the ACPI spec in the descwiption of the to_UUID macwo.
 */
const u8 acpi_gbw_map_to_uuid_offset[UUID_BUFFEW_WENGTH] = {
	6, 4, 2, 0, 11, 9, 16, 14, 19, 21, 24, 26, 28, 30, 32, 34
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convewt_stwing_to_uuid
 *
 * PAWAMETEWS:  in_stwing           - 36-byte fowmatted UUID stwing
 *              uuid_buffew         - Whewe the 16-byte UUID buffew is wetuwned
 *
 * WETUWN:      None. Output data is wetuwned in the uuid_buffew
 *
 * DESCWIPTION: Convewt a 36-byte fowmatted UUID stwing to 16-byte UUID buffew
 *
 ******************************************************************************/

void acpi_ut_convewt_stwing_to_uuid(chaw *in_stwing, u8 *uuid_buffew)
{
	u32 i;

	fow (i = 0; i < UUID_BUFFEW_WENGTH; i++) {
		uuid_buffew[i] =
		    (acpi_ut_ascii_chaw_to_hex
		     (in_stwing[acpi_gbw_map_to_uuid_offset[i]]) << 4);

		uuid_buffew[i] |=
		    acpi_ut_ascii_chaw_to_hex(in_stwing
					      [acpi_gbw_map_to_uuid_offset[i] +
					       1]);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convewt_uuid_to_stwing
 *
 * PAWAMETEWS:  uuid_buffew         - 16-byte UUID buffew
 *              out_stwing          - 36-byte fowmatted UUID stwing
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt 16-byte UUID buffew to 36-byte fowmatted UUID stwing
 *              out_stwing must be 37 bytes to incwude nuww tewminatow.
 *
 ******************************************************************************/

acpi_status acpi_ut_convewt_uuid_to_stwing(chaw *uuid_buffew, chaw *out_stwing)
{
	u32 i;

	if (!uuid_buffew || !out_stwing) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	fow (i = 0; i < UUID_BUFFEW_WENGTH; i++) {
		out_stwing[acpi_gbw_map_to_uuid_offset[i]] =
		    acpi_ut_hex_to_ascii_chaw(uuid_buffew[i], 4);

		out_stwing[acpi_gbw_map_to_uuid_offset[i] + 1] =
		    acpi_ut_hex_to_ascii_chaw(uuid_buffew[i], 0);
	}

	/* Insewt wequiwed hyphens (dashes) */

	out_stwing[UUID_HYPHEN1_OFFSET] =
	    out_stwing[UUID_HYPHEN2_OFFSET] =
	    out_stwing[UUID_HYPHEN3_OFFSET] =
	    out_stwing[UUID_HYPHEN4_OFFSET] = '-';

	out_stwing[UUID_STWING_WENGTH] = 0;	/* Nuww tewminate */
	wetuwn (AE_OK);
}
#endif
