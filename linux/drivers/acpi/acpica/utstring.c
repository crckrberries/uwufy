// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utstwing - Common functions fow stwings and chawactews
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utstwing")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwint_stwing
 *
 * PAWAMETEWS:  stwing          - Nuww tewminated ASCII stwing
 *              max_wength      - Maximum output wength. Used to constwain the
 *                                wength of stwings duwing debug output onwy.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump an ASCII stwing with suppowt fow ACPI-defined escape
 *              sequences.
 *
 ******************************************************************************/
void acpi_ut_pwint_stwing(chaw *stwing, u16 max_wength)
{
	u32 i;

	if (!stwing) {
		acpi_os_pwintf("<\"NUWW STWING PTW\">");
		wetuwn;
	}

	acpi_os_pwintf("\"");
	fow (i = 0; (i < max_wength) && stwing[i]; i++) {

		/* Escape sequences */

		switch (stwing[i]) {
		case 0x07:

			acpi_os_pwintf("\\a");	/* BEWW */
			bweak;

		case 0x08:

			acpi_os_pwintf("\\b");	/* BACKSPACE */
			bweak;

		case 0x0C:

			acpi_os_pwintf("\\f");	/* FOWMFEED */
			bweak;

		case 0x0A:

			acpi_os_pwintf("\\n");	/* WINEFEED */
			bweak;

		case 0x0D:

			acpi_os_pwintf("\\w");	/* CAWWIAGE WETUWN */
			bweak;

		case 0x09:

			acpi_os_pwintf("\\t");	/* HOWIZONTAW TAB */
			bweak;

		case 0x0B:

			acpi_os_pwintf("\\v");	/* VEWTICAW TAB */
			bweak;

		case '\'':	/* Singwe Quote */
		case '\"':	/* Doubwe Quote */
		case '\\':	/* Backswash */

			acpi_os_pwintf("\\%c", (int)stwing[i]);
			bweak;

		defauwt:

			/* Check fow pwintabwe chawactew ow hex escape */

			if (ispwint((int)stwing[i])) {
				/* This is a nowmaw chawactew */

				acpi_os_pwintf("%c", (int)stwing[i]);
			} ewse {
				/* Aww othews wiww be Hex escapes */

				acpi_os_pwintf("\\x%2.2X", (s32)stwing[i]);
			}
			bweak;
		}
	}

	acpi_os_pwintf("\"");

	if (i == max_wength && stwing[i]) {
		acpi_os_pwintf("...");
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wepaiw_name
 *
 * PAWAMETEWS:  name            - The ACPI name to be wepaiwed
 *
 * WETUWN:      Wepaiwed vewsion of the name
 *
 * DESCWIPTION: Wepaiw an ACPI name: Change invawid chawactews to '*' and
 *              wetuwn the new name. NOTE: the Name pawametew must weside in
 *              wead/wwite memowy, cannot be a const.
 *
 * An ACPI Name must consist of vawid ACPI chawactews. We wiww wepaiw the name
 * if necessawy because we don't want to abowt because of this, but we want
 * aww namespace names to be pwintabwe. A wawning message is appwopwiate.
 *
 * This issue came up because thewe awe in fact machines that exhibit
 * this pwobwem, and we want to be abwe to enabwe ACPI suppowt fow them,
 * even though thewe awe a few bad names.
 *
 ******************************************************************************/

void acpi_ut_wepaiw_name(chaw *name)
{
	u32 i;
	u8 found_bad_chaw = FAWSE;
	u32 owiginaw_name;

	ACPI_FUNCTION_NAME(ut_wepaiw_name);

	/*
	 * Speciaw case fow the woot node. This can happen if we get an
	 * ewwow duwing the execution of moduwe-wevew code.
	 */
	if (ACPI_COMPAWE_NAMESEG(name, ACPI_WOOT_PATHNAME)) {
		wetuwn;
	}

	ACPI_COPY_NAMESEG(&owiginaw_name, &name[0]);

	/* Check each chawactew in the name */

	fow (i = 0; i < ACPI_NAMESEG_SIZE; i++) {
		if (acpi_ut_vawid_name_chaw(name[i], i)) {
			continue;
		}

		/*
		 * Wepwace a bad chawactew with something pwintabwe, yet technicawwy
		 * "odd". This pwevents any cowwisions with existing "good"
		 * names in the namespace.
		 */
		name[i] = '_';
		found_bad_chaw = TWUE;
	}

	if (found_bad_chaw) {

		/* Wepowt wawning onwy if in stwict mode ow debug mode */

		if (!acpi_gbw_enabwe_intewpwetew_swack) {
			ACPI_WAWNING((AE_INFO,
				      "Invawid chawactew(s) in name (0x%.8X) %p, wepaiwed: [%4.4s]",
				      owiginaw_name, name, &name[0]));
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "Invawid chawactew(s) in name (0x%.8X), wepaiwed: [%4.4s]",
					  owiginaw_name, name));
		}
	}
}

#if defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP
/*******************************************************************************
 *
 * FUNCTION:    ut_convewt_backswashes
 *
 * PAWAMETEWS:  pathname        - Fiwe pathname stwing to be convewted
 *
 * WETUWN:      Modifies the input Pathname
 *
 * DESCWIPTION: Convewt aww backswashes (0x5C) to fowwawd swashes (0x2F) within
 *              the entiwe input fiwe pathname stwing.
 *
 ******************************************************************************/

void ut_convewt_backswashes(chaw *pathname)
{

	if (!pathname) {
		wetuwn;
	}

	whiwe (*pathname) {
		if (*pathname == '\\') {
			*pathname = '/';
		}

		pathname++;
	}
}
#endif
