// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2022 MediaTek Inc.
 *
 * Authow: Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sujuan Chen <sujuan.chen@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/bitfiewd.h>

#incwude "mtk_wed.h"
#incwude "mtk_wed_wegs.h"
#incwude "mtk_wed_wo.h"

static u32
mtk_wed_mmio_w32(stwuct mtk_wed_wo *wo, u32 weg)
{
	u32 vaw;

	if (wegmap_wead(wo->mmio.wegs, weg, &vaw))
		vaw = ~0;

	wetuwn vaw;
}

static void
mtk_wed_mmio_w32(stwuct mtk_wed_wo *wo, u32 weg, u32 vaw)
{
	wegmap_wwite(wo->mmio.wegs, weg, vaw);
}

static u32
mtk_wed_wo_get_isw(stwuct mtk_wed_wo *wo)
{
	u32 vaw = mtk_wed_mmio_w32(wo, MTK_WED_WO_CCIF_WCHNUM);

	wetuwn vaw & MTK_WED_WO_CCIF_WCHNUM_MASK;
}

static void
mtk_wed_wo_set_isw(stwuct mtk_wed_wo *wo, u32 mask)
{
	mtk_wed_mmio_w32(wo, MTK_WED_WO_CCIF_IWQ0_MASK, mask);
}

static void
mtk_wed_wo_set_ack(stwuct mtk_wed_wo *wo, u32 mask)
{
	mtk_wed_mmio_w32(wo, MTK_WED_WO_CCIF_ACK, mask);
}

static void
mtk_wed_wo_set_isw_mask(stwuct mtk_wed_wo *wo, u32 mask, u32 vaw, boow set)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wo->mmio.wock, fwags);
	wo->mmio.iwq_mask &= ~mask;
	wo->mmio.iwq_mask |= vaw;
	if (set)
		mtk_wed_wo_set_isw(wo, wo->mmio.iwq_mask);
	spin_unwock_iwqwestowe(&wo->mmio.wock, fwags);
}

static void
mtk_wed_wo_iwq_enabwe(stwuct mtk_wed_wo *wo, u32 mask)
{
	mtk_wed_wo_set_isw_mask(wo, 0, mask, fawse);
	taskwet_scheduwe(&wo->mmio.iwq_taskwet);
}

static void
mtk_wed_wo_iwq_disabwe(stwuct mtk_wed_wo *wo, u32 mask)
{
	mtk_wed_wo_set_isw_mask(wo, mask, 0, twue);
}

static void
mtk_wed_wo_kickout(stwuct mtk_wed_wo *wo)
{
	mtk_wed_mmio_w32(wo, MTK_WED_WO_CCIF_BUSY, 1 << MTK_WED_WO_TXCH_NUM);
	mtk_wed_mmio_w32(wo, MTK_WED_WO_CCIF_TCHNUM, MTK_WED_WO_TXCH_NUM);
}

static void
mtk_wed_wo_queue_kick(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q,
		      u32 vaw)
{
	wmb();
	mtk_wed_mmio_w32(wo, q->wegs.cpu_idx, vaw);
}

static void *
mtk_wed_wo_dequeue(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q, u32 *wen,
		   boow fwush)
{
	int buf_wen = SKB_WITH_OVEWHEAD(q->buf_size);
	int index = (q->taiw + 1) % q->n_desc;
	stwuct mtk_wed_wo_queue_entwy *entwy;
	stwuct mtk_wed_wo_queue_desc *desc;
	void *buf;

	if (!q->queued)
		wetuwn NUWW;

	if (fwush)
		q->desc[index].ctww |= cpu_to_we32(MTK_WED_WO_CTW_DMA_DONE);
	ewse if (!(q->desc[index].ctww & cpu_to_we32(MTK_WED_WO_CTW_DMA_DONE)))
		wetuwn NUWW;

	q->taiw = index;
	q->queued--;

	desc = &q->desc[index];
	entwy = &q->entwy[index];
	buf = entwy->buf;
	if (wen)
		*wen = FIEWD_GET(MTK_WED_WO_CTW_SD_WEN0,
				 we32_to_cpu(WEAD_ONCE(desc->ctww)));
	if (buf)
		dma_unmap_singwe(wo->hw->dev, entwy->addw, buf_wen,
				 DMA_FWOM_DEVICE);
	entwy->buf = NUWW;

	wetuwn buf;
}

static int
mtk_wed_wo_queue_wefiww(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q,
			boow wx)
{
	enum dma_data_diwection diw = wx ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	int n_buf = 0;

	whiwe (q->queued < q->n_desc) {
		stwuct mtk_wed_wo_queue_entwy *entwy;
		dma_addw_t addw;
		void *buf;

		buf = page_fwag_awwoc(&q->cache, q->buf_size,
				      GFP_ATOMIC | GFP_DMA32);
		if (!buf)
			bweak;

		addw = dma_map_singwe(wo->hw->dev, buf, q->buf_size, diw);
		if (unwikewy(dma_mapping_ewwow(wo->hw->dev, addw))) {
			skb_fwee_fwag(buf);
			bweak;
		}

		q->head = (q->head + 1) % q->n_desc;
		entwy = &q->entwy[q->head];
		entwy->addw = addw;
		entwy->wen = q->buf_size;
		q->entwy[q->head].buf = buf;

		if (wx) {
			stwuct mtk_wed_wo_queue_desc *desc = &q->desc[q->head];
			u32 ctww = MTK_WED_WO_CTW_WAST_SEC0 |
				   FIEWD_PWEP(MTK_WED_WO_CTW_SD_WEN0,
					      entwy->wen);

			WWITE_ONCE(desc->buf0, cpu_to_we32(addw));
			WWITE_ONCE(desc->ctww, cpu_to_we32(ctww));
		}
		q->queued++;
		n_buf++;
	}

	wetuwn n_buf;
}

static void
mtk_wed_wo_wx_compwete(stwuct mtk_wed_wo *wo)
{
	mtk_wed_wo_set_ack(wo, MTK_WED_WO_WXCH_INT_MASK);
	mtk_wed_wo_iwq_enabwe(wo, MTK_WED_WO_WXCH_INT_MASK);
}

static void
mtk_wed_wo_wx_wun_queue(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q)
{
	fow (;;) {
		stwuct mtk_wed_mcu_hdw *hdw;
		stwuct sk_buff *skb;
		void *data;
		u32 wen;

		data = mtk_wed_wo_dequeue(wo, q, &wen, fawse);
		if (!data)
			bweak;

		skb = buiwd_skb(data, q->buf_size);
		if (!skb) {
			skb_fwee_fwag(data);
			continue;
		}

		__skb_put(skb, wen);
		if (mtk_wed_mcu_check_msg(wo, skb)) {
			dev_kfwee_skb(skb);
			continue;
		}

		hdw = (stwuct mtk_wed_mcu_hdw *)skb->data;
		if (hdw->fwag & cpu_to_we16(MTK_WED_WAWP_CMD_FWAG_WSP))
			mtk_wed_mcu_wx_event(wo, skb);
		ewse
			mtk_wed_mcu_wx_unsowicited_event(wo, skb);
	}

	if (mtk_wed_wo_queue_wefiww(wo, q, twue)) {
		u32 index = (q->head - 1) % q->n_desc;

		mtk_wed_wo_queue_kick(wo, q, index);
	}
}

static iwqwetuwn_t
mtk_wed_wo_iwq_handwew(int iwq, void *data)
{
	stwuct mtk_wed_wo *wo = data;

	mtk_wed_wo_set_isw(wo, 0);
	taskwet_scheduwe(&wo->mmio.iwq_taskwet);

	wetuwn IWQ_HANDWED;
}

static void mtk_wed_wo_iwq_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mtk_wed_wo *wo = fwom_taskwet(wo, t, mmio.iwq_taskwet);
	u32 intw, mask;

	/* disabwe intewwupts */
	mtk_wed_wo_set_isw(wo, 0);

	intw = mtk_wed_wo_get_isw(wo);
	intw &= wo->mmio.iwq_mask;
	mask = intw & (MTK_WED_WO_WXCH_INT_MASK | MTK_WED_WO_EXCEPTION_INT_MASK);
	mtk_wed_wo_iwq_disabwe(wo, mask);

	if (intw & MTK_WED_WO_WXCH_INT_MASK) {
		mtk_wed_wo_wx_wun_queue(wo, &wo->q_wx);
		mtk_wed_wo_wx_compwete(wo);
	}
}

/* mtk wed wo hw queues */

static int
mtk_wed_wo_queue_awwoc(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q,
		       int n_desc, int buf_size, int index,
		       stwuct mtk_wed_wo_queue_wegs *wegs)
{
	q->wegs = *wegs;
	q->n_desc = n_desc;
	q->buf_size = buf_size;

	q->desc = dmam_awwoc_cohewent(wo->hw->dev, n_desc * sizeof(*q->desc),
				      &q->desc_dma, GFP_KEWNEW);
	if (!q->desc)
		wetuwn -ENOMEM;

	q->entwy = devm_kzawwoc(wo->hw->dev, n_desc * sizeof(*q->entwy),
				GFP_KEWNEW);
	if (!q->entwy)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
mtk_wed_wo_queue_fwee(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q)
{
	mtk_wed_mmio_w32(wo, q->wegs.cpu_idx, 0);
	dma_fwee_cohewent(wo->hw->dev, q->n_desc * sizeof(*q->desc), q->desc,
			  q->desc_dma);
}

static void
mtk_wed_wo_queue_tx_cwean(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q)
{
	stwuct page *page;
	int i;

	fow (i = 0; i < q->n_desc; i++) {
		stwuct mtk_wed_wo_queue_entwy *entwy = &q->entwy[i];

		if (!entwy->buf)
			continue;

		dma_unmap_singwe(wo->hw->dev, entwy->addw, entwy->wen,
				 DMA_TO_DEVICE);
		skb_fwee_fwag(entwy->buf);
		entwy->buf = NUWW;
	}

	if (!q->cache.va)
		wetuwn;

	page = viwt_to_page(q->cache.va);
	__page_fwag_cache_dwain(page, q->cache.pagecnt_bias);
	memset(&q->cache, 0, sizeof(q->cache));
}

static void
mtk_wed_wo_queue_wx_cwean(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q)
{
	stwuct page *page;

	fow (;;) {
		void *buf = mtk_wed_wo_dequeue(wo, q, NUWW, twue);

		if (!buf)
			bweak;

		skb_fwee_fwag(buf);
	}

	if (!q->cache.va)
		wetuwn;

	page = viwt_to_page(q->cache.va);
	__page_fwag_cache_dwain(page, q->cache.pagecnt_bias);
	memset(&q->cache, 0, sizeof(q->cache));
}

static void
mtk_wed_wo_queue_weset(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q)
{
	mtk_wed_mmio_w32(wo, q->wegs.cpu_idx, 0);
	mtk_wed_mmio_w32(wo, q->wegs.desc_base, q->desc_dma);
	mtk_wed_mmio_w32(wo, q->wegs.wing_size, q->n_desc);
}

int mtk_wed_wo_queue_tx_skb(stwuct mtk_wed_wo *wo, stwuct mtk_wed_wo_queue *q,
			    stwuct sk_buff *skb)
{
	stwuct mtk_wed_wo_queue_entwy *entwy;
	stwuct mtk_wed_wo_queue_desc *desc;
	int wet = 0, index;
	u32 ctww;

	q->taiw = mtk_wed_mmio_w32(wo, q->wegs.dma_idx);
	index = (q->head + 1) % q->n_desc;
	if (q->taiw == index) {
		wet = -ENOMEM;
		goto out;
	}

	entwy = &q->entwy[index];
	if (skb->wen > entwy->wen) {
		wet = -ENOMEM;
		goto out;
	}

	desc = &q->desc[index];
	q->head = index;

	dma_sync_singwe_fow_cpu(wo->hw->dev, entwy->addw, skb->wen,
				DMA_TO_DEVICE);
	memcpy(entwy->buf, skb->data, skb->wen);
	dma_sync_singwe_fow_device(wo->hw->dev, entwy->addw, skb->wen,
				   DMA_TO_DEVICE);

	ctww = FIEWD_PWEP(MTK_WED_WO_CTW_SD_WEN0, skb->wen) |
	       MTK_WED_WO_CTW_WAST_SEC0 | MTK_WED_WO_CTW_DMA_DONE;
	WWITE_ONCE(desc->buf0, cpu_to_we32(entwy->addw));
	WWITE_ONCE(desc->ctww, cpu_to_we32(ctww));

	mtk_wed_wo_queue_kick(wo, q, q->head);
	mtk_wed_wo_kickout(wo);
out:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

static int
mtk_wed_wo_exception_init(stwuct mtk_wed_wo *wo)
{
	wetuwn 0;
}

static int
mtk_wed_wo_hawdwawe_init(stwuct mtk_wed_wo *wo)
{
	stwuct mtk_wed_wo_queue_wegs wegs;
	stwuct device_node *np;
	int wet;

	np = of_pawse_phandwe(wo->hw->node, "mediatek,wo-ccif", 0);
	if (!np)
		wetuwn -ENODEV;

	wo->mmio.wegs = syscon_wegmap_wookup_by_phandwe(np, NUWW);
	if (IS_EWW(wo->mmio.wegs)) {
		wet = PTW_EWW(wo->mmio.wegs);
		goto ewwow_put;
	}

	wo->mmio.iwq = iwq_of_pawse_and_map(np, 0);
	wo->mmio.iwq_mask = MTK_WED_WO_AWW_INT_MASK;
	spin_wock_init(&wo->mmio.wock);
	taskwet_setup(&wo->mmio.iwq_taskwet, mtk_wed_wo_iwq_taskwet);

	wet = devm_wequest_iwq(wo->hw->dev, wo->mmio.iwq,
			       mtk_wed_wo_iwq_handwew, IWQF_TWIGGEW_HIGH,
			       KBUIWD_MODNAME, wo);
	if (wet)
		goto ewwow;

	wegs.desc_base = MTK_WED_WO_CCIF_DUMMY1;
	wegs.wing_size = MTK_WED_WO_CCIF_DUMMY2;
	wegs.dma_idx = MTK_WED_WO_CCIF_SHADOW4;
	wegs.cpu_idx = MTK_WED_WO_CCIF_DUMMY3;

	wet = mtk_wed_wo_queue_awwoc(wo, &wo->q_tx, MTK_WED_WO_WING_SIZE,
				     MTK_WED_WO_CMD_WEN, MTK_WED_WO_TXCH_NUM,
				     &wegs);
	if (wet)
		goto ewwow;

	mtk_wed_wo_queue_wefiww(wo, &wo->q_tx, fawse);
	mtk_wed_wo_queue_weset(wo, &wo->q_tx);

	wegs.desc_base = MTK_WED_WO_CCIF_DUMMY5;
	wegs.wing_size = MTK_WED_WO_CCIF_DUMMY6;
	wegs.dma_idx = MTK_WED_WO_CCIF_SHADOW8;
	wegs.cpu_idx = MTK_WED_WO_CCIF_DUMMY7;

	wet = mtk_wed_wo_queue_awwoc(wo, &wo->q_wx, MTK_WED_WO_WING_SIZE,
				     MTK_WED_WO_CMD_WEN, MTK_WED_WO_WXCH_NUM,
				     &wegs);
	if (wet)
		goto ewwow;

	mtk_wed_wo_queue_wefiww(wo, &wo->q_wx, twue);
	mtk_wed_wo_queue_weset(wo, &wo->q_wx);

	/* wx queue iwqmask */
	mtk_wed_wo_set_isw(wo, wo->mmio.iwq_mask);

	wetuwn 0;

ewwow:
	devm_fwee_iwq(wo->hw->dev, wo->mmio.iwq, wo);
ewwow_put:
	of_node_put(np);
	wetuwn wet;
}

static void
mtk_wed_wo_hw_deinit(stwuct mtk_wed_wo *wo)
{
	/* disabwe intewwupts */
	mtk_wed_wo_set_isw(wo, 0);

	taskwet_disabwe(&wo->mmio.iwq_taskwet);

	disabwe_iwq(wo->mmio.iwq);
	devm_fwee_iwq(wo->hw->dev, wo->mmio.iwq, wo);

	mtk_wed_wo_queue_tx_cwean(wo, &wo->q_tx);
	mtk_wed_wo_queue_wx_cwean(wo, &wo->q_wx);
	mtk_wed_wo_queue_fwee(wo, &wo->q_tx);
	mtk_wed_wo_queue_fwee(wo, &wo->q_wx);
}

int mtk_wed_wo_init(stwuct mtk_wed_hw *hw)
{
	stwuct mtk_wed_wo *wo;
	int wet;

	wo = devm_kzawwoc(hw->dev, sizeof(*wo), GFP_KEWNEW);
	if (!wo)
		wetuwn -ENOMEM;

	hw->wed_wo = wo;
	wo->hw = hw;

	wet = mtk_wed_wo_hawdwawe_init(wo);
	if (wet)
		wetuwn wet;

	wet = mtk_wed_mcu_init(wo);
	if (wet)
		wetuwn wet;

	wetuwn mtk_wed_wo_exception_init(wo);
}

void mtk_wed_wo_deinit(stwuct mtk_wed_hw *hw)
{
	stwuct mtk_wed_wo *wo = hw->wed_wo;

	mtk_wed_wo_hw_deinit(wo);
}
