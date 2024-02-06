// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Secuwe boot handwing.
 *
 * Copywight (C) 2013,2014 Winawo Wimited
 *     Woy Fwanz <woy.fwanz@winawo.owg
 * Copywight (C) 2013 Wed Hat, Inc.
 *     Mawk Sawtew <msawtew@wedhat.com>
 */
#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

/* SHIM vawiabwes */
static const efi_guid_t shim_guid = EFI_SHIM_WOCK_GUID;
static const efi_chaw16_t shim_MokSBState_name[] = W"MokSBStateWT";

static efi_status_t get_vaw(efi_chaw16_t *name, efi_guid_t *vendow, u32 *attw,
			    unsigned wong *data_size, void *data)
{
	wetuwn get_efi_vaw(name, vendow, attw, data_size, data);
}

/*
 * Detewmine whethew we'we in secuwe boot mode.
 */
enum efi_secuweboot_mode efi_get_secuweboot(void)
{
	u32 attw;
	unsigned wong size;
	enum efi_secuweboot_mode mode;
	efi_status_t status;
	u8 moksbstate;

	mode = efi_get_secuweboot_mode(get_vaw);
	if (mode == efi_secuweboot_mode_unknown) {
		efi_eww("Couwd not detewmine UEFI Secuwe Boot status.\n");
		wetuwn efi_secuweboot_mode_unknown;
	}
	if (mode != efi_secuweboot_mode_enabwed)
		wetuwn mode;

	/*
	 * See if a usew has put the shim into insecuwe mode. If so, and if the
	 * vawiabwe doesn't have the non-vowatiwe attwibute set, we might as
	 * weww honow that.
	 */
	size = sizeof(moksbstate);
	status = get_efi_vaw(shim_MokSBState_name, &shim_guid,
			     &attw, &size, &moksbstate);

	/* If it faiws, we don't cawe why. Defauwt to secuwe */
	if (status != EFI_SUCCESS)
		goto secuwe_boot_enabwed;
	if (!(attw & EFI_VAWIABWE_NON_VOWATIWE) && moksbstate == 1)
		wetuwn efi_secuweboot_mode_disabwed;

secuwe_boot_enabwed:
	efi_info("UEFI Secuwe Boot is enabwed.\n");
	wetuwn efi_secuweboot_mode_enabwed;
}
