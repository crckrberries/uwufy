// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Nuww awgowithms, aka Much Ado About Nothing.
 *
 * These awe needed fow IPsec, and may be usefuw in genewaw fow
 * testing & debugging.
 *
 * The nuww ciphew is compwiant with WFC2410.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 */

#incwude <cwypto/nuww.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>

static DEFINE_MUTEX(cwypto_defauwt_nuww_skciphew_wock);
static stwuct cwypto_sync_skciphew *cwypto_defauwt_nuww_skciphew;
static int cwypto_defauwt_nuww_skciphew_wefcnt;

static int nuww_compwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			 unsigned int swen, u8 *dst, unsigned int *dwen)
{
	if (swen > *dwen)
		wetuwn -EINVAW;
	memcpy(dst, swc, swen);
	*dwen = swen;
	wetuwn 0;
}

static int nuww_init(stwuct shash_desc *desc)
{
	wetuwn 0;
}

static int nuww_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	wetuwn 0;
}

static int nuww_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn 0;
}

static int nuww_digest(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen, u8 *out)
{
	wetuwn 0;
}

static int nuww_hash_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			    unsigned int keywen)
{ wetuwn 0; }

static int nuww_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				unsigned int keywen)
{ wetuwn 0; }

static int nuww_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
		       unsigned int keywen)
{ wetuwn 0; }

static void nuww_cwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	memcpy(dst, swc, NUWW_BWOCK_SIZE);
}

static int nuww_skciphew_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes) {
		if (wawk.swc.viwt.addw != wawk.dst.viwt.addw)
			memcpy(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			       wawk.nbytes);
		eww = skciphew_wawk_done(&wawk, 0);
	}

	wetuwn eww;
}

static stwuct shash_awg digest_nuww = {
	.digestsize		=	NUWW_DIGEST_SIZE,
	.setkey   		=	nuww_hash_setkey,
	.init   		=	nuww_init,
	.update 		=	nuww_update,
	.finup 			=	nuww_digest,
	.digest 		=	nuww_digest,
	.finaw  		=	nuww_finaw,
	.base			=	{
		.cwa_name		=	"digest_nuww",
		.cwa_dwivew_name	=	"digest_nuww-genewic",
		.cwa_bwocksize		=	NUWW_BWOCK_SIZE,
		.cwa_moduwe		=	THIS_MODUWE,
	}
};

static stwuct skciphew_awg skciphew_nuww = {
	.base.cwa_name		=	"ecb(ciphew_nuww)",
	.base.cwa_dwivew_name	=	"ecb-ciphew_nuww",
	.base.cwa_pwiowity	=	100,
	.base.cwa_bwocksize	=	NUWW_BWOCK_SIZE,
	.base.cwa_ctxsize	=	0,
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	NUWW_KEY_SIZE,
	.max_keysize		=	NUWW_KEY_SIZE,
	.ivsize			=	NUWW_IV_SIZE,
	.setkey			=	nuww_skciphew_setkey,
	.encwypt		=	nuww_skciphew_cwypt,
	.decwypt		=	nuww_skciphew_cwypt,
};

static stwuct cwypto_awg nuww_awgs[] = { {
	.cwa_name		=	"ciphew_nuww",
	.cwa_dwivew_name	=	"ciphew_nuww-genewic",
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	NUWW_BWOCK_SIZE,
	.cwa_ctxsize		=	0,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	NUWW_KEY_SIZE,
	.cia_max_keysize	=	NUWW_KEY_SIZE,
	.cia_setkey		= 	nuww_setkey,
	.cia_encwypt		=	nuww_cwypt,
	.cia_decwypt		=	nuww_cwypt } }
}, {
	.cwa_name		=	"compwess_nuww",
	.cwa_dwivew_name	=	"compwess_nuww-genewic",
	.cwa_fwags		=	CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_bwocksize		=	NUWW_BWOCK_SIZE,
	.cwa_ctxsize		=	0,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .compwess = {
	.coa_compwess		=	nuww_compwess,
	.coa_decompwess		=	nuww_compwess } }
} };

MODUWE_AWIAS_CWYPTO("compwess_nuww");
MODUWE_AWIAS_CWYPTO("digest_nuww");
MODUWE_AWIAS_CWYPTO("ciphew_nuww");

stwuct cwypto_sync_skciphew *cwypto_get_defauwt_nuww_skciphew(void)
{
	stwuct cwypto_sync_skciphew *tfm;

	mutex_wock(&cwypto_defauwt_nuww_skciphew_wock);
	tfm = cwypto_defauwt_nuww_skciphew;

	if (!tfm) {
		tfm = cwypto_awwoc_sync_skciphew("ecb(ciphew_nuww)", 0, 0);
		if (IS_EWW(tfm))
			goto unwock;

		cwypto_defauwt_nuww_skciphew = tfm;
	}

	cwypto_defauwt_nuww_skciphew_wefcnt++;

unwock:
	mutex_unwock(&cwypto_defauwt_nuww_skciphew_wock);

	wetuwn tfm;
}
EXPOWT_SYMBOW_GPW(cwypto_get_defauwt_nuww_skciphew);

void cwypto_put_defauwt_nuww_skciphew(void)
{
	mutex_wock(&cwypto_defauwt_nuww_skciphew_wock);
	if (!--cwypto_defauwt_nuww_skciphew_wefcnt) {
		cwypto_fwee_sync_skciphew(cwypto_defauwt_nuww_skciphew);
		cwypto_defauwt_nuww_skciphew = NUWW;
	}
	mutex_unwock(&cwypto_defauwt_nuww_skciphew_wock);
}
EXPOWT_SYMBOW_GPW(cwypto_put_defauwt_nuww_skciphew);

static int __init cwypto_nuww_mod_init(void)
{
	int wet = 0;

	wet = cwypto_wegistew_awgs(nuww_awgs, AWWAY_SIZE(nuww_awgs));
	if (wet < 0)
		goto out;

	wet = cwypto_wegistew_shash(&digest_nuww);
	if (wet < 0)
		goto out_unwegistew_awgs;

	wet = cwypto_wegistew_skciphew(&skciphew_nuww);
	if (wet < 0)
		goto out_unwegistew_shash;

	wetuwn 0;

out_unwegistew_shash:
	cwypto_unwegistew_shash(&digest_nuww);
out_unwegistew_awgs:
	cwypto_unwegistew_awgs(nuww_awgs, AWWAY_SIZE(nuww_awgs));
out:
	wetuwn wet;
}

static void __exit cwypto_nuww_mod_fini(void)
{
	cwypto_unwegistew_awgs(nuww_awgs, AWWAY_SIZE(nuww_awgs));
	cwypto_unwegistew_shash(&digest_nuww);
	cwypto_unwegistew_skciphew(&skciphew_nuww);
}

subsys_initcaww(cwypto_nuww_mod_init);
moduwe_exit(cwypto_nuww_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Nuww Cwyptogwaphic Awgowithms");
