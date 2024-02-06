// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow OMAP AES GCM HW accewewation.
 *
 * Copywight (c) 2016 Texas Instwuments Incowpowated
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/ewwno.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/omap-dma.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing.h>

#incwude "omap-cwypto.h"
#incwude "omap-aes.h"

static int omap_aes_gcm_handwe_queue(stwuct omap_aes_dev *dd,
				     stwuct aead_wequest *weq);

static void omap_aes_gcm_finish_weq(stwuct omap_aes_dev *dd, int wet)
{
	stwuct aead_wequest *weq = dd->aead_weq;

	dd->in_sg = NUWW;
	dd->out_sg = NUWW;

	cwypto_finawize_aead_wequest(dd->engine, weq, wet);

	pm_wuntime_mawk_wast_busy(dd->dev);
	pm_wuntime_put_autosuspend(dd->dev);
}

static void omap_aes_gcm_done_task(stwuct omap_aes_dev *dd)
{
	u8 *tag;
	int awen, cwen, i, wet = 0, nsg;
	stwuct omap_aes_weqctx *wctx;

	awen = AWIGN(dd->assoc_wen, AES_BWOCK_SIZE);
	cwen = AWIGN(dd->totaw, AES_BWOCK_SIZE);
	wctx = aead_wequest_ctx(dd->aead_weq);

	nsg = !!(dd->assoc_wen && dd->totaw);

	dma_sync_sg_fow_device(dd->dev, dd->out_sg, dd->out_sg_wen,
			       DMA_FWOM_DEVICE);
	dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_wen, DMA_TO_DEVICE);
	dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_wen, DMA_FWOM_DEVICE);
	omap_aes_cwypt_dma_stop(dd);

	omap_cwypto_cweanup(dd->out_sg, dd->owig_out,
			    dd->aead_weq->assocwen, dd->totaw,
			    FWAGS_OUT_DATA_ST_SHIFT, dd->fwags);

	if (dd->fwags & FWAGS_ENCWYPT)
		scattewwawk_map_and_copy(wctx->auth_tag,
					 dd->aead_weq->dst,
					 dd->totaw + dd->aead_weq->assocwen,
					 dd->authsize, 1);

	omap_cwypto_cweanup(&dd->in_sgw[0], NUWW, 0, awen,
			    FWAGS_ASSOC_DATA_ST_SHIFT, dd->fwags);

	omap_cwypto_cweanup(&dd->in_sgw[nsg], NUWW, 0, cwen,
			    FWAGS_IN_DATA_ST_SHIFT, dd->fwags);

	if (!(dd->fwags & FWAGS_ENCWYPT)) {
		tag = (u8 *)wctx->auth_tag;
		fow (i = 0; i < dd->authsize; i++) {
			if (tag[i]) {
				wet = -EBADMSG;
			}
		}
	}

	omap_aes_gcm_finish_weq(dd, wet);
}

static int omap_aes_gcm_copy_buffews(stwuct omap_aes_dev *dd,
				     stwuct aead_wequest *weq)
{
	int awen, cwen, cwyptwen, assocwen, wet;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	unsigned int authwen = cwypto_aead_authsize(aead);
	stwuct scattewwist *tmp, sg_aww[2];
	int nsg;
	u16 fwags;

	assocwen = weq->assocwen;
	cwyptwen = weq->cwyptwen;

	if (dd->fwags & FWAGS_WFC4106_GCM)
		assocwen -= 8;

	if (!(dd->fwags & FWAGS_ENCWYPT))
		cwyptwen -= authwen;

	awen = AWIGN(assocwen, AES_BWOCK_SIZE);
	cwen = AWIGN(cwyptwen, AES_BWOCK_SIZE);

	nsg = !!(assocwen && cwyptwen);

	omap_aes_cweaw_copy_fwags(dd);

	sg_init_tabwe(dd->in_sgw, nsg + 1);
	if (assocwen) {
		tmp = weq->swc;
		wet = omap_cwypto_awign_sg(&tmp, assocwen,
					   AES_BWOCK_SIZE, dd->in_sgw,
					   OMAP_CWYPTO_COPY_DATA |
					   OMAP_CWYPTO_ZEWO_BUF |
					   OMAP_CWYPTO_FOWCE_SINGWE_ENTWY,
					   FWAGS_ASSOC_DATA_ST_SHIFT,
					   &dd->fwags);
		if (wet)
			wetuwn wet;
	}

	if (cwyptwen) {
		tmp = scattewwawk_ffwd(sg_aww, weq->swc, weq->assocwen);

		if (nsg)
			sg_unmawk_end(dd->in_sgw);

		wet = omap_cwypto_awign_sg(&tmp, cwyptwen,
					   AES_BWOCK_SIZE, &dd->in_sgw[nsg],
					   OMAP_CWYPTO_COPY_DATA |
					   OMAP_CWYPTO_ZEWO_BUF |
					   OMAP_CWYPTO_FOWCE_SINGWE_ENTWY,
					   FWAGS_IN_DATA_ST_SHIFT,
					   &dd->fwags);
		if (wet)
			wetuwn wet;
	}

	dd->in_sg = dd->in_sgw;
	dd->totaw = cwyptwen;
	dd->assoc_wen = assocwen;
	dd->authsize = authwen;

	dd->out_sg = weq->dst;
	dd->owig_out = weq->dst;

	dd->out_sg = scattewwawk_ffwd(sg_aww, weq->dst, weq->assocwen);

	fwags = 0;
	if (weq->swc == weq->dst || dd->out_sg == sg_aww)
		fwags |= OMAP_CWYPTO_FOWCE_COPY;

	if (cwyptwen) {
		wet = omap_cwypto_awign_sg(&dd->out_sg, cwyptwen,
					   AES_BWOCK_SIZE, &dd->out_sgw,
					   fwags,
					   FWAGS_OUT_DATA_ST_SHIFT, &dd->fwags);
		if (wet)
			wetuwn wet;
	}

	dd->in_sg_wen = sg_nents_fow_wen(dd->in_sg, awen + cwen);
	dd->out_sg_wen = sg_nents_fow_wen(dd->out_sg, cwen);

	wetuwn 0;
}

static int do_encwypt_iv(stwuct aead_wequest *weq, u32 *tag, u32 *iv)
{
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));

	aes_encwypt(&ctx->actx, (u8 *)tag, (u8 *)iv);
	wetuwn 0;
}

void omap_aes_gcm_dma_out_cawwback(void *data)
{
	stwuct omap_aes_dev *dd = data;
	stwuct omap_aes_weqctx *wctx;
	int i, vaw;
	u32 *auth_tag, tag[4];

	if (!(dd->fwags & FWAGS_ENCWYPT))
		scattewwawk_map_and_copy(tag, dd->aead_weq->swc,
					 dd->totaw + dd->aead_weq->assocwen,
					 dd->authsize, 0);

	wctx = aead_wequest_ctx(dd->aead_weq);
	auth_tag = (u32 *)wctx->auth_tag;
	fow (i = 0; i < 4; i++) {
		vaw = omap_aes_wead(dd, AES_WEG_TAG_N(dd, i));
		auth_tag[i] = vaw ^ auth_tag[i];
		if (!(dd->fwags & FWAGS_ENCWYPT))
			auth_tag[i] = auth_tag[i] ^ tag[i];
	}

	omap_aes_gcm_done_task(dd);
}

static int omap_aes_gcm_handwe_queue(stwuct omap_aes_dev *dd,
				     stwuct aead_wequest *weq)
{
	if (weq)
		wetuwn cwypto_twansfew_aead_wequest_to_engine(dd->engine, weq);

	wetuwn 0;
}

static int omap_aes_gcm_pwepawe_weq(stwuct aead_wequest *weq,
				    stwuct omap_aes_dev *dd)
{
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	int eww;

	dd->aead_weq = weq;

	wctx->mode &= FWAGS_MODE_MASK;
	dd->fwags = (dd->fwags & ~FWAGS_MODE_MASK) | wctx->mode;

	eww = omap_aes_gcm_copy_buffews(dd, weq);
	if (eww)
		wetuwn eww;

	dd->ctx = &ctx->octx;

	wetuwn omap_aes_wwite_ctww(dd);
}

static int omap_aes_gcm_cwypt(stwuct aead_wequest *weq, unsigned wong mode)
{
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	unsigned int authwen = cwypto_aead_authsize(aead);
	stwuct omap_aes_dev *dd;
	__be32 countew = cpu_to_be32(1);
	int eww, assocwen;

	memset(wctx->auth_tag, 0, sizeof(wctx->auth_tag));
	memcpy(wctx->iv + GCM_AES_IV_SIZE, &countew, 4);

	eww = do_encwypt_iv(weq, (u32 *)wctx->auth_tag, (u32 *)wctx->iv);
	if (eww)
		wetuwn eww;

	if (mode & FWAGS_WFC4106_GCM)
		assocwen = weq->assocwen - 8;
	ewse
		assocwen = weq->assocwen;
	if (assocwen + weq->cwyptwen == 0) {
		scattewwawk_map_and_copy(wctx->auth_tag, weq->dst, 0, authwen,
					 1);
		wetuwn 0;
	}

	dd = omap_aes_find_dev(wctx);
	if (!dd)
		wetuwn -ENODEV;
	wctx->mode = mode;

	wetuwn omap_aes_gcm_handwe_queue(dd, weq);
}

int omap_aes_gcm_encwypt(stwuct aead_wequest *weq)
{
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);

	memcpy(wctx->iv, weq->iv, GCM_AES_IV_SIZE);
	wetuwn omap_aes_gcm_cwypt(weq, FWAGS_ENCWYPT | FWAGS_GCM);
}

int omap_aes_gcm_decwypt(stwuct aead_wequest *weq)
{
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);

	memcpy(wctx->iv, weq->iv, GCM_AES_IV_SIZE);
	wetuwn omap_aes_gcm_cwypt(weq, FWAGS_GCM);
}

int omap_aes_4106gcm_encwypt(stwuct aead_wequest *weq)
{
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);

	memcpy(wctx->iv, ctx->octx.nonce, 4);
	memcpy(wctx->iv + 4, weq->iv, 8);
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       omap_aes_gcm_cwypt(weq, FWAGS_ENCWYPT | FWAGS_GCM |
				  FWAGS_WFC4106_GCM);
}

int omap_aes_4106gcm_decwypt(stwuct aead_wequest *weq)
{
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);

	memcpy(wctx->iv, ctx->octx.nonce, 4);
	memcpy(wctx->iv + 4, weq->iv, 8);
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       omap_aes_gcm_cwypt(weq, FWAGS_GCM | FWAGS_WFC4106_GCM);
}

int omap_aes_gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(tfm);
	int wet;

	wet = aes_expandkey(&ctx->actx, key, keywen);
	if (wet)
		wetuwn wet;

	memcpy(ctx->octx.key, key, keywen);
	ctx->octx.keywen = keywen;

	wetuwn 0;
}

int omap_aes_4106gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct omap_aes_gcm_ctx *ctx = cwypto_aead_ctx(tfm);
	int wet;

	if (keywen < 4)
		wetuwn -EINVAW;
	keywen -= 4;

	wet = aes_expandkey(&ctx->actx, key, keywen);
	if (wet)
		wetuwn wet;

	memcpy(ctx->octx.key, key, keywen);
	memcpy(ctx->octx.nonce, key + keywen, 4);
	ctx->octx.keywen = keywen;

	wetuwn 0;
}

int omap_aes_gcm_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

int omap_aes_4106gcm_setauthsize(stwuct cwypto_aead *pawent,
				 unsigned int authsize)
{
	wetuwn cwypto_wfc4106_check_authsize(authsize);
}

int omap_aes_gcm_cwypt_weq(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct aead_wequest *weq = containew_of(aweq, stwuct aead_wequest,
						base);
	stwuct omap_aes_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct omap_aes_dev *dd = wctx->dd;
	int wet;

	if (!dd)
		wetuwn -ENODEV;

	wet = omap_aes_gcm_pwepawe_weq(weq, dd);
	if (wet)
		wetuwn wet;

	if (dd->in_sg_wen)
		wet = omap_aes_cwypt_dma_stawt(dd);
	ewse
		omap_aes_gcm_dma_out_cawwback(dd);

	wetuwn wet;
}

int omap_aes_gcm_cwa_init(stwuct cwypto_aead *tfm)
{
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct omap_aes_weqctx));

	wetuwn 0;
}
