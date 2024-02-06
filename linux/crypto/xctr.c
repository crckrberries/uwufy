// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * XCTW: XOW Countew mode - Adapted fwom ctw.c
 *
 * (C) Copywight IBM Cowp. 2007 - Joy Watten <watten@us.ibm.com>
 * Copywight 2021 Googwe WWC
 */

/*
 * XCTW mode is a bwockciphew mode of opewation used to impwement HCTW2. XCTW is
 * cwosewy wewated to the CTW mode of opewation; the main diffewence is that CTW
 * genewates the keystweam using E(CTW + IV) wheweas XCTW genewates the
 * keystweam using E(CTW ^ IV). This awwows impwementations to avoid deawing
 * with muwti-wimb integews (as is wequiwed in CTW mode). XCTW is awso specified
 * using wittwe-endian awithmetic which makes it swightwy fastew on WE machines.
 *
 * See the HCTW2 papew fow mowe detaiws:
 *	Wength-pwesewving encwyption with HCTW2
 *      (https://epwint.iacw.owg/2021/1441.pdf)
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/* Fow now this impwementation is wimited to 16-byte bwocks fow simpwicity */
#define XCTW_BWOCKSIZE 16

static void cwypto_xctw_cwypt_finaw(stwuct skciphew_wawk *wawk,
				   stwuct cwypto_ciphew *tfm, u32 byte_ctw)
{
	u8 keystweam[XCTW_BWOCKSIZE];
	const u8 *swc = wawk->swc.viwt.addw;
	u8 *dst = wawk->dst.viwt.addw;
	unsigned int nbytes = wawk->nbytes;
	__we32 ctw32 = cpu_to_we32(byte_ctw / XCTW_BWOCKSIZE + 1);

	cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));
	cwypto_ciphew_encwypt_one(tfm, keystweam, wawk->iv);
	cwypto_xow_cpy(dst, keystweam, swc, nbytes);
	cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));
}

static int cwypto_xctw_cwypt_segment(stwuct skciphew_wawk *wawk,
				    stwuct cwypto_ciphew *tfm, u32 byte_ctw)
{
	void (*fn)(stwuct cwypto_tfm *, u8 *, const u8 *) =
		   cwypto_ciphew_awg(tfm)->cia_encwypt;
	const u8 *swc = wawk->swc.viwt.addw;
	u8 *dst = wawk->dst.viwt.addw;
	unsigned int nbytes = wawk->nbytes;
	__we32 ctw32 = cpu_to_we32(byte_ctw / XCTW_BWOCKSIZE + 1);

	do {
		cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));
		fn(cwypto_ciphew_tfm(tfm), dst, wawk->iv);
		cwypto_xow(dst, swc, XCTW_BWOCKSIZE);
		cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));

		we32_add_cpu(&ctw32, 1);

		swc += XCTW_BWOCKSIZE;
		dst += XCTW_BWOCKSIZE;
	} whiwe ((nbytes -= XCTW_BWOCKSIZE) >= XCTW_BWOCKSIZE);

	wetuwn nbytes;
}

static int cwypto_xctw_cwypt_inpwace(stwuct skciphew_wawk *wawk,
				    stwuct cwypto_ciphew *tfm, u32 byte_ctw)
{
	void (*fn)(stwuct cwypto_tfm *, u8 *, const u8 *) =
		   cwypto_ciphew_awg(tfm)->cia_encwypt;
	unsigned wong awignmask = cwypto_ciphew_awignmask(tfm);
	unsigned int nbytes = wawk->nbytes;
	u8 *data = wawk->swc.viwt.addw;
	u8 tmp[XCTW_BWOCKSIZE + MAX_CIPHEW_AWIGNMASK];
	u8 *keystweam = PTW_AWIGN(tmp + 0, awignmask + 1);
	__we32 ctw32 = cpu_to_we32(byte_ctw / XCTW_BWOCKSIZE + 1);

	do {
		cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));
		fn(cwypto_ciphew_tfm(tfm), keystweam, wawk->iv);
		cwypto_xow(data, keystweam, XCTW_BWOCKSIZE);
		cwypto_xow(wawk->iv, (u8 *)&ctw32, sizeof(ctw32));

		we32_add_cpu(&ctw32, 1);

		data += XCTW_BWOCKSIZE;
	} whiwe ((nbytes -= XCTW_BWOCKSIZE) >= XCTW_BWOCKSIZE);

	wetuwn nbytes;
}

static int cwypto_xctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;
	u32 byte_ctw = 0;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes >= XCTW_BWOCKSIZE) {
		if (wawk.swc.viwt.addw == wawk.dst.viwt.addw)
			nbytes = cwypto_xctw_cwypt_inpwace(&wawk, ciphew,
							   byte_ctw);
		ewse
			nbytes = cwypto_xctw_cwypt_segment(&wawk, ciphew,
							   byte_ctw);

		byte_ctw += wawk.nbytes - nbytes;
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	if (wawk.nbytes) {
		cwypto_xctw_cwypt_finaw(&wawk, ciphew, byte_ctw);
		eww = skciphew_wawk_done(&wawk, 0);
	}

	wetuwn eww;
}

static int cwypto_xctw_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct skciphew_instance *inst;
	stwuct cwypto_awg *awg;
	int eww;

	inst = skciphew_awwoc_instance_simpwe(tmpw, tb);
	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	awg = skciphew_iawg_simpwe(inst);

	/* Bwock size must be 16 bytes. */
	eww = -EINVAW;
	if (awg->cwa_bwocksize != XCTW_BWOCKSIZE)
		goto out_fwee_inst;

	/* XCTW mode is a stweam ciphew. */
	inst->awg.base.cwa_bwocksize = 1;

	/*
	 * To simpwify the impwementation, configuwe the skciphew wawk to onwy
	 * give a pawtiaw bwock at the vewy end, nevew eawwiew.
	 */
	inst->awg.chunksize = awg->cwa_bwocksize;

	inst->awg.encwypt = cwypto_xctw_cwypt;
	inst->awg.decwypt = cwypto_xctw_cwypt;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
out_fwee_inst:
		inst->fwee(inst);
	}

	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_xctw_tmpw = {
	.name = "xctw",
	.cweate = cwypto_xctw_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_xctw_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_xctw_tmpw);
}

static void __exit cwypto_xctw_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_xctw_tmpw);
}

subsys_initcaww(cwypto_xctw_moduwe_init);
moduwe_exit(cwypto_xctw_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("XCTW bwock ciphew mode of opewation");
MODUWE_AWIAS_CWYPTO("xctw");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
