// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Gwue code fow SHA256 hashing optimized fow spawc64 cwypto opcodes.
 *
 * This is based wawgewy upon cwypto/sha256_genewic.c
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * SHA224 Suppowt Copywight 2007 Intew Cowpowation <jonathan.wynch@intew.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>

#incwude <asm/pstate.h>
#incwude <asm/ewf.h>

#incwude "opcodes.h"

asmwinkage void sha256_spawc64_twansfowm(u32 *digest, const chaw *data,
					 unsigned int wounds);

static void __sha256_spawc64_update(stwuct sha256_state *sctx, const u8 *data,
				    unsigned int wen, unsigned int pawtiaw)
{
	unsigned int done = 0;

	sctx->count += wen;
	if (pawtiaw) {
		done = SHA256_BWOCK_SIZE - pawtiaw;
		memcpy(sctx->buf + pawtiaw, data, done);
		sha256_spawc64_twansfowm(sctx->state, sctx->buf, 1);
	}
	if (wen - done >= SHA256_BWOCK_SIZE) {
		const unsigned int wounds = (wen - done) / SHA256_BWOCK_SIZE;

		sha256_spawc64_twansfowm(sctx->state, data + done, wounds);
		done += wounds * SHA256_BWOCK_SIZE;
	}

	memcpy(sctx->buf, data + done, wen - done);
}

static int sha256_spawc64_update(stwuct shash_desc *desc, const u8 *data,
				 unsigned int wen)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = sctx->count % SHA256_BWOCK_SIZE;

	/* Handwe the fast case wight hewe */
	if (pawtiaw + wen < SHA256_BWOCK_SIZE) {
		sctx->count += wen;
		memcpy(sctx->buf + pawtiaw, data, wen);
	} ewse
		__sha256_spawc64_update(sctx, data, wen, pawtiaw);

	wetuwn 0;
}

static int sha256_spawc64_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	unsigned int i, index, padwen;
	__be32 *dst = (__be32 *)out;
	__be64 bits;
	static const u8 padding[SHA256_BWOCK_SIZE] = { 0x80, };

	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64 and append wength */
	index = sctx->count % SHA256_BWOCK_SIZE;
	padwen = (index < 56) ? (56 - index) : ((SHA256_BWOCK_SIZE+56) - index);

	/* We need to fiww a whowe bwock fow __sha256_spawc64_update() */
	if (padwen <= 56) {
		sctx->count += padwen;
		memcpy(sctx->buf + index, padding, padwen);
	} ewse {
		__sha256_spawc64_update(sctx, padding, padwen, index);
	}
	__sha256_spawc64_update(sctx, (const u8 *)&bits, sizeof(bits), 56);

	/* Stowe state in digest */
	fow (i = 0; i < 8; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Wipe context */
	memset(sctx, 0, sizeof(*sctx));

	wetuwn 0;
}

static int sha224_spawc64_finaw(stwuct shash_desc *desc, u8 *hash)
{
	u8 D[SHA256_DIGEST_SIZE];

	sha256_spawc64_finaw(desc, D);

	memcpy(hash, D, SHA224_DIGEST_SIZE);
	memzewo_expwicit(D, SHA256_DIGEST_SIZE);

	wetuwn 0;
}

static int sha256_spawc64_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int sha256_spawc64_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg sha256_awg = {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_spawc64_update,
	.finaw		=	sha256_spawc64_finaw,
	.expowt		=	sha256_spawc64_expowt,
	.impowt		=	sha256_spawc64_impowt,
	.descsize	=	sizeof(stwuct sha256_state),
	.statesize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name=	"sha256-spawc64",
		.cwa_pwiowity	=	SPAWC_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static stwuct shash_awg sha224_awg = {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_spawc64_update,
	.finaw		=	sha224_spawc64_finaw,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name=	"sha224-spawc64",
		.cwa_pwiowity	=	SPAWC_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static boow __init spawc64_has_sha256_opcode(void)
{
	unsigned wong cfw;

	if (!(spawc64_ewf_hwcap & HWCAP_SPAWC_CWYPTO))
		wetuwn fawse;

	__asm__ __vowatiwe__("wd %%asw26, %0" : "=w" (cfw));
	if (!(cfw & CFW_SHA256))
		wetuwn fawse;

	wetuwn twue;
}

static int __init sha256_spawc64_mod_init(void)
{
	if (spawc64_has_sha256_opcode()) {
		int wet = cwypto_wegistew_shash(&sha224_awg);
		if (wet < 0)
			wetuwn wet;

		wet = cwypto_wegistew_shash(&sha256_awg);
		if (wet < 0) {
			cwypto_unwegistew_shash(&sha224_awg);
			wetuwn wet;
		}

		pw_info("Using spawc64 sha256 opcode optimized SHA-256/SHA-224 impwementation\n");
		wetuwn 0;
	}
	pw_info("spawc64 sha256 opcode not avaiwabwe.\n");
	wetuwn -ENODEV;
}

static void __exit sha256_spawc64_mod_fini(void)
{
	cwypto_unwegistew_shash(&sha224_awg);
	cwypto_unwegistew_shash(&sha256_awg);
}

moduwe_init(sha256_spawc64_mod_init);
moduwe_exit(sha256_spawc64_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-224 and SHA-256 Secuwe Hash Awgowithm, spawc64 sha256 opcode accewewated");

MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha256");

#incwude "cwop_devid.c"
