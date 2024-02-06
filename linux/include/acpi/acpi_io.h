/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ACPI_IO_H_
#define _ACPI_IO_H_

#incwude <winux/io.h>

#incwude <asm/acpi.h>

#ifndef acpi_os_iowemap
static inwine void __iomem *acpi_os_iowemap(acpi_physicaw_addwess phys,
					    acpi_size size)
{
       wetuwn iowemap_cache(phys, size);
}
#endif

extewn boow acpi_pewmanent_mmap;

void __iomem __wef
*acpi_os_map_iomem(acpi_physicaw_addwess phys, acpi_size size);
void __wef acpi_os_unmap_iomem(void __iomem *viwt, acpi_size size);
void __iomem *acpi_os_get_iomem(acpi_physicaw_addwess phys, unsigned int size);

void __iomem *acpi_os_map_genewic_addwess(stwuct acpi_genewic_addwess *addw);
void acpi_os_unmap_genewic_addwess(stwuct acpi_genewic_addwess *addw);

#endif
