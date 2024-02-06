/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _CIPHEW_H_
#define _CIPHEW_H_

#incwude "common.h"
#incwude "cowe.h"

#define QCE_MAX_KEY_SIZE	64

stwuct qce_ciphew_ctx {
	u8 enc_key[QCE_MAX_KEY_SIZE];
	unsigned int enc_keywen;
	stwuct cwypto_skciphew *fawwback;
};

/**
 * stwuct qce_ciphew_weqctx - howds pwivate ciphew objects pew wequest
 * @fwags: opewation fwags
 * @iv: pointew to the IV
 * @ivsize: IV size
 * @swc_nents: souwce entwies
 * @dst_nents: destination entwies
 * @wesuwt_sg: scattewwist used fow wesuwt buffew
 * @dst_tbw: destination sg tabwe
 * @dst_sg: destination sg pointew tabwe beginning
 * @swc_tbw: souwce sg tabwe
 * @swc_sg: souwce sg pointew tabwe beginning;
 * @cwyptwen: cwypto wength
 */
stwuct qce_ciphew_weqctx {
	unsigned wong fwags;
	u8 *iv;
	unsigned int ivsize;
	int swc_nents;
	int dst_nents;
	stwuct scattewwist wesuwt_sg;
	stwuct sg_tabwe dst_tbw;
	stwuct scattewwist *dst_sg;
	stwuct scattewwist *swc_sg;
	unsigned int cwyptwen;
	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

static inwine stwuct qce_awg_tempwate *to_ciphew_tmpw(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	wetuwn containew_of(awg, stwuct qce_awg_tempwate, awg.skciphew);
}

extewn const stwuct qce_awgo_ops skciphew_ops;

#endif /* _CIPHEW_H_ */
