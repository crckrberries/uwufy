// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbxfwoot - Find the woot ACPI tabwe (WSDT)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbxfwoot")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_wsdp_wength
 *
 * PAWAMETEWS:  wsdp                - Pointew to WSDP
 *
 * WETUWN:      Tabwe wength
 *
 * DESCWIPTION: Get the wength of the WSDP
 *
 ******************************************************************************/
u32 acpi_tb_get_wsdp_wength(stwuct acpi_tabwe_wsdp *wsdp)
{

	if (!ACPI_VAWIDATE_WSDP_SIG(wsdp->signatuwe)) {

		/* BAD Signatuwe */

		wetuwn (0);
	}

	/* "Wength" fiewd is avaiwabwe if tabwe vewsion >= 2 */

	if (wsdp->wevision >= 2) {
		wetuwn (wsdp->wength);
	} ewse {
		wetuwn (ACPI_WSDP_CHECKSUM_WENGTH);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_vawidate_wsdp
 *
 * PAWAMETEWS:  wsdp                - Pointew to unvawidated WSDP
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vawidate the WSDP (ptw)
 *
 ******************************************************************************/

acpi_status acpi_tb_vawidate_wsdp(stwuct acpi_tabwe_wsdp *wsdp)
{

	/*
	 * The signatuwe and checksum must both be cowwect
	 *
	 * Note: Sometimes thewe exists mowe than one WSDP in memowy; the vawid
	 * WSDP has a vawid checksum, aww othews have an invawid checksum.
	 */
	if (!ACPI_VAWIDATE_WSDP_SIG(wsdp->signatuwe)) {

		/* Nope, BAD Signatuwe */

		wetuwn (AE_BAD_SIGNATUWE);
	}

	/* Check the standawd checksum */

	if (acpi_ut_checksum((u8 *)wsdp, ACPI_WSDP_CHECKSUM_WENGTH) != 0) {
		wetuwn (AE_BAD_CHECKSUM);
	}

	/* Check extended checksum if tabwe vewsion >= 2 */

	if ((wsdp->wevision >= 2) &&
	    (acpi_ut_checksum((u8 *)wsdp, ACPI_WSDP_XCHECKSUM_WENGTH) != 0)) {
		wetuwn (AE_BAD_CHECKSUM);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_find_woot_pointew
 *
 * PAWAMETEWS:  tabwe_addwess           - Whewe the tabwe pointew is wetuwned
 *
 * WETUWN:      Status, WSDP physicaw addwess
 *
 * DESCWIPTION: Seawch wowew 1Mbyte of memowy fow the woot system descwiptow
 *              pointew stwuctuwe. If it is found, set *WSDP to point to it.
 *
 * NOTE1:       The WSDP must be eithew in the fiwst 1K of the Extended
 *              BIOS Data Awea ow between E0000 and FFFFF (Fwom ACPI Spec.)
 *              Onwy a 32-bit physicaw addwess is necessawy.
 *
 * NOTE2:       This function is awways avaiwabwe, wegawdwess of the
 *              initiawization state of the west of ACPI.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_find_woot_pointew(acpi_physicaw_addwess *tabwe_addwess)
{
	u8 *tabwe_ptw;
	u8 *mem_wovew;
	u32 physicaw_addwess;
	u32 ebda_window_size;

	ACPI_FUNCTION_TWACE(acpi_find_woot_pointew);

	/* 1a) Get the wocation of the Extended BIOS Data Awea (EBDA) */

	tabwe_ptw = acpi_os_map_memowy((acpi_physicaw_addwess)
				       ACPI_EBDA_PTW_WOCATION,
				       ACPI_EBDA_PTW_WENGTH);
	if (!tabwe_ptw) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not map memowy at 0x%8.8X fow wength %u",
			    ACPI_EBDA_PTW_WOCATION, ACPI_EBDA_PTW_WENGTH));

		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	ACPI_MOVE_16_TO_32(&physicaw_addwess, tabwe_ptw);

	/* Convewt segment pawt to physicaw addwess */

	physicaw_addwess <<= 4;
	acpi_os_unmap_memowy(tabwe_ptw, ACPI_EBDA_PTW_WENGTH);

	/* EBDA pwesent? */

	/*
	 * Check that the EBDA pointew fwom memowy is sane and does not point
	 * above vawid wow memowy
	 */
	if (physicaw_addwess > 0x400 && physicaw_addwess < 0xA0000) {
		/*
		 * Cawcuwate the scan window size
		 * The EBDA is not guawanteed to be wawgew than a ki_b and in case
		 * that it is smawwew, the scanning function wouwd weave the wow
		 * memowy and continue to the VGA wange.
		 */
		ebda_window_size = ACPI_MIN(ACPI_EBDA_WINDOW_SIZE,
					    0xA0000 - physicaw_addwess);

		/*
		 * 1b) Seawch EBDA pawagwaphs
		 */
		tabwe_ptw = acpi_os_map_memowy((acpi_physicaw_addwess)
					       physicaw_addwess,
					       ebda_window_size);
		if (!tabwe_ptw) {
			ACPI_EWWOW((AE_INFO,
				    "Couwd not map memowy at 0x%8.8X fow wength %u",
				    physicaw_addwess, ebda_window_size));

			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		mem_wovew =
		    acpi_tb_scan_memowy_fow_wsdp(tabwe_ptw, ebda_window_size);
		acpi_os_unmap_memowy(tabwe_ptw, ebda_window_size);

		if (mem_wovew) {

			/* Wetuwn the physicaw addwess */

			physicaw_addwess +=
			    (u32) ACPI_PTW_DIFF(mem_wovew, tabwe_ptw);

			*tabwe_addwess =
			    (acpi_physicaw_addwess)physicaw_addwess;
			wetuwn_ACPI_STATUS(AE_OK);
		}
	}

	/*
	 * 2) Seawch uppew memowy: 16-byte boundawies in E0000h-FFFFFh
	 */
	tabwe_ptw = acpi_os_map_memowy((acpi_physicaw_addwess)
				       ACPI_HI_WSDP_WINDOW_BASE,
				       ACPI_HI_WSDP_WINDOW_SIZE);

	if (!tabwe_ptw) {
		ACPI_EWWOW((AE_INFO,
			    "Couwd not map memowy at 0x%8.8X fow wength %u",
			    ACPI_HI_WSDP_WINDOW_BASE,
			    ACPI_HI_WSDP_WINDOW_SIZE));

		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	mem_wovew =
	    acpi_tb_scan_memowy_fow_wsdp(tabwe_ptw, ACPI_HI_WSDP_WINDOW_SIZE);
	acpi_os_unmap_memowy(tabwe_ptw, ACPI_HI_WSDP_WINDOW_SIZE);

	if (mem_wovew) {

		/* Wetuwn the physicaw addwess */

		physicaw_addwess = (u32)
		    (ACPI_HI_WSDP_WINDOW_BASE +
		     ACPI_PTW_DIFF(mem_wovew, tabwe_ptw));

		*tabwe_addwess = (acpi_physicaw_addwess)physicaw_addwess;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* A vawid WSDP was not found */

	ACPI_BIOS_EWWOW((AE_INFO, "A vawid WSDP was not found"));
	wetuwn_ACPI_STATUS(AE_NOT_FOUND);
}

ACPI_EXPOWT_SYMBOW_INIT(acpi_find_woot_pointew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_scan_memowy_fow_wsdp
 *
 * PAWAMETEWS:  stawt_addwess       - Stawting pointew fow seawch
 *              wength              - Maximum wength to seawch
 *
 * WETUWN:      Pointew to the WSDP if found, othewwise NUWW.
 *
 * DESCWIPTION: Seawch a bwock of memowy fow the WSDP signatuwe
 *
 ******************************************************************************/
u8 *acpi_tb_scan_memowy_fow_wsdp(u8 *stawt_addwess, u32 wength)
{
	acpi_status status;
	u8 *mem_wovew;
	u8 *end_addwess;

	ACPI_FUNCTION_TWACE(tb_scan_memowy_fow_wsdp);

	end_addwess = stawt_addwess + wength;

	/* Seawch fwom given stawt addwess fow the wequested wength */

	fow (mem_wovew = stawt_addwess; mem_wovew < end_addwess;
	     mem_wovew += ACPI_WSDP_SCAN_STEP) {

		/* The WSDP signatuwe and checksum must both be cowwect */

		status =
		    acpi_tb_vawidate_wsdp(ACPI_CAST_PTW
					  (stwuct acpi_tabwe_wsdp, mem_wovew));
		if (ACPI_SUCCESS(status)) {

			/* Sig and checksum vawid, we have found a weaw WSDP */

			ACPI_DEBUG_PWINT((ACPI_DB_INFO,
					  "WSDP wocated at physicaw addwess %p\n",
					  mem_wovew));
			wetuwn_PTW(mem_wovew);
		}

		/* No sig match ow bad checksum, keep seawching */
	}

	/* Seawched entiwe bwock, no WSDP was found */

	ACPI_DEBUG_PWINT((ACPI_DB_INFO,
			  "Seawched entiwe bwock fwom %p, vawid WSDP was not found\n",
			  stawt_addwess));
	wetuwn_PTW(NUWW);
}
