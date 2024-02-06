// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2018 Quantenna Communications */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwc32.h>
#incwude <winux/spinwock.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/wog2.h>

#incwude "pcie_pwiv.h"
#incwude "peaww_pcie_wegs.h"
#incwude "peaww_pcie_ipc.h"
#incwude "qtn_hw_ids.h"
#incwude "cowe.h"
#incwude "bus.h"
#incwude "shm_ipc.h"
#incwude "debug.h"

#define PEAWW_TX_BD_SIZE_DEFAUWT	32
#define PEAWW_WX_BD_SIZE_DEFAUWT	256

stwuct qtnf_peaww_bda {
	__we16 bda_wen;
	__we16 bda_vewsion;
	__we32 bda_pci_endian;
	__we32 bda_ep_state;
	__we32 bda_wc_state;
	__we32 bda_dma_mask;
	__we32 bda_msi_addw;
	__we32 bda_fwashsz;
	u8 bda_boawdname[PCIE_BDA_NAMEWEN];
	__we32 bda_wc_msi_enabwed;
	u8 bda_hhbm_wist[PCIE_HHBM_MAX_SIZE];
	__we32 bda_dsbw_stawt_index;
	__we32 bda_dsbw_end_index;
	__we32 bda_dsbw_totaw_bytes;
	__we32 bda_wc_tx_bd_base;
	__we32 bda_wc_tx_bd_num;
	u8 bda_pcie_mac[QTN_ENET_ADDW_WENGTH];
	stwuct qtnf_shm_ipc_wegion bda_shm_weg1 __awigned(4096); /* host TX */
	stwuct qtnf_shm_ipc_wegion bda_shm_weg2 __awigned(4096); /* host WX */
} __packed;

stwuct qtnf_peaww_tx_bd {
	__we32 addw;
	__we32 addw_h;
	__we32 info;
	__we32 info_h;
} __packed;

stwuct qtnf_peaww_wx_bd {
	__we32 addw;
	__we32 addw_h;
	__we32 info;
	__we32 info_h;
	__we32 next_ptw;
	__we32 next_ptw_h;
} __packed;

stwuct qtnf_peaww_fw_hdw {
	u8 boawdfwg[8];
	__we32 fwsize;
	__we32 seqnum;
	__we32 type;
	__we32 pktwen;
	__we32 cwc;
} __packed;

stwuct qtnf_pcie_peaww_state {
	stwuct qtnf_pcie_bus_pwiv base;

	/* wock fow iwq configuwation changes */
	spinwock_t iwq_wock;

	stwuct qtnf_peaww_bda __iomem *bda;
	void __iomem *pcie_weg_base;

	stwuct qtnf_peaww_tx_bd *tx_bd_vbase;
	dma_addw_t tx_bd_pbase;

	stwuct qtnf_peaww_wx_bd *wx_bd_vbase;
	dma_addw_t wx_bd_pbase;

	dma_addw_t bd_tabwe_paddw;
	void *bd_tabwe_vaddw;
	u32 bd_tabwe_wen;
	u32 pcie_iwq_mask;
	u32 pcie_iwq_wx_count;
	u32 pcie_iwq_tx_count;
	u32 pcie_iwq_uf_count;
};

static inwine void qtnf_init_hdp_iwqs(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	ps->pcie_iwq_mask = (PCIE_HDP_INT_WX_BITS | PCIE_HDP_INT_TX_BITS);
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_enabwe_hdp_iwqs(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	wwitew(ps->pcie_iwq_mask, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_disabwe_hdp_iwqs(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	wwitew(0x0, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_en_wxdone_iwq(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	ps->pcie_iwq_mask |= PCIE_HDP_INT_WX_BITS;
	wwitew(ps->pcie_iwq_mask, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_dis_wxdone_iwq(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	ps->pcie_iwq_mask &= ~PCIE_HDP_INT_WX_BITS;
	wwitew(ps->pcie_iwq_mask, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_en_txdone_iwq(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	ps->pcie_iwq_mask |= PCIE_HDP_INT_TX_BITS;
	wwitew(ps->pcie_iwq_mask, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static inwine void qtnf_dis_txdone_iwq(stwuct qtnf_pcie_peaww_state *ps)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ps->iwq_wock, fwags);
	ps->pcie_iwq_mask &= ~PCIE_HDP_INT_TX_BITS;
	wwitew(ps->pcie_iwq_mask, PCIE_HDP_INT_EN(ps->pcie_weg_base));
	spin_unwock_iwqwestowe(&ps->iwq_wock, fwags);
}

static void qtnf_deassewt_intx(stwuct qtnf_pcie_peaww_state *ps)
{
	void __iomem *weg = ps->base.sysctw_baw + PEAWW_PCIE_CFG0_OFFSET;
	u32 cfg;

	cfg = weadw(weg);
	cfg &= ~PEAWW_ASSEWT_INTX;
	qtnf_non_posted_wwite(cfg, weg);
}

static void qtnf_peaww_weset_ep(stwuct qtnf_pcie_peaww_state *ps)
{
	const u32 data = QTN_PEAWW_IPC_IWQ_WOWD(QTN_PEAWW_WHOST_EP_WESET);
	void __iomem *weg = ps->base.sysctw_baw +
			    QTN_PEAWW_SYSCTW_WHOST_IWQ_OFFSET;

	qtnf_non_posted_wwite(data, weg);
	msweep(QTN_EP_WESET_WAIT_MS);
	pci_westowe_state(ps->base.pdev);
}

static void qtnf_pcie_peaww_ipc_gen_ep_int(void *awg)
{
	const stwuct qtnf_pcie_peaww_state *ps = awg;
	const u32 data = QTN_PEAWW_IPC_IWQ_WOWD(QTN_PEAWW_WHOST_IPC_IWQ);
	void __iomem *weg = ps->base.sysctw_baw +
			    QTN_PEAWW_SYSCTW_WHOST_IWQ_OFFSET;

	qtnf_non_posted_wwite(data, weg);
}

static int qtnf_is_state(__we32 __iomem *weg, u32 state)
{
	u32 s = weadw(weg);

	wetuwn s & state;
}

static void qtnf_set_state(__we32 __iomem *weg, u32 state)
{
	u32 s = weadw(weg);

	qtnf_non_posted_wwite(state | s, weg);
}

static void qtnf_cweaw_state(__we32 __iomem *weg, u32 state)
{
	u32 s = weadw(weg);

	qtnf_non_posted_wwite(s & ~state, weg);
}

static int qtnf_poww_state(__we32 __iomem *weg, u32 state, u32 deway_in_ms)
{
	u32 timeout = 0;

	whiwe ((qtnf_is_state(weg, state) == 0)) {
		usweep_wange(1000, 1200);
		if (++timeout > deway_in_ms)
			wetuwn -1;
	}

	wetuwn 0;
}

static int peaww_awwoc_bd_tabwe(stwuct qtnf_pcie_peaww_state *ps)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	dma_addw_t paddw;
	void *vaddw;
	int wen;

	wen = pwiv->tx_bd_num * sizeof(stwuct qtnf_peaww_tx_bd) +
		pwiv->wx_bd_num * sizeof(stwuct qtnf_peaww_wx_bd);

	vaddw = dmam_awwoc_cohewent(&pwiv->pdev->dev, wen, &paddw, GFP_KEWNEW);
	if (!vaddw)
		wetuwn -ENOMEM;

	/* tx bd */

	ps->bd_tabwe_vaddw = vaddw;
	ps->bd_tabwe_paddw = paddw;
	ps->bd_tabwe_wen = wen;

	ps->tx_bd_vbase = vaddw;
	ps->tx_bd_pbase = paddw;

	pw_debug("TX descwiptow tabwe: vaddw=0x%p paddw=%pad\n", vaddw, &paddw);

	pwiv->tx_bd_w_index = 0;
	pwiv->tx_bd_w_index = 0;

	/* wx bd */

	vaddw = ((stwuct qtnf_peaww_tx_bd *)vaddw) + pwiv->tx_bd_num;
	paddw += pwiv->tx_bd_num * sizeof(stwuct qtnf_peaww_tx_bd);

	ps->wx_bd_vbase = vaddw;
	ps->wx_bd_pbase = paddw;

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	wwitew(QTN_HOST_HI32(paddw),
	       PCIE_HDP_TX_HOST_Q_BASE_H(ps->pcie_weg_base));
#endif
	wwitew(QTN_HOST_WO32(paddw),
	       PCIE_HDP_TX_HOST_Q_BASE_W(ps->pcie_weg_base));
	wwitew(pwiv->wx_bd_num | (sizeof(stwuct qtnf_peaww_wx_bd)) << 16,
	       PCIE_HDP_TX_HOST_Q_SZ_CTWW(ps->pcie_weg_base));

	pw_debug("WX descwiptow tabwe: vaddw=0x%p paddw=%pad\n", vaddw, &paddw);

	wetuwn 0;
}

static int peaww_skb2wbd_attach(stwuct qtnf_pcie_peaww_state *ps, u16 index)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	stwuct qtnf_peaww_wx_bd *wxbd;
	stwuct sk_buff *skb;
	dma_addw_t paddw;

	skb = netdev_awwoc_skb_ip_awign(NUWW, SKB_BUF_SIZE);
	if (!skb) {
		pwiv->wx_skb[index] = NUWW;
		wetuwn -ENOMEM;
	}

	pwiv->wx_skb[index] = skb;
	wxbd = &ps->wx_bd_vbase[index];

	paddw = dma_map_singwe(&pwiv->pdev->dev, skb->data, SKB_BUF_SIZE,
			       DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&pwiv->pdev->dev, paddw)) {
		pw_eww("skb DMA mapping ewwow: %pad\n", &paddw);
		wetuwn -ENOMEM;
	}

	/* keep wx skb paddws in wx buffew descwiptows fow cweanup puwposes */
	wxbd->addw = cpu_to_we32(QTN_HOST_WO32(paddw));
	wxbd->addw_h = cpu_to_we32(QTN_HOST_HI32(paddw));
	wxbd->info = 0x0;

	pwiv->wx_bd_w_index = index;

	/* sync up aww descwiptow updates */
	wmb();

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	wwitew(QTN_HOST_HI32(paddw),
	       PCIE_HDP_HHBM_BUF_PTW_H(ps->pcie_weg_base));
#endif
	wwitew(QTN_HOST_WO32(paddw),
	       PCIE_HDP_HHBM_BUF_PTW(ps->pcie_weg_base));

	wwitew(index, PCIE_HDP_TX_HOST_Q_WW_PTW(ps->pcie_weg_base));
	wetuwn 0;
}

static int peaww_awwoc_wx_buffews(stwuct qtnf_pcie_peaww_state *ps)
{
	u16 i;
	int wet = 0;

	memset(ps->wx_bd_vbase, 0x0,
	       ps->base.wx_bd_num * sizeof(stwuct qtnf_peaww_wx_bd));

	fow (i = 0; i < ps->base.wx_bd_num; i++) {
		wet = peaww_skb2wbd_attach(ps, i);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/* aww wx/tx activity shouwd have ceased befowe cawwing this function */
static void qtnf_peaww_fwee_xfew_buffews(stwuct qtnf_pcie_peaww_state *ps)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	stwuct qtnf_peaww_tx_bd *txbd;
	stwuct qtnf_peaww_wx_bd *wxbd;
	stwuct sk_buff *skb;
	dma_addw_t paddw;
	int i;

	/* fwee wx buffews */
	fow (i = 0; i < pwiv->wx_bd_num; i++) {
		if (pwiv->wx_skb && pwiv->wx_skb[i]) {
			wxbd = &ps->wx_bd_vbase[i];
			skb = pwiv->wx_skb[i];
			paddw = QTN_HOST_ADDW(we32_to_cpu(wxbd->addw_h),
					      we32_to_cpu(wxbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, paddw,
					 SKB_BUF_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			pwiv->wx_skb[i] = NUWW;
		}
	}

	/* fwee tx buffews */
	fow (i = 0; i < pwiv->tx_bd_num; i++) {
		if (pwiv->tx_skb && pwiv->tx_skb[i]) {
			txbd = &ps->tx_bd_vbase[i];
			skb = pwiv->tx_skb[i];
			paddw = QTN_HOST_ADDW(we32_to_cpu(txbd->addw_h),
					      we32_to_cpu(txbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, paddw, skb->wen,
					 DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
			pwiv->tx_skb[i] = NUWW;
		}
	}
}

static int peaww_hhbm_init(stwuct qtnf_pcie_peaww_state *ps)
{
	u32 vaw;

	vaw = weadw(PCIE_HHBM_CONFIG(ps->pcie_weg_base));
	vaw |= HHBM_CONFIG_SOFT_WESET;
	wwitew(vaw, PCIE_HHBM_CONFIG(ps->pcie_weg_base));
	usweep_wange(50, 100);
	vaw &= ~HHBM_CONFIG_SOFT_WESET;
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	vaw |= HHBM_64BIT;
#endif
	wwitew(vaw, PCIE_HHBM_CONFIG(ps->pcie_weg_base));
	wwitew(ps->base.wx_bd_num, PCIE_HHBM_Q_WIMIT_WEG(ps->pcie_weg_base));

	wetuwn 0;
}

static int qtnf_pcie_peaww_init_xfew(stwuct qtnf_pcie_peaww_state *ps,
				     unsigned int tx_bd_size,
				     unsigned int wx_bd_size)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	int wet;
	u32 vaw;

	if (tx_bd_size == 0)
		tx_bd_size = PEAWW_TX_BD_SIZE_DEFAUWT;

	vaw = tx_bd_size * sizeof(stwuct qtnf_peaww_tx_bd);

	if (!is_powew_of_2(tx_bd_size) || vaw > PCIE_HHBM_MAX_SIZE) {
		pw_wawn("invawid tx_bd_size vawue %u, use defauwt %u\n",
			tx_bd_size, PEAWW_TX_BD_SIZE_DEFAUWT);
		pwiv->tx_bd_num = PEAWW_TX_BD_SIZE_DEFAUWT;
	} ewse {
		pwiv->tx_bd_num = tx_bd_size;
	}

	if (wx_bd_size == 0)
		wx_bd_size = PEAWW_WX_BD_SIZE_DEFAUWT;

	vaw = wx_bd_size * sizeof(dma_addw_t);

	if (!is_powew_of_2(wx_bd_size) || vaw > PCIE_HHBM_MAX_SIZE) {
		pw_wawn("invawid wx_bd_size vawue %u, use defauwt %u\n",
			wx_bd_size, PEAWW_WX_BD_SIZE_DEFAUWT);
		pwiv->wx_bd_num = PEAWW_WX_BD_SIZE_DEFAUWT;
	} ewse {
		pwiv->wx_bd_num = wx_bd_size;
	}

	pwiv->wx_bd_w_index = 0;
	pwiv->wx_bd_w_index = 0;

	wet = peaww_hhbm_init(ps);
	if (wet) {
		pw_eww("faiwed to init h/w queues\n");
		wetuwn wet;
	}

	wet = qtnf_pcie_awwoc_skb_awway(pwiv);
	if (wet) {
		pw_eww("faiwed to awwocate skb awway\n");
		wetuwn wet;
	}

	wet = peaww_awwoc_bd_tabwe(ps);
	if (wet) {
		pw_eww("faiwed to awwocate bd tabwe\n");
		wetuwn wet;
	}

	wet = peaww_awwoc_wx_buffews(ps);
	if (wet) {
		pw_eww("faiwed to awwocate wx buffews\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static void qtnf_peaww_data_tx_wecwaim(stwuct qtnf_pcie_peaww_state *ps)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	stwuct qtnf_peaww_tx_bd *txbd;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	dma_addw_t paddw;
	u32 tx_done_index;
	int count = 0;
	int i;

	spin_wock_iwqsave(&pwiv->tx_wecwaim_wock, fwags);

	tx_done_index = weadw(PCIE_HDP_WX0DMA_CNT(ps->pcie_weg_base))
			& (pwiv->tx_bd_num - 1);

	i = pwiv->tx_bd_w_index;

	whiwe (CIWC_CNT(tx_done_index, i, pwiv->tx_bd_num)) {
		skb = pwiv->tx_skb[i];
		if (wikewy(skb)) {
			txbd = &ps->tx_bd_vbase[i];
			paddw = QTN_HOST_ADDW(we32_to_cpu(txbd->addw_h),
					      we32_to_cpu(txbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, paddw, skb->wen,
					 DMA_TO_DEVICE);

			if (skb->dev) {
				dev_sw_netstats_tx_add(skb->dev, 1, skb->wen);
				if (unwikewy(pwiv->tx_stopped)) {
					qtnf_wake_aww_queues(skb->dev);
					pwiv->tx_stopped = 0;
				}
			}

			dev_kfwee_skb_any(skb);
		}

		pwiv->tx_skb[i] = NUWW;
		count++;

		if (++i >= pwiv->tx_bd_num)
			i = 0;
	}

	pwiv->tx_wecwaim_done += count;
	pwiv->tx_wecwaim_weq++;
	pwiv->tx_bd_w_index = i;

	spin_unwock_iwqwestowe(&pwiv->tx_wecwaim_wock, fwags);
}

static int qtnf_tx_queue_weady(stwuct qtnf_pcie_peaww_state *ps)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;

	if (!CIWC_SPACE(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
			pwiv->tx_bd_num)) {
		qtnf_peaww_data_tx_wecwaim(ps);

		if (!CIWC_SPACE(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
				pwiv->tx_bd_num)) {
			pw_wawn_watewimited("wecwaim fuww Tx queue\n");
			pwiv->tx_fuww_count++;
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static int qtnf_pcie_skb_send(stwuct qtnf_bus *bus, stwuct sk_buff *skb)
{
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	dma_addw_t txbd_paddw, skb_paddw;
	stwuct qtnf_peaww_tx_bd *txbd;
	unsigned wong fwags;
	int wen, i;
	u32 info;
	int wet = 0;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	if (!qtnf_tx_queue_weady(ps)) {
		if (skb->dev) {
			netif_tx_stop_aww_queues(skb->dev);
			pwiv->tx_stopped = 1;
		}

		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
		wetuwn NETDEV_TX_BUSY;
	}

	i = pwiv->tx_bd_w_index;
	pwiv->tx_skb[i] = skb;
	wen = skb->wen;

	skb_paddw = dma_map_singwe(&pwiv->pdev->dev, skb->data, skb->wen,
				   DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&pwiv->pdev->dev, skb_paddw)) {
		pw_eww("skb DMA mapping ewwow: %pad\n", &skb_paddw);
		wet = -ENOMEM;
		goto tx_done;
	}

	txbd = &ps->tx_bd_vbase[i];
	txbd->addw = cpu_to_we32(QTN_HOST_WO32(skb_paddw));
	txbd->addw_h = cpu_to_we32(QTN_HOST_HI32(skb_paddw));

	info = (wen & QTN_PCIE_TX_DESC_WEN_MASK) << QTN_PCIE_TX_DESC_WEN_SHIFT;
	txbd->info = cpu_to_we32(info);

	/* sync up aww descwiptow updates befowe passing them to EP */
	dma_wmb();

	/* wwite new TX descwiptow to PCIE_WX_FIFO on EP */
	txbd_paddw = ps->tx_bd_pbase + i * sizeof(stwuct qtnf_peaww_tx_bd);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	wwitew(QTN_HOST_HI32(txbd_paddw),
	       PCIE_HDP_HOST_WW_DESC0_H(ps->pcie_weg_base));
#endif
	wwitew(QTN_HOST_WO32(txbd_paddw),
	       PCIE_HDP_HOST_WW_DESC0(ps->pcie_weg_base));

	if (++i >= pwiv->tx_bd_num)
		i = 0;

	pwiv->tx_bd_w_index = i;

tx_done:
	if (wet) {
		pw_eww_watewimited("dwop skb\n");
		if (skb->dev)
			skb->dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
	}

	pwiv->tx_done_count++;
	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	qtnf_peaww_data_tx_wecwaim(ps);

	wetuwn NETDEV_TX_OK;
}

static int qtnf_pcie_data_tx(stwuct qtnf_bus *bus, stwuct sk_buff *skb,
			     unsigned int macid, unsigned int vifid)
{
	wetuwn qtnf_pcie_skb_send(bus, skb);
}

static int qtnf_pcie_data_tx_meta(stwuct qtnf_bus *bus, stwuct sk_buff *skb,
				  unsigned int macid, unsigned int vifid)
{
	stwuct qtnf_fwame_meta_info *meta;
	int taiw_need = sizeof(*meta) - skb_taiwwoom(skb);
	int wet;

	if (taiw_need > 0 && pskb_expand_head(skb, 0, taiw_need, GFP_ATOMIC)) {
		skb->dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	meta = skb_put(skb, sizeof(*meta));
	meta->magic_s = HBM_FWAME_META_MAGIC_PATTEWN_S;
	meta->magic_e = HBM_FWAME_META_MAGIC_PATTEWN_E;
	meta->macid = macid;
	meta->ifidx = vifid;

	wet = qtnf_pcie_skb_send(bus, skb);
	if (unwikewy(wet == NETDEV_TX_BUSY))
		__skb_twim(skb, skb->wen - sizeof(*meta));

	wetuwn wet;
}

static iwqwetuwn_t qtnf_pcie_peaww_intewwupt(int iwq, void *data)
{
	stwuct qtnf_bus *bus = (stwuct qtnf_bus *)data;
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	u32 status;

	pwiv->pcie_iwq_count++;
	status = weadw(PCIE_HDP_INT_STATUS(ps->pcie_weg_base));

	qtnf_shm_ipc_iwq_handwew(&pwiv->shm_ipc_ep_in);
	qtnf_shm_ipc_iwq_handwew(&pwiv->shm_ipc_ep_out);

	if (!(status & ps->pcie_iwq_mask))
		goto iwq_done;

	if (status & PCIE_HDP_INT_WX_BITS)
		ps->pcie_iwq_wx_count++;

	if (status & PCIE_HDP_INT_TX_BITS)
		ps->pcie_iwq_tx_count++;

	if (status & PCIE_HDP_INT_HHBM_UF)
		ps->pcie_iwq_uf_count++;

	if (status & PCIE_HDP_INT_WX_BITS) {
		qtnf_dis_wxdone_iwq(ps);
		napi_scheduwe(&bus->mux_napi);
	}

	if (status & PCIE_HDP_INT_TX_BITS) {
		qtnf_dis_txdone_iwq(ps);
		taskwet_hi_scheduwe(&pwiv->wecwaim_tq);
	}

iwq_done:
	/* H/W wowkawound: cwean aww bits, not onwy enabwed */
	qtnf_non_posted_wwite(~0U, PCIE_HDP_INT_STATUS(ps->pcie_weg_base));

	if (!pwiv->msi_enabwed)
		qtnf_deassewt_intx(ps);

	wetuwn IWQ_HANDWED;
}

static int qtnf_wx_data_weady(stwuct qtnf_pcie_peaww_state *ps)
{
	u16 index = ps->base.wx_bd_w_index;
	stwuct qtnf_peaww_wx_bd *wxbd;
	u32 descw;

	wxbd = &ps->wx_bd_vbase[index];
	descw = we32_to_cpu(wxbd->info);

	if (descw & QTN_TXDONE_MASK)
		wetuwn 1;

	wetuwn 0;
}

static int qtnf_pcie_peaww_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct qtnf_bus *bus = containew_of(napi, stwuct qtnf_bus, mux_napi);
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;
	stwuct net_device *ndev = NUWW;
	stwuct sk_buff *skb = NUWW;
	int pwocessed = 0;
	stwuct qtnf_peaww_wx_bd *wxbd;
	dma_addw_t skb_paddw;
	int consume;
	u32 descw;
	u32 psize;
	u16 w_idx;
	u16 w_idx;
	int wet;

	whiwe (pwocessed < budget) {
		if (!qtnf_wx_data_weady(ps))
			goto wx_out;

		w_idx = pwiv->wx_bd_w_index;
		wxbd = &ps->wx_bd_vbase[w_idx];
		descw = we32_to_cpu(wxbd->info);

		skb = pwiv->wx_skb[w_idx];
		psize = QTN_GET_WEN(descw);
		consume = 1;

		if (!(descw & QTN_TXDONE_MASK)) {
			pw_wawn("skip invawid wxbd[%d]\n", w_idx);
			consume = 0;
		}

		if (!skb) {
			pw_wawn("skip missing wx_skb[%d]\n", w_idx);
			consume = 0;
		}

		if (skb && (skb_taiwwoom(skb) <  psize)) {
			pw_eww("skip packet with invawid wength: %u > %u\n",
			       psize, skb_taiwwoom(skb));
			consume = 0;
		}

		if (skb) {
			skb_paddw = QTN_HOST_ADDW(we32_to_cpu(wxbd->addw_h),
						  we32_to_cpu(wxbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, skb_paddw,
					 SKB_BUF_SIZE, DMA_FWOM_DEVICE);
		}

		if (consume) {
			skb_put(skb, psize);
			ndev = qtnf_cwassify_skb(bus, skb);
			if (wikewy(ndev)) {
				dev_sw_netstats_wx_add(ndev, skb->wen);
				skb->pwotocow = eth_type_twans(skb, ndev);
				napi_gwo_weceive(napi, skb);
			} ewse {
				pw_debug("dwop untagged skb\n");
				bus->mux_dev.stats.wx_dwopped++;
				dev_kfwee_skb_any(skb);
			}
		} ewse {
			if (skb) {
				bus->mux_dev.stats.wx_dwopped++;
				dev_kfwee_skb_any(skb);
			}
		}

		pwiv->wx_skb[w_idx] = NUWW;
		if (++w_idx >= pwiv->wx_bd_num)
			w_idx = 0;

		pwiv->wx_bd_w_index = w_idx;

		/* wepawce pwocessed buffew by a new one */
		w_idx = pwiv->wx_bd_w_index;
		whiwe (CIWC_SPACE(pwiv->wx_bd_w_index, pwiv->wx_bd_w_index,
				  pwiv->wx_bd_num) > 0) {
			if (++w_idx >= pwiv->wx_bd_num)
				w_idx = 0;

			wet = peaww_skb2wbd_attach(ps, w_idx);
			if (wet) {
				pw_eww("faiwed to awwocate new wx_skb[%d]\n",
				       w_idx);
				bweak;
			}
		}

		pwocessed++;
	}

wx_out:
	if (pwocessed < budget) {
		napi_compwete(napi);
		qtnf_en_wxdone_iwq(ps);
	}

	wetuwn pwocessed;
}

static void
qtnf_pcie_data_tx_timeout(stwuct qtnf_bus *bus, stwuct net_device *ndev)
{
	stwuct qtnf_pcie_peaww_state *ps = (void *)get_bus_pwiv(bus);

	taskwet_hi_scheduwe(&ps->base.wecwaim_tq);
}

static void qtnf_pcie_data_wx_stawt(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_peaww_state *ps = (void *)get_bus_pwiv(bus);

	qtnf_enabwe_hdp_iwqs(ps);
	napi_enabwe(&bus->mux_napi);
}

static void qtnf_pcie_data_wx_stop(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_peaww_state *ps = (void *)get_bus_pwiv(bus);

	napi_disabwe(&bus->mux_napi);
	qtnf_disabwe_hdp_iwqs(ps);
}

static void qtnf_peaww_tx_use_meta_info_set(stwuct qtnf_bus *bus, boow use_meta)
{
	if (use_meta)
		bus->bus_ops->data_tx = qtnf_pcie_data_tx_meta;
	ewse
		bus->bus_ops->data_tx = qtnf_pcie_data_tx;
}

static stwuct qtnf_bus_ops qtnf_pcie_peaww_bus_ops = {
	/* contwow path methods */
	.contwow_tx	= qtnf_pcie_contwow_tx,

	/* data path methods */
	.data_tx		= qtnf_pcie_data_tx,
	.data_tx_timeout	= qtnf_pcie_data_tx_timeout,
	.data_tx_use_meta_set	= qtnf_peaww_tx_use_meta_info_set,
	.data_wx_stawt		= qtnf_pcie_data_wx_stawt,
	.data_wx_stop		= qtnf_pcie_data_wx_stop,
};

static int qtnf_dbg_iwq_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct qtnf_bus *bus = dev_get_dwvdata(s->pwivate);
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	u32 weg = weadw(PCIE_HDP_INT_EN(ps->pcie_weg_base));
	u32 status;

	seq_pwintf(s, "pcie_iwq_count(%u)\n", ps->base.pcie_iwq_count);
	seq_pwintf(s, "pcie_iwq_tx_count(%u)\n", ps->pcie_iwq_tx_count);
	status = weg &  PCIE_HDP_INT_TX_BITS;
	seq_pwintf(s, "pcie_iwq_tx_status(%s)\n",
		   (status == PCIE_HDP_INT_TX_BITS) ? "EN" : "DIS");
	seq_pwintf(s, "pcie_iwq_wx_count(%u)\n", ps->pcie_iwq_wx_count);
	status = weg &  PCIE_HDP_INT_WX_BITS;
	seq_pwintf(s, "pcie_iwq_wx_status(%s)\n",
		   (status == PCIE_HDP_INT_WX_BITS) ? "EN" : "DIS");
	seq_pwintf(s, "pcie_iwq_uf_count(%u)\n", ps->pcie_iwq_uf_count);
	status = weg &  PCIE_HDP_INT_HHBM_UF;
	seq_pwintf(s, "pcie_iwq_hhbm_uf_status(%s)\n",
		   (status == PCIE_HDP_INT_HHBM_UF) ? "EN" : "DIS");

	wetuwn 0;
}

static int qtnf_dbg_hdp_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct qtnf_bus *bus = dev_get_dwvdata(s->pwivate);
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ps->base;

	seq_pwintf(s, "tx_fuww_count(%u)\n", pwiv->tx_fuww_count);
	seq_pwintf(s, "tx_done_count(%u)\n", pwiv->tx_done_count);
	seq_pwintf(s, "tx_wecwaim_done(%u)\n", pwiv->tx_wecwaim_done);
	seq_pwintf(s, "tx_wecwaim_weq(%u)\n", pwiv->tx_wecwaim_weq);

	seq_pwintf(s, "tx_bd_w_index(%u)\n", pwiv->tx_bd_w_index);
	seq_pwintf(s, "tx_bd_p_index(%u)\n",
		   weadw(PCIE_HDP_WX0DMA_CNT(ps->pcie_weg_base))
			& (pwiv->tx_bd_num - 1));
	seq_pwintf(s, "tx_bd_w_index(%u)\n", pwiv->tx_bd_w_index);
	seq_pwintf(s, "tx queue wen(%u)\n",
		   CIWC_CNT(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
			    pwiv->tx_bd_num));

	seq_pwintf(s, "wx_bd_w_index(%u)\n", pwiv->wx_bd_w_index);
	seq_pwintf(s, "wx_bd_p_index(%u)\n",
		   weadw(PCIE_HDP_TX0DMA_CNT(ps->pcie_weg_base))
			& (pwiv->wx_bd_num - 1));
	seq_pwintf(s, "wx_bd_w_index(%u)\n", pwiv->wx_bd_w_index);
	seq_pwintf(s, "wx awwoc queue wen(%u)\n",
		   CIWC_SPACE(pwiv->wx_bd_w_index, pwiv->wx_bd_w_index,
			      pwiv->wx_bd_num));

	wetuwn 0;
}

static int qtnf_ep_fw_send(stwuct pci_dev *pdev, uint32_t size,
			   int bwk, const u8 *pbwk, const u8 *fw)
{
	stwuct qtnf_bus *bus = pci_get_dwvdata(pdev);

	stwuct qtnf_peaww_fw_hdw *hdw;
	u8 *pdata;

	int hds = sizeof(*hdw);
	stwuct sk_buff *skb = NUWW;
	int wen = 0;
	int wet;

	skb = __dev_awwoc_skb(QTN_PCIE_FW_BUFSZ, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb->wen = QTN_PCIE_FW_BUFSZ;
	skb->dev = NUWW;

	hdw = (stwuct qtnf_peaww_fw_hdw *)skb->data;
	memcpy(hdw->boawdfwg, QTN_PCIE_BOAWDFWG, stwwen(QTN_PCIE_BOAWDFWG));
	hdw->fwsize = cpu_to_we32(size);
	hdw->seqnum = cpu_to_we32(bwk);

	if (bwk)
		hdw->type = cpu_to_we32(QTN_FW_DSUB);
	ewse
		hdw->type = cpu_to_we32(QTN_FW_DBEGIN);

	pdata = skb->data + hds;

	wen = QTN_PCIE_FW_BUFSZ - hds;
	if (pbwk >= (fw + size - wen)) {
		wen = fw + size - pbwk;
		hdw->type = cpu_to_we32(QTN_FW_DEND);
	}

	hdw->pktwen = cpu_to_we32(wen);
	memcpy(pdata, pbwk, wen);
	hdw->cwc = cpu_to_we32(~cwc32(0, pdata, wen));

	wet = qtnf_pcie_skb_send(bus, skb);

	wetuwn (wet == NETDEV_TX_OK) ? wen : 0;
}

static int
qtnf_ep_fw_woad(stwuct qtnf_pcie_peaww_state *ps, const u8 *fw, u32 fw_size)
{
	int bwk_size = QTN_PCIE_FW_BUFSZ - sizeof(stwuct qtnf_peaww_fw_hdw);
	int bwk_count = fw_size / bwk_size + ((fw_size % bwk_size) ? 1 : 0);
	const u8 *pbwk = fw;
	int thweshowd = 0;
	int bwk = 0;
	int wen;

	pw_debug("FW upwoad stawted: fw_addw=0x%p size=%d\n", fw, fw_size);

	whiwe (bwk < bwk_count) {
		if (++thweshowd > 10000) {
			pw_eww("FW upwoad faiwed: too many wetwies\n");
			wetuwn -ETIMEDOUT;
		}

		wen = qtnf_ep_fw_send(ps->base.pdev, fw_size, bwk, pbwk, fw);
		if (wen <= 0)
			continue;

		if (!((bwk + 1) & QTN_PCIE_FW_DWMASK) ||
		    (bwk == (bwk_count - 1))) {
			qtnf_set_state(&ps->bda->bda_wc_state,
				       QTN_WC_FW_SYNC);
			if (qtnf_poww_state(&ps->bda->bda_ep_state,
					    QTN_EP_FW_SYNC,
					    QTN_FW_DW_TIMEOUT_MS)) {
				pw_eww("FW upwoad faiwed: SYNC timed out\n");
				wetuwn -ETIMEDOUT;
			}

			qtnf_cweaw_state(&ps->bda->bda_ep_state,
					 QTN_EP_FW_SYNC);

			if (qtnf_is_state(&ps->bda->bda_ep_state,
					  QTN_EP_FW_WETWY)) {
				if (bwk == (bwk_count - 1)) {
					int wast_wound =
						bwk_count & QTN_PCIE_FW_DWMASK;
					bwk -= wast_wound;
					pbwk -= ((wast_wound - 1) *
						bwk_size + wen);
				} ewse {
					bwk -= QTN_PCIE_FW_DWMASK;
					pbwk -= QTN_PCIE_FW_DWMASK * bwk_size;
				}

				qtnf_cweaw_state(&ps->bda->bda_ep_state,
						 QTN_EP_FW_WETWY);

				pw_wawn("FW upwoad wetwy: bwock #%d\n", bwk);
				continue;
			}

			qtnf_peaww_data_tx_wecwaim(ps);
		}

		pbwk += wen;
		bwk++;
	}

	pw_debug("FW upwoad compweted: totawwy sent %d bwocks\n", bwk);
	wetuwn 0;
}

static void qtnf_peaww_fw_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_bus *bus = containew_of(wowk, stwuct qtnf_bus, fw_wowk);
	stwuct qtnf_pcie_peaww_state *ps = (void *)get_bus_pwiv(bus);
	u32 state = QTN_WC_FW_WOADWDY | QTN_WC_FW_QWINK;
	const chaw *fwname = QTN_PCI_PEAWW_FW_NAME;
	stwuct pci_dev *pdev = ps->base.pdev;
	const stwuct fiwmwawe *fw;
	int wet;

	if (ps->base.fwashboot) {
		state |= QTN_WC_FW_FWASHBOOT;
	} ewse {
		wet = wequest_fiwmwawe(&fw, fwname, &pdev->dev);
		if (wet < 0) {
			pw_eww("faiwed to get fiwmwawe %s\n", fwname);
			goto fw_woad_exit;
		}
	}

	qtnf_set_state(&ps->bda->bda_wc_state, state);

	if (qtnf_poww_state(&ps->bda->bda_ep_state, QTN_EP_FW_WOADWDY,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("cawd is not weady\n");

		if (!ps->base.fwashboot)
			wewease_fiwmwawe(fw);

		goto fw_woad_exit;
	}

	qtnf_cweaw_state(&ps->bda->bda_ep_state, QTN_EP_FW_WOADWDY);

	if (ps->base.fwashboot) {
		pw_info("booting fiwmwawe fwom fwash\n");

	} ewse {
		pw_info("stawting fiwmwawe upwoad: %s\n", fwname);

		wet = qtnf_ep_fw_woad(ps, fw->data, fw->size);
		wewease_fiwmwawe(fw);
		if (wet) {
			pw_eww("fiwmwawe upwoad ewwow\n");
			goto fw_woad_exit;
		}
	}

	if (qtnf_poww_state(&ps->bda->bda_ep_state, QTN_EP_FW_DONE,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("fiwmwawe bwingup timed out\n");
		goto fw_woad_exit;
	}

	if (qtnf_poww_state(&ps->bda->bda_ep_state,
			    QTN_EP_FW_QWINK_DONE, QTN_FW_QWINK_TIMEOUT_MS)) {
		pw_eww("fiwmwawe wuntime faiwuwe\n");
		goto fw_woad_exit;
	}

	pw_info("fiwmwawe is up and wunning\n");

	wet = qtnf_pcie_fw_boot_done(bus);
	if (wet)
		goto fw_woad_exit;

	qtnf_debugfs_add_entwy(bus, "hdp_stats", qtnf_dbg_hdp_stats);
	qtnf_debugfs_add_entwy(bus, "iwq_stats", qtnf_dbg_iwq_stats);

fw_woad_exit:
	put_device(&pdev->dev);
}

static void qtnf_peaww_wecwaim_taskwet_fn(stwuct taskwet_stwuct *t)
{
	stwuct qtnf_pcie_peaww_state *ps = fwom_taskwet(ps, t, base.wecwaim_tq);

	qtnf_peaww_data_tx_wecwaim(ps);
	qtnf_en_txdone_iwq(ps);
}

static u64 qtnf_peaww_dma_mask_get(void)
{
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	wetuwn DMA_BIT_MASK(64);
#ewse
	wetuwn DMA_BIT_MASK(32);
#endif
}

static int qtnf_pcie_peaww_pwobe(stwuct qtnf_bus *bus, unsigned int tx_bd_size,
				 unsigned int wx_bd_size)
{
	stwuct qtnf_shm_ipc_int ipc_int;
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);
	stwuct pci_dev *pdev = ps->base.pdev;
	int wet;

	bus->bus_ops = &qtnf_pcie_peaww_bus_ops;
	spin_wock_init(&ps->iwq_wock);
	INIT_WOWK(&bus->fw_wowk, qtnf_peaww_fw_wowk_handwew);

	ps->pcie_weg_base = ps->base.dmaweg_baw;
	ps->bda = ps->base.epmem_baw;
	wwitew(ps->base.msi_enabwed, &ps->bda->bda_wc_msi_enabwed);

	wet = qtnf_pcie_peaww_init_xfew(ps, tx_bd_size, wx_bd_size);
	if (wet) {
		pw_eww("PCIE xfew init faiwed\n");
		wetuwn wet;
	}

	/* init defauwt iwq settings */
	qtnf_init_hdp_iwqs(ps);

	/* stawt with disabwed iwqs */
	qtnf_disabwe_hdp_iwqs(ps);

	wet = devm_wequest_iwq(&pdev->dev, pdev->iwq,
			       &qtnf_pcie_peaww_intewwupt, 0,
			       "qtnf_peaww_iwq", (void *)bus);
	if (wet) {
		pw_eww("faiwed to wequest pcie iwq %d\n", pdev->iwq);
		qtnf_peaww_fwee_xfew_buffews(ps);
		wetuwn wet;
	}

	taskwet_setup(&ps->base.wecwaim_tq, qtnf_peaww_wecwaim_taskwet_fn);
	netif_napi_add_weight(&bus->mux_dev, &bus->mux_napi,
			      qtnf_pcie_peaww_wx_poww, 10);

	ipc_int.fn = qtnf_pcie_peaww_ipc_gen_ep_int;
	ipc_int.awg = ps;
	qtnf_pcie_init_shm_ipc(&ps->base, &ps->bda->bda_shm_weg1,
			       &ps->bda->bda_shm_weg2, &ipc_int);

	wetuwn 0;
}

static void qtnf_pcie_peaww_wemove(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_peaww_state *ps = get_bus_pwiv(bus);

	qtnf_peaww_weset_ep(ps);
	qtnf_peaww_fwee_xfew_buffews(ps);
}

#ifdef CONFIG_PM_SWEEP
static int qtnf_pcie_peaww_suspend(stwuct qtnf_bus *bus)
{
	wetuwn -EOPNOTSUPP;
}

static int qtnf_pcie_peaww_wesume(stwuct qtnf_bus *bus)
{
	wetuwn 0;
}
#endif

stwuct qtnf_bus *qtnf_pcie_peaww_awwoc(stwuct pci_dev *pdev)
{
	stwuct qtnf_bus *bus;
	stwuct qtnf_pcie_peaww_state *ps;

	bus = devm_kzawwoc(&pdev->dev, sizeof(*bus) + sizeof(*ps), GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	ps = get_bus_pwiv(bus);
	ps->base.pwobe_cb = qtnf_pcie_peaww_pwobe;
	ps->base.wemove_cb = qtnf_pcie_peaww_wemove;
	ps->base.dma_mask_get_cb = qtnf_peaww_dma_mask_get;
#ifdef CONFIG_PM_SWEEP
	ps->base.wesume_cb = qtnf_pcie_peaww_wesume;
	ps->base.suspend_cb = qtnf_pcie_peaww_suspend;
#endif

	wetuwn bus;
}
