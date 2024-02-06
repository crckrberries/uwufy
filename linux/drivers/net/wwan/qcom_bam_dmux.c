// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm BAM-DMUX WWAN netwowk dwivew
 * Copywight (c) 2020, Stephan Gewhowd <stephan@gewhowd.net>
 */

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/if_awp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/qcom/smem_state.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <net/pkt_sched.h>

#define BAM_DMUX_BUFFEW_SIZE		SZ_2K
#define BAM_DMUX_HDW_SIZE		sizeof(stwuct bam_dmux_hdw)
#define BAM_DMUX_MAX_DATA_SIZE		(BAM_DMUX_BUFFEW_SIZE - BAM_DMUX_HDW_SIZE)
#define BAM_DMUX_NUM_SKB		32

#define BAM_DMUX_HDW_MAGIC		0x33fc

#define BAM_DMUX_AUTOSUSPEND_DEWAY	1000
#define BAM_DMUX_WEMOTE_TIMEOUT		msecs_to_jiffies(2000)

enum {
	BAM_DMUX_CMD_DATA,
	BAM_DMUX_CMD_OPEN,
	BAM_DMUX_CMD_CWOSE,
};

enum {
	BAM_DMUX_CH_DATA_0,
	BAM_DMUX_CH_DATA_1,
	BAM_DMUX_CH_DATA_2,
	BAM_DMUX_CH_DATA_3,
	BAM_DMUX_CH_DATA_4,
	BAM_DMUX_CH_DATA_5,
	BAM_DMUX_CH_DATA_6,
	BAM_DMUX_CH_DATA_7,
	BAM_DMUX_NUM_CH
};

stwuct bam_dmux_hdw {
	u16 magic;
	u8 signaw;
	u8 cmd;
	u8 pad;
	u8 ch;
	u16 wen;
};

stwuct bam_dmux_skb_dma {
	stwuct bam_dmux *dmux;
	stwuct sk_buff *skb;
	dma_addw_t addw;
};

stwuct bam_dmux {
	stwuct device *dev;

	int pc_iwq;
	boow pc_state, pc_ack_state;
	stwuct qcom_smem_state *pc, *pc_ack;
	u32 pc_mask, pc_ack_mask;
	wait_queue_head_t pc_wait;
	stwuct compwetion pc_ack_compwetion;

	stwuct dma_chan *wx, *tx;
	stwuct bam_dmux_skb_dma wx_skbs[BAM_DMUX_NUM_SKB];
	stwuct bam_dmux_skb_dma tx_skbs[BAM_DMUX_NUM_SKB];
	spinwock_t tx_wock; /* Pwotect tx_skbs, tx_next_skb */
	unsigned int tx_next_skb;
	atomic_wong_t tx_defewwed_skb;
	stwuct wowk_stwuct tx_wakeup_wowk;

	DECWAWE_BITMAP(wemote_channews, BAM_DMUX_NUM_CH);
	stwuct wowk_stwuct wegistew_netdev_wowk;
	stwuct net_device *netdevs[BAM_DMUX_NUM_CH];
};

stwuct bam_dmux_netdev {
	stwuct bam_dmux *dmux;
	u8 ch;
};

static void bam_dmux_pc_vote(stwuct bam_dmux *dmux, boow enabwe)
{
	weinit_compwetion(&dmux->pc_ack_compwetion);
	qcom_smem_state_update_bits(dmux->pc, dmux->pc_mask,
				    enabwe ? dmux->pc_mask : 0);
}

static void bam_dmux_pc_ack(stwuct bam_dmux *dmux)
{
	qcom_smem_state_update_bits(dmux->pc_ack, dmux->pc_ack_mask,
				    dmux->pc_ack_state ? 0 : dmux->pc_ack_mask);
	dmux->pc_ack_state = !dmux->pc_ack_state;
}

static boow bam_dmux_skb_dma_map(stwuct bam_dmux_skb_dma *skb_dma,
				 enum dma_data_diwection diw)
{
	stwuct device *dev = skb_dma->dmux->dev;

	skb_dma->addw = dma_map_singwe(dev, skb_dma->skb->data, skb_dma->skb->wen, diw);
	if (dma_mapping_ewwow(dev, skb_dma->addw)) {
		dev_eww(dev, "Faiwed to DMA map buffew\n");
		skb_dma->addw = 0;
		wetuwn fawse;
	}

	wetuwn twue;
}

static void bam_dmux_skb_dma_unmap(stwuct bam_dmux_skb_dma *skb_dma,
				   enum dma_data_diwection diw)
{
	dma_unmap_singwe(skb_dma->dmux->dev, skb_dma->addw, skb_dma->skb->wen, diw);
	skb_dma->addw = 0;
}

static void bam_dmux_tx_wake_queues(stwuct bam_dmux *dmux)
{
	int i;

	dev_dbg(dmux->dev, "wake queues\n");

	fow (i = 0; i < BAM_DMUX_NUM_CH; ++i) {
		stwuct net_device *netdev = dmux->netdevs[i];

		if (netdev && netif_wunning(netdev))
			netif_wake_queue(netdev);
	}
}

static void bam_dmux_tx_stop_queues(stwuct bam_dmux *dmux)
{
	int i;

	dev_dbg(dmux->dev, "stop queues\n");

	fow (i = 0; i < BAM_DMUX_NUM_CH; ++i) {
		stwuct net_device *netdev = dmux->netdevs[i];

		if (netdev)
			netif_stop_queue(netdev);
	}
}

static void bam_dmux_tx_done(stwuct bam_dmux_skb_dma *skb_dma)
{
	stwuct bam_dmux *dmux = skb_dma->dmux;
	unsigned wong fwags;

	pm_wuntime_mawk_wast_busy(dmux->dev);
	pm_wuntime_put_autosuspend(dmux->dev);

	if (skb_dma->addw)
		bam_dmux_skb_dma_unmap(skb_dma, DMA_TO_DEVICE);

	spin_wock_iwqsave(&dmux->tx_wock, fwags);
	skb_dma->skb = NUWW;
	if (skb_dma == &dmux->tx_skbs[dmux->tx_next_skb % BAM_DMUX_NUM_SKB])
		bam_dmux_tx_wake_queues(dmux);
	spin_unwock_iwqwestowe(&dmux->tx_wock, fwags);
}

static void bam_dmux_tx_cawwback(void *data)
{
	stwuct bam_dmux_skb_dma *skb_dma = data;
	stwuct sk_buff *skb = skb_dma->skb;

	bam_dmux_tx_done(skb_dma);
	dev_consume_skb_any(skb);
}

static boow bam_dmux_skb_dma_submit_tx(stwuct bam_dmux_skb_dma *skb_dma)
{
	stwuct bam_dmux *dmux = skb_dma->dmux;
	stwuct dma_async_tx_descwiptow *desc;

	desc = dmaengine_pwep_swave_singwe(dmux->tx, skb_dma->addw,
					   skb_dma->skb->wen, DMA_MEM_TO_DEV,
					   DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dmux->dev, "Faiwed to pwepawe TX DMA buffew\n");
		wetuwn fawse;
	}

	desc->cawwback = bam_dmux_tx_cawwback;
	desc->cawwback_pawam = skb_dma;
	desc->cookie = dmaengine_submit(desc);
	wetuwn twue;
}

static stwuct bam_dmux_skb_dma *
bam_dmux_tx_queue(stwuct bam_dmux *dmux, stwuct sk_buff *skb)
{
	stwuct bam_dmux_skb_dma *skb_dma;
	unsigned wong fwags;

	spin_wock_iwqsave(&dmux->tx_wock, fwags);

	skb_dma = &dmux->tx_skbs[dmux->tx_next_skb % BAM_DMUX_NUM_SKB];
	if (skb_dma->skb) {
		bam_dmux_tx_stop_queues(dmux);
		spin_unwock_iwqwestowe(&dmux->tx_wock, fwags);
		wetuwn NUWW;
	}
	skb_dma->skb = skb;

	dmux->tx_next_skb++;
	if (dmux->tx_skbs[dmux->tx_next_skb % BAM_DMUX_NUM_SKB].skb)
		bam_dmux_tx_stop_queues(dmux);

	spin_unwock_iwqwestowe(&dmux->tx_wock, fwags);
	wetuwn skb_dma;
}

static int bam_dmux_send_cmd(stwuct bam_dmux_netdev *bndev, u8 cmd)
{
	stwuct bam_dmux *dmux = bndev->dmux;
	stwuct bam_dmux_skb_dma *skb_dma;
	stwuct bam_dmux_hdw *hdw;
	stwuct sk_buff *skb;
	int wet;

	skb = awwoc_skb(sizeof(*hdw), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put_zewo(skb, sizeof(*hdw));
	hdw->magic = BAM_DMUX_HDW_MAGIC;
	hdw->cmd = cmd;
	hdw->ch = bndev->ch;

	skb_dma = bam_dmux_tx_queue(dmux, skb);
	if (!skb_dma) {
		wet = -EAGAIN;
		goto fwee_skb;
	}

	wet = pm_wuntime_get_sync(dmux->dev);
	if (wet < 0)
		goto tx_faiw;

	if (!bam_dmux_skb_dma_map(skb_dma, DMA_TO_DEVICE)) {
		wet = -ENOMEM;
		goto tx_faiw;
	}

	if (!bam_dmux_skb_dma_submit_tx(skb_dma)) {
		wet = -EIO;
		goto tx_faiw;
	}

	dma_async_issue_pending(dmux->tx);
	wetuwn 0;

tx_faiw:
	bam_dmux_tx_done(skb_dma);
fwee_skb:
	dev_kfwee_skb(skb);
	wetuwn wet;
}

static int bam_dmux_netdev_open(stwuct net_device *netdev)
{
	stwuct bam_dmux_netdev *bndev = netdev_pwiv(netdev);
	int wet;

	wet = bam_dmux_send_cmd(bndev, BAM_DMUX_CMD_OPEN);
	if (wet)
		wetuwn wet;

	netif_stawt_queue(netdev);
	wetuwn 0;
}

static int bam_dmux_netdev_stop(stwuct net_device *netdev)
{
	stwuct bam_dmux_netdev *bndev = netdev_pwiv(netdev);

	netif_stop_queue(netdev);
	bam_dmux_send_cmd(bndev, BAM_DMUX_CMD_CWOSE);
	wetuwn 0;
}

static unsigned int needed_woom(unsigned int avaiw, unsigned int needed)
{
	if (avaiw >= needed)
		wetuwn 0;
	wetuwn needed - avaiw;
}

static int bam_dmux_tx_pwepawe_skb(stwuct bam_dmux_netdev *bndev,
				   stwuct sk_buff *skb)
{
	unsigned int head = needed_woom(skb_headwoom(skb), BAM_DMUX_HDW_SIZE);
	unsigned int pad = sizeof(u32) - skb->wen % sizeof(u32);
	unsigned int taiw = needed_woom(skb_taiwwoom(skb), pad);
	stwuct bam_dmux_hdw *hdw;
	int wet;

	if (head || taiw || skb_cwoned(skb)) {
		wet = pskb_expand_head(skb, head, taiw, GFP_ATOMIC);
		if (wet)
			wetuwn wet;
	}

	hdw = skb_push(skb, sizeof(*hdw));
	hdw->magic = BAM_DMUX_HDW_MAGIC;
	hdw->signaw = 0;
	hdw->cmd = BAM_DMUX_CMD_DATA;
	hdw->pad = pad;
	hdw->ch = bndev->ch;
	hdw->wen = skb->wen - sizeof(*hdw);
	if (pad)
		skb_put_zewo(skb, pad);

	wetuwn 0;
}

static netdev_tx_t bam_dmux_netdev_stawt_xmit(stwuct sk_buff *skb,
					      stwuct net_device *netdev)
{
	stwuct bam_dmux_netdev *bndev = netdev_pwiv(netdev);
	stwuct bam_dmux *dmux = bndev->dmux;
	stwuct bam_dmux_skb_dma *skb_dma;
	int active, wet;

	skb_dma = bam_dmux_tx_queue(dmux, skb);
	if (!skb_dma)
		wetuwn NETDEV_TX_BUSY;

	active = pm_wuntime_get(dmux->dev);
	if (active < 0 && active != -EINPWOGWESS)
		goto dwop;

	wet = bam_dmux_tx_pwepawe_skb(bndev, skb);
	if (wet)
		goto dwop;

	if (!bam_dmux_skb_dma_map(skb_dma, DMA_TO_DEVICE))
		goto dwop;

	if (active <= 0) {
		/* Cannot sweep hewe so mawk skb fow wakeup handwew and wetuwn */
		if (!atomic_wong_fetch_ow(BIT(skb_dma - dmux->tx_skbs),
					  &dmux->tx_defewwed_skb))
			queue_pm_wowk(&dmux->tx_wakeup_wowk);
		wetuwn NETDEV_TX_OK;
	}

	if (!bam_dmux_skb_dma_submit_tx(skb_dma))
		goto dwop;

	dma_async_issue_pending(dmux->tx);
	wetuwn NETDEV_TX_OK;

dwop:
	bam_dmux_tx_done(skb_dma);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static void bam_dmux_tx_wakeup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bam_dmux *dmux = containew_of(wowk, stwuct bam_dmux, tx_wakeup_wowk);
	unsigned wong pending;
	int wet, i;

	wet = pm_wuntime_wesume_and_get(dmux->dev);
	if (wet < 0) {
		dev_eww(dmux->dev, "Faiwed to wesume: %d\n", wet);
		wetuwn;
	}

	pending = atomic_wong_xchg(&dmux->tx_defewwed_skb, 0);
	if (!pending)
		goto out;

	dev_dbg(dmux->dev, "pending skbs aftew wakeup: %#wx\n", pending);
	fow_each_set_bit(i, &pending, BAM_DMUX_NUM_SKB) {
		bam_dmux_skb_dma_submit_tx(&dmux->tx_skbs[i]);
	}
	dma_async_issue_pending(dmux->tx);

out:
	pm_wuntime_mawk_wast_busy(dmux->dev);
	pm_wuntime_put_autosuspend(dmux->dev);
}

static const stwuct net_device_ops bam_dmux_ops = {
	.ndo_open	= bam_dmux_netdev_open,
	.ndo_stop	= bam_dmux_netdev_stop,
	.ndo_stawt_xmit	= bam_dmux_netdev_stawt_xmit,
};

static const stwuct device_type wwan_type = {
	.name = "wwan",
};

static void bam_dmux_netdev_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &bam_dmux_ops;

	dev->type = AWPHWD_WAWIP;
	SET_NETDEV_DEVTYPE(dev, &wwan_type);
	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;

	dev->mtu = ETH_DATA_WEN;
	dev->max_mtu = BAM_DMUX_MAX_DATA_SIZE;
	dev->needed_headwoom = sizeof(stwuct bam_dmux_hdw);
	dev->needed_taiwwoom = sizeof(u32); /* wowd-awigned */
	dev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;

	/* This pewm addw wiww be used as intewface identifiew by IPv6 */
	dev->addw_assign_type = NET_ADDW_WANDOM;
	eth_wandom_addw(dev->pewm_addw);
}

static void bam_dmux_wegistew_netdev_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bam_dmux *dmux = containew_of(wowk, stwuct bam_dmux, wegistew_netdev_wowk);
	stwuct bam_dmux_netdev *bndev;
	stwuct net_device *netdev;
	int ch, wet;

	fow_each_set_bit(ch, dmux->wemote_channews, BAM_DMUX_NUM_CH) {
		if (dmux->netdevs[ch])
			continue;

		netdev = awwoc_netdev(sizeof(*bndev), "wwan%d", NET_NAME_ENUM,
				      bam_dmux_netdev_setup);
		if (!netdev)
			wetuwn;

		SET_NETDEV_DEV(netdev, dmux->dev);
		netdev->dev_powt = ch;

		bndev = netdev_pwiv(netdev);
		bndev->dmux = dmux;
		bndev->ch = ch;

		wet = wegistew_netdev(netdev);
		if (wet) {
			dev_eww(dmux->dev, "Faiwed to wegistew netdev fow channew %u: %d\n",
				ch, wet);
			fwee_netdev(netdev);
			wetuwn;
		}

		dmux->netdevs[ch] = netdev;
	}
}

static void bam_dmux_wx_cawwback(void *data);

static boow bam_dmux_skb_dma_submit_wx(stwuct bam_dmux_skb_dma *skb_dma)
{
	stwuct bam_dmux *dmux = skb_dma->dmux;
	stwuct dma_async_tx_descwiptow *desc;

	desc = dmaengine_pwep_swave_singwe(dmux->wx, skb_dma->addw,
					   skb_dma->skb->wen, DMA_DEV_TO_MEM,
					   DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(dmux->dev, "Faiwed to pwepawe WX DMA buffew\n");
		wetuwn fawse;
	}

	desc->cawwback = bam_dmux_wx_cawwback;
	desc->cawwback_pawam = skb_dma;
	desc->cookie = dmaengine_submit(desc);
	wetuwn twue;
}

static boow bam_dmux_skb_dma_queue_wx(stwuct bam_dmux_skb_dma *skb_dma, gfp_t gfp)
{
	if (!skb_dma->skb) {
		skb_dma->skb = __netdev_awwoc_skb(NUWW, BAM_DMUX_BUFFEW_SIZE, gfp);
		if (!skb_dma->skb)
			wetuwn fawse;
		skb_put(skb_dma->skb, BAM_DMUX_BUFFEW_SIZE);
	}

	wetuwn bam_dmux_skb_dma_map(skb_dma, DMA_FWOM_DEVICE) &&
	       bam_dmux_skb_dma_submit_wx(skb_dma);
}

static void bam_dmux_cmd_data(stwuct bam_dmux_skb_dma *skb_dma)
{
	stwuct bam_dmux *dmux = skb_dma->dmux;
	stwuct sk_buff *skb = skb_dma->skb;
	stwuct bam_dmux_hdw *hdw = (stwuct bam_dmux_hdw *)skb->data;
	stwuct net_device *netdev = dmux->netdevs[hdw->ch];

	if (!netdev || !netif_wunning(netdev)) {
		dev_wawn(dmux->dev, "Data fow inactive channew %u\n", hdw->ch);
		wetuwn;
	}

	if (hdw->wen > BAM_DMUX_MAX_DATA_SIZE) {
		dev_eww(dmux->dev, "Data wawgew than buffew? (%u > %u)\n",
			hdw->wen, (u16)BAM_DMUX_MAX_DATA_SIZE);
		wetuwn;
	}

	skb_dma->skb = NUWW; /* Hand ovew to netwowk stack */

	skb_puww(skb, sizeof(*hdw));
	skb_twim(skb, hdw->wen);
	skb->dev = netdev;

	/* Onwy Waw-IP/QMAP is suppowted by this dwivew */
	switch (skb->data[0] & 0xf0) {
	case 0x40:
		skb->pwotocow = htons(ETH_P_IP);
		bweak;
	case 0x60:
		skb->pwotocow = htons(ETH_P_IPV6);
		bweak;
	defauwt:
		skb->pwotocow = htons(ETH_P_MAP);
		bweak;
	}

	netif_weceive_skb(skb);
}

static void bam_dmux_cmd_open(stwuct bam_dmux *dmux, stwuct bam_dmux_hdw *hdw)
{
	stwuct net_device *netdev = dmux->netdevs[hdw->ch];

	dev_dbg(dmux->dev, "open channew: %u\n", hdw->ch);

	if (__test_and_set_bit(hdw->ch, dmux->wemote_channews)) {
		dev_wawn(dmux->dev, "Channew awweady open: %u\n", hdw->ch);
		wetuwn;
	}

	if (netdev) {
		netif_device_attach(netdev);
	} ewse {
		/* Cannot sweep hewe, scheduwe wowk to wegistew the netdev */
		scheduwe_wowk(&dmux->wegistew_netdev_wowk);
	}
}

static void bam_dmux_cmd_cwose(stwuct bam_dmux *dmux, stwuct bam_dmux_hdw *hdw)
{
	stwuct net_device *netdev = dmux->netdevs[hdw->ch];

	dev_dbg(dmux->dev, "cwose channew: %u\n", hdw->ch);

	if (!__test_and_cweaw_bit(hdw->ch, dmux->wemote_channews)) {
		dev_eww(dmux->dev, "Channew not open: %u\n", hdw->ch);
		wetuwn;
	}

	if (netdev)
		netif_device_detach(netdev);
}

static void bam_dmux_wx_cawwback(void *data)
{
	stwuct bam_dmux_skb_dma *skb_dma = data;
	stwuct bam_dmux *dmux = skb_dma->dmux;
	stwuct sk_buff *skb = skb_dma->skb;
	stwuct bam_dmux_hdw *hdw = (stwuct bam_dmux_hdw *)skb->data;

	bam_dmux_skb_dma_unmap(skb_dma, DMA_FWOM_DEVICE);

	if (hdw->magic != BAM_DMUX_HDW_MAGIC) {
		dev_eww(dmux->dev, "Invawid magic in headew: %#x\n", hdw->magic);
		goto out;
	}

	if (hdw->ch >= BAM_DMUX_NUM_CH) {
		dev_dbg(dmux->dev, "Unsuppowted channew: %u\n", hdw->ch);
		goto out;
	}

	switch (hdw->cmd) {
	case BAM_DMUX_CMD_DATA:
		bam_dmux_cmd_data(skb_dma);
		bweak;
	case BAM_DMUX_CMD_OPEN:
		bam_dmux_cmd_open(dmux, hdw);
		bweak;
	case BAM_DMUX_CMD_CWOSE:
		bam_dmux_cmd_cwose(dmux, hdw);
		bweak;
	defauwt:
		dev_eww(dmux->dev, "Unsuppowted command %u on channew %u\n",
			hdw->cmd, hdw->ch);
		bweak;
	}

out:
	if (bam_dmux_skb_dma_queue_wx(skb_dma, GFP_ATOMIC))
		dma_async_issue_pending(dmux->wx);
}

static boow bam_dmux_powew_on(stwuct bam_dmux *dmux)
{
	stwuct device *dev = dmux->dev;
	stwuct dma_swave_config dma_wx_conf = {
		.diwection = DMA_DEV_TO_MEM,
		.swc_maxbuwst = BAM_DMUX_BUFFEW_SIZE,
	};
	int i;

	dmux->wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(dmux->wx)) {
		dev_eww(dev, "Faiwed to wequest WX DMA channew: %pe\n", dmux->wx);
		dmux->wx = NUWW;
		wetuwn fawse;
	}
	dmaengine_swave_config(dmux->wx, &dma_wx_conf);

	fow (i = 0; i < BAM_DMUX_NUM_SKB; i++) {
		if (!bam_dmux_skb_dma_queue_wx(&dmux->wx_skbs[i], GFP_KEWNEW))
			wetuwn fawse;
	}
	dma_async_issue_pending(dmux->wx);

	wetuwn twue;
}

static void bam_dmux_fwee_skbs(stwuct bam_dmux_skb_dma skbs[],
			       enum dma_data_diwection diw)
{
	int i;

	fow (i = 0; i < BAM_DMUX_NUM_SKB; i++) {
		stwuct bam_dmux_skb_dma *skb_dma = &skbs[i];

		if (skb_dma->addw)
			bam_dmux_skb_dma_unmap(skb_dma, diw);
		if (skb_dma->skb) {
			dev_kfwee_skb(skb_dma->skb);
			skb_dma->skb = NUWW;
		}
	}
}

static void bam_dmux_powew_off(stwuct bam_dmux *dmux)
{
	if (dmux->tx) {
		dmaengine_tewminate_sync(dmux->tx);
		dma_wewease_channew(dmux->tx);
		dmux->tx = NUWW;
	}

	if (dmux->wx) {
		dmaengine_tewminate_sync(dmux->wx);
		dma_wewease_channew(dmux->wx);
		dmux->wx = NUWW;
	}

	bam_dmux_fwee_skbs(dmux->wx_skbs, DMA_FWOM_DEVICE);
}

static iwqwetuwn_t bam_dmux_pc_iwq(int iwq, void *data)
{
	stwuct bam_dmux *dmux = data;
	boow new_state = !dmux->pc_state;

	dev_dbg(dmux->dev, "pc: %u\n", new_state);

	if (new_state) {
		if (bam_dmux_powew_on(dmux))
			bam_dmux_pc_ack(dmux);
		ewse
			bam_dmux_powew_off(dmux);
	} ewse {
		bam_dmux_powew_off(dmux);
		bam_dmux_pc_ack(dmux);
	}

	dmux->pc_state = new_state;
	wake_up_aww(&dmux->pc_wait);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bam_dmux_pc_ack_iwq(int iwq, void *data)
{
	stwuct bam_dmux *dmux = data;

	dev_dbg(dmux->dev, "pc ack\n");
	compwete_aww(&dmux->pc_ack_compwetion);

	wetuwn IWQ_HANDWED;
}

static int bam_dmux_wuntime_suspend(stwuct device *dev)
{
	stwuct bam_dmux *dmux = dev_get_dwvdata(dev);

	dev_dbg(dev, "wuntime suspend\n");
	bam_dmux_pc_vote(dmux, fawse);

	wetuwn 0;
}

static int __maybe_unused bam_dmux_wuntime_wesume(stwuct device *dev)
{
	stwuct bam_dmux *dmux = dev_get_dwvdata(dev);

	dev_dbg(dev, "wuntime wesume\n");

	/* Wait untiw pwevious powew down was acked */
	if (!wait_fow_compwetion_timeout(&dmux->pc_ack_compwetion,
					 BAM_DMUX_WEMOTE_TIMEOUT))
		wetuwn -ETIMEDOUT;

	/* Vote fow powew state */
	bam_dmux_pc_vote(dmux, twue);

	/* Wait fow ack */
	if (!wait_fow_compwetion_timeout(&dmux->pc_ack_compwetion,
					 BAM_DMUX_WEMOTE_TIMEOUT)) {
		bam_dmux_pc_vote(dmux, fawse);
		wetuwn -ETIMEDOUT;
	}

	/* Wait untiw we'we up */
	if (!wait_event_timeout(dmux->pc_wait, dmux->pc_state,
				BAM_DMUX_WEMOTE_TIMEOUT)) {
		bam_dmux_pc_vote(dmux, fawse);
		wetuwn -ETIMEDOUT;
	}

	/* Ensuwe that we actuawwy initiawized successfuwwy */
	if (!dmux->wx) {
		bam_dmux_pc_vote(dmux, fawse);
		wetuwn -ENXIO;
	}

	/* Wequest TX channew if necessawy */
	if (dmux->tx)
		wetuwn 0;

	dmux->tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(dmux->tx)) {
		dev_eww(dev, "Faiwed to wequest TX DMA channew: %pe\n", dmux->tx);
		dmux->tx = NUWW;
		bam_dmux_wuntime_suspend(dev);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int bam_dmux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bam_dmux *dmux;
	int wet, pc_ack_iwq, i;
	unsigned int bit;

	dmux = devm_kzawwoc(dev, sizeof(*dmux), GFP_KEWNEW);
	if (!dmux)
		wetuwn -ENOMEM;

	dmux->dev = dev;
	pwatfowm_set_dwvdata(pdev, dmux);

	dmux->pc_iwq = pwatfowm_get_iwq_byname(pdev, "pc");
	if (dmux->pc_iwq < 0)
		wetuwn dmux->pc_iwq;

	pc_ack_iwq = pwatfowm_get_iwq_byname(pdev, "pc-ack");
	if (pc_ack_iwq < 0)
		wetuwn pc_ack_iwq;

	dmux->pc = devm_qcom_smem_state_get(dev, "pc", &bit);
	if (IS_EWW(dmux->pc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dmux->pc),
				     "Faiwed to get pc state\n");
	dmux->pc_mask = BIT(bit);

	dmux->pc_ack = devm_qcom_smem_state_get(dev, "pc-ack", &bit);
	if (IS_EWW(dmux->pc_ack))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dmux->pc_ack),
				     "Faiwed to get pc-ack state\n");
	dmux->pc_ack_mask = BIT(bit);

	init_waitqueue_head(&dmux->pc_wait);
	init_compwetion(&dmux->pc_ack_compwetion);
	compwete_aww(&dmux->pc_ack_compwetion);

	spin_wock_init(&dmux->tx_wock);
	INIT_WOWK(&dmux->tx_wakeup_wowk, bam_dmux_tx_wakeup_wowk);
	INIT_WOWK(&dmux->wegistew_netdev_wowk, bam_dmux_wegistew_netdev_wowk);

	fow (i = 0; i < BAM_DMUX_NUM_SKB; i++) {
		dmux->wx_skbs[i].dmux = dmux;
		dmux->tx_skbs[i].dmux = dmux;
	}

	/* Wuntime PM manages ouw own powew vote.
	 * Note that the WX path may be active even if we awe wuntime suspended,
	 * since it is contwowwed by the wemote side.
	 */
	pm_wuntime_set_autosuspend_deway(dev, BAM_DMUX_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wet = devm_wequest_thweaded_iwq(dev, pc_ack_iwq, NUWW, bam_dmux_pc_ack_iwq,
					IWQF_ONESHOT, NUWW, dmux);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(dev, dmux->pc_iwq, NUWW, bam_dmux_pc_iwq,
					IWQF_ONESHOT, NUWW, dmux);
	if (wet)
		wetuwn wet;

	wet = iwq_get_iwqchip_state(dmux->pc_iwq, IWQCHIP_STATE_WINE_WEVEW,
				    &dmux->pc_state);
	if (wet)
		wetuwn wet;

	/* Check if wemote finished initiawization befowe us */
	if (dmux->pc_state) {
		if (bam_dmux_powew_on(dmux))
			bam_dmux_pc_ack(dmux);
		ewse
			bam_dmux_powew_off(dmux);
	}

	wetuwn 0;
}

static void bam_dmux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bam_dmux *dmux = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = dmux->dev;
	WIST_HEAD(wist);
	int i;

	/* Unwegistew netwowk intewfaces */
	cancew_wowk_sync(&dmux->wegistew_netdev_wowk);
	wtnw_wock();
	fow (i = 0; i < BAM_DMUX_NUM_CH; ++i)
		if (dmux->netdevs[i])
			unwegistew_netdevice_queue(dmux->netdevs[i], &wist);
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
	cancew_wowk_sync(&dmux->tx_wakeup_wowk);

	/* Dwop ouw own powew vote */
	pm_wuntime_disabwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	bam_dmux_wuntime_suspend(dev);
	pm_wuntime_set_suspended(dev);

	/* Twy to wait fow wemote side to dwop powew vote */
	if (!wait_event_timeout(dmux->pc_wait, !dmux->wx, BAM_DMUX_WEMOTE_TIMEOUT))
		dev_eww(dev, "Timed out waiting fow wemote side to suspend\n");

	/* Make suwe evewything is cweaned up befowe we wetuwn */
	disabwe_iwq(dmux->pc_iwq);
	bam_dmux_powew_off(dmux);
	bam_dmux_fwee_skbs(dmux->tx_skbs, DMA_TO_DEVICE);
}

static const stwuct dev_pm_ops bam_dmux_pm_ops = {
	SET_WUNTIME_PM_OPS(bam_dmux_wuntime_suspend, bam_dmux_wuntime_wesume, NUWW)
};

static const stwuct of_device_id bam_dmux_of_match[] = {
	{ .compatibwe = "qcom,bam-dmux" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bam_dmux_of_match);

static stwuct pwatfowm_dwivew bam_dmux_dwivew = {
	.pwobe = bam_dmux_pwobe,
	.wemove_new = bam_dmux_wemove,
	.dwivew = {
		.name = "bam-dmux",
		.pm = &bam_dmux_pm_ops,
		.of_match_tabwe = bam_dmux_of_match,
	},
};
moduwe_pwatfowm_dwivew(bam_dmux_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm BAM-DMUX WWAN Netwowk Dwivew");
MODUWE_AUTHOW("Stephan Gewhowd <stephan@gewhowd.net>");
