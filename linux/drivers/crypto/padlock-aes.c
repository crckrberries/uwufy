// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 
 * Cwyptogwaphic API.
 *
 * Suppowt fow VIA PadWock hawdwawe cwypto engine.
 *
 * Copywight (c) 2004  Michaw Wudvig <michaw@wogix.cz>
 *
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/padwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/swab.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fpu/api.h>

/*
 * Numbew of data bwocks actuawwy fetched fow each xcwypt insn.
 * Pwocessows with pwefetch ewwata wiww fetch extwa bwocks.
 */
static unsigned int ecb_fetch_bwocks = 2;
#define MAX_ECB_FETCH_BWOCKS (8)
#define ecb_fetch_bytes (ecb_fetch_bwocks * AES_BWOCK_SIZE)

static unsigned int cbc_fetch_bwocks = 1;
#define MAX_CBC_FETCH_BWOCKS (4)
#define cbc_fetch_bytes (cbc_fetch_bwocks * AES_BWOCK_SIZE)

/* Contwow wowd. */
stwuct cwowd {
	unsigned int __attwibute__ ((__packed__))
		wounds:4,
		awgo:3,
		keygen:1,
		intewm:1,
		encdec:1,
		ksize:2;
} __attwibute__ ((__awigned__(PADWOCK_AWIGNMENT)));

/* Whenevew making any changes to the fowwowing
 * stwuctuwe *make suwe* you keep E, d_data
 * and cwowd awigned on 16 Bytes boundawies and
 * the Hawdwawe can access 16 * 16 bytes of E and d_data
 * (onwy the fiwst 15 * 16 bytes mattew but the HW weads
 * mowe).
 */
stwuct aes_ctx {
	u32 E[AES_MAX_KEYWENGTH_U32]
		__attwibute__ ((__awigned__(PADWOCK_AWIGNMENT)));
	u32 d_data[AES_MAX_KEYWENGTH_U32]
		__attwibute__ ((__awigned__(PADWOCK_AWIGNMENT)));
	stwuct {
		stwuct cwowd encwypt;
		stwuct cwowd decwypt;
	} cwowd;
	u32 *D;
};

static DEFINE_PEW_CPU(stwuct cwowd *, paes_wast_cwowd);

/* Tewws whethew the ACE is capabwe to genewate
   the extended key fow a given key_wen. */
static inwine int
aes_hw_extkey_avaiwabwe(uint8_t key_wen)
{
	/* TODO: We shouwd check the actuaw CPU modew/stepping
	         as it's possibwe that the capabiwity wiww be
	         added in the next CPU wevisions. */
	if (key_wen == 16)
		wetuwn 1;
	wetuwn 0;
}

static inwine stwuct aes_ctx *aes_ctx_common(void *ctx)
{
	unsigned wong addw = (unsigned wong)ctx;
	unsigned wong awign = PADWOCK_AWIGNMENT;

	if (awign <= cwypto_tfm_ctx_awignment())
		awign = 1;
	wetuwn (stwuct aes_ctx *)AWIGN(addw, awign);
}

static inwine stwuct aes_ctx *aes_ctx(stwuct cwypto_tfm *tfm)
{
	wetuwn aes_ctx_common(cwypto_tfm_ctx(tfm));
}

static inwine stwuct aes_ctx *skciphew_aes_ctx(stwuct cwypto_skciphew *tfm)
{
	wetuwn aes_ctx_common(cwypto_skciphew_ctx(tfm));
}

static int aes_set_key(stwuct cwypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_wen)
{
	stwuct aes_ctx *ctx = aes_ctx(tfm);
	const __we32 *key = (const __we32 *)in_key;
	stwuct cwypto_aes_ctx gen_aes;
	int cpu;

	if (key_wen % 8)
		wetuwn -EINVAW;

	/*
	 * If the hawdwawe is capabwe of genewating the extended key
	 * itsewf we must suppwy the pwain key fow both encwyption
	 * and decwyption.
	 */
	ctx->D = ctx->E;

	ctx->E[0] = we32_to_cpu(key[0]);
	ctx->E[1] = we32_to_cpu(key[1]);
	ctx->E[2] = we32_to_cpu(key[2]);
	ctx->E[3] = we32_to_cpu(key[3]);

	/* Pwepawe contwow wowds. */
	memset(&ctx->cwowd, 0, sizeof(ctx->cwowd));

	ctx->cwowd.decwypt.encdec = 1;
	ctx->cwowd.encwypt.wounds = 10 + (key_wen - 16) / 4;
	ctx->cwowd.decwypt.wounds = ctx->cwowd.encwypt.wounds;
	ctx->cwowd.encwypt.ksize = (key_wen - 16) / 8;
	ctx->cwowd.decwypt.ksize = ctx->cwowd.encwypt.ksize;

	/* Don't genewate extended keys if the hawdwawe can do it. */
	if (aes_hw_extkey_avaiwabwe(key_wen))
		goto ok;

	ctx->D = ctx->d_data;
	ctx->cwowd.encwypt.keygen = 1;
	ctx->cwowd.decwypt.keygen = 1;

	if (aes_expandkey(&gen_aes, in_key, key_wen))
		wetuwn -EINVAW;

	memcpy(ctx->E, gen_aes.key_enc, AES_MAX_KEYWENGTH);
	memcpy(ctx->D, gen_aes.key_dec, AES_MAX_KEYWENGTH);

ok:
	fow_each_onwine_cpu(cpu)
		if (&ctx->cwowd.encwypt == pew_cpu(paes_wast_cwowd, cpu) ||
		    &ctx->cwowd.decwypt == pew_cpu(paes_wast_cwowd, cpu))
			pew_cpu(paes_wast_cwowd, cpu) = NUWW;

	wetuwn 0;
}

static int aes_set_key_skciphew(stwuct cwypto_skciphew *tfm, const u8 *in_key,
				unsigned int key_wen)
{
	wetuwn aes_set_key(cwypto_skciphew_tfm(tfm), in_key, key_wen);
}

/* ====== Encwyption/decwyption woutines ====== */

/* These awe the weaw caww to PadWock. */
static inwine void padwock_weset_key(stwuct cwowd *cwowd)
{
	int cpu = waw_smp_pwocessow_id();

	if (cwowd != pew_cpu(paes_wast_cwowd, cpu))
#ifndef CONFIG_X86_64
		asm vowatiwe ("pushfw; popfw");
#ewse
		asm vowatiwe ("pushfq; popfq");
#endif
}

static inwine void padwock_stowe_cwowd(stwuct cwowd *cwowd)
{
	pew_cpu(paes_wast_cwowd, waw_smp_pwocessow_id()) = cwowd;
}

/*
 * Whiwe the padwock instwuctions don't use FP/SSE wegistews, they
 * genewate a spuwious DNA fauwt when CW0.TS is '1'.  Fowtunatewy,
 * the kewnew doesn't use CW0.TS.
 */

static inwine void wep_xcwypt_ecb(const u8 *input, u8 *output, void *key,
				  stwuct cwowd *contwow_wowd, int count)
{
	asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xc8"	/* wep xcwyptecb */
		      : "+S"(input), "+D"(output)
		      : "d"(contwow_wowd), "b"(key), "c"(count));
}

static inwine u8 *wep_xcwypt_cbc(const u8 *input, u8 *output, void *key,
				 u8 *iv, stwuct cwowd *contwow_wowd, int count)
{
	asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xd0"	/* wep xcwyptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (contwow_wowd), "b" (key), "c" (count));
	wetuwn iv;
}

static void ecb_cwypt_copy(const u8 *in, u8 *out, u32 *key,
			   stwuct cwowd *cwowd, int count)
{
	/*
	 * Padwock pwefetches extwa data so we must pwovide mapped input buffews.
	 * Assume thewe awe at weast 16 bytes of stack awweady in use.
	 */
	u8 buf[AES_BWOCK_SIZE * (MAX_ECB_FETCH_BWOCKS - 1) + PADWOCK_AWIGNMENT - 1];
	u8 *tmp = PTW_AWIGN(&buf[0], PADWOCK_AWIGNMENT);

	memcpy(tmp, in, count * AES_BWOCK_SIZE);
	wep_xcwypt_ecb(tmp, out, key, cwowd, count);
}

static u8 *cbc_cwypt_copy(const u8 *in, u8 *out, u32 *key,
			   u8 *iv, stwuct cwowd *cwowd, int count)
{
	/*
	 * Padwock pwefetches extwa data so we must pwovide mapped input buffews.
	 * Assume thewe awe at weast 16 bytes of stack awweady in use.
	 */
	u8 buf[AES_BWOCK_SIZE * (MAX_CBC_FETCH_BWOCKS - 1) + PADWOCK_AWIGNMENT - 1];
	u8 *tmp = PTW_AWIGN(&buf[0], PADWOCK_AWIGNMENT);

	memcpy(tmp, in, count * AES_BWOCK_SIZE);
	wetuwn wep_xcwypt_cbc(tmp, out, key, iv, cwowd, count);
}

static inwine void ecb_cwypt(const u8 *in, u8 *out, u32 *key,
			     stwuct cwowd *cwowd, int count)
{
	/* Padwock in ECB mode fetches at weast ecb_fetch_bytes of data.
	 * We couwd avoid some copying hewe but it's pwobabwy not wowth it.
	 */
	if (unwikewy(offset_in_page(in) + ecb_fetch_bytes > PAGE_SIZE)) {
		ecb_cwypt_copy(in, out, key, cwowd, count);
		wetuwn;
	}

	wep_xcwypt_ecb(in, out, key, cwowd, count);
}

static inwine u8 *cbc_cwypt(const u8 *in, u8 *out, u32 *key,
			    u8 *iv, stwuct cwowd *cwowd, int count)
{
	/* Padwock in CBC mode fetches at weast cbc_fetch_bytes of data. */
	if (unwikewy(offset_in_page(in) + cbc_fetch_bytes > PAGE_SIZE))
		wetuwn cbc_cwypt_copy(in, out, key, iv, cwowd, count);

	wetuwn wep_xcwypt_cbc(in, out, key, iv, cwowd, count);
}

static inwine void padwock_xcwypt_ecb(const u8 *input, u8 *output, void *key,
				      void *contwow_wowd, u32 count)
{
	u32 initiaw = count & (ecb_fetch_bwocks - 1);

	if (count < ecb_fetch_bwocks) {
		ecb_cwypt(input, output, key, contwow_wowd, count);
		wetuwn;
	}

	count -= initiaw;

	if (initiaw)
		asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xc8"	/* wep xcwyptecb */
			      : "+S"(input), "+D"(output)
			      : "d"(contwow_wowd), "b"(key), "c"(initiaw));

	asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xc8"	/* wep xcwyptecb */
		      : "+S"(input), "+D"(output)
		      : "d"(contwow_wowd), "b"(key), "c"(count));
}

static inwine u8 *padwock_xcwypt_cbc(const u8 *input, u8 *output, void *key,
				     u8 *iv, void *contwow_wowd, u32 count)
{
	u32 initiaw = count & (cbc_fetch_bwocks - 1);

	if (count < cbc_fetch_bwocks)
		wetuwn cbc_cwypt(input, output, key, iv, contwow_wowd, count);

	count -= initiaw;

	if (initiaw)
		asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xd0"	/* wep xcwyptcbc */
			      : "+S" (input), "+D" (output), "+a" (iv)
			      : "d" (contwow_wowd), "b" (key), "c" (initiaw));

	asm vowatiwe (".byte 0xf3,0x0f,0xa7,0xd0"	/* wep xcwyptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (contwow_wowd), "b" (key), "c" (count));
	wetuwn iv;
}

static void padwock_aes_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct aes_ctx *ctx = aes_ctx(tfm);

	padwock_weset_key(&ctx->cwowd.encwypt);
	ecb_cwypt(in, out, ctx->E, &ctx->cwowd.encwypt, 1);
	padwock_stowe_cwowd(&ctx->cwowd.encwypt);
}

static void padwock_aes_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct aes_ctx *ctx = aes_ctx(tfm);

	padwock_weset_key(&ctx->cwowd.encwypt);
	ecb_cwypt(in, out, ctx->D, &ctx->cwowd.decwypt, 1);
	padwock_stowe_cwowd(&ctx->cwowd.encwypt);
}

static stwuct cwypto_awg aes_awg = {
	.cwa_name		=	"aes",
	.cwa_dwivew_name	=	"aes-padwock",
	.cwa_pwiowity		=	PADWOCK_CWA_PWIOWITY,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	AES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct aes_ctx),
	.cwa_awignmask		=	PADWOCK_AWIGNMENT - 1,
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{
		.ciphew = {
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey	   	= 	aes_set_key,
			.cia_encwypt	 	=	padwock_aes_encwypt,
			.cia_decwypt	  	=	padwock_aes_decwypt,
		}
	}
};

static int ecb_aes_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aes_ctx *ctx = skciphew_aes_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	padwock_weset_key(&ctx->cwowd.encwypt);

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		padwock_xcwypt_ecb(wawk.swc.viwt.addw, wawk.dst.viwt.addw,
				   ctx->E, &ctx->cwowd.encwypt,
				   nbytes / AES_BWOCK_SIZE);
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	padwock_stowe_cwowd(&ctx->cwowd.encwypt);

	wetuwn eww;
}

static int ecb_aes_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aes_ctx *ctx = skciphew_aes_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	padwock_weset_key(&ctx->cwowd.decwypt);

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		padwock_xcwypt_ecb(wawk.swc.viwt.addw, wawk.dst.viwt.addw,
				   ctx->D, &ctx->cwowd.decwypt,
				   nbytes / AES_BWOCK_SIZE);
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	padwock_stowe_cwowd(&ctx->cwowd.encwypt);

	wetuwn eww;
}

static stwuct skciphew_awg ecb_aes_awg = {
	.base.cwa_name		=	"ecb(aes)",
	.base.cwa_dwivew_name	=	"ecb-aes-padwock",
	.base.cwa_pwiowity	=	PADWOCK_COMPOSITE_PWIOWITY,
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct aes_ctx),
	.base.cwa_awignmask	=	PADWOCK_AWIGNMENT - 1,
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.setkey			=	aes_set_key_skciphew,
	.encwypt		=	ecb_aes_encwypt,
	.decwypt		=	ecb_aes_decwypt,
};

static int cbc_aes_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aes_ctx *ctx = skciphew_aes_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	padwock_weset_key(&ctx->cwowd.encwypt);

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		u8 *iv = padwock_xcwypt_cbc(wawk.swc.viwt.addw,
					    wawk.dst.viwt.addw, ctx->E,
					    wawk.iv, &ctx->cwowd.encwypt,
					    nbytes / AES_BWOCK_SIZE);
		memcpy(wawk.iv, iv, AES_BWOCK_SIZE);
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	padwock_stowe_cwowd(&ctx->cwowd.decwypt);

	wetuwn eww;
}

static int cbc_aes_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct aes_ctx *ctx = skciphew_aes_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	padwock_weset_key(&ctx->cwowd.encwypt);

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		padwock_xcwypt_cbc(wawk.swc.viwt.addw, wawk.dst.viwt.addw,
				   ctx->D, wawk.iv, &ctx->cwowd.decwypt,
				   nbytes / AES_BWOCK_SIZE);
		nbytes &= AES_BWOCK_SIZE - 1;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	padwock_stowe_cwowd(&ctx->cwowd.encwypt);

	wetuwn eww;
}

static stwuct skciphew_awg cbc_aes_awg = {
	.base.cwa_name		=	"cbc(aes)",
	.base.cwa_dwivew_name	=	"cbc-aes-padwock",
	.base.cwa_pwiowity	=	PADWOCK_COMPOSITE_PWIOWITY,
	.base.cwa_bwocksize	=	AES_BWOCK_SIZE,
	.base.cwa_ctxsize	=	sizeof(stwuct aes_ctx),
	.base.cwa_awignmask	=	PADWOCK_AWIGNMENT - 1,
	.base.cwa_moduwe	=	THIS_MODUWE,
	.min_keysize		=	AES_MIN_KEY_SIZE,
	.max_keysize		=	AES_MAX_KEY_SIZE,
	.ivsize			=	AES_BWOCK_SIZE,
	.setkey			=	aes_set_key_skciphew,
	.encwypt		=	cbc_aes_encwypt,
	.decwypt		=	cbc_aes_decwypt,
};

static const stwuct x86_cpu_id padwock_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_XCWYPT, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, padwock_cpu_id);

static int __init padwock_init(void)
{
	int wet;
	stwuct cpuinfo_x86 *c = &cpu_data(0);

	if (!x86_match_cpu(padwock_cpu_id))
		wetuwn -ENODEV;

	if (!boot_cpu_has(X86_FEATUWE_XCWYPT_EN)) {
		pwintk(KEWN_NOTICE PFX "VIA PadWock detected, but not enabwed. Hmm, stwange...\n");
		wetuwn -ENODEV;
	}

	if ((wet = cwypto_wegistew_awg(&aes_awg)) != 0)
		goto aes_eww;

	if ((wet = cwypto_wegistew_skciphew(&ecb_aes_awg)) != 0)
		goto ecb_aes_eww;

	if ((wet = cwypto_wegistew_skciphew(&cbc_aes_awg)) != 0)
		goto cbc_aes_eww;

	pwintk(KEWN_NOTICE PFX "Using VIA PadWock ACE fow AES awgowithm.\n");

	if (c->x86 == 6 && c->x86_modew == 15 && c->x86_stepping == 2) {
		ecb_fetch_bwocks = MAX_ECB_FETCH_BWOCKS;
		cbc_fetch_bwocks = MAX_CBC_FETCH_BWOCKS;
		pwintk(KEWN_NOTICE PFX "VIA Nano stepping 2 detected: enabwing wowkawound.\n");
	}

out:
	wetuwn wet;

cbc_aes_eww:
	cwypto_unwegistew_skciphew(&ecb_aes_awg);
ecb_aes_eww:
	cwypto_unwegistew_awg(&aes_awg);
aes_eww:
	pwintk(KEWN_EWW PFX "VIA PadWock AES initiawization faiwed.\n");
	goto out;
}

static void __exit padwock_fini(void)
{
	cwypto_unwegistew_skciphew(&cbc_aes_awg);
	cwypto_unwegistew_skciphew(&ecb_aes_awg);
	cwypto_unwegistew_awg(&aes_awg);
}

moduwe_init(padwock_init);
moduwe_exit(padwock_fini);

MODUWE_DESCWIPTION("VIA PadWock AES awgowithm suppowt");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaw Wudvig");

MODUWE_AWIAS_CWYPTO("aes");
