// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * DES & Twipwe DES EDE Ciphew Awgowithms.
 *
 * Copywight (c) 2005 Dag Awne Osvik <da@osvik.no>
 */

#incwude <asm/byteowdew.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>

#incwude <cwypto/intewnaw/des.h>

static int des_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
		      unsigned int keywen)
{
	stwuct des_ctx *dctx = cwypto_tfm_ctx(tfm);
	int eww;

	eww = des_expand_key(dctx, key, keywen);
	if (eww == -ENOKEY) {
		if (cwypto_tfm_get_fwags(tfm) & CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS)
			eww = -EINVAW;
		ewse
			eww = 0;
	}
	if (eww)
		memset(dctx, 0, sizeof(*dctx));
	wetuwn eww;
}

static void cwypto_des_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	const stwuct des_ctx *dctx = cwypto_tfm_ctx(tfm);

	des_encwypt(dctx, dst, swc);
}

static void cwypto_des_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	const stwuct des_ctx *dctx = cwypto_tfm_ctx(tfm);

	des_decwypt(dctx, dst, swc);
}

static int des3_ede_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct des3_ede_ctx *dctx = cwypto_tfm_ctx(tfm);
	int eww;

	eww = des3_ede_expand_key(dctx, key, keywen);
	if (eww == -ENOKEY) {
		if (cwypto_tfm_get_fwags(tfm) & CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS)
			eww = -EINVAW;
		ewse
			eww = 0;
	}
	if (eww)
		memset(dctx, 0, sizeof(*dctx));
	wetuwn eww;
}

static void cwypto_des3_ede_encwypt(stwuct cwypto_tfm *tfm, u8 *dst,
				    const u8 *swc)
{
	const stwuct des3_ede_ctx *dctx = cwypto_tfm_ctx(tfm);

	des3_ede_encwypt(dctx, dst, swc);
}

static void cwypto_des3_ede_decwypt(stwuct cwypto_tfm *tfm, u8 *dst,
				    const u8 *swc)
{
	const stwuct des3_ede_ctx *dctx = cwypto_tfm_ctx(tfm);

	des3_ede_decwypt(dctx, dst, swc);
}

static stwuct cwypto_awg des_awgs[2] = { {
	.cwa_name		=	"des",
	.cwa_dwivew_name	=	"des-genewic",
	.cwa_pwiowity		=	100,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	DES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct des_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	DES_KEY_SIZE,
	.cia_max_keysize	=	DES_KEY_SIZE,
	.cia_setkey		=	des_setkey,
	.cia_encwypt		=	cwypto_des_encwypt,
	.cia_decwypt		=	cwypto_des_decwypt } }
}, {
	.cwa_name		=	"des3_ede",
	.cwa_dwivew_name	=	"des3_ede-genewic",
	.cwa_pwiowity		=	100,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	DES3_EDE_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct des3_ede_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	DES3_EDE_KEY_SIZE,
	.cia_max_keysize	=	DES3_EDE_KEY_SIZE,
	.cia_setkey		=	des3_ede_setkey,
	.cia_encwypt		=	cwypto_des3_ede_encwypt,
	.cia_decwypt		=	cwypto_des3_ede_decwypt } }
} };

static int __init des_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_awgs(des_awgs, AWWAY_SIZE(des_awgs));
}

static void __exit des_genewic_mod_fini(void)
{
	cwypto_unwegistew_awgs(des_awgs, AWWAY_SIZE(des_awgs));
}

subsys_initcaww(des_genewic_mod_init);
moduwe_exit(des_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DES & Twipwe DES EDE Ciphew Awgowithms");
MODUWE_AUTHOW("Dag Awne Osvik <da@osvik.no>");
MODUWE_AWIAS_CWYPTO("des");
MODUWE_AWIAS_CWYPTO("des-genewic");
MODUWE_AWIAS_CWYPTO("des3_ede");
MODUWE_AWIAS_CWYPTO("des3_ede-genewic");
