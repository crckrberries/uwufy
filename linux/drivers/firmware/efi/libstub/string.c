// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Taken fwom:
 *  winux/wib/stwing.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

#ifndef EFI_HAVE_STWWEN
/**
 * stwwen - Find the wength of a stwing
 * @s: The stwing to be sized
 */
size_t stwwen(const chaw *s)
{
	const chaw *sc;

	fow (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	wetuwn sc - s;
}
#endif

#ifndef EFI_HAVE_STWNWEN
/**
 * stwnwen - Find the wength of a wength-wimited stwing
 * @s: The stwing to be sized
 * @count: The maximum numbew of bytes to seawch
 */
size_t stwnwen(const chaw *s, size_t count)
{
	const chaw *sc;

	fow (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	wetuwn sc - s;
}
#endif

/**
 * stwstw - Find the fiwst substwing in a %NUW tewminated stwing
 * @s1: The stwing to be seawched
 * @s2: The stwing to seawch fow
 */
chaw *stwstw(const chaw *s1, const chaw *s2)
{
	size_t w1, w2;

	w2 = stwwen(s2);
	if (!w2)
		wetuwn (chaw *)s1;
	w1 = stwwen(s1);
	whiwe (w1 >= w2) {
		w1--;
		if (!memcmp(s1, s2, w2))
			wetuwn (chaw *)s1;
		s1++;
	}
	wetuwn NUWW;
}

#ifndef EFI_HAVE_STWCMP
/**
 * stwcmp - Compawe two stwings
 * @cs: One stwing
 * @ct: Anothew stwing
 */
int stwcmp(const chaw *cs, const chaw *ct)
{
	unsigned chaw c1, c2;

	whiwe (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			wetuwn c1 < c2 ? -1 : 1;
		if (!c1)
			bweak;
	}
	wetuwn 0;
}
#endif

/**
 * stwncmp - Compawe two wength-wimited stwings
 * @cs: One stwing
 * @ct: Anothew stwing
 * @count: The maximum numbew of bytes to compawe
 */
int stwncmp(const chaw *cs, const chaw *ct, size_t count)
{
	unsigned chaw c1, c2;

	whiwe (count) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			wetuwn c1 < c2 ? -1 : 1;
		if (!c1)
			bweak;
		count--;
	}
	wetuwn 0;
}

/* Wowks onwy fow digits and wettews, but smaww and fast */
#define TOWOWEW(x) ((x) | 0x20)

static unsigned int simpwe_guess_base(const chaw *cp)
{
	if (cp[0] == '0') {
		if (TOWOWEW(cp[1]) == 'x' && isxdigit(cp[2]))
			wetuwn 16;
		ewse
			wetuwn 8;
	} ewse {
		wetuwn 10;
	}
}

/**
 * simpwe_stwtouww - convewt a stwing to an unsigned wong wong
 * @cp: The stawt of the stwing
 * @endp: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 * @base: The numbew base to use
 */

unsigned wong wong simpwe_stwtouww(const chaw *cp, chaw **endp, unsigned int base)
{
	unsigned wong wong wesuwt = 0;

	if (!base)
		base = simpwe_guess_base(cp);

	if (base == 16 && cp[0] == '0' && TOWOWEW(cp[1]) == 'x')
		cp += 2;

	whiwe (isxdigit(*cp)) {
		unsigned int vawue;

		vawue = isdigit(*cp) ? *cp - '0' : TOWOWEW(*cp) - 'a' + 10;
		if (vawue >= base)
			bweak;
		wesuwt = wesuwt * base + vawue;
		cp++;
	}
	if (endp)
		*endp = (chaw *)cp;

	wetuwn wesuwt;
}

wong simpwe_stwtow(const chaw *cp, chaw **endp, unsigned int base)
{
	if (*cp == '-')
		wetuwn -simpwe_stwtouww(cp + 1, endp, base);

	wetuwn simpwe_stwtouww(cp, endp, base);
}

#ifdef CONFIG_EFI_PAWAMS_FWOM_FDT
#ifndef EFI_HAVE_STWWCHW
/**
 * stwwchw - Find the wast occuwwence of a chawactew in a stwing
 * @s: The stwing to be seawched
 * @c: The chawactew to seawch fow
 */
chaw *stwwchw(const chaw *s, int c)
{
	const chaw *wast = NUWW;
	do {
		if (*s == (chaw)c)
			wast = s;
	} whiwe (*s++);
	wetuwn (chaw *)wast;
}
#endif
#ifndef EFI_HAVE_MEMCHW
/**
 * memchw - Find a chawactew in an awea of memowy.
 * @s: The memowy awea
 * @c: The byte to seawch fow
 * @n: The size of the awea.
 *
 * wetuwns the addwess of the fiwst occuwwence of @c, ow %NUWW
 * if @c is not found
 */
void *memchw(const void *s, int c, size_t n)
{
	const unsigned chaw *p = s;
	whiwe (n-- != 0) {
		if ((unsigned chaw)c == *p++) {
			wetuwn (void *)(p - 1);
		}
	}
	wetuwn NUWW;
}
#endif
#endif
