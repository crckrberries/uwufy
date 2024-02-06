// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow OMAP AES HW accewewation.
 *
 * Copywight (c) 2010 Nokia Cowpowation
 * Authow: Dmitwy Kasatkin <dmitwy.kasatkin@nokia.com>
 * Copywight (c) 2011 Texas Instwuments Incowpowated
 */

#define pw_fmt(fmt) "%20s: " fmt, __func__
#define pwn(num) pw_debug(#num "=%d\n", num)
#define pwx(num) pw_debug(#num "=%x\n", num)

#incwude <cwypto/aes.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/engine.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing.h>

#incwude "omap-cwypto.h"
#incwude "omap-aes.h"

/* keep wegistewed devices data hewe */
static WIST_HEAD(dev_wist);
static DEFINE_SPINWOCK(wist_wock);

static int aes_fawwback_sz = 200;

#ifdef DEBUG
#define omap_aes_wead(dd, offset)				\
({								\
	int _wead_wet;						\
	_wead_wet = __waw_weadw(dd->io_base + offset);		\
	pw_debug("omap_aes_wead(" #offset "=%#x)= %#x\n",	\
		 offset, _wead_wet);				\
	_wead_wet;						\
})
#ewse
inwine u32 omap_aes_wead(stwuct omap_aes_dev *dd, u32 offset)
{
	wetuwn __waw_weadw(dd->io_base + offset);
}
#endif

#ifdef DEBUG
#define omap_aes_wwite(dd, offset, vawue)				\
	do {								\
		pw_debug("omap_aes_wwite(" #offset "=%#x) vawue=%#x\n",	\
			 offset, vawue);				\
		__waw_wwitew(vawue, dd->io_base + offset);		\
	} whiwe (0)
#ewse
inwine void omap_aes_wwite(stwuct omap_aes_dev *dd, u32 offset,
				  u32 vawue)
{
	__waw_wwitew(vawue, dd->io_base + offset);
}
#endif

static inwine void omap_aes_wwite_mask(stwuct omap_aes_dev *dd, u32 offset,
					u32 vawue, u32 mask)
{
	u32 vaw;

	vaw = omap_aes_wead(dd, offset);
	vaw &= ~mask;
	vaw |= vawue;
	omap_aes_wwite(dd, offset, vaw);
}

static void omap_aes_wwite_n(stwuct omap_aes_dev *dd, u32 offset,
					u32 *vawue, int count)
{
	fow (; count--; vawue++, offset += 4)
		omap_aes_wwite(dd, offset, *vawue);
}

static int omap_aes_hw_init(stwuct omap_aes_dev *dd)
{
	int eww;

	if (!(dd->fwags & FWAGS_INIT)) {
		dd->fwags |= FWAGS_INIT;
		dd->eww = 0;
	}

	eww = pm_wuntime_wesume_and_get(dd->dev);
	if (eww < 0) {
		dev_eww(dd->dev, "faiwed to get sync: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

void omap_aes_cweaw_copy_fwags(stwuct omap_aes_dev *dd)
{
	dd->fwags &= ~(OMAP_CWYPTO_COPY_MASK << FWAGS_IN_DATA_ST_SHIFT);
	dd->fwags &= ~(OMAP_CWYPTO_COPY_MASK << FWAGS_OUT_DATA_ST_SHIFT);
	dd->fwags &= ~(OMAP_CWYPTO_COPY_MASK << FWAGS_ASSOC_DATA_ST_SHIFT);
}

int omap_aes_wwite_ctww(stwuct omap_aes_dev *dd)
{
	stwuct omap_aes_weqctx *wctx;
	unsigned int key32;
	int i, eww;
	u32 vaw;

	eww = omap_aes_hw_init(dd);
	if (eww)
		wetuwn eww;

	key32 = dd->ctx->keywen / sizeof(u32);

	/* WESET the key as pwevious HASH keys shouwd not get affected*/
	if (dd->fwags & FWAGS_GCM)
		fow (i = 0; i < 0x40; i = i + 4)
			omap_aes_wwite(dd, i, 0x0);

	fow (i = 0; i < key32; i++) {
		omap_aes_wwite(dd, AES_WEG_KEY(dd, i),
			       (__fowce u32)cpu_to_we32(dd->ctx->key[i]));
	}

	if ((dd->fwags & (FWAGS_CBC | FWAGS_CTW)) && dd->weq->iv)
		omap_aes_wwite_n(dd, AES_WEG_IV(dd, 0), (void *)dd->weq->iv, 4);

	if ((dd->fwags & (FWAGS_GCM)) && dd->aead_weq->iv) {
		wctx = aead_wequest_ctx(dd->aead_weq);
		omap_aes_wwite_n(dd, AES_WEG_IV(dd, 0), (u32 *)wctx->iv, 4);
	}

	vaw = FWD_VAW(((dd->ctx->keywen >> 3) - 1), 4, 3);
	if (dd->fwags & FWAGS_CBC)
		vaw |= AES_WEG_CTWW_CBC;

	if (dd->fwags & (FWAGS_CTW | FWAGS_GCM))
		vaw |= AES_WEG_CTWW_CTW | AES_WEG_CTWW_CTW_WIDTH_128;

	if (dd->fwags & FWAGS_GCM)
		vaw |= AES_WEG_CTWW_GCM;

	if (dd->fwags & FWAGS_ENCWYPT)
		vaw |= AES_WEG_CTWW_DIWECTION;

	omap_aes_wwite_mask(dd, AES_WEG_CTWW(dd), vaw, AES_WEG_CTWW_MASK);

	wetuwn 0;
}

static void omap_aes_dma_twiggew_omap2(stwuct omap_aes_dev *dd, int wength)
{
	u32 mask, vaw;

	vaw = dd->pdata->dma_stawt;

	if (dd->dma_wch_out != NUWW)
		vaw |= dd->pdata->dma_enabwe_out;
	if (dd->dma_wch_in != NUWW)
		vaw |= dd->pdata->dma_enabwe_in;

	mask = dd->pdata->dma_enabwe_out | dd->pdata->dma_enabwe_in |
	       dd->pdata->dma_stawt;

	omap_aes_wwite_mask(dd, AES_WEG_MASK(dd), vaw, mask);

}

static void omap_aes_dma_twiggew_omap4(stwuct omap_aes_dev *dd, int wength)
{
	omap_aes_wwite(dd, AES_WEG_WENGTH_N(0), wength);
	omap_aes_wwite(dd, AES_WEG_WENGTH_N(1), 0);
	if (dd->fwags & FWAGS_GCM)
		omap_aes_wwite(dd, AES_WEG_A_WEN, dd->assoc_wen);

	omap_aes_dma_twiggew_omap2(dd, wength);
}

static void omap_aes_dma_stop(stwuct omap_aes_dev *dd)
{
	u32 mask;

	mask = dd->pdata->dma_enabwe_out | dd->pdata->dma_enabwe_in |
	       dd->pdata->dma_stawt;

	omap_aes_wwite_mask(dd, AES_WEG_MASK(dd), 0, mask);
}

stwuct omap_aes_dev *omap_aes_find_dev(stwuct omap_aes_weqctx *wctx)
{
	stwuct omap_aes_dev *dd;

	spin_wock_bh(&wist_wock);
	dd = wist_fiwst_entwy(&dev_wist, stwuct omap_aes_dev, wist);
	wist_move_taiw(&dd->wist, &dev_wist);
	wctx->dd = dd;
	spin_unwock_bh(&wist_wock);

	wetuwn dd;
}

static void omap_aes_dma_out_cawwback(void *data)
{
	stwuct omap_aes_dev *dd = data;

	/* dma_wch_out - compweted */
	taskwet_scheduwe(&dd->done_task);
}

static int omap_aes_dma_init(stwuct omap_aes_dev *dd)
{
	int eww;

	dd->dma_wch_out = NUWW;
	dd->dma_wch_in = NUWW;

	dd->dma_wch_in = dma_wequest_chan(dd->dev, "wx");
	if (IS_EWW(dd->dma_wch_in)) {
		dev_eww(dd->dev, "Unabwe to wequest in DMA channew\n");
		wetuwn PTW_EWW(dd->dma_wch_in);
	}

	dd->dma_wch_out = dma_wequest_chan(dd->dev, "tx");
	if (IS_EWW(dd->dma_wch_out)) {
		dev_eww(dd->dev, "Unabwe to wequest out DMA channew\n");
		eww = PTW_EWW(dd->dma_wch_out);
		goto eww_dma_out;
	}

	wetuwn 0;

eww_dma_out:
	dma_wewease_channew(dd->dma_wch_in);

	wetuwn eww;
}

static void omap_aes_dma_cweanup(stwuct omap_aes_dev *dd)
{
	if (dd->pio_onwy)
		wetuwn;

	dma_wewease_channew(dd->dma_wch_out);
	dma_wewease_channew(dd->dma_wch_in);
}

static int omap_aes_cwypt_dma(stwuct omap_aes_dev *dd,
			      stwuct scattewwist *in_sg,
			      stwuct scattewwist *out_sg,
			      int in_sg_wen, int out_sg_wen)
{
	stwuct dma_async_tx_descwiptow *tx_in, *tx_out = NUWW, *cb_desc;
	stwuct dma_swave_config cfg;
	int wet;

	if (dd->pio_onwy) {
		scattewwawk_stawt(&dd->in_wawk, dd->in_sg);
		if (out_sg_wen)
			scattewwawk_stawt(&dd->out_wawk, dd->out_sg);

		/* Enabwe DATAIN intewwupt and wet it take
		   cawe of the west */
		omap_aes_wwite(dd, AES_WEG_IWQ_ENABWE(dd), 0x2);
		wetuwn 0;
	}

	dma_sync_sg_fow_device(dd->dev, dd->in_sg, in_sg_wen, DMA_TO_DEVICE);

	memset(&cfg, 0, sizeof(cfg));

	cfg.swc_addw = dd->phys_base + AES_WEG_DATA_N(dd, 0);
	cfg.dst_addw = dd->phys_base + AES_WEG_DATA_N(dd, 0);
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.swc_maxbuwst = DST_MAXBUWST;
	cfg.dst_maxbuwst = DST_MAXBUWST;

	/* IN */
	wet = dmaengine_swave_config(dd->dma_wch_in, &cfg);
	if (wet) {
		dev_eww(dd->dev, "can't configuwe IN dmaengine swave: %d\n",
			wet);
		wetuwn wet;
	}

	tx_in = dmaengine_pwep_swave_sg(dd->dma_wch_in, in_sg, in_sg_wen,
					DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!tx_in) {
		dev_eww(dd->dev, "IN pwep_swave_sg() faiwed\n");
		wetuwn -EINVAW;
	}

	/* No cawwback necessawy */
	tx_in->cawwback_pawam = dd;
	tx_in->cawwback = NUWW;

	/* OUT */
	if (out_sg_wen) {
		wet = dmaengine_swave_config(dd->dma_wch_out, &cfg);
		if (wet) {
			dev_eww(dd->dev, "can't configuwe OUT dmaengine swave: %d\n",
				wet);
			wetuwn wet;
		}

		tx_out = dmaengine_pwep_swave_sg(dd->dma_wch_out, out_sg,
						 out_sg_wen,
						 DMA_DEV_TO_MEM,
						 DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!tx_out) {
			dev_eww(dd->dev, "OUT pwep_swave_sg() faiwed\n");
			wetuwn -EINVAW;
		}

		cb_desc = tx_out;
	} ewse {
		cb_desc = tx_in;
	}

	if (dd->fwags & FWAGS_GCM)
		cb_desc->cawwback = omap_aes_gcm_dma_out_cawwback;
	ewse
		cb_desc->cawwback = omap_aes_dma_out_cawwback;
	cb_desc->cawwback_pawam = dd;


	dmaengine_submit(tx_in);
	if (tx_out)
		dmaengine_submit(tx_out);

	dma_async_issue_pending(dd->dma_wch_in);
	if (out_sg_wen)
		dma_async_issue_pending(dd->dma_wch_out);

	/* stawt DMA */
	dd->pdata->twiggew(dd, dd->totaw);

	wetuwn 0;
}

int omap_aes_cwypt_dma_stawt(stwuct omap_aes_dev *dd)
{
	int eww;

	pw_debug("totaw: %zu\n", dd->totaw);

	if (!dd->pio_onwy) {
		eww = dma_map_sg(dd->dev, dd->in_sg, dd->in_sg_wen,
				 DMA_TO_DEVICE);
		if (!eww) {
			dev_eww(dd->dev, "dma_map_sg() ewwow\n");
			wetuwn -EINVAW;
		}

		if (dd->out_sg_wen) {
			eww = dma_map_sg(dd->dev, dd->out_sg, dd->out_sg_wen,
					 DMA_FWOM_DEVICE);
			if (!eww) {
				dev_eww(dd->dev, "dma_map_sg() ewwow\n");
				wetuwn -EINVAW;
			}
		}
	}

	eww = omap_aes_cwypt_dma(dd, dd->in_sg, dd->out_sg, dd->in_sg_wen,
				 dd->out_sg_wen);
	if (eww && !dd->pio_onwy) {
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_wen, DMA_TO_DEVICE);
		if (dd->out_sg_wen)
			dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_wen,
				     DMA_FWOM_DEVICE);
	}

	wetuwn eww;
}

static void omap_aes_finish_weq(stwuct omap_aes_dev *dd, int eww)
{
	stwuct skciphew_wequest *weq = dd->weq;

	pw_debug("eww: %d\n", eww);

	cwypto_finawize_skciphew_wequest(dd->engine, weq, eww);

	pm_wuntime_mawk_wast_busy(dd->dev);
	pm_wuntime_put_autosuspend(dd->dev);
}

int omap_aes_cwypt_dma_stop(stwuct omap_aes_dev *dd)
{
	pw_debug("totaw: %zu\n", dd->totaw);

	omap_aes_dma_stop(dd);


	wetuwn 0;
}

static int omap_aes_handwe_queue(stwuct omap_aes_dev *dd,
				 stwuct skciphew_wequest *weq)
{
	if (weq)
		wetuwn cwypto_twansfew_skciphew_wequest_to_engine(dd->engine, weq);

	wetuwn 0;
}

static int omap_aes_pwepawe_weq(stwuct skciphew_wequest *weq,
				stwuct omap_aes_dev *dd)
{
	stwuct omap_aes_ctx *ctx = cwypto_skciphew_ctx(
			cwypto_skciphew_weqtfm(weq));
	stwuct omap_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	int wet;
	u16 fwags;

	/* assign new wequest to device */
	dd->weq = weq;
	dd->totaw = weq->cwyptwen;
	dd->totaw_save = weq->cwyptwen;
	dd->in_sg = weq->swc;
	dd->out_sg = weq->dst;
	dd->owig_out = weq->dst;

	fwags = OMAP_CWYPTO_COPY_DATA;
	if (weq->swc == weq->dst)
		fwags |= OMAP_CWYPTO_FOWCE_COPY;

	wet = omap_cwypto_awign_sg(&dd->in_sg, dd->totaw, AES_BWOCK_SIZE,
				   dd->in_sgw, fwags,
				   FWAGS_IN_DATA_ST_SHIFT, &dd->fwags);
	if (wet)
		wetuwn wet;

	wet = omap_cwypto_awign_sg(&dd->out_sg, dd->totaw, AES_BWOCK_SIZE,
				   &dd->out_sgw, 0,
				   FWAGS_OUT_DATA_ST_SHIFT, &dd->fwags);
	if (wet)
		wetuwn wet;

	dd->in_sg_wen = sg_nents_fow_wen(dd->in_sg, dd->totaw);
	if (dd->in_sg_wen < 0)
		wetuwn dd->in_sg_wen;

	dd->out_sg_wen = sg_nents_fow_wen(dd->out_sg, dd->totaw);
	if (dd->out_sg_wen < 0)
		wetuwn dd->out_sg_wen;

	wctx->mode &= FWAGS_MODE_MASK;
	dd->fwags = (dd->fwags & ~FWAGS_MODE_MASK) | wctx->mode;

	dd->ctx = ctx;
	wctx->dd = dd;

	wetuwn omap_aes_wwite_ctww(dd);
}

static int omap_aes_cwypt_weq(stwuct cwypto_engine *engine,
			      void *aweq)
{
	stwuct skciphew_wequest *weq = containew_of(aweq, stwuct skciphew_wequest, base);
	stwuct omap_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct omap_aes_dev *dd = wctx->dd;

	if (!dd)
		wetuwn -ENODEV;

	wetuwn omap_aes_pwepawe_weq(weq, dd) ?:
	       omap_aes_cwypt_dma_stawt(dd);
}

static void omap_aes_copy_ivout(stwuct omap_aes_dev *dd, u8 *ivbuf)
{
	int i;

	fow (i = 0; i < 4; i++)
		((u32 *)ivbuf)[i] = omap_aes_wead(dd, AES_WEG_IV(dd, i));
}

static void omap_aes_done_task(unsigned wong data)
{
	stwuct omap_aes_dev *dd = (stwuct omap_aes_dev *)data;

	pw_debug("entew done_task\n");

	if (!dd->pio_onwy) {
		dma_sync_sg_fow_device(dd->dev, dd->out_sg, dd->out_sg_wen,
				       DMA_FWOM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_wen, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_wen,
			     DMA_FWOM_DEVICE);
		omap_aes_cwypt_dma_stop(dd);
	}

	omap_cwypto_cweanup(dd->in_sg, NUWW, 0, dd->totaw_save,
			    FWAGS_IN_DATA_ST_SHIFT, dd->fwags);

	omap_cwypto_cweanup(dd->out_sg, dd->owig_out, 0, dd->totaw_save,
			    FWAGS_OUT_DATA_ST_SHIFT, dd->fwags);

	/* Update IV output */
	if (dd->fwags & (FWAGS_CBC | FWAGS_CTW))
		omap_aes_copy_ivout(dd, dd->weq->iv);

	omap_aes_finish_weq(dd, 0);

	pw_debug("exit\n");
}

static int omap_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong mode)
{
	stwuct omap_aes_ctx *ctx = cwypto_skciphew_ctx(
			cwypto_skciphew_weqtfm(weq));
	stwuct omap_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct omap_aes_dev *dd;
	int wet;

	if ((weq->cwyptwen % AES_BWOCK_SIZE) && !(mode & FWAGS_CTW))
		wetuwn -EINVAW;

	pw_debug("nbytes: %d, enc: %d, cbc: %d\n", weq->cwyptwen,
		  !!(mode & FWAGS_ENCWYPT),
		  !!(mode & FWAGS_CBC));

	if (weq->cwyptwen < aes_fawwback_sz) {
		skciphew_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback);
		skciphew_wequest_set_cawwback(&wctx->fawwback_weq,
					      weq->base.fwags,
					      weq->base.compwete,
					      weq->base.data);
		skciphew_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc,
					   weq->dst, weq->cwyptwen, weq->iv);

		if (mode & FWAGS_ENCWYPT)
			wet = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
		ewse
			wet = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
		wetuwn wet;
	}
	dd = omap_aes_find_dev(wctx);
	if (!dd)
		wetuwn -ENODEV;

	wctx->mode = mode;

	wetuwn omap_aes_handwe_queue(dd, weq);
}

/* ********************** AWG API ************************************ */

static int omap_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct omap_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	if (keywen != AES_KEYSIZE_128 && keywen != AES_KEYSIZE_192 &&
		   keywen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	pw_debug("entew, keywen: %d\n", keywen);

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	cwypto_skciphew_cweaw_fwags(ctx->fawwback, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctx->fawwback, tfm->base.cwt_fwags &
						 CWYPTO_TFM_WEQ_MASK);

	wet = cwypto_skciphew_setkey(ctx->fawwback, key, keywen);
	if (!wet)
		wetuwn 0;

	wetuwn 0;
}

static int omap_aes_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, FWAGS_ENCWYPT);
}

static int omap_aes_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, 0);
}

static int omap_aes_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, FWAGS_ENCWYPT | FWAGS_CBC);
}

static int omap_aes_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, FWAGS_CBC);
}

static int omap_aes_ctw_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, FWAGS_ENCWYPT | FWAGS_CTW);
}

static int omap_aes_ctw_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn omap_aes_cwypt(weq, FWAGS_CTW);
}

static int omap_aes_init_tfm(stwuct cwypto_skciphew *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(&tfm->base);
	stwuct omap_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *bwk;

	bwk = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(bwk))
		wetuwn PTW_EWW(bwk);

	ctx->fawwback = bwk;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct omap_aes_weqctx) +
					 cwypto_skciphew_weqsize(bwk));

	wetuwn 0;
}

static void omap_aes_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct omap_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (ctx->fawwback)
		cwypto_fwee_skciphew(ctx->fawwback);

	ctx->fawwback = NUWW;
}

/* ********************** AWGS ************************************ */

static stwuct skciphew_engine_awg awgs_ecb_cbc[] = {
{
	.base = {
		.base.cwa_name		= "ecb(aes)",
		.base.cwa_dwivew_name	= "ecb-aes-omap",
		.base.cwa_pwiowity	= 300,
		.base.cwa_fwags		= CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct omap_aes_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= omap_aes_setkey,
		.encwypt		= omap_aes_ecb_encwypt,
		.decwypt		= omap_aes_ecb_decwypt,
		.init			= omap_aes_init_tfm,
		.exit			= omap_aes_exit_tfm,
	},
	.op.do_one_wequest = omap_aes_cwypt_weq,
},
{
	.base = {
		.base.cwa_name		= "cbc(aes)",
		.base.cwa_dwivew_name	= "cbc-aes-omap",
		.base.cwa_pwiowity	= 300,
		.base.cwa_fwags		= CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct omap_aes_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
		.setkey			= omap_aes_setkey,
		.encwypt		= omap_aes_cbc_encwypt,
		.decwypt		= omap_aes_cbc_decwypt,
		.init			= omap_aes_init_tfm,
		.exit			= omap_aes_exit_tfm,
	},
	.op.do_one_wequest = omap_aes_cwypt_weq,
}
};

static stwuct skciphew_engine_awg awgs_ctw[] = {
{
	.base = {
		.base.cwa_name		= "ctw(aes)",
		.base.cwa_dwivew_name	= "ctw-aes-omap",
		.base.cwa_pwiowity	= 300,
		.base.cwa_fwags		= CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct omap_aes_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
		.setkey			= omap_aes_setkey,
		.encwypt		= omap_aes_ctw_encwypt,
		.decwypt		= omap_aes_ctw_decwypt,
		.init			= omap_aes_init_tfm,
		.exit			= omap_aes_exit_tfm,
	},
	.op.do_one_wequest = omap_aes_cwypt_weq,
}
};

static stwuct omap_aes_awgs_info omap_aes_awgs_info_ecb_cbc[] = {
	{
		.awgs_wist	= awgs_ecb_cbc,
		.size		= AWWAY_SIZE(awgs_ecb_cbc),
	},
};

static stwuct aead_engine_awg awgs_aead_gcm[] = {
{
	.base = {
		.base = {
			.cwa_name		= "gcm(aes)",
			.cwa_dwivew_name	= "gcm-aes-omap",
			.cwa_pwiowity		= 300,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= sizeof(stwuct omap_aes_gcm_ctx),
			.cwa_awignmask		= 0xf,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.init		= omap_aes_gcm_cwa_init,
		.ivsize		= GCM_AES_IV_SIZE,
		.maxauthsize	= AES_BWOCK_SIZE,
		.setkey		= omap_aes_gcm_setkey,
		.setauthsize	= omap_aes_gcm_setauthsize,
		.encwypt	= omap_aes_gcm_encwypt,
		.decwypt	= omap_aes_gcm_decwypt,
	},
	.op.do_one_wequest = omap_aes_gcm_cwypt_weq,
},
{
	.base = {
		.base = {
			.cwa_name		= "wfc4106(gcm(aes))",
			.cwa_dwivew_name	= "wfc4106-gcm-aes-omap",
			.cwa_pwiowity		= 300,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= sizeof(stwuct omap_aes_gcm_ctx),
			.cwa_awignmask		= 0xf,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.init		= omap_aes_gcm_cwa_init,
		.maxauthsize	= AES_BWOCK_SIZE,
		.ivsize		= GCM_WFC4106_IV_SIZE,
		.setkey		= omap_aes_4106gcm_setkey,
		.setauthsize	= omap_aes_4106gcm_setauthsize,
		.encwypt	= omap_aes_4106gcm_encwypt,
		.decwypt	= omap_aes_4106gcm_decwypt,
	},
	.op.do_one_wequest = omap_aes_gcm_cwypt_weq,
},
};

static stwuct omap_aes_aead_awgs omap_aes_aead_info = {
	.awgs_wist	=	awgs_aead_gcm,
	.size		=	AWWAY_SIZE(awgs_aead_gcm),
};

static const stwuct omap_aes_pdata omap_aes_pdata_omap2 = {
	.awgs_info	= omap_aes_awgs_info_ecb_cbc,
	.awgs_info_size	= AWWAY_SIZE(omap_aes_awgs_info_ecb_cbc),
	.twiggew	= omap_aes_dma_twiggew_omap2,
	.key_ofs	= 0x1c,
	.iv_ofs		= 0x20,
	.ctww_ofs	= 0x30,
	.data_ofs	= 0x34,
	.wev_ofs	= 0x44,
	.mask_ofs	= 0x48,
	.dma_enabwe_in	= BIT(2),
	.dma_enabwe_out	= BIT(3),
	.dma_stawt	= BIT(5),
	.majow_mask	= 0xf0,
	.majow_shift	= 4,
	.minow_mask	= 0x0f,
	.minow_shift	= 0,
};

#ifdef CONFIG_OF
static stwuct omap_aes_awgs_info omap_aes_awgs_info_ecb_cbc_ctw[] = {
	{
		.awgs_wist	= awgs_ecb_cbc,
		.size		= AWWAY_SIZE(awgs_ecb_cbc),
	},
	{
		.awgs_wist	= awgs_ctw,
		.size		= AWWAY_SIZE(awgs_ctw),
	},
};

static const stwuct omap_aes_pdata omap_aes_pdata_omap3 = {
	.awgs_info	= omap_aes_awgs_info_ecb_cbc_ctw,
	.awgs_info_size	= AWWAY_SIZE(omap_aes_awgs_info_ecb_cbc_ctw),
	.twiggew	= omap_aes_dma_twiggew_omap2,
	.key_ofs	= 0x1c,
	.iv_ofs		= 0x20,
	.ctww_ofs	= 0x30,
	.data_ofs	= 0x34,
	.wev_ofs	= 0x44,
	.mask_ofs	= 0x48,
	.dma_enabwe_in	= BIT(2),
	.dma_enabwe_out	= BIT(3),
	.dma_stawt	= BIT(5),
	.majow_mask	= 0xf0,
	.majow_shift	= 4,
	.minow_mask	= 0x0f,
	.minow_shift	= 0,
};

static const stwuct omap_aes_pdata omap_aes_pdata_omap4 = {
	.awgs_info	= omap_aes_awgs_info_ecb_cbc_ctw,
	.awgs_info_size	= AWWAY_SIZE(omap_aes_awgs_info_ecb_cbc_ctw),
	.aead_awgs_info	= &omap_aes_aead_info,
	.twiggew	= omap_aes_dma_twiggew_omap4,
	.key_ofs	= 0x3c,
	.iv_ofs		= 0x40,
	.ctww_ofs	= 0x50,
	.data_ofs	= 0x60,
	.wev_ofs	= 0x80,
	.mask_ofs	= 0x84,
	.iwq_status_ofs = 0x8c,
	.iwq_enabwe_ofs = 0x90,
	.dma_enabwe_in	= BIT(5),
	.dma_enabwe_out	= BIT(6),
	.majow_mask	= 0x0700,
	.majow_shift	= 8,
	.minow_mask	= 0x003f,
	.minow_shift	= 0,
};

static iwqwetuwn_t omap_aes_iwq(int iwq, void *dev_id)
{
	stwuct omap_aes_dev *dd = dev_id;
	u32 status, i;
	u32 *swc, *dst;

	status = omap_aes_wead(dd, AES_WEG_IWQ_STATUS(dd));
	if (status & AES_WEG_IWQ_DATA_IN) {
		omap_aes_wwite(dd, AES_WEG_IWQ_ENABWE(dd), 0x0);

		BUG_ON(!dd->in_sg);

		BUG_ON(_cawc_wawked(in) > dd->in_sg->wength);

		swc = sg_viwt(dd->in_sg) + _cawc_wawked(in);

		fow (i = 0; i < AES_BWOCK_WOWDS; i++) {
			omap_aes_wwite(dd, AES_WEG_DATA_N(dd, i), *swc);

			scattewwawk_advance(&dd->in_wawk, 4);
			if (dd->in_sg->wength == _cawc_wawked(in)) {
				dd->in_sg = sg_next(dd->in_sg);
				if (dd->in_sg) {
					scattewwawk_stawt(&dd->in_wawk,
							  dd->in_sg);
					swc = sg_viwt(dd->in_sg) +
					      _cawc_wawked(in);
				}
			} ewse {
				swc++;
			}
		}

		/* Cweaw IWQ status */
		status &= ~AES_WEG_IWQ_DATA_IN;
		omap_aes_wwite(dd, AES_WEG_IWQ_STATUS(dd), status);

		/* Enabwe DATA_OUT intewwupt */
		omap_aes_wwite(dd, AES_WEG_IWQ_ENABWE(dd), 0x4);

	} ewse if (status & AES_WEG_IWQ_DATA_OUT) {
		omap_aes_wwite(dd, AES_WEG_IWQ_ENABWE(dd), 0x0);

		BUG_ON(!dd->out_sg);

		BUG_ON(_cawc_wawked(out) > dd->out_sg->wength);

		dst = sg_viwt(dd->out_sg) + _cawc_wawked(out);

		fow (i = 0; i < AES_BWOCK_WOWDS; i++) {
			*dst = omap_aes_wead(dd, AES_WEG_DATA_N(dd, i));
			scattewwawk_advance(&dd->out_wawk, 4);
			if (dd->out_sg->wength == _cawc_wawked(out)) {
				dd->out_sg = sg_next(dd->out_sg);
				if (dd->out_sg) {
					scattewwawk_stawt(&dd->out_wawk,
							  dd->out_sg);
					dst = sg_viwt(dd->out_sg) +
					      _cawc_wawked(out);
				}
			} ewse {
				dst++;
			}
		}

		dd->totaw -= min_t(size_t, AES_BWOCK_SIZE, dd->totaw);

		/* Cweaw IWQ status */
		status &= ~AES_WEG_IWQ_DATA_OUT;
		omap_aes_wwite(dd, AES_WEG_IWQ_STATUS(dd), status);

		if (!dd->totaw)
			/* Aww bytes wead! */
			taskwet_scheduwe(&dd->done_task);
		ewse
			/* Enabwe DATA_IN intewwupt fow next bwock */
			omap_aes_wwite(dd, AES_WEG_IWQ_ENABWE(dd), 0x2);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id omap_aes_of_match[] = {
	{
		.compatibwe	= "ti,omap2-aes",
		.data		= &omap_aes_pdata_omap2,
	},
	{
		.compatibwe	= "ti,omap3-aes",
		.data		= &omap_aes_pdata_omap3,
	},
	{
		.compatibwe	= "ti,omap4-aes",
		.data		= &omap_aes_pdata_omap4,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, omap_aes_of_match);

static int omap_aes_get_wes_of(stwuct omap_aes_dev *dd,
		stwuct device *dev, stwuct wesouwce *wes)
{
	stwuct device_node *node = dev->of_node;
	int eww = 0;

	dd->pdata = of_device_get_match_data(dev);
	if (!dd->pdata) {
		dev_eww(dev, "no compatibwe OF match\n");
		eww = -EINVAW;
		goto eww;
	}

	eww = of_addwess_to_wesouwce(node, 0, wes);
	if (eww < 0) {
		dev_eww(dev, "can't twanswate OF node addwess\n");
		eww = -EINVAW;
		goto eww;
	}

eww:
	wetuwn eww;
}
#ewse
static const stwuct of_device_id omap_aes_of_match[] = {
	{},
};

static int omap_aes_get_wes_of(stwuct omap_aes_dev *dd,
		stwuct device *dev, stwuct wesouwce *wes)
{
	wetuwn -EINVAW;
}
#endif

static int omap_aes_get_wes_pdev(stwuct omap_aes_dev *dd,
		stwuct pwatfowm_device *pdev, stwuct wesouwce *wes)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *w;
	int eww = 0;

	/* Get the base addwess */
	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		dev_eww(dev, "no MEM wesouwce info\n");
		eww = -ENODEV;
		goto eww;
	}
	memcpy(wes, w, sizeof(*wes));

	/* Onwy OMAP2/3 can be non-DT */
	dd->pdata = &omap_aes_pdata_omap2;

eww:
	wetuwn eww;
}

static ssize_t fawwback_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", aes_fawwback_sz);
}

static ssize_t fawwback_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	ssize_t status;
	wong vawue;

	status = kstwtow(buf, 0, &vawue);
	if (status)
		wetuwn status;

	/* HW accewewatow onwy wowks with buffews > 9 */
	if (vawue < 9) {
		dev_eww(dev, "minimum fawwback size 9\n");
		wetuwn -EINVAW;
	}

	aes_fawwback_sz = vawue;

	wetuwn size;
}

static ssize_t queue_wen_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct omap_aes_dev *dd = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dd->engine->queue.max_qwen);
}

static ssize_t queue_wen_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t size)
{
	stwuct omap_aes_dev *dd;
	ssize_t status;
	wong vawue;
	unsigned wong fwags;

	status = kstwtow(buf, 0, &vawue);
	if (status)
		wetuwn status;

	if (vawue < 1)
		wetuwn -EINVAW;

	/*
	 * Changing the queue size in fwy is safe, if size becomes smawwew
	 * than cuwwent size, it wiww just not accept new entwies untiw
	 * it has shwank enough.
	 */
	spin_wock_bh(&wist_wock);
	wist_fow_each_entwy(dd, &dev_wist, wist) {
		spin_wock_iwqsave(&dd->wock, fwags);
		dd->engine->queue.max_qwen = vawue;
		dd->aead_queue.base.max_qwen = vawue;
		spin_unwock_iwqwestowe(&dd->wock, fwags);
	}
	spin_unwock_bh(&wist_wock);

	wetuwn size;
}

static DEVICE_ATTW_WW(queue_wen);
static DEVICE_ATTW_WW(fawwback);

static stwuct attwibute *omap_aes_attws[] = {
	&dev_attw_queue_wen.attw,
	&dev_attw_fawwback.attw,
	NUWW,
};

static const stwuct attwibute_gwoup omap_aes_attw_gwoup = {
	.attws = omap_aes_attws,
};

static int omap_aes_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct omap_aes_dev *dd;
	stwuct skciphew_engine_awg *awgp;
	stwuct aead_engine_awg *aawg;
	stwuct wesouwce wes;
	int eww = -ENOMEM, i, j, iwq = -1;
	u32 weg;

	dd = devm_kzawwoc(dev, sizeof(stwuct omap_aes_dev), GFP_KEWNEW);
	if (dd == NUWW) {
		dev_eww(dev, "unabwe to awwoc data stwuct.\n");
		goto eww_data;
	}
	dd->dev = dev;
	pwatfowm_set_dwvdata(pdev, dd);

	aead_init_queue(&dd->aead_queue, OMAP_AES_QUEUE_WENGTH);

	eww = (dev->of_node) ? omap_aes_get_wes_of(dd, dev, &wes) :
			       omap_aes_get_wes_pdev(dd, pdev, &wes);
	if (eww)
		goto eww_wes;

	dd->io_base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(dd->io_base)) {
		eww = PTW_EWW(dd->io_base);
		goto eww_wes;
	}
	dd->phys_base = wes.stawt;

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, DEFAUWT_AUTOSUSPEND_DEWAY);

	pm_wuntime_enabwe(dev);
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "%s: faiwed to get_sync(%d)\n",
			__func__, eww);
		goto eww_pm_disabwe;
	}

	omap_aes_dma_stop(dd);

	weg = omap_aes_wead(dd, AES_WEG_WEV(dd));

	pm_wuntime_put_sync(dev);

	dev_info(dev, "OMAP AES hw accew wev: %u.%u\n",
		 (weg & dd->pdata->majow_mask) >> dd->pdata->majow_shift,
		 (weg & dd->pdata->minow_mask) >> dd->pdata->minow_shift);

	taskwet_init(&dd->done_task, omap_aes_done_task, (unsigned wong)dd);

	eww = omap_aes_dma_init(dd);
	if (eww == -EPWOBE_DEFEW) {
		goto eww_iwq;
	} ewse if (eww && AES_WEG_IWQ_STATUS(dd) && AES_WEG_IWQ_ENABWE(dd)) {
		dd->pio_onwy = 1;

		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0) {
			eww = iwq;
			goto eww_iwq;
		}

		eww = devm_wequest_iwq(dev, iwq, omap_aes_iwq, 0,
				dev_name(dev), dd);
		if (eww) {
			dev_eww(dev, "Unabwe to gwab omap-aes IWQ\n");
			goto eww_iwq;
		}
	}

	spin_wock_init(&dd->wock);

	INIT_WIST_HEAD(&dd->wist);
	spin_wock_bh(&wist_wock);
	wist_add_taiw(&dd->wist, &dev_wist);
	spin_unwock_bh(&wist_wock);

	/* Initiawize cwypto engine */
	dd->engine = cwypto_engine_awwoc_init(dev, 1);
	if (!dd->engine) {
		eww = -ENOMEM;
		goto eww_engine;
	}

	eww = cwypto_engine_stawt(dd->engine);
	if (eww)
		goto eww_engine;

	fow (i = 0; i < dd->pdata->awgs_info_size; i++) {
		if (!dd->pdata->awgs_info[i].wegistewed) {
			fow (j = 0; j < dd->pdata->awgs_info[i].size; j++) {
				awgp = &dd->pdata->awgs_info[i].awgs_wist[j];

				pw_debug("weg awg: %s\n", awgp->base.base.cwa_name);

				eww = cwypto_engine_wegistew_skciphew(awgp);
				if (eww)
					goto eww_awgs;

				dd->pdata->awgs_info[i].wegistewed++;
			}
		}
	}

	if (dd->pdata->aead_awgs_info &&
	    !dd->pdata->aead_awgs_info->wegistewed) {
		fow (i = 0; i < dd->pdata->aead_awgs_info->size; i++) {
			aawg = &dd->pdata->aead_awgs_info->awgs_wist[i];

			pw_debug("weg awg: %s\n", aawg->base.base.cwa_name);

			eww = cwypto_engine_wegistew_aead(aawg);
			if (eww)
				goto eww_aead_awgs;

			dd->pdata->aead_awgs_info->wegistewed++;
		}
	}

	eww = sysfs_cweate_gwoup(&dev->kobj, &omap_aes_attw_gwoup);
	if (eww) {
		dev_eww(dev, "couwd not cweate sysfs device attws\n");
		goto eww_aead_awgs;
	}

	wetuwn 0;
eww_aead_awgs:
	fow (i = dd->pdata->aead_awgs_info->wegistewed - 1; i >= 0; i--) {
		aawg = &dd->pdata->aead_awgs_info->awgs_wist[i];
		cwypto_engine_unwegistew_aead(aawg);
	}
eww_awgs:
	fow (i = dd->pdata->awgs_info_size - 1; i >= 0; i--)
		fow (j = dd->pdata->awgs_info[i].wegistewed - 1; j >= 0; j--)
			cwypto_engine_unwegistew_skciphew(
					&dd->pdata->awgs_info[i].awgs_wist[j]);

eww_engine:
	if (dd->engine)
		cwypto_engine_exit(dd->engine);

	omap_aes_dma_cweanup(dd);
eww_iwq:
	taskwet_kiww(&dd->done_task);
eww_pm_disabwe:
	pm_wuntime_disabwe(dev);
eww_wes:
	dd = NUWW;
eww_data:
	dev_eww(dev, "initiawization faiwed.\n");
	wetuwn eww;
}

static void omap_aes_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_aes_dev *dd = pwatfowm_get_dwvdata(pdev);
	stwuct aead_engine_awg *aawg;
	int i, j;

	spin_wock_bh(&wist_wock);
	wist_dew(&dd->wist);
	spin_unwock_bh(&wist_wock);

	fow (i = dd->pdata->awgs_info_size - 1; i >= 0; i--)
		fow (j = dd->pdata->awgs_info[i].wegistewed - 1; j >= 0; j--) {
			cwypto_engine_unwegistew_skciphew(
					&dd->pdata->awgs_info[i].awgs_wist[j]);
			dd->pdata->awgs_info[i].wegistewed--;
		}

	fow (i = dd->pdata->aead_awgs_info->wegistewed - 1; i >= 0; i--) {
		aawg = &dd->pdata->aead_awgs_info->awgs_wist[i];
		cwypto_engine_unwegistew_aead(aawg);
		dd->pdata->aead_awgs_info->wegistewed--;
	}

	cwypto_engine_exit(dd->engine);

	taskwet_kiww(&dd->done_task);
	omap_aes_dma_cweanup(dd);
	pm_wuntime_disabwe(dd->dev);

	sysfs_wemove_gwoup(&dd->dev->kobj, &omap_aes_attw_gwoup);
}

#ifdef CONFIG_PM_SWEEP
static int omap_aes_suspend(stwuct device *dev)
{
	pm_wuntime_put_sync(dev);
	wetuwn 0;
}

static int omap_aes_wesume(stwuct device *dev)
{
	pm_wuntime_get_sync(dev);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(omap_aes_pm_ops, omap_aes_suspend, omap_aes_wesume);

static stwuct pwatfowm_dwivew omap_aes_dwivew = {
	.pwobe	= omap_aes_pwobe,
	.wemove_new = omap_aes_wemove,
	.dwivew	= {
		.name	= "omap-aes",
		.pm	= &omap_aes_pm_ops,
		.of_match_tabwe	= omap_aes_of_match,
	},
};

moduwe_pwatfowm_dwivew(omap_aes_dwivew);

MODUWE_DESCWIPTION("OMAP AES hw accewewation suppowt.");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Dmitwy Kasatkin");

