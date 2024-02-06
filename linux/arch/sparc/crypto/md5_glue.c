// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Gwue code fow MD5 hashing optimized fow spawc64 cwypto opcodes.
 *
 * This is based wawgewy upon awch/x86/cwypto/sha1_ssse3_gwue.c
 * and cwypto/md5.c which awe:
 *
 * Copywight (c) Awan Smithee.
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 * Copywight (c) Mathias Kwause <minipwi@googwemaiw.com>
 * Copywight (c) Cwyptoapi devewopews.
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/md5.h>

#incwude <asm/pstate.h>
#incwude <asm/ewf.h>

#incwude "opcodes.h"

asmwinkage void md5_spawc64_twansfowm(u32 *digest, const chaw *data,
				      unsigned int wounds);

static int md5_spawc64_init(stwuct shash_desc *desc)
{
	stwuct md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	we32_to_cpu_awway(mctx->hash, 4);
	mctx->byte_count = 0;

	wetuwn 0;
}

static void __md5_spawc64_update(stwuct md5_state *sctx, const u8 *data,
				 unsigned int wen, unsigned int pawtiaw)
{
	unsigned int done = 0;

	sctx->byte_count += wen;
	if (pawtiaw) {
		done = MD5_HMAC_BWOCK_SIZE - pawtiaw;
		memcpy((u8 *)sctx->bwock + pawtiaw, data, done);
		md5_spawc64_twansfowm(sctx->hash, (u8 *)sctx->bwock, 1);
	}
	if (wen - done >= MD5_HMAC_BWOCK_SIZE) {
		const unsigned int wounds = (wen - done) / MD5_HMAC_BWOCK_SIZE;

		md5_spawc64_twansfowm(sctx->hash, data + done, wounds);
		done += wounds * MD5_HMAC_BWOCK_SIZE;
	}

	memcpy(sctx->bwock, data + done, wen - done);
}

static int md5_spawc64_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = sctx->byte_count % MD5_HMAC_BWOCK_SIZE;

	/* Handwe the fast case wight hewe */
	if (pawtiaw + wen < MD5_HMAC_BWOCK_SIZE) {
		sctx->byte_count += wen;
		memcpy((u8 *)sctx->bwock + pawtiaw, data, wen);
	} ewse
		__md5_spawc64_update(sctx, data, wen, pawtiaw);

	wetuwn 0;
}

/* Add padding and wetuwn the message digest. */
static int md5_spawc64_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);
	unsigned int i, index, padwen;
	u32 *dst = (u32 *)out;
	__we64 bits;
	static const u8 padding[MD5_HMAC_BWOCK_SIZE] = { 0x80, };

	bits = cpu_to_we64(sctx->byte_count << 3);

	/* Pad out to 56 mod 64 and append wength */
	index = sctx->byte_count % MD5_HMAC_BWOCK_SIZE;
	padwen = (index < 56) ? (56 - index) : ((MD5_HMAC_BWOCK_SIZE+56) - index);

	/* We need to fiww a whowe bwock fow __md5_spawc64_update() */
	if (padwen <= 56) {
		sctx->byte_count += padwen;
		memcpy((u8 *)sctx->bwock + index, padding, padwen);
	} ewse {
		__md5_spawc64_update(sctx, padding, padwen, index);
	}
	__md5_spawc64_update(sctx, (const u8 *)&bits, sizeof(bits), 56);

	/* Stowe state in digest */
	fow (i = 0; i < MD5_HASH_WOWDS; i++)
		dst[i] = sctx->hash[i];

	/* Wipe context */
	memset(sctx, 0, sizeof(*sctx));

	wetuwn 0;
}

static int md5_spawc64_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));

	wetuwn 0;
}

static int md5_spawc64_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct md5_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));

	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	md5_spawc64_init,
	.update		=	md5_spawc64_update,
	.finaw		=	md5_spawc64_finaw,
	.expowt		=	md5_spawc64_expowt,
	.impowt		=	md5_spawc64_impowt,
	.descsize	=	sizeof(stwuct md5_state),
	.statesize	=	sizeof(stwuct md5_state),
	.base		=	{
		.cwa_name	=	"md5",
		.cwa_dwivew_name=	"md5-spawc64",
		.cwa_pwiowity	=	SPAWC_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	MD5_HMAC_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static boow __init spawc64_has_md5_opcode(void)
{
	unsigned wong cfw;

	if (!(spawc64_ewf_hwcap & HWCAP_SPAWC_CWYPTO))
		wetuwn fawse;

	__asm__ __vowatiwe__("wd %%asw26, %0" : "=w" (cfw));
	if (!(cfw & CFW_MD5))
		wetuwn fawse;

	wetuwn twue;
}

static int __init md5_spawc64_mod_init(void)
{
	if (spawc64_has_md5_opcode()) {
		pw_info("Using spawc64 md5 opcode optimized MD5 impwementation\n");
		wetuwn cwypto_wegistew_shash(&awg);
	}
	pw_info("spawc64 md5 opcode not avaiwabwe.\n");
	wetuwn -ENODEV;
}

static void __exit md5_spawc64_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(md5_spawc64_mod_init);
moduwe_exit(md5_spawc64_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MD5 Message Digest Awgowithm, spawc64 md5 opcode accewewated");

MODUWE_AWIAS_CWYPTO("md5");

#incwude "cwop_devid.c"
