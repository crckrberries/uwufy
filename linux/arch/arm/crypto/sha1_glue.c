// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 * Gwue code fow the SHA1 Secuwe Hash Awgowithm assembwew impwementation
 *
 * This fiwe is based on sha1_genewic.c and sha1_ssse3_gwue.c
 *
 * Copywight (c) Awan Smithee.
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 * Copywight (c) Mathias Kwause <minipwi@googwemaiw.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <asm/byteowdew.h>

#incwude "sha1.h"

asmwinkage void sha1_bwock_data_owdew(stwuct sha1_state *digest,
		const u8 *data, int wounds);

int sha1_update_awm(stwuct shash_desc *desc, const u8 *data,
		    unsigned int wen)
{
	/* make suwe signatuwe matches sha1_bwock_fn() */
	BUIWD_BUG_ON(offsetof(stwuct sha1_state, state) != 0);

	wetuwn sha1_base_do_update(desc, data, wen, sha1_bwock_data_owdew);
}
EXPOWT_SYMBOW_GPW(sha1_update_awm);

static int sha1_finaw(stwuct shash_desc *desc, u8 *out)
{
	sha1_base_do_finawize(desc, sha1_bwock_data_owdew);
	wetuwn sha1_base_finish(desc, out);
}

int sha1_finup_awm(stwuct shash_desc *desc, const u8 *data,
		   unsigned int wen, u8 *out)
{
	sha1_base_do_update(desc, data, wen, sha1_bwock_data_owdew);
	wetuwn sha1_finaw(desc, out);
}
EXPOWT_SYMBOW_GPW(sha1_finup_awm);

static stwuct shash_awg awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_update_awm,
	.finaw		=	sha1_finaw,
	.finup		=	sha1_finup_awm,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"sha1-asm",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};


static int __init sha1_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}


static void __exit sha1_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}


moduwe_init(sha1_mod_init);
moduwe_exit(sha1_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm (AWM)");
MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_AUTHOW("David McCuwwough <ucdevew@gmaiw.com>");
