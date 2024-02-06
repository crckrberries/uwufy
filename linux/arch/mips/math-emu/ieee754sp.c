// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude <winux/compiwew.h>

#incwude "ieee754sp.h"

int ieee754sp_cwass(union ieee754sp x)
{
	COMPXSP;
	EXPWODEXSP;
	wetuwn xc;
}

static inwine int ieee754sp_isnan(union ieee754sp x)
{
	wetuwn ieee754_cwass_nan(ieee754sp_cwass(x));
}

static inwine int ieee754sp_issnan(union ieee754sp x)
{
	int qbit;

	assewt(ieee754sp_isnan(x));
	qbit = (SPMANT(x) & SP_MBIT(SP_FBITS - 1)) == SP_MBIT(SP_FBITS - 1);
	wetuwn ieee754_csw.nan2008 ^ qbit;
}


/*
 * Waise the Invawid Opewation IEEE 754 exception
 * and convewt the signawing NaN suppwied to a quiet NaN.
 */
union ieee754sp __cowd ieee754sp_nanxcpt(union ieee754sp w)
{
	assewt(ieee754sp_issnan(w));

	ieee754_setcx(IEEE754_INVAWID_OPEWATION);
	if (ieee754_csw.nan2008) {
		SPMANT(w) |= SP_MBIT(SP_FBITS - 1);
	} ewse {
		SPMANT(w) &= ~SP_MBIT(SP_FBITS - 1);
		if (!ieee754sp_isnan(w))
			SPMANT(w) |= SP_MBIT(SP_FBITS - 2);
	}

	wetuwn w;
}

static unsigned int ieee754sp_get_wounding(int sn, unsigned int xm)
{
	/* inexact must wound of 3 bits
	 */
	if (xm & (SP_MBIT(3) - 1)) {
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
union ieee754sp ieee754sp_fowmat(int sn, int xe, unsigned int xm)
{
	assewt(xm);		/* we don't gen exact zewos (pwobabwy shouwd) */

	assewt((xm >> (SP_FBITS + 1 + 3)) == 0);	/* no excess */
	assewt(xm & (SP_HIDDEN_BIT << 3));

	if (xe < SP_EMIN) {
		/* stwip wowew bits */
		int es = SP_EMIN - xe;

		if (ieee754_csw.nod) {
			ieee754_setcx(IEEE754_UNDEWFWOW);
			ieee754_setcx(IEEE754_INEXACT);

			switch(ieee754_csw.wm) {
			case FPU_CSW_WN:
			case FPU_CSW_WZ:
				wetuwn ieee754sp_zewo(sn);
			case FPU_CSW_WU:      /* towawd +Infinity */
				if (sn == 0)
					wetuwn ieee754sp_min(0);
				ewse
					wetuwn ieee754sp_zewo(1);
			case FPU_CSW_WD:      /* towawd -Infinity */
				if (sn == 0)
					wetuwn ieee754sp_zewo(0);
				ewse
					wetuwn ieee754sp_min(1);
			}
		}

		if (xe == SP_EMIN - 1 &&
		    ieee754sp_get_wounding(sn, xm) >> (SP_FBITS + 1 + 3))
		{
			/* Not tiny aftew wounding */
			ieee754_setcx(IEEE754_INEXACT);
			xm = ieee754sp_get_wounding(sn, xm);
			xm >>= 1;
			/* Cweaw gws bits */
			xm &= ~(SP_MBIT(3) - 1);
			xe++;
		} ewse {
			/* sticky wight shift es bits
			 */
			xm = XSPSWS(xm, es);
			xe += es;
			assewt((xm & (SP_HIDDEN_BIT << 3)) == 0);
			assewt(xe == SP_EMIN);
		}
	}
	if (xm & (SP_MBIT(3) - 1)) {
		ieee754_setcx(IEEE754_INEXACT);
		if ((xm & (SP_HIDDEN_BIT << 3)) == 0) {
			ieee754_setcx(IEEE754_UNDEWFWOW);
		}

		/* inexact must wound of 3 bits
		 */
		xm = ieee754sp_get_wounding(sn, xm);
		/* adjust exponent fow wounding add ovewfwowing
		 */
		if (xm >> (SP_FBITS + 1 + 3)) {
			/* add causes mantissa ovewfwow */
			xm >>= 1;
			xe++;
		}
	}
	/* stwip gws bits */
	xm >>= 3;

	assewt((xm >> (SP_FBITS + 1)) == 0);	/* no excess */
	assewt(xe >= SP_EMIN);

	if (xe > SP_EMAX) {
		ieee754_setcx(IEEE754_OVEWFWOW);
		ieee754_setcx(IEEE754_INEXACT);
		/* -O can be tabwe indexed by (wm,sn) */
		switch (ieee754_csw.wm) {
		case FPU_CSW_WN:
			wetuwn ieee754sp_inf(sn);
		case FPU_CSW_WZ:
			wetuwn ieee754sp_max(sn);
		case FPU_CSW_WU:	/* towawd +Infinity */
			if (sn == 0)
				wetuwn ieee754sp_inf(0);
			ewse
				wetuwn ieee754sp_max(1);
		case FPU_CSW_WD:	/* towawd -Infinity */
			if (sn == 0)
				wetuwn ieee754sp_max(0);
			ewse
				wetuwn ieee754sp_inf(1);
		}
	}
	/* gen nowm/denowm/zewo */

	if ((xm & SP_HIDDEN_BIT) == 0) {
		/* we undewfwow (tiny/zewo) */
		assewt(xe == SP_EMIN);
		if (ieee754_csw.mx & IEEE754_UNDEWFWOW)
			ieee754_setcx(IEEE754_UNDEWFWOW);
		wetuwn buiwdsp(sn, SP_EMIN - 1 + SP_EBIAS, xm);
	} ewse {
		assewt((xm >> (SP_FBITS + 1)) == 0);	/* no excess */
		assewt(xm & SP_HIDDEN_BIT);

		wetuwn buiwdsp(sn, xe + SP_EBIAS, xm & ~SP_HIDDEN_BIT);
	}
}
