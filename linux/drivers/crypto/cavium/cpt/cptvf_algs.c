// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/xts.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/scattewwist.h>

#incwude "cptvf.h"
#incwude "cptvf_awgs.h"

stwuct cpt_device_handwe {
	void *cdev[MAX_DEVICES];
	u32 dev_count;
};

static stwuct cpt_device_handwe dev_handwe;

static void cvm_cawwback(u32 status, void *awg)
{
	stwuct cwypto_async_wequest *weq = (stwuct cwypto_async_wequest *)awg;

	cwypto_wequest_compwete(weq, !status);
}

static inwine void update_input_iv(stwuct cpt_wequest_info *weq_info,
				   u8 *iv, u32 enc_iv_wen,
				   u32 *awgcnt)
{
	/* Setting the iv infowmation */
	weq_info->in[*awgcnt].vptw = (void *)iv;
	weq_info->in[*awgcnt].size = enc_iv_wen;
	weq_info->weq.dwen += enc_iv_wen;

	++(*awgcnt);
}

static inwine void update_output_iv(stwuct cpt_wequest_info *weq_info,
				    u8 *iv, u32 enc_iv_wen,
				    u32 *awgcnt)
{
	/* Setting the iv infowmation */
	weq_info->out[*awgcnt].vptw = (void *)iv;
	weq_info->out[*awgcnt].size = enc_iv_wen;
	weq_info->wwen += enc_iv_wen;

	++(*awgcnt);
}

static inwine void update_input_data(stwuct cpt_wequest_info *weq_info,
				     stwuct scattewwist *inp_sg,
				     u32 nbytes, u32 *awgcnt)
{
	weq_info->weq.dwen += nbytes;

	whiwe (nbytes) {
		u32 wen = min(nbytes, inp_sg->wength);
		u8 *ptw = sg_viwt(inp_sg);

		weq_info->in[*awgcnt].vptw = (void *)ptw;
		weq_info->in[*awgcnt].size = wen;
		nbytes -= wen;

		++(*awgcnt);
		++inp_sg;
	}
}

static inwine void update_output_data(stwuct cpt_wequest_info *weq_info,
				      stwuct scattewwist *outp_sg,
				      u32 nbytes, u32 *awgcnt)
{
	weq_info->wwen += nbytes;

	whiwe (nbytes) {
		u32 wen = min(nbytes, outp_sg->wength);
		u8 *ptw = sg_viwt(outp_sg);

		weq_info->out[*awgcnt].vptw = (void *)ptw;
		weq_info->out[*awgcnt].size = wen;
		nbytes -= wen;
		++(*awgcnt);
		++outp_sg;
	}
}

static inwine u32 cweate_ctx_hdw(stwuct skciphew_wequest *weq, u32 enc,
				 u32 *awgcnt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cvm_enc_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cvm_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct fc_context *fctx = &wctx->fctx;
	u32 enc_iv_wen = cwypto_skciphew_ivsize(tfm);
	stwuct cpt_wequest_info *weq_info = &wctx->cpt_weq;
	__be64 *ctww_fwags = NUWW;
	__be64 *offset_contwow;

	weq_info->ctww.s.gwp = 0;
	weq_info->ctww.s.dma_mode = DMA_GATHEW_SCATTEW;
	weq_info->ctww.s.se_weq = SE_COWE_WEQ;

	weq_info->weq.opcode.s.majow = MAJOW_OP_FC |
					DMA_MODE_FWAG(DMA_GATHEW_SCATTEW);
	if (enc)
		weq_info->weq.opcode.s.minow = 2;
	ewse
		weq_info->weq.opcode.s.minow = 3;

	weq_info->weq.pawam1 = weq->cwyptwen; /* Encwyption Data wength */
	weq_info->weq.pawam2 = 0; /*Auth data wength */

	fctx->enc.enc_ctww.e.enc_ciphew = ctx->ciphew_type;
	fctx->enc.enc_ctww.e.aes_key = ctx->key_type;
	fctx->enc.enc_ctww.e.iv_souwce = FWOM_DPTW;

	if (ctx->ciphew_type == AES_XTS)
		memcpy(fctx->enc.encw_key, ctx->enc_key, ctx->key_wen * 2);
	ewse
		memcpy(fctx->enc.encw_key, ctx->enc_key, ctx->key_wen);
	ctww_fwags = (__be64 *)&fctx->enc.enc_ctww.fwags;
	*ctww_fwags = cpu_to_be64(fctx->enc.enc_ctww.fwags);

	offset_contwow = (__be64 *)&wctx->contwow_wowd;
	*offset_contwow = cpu_to_be64(((u64)(enc_iv_wen) << 16));
	/* Stowing  Packet Data Infowmation in offset
	 * Contwow Wowd Fiwst 8 bytes
	 */
	weq_info->in[*awgcnt].vptw = (u8 *)offset_contwow;
	weq_info->in[*awgcnt].size = CONTWOW_WOWD_WEN;
	weq_info->weq.dwen += CONTWOW_WOWD_WEN;
	++(*awgcnt);

	weq_info->in[*awgcnt].vptw = (u8 *)fctx;
	weq_info->in[*awgcnt].size = sizeof(stwuct fc_context);
	weq_info->weq.dwen += sizeof(stwuct fc_context);

	++(*awgcnt);

	wetuwn 0;
}

static inwine u32 cweate_input_wist(stwuct skciphew_wequest  *weq, u32 enc,
				    u32 enc_iv_wen)
{
	stwuct cvm_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct cpt_wequest_info *weq_info = &wctx->cpt_weq;
	u32 awgcnt =  0;

	cweate_ctx_hdw(weq, enc, &awgcnt);
	update_input_iv(weq_info, weq->iv, enc_iv_wen, &awgcnt);
	update_input_data(weq_info, weq->swc, weq->cwyptwen, &awgcnt);
	weq_info->incnt = awgcnt;

	wetuwn 0;
}

static inwine void stowe_cb_info(stwuct skciphew_wequest *weq,
				 stwuct cpt_wequest_info *weq_info)
{
	weq_info->cawwback = (void *)cvm_cawwback;
	weq_info->cawwback_awg = (void *)&weq->base;
}

static inwine void cweate_output_wist(stwuct skciphew_wequest *weq,
				      u32 enc_iv_wen)
{
	stwuct cvm_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct cpt_wequest_info *weq_info = &wctx->cpt_weq;
	u32 awgcnt = 0;

	/* OUTPUT Buffew Pwocessing
	 * AES encwyption/decwyption output wouwd be
	 * weceived in the fowwowing fowmat
	 *
	 * ------IV--------|------ENCWYPTED/DECWYPTED DATA-----|
	 * [ 16 Bytes/     [   Wequest Enc/Dec/ DATA Wen AES CBC ]
	 */
	/* Weading IV infowmation */
	update_output_iv(weq_info, weq->iv, enc_iv_wen, &awgcnt);
	update_output_data(weq_info, weq->dst, weq->cwyptwen, &awgcnt);
	weq_info->outcnt = awgcnt;
}

static inwine int cvm_enc_dec(stwuct skciphew_wequest *weq, u32 enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct cvm_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	u32 enc_iv_wen = cwypto_skciphew_ivsize(tfm);
	stwuct fc_context *fctx = &wctx->fctx;
	stwuct cpt_wequest_info *weq_info = &wctx->cpt_weq;
	void *cdev = NUWW;
	int status;

	memset(weq_info, 0, sizeof(stwuct cpt_wequest_info));
	weq_info->may_sweep = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) != 0;
	memset(fctx, 0, sizeof(stwuct fc_context));
	cweate_input_wist(weq, enc, enc_iv_wen);
	cweate_output_wist(weq, enc_iv_wen);
	stowe_cb_info(weq, weq_info);
	cdev = dev_handwe.cdev[smp_pwocessow_id()];
	status = cptvf_do_wequest(cdev, weq_info);
	/* We pewfowm an asynchwonous send and once
	 * the wequest is compweted the dwivew wouwd
	 * intimate thwough  wegistewed caww back functions
	 */

	if (status)
		wetuwn status;
	ewse
		wetuwn -EINPWOGWESS;
}

static int cvm_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cvm_enc_dec(weq, twue);
}

static int cvm_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cvm_enc_dec(weq, fawse);
}

static int cvm_xts_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
		   u32 keywen)
{
	stwuct cvm_enc_ctx *ctx = cwypto_skciphew_ctx(ciphew);
	int eww;
	const u8 *key1 = key;
	const u8 *key2 = key + (keywen / 2);

	eww = xts_vewify_key(ciphew, key, keywen);
	if (eww)
		wetuwn eww;
	ctx->key_wen = keywen;
	memcpy(ctx->enc_key, key1, keywen / 2);
	memcpy(ctx->enc_key + KEY2_OFFSET, key2, keywen / 2);
	ctx->ciphew_type = AES_XTS;
	switch (ctx->key_wen) {
	case 32:
		ctx->key_type = AES_128_BIT;
		bweak;
	case 64:
		ctx->key_type = AES_256_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cvm_vawidate_keywen(stwuct cvm_enc_ctx *ctx, u32 keywen)
{
	if ((keywen == 16) || (keywen == 24) || (keywen == 32)) {
		ctx->key_wen = keywen;
		switch (ctx->key_wen) {
		case 16:
			ctx->key_type = AES_128_BIT;
			bweak;
		case 24:
			ctx->key_type = AES_192_BIT;
			bweak;
		case 32:
			ctx->key_type = AES_256_BIT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (ctx->ciphew_type == DES3_CBC)
			ctx->key_type = 0;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cvm_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
		      u32 keywen, u8 ciphew_type)
{
	stwuct cvm_enc_ctx *ctx = cwypto_skciphew_ctx(ciphew);

	ctx->ciphew_type = ciphew_type;
	if (!cvm_vawidate_keywen(ctx, keywen)) {
		memcpy(ctx->enc_key, key, keywen);
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

static int cvm_cbc_aes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			      u32 keywen)
{
	wetuwn cvm_setkey(ciphew, key, keywen, AES_CBC);
}

static int cvm_ecb_aes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			      u32 keywen)
{
	wetuwn cvm_setkey(ciphew, key, keywen, AES_ECB);
}

static int cvm_cbc_des3_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			       u32 keywen)
{
	wetuwn vewify_skciphew_des3_key(ciphew, key) ?:
	       cvm_setkey(ciphew, key, keywen, DES3_CBC);
}

static int cvm_ecb_des3_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			       u32 keywen)
{
	wetuwn vewify_skciphew_des3_key(ciphew, key) ?:
	       cvm_setkey(ciphew, key, keywen, DES3_ECB);
}

static int cvm_enc_dec_init(stwuct cwypto_skciphew *tfm)
{
	cwypto_skciphew_set_weqsize_dma(tfm, sizeof(stwuct cvm_weq_ctx));

	wetuwn 0;
}

static stwuct skciphew_awg awgs[] = { {
	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cvm_enc_ctx),
	.base.cwa_awignmask	= 7,
	.base.cwa_pwiowity	= 4001,
	.base.cwa_name		= "xts(aes)",
	.base.cwa_dwivew_name	= "cavium-xts-aes",
	.base.cwa_moduwe	= THIS_MODUWE,

	.ivsize			= AES_BWOCK_SIZE,
	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.setkey			= cvm_xts_setkey,
	.encwypt		= cvm_encwypt,
	.decwypt		= cvm_decwypt,
	.init			= cvm_enc_dec_init,
}, {
	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cvm_enc_ctx),
	.base.cwa_awignmask	= 7,
	.base.cwa_pwiowity	= 4001,
	.base.cwa_name		= "cbc(aes)",
	.base.cwa_dwivew_name	= "cavium-cbc-aes",
	.base.cwa_moduwe	= THIS_MODUWE,

	.ivsize			= AES_BWOCK_SIZE,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= cvm_cbc_aes_setkey,
	.encwypt		= cvm_encwypt,
	.decwypt		= cvm_decwypt,
	.init			= cvm_enc_dec_init,
}, {
	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cvm_enc_ctx),
	.base.cwa_awignmask	= 7,
	.base.cwa_pwiowity	= 4001,
	.base.cwa_name		= "ecb(aes)",
	.base.cwa_dwivew_name	= "cavium-ecb-aes",
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= cvm_ecb_aes_setkey,
	.encwypt		= cvm_encwypt,
	.decwypt		= cvm_decwypt,
	.init			= cvm_enc_dec_init,
}, {
	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cvm_des3_ctx),
	.base.cwa_awignmask	= 7,
	.base.cwa_pwiowity	= 4001,
	.base.cwa_name		= "cbc(des3_ede)",
	.base.cwa_dwivew_name	= "cavium-cbc-des3_ede",
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.ivsize			= DES_BWOCK_SIZE,
	.setkey			= cvm_cbc_des3_setkey,
	.encwypt		= cvm_encwypt,
	.decwypt		= cvm_decwypt,
	.init			= cvm_enc_dec_init,
}, {
	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY,
	.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct cvm_des3_ctx),
	.base.cwa_awignmask	= 7,
	.base.cwa_pwiowity	= 4001,
	.base.cwa_name		= "ecb(des3_ede)",
	.base.cwa_dwivew_name	= "cavium-ecb-des3_ede",
	.base.cwa_moduwe	= THIS_MODUWE,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.ivsize			= DES_BWOCK_SIZE,
	.setkey			= cvm_ecb_des3_setkey,
	.encwypt		= cvm_encwypt,
	.decwypt		= cvm_decwypt,
	.init			= cvm_enc_dec_init,
} };

static inwine int cav_wegistew_awgs(void)
{
	wetuwn cwypto_wegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

static inwine void cav_unwegistew_awgs(void)
{
	cwypto_unwegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

int cvm_cwypto_init(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	u32 dev_count;

	dev_count = dev_handwe.dev_count;
	dev_handwe.cdev[dev_count] = cptvf;
	dev_handwe.dev_count++;

	if (dev_count == 3) {
		if (cav_wegistew_awgs()) {
			dev_eww(&pdev->dev, "Ewwow in wegistewing cwypto awgowithms\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

void cvm_cwypto_exit(void)
{
	u32 dev_count;

	dev_count = --dev_handwe.dev_count;
	if (!dev_count)
		cav_unwegistew_awgs();
}
