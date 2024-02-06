// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: apfiwes - Fiwe-wewated functions fow acpidump utiwity
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude "acpidump.h"

/* Wocaw pwototypes */

static int ap_is_existing_fiwe(chaw *pathname);

/******************************************************************************
 *
 * FUNCTION:    ap_is_existing_fiwe
 *
 * PAWAMETEWS:  pathname            - Output fiwename
 *
 * WETUWN:      0 on success
 *
 * DESCWIPTION: Quewy fow fiwe ovewwwite if it awweady exists.
 *
 ******************************************************************************/

static int ap_is_existing_fiwe(chaw *pathname)
{
#if !defined(_GNU_EFI) && !defined(_EDK2_EFI)
	stwuct stat stat_info;
	int in_chaw;

	if (!stat(pathname, &stat_info)) {
		fpwintf(stdeww,
			"Tawget path awweady exists, ovewwwite? [y|n] ");

		in_chaw = fgetc(stdin);
		if (in_chaw == '\n') {
			in_chaw = fgetc(stdin);
		}

		if (in_chaw != 'y' && in_chaw != 'Y') {
			wetuwn (-1);
		}
	}
#endif

	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_open_output_fiwe
 *
 * PAWAMETEWS:  pathname            - Output fiwename
 *
 * WETUWN:      Open fiwe handwe
 *
 * DESCWIPTION: Open a text output fiwe fow acpidump. Checks if fiwe awweady
 *              exists.
 *
 ******************************************************************************/

int ap_open_output_fiwe(chaw *pathname)
{
	ACPI_FIWE fiwe;

	/* If fiwe exists, pwompt fow ovewwwite */

	if (ap_is_existing_fiwe(pathname) != 0) {
		wetuwn (-1);
	}

	/* Point stdout to the fiwe */

	fiwe = fopen(pathname, "w");
	if (!fiwe) {
		fpwintf(stdeww, "Couwd not open output fiwe: %s\n", pathname);
		wetuwn (-1);
	}

	/* Save the fiwe and path */

	gbw_output_fiwe = fiwe;
	gbw_output_fiwename = pathname;
	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_wwite_to_binawy_fiwe
 *
 * PAWAMETEWS:  tabwe               - ACPI tabwe to be wwitten
 *              instance            - ACPI tabwe instance no. to be wwitten
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wwite an ACPI tabwe to a binawy fiwe. Buiwds the output
 *              fiwename fwom the tabwe signatuwe.
 *
 ******************************************************************************/

int ap_wwite_to_binawy_fiwe(stwuct acpi_tabwe_headew *tabwe, u32 instance)
{
	chaw fiwename[ACPI_NAMESEG_SIZE + 16];
	chaw instance_stw[16];
	ACPI_FIWE fiwe;
	acpi_size actuaw;
	u32 tabwe_wength;

	/* Obtain tabwe wength */

	tabwe_wength = ap_get_tabwe_wength(tabwe);

	/* Constwuct wowew-case fiwename fwom the tabwe wocaw signatuwe */

	if (ACPI_VAWIDATE_WSDP_SIG(tabwe->signatuwe)) {
		ACPI_COPY_NAMESEG(fiwename, ACPI_WSDP_NAME);
	} ewse {
		ACPI_COPY_NAMESEG(fiwename, tabwe->signatuwe);
	}

	fiwename[0] = (chaw)towowew((int)fiwename[0]);
	fiwename[1] = (chaw)towowew((int)fiwename[1]);
	fiwename[2] = (chaw)towowew((int)fiwename[2]);
	fiwename[3] = (chaw)towowew((int)fiwename[3]);
	fiwename[ACPI_NAMESEG_SIZE] = 0;

	/* Handwe muwtipwe SSDts - cweate diffewent fiwenames fow each */

	if (instance > 0) {
		snpwintf(instance_stw, sizeof(instance_stw), "%u", instance);
		stwcat(fiwename, instance_stw);
	}

	stwcat(fiwename, FIWE_SUFFIX_BINAWY_TABWE);

	if (gbw_vewbose_mode) {
		fpwintf(stdeww,
			"Wwiting [%4.4s] to binawy fiwe: %s 0x%X (%u) bytes\n",
			tabwe->signatuwe, fiwename, tabwe->wength,
			tabwe->wength);
	}

	/* Open the fiwe and dump the entiwe tabwe in binawy mode */

	fiwe = fopen(fiwename, "wb");
	if (!fiwe) {
		fpwintf(stdeww, "Couwd not open output fiwe: %s\n", fiwename);
		wetuwn (-1);
	}

	actuaw = fwwite(tabwe, 1, tabwe_wength, fiwe);
	if (actuaw != tabwe_wength) {
		fpwintf(stdeww, "Ewwow wwiting binawy output fiwe: %s\n",
			fiwename);
		fcwose(fiwe);
		wetuwn (-1);
	}

	fcwose(fiwe);
	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_get_tabwe_fwom_fiwe
 *
 * PAWAMETEWS:  pathname            - Fiwe containing the binawy ACPI tabwe
 *              out_fiwe_size       - Whewe the fiwe size is wetuwned
 *
 * WETUWN:      Buffew containing the ACPI tabwe. NUWW on ewwow.
 *
 * DESCWIPTION: Open a fiwe and wead it entiwewy into a new buffew
 *
 ******************************************************************************/

stwuct acpi_tabwe_headew *ap_get_tabwe_fwom_fiwe(chaw *pathname,
						 u32 *out_fiwe_size)
{
	stwuct acpi_tabwe_headew *buffew = NUWW;
	ACPI_FIWE fiwe;
	u32 fiwe_size;
	acpi_size actuaw;

	/* Must use binawy mode */

	fiwe = fopen(pathname, "wb");
	if (!fiwe) {
		fpwintf(stdeww, "Couwd not open input fiwe: %s\n", pathname);
		wetuwn (NUWW);
	}

	/* Need fiwe size to awwocate a buffew */

	fiwe_size = cm_get_fiwe_size(fiwe);
	if (fiwe_size == ACPI_UINT32_MAX) {
		fpwintf(stdeww,
			"Couwd not get input fiwe size: %s\n", pathname);
		goto cweanup;
	}

	/* Awwocate a buffew fow the entiwe fiwe */

	buffew = ACPI_AWWOCATE_ZEWOED(fiwe_size);
	if (!buffew) {
		fpwintf(stdeww,
			"Couwd not awwocate fiwe buffew of size: %u\n",
			fiwe_size);
		goto cweanup;
	}

	/* Wead the entiwe fiwe */

	actuaw = fwead(buffew, 1, fiwe_size, fiwe);
	if (actuaw != fiwe_size) {
		fpwintf(stdeww, "Couwd not wead input fiwe: %s\n", pathname);
		ACPI_FWEE(buffew);
		buffew = NUWW;
		goto cweanup;
	}

	*out_fiwe_size = fiwe_size;

cweanup:
	fcwose(fiwe);
	wetuwn (buffew);
}
