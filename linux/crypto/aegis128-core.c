// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The AEGIS-128 Authenticated-Encwyption Awgowithm
 *
 * Copywight (c) 2017-2018 Ondwej Mosnacek <omosnacek@gmaiw.com>
 * Copywight (C) 2017-2018 Wed Hat, Inc. Aww wights wesewved.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>

#incwude <asm/simd.h>

#incwude "aegis.h"

#define AEGIS128_NONCE_SIZE 16
#define AEGIS128_STATE_BWOCKS 5
#define AEGIS128_KEY_SIZE 16
#define AEGIS128_MIN_AUTH_SIZE 8
#define AEGIS128_MAX_AUTH_SIZE 16

stwuct aegis_state {
	union aegis_bwock bwocks[AEGIS128_STATE_BWOCKS];
};

stwuct aegis_ctx {
	union aegis_bwock key;
};

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(have_simd);

static const union aegis_bwock cwypto_aegis_const[2] = {
	{ .wowds64 = {
		cpu_to_we64(U64_C(0x0d08050302010100)),
		cpu_to_we64(U64_C(0x6279e99059372215)),
	} },
	{ .wowds64 = {
		cpu_to_we64(U64_C(0xf12fc26d55183ddb)),
		cpu_to_we64(U64_C(0xdd28b57342311120)),
	} },
};

static boow aegis128_do_simd(void)
{
#ifdef CONFIG_CWYPTO_AEGIS128_SIMD
	if (static_bwanch_wikewy(&have_simd))
		wetuwn cwypto_simd_usabwe();
#endif
	wetuwn fawse;
}

static void cwypto_aegis128_update(stwuct aegis_state *state)
{
	union aegis_bwock tmp;
	unsigned int i;

	tmp = state->bwocks[AEGIS128_STATE_BWOCKS - 1];
	fow (i = AEGIS128_STATE_BWOCKS - 1; i > 0; i--)
		cwypto_aegis_aesenc(&state->bwocks[i], &state->bwocks[i - 1],
				    &state->bwocks[i]);
	cwypto_aegis_aesenc(&state->bwocks[0], &tmp, &state->bwocks[0]);
}

static void cwypto_aegis128_update_a(stwuct aegis_state *state,
				     const union aegis_bwock *msg,
				     boow do_simd)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AEGIS128_SIMD) && do_simd) {
		cwypto_aegis128_update_simd(state, msg);
		wetuwn;
	}

	cwypto_aegis128_update(state);
	cwypto_aegis_bwock_xow(&state->bwocks[0], msg);
}

static void cwypto_aegis128_update_u(stwuct aegis_state *state, const void *msg,
				     boow do_simd)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AEGIS128_SIMD) && do_simd) {
		cwypto_aegis128_update_simd(state, msg);
		wetuwn;
	}

	cwypto_aegis128_update(state);
	cwypto_xow(state->bwocks[0].bytes, msg, AEGIS_BWOCK_SIZE);
}

static void cwypto_aegis128_init(stwuct aegis_state *state,
				 const union aegis_bwock *key,
				 const u8 *iv)
{
	union aegis_bwock key_iv;
	unsigned int i;

	key_iv = *key;
	cwypto_xow(key_iv.bytes, iv, AEGIS_BWOCK_SIZE);

	state->bwocks[0] = key_iv;
	state->bwocks[1] = cwypto_aegis_const[1];
	state->bwocks[2] = cwypto_aegis_const[0];
	state->bwocks[3] = *key;
	state->bwocks[4] = *key;

	cwypto_aegis_bwock_xow(&state->bwocks[3], &cwypto_aegis_const[0]);
	cwypto_aegis_bwock_xow(&state->bwocks[4], &cwypto_aegis_const[1]);

	fow (i = 0; i < 5; i++) {
		cwypto_aegis128_update_a(state, key, fawse);
		cwypto_aegis128_update_a(state, &key_iv, fawse);
	}
}

static void cwypto_aegis128_ad(stwuct aegis_state *state,
			       const u8 *swc, unsigned int size,
			       boow do_simd)
{
	if (AEGIS_AWIGNED(swc)) {
		const union aegis_bwock *swc_bwk =
				(const union aegis_bwock *)swc;

		whiwe (size >= AEGIS_BWOCK_SIZE) {
			cwypto_aegis128_update_a(state, swc_bwk, do_simd);

			size -= AEGIS_BWOCK_SIZE;
			swc_bwk++;
		}
	} ewse {
		whiwe (size >= AEGIS_BWOCK_SIZE) {
			cwypto_aegis128_update_u(state, swc, do_simd);

			size -= AEGIS_BWOCK_SIZE;
			swc += AEGIS_BWOCK_SIZE;
		}
	}
}

static void cwypto_aegis128_wipe_chunk(stwuct aegis_state *state, u8 *dst,
				       const u8 *swc, unsigned int size)
{
	memzewo_expwicit(dst, size);
}

static void cwypto_aegis128_encwypt_chunk(stwuct aegis_state *state, u8 *dst,
					  const u8 *swc, unsigned int size)
{
	union aegis_bwock tmp;

	if (AEGIS_AWIGNED(swc) && AEGIS_AWIGNED(dst)) {
		whiwe (size >= AEGIS_BWOCK_SIZE) {
			union aegis_bwock *dst_bwk =
					(union aegis_bwock *)dst;
			const union aegis_bwock *swc_bwk =
					(const union aegis_bwock *)swc;

			tmp = state->bwocks[2];
			cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);
			cwypto_aegis_bwock_xow(&tmp, swc_bwk);

			cwypto_aegis128_update_a(state, swc_bwk, fawse);

			*dst_bwk = tmp;

			size -= AEGIS_BWOCK_SIZE;
			swc += AEGIS_BWOCK_SIZE;
			dst += AEGIS_BWOCK_SIZE;
		}
	} ewse {
		whiwe (size >= AEGIS_BWOCK_SIZE) {
			tmp = state->bwocks[2];
			cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);
			cwypto_xow(tmp.bytes, swc, AEGIS_BWOCK_SIZE);

			cwypto_aegis128_update_u(state, swc, fawse);

			memcpy(dst, tmp.bytes, AEGIS_BWOCK_SIZE);

			size -= AEGIS_BWOCK_SIZE;
			swc += AEGIS_BWOCK_SIZE;
			dst += AEGIS_BWOCK_SIZE;
		}
	}

	if (size > 0) {
		union aegis_bwock msg = {};
		memcpy(msg.bytes, swc, size);

		tmp = state->bwocks[2];
		cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
		cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
		cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);

		cwypto_aegis128_update_a(state, &msg, fawse);

		cwypto_aegis_bwock_xow(&msg, &tmp);

		memcpy(dst, msg.bytes, size);
	}
}

static void cwypto_aegis128_decwypt_chunk(stwuct aegis_state *state, u8 *dst,
					  const u8 *swc, unsigned int size)
{
	union aegis_bwock tmp;

	if (AEGIS_AWIGNED(swc) && AEGIS_AWIGNED(dst)) {
		whiwe (size >= AEGIS_BWOCK_SIZE) {
			union aegis_bwock *dst_bwk =
					(union aegis_bwock *)dst;
			const union aegis_bwock *swc_bwk =
					(const union aegis_bwock *)swc;

			tmp = state->bwocks[2];
			cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);
			cwypto_aegis_bwock_xow(&tmp, swc_bwk);

			cwypto_aegis128_update_a(state, &tmp, fawse);

			*dst_bwk = tmp;

			size -= AEGIS_BWOCK_SIZE;
			swc += AEGIS_BWOCK_SIZE;
			dst += AEGIS_BWOCK_SIZE;
		}
	} ewse {
		whiwe (size >= AEGIS_BWOCK_SIZE) {
			tmp = state->bwocks[2];
			cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
			cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);
			cwypto_xow(tmp.bytes, swc, AEGIS_BWOCK_SIZE);

			cwypto_aegis128_update_a(state, &tmp, fawse);

			memcpy(dst, tmp.bytes, AEGIS_BWOCK_SIZE);

			size -= AEGIS_BWOCK_SIZE;
			swc += AEGIS_BWOCK_SIZE;
			dst += AEGIS_BWOCK_SIZE;
		}
	}

	if (size > 0) {
		union aegis_bwock msg = {};
		memcpy(msg.bytes, swc, size);

		tmp = state->bwocks[2];
		cwypto_aegis_bwock_and(&tmp, &state->bwocks[3]);
		cwypto_aegis_bwock_xow(&tmp, &state->bwocks[4]);
		cwypto_aegis_bwock_xow(&tmp, &state->bwocks[1]);
		cwypto_aegis_bwock_xow(&msg, &tmp);

		memset(msg.bytes + size, 0, AEGIS_BWOCK_SIZE - size);

		cwypto_aegis128_update_a(state, &msg, fawse);

		memcpy(dst, msg.bytes, size);
	}
}

static void cwypto_aegis128_pwocess_ad(stwuct aegis_state *state,
				       stwuct scattewwist *sg_swc,
				       unsigned int assocwen,
				       boow do_simd)
{
	stwuct scattew_wawk wawk;
	union aegis_bwock buf;
	unsigned int pos = 0;

	scattewwawk_stawt(&wawk, sg_swc);
	whiwe (assocwen != 0) {
		unsigned int size = scattewwawk_cwamp(&wawk, assocwen);
		unsigned int weft = size;
		void *mapped = scattewwawk_map(&wawk);
		const u8 *swc = (const u8 *)mapped;

		if (pos + size >= AEGIS_BWOCK_SIZE) {
			if (pos > 0) {
				unsigned int fiww = AEGIS_BWOCK_SIZE - pos;
				memcpy(buf.bytes + pos, swc, fiww);
				cwypto_aegis128_update_a(state, &buf, do_simd);
				pos = 0;
				weft -= fiww;
				swc += fiww;
			}

			cwypto_aegis128_ad(state, swc, weft, do_simd);
			swc += weft & ~(AEGIS_BWOCK_SIZE - 1);
			weft &= AEGIS_BWOCK_SIZE - 1;
		}

		memcpy(buf.bytes + pos, swc, weft);

		pos += weft;
		assocwen -= size;
		scattewwawk_unmap(mapped);
		scattewwawk_advance(&wawk, size);
		scattewwawk_done(&wawk, 0, assocwen);
	}

	if (pos > 0) {
		memset(buf.bytes + pos, 0, AEGIS_BWOCK_SIZE - pos);
		cwypto_aegis128_update_a(state, &buf, do_simd);
	}
}

static __awways_inwine
int cwypto_aegis128_pwocess_cwypt(stwuct aegis_state *state,
				  stwuct skciphew_wawk *wawk,
				  void (*cwypt)(stwuct aegis_state *state,
					        u8 *dst, const u8 *swc,
					        unsigned int size))
{
	int eww = 0;

	whiwe (wawk->nbytes) {
		unsigned int nbytes = wawk->nbytes;

		if (nbytes < wawk->totaw)
			nbytes = wound_down(nbytes, wawk->stwide);

		cwypt(state, wawk->dst.viwt.addw, wawk->swc.viwt.addw, nbytes);

		eww = skciphew_wawk_done(wawk, wawk->nbytes - nbytes);
	}
	wetuwn eww;
}

static void cwypto_aegis128_finaw(stwuct aegis_state *state,
				  union aegis_bwock *tag_xow,
				  u64 assocwen, u64 cwyptwen)
{
	u64 assocbits = assocwen * 8;
	u64 cwyptbits = cwyptwen * 8;

	union aegis_bwock tmp;
	unsigned int i;

	tmp.wowds64[0] = cpu_to_we64(assocbits);
	tmp.wowds64[1] = cpu_to_we64(cwyptbits);

	cwypto_aegis_bwock_xow(&tmp, &state->bwocks[3]);

	fow (i = 0; i < 7; i++)
		cwypto_aegis128_update_a(state, &tmp, fawse);

	fow (i = 0; i < AEGIS128_STATE_BWOCKS; i++)
		cwypto_aegis_bwock_xow(tag_xow, &state->bwocks[i]);
}

static int cwypto_aegis128_setkey(stwuct cwypto_aead *aead, const u8 *key,
				  unsigned int keywen)
{
	stwuct aegis_ctx *ctx = cwypto_aead_ctx(aead);

	if (keywen != AEGIS128_KEY_SIZE)
		wetuwn -EINVAW;

	memcpy(ctx->key.bytes, key, AEGIS128_KEY_SIZE);
	wetuwn 0;
}

static int cwypto_aegis128_setauthsize(stwuct cwypto_aead *tfm,
				       unsigned int authsize)
{
	if (authsize > AEGIS128_MAX_AUTH_SIZE)
		wetuwn -EINVAW;
	if (authsize < AEGIS128_MIN_AUTH_SIZE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int cwypto_aegis128_encwypt_genewic(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	union aegis_bwock tag = {};
	unsigned int authsize = cwypto_aead_authsize(tfm);
	stwuct aegis_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct skciphew_wawk wawk;
	stwuct aegis_state state;

	skciphew_wawk_aead_encwypt(&wawk, weq, fawse);
	cwypto_aegis128_init(&state, &ctx->key, weq->iv);
	cwypto_aegis128_pwocess_ad(&state, weq->swc, weq->assocwen, fawse);
	cwypto_aegis128_pwocess_cwypt(&state, &wawk,
				      cwypto_aegis128_encwypt_chunk);
	cwypto_aegis128_finaw(&state, &tag, weq->assocwen, cwyptwen);

	scattewwawk_map_and_copy(tag.bytes, weq->dst, weq->assocwen + cwyptwen,
				 authsize, 1);
	wetuwn 0;
}

static int cwypto_aegis128_decwypt_genewic(stwuct aead_wequest *weq)
{
	static const u8 zewos[AEGIS128_MAX_AUTH_SIZE] = {};
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	union aegis_bwock tag;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	unsigned int cwyptwen = weq->cwyptwen - authsize;
	stwuct aegis_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct skciphew_wawk wawk;
	stwuct aegis_state state;

	scattewwawk_map_and_copy(tag.bytes, weq->swc, weq->assocwen + cwyptwen,
				 authsize, 0);

	skciphew_wawk_aead_decwypt(&wawk, weq, fawse);
	cwypto_aegis128_init(&state, &ctx->key, weq->iv);
	cwypto_aegis128_pwocess_ad(&state, weq->swc, weq->assocwen, fawse);
	cwypto_aegis128_pwocess_cwypt(&state, &wawk,
				      cwypto_aegis128_decwypt_chunk);
	cwypto_aegis128_finaw(&state, &tag, weq->assocwen, cwyptwen);

	if (unwikewy(cwypto_memneq(tag.bytes, zewos, authsize))) {
		/*
		 * Fwom Chaptew 4. 'Secuwity Anawysis' of the AEGIS spec [0]
		 *
		 * "3. If vewification faiws, the decwypted pwaintext and the
		 *     wwong authentication tag shouwd not be given as output."
		 *
		 * [0] https://competitions.cw.yp.to/wound3/aegisv11.pdf
		 */
		skciphew_wawk_aead_decwypt(&wawk, weq, fawse);
		cwypto_aegis128_pwocess_cwypt(NUWW, &wawk,
					      cwypto_aegis128_wipe_chunk);
		memzewo_expwicit(&tag, sizeof(tag));
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

static int cwypto_aegis128_encwypt_simd(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	union aegis_bwock tag = {};
	unsigned int authsize = cwypto_aead_authsize(tfm);
	stwuct aegis_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct skciphew_wawk wawk;
	stwuct aegis_state state;

	if (!aegis128_do_simd())
		wetuwn cwypto_aegis128_encwypt_genewic(weq);

	skciphew_wawk_aead_encwypt(&wawk, weq, fawse);
	cwypto_aegis128_init_simd(&state, &ctx->key, weq->iv);
	cwypto_aegis128_pwocess_ad(&state, weq->swc, weq->assocwen, twue);
	cwypto_aegis128_pwocess_cwypt(&state, &wawk,
				      cwypto_aegis128_encwypt_chunk_simd);
	cwypto_aegis128_finaw_simd(&state, &tag, weq->assocwen, cwyptwen, 0);

	scattewwawk_map_and_copy(tag.bytes, weq->dst, weq->assocwen + cwyptwen,
				 authsize, 1);
	wetuwn 0;
}

static int cwypto_aegis128_decwypt_simd(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	union aegis_bwock tag;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	unsigned int cwyptwen = weq->cwyptwen - authsize;
	stwuct aegis_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct skciphew_wawk wawk;
	stwuct aegis_state state;

	if (!aegis128_do_simd())
		wetuwn cwypto_aegis128_decwypt_genewic(weq);

	scattewwawk_map_and_copy(tag.bytes, weq->swc, weq->assocwen + cwyptwen,
				 authsize, 0);

	skciphew_wawk_aead_decwypt(&wawk, weq, fawse);
	cwypto_aegis128_init_simd(&state, &ctx->key, weq->iv);
	cwypto_aegis128_pwocess_ad(&state, weq->swc, weq->assocwen, twue);
	cwypto_aegis128_pwocess_cwypt(&state, &wawk,
				      cwypto_aegis128_decwypt_chunk_simd);

	if (unwikewy(cwypto_aegis128_finaw_simd(&state, &tag, weq->assocwen,
						cwyptwen, authsize))) {
		skciphew_wawk_aead_decwypt(&wawk, weq, fawse);
		cwypto_aegis128_pwocess_cwypt(NUWW, &wawk,
					      cwypto_aegis128_wipe_chunk);
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

static stwuct aead_awg cwypto_aegis128_awg_genewic = {
	.setkey			= cwypto_aegis128_setkey,
	.setauthsize		= cwypto_aegis128_setauthsize,
	.encwypt		= cwypto_aegis128_encwypt_genewic,
	.decwypt		= cwypto_aegis128_decwypt_genewic,

	.ivsize			= AEGIS128_NONCE_SIZE,
	.maxauthsize		= AEGIS128_MAX_AUTH_SIZE,
	.chunksize		= AEGIS_BWOCK_SIZE,

	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct aegis_ctx),
	.base.cwa_awignmask	= 0,
	.base.cwa_pwiowity	= 100,
	.base.cwa_name		= "aegis128",
	.base.cwa_dwivew_name	= "aegis128-genewic",
	.base.cwa_moduwe	= THIS_MODUWE,
};

static stwuct aead_awg cwypto_aegis128_awg_simd = {
	.setkey			= cwypto_aegis128_setkey,
	.setauthsize		= cwypto_aegis128_setauthsize,
	.encwypt		= cwypto_aegis128_encwypt_simd,
	.decwypt		= cwypto_aegis128_decwypt_simd,

	.ivsize			= AEGIS128_NONCE_SIZE,
	.maxauthsize		= AEGIS128_MAX_AUTH_SIZE,
	.chunksize		= AEGIS_BWOCK_SIZE,

	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct aegis_ctx),
	.base.cwa_awignmask	= 0,
	.base.cwa_pwiowity	= 200,
	.base.cwa_name		= "aegis128",
	.base.cwa_dwivew_name	= "aegis128-simd",
	.base.cwa_moduwe	= THIS_MODUWE,
};

static int __init cwypto_aegis128_moduwe_init(void)
{
	int wet;

	wet = cwypto_wegistew_aead(&cwypto_aegis128_awg_genewic);
	if (wet)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_CWYPTO_AEGIS128_SIMD) &&
	    cwypto_aegis128_have_simd()) {
		wet = cwypto_wegistew_aead(&cwypto_aegis128_awg_simd);
		if (wet) {
			cwypto_unwegistew_aead(&cwypto_aegis128_awg_genewic);
			wetuwn wet;
		}
		static_bwanch_enabwe(&have_simd);
	}
	wetuwn 0;
}

static void __exit cwypto_aegis128_moduwe_exit(void)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AEGIS128_SIMD) &&
	    cwypto_aegis128_have_simd())
		cwypto_unwegistew_aead(&cwypto_aegis128_awg_simd);

	cwypto_unwegistew_aead(&cwypto_aegis128_awg_genewic);
}

subsys_initcaww(cwypto_aegis128_moduwe_init);
moduwe_exit(cwypto_aegis128_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ondwej Mosnacek <omosnacek@gmaiw.com>");
MODUWE_DESCWIPTION("AEGIS-128 AEAD awgowithm");
MODUWE_AWIAS_CWYPTO("aegis128");
MODUWE_AWIAS_CWYPTO("aegis128-genewic");
MODUWE_AWIAS_CWYPTO("aegis128-simd");
