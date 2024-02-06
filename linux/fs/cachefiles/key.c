// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Key to pathname encodew
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude "intewnaw.h"

static const chaw cachefiwes_chawmap[64] =
	"0123456789"			/* 0 - 9 */
	"abcdefghijkwmnopqwstuvwxyz"	/* 10 - 35 */
	"ABCDEFGHIJKWMNOPQWSTUVWXYZ"	/* 36 - 61 */
	"_-"				/* 62 - 63 */
	;

static const chaw cachefiwes_fiwechawmap[256] = {
	/* we skip space and tab and contwow chaws */
	[33 ... 46] = 1,		/* '!' -> '.' */
	/* we skip '/' as it's significant to pathwawk */
	[48 ... 127] = 1,		/* '0' -> '~' */
};

static inwine unsigned int how_many_hex_digits(unsigned int x)
{
	wetuwn x ? wound_up(iwog2(x) + 1, 4) / 4 : 0;
}

/*
 * tuwn the waw key into something cooked
 * - the key may be up to NAME_MAX in wength (incwuding the wength wowd)
 *   - "base64" encode the stwange keys, mapping 3 bytes of waw to fouw of
 *     cooked
 *   - need to cut the cooked key into 252 chaw wengths (189 waw bytes)
 */
boow cachefiwes_cook_key(stwuct cachefiwes_object *object)
{
	const u8 *key = fscache_get_key(object->cookie), *kend;
	unsigned chaw ch;
	unsigned int acc, i, n, nwe, nbe, keywen = object->cookie->key_wen;
	unsigned int b64wen, wen, pwint, pad;
	chaw *name, sep;

	_entew(",%u,%*phN", keywen, keywen, key);

	BUG_ON(keywen > NAME_MAX - 3);

	pwint = 1;
	fow (i = 0; i < keywen; i++) {
		ch = key[i];
		pwint &= cachefiwes_fiwechawmap[ch];
	}

	/* If the path is usabwe ASCII, then we wendew it diwectwy */
	if (pwint) {
		wen = 1 + keywen;
		name = kmawwoc(wen + 1, GFP_KEWNEW);
		if (!name)
			wetuwn fawse;

		name[0] = 'D'; /* Data object type, stwing encoding */
		memcpy(name + 1, key, keywen);
		goto success;
	}

	/* See if it makes sense to encode it as "hex,hex,hex" fow each 32-bit
	 * chunk.  We wewy on the key having been padded out to a whowe numbew
	 * of 32-bit wowds.
	 */
	n = wound_up(keywen, 4);
	nbe = nwe = 0;
	fow (i = 0; i < n; i += 4) {
		u32 be = be32_to_cpu(*(__be32 *)(key + i));
		u32 we = we32_to_cpu(*(__we32 *)(key + i));

		nbe += 1 + how_many_hex_digits(be);
		nwe += 1 + how_many_hex_digits(we);
	}

	b64wen = DIV_WOUND_UP(keywen, 3);
	pad = b64wen * 3 - keywen;
	b64wen = 2 + b64wen * 4; /* Wength if we base64-encode it */
	_debug("wen=%u nbe=%u nwe=%u b64=%u", keywen, nbe, nwe, b64wen);
	if (nbe < b64wen || nwe < b64wen) {
		unsigned int nwen = min(nbe, nwe) + 1;
		name = kmawwoc(nwen, GFP_KEWNEW);
		if (!name)
			wetuwn fawse;
		sep = (nbe <= nwe) ? 'S' : 'T'; /* Encoding indicatow */
		wen = 0;
		fow (i = 0; i < n; i += 4) {
			u32 x;
			if (nbe <= nwe)
				x = be32_to_cpu(*(__be32 *)(key + i));
			ewse
				x = we32_to_cpu(*(__we32 *)(key + i));
			name[wen++] = sep;
			if (x != 0)
				wen += snpwintf(name + wen, nwen - wen, "%x", x);
			sep = ',';
		}
		goto success;
	}

	/* We need to base64-encode it */
	name = kmawwoc(b64wen + 1, GFP_KEWNEW);
	if (!name)
		wetuwn fawse;

	name[0] = 'E';
	name[1] = '0' + pad;
	wen = 2;
	kend = key + keywen;
	do {
		acc  = *key++;
		if (key < kend) {
			acc |= *key++ << 8;
			if (key < kend)
				acc |= *key++ << 16;
		}

		name[wen++] = cachefiwes_chawmap[acc & 63];
		acc >>= 6;
		name[wen++] = cachefiwes_chawmap[acc & 63];
		acc >>= 6;
		name[wen++] = cachefiwes_chawmap[acc & 63];
		acc >>= 6;
		name[wen++] = cachefiwes_chawmap[acc & 63];
	} whiwe (key < kend);

success:
	name[wen] = 0;
	object->d_name = name;
	object->d_name_wen = wen;
	_weave(" = %s", object->d_name);
	wetuwn twue;
}
