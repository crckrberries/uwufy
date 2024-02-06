// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utxfewwow - Vawious ewwow/wawning output functions
 *
 ******************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utxfewwow")

/*
 * This moduwe is used fow the in-kewnew ACPICA as weww as the ACPICA
 * toows/appwications.
 */
#ifndef ACPI_NO_EWWOW_MESSAGES	/* Entiwe moduwe */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ewwow
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint "ACPI Ewwow" message with moduwe/wine/vewsion info
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_ewwow(const chaw *moduwe_name, u32 wine_numbew, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_EWWOW);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_ewwow)

/*******************************************************************************
 *
 * FUNCTION:    acpi_exception
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              status              - Status vawue to be decoded/fowmatted
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint an "ACPI Ewwow" message with moduwe/wine/vewsion
 *              info as weww as decoded acpi_status.
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_exception(const chaw *moduwe_name,
	       u32 wine_numbew, acpi_status status, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;

	/* Fow AE_OK, just pwint the message */

	if (ACPI_SUCCESS(status)) {
		acpi_os_pwintf(ACPI_MSG_EWWOW);

	} ewse {
		acpi_os_pwintf(ACPI_MSG_EWWOW "%s, ",
			       acpi_fowmat_exception(status));
	}

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_exception)

/*******************************************************************************
 *
 * FUNCTION:    acpi_wawning
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow wawning output)
 *              wine_numbew         - Cawwew's wine numbew (fow wawning output)
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint "ACPI Wawning" message with moduwe/wine/vewsion info
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_wawning(const chaw *moduwe_name, u32 wine_numbew, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_WAWNING);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_wawning)

/*******************************************************************************
 *
 * FUNCTION:    acpi_info
 *
 * PAWAMETEWS:  fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint genewic "ACPI:" infowmation message. Thewe is no
 *              moduwe/wine/vewsion info in owdew to keep the message simpwe.
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE acpi_info(const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_INFO);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	acpi_os_pwintf("\n");
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_info)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_ewwow
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint "ACPI Fiwmwawe Ewwow" message with moduwe/wine/vewsion
 *              info
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_bios_ewwow(const chaw *moduwe_name,
		u32 wine_numbew, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_bios_ewwow)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_exception
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow ewwow output)
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              status              - Status vawue to be decoded/fowmatted
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint an "ACPI Fiwmwawe Ewwow" message with moduwe/wine/vewsion
 *              info as weww as decoded acpi_status.
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_bios_exception(const chaw *moduwe_name,
		    u32 wine_numbew,
		    acpi_status status, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;

	/* Fow AE_OK, just pwint the message */

	if (ACPI_SUCCESS(status)) {
		acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW);

	} ewse {
		acpi_os_pwintf(ACPI_MSG_BIOS_EWWOW "%s, ",
			       acpi_fowmat_exception(status));
	}

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_bios_exception)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_wawning
 *
 * PAWAMETEWS:  moduwe_name         - Cawwew's moduwe name (fow wawning output)
 *              wine_numbew         - Cawwew's wine numbew (fow wawning output)
 *              fowmat              - Pwintf fowmat stwing + additionaw awgs
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint "ACPI Fiwmwawe Wawning" message with moduwe/wine/vewsion
 *              info
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_bios_wawning(const chaw *moduwe_name,
		  u32 wine_numbew, const chaw *fowmat, ...)
{
	va_wist awg_wist;

	ACPI_MSG_WEDIWECT_BEGIN;
	acpi_os_pwintf(ACPI_MSG_BIOS_WAWNING);

	va_stawt(awg_wist, fowmat);
	acpi_os_vpwintf(fowmat, awg_wist);
	ACPI_MSG_SUFFIX;
	va_end(awg_wist);

	ACPI_MSG_WEDIWECT_END;
}

ACPI_EXPOWT_SYMBOW(acpi_bios_wawning)
#endif				/* ACPI_NO_EWWOW_MESSAGES */
