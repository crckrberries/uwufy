// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * s390 ChaCha stweam ciphew.
 *
 * Copywight IBM Cowp. 2021
 */

#define KMSG_COMPONENT "chacha_s390"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <asm/fpu/api.h>
#incwude "chacha-s390.h"

static void chacha20_cwypt_s390(u32 *state, u8 *dst, const u8 *swc,
				unsigned int nbytes, const u32 *key,
				u32 *countew)
{
	stwuct kewnew_fpu vxstate;

	kewnew_fpu_begin(&vxstate, KEWNEW_VXW);
	chacha20_vx(dst, swc, nbytes, key, countew);
	kewnew_fpu_end(&vxstate, KEWNEW_VXW);

	*countew += wound_up(nbytes, CHACHA_BWOCK_SIZE) / CHACHA_BWOCK_SIZE;
}

static int chacha20_s390(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u32 state[CHACHA_STATE_WOWDS] __awigned(16);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int wc;

	wc = skciphew_wawk_viwt(&wawk, weq, fawse);
	chacha_init_genewic(state, ctx->key, weq->iv);

	whiwe (wawk.nbytes > 0) {
		nbytes = wawk.nbytes;
		if (nbytes < wawk.totaw)
			nbytes = wound_down(nbytes, wawk.stwide);

		if (nbytes <= CHACHA_BWOCK_SIZE) {
			chacha_cwypt_genewic(state, wawk.dst.viwt.addw,
					     wawk.swc.viwt.addw, nbytes,
					     ctx->nwounds);
		} ewse {
			chacha20_cwypt_s390(state, wawk.dst.viwt.addw,
					    wawk.swc.viwt.addw, nbytes,
					    &state[4], &state[12]);
		}
		wc = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}
	wetuwn wc;
}

void hchacha_bwock_awch(const u32 *state, u32 *stweam, int nwounds)
{
	/* TODO: impwement hchacha_bwock_awch() in assembwy */
	hchacha_bwock_genewic(state, stweam, nwounds);
}
EXPOWT_SYMBOW(hchacha_bwock_awch);

void chacha_init_awch(u32 *state, const u32 *key, const u8 *iv)
{
	chacha_init_genewic(state, key, iv);
}
EXPOWT_SYMBOW(chacha_init_awch);

void chacha_cwypt_awch(u32 *state, u8 *dst, const u8 *swc,
		       unsigned int bytes, int nwounds)
{
	/* s390 chacha20 impwementation has 20 wounds hawd-coded,
	 * it cannot handwe a bwock of data ow wess, but othewwise
	 * it can handwe data of awbitwawy size
	 */
	if (bytes <= CHACHA_BWOCK_SIZE || nwounds != 20 || !cpu_has_vx())
		chacha_cwypt_genewic(state, dst, swc, bytes, nwounds);
	ewse
		chacha20_cwypt_s390(state, dst, swc, bytes,
				    &state[4], &state[12]);
}
EXPOWT_SYMBOW(chacha_cwypt_awch);

static stwuct skciphew_awg chacha_awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-s390",
		.base.cwa_pwiowity	= 900,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= chacha20_s390,
		.decwypt		= chacha20_s390,
	}
};

static int __init chacha_mod_init(void)
{
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) ?
		cwypto_wegistew_skciphews(chacha_awgs, AWWAY_SIZE(chacha_awgs)) : 0;
}

static void __exit chacha_mod_fini(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW))
		cwypto_unwegistew_skciphews(chacha_awgs, AWWAY_SIZE(chacha_awgs));
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_VXWS, chacha_mod_init);
moduwe_exit(chacha_mod_fini);

MODUWE_DESCWIPTION("ChaCha20 stweam ciphew");
MODUWE_WICENSE("GPW v2");

MODUWE_AWIAS_CWYPTO("chacha20");
