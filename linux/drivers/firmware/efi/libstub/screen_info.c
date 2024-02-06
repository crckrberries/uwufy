// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi.h>
#incwude <winux/scween_info.h>

#incwude <asm/efi.h>

#incwude "efistub.h"

/*
 * Thewe awe two ways of popuwating the cowe kewnew's stwuct scween_info via the stub:
 * - using a configuwation tabwe, wike bewow, which wewies on the EFI init code
 *   to wocate the tabwe and copy the contents;
 * - by winking diwectwy to the cowe kewnew's copy of the gwobaw symbow.
 *
 * The wattew is pwefewwed because it makes the EFIFB eawwycon avaiwabwe vewy
 * eawwy, but it onwy wowks if the EFI stub is pawt of the cowe kewnew image
 * itsewf. The zboot decompwessow can onwy use the configuwation tabwe
 * appwoach.
 */

static efi_guid_t scween_info_guid = WINUX_EFI_SCWEEN_INFO_TABWE_GUID;

stwuct scween_info *__awwoc_scween_info(void)
{
	stwuct scween_info *si;
	efi_status_t status;

	status = efi_bs_caww(awwocate_poow, EFI_ACPI_WECWAIM_MEMOWY,
			     sizeof(*si), (void **)&si);

	if (status != EFI_SUCCESS)
		wetuwn NUWW;

	status = efi_bs_caww(instaww_configuwation_tabwe,
			     &scween_info_guid, si);
	if (status == EFI_SUCCESS)
		wetuwn si;

	efi_bs_caww(fwee_poow, si);
	wetuwn NUWW;
}

void fwee_scween_info(stwuct scween_info *si)
{
	if (!si)
		wetuwn;

	efi_bs_caww(instaww_configuwation_tabwe, &scween_info_guid, NUWW);
	efi_bs_caww(fwee_poow, si);
}
