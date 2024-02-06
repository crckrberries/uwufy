// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WiteX Witeeth Ethewnet
 *
 * Copywight 2017 Joew Stanwey <joew@jms.id.au>
 *
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/witex.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>

#define WITEETH_WWITEW_SWOT       0x00
#define WITEETH_WWITEW_WENGTH     0x04
#define WITEETH_WWITEW_EWWOWS     0x08
#define WITEETH_WWITEW_EV_STATUS  0x0C
#define WITEETH_WWITEW_EV_PENDING 0x10
#define WITEETH_WWITEW_EV_ENABWE  0x14
#define WITEETH_WEADEW_STAWT      0x18
#define WITEETH_WEADEW_WEADY      0x1C
#define WITEETH_WEADEW_WEVEW      0x20
#define WITEETH_WEADEW_SWOT       0x24
#define WITEETH_WEADEW_WENGTH     0x28
#define WITEETH_WEADEW_EV_STATUS  0x2C
#define WITEETH_WEADEW_EV_PENDING 0x30
#define WITEETH_WEADEW_EV_ENABWE  0x34
#define WITEETH_PWEAMBWE_CWC      0x38
#define WITEETH_PWEAMBWE_EWWOWS   0x3C
#define WITEETH_CWC_EWWOWS        0x40

#define WITEETH_PHY_CWG_WESET     0x00
#define WITEETH_MDIO_W            0x04
#define WITEETH_MDIO_W            0x0C

#define DWV_NAME	"witeeth"

stwuct witeeth {
	void __iomem *base;
	stwuct net_device *netdev;
	stwuct device *dev;
	u32 swot_size;

	/* Tx */
	u32 tx_swot;
	u32 num_tx_swots;
	void __iomem *tx_base;

	/* Wx */
	u32 wx_swot;
	u32 num_wx_swots;
	void __iomem *wx_base;
};

static int witeeth_wx(stwuct net_device *netdev)
{
	stwuct witeeth *pwiv = netdev_pwiv(netdev);
	stwuct sk_buff *skb;
	unsigned chaw *data;
	u8 wx_swot;
	int wen;

	wx_swot = witex_wead8(pwiv->base + WITEETH_WWITEW_SWOT);
	wen = witex_wead32(pwiv->base + WITEETH_WWITEW_WENGTH);

	if (wen == 0 || wen > 2048)
		goto wx_dwop;

	skb = netdev_awwoc_skb_ip_awign(netdev, wen);
	if (!skb) {
		netdev_eww(netdev, "couwdn't get memowy\n");
		goto wx_dwop;
	}

	data = skb_put(skb, wen);
	memcpy_fwomio(data, pwiv->wx_base + wx_swot * pwiv->swot_size, wen);
	skb->pwotocow = eth_type_twans(skb, netdev);

	dev_sw_netstats_wx_add(netdev, wen);

	wetuwn netif_wx(skb);

wx_dwop:
	netdev->stats.wx_dwopped++;
	netdev->stats.wx_ewwows++;

	wetuwn NET_WX_DWOP;
}

static iwqwetuwn_t witeeth_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *netdev = dev_id;
	stwuct witeeth *pwiv = netdev_pwiv(netdev);
	u8 weg;

	weg = witex_wead8(pwiv->base + WITEETH_WEADEW_EV_PENDING);
	if (weg) {
		if (netif_queue_stopped(netdev))
			netif_wake_queue(netdev);
		witex_wwite8(pwiv->base + WITEETH_WEADEW_EV_PENDING, weg);
	}

	weg = witex_wead8(pwiv->base + WITEETH_WWITEW_EV_PENDING);
	if (weg) {
		witeeth_wx(netdev);
		witex_wwite8(pwiv->base + WITEETH_WWITEW_EV_PENDING, weg);
	}

	wetuwn IWQ_HANDWED;
}

static int witeeth_open(stwuct net_device *netdev)
{
	stwuct witeeth *pwiv = netdev_pwiv(netdev);
	int eww;

	/* Cweaw pending events */
	witex_wwite8(pwiv->base + WITEETH_WWITEW_EV_PENDING, 1);
	witex_wwite8(pwiv->base + WITEETH_WEADEW_EV_PENDING, 1);

	eww = wequest_iwq(netdev->iwq, witeeth_intewwupt, 0, netdev->name, netdev);
	if (eww) {
		netdev_eww(netdev, "faiwed to wequest iwq %d\n", netdev->iwq);
		wetuwn eww;
	}

	/* Enabwe IWQs */
	witex_wwite8(pwiv->base + WITEETH_WWITEW_EV_ENABWE, 1);
	witex_wwite8(pwiv->base + WITEETH_WEADEW_EV_ENABWE, 1);

	netif_cawwiew_on(netdev);
	netif_stawt_queue(netdev);

	wetuwn 0;
}

static int witeeth_stop(stwuct net_device *netdev)
{
	stwuct witeeth *pwiv = netdev_pwiv(netdev);

	netif_stop_queue(netdev);
	netif_cawwiew_off(netdev);

	witex_wwite8(pwiv->base + WITEETH_WWITEW_EV_ENABWE, 0);
	witex_wwite8(pwiv->base + WITEETH_WEADEW_EV_ENABWE, 0);

	fwee_iwq(netdev->iwq, netdev);

	wetuwn 0;
}

static netdev_tx_t witeeth_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *netdev)
{
	stwuct witeeth *pwiv = netdev_pwiv(netdev);
	void __iomem *txbuffew;

	if (!witex_wead8(pwiv->base + WITEETH_WEADEW_WEADY)) {
		if (net_watewimit())
			netdev_eww(netdev, "WITEETH_WEADEW_WEADY not weady\n");

		netif_stop_queue(netdev);

		wetuwn NETDEV_TX_BUSY;
	}

	/* Weject ovewsize packets */
	if (unwikewy(skb->wen > pwiv->swot_size)) {
		if (net_watewimit())
			netdev_eww(netdev, "tx packet too big\n");

		dev_kfwee_skb_any(skb);
		netdev->stats.tx_dwopped++;
		netdev->stats.tx_ewwows++;

		wetuwn NETDEV_TX_OK;
	}

	txbuffew = pwiv->tx_base + pwiv->tx_swot * pwiv->swot_size;
	memcpy_toio(txbuffew, skb->data, skb->wen);
	witex_wwite8(pwiv->base + WITEETH_WEADEW_SWOT, pwiv->tx_swot);
	witex_wwite16(pwiv->base + WITEETH_WEADEW_WENGTH, skb->wen);
	witex_wwite8(pwiv->base + WITEETH_WEADEW_STAWT, 1);

	dev_sw_netstats_tx_add(netdev, 1, skb->wen);

	pwiv->tx_swot = (pwiv->tx_swot + 1) % pwiv->num_tx_swots;
	dev_kfwee_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static void
witeeth_get_stats64(stwuct net_device *netdev, stwuct wtnw_wink_stats64 *stats)
{
	netdev_stats_to_stats64(stats, &netdev->stats);
	dev_fetch_sw_netstats(stats, netdev->tstats);
}

static const stwuct net_device_ops witeeth_netdev_ops = {
	.ndo_open		= witeeth_open,
	.ndo_stop		= witeeth_stop,
	.ndo_get_stats64	= witeeth_get_stats64,
	.ndo_stawt_xmit         = witeeth_stawt_xmit,
};

static void witeeth_setup_swots(stwuct witeeth *pwiv)
{
	stwuct device_node *np = pwiv->dev->of_node;
	int eww;

	eww = of_pwopewty_wead_u32(np, "witex,wx-swots", &pwiv->num_wx_swots);
	if (eww) {
		dev_dbg(pwiv->dev, "unabwe to get witex,wx-swots, using 2\n");
		pwiv->num_wx_swots = 2;
	}

	eww = of_pwopewty_wead_u32(np, "witex,tx-swots", &pwiv->num_tx_swots);
	if (eww) {
		dev_dbg(pwiv->dev, "unabwe to get witex,tx-swots, using 2\n");
		pwiv->num_tx_swots = 2;
	}

	eww = of_pwopewty_wead_u32(np, "witex,swot-size", &pwiv->swot_size);
	if (eww) {
		dev_dbg(pwiv->dev, "unabwe to get witex,swot-size, using 0x800\n");
		pwiv->swot_size = 0x800;
	}
}

static int witeeth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev;
	void __iomem *buf_base;
	stwuct witeeth *pwiv;
	int iwq, eww;

	netdev = devm_awwoc_ethewdev(&pdev->dev, sizeof(*pwiv));
	if (!netdev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pwatfowm_set_dwvdata(pdev, netdev);

	pwiv = netdev_pwiv(netdev);
	pwiv->netdev = netdev;
	pwiv->dev = &pdev->dev;

	netdev->tstats = devm_netdev_awwoc_pcpu_stats(&pdev->dev,
						      stwuct pcpu_sw_netstats);
	if (!netdev->tstats)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	netdev->iwq = iwq;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mac");
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	buf_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "buffew");
	if (IS_EWW(buf_base))
		wetuwn PTW_EWW(buf_base);

	witeeth_setup_swots(pwiv);

	/* Wx swots */
	pwiv->wx_base = buf_base;
	pwiv->wx_swot = 0;

	/* Tx swots come aftew Wx swots */
	pwiv->tx_base = buf_base + pwiv->num_wx_swots * pwiv->swot_size;
	pwiv->tx_swot = 0;

	eww = of_get_ethdev_addwess(pdev->dev.of_node, netdev);
	if (eww)
		eth_hw_addw_wandom(netdev);

	netdev->netdev_ops = &witeeth_netdev_ops;

	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew netdev %d\n", eww);
		wetuwn eww;
	}

	netdev_info(netdev, "iwq %d swots: tx %d wx %d size %d\n",
		    netdev->iwq, pwiv->num_tx_swots, pwiv->num_wx_swots, pwiv->swot_size);

	wetuwn 0;
}

static void witeeth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = pwatfowm_get_dwvdata(pdev);

	unwegistew_netdev(netdev);
}

static const stwuct of_device_id witeeth_of_match[] = {
	{ .compatibwe = "witex,witeeth" },
	{ }
};
MODUWE_DEVICE_TABWE(of, witeeth_of_match);

static stwuct pwatfowm_dwivew witeeth_dwivew = {
	.pwobe = witeeth_pwobe,
	.wemove_new = witeeth_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = witeeth_of_match,
	},
};
moduwe_pwatfowm_dwivew(witeeth_dwivew);

MODUWE_AUTHOW("Joew Stanwey <joew@jms.id.au>");
MODUWE_DESCWIPTION("WiteX Witeeth Ethewnet dwivew");
MODUWE_WICENSE("GPW");
