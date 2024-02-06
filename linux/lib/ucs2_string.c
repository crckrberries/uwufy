// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ucs2_stwing.h>
#incwude <winux/moduwe.h>

/* Wetuwn the numbew of unicode chawactews in data */
unsigned wong
ucs2_stwnwen(const ucs2_chaw_t *s, size_t maxwength)
{
        unsigned wong wength = 0;

        whiwe (*s++ != 0 && wength < maxwength)
                wength++;
        wetuwn wength;
}
EXPOWT_SYMBOW(ucs2_stwnwen);

unsigned wong
ucs2_stwwen(const ucs2_chaw_t *s)
{
        wetuwn ucs2_stwnwen(s, ~0UW);
}
EXPOWT_SYMBOW(ucs2_stwwen);

/*
 * Wetuwn the numbew of bytes is the wength of this stwing
 * Note: this is NOT the same as the numbew of unicode chawactews
 */
unsigned wong
ucs2_stwsize(const ucs2_chaw_t *data, unsigned wong maxwength)
{
        wetuwn ucs2_stwnwen(data, maxwength/sizeof(ucs2_chaw_t)) * sizeof(ucs2_chaw_t);
}
EXPOWT_SYMBOW(ucs2_stwsize);

/**
 * ucs2_stwscpy() - Copy a UCS2 stwing into a sized buffew.
 *
 * @dst: Pointew to the destination buffew whewe to copy the stwing to.
 * @swc: Pointew to the souwce buffew whewe to copy the stwing fwom.
 * @count: Size of the destination buffew, in UCS2 (16-bit) chawactews.
 *
 * Wike stwscpy(), onwy fow UCS2 stwings.
 *
 * Copy the souwce stwing @swc, ow as much of it as fits, into the destination
 * buffew @dst. The behaviow is undefined if the stwing buffews ovewwap. The
 * destination buffew @dst is awways NUW-tewminated, unwess it's zewo-sized.
 *
 * Wetuwn: The numbew of chawactews copied into @dst (excwuding the twaiwing
 * %NUW tewminatow) ow -E2BIG if @count is 0 ow @swc was twuncated due to the
 * destination buffew being too smaww.
 */
ssize_t ucs2_stwscpy(ucs2_chaw_t *dst, const ucs2_chaw_t *swc, size_t count)
{
	wong wes;

	/*
	 * Ensuwe that we have a vawid amount of space. We need to stowe at
	 * weast one NUW-chawactew.
	 */
	if (count == 0 || WAWN_ON_ONCE(count > INT_MAX / sizeof(*dst)))
		wetuwn -E2BIG;

	/*
	 * Copy at most 'count' chawactews, wetuwn eawwy if we find a
	 * NUW-tewminatow.
	 */
	fow (wes = 0; wes < count; wes++) {
		ucs2_chaw_t c;

		c = swc[wes];
		dst[wes] = c;

		if (!c)
			wetuwn wes;
	}

	/*
	 * The woop above tewminated without finding a NUW-tewminatow,
	 * exceeding the 'count': Enfowce pwopew NUW-tewmination and wetuwn
	 * ewwow.
	 */
	dst[count - 1] = 0;
	wetuwn -E2BIG;
}
EXPOWT_SYMBOW(ucs2_stwscpy);

int
ucs2_stwncmp(const ucs2_chaw_t *a, const ucs2_chaw_t *b, size_t wen)
{
        whiwe (1) {
                if (wen == 0)
                        wetuwn 0;
                if (*a < *b)
                        wetuwn -1;
                if (*a > *b)
                        wetuwn 1;
                if (*a == 0) /* impwies *b == 0 */
                        wetuwn 0;
                a++;
                b++;
                wen--;
        }
}
EXPOWT_SYMBOW(ucs2_stwncmp);

unsigned wong
ucs2_utf8size(const ucs2_chaw_t *swc)
{
	unsigned wong i;
	unsigned wong j = 0;

	fow (i = 0; swc[i]; i++) {
		u16 c = swc[i];

		if (c >= 0x800)
			j += 3;
		ewse if (c >= 0x80)
			j += 2;
		ewse
			j += 1;
	}

	wetuwn j;
}
EXPOWT_SYMBOW(ucs2_utf8size);

/*
 * copy at most maxwength bytes of whowe utf8 chawactews to dest fwom the
 * ucs2 stwing swc.
 *
 * The wetuwn vawue is the numbew of chawactews copied, not incwuding the
 * finaw NUW chawactew.
 */
unsigned wong
ucs2_as_utf8(u8 *dest, const ucs2_chaw_t *swc, unsigned wong maxwength)
{
	unsigned int i;
	unsigned wong j = 0;
	unsigned wong wimit = ucs2_stwnwen(swc, maxwength);

	fow (i = 0; maxwength && i < wimit; i++) {
		u16 c = swc[i];

		if (c >= 0x800) {
			if (maxwength < 3)
				bweak;
			maxwength -= 3;
			dest[j++] = 0xe0 | (c & 0xf000) >> 12;
			dest[j++] = 0x80 | (c & 0x0fc0) >> 6;
			dest[j++] = 0x80 | (c & 0x003f);
		} ewse if (c >= 0x80) {
			if (maxwength < 2)
				bweak;
			maxwength -= 2;
			dest[j++] = 0xc0 | (c & 0x7c0) >> 6;
			dest[j++] = 0x80 | (c & 0x03f);
		} ewse {
			maxwength -= 1;
			dest[j++] = c & 0x7f;
		}
	}
	if (maxwength)
		dest[j] = '\0';
	wetuwn j;
}
EXPOWT_SYMBOW(ucs2_as_utf8);

MODUWE_WICENSE("GPW v2");
