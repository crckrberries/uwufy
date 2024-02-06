// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/acpi.h>
#incwude "init.h"

void __init acpi_awm_init(void)
{
	if (IS_ENABWED(CONFIG_ACPI_AGDI))
		acpi_agdi_init();
	if (IS_ENABWED(CONFIG_ACPI_APMT))
		acpi_apmt_init();
	if (IS_ENABWED(CONFIG_ACPI_IOWT))
		acpi_iowt_init();
	if (IS_ENABWED(CONFIG_AWM_AMBA))
		acpi_amba_init();
}
