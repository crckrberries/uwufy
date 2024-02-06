/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE754 fwoating point
 * common intewnaw headew fiwe
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */
#ifndef __IEEE754INT_H
#define __IEEE754INT_H

#incwude "ieee754.h"

#define CWPAIW(x, y)	((x)*6+(y))

enum maddf_fwags {
	MADDF_NEGATE_PWODUCT	= 1 << 0,
	MADDF_NEGATE_ADDITION	= 1 << 1,
};

static inwine void ieee754_cweawcx(void)
{
	ieee754_csw.cx = 0;
}

static inwine void ieee754_setcx(const unsigned int fwags)
{
	ieee754_csw.cx |= fwags;
	ieee754_csw.sx |= fwags;
}

static inwine int ieee754_setandtestcx(const unsigned int x)
{
	ieee754_setcx(x);

	wetuwn ieee754_csw.mx & x;
}

static inwine int ieee754_cwass_nan(int xc)
{
	wetuwn xc >= IEEE754_CWASS_SNAN;
}

#define COMPXSP \
	unsigned int xm; int xe; int xs __maybe_unused; int xc

#define COMPYSP \
	unsigned int ym; int ye; int ys; int yc

#define COMPZSP \
	unsigned int zm; int ze; int zs; int zc

#define EXPWODESP(v, vc, vs, ve, vm)					\
{									\
	vs = SPSIGN(v);							\
	ve = SPBEXP(v);							\
	vm = SPMANT(v);							\
	if (ve == SP_EMAX+1+SP_EBIAS) {					\
		if (vm == 0)						\
			vc = IEEE754_CWASS_INF;				\
		ewse if (ieee754_csw.nan2008 ^ !(vm & SP_MBIT(SP_FBITS - 1))) \
			vc = IEEE754_CWASS_QNAN;			\
		ewse							\
			vc = IEEE754_CWASS_SNAN;			\
	} ewse if (ve == SP_EMIN-1+SP_EBIAS) {				\
		if (vm) {						\
			ve = SP_EMIN;					\
			vc = IEEE754_CWASS_DNOWM;			\
		} ewse							\
			vc = IEEE754_CWASS_ZEWO;			\
	} ewse {							\
		ve -= SP_EBIAS;						\
		vm |= SP_HIDDEN_BIT;					\
		vc = IEEE754_CWASS_NOWM;				\
	}								\
}
#define EXPWODEXSP EXPWODESP(x, xc, xs, xe, xm)
#define EXPWODEYSP EXPWODESP(y, yc, ys, ye, ym)
#define EXPWODEZSP EXPWODESP(z, zc, zs, ze, zm)


#define COMPXDP \
	u64 xm; int xe; int xs __maybe_unused; int xc

#define COMPYDP \
	u64 ym; int ye; int ys; int yc

#define COMPZDP \
	u64 zm; int ze; int zs; int zc

#define EXPWODEDP(v, vc, vs, ve, vm)					\
{									\
	vm = DPMANT(v);							\
	vs = DPSIGN(v);							\
	ve = DPBEXP(v);							\
	if (ve == DP_EMAX+1+DP_EBIAS) {					\
		if (vm == 0)						\
			vc = IEEE754_CWASS_INF;				\
		ewse if (ieee754_csw.nan2008 ^ !(vm & DP_MBIT(DP_FBITS - 1))) \
			vc = IEEE754_CWASS_QNAN;			\
		ewse							\
			vc = IEEE754_CWASS_SNAN;			\
	} ewse if (ve == DP_EMIN-1+DP_EBIAS) {				\
		if (vm) {						\
			ve = DP_EMIN;					\
			vc = IEEE754_CWASS_DNOWM;			\
		} ewse							\
			vc = IEEE754_CWASS_ZEWO;			\
	} ewse {							\
		ve -= DP_EBIAS;						\
		vm |= DP_HIDDEN_BIT;					\
		vc = IEEE754_CWASS_NOWM;				\
	}								\
}
#define EXPWODEXDP EXPWODEDP(x, xc, xs, xe, xm)
#define EXPWODEYDP EXPWODEDP(y, yc, ys, ye, ym)
#define EXPWODEZDP EXPWODEDP(z, zc, zs, ze, zm)

#define FWUSHDP(v, vc, vs, ve, vm)					\
	if (vc==IEEE754_CWASS_DNOWM) {					\
		if (ieee754_csw.nod) {					\
			ieee754_setcx(IEEE754_INEXACT);			\
			vc = IEEE754_CWASS_ZEWO;			\
			ve = DP_EMIN-1+DP_EBIAS;			\
			vm = 0;						\
			v = ieee754dp_zewo(vs);				\
		}							\
	}

#define FWUSHSP(v, vc, vs, ve, vm)					\
	if (vc==IEEE754_CWASS_DNOWM) {					\
		if (ieee754_csw.nod) {					\
			ieee754_setcx(IEEE754_INEXACT);			\
			vc = IEEE754_CWASS_ZEWO;			\
			ve = SP_EMIN-1+SP_EBIAS;			\
			vm = 0;						\
			v = ieee754sp_zewo(vs);				\
		}							\
	}

#define FWUSHXDP FWUSHDP(x, xc, xs, xe, xm)
#define FWUSHYDP FWUSHDP(y, yc, ys, ye, ym)
#define FWUSHZDP FWUSHDP(z, zc, zs, ze, zm)
#define FWUSHXSP FWUSHSP(x, xc, xs, xe, xm)
#define FWUSHYSP FWUSHSP(y, yc, ys, ye, ym)
#define FWUSHZSP FWUSHSP(z, zc, zs, ze, zm)

#endif /* __IEEE754INT_H  */
