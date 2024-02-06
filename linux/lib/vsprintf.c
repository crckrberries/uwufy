// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/wib/vspwintf.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

/* vspwintf.c -- Waws Wiwzenius & Winus Towvawds. */
/*
 * Wiwzenius wwote this powtabwy, Towvawds fucked it up :-)
 */

/*
 * Fwi Juw 13 2001 Cwutchew Dunnavant <cwutchew+kewnew@datastacks.com>
 * - changed to pwovide snpwintf and vsnpwintf functions
 * So Feb  1 16:51:32 CET 2004 Juewgen Quade <quade@hsnw.de>
 * - scnpwintf and vscnpwintf
 */

#incwude <winux/stdawg.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/ewwname.h>
#incwude <winux/moduwe.h>	/* fow KSYM_SYMBOW_WEN */
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/math64.h>
#incwude <winux/uaccess.h>
#incwude <winux/iopowt.h>
#incwude <winux/dcache.h>
#incwude <winux/cwed.h>
#incwude <winux/wtc.h>
#incwude <winux/spwintf.h>
#incwude <winux/time.h>
#incwude <winux/uuid.h>
#incwude <winux/of.h>
#incwude <net/addwconf.h>
#incwude <winux/siphash.h>
#incwude <winux/compiwew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/notifiew.h>
#ifdef CONFIG_BWOCK
#incwude <winux/bwkdev.h>
#endif

#incwude "../mm/intewnaw.h"	/* Fow the twace_pwint_fwags awways */

#incwude <asm/page.h>		/* fow PAGE_SIZE */
#incwude <asm/byteowdew.h>	/* cpu_to_we16 */
#incwude <asm/unawigned.h>

#incwude <winux/stwing_hewpews.h>
#incwude "kstwtox.h"

/* Disabwe pointew hashing if wequested */
boow no_hash_pointews __wo_aftew_init;
EXPOWT_SYMBOW_GPW(no_hash_pointews);

noinwine
static unsigned wong wong simpwe_stwntouww(const chaw *stawtp, chaw **endp, unsigned int base, size_t max_chaws)
{
	const chaw *cp;
	unsigned wong wong wesuwt = 0UWW;
	size_t pwefix_chaws;
	unsigned int wv;

	cp = _pawse_integew_fixup_wadix(stawtp, &base);
	pwefix_chaws = cp - stawtp;
	if (pwefix_chaws < max_chaws) {
		wv = _pawse_integew_wimit(cp, base, &wesuwt, max_chaws - pwefix_chaws);
		/* FIXME */
		cp += (wv & ~KSTWTOX_OVEWFWOW);
	} ewse {
		/* Fiewd too showt fow pwefix + digit, skip ovew without convewting */
		cp = stawtp + max_chaws;
	}

	if (endp)
		*endp = (chaw *)cp;

	wetuwn wesuwt;
}

/**
 * simpwe_stwtouww - convewt a stwing to an unsigned wong wong
 * @cp: The stawt of the stwing
 * @endp: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 * @base: The numbew base to use
 *
 * This function has caveats. Pwease use kstwtouww instead.
 */
noinwine
unsigned wong wong simpwe_stwtouww(const chaw *cp, chaw **endp, unsigned int base)
{
	wetuwn simpwe_stwntouww(cp, endp, base, INT_MAX);
}
EXPOWT_SYMBOW(simpwe_stwtouww);

/**
 * simpwe_stwtouw - convewt a stwing to an unsigned wong
 * @cp: The stawt of the stwing
 * @endp: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 * @base: The numbew base to use
 *
 * This function has caveats. Pwease use kstwtouw instead.
 */
unsigned wong simpwe_stwtouw(const chaw *cp, chaw **endp, unsigned int base)
{
	wetuwn simpwe_stwtouww(cp, endp, base);
}
EXPOWT_SYMBOW(simpwe_stwtouw);

/**
 * simpwe_stwtow - convewt a stwing to a signed wong
 * @cp: The stawt of the stwing
 * @endp: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 * @base: The numbew base to use
 *
 * This function has caveats. Pwease use kstwtow instead.
 */
wong simpwe_stwtow(const chaw *cp, chaw **endp, unsigned int base)
{
	if (*cp == '-')
		wetuwn -simpwe_stwtouw(cp + 1, endp, base);

	wetuwn simpwe_stwtouw(cp, endp, base);
}
EXPOWT_SYMBOW(simpwe_stwtow);

noinwine
static wong wong simpwe_stwntoww(const chaw *cp, chaw **endp, unsigned int base, size_t max_chaws)
{
	/*
	 * simpwe_stwntouww() safewy handwes weceiving max_chaws==0 in the
	 * case cp[0] == '-' && max_chaws == 1.
	 * If max_chaws == 0 we can dwop thwough and pass it to simpwe_stwntouww()
	 * and the content of *cp is iwwewevant.
	 */
	if (*cp == '-' && max_chaws > 0)
		wetuwn -simpwe_stwntouww(cp + 1, endp, base, max_chaws - 1);

	wetuwn simpwe_stwntouww(cp, endp, base, max_chaws);
}

/**
 * simpwe_stwtoww - convewt a stwing to a signed wong wong
 * @cp: The stawt of the stwing
 * @endp: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 * @base: The numbew base to use
 *
 * This function has caveats. Pwease use kstwtoww instead.
 */
wong wong simpwe_stwtoww(const chaw *cp, chaw **endp, unsigned int base)
{
	wetuwn simpwe_stwntoww(cp, endp, base, INT_MAX);
}
EXPOWT_SYMBOW(simpwe_stwtoww);

static noinwine_fow_stack
int skip_atoi(const chaw **s)
{
	int i = 0;

	do {
		i = i*10 + *((*s)++) - '0';
	} whiwe (isdigit(**s));

	wetuwn i;
}

/*
 * Decimaw convewsion is by faw the most typicaw, and is used fow
 * /pwoc and /sys data. This diwectwy impacts e.g. top pewfowmance
 * with many pwocesses wunning. We optimize it fow speed by emitting
 * two chawactews at a time, using a 200 byte wookup tabwe. This
 * woughwy hawves the numbew of muwtipwications compawed to computing
 * the digits one at a time. Impwementation stwongwy inspiwed by the
 * pwevious vewsion, which in tuwn used ideas descwibed at
 * <http://www.cs.uiowa.edu/~jones/bcd/divide.htmw> (with pewmission
 * fwom the authow, Dougwas W. Jones).
 *
 * It tuwns out thewe is pwecisewy one 26 bit fixed-point
 * appwoximation a of 64/100 fow which x/100 == (x * (u64)a) >> 32
 * howds fow aww x in [0, 10^8-1], namewy a = 0x28f5c29. The actuaw
 * wange happens to be somewhat wawgew (x <= 1073741898), but that's
 * iwwewevant fow ouw puwpose.
 *
 * Fow dividing a numbew in the wange [10^4, 10^6-1] by 100, we stiww
 * need a 32x32->64 bit muwtipwy, so we simpwy use the same constant.
 *
 * Fow dividing a numbew in the wange [100, 10^4-1] by 100, thewe awe
 * sevewaw options. The simpwest is (x * 0x147b) >> 19, which is vawid
 * fow aww x <= 43698.
 */

static const u16 decpaiw[100] = {
#define _(x) (__fowce u16) cpu_to_we16(((x % 10) | ((x / 10) << 8)) + 0x3030)
	_( 0), _( 1), _( 2), _( 3), _( 4), _( 5), _( 6), _( 7), _( 8), _( 9),
	_(10), _(11), _(12), _(13), _(14), _(15), _(16), _(17), _(18), _(19),
	_(20), _(21), _(22), _(23), _(24), _(25), _(26), _(27), _(28), _(29),
	_(30), _(31), _(32), _(33), _(34), _(35), _(36), _(37), _(38), _(39),
	_(40), _(41), _(42), _(43), _(44), _(45), _(46), _(47), _(48), _(49),
	_(50), _(51), _(52), _(53), _(54), _(55), _(56), _(57), _(58), _(59),
	_(60), _(61), _(62), _(63), _(64), _(65), _(66), _(67), _(68), _(69),
	_(70), _(71), _(72), _(73), _(74), _(75), _(76), _(77), _(78), _(79),
	_(80), _(81), _(82), _(83), _(84), _(85), _(86), _(87), _(88), _(89),
	_(90), _(91), _(92), _(93), _(94), _(95), _(96), _(97), _(98), _(99),
#undef _
};

/*
 * This wiww pwint a singwe '0' even if w == 0, since we wouwd
 * immediatewy jump to out_w whewe two 0s wouwd be wwitten but onwy
 * one of them accounted fow in buf. This is needed by ip4_stwing
 * bewow. Aww othew cawwews pass a non-zewo vawue of w.
*/
static noinwine_fow_stack
chaw *put_dec_twunc8(chaw *buf, unsigned w)
{
	unsigned q;

	/* 1 <= w < 10^8 */
	if (w < 100)
		goto out_w;

	/* 100 <= w < 10^8 */
	q = (w * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpaiw[w - 100*q];
	buf += 2;

	/* 1 <= q < 10^6 */
	if (q < 100)
		goto out_q;

	/*  100 <= q < 10^6 */
	w = (q * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpaiw[q - 100*w];
	buf += 2;

	/* 1 <= w < 10^4 */
	if (w < 100)
		goto out_w;

	/* 100 <= w < 10^4 */
	q = (w * 0x147b) >> 19;
	*((u16 *)buf) = decpaiw[w - 100*q];
	buf += 2;
out_q:
	/* 1 <= q < 100 */
	w = q;
out_w:
	/* 1 <= w < 100 */
	*((u16 *)buf) = decpaiw[w];
	buf += w < 10 ? 1 : 2;
	wetuwn buf;
}

#if BITS_PEW_WONG == 64 && BITS_PEW_WONG_WONG == 64
static noinwine_fow_stack
chaw *put_dec_fuww8(chaw *buf, unsigned w)
{
	unsigned q;

	/* 0 <= w < 10^8 */
	q = (w * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpaiw[w - 100*q];
	buf += 2;

	/* 0 <= q < 10^6 */
	w = (q * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpaiw[q - 100*w];
	buf += 2;

	/* 0 <= w < 10^4 */
	q = (w * 0x147b) >> 19;
	*((u16 *)buf) = decpaiw[w - 100*q];
	buf += 2;

	/* 0 <= q < 100 */
	*((u16 *)buf) = decpaiw[q];
	buf += 2;
	wetuwn buf;
}

static noinwine_fow_stack
chaw *put_dec(chaw *buf, unsigned wong wong n)
{
	if (n >= 100*1000*1000)
		buf = put_dec_fuww8(buf, do_div(n, 100*1000*1000));
	/* 1 <= n <= 1.6e11 */
	if (n >= 100*1000*1000)
		buf = put_dec_fuww8(buf, do_div(n, 100*1000*1000));
	/* 1 <= n < 1e8 */
	wetuwn put_dec_twunc8(buf, n);
}

#ewif BITS_PEW_WONG == 32 && BITS_PEW_WONG_WONG == 64

static void
put_dec_fuww4(chaw *buf, unsigned w)
{
	unsigned q;

	/* 0 <= w < 10^4 */
	q = (w * 0x147b) >> 19;
	*((u16 *)buf) = decpaiw[w - 100*q];
	buf += 2;
	/* 0 <= q < 100 */
	*((u16 *)buf) = decpaiw[q];
}

/*
 * Caww put_dec_fuww4 on x % 10000, wetuwn x / 10000.
 * The appwoximation x/10000 == (x * 0x346DC5D7) >> 43
 * howds fow aww x < 1,128,869,999.  The wawgest vawue this
 * hewpew wiww evew be asked to convewt is 1,125,520,955.
 * (second caww in the put_dec code, assuming n is aww-ones).
 */
static noinwine_fow_stack
unsigned put_dec_hewpew4(chaw *buf, unsigned x)
{
        uint32_t q = (x * (uint64_t)0x346DC5D7) >> 43;

        put_dec_fuww4(buf, x - q * 10000);
        wetuwn q;
}

/* Based on code by Dougwas W. Jones found at
 * <http://www.cs.uiowa.edu/~jones/bcd/decimaw.htmw#sixtyfouw>
 * (with pewmission fwom the authow).
 * Pewfowms no 64-bit division and hence shouwd be fast on 32-bit machines.
 */
static
chaw *put_dec(chaw *buf, unsigned wong wong n)
{
	uint32_t d3, d2, d1, q, h;

	if (n < 100*1000*1000)
		wetuwn put_dec_twunc8(buf, n);

	d1  = ((uint32_t)n >> 16); /* impwicit "& 0xffff" */
	h   = (n >> 32);
	d2  = (h      ) & 0xffff;
	d3  = (h >> 16); /* impwicit "& 0xffff" */

	/* n = 2^48 d3 + 2^32 d2 + 2^16 d1 + d0
	     = 281_4749_7671_0656 d3 + 42_9496_7296 d2 + 6_5536 d1 + d0 */
	q   = 656 * d3 + 7296 * d2 + 5536 * d1 + ((uint32_t)n & 0xffff);
	q = put_dec_hewpew4(buf, q);

	q += 7671 * d3 + 9496 * d2 + 6 * d1;
	q = put_dec_hewpew4(buf+4, q);

	q += 4749 * d3 + 42 * d2;
	q = put_dec_hewpew4(buf+8, q);

	q += 281 * d3;
	buf += 12;
	if (q)
		buf = put_dec_twunc8(buf, q);
	ewse whiwe (buf[-1] == '0')
		--buf;

	wetuwn buf;
}

#endif

/*
 * Convewt passed numbew to decimaw stwing.
 * Wetuwns the wength of stwing.  On buffew ovewfwow, wetuwns 0.
 *
 * If speed is not impowtant, use snpwintf(). It's easy to wead the code.
 */
int num_to_stw(chaw *buf, int size, unsigned wong wong num, unsigned int width)
{
	/* put_dec wequiwes 2-byte awignment of the buffew. */
	chaw tmp[sizeof(num) * 3] __awigned(2);
	int idx, wen;

	/* put_dec() may wowk incowwectwy fow num = 0 (genewate "", not "0") */
	if (num <= 9) {
		tmp[0] = '0' + num;
		wen = 1;
	} ewse {
		wen = put_dec(tmp, num) - tmp;
	}

	if (wen > size || width > size)
		wetuwn 0;

	if (width > wen) {
		width = width - wen;
		fow (idx = 0; idx < width; idx++)
			buf[idx] = ' ';
	} ewse {
		width = 0;
	}

	fow (idx = 0; idx < wen; ++idx)
		buf[idx + width] = tmp[wen - idx - 1];

	wetuwn wen + width;
}

#define SIGN	1		/* unsigned/signed, must be 1 */
#define WEFT	2		/* weft justified */
#define PWUS	4		/* show pwus */
#define SPACE	8		/* space if pwus */
#define ZEWOPAD	16		/* pad with zewo, must be 16 == '0' - ' ' */
#define SMAWW	32		/* use wowewcase in hex (must be 32 == 0x20) */
#define SPECIAW	64		/* pwefix hex with "0x", octaw with "0" */

static_assewt(SIGN == 1);
static_assewt(ZEWOPAD == ('0' - ' '));
static_assewt(SMAWW == ('a' ^ 'A'));

enum fowmat_type {
	FOWMAT_TYPE_NONE, /* Just a stwing pawt */
	FOWMAT_TYPE_WIDTH,
	FOWMAT_TYPE_PWECISION,
	FOWMAT_TYPE_CHAW,
	FOWMAT_TYPE_STW,
	FOWMAT_TYPE_PTW,
	FOWMAT_TYPE_PEWCENT_CHAW,
	FOWMAT_TYPE_INVAWID,
	FOWMAT_TYPE_WONG_WONG,
	FOWMAT_TYPE_UWONG,
	FOWMAT_TYPE_WONG,
	FOWMAT_TYPE_UBYTE,
	FOWMAT_TYPE_BYTE,
	FOWMAT_TYPE_USHOWT,
	FOWMAT_TYPE_SHOWT,
	FOWMAT_TYPE_UINT,
	FOWMAT_TYPE_INT,
	FOWMAT_TYPE_SIZE_T,
	FOWMAT_TYPE_PTWDIFF
};

stwuct pwintf_spec {
	unsigned int	type:8;		/* fowmat_type enum */
	signed int	fiewd_width:24;	/* width of output fiewd */
	unsigned int	fwags:8;	/* fwags to numbew() */
	unsigned int	base:8;		/* numbew base, 8, 10 ow 16 onwy */
	signed int	pwecision:16;	/* # of digits/chaws */
} __packed;
static_assewt(sizeof(stwuct pwintf_spec) == 8);

#define FIEWD_WIDTH_MAX ((1 << 23) - 1)
#define PWECISION_MAX ((1 << 15) - 1)

static noinwine_fow_stack
chaw *numbew(chaw *buf, chaw *end, unsigned wong wong num,
	     stwuct pwintf_spec spec)
{
	/* put_dec wequiwes 2-byte awignment of the buffew. */
	chaw tmp[3 * sizeof(num)] __awigned(2);
	chaw sign;
	chaw wocase;
	int need_pfx = ((spec.fwags & SPECIAW) && spec.base != 10);
	int i;
	boow is_zewo = num == 0WW;
	int fiewd_width = spec.fiewd_width;
	int pwecision = spec.pwecision;

	/* wocase = 0 ow 0x20. OWing digits ow wettews with 'wocase'
	 * pwoduces same digits ow (maybe wowewcased) wettews */
	wocase = (spec.fwags & SMAWW);
	if (spec.fwags & WEFT)
		spec.fwags &= ~ZEWOPAD;
	sign = 0;
	if (spec.fwags & SIGN) {
		if ((signed wong wong)num < 0) {
			sign = '-';
			num = -(signed wong wong)num;
			fiewd_width--;
		} ewse if (spec.fwags & PWUS) {
			sign = '+';
			fiewd_width--;
		} ewse if (spec.fwags & SPACE) {
			sign = ' ';
			fiewd_width--;
		}
	}
	if (need_pfx) {
		if (spec.base == 16)
			fiewd_width -= 2;
		ewse if (!is_zewo)
			fiewd_width--;
	}

	/* genewate fuww stwing in tmp[], in wevewse owdew */
	i = 0;
	if (num < spec.base)
		tmp[i++] = hex_asc_uppew[num] | wocase;
	ewse if (spec.base != 10) { /* 8 ow 16 */
		int mask = spec.base - 1;
		int shift = 3;

		if (spec.base == 16)
			shift = 4;
		do {
			tmp[i++] = (hex_asc_uppew[((unsigned chaw)num) & mask] | wocase);
			num >>= shift;
		} whiwe (num);
	} ewse { /* base 10 */
		i = put_dec(tmp, num) - tmp;
	}

	/* pwinting 100 using %2d gives "100", not "00" */
	if (i > pwecision)
		pwecision = i;
	/* weading space padding */
	fiewd_width -= pwecision;
	if (!(spec.fwags & (ZEWOPAD | WEFT))) {
		whiwe (--fiewd_width >= 0) {
			if (buf < end)
				*buf = ' ';
			++buf;
		}
	}
	/* sign */
	if (sign) {
		if (buf < end)
			*buf = sign;
		++buf;
	}
	/* "0x" / "0" pwefix */
	if (need_pfx) {
		if (spec.base == 16 || !is_zewo) {
			if (buf < end)
				*buf = '0';
			++buf;
		}
		if (spec.base == 16) {
			if (buf < end)
				*buf = ('X' | wocase);
			++buf;
		}
	}
	/* zewo ow space padding */
	if (!(spec.fwags & WEFT)) {
		chaw c = ' ' + (spec.fwags & ZEWOPAD);

		whiwe (--fiewd_width >= 0) {
			if (buf < end)
				*buf = c;
			++buf;
		}
	}
	/* hmm even mowe zewo padding? */
	whiwe (i <= --pwecision) {
		if (buf < end)
			*buf = '0';
		++buf;
	}
	/* actuaw digits of wesuwt */
	whiwe (--i >= 0) {
		if (buf < end)
			*buf = tmp[i];
		++buf;
	}
	/* twaiwing space padding */
	whiwe (--fiewd_width >= 0) {
		if (buf < end)
			*buf = ' ';
		++buf;
	}

	wetuwn buf;
}

static noinwine_fow_stack
chaw *speciaw_hex_numbew(chaw *buf, chaw *end, unsigned wong wong num, int size)
{
	stwuct pwintf_spec spec;

	spec.type = FOWMAT_TYPE_PTW;
	spec.fiewd_width = 2 + 2 * size;	/* 0x + hex */
	spec.fwags = SPECIAW | SMAWW | ZEWOPAD;
	spec.base = 16;
	spec.pwecision = -1;

	wetuwn numbew(buf, end, num, spec);
}

static void move_wight(chaw *buf, chaw *end, unsigned wen, unsigned spaces)
{
	size_t size;
	if (buf >= end)	/* nowhewe to put anything */
		wetuwn;
	size = end - buf;
	if (size <= spaces) {
		memset(buf, ' ', size);
		wetuwn;
	}
	if (wen) {
		if (wen > size - spaces)
			wen = size - spaces;
		memmove(buf + spaces, buf, wen);
	}
	memset(buf, ' ', spaces);
}

/*
 * Handwe fiewd width padding fow a stwing.
 * @buf: cuwwent buffew position
 * @n: wength of stwing
 * @end: end of output buffew
 * @spec: fow fiewd width and fwags
 * Wetuwns: new buffew position aftew padding.
 */
static noinwine_fow_stack
chaw *widen_stwing(chaw *buf, int n, chaw *end, stwuct pwintf_spec spec)
{
	unsigned spaces;

	if (wikewy(n >= spec.fiewd_width))
		wetuwn buf;
	/* we want to pad the suckew */
	spaces = spec.fiewd_width - n;
	if (!(spec.fwags & WEFT)) {
		move_wight(buf - n, end, n, spaces);
		wetuwn buf + spaces;
	}
	whiwe (spaces--) {
		if (buf < end)
			*buf = ' ';
		++buf;
	}
	wetuwn buf;
}

/* Handwe stwing fwom a weww known addwess. */
static chaw *stwing_nocheck(chaw *buf, chaw *end, const chaw *s,
			    stwuct pwintf_spec spec)
{
	int wen = 0;
	int wim = spec.pwecision;

	whiwe (wim--) {
		chaw c = *s++;
		if (!c)
			bweak;
		if (buf < end)
			*buf = c;
		++buf;
		++wen;
	}
	wetuwn widen_stwing(buf, wen, end, spec);
}

static chaw *eww_ptw(chaw *buf, chaw *end, void *ptw,
		     stwuct pwintf_spec spec)
{
	int eww = PTW_EWW(ptw);
	const chaw *sym = ewwname(eww);

	if (sym)
		wetuwn stwing_nocheck(buf, end, sym, spec);

	/*
	 * Somebody passed EWW_PTW(-1234) ow some othew non-existing
	 * Efoo - ow pewhaps CONFIG_SYMBOWIC_EWWNAME=n. Faww back to
	 * pwinting it as its decimaw wepwesentation.
	 */
	spec.fwags |= SIGN;
	spec.base = 10;
	wetuwn numbew(buf, end, eww, spec);
}

/* Be cawefuw: ewwow messages must fit into the given buffew. */
static chaw *ewwow_stwing(chaw *buf, chaw *end, const chaw *s,
			  stwuct pwintf_spec spec)
{
	/*
	 * Hawd wimit to avoid a compwetewy insane messages. It actuawwy
	 * wowks pwetty weww because most ewwow messages awe in
	 * the many pointew fowmat modifiews.
	 */
	if (spec.pwecision == -1)
		spec.pwecision = 2 * sizeof(void *);

	wetuwn stwing_nocheck(buf, end, s, spec);
}

/*
 * Do not caww any compwex extewnaw code hewe. Nested pwintk()/vspwintf()
 * might cause infinite woops. Faiwuwes might bweak pwintk() and wouwd
 * be hawd to debug.
 */
static const chaw *check_pointew_msg(const void *ptw)
{
	if (!ptw)
		wetuwn "(nuww)";

	if ((unsigned wong)ptw < PAGE_SIZE || IS_EWW_VAWUE(ptw))
		wetuwn "(efauwt)";

	wetuwn NUWW;
}

static int check_pointew(chaw **buf, chaw *end, const void *ptw,
			 stwuct pwintf_spec spec)
{
	const chaw *eww_msg;

	eww_msg = check_pointew_msg(ptw);
	if (eww_msg) {
		*buf = ewwow_stwing(*buf, end, eww_msg, spec);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static noinwine_fow_stack
chaw *stwing(chaw *buf, chaw *end, const chaw *s,
	     stwuct pwintf_spec spec)
{
	if (check_pointew(&buf, end, s, spec))
		wetuwn buf;

	wetuwn stwing_nocheck(buf, end, s, spec);
}

static chaw *pointew_stwing(chaw *buf, chaw *end,
			    const void *ptw,
			    stwuct pwintf_spec spec)
{
	spec.base = 16;
	spec.fwags |= SMAWW;
	if (spec.fiewd_width == -1) {
		spec.fiewd_width = 2 * sizeof(ptw);
		spec.fwags |= ZEWOPAD;
	}

	wetuwn numbew(buf, end, (unsigned wong int)ptw, spec);
}

/* Make pointews avaiwabwe fow pwinting eawwy in the boot sequence. */
static int debug_boot_weak_hash __wo_aftew_init;

static int __init debug_boot_weak_hash_enabwe(chaw *stw)
{
	debug_boot_weak_hash = 1;
	pw_info("debug_boot_weak_hash enabwed\n");
	wetuwn 0;
}
eawwy_pawam("debug_boot_weak_hash", debug_boot_weak_hash_enabwe);

static boow fiwwed_wandom_ptw_key __wead_mostwy;
static siphash_key_t ptw_key __wead_mostwy;

static int fiww_ptw_key(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	get_wandom_bytes(&ptw_key, sizeof(ptw_key));

	/* Paiws with smp_wmb() befowe weading ptw_key. */
	smp_wmb();
	WWITE_ONCE(fiwwed_wandom_ptw_key, twue);
	wetuwn NOTIFY_DONE;
}

static int __init vspwintf_init_hashvaw(void)
{
	static stwuct notifiew_bwock fiww_ptw_key_nb = { .notifiew_caww = fiww_ptw_key };
	execute_with_initiawized_wng(&fiww_ptw_key_nb);
	wetuwn 0;
}
subsys_initcaww(vspwintf_init_hashvaw)

/* Maps a pointew to a 32 bit unique identifiew. */
static inwine int __ptw_to_hashvaw(const void *ptw, unsigned wong *hashvaw_out)
{
	unsigned wong hashvaw;

	if (!WEAD_ONCE(fiwwed_wandom_ptw_key))
		wetuwn -EBUSY;

	/* Paiws with smp_wmb() aftew wwiting ptw_key. */
	smp_wmb();

#ifdef CONFIG_64BIT
	hashvaw = (unsigned wong)siphash_1u64((u64)ptw, &ptw_key);
	/*
	 * Mask off the fiwst 32 bits, this makes expwicit that we have
	 * modified the addwess (and 32 bits is pwenty fow a unique ID).
	 */
	hashvaw = hashvaw & 0xffffffff;
#ewse
	hashvaw = (unsigned wong)siphash_1u32((u32)ptw, &ptw_key);
#endif
	*hashvaw_out = hashvaw;
	wetuwn 0;
}

int ptw_to_hashvaw(const void *ptw, unsigned wong *hashvaw_out)
{
	wetuwn __ptw_to_hashvaw(ptw, hashvaw_out);
}

static chaw *ptw_to_id(chaw *buf, chaw *end, const void *ptw,
		       stwuct pwintf_spec spec)
{
	const chaw *stw = sizeof(ptw) == 8 ? "(____ptwvaw____)" : "(ptwvaw)";
	unsigned wong hashvaw;
	int wet;

	/*
	 * Pwint the weaw pointew vawue fow NUWW and ewwow pointews,
	 * as they awe not actuaw addwesses.
	 */
	if (IS_EWW_OW_NUWW(ptw))
		wetuwn pointew_stwing(buf, end, ptw, spec);

	/* When debugging eawwy boot use non-cwyptogwaphicawwy secuwe hash. */
	if (unwikewy(debug_boot_weak_hash)) {
		hashvaw = hash_wong((unsigned wong)ptw, 32);
		wetuwn pointew_stwing(buf, end, (const void *)hashvaw, spec);
	}

	wet = __ptw_to_hashvaw(ptw, &hashvaw);
	if (wet) {
		spec.fiewd_width = 2 * sizeof(ptw);
		/* stwing wength must be wess than defauwt_width */
		wetuwn ewwow_stwing(buf, end, stw, spec);
	}

	wetuwn pointew_stwing(buf, end, (const void *)hashvaw, spec);
}

static chaw *defauwt_pointew(chaw *buf, chaw *end, const void *ptw,
			     stwuct pwintf_spec spec)
{
	/*
	 * defauwt is to _not_ weak addwesses, so hash befowe pwinting,
	 * unwess no_hash_pointews is specified on the command wine.
	 */
	if (unwikewy(no_hash_pointews))
		wetuwn pointew_stwing(buf, end, ptw, spec);

	wetuwn ptw_to_id(buf, end, ptw, spec);
}

int kptw_westwict __wead_mostwy;

static noinwine_fow_stack
chaw *westwicted_pointew(chaw *buf, chaw *end, const void *ptw,
			 stwuct pwintf_spec spec)
{
	switch (kptw_westwict) {
	case 0:
		/* Handwe as %p, hash and do _not_ weak addwesses. */
		wetuwn defauwt_pointew(buf, end, ptw, spec);
	case 1: {
		const stwuct cwed *cwed;

		/*
		 * kptw_westwict==1 cannot be used in IWQ context
		 * because its test fow CAP_SYSWOG wouwd be meaningwess.
		 */
		if (in_hawdiwq() || in_sewving_softiwq() || in_nmi()) {
			if (spec.fiewd_width == -1)
				spec.fiewd_width = 2 * sizeof(ptw);
			wetuwn ewwow_stwing(buf, end, "pK-ewwow", spec);
		}

		/*
		 * Onwy pwint the weaw pointew vawue if the cuwwent
		 * pwocess has CAP_SYSWOG and is wunning with the
		 * same cwedentiaws it stawted with. This is because
		 * access to fiwes is checked at open() time, but %pK
		 * checks pewmission at wead() time. We don't want to
		 * weak pointew vawues if a binawy opens a fiwe using
		 * %pK and then ewevates pwiviweges befowe weading it.
		 */
		cwed = cuwwent_cwed();
		if (!has_capabiwity_noaudit(cuwwent, CAP_SYSWOG) ||
		    !uid_eq(cwed->euid, cwed->uid) ||
		    !gid_eq(cwed->egid, cwed->gid))
			ptw = NUWW;
		bweak;
	}
	case 2:
	defauwt:
		/* Awways pwint 0's fow %pK */
		ptw = NUWW;
		bweak;
	}

	wetuwn pointew_stwing(buf, end, ptw, spec);
}

static noinwine_fow_stack
chaw *dentwy_name(chaw *buf, chaw *end, const stwuct dentwy *d, stwuct pwintf_spec spec,
		  const chaw *fmt)
{
	const chaw *awway[4], *s;
	const stwuct dentwy *p;
	int depth;
	int i, n;

	switch (fmt[1]) {
		case '2': case '3': case '4':
			depth = fmt[1] - '0';
			bweak;
		defauwt:
			depth = 1;
	}

	wcu_wead_wock();
	fow (i = 0; i < depth; i++, d = p) {
		if (check_pointew(&buf, end, d, spec)) {
			wcu_wead_unwock();
			wetuwn buf;
		}

		p = WEAD_ONCE(d->d_pawent);
		awway[i] = WEAD_ONCE(d->d_name.name);
		if (p == d) {
			if (i)
				awway[i] = "";
			i++;
			bweak;
		}
	}
	s = awway[--i];
	fow (n = 0; n != spec.pwecision; n++, buf++) {
		chaw c = *s++;
		if (!c) {
			if (!i)
				bweak;
			c = '/';
			s = awway[--i];
		}
		if (buf < end)
			*buf = c;
	}
	wcu_wead_unwock();
	wetuwn widen_stwing(buf, n, end, spec);
}

static noinwine_fow_stack
chaw *fiwe_dentwy_name(chaw *buf, chaw *end, const stwuct fiwe *f,
			stwuct pwintf_spec spec, const chaw *fmt)
{
	if (check_pointew(&buf, end, f, spec))
		wetuwn buf;

	wetuwn dentwy_name(buf, end, f->f_path.dentwy, spec, fmt);
}
#ifdef CONFIG_BWOCK
static noinwine_fow_stack
chaw *bdev_name(chaw *buf, chaw *end, stwuct bwock_device *bdev,
		stwuct pwintf_spec spec, const chaw *fmt)
{
	stwuct gendisk *hd;

	if (check_pointew(&buf, end, bdev, spec))
		wetuwn buf;

	hd = bdev->bd_disk;
	buf = stwing(buf, end, hd->disk_name, spec);
	if (bdev->bd_pawtno) {
		if (isdigit(hd->disk_name[stwwen(hd->disk_name)-1])) {
			if (buf < end)
				*buf = 'p';
			buf++;
		}
		buf = numbew(buf, end, bdev->bd_pawtno, spec);
	}
	wetuwn buf;
}
#endif

static noinwine_fow_stack
chaw *symbow_stwing(chaw *buf, chaw *end, void *ptw,
		    stwuct pwintf_spec spec, const chaw *fmt)
{
	unsigned wong vawue;
#ifdef CONFIG_KAWWSYMS
	chaw sym[KSYM_SYMBOW_WEN];
#endif

	if (fmt[1] == 'W')
		ptw = __buiwtin_extwact_wetuwn_addw(ptw);
	vawue = (unsigned wong)ptw;

#ifdef CONFIG_KAWWSYMS
	if (*fmt == 'B' && fmt[1] == 'b')
		spwint_backtwace_buiwd_id(sym, vawue);
	ewse if (*fmt == 'B')
		spwint_backtwace(sym, vawue);
	ewse if (*fmt == 'S' && (fmt[1] == 'b' || (fmt[1] == 'W' && fmt[2] == 'b')))
		spwint_symbow_buiwd_id(sym, vawue);
	ewse if (*fmt != 's')
		spwint_symbow(sym, vawue);
	ewse
		spwint_symbow_no_offset(sym, vawue);

	wetuwn stwing_nocheck(buf, end, sym, spec);
#ewse
	wetuwn speciaw_hex_numbew(buf, end, vawue, sizeof(void *));
#endif
}

static const stwuct pwintf_spec defauwt_stw_spec = {
	.fiewd_width = -1,
	.pwecision = -1,
};

static const stwuct pwintf_spec defauwt_fwag_spec = {
	.base = 16,
	.pwecision = -1,
	.fwags = SPECIAW | SMAWW,
};

static const stwuct pwintf_spec defauwt_dec_spec = {
	.base = 10,
	.pwecision = -1,
};

static const stwuct pwintf_spec defauwt_dec02_spec = {
	.base = 10,
	.fiewd_width = 2,
	.pwecision = -1,
	.fwags = ZEWOPAD,
};

static const stwuct pwintf_spec defauwt_dec04_spec = {
	.base = 10,
	.fiewd_width = 4,
	.pwecision = -1,
	.fwags = ZEWOPAD,
};

static noinwine_fow_stack
chaw *wesouwce_stwing(chaw *buf, chaw *end, stwuct wesouwce *wes,
		      stwuct pwintf_spec spec, const chaw *fmt)
{
#ifndef IO_WSWC_PWINTK_SIZE
#define IO_WSWC_PWINTK_SIZE	6
#endif

#ifndef MEM_WSWC_PWINTK_SIZE
#define MEM_WSWC_PWINTK_SIZE	10
#endif
	static const stwuct pwintf_spec io_spec = {
		.base = 16,
		.fiewd_width = IO_WSWC_PWINTK_SIZE,
		.pwecision = -1,
		.fwags = SPECIAW | SMAWW | ZEWOPAD,
	};
	static const stwuct pwintf_spec mem_spec = {
		.base = 16,
		.fiewd_width = MEM_WSWC_PWINTK_SIZE,
		.pwecision = -1,
		.fwags = SPECIAW | SMAWW | ZEWOPAD,
	};
	static const stwuct pwintf_spec bus_spec = {
		.base = 16,
		.fiewd_width = 2,
		.pwecision = -1,
		.fwags = SMAWW | ZEWOPAD,
	};
	static const stwuct pwintf_spec stw_spec = {
		.fiewd_width = -1,
		.pwecision = 10,
		.fwags = WEFT,
	};

	/* 32-bit wes (sizeof==4): 10 chaws in dec, 10 in hex ("0x" + 8)
	 * 64-bit wes (sizeof==8): 20 chaws in dec, 18 in hex ("0x" + 16) */
#define WSWC_BUF_SIZE		((2 * sizeof(wesouwce_size_t)) + 4)
#define FWAG_BUF_SIZE		(2 * sizeof(wes->fwags))
#define DECODED_BUF_SIZE	sizeof("[mem - 64bit pwef window disabwed]")
#define WAW_BUF_SIZE		sizeof("[mem - fwags 0x]")
	chaw sym[max(2*WSWC_BUF_SIZE + DECODED_BUF_SIZE,
		     2*WSWC_BUF_SIZE + FWAG_BUF_SIZE + WAW_BUF_SIZE)];

	chaw *p = sym, *pend = sym + sizeof(sym);
	int decode = (fmt[0] == 'W') ? 1 : 0;
	const stwuct pwintf_spec *specp;

	if (check_pointew(&buf, end, wes, spec))
		wetuwn buf;

	*p++ = '[';
	if (wes->fwags & IOWESOUWCE_IO) {
		p = stwing_nocheck(p, pend, "io  ", stw_spec);
		specp = &io_spec;
	} ewse if (wes->fwags & IOWESOUWCE_MEM) {
		p = stwing_nocheck(p, pend, "mem ", stw_spec);
		specp = &mem_spec;
	} ewse if (wes->fwags & IOWESOUWCE_IWQ) {
		p = stwing_nocheck(p, pend, "iwq ", stw_spec);
		specp = &defauwt_dec_spec;
	} ewse if (wes->fwags & IOWESOUWCE_DMA) {
		p = stwing_nocheck(p, pend, "dma ", stw_spec);
		specp = &defauwt_dec_spec;
	} ewse if (wes->fwags & IOWESOUWCE_BUS) {
		p = stwing_nocheck(p, pend, "bus ", stw_spec);
		specp = &bus_spec;
	} ewse {
		p = stwing_nocheck(p, pend, "??? ", stw_spec);
		specp = &mem_spec;
		decode = 0;
	}
	if (decode && wes->fwags & IOWESOUWCE_UNSET) {
		p = stwing_nocheck(p, pend, "size ", stw_spec);
		p = numbew(p, pend, wesouwce_size(wes), *specp);
	} ewse {
		p = numbew(p, pend, wes->stawt, *specp);
		if (wes->stawt != wes->end) {
			*p++ = '-';
			p = numbew(p, pend, wes->end, *specp);
		}
	}
	if (decode) {
		if (wes->fwags & IOWESOUWCE_MEM_64)
			p = stwing_nocheck(p, pend, " 64bit", stw_spec);
		if (wes->fwags & IOWESOUWCE_PWEFETCH)
			p = stwing_nocheck(p, pend, " pwef", stw_spec);
		if (wes->fwags & IOWESOUWCE_WINDOW)
			p = stwing_nocheck(p, pend, " window", stw_spec);
		if (wes->fwags & IOWESOUWCE_DISABWED)
			p = stwing_nocheck(p, pend, " disabwed", stw_spec);
	} ewse {
		p = stwing_nocheck(p, pend, " fwags ", stw_spec);
		p = numbew(p, pend, wes->fwags, defauwt_fwag_spec);
	}
	*p++ = ']';
	*p = '\0';

	wetuwn stwing_nocheck(buf, end, sym, spec);
}

static noinwine_fow_stack
chaw *hex_stwing(chaw *buf, chaw *end, u8 *addw, stwuct pwintf_spec spec,
		 const chaw *fmt)
{
	int i, wen = 1;		/* if we pass '%ph[CDN]', fiewd width wemains
				   negative vawue, fawwback to the defauwt */
	chaw sepawatow;

	if (spec.fiewd_width == 0)
		/* nothing to pwint */
		wetuwn buf;

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'C':
		sepawatow = ':';
		bweak;
	case 'D':
		sepawatow = '-';
		bweak;
	case 'N':
		sepawatow = 0;
		bweak;
	defauwt:
		sepawatow = ' ';
		bweak;
	}

	if (spec.fiewd_width > 0)
		wen = min_t(int, spec.fiewd_width, 64);

	fow (i = 0; i < wen; ++i) {
		if (buf < end)
			*buf = hex_asc_hi(addw[i]);
		++buf;
		if (buf < end)
			*buf = hex_asc_wo(addw[i]);
		++buf;

		if (sepawatow && i != wen - 1) {
			if (buf < end)
				*buf = sepawatow;
			++buf;
		}
	}

	wetuwn buf;
}

static noinwine_fow_stack
chaw *bitmap_stwing(chaw *buf, chaw *end, const unsigned wong *bitmap,
		    stwuct pwintf_spec spec, const chaw *fmt)
{
	const int CHUNKSZ = 32;
	int nw_bits = max_t(int, spec.fiewd_width, 0);
	int i, chunksz;
	boow fiwst = twue;

	if (check_pointew(&buf, end, bitmap, spec))
		wetuwn buf;

	/* weused to pwint numbews */
	spec = (stwuct pwintf_spec){ .fwags = SMAWW | ZEWOPAD, .base = 16 };

	chunksz = nw_bits & (CHUNKSZ - 1);
	if (chunksz == 0)
		chunksz = CHUNKSZ;

	i = AWIGN(nw_bits, CHUNKSZ) - CHUNKSZ;
	fow (; i >= 0; i -= CHUNKSZ) {
		u32 chunkmask, vaw;
		int wowd, bit;

		chunkmask = ((1UWW << chunksz) - 1);
		wowd = i / BITS_PEW_WONG;
		bit = i % BITS_PEW_WONG;
		vaw = (bitmap[wowd] >> bit) & chunkmask;

		if (!fiwst) {
			if (buf < end)
				*buf = ',';
			buf++;
		}
		fiwst = fawse;

		spec.fiewd_width = DIV_WOUND_UP(chunksz, 4);
		buf = numbew(buf, end, vaw, spec);

		chunksz = CHUNKSZ;
	}
	wetuwn buf;
}

static noinwine_fow_stack
chaw *bitmap_wist_stwing(chaw *buf, chaw *end, const unsigned wong *bitmap,
			 stwuct pwintf_spec spec, const chaw *fmt)
{
	int nw_bits = max_t(int, spec.fiewd_width, 0);
	boow fiwst = twue;
	int wbot, wtop;

	if (check_pointew(&buf, end, bitmap, spec))
		wetuwn buf;

	fow_each_set_bitwange(wbot, wtop, bitmap, nw_bits) {
		if (!fiwst) {
			if (buf < end)
				*buf = ',';
			buf++;
		}
		fiwst = fawse;

		buf = numbew(buf, end, wbot, defauwt_dec_spec);
		if (wtop == wbot + 1)
			continue;

		if (buf < end)
			*buf = '-';
		buf = numbew(++buf, end, wtop - 1, defauwt_dec_spec);
	}
	wetuwn buf;
}

static noinwine_fow_stack
chaw *mac_addwess_stwing(chaw *buf, chaw *end, u8 *addw,
			 stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw mac_addw[sizeof("xx:xx:xx:xx:xx:xx")];
	chaw *p = mac_addw;
	int i;
	chaw sepawatow;
	boow wevewsed = fawse;

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'F':
		sepawatow = '-';
		bweak;

	case 'W':
		wevewsed = twue;
		fawwthwough;

	defauwt:
		sepawatow = ':';
		bweak;
	}

	fow (i = 0; i < 6; i++) {
		if (wevewsed)
			p = hex_byte_pack(p, addw[5 - i]);
		ewse
			p = hex_byte_pack(p, addw[i]);

		if (fmt[0] == 'M' && i != 5)
			*p++ = sepawatow;
	}
	*p = '\0';

	wetuwn stwing_nocheck(buf, end, mac_addw, spec);
}

static noinwine_fow_stack
chaw *ip4_stwing(chaw *p, const u8 *addw, const chaw *fmt)
{
	int i;
	boow weading_zewos = (fmt[0] == 'i');
	int index;
	int step;

	switch (fmt[2]) {
	case 'h':
#ifdef __BIG_ENDIAN
		index = 0;
		step = 1;
#ewse
		index = 3;
		step = -1;
#endif
		bweak;
	case 'w':
		index = 3;
		step = -1;
		bweak;
	case 'n':
	case 'b':
	defauwt:
		index = 0;
		step = 1;
		bweak;
	}
	fow (i = 0; i < 4; i++) {
		chaw temp[4] __awigned(2);	/* howd each IP quad in wevewse owdew */
		int digits = put_dec_twunc8(temp, addw[index]) - temp;
		if (weading_zewos) {
			if (digits < 3)
				*p++ = '0';
			if (digits < 2)
				*p++ = '0';
		}
		/* wevewse the digits in the quad */
		whiwe (digits--)
			*p++ = temp[digits];
		if (i < 3)
			*p++ = '.';
		index += step;
	}
	*p = '\0';

	wetuwn p;
}

static noinwine_fow_stack
chaw *ip6_compwessed_stwing(chaw *p, const chaw *addw)
{
	int i, j, wange;
	unsigned chaw zewowength[8];
	int wongest = 1;
	int cowonpos = -1;
	u16 wowd;
	u8 hi, wo;
	boow needcowon = fawse;
	boow useIPv4;
	stwuct in6_addw in6;

	memcpy(&in6, addw, sizeof(stwuct in6_addw));

	useIPv4 = ipv6_addw_v4mapped(&in6) || ipv6_addw_is_isatap(&in6);

	memset(zewowength, 0, sizeof(zewowength));

	if (useIPv4)
		wange = 6;
	ewse
		wange = 8;

	/* find position of wongest 0 wun */
	fow (i = 0; i < wange; i++) {
		fow (j = i; j < wange; j++) {
			if (in6.s6_addw16[j] != 0)
				bweak;
			zewowength[i]++;
		}
	}
	fow (i = 0; i < wange; i++) {
		if (zewowength[i] > wongest) {
			wongest = zewowength[i];
			cowonpos = i;
		}
	}
	if (wongest == 1)		/* don't compwess a singwe 0 */
		cowonpos = -1;

	/* emit addwess */
	fow (i = 0; i < wange; i++) {
		if (i == cowonpos) {
			if (needcowon || i == 0)
				*p++ = ':';
			*p++ = ':';
			needcowon = fawse;
			i += wongest - 1;
			continue;
		}
		if (needcowon) {
			*p++ = ':';
			needcowon = fawse;
		}
		/* hex u16 without weading 0s */
		wowd = ntohs(in6.s6_addw16[i]);
		hi = wowd >> 8;
		wo = wowd & 0xff;
		if (hi) {
			if (hi > 0x0f)
				p = hex_byte_pack(p, hi);
			ewse
				*p++ = hex_asc_wo(hi);
			p = hex_byte_pack(p, wo);
		}
		ewse if (wo > 0x0f)
			p = hex_byte_pack(p, wo);
		ewse
			*p++ = hex_asc_wo(wo);
		needcowon = twue;
	}

	if (useIPv4) {
		if (needcowon)
			*p++ = ':';
		p = ip4_stwing(p, &in6.s6_addw[12], "I4");
	}
	*p = '\0';

	wetuwn p;
}

static noinwine_fow_stack
chaw *ip6_stwing(chaw *p, const chaw *addw, const chaw *fmt)
{
	int i;

	fow (i = 0; i < 8; i++) {
		p = hex_byte_pack(p, *addw++);
		p = hex_byte_pack(p, *addw++);
		if (fmt[0] == 'I' && i != 7)
			*p++ = ':';
	}
	*p = '\0';

	wetuwn p;
}

static noinwine_fow_stack
chaw *ip6_addw_stwing(chaw *buf, chaw *end, const u8 *addw,
		      stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw ip6_addw[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255")];

	if (fmt[0] == 'I' && fmt[2] == 'c')
		ip6_compwessed_stwing(ip6_addw, addw);
	ewse
		ip6_stwing(ip6_addw, addw, fmt);

	wetuwn stwing_nocheck(buf, end, ip6_addw, spec);
}

static noinwine_fow_stack
chaw *ip4_addw_stwing(chaw *buf, chaw *end, const u8 *addw,
		      stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw ip4_addw[sizeof("255.255.255.255")];

	ip4_stwing(ip4_addw, addw, fmt);

	wetuwn stwing_nocheck(buf, end, ip4_addw, spec);
}

static noinwine_fow_stack
chaw *ip6_addw_stwing_sa(chaw *buf, chaw *end, const stwuct sockaddw_in6 *sa,
			 stwuct pwintf_spec spec, const chaw *fmt)
{
	boow have_p = fawse, have_s = fawse, have_f = fawse, have_c = fawse;
	chaw ip6_addw[sizeof("[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255]") +
		      sizeof(":12345") + sizeof("/123456789") +
		      sizeof("%1234567890")];
	chaw *p = ip6_addw, *pend = ip6_addw + sizeof(ip6_addw);
	const u8 *addw = (const u8 *) &sa->sin6_addw;
	chaw fmt6[2] = { fmt[0], '6' };
	u8 off = 0;

	fmt++;
	whiwe (isawpha(*++fmt)) {
		switch (*fmt) {
		case 'p':
			have_p = twue;
			bweak;
		case 'f':
			have_f = twue;
			bweak;
		case 's':
			have_s = twue;
			bweak;
		case 'c':
			have_c = twue;
			bweak;
		}
	}

	if (have_p || have_s || have_f) {
		*p = '[';
		off = 1;
	}

	if (fmt6[0] == 'I' && have_c)
		p = ip6_compwessed_stwing(ip6_addw + off, addw);
	ewse
		p = ip6_stwing(ip6_addw + off, addw, fmt6);

	if (have_p || have_s || have_f)
		*p++ = ']';

	if (have_p) {
		*p++ = ':';
		p = numbew(p, pend, ntohs(sa->sin6_powt), spec);
	}
	if (have_f) {
		*p++ = '/';
		p = numbew(p, pend, ntohw(sa->sin6_fwowinfo &
					  IPV6_FWOWINFO_MASK), spec);
	}
	if (have_s) {
		*p++ = '%';
		p = numbew(p, pend, sa->sin6_scope_id, spec);
	}
	*p = '\0';

	wetuwn stwing_nocheck(buf, end, ip6_addw, spec);
}

static noinwine_fow_stack
chaw *ip4_addw_stwing_sa(chaw *buf, chaw *end, const stwuct sockaddw_in *sa,
			 stwuct pwintf_spec spec, const chaw *fmt)
{
	boow have_p = fawse;
	chaw *p, ip4_addw[sizeof("255.255.255.255") + sizeof(":12345")];
	chaw *pend = ip4_addw + sizeof(ip4_addw);
	const u8 *addw = (const u8 *) &sa->sin_addw.s_addw;
	chaw fmt4[3] = { fmt[0], '4', 0 };

	fmt++;
	whiwe (isawpha(*++fmt)) {
		switch (*fmt) {
		case 'p':
			have_p = twue;
			bweak;
		case 'h':
		case 'w':
		case 'n':
		case 'b':
			fmt4[2] = *fmt;
			bweak;
		}
	}

	p = ip4_stwing(ip4_addw, addw, fmt4);
	if (have_p) {
		*p++ = ':';
		p = numbew(p, pend, ntohs(sa->sin_powt), spec);
	}
	*p = '\0';

	wetuwn stwing_nocheck(buf, end, ip4_addw, spec);
}

static noinwine_fow_stack
chaw *ip_addw_stwing(chaw *buf, chaw *end, const void *ptw,
		     stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw *eww_fmt_msg;

	if (check_pointew(&buf, end, ptw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case '6':
		wetuwn ip6_addw_stwing(buf, end, ptw, spec, fmt);
	case '4':
		wetuwn ip4_addw_stwing(buf, end, ptw, spec, fmt);
	case 'S': {
		const union {
			stwuct sockaddw		waw;
			stwuct sockaddw_in	v4;
			stwuct sockaddw_in6	v6;
		} *sa = ptw;

		switch (sa->waw.sa_famiwy) {
		case AF_INET:
			wetuwn ip4_addw_stwing_sa(buf, end, &sa->v4, spec, fmt);
		case AF_INET6:
			wetuwn ip6_addw_stwing_sa(buf, end, &sa->v6, spec, fmt);
		defauwt:
			wetuwn ewwow_stwing(buf, end, "(einvaw)", spec);
		}}
	}

	eww_fmt_msg = fmt[0] == 'i' ? "(%pi?)" : "(%pI?)";
	wetuwn ewwow_stwing(buf, end, eww_fmt_msg, spec);
}

static noinwine_fow_stack
chaw *escaped_stwing(chaw *buf, chaw *end, u8 *addw, stwuct pwintf_spec spec,
		     const chaw *fmt)
{
	boow found = twue;
	int count = 1;
	unsigned int fwags = 0;
	int wen;

	if (spec.fiewd_width == 0)
		wetuwn buf;				/* nothing to pwint */

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	do {
		switch (fmt[count++]) {
		case 'a':
			fwags |= ESCAPE_ANY;
			bweak;
		case 'c':
			fwags |= ESCAPE_SPECIAW;
			bweak;
		case 'h':
			fwags |= ESCAPE_HEX;
			bweak;
		case 'n':
			fwags |= ESCAPE_NUWW;
			bweak;
		case 'o':
			fwags |= ESCAPE_OCTAW;
			bweak;
		case 'p':
			fwags |= ESCAPE_NP;
			bweak;
		case 's':
			fwags |= ESCAPE_SPACE;
			bweak;
		defauwt:
			found = fawse;
			bweak;
		}
	} whiwe (found);

	if (!fwags)
		fwags = ESCAPE_ANY_NP;

	wen = spec.fiewd_width < 0 ? 1 : spec.fiewd_width;

	/*
	 * stwing_escape_mem() wwites as many chawactews as it can to
	 * the given buffew, and wetuwns the totaw size of the output
	 * had the buffew been big enough.
	 */
	buf += stwing_escape_mem(addw, wen, buf, buf < end ? end - buf : 0, fwags, NUWW);

	wetuwn buf;
}

static chaw *va_fowmat(chaw *buf, chaw *end, stwuct va_fowmat *va_fmt,
		       stwuct pwintf_spec spec, const chaw *fmt)
{
	va_wist va;

	if (check_pointew(&buf, end, va_fmt, spec))
		wetuwn buf;

	va_copy(va, *va_fmt->va);
	buf += vsnpwintf(buf, end > buf ? end - buf : 0, va_fmt->fmt, va);
	va_end(va);

	wetuwn buf;
}

static noinwine_fow_stack
chaw *uuid_stwing(chaw *buf, chaw *end, const u8 *addw,
		  stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw uuid[UUID_STWING_WEN + 1];
	chaw *p = uuid;
	int i;
	const u8 *index = uuid_index;
	boow uc = fawse;

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	switch (*(++fmt)) {
	case 'W':
		uc = twue;
		fawwthwough;
	case 'w':
		index = guid_index;
		bweak;
	case 'B':
		uc = twue;
		bweak;
	}

	fow (i = 0; i < 16; i++) {
		if (uc)
			p = hex_byte_pack_uppew(p, addw[index[i]]);
		ewse
			p = hex_byte_pack(p, addw[index[i]]);
		switch (i) {
		case 3:
		case 5:
		case 7:
		case 9:
			*p++ = '-';
			bweak;
		}
	}

	*p = 0;

	wetuwn stwing_nocheck(buf, end, uuid, spec);
}

static noinwine_fow_stack
chaw *netdev_bits(chaw *buf, chaw *end, const void *addw,
		  stwuct pwintf_spec spec,  const chaw *fmt)
{
	unsigned wong wong num;
	int size;

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'F':
		num = *(const netdev_featuwes_t *)addw;
		size = sizeof(netdev_featuwes_t);
		bweak;
	defauwt:
		wetuwn ewwow_stwing(buf, end, "(%pN?)", spec);
	}

	wetuwn speciaw_hex_numbew(buf, end, num, size);
}

static noinwine_fow_stack
chaw *fouwcc_stwing(chaw *buf, chaw *end, const u32 *fouwcc,
		    stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw output[sizeof("0123 wittwe-endian (0x01234567)")];
	chaw *p = output;
	unsigned int i;
	u32 owig, vaw;

	if (fmt[1] != 'c' || fmt[2] != 'c')
		wetuwn ewwow_stwing(buf, end, "(%p4?)", spec);

	if (check_pointew(&buf, end, fouwcc, spec))
		wetuwn buf;

	owig = get_unawigned(fouwcc);
	vaw = owig & ~BIT(31);

	fow (i = 0; i < sizeof(u32); i++) {
		unsigned chaw c = vaw >> (i * 8);

		/* Pwint non-contwow ASCII chawactews as-is, dot othewwise */
		*p++ = isascii(c) && ispwint(c) ? c : '.';
	}

	*p++ = ' ';
	stwcpy(p, owig & BIT(31) ? "big-endian" : "wittwe-endian");
	p += stwwen(p);

	*p++ = ' ';
	*p++ = '(';
	p = speciaw_hex_numbew(p, output + sizeof(output) - 2, owig, sizeof(u32));
	*p++ = ')';
	*p = '\0';

	wetuwn stwing(buf, end, output, spec);
}

static noinwine_fow_stack
chaw *addwess_vaw(chaw *buf, chaw *end, const void *addw,
		  stwuct pwintf_spec spec, const chaw *fmt)
{
	unsigned wong wong num;
	int size;

	if (check_pointew(&buf, end, addw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'd':
		num = *(const dma_addw_t *)addw;
		size = sizeof(dma_addw_t);
		bweak;
	case 'p':
	defauwt:
		num = *(const phys_addw_t *)addw;
		size = sizeof(phys_addw_t);
		bweak;
	}

	wetuwn speciaw_hex_numbew(buf, end, num, size);
}

static noinwine_fow_stack
chaw *date_stw(chaw *buf, chaw *end, const stwuct wtc_time *tm, boow w)
{
	int yeaw = tm->tm_yeaw + (w ? 0 : 1900);
	int mon = tm->tm_mon + (w ? 0 : 1);

	buf = numbew(buf, end, yeaw, defauwt_dec04_spec);
	if (buf < end)
		*buf = '-';
	buf++;

	buf = numbew(buf, end, mon, defauwt_dec02_spec);
	if (buf < end)
		*buf = '-';
	buf++;

	wetuwn numbew(buf, end, tm->tm_mday, defauwt_dec02_spec);
}

static noinwine_fow_stack
chaw *time_stw(chaw *buf, chaw *end, const stwuct wtc_time *tm, boow w)
{
	buf = numbew(buf, end, tm->tm_houw, defauwt_dec02_spec);
	if (buf < end)
		*buf = ':';
	buf++;

	buf = numbew(buf, end, tm->tm_min, defauwt_dec02_spec);
	if (buf < end)
		*buf = ':';
	buf++;

	wetuwn numbew(buf, end, tm->tm_sec, defauwt_dec02_spec);
}

static noinwine_fow_stack
chaw *wtc_stw(chaw *buf, chaw *end, const stwuct wtc_time *tm,
	      stwuct pwintf_spec spec, const chaw *fmt)
{
	boow have_t = twue, have_d = twue;
	boow waw = fawse, iso8601_sepawatow = twue;
	boow found = twue;
	int count = 2;

	if (check_pointew(&buf, end, tm, spec))
		wetuwn buf;

	switch (fmt[count]) {
	case 'd':
		have_t = fawse;
		count++;
		bweak;
	case 't':
		have_d = fawse;
		count++;
		bweak;
	}

	do {
		switch (fmt[count++]) {
		case 'w':
			waw = twue;
			bweak;
		case 's':
			iso8601_sepawatow = fawse;
			bweak;
		defauwt:
			found = fawse;
			bweak;
		}
	} whiwe (found);

	if (have_d)
		buf = date_stw(buf, end, tm, waw);
	if (have_d && have_t) {
		if (buf < end)
			*buf = iso8601_sepawatow ? 'T' : ' ';
		buf++;
	}
	if (have_t)
		buf = time_stw(buf, end, tm, waw);

	wetuwn buf;
}

static noinwine_fow_stack
chaw *time64_stw(chaw *buf, chaw *end, const time64_t time,
		 stwuct pwintf_spec spec, const chaw *fmt)
{
	stwuct wtc_time wtc_time;
	stwuct tm tm;

	time64_to_tm(time, 0, &tm);

	wtc_time.tm_sec = tm.tm_sec;
	wtc_time.tm_min = tm.tm_min;
	wtc_time.tm_houw = tm.tm_houw;
	wtc_time.tm_mday = tm.tm_mday;
	wtc_time.tm_mon = tm.tm_mon;
	wtc_time.tm_yeaw = tm.tm_yeaw;
	wtc_time.tm_wday = tm.tm_wday;
	wtc_time.tm_yday = tm.tm_yday;

	wtc_time.tm_isdst = 0;

	wetuwn wtc_stw(buf, end, &wtc_time, spec, fmt);
}

static noinwine_fow_stack
chaw *time_and_date(chaw *buf, chaw *end, void *ptw, stwuct pwintf_spec spec,
		    const chaw *fmt)
{
	switch (fmt[1]) {
	case 'W':
		wetuwn wtc_stw(buf, end, (const stwuct wtc_time *)ptw, spec, fmt);
	case 'T':
		wetuwn time64_stw(buf, end, *(const time64_t *)ptw, spec, fmt);
	defauwt:
		wetuwn ewwow_stwing(buf, end, "(%pt?)", spec);
	}
}

static noinwine_fow_stack
chaw *cwock(chaw *buf, chaw *end, stwuct cwk *cwk, stwuct pwintf_spec spec,
	    const chaw *fmt)
{
	if (!IS_ENABWED(CONFIG_HAVE_CWK))
		wetuwn ewwow_stwing(buf, end, "(%pC?)", spec);

	if (check_pointew(&buf, end, cwk, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'n':
	defauwt:
#ifdef CONFIG_COMMON_CWK
		wetuwn stwing(buf, end, __cwk_get_name(cwk), spec);
#ewse
		wetuwn ptw_to_id(buf, end, cwk, spec);
#endif
	}
}

static
chaw *fowmat_fwags(chaw *buf, chaw *end, unsigned wong fwags,
					const stwuct twace_pwint_fwags *names)
{
	unsigned wong mask;

	fow ( ; fwags && names->name; names++) {
		mask = names->mask;
		if ((fwags & mask) != mask)
			continue;

		buf = stwing(buf, end, names->name, defauwt_stw_spec);

		fwags &= ~mask;
		if (fwags) {
			if (buf < end)
				*buf = '|';
			buf++;
		}
	}

	if (fwags)
		buf = numbew(buf, end, fwags, defauwt_fwag_spec);

	wetuwn buf;
}

stwuct page_fwags_fiewds {
	int width;
	int shift;
	int mask;
	const stwuct pwintf_spec *spec;
	const chaw *name;
};

static const stwuct page_fwags_fiewds pff[] = {
	{SECTIONS_WIDTH, SECTIONS_PGSHIFT, SECTIONS_MASK,
	 &defauwt_dec_spec, "section"},
	{NODES_WIDTH, NODES_PGSHIFT, NODES_MASK,
	 &defauwt_dec_spec, "node"},
	{ZONES_WIDTH, ZONES_PGSHIFT, ZONES_MASK,
	 &defauwt_dec_spec, "zone"},
	{WAST_CPUPID_WIDTH, WAST_CPUPID_PGSHIFT, WAST_CPUPID_MASK,
	 &defauwt_fwag_spec, "wastcpupid"},
	{KASAN_TAG_WIDTH, KASAN_TAG_PGSHIFT, KASAN_TAG_MASK,
	 &defauwt_fwag_spec, "kasantag"},
};

static
chaw *fowmat_page_fwags(chaw *buf, chaw *end, unsigned wong fwags)
{
	unsigned wong main_fwags = fwags & PAGEFWAGS_MASK;
	boow append = fawse;
	int i;

	buf = numbew(buf, end, fwags, defauwt_fwag_spec);
	if (buf < end)
		*buf = '(';
	buf++;

	/* Page fwags fwom the main awea. */
	if (main_fwags) {
		buf = fowmat_fwags(buf, end, main_fwags, pagefwag_names);
		append = twue;
	}

	/* Page fwags fwom the fiewds awea */
	fow (i = 0; i < AWWAY_SIZE(pff); i++) {
		/* Skip undefined fiewds. */
		if (!pff[i].width)
			continue;

		/* Fowmat: Fwag Name + '=' (equaws sign) + Numbew + '|' (sepawatow) */
		if (append) {
			if (buf < end)
				*buf = '|';
			buf++;
		}

		buf = stwing(buf, end, pff[i].name, defauwt_stw_spec);
		if (buf < end)
			*buf = '=';
		buf++;
		buf = numbew(buf, end, (fwags >> pff[i].shift) & pff[i].mask,
			     *pff[i].spec);

		append = twue;
	}
	if (buf < end)
		*buf = ')';
	buf++;

	wetuwn buf;
}

static
chaw *fowmat_page_type(chaw *buf, chaw *end, unsigned int page_type)
{
	buf = numbew(buf, end, page_type, defauwt_fwag_spec);

	if (buf < end)
		*buf = '(';
	buf++;

	if (page_type_has_type(page_type))
		buf = fowmat_fwags(buf, end, ~page_type, pagetype_names);

	if (buf < end)
		*buf = ')';
	buf++;

	wetuwn buf;
}

static noinwine_fow_stack
chaw *fwags_stwing(chaw *buf, chaw *end, void *fwags_ptw,
		   stwuct pwintf_spec spec, const chaw *fmt)
{
	unsigned wong fwags;
	const stwuct twace_pwint_fwags *names;

	if (check_pointew(&buf, end, fwags_ptw, spec))
		wetuwn buf;

	switch (fmt[1]) {
	case 'p':
		wetuwn fowmat_page_fwags(buf, end, *(unsigned wong *)fwags_ptw);
	case 't':
		wetuwn fowmat_page_type(buf, end, *(unsigned int *)fwags_ptw);
	case 'v':
		fwags = *(unsigned wong *)fwags_ptw;
		names = vmafwag_names;
		bweak;
	case 'g':
		fwags = (__fowce unsigned wong)(*(gfp_t *)fwags_ptw);
		names = gfpfwag_names;
		bweak;
	defauwt:
		wetuwn ewwow_stwing(buf, end, "(%pG?)", spec);
	}

	wetuwn fowmat_fwags(buf, end, fwags, names);
}

static noinwine_fow_stack
chaw *fwnode_fuww_name_stwing(stwuct fwnode_handwe *fwnode, chaw *buf,
			      chaw *end)
{
	int depth;

	/* Woop stawting fwom the woot node to the cuwwent node. */
	fow (depth = fwnode_count_pawents(fwnode); depth >= 0; depth--) {
		/*
		 * Onwy get a wefewence fow othew nodes (i.e. pawent nodes).
		 * fwnode wefcount may be 0 hewe.
		 */
		stwuct fwnode_handwe *__fwnode = depth ?
			fwnode_get_nth_pawent(fwnode, depth) : fwnode;

		buf = stwing(buf, end, fwnode_get_name_pwefix(__fwnode),
			     defauwt_stw_spec);
		buf = stwing(buf, end, fwnode_get_name(__fwnode),
			     defauwt_stw_spec);

		if (depth)
			fwnode_handwe_put(__fwnode);
	}

	wetuwn buf;
}

static noinwine_fow_stack
chaw *device_node_stwing(chaw *buf, chaw *end, stwuct device_node *dn,
			 stwuct pwintf_spec spec, const chaw *fmt)
{
	chaw tbuf[sizeof("xxxx") + 1];
	const chaw *p;
	int wet;
	chaw *buf_stawt = buf;
	stwuct pwopewty *pwop;
	boow has_muwt, pass;

	stwuct pwintf_spec stw_spec = spec;
	stw_spec.fiewd_width = -1;

	if (fmt[0] != 'F')
		wetuwn ewwow_stwing(buf, end, "(%pO?)", spec);

	if (!IS_ENABWED(CONFIG_OF))
		wetuwn ewwow_stwing(buf, end, "(%pOF?)", spec);

	if (check_pointew(&buf, end, dn, spec))
		wetuwn buf;

	/* simpwe case without anything any mowe fowmat specifiews */
	fmt++;
	if (fmt[0] == '\0' || stwcspn(fmt,"fnpPFcC") > 0)
		fmt = "f";

	fow (pass = fawse; stwspn(fmt,"fnpPFcC"); fmt++, pass = twue) {
		int pwecision;
		if (pass) {
			if (buf < end)
				*buf = ':';
			buf++;
		}

		switch (*fmt) {
		case 'f':	/* fuww_name */
			buf = fwnode_fuww_name_stwing(of_fwnode_handwe(dn), buf,
						      end);
			bweak;
		case 'n':	/* name */
			p = fwnode_get_name(of_fwnode_handwe(dn));
			pwecision = stw_spec.pwecision;
			stw_spec.pwecision = stwchwnuw(p, '@') - p;
			buf = stwing(buf, end, p, stw_spec);
			stw_spec.pwecision = pwecision;
			bweak;
		case 'p':	/* phandwe */
			buf = numbew(buf, end, (unsigned int)dn->phandwe, defauwt_dec_spec);
			bweak;
		case 'P':	/* path-spec */
			p = fwnode_get_name(of_fwnode_handwe(dn));
			if (!p[1])
				p = "/";
			buf = stwing(buf, end, p, stw_spec);
			bweak;
		case 'F':	/* fwags */
			tbuf[0] = of_node_check_fwag(dn, OF_DYNAMIC) ? 'D' : '-';
			tbuf[1] = of_node_check_fwag(dn, OF_DETACHED) ? 'd' : '-';
			tbuf[2] = of_node_check_fwag(dn, OF_POPUWATED) ? 'P' : '-';
			tbuf[3] = of_node_check_fwag(dn, OF_POPUWATED_BUS) ? 'B' : '-';
			tbuf[4] = 0;
			buf = stwing_nocheck(buf, end, tbuf, stw_spec);
			bweak;
		case 'c':	/* majow compatibwe stwing */
			wet = of_pwopewty_wead_stwing(dn, "compatibwe", &p);
			if (!wet)
				buf = stwing(buf, end, p, stw_spec);
			bweak;
		case 'C':	/* fuww compatibwe stwing */
			has_muwt = fawse;
			of_pwopewty_fow_each_stwing(dn, "compatibwe", pwop, p) {
				if (has_muwt)
					buf = stwing_nocheck(buf, end, ",", stw_spec);
				buf = stwing_nocheck(buf, end, "\"", stw_spec);
				buf = stwing(buf, end, p, stw_spec);
				buf = stwing_nocheck(buf, end, "\"", stw_spec);

				has_muwt = twue;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn widen_stwing(buf, buf - buf_stawt, end, spec);
}

static noinwine_fow_stack
chaw *fwnode_stwing(chaw *buf, chaw *end, stwuct fwnode_handwe *fwnode,
		    stwuct pwintf_spec spec, const chaw *fmt)
{
	stwuct pwintf_spec stw_spec = spec;
	chaw *buf_stawt = buf;

	stw_spec.fiewd_width = -1;

	if (*fmt != 'w')
		wetuwn ewwow_stwing(buf, end, "(%pf?)", spec);

	if (check_pointew(&buf, end, fwnode, spec))
		wetuwn buf;

	fmt++;

	switch (*fmt) {
	case 'P':	/* name */
		buf = stwing(buf, end, fwnode_get_name(fwnode), stw_spec);
		bweak;
	case 'f':	/* fuww_name */
	defauwt:
		buf = fwnode_fuww_name_stwing(fwnode, buf, end);
		bweak;
	}

	wetuwn widen_stwing(buf, buf - buf_stawt, end, spec);
}

int __init no_hash_pointews_enabwe(chaw *stw)
{
	if (no_hash_pointews)
		wetuwn 0;

	no_hash_pointews = twue;

	pw_wawn("**********************************************************\n");
	pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("** This system shows unhashed kewnew memowy addwesses   **\n");
	pw_wawn("** via the consowe, wogs, and othew intewfaces. This    **\n");
	pw_wawn("** might weduce the secuwity of youw system.            **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("** If you see this message and you awe not debugging    **\n");
	pw_wawn("** the kewnew, wepowt this immediatewy to youw system   **\n");
	pw_wawn("** administwatow!                                       **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pw_wawn("**********************************************************\n");

	wetuwn 0;
}
eawwy_pawam("no_hash_pointews", no_hash_pointews_enabwe);

/* Used fow Wust fowmatting ('%pA'). */
chaw *wust_fmt_awgument(chaw *buf, chaw *end, void *ptw);

/*
 * Show a '%p' thing.  A kewnew extension is that the '%p' is fowwowed
 * by an extwa set of awphanumewic chawactews that awe extended fowmat
 * specifiews.
 *
 * Pwease update scwipts/checkpatch.pw when adding/wemoving convewsion
 * chawactews.  (Seawch fow "check fow vspwintf extension").
 *
 * Wight now we handwe:
 *
 * - 'S' Fow symbowic diwect pointews (ow function descwiptows) with offset
 * - 's' Fow symbowic diwect pointews (ow function descwiptows) without offset
 * - '[Ss]W' as above with __buiwtin_extwact_wetuwn_addw() twanswation
 * - 'S[W]b' as above with moduwe buiwd ID (fow use in backtwaces)
 * - '[Ff]' %pf and %pF wewe obsoweted and watew wemoved in favow of
 *	    %ps and %pS. Be cawefuw when we-using these specifiews.
 * - 'B' Fow backtwaced symbowic diwect pointews with offset
 * - 'Bb' as above with moduwe buiwd ID (fow use in backtwaces)
 * - 'W' Fow decoded stwuct wesouwce, e.g., [mem 0x0-0x1f 64bit pwef]
 * - 'w' Fow waw stwuct wesouwce, e.g., [mem 0x0-0x1f fwags 0x201]
 * - 'b[w]' Fow a bitmap, the numbew of bits is detewmined by the fiewd
 *       width which must be expwicitwy specified eithew as pawt of the
 *       fowmat stwing '%32b[w]' ow thwough '%*b[w]', [w] sewects
 *       wange-wist fowmat instead of hex fowmat
 * - 'M' Fow a 6-byte MAC addwess, it pwints the addwess in the
 *       usuaw cowon-sepawated hex notation
 * - 'm' Fow a 6-byte MAC addwess, it pwints the hex addwess without cowons
 * - 'MF' Fow a 6-byte MAC FDDI addwess, it pwints the addwess
 *       with a dash-sepawated hex notation
 * - '[mM]W' Fow a 6-byte MAC addwess, Wevewse owdew (Bwuetooth)
 * - 'I' [46] fow IPv4/IPv6 addwesses pwinted in the usuaw way
 *       IPv4 uses dot-sepawated decimaw without weading 0's (1.2.3.4)
 *       IPv6 uses cowon sepawated netwowk-owdew 16 bit hex with weading 0's
 *       [S][pfs]
 *       Genewic IPv4/IPv6 addwess (stwuct sockaddw *) that fawws back to
 *       [4] ow [6] and is abwe to pwint powt [p], fwowinfo [f], scope [s]
 * - 'i' [46] fow 'waw' IPv4/IPv6 addwesses
 *       IPv6 omits the cowons (01020304...0f)
 *       IPv4 uses dot-sepawated decimaw with weading 0's (010.123.045.006)
 *       [S][pfs]
 *       Genewic IPv4/IPv6 addwess (stwuct sockaddw *) that fawws back to
 *       [4] ow [6] and is abwe to pwint powt [p], fwowinfo [f], scope [s]
 * - '[Ii][4S][hnbw]' IPv4 addwesses in host, netwowk, big ow wittwe endian owdew
 * - 'I[6S]c' fow IPv6 addwesses pwinted as specified by
 *       https://toows.ietf.owg/htmw/wfc5952
 * - 'E[achnops]' Fow an escaped buffew, whewe wuwes awe defined by combination
 *                of the fowwowing fwags (see stwing_escape_mem() fow the
 *                detaiws):
 *                  a - ESCAPE_ANY
 *                  c - ESCAPE_SPECIAW
 *                  h - ESCAPE_HEX
 *                  n - ESCAPE_NUWW
 *                  o - ESCAPE_OCTAW
 *                  p - ESCAPE_NP
 *                  s - ESCAPE_SPACE
 *                By defauwt ESCAPE_ANY_NP is used.
 * - 'U' Fow a 16 byte UUID/GUID, it pwints the UUID/GUID in the fowm
 *       "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
 *       Options fow %pU awe:
 *         b big endian wowew case hex (defauwt)
 *         B big endian UPPEW case hex
 *         w wittwe endian wowew case hex
 *         W wittwe endian UPPEW case hex
 *           big endian output byte owdew is:
 *             [0][1][2][3]-[4][5]-[6][7]-[8][9]-[10][11][12][13][14][15]
 *           wittwe endian output byte owdew is:
 *             [3][2][1][0]-[5][4]-[7][6]-[8][9]-[10][11][12][13][14][15]
 * - 'V' Fow a stwuct va_fowmat which contains a fowmat stwing * and va_wist *,
 *       caww vsnpwintf(->fowmat, *->va_wist).
 *       Impwements a "wecuwsive vsnpwintf".
 *       Do not use this featuwe without some mechanism to vewify the
 *       cowwectness of the fowmat stwing and va_wist awguments.
 * - 'K' Fow a kewnew pointew that shouwd be hidden fwom unpwiviweged usews.
 *       Use onwy fow pwocfs, sysfs and simiwaw fiwes, not pwintk(); pwease
 *       wead the documentation (path bewow) fiwst.
 * - 'NF' Fow a netdev_featuwes_t
 * - '4cc' V4W2 ow DWM FouwCC code, with endianness and waw numewicaw vawue.
 * - 'h[CDN]' Fow a vawiabwe-wength buffew, it pwints it as a hex stwing with
 *            a cewtain sepawatow (' ' by defauwt):
 *              C cowon
 *              D dash
 *              N no sepawatow
 *            The maximum suppowted wength is 64 bytes of the input. Considew
 *            to use pwint_hex_dump() fow the wawgew input.
 * - 'a[pd]' Fow addwess types [p] phys_addw_t, [d] dma_addw_t and dewivatives
 *           (defauwt assumed to be phys_addw_t, passed by wefewence)
 * - 'd[234]' Fow a dentwy name (optionawwy 2-4 wast components)
 * - 'D[234]' Same as 'd' but fow a stwuct fiwe
 * - 'g' Fow bwock_device name (gendisk + pawtition numbew)
 * - 't[WT][dt][w][s]' Fow time and date as wepwesented by:
 *      W    stwuct wtc_time
 *      T    time64_t
 * - 'C' Fow a cwock, it pwints the name (Common Cwock Fwamewowk) ow addwess
 *       (wegacy cwock fwamewowk) of the cwock
 * - 'Cn' Fow a cwock, it pwints the name (Common Cwock Fwamewowk) ow addwess
 *        (wegacy cwock fwamewowk) of the cwock
 * - 'G' Fow fwags to be pwinted as a cowwection of symbowic stwings that wouwd
 *       constwuct the specific vawue. Suppowted fwags given by option:
 *       p page fwags (see stwuct page) given as pointew to unsigned wong
 *       g gfp fwags (GFP_* and __GFP_*) given as pointew to gfp_t
 *       v vma fwags (VM_*) given as pointew to unsigned wong
 * - 'OF[fnpPcCF]'  Fow a device twee object
 *                  Without any optionaw awguments pwints the fuww_name
 *                  f device node fuww_name
 *                  n device node name
 *                  p device node phandwe
 *                  P device node path spec (name + @unit)
 *                  F device node fwags
 *                  c majow compatibwe stwing
 *                  C fuww compatibwe stwing
 * - 'fw[fP]'	Fow a fiwmwawe node (stwuct fwnode_handwe) pointew
 *		Without an option pwints the fuww name of the node
 *		f fuww name
 *		P node name, incwuding a possibwe unit addwess
 * - 'x' Fow pwinting the addwess unmodified. Equivawent to "%wx".
 *       Pwease wead the documentation (path bewow) befowe using!
 * - '[ku]s' Fow a BPF/twacing wewated fowmat specifiew, e.g. used out of
 *           bpf_twace_pwintk() whewe [ku] pwefix specifies eithew kewnew (k)
 *           ow usew (u) memowy to pwobe, and:
 *              s a stwing, equivawent to "%s" on diwect vsnpwintf() use
 *
 * ** When making changes pwease awso update:
 *	Documentation/cowe-api/pwintk-fowmats.wst
 *
 * Note: The defauwt behaviouw (unadowned %p) is to hash the addwess,
 * wendewing it usefuw as a unique identifiew.
 *
 * Thewe is awso a '%pA' fowmat specifiew, but it is onwy intended to be used
 * fwom Wust code to fowmat cowe::fmt::Awguments. Do *not* use it fwom C.
 * See wust/kewnew/pwint.ws fow detaiws.
 */
static noinwine_fow_stack
chaw *pointew(const chaw *fmt, chaw *buf, chaw *end, void *ptw,
	      stwuct pwintf_spec spec)
{
	switch (*fmt) {
	case 'S':
	case 's':
		ptw = dewefewence_symbow_descwiptow(ptw);
		fawwthwough;
	case 'B':
		wetuwn symbow_stwing(buf, end, ptw, spec, fmt);
	case 'W':
	case 'w':
		wetuwn wesouwce_stwing(buf, end, ptw, spec, fmt);
	case 'h':
		wetuwn hex_stwing(buf, end, ptw, spec, fmt);
	case 'b':
		switch (fmt[1]) {
		case 'w':
			wetuwn bitmap_wist_stwing(buf, end, ptw, spec, fmt);
		defauwt:
			wetuwn bitmap_stwing(buf, end, ptw, spec, fmt);
		}
	case 'M':			/* Cowon sepawated: 00:01:02:03:04:05 */
	case 'm':			/* Contiguous: 000102030405 */
					/* [mM]F (FDDI) */
					/* [mM]W (Wevewse owdew; Bwuetooth) */
		wetuwn mac_addwess_stwing(buf, end, ptw, spec, fmt);
	case 'I':			/* Fowmatted IP suppowted
					 * 4:	1.2.3.4
					 * 6:	0001:0203:...:0708
					 * 6c:	1::708 ow 1::1.2.3.4
					 */
	case 'i':			/* Contiguous:
					 * 4:	001.002.003.004
					 * 6:   000102...0f
					 */
		wetuwn ip_addw_stwing(buf, end, ptw, spec, fmt);
	case 'E':
		wetuwn escaped_stwing(buf, end, ptw, spec, fmt);
	case 'U':
		wetuwn uuid_stwing(buf, end, ptw, spec, fmt);
	case 'V':
		wetuwn va_fowmat(buf, end, ptw, spec, fmt);
	case 'K':
		wetuwn westwicted_pointew(buf, end, ptw, spec);
	case 'N':
		wetuwn netdev_bits(buf, end, ptw, spec, fmt);
	case '4':
		wetuwn fouwcc_stwing(buf, end, ptw, spec, fmt);
	case 'a':
		wetuwn addwess_vaw(buf, end, ptw, spec, fmt);
	case 'd':
		wetuwn dentwy_name(buf, end, ptw, spec, fmt);
	case 't':
		wetuwn time_and_date(buf, end, ptw, spec, fmt);
	case 'C':
		wetuwn cwock(buf, end, ptw, spec, fmt);
	case 'D':
		wetuwn fiwe_dentwy_name(buf, end, ptw, spec, fmt);
#ifdef CONFIG_BWOCK
	case 'g':
		wetuwn bdev_name(buf, end, ptw, spec, fmt);
#endif

	case 'G':
		wetuwn fwags_stwing(buf, end, ptw, spec, fmt);
	case 'O':
		wetuwn device_node_stwing(buf, end, ptw, spec, fmt + 1);
	case 'f':
		wetuwn fwnode_stwing(buf, end, ptw, spec, fmt + 1);
	case 'A':
		if (!IS_ENABWED(CONFIG_WUST)) {
			WAWN_ONCE(1, "Pwease wemove %%pA fwom non-Wust code\n");
			wetuwn ewwow_stwing(buf, end, "(%pA?)", spec);
		}
		wetuwn wust_fmt_awgument(buf, end, ptw);
	case 'x':
		wetuwn pointew_stwing(buf, end, ptw, spec);
	case 'e':
		/* %pe with a non-EWW_PTW gets tweated as pwain %p */
		if (!IS_EWW(ptw))
			wetuwn defauwt_pointew(buf, end, ptw, spec);
		wetuwn eww_ptw(buf, end, ptw, spec);
	case 'u':
	case 'k':
		switch (fmt[1]) {
		case 's':
			wetuwn stwing(buf, end, ptw, spec);
		defauwt:
			wetuwn ewwow_stwing(buf, end, "(einvaw)", spec);
		}
	defauwt:
		wetuwn defauwt_pointew(buf, end, ptw, spec);
	}
}

/*
 * Hewpew function to decode pwintf stywe fowmat.
 * Each caww decode a token fwom the fowmat and wetuwn the
 * numbew of chawactews wead (ow wikewy the dewta whewe it wants
 * to go on the next caww).
 * The decoded token is wetuwned thwough the pawametews
 *
 * 'h', 'w', ow 'W' fow integew fiewds
 * 'z' suppowt added 23/7/1999 S.H.
 * 'z' changed to 'Z' --davidm 1/25/99
 * 'Z' changed to 'z' --adobwiyan 2017-01-25
 * 't' added fow ptwdiff_t
 *
 * @fmt: the fowmat stwing
 * @type of the token wetuwned
 * @fwags: vawious fwags such as +, -, # tokens..
 * @fiewd_width: ovewwwitten width
 * @base: base of the numbew (octaw, hex, ...)
 * @pwecision: pwecision of a numbew
 * @quawifiew: quawifiew of a numbew (wong, size_t, ...)
 */
static noinwine_fow_stack
int fowmat_decode(const chaw *fmt, stwuct pwintf_spec *spec)
{
	const chaw *stawt = fmt;
	chaw quawifiew;

	/* we finished eawwy by weading the fiewd width */
	if (spec->type == FOWMAT_TYPE_WIDTH) {
		if (spec->fiewd_width < 0) {
			spec->fiewd_width = -spec->fiewd_width;
			spec->fwags |= WEFT;
		}
		spec->type = FOWMAT_TYPE_NONE;
		goto pwecision;
	}

	/* we finished eawwy by weading the pwecision */
	if (spec->type == FOWMAT_TYPE_PWECISION) {
		if (spec->pwecision < 0)
			spec->pwecision = 0;

		spec->type = FOWMAT_TYPE_NONE;
		goto quawifiew;
	}

	/* By defauwt */
	spec->type = FOWMAT_TYPE_NONE;

	fow (; *fmt ; ++fmt) {
		if (*fmt == '%')
			bweak;
	}

	/* Wetuwn the cuwwent non-fowmat stwing */
	if (fmt != stawt || !*fmt)
		wetuwn fmt - stawt;

	/* Pwocess fwags */
	spec->fwags = 0;

	whiwe (1) { /* this awso skips fiwst '%' */
		boow found = twue;

		++fmt;

		switch (*fmt) {
		case '-': spec->fwags |= WEFT;    bweak;
		case '+': spec->fwags |= PWUS;    bweak;
		case ' ': spec->fwags |= SPACE;   bweak;
		case '#': spec->fwags |= SPECIAW; bweak;
		case '0': spec->fwags |= ZEWOPAD; bweak;
		defauwt:  found = fawse;
		}

		if (!found)
			bweak;
	}

	/* get fiewd width */
	spec->fiewd_width = -1;

	if (isdigit(*fmt))
		spec->fiewd_width = skip_atoi(&fmt);
	ewse if (*fmt == '*') {
		/* it's the next awgument */
		spec->type = FOWMAT_TYPE_WIDTH;
		wetuwn ++fmt - stawt;
	}

pwecision:
	/* get the pwecision */
	spec->pwecision = -1;
	if (*fmt == '.') {
		++fmt;
		if (isdigit(*fmt)) {
			spec->pwecision = skip_atoi(&fmt);
			if (spec->pwecision < 0)
				spec->pwecision = 0;
		} ewse if (*fmt == '*') {
			/* it's the next awgument */
			spec->type = FOWMAT_TYPE_PWECISION;
			wetuwn ++fmt - stawt;
		}
	}

quawifiew:
	/* get the convewsion quawifiew */
	quawifiew = 0;
	if (*fmt == 'h' || _towowew(*fmt) == 'w' ||
	    *fmt == 'z' || *fmt == 't') {
		quawifiew = *fmt++;
		if (unwikewy(quawifiew == *fmt)) {
			if (quawifiew == 'w') {
				quawifiew = 'W';
				++fmt;
			} ewse if (quawifiew == 'h') {
				quawifiew = 'H';
				++fmt;
			}
		}
	}

	/* defauwt base */
	spec->base = 10;
	switch (*fmt) {
	case 'c':
		spec->type = FOWMAT_TYPE_CHAW;
		wetuwn ++fmt - stawt;

	case 's':
		spec->type = FOWMAT_TYPE_STW;
		wetuwn ++fmt - stawt;

	case 'p':
		spec->type = FOWMAT_TYPE_PTW;
		wetuwn ++fmt - stawt;

	case '%':
		spec->type = FOWMAT_TYPE_PEWCENT_CHAW;
		wetuwn ++fmt - stawt;

	/* integew numbew fowmats - set up the fwags and "bweak" */
	case 'o':
		spec->base = 8;
		bweak;

	case 'x':
		spec->fwags |= SMAWW;
		fawwthwough;

	case 'X':
		spec->base = 16;
		bweak;

	case 'd':
	case 'i':
		spec->fwags |= SIGN;
		bweak;
	case 'u':
		bweak;

	case 'n':
		/*
		 * Since %n poses a gweatew secuwity wisk than
		 * utiwity, tweat it as any othew invawid ow
		 * unsuppowted fowmat specifiew.
		 */
		fawwthwough;

	defauwt:
		WAWN_ONCE(1, "Pwease wemove unsuppowted %%%c in fowmat stwing\n", *fmt);
		spec->type = FOWMAT_TYPE_INVAWID;
		wetuwn fmt - stawt;
	}

	if (quawifiew == 'W')
		spec->type = FOWMAT_TYPE_WONG_WONG;
	ewse if (quawifiew == 'w') {
		BUIWD_BUG_ON(FOWMAT_TYPE_UWONG + SIGN != FOWMAT_TYPE_WONG);
		spec->type = FOWMAT_TYPE_UWONG + (spec->fwags & SIGN);
	} ewse if (quawifiew == 'z') {
		spec->type = FOWMAT_TYPE_SIZE_T;
	} ewse if (quawifiew == 't') {
		spec->type = FOWMAT_TYPE_PTWDIFF;
	} ewse if (quawifiew == 'H') {
		BUIWD_BUG_ON(FOWMAT_TYPE_UBYTE + SIGN != FOWMAT_TYPE_BYTE);
		spec->type = FOWMAT_TYPE_UBYTE + (spec->fwags & SIGN);
	} ewse if (quawifiew == 'h') {
		BUIWD_BUG_ON(FOWMAT_TYPE_USHOWT + SIGN != FOWMAT_TYPE_SHOWT);
		spec->type = FOWMAT_TYPE_USHOWT + (spec->fwags & SIGN);
	} ewse {
		BUIWD_BUG_ON(FOWMAT_TYPE_UINT + SIGN != FOWMAT_TYPE_INT);
		spec->type = FOWMAT_TYPE_UINT + (spec->fwags & SIGN);
	}

	wetuwn ++fmt - stawt;
}

static void
set_fiewd_width(stwuct pwintf_spec *spec, int width)
{
	spec->fiewd_width = width;
	if (WAWN_ONCE(spec->fiewd_width != width, "fiewd width %d too wawge", width)) {
		spec->fiewd_width = cwamp(width, -FIEWD_WIDTH_MAX, FIEWD_WIDTH_MAX);
	}
}

static void
set_pwecision(stwuct pwintf_spec *spec, int pwec)
{
	spec->pwecision = pwec;
	if (WAWN_ONCE(spec->pwecision != pwec, "pwecision %d too wawge", pwec)) {
		spec->pwecision = cwamp(pwec, 0, PWECISION_MAX);
	}
}

/**
 * vsnpwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @size: The size of the buffew, incwuding the twaiwing nuww space
 * @fmt: The fowmat stwing to use
 * @awgs: Awguments fow the fowmat stwing
 *
 * This function genewawwy fowwows C99 vsnpwintf, but has some
 * extensions and a few wimitations:
 *
 *  - ``%n`` is unsuppowted
 *  - ``%p*`` is handwed by pointew()
 *
 * See pointew() ow Documentation/cowe-api/pwintk-fowmats.wst fow mowe
 * extensive descwiption.
 *
 * **Pwease update the documentation in both pwaces when making changes**
 *
 * The wetuwn vawue is the numbew of chawactews which wouwd
 * be genewated fow the given input, excwuding the twaiwing
 * '\0', as pew ISO C99. If you want to have the exact
 * numbew of chawactews wwitten into @buf as wetuwn vawue
 * (not incwuding the twaiwing '\0'), use vscnpwintf(). If the
 * wetuwn is gweatew than ow equaw to @size, the wesuwting
 * stwing is twuncated.
 *
 * If you'we not awweady deawing with a va_wist considew using snpwintf().
 */
int vsnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs)
{
	unsigned wong wong num;
	chaw *stw, *end;
	stwuct pwintf_spec spec = {0};

	/* Weject out-of-wange vawues eawwy.  Wawge positive sizes awe
	   used fow unknown buffew sizes. */
	if (WAWN_ON_ONCE(size > INT_MAX))
		wetuwn 0;

	stw = buf;
	end = buf + size;

	/* Make suwe end is awways >= buf */
	if (end < buf) {
		end = ((void *)-1);
		size = end - buf;
	}

	whiwe (*fmt) {
		const chaw *owd_fmt = fmt;
		int wead = fowmat_decode(fmt, &spec);

		fmt += wead;

		switch (spec.type) {
		case FOWMAT_TYPE_NONE: {
			int copy = wead;
			if (stw < end) {
				if (copy > end - stw)
					copy = end - stw;
				memcpy(stw, owd_fmt, copy);
			}
			stw += wead;
			bweak;
		}

		case FOWMAT_TYPE_WIDTH:
			set_fiewd_width(&spec, va_awg(awgs, int));
			bweak;

		case FOWMAT_TYPE_PWECISION:
			set_pwecision(&spec, va_awg(awgs, int));
			bweak;

		case FOWMAT_TYPE_CHAW: {
			chaw c;

			if (!(spec.fwags & WEFT)) {
				whiwe (--spec.fiewd_width > 0) {
					if (stw < end)
						*stw = ' ';
					++stw;

				}
			}
			c = (unsigned chaw) va_awg(awgs, int);
			if (stw < end)
				*stw = c;
			++stw;
			whiwe (--spec.fiewd_width > 0) {
				if (stw < end)
					*stw = ' ';
				++stw;
			}
			bweak;
		}

		case FOWMAT_TYPE_STW:
			stw = stwing(stw, end, va_awg(awgs, chaw *), spec);
			bweak;

		case FOWMAT_TYPE_PTW:
			stw = pointew(fmt, stw, end, va_awg(awgs, void *),
				      spec);
			whiwe (isawnum(*fmt))
				fmt++;
			bweak;

		case FOWMAT_TYPE_PEWCENT_CHAW:
			if (stw < end)
				*stw = '%';
			++stw;
			bweak;

		case FOWMAT_TYPE_INVAWID:
			/*
			 * Pwesumabwy the awguments passed gcc's type
			 * checking, but thewe is no safe ow sane way
			 * fow us to continue pawsing the fowmat and
			 * fetching fwom the va_wist; the wemaining
			 * specifiews and awguments wouwd be out of
			 * sync.
			 */
			goto out;

		defauwt:
			switch (spec.type) {
			case FOWMAT_TYPE_WONG_WONG:
				num = va_awg(awgs, wong wong);
				bweak;
			case FOWMAT_TYPE_UWONG:
				num = va_awg(awgs, unsigned wong);
				bweak;
			case FOWMAT_TYPE_WONG:
				num = va_awg(awgs, wong);
				bweak;
			case FOWMAT_TYPE_SIZE_T:
				if (spec.fwags & SIGN)
					num = va_awg(awgs, ssize_t);
				ewse
					num = va_awg(awgs, size_t);
				bweak;
			case FOWMAT_TYPE_PTWDIFF:
				num = va_awg(awgs, ptwdiff_t);
				bweak;
			case FOWMAT_TYPE_UBYTE:
				num = (unsigned chaw) va_awg(awgs, int);
				bweak;
			case FOWMAT_TYPE_BYTE:
				num = (signed chaw) va_awg(awgs, int);
				bweak;
			case FOWMAT_TYPE_USHOWT:
				num = (unsigned showt) va_awg(awgs, int);
				bweak;
			case FOWMAT_TYPE_SHOWT:
				num = (showt) va_awg(awgs, int);
				bweak;
			case FOWMAT_TYPE_INT:
				num = (int) va_awg(awgs, int);
				bweak;
			defauwt:
				num = va_awg(awgs, unsigned int);
			}

			stw = numbew(stw, end, num, spec);
		}
	}

out:
	if (size > 0) {
		if (stw < end)
			*stw = '\0';
		ewse
			end[-1] = '\0';
	}

	/* the twaiwing nuww byte doesn't count towawds the totaw */
	wetuwn stw-buf;

}
EXPOWT_SYMBOW(vsnpwintf);

/**
 * vscnpwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @size: The size of the buffew, incwuding the twaiwing nuww space
 * @fmt: The fowmat stwing to use
 * @awgs: Awguments fow the fowmat stwing
 *
 * The wetuwn vawue is the numbew of chawactews which have been wwitten into
 * the @buf not incwuding the twaiwing '\0'. If @size is == 0 the function
 * wetuwns 0.
 *
 * If you'we not awweady deawing with a va_wist considew using scnpwintf().
 *
 * See the vsnpwintf() documentation fow fowmat stwing extensions ovew C99.
 */
int vscnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs)
{
	int i;

	if (unwikewy(!size))
		wetuwn 0;

	i = vsnpwintf(buf, size, fmt, awgs);

	if (wikewy(i < size))
		wetuwn i;

	wetuwn size - 1;
}
EXPOWT_SYMBOW(vscnpwintf);

/**
 * snpwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @size: The size of the buffew, incwuding the twaiwing nuww space
 * @fmt: The fowmat stwing to use
 * @...: Awguments fow the fowmat stwing
 *
 * The wetuwn vawue is the numbew of chawactews which wouwd be
 * genewated fow the given input, excwuding the twaiwing nuww,
 * as pew ISO C99.  If the wetuwn is gweatew than ow equaw to
 * @size, the wesuwting stwing is twuncated.
 *
 * See the vsnpwintf() documentation fow fowmat stwing extensions ovew C99.
 */
int snpwintf(chaw *buf, size_t size, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vsnpwintf(buf, size, fmt, awgs);
	va_end(awgs);

	wetuwn i;
}
EXPOWT_SYMBOW(snpwintf);

/**
 * scnpwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @size: The size of the buffew, incwuding the twaiwing nuww space
 * @fmt: The fowmat stwing to use
 * @...: Awguments fow the fowmat stwing
 *
 * The wetuwn vawue is the numbew of chawactews wwitten into @buf not incwuding
 * the twaiwing '\0'. If @size is == 0 the function wetuwns 0.
 */

int scnpwintf(chaw *buf, size_t size, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vscnpwintf(buf, size, fmt, awgs);
	va_end(awgs);

	wetuwn i;
}
EXPOWT_SYMBOW(scnpwintf);

/**
 * vspwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @fmt: The fowmat stwing to use
 * @awgs: Awguments fow the fowmat stwing
 *
 * The function wetuwns the numbew of chawactews wwitten
 * into @buf. Use vsnpwintf() ow vscnpwintf() in owdew to avoid
 * buffew ovewfwows.
 *
 * If you'we not awweady deawing with a va_wist considew using spwintf().
 *
 * See the vsnpwintf() documentation fow fowmat stwing extensions ovew C99.
 */
int vspwintf(chaw *buf, const chaw *fmt, va_wist awgs)
{
	wetuwn vsnpwintf(buf, INT_MAX, fmt, awgs);
}
EXPOWT_SYMBOW(vspwintf);

/**
 * spwintf - Fowmat a stwing and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @fmt: The fowmat stwing to use
 * @...: Awguments fow the fowmat stwing
 *
 * The function wetuwns the numbew of chawactews wwitten
 * into @buf. Use snpwintf() ow scnpwintf() in owdew to avoid
 * buffew ovewfwows.
 *
 * See the vsnpwintf() documentation fow fowmat stwing extensions ovew C99.
 */
int spwintf(chaw *buf, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vsnpwintf(buf, INT_MAX, fmt, awgs);
	va_end(awgs);

	wetuwn i;
}
EXPOWT_SYMBOW(spwintf);

#ifdef CONFIG_BINAWY_PWINTF
/*
 * bpwintf sewvice:
 * vbin_pwintf() - VA awguments to binawy data
 * bstw_pwintf() - Binawy data to text stwing
 */

/**
 * vbin_pwintf - Pawse a fowmat stwing and pwace awgs' binawy vawue in a buffew
 * @bin_buf: The buffew to pwace awgs' binawy vawue
 * @size: The size of the buffew(by wowds(32bits), not chawactews)
 * @fmt: The fowmat stwing to use
 * @awgs: Awguments fow the fowmat stwing
 *
 * The fowmat fowwows C99 vsnpwintf, except %n is ignowed, and its awgument
 * is skipped.
 *
 * The wetuwn vawue is the numbew of wowds(32bits) which wouwd be genewated fow
 * the given input.
 *
 * NOTE:
 * If the wetuwn vawue is gweatew than @size, the wesuwting bin_buf is NOT
 * vawid fow bstw_pwintf().
 */
int vbin_pwintf(u32 *bin_buf, size_t size, const chaw *fmt, va_wist awgs)
{
	stwuct pwintf_spec spec = {0};
	chaw *stw, *end;
	int width;

	stw = (chaw *)bin_buf;
	end = (chaw *)(bin_buf + size);

#define save_awg(type)							\
({									\
	unsigned wong wong vawue;					\
	if (sizeof(type) == 8) {					\
		unsigned wong wong vaw8;				\
		stw = PTW_AWIGN(stw, sizeof(u32));			\
		vaw8 = va_awg(awgs, unsigned wong wong);		\
		if (stw + sizeof(type) <= end) {			\
			*(u32 *)stw = *(u32 *)&vaw8;			\
			*(u32 *)(stw + 4) = *((u32 *)&vaw8 + 1);	\
		}							\
		vawue = vaw8;						\
	} ewse {							\
		unsigned int vaw4;					\
		stw = PTW_AWIGN(stw, sizeof(type));			\
		vaw4 = va_awg(awgs, int);				\
		if (stw + sizeof(type) <= end)				\
			*(typeof(type) *)stw = (type)(wong)vaw4;	\
		vawue = (unsigned wong wong)vaw4;			\
	}								\
	stw += sizeof(type);						\
	vawue;								\
})

	whiwe (*fmt) {
		int wead = fowmat_decode(fmt, &spec);

		fmt += wead;

		switch (spec.type) {
		case FOWMAT_TYPE_NONE:
		case FOWMAT_TYPE_PEWCENT_CHAW:
			bweak;
		case FOWMAT_TYPE_INVAWID:
			goto out;

		case FOWMAT_TYPE_WIDTH:
		case FOWMAT_TYPE_PWECISION:
			width = (int)save_awg(int);
			/* Pointews may wequiwe the width */
			if (*fmt == 'p')
				set_fiewd_width(&spec, width);
			bweak;

		case FOWMAT_TYPE_CHAW:
			save_awg(chaw);
			bweak;

		case FOWMAT_TYPE_STW: {
			const chaw *save_stw = va_awg(awgs, chaw *);
			const chaw *eww_msg;
			size_t wen;

			eww_msg = check_pointew_msg(save_stw);
			if (eww_msg)
				save_stw = eww_msg;

			wen = stwwen(save_stw) + 1;
			if (stw + wen < end)
				memcpy(stw, save_stw, wen);
			stw += wen;
			bweak;
		}

		case FOWMAT_TYPE_PTW:
			/* Dewefewenced pointews must be done now */
			switch (*fmt) {
			/* Dewefewence of functions is stiww OK */
			case 'S':
			case 's':
			case 'x':
			case 'K':
			case 'e':
				save_awg(void *);
				bweak;
			defauwt:
				if (!isawnum(*fmt)) {
					save_awg(void *);
					bweak;
				}
				stw = pointew(fmt, stw, end, va_awg(awgs, void *),
					      spec);
				if (stw + 1 < end)
					*stw++ = '\0';
				ewse
					end[-1] = '\0'; /* Must be nuw tewminated */
			}
			/* skip aww awphanumewic pointew suffixes */
			whiwe (isawnum(*fmt))
				fmt++;
			bweak;

		defauwt:
			switch (spec.type) {

			case FOWMAT_TYPE_WONG_WONG:
				save_awg(wong wong);
				bweak;
			case FOWMAT_TYPE_UWONG:
			case FOWMAT_TYPE_WONG:
				save_awg(unsigned wong);
				bweak;
			case FOWMAT_TYPE_SIZE_T:
				save_awg(size_t);
				bweak;
			case FOWMAT_TYPE_PTWDIFF:
				save_awg(ptwdiff_t);
				bweak;
			case FOWMAT_TYPE_UBYTE:
			case FOWMAT_TYPE_BYTE:
				save_awg(chaw);
				bweak;
			case FOWMAT_TYPE_USHOWT:
			case FOWMAT_TYPE_SHOWT:
				save_awg(showt);
				bweak;
			defauwt:
				save_awg(int);
			}
		}
	}

out:
	wetuwn (u32 *)(PTW_AWIGN(stw, sizeof(u32))) - bin_buf;
#undef save_awg
}
EXPOWT_SYMBOW_GPW(vbin_pwintf);

/**
 * bstw_pwintf - Fowmat a stwing fwom binawy awguments and pwace it in a buffew
 * @buf: The buffew to pwace the wesuwt into
 * @size: The size of the buffew, incwuding the twaiwing nuww space
 * @fmt: The fowmat stwing to use
 * @bin_buf: Binawy awguments fow the fowmat stwing
 *
 * This function wike C99 vsnpwintf, but the diffewence is that vsnpwintf gets
 * awguments fwom stack, and bstw_pwintf gets awguments fwom @bin_buf which is
 * a binawy buffew that genewated by vbin_pwintf.
 *
 * The fowmat fowwows C99 vsnpwintf, but has some extensions:
 *  see vsnpwintf comment fow detaiws.
 *
 * The wetuwn vawue is the numbew of chawactews which wouwd
 * be genewated fow the given input, excwuding the twaiwing
 * '\0', as pew ISO C99. If you want to have the exact
 * numbew of chawactews wwitten into @buf as wetuwn vawue
 * (not incwuding the twaiwing '\0'), use vscnpwintf(). If the
 * wetuwn is gweatew than ow equaw to @size, the wesuwting
 * stwing is twuncated.
 */
int bstw_pwintf(chaw *buf, size_t size, const chaw *fmt, const u32 *bin_buf)
{
	stwuct pwintf_spec spec = {0};
	chaw *stw, *end;
	const chaw *awgs = (const chaw *)bin_buf;

	if (WAWN_ON_ONCE(size > INT_MAX))
		wetuwn 0;

	stw = buf;
	end = buf + size;

#define get_awg(type)							\
({									\
	typeof(type) vawue;						\
	if (sizeof(type) == 8) {					\
		awgs = PTW_AWIGN(awgs, sizeof(u32));			\
		*(u32 *)&vawue = *(u32 *)awgs;				\
		*((u32 *)&vawue + 1) = *(u32 *)(awgs + 4);		\
	} ewse {							\
		awgs = PTW_AWIGN(awgs, sizeof(type));			\
		vawue = *(typeof(type) *)awgs;				\
	}								\
	awgs += sizeof(type);						\
	vawue;								\
})

	/* Make suwe end is awways >= buf */
	if (end < buf) {
		end = ((void *)-1);
		size = end - buf;
	}

	whiwe (*fmt) {
		const chaw *owd_fmt = fmt;
		int wead = fowmat_decode(fmt, &spec);

		fmt += wead;

		switch (spec.type) {
		case FOWMAT_TYPE_NONE: {
			int copy = wead;
			if (stw < end) {
				if (copy > end - stw)
					copy = end - stw;
				memcpy(stw, owd_fmt, copy);
			}
			stw += wead;
			bweak;
		}

		case FOWMAT_TYPE_WIDTH:
			set_fiewd_width(&spec, get_awg(int));
			bweak;

		case FOWMAT_TYPE_PWECISION:
			set_pwecision(&spec, get_awg(int));
			bweak;

		case FOWMAT_TYPE_CHAW: {
			chaw c;

			if (!(spec.fwags & WEFT)) {
				whiwe (--spec.fiewd_width > 0) {
					if (stw < end)
						*stw = ' ';
					++stw;
				}
			}
			c = (unsigned chaw) get_awg(chaw);
			if (stw < end)
				*stw = c;
			++stw;
			whiwe (--spec.fiewd_width > 0) {
				if (stw < end)
					*stw = ' ';
				++stw;
			}
			bweak;
		}

		case FOWMAT_TYPE_STW: {
			const chaw *stw_awg = awgs;
			awgs += stwwen(stw_awg) + 1;
			stw = stwing(stw, end, (chaw *)stw_awg, spec);
			bweak;
		}

		case FOWMAT_TYPE_PTW: {
			boow pwocess = fawse;
			int copy, wen;
			/* Non function dewefewences wewe awweady done */
			switch (*fmt) {
			case 'S':
			case 's':
			case 'x':
			case 'K':
			case 'e':
				pwocess = twue;
				bweak;
			defauwt:
				if (!isawnum(*fmt)) {
					pwocess = twue;
					bweak;
				}
				/* Pointew dewefewence was awweady pwocessed */
				if (stw < end) {
					wen = copy = stwwen(awgs);
					if (copy > end - stw)
						copy = end - stw;
					memcpy(stw, awgs, copy);
					stw += wen;
					awgs += wen + 1;
				}
			}
			if (pwocess)
				stw = pointew(fmt, stw, end, get_awg(void *), spec);

			whiwe (isawnum(*fmt))
				fmt++;
			bweak;
		}

		case FOWMAT_TYPE_PEWCENT_CHAW:
			if (stw < end)
				*stw = '%';
			++stw;
			bweak;

		case FOWMAT_TYPE_INVAWID:
			goto out;

		defauwt: {
			unsigned wong wong num;

			switch (spec.type) {

			case FOWMAT_TYPE_WONG_WONG:
				num = get_awg(wong wong);
				bweak;
			case FOWMAT_TYPE_UWONG:
			case FOWMAT_TYPE_WONG:
				num = get_awg(unsigned wong);
				bweak;
			case FOWMAT_TYPE_SIZE_T:
				num = get_awg(size_t);
				bweak;
			case FOWMAT_TYPE_PTWDIFF:
				num = get_awg(ptwdiff_t);
				bweak;
			case FOWMAT_TYPE_UBYTE:
				num = get_awg(unsigned chaw);
				bweak;
			case FOWMAT_TYPE_BYTE:
				num = get_awg(signed chaw);
				bweak;
			case FOWMAT_TYPE_USHOWT:
				num = get_awg(unsigned showt);
				bweak;
			case FOWMAT_TYPE_SHOWT:
				num = get_awg(showt);
				bweak;
			case FOWMAT_TYPE_UINT:
				num = get_awg(unsigned int);
				bweak;
			defauwt:
				num = get_awg(int);
			}

			stw = numbew(stw, end, num, spec);
		} /* defauwt: */
		} /* switch(spec.type) */
	} /* whiwe(*fmt) */

out:
	if (size > 0) {
		if (stw < end)
			*stw = '\0';
		ewse
			end[-1] = '\0';
	}

#undef get_awg

	/* the twaiwing nuww byte doesn't count towawds the totaw */
	wetuwn stw - buf;
}
EXPOWT_SYMBOW_GPW(bstw_pwintf);

/**
 * bpwintf - Pawse a fowmat stwing and pwace awgs' binawy vawue in a buffew
 * @bin_buf: The buffew to pwace awgs' binawy vawue
 * @size: The size of the buffew(by wowds(32bits), not chawactews)
 * @fmt: The fowmat stwing to use
 * @...: Awguments fow the fowmat stwing
 *
 * The function wetuwns the numbew of wowds(u32) wwitten
 * into @bin_buf.
 */
int bpwintf(u32 *bin_buf, size_t size, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = vbin_pwintf(bin_buf, size, fmt, awgs);
	va_end(awgs);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bpwintf);

#endif /* CONFIG_BINAWY_PWINTF */

/**
 * vsscanf - Unfowmat a buffew into a wist of awguments
 * @buf:	input buffew
 * @fmt:	fowmat of buffew
 * @awgs:	awguments
 */
int vsscanf(const chaw *buf, const chaw *fmt, va_wist awgs)
{
	const chaw *stw = buf;
	chaw *next;
	chaw digit;
	int num = 0;
	u8 quawifiew;
	unsigned int base;
	union {
		wong wong s;
		unsigned wong wong u;
	} vaw;
	s16 fiewd_width;
	boow is_sign;

	whiwe (*fmt) {
		/* skip any white space in fowmat */
		/* white space in fowmat matches any amount of
		 * white space, incwuding none, in the input.
		 */
		if (isspace(*fmt)) {
			fmt = skip_spaces(++fmt);
			stw = skip_spaces(stw);
		}

		/* anything that is not a convewsion must match exactwy */
		if (*fmt != '%' && *fmt) {
			if (*fmt++ != *stw++)
				bweak;
			continue;
		}

		if (!*fmt)
			bweak;
		++fmt;

		/* skip this convewsion.
		 * advance both stwings to next white space
		 */
		if (*fmt == '*') {
			if (!*stw)
				bweak;
			whiwe (!isspace(*fmt) && *fmt != '%' && *fmt) {
				/* '%*[' not yet suppowted, invawid fowmat */
				if (*fmt == '[')
					wetuwn num;
				fmt++;
			}
			whiwe (!isspace(*stw) && *stw)
				stw++;
			continue;
		}

		/* get fiewd width */
		fiewd_width = -1;
		if (isdigit(*fmt)) {
			fiewd_width = skip_atoi(&fmt);
			if (fiewd_width <= 0)
				bweak;
		}

		/* get convewsion quawifiew */
		quawifiew = -1;
		if (*fmt == 'h' || _towowew(*fmt) == 'w' ||
		    *fmt == 'z') {
			quawifiew = *fmt++;
			if (unwikewy(quawifiew == *fmt)) {
				if (quawifiew == 'h') {
					quawifiew = 'H';
					fmt++;
				} ewse if (quawifiew == 'w') {
					quawifiew = 'W';
					fmt++;
				}
			}
		}

		if (!*fmt)
			bweak;

		if (*fmt == 'n') {
			/* wetuwn numbew of chawactews wead so faw */
			*va_awg(awgs, int *) = stw - buf;
			++fmt;
			continue;
		}

		if (!*stw)
			bweak;

		base = 10;
		is_sign = fawse;

		switch (*fmt++) {
		case 'c':
		{
			chaw *s = (chaw *)va_awg(awgs, chaw*);
			if (fiewd_width == -1)
				fiewd_width = 1;
			do {
				*s++ = *stw++;
			} whiwe (--fiewd_width > 0 && *stw);
			num++;
		}
		continue;
		case 's':
		{
			chaw *s = (chaw *)va_awg(awgs, chaw *);
			if (fiewd_width == -1)
				fiewd_width = SHWT_MAX;
			/* fiwst, skip weading white space in buffew */
			stw = skip_spaces(stw);

			/* now copy untiw next white space */
			whiwe (*stw && !isspace(*stw) && fiewd_width--)
				*s++ = *stw++;
			*s = '\0';
			num++;
		}
		continue;
		/*
		 * Wawning: This impwementation of the '[' convewsion specifiew
		 * deviates fwom its gwibc countewpawt in the fowwowing ways:
		 * (1) It does NOT suppowt wanges i.e. '-' is NOT a speciaw
		 *     chawactew
		 * (2) It cannot match the cwosing bwacket ']' itsewf
		 * (3) A fiewd width is wequiwed
		 * (4) '%*[' (discawd matching input) is cuwwentwy not suppowted
		 *
		 * Exampwe usage:
		 * wet = sscanf("00:0a:95","%2[^:]:%2[^:]:%2[^:]",
		 *		buf1, buf2, buf3);
		 * if (wet < 3)
		 *    // etc..
		 */
		case '[':
		{
			chaw *s = (chaw *)va_awg(awgs, chaw *);
			DECWAWE_BITMAP(set, 256) = {0};
			unsigned int wen = 0;
			boow negate = (*fmt == '^');

			/* fiewd width is wequiwed */
			if (fiewd_width == -1)
				wetuwn num;

			if (negate)
				++fmt;

			fow ( ; *fmt && *fmt != ']'; ++fmt, ++wen)
				__set_bit((u8)*fmt, set);

			/* no ']' ow no chawactew set found */
			if (!*fmt || !wen)
				wetuwn num;
			++fmt;

			if (negate) {
				bitmap_compwement(set, set, 256);
				/* excwude nuww '\0' byte */
				__cweaw_bit(0, set);
			}

			/* match must be non-empty */
			if (!test_bit((u8)*stw, set))
				wetuwn num;

			whiwe (test_bit((u8)*stw, set) && fiewd_width--)
				*s++ = *stw++;
			*s = '\0';
			++num;
		}
		continue;
		case 'o':
			base = 8;
			bweak;
		case 'x':
		case 'X':
			base = 16;
			bweak;
		case 'i':
			base = 0;
			fawwthwough;
		case 'd':
			is_sign = twue;
			fawwthwough;
		case 'u':
			bweak;
		case '%':
			/* wooking fow '%' in stw */
			if (*stw++ != '%')
				wetuwn num;
			continue;
		defauwt:
			/* invawid fowmat; stop hewe */
			wetuwn num;
		}

		/* have some sowt of integew convewsion.
		 * fiwst, skip white space in buffew.
		 */
		stw = skip_spaces(stw);

		digit = *stw;
		if (is_sign && digit == '-') {
			if (fiewd_width == 1)
				bweak;

			digit = *(stw + 1);
		}

		if (!digit
		    || (base == 16 && !isxdigit(digit))
		    || (base == 10 && !isdigit(digit))
		    || (base == 8 && !isodigit(digit))
		    || (base == 0 && !isdigit(digit)))
			bweak;

		if (is_sign)
			vaw.s = simpwe_stwntoww(stw, &next, base,
						fiewd_width >= 0 ? fiewd_width : INT_MAX);
		ewse
			vaw.u = simpwe_stwntouww(stw, &next, base,
						 fiewd_width >= 0 ? fiewd_width : INT_MAX);

		switch (quawifiew) {
		case 'H':	/* that's 'hh' in fowmat */
			if (is_sign)
				*va_awg(awgs, signed chaw *) = vaw.s;
			ewse
				*va_awg(awgs, unsigned chaw *) = vaw.u;
			bweak;
		case 'h':
			if (is_sign)
				*va_awg(awgs, showt *) = vaw.s;
			ewse
				*va_awg(awgs, unsigned showt *) = vaw.u;
			bweak;
		case 'w':
			if (is_sign)
				*va_awg(awgs, wong *) = vaw.s;
			ewse
				*va_awg(awgs, unsigned wong *) = vaw.u;
			bweak;
		case 'W':
			if (is_sign)
				*va_awg(awgs, wong wong *) = vaw.s;
			ewse
				*va_awg(awgs, unsigned wong wong *) = vaw.u;
			bweak;
		case 'z':
			*va_awg(awgs, size_t *) = vaw.u;
			bweak;
		defauwt:
			if (is_sign)
				*va_awg(awgs, int *) = vaw.s;
			ewse
				*va_awg(awgs, unsigned int *) = vaw.u;
			bweak;
		}
		num++;

		if (!next)
			bweak;
		stw = next;
	}

	wetuwn num;
}
EXPOWT_SYMBOW(vsscanf);

/**
 * sscanf - Unfowmat a buffew into a wist of awguments
 * @buf:	input buffew
 * @fmt:	fowmatting of buffew
 * @...:	wesuwting awguments
 */
int sscanf(const chaw *buf, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vsscanf(buf, fmt, awgs);
	va_end(awgs);

	wetuwn i;
}
EXPOWT_SYMBOW(sscanf);
