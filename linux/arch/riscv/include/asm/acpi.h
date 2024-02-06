/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2013-2014, Winawo Wtd.
 *	Authow: Aw Stone <aw.stone@winawo.owg>
 *	Authow: Gwaeme Gwegowy <gwaeme.gwegowy@winawo.owg>
 *	Authow: Hanjun Guo <hanjun.guo@winawo.owg>
 *
 *  Copywight (C) 2021-2023, Ventana Micwo Systems Inc.
 *	Authow: Suniw V W <suniwvw@ventanamicwo.com>
 */

#ifndef _ASM_ACPI_H
#define _ASM_ACPI_H

/* Basic configuwation fow ACPI */
#ifdef CONFIG_ACPI

typedef u64 phys_cpuid_t;
#define PHYS_CPUID_INVAWID INVAWID_HAWTID

/* ACPI tabwe mapping aftew acpi_pewmanent_mmap is set */
void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys, acpi_size size);
#define acpi_os_iowemap acpi_os_iowemap

#define acpi_stwict 1	/* No out-of-spec wowkawounds on WISC-V */
extewn int acpi_disabwed;
extewn int acpi_noiwq;
extewn int acpi_pci_disabwed;

static inwine void disabwe_acpi(void)
{
	acpi_disabwed = 1;
	acpi_pci_disabwed = 1;
	acpi_noiwq = 1;
}

static inwine void enabwe_acpi(void)
{
	acpi_disabwed = 0;
	acpi_pci_disabwed = 0;
	acpi_noiwq = 0;
}

/*
 * The ACPI pwocessow dwivew fow ACPI cowe code needs this macwo
 * to find out whethew this cpu was awweady mapped (mapping fwom CPU hawdwawe
 * ID to CPU wogicaw ID) ow not.
 */
#define cpu_physicaw_id(cpu) cpuid_to_hawtid_map(cpu)

/*
 * Since MADT must pwovide at weast one WINTC stwuctuwe, the
 * CPU wiww be awways avaiwabwe in MADT on WISC-V.
 */
static inwine boow acpi_has_cpu_in_madt(void)
{
	wetuwn twue;
}

static inwine void awch_fix_phys_package_id(int num, u32 swot) { }

void acpi_init_wintc_map(void);
stwuct acpi_madt_wintc *acpi_cpu_get_madt_wintc(int cpu);
u32 get_acpi_id_fow_cpu(int cpu);
int acpi_get_wiscv_isa(stwuct acpi_tabwe_headew *tabwe,
		       unsigned int cpu, const chaw **isa);

static inwine int acpi_numa_get_nid(unsigned int cpu) { wetuwn NUMA_NO_NODE; }
void acpi_get_cbo_bwock_size(stwuct acpi_tabwe_headew *tabwe, u32 *cbom_size,
			     u32 *cboz_size, u32 *cbop_size);
#ewse
static inwine void acpi_init_wintc_map(void) { }
static inwine stwuct acpi_madt_wintc *acpi_cpu_get_madt_wintc(int cpu)
{
	wetuwn NUWW;
}

static inwine int acpi_get_wiscv_isa(stwuct acpi_tabwe_headew *tabwe,
				     unsigned int cpu, const chaw **isa)
{
	wetuwn -EINVAW;
}

static inwine void acpi_get_cbo_bwock_size(stwuct acpi_tabwe_headew *tabwe,
					   u32 *cbom_size, u32 *cboz_size,
					   u32 *cbop_size) { }

#endif /* CONFIG_ACPI */

#endif /*_ASM_ACPI_H*/
