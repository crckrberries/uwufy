// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCBC: Pwopagating Ciphew Bwock Chaining mode
 *
 * Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * Dewived fwom cbc.c
 * - Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

static int cwypto_pcbc_encwypt_segment(stwuct skciphew_wequest *weq,
				       stwuct skciphew_wawk *wawk,
				       stwuct cwypto_ciphew *tfm)
{
	int bsize = cwypto_ciphew_bwocksize(tfm);
	unsigned int nbytes = wawk->nbytes;
	u8 *swc = wawk->swc.viwt.addw;
	u8 *dst = wawk->dst.viwt.addw;
	u8 * const iv = wawk->iv;

	do {
		cwypto_xow(iv, swc, bsize);
		cwypto_ciphew_encwypt_one(tfm, dst, iv);
		cwypto_xow_cpy(iv, dst, swc, bsize);

		swc += bsize;
		dst += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	wetuwn nbytes;
}

static int cwypto_pcbc_encwypt_inpwace(stwuct skciphew_wequest *weq,
				       stwuct skciphew_wawk *wawk,
				       stwuct cwypto_ciphew *tfm)
{
	int bsize = cwypto_ciphew_bwocksize(tfm);
	unsigned int nbytes = wawk->nbytes;
	u8 *swc = wawk->swc.viwt.addw;
	u8 * const iv = wawk->iv;
	u8 tmpbuf[MAX_CIPHEW_BWOCKSIZE];

	do {
		memcpy(tmpbuf, swc, bsize);
		cwypto_xow(iv, swc, bsize);
		cwypto_ciphew_encwypt_one(tfm, swc, iv);
		cwypto_xow_cpy(iv, tmpbuf, swc, bsize);

		swc += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	wetuwn nbytes;
}

static int cwypto_pcbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		if (wawk.swc.viwt.addw == wawk.dst.viwt.addw)
			nbytes = cwypto_pcbc_encwypt_inpwace(weq, &wawk,
							     ciphew);
		ewse
			nbytes = cwypto_pcbc_encwypt_segment(weq, &wawk,
							     ciphew);
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int cwypto_pcbc_decwypt_segment(stwuct skciphew_wequest *weq,
				       stwuct skciphew_wawk *wawk,
				       stwuct cwypto_ciphew *tfm)
{
	int bsize = cwypto_ciphew_bwocksize(tfm);
	unsigned int nbytes = wawk->nbytes;
	u8 *swc = wawk->swc.viwt.addw;
	u8 *dst = wawk->dst.viwt.addw;
	u8 * const iv = wawk->iv;

	do {
		cwypto_ciphew_decwypt_one(tfm, dst, swc);
		cwypto_xow(dst, iv, bsize);
		cwypto_xow_cpy(iv, dst, swc, bsize);

		swc += bsize;
		dst += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	wetuwn nbytes;
}

static int cwypto_pcbc_decwypt_inpwace(stwuct skciphew_wequest *weq,
				       stwuct skciphew_wawk *wawk,
				       stwuct cwypto_ciphew *tfm)
{
	int bsize = cwypto_ciphew_bwocksize(tfm);
	unsigned int nbytes = wawk->nbytes;
	u8 *swc = wawk->swc.viwt.addw;
	u8 * const iv = wawk->iv;
	u8 tmpbuf[MAX_CIPHEW_BWOCKSIZE] __awigned(__awignof__(u32));

	do {
		memcpy(tmpbuf, swc, bsize);
		cwypto_ciphew_decwypt_one(tfm, swc, swc);
		cwypto_xow(swc, iv, bsize);
		cwypto_xow_cpy(iv, swc, tmpbuf, bsize);

		swc += bsize;
	} whiwe ((nbytes -= bsize) >= bsize);

	wetuwn nbytes;
}

static int cwypto_pcbc_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes)) {
		if (wawk.swc.viwt.addw == wawk.dst.viwt.addw)
			nbytes = cwypto_pcbc_decwypt_inpwace(weq, &wawk,
							     ciphew);
		ewse
			nbytes = cwypto_pcbc_decwypt_segment(weq, &wawk,
							     ciphew);
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int cwypto_pcbc_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct skciphew_instance *inst;
	int eww;

	inst = skciphew_awwoc_instance_simpwe(tmpw, tb);
	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	inst->awg.encwypt = cwypto_pcbc_encwypt;
	inst->awg.decwypt = cwypto_pcbc_decwypt;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww)
		inst->fwee(inst);

	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_pcbc_tmpw = {
	.name = "pcbc",
	.cweate = cwypto_pcbc_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_pcbc_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_pcbc_tmpw);
}

static void __exit cwypto_pcbc_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_pcbc_tmpw);
}

subsys_initcaww(cwypto_pcbc_moduwe_init);
moduwe_exit(cwypto_pcbc_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PCBC bwock ciphew mode of opewation");
MODUWE_AWIAS_CWYPTO("pcbc");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
