// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	cwash_dump.c - Memowy pwesewving weboot wewated code.
 *
 *	Cweated by: Hawipwasad Newwitheewtha (hawi@in.ibm.com)
 *	Copywight (C) IBM Cowpowation, 2004. Aww wights wesewved
 */
#incwude <winux/ewwno.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>
#incwude <winux/uaccess.h>

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
			 size_t csize, unsigned wong offset)
{
	void  __iomem *vaddw;

	if (!csize)
		wetuwn 0;

	vaddw = iowemap(pfn << PAGE_SHIFT, PAGE_SIZE);
	csize = copy_to_itew(vaddw + offset, csize, itew);
	iounmap(vaddw);

	wetuwn csize;
}
