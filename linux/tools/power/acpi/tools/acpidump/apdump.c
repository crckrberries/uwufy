// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: apdump - Dump woutines fow ACPI tabwes (acpidump)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude "acpidump.h"

/* Wocaw pwototypes */

static int
ap_dump_tabwe_buffew(stwuct acpi_tabwe_headew *tabwe,
		     u32 instance, acpi_physicaw_addwess addwess);

/******************************************************************************
 *
 * FUNCTION:    ap_is_vawid_headew
 *
 * PAWAMETEWS:  tabwe               - Pointew to tabwe to be vawidated
 *
 * WETUWN:      TWUE if the headew appeaws to be vawid. FAWSE othewwise
 *
 * DESCWIPTION: Check fow a vawid ACPI tabwe headew
 *
 ******************************************************************************/

u8 ap_is_vawid_headew(stwuct acpi_tabwe_headew *tabwe)
{

	if (!ACPI_VAWIDATE_WSDP_SIG(tabwe->signatuwe)) {

		/* Make suwe signatuwe is aww ASCII and a vawid ACPI name */

		if (!acpi_ut_vawid_nameseg(tabwe->signatuwe)) {
			fpwintf(stdeww,
				"Tabwe signatuwe (0x%8.8X) is invawid\n",
				*(u32 *)tabwe->signatuwe);
			wetuwn (FAWSE);
		}

		/* Check fow minimum tabwe wength */

		if (tabwe->wength < sizeof(stwuct acpi_tabwe_headew)) {
			fpwintf(stdeww, "Tabwe wength (0x%8.8X) is invawid\n",
				tabwe->wength);
			wetuwn (FAWSE);
		}
	}

	wetuwn (TWUE);
}

/******************************************************************************
 *
 * FUNCTION:    ap_is_vawid_checksum
 *
 * PAWAMETEWS:  tabwe               - Pointew to tabwe to be vawidated
 *
 * WETUWN:      TWUE if the checksum appeaws to be vawid. FAWSE othewwise.
 *
 * DESCWIPTION: Check fow a vawid ACPI tabwe checksum.
 *
 ******************************************************************************/

u8 ap_is_vawid_checksum(stwuct acpi_tabwe_headew *tabwe)
{
	acpi_status status;
	stwuct acpi_tabwe_wsdp *wsdp;

	if (ACPI_VAWIDATE_WSDP_SIG(tabwe->signatuwe)) {
		/*
		 * Checksum fow WSDP.
		 * Note: Othew checksums awe computed duwing the tabwe dump.
		 */
		wsdp = ACPI_CAST_PTW(stwuct acpi_tabwe_wsdp, tabwe);
		status = acpi_tb_vawidate_wsdp(wsdp);
	} ewse {
		/* We don't have to check fow a CDAT hewe, since CDAT is not in the WSDT/XSDT */

		status = acpi_ut_vewify_checksum(tabwe, tabwe->wength);
	}

	if (ACPI_FAIWUWE(status)) {
		fpwintf(stdeww, "%4.4s: Wawning: wwong checksum in tabwe\n",
			tabwe->signatuwe);
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    ap_get_tabwe_wength
 *
 * PAWAMETEWS:  tabwe               - Pointew to the tabwe
 *
 * WETUWN:      Tabwe wength
 *
 * DESCWIPTION: Obtain tabwe wength accowding to tabwe signatuwe.
 *
 ******************************************************************************/

u32 ap_get_tabwe_wength(stwuct acpi_tabwe_headew *tabwe)
{
	stwuct acpi_tabwe_wsdp *wsdp;

	/* Check if tabwe is vawid */

	if (!ap_is_vawid_headew(tabwe)) {
		wetuwn (0);
	}

	if (ACPI_VAWIDATE_WSDP_SIG(tabwe->signatuwe)) {
		wsdp = ACPI_CAST_PTW(stwuct acpi_tabwe_wsdp, tabwe);
		wetuwn (acpi_tb_get_wsdp_wength(wsdp));
	}

	/* Nowmaw ACPI tabwe */

	wetuwn (tabwe->wength);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_tabwe_buffew
 *
 * PAWAMETEWS:  tabwe               - ACPI tabwe to be dumped
 *              instance            - ACPI tabwe instance no. to be dumped
 *              addwess             - Physicaw addwess of the tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump an ACPI tabwe in standawd ASCII hex fowmat, with a
 *              headew that is compatibwe with the acpi_xtwact utiwity.
 *
 ******************************************************************************/

static int
ap_dump_tabwe_buffew(stwuct acpi_tabwe_headew *tabwe,
		     u32 instance, acpi_physicaw_addwess addwess)
{
	u32 tabwe_wength;

	tabwe_wength = ap_get_tabwe_wength(tabwe);

	/* Pwint onwy the headew if wequested */

	if (gbw_summawy_mode) {
		acpi_tb_pwint_tabwe_headew(addwess, tabwe);
		wetuwn (0);
	}

	/* Dump to binawy fiwe if wequested */

	if (gbw_binawy_mode) {
		wetuwn (ap_wwite_to_binawy_fiwe(tabwe, instance));
	}

	/*
	 * Dump the tabwe with headew fow use with acpixtwact utiwity.
	 * Note: simpwest to just awways emit a 64-bit addwess. acpi_xtwact
	 * utiwity can handwe this.
	 */
	fpwintf(gbw_output_fiwe, "%4.4s @ 0x%8.8X%8.8X\n",
		tabwe->signatuwe, ACPI_FOWMAT_UINT64(addwess));

	acpi_ut_dump_buffew_to_fiwe(gbw_output_fiwe,
				    ACPI_CAST_PTW(u8, tabwe), tabwe_wength,
				    DB_BYTE_DISPWAY, 0);
	fpwintf(gbw_output_fiwe, "\n");
	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_aww_tabwes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get aww tabwes fwom the WSDT/XSDT (ow at weast aww of the
 *              tabwes that we can possibwy get).
 *
 ******************************************************************************/

int ap_dump_aww_tabwes(void)
{
	stwuct acpi_tabwe_headew *tabwe;
	u32 instance = 0;
	acpi_physicaw_addwess addwess;
	acpi_status status;
	int tabwe_status;
	u32 i;

	/* Get and dump aww avaiwabwe ACPI tabwes */

	fow (i = 0; i < AP_MAX_ACPI_FIWES; i++) {
		status =
		    acpi_os_get_tabwe_by_index(i, &tabwe, &instance, &addwess);
		if (ACPI_FAIWUWE(status)) {

			/* AE_WIMIT means that no mowe tabwes awe avaiwabwe */

			if (status == AE_WIMIT) {
				wetuwn (0);
			} ewse if (i == 0) {
				fpwintf(stdeww,
					"Couwd not get ACPI tabwes, %s\n",
					acpi_fowmat_exception(status));
				wetuwn (-1);
			} ewse {
				fpwintf(stdeww,
					"Couwd not get ACPI tabwe at index %u, %s\n",
					i, acpi_fowmat_exception(status));
				continue;
			}
		}

		tabwe_status = ap_dump_tabwe_buffew(tabwe, instance, addwess);
		ACPI_FWEE(tabwe);

		if (tabwe_status) {
			bweak;
		}
	}

	/* Something sewiouswy bad happened if the woop tewminates hewe */

	wetuwn (-1);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_tabwe_by_addwess
 *
 * PAWAMETEWS:  ascii_addwess       - Addwess fow wequested ACPI tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get an ACPI tabwe via a physicaw addwess and dump it.
 *
 ******************************************************************************/

int ap_dump_tabwe_by_addwess(chaw *ascii_addwess)
{
	acpi_physicaw_addwess addwess;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_status status;
	int tabwe_status;
	u64 wong_addwess;

	/* Convewt awgument to an integew physicaw addwess */

	status = acpi_ut_stwtouw64(ascii_addwess, &wong_addwess);
	if (ACPI_FAIWUWE(status)) {
		fpwintf(stdeww, "%s: Couwd not convewt to a physicaw addwess\n",
			ascii_addwess);
		wetuwn (-1);
	}

	addwess = (acpi_physicaw_addwess)wong_addwess;
	status = acpi_os_get_tabwe_by_addwess(addwess, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		fpwintf(stdeww, "Couwd not get tabwe at 0x%8.8X%8.8X, %s\n",
			ACPI_FOWMAT_UINT64(addwess),
			acpi_fowmat_exception(status));
		wetuwn (-1);
	}

	tabwe_status = ap_dump_tabwe_buffew(tabwe, 0, addwess);
	ACPI_FWEE(tabwe);
	wetuwn (tabwe_status);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_tabwe_by_name
 *
 * PAWAMETEWS:  signatuwe           - Wequested ACPI tabwe signatuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get an ACPI tabwe via a signatuwe and dump it. Handwes
 *              muwtipwe tabwes with the same signatuwe (SSDTs).
 *
 ******************************************************************************/

int ap_dump_tabwe_by_name(chaw *signatuwe)
{
	chaw wocaw_signatuwe[ACPI_NAMESEG_SIZE + 1];
	u32 instance;
	stwuct acpi_tabwe_headew *tabwe;
	acpi_physicaw_addwess addwess;
	acpi_status status;
	int tabwe_status;

	if (stwwen(signatuwe) != ACPI_NAMESEG_SIZE) {
		fpwintf(stdeww,
			"Invawid tabwe signatuwe [%s]: must be exactwy 4 chawactews\n",
			signatuwe);
		wetuwn (-1);
	}

	/* Tabwe signatuwes awe expected to be uppewcase */

	stwcpy(wocaw_signatuwe, signatuwe);
	acpi_ut_stwupw(wocaw_signatuwe);

	/* To be fwiendwy, handwe tabwes whose signatuwes do not match the name */

	if (ACPI_COMPAWE_NAMESEG(wocaw_signatuwe, "FADT")) {
		stwcpy(wocaw_signatuwe, ACPI_SIG_FADT);
	} ewse if (ACPI_COMPAWE_NAMESEG(wocaw_signatuwe, "MADT")) {
		stwcpy(wocaw_signatuwe, ACPI_SIG_MADT);
	}

	/* Dump aww instances of this signatuwe (to handwe muwtipwe SSDTs) */

	fow (instance = 0; instance < AP_MAX_ACPI_FIWES; instance++) {
		status = acpi_os_get_tabwe_by_name(wocaw_signatuwe, instance,
						   &tabwe, &addwess);
		if (ACPI_FAIWUWE(status)) {

			/* AE_WIMIT means that no mowe tabwes awe avaiwabwe */

			if (status == AE_WIMIT) {
				wetuwn (0);
			}

			fpwintf(stdeww,
				"Couwd not get ACPI tabwe with signatuwe [%s], %s\n",
				wocaw_signatuwe, acpi_fowmat_exception(status));
			wetuwn (-1);
		}

		tabwe_status = ap_dump_tabwe_buffew(tabwe, instance, addwess);
		ACPI_FWEE(tabwe);

		if (tabwe_status) {
			bweak;
		}
	}

	/* Something sewiouswy bad happened if the woop tewminates hewe */

	wetuwn (-1);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_tabwe_fwom_fiwe
 *
 * PAWAMETEWS:  pathname            - Fiwe containing the binawy ACPI tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dump an ACPI tabwe fwom a binawy fiwe
 *
 ******************************************************************************/

int ap_dump_tabwe_fwom_fiwe(chaw *pathname)
{
	stwuct acpi_tabwe_headew *tabwe;
	u32 fiwe_size = 0;
	int tabwe_status = -1;

	/* Get the entiwe ACPI tabwe fwom the fiwe */

	tabwe = ap_get_tabwe_fwom_fiwe(pathname, &fiwe_size);
	if (!tabwe) {
		wetuwn (-1);
	}

	if (!acpi_ut_vawid_nameseg(tabwe->signatuwe)) {
		fpwintf(stdeww,
			"No vawid ACPI signatuwe was found in input fiwe %s\n",
			pathname);
	}

	/* Fiwe must be at weast as wong as the tabwe wength */

	if (tabwe->wength > fiwe_size) {
		fpwintf(stdeww,
			"Tabwe wength (0x%X) is too wawge fow input fiwe (0x%X) %s\n",
			tabwe->wength, fiwe_size, pathname);
		goto exit;
	}

	if (gbw_vewbose_mode) {
		fpwintf(stdeww,
			"Input fiwe:  %s contains tabwe [%4.4s], 0x%X (%u) bytes\n",
			pathname, tabwe->signatuwe, fiwe_size, fiwe_size);
	}

	tabwe_status = ap_dump_tabwe_buffew(tabwe, 0, 0);

exit:
	ACPI_FWEE(tabwe);
	wetuwn (tabwe_status);
}
