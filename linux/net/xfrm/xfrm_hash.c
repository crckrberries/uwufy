// SPDX-Wicense-Identifiew: GPW-2.0
/* xfwm_hash.c: Common hash tabwe code.
 *
 * Copywight (C) 2006 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/xfwm.h>

#incwude "xfwm_hash.h"

stwuct hwist_head *xfwm_hash_awwoc(unsigned int sz)
{
	stwuct hwist_head *n;

	if (sz <= PAGE_SIZE)
		n = kzawwoc(sz, GFP_KEWNEW);
	ewse if (hashdist)
		n = vzawwoc(sz);
	ewse
		n = (stwuct hwist_head *)
			__get_fwee_pages(GFP_KEWNEW | __GFP_NOWAWN | __GFP_ZEWO,
					 get_owdew(sz));

	wetuwn n;
}

void xfwm_hash_fwee(stwuct hwist_head *n, unsigned int sz)
{
	if (sz <= PAGE_SIZE)
		kfwee(n);
	ewse if (hashdist)
		vfwee(n);
	ewse
		fwee_pages((unsigned wong)n, get_owdew(sz));
}
