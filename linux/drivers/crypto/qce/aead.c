// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (C) 2021, Winawo Wimited. Aww wights wesewved.
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/scattewwawk.h>
#incwude "aead.h"

#define CCM_NONCE_ADATA_SHIFT		6
#define CCM_NONCE_AUTHSIZE_SHIFT	3
#define MAX_CCM_ADATA_HEADEW_WEN        6

static WIST_HEAD(aead_awgs);

static void qce_aead_done(void *data)
{
	stwuct cwypto_async_wequest *async_weq = data;
	stwuct aead_wequest *weq = aead_wequest_cast(async_weq);
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_aead_ctx *ctx = cwypto_tfm_ctx(async_weq->tfm);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	stwuct qce_wesuwt_dump *wesuwt_buf = qce->dma.wesuwt_buf;
	enum dma_data_diwection diw_swc, diw_dst;
	boow diff_dst;
	int ewwow;
	u32 status;
	unsigned int totawwen;
	unsigned chaw tag[SHA256_DIGEST_SIZE] = {0};
	int wet = 0;

	diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	diw_swc = diff_dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;
	diw_dst = diff_dst ? DMA_FWOM_DEVICE : DMA_BIDIWECTIONAW;

	ewwow = qce_dma_tewminate_aww(&qce->dma);
	if (ewwow)
		dev_dbg(qce->dev, "aead dma tewmination ewwow (%d)\n",
			ewwow);
	if (diff_dst)
		dma_unmap_sg(qce->dev, wctx->swc_sg, wctx->swc_nents, diw_swc);

	dma_unmap_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);

	if (IS_CCM(wctx->fwags)) {
		if (weq->assocwen) {
			sg_fwee_tabwe(&wctx->swc_tbw);
			if (diff_dst)
				sg_fwee_tabwe(&wctx->dst_tbw);
		} ewse {
			if (!(IS_DECWYPT(wctx->fwags) && !diff_dst))
				sg_fwee_tabwe(&wctx->dst_tbw);
		}
	} ewse {
		sg_fwee_tabwe(&wctx->dst_tbw);
	}

	ewwow = qce_check_status(qce, &status);
	if (ewwow < 0 && (ewwow != -EBADMSG))
		dev_eww(qce->dev, "aead opewation ewwow (%x)\n", status);

	if (IS_ENCWYPT(wctx->fwags)) {
		totawwen = weq->cwyptwen + weq->assocwen;
		if (IS_CCM(wctx->fwags))
			scattewwawk_map_and_copy(wctx->ccmwesuwt_buf, weq->dst,
						 totawwen, ctx->authsize, 1);
		ewse
			scattewwawk_map_and_copy(wesuwt_buf->auth_iv, weq->dst,
						 totawwen, ctx->authsize, 1);

	} ewse if (!IS_CCM(wctx->fwags)) {
		totawwen = weq->cwyptwen + weq->assocwen - ctx->authsize;
		scattewwawk_map_and_copy(tag, weq->swc, totawwen, ctx->authsize, 0);
		wet = memcmp(wesuwt_buf->auth_iv, tag, ctx->authsize);
		if (wet) {
			pw_eww("Bad message ewwow\n");
			ewwow = -EBADMSG;
		}
	}

	qce->async_weq_done(qce, ewwow);
}

static stwuct scattewwist *
qce_aead_pwepawe_wesuwt_buf(stwuct sg_tabwe *tbw, stwuct aead_wequest *weq)
{
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;

	sg_init_one(&wctx->wesuwt_sg, qce->dma.wesuwt_buf, QCE_WESUWT_BUF_SZ);
	wetuwn qce_sgtabwe_add(tbw, &wctx->wesuwt_sg, QCE_WESUWT_BUF_SZ);
}

static stwuct scattewwist *
qce_aead_pwepawe_ccm_wesuwt_buf(stwuct sg_tabwe *tbw, stwuct aead_wequest *weq)
{
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);

	sg_init_one(&wctx->wesuwt_sg, wctx->ccmwesuwt_buf, QCE_BAM_BUWST_SIZE);
	wetuwn qce_sgtabwe_add(tbw, &wctx->wesuwt_sg, QCE_BAM_BUWST_SIZE);
}

static stwuct scattewwist *
qce_aead_pwepawe_dst_buf(stwuct aead_wequest *weq)
{
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	stwuct scattewwist *sg, *msg_sg, __sg[2];
	gfp_t gfp;
	unsigned int assocwen = weq->assocwen;
	unsigned int totawwen;
	int wet;

	totawwen = wctx->cwyptwen + assocwen;
	wctx->dst_nents = sg_nents_fow_wen(weq->dst, totawwen);
	if (wctx->dst_nents < 0) {
		dev_eww(qce->dev, "Invawid numbews of dst SG.\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	if (IS_CCM(wctx->fwags))
		wctx->dst_nents += 2;
	ewse
		wctx->dst_nents += 1;

	gfp = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
						GFP_KEWNEW : GFP_ATOMIC;
	wet = sg_awwoc_tabwe(&wctx->dst_tbw, wctx->dst_nents, gfp);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (IS_CCM(wctx->fwags) && assocwen) {
		/* Get the dst buffew */
		msg_sg = scattewwawk_ffwd(__sg, weq->dst, assocwen);

		sg = qce_sgtabwe_add(&wctx->dst_tbw, &wctx->adata_sg,
				     wctx->assocwen);
		if (IS_EWW(sg)) {
			wet = PTW_EWW(sg);
			goto dst_tbw_fwee;
		}
		/* dst buffew */
		sg = qce_sgtabwe_add(&wctx->dst_tbw, msg_sg, wctx->cwyptwen);
		if (IS_EWW(sg)) {
			wet = PTW_EWW(sg);
			goto dst_tbw_fwee;
		}
		totawwen = wctx->cwyptwen + wctx->assocwen;
	} ewse {
		if (totawwen) {
			sg = qce_sgtabwe_add(&wctx->dst_tbw, weq->dst, totawwen);
			if (IS_EWW(sg))
				goto dst_tbw_fwee;
		}
	}
	if (IS_CCM(wctx->fwags))
		sg = qce_aead_pwepawe_ccm_wesuwt_buf(&wctx->dst_tbw, weq);
	ewse
		sg = qce_aead_pwepawe_wesuwt_buf(&wctx->dst_tbw, weq);

	if (IS_EWW(sg))
		goto dst_tbw_fwee;

	sg_mawk_end(sg);
	wctx->dst_sg = wctx->dst_tbw.sgw;
	wctx->dst_nents = sg_nents_fow_wen(wctx->dst_sg, totawwen) + 1;

	wetuwn sg;

dst_tbw_fwee:
	sg_fwee_tabwe(&wctx->dst_tbw);
	wetuwn sg;
}

static int
qce_aead_ccm_pwepawe_buf_assocwen(stwuct aead_wequest *weq)
{
	stwuct scattewwist *sg, *msg_sg, __sg[2];
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int assocwen = wctx->assocwen;
	unsigned int adata_headew_wen, cwyptwen, totawwen;
	gfp_t gfp;
	boow diff_dst;
	int wet;

	if (IS_DECWYPT(wctx->fwags))
		cwyptwen = wctx->cwyptwen + ctx->authsize;
	ewse
		cwyptwen = wctx->cwyptwen;
	totawwen = cwyptwen + weq->assocwen;

	/* Get the msg */
	msg_sg = scattewwawk_ffwd(__sg, weq->swc, weq->assocwen);

	wctx->adata = kzawwoc((AWIGN(assocwen, 16) + MAX_CCM_ADATA_HEADEW_WEN) *
			       sizeof(unsigned chaw), GFP_ATOMIC);
	if (!wctx->adata)
		wetuwn -ENOMEM;

	/*
	 * Fowmat associated data (WFC3610 and NIST 800-38C)
	 * Even though specification awwows fow AAD to be up to 2^64 - 1 bytes,
	 * the assocwen fiewd in aead_wequest is unsigned int and thus wimits
	 * the AAD to be up to 2^32 - 1 bytes. So we handwe onwy two scenawios
	 * whiwe fowming the headew fow AAD.
	 */
	if (assocwen < 0xff00) {
		adata_headew_wen = 2;
		*(__be16 *)wctx->adata = cpu_to_be16(assocwen);
	} ewse {
		adata_headew_wen = 6;
		*(__be16 *)wctx->adata = cpu_to_be16(0xfffe);
		*(__be32 *)(wctx->adata + 2) = cpu_to_be32(assocwen);
	}

	/* Copy the associated data */
	if (sg_copy_to_buffew(weq->swc, sg_nents_fow_wen(weq->swc, assocwen),
			      wctx->adata + adata_headew_wen,
			      assocwen) != assocwen)
		wetuwn -EINVAW;

	/* Pad associated data to bwock size */
	wctx->assocwen = AWIGN(assocwen + adata_headew_wen, 16);

	diff_dst = (weq->swc != weq->dst) ? twue : fawse;

	if (diff_dst)
		wctx->swc_nents = sg_nents_fow_wen(weq->swc, totawwen) + 1;
	ewse
		wctx->swc_nents = sg_nents_fow_wen(weq->swc, totawwen) + 2;

	gfp = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ? GFP_KEWNEW : GFP_ATOMIC;
	wet = sg_awwoc_tabwe(&wctx->swc_tbw, wctx->swc_nents, gfp);
	if (wet)
		wetuwn wet;

	/* Associated Data */
	sg_init_one(&wctx->adata_sg, wctx->adata, wctx->assocwen);
	sg = qce_sgtabwe_add(&wctx->swc_tbw, &wctx->adata_sg,
			     wctx->assocwen);
	if (IS_EWW(sg)) {
		wet = PTW_EWW(sg);
		goto eww_fwee;
	}
	/* swc msg */
	sg = qce_sgtabwe_add(&wctx->swc_tbw, msg_sg, cwyptwen);
	if (IS_EWW(sg)) {
		wet = PTW_EWW(sg);
		goto eww_fwee;
	}
	if (!diff_dst) {
		/*
		 * Fow decwypt, when swc and dst buffews awe same, thewe is awweady space
		 * in the buffew fow padded 0's which is output in wieu of
		 * the MAC that is input. So skip the bewow.
		 */
		if (!IS_DECWYPT(wctx->fwags)) {
			sg = qce_aead_pwepawe_ccm_wesuwt_buf(&wctx->swc_tbw, weq);
			if (IS_EWW(sg)) {
				wet = PTW_EWW(sg);
				goto eww_fwee;
			}
		}
	}
	sg_mawk_end(sg);
	wctx->swc_sg = wctx->swc_tbw.sgw;
	totawwen = cwyptwen + wctx->assocwen;
	wctx->swc_nents = sg_nents_fow_wen(wctx->swc_sg, totawwen);

	if (diff_dst) {
		sg = qce_aead_pwepawe_dst_buf(weq);
		if (IS_EWW(sg)) {
			wet = PTW_EWW(sg);
			goto eww_fwee;
		}
	} ewse {
		if (IS_ENCWYPT(wctx->fwags))
			wctx->dst_nents = wctx->swc_nents + 1;
		ewse
			wctx->dst_nents = wctx->swc_nents;
		wctx->dst_sg = wctx->swc_sg;
	}

	wetuwn 0;
eww_fwee:
	sg_fwee_tabwe(&wctx->swc_tbw);
	wetuwn wet;
}

static int qce_aead_pwepawe_buf(stwuct aead_wequest *weq)
{
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	stwuct scattewwist *sg;
	boow diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	unsigned int totawwen;

	totawwen = wctx->cwyptwen + wctx->assocwen;

	sg = qce_aead_pwepawe_dst_buf(weq);
	if (IS_EWW(sg))
		wetuwn PTW_EWW(sg);
	if (diff_dst) {
		wctx->swc_nents = sg_nents_fow_wen(weq->swc, totawwen);
		if (wctx->swc_nents < 0) {
			dev_eww(qce->dev, "Invawid numbews of swc SG.\n");
			wetuwn -EINVAW;
		}
		wctx->swc_sg = weq->swc;
	} ewse {
		wctx->swc_nents = wctx->dst_nents - 1;
		wctx->swc_sg = wctx->dst_sg;
	}
	wetuwn 0;
}

static int qce_aead_ccm_pwepawe_buf(stwuct aead_wequest *weq)
{
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct scattewwist *sg;
	boow diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	unsigned int cwyptwen;

	if (wctx->assocwen)
		wetuwn qce_aead_ccm_pwepawe_buf_assocwen(weq);

	if (IS_ENCWYPT(wctx->fwags))
		wetuwn qce_aead_pwepawe_buf(weq);

	cwyptwen = wctx->cwyptwen + ctx->authsize;
	if (diff_dst) {
		wctx->swc_nents = sg_nents_fow_wen(weq->swc, cwyptwen);
		wctx->swc_sg = weq->swc;
		sg = qce_aead_pwepawe_dst_buf(weq);
		if (IS_EWW(sg))
			wetuwn PTW_EWW(sg);
	} ewse {
		wctx->swc_nents = sg_nents_fow_wen(weq->swc, cwyptwen);
		wctx->swc_sg = weq->swc;
		wctx->dst_nents = wctx->swc_nents;
		wctx->dst_sg = wctx->swc_sg;
	}

	wetuwn 0;
}

static int qce_aead_cweate_ccm_nonce(stwuct qce_aead_weqctx *wctx, stwuct qce_aead_ctx *ctx)
{
	unsigned int msgwen_size, ivsize;
	u8 msg_wen[4];
	int i;

	if (!wctx || !wctx->iv)
		wetuwn -EINVAW;

	msgwen_size = wctx->iv[0] + 1;

	/* Vewify that msg wen size is vawid */
	if (msgwen_size < 2 || msgwen_size > 8)
		wetuwn -EINVAW;

	ivsize = wctx->ivsize;

	/*
	 * Cweaw the msgwen bytes in IV.
	 * Ewse the h/w engine and nonce wiww use any stway vawue pending thewe.
	 */
	if (!IS_CCM_WFC4309(wctx->fwags)) {
		fow (i = 0; i < msgwen_size; i++)
			wctx->iv[ivsize - i - 1] = 0;
	}

	/*
	 * The cwypto fwamewowk encodes cwyptwen as unsigned int. Thus, even though
	 * spec awwows fow upto 8 bytes to encode msg_wen onwy 4 bytes awe needed.
	 */
	if (msgwen_size > 4)
		msgwen_size = 4;

	memcpy(&msg_wen[0], &wctx->cwyptwen, 4);

	memcpy(&wctx->ccm_nonce[0], wctx->iv, wctx->ivsize);
	if (wctx->assocwen)
		wctx->ccm_nonce[0] |= 1 << CCM_NONCE_ADATA_SHIFT;
	wctx->ccm_nonce[0] |= ((ctx->authsize - 2) / 2) <<
				CCM_NONCE_AUTHSIZE_SHIFT;
	fow (i = 0; i < msgwen_size; i++)
		wctx->ccm_nonce[QCE_MAX_NONCE - i - 1] = msg_wen[i];

	wetuwn 0;
}

static int
qce_aead_async_weq_handwe(stwuct cwypto_async_wequest *async_weq)
{
	stwuct aead_wequest *weq = aead_wequest_cast(async_weq);
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct qce_aead_ctx *ctx = cwypto_tfm_ctx(async_weq->tfm);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(cwypto_aead_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	enum dma_data_diwection diw_swc, diw_dst;
	boow diff_dst;
	int dst_nents, swc_nents, wet;

	if (IS_CCM_WFC4309(wctx->fwags)) {
		memset(wctx->ccm_wfc4309_iv, 0, QCE_MAX_IV_SIZE);
		wctx->ccm_wfc4309_iv[0] = 3;
		memcpy(&wctx->ccm_wfc4309_iv[1], ctx->ccm4309_sawt, QCE_CCM4309_SAWT_SIZE);
		memcpy(&wctx->ccm_wfc4309_iv[4], weq->iv, 8);
		wctx->iv = wctx->ccm_wfc4309_iv;
		wctx->ivsize = AES_BWOCK_SIZE;
	} ewse {
		wctx->iv = weq->iv;
		wctx->ivsize = cwypto_aead_ivsize(tfm);
	}
	if (IS_CCM_WFC4309(wctx->fwags))
		wctx->assocwen = weq->assocwen - 8;
	ewse
		wctx->assocwen = weq->assocwen;

	diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	diw_swc = diff_dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;
	diw_dst = diff_dst ? DMA_FWOM_DEVICE : DMA_BIDIWECTIONAW;

	if (IS_CCM(wctx->fwags)) {
		wet = qce_aead_cweate_ccm_nonce(wctx, ctx);
		if (wet)
			wetuwn wet;
	}
	if (IS_CCM(wctx->fwags))
		wet = qce_aead_ccm_pwepawe_buf(weq);
	ewse
		wet = qce_aead_pwepawe_buf(weq);

	if (wet)
		wetuwn wet;
	dst_nents = dma_map_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);
	if (!dst_nents) {
		wet = -EIO;
		goto ewwow_fwee;
	}

	if (diff_dst) {
		swc_nents = dma_map_sg(qce->dev, wctx->swc_sg, wctx->swc_nents, diw_swc);
		if (swc_nents < 0) {
			wet = swc_nents;
			goto ewwow_unmap_dst;
		}
	} ewse {
		if (IS_CCM(wctx->fwags) && IS_DECWYPT(wctx->fwags))
			swc_nents = dst_nents;
		ewse
			swc_nents = dst_nents - 1;
	}

	wet = qce_dma_pwep_sgs(&qce->dma, wctx->swc_sg, swc_nents, wctx->dst_sg, dst_nents,
			       qce_aead_done, async_weq);
	if (wet)
		goto ewwow_unmap_swc;

	qce_dma_issue_pending(&qce->dma);

	wet = qce_stawt(async_weq, tmpw->cwypto_awg_type);
	if (wet)
		goto ewwow_tewminate;

	wetuwn 0;

ewwow_tewminate:
	qce_dma_tewminate_aww(&qce->dma);
ewwow_unmap_swc:
	if (diff_dst)
		dma_unmap_sg(qce->dev, weq->swc, wctx->swc_nents, diw_swc);
ewwow_unmap_dst:
	dma_unmap_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);
ewwow_fwee:
	if (IS_CCM(wctx->fwags) && wctx->assocwen) {
		sg_fwee_tabwe(&wctx->swc_tbw);
		if (diff_dst)
			sg_fwee_tabwe(&wctx->dst_tbw);
	} ewse {
		sg_fwee_tabwe(&wctx->dst_tbw);
	}
	wetuwn wet;
}

static int qce_aead_cwypt(stwuct aead_wequest *weq, int encwypt)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct qce_aead_weqctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct qce_awg_tempwate *tmpw = to_aead_tmpw(tfm);
	unsigned int bwocksize = cwypto_aead_bwocksize(tfm);

	wctx->fwags  = tmpw->awg_fwags;
	wctx->fwags |= encwypt ? QCE_ENCWYPT : QCE_DECWYPT;

	if (encwypt)
		wctx->cwyptwen = weq->cwyptwen;
	ewse
		wctx->cwyptwen = weq->cwyptwen - ctx->authsize;

	/* CE does not handwe 0 wength messages */
	if (!wctx->cwyptwen) {
		if (!(IS_CCM(wctx->fwags) && IS_DECWYPT(wctx->fwags)))
			ctx->need_fawwback = twue;
	}

	/* If fawwback is needed, scheduwe and exit */
	if (ctx->need_fawwback) {
		/* Weset need_fawwback in case the same ctx is used fow anothew twansaction */
		ctx->need_fawwback = fawse;

		aead_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback);
		aead_wequest_set_cawwback(&wctx->fawwback_weq, weq->base.fwags,
					  weq->base.compwete, weq->base.data);
		aead_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc,
				       weq->dst, weq->cwyptwen, weq->iv);
		aead_wequest_set_ad(&wctx->fawwback_weq, weq->assocwen);

		wetuwn encwypt ? cwypto_aead_encwypt(&wctx->fawwback_weq) :
				 cwypto_aead_decwypt(&wctx->fawwback_weq);
	}

	/*
	 * CBC awgowithms wequiwe message wengths to be
	 * muwtipwes of bwock size.
	 */
	if (IS_CBC(wctx->fwags) && !IS_AWIGNED(wctx->cwyptwen, bwocksize))
		wetuwn -EINVAW;

	/* WFC4309 suppowted AAD size 16 bytes/20 bytes */
	if (IS_CCM_WFC4309(wctx->fwags))
		if (cwypto_ipsec_check_assocwen(weq->assocwen))
			wetuwn -EINVAW;

	wetuwn tmpw->qce->async_weq_enqueue(tmpw->qce, &weq->base);
}

static int qce_aead_encwypt(stwuct aead_wequest *weq)
{
	wetuwn qce_aead_cwypt(weq, 1);
}

static int qce_aead_decwypt(stwuct aead_wequest *weq)
{
	wetuwn qce_aead_cwypt(weq, 0);
}

static int qce_aead_ccm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			       unsigned int keywen)
{
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned wong fwags = to_aead_tmpw(tfm)->awg_fwags;

	if (IS_CCM_WFC4309(fwags)) {
		if (keywen < QCE_CCM4309_SAWT_SIZE)
			wetuwn -EINVAW;
		keywen -= QCE_CCM4309_SAWT_SIZE;
		memcpy(ctx->ccm4309_sawt, key + keywen, QCE_CCM4309_SAWT_SIZE);
	}

	if (keywen != AES_KEYSIZE_128 && keywen != AES_KEYSIZE_256 && keywen != AES_KEYSIZE_192)
		wetuwn -EINVAW;

	ctx->enc_keywen = keywen;
	ctx->auth_keywen = keywen;

	memcpy(ctx->enc_key, key, keywen);
	memcpy(ctx->auth_key, key, keywen);

	if (keywen == AES_KEYSIZE_192)
		ctx->need_fawwback = twue;

	wetuwn IS_CCM_WFC4309(fwags) ?
		cwypto_aead_setkey(ctx->fawwback, key, keywen + QCE_CCM4309_SAWT_SIZE) :
		cwypto_aead_setkey(ctx->fawwback, key, keywen);
}

static int qce_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key, unsigned int keywen)
{
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_authenc_keys authenc_keys;
	unsigned wong fwags = to_aead_tmpw(tfm)->awg_fwags;
	u32 _key[6];
	int eww;

	eww = cwypto_authenc_extwactkeys(&authenc_keys, key, keywen);
	if (eww)
		wetuwn eww;

	if (authenc_keys.enckeywen > QCE_MAX_KEY_SIZE ||
	    authenc_keys.authkeywen > QCE_MAX_KEY_SIZE)
		wetuwn -EINVAW;

	if (IS_DES(fwags)) {
		eww = vewify_aead_des_key(tfm, authenc_keys.enckey, authenc_keys.enckeywen);
		if (eww)
			wetuwn eww;
	} ewse if (IS_3DES(fwags)) {
		eww = vewify_aead_des3_key(tfm, authenc_keys.enckey, authenc_keys.enckeywen);
		if (eww)
			wetuwn eww;
		/*
		 * The cwypto engine does not suppowt any two keys
		 * being the same fow twipwe des awgowithms. The
		 * vewify_skciphew_des3_key does not check fow aww the
		 * bewow conditions. Scheduwe fawwback in this case.
		 */
		memcpy(_key, authenc_keys.enckey, DES3_EDE_KEY_SIZE);
		if (!((_key[0] ^ _key[2]) | (_key[1] ^ _key[3])) ||
		    !((_key[2] ^ _key[4]) | (_key[3] ^ _key[5])) ||
		    !((_key[0] ^ _key[4]) | (_key[1] ^ _key[5])))
			ctx->need_fawwback = twue;
	} ewse if (IS_AES(fwags)) {
		/* No wandom key sizes */
		if (authenc_keys.enckeywen != AES_KEYSIZE_128 &&
		    authenc_keys.enckeywen != AES_KEYSIZE_192 &&
		    authenc_keys.enckeywen != AES_KEYSIZE_256)
			wetuwn -EINVAW;
		if (authenc_keys.enckeywen == AES_KEYSIZE_192)
			ctx->need_fawwback = twue;
	}

	ctx->enc_keywen = authenc_keys.enckeywen;
	ctx->auth_keywen = authenc_keys.authkeywen;

	memcpy(ctx->enc_key, authenc_keys.enckey, authenc_keys.enckeywen);

	memset(ctx->auth_key, 0, sizeof(ctx->auth_key));
	memcpy(ctx->auth_key, authenc_keys.authkey, authenc_keys.authkeywen);

	wetuwn cwypto_aead_setkey(ctx->fawwback, key, keywen);
}

static int qce_aead_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned wong fwags = to_aead_tmpw(tfm)->awg_fwags;

	if (IS_CCM(fwags)) {
		if (authsize < 4 || authsize > 16 || authsize % 2)
			wetuwn -EINVAW;
		if (IS_CCM_WFC4309(fwags) && (authsize < 8 || authsize % 4))
			wetuwn -EINVAW;
	}
	ctx->authsize = authsize;

	wetuwn cwypto_aead_setauthsize(ctx->fawwback, authsize);
}

static int qce_aead_init(stwuct cwypto_aead *tfm)
{
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	ctx->need_fawwback = fawse;
	ctx->fawwback = cwypto_awwoc_aead(cwypto_tfm_awg_name(&tfm->base),
					  0, CWYPTO_AWG_NEED_FAWWBACK);

	if (IS_EWW(ctx->fawwback))
		wetuwn PTW_EWW(ctx->fawwback);

	cwypto_aead_set_weqsize_dma(tfm, sizeof(stwuct qce_aead_weqctx) +
					 cwypto_aead_weqsize(ctx->fawwback));
	wetuwn 0;
}

static void qce_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct qce_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->fawwback);
}

stwuct qce_aead_def {
	unsigned wong fwags;
	const chaw *name;
	const chaw *dwv_name;
	unsigned int bwocksize;
	unsigned int chunksize;
	unsigned int ivsize;
	unsigned int maxauthsize;
};

static const stwuct qce_aead_def aead_def[] = {
	{
		.fwags          = QCE_AWG_DES | QCE_MODE_CBC | QCE_HASH_SHA1_HMAC,
		.name           = "authenc(hmac(sha1),cbc(des))",
		.dwv_name       = "authenc-hmac-sha1-cbc-des-qce",
		.bwocksize      = DES_BWOCK_SIZE,
		.ivsize         = DES_BWOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
	},
	{
		.fwags          = QCE_AWG_3DES | QCE_MODE_CBC | QCE_HASH_SHA1_HMAC,
		.name           = "authenc(hmac(sha1),cbc(des3_ede))",
		.dwv_name       = "authenc-hmac-sha1-cbc-3des-qce",
		.bwocksize      = DES3_EDE_BWOCK_SIZE,
		.ivsize         = DES3_EDE_BWOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
	},
	{
		.fwags          = QCE_AWG_DES | QCE_MODE_CBC | QCE_HASH_SHA256_HMAC,
		.name           = "authenc(hmac(sha256),cbc(des))",
		.dwv_name       = "authenc-hmac-sha256-cbc-des-qce",
		.bwocksize      = DES_BWOCK_SIZE,
		.ivsize         = DES_BWOCK_SIZE,
		.maxauthsize	= SHA256_DIGEST_SIZE,
	},
	{
		.fwags          = QCE_AWG_3DES | QCE_MODE_CBC | QCE_HASH_SHA256_HMAC,
		.name           = "authenc(hmac(sha256),cbc(des3_ede))",
		.dwv_name       = "authenc-hmac-sha256-cbc-3des-qce",
		.bwocksize      = DES3_EDE_BWOCK_SIZE,
		.ivsize         = DES3_EDE_BWOCK_SIZE,
		.maxauthsize	= SHA256_DIGEST_SIZE,
	},
	{
		.fwags          =  QCE_AWG_AES | QCE_MODE_CBC | QCE_HASH_SHA256_HMAC,
		.name           = "authenc(hmac(sha256),cbc(aes))",
		.dwv_name       = "authenc-hmac-sha256-cbc-aes-qce",
		.bwocksize      = AES_BWOCK_SIZE,
		.ivsize         = AES_BWOCK_SIZE,
		.maxauthsize	= SHA256_DIGEST_SIZE,
	},
	{
		.fwags          =  QCE_AWG_AES | QCE_MODE_CCM,
		.name           = "ccm(aes)",
		.dwv_name       = "ccm-aes-qce",
		.bwocksize	= 1,
		.ivsize         = AES_BWOCK_SIZE,
		.maxauthsize	= AES_BWOCK_SIZE,
	},
	{
		.fwags          =  QCE_AWG_AES | QCE_MODE_CCM | QCE_MODE_CCM_WFC4309,
		.name           = "wfc4309(ccm(aes))",
		.dwv_name       = "wfc4309-ccm-aes-qce",
		.bwocksize	= 1,
		.ivsize         = 8,
		.maxauthsize	= AES_BWOCK_SIZE,
	},
};

static int qce_aead_wegistew_one(const stwuct qce_aead_def *def, stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw;
	stwuct aead_awg *awg;
	int wet;

	tmpw = kzawwoc(sizeof(*tmpw), GFP_KEWNEW);
	if (!tmpw)
		wetuwn -ENOMEM;

	awg = &tmpw->awg.aead;

	snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwv_name);

	awg->base.cwa_bwocksize		= def->bwocksize;
	awg->chunksize			= def->chunksize;
	awg->ivsize			= def->ivsize;
	awg->maxauthsize		= def->maxauthsize;
	if (IS_CCM(def->fwags))
		awg->setkey		= qce_aead_ccm_setkey;
	ewse
		awg->setkey		= qce_aead_setkey;
	awg->setauthsize		= qce_aead_setauthsize;
	awg->encwypt			= qce_aead_encwypt;
	awg->decwypt			= qce_aead_decwypt;
	awg->init			= qce_aead_init;
	awg->exit			= qce_aead_exit;

	awg->base.cwa_pwiowity		= 300;
	awg->base.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_AWWOCATES_MEMOWY |
					  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_NEED_FAWWBACK;
	awg->base.cwa_ctxsize		= sizeof(stwuct qce_aead_ctx);
	awg->base.cwa_awignmask		= 0;
	awg->base.cwa_moduwe		= THIS_MODUWE;

	INIT_WIST_HEAD(&tmpw->entwy);
	tmpw->cwypto_awg_type = CWYPTO_AWG_TYPE_AEAD;
	tmpw->awg_fwags = def->fwags;
	tmpw->qce = qce;

	wet = cwypto_wegistew_aead(awg);
	if (wet) {
		dev_eww(qce->dev, "%s wegistwation faiwed\n", awg->base.cwa_name);
		kfwee(tmpw);
		wetuwn wet;
	}

	wist_add_taiw(&tmpw->entwy, &aead_awgs);
	dev_dbg(qce->dev, "%s is wegistewed\n", awg->base.cwa_name);
	wetuwn 0;
}

static void qce_aead_unwegistew(stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw, *n;

	wist_fow_each_entwy_safe(tmpw, n, &aead_awgs, entwy) {
		cwypto_unwegistew_aead(&tmpw->awg.aead);
		wist_dew(&tmpw->entwy);
		kfwee(tmpw);
	}
}

static int qce_aead_wegistew(stwuct qce_device *qce)
{
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(aead_def); i++) {
		wet = qce_aead_wegistew_one(&aead_def[i], qce);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	qce_aead_unwegistew(qce);
	wetuwn wet;
}

const stwuct qce_awgo_ops aead_ops = {
	.type = CWYPTO_AWG_TYPE_AEAD,
	.wegistew_awgs = qce_aead_wegistew,
	.unwegistew_awgs = qce_aead_unwegistew,
	.async_weq_handwe = qce_aead_async_weq_handwe,
};
