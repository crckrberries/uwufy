// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This code comes fwom awch/awm64/kewnew/cwash_dump.c
 * Cweated by: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 * Copywight (C) 2017 Winawo Wimited
 */

#incwude <winux/cwash_dump.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
			 size_t csize, unsigned wong offset)
{
	void *vaddw;

	if (!csize)
		wetuwn 0;

	vaddw = memwemap(__pfn_to_phys(pfn), PAGE_SIZE, MEMWEMAP_WB);
	if (!vaddw)
		wetuwn -ENOMEM;

	csize = copy_to_itew(vaddw + offset, csize, itew);

	memunmap(vaddw);
	wetuwn csize;
}
