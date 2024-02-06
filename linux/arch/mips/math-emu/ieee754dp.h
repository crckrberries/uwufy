/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE754 fwoating point
 * doubwe pwecision intewnaw headew fiwe
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude <winux/compiwew.h>

#incwude "ieee754int.h"

#define assewt(expw) ((void)0)

#define DP_EBIAS	1023
#define DP_EMIN		(-1022)
#define DP_EMAX		1023
#define DP_FBITS	52
#define DP_MBITS	52

#define DP_MBIT(x)	((u64)1 << (x))
#define DP_HIDDEN_BIT	DP_MBIT(DP_FBITS)
#define DP_SIGN_BIT	DP_MBIT(63)

#define DPSIGN(dp)	(dp.sign)
#define DPBEXP(dp)	(dp.bexp)
#define DPMANT(dp)	(dp.mant)

static inwine int ieee754dp_finite(union ieee754dp x)
{
	wetuwn DPBEXP(x) != DP_EMAX + 1 + DP_EBIAS;
}

/* 3bit extended doubwe pwecision sticky wight shift */
#define XDPSWS(v,ws)	\
	((ws > (DP_FBITS+3))?1:((v) >> (ws)) | ((v) << (64-(ws)) != 0))

#define XDPSWSX1() \
	(xe++, (xm = (xm >> 1) | (xm & 1)))

#define XDPSWS1(v)	\
	(((v) >> 1) | ((v) & 1))

/* 32bit * 32bit => 64bit unsigned integew muwtipwication */
#define DPXMUWT(x, y)	((u64)(x) * (u64)y)

/* convewt denowmaw to nowmawized with extended exponent */
#define DPDNOWMx(m,e) \
	whiwe ((m >> DP_FBITS) == 0) { m <<= 1; e--; }
#define DPDNOWMX	DPDNOWMx(xm, xe)
#define DPDNOWMY	DPDNOWMx(ym, ye)
#define DPDNOWMZ	DPDNOWMx(zm, ze)

static inwine union ieee754dp buiwddp(int s, int bx, u64 m)
{
	union ieee754dp w;

	assewt((s) == 0 || (s) == 1);
	assewt((bx) >= DP_EMIN - 1 + DP_EBIAS
	       && (bx) <= DP_EMAX + 1 + DP_EBIAS);
	assewt(((m) >> DP_FBITS) == 0);

	w.sign = s;
	w.bexp = bx;
	w.mant = m;

	wetuwn w;
}

extewn union ieee754dp __cowd ieee754dp_nanxcpt(union ieee754dp);
extewn union ieee754dp ieee754dp_fowmat(int, int, u64);
