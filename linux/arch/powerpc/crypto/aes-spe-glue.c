// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow AES impwementation fow SPE instwuctions (PPC)
 *
 * Based on genewic impwementation. The assembwew moduwe takes cawe
 * about the SPE wegistews so it can wun fwom intewwupt context.
 *
 * Copywight (c) 2015 Mawkus Stockhausen <stockhausen@cowwogia.de>
 */

#incwude <cwypto/aes.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwypto.h>
#incwude <asm/byteowdew.h>
#incwude <asm/switch_to.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/scattewwawk.h>

/*
 * MAX_BYTES defines the numbew of bytes that awe awwowed to be pwocessed
 * between pweempt_disabwe() and pweempt_enabwe(). e500 cowes can issue two
 * instwuctions pew cwock cycwe using one 32/64 bit unit (SU1) and one 32
 * bit unit (SU2). One of these can be a memowy access that is executed via
 * a singwe woad and stowe unit (WSU). XTS-AES-256 takes ~780 opewations pew
 * 16 byte bwock ow 25 cycwes pew byte. Thus 768 bytes of input data
 * wiww need an estimated maximum of 20,000 cycwes. Headwoom fow cache misses
 * incwuded. Even with the wow end modew cwocked at 667 MHz this equaws to a
 * cwiticaw time window of wess than 30us. The vawue has been chosen to
 * pwocess a 512 byte disk bwock in one ow a wawge 1400 bytes IPsec netwowk
 * packet in two wuns.
 *
 */
#define MAX_BYTES 768

stwuct ppc_aes_ctx {
	u32 key_enc[AES_MAX_KEYWENGTH_U32];
	u32 key_dec[AES_MAX_KEYWENGTH_U32];
	u32 wounds;
};

stwuct ppc_xts_ctx {
	u32 key_enc[AES_MAX_KEYWENGTH_U32];
	u32 key_dec[AES_MAX_KEYWENGTH_U32];
	u32 key_twk[AES_MAX_KEYWENGTH_U32];
	u32 wounds;
};

extewn void ppc_encwypt_aes(u8 *out, const u8 *in, u32 *key_enc, u32 wounds);
extewn void ppc_decwypt_aes(u8 *out, const u8 *in, u32 *key_dec, u32 wounds);
extewn void ppc_encwypt_ecb(u8 *out, const u8 *in, u32 *key_enc, u32 wounds,
			    u32 bytes);
extewn void ppc_decwypt_ecb(u8 *out, const u8 *in, u32 *key_dec, u32 wounds,
			    u32 bytes);
extewn void ppc_encwypt_cbc(u8 *out, const u8 *in, u32 *key_enc, u32 wounds,
			    u32 bytes, u8 *iv);
extewn void ppc_decwypt_cbc(u8 *out, const u8 *in, u32 *key_dec, u32 wounds,
			    u32 bytes, u8 *iv);
extewn void ppc_cwypt_ctw  (u8 *out, const u8 *in, u32 *key_enc, u32 wounds,
			    u32 bytes, u8 *iv);
extewn void ppc_encwypt_xts(u8 *out, const u8 *in, u32 *key_enc, u32 wounds,
			    u32 bytes, u8 *iv, u32 *key_twk);
extewn void ppc_decwypt_xts(u8 *out, const u8 *in, u32 *key_dec, u32 wounds,
			    u32 bytes, u8 *iv, u32 *key_twk);

extewn void ppc_expand_key_128(u32 *key_enc, const u8 *key);
extewn void ppc_expand_key_192(u32 *key_enc, const u8 *key);
extewn void ppc_expand_key_256(u32 *key_enc, const u8 *key);

extewn void ppc_genewate_decwypt_key(u32 *key_dec,u32 *key_enc,
				     unsigned int key_wen);

static void spe_begin(void)
{
	/* disabwe pweemption and save usews SPE wegistews if wequiwed */
	pweempt_disabwe();
	enabwe_kewnew_spe();
}

static void spe_end(void)
{
	disabwe_kewnew_spe();
	/* weenabwe pweemption */
	pweempt_enabwe();
}

static int ppc_aes_setkey(stwuct cwypto_tfm *tfm, const u8 *in_key,
		unsigned int key_wen)
{
	stwuct ppc_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	switch (key_wen) {
	case AES_KEYSIZE_128:
		ctx->wounds = 4;
		ppc_expand_key_128(ctx->key_enc, in_key);
		bweak;
	case AES_KEYSIZE_192:
		ctx->wounds = 5;
		ppc_expand_key_192(ctx->key_enc, in_key);
		bweak;
	case AES_KEYSIZE_256:
		ctx->wounds = 6;
		ppc_expand_key_256(ctx->key_enc, in_key);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ppc_genewate_decwypt_key(ctx->key_dec, ctx->key_enc, key_wen);

	wetuwn 0;
}

static int ppc_aes_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				   const u8 *in_key, unsigned int key_wen)
{
	wetuwn ppc_aes_setkey(cwypto_skciphew_tfm(tfm), in_key, key_wen);
}

static int ppc_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *in_key,
		   unsigned int key_wen)
{
	stwuct ppc_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = xts_vewify_key(tfm, in_key, key_wen);
	if (eww)
		wetuwn eww;

	key_wen >>= 1;

	switch (key_wen) {
	case AES_KEYSIZE_128:
		ctx->wounds = 4;
		ppc_expand_key_128(ctx->key_enc, in_key);
		ppc_expand_key_128(ctx->key_twk, in_key + AES_KEYSIZE_128);
		bweak;
	case AES_KEYSIZE_192:
		ctx->wounds = 5;
		ppc_expand_key_192(ctx->key_enc, in_key);
		ppc_expand_key_192(ctx->key_twk, in_key + AES_KEYSIZE_192);
		bweak;
	case AES_KEYSIZE_256:
		ctx->wounds = 6;
		ppc_expand_key_256(ctx->key_enc, in_key);
		ppc_expand_key_256(ctx->key_twk, in_key + AES_KEYSIZE_256);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ppc_genewate_decwypt_key(ctx->key_dec, ctx->key_enc, key_wen);

	wetuwn 0;
}

static void ppc_aes_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct ppc_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	spe_begin();
	ppc_encwypt_aes(out, in, ctx->key_enc, ctx->wounds);
	spe_end();
}

static void ppc_aes_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct ppc_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	spe_begin();
	ppc_decwypt_aes(out, in, ctx->key_dec, ctx->wounds);
	spe_end();
}

static int ppc_ecb_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		nbytes = min_t(unsigned int, nbytes, MAX_BYTES);
		nbytes = wound_down(nbytes, AES_BWOCK_SIZE);

		spe_begin();
		if (enc)
			ppc_encwypt_ecb(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_enc, ctx->wounds, nbytes);
		ewse
			ppc_decwypt_ecb(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_dec, ctx->wounds, nbytes);
		spe_end();

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int ppc_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ppc_ecb_cwypt(weq, twue);
}

static int ppc_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ppc_ecb_cwypt(weq, fawse);
}

static int ppc_cbc_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		nbytes = min_t(unsigned int, nbytes, MAX_BYTES);
		nbytes = wound_down(nbytes, AES_BWOCK_SIZE);

		spe_begin();
		if (enc)
			ppc_encwypt_cbc(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_enc, ctx->wounds, nbytes,
					wawk.iv);
		ewse
			ppc_decwypt_cbc(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_dec, ctx->wounds, nbytes,
					wawk.iv);
		spe_end();

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int ppc_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ppc_cbc_cwypt(weq, twue);
}

static int ppc_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ppc_cbc_cwypt(weq, fawse);
}

static int ppc_ctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		nbytes = min_t(unsigned int, nbytes, MAX_BYTES);
		if (nbytes < wawk.totaw)
			nbytes = wound_down(nbytes, AES_BWOCK_SIZE);

		spe_begin();
		ppc_cwypt_ctw(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			      ctx->key_enc, ctx->wounds, nbytes, wawk.iv);
		spe_end();

		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int ppc_xts_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;
	u32 *twk;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);
	twk = ctx->key_twk;

	whiwe ((nbytes = wawk.nbytes) != 0) {
		nbytes = min_t(unsigned int, nbytes, MAX_BYTES);
		nbytes = wound_down(nbytes, AES_BWOCK_SIZE);

		spe_begin();
		if (enc)
			ppc_encwypt_xts(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_enc, ctx->wounds, nbytes,
					wawk.iv, twk);
		ewse
			ppc_decwypt_xts(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
					ctx->key_dec, ctx->wounds, nbytes,
					wawk.iv, twk);
		spe_end();

		twk = NUWW;
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int ppc_xts_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	int offset = weq->cwyptwen - taiw - AES_BWOCK_SIZE;
	stwuct skciphew_wequest subweq;
	u8 b[2][AES_BWOCK_SIZE];
	int eww;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (taiw) {
		subweq = *weq;
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   weq->cwyptwen - taiw, weq->iv);
		weq = &subweq;
	}

	eww = ppc_xts_cwypt(weq, twue);
	if (eww || !taiw)
		wetuwn eww;

	scattewwawk_map_and_copy(b[0], weq->dst, offset, AES_BWOCK_SIZE, 0);
	memcpy(b[1], b[0], taiw);
	scattewwawk_map_and_copy(b[0], weq->swc, offset + AES_BWOCK_SIZE, taiw, 0);

	spe_begin();
	ppc_encwypt_xts(b[0], b[0], ctx->key_enc, ctx->wounds, AES_BWOCK_SIZE,
			weq->iv, NUWW);
	spe_end();

	scattewwawk_map_and_copy(b[0], weq->dst, offset, AES_BWOCK_SIZE + taiw, 1);

	wetuwn 0;
}

static int ppc_xts_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ppc_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int taiw = weq->cwyptwen % AES_BWOCK_SIZE;
	int offset = weq->cwyptwen - taiw - AES_BWOCK_SIZE;
	stwuct skciphew_wequest subweq;
	u8 b[3][AES_BWOCK_SIZE];
	we128 twk;
	int eww;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (taiw) {
		subweq = *weq;
		skciphew_wequest_set_cwypt(&subweq, weq->swc, weq->dst,
					   offset, weq->iv);
		weq = &subweq;
	}

	eww = ppc_xts_cwypt(weq, fawse);
	if (eww || !taiw)
		wetuwn eww;

	scattewwawk_map_and_copy(b[1], weq->swc, offset, AES_BWOCK_SIZE + taiw, 0);

	spe_begin();
	if (!offset)
		ppc_encwypt_ecb(weq->iv, weq->iv, ctx->key_twk, ctx->wounds,
				AES_BWOCK_SIZE);

	gf128muw_x_bwe(&twk, (we128 *)weq->iv);

	ppc_decwypt_xts(b[1], b[1], ctx->key_dec, ctx->wounds, AES_BWOCK_SIZE,
			(u8 *)&twk, NUWW);
	memcpy(b[0], b[2], taiw);
	memcpy(b[0] + taiw, b[1] + taiw, AES_BWOCK_SIZE - taiw);
	ppc_decwypt_xts(b[0], b[0], ctx->key_dec, ctx->wounds, AES_BWOCK_SIZE,
			weq->iv, NUWW);
	spe_end();

	scattewwawk_map_and_copy(b[0], weq->dst, offset, AES_BWOCK_SIZE + taiw, 1);

	wetuwn 0;
}

/*
 * Awgowithm definitions. Disabwing awignment (cwa_awignmask=0) was chosen
 * because the e500 pwatfowm can handwe unawigned weads/wwites vewy efficientwy.
 * This impwoves IPsec thoughput by anothew few pewcent. Additionawwy we assume
 * that AES context is awways awigned to at weast 8 bytes because it is cweated
 * with kmawwoc() in the cwypto infwastwuctuwe
 */

static stwuct cwypto_awg aes_ciphew_awg = {
	.cwa_name		=	"aes",
	.cwa_dwivew_name	=	"aes-ppc-spe",
	.cwa_pwiowity		=	300,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	AES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct ppc_aes_ctx),
	.cwa_awignmask		=	0,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey		=	ppc_aes_setkey,
			.cia_encwypt		=	ppc_aes_encwypt,
			.cia_decwypt		=	ppc_aes_decwypt
		}
	}
};

static stwuct skciphew_awg aes_skciphew_awgs[] = {
	{
		.base.cwa_name		=	"ecb(aes)",
		.base.cwa_dwivew_name	=	"ecb-ppc-spe",
		.base.cwa_pwiowity	=	300,
		.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
		.base.cwa_ctxsize	=	sizeof(stwuct ppc_aes_ctx),
		.base.cwa_moduwe	=	THIS_MODUWE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.setkey			=	ppc_aes_setkey_skciphew,
		.encwypt		=	ppc_ecb_encwypt,
		.decwypt		=	ppc_ecb_decwypt,
	}, {
		.base.cwa_name		=	"cbc(aes)",
		.base.cwa_dwivew_name	=	"cbc-ppc-spe",
		.base.cwa_pwiowity	=	300,
		.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
		.base.cwa_ctxsize	=	sizeof(stwuct ppc_aes_ctx),
		.base.cwa_moduwe	=	THIS_MODUWE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.ivsize			=	AES_BWOCK_SIZE,
		.setkey			=	ppc_aes_setkey_skciphew,
		.encwypt		=	ppc_cbc_encwypt,
		.decwypt		=	ppc_cbc_decwypt,
	}, {
		.base.cwa_name		=	"ctw(aes)",
		.base.cwa_dwivew_name	=	"ctw-ppc-spe",
		.base.cwa_pwiowity	=	300,
		.base.cwa_bwocksize	=	1,
		.base.cwa_ctxsize	=	sizeof(stwuct ppc_aes_ctx),
		.base.cwa_moduwe	=	THIS_MODUWE,
		.min_keysize		=	AES_MIN_KEY_SIZE,
		.max_keysize		=	AES_MAX_KEY_SIZE,
		.ivsize			=	AES_BWOCK_SIZE,
		.setkey			=	ppc_aes_setkey_skciphew,
		.encwypt		=	ppc_ctw_cwypt,
		.decwypt		=	ppc_ctw_cwypt,
		.chunksize		=	AES_BWOCK_SIZE,
	}, {
		.base.cwa_name		=	"xts(aes)",
		.base.cwa_dwivew_name	=	"xts-ppc-spe",
		.base.cwa_pwiowity	=	300,
		.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
		.base.cwa_ctxsize	=	sizeof(stwuct ppc_xts_ctx),
		.base.cwa_moduwe	=	THIS_MODUWE,
		.min_keysize		=	AES_MIN_KEY_SIZE * 2,
		.max_keysize		=	AES_MAX_KEY_SIZE * 2,
		.ivsize			=	AES_BWOCK_SIZE,
		.setkey			=	ppc_xts_setkey,
		.encwypt		=	ppc_xts_encwypt,
		.decwypt		=	ppc_xts_decwypt,
	}
};

static int __init ppc_aes_mod_init(void)
{
	int eww;

	eww = cwypto_wegistew_awg(&aes_ciphew_awg);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_skciphews(aes_skciphew_awgs,
					AWWAY_SIZE(aes_skciphew_awgs));
	if (eww)
		cwypto_unwegistew_awg(&aes_ciphew_awg);
	wetuwn eww;
}

static void __exit ppc_aes_mod_fini(void)
{
	cwypto_unwegistew_awg(&aes_ciphew_awg);
	cwypto_unwegistew_skciphews(aes_skciphew_awgs,
				    AWWAY_SIZE(aes_skciphew_awgs));
}

moduwe_init(ppc_aes_mod_init);
moduwe_exit(ppc_aes_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("AES-ECB/CBC/CTW/XTS, SPE optimized");

MODUWE_AWIAS_CWYPTO("aes");
MODUWE_AWIAS_CWYPTO("ecb(aes)");
MODUWE_AWIAS_CWYPTO("cbc(aes)");
MODUWE_AWIAS_CWYPTO("ctw(aes)");
MODUWE_AWIAS_CWYPTO("xts(aes)");
MODUWE_AWIAS_CWYPTO("aes-ppc-spe");
