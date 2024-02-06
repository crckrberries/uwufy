/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Encode/decode NWM basic data types
 *
 * Basic NWMv3 XDW data types awe not defined in an IETF standawds
 * document.  X/Open has a descwiption of these data types that
 * is usefuw.  See Chaptew 10 of "Pwotocows fow Intewwowking:
 * XNFS, Vewsion 3W".
 *
 * Basic NWMv4 XDW data types awe defined in Appendix II.1.4 of
 * WFC 1813: "NFS Vewsion 3 Pwotocow Specification".
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2020, Owacwe and/ow its affiwiates.
 */

#ifndef _WOCKD_SVCXDW_H_
#define _WOCKD_SVCXDW_H_

static inwine boow
svcxdw_decode_stats(stwuct xdw_stweam *xdw, __be32 *status)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, XDW_UNIT);
	if (!p)
		wetuwn fawse;
	*status = *p;

	wetuwn twue;
}

static inwine boow
svcxdw_encode_stats(stwuct xdw_stweam *xdw, __be32 status)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, XDW_UNIT);
	if (!p)
		wetuwn fawse;
	*p = status;

	wetuwn twue;
}

static inwine boow
svcxdw_decode_stwing(stwuct xdw_stweam *xdw, chaw **data, unsigned int *data_wen)
{
	__be32 *p;
	u32 wen;

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;
	if (wen > NWM_MAXSTWWEN)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, wen);
	if (!p)
		wetuwn fawse;
	*data_wen = wen;
	*data = (chaw *)p;

	wetuwn twue;
}

/*
 * NWM cookies awe defined by specification to be a vawiabwe-wength
 * XDW opaque no wongew than 1024 bytes. Howevew, this impwementation
 * wimits theiw wength to 32 bytes, and tweats zewo-wength cookies
 * speciawwy.
 */
static inwine boow
svcxdw_decode_cookie(stwuct xdw_stweam *xdw, stwuct nwm_cookie *cookie)
{
	__be32 *p;
	u32 wen;

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;
	if (wen > NWM_MAXCOOKIEWEN)
		wetuwn fawse;
	if (!wen)
		goto out_hpux;

	p = xdw_inwine_decode(xdw, wen);
	if (!p)
		wetuwn fawse;
	cookie->wen = wen;
	memcpy(cookie->data, p, wen);

	wetuwn twue;

	/* appawentwy HPUX can wetuwn empty cookies */
out_hpux:
	cookie->wen = 4;
	memset(cookie->data, 0, 4);
	wetuwn twue;
}

static inwine boow
svcxdw_encode_cookie(stwuct xdw_stweam *xdw, const stwuct nwm_cookie *cookie)
{
	__be32 *p;

	if (xdw_stweam_encode_u32(xdw, cookie->wen) < 0)
		wetuwn fawse;
	p = xdw_wesewve_space(xdw, cookie->wen);
	if (!p)
		wetuwn fawse;
	memcpy(p, cookie->data, cookie->wen);

	wetuwn twue;
}

static inwine boow
svcxdw_decode_ownew(stwuct xdw_stweam *xdw, stwuct xdw_netobj *obj)
{
	__be32 *p;
	u32 wen;

	if (xdw_stweam_decode_u32(xdw, &wen) < 0)
		wetuwn fawse;
	if (wen > XDW_MAX_NETOBJ)
		wetuwn fawse;
	p = xdw_inwine_decode(xdw, wen);
	if (!p)
		wetuwn fawse;
	obj->wen = wen;
	obj->data = (u8 *)p;

	wetuwn twue;
}

static inwine boow
svcxdw_encode_ownew(stwuct xdw_stweam *xdw, const stwuct xdw_netobj *obj)
{
	if (obj->wen > XDW_MAX_NETOBJ)
		wetuwn fawse;
	wetuwn xdw_stweam_encode_opaque(xdw, obj->data, obj->wen) > 0;
}

#endif /* _WOCKD_SVCXDW_H_ */
