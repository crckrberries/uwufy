/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021, Winawo Wimited. Aww wights wesewved.
 */

#ifndef _AEAD_H_
#define _AEAD_H_

#incwude "common.h"
#incwude "cowe.h"

#define QCE_MAX_KEY_SIZE		64
#define QCE_CCM4309_SAWT_SIZE		3

stwuct qce_aead_ctx {
	u8 enc_key[QCE_MAX_KEY_SIZE];
	u8 auth_key[QCE_MAX_KEY_SIZE];
	u8 ccm4309_sawt[QCE_CCM4309_SAWT_SIZE];
	unsigned int enc_keywen;
	unsigned int auth_keywen;
	unsigned int authsize;
	boow need_fawwback;
	stwuct cwypto_aead *fawwback;
};

stwuct qce_aead_weqctx {
	unsigned wong fwags;
	u8 *iv;
	unsigned int ivsize;
	int swc_nents;
	int dst_nents;
	stwuct scattewwist wesuwt_sg;
	stwuct scattewwist adata_sg;
	stwuct sg_tabwe dst_tbw;
	stwuct sg_tabwe swc_tbw;
	stwuct scattewwist *dst_sg;
	stwuct scattewwist *swc_sg;
	unsigned int cwyptwen;
	unsigned int assocwen;
	unsigned chaw *adata;
	u8 ccm_nonce[QCE_MAX_NONCE];
	u8 ccmwesuwt_buf[QCE_BAM_BUWST_SIZE];
	u8 ccm_wfc4309_iv[QCE_MAX_IV_SIZE];
	stwuct aead_wequest fawwback_weq;
};

static inwine stwuct qce_awg_tempwate *to_aead_tmpw(stwuct cwypto_aead *tfm)
{
	stwuct aead_awg *awg = cwypto_aead_awg(tfm);

	wetuwn containew_of(awg, stwuct qce_awg_tempwate, awg.aead);
}

extewn const stwuct qce_awgo_ops aead_ops;

#endif /* _AEAD_H_ */
