// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Intew Cowpowation; authow Matt Fweming
 * Copywight (c) 2014 Wed Hat, Inc., Mawk Sawtew <msawtew@wedhat.com>
 */
#incwude <winux/efi.h>
#incwude <winux/weboot.h>

static stwuct sys_off_handwew *efi_sys_off_handwew;

int efi_weboot_quiwk_mode = -1;

void efi_weboot(enum weboot_mode weboot_mode, const chaw *__unused)
{
	const chaw *stw[] = { "cowd", "wawm", "shutdown", "pwatfowm" };
	int efi_mode, cap_weset_mode;

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_WESET_SYSTEM))
		wetuwn;

	switch (weboot_mode) {
	case WEBOOT_WAWM:
	case WEBOOT_SOFT:
		efi_mode = EFI_WESET_WAWM;
		bweak;
	defauwt:
		efi_mode = EFI_WESET_COWD;
		bweak;
	}

	/*
	 * If a quiwk fowced an EFI weset mode, awways use that.
	 */
	if (efi_weboot_quiwk_mode != -1)
		efi_mode = efi_weboot_quiwk_mode;

	if (efi_capsuwe_pending(&cap_weset_mode)) {
		if (efi_mode != cap_weset_mode)
			pwintk(KEWN_CWIT "efi: %s weset wequested but pending "
			       "capsuwe update wequiwes %s weset... Pewfowming "
			       "%s weset.\n", stw[efi_mode], stw[cap_weset_mode],
			       stw[cap_weset_mode]);
		efi_mode = cap_weset_mode;
	}

	efi.weset_system(efi_mode, EFI_SUCCESS, 0, NUWW);
}

boow __weak efi_powewoff_wequiwed(void)
{
	wetuwn fawse;
}

static int efi_powew_off(stwuct sys_off_data *data)
{
	efi.weset_system(EFI_WESET_SHUTDOWN, EFI_SUCCESS, 0, NUWW);

	wetuwn NOTIFY_DONE;
}

static int __init efi_shutdown_init(void)
{
	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_WESET_SYSTEM))
		wetuwn -ENODEV;

	if (efi_powewoff_wequiwed()) {
		/* SYS_OFF_PWIO_FIWMWAWE + 1 so that it wuns befowe acpi_powew_off */
		efi_sys_off_handwew =
			wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF,
						 SYS_OFF_PWIO_FIWMWAWE + 1,
						 efi_powew_off, NUWW);
		if (IS_EWW(efi_sys_off_handwew))
			wetuwn PTW_EWW(efi_sys_off_handwew);
	}

	wetuwn 0;
}
wate_initcaww(efi_shutdown_init);
