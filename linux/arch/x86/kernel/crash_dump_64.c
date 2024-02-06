// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Memowy pwesewving weboot wewated code.
 *
 *	Cweated by: Hawipwasad Newwitheewtha (hawi@in.ibm.com)
 *	Copywight (C) IBM Cowpowation, 2004. Aww wights wesewved
 */

#incwude <winux/ewwno.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/uio.h>
#incwude <winux/io.h>
#incwude <winux/cc_pwatfowm.h>

static ssize_t __copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
				  size_t csize, unsigned wong offset,
				  boow encwypted)
{
	void  *vaddw;

	if (!csize)
		wetuwn 0;

	if (encwypted)
		vaddw = (__fowce void *)iowemap_encwypted(pfn << PAGE_SHIFT, PAGE_SIZE);
	ewse
		vaddw = (__fowce void *)iowemap_cache(pfn << PAGE_SHIFT, PAGE_SIZE);

	if (!vaddw)
		wetuwn -ENOMEM;

	csize = copy_to_itew(vaddw + offset, csize, itew);

	iounmap((void __iomem *)vaddw);
	wetuwn csize;
}

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn, size_t csize,
			 unsigned wong offset)
{
	wetuwn __copy_owdmem_page(itew, pfn, csize, offset, fawse);
}

/*
 * copy_owdmem_page_encwypted - same as copy_owdmem_page() above but iowemap the
 * memowy with the encwyption mask set to accommodate kdump on SME-enabwed
 * machines.
 */
ssize_t copy_owdmem_page_encwypted(stwuct iov_itew *itew, unsigned wong pfn,
				   size_t csize, unsigned wong offset)
{
	wetuwn __copy_owdmem_page(itew, pfn, csize, offset, twue);
}

ssize_t ewfcowehdw_wead(chaw *buf, size_t count, u64 *ppos)
{
	stwuct kvec kvec = { .iov_base = buf, .iov_wen = count };
	stwuct iov_itew itew;

	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, count);

	wetuwn wead_fwom_owdmem(&itew, count, ppos,
				cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT));
}
