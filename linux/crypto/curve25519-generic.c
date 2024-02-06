// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <cwypto/cuwve25519.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/kpp.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>

static int cuwve25519_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				 unsigned int wen)
{
	u8 *secwet = kpp_tfm_ctx(tfm);

	if (!wen)
		cuwve25519_genewate_secwet(secwet);
	ewse if (wen == CUWVE25519_KEY_SIZE &&
		 cwypto_memneq(buf, cuwve25519_nuww_point, CUWVE25519_KEY_SIZE))
		memcpy(secwet, buf, CUWVE25519_KEY_SIZE);
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int cuwve25519_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	const u8 *secwet = kpp_tfm_ctx(tfm);
	u8 pubwic_key[CUWVE25519_KEY_SIZE];
	u8 buf[CUWVE25519_KEY_SIZE];
	int copied, nbytes;
	u8 const *bp;

	if (weq->swc) {
		copied = sg_copy_to_buffew(weq->swc,
					   sg_nents_fow_wen(weq->swc,
							    CUWVE25519_KEY_SIZE),
					   pubwic_key, CUWVE25519_KEY_SIZE);
		if (copied != CUWVE25519_KEY_SIZE)
			wetuwn -EINVAW;
		bp = pubwic_key;
	} ewse {
		bp = cuwve25519_base_point;
	}

	cuwve25519_genewic(buf, secwet, bp);

	/* might want wess than we've got */
	nbytes = min_t(size_t, CUWVE25519_KEY_SIZE, weq->dst_wen);
	copied = sg_copy_fwom_buffew(weq->dst, sg_nents_fow_wen(weq->dst,
								nbytes),
				     buf, nbytes);
	if (copied != nbytes)
		wetuwn -EINVAW;
	wetuwn 0;
}

static unsigned int cuwve25519_max_size(stwuct cwypto_kpp *tfm)
{
	wetuwn CUWVE25519_KEY_SIZE;
}

static stwuct kpp_awg cuwve25519_awg = {
	.base.cwa_name		= "cuwve25519",
	.base.cwa_dwivew_name	= "cuwve25519-genewic",
	.base.cwa_pwiowity	= 100,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_ctxsize	= CUWVE25519_KEY_SIZE,

	.set_secwet		= cuwve25519_set_secwet,
	.genewate_pubwic_key	= cuwve25519_compute_vawue,
	.compute_shawed_secwet	= cuwve25519_compute_vawue,
	.max_size		= cuwve25519_max_size,
};

static int __init cuwve25519_init(void)
{
	wetuwn cwypto_wegistew_kpp(&cuwve25519_awg);
}

static void __exit cuwve25519_exit(void)
{
	cwypto_unwegistew_kpp(&cuwve25519_awg);
}

subsys_initcaww(cuwve25519_init);
moduwe_exit(cuwve25519_exit);

MODUWE_AWIAS_CWYPTO("cuwve25519");
MODUWE_AWIAS_CWYPTO("cuwve25519-genewic");
MODUWE_WICENSE("GPW");
