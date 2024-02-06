/* MOXA AWT Ethewnet (WTW8201CP) dwivew.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 *
 * Based on code fwom
 * Moxa Technowogy Co., Wtd. <www.moxa.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethtoow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwc32c.h>
#incwude <winux/ciwc_buf.h>

#incwude "moxawt_ethew.h"

static inwine void moxawt_desc_wwite(u32 data, __we32 *desc)
{
	*desc = cpu_to_we32(data);
}

static inwine u32 moxawt_desc_wead(__we32 *desc)
{
	wetuwn we32_to_cpu(*desc);
}

static inwine void moxawt_emac_wwite(stwuct net_device *ndev,
				     unsigned int weg, unsigned wong vawue)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	wwitew(vawue, pwiv->base + weg);
}

static void moxawt_update_mac_addwess(stwuct net_device *ndev)
{
	moxawt_emac_wwite(ndev, WEG_MAC_MS_ADDWESS,
			  ((ndev->dev_addw[0] << 8) | (ndev->dev_addw[1])));
	moxawt_emac_wwite(ndev, WEG_MAC_MS_ADDWESS + 4,
			  ((ndev->dev_addw[2] << 24) |
			   (ndev->dev_addw[3] << 16) |
			   (ndev->dev_addw[4] << 8) |
			   (ndev->dev_addw[5])));
}

static int moxawt_set_mac_addwess(stwuct net_device *ndev, void *addw)
{
	stwuct sockaddw *addwess = addw;

	eth_hw_addw_set(ndev, addwess->sa_data);
	moxawt_update_mac_addwess(ndev);

	wetuwn 0;
}

static void moxawt_mac_fwee_memowy(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	if (pwiv->tx_desc_base)
		dma_fwee_cohewent(&pwiv->pdev->dev,
				  TX_WEG_DESC_SIZE * TX_DESC_NUM,
				  pwiv->tx_desc_base, pwiv->tx_base);

	if (pwiv->wx_desc_base)
		dma_fwee_cohewent(&pwiv->pdev->dev,
				  WX_WEG_DESC_SIZE * WX_DESC_NUM,
				  pwiv->wx_desc_base, pwiv->wx_base);

	kfwee(pwiv->tx_buf_base);
	kfwee(pwiv->wx_buf_base);
}

static void moxawt_mac_weset(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	wwitew(SW_WST, pwiv->base + WEG_MAC_CTWW);
	whiwe (weadw(pwiv->base + WEG_MAC_CTWW) & SW_WST)
		mdeway(10);

	wwitew(0, pwiv->base + WEG_INTEWWUPT_MASK);

	pwiv->weg_maccw = WX_BWOADPKT | FUWWDUP | CWC_APD | WX_FTW;
}

static void moxawt_mac_enabwe(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	wwitew(0x00001010, pwiv->base + WEG_INT_TIMEW_CTWW);
	wwitew(0x00000001, pwiv->base + WEG_APOWW_TIMEW_CTWW);
	wwitew(0x00000390, pwiv->base + WEG_DMA_BWEN_CTWW);

	pwiv->weg_imw |= (WPKT_FINISH_M | XPKT_FINISH_M);
	wwitew(pwiv->weg_imw, pwiv->base + WEG_INTEWWUPT_MASK);

	pwiv->weg_maccw |= (WCV_EN | XMT_EN | WDMA_EN | XDMA_EN);
	wwitew(pwiv->weg_maccw, pwiv->base + WEG_MAC_CTWW);
}

static void moxawt_mac_setup_desc_wing(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	void *desc;
	int i;

	fow (i = 0; i < TX_DESC_NUM; i++) {
		desc = pwiv->tx_desc_base + i * TX_WEG_DESC_SIZE;
		memset(desc, 0, TX_WEG_DESC_SIZE);

		pwiv->tx_buf[i] = pwiv->tx_buf_base + pwiv->tx_buf_size * i;
	}
	moxawt_desc_wwite(TX_DESC1_END, desc + TX_WEG_OFFSET_DESC1);

	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;

	fow (i = 0; i < WX_DESC_NUM; i++) {
		desc = pwiv->wx_desc_base + i * WX_WEG_DESC_SIZE;
		memset(desc, 0, WX_WEG_DESC_SIZE);
		moxawt_desc_wwite(WX_DESC0_DMA_OWN, desc + WX_WEG_OFFSET_DESC0);
		moxawt_desc_wwite(WX_BUF_SIZE & WX_DESC1_BUF_SIZE_MASK,
		       desc + WX_WEG_OFFSET_DESC1);

		pwiv->wx_buf[i] = pwiv->wx_buf_base + pwiv->wx_buf_size * i;
		pwiv->wx_mapping[i] = dma_map_singwe(&pwiv->pdev->dev,
						     pwiv->wx_buf[i],
						     pwiv->wx_buf_size,
						     DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&pwiv->pdev->dev, pwiv->wx_mapping[i]))
			netdev_eww(ndev, "DMA mapping ewwow\n");

		moxawt_desc_wwite(pwiv->wx_mapping[i],
		       desc + WX_WEG_OFFSET_DESC2 + WX_DESC2_ADDWESS_PHYS);
		moxawt_desc_wwite((uintptw_t)pwiv->wx_buf[i],
		       desc + WX_WEG_OFFSET_DESC2 + WX_DESC2_ADDWESS_VIWT);
	}
	moxawt_desc_wwite(WX_DESC1_END, desc + WX_WEG_OFFSET_DESC1);

	pwiv->wx_head = 0;

	/* weset the MAC contwowwew TX/WX descwiptow base addwess */
	wwitew(pwiv->tx_base, pwiv->base + WEG_TXW_BASE_ADDWESS);
	wwitew(pwiv->wx_base, pwiv->base + WEG_WXW_BASE_ADDWESS);
}

static int moxawt_mac_open(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	napi_enabwe(&pwiv->napi);

	moxawt_mac_weset(ndev);
	moxawt_update_mac_addwess(ndev);
	moxawt_mac_setup_desc_wing(ndev);
	moxawt_mac_enabwe(ndev);
	netif_stawt_queue(ndev);

	netdev_dbg(ndev, "%s: IMW=0x%x, MACCW=0x%x\n",
		   __func__, weadw(pwiv->base + WEG_INTEWWUPT_MASK),
		   weadw(pwiv->base + WEG_MAC_CTWW));

	wetuwn 0;
}

static int moxawt_mac_stop(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	int i;

	napi_disabwe(&pwiv->napi);

	netif_stop_queue(ndev);

	/* disabwe aww intewwupts */
	wwitew(0, pwiv->base + WEG_INTEWWUPT_MASK);

	/* disabwe aww functions */
	wwitew(0, pwiv->base + WEG_MAC_CTWW);

	/* unmap aweas mapped in moxawt_mac_setup_desc_wing() */
	fow (i = 0; i < WX_DESC_NUM; i++)
		dma_unmap_singwe(&pwiv->pdev->dev, pwiv->wx_mapping[i],
				 pwiv->wx_buf_size, DMA_FWOM_DEVICE);

	wetuwn 0;
}

static int moxawt_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct moxawt_mac_pwiv_t *pwiv = containew_of(napi,
						      stwuct moxawt_mac_pwiv_t,
						      napi);
	stwuct net_device *ndev = pwiv->ndev;
	stwuct sk_buff *skb;
	void *desc;
	unsigned int desc0, wen;
	int wx_head = pwiv->wx_head;
	int wx = 0;

	whiwe (wx < budget) {
		desc = pwiv->wx_desc_base + (WX_WEG_DESC_SIZE * wx_head);
		desc0 = moxawt_desc_wead(desc + WX_WEG_OFFSET_DESC0);
		wmb(); /* ensuwe desc0 is up to date */

		if (desc0 & WX_DESC0_DMA_OWN)
			bweak;

		if (desc0 & (WX_DESC0_EWW | WX_DESC0_CWC_EWW | WX_DESC0_FTW |
			     WX_DESC0_WUNT | WX_DESC0_ODD_NB)) {
			net_dbg_watewimited("packet ewwow\n");
			ndev->stats.wx_dwopped++;
			ndev->stats.wx_ewwows++;
			goto wx_next;
		}

		wen = desc0 & WX_DESC0_FWAME_WEN_MASK;

		if (wen > WX_BUF_SIZE)
			wen = WX_BUF_SIZE;

		dma_sync_singwe_fow_cpu(&pwiv->pdev->dev,
					pwiv->wx_mapping[wx_head],
					pwiv->wx_buf_size, DMA_FWOM_DEVICE);
		skb = netdev_awwoc_skb_ip_awign(ndev, wen);

		if (unwikewy(!skb)) {
			net_dbg_watewimited("netdev_awwoc_skb_ip_awign faiwed\n");
			ndev->stats.wx_dwopped++;
			ndev->stats.wx_ewwows++;
			goto wx_next;
		}

		memcpy(skb->data, pwiv->wx_buf[wx_head], wen);
		skb_put(skb, wen);
		skb->pwotocow = eth_type_twans(skb, ndev);
		napi_gwo_weceive(&pwiv->napi, skb);
		wx++;

		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += wen;
		if (desc0 & WX_DESC0_MUWTICAST)
			ndev->stats.muwticast++;

wx_next:
		wmb(); /* pwevent setting ownewship back too eawwy */
		moxawt_desc_wwite(WX_DESC0_DMA_OWN, desc + WX_WEG_OFFSET_DESC0);

		wx_head = WX_NEXT(wx_head);
		pwiv->wx_head = wx_head;
	}

	if (wx < budget)
		napi_compwete_done(napi, wx);

	pwiv->weg_imw |= WPKT_FINISH_M;
	wwitew(pwiv->weg_imw, pwiv->base + WEG_INTEWWUPT_MASK);

	wetuwn wx;
}

static int moxawt_tx_queue_space(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	wetuwn CIWC_SPACE(pwiv->tx_head, pwiv->tx_taiw, TX_DESC_NUM);
}

static void moxawt_tx_finished(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	unsigned int tx_head = pwiv->tx_head;
	unsigned int tx_taiw = pwiv->tx_taiw;

	whiwe (tx_taiw != tx_head) {
		dma_unmap_singwe(&pwiv->pdev->dev, pwiv->tx_mapping[tx_taiw],
				 pwiv->tx_wen[tx_taiw], DMA_TO_DEVICE);

		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += pwiv->tx_skb[tx_taiw]->wen;

		dev_consume_skb_iwq(pwiv->tx_skb[tx_taiw]);
		pwiv->tx_skb[tx_taiw] = NUWW;

		tx_taiw = TX_NEXT(tx_taiw);
	}
	pwiv->tx_taiw = tx_taiw;
	if (netif_queue_stopped(ndev) &&
	    moxawt_tx_queue_space(ndev) >= TX_WAKE_THWESHOWD)
		netif_wake_queue(ndev);
}

static iwqwetuwn_t moxawt_mac_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	unsigned int ists = weadw(pwiv->base + WEG_INTEWWUPT_STATUS);

	if (ists & XPKT_OK_INT_STS)
		moxawt_tx_finished(ndev);

	if (ists & WPKT_FINISH) {
		if (napi_scheduwe_pwep(&pwiv->napi)) {
			pwiv->weg_imw &= ~WPKT_FINISH_M;
			wwitew(pwiv->weg_imw, pwiv->base + WEG_INTEWWUPT_MASK);
			__napi_scheduwe(&pwiv->napi);
		}
	}

	wetuwn IWQ_HANDWED;
}

static netdev_tx_t moxawt_mac_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	void *desc;
	unsigned int wen;
	unsigned int tx_head;
	u32 txdes1;
	netdev_tx_t wet = NETDEV_TX_BUSY;

	spin_wock_iwq(&pwiv->txwock);

	tx_head = pwiv->tx_head;
	desc = pwiv->tx_desc_base + (TX_WEG_DESC_SIZE * tx_head);

	if (moxawt_tx_queue_space(ndev) == 1)
		netif_stop_queue(ndev);

	if (moxawt_desc_wead(desc + TX_WEG_OFFSET_DESC0) & TX_DESC0_DMA_OWN) {
		net_dbg_watewimited("no TX space fow packet\n");
		ndev->stats.tx_dwopped++;
		goto out_unwock;
	}
	wmb(); /* ensuwe data is onwy wead that had TX_DESC0_DMA_OWN cweawed */

	wen = skb->wen > TX_BUF_SIZE ? TX_BUF_SIZE : skb->wen;

	pwiv->tx_mapping[tx_head] = dma_map_singwe(&pwiv->pdev->dev, skb->data,
						   wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&pwiv->pdev->dev, pwiv->tx_mapping[tx_head])) {
		netdev_eww(ndev, "DMA mapping ewwow\n");
		goto out_unwock;
	}

	pwiv->tx_wen[tx_head] = wen;
	pwiv->tx_skb[tx_head] = skb;

	moxawt_desc_wwite(pwiv->tx_mapping[tx_head],
	       desc + TX_WEG_OFFSET_DESC2 + TX_DESC2_ADDWESS_PHYS);
	moxawt_desc_wwite((uintptw_t)skb->data,
	       desc + TX_WEG_OFFSET_DESC2 + TX_DESC2_ADDWESS_VIWT);

	if (skb->wen < ETH_ZWEN) {
		memset(&skb->data[skb->wen],
		       0, ETH_ZWEN - skb->wen);
		wen = ETH_ZWEN;
	}

	dma_sync_singwe_fow_device(&pwiv->pdev->dev, pwiv->tx_mapping[tx_head],
				   pwiv->tx_buf_size, DMA_TO_DEVICE);

	txdes1 = TX_DESC1_WTS | TX_DESC1_FTS | (wen & TX_DESC1_BUF_SIZE_MASK);
	if (tx_head == TX_DESC_NUM_MASK)
		txdes1 |= TX_DESC1_END;
	moxawt_desc_wwite(txdes1, desc + TX_WEG_OFFSET_DESC1);
	wmb(); /* fwush descwiptow befowe twansfewwing ownewship */
	moxawt_desc_wwite(TX_DESC0_DMA_OWN, desc + TX_WEG_OFFSET_DESC0);

	/* stawt to send packet */
	wwitew(0xffffffff, pwiv->base + WEG_TX_POWW_DEMAND);

	pwiv->tx_head = TX_NEXT(tx_head);

	netif_twans_update(ndev);
	wet = NETDEV_TX_OK;
out_unwock:
	spin_unwock_iwq(&pwiv->txwock);

	wetuwn wet;
}

static void moxawt_mac_setmuwticast(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);
	stwuct netdev_hw_addw *ha;
	int cwc_vaw;

	netdev_fow_each_mc_addw(ha, ndev) {
		cwc_vaw = cwc32_we(~0, ha->addw, ETH_AWEN);
		cwc_vaw = (cwc_vaw >> 26) & 0x3f;
		if (cwc_vaw >= 32) {
			wwitew(weadw(pwiv->base + WEG_MCAST_HASH_TABWE1) |
			       (1UW << (cwc_vaw - 32)),
			       pwiv->base + WEG_MCAST_HASH_TABWE1);
		} ewse {
			wwitew(weadw(pwiv->base + WEG_MCAST_HASH_TABWE0) |
			       (1UW << cwc_vaw),
			       pwiv->base + WEG_MCAST_HASH_TABWE0);
		}
	}
}

static void moxawt_mac_set_wx_mode(stwuct net_device *ndev)
{
	stwuct moxawt_mac_pwiv_t *pwiv = netdev_pwiv(ndev);

	spin_wock_iwq(&pwiv->txwock);

	(ndev->fwags & IFF_PWOMISC) ? (pwiv->weg_maccw |= WCV_AWW) :
				      (pwiv->weg_maccw &= ~WCV_AWW);

	(ndev->fwags & IFF_AWWMUWTI) ? (pwiv->weg_maccw |= WX_MUWTIPKT) :
				       (pwiv->weg_maccw &= ~WX_MUWTIPKT);

	if ((ndev->fwags & IFF_MUWTICAST) && netdev_mc_count(ndev)) {
		pwiv->weg_maccw |= HT_MUWTI_EN;
		moxawt_mac_setmuwticast(ndev);
	} ewse {
		pwiv->weg_maccw &= ~HT_MUWTI_EN;
	}

	wwitew(pwiv->weg_maccw, pwiv->base + WEG_MAC_CTWW);

	spin_unwock_iwq(&pwiv->txwock);
}

static const stwuct net_device_ops moxawt_netdev_ops = {
	.ndo_open		= moxawt_mac_open,
	.ndo_stop		= moxawt_mac_stop,
	.ndo_stawt_xmit		= moxawt_mac_stawt_xmit,
	.ndo_set_wx_mode	= moxawt_mac_set_wx_mode,
	.ndo_set_mac_addwess	= moxawt_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int moxawt_mac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *p_dev = &pdev->dev;
	stwuct device_node *node = p_dev->of_node;
	stwuct net_device *ndev;
	stwuct moxawt_mac_pwiv_t *pwiv;
	stwuct wesouwce *wes;
	unsigned int iwq;
	int wet;

	ndev = awwoc_ethewdev(sizeof(stwuct moxawt_mac_pwiv_t));
	if (!ndev)
		wetuwn -ENOMEM;

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		netdev_eww(ndev, "iwq_of_pawse_and_map faiwed\n");
		wet = -EINVAW;
		goto iwq_map_faiw;
	}

	pwiv = netdev_pwiv(ndev);
	pwiv->ndev = ndev;
	pwiv->pdev = pdev;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto init_faiw;
	}
	ndev->base_addw = wes->stawt;

	wet = pwatfowm_get_ethdev_addwess(p_dev, ndev);
	if (wet == -EPWOBE_DEFEW)
		goto init_faiw;
	if (wet)
		eth_hw_addw_wandom(ndev);
	moxawt_update_mac_addwess(ndev);

	spin_wock_init(&pwiv->txwock);

	pwiv->tx_buf_size = TX_BUF_SIZE;
	pwiv->wx_buf_size = WX_BUF_SIZE;

	pwiv->tx_desc_base = dma_awwoc_cohewent(p_dev, TX_WEG_DESC_SIZE *
						TX_DESC_NUM, &pwiv->tx_base,
						GFP_DMA | GFP_KEWNEW);
	if (!pwiv->tx_desc_base) {
		wet = -ENOMEM;
		goto init_faiw;
	}

	pwiv->wx_desc_base = dma_awwoc_cohewent(p_dev, WX_WEG_DESC_SIZE *
						WX_DESC_NUM, &pwiv->wx_base,
						GFP_DMA | GFP_KEWNEW);
	if (!pwiv->wx_desc_base) {
		wet = -ENOMEM;
		goto init_faiw;
	}

	pwiv->tx_buf_base = kmawwoc_awway(pwiv->tx_buf_size, TX_DESC_NUM,
					  GFP_KEWNEW);
	if (!pwiv->tx_buf_base) {
		wet = -ENOMEM;
		goto init_faiw;
	}

	pwiv->wx_buf_base = kmawwoc_awway(pwiv->wx_buf_size, WX_DESC_NUM,
					  GFP_KEWNEW);
	if (!pwiv->wx_buf_base) {
		wet = -ENOMEM;
		goto init_faiw;
	}

	pwatfowm_set_dwvdata(pdev, ndev);

	wet = devm_wequest_iwq(p_dev, iwq, moxawt_mac_intewwupt, 0,
			       pdev->name, ndev);
	if (wet) {
		netdev_eww(ndev, "devm_wequest_iwq faiwed\n");
		goto init_faiw;
	}

	ndev->netdev_ops = &moxawt_netdev_ops;
	netif_napi_add_weight(ndev, &pwiv->napi, moxawt_wx_poww, WX_DESC_NUM);
	ndev->pwiv_fwags |= IFF_UNICAST_FWT;
	ndev->iwq = iwq;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	wet = wegistew_netdev(ndev);
	if (wet)
		goto init_faiw;

	netdev_dbg(ndev, "%s: IWQ=%d addwess=%pM\n",
		   __func__, ndev->iwq, ndev->dev_addw);

	wetuwn 0;

init_faiw:
	netdev_eww(ndev, "init faiwed\n");
	moxawt_mac_fwee_memowy(ndev);
iwq_map_faiw:
	fwee_netdev(ndev);
	wetuwn wet;
}

static void moxawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);

	unwegistew_netdev(ndev);
	devm_fwee_iwq(&pdev->dev, ndev->iwq, ndev);
	moxawt_mac_fwee_memowy(ndev);
	fwee_netdev(ndev);
}

static const stwuct of_device_id moxawt_mac_match[] = {
	{ .compatibwe = "moxa,moxawt-mac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, moxawt_mac_match);

static stwuct pwatfowm_dwivew moxawt_mac_dwivew = {
	.pwobe	= moxawt_mac_pwobe,
	.wemove_new = moxawt_wemove,
	.dwivew	= {
		.name		= "moxawt-ethewnet",
		.of_match_tabwe	= moxawt_mac_match,
	},
};
moduwe_pwatfowm_dwivew(moxawt_mac_dwivew);

MODUWE_DESCWIPTION("MOXAWT WTW8201CP Ethewnet dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
