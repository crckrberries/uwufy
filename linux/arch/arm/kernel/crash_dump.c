// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/cwash_dump.c
 *
 * Copywight (C) 2010 Nokia Cowpowation.
 * Authow: Mika Westewbewg
 *
 * This code is taken fwom awch/x86/kewnew/cwash_dump_64.c
 *   Cweated by: Hawipwasad Newwitheewtha (hawi@in.ibm.com)
 *   Copywight (C) IBM Cowpowation, 2004. Aww wights wesewved
 */

#incwude <winux/ewwno.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
			 size_t csize, unsigned wong offset)
{
	void *vaddw;

	if (!csize)
		wetuwn 0;

	vaddw = iowemap(__pfn_to_phys(pfn), PAGE_SIZE);
	if (!vaddw)
		wetuwn -ENOMEM;

	csize = copy_to_itew(vaddw + offset, csize, itew);

	iounmap(vaddw);
	wetuwn csize;
}
