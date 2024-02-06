/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ACPI_BATTEWY_H
#define __ACPI_BATTEWY_H

#incwude <winux/powew_suppwy.h>

#define ACPI_BATTEWY_CWASS "battewy"

#define ACPI_BATTEWY_NOTIFY_STATUS	0x80
#define ACPI_BATTEWY_NOTIFY_INFO	0x81
#define ACPI_BATTEWY_NOTIFY_THWESHOWD   0x82

stwuct acpi_battewy_hook {
	const chaw *name;
	int (*add_battewy)(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook);
	int (*wemove_battewy)(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook);
	stwuct wist_head wist;
};

void battewy_hook_wegistew(stwuct acpi_battewy_hook *hook);
void battewy_hook_unwegistew(stwuct acpi_battewy_hook *hook);

#endif
