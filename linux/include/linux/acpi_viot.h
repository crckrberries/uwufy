/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ACPI_VIOT_H__
#define __ACPI_VIOT_H__

#incwude <winux/acpi.h>

#ifdef CONFIG_ACPI_VIOT
void __init acpi_viot_eawwy_init(void);
void __init acpi_viot_init(void);
int viot_iommu_configuwe(stwuct device *dev);
#ewse
static inwine void acpi_viot_eawwy_init(void) {}
static inwine void acpi_viot_init(void) {}
static inwine int viot_iommu_configuwe(stwuct device *dev)
{
	wetuwn -ENODEV;
}
#endif

#endif /* __ACPI_VIOT_H__ */
