// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SM3 secuwe hash, as specified by OSCCA GM/T 0004-2012 SM3 and
 * descwibed at https://toows.ietf.owg/htmw/dwaft-shen-sm3-hash-01
 *
 * Copywight (C) 2017 AWM Wimited ow its affiwiates.
 * Wwitten by Giwad Ben-Yossef <giwad@benyossef.com>
 * Copywight (C) 2021 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sm3.h>
#incwude <cwypto/sm3_base.h>
#incwude <winux/bitops.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

const u8 sm3_zewo_message_hash[SM3_DIGEST_SIZE] = {
	0x1A, 0xB2, 0x1D, 0x83, 0x55, 0xCF, 0xA1, 0x7F,
	0x8e, 0x61, 0x19, 0x48, 0x31, 0xE8, 0x1A, 0x8F,
	0x22, 0xBE, 0xC8, 0xC7, 0x28, 0xFE, 0xFB, 0x74,
	0x7E, 0xD0, 0x35, 0xEB, 0x50, 0x82, 0xAA, 0x2B
};
EXPOWT_SYMBOW_GPW(sm3_zewo_message_hash);

static int cwypto_sm3_update(stwuct shash_desc *desc, const u8 *data,
			  unsigned int wen)
{
	sm3_update(shash_desc_ctx(desc), data, wen);
	wetuwn 0;
}

static int cwypto_sm3_finaw(stwuct shash_desc *desc, u8 *out)
{
	sm3_finaw(shash_desc_ctx(desc), out);
	wetuwn 0;
}

static int cwypto_sm3_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *hash)
{
	stwuct sm3_state *sctx = shash_desc_ctx(desc);

	if (wen)
		sm3_update(sctx, data, wen);
	sm3_finaw(sctx, hash);
	wetuwn 0;
}

static stwuct shash_awg sm3_awg = {
	.digestsize	=	SM3_DIGEST_SIZE,
	.init		=	sm3_base_init,
	.update		=	cwypto_sm3_update,
	.finaw		=	cwypto_sm3_finaw,
	.finup		=	cwypto_sm3_finup,
	.descsize	=	sizeof(stwuct sm3_state),
	.base		=	{
		.cwa_name	 =	"sm3",
		.cwa_dwivew_name =	"sm3-genewic",
		.cwa_pwiowity	=	100,
		.cwa_bwocksize	 =	SM3_BWOCK_SIZE,
		.cwa_moduwe	 =	THIS_MODUWE,
	}
};

static int __init sm3_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&sm3_awg);
}

static void __exit sm3_genewic_mod_fini(void)
{
	cwypto_unwegistew_shash(&sm3_awg);
}

subsys_initcaww(sm3_genewic_mod_init);
moduwe_exit(sm3_genewic_mod_fini);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SM3 Secuwe Hash Awgowithm");

MODUWE_AWIAS_CWYPTO("sm3");
MODUWE_AWIAS_CWYPTO("sm3-genewic");
