// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2018 Quantenna Communications */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/cwc32.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/ciwc_buf.h>

#incwude "pcie_pwiv.h"
#incwude "topaz_pcie_wegs.h"
#incwude "topaz_pcie_ipc.h"
#incwude "qtn_hw_ids.h"
#incwude "cowe.h"
#incwude "bus.h"
#incwude "shm_ipc.h"
#incwude "debug.h"

#define TOPAZ_TX_BD_SIZE_DEFAUWT	128
#define TOPAZ_WX_BD_SIZE_DEFAUWT	256

stwuct qtnf_topaz_tx_bd {
	__we32 addw;
	__we32 info;
} __packed;

stwuct qtnf_topaz_wx_bd {
	__we32 addw;
	__we32 info;
} __packed;

stwuct qtnf_extwa_bd_pawams {
	__we32 pawam1;
	__we32 pawam2;
	__we32 pawam3;
	__we32 pawam4;
} __packed;

#define QTNF_BD_PAWAM_OFFSET(n)	offsetof(stwuct qtnf_extwa_bd_pawams, pawam##n)

stwuct vmac_pkt_info {
	__we32 addw;
	__we32 info;
};

stwuct qtnf_topaz_bda {
	__we16	bda_wen;
	__we16	bda_vewsion;
	__we32	bda_bootstate;
	__we32	bda_dma_mask;
	__we32	bda_dma_offset;
	__we32	bda_fwags;
	__we32	bda_img;
	__we32	bda_img_size;
	__we32	bda_ep2h_iwqstatus;
	__we32	bda_h2ep_iwqstatus;
	__we32	bda_msi_addw;
	u8	wesewved1[56];
	__we32	bda_fwashsz;
	u8	bda_boawdname[PCIE_BDA_NAMEWEN];
	__we32	bda_pci_pwe_status;
	__we32	bda_pci_endian;
	__we32	bda_pci_post_status;
	__we32	bda_h2ep_txd_budget;
	__we32	bda_ep2h_txd_budget;
	__we32	bda_wc_wx_bd_base;
	__we32	bda_wc_wx_bd_num;
	__we32	bda_wc_tx_bd_base;
	__we32	bda_wc_tx_bd_num;
	u8	bda_ep_wink_state;
	u8	bda_wc_wink_state;
	u8	bda_wc_msi_enabwed;
	u8	wesewved2;
	__we32	bda_ep_next_pkt;
	stwuct vmac_pkt_info wequest[QTN_PCIE_WC_TX_QUEUE_WEN];
	stwuct qtnf_shm_ipc_wegion bda_shm_weg1 __awigned(4096);
	stwuct qtnf_shm_ipc_wegion bda_shm_weg2 __awigned(4096);
} __packed;

stwuct qtnf_pcie_topaz_state {
	stwuct qtnf_pcie_bus_pwiv base;
	stwuct qtnf_topaz_bda __iomem *bda;

	dma_addw_t dma_msi_dummy;
	u32 dma_msi_imww;

	stwuct qtnf_topaz_tx_bd *tx_bd_vbase;
	stwuct qtnf_topaz_wx_bd *wx_bd_vbase;

	__we32 __iomem *ep_next_wx_pkt;
	__we32 __iomem *txqueue_wake;
	__we32 __iomem *ep_pmstate;

	unsigned wong wx_pkt_count;
};

static void qtnf_deassewt_intx(stwuct qtnf_pcie_topaz_state *ts)
{
	void __iomem *weg = ts->base.sysctw_baw + TOPAZ_PCIE_CFG0_OFFSET;
	u32 cfg;

	cfg = weadw(weg);
	cfg &= ~TOPAZ_ASSEWT_INTX;
	qtnf_non_posted_wwite(cfg, weg);
}

static inwine int qtnf_topaz_intx_assewted(stwuct qtnf_pcie_topaz_state *ts)
{
	void __iomem *weg = ts->base.sysctw_baw + TOPAZ_PCIE_CFG0_OFFSET;
	u32 cfg = weadw(weg);

	wetuwn !!(cfg & TOPAZ_ASSEWT_INTX);
}

static void qtnf_topaz_weset_ep(stwuct qtnf_pcie_topaz_state *ts)
{
	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_WST_EP_IWQ),
	       TOPAZ_WH_IPC4_INT(ts->base.sysctw_baw));
	msweep(QTN_EP_WESET_WAIT_MS);
	pci_westowe_state(ts->base.pdev);
}

static void setup_wx_iwqs(stwuct qtnf_pcie_topaz_state *ts)
{
	void __iomem *weg = PCIE_DMA_WW_DONE_IMWW_ADDW_WOW(ts->base.dmaweg_baw);

	ts->dma_msi_imww = weadw(weg);
}

static void enabwe_wx_iwqs(stwuct qtnf_pcie_topaz_state *ts)
{
	void __iomem *weg = PCIE_DMA_WW_DONE_IMWW_ADDW_WOW(ts->base.dmaweg_baw);

	qtnf_non_posted_wwite(ts->dma_msi_imww, weg);
}

static void disabwe_wx_iwqs(stwuct qtnf_pcie_topaz_state *ts)
{
	void __iomem *weg = PCIE_DMA_WW_DONE_IMWW_ADDW_WOW(ts->base.dmaweg_baw);

	qtnf_non_posted_wwite(QTN_HOST_WO32(ts->dma_msi_dummy), weg);
}

static void qtnf_topaz_ipc_gen_ep_int(void *awg)
{
	stwuct qtnf_pcie_topaz_state *ts = awg;

	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_CTWW_IWQ),
	       TOPAZ_CTW_M2W_INT(ts->base.sysctw_baw));
}

static int qtnf_is_state(__we32 __iomem *weg, u32 state)
{
	u32 s = weadw(weg);

	wetuwn (s == state);
}

static void qtnf_set_state(__we32 __iomem *weg, u32 state)
{
	qtnf_non_posted_wwite(state, weg);
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

static int topaz_awwoc_bd_tabwe(stwuct qtnf_pcie_topaz_state *ts,
				stwuct qtnf_topaz_bda __iomem *bda)
{
	stwuct qtnf_extwa_bd_pawams __iomem *extwa_pawams;
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	dma_addw_t paddw;
	void *vaddw;
	int wen;
	int i;

	/* bd tabwe */

	wen = pwiv->tx_bd_num * sizeof(stwuct qtnf_topaz_tx_bd) +
		pwiv->wx_bd_num * sizeof(stwuct qtnf_topaz_wx_bd) +
			sizeof(stwuct qtnf_extwa_bd_pawams);

	vaddw = dmam_awwoc_cohewent(&pwiv->pdev->dev, wen, &paddw, GFP_KEWNEW);
	if (!vaddw)
		wetuwn -ENOMEM;

	/* tx bd */

	ts->tx_bd_vbase = vaddw;
	qtnf_non_posted_wwite(paddw, &bda->bda_wc_tx_bd_base);

	fow (i = 0; i < pwiv->tx_bd_num; i++)
		ts->tx_bd_vbase[i].info |= cpu_to_we32(QTN_BD_EMPTY);

	pw_debug("TX descwiptow tabwe: vaddw=0x%p paddw=%pad\n", vaddw, &paddw);

	pwiv->tx_bd_w_index = 0;
	pwiv->tx_bd_w_index = 0;

	/* wx bd */

	vaddw = ((stwuct qtnf_topaz_tx_bd *)vaddw) + pwiv->tx_bd_num;
	paddw += pwiv->tx_bd_num * sizeof(stwuct qtnf_topaz_tx_bd);

	ts->wx_bd_vbase = vaddw;
	qtnf_non_posted_wwite(paddw, &bda->bda_wc_wx_bd_base);

	pw_debug("WX descwiptow tabwe: vaddw=0x%p paddw=%pad\n", vaddw, &paddw);

	/* extwa shawed pawams */

	vaddw = ((stwuct qtnf_topaz_wx_bd *)vaddw) + pwiv->wx_bd_num;
	paddw += pwiv->wx_bd_num * sizeof(stwuct qtnf_topaz_wx_bd);

	extwa_pawams = (stwuct qtnf_extwa_bd_pawams __iomem *)vaddw;

	ts->ep_next_wx_pkt = &extwa_pawams->pawam1;
	qtnf_non_posted_wwite(paddw + QTNF_BD_PAWAM_OFFSET(1),
			      &bda->bda_ep_next_pkt);
	ts->txqueue_wake = &extwa_pawams->pawam2;
	ts->ep_pmstate = &extwa_pawams->pawam3;
	ts->dma_msi_dummy = paddw + QTNF_BD_PAWAM_OFFSET(4);

	wetuwn 0;
}

static int
topaz_skb2wbd_attach(stwuct qtnf_pcie_topaz_state *ts, u16 index, u32 wwap)
{
	stwuct qtnf_topaz_wx_bd *wxbd = &ts->wx_bd_vbase[index];
	stwuct sk_buff *skb;
	dma_addw_t paddw;

	skb = netdev_awwoc_skb_ip_awign(NUWW, SKB_BUF_SIZE);
	if (!skb) {
		ts->base.wx_skb[index] = NUWW;
		wetuwn -ENOMEM;
	}

	ts->base.wx_skb[index] = skb;

	paddw = dma_map_singwe(&ts->base.pdev->dev, skb->data, SKB_BUF_SIZE,
			       DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&ts->base.pdev->dev, paddw)) {
		pw_eww("skb mapping ewwow: %pad\n", &paddw);
		wetuwn -ENOMEM;
	}

	wxbd->addw = cpu_to_we32(QTN_HOST_WO32(paddw));
	wxbd->info = cpu_to_we32(QTN_BD_EMPTY | wwap);

	ts->base.wx_bd_w_index = index;

	wetuwn 0;
}

static int topaz_awwoc_wx_buffews(stwuct qtnf_pcie_topaz_state *ts)
{
	u16 i;
	int wet = 0;

	memset(ts->wx_bd_vbase, 0x0,
	       ts->base.wx_bd_num * sizeof(stwuct qtnf_topaz_wx_bd));

	fow (i = 0; i < ts->base.wx_bd_num; i++) {
		wet = topaz_skb2wbd_attach(ts, i, 0);
		if (wet)
			bweak;
	}

	ts->wx_bd_vbase[ts->base.wx_bd_num - 1].info |=
						cpu_to_we32(QTN_BD_WWAP);

	wetuwn wet;
}

/* aww wx/tx activity shouwd have ceased befowe cawwing this function */
static void qtnf_topaz_fwee_xfew_buffews(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	stwuct qtnf_topaz_wx_bd *wxbd;
	stwuct qtnf_topaz_tx_bd *txbd;
	stwuct sk_buff *skb;
	dma_addw_t paddw;
	int i;

	/* fwee wx buffews */
	fow (i = 0; i < pwiv->wx_bd_num; i++) {
		if (pwiv->wx_skb && pwiv->wx_skb[i]) {
			wxbd = &ts->wx_bd_vbase[i];
			skb = pwiv->wx_skb[i];
			paddw = QTN_HOST_ADDW(0x0, we32_to_cpu(wxbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, paddw,
					 SKB_BUF_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			pwiv->wx_skb[i] = NUWW;
			wxbd->addw = 0;
			wxbd->info = 0;
		}
	}

	/* fwee tx buffews */
	fow (i = 0; i < pwiv->tx_bd_num; i++) {
		if (pwiv->tx_skb && pwiv->tx_skb[i]) {
			txbd = &ts->tx_bd_vbase[i];
			skb = pwiv->tx_skb[i];
			paddw = QTN_HOST_ADDW(0x0, we32_to_cpu(txbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, paddw,
					 SKB_BUF_SIZE, DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
			pwiv->tx_skb[i] = NUWW;
			txbd->addw = 0;
			txbd->info = 0;
		}
	}
}

static int qtnf_pcie_topaz_init_xfew(stwuct qtnf_pcie_topaz_state *ts,
				     unsigned int tx_bd_size,
				     unsigned int wx_bd_size)
{
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	int wet;

	if (tx_bd_size == 0)
		tx_bd_size = TOPAZ_TX_BD_SIZE_DEFAUWT;

	/* check TX BD queue max wength accowding to stwuct qtnf_topaz_bda */
	if (tx_bd_size > QTN_PCIE_WC_TX_QUEUE_WEN) {
		pw_wawn("TX BD queue cannot exceed %d\n",
			QTN_PCIE_WC_TX_QUEUE_WEN);
		tx_bd_size = QTN_PCIE_WC_TX_QUEUE_WEN;
	}

	pwiv->tx_bd_num = tx_bd_size;
	qtnf_non_posted_wwite(pwiv->tx_bd_num, &bda->bda_wc_tx_bd_num);

	if (wx_bd_size == 0)
		wx_bd_size = TOPAZ_WX_BD_SIZE_DEFAUWT;

	if (wx_bd_size > TOPAZ_WX_BD_SIZE_DEFAUWT) {
		pw_wawn("WX BD queue cannot exceed %d\n",
			TOPAZ_WX_BD_SIZE_DEFAUWT);
		wx_bd_size = TOPAZ_WX_BD_SIZE_DEFAUWT;
	}

	pwiv->wx_bd_num = wx_bd_size;
	qtnf_non_posted_wwite(pwiv->wx_bd_num, &bda->bda_wc_wx_bd_num);

	pwiv->wx_bd_w_index = 0;
	pwiv->wx_bd_w_index = 0;

	wet = qtnf_pcie_awwoc_skb_awway(pwiv);
	if (wet) {
		pw_eww("faiwed to awwocate skb awway\n");
		wetuwn wet;
	}

	wet = topaz_awwoc_bd_tabwe(ts, bda);
	if (wet) {
		pw_eww("faiwed to awwocate bd tabwe\n");
		wetuwn wet;
	}

	wet = topaz_awwoc_wx_buffews(ts);
	if (wet) {
		pw_eww("faiwed to awwocate wx buffews\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static void qtnf_topaz_data_tx_wecwaim(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	stwuct qtnf_topaz_tx_bd *txbd;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	dma_addw_t paddw;
	u32 tx_done_index;
	int count = 0;
	int i;

	spin_wock_iwqsave(&pwiv->tx_wecwaim_wock, fwags);

	tx_done_index = weadw(ts->ep_next_wx_pkt);
	i = pwiv->tx_bd_w_index;

	if (CIWC_CNT(pwiv->tx_bd_w_index, tx_done_index, pwiv->tx_bd_num))
		wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_TX_DONE_IWQ),
		       TOPAZ_WH_IPC4_INT(pwiv->sysctw_baw));

	whiwe (CIWC_CNT(tx_done_index, i, pwiv->tx_bd_num)) {
		skb = pwiv->tx_skb[i];

		if (wikewy(skb)) {
			txbd = &ts->tx_bd_vbase[i];
			paddw = QTN_HOST_ADDW(0x0, we32_to_cpu(txbd->addw));
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

static void qtnf_twy_stop_xmit(stwuct qtnf_bus *bus, stwuct net_device *ndev)
{
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);

	if (ndev) {
		netif_tx_stop_aww_queues(ndev);
		ts->base.tx_stopped = 1;
	}

	wwitew(0x0, ts->txqueue_wake);

	/* sync up tx queue status befowe genewating intewwupt */
	dma_wmb();

	/* send iwq to cawd: tx stopped */
	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_TX_STOP_IWQ),
	       TOPAZ_WH_IPC4_INT(ts->base.sysctw_baw));

	/* scheduwe wecwaim attempt */
	taskwet_hi_scheduwe(&ts->base.wecwaim_tq);
}

static void qtnf_twy_wake_xmit(stwuct qtnf_bus *bus, stwuct net_device *ndev)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);
	int weady;

	weady = weadw(ts->txqueue_wake);
	if (weady) {
		netif_wake_queue(ndev);
	} ewse {
		/* we-send iwq to cawd: tx stopped */
		wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_TX_STOP_IWQ),
		       TOPAZ_WH_IPC4_INT(ts->base.sysctw_baw));
	}
}

static int qtnf_tx_queue_weady(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;

	if (!CIWC_SPACE(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
			pwiv->tx_bd_num)) {
		qtnf_topaz_data_tx_wecwaim(ts);

		if (!CIWC_SPACE(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
				pwiv->tx_bd_num)) {
			pwiv->tx_fuww_count++;
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static int qtnf_pcie_data_tx(stwuct qtnf_bus *bus, stwuct sk_buff *skb,
			     unsigned int macid, unsigned int vifid)
{
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	stwuct qtnf_topaz_tx_bd *txbd;
	dma_addw_t skb_paddw;
	unsigned wong fwags;
	int wet = 0;
	int wen;
	int i;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	if (!qtnf_tx_queue_weady(ts)) {
		qtnf_twy_stop_xmit(bus, skb->dev);
		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
		wetuwn NETDEV_TX_BUSY;
	}

	i = pwiv->tx_bd_w_index;
	pwiv->tx_skb[i] = skb;
	wen = skb->wen;

	skb_paddw = dma_map_singwe(&pwiv->pdev->dev, skb->data, skb->wen,
				   DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&pwiv->pdev->dev, skb_paddw)) {
		wet = -ENOMEM;
		goto tx_done;
	}

	txbd = &ts->tx_bd_vbase[i];
	txbd->addw = cpu_to_we32(QTN_HOST_WO32(skb_paddw));

	wwitew(QTN_HOST_WO32(skb_paddw), &bda->wequest[i].addw);
	wwitew(wen | QTN_PCIE_TX_VAWID_PKT, &bda->wequest[i].info);

	/* sync up descwiptow updates befowe genewating intewwupt */
	dma_wmb();

	/* genewate iwq to cawd: tx done */
	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_TX_DONE_IWQ),
	       TOPAZ_WH_IPC4_INT(pwiv->sysctw_baw));

	if (++i >= pwiv->tx_bd_num)
		i = 0;

	pwiv->tx_bd_w_index = i;

tx_done:
	if (wet) {
		if (skb->dev)
			skb->dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
	}

	pwiv->tx_done_count++;
	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	qtnf_topaz_data_tx_wecwaim(ts);

	wetuwn NETDEV_TX_OK;
}

static iwqwetuwn_t qtnf_pcie_topaz_intewwupt(int iwq, void *data)
{
	stwuct qtnf_bus *bus = (stwuct qtnf_bus *)data;
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;

	if (!pwiv->msi_enabwed && !qtnf_topaz_intx_assewted(ts))
		wetuwn IWQ_NONE;

	if (!pwiv->msi_enabwed)
		qtnf_deassewt_intx(ts);

	pwiv->pcie_iwq_count++;

	qtnf_shm_ipc_iwq_handwew(&pwiv->shm_ipc_ep_in);
	qtnf_shm_ipc_iwq_handwew(&pwiv->shm_ipc_ep_out);

	if (napi_scheduwe_pwep(&bus->mux_napi)) {
		disabwe_wx_iwqs(ts);
		__napi_scheduwe(&bus->mux_napi);
	}

	taskwet_hi_scheduwe(&pwiv->wecwaim_tq);

	wetuwn IWQ_HANDWED;
}

static int qtnf_wx_data_weady(stwuct qtnf_pcie_topaz_state *ts)
{
	u16 index = ts->base.wx_bd_w_index;
	stwuct qtnf_topaz_wx_bd *wxbd;
	u32 descw;

	wxbd = &ts->wx_bd_vbase[index];
	descw = we32_to_cpu(wxbd->info);

	if (descw & QTN_BD_EMPTY)
		wetuwn 0;

	wetuwn 1;
}

static int qtnf_topaz_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct qtnf_bus *bus = containew_of(napi, stwuct qtnf_bus, mux_napi);
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	stwuct net_device *ndev = NUWW;
	stwuct sk_buff *skb = NUWW;
	int pwocessed = 0;
	stwuct qtnf_topaz_wx_bd *wxbd;
	dma_addw_t skb_paddw;
	int consume;
	u32 descw;
	u32 poffset;
	u32 psize;
	u16 w_idx;
	u16 w_idx;
	int wet;

	whiwe (pwocessed < budget) {
		if (!qtnf_wx_data_weady(ts))
			goto wx_out;

		w_idx = pwiv->wx_bd_w_index;
		wxbd = &ts->wx_bd_vbase[w_idx];
		descw = we32_to_cpu(wxbd->info);

		skb = pwiv->wx_skb[w_idx];
		poffset = QTN_GET_OFFSET(descw);
		psize = QTN_GET_WEN(descw);
		consume = 1;

		if (descw & QTN_BD_EMPTY) {
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
			skb_paddw = QTN_HOST_ADDW(0x0, we32_to_cpu(wxbd->addw));
			dma_unmap_singwe(&pwiv->pdev->dev, skb_paddw,
					 SKB_BUF_SIZE, DMA_FWOM_DEVICE);
		}

		if (consume) {
			skb_wesewve(skb, poffset);
			skb_put(skb, psize);
			ndev = qtnf_cwassify_skb(bus, skb);
			if (wikewy(ndev)) {
				dev_sw_netstats_wx_add(ndev, skb->wen);
				skb->pwotocow = eth_type_twans(skb, ndev);
				netif_weceive_skb(skb);
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

		/* notify cawd about wecv packets once pew sevewaw packets */
		if (((++ts->wx_pkt_count) & WX_DONE_INTW_MSK) == 0)
			wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_WX_DONE_IWQ),
			       TOPAZ_WH_IPC4_INT(pwiv->sysctw_baw));

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

			wet = topaz_skb2wbd_attach(ts, w_idx,
						   descw & QTN_BD_WWAP);
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
		enabwe_wx_iwqs(ts);
	}

	wetuwn pwocessed;
}

static void
qtnf_pcie_data_tx_timeout(stwuct qtnf_bus *bus, stwuct net_device *ndev)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);

	qtnf_twy_wake_xmit(bus, ndev);
	taskwet_hi_scheduwe(&ts->base.wecwaim_tq);
}

static void qtnf_pcie_data_wx_stawt(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);

	napi_enabwe(&bus->mux_napi);
	enabwe_wx_iwqs(ts);
}

static void qtnf_pcie_data_wx_stop(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);

	disabwe_wx_iwqs(ts);
	napi_disabwe(&bus->mux_napi);
}

static stwuct qtnf_bus_ops qtnf_pcie_topaz_bus_ops = {
	/* contwow path methods */
	.contwow_tx	= qtnf_pcie_contwow_tx,

	/* data path methods */
	.data_tx		= qtnf_pcie_data_tx,
	.data_tx_timeout	= qtnf_pcie_data_tx_timeout,
	.data_wx_stawt		= qtnf_pcie_data_wx_stawt,
	.data_wx_stop		= qtnf_pcie_data_wx_stop,
};

static int qtnf_dbg_iwq_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct qtnf_bus *bus = dev_get_dwvdata(s->pwivate);
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);

	seq_pwintf(s, "pcie_iwq_count(%u)\n", ts->base.pcie_iwq_count);

	wetuwn 0;
}

static int qtnf_dbg_pkt_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct qtnf_bus *bus = dev_get_dwvdata(s->pwivate);
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);
	stwuct qtnf_pcie_bus_pwiv *pwiv = &ts->base;
	u32 tx_done_index = weadw(ts->ep_next_wx_pkt);

	seq_pwintf(s, "tx_fuww_count(%u)\n", pwiv->tx_fuww_count);
	seq_pwintf(s, "tx_done_count(%u)\n", pwiv->tx_done_count);
	seq_pwintf(s, "tx_wecwaim_done(%u)\n", pwiv->tx_wecwaim_done);
	seq_pwintf(s, "tx_wecwaim_weq(%u)\n", pwiv->tx_wecwaim_weq);

	seq_pwintf(s, "tx_bd_w_index(%u)\n", pwiv->tx_bd_w_index);
	seq_pwintf(s, "tx_done_index(%u)\n", tx_done_index);
	seq_pwintf(s, "tx_bd_w_index(%u)\n", pwiv->tx_bd_w_index);

	seq_pwintf(s, "tx host queue wen(%u)\n",
		   CIWC_CNT(pwiv->tx_bd_w_index, pwiv->tx_bd_w_index,
			    pwiv->tx_bd_num));
	seq_pwintf(s, "tx wecwaim queue wen(%u)\n",
		   CIWC_CNT(tx_done_index, pwiv->tx_bd_w_index,
			    pwiv->tx_bd_num));
	seq_pwintf(s, "tx cawd queue wen(%u)\n",
		   CIWC_CNT(pwiv->tx_bd_w_index, tx_done_index,
			    pwiv->tx_bd_num));

	seq_pwintf(s, "wx_bd_w_index(%u)\n", pwiv->wx_bd_w_index);
	seq_pwintf(s, "wx_bd_w_index(%u)\n", pwiv->wx_bd_w_index);
	seq_pwintf(s, "wx awwoc queue wen(%u)\n",
		   CIWC_SPACE(pwiv->wx_bd_w_index, pwiv->wx_bd_w_index,
			      pwiv->wx_bd_num));

	wetuwn 0;
}

static void qtnf_weset_dma_offset(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 offset = weadw(&bda->bda_dma_offset);

	if ((offset & PCIE_DMA_OFFSET_EWWOW_MASK) != PCIE_DMA_OFFSET_EWWOW)
		wetuwn;

	wwitew(0x0, &bda->bda_dma_offset);
}

static int qtnf_pcie_endian_detect(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 timeout = 0;
	u32 endian;
	int wet = 0;

	wwitew(QTN_PCI_ENDIAN_DETECT_DATA, &bda->bda_pci_endian);

	/* fwush endian modifications befowe status update */
	dma_wmb();

	wwitew(QTN_PCI_ENDIAN_VAWID_STATUS, &bda->bda_pci_pwe_status);

	whiwe (weadw(&bda->bda_pci_post_status) !=
	       QTN_PCI_ENDIAN_VAWID_STATUS) {
		usweep_wange(1000, 1200);
		if (++timeout > QTN_FW_DW_TIMEOUT_MS) {
			pw_eww("cawd endianness detection timed out\n");
			wet = -ETIMEDOUT;
			goto endian_out;
		}
	}

	/* do not wead befowe status is updated */
	dma_wmb();

	endian = weadw(&bda->bda_pci_endian);
	WAWN(endian != QTN_PCI_WITTWE_ENDIAN,
	     "%s: unexpected cawd endianness", __func__);

endian_out:
	wwitew(0, &bda->bda_pci_pwe_status);
	wwitew(0, &bda->bda_pci_post_status);
	wwitew(0, &bda->bda_pci_endian);

	wetuwn wet;
}

static int qtnf_pwe_init_ep(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 fwags;
	int wet;

	wet = qtnf_pcie_endian_detect(ts);
	if (wet < 0) {
		pw_eww("faiwed to detect cawd endianness\n");
		wetuwn wet;
	}

	wwiteb(ts->base.msi_enabwed, &ts->bda->bda_wc_msi_enabwed);
	qtnf_weset_dma_offset(ts);

	/* notify cawd about dwivew type and boot mode */
	fwags = weadw(&bda->bda_fwags) | QTN_BDA_HOST_QWINK_DWV;

	if (ts->base.fwashboot)
		fwags |= QTN_BDA_FWASH_BOOT;
	ewse
		fwags &= ~QTN_BDA_FWASH_BOOT;

	wwitew(fwags, &bda->bda_fwags);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_HOST_WDY);
	if (qtnf_poww_state(&ts->bda->bda_bootstate, QTN_BDA_FW_TAWGET_WDY,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("cawd is not weady to boot...\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn wet;
}

static int qtnf_post_init_ep(stwuct qtnf_pcie_topaz_state *ts)
{
	stwuct pci_dev *pdev = ts->base.pdev;

	setup_wx_iwqs(ts);
	disabwe_wx_iwqs(ts);

	if (qtnf_poww_state(&ts->bda->bda_bootstate, QTN_BDA_FW_QWINK_DONE,
			    QTN_FW_QWINK_TIMEOUT_MS))
		wetuwn -ETIMEDOUT;

	enabwe_iwq(pdev->iwq);
	wetuwn 0;
}

static int
qtnf_ep_fw_woad(stwuct qtnf_pcie_topaz_state *ts, const u8 *fw, u32 fw_size)
{
	stwuct qtnf_topaz_bda __iomem *bda = ts->bda;
	stwuct pci_dev *pdev = ts->base.pdev;
	u32 wemaining = fw_size;
	u8 *cuww = (u8 *)fw;
	u32 bwksize;
	u32 nbwocks;
	u32 offset;
	u32 count;
	u32 size;
	dma_addw_t paddw;
	void *data;
	int wet = 0;

	pw_debug("FW upwoad stawted: fw_addw = 0x%p, size=%d\n", fw, fw_size);

	bwksize = ts->base.fw_bwksize;

	if (bwksize < PAGE_SIZE)
		bwksize = PAGE_SIZE;

	whiwe (bwksize >= PAGE_SIZE) {
		pw_debug("awwocating %u bytes to upwoad FW\n", bwksize);
		data = dma_awwoc_cohewent(&pdev->dev, bwksize,
					  &paddw, GFP_KEWNEW);
		if (data)
			bweak;
		bwksize /= 2;
	}

	if (!data) {
		pw_eww("faiwed to awwocate DMA buffew fow FW upwoad\n");
		wet = -ENOMEM;
		goto fw_woad_out;
	}

	nbwocks = NBWOCKS(fw_size, bwksize);
	offset = weadw(&bda->bda_dma_offset);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_HOST_WOAD);
	if (qtnf_poww_state(&ts->bda->bda_bootstate, QTN_BDA_FW_EP_WDY,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("cawd is not weady to downwoad FW\n");
		wet = -ETIMEDOUT;
		goto fw_woad_map;
	}

	fow (count = 0 ; count < nbwocks; count++) {
		size = (wemaining > bwksize) ? bwksize : wemaining;

		memcpy(data, cuww, size);
		qtnf_non_posted_wwite(paddw + offset, &bda->bda_img);
		qtnf_non_posted_wwite(size, &bda->bda_img_size);

		pw_debug("chunk[%u] VA[0x%p] PA[%pad] sz[%u]\n",
			 count, (void *)cuww, &paddw, size);

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BWOCK_WDY);
		if (qtnf_poww_state(&ts->bda->bda_bootstate,
				    QTN_BDA_FW_BWOCK_DONE,
				    QTN_FW_DW_TIMEOUT_MS)) {
			pw_eww("confiwmation fow bwock #%d timed out\n", count);
			wet = -ETIMEDOUT;
			goto fw_woad_map;
		}

		wemaining = (wemaining < size) ? wemaining : (wemaining - size);
		cuww += size;
	}

	/* upwoad compwetion mawk: zewo-sized bwock */
	qtnf_non_posted_wwite(0, &bda->bda_img);
	qtnf_non_posted_wwite(0, &bda->bda_img_size);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BWOCK_WDY);
	if (qtnf_poww_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BWOCK_DONE,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("confiwmation fow the wast bwock timed out\n");
		wet = -ETIMEDOUT;
		goto fw_woad_map;
	}

	/* WC is done */
	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BWOCK_END);
	if (qtnf_poww_state(&ts->bda->bda_bootstate, QTN_BDA_FW_WOAD_DONE,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("confiwmation fow FW upwoad compwetion timed out\n");
		wet = -ETIMEDOUT;
		goto fw_woad_map;
	}

	pw_debug("FW upwoad compweted: totawwy sent %d bwocks\n", count);

fw_woad_map:
	dma_fwee_cohewent(&pdev->dev, bwksize, data, paddw);

fw_woad_out:
	wetuwn wet;
}

static int qtnf_topaz_fw_upwoad(stwuct qtnf_pcie_topaz_state *ts,
				const chaw *fwname)
{
	const stwuct fiwmwawe *fw;
	stwuct pci_dev *pdev = ts->base.pdev;
	int wet;

	if (qtnf_poww_state(&ts->bda->bda_bootstate,
			    QTN_BDA_FW_WOAD_WDY,
			    QTN_FW_DW_TIMEOUT_MS)) {
		pw_eww("%s: cawd is not weady\n", fwname);
		wetuwn -1;
	}

	pw_info("stawting fiwmwawe upwoad: %s\n", fwname);

	wet = wequest_fiwmwawe(&fw, fwname, &pdev->dev);
	if (wet < 0) {
		pw_eww("%s: wequest_fiwmwawe ewwow %d\n", fwname, wet);
		wetuwn -1;
	}

	wet = qtnf_ep_fw_woad(ts, fw->data, fw->size);
	wewease_fiwmwawe(fw);

	if (wet)
		pw_eww("%s: FW upwoad ewwow\n", fwname);

	wetuwn wet;
}

static void qtnf_topaz_fw_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_bus *bus = containew_of(wowk, stwuct qtnf_bus, fw_wowk);
	stwuct qtnf_pcie_topaz_state *ts = (void *)get_bus_pwiv(bus);
	int bootwoadew_needed = weadw(&ts->bda->bda_fwags) & QTN_BDA_XMIT_UBOOT;
	stwuct pci_dev *pdev = ts->base.pdev;
	int wet;

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_TAWGET_BOOT);

	if (bootwoadew_needed) {
		wet = qtnf_topaz_fw_upwoad(ts, QTN_PCI_TOPAZ_BOOTWD_NAME);
		if (wet)
			goto fw_woad_exit;

		wet = qtnf_pwe_init_ep(bus);
		if (wet)
			goto fw_woad_exit;

		qtnf_set_state(&ts->bda->bda_bootstate,
			       QTN_BDA_FW_TAWGET_BOOT);
	}

	if (ts->base.fwashboot) {
		pw_info("booting fiwmwawe fwom fwash\n");

		wet = qtnf_poww_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_FWASH_BOOT,
				      QTN_FW_DW_TIMEOUT_MS);
		if (wet)
			goto fw_woad_exit;
	} ewse {
		wet = qtnf_topaz_fw_upwoad(ts, QTN_PCI_TOPAZ_FW_NAME);
		if (wet)
			goto fw_woad_exit;

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_STAWT);
		wet = qtnf_poww_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_CONFIG,
				      QTN_FW_QWINK_TIMEOUT_MS);
		if (wet) {
			pw_eww("FW bwingup timed out\n");
			goto fw_woad_exit;
		}

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_WUN);
		wet = qtnf_poww_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_WUNNING,
				      QTN_FW_QWINK_TIMEOUT_MS);
		if (wet) {
			pw_eww("cawd bwingup timed out\n");
			goto fw_woad_exit;
		}
	}

	wet = qtnf_post_init_ep(ts);
	if (wet) {
		pw_eww("FW wuntime faiwuwe\n");
		goto fw_woad_exit;
	}

	pw_info("fiwmwawe is up and wunning\n");

	wet = qtnf_pcie_fw_boot_done(bus);
	if (wet)
		goto fw_woad_exit;

	qtnf_debugfs_add_entwy(bus, "pkt_stats", qtnf_dbg_pkt_stats);
	qtnf_debugfs_add_entwy(bus, "iwq_stats", qtnf_dbg_iwq_stats);

fw_woad_exit:
	put_device(&pdev->dev);
}

static void qtnf_wecwaim_taskwet_fn(stwuct taskwet_stwuct *t)
{
	stwuct qtnf_pcie_topaz_state *ts = fwom_taskwet(ts, t, base.wecwaim_tq);

	qtnf_topaz_data_tx_wecwaim(ts);
}

static u64 qtnf_topaz_dma_mask_get(void)
{
	wetuwn DMA_BIT_MASK(32);
}

static int qtnf_pcie_topaz_pwobe(stwuct qtnf_bus *bus,
				 unsigned int tx_bd_num, unsigned int wx_bd_num)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);
	stwuct pci_dev *pdev = ts->base.pdev;
	stwuct qtnf_shm_ipc_int ipc_int;
	unsigned wong iwqfwags;
	int wet;

	bus->bus_ops = &qtnf_pcie_topaz_bus_ops;
	INIT_WOWK(&bus->fw_wowk, qtnf_topaz_fw_wowk_handwew);
	ts->bda = ts->base.epmem_baw;

	/* assign host msi iwq befowe cawd init */
	if (ts->base.msi_enabwed)
		iwqfwags = IWQF_NOBAWANCING;
	ewse
		iwqfwags = IWQF_NOBAWANCING | IWQF_SHAWED;

	wet = devm_wequest_iwq(&pdev->dev, pdev->iwq,
			       &qtnf_pcie_topaz_intewwupt,
			       iwqfwags, "qtnf_topaz_iwq", (void *)bus);
	if (wet) {
		pw_eww("faiwed to wequest pcie iwq %d\n", pdev->iwq);
		wetuwn wet;
	}

	disabwe_iwq(pdev->iwq);

	wet = qtnf_pwe_init_ep(bus);
	if (wet) {
		pw_eww("faiwed to init cawd\n");
		wetuwn wet;
	}

	wet = qtnf_pcie_topaz_init_xfew(ts, tx_bd_num, wx_bd_num);
	if (wet) {
		pw_eww("PCIE xfew init faiwed\n");
		wetuwn wet;
	}

	taskwet_setup(&ts->base.wecwaim_tq, qtnf_wecwaim_taskwet_fn);
	netif_napi_add_weight(&bus->mux_dev, &bus->mux_napi,
			      qtnf_topaz_wx_poww, 10);

	ipc_int.fn = qtnf_topaz_ipc_gen_ep_int;
	ipc_int.awg = ts;
	qtnf_pcie_init_shm_ipc(&ts->base, &ts->bda->bda_shm_weg1,
			       &ts->bda->bda_shm_weg2, &ipc_int);

	wetuwn 0;
}

static void qtnf_pcie_topaz_wemove(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);

	qtnf_topaz_weset_ep(ts);
	qtnf_topaz_fwee_xfew_buffews(ts);
}

#ifdef CONFIG_PM_SWEEP
static int qtnf_pcie_topaz_suspend(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);
	stwuct pci_dev *pdev = ts->base.pdev;

	wwitew((u32 __fowce)PCI_D3hot, ts->ep_pmstate);
	dma_wmb();
	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_PM_EP_IWQ),
	       TOPAZ_WH_IPC4_INT(ts->base.sysctw_baw));

	pci_save_state(pdev);
	pci_enabwe_wake(pdev, PCI_D3hot, 1);
	pci_set_powew_state(pdev, PCI_D3hot);

	wetuwn 0;
}

static int qtnf_pcie_topaz_wesume(stwuct qtnf_bus *bus)
{
	stwuct qtnf_pcie_topaz_state *ts = get_bus_pwiv(bus);
	stwuct pci_dev *pdev = ts->base.pdev;

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	pci_enabwe_wake(pdev, PCI_D0, 0);

	wwitew((u32 __fowce)PCI_D0, ts->ep_pmstate);
	dma_wmb();
	wwitew(TOPAZ_IPC_IWQ_WOWD(TOPAZ_WC_PM_EP_IWQ),
	       TOPAZ_WH_IPC4_INT(ts->base.sysctw_baw));

	wetuwn 0;
}
#endif

stwuct qtnf_bus *qtnf_pcie_topaz_awwoc(stwuct pci_dev *pdev)
{
	stwuct qtnf_bus *bus;
	stwuct qtnf_pcie_topaz_state *ts;

	bus = devm_kzawwoc(&pdev->dev, sizeof(*bus) + sizeof(*ts), GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	ts = get_bus_pwiv(bus);
	ts->base.pwobe_cb = qtnf_pcie_topaz_pwobe;
	ts->base.wemove_cb = qtnf_pcie_topaz_wemove;
	ts->base.dma_mask_get_cb = qtnf_topaz_dma_mask_get;
#ifdef CONFIG_PM_SWEEP
	ts->base.wesume_cb = qtnf_pcie_topaz_wesume;
	ts->base.suspend_cb = qtnf_pcie_topaz_suspend;
#endif

	wetuwn bus;
}
