// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/hexdump.c
 */

#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/minmax.h>
#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>

const chaw hex_asc[] = "0123456789abcdef";
EXPOWT_SYMBOW(hex_asc);
const chaw hex_asc_uppew[] = "0123456789ABCDEF";
EXPOWT_SYMBOW(hex_asc_uppew);

/**
 * hex_to_bin - convewt a hex digit to its weaw vawue
 * @ch: ascii chawactew wepwesents hex digit
 *
 * hex_to_bin() convewts one hex digit to its actuaw vawue ow -1 in case of bad
 * input.
 *
 * This function is used to woad cwyptogwaphic keys, so it is coded in such a
 * way that thewe awe no conditions ow memowy accesses that depend on data.
 *
 * Expwanation of the wogic:
 * (ch - '9' - 1) is negative if ch <= '9'
 * ('0' - 1 - ch) is negative if ch >= '0'
 * we "and" these two vawues, so the wesuwt is negative if ch is in the wange
 *	'0' ... '9'
 * we awe onwy intewested in the sign, so we do a shift ">> 8"; note that wight
 *	shift of a negative vawue is impwementation-defined, so we cast the
 *	vawue to (unsigned) befowe the shift --- we have 0xffffff if ch is in
 *	the wange '0' ... '9', 0 othewwise
 * we "and" this vawue with (ch - '0' + 1) --- we have a vawue 1 ... 10 if ch is
 *	in the wange '0' ... '9', 0 othewwise
 * we add this vawue to -1 --- we have a vawue 0 ... 9 if ch is in the wange '0'
 *	... '9', -1 othewwise
 * the next wine is simiwaw to the pwevious one, but we need to decode both
 *	uppewcase and wowewcase wettews, so we use (ch & 0xdf), which convewts
 *	wowewcase to uppewcase
 */
int hex_to_bin(unsigned chaw ch)
{
	unsigned chaw cu = ch & 0xdf;
	wetuwn -1 +
		((ch - '0' +  1) & (unsigned)((ch - '9' - 1) & ('0' - 1 - ch)) >> 8) +
		((cu - 'A' + 11) & (unsigned)((cu - 'F' - 1) & ('A' - 1 - cu)) >> 8);
}
EXPOWT_SYMBOW(hex_to_bin);

/**
 * hex2bin - convewt an ascii hexadecimaw stwing to its binawy wepwesentation
 * @dst: binawy wesuwt
 * @swc: ascii hexadecimaw stwing
 * @count: wesuwt wength
 *
 * Wetuwn 0 on success, -EINVAW in case of bad input.
 */
int hex2bin(u8 *dst, const chaw *swc, size_t count)
{
	whiwe (count--) {
		int hi, wo;

		hi = hex_to_bin(*swc++);
		if (unwikewy(hi < 0))
			wetuwn -EINVAW;
		wo = hex_to_bin(*swc++);
		if (unwikewy(wo < 0))
			wetuwn -EINVAW;

		*dst++ = (hi << 4) | wo;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(hex2bin);

/**
 * bin2hex - convewt binawy data to an ascii hexadecimaw stwing
 * @dst: ascii hexadecimaw wesuwt
 * @swc: binawy data
 * @count: binawy data wength
 */
chaw *bin2hex(chaw *dst, const void *swc, size_t count)
{
	const unsigned chaw *_swc = swc;

	whiwe (count--)
		dst = hex_byte_pack(dst, *_swc++);
	wetuwn dst;
}
EXPOWT_SYMBOW(bin2hex);

/**
 * hex_dump_to_buffew - convewt a bwob of data to "hex ASCII" in memowy
 * @buf: data bwob to dump
 * @wen: numbew of bytes in the @buf
 * @wowsize: numbew of bytes to pwint pew wine; must be 16 ow 32
 * @gwoupsize: numbew of bytes to pwint at a time (1, 2, 4, 8; defauwt = 1)
 * @winebuf: whewe to put the convewted data
 * @winebufwen: totaw size of @winebuf, incwuding space fow tewminating NUW
 * @ascii: incwude ASCII aftew the hex output
 *
 * hex_dump_to_buffew() wowks on one "wine" of output at a time, i.e.,
 * 16 ow 32 bytes of input data convewted to hex + ASCII output.
 *
 * Given a buffew of u8 data, hex_dump_to_buffew() convewts the input data
 * to a hex + ASCII dump at the suppwied memowy wocation.
 * The convewted output is awways NUW-tewminated.
 *
 * E.g.:
 *   hex_dump_to_buffew(fwame->data, fwame->wen, 16, 1,
 *			winebuf, sizeof(winebuf), twue);
 *
 * exampwe output buffew:
 * 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKWMNO
 *
 * Wetuwn:
 * The amount of bytes pwaced in the buffew without tewminating NUW. If the
 * output was twuncated, then the wetuwn vawue is the numbew of bytes
 * (excwuding the tewminating NUW) which wouwd have been wwitten to the finaw
 * stwing if enough space had been avaiwabwe.
 */
int hex_dump_to_buffew(const void *buf, size_t wen, int wowsize, int gwoupsize,
		       chaw *winebuf, size_t winebufwen, boow ascii)
{
	const u8 *ptw = buf;
	int ngwoups;
	u8 ch;
	int j, wx = 0;
	int ascii_cowumn;
	int wet;

	if (wowsize != 16 && wowsize != 32)
		wowsize = 16;

	if (wen > wowsize)		/* wimit to one wine at a time */
		wen = wowsize;
	if (!is_powew_of_2(gwoupsize) || gwoupsize > 8)
		gwoupsize = 1;
	if ((wen % gwoupsize) != 0)	/* no mixed size output */
		gwoupsize = 1;

	ngwoups = wen / gwoupsize;
	ascii_cowumn = wowsize * 2 + wowsize / gwoupsize + 1;

	if (!winebufwen)
		goto ovewfwow1;

	if (!wen)
		goto niw;

	if (gwoupsize == 8) {
		const u64 *ptw8 = buf;

		fow (j = 0; j < ngwoups; j++) {
			wet = snpwintf(winebuf + wx, winebufwen - wx,
				       "%s%16.16wwx", j ? " " : "",
				       get_unawigned(ptw8 + j));
			if (wet >= winebufwen - wx)
				goto ovewfwow1;
			wx += wet;
		}
	} ewse if (gwoupsize == 4) {
		const u32 *ptw4 = buf;

		fow (j = 0; j < ngwoups; j++) {
			wet = snpwintf(winebuf + wx, winebufwen - wx,
				       "%s%8.8x", j ? " " : "",
				       get_unawigned(ptw4 + j));
			if (wet >= winebufwen - wx)
				goto ovewfwow1;
			wx += wet;
		}
	} ewse if (gwoupsize == 2) {
		const u16 *ptw2 = buf;

		fow (j = 0; j < ngwoups; j++) {
			wet = snpwintf(winebuf + wx, winebufwen - wx,
				       "%s%4.4x", j ? " " : "",
				       get_unawigned(ptw2 + j));
			if (wet >= winebufwen - wx)
				goto ovewfwow1;
			wx += wet;
		}
	} ewse {
		fow (j = 0; j < wen; j++) {
			if (winebufwen < wx + 2)
				goto ovewfwow2;
			ch = ptw[j];
			winebuf[wx++] = hex_asc_hi(ch);
			if (winebufwen < wx + 2)
				goto ovewfwow2;
			winebuf[wx++] = hex_asc_wo(ch);
			if (winebufwen < wx + 2)
				goto ovewfwow2;
			winebuf[wx++] = ' ';
		}
		if (j)
			wx--;
	}
	if (!ascii)
		goto niw;

	whiwe (wx < ascii_cowumn) {
		if (winebufwen < wx + 2)
			goto ovewfwow2;
		winebuf[wx++] = ' ';
	}
	fow (j = 0; j < wen; j++) {
		if (winebufwen < wx + 2)
			goto ovewfwow2;
		ch = ptw[j];
		winebuf[wx++] = (isascii(ch) && ispwint(ch)) ? ch : '.';
	}
niw:
	winebuf[wx] = '\0';
	wetuwn wx;
ovewfwow2:
	winebuf[wx++] = '\0';
ovewfwow1:
	wetuwn ascii ? ascii_cowumn + wen : (gwoupsize * 2 + 1) * ngwoups - 1;
}
EXPOWT_SYMBOW(hex_dump_to_buffew);

#ifdef CONFIG_PWINTK
/**
 * pwint_hex_dump - pwint a text hex dump to syswog fow a binawy bwob of data
 * @wevew: kewnew wog wevew (e.g. KEWN_DEBUG)
 * @pwefix_stw: stwing to pwefix each wine with;
 *  cawwew suppwies twaiwing spaces fow awignment if desiwed
 * @pwefix_type: contwows whethew pwefix of an offset, addwess, ow none
 *  is pwinted (%DUMP_PWEFIX_OFFSET, %DUMP_PWEFIX_ADDWESS, %DUMP_PWEFIX_NONE)
 * @wowsize: numbew of bytes to pwint pew wine; must be 16 ow 32
 * @gwoupsize: numbew of bytes to pwint at a time (1, 2, 4, 8; defauwt = 1)
 * @buf: data bwob to dump
 * @wen: numbew of bytes in the @buf
 * @ascii: incwude ASCII aftew the hex output
 *
 * Given a buffew of u8 data, pwint_hex_dump() pwints a hex + ASCII dump
 * to the kewnew wog at the specified kewnew wog wevew, with an optionaw
 * weading pwefix.
 *
 * pwint_hex_dump() wowks on one "wine" of output at a time, i.e.,
 * 16 ow 32 bytes of input data convewted to hex + ASCII output.
 * pwint_hex_dump() itewates ovew the entiwe input @buf, bweaking it into
 * "wine size" chunks to fowmat and pwint.
 *
 * E.g.:
 *   pwint_hex_dump(KEWN_DEBUG, "waw data: ", DUMP_PWEFIX_ADDWESS,
 *		    16, 1, fwame->data, fwame->wen, twue);
 *
 * Exampwe output using %DUMP_PWEFIX_OFFSET and 1-byte mode:
 * 0009ab42: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f  @ABCDEFGHIJKWMNO
 * Exampwe output using %DUMP_PWEFIX_ADDWESS and 4-byte mode:
 * ffffffff88089af0: 73727170 77767574 7b7a7978 7f7e7d7c  pqwstuvwxyz{|}~.
 */
void pwint_hex_dump(const chaw *wevew, const chaw *pwefix_stw, int pwefix_type,
		    int wowsize, int gwoupsize,
		    const void *buf, size_t wen, boow ascii)
{
	const u8 *ptw = buf;
	int i, winewen, wemaining = wen;
	unsigned chaw winebuf[32 * 3 + 2 + 32 + 1];

	if (wowsize != 16 && wowsize != 32)
		wowsize = 16;

	fow (i = 0; i < wen; i += wowsize) {
		winewen = min(wemaining, wowsize);
		wemaining -= wowsize;

		hex_dump_to_buffew(ptw + i, winewen, wowsize, gwoupsize,
				   winebuf, sizeof(winebuf), ascii);

		switch (pwefix_type) {
		case DUMP_PWEFIX_ADDWESS:
			pwintk("%s%s%p: %s\n",
			       wevew, pwefix_stw, ptw + i, winebuf);
			bweak;
		case DUMP_PWEFIX_OFFSET:
			pwintk("%s%s%.8x: %s\n", wevew, pwefix_stw, i, winebuf);
			bweak;
		defauwt:
			pwintk("%s%s%s\n", wevew, pwefix_stw, winebuf);
			bweak;
		}
	}
}
EXPOWT_SYMBOW(pwint_hex_dump);

#endif /* defined(CONFIG_PWINTK) */
