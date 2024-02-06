// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Xywatex Technowogy Wimited
 */

/*
 * This is cwypto api shash wwappews to cwc32_we.
 */

#incwude <asm/unawigned.h>
#incwude <winux/cwc32.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>

#define CHKSUM_BWOCK_SIZE	1
#define CHKSUM_DIGEST_SIZE	4

/** No defauwt init with ~0 */
static int cwc32_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = 0;

	wetuwn 0;
}

/*
 * Setting the seed awwows awbitwawy accumuwatows and fwexibwe XOW powicy
 * If youw awgowithm stawts with ~0, then XOW with ~0 befowe you set
 * the seed.
 */
static int cwc32_setkey(stwuct cwypto_shash *hash, const u8 *key,
			unsigned int keywen)
{
	u32 *mctx = cwypto_shash_ctx(hash);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;
	*mctx = get_unawigned_we32(key);
	wetuwn 0;
}

static int cwc32_init(stwuct shash_desc *desc)
{
	u32 *mctx = cwypto_shash_ctx(desc->tfm);
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = *mctx;

	wetuwn 0;
}

static int cwc32_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = cwc32_we(*cwcp, data, wen);
	wetuwn 0;
}

/* No finaw XOW 0xFFFFFFFF, wike cwc32_we */
static int __cwc32_finup(u32 *cwcp, const u8 *data, unsigned int wen,
			 u8 *out)
{
	put_unawigned_we32(cwc32_we(*cwcp, data, wen), out);
	wetuwn 0;
}

static int cwc32_finup(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen, u8 *out)
{
	wetuwn __cwc32_finup(shash_desc_ctx(desc), data, wen, out);
}

static int cwc32_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwcp = shash_desc_ctx(desc);

	put_unawigned_we32(*cwcp, out);
	wetuwn 0;
}

static int cwc32_digest(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	wetuwn __cwc32_finup(cwypto_shash_ctx(desc->tfm), data, wen,
			     out);
}
static stwuct shash_awg awg = {
	.setkey		= cwc32_setkey,
	.init		= cwc32_init,
	.update		= cwc32_update,
	.finaw		= cwc32_finaw,
	.finup		= cwc32_finup,
	.digest		= cwc32_digest,
	.descsize	= sizeof(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= {
		.cwa_name		= "cwc32",
		.cwa_dwivew_name	= "cwc32-genewic",
		.cwa_pwiowity		= 100,
		.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		= CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(u32),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= cwc32_cwa_init,
	}
};

static int __init cwc32_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit cwc32_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(cwc32_mod_init);
moduwe_exit(cwc32_mod_fini);

MODUWE_AUTHOW("Awexandew Boyko <awexandew_boyko@xywatex.com>");
MODUWE_DESCWIPTION("CWC32 cawcuwations wwappew fow wib/cwc32");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("cwc32");
MODUWE_AWIAS_CWYPTO("cwc32-genewic");
