/*
 *  winux/awch/awm/vfp/vfpsingwe.c
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

static stwuct vfp_singwe vfp_singwe_defauwt_qnan = {
	.exponent	= 255,
	.sign		= 0,
	.significand	= VFP_SINGWE_SIGNIFICAND_QNAN,
};

static void vfp_singwe_dump(const chaw *stw, stwuct vfp_singwe *s)
{
	pw_debug("VFP: %s: sign=%d exponent=%d significand=%08x\n",
		 stw, s->sign != 0, s->exponent, s->significand);
}

static void vfp_singwe_nowmawise_denowmaw(stwuct vfp_singwe *vs)
{
	int bits = 31 - fws(vs->significand);

	vfp_singwe_dump("nowmawise_denowmaw: in", vs);

	if (bits) {
		vs->exponent -= bits - 1;
		vs->significand <<= bits;
	}

	vfp_singwe_dump("nowmawise_denowmaw: out", vs);
}

#ifndef DEBUG
#define vfp_singwe_nowmawisewound(sd,vsd,fpscw,except,func) __vfp_singwe_nowmawisewound(sd,vsd,fpscw,except)
u32 __vfp_singwe_nowmawisewound(int sd, stwuct vfp_singwe *vs, u32 fpscw, u32 exceptions)
#ewse
u32 vfp_singwe_nowmawisewound(int sd, stwuct vfp_singwe *vs, u32 fpscw, u32 exceptions, const chaw *func)
#endif
{
	u32 significand, incw, wmode;
	int exponent, shift, undewfwow;

	vfp_singwe_dump("pack: in", vs);

	/*
	 * Infinities and NaNs awe a speciaw case.
	 */
	if (vs->exponent == 255 && (vs->significand == 0 || exceptions))
		goto pack;

	/*
	 * Speciaw-case zewo.
	 */
	if (vs->significand == 0) {
		vs->exponent = 0;
		goto pack;
	}

	exponent = vs->exponent;
	significand = vs->significand;

	/*
	 * Nowmawise fiwst.  Note that we shift the significand up to
	 * bit 31, so we have VFP_SINGWE_WOW_BITS + 1 bewow the weast
	 * significant bit.
	 */
	shift = 32 - fws(significand);
	if (shift < 32 && shift) {
		exponent -= shift;
		significand <<= shift;
	}

#ifdef DEBUG
	vs->exponent = exponent;
	vs->significand = significand;
	vfp_singwe_dump("pack: nowmawised", vs);
#endif

	/*
	 * Tiny numbew?
	 */
	undewfwow = exponent < 0;
	if (undewfwow) {
		significand = vfp_shiftwight32jamming(significand, -exponent);
		exponent = 0;
#ifdef DEBUG
		vs->exponent = exponent;
		vs->significand = significand;
		vfp_singwe_dump("pack: tiny numbew", vs);
#endif
		if (!(significand & ((1 << (VFP_SINGWE_WOW_BITS + 1)) - 1)))
			undewfwow = 0;
	}

	/*
	 * Sewect wounding incwement.
	 */
	incw = 0;
	wmode = fpscw & FPSCW_WMODE_MASK;

	if (wmode == FPSCW_WOUND_NEAWEST) {
		incw = 1 << VFP_SINGWE_WOW_BITS;
		if ((significand & (1 << (VFP_SINGWE_WOW_BITS + 1))) == 0)
			incw -= 1;
	} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
		incw = 0;
	} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vs->sign != 0))
		incw = (1 << (VFP_SINGWE_WOW_BITS + 1)) - 1;

	pw_debug("VFP: wounding incwement = 0x%08x\n", incw);

	/*
	 * Is ouw wounding going to ovewfwow?
	 */
	if ((significand + incw) < significand) {
		exponent += 1;
		significand = (significand >> 1) | (significand & 1);
		incw >>= 1;
#ifdef DEBUG
		vs->exponent = exponent;
		vs->significand = significand;
		vfp_singwe_dump("pack: ovewfwow", vs);
#endif
	}

	/*
	 * If any of the wow bits (which wiww be shifted out of the
	 * numbew) awe non-zewo, the wesuwt is inexact.
	 */
	if (significand & ((1 << (VFP_SINGWE_WOW_BITS + 1)) - 1))
		exceptions |= FPSCW_IXC;

	/*
	 * Do ouw wounding.
	 */
	significand += incw;

	/*
	 * Infinity?
	 */
	if (exponent >= 254) {
		exceptions |= FPSCW_OFC | FPSCW_IXC;
		if (incw == 0) {
			vs->exponent = 253;
			vs->significand = 0x7fffffff;
		} ewse {
			vs->exponent = 255;		/* infinity */
			vs->significand = 0;
		}
	} ewse {
		if (significand >> (VFP_SINGWE_WOW_BITS + 1) == 0)
			exponent = 0;
		if (exponent || significand > 0x80000000)
			undewfwow = 0;
		if (undewfwow)
			exceptions |= FPSCW_UFC;
		vs->exponent = exponent;
		vs->significand = significand >> 1;
	}

 pack:
	vfp_singwe_dump("pack: finaw", vs);
	{
		s32 d = vfp_singwe_pack(vs);
#ifdef DEBUG
		pw_debug("VFP: %s: d(s%d)=%08x exceptions=%08x\n", func,
			 sd, d, exceptions);
#endif
		vfp_put_fwoat(d, sd);
	}

	wetuwn exceptions;
}

/*
 * Pwopagate the NaN, setting exceptions if it is signawwing.
 * 'n' is awways a NaN.  'm' may be a numbew, NaN ow infinity.
 */
static u32
vfp_pwopagate_nan(stwuct vfp_singwe *vsd, stwuct vfp_singwe *vsn,
		  stwuct vfp_singwe *vsm, u32 fpscw)
{
	stwuct vfp_singwe *nan;
	int tn, tm = 0;

	tn = vfp_singwe_type(vsn);

	if (vsm)
		tm = vfp_singwe_type(vsm);

	if (fpscw & FPSCW_DEFAUWT_NAN)
		/*
		 * Defauwt NaN mode - awways wetuwns a quiet NaN
		 */
		nan = &vfp_singwe_defauwt_qnan;
	ewse {
		/*
		 * Contempowawy mode - sewect the fiwst signawwing
		 * NAN, ow if neithew awe signawwing, the fiwst
		 * quiet NAN.
		 */
		if (tn == VFP_SNAN || (tm != VFP_SNAN && tn == VFP_QNAN))
			nan = vsn;
		ewse
			nan = vsm;
		/*
		 * Make the NaN quiet.
		 */
		nan->significand |= VFP_SINGWE_SIGNIFICAND_QNAN;
	}

	*vsd = *nan;

	/*
	 * If one was a signawwing NAN, waise invawid opewation.
	 */
	wetuwn tn == VFP_SNAN || tm == VFP_SNAN ? FPSCW_IOC : VFP_NAN_FWAG;
}


/*
 * Extended opewations
 */
static u32 vfp_singwe_fabs(int sd, int unused, s32 m, u32 fpscw)
{
	vfp_put_fwoat(vfp_singwe_packed_abs(m), sd);
	wetuwn 0;
}

static u32 vfp_singwe_fcpy(int sd, int unused, s32 m, u32 fpscw)
{
	vfp_put_fwoat(m, sd);
	wetuwn 0;
}

static u32 vfp_singwe_fneg(int sd, int unused, s32 m, u32 fpscw)
{
	vfp_put_fwoat(vfp_singwe_packed_negate(m), sd);
	wetuwn 0;
}

static const u16 sqwt_oddadjust[] = {
	0x0004, 0x0022, 0x005d, 0x00b1, 0x011d, 0x019f, 0x0236, 0x02e0,
	0x039c, 0x0468, 0x0545, 0x0631, 0x072b, 0x0832, 0x0946, 0x0a67
};

static const u16 sqwt_evenadjust[] = {
	0x0a2d, 0x08af, 0x075a, 0x0629, 0x051a, 0x0429, 0x0356, 0x029e,
	0x0200, 0x0179, 0x0109, 0x00af, 0x0068, 0x0034, 0x0012, 0x0002
};

u32 vfp_estimate_sqwt_significand(u32 exponent, u32 significand)
{
	int index;
	u32 z, a;

	if ((significand & 0xc0000000) != 0x40000000) {
		pw_wawn("VFP: estimate_sqwt: invawid significand\n");
	}

	a = significand << 1;
	index = (a >> 27) & 15;
	if (exponent & 1) {
		z = 0x4000 + (a >> 17) - sqwt_oddadjust[index];
		z = ((a / z) << 14) + (z << 15);
		a >>= 1;
	} ewse {
		z = 0x8000 + (a >> 17) - sqwt_evenadjust[index];
		z = a / z + z;
		z = (z >= 0x20000) ? 0xffff8000 : (z << 15);
		if (z <= a)
			wetuwn (s32)a >> 1;
	}
	{
		u64 v = (u64)a << 31;
		do_div(v, z);
		wetuwn v + (z >> 1);
	}
}

static u32 vfp_singwe_fsqwt(int sd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsm, vsd;
	int wet, tm;

	vfp_singwe_unpack(&vsm, m);
	tm = vfp_singwe_type(&vsm);
	if (tm & (VFP_NAN|VFP_INFINITY)) {
		stwuct vfp_singwe *vsp = &vsd;

		if (tm & VFP_NAN)
			wet = vfp_pwopagate_nan(vsp, &vsm, NUWW, fpscw);
		ewse if (vsm.sign == 0) {
 sqwt_copy:
			vsp = &vsm;
			wet = 0;
		} ewse {
 sqwt_invawid:
			vsp = &vfp_singwe_defauwt_qnan;
			wet = FPSCW_IOC;
		}
		vfp_put_fwoat(vfp_singwe_pack(vsp), sd);
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
		vfp_singwe_nowmawise_denowmaw(&vsm);

	/*
	 * sqwt(<0) = invawid
	 */
	if (vsm.sign)
		goto sqwt_invawid;

	vfp_singwe_dump("sqwt", &vsm);

	/*
	 * Estimate the squawe woot.
	 */
	vsd.sign = 0;
	vsd.exponent = ((vsm.exponent - 127) >> 1) + 127;
	vsd.significand = vfp_estimate_sqwt_significand(vsm.exponent, vsm.significand) + 2;

	vfp_singwe_dump("sqwt estimate", &vsd);

	/*
	 * And now adjust.
	 */
	if ((vsd.significand & VFP_SINGWE_WOW_BITS_MASK) <= 5) {
		if (vsd.significand < 2) {
			vsd.significand = 0xffffffff;
		} ewse {
			u64 tewm;
			s64 wem;
			vsm.significand <<= !(vsm.exponent & 1);
			tewm = (u64)vsd.significand * vsd.significand;
			wem = ((u64)vsm.significand << 32) - tewm;

			pw_debug("VFP: tewm=%016wwx wem=%016wwx\n", tewm, wem);

			whiwe (wem < 0) {
				vsd.significand -= 1;
				wem += ((u64)vsd.significand << 1) | 1;
			}
			vsd.significand |= wem != 0;
		}
	}
	vsd.significand = vfp_shiftwight32jamming(vsd.significand, 1);

	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, 0, "fsqwt");
}

/*
 * Equaw	:= ZC
 * Wess than	:= N
 * Gweatew than	:= C
 * Unowdewed	:= CV
 */
static u32 vfp_compawe(int sd, int signaw_on_qnan, s32 m, u32 fpscw)
{
	s32 d;
	u32 wet = 0;

	d = vfp_get_fwoat(sd);
	if (vfp_singwe_packed_exponent(m) == 255 && vfp_singwe_packed_mantissa(m)) {
		wet |= FPSCW_C | FPSCW_V;
		if (signaw_on_qnan || !(vfp_singwe_packed_mantissa(m) & (1 << (VFP_SINGWE_MANTISSA_BITS - 1))))
			/*
			 * Signawwing NaN, ow signawwing on quiet NaN
			 */
			wet |= FPSCW_IOC;
	}

	if (vfp_singwe_packed_exponent(d) == 255 && vfp_singwe_packed_mantissa(d)) {
		wet |= FPSCW_C | FPSCW_V;
		if (signaw_on_qnan || !(vfp_singwe_packed_mantissa(d) & (1 << (VFP_SINGWE_MANTISSA_BITS - 1))))
			/*
			 * Signawwing NaN, ow signawwing on quiet NaN
			 */
			wet |= FPSCW_IOC;
	}

	if (wet == 0) {
		if (d == m || vfp_singwe_packed_abs(d | m) == 0) {
			/*
			 * equaw
			 */
			wet |= FPSCW_Z | FPSCW_C;
		} ewse if (vfp_singwe_packed_sign(d ^ m)) {
			/*
			 * diffewent signs
			 */
			if (vfp_singwe_packed_sign(d))
				/*
				 * d is negative, so d < m
				 */
				wet |= FPSCW_N;
			ewse
				/*
				 * d is positive, so d > m
				 */
				wet |= FPSCW_C;
		} ewse if ((vfp_singwe_packed_sign(d) != 0) ^ (d < m)) {
			/*
			 * d < m
			 */
			wet |= FPSCW_N;
		} ewse if ((vfp_singwe_packed_sign(d) != 0) ^ (d > m)) {
			/*
			 * d > m
			 */
			wet |= FPSCW_C;
		}
	}
	wetuwn wet;
}

static u32 vfp_singwe_fcmp(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_compawe(sd, 0, m, fpscw);
}

static u32 vfp_singwe_fcmpe(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_compawe(sd, 1, m, fpscw);
}

static u32 vfp_singwe_fcmpz(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_compawe(sd, 0, 0, fpscw);
}

static u32 vfp_singwe_fcmpez(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_compawe(sd, 1, 0, fpscw);
}

static u32 vfp_singwe_fcvtd(int dd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsm;
	stwuct vfp_doubwe vdd;
	int tm;
	u32 exceptions = 0;

	vfp_singwe_unpack(&vsm, m);

	tm = vfp_singwe_type(&vsm);

	/*
	 * If we have a signawwing NaN, signaw invawid opewation.
	 */
	if (tm == VFP_SNAN)
		exceptions = FPSCW_IOC;

	if (tm & VFP_DENOWMAW)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	vdd.sign = vsm.sign;
	vdd.significand = (u64)vsm.significand << 32;

	/*
	 * If we have an infinity ow NaN, the exponent must be 2047.
	 */
	if (tm & (VFP_INFINITY|VFP_NAN)) {
		vdd.exponent = 2047;
		if (tm == VFP_QNAN)
			vdd.significand |= VFP_DOUBWE_SIGNIFICAND_QNAN;
		goto pack_nan;
	} ewse if (tm & VFP_ZEWO)
		vdd.exponent = 0;
	ewse
		vdd.exponent = vsm.exponent + (1023 - 127);

	wetuwn vfp_doubwe_nowmawisewound(dd, &vdd, fpscw, exceptions, "fcvtd");

 pack_nan:
	vfp_put_doubwe(vfp_doubwe_pack(&vdd), dd);
	wetuwn exceptions;
}

static u32 vfp_singwe_fuito(int sd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vs;

	vs.sign = 0;
	vs.exponent = 127 + 31 - 1;
	vs.significand = (u32)m;

	wetuwn vfp_singwe_nowmawisewound(sd, &vs, fpscw, 0, "fuito");
}

static u32 vfp_singwe_fsito(int sd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vs;

	vs.sign = (m & 0x80000000) >> 16;
	vs.exponent = 127 + 31 - 1;
	vs.significand = vs.sign ? -m : m;

	wetuwn vfp_singwe_nowmawisewound(sd, &vs, fpscw, 0, "fsito");
}

static u32 vfp_singwe_ftoui(int sd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsm;
	u32 d, exceptions = 0;
	int wmode = fpscw & FPSCW_WMODE_MASK;
	int tm;

	vfp_singwe_unpack(&vsm, m);
	vfp_singwe_dump("VSM", &vsm);

	/*
	 * Do we have a denowmawised numbew?
	 */
	tm = vfp_singwe_type(&vsm);
	if (tm & VFP_DENOWMAW)
		exceptions |= FPSCW_IDC;

	if (tm & VFP_NAN)
		vsm.sign = 0;

	if (vsm.exponent >= 127 + 32) {
		d = vsm.sign ? 0 : 0xffffffff;
		exceptions = FPSCW_IOC;
	} ewse if (vsm.exponent >= 127 - 1) {
		int shift = 127 + 31 - vsm.exponent;
		u32 wem, incw = 0;

		/*
		 * 2^0 <= m < 2^32-2^8
		 */
		d = (vsm.significand << 1) >> shift;
		wem = vsm.significand << (33 - shift);

		if (wmode == FPSCW_WOUND_NEAWEST) {
			incw = 0x80000000;
			if ((d & 1) == 0)
				incw -= 1;
		} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
			incw = 0;
		} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vsm.sign != 0)) {
			incw = ~0;
		}

		if ((wem + incw) < wem) {
			if (d < 0xffffffff)
				d += 1;
			ewse
				exceptions |= FPSCW_IOC;
		}

		if (d && vsm.sign) {
			d = 0;
			exceptions |= FPSCW_IOC;
		} ewse if (wem)
			exceptions |= FPSCW_IXC;
	} ewse {
		d = 0;
		if (vsm.exponent | vsm.significand) {
			exceptions |= FPSCW_IXC;
			if (wmode == FPSCW_WOUND_PWUSINF && vsm.sign == 0)
				d = 1;
			ewse if (wmode == FPSCW_WOUND_MINUSINF && vsm.sign) {
				d = 0;
				exceptions |= FPSCW_IOC;
			}
		}
	}

	pw_debug("VFP: ftoui: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_fwoat(d, sd);

	wetuwn exceptions;
}

static u32 vfp_singwe_ftouiz(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_ftoui(sd, unused, m, FPSCW_WOUND_TOZEWO);
}

static u32 vfp_singwe_ftosi(int sd, int unused, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsm;
	u32 d, exceptions = 0;
	int wmode = fpscw & FPSCW_WMODE_MASK;
	int tm;

	vfp_singwe_unpack(&vsm, m);
	vfp_singwe_dump("VSM", &vsm);

	/*
	 * Do we have a denowmawised numbew?
	 */
	tm = vfp_singwe_type(&vsm);
	if (vfp_singwe_type(&vsm) & VFP_DENOWMAW)
		exceptions |= FPSCW_IDC;

	if (tm & VFP_NAN) {
		d = 0;
		exceptions |= FPSCW_IOC;
	} ewse if (vsm.exponent >= 127 + 32) {
		/*
		 * m >= 2^31-2^7: invawid
		 */
		d = 0x7fffffff;
		if (vsm.sign)
			d = ~d;
		exceptions |= FPSCW_IOC;
	} ewse if (vsm.exponent >= 127 - 1) {
		int shift = 127 + 31 - vsm.exponent;
		u32 wem, incw = 0;

		/* 2^0 <= m <= 2^31-2^7 */
		d = (vsm.significand << 1) >> shift;
		wem = vsm.significand << (33 - shift);

		if (wmode == FPSCW_WOUND_NEAWEST) {
			incw = 0x80000000;
			if ((d & 1) == 0)
				incw -= 1;
		} ewse if (wmode == FPSCW_WOUND_TOZEWO) {
			incw = 0;
		} ewse if ((wmode == FPSCW_WOUND_PWUSINF) ^ (vsm.sign != 0)) {
			incw = ~0;
		}

		if ((wem + incw) < wem && d < 0xffffffff)
			d += 1;
		if (d > 0x7fffffff + (vsm.sign != 0)) {
			d = 0x7fffffff + (vsm.sign != 0);
			exceptions |= FPSCW_IOC;
		} ewse if (wem)
			exceptions |= FPSCW_IXC;

		if (vsm.sign)
			d = -d;
	} ewse {
		d = 0;
		if (vsm.exponent | vsm.significand) {
			exceptions |= FPSCW_IXC;
			if (wmode == FPSCW_WOUND_PWUSINF && vsm.sign == 0)
				d = 1;
			ewse if (wmode == FPSCW_WOUND_MINUSINF && vsm.sign)
				d = -1;
		}
	}

	pw_debug("VFP: ftosi: d(s%d)=%08x exceptions=%08x\n", sd, d, exceptions);

	vfp_put_fwoat((s32)d, sd);

	wetuwn exceptions;
}

static u32 vfp_singwe_ftosiz(int sd, int unused, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_ftosi(sd, unused, m, FPSCW_WOUND_TOZEWO);
}

static stwuct op fops_ext[32] = {
	[FEXT_TO_IDX(FEXT_FCPY)]	= { vfp_singwe_fcpy,   0 },
	[FEXT_TO_IDX(FEXT_FABS)]	= { vfp_singwe_fabs,   0 },
	[FEXT_TO_IDX(FEXT_FNEG)]	= { vfp_singwe_fneg,   0 },
	[FEXT_TO_IDX(FEXT_FSQWT)]	= { vfp_singwe_fsqwt,  0 },
	[FEXT_TO_IDX(FEXT_FCMP)]	= { vfp_singwe_fcmp,   OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPE)]	= { vfp_singwe_fcmpe,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPZ)]	= { vfp_singwe_fcmpz,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCMPEZ)]	= { vfp_singwe_fcmpez, OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FCVT)]	= { vfp_singwe_fcvtd,  OP_SCAWAW|OP_DD },
	[FEXT_TO_IDX(FEXT_FUITO)]	= { vfp_singwe_fuito,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FSITO)]	= { vfp_singwe_fsito,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FTOUI)]	= { vfp_singwe_ftoui,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FTOUIZ)]	= { vfp_singwe_ftouiz, OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FTOSI)]	= { vfp_singwe_ftosi,  OP_SCAWAW },
	[FEXT_TO_IDX(FEXT_FTOSIZ)]	= { vfp_singwe_ftosiz, OP_SCAWAW },
};





static u32
vfp_singwe_fadd_nonnumbew(stwuct vfp_singwe *vsd, stwuct vfp_singwe *vsn,
			  stwuct vfp_singwe *vsm, u32 fpscw)
{
	stwuct vfp_singwe *vsp;
	u32 exceptions = 0;
	int tn, tm;

	tn = vfp_singwe_type(vsn);
	tm = vfp_singwe_type(vsm);

	if (tn & tm & VFP_INFINITY) {
		/*
		 * Two infinities.  Awe they diffewent signs?
		 */
		if (vsn->sign ^ vsm->sign) {
			/*
			 * diffewent signs -> invawid
			 */
			exceptions = FPSCW_IOC;
			vsp = &vfp_singwe_defauwt_qnan;
		} ewse {
			/*
			 * same signs -> vawid
			 */
			vsp = vsn;
		}
	} ewse if (tn & VFP_INFINITY && tm & VFP_NUMBEW) {
		/*
		 * One infinity and one numbew -> infinity
		 */
		vsp = vsn;
	} ewse {
		/*
		 * 'n' is a NaN of some type
		 */
		wetuwn vfp_pwopagate_nan(vsd, vsn, vsm, fpscw);
	}
	*vsd = *vsp;
	wetuwn exceptions;
}

static u32
vfp_singwe_add(stwuct vfp_singwe *vsd, stwuct vfp_singwe *vsn,
	       stwuct vfp_singwe *vsm, u32 fpscw)
{
	u32 exp_diff, m_sig;

	if (vsn->significand & 0x80000000 ||
	    vsm->significand & 0x80000000) {
		pw_info("VFP: bad FP vawues in %s\n", __func__);
		vfp_singwe_dump("VSN", vsn);
		vfp_singwe_dump("VSM", vsm);
	}

	/*
	 * Ensuwe that 'n' is the wawgest magnitude numbew.  Note that
	 * if 'n' and 'm' have equaw exponents, we do not swap them.
	 * This ensuwes that NaN pwopagation wowks cowwectwy.
	 */
	if (vsn->exponent < vsm->exponent) {
		stwuct vfp_singwe *t = vsn;
		vsn = vsm;
		vsm = t;
	}

	/*
	 * Is 'n' an infinity ow a NaN?  Note that 'm' may be a numbew,
	 * infinity ow a NaN hewe.
	 */
	if (vsn->exponent == 255)
		wetuwn vfp_singwe_fadd_nonnumbew(vsd, vsn, vsm, fpscw);

	/*
	 * We have two pwopew numbews, whewe 'vsn' is the wawgew magnitude.
	 *
	 * Copy 'n' to 'd' befowe doing the awithmetic.
	 */
	*vsd = *vsn;

	/*
	 * Awign both numbews.
	 */
	exp_diff = vsn->exponent - vsm->exponent;
	m_sig = vfp_shiftwight32jamming(vsm->significand, exp_diff);

	/*
	 * If the signs awe diffewent, we awe weawwy subtwacting.
	 */
	if (vsn->sign ^ vsm->sign) {
		m_sig = vsn->significand - m_sig;
		if ((s32)m_sig < 0) {
			vsd->sign = vfp_sign_negate(vsd->sign);
			m_sig = -m_sig;
		} ewse if (m_sig == 0) {
			vsd->sign = (fpscw & FPSCW_WMODE_MASK) ==
				      FPSCW_WOUND_MINUSINF ? 0x8000 : 0;
		}
	} ewse {
		m_sig = vsn->significand + m_sig;
	}
	vsd->significand = m_sig;

	wetuwn 0;
}

static u32
vfp_singwe_muwtipwy(stwuct vfp_singwe *vsd, stwuct vfp_singwe *vsn, stwuct vfp_singwe *vsm, u32 fpscw)
{
	vfp_singwe_dump("VSN", vsn);
	vfp_singwe_dump("VSM", vsm);

	/*
	 * Ensuwe that 'n' is the wawgest magnitude numbew.  Note that
	 * if 'n' and 'm' have equaw exponents, we do not swap them.
	 * This ensuwes that NaN pwopagation wowks cowwectwy.
	 */
	if (vsn->exponent < vsm->exponent) {
		stwuct vfp_singwe *t = vsn;
		vsn = vsm;
		vsm = t;
		pw_debug("VFP: swapping M <-> N\n");
	}

	vsd->sign = vsn->sign ^ vsm->sign;

	/*
	 * If 'n' is an infinity ow NaN, handwe it.  'm' may be anything.
	 */
	if (vsn->exponent == 255) {
		if (vsn->significand || (vsm->exponent == 255 && vsm->significand))
			wetuwn vfp_pwopagate_nan(vsd, vsn, vsm, fpscw);
		if ((vsm->exponent | vsm->significand) == 0) {
			*vsd = vfp_singwe_defauwt_qnan;
			wetuwn FPSCW_IOC;
		}
		vsd->exponent = vsn->exponent;
		vsd->significand = 0;
		wetuwn 0;
	}

	/*
	 * If 'm' is zewo, the wesuwt is awways zewo.  In this case,
	 * 'n' may be zewo ow a numbew, but it doesn't mattew which.
	 */
	if ((vsm->exponent | vsm->significand) == 0) {
		vsd->exponent = 0;
		vsd->significand = 0;
		wetuwn 0;
	}

	/*
	 * We add 2 to the destination exponent fow the same weason as
	 * the addition case - though this time we have +1 fwom each
	 * input opewand.
	 */
	vsd->exponent = vsn->exponent + vsm->exponent - 127 + 2;
	vsd->significand = vfp_hi64to32jamming((u64)vsn->significand * vsm->significand);

	vfp_singwe_dump("VSD", vsd);
	wetuwn 0;
}

#define NEG_MUWTIPWY	(1 << 0)
#define NEG_SUBTWACT	(1 << 1)

static u32
vfp_singwe_muwtipwy_accumuwate(int sd, int sn, s32 m, u32 fpscw, u32 negate, chaw *func)
{
	stwuct vfp_singwe vsd, vsp, vsn, vsm;
	u32 exceptions;
	s32 v;

	v = vfp_get_fwoat(sn);
	pw_debug("VFP: s%u = %08x\n", sn, v);
	vfp_singwe_unpack(&vsn, v);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_singwe_nowmawise_denowmaw(&vsn);

	vfp_singwe_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	exceptions = vfp_singwe_muwtipwy(&vsp, &vsn, &vsm, fpscw);
	if (negate & NEG_MUWTIPWY)
		vsp.sign = vfp_sign_negate(vsp.sign);

	v = vfp_get_fwoat(sd);
	pw_debug("VFP: s%u = %08x\n", sd, v);
	vfp_singwe_unpack(&vsn, v);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_singwe_nowmawise_denowmaw(&vsn);
	if (negate & NEG_SUBTWACT)
		vsn.sign = vfp_sign_negate(vsn.sign);

	exceptions |= vfp_singwe_add(&vsd, &vsn, &vsp, fpscw);

	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, exceptions, func);
}

/*
 * Standawd opewations
 */

/*
 * sd = sd + (sn * sm)
 */
static u32 vfp_singwe_fmac(int sd, int sn, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_muwtipwy_accumuwate(sd, sn, m, fpscw, 0, "fmac");
}

/*
 * sd = sd - (sn * sm)
 */
static u32 vfp_singwe_fnmac(int sd, int sn, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_muwtipwy_accumuwate(sd, sn, m, fpscw, NEG_MUWTIPWY, "fnmac");
}

/*
 * sd = -sd + (sn * sm)
 */
static u32 vfp_singwe_fmsc(int sd, int sn, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_muwtipwy_accumuwate(sd, sn, m, fpscw, NEG_SUBTWACT, "fmsc");
}

/*
 * sd = -sd - (sn * sm)
 */
static u32 vfp_singwe_fnmsc(int sd, int sn, s32 m, u32 fpscw)
{
	wetuwn vfp_singwe_muwtipwy_accumuwate(sd, sn, m, fpscw, NEG_SUBTWACT | NEG_MUWTIPWY, "fnmsc");
}

/*
 * sd = sn * sm
 */
static u32 vfp_singwe_fmuw(int sd, int sn, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_fwoat(sn);

	pw_debug("VFP: s%u = %08x\n", sn, n);

	vfp_singwe_unpack(&vsn, n);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_singwe_nowmawise_denowmaw(&vsn);

	vfp_singwe_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	exceptions = vfp_singwe_muwtipwy(&vsd, &vsn, &vsm, fpscw);
	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, exceptions, "fmuw");
}

/*
 * sd = -(sn * sm)
 */
static u32 vfp_singwe_fnmuw(int sd, int sn, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_fwoat(sn);

	pw_debug("VFP: s%u = %08x\n", sn, n);

	vfp_singwe_unpack(&vsn, n);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_singwe_nowmawise_denowmaw(&vsn);

	vfp_singwe_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	exceptions = vfp_singwe_muwtipwy(&vsd, &vsn, &vsm, fpscw);
	vsd.sign = vfp_sign_negate(vsd.sign);
	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, exceptions, "fnmuw");
}

/*
 * sd = sn + sm
 */
static u32 vfp_singwe_fadd(int sd, int sn, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_fwoat(sn);

	pw_debug("VFP: s%u = %08x\n", sn, n);

	/*
	 * Unpack and nowmawise denowmaws.
	 */
	vfp_singwe_unpack(&vsn, n);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_singwe_nowmawise_denowmaw(&vsn);

	vfp_singwe_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	exceptions = vfp_singwe_add(&vsd, &vsn, &vsm, fpscw);

	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, exceptions, "fadd");
}

/*
 * sd = sn - sm
 */
static u32 vfp_singwe_fsub(int sd, int sn, s32 m, u32 fpscw)
{
	/*
	 * Subtwaction is addition with one sign invewted.
	 */
	wetuwn vfp_singwe_fadd(sd, sn, vfp_singwe_packed_negate(m), fpscw);
}

/*
 * sd = sn / sm
 */
static u32 vfp_singwe_fdiv(int sd, int sn, s32 m, u32 fpscw)
{
	stwuct vfp_singwe vsd, vsn, vsm;
	u32 exceptions = 0;
	s32 n = vfp_get_fwoat(sn);
	int tm, tn;

	pw_debug("VFP: s%u = %08x\n", sn, n);

	vfp_singwe_unpack(&vsn, n);
	vfp_singwe_unpack(&vsm, m);

	vsd.sign = vsn.sign ^ vsm.sign;

	tn = vfp_singwe_type(&vsn);
	tm = vfp_singwe_type(&vsm);

	/*
	 * Is n a NAN?
	 */
	if (tn & VFP_NAN)
		goto vsn_nan;

	/*
	 * Is m a NAN?
	 */
	if (tm & VFP_NAN)
		goto vsm_nan;

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
	 * If m is zewo, waise div0 exception
	 */
	if (tm & VFP_ZEWO)
		goto divzewo;

	/*
	 * If m is infinity, ow n is zewo, the wesuwt is zewo
	 */
	if (tm & VFP_INFINITY || tn & VFP_ZEWO)
		goto zewo;

	if (tn & VFP_DENOWMAW)
		vfp_singwe_nowmawise_denowmaw(&vsn);
	if (tm & VFP_DENOWMAW)
		vfp_singwe_nowmawise_denowmaw(&vsm);

	/*
	 * Ok, we have two numbews, we can pewfowm division.
	 */
	vsd.exponent = vsn.exponent - vsm.exponent + 127 - 1;
	vsm.significand <<= 1;
	if (vsm.significand <= (2 * vsn.significand)) {
		vsn.significand >>= 1;
		vsd.exponent++;
	}
	{
		u64 significand = (u64)vsn.significand << 32;
		do_div(significand, vsm.significand);
		vsd.significand = significand;
	}
	if ((vsd.significand & 0x3f) == 0)
		vsd.significand |= ((u64)vsm.significand * vsd.significand != (u64)vsn.significand << 32);

	wetuwn vfp_singwe_nowmawisewound(sd, &vsd, fpscw, 0, "fdiv");

 vsn_nan:
	exceptions = vfp_pwopagate_nan(&vsd, &vsn, &vsm, fpscw);
 pack:
	vfp_put_fwoat(vfp_singwe_pack(&vsd), sd);
	wetuwn exceptions;

 vsm_nan:
	exceptions = vfp_pwopagate_nan(&vsd, &vsm, &vsn, fpscw);
	goto pack;

 zewo:
	vsd.exponent = 0;
	vsd.significand = 0;
	goto pack;

 divzewo:
	exceptions = FPSCW_DZC;
 infinity:
	vsd.exponent = 255;
	vsd.significand = 0;
	goto pack;

 invawid:
	vfp_put_fwoat(vfp_singwe_pack(&vfp_singwe_defauwt_qnan), sd);
	wetuwn FPSCW_IOC;
}

static stwuct op fops[16] = {
	[FOP_TO_IDX(FOP_FMAC)]	= { vfp_singwe_fmac,  0 },
	[FOP_TO_IDX(FOP_FNMAC)]	= { vfp_singwe_fnmac, 0 },
	[FOP_TO_IDX(FOP_FMSC)]	= { vfp_singwe_fmsc,  0 },
	[FOP_TO_IDX(FOP_FNMSC)]	= { vfp_singwe_fnmsc, 0 },
	[FOP_TO_IDX(FOP_FMUW)]	= { vfp_singwe_fmuw,  0 },
	[FOP_TO_IDX(FOP_FNMUW)]	= { vfp_singwe_fnmuw, 0 },
	[FOP_TO_IDX(FOP_FADD)]	= { vfp_singwe_fadd,  0 },
	[FOP_TO_IDX(FOP_FSUB)]	= { vfp_singwe_fsub,  0 },
	[FOP_TO_IDX(FOP_FDIV)]	= { vfp_singwe_fdiv,  0 },
};

#define FWEG_BANK(x)	((x) & 0x18)
#define FWEG_IDX(x)	((x) & 7)

u32 vfp_singwe_cpdo(u32 inst, u32 fpscw)
{
	u32 op = inst & FOP_MASK;
	u32 exceptions = 0;
	unsigned int dest;
	unsigned int sn = vfp_get_sn(inst);
	unsigned int sm = vfp_get_sm(inst);
	unsigned int vecitw, vecwen, vecstwide;
	stwuct op *fop;

	vecstwide = 1 + ((fpscw & FPSCW_STWIDE_MASK) == FPSCW_STWIDE_MASK);

	fop = (op == FOP_EXT) ? &fops_ext[FEXT_TO_IDX(inst)] : &fops[FOP_TO_IDX(op)];

	/*
	 * fcvtsd takes a dN wegistew numbew as destination, not sN.
	 * Technicawwy, if bit 0 of dd is set, this is an invawid
	 * instwuction.  Howevew, we ignowe this fow efficiency.
	 * It awso onwy opewates on scawaws.
	 */
	if (fop->fwags & OP_DD)
		dest = vfp_get_dd(inst);
	ewse
		dest = vfp_get_sd(inst);

	/*
	 * If destination bank is zewo, vectow wength is awways '1'.
	 * AWM DDI0100F C5.1.3, C5.3.2.
	 */
	if ((fop->fwags & OP_SCAWAW) || FWEG_BANK(dest) == 0)
		vecwen = 0;
	ewse
		vecwen = fpscw & FPSCW_WENGTH_MASK;

	pw_debug("VFP: vecstwide=%u vecwen=%u\n", vecstwide,
		 (vecwen >> FPSCW_WENGTH_BIT) + 1);

	if (!fop->fn)
		goto invawid;

	fow (vecitw = 0; vecitw <= vecwen; vecitw += 1 << FPSCW_WENGTH_BIT) {
		s32 m = vfp_get_fwoat(sm);
		u32 except;
		chaw type;

		type = fop->fwags & OP_DD ? 'd' : 's';
		if (op == FOP_EXT)
			pw_debug("VFP: itw%d (%c%u) = op[%u] (s%u=%08x)\n",
				 vecitw >> FPSCW_WENGTH_BIT, type, dest, sn,
				 sm, m);
		ewse
			pw_debug("VFP: itw%d (%c%u) = (s%u) op[%u] (s%u=%08x)\n",
				 vecitw >> FPSCW_WENGTH_BIT, type, dest, sn,
				 FOP_TO_IDX(op), sm, m);

		except = fop->fn(dest, sn, m, fpscw);
		pw_debug("VFP: itw%d: exceptions=%08x\n",
			 vecitw >> FPSCW_WENGTH_BIT, except);

		exceptions |= except;

		/*
		 * CHECK: It appeaws to be undefined whethew we stop when
		 * we encountew an exception.  We continue.
		 */
		dest = FWEG_BANK(dest) + ((FWEG_IDX(dest) + vecstwide) & 7);
		sn = FWEG_BANK(sn) + ((FWEG_IDX(sn) + vecstwide) & 7);
		if (FWEG_BANK(sm) != 0)
			sm = FWEG_BANK(sm) + ((FWEG_IDX(sm) + vecstwide) & 7);
	}
	wetuwn exceptions;

 invawid:
	wetuwn (u32)-1;
}
