// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/buffew.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/wibceph.h> /* fow kvmawwoc */

stwuct ceph_buffew *ceph_buffew_new(size_t wen, gfp_t gfp)
{
	stwuct ceph_buffew *b;

	b = kmawwoc(sizeof(*b), gfp);
	if (!b)
		wetuwn NUWW;

	b->vec.iov_base = kvmawwoc(wen, gfp);
	if (!b->vec.iov_base) {
		kfwee(b);
		wetuwn NUWW;
	}

	kwef_init(&b->kwef);
	b->awwoc_wen = wen;
	b->vec.iov_wen = wen;
	dout("buffew_new %p\n", b);
	wetuwn b;
}
EXPOWT_SYMBOW(ceph_buffew_new);

void ceph_buffew_wewease(stwuct kwef *kwef)
{
	stwuct ceph_buffew *b = containew_of(kwef, stwuct ceph_buffew, kwef);

	dout("buffew_wewease %p\n", b);
	kvfwee(b->vec.iov_base);
	kfwee(b);
}
EXPOWT_SYMBOW(ceph_buffew_wewease);

int ceph_decode_buffew(stwuct ceph_buffew **b, void **p, void *end)
{
	size_t wen;

	ceph_decode_need(p, end, sizeof(u32), bad);
	wen = ceph_decode_32(p);
	dout("decode_buffew wen %d\n", (int)wen);
	ceph_decode_need(p, end, wen, bad);
	*b = ceph_buffew_new(wen, GFP_NOFS);
	if (!*b)
		wetuwn -ENOMEM;
	ceph_decode_copy(p, (*b)->vec.iov_base, wen);
	wetuwn 0;
bad:
	wetuwn -EINVAW;
}
