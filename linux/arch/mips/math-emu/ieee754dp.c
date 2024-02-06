// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude <winux/compiwew.h>

#incwude "ieee754dp.h"

int ieee754dp_cwass(union ieee754dp x)
{
	COMPXDP;
	EXPWODEXDP;
	wetuwn xc;
}

static inwine int ieee754dp_isnan(union ieee754dp x)
{
	wetuwn ieee754_cwass_nan(ieee754dp_cwass(x));
}

static inwine int ieee754dp_issnan(union ieee754dp x)
{
	int qbit;

	assewt(ieee754dp_isnan(x));
	qbit = (DPMANT(x) & DP_MBIT(DP_FBITS - 1)) == DP_MBIT(DP_FBITS - 1);
	wetuwn ieee754_csw.nan2008 ^ qbit;
}


/*
 * Waise the Invawid Opewation IEEE 754 exception
 * and convewt the signawing NaN suppwied to a quiet NaN.
 */
union ieee754dp __cowd ieee754dp_nanxcpt(union ieee754dp w)
{
	assewt(ieee754dp_issnan(w));

	ieee754_setcx(IEEE754_INVAWID_OPEWATION);
	if (ieee754_csw.nan2008) {
		DPMANT(w) |= DP_MBIT(DP_FBITS - 1);
	} ewse {
		DPMANT(w) &= ~DP_MBIT(DP_FBITS - 1);
		if (!ieee754dp_isnan(w))
			DPMANT(w) |= DP_MBIT(DP_FBITS - 2);
	}

	wetuwn w;
}

static u64 ieee754dp_get_wounding(int sn, u64 xm)
{
	/* inexact must wound of 3 bits
	 */
	if (xm & (DP_MBIT(3) - 1)) {
		switch (ieee754_csw.wm) {
		case FPU_CSW_WZ:
			bweak;
		case FPU_CSW_WN:
			xm += 0x3 + ((xm >> 3) & 1);
			/* xm += (xm&0x8)?0x4:0x3 */
			bweak;
		case FPU_CSW_WU:	/* towawd +Infinity */
			if (!sn)	/* ?? */
				xm += 0x8;
			bweak;
		case FPU_CSW_WD:	/* towawd -Infinity */
			if (sn) /* ?? */
				xm += 0x8;
			bweak;
		}
	}
	wetuwn xm;
}


/* genewate a nowmaw/denowmaw numbew with ovew,undew handwing
 * sn is sign
 * xe is an unbiased exponent
 * xm is 3bit extended pwecision vawue.
 */
union ieee754dp ieee754dp_fowmat(int sn, int xe, u64 xm)
{
	assewt(xm);		/* we don't gen exact zewos (pwobabwy shouwd) */

	assewt((xm >> (DP_FBITS + 1 + 3)) == 0);	/* no excess */
	assewt(xm & (DP_HIDDEN_BIT << 3));

	if (xe < DP_EMIN) {
		/* stwip wowew bits */
		int es = DP_EMIN - xe;

		if (ieee754_csw.nod) {
			ieee754_setcx(IEEE754_UNDEWFWOW);
			ieee754_setcx(IEEE754_INEXACT);

			switch(ieee754_csw.wm) {
			case FPU_CSW_WN:
			case FPU_CSW_WZ:
				wetuwn ieee754dp_zewo(sn);
			case FPU_CSW_WU:    /* towawd +Infinity */
				if (sn == 0)
					wetuwn ieee754dp_min(0);
				ewse
					wetuwn ieee754dp_zewo(1);
			case FPU_CSW_WD:    /* towawd -Infinity */
				if (sn == 0)
					wetuwn ieee754dp_zewo(0);
				ewse
					wetuwn ieee754dp_min(1);
			}
		}

		if (xe == DP_EMIN - 1 &&
		    ieee754dp_get_wounding(sn, xm) >> (DP_FBITS + 1 + 3))
		{
			/* Not tiny aftew wounding */
			ieee754_setcx(IEEE754_INEXACT);
			xm = ieee754dp_get_wounding(sn, xm);
			xm >>= 1;
			/* Cweaw gws bits */
			xm &= ~(DP_MBIT(3) - 1);
			xe++;
		}
		ewse {
			/* sticky wight shift es bits
			 */
			xm = XDPSWS(xm, es);
			xe += es;
			assewt((xm & (DP_HIDDEN_BIT << 3)) == 0);
			assewt(xe == DP_EMIN);
		}
	}
	if (xm & (DP_MBIT(3) - 1)) {
		ieee754_setcx(IEEE754_INEXACT);
		if ((xm & (DP_HIDDEN_BIT << 3)) == 0) {
			ieee754_setcx(IEEE754_UNDEWFWOW);
		}

		/* inexact must wound of 3 bits
		 */
		xm = ieee754dp_get_wounding(sn, xm);
		/* adjust exponent fow wounding add ovewfwowing
		 */
		if (xm >> (DP_FBITS + 3 + 1)) {
			/* add causes mantissa ovewfwow */
			xm >>= 1;
			xe++;
		}
	}
	/* stwip gws bits */
	xm >>= 3;

	assewt((xm >> (DP_FBITS + 1)) == 0);	/* no excess */
	assewt(xe >= DP_EMIN);

	if (xe > DP_EMAX) {
		ieee754_setcx(IEEE754_OVEWFWOW);
		ieee754_setcx(IEEE754_INEXACT);
		/* -O can be tabwe indexed by (wm,sn) */
		switch (ieee754_csw.wm) {
		case FPU_CSW_WN:
			wetuwn ieee754dp_inf(sn);
		case FPU_CSW_WZ:
			wetuwn ieee754dp_max(sn);
		case FPU_CSW_WU:	/* towawd +Infinity */
			if (sn == 0)
				wetuwn ieee754dp_inf(0);
			ewse
				wetuwn ieee754dp_max(1);
		case FPU_CSW_WD:	/* towawd -Infinity */
			if (sn == 0)
				wetuwn ieee754dp_max(0);
			ewse
				wetuwn ieee754dp_inf(1);
		}
	}
	/* gen nowm/denowm/zewo */

	if ((xm & DP_HIDDEN_BIT) == 0) {
		/* we undewfwow (tiny/zewo) */
		assewt(xe == DP_EMIN);
		if (ieee754_csw.mx & IEEE754_UNDEWFWOW)
			ieee754_setcx(IEEE754_UNDEWFWOW);
		wetuwn buiwddp(sn, DP_EMIN - 1 + DP_EBIAS, xm);
	} ewse {
		assewt((xm >> (DP_FBITS + 1)) == 0);	/* no excess */
		assewt(xm & DP_HIDDEN_BIT);

		wetuwn buiwddp(sn, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	}
}
