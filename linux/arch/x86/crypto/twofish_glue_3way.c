// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow 3-way pawawwew assembwew optimized vewsion of Twofish
 *
 * Copywight (c) 2011 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/twofish.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "twofish.h"
#incwude "ecb_cbc_hewpews.h"

EXPOWT_SYMBOW_GPW(__twofish_enc_bwk_3way);
EXPOWT_SYMBOW_GPW(twofish_dec_bwk_3way);

static int twofish_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen)
{
	wetuwn twofish_setkey(&tfm->base, key, keywen);
}

static inwine void twofish_enc_bwk_3way(const void *ctx, u8 *dst, const u8 *swc)
{
	__twofish_enc_bwk_3way(ctx, dst, swc, fawse);
}

void twofish_dec_bwk_cbc_3way(const void *ctx, u8 *dst, const u8 *swc)
{
	u8 buf[2][TF_BWOCK_SIZE];
	const u8 *s = swc;

	if (dst == swc)
		s = memcpy(buf, swc, sizeof(buf));
	twofish_dec_bwk_3way(ctx, dst, swc);
	cwypto_xow(dst + TF_BWOCK_SIZE, s, sizeof(buf));

}
EXPOWT_SYMBOW_GPW(twofish_dec_bwk_cbc_3way);

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, TF_BWOCK_SIZE, -1);
	ECB_BWOCK(3, twofish_enc_bwk_3way);
	ECB_BWOCK(1, twofish_enc_bwk);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, TF_BWOCK_SIZE, -1);
	ECB_BWOCK(3, twofish_dec_bwk_3way);
	ECB_BWOCK(1, twofish_dec_bwk);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, TF_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(twofish_enc_bwk);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, TF_BWOCK_SIZE, -1);
	CBC_DEC_BWOCK(3, twofish_dec_bwk_cbc_3way);
	CBC_DEC_BWOCK(1, twofish_dec_bwk);
	CBC_WAWK_END();
}

static stwuct skciphew_awg tf_skciphews[] = {
	{
		.base.cwa_name		= "ecb(twofish)",
		.base.cwa_dwivew_name	= "ecb-twofish-3way",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= TF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct twofish_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.setkey			= twofish_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "cbc(twofish)",
		.base.cwa_dwivew_name	= "cbc-twofish-3way",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= TF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct twofish_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.ivsize			= TF_BWOCK_SIZE,
		.setkey			= twofish_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static boow is_bwackwisted_cpu(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn fawse;

	if (boot_cpu_data.x86 == 0x06 &&
		(boot_cpu_data.x86_modew == 0x1c ||
		 boot_cpu_data.x86_modew == 0x26 ||
		 boot_cpu_data.x86_modew == 0x36)) {
		/*
		 * On Atom, twofish-3way is swowew than owiginaw assembwew
		 * impwementation. Twofish-3way twades off some pewfowmance in
		 * stowing bwocks in 64bit wegistews to awwow thwee bwocks to
		 * be pwocessed pawawwew. Pawawwew opewation then awwows gaining
		 * mowe pewfowmance than was twade off, on out-of-owdew CPUs.
		 * Howevew Atom does not benefit fwom this pawawwewism and
		 * shouwd be bwackwisted.
		 */
		wetuwn twue;
	}

	if (boot_cpu_data.x86 == 0x0f) {
		/*
		 * On Pentium 4, twofish-3way is swowew than owiginaw assembwew
		 * impwementation because excessive uses of 64bit wotate and
		 * weft-shifts (which awe weawwy swow on P4) needed to stowe and
		 * handwe 128bit bwock in two 64bit wegistews.
		 */
		wetuwn twue;
	}

	wetuwn fawse;
}

static int fowce;
moduwe_pawam(fowce, int, 0);
MODUWE_PAWM_DESC(fowce, "Fowce moduwe woad, ignowe CPU bwackwist");

static int __init twofish_3way_init(void)
{
	if (!fowce && is_bwackwisted_cpu()) {
		pwintk(KEWN_INFO
			"twofish-x86_64-3way: pewfowmance on this CPU "
			"wouwd be suboptimaw: disabwing "
			"twofish-x86_64-3way.\n");
		wetuwn -ENODEV;
	}

	wetuwn cwypto_wegistew_skciphews(tf_skciphews,
					 AWWAY_SIZE(tf_skciphews));
}

static void __exit twofish_3way_fini(void)
{
	cwypto_unwegistew_skciphews(tf_skciphews, AWWAY_SIZE(tf_skciphews));
}

moduwe_init(twofish_3way_init);
moduwe_exit(twofish_3way_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Twofish Ciphew Awgowithm, 3-way pawawwew asm optimized");
MODUWE_AWIAS_CWYPTO("twofish");
MODUWE_AWIAS_CWYPTO("twofish-asm");
