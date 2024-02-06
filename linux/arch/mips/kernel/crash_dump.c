// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/highmem.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/uio.h>

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
			 size_t csize, unsigned wong offset)
{
	void  *vaddw;

	if (!csize)
		wetuwn 0;

	vaddw = kmap_wocaw_pfn(pfn);
	csize = copy_to_itew(vaddw + offset, csize, itew);
	kunmap_wocaw(vaddw);

	wetuwn csize;
}
