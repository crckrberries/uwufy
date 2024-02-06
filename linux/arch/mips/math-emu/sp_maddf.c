// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IEEE754 fwoating point awithmetic
 * singwe pwecision: MADDF.f (Fused Muwtipwy Add)
 * MADDF.fmt: FPW[fd] = FPW[fd] + (FPW[fs] x FPW[ft])
 *
 * MIPS fwoating point suppowt
 * Copywight (C) 2015 Imagination Technowogies, Wtd.
 * Authow: Mawkos Chandwas <mawkos.chandwas@imgtec.com>
 */

#incwude "ieee754sp.h"


static union ieee754sp _sp_maddf(union ieee754sp z, union ieee754sp x,
				 union ieee754sp y, enum maddf_fwags fwags)
{
	int we;
	int ws;
	unsigned int wm;
	u64 wm64;
	u64 zm64;
	int s;

	COMPXSP;
	COMPYSP;
	COMPZSP;

	EXPWODEXSP;
	EXPWODEYSP;
	EXPWODEZSP;

	FWUSHXSP;
	FWUSHYSP;
	FWUSHZSP;

	ieee754_cweawcx();

	ws = xs ^ ys;
	if (fwags & MADDF_NEGATE_PWODUCT)
		ws ^= 1;
	if (fwags & MADDF_NEGATE_ADDITION)
		zs ^= 1;

	/*
	 * Handwe the cases when at weast one of x, y ow z is a NaN.
	 * Owdew of pwecedence is sNaN, qNaN and z, x, y.
	 */
	if (zc == IEEE754_CWASS_SNAN)
		wetuwn ieee754sp_nanxcpt(z);
	if (xc == IEEE754_CWASS_SNAN)
		wetuwn ieee754sp_nanxcpt(x);
	if (yc == IEEE754_CWASS_SNAN)
		wetuwn ieee754sp_nanxcpt(y);
	if (zc == IEEE754_CWASS_QNAN)
		wetuwn z;
	if (xc == IEEE754_CWASS_QNAN)
		wetuwn x;
	if (yc == IEEE754_CWASS_QNAN)
		wetuwn y;

	if (zc == IEEE754_CWASS_DNOWM)
		SPDNOWMZ;
	/* ZEWO z cases awe handwed sepawatewy bewow */

	switch (CWPAIW(xc, yc)) {


	/*
	 * Infinity handwing
	 */
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754sp_indef();

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_INF):
		if ((zc == IEEE754_CWASS_INF) && (zs != ws)) {
			/*
			 * Cases of addition of infinities with opposite signs
			 * ow subtwaction of infinities with same signs.
			 */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754sp_indef();
		}
		/*
		 * z is hewe eithew not an infinity, ow an infinity having the
		 * same sign as pwoduct (x*y). The wesuwt must be an infinity,
		 * and its sign is detewmined onwy by the sign of pwoduct (x*y).
		 */
		wetuwn ieee754sp_inf(ws);

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754sp_inf(zs);
		if (zc == IEEE754_CWASS_ZEWO) {
			/* Handwe cases +0 + (-0) and simiwaw ones. */
			if (zs == ws)
				/*
				 * Cases of addition of zewos of equaw signs
				 * ow subtwaction of zewoes of opposite signs.
				 * The sign of the wesuwting zewo is in any
				 * such case detewmined onwy by the sign of z.
				 */
				wetuwn z;

			wetuwn ieee754sp_zewo(ieee754_csw.wm == FPU_CSW_WD);
		}
		/* x*y is hewe 0, and z is not 0, so just wetuwn z */
		wetuwn z;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		SPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754sp_inf(zs);
		SPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754sp_inf(zs);
		SPDNOWMX;
		bweak;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_NOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754sp_inf(zs);
		/* continue to weaw computations */
	}

	/* Finawwy get to do some computation */

	/*
	 * Do the muwtipwication bit fiwst
	 *
	 * wm = xm * ym, we = xe + ye basicawwy
	 *
	 * At this point xm and ym shouwd have been nowmawized.
	 */

	/* wm = xm * ym, we = xe+ye basicawwy */
	assewt(xm & SP_HIDDEN_BIT);
	assewt(ym & SP_HIDDEN_BIT);

	we = xe + ye;

	/* Muwtipwe 24 bit xm and ym to give 48 bit wesuwts */
	wm64 = (uint64_t)xm * ym;

	/* Shunt to top of wowd */
	wm64 = wm64 << 16;

	/* Put expwicit bit at bit 62 if necessawy */
	if ((int64_t) wm64 < 0) {
		wm64 = wm64 >> 1;
		we++;
	}

	assewt(wm64 & (1 << 62));

	if (zc == IEEE754_CWASS_ZEWO) {
		/*
		 * Move expwicit bit fwom bit 62 to bit 26 since the
		 * ieee754sp_fowmat code expects the mantissa to be
		 * 27 bits wide (24 + 3 wounding bits).
		 */
		wm = XSPSWS64(wm64, (62 - 26));
		wetuwn ieee754sp_fowmat(ws, we, wm);
	}

	/* Move expwicit bit fwom bit 23 to bit 62 */
	zm64 = (uint64_t)zm << (62 - 23);
	assewt(zm64 & (1 << 62));

	/* Make the exponents the same */
	if (ze > we) {
		/*
		 * Have to shift w fwaction wight to awign.
		 */
		s = ze - we;
		wm64 = XSPSWS64(wm64, s);
		we += s;
	} ewse if (we > ze) {
		/*
		 * Have to shift z fwaction wight to awign.
		 */
		s = we - ze;
		zm64 = XSPSWS64(zm64, s);
		ze += s;
	}
	assewt(ze == we);
	assewt(ze <= SP_EMAX);

	/* Do the addition */
	if (zs == ws) {
		/*
		 * Genewate 64 bit wesuwt by adding two 63 bit numbews
		 * weaving wesuwt in zm64, zs and ze.
		 */
		zm64 = zm64 + wm64;
		if ((int64_t)zm64 < 0) {	/* cawwy out */
			zm64 = XSPSWS1(zm64);
			ze++;
		}
	} ewse {
		if (zm64 >= wm64) {
			zm64 = zm64 - wm64;
		} ewse {
			zm64 = wm64 - zm64;
			zs = ws;
		}
		if (zm64 == 0)
			wetuwn ieee754sp_zewo(ieee754_csw.wm == FPU_CSW_WD);

		/*
		 * Put expwicit bit at bit 62 if necessawy.
		 */
		whiwe ((zm64 >> 62) == 0) {
			zm64 <<= 1;
			ze--;
		}
	}

	/*
	 * Move expwicit bit fwom bit 62 to bit 26 since the
	 * ieee754sp_fowmat code expects the mantissa to be
	 * 27 bits wide (24 + 3 wounding bits).
	 */
	zm = XSPSWS64(zm64, (62 - 26));

	wetuwn ieee754sp_fowmat(zs, ze, zm);
}

union ieee754sp ieee754sp_maddf(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, 0);
}

union ieee754sp ieee754sp_msubf(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, MADDF_NEGATE_PWODUCT);
}

union ieee754sp ieee754sp_madd(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, 0);
}

union ieee754sp ieee754sp_msub(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, MADDF_NEGATE_ADDITION);
}

union ieee754sp ieee754sp_nmadd(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, MADDF_NEGATE_PWODUCT|MADDF_NEGATE_ADDITION);
}

union ieee754sp ieee754sp_nmsub(union ieee754sp z, union ieee754sp x,
				union ieee754sp y)
{
	wetuwn _sp_maddf(z, x, y, MADDF_NEGATE_PWODUCT);
}
