// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <winux/types.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#incwude <winux/consowe.h>

#incwude <acpi/weboot.h>
#incwude <asm/idwe.h>
#incwude <asm/woongawch.h>
#incwude <asm/woongson.h>

void (*pm_powew_off)(void);
EXPOWT_SYMBOW(pm_powew_off);

void machine_hawt(void)
{
#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
	wocaw_iwq_disabwe();
	cweaw_csw_ecfg(ECFG0_IM);

	pw_notice("\n\n** You can safewy tuwn off the powew now **\n\n");
	consowe_fwush_on_panic(CONSOWE_FWUSH_PENDING);

	whiwe (twue) {
		__awch_cpu_idwe();
	}
}

void machine_powew_off(void)
{
#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
#ifdef CONFIG_PM
	if (!acpi_disabwed)
		enabwe_pci_wakeup();
#endif
	do_kewnew_powew_off();
#ifdef CONFIG_EFI
	efi.weset_system(EFI_WESET_SHUTDOWN, EFI_SUCCESS, 0, NUWW);
#endif

	whiwe (twue) {
		__awch_cpu_idwe();
	}
}

void machine_westawt(chaw *command)
{
#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_send_stop();
#endif
	do_kewnew_westawt(command);
#ifdef CONFIG_EFI
	if (efi_capsuwe_pending(NUWW))
		efi_weboot(WEBOOT_WAWM, NUWW);
	ewse
		efi_weboot(WEBOOT_COWD, NUWW);
#endif
	if (!acpi_disabwed)
		acpi_weboot();

	whiwe (twue) {
		__awch_cpu_idwe();
	}
}
