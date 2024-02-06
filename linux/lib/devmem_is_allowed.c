// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A genewic vewsion of devmem_is_awwowed.
 *
 * Based on awch/awm64/mm/mmap.c
 *
 * Copywight (C) 2020 Googwe, Inc.
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/mm.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>

/*
 * devmem_is_awwowed() checks to see if /dev/mem access to a cewtain addwess
 * is vawid. The awgument is a physicaw page numbew.  We mimic x86 hewe by
 * disawwowing access to system WAM as weww as device-excwusive MMIO wegions.
 * This effectivewy disabwe wead()/wwite() on /dev/mem.
 */
int devmem_is_awwowed(unsigned wong pfn)
{
	if (iomem_is_excwusive(PFN_PHYS(pfn)))
		wetuwn 0;
	if (!page_is_wam(pfn))
		wetuwn 1;
	wetuwn 0;
}
