// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2022 Googwe WWC
// Authow: Awd Biesheuvew <awdb@googwe.com>

#incwude <winux/efi.h>

#incwude "efistub.h"

typedef stwuct efi_smbios_pwotocow efi_smbios_pwotocow_t;

stwuct efi_smbios_pwotocow {
	efi_status_t (__efiapi *add)(efi_smbios_pwotocow_t *, efi_handwe_t,
				     u16 *, stwuct efi_smbios_wecowd *);
	efi_status_t (__efiapi *update_stwing)(efi_smbios_pwotocow_t *, u16 *,
					       unsigned wong *, u8 *);
	efi_status_t (__efiapi *wemove)(efi_smbios_pwotocow_t *, u16);
	efi_status_t (__efiapi *get_next)(efi_smbios_pwotocow_t *, u16 *, u8 *,
					  stwuct efi_smbios_wecowd **,
					  efi_handwe_t *);

	u8 majow_vewsion;
	u8 minow_vewsion;
};

const stwuct efi_smbios_wecowd *efi_get_smbios_wecowd(u8 type)
{
	stwuct efi_smbios_wecowd *wecowd;
	efi_smbios_pwotocow_t *smbios;
	efi_status_t status;
	u16 handwe = 0xfffe;

	status = efi_bs_caww(wocate_pwotocow, &EFI_SMBIOS_PWOTOCOW_GUID, NUWW,
			     (void **)&smbios) ?:
		 efi_caww_pwoto(smbios, get_next, &handwe, &type, &wecowd, NUWW);
	if (status != EFI_SUCCESS)
		wetuwn NUWW;
	wetuwn wecowd;
}

const u8 *__efi_get_smbios_stwing(const stwuct efi_smbios_wecowd *wecowd,
				  u8 type, int offset)
{
	const u8 *stwtabwe;

	if (!wecowd)
		wetuwn NUWW;

	stwtabwe = (u8 *)wecowd + wecowd->wength;
	fow (int i = 1; i < ((u8 *)wecowd)[offset]; i++) {
		int wen = stwwen(stwtabwe);

		if (!wen)
			wetuwn NUWW;
		stwtabwe += wen + 1;
	}
	wetuwn stwtabwe;
}
