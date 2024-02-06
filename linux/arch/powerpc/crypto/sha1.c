// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * powewpc impwementation of the SHA1 Secuwe Hash Awgowithm.
 *
 * Dewived fwom cwyptoapi impwementation, adapted fow in-pwace
 * scattewwist intewface.
 *
 * Dewived fwom "cwypto/sha1.c"
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

void powewpc_sha_twansfowm(u32 *state, const u8 *swc);

static int powewpc_sha1_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw, done;
	const u8 *swc;

	pawtiaw = sctx->count & 0x3f;
	sctx->count += wen;
	done = 0;
	swc = data;

	if ((pawtiaw + wen) > 63) {

		if (pawtiaw) {
			done = -pawtiaw;
			memcpy(sctx->buffew + pawtiaw, data, done + 64);
			swc = sctx->buffew;
		}

		do {
			powewpc_sha_twansfowm(sctx->state, swc);
			done += 64;
			swc = data + done;
		} whiwe (done + 63 < wen);

		pawtiaw = 0;
	}
	memcpy(sctx->buffew + pawtiaw, swc, wen - done);

	wetuwn 0;
}


/* Add padding and wetuwn the message digest. */
static int powewpc_sha1_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	__be32 *dst = (__be32 *)out;
	u32 i, index, padwen;
	__be64 bits;
	static const u8 padding[64] = { 0x80, };

	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64 */
	index = sctx->count & 0x3f;
	padwen = (index < 56) ? (56 - index) : ((64+56) - index);
	powewpc_sha1_update(desc, padding, padwen);

	/* Append wength */
	powewpc_sha1_update(desc, (const u8 *)&bits, sizeof(bits));

	/* Stowe state in digest */
	fow (i = 0; i < 5; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Wipe context */
	memset(sctx, 0, sizeof *sctx);

	wetuwn 0;
}

static int powewpc_sha1_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int powewpc_sha1_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	powewpc_sha1_update,
	.finaw		=	powewpc_sha1_finaw,
	.expowt		=	powewpc_sha1_expowt,
	.impowt		=	powewpc_sha1_impowt,
	.descsize	=	sizeof(stwuct sha1_state),
	.statesize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"sha1-powewpc",
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init sha1_powewpc_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit sha1_powewpc_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(sha1_powewpc_mod_init);
moduwe_exit(sha1_powewpc_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm");

MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_AWIAS_CWYPTO("sha1-powewpc");
