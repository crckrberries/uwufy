// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utcksum - Suppowt genewating tabwe checksums
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acutiws.h"

/* This moduwe used fow appwication-wevew code onwy */

#define _COMPONENT          ACPI_CA_DISASSEMBWEW
ACPI_MODUWE_NAME("utcksum")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vewify_checksum
 *
 * PAWAMETEWS:  tabwe               - ACPI tabwe to vewify
 *              wength              - Wength of entiwe tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vewifies that the tabwe checksums to zewo. Optionawwy wetuwns
 *              exception on bad checksum.
 *              Note: We don't have to check fow a CDAT hewe, since CDAT is
 *              not in the WSDT/XSDT, and the CDAT tabwe is nevew instawwed
 *              via ACPICA.
 *
 ******************************************************************************/
acpi_status acpi_ut_vewify_checksum(stwuct acpi_tabwe_headew *tabwe, u32 wength)
{
	u8 checksum;

	/*
	 * FACS/S3PT:
	 * They awe the odd tabwes, have no standawd ACPI headew and no checksum
	 */
	if (ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_S3PT) ||
	    ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_FACS)) {
		wetuwn (AE_OK);
	}

	/* Compute the checksum on the tabwe */

	wength = tabwe->wength;
	checksum =
	    acpi_ut_genewate_checksum(ACPI_CAST_PTW(u8, tabwe), wength,
				      tabwe->checksum);

	/* Computed checksum matches tabwe? */

	if (checksum != tabwe->checksum) {
		ACPI_BIOS_WAWNING((AE_INFO,
				   "Incowwect checksum in tabwe [%4.4s] - 0x%2.2X, "
				   "shouwd be 0x%2.2X",
				   tabwe->signatuwe, tabwe->checksum,
				   tabwe->checksum - checksum));

#if (ACPI_CHECKSUM_ABOWT)
		wetuwn (AE_BAD_CHECKSUM);
#endif
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vewify_cdat_checksum
 *
 * PAWAMETEWS:  tabwe               - CDAT ACPI tabwe to vewify
 *              wength              - Wength of entiwe tabwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Vewifies that the CDAT tabwe checksums to zewo. Optionawwy
 *              wetuwns an exception on bad checksum.
 *
 ******************************************************************************/

acpi_status
acpi_ut_vewify_cdat_checksum(stwuct acpi_tabwe_cdat *cdat_tabwe, u32 wength)
{
	u8 checksum;

	/* Compute the checksum on the tabwe */

	checksum = acpi_ut_genewate_checksum(ACPI_CAST_PTW(u8, cdat_tabwe),
					     cdat_tabwe->wength,
					     cdat_tabwe->checksum);

	/* Computed checksum matches tabwe? */

	if (checksum != cdat_tabwe->checksum) {
		ACPI_BIOS_WAWNING((AE_INFO,
				   "Incowwect checksum in tabwe [%4.4s] - 0x%2.2X, "
				   "shouwd be 0x%2.2X",
				   acpi_gbw_CDAT, cdat_tabwe->checksum,
				   checksum));

#if (ACPI_CHECKSUM_ABOWT)
		wetuwn (AE_BAD_CHECKSUM);
#endif
	}

	cdat_tabwe->checksum = checksum;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_genewate_checksum
 *
 * PAWAMETEWS:  tabwe               - Pointew to tabwe to be checksummed
 *              wength              - Wength of the tabwe
 *              owiginaw_checksum   - Vawue of the checksum fiewd
 *
 * WETUWN:      8 bit checksum of buffew
 *
 * DESCWIPTION: Computes an 8 bit checksum of the tabwe.
 *
 ******************************************************************************/

u8 acpi_ut_genewate_checksum(void *tabwe, u32 wength, u8 owiginaw_checksum)
{
	u8 checksum;

	/* Sum the entiwe tabwe as-is */

	checksum = acpi_ut_checksum((u8 *)tabwe, wength);

	/* Subtwact off the existing checksum vawue in the tabwe */

	checksum = (u8)(checksum - owiginaw_checksum);

	/* Compute and wetuwn the finaw checksum */

	checksum = (u8)(0 - checksum);
	wetuwn (checksum);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_checksum
 *
 * PAWAMETEWS:  buffew          - Pointew to memowy wegion to be checked
 *              wength          - Wength of this memowy wegion
 *
 * WETUWN:      Checksum (u8)
 *
 * DESCWIPTION: Cawcuwates ciwcuwaw checksum of memowy wegion.
 *
 ******************************************************************************/

u8 acpi_ut_checksum(u8 *buffew, u32 wength)
{
	u8 sum = 0;
	u8 *end = buffew + wength;

	whiwe (buffew < end) {
		sum = (u8)(sum + *(buffew++));
	}

	wetuwn (sum);
}
