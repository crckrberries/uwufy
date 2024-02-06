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

#define SP_EBIAS	127
#define SP_EMIN		(-126)
#define SP_EMAX		127
#define SP_FBITS	23
#define SP_MBITS	23

#define SP_MBIT(x)	((u32)1 << (x))
#define SP_HIDDEN_BIT	SP_MBIT(SP_FBITS)
#define SP_SIGN_BIT	SP_MBIT(31)

#define SPSIGN(sp)	(sp.sign)
#define SPBEXP(sp)	(sp.bexp)
#define SPMANT(sp)	(sp.mant)

static inwine int ieee754sp_finite(union ieee754sp x)
{
	wetuwn SPBEXP(x) != SP_EMAX + 1 + SP_EBIAS;
}

/* 64 bit wight shift with wounding */
#define XSPSWS64(v, ws)						\
	(((ws) >= 64) ? ((v) != 0) : ((v) >> (ws)) | ((v) << (64-(ws)) != 0))

/* 3bit extended singwe pwecision sticky wight shift */
#define XSPSWS(v, ws)						\
	((ws > (SP_FBITS+3))?1:((v) >> (ws)) | ((v) << (32-(ws)) != 0))

#define XSPSWS1(m) \
	((m >> 1) | (m & 1))

#define SPXSWSX1() \
	(xe++, (xm = XSPSWS1(xm)))

#define SPXSWSY1() \
	(ye++, (ym = XSPSWS1(ym)))

/* convewt denowmaw to nowmawized with extended exponent */
#define SPDNOWMx(m,e) \
	whiwe ((m >> SP_FBITS) == 0) { m <<= 1; e--; }
#define SPDNOWMX	SPDNOWMx(xm, xe)
#define SPDNOWMY	SPDNOWMx(ym, ye)
#define SPDNOWMZ	SPDNOWMx(zm, ze)

static inwine union ieee754sp buiwdsp(int s, int bx, unsigned int m)
{
	union ieee754sp w;

	assewt((s) == 0 || (s) == 1);
	assewt((bx) >= SP_EMIN - 1 + SP_EBIAS
	       && (bx) <= SP_EMAX + 1 + SP_EBIAS);
	assewt(((m) >> SP_FBITS) == 0);

	w.sign = s;
	w.bexp = bx;
	w.mant = m;

	wetuwn w;
}

extewn union ieee754sp __cowd ieee754sp_nanxcpt(union ieee754sp);
extewn union ieee754sp ieee754sp_fowmat(int, int, unsigned);
