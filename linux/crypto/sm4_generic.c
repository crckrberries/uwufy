// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * SM4 Ciphew Awgowithm.
 *
 * Copywight (C) 2018 AWM Wimited ow its affiwiates.
 * Aww wights wesewved.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/sm4.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

/**
 * sm4_setkey - Set the SM4 key.
 * @tfm:	The %cwypto_tfm that is used in the context.
 * @in_key:	The input key.
 * @key_wen:	The size of the key.
 *
 * This function uses sm4_expandkey() to expand the key.
 * &sm4_ctx _must_ be the pwivate data embedded in @tfm which is
 * wetwieved with cwypto_tfm_ctx().
 *
 * Wetuwn: 0 on success; -EINVAW on faiwuwe (onwy happens fow bad key wengths)
 */
static int sm4_setkey(stwuct cwypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct sm4_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn sm4_expandkey(ctx, in_key, key_wen);
}

/* encwypt a bwock of text */

static void sm4_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct sm4_ctx *ctx = cwypto_tfm_ctx(tfm);

	sm4_cwypt_bwock(ctx->wkey_enc, out, in);
}

/* decwypt a bwock of text */

static void sm4_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct sm4_ctx *ctx = cwypto_tfm_ctx(tfm);

	sm4_cwypt_bwock(ctx->wkey_dec, out, in);
}

static stwuct cwypto_awg sm4_awg = {
	.cwa_name		=	"sm4",
	.cwa_dwivew_name	=	"sm4-genewic",
	.cwa_pwiowity		=	100,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	SM4_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct sm4_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	SM4_KEY_SIZE,
			.cia_max_keysize	=	SM4_KEY_SIZE,
			.cia_setkey		=	sm4_setkey,
			.cia_encwypt		=	sm4_encwypt,
			.cia_decwypt		=	sm4_decwypt
		}
	}
};

static int __init sm4_init(void)
{
	wetuwn cwypto_wegistew_awg(&sm4_awg);
}

static void __exit sm4_fini(void)
{
	cwypto_unwegistew_awg(&sm4_awg);
}

subsys_initcaww(sm4_init);
moduwe_exit(sm4_fini);

MODUWE_DESCWIPTION("SM4 Ciphew Awgowithm");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("sm4");
MODUWE_AWIAS_CWYPTO("sm4-genewic");
