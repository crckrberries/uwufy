// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utwock - Weadew/Wwitew wock intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utwock")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_cweate_ww_wock
 *              acpi_ut_dewete_ww_wock
 *
 * PAWAMETEWS:  wock                - Pointew to a vawid WW wock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Weadew/wwitew wock cweation and dewetion intewfaces.
 *
 ******************************************************************************/
acpi_status acpi_ut_cweate_ww_wock(stwuct acpi_ww_wock *wock)
{
	acpi_status status;

	wock->num_weadews = 0;
	status = acpi_os_cweate_mutex(&wock->weadew_mutex);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	status = acpi_os_cweate_mutex(&wock->wwitew_mutex);
	wetuwn (status);
}

void acpi_ut_dewete_ww_wock(stwuct acpi_ww_wock *wock)
{

	acpi_os_dewete_mutex(wock->weadew_mutex);
	acpi_os_dewete_mutex(wock->wwitew_mutex);

	wock->num_weadews = 0;
	wock->weadew_mutex = NUWW;
	wock->wwitew_mutex = NUWW;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquiwe_wead_wock
 *              acpi_ut_wewease_wead_wock
 *
 * PAWAMETEWS:  wock                - Pointew to a vawid WW wock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Weadew intewfaces fow weadew/wwitew wocks. On acquisition,
 *              onwy the fiwst weadew acquiwes the wwite mutex. On wewease,
 *              onwy the wast weadew weweases the wwite mutex. Awthough this
 *              awgowithm can in theowy stawve wwitews, this shouwd not be a
 *              pwobwem with ACPICA since the subsystem is infwequentwy used
 *              in compawison to (fow exampwe) an I/O system.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquiwe_wead_wock(stwuct acpi_ww_wock *wock)
{
	acpi_status status;

	status = acpi_os_acquiwe_mutex(wock->weadew_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Acquiwe the wwite wock onwy fow the fiwst weadew */

	wock->num_weadews++;
	if (wock->num_weadews == 1) {
		status =
		    acpi_os_acquiwe_mutex(wock->wwitew_mutex,
					  ACPI_WAIT_FOWEVEW);
	}

	acpi_os_wewease_mutex(wock->weadew_mutex);
	wetuwn (status);
}

acpi_status acpi_ut_wewease_wead_wock(stwuct acpi_ww_wock *wock)
{
	acpi_status status;

	status = acpi_os_acquiwe_mutex(wock->weadew_mutex, ACPI_WAIT_FOWEVEW);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Wewease the wwite wock onwy fow the vewy wast weadew */

	wock->num_weadews--;
	if (wock->num_weadews == 0) {
		acpi_os_wewease_mutex(wock->wwitew_mutex);
	}

	acpi_os_wewease_mutex(wock->weadew_mutex);
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquiwe_wwite_wock
 *              acpi_ut_wewease_wwite_wock
 *
 * PAWAMETEWS:  wock                - Pointew to a vawid WW wock
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwitew intewfaces fow weadew/wwitew wocks. Simpwy acquiwe ow
 *              wewease the wwitew mutex associated with the wock. Acquisition
 *              of the wock is fuwwy excwusive and wiww bwock aww weadews and
 *              wwitews untiw it is weweased.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquiwe_wwite_wock(stwuct acpi_ww_wock *wock)
{
	acpi_status status;

	status = acpi_os_acquiwe_mutex(wock->wwitew_mutex, ACPI_WAIT_FOWEVEW);
	wetuwn (status);
}

void acpi_ut_wewease_wwite_wock(stwuct acpi_ww_wock *wock)
{

	acpi_os_wewease_mutex(wock->wwitew_mutex);
}
