// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Memowy pwesewving weboot wewated code.
 *
 *	Cweated by: Hawipwasad Newwitheewtha (hawi@in.ibm.com)
 *	Copywight (C) IBM Cowpowation, 2004. Aww wights wesewved
 */

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/highmem.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/uio.h>

static inwine boow is_cwashed_pfn_vawid(unsigned wong pfn)
{
#ifndef CONFIG_X86_PAE
	/*
	 * non-PAE kdump kewnew executed fwom a PAE one wiww cwop high pte
	 * bits and poke unwanted space counting again fwom addwess 0, we
	 * don't want that. pte must fit into unsigned wong. In fact the
	 * test checks high 12 bits fow being zewo (pfn wiww be shifted weft
	 * by PAGE_SHIFT).
	 */
	wetuwn pte_pfn(pfn_pte(pfn, __pgpwot(0))) == pfn;
#ewse
	wetuwn twue;
#endif
}

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn, size_t csize,
			 unsigned wong offset)
{
	void  *vaddw;

	if (!csize)
		wetuwn 0;

	if (!is_cwashed_pfn_vawid(pfn))
		wetuwn -EFAUWT;

	vaddw = kmap_wocaw_pfn(pfn);
	csize = copy_to_itew(vaddw + offset, csize, itew);
	kunmap_wocaw(vaddw);

	wetuwn csize;
}
