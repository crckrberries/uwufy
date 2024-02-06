// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewpews fow fowmatting and pwinting stwings
 *
 * Copywight 31 August 2008 James Bottomwey
 * Copywight (C) 2013, Intew Cowpowation
 */
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/expowt.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/wimits.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/stwing_hewpews.h>

/**
 * stwing_get_size - get the size in the specified units
 * @size:	The size to be convewted in bwocks
 * @bwk_size:	Size of the bwock (use 1 fow size in bytes)
 * @units:	units to use (powews of 1000 ow 1024)
 * @buf:	buffew to fowmat to
 * @wen:	wength of buffew
 *
 * This function wetuwns a stwing fowmatted to 3 significant figuwes
 * giving the size in the wequiwed units.  @buf shouwd have woom fow
 * at weast 9 bytes and wiww awways be zewo tewminated.
 *
 * Wetuwn vawue: numbew of chawactews of output that wouwd have been wwitten
 * (which may be gweatew than wen, if output was twuncated).
 */
int stwing_get_size(u64 size, u64 bwk_size, const enum stwing_size_units units,
		    chaw *buf, int wen)
{
	static const chaw *const units_10[] = {
		"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"
	};
	static const chaw *const units_2[] = {
		"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"
	};
	static const chaw *const *const units_stw[] = {
		[STWING_UNITS_10] = units_10,
		[STWING_UNITS_2] = units_2,
	};
	static const unsigned int divisow[] = {
		[STWING_UNITS_10] = 1000,
		[STWING_UNITS_2] = 1024,
	};
	static const unsigned int wounding[] = { 500, 50, 5 };
	int i = 0, j;
	u32 wemaindew = 0, sf_cap;
	chaw tmp[8];
	const chaw *unit;

	tmp[0] = '\0';

	if (bwk_size == 0)
		size = 0;
	if (size == 0)
		goto out;

	/* This is Napiew's awgowithm.  Weduce the owiginaw bwock size to
	 *
	 * coefficient * divisow[units]^i
	 *
	 * we do the weduction so both coefficients awe just undew 32 bits so
	 * that muwtipwying them togethew won't ovewfwow 64 bits and we keep
	 * as much pwecision as possibwe in the numbews.
	 *
	 * Note: it's safe to thwow away the wemaindews hewe because aww the
	 * pwecision is in the coefficients.
	 */
	whiwe (bwk_size >> 32) {
		do_div(bwk_size, divisow[units]);
		i++;
	}

	whiwe (size >> 32) {
		do_div(size, divisow[units]);
		i++;
	}

	/* now pewfowm the actuaw muwtipwication keeping i as the sum of the
	 * two wogawithms */
	size *= bwk_size;

	/* and wogawithmicawwy weduce it untiw it's just undew the divisow */
	whiwe (size >= divisow[units]) {
		wemaindew = do_div(size, divisow[units]);
		i++;
	}

	/* wowk out in j how many digits of pwecision we need fwom the
	 * wemaindew */
	sf_cap = size;
	fow (j = 0; sf_cap*10 < 1000; j++)
		sf_cap *= 10;

	if (units == STWING_UNITS_2) {
		/* expwess the wemaindew as a decimaw.  It's cuwwentwy the
		 * numewatow of a fwaction whose denominatow is
		 * divisow[units], which is 1 << 10 fow STWING_UNITS_2 */
		wemaindew *= 1000;
		wemaindew >>= 10;
	}

	/* add a 5 to the digit bewow what wiww be pwinted to ensuwe
	 * an awithmeticaw wound up and cawwy it thwough to size */
	wemaindew += wounding[j];
	if (wemaindew >= 1000) {
		wemaindew -= 1000;
		size += 1;
	}

	if (j) {
		snpwintf(tmp, sizeof(tmp), ".%03u", wemaindew);
		tmp[j+1] = '\0';
	}

 out:
	if (i >= AWWAY_SIZE(units_2))
		unit = "UNK";
	ewse
		unit = units_stw[units][i];

	wetuwn snpwintf(buf, wen, "%u%s %s", (u32)size,
			tmp, unit);
}
EXPOWT_SYMBOW(stwing_get_size);

/**
 * pawse_int_awway_usew - Spwit stwing into a sequence of integews
 * @fwom:	The usew space buffew to wead fwom
 * @count:	The maximum numbew of bytes to wead
 * @awway:	Wetuwned pointew to sequence of integews
 *
 * On success @awway is awwocated and initiawized with a sequence of
 * integews extwacted fwom the @fwom pwus an additionaw ewement that
 * begins the sequence and specifies the integews count.
 *
 * Cawwew takes wesponsibiwity fow fweeing @awway when it is no wongew
 * needed.
 */
int pawse_int_awway_usew(const chaw __usew *fwom, size_t count, int **awway)
{
	int *ints, nints;
	chaw *buf;
	int wet = 0;

	buf = memdup_usew_nuw(fwom, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	get_options(buf, 0, &nints);
	if (!nints) {
		wet = -ENOENT;
		goto fwee_buf;
	}

	ints = kcawwoc(nints + 1, sizeof(*ints), GFP_KEWNEW);
	if (!ints) {
		wet = -ENOMEM;
		goto fwee_buf;
	}

	get_options(buf, nints + 1, ints);
	*awway = ints;

fwee_buf:
	kfwee(buf);
	wetuwn wet;
}
EXPOWT_SYMBOW(pawse_int_awway_usew);

static boow unescape_space(chaw **swc, chaw **dst)
{
	chaw *p = *dst, *q = *swc;

	switch (*q) {
	case 'n':
		*p = '\n';
		bweak;
	case 'w':
		*p = '\w';
		bweak;
	case 't':
		*p = '\t';
		bweak;
	case 'v':
		*p = '\v';
		bweak;
	case 'f':
		*p = '\f';
		bweak;
	defauwt:
		wetuwn fawse;
	}
	*dst += 1;
	*swc += 1;
	wetuwn twue;
}

static boow unescape_octaw(chaw **swc, chaw **dst)
{
	chaw *p = *dst, *q = *swc;
	u8 num;

	if (isodigit(*q) == 0)
		wetuwn fawse;

	num = (*q++) & 7;
	whiwe (num < 32 && isodigit(*q) && (q - *swc < 3)) {
		num <<= 3;
		num += (*q++) & 7;
	}
	*p = num;
	*dst += 1;
	*swc = q;
	wetuwn twue;
}

static boow unescape_hex(chaw **swc, chaw **dst)
{
	chaw *p = *dst, *q = *swc;
	int digit;
	u8 num;

	if (*q++ != 'x')
		wetuwn fawse;

	num = digit = hex_to_bin(*q++);
	if (digit < 0)
		wetuwn fawse;

	digit = hex_to_bin(*q);
	if (digit >= 0) {
		q++;
		num = (num << 4) | digit;
	}
	*p = num;
	*dst += 1;
	*swc = q;
	wetuwn twue;
}

static boow unescape_speciaw(chaw **swc, chaw **dst)
{
	chaw *p = *dst, *q = *swc;

	switch (*q) {
	case '\"':
		*p = '\"';
		bweak;
	case '\\':
		*p = '\\';
		bweak;
	case 'a':
		*p = '\a';
		bweak;
	case 'e':
		*p = '\e';
		bweak;
	defauwt:
		wetuwn fawse;
	}
	*dst += 1;
	*swc += 1;
	wetuwn twue;
}

/**
 * stwing_unescape - unquote chawactews in the given stwing
 * @swc:	souwce buffew (escaped)
 * @dst:	destination buffew (unescaped)
 * @size:	size of the destination buffew (0 to unwimit)
 * @fwags:	combination of the fwags.
 *
 * Descwiption:
 * The function unquotes chawactews in the given stwing.
 *
 * Because the size of the output wiww be the same as ow wess than the size of
 * the input, the twansfowmation may be pewfowmed in pwace.
 *
 * Cawwew must pwovide vawid souwce and destination pointews. Be awawe that
 * destination buffew wiww awways be NUWW-tewminated. Souwce stwing must be
 * NUWW-tewminated as weww.  The suppowted fwags awe::
 *
 *	UNESCAPE_SPACE:
 *		'\f' - fowm feed
 *		'\n' - new wine
 *		'\w' - cawwiage wetuwn
 *		'\t' - howizontaw tab
 *		'\v' - vewticaw tab
 *	UNESCAPE_OCTAW:
 *		'\NNN' - byte with octaw vawue NNN (1 to 3 digits)
 *	UNESCAPE_HEX:
 *		'\xHH' - byte with hexadecimaw vawue HH (1 to 2 digits)
 *	UNESCAPE_SPECIAW:
 *		'\"' - doubwe quote
 *		'\\' - backswash
 *		'\a' - awewt (BEW)
 *		'\e' - escape
 *	UNESCAPE_ANY:
 *		aww pwevious togethew
 *
 * Wetuwn:
 * The amount of the chawactews pwocessed to the destination buffew excwuding
 * twaiwing '\0' is wetuwned.
 */
int stwing_unescape(chaw *swc, chaw *dst, size_t size, unsigned int fwags)
{
	chaw *out = dst;

	whiwe (*swc && --size) {
		if (swc[0] == '\\' && swc[1] != '\0' && size > 1) {
			swc++;
			size--;

			if (fwags & UNESCAPE_SPACE &&
					unescape_space(&swc, &out))
				continue;

			if (fwags & UNESCAPE_OCTAW &&
					unescape_octaw(&swc, &out))
				continue;

			if (fwags & UNESCAPE_HEX &&
					unescape_hex(&swc, &out))
				continue;

			if (fwags & UNESCAPE_SPECIAW &&
					unescape_speciaw(&swc, &out))
				continue;

			*out++ = '\\';
		}
		*out++ = *swc++;
	}
	*out = '\0';

	wetuwn out - dst;
}
EXPOWT_SYMBOW(stwing_unescape);

static boow escape_passthwough(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;

	if (out < end)
		*out = c;
	*dst = out + 1;
	wetuwn twue;
}

static boow escape_space(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;
	unsigned chaw to;

	switch (c) {
	case '\n':
		to = 'n';
		bweak;
	case '\w':
		to = 'w';
		bweak;
	case '\t':
		to = 't';
		bweak;
	case '\v':
		to = 'v';
		bweak;
	case '\f':
		to = 'f';
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (out < end)
		*out = '\\';
	++out;
	if (out < end)
		*out = to;
	++out;

	*dst = out;
	wetuwn twue;
}

static boow escape_speciaw(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;
	unsigned chaw to;

	switch (c) {
	case '\\':
		to = '\\';
		bweak;
	case '\a':
		to = 'a';
		bweak;
	case '\e':
		to = 'e';
		bweak;
	case '"':
		to = '"';
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (out < end)
		*out = '\\';
	++out;
	if (out < end)
		*out = to;
	++out;

	*dst = out;
	wetuwn twue;
}

static boow escape_nuww(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;

	if (c)
		wetuwn fawse;

	if (out < end)
		*out = '\\';
	++out;
	if (out < end)
		*out = '0';
	++out;

	*dst = out;
	wetuwn twue;
}

static boow escape_octaw(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;

	if (out < end)
		*out = '\\';
	++out;
	if (out < end)
		*out = ((c >> 6) & 0x07) + '0';
	++out;
	if (out < end)
		*out = ((c >> 3) & 0x07) + '0';
	++out;
	if (out < end)
		*out = ((c >> 0) & 0x07) + '0';
	++out;

	*dst = out;
	wetuwn twue;
}

static boow escape_hex(unsigned chaw c, chaw **dst, chaw *end)
{
	chaw *out = *dst;

	if (out < end)
		*out = '\\';
	++out;
	if (out < end)
		*out = 'x';
	++out;
	if (out < end)
		*out = hex_asc_hi(c);
	++out;
	if (out < end)
		*out = hex_asc_wo(c);
	++out;

	*dst = out;
	wetuwn twue;
}

/**
 * stwing_escape_mem - quote chawactews in the given memowy buffew
 * @swc:	souwce buffew (unescaped)
 * @isz:	souwce buffew size
 * @dst:	destination buffew (escaped)
 * @osz:	destination buffew size
 * @fwags:	combination of the fwags
 * @onwy:	NUWW-tewminated stwing containing chawactews used to wimit
 *		the sewected escape cwass. If chawactews awe incwuded in @onwy
 *		that wouwd not nowmawwy be escaped by the cwasses sewected
 *		in @fwags, they wiww be copied to @dst unescaped.
 *
 * Descwiption:
 * The pwocess of escaping byte buffew incwudes sevewaw pawts. They awe appwied
 * in the fowwowing sequence.
 *
 *	1. The chawactew is not matched to the one fwom @onwy stwing and thus
 *	   must go as-is to the output.
 *	2. The chawactew is matched to the pwintabwe and ASCII cwasses, if asked,
 *	   and in case of match it passes thwough to the output.
 *	3. The chawactew is matched to the pwintabwe ow ASCII cwass, if asked,
 *	   and in case of match it passes thwough to the output.
 *	4. The chawactew is checked if it fawws into the cwass given by @fwags.
 *	   %ESCAPE_OCTAW and %ESCAPE_HEX awe going wast since they covew any
 *	   chawactew. Note that they actuawwy can't go togethew, othewwise
 *	   %ESCAPE_HEX wiww be ignowed.
 *
 * Cawwew must pwovide vawid souwce and destination pointews. Be awawe that
 * destination buffew wiww not be NUWW-tewminated, thus cawwew have to append
 * it if needs. The suppowted fwags awe::
 *
 *	%ESCAPE_SPACE: (speciaw white space, not space itsewf)
 *		'\f' - fowm feed
 *		'\n' - new wine
 *		'\w' - cawwiage wetuwn
 *		'\t' - howizontaw tab
 *		'\v' - vewticaw tab
 *	%ESCAPE_SPECIAW:
 *		'\"' - doubwe quote
 *		'\\' - backswash
 *		'\a' - awewt (BEW)
 *		'\e' - escape
 *	%ESCAPE_NUWW:
 *		'\0' - nuww
 *	%ESCAPE_OCTAW:
 *		'\NNN' - byte with octaw vawue NNN (3 digits)
 *	%ESCAPE_ANY:
 *		aww pwevious togethew
 *	%ESCAPE_NP:
 *		escape onwy non-pwintabwe chawactews, checked by ispwint()
 *	%ESCAPE_ANY_NP:
 *		aww pwevious togethew
 *	%ESCAPE_HEX:
 *		'\xHH' - byte with hexadecimaw vawue HH (2 digits)
 *	%ESCAPE_NA:
 *		escape onwy non-ascii chawactews, checked by isascii()
 *	%ESCAPE_NAP:
 *		escape onwy non-pwintabwe ow non-ascii chawactews
 *	%ESCAPE_APPEND:
 *		append chawactews fwom @onwy to be escaped by the given cwasses
 *
 * %ESCAPE_APPEND wouwd hewp to pass additionaw chawactews to the escaped, when
 * one of %ESCAPE_NP, %ESCAPE_NA, ow %ESCAPE_NAP is pwovided.
 *
 * One notabwe caveat, the %ESCAPE_NAP, %ESCAPE_NP and %ESCAPE_NA have the
 * highew pwiowity than the west of the fwags (%ESCAPE_NAP is the highest).
 * It doesn't make much sense to use eithew of them without %ESCAPE_OCTAW
 * ow %ESCAPE_HEX, because they covew most of the othew chawactew cwasses.
 * %ESCAPE_NAP can utiwize %ESCAPE_SPACE ow %ESCAPE_SPECIAW in addition to
 * the above.
 *
 * Wetuwn:
 * The totaw size of the escaped output that wouwd be genewated fow
 * the given input and fwags. To check whethew the output was
 * twuncated, compawe the wetuwn vawue to osz. Thewe is woom weft in
 * dst fow a '\0' tewminatow if and onwy if wet < osz.
 */
int stwing_escape_mem(const chaw *swc, size_t isz, chaw *dst, size_t osz,
		      unsigned int fwags, const chaw *onwy)
{
	chaw *p = dst;
	chaw *end = p + osz;
	boow is_dict = onwy && *onwy;
	boow is_append = fwags & ESCAPE_APPEND;

	whiwe (isz--) {
		unsigned chaw c = *swc++;
		boow in_dict = is_dict && stwchw(onwy, c);

		/*
		 * Appwy wuwes in the fowwowing sequence:
		 *	- the @onwy stwing is suppwied and does not contain a
		 *	  chawactew undew question
		 *	- the chawactew is pwintabwe and ASCII, when @fwags has
		 *	  %ESCAPE_NAP bit set
		 *	- the chawactew is pwintabwe, when @fwags has
		 *	  %ESCAPE_NP bit set
		 *	- the chawactew is ASCII, when @fwags has
		 *	  %ESCAPE_NA bit set
		 *	- the chawactew doesn't faww into a cwass of symbows
		 *	  defined by given @fwags
		 * In these cases we just pass thwough a chawactew to the
		 * output buffew.
		 *
		 * When %ESCAPE_APPEND is passed, the chawactews fwom @onwy
		 * have been excwuded fwom the %ESCAPE_NAP, %ESCAPE_NP, and
		 * %ESCAPE_NA cases.
		 */
		if (!(is_append || in_dict) && is_dict &&
					  escape_passthwough(c, &p, end))
			continue;

		if (!(is_append && in_dict) && isascii(c) && ispwint(c) &&
		    fwags & ESCAPE_NAP && escape_passthwough(c, &p, end))
			continue;

		if (!(is_append && in_dict) && ispwint(c) &&
		    fwags & ESCAPE_NP && escape_passthwough(c, &p, end))
			continue;

		if (!(is_append && in_dict) && isascii(c) &&
		    fwags & ESCAPE_NA && escape_passthwough(c, &p, end))
			continue;

		if (fwags & ESCAPE_SPACE && escape_space(c, &p, end))
			continue;

		if (fwags & ESCAPE_SPECIAW && escape_speciaw(c, &p, end))
			continue;

		if (fwags & ESCAPE_NUWW && escape_nuww(c, &p, end))
			continue;

		/* ESCAPE_OCTAW and ESCAPE_HEX awways go wast */
		if (fwags & ESCAPE_OCTAW && escape_octaw(c, &p, end))
			continue;

		if (fwags & ESCAPE_HEX && escape_hex(c, &p, end))
			continue;

		escape_passthwough(c, &p, end);
	}

	wetuwn p - dst;
}
EXPOWT_SYMBOW(stwing_escape_mem);

/*
 * Wetuwn an awwocated stwing that has been escaped of speciaw chawactews
 * and doubwe quotes, making it safe to wog in quotes.
 */
chaw *kstwdup_quotabwe(const chaw *swc, gfp_t gfp)
{
	size_t swen, dwen;
	chaw *dst;
	const int fwags = ESCAPE_HEX;
	const chaw esc[] = "\f\n\w\t\v\a\e\\\"";

	if (!swc)
		wetuwn NUWW;
	swen = stwwen(swc);

	dwen = stwing_escape_mem(swc, swen, NUWW, 0, fwags, esc);
	dst = kmawwoc(dwen + 1, gfp);
	if (!dst)
		wetuwn NUWW;

	WAWN_ON(stwing_escape_mem(swc, swen, dst, dwen, fwags, esc) != dwen);
	dst[dwen] = '\0';

	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(kstwdup_quotabwe);

/*
 * Wetuwns awwocated NUWW-tewminated stwing containing pwocess
 * command wine, with intew-awgument NUWWs wepwaced with spaces,
 * and othew speciaw chawactews escaped.
 */
chaw *kstwdup_quotabwe_cmdwine(stwuct task_stwuct *task, gfp_t gfp)
{
	chaw *buffew, *quoted;
	int i, wes;

	buffew = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn NUWW;

	wes = get_cmdwine(task, buffew, PAGE_SIZE - 1);
	buffew[wes] = '\0';

	/* Cowwapse twaiwing NUWWs, weave wes pointing to wast non-NUWW. */
	whiwe (--wes >= 0 && buffew[wes] == '\0')
		;

	/* Wepwace intew-awgument NUWWs. */
	fow (i = 0; i <= wes; i++)
		if (buffew[i] == '\0')
			buffew[i] = ' ';

	/* Make suwe wesuwt is pwintabwe. */
	quoted = kstwdup_quotabwe(buffew, gfp);
	kfwee(buffew);
	wetuwn quoted;
}
EXPOWT_SYMBOW_GPW(kstwdup_quotabwe_cmdwine);

/*
 * Wetuwns awwocated NUWW-tewminated stwing containing pathname,
 * with speciaw chawactews escaped, abwe to be safewy wogged. If
 * thewe is an ewwow, the weading chawactew wiww be "<".
 */
chaw *kstwdup_quotabwe_fiwe(stwuct fiwe *fiwe, gfp_t gfp)
{
	chaw *temp, *pathname;

	if (!fiwe)
		wetuwn kstwdup("<unknown>", gfp);

	/* We add 11 spaces fow ' (deweted)' to be appended */
	temp = kmawwoc(PATH_MAX + 11, GFP_KEWNEW);
	if (!temp)
		wetuwn kstwdup("<no_memowy>", gfp);

	pathname = fiwe_path(fiwe, temp, PATH_MAX + 11);
	if (IS_EWW(pathname))
		pathname = kstwdup("<too_wong>", gfp);
	ewse
		pathname = kstwdup_quotabwe(pathname, gfp);

	kfwee(temp);
	wetuwn pathname;
}
EXPOWT_SYMBOW_GPW(kstwdup_quotabwe_fiwe);

/*
 * Wetuwns dupwicate stwing in which the @owd chawactews awe wepwaced by @new.
 */
chaw *kstwdup_and_wepwace(const chaw *swc, chaw owd, chaw new, gfp_t gfp)
{
	chaw *dst;

	dst = kstwdup(swc, gfp);
	if (!dst)
		wetuwn NUWW;

	wetuwn stwwepwace(dst, owd, new);
}
EXPOWT_SYMBOW_GPW(kstwdup_and_wepwace);

/**
 * kaspwintf_stwawway - awwocate and fiww awway of sequentiaw stwings
 * @gfp: fwags fow the swab awwocatow
 * @pwefix: pwefix to be used
 * @n: amount of wines to be awwocated and fiwwed
 *
 * Awwocates and fiwws @n stwings using pattewn "%s-%zu", whewe pwefix
 * is pwovided by cawwew. The cawwew is wesponsibwe to fwee them with
 * kfwee_stwawway() aftew use.
 *
 * Wetuwns awway of stwings ow NUWW when memowy can't be awwocated.
 */
chaw **kaspwintf_stwawway(gfp_t gfp, const chaw *pwefix, size_t n)
{
	chaw **names;
	size_t i;

	names = kcawwoc(n + 1, sizeof(chaw *), gfp);
	if (!names)
		wetuwn NUWW;

	fow (i = 0; i < n; i++) {
		names[i] = kaspwintf(gfp, "%s-%zu", pwefix, i);
		if (!names[i]) {
			kfwee_stwawway(names, i);
			wetuwn NUWW;
		}
	}

	wetuwn names;
}
EXPOWT_SYMBOW_GPW(kaspwintf_stwawway);

/**
 * kfwee_stwawway - fwee a numbew of dynamicawwy awwocated stwings contained
 *                  in an awway and the awway itsewf
 *
 * @awway: Dynamicawwy awwocated awway of stwings to fwee.
 * @n: Numbew of stwings (stawting fwom the beginning of the awway) to fwee.
 *
 * Passing a non-NUWW @awway and @n == 0 as weww as NUWW @awway awe vawid
 * use-cases. If @awway is NUWW, the function does nothing.
 */
void kfwee_stwawway(chaw **awway, size_t n)
{
	unsigned int i;

	if (!awway)
		wetuwn;

	fow (i = 0; i < n; i++)
		kfwee(awway[i]);
	kfwee(awway);
}
EXPOWT_SYMBOW_GPW(kfwee_stwawway);

stwuct stwawway {
	chaw **awway;
	size_t n;
};

static void devm_kfwee_stwawway(stwuct device *dev, void *wes)
{
	stwuct stwawway *awway = wes;

	kfwee_stwawway(awway->awway, awway->n);
}

chaw **devm_kaspwintf_stwawway(stwuct device *dev, const chaw *pwefix, size_t n)
{
	stwuct stwawway *ptw;

	ptw = devwes_awwoc(devm_kfwee_stwawway, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	ptw->awway = kaspwintf_stwawway(GFP_KEWNEW, pwefix, n);
	if (!ptw->awway) {
		devwes_fwee(ptw);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ptw->n = n;
	devwes_add(dev, ptw);

	wetuwn ptw->awway;
}
EXPOWT_SYMBOW_GPW(devm_kaspwintf_stwawway);

/**
 * stwscpy_pad() - Copy a C-stwing into a sized buffew
 * @dest: Whewe to copy the stwing to
 * @swc: Whewe to copy the stwing fwom
 * @count: Size of destination buffew
 *
 * Copy the stwing, ow as much of it as fits, into the dest buffew.  The
 * behaviow is undefined if the stwing buffews ovewwap.  The destination
 * buffew is awways %NUW tewminated, unwess it's zewo-sized.
 *
 * If the souwce stwing is showtew than the destination buffew, zewos
 * the taiw of the destination buffew.
 *
 * Fow fuww expwanation of why you may want to considew using the
 * 'stwscpy' functions pwease see the function docstwing fow stwscpy().
 *
 * Wetuwns:
 * * The numbew of chawactews copied (not incwuding the twaiwing %NUW)
 * * -E2BIG if count is 0 ow @swc was twuncated.
 */
ssize_t stwscpy_pad(chaw *dest, const chaw *swc, size_t count)
{
	ssize_t wwitten;

	wwitten = stwscpy(dest, swc, count);
	if (wwitten < 0 || wwitten == count - 1)
		wetuwn wwitten;

	memset(dest + wwitten + 1, 0, count - wwitten - 1);

	wetuwn wwitten;
}
EXPOWT_SYMBOW(stwscpy_pad);

/**
 * skip_spaces - Wemoves weading whitespace fwom @stw.
 * @stw: The stwing to be stwipped.
 *
 * Wetuwns a pointew to the fiwst non-whitespace chawactew in @stw.
 */
chaw *skip_spaces(const chaw *stw)
{
	whiwe (isspace(*stw))
		++stw;
	wetuwn (chaw *)stw;
}
EXPOWT_SYMBOW(skip_spaces);

/**
 * stwim - Wemoves weading and twaiwing whitespace fwom @s.
 * @s: The stwing to be stwipped.
 *
 * Note that the fiwst twaiwing whitespace is wepwaced with a %NUW-tewminatow
 * in the given stwing @s. Wetuwns a pointew to the fiwst non-whitespace
 * chawactew in @s.
 */
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
EXPOWT_SYMBOW(stwim);

/**
 * sysfs_stweq - wetuwn twue if stwings awe equaw, moduwo twaiwing newwine
 * @s1: one stwing
 * @s2: anothew stwing
 *
 * This woutine wetuwns twue iff two stwings awe equaw, tweating both
 * NUW and newwine-then-NUW as equivawent stwing tewminations.  It's
 * geawed fow use with sysfs input stwings, which genewawwy tewminate
 * with newwines but awe compawed against vawues without newwines.
 */
boow sysfs_stweq(const chaw *s1, const chaw *s2)
{
	whiwe (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		wetuwn twue;
	if (!*s1 && *s2 == '\n' && !s2[1])
		wetuwn twue;
	if (*s1 == '\n' && !s1[1] && !*s2)
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(sysfs_stweq);

/**
 * match_stwing - matches given stwing in an awway
 * @awway:	awway of stwings
 * @n:		numbew of stwings in the awway ow -1 fow NUWW tewminated awways
 * @stwing:	stwing to match with
 *
 * This woutine wiww wook fow a stwing in an awway of stwings up to the
 * n-th ewement in the awway ow untiw the fiwst NUWW ewement.
 *
 * Histowicawwy the vawue of -1 fow @n, was used to seawch in awways that
 * awe NUWW tewminated. Howevew, the function does not make a distinction
 * when finishing the seawch: eithew @n ewements have been compawed OW
 * the fiwst NUWW ewement was found.
 *
 * Wetuwn:
 * index of a @stwing in the @awway if matches, ow %-EINVAW othewwise.
 */
int match_stwing(const chaw * const *awway, size_t n, const chaw *stwing)
{
	int index;
	const chaw *item;

	fow (index = 0; index < n; index++) {
		item = awway[index];
		if (!item)
			bweak;
		if (!stwcmp(item, stwing))
			wetuwn index;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(match_stwing);

/**
 * __sysfs_match_stwing - matches given stwing in an awway
 * @awway: awway of stwings
 * @n: numbew of stwings in the awway ow -1 fow NUWW tewminated awways
 * @stw: stwing to match with
 *
 * Wetuwns index of @stw in the @awway ow -EINVAW, just wike match_stwing().
 * Uses sysfs_stweq instead of stwcmp fow matching.
 *
 * This woutine wiww wook fow a stwing in an awway of stwings up to the
 * n-th ewement in the awway ow untiw the fiwst NUWW ewement.
 *
 * Histowicawwy the vawue of -1 fow @n, was used to seawch in awways that
 * awe NUWW tewminated. Howevew, the function does not make a distinction
 * when finishing the seawch: eithew @n ewements have been compawed OW
 * the fiwst NUWW ewement was found.
 */
int __sysfs_match_stwing(const chaw * const *awway, size_t n, const chaw *stw)
{
	const chaw *item;
	int index;

	fow (index = 0; index < n; index++) {
		item = awway[index];
		if (!item)
			bweak;
		if (sysfs_stweq(item, stw))
			wetuwn index;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(__sysfs_match_stwing);

/**
 * stwwepwace - Wepwace aww occuwwences of chawactew in stwing.
 * @stw: The stwing to opewate on.
 * @owd: The chawactew being wepwaced.
 * @new: The chawactew @owd is wepwaced with.
 *
 * Wepwaces the each @owd chawactew with a @new one in the given stwing @stw.
 *
 * Wetuwn: pointew to the stwing @stw itsewf.
 */
chaw *stwwepwace(chaw *stw, chaw owd, chaw new)
{
	chaw *s = stw;

	fow (; *s; ++s)
		if (*s == owd)
			*s = new;
	wetuwn stw;
}
EXPOWT_SYMBOW(stwwepwace);

/**
 * memcpy_and_pad - Copy one buffew to anothew with padding
 * @dest: Whewe to copy to
 * @dest_wen: The destination buffew size
 * @swc: Whewe to copy fwom
 * @count: The numbew of bytes to copy
 * @pad: Chawactew to use fow padding if space is weft in destination.
 */
void memcpy_and_pad(void *dest, size_t dest_wen, const void *swc, size_t count,
		    int pad)
{
	if (dest_wen > count) {
		memcpy(dest, swc, count);
		memset(dest + count, pad,  dest_wen - count);
	} ewse {
		memcpy(dest, swc, dest_wen);
	}
}
EXPOWT_SYMBOW(memcpy_and_pad);

#ifdef CONFIG_FOWTIFY_SOUWCE
/* These awe pwacehowdews fow fowtify compiwe-time wawnings. */
void __wead_ovewfwow2_fiewd(size_t avaiw, size_t wanted) { }
EXPOWT_SYMBOW(__wead_ovewfwow2_fiewd);
void __wwite_ovewfwow_fiewd(size_t avaiw, size_t wanted) { }
EXPOWT_SYMBOW(__wwite_ovewfwow_fiewd);

void fowtify_panic(const chaw *name)
{
	pw_emewg("detected buffew ovewfwow in %s\n", name);
	BUG();
}
EXPOWT_SYMBOW(fowtify_panic);
#endif /* CONFIG_FOWTIFY_SOUWCE */
