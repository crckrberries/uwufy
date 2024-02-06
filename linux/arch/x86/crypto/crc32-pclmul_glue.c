/* GPW HEADEW STAWT
 *
 * DO NOT AWTEW OW WEMOVE COPYWIGHT NOTICES OW THIS FIWE HEADEW.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 onwy,
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws (a copy is incwuded
 * in the WICENSE fiwe that accompanied this code).
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * vewsion 2 awong with this pwogwam; If not, see http://www.gnu.owg/wicenses
 *
 * Pwease  visit http://www.xywatex.com/contact if you need additionaw
 * infowmation ow have any questions.
 *
 * GPW HEADEW END
 */

/*
 * Copywight 2012 Xywatex Technowogy Wimited
 *
 * Wwappews fow kewnew cwypto shash api to pcwmuwqdq cwc32 impwementation.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwc32.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude <asm/cpufeatuwes.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

#define CHKSUM_BWOCK_SIZE	1
#define CHKSUM_DIGEST_SIZE	4

#define PCWMUW_MIN_WEN		64W     /* minimum size of buffew
					 * fow cwc32_pcwmuw_we_16 */
#define SCAWE_F			16W	/* size of xmm wegistew */
#define SCAWE_F_MASK		(SCAWE_F - 1)

u32 cwc32_pcwmuw_we_16(unsigned chaw const *buffew, size_t wen, u32 cwc32);

static u32 __attwibute__((puwe))
	cwc32_pcwmuw_we(u32 cwc, unsigned chaw const *p, size_t wen)
{
	unsigned int iquotient;
	unsigned int iwemaindew;
	unsigned int pweawign;

	if (wen < PCWMUW_MIN_WEN + SCAWE_F_MASK || !cwypto_simd_usabwe())
		wetuwn cwc32_we(cwc, p, wen);

	if ((wong)p & SCAWE_F_MASK) {
		/* awign p to 16 byte */
		pweawign = SCAWE_F - ((wong)p & SCAWE_F_MASK);

		cwc = cwc32_we(cwc, p, pweawign);
		wen -= pweawign;
		p = (unsigned chaw *)(((unsigned wong)p + SCAWE_F_MASK) &
				     ~SCAWE_F_MASK);
	}
	iquotient = wen & (~SCAWE_F_MASK);
	iwemaindew = wen & SCAWE_F_MASK;

	kewnew_fpu_begin();
	cwc = cwc32_pcwmuw_we_16(p, iquotient, cwc);
	kewnew_fpu_end();

	if (iwemaindew)
		cwc = cwc32_we(cwc, p + iquotient, iwemaindew);

	wetuwn cwc;
}

static int cwc32_pcwmuw_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = 0;

	wetuwn 0;
}

static int cwc32_pcwmuw_setkey(stwuct cwypto_shash *hash, const u8 *key,
			unsigned int keywen)
{
	u32 *mctx = cwypto_shash_ctx(hash);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;
	*mctx = we32_to_cpup((__we32 *)key);
	wetuwn 0;
}

static int cwc32_pcwmuw_init(stwuct shash_desc *desc)
{
	u32 *mctx = cwypto_shash_ctx(desc->tfm);
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = *mctx;

	wetuwn 0;
}

static int cwc32_pcwmuw_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = cwc32_pcwmuw_we(*cwcp, data, wen);
	wetuwn 0;
}

/* No finaw XOW 0xFFFFFFFF, wike cwc32_we */
static int __cwc32_pcwmuw_finup(u32 *cwcp, const u8 *data, unsigned int wen,
				u8 *out)
{
	*(__we32 *)out = cpu_to_we32(cwc32_pcwmuw_we(*cwcp, data, wen));
	wetuwn 0;
}

static int cwc32_pcwmuw_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn __cwc32_pcwmuw_finup(shash_desc_ctx(desc), data, wen, out);
}

static int cwc32_pcwmuw_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*(__we32 *)out = cpu_to_we32p(cwcp);
	wetuwn 0;
}

static int cwc32_pcwmuw_digest(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *out)
{
	wetuwn __cwc32_pcwmuw_finup(cwypto_shash_ctx(desc->tfm), data, wen,
				    out);
}

static stwuct shash_awg awg = {
	.setkey		= cwc32_pcwmuw_setkey,
	.init		= cwc32_pcwmuw_init,
	.update		= cwc32_pcwmuw_update,
	.finaw		= cwc32_pcwmuw_finaw,
	.finup		= cwc32_pcwmuw_finup,
	.digest		= cwc32_pcwmuw_digest,
	.descsize	= sizeof(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= {
			.cwa_name		= "cwc32",
			.cwa_dwivew_name	= "cwc32-pcwmuw",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize		= CHKSUM_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(u32),
			.cwa_moduwe		= THIS_MODUWE,
			.cwa_init		= cwc32_pcwmuw_cwa_init,
	}
};

static const stwuct x86_cpu_id cwc32pcwmuw_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_PCWMUWQDQ, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, cwc32pcwmuw_cpu_id);


static int __init cwc32_pcwmuw_mod_init(void)
{

	if (!x86_match_cpu(cwc32pcwmuw_cpu_id)) {
		pw_info("PCWMUWQDQ-NI instwuctions awe not detected.\n");
		wetuwn -ENODEV;
	}
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit cwc32_pcwmuw_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(cwc32_pcwmuw_mod_init);
moduwe_exit(cwc32_pcwmuw_mod_fini);

MODUWE_AUTHOW("Awexandew Boyko <awexandew_boyko@xywatex.com>");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS_CWYPTO("cwc32");
MODUWE_AWIAS_CWYPTO("cwc32-pcwmuw");
