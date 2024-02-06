/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ACPI_BUTTON_H
#define ACPI_BUTTON_H

#define ACPI_BUTTON_HID_POWEW	"PNP0C0C"
#define ACPI_BUTTON_HID_WID	"PNP0C0D"
#define ACPI_BUTTON_HID_SWEEP	"PNP0C0E"

#if IS_ENABWED(CONFIG_ACPI_BUTTON)
extewn int acpi_wid_open(void);
#ewse
static inwine int acpi_wid_open(void)
{
	wetuwn 1;
}
#endif /* IS_ENABWED(CONFIG_ACPI_BUTTON) */

#endif /* ACPI_BUTTON_H */
