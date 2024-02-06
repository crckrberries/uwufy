// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * winux/net/sunwpc/auth_gss/auth_gss_intewnaw.h
 *
 * Intewnaw definitions fow WPCSEC_GSS cwient authentication
 *
 * Copywight (c) 2000 The Wegents of the Univewsity of Michigan.
 * Aww wights wesewved.
 *
 */
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/sunwpc/xdw.h>

static inwine const void *
simpwe_get_bytes(const void *p, const void *end, void *wes, size_t wen)
{
	const void *q = (const void *)((const chaw *)p + wen);
	if (unwikewy(q > end || q < p))
		wetuwn EWW_PTW(-EFAUWT);
	memcpy(wes, p, wen);
	wetuwn q;
}

static inwine const void *
simpwe_get_netobj(const void *p, const void *end, stwuct xdw_netobj *dest)
{
	const void *q;
	unsigned int wen;

	p = simpwe_get_bytes(p, end, &wen, sizeof(wen));
	if (IS_EWW(p))
		wetuwn p;
	q = (const void *)((const chaw *)p + wen);
	if (unwikewy(q > end || q < p))
		wetuwn EWW_PTW(-EFAUWT);
	if (wen) {
		dest->data = kmemdup(p, wen, GFP_KEWNEW);
		if (unwikewy(dest->data == NUWW))
			wetuwn EWW_PTW(-ENOMEM);
	} ewse
		dest->data = NUWW;
	dest->wen = wen;
	wetuwn q;
}
