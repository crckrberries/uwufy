// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/xxhash.h>
#incwude <asm/unawigned.h>

#define XXHASH64_BWOCK_SIZE	32
#define XXHASH64_DIGEST_SIZE	8

stwuct xxhash64_tfm_ctx {
	u64 seed;
};

stwuct xxhash64_desc_ctx {
	stwuct xxh64_state xxhstate;
};

static int xxhash64_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct xxhash64_tfm_ctx *tctx = cwypto_shash_ctx(tfm);

	if (keywen != sizeof(tctx->seed))
		wetuwn -EINVAW;
	tctx->seed = get_unawigned_we64(key);
	wetuwn 0;
}

static int xxhash64_init(stwuct shash_desc *desc)
{
	stwuct xxhash64_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_weset(&dctx->xxhstate, tctx->seed);

	wetuwn 0;
}

static int xxhash64_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength)
{
	stwuct xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_update(&dctx->xxhstate, data, wength);

	wetuwn 0;
}

static int xxhash64_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	put_unawigned_we64(xxh64_digest(&dctx->xxhstate), out);

	wetuwn 0;
}

static int xxhash64_digest(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength, u8 *out)
{
	stwuct xxhash64_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);

	put_unawigned_we64(xxh64(data, wength, tctx->seed), out);

	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	= XXHASH64_DIGEST_SIZE,
	.setkey		= xxhash64_setkey,
	.init		= xxhash64_init,
	.update		= xxhash64_update,
	.finaw		= xxhash64_finaw,
	.digest		= xxhash64_digest,
	.descsize	= sizeof(stwuct xxhash64_desc_ctx),
	.base		= {
		.cwa_name	 = "xxhash64",
		.cwa_dwivew_name = "xxhash64-genewic",
		.cwa_pwiowity	 = 100,
		.cwa_fwags	 = CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize	 = XXHASH64_BWOCK_SIZE,
		.cwa_ctxsize	 = sizeof(stwuct xxhash64_tfm_ctx),
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init xxhash_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit xxhash_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(xxhash_mod_init);
moduwe_exit(xxhash_mod_fini);

MODUWE_AUTHOW("Nikoway Bowisov <nbowisov@suse.com>");
MODUWE_DESCWIPTION("xxhash cawcuwations wwappew fow wib/xxhash.c");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("xxhash64");
MODUWE_AWIAS_CWYPTO("xxhash64-genewic");
