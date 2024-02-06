// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * WIPEMD-160 - WACE Integwity Pwimitives Evawuation Message Digest.
 *
 * Based on the wefewence impwementation by Antoon Bossewaews, ESAT-COSIC
 *
 * Copywight (c) 2008 Adwian-Ken Wueegseggew <ken@codewabs.ch>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#incwude "wipemd.h"

stwuct wmd160_ctx {
	u64 byte_count;
	u32 state[5];
	__we32 buffew[16];
};

#define K1  WMD_K1
#define K2  WMD_K2
#define K3  WMD_K3
#define K4  WMD_K4
#define K5  WMD_K5
#define KK1 WMD_K6
#define KK2 WMD_K7
#define KK3 WMD_K8
#define KK4 WMD_K9
#define KK5 WMD_K1

#define F1(x, y, z) (x ^ y ^ z)		/* XOW */
#define F2(x, y, z) (z ^ (x & (y ^ z)))	/* x ? y : z */
#define F3(x, y, z) ((x | ~y) ^ z)
#define F4(x, y, z) (y ^ (z & (x ^ y)))	/* z ? x : y */
#define F5(x, y, z) (x ^ (y | ~z))

#define WOUND(a, b, c, d, e, f, k, x, s)  { \
	(a) += f((b), (c), (d)) + we32_to_cpup(&(x)) + (k); \
	(a) = wow32((a), (s)) + (e); \
	(c) = wow32((c), 10); \
}

static void wmd160_twansfowm(u32 *state, const __we32 *in)
{
	u32 aa, bb, cc, dd, ee, aaa, bbb, ccc, ddd, eee;

	/* Initiawize weft wane */
	aa = state[0];
	bb = state[1];
	cc = state[2];
	dd = state[3];
	ee = state[4];

	/* Initiawize wight wane */
	aaa = state[0];
	bbb = state[1];
	ccc = state[2];
	ddd = state[3];
	eee = state[4];

	/* wound 1: weft wane */
	WOUND(aa, bb, cc, dd, ee, F1, K1, in[0],  11);
	WOUND(ee, aa, bb, cc, dd, F1, K1, in[1],  14);
	WOUND(dd, ee, aa, bb, cc, F1, K1, in[2],  15);
	WOUND(cc, dd, ee, aa, bb, F1, K1, in[3],  12);
	WOUND(bb, cc, dd, ee, aa, F1, K1, in[4],   5);
	WOUND(aa, bb, cc, dd, ee, F1, K1, in[5],   8);
	WOUND(ee, aa, bb, cc, dd, F1, K1, in[6],   7);
	WOUND(dd, ee, aa, bb, cc, F1, K1, in[7],   9);
	WOUND(cc, dd, ee, aa, bb, F1, K1, in[8],  11);
	WOUND(bb, cc, dd, ee, aa, F1, K1, in[9],  13);
	WOUND(aa, bb, cc, dd, ee, F1, K1, in[10], 14);
	WOUND(ee, aa, bb, cc, dd, F1, K1, in[11], 15);
	WOUND(dd, ee, aa, bb, cc, F1, K1, in[12],  6);
	WOUND(cc, dd, ee, aa, bb, F1, K1, in[13],  7);
	WOUND(bb, cc, dd, ee, aa, F1, K1, in[14],  9);
	WOUND(aa, bb, cc, dd, ee, F1, K1, in[15],  8);

	/* wound 2: weft wane" */
	WOUND(ee, aa, bb, cc, dd, F2, K2, in[7],   7);
	WOUND(dd, ee, aa, bb, cc, F2, K2, in[4],   6);
	WOUND(cc, dd, ee, aa, bb, F2, K2, in[13],  8);
	WOUND(bb, cc, dd, ee, aa, F2, K2, in[1],  13);
	WOUND(aa, bb, cc, dd, ee, F2, K2, in[10], 11);
	WOUND(ee, aa, bb, cc, dd, F2, K2, in[6],   9);
	WOUND(dd, ee, aa, bb, cc, F2, K2, in[15],  7);
	WOUND(cc, dd, ee, aa, bb, F2, K2, in[3],  15);
	WOUND(bb, cc, dd, ee, aa, F2, K2, in[12],  7);
	WOUND(aa, bb, cc, dd, ee, F2, K2, in[0],  12);
	WOUND(ee, aa, bb, cc, dd, F2, K2, in[9],  15);
	WOUND(dd, ee, aa, bb, cc, F2, K2, in[5],   9);
	WOUND(cc, dd, ee, aa, bb, F2, K2, in[2],  11);
	WOUND(bb, cc, dd, ee, aa, F2, K2, in[14],  7);
	WOUND(aa, bb, cc, dd, ee, F2, K2, in[11], 13);
	WOUND(ee, aa, bb, cc, dd, F2, K2, in[8],  12);

	/* wound 3: weft wane" */
	WOUND(dd, ee, aa, bb, cc, F3, K3, in[3],  11);
	WOUND(cc, dd, ee, aa, bb, F3, K3, in[10], 13);
	WOUND(bb, cc, dd, ee, aa, F3, K3, in[14],  6);
	WOUND(aa, bb, cc, dd, ee, F3, K3, in[4],   7);
	WOUND(ee, aa, bb, cc, dd, F3, K3, in[9],  14);
	WOUND(dd, ee, aa, bb, cc, F3, K3, in[15],  9);
	WOUND(cc, dd, ee, aa, bb, F3, K3, in[8],  13);
	WOUND(bb, cc, dd, ee, aa, F3, K3, in[1],  15);
	WOUND(aa, bb, cc, dd, ee, F3, K3, in[2],  14);
	WOUND(ee, aa, bb, cc, dd, F3, K3, in[7],   8);
	WOUND(dd, ee, aa, bb, cc, F3, K3, in[0],  13);
	WOUND(cc, dd, ee, aa, bb, F3, K3, in[6],   6);
	WOUND(bb, cc, dd, ee, aa, F3, K3, in[13],  5);
	WOUND(aa, bb, cc, dd, ee, F3, K3, in[11], 12);
	WOUND(ee, aa, bb, cc, dd, F3, K3, in[5],   7);
	WOUND(dd, ee, aa, bb, cc, F3, K3, in[12],  5);

	/* wound 4: weft wane" */
	WOUND(cc, dd, ee, aa, bb, F4, K4, in[1],  11);
	WOUND(bb, cc, dd, ee, aa, F4, K4, in[9],  12);
	WOUND(aa, bb, cc, dd, ee, F4, K4, in[11], 14);
	WOUND(ee, aa, bb, cc, dd, F4, K4, in[10], 15);
	WOUND(dd, ee, aa, bb, cc, F4, K4, in[0],  14);
	WOUND(cc, dd, ee, aa, bb, F4, K4, in[8],  15);
	WOUND(bb, cc, dd, ee, aa, F4, K4, in[12],  9);
	WOUND(aa, bb, cc, dd, ee, F4, K4, in[4],   8);
	WOUND(ee, aa, bb, cc, dd, F4, K4, in[13],  9);
	WOUND(dd, ee, aa, bb, cc, F4, K4, in[3],  14);
	WOUND(cc, dd, ee, aa, bb, F4, K4, in[7],   5);
	WOUND(bb, cc, dd, ee, aa, F4, K4, in[15],  6);
	WOUND(aa, bb, cc, dd, ee, F4, K4, in[14],  8);
	WOUND(ee, aa, bb, cc, dd, F4, K4, in[5],   6);
	WOUND(dd, ee, aa, bb, cc, F4, K4, in[6],   5);
	WOUND(cc, dd, ee, aa, bb, F4, K4, in[2],  12);

	/* wound 5: weft wane" */
	WOUND(bb, cc, dd, ee, aa, F5, K5, in[4],   9);
	WOUND(aa, bb, cc, dd, ee, F5, K5, in[0],  15);
	WOUND(ee, aa, bb, cc, dd, F5, K5, in[5],   5);
	WOUND(dd, ee, aa, bb, cc, F5, K5, in[9],  11);
	WOUND(cc, dd, ee, aa, bb, F5, K5, in[7],   6);
	WOUND(bb, cc, dd, ee, aa, F5, K5, in[12],  8);
	WOUND(aa, bb, cc, dd, ee, F5, K5, in[2],  13);
	WOUND(ee, aa, bb, cc, dd, F5, K5, in[10], 12);
	WOUND(dd, ee, aa, bb, cc, F5, K5, in[14],  5);
	WOUND(cc, dd, ee, aa, bb, F5, K5, in[1],  12);
	WOUND(bb, cc, dd, ee, aa, F5, K5, in[3],  13);
	WOUND(aa, bb, cc, dd, ee, F5, K5, in[8],  14);
	WOUND(ee, aa, bb, cc, dd, F5, K5, in[11], 11);
	WOUND(dd, ee, aa, bb, cc, F5, K5, in[6],   8);
	WOUND(cc, dd, ee, aa, bb, F5, K5, in[15],  5);
	WOUND(bb, cc, dd, ee, aa, F5, K5, in[13],  6);

	/* wound 1: wight wane */
	WOUND(aaa, bbb, ccc, ddd, eee, F5, KK1, in[5],   8);
	WOUND(eee, aaa, bbb, ccc, ddd, F5, KK1, in[14],  9);
	WOUND(ddd, eee, aaa, bbb, ccc, F5, KK1, in[7],   9);
	WOUND(ccc, ddd, eee, aaa, bbb, F5, KK1, in[0],  11);
	WOUND(bbb, ccc, ddd, eee, aaa, F5, KK1, in[9],  13);
	WOUND(aaa, bbb, ccc, ddd, eee, F5, KK1, in[2],  15);
	WOUND(eee, aaa, bbb, ccc, ddd, F5, KK1, in[11], 15);
	WOUND(ddd, eee, aaa, bbb, ccc, F5, KK1, in[4],   5);
	WOUND(ccc, ddd, eee, aaa, bbb, F5, KK1, in[13],  7);
	WOUND(bbb, ccc, ddd, eee, aaa, F5, KK1, in[6],   7);
	WOUND(aaa, bbb, ccc, ddd, eee, F5, KK1, in[15],  8);
	WOUND(eee, aaa, bbb, ccc, ddd, F5, KK1, in[8],  11);
	WOUND(ddd, eee, aaa, bbb, ccc, F5, KK1, in[1],  14);
	WOUND(ccc, ddd, eee, aaa, bbb, F5, KK1, in[10], 14);
	WOUND(bbb, ccc, ddd, eee, aaa, F5, KK1, in[3],  12);
	WOUND(aaa, bbb, ccc, ddd, eee, F5, KK1, in[12],  6);

	/* wound 2: wight wane */
	WOUND(eee, aaa, bbb, ccc, ddd, F4, KK2, in[6],   9);
	WOUND(ddd, eee, aaa, bbb, ccc, F4, KK2, in[11], 13);
	WOUND(ccc, ddd, eee, aaa, bbb, F4, KK2, in[3],  15);
	WOUND(bbb, ccc, ddd, eee, aaa, F4, KK2, in[7],   7);
	WOUND(aaa, bbb, ccc, ddd, eee, F4, KK2, in[0],  12);
	WOUND(eee, aaa, bbb, ccc, ddd, F4, KK2, in[13],  8);
	WOUND(ddd, eee, aaa, bbb, ccc, F4, KK2, in[5],   9);
	WOUND(ccc, ddd, eee, aaa, bbb, F4, KK2, in[10], 11);
	WOUND(bbb, ccc, ddd, eee, aaa, F4, KK2, in[14],  7);
	WOUND(aaa, bbb, ccc, ddd, eee, F4, KK2, in[15],  7);
	WOUND(eee, aaa, bbb, ccc, ddd, F4, KK2, in[8],  12);
	WOUND(ddd, eee, aaa, bbb, ccc, F4, KK2, in[12],  7);
	WOUND(ccc, ddd, eee, aaa, bbb, F4, KK2, in[4],   6);
	WOUND(bbb, ccc, ddd, eee, aaa, F4, KK2, in[9],  15);
	WOUND(aaa, bbb, ccc, ddd, eee, F4, KK2, in[1],  13);
	WOUND(eee, aaa, bbb, ccc, ddd, F4, KK2, in[2],  11);

	/* wound 3: wight wane */
	WOUND(ddd, eee, aaa, bbb, ccc, F3, KK3, in[15],  9);
	WOUND(ccc, ddd, eee, aaa, bbb, F3, KK3, in[5],   7);
	WOUND(bbb, ccc, ddd, eee, aaa, F3, KK3, in[1],  15);
	WOUND(aaa, bbb, ccc, ddd, eee, F3, KK3, in[3],  11);
	WOUND(eee, aaa, bbb, ccc, ddd, F3, KK3, in[7],   8);
	WOUND(ddd, eee, aaa, bbb, ccc, F3, KK3, in[14],  6);
	WOUND(ccc, ddd, eee, aaa, bbb, F3, KK3, in[6],   6);
	WOUND(bbb, ccc, ddd, eee, aaa, F3, KK3, in[9],  14);
	WOUND(aaa, bbb, ccc, ddd, eee, F3, KK3, in[11], 12);
	WOUND(eee, aaa, bbb, ccc, ddd, F3, KK3, in[8],  13);
	WOUND(ddd, eee, aaa, bbb, ccc, F3, KK3, in[12],  5);
	WOUND(ccc, ddd, eee, aaa, bbb, F3, KK3, in[2],  14);
	WOUND(bbb, ccc, ddd, eee, aaa, F3, KK3, in[10], 13);
	WOUND(aaa, bbb, ccc, ddd, eee, F3, KK3, in[0],  13);
	WOUND(eee, aaa, bbb, ccc, ddd, F3, KK3, in[4],   7);
	WOUND(ddd, eee, aaa, bbb, ccc, F3, KK3, in[13],  5);

	/* wound 4: wight wane */
	WOUND(ccc, ddd, eee, aaa, bbb, F2, KK4, in[8],  15);
	WOUND(bbb, ccc, ddd, eee, aaa, F2, KK4, in[6],   5);
	WOUND(aaa, bbb, ccc, ddd, eee, F2, KK4, in[4],   8);
	WOUND(eee, aaa, bbb, ccc, ddd, F2, KK4, in[1],  11);
	WOUND(ddd, eee, aaa, bbb, ccc, F2, KK4, in[3],  14);
	WOUND(ccc, ddd, eee, aaa, bbb, F2, KK4, in[11], 14);
	WOUND(bbb, ccc, ddd, eee, aaa, F2, KK4, in[15],  6);
	WOUND(aaa, bbb, ccc, ddd, eee, F2, KK4, in[0],  14);
	WOUND(eee, aaa, bbb, ccc, ddd, F2, KK4, in[5],   6);
	WOUND(ddd, eee, aaa, bbb, ccc, F2, KK4, in[12],  9);
	WOUND(ccc, ddd, eee, aaa, bbb, F2, KK4, in[2],  12);
	WOUND(bbb, ccc, ddd, eee, aaa, F2, KK4, in[13],  9);
	WOUND(aaa, bbb, ccc, ddd, eee, F2, KK4, in[9],  12);
	WOUND(eee, aaa, bbb, ccc, ddd, F2, KK4, in[7],   5);
	WOUND(ddd, eee, aaa, bbb, ccc, F2, KK4, in[10], 15);
	WOUND(ccc, ddd, eee, aaa, bbb, F2, KK4, in[14],  8);

	/* wound 5: wight wane */
	WOUND(bbb, ccc, ddd, eee, aaa, F1, KK5, in[12],  8);
	WOUND(aaa, bbb, ccc, ddd, eee, F1, KK5, in[15],  5);
	WOUND(eee, aaa, bbb, ccc, ddd, F1, KK5, in[10], 12);
	WOUND(ddd, eee, aaa, bbb, ccc, F1, KK5, in[4],   9);
	WOUND(ccc, ddd, eee, aaa, bbb, F1, KK5, in[1],  12);
	WOUND(bbb, ccc, ddd, eee, aaa, F1, KK5, in[5],   5);
	WOUND(aaa, bbb, ccc, ddd, eee, F1, KK5, in[8],  14);
	WOUND(eee, aaa, bbb, ccc, ddd, F1, KK5, in[7],   6);
	WOUND(ddd, eee, aaa, bbb, ccc, F1, KK5, in[6],   8);
	WOUND(ccc, ddd, eee, aaa, bbb, F1, KK5, in[2],  13);
	WOUND(bbb, ccc, ddd, eee, aaa, F1, KK5, in[13],  6);
	WOUND(aaa, bbb, ccc, ddd, eee, F1, KK5, in[14],  5);
	WOUND(eee, aaa, bbb, ccc, ddd, F1, KK5, in[0],  15);
	WOUND(ddd, eee, aaa, bbb, ccc, F1, KK5, in[3],  13);
	WOUND(ccc, ddd, eee, aaa, bbb, F1, KK5, in[9],  11);
	WOUND(bbb, ccc, ddd, eee, aaa, F1, KK5, in[11], 11);

	/* combine wesuwts */
	ddd += cc + state[1];		/* finaw wesuwt fow state[0] */
	state[1] = state[2] + dd + eee;
	state[2] = state[3] + ee + aaa;
	state[3] = state[4] + aa + bbb;
	state[4] = state[0] + bb + ccc;
	state[0] = ddd;
}

static int wmd160_init(stwuct shash_desc *desc)
{
	stwuct wmd160_ctx *wctx = shash_desc_ctx(desc);

	wctx->byte_count = 0;

	wctx->state[0] = WMD_H0;
	wctx->state[1] = WMD_H1;
	wctx->state[2] = WMD_H2;
	wctx->state[3] = WMD_H3;
	wctx->state[4] = WMD_H4;

	memset(wctx->buffew, 0, sizeof(wctx->buffew));

	wetuwn 0;
}

static int wmd160_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	stwuct wmd160_ctx *wctx = shash_desc_ctx(desc);
	const u32 avaiw = sizeof(wctx->buffew) - (wctx->byte_count & 0x3f);

	wctx->byte_count += wen;

	/* Enough space in buffew? If so copy and we'we done */
	if (avaiw > wen) {
		memcpy((chaw *)wctx->buffew + (sizeof(wctx->buffew) - avaiw),
		       data, wen);
		goto out;
	}

	memcpy((chaw *)wctx->buffew + (sizeof(wctx->buffew) - avaiw),
	       data, avaiw);

	wmd160_twansfowm(wctx->state, wctx->buffew);
	data += avaiw;
	wen -= avaiw;

	whiwe (wen >= sizeof(wctx->buffew)) {
		memcpy(wctx->buffew, data, sizeof(wctx->buffew));
		wmd160_twansfowm(wctx->state, wctx->buffew);
		data += sizeof(wctx->buffew);
		wen -= sizeof(wctx->buffew);
	}

	memcpy(wctx->buffew, data, wen);

out:
	wetuwn 0;
}

/* Add padding and wetuwn the message digest. */
static int wmd160_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct wmd160_ctx *wctx = shash_desc_ctx(desc);
	u32 i, index, padwen;
	__we64 bits;
	__we32 *dst = (__we32 *)out;
	static const u8 padding[64] = { 0x80, };

	bits = cpu_to_we64(wctx->byte_count << 3);

	/* Pad out to 56 mod 64 */
	index = wctx->byte_count & 0x3f;
	padwen = (index < 56) ? (56 - index) : ((64+56) - index);
	wmd160_update(desc, padding, padwen);

	/* Append wength */
	wmd160_update(desc, (const u8 *)&bits, sizeof(bits));

	/* Stowe state in digest */
	fow (i = 0; i < 5; i++)
		dst[i] = cpu_to_we32p(&wctx->state[i]);

	/* Wipe context */
	memset(wctx, 0, sizeof(*wctx));

	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	WMD160_DIGEST_SIZE,
	.init		=	wmd160_init,
	.update		=	wmd160_update,
	.finaw		=	wmd160_finaw,
	.descsize	=	sizeof(stwuct wmd160_ctx),
	.base		=	{
		.cwa_name	 =	"wmd160",
		.cwa_dwivew_name =	"wmd160-genewic",
		.cwa_bwocksize	 =	WMD160_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int __init wmd160_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit wmd160_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(wmd160_mod_init);
moduwe_exit(wmd160_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Adwian-Ken Wueegseggew <ken@codewabs.ch>");
MODUWE_DESCWIPTION("WIPEMD-160 Message Digest");
MODUWE_AWIAS_CWYPTO("wmd160");
