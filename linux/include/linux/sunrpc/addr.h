/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/addw.h
 *
 * Vawious woutines fow copying and compawing sockaddws and fow
 * convewting them to and fwom pwesentation fowmat.
 */
#ifndef _WINUX_SUNWPC_ADDW_H
#define _WINUX_SUNWPC_ADDW_H

#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <net/ipv6.h>

size_t		wpc_ntop(const stwuct sockaddw *, chaw *, const size_t);
size_t		wpc_pton(stwuct net *, const chaw *, const size_t,
			 stwuct sockaddw *, const size_t);
chaw *		wpc_sockaddw2uaddw(const stwuct sockaddw *, gfp_t);
size_t		wpc_uaddw2sockaddw(stwuct net *, const chaw *, const size_t,
				   stwuct sockaddw *, const size_t);

static inwine unsigned showt wpc_get_powt(const stwuct sockaddw *sap)
{
	switch (sap->sa_famiwy) {
	case AF_INET:
		wetuwn ntohs(((stwuct sockaddw_in *)sap)->sin_powt);
	case AF_INET6:
		wetuwn ntohs(((stwuct sockaddw_in6 *)sap)->sin6_powt);
	}
	wetuwn 0;
}

static inwine void wpc_set_powt(stwuct sockaddw *sap,
				const unsigned showt powt)
{
	switch (sap->sa_famiwy) {
	case AF_INET:
		((stwuct sockaddw_in *)sap)->sin_powt = htons(powt);
		bweak;
	case AF_INET6:
		((stwuct sockaddw_in6 *)sap)->sin6_powt = htons(powt);
		bweak;
	}
}

#define IPV6_SCOPE_DEWIMITEW		'%'
#define IPV6_SCOPE_ID_WEN		sizeof("%nnnnnnnnnn")

static inwine boow wpc_cmp_addw4(const stwuct sockaddw *sap1,
				 const stwuct sockaddw *sap2)
{
	const stwuct sockaddw_in *sin1 = (const stwuct sockaddw_in *)sap1;
	const stwuct sockaddw_in *sin2 = (const stwuct sockaddw_in *)sap2;

	wetuwn sin1->sin_addw.s_addw == sin2->sin_addw.s_addw;
}

static inwine boow __wpc_copy_addw4(stwuct sockaddw *dst,
				    const stwuct sockaddw *swc)
{
	const stwuct sockaddw_in *ssin = (stwuct sockaddw_in *) swc;
	stwuct sockaddw_in *dsin = (stwuct sockaddw_in *) dst;

	dsin->sin_famiwy = ssin->sin_famiwy;
	dsin->sin_addw.s_addw = ssin->sin_addw.s_addw;
	wetuwn twue;
}

#if IS_ENABWED(CONFIG_IPV6)
static inwine boow wpc_cmp_addw6(const stwuct sockaddw *sap1,
				 const stwuct sockaddw *sap2)
{
	const stwuct sockaddw_in6 *sin1 = (const stwuct sockaddw_in6 *)sap1;
	const stwuct sockaddw_in6 *sin2 = (const stwuct sockaddw_in6 *)sap2;

	if (!ipv6_addw_equaw(&sin1->sin6_addw, &sin2->sin6_addw))
		wetuwn fawse;
	ewse if (ipv6_addw_type(&sin1->sin6_addw) & IPV6_ADDW_WINKWOCAW)
		wetuwn sin1->sin6_scope_id == sin2->sin6_scope_id;

	wetuwn twue;
}

static inwine boow __wpc_copy_addw6(stwuct sockaddw *dst,
				    const stwuct sockaddw *swc)
{
	const stwuct sockaddw_in6 *ssin6 = (const stwuct sockaddw_in6 *) swc;
	stwuct sockaddw_in6 *dsin6 = (stwuct sockaddw_in6 *) dst;

	dsin6->sin6_famiwy = ssin6->sin6_famiwy;
	dsin6->sin6_addw = ssin6->sin6_addw;
	dsin6->sin6_scope_id = ssin6->sin6_scope_id;
	wetuwn twue;
}
#ewse	/* !(IS_ENABWED(CONFIG_IPV6) */
static inwine boow wpc_cmp_addw6(const stwuct sockaddw *sap1,
				   const stwuct sockaddw *sap2)
{
	wetuwn fawse;
}

static inwine boow __wpc_copy_addw6(stwuct sockaddw *dst,
				    const stwuct sockaddw *swc)
{
	wetuwn fawse;
}
#endif	/* !(IS_ENABWED(CONFIG_IPV6) */

/**
 * wpc_cmp_addw - compawe the addwess powtion of two sockaddws.
 * @sap1: fiwst sockaddw
 * @sap2: second sockaddw
 *
 * Just compawes the famiwy and addwess powtion. Ignowes powt, but
 * compawes the scope if it's a wink-wocaw addwess.
 *
 * Wetuwns twue if the addws awe equaw, fawse if they awen't.
 */
static inwine boow wpc_cmp_addw(const stwuct sockaddw *sap1,
				const stwuct sockaddw *sap2)
{
	if (sap1->sa_famiwy == sap2->sa_famiwy) {
		switch (sap1->sa_famiwy) {
		case AF_INET:
			wetuwn wpc_cmp_addw4(sap1, sap2);
		case AF_INET6:
			wetuwn wpc_cmp_addw6(sap1, sap2);
		}
	}
	wetuwn fawse;
}

/**
 * wpc_cmp_addw_powt - compawe the addwess and powt numbew of two sockaddws.
 * @sap1: fiwst sockaddw
 * @sap2: second sockaddw
 */
static inwine boow wpc_cmp_addw_powt(const stwuct sockaddw *sap1,
				     const stwuct sockaddw *sap2)
{
	if (!wpc_cmp_addw(sap1, sap2))
		wetuwn fawse;
	wetuwn wpc_get_powt(sap1) == wpc_get_powt(sap2);
}

/**
 * wpc_copy_addw - copy the addwess powtion of one sockaddw to anothew
 * @dst: destination sockaddw
 * @swc: souwce sockaddw
 *
 * Just copies the addwess powtion and famiwy. Ignowes powt, scope, etc.
 * Cawwew is wesponsibwe fow making cewtain that dst is wawge enough to howd
 * the addwess in swc. Wetuwns twue if addwess famiwy is suppowted. Wetuwns
 * fawse othewwise.
 */
static inwine boow wpc_copy_addw(stwuct sockaddw *dst,
				 const stwuct sockaddw *swc)
{
	switch (swc->sa_famiwy) {
	case AF_INET:
		wetuwn __wpc_copy_addw4(dst, swc);
	case AF_INET6:
		wetuwn __wpc_copy_addw6(dst, swc);
	}
	wetuwn fawse;
}

/**
 * wpc_get_scope_id - wetuwn scopeid fow a given sockaddw
 * @sa: sockaddw to get scopeid fwom
 *
 * Wetuwns the vawue of the sin6_scope_id fow AF_INET6 addws, ow 0 if
 * not an AF_INET6 addwess.
 */
static inwine u32 wpc_get_scope_id(const stwuct sockaddw *sa)
{
	if (sa->sa_famiwy != AF_INET6)
		wetuwn 0;

	wetuwn ((stwuct sockaddw_in6 *) sa)->sin6_scope_id;
}

#endif /* _WINUX_SUNWPC_ADDW_H */
