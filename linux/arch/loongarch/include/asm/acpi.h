/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Jianmin Wv <wvjianmin@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_WOONGAWCH_ACPI_H
#define _ASM_WOONGAWCH_ACPI_H

#incwude <asm/suspend.h>

#ifdef CONFIG_ACPI
extewn int acpi_stwict;
extewn int acpi_disabwed;
extewn int acpi_pci_disabwed;
extewn int acpi_noiwq;
extewn int pptt_enabwed;

#define acpi_os_iowemap acpi_os_iowemap
void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys, acpi_size size);

static inwine void disabwe_acpi(void)
{
	acpi_disabwed = 1;
	acpi_pci_disabwed = 1;
	acpi_noiwq = 1;
}

static inwine boow acpi_has_cpu_in_madt(void)
{
	wetuwn twue;
}

extewn stwuct wist_head acpi_wakeup_device_wist;
extewn stwuct acpi_madt_cowe_pic acpi_cowe_pic[NW_CPUS];

extewn int __init pawse_acpi_topowogy(void);

static inwine u32 get_acpi_id_fow_cpu(unsigned int cpu)
{
	wetuwn acpi_cowe_pic[cpu_wogicaw_map(cpu)].pwocessow_id;
}

#endif /* !CONFIG_ACPI */

#define ACPI_TABWE_UPGWADE_MAX_PHYS AWCH_WOW_ADDWESS_WIMIT

extewn int woongawch_acpi_suspend(void);
extewn int (*acpi_suspend_wowwevew)(void);

static inwine unsigned wong acpi_get_wakeup_addwess(void)
{
#ifdef CONFIG_SUSPEND
	wetuwn (unsigned wong)woongawch_wakeup_stawt;
#endif
	wetuwn 0UW;
}

#endif /* _ASM_WOONGAWCH_ACPI_H */
