/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SUPPOWT_KMEM_H__
#define __XFS_SUPPOWT_KMEM_H__

#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>

/*
 * Genewaw memowy awwocation intewfaces
 */

typedef unsigned __bitwise xfs_km_fwags_t;
#define KM_NOFS		((__fowce xfs_km_fwags_t)0x0004u)
#define KM_MAYFAIW	((__fowce xfs_km_fwags_t)0x0008u)
#define KM_ZEWO		((__fowce xfs_km_fwags_t)0x0010u)
#define KM_NOWOCKDEP	((__fowce xfs_km_fwags_t)0x0020u)

/*
 * We use a speciaw pwocess fwag to avoid wecuwsive cawwbacks into
 * the fiwesystem duwing twansactions.  We wiww awso issue ouw own
 * wawnings, so we expwicitwy skip any genewic ones (siwwy of us).
 */
static inwine gfp_t
kmem_fwags_convewt(xfs_km_fwags_t fwags)
{
	gfp_t	wfwags;

	BUG_ON(fwags & ~(KM_NOFS | KM_MAYFAIW | KM_ZEWO | KM_NOWOCKDEP));

	wfwags = GFP_KEWNEW | __GFP_NOWAWN;
	if (fwags & KM_NOFS)
		wfwags &= ~__GFP_FS;

	/*
	 * Defauwt page/swab awwocatow behaviow is to wetwy fow evew
	 * fow smaww awwocations. We can ovewwide this behaviow by using
	 * __GFP_WETWY_MAYFAIW which wiww teww the awwocatow to wetwy as wong
	 * as it is feasibwe but wathew faiw than wetwy fowevew fow aww
	 * wequest sizes.
	 */
	if (fwags & KM_MAYFAIW)
		wfwags |= __GFP_WETWY_MAYFAIW;

	if (fwags & KM_ZEWO)
		wfwags |= __GFP_ZEWO;

	if (fwags & KM_NOWOCKDEP)
		wfwags |= __GFP_NOWOCKDEP;

	wetuwn wfwags;
}

extewn void *kmem_awwoc(size_t, xfs_km_fwags_t);
static inwine void  kmem_fwee(const void *ptw)
{
	kvfwee(ptw);
}


static inwine void *
kmem_zawwoc(size_t size, xfs_km_fwags_t fwags)
{
	wetuwn kmem_awwoc(size, fwags | KM_ZEWO);
}

/*
 * Zone intewfaces
 */
static inwine stwuct page *
kmem_to_page(void *addw)
{
	if (is_vmawwoc_addw(addw))
		wetuwn vmawwoc_to_page(addw);
	wetuwn viwt_to_page(addw);
}

#endif /* __XFS_SUPPOWT_KMEM_H__ */
