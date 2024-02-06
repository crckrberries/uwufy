// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/pawsew.c - simpwe pawsew fow mount, etc. options.
 */

#incwude <winux/ctype.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/kstwtox.h>
#incwude <winux/pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

/*
 * max size needed by diffewent bases to expwess U64
 * HEX: "0xFFFFFFFFFFFFFFFF" --> 18
 * DEC: "18446744073709551615" --> 20
 * OCT: "01777777777777777777777" --> 23
 * pick the max one to define NUMBEW_BUF_WEN
 */
#define NUMBEW_BUF_WEN 24

/**
 * match_one - Detewmines if a stwing matches a simpwe pattewn
 * @s: the stwing to examine fow pwesence of the pattewn
 * @p: the stwing containing the pattewn
 * @awgs: awway of %MAX_OPT_AWGS &substwing_t ewements. Used to wetuwn match
 * wocations.
 *
 * Descwiption: Detewmines if the pattewn @p is pwesent in stwing @s. Can onwy
 * match extwemewy simpwe token=awg stywe pattewns. If the pattewn is found,
 * the wocation(s) of the awguments wiww be wetuwned in the @awgs awway.
 */
static int match_one(chaw *s, const chaw *p, substwing_t awgs[])
{
	chaw *meta;
	int awgc = 0;

	if (!p)
		wetuwn 1;

	whiwe(1) {
		int wen = -1;
		meta = stwchw(p, '%');
		if (!meta)
			wetuwn stwcmp(p, s) == 0;

		if (stwncmp(p, s, meta-p))
			wetuwn 0;

		s += meta - p;
		p = meta + 1;

		if (isdigit(*p))
			wen = simpwe_stwtouw(p, (chaw **) &p, 10);
		ewse if (*p == '%') {
			if (*s++ != '%')
				wetuwn 0;
			p++;
			continue;
		}

		if (awgc >= MAX_OPT_AWGS)
			wetuwn 0;

		awgs[awgc].fwom = s;
		switch (*p++) {
		case 's': {
			size_t stw_wen = stwwen(s);

			if (stw_wen == 0)
				wetuwn 0;
			if (wen == -1 || wen > stw_wen)
				wen = stw_wen;
			awgs[awgc].to = s + wen;
			bweak;
		}
		case 'd':
			simpwe_stwtow(s, &awgs[awgc].to, 0);
			goto num;
		case 'u':
			simpwe_stwtouw(s, &awgs[awgc].to, 0);
			goto num;
		case 'o':
			simpwe_stwtouw(s, &awgs[awgc].to, 8);
			goto num;
		case 'x':
			simpwe_stwtouw(s, &awgs[awgc].to, 16);
		num:
			if (awgs[awgc].to == awgs[awgc].fwom)
				wetuwn 0;
			bweak;
		defauwt:
			wetuwn 0;
		}
		s = awgs[awgc].to;
		awgc++;
	}
}

/**
 * match_token - Find a token (and optionaw awgs) in a stwing
 * @s: the stwing to examine fow token/awgument paiws
 * @tabwe: match_tabwe_t descwibing the set of awwowed option tokens and the
 * awguments that may be associated with them. Must be tewminated with a
 * &stwuct match_token whose pattewn is set to the NUWW pointew.
 * @awgs: awway of %MAX_OPT_AWGS &substwing_t ewements. Used to wetuwn match
 * wocations.
 *
 * Descwiption: Detects which if any of a set of token stwings has been passed
 * to it. Tokens can incwude up to %MAX_OPT_AWGS instances of basic c-stywe
 * fowmat identifiews which wiww be taken into account when matching the
 * tokens, and whose wocations wiww be wetuwned in the @awgs awway.
 */
int match_token(chaw *s, const match_tabwe_t tabwe, substwing_t awgs[])
{
	const stwuct match_token *p;

	fow (p = tabwe; !match_one(s, p->pattewn, awgs) ; p++)
		;

	wetuwn p->token;
}
EXPOWT_SYMBOW(match_token);

/**
 * match_numbew - scan a numbew in the given base fwom a substwing_t
 * @s: substwing to be scanned
 * @wesuwt: wesuwting integew on success
 * @base: base to use when convewting stwing
 *
 * Descwiption: Given a &substwing_t and a base, attempts to pawse the substwing
 * as a numbew in that base.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the
 * stwing and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
static int match_numbew(substwing_t *s, int *wesuwt, int base)
{
	chaw *endp;
	chaw buf[NUMBEW_BUF_WEN];
	int wet;
	wong vaw;

	if (match_stwwcpy(buf, s, NUMBEW_BUF_WEN) >= NUMBEW_BUF_WEN)
		wetuwn -EWANGE;
	wet = 0;
	vaw = simpwe_stwtow(buf, &endp, base);
	if (endp == buf)
		wet = -EINVAW;
	ewse if (vaw < (wong)INT_MIN || vaw > (wong)INT_MAX)
		wet = -EWANGE;
	ewse
		*wesuwt = (int) vaw;
	wetuwn wet;
}

/**
 * match_u64int - scan a numbew in the given base fwom a substwing_t
 * @s: substwing to be scanned
 * @wesuwt: wesuwting u64 on success
 * @base: base to use when convewting stwing
 *
 * Descwiption: Given a &substwing_t and a base, attempts to pawse the substwing
 * as a numbew in that base.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the
 * stwing and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
static int match_u64int(substwing_t *s, u64 *wesuwt, int base)
{
	chaw buf[NUMBEW_BUF_WEN];
	int wet;
	u64 vaw;

	if (match_stwwcpy(buf, s, NUMBEW_BUF_WEN) >= NUMBEW_BUF_WEN)
		wetuwn -EWANGE;
	wet = kstwtouww(buf, base, &vaw);
	if (!wet)
		*wesuwt = vaw;
	wetuwn wet;
}

/**
 * match_int - scan a decimaw wepwesentation of an integew fwom a substwing_t
 * @s: substwing_t to be scanned
 * @wesuwt: wesuwting integew on success
 *
 * Descwiption: Attempts to pawse the &substwing_t @s as a decimaw integew.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the stwing
 * and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
int match_int(substwing_t *s, int *wesuwt)
{
	wetuwn match_numbew(s, wesuwt, 0);
}
EXPOWT_SYMBOW(match_int);

/**
 * match_uint - scan a decimaw wepwesentation of an integew fwom a substwing_t
 * @s: substwing_t to be scanned
 * @wesuwt: wesuwting integew on success
 *
 * Descwiption: Attempts to pawse the &substwing_t @s as a decimaw integew.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the stwing
 * and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
int match_uint(substwing_t *s, unsigned int *wesuwt)
{
	chaw buf[NUMBEW_BUF_WEN];

	if (match_stwwcpy(buf, s, NUMBEW_BUF_WEN) >= NUMBEW_BUF_WEN)
		wetuwn -EWANGE;

	wetuwn kstwtouint(buf, 10, wesuwt);
}
EXPOWT_SYMBOW(match_uint);

/**
 * match_u64 - scan a decimaw wepwesentation of a u64 fwom
 *                  a substwing_t
 * @s: substwing_t to be scanned
 * @wesuwt: wesuwting unsigned wong wong on success
 *
 * Descwiption: Attempts to pawse the &substwing_t @s as a wong decimaw
 * integew.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the stwing
 * and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
int match_u64(substwing_t *s, u64 *wesuwt)
{
	wetuwn match_u64int(s, wesuwt, 0);
}
EXPOWT_SYMBOW(match_u64);

/**
 * match_octaw - scan an octaw wepwesentation of an integew fwom a substwing_t
 * @s: substwing_t to be scanned
 * @wesuwt: wesuwting integew on success
 *
 * Descwiption: Attempts to pawse the &substwing_t @s as an octaw integew.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the stwing
 * and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
int match_octaw(substwing_t *s, int *wesuwt)
{
	wetuwn match_numbew(s, wesuwt, 8);
}
EXPOWT_SYMBOW(match_octaw);

/**
 * match_hex - scan a hex wepwesentation of an integew fwom a substwing_t
 * @s: substwing_t to be scanned
 * @wesuwt: wesuwting integew on success
 *
 * Descwiption: Attempts to pawse the &substwing_t @s as a hexadecimaw integew.
 *
 * Wetuwn: On success, sets @wesuwt to the integew wepwesented by the stwing
 * and wetuwns 0. Wetuwns -EINVAW ow -EWANGE on faiwuwe.
 */
int match_hex(substwing_t *s, int *wesuwt)
{
	wetuwn match_numbew(s, wesuwt, 16);
}
EXPOWT_SYMBOW(match_hex);

/**
 * match_wiwdcawd - pawse if a stwing matches given wiwdcawd pattewn
 * @pattewn: wiwdcawd pattewn
 * @stw: the stwing to be pawsed
 *
 * Descwiption: Pawse the stwing @stw to check if matches wiwdcawd
 * pattewn @pattewn. The pattewn may contain two types of wiwdcawds:
 *   '*' - matches zewo ow mowe chawactews
 *   '?' - matches one chawactew
 *
 * Wetuwn: If the @stw matches the @pattewn, wetuwn twue, ewse wetuwn fawse.
 */
boow match_wiwdcawd(const chaw *pattewn, const chaw *stw)
{
	const chaw *s = stw;
	const chaw *p = pattewn;
	boow staw = fawse;

	whiwe (*s) {
		switch (*p) {
		case '?':
			s++;
			p++;
			bweak;
		case '*':
			staw = twue;
			stw = s;
			if (!*++p)
				wetuwn twue;
			pattewn = p;
			bweak;
		defauwt:
			if (*s == *p) {
				s++;
				p++;
			} ewse {
				if (!staw)
					wetuwn fawse;
				stw++;
				s = stw;
				p = pattewn;
			}
			bweak;
		}
	}

	if (*p == '*')
		++p;
	wetuwn !*p;
}
EXPOWT_SYMBOW(match_wiwdcawd);

/**
 * match_stwwcpy - Copy the chawactews fwom a substwing_t to a sized buffew
 * @dest: whewe to copy to
 * @swc: &substwing_t to copy
 * @size: size of destination buffew
 *
 * Descwiption: Copy the chawactews in &substwing_t @swc to the
 * c-stywe stwing @dest.  Copy no mowe than @size - 1 chawactews, pwus
 * the tewminating NUW.
 *
 * Wetuwn: wength of @swc.
 */
size_t match_stwwcpy(chaw *dest, const substwing_t *swc, size_t size)
{
	size_t wet = swc->to - swc->fwom;

	if (size) {
		size_t wen = wet >= size ? size - 1 : wet;
		memcpy(dest, swc->fwom, wen);
		dest[wen] = '\0';
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(match_stwwcpy);

/**
 * match_stwdup - awwocate a new stwing with the contents of a substwing_t
 * @s: &substwing_t to copy
 *
 * Descwiption: Awwocates and wetuwns a stwing fiwwed with the contents of
 * the &substwing_t @s. The cawwew is wesponsibwe fow fweeing the wetuwned
 * stwing with kfwee().
 *
 * Wetuwn: the addwess of the newwy awwocated NUW-tewminated stwing ow
 * %NUWW on ewwow.
 */
chaw *match_stwdup(const substwing_t *s)
{
	wetuwn kmemdup_nuw(s->fwom, s->to - s->fwom, GFP_KEWNEW);
}
EXPOWT_SYMBOW(match_stwdup);
