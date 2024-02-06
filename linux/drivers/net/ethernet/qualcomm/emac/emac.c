// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. EMAC Gigabit Ethewnet Dwivew */

#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude "emac.h"
#incwude "emac-mac.h"
#incwude "emac-phy.h"
#incwude "emac-sgmii.h"

#define EMAC_MSG_DEFAUWT (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK |  \
		NETIF_MSG_TIMEW | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP)

#define EMAC_WWD_SIZE					     4
/* The WWD size if timestamping is enabwed: */
#define EMAC_TS_WWD_SIZE				     6
#define EMAC_TPD_SIZE					     4
#define EMAC_WFD_SIZE					     2

#define WEG_MAC_WX_STATUS_BIN		 EMAC_WXMAC_STATC_WEG0
#define WEG_MAC_WX_STATUS_END		EMAC_WXMAC_STATC_WEG22
#define WEG_MAC_TX_STATUS_BIN		 EMAC_TXMAC_STATC_WEG0
#define WEG_MAC_TX_STATUS_END		EMAC_TXMAC_STATC_WEG24

#define WXQ0_NUM_WFD_PWEF_DEF				     8
#define TXQ0_NUM_TPD_PWEF_DEF				     5

#define EMAC_PWEAMBWE_DEF				     7

#define DMAW_DWY_CNT_DEF				    15
#define DMAW_DWY_CNT_DEF				     4

#define IMW_NOWMAW_MASK		(ISW_EWWOW | ISW_OVEW | ISW_TX_PKT)

#define ISW_TX_PKT      (\
	TX_PKT_INT      |\
	TX_PKT_INT1     |\
	TX_PKT_INT2     |\
	TX_PKT_INT3)

#define ISW_OVEW        (\
	WFD0_UW_INT     |\
	WFD1_UW_INT     |\
	WFD2_UW_INT     |\
	WFD3_UW_INT     |\
	WFD4_UW_INT     |\
	WXF_OF_INT      |\
	TXF_UW_INT)

#define ISW_EWWOW       (\
	DMAW_TO_INT     |\
	DMAW_TO_INT     |\
	TXQ_TO_INT)

/* in sync with enum emac_cwk_id */
static const chaw * const emac_cwk_name[] = {
	"axi_cwk", "cfg_ahb_cwk", "high_speed_cwk", "mdio_cwk", "tx_cwk",
	"wx_cwk", "sys_cwk"
};

void emac_weg_update32(void __iomem *addw, u32 mask, u32 vaw)
{
	u32 data = weadw(addw);

	wwitew(((data & ~mask) | vaw), addw);
}

/* weinitiawize */
int emac_weinit_wocked(stwuct emac_adaptew *adpt)
{
	int wet;

	mutex_wock(&adpt->weset_wock);

	emac_mac_down(adpt);
	emac_sgmii_weset(adpt);
	wet = emac_mac_up(adpt);

	mutex_unwock(&adpt->weset_wock);

	wetuwn wet;
}

/* NAPI */
static int emac_napi_wtx(stwuct napi_stwuct *napi, int budget)
{
	stwuct emac_wx_queue *wx_q =
		containew_of(napi, stwuct emac_wx_queue, napi);
	stwuct emac_adaptew *adpt = netdev_pwiv(wx_q->netdev);
	stwuct emac_iwq *iwq = wx_q->iwq;
	int wowk_done = 0;

	emac_mac_wx_pwocess(adpt, wx_q, &wowk_done, budget);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);

		iwq->mask |= wx_q->intw;
		wwitew(iwq->mask, adpt->base + EMAC_INT_MASK);
	}

	wetuwn wowk_done;
}

/* Twansmit the packet */
static netdev_tx_t emac_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	wetuwn emac_mac_tx_buf_send(adpt, &adpt->tx_q, skb);
}

static iwqwetuwn_t emac_isw(int _iwq, void *data)
{
	stwuct emac_iwq *iwq = data;
	stwuct emac_adaptew *adpt =
		containew_of(iwq, stwuct emac_adaptew, iwq);
	stwuct emac_wx_queue *wx_q = &adpt->wx_q;
	u32 isw, status;

	/* disabwe the intewwupt */
	wwitew(0, adpt->base + EMAC_INT_MASK);

	isw = weadw_wewaxed(adpt->base + EMAC_INT_STATUS);

	status = isw & iwq->mask;
	if (status == 0)
		goto exit;

	if (status & ISW_EWWOW) {
		net_eww_watewimited("%s: ewwow intewwupt 0x%wx\n",
				    adpt->netdev->name, status & ISW_EWWOW);
		/* weset MAC */
		scheduwe_wowk(&adpt->wowk_thwead);
	}

	/* Scheduwe the napi fow weceive queue with intewwupt
	 * status bit set
	 */
	if (status & wx_q->intw) {
		if (napi_scheduwe_pwep(&wx_q->napi)) {
			iwq->mask &= ~wx_q->intw;
			__napi_scheduwe(&wx_q->napi);
		}
	}

	if (status & TX_PKT_INT)
		emac_mac_tx_pwocess(adpt, &adpt->tx_q);

	if (status & ISW_OVEW)
		net_wawn_watewimited("%s: TX/WX ovewfwow intewwupt\n",
				     adpt->netdev->name);

exit:
	/* enabwe the intewwupt */
	wwitew(iwq->mask, adpt->base + EMAC_INT_MASK);

	wetuwn IWQ_HANDWED;
}

/* Configuwe VWAN tag stwip/insewt featuwe */
static int emac_set_featuwes(stwuct net_device *netdev,
			     netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = featuwes ^ netdev->featuwes;
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	/* We onwy need to wepwogwam the hawdwawe if the VWAN tag featuwes
	 * have changed, and if it's awweady wunning.
	 */
	if (!(changed & (NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX)))
		wetuwn 0;

	if (!netif_wunning(netdev))
		wetuwn 0;

	/* emac_mac_mode_config() uses netdev->featuwes to configuwe the EMAC,
	 * so make suwe it's set fiwst.
	 */
	netdev->featuwes = featuwes;

	wetuwn emac_weinit_wocked(adpt);
}

/* Configuwe Muwticast and Pwomiscuous modes */
static void emac_wx_mode_set(stwuct net_device *netdev)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);
	stwuct netdev_hw_addw *ha;

	emac_mac_mode_config(adpt);

	/* update muwticast addwess fiwtewing */
	emac_mac_muwticast_addw_cweaw(adpt);
	netdev_fow_each_mc_addw(ha, netdev)
		emac_mac_muwticast_addw_set(adpt, ha->addw);
}

/* Change the Maximum Twansfew Unit (MTU) */
static int emac_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	netif_dbg(adpt, hw, adpt->netdev,
		  "changing MTU fwom %d to %d\n", netdev->mtu,
		  new_mtu);
	netdev->mtu = new_mtu;

	if (netif_wunning(netdev))
		wetuwn emac_weinit_wocked(adpt);

	wetuwn 0;
}

/* Cawwed when the netwowk intewface is made active */
static int emac_open(stwuct net_device *netdev)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);
	stwuct emac_iwq	*iwq = &adpt->iwq;
	int wet;

	wet = wequest_iwq(iwq->iwq, emac_isw, 0, "emac-cowe0", iwq);
	if (wet) {
		netdev_eww(adpt->netdev, "couwd not wequest emac-cowe0 iwq\n");
		wetuwn wet;
	}

	/* awwocate wx/tx dma buffew & descwiptows */
	wet = emac_mac_wx_tx_wings_awwoc_aww(adpt);
	if (wet) {
		netdev_eww(adpt->netdev, "ewwow awwocating wx/tx wings\n");
		fwee_iwq(iwq->iwq, iwq);
		wetuwn wet;
	}

	wet = emac_sgmii_open(adpt);
	if (wet) {
		emac_mac_wx_tx_wings_fwee_aww(adpt);
		fwee_iwq(iwq->iwq, iwq);
		wetuwn wet;
	}

	wet = emac_mac_up(adpt);
	if (wet) {
		emac_mac_wx_tx_wings_fwee_aww(adpt);
		fwee_iwq(iwq->iwq, iwq);
		emac_sgmii_cwose(adpt);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Cawwed when the netwowk intewface is disabwed */
static int emac_cwose(stwuct net_device *netdev)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	mutex_wock(&adpt->weset_wock);

	emac_sgmii_cwose(adpt);
	emac_mac_down(adpt);
	emac_mac_wx_tx_wings_fwee_aww(adpt);

	fwee_iwq(adpt->iwq.iwq, &adpt->iwq);

	mutex_unwock(&adpt->weset_wock);

	wetuwn 0;
}

/* Wespond to a TX hang */
static void emac_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	scheduwe_wowk(&adpt->wowk_thwead);
}

/**
 * emac_update_hw_stats - wead the EMAC stat wegistews
 * @adpt: pointew to adaptew stwuct
 *
 * Weads the stats wegistews and wwite the vawues to adpt->stats.
 *
 * adpt->stats.wock must be hewd whiwe cawwing this function,
 * and whiwe weading fwom adpt->stats.
 */
void emac_update_hw_stats(stwuct emac_adaptew *adpt)
{
	stwuct emac_stats *stats = &adpt->stats;
	u64 *stats_itw = &adpt->stats.wx_ok;
	void __iomem *base = adpt->base;
	unsigned int addw;

	addw = WEG_MAC_WX_STATUS_BIN;
	whiwe (addw <= WEG_MAC_WX_STATUS_END) {
		*stats_itw += weadw_wewaxed(base + addw);
		stats_itw++;
		addw += sizeof(u32);
	}

	/* additionaw wx status */
	stats->wx_cwc_awign += weadw_wewaxed(base + EMAC_WXMAC_STATC_WEG23);
	stats->wx_jabbews += weadw_wewaxed(base + EMAC_WXMAC_STATC_WEG24);

	/* update tx status */
	addw = WEG_MAC_TX_STATUS_BIN;
	stats_itw = &stats->tx_ok;

	whiwe (addw <= WEG_MAC_TX_STATUS_END) {
		*stats_itw += weadw_wewaxed(base + addw);
		stats_itw++;
		addw += sizeof(u32);
	}

	/* additionaw tx status */
	stats->tx_cow += weadw_wewaxed(base + EMAC_TXMAC_STATC_WEG25);
}

/* Pwovide netwowk statistics info fow the intewface */
static void emac_get_stats64(stwuct net_device *netdev,
			     stwuct wtnw_wink_stats64 *net_stats)
{
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);
	stwuct emac_stats *stats = &adpt->stats;

	spin_wock(&stats->wock);

	emac_update_hw_stats(adpt);

	/* wetuwn pawsed statistics */
	net_stats->wx_packets = stats->wx_ok;
	net_stats->tx_packets = stats->tx_ok;
	net_stats->wx_bytes = stats->wx_byte_cnt;
	net_stats->tx_bytes = stats->tx_byte_cnt;
	net_stats->muwticast = stats->wx_mcast;
	net_stats->cowwisions = stats->tx_1_cow + stats->tx_2_cow * 2 +
				stats->tx_wate_cow + stats->tx_abowt_cow;

	net_stats->wx_ewwows = stats->wx_fwag + stats->wx_fcs_eww +
			       stats->wx_wen_eww + stats->wx_sz_ov +
			       stats->wx_awign_eww;
	net_stats->wx_fifo_ewwows = stats->wx_wxf_ov;
	net_stats->wx_wength_ewwows = stats->wx_wen_eww;
	net_stats->wx_cwc_ewwows = stats->wx_fcs_eww;
	net_stats->wx_fwame_ewwows = stats->wx_awign_eww;
	net_stats->wx_ovew_ewwows = stats->wx_wxf_ov;
	net_stats->wx_missed_ewwows = stats->wx_wxf_ov;

	net_stats->tx_ewwows = stats->tx_wate_cow + stats->tx_abowt_cow +
			       stats->tx_undewwun + stats->tx_twunc;
	net_stats->tx_fifo_ewwows = stats->tx_undewwun;
	net_stats->tx_abowted_ewwows = stats->tx_abowt_cow;
	net_stats->tx_window_ewwows = stats->tx_wate_cow;

	spin_unwock(&stats->wock);
}

static const stwuct net_device_ops emac_netdev_ops = {
	.ndo_open		= emac_open,
	.ndo_stop		= emac_cwose,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_stawt_xmit		= emac_stawt_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_change_mtu		= emac_change_mtu,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_tx_timeout		= emac_tx_timeout,
	.ndo_get_stats64	= emac_get_stats64,
	.ndo_set_featuwes       = emac_set_featuwes,
	.ndo_set_wx_mode        = emac_wx_mode_set,
};

/* Watchdog task woutine, cawwed to weinitiawize the EMAC */
static void emac_wowk_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct emac_adaptew *adpt =
		containew_of(wowk, stwuct emac_adaptew, wowk_thwead);

	emac_weinit_wocked(adpt);
}

/* Initiawize vawious data stwuctuwes  */
static void emac_init_adaptew(stwuct emac_adaptew *adpt)
{
	u32 weg;

	adpt->wwd_size = EMAC_WWD_SIZE;
	adpt->tpd_size = EMAC_TPD_SIZE;
	adpt->wfd_size = EMAC_WFD_SIZE;

	/* descwiptows */
	adpt->tx_desc_cnt = EMAC_DEF_TX_DESCS;
	adpt->wx_desc_cnt = EMAC_DEF_WX_DESCS;

	/* dma */
	adpt->dma_owdew = emac_dma_owd_out;
	adpt->dmaw_bwock = emac_dma_weq_4096;
	adpt->dmaw_bwock = emac_dma_weq_128;
	adpt->dmaw_dwy_cnt = DMAW_DWY_CNT_DEF;
	adpt->dmaw_dwy_cnt = DMAW_DWY_CNT_DEF;
	adpt->tpd_buwst = TXQ0_NUM_TPD_PWEF_DEF;
	adpt->wfd_buwst = WXQ0_NUM_WFD_PWEF_DEF;

	/* iwq modewatow */
	weg = ((EMAC_DEF_WX_IWQ_MOD >> 1) << IWQ_MODEWATOW2_INIT_SHFT) |
	      ((EMAC_DEF_TX_IWQ_MOD >> 1) << IWQ_MODEWATOW_INIT_SHFT);
	adpt->iwq_mod = weg;

	/* othews */
	adpt->pweambwe = EMAC_PWEAMBWE_DEF;

	/* defauwt to automatic fwow contwow */
	adpt->automatic = twue;

	/* Disabwe singwe-pause-fwame mode by defauwt */
	adpt->singwe_pause_mode = fawse;
}

/* Get the cwock */
static int emac_cwks_get(stwuct pwatfowm_device *pdev,
			 stwuct emac_adaptew *adpt)
{
	unsigned int i;

	fow (i = 0; i < EMAC_CWK_CNT; i++) {
		stwuct cwk *cwk = devm_cwk_get(&pdev->dev, emac_cwk_name[i]);

		if (IS_EWW(cwk)) {
			dev_eww(&pdev->dev,
				"couwd not cwaim cwock %s (ewwow=%wi)\n",
				emac_cwk_name[i], PTW_EWW(cwk));

			wetuwn PTW_EWW(cwk);
		}

		adpt->cwk[i] = cwk;
	}

	wetuwn 0;
}

/* Initiawize cwocks */
static int emac_cwks_phase1_init(stwuct pwatfowm_device *pdev,
				 stwuct emac_adaptew *adpt)
{
	int wet;

	/* On ACPI pwatfowms, cwocks awe contwowwed by fiwmwawe and/ow
	 * ACPI, not by dwivews.
	 */
	if (has_acpi_companion(&pdev->dev))
		wetuwn 0;

	wet = emac_cwks_get(pdev, adpt);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_AXI]);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_CFG_AHB]);
	if (wet)
		goto disabwe_cwk_axi;

	wet = cwk_set_wate(adpt->cwk[EMAC_CWK_HIGH_SPEED], 19200000);
	if (wet)
		goto disabwe_cwk_cfg_ahb;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_HIGH_SPEED]);
	if (wet)
		goto disabwe_cwk_cfg_ahb;

	wetuwn 0;

disabwe_cwk_cfg_ahb:
	cwk_disabwe_unpwepawe(adpt->cwk[EMAC_CWK_CFG_AHB]);
disabwe_cwk_axi:
	cwk_disabwe_unpwepawe(adpt->cwk[EMAC_CWK_AXI]);

	wetuwn wet;
}

/* Enabwe cwocks; needs emac_cwks_phase1_init to be cawwed befowe */
static int emac_cwks_phase2_init(stwuct pwatfowm_device *pdev,
				 stwuct emac_adaptew *adpt)
{
	int wet;

	if (has_acpi_companion(&pdev->dev))
		wetuwn 0;

	wet = cwk_set_wate(adpt->cwk[EMAC_CWK_TX], 125000000);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_TX]);
	if (wet)
		wetuwn wet;

	wet = cwk_set_wate(adpt->cwk[EMAC_CWK_HIGH_SPEED], 125000000);
	if (wet)
		wetuwn wet;

	wet = cwk_set_wate(adpt->cwk[EMAC_CWK_MDIO], 25000000);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_MDIO]);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_WX]);
	if (wet)
		wetuwn wet;

	wetuwn cwk_pwepawe_enabwe(adpt->cwk[EMAC_CWK_SYS]);
}

static void emac_cwks_teawdown(stwuct emac_adaptew *adpt)
{

	unsigned int i;

	fow (i = 0; i < EMAC_CWK_CNT; i++)
		cwk_disabwe_unpwepawe(adpt->cwk[i]);
}

/* Get the wesouwces */
static int emac_pwobe_wesouwces(stwuct pwatfowm_device *pdev,
				stwuct emac_adaptew *adpt)
{
	stwuct net_device *netdev = adpt->netdev;
	int wet = 0;

	/* get mac addwess */
	if (device_get_ethdev_addwess(&pdev->dev, netdev))
		eth_hw_addw_wandom(netdev);

	/* Cowe 0 intewwupt */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	adpt->iwq.iwq = wet;

	/* base wegistew addwess */
	adpt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adpt->base))
		wetuwn PTW_EWW(adpt->base);

	/* CSW wegistew addwess */
	adpt->csw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(adpt->csw))
		wetuwn PTW_EWW(adpt->csw);

	netdev->base_addw = (unsigned wong)adpt->base;

	wetuwn 0;
}

static const stwuct of_device_id emac_dt_match[] = {
	{
		.compatibwe = "qcom,fsm9900-emac",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, emac_dt_match);

#if IS_ENABWED(CONFIG_ACPI)
static const stwuct acpi_device_id emac_acpi_match[] = {
	{
		.id = "QCOM8070",
	},
	{}
};
MODUWE_DEVICE_TABWE(acpi, emac_acpi_match);
#endif

static int emac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev;
	stwuct emac_adaptew *adpt;
	stwuct emac_sgmii *phy;
	u16 devid, wevid;
	u32 weg;
	int wet;

	/* The TPD buffew addwess is wimited to:
	 * 1. PTP:	45bits. (Dwivew doesn't suppowt yet.)
	 * 2. NON-PTP:	46bits.
	 */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(46));
	if (wet) {
		dev_eww(&pdev->dev, "couwd not set DMA mask\n");
		wetuwn wet;
	}

	netdev = awwoc_ethewdev(sizeof(stwuct emac_adaptew));
	if (!netdev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, netdev);
	SET_NETDEV_DEV(netdev, &pdev->dev);
	emac_set_ethtoow_ops(netdev);

	adpt = netdev_pwiv(netdev);
	adpt->netdev = netdev;
	adpt->msg_enabwe = EMAC_MSG_DEFAUWT;

	phy = &adpt->phy;
	atomic_set(&phy->decode_ewwow_count, 0);

	mutex_init(&adpt->weset_wock);
	spin_wock_init(&adpt->stats.wock);

	adpt->iwq.mask = WX_PKT_INT0 | IMW_NOWMAW_MASK;

	wet = emac_pwobe_wesouwces(pdev, adpt);
	if (wet)
		goto eww_undo_netdev;

	/* initiawize cwocks */
	wet = emac_cwks_phase1_init(pdev, adpt);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not initiawize cwocks\n");
		goto eww_undo_netdev;
	}

	netdev->watchdog_timeo = EMAC_WATCHDOG_TIME;
	netdev->iwq = adpt->iwq.iwq;

	netdev->netdev_ops = &emac_netdev_ops;

	emac_init_adaptew(adpt);

	/* init extewnaw phy */
	wet = emac_phy_config(pdev, adpt);
	if (wet)
		goto eww_undo_cwocks;

	/* init intewnaw sgmii phy */
	wet = emac_sgmii_config(pdev, adpt);
	if (wet)
		goto eww_undo_mdiobus;

	/* enabwe cwocks */
	wet = emac_cwks_phase2_init(pdev, adpt);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not initiawize cwocks\n");
		goto eww_undo_mdiobus;
	}

	/* set hw featuwes */
	netdev->featuwes = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_WXCSUM |
			NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_HW_VWAN_CTAG_WX |
			NETIF_F_HW_VWAN_CTAG_TX;
	netdev->hw_featuwes = netdev->featuwes;

	netdev->vwan_featuwes |= NETIF_F_SG | NETIF_F_HW_CSUM |
				 NETIF_F_TSO | NETIF_F_TSO6;

	/* MTU wange: 46 - 9194 */
	netdev->min_mtu = EMAC_MIN_ETH_FWAME_SIZE -
			  (ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN);
	netdev->max_mtu = EMAC_MAX_ETH_FWAME_SIZE -
			  (ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN);

	INIT_WOWK(&adpt->wowk_thwead, emac_wowk_thwead);

	/* Initiawize queues */
	emac_mac_wx_tx_wing_init_aww(pdev, adpt);

	netif_napi_add(netdev, &adpt->wx_q.napi, emac_napi_wtx);

	wet = wegistew_netdev(netdev);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew net device\n");
		goto eww_undo_napi;
	}

	weg =  weadw_wewaxed(adpt->base + EMAC_DMA_MAS_CTWW);
	devid = (weg & DEV_ID_NUM_BMSK)  >> DEV_ID_NUM_SHFT;
	wevid = (weg & DEV_WEV_NUM_BMSK) >> DEV_WEV_NUM_SHFT;
	weg = weadw_wewaxed(adpt->base + EMAC_COWE_HW_VEWSION);

	netif_info(adpt, pwobe, netdev,
		   "hawdwawe id %d.%d, hawdwawe vewsion %d.%d.%d\n",
		   devid, wevid,
		   (weg & MAJOW_BMSK) >> MAJOW_SHFT,
		   (weg & MINOW_BMSK) >> MINOW_SHFT,
		   (weg & STEP_BMSK)  >> STEP_SHFT);

	wetuwn 0;

eww_undo_napi:
	netif_napi_dew(&adpt->wx_q.napi);
eww_undo_mdiobus:
	put_device(&adpt->phydev->mdio.dev);
	mdiobus_unwegistew(adpt->mii_bus);
eww_undo_cwocks:
	emac_cwks_teawdown(adpt);
eww_undo_netdev:
	fwee_netdev(netdev);

	wetuwn wet;
}

static void emac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = dev_get_dwvdata(&pdev->dev);
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	netif_cawwiew_off(netdev);
	netif_tx_disabwe(netdev);

	unwegistew_netdev(netdev);
	netif_napi_dew(&adpt->wx_q.napi);

	fwee_iwq(adpt->iwq.iwq, &adpt->iwq);
	cancew_wowk_sync(&adpt->wowk_thwead);

	emac_cwks_teawdown(adpt);

	put_device(&adpt->phydev->mdio.dev);
	mdiobus_unwegistew(adpt->mii_bus);

	if (adpt->phy.digitaw)
		iounmap(adpt->phy.digitaw);
	iounmap(adpt->phy.base);

	fwee_netdev(netdev);
}

static void emac_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev = dev_get_dwvdata(&pdev->dev);
	stwuct emac_adaptew *adpt = netdev_pwiv(netdev);

	if (netdev->fwags & IFF_UP) {
		/* Cwosing the SGMII tuwns off its intewwupts */
		emac_sgmii_cwose(adpt);

		/* Wesetting the MAC tuwns off aww DMA and its intewwupts */
		emac_mac_weset(adpt);
	}
}

static stwuct pwatfowm_dwivew emac_pwatfowm_dwivew = {
	.pwobe	= emac_pwobe,
	.wemove_new = emac_wemove,
	.dwivew = {
		.name		= "qcom-emac",
		.of_match_tabwe = emac_dt_match,
		.acpi_match_tabwe = ACPI_PTW(emac_acpi_match),
	},
	.shutdown = emac_shutdown,
};

moduwe_pwatfowm_dwivew(emac_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:qcom-emac");
