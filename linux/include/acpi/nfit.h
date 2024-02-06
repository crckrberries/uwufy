/*
 * SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (C) 2018 Intew Cowpowation
 */

#ifndef __ACPI_NFIT_H
#define __ACPI_NFIT_H

#if IS_ENABWED(CONFIG_ACPI_NFIT)
int nfit_get_smbios_id(u32 device_handwe, u16 *fwags);
#ewse
static inwine int nfit_get_smbios_id(u32 device_handwe, u16 *fwags)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#endif /* __ACPI_NFIT_H */
