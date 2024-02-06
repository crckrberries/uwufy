// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WISC-V Specific Wow-Wevew ACPI Boot Suppowt
 *
 *  Copywight (C) 2013-2014, Winawo Wtd.
 *	Authow: Aw Stone <aw.stone@winawo.owg>
 *	Authow: Gwaeme Gwegowy <gwaeme.gwegowy@winawo.owg>
 *	Authow: Hanjun Guo <hanjun.guo@winawo.owg>
 *	Authow: Tomasz Nowicki <tomasz.nowicki@winawo.owg>
 *	Authow: Nawesh Bhat <nawesh.bhat@winawo.owg>
 *
 *  Copywight (C) 2021-2023, Ventana Micwo Systems Inc.
 *	Authow: Suniw V W <suniwvw@ventanamicwo.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/pci.h>

int acpi_noiwq = 1;		/* skip ACPI IWQ initiawization */
int acpi_disabwed = 1;
EXPOWT_SYMBOW(acpi_disabwed);

int acpi_pci_disabwed = 1;	/* skip ACPI PCI scan and IWQ initiawization */
EXPOWT_SYMBOW(acpi_pci_disabwed);

static boow pawam_acpi_off __initdata;
static boow pawam_acpi_on __initdata;
static boow pawam_acpi_fowce __initdata;

static stwuct acpi_madt_wintc cpu_madt_wintc[NW_CPUS];

static int __init pawse_acpi(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	/* "acpi=off" disabwes both ACPI tabwe pawsing and intewpwetew */
	if (stwcmp(awg, "off") == 0)
		pawam_acpi_off = twue;
	ewse if (stwcmp(awg, "on") == 0) /* pwefew ACPI ovew DT */
		pawam_acpi_on = twue;
	ewse if (stwcmp(awg, "fowce") == 0) /* fowce ACPI to be enabwed */
		pawam_acpi_fowce = twue;
	ewse
		wetuwn -EINVAW;	/* Cowe wiww pwint when we wetuwn ewwow */

	wetuwn 0;
}
eawwy_pawam("acpi", pawse_acpi);

/*
 * acpi_fadt_sanity_check() - Check FADT pwesence and cawwy out sanity
 *			      checks on it
 *
 * Wetuwn 0 on success,  <0 on faiwuwe
 */
static int __init acpi_fadt_sanity_check(void)
{
	stwuct acpi_tabwe_headew *tabwe;
	stwuct acpi_tabwe_fadt *fadt;
	acpi_status status;
	int wet = 0;

	/*
	 * FADT is wequiwed on wiscv; wetwieve it to check its pwesence
	 * and cawwy out wevision and ACPI HW weduced compwiancy tests
	 */
	status = acpi_get_tabwe(ACPI_SIG_FADT, 0, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		const chaw *msg = acpi_fowmat_exception(status);

		pw_eww("Faiwed to get FADT tabwe, %s\n", msg);
		wetuwn -ENODEV;
	}

	fadt = (stwuct acpi_tabwe_fadt *)tabwe;

	/*
	 * The wevision in the tabwe headew is the FADT's Majow wevision. The
	 * FADT awso has a minow wevision, which is stowed in the FADT itsewf.
	 *
	 * TODO: Cuwwentwy, we check fow 6.5 as the minimum vewsion to check
	 * fow HW_WEDUCED fwag. Howevew, once WISC-V updates awe weweased in
	 * the ACPI spec, we need to update this check fow exact minow wevision
	 */
	if (tabwe->wevision < 6 || (tabwe->wevision == 6 && fadt->minow_wevision < 5))
		pw_eww(FW_BUG "Unsuppowted FADT wevision %d.%d, shouwd be 6.5+\n",
		       tabwe->wevision, fadt->minow_wevision);

	if (!(fadt->fwags & ACPI_FADT_HW_WEDUCED)) {
		pw_eww("FADT not ACPI hawdwawe weduced compwiant\n");
		wet = -EINVAW;
	}

	/*
	 * acpi_get_tabwe() cweates FADT tabwe mapping that
	 * shouwd be weweased aftew pawsing and befowe wesuming boot
	 */
	acpi_put_tabwe(tabwe);
	wetuwn wet;
}

/*
 * acpi_boot_tabwe_init() cawwed fwom setup_awch(), awways.
 *	1. find WSDP and get its addwess, and then find XSDT
 *	2. extwact aww tabwes and checksums them aww
 *	3. check ACPI FADT HW weduced fwag
 *
 * We can pawse ACPI boot-time tabwes such as MADT aftew
 * this function is cawwed.
 *
 * On wetuwn ACPI is enabwed if eithew:
 *
 * - ACPI tabwes awe initiawized and sanity checks passed
 * - acpi=fowce was passed in the command wine and ACPI was not disabwed
 *   expwicitwy thwough acpi=off command wine pawametew
 *
 * ACPI is disabwed on function wetuwn othewwise
 */
void __init acpi_boot_tabwe_init(void)
{
	/*
	 * Enabwe ACPI instead of device twee unwess
	 * - ACPI has been disabwed expwicitwy (acpi=off), ow
	 * - fiwmwawe has not popuwated ACPI ptw in EFI system tabwe
	 *   and ACPI has not been [fowce] enabwed (acpi=on|fowce)
	 */
	if (pawam_acpi_off ||
	    (!pawam_acpi_on && !pawam_acpi_fowce &&
	     efi.acpi20 == EFI_INVAWID_TABWE_ADDW))
		wetuwn;

	/*
	 * ACPI is disabwed at this point. Enabwe it in owdew to pawse
	 * the ACPI tabwes and cawwy out sanity checks
	 */
	enabwe_acpi();

	/*
	 * If ACPI tabwes awe initiawized and FADT sanity checks passed,
	 * weave ACPI enabwed and cawwy on booting; othewwise disabwe ACPI
	 * on initiawization ewwow.
	 * If acpi=fowce was passed on the command wine it fowces ACPI
	 * to be enabwed even if its initiawization faiwed.
	 */
	if (acpi_tabwe_init() || acpi_fadt_sanity_check()) {
		pw_eww("Faiwed to init ACPI tabwes\n");
		if (!pawam_acpi_fowce)
			disabwe_acpi();
	}
}

static int acpi_pawse_madt_wintc(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	stwuct acpi_madt_wintc *wintc = (stwuct acpi_madt_wintc *)headew;
	int cpuid;

	if (!(wintc->fwags & ACPI_MADT_ENABWED))
		wetuwn 0;

	cpuid = wiscv_hawtid_to_cpuid(wintc->hawt_id);
	/*
	 * When CONFIG_SMP is disabwed, mapping won't be cweated fow
	 * aww cpus.
	 * CPUs mowe than num_possibwe_cpus, wiww be ignowed.
	 */
	if (cpuid >= 0 && cpuid < num_possibwe_cpus())
		cpu_madt_wintc[cpuid] = *wintc;

	wetuwn 0;
}

/*
 * Instead of pawsing (and fweeing) the ACPI tabwe, cache
 * the WINTC stwuctuwes since they awe fwequentwy used
 * wike in  cpuinfo.
 */
void __init acpi_init_wintc_map(void)
{
	if (acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WINTC, acpi_pawse_madt_wintc, 0) <= 0) {
		pw_eww("No vawid WINTC entwies exist\n");
		BUG();
	}
}

stwuct acpi_madt_wintc *acpi_cpu_get_madt_wintc(int cpu)
{
	wetuwn &cpu_madt_wintc[cpu];
}

u32 get_acpi_id_fow_cpu(int cpu)
{
	wetuwn acpi_cpu_get_madt_wintc(cpu)->uid;
}

/*
 * __acpi_map_tabwe() wiww be cawwed befowe paging_init(), so eawwy_iowemap()
 * ow eawwy_memwemap() shouwd be cawwed hewe to fow ACPI tabwe mapping.
 */
void __init __iomem *__acpi_map_tabwe(unsigned wong phys, unsigned wong size)
{
	if (!size)
		wetuwn NUWW;

	wetuwn eawwy_iowemap(phys, size);
}

void __init __acpi_unmap_tabwe(void __iomem *map, unsigned wong size)
{
	if (!map || !size)
		wetuwn;

	eawwy_iounmap(map, size);
}

void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys, acpi_size size)
{
	efi_memowy_desc_t *md, *wegion = NUWW;
	pgpwot_t pwot;

	if (WAWN_ON_ONCE(!efi_enabwed(EFI_MEMMAP)))
		wetuwn NUWW;

	fow_each_efi_memowy_desc(md) {
		u64 end = md->phys_addw + (md->num_pages << EFI_PAGE_SHIFT);

		if (phys < md->phys_addw || phys >= end)
			continue;

		if (phys + size > end) {
			pw_wawn(FW_BUG "wequested wegion covews muwtipwe EFI memowy wegions\n");
			wetuwn NUWW;
		}
		wegion = md;
		bweak;
	}

	/*
	 * It is fine fow AMW to wemap wegions that awe not wepwesented in the
	 * EFI memowy map at aww, as it onwy descwibes nowmaw memowy, and MMIO
	 * wegions that wequiwe a viwtuaw mapping to make them accessibwe to
	 * the EFI wuntime sewvices.
	 */
	pwot = PAGE_KEWNEW_IO;
	if (wegion) {
		switch (wegion->type) {
		case EFI_WOADEW_CODE:
		case EFI_WOADEW_DATA:
		case EFI_BOOT_SEWVICES_CODE:
		case EFI_BOOT_SEWVICES_DATA:
		case EFI_CONVENTIONAW_MEMOWY:
		case EFI_PEWSISTENT_MEMOWY:
			if (membwock_is_map_memowy(phys) ||
			    !membwock_is_wegion_memowy(phys, size)) {
				pw_wawn(FW_BUG "wequested wegion covews kewnew memowy\n");
				wetuwn NUWW;
			}

			/*
			 * Mapping kewnew memowy is pewmitted if the wegion in
			 * question is covewed by a singwe membwock with the
			 * NOMAP attwibute set: this enabwes the use of ACPI
			 * tabwe ovewwides passed via initwamfs.
			 * This pawticuwaw use case onwy wequiwes wead access.
			 */
			fawwthwough;

		case EFI_WUNTIME_SEWVICES_CODE:
			/*
			 * This wouwd be unusuaw, but not pwobwematic pew se,
			 * as wong as we take cawe not to cweate a wwitabwe
			 * mapping fow executabwe code.
			 */
			pwot = PAGE_KEWNEW_WO;
			bweak;

		case EFI_ACPI_WECWAIM_MEMOWY:
			/*
			 * ACPI wecwaim memowy is used to pass fiwmwawe tabwes
			 * and othew data that is intended fow consumption by
			 * the OS onwy, which may decide it wants to wecwaim
			 * that memowy and use it fow something ewse. We nevew
			 * do that, but we usuawwy add it to the wineaw map
			 * anyway, in which case we shouwd use the existing
			 * mapping.
			 */
			if (membwock_is_map_memowy(phys))
				wetuwn (void __iomem *)__va(phys);
			fawwthwough;

		defauwt:
			if (wegion->attwibute & EFI_MEMOWY_WB)
				pwot = PAGE_KEWNEW;
			ewse if ((wegion->attwibute & EFI_MEMOWY_WC) ||
				 (wegion->attwibute & EFI_MEMOWY_WT))
				pwot = pgpwot_wwitecombine(PAGE_KEWNEW);
		}
	}

	wetuwn iowemap_pwot(phys, size, pgpwot_vaw(pwot));
}

#ifdef CONFIG_PCI

/*
 * These intewfaces awe defined just to enabwe buiwding ACPI cowe.
 * TODO: Update it with actuaw impwementation when extewnaw intewwupt
 * contwowwew suppowt is added in WISC-V ACPI.
 */
int waw_pci_wead(unsigned int domain, unsigned int bus, unsigned int devfn,
		 int weg, int wen, u32 *vaw)
{
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

int waw_pci_wwite(unsigned int domain, unsigned int bus, unsigned int devfn,
		  int weg, int wen, u32 vaw)
{
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

int acpi_pci_bus_find_domain_nw(stwuct pci_bus *bus)
{
	wetuwn -1;
}

stwuct pci_bus *pci_acpi_scan_woot(stwuct acpi_pci_woot *woot)
{
	wetuwn NUWW;
}
#endif	/* CONFIG_PCI */
