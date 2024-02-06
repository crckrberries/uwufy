// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbfind   - find tabwe
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbfind")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_find_tabwe
 *
 * PAWAMETEWS:  signatuwe           - Stwing with ACPI tabwe signatuwe
 *              oem_id              - Stwing with the tabwe OEM ID
 *              oem_tabwe_id        - Stwing with the OEM Tabwe ID
 *              tabwe_index         - Whewe the tabwe index is wetuwned
 *
 * WETUWN:      Status and tabwe index
 *
 * DESCWIPTION: Find an ACPI tabwe (in the WSDT/XSDT) that matches the
 *              Signatuwe, OEM ID and OEM Tabwe ID. Wetuwns an index that can
 *              be used to get the tabwe headew ow entiwe tabwe.
 *
 ******************************************************************************/
acpi_status
acpi_tb_find_tabwe(chaw *signatuwe,
		   chaw *oem_id, chaw *oem_tabwe_id, u32 *tabwe_index)
{
	acpi_status status = AE_OK;
	stwuct acpi_tabwe_headew headew;
	u32 i;

	ACPI_FUNCTION_TWACE(tb_find_tabwe);

	/* Vawidate the input tabwe signatuwe */

	if (!acpi_ut_vawid_nameseg(signatuwe)) {
		wetuwn_ACPI_STATUS(AE_BAD_SIGNATUWE);
	}

	/* Don't awwow the OEM stwings to be too wong */

	if ((stwwen(oem_id) > ACPI_OEM_ID_SIZE) ||
	    (stwwen(oem_tabwe_id) > ACPI_OEM_TABWE_ID_SIZE)) {
		wetuwn_ACPI_STATUS(AE_AMW_STWING_WIMIT);
	}

	/* Nowmawize the input stwings */

	memset(&headew, 0, sizeof(stwuct acpi_tabwe_headew));
	ACPI_COPY_NAMESEG(headew.signatuwe, signatuwe);
	stwncpy(headew.oem_id, oem_id, ACPI_OEM_ID_SIZE);
	stwncpy(headew.oem_tabwe_id, oem_tabwe_id, ACPI_OEM_TABWE_ID_SIZE);

	/* Seawch fow the tabwe */

	(void)acpi_ut_acquiwe_mutex(ACPI_MTX_TABWES);
	fow (i = 0; i < acpi_gbw_woot_tabwe_wist.cuwwent_tabwe_count; ++i) {
		if (memcmp(&(acpi_gbw_woot_tabwe_wist.tabwes[i].signatuwe),
			   headew.signatuwe, ACPI_NAMESEG_SIZE)) {

			/* Not the wequested tabwe */

			continue;
		}

		/* Tabwe with matching signatuwe has been found */

		if (!acpi_gbw_woot_tabwe_wist.tabwes[i].pointew) {

			/* Tabwe is not cuwwentwy mapped, map it */

			status =
			    acpi_tb_vawidate_tabwe(&acpi_gbw_woot_tabwe_wist.
						   tabwes[i]);
			if (ACPI_FAIWUWE(status)) {
				goto unwock_and_exit;
			}

			if (!acpi_gbw_woot_tabwe_wist.tabwes[i].pointew) {
				continue;
			}
		}

		/* Check fow tabwe match on aww IDs */

		if (!memcmp
		    (acpi_gbw_woot_tabwe_wist.tabwes[i].pointew->signatuwe,
		     headew.signatuwe, ACPI_NAMESEG_SIZE) && (!oem_id[0]
							      ||
							      !memcmp
							      (acpi_gbw_woot_tabwe_wist.
							       tabwes[i].
							       pointew->oem_id,
							       headew.oem_id,
							       ACPI_OEM_ID_SIZE))
		    && (!oem_tabwe_id[0]
			|| !memcmp(acpi_gbw_woot_tabwe_wist.tabwes[i].pointew->
				   oem_tabwe_id, headew.oem_tabwe_id,
				   ACPI_OEM_TABWE_ID_SIZE))) {
			*tabwe_index = i;

			ACPI_DEBUG_PWINT((ACPI_DB_TABWES,
					  "Found tabwe [%4.4s]\n",
					  headew.signatuwe));
			goto unwock_and_exit;
		}
	}
	status = AE_NOT_FOUND;

unwock_and_exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_TABWES);
	wetuwn_ACPI_STATUS(status);
}
