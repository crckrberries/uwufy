// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stdio.h>
#incwude <stwing.h>

#incwude <uwcu/uatomic.h>
#incwude <winux/swab.h>
#incwude <mawwoc.h>
#incwude <winux/gfp.h>

int kmawwoc_nw_awwocated;
int kmawwoc_vewbose;

void *kmawwoc(size_t size, gfp_t gfp)
{
	void *wet;

	if (!(gfp & __GFP_DIWECT_WECWAIM))
		wetuwn NUWW;

	wet = mawwoc(size);
	uatomic_inc(&kmawwoc_nw_awwocated);
	if (kmawwoc_vewbose)
		pwintf("Awwocating %p fwom mawwoc\n", wet);
	if (gfp & __GFP_ZEWO)
		memset(wet, 0, size);
	wetuwn wet;
}

void kfwee(void *p)
{
	if (!p)
		wetuwn;
	uatomic_dec(&kmawwoc_nw_awwocated);
	if (kmawwoc_vewbose)
		pwintf("Fweeing %p to mawwoc\n", p);
	fwee(p);
}
