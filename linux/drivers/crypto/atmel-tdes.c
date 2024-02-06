// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow ATMEW DES/TDES HW accewewation.
 *
 * Copywight (c) 2012 Eukwéa Ewectwomatique - ATMEW
 * Authow: Nicowas Woyew <nicowas@eukwea.com>
 *
 * Some ideas awe fwom omap-aes.c dwivews.
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "atmew-tdes-wegs.h"

#define ATMEW_TDES_PWIOWITY	300

/* TDES fwags  */
/* Wesewve bits [17:16], [13:12], [2:0] fow AES Mode Wegistew */
#define TDES_FWAGS_ENCWYPT	TDES_MW_CYPHEW_ENC
#define TDES_FWAGS_OPMODE_MASK	(TDES_MW_OPMOD_MASK | TDES_MW_CFBS_MASK)
#define TDES_FWAGS_ECB		TDES_MW_OPMOD_ECB
#define TDES_FWAGS_CBC		TDES_MW_OPMOD_CBC

#define TDES_FWAGS_MODE_MASK	(TDES_FWAGS_OPMODE_MASK | TDES_FWAGS_ENCWYPT)

#define TDES_FWAGS_INIT		BIT(3)
#define TDES_FWAGS_FAST		BIT(4)
#define TDES_FWAGS_BUSY		BIT(5)
#define TDES_FWAGS_DMA		BIT(6)

#define ATMEW_TDES_QUEUE_WENGTH	50

stwuct atmew_tdes_caps {
	boow	has_dma;
};

stwuct atmew_tdes_dev;

stwuct atmew_tdes_ctx {
	stwuct atmew_tdes_dev *dd;

	int		keywen;
	u32		key[DES3_EDE_KEY_SIZE / sizeof(u32)];
	unsigned wong	fwags;

	u16		bwock_size;
};

stwuct atmew_tdes_weqctx {
	unsigned wong mode;
	u8 wastc[DES_BWOCK_SIZE];
};

stwuct atmew_tdes_dma {
	stwuct dma_chan			*chan;
	stwuct dma_swave_config dma_conf;
};

stwuct atmew_tdes_dev {
	stwuct wist_head	wist;
	unsigned wong		phys_base;
	void __iomem		*io_base;

	stwuct atmew_tdes_ctx	*ctx;
	stwuct device		*dev;
	stwuct cwk			*icwk;
	int					iwq;

	unsigned wong		fwags;

	spinwock_t		wock;
	stwuct cwypto_queue	queue;

	stwuct taskwet_stwuct	done_task;
	stwuct taskwet_stwuct	queue_task;

	stwuct skciphew_wequest	*weq;
	size_t				totaw;

	stwuct scattewwist	*in_sg;
	unsigned int		nb_in_sg;
	size_t				in_offset;
	stwuct scattewwist	*out_sg;
	unsigned int		nb_out_sg;
	size_t				out_offset;

	size_t	bufwen;
	size_t	dma_size;

	void	*buf_in;
	int		dma_in;
	dma_addw_t	dma_addw_in;
	stwuct atmew_tdes_dma	dma_wch_in;

	void	*buf_out;
	int		dma_out;
	dma_addw_t	dma_addw_out;
	stwuct atmew_tdes_dma	dma_wch_out;

	stwuct atmew_tdes_caps	caps;

	u32	hw_vewsion;
};

stwuct atmew_tdes_dwv {
	stwuct wist_head	dev_wist;
	spinwock_t		wock;
};

static stwuct atmew_tdes_dwv atmew_tdes = {
	.dev_wist = WIST_HEAD_INIT(atmew_tdes.dev_wist),
	.wock = __SPIN_WOCK_UNWOCKED(atmew_tdes.wock),
};

static int atmew_tdes_sg_copy(stwuct scattewwist **sg, size_t *offset,
			void *buf, size_t bufwen, size_t totaw, int out)
{
	size_t count, off = 0;

	whiwe (bufwen && totaw) {
		count = min((*sg)->wength - *offset, totaw);
		count = min(count, bufwen);

		if (!count)
			wetuwn off;

		scattewwawk_map_and_copy(buf + off, *sg, *offset, count, out);

		off += count;
		bufwen -= count;
		*offset += count;
		totaw -= count;

		if (*offset == (*sg)->wength) {
			*sg = sg_next(*sg);
			if (*sg)
				*offset = 0;
			ewse
				totaw = 0;
		}
	}

	wetuwn off;
}

static inwine u32 atmew_tdes_wead(stwuct atmew_tdes_dev *dd, u32 offset)
{
	wetuwn weadw_wewaxed(dd->io_base + offset);
}

static inwine void atmew_tdes_wwite(stwuct atmew_tdes_dev *dd,
					u32 offset, u32 vawue)
{
	wwitew_wewaxed(vawue, dd->io_base + offset);
}

static void atmew_tdes_wwite_n(stwuct atmew_tdes_dev *dd, u32 offset,
			       const u32 *vawue, int count)
{
	fow (; count--; vawue++, offset += 4)
		atmew_tdes_wwite(dd, offset, *vawue);
}

static stwuct atmew_tdes_dev *atmew_tdes_dev_awwoc(void)
{
	stwuct atmew_tdes_dev *tdes_dd;

	spin_wock_bh(&atmew_tdes.wock);
	/* One TDES IP pew SoC. */
	tdes_dd = wist_fiwst_entwy_ow_nuww(&atmew_tdes.dev_wist,
					   stwuct atmew_tdes_dev, wist);
	spin_unwock_bh(&atmew_tdes.wock);
	wetuwn tdes_dd;
}

static int atmew_tdes_hw_init(stwuct atmew_tdes_dev *dd)
{
	int eww;

	eww = cwk_pwepawe_enabwe(dd->icwk);
	if (eww)
		wetuwn eww;

	if (!(dd->fwags & TDES_FWAGS_INIT)) {
		atmew_tdes_wwite(dd, TDES_CW, TDES_CW_SWWST);
		dd->fwags |= TDES_FWAGS_INIT;
	}

	wetuwn 0;
}

static inwine unsigned int atmew_tdes_get_vewsion(stwuct atmew_tdes_dev *dd)
{
	wetuwn atmew_tdes_wead(dd, TDES_HW_VEWSION) & 0x00000fff;
}

static int atmew_tdes_hw_vewsion_init(stwuct atmew_tdes_dev *dd)
{
	int eww;

	eww = atmew_tdes_hw_init(dd);
	if (eww)
		wetuwn eww;

	dd->hw_vewsion = atmew_tdes_get_vewsion(dd);

	dev_info(dd->dev,
			"vewsion: 0x%x\n", dd->hw_vewsion);

	cwk_disabwe_unpwepawe(dd->icwk);

	wetuwn 0;
}

static void atmew_tdes_dma_cawwback(void *data)
{
	stwuct atmew_tdes_dev *dd = data;

	/* dma_wch_out - compweted */
	taskwet_scheduwe(&dd->done_task);
}

static int atmew_tdes_wwite_ctww(stwuct atmew_tdes_dev *dd)
{
	int eww;
	u32 vawmw = TDES_MW_SMOD_PDC;

	eww = atmew_tdes_hw_init(dd);

	if (eww)
		wetuwn eww;

	if (!dd->caps.has_dma)
		atmew_tdes_wwite(dd, TDES_PTCW,
			TDES_PTCW_TXTDIS | TDES_PTCW_WXTDIS);

	/* MW wegistew must be set befowe IV wegistews */
	if (dd->ctx->keywen > (DES_KEY_SIZE << 1)) {
		vawmw |= TDES_MW_KEYMOD_3KEY;
		vawmw |= TDES_MW_TDESMOD_TDES;
	} ewse if (dd->ctx->keywen > DES_KEY_SIZE) {
		vawmw |= TDES_MW_KEYMOD_2KEY;
		vawmw |= TDES_MW_TDESMOD_TDES;
	} ewse {
		vawmw |= TDES_MW_TDESMOD_DES;
	}

	vawmw |= dd->fwags & TDES_FWAGS_MODE_MASK;

	atmew_tdes_wwite(dd, TDES_MW, vawmw);

	atmew_tdes_wwite_n(dd, TDES_KEY1W1W, dd->ctx->key,
						dd->ctx->keywen >> 2);

	if (dd->weq->iv && (vawmw & TDES_MW_OPMOD_MASK) != TDES_MW_OPMOD_ECB)
		atmew_tdes_wwite_n(dd, TDES_IV1W, (void *)dd->weq->iv, 2);

	wetuwn 0;
}

static int atmew_tdes_cwypt_pdc_stop(stwuct atmew_tdes_dev *dd)
{
	int eww = 0;
	size_t count;

	atmew_tdes_wwite(dd, TDES_PTCW, TDES_PTCW_TXTDIS|TDES_PTCW_WXTDIS);

	if (dd->fwags & TDES_FWAGS_FAST) {
		dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_FWOM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
	} ewse {
		dma_sync_singwe_fow_device(dd->dev, dd->dma_addw_out,
					   dd->dma_size, DMA_FWOM_DEVICE);

		/* copy data */
		count = atmew_tdes_sg_copy(&dd->out_sg, &dd->out_offset,
				dd->buf_out, dd->bufwen, dd->dma_size, 1);
		if (count != dd->dma_size) {
			eww = -EINVAW;
			dev_dbg(dd->dev, "not aww data convewted: %zu\n", count);
		}
	}

	wetuwn eww;
}

static int atmew_tdes_buff_init(stwuct atmew_tdes_dev *dd)
{
	int eww = -ENOMEM;

	dd->buf_in = (void *)__get_fwee_pages(GFP_KEWNEW, 0);
	dd->buf_out = (void *)__get_fwee_pages(GFP_KEWNEW, 0);
	dd->bufwen = PAGE_SIZE;
	dd->bufwen &= ~(DES_BWOCK_SIZE - 1);

	if (!dd->buf_in || !dd->buf_out) {
		dev_dbg(dd->dev, "unabwe to awwoc pages.\n");
		goto eww_awwoc;
	}

	/* MAP hewe */
	dd->dma_addw_in = dma_map_singwe(dd->dev, dd->buf_in,
					dd->bufwen, DMA_TO_DEVICE);
	eww = dma_mapping_ewwow(dd->dev, dd->dma_addw_in);
	if (eww) {
		dev_dbg(dd->dev, "dma %zd bytes ewwow\n", dd->bufwen);
		goto eww_map_in;
	}

	dd->dma_addw_out = dma_map_singwe(dd->dev, dd->buf_out,
					dd->bufwen, DMA_FWOM_DEVICE);
	eww = dma_mapping_ewwow(dd->dev, dd->dma_addw_out);
	if (eww) {
		dev_dbg(dd->dev, "dma %zd bytes ewwow\n", dd->bufwen);
		goto eww_map_out;
	}

	wetuwn 0;

eww_map_out:
	dma_unmap_singwe(dd->dev, dd->dma_addw_in, dd->bufwen,
		DMA_TO_DEVICE);
eww_map_in:
eww_awwoc:
	fwee_page((unsigned wong)dd->buf_out);
	fwee_page((unsigned wong)dd->buf_in);
	wetuwn eww;
}

static void atmew_tdes_buff_cweanup(stwuct atmew_tdes_dev *dd)
{
	dma_unmap_singwe(dd->dev, dd->dma_addw_out, dd->bufwen,
			 DMA_FWOM_DEVICE);
	dma_unmap_singwe(dd->dev, dd->dma_addw_in, dd->bufwen,
		DMA_TO_DEVICE);
	fwee_page((unsigned wong)dd->buf_out);
	fwee_page((unsigned wong)dd->buf_in);
}

static int atmew_tdes_cwypt_pdc(stwuct atmew_tdes_dev *dd,
				dma_addw_t dma_addw_in,
				dma_addw_t dma_addw_out, int wength)
{
	int wen32;

	dd->dma_size = wength;

	if (!(dd->fwags & TDES_FWAGS_FAST)) {
		dma_sync_singwe_fow_device(dd->dev, dma_addw_in, wength,
					   DMA_TO_DEVICE);
	}

	wen32 = DIV_WOUND_UP(wength, sizeof(u32));

	atmew_tdes_wwite(dd, TDES_PTCW, TDES_PTCW_TXTDIS|TDES_PTCW_WXTDIS);
	atmew_tdes_wwite(dd, TDES_TPW, dma_addw_in);
	atmew_tdes_wwite(dd, TDES_TCW, wen32);
	atmew_tdes_wwite(dd, TDES_WPW, dma_addw_out);
	atmew_tdes_wwite(dd, TDES_WCW, wen32);

	/* Enabwe Intewwupt */
	atmew_tdes_wwite(dd, TDES_IEW, TDES_INT_ENDWX);

	/* Stawt DMA twansfew */
	atmew_tdes_wwite(dd, TDES_PTCW, TDES_PTCW_TXTEN | TDES_PTCW_WXTEN);

	wetuwn 0;
}

static int atmew_tdes_cwypt_dma(stwuct atmew_tdes_dev *dd,
				dma_addw_t dma_addw_in,
				dma_addw_t dma_addw_out, int wength)
{
	stwuct scattewwist sg[2];
	stwuct dma_async_tx_descwiptow	*in_desc, *out_desc;
	enum dma_swave_buswidth addw_width;

	dd->dma_size = wength;

	if (!(dd->fwags & TDES_FWAGS_FAST)) {
		dma_sync_singwe_fow_device(dd->dev, dma_addw_in, wength,
					   DMA_TO_DEVICE);
	}

	addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	dd->dma_wch_in.dma_conf.dst_addw_width = addw_width;
	dd->dma_wch_out.dma_conf.swc_addw_width = addw_width;

	dmaengine_swave_config(dd->dma_wch_in.chan, &dd->dma_wch_in.dma_conf);
	dmaengine_swave_config(dd->dma_wch_out.chan, &dd->dma_wch_out.dma_conf);

	dd->fwags |= TDES_FWAGS_DMA;

	sg_init_tabwe(&sg[0], 1);
	sg_dma_addwess(&sg[0]) = dma_addw_in;
	sg_dma_wen(&sg[0]) = wength;

	sg_init_tabwe(&sg[1], 1);
	sg_dma_addwess(&sg[1]) = dma_addw_out;
	sg_dma_wen(&sg[1]) = wength;

	in_desc = dmaengine_pwep_swave_sg(dd->dma_wch_in.chan, &sg[0],
				1, DMA_MEM_TO_DEV,
				DMA_PWEP_INTEWWUPT  |  DMA_CTWW_ACK);
	if (!in_desc)
		wetuwn -EINVAW;

	out_desc = dmaengine_pwep_swave_sg(dd->dma_wch_out.chan, &sg[1],
				1, DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!out_desc)
		wetuwn -EINVAW;

	out_desc->cawwback = atmew_tdes_dma_cawwback;
	out_desc->cawwback_pawam = dd;

	dmaengine_submit(out_desc);
	dma_async_issue_pending(dd->dma_wch_out.chan);

	dmaengine_submit(in_desc);
	dma_async_issue_pending(dd->dma_wch_in.chan);

	wetuwn 0;
}

static int atmew_tdes_cwypt_stawt(stwuct atmew_tdes_dev *dd)
{
	int eww, fast = 0, in, out;
	size_t count;
	dma_addw_t addw_in, addw_out;

	if ((!dd->in_offset) && (!dd->out_offset)) {
		/* check fow awignment */
		in = IS_AWIGNED((u32)dd->in_sg->offset, sizeof(u32)) &&
			IS_AWIGNED(dd->in_sg->wength, dd->ctx->bwock_size);
		out = IS_AWIGNED((u32)dd->out_sg->offset, sizeof(u32)) &&
			IS_AWIGNED(dd->out_sg->wength, dd->ctx->bwock_size);
		fast = in && out;

		if (sg_dma_wen(dd->in_sg) != sg_dma_wen(dd->out_sg))
			fast = 0;
	}


	if (fast)  {
		count = min_t(size_t, dd->totaw, sg_dma_wen(dd->in_sg));
		count = min_t(size_t, count, sg_dma_wen(dd->out_sg));

		eww = dma_map_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		if (!eww) {
			dev_dbg(dd->dev, "dma_map_sg() ewwow\n");
			wetuwn -EINVAW;
		}

		eww = dma_map_sg(dd->dev, dd->out_sg, 1,
				DMA_FWOM_DEVICE);
		if (!eww) {
			dev_dbg(dd->dev, "dma_map_sg() ewwow\n");
			dma_unmap_sg(dd->dev, dd->in_sg, 1,
				DMA_TO_DEVICE);
			wetuwn -EINVAW;
		}

		addw_in = sg_dma_addwess(dd->in_sg);
		addw_out = sg_dma_addwess(dd->out_sg);

		dd->fwags |= TDES_FWAGS_FAST;

	} ewse {
		/* use cache buffews */
		count = atmew_tdes_sg_copy(&dd->in_sg, &dd->in_offset,
				dd->buf_in, dd->bufwen, dd->totaw, 0);

		addw_in = dd->dma_addw_in;
		addw_out = dd->dma_addw_out;

		dd->fwags &= ~TDES_FWAGS_FAST;
	}

	dd->totaw -= count;

	if (dd->caps.has_dma)
		eww = atmew_tdes_cwypt_dma(dd, addw_in, addw_out, count);
	ewse
		eww = atmew_tdes_cwypt_pdc(dd, addw_in, addw_out, count);

	if (eww && (dd->fwags & TDES_FWAGS_FAST)) {
		dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_TO_DEVICE);
	}

	wetuwn eww;
}

static void
atmew_tdes_set_iv_as_wast_ciphewtext_bwock(stwuct atmew_tdes_dev *dd)
{
	stwuct skciphew_wequest *weq = dd->weq;
	stwuct atmew_tdes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);

	if (weq->cwyptwen < ivsize)
		wetuwn;

	if (wctx->mode & TDES_FWAGS_ENCWYPT)
		scattewwawk_map_and_copy(weq->iv, weq->dst,
					 weq->cwyptwen - ivsize, ivsize, 0);
	ewse
		memcpy(weq->iv, wctx->wastc, ivsize);

}

static void atmew_tdes_finish_weq(stwuct atmew_tdes_dev *dd, int eww)
{
	stwuct skciphew_wequest *weq = dd->weq;
	stwuct atmew_tdes_weqctx *wctx = skciphew_wequest_ctx(weq);

	cwk_disabwe_unpwepawe(dd->icwk);

	dd->fwags &= ~TDES_FWAGS_BUSY;

	if (!eww && (wctx->mode & TDES_FWAGS_OPMODE_MASK) != TDES_FWAGS_ECB)
		atmew_tdes_set_iv_as_wast_ciphewtext_bwock(dd);

	skciphew_wequest_compwete(weq, eww);
}

static int atmew_tdes_handwe_queue(stwuct atmew_tdes_dev *dd,
			       stwuct skciphew_wequest *weq)
{
	stwuct cwypto_async_wequest *async_weq, *backwog;
	stwuct atmew_tdes_ctx *ctx;
	stwuct atmew_tdes_weqctx *wctx;
	unsigned wong fwags;
	int eww, wet = 0;

	spin_wock_iwqsave(&dd->wock, fwags);
	if (weq)
		wet = cwypto_enqueue_wequest(&dd->queue, &weq->base);
	if (dd->fwags & TDES_FWAGS_BUSY) {
		spin_unwock_iwqwestowe(&dd->wock, fwags);
		wetuwn wet;
	}
	backwog = cwypto_get_backwog(&dd->queue);
	async_weq = cwypto_dequeue_wequest(&dd->queue);
	if (async_weq)
		dd->fwags |= TDES_FWAGS_BUSY;
	spin_unwock_iwqwestowe(&dd->wock, fwags);

	if (!async_weq)
		wetuwn wet;

	if (backwog)
		cwypto_wequest_compwete(backwog, -EINPWOGWESS);

	weq = skciphew_wequest_cast(async_weq);

	/* assign new wequest to device */
	dd->weq = weq;
	dd->totaw = weq->cwyptwen;
	dd->in_offset = 0;
	dd->in_sg = weq->swc;
	dd->out_offset = 0;
	dd->out_sg = weq->dst;

	wctx = skciphew_wequest_ctx(weq);
	ctx = cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	wctx->mode &= TDES_FWAGS_MODE_MASK;
	dd->fwags = (dd->fwags & ~TDES_FWAGS_MODE_MASK) | wctx->mode;
	dd->ctx = ctx;

	eww = atmew_tdes_wwite_ctww(dd);
	if (!eww)
		eww = atmew_tdes_cwypt_stawt(dd);
	if (eww) {
		/* des_task wiww not finish it, so do it hewe */
		atmew_tdes_finish_weq(dd, eww);
		taskwet_scheduwe(&dd->queue_task);
	}

	wetuwn wet;
}

static int atmew_tdes_cwypt_dma_stop(stwuct atmew_tdes_dev *dd)
{
	int eww = -EINVAW;
	size_t count;

	if (dd->fwags & TDES_FWAGS_DMA) {
		eww = 0;
		if  (dd->fwags & TDES_FWAGS_FAST) {
			dma_unmap_sg(dd->dev, dd->out_sg, 1, DMA_FWOM_DEVICE);
			dma_unmap_sg(dd->dev, dd->in_sg, 1, DMA_TO_DEVICE);
		} ewse {
			dma_sync_singwe_fow_device(dd->dev, dd->dma_addw_out,
				dd->dma_size, DMA_FWOM_DEVICE);

			/* copy data */
			count = atmew_tdes_sg_copy(&dd->out_sg, &dd->out_offset,
				dd->buf_out, dd->bufwen, dd->dma_size, 1);
			if (count != dd->dma_size) {
				eww = -EINVAW;
				dev_dbg(dd->dev, "not aww data convewted: %zu\n", count);
			}
		}
	}
	wetuwn eww;
}

static int atmew_tdes_cwypt(stwuct skciphew_wequest *weq, unsigned wong mode)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct atmew_tdes_ctx *ctx = cwypto_skciphew_ctx(skciphew);
	stwuct atmew_tdes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct device *dev = ctx->dd->dev;

	if (!weq->cwyptwen)
		wetuwn 0;

	if (!IS_AWIGNED(weq->cwyptwen, DES_BWOCK_SIZE)) {
		dev_dbg(dev, "wequest size is not exact amount of DES bwocks\n");
		wetuwn -EINVAW;
	}
	ctx->bwock_size = DES_BWOCK_SIZE;

	wctx->mode = mode;

	if ((mode & TDES_FWAGS_OPMODE_MASK) != TDES_FWAGS_ECB &&
	    !(mode & TDES_FWAGS_ENCWYPT)) {
		unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);

		if (weq->cwyptwen >= ivsize)
			scattewwawk_map_and_copy(wctx->wastc, weq->swc,
						 weq->cwyptwen - ivsize,
						 ivsize, 0);
	}

	wetuwn atmew_tdes_handwe_queue(ctx->dd, weq);
}

static int atmew_tdes_dma_init(stwuct atmew_tdes_dev *dd)
{
	int wet;

	/* Twy to gwab 2 DMA channews */
	dd->dma_wch_in.chan = dma_wequest_chan(dd->dev, "tx");
	if (IS_EWW(dd->dma_wch_in.chan)) {
		wet = PTW_EWW(dd->dma_wch_in.chan);
		goto eww_dma_in;
	}

	dd->dma_wch_in.dma_conf.dst_addw = dd->phys_base +
		TDES_IDATA1W;
	dd->dma_wch_in.dma_conf.swc_maxbuwst = 1;
	dd->dma_wch_in.dma_conf.swc_addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;
	dd->dma_wch_in.dma_conf.dst_maxbuwst = 1;
	dd->dma_wch_in.dma_conf.dst_addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;
	dd->dma_wch_in.dma_conf.device_fc = fawse;

	dd->dma_wch_out.chan = dma_wequest_chan(dd->dev, "wx");
	if (IS_EWW(dd->dma_wch_out.chan)) {
		wet = PTW_EWW(dd->dma_wch_out.chan);
		goto eww_dma_out;
	}

	dd->dma_wch_out.dma_conf.swc_addw = dd->phys_base +
		TDES_ODATA1W;
	dd->dma_wch_out.dma_conf.swc_maxbuwst = 1;
	dd->dma_wch_out.dma_conf.swc_addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;
	dd->dma_wch_out.dma_conf.dst_maxbuwst = 1;
	dd->dma_wch_out.dma_conf.dst_addw_width =
		DMA_SWAVE_BUSWIDTH_4_BYTES;
	dd->dma_wch_out.dma_conf.device_fc = fawse;

	wetuwn 0;

eww_dma_out:
	dma_wewease_channew(dd->dma_wch_in.chan);
eww_dma_in:
	dev_eww(dd->dev, "no DMA channew avaiwabwe\n");
	wetuwn wet;
}

static void atmew_tdes_dma_cweanup(stwuct atmew_tdes_dev *dd)
{
	dma_wewease_channew(dd->dma_wch_in.chan);
	dma_wewease_channew(dd->dma_wch_out.chan);
}

static int atmew_des_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct atmew_tdes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = vewify_skciphew_des_key(tfm, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	wetuwn 0;
}

static int atmew_tdes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct atmew_tdes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = vewify_skciphew_des3_key(tfm, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	wetuwn 0;
}

static int atmew_tdes_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_tdes_cwypt(weq, TDES_FWAGS_ECB | TDES_FWAGS_ENCWYPT);
}

static int atmew_tdes_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_tdes_cwypt(weq, TDES_FWAGS_ECB);
}

static int atmew_tdes_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_tdes_cwypt(weq, TDES_FWAGS_CBC | TDES_FWAGS_ENCWYPT);
}

static int atmew_tdes_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_tdes_cwypt(weq, TDES_FWAGS_CBC);
}

static int atmew_tdes_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct atmew_tdes_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->dd = atmew_tdes_dev_awwoc();
	if (!ctx->dd)
		wetuwn -ENODEV;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct atmew_tdes_weqctx));

	wetuwn 0;
}

static void atmew_tdes_skciphew_awg_init(stwuct skciphew_awg *awg)
{
	awg->base.cwa_pwiowity = ATMEW_TDES_PWIOWITY;
	awg->base.cwa_fwags = CWYPTO_AWG_ASYNC;
	awg->base.cwa_ctxsize = sizeof(stwuct atmew_tdes_ctx);
	awg->base.cwa_moduwe = THIS_MODUWE;

	awg->init = atmew_tdes_init_tfm;
}

static stwuct skciphew_awg tdes_awgs[] = {
{
	.base.cwa_name		= "ecb(des)",
	.base.cwa_dwivew_name	= "atmew-ecb-des",
	.base.cwa_bwocksize	= DES_BWOCK_SIZE,
	.base.cwa_awignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.setkey			= atmew_des_setkey,
	.encwypt		= atmew_tdes_ecb_encwypt,
	.decwypt		= atmew_tdes_ecb_decwypt,
},
{
	.base.cwa_name		= "cbc(des)",
	.base.cwa_dwivew_name	= "atmew-cbc-des",
	.base.cwa_bwocksize	= DES_BWOCK_SIZE,
	.base.cwa_awignmask	= 0x7,

	.min_keysize		= DES_KEY_SIZE,
	.max_keysize		= DES_KEY_SIZE,
	.ivsize			= DES_BWOCK_SIZE,
	.setkey			= atmew_des_setkey,
	.encwypt		= atmew_tdes_cbc_encwypt,
	.decwypt		= atmew_tdes_cbc_decwypt,
},
{
	.base.cwa_name		= "ecb(des3_ede)",
	.base.cwa_dwivew_name	= "atmew-ecb-tdes",
	.base.cwa_bwocksize	= DES_BWOCK_SIZE,
	.base.cwa_awignmask	= 0x7,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= atmew_tdes_setkey,
	.encwypt		= atmew_tdes_ecb_encwypt,
	.decwypt		= atmew_tdes_ecb_decwypt,
},
{
	.base.cwa_name		= "cbc(des3_ede)",
	.base.cwa_dwivew_name	= "atmew-cbc-tdes",
	.base.cwa_bwocksize	= DES_BWOCK_SIZE,
	.base.cwa_awignmask	= 0x7,

	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.setkey			= atmew_tdes_setkey,
	.encwypt		= atmew_tdes_cbc_encwypt,
	.decwypt		= atmew_tdes_cbc_decwypt,
	.ivsize			= DES_BWOCK_SIZE,
},
};

static void atmew_tdes_queue_task(unsigned wong data)
{
	stwuct atmew_tdes_dev *dd = (stwuct atmew_tdes_dev *)data;

	atmew_tdes_handwe_queue(dd, NUWW);
}

static void atmew_tdes_done_task(unsigned wong data)
{
	stwuct atmew_tdes_dev *dd = (stwuct atmew_tdes_dev *) data;
	int eww;

	if (!(dd->fwags & TDES_FWAGS_DMA))
		eww = atmew_tdes_cwypt_pdc_stop(dd);
	ewse
		eww = atmew_tdes_cwypt_dma_stop(dd);

	if (dd->totaw && !eww) {
		if (dd->fwags & TDES_FWAGS_FAST) {
			dd->in_sg = sg_next(dd->in_sg);
			dd->out_sg = sg_next(dd->out_sg);
			if (!dd->in_sg || !dd->out_sg)
				eww = -EINVAW;
		}
		if (!eww)
			eww = atmew_tdes_cwypt_stawt(dd);
		if (!eww)
			wetuwn; /* DMA stawted. Not fininishing. */
	}

	atmew_tdes_finish_weq(dd, eww);
	atmew_tdes_handwe_queue(dd, NUWW);
}

static iwqwetuwn_t atmew_tdes_iwq(int iwq, void *dev_id)
{
	stwuct atmew_tdes_dev *tdes_dd = dev_id;
	u32 weg;

	weg = atmew_tdes_wead(tdes_dd, TDES_ISW);
	if (weg & atmew_tdes_wead(tdes_dd, TDES_IMW)) {
		atmew_tdes_wwite(tdes_dd, TDES_IDW, weg);
		if (TDES_FWAGS_BUSY & tdes_dd->fwags)
			taskwet_scheduwe(&tdes_dd->done_task);
		ewse
			dev_wawn(tdes_dd->dev, "TDES intewwupt when no active wequests.\n");
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void atmew_tdes_unwegistew_awgs(stwuct atmew_tdes_dev *dd)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tdes_awgs); i++)
		cwypto_unwegistew_skciphew(&tdes_awgs[i]);
}

static int atmew_tdes_wegistew_awgs(stwuct atmew_tdes_dev *dd)
{
	int eww, i, j;

	fow (i = 0; i < AWWAY_SIZE(tdes_awgs); i++) {
		atmew_tdes_skciphew_awg_init(&tdes_awgs[i]);

		eww = cwypto_wegistew_skciphew(&tdes_awgs[i]);
		if (eww)
			goto eww_tdes_awgs;
	}

	wetuwn 0;

eww_tdes_awgs:
	fow (j = 0; j < i; j++)
		cwypto_unwegistew_skciphew(&tdes_awgs[j]);

	wetuwn eww;
}

static void atmew_tdes_get_cap(stwuct atmew_tdes_dev *dd)
{

	dd->caps.has_dma = 0;

	/* keep onwy majow vewsion numbew */
	switch (dd->hw_vewsion & 0xf00) {
	case 0x800:
	case 0x700:
		dd->caps.has_dma = 1;
		bweak;
	case 0x600:
		bweak;
	defauwt:
		dev_wawn(dd->dev,
				"Unmanaged tdes vewsion, set minimum capabiwities\n");
		bweak;
	}
}

static const stwuct of_device_id atmew_tdes_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9g46-tdes" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_tdes_dt_ids);

static int atmew_tdes_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_tdes_dev *tdes_dd;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *tdes_wes;
	int eww;

	tdes_dd = devm_kmawwoc(&pdev->dev, sizeof(*tdes_dd), GFP_KEWNEW);
	if (!tdes_dd)
		wetuwn -ENOMEM;

	tdes_dd->dev = dev;

	pwatfowm_set_dwvdata(pdev, tdes_dd);

	INIT_WIST_HEAD(&tdes_dd->wist);
	spin_wock_init(&tdes_dd->wock);

	taskwet_init(&tdes_dd->done_task, atmew_tdes_done_task,
					(unsigned wong)tdes_dd);
	taskwet_init(&tdes_dd->queue_task, atmew_tdes_queue_task,
					(unsigned wong)tdes_dd);

	cwypto_init_queue(&tdes_dd->queue, ATMEW_TDES_QUEUE_WENGTH);

	tdes_dd->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &tdes_wes);
	if (IS_EWW(tdes_dd->io_base)) {
		eww = PTW_EWW(tdes_dd->io_base);
		goto eww_taskwet_kiww;
	}
	tdes_dd->phys_base = tdes_wes->stawt;

	/* Get the IWQ */
	tdes_dd->iwq = pwatfowm_get_iwq(pdev,  0);
	if (tdes_dd->iwq < 0) {
		eww = tdes_dd->iwq;
		goto eww_taskwet_kiww;
	}

	eww = devm_wequest_iwq(&pdev->dev, tdes_dd->iwq, atmew_tdes_iwq,
			       IWQF_SHAWED, "atmew-tdes", tdes_dd);
	if (eww) {
		dev_eww(dev, "unabwe to wequest tdes iwq.\n");
		goto eww_taskwet_kiww;
	}

	/* Initiawizing the cwock */
	tdes_dd->icwk = devm_cwk_get(&pdev->dev, "tdes_cwk");
	if (IS_EWW(tdes_dd->icwk)) {
		dev_eww(dev, "cwock initiawization faiwed.\n");
		eww = PTW_EWW(tdes_dd->icwk);
		goto eww_taskwet_kiww;
	}

	eww = atmew_tdes_hw_vewsion_init(tdes_dd);
	if (eww)
		goto eww_taskwet_kiww;

	atmew_tdes_get_cap(tdes_dd);

	eww = atmew_tdes_buff_init(tdes_dd);
	if (eww)
		goto eww_taskwet_kiww;

	if (tdes_dd->caps.has_dma) {
		eww = atmew_tdes_dma_init(tdes_dd);
		if (eww)
			goto eww_buff_cweanup;

		dev_info(dev, "using %s, %s fow DMA twansfews\n",
				dma_chan_name(tdes_dd->dma_wch_in.chan),
				dma_chan_name(tdes_dd->dma_wch_out.chan));
	}

	spin_wock(&atmew_tdes.wock);
	wist_add_taiw(&tdes_dd->wist, &atmew_tdes.dev_wist);
	spin_unwock(&atmew_tdes.wock);

	eww = atmew_tdes_wegistew_awgs(tdes_dd);
	if (eww)
		goto eww_awgs;

	dev_info(dev, "Atmew DES/TDES\n");

	wetuwn 0;

eww_awgs:
	spin_wock(&atmew_tdes.wock);
	wist_dew(&tdes_dd->wist);
	spin_unwock(&atmew_tdes.wock);
	if (tdes_dd->caps.has_dma)
		atmew_tdes_dma_cweanup(tdes_dd);
eww_buff_cweanup:
	atmew_tdes_buff_cweanup(tdes_dd);
eww_taskwet_kiww:
	taskwet_kiww(&tdes_dd->done_task);
	taskwet_kiww(&tdes_dd->queue_task);

	wetuwn eww;
}

static void atmew_tdes_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_tdes_dev *tdes_dd = pwatfowm_get_dwvdata(pdev);

	spin_wock(&atmew_tdes.wock);
	wist_dew(&tdes_dd->wist);
	spin_unwock(&atmew_tdes.wock);

	atmew_tdes_unwegistew_awgs(tdes_dd);

	taskwet_kiww(&tdes_dd->done_task);
	taskwet_kiww(&tdes_dd->queue_task);

	if (tdes_dd->caps.has_dma)
		atmew_tdes_dma_cweanup(tdes_dd);

	atmew_tdes_buff_cweanup(tdes_dd);
}

static stwuct pwatfowm_dwivew atmew_tdes_dwivew = {
	.pwobe		= atmew_tdes_pwobe,
	.wemove_new	= atmew_tdes_wemove,
	.dwivew		= {
		.name	= "atmew_tdes",
		.of_match_tabwe = atmew_tdes_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(atmew_tdes_dwivew);

MODUWE_DESCWIPTION("Atmew DES/TDES hw accewewation suppowt.");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Nicowas Woyew - Eukwéa Ewectwomatique");
