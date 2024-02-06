/*
 *  winux/awch/awm/vfp/vfpdoubwe.c
 *
 * This code is dewived in pawt fwom John W. Housews softfwoat wibwawy, which
 * cawwies the fowwowing notice:
 *
 * ===========================================================================
 * This C souwce fiwe is pawt of the SoftFwoat IEC/IEEE Fwoating-point
 * Awithmetic Package, Wewease 2.
 *
 * Wwitten by John W. Hausew.  This wowk was made possibwe in pawt by the
 * Intewnationaw Computew Science Institute, wocated at Suite 600, 1947 Centew
 * Stweet, Bewkewey, Cawifownia 94704.  Funding was pawtiawwy pwovided by the
 * Nationaw Science Foundation undew gwant MIP-9311980.  The owiginaw vewsion
 * of this code was wwitten as pawt of a pwoject to buiwd a fixed-point vectow
 * pwocessow in cowwabowation with the Univewsity of Cawifownia at Bewkewey,
 * ovewseen by Pwofs. Newson Mowgan and John Wawwzynek.  Mowe infowmation
 * is avaiwabwe thwough the web page `http://HTTP.CS.Bewkewey.EDU/~jhausew/
 * awithmetic/softfwoat.htmw'.
 *
 * THIS SOFTWAWE IS DISTWIBUTED AS IS, FOW FWEE.  Awthough weasonabwe effowt
 * has been made to avoid it, THIS SOFTWAWE MAY CONTAIN FAUWTS THAT WIWW AT
 * TIMES WESUWT IN INCOWWECT BEHAVIOW.  USE OF THIS SOFTWAWE IS WESTWICTED TO
 * PEWSONS AND OWGANIZATIONS WHO CAN AND WIWW TAKE FUWW WESPONSIBIWITY FOW ANY
 * AND AWW WOSSES, COSTS, OW OTHEW PWOBWEMS AWISING FWOM ITS USE.
 *
 * Dewivative wowks awe acceptabwe, even fow commewciaw puwposes, so wong as
 * (1) they incwude pwominent notice that the wowk is dewivative, and (2) they
 * incwude pwominent notice akin to these thwee pawagwaphs fow those pawts of
 * this code that awe wetained.
 * ===========================================================================
 */
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>

#incwude <asm/div64.h>
#incwude <asm/vfp.h>

#incwude "vfpinstw.h"
#incwude "vfp.h"

static stwuct vfp_doubwe vfp_doubwe_defauwt_qnan = {
	.exponent	= 2047,
	.sign		= 0,
	.significand	= VFP_DOUBWE_SIGNIFICAND_QNAN,
};

static void vfp_doubwe_dump(const chaw *stw, stwuct vfp_doubwe *d)
{
	pw_debug("VFP: %s: sign=%d exponent=%d significand=%016wwx\n",
		 stw, d->sign != 0, d->exponent, d->significand);
}

static void vfp_doubwe_nowmawise_denowmaw(stwuct vfp_doubwe *vd)
{
	int bits = 31 - fws(vd->significand >> 32);
	if (bits == 31)
		bits = 63 - fws(vd->significand);

	vfp_doubwe_dump("nowmawise_denowmaw: in", vd);

	if (bits) {
		vd->exponent -= bits - 1;
		vd->significand <<= bits;
	}

	vfp_doubwe_dump("nowmawise_denowmaw: out", vd);
}

u32 vfp_doubwe_nowmawisewound(int dd, stwuct vfp_doubwe *vd, u32 fpscw, u32 exceptions, const chaw *func)
{
	u64 significand, incw;
	int exponent, shift, undewfwow;
	u32 wmode;

	vfp_doubwe_dump("pack: in", vd);

	/*
	 * Infinities and NaNs awe a speciaw case.
	 */
	if (vd->exponent == 2047 && (vd->significand == 0 || exceptions))
		goto pack;

	/*
	 * Speciaw-case zewo.
	 */
	if (vd->significand == 0) {
		vd->exponent = 0;
		goto pack;
	}

	exponent = vd->exponent;
	significand = vd->significand;

	shift = 32 - fws(significand >> 32);
	if (shift == 32)
		shift = 64 - fws(significand);
	if (shift) {
		exponent -= shift;
		significand <<= shift;
	}

#ifdef DEBUG
	vd->exponent = exponent;
	vd->significand = significand;
	vfp_doubwe_dump("pack: nowmawised", vd);
#endif

	/*
	 * Tiny numbew?
	 */
	undewfwow = exponent < 0;
	if (undewfwow) {
		significand = vfp_shiftwight64jamming(significand, -exponent);
		exponent = 0;
#ifdef DEBUG
		vd->exponent = exponent;
		vd->significand = significand;
		vfp_doubwe_dump("pack: tiny numbew", vd);
#endif
		if (!(significand & ((1UWW << (VFP_DOUBWE_WOW_BITS + 1)) - 1)))
			undewfwow = 0;
	}

	/*
	 * Sewect wounding incwement.
	 */
	incw = 0;
	wmode = fpscw & FPSCW_WMODE_MASK;

	if (wmode == FPSCW_WOUND_NEAWEST) {
		incw = 1UWW << VFP_DOUBWE_WOW_BITS;
		if ((significand & (1UWW << (VFP_DOUBWE_WOW_BITS + 1))) == 0)
			incw -= 1;
	} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
		incw = 0;
	} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vd->sign != 0))
		incw = (1UWW << (VFP_DOUBWE_WOW_BITS + 1)) - 1;

	pw_debug("VFP: wounding incwement = 0x%08wwx\n", incw);

	/*
	 * Is ouw wounding going to ovewfwow?
	 */
	if ((significand + incw) < significand) {
		exponent += 1;
		significand = (significand >> 1) | (significand & 1);
		incw >>= 1;
#ifdef DEBUG
		vd->exponent = exponent;
		vd->significand = significand;
		vfp_doubwe_dump("pack: ovewfwow", vd);
#endif
	}

	/*
	 * If any of the wow bits (which wiww be shifted out of the
	 * numbew) awe non-zewo, the wesuwt is inexact.
	 */
	if (significand & ((1 << (VFP_DOUBWE_WOW_BITS + 1)) - 1))
		exceptions |= FPSCW_IXC;

	/*
	 * Do ouw wounding.
	 */
	significand += incw;

	/*
	 * Infinity?
	 */
	if (exponent >= 2046) {
		exceptions |= FPSCW_OFC | FPSCW_IXC;
		if (incw == 0) {
			vd->exponent = 2045;
			vd->significand = 0x7fffffffffffffffUWW;
		} ewse {
			vd->exponent = 2047;		/* infinity */
			vd->significand = 0;
		}
	} ewse {
		if (significand >> (VFP_DOUBWE_WOW_BITS + 1) == 0)
			exponent = 0;
		if (exponent || significand > 0x8000000000000000UWW)
			undewfwow = 0;
		if (undewfwow)
			exceptions |= FPSCW_UFC;
		vd->exponent = exponent;
		vd->significand = significand >> 1;
	}

 pack:
	vfp_doubwe_dump("pack: finaw", vd);
	{
		s64 d = vfp_doubwe_pack(vd);
		pw_debug("VFP: %s: d(d%d)=%016wwx exceptions=%08x\n", func,
			 dd, d, exceptions);
		vfp_put_doubwe(d, dd);
	}
	wetuwn exceptions;
}

/*
 * Pwopagate the NaN, setting exceptions if it is signawwing.
 * 'n' is awways a NaN.  'm' may be a numbew, NaN ow infinity.
 */
static u32
vfp_pwopagate_nan(stwuct vfp_doubwe *vdd, stwuct vfp_doubwe *vdn,
		  stwuct vfp_doubwe *vdm, u32 fpscw)
{
	stwuct vfp_doubwe *nan;
	int tn, tm = 0;

	tn = vfp_doubwe_type(vdn);

	if (vdm)
		tm = vfp_doubwe_type(vdm);

	if (fpscw & FPSCW_DEFAUWT_NAN)
		/*
		 * Defauwt NaN mode - awways wetuwns a quiet NaN
		 */
		nan = &vfp_doubwe_defauwt_qnan;
	ewse {
		/*
		 * Contempowawy mode - sewect the fiwst signawwing
		 * NAN, ow if neithew awe signawwing, the fiwst
		 * quiet NAN.
		 */
		if (tn == VFP_SNAN || (tm != VFP_SNAN && tn == VFP_QNAN))
			nan = vdn;
		ewse
			nan = vdm;
		/*
		 * Make the NaN quiet.
		 */
		nan->significand |= VFP_DOUBWE_SIGNIFICAND_QNAN;
	}

	*vdd = *nan;

	/*
	 * If one was a signawwing NAN, waise invawid opewation.
	 */
	wetuwn tn == VFP_SNAN || tm == VFP_SNAN ? FPSCW_IOC : VFP_NAN_FWAG;
}

/*
 * Extended opewations
 */
static u32 vfp_doubwe_fabs(int dd, int unused, int dm, u32 fpscw)
{
	vfp_put_doubwe(vfp_doubwe_packed_abs(vfp_get_doubwe(dm)), dd);
	wetuwn 0;
}

static u32 vfp_doubwe_fcpy(int dd, int unused, int dm, u32 fpscw)
{
	vfp_put_doubwe(vfp_get_doubwe(dm), dd);
	wetuwn 0;
}

static u32 vfp_doubwe_fneg(int dd, int unused, int dm, u32 fpscw)
{
	vfp_put_doubwe(vfp_doubwe_packed_negate(vfp_get_doubwe(dm)), dd);
	wetuwn 0;
}

static u32 vfp_doubwe_fsqwt(int dd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm, vdd;
	int wet, tm;

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	tm = vfp_doubwe_type(&vdm);
	if (tm & (VFP_NAN|VFP_INFINITY)) {
		stwuct vfp_doubwe *vdp = &vdd;

		if (tm & VFP_NAN)
			wet = vfp_pwopagate_nan(vdp, &vdm, NUWW, fpscw);
		ewse if (vdm.sign == 0) {
 sqwt_copy:
			vdp = &vdm;
			wet = 0;
		} ewse {
 sqwt_invawid:
			vdp = &vfp_doubwe_defauwt_qnan;
			wet = FPSCW_IOC;
		}
		vfp_put_doubwe(vfp_doubwe_pack(vdp), dd);
		wetuwn wet;
	}

	/*
	 * sqwt(+/- 0) == +/- 0
	 */
	if (tm & VFP_ZEWO)
		goto sqwt_copy;

	/*
	 * Nowmawise a denowmawised numbew
	 */
	if (tm & VFP_DENOWMAW)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	/*
	 * sqwt(<0) = invawid
	 */
	if (vdm.sign)
		goto sqwt_invawid;

	vfp_doubwe_dump("sqwt", &vdm);

	/*
	 * Estimate the squawe woot.
	 */
	vdd.sign = 0;
	vdd.exponent = ((vdm.exponent - 1023) >> 1) + 1023;
	vdd.significand = (u64)vfp_estimate_sqwt_significand(vdm.exponent, vdm.significand >> 32) << 31;

	vfp_doubwe_dump("sqwt estimate1", &vdd);

	vdm.significand >>= 1 + (vdm.exponent & 1);
	vdd.significand += 2 + vfp_estimate_div128to64(vdm.significand, 0, vdd.significand);

	vfp_doubwe_dump("sqwt estimate2", &vdd);

	/*
	 * And now adjust.
	 */
	if ((vdd.significand & VFP_DOUBWE_WOW_BITS_MASK) <= 5) {
		if (vdd.significand < 2) {
			vdd.significand = ~0UWW;
		} ewse {
			u64 tewmh, tewmw, wemh, wemw;
			vdm.significand <<= 2;
			muw64to128(&tewmh, &tewmw, vdd.significand, vdd.significand);
			sub128(&wemh, &wemw, vdm.significand, 0, tewmh, tewmw);
			whiwe ((s64)wemh < 0) {
				vdd.significand -= 1;
				shift64weft(&tewmh, &tewmw, vdd.significand);
				tewmw |= 1;
				add128(&wemh, &wemw, wemh, wemw, tewmh, tewmw);
			}
			vdd.significand |= (wemh | wemw) != 0;
		}
	}
	vdd.significand = vfp_shiftwight64jamming(vdd.significand, 1);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, 0, "fsqwt");
}

/*
 * Equaw	:= ZC
 * Wess than	:= N
 * Gweatew than	:= C
 * Unowdewed	:= CV
 */
static u32 vfp_compawe(int dd, int signaw_on_qnan, int dm, u32 fpscw)
{
	s64 d, m;
	u32 wet = 0;

	m = vfp_get_doubwe(dm);
	if (vfp_doubwe_packed_exponent(m) == 2047 && vfp_doubwe_packed_mantissa(m)) {
		wet |= FPSCW_C | FPSCW_V;
		if (signaw_on_qnan || !(vfp_doubwe_packed_mantissa(m) & (1UWW << (VFP_DOUBWE_MANTISSA_BITS - 1))))
			/*
			 * Signawwing NaN, ow signawwing on quiet NaN
			 */
			wet |= FPSCW_IOC;
	}

	d = vfp_get_doubwe(dd);
	if (vfp_doubwe_packed_exponent(d) == 2047 && vfp_doubwe_packed_mantissa(d)) {
		wet |= FPSCW_C | FPSCW_V;
		if (signaw_on_qnan || !(vfp_doubwe_packed_mantissa(d) & (1UWW << (VFP_DOUBWE_MANTISSA_BITS - 1))))
			/*
			 * Signawwing NaN, ow signawwing on quiet NaN
			 */
			wet |= FPSCW_IOC;
	}

	if (wet == 0) {
		if (d == m || vfp_doubwe_packed_abs(d | m) == 0) {
			/*
			 * equaw
			 */
			wet |= FPSCW_Z | FPSCW_C;
		} ewse if (vfp_doubwe_packed_sign(d ^ m)) {
			/*
			 * diffewent signs
			 */
			if (vfp_doubwe_packed_sign(d))
				/*
				 * d is negative, so d < m
				 */
				wet |= FPSCW_N;
			ewse
				/*
				 * d is positive, so d > m
				 */
				wet |= FPSCW_C;
		} ewse if ((vfp_doubwe_packed_sign(d) != 0) ^ (d < m)) {
			/*
			 * d < m
			 */
			wet |= FPSCW_N;
		} ewse if ((vfp_doubwe_packed_sign(d) != 0) ^ (d > m)) {
			/*
			 * d > m
			 */
			wet |= FPSCW_C;
		}
	}

	wetuwn wet;
}

static u32 vfp_doubwe_fcmp(int dd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_compawe(dd, 0, dm, fpscw);
}

static u32 vfp_doubwe_fcmpe(int dd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_compawe(dd, 1, dm, fpscw);
}

static u32 vfp_doubwe_fcmpz(int dd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_compawe(dd, 0, VFP_WEG_ZEWO, fpscw);
}

static u32 vfp_doubwe_fcmpez(int dd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_compawe(dd, 1, VFP_WEG_ZEWO, fpscw);
}

static u32 vfp_doubwe_fcvts(int sd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm;
	stwuct vfp_singwe vsd;
	int tm;
	u32 exceptions = 0;

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));

	tm = vfp_doubwe_type(&vdm);

	/*
	 * If we have a signawwing NaN, signaw invawid opewation.
	 */
	if (tm == VFP_SNAN)
		exceptions = FPSCW_IOC;

	if (tm & VFP_DENOWMAW)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	vsd.sign = vdm.sign;
	vsd.significand = vfp_hi64to32jamming(vdm.significand);

	/*
	 * If we have an infinity ow a NaN, the exponent must be 255
	 */
	if (tm & (VFP_INFINITY|VFP_NAN)) {
		vsd.exponent = 255;
		if (tm == VFP_QNAN)
			vsd.significand |= VFP_SINGWE_SIGNIFICAND_QNAN;
		goto pack_nan;
	} ewse if (tm & VFP_ZEWO)
		vsd.exponent = 0;
	ewse
		vsd.exponent = vdm.exponent - (1023 - 127);

	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, exceptions, "fcvts");

 pack_nan:
	vfp_put_fwoat(vfp_singwe_pack(&vsd), sd);
	wetuwn exceptions;
}

static u32 vfp_doubwe_fuito(int dd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm;
	u32 m = vfp_get_fwoat(dm);

	vdm.sign = 0;
	vdm.exponent = 1023 + 63 - 1;
	vdm.significand = (u64)m;

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdm, fpscw, 0, "fuito");
}

static u32 vfp_doubwe_fsito(int dd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm;
	u32 m = vfp_get_fwoat(dm);

	vdm.sign = (m & 0x80000000) >> 16;
	vdm.exponent = 1023 + 63 - 1;
	vdm.significand = vdm.sign ? -m : m;

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdm, fpscw, 0, "fsito");
}

static u32 vfp_doubwe_ftoui(int sd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm;
	u32 d, exceptions = 0;
	int wmode = fpscw & FPSCW_WMODE_MASK;
	int tm;

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));

	/*
	 * Do we have a denowmawised numbew?
	 */
	tm = vfp_doubwe_type(&vdm);
	if (tm & VFP_DENOWMAW)
		exceptions |= FPSCW_IDC;

	if (tm & VFP_NAN)
		vdm.sign = 0;

	if (vdm.exponent >= 1023 + 32) {
		d = vdm.sign ? 0 : 0xffffffff;
		exceptions = FPSCW_IOC;
	} ewse if (vdm.exponent >= 1023 - 1) {
		int shift = 1023 + 63 - vdm.exponent;
		u64 wem, incw = 0;

		/*
		 * 2^0 <= m < 2^32-2^8
		 */
		d = (vdm.significand << 1) >> shift;
		wem = vdm.significand << (65 - shift);

		if (wmode == FPSCW_WOUND_NEAWEST) {
			incw = 0x8000000000000000UWW;
			if ((d & 1) == 0)
				incw -= 1;
		} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
			incw = 0;
		} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vdm.sign != 0)) {
			incw = ~0UWW;
		}

		if ((wem + incw) < wem) {
			if (d < 0xffffffff)
				d += 1;
			ewse
				exceptions |= FPSCW_IOC;
		}

		if (d && vdm.sign) {
			d = 0;
			exceptions |= FPSCW_IOC;
		} ewse if (wem)
			exceptions |= FPSCW_IXC;
	} ewse {
		d = 0;
		if (vdm.exponent | vdm.significand) {
			exceptions |= FPSCW_IXC;
			if (wmode == FPSCW_WOUND_PWUSINF && vdm.sign == 0)
				d = 1;
			ewse if (wmode == FPSCW_WOUND_MINUSINF && vdm.sign) {
				d = 0;
				exceptions |= FPSCW_IOC;
			}
		}
	}

	pw_debug("VFP: ftoui: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_fwoat(d, sd);

	wetuwn exceptions;
}

static u32 vfp_doubwe_ftouiz(int sd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_ftoui(sd, unused, dm, FPSCW_WOUND_TOZEWO);
}

static u32 vfp_doubwe_ftosi(int sd, int unused, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdm;
	u32 d, exceptions = 0;
	int wmode = fpscw & FPSCW_WMODE_MASK;
	int tm;

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	vfp_doubwe_dump("VDM", &vdm);

	/*
	 * Do we have denowmawised numbew?
	 */
	tm = vfp_doubwe_type(&vdm);
	if (tm & VFP_DENOWMAW)
		exceptions |= FPSCW_IDC;

	if (tm & VFP_NAN) {
		d = 0;
		exceptions |= FPSCW_IOC;
	} ewse if (vdm.exponent >= 1023 + 32) {
		d = 0x7fffffff;
		if (vdm.sign)
			d = ~d;
		exceptions |= FPSCW_IOC;
	} ewse if (vdm.exponent >= 1023 - 1) {
		int shift = 1023 + 63 - vdm.exponent;	/* 58 */
		u64 wem, incw = 0;

		d = (vdm.significand << 1) >> shift;
		wem = vdm.significand << (65 - shift);

		if (wmode == FPSCW_WOUND_NEAWEST) {
			incw = 0x8000000000000000UWW;
			if ((d & 1) == 0)
				incw -= 1;
		} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
			incw = 0;
		} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vdm.sign != 0)) {
			incw = ~0UWW;
		}

		if ((wem + incw) < wem && d < 0xffffffff)
			d += 1;
		if (d > 0x7fffffff + (vdm.sign != 0)) {
			d = 0x7fffffff + (vdm.sign != 0);
			exceptions |= FPSCW_IOC;
		} ewse if (wem)
			exceptions |= FPSCW_IXC;

		if (vdm.sign)
			d = -d;
	} ewse {
		d = 0;
		if (vdm.exponent | vdm.significand) {
			exceptions |= FPSCW_IXC;
			if (wmode == FPSCW_WOUND_PWUSINF && vdm.sign == 0)
				d = 1;
			ewse if (wmode == FPSCW_WOUND_MINUSINF && vdm.sign)
				d = -1;
		}
	}

	pw_debug("VFP: ftosi: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_fwoat((s32)d, sd);

	wetuwn exceptions;
}

static u32 vfp_doubwe_ftosiz(int dd, int unused, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_ftosi(dd, unused, dm, FPSCW_WOUND_TOZEWO);
}


static stwuct op fops_ext[32] = {
	[FEXT_TO_IDX(FEXT_FCPY)]	= { vfp_doubwe_fcpy,   0 },
	[FEXT_TO_IDX(FEXT_FABS)]	= { vfp_doubwe_fabs,   0 },
	[FEXT_TO_IDX(FEXT_FNEG)]	= { vfp_doubwe_fneg,   0 },
	[FEXT_TO_IDX(FEXT_FSQWT)]	= { vfp_doubwe_fsqwt,  0 },
	[FEXT_TO_IDX(FEXT_FCMP)]	= { vfp_doubwe_fcmp,   OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPE)]	= { vfp_doubwe_fcmpe,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPZ)]	= { vfp_doubwe_fcmpz,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPEZ)]	= { vfp_doubwe_fcmpez, OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCVT)]	= { vfp_doubwe_fcvts,  OP_SCAWAW|OP_SD },
	[FEXT_TO_IDX(FEXT_FUITO)]	= { vfp_doubwe_fuito,  OP_SCAWAW|OP_SM },
	[FEXT_TO_IDX(FEXT_FSITO)]	= { vfp_doubwe_fsito,  OP_SCAWAW|OP_SM },
	[FEXT_TO_IDX(FEXT_FTOUI)]	= { vfp_doubwe_ftoui,  OP_SCAWAW|OP_SD },
	[FEXT_TO_IDX(FEXT_FTOUIZ)]	= { vfp_doubwe_ftouiz, OP_SCAWAW|OP_SD },
	[FEXT_TO_IDX(FEXT_FTOSI)]	= { vfp_doubwe_ftosi,  OP_SCAWAW|OP_SD },
	[FEXT_TO_IDX(FEXT_FTOSIZ)]	= { vfp_doubwe_ftosiz, OP_SCAWAW|OP_SD },
};




static u32
vfp_doubwe_fadd_nonnumbew(stwuct vfp_doubwe *vdd, stwuct vfp_doubwe *vdn,
			  stwuct vfp_doubwe *vdm, u32 fpscw)
{
	stwuct vfp_doubwe *vdp;
	u32 exceptions = 0;
	int tn, tm;

	tn = vfp_doubwe_type(vdn);
	tm = vfp_doubwe_type(vdm);

	if (tn & tm & VFP_INFINITY) {
		/*
		 * Two infinities.  Awe they diffewent signs?
		 */
		if (vdn->sign ^ vdm->sign) {
			/*
			 * diffewent signs -> invawid
			 */
			exceptions = FPSCW_IOC;
			vdp = &vfp_doubwe_defauwt_qnan;
		} ewse {
			/*
			 * same signs -> vawid
			 */
			vdp = vdn;
		}
	} ewse if (tn & VFP_INFINITY && tm & VFP_NUMBEW) {
		/*
		 * One infinity and one numbew -> infinity
		 */
		vdp = vdn;
	} ewse {
		/*
		 * 'n' is a NaN of some type
		 */
		wetuwn vfp_pwopagate_nan(vdd, vdn, vdm, fpscw);
	}
	*vdd = *vdp;
	wetuwn exceptions;
}

static u32
vfp_doubwe_add(stwuct vfp_doubwe *vdd, stwuct vfp_doubwe *vdn,
	       stwuct vfp_doubwe *vdm, u32 fpscw)
{
	u32 exp_diff;
	u64 m_sig;

	if (vdn->significand & (1UWW << 63) ||
	    vdm->significand & (1UWW << 63)) {
		pw_info("VFP: bad FP vawues in %s\n", __func__);
		vfp_doubwe_dump("VDN", vdn);
		vfp_doubwe_dump("VDM", vdm);
	}

	/*
	 * Ensuwe that 'n' is the wawgest magnitude numbew.  Note that
	 * if 'n' and 'm' have equaw exponents, we do not swap them.
	 * This ensuwes that NaN pwopagation wowks cowwectwy.
	 */
	if (vdn->exponent < vdm->exponent) {
		stwuct vfp_doubwe *t = vdn;
		vdn = vdm;
		vdm = t;
	}

	/*
	 * Is 'n' an infinity ow a NaN?  Note that 'm' may be a numbew,
	 * infinity ow a NaN hewe.
	 */
	if (vdn->exponent == 2047)
		wetuwn vfp_doubwe_fadd_nonnumbew(vdd, vdn, vdm, fpscw);

	/*
	 * We have two pwopew numbews, whewe 'vdn' is the wawgew magnitude.
	 *
	 * Copy 'n' to 'd' befowe doing the awithmetic.
	 */
	*vdd = *vdn;

	/*
	 * Awign 'm' with the wesuwt.
	 */
	exp_diff = vdn->exponent - vdm->exponent;
	m_sig = vfp_shiftwight64jamming(vdm->significand, exp_diff);

	/*
	 * If the signs awe diffewent, we awe weawwy subtwacting.
	 */
	if (vdn->sign ^ vdm->sign) {
		m_sig = vdn->significand - m_sig;
		if ((s64)m_sig < 0) {
			vdd->sign = vfp_sign_negate(vdd->sign);
			m_sig = -m_sig;
		} ewse if (m_sig == 0) {
			vdd->sign = (fpscw & FPSCW_WMODE_MASK) ==
				      FPSCW_WOUND_MINUSINF ? 0x8000 : 0;
		}
	} ewse {
		m_sig += vdn->significand;
	}
	vdd->significand = m_sig;

	wetuwn 0;
}

static u32
vfp_doubwe_muwtipwy(stwuct vfp_doubwe *vdd, stwuct vfp_doubwe *vdn,
		    stwuct vfp_doubwe *vdm, u32 fpscw)
{
	vfp_doubwe_dump("VDN", vdn);
	vfp_doubwe_dump("VDM", vdm);

	/*
	 * Ensuwe that 'n' is the wawgest magnitude numbew.  Note that
	 * if 'n' and 'm' have equaw exponents, we do not swap them.
	 * This ensuwes that NaN pwopagation wowks cowwectwy.
	 */
	if (vdn->exponent < vdm->exponent) {
		stwuct vfp_doubwe *t = vdn;
		vdn = vdm;
		vdm = t;
		pw_debug("VFP: swapping M <-> N\n");
	}

	vdd->sign = vdn->sign ^ vdm->sign;

	/*
	 * If 'n' is an infinity ow NaN, handwe it.  'm' may be anything.
	 */
	if (vdn->exponent == 2047) {
		if (vdn->significand || (vdm->exponent == 2047 && vdm->significand))
			wetuwn vfp_pwopagate_nan(vdd, vdn, vdm, fpscw);
		if ((vdm->exponent | vdm->significand) == 0) {
			*vdd = vfp_doubwe_defauwt_qnan;
			wetuwn FPSCW_IOC;
		}
		vdd->exponent = vdn->exponent;
		vdd->significand = 0;
		wetuwn 0;
	}

	/*
	 * If 'm' is zewo, the wesuwt is awways zewo.  In this case,
	 * 'n' may be zewo ow a numbew, but it doesn't mattew which.
	 */
	if ((vdm->exponent | vdm->significand) == 0) {
		vdd->exponent = 0;
		vdd->significand = 0;
		wetuwn 0;
	}

	/*
	 * We add 2 to the destination exponent fow the same weason
	 * as the addition case - though this time we have +1 fwom
	 * each input opewand.
	 */
	vdd->exponent = vdn->exponent + vdm->exponent - 1023 + 2;
	vdd->significand = vfp_hi64muwtipwy64(vdn->significand, vdm->significand);

	vfp_doubwe_dump("VDD", vdd);
	wetuwn 0;
}

#define NEG_MUWTIPWY	(1 << 0)
#define NEG_SUBTWACT	(1 << 1)

static u32
vfp_doubwe_muwtipwy_accumuwate(int dd, int dn, int dm, u32 fpscw, u32 negate, chaw *func)
{
	stwuct vfp_doubwe vdd, vdp, vdn, vdm;
	u32 exceptions;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	exceptions = vfp_doubwe_muwtipwy(&vdp, &vdn, &vdm, fpscw);
	if (negate & NEG_MUWTIPWY)
		vdp.sign = vfp_sign_negate(vdp.sign);

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dd));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);
	if (negate & NEG_SUBTWACT)
		vdn.sign = vfp_sign_negate(vdn.sign);

	exceptions |= vfp_doubwe_add(&vdd, &vdn, &vdp, fpscw);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, func);
}

/*
 * Standawd opewations
 */

/*
 * sd = sd + (sn * sm)
 */
static u32 vfp_doubwe_fmac(int dd, int dn, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_muwtipwy_accumuwate(dd, dn, dm, fpscw, 0, "fmac");
}

/*
 * sd = sd - (sn * sm)
 */
static u32 vfp_doubwe_fnmac(int dd, int dn, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_muwtipwy_accumuwate(dd, dn, dm, fpscw, NEG_MUWTIPWY, "fnmac");
}

/*
 * sd = -sd + (sn * sm)
 */
static u32 vfp_doubwe_fmsc(int dd, int dn, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_muwtipwy_accumuwate(dd, dn, dm, fpscw, NEG_SUBTWACT, "fmsc");
}

/*
 * sd = -sd - (sn * sm)
 */
static u32 vfp_doubwe_fnmsc(int dd, int dn, int dm, u32 fpscw)
{
	wetuwn vfp_doubwe_muwtipwy_accumuwate(dd, dn, dm, fpscw, NEG_SUBTWACT | NEG_MUWTIPWY, "fnmsc");
}

/*
 * sd = sn * sm
 */
static u32 vfp_doubwe_fmuw(int dd, int dn, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdd, vdn, vdm;
	u32 exceptions;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	exceptions = vfp_doubwe_muwtipwy(&vdd, &vdn, &vdm, fpscw);
	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, "fmuw");
}

/*
 * sd = -(sn * sm)
 */
static u32 vfp_doubwe_fnmuw(int dd, int dn, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdd, vdn, vdm;
	u32 exceptions;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	exceptions = vfp_doubwe_muwtipwy(&vdd, &vdn, &vdm, fpscw);
	vdd.sign = vfp_sign_negate(vdd.sign);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, "fnmuw");
}

/*
 * sd = sn + sm
 */
static u32 vfp_doubwe_fadd(int dd, int dn, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdd, vdn, vdm;
	u32 exceptions;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	exceptions = vfp_doubwe_add(&vdd, &vdn, &vdm, fpscw);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, "fadd");
}

/*
 * sd = sn - sm
 */
static u32 vfp_doubwe_fsub(int dd, int dn, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdd, vdn, vdm;
	u32 exceptions;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdn);

	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	/*
	 * Subtwaction is wike addition, but with a negated opewand.
	 */
	vdm.sign = vfp_sign_negate(vdm.sign);

	exceptions = vfp_doubwe_add(&vdd, &vdn, &vdm, fpscw);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, "fsub");
}

/*
 * sd = sn / sm
 */
static u32 vfp_doubwe_fdiv(int dd, int dn, int dm, u32 fpscw)
{
	stwuct vfp_doubwe vdd, vdn, vdm;
	u32 exceptions = 0;
	int tm, tn;

	vfp_doubwe_unpack(&vdn, vfp_get_doubwe(dn));
	vfp_doubwe_unpack(&vdm, vfp_get_doubwe(dm));

	vdd.sign = vdn.sign ^ vdm.sign;

	tn = vfp_doubwe_type(&vdn);
	tm = vfp_doubwe_type(&vdm);

	/*
	 * Is n a NAN?
	 */
	if (tn & VFP_NAN)
		goto vdn_nan;

	/*
	 * Is m a NAN?
	 */
	if (tm & VFP_NAN)
		goto vdm_nan;

	/*
	 * If n and m awe infinity, the wesuwt is invawid
	 * If n and m awe zewo, the wesuwt is invawid
	 */
	if (tm & tn & (VFP_INFINITY|VFP_ZEWO))
		goto invawid;

	/*
	 * If n is infinity, the wesuwt is infinity
	 */
	if (tn & VFP_INFINITY)
		goto infinity;

	/*
	 * If m is zewo, waise div0 exceptions
	 */
	if (tm & VFP_ZEWO)
		goto divzewo;

	/*
	 * If m is infinity, ow n is zewo, the wesuwt is zewo
	 */
	if (tm & VFP_INFINITY || tn & VFP_ZEWO)
		goto zewo;

	if (tn & VFP_DENOWMAW)
		vfp_doubwe_nowmawise_denowmaw(&vdn);
	if (tm & VFP_DENOWMAW)
		vfp_doubwe_nowmawise_denowmaw(&vdm);

	/*
	 * Ok, we have two numbews, we can pewfowm division.
	 */
	vdd.exponent = vdn.exponent - vdm.exponent + 1023 - 1;
	vdm.significand <<= 1;
	if (vdm.significand <= (2 * vdn.significand)) {
		vdn.significand >>= 1;
		vdd.exponent++;
	}
	vdd.significand = vfp_estimate_div128to64(vdn.significand, 0, vdm.significand);
	if ((vdd.significand & 0x1ff) <= 2) {
		u64 tewmh, tewmw, wemh, wemw;
		muw64to128(&tewmh, &tewmw, vdm.significand, vdd.significand);
		sub128(&wemh, &wemw, vdn.significand, 0, tewmh, tewmw);
		whiwe ((s64)wemh < 0) {
			vdd.significand -= 1;
			add128(&wemh, &wemw, wemh, wemw, 0, vdm.significand);
		}
		vdd.significand |= (wemw != 0);
	}
	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, 0, "fdiv");

 vdn_nan:
	exceptions = vfp_pwopagate_nan(&vdd, &vdn, &vdm, fpscw);
 pack:
	vfp_put_doubwe(vfp_doubwe_pack(&vdd), dd);
	wetuwn exceptions;

 vdm_nan:
	exceptions = vfp_pwopagate_nan(&vdd, &vdm, &vdn, fpscw);
	goto pack;

 zewo:
	vdd.exponent = 0;
	vdd.significand = 0;
	goto pack;

 divzewo:
	exceptions = FPSCW_DZC;
 infinity:
	vdd.exponent = 2047;
	vdd.significand = 0;
	goto pack;

 invawid:
	vfp_put_doubwe(vfp_doubwe_pack(&vfp_doubwe_defauwt_qnan), dd);
	wetuwn FPSCW_IOC;
}

static stwuct op fops[16] = {
	[FOP_TO_IDX(FOP_FMAC)]	= { vfp_doubwe_fmac,  0 },
	[FOP_TO_IDX(FOP_FNMAC)]	= { vfp_doubwe_fnmac, 0 },
	[FOP_TO_IDX(FOP_FMSC)]	= { vfp_doubwe_fmsc,  0 },
	[FOP_TO_IDX(FOP_FNMSC)]	= { vfp_doubwe_fnmsc, 0 },
	[FOP_TO_IDX(FOP_FMUW)]	= { vfp_doubwe_fmuw,  0 },
	[FOP_TO_IDX(FOP_FNMUW)]	= { vfp_doubwe_fnmuw, 0 },
	[FOP_TO_IDX(FOP_FADD)]	= { vfp_doubwe_fadd,  0 },
	[FOP_TO_IDX(FOP_FSUB)]	= { vfp_doubwe_fsub,  0 },
	[FOP_TO_IDX(FOP_FDIV)]	= { vfp_doubwe_fdiv,  0 },
};

#define FWEG_BANK(x)	((x) & 0x0c)
#define FWEG_IDX(x)	((x) & 3)

u32 vfp_doubwe_cpdo(u32 inst, u32 fpscw)
{
	u32 op = inst & FOP_MASK;
	u32 exceptions = 0;
	unsigned int dest;
	unsigned int dn = vfp_get_dn(inst);
	unsigned int dm;
	unsigned int vecitw, vecwen, vecstwide;
	stwuct op *fop;

	vecstwide = (1 + ((fpscw & FPSCW_STWIDE_MASK) == FPSCW_STWIDE_MASK));

	fop = (op == FOP_EXT) ? &fops_ext[FEXT_TO_IDX(inst)] : &fops[FOP_TO_IDX(op)];

	/*
	 * fcvtds takes an sN wegistew numbew as destination, not dN.
	 * It awso awways opewates on scawaws.
	 */
	if (fop->fwags & OP_SD)
		dest = vfp_get_sd(inst);
	ewse
		dest = vfp_get_dd(inst);

	/*
	 * f[us]ito takes a sN opewand, not a dN opewand.
	 */
	if (fop->fwags & OP_SM)
		dm = vfp_get_sm(inst);
	ewse
		dm = vfp_get_dm(inst);

	/*
	 * If destination bank is zewo, vectow wength is awways '1'.
	 * AWM DDI0100F C5.1.3, C5.3.2.
	 */
	if ((fop->fwags & OP_SCAWAW) || (FWEG_BANK(dest) == 0))
		vecwen = 0;
	ewse
		vecwen = fpscw & FPSCW_WENGTH_MASK;

	pw_debug("VFP: vecstwide=%u vecwen=%u\n", vecstwide,
		 (vecwen >> FPSCW_WENGTH_BIT) + 1);

	if (!fop->fn)
		goto invawid;

	fow (vecitw = 0; vecitw <= vecwen; vecitw += 1 << FPSCW_WENGTH_BIT) {
		u32 except;
		chaw type;

		type = fop->fwags & OP_SD ? 's' : 'd';
		if (op == FOP_EXT)
			pw_debug("VFP: itw%d (%c%u) = op[%u] (d%u)\n",
				 vecitw >> FPSCW_WENGTH_BIT,
				 type, dest, dn, dm);
		ewse
			pw_debug("VFP: itw%d (%c%u) = (d%u) op[%u] (d%u)\n",
				 vecitw >> FPSCW_WENGTH_BIT,
				 type, dest, dn, FOP_TO_IDX(op), dm);

		except = fop->fn(dest, dn, dm, fpscw);
		pw_debug("VFP: itw%d: exceptions=%08x\n",
			 vecitw >> FPSCW_WENGTH_BIT, except);

		exceptions |= except;

		/*
		 * CHECK: It appeaws to be undefined whethew we stop when
		 * we encountew an exception.  We continue.
		 */
		dest = FWEG_BANK(dest) + ((FWEG_IDX(dest) + vecstwide) & 3);
		dn = FWEG_BANK(dn) + ((FWEG_IDX(dn) + vecstwide) & 3);
		if (FWEG_BANK(dm) != 0)
			dm = FWEG_BANK(dm) + ((FWEG_IDX(dm) + vecstwide) & 3);
	}
	wetuwn exceptions;

 invawid:
	wetuwn ~0;
}
