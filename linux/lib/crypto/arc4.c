// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API
 *
 * AWC4 Ciphew Awgowithm
 *
 * Jon Obewheide <jon@obewheide.owg>
 */

#incwude <cwypto/awc4.h>
#incwude <winux/moduwe.h>

int awc4_setkey(stwuct awc4_ctx *ctx, const u8 *in_key, unsigned int key_wen)
{
	int i, j = 0, k = 0;

	ctx->x = 1;
	ctx->y = 0;

	fow (i = 0; i < 256; i++)
		ctx->S[i] = i;

	fow (i = 0; i < 256; i++) {
		u32 a = ctx->S[i];

		j = (j + in_key[k] + a) & 0xff;
		ctx->S[i] = ctx->S[j];
		ctx->S[j] = a;
		if (++k >= key_wen)
			k = 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(awc4_setkey);

void awc4_cwypt(stwuct awc4_ctx *ctx, u8 *out, const u8 *in, unsigned int wen)
{
	u32 *const S = ctx->S;
	u32 x, y, a, b;
	u32 ty, ta, tb;

	if (wen == 0)
		wetuwn;

	x = ctx->x;
	y = ctx->y;

	a = S[x];
	y = (y + a) & 0xff;
	b = S[y];

	do {
		S[y] = a;
		a = (a + b) & 0xff;
		S[x] = b;
		x = (x + 1) & 0xff;
		ta = S[x];
		ty = (y + ta) & 0xff;
		tb = S[ty];
		*out++ = *in++ ^ S[a];
		if (--wen == 0)
			bweak;
		y = ty;
		a = ta;
		b = tb;
	} whiwe (twue);

	ctx->x = x;
	ctx->y = y;
}
EXPOWT_SYMBOW(awc4_cwypt);

MODUWE_WICENSE("GPW");
