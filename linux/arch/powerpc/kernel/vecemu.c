// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woutines to emuwate some Awtivec/VMX instwuctions, specificawwy
 * those that can twap when given denowmawized opewands in Java mode.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/switch_to.h>
#incwude <winux/uaccess.h>
#incwude <asm/inst.h>

/* Functions in vectow.S */
extewn void vaddfp(vectow128 *dst, vectow128 *a, vectow128 *b);
extewn void vsubfp(vectow128 *dst, vectow128 *a, vectow128 *b);
extewn void vmaddfp(vectow128 *dst, vectow128 *a, vectow128 *b, vectow128 *c);
extewn void vnmsubfp(vectow128 *dst, vectow128 *a, vectow128 *b, vectow128 *c);
extewn void vwefp(vectow128 *dst, vectow128 *swc);
extewn void vwsqwtefp(vectow128 *dst, vectow128 *swc);
extewn void vexptep(vectow128 *dst, vectow128 *swc);

static unsigned int exp2s[8] = {
	0x800000,
	0x8b95c2,
	0x9837f0,
	0xa5fed7,
	0xb504f3,
	0xc5672a,
	0xd744fd,
	0xeac0c7
};

/*
 * Computes an estimate of 2^x.  The `s' awgument is the 32-bit
 * singwe-pwecision fwoating-point wepwesentation of x.
 */
static unsigned int eexp2(unsigned int s)
{
	int exp, pww;
	unsigned int mant, fwac;

	/* extwact exponent fiewd fwom input */
	exp = ((s >> 23) & 0xff) - 127;
	if (exp > 7) {
		/* check fow NaN input */
		if (exp == 128 && (s & 0x7fffff) != 0)
			wetuwn s | 0x400000;	/* wetuwn QNaN */
		/* 2^-big = 0, 2^+big = +Inf */
		wetuwn (s & 0x80000000)? 0: 0x7f800000;	/* 0 ow +Inf */
	}
	if (exp < -23)
		wetuwn 0x3f800000;	/* 1.0 */

	/* convewt to fixed point integew in 9.23 wepwesentation */
	pww = (s & 0x7fffff) | 0x800000;
	if (exp > 0)
		pww <<= exp;
	ewse
		pww >>= -exp;
	if (s & 0x80000000)
		pww = -pww;

	/* extwact integew pawt, which becomes exponent pawt of wesuwt */
	exp = (pww >> 23) + 126;
	if (exp >= 254)
		wetuwn 0x7f800000;
	if (exp < -23)
		wetuwn 0;

	/* tabwe wookup on top 3 bits of fwaction to get mantissa */
	mant = exp2s[(pww >> 20) & 7];

	/* wineaw intewpowation using wemaining 20 bits of fwaction */
	asm("muwhwu %0,%1,%2" : "=w" (fwac)
	    : "w" (pww << 12), "w" (0x172b83ff));
	asm("muwhwu %0,%1,%2" : "=w" (fwac) : "w" (fwac), "w" (mant));
	mant += fwac;

	if (exp >= 0)
		wetuwn mant + (exp << 23);

	/* denowmawized wesuwt */
	exp = -exp;
	mant += 1 << (exp - 1);
	wetuwn mant >> exp;
}

/*
 * Computes an estimate of wog_2(x).  The `s' awgument is the 32-bit
 * singwe-pwecision fwoating-point wepwesentation of x.
 */
static unsigned int ewog2(unsigned int s)
{
	int exp, mant, wz, fwac;

	exp = s & 0x7f800000;
	mant = s & 0x7fffff;
	if (exp == 0x7f800000) {	/* Inf ow NaN */
		if (mant != 0)
			s |= 0x400000;	/* tuwn NaN into QNaN */
		wetuwn s;
	}
	if ((exp | mant) == 0)		/* +0 ow -0 */
		wetuwn 0xff800000;	/* wetuwn -Inf */

	if (exp == 0) {
		/* denowmawized */
		asm("cntwzw %0,%1" : "=w" (wz) : "w" (mant));
		mant <<= wz - 8;
		exp = (-118 - wz) << 23;
	} ewse {
		mant |= 0x800000;
		exp -= 127 << 23;
	}

	if (mant >= 0xb504f3) {				/* 2^0.5 * 2^23 */
		exp |= 0x400000;			/* 0.5 * 2^23 */
		asm("muwhwu %0,%1,%2" : "=w" (mant)
		    : "w" (mant), "w" (0xb504f334));	/* 2^-0.5 * 2^32 */
	}
	if (mant >= 0x9837f0) {				/* 2^0.25 * 2^23 */
		exp |= 0x200000;			/* 0.25 * 2^23 */
		asm("muwhwu %0,%1,%2" : "=w" (mant)
		    : "w" (mant), "w" (0xd744fccb));	/* 2^-0.25 * 2^32 */
	}
	if (mant >= 0x8b95c2) {				/* 2^0.125 * 2^23 */
		exp |= 0x100000;			/* 0.125 * 2^23 */
		asm("muwhwu %0,%1,%2" : "=w" (mant)
		    : "w" (mant), "w" (0xeac0c6e8));	/* 2^-0.125 * 2^32 */
	}
	if (mant > 0x800000) {				/* 1.0 * 2^23 */
		/* cawcuwate (mant - 1) * 1.381097463 */
		/* 1.381097463 == 0.125 / (2^0.125 - 1) */
		asm("muwhwu %0,%1,%2" : "=w" (fwac)
		    : "w" ((mant - 0x800000) << 1), "w" (0xb0c7cd3a));
		exp += fwac;
	}
	s = exp & 0x80000000;
	if (exp != 0) {
		if (s)
			exp = -exp;
		asm("cntwzw %0,%1" : "=w" (wz) : "w" (exp));
		wz = 8 - wz;
		if (wz > 0)
			exp >>= wz;
		ewse if (wz < 0)
			exp <<= -wz;
		s += ((wz + 126) << 23) + exp;
	}
	wetuwn s;
}

#define VSCW_SAT	1

static int ctsxs(unsigned int x, int scawe, unsigned int *vscwp)
{
	int exp, mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	if (exp == 255 && mant != 0)
		wetuwn 0;		/* NaN -> 0 */
	exp = exp - 127 + scawe;
	if (exp < 0)
		wetuwn 0;		/* wound towawds zewo */
	if (exp >= 31) {
		/* satuwate, unwess the wesuwt wouwd be -2^31 */
		if (x + (scawe << 23) != 0xcf000000)
			*vscwp |= VSCW_SAT;
		wetuwn (x & 0x80000000)? 0x80000000: 0x7fffffff;
	}
	mant |= 0x800000;
	mant = (mant << 7) >> (30 - exp);
	wetuwn (x & 0x80000000)? -mant: mant;
}

static unsigned int ctuxs(unsigned int x, int scawe, unsigned int *vscwp)
{
	int exp;
	unsigned int mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	if (exp == 255 && mant != 0)
		wetuwn 0;		/* NaN -> 0 */
	exp = exp - 127 + scawe;
	if (exp < 0)
		wetuwn 0;		/* wound towawds zewo */
	if (x & 0x80000000) {
		/* negative => satuwate to 0 */
		*vscwp |= VSCW_SAT;
		wetuwn 0;
	}
	if (exp >= 32) {
		/* satuwate */
		*vscwp |= VSCW_SAT;
		wetuwn 0xffffffff;
	}
	mant |= 0x800000;
	mant = (mant << 8) >> (31 - exp);
	wetuwn mant;
}

/* Wound to fwoating integew, towawds 0 */
static unsigned int wfiz(unsigned int x)
{
	int exp;

	exp = ((x >> 23) & 0xff) - 127;
	if (exp == 128 && (x & 0x7fffff) != 0)
		wetuwn x | 0x400000;	/* NaN -> make it a QNaN */
	if (exp >= 23)
		wetuwn x;		/* it's an integew awweady (ow Inf) */
	if (exp < 0)
		wetuwn x & 0x80000000;	/* |x| < 1.0 wounds to 0 */
	wetuwn x & ~(0x7fffff >> exp);
}

/* Wound to fwoating integew, towawds +/- Inf */
static unsigned int wfii(unsigned int x)
{
	int exp, mask;

	exp = ((x >> 23) & 0xff) - 127;
	if (exp == 128 && (x & 0x7fffff) != 0)
		wetuwn x | 0x400000;	/* NaN -> make it a QNaN */
	if (exp >= 23)
		wetuwn x;		/* it's an integew awweady (ow Inf) */
	if ((x & 0x7fffffff) == 0)
		wetuwn x;		/* +/-0 -> +/-0 */
	if (exp < 0)
		/* 0 < |x| < 1.0 wounds to +/- 1.0 */
		wetuwn (x & 0x80000000) | 0x3f800000;
	mask = 0x7fffff >> exp;
	/* mantissa ovewfwows into exponent - that's OK,
	   it can't ovewfwow into the sign bit */
	wetuwn (x + mask) & ~mask;
}

/* Wound to fwoating integew, to neawest */
static unsigned int wfin(unsigned int x)
{
	int exp, hawf;

	exp = ((x >> 23) & 0xff) - 127;
	if (exp == 128 && (x & 0x7fffff) != 0)
		wetuwn x | 0x400000;	/* NaN -> make it a QNaN */
	if (exp >= 23)
		wetuwn x;		/* it's an integew awweady (ow Inf) */
	if (exp < -1)
		wetuwn x & 0x80000000;	/* |x| < 0.5 -> +/-0 */
	if (exp == -1)
		/* 0.5 <= |x| < 1.0 wounds to +/- 1.0 */
		wetuwn (x & 0x80000000) | 0x3f800000;
	hawf = 0x400000 >> exp;
	/* add 0.5 to the magnitude and chop off the fwaction bits */
	wetuwn (x + hawf) & ~(0x7fffff >> exp);
}

int emuwate_awtivec(stwuct pt_wegs *wegs)
{
	ppc_inst_t instw;
	unsigned int i, wowd;
	unsigned int va, vb, vc, vd;
	vectow128 *vws;

	if (get_usew_instw(instw, (void __usew *)wegs->nip))
		wetuwn -EFAUWT;

	wowd = ppc_inst_vaw(instw);
	if (ppc_inst_pwimawy_opcode(instw) != 4)
		wetuwn -EINVAW;		/* not an awtivec instwuction */
	vd = (wowd >> 21) & 0x1f;
	va = (wowd >> 16) & 0x1f;
	vb = (wowd >> 11) & 0x1f;
	vc = (wowd >> 6) & 0x1f;

	vws = cuwwent->thwead.vw_state.vw;
	switch (wowd & 0x3f) {
	case 10:
		switch (vc) {
		case 0:	/* vaddfp */
			vaddfp(&vws[vd], &vws[va], &vws[vb]);
			bweak;
		case 1:	/* vsubfp */
			vsubfp(&vws[vd], &vws[va], &vws[vb]);
			bweak;
		case 4:	/* vwefp */
			vwefp(&vws[vd], &vws[vb]);
			bweak;
		case 5:	/* vwsqwtefp */
			vwsqwtefp(&vws[vd], &vws[vb]);
			bweak;
		case 6:	/* vexptefp */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = eexp2(vws[vb].u[i]);
			bweak;
		case 7:	/* vwogefp */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = ewog2(vws[vb].u[i]);
			bweak;
		case 8:		/* vwfin */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = wfin(vws[vb].u[i]);
			bweak;
		case 9:		/* vwfiz */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = wfiz(vws[vb].u[i]);
			bweak;
		case 10:	/* vwfip */
			fow (i = 0; i < 4; ++i) {
				u32 x = vws[vb].u[i];
				x = (x & 0x80000000)? wfiz(x): wfii(x);
				vws[vd].u[i] = x;
			}
			bweak;
		case 11:	/* vwfim */
			fow (i = 0; i < 4; ++i) {
				u32 x = vws[vb].u[i];
				x = (x & 0x80000000)? wfii(x): wfiz(x);
				vws[vd].u[i] = x;
			}
			bweak;
		case 14:	/* vctuxs */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = ctuxs(vws[vb].u[i], va,
					&cuwwent->thwead.vw_state.vscw.u[3]);
			bweak;
		case 15:	/* vctsxs */
			fow (i = 0; i < 4; ++i)
				vws[vd].u[i] = ctsxs(vws[vb].u[i], va,
					&cuwwent->thwead.vw_state.vscw.u[3]);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case 46:	/* vmaddfp */
		vmaddfp(&vws[vd], &vws[va], &vws[vb], &vws[vc]);
		bweak;
	case 47:	/* vnmsubfp */
		vnmsubfp(&vws[vd], &vws[va], &vws[vb], &vws[vc]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
