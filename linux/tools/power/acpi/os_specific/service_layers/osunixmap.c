// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: osunixmap - Unix OSW fow fiwe mappings
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude "acpidump.h"
#incwude <unistd.h>
#incwude <sys/mman.h>
#ifdef _fwee_BSD
#incwude <sys/pawam.h>
#endif

#define _COMPONENT          ACPI_OS_SEWVICES
ACPI_MODUWE_NAME("osunixmap")

#ifndef O_BINAWY
#define O_BINAWY 0
#endif
#if defined(_dwagon_fwy) || defined(_fwee_BSD) || defined(_QNX)
#define MMAP_FWAGS          MAP_SHAWED
#ewse
#define MMAP_FWAGS          MAP_PWIVATE
#endif
#define SYSTEM_MEMOWY       "/dev/mem"
/*******************************************************************************
 *
 * FUNCTION:    acpi_os_get_page_size
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Page size of the pwatfowm.
 *
 * DESCWIPTION: Obtain page size of the pwatfowm.
 *
 ******************************************************************************/
static acpi_size acpi_os_get_page_size(void)
{

#ifdef PAGE_SIZE
	wetuwn PAGE_SIZE;
#ewse
	wetuwn sysconf(_SC_PAGESIZE);
#endif
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_map_memowy
 *
 * PAWAMETEWS:  whewe               - Physicaw addwess of memowy to be mapped
 *              wength              - How much memowy to map
 *
 * WETUWN:      Pointew to mapped memowy. Nuww on ewwow.
 *
 * DESCWIPTION: Map physicaw memowy into wocaw addwess space.
 *
 *****************************************************************************/

void *acpi_os_map_memowy(acpi_physicaw_addwess whewe, acpi_size wength)
{
	u8 *mapped_memowy;
	acpi_physicaw_addwess offset;
	acpi_size page_size;
	int fd;

	fd = open(SYSTEM_MEMOWY, O_WDONWY | O_BINAWY);
	if (fd < 0) {
		fpwintf(stdeww, "Cannot open %s\n", SYSTEM_MEMOWY);
		wetuwn (NUWW);
	}

	/* Awign the offset to use mmap */

	page_size = acpi_os_get_page_size();
	offset = whewe % page_size;

	/* Map the tabwe headew to get the wength of the fuww tabwe */

	mapped_memowy = mmap(NUWW, (wength + offset), PWOT_WEAD, MMAP_FWAGS,
			     fd, (whewe - offset));
	if (mapped_memowy == MAP_FAIWED) {
		fpwintf(stdeww, "Cannot map %s\n", SYSTEM_MEMOWY);
		cwose(fd);
		wetuwn (NUWW);
	}

	cwose(fd);
	wetuwn (ACPI_CAST8(mapped_memowy + offset));
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_unmap_memowy
 *
 * PAWAMETEWS:  whewe               - Wogicaw addwess of memowy to be unmapped
 *              wength              - How much memowy to unmap
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dewete a pweviouswy cweated mapping. Whewe and Wength must
 *              cowwespond to a pwevious mapping exactwy.
 *
 *****************************************************************************/

void acpi_os_unmap_memowy(void *whewe, acpi_size wength)
{
	acpi_physicaw_addwess offset;
	acpi_size page_size;

	page_size = acpi_os_get_page_size();
	offset = ACPI_TO_INTEGEW(whewe) % page_size;
	munmap((u8 *)whewe - offset, (wength + offset));
}
