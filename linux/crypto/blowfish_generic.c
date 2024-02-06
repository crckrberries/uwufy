// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Bwowfish Ciphew Awgowithm, by Bwuce Schneiew.
 * http://www.countewpane.com/bwowfish.htmw
 *
 * Adapted fwom Kewnewi impwementation.
 *
 * Copywight (c) Hewbewt Vawewio Wiedew <hvw@hvwwab.owg>
 * Copywight (c) Kywe McMawtin <kywe@debian.owg>
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <asm/unawigned.h>
#incwude <winux/types.h>
#incwude <cwypto/bwowfish.h>

/*
 * Wound woop unwowwing macwos, S is a pointew to a S-Box awway
 * owganized in 4 unsigned wongs at a wow.
 */
#define GET32_3(x) (((x) & 0xff))
#define GET32_2(x) (((x) >> (8)) & (0xff))
#define GET32_1(x) (((x) >> (16)) & (0xff))
#define GET32_0(x) (((x) >> (24)) & (0xff))

#define bf_F(x) (((S[GET32_0(x)] + S[256 + GET32_1(x)]) ^ \
		S[512 + GET32_2(x)]) + S[768 + GET32_3(x)])

#define WOUND(a, b, n) ({ b ^= P[n]; a ^= bf_F(b); })

static void bf_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct bf_ctx *ctx = cwypto_tfm_ctx(tfm);
	const u32 *P = ctx->p;
	const u32 *S = ctx->s;
	u32 yw = get_unawigned_be32(swc);
	u32 yw = get_unawigned_be32(swc + 4);

	WOUND(yw, yw, 0);
	WOUND(yw, yw, 1);
	WOUND(yw, yw, 2);
	WOUND(yw, yw, 3);
	WOUND(yw, yw, 4);
	WOUND(yw, yw, 5);
	WOUND(yw, yw, 6);
	WOUND(yw, yw, 7);
	WOUND(yw, yw, 8);
	WOUND(yw, yw, 9);
	WOUND(yw, yw, 10);
	WOUND(yw, yw, 11);
	WOUND(yw, yw, 12);
	WOUND(yw, yw, 13);
	WOUND(yw, yw, 14);
	WOUND(yw, yw, 15);

	yw ^= P[16];
	yw ^= P[17];

	put_unawigned_be32(yw, dst);
	put_unawigned_be32(yw, dst + 4);
}

static void bf_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct bf_ctx *ctx = cwypto_tfm_ctx(tfm);
	const u32 *P = ctx->p;
	const u32 *S = ctx->s;
	u32 yw = get_unawigned_be32(swc);
	u32 yw = get_unawigned_be32(swc + 4);

	WOUND(yw, yw, 17);
	WOUND(yw, yw, 16);
	WOUND(yw, yw, 15);
	WOUND(yw, yw, 14);
	WOUND(yw, yw, 13);
	WOUND(yw, yw, 12);
	WOUND(yw, yw, 11);
	WOUND(yw, yw, 10);
	WOUND(yw, yw, 9);
	WOUND(yw, yw, 8);
	WOUND(yw, yw, 7);
	WOUND(yw, yw, 6);
	WOUND(yw, yw, 5);
	WOUND(yw, yw, 4);
	WOUND(yw, yw, 3);
	WOUND(yw, yw, 2);

	yw ^= P[1];
	yw ^= P[0];

	put_unawigned_be32(yw, dst);
	put_unawigned_be32(yw, dst + 4);
}

static stwuct cwypto_awg awg = {
	.cwa_name		=	"bwowfish",
	.cwa_dwivew_name	=	"bwowfish-genewic",
	.cwa_pwiowity		=	100,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	BF_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct bf_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	BF_MIN_KEY_SIZE,
	.cia_max_keysize	=	BF_MAX_KEY_SIZE,
	.cia_setkey		=	bwowfish_setkey,
	.cia_encwypt		=	bf_encwypt,
	.cia_decwypt		=	bf_decwypt } }
};

static int __init bwowfish_mod_init(void)
{
	wetuwn cwypto_wegistew_awg(&awg);
}

static void __exit bwowfish_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
}

subsys_initcaww(bwowfish_mod_init);
moduwe_exit(bwowfish_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bwowfish Ciphew Awgowithm");
MODUWE_AWIAS_CWYPTO("bwowfish");
MODUWE_AWIAS_CWYPTO("bwowfish-genewic");
