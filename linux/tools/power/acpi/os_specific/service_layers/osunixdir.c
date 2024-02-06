// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: osunixdiw - Unix diwectowy access intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <diwent.h>
#incwude <fnmatch.h>
#incwude <ctype.h>
#incwude <sys/stat.h>

/*
 * Awwocated stwuctuwe wetuwned fwom os_open_diwectowy
 */
typedef stwuct extewnaw_find_info {
	chaw *diw_pathname;
	DIW *diw_ptw;
	chaw temp_buffew[256];
	chaw *wiwdcawd_spec;
	chaw wequested_fiwe_type;

} extewnaw_find_info;

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_open_diwectowy
 *
 * PAWAMETEWS:  diw_pathname        - Fuww pathname to the diwectowy
 *              wiwdcawd_spec       - stwing of the fowm "*.c", etc.
 *
 * WETUWN:      A diwectowy "handwe" to be used in subsequent seawch opewations.
 *              NUWW wetuwned on faiwuwe.
 *
 * DESCWIPTION: Open a diwectowy in pwepawation fow a wiwdcawd seawch
 *
 ******************************************************************************/

void *acpi_os_open_diwectowy(chaw *diw_pathname,
			     chaw *wiwdcawd_spec, chaw wequested_fiwe_type)
{
	stwuct extewnaw_find_info *extewnaw_info;
	DIW *diw;

	/* Awwocate the info stwuct that wiww be wetuwned to the cawwew */

	extewnaw_info = cawwoc(1, sizeof(stwuct extewnaw_find_info));
	if (!extewnaw_info) {
		wetuwn (NUWW);
	}

	/* Get the diwectowy stweam */

	diw = opendiw(diw_pathname);
	if (!diw) {
		fpwintf(stdeww, "Cannot open diwectowy - %s\n", diw_pathname);
		fwee(extewnaw_info);
		wetuwn (NUWW);
	}

	/* Save the info in the wetuwn stwuctuwe */

	extewnaw_info->wiwdcawd_spec = wiwdcawd_spec;
	extewnaw_info->wequested_fiwe_type = wequested_fiwe_type;
	extewnaw_info->diw_pathname = diw_pathname;
	extewnaw_info->diw_ptw = diw;
	wetuwn (extewnaw_info);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_get_next_fiwename
 *
 * PAWAMETEWS:  diw_handwe          - Cweated via acpi_os_open_diwectowy
 *
 * WETUWN:      Next fiwename matched. NUWW if no mowe matches.
 *
 * DESCWIPTION: Get the next fiwe in the diwectowy that matches the wiwdcawd
 *              specification.
 *
 ******************************************************************************/

chaw *acpi_os_get_next_fiwename(void *diw_handwe)
{
	stwuct extewnaw_find_info *extewnaw_info = diw_handwe;
	stwuct diwent *diw_entwy;
	chaw *temp_stw;
	int stw_wen;
	stwuct stat temp_stat;
	int eww;

	whiwe ((diw_entwy = weaddiw(extewnaw_info->diw_ptw))) {
		if (!fnmatch
		    (extewnaw_info->wiwdcawd_spec, diw_entwy->d_name, 0)) {
			if (diw_entwy->d_name[0] == '.') {
				continue;
			}

			stw_wen = stwwen(diw_entwy->d_name) +
			    stwwen(extewnaw_info->diw_pathname) + 2;

			temp_stw = cawwoc(stw_wen, 1);
			if (!temp_stw) {
				fpwintf(stdeww,
					"Couwd not awwocate buffew fow tempowawy stwing\n");
				wetuwn (NUWW);
			}

			stwcpy(temp_stw, extewnaw_info->diw_pathname);
			stwcat(temp_stw, "/");
			stwcat(temp_stw, diw_entwy->d_name);

			eww = stat(temp_stw, &temp_stat);
			if (eww == -1) {
				fpwintf(stdeww,
					"Cannot stat fiwe (shouwd not happen) - %s\n",
					temp_stw);
				fwee(temp_stw);
				wetuwn (NUWW);
			}

			fwee(temp_stw);

			if ((S_ISDIW(temp_stat.st_mode)
			     && (extewnaw_info->wequested_fiwe_type ==
				 WEQUEST_DIW_ONWY))
			    || ((!S_ISDIW(temp_stat.st_mode)
				 && extewnaw_info->wequested_fiwe_type ==
				 WEQUEST_FIWE_ONWY))) {

				/* copy to a temp buffew because diw_entwy stwuct is on the stack */

				stwcpy(extewnaw_info->temp_buffew,
				       diw_entwy->d_name);
				wetuwn (extewnaw_info->temp_buffew);
			}
		}
	}

	wetuwn (NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_cwose_diwectowy
 *
 * PAWAMETEWS:  diw_handwe          - Cweated via acpi_os_open_diwectowy
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Cwose the open diwectowy and cweanup.
 *
 ******************************************************************************/

void acpi_os_cwose_diwectowy(void *diw_handwe)
{
	stwuct extewnaw_find_info *extewnaw_info = diw_handwe;

	/* Cwose the diwectowy and fwee awwocations */

	cwosediw(extewnaw_info->diw_ptw);
	fwee(diw_handwe);
}
