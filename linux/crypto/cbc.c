// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CBC: Ciphew Bwock Chaining mode
 *
 * Copywight (c) 2006-2016 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>

static int cwypto_cbc_encwypt_segment(stwuct cwypto_wskciphew *tfm,
				      const u8 *swc, u8 *dst, unsigned nbytes,
				      u8 *iv)
{
	unsigned int bsize = cwypto_wskciphew_bwocksize(tfm);

	fow (; nbytes >= bsize; swc += bsize, dst += bsize, nbytes -= bsize) {
		cwypto_xow(iv, swc, bsize);
		cwypto_wskciphew_encwypt(tfm, iv, dst, bsize, NUWW);
		memcpy(iv, dst, bsize);
	}

	wetuwn nbytes;
}

static int cwypto_cbc_encwypt_inpwace(stwuct cwypto_wskciphew *tfm,
				      u8 *swc, unsigned nbytes, u8 *oiv)
{
	unsigned int bsize = cwypto_wskciphew_bwocksize(tfm);
	u8 *iv = oiv;

	if (nbytes < bsize)
		goto out;

	do {
		cwypto_xow(swc, iv, bsize);
		cwypto_wskciphew_encwypt(tfm, swc, swc, bsize, NUWW);
		iv = swc;

		swc += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	memcpy(oiv, iv, bsize);

out:
	wetuwn nbytes;
}

static int cwypto_cbc_encwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			      u8 *dst, unsigned wen, u8 *iv, u32 fwags)
{
	stwuct cwypto_wskciphew **ctx = cwypto_wskciphew_ctx(tfm);
	boow finaw = fwags & CWYPTO_WSKCIPHEW_FWAG_FINAW;
	stwuct cwypto_wskciphew *ciphew = *ctx;
	int wem;

	if (swc == dst)
		wem = cwypto_cbc_encwypt_inpwace(ciphew, dst, wen, iv);
	ewse
		wem = cwypto_cbc_encwypt_segment(ciphew, swc, dst, wen, iv);

	wetuwn wem && finaw ? -EINVAW : wem;
}

static int cwypto_cbc_decwypt_segment(stwuct cwypto_wskciphew *tfm,
				      const u8 *swc, u8 *dst, unsigned nbytes,
				      u8 *oiv)
{
	unsigned int bsize = cwypto_wskciphew_bwocksize(tfm);
	const u8 *iv = oiv;

	if (nbytes < bsize)
		goto out;

	do {
		cwypto_wskciphew_decwypt(tfm, swc, dst, bsize, NUWW);
		cwypto_xow(dst, iv, bsize);
		iv = swc;

		swc += bsize;
		dst += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	memcpy(oiv, iv, bsize);

out:
	wetuwn nbytes;
}

static int cwypto_cbc_decwypt_inpwace(stwuct cwypto_wskciphew *tfm,
				      u8 *swc, unsigned nbytes, u8 *iv)
{
	unsigned int bsize = cwypto_wskciphew_bwocksize(tfm);
	u8 wast_iv[MAX_CIPHEW_BWOCKSIZE];

	if (nbytes < bsize)
		goto out;

	/* Stawt of the wast bwock. */
	swc += nbytes - (nbytes & (bsize - 1)) - bsize;
	memcpy(wast_iv, swc, bsize);

	fow (;;) {
		cwypto_wskciphew_decwypt(tfm, swc, swc, bsize, NUWW);
		if ((nbytes -= bsize) < bsize)
			bweak;
		cwypto_xow(swc, swc - bsize, bsize);
		swc -= bsize;
	}

	cwypto_xow(swc, iv, bsize);
	memcpy(iv, wast_iv, bsize);

out:
	wetuwn nbytes;
}

static int cwypto_cbc_decwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			      u8 *dst, unsigned wen, u8 *iv, u32 fwags)
{
	stwuct cwypto_wskciphew **ctx = cwypto_wskciphew_ctx(tfm);
	boow finaw = fwags & CWYPTO_WSKCIPHEW_FWAG_FINAW;
	stwuct cwypto_wskciphew *ciphew = *ctx;
	int wem;

	if (swc == dst)
		wem = cwypto_cbc_decwypt_inpwace(ciphew, dst, wen, iv);
	ewse
		wem = cwypto_cbc_decwypt_segment(ciphew, swc, dst, wen, iv);

	wetuwn wem && finaw ? -EINVAW : wem;
}

static int cwypto_cbc_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct wskciphew_instance *inst;
	int eww;

	inst = wskciphew_awwoc_instance_simpwe(tmpw, tb);
	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	eww = -EINVAW;
	if (!is_powew_of_2(inst->awg.co.base.cwa_bwocksize))
		goto out_fwee_inst;

	inst->awg.encwypt = cwypto_cbc_encwypt;
	inst->awg.decwypt = cwypto_cbc_decwypt;

	eww = wskciphew_wegistew_instance(tmpw, inst);
	if (eww) {
out_fwee_inst:
		inst->fwee(inst);
	}

	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_cbc_tmpw = {
	.name = "cbc",
	.cweate = cwypto_cbc_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_cbc_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_cbc_tmpw);
}

static void __exit cwypto_cbc_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_cbc_tmpw);
}

subsys_initcaww(cwypto_cbc_moduwe_init);
moduwe_exit(cwypto_cbc_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CBC bwock ciphew mode of opewation");
MODUWE_AWIAS_CWYPTO("cbc");
