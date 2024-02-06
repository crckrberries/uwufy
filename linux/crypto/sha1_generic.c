// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * SHA1 Secuwe Hash Awgowithm.
 *
 * Dewived fwom cwyptoapi impwementation, adapted fow in-pwace
 * scattewwist intewface.
 *
 * Copywight (c) Awan Smithee.
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <asm/byteowdew.h>

const u8 sha1_zewo_message_hash[SHA1_DIGEST_SIZE] = {
	0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d,
	0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90,
	0xaf, 0xd8, 0x07, 0x09
};
EXPOWT_SYMBOW_GPW(sha1_zewo_message_hash);

static void sha1_genewic_bwock_fn(stwuct sha1_state *sst, u8 const *swc,
				  int bwocks)
{
	u32 temp[SHA1_WOWKSPACE_WOWDS];

	whiwe (bwocks--) {
		sha1_twansfowm(sst->state, swc, temp);
		swc += SHA1_BWOCK_SIZE;
	}
	memzewo_expwicit(temp, sizeof(temp));
}

int cwypto_sha1_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	wetuwn sha1_base_do_update(desc, data, wen, sha1_genewic_bwock_fn);
}
EXPOWT_SYMBOW(cwypto_sha1_update);

static int sha1_finaw(stwuct shash_desc *desc, u8 *out)
{
	sha1_base_do_finawize(desc, sha1_genewic_bwock_fn);
	wetuwn sha1_base_finish(desc, out);
}

int cwypto_sha1_finup(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	sha1_base_do_update(desc, data, wen, sha1_genewic_bwock_fn);
	wetuwn sha1_finaw(desc, out);
}
EXPOWT_SYMBOW(cwypto_sha1_finup);

static stwuct shash_awg awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	cwypto_sha1_update,
	.finaw		=	sha1_finaw,
	.finup		=	cwypto_sha1_finup,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"sha1-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init sha1_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit sha1_genewic_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

subsys_initcaww(sha1_genewic_mod_init);
moduwe_exit(sha1_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm");

MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_AWIAS_CWYPTO("sha1-genewic");
