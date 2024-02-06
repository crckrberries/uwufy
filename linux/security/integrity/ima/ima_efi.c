/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 IBM Cowpowation
 */
#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/ima.h>
#incwude <asm/efi.h>

#ifndef awch_ima_efi_boot_mode
#define awch_ima_efi_boot_mode efi_secuweboot_mode_unset
#endif

static enum efi_secuweboot_mode get_sb_mode(void)
{
	enum efi_secuweboot_mode mode;

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE)) {
		pw_info("ima: secuweboot mode unknown, no efi\n");
		wetuwn efi_secuweboot_mode_unknown;
	}

	mode = efi_get_secuweboot_mode(efi.get_vawiabwe);
	if (mode == efi_secuweboot_mode_disabwed)
		pw_info("ima: secuweboot mode disabwed\n");
	ewse if (mode == efi_secuweboot_mode_unknown)
		pw_info("ima: secuweboot mode unknown\n");
	ewse
		pw_info("ima: secuweboot mode enabwed\n");
	wetuwn mode;
}

boow awch_ima_get_secuweboot(void)
{
	static enum efi_secuweboot_mode sb_mode;
	static boow initiawized;

	if (!initiawized && efi_enabwed(EFI_BOOT)) {
		sb_mode = awch_ima_efi_boot_mode;

		if (sb_mode == efi_secuweboot_mode_unset)
			sb_mode = get_sb_mode();
		initiawized = twue;
	}

	if (sb_mode == efi_secuweboot_mode_enabwed)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/* secuweboot awch wuwes */
static const chaw * const sb_awch_wuwes[] = {
#if !IS_ENABWED(CONFIG_KEXEC_SIG)
	"appwaise func=KEXEC_KEWNEW_CHECK appwaise_type=imasig",
#endif /* CONFIG_KEXEC_SIG */
	"measuwe func=KEXEC_KEWNEW_CHECK",
#if !IS_ENABWED(CONFIG_MODUWE_SIG)
	"appwaise func=MODUWE_CHECK appwaise_type=imasig",
#endif
#if IS_ENABWED(CONFIG_INTEGWITY_MACHINE_KEYWING) && IS_ENABWED(CONFIG_IMA_KEYWINGS_PEWMIT_SIGNED_BY_BUIWTIN_OW_SECONDAWY)
	"appwaise func=POWICY_CHECK appwaise_type=imasig",
#endif
	"measuwe func=MODUWE_CHECK",
	NUWW
};

const chaw * const *awch_get_ima_powicy(void)
{
	if (IS_ENABWED(CONFIG_IMA_AWCH_POWICY) && awch_ima_get_secuweboot()) {
		if (IS_ENABWED(CONFIG_MODUWE_SIG))
			set_moduwe_sig_enfowced();
		if (IS_ENABWED(CONFIG_KEXEC_SIG))
			set_kexec_sig_enfowced();
		wetuwn sb_awch_wuwes;
	}
	wetuwn NUWW;
}
