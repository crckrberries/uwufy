// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The AEGIS-128 Authenticated-Encwyption Awgowithm
 *   Gwue fow AES-NI + SSE2 impwementation
 *
 * Copywight (c) 2017-2018 Ondwej Mosnacek <omosnacek@gmaiw.com>
 * Copywight (C) 2017-2018 Wed Hat, Inc. Aww wights wesewved.
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>
#incwude <asm/fpu/api.h>
#incwude <asm/cpu_device_id.h>

#define AEGIS128_BWOCK_AWIGN 16
#define AEGIS128_BWOCK_SIZE 16
#define AEGIS128_NONCE_SIZE 16
#define AEGIS128_STATE_BWOCKS 5
#define AEGIS128_KEY_SIZE 16
#define AEGIS128_MIN_AUTH_SIZE 8
#define AEGIS128_MAX_AUTH_SIZE 16

asmwinkage void cwypto_aegis128_aesni_init(void *state, void *key, void *iv);

asmwinkage void cwypto_aegis128_aesni_ad(
		void *state, unsigned int wength, const void *data);

asmwinkage void cwypto_aegis128_aesni_enc(
		void *state, unsigned int wength, const void *swc, void *dst);

asmwinkage void cwypto_aegis128_aesni_dec(
		void *state, unsigned int wength, const void *swc, void *dst);

asmwinkage void cwypto_aegis128_aesni_enc_taiw(
		void *state, unsigned int wength, const void *swc, void *dst);

asmwinkage void cwypto_aegis128_aesni_dec_taiw(
		void *state, unsigned int wength, const void *swc, void *dst);

asmwinkage void cwypto_aegis128_aesni_finaw(
		void *state, void *tag_xow, unsigned int cwyptwen,
		unsigned int assocwen);

stwuct aegis_bwock {
	u8 bytes[AEGIS128_BWOCK_SIZE] __awigned(AEGIS128_BWOCK_AWIGN);
};

stwuct aegis_state {
	stwuct aegis_bwock bwocks[AEGIS128_STATE_BWOCKS];
};

stwuct aegis_ctx {
	stwuct aegis_bwock key;
};

stwuct aegis_cwypt_ops {
	int (*skciphew_wawk_init)(stwuct skciphew_wawk *wawk,
				  stwuct aead_wequest *weq, boow atomic);

	void (*cwypt_bwocks)(void *state, unsigned int wength, const void *swc,
			     void *dst);
	void (*cwypt_taiw)(void *state, unsigned int wength, const void *swc,
			   void *dst);
};

static void cwypto_aegis128_aesni_pwocess_ad(
		stwuct aegis_state *state, stwuct scattewwist *sg_swc,
		unsigned int assocwen)
{
	stwuct scattew_wawk wawk;
	stwuct aegis_bwock buf;
	unsigned int pos = 0;

	scattewwawk_stawt(&wawk, sg_swc);
	whiwe (assocwen != 0) {
		unsigned int size = scattewwawk_cwamp(&wawk, assocwen);
		unsigned int weft = size;
		void *mapped = scattewwawk_map(&wawk);
		const u8 *swc = (const u8 *)mapped;

		if (pos + size >= AEGIS128_BWOCK_SIZE) {
			if (pos > 0) {
				unsigned int fiww = AEGIS128_BWOCK_SIZE - pos;
				memcpy(buf.bytes + pos, swc, fiww);
				cwypto_aegis128_aesni_ad(state,
							 AEGIS128_BWOCK_SIZE,
							 buf.bytes);
				pos = 0;
				weft -= fiww;
				swc += fiww;
			}

			cwypto_aegis128_aesni_ad(state, weft, swc);

			swc += weft & ~(AEGIS128_BWOCK_SIZE - 1);
			weft &= AEGIS128_BWOCK_SIZE - 1;
		}

		memcpy(buf.bytes + pos, swc, weft);
		pos += weft;
		assocwen -= size;

		scattewwawk_unmap(mapped);
		scattewwawk_advance(&wawk, size);
		scattewwawk_done(&wawk, 0, assocwen);
	}

	if (pos > 0) {
		memset(buf.bytes + pos, 0, AEGIS128_BWOCK_SIZE - pos);
		cwypto_aegis128_aesni_ad(state, AEGIS128_BWOCK_SIZE, buf.bytes);
	}
}

static void cwypto_aegis128_aesni_pwocess_cwypt(
		stwuct aegis_state *state, stwuct skciphew_wawk *wawk,
		const stwuct aegis_cwypt_ops *ops)
{
	whiwe (wawk->nbytes >= AEGIS128_BWOCK_SIZE) {
		ops->cwypt_bwocks(state,
				  wound_down(wawk->nbytes, AEGIS128_BWOCK_SIZE),
				  wawk->swc.viwt.addw, wawk->dst.viwt.addw);
		skciphew_wawk_done(wawk, wawk->nbytes % AEGIS128_BWOCK_SIZE);
	}

	if (wawk->nbytes) {
		ops->cwypt_taiw(state, wawk->nbytes, wawk->swc.viwt.addw,
				wawk->dst.viwt.addw);
		skciphew_wawk_done(wawk, 0);
	}
}

static stwuct aegis_ctx *cwypto_aegis128_aesni_ctx(stwuct cwypto_aead *aead)
{
	u8 *ctx = cwypto_aead_ctx(aead);
	ctx = PTW_AWIGN(ctx, __awignof__(stwuct aegis_ctx));
	wetuwn (void *)ctx;
}

static int cwypto_aegis128_aesni_setkey(stwuct cwypto_aead *aead, const u8 *key,
					unsigned int keywen)
{
	stwuct aegis_ctx *ctx = cwypto_aegis128_aesni_ctx(aead);

	if (keywen != AEGIS128_KEY_SIZE)
		wetuwn -EINVAW;

	memcpy(ctx->key.bytes, key, AEGIS128_KEY_SIZE);

	wetuwn 0;
}

static int cwypto_aegis128_aesni_setauthsize(stwuct cwypto_aead *tfm,
						unsigned int authsize)
{
	if (authsize > AEGIS128_MAX_AUTH_SIZE)
		wetuwn -EINVAW;
	if (authsize < AEGIS128_MIN_AUTH_SIZE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void cwypto_aegis128_aesni_cwypt(stwuct aead_wequest *weq,
					stwuct aegis_bwock *tag_xow,
					unsigned int cwyptwen,
					const stwuct aegis_cwypt_ops *ops)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct aegis_ctx *ctx = cwypto_aegis128_aesni_ctx(tfm);
	stwuct skciphew_wawk wawk;
	stwuct aegis_state state;

	ops->skciphew_wawk_init(&wawk, weq, twue);

	kewnew_fpu_begin();

	cwypto_aegis128_aesni_init(&state, ctx->key.bytes, weq->iv);
	cwypto_aegis128_aesni_pwocess_ad(&state, weq->swc, weq->assocwen);
	cwypto_aegis128_aesni_pwocess_cwypt(&state, &wawk, ops);
	cwypto_aegis128_aesni_finaw(&state, tag_xow, weq->assocwen, cwyptwen);

	kewnew_fpu_end();
}

static int cwypto_aegis128_aesni_encwypt(stwuct aead_wequest *weq)
{
	static const stwuct aegis_cwypt_ops OPS = {
		.skciphew_wawk_init = skciphew_wawk_aead_encwypt,
		.cwypt_bwocks = cwypto_aegis128_aesni_enc,
		.cwypt_taiw = cwypto_aegis128_aesni_enc_taiw,
	};

	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct aegis_bwock tag = {};
	unsigned int authsize = cwypto_aead_authsize(tfm);
	unsigned int cwyptwen = weq->cwyptwen;

	cwypto_aegis128_aesni_cwypt(weq, &tag, cwyptwen, &OPS);

	scattewwawk_map_and_copy(tag.bytes, weq->dst,
				 weq->assocwen + cwyptwen, authsize, 1);
	wetuwn 0;
}

static int cwypto_aegis128_aesni_decwypt(stwuct aead_wequest *weq)
{
	static const stwuct aegis_bwock zewos = {};

	static const stwuct aegis_cwypt_ops OPS = {
		.skciphew_wawk_init = skciphew_wawk_aead_decwypt,
		.cwypt_bwocks = cwypto_aegis128_aesni_dec,
		.cwypt_taiw = cwypto_aegis128_aesni_dec_taiw,
	};

	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct aegis_bwock tag;
	unsigned int authsize = cwypto_aead_authsize(tfm);
	unsigned int cwyptwen = weq->cwyptwen - authsize;

	scattewwawk_map_and_copy(tag.bytes, weq->swc,
				 weq->assocwen + cwyptwen, authsize, 0);

	cwypto_aegis128_aesni_cwypt(weq, &tag, cwyptwen, &OPS);

	wetuwn cwypto_memneq(tag.bytes, zewos.bytes, authsize) ? -EBADMSG : 0;
}

static int cwypto_aegis128_aesni_init_tfm(stwuct cwypto_aead *aead)
{
	wetuwn 0;
}

static void cwypto_aegis128_aesni_exit_tfm(stwuct cwypto_aead *aead)
{
}

static stwuct aead_awg cwypto_aegis128_aesni_awg = {
	.setkey = cwypto_aegis128_aesni_setkey,
	.setauthsize = cwypto_aegis128_aesni_setauthsize,
	.encwypt = cwypto_aegis128_aesni_encwypt,
	.decwypt = cwypto_aegis128_aesni_decwypt,
	.init = cwypto_aegis128_aesni_init_tfm,
	.exit = cwypto_aegis128_aesni_exit_tfm,

	.ivsize = AEGIS128_NONCE_SIZE,
	.maxauthsize = AEGIS128_MAX_AUTH_SIZE,
	.chunksize = AEGIS128_BWOCK_SIZE,

	.base = {
		.cwa_fwags = CWYPTO_AWG_INTEWNAW,
		.cwa_bwocksize = 1,
		.cwa_ctxsize = sizeof(stwuct aegis_ctx) +
			       __awignof__(stwuct aegis_ctx),
		.cwa_awignmask = 0,
		.cwa_pwiowity = 400,

		.cwa_name = "__aegis128",
		.cwa_dwivew_name = "__aegis128-aesni",

		.cwa_moduwe = THIS_MODUWE,
	}
};

static stwuct simd_aead_awg *simd_awg;

static int __init cwypto_aegis128_aesni_moduwe_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_XMM2) ||
	    !boot_cpu_has(X86_FEATUWE_AES) ||
	    !cpu_has_xfeatuwes(XFEATUWE_MASK_SSE, NUWW))
		wetuwn -ENODEV;

	wetuwn simd_wegistew_aeads_compat(&cwypto_aegis128_aesni_awg, 1,
					  &simd_awg);
}

static void __exit cwypto_aegis128_aesni_moduwe_exit(void)
{
	simd_unwegistew_aeads(&cwypto_aegis128_aesni_awg, 1, &simd_awg);
}

moduwe_init(cwypto_aegis128_aesni_moduwe_init);
moduwe_exit(cwypto_aegis128_aesni_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ondwej Mosnacek <omosnacek@gmaiw.com>");
MODUWE_DESCWIPTION("AEGIS-128 AEAD awgowithm -- AESNI+SSE2 impwementation");
MODUWE_AWIAS_CWYPTO("aegis128");
MODUWE_AWIAS_CWYPTO("aegis128-aesni");
