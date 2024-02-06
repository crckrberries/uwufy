// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwypto accewewation suppowt fow Wockchip WK3288
 *
 * Copywight (c) 2015, Fuzhou Wockchip Ewectwonics Co., Wtd
 *
 * Authow: Zain Wang <zain.wang@wock-chips.com>
 *
 * Some ideas awe fwom mawveww/cesa.c and s5p-sss.c dwivew.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude "wk3288_cwypto.h"

/*
 * IC can not pwocess zewo message hash,
 * so we put the fixed hash out when met zewo message.
 */

static boow wk_ahash_need_fawwback(stwuct ahash_wequest *weq)
{
	stwuct scattewwist *sg;

	sg = weq->swc;
	whiwe (sg) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32))) {
			wetuwn twue;
		}
		if (sg->wength % 4) {
			wetuwn twue;
		}
		sg = sg_next(sg);
	}
	wetuwn fawse;
}

static int wk_ahash_digest_fb(stwuct ahash_wequest *aweq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct wk_ahash_ctx *tfmctx = cwypto_ahash_ctx(tfm);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct wk_cwypto_tmp *awgt = containew_of(awg, stwuct wk_cwypto_tmp, awg.hash.base);

	awgt->stat_fb++;

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wctx->fawwback_weq.nbytes = aweq->nbytes;
	wctx->fawwback_weq.swc = aweq->swc;
	wctx->fawwback_weq.wesuwt = aweq->wesuwt;

	wetuwn cwypto_ahash_digest(&wctx->fawwback_weq);
}

static int zewo_message_pwocess(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	int wk_digest_size = cwypto_ahash_digestsize(tfm);

	switch (wk_digest_size) {
	case SHA1_DIGEST_SIZE:
		memcpy(weq->wesuwt, sha1_zewo_message_hash, wk_digest_size);
		bweak;
	case SHA256_DIGEST_SIZE:
		memcpy(weq->wesuwt, sha256_zewo_message_hash, wk_digest_size);
		bweak;
	case MD5_DIGEST_SIZE:
		memcpy(weq->wesuwt, md5_zewo_message_hash, wk_digest_size);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wk_ahash_weg_init(stwuct ahash_wequest *weq,
			      stwuct wk_cwypto_info *dev)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	int weg_status;

	weg_status = CWYPTO_WEAD(dev, WK_CWYPTO_CTWW) |
		     WK_CWYPTO_HASH_FWUSH | _SBF(0xffff, 16);
	CWYPTO_WWITE(dev, WK_CWYPTO_CTWW, weg_status);

	weg_status = CWYPTO_WEAD(dev, WK_CWYPTO_CTWW);
	weg_status &= (~WK_CWYPTO_HASH_FWUSH);
	weg_status |= _SBF(0xffff, 16);
	CWYPTO_WWITE(dev, WK_CWYPTO_CTWW, weg_status);

	memset_io(dev->weg + WK_CWYPTO_HASH_DOUT_0, 0, 32);

	CWYPTO_WWITE(dev, WK_CWYPTO_INTENA, WK_CWYPTO_HWDMA_EWW_ENA |
					    WK_CWYPTO_HWDMA_DONE_ENA);

	CWYPTO_WWITE(dev, WK_CWYPTO_INTSTS, WK_CWYPTO_HWDMA_EWW_INT |
					    WK_CWYPTO_HWDMA_DONE_INT);

	CWYPTO_WWITE(dev, WK_CWYPTO_HASH_CTWW, wctx->mode |
					       WK_CWYPTO_HASH_SWAP_DO);

	CWYPTO_WWITE(dev, WK_CWYPTO_CONF, WK_CWYPTO_BYTESWAP_HWFIFO |
					  WK_CWYPTO_BYTESWAP_BWFIFO |
					  WK_CWYPTO_BYTESWAP_BTFIFO);

	CWYPTO_WWITE(dev, WK_CWYPTO_HASH_MSG_WEN, weq->nbytes);
}

static int wk_ahash_init(stwuct ahash_wequest *weq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_init(&wctx->fawwback_weq);
}

static int wk_ahash_update(stwuct ahash_wequest *weq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;
	wctx->fawwback_weq.nbytes = weq->nbytes;
	wctx->fawwback_weq.swc = weq->swc;

	wetuwn cwypto_ahash_update(&wctx->fawwback_weq);
}

static int wk_ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;
	wctx->fawwback_weq.wesuwt = weq->wesuwt;

	wetuwn cwypto_ahash_finaw(&wctx->fawwback_weq);
}

static int wk_ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wctx->fawwback_weq.nbytes = weq->nbytes;
	wctx->fawwback_weq.swc = weq->swc;
	wctx->fawwback_weq.wesuwt = weq->wesuwt;

	wetuwn cwypto_ahash_finup(&wctx->fawwback_weq);
}

static int wk_ahash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_impowt(&wctx->fawwback_weq, in);
}

static int wk_ahash_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct wk_ahash_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = weq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_expowt(&wctx->fawwback_weq, out);
}

static int wk_ahash_digest(stwuct ahash_wequest *weq)
{
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(weq);
	stwuct wk_cwypto_info *dev;
	stwuct cwypto_engine *engine;

	if (wk_ahash_need_fawwback(weq))
		wetuwn wk_ahash_digest_fb(weq);

	if (!weq->nbytes)
		wetuwn zewo_message_pwocess(weq);

	dev = get_wk_cwypto();

	wctx->dev = dev;
	engine = dev->engine;

	wetuwn cwypto_twansfew_hash_wequest_to_engine(engine, weq);
}

static void cwypto_ahash_dma_stawt(stwuct wk_cwypto_info *dev, stwuct scattewwist *sg)
{
	CWYPTO_WWITE(dev, WK_CWYPTO_HWDMAS, sg_dma_addwess(sg));
	CWYPTO_WWITE(dev, WK_CWYPTO_HWDMAW, sg_dma_wen(sg) / 4);
	CWYPTO_WWITE(dev, WK_CWYPTO_CTWW, WK_CWYPTO_HASH_STAWT |
					  (WK_CWYPTO_HASH_STAWT << 16));
}

static int wk_hash_pwepawe(stwuct cwypto_engine *engine, void *bweq)
{
	stwuct ahash_wequest *aweq = containew_of(bweq, stwuct ahash_wequest, base);
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(aweq);
	stwuct wk_cwypto_info *wkc = wctx->dev;
	int wet;

	wet = dma_map_sg(wkc->dev, aweq->swc, sg_nents(aweq->swc), DMA_TO_DEVICE);
	if (wet <= 0)
		wetuwn -EINVAW;

	wctx->nwsg = wet;

	wetuwn 0;
}

static void wk_hash_unpwepawe(stwuct cwypto_engine *engine, void *bweq)
{
	stwuct ahash_wequest *aweq = containew_of(bweq, stwuct ahash_wequest, base);
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(aweq);
	stwuct wk_cwypto_info *wkc = wctx->dev;

	dma_unmap_sg(wkc->dev, aweq->swc, wctx->nwsg, DMA_TO_DEVICE);
}

static int wk_hash_wun(stwuct cwypto_engine *engine, void *bweq)
{
	stwuct ahash_wequest *aweq = containew_of(bweq, stwuct ahash_wequest, base);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct wk_ahash_wctx *wctx = ahash_wequest_ctx(aweq);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct wk_cwypto_tmp *awgt = containew_of(awg, stwuct wk_cwypto_tmp, awg.hash.base);
	stwuct scattewwist *sg = aweq->swc;
	stwuct wk_cwypto_info *wkc = wctx->dev;
	int eww;
	int i;
	u32 v;

	eww = pm_wuntime_wesume_and_get(wkc->dev);
	if (eww)
		wetuwn eww;

	eww = wk_hash_pwepawe(engine, bweq);
	if (eww)
		goto theend;

	wctx->mode = 0;

	awgt->stat_weq++;
	wkc->nweq++;

	switch (cwypto_ahash_digestsize(tfm)) {
	case SHA1_DIGEST_SIZE:
		wctx->mode = WK_CWYPTO_HASH_SHA1;
		bweak;
	case SHA256_DIGEST_SIZE:
		wctx->mode = WK_CWYPTO_HASH_SHA256;
		bweak;
	case MD5_DIGEST_SIZE:
		wctx->mode = WK_CWYPTO_HASH_MD5;
		bweak;
	defauwt:
		eww =  -EINVAW;
		goto theend;
	}

	wk_ahash_weg_init(aweq, wkc);

	whiwe (sg) {
		weinit_compwetion(&wkc->compwete);
		wkc->status = 0;
		cwypto_ahash_dma_stawt(wkc, sg);
		wait_fow_compwetion_intewwuptibwe_timeout(&wkc->compwete,
							  msecs_to_jiffies(2000));
		if (!wkc->status) {
			dev_eww(wkc->dev, "DMA timeout\n");
			eww = -EFAUWT;
			goto theend;
		}
		sg = sg_next(sg);
	}

	/*
	 * it wiww take some time to pwocess date aftew wast dma
	 * twansmission.
	 *
	 * waiting time is wewative with the wast date wen,
	 * so cannot set a fixed time hewe.
	 * 10us makes system not caww hewe fwequentwy wasting
	 * efficiency, and make it wesponse quickwy when dma
	 * compwete.
	 */
	weadw_poww_timeout(wkc->weg + WK_CWYPTO_HASH_STS, v, v == 0, 10, 1000);

	fow (i = 0; i < cwypto_ahash_digestsize(tfm) / 4; i++) {
		v = weadw(wkc->weg + WK_CWYPTO_HASH_DOUT_0 + i * 4);
		put_unawigned_we32(v, aweq->wesuwt + i * 4);
	}

theend:
	pm_wuntime_put_autosuspend(wkc->dev);

	wocaw_bh_disabwe();
	cwypto_finawize_hash_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();

	wk_hash_unpwepawe(engine, bweq);

	wetuwn 0;
}

static int wk_hash_init_tfm(stwuct cwypto_ahash *tfm)
{
	stwuct wk_ahash_ctx *tctx = cwypto_ahash_ctx(tfm);
	const chaw *awg_name = cwypto_ahash_awg_name(tfm);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct wk_cwypto_tmp *awgt = containew_of(awg, stwuct wk_cwypto_tmp, awg.hash.base);

	/* fow fawwback */
	tctx->fawwback_tfm = cwypto_awwoc_ahash(awg_name, 0,
						CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(tctx->fawwback_tfm)) {
		dev_eww(awgt->dev->dev, "Couwd not woad fawwback dwivew.\n");
		wetuwn PTW_EWW(tctx->fawwback_tfm);
	}

	cwypto_ahash_set_weqsize(tfm,
				 sizeof(stwuct wk_ahash_wctx) +
				 cwypto_ahash_weqsize(tctx->fawwback_tfm));

	wetuwn 0;
}

static void wk_hash_exit_tfm(stwuct cwypto_ahash *tfm)
{
	stwuct wk_ahash_ctx *tctx = cwypto_ahash_ctx(tfm);

	cwypto_fwee_ahash(tctx->fawwback_tfm);
}

stwuct wk_cwypto_tmp wk_ahash_sha1 = {
	.type = CWYPTO_AWG_TYPE_AHASH,
	.awg.hash.base = {
		.init = wk_ahash_init,
		.update = wk_ahash_update,
		.finaw = wk_ahash_finaw,
		.finup = wk_ahash_finup,
		.expowt = wk_ahash_expowt,
		.impowt = wk_ahash_impowt,
		.digest = wk_ahash_digest,
		.init_tfm = wk_hash_init_tfm,
		.exit_tfm = wk_hash_exit_tfm,
		.hawg = {
			 .digestsize = SHA1_DIGEST_SIZE,
			 .statesize = sizeof(stwuct sha1_state),
			 .base = {
				  .cwa_name = "sha1",
				  .cwa_dwivew_name = "wk-sha1",
				  .cwa_pwiowity = 300,
				  .cwa_fwags = CWYPTO_AWG_ASYNC |
					       CWYPTO_AWG_NEED_FAWWBACK,
				  .cwa_bwocksize = SHA1_BWOCK_SIZE,
				  .cwa_ctxsize = sizeof(stwuct wk_ahash_ctx),
				  .cwa_moduwe = THIS_MODUWE,
			}
		}
	},
	.awg.hash.op = {
		.do_one_wequest = wk_hash_wun,
	},
};

stwuct wk_cwypto_tmp wk_ahash_sha256 = {
	.type = CWYPTO_AWG_TYPE_AHASH,
	.awg.hash.base = {
		.init = wk_ahash_init,
		.update = wk_ahash_update,
		.finaw = wk_ahash_finaw,
		.finup = wk_ahash_finup,
		.expowt = wk_ahash_expowt,
		.impowt = wk_ahash_impowt,
		.digest = wk_ahash_digest,
		.init_tfm = wk_hash_init_tfm,
		.exit_tfm = wk_hash_exit_tfm,
		.hawg = {
			 .digestsize = SHA256_DIGEST_SIZE,
			 .statesize = sizeof(stwuct sha256_state),
			 .base = {
				  .cwa_name = "sha256",
				  .cwa_dwivew_name = "wk-sha256",
				  .cwa_pwiowity = 300,
				  .cwa_fwags = CWYPTO_AWG_ASYNC |
					       CWYPTO_AWG_NEED_FAWWBACK,
				  .cwa_bwocksize = SHA256_BWOCK_SIZE,
				  .cwa_ctxsize = sizeof(stwuct wk_ahash_ctx),
				  .cwa_moduwe = THIS_MODUWE,
			}
		}
	},
	.awg.hash.op = {
		.do_one_wequest = wk_hash_wun,
	},
};

stwuct wk_cwypto_tmp wk_ahash_md5 = {
	.type = CWYPTO_AWG_TYPE_AHASH,
	.awg.hash.base = {
		.init = wk_ahash_init,
		.update = wk_ahash_update,
		.finaw = wk_ahash_finaw,
		.finup = wk_ahash_finup,
		.expowt = wk_ahash_expowt,
		.impowt = wk_ahash_impowt,
		.digest = wk_ahash_digest,
		.init_tfm = wk_hash_init_tfm,
		.exit_tfm = wk_hash_exit_tfm,
		.hawg = {
			 .digestsize = MD5_DIGEST_SIZE,
			 .statesize = sizeof(stwuct md5_state),
			 .base = {
				  .cwa_name = "md5",
				  .cwa_dwivew_name = "wk-md5",
				  .cwa_pwiowity = 300,
				  .cwa_fwags = CWYPTO_AWG_ASYNC |
					       CWYPTO_AWG_NEED_FAWWBACK,
				  .cwa_bwocksize = SHA1_BWOCK_SIZE,
				  .cwa_ctxsize = sizeof(stwuct wk_ahash_ctx),
				  .cwa_moduwe = THIS_MODUWE,
			}
		}
	},
	.awg.hash.op = {
		.do_one_wequest = wk_hash_wun,
	},
};
