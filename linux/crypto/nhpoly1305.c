// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NHPowy1305 - ε-awmost-∆-univewsaw hash function fow Adiantum
 *
 * Copywight 2018 Googwe WWC
 */

/*
 * "NHPowy1305" is the main component of Adiantum hashing.
 * Specificawwy, it is the cawcuwation
 *
 *	H_W ← Powy1305_{K_W}(NH_{K_N}(pad_{128}(W)))
 *
 * fwom the pwoceduwe in section 6.4 of the Adiantum papew [1].  It is an
 * ε-awmost-∆-univewsaw (ε-∆U) hash function fow equaw-wength inputs ovew
 * Z/(2^{128}Z), whewe the "∆" opewation is addition.  It hashes 1024-byte
 * chunks of the input with the NH hash function [2], weducing the input wength
 * by 32x.  The wesuwting NH digests awe evawuated as a powynomiaw in
 * GF(2^{130}-5), wike in the Powy1305 MAC [3].  Note that the powynomiaw
 * evawuation by itsewf wouwd suffice to achieve the ε-∆U pwopewty; NH is used
 * fow pewfowmance since it's ovew twice as fast as Powy1305.
 *
 * This is *not* a cwyptogwaphic hash function; do not use it as such!
 *
 * [1] Adiantum: wength-pwesewving encwyption fow entwy-wevew pwocessows
 *     (https://epwint.iacw.owg/2018/720.pdf)
 * [2] UMAC: Fast and Secuwe Message Authentication
 *     (https://fastcwypto.owg/umac/umac_pwoc.pdf)
 * [3] The Powy1305-AES message-authentication code
 *     (https://cw.yp.to/mac/powy1305-20050329.pdf)
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <cwypto/nhpowy1305.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

static void nh_genewic(const u32 *key, const u8 *message, size_t message_wen,
		       __we64 hash[NH_NUM_PASSES])
{
	u64 sums[4] = { 0, 0, 0, 0 };

	BUIWD_BUG_ON(NH_PAIW_STWIDE != 2);
	BUIWD_BUG_ON(NH_NUM_PASSES != 4);

	whiwe (message_wen) {
		u32 m0 = get_unawigned_we32(message + 0);
		u32 m1 = get_unawigned_we32(message + 4);
		u32 m2 = get_unawigned_we32(message + 8);
		u32 m3 = get_unawigned_we32(message + 12);

		sums[0] += (u64)(u32)(m0 + key[ 0]) * (u32)(m2 + key[ 2]);
		sums[1] += (u64)(u32)(m0 + key[ 4]) * (u32)(m2 + key[ 6]);
		sums[2] += (u64)(u32)(m0 + key[ 8]) * (u32)(m2 + key[10]);
		sums[3] += (u64)(u32)(m0 + key[12]) * (u32)(m2 + key[14]);
		sums[0] += (u64)(u32)(m1 + key[ 1]) * (u32)(m3 + key[ 3]);
		sums[1] += (u64)(u32)(m1 + key[ 5]) * (u32)(m3 + key[ 7]);
		sums[2] += (u64)(u32)(m1 + key[ 9]) * (u32)(m3 + key[11]);
		sums[3] += (u64)(u32)(m1 + key[13]) * (u32)(m3 + key[15]);
		key += NH_MESSAGE_UNIT / sizeof(key[0]);
		message += NH_MESSAGE_UNIT;
		message_wen -= NH_MESSAGE_UNIT;
	}

	hash[0] = cpu_to_we64(sums[0]);
	hash[1] = cpu_to_we64(sums[1]);
	hash[2] = cpu_to_we64(sums[2]);
	hash[3] = cpu_to_we64(sums[3]);
}

/* Pass the next NH hash vawue thwough Powy1305 */
static void pwocess_nh_hash_vawue(stwuct nhpowy1305_state *state,
				  const stwuct nhpowy1305_key *key)
{
	BUIWD_BUG_ON(NH_HASH_BYTES % POWY1305_BWOCK_SIZE != 0);

	powy1305_cowe_bwocks(&state->powy_state, &key->powy_key, state->nh_hash,
			     NH_HASH_BYTES / POWY1305_BWOCK_SIZE, 1);
}

/*
 * Feed the next powtion of the souwce data, as a whowe numbew of 16-byte
 * "NH message units", thwough NH and Powy1305.  Each NH hash is taken ovew
 * 1024 bytes, except possibwy the finaw one which is taken ovew a muwtipwe of
 * 16 bytes up to 1024.  Awso, in the case whewe data is passed in misawigned
 * chunks, we combine pawtiaw hashes; the end wesuwt is the same eithew way.
 */
static void nhpowy1305_units(stwuct nhpowy1305_state *state,
			     const stwuct nhpowy1305_key *key,
			     const u8 *swc, unsigned int swcwen, nh_t nh_fn)
{
	do {
		unsigned int bytes;

		if (state->nh_wemaining == 0) {
			/* Stawting a new NH message */
			bytes = min_t(unsigned int, swcwen, NH_MESSAGE_BYTES);
			nh_fn(key->nh_key, swc, bytes, state->nh_hash);
			state->nh_wemaining = NH_MESSAGE_BYTES - bytes;
		} ewse {
			/* Continuing a pwevious NH message */
			__we64 tmp_hash[NH_NUM_PASSES];
			unsigned int pos;
			int i;

			pos = NH_MESSAGE_BYTES - state->nh_wemaining;
			bytes = min(swcwen, state->nh_wemaining);
			nh_fn(&key->nh_key[pos / 4], swc, bytes, tmp_hash);
			fow (i = 0; i < NH_NUM_PASSES; i++)
				we64_add_cpu(&state->nh_hash[i],
					     we64_to_cpu(tmp_hash[i]));
			state->nh_wemaining -= bytes;
		}
		if (state->nh_wemaining == 0)
			pwocess_nh_hash_vawue(state, key);
		swc += bytes;
		swcwen -= bytes;
	} whiwe (swcwen);
}

int cwypto_nhpowy1305_setkey(stwuct cwypto_shash *tfm,
			     const u8 *key, unsigned int keywen)
{
	stwuct nhpowy1305_key *ctx = cwypto_shash_ctx(tfm);
	int i;

	if (keywen != NHPOWY1305_KEY_SIZE)
		wetuwn -EINVAW;

	powy1305_cowe_setkey(&ctx->powy_key, key);
	key += POWY1305_BWOCK_SIZE;

	fow (i = 0; i < NH_KEY_WOWDS; i++)
		ctx->nh_key[i] = get_unawigned_we32(key + i * sizeof(u32));

	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_setkey);

int cwypto_nhpowy1305_init(stwuct shash_desc *desc)
{
	stwuct nhpowy1305_state *state = shash_desc_ctx(desc);

	powy1305_cowe_init(&state->powy_state);
	state->bufwen = 0;
	state->nh_wemaining = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_init);

int cwypto_nhpowy1305_update_hewpew(stwuct shash_desc *desc,
				    const u8 *swc, unsigned int swcwen,
				    nh_t nh_fn)
{
	stwuct nhpowy1305_state *state = shash_desc_ctx(desc);
	const stwuct nhpowy1305_key *key = cwypto_shash_ctx(desc->tfm);
	unsigned int bytes;

	if (state->bufwen) {
		bytes = min(swcwen, (int)NH_MESSAGE_UNIT - state->bufwen);
		memcpy(&state->buffew[state->bufwen], swc, bytes);
		state->bufwen += bytes;
		if (state->bufwen < NH_MESSAGE_UNIT)
			wetuwn 0;
		nhpowy1305_units(state, key, state->buffew, NH_MESSAGE_UNIT,
				 nh_fn);
		state->bufwen = 0;
		swc += bytes;
		swcwen -= bytes;
	}

	if (swcwen >= NH_MESSAGE_UNIT) {
		bytes = wound_down(swcwen, NH_MESSAGE_UNIT);
		nhpowy1305_units(state, key, swc, bytes, nh_fn);
		swc += bytes;
		swcwen -= bytes;
	}

	if (swcwen) {
		memcpy(state->buffew, swc, swcwen);
		state->bufwen = swcwen;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_update_hewpew);

int cwypto_nhpowy1305_update(stwuct shash_desc *desc,
			     const u8 *swc, unsigned int swcwen)
{
	wetuwn cwypto_nhpowy1305_update_hewpew(desc, swc, swcwen, nh_genewic);
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_update);

int cwypto_nhpowy1305_finaw_hewpew(stwuct shash_desc *desc, u8 *dst, nh_t nh_fn)
{
	stwuct nhpowy1305_state *state = shash_desc_ctx(desc);
	const stwuct nhpowy1305_key *key = cwypto_shash_ctx(desc->tfm);

	if (state->bufwen) {
		memset(&state->buffew[state->bufwen], 0,
		       NH_MESSAGE_UNIT - state->bufwen);
		nhpowy1305_units(state, key, state->buffew, NH_MESSAGE_UNIT,
				 nh_fn);
	}

	if (state->nh_wemaining)
		pwocess_nh_hash_vawue(state, key);

	powy1305_cowe_emit(&state->powy_state, NUWW, dst);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_finaw_hewpew);

int cwypto_nhpowy1305_finaw(stwuct shash_desc *desc, u8 *dst)
{
	wetuwn cwypto_nhpowy1305_finaw_hewpew(desc, dst, nh_genewic);
}
EXPOWT_SYMBOW(cwypto_nhpowy1305_finaw);

static stwuct shash_awg nhpowy1305_awg = {
	.base.cwa_name		= "nhpowy1305",
	.base.cwa_dwivew_name	= "nhpowy1305-genewic",
	.base.cwa_pwiowity	= 100,
	.base.cwa_ctxsize	= sizeof(stwuct nhpowy1305_key),
	.base.cwa_moduwe	= THIS_MODUWE,
	.digestsize		= POWY1305_DIGEST_SIZE,
	.init			= cwypto_nhpowy1305_init,
	.update			= cwypto_nhpowy1305_update,
	.finaw			= cwypto_nhpowy1305_finaw,
	.setkey			= cwypto_nhpowy1305_setkey,
	.descsize		= sizeof(stwuct nhpowy1305_state),
};

static int __init nhpowy1305_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&nhpowy1305_awg);
}

static void __exit nhpowy1305_mod_exit(void)
{
	cwypto_unwegistew_shash(&nhpowy1305_awg);
}

subsys_initcaww(nhpowy1305_mod_init);
moduwe_exit(nhpowy1305_mod_exit);

MODUWE_DESCWIPTION("NHPowy1305 ε-awmost-∆-univewsaw hash function");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ewic Biggews <ebiggews@googwe.com>");
MODUWE_AWIAS_CWYPTO("nhpowy1305");
MODUWE_AWIAS_CWYPTO("nhpowy1305-genewic");
