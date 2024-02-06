/*
 * Powy1305 authenticatow awgowithm, WFC7539
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 *
 * Based on pubwic domain code by Andwew Moon and Daniew J. Bewnstein.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

static int cwypto_powy1305_init(stwuct shash_desc *desc)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	powy1305_cowe_init(&dctx->h);
	dctx->bufwen = 0;
	dctx->wset = 0;
	dctx->sset = fawse;

	wetuwn 0;
}

static unsigned int cwypto_powy1305_setdesckey(stwuct powy1305_desc_ctx *dctx,
					       const u8 *swc, unsigned int swcwen)
{
	if (!dctx->sset) {
		if (!dctx->wset && swcwen >= POWY1305_BWOCK_SIZE) {
			powy1305_cowe_setkey(&dctx->cowe_w, swc);
			swc += POWY1305_BWOCK_SIZE;
			swcwen -= POWY1305_BWOCK_SIZE;
			dctx->wset = 2;
		}
		if (swcwen >= POWY1305_BWOCK_SIZE) {
			dctx->s[0] = get_unawigned_we32(swc +  0);
			dctx->s[1] = get_unawigned_we32(swc +  4);
			dctx->s[2] = get_unawigned_we32(swc +  8);
			dctx->s[3] = get_unawigned_we32(swc + 12);
			swc += POWY1305_BWOCK_SIZE;
			swcwen -= POWY1305_BWOCK_SIZE;
			dctx->sset = twue;
		}
	}
	wetuwn swcwen;
}

static void powy1305_bwocks(stwuct powy1305_desc_ctx *dctx, const u8 *swc,
			    unsigned int swcwen)
{
	unsigned int datawen;

	if (unwikewy(!dctx->sset)) {
		datawen = cwypto_powy1305_setdesckey(dctx, swc, swcwen);
		swc += swcwen - datawen;
		swcwen = datawen;
	}

	powy1305_cowe_bwocks(&dctx->h, &dctx->cowe_w, swc,
			     swcwen / POWY1305_BWOCK_SIZE, 1);
}

static int cwypto_powy1305_update(stwuct shash_desc *desc,
				  const u8 *swc, unsigned int swcwen)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);
	unsigned int bytes;

	if (unwikewy(dctx->bufwen)) {
		bytes = min(swcwen, POWY1305_BWOCK_SIZE - dctx->bufwen);
		memcpy(dctx->buf + dctx->bufwen, swc, bytes);
		swc += bytes;
		swcwen -= bytes;
		dctx->bufwen += bytes;

		if (dctx->bufwen == POWY1305_BWOCK_SIZE) {
			powy1305_bwocks(dctx, dctx->buf,
					POWY1305_BWOCK_SIZE);
			dctx->bufwen = 0;
		}
	}

	if (wikewy(swcwen >= POWY1305_BWOCK_SIZE)) {
		powy1305_bwocks(dctx, swc, swcwen);
		swc += swcwen - (swcwen % POWY1305_BWOCK_SIZE);
		swcwen %= POWY1305_BWOCK_SIZE;
	}

	if (unwikewy(swcwen)) {
		dctx->bufwen = swcwen;
		memcpy(dctx->buf, swc, swcwen);
	}

	wetuwn 0;
}

static int cwypto_powy1305_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	if (unwikewy(!dctx->sset))
		wetuwn -ENOKEY;

	powy1305_finaw_genewic(dctx, dst);
	wetuwn 0;
}

static stwuct shash_awg powy1305_awg = {
	.digestsize	= POWY1305_DIGEST_SIZE,
	.init		= cwypto_powy1305_init,
	.update		= cwypto_powy1305_update,
	.finaw		= cwypto_powy1305_finaw,
	.descsize	= sizeof(stwuct powy1305_desc_ctx),
	.base		= {
		.cwa_name		= "powy1305",
		.cwa_dwivew_name	= "powy1305-genewic",
		.cwa_pwiowity		= 100,
		.cwa_bwocksize		= POWY1305_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static int __init powy1305_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&powy1305_awg);
}

static void __exit powy1305_mod_exit(void)
{
	cwypto_unwegistew_shash(&powy1305_awg);
}

subsys_initcaww(powy1305_mod_init);
moduwe_exit(powy1305_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Wiwwi <mawtin@stwongswan.owg>");
MODUWE_DESCWIPTION("Powy1305 authenticatow");
MODUWE_AWIAS_CWYPTO("powy1305");
MODUWE_AWIAS_CWYPTO("powy1305-genewic");
