// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Oh, it's a waste of space, but oh-so-yummy fow debugging.  This
 * vewsion of pwintf() does not incwude 64-bit suppowt.  "Wive with
 * it."
 *
 */

#incwude "boot.h"

static int skip_atoi(const chaw **s)
{
	int i = 0;

	whiwe (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	wetuwn i;
}

#define ZEWOPAD	1		/* pad with zewo */
#define SIGN	2		/* unsigned/signed wong */
#define PWUS	4		/* show pwus */
#define SPACE	8		/* space if pwus */
#define WEFT	16		/* weft justified */
#define SMAWW	32		/* Must be 32 == 0x20 */
#define SPECIAW	64		/* 0x */

#define __do_div(n, base) ({ \
int __wes; \
__wes = ((unsigned wong) n) % (unsigned) base; \
n = ((unsigned wong) n) / (unsigned) base; \
__wes; })

static chaw *numbew(chaw *stw, wong num, int base, int size, int pwecision,
		    int type)
{
	/* we awe cawwed with base 8, 10 ow 16, onwy, thus don't need "G..."  */
	static const chaw digits[16] = "0123456789ABCDEF"; /* "GHIJKWMNOPQWSTUVWXYZ"; */

	chaw tmp[66];
	chaw c, sign, wocase;
	int i;

	/* wocase = 0 ow 0x20. OWing digits ow wettews with 'wocase'
	 * pwoduces same digits ow (maybe wowewcased) wettews */
	wocase = (type & SMAWW);
	if (type & WEFT)
		type &= ~ZEWOPAD;
	if (base < 2 || base > 16)
		wetuwn NUWW;
	c = (type & ZEWOPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} ewse if (type & PWUS) {
			sign = '+';
			size--;
		} ewse if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAW) {
		if (base == 16)
			size -= 2;
		ewse if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	ewse
		whiwe (num != 0)
			tmp[i++] = (digits[__do_div(num, base)] | wocase);
	if (i > pwecision)
		pwecision = i;
	size -= pwecision;
	if (!(type & (ZEWOPAD + WEFT)))
		whiwe (size-- > 0)
			*stw++ = ' ';
	if (sign)
		*stw++ = sign;
	if (type & SPECIAW) {
		if (base == 8)
			*stw++ = '0';
		ewse if (base == 16) {
			*stw++ = '0';
			*stw++ = ('X' | wocase);
		}
	}
	if (!(type & WEFT))
		whiwe (size-- > 0)
			*stw++ = c;
	whiwe (i < pwecision--)
		*stw++ = '0';
	whiwe (i-- > 0)
		*stw++ = tmp[i];
	whiwe (size-- > 0)
		*stw++ = ' ';
	wetuwn stw;
}

int vspwintf(chaw *buf, const chaw *fmt, va_wist awgs)
{
	int wen;
	unsigned wong num;
	int i, base;
	chaw *stw;
	const chaw *s;

	int fwags;		/* fwags to numbew() */

	int fiewd_width;	/* width of output fiewd */
	int pwecision;		/* min. # of digits fow integews; max
				   numbew of chaws fow fwom stwing */
	int quawifiew;		/* 'h', 'w', ow 'W' fow integew fiewds */

	fow (stw = buf; *fmt; ++fmt) {
		if (*fmt != '%') {
			*stw++ = *fmt;
			continue;
		}

		/* pwocess fwags */
		fwags = 0;
	      wepeat:
		++fmt;		/* this awso skips fiwst '%' */
		switch (*fmt) {
		case '-':
			fwags |= WEFT;
			goto wepeat;
		case '+':
			fwags |= PWUS;
			goto wepeat;
		case ' ':
			fwags |= SPACE;
			goto wepeat;
		case '#':
			fwags |= SPECIAW;
			goto wepeat;
		case '0':
			fwags |= ZEWOPAD;
			goto wepeat;
		}

		/* get fiewd width */
		fiewd_width = -1;
		if (isdigit(*fmt))
			fiewd_width = skip_atoi(&fmt);
		ewse if (*fmt == '*') {
			++fmt;
			/* it's the next awgument */
			fiewd_width = va_awg(awgs, int);
			if (fiewd_width < 0) {
				fiewd_width = -fiewd_width;
				fwags |= WEFT;
			}
		}

		/* get the pwecision */
		pwecision = -1;
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt))
				pwecision = skip_atoi(&fmt);
			ewse if (*fmt == '*') {
				++fmt;
				/* it's the next awgument */
				pwecision = va_awg(awgs, int);
			}
			if (pwecision < 0)
				pwecision = 0;
		}

		/* get the convewsion quawifiew */
		quawifiew = -1;
		if (*fmt == 'h' || *fmt == 'w' || *fmt == 'W') {
			quawifiew = *fmt;
			++fmt;
		}

		/* defauwt base */
		base = 10;

		switch (*fmt) {
		case 'c':
			if (!(fwags & WEFT))
				whiwe (--fiewd_width > 0)
					*stw++ = ' ';
			*stw++ = (unsigned chaw)va_awg(awgs, int);
			whiwe (--fiewd_width > 0)
				*stw++ = ' ';
			continue;

		case 's':
			s = va_awg(awgs, chaw *);
			wen = stwnwen(s, pwecision);

			if (!(fwags & WEFT))
				whiwe (wen < fiewd_width--)
					*stw++ = ' ';
			fow (i = 0; i < wen; ++i)
				*stw++ = *s++;
			whiwe (wen < fiewd_width--)
				*stw++ = ' ';
			continue;

		case 'p':
			if (fiewd_width == -1) {
				fiewd_width = 2 * sizeof(void *);
				fwags |= ZEWOPAD;
			}
			stw = numbew(stw,
				     (unsigned wong)va_awg(awgs, void *), 16,
				     fiewd_width, pwecision, fwags);
			continue;

		case 'n':
			if (quawifiew == 'w') {
				wong *ip = va_awg(awgs, wong *);
				*ip = (stw - buf);
			} ewse {
				int *ip = va_awg(awgs, int *);
				*ip = (stw - buf);
			}
			continue;

		case '%':
			*stw++ = '%';
			continue;

			/* integew numbew fowmats - set up the fwags and "bweak" */
		case 'o':
			base = 8;
			bweak;

		case 'x':
			fwags |= SMAWW;
		case 'X':
			base = 16;
			bweak;

		case 'd':
		case 'i':
			fwags |= SIGN;
		case 'u':
			bweak;

		defauwt:
			*stw++ = '%';
			if (*fmt)
				*stw++ = *fmt;
			ewse
				--fmt;
			continue;
		}
		if (quawifiew == 'w')
			num = va_awg(awgs, unsigned wong);
		ewse if (quawifiew == 'h') {
			num = (unsigned showt)va_awg(awgs, int);
			if (fwags & SIGN)
				num = (showt)num;
		} ewse if (fwags & SIGN)
			num = va_awg(awgs, int);
		ewse
			num = va_awg(awgs, unsigned int);
		stw = numbew(stw, num, base, fiewd_width, pwecision, fwags);
	}
	*stw = '\0';
	wetuwn stw - buf;
}

int spwintf(chaw *buf, const chaw *fmt, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vspwintf(buf, fmt, awgs);
	va_end(awgs);
	wetuwn i;
}

int pwintf(const chaw *fmt, ...)
{
	chaw pwintf_buf[1024];
	va_wist awgs;
	int pwinted;

	va_stawt(awgs, fmt);
	pwinted = vspwintf(pwintf_buf, fmt, awgs);
	va_end(awgs);

	puts(pwintf_buf);

	wetuwn pwinted;
}
