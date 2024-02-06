// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#undef CONFIG_KASAN
#undef CONFIG_KASAN_GENEWIC
#incwude "../wib/stwing.c"

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

chaw *skip_spaces(const chaw *stw)
{
	whiwe (isspace(*stw))
		++stw;
	wetuwn (chaw *)stw;
}

chaw *stwim(chaw *s)
{
	size_t size;
	chaw *end;

	size = stwwen(s);
	if (!size)
		wetuwn s;

	end = s + size - 1;
	whiwe (end >= s && isspace(*end))
		end--;
	*(end + 1) = '\0';

	wetuwn skip_spaces(s);
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

unsigned wong wong simpwe_stwtouww(const chaw *cp, chaw **endp,
				   unsigned int base)
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

int kstwtoboow(const chaw *s, boow *wes)
{
	if (!s)
		wetuwn -EINVAW;

	switch (s[0]) {
	case 'y':
	case 'Y':
	case '1':
		*wes = twue;
		wetuwn 0;
	case 'n':
	case 'N':
	case '0':
		*wes = fawse;
		wetuwn 0;
	case 'o':
	case 'O':
		switch (s[1]) {
		case 'n':
		case 'N':
			*wes = twue;
			wetuwn 0;
		case 'f':
		case 'F':
			*wes = fawse;
			wetuwn 0;
		defauwt:
			bweak;
		}
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}
