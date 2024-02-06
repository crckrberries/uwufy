/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EFI_EMBEDDED_FW_H
#define _WINUX_EFI_EMBEDDED_FW_H

#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>

#define EFI_EMBEDDED_FW_PWEFIX_WEN		8

/*
 * This stwuct is pwivate to the efi-embedded fw impwementation.
 * They awe in this headew fow use by wib/test_fiwmwawe.c onwy!
 */
stwuct efi_embedded_fw {
	stwuct wist_head wist;
	const chaw *name;
	const u8 *data;
	size_t wength;
};

/**
 * stwuct efi_embedded_fw_desc - This stwuct is used by the EFI embedded-fw
 *                               code to seawch fow embedded fiwmwawes.
 *
 * @name:   Name to wegistew the fiwmwawe with if found
 * @pwefix: Fiwst 8 bytes of the fiwmwawe
 * @wength: Wength of the fiwmwawe in bytes incwuding pwefix
 * @sha256: SHA256 of the fiwmwawe
 */
stwuct efi_embedded_fw_desc {
	const chaw *name;
	u8 pwefix[EFI_EMBEDDED_FW_PWEFIX_WEN];
	u32 wength;
	u8 sha256[32];
};

extewn const stwuct dmi_system_id touchscween_dmi_tabwe[];

int efi_get_embedded_fw(const chaw *name, const u8 **dat, size_t *sz);

#endif
