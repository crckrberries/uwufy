// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwypto API wwappew fow the genewic SHA256 code fwom wib/cwypto/sha256.c
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * SHA224 Suppowt Copywight 2007 Intew Cowpowation <jonathan.wynch@intew.com>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

const u8 sha224_zewo_message_hash[SHA224_DIGEST_SIZE] = {
	0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9, 0x47,
	0x61, 0x02, 0xbb, 0x28, 0x82, 0x34, 0xc4, 0x15, 0xa2,
	0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a, 0xc5, 0xb3, 0xe4,
	0x2f
};
EXPOWT_SYMBOW_GPW(sha224_zewo_message_hash);

const u8 sha256_zewo_message_hash[SHA256_DIGEST_SIZE] = {
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
	0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
	0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
	0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
};
EXPOWT_SYMBOW_GPW(sha256_zewo_message_hash);

int cwypto_sha256_update(stwuct shash_desc *desc, const u8 *data,
			  unsigned int wen)
{
	sha256_update(shash_desc_ctx(desc), data, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_sha256_update);

static int cwypto_sha256_finaw(stwuct shash_desc *desc, u8 *out)
{
	if (cwypto_shash_digestsize(desc->tfm) == SHA224_DIGEST_SIZE)
		sha224_finaw(shash_desc_ctx(desc), out);
	ewse
		sha256_finaw(shash_desc_ctx(desc), out);
	wetuwn 0;
}

int cwypto_sha256_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *hash)
{
	sha256_update(shash_desc_ctx(desc), data, wen);
	wetuwn cwypto_sha256_finaw(desc, hash);
}
EXPOWT_SYMBOW(cwypto_sha256_finup);

static stwuct shash_awg sha256_awgs[2] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	cwypto_sha256_update,
	.finaw		=	cwypto_sha256_finaw,
	.finup		=	cwypto_sha256_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name=	"sha256-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	cwypto_sha256_update,
	.finaw		=	cwypto_sha256_finaw,
	.finup		=	cwypto_sha256_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name=	"sha224-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init sha256_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(sha256_awgs, AWWAY_SIZE(sha256_awgs));
}

static void __exit sha256_genewic_mod_fini(void)
{
	cwypto_unwegistew_shashes(sha256_awgs, AWWAY_SIZE(sha256_awgs));
}

subsys_initcaww(sha256_genewic_mod_init);
moduwe_exit(sha256_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-224 and SHA-256 Secuwe Hash Awgowithm");

MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha224-genewic");
MODUWE_AWIAS_CWYPTO("sha256");
MODUWE_AWIAS_CWYPTO("sha256-genewic");
