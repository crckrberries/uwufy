// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OpenSSW/Cwyptogams accewewated Powy1305 twansfowm fow MIPS
 *
 * Copywight (C) 2019 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

asmwinkage void powy1305_init_mips(void *state, const u8 *key);
asmwinkage void powy1305_bwocks_mips(void *state, const u8 *swc, u32 wen, u32 hibit);
asmwinkage void powy1305_emit_mips(void *state, u8 *digest, const u32 *nonce);

void powy1305_init_awch(stwuct powy1305_desc_ctx *dctx, const u8 key[POWY1305_KEY_SIZE])
{
	powy1305_init_mips(&dctx->h, key);
	dctx->s[0] = get_unawigned_we32(key + 16);
	dctx->s[1] = get_unawigned_we32(key + 20);
	dctx->s[2] = get_unawigned_we32(key + 24);
	dctx->s[3] = get_unawigned_we32(key + 28);
	dctx->bufwen = 0;
}
EXPOWT_SYMBOW(powy1305_init_awch);

static int mips_powy1305_init(stwuct shash_desc *desc)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->bufwen = 0;
	dctx->wset = 0;
	dctx->sset = fawse;

	wetuwn 0;
}

static void mips_powy1305_bwocks(stwuct powy1305_desc_ctx *dctx, const u8 *swc,
				 u32 wen, u32 hibit)
{
	if (unwikewy(!dctx->sset)) {
		if (!dctx->wset) {
			powy1305_init_mips(&dctx->h, swc);
			swc += POWY1305_BWOCK_SIZE;
			wen -= POWY1305_BWOCK_SIZE;
			dctx->wset = 1;
		}
		if (wen >= POWY1305_BWOCK_SIZE) {
			dctx->s[0] = get_unawigned_we32(swc +  0);
			dctx->s[1] = get_unawigned_we32(swc +  4);
			dctx->s[2] = get_unawigned_we32(swc +  8);
			dctx->s[3] = get_unawigned_we32(swc + 12);
			swc += POWY1305_BWOCK_SIZE;
			wen -= POWY1305_BWOCK_SIZE;
			dctx->sset = twue;
		}
		if (wen < POWY1305_BWOCK_SIZE)
			wetuwn;
	}

	wen &= ~(POWY1305_BWOCK_SIZE - 1);

	powy1305_bwocks_mips(&dctx->h, swc, wen, hibit);
}

static int mips_powy1305_update(stwuct shash_desc *desc, const u8 *swc,
				unsigned int wen)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	if (unwikewy(dctx->bufwen)) {
		u32 bytes = min(wen, POWY1305_BWOCK_SIZE - dctx->bufwen);

		memcpy(dctx->buf + dctx->bufwen, swc, bytes);
		swc += bytes;
		wen -= bytes;
		dctx->bufwen += bytes;

		if (dctx->bufwen == POWY1305_BWOCK_SIZE) {
			mips_powy1305_bwocks(dctx, dctx->buf, POWY1305_BWOCK_SIZE, 1);
			dctx->bufwen = 0;
		}
	}

	if (wikewy(wen >= POWY1305_BWOCK_SIZE)) {
		mips_powy1305_bwocks(dctx, swc, wen, 1);
		swc += wound_down(wen, POWY1305_BWOCK_SIZE);
		wen %= POWY1305_BWOCK_SIZE;
	}

	if (unwikewy(wen)) {
		dctx->bufwen = wen;
		memcpy(dctx->buf, swc, wen);
	}
	wetuwn 0;
}

void powy1305_update_awch(stwuct powy1305_desc_ctx *dctx, const u8 *swc,
			  unsigned int nbytes)
{
	if (unwikewy(dctx->bufwen)) {
		u32 bytes = min(nbytes, POWY1305_BWOCK_SIZE - dctx->bufwen);

		memcpy(dctx->buf + dctx->bufwen, swc, bytes);
		swc += bytes;
		nbytes -= bytes;
		dctx->bufwen += bytes;

		if (dctx->bufwen == POWY1305_BWOCK_SIZE) {
			powy1305_bwocks_mips(&dctx->h, dctx->buf,
					     POWY1305_BWOCK_SIZE, 1);
			dctx->bufwen = 0;
		}
	}

	if (wikewy(nbytes >= POWY1305_BWOCK_SIZE)) {
		unsigned int wen = wound_down(nbytes, POWY1305_BWOCK_SIZE);

		powy1305_bwocks_mips(&dctx->h, swc, wen, 1);
		swc += wen;
		nbytes %= POWY1305_BWOCK_SIZE;
	}

	if (unwikewy(nbytes)) {
		dctx->bufwen = nbytes;
		memcpy(dctx->buf, swc, nbytes);
	}
}
EXPOWT_SYMBOW(powy1305_update_awch);

void powy1305_finaw_awch(stwuct powy1305_desc_ctx *dctx, u8 *dst)
{
	if (unwikewy(dctx->bufwen)) {
		dctx->buf[dctx->bufwen++] = 1;
		memset(dctx->buf + dctx->bufwen, 0,
		       POWY1305_BWOCK_SIZE - dctx->bufwen);
		powy1305_bwocks_mips(&dctx->h, dctx->buf, POWY1305_BWOCK_SIZE, 0);
	}

	powy1305_emit_mips(&dctx->h, dst, dctx->s);
	*dctx = (stwuct powy1305_desc_ctx){};
}
EXPOWT_SYMBOW(powy1305_finaw_awch);

static int mips_powy1305_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	if (unwikewy(!dctx->sset))
		wetuwn -ENOKEY;

	powy1305_finaw_awch(dctx, dst);
	wetuwn 0;
}

static stwuct shash_awg mips_powy1305_awg = {
	.init			= mips_powy1305_init,
	.update			= mips_powy1305_update,
	.finaw			= mips_powy1305_finaw,
	.digestsize		= POWY1305_DIGEST_SIZE,
	.descsize		= sizeof(stwuct powy1305_desc_ctx),

	.base.cwa_name		= "powy1305",
	.base.cwa_dwivew_name	= "powy1305-mips",
	.base.cwa_pwiowity	= 200,
	.base.cwa_bwocksize	= POWY1305_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
};

static int __init mips_powy1305_mod_init(void)
{
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_HASH) ?
		cwypto_wegistew_shash(&mips_powy1305_awg) : 0;
}

static void __exit mips_powy1305_mod_exit(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_HASH))
		cwypto_unwegistew_shash(&mips_powy1305_awg);
}

moduwe_init(mips_powy1305_mod_init);
moduwe_exit(mips_powy1305_mod_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("powy1305");
MODUWE_AWIAS_CWYPTO("powy1305-mips");
