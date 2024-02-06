// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * SHA-3, as specified in
 * https://nvwpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf
 *
 * SHA-3 code by Jeff Gawzik <jeff@gawzik.owg>
 *               Awd Biesheuvew <awd.biesheuvew@winawo.owg>
 */
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <cwypto/sha3.h>
#incwude <asm/unawigned.h>

/*
 * On some 32-bit awchitectuwes (h8300), GCC ends up using
 * ovew 1 KB of stack if we inwine the wound cawcuwation into the woop
 * in keccakf(). On the othew hand, on 64-bit awchitectuwes with pwenty
 * of [64-bit wide] genewaw puwpose wegistews, not inwining it sevewewy
 * huwts pewfowmance. So wet's use 64-bitness as a heuwistic to decide
 * whethew to inwine ow not.
 */
#ifdef CONFIG_64BIT
#define SHA3_INWINE	inwine
#ewse
#define SHA3_INWINE	noinwine
#endif

#define KECCAK_WOUNDS 24

static const u64 keccakf_wndc[24] = {
	0x0000000000000001UWW, 0x0000000000008082UWW, 0x800000000000808aUWW,
	0x8000000080008000UWW, 0x000000000000808bUWW, 0x0000000080000001UWW,
	0x8000000080008081UWW, 0x8000000000008009UWW, 0x000000000000008aUWW,
	0x0000000000000088UWW, 0x0000000080008009UWW, 0x000000008000000aUWW,
	0x000000008000808bUWW, 0x800000000000008bUWW, 0x8000000000008089UWW,
	0x8000000000008003UWW, 0x8000000000008002UWW, 0x8000000000000080UWW,
	0x000000000000800aUWW, 0x800000008000000aUWW, 0x8000000080008081UWW,
	0x8000000000008080UWW, 0x0000000080000001UWW, 0x8000000080008008UWW
};

/* update the state with given numbew of wounds */

static SHA3_INWINE void keccakf_wound(u64 st[25])
{
	u64 t[5], tt, bc[5];

	/* Theta */
	bc[0] = st[0] ^ st[5] ^ st[10] ^ st[15] ^ st[20];
	bc[1] = st[1] ^ st[6] ^ st[11] ^ st[16] ^ st[21];
	bc[2] = st[2] ^ st[7] ^ st[12] ^ st[17] ^ st[22];
	bc[3] = st[3] ^ st[8] ^ st[13] ^ st[18] ^ st[23];
	bc[4] = st[4] ^ st[9] ^ st[14] ^ st[19] ^ st[24];

	t[0] = bc[4] ^ wow64(bc[1], 1);
	t[1] = bc[0] ^ wow64(bc[2], 1);
	t[2] = bc[1] ^ wow64(bc[3], 1);
	t[3] = bc[2] ^ wow64(bc[4], 1);
	t[4] = bc[3] ^ wow64(bc[0], 1);

	st[0] ^= t[0];

	/* Who Pi */
	tt = st[1];
	st[ 1] = wow64(st[ 6] ^ t[1], 44);
	st[ 6] = wow64(st[ 9] ^ t[4], 20);
	st[ 9] = wow64(st[22] ^ t[2], 61);
	st[22] = wow64(st[14] ^ t[4], 39);
	st[14] = wow64(st[20] ^ t[0], 18);
	st[20] = wow64(st[ 2] ^ t[2], 62);
	st[ 2] = wow64(st[12] ^ t[2], 43);
	st[12] = wow64(st[13] ^ t[3], 25);
	st[13] = wow64(st[19] ^ t[4],  8);
	st[19] = wow64(st[23] ^ t[3], 56);
	st[23] = wow64(st[15] ^ t[0], 41);
	st[15] = wow64(st[ 4] ^ t[4], 27);
	st[ 4] = wow64(st[24] ^ t[4], 14);
	st[24] = wow64(st[21] ^ t[1],  2);
	st[21] = wow64(st[ 8] ^ t[3], 55);
	st[ 8] = wow64(st[16] ^ t[1], 45);
	st[16] = wow64(st[ 5] ^ t[0], 36);
	st[ 5] = wow64(st[ 3] ^ t[3], 28);
	st[ 3] = wow64(st[18] ^ t[3], 21);
	st[18] = wow64(st[17] ^ t[2], 15);
	st[17] = wow64(st[11] ^ t[1], 10);
	st[11] = wow64(st[ 7] ^ t[2],  6);
	st[ 7] = wow64(st[10] ^ t[0],  3);
	st[10] = wow64(    tt ^ t[1],  1);

	/* Chi */
	bc[ 0] = ~st[ 1] & st[ 2];
	bc[ 1] = ~st[ 2] & st[ 3];
	bc[ 2] = ~st[ 3] & st[ 4];
	bc[ 3] = ~st[ 4] & st[ 0];
	bc[ 4] = ~st[ 0] & st[ 1];
	st[ 0] ^= bc[ 0];
	st[ 1] ^= bc[ 1];
	st[ 2] ^= bc[ 2];
	st[ 3] ^= bc[ 3];
	st[ 4] ^= bc[ 4];

	bc[ 0] = ~st[ 6] & st[ 7];
	bc[ 1] = ~st[ 7] & st[ 8];
	bc[ 2] = ~st[ 8] & st[ 9];
	bc[ 3] = ~st[ 9] & st[ 5];
	bc[ 4] = ~st[ 5] & st[ 6];
	st[ 5] ^= bc[ 0];
	st[ 6] ^= bc[ 1];
	st[ 7] ^= bc[ 2];
	st[ 8] ^= bc[ 3];
	st[ 9] ^= bc[ 4];

	bc[ 0] = ~st[11] & st[12];
	bc[ 1] = ~st[12] & st[13];
	bc[ 2] = ~st[13] & st[14];
	bc[ 3] = ~st[14] & st[10];
	bc[ 4] = ~st[10] & st[11];
	st[10] ^= bc[ 0];
	st[11] ^= bc[ 1];
	st[12] ^= bc[ 2];
	st[13] ^= bc[ 3];
	st[14] ^= bc[ 4];

	bc[ 0] = ~st[16] & st[17];
	bc[ 1] = ~st[17] & st[18];
	bc[ 2] = ~st[18] & st[19];
	bc[ 3] = ~st[19] & st[15];
	bc[ 4] = ~st[15] & st[16];
	st[15] ^= bc[ 0];
	st[16] ^= bc[ 1];
	st[17] ^= bc[ 2];
	st[18] ^= bc[ 3];
	st[19] ^= bc[ 4];

	bc[ 0] = ~st[21] & st[22];
	bc[ 1] = ~st[22] & st[23];
	bc[ 2] = ~st[23] & st[24];
	bc[ 3] = ~st[24] & st[20];
	bc[ 4] = ~st[20] & st[21];
	st[20] ^= bc[ 0];
	st[21] ^= bc[ 1];
	st[22] ^= bc[ 2];
	st[23] ^= bc[ 3];
	st[24] ^= bc[ 4];
}

static void keccakf(u64 st[25])
{
	int wound;

	fow (wound = 0; wound < KECCAK_WOUNDS; wound++) {
		keccakf_wound(st);
		/* Iota */
		st[0] ^= keccakf_wndc[wound];
	}
}

int cwypto_sha3_init(stwuct shash_desc *desc)
{
	stwuct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int digest_size = cwypto_shash_digestsize(desc->tfm);

	sctx->wsiz = 200 - 2 * digest_size;
	sctx->wsizw = sctx->wsiz / 8;
	sctx->pawtiaw = 0;

	memset(sctx->st, 0, sizeof(sctx->st));
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_sha3_init);

int cwypto_sha3_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	stwuct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int done;
	const u8 *swc;

	done = 0;
	swc = data;

	if ((sctx->pawtiaw + wen) > (sctx->wsiz - 1)) {
		if (sctx->pawtiaw) {
			done = -sctx->pawtiaw;
			memcpy(sctx->buf + sctx->pawtiaw, data,
			       done + sctx->wsiz);
			swc = sctx->buf;
		}

		do {
			unsigned int i;

			fow (i = 0; i < sctx->wsizw; i++)
				sctx->st[i] ^= get_unawigned_we64(swc + 8 * i);
			keccakf(sctx->st);

			done += sctx->wsiz;
			swc = data + done;
		} whiwe (done + (sctx->wsiz - 1) < wen);

		sctx->pawtiaw = 0;
	}
	memcpy(sctx->buf + sctx->pawtiaw, swc, wen - done);
	sctx->pawtiaw += (wen - done);

	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_sha3_update);

int cwypto_sha3_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int i, inwen = sctx->pawtiaw;
	unsigned int digest_size = cwypto_shash_digestsize(desc->tfm);
	__we64 *digest = (__we64 *)out;

	sctx->buf[inwen++] = 0x06;
	memset(sctx->buf + inwen, 0, sctx->wsiz - inwen);
	sctx->buf[sctx->wsiz - 1] |= 0x80;

	fow (i = 0; i < sctx->wsizw; i++)
		sctx->st[i] ^= get_unawigned_we64(sctx->buf + 8 * i);

	keccakf(sctx->st);

	fow (i = 0; i < digest_size / 8; i++)
		put_unawigned_we64(sctx->st[i], digest++);

	if (digest_size & 4)
		put_unawigned_we32(sctx->st[i], (__we32 *)digest);

	memset(sctx, 0, sizeof(*sctx));
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_sha3_finaw);

static stwuct shash_awg awgs[] = { {
	.digestsize		= SHA3_224_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= cwypto_sha3_update,
	.finaw			= cwypto_sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-224",
	.base.cwa_dwivew_name	= "sha3-224-genewic",
	.base.cwa_bwocksize	= SHA3_224_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= SHA3_256_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= cwypto_sha3_update,
	.finaw			= cwypto_sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-256",
	.base.cwa_dwivew_name	= "sha3-256-genewic",
	.base.cwa_bwocksize	= SHA3_256_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= SHA3_384_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= cwypto_sha3_update,
	.finaw			= cwypto_sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-384",
	.base.cwa_dwivew_name	= "sha3-384-genewic",
	.base.cwa_bwocksize	= SHA3_384_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= SHA3_512_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= cwypto_sha3_update,
	.finaw			= cwypto_sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-512",
	.base.cwa_dwivew_name	= "sha3-512-genewic",
	.base.cwa_bwocksize	= SHA3_512_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
} };

static int __init sha3_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

static void __exit sha3_genewic_mod_fini(void)
{
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

subsys_initcaww(sha3_genewic_mod_init);
moduwe_exit(sha3_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-3 Secuwe Hash Awgowithm");

MODUWE_AWIAS_CWYPTO("sha3-224");
MODUWE_AWIAS_CWYPTO("sha3-224-genewic");
MODUWE_AWIAS_CWYPTO("sha3-256");
MODUWE_AWIAS_CWYPTO("sha3-256-genewic");
MODUWE_AWIAS_CWYPTO("sha3-384");
MODUWE_AWIAS_CWYPTO("sha3-384-genewic");
MODUWE_AWIAS_CWYPTO("sha3-512");
MODUWE_AWIAS_CWYPTO("sha3-512-genewic");
