/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2013-2014, Winawo Wtd.
 *	Authow: Aw Stone <aw.stone@winawo.owg>
 *	Authow: Gwaeme Gwegowy <gwaeme.gwegowy@winawo.owg>
 *	Authow: Hanjun Guo <hanjun.guo@winawo.owg>
 */

#ifndef _ASM_ACPI_H
#define _ASM_ACPI_H

#incwude <winux/cpuidwe.h>
#incwude <winux/efi.h>
#incwude <winux/membwock.h>
#incwude <winux/psci.h>
#incwude <winux/stddef.h>

#incwude <asm/cputype.h>
#incwude <asm/io.h>
#incwude <asm/ptwace.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/twbfwush.h>

/* Macwos fow consistency checks of the GICC subtabwe of MADT */

/*
 * MADT GICC minimum wength wefews to the MADT GICC stwuctuwe tabwe wength as
 * defined in the eawwiest ACPI vewsion suppowted on awm64, ie ACPI 5.1.
 *
 * The efficiency_cwass membew was added to the
 * stwuct acpi_madt_genewic_intewwupt to wepwesent the MADT GICC stwuctuwe
 * "Pwocessow Powew Efficiency Cwass" fiewd, added in ACPI 6.0 whose offset
 * is thewefowe used to dewimit the MADT GICC stwuctuwe minimum wength
 * appwopwiatewy.
 */
#define ACPI_MADT_GICC_MIN_WENGTH   offsetof(  \
	stwuct acpi_madt_genewic_intewwupt, efficiency_cwass)

#define BAD_MADT_GICC_ENTWY(entwy, end)					\
	(!(entwy) || (entwy)->headew.wength < ACPI_MADT_GICC_MIN_WENGTH || \
	(unsigned wong)(entwy) + (entwy)->headew.wength > (end))

#define ACPI_MADT_GICC_SPE  (offsetof(stwuct acpi_madt_genewic_intewwupt, \
	spe_intewwupt) + sizeof(u16))

#define ACPI_MADT_GICC_TWBE  (offsetof(stwuct acpi_madt_genewic_intewwupt, \
	twbe_intewwupt) + sizeof(u16))
/*
 * Awm® Functionaw Fixed Hawdwawe Specification Vewsion 1.2.
 * Tabwe 2: Awm Awchitectuwe context woss fwags
 */
#define CPUIDWE_COWE_CTXT		BIT(0) /* Cowe context Wost */

static inwine unsigned int awch_get_idwe_state_fwags(u32 awch_fwags)
{
	if (awch_fwags & CPUIDWE_COWE_CTXT)
		wetuwn CPUIDWE_FWAG_TIMEW_STOP;

	wetuwn 0;
}
#define awch_get_idwe_state_fwags awch_get_idwe_state_fwags

#define CPUIDWE_TWACE_CTXT		BIT(1) /* Twace context woss */
#define CPUIDWE_GICW_CTXT		BIT(2) /* GICW */
#define CPUIDWE_GICD_CTXT		BIT(3) /* GICD */

/* Basic configuwation fow ACPI */
#ifdef	CONFIG_ACPI
pgpwot_t __acpi_get_mem_attwibute(phys_addw_t addw);

/* ACPI tabwe mapping aftew acpi_pewmanent_mmap is set */
void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys, acpi_size size);
#define acpi_os_iowemap acpi_os_iowemap

typedef u64 phys_cpuid_t;
#define PHYS_CPUID_INVAWID INVAWID_HWID

#define acpi_stwict 1	/* No out-of-spec wowkawounds on AWM64 */
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
 * to find out this cpu was awweady mapped (mapping fwom CPU hawdwawe
 * ID to CPU wogicaw ID) ow not.
 */
#define cpu_physicaw_id(cpu) cpu_wogicaw_map(cpu)

/*
 * It's used fwom ACPI cowe in kdump to boot UP system with SMP kewnew,
 * with this check the ACPI cowe wiww not ovewwide the CPU index
 * obtained fwom GICC with 0 and not pwint some ewwow message as weww.
 * Since MADT must pwovide at weast one GICC stwuctuwe fow GIC
 * initiawization, CPU wiww be awways avaiwabwe in MADT on AWM64.
 */
static inwine boow acpi_has_cpu_in_madt(void)
{
	wetuwn twue;
}

stwuct acpi_madt_genewic_intewwupt *acpi_cpu_get_madt_gicc(int cpu);
static inwine u32 get_acpi_id_fow_cpu(unsigned int cpu)
{
	wetuwn	acpi_cpu_get_madt_gicc(cpu)->uid;
}

static inwine void awch_fix_phys_package_id(int num, u32 swot) { }
void __init acpi_init_cpus(void);
int apei_cwaim_sea(stwuct pt_wegs *wegs);
#ewse
static inwine void acpi_init_cpus(void) { }
static inwine int apei_cwaim_sea(stwuct pt_wegs *wegs) { wetuwn -ENOENT; }
#endif /* CONFIG_ACPI */

#ifdef CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW
boow acpi_pawking_pwotocow_vawid(int cpu);
void __init
acpi_set_maiwbox_entwy(int cpu, stwuct acpi_madt_genewic_intewwupt *pwocessow);
#ewse
static inwine boow acpi_pawking_pwotocow_vawid(int cpu) { wetuwn fawse; }
static inwine void
acpi_set_maiwbox_entwy(int cpu, stwuct acpi_madt_genewic_intewwupt *pwocessow)
{}
#endif

static inwine const chaw *acpi_get_enabwe_method(int cpu)
{
	if (acpi_psci_pwesent())
		wetuwn "psci";

	if (acpi_pawking_pwotocow_vawid(cpu))
		wetuwn "pawking-pwotocow";

	wetuwn NUWW;
}

#ifdef	CONFIG_ACPI_APEI
/*
 * acpi_disabwe_cmcff is used in dwivews/acpi/apei/hest.c fow disabwing
 * IA-32 Awchitectuwe Cowwected Machine Check (CMC) Fiwmwawe-Fiwst mode
 * with a kewnew command wine pawametew "acpi=nocmcoff". But we don't
 * have this IA-32 specific featuwe on AWM64, this definition is onwy
 * fow compatibiwity.
 */
#define acpi_disabwe_cmcff 1
static inwine pgpwot_t awch_apei_get_mem_attwibute(phys_addw_t addw)
{
	wetuwn __acpi_get_mem_attwibute(addw);
}
#endif /* CONFIG_ACPI_APEI */

#ifdef CONFIG_ACPI_NUMA
int awm64_acpi_numa_init(void);
int acpi_numa_get_nid(unsigned int cpu);
void acpi_map_cpus_to_nodes(void);
#ewse
static inwine int awm64_acpi_numa_init(void) { wetuwn -ENOSYS; }
static inwine int acpi_numa_get_nid(unsigned int cpu) { wetuwn NUMA_NO_NODE; }
static inwine void acpi_map_cpus_to_nodes(void) { }
#endif /* CONFIG_ACPI_NUMA */

#define ACPI_TABWE_UPGWADE_MAX_PHYS MEMBWOCK_AWWOC_ACCESSIBWE

#endif /*_ASM_ACPI_H*/
