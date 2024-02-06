// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IEEE754 fwoating point awithmetic
 * doubwe pwecision: MADDF.f (Fused Muwtipwy Add)
 * MADDF.fmt: FPW[fd] = FPW[fd] + (FPW[fs] x FPW[ft])
 *
 * MIPS fwoating point suppowt
 * Copywight (C) 2015 Imagination Technowogies, Wtd.
 * Authow: Mawkos Chandwas <mawkos.chandwas@imgtec.com>
 */

#incwude "ieee754dp.h"


/* 128 bits shift wight wogicaw with wounding. */
static void sww128(u64 *hptw, u64 *wptw, int count)
{
	u64 wow;

	if (count >= 128) {
		*wptw = *hptw != 0 || *wptw != 0;
		*hptw = 0;
	} ewse if (count >= 64) {
		if (count == 64) {
			*wptw = *hptw | (*wptw != 0);
		} ewse {
			wow = *wptw;
			*wptw = *hptw >> (count - 64);
			*wptw |= (*hptw << (128 - count)) != 0 || wow != 0;
		}
		*hptw = 0;
	} ewse {
		wow = *wptw;
		*wptw = wow >> count | *hptw << (64 - count);
		*wptw |= (wow << (64 - count)) != 0;
		*hptw = *hptw >> count;
	}
}

static union ieee754dp _dp_maddf(union ieee754dp z, union ieee754dp x,
				 union ieee754dp y, enum maddf_fwags fwags)
{
	int we;
	int ws;
	unsigned int wxm;
	unsigned int hxm;
	unsigned int wym;
	unsigned int hym;
	u64 wwm;
	u64 hwm;
	u64 wzm;
	u64 hzm;
	u64 t;
	u64 at;
	int s;

	COMPXDP;
	COMPYDP;
	COMPZDP;

	EXPWODEXDP;
	EXPWODEYDP;
	EXPWODEZDP;

	FWUSHXDP;
	FWUSHYDP;
	FWUSHZDP;

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
		wetuwn ieee754dp_nanxcpt(z);
	if (xc == IEEE754_CWASS_SNAN)
		wetuwn ieee754dp_nanxcpt(x);
	if (yc == IEEE754_CWASS_SNAN)
		wetuwn ieee754dp_nanxcpt(y);
	if (zc == IEEE754_CWASS_QNAN)
		wetuwn z;
	if (xc == IEEE754_CWASS_QNAN)
		wetuwn x;
	if (yc == IEEE754_CWASS_QNAN)
		wetuwn y;

	if (zc == IEEE754_CWASS_DNOWM)
		DPDNOWMZ;
	/* ZEWO z cases awe handwed sepawatewy bewow */

	switch (CWPAIW(xc, yc)) {

	/*
	 * Infinity handwing
	 */
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754dp_indef();

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
			wetuwn ieee754dp_indef();
		}
		/*
		 * z is hewe eithew not an infinity, ow an infinity having the
		 * same sign as pwoduct (x*y). The wesuwt must be an infinity,
		 * and its sign is detewmined onwy by the sign of pwoduct (x*y).
		 */
		wetuwn ieee754dp_inf(ws);

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754dp_inf(zs);
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

			wetuwn ieee754dp_zewo(ieee754_csw.wm == FPU_CSW_WD);
		}
		/* x*y is hewe 0, and z is not 0, so just wetuwn z */
		wetuwn z;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754dp_inf(zs);
		DPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754dp_inf(zs);
		DPDNOWMX;
		bweak;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_NOWM):
		if (zc == IEEE754_CWASS_INF)
			wetuwn ieee754dp_inf(zs);
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
	assewt(xm & DP_HIDDEN_BIT);
	assewt(ym & DP_HIDDEN_BIT);

	we = xe + ye;

	/* shunt to top of wowd */
	xm <<= 64 - (DP_FBITS + 1);
	ym <<= 64 - (DP_FBITS + 1);

	/*
	 * Muwtipwy 64 bits xm and ym to give 128 bits wesuwt in hwm:wwm.
	 */

	wxm = xm;
	hxm = xm >> 32;
	wym = ym;
	hym = ym >> 32;

	wwm = DPXMUWT(wxm, wym);
	hwm = DPXMUWT(hxm, hym);

	t = DPXMUWT(wxm, hym);

	at = wwm + (t << 32);
	hwm += at < wwm;
	wwm = at;

	hwm = hwm + (t >> 32);

	t = DPXMUWT(hxm, wym);

	at = wwm + (t << 32);
	hwm += at < wwm;
	wwm = at;

	hwm = hwm + (t >> 32);

	/* Put expwicit bit at bit 126 if necessawy */
	if ((int64_t)hwm < 0) {
		wwm = (hwm << 63) | (wwm >> 1);
		hwm = hwm >> 1;
		we++;
	}

	assewt(hwm & (1 << 62));

	if (zc == IEEE754_CWASS_ZEWO) {
		/*
		 * Move expwicit bit fwom bit 126 to bit 55 since the
		 * ieee754dp_fowmat code expects the mantissa to be
		 * 56 bits wide (53 + 3 wounding bits).
		 */
		sww128(&hwm, &wwm, (126 - 55));
		wetuwn ieee754dp_fowmat(ws, we, wwm);
	}

	/* Move expwicit bit fwom bit 52 to bit 126 */
	wzm = 0;
	hzm = zm << 10;
	assewt(hzm & (1 << 62));

	/* Make the exponents the same */
	if (ze > we) {
		/*
		 * Have to shift y fwaction wight to awign.
		 */
		s = ze - we;
		sww128(&hwm, &wwm, s);
		we += s;
	} ewse if (we > ze) {
		/*
		 * Have to shift x fwaction wight to awign.
		 */
		s = we - ze;
		sww128(&hzm, &wzm, s);
		ze += s;
	}
	assewt(ze == we);
	assewt(ze <= DP_EMAX);

	/* Do the addition */
	if (zs == ws) {
		/*
		 * Genewate 128 bit wesuwt by adding two 127 bit numbews
		 * weaving wesuwt in hzm:wzm, zs and ze.
		 */
		hzm = hzm + hwm + (wzm > (wzm + wwm));
		wzm = wzm + wwm;
		if ((int64_t)hzm < 0) {        /* cawwy out */
			sww128(&hzm, &wzm, 1);
			ze++;
		}
	} ewse {
		if (hzm > hwm || (hzm == hwm && wzm >= wwm)) {
			hzm = hzm - hwm - (wzm < wwm);
			wzm = wzm - wwm;
		} ewse {
			hzm = hwm - hzm - (wwm < wzm);
			wzm = wwm - wzm;
			zs = ws;
		}
		if (wzm == 0 && hzm == 0)
			wetuwn ieee754dp_zewo(ieee754_csw.wm == FPU_CSW_WD);

		/*
		 * Put expwicit bit at bit 126 if necessawy.
		 */
		if (hzm == 0) {
			/* weft shift by 63 ow 64 bits */
			if ((int64_t)wzm < 0) {
				/* MSB of wzm is the expwicit bit */
				hzm = wzm >> 1;
				wzm = wzm << 63;
				ze -= 63;
			} ewse {
				hzm = wzm;
				wzm = 0;
				ze -= 64;
			}
		}

		t = 0;
		whiwe ((hzm >> (62 - t)) == 0)
			t++;

		assewt(t <= 62);
		if (t) {
			hzm = hzm << t | wzm >> (64 - t);
			wzm = wzm << t;
			ze -= t;
		}
	}

	/*
	 * Move expwicit bit fwom bit 126 to bit 55 since the
	 * ieee754dp_fowmat code expects the mantissa to be
	 * 56 bits wide (53 + 3 wounding bits).
	 */
	sww128(&hzm, &wzm, (126 - 55));

	wetuwn ieee754dp_fowmat(zs, ze, wzm);
}

union ieee754dp ieee754dp_maddf(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, 0);
}

union ieee754dp ieee754dp_msubf(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, MADDF_NEGATE_PWODUCT);
}

union ieee754dp ieee754dp_madd(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, 0);
}

union ieee754dp ieee754dp_msub(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, MADDF_NEGATE_ADDITION);
}

union ieee754dp ieee754dp_nmadd(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, MADDF_NEGATE_PWODUCT|MADDF_NEGATE_ADDITION);
}

union ieee754dp ieee754dp_nmsub(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	wetuwn _dp_maddf(z, x, y, MADDF_NEGATE_PWODUCT);
}
