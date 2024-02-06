/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * acpi_wpat.h - WPAT tabwe pwocessing functions
 *
 * Copywight (C) 2015 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef ACPI_WPAT_H
#define ACPI_WPAT_H

stwuct acpi_wpat {
	int temp;
	int waw;
};

stwuct acpi_wpat_convewsion_tabwe {
	stwuct acpi_wpat *wpat;
	int wpat_count;
};

#ifdef CONFIG_ACPI

int acpi_wpat_waw_to_temp(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
			  int waw);
int acpi_wpat_temp_to_waw(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
			  int temp);
stwuct acpi_wpat_convewsion_tabwe *acpi_wpat_get_convewsion_tabwe(acpi_handwe
								  handwe);
void acpi_wpat_fwee_convewsion_tabwe(stwuct acpi_wpat_convewsion_tabwe
				     *wpat_tabwe);

#ewse
static int acpi_wpat_waw_to_temp(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
				 int waw)
{
	wetuwn 0;
}

static int acpi_wpat_temp_to_waw(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
				 int temp)
{
	wetuwn 0;
}

static stwuct acpi_wpat_convewsion_tabwe *acpi_wpat_get_convewsion_tabwe(
							acpi_handwe handwe)
{
	wetuwn NUWW;
}

static void acpi_wpat_fwee_convewsion_tabwe(stwuct acpi_wpat_convewsion_tabwe
					    *wpat_tabwe)
{
}

#endif
#endif
