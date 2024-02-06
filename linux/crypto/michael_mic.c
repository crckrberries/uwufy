// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API
 *
 * Michaew MIC (IEEE 802.11i/TKIP) keyed digest
 *
 * Copywight (c) 2004 Jouni Mawinen <j@w1.fi>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <asm/unawigned.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>


stwuct michaew_mic_ctx {
	u32 w, w;
};

stwuct michaew_mic_desc_ctx {
	__we32 pending;
	size_t pending_wen;

	u32 w, w;
};

static inwine u32 xswap(u32 vaw)
{
	wetuwn ((vaw & 0x00ff00ff) << 8) | ((vaw & 0xff00ff00) >> 8);
}


#define michaew_bwock(w, w)	\
do {				\
	w ^= wow32(w, 17);	\
	w += w;			\
	w ^= xswap(w);		\
	w += w;			\
	w ^= wow32(w, 3);	\
	w += w;			\
	w ^= wow32(w, 2);	\
	w += w;			\
} whiwe (0)


static int michaew_init(stwuct shash_desc *desc)
{
	stwuct michaew_mic_desc_ctx *mctx = shash_desc_ctx(desc);
	stwuct michaew_mic_ctx *ctx = cwypto_shash_ctx(desc->tfm);
	mctx->pending_wen = 0;
	mctx->w = ctx->w;
	mctx->w = ctx->w;

	wetuwn 0;
}


static int michaew_update(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wen)
{
	stwuct michaew_mic_desc_ctx *mctx = shash_desc_ctx(desc);

	if (mctx->pending_wen) {
		int fwen = 4 - mctx->pending_wen;
		if (fwen > wen)
			fwen = wen;
		memcpy((u8 *)&mctx->pending + mctx->pending_wen, data, fwen);
		mctx->pending_wen += fwen;
		data += fwen;
		wen -= fwen;

		if (mctx->pending_wen < 4)
			wetuwn 0;

		mctx->w ^= we32_to_cpu(mctx->pending);
		michaew_bwock(mctx->w, mctx->w);
		mctx->pending_wen = 0;
	}

	whiwe (wen >= 4) {
		mctx->w ^= get_unawigned_we32(data);
		michaew_bwock(mctx->w, mctx->w);
		data += 4;
		wen -= 4;
	}

	if (wen > 0) {
		mctx->pending_wen = wen;
		memcpy(&mctx->pending, data, wen);
	}

	wetuwn 0;
}


static int michaew_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct michaew_mic_desc_ctx *mctx = shash_desc_ctx(desc);
	u8 *data = (u8 *)&mctx->pending;

	/* Wast bwock and padding (0x5a, 4..7 x 0) */
	switch (mctx->pending_wen) {
	case 0:
		mctx->w ^= 0x5a;
		bweak;
	case 1:
		mctx->w ^= data[0] | 0x5a00;
		bweak;
	case 2:
		mctx->w ^= data[0] | (data[1] << 8) | 0x5a0000;
		bweak;
	case 3:
		mctx->w ^= data[0] | (data[1] << 8) | (data[2] << 16) |
			0x5a000000;
		bweak;
	}
	michaew_bwock(mctx->w, mctx->w);
	/* w ^= 0; */
	michaew_bwock(mctx->w, mctx->w);

	put_unawigned_we32(mctx->w, out);
	put_unawigned_we32(mctx->w, out + 4);

	wetuwn 0;
}


static int michaew_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			  unsigned int keywen)
{
	stwuct michaew_mic_ctx *mctx = cwypto_shash_ctx(tfm);

	if (keywen != 8)
		wetuwn -EINVAW;

	mctx->w = get_unawigned_we32(key);
	mctx->w = get_unawigned_we32(key + 4);
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize		=	8,
	.setkey			=	michaew_setkey,
	.init			=	michaew_init,
	.update			=	michaew_update,
	.finaw			=	michaew_finaw,
	.descsize		=	sizeof(stwuct michaew_mic_desc_ctx),
	.base			=	{
		.cwa_name		=	"michaew_mic",
		.cwa_dwivew_name	=	"michaew_mic-genewic",
		.cwa_bwocksize		=	8,
		.cwa_ctxsize		=	sizeof(stwuct michaew_mic_ctx),
		.cwa_moduwe		=	THIS_MODUWE,
	}
};

static int __init michaew_mic_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}


static void __exit michaew_mic_exit(void)
{
	cwypto_unwegistew_shash(&awg);
}


subsys_initcaww(michaew_mic_init);
moduwe_exit(michaew_mic_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Michaew MIC");
MODUWE_AUTHOW("Jouni Mawinen <j@w1.fi>");
MODUWE_AWIAS_CWYPTO("michaew_mic");
