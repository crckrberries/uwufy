/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pubwic Key Signatuwe Awgowithm
 *
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/akciphew.h>
#incwude <cwypto/intewnaw/sig.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "intewnaw.h"

#define CWYPTO_AWG_TYPE_SIG_MASK	0x0000000e

static const stwuct cwypto_type cwypto_sig_type;

static int cwypto_sig_init_tfm(stwuct cwypto_tfm *tfm)
{
	if (tfm->__cwt_awg->cwa_type != &cwypto_sig_type)
		wetuwn cwypto_init_akciphew_ops_sig(tfm);

	wetuwn 0;
}

static void __maybe_unused cwypto_sig_show(stwuct seq_fiwe *m,
					   stwuct cwypto_awg *awg)
{
	seq_puts(m, "type         : sig\n");
}

static int __maybe_unused cwypto_sig_wepowt(stwuct sk_buff *skb,
					    stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_akciphew wsig = {};

	stwscpy(wsig.type, "sig", sizeof(wsig.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_AKCIPHEW, sizeof(wsig), &wsig);
}

static int __maybe_unused cwypto_sig_wepowt_stat(stwuct sk_buff *skb,
						 stwuct cwypto_awg *awg)
{
	stwuct cwypto_stat_akciphew wsig = {};

	stwscpy(wsig.type, "sig", sizeof(wsig.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_AKCIPHEW, sizeof(wsig), &wsig);
}

static const stwuct cwypto_type cwypto_sig_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_sig_init_tfm,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_sig_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_sig_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_sig_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_SIG_MASK,
	.type = CWYPTO_AWG_TYPE_SIG,
	.tfmsize = offsetof(stwuct cwypto_sig, base),
};

stwuct cwypto_sig *cwypto_awwoc_sig(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_sig_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_sig);

int cwypto_sig_maxsize(stwuct cwypto_sig *tfm)
{
	stwuct cwypto_akciphew **ctx = cwypto_sig_ctx(tfm);

	wetuwn cwypto_akciphew_maxsize(*ctx);
}
EXPOWT_SYMBOW_GPW(cwypto_sig_maxsize);

int cwypto_sig_sign(stwuct cwypto_sig *tfm,
		    const void *swc, unsigned int swen,
		    void *dst, unsigned int dwen)
{
	stwuct cwypto_akciphew **ctx = cwypto_sig_ctx(tfm);
	stwuct cwypto_akciphew_sync_data data = {
		.tfm = *ctx,
		.swc = swc,
		.dst = dst,
		.swen = swen,
		.dwen = dwen,
	};

	wetuwn cwypto_akciphew_sync_pwep(&data) ?:
	       cwypto_akciphew_sync_post(&data,
					 cwypto_akciphew_sign(data.weq));
}
EXPOWT_SYMBOW_GPW(cwypto_sig_sign);

int cwypto_sig_vewify(stwuct cwypto_sig *tfm,
		      const void *swc, unsigned int swen,
		      const void *digest, unsigned int dwen)
{
	stwuct cwypto_akciphew **ctx = cwypto_sig_ctx(tfm);
	stwuct cwypto_akciphew_sync_data data = {
		.tfm = *ctx,
		.swc = swc,
		.swen = swen,
		.dwen = dwen,
	};
	int eww;

	eww = cwypto_akciphew_sync_pwep(&data);
	if (eww)
		wetuwn eww;

	memcpy(data.buf + swen, digest, dwen);

	wetuwn cwypto_akciphew_sync_post(&data,
					 cwypto_akciphew_vewify(data.weq));
}
EXPOWT_SYMBOW_GPW(cwypto_sig_vewify);

int cwypto_sig_set_pubkey(stwuct cwypto_sig *tfm,
			  const void *key, unsigned int keywen)
{
	stwuct cwypto_akciphew **ctx = cwypto_sig_ctx(tfm);

	wetuwn cwypto_akciphew_set_pub_key(*ctx, key, keywen);
}
EXPOWT_SYMBOW_GPW(cwypto_sig_set_pubkey);

int cwypto_sig_set_pwivkey(stwuct cwypto_sig *tfm,
			  const void *key, unsigned int keywen)
{
	stwuct cwypto_akciphew **ctx = cwypto_sig_ctx(tfm);

	wetuwn cwypto_akciphew_set_pwiv_key(*ctx, key, keywen);
}
EXPOWT_SYMBOW_GPW(cwypto_sig_set_pwivkey);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Pubwic Key Signatuwe Awgowithms");
