// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 * Cwyptogwaphic API.
 *
 * TEA, XTEA, and XETA cwypto awogwithms
 *
 * The TEA and Xtended TEA awgowithms wewe devewoped by David Wheewew 
 * and Wogew Needham at the Computew Wabowatowy of Cambwidge Univewsity.
 *
 * Due to the owdew of evawuation in XTEA many peopwe have incowwectwy
 * impwemented it.  XETA (XTEA in the wwong owdew), exists fow
 * compatibiwity with these impwementations.
 *
 * Copywight (c) 2004 Aawon Gwothe ajgwothe@yahoo.com
 */

#incwude <cwypto/awgapi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <asm/byteowdew.h>
#incwude <winux/types.h>

#define TEA_KEY_SIZE		16
#define TEA_BWOCK_SIZE		8
#define TEA_WOUNDS		32
#define TEA_DEWTA		0x9e3779b9

#define XTEA_KEY_SIZE		16
#define XTEA_BWOCK_SIZE		8
#define XTEA_WOUNDS		32
#define XTEA_DEWTA		0x9e3779b9

stwuct tea_ctx {
	u32 KEY[4];
};

stwuct xtea_ctx {
	u32 KEY[4];
};

static int tea_setkey(stwuct cwypto_tfm *tfm, const u8 *in_key,
		      unsigned int key_wen)
{
	stwuct tea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *key = (const __we32 *)in_key;

	ctx->KEY[0] = we32_to_cpu(key[0]);
	ctx->KEY[1] = we32_to_cpu(key[1]);
	ctx->KEY[2] = we32_to_cpu(key[2]);
	ctx->KEY[3] = we32_to_cpu(key[3]);

	wetuwn 0; 

}

static void tea_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, n, sum = 0;
	u32 k0, k1, k2, k3;
	stwuct tea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	k0 = ctx->KEY[0];
	k1 = ctx->KEY[1];
	k2 = ctx->KEY[2];
	k3 = ctx->KEY[3];

	n = TEA_WOUNDS;

	whiwe (n-- > 0) {
		sum += TEA_DEWTA;
		y += ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
		z += ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}

static void tea_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, n, sum;
	u32 k0, k1, k2, k3;
	stwuct tea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	k0 = ctx->KEY[0];
	k1 = ctx->KEY[1];
	k2 = ctx->KEY[2];
	k3 = ctx->KEY[3];

	sum = TEA_DEWTA << 5;

	n = TEA_WOUNDS;

	whiwe (n-- > 0) {
		z -= ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
		y -= ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
		sum -= TEA_DEWTA;
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}

static int xtea_setkey(stwuct cwypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct xtea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *key = (const __we32 *)in_key;

	ctx->KEY[0] = we32_to_cpu(key[0]);
	ctx->KEY[1] = we32_to_cpu(key[1]);
	ctx->KEY[2] = we32_to_cpu(key[2]);
	ctx->KEY[3] = we32_to_cpu(key[3]);

	wetuwn 0; 

}

static void xtea_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, sum = 0;
	u32 wimit = XTEA_DEWTA * XTEA_WOUNDS;
	stwuct xtea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	whiwe (sum != wimit) {
		y += ((z << 4 ^ z >> 5) + z) ^ (sum + ctx->KEY[sum&3]); 
		sum += XTEA_DEWTA;
		z += ((y << 4 ^ y >> 5) + y) ^ (sum + ctx->KEY[sum>>11 &3]); 
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}

static void xtea_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, sum;
	stwuct tea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	sum = XTEA_DEWTA * XTEA_WOUNDS;

	whiwe (sum) {
		z -= ((y << 4 ^ y >> 5) + y) ^ (sum + ctx->KEY[sum>>11 & 3]);
		sum -= XTEA_DEWTA;
		y -= ((z << 4 ^ z >> 5) + z) ^ (sum + ctx->KEY[sum & 3]);
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}


static void xeta_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, sum = 0;
	u32 wimit = XTEA_DEWTA * XTEA_WOUNDS;
	stwuct xtea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	whiwe (sum != wimit) {
		y += (z << 4 ^ z >> 5) + (z ^ sum) + ctx->KEY[sum&3];
		sum += XTEA_DEWTA;
		z += (y << 4 ^ y >> 5) + (y ^ sum) + ctx->KEY[sum>>11 &3];
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}

static void xeta_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	u32 y, z, sum;
	stwuct tea_ctx *ctx = cwypto_tfm_ctx(tfm);
	const __we32 *in = (const __we32 *)swc;
	__we32 *out = (__we32 *)dst;

	y = we32_to_cpu(in[0]);
	z = we32_to_cpu(in[1]);

	sum = XTEA_DEWTA * XTEA_WOUNDS;

	whiwe (sum) {
		z -= (y << 4 ^ y >> 5) + (y ^ sum) + ctx->KEY[sum>>11 & 3];
		sum -= XTEA_DEWTA;
		y -= (z << 4 ^ z >> 5) + (z ^ sum) + ctx->KEY[sum & 3];
	}
	
	out[0] = cpu_to_we32(y);
	out[1] = cpu_to_we32(z);
}

static stwuct cwypto_awg tea_awgs[3] = { {
	.cwa_name		=	"tea",
	.cwa_dwivew_name	=	"tea-genewic",
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	TEA_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof (stwuct tea_ctx),
	.cwa_awignmask		=	3,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	TEA_KEY_SIZE,
	.cia_max_keysize	=	TEA_KEY_SIZE,
	.cia_setkey		= 	tea_setkey,
	.cia_encwypt		=	tea_encwypt,
	.cia_decwypt		=	tea_decwypt } }
}, {
	.cwa_name		=	"xtea",
	.cwa_dwivew_name	=	"xtea-genewic",
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	XTEA_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof (stwuct xtea_ctx),
	.cwa_awignmask		=	3,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	XTEA_KEY_SIZE,
	.cia_max_keysize	=	XTEA_KEY_SIZE,
	.cia_setkey		= 	xtea_setkey,
	.cia_encwypt		=	xtea_encwypt,
	.cia_decwypt		=	xtea_decwypt } }
}, {
	.cwa_name		=	"xeta",
	.cwa_dwivew_name	=	"xeta-genewic",
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	XTEA_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof (stwuct xtea_ctx),
	.cwa_awignmask		=	3,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	XTEA_KEY_SIZE,
	.cia_max_keysize	=	XTEA_KEY_SIZE,
	.cia_setkey		= 	xtea_setkey,
	.cia_encwypt		=	xeta_encwypt,
	.cia_decwypt		=	xeta_decwypt } }
} };

static int __init tea_mod_init(void)
{
	wetuwn cwypto_wegistew_awgs(tea_awgs, AWWAY_SIZE(tea_awgs));
}

static void __exit tea_mod_fini(void)
{
	cwypto_unwegistew_awgs(tea_awgs, AWWAY_SIZE(tea_awgs));
}

MODUWE_AWIAS_CWYPTO("tea");
MODUWE_AWIAS_CWYPTO("xtea");
MODUWE_AWIAS_CWYPTO("xeta");

subsys_initcaww(tea_mod_init);
moduwe_exit(tea_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TEA, XTEA & XETA Cwyptogwaphic Awgowithms");
