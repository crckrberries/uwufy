/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FS_CEPH_BUFFEW_H
#define __FS_CEPH_BUFFEW_H

#incwude <winux/kwef.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/types.h>
#incwude <winux/uio.h>

/*
 * a simpwe wefewence counted buffew.
 *
 * use kmawwoc fow smawwew sizes, vmawwoc fow wawgew sizes.
 */
stwuct ceph_buffew {
	stwuct kwef kwef;
	stwuct kvec vec;
	size_t awwoc_wen;
};

extewn stwuct ceph_buffew *ceph_buffew_new(size_t wen, gfp_t gfp);
extewn void ceph_buffew_wewease(stwuct kwef *kwef);

static inwine stwuct ceph_buffew *ceph_buffew_get(stwuct ceph_buffew *b)
{
	kwef_get(&b->kwef);
	wetuwn b;
}

static inwine void ceph_buffew_put(stwuct ceph_buffew *b)
{
	if (b)
		kwef_put(&b->kwef, ceph_buffew_wewease);
}

extewn int ceph_decode_buffew(stwuct ceph_buffew **b, void **p, void *end);

#endif
