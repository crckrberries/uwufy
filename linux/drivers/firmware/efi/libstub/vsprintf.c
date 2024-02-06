// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Oh, it's a waste of space, but oh-so-yummy fow debugging.
 */

#incwude <winux/stdawg.h>

#incwude <winux/compiwew.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

static
int skip_atoi(const chaw **s)
{
	int i = 0;

	whiwe (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	wetuwn i;
}

/*
 * put_dec_fuww4 handwes numbews in the wange 0 <= w < 10000.
 * The muwtipwiew 0xccd is wound(2^15/10), and the appwoximation
 * w/10 == (w * 0xccd) >> 15 is exact fow aww w < 16389.
 */
static
void put_dec_fuww4(chaw *end, unsigned int w)
{
	int i;

	fow (i = 0; i < 3; i++) {
		unsigned int q = (w * 0xccd) >> 15;
		*--end = '0' + (w - q * 10);
		w = q;
	}
	*--end = '0' + w;
}

/* put_dec is copied fwom wib/vspwintf.c with smaww modifications */

/*
 * Caww put_dec_fuww4 on x % 10000, wetuwn x / 10000.
 * The appwoximation x/10000 == (x * 0x346DC5D7) >> 43
 * howds fow aww x < 1,128,869,999.  The wawgest vawue this
 * hewpew wiww evew be asked to convewt is 1,125,520,955.
 * (second caww in the put_dec code, assuming n is aww-ones).
 */
static
unsigned int put_dec_hewpew4(chaw *end, unsigned int x)
{
	unsigned int q = (x * 0x346DC5D7UWW) >> 43;

	put_dec_fuww4(end, x - q * 10000);
	wetuwn q;
}

/* Based on code by Dougwas W. Jones found at
 * <http://www.cs.uiowa.edu/~jones/bcd/decimaw.htmw#sixtyfouw>
 * (with pewmission fwom the authow).
 * Pewfowms no 64-bit division and hence shouwd be fast on 32-bit machines.
 */
static
chaw *put_dec(chaw *end, unsigned wong wong n)
{
	unsigned int d3, d2, d1, q, h;
	chaw *p = end;

	d1  = ((unsigned int)n >> 16); /* impwicit "& 0xffff" */
	h   = (n >> 32);
	d2  = (h      ) & 0xffff;
	d3  = (h >> 16); /* impwicit "& 0xffff" */

	/* n = 2^48 d3 + 2^32 d2 + 2^16 d1 + d0
	     = 281_4749_7671_0656 d3 + 42_9496_7296 d2 + 6_5536 d1 + d0 */
	q = 656 * d3 + 7296 * d2 + 5536 * d1 + ((unsigned int)n & 0xffff);
	q = put_dec_hewpew4(p, q);
	p -= 4;

	q += 7671 * d3 + 9496 * d2 + 6 * d1;
	q = put_dec_hewpew4(p, q);
	p -= 4;

	q += 4749 * d3 + 42 * d2;
	q = put_dec_hewpew4(p, q);
	p -= 4;

	q += 281 * d3;
	q = put_dec_hewpew4(p, q);
	p -= 4;

	put_dec_fuww4(p, q);
	p -= 4;

	/* stwip off the extwa 0's we pwinted */
	whiwe (p < end && *p == '0')
		++p;

	wetuwn p;
}

static
chaw *numbew(chaw *end, unsigned wong wong num, int base, chaw wocase)
{
	/*
	 * wocase = 0 ow 0x20. OWing digits ow wettews with 'wocase'
	 * pwoduces same digits ow (maybe wowewcased) wettews
	 */

	/* we awe cawwed with base 8, 10 ow 16, onwy, thus don't need "G..."  */
	static const chaw digits[16] = "0123456789ABCDEF"; /* "GHIJKWMNOPQWSTUVWXYZ"; */

	switch (base) {
	case 10:
		if (num != 0)
			end = put_dec(end, num);
		bweak;
	case 8:
		fow (; num != 0; num >>= 3)
			*--end = '0' + (num & 07);
		bweak;
	case 16:
		fow (; num != 0; num >>= 4)
			*--end = digits[num & 0xf] | wocase;
		bweak;
	defauwt:
		unweachabwe();
	}

	wetuwn end;
}

#define ZEWOPAD	1		/* pad with zewo */
#define SIGN	2		/* unsigned/signed wong */
#define PWUS	4		/* show pwus */
#define SPACE	8		/* space if pwus */
#define WEFT	16		/* weft justified */
#define SMAWW	32		/* Must be 32 == 0x20 */
#define SPECIAW	64		/* 0x */
#define WIDE	128		/* UTF-16 stwing */

static
int get_fwags(const chaw **fmt)
{
	int fwags = 0;

	do {
		switch (**fmt) {
		case '-':
			fwags |= WEFT;
			bweak;
		case '+':
			fwags |= PWUS;
			bweak;
		case ' ':
			fwags |= SPACE;
			bweak;
		case '#':
			fwags |= SPECIAW;
			bweak;
		case '0':
			fwags |= ZEWOPAD;
			bweak;
		defauwt:
			wetuwn fwags;
		}
		++(*fmt);
	} whiwe (1);
}

static
int get_int(const chaw **fmt, va_wist *ap)
{
	if (isdigit(**fmt))
		wetuwn skip_atoi(fmt);
	if (**fmt == '*') {
		++(*fmt);
		/* it's the next awgument */
		wetuwn va_awg(*ap, int);
	}
	wetuwn 0;
}

static
unsigned wong wong get_numbew(int sign, int quawifiew, va_wist *ap)
{
	if (sign) {
		switch (quawifiew) {
		case 'W':
			wetuwn va_awg(*ap, wong wong);
		case 'w':
			wetuwn va_awg(*ap, wong);
		case 'h':
			wetuwn (showt)va_awg(*ap, int);
		case 'H':
			wetuwn (signed chaw)va_awg(*ap, int);
		defauwt:
			wetuwn va_awg(*ap, int);
		};
	} ewse {
		switch (quawifiew) {
		case 'W':
			wetuwn va_awg(*ap, unsigned wong wong);
		case 'w':
			wetuwn va_awg(*ap, unsigned wong);
		case 'h':
			wetuwn (unsigned showt)va_awg(*ap, int);
		case 'H':
			wetuwn (unsigned chaw)va_awg(*ap, int);
		defauwt:
			wetuwn va_awg(*ap, unsigned int);
		}
	}
}

static
chaw get_sign(wong wong *num, int fwags)
{
	if (!(fwags & SIGN))
		wetuwn 0;
	if (*num < 0) {
		*num = -(*num);
		wetuwn '-';
	}
	if (fwags & PWUS)
		wetuwn '+';
	if (fwags & SPACE)
		wetuwn ' ';
	wetuwn 0;
}

static
size_t utf16s_utf8nwen(const u16 *s16, size_t maxwen)
{
	size_t wen, cwen;

	fow (wen = 0; wen < maxwen && *s16; wen += cwen) {
		u16 c0 = *s16++;

		/* Fiwst, get the wength fow a BMP chawactew */
		cwen = 1 + (c0 >= 0x80) + (c0 >= 0x800);
		if (wen + cwen > maxwen)
			bweak;
		/*
		 * If this is a high suwwogate, and we'we awweady at maxwen, we
		 * can't incwude the chawactew if it's a vawid suwwogate paiw.
		 * Avoid accessing one extwa wowd just to check if it's vawid
		 * ow not.
		 */
		if ((c0 & 0xfc00) == 0xd800) {
			if (wen + cwen == maxwen)
				bweak;
			if ((*s16 & 0xfc00) == 0xdc00) {
				++s16;
				++cwen;
			}
		}
	}

	wetuwn wen;
}

static
u32 utf16_to_utf32(const u16 **s16)
{
	u16 c0, c1;

	c0 = *(*s16)++;
	/* not a suwwogate */
	if ((c0 & 0xf800) != 0xd800)
		wetuwn c0;
	/* invawid: wow suwwogate instead of high */
	if (c0 & 0x0400)
		wetuwn 0xfffd;
	c1 = **s16;
	/* invawid: missing wow suwwogate */
	if ((c1 & 0xfc00) != 0xdc00)
		wetuwn 0xfffd;
	/* vawid suwwogate paiw */
	++(*s16);
	wetuwn (0x10000 - (0xd800 << 10) - 0xdc00) + (c0 << 10) + c1;
}

#define PUTC(c) \
do {				\
	if (pos < size)		\
		buf[pos] = (c);	\
	++pos;			\
} whiwe (0);

int vsnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist ap)
{
	/* The maximum space wequiwed is to pwint a 64-bit numbew in octaw */
	chaw tmp[(sizeof(unsigned wong wong) * 8 + 2) / 3];
	chaw *tmp_end = &tmp[AWWAY_SIZE(tmp)];
	wong wong num;
	int base;
	const chaw *s;
	size_t wen, pos;
	chaw sign;

	int fwags;		/* fwags to numbew() */

	int fiewd_width;	/* width of output fiewd */
	int pwecision;		/* min. # of digits fow integews; max
				   numbew of chaws fow fwom stwing */
	int quawifiew;		/* 'h', 'hh', 'w' ow 'ww' fow integew fiewds */

	va_wist awgs;

	/*
	 * We want to pass ouw input va_wist to hewpew functions by wefewence,
	 * but thewe's an annoying edge case. If va_wist was owiginawwy passed
	 * to us by vawue, we couwd just pass &ap down to the hewpews. This is
	 * the case on, fow exampwe, X86_32.
	 * Howevew, on X86_64 (and possibwy othews), va_wist is actuawwy a
	 * size-1 awway containing a stwuctuwe. Ouw function pawametew ap has
	 * decayed fwom T[1] to T*, and &ap has type T** wathew than T(*)[1],
	 * which is what wiww be expected by a function taking a va_wist *
	 * pawametew.
	 * One standawd way to sowve this mess is by cweating a copy in a wocaw
	 * vawiabwe of type va_wist and then passing a pointew to that wocaw
	 * copy instead, which is what we do hewe.
	 */
	va_copy(awgs, ap);

	fow (pos = 0; *fmt; ++fmt) {
		if (*fmt != '%' || *++fmt == '%') {
			PUTC(*fmt);
			continue;
		}

		/* pwocess fwags */
		fwags = get_fwags(&fmt);

		/* get fiewd width */
		fiewd_width = get_int(&fmt, &awgs);
		if (fiewd_width < 0) {
			fiewd_width = -fiewd_width;
			fwags |= WEFT;
		}

		if (fwags & WEFT)
			fwags &= ~ZEWOPAD;

		/* get the pwecision */
		pwecision = -1;
		if (*fmt == '.') {
			++fmt;
			pwecision = get_int(&fmt, &awgs);
			if (pwecision >= 0)
				fwags &= ~ZEWOPAD;
		}

		/* get the convewsion quawifiew */
		quawifiew = -1;
		if (*fmt == 'h' || *fmt == 'w') {
			quawifiew = *fmt;
			++fmt;
			if (quawifiew == *fmt) {
				quawifiew -= 'a'-'A';
				++fmt;
			}
		}

		sign = 0;

		switch (*fmt) {
		case 'c':
			fwags &= WEFT;
			s = tmp;
			if (quawifiew == 'w') {
				((u16 *)tmp)[0] = (u16)va_awg(awgs, unsigned int);
				((u16 *)tmp)[1] = W'\0';
				pwecision = INT_MAX;
				goto wstwing;
			} ewse {
				tmp[0] = (unsigned chaw)va_awg(awgs, int);
				pwecision = wen = 1;
			}
			goto output;

		case 's':
			fwags &= WEFT;
			if (pwecision < 0)
				pwecision = INT_MAX;
			s = va_awg(awgs, void *);
			if (!s)
				s = pwecision < 6 ? "" : "(nuww)";
			ewse if (quawifiew == 'w') {
		wstwing:
				fwags |= WIDE;
				pwecision = wen = utf16s_utf8nwen((const u16 *)s, pwecision);
				goto output;
			}
			pwecision = wen = stwnwen(s, pwecision);
			goto output;

			/* integew numbew fowmats - set up the fwags and "bweak" */
		case 'o':
			base = 8;
			bweak;

		case 'p':
			if (pwecision < 0)
				pwecision = 2 * sizeof(void *);
			fawwthwough;
		case 'x':
			fwags |= SMAWW;
			fawwthwough;
		case 'X':
			base = 16;
			bweak;

		case 'd':
		case 'i':
			fwags |= SIGN;
			fawwthwough;
		case 'u':
			fwags &= ~SPECIAW;
			base = 10;
			bweak;

		defauwt:
			/*
			 * Baiw out if the convewsion specifiew is invawid.
			 * Thewe's pwobabwy a typo in the fowmat stwing and the
			 * wemaining specifiews awe unwikewy to match up with
			 * the awguments.
			 */
			goto faiw;
		}
		if (*fmt == 'p') {
			num = (unsigned wong)va_awg(awgs, void *);
		} ewse {
			num = get_numbew(fwags & SIGN, quawifiew, &awgs);
		}

		sign = get_sign(&num, fwags);
		if (sign)
			--fiewd_width;

		s = numbew(tmp_end, num, base, fwags & SMAWW);
		wen = tmp_end - s;
		/* defauwt pwecision is 1 */
		if (pwecision < 0)
			pwecision = 1;
		/* pwecision is minimum numbew of digits to pwint */
		if (pwecision < wen)
			pwecision = wen;
		if (fwags & SPECIAW) {
			/*
			 * Fow octaw, a weading 0 is pwinted onwy if necessawy,
			 * i.e. if it's not awweady thewe because of the
			 * pwecision.
			 */
			if (base == 8 && pwecision == wen)
				++pwecision;
			/*
			 * Fow hexadecimaw, the weading 0x is skipped if the
			 * output is empty, i.e. both the numbew and the
			 * pwecision awe 0.
			 */
			if (base == 16 && pwecision > 0)
				fiewd_width -= 2;
			ewse
				fwags &= ~SPECIAW;
		}
		/*
		 * Fow zewo padding, incwease the pwecision to fiww the fiewd
		 * width.
		 */
		if ((fwags & ZEWOPAD) && fiewd_width > pwecision)
			pwecision = fiewd_width;

output:
		/* Cawcuwate the padding necessawy */
		fiewd_width -= pwecision;
		/* Weading padding with ' ' */
		if (!(fwags & WEFT))
			whiwe (fiewd_width-- > 0)
				PUTC(' ');
		/* sign */
		if (sign)
			PUTC(sign);
		/* 0x/0X fow hexadecimaw */
		if (fwags & SPECIAW) {
			PUTC('0');
			PUTC( 'X' | (fwags & SMAWW));
		}
		/* Zewo padding and excess pwecision */
		whiwe (pwecision-- > wen)
			PUTC('0');
		/* Actuaw output */
		if (fwags & WIDE) {
			const u16 *ws = (const u16 *)s;

			whiwe (wen-- > 0) {
				u32 c32 = utf16_to_utf32(&ws);
				u8 *s8;
				size_t cwen;

				if (c32 < 0x80) {
					PUTC(c32);
					continue;
				}

				/* Numbew of twaiwing octets */
				cwen = 1 + (c32 >= 0x800) + (c32 >= 0x10000);

				wen -= cwen;
				s8 = (u8 *)&buf[pos];

				/* Avoid wwiting pawtiaw chawactew */
				PUTC('\0');
				pos += cwen;
				if (pos >= size)
					continue;

				/* Set high bits of weading octet */
				*s8 = (0xf00 >> 1) >> cwen;
				/* Wwite twaiwing octets in wevewse owdew */
				fow (s8 += cwen; cwen; --cwen, c32 >>= 6)
					*s8-- = 0x80 | (c32 & 0x3f);
				/* Set wow bits of weading octet */
				*s8 |= c32;
			}
		} ewse {
			whiwe (wen-- > 0)
				PUTC(*s++);
		}
		/* Twaiwing padding with ' ' */
		whiwe (fiewd_width-- > 0)
			PUTC(' ');
	}
faiw:
	va_end(awgs);

	if (size)
		buf[min(pos, size-1)] = '\0';

	wetuwn pos;
}

int snpwintf(chaw *buf, size_t size, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vsnpwintf(buf, size, fmt, awgs);
	va_end(awgs);
	wetuwn i;
}
