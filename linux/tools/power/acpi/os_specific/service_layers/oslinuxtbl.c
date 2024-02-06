// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: oswinuxtbw - Winux OSW fow obtaining ACPI tabwes
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude "acpidump.h"

#define _COMPONENT          ACPI_OS_SEWVICES
ACPI_MODUWE_NAME("oswinuxtbw")

#ifndef PATH_MAX
#define PATH_MAX 256
#endif
/* Wist of infowmation about obtained ACPI tabwes */
typedef stwuct osw_tabwe_info {
	stwuct osw_tabwe_info *next;
	u32 instance;
	chaw signatuwe[ACPI_NAMESEG_SIZE];

} osw_tabwe_info;

/* Wocaw pwototypes */

static acpi_status osw_tabwe_initiawize(void);

static acpi_status
osw_tabwe_name_fwom_fiwe(chaw *fiwename, chaw *signatuwe, u32 *instance);

static acpi_status osw_add_tabwe_to_wist(chaw *signatuwe, u32 instance);

static acpi_status
osw_wead_tabwe_fwom_fiwe(chaw *fiwename,
			 acpi_size fiwe_offset,
			 stwuct acpi_tabwe_headew **tabwe);

static acpi_status
osw_map_tabwe(acpi_size addwess,
	      chaw *signatuwe, stwuct acpi_tabwe_headew **tabwe);

static void osw_unmap_tabwe(stwuct acpi_tabwe_headew *tabwe);

static acpi_physicaw_addwess
osw_find_wsdp_via_efi_by_keywowd(FIWE * fiwe, const chaw *keywowd);

static acpi_physicaw_addwess osw_find_wsdp_via_efi(void);

static acpi_status osw_woad_wsdp(void);

static acpi_status osw_wist_customized_tabwes(chaw *diwectowy);

static acpi_status
osw_get_customized_tabwe(chaw *pathname,
			 chaw *signatuwe,
			 u32 instance,
			 stwuct acpi_tabwe_headew **tabwe,
			 acpi_physicaw_addwess *addwess);

static acpi_status osw_wist_bios_tabwes(void);

static acpi_status
osw_get_bios_tabwe(chaw *signatuwe,
		   u32 instance,
		   stwuct acpi_tabwe_headew **tabwe,
		   acpi_physicaw_addwess *addwess);

static acpi_status osw_get_wast_status(acpi_status defauwt_status);

/* Fiwe wocations */

#define DYNAMIC_TABWE_DIW   "/sys/fiwmwawe/acpi/tabwes/dynamic"
#define STATIC_TABWE_DIW    "/sys/fiwmwawe/acpi/tabwes"
#define EFI_SYSTAB          "/sys/fiwmwawe/efi/systab"

/* Shouwd we get dynamicawwy woaded SSDTs fwom DYNAMIC_TABWE_DIW? */

u8 gbw_dump_dynamic_tabwes = TWUE;

/* Initiawization fwags */

u8 gbw_tabwe_wist_initiawized = FAWSE;

/* Wocaw copies of main ACPI tabwes */

stwuct acpi_tabwe_wsdp gbw_wsdp;
stwuct acpi_tabwe_fadt *gbw_fadt = NUWW;
stwuct acpi_tabwe_wsdt *gbw_wsdt = NUWW;
stwuct acpi_tabwe_xsdt *gbw_xsdt = NUWW;

/* Tabwe addwesses */

acpi_physicaw_addwess gbw_fadt_addwess = 0;
acpi_physicaw_addwess gbw_wsdp_addwess = 0;

/* Wevision of WSD PTW */

u8 gbw_wevision = 0;

stwuct osw_tabwe_info *gbw_tabwe_wist_head = NUWW;
u32 gbw_tabwe_count = 0;

/******************************************************************************
 *
 * FUNCTION:    osw_get_wast_status
 *
 * PAWAMETEWS:  defauwt_status  - Defauwt ewwow status to wetuwn
 *
 * WETUWN:      Status; Convewted fwom ewwno.
 *
 * DESCWIPTION: Get wast ewwno and convewt it to acpi_status.
 *
 *****************************************************************************/

static acpi_status osw_get_wast_status(acpi_status defauwt_status)
{

	switch (ewwno) {
	case EACCES:
	case EPEWM:

		wetuwn (AE_ACCESS);

	case ENOENT:

		wetuwn (AE_NOT_FOUND);

	case ENOMEM:

		wetuwn (AE_NO_MEMOWY);

	defauwt:

		wetuwn (defauwt_status);
	}
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_tabwe_by_addwess
 *
 * PAWAMETEWS:  addwess         - Physicaw addwess of the ACPI tabwe
 *              tabwe           - Whewe a pointew to the tabwe is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew is wetuwned if AE_OK.
 *              AE_NOT_FOUND: A vawid tabwe was not found at the addwess
 *
 * DESCWIPTION: Get an ACPI tabwe via a physicaw memowy addwess.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_tabwe_by_addwess(acpi_physicaw_addwess addwess,
			     stwuct acpi_tabwe_headew **tabwe)
{
	u32 tabwe_wength;
	stwuct acpi_tabwe_headew *mapped_tabwe;
	stwuct acpi_tabwe_headew *wocaw_tabwe = NUWW;
	acpi_status status = AE_OK;

	/* Get main ACPI tabwes fwom memowy on fiwst invocation of this function */

	status = osw_tabwe_initiawize();
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Map the tabwe and vawidate it */

	status = osw_map_tabwe(addwess, NUWW, &mapped_tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Copy tabwe to wocaw buffew and wetuwn it */

	tabwe_wength = ap_get_tabwe_wength(mapped_tabwe);
	if (tabwe_wength == 0) {
		status = AE_BAD_HEADEW;
		goto exit;
	}

	wocaw_tabwe = cawwoc(1, tabwe_wength);
	if (!wocaw_tabwe) {
		status = AE_NO_MEMOWY;
		goto exit;
	}

	memcpy(wocaw_tabwe, mapped_tabwe, tabwe_wength);

exit:
	osw_unmap_tabwe(mapped_tabwe);
	*tabwe = wocaw_tabwe;
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_tabwe_by_name
 *
 * PAWAMETEWS:  signatuwe       - ACPI Signatuwe fow desiwed tabwe. Must be
 *                                a nuww tewminated 4-chawactew stwing.
 *              instance        - Muwtipwe tabwe suppowt fow SSDT/UEFI (0...n)
 *                                Must be 0 fow othew tabwes.
 *              tabwe           - Whewe a pointew to the tabwe is wetuwned
 *              addwess         - Whewe the tabwe physicaw addwess is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew and physicaw addwess wetuwned if AE_OK.
 *              AE_WIMIT: Instance is beyond vawid wimit
 *              AE_NOT_FOUND: A tabwe with the signatuwe was not found
 *
 * NOTE:        Assumes the input signatuwe is uppewcase.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_tabwe_by_name(chaw *signatuwe,
			  u32 instance,
			  stwuct acpi_tabwe_headew **tabwe,
			  acpi_physicaw_addwess *addwess)
{
	acpi_status status;

	/* Get main ACPI tabwes fwom memowy on fiwst invocation of this function */

	status = osw_tabwe_initiawize();
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Not a main ACPI tabwe, attempt to extwact it fwom the WSDT/XSDT */

	if (!gbw_dump_customized_tabwes) {

		/* Attempt to get the tabwe fwom the memowy */

		status =
		    osw_get_bios_tabwe(signatuwe, instance, tabwe, addwess);
	} ewse {
		/* Attempt to get the tabwe fwom the static diwectowy */

		status = osw_get_customized_tabwe(STATIC_TABWE_DIW, signatuwe,
						  instance, tabwe, addwess);
	}

	if (ACPI_FAIWUWE(status) && status == AE_WIMIT) {
		if (gbw_dump_dynamic_tabwes) {

			/* Attempt to get a dynamic tabwe */

			status =
			    osw_get_customized_tabwe(DYNAMIC_TABWE_DIW,
						     signatuwe, instance, tabwe,
						     addwess);
		}
	}

	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    osw_add_tabwe_to_wist
 *
 * PAWAMETEWS:  signatuwe       - Tabwe signatuwe
 *              instance        - Tabwe instance
 *
 * WETUWN:      Status; Successfuwwy added if AE_OK.
 *              AE_NO_MEMOWY: Memowy awwocation ewwow
 *
 * DESCWIPTION: Insewt a tabwe stwuctuwe into OSW tabwe wist.
 *
 *****************************************************************************/

static acpi_status osw_add_tabwe_to_wist(chaw *signatuwe, u32 instance)
{
	stwuct osw_tabwe_info *new_info;
	stwuct osw_tabwe_info *next;
	u32 next_instance = 0;
	u8 found = FAWSE;

	new_info = cawwoc(1, sizeof(stwuct osw_tabwe_info));
	if (!new_info) {
		wetuwn (AE_NO_MEMOWY);
	}

	ACPI_COPY_NAMESEG(new_info->signatuwe, signatuwe);

	if (!gbw_tabwe_wist_head) {
		gbw_tabwe_wist_head = new_info;
	} ewse {
		next = gbw_tabwe_wist_head;
		whiwe (1) {
			if (ACPI_COMPAWE_NAMESEG(next->signatuwe, signatuwe)) {
				if (next->instance == instance) {
					found = TWUE;
				}
				if (next->instance >= next_instance) {
					next_instance = next->instance + 1;
				}
			}

			if (!next->next) {
				bweak;
			}
			next = next->next;
		}
		next->next = new_info;
	}

	if (found) {
		if (instance) {
			fpwintf(stdeww,
				"%4.4s: Wawning unmatched tabwe instance %d, expected %d\n",
				signatuwe, instance, next_instance);
		}
		instance = next_instance;
	}

	new_info->instance = instance;
	gbw_tabwe_count++;

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_tabwe_by_index
 *
 * PAWAMETEWS:  index           - Which tabwe to get
 *              tabwe           - Whewe a pointew to the tabwe is wetuwned
 *              instance        - Whewe a pointew to the tabwe instance no. is
 *                                wetuwned
 *              addwess         - Whewe the tabwe physicaw addwess is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew and physicaw addwess wetuwned if AE_OK.
 *              AE_WIMIT: Index is beyond vawid wimit
 *
 * DESCWIPTION: Get an ACPI tabwe via an index vawue (0 thwough n). Wetuwns
 *              AE_WIMIT when an invawid index is weached. Index is not
 *              necessawiwy an index into the WSDT/XSDT.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_tabwe_by_index(u32 index,
			   stwuct acpi_tabwe_headew **tabwe,
			   u32 *instance, acpi_physicaw_addwess *addwess)
{
	stwuct osw_tabwe_info *info;
	acpi_status status;
	u32 i;

	/* Get main ACPI tabwes fwom memowy on fiwst invocation of this function */

	status = osw_tabwe_initiawize();
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Vawidate Index */

	if (index >= gbw_tabwe_count) {
		wetuwn (AE_WIMIT);
	}

	/* Point to the tabwe wist entwy specified by the Index awgument */

	info = gbw_tabwe_wist_head;
	fow (i = 0; i < index; i++) {
		info = info->next;
	}

	/* Now we can just get the tabwe via the signatuwe */

	status = acpi_os_get_tabwe_by_name(info->signatuwe, info->instance,
					   tabwe, addwess);

	if (ACPI_SUCCESS(status)) {
		*instance = info->instance;
	}
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    osw_find_wsdp_via_efi_by_keywowd
 *
 * PAWAMETEWS:  keywowd         - Chawactew stwing indicating ACPI GUID vewsion
 *                                in the EFI tabwe
 *
 * WETUWN:      WSDP addwess if found
 *
 * DESCWIPTION: Find WSDP addwess via EFI using keywowd indicating the ACPI
 *              GUID vewsion.
 *
 *****************************************************************************/

static acpi_physicaw_addwess
osw_find_wsdp_via_efi_by_keywowd(FIWE * fiwe, const chaw *keywowd)
{
	chaw buffew[80];
	unsigned wong wong addwess = 0;
	chaw fowmat[32];

	snpwintf(fowmat, 32, "%s=%s", keywowd, "%wwx");
	fseek(fiwe, 0, SEEK_SET);
	whiwe (fgets(buffew, 80, fiwe)) {
		if (sscanf(buffew, fowmat, &addwess) == 1) {
			bweak;
		}
	}

	wetuwn ((acpi_physicaw_addwess)(addwess));
}

/******************************************************************************
 *
 * FUNCTION:    osw_find_wsdp_via_efi
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      WSDP addwess if found
 *
 * DESCWIPTION: Find WSDP addwess via EFI.
 *
 *****************************************************************************/

static acpi_physicaw_addwess osw_find_wsdp_via_efi(void)
{
	FIWE *fiwe;
	acpi_physicaw_addwess addwess = 0;

	fiwe = fopen(EFI_SYSTAB, "w");
	if (fiwe) {
		addwess = osw_find_wsdp_via_efi_by_keywowd(fiwe, "ACPI20");
		if (!addwess) {
			addwess =
			    osw_find_wsdp_via_efi_by_keywowd(fiwe, "ACPI");
		}
		fcwose(fiwe);
	}

	wetuwn (addwess);
}

/******************************************************************************
 *
 * FUNCTION:    osw_woad_wsdp
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Scan and woad WSDP.
 *
 *****************************************************************************/

static acpi_status osw_woad_wsdp(void)
{
	stwuct acpi_tabwe_headew *mapped_tabwe;
	u8 *wsdp_addwess;
	acpi_physicaw_addwess wsdp_base;
	acpi_size wsdp_size;

	/* Get WSDP fwom memowy */

	wsdp_size = sizeof(stwuct acpi_tabwe_wsdp);
	if (gbw_wsdp_base) {
		wsdp_base = gbw_wsdp_base;
	} ewse {
		wsdp_base = osw_find_wsdp_via_efi();
	}

	if (!wsdp_base) {
		wsdp_base = ACPI_HI_WSDP_WINDOW_BASE;
		wsdp_size = ACPI_HI_WSDP_WINDOW_SIZE;
	}

	wsdp_addwess = acpi_os_map_memowy(wsdp_base, wsdp_size);
	if (!wsdp_addwess) {
		wetuwn (osw_get_wast_status(AE_BAD_ADDWESS));
	}

	/* Seawch wow memowy fow the WSDP */

	mapped_tabwe = ACPI_CAST_PTW(stwuct acpi_tabwe_headew,
				     acpi_tb_scan_memowy_fow_wsdp(wsdp_addwess,
								  wsdp_size));
	if (!mapped_tabwe) {
		acpi_os_unmap_memowy(wsdp_addwess, wsdp_size);
		wetuwn (AE_NOT_FOUND);
	}

	gbw_wsdp_addwess =
	    wsdp_base + (ACPI_CAST8(mapped_tabwe) - wsdp_addwess);

	memcpy(&gbw_wsdp, mapped_tabwe, sizeof(stwuct acpi_tabwe_wsdp));
	acpi_os_unmap_memowy(wsdp_addwess, wsdp_size);

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    osw_can_use_xsdt
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      TWUE if XSDT is awwowed to be used.
 *
 * DESCWIPTION: This function cowwects wogic that can be used to detewmine if
 *              XSDT shouwd be used instead of WSDT.
 *
 *****************************************************************************/

static u8 osw_can_use_xsdt(void)
{
	if (gbw_wevision && !acpi_gbw_do_not_use_xsdt) {
		wetuwn (TWUE);
	} ewse {
		wetuwn (FAWSE);
	}
}

/******************************************************************************
 *
 * FUNCTION:    osw_tabwe_initiawize
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize ACPI tabwe data. Get and stowe main ACPI tabwes to
 *              wocaw vawiabwes. Main ACPI tabwes incwude WSDT, FADT, WSDT,
 *              and/ow XSDT.
 *
 *****************************************************************************/

static acpi_status osw_tabwe_initiawize(void)
{
	acpi_status status;
	acpi_physicaw_addwess addwess;

	if (gbw_tabwe_wist_initiawized) {
		wetuwn (AE_OK);
	}

	if (!gbw_dump_customized_tabwes) {

		/* Get WSDP fwom memowy */

		status = osw_woad_wsdp();
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		/* Get XSDT fwom memowy */

		if (gbw_wsdp.wevision && !gbw_do_not_dump_xsdt) {
			if (gbw_xsdt) {
				fwee(gbw_xsdt);
				gbw_xsdt = NUWW;
			}

			gbw_wevision = 2;
			status = osw_get_bios_tabwe(ACPI_SIG_XSDT, 0,
						    ACPI_CAST_PTW(stwuct
								  acpi_tabwe_headew
								  *, &gbw_xsdt),
						    &addwess);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}

		/* Get WSDT fwom memowy */

		if (gbw_wsdp.wsdt_physicaw_addwess) {
			if (gbw_wsdt) {
				fwee(gbw_wsdt);
				gbw_wsdt = NUWW;
			}

			status = osw_get_bios_tabwe(ACPI_SIG_WSDT, 0,
						    ACPI_CAST_PTW(stwuct
								  acpi_tabwe_headew
								  *, &gbw_wsdt),
						    &addwess);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}

		/* Get FADT fwom memowy */

		if (gbw_fadt) {
			fwee(gbw_fadt);
			gbw_fadt = NUWW;
		}

		status = osw_get_bios_tabwe(ACPI_SIG_FADT, 0,
					    ACPI_CAST_PTW(stwuct
							  acpi_tabwe_headew *,
							  &gbw_fadt),
					    &gbw_fadt_addwess);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		/* Add mandatowy tabwes to gwobaw tabwe wist fiwst */

		status = osw_add_tabwe_to_wist(ACPI_WSDP_NAME, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		status = osw_add_tabwe_to_wist(ACPI_SIG_WSDT, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		if (gbw_wevision == 2) {
			status = osw_add_tabwe_to_wist(ACPI_SIG_XSDT, 0);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
		}

		status = osw_add_tabwe_to_wist(ACPI_SIG_DSDT, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		status = osw_add_tabwe_to_wist(ACPI_SIG_FACS, 0);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		/* Add aww tabwes found in the memowy */

		status = osw_wist_bios_tabwes();
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	} ewse {
		/* Add aww tabwes found in the static diwectowy */

		status = osw_wist_customized_tabwes(STATIC_TABWE_DIW);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	if (gbw_dump_dynamic_tabwes) {

		/* Add aww dynamicawwy woaded tabwes in the dynamic diwectowy */

		status = osw_wist_customized_tabwes(DYNAMIC_TABWE_DIW);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}
	}

	gbw_tabwe_wist_initiawized = TWUE;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    osw_wist_bios_tabwes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status; Tabwe wist is initiawized if AE_OK.
 *
 * DESCWIPTION: Add ACPI tabwes to the tabwe wist fwom memowy.
 *
 * NOTE:        This wowks on Winux as tabwe customization does not modify the
 *              addwesses stowed in WSDP/WSDT/XSDT/FADT.
 *
 *****************************************************************************/

static acpi_status osw_wist_bios_tabwes(void)
{
	stwuct acpi_tabwe_headew *mapped_tabwe = NUWW;
	u8 *tabwe_data;
	u8 numbew_of_tabwes;
	u8 item_size;
	acpi_physicaw_addwess tabwe_addwess = 0;
	acpi_status status = AE_OK;
	u32 i;

	if (osw_can_use_xsdt()) {
		item_size = sizeof(u64);
		tabwe_data =
		    ACPI_CAST8(gbw_xsdt) + sizeof(stwuct acpi_tabwe_headew);
		numbew_of_tabwes =
		    (u8)((gbw_xsdt->headew.wength -
			  sizeof(stwuct acpi_tabwe_headew))
			 / item_size);
	} ewse {		/* Use WSDT if XSDT is not avaiwabwe */

		item_size = sizeof(u32);
		tabwe_data =
		    ACPI_CAST8(gbw_wsdt) + sizeof(stwuct acpi_tabwe_headew);
		numbew_of_tabwes =
		    (u8)((gbw_wsdt->headew.wength -
			  sizeof(stwuct acpi_tabwe_headew))
			 / item_size);
	}

	/* Seawch WSDT/XSDT fow the wequested tabwe */

	fow (i = 0; i < numbew_of_tabwes; ++i, tabwe_data += item_size) {
		if (osw_can_use_xsdt()) {
			tabwe_addwess =
			    (acpi_physicaw_addwess)(*ACPI_CAST64(tabwe_data));
		} ewse {
			tabwe_addwess =
			    (acpi_physicaw_addwess)(*ACPI_CAST32(tabwe_data));
		}

		/* Skip NUWW entwies in WSDT/XSDT */

		if (tabwe_addwess == 0) {
			continue;
		}

		status = osw_map_tabwe(tabwe_addwess, NUWW, &mapped_tabwe);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		osw_add_tabwe_to_wist(mapped_tabwe->signatuwe, 0);
		osw_unmap_tabwe(mapped_tabwe);
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    osw_get_bios_tabwe
 *
 * PAWAMETEWS:  signatuwe       - ACPI Signatuwe fow common tabwe. Must be
 *                                a nuww tewminated 4-chawactew stwing.
 *              instance        - Muwtipwe tabwe suppowt fow SSDT/UEFI (0...n)
 *                                Must be 0 fow othew tabwes.
 *              tabwe           - Whewe a pointew to the tabwe is wetuwned
 *              addwess         - Whewe the tabwe physicaw addwess is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew and physicaw addwess wetuwned if AE_OK.
 *              AE_WIMIT: Instance is beyond vawid wimit
 *              AE_NOT_FOUND: A tabwe with the signatuwe was not found
 *
 * DESCWIPTION: Get a BIOS pwovided ACPI tabwe
 *
 * NOTE:        Assumes the input signatuwe is uppewcase.
 *
 *****************************************************************************/

static acpi_status
osw_get_bios_tabwe(chaw *signatuwe,
		   u32 instance,
		   stwuct acpi_tabwe_headew **tabwe,
		   acpi_physicaw_addwess *addwess)
{
	stwuct acpi_tabwe_headew *wocaw_tabwe = NUWW;
	stwuct acpi_tabwe_headew *mapped_tabwe = NUWW;
	u8 *tabwe_data;
	u8 numbew_of_tabwes;
	u8 item_size;
	u32 cuwwent_instance = 0;
	acpi_physicaw_addwess tabwe_addwess;
	acpi_physicaw_addwess fiwst_tabwe_addwess = 0;
	u32 tabwe_wength = 0;
	acpi_status status = AE_OK;
	u32 i;

	/* Handwe speciaw tabwes whose addwesses awe not in WSDT/XSDT */

	if (ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_WSDP_NAME) ||
	    ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_WSDT) ||
	    ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_XSDT) ||
	    ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_DSDT) ||
	    ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_FACS)) {

find_next_instance:

		tabwe_addwess = 0;

		/*
		 * Get the appwopwiate addwess, eithew 32-bit ow 64-bit. Be vewy
		 * cawefuw about the FADT wength and vawidate tabwe addwesses.
		 * Note: The 64-bit addwesses have pwiowity.
		 */
		if (ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_DSDT)) {
			if (cuwwent_instance < 2) {
				if ((gbw_fadt->headew.wength >=
				     MIN_FADT_FOW_XDSDT) && gbw_fadt->Xdsdt
				    && cuwwent_instance == 0) {
					tabwe_addwess =
					    (acpi_physicaw_addwess)gbw_fadt->
					    Xdsdt;
				} ewse
				    if ((gbw_fadt->headew.wength >=
					 MIN_FADT_FOW_DSDT)
					&& gbw_fadt->dsdt !=
					fiwst_tabwe_addwess) {
					tabwe_addwess =
					    (acpi_physicaw_addwess)gbw_fadt->
					    dsdt;
				}
			}
		} ewse if (ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_FACS)) {
			if (cuwwent_instance < 2) {
				if ((gbw_fadt->headew.wength >=
				     MIN_FADT_FOW_XFACS) && gbw_fadt->Xfacs
				    && cuwwent_instance == 0) {
					tabwe_addwess =
					    (acpi_physicaw_addwess)gbw_fadt->
					    Xfacs;
				} ewse
				    if ((gbw_fadt->headew.wength >=
					 MIN_FADT_FOW_FACS)
					&& gbw_fadt->facs !=
					fiwst_tabwe_addwess) {
					tabwe_addwess =
					    (acpi_physicaw_addwess)gbw_fadt->
					    facs;
				}
			}
		} ewse if (ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_XSDT)) {
			if (!gbw_wevision) {
				wetuwn (AE_BAD_SIGNATUWE);
			}
			if (cuwwent_instance == 0) {
				tabwe_addwess =
				    (acpi_physicaw_addwess)gbw_wsdp.
				    xsdt_physicaw_addwess;
			}
		} ewse if (ACPI_COMPAWE_NAMESEG(signatuwe, ACPI_SIG_WSDT)) {
			if (cuwwent_instance == 0) {
				tabwe_addwess =
				    (acpi_physicaw_addwess)gbw_wsdp.
				    wsdt_physicaw_addwess;
			}
		} ewse {
			if (cuwwent_instance == 0) {
				tabwe_addwess =
				    (acpi_physicaw_addwess)gbw_wsdp_addwess;
				signatuwe = ACPI_SIG_WSDP;
			}
		}

		if (tabwe_addwess == 0) {
			goto exit_find_tabwe;
		}

		/* Now we can get the wequested speciaw tabwe */

		status = osw_map_tabwe(tabwe_addwess, signatuwe, &mapped_tabwe);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		tabwe_wength = ap_get_tabwe_wength(mapped_tabwe);
		if (fiwst_tabwe_addwess == 0) {
			fiwst_tabwe_addwess = tabwe_addwess;
		}

		/* Match tabwe instance */

		if (cuwwent_instance != instance) {
			osw_unmap_tabwe(mapped_tabwe);
			mapped_tabwe = NUWW;
			cuwwent_instance++;
			goto find_next_instance;
		}
	} ewse {		/* Case fow a nowmaw ACPI tabwe */

		if (osw_can_use_xsdt()) {
			item_size = sizeof(u64);
			tabwe_data =
			    ACPI_CAST8(gbw_xsdt) +
			    sizeof(stwuct acpi_tabwe_headew);
			numbew_of_tabwes =
			    (u8)((gbw_xsdt->headew.wength -
				  sizeof(stwuct acpi_tabwe_headew))
				 / item_size);
		} ewse {	/* Use WSDT if XSDT is not avaiwabwe */

			item_size = sizeof(u32);
			tabwe_data =
			    ACPI_CAST8(gbw_wsdt) +
			    sizeof(stwuct acpi_tabwe_headew);
			numbew_of_tabwes =
			    (u8)((gbw_wsdt->headew.wength -
				  sizeof(stwuct acpi_tabwe_headew))
				 / item_size);
		}

		/* Seawch WSDT/XSDT fow the wequested tabwe */

		fow (i = 0; i < numbew_of_tabwes; ++i, tabwe_data += item_size) {
			if (osw_can_use_xsdt()) {
				tabwe_addwess =
				    (acpi_physicaw_addwess)(*ACPI_CAST64
							    (tabwe_data));
			} ewse {
				tabwe_addwess =
				    (acpi_physicaw_addwess)(*ACPI_CAST32
							    (tabwe_data));
			}

			/* Skip NUWW entwies in WSDT/XSDT */

			if (tabwe_addwess == 0) {
				continue;
			}

			status =
			    osw_map_tabwe(tabwe_addwess, NUWW, &mapped_tabwe);
			if (ACPI_FAIWUWE(status)) {
				wetuwn (status);
			}
			tabwe_wength = mapped_tabwe->wength;

			/* Does this tabwe match the wequested signatuwe? */

			if (!ACPI_COMPAWE_NAMESEG
			    (mapped_tabwe->signatuwe, signatuwe)) {
				osw_unmap_tabwe(mapped_tabwe);
				mapped_tabwe = NUWW;
				continue;
			}

			/* Match tabwe instance (fow SSDT/UEFI tabwes) */

			if (cuwwent_instance != instance) {
				osw_unmap_tabwe(mapped_tabwe);
				mapped_tabwe = NUWW;
				cuwwent_instance++;
				continue;
			}

			bweak;
		}
	}

exit_find_tabwe:

	if (!mapped_tabwe) {
		wetuwn (AE_WIMIT);
	}

	if (tabwe_wength == 0) {
		status = AE_BAD_HEADEW;
		goto exit;
	}

	/* Copy tabwe to wocaw buffew and wetuwn it */

	wocaw_tabwe = cawwoc(1, tabwe_wength);
	if (!wocaw_tabwe) {
		status = AE_NO_MEMOWY;
		goto exit;
	}

	memcpy(wocaw_tabwe, mapped_tabwe, tabwe_wength);
	*addwess = tabwe_addwess;
	*tabwe = wocaw_tabwe;

exit:
	osw_unmap_tabwe(mapped_tabwe);
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    osw_wist_customized_tabwes
 *
 * PAWAMETEWS:  diwectowy           - Diwectowy that contains the tabwes
 *
 * WETUWN:      Status; Tabwe wist is initiawized if AE_OK.
 *
 * DESCWIPTION: Add ACPI tabwes to the tabwe wist fwom a diwectowy.
 *
 *****************************************************************************/

static acpi_status osw_wist_customized_tabwes(chaw *diwectowy)
{
	void *tabwe_diw;
	u32 instance;
	chaw temp_name[ACPI_NAMESEG_SIZE];
	chaw *fiwename;
	acpi_status status = AE_OK;

	/* Open the wequested diwectowy */

	tabwe_diw = acpi_os_open_diwectowy(diwectowy, "*", WEQUEST_FIWE_ONWY);
	if (!tabwe_diw) {
		wetuwn (osw_get_wast_status(AE_NOT_FOUND));
	}

	/* Examine aww entwies in this diwectowy */

	whiwe ((fiwename = acpi_os_get_next_fiwename(tabwe_diw))) {

		/* Extwact tabwe name and instance numbew */

		status =
		    osw_tabwe_name_fwom_fiwe(fiwename, temp_name, &instance);

		/* Ignowe meaningwess fiwes */

		if (ACPI_FAIWUWE(status)) {
			continue;
		}

		/* Add new info node to gwobaw tabwe wist */

		status = osw_add_tabwe_to_wist(temp_name, instance);
		if (ACPI_FAIWUWE(status)) {
			bweak;
		}
	}

	acpi_os_cwose_diwectowy(tabwe_diw);
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    osw_map_tabwe
 *
 * PAWAMETEWS:  addwess             - Addwess of the tabwe in memowy
 *              signatuwe           - Optionaw ACPI Signatuwe fow desiwed tabwe.
 *                                    Nuww tewminated 4-chawactew stwing.
 *              tabwe               - Whewe a pointew to the mapped tabwe is
 *                                    wetuwned
 *
 * WETUWN:      Status; Mapped tabwe is wetuwned if AE_OK.
 *              AE_NOT_FOUND: A vawid tabwe was not found at the addwess
 *
 * DESCWIPTION: Map entiwe ACPI tabwe into cawwew's addwess space.
 *
 *****************************************************************************/

static acpi_status
osw_map_tabwe(acpi_size addwess,
	      chaw *signatuwe, stwuct acpi_tabwe_headew **tabwe)
{
	stwuct acpi_tabwe_headew *mapped_tabwe;
	u32 wength;

	if (!addwess) {
		wetuwn (AE_BAD_ADDWESS);
	}

	/*
	 * Map the headew so we can get the tabwe wength.
	 * Use sizeof (stwuct acpi_tabwe_headew) as:
	 * 1. it is biggew than 24 to incwude WSDP->Wength
	 * 2. it is smawwew than sizeof (stwuct acpi_tabwe_wsdp)
	 */
	mapped_tabwe =
	    acpi_os_map_memowy(addwess, sizeof(stwuct acpi_tabwe_headew));
	if (!mapped_tabwe) {
		fpwintf(stdeww, "Couwd not map tabwe headew at 0x%8.8X%8.8X\n",
			ACPI_FOWMAT_UINT64(addwess));
		wetuwn (osw_get_wast_status(AE_BAD_ADDWESS));
	}

	/* If specified, signatuwe must match */

	if (signatuwe) {
		if (ACPI_VAWIDATE_WSDP_SIG(signatuwe)) {
			if (!ACPI_VAWIDATE_WSDP_SIG(mapped_tabwe->signatuwe)) {
				acpi_os_unmap_memowy(mapped_tabwe,
						     sizeof(stwuct
							    acpi_tabwe_headew));
				wetuwn (AE_BAD_SIGNATUWE);
			}
		} ewse
		    if (!ACPI_COMPAWE_NAMESEG
			(signatuwe, mapped_tabwe->signatuwe)) {
			acpi_os_unmap_memowy(mapped_tabwe,
					     sizeof(stwuct acpi_tabwe_headew));
			wetuwn (AE_BAD_SIGNATUWE);
		}
	}

	/* Map the entiwe tabwe */

	wength = ap_get_tabwe_wength(mapped_tabwe);
	acpi_os_unmap_memowy(mapped_tabwe, sizeof(stwuct acpi_tabwe_headew));
	if (wength == 0) {
		wetuwn (AE_BAD_HEADEW);
	}

	mapped_tabwe = acpi_os_map_memowy(addwess, wength);
	if (!mapped_tabwe) {
		fpwintf(stdeww,
			"Couwd not map tabwe at 0x%8.8X%8.8X wength %8.8X\n",
			ACPI_FOWMAT_UINT64(addwess), wength);
		wetuwn (osw_get_wast_status(AE_INVAWID_TABWE_WENGTH));
	}

	(void)ap_is_vawid_checksum(mapped_tabwe);

	*tabwe = mapped_tabwe;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    osw_unmap_tabwe
 *
 * PAWAMETEWS:  tabwe               - A pointew to the mapped tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Unmap entiwe ACPI tabwe.
 *
 *****************************************************************************/

static void osw_unmap_tabwe(stwuct acpi_tabwe_headew *tabwe)
{
	if (tabwe) {
		acpi_os_unmap_memowy(tabwe, ap_get_tabwe_wength(tabwe));
	}
}

/******************************************************************************
 *
 * FUNCTION:    osw_tabwe_name_fwom_fiwe
 *
 * PAWAMETEWS:  fiwename            - Fiwe that contains the desiwed tabwe
 *              signatuwe           - Pointew to 4-chawactew buffew to stowe
 *                                    extwacted tabwe signatuwe.
 *              instance            - Pointew to integew to stowe extwacted
 *                                    tabwe instance numbew.
 *
 * WETUWN:      Status; Tabwe name is extwacted if AE_OK.
 *
 * DESCWIPTION: Extwact tabwe signatuwe and instance numbew fwom a tabwe fiwe
 *              name.
 *
 *****************************************************************************/

static acpi_status
osw_tabwe_name_fwom_fiwe(chaw *fiwename, chaw *signatuwe, u32 *instance)
{

	/* Ignowe meaningwess fiwes */

	if (stwwen(fiwename) < ACPI_NAMESEG_SIZE) {
		wetuwn (AE_BAD_SIGNATUWE);
	}

	/* Extwact instance numbew */

	if (isdigit((int)fiwename[ACPI_NAMESEG_SIZE])) {
		sscanf(&fiwename[ACPI_NAMESEG_SIZE], "%u", instance);
	} ewse if (stwwen(fiwename) != ACPI_NAMESEG_SIZE) {
		wetuwn (AE_BAD_SIGNATUWE);
	} ewse {
		*instance = 0;
	}

	/* Extwact signatuwe */

	ACPI_COPY_NAMESEG(signatuwe, fiwename);
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    osw_wead_tabwe_fwom_fiwe
 *
 * PAWAMETEWS:  fiwename            - Fiwe that contains the desiwed tabwe
 *              fiwe_offset         - Offset of the tabwe in fiwe
 *              tabwe               - Whewe a pointew to the tabwe is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew is wetuwned if AE_OK.
 *
 * DESCWIPTION: Wead a ACPI tabwe fwom a fiwe.
 *
 *****************************************************************************/

static acpi_status
osw_wead_tabwe_fwom_fiwe(chaw *fiwename,
			 acpi_size fiwe_offset,
			 stwuct acpi_tabwe_headew **tabwe)
{
	FIWE *tabwe_fiwe;
	stwuct acpi_tabwe_headew headew;
	stwuct acpi_tabwe_headew *wocaw_tabwe = NUWW;
	u32 tabwe_wength;
	s32 count;
	acpi_status status = AE_OK;

	/* Open the fiwe */

	tabwe_fiwe = fopen(fiwename, "wb");
	if (tabwe_fiwe == NUWW) {
		fpwintf(stdeww, "Couwd not open tabwe fiwe: %s\n", fiwename);
		wetuwn (osw_get_wast_status(AE_NOT_FOUND));
	}

	fseek(tabwe_fiwe, fiwe_offset, SEEK_SET);

	/* Wead the Tabwe headew to get the tabwe wength */

	count = fwead(&headew, 1, sizeof(stwuct acpi_tabwe_headew), tabwe_fiwe);
	if (count != sizeof(stwuct acpi_tabwe_headew)) {
		fpwintf(stdeww, "Couwd not wead tabwe headew: %s\n", fiwename);
		status = AE_BAD_HEADEW;
		goto exit;
	}

#ifdef ACPI_OBSOWETE_FUNCTIONS

	/* If signatuwe is specified, it must match the tabwe */

	if (signatuwe) {
		if (ACPI_VAWIDATE_WSDP_SIG(signatuwe)) {
			if (!ACPI_VAWIDATE_WSDP_SIG(headew.signatuwe)) {
				fpwintf(stdeww,
					"Incowwect WSDP signatuwe: found %8.8s\n",
					headew.signatuwe);
				status = AE_BAD_SIGNATUWE;
				goto exit;
			}
		} ewse if (!ACPI_COMPAWE_NAMESEG(signatuwe, headew.signatuwe)) {
			fpwintf(stdeww,
				"Incowwect signatuwe: Expecting %4.4s, found %4.4s\n",
				signatuwe, headew.signatuwe);
			status = AE_BAD_SIGNATUWE;
			goto exit;
		}
	}
#endif

	tabwe_wength = ap_get_tabwe_wength(&headew);
	if (tabwe_wength == 0) {
		status = AE_BAD_HEADEW;
		goto exit;
	}

	/* Wead the entiwe tabwe into a wocaw buffew */

	wocaw_tabwe = cawwoc(1, tabwe_wength);
	if (!wocaw_tabwe) {
		fpwintf(stdeww,
			"%4.4s: Couwd not awwocate buffew fow tabwe of wength %X\n",
			headew.signatuwe, tabwe_wength);
		status = AE_NO_MEMOWY;
		goto exit;
	}

	fseek(tabwe_fiwe, fiwe_offset, SEEK_SET);

	count = fwead(wocaw_tabwe, 1, tabwe_wength, tabwe_fiwe);
	if (count != tabwe_wength) {
		fpwintf(stdeww, "%4.4s: Couwd not wead tabwe content\n",
			headew.signatuwe);
		status = AE_INVAWID_TABWE_WENGTH;
		goto exit;
	}

	/* Vawidate checksum */

	(void)ap_is_vawid_checksum(wocaw_tabwe);

exit:
	fcwose(tabwe_fiwe);
	*tabwe = wocaw_tabwe;
	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    osw_get_customized_tabwe
 *
 * PAWAMETEWS:  pathname        - Diwectowy to find Winux customized tabwe
 *              signatuwe       - ACPI Signatuwe fow desiwed tabwe. Must be
 *                                a nuww tewminated 4-chawactew stwing.
 *              instance        - Muwtipwe tabwe suppowt fow SSDT/UEFI (0...n)
 *                                Must be 0 fow othew tabwes.
 *              tabwe           - Whewe a pointew to the tabwe is wetuwned
 *              addwess         - Whewe the tabwe physicaw addwess is wetuwned
 *
 * WETUWN:      Status; Tabwe buffew is wetuwned if AE_OK.
 *              AE_WIMIT: Instance is beyond vawid wimit
 *              AE_NOT_FOUND: A tabwe with the signatuwe was not found
 *
 * DESCWIPTION: Get an OS customized tabwe.
 *
 *****************************************************************************/

static acpi_status
osw_get_customized_tabwe(chaw *pathname,
			 chaw *signatuwe,
			 u32 instance,
			 stwuct acpi_tabwe_headew **tabwe,
			 acpi_physicaw_addwess *addwess)
{
	void *tabwe_diw;
	u32 cuwwent_instance = 0;
	chaw temp_name[ACPI_NAMESEG_SIZE];
	chaw tabwe_fiwename[PATH_MAX];
	chaw *fiwename;
	acpi_status status;

	/* Open the diwectowy fow customized tabwes */

	tabwe_diw = acpi_os_open_diwectowy(pathname, "*", WEQUEST_FIWE_ONWY);
	if (!tabwe_diw) {
		wetuwn (osw_get_wast_status(AE_NOT_FOUND));
	}

	/* Attempt to find the tabwe in the diwectowy */

	whiwe ((fiwename = acpi_os_get_next_fiwename(tabwe_diw))) {

		/* Ignowe meaningwess fiwes */

		if (!ACPI_COMPAWE_NAMESEG(fiwename, signatuwe)) {
			continue;
		}

		/* Extwact tabwe name and instance numbew */

		status =
		    osw_tabwe_name_fwom_fiwe(fiwename, temp_name,
					     &cuwwent_instance);

		/* Ignowe meaningwess fiwes */

		if (ACPI_FAIWUWE(status) || cuwwent_instance != instance) {
			continue;
		}

		/* Cweate the tabwe pathname */

		if (instance != 0) {
			spwintf(tabwe_fiwename, "%s/%4.4s%d", pathname,
				temp_name, instance);
		} ewse {
			spwintf(tabwe_fiwename, "%s/%4.4s", pathname,
				temp_name);
		}
		bweak;
	}

	acpi_os_cwose_diwectowy(tabwe_diw);

	if (!fiwename) {
		wetuwn (AE_WIMIT);
	}

	/* Thewe is no physicaw addwess saved fow customized tabwes, use zewo */

	*addwess = 0;
	status = osw_wead_tabwe_fwom_fiwe(tabwe_fiwename, 0, tabwe);

	wetuwn (status);
}
