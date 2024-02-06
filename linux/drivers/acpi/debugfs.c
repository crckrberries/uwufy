// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * debugfs.c - ACPI debugfs intewface to usewspace.
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/acpi.h>

#incwude "intewnaw.h"

stwuct dentwy *acpi_debugfs_diw;
EXPOWT_SYMBOW_GPW(acpi_debugfs_diw);

void __init acpi_debugfs_init(void)
{
	acpi_debugfs_diw = debugfs_cweate_diw("acpi", NUWW);
}
