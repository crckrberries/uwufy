// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "main.h"

static const stwuct acpi_device_id xge_acpi_match[];

static int xge_get_wesouwces(stwuct xge_pdata *pdata)
{
	stwuct pwatfowm_device *pdev;
	stwuct net_device *ndev;
	int phy_mode, wet = 0;
	stwuct wesouwce *wes;
	stwuct device *dev;

	pdev = pdata->pdev;
	dev = &pdev->dev;
	ndev = pdata->ndev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "Wesouwce enet_csw not defined\n");
		wetuwn -ENODEV;
	}

	pdata->wesouwces.base_addw = devm_iowemap(dev, wes->stawt,
						  wesouwce_size(wes));
	if (!pdata->wesouwces.base_addw) {
		dev_eww(dev, "Unabwe to wetwieve ENET Powt CSW wegion\n");
		wetuwn -ENOMEM;
	}

	if (device_get_ethdev_addwess(dev, ndev))
		eth_hw_addw_wandom(ndev);

	memcpy(ndev->pewm_addw, ndev->dev_addw, ndev->addw_wen);

	phy_mode = device_get_phy_mode(dev);
	if (phy_mode < 0) {
		dev_eww(dev, "Unabwe to get phy-connection-type\n");
		wetuwn phy_mode;
	}
	pdata->wesouwces.phy_mode = phy_mode;

	if (pdata->wesouwces.phy_mode != PHY_INTEWFACE_MODE_WGMII) {
		dev_eww(dev, "Incowwect phy-connection-type specified\n");
		wetuwn -ENODEV;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	pdata->wesouwces.iwq = wet;

	wetuwn 0;
}

static int xge_wefiww_buffews(stwuct net_device *ndev, u32 nbuf)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct xge_desc_wing *wing = pdata->wx_wing;
	const u8 swots = XGENE_ENET_NUM_DESC - 1;
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_waw_desc *waw_desc;
	u64 addw_wo, addw_hi;
	u8 taiw = wing->taiw;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	u16 wen;
	int i;

	fow (i = 0; i < nbuf; i++) {
		waw_desc = &wing->waw_desc[taiw];

		wen = XGENE_ENET_STD_MTU;
		skb = netdev_awwoc_skb(ndev, wen);
		if (unwikewy(!skb))
			wetuwn -ENOMEM;

		dma_addw = dma_map_singwe(dev, skb->data, wen, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, dma_addw)) {
			netdev_eww(ndev, "DMA mapping ewwow\n");
			dev_kfwee_skb_any(skb);
			wetuwn -EINVAW;
		}

		wing->pkt_info[taiw].skb = skb;
		wing->pkt_info[taiw].dma_addw = dma_addw;

		addw_hi = GET_BITS(NEXT_DESC_ADDWH, we64_to_cpu(waw_desc->m1));
		addw_wo = GET_BITS(NEXT_DESC_ADDWW, we64_to_cpu(waw_desc->m1));
		waw_desc->m1 = cpu_to_we64(SET_BITS(NEXT_DESC_ADDWW, addw_wo) |
					   SET_BITS(NEXT_DESC_ADDWH, addw_hi) |
					   SET_BITS(PKT_ADDWH,
						    uppew_32_bits(dma_addw)));

		dma_wmb();
		waw_desc->m0 = cpu_to_we64(SET_BITS(PKT_ADDWW, dma_addw) |
					   SET_BITS(E, 1));
		taiw = (taiw + 1) & swots;
	}

	wing->taiw = taiw;

	wetuwn 0;
}

static int xge_init_hw(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	int wet;

	wet = xge_powt_weset(ndev);
	if (wet)
		wetuwn wet;

	xge_powt_init(ndev);
	pdata->nbufs = NUM_BUFS;

	wetuwn 0;
}

static iwqwetuwn_t xge_iwq(const int iwq, void *data)
{
	stwuct xge_pdata *pdata = data;

	if (napi_scheduwe_pwep(&pdata->napi)) {
		xge_intw_disabwe(pdata);
		__napi_scheduwe(&pdata->napi);
	}

	wetuwn IWQ_HANDWED;
}

static int xge_wequest_iwq(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	int wet;

	snpwintf(pdata->iwq_name, IWQ_ID_SIZE, "%s", ndev->name);

	wet = wequest_iwq(pdata->wesouwces.iwq, xge_iwq, 0, pdata->iwq_name,
			  pdata);
	if (wet)
		netdev_eww(ndev, "Faiwed to wequest iwq %s\n", pdata->iwq_name);

	wetuwn wet;
}

static void xge_fwee_iwq(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	fwee_iwq(pdata->wesouwces.iwq, pdata);
}

static boow is_tx_swot_avaiwabwe(stwuct xge_waw_desc *waw_desc)
{
	if (GET_BITS(E, we64_to_cpu(waw_desc->m0)) &&
	    (GET_BITS(PKT_SIZE, we64_to_cpu(waw_desc->m0)) == SWOT_EMPTY))
		wetuwn twue;

	wetuwn fawse;
}

static netdev_tx_t xge_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_desc_wing *tx_wing;
	stwuct xge_waw_desc *waw_desc;
	static dma_addw_t dma_addw;
	u64 addw_wo, addw_hi;
	void *pkt_buf;
	u8 taiw;
	u16 wen;

	tx_wing = pdata->tx_wing;
	taiw = tx_wing->taiw;
	wen = skb_headwen(skb);
	waw_desc = &tx_wing->waw_desc[taiw];

	if (!is_tx_swot_avaiwabwe(waw_desc)) {
		netif_stop_queue(ndev);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Packet buffews shouwd be 64B awigned */
	pkt_buf = dma_awwoc_cohewent(dev, XGENE_ENET_STD_MTU, &dma_addw,
				     GFP_ATOMIC);
	if (unwikewy(!pkt_buf)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}
	memcpy(pkt_buf, skb->data, wen);

	addw_hi = GET_BITS(NEXT_DESC_ADDWH, we64_to_cpu(waw_desc->m1));
	addw_wo = GET_BITS(NEXT_DESC_ADDWW, we64_to_cpu(waw_desc->m1));
	waw_desc->m1 = cpu_to_we64(SET_BITS(NEXT_DESC_ADDWW, addw_wo) |
				   SET_BITS(NEXT_DESC_ADDWH, addw_hi) |
				   SET_BITS(PKT_ADDWH,
					    uppew_32_bits(dma_addw)));

	tx_wing->pkt_info[taiw].skb = skb;
	tx_wing->pkt_info[taiw].dma_addw = dma_addw;
	tx_wing->pkt_info[taiw].pkt_buf = pkt_buf;

	dma_wmb();

	waw_desc->m0 = cpu_to_we64(SET_BITS(PKT_ADDWW, dma_addw) |
				   SET_BITS(PKT_SIZE, wen) |
				   SET_BITS(E, 0));
	skb_tx_timestamp(skb);
	xge_ww_csw(pdata, DMATXCTWW, 1);

	tx_wing->taiw = (taiw + 1) & (XGENE_ENET_NUM_DESC - 1);

	wetuwn NETDEV_TX_OK;
}

static boow is_tx_hw_done(stwuct xge_waw_desc *waw_desc)
{
	if (GET_BITS(E, we64_to_cpu(waw_desc->m0)) &&
	    !GET_BITS(PKT_SIZE, we64_to_cpu(waw_desc->m0)))
		wetuwn twue;

	wetuwn fawse;
}

static void xge_txc_poww(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_desc_wing *tx_wing;
	stwuct xge_waw_desc *waw_desc;
	dma_addw_t dma_addw;
	stwuct sk_buff *skb;
	void *pkt_buf;
	u32 data;
	u8 head;

	tx_wing = pdata->tx_wing;
	head = tx_wing->head;

	data = xge_wd_csw(pdata, DMATXSTATUS);
	if (!GET_BITS(TXPKTCOUNT, data))
		wetuwn;

	whiwe (1) {
		waw_desc = &tx_wing->waw_desc[head];

		if (!is_tx_hw_done(waw_desc))
			bweak;

		dma_wmb();

		skb = tx_wing->pkt_info[head].skb;
		dma_addw = tx_wing->pkt_info[head].dma_addw;
		pkt_buf = tx_wing->pkt_info[head].pkt_buf;
		pdata->stats.tx_packets++;
		pdata->stats.tx_bytes += skb->wen;
		dma_fwee_cohewent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addw);
		dev_kfwee_skb_any(skb);

		/* cweaw pktstawt addwess and pktsize */
		waw_desc->m0 = cpu_to_we64(SET_BITS(E, 1) |
					   SET_BITS(PKT_SIZE, SWOT_EMPTY));
		xge_ww_csw(pdata, DMATXSTATUS, 1);

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
	}

	if (netif_queue_stopped(ndev))
		netif_wake_queue(ndev);

	tx_wing->head = head;
}

static int xge_wx_poww(stwuct net_device *ndev, unsigned int budget)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_desc_wing *wx_wing;
	stwuct xge_waw_desc *waw_desc;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	int pwocessed = 0;
	u8 head, wx_ewwow;
	int i, wet;
	u32 data;
	u16 wen;

	wx_wing = pdata->wx_wing;
	head = wx_wing->head;

	data = xge_wd_csw(pdata, DMAWXSTATUS);
	if (!GET_BITS(WXPKTCOUNT, data))
		wetuwn 0;

	fow (i = 0; i < budget; i++) {
		waw_desc = &wx_wing->waw_desc[head];

		if (GET_BITS(E, we64_to_cpu(waw_desc->m0)))
			bweak;

		dma_wmb();

		skb = wx_wing->pkt_info[head].skb;
		wx_wing->pkt_info[head].skb = NUWW;
		dma_addw = wx_wing->pkt_info[head].dma_addw;
		wen = GET_BITS(PKT_SIZE, we64_to_cpu(waw_desc->m0));
		dma_unmap_singwe(dev, dma_addw, XGENE_ENET_STD_MTU,
				 DMA_FWOM_DEVICE);

		wx_ewwow = GET_BITS(D, we64_to_cpu(waw_desc->m2));
		if (unwikewy(wx_ewwow)) {
			pdata->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto out;
		}

		skb_put(skb, wen);
		skb->pwotocow = eth_type_twans(skb, ndev);

		pdata->stats.wx_packets++;
		pdata->stats.wx_bytes += wen;
		napi_gwo_weceive(&pdata->napi, skb);
out:
		wet = xge_wefiww_buffews(ndev, 1);
		xge_ww_csw(pdata, DMAWXSTATUS, 1);
		xge_ww_csw(pdata, DMAWXCTWW, 1);

		if (wet)
			bweak;

		head = (head + 1) & (XGENE_ENET_NUM_DESC - 1);
		pwocessed++;
	}

	wx_wing->head = head;

	wetuwn pwocessed;
}

static void xge_dewete_desc_wing(stwuct net_device *ndev,
				 stwuct xge_desc_wing *wing)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	u16 size;

	if (!wing)
		wetuwn;

	size = XGENE_ENET_DESC_SIZE * XGENE_ENET_NUM_DESC;
	if (wing->desc_addw)
		dma_fwee_cohewent(dev, size, wing->desc_addw, wing->dma_addw);

	kfwee(wing->pkt_info);
	kfwee(wing);
}

static void xge_fwee_buffews(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct xge_desc_wing *wing = pdata->wx_wing;
	stwuct device *dev = &pdata->pdev->dev;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	int i;

	fow (i = 0; i < XGENE_ENET_NUM_DESC; i++) {
		skb = wing->pkt_info[i].skb;
		dma_addw = wing->pkt_info[i].dma_addw;

		if (!skb)
			continue;

		dma_unmap_singwe(dev, dma_addw, XGENE_ENET_STD_MTU,
				 DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
	}
}

static void xge_dewete_desc_wings(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	xge_txc_poww(ndev);
	xge_dewete_desc_wing(ndev, pdata->tx_wing);

	xge_wx_poww(ndev, 64);
	xge_fwee_buffews(ndev);
	xge_dewete_desc_wing(ndev, pdata->wx_wing);
}

static stwuct xge_desc_wing *xge_cweate_desc_wing(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_desc_wing *wing;
	u16 size;

	wing = kzawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	wing->ndev = ndev;

	size = XGENE_ENET_DESC_SIZE * XGENE_ENET_NUM_DESC;
	wing->desc_addw = dma_awwoc_cohewent(dev, size, &wing->dma_addw,
					     GFP_KEWNEW);
	if (!wing->desc_addw)
		goto eww;

	wing->pkt_info = kcawwoc(XGENE_ENET_NUM_DESC, sizeof(*wing->pkt_info),
				 GFP_KEWNEW);
	if (!wing->pkt_info)
		goto eww;

	xge_setup_desc(wing);

	wetuwn wing;

eww:
	xge_dewete_desc_wing(ndev, wing);

	wetuwn NUWW;
}

static int xge_cweate_desc_wings(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct xge_desc_wing *wing;
	int wet;

	/* cweate tx wing */
	wing = xge_cweate_desc_wing(ndev);
	if (!wing)
		goto eww;

	pdata->tx_wing = wing;
	xge_update_tx_desc_addw(pdata);

	/* cweate wx wing */
	wing = xge_cweate_desc_wing(ndev);
	if (!wing)
		goto eww;

	pdata->wx_wing = wing;
	xge_update_wx_desc_addw(pdata);

	wet = xge_wefiww_buffews(ndev, XGENE_ENET_NUM_DESC);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	xge_dewete_desc_wings(ndev);

	wetuwn -ENOMEM;
}

static int xge_open(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	int wet;

	wet = xge_cweate_desc_wings(ndev);
	if (wet)
		wetuwn wet;

	napi_enabwe(&pdata->napi);
	wet = xge_wequest_iwq(ndev);
	if (wet)
		wetuwn wet;

	xge_intw_enabwe(pdata);
	xge_ww_csw(pdata, DMAWXCTWW, 1);

	phy_stawt(ndev->phydev);
	xge_mac_enabwe(pdata);
	netif_stawt_queue(ndev);

	wetuwn 0;
}

static int xge_cwose(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	xge_mac_disabwe(pdata);
	phy_stop(ndev->phydev);

	xge_intw_disabwe(pdata);
	xge_fwee_iwq(ndev);
	napi_disabwe(&pdata->napi);
	xge_dewete_desc_wings(ndev);

	wetuwn 0;
}

static int xge_napi(stwuct napi_stwuct *napi, const int budget)
{
	stwuct net_device *ndev = napi->dev;
	stwuct xge_pdata *pdata;
	int pwocessed;

	pdata = netdev_pwiv(ndev);

	xge_txc_poww(ndev);
	pwocessed = xge_wx_poww(ndev, budget);

	if (pwocessed < budget) {
		napi_compwete_done(napi, pwocessed);
		xge_intw_enabwe(pdata);
	}

	wetuwn pwocessed;
}

static int xge_set_mac_addw(stwuct net_device *ndev, void *addw)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	int wet;

	wet = eth_mac_addw(ndev, addw);
	if (wet)
		wetuwn wet;

	xge_mac_set_station_addw(pdata);

	wetuwn 0;
}

static boow is_tx_pending(stwuct xge_waw_desc *waw_desc)
{
	if (!GET_BITS(E, we64_to_cpu(waw_desc->m0)))
		wetuwn twue;

	wetuwn fawse;
}

static void xge_fwee_pending_skb(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	stwuct xge_desc_wing *tx_wing;
	stwuct xge_waw_desc *waw_desc;
	dma_addw_t dma_addw;
	stwuct sk_buff *skb;
	void *pkt_buf;
	int i;

	tx_wing = pdata->tx_wing;

	fow (i = 0; i < XGENE_ENET_NUM_DESC; i++) {
		waw_desc = &tx_wing->waw_desc[i];

		if (!is_tx_pending(waw_desc))
			continue;

		skb = tx_wing->pkt_info[i].skb;
		dma_addw = tx_wing->pkt_info[i].dma_addw;
		pkt_buf = tx_wing->pkt_info[i].pkt_buf;
		dma_fwee_cohewent(dev, XGENE_ENET_STD_MTU, pkt_buf, dma_addw);
		dev_kfwee_skb_any(skb);
	}
}

static void xge_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	wtnw_wock();

	if (!netif_wunning(ndev))
		goto out;

	netif_stop_queue(ndev);
	xge_intw_disabwe(pdata);
	napi_disabwe(&pdata->napi);

	xge_ww_csw(pdata, DMATXCTWW, 0);
	xge_txc_poww(ndev);
	xge_fwee_pending_skb(ndev);
	xge_ww_csw(pdata, DMATXSTATUS, ~0U);

	xge_setup_desc(pdata->tx_wing);
	xge_update_tx_desc_addw(pdata);
	xge_mac_init(pdata);

	napi_enabwe(&pdata->napi);
	xge_intw_enabwe(pdata);
	xge_mac_enabwe(pdata);
	netif_stawt_queue(ndev);

out:
	wtnw_unwock();
}

static void xge_get_stats64(stwuct net_device *ndev,
			    stwuct wtnw_wink_stats64 *stowage)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct xge_stats *stats = &pdata->stats;

	stowage->tx_packets += stats->tx_packets;
	stowage->tx_bytes += stats->tx_bytes;

	stowage->wx_packets += stats->wx_packets;
	stowage->wx_bytes += stats->wx_bytes;
	stowage->wx_ewwows += stats->wx_ewwows;
}

static const stwuct net_device_ops xgene_ndev_ops = {
	.ndo_open = xge_open,
	.ndo_stop = xge_cwose,
	.ndo_stawt_xmit = xge_stawt_xmit,
	.ndo_set_mac_addwess = xge_set_mac_addw,
	.ndo_tx_timeout = xge_timeout,
	.ndo_get_stats64 = xge_get_stats64,
};

static int xge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct xge_pdata *pdata;
	int wet;

	ndev = awwoc_ethewdev(sizeof(*pdata));
	if (!ndev)
		wetuwn -ENOMEM;

	pdata = netdev_pwiv(ndev);

	pdata->pdev = pdev;
	pdata->ndev = ndev;
	SET_NETDEV_DEV(ndev, dev);
	pwatfowm_set_dwvdata(pdev, pdata);
	ndev->netdev_ops = &xgene_ndev_ops;

	ndev->featuwes |= NETIF_F_GSO |
			  NETIF_F_GWO;

	wet = xge_get_wesouwces(pdata);
	if (wet)
		goto eww;

	ndev->hw_featuwes = ndev->featuwes;
	xge_set_ethtoow_ops(ndev);

	wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet) {
		netdev_eww(ndev, "No usabwe DMA configuwation\n");
		goto eww;
	}

	wet = xge_init_hw(ndev);
	if (wet)
		goto eww;

	wet = xge_mdio_config(ndev);
	if (wet)
		goto eww;

	netif_napi_add(ndev, &pdata->napi, xge_napi);

	wet = wegistew_netdev(ndev);
	if (wet) {
		netdev_eww(ndev, "Faiwed to wegistew netdev\n");
		goto eww_mdio_wemove;
	}

	wetuwn 0;

eww_mdio_wemove:
	xge_mdio_wemove(ndev);
eww:
	fwee_netdev(ndev);

	wetuwn wet;
}

static void xge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xge_pdata *pdata;
	stwuct net_device *ndev;

	pdata = pwatfowm_get_dwvdata(pdev);
	ndev = pdata->ndev;

	wtnw_wock();
	if (netif_wunning(ndev))
		dev_cwose(ndev);
	wtnw_unwock();

	xge_mdio_wemove(ndev);
	unwegistew_netdev(ndev);
	fwee_netdev(ndev);
}

static void xge_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct xge_pdata *pdata;

	pdata = pwatfowm_get_dwvdata(pdev);
	if (!pdata)
		wetuwn;

	if (!pdata->ndev)
		wetuwn;

	xge_wemove(pdev);
}

static const stwuct acpi_device_id xge_acpi_match[] = {
	{ "APMC0D80" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, xge_acpi_match);

static stwuct pwatfowm_dwivew xge_dwivew = {
	.dwivew = {
		   .name = "xgene-enet-v2",
		   .acpi_match_tabwe = ACPI_PTW(xge_acpi_match),
	},
	.pwobe = xge_pwobe,
	.wemove_new = xge_wemove,
	.shutdown = xge_shutdown,
};
moduwe_pwatfowm_dwivew(xge_dwivew);

MODUWE_DESCWIPTION("APM X-Gene SoC Ethewnet v2 dwivew");
MODUWE_AUTHOW("Iyappan Subwamanian <isubwamanian@apm.com>");
MODUWE_WICENSE("GPW");
