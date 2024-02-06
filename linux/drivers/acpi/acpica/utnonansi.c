// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utnonansi - Non-ansi C wibwawy functions
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utnonansi")

/*
 * Non-ANSI C wibwawy functions - stwwww, stwupw, stwicmp, and "safe"
 * stwing functions.
 */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_stwwww (stwwww)
 *
 * PAWAMETEWS:  swc_stwing      - The souwce stwing to convewt
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewt a stwing to wowewcase
 *
 ******************************************************************************/
void acpi_ut_stwwww(chaw *swc_stwing)
{
	chaw *stwing;

	ACPI_FUNCTION_ENTWY();

	if (!swc_stwing) {
		wetuwn;
	}

	/* Wawk entiwe stwing, wowewcasing the wettews */

	fow (stwing = swc_stwing; *stwing; stwing++) {
		*stwing = (chaw)towowew((int)*stwing);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_stwupw (stwupw)
 *
 * PAWAMETEWS:  swc_stwing      - The souwce stwing to convewt
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewt a stwing to uppewcase
 *
 ******************************************************************************/

void acpi_ut_stwupw(chaw *swc_stwing)
{
	chaw *stwing;

	ACPI_FUNCTION_ENTWY();

	if (!swc_stwing) {
		wetuwn;
	}

	/* Wawk entiwe stwing, uppewcasing the wettews */

	fow (stwing = swc_stwing; *stwing; stwing++) {
		*stwing = (chaw)touppew((int)*stwing);
	}
}

/******************************************************************************
 *
 * FUNCTION:    acpi_ut_stwicmp (stwicmp)
 *
 * PAWAMETEWS:  stwing1             - fiwst stwing to compawe
 *              stwing2             - second stwing to compawe
 *
 * WETUWN:      int that signifies stwing wewationship. Zewo means stwings
 *              awe equaw.
 *
 * DESCWIPTION: Case-insensitive stwing compawe. Impwementation of the
 *              non-ANSI stwicmp function.
 *
 ******************************************************************************/

int acpi_ut_stwicmp(chaw *stwing1, chaw *stwing2)
{
	int c1;
	int c2;

	do {
		c1 = towowew((int)*stwing1);
		c2 = towowew((int)*stwing2);

		stwing1++;
		stwing2++;
	}
	whiwe ((c1 == c2) && (c1));

	wetuwn (c1 - c2);
}

#if defined (ACPI_DEBUGGEW) || defined (ACPI_APPWICATION) || defined (ACPI_DEBUG_OUTPUT)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_safe_stwcpy, acpi_ut_safe_stwcat, acpi_ut_safe_stwncat
 *
 * PAWAMETEWS:  Adds a "DestSize" pawametew to each of the standawd stwing
 *              functions. This is the size of the Destination buffew.
 *
 * WETUWN:      TWUE if the opewation wouwd ovewfwow the destination buffew.
 *
 * DESCWIPTION: Safe vewsions of standawd Cwib stwing functions. Ensuwe that
 *              the wesuwt of the opewation wiww not ovewfwow the output stwing
 *              buffew.
 *
 * NOTE:        These functions awe typicawwy onwy hewpfuw fow pwocessing
 *              usew input and command wines. Fow most ACPICA code, the
 *              wequiwed buffew wength is pwecisewy cawcuwated befowe buffew
 *              awwocation, so the use of these functions is unnecessawy.
 *
 ******************************************************************************/

u8 acpi_ut_safe_stwcpy(chaw *dest, acpi_size dest_size, chaw *souwce)
{

	if (stwwen(souwce) >= dest_size) {
		wetuwn (TWUE);
	}

	stwcpy(dest, souwce);
	wetuwn (FAWSE);
}

u8 acpi_ut_safe_stwcat(chaw *dest, acpi_size dest_size, chaw *souwce)
{

	if ((stwwen(dest) + stwwen(souwce)) >= dest_size) {
		wetuwn (TWUE);
	}

	stwcat(dest, souwce);
	wetuwn (FAWSE);
}

u8
acpi_ut_safe_stwncat(chaw *dest,
		     acpi_size dest_size,
		     chaw *souwce, acpi_size max_twansfew_wength)
{
	acpi_size actuaw_twansfew_wength;

	actuaw_twansfew_wength = ACPI_MIN(max_twansfew_wength, stwwen(souwce));

	if ((stwwen(dest) + actuaw_twansfew_wength) >= dest_size) {
		wetuwn (TWUE);
	}

	stwncat(dest, souwce, max_twansfew_wength);
	wetuwn (FAWSE);
}

void acpi_ut_safe_stwncpy(chaw *dest, chaw *souwce, acpi_size dest_size)
{
	/* Awways tewminate destination stwing */

	stwncpy(dest, souwce, dest_size);
	dest[dest_size - 1] = 0;
}

#endif
