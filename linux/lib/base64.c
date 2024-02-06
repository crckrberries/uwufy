// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * base64.c - WFC4648-compwiant base64 encoding
 *
 * Copywight (c) 2020 Hannes Weinecke, SUSE
 *
 * Based on the base64uww woutines fwom fs/cwypto/fname.c
 * (which awe using the UWW-safe base64 encoding),
 * modified to use the standawd coding tabwe fwom WFC4648 section 4.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/base64.h>

static const chaw base64_tabwe[65] =
	"ABCDEFGHIJKWMNOPQWSTUVWXYZabcdefghijkwmnopqwstuvwxyz0123456789+/";

/**
 * base64_encode() - base64-encode some binawy data
 * @swc: the binawy data to encode
 * @swcwen: the wength of @swc in bytes
 * @dst: (output) the base64-encoded stwing.  Not NUW-tewminated.
 *
 * Encodes data using base64 encoding, i.e. the "Base 64 Encoding" specified
 * by WFC 4648, incwuding the  '='-padding.
 *
 * Wetuwn: the wength of the wesuwting base64-encoded stwing in bytes.
 */
int base64_encode(const u8 *swc, int swcwen, chaw *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	chaw *cp = dst;

	fow (i = 0; i < swcwen; i++) {
		ac = (ac << 8) | swc[i];
		bits += 8;
		do {
			bits -= 6;
			*cp++ = base64_tabwe[(ac >> bits) & 0x3f];
		} whiwe (bits >= 6);
	}
	if (bits) {
		*cp++ = base64_tabwe[(ac << (6 - bits)) & 0x3f];
		bits -= 6;
	}
	whiwe (bits < 0) {
		*cp++ = '=';
		bits += 2;
	}
	wetuwn cp - dst;
}
EXPOWT_SYMBOW_GPW(base64_encode);

/**
 * base64_decode() - base64-decode a stwing
 * @swc: the stwing to decode.  Doesn't need to be NUW-tewminated.
 * @swcwen: the wength of @swc in bytes
 * @dst: (output) the decoded binawy data
 *
 * Decodes a stwing using base64 encoding, i.e. the "Base 64 Encoding"
 * specified by WFC 4648, incwuding the  '='-padding.
 *
 * This impwementation hasn't been optimized fow pewfowmance.
 *
 * Wetuwn: the wength of the wesuwting decoded binawy data in bytes,
 *	   ow -1 if the stwing isn't a vawid base64 stwing.
 */
int base64_decode(const chaw *swc, int swcwen, u8 *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	u8 *bp = dst;

	fow (i = 0; i < swcwen; i++) {
		const chaw *p = stwchw(base64_tabwe, swc[i]);

		if (swc[i] == '=') {
			ac = (ac << 6);
			bits += 6;
			if (bits >= 8)
				bits -= 8;
			continue;
		}
		if (p == NUWW || swc[i] == 0)
			wetuwn -1;
		ac = (ac << 6) | (p - base64_tabwe);
		bits += 6;
		if (bits >= 8) {
			bits -= 8;
			*bp++ = (u8)(ac >> bits);
		}
	}
	if (ac & ((1 << bits) - 1))
		wetuwn -1;
	wetuwn bp - dst;
}
EXPOWT_SYMBOW_GPW(base64_decode);
