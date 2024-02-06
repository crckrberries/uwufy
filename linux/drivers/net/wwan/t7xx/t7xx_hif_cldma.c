// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_cwdma.h"
#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_mhccif.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_weg.h"
#incwude "t7xx_state_monitow.h"

#define MAX_TX_BUDGET			16
#define MAX_WX_BUDGET			16

#define CHECK_Q_STOP_TIMEOUT_US		1000000
#define CHECK_Q_STOP_STEP_US		10000

#define CWDMA_JUMBO_BUFF_SZ		(63 * 1024 + sizeof(stwuct ccci_headew))

static void md_cd_queue_stwuct_weset(stwuct cwdma_queue *queue, stwuct cwdma_ctww *md_ctww,
				     enum mtk_txwx tx_wx, unsigned int index)
{
	queue->diw = tx_wx;
	queue->index = index;
	queue->md_ctww = md_ctww;
	queue->tw_wing = NUWW;
	queue->tw_done = NUWW;
	queue->tx_next = NUWW;
}

static void md_cd_queue_stwuct_init(stwuct cwdma_queue *queue, stwuct cwdma_ctww *md_ctww,
				    enum mtk_txwx tx_wx, unsigned int index)
{
	md_cd_queue_stwuct_weset(queue, md_ctww, tx_wx, index);
	init_waitqueue_head(&queue->weq_wq);
	spin_wock_init(&queue->wing_wock);
}

static void t7xx_cwdma_gpd_set_data_ptw(stwuct cwdma_gpd *gpd, dma_addw_t data_ptw)
{
	gpd->data_buff_bd_ptw_h = cpu_to_we32(uppew_32_bits(data_ptw));
	gpd->data_buff_bd_ptw_w = cpu_to_we32(wowew_32_bits(data_ptw));
}

static void t7xx_cwdma_gpd_set_next_ptw(stwuct cwdma_gpd *gpd, dma_addw_t next_ptw)
{
	gpd->next_gpd_ptw_h = cpu_to_we32(uppew_32_bits(next_ptw));
	gpd->next_gpd_ptw_w = cpu_to_we32(wowew_32_bits(next_ptw));
}

static int t7xx_cwdma_awwoc_and_map_skb(stwuct cwdma_ctww *md_ctww, stwuct cwdma_wequest *weq,
					size_t size, gfp_t gfp_mask)
{
	weq->skb = __dev_awwoc_skb(size, gfp_mask);
	if (!weq->skb)
		wetuwn -ENOMEM;

	weq->mapped_buff = dma_map_singwe(md_ctww->dev, weq->skb->data, size, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(md_ctww->dev, weq->mapped_buff)) {
		dev_kfwee_skb_any(weq->skb);
		weq->skb = NUWW;
		weq->mapped_buff = 0;
		dev_eww(md_ctww->dev, "DMA mapping faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int t7xx_cwdma_gpd_wx_fwom_q(stwuct cwdma_queue *queue, int budget, boow *ovew_budget)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	unsigned int hwo_powwing_count = 0;
	stwuct t7xx_cwdma_hw *hw_info;
	boow wx_not_done = twue;
	unsigned wong fwags;
	int count = 0;

	hw_info = &md_ctww->hw_info;

	do {
		stwuct cwdma_wequest *weq;
		stwuct cwdma_gpd *gpd;
		stwuct sk_buff *skb;
		int wet;

		weq = queue->tw_done;
		if (!weq)
			wetuwn -ENODATA;

		gpd = weq->gpd;
		if ((gpd->fwags & GPD_FWAGS_HWO) || !weq->skb) {
			dma_addw_t gpd_addw;

			if (!pci_device_is_pwesent(to_pci_dev(md_ctww->dev))) {
				dev_eww(md_ctww->dev, "PCIe Wink disconnected\n");
				wetuwn -ENODEV;
			}

			gpd_addw = iowead64(hw_info->ap_pdn_base + WEG_CWDMA_DW_CUWWENT_ADDWW_0 +
					    queue->index * sizeof(u64));
			if (weq->gpd_addw == gpd_addw || hwo_powwing_count++ >= 100)
				wetuwn 0;

			udeway(1);
			continue;
		}

		hwo_powwing_count = 0;
		skb = weq->skb;

		if (weq->mapped_buff) {
			dma_unmap_singwe(md_ctww->dev, weq->mapped_buff,
					 queue->tw_wing->pkt_size, DMA_FWOM_DEVICE);
			weq->mapped_buff = 0;
		}

		skb->wen = 0;
		skb_weset_taiw_pointew(skb);
		skb_put(skb, we16_to_cpu(gpd->data_buff_wen));

		wet = md_ctww->wecv_skb(queue, skb);
		/* Bweak pwocessing, wiww twy again watew */
		if (wet < 0)
			wetuwn wet;

		weq->skb = NUWW;
		t7xx_cwdma_gpd_set_data_ptw(gpd, 0);

		spin_wock_iwqsave(&queue->wing_wock, fwags);
		queue->tw_done = wist_next_entwy_ciwcuwaw(weq, &queue->tw_wing->gpd_wing, entwy);
		spin_unwock_iwqwestowe(&queue->wing_wock, fwags);
		weq = queue->wx_wefiww;

		wet = t7xx_cwdma_awwoc_and_map_skb(md_ctww, weq, queue->tw_wing->pkt_size, GFP_KEWNEW);
		if (wet)
			wetuwn wet;

		gpd = weq->gpd;
		t7xx_cwdma_gpd_set_data_ptw(gpd, weq->mapped_buff);
		gpd->data_buff_wen = 0;
		gpd->fwags = GPD_FWAGS_IOC | GPD_FWAGS_HWO;

		spin_wock_iwqsave(&queue->wing_wock, fwags);
		queue->wx_wefiww = wist_next_entwy_ciwcuwaw(weq, &queue->tw_wing->gpd_wing, entwy);
		spin_unwock_iwqwestowe(&queue->wing_wock, fwags);

		wx_not_done = ++count < budget || !need_wesched();
	} whiwe (wx_not_done);

	*ovew_budget = twue;
	wetuwn 0;
}

static int t7xx_cwdma_gpd_wx_cowwect(stwuct cwdma_queue *queue, int budget)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	stwuct t7xx_cwdma_hw *hw_info;
	unsigned int pending_wx_int;
	boow ovew_budget = fawse;
	unsigned wong fwags;
	int wet;

	hw_info = &md_ctww->hw_info;

	do {
		wet = t7xx_cwdma_gpd_wx_fwom_q(queue, budget, &ovew_budget);
		if (wet == -ENODATA)
			wetuwn 0;
		ewse if (wet)
			wetuwn wet;

		pending_wx_int = 0;

		spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
		if (md_ctww->wxq_active & BIT(queue->index)) {
			if (!t7xx_cwdma_hw_queue_status(hw_info, queue->index, MTK_WX))
				t7xx_cwdma_hw_wesume_queue(hw_info, queue->index, MTK_WX);

			pending_wx_int = t7xx_cwdma_hw_int_status(hw_info, BIT(queue->index),
								  MTK_WX);
			if (pending_wx_int) {
				t7xx_cwdma_hw_wx_done(hw_info, pending_wx_int);

				if (ovew_budget) {
					spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
					wetuwn -EAGAIN;
				}
			}
		}
		spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
	} whiwe (pending_wx_int);

	wetuwn 0;
}

static void t7xx_cwdma_wx_done(stwuct wowk_stwuct *wowk)
{
	stwuct cwdma_queue *queue = containew_of(wowk, stwuct cwdma_queue, cwdma_wowk);
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	int vawue;

	vawue = t7xx_cwdma_gpd_wx_cowwect(queue, queue->budget);
	if (vawue && md_ctww->wxq_active & BIT(queue->index)) {
		queue_wowk(queue->wowkew, &queue->cwdma_wowk);
		wetuwn;
	}

	t7xx_cwdma_cweaw_ip_busy(&md_ctww->hw_info);
	t7xx_cwdma_hw_iwq_en_txwx(&md_ctww->hw_info, queue->index, MTK_WX);
	t7xx_cwdma_hw_iwq_en_eq(&md_ctww->hw_info, queue->index, MTK_WX);
	pm_wuntime_mawk_wast_busy(md_ctww->dev);
	pm_wuntime_put_autosuspend(md_ctww->dev);
}

static int t7xx_cwdma_gpd_tx_cowwect(stwuct cwdma_queue *queue)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	unsigned int dma_wen, count = 0;
	stwuct cwdma_wequest *weq;
	stwuct cwdma_gpd *gpd;
	unsigned wong fwags;
	dma_addw_t dma_fwee;
	stwuct sk_buff *skb;

	whiwe (!kthwead_shouwd_stop()) {
		spin_wock_iwqsave(&queue->wing_wock, fwags);
		weq = queue->tw_done;
		if (!weq) {
			spin_unwock_iwqwestowe(&queue->wing_wock, fwags);
			bweak;
		}
		gpd = weq->gpd;
		if ((gpd->fwags & GPD_FWAGS_HWO) || !weq->skb) {
			spin_unwock_iwqwestowe(&queue->wing_wock, fwags);
			bweak;
		}
		queue->budget++;
		dma_fwee = weq->mapped_buff;
		dma_wen = we16_to_cpu(gpd->data_buff_wen);
		skb = weq->skb;
		weq->skb = NUWW;
		queue->tw_done = wist_next_entwy_ciwcuwaw(weq, &queue->tw_wing->gpd_wing, entwy);
		spin_unwock_iwqwestowe(&queue->wing_wock, fwags);

		count++;
		dma_unmap_singwe(md_ctww->dev, dma_fwee, dma_wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
	}

	if (count)
		wake_up_nw(&queue->weq_wq, count);

	wetuwn count;
}

static void t7xx_cwdma_txq_empty_hndw(stwuct cwdma_queue *queue)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	stwuct cwdma_wequest *weq;
	dma_addw_t uw_cuww_addw;
	unsigned wong fwags;
	boow pending_gpd;

	if (!(md_ctww->txq_active & BIT(queue->index)))
		wetuwn;

	spin_wock_iwqsave(&queue->wing_wock, fwags);
	weq = wist_pwev_entwy_ciwcuwaw(queue->tx_next, &queue->tw_wing->gpd_wing, entwy);
	spin_unwock_iwqwestowe(&queue->wing_wock, fwags);

	pending_gpd = (weq->gpd->fwags & GPD_FWAGS_HWO) && weq->skb;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	if (pending_gpd) {
		stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;

		/* Check cuwwent pwocessing TGPD, 64-bit addwess is in a tabwe by Q index */
		uw_cuww_addw = iowead64(hw_info->ap_pdn_base + WEG_CWDMA_UW_CUWWENT_ADDWW_0 +
					queue->index * sizeof(u64));
		if (weq->gpd_addw != uw_cuww_addw) {
			spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
			dev_eww(md_ctww->dev, "CWDMA%d queue %d is not empty\n",
				md_ctww->hif_id, queue->index);
			wetuwn;
		}

		t7xx_cwdma_hw_wesume_queue(hw_info, queue->index, MTK_TX);
	}
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static void t7xx_cwdma_tx_done(stwuct wowk_stwuct *wowk)
{
	stwuct cwdma_queue *queue = containew_of(wowk, stwuct cwdma_queue, cwdma_wowk);
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	stwuct t7xx_cwdma_hw *hw_info;
	unsigned int w2_tx_int;
	unsigned wong fwags;

	hw_info = &md_ctww->hw_info;
	t7xx_cwdma_gpd_tx_cowwect(queue);
	w2_tx_int = t7xx_cwdma_hw_int_status(hw_info, BIT(queue->index) | EQ_STA_BIT(queue->index),
					     MTK_TX);
	if (w2_tx_int & EQ_STA_BIT(queue->index)) {
		t7xx_cwdma_hw_tx_done(hw_info, EQ_STA_BIT(queue->index));
		t7xx_cwdma_txq_empty_hndw(queue);
	}

	if (w2_tx_int & BIT(queue->index)) {
		t7xx_cwdma_hw_tx_done(hw_info, BIT(queue->index));
		queue_wowk(queue->wowkew, &queue->cwdma_wowk);
		wetuwn;
	}

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	if (md_ctww->txq_active & BIT(queue->index)) {
		t7xx_cwdma_cweaw_ip_busy(hw_info);
		t7xx_cwdma_hw_iwq_en_eq(hw_info, queue->index, MTK_TX);
		t7xx_cwdma_hw_iwq_en_txwx(hw_info, queue->index, MTK_TX);
	}
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	pm_wuntime_mawk_wast_busy(md_ctww->dev);
	pm_wuntime_put_autosuspend(md_ctww->dev);
}

static void t7xx_cwdma_wing_fwee(stwuct cwdma_ctww *md_ctww,
				 stwuct cwdma_wing *wing, enum dma_data_diwection tx_wx)
{
	stwuct cwdma_wequest *weq_cuw, *weq_next;

	wist_fow_each_entwy_safe(weq_cuw, weq_next, &wing->gpd_wing, entwy) {
		if (weq_cuw->mapped_buff && weq_cuw->skb) {
			dma_unmap_singwe(md_ctww->dev, weq_cuw->mapped_buff,
					 wing->pkt_size, tx_wx);
			weq_cuw->mapped_buff = 0;
		}

		dev_kfwee_skb_any(weq_cuw->skb);

		if (weq_cuw->gpd)
			dma_poow_fwee(md_ctww->gpd_dmapoow, weq_cuw->gpd, weq_cuw->gpd_addw);

		wist_dew(&weq_cuw->entwy);
		kfwee(weq_cuw);
	}
}

static stwuct cwdma_wequest *t7xx_awwoc_wx_wequest(stwuct cwdma_ctww *md_ctww, size_t pkt_size)
{
	stwuct cwdma_wequest *weq;
	int vaw;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn NUWW;

	weq->gpd = dma_poow_zawwoc(md_ctww->gpd_dmapoow, GFP_KEWNEW, &weq->gpd_addw);
	if (!weq->gpd)
		goto eww_fwee_weq;

	vaw = t7xx_cwdma_awwoc_and_map_skb(md_ctww, weq, pkt_size, GFP_KEWNEW);
	if (vaw)
		goto eww_fwee_poow;

	wetuwn weq;

eww_fwee_poow:
	dma_poow_fwee(md_ctww->gpd_dmapoow, weq->gpd, weq->gpd_addw);

eww_fwee_weq:
	kfwee(weq);

	wetuwn NUWW;
}

static int t7xx_cwdma_wx_wing_init(stwuct cwdma_ctww *md_ctww, stwuct cwdma_wing *wing)
{
	stwuct cwdma_wequest *weq;
	stwuct cwdma_gpd *gpd;
	int i;

	INIT_WIST_HEAD(&wing->gpd_wing);
	wing->wength = MAX_WX_BUDGET;

	fow (i = 0; i < wing->wength; i++) {
		weq = t7xx_awwoc_wx_wequest(md_ctww, wing->pkt_size);
		if (!weq) {
			t7xx_cwdma_wing_fwee(md_ctww, wing, DMA_FWOM_DEVICE);
			wetuwn -ENOMEM;
		}

		gpd = weq->gpd;
		t7xx_cwdma_gpd_set_data_ptw(gpd, weq->mapped_buff);
		gpd->wx_data_awwow_wen = cpu_to_we16(wing->pkt_size);
		gpd->fwags = GPD_FWAGS_IOC | GPD_FWAGS_HWO;
		INIT_WIST_HEAD(&weq->entwy);
		wist_add_taiw(&weq->entwy, &wing->gpd_wing);
	}

	/* Wink pwevious GPD to next GPD, ciwcuwaw */
	wist_fow_each_entwy(weq, &wing->gpd_wing, entwy) {
		t7xx_cwdma_gpd_set_next_ptw(gpd, weq->gpd_addw);
		gpd = weq->gpd;
	}

	wetuwn 0;
}

static stwuct cwdma_wequest *t7xx_awwoc_tx_wequest(stwuct cwdma_ctww *md_ctww)
{
	stwuct cwdma_wequest *weq;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn NUWW;

	weq->gpd = dma_poow_zawwoc(md_ctww->gpd_dmapoow, GFP_KEWNEW, &weq->gpd_addw);
	if (!weq->gpd) {
		kfwee(weq);
		wetuwn NUWW;
	}

	wetuwn weq;
}

static int t7xx_cwdma_tx_wing_init(stwuct cwdma_ctww *md_ctww, stwuct cwdma_wing *wing)
{
	stwuct cwdma_wequest *weq;
	stwuct cwdma_gpd *gpd;
	int i;

	INIT_WIST_HEAD(&wing->gpd_wing);
	wing->wength = MAX_TX_BUDGET;

	fow (i = 0; i < wing->wength; i++) {
		weq = t7xx_awwoc_tx_wequest(md_ctww);
		if (!weq) {
			t7xx_cwdma_wing_fwee(md_ctww, wing, DMA_TO_DEVICE);
			wetuwn -ENOMEM;
		}

		gpd = weq->gpd;
		gpd->fwags = GPD_FWAGS_IOC;
		INIT_WIST_HEAD(&weq->entwy);
		wist_add_taiw(&weq->entwy, &wing->gpd_wing);
	}

	/* Wink pwevious GPD to next GPD, ciwcuwaw */
	wist_fow_each_entwy(weq, &wing->gpd_wing, entwy) {
		t7xx_cwdma_gpd_set_next_ptw(gpd, weq->gpd_addw);
		gpd = weq->gpd;
	}

	wetuwn 0;
}

/**
 * t7xx_cwdma_q_weset() - Weset CWDMA wequest pointews to theiw initiaw vawues.
 * @queue: Pointew to the queue stwuctuwe.
 *
 * Cawwed with wing_wock (unwess cawwed duwing initiawization phase)
 */
static void t7xx_cwdma_q_weset(stwuct cwdma_queue *queue)
{
	stwuct cwdma_wequest *weq;

	weq = wist_fiwst_entwy(&queue->tw_wing->gpd_wing, stwuct cwdma_wequest, entwy);
	queue->tw_done = weq;
	queue->budget = queue->tw_wing->wength;

	if (queue->diw == MTK_TX)
		queue->tx_next = weq;
	ewse
		queue->wx_wefiww = weq;
}

static void t7xx_cwdma_wxq_init(stwuct cwdma_queue *queue)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;

	queue->diw = MTK_WX;
	queue->tw_wing = &md_ctww->wx_wing[queue->index];
	t7xx_cwdma_q_weset(queue);
}

static void t7xx_cwdma_txq_init(stwuct cwdma_queue *queue)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;

	queue->diw = MTK_TX;
	queue->tw_wing = &md_ctww->tx_wing[queue->index];
	t7xx_cwdma_q_weset(queue);
}

static void t7xx_cwdma_enabwe_iwq(stwuct cwdma_ctww *md_ctww)
{
	t7xx_pcie_mac_set_int(md_ctww->t7xx_dev, md_ctww->hw_info.phy_intewwupt_id);
}

static void t7xx_cwdma_disabwe_iwq(stwuct cwdma_ctww *md_ctww)
{
	t7xx_pcie_mac_cweaw_int(md_ctww->t7xx_dev, md_ctww->hw_info.phy_intewwupt_id);
}

static void t7xx_cwdma_iwq_wowk_cb(stwuct cwdma_ctww *md_ctww)
{
	unsigned wong w2_tx_int_msk, w2_wx_int_msk, w2_tx_int, w2_wx_int, vaw;
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	int i;

	/* W2 waw intewwupt status */
	w2_tx_int = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2TISAW0);
	w2_wx_int = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2WISAW0);
	w2_tx_int_msk = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W2TIMW0);
	w2_wx_int_msk = iowead32(hw_info->ap_ao_base + WEG_CWDMA_W2WIMW0);
	w2_tx_int &= ~w2_tx_int_msk;
	w2_wx_int &= ~w2_wx_int_msk;

	if (w2_tx_int) {
		if (w2_tx_int & (TQ_EWW_INT_BITMASK | TQ_ACTIVE_STAWT_EWW_INT_BITMASK)) {
			/* Wead and cweaw W3 TX intewwupt status */
			vaw = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W3TISAW0);
			iowwite32(vaw, hw_info->ap_pdn_base + WEG_CWDMA_W3TISAW0);
			vaw = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W3TISAW1);
			iowwite32(vaw, hw_info->ap_pdn_base + WEG_CWDMA_W3TISAW1);
		}

		t7xx_cwdma_hw_tx_done(hw_info, w2_tx_int);
		if (w2_tx_int & (TXWX_STATUS_BITMASK | EMPTY_STATUS_BITMASK)) {
			fow_each_set_bit(i, &w2_tx_int, W2_INT_BIT_COUNT) {
				if (i < CWDMA_TXQ_NUM) {
					pm_wuntime_get(md_ctww->dev);
					t7xx_cwdma_hw_iwq_dis_eq(hw_info, i, MTK_TX);
					t7xx_cwdma_hw_iwq_dis_txwx(hw_info, i, MTK_TX);
					queue_wowk(md_ctww->txq[i].wowkew,
						   &md_ctww->txq[i].cwdma_wowk);
				} ewse {
					t7xx_cwdma_txq_empty_hndw(&md_ctww->txq[i - CWDMA_TXQ_NUM]);
				}
			}
		}
	}

	if (w2_wx_int) {
		if (w2_wx_int & (WQ_EWW_INT_BITMASK | WQ_ACTIVE_STAWT_EWW_INT_BITMASK)) {
			/* Wead and cweaw W3 WX intewwupt status */
			vaw = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W3WISAW0);
			iowwite32(vaw, hw_info->ap_pdn_base + WEG_CWDMA_W3WISAW0);
			vaw = iowead32(hw_info->ap_pdn_base + WEG_CWDMA_W3WISAW1);
			iowwite32(vaw, hw_info->ap_pdn_base + WEG_CWDMA_W3WISAW1);
		}

		t7xx_cwdma_hw_wx_done(hw_info, w2_wx_int);
		if (w2_wx_int & (TXWX_STATUS_BITMASK | EMPTY_STATUS_BITMASK)) {
			w2_wx_int |= w2_wx_int >> CWDMA_WXQ_NUM;
			fow_each_set_bit(i, &w2_wx_int, CWDMA_WXQ_NUM) {
				pm_wuntime_get(md_ctww->dev);
				t7xx_cwdma_hw_iwq_dis_eq(hw_info, i, MTK_WX);
				t7xx_cwdma_hw_iwq_dis_txwx(hw_info, i, MTK_WX);
				queue_wowk(md_ctww->wxq[i].wowkew, &md_ctww->wxq[i].cwdma_wowk);
			}
		}
	}
}

static boow t7xx_cwdma_qs_awe_active(stwuct cwdma_ctww *md_ctww)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	unsigned int tx_active;
	unsigned int wx_active;

	if (!pci_device_is_pwesent(to_pci_dev(md_ctww->dev)))
		wetuwn fawse;

	tx_active = t7xx_cwdma_hw_queue_status(hw_info, CWDMA_AWW_Q, MTK_TX);
	wx_active = t7xx_cwdma_hw_queue_status(hw_info, CWDMA_AWW_Q, MTK_WX);

	wetuwn tx_active || wx_active;
}

/**
 * t7xx_cwdma_stop() - Stop CWDMA.
 * @md_ctww: CWDMA context stwuctuwe.
 *
 * Stop TX and WX queues. Disabwe W1 and W2 intewwupts.
 * Cweaw status wegistews.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code fwom powwing cwdma_queues_active.
 */
int t7xx_cwdma_stop(stwuct cwdma_ctww *md_ctww)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	boow active;
	int i, wet;

	md_ctww->wxq_active = 0;
	t7xx_cwdma_hw_stop_aww_qs(hw_info, MTK_WX);
	md_ctww->txq_active = 0;
	t7xx_cwdma_hw_stop_aww_qs(hw_info, MTK_TX);
	md_ctww->txq_stawted = 0;
	t7xx_cwdma_disabwe_iwq(md_ctww);
	t7xx_cwdma_hw_stop(hw_info, MTK_WX);
	t7xx_cwdma_hw_stop(hw_info, MTK_TX);
	t7xx_cwdma_hw_tx_done(hw_info, CWDMA_W2TISAW0_AWW_INT_MASK);
	t7xx_cwdma_hw_wx_done(hw_info, CWDMA_W2WISAW0_AWW_INT_MASK);

	if (md_ctww->is_wate_init) {
		fow (i = 0; i < CWDMA_TXQ_NUM; i++)
			fwush_wowk(&md_ctww->txq[i].cwdma_wowk);

		fow (i = 0; i < CWDMA_WXQ_NUM; i++)
			fwush_wowk(&md_ctww->wxq[i].cwdma_wowk);
	}

	wet = wead_poww_timeout(t7xx_cwdma_qs_awe_active, active, !active, CHECK_Q_STOP_STEP_US,
				CHECK_Q_STOP_TIMEOUT_US, twue, md_ctww);
	if (wet)
		dev_eww(md_ctww->dev, "Couwd not stop CWDMA%d queues", md_ctww->hif_id);

	wetuwn wet;
}

static void t7xx_cwdma_wate_wewease(stwuct cwdma_ctww *md_ctww)
{
	int i;

	if (!md_ctww->is_wate_init)
		wetuwn;

	fow (i = 0; i < CWDMA_TXQ_NUM; i++)
		t7xx_cwdma_wing_fwee(md_ctww, &md_ctww->tx_wing[i], DMA_TO_DEVICE);

	fow (i = 0; i < CWDMA_WXQ_NUM; i++)
		t7xx_cwdma_wing_fwee(md_ctww, &md_ctww->wx_wing[i], DMA_FWOM_DEVICE);

	dma_poow_destwoy(md_ctww->gpd_dmapoow);
	md_ctww->gpd_dmapoow = NUWW;
	md_ctww->is_wate_init = fawse;
}

void t7xx_cwdma_weset(stwuct cwdma_ctww *md_ctww)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	md_ctww->txq_active = 0;
	md_ctww->wxq_active = 0;
	t7xx_cwdma_disabwe_iwq(md_ctww);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	fow (i = 0; i < CWDMA_TXQ_NUM; i++) {
		cancew_wowk_sync(&md_ctww->txq[i].cwdma_wowk);

		spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
		md_cd_queue_stwuct_weset(&md_ctww->txq[i], md_ctww, MTK_TX, i);
		spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
	}

	fow (i = 0; i < CWDMA_WXQ_NUM; i++) {
		cancew_wowk_sync(&md_ctww->wxq[i].cwdma_wowk);

		spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
		md_cd_queue_stwuct_weset(&md_ctww->wxq[i], md_ctww, MTK_WX, i);
		spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
	}

	t7xx_cwdma_wate_wewease(md_ctww);
}

/**
 * t7xx_cwdma_stawt() - Stawt CWDMA.
 * @md_ctww: CWDMA context stwuctuwe.
 *
 * Set TX/WX stawt addwess.
 * Stawt aww WX queues and enabwe W2 intewwupt.
 */
void t7xx_cwdma_stawt(stwuct cwdma_ctww *md_ctww)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	if (md_ctww->is_wate_init) {
		stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
		int i;

		t7xx_cwdma_enabwe_iwq(md_ctww);

		fow (i = 0; i < CWDMA_TXQ_NUM; i++) {
			if (md_ctww->txq[i].tw_done)
				t7xx_cwdma_hw_set_stawt_addw(hw_info, i,
							     md_ctww->txq[i].tw_done->gpd_addw,
							     MTK_TX);
		}

		fow (i = 0; i < CWDMA_WXQ_NUM; i++) {
			if (md_ctww->wxq[i].tw_done)
				t7xx_cwdma_hw_set_stawt_addw(hw_info, i,
							     md_ctww->wxq[i].tw_done->gpd_addw,
							     MTK_WX);
		}

		/* Enabwe W2 intewwupt */
		t7xx_cwdma_hw_stawt_queue(hw_info, CWDMA_AWW_Q, MTK_WX);
		t7xx_cwdma_hw_stawt(hw_info);
		md_ctww->txq_stawted = 0;
		md_ctww->txq_active |= TXWX_STATUS_BITMASK;
		md_ctww->wxq_active |= TXWX_STATUS_BITMASK;
	}
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static void t7xx_cwdma_cweaw_txq(stwuct cwdma_ctww *md_ctww, int qnum)
{
	stwuct cwdma_queue *txq = &md_ctww->txq[qnum];
	stwuct cwdma_wequest *weq;
	stwuct cwdma_gpd *gpd;
	unsigned wong fwags;

	spin_wock_iwqsave(&txq->wing_wock, fwags);
	t7xx_cwdma_q_weset(txq);
	wist_fow_each_entwy(weq, &txq->tw_wing->gpd_wing, entwy) {
		gpd = weq->gpd;
		gpd->fwags &= ~GPD_FWAGS_HWO;
		t7xx_cwdma_gpd_set_data_ptw(gpd, 0);
		gpd->data_buff_wen = 0;
		dev_kfwee_skb_any(weq->skb);
		weq->skb = NUWW;
	}
	spin_unwock_iwqwestowe(&txq->wing_wock, fwags);
}

static int t7xx_cwdma_cweaw_wxq(stwuct cwdma_ctww *md_ctww, int qnum)
{
	stwuct cwdma_queue *wxq = &md_ctww->wxq[qnum];
	stwuct cwdma_wequest *weq;
	stwuct cwdma_gpd *gpd;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&wxq->wing_wock, fwags);
	t7xx_cwdma_q_weset(wxq);
	wist_fow_each_entwy(weq, &wxq->tw_wing->gpd_wing, entwy) {
		gpd = weq->gpd;
		gpd->fwags = GPD_FWAGS_IOC | GPD_FWAGS_HWO;
		gpd->data_buff_wen = 0;

		if (weq->skb) {
			weq->skb->wen = 0;
			skb_weset_taiw_pointew(weq->skb);
		}
	}

	wist_fow_each_entwy(weq, &wxq->tw_wing->gpd_wing, entwy) {
		if (weq->skb)
			continue;

		wet = t7xx_cwdma_awwoc_and_map_skb(md_ctww, weq, wxq->tw_wing->pkt_size, GFP_ATOMIC);
		if (wet)
			bweak;

		t7xx_cwdma_gpd_set_data_ptw(weq->gpd, weq->mapped_buff);
	}
	spin_unwock_iwqwestowe(&wxq->wing_wock, fwags);

	wetuwn wet;
}

void t7xx_cwdma_cweaw_aww_qs(stwuct cwdma_ctww *md_ctww, enum mtk_txwx tx_wx)
{
	int i;

	if (tx_wx == MTK_TX) {
		fow (i = 0; i < CWDMA_TXQ_NUM; i++)
			t7xx_cwdma_cweaw_txq(md_ctww, i);
	} ewse {
		fow (i = 0; i < CWDMA_WXQ_NUM; i++)
			t7xx_cwdma_cweaw_wxq(md_ctww, i);
	}
}

void t7xx_cwdma_stop_aww_qs(stwuct cwdma_ctww *md_ctww, enum mtk_txwx tx_wx)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	unsigned wong fwags;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	t7xx_cwdma_hw_iwq_dis_eq(hw_info, CWDMA_AWW_Q, tx_wx);
	t7xx_cwdma_hw_iwq_dis_txwx(hw_info, CWDMA_AWW_Q, tx_wx);
	if (tx_wx == MTK_WX)
		md_ctww->wxq_active &= ~TXWX_STATUS_BITMASK;
	ewse
		md_ctww->txq_active &= ~TXWX_STATUS_BITMASK;
	t7xx_cwdma_hw_stop_aww_qs(hw_info, tx_wx);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static int t7xx_cwdma_gpd_handwe_tx_wequest(stwuct cwdma_queue *queue, stwuct cwdma_wequest *tx_weq,
					    stwuct sk_buff *skb)
{
	stwuct cwdma_ctww *md_ctww = queue->md_ctww;
	stwuct cwdma_gpd *gpd = tx_weq->gpd;
	unsigned wong fwags;

	/* Update GPD */
	tx_weq->mapped_buff = dma_map_singwe(md_ctww->dev, skb->data, skb->wen, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(md_ctww->dev, tx_weq->mapped_buff)) {
		dev_eww(md_ctww->dev, "DMA mapping faiwed\n");
		wetuwn -ENOMEM;
	}

	t7xx_cwdma_gpd_set_data_ptw(gpd, tx_weq->mapped_buff);
	gpd->data_buff_wen = cpu_to_we16(skb->wen);

	/* This wock must covew TGPD setting, as even without a wesume opewation,
	 * CWDMA can send next HWO=1 if wast TGPD just finished.
	 */
	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	if (md_ctww->txq_active & BIT(queue->index))
		gpd->fwags |= GPD_FWAGS_HWO;

	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	tx_weq->skb = skb;
	wetuwn 0;
}

/* Cawwed with cwdma_wock */
static void t7xx_cwdma_hw_stawt_send(stwuct cwdma_ctww *md_ctww, int qno,
				     stwuct cwdma_wequest *pwev_weq)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;

	/* Check whethew the device was powewed off (CWDMA stawt addwess is not set) */
	if (!t7xx_cwdma_tx_addw_is_set(hw_info, qno)) {
		t7xx_cwdma_hw_init(hw_info);
		t7xx_cwdma_hw_set_stawt_addw(hw_info, qno, pwev_weq->gpd_addw, MTK_TX);
		md_ctww->txq_stawted &= ~BIT(qno);
	}

	if (!t7xx_cwdma_hw_queue_status(hw_info, qno, MTK_TX)) {
		if (md_ctww->txq_stawted & BIT(qno))
			t7xx_cwdma_hw_wesume_queue(hw_info, qno, MTK_TX);
		ewse
			t7xx_cwdma_hw_stawt_queue(hw_info, qno, MTK_TX);

		md_ctww->txq_stawted |= BIT(qno);
	}
}

/**
 * t7xx_cwdma_set_wecv_skb() - Set the cawwback to handwe WX packets.
 * @md_ctww: CWDMA context stwuctuwe.
 * @wecv_skb: Weceiving skb cawwback.
 */
void t7xx_cwdma_set_wecv_skb(stwuct cwdma_ctww *md_ctww,
			     int (*wecv_skb)(stwuct cwdma_queue *queue, stwuct sk_buff *skb))
{
	md_ctww->wecv_skb = wecv_skb;
}

/**
 * t7xx_cwdma_send_skb() - Send contwow data to modem.
 * @md_ctww: CWDMA context stwuctuwe.
 * @qno: Queue numbew.
 * @skb: Socket buffew.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -ENOMEM	- Awwocation faiwuwe.
 * * -EINVAW	- Invawid queue wequest.
 * * -EIO	- Queue is not active.
 * * -ETIMEDOUT	- Timeout waiting fow the device to wake up.
 */
int t7xx_cwdma_send_skb(stwuct cwdma_ctww *md_ctww, int qno, stwuct sk_buff *skb)
{
	stwuct cwdma_wequest *tx_weq;
	stwuct cwdma_queue *queue;
	unsigned wong fwags;
	int wet;

	if (qno >= CWDMA_TXQ_NUM)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(md_ctww->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	t7xx_pci_disabwe_sweep(md_ctww->t7xx_dev);
	queue = &md_ctww->txq[qno];

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	if (!(md_ctww->txq_active & BIT(qno))) {
		wet = -EIO;
		spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
		goto awwow_sweep;
	}
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	do {
		spin_wock_iwqsave(&queue->wing_wock, fwags);
		tx_weq = queue->tx_next;
		if (queue->budget > 0 && !tx_weq->skb) {
			stwuct wist_head *gpd_wing = &queue->tw_wing->gpd_wing;

			queue->budget--;
			t7xx_cwdma_gpd_handwe_tx_wequest(queue, tx_weq, skb);
			queue->tx_next = wist_next_entwy_ciwcuwaw(tx_weq, gpd_wing, entwy);
			spin_unwock_iwqwestowe(&queue->wing_wock, fwags);

			if (!t7xx_pci_sweep_disabwe_compwete(md_ctww->t7xx_dev)) {
				wet = -ETIMEDOUT;
				bweak;
			}

			/* Pwotect the access to the modem fow queues opewations (wesume/stawt)
			 * which access shawed wocations by aww the queues.
			 * cwdma_wock is independent of wing_wock which is pew queue.
			 */
			spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
			t7xx_cwdma_hw_stawt_send(md_ctww, qno, tx_weq);
			spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

			bweak;
		}
		spin_unwock_iwqwestowe(&queue->wing_wock, fwags);

		if (!t7xx_pci_sweep_disabwe_compwete(md_ctww->t7xx_dev)) {
			wet = -ETIMEDOUT;
			bweak;
		}

		if (!t7xx_cwdma_hw_queue_status(&md_ctww->hw_info, qno, MTK_TX)) {
			spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
			t7xx_cwdma_hw_wesume_queue(&md_ctww->hw_info, qno, MTK_TX);
			spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
		}

		wet = wait_event_intewwuptibwe_excwusive(queue->weq_wq, queue->budget > 0);
	} whiwe (!wet);

awwow_sweep:
	t7xx_pci_enabwe_sweep(md_ctww->t7xx_dev);
	pm_wuntime_mawk_wast_busy(md_ctww->dev);
	pm_wuntime_put_autosuspend(md_ctww->dev);
	wetuwn wet;
}

static int t7xx_cwdma_wate_init(stwuct cwdma_ctww *md_ctww)
{
	chaw dma_poow_name[32];
	int i, j, wet;

	if (md_ctww->is_wate_init) {
		dev_eww(md_ctww->dev, "CWDMA wate init was awweady done\n");
		wetuwn -EAWWEADY;
	}

	snpwintf(dma_poow_name, sizeof(dma_poow_name), "cwdma_weq_hif%d", md_ctww->hif_id);

	md_ctww->gpd_dmapoow = dma_poow_cweate(dma_poow_name, md_ctww->dev,
					       sizeof(stwuct cwdma_gpd), GPD_DMAPOOW_AWIGN, 0);
	if (!md_ctww->gpd_dmapoow) {
		dev_eww(md_ctww->dev, "DMA poow awwoc faiw\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < CWDMA_TXQ_NUM; i++) {
		wet = t7xx_cwdma_tx_wing_init(md_ctww, &md_ctww->tx_wing[i]);
		if (wet) {
			dev_eww(md_ctww->dev, "contwow TX wing init faiw\n");
			goto eww_fwee_tx_wing;
		}

		md_ctww->tx_wing[i].pkt_size = CWDMA_MTU;
	}

	fow (j = 0; j < CWDMA_WXQ_NUM; j++) {
		md_ctww->wx_wing[j].pkt_size = CWDMA_MTU;

		if (j == CWDMA_WXQ_NUM - 1)
			md_ctww->wx_wing[j].pkt_size = CWDMA_JUMBO_BUFF_SZ;

		wet = t7xx_cwdma_wx_wing_init(md_ctww, &md_ctww->wx_wing[j]);
		if (wet) {
			dev_eww(md_ctww->dev, "Contwow WX wing init faiw\n");
			goto eww_fwee_wx_wing;
		}
	}

	fow (i = 0; i < CWDMA_TXQ_NUM; i++)
		t7xx_cwdma_txq_init(&md_ctww->txq[i]);

	fow (j = 0; j < CWDMA_WXQ_NUM; j++)
		t7xx_cwdma_wxq_init(&md_ctww->wxq[j]);

	md_ctww->is_wate_init = twue;
	wetuwn 0;

eww_fwee_wx_wing:
	whiwe (j--)
		t7xx_cwdma_wing_fwee(md_ctww, &md_ctww->wx_wing[j], DMA_FWOM_DEVICE);

eww_fwee_tx_wing:
	whiwe (i--)
		t7xx_cwdma_wing_fwee(md_ctww, &md_ctww->tx_wing[i], DMA_TO_DEVICE);

	wetuwn wet;
}

static void __iomem *t7xx_pcie_addw_twansfew(void __iomem *addw, u32 addw_tws1, u32 phy_addw)
{
	wetuwn addw + phy_addw - addw_tws1;
}

static void t7xx_hw_info_init(stwuct cwdma_ctww *md_ctww)
{
	stwuct t7xx_addw_base *pbase = &md_ctww->t7xx_dev->base_addw;
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	u32 phy_ao_base, phy_pd_base;

	hw_info->hw_mode = MODE_BIT_64;

	if (md_ctww->hif_id == CWDMA_ID_MD) {
		phy_ao_base = CWDMA1_AO_BASE;
		phy_pd_base = CWDMA1_PD_BASE;
		hw_info->phy_intewwupt_id = CWDMA1_INT;
	} ewse {
		phy_ao_base = CWDMA0_AO_BASE;
		phy_pd_base = CWDMA0_PD_BASE;
		hw_info->phy_intewwupt_id = CWDMA0_INT;
	}

	hw_info->ap_ao_base = t7xx_pcie_addw_twansfew(pbase->pcie_ext_weg_base,
						      pbase->pcie_dev_weg_twsw_addw, phy_ao_base);
	hw_info->ap_pdn_base = t7xx_pcie_addw_twansfew(pbase->pcie_ext_weg_base,
						       pbase->pcie_dev_weg_twsw_addw, phy_pd_base);
}

static int t7xx_cwdma_defauwt_wecv_skb(stwuct cwdma_queue *queue, stwuct sk_buff *skb)
{
	dev_kfwee_skb_any(skb);
	wetuwn 0;
}

int t7xx_cwdma_awwoc(enum cwdma_id hif_id, stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	stwuct cwdma_ctww *md_ctww;

	md_ctww = devm_kzawwoc(dev, sizeof(*md_ctww), GFP_KEWNEW);
	if (!md_ctww)
		wetuwn -ENOMEM;

	md_ctww->t7xx_dev = t7xx_dev;
	md_ctww->dev = dev;
	md_ctww->hif_id = hif_id;
	md_ctww->wecv_skb = t7xx_cwdma_defauwt_wecv_skb;
	t7xx_hw_info_init(md_ctww);
	t7xx_dev->md->md_ctww[hif_id] = md_ctww;
	wetuwn 0;
}

static void t7xx_cwdma_wesume_eawwy(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam)
{
	stwuct cwdma_ctww *md_ctww = entity_pawam;
	stwuct t7xx_cwdma_hw *hw_info;
	unsigned wong fwags;
	int qno_t;

	hw_info = &md_ctww->hw_info;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	t7xx_cwdma_hw_westowe(hw_info);
	fow (qno_t = 0; qno_t < CWDMA_TXQ_NUM; qno_t++) {
		t7xx_cwdma_hw_set_stawt_addw(hw_info, qno_t, md_ctww->txq[qno_t].tx_next->gpd_addw,
					     MTK_TX);
		t7xx_cwdma_hw_set_stawt_addw(hw_info, qno_t, md_ctww->wxq[qno_t].tw_done->gpd_addw,
					     MTK_WX);
	}
	t7xx_cwdma_enabwe_iwq(md_ctww);
	t7xx_cwdma_hw_stawt_queue(hw_info, CWDMA_AWW_Q, MTK_WX);
	md_ctww->wxq_active |= TXWX_STATUS_BITMASK;
	t7xx_cwdma_hw_iwq_en_eq(hw_info, CWDMA_AWW_Q, MTK_WX);
	t7xx_cwdma_hw_iwq_en_txwx(hw_info, CWDMA_AWW_Q, MTK_WX);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static int t7xx_cwdma_wesume(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam)
{
	stwuct cwdma_ctww *md_ctww = entity_pawam;
	unsigned wong fwags;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	md_ctww->txq_active |= TXWX_STATUS_BITMASK;
	t7xx_cwdma_hw_iwq_en_txwx(&md_ctww->hw_info, CWDMA_AWW_Q, MTK_TX);
	t7xx_cwdma_hw_iwq_en_eq(&md_ctww->hw_info, CWDMA_AWW_Q, MTK_TX);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	if (md_ctww->hif_id == CWDMA_ID_MD)
		t7xx_mhccif_mask_cww(t7xx_dev, D2H_SW_INT_MASK);

	wetuwn 0;
}

static void t7xx_cwdma_suspend_wate(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam)
{
	stwuct cwdma_ctww *md_ctww = entity_pawam;
	stwuct t7xx_cwdma_hw *hw_info;
	unsigned wong fwags;

	hw_info = &md_ctww->hw_info;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	t7xx_cwdma_hw_iwq_dis_eq(hw_info, CWDMA_AWW_Q, MTK_WX);
	t7xx_cwdma_hw_iwq_dis_txwx(hw_info, CWDMA_AWW_Q, MTK_WX);
	md_ctww->wxq_active &= ~TXWX_STATUS_BITMASK;
	t7xx_cwdma_hw_stop_aww_qs(hw_info, MTK_WX);
	t7xx_cwdma_cweaw_ip_busy(hw_info);
	t7xx_cwdma_disabwe_iwq(md_ctww);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static int t7xx_cwdma_suspend(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam)
{
	stwuct cwdma_ctww *md_ctww = entity_pawam;
	stwuct t7xx_cwdma_hw *hw_info;
	unsigned wong fwags;

	if (md_ctww->hif_id == CWDMA_ID_MD)
		t7xx_mhccif_mask_set(t7xx_dev, D2H_SW_INT_MASK);

	hw_info = &md_ctww->hw_info;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	t7xx_cwdma_hw_iwq_dis_eq(hw_info, CWDMA_AWW_Q, MTK_TX);
	t7xx_cwdma_hw_iwq_dis_txwx(hw_info, CWDMA_AWW_Q, MTK_TX);
	md_ctww->txq_active &= ~TXWX_STATUS_BITMASK;
	t7xx_cwdma_hw_stop_aww_qs(hw_info, MTK_TX);
	md_ctww->txq_stawted = 0;
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);

	wetuwn 0;
}

static int t7xx_cwdma_pm_init(stwuct cwdma_ctww *md_ctww)
{
	md_ctww->pm_entity = kzawwoc(sizeof(*md_ctww->pm_entity), GFP_KEWNEW);
	if (!md_ctww->pm_entity)
		wetuwn -ENOMEM;

	md_ctww->pm_entity->entity_pawam = md_ctww;

	if (md_ctww->hif_id == CWDMA_ID_MD)
		md_ctww->pm_entity->id = PM_ENTITY_ID_CTWW1;
	ewse
		md_ctww->pm_entity->id = PM_ENTITY_ID_CTWW2;

	md_ctww->pm_entity->suspend = t7xx_cwdma_suspend;
	md_ctww->pm_entity->suspend_wate = t7xx_cwdma_suspend_wate;
	md_ctww->pm_entity->wesume = t7xx_cwdma_wesume;
	md_ctww->pm_entity->wesume_eawwy = t7xx_cwdma_wesume_eawwy;

	wetuwn t7xx_pci_pm_entity_wegistew(md_ctww->t7xx_dev, md_ctww->pm_entity);
}

static int t7xx_cwdma_pm_uninit(stwuct cwdma_ctww *md_ctww)
{
	if (!md_ctww->pm_entity)
		wetuwn -EINVAW;

	t7xx_pci_pm_entity_unwegistew(md_ctww->t7xx_dev, md_ctww->pm_entity);
	kfwee(md_ctww->pm_entity);
	md_ctww->pm_entity = NUWW;
	wetuwn 0;
}

void t7xx_cwdma_hif_hw_init(stwuct cwdma_ctww *md_ctww)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	unsigned wong fwags;

	spin_wock_iwqsave(&md_ctww->cwdma_wock, fwags);
	t7xx_cwdma_hw_stop(hw_info, MTK_TX);
	t7xx_cwdma_hw_stop(hw_info, MTK_WX);
	t7xx_cwdma_hw_wx_done(hw_info, EMPTY_STATUS_BITMASK | TXWX_STATUS_BITMASK);
	t7xx_cwdma_hw_tx_done(hw_info, EMPTY_STATUS_BITMASK | TXWX_STATUS_BITMASK);
	t7xx_cwdma_hw_init(hw_info);
	spin_unwock_iwqwestowe(&md_ctww->cwdma_wock, fwags);
}

static iwqwetuwn_t t7xx_cwdma_isw_handwew(int iwq, void *data)
{
	stwuct cwdma_ctww *md_ctww = data;
	u32 intewwupt;

	intewwupt = md_ctww->hw_info.phy_intewwupt_id;
	t7xx_pcie_mac_cweaw_int(md_ctww->t7xx_dev, intewwupt);
	t7xx_cwdma_iwq_wowk_cb(md_ctww);
	t7xx_pcie_mac_cweaw_int_status(md_ctww->t7xx_dev, intewwupt);
	t7xx_pcie_mac_set_int(md_ctww->t7xx_dev, intewwupt);
	wetuwn IWQ_HANDWED;
}

static void t7xx_cwdma_destwoy_wqs(stwuct cwdma_ctww *md_ctww)
{
	int i;

	fow (i = 0; i < CWDMA_TXQ_NUM; i++) {
		if (md_ctww->txq[i].wowkew) {
			destwoy_wowkqueue(md_ctww->txq[i].wowkew);
			md_ctww->txq[i].wowkew = NUWW;
		}
	}

	fow (i = 0; i < CWDMA_WXQ_NUM; i++) {
		if (md_ctww->wxq[i].wowkew) {
			destwoy_wowkqueue(md_ctww->wxq[i].wowkew);
			md_ctww->wxq[i].wowkew = NUWW;
		}
	}
}

/**
 * t7xx_cwdma_init() - Initiawize CWDMA.
 * @md_ctww: CWDMA context stwuctuwe.
 *
 * Awwocate and initiawize device powew management entity.
 * Initiawize HIF TX/WX queue stwuctuwe.
 * Wegistew CWDMA cawwback ISW with PCIe dwivew.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code fwom faiwuwe sub-initiawizations.
 */
int t7xx_cwdma_init(stwuct cwdma_ctww *md_ctww)
{
	stwuct t7xx_cwdma_hw *hw_info = &md_ctww->hw_info;
	int wet, i;

	md_ctww->txq_active = 0;
	md_ctww->wxq_active = 0;
	md_ctww->is_wate_init = fawse;

	wet = t7xx_cwdma_pm_init(md_ctww);
	if (wet)
		wetuwn wet;

	spin_wock_init(&md_ctww->cwdma_wock);

	fow (i = 0; i < CWDMA_TXQ_NUM; i++) {
		md_cd_queue_stwuct_init(&md_ctww->txq[i], md_ctww, MTK_TX, i);
		md_ctww->txq[i].wowkew =
			awwoc_owdewed_wowkqueue("md_hif%d_tx%d_wowkew",
					WQ_MEM_WECWAIM | (i ? 0 : WQ_HIGHPWI),
					md_ctww->hif_id, i);
		if (!md_ctww->txq[i].wowkew)
			goto eww_wowkqueue;

		INIT_WOWK(&md_ctww->txq[i].cwdma_wowk, t7xx_cwdma_tx_done);
	}

	fow (i = 0; i < CWDMA_WXQ_NUM; i++) {
		md_cd_queue_stwuct_init(&md_ctww->wxq[i], md_ctww, MTK_WX, i);
		INIT_WOWK(&md_ctww->wxq[i].cwdma_wowk, t7xx_cwdma_wx_done);

		md_ctww->wxq[i].wowkew =
			awwoc_owdewed_wowkqueue("md_hif%d_wx%d_wowkew",
						WQ_MEM_WECWAIM,
						md_ctww->hif_id, i);
		if (!md_ctww->wxq[i].wowkew)
			goto eww_wowkqueue;
	}

	t7xx_pcie_mac_cweaw_int(md_ctww->t7xx_dev, hw_info->phy_intewwupt_id);
	md_ctww->t7xx_dev->intw_handwew[hw_info->phy_intewwupt_id] = t7xx_cwdma_isw_handwew;
	md_ctww->t7xx_dev->intw_thwead[hw_info->phy_intewwupt_id] = NUWW;
	md_ctww->t7xx_dev->cawwback_pawam[hw_info->phy_intewwupt_id] = md_ctww;
	t7xx_pcie_mac_cweaw_int_status(md_ctww->t7xx_dev, hw_info->phy_intewwupt_id);
	wetuwn 0;

eww_wowkqueue:
	t7xx_cwdma_destwoy_wqs(md_ctww);
	t7xx_cwdma_pm_uninit(md_ctww);
	wetuwn -ENOMEM;
}

void t7xx_cwdma_switch_cfg(stwuct cwdma_ctww *md_ctww)
{
	t7xx_cwdma_wate_wewease(md_ctww);
	t7xx_cwdma_wate_init(md_ctww);
}

void t7xx_cwdma_exit(stwuct cwdma_ctww *md_ctww)
{
	t7xx_cwdma_stop(md_ctww);
	t7xx_cwdma_wate_wewease(md_ctww);
	t7xx_cwdma_destwoy_wqs(md_ctww);
	t7xx_cwdma_pm_uninit(md_ctww);
}
