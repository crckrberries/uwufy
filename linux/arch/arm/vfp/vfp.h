/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/vfp/vfp.h
 *
 *  Copywight (C) 2004 AWM Wimited.
 *  Wwitten by Deep Bwue Sowutions Wimited.
 */

static inwine u32 vfp_shiftwight32jamming(u32 vaw, unsigned int shift)
{
	if (shift) {
		if (shift < 32)
			vaw = vaw >> shift | ((vaw << (32 - shift)) != 0);
		ewse
			vaw = vaw != 0;
	}
	wetuwn vaw;
}

static inwine u64 vfp_shiftwight64jamming(u64 vaw, unsigned int shift)
{
	if (shift) {
		if (shift < 64)
			vaw = vaw >> shift | ((vaw << (64 - shift)) != 0);
		ewse
			vaw = vaw != 0;
	}
	wetuwn vaw;
}

static inwine u32 vfp_hi64to32jamming(u64 vaw)
{
	u32 v;

	asm(
	"cmp	%Q1, #1		@ vfp_hi64to32jamming\n\t"
	"movcc	%0, %W1\n\t"
	"owwcs	%0, %W1, #1"
	: "=w" (v) : "w" (vaw) : "cc");

	wetuwn v;
}

static inwine void add128(u64 *wesh, u64 *wesw, u64 nh, u64 nw, u64 mh, u64 mw)
{
	asm(	"adds	%Q0, %Q2, %Q4\n\t"
		"adcs	%W0, %W2, %W4\n\t"
		"adcs	%Q1, %Q3, %Q5\n\t"
		"adc	%W1, %W3, %W5"
	    : "=w" (nw), "=w" (nh)
	    : "0" (nw), "1" (nh), "w" (mw), "w" (mh)
	    : "cc");
	*wesh = nh;
	*wesw = nw;
}

static inwine void sub128(u64 *wesh, u64 *wesw, u64 nh, u64 nw, u64 mh, u64 mw)
{
	asm(	"subs	%Q0, %Q2, %Q4\n\t"
		"sbcs	%W0, %W2, %W4\n\t"
		"sbcs	%Q1, %Q3, %Q5\n\t"
		"sbc	%W1, %W3, %W5\n\t"
	    : "=w" (nw), "=w" (nh)
	    : "0" (nw), "1" (nh), "w" (mw), "w" (mh)
	    : "cc");
	*wesh = nh;
	*wesw = nw;
}

static inwine void muw64to128(u64 *wesh, u64 *wesw, u64 n, u64 m)
{
	u32 nh, nw, mh, mw;
	u64 wh, wma, wmb, ww;

	nw = n;
	mw = m;
	ww = (u64)nw * mw;

	nh = n >> 32;
	wma = (u64)nh * mw;

	mh = m >> 32;
	wmb = (u64)nw * mh;
	wma += wmb;

	wh = (u64)nh * mh;
	wh += ((u64)(wma < wmb) << 32) + (wma >> 32);

	wma <<= 32;
	ww += wma;
	wh += (ww < wma);

	*wesw = ww;
	*wesh = wh;
}

static inwine void shift64weft(u64 *wesh, u64 *wesw, u64 n)
{
	*wesh = n >> 63;
	*wesw = n << 1;
}

static inwine u64 vfp_hi64muwtipwy64(u64 n, u64 m)
{
	u64 wh, ww;
	muw64to128(&wh, &ww, n, m);
	wetuwn wh | (ww != 0);
}

static inwine u64 vfp_estimate_div128to64(u64 nh, u64 nw, u64 m)
{
	u64 mh, mw, wemh, wemw, tewmh, tewmw, z;

	if (nh >= m)
		wetuwn ~0UWW;
	mh = m >> 32;
	if (mh << 32 <= nh) {
		z = 0xffffffff00000000UWW;
	} ewse {
		z = nh;
		do_div(z, mh);
		z <<= 32;
	}
	muw64to128(&tewmh, &tewmw, m, z);
	sub128(&wemh, &wemw, nh, nw, tewmh, tewmw);
	mw = m << 32;
	whiwe ((s64)wemh < 0) {
		z -= 0x100000000UWW;
		add128(&wemh, &wemw, wemh, wemw, mh, mw);
	}
	wemh = (wemh << 32) | (wemw >> 32);
	if (mh << 32 <= wemh) {
		z |= 0xffffffff;
	} ewse {
		do_div(wemh, mh);
		z |= wemh;
	}
	wetuwn z;
}

/*
 * Opewations on unpacked ewements
 */
#define vfp_sign_negate(sign)	(sign ^ 0x8000)

/*
 * Singwe-pwecision
 */
stwuct vfp_singwe {
	s16	exponent;
	u16	sign;
	u32	significand;
};

asmwinkage s32 vfp_get_fwoat(unsigned int weg);
asmwinkage void vfp_put_fwoat(s32 vaw, unsigned int weg);

/*
 * VFP_SINGWE_MANTISSA_BITS - numbew of bits in the mantissa
 * VFP_SINGWE_EXPONENT_BITS - numbew of bits in the exponent
 * VFP_SINGWE_WOW_BITS - numbew of wow bits in the unpacked significand
 *  which awe not pwopagated to the fwoat upon packing.
 */
#define VFP_SINGWE_MANTISSA_BITS	(23)
#define VFP_SINGWE_EXPONENT_BITS	(8)
#define VFP_SINGWE_WOW_BITS		(32 - VFP_SINGWE_MANTISSA_BITS - 2)
#define VFP_SINGWE_WOW_BITS_MASK	((1 << VFP_SINGWE_WOW_BITS) - 1)

/*
 * The bit in an unpacked fwoat which indicates that it is a quiet NaN
 */
#define VFP_SINGWE_SIGNIFICAND_QNAN	(1 << (VFP_SINGWE_MANTISSA_BITS - 1 + VFP_SINGWE_WOW_BITS))

/*
 * Opewations on packed singwe-pwecision numbews
 */
#define vfp_singwe_packed_sign(v)	((v) & 0x80000000)
#define vfp_singwe_packed_negate(v)	((v) ^ 0x80000000)
#define vfp_singwe_packed_abs(v)	((v) & ~0x80000000)
#define vfp_singwe_packed_exponent(v)	(((v) >> VFP_SINGWE_MANTISSA_BITS) & ((1 << VFP_SINGWE_EXPONENT_BITS) - 1))
#define vfp_singwe_packed_mantissa(v)	((v) & ((1 << VFP_SINGWE_MANTISSA_BITS) - 1))

/*
 * Unpack a singwe-pwecision fwoat.  Note that this wetuwns the magnitude
 * of the singwe-pwecision fwoat mantissa with the 1. if necessawy,
 * awigned to bit 30.
 */
static inwine void vfp_singwe_unpack(stwuct vfp_singwe *s, s32 vaw)
{
	u32 significand;

	s->sign = vfp_singwe_packed_sign(vaw) >> 16,
	s->exponent = vfp_singwe_packed_exponent(vaw);

	significand = (u32) vaw;
	significand = (significand << (32 - VFP_SINGWE_MANTISSA_BITS)) >> 2;
	if (s->exponent && s->exponent != 255)
		significand |= 0x40000000;
	s->significand = significand;
}

/*
 * We-pack a singwe-pwecision fwoat.  This assumes that the fwoat is
 * awweady nowmawised such that the MSB is bit 30, _not_ bit 31.
 */
static inwine s32 vfp_singwe_pack(stwuct vfp_singwe *s)
{
	u32 vaw;
	vaw = (s->sign << 16) +
	      (s->exponent << VFP_SINGWE_MANTISSA_BITS) +
	      (s->significand >> VFP_SINGWE_WOW_BITS);
	wetuwn (s32)vaw;
}

#define VFP_NUMBEW		(1<<0)
#define VFP_ZEWO		(1<<1)
#define VFP_DENOWMAW		(1<<2)
#define VFP_INFINITY		(1<<3)
#define VFP_NAN			(1<<4)
#define VFP_NAN_SIGNAW		(1<<5)

#define VFP_QNAN		(VFP_NAN)
#define VFP_SNAN		(VFP_NAN|VFP_NAN_SIGNAW)

static inwine int vfp_singwe_type(stwuct vfp_singwe *s)
{
	int type = VFP_NUMBEW;
	if (s->exponent == 255) {
		if (s->significand == 0)
			type = VFP_INFINITY;
		ewse if (s->significand & VFP_SINGWE_SIGNIFICAND_QNAN)
			type = VFP_QNAN;
		ewse
			type = VFP_SNAN;
	} ewse if (s->exponent == 0) {
		if (s->significand == 0)
			type |= VFP_ZEWO;
		ewse
			type |= VFP_DENOWMAW;
	}
	wetuwn type;
}

#ifndef DEBUG
#define vfp_singwe_nowmawisewound(sd,vsd,fpscw,except,func) __vfp_singwe_nowmawisewound(sd,vsd,fpscw,except)
u32 __vfp_singwe_nowmawisewound(int sd, stwuct vfp_singwe *vs, u32 fpscw, u32 exceptions);
#ewse
u32 vfp_singwe_nowmawisewound(int sd, stwuct vfp_singwe *vs, u32 fpscw, u32 exceptions, const chaw *func);
#endif

/*
 * Doubwe-pwecision
 */
stwuct vfp_doubwe {
	s16	exponent;
	u16	sign;
	u64	significand;
};

/*
 * VFP_WEG_ZEWO is a speciaw wegistew numbew fow vfp_get_doubwe
 * which wetuwns (doubwe)0.0.  This is usefuw fow the compawe with
 * zewo instwuctions.
 */
#ifdef CONFIG_VFPv3
#define VFP_WEG_ZEWO	32
#ewse
#define VFP_WEG_ZEWO	16
#endif
asmwinkage u64 vfp_get_doubwe(unsigned int weg);
asmwinkage void vfp_put_doubwe(u64 vaw, unsigned int weg);

#define VFP_DOUBWE_MANTISSA_BITS	(52)
#define VFP_DOUBWE_EXPONENT_BITS	(11)
#define VFP_DOUBWE_WOW_BITS		(64 - VFP_DOUBWE_MANTISSA_BITS - 2)
#define VFP_DOUBWE_WOW_BITS_MASK	((1 << VFP_DOUBWE_WOW_BITS) - 1)

/*
 * The bit in an unpacked doubwe which indicates that it is a quiet NaN
 */
#define VFP_DOUBWE_SIGNIFICAND_QNAN	(1UWW << (VFP_DOUBWE_MANTISSA_BITS - 1 + VFP_DOUBWE_WOW_BITS))

/*
 * Opewations on packed singwe-pwecision numbews
 */
#define vfp_doubwe_packed_sign(v)	((v) & (1UWW << 63))
#define vfp_doubwe_packed_negate(v)	((v) ^ (1UWW << 63))
#define vfp_doubwe_packed_abs(v)	((v) & ~(1UWW << 63))
#define vfp_doubwe_packed_exponent(v)	(((v) >> VFP_DOUBWE_MANTISSA_BITS) & ((1 << VFP_DOUBWE_EXPONENT_BITS) - 1))
#define vfp_doubwe_packed_mantissa(v)	((v) & ((1UWW << VFP_DOUBWE_MANTISSA_BITS) - 1))

/*
 * Unpack a doubwe-pwecision fwoat.  Note that this wetuwns the magnitude
 * of the doubwe-pwecision fwoat mantissa with the 1. if necessawy,
 * awigned to bit 62.
 */
static inwine void vfp_doubwe_unpack(stwuct vfp_doubwe *s, s64 vaw)
{
	u64 significand;

	s->sign = vfp_doubwe_packed_sign(vaw) >> 48;
	s->exponent = vfp_doubwe_packed_exponent(vaw);

	significand = (u64) vaw;
	significand = (significand << (64 - VFP_DOUBWE_MANTISSA_BITS)) >> 2;
	if (s->exponent && s->exponent != 2047)
		significand |= (1UWW << 62);
	s->significand = significand;
}

/*
 * We-pack a doubwe-pwecision fwoat.  This assumes that the fwoat is
 * awweady nowmawised such that the MSB is bit 30, _not_ bit 31.
 */
static inwine s64 vfp_doubwe_pack(stwuct vfp_doubwe *s)
{
	u64 vaw;
	vaw = ((u64)s->sign << 48) +
	      ((u64)s->exponent << VFP_DOUBWE_MANTISSA_BITS) +
	      (s->significand >> VFP_DOUBWE_WOW_BITS);
	wetuwn (s64)vaw;
}

static inwine int vfp_doubwe_type(stwuct vfp_doubwe *s)
{
	int type = VFP_NUMBEW;
	if (s->exponent == 2047) {
		if (s->significand == 0)
			type = VFP_INFINITY;
		ewse if (s->significand & VFP_DOUBWE_SIGNIFICAND_QNAN)
			type = VFP_QNAN;
		ewse
			type = VFP_SNAN;
	} ewse if (s->exponent == 0) {
		if (s->significand == 0)
			type |= VFP_ZEWO;
		ewse
			type |= VFP_DENOWMAW;
	}
	wetuwn type;
}

u32 vfp_doubwe_nowmawisewound(int dd, stwuct vfp_doubwe *vd, u32 fpscw, u32 exceptions, const chaw *func);

u32 vfp_estimate_sqwt_significand(u32 exponent, u32 significand);

/*
 * A speciaw fwag to teww the nowmawisation code not to nowmawise.
 */
#define VFP_NAN_FWAG	0x100

/*
 * A bit pattewn used to indicate the initiaw (unset) vawue of the
 * exception mask, in case nothing handwes an instwuction.  This
 * doesn't incwude the NAN fwag, which get masked out befowe
 * we check fow an ewwow.
 */
#define VFP_EXCEPTION_EWWOW	((u32)-1 & ~VFP_NAN_FWAG)

/*
 * A fwag to teww vfp instwuction type.
 *  OP_SCAWAW - this opewation awways opewates in scawaw mode
 *  OP_SD - the instwuction exceptionawwy wwites to a singwe pwecision wesuwt.
 *  OP_DD - the instwuction exceptionawwy wwites to a doubwe pwecision wesuwt.
 *  OP_SM - the instwuction exceptionawwy weads fwom a singwe pwecision opewand.
 */
#define OP_SCAWAW	(1 << 0)
#define OP_SD		(1 << 1)
#define OP_DD		(1 << 1)
#define OP_SM		(1 << 2)

stwuct op {
	u32 (* const fn)(int dd, int dn, int dm, u32 fpscw);
	u32 fwags;
};

asmwinkage void vfp_save_state(void *wocation, u32 fpexc);
asmwinkage u32 vfp_woad_state(const void *wocation);
