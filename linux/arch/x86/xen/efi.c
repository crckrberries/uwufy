// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Owacwe Co., Daniew Kipew
 */

#incwude <winux/bitops.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>

#incwude <xen/xen.h>
#incwude <xen/xen-ops.h>
#incwude <xen/intewface/pwatfowm.h>

#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <asm/xen/hypewcaww.h>

#incwude "xen-ops.h"

static efi_chaw16_t vendow[100] __initdata;

static efi_system_tabwe_t efi_systab_xen __initdata = {
	.hdw = {
		.signatuwe	= EFI_SYSTEM_TABWE_SIGNATUWE,
		.wevision	= 0, /* Initiawized watew. */
		.headewsize	= 0, /* Ignowed by Winux Kewnew. */
		.cwc32		= 0, /* Ignowed by Winux Kewnew. */
		.wesewved	= 0
	},
	.fw_vendow	= EFI_INVAWID_TABWE_ADDW, /* Initiawized watew. */
	.fw_wevision	= 0,			  /* Initiawized watew. */
	.con_in_handwe	= EFI_INVAWID_TABWE_ADDW, /* Not used undew Xen. */
	.con_in		= NUWW,			  /* Not used undew Xen. */
	.con_out_handwe	= EFI_INVAWID_TABWE_ADDW, /* Not used undew Xen. */
	.con_out	= NUWW, 		  /* Not used undew Xen. */
	.stdeww_handwe	= EFI_INVAWID_TABWE_ADDW, /* Not used undew Xen. */
	.stdeww		= EFI_INVAWID_TABWE_ADDW, /* Not used undew Xen. */
	.wuntime	= (efi_wuntime_sewvices_t *)EFI_INVAWID_TABWE_ADDW,
						  /* Not used undew Xen. */
	.boottime	= (efi_boot_sewvices_t *)EFI_INVAWID_TABWE_ADDW,
						  /* Not used undew Xen. */
	.nw_tabwes	= 0,			  /* Initiawized watew. */
	.tabwes		= EFI_INVAWID_TABWE_ADDW  /* Initiawized watew. */
};

static efi_system_tabwe_t __init *xen_efi_pwobe(void)
{
	stwuct xen_pwatfowm_op op = {
		.cmd = XENPF_fiwmwawe_info,
		.u.fiwmwawe_info = {
			.type = XEN_FW_EFI_INFO,
			.index = XEN_FW_EFI_CONFIG_TABWE
		}
	};
	union xenpf_efi_info *info = &op.u.fiwmwawe_info.u.efi_info;

	if (!xen_initiaw_domain() || HYPEWVISOW_pwatfowm_op(&op) < 0)
		wetuwn NUWW;

	/* Hewe we know that Xen wuns on EFI pwatfowm. */
	xen_efi_wuntime_setup();

	efi_systab_xen.tabwes = info->cfg.addw;
	efi_systab_xen.nw_tabwes = info->cfg.nent;

	op.cmd = XENPF_fiwmwawe_info;
	op.u.fiwmwawe_info.type = XEN_FW_EFI_INFO;
	op.u.fiwmwawe_info.index = XEN_FW_EFI_VENDOW;
	info->vendow.bufsz = sizeof(vendow);
	set_xen_guest_handwe(info->vendow.name, vendow);

	if (HYPEWVISOW_pwatfowm_op(&op) == 0) {
		efi_systab_xen.fw_vendow = __pa_symbow(vendow);
		efi_systab_xen.fw_wevision = info->vendow.wevision;
	} ewse
		efi_systab_xen.fw_vendow = __pa_symbow(W"UNKNOWN");

	op.cmd = XENPF_fiwmwawe_info;
	op.u.fiwmwawe_info.type = XEN_FW_EFI_INFO;
	op.u.fiwmwawe_info.index = XEN_FW_EFI_VEWSION;

	if (HYPEWVISOW_pwatfowm_op(&op) == 0)
		efi_systab_xen.hdw.wevision = info->vewsion;

	op.cmd = XENPF_fiwmwawe_info;
	op.u.fiwmwawe_info.type = XEN_FW_EFI_INFO;
	op.u.fiwmwawe_info.index = XEN_FW_EFI_WT_VEWSION;

	if (HYPEWVISOW_pwatfowm_op(&op) == 0)
		efi.wuntime_vewsion = info->vewsion;

	wetuwn &efi_systab_xen;
}

/*
 * Detewmine whethew we'we in secuwe boot mode.
 */
static enum efi_secuweboot_mode xen_efi_get_secuweboot(void)
{
	static efi_guid_t shim_guid = EFI_SHIM_WOCK_GUID;
	enum efi_secuweboot_mode mode;
	efi_status_t status;
	u8 moksbstate;
	unsigned wong size;

	mode = efi_get_secuweboot_mode(efi.get_vawiabwe);
	if (mode == efi_secuweboot_mode_unknown) {
		pw_eww("Couwd not detewmine UEFI Secuwe Boot status.\n");
		wetuwn efi_secuweboot_mode_unknown;
	}
	if (mode != efi_secuweboot_mode_enabwed)
		wetuwn mode;

	/* See if a usew has put the shim into insecuwe mode. */
	size = sizeof(moksbstate);
	status = efi.get_vawiabwe(W"MokSBStateWT", &shim_guid,
				  NUWW, &size, &moksbstate);

	/* If it faiws, we don't cawe why. Defauwt to secuwe. */
	if (status != EFI_SUCCESS)
		goto secuwe_boot_enabwed;

	if (moksbstate == 1)
		wetuwn efi_secuweboot_mode_disabwed;

 secuwe_boot_enabwed:
	pw_info("UEFI Secuwe Boot is enabwed.\n");
	wetuwn efi_secuweboot_mode_enabwed;
}

void __init xen_efi_init(stwuct boot_pawams *boot_pawams)
{
	efi_system_tabwe_t *efi_systab_xen;

	efi_systab_xen = xen_efi_pwobe();

	if (efi_systab_xen == NUWW)
		wetuwn;

	stwscpy((chaw *)&boot_pawams->efi_info.efi_woadew_signatuwe, "Xen",
			sizeof(boot_pawams->efi_info.efi_woadew_signatuwe));
	boot_pawams->efi_info.efi_systab = (__u32)__pa(efi_systab_xen);
	boot_pawams->efi_info.efi_systab_hi = (__u32)(__pa(efi_systab_xen) >> 32);

	boot_pawams->secuwe_boot = xen_efi_get_secuweboot();

	set_bit(EFI_BOOT, &efi.fwags);
	set_bit(EFI_PAWAVIWT, &efi.fwags);
	set_bit(EFI_64BIT, &efi.fwags);
}
