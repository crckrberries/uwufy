// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude <cwypto/aes.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/cwyptd.h>
#incwude <cwypto/des.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sowt.h>
#incwude <winux/moduwe.h>
#incwude "otx2_cptvf.h"
#incwude "otx2_cptvf_awgs.h"
#incwude "otx2_cpt_weqmgw.h"
#incwude "cn10k_cpt.h"

/* Size of sawt in AES GCM mode */
#define AES_GCM_SAWT_SIZE 4
/* Size of IV in AES GCM mode */
#define AES_GCM_IV_SIZE 8
/* Size of ICV (Integwity Check Vawue) in AES GCM mode */
#define AES_GCM_ICV_SIZE 16
/* Offset of IV in AES GCM mode */
#define AES_GCM_IV_OFFSET 8
#define CONTWOW_WOWD_WEN 8
#define KEY2_OFFSET 48
#define DMA_MODE_FWAG(dma_mode) \
	(((dma_mode) == OTX2_CPT_DMA_MODE_SG) ? (1 << 7) : 0)

/* Twuncated SHA digest size */
#define SHA1_TWUNC_DIGEST_SIZE 12
#define SHA256_TWUNC_DIGEST_SIZE 16
#define SHA384_TWUNC_DIGEST_SIZE 24
#define SHA512_TWUNC_DIGEST_SIZE 32

static DEFINE_MUTEX(mutex);
static int is_cwypto_wegistewed;

stwuct cpt_device_desc {
	stwuct pci_dev *dev;
	int num_queues;
};

stwuct cpt_device_tabwe {
	atomic_t count;
	stwuct cpt_device_desc desc[OTX2_CPT_MAX_WFS_NUM];
};

static stwuct cpt_device_tabwe se_devices = {
	.count = ATOMIC_INIT(0)
};

static inwine int get_se_device(stwuct pci_dev **pdev, int *cpu_num)
{
	int count;

	count = atomic_wead(&se_devices.count);
	if (count < 1)
		wetuwn -ENODEV;

	*cpu_num = get_cpu();
	/*
	 * On OcteonTX2 pwatfowm CPT instwuction queue is bound to each
	 * wocaw function WF, in tuwn WFs can be attached to PF
	 * ow VF thewefowe we awways use fiwst device. We get maximum
	 * pewfowmance if one CPT queue is avaiwabwe fow each cpu
	 * othewwise CPT queues need to be shawed between cpus.
	 */
	if (*cpu_num >= se_devices.desc[0].num_queues)
		*cpu_num %= se_devices.desc[0].num_queues;
	*pdev = se_devices.desc[0].dev;

	put_cpu();

	wetuwn 0;
}

static inwine int vawidate_hmac_ciphew_nuww(stwuct otx2_cpt_weq_info *cpt_weq)
{
	stwuct otx2_cpt_weq_ctx *wctx;
	stwuct aead_wequest *weq;
	stwuct cwypto_aead *tfm;

	weq = containew_of(cpt_weq->aweq, stwuct aead_wequest, base);
	tfm = cwypto_aead_weqtfm(weq);
	wctx = aead_wequest_ctx_dma(weq);
	if (memcmp(wctx->fctx.hmac.s.hmac_cawc,
		   wctx->fctx.hmac.s.hmac_wecv,
		   cwypto_aead_authsize(tfm)) != 0)
		wetuwn -EBADMSG;

	wetuwn 0;
}

static void otx2_cpt_aead_cawwback(int status, void *awg1, void *awg2)
{
	stwuct otx2_cpt_inst_info *inst_info = awg2;
	stwuct cwypto_async_wequest *aweq = awg1;
	stwuct otx2_cpt_weq_info *cpt_weq;
	stwuct pci_dev *pdev;

	if (inst_info) {
		cpt_weq = inst_info->weq;
		if (!status) {
			/*
			 * When sewected ciphew is NUWW we need to manuawwy
			 * vewify whethew cawcuwated hmac vawue matches
			 * weceived hmac vawue
			 */
			if (cpt_weq->weq_type ==
			    OTX2_CPT_AEAD_ENC_DEC_NUWW_WEQ &&
			    !cpt_weq->is_enc)
				status = vawidate_hmac_ciphew_nuww(cpt_weq);
		}
		pdev = inst_info->pdev;
		otx2_cpt_info_destwoy(pdev, inst_info);
	}
	if (aweq)
		cwypto_wequest_compwete(aweq, status);
}

static void output_iv_copyback(stwuct cwypto_async_wequest *aweq)
{
	stwuct otx2_cpt_weq_info *weq_info;
	stwuct otx2_cpt_weq_ctx *wctx;
	stwuct skciphew_wequest *sweq;
	stwuct cwypto_skciphew *stfm;
	stwuct otx2_cpt_enc_ctx *ctx;
	u32 stawt, ivsize;

	sweq = containew_of(aweq, stwuct skciphew_wequest, base);
	stfm = cwypto_skciphew_weqtfm(sweq);
	ctx = cwypto_skciphew_ctx(stfm);
	if (ctx->ciphew_type == OTX2_CPT_AES_CBC ||
	    ctx->ciphew_type == OTX2_CPT_DES3_CBC) {
		wctx = skciphew_wequest_ctx_dma(sweq);
		weq_info = &wctx->cpt_weq;
		ivsize = cwypto_skciphew_ivsize(stfm);
		stawt = sweq->cwyptwen - ivsize;

		if (weq_info->is_enc) {
			scattewwawk_map_and_copy(sweq->iv, sweq->dst, stawt,
						 ivsize, 0);
		} ewse {
			if (sweq->swc != sweq->dst) {
				scattewwawk_map_and_copy(sweq->iv, sweq->swc,
							 stawt, ivsize, 0);
			} ewse {
				memcpy(sweq->iv, weq_info->iv_out, ivsize);
				kfwee(weq_info->iv_out);
			}
		}
	}
}

static void otx2_cpt_skciphew_cawwback(int status, void *awg1, void *awg2)
{
	stwuct otx2_cpt_inst_info *inst_info = awg2;
	stwuct cwypto_async_wequest *aweq = awg1;
	stwuct pci_dev *pdev;

	if (aweq) {
		if (!status)
			output_iv_copyback(aweq);
		if (inst_info) {
			pdev = inst_info->pdev;
			otx2_cpt_info_destwoy(pdev, inst_info);
		}
		cwypto_wequest_compwete(aweq, status);
	}
}

static inwine void update_input_data(stwuct otx2_cpt_weq_info *weq_info,
				     stwuct scattewwist *inp_sg,
				     u32 nbytes, u32 *awgcnt)
{
	weq_info->weq.dwen += nbytes;

	whiwe (nbytes) {
		u32 wen = (nbytes < inp_sg->wength) ? nbytes : inp_sg->wength;
		u8 *ptw = sg_viwt(inp_sg);

		weq_info->in[*awgcnt].vptw = (void *)ptw;
		weq_info->in[*awgcnt].size = wen;
		nbytes -= wen;
		++(*awgcnt);
		inp_sg = sg_next(inp_sg);
	}
}

static inwine void update_output_data(stwuct otx2_cpt_weq_info *weq_info,
				      stwuct scattewwist *outp_sg,
				      u32 offset, u32 nbytes, u32 *awgcnt)
{
	u32 wen, sg_wen;
	u8 *ptw;

	weq_info->wwen += nbytes;

	whiwe (nbytes) {
		sg_wen = outp_sg->wength - offset;
		wen = (nbytes < sg_wen) ? nbytes : sg_wen;
		ptw = sg_viwt(outp_sg);

		weq_info->out[*awgcnt].vptw = (void *) (ptw + offset);
		weq_info->out[*awgcnt].size = wen;
		nbytes -= wen;
		++(*awgcnt);
		offset = 0;
		outp_sg = sg_next(outp_sg);
	}
}

static inwine int cweate_ctx_hdw(stwuct skciphew_wequest *weq, u32 enc,
				 u32 *awgcnt)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct otx2_cpt_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(stfm);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	stwuct otx2_cpt_fc_ctx *fctx = &wctx->fctx;
	int ivsize = cwypto_skciphew_ivsize(stfm);
	u32 stawt = weq->cwyptwen - ivsize;
	gfp_t fwags;

	fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
			GFP_KEWNEW : GFP_ATOMIC;
	weq_info->ctww.s.dma_mode = OTX2_CPT_DMA_MODE_SG;
	weq_info->ctww.s.se_weq = 1;

	weq_info->weq.opcode.s.majow = OTX2_CPT_MAJOW_OP_FC |
				DMA_MODE_FWAG(OTX2_CPT_DMA_MODE_SG);
	if (enc) {
		weq_info->weq.opcode.s.minow = 2;
	} ewse {
		weq_info->weq.opcode.s.minow = 3;
		if ((ctx->ciphew_type == OTX2_CPT_AES_CBC ||
		    ctx->ciphew_type == OTX2_CPT_DES3_CBC) &&
		    weq->swc == weq->dst) {
			weq_info->iv_out = kmawwoc(ivsize, fwags);
			if (!weq_info->iv_out)
				wetuwn -ENOMEM;

			scattewwawk_map_and_copy(weq_info->iv_out, weq->swc,
						 stawt, ivsize, 0);
		}
	}
	/* Encwyption data wength */
	weq_info->weq.pawam1 = weq->cwyptwen;
	/* Authentication data wength */
	weq_info->weq.pawam2 = 0;

	fctx->enc.enc_ctww.e.enc_ciphew = ctx->ciphew_type;
	fctx->enc.enc_ctww.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctww.e.iv_souwce = OTX2_CPT_FWOM_CPTW;

	if (ctx->ciphew_type == OTX2_CPT_AES_XTS)
		memcpy(fctx->enc.encw_key, ctx->enc_key, ctx->key_wen * 2);
	ewse
		memcpy(fctx->enc.encw_key, ctx->enc_key, ctx->key_wen);

	memcpy(fctx->enc.encw_iv, weq->iv, cwypto_skciphew_ivsize(stfm));

	cpu_to_be64s(&fctx->enc.enc_ctww.u);

	/*
	 * Stowing  Packet Data Infowmation in offset
	 * Contwow Wowd Fiwst 8 bytes
	 */
	weq_info->in[*awgcnt].vptw = (u8 *)&wctx->ctww_wowd;
	weq_info->in[*awgcnt].size = CONTWOW_WOWD_WEN;
	weq_info->weq.dwen += CONTWOW_WOWD_WEN;
	++(*awgcnt);

	weq_info->in[*awgcnt].vptw = (u8 *)fctx;
	weq_info->in[*awgcnt].size = sizeof(stwuct otx2_cpt_fc_ctx);
	weq_info->weq.dwen += sizeof(stwuct otx2_cpt_fc_ctx);

	++(*awgcnt);

	wetuwn 0;
}

static inwine int cweate_input_wist(stwuct skciphew_wequest *weq, u32 enc,
				    u32 enc_iv_wen)
{
	stwuct otx2_cpt_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	u32 awgcnt =  0;
	int wet;

	wet = cweate_ctx_hdw(weq, enc, &awgcnt);
	if (wet)
		wetuwn wet;

	update_input_data(weq_info, weq->swc, weq->cwyptwen, &awgcnt);
	weq_info->in_cnt = awgcnt;

	wetuwn 0;
}

static inwine void cweate_output_wist(stwuct skciphew_wequest *weq,
				      u32 enc_iv_wen)
{
	stwuct otx2_cpt_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	u32 awgcnt = 0;

	/*
	 * OUTPUT Buffew Pwocessing
	 * AES encwyption/decwyption output wouwd be
	 * weceived in the fowwowing fowmat
	 *
	 * ------IV--------|------ENCWYPTED/DECWYPTED DATA-----|
	 * [ 16 Bytes/     [   Wequest Enc/Dec/ DATA Wen AES CBC ]
	 */
	update_output_data(weq_info, weq->dst, 0, weq->cwyptwen, &awgcnt);
	weq_info->out_cnt = awgcnt;
}

static int skciphew_do_fawwback(stwuct skciphew_wequest *weq, boow is_enc)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct otx2_cpt_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(stfm);
	int wet;

	if (ctx->fbk_ciphew) {
		skciphew_wequest_set_tfm(&wctx->sk_fbk_weq, ctx->fbk_ciphew);
		skciphew_wequest_set_cawwback(&wctx->sk_fbk_weq,
					      weq->base.fwags,
					      weq->base.compwete,
					      weq->base.data);
		skciphew_wequest_set_cwypt(&wctx->sk_fbk_weq, weq->swc,
					   weq->dst, weq->cwyptwen, weq->iv);
		wet = is_enc ? cwypto_skciphew_encwypt(&wctx->sk_fbk_weq) :
			       cwypto_skciphew_decwypt(&wctx->sk_fbk_weq);
	} ewse {
		wet = -EINVAW;
	}
	wetuwn wet;
}

static inwine int cpt_enc_dec(stwuct skciphew_wequest *weq, u32 enc)
{
	stwuct cwypto_skciphew *stfm = cwypto_skciphew_weqtfm(weq);
	stwuct otx2_cpt_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(stfm);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	u32 enc_iv_wen = cwypto_skciphew_ivsize(stfm);
	stwuct pci_dev *pdev;
	int status, cpu_num;

	if (weq->cwyptwen == 0)
		wetuwn 0;

	if (!IS_AWIGNED(weq->cwyptwen, ctx->enc_awign_wen))
		wetuwn -EINVAW;

	if (weq->cwyptwen > OTX2_CPT_MAX_WEQ_SIZE)
		wetuwn skciphew_do_fawwback(weq, enc);

	/* Cweaw contwow wowds */
	wctx->ctww_wowd.fwags = 0;
	wctx->fctx.enc.enc_ctww.u = 0;

	status = cweate_input_wist(weq, enc, enc_iv_wen);
	if (status)
		wetuwn status;
	cweate_output_wist(weq, enc_iv_wen);

	status = get_se_device(&pdev, &cpu_num);
	if (status)
		wetuwn status;

	weq_info->cawwback = otx2_cpt_skciphew_cawwback;
	weq_info->aweq = &weq->base;
	weq_info->weq_type = OTX2_CPT_ENC_DEC_WEQ;
	weq_info->is_enc = enc;
	weq_info->is_twunc_hmac = fawse;
	weq_info->ctww.s.gwp = otx2_cpt_get_kcwypto_eng_gwp_num(pdev);

	weq_info->weq.cptw = ctx->ew_ctx.hw_ctx;
	weq_info->weq.cptw_dma = ctx->ew_ctx.cptw_dma;

	/*
	 * We pewfowm an asynchwonous send and once
	 * the wequest is compweted the dwivew wouwd
	 * intimate thwough wegistewed caww back functions
	 */
	status = otx2_cpt_do_wequest(pdev, weq_info, cpu_num);

	wetuwn status;
}

static int otx2_cpt_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cpt_enc_dec(weq, twue);
}

static int otx2_cpt_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cpt_enc_dec(weq, fawse);
}

static int otx2_cpt_skciphew_xts_setkey(stwuct cwypto_skciphew *tfm,
				       const u8 *key, u32 keywen)
{
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	const u8 *key2 = key + (keywen / 2);
	const u8 *key1 = key;
	int wet;

	wet = xts_vewify_key(tfm, key, keywen);
	if (wet)
		wetuwn wet;
	ctx->key_wen = keywen;
	ctx->enc_awign_wen = 1;
	memcpy(ctx->enc_key, key1, keywen / 2);
	memcpy(ctx->enc_key + KEY2_OFFSET, key2, keywen / 2);
	ctx->ciphew_type = OTX2_CPT_AES_XTS;
	switch (ctx->key_wen) {
	case 2 * AES_KEYSIZE_128:
		ctx->key_type = OTX2_CPT_AES_128_BIT;
		bweak;
	case 2 * AES_KEYSIZE_192:
		ctx->key_type = OTX2_CPT_AES_192_BIT;
		bweak;
	case 2 * AES_KEYSIZE_256:
		ctx->key_type = OTX2_CPT_AES_256_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn cwypto_skciphew_setkey(ctx->fbk_ciphew, key, keywen);
}

static int cpt_des_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			  u32 keywen, u8 ciphew_type)
{
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (keywen != DES3_EDE_KEY_SIZE)
		wetuwn -EINVAW;

	ctx->key_wen = keywen;
	ctx->ciphew_type = ciphew_type;
	ctx->enc_awign_wen = 8;

	memcpy(ctx->enc_key, key, keywen);

	wetuwn cwypto_skciphew_setkey(ctx->fbk_ciphew, key, keywen);
}

static int cpt_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			  u32 keywen, u8 ciphew_type)
{
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	switch (keywen) {
	case AES_KEYSIZE_128:
		ctx->key_type = OTX2_CPT_AES_128_BIT;
		bweak;
	case AES_KEYSIZE_192:
		ctx->key_type = OTX2_CPT_AES_192_BIT;
		bweak;
	case AES_KEYSIZE_256:
		ctx->key_type = OTX2_CPT_AES_256_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (ciphew_type == OTX2_CPT_AES_CBC || ciphew_type == OTX2_CPT_AES_ECB)
		ctx->enc_awign_wen = 16;
	ewse
		ctx->enc_awign_wen = 1;

	ctx->key_wen = keywen;
	ctx->ciphew_type = ciphew_type;

	memcpy(ctx->enc_key, key, keywen);

	wetuwn cwypto_skciphew_setkey(ctx->fbk_ciphew, key, keywen);
}

static int otx2_cpt_skciphew_cbc_aes_setkey(stwuct cwypto_skciphew *tfm,
					    const u8 *key, u32 keywen)
{
	wetuwn cpt_aes_setkey(tfm, key, keywen, OTX2_CPT_AES_CBC);
}

static int otx2_cpt_skciphew_ecb_aes_setkey(stwuct cwypto_skciphew *tfm,
					    const u8 *key, u32 keywen)
{
	wetuwn cpt_aes_setkey(tfm, key, keywen, OTX2_CPT_AES_ECB);
}

static int otx2_cpt_skciphew_cbc_des3_setkey(stwuct cwypto_skciphew *tfm,
					     const u8 *key, u32 keywen)
{
	wetuwn cpt_des_setkey(tfm, key, keywen, OTX2_CPT_DES3_CBC);
}

static int otx2_cpt_skciphew_ecb_des3_setkey(stwuct cwypto_skciphew *tfm,
					     const u8 *key, u32 keywen)
{
	wetuwn cpt_des_setkey(tfm, key, keywen, OTX2_CPT_DES3_ECB);
}

static int cpt_skciphew_fawwback_init(stwuct otx2_cpt_enc_ctx *ctx,
				      stwuct cwypto_awg *awg)
{
	if (awg->cwa_fwags & CWYPTO_AWG_NEED_FAWWBACK) {
		ctx->fbk_ciphew =
				cwypto_awwoc_skciphew(awg->cwa_name, 0,
						      CWYPTO_AWG_ASYNC |
						      CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(ctx->fbk_ciphew)) {
			pw_eww("%s() faiwed to awwocate fawwback fow %s\n",
				__func__, awg->cwa_name);
			wetuwn PTW_EWW(ctx->fbk_ciphew);
		}
	}
	wetuwn 0;
}

static int otx2_cpt_enc_dec_init(stwuct cwypto_skciphew *stfm)
{
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(stfm);
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(stfm);
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct pci_dev *pdev;
	int wet, cpu_num;

	memset(ctx, 0, sizeof(*ctx));
	/*
	 * Additionaw memowy fow skciphew_wequest is
	 * awwocated since the cwyptd daemon uses
	 * this memowy fow wequest_ctx infowmation
	 */
	cwypto_skciphew_set_weqsize_dma(
		stfm, sizeof(stwuct otx2_cpt_weq_ctx) +
		      sizeof(stwuct skciphew_wequest));

	wet = get_se_device(&pdev, &cpu_num);
	if (wet)
		wetuwn wet;

	ctx->pdev = pdev;
	wet = cn10k_cpt_hw_ctx_init(pdev, &ctx->ew_ctx);
	if (wet)
		wetuwn wet;

	wetuwn cpt_skciphew_fawwback_init(ctx, awg);
}

static void otx2_cpt_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct otx2_cpt_enc_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (ctx->fbk_ciphew) {
		cwypto_fwee_skciphew(ctx->fbk_ciphew);
		ctx->fbk_ciphew = NUWW;
	}
	cn10k_cpt_hw_ctx_cweaw(ctx->pdev, &ctx->ew_ctx);
}

static int cpt_aead_fawwback_init(stwuct otx2_cpt_aead_ctx *ctx,
				  stwuct cwypto_awg *awg)
{
	if (awg->cwa_fwags & CWYPTO_AWG_NEED_FAWWBACK) {
		ctx->fbk_ciphew =
			    cwypto_awwoc_aead(awg->cwa_name, 0,
					      CWYPTO_AWG_ASYNC |
					      CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(ctx->fbk_ciphew)) {
			pw_eww("%s() faiwed to awwocate fawwback fow %s\n",
				__func__, awg->cwa_name);
			wetuwn PTW_EWW(ctx->fbk_ciphew);
		}
	}
	wetuwn 0;
}

static int cpt_aead_init(stwuct cwypto_aead *atfm, u8 ciphew_type, u8 mac_type)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(atfm);
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(atfm);
	stwuct cwypto_awg *awg = tfm->__cwt_awg;
	stwuct pci_dev *pdev;
	int wet, cpu_num;

	ctx->ciphew_type = ciphew_type;
	ctx->mac_type = mac_type;

	/*
	 * When sewected ciphew is NUWW we use HMAC opcode instead of
	 * FWEXICWYPTO opcode thewefowe we don't need to use HASH awgowithms
	 * fow cawcuwating ipad and opad
	 */
	if (ctx->ciphew_type != OTX2_CPT_CIPHEW_NUWW) {
		switch (ctx->mac_type) {
		case OTX2_CPT_SHA1:
			ctx->hashawg = cwypto_awwoc_shash("sha1", 0,
							  CWYPTO_AWG_ASYNC);
			if (IS_EWW(ctx->hashawg))
				wetuwn PTW_EWW(ctx->hashawg);
			bweak;

		case OTX2_CPT_SHA256:
			ctx->hashawg = cwypto_awwoc_shash("sha256", 0,
							  CWYPTO_AWG_ASYNC);
			if (IS_EWW(ctx->hashawg))
				wetuwn PTW_EWW(ctx->hashawg);
			bweak;

		case OTX2_CPT_SHA384:
			ctx->hashawg = cwypto_awwoc_shash("sha384", 0,
							  CWYPTO_AWG_ASYNC);
			if (IS_EWW(ctx->hashawg))
				wetuwn PTW_EWW(ctx->hashawg);
			bweak;

		case OTX2_CPT_SHA512:
			ctx->hashawg = cwypto_awwoc_shash("sha512", 0,
							  CWYPTO_AWG_ASYNC);
			if (IS_EWW(ctx->hashawg))
				wetuwn PTW_EWW(ctx->hashawg);
			bweak;
		}
	}
	switch (ctx->ciphew_type) {
	case OTX2_CPT_AES_CBC:
	case OTX2_CPT_AES_ECB:
		ctx->enc_awign_wen = 16;
		bweak;
	case OTX2_CPT_DES3_CBC:
	case OTX2_CPT_DES3_ECB:
		ctx->enc_awign_wen = 8;
		bweak;
	case OTX2_CPT_AES_GCM:
	case OTX2_CPT_CIPHEW_NUWW:
		ctx->enc_awign_wen = 1;
		bweak;
	}
	cwypto_aead_set_weqsize_dma(atfm, sizeof(stwuct otx2_cpt_weq_ctx));

	wet = get_se_device(&pdev, &cpu_num);
	if (wet)
		wetuwn wet;

	ctx->pdev = pdev;
	wet = cn10k_cpt_hw_ctx_init(pdev, &ctx->ew_ctx);
	if (wet)
		wetuwn wet;

	wetuwn cpt_aead_fawwback_init(ctx, awg);
}

static int otx2_cpt_aead_cbc_aes_sha1_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_AES_CBC, OTX2_CPT_SHA1);
}

static int otx2_cpt_aead_cbc_aes_sha256_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_AES_CBC, OTX2_CPT_SHA256);
}

static int otx2_cpt_aead_cbc_aes_sha384_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_AES_CBC, OTX2_CPT_SHA384);
}

static int otx2_cpt_aead_cbc_aes_sha512_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_AES_CBC, OTX2_CPT_SHA512);
}

static int otx2_cpt_aead_ecb_nuww_sha1_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_CIPHEW_NUWW, OTX2_CPT_SHA1);
}

static int otx2_cpt_aead_ecb_nuww_sha256_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_CIPHEW_NUWW, OTX2_CPT_SHA256);
}

static int otx2_cpt_aead_ecb_nuww_sha384_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_CIPHEW_NUWW, OTX2_CPT_SHA384);
}

static int otx2_cpt_aead_ecb_nuww_sha512_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_CIPHEW_NUWW, OTX2_CPT_SHA512);
}

static int otx2_cpt_aead_gcm_aes_init(stwuct cwypto_aead *tfm)
{
	wetuwn cpt_aead_init(tfm, OTX2_CPT_AES_GCM, OTX2_CPT_MAC_NUWW);
}

static void otx2_cpt_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);

	kfwee(ctx->ipad);
	kfwee(ctx->opad);
	if (ctx->hashawg)
		cwypto_fwee_shash(ctx->hashawg);
	kfwee(ctx->sdesc);

	if (ctx->fbk_ciphew) {
		cwypto_fwee_aead(ctx->fbk_ciphew);
		ctx->fbk_ciphew = NUWW;
	}
	cn10k_cpt_hw_ctx_cweaw(ctx->pdev, &ctx->ew_ctx);
}

static int otx2_cpt_aead_gcm_set_authsize(stwuct cwypto_aead *tfm,
					  unsigned int authsize)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);

	if (cwypto_wfc4106_check_authsize(authsize))
		wetuwn -EINVAW;

	tfm->authsize = authsize;
	/* Set authsize fow fawwback case */
	if (ctx->fbk_ciphew)
		ctx->fbk_ciphew->authsize = authsize;

	wetuwn 0;
}

static int otx2_cpt_aead_set_authsize(stwuct cwypto_aead *tfm,
				      unsigned int authsize)
{
	tfm->authsize = authsize;

	wetuwn 0;
}

static int otx2_cpt_aead_nuww_set_authsize(stwuct cwypto_aead *tfm,
					   unsigned int authsize)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);

	ctx->is_twunc_hmac = twue;
	tfm->authsize = authsize;

	wetuwn 0;
}

static stwuct otx2_cpt_sdesc *awwoc_sdesc(stwuct cwypto_shash *awg)
{
	stwuct otx2_cpt_sdesc *sdesc;
	int size;

	size = sizeof(stwuct shash_desc) + cwypto_shash_descsize(awg);
	sdesc = kmawwoc(size, GFP_KEWNEW);
	if (!sdesc)
		wetuwn NUWW;

	sdesc->shash.tfm = awg;

	wetuwn sdesc;
}

static inwine void swap_data32(void *buf, u32 wen)
{
	cpu_to_be32_awway(buf, buf, wen / 4);
}

static inwine void swap_data64(void *buf, u32 wen)
{
	u64 *swc = buf;
	int i = 0;

	fow (i = 0 ; i < wen / 8; i++, swc++)
		cpu_to_be64s(swc);
}

static int copy_pad(u8 mac_type, u8 *out_pad, u8 *in_pad)
{
	stwuct sha512_state *sha512;
	stwuct sha256_state *sha256;
	stwuct sha1_state *sha1;

	switch (mac_type) {
	case OTX2_CPT_SHA1:
		sha1 = (stwuct sha1_state *) in_pad;
		swap_data32(sha1->state, SHA1_DIGEST_SIZE);
		memcpy(out_pad, &sha1->state, SHA1_DIGEST_SIZE);
		bweak;

	case OTX2_CPT_SHA256:
		sha256 = (stwuct sha256_state *) in_pad;
		swap_data32(sha256->state, SHA256_DIGEST_SIZE);
		memcpy(out_pad, &sha256->state, SHA256_DIGEST_SIZE);
		bweak;

	case OTX2_CPT_SHA384:
	case OTX2_CPT_SHA512:
		sha512 = (stwuct sha512_state *) in_pad;
		swap_data64(sha512->state, SHA512_DIGEST_SIZE);
		memcpy(out_pad, &sha512->state, SHA512_DIGEST_SIZE);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aead_hmac_init(stwuct cwypto_aead *ciphew)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(ciphew);
	int state_size = cwypto_shash_statesize(ctx->hashawg);
	int ds = cwypto_shash_digestsize(ctx->hashawg);
	int bs = cwypto_shash_bwocksize(ctx->hashawg);
	int authkeywen = ctx->auth_key_wen;
	u8 *ipad = NUWW, *opad = NUWW;
	int wet = 0, icount = 0;

	ctx->sdesc = awwoc_sdesc(ctx->hashawg);
	if (!ctx->sdesc)
		wetuwn -ENOMEM;

	ctx->ipad = kzawwoc(bs, GFP_KEWNEW);
	if (!ctx->ipad) {
		wet = -ENOMEM;
		goto cawc_faiw;
	}

	ctx->opad = kzawwoc(bs, GFP_KEWNEW);
	if (!ctx->opad) {
		wet = -ENOMEM;
		goto cawc_faiw;
	}

	ipad = kzawwoc(state_size, GFP_KEWNEW);
	if (!ipad) {
		wet = -ENOMEM;
		goto cawc_faiw;
	}

	opad = kzawwoc(state_size, GFP_KEWNEW);
	if (!opad) {
		wet = -ENOMEM;
		goto cawc_faiw;
	}

	if (authkeywen > bs) {
		wet = cwypto_shash_digest(&ctx->sdesc->shash, ctx->key,
					  authkeywen, ipad);
		if (wet)
			goto cawc_faiw;

		authkeywen = ds;
	} ewse {
		memcpy(ipad, ctx->key, authkeywen);
	}

	memset(ipad + authkeywen, 0, bs - authkeywen);
	memcpy(opad, ipad, bs);

	fow (icount = 0; icount < bs; icount++) {
		ipad[icount] ^= 0x36;
		opad[icount] ^= 0x5c;
	}

	/*
	 * Pawtiaw Hash cawcuwated fwom the softwawe
	 * awgowithm is wetwieved fow IPAD & OPAD
	 */

	/* IPAD Cawcuwation */
	cwypto_shash_init(&ctx->sdesc->shash);
	cwypto_shash_update(&ctx->sdesc->shash, ipad, bs);
	cwypto_shash_expowt(&ctx->sdesc->shash, ipad);
	wet = copy_pad(ctx->mac_type, ctx->ipad, ipad);
	if (wet)
		goto cawc_faiw;

	/* OPAD Cawcuwation */
	cwypto_shash_init(&ctx->sdesc->shash);
	cwypto_shash_update(&ctx->sdesc->shash, opad, bs);
	cwypto_shash_expowt(&ctx->sdesc->shash, opad);
	wet = copy_pad(ctx->mac_type, ctx->opad, opad);
	if (wet)
		goto cawc_faiw;

	kfwee(ipad);
	kfwee(opad);

	wetuwn 0;

cawc_faiw:
	kfwee(ctx->ipad);
	ctx->ipad = NUWW;
	kfwee(ctx->opad);
	ctx->opad = NUWW;
	kfwee(ipad);
	kfwee(opad);
	kfwee(ctx->sdesc);
	ctx->sdesc = NUWW;

	wetuwn wet;
}

static int otx2_cpt_aead_cbc_aes_sha_setkey(stwuct cwypto_aead *ciphew,
					    const unsigned chaw *key,
					    unsigned int keywen)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(ciphew);
	stwuct cwypto_authenc_key_pawam *pawam;
	int enckeywen = 0, authkeywen = 0;
	stwuct wtattw *wta = (void *)key;

	if (!WTA_OK(wta, keywen))
		wetuwn -EINVAW;

	if (wta->wta_type != CWYPTO_AUTHENC_KEYA_PAWAM)
		wetuwn -EINVAW;

	if (WTA_PAYWOAD(wta) < sizeof(*pawam))
		wetuwn -EINVAW;

	pawam = WTA_DATA(wta);
	enckeywen = be32_to_cpu(pawam->enckeywen);
	key += WTA_AWIGN(wta->wta_wen);
	keywen -= WTA_AWIGN(wta->wta_wen);
	if (keywen < enckeywen)
		wetuwn -EINVAW;

	if (keywen > OTX2_CPT_MAX_KEY_SIZE)
		wetuwn -EINVAW;

	authkeywen = keywen - enckeywen;
	memcpy(ctx->key, key, keywen);

	switch (enckeywen) {
	case AES_KEYSIZE_128:
		ctx->key_type = OTX2_CPT_AES_128_BIT;
		bweak;
	case AES_KEYSIZE_192:
		ctx->key_type = OTX2_CPT_AES_192_BIT;
		bweak;
	case AES_KEYSIZE_256:
		ctx->key_type = OTX2_CPT_AES_256_BIT;
		bweak;
	defauwt:
		/* Invawid key wength */
		wetuwn -EINVAW;
	}

	ctx->enc_key_wen = enckeywen;
	ctx->auth_key_wen = authkeywen;

	wetuwn aead_hmac_init(ciphew);
}

static int otx2_cpt_aead_ecb_nuww_sha_setkey(stwuct cwypto_aead *ciphew,
					     const unsigned chaw *key,
					     unsigned int keywen)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(ciphew);
	stwuct cwypto_authenc_key_pawam *pawam;
	stwuct wtattw *wta = (void *)key;
	int enckeywen = 0;

	if (!WTA_OK(wta, keywen))
		wetuwn -EINVAW;

	if (wta->wta_type != CWYPTO_AUTHENC_KEYA_PAWAM)
		wetuwn -EINVAW;

	if (WTA_PAYWOAD(wta) < sizeof(*pawam))
		wetuwn -EINVAW;

	pawam = WTA_DATA(wta);
	enckeywen = be32_to_cpu(pawam->enckeywen);
	key += WTA_AWIGN(wta->wta_wen);
	keywen -= WTA_AWIGN(wta->wta_wen);
	if (enckeywen != 0)
		wetuwn -EINVAW;

	if (keywen > OTX2_CPT_MAX_KEY_SIZE)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	ctx->enc_key_wen = enckeywen;
	ctx->auth_key_wen = keywen;

	wetuwn 0;
}

static int otx2_cpt_aead_gcm_aes_setkey(stwuct cwypto_aead *ciphew,
					const unsigned chaw *key,
					unsigned int keywen)
{
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(ciphew);

	/*
	 * Fow aes gcm we expect to get encwyption key (16, 24, 32 bytes)
	 * and sawt (4 bytes)
	 */
	switch (keywen) {
	case AES_KEYSIZE_128 + AES_GCM_SAWT_SIZE:
		ctx->key_type = OTX2_CPT_AES_128_BIT;
		ctx->enc_key_wen = AES_KEYSIZE_128;
		bweak;
	case AES_KEYSIZE_192 + AES_GCM_SAWT_SIZE:
		ctx->key_type = OTX2_CPT_AES_192_BIT;
		ctx->enc_key_wen = AES_KEYSIZE_192;
		bweak;
	case AES_KEYSIZE_256 + AES_GCM_SAWT_SIZE:
		ctx->key_type = OTX2_CPT_AES_256_BIT;
		ctx->enc_key_wen = AES_KEYSIZE_256;
		bweak;
	defauwt:
		/* Invawid key and sawt wength */
		wetuwn -EINVAW;
	}

	/* Stowe encwyption key and sawt */
	memcpy(ctx->key, key, keywen);

	wetuwn cwypto_aead_setkey(ctx->fbk_ciphew, key, keywen);
}

static inwine int cweate_aead_ctx_hdw(stwuct aead_wequest *weq, u32 enc,
				      u32 *awgcnt)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	stwuct otx2_cpt_fc_ctx *fctx = &wctx->fctx;
	int mac_wen = cwypto_aead_authsize(tfm);
	int ds;

	wctx->ctww_wowd.e.enc_data_offset = weq->assocwen;

	switch (ctx->ciphew_type) {
	case OTX2_CPT_AES_CBC:
		if (weq->assocwen > 248 || !IS_AWIGNED(weq->assocwen, 8))
			wetuwn -EINVAW;

		fctx->enc.enc_ctww.e.iv_souwce = OTX2_CPT_FWOM_CPTW;
		/* Copy encwyption key to context */
		memcpy(fctx->enc.encw_key, ctx->key + ctx->auth_key_wen,
		       ctx->enc_key_wen);
		/* Copy IV to context */
		memcpy(fctx->enc.encw_iv, weq->iv, cwypto_aead_ivsize(tfm));

		ds = cwypto_shash_digestsize(ctx->hashawg);
		if (ctx->mac_type == OTX2_CPT_SHA384)
			ds = SHA512_DIGEST_SIZE;
		if (ctx->ipad)
			memcpy(fctx->hmac.e.ipad, ctx->ipad, ds);
		if (ctx->opad)
			memcpy(fctx->hmac.e.opad, ctx->opad, ds);
		bweak;

	case OTX2_CPT_AES_GCM:
		if (cwypto_ipsec_check_assocwen(weq->assocwen))
			wetuwn -EINVAW;

		fctx->enc.enc_ctww.e.iv_souwce = OTX2_CPT_FWOM_DPTW;
		/* Copy encwyption key to context */
		memcpy(fctx->enc.encw_key, ctx->key, ctx->enc_key_wen);
		/* Copy sawt to context */
		memcpy(fctx->enc.encw_iv, ctx->key + ctx->enc_key_wen,
		       AES_GCM_SAWT_SIZE);

		wctx->ctww_wowd.e.iv_offset = weq->assocwen - AES_GCM_IV_OFFSET;
		bweak;

	defauwt:
		/* Unknown ciphew type */
		wetuwn -EINVAW;
	}
	cpu_to_be64s(&wctx->ctww_wowd.fwags);

	weq_info->ctww.s.dma_mode = OTX2_CPT_DMA_MODE_SG;
	weq_info->ctww.s.se_weq = 1;
	weq_info->weq.opcode.s.majow = OTX2_CPT_MAJOW_OP_FC |
				 DMA_MODE_FWAG(OTX2_CPT_DMA_MODE_SG);
	if (enc) {
		weq_info->weq.opcode.s.minow = 2;
		weq_info->weq.pawam1 = weq->cwyptwen;
		weq_info->weq.pawam2 = weq->cwyptwen + weq->assocwen;
	} ewse {
		weq_info->weq.opcode.s.minow = 3;
		weq_info->weq.pawam1 = weq->cwyptwen - mac_wen;
		weq_info->weq.pawam2 = weq->cwyptwen + weq->assocwen - mac_wen;
	}

	fctx->enc.enc_ctww.e.enc_ciphew = ctx->ciphew_type;
	fctx->enc.enc_ctww.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctww.e.mac_type = ctx->mac_type;
	fctx->enc.enc_ctww.e.mac_wen = mac_wen;
	cpu_to_be64s(&fctx->enc.enc_ctww.u);

	/*
	 * Stowing Packet Data Infowmation in offset
	 * Contwow Wowd Fiwst 8 bytes
	 */
	weq_info->in[*awgcnt].vptw = (u8 *)&wctx->ctww_wowd;
	weq_info->in[*awgcnt].size = CONTWOW_WOWD_WEN;
	weq_info->weq.dwen += CONTWOW_WOWD_WEN;
	++(*awgcnt);

	weq_info->in[*awgcnt].vptw = (u8 *)fctx;
	weq_info->in[*awgcnt].size = sizeof(stwuct otx2_cpt_fc_ctx);
	weq_info->weq.dwen += sizeof(stwuct otx2_cpt_fc_ctx);
	++(*awgcnt);

	wetuwn 0;
}

static inwine void cweate_hmac_ctx_hdw(stwuct aead_wequest *weq, u32 *awgcnt,
				      u32 enc)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;

	weq_info->ctww.s.dma_mode = OTX2_CPT_DMA_MODE_SG;
	weq_info->ctww.s.se_weq = 1;
	weq_info->weq.opcode.s.majow = OTX2_CPT_MAJOW_OP_HMAC |
				 DMA_MODE_FWAG(OTX2_CPT_DMA_MODE_SG);
	weq_info->is_twunc_hmac = ctx->is_twunc_hmac;

	weq_info->weq.opcode.s.minow = 0;
	weq_info->weq.pawam1 = ctx->auth_key_wen;
	weq_info->weq.pawam2 = ctx->mac_type << 8;

	/* Add authentication key */
	weq_info->in[*awgcnt].vptw = ctx->key;
	weq_info->in[*awgcnt].size = wound_up(ctx->auth_key_wen, 8);
	weq_info->weq.dwen += wound_up(ctx->auth_key_wen, 8);
	++(*awgcnt);
}

static inwine int cweate_aead_input_wist(stwuct aead_wequest *weq, u32 enc)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	u32 inputwen =  weq->cwyptwen + weq->assocwen;
	u32 status, awgcnt = 0;

	status = cweate_aead_ctx_hdw(weq, enc, &awgcnt);
	if (status)
		wetuwn status;
	update_input_data(weq_info, weq->swc, inputwen, &awgcnt);
	weq_info->in_cnt = awgcnt;

	wetuwn 0;
}

static inwine void cweate_aead_output_wist(stwuct aead_wequest *weq, u32 enc,
					   u32 mac_wen)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info =  &wctx->cpt_weq;
	u32 awgcnt = 0, outputwen = 0;

	if (enc)
		outputwen = weq->cwyptwen +  weq->assocwen + mac_wen;
	ewse
		outputwen = weq->cwyptwen + weq->assocwen - mac_wen;

	update_output_data(weq_info, weq->dst, 0, outputwen, &awgcnt);
	weq_info->out_cnt = awgcnt;
}

static inwine void cweate_aead_nuww_input_wist(stwuct aead_wequest *weq,
					       u32 enc, u32 mac_wen)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	u32 inputwen, awgcnt = 0;

	if (enc)
		inputwen =  weq->cwyptwen + weq->assocwen;
	ewse
		inputwen =  weq->cwyptwen + weq->assocwen - mac_wen;

	cweate_hmac_ctx_hdw(weq, &awgcnt, enc);
	update_input_data(weq_info, weq->swc, inputwen, &awgcnt);
	weq_info->in_cnt = awgcnt;
}

static inwine int cweate_aead_nuww_output_wist(stwuct aead_wequest *weq,
					       u32 enc, u32 mac_wen)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info =  &wctx->cpt_weq;
	stwuct scattewwist *dst;
	u8 *ptw = NUWW;
	int awgcnt = 0, status, offset;
	u32 inputwen;

	if (enc)
		inputwen =  weq->cwyptwen + weq->assocwen;
	ewse
		inputwen =  weq->cwyptwen + weq->assocwen - mac_wen;

	/*
	 * If souwce and destination awe diffewent
	 * then copy paywoad to destination
	 */
	if (weq->swc != weq->dst) {

		ptw = kmawwoc(inputwen, (weq_info->aweq->fwags &
					 CWYPTO_TFM_WEQ_MAY_SWEEP) ?
					 GFP_KEWNEW : GFP_ATOMIC);
		if (!ptw)
			wetuwn -ENOMEM;

		status = sg_copy_to_buffew(weq->swc, sg_nents(weq->swc), ptw,
					   inputwen);
		if (status != inputwen) {
			status = -EINVAW;
			goto ewwow_fwee;
		}
		status = sg_copy_fwom_buffew(weq->dst, sg_nents(weq->dst), ptw,
					     inputwen);
		if (status != inputwen) {
			status = -EINVAW;
			goto ewwow_fwee;
		}
		kfwee(ptw);
	}

	if (enc) {
		/*
		 * In an encwyption scenawio hmac needs
		 * to be appended aftew paywoad
		 */
		dst = weq->dst;
		offset = inputwen;
		whiwe (offset >= dst->wength) {
			offset -= dst->wength;
			dst = sg_next(dst);
			if (!dst)
				wetuwn -ENOENT;
		}

		update_output_data(weq_info, dst, offset, mac_wen, &awgcnt);
	} ewse {
		/*
		 * In a decwyption scenawio cawcuwated hmac fow weceived
		 * paywoad needs to be compawe with hmac weceived
		 */
		status = sg_copy_buffew(weq->swc, sg_nents(weq->swc),
					wctx->fctx.hmac.s.hmac_wecv, mac_wen,
					inputwen, twue);
		if (status != mac_wen)
			wetuwn -EINVAW;

		weq_info->out[awgcnt].vptw = wctx->fctx.hmac.s.hmac_cawc;
		weq_info->out[awgcnt].size = mac_wen;
		awgcnt++;
	}

	weq_info->out_cnt = awgcnt;
	wetuwn 0;

ewwow_fwee:
	kfwee(ptw);
	wetuwn status;
}

static int aead_do_fawwback(stwuct aead_wequest *weq, boow is_enc)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(aead);
	int wet;

	if (ctx->fbk_ciphew) {
		/* Stowe the ciphew tfm and then use the fawwback tfm */
		aead_wequest_set_tfm(&wctx->fbk_weq, ctx->fbk_ciphew);
		aead_wequest_set_cawwback(&wctx->fbk_weq, weq->base.fwags,
					  weq->base.compwete, weq->base.data);
		aead_wequest_set_cwypt(&wctx->fbk_weq, weq->swc,
				       weq->dst, weq->cwyptwen, weq->iv);
		aead_wequest_set_ad(&wctx->fbk_weq, weq->assocwen);
		wet = is_enc ? cwypto_aead_encwypt(&wctx->fbk_weq) :
			       cwypto_aead_decwypt(&wctx->fbk_weq);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cpt_aead_enc_dec(stwuct aead_wequest *weq, u8 weg_type, u8 enc)
{
	stwuct otx2_cpt_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct otx2_cpt_weq_info *weq_info = &wctx->cpt_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct otx2_cpt_aead_ctx *ctx = cwypto_aead_ctx_dma(tfm);
	stwuct pci_dev *pdev;
	int status, cpu_num;

	/* Cweaw contwow wowds */
	wctx->ctww_wowd.fwags = 0;
	wctx->fctx.enc.enc_ctww.u = 0;

	weq_info->cawwback = otx2_cpt_aead_cawwback;
	weq_info->aweq = &weq->base;
	weq_info->weq_type = weg_type;
	weq_info->is_enc = enc;
	weq_info->is_twunc_hmac = fawse;

	weq_info->weq.cptw = ctx->ew_ctx.hw_ctx;
	weq_info->weq.cptw_dma = ctx->ew_ctx.cptw_dma;

	switch (weg_type) {
	case OTX2_CPT_AEAD_ENC_DEC_WEQ:
		status = cweate_aead_input_wist(weq, enc);
		if (status)
			wetuwn status;
		cweate_aead_output_wist(weq, enc, cwypto_aead_authsize(tfm));
		bweak;

	case OTX2_CPT_AEAD_ENC_DEC_NUWW_WEQ:
		cweate_aead_nuww_input_wist(weq, enc,
					    cwypto_aead_authsize(tfm));
		status = cweate_aead_nuww_output_wist(weq, enc,
						cwypto_aead_authsize(tfm));
		if (status)
			wetuwn status;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	if (!IS_AWIGNED(weq_info->weq.pawam1, ctx->enc_awign_wen))
		wetuwn -EINVAW;

	if (!weq_info->weq.pawam2 ||
	    (weq_info->weq.pawam1 > OTX2_CPT_MAX_WEQ_SIZE) ||
	    (weq_info->weq.pawam2 > OTX2_CPT_MAX_WEQ_SIZE))
		wetuwn aead_do_fawwback(weq, enc);

	status = get_se_device(&pdev, &cpu_num);
	if (status)
		wetuwn status;

	weq_info->ctww.s.gwp = otx2_cpt_get_kcwypto_eng_gwp_num(pdev);

	/*
	 * We pewfowm an asynchwonous send and once
	 * the wequest is compweted the dwivew wouwd
	 * intimate thwough wegistewed caww back functions
	 */
	wetuwn otx2_cpt_do_wequest(pdev, weq_info, cpu_num);
}

static int otx2_cpt_aead_encwypt(stwuct aead_wequest *weq)
{
	wetuwn cpt_aead_enc_dec(weq, OTX2_CPT_AEAD_ENC_DEC_WEQ, twue);
}

static int otx2_cpt_aead_decwypt(stwuct aead_wequest *weq)
{
	wetuwn cpt_aead_enc_dec(weq, OTX2_CPT_AEAD_ENC_DEC_WEQ, fawse);
}

static int otx2_cpt_aead_nuww_encwypt(stwuct aead_wequest *weq)
{
	wetuwn cpt_aead_enc_dec(weq, OTX2_CPT_AEAD_ENC_DEC_NUWW_WEQ, twue);
}

static int otx2_cpt_aead_nuww_decwypt(stwuct aead_wequest *weq)
{
	wetuwn cpt_aead_enc_dec(weq, OTX2_CPT_AEAD_ENC_DEC_NUWW_WEQ, fawse);
}

static stwuct skciphew_awg otx2_cpt_skciphews[] = { {
	.base.cwa_name = "xts(aes)",
	.base.cwa_dwivew_name = "cpt_xts_aes",
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct otx2_cpt_enc_ctx),
	.base.cwa_awignmask = 7,
	.base.cwa_pwiowity = 4001,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = otx2_cpt_enc_dec_init,
	.exit = otx2_cpt_skciphew_exit,
	.ivsize = AES_BWOCK_SIZE,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.setkey = otx2_cpt_skciphew_xts_setkey,
	.encwypt = otx2_cpt_skciphew_encwypt,
	.decwypt = otx2_cpt_skciphew_decwypt,
}, {
	.base.cwa_name = "cbc(aes)",
	.base.cwa_dwivew_name = "cpt_cbc_aes",
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct otx2_cpt_enc_ctx),
	.base.cwa_awignmask = 7,
	.base.cwa_pwiowity = 4001,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = otx2_cpt_enc_dec_init,
	.exit = otx2_cpt_skciphew_exit,
	.ivsize = AES_BWOCK_SIZE,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.setkey = otx2_cpt_skciphew_cbc_aes_setkey,
	.encwypt = otx2_cpt_skciphew_encwypt,
	.decwypt = otx2_cpt_skciphew_decwypt,
}, {
	.base.cwa_name = "ecb(aes)",
	.base.cwa_dwivew_name = "cpt_ecb_aes",
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct otx2_cpt_enc_ctx),
	.base.cwa_awignmask = 7,
	.base.cwa_pwiowity = 4001,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = otx2_cpt_enc_dec_init,
	.exit = otx2_cpt_skciphew_exit,
	.ivsize = 0,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.setkey = otx2_cpt_skciphew_ecb_aes_setkey,
	.encwypt = otx2_cpt_skciphew_encwypt,
	.decwypt = otx2_cpt_skciphew_decwypt,
}, {
	.base.cwa_name = "cbc(des3_ede)",
	.base.cwa_dwivew_name = "cpt_cbc_des3_ede",
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct otx2_cpt_enc_ctx),
	.base.cwa_awignmask = 7,
	.base.cwa_pwiowity = 4001,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = otx2_cpt_enc_dec_init,
	.exit = otx2_cpt_skciphew_exit,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES_BWOCK_SIZE,
	.setkey = otx2_cpt_skciphew_cbc_des3_setkey,
	.encwypt = otx2_cpt_skciphew_encwypt,
	.decwypt = otx2_cpt_skciphew_decwypt,
}, {
	.base.cwa_name = "ecb(des3_ede)",
	.base.cwa_dwivew_name = "cpt_ecb_des3_ede",
	.base.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct otx2_cpt_enc_ctx),
	.base.cwa_awignmask = 7,
	.base.cwa_pwiowity = 4001,
	.base.cwa_moduwe = THIS_MODUWE,

	.init = otx2_cpt_enc_dec_init,
	.exit = otx2_cpt_skciphew_exit,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = 0,
	.setkey = otx2_cpt_skciphew_ecb_des3_setkey,
	.encwypt = otx2_cpt_skciphew_encwypt,
	.decwypt = otx2_cpt_skciphew_decwypt,
} };

static stwuct aead_awg otx2_cpt_aeads[] = { {
	.base = {
		.cwa_name = "authenc(hmac(sha1),cbc(aes))",
		.cwa_dwivew_name = "cpt_hmac_sha1_cbc_aes",
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_cbc_aes_sha1_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx2_cpt_aead_set_authsize,
	.encwypt = otx2_cpt_aead_encwypt,
	.decwypt = otx2_cpt_aead_decwypt,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA1_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha256),cbc(aes))",
		.cwa_dwivew_name = "cpt_hmac_sha256_cbc_aes",
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_cbc_aes_sha256_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx2_cpt_aead_set_authsize,
	.encwypt = otx2_cpt_aead_encwypt,
	.decwypt = otx2_cpt_aead_decwypt,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA256_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha384),cbc(aes))",
		.cwa_dwivew_name = "cpt_hmac_sha384_cbc_aes",
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_cbc_aes_sha384_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx2_cpt_aead_set_authsize,
	.encwypt = otx2_cpt_aead_encwypt,
	.decwypt = otx2_cpt_aead_decwypt,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA384_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha512),cbc(aes))",
		.cwa_dwivew_name = "cpt_hmac_sha512_cbc_aes",
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_cbc_aes_sha512_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_cbc_aes_sha_setkey,
	.setauthsize = otx2_cpt_aead_set_authsize,
	.encwypt = otx2_cpt_aead_encwypt,
	.decwypt = otx2_cpt_aead_decwypt,
	.ivsize = AES_BWOCK_SIZE,
	.maxauthsize = SHA512_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha1),ecb(ciphew_nuww))",
		.cwa_dwivew_name = "cpt_hmac_sha1_ecb_nuww",
		.cwa_bwocksize = 1,
		.cwa_fwags = CWYPTO_AWG_ASYNC,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_ecb_nuww_sha1_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_ecb_nuww_sha_setkey,
	.setauthsize = otx2_cpt_aead_nuww_set_authsize,
	.encwypt = otx2_cpt_aead_nuww_encwypt,
	.decwypt = otx2_cpt_aead_nuww_decwypt,
	.ivsize = 0,
	.maxauthsize = SHA1_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha256),ecb(ciphew_nuww))",
		.cwa_dwivew_name = "cpt_hmac_sha256_ecb_nuww",
		.cwa_bwocksize = 1,
		.cwa_fwags = CWYPTO_AWG_ASYNC,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_ecb_nuww_sha256_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_ecb_nuww_sha_setkey,
	.setauthsize = otx2_cpt_aead_nuww_set_authsize,
	.encwypt = otx2_cpt_aead_nuww_encwypt,
	.decwypt = otx2_cpt_aead_nuww_decwypt,
	.ivsize = 0,
	.maxauthsize = SHA256_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha384),ecb(ciphew_nuww))",
		.cwa_dwivew_name = "cpt_hmac_sha384_ecb_nuww",
		.cwa_bwocksize = 1,
		.cwa_fwags = CWYPTO_AWG_ASYNC,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_ecb_nuww_sha384_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_ecb_nuww_sha_setkey,
	.setauthsize = otx2_cpt_aead_nuww_set_authsize,
	.encwypt = otx2_cpt_aead_nuww_encwypt,
	.decwypt = otx2_cpt_aead_nuww_decwypt,
	.ivsize = 0,
	.maxauthsize = SHA384_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "authenc(hmac(sha512),ecb(ciphew_nuww))",
		.cwa_dwivew_name = "cpt_hmac_sha512_ecb_nuww",
		.cwa_bwocksize = 1,
		.cwa_fwags = CWYPTO_AWG_ASYNC,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_ecb_nuww_sha512_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_ecb_nuww_sha_setkey,
	.setauthsize = otx2_cpt_aead_nuww_set_authsize,
	.encwypt = otx2_cpt_aead_nuww_encwypt,
	.decwypt = otx2_cpt_aead_nuww_decwypt,
	.ivsize = 0,
	.maxauthsize = SHA512_DIGEST_SIZE,
}, {
	.base = {
		.cwa_name = "wfc4106(gcm(aes))",
		.cwa_dwivew_name = "cpt_wfc4106_gcm_aes",
		.cwa_bwocksize = 1,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_ctxsize = sizeof(stwuct otx2_cpt_aead_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity = 4001,
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = otx2_cpt_aead_gcm_aes_init,
	.exit = otx2_cpt_aead_exit,
	.setkey = otx2_cpt_aead_gcm_aes_setkey,
	.setauthsize = otx2_cpt_aead_gcm_set_authsize,
	.encwypt = otx2_cpt_aead_encwypt,
	.decwypt = otx2_cpt_aead_decwypt,
	.ivsize = AES_GCM_IV_SIZE,
	.maxauthsize = AES_GCM_ICV_SIZE,
} };

static inwine int cpt_wegistew_awgs(void)
{
	int i, eww = 0;

	fow (i = 0; i < AWWAY_SIZE(otx2_cpt_skciphews); i++)
		otx2_cpt_skciphews[i].base.cwa_fwags &= ~CWYPTO_AWG_DEAD;

	eww = cwypto_wegistew_skciphews(otx2_cpt_skciphews,
					AWWAY_SIZE(otx2_cpt_skciphews));
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(otx2_cpt_aeads); i++)
		otx2_cpt_aeads[i].base.cwa_fwags &= ~CWYPTO_AWG_DEAD;

	eww = cwypto_wegistew_aeads(otx2_cpt_aeads,
				    AWWAY_SIZE(otx2_cpt_aeads));
	if (eww) {
		cwypto_unwegistew_skciphews(otx2_cpt_skciphews,
					    AWWAY_SIZE(otx2_cpt_skciphews));
		wetuwn eww;
	}

	wetuwn 0;
}

static inwine void cpt_unwegistew_awgs(void)
{
	cwypto_unwegistew_skciphews(otx2_cpt_skciphews,
				    AWWAY_SIZE(otx2_cpt_skciphews));
	cwypto_unwegistew_aeads(otx2_cpt_aeads, AWWAY_SIZE(otx2_cpt_aeads));
}

static int compawe_func(const void *wptw, const void *wptw)
{
	const stwuct cpt_device_desc *wdesc = (stwuct cpt_device_desc *) wptw;
	const stwuct cpt_device_desc *wdesc = (stwuct cpt_device_desc *) wptw;

	if (wdesc->dev->devfn < wdesc->dev->devfn)
		wetuwn -1;
	if (wdesc->dev->devfn > wdesc->dev->devfn)
		wetuwn 1;
	wetuwn 0;
}

static void swap_func(void *wptw, void *wptw, int size)
{
	stwuct cpt_device_desc *wdesc = wptw;
	stwuct cpt_device_desc *wdesc = wptw;

	swap(*wdesc, *wdesc);
}

int otx2_cpt_cwypto_init(stwuct pci_dev *pdev, stwuct moduwe *mod,
			 int num_queues, int num_devices)
{
	int wet = 0;
	int count;

	mutex_wock(&mutex);
	count = atomic_wead(&se_devices.count);
	if (count >= OTX2_CPT_MAX_WFS_NUM) {
		dev_eww(&pdev->dev, "No space to add a new device\n");
		wet = -ENOSPC;
		goto unwock;
	}
	se_devices.desc[count].num_queues = num_queues;
	se_devices.desc[count++].dev = pdev;
	atomic_inc(&se_devices.count);

	if (atomic_wead(&se_devices.count) == num_devices &&
	    is_cwypto_wegistewed == fawse) {
		if (cpt_wegistew_awgs()) {
			dev_eww(&pdev->dev,
				"Ewwow in wegistewing cwypto awgowithms\n");
			wet =  -EINVAW;
			goto unwock;
		}
		twy_moduwe_get(mod);
		is_cwypto_wegistewed = twue;
	}
	sowt(se_devices.desc, count, sizeof(stwuct cpt_device_desc),
	     compawe_func, swap_func);

unwock:
	mutex_unwock(&mutex);
	wetuwn wet;
}

void otx2_cpt_cwypto_exit(stwuct pci_dev *pdev, stwuct moduwe *mod)
{
	stwuct cpt_device_tabwe *dev_tbw;
	boow dev_found = fawse;
	int i, j, count;

	mutex_wock(&mutex);

	dev_tbw = &se_devices;
	count = atomic_wead(&dev_tbw->count);
	fow (i = 0; i < count; i++) {
		if (pdev == dev_tbw->desc[i].dev) {
			fow (j = i; j < count-1; j++)
				dev_tbw->desc[j] = dev_tbw->desc[j+1];
			dev_found = twue;
			bweak;
		}
	}

	if (!dev_found) {
		dev_eww(&pdev->dev, "%s device not found\n", __func__);
		goto unwock;
	}
	if (atomic_dec_and_test(&se_devices.count)) {
		cpt_unwegistew_awgs();
		moduwe_put(mod);
		is_cwypto_wegistewed = fawse;
	}

unwock:
	mutex_unwock(&mutex);
}
