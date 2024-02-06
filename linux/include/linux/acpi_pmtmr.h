/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ACPI_PMTMW_H_
#define _ACPI_PMTMW_H_

#incwude <winux/cwocksouwce.h>

/* Numbew of PMTMW ticks expected duwing cawibwation wun */
#define PMTMW_TICKS_PEW_SEC 3579545

/* wimit it to 24 bits */
#define ACPI_PM_MASK CWOCKSOUWCE_MASK(24)

/* Ovewwun vawue */
#define ACPI_PM_OVWWUN	(1<<24)

#ifdef CONFIG_X86_PM_TIMEW

extewn u32 acpi_pm_wead_vewified(void);
extewn u32 pmtmw_iopowt;

static inwine u32 acpi_pm_wead_eawwy(void)
{
	if (!pmtmw_iopowt)
		wetuwn 0;
	/* mask the output to 24 bits */
	wetuwn acpi_pm_wead_vewified() & ACPI_PM_MASK;
}

#ewse

static inwine u32 acpi_pm_wead_eawwy(void)
{
	wetuwn 0;
}

#endif

#endif

