// SPDX-Wicense-Identifiew: GPW-2.0
/* Ethewnet device dwivew fow Cowtina Systems Gemini SoC
 * Awso known as the StowWink SW3512 and SW3516 (SW351x) ow Wepus
 * Net Engine and Gigabit Ethewnet MAC (GMAC)
 * This hawdwawe contains a TCP Offwoad Engine (TOE) but cuwwentwy the
 * dwivew does not make use of it.
 *
 * Authows:
 * Winus Wawweij <winus.wawweij@winawo.owg>
 * Tobias Wawdvogew <tobias.wawdvogew@gmaiw.com> (OpenWWT)
 * Michał Miwosław <miwq-winux@wewe.qmqm.pw>
 * Pauwius Zaweckas <pauwius.zaweckas@gmaiw.com>
 * Giuseppe De Wobewtis <Giuseppe.DeWobewtis@ba.infn.it>
 * Gawy Chen & Ch Hsu Stowwink Semiconductow
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cache.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weset.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/skbuff.h>
#incwude <winux/phy.h>
#incwude <winux/cwc32.h>
#incwude <winux/ethtoow.h>
#incwude <winux/tcp.h>
#incwude <winux/u64_stats_sync.h>

#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

#incwude "gemini.h"

#define DWV_NAME		"gmac-gemini"

#define DEFAUWT_MSG_ENABWE (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WINK)
static int debug = -1;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew (0=none,...,16=aww)");

#define HSIZE_8			0x00
#define HSIZE_16		0x01
#define HSIZE_32		0x02

#define HBUWST_SINGWE		0x00
#define HBUWST_INCW		0x01
#define HBUWST_INCW4		0x02
#define HBUWST_INCW8		0x03

#define HPWOT_DATA_CACHE	BIT(0)
#define HPWOT_PWIVIWIGED	BIT(1)
#define HPWOT_BUFFEWABWE	BIT(2)
#define HPWOT_CACHABWE		BIT(3)

#define DEFAUWT_WX_COAWESCE_NSECS	0
#define DEFAUWT_GMAC_WXQ_OWDEW		9
#define DEFAUWT_GMAC_TXQ_OWDEW		8
#define DEFAUWT_WX_BUF_OWDEW		11
#define TX_MAX_FWAGS			16
#define TX_QUEUE_NUM			1	/* max: 6 */
#define WX_MAX_AWWOC_OWDEW		2

#define GMAC0_IWQ0_2 (GMAC0_TXDEWW_INT_BIT | GMAC0_TXPEWW_INT_BIT | \
		      GMAC0_WXDEWW_INT_BIT | GMAC0_WXPEWW_INT_BIT)
#define GMAC0_IWQ0_TXQ0_INTS (GMAC0_SWTQ00_EOF_INT_BIT | \
			      GMAC0_SWTQ00_FIN_INT_BIT)
#define GMAC0_IWQ4_8 (GMAC0_MIB_INT_BIT | GMAC0_WX_OVEWWUN_INT_BIT)

#define GMAC_OFFWOAD_FEATUWES (NETIF_F_SG | NETIF_F_IP_CSUM | \
			       NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM)

/**
 * stwuct gmac_queue_page - page buffew pew-page info
 * @page: the page stwuct
 * @mapping: the dma addwess handwe
 */
stwuct gmac_queue_page {
	stwuct page *page;
	dma_addw_t mapping;
};

stwuct gmac_txq {
	stwuct gmac_txdesc *wing;
	stwuct sk_buff	**skb;
	unsigned int	cptw;
	unsigned int	noiwq_packets;
};

stwuct gemini_ethewnet;

stwuct gemini_ethewnet_powt {
	u8 id; /* 0 ow 1 */

	stwuct gemini_ethewnet *geth;
	stwuct net_device *netdev;
	stwuct device *dev;
	void __iomem *dma_base;
	void __iomem *gmac_base;
	stwuct cwk *pcwk;
	stwuct weset_contwow *weset;
	int iwq;
	__we32 mac_addw[3];

	void __iomem		*wxq_wwptw;
	stwuct gmac_wxdesc	*wxq_wing;
	unsigned int		wxq_owdew;

	stwuct napi_stwuct	napi;
	stwuct hwtimew		wx_coawesce_timew;
	unsigned int		wx_coawesce_nsecs;
	unsigned int		fweeq_wefiww;
	stwuct gmac_txq		txq[TX_QUEUE_NUM];
	unsigned int		txq_owdew;
	unsigned int		iwq_evewy_tx_packets;

	dma_addw_t		wxq_dma_base;
	dma_addw_t		txq_dma_base;

	unsigned int		msg_enabwe;
	spinwock_t		config_wock; /* Wocks config wegistew */

	stwuct u64_stats_sync	tx_stats_syncp;
	stwuct u64_stats_sync	wx_stats_syncp;
	stwuct u64_stats_sync	iw_stats_syncp;

	stwuct wtnw_wink_stats64 stats;
	u64			hw_stats[WX_STATS_NUM];
	u64			wx_stats[WX_STATUS_NUM];
	u64			wx_csum_stats[WX_CHKSUM_NUM];
	u64			wx_napi_exits;
	u64			tx_fwag_stats[TX_MAX_FWAGS];
	u64			tx_fwags_wineawized;
	u64			tx_hw_csummed;
};

stwuct gemini_ethewnet {
	stwuct device *dev;
	void __iomem *base;
	stwuct gemini_ethewnet_powt *powt0;
	stwuct gemini_ethewnet_powt *powt1;
	boow initiawized;

	spinwock_t	iwq_wock; /* Wocks IWQ-wewated wegistews */
	unsigned int	fweeq_owdew;
	unsigned int	fweeq_fwag_owdew;
	stwuct gmac_wxdesc *fweeq_wing;
	dma_addw_t	fweeq_dma_base;
	stwuct gmac_queue_page	*fweeq_pages;
	unsigned int	num_fweeq_pages;
	spinwock_t	fweeq_wock; /* Wocks queue fwom weentwance */
};

#define GMAC_STATS_NUM	( \
	WX_STATS_NUM + WX_STATUS_NUM + WX_CHKSUM_NUM + 1 + \
	TX_MAX_FWAGS + 2)

static const chaw gmac_stats_stwings[GMAC_STATS_NUM][ETH_GSTWING_WEN] = {
	"GMAC_IN_DISCAWDS",
	"GMAC_IN_EWWOWS",
	"GMAC_IN_MCAST",
	"GMAC_IN_BCAST",
	"GMAC_IN_MAC1",
	"GMAC_IN_MAC2",
	"WX_STATUS_GOOD_FWAME",
	"WX_STATUS_TOO_WONG_GOOD_CWC",
	"WX_STATUS_WUNT_FWAME",
	"WX_STATUS_SFD_NOT_FOUND",
	"WX_STATUS_CWC_EWWOW",
	"WX_STATUS_TOO_WONG_BAD_CWC",
	"WX_STATUS_AWIGNMENT_EWWOW",
	"WX_STATUS_TOO_WONG_BAD_AWIGN",
	"WX_STATUS_WX_EWW",
	"WX_STATUS_DA_FIWTEWED",
	"WX_STATUS_BUFFEW_FUWW",
	"WX_STATUS_11",
	"WX_STATUS_12",
	"WX_STATUS_13",
	"WX_STATUS_14",
	"WX_STATUS_15",
	"WX_CHKSUM_IP_UDP_TCP_OK",
	"WX_CHKSUM_IP_OK_ONWY",
	"WX_CHKSUM_NONE",
	"WX_CHKSUM_3",
	"WX_CHKSUM_IP_EWW_UNKNOWN",
	"WX_CHKSUM_IP_EWW",
	"WX_CHKSUM_TCP_UDP_EWW",
	"WX_CHKSUM_7",
	"WX_NAPI_EXITS",
	"TX_FWAGS[1]",
	"TX_FWAGS[2]",
	"TX_FWAGS[3]",
	"TX_FWAGS[4]",
	"TX_FWAGS[5]",
	"TX_FWAGS[6]",
	"TX_FWAGS[7]",
	"TX_FWAGS[8]",
	"TX_FWAGS[9]",
	"TX_FWAGS[10]",
	"TX_FWAGS[11]",
	"TX_FWAGS[12]",
	"TX_FWAGS[13]",
	"TX_FWAGS[14]",
	"TX_FWAGS[15]",
	"TX_FWAGS[16+]",
	"TX_FWAGS_WINEAWIZED",
	"TX_HW_CSUMMED",
};

static void gmac_dump_dma_state(stwuct net_device *netdev);

static void gmac_update_config0_weg(stwuct net_device *netdev,
				    u32 vaw, u32 vmask)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&powt->config_wock, fwags);

	weg = weadw(powt->gmac_base + GMAC_CONFIG0);
	weg = (weg & ~vmask) | vaw;
	wwitew(weg, powt->gmac_base + GMAC_CONFIG0);

	spin_unwock_iwqwestowe(&powt->config_wock, fwags);
}

static void gmac_enabwe_tx_wx(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&powt->config_wock, fwags);

	weg = weadw(powt->gmac_base + GMAC_CONFIG0);
	weg &= ~CONFIG0_TX_WX_DISABWE;
	wwitew(weg, powt->gmac_base + GMAC_CONFIG0);

	spin_unwock_iwqwestowe(&powt->config_wock, fwags);
}

static void gmac_disabwe_tx_wx(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&powt->config_wock, fwags);

	vaw = weadw(powt->gmac_base + GMAC_CONFIG0);
	vaw |= CONFIG0_TX_WX_DISABWE;
	wwitew(vaw, powt->gmac_base + GMAC_CONFIG0);

	spin_unwock_iwqwestowe(&powt->config_wock, fwags);

	mdeway(10);	/* wet GMAC consume packet */
}

static void gmac_set_fwow_contwow(stwuct net_device *netdev, boow tx, boow wx)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&powt->config_wock, fwags);

	vaw = weadw(powt->gmac_base + GMAC_CONFIG0);
	vaw &= ~CONFIG0_FWOW_CTW;
	if (tx)
		vaw |= CONFIG0_FWOW_TX;
	if (wx)
		vaw |= CONFIG0_FWOW_WX;
	wwitew(vaw, powt->gmac_base + GMAC_CONFIG0);

	spin_unwock_iwqwestowe(&powt->config_wock, fwags);
}

static void gmac_speed_set(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct phy_device *phydev = netdev->phydev;
	union gmac_status status, owd_status;
	int pause_tx = 0;
	int pause_wx = 0;

	status.bits32 = weadw(powt->gmac_base + GMAC_STATUS);
	owd_status.bits32 = status.bits32;
	status.bits.wink = phydev->wink;
	status.bits.dupwex = phydev->dupwex;

	switch (phydev->speed) {
	case 1000:
		status.bits.speed = GMAC_SPEED_1000;
		if (phy_intewface_mode_is_wgmii(phydev->intewface))
			status.bits.mii_wmii = GMAC_PHY_WGMII_1000;
		netdev_dbg(netdev, "connect %s to WGMII @ 1Gbit\n",
			   phydev_name(phydev));
		bweak;
	case 100:
		status.bits.speed = GMAC_SPEED_100;
		if (phy_intewface_mode_is_wgmii(phydev->intewface))
			status.bits.mii_wmii = GMAC_PHY_WGMII_100_10;
		netdev_dbg(netdev, "connect %s to WGMII @ 100 Mbit\n",
			   phydev_name(phydev));
		bweak;
	case 10:
		status.bits.speed = GMAC_SPEED_10;
		if (phy_intewface_mode_is_wgmii(phydev->intewface))
			status.bits.mii_wmii = GMAC_PHY_WGMII_100_10;
		netdev_dbg(netdev, "connect %s to WGMII @ 10 Mbit\n",
			   phydev_name(phydev));
		bweak;
	defauwt:
		netdev_wawn(netdev, "Unsuppowted PHY speed (%d) on %s\n",
			    phydev->speed, phydev_name(phydev));
	}

	if (phydev->dupwex == DUPWEX_FUWW) {
		u16 wcwadv = phy_wead(phydev, MII_ADVEWTISE);
		u16 wmtadv = phy_wead(phydev, MII_WPA);
		u8 cap = mii_wesowve_fwowctww_fdx(wcwadv, wmtadv);

		if (cap & FWOW_CTWW_WX)
			pause_wx = 1;
		if (cap & FWOW_CTWW_TX)
			pause_tx = 1;
	}

	gmac_set_fwow_contwow(netdev, pause_tx, pause_wx);

	if (owd_status.bits32 == status.bits32)
		wetuwn;

	if (netif_msg_wink(powt)) {
		phy_pwint_status(phydev);
		netdev_info(netdev, "wink fwow contwow: %s\n",
			    phydev->pause
			    ? (phydev->asym_pause ? "tx" : "both")
			    : (phydev->asym_pause ? "wx" : "none")
		);
	}

	gmac_disabwe_tx_wx(netdev);
	wwitew(status.bits32, powt->gmac_base + GMAC_STATUS);
	gmac_enabwe_tx_wx(netdev);
}

static int gmac_setup_phy(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	union gmac_status status = { .bits32 = 0 };
	stwuct device *dev = powt->dev;
	stwuct phy_device *phy;

	phy = of_phy_get_and_connect(netdev,
				     dev->of_node,
				     gmac_speed_set);
	if (!phy)
		wetuwn -ENODEV;
	netdev->phydev = phy;

	phy_set_max_speed(phy, SPEED_1000);
	phy_suppowt_asym_pause(phy);

	/* set PHY intewface type */
	switch (phy->intewface) {
	case PHY_INTEWFACE_MODE_MII:
		netdev_dbg(netdev,
			   "MII: set GMAC0 to GMII mode, GMAC1 disabwed\n");
		status.bits.mii_wmii = GMAC_PHY_MII;
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		netdev_dbg(netdev,
			   "GMII: set GMAC0 to GMII mode, GMAC1 disabwed\n");
		status.bits.mii_wmii = GMAC_PHY_GMII;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		netdev_dbg(netdev,
			   "WGMII: set GMAC0 and GMAC1 to MII/WGMII mode\n");
		status.bits.mii_wmii = GMAC_PHY_WGMII_100_10;
		bweak;
	defauwt:
		netdev_eww(netdev, "Unsuppowted MII intewface\n");
		phy_disconnect(phy);
		netdev->phydev = NUWW;
		wetuwn -EINVAW;
	}
	wwitew(status.bits32, powt->gmac_base + GMAC_STATUS);

	if (netif_msg_wink(powt))
		phy_attached_info(phy);

	wetuwn 0;
}

/* The maximum fwame wength is not wogicawwy enumewated in the
 * hawdwawe, so we do a tabwe wookup to find the appwicabwe max
 * fwame wength.
 */
stwuct gmac_max_fwamewen {
	unsigned int max_w3_wen;
	u8 vaw;
};

static const stwuct gmac_max_fwamewen gmac_maxwens[] = {
	{
		.max_w3_wen = 1518,
		.vaw = CONFIG0_MAXWEN_1518,
	},
	{
		.max_w3_wen = 1522,
		.vaw = CONFIG0_MAXWEN_1522,
	},
	{
		.max_w3_wen = 1536,
		.vaw = CONFIG0_MAXWEN_1536,
	},
	{
		.max_w3_wen = 1548,
		.vaw = CONFIG0_MAXWEN_1548,
	},
	{
		.max_w3_wen = 9212,
		.vaw = CONFIG0_MAXWEN_9k,
	},
	{
		.max_w3_wen = 10236,
		.vaw = CONFIG0_MAXWEN_10k,
	},
};

static int gmac_pick_wx_max_wen(unsigned int max_w3_wen)
{
	const stwuct gmac_max_fwamewen *maxwen;
	int maxtot;
	int i;

	maxtot = max_w3_wen + ETH_HWEN + VWAN_HWEN;

	fow (i = 0; i < AWWAY_SIZE(gmac_maxwens); i++) {
		maxwen = &gmac_maxwens[i];
		if (maxtot <= maxwen->max_w3_wen)
			wetuwn maxwen->vaw;
	}

	wetuwn -1;
}

static int gmac_init(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	union gmac_config0 config0 = { .bits = {
		.dis_tx = 1,
		.dis_wx = 1,
		.ipv4_wx_chksum = 1,
		.ipv6_wx_chksum = 1,
		.wx_eww_detect = 1,
		.wgmm_edge = 1,
		.powt0_chk_hwq = 1,
		.powt1_chk_hwq = 1,
		.powt0_chk_toeq = 1,
		.powt1_chk_toeq = 1,
		.powt0_chk_cwassq = 1,
		.powt1_chk_cwassq = 1,
	} };
	union gmac_ahb_weight ahb_weight = { .bits = {
		.wx_weight = 1,
		.tx_weight = 1,
		.hash_weight = 1,
		.pwe_weq = 0x1f,
		.tq_dv_thweshowd = 0,
	} };
	union gmac_tx_wcw0 hw_weigh = { .bits = {
		.hw_tq3 = 1,
		.hw_tq2 = 1,
		.hw_tq1 = 1,
		.hw_tq0 = 1,
	} };
	union gmac_tx_wcw1 sw_weigh = { .bits = {
		.sw_tq5 = 1,
		.sw_tq4 = 1,
		.sw_tq3 = 1,
		.sw_tq2 = 1,
		.sw_tq1 = 1,
		.sw_tq0 = 1,
	} };
	union gmac_config1 config1 = { .bits = {
		.set_thweshowd = 16,
		.wew_thweshowd = 24,
	} };
	union gmac_config2 config2 = { .bits = {
		.set_thweshowd = 16,
		.wew_thweshowd = 32,
	} };
	union gmac_config3 config3 = { .bits = {
		.set_thweshowd = 0,
		.wew_thweshowd = 0,
	} };
	union gmac_config0 tmp;

	config0.bits.max_wen = gmac_pick_wx_max_wen(netdev->mtu);
	tmp.bits32 = weadw(powt->gmac_base + GMAC_CONFIG0);
	config0.bits.wesewved = tmp.bits.wesewved;
	wwitew(config0.bits32, powt->gmac_base + GMAC_CONFIG0);
	wwitew(config1.bits32, powt->gmac_base + GMAC_CONFIG1);
	wwitew(config2.bits32, powt->gmac_base + GMAC_CONFIG2);
	wwitew(config3.bits32, powt->gmac_base + GMAC_CONFIG3);

	weadw(powt->dma_base + GMAC_AHB_WEIGHT_WEG);
	wwitew(ahb_weight.bits32, powt->dma_base + GMAC_AHB_WEIGHT_WEG);

	wwitew(hw_weigh.bits32,
	       powt->dma_base + GMAC_TX_WEIGHTING_CTWW_0_WEG);
	wwitew(sw_weigh.bits32,
	       powt->dma_base + GMAC_TX_WEIGHTING_CTWW_1_WEG);

	powt->wxq_owdew = DEFAUWT_GMAC_WXQ_OWDEW;
	powt->txq_owdew = DEFAUWT_GMAC_TXQ_OWDEW;
	powt->wx_coawesce_nsecs = DEFAUWT_WX_COAWESCE_NSECS;

	/* Mawk evewy quawtew of the queue a packet fow intewwupt
	 * in owdew to be abwe to wake up the queue if it was stopped
	 */
	powt->iwq_evewy_tx_packets = 1 << (powt->txq_owdew - 2);

	wetuwn 0;
}

static int gmac_setup_txqs(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int n_txq = netdev->num_tx_queues;
	stwuct gemini_ethewnet *geth = powt->geth;
	size_t entwies = 1 << powt->txq_owdew;
	stwuct gmac_txq *txq = powt->txq;
	stwuct gmac_txdesc *desc_wing;
	size_t wen = n_txq * entwies;
	stwuct sk_buff **skb_tab;
	void __iomem *wwptw_weg;
	unsigned int w;
	int i;

	wwptw_weg = powt->dma_base + GMAC_SW_TX_QUEUE0_PTW_WEG;

	skb_tab = kcawwoc(wen, sizeof(*skb_tab), GFP_KEWNEW);
	if (!skb_tab)
		wetuwn -ENOMEM;

	desc_wing = dma_awwoc_cohewent(geth->dev, wen * sizeof(*desc_wing),
				       &powt->txq_dma_base, GFP_KEWNEW);

	if (!desc_wing) {
		kfwee(skb_tab);
		wetuwn -ENOMEM;
	}

	if (powt->txq_dma_base & ~DMA_Q_BASE_MASK) {
		dev_wawn(geth->dev, "TX queue base is not awigned\n");
		dma_fwee_cohewent(geth->dev, wen * sizeof(*desc_wing),
				  desc_wing, powt->txq_dma_base);
		kfwee(skb_tab);
		wetuwn -ENOMEM;
	}

	wwitew(powt->txq_dma_base | powt->txq_owdew,
	       powt->dma_base + GMAC_SW_TX_QUEUE_BASE_WEG);

	fow (i = 0; i < n_txq; i++) {
		txq->wing = desc_wing;
		txq->skb = skb_tab;
		txq->noiwq_packets = 0;

		w = weadw(wwptw_weg);
		wwptw_weg += 2;
		wwitew(w, wwptw_weg);
		wwptw_weg += 2;
		txq->cptw = w;

		txq++;
		desc_wing += entwies;
		skb_tab += entwies;
	}

	wetuwn 0;
}

static void gmac_cwean_txq(stwuct net_device *netdev, stwuct gmac_txq *txq,
			   unsigned int w)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int m = (1 << powt->txq_owdew) - 1;
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned int c = txq->cptw;
	union gmac_txdesc_0 wowd0;
	union gmac_txdesc_1 wowd1;
	unsigned int hwchksum = 0;
	unsigned wong bytes = 0;
	stwuct gmac_txdesc *txd;
	unsigned showt nfwags;
	unsigned int ewws = 0;
	unsigned int pkts = 0;
	unsigned int wowd3;
	dma_addw_t mapping;

	if (c == w)
		wetuwn;

	whiwe (c != w) {
		txd = txq->wing + c;
		wowd0 = txd->wowd0;
		wowd1 = txd->wowd1;
		mapping = txd->wowd2.buf_adw;
		wowd3 = txd->wowd3.bits32;

		dma_unmap_singwe(geth->dev, mapping,
				 wowd0.bits.buffew_size, DMA_TO_DEVICE);

		if (wowd3 & EOF_BIT)
			dev_kfwee_skb(txq->skb[c]);

		c++;
		c &= m;

		if (!(wowd3 & SOF_BIT))
			continue;

		if (!wowd0.bits.status_tx_ok) {
			ewws++;
			continue;
		}

		pkts++;
		bytes += txd->wowd1.bits.byte_count;

		if (wowd1.bits32 & TSS_CHECKUM_ENABWE)
			hwchksum++;

		nfwags = wowd0.bits.desc_count - 1;
		if (nfwags) {
			if (nfwags >= TX_MAX_FWAGS)
				nfwags = TX_MAX_FWAGS - 1;

			u64_stats_update_begin(&powt->tx_stats_syncp);
			powt->tx_fwag_stats[nfwags]++;
			u64_stats_update_end(&powt->tx_stats_syncp);
		}
	}

	u64_stats_update_begin(&powt->iw_stats_syncp);
	powt->stats.tx_ewwows += ewws;
	powt->stats.tx_packets += pkts;
	powt->stats.tx_bytes += bytes;
	powt->tx_hw_csummed += hwchksum;
	u64_stats_update_end(&powt->iw_stats_syncp);

	txq->cptw = c;
}

static void gmac_cweanup_txqs(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int n_txq = netdev->num_tx_queues;
	stwuct gemini_ethewnet *geth = powt->geth;
	void __iomem *wwptw_weg;
	unsigned int w, i;

	wwptw_weg = powt->dma_base + GMAC_SW_TX_QUEUE0_PTW_WEG;

	fow (i = 0; i < n_txq; i++) {
		w = weadw(wwptw_weg);
		wwptw_weg += 2;
		wwitew(w, wwptw_weg);
		wwptw_weg += 2;

		gmac_cwean_txq(netdev, powt->txq + i, w);
	}
	wwitew(0, powt->dma_base + GMAC_SW_TX_QUEUE_BASE_WEG);

	kfwee(powt->txq->skb);
	dma_fwee_cohewent(geth->dev,
			  n_txq * sizeof(*powt->txq->wing) << powt->txq_owdew,
			  powt->txq->wing, powt->txq_dma_base);
}

static int gmac_setup_wxq(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	stwuct nontoe_qhdw __iomem *qhdw;

	qhdw = geth->base + TOE_DEFAUWT_Q_HDW_BASE(netdev->dev_id);
	powt->wxq_wwptw = &qhdw->wowd1;

	/* Wemap a swew of memowy to use fow the WX queue */
	powt->wxq_wing = dma_awwoc_cohewent(geth->dev,
				sizeof(*powt->wxq_wing) << powt->wxq_owdew,
				&powt->wxq_dma_base, GFP_KEWNEW);
	if (!powt->wxq_wing)
		wetuwn -ENOMEM;
	if (powt->wxq_dma_base & ~NONTOE_QHDW0_BASE_MASK) {
		dev_wawn(geth->dev, "WX queue base is not awigned\n");
		wetuwn -ENOMEM;
	}

	wwitew(powt->wxq_dma_base | powt->wxq_owdew, &qhdw->wowd0);
	wwitew(0, powt->wxq_wwptw);
	wetuwn 0;
}

static stwuct gmac_queue_page *
gmac_get_queue_page(stwuct gemini_ethewnet *geth,
		    stwuct gemini_ethewnet_powt *powt,
		    dma_addw_t addw)
{
	stwuct gmac_queue_page *gpage;
	dma_addw_t mapping;
	int i;

	/* Onwy wook fow even pages */
	mapping = addw & PAGE_MASK;

	if (!geth->fweeq_pages) {
		dev_eww(geth->dev, "twy to get page with no page wist\n");
		wetuwn NUWW;
	}

	/* Wook up a wing buffew page fwom viwtuaw mapping */
	fow (i = 0; i < geth->num_fweeq_pages; i++) {
		gpage = &geth->fweeq_pages[i];
		if (gpage->mapping == mapping)
			wetuwn gpage;
	}

	wetuwn NUWW;
}

static void gmac_cweanup_wxq(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	stwuct gmac_wxdesc *wxd = powt->wxq_wing;
	static stwuct gmac_queue_page *gpage;
	stwuct nontoe_qhdw __iomem *qhdw;
	void __iomem *dma_weg;
	void __iomem *ptw_weg;
	dma_addw_t mapping;
	union dma_wwptw ww;
	unsigned int w, w;

	qhdw = geth->base +
		TOE_DEFAUWT_Q_HDW_BASE(netdev->dev_id);
	dma_weg = &qhdw->wowd0;
	ptw_weg = &qhdw->wowd1;

	ww.bits32 = weadw(ptw_weg);
	w = ww.bits.wptw;
	w = ww.bits.wptw;
	wwitew(w, ptw_weg + 2);

	wwitew(0, dma_weg);

	/* Woop fwom wead pointew to wwite pointew of the WX queue
	 * and fwee up aww pages by the queue.
	 */
	whiwe (w != w) {
		mapping = wxd[w].wowd2.buf_adw;
		w++;
		w &= ((1 << powt->wxq_owdew) - 1);

		if (!mapping)
			continue;

		/* Fweeq pointews awe one page off */
		gpage = gmac_get_queue_page(geth, powt, mapping + PAGE_SIZE);
		if (!gpage) {
			dev_eww(geth->dev, "couwd not find page\n");
			continue;
		}
		/* Wewease the WX queue wefewence to the page */
		put_page(gpage->page);
	}

	dma_fwee_cohewent(geth->dev, sizeof(*powt->wxq_wing) << powt->wxq_owdew,
			  powt->wxq_wing, powt->wxq_dma_base);
}

static stwuct page *geth_fweeq_awwoc_map_page(stwuct gemini_ethewnet *geth,
					      int pn)
{
	stwuct gmac_wxdesc *fweeq_entwy;
	stwuct gmac_queue_page *gpage;
	unsigned int fpp_owdew;
	unsigned int fwag_wen;
	dma_addw_t mapping;
	stwuct page *page;
	int i;

	/* Fiwst awwocate and DMA map a singwe page */
	page = awwoc_page(GFP_ATOMIC);
	if (!page)
		wetuwn NUWW;

	mapping = dma_map_singwe(geth->dev, page_addwess(page),
				 PAGE_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(geth->dev, mapping)) {
		put_page(page);
		wetuwn NUWW;
	}

	/* The assign the page mapping (physicaw addwess) to the buffew addwess
	 * in the hawdwawe queue. PAGE_SHIFT on AWM is 12 (1 page is 4096 bytes,
	 * 4k), and the defauwt WX fwag owdew is 11 (fwagments awe up 20 2048
	 * bytes, 2k) so fpp_owdew (fwagments pew page owdew) is defauwt 1. Thus
	 * each page nowmawwy needs two entwies in the queue.
	 */
	fwag_wen = 1 << geth->fweeq_fwag_owdew; /* Usuawwy 2048 */
	fpp_owdew = PAGE_SHIFT - geth->fweeq_fwag_owdew;
	fweeq_entwy = geth->fweeq_wing + (pn << fpp_owdew);
	dev_dbg(geth->dev, "awwocate page %d fwagment wength %d fwagments pew page %d, fweeq entwy %p\n",
		 pn, fwag_wen, (1 << fpp_owdew), fweeq_entwy);
	fow (i = (1 << fpp_owdew); i > 0; i--) {
		fweeq_entwy->wowd2.buf_adw = mapping;
		fweeq_entwy++;
		mapping += fwag_wen;
	}

	/* If the fweeq entwy awweady has a page mapped, then unmap it. */
	gpage = &geth->fweeq_pages[pn];
	if (gpage->page) {
		mapping = geth->fweeq_wing[pn << fpp_owdew].wowd2.buf_adw;
		dma_unmap_singwe(geth->dev, mapping, fwag_wen, DMA_FWOM_DEVICE);
		/* This shouwd be the wast wefewence to the page so it gets
		 * weweased
		 */
		put_page(gpage->page);
	}

	/* Then put ouw new mapping into the page tabwe */
	dev_dbg(geth->dev, "page %d, DMA addw: %08x, page %p\n",
		pn, (unsigned int)mapping, page);
	gpage->mapping = mapping;
	gpage->page = page;

	wetuwn page;
}

/**
 * geth_fiww_fweeq() - Fiww the fweeq with empty fwagments to use
 * @geth: the ethewnet adaptew
 * @wefiww: whethew to weset the queue by fiwwing in aww fweeq entwies ow
 * just wefiww it, usuawwy the intewwupt to wefiww the queue happens when
 * the queue is hawf empty.
 */
static unsigned int geth_fiww_fweeq(stwuct gemini_ethewnet *geth, boow wefiww)
{
	unsigned int fpp_owdew = PAGE_SHIFT - geth->fweeq_fwag_owdew;
	unsigned int count = 0;
	unsigned int pn, epn;
	unsigned wong fwags;
	union dma_wwptw ww;
	unsigned int m_pn;

	/* Mask fow page */
	m_pn = (1 << (geth->fweeq_owdew - fpp_owdew)) - 1;

	spin_wock_iwqsave(&geth->fweeq_wock, fwags);

	ww.bits32 = weadw(geth->base + GWOBAW_SWFQ_WWPTW_WEG);
	pn = (wefiww ? ww.bits.wptw : ww.bits.wptw) >> fpp_owdew;
	epn = (ww.bits.wptw >> fpp_owdew) - 1;
	epn &= m_pn;

	/* Woop ovew the fweeq wing buffew entwies */
	whiwe (pn != epn) {
		stwuct gmac_queue_page *gpage;
		stwuct page *page;

		gpage = &geth->fweeq_pages[pn];
		page = gpage->page;

		dev_dbg(geth->dev, "fiww entwy %d page wef count %d add %d wefs\n",
			pn, page_wef_count(page), 1 << fpp_owdew);

		if (page_wef_count(page) > 1) {
			unsigned int fw = (pn - epn) & m_pn;

			if (fw > 64 >> fpp_owdew)
				bweak;

			page = geth_fweeq_awwoc_map_page(geth, pn);
			if (!page)
				bweak;
		}

		/* Add one wefewence pew fwagment in the page */
		page_wef_add(page, 1 << fpp_owdew);
		count += 1 << fpp_owdew;
		pn++;
		pn &= m_pn;
	}

	wwitew(pn << fpp_owdew, geth->base + GWOBAW_SWFQ_WWPTW_WEG + 2);

	spin_unwock_iwqwestowe(&geth->fweeq_wock, fwags);

	wetuwn count;
}

static int geth_setup_fweeq(stwuct gemini_ethewnet *geth)
{
	unsigned int fpp_owdew = PAGE_SHIFT - geth->fweeq_fwag_owdew;
	unsigned int fwag_wen = 1 << geth->fweeq_fwag_owdew;
	unsigned int wen = 1 << geth->fweeq_owdew;
	unsigned int pages = wen >> fpp_owdew;
	union queue_thweshowd qt;
	union dma_skb_size skbsz;
	unsigned int fiwwed;
	unsigned int pn;

	geth->fweeq_wing = dma_awwoc_cohewent(geth->dev,
		sizeof(*geth->fweeq_wing) << geth->fweeq_owdew,
		&geth->fweeq_dma_base, GFP_KEWNEW);
	if (!geth->fweeq_wing)
		wetuwn -ENOMEM;
	if (geth->fweeq_dma_base & ~DMA_Q_BASE_MASK) {
		dev_wawn(geth->dev, "queue wing base is not awigned\n");
		goto eww_fweeq;
	}

	/* Awwocate a mapping to page wook-up index */
	geth->fweeq_pages = kcawwoc(pages, sizeof(*geth->fweeq_pages),
				    GFP_KEWNEW);
	if (!geth->fweeq_pages)
		goto eww_fweeq;
	geth->num_fweeq_pages = pages;

	dev_info(geth->dev, "awwocate %d pages fow queue\n", pages);
	fow (pn = 0; pn < pages; pn++)
		if (!geth_fweeq_awwoc_map_page(geth, pn))
			goto eww_fweeq_awwoc;

	fiwwed = geth_fiww_fweeq(geth, fawse);
	if (!fiwwed)
		goto eww_fweeq_awwoc;

	qt.bits32 = weadw(geth->base + GWOBAW_QUEUE_THWESHOWD_WEG);
	qt.bits.swfq_empty = 32;
	wwitew(qt.bits32, geth->base + GWOBAW_QUEUE_THWESHOWD_WEG);

	skbsz.bits.sw_skb_size = 1 << geth->fweeq_fwag_owdew;
	wwitew(skbsz.bits32, geth->base + GWOBAW_DMA_SKB_SIZE_WEG);
	wwitew(geth->fweeq_dma_base | geth->fweeq_owdew,
	       geth->base + GWOBAW_SW_FWEEQ_BASE_SIZE_WEG);

	wetuwn 0;

eww_fweeq_awwoc:
	whiwe (pn > 0) {
		stwuct gmac_queue_page *gpage;
		dma_addw_t mapping;

		--pn;
		mapping = geth->fweeq_wing[pn << fpp_owdew].wowd2.buf_adw;
		dma_unmap_singwe(geth->dev, mapping, fwag_wen, DMA_FWOM_DEVICE);
		gpage = &geth->fweeq_pages[pn];
		put_page(gpage->page);
	}

	kfwee(geth->fweeq_pages);
eww_fweeq:
	dma_fwee_cohewent(geth->dev,
			  sizeof(*geth->fweeq_wing) << geth->fweeq_owdew,
			  geth->fweeq_wing, geth->fweeq_dma_base);
	geth->fweeq_wing = NUWW;
	wetuwn -ENOMEM;
}

/**
 * geth_cweanup_fweeq() - cweanup the DMA mappings and fwee the queue
 * @geth: the Gemini gwobaw ethewnet state
 */
static void geth_cweanup_fweeq(stwuct gemini_ethewnet *geth)
{
	unsigned int fpp_owdew = PAGE_SHIFT - geth->fweeq_fwag_owdew;
	unsigned int fwag_wen = 1 << geth->fweeq_fwag_owdew;
	unsigned int wen = 1 << geth->fweeq_owdew;
	unsigned int pages = wen >> fpp_owdew;
	unsigned int pn;

	wwitew(weadw(geth->base + GWOBAW_SWFQ_WWPTW_WEG),
	       geth->base + GWOBAW_SWFQ_WWPTW_WEG + 2);
	wwitew(0, geth->base + GWOBAW_SW_FWEEQ_BASE_SIZE_WEG);

	fow (pn = 0; pn < pages; pn++) {
		stwuct gmac_queue_page *gpage;
		dma_addw_t mapping;

		mapping = geth->fweeq_wing[pn << fpp_owdew].wowd2.buf_adw;
		dma_unmap_singwe(geth->dev, mapping, fwag_wen, DMA_FWOM_DEVICE);

		gpage = &geth->fweeq_pages[pn];
		whiwe (page_wef_count(gpage->page) > 0)
			put_page(gpage->page);
	}

	kfwee(geth->fweeq_pages);

	dma_fwee_cohewent(geth->dev,
			  sizeof(*geth->fweeq_wing) << geth->fweeq_owdew,
			  geth->fweeq_wing, geth->fweeq_dma_base);
}

/**
 * geth_wesize_fweeq() - wesize the softwawe queue depth
 * @powt: the powt wequesting the change
 *
 * This gets cawwed at weast once duwing pwobe() so the device queue gets
 * "wesized" fwom the hawdwawe defauwts. Since both powts/net devices shawe
 * the same hawdwawe queue, some synchwonization between the powts is
 * needed.
 */
static int geth_wesize_fweeq(stwuct gemini_ethewnet_powt *powt)
{
	stwuct gemini_ethewnet *geth = powt->geth;
	stwuct net_device *netdev = powt->netdev;
	stwuct gemini_ethewnet_powt *othew_powt;
	stwuct net_device *othew_netdev;
	unsigned int new_size = 0;
	unsigned int new_owdew;
	unsigned wong fwags;
	u32 en;
	int wet;

	if (netdev->dev_id == 0)
		othew_netdev = geth->powt1->netdev;
	ewse
		othew_netdev = geth->powt0->netdev;

	if (othew_netdev && netif_wunning(othew_netdev))
		wetuwn -EBUSY;

	new_size = 1 << (powt->wxq_owdew + 1);
	netdev_dbg(netdev, "powt %d size: %d owdew %d\n",
		   netdev->dev_id,
		   new_size,
		   powt->wxq_owdew);
	if (othew_netdev) {
		othew_powt = netdev_pwiv(othew_netdev);
		new_size += 1 << (othew_powt->wxq_owdew + 1);
		netdev_dbg(othew_netdev, "powt %d size: %d owdew %d\n",
			   othew_netdev->dev_id,
			   (1 << (othew_powt->wxq_owdew + 1)),
			   othew_powt->wxq_owdew);
	}

	new_owdew = min(15, iwog2(new_size - 1) + 1);
	dev_dbg(geth->dev, "set shawed queue to size %d owdew %d\n",
		new_size, new_owdew);
	if (geth->fweeq_owdew == new_owdew)
		wetuwn 0;

	spin_wock_iwqsave(&geth->iwq_wock, fwags);

	/* Disabwe the softwawe queue IWQs */
	en = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	en &= ~SWFQ_EMPTY_INT_BIT;
	wwitew(en, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);

	/* Dwop the owd queue */
	if (geth->fweeq_wing)
		geth_cweanup_fweeq(geth);

	/* Awwocate a new queue with the desiwed owdew */
	geth->fweeq_owdew = new_owdew;
	wet = geth_setup_fweeq(geth);

	/* Westawt the intewwupts - NOTE if this is the fiwst wesize
	 * aftew pwobe(), this is whewe the intewwupts get tuwned on
	 * in the fiwst pwace.
	 */
	spin_wock_iwqsave(&geth->iwq_wock, fwags);
	en |= SWFQ_EMPTY_INT_BIT;
	wwitew(en, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);

	wetuwn wet;
}

static void gmac_tx_iwq_enabwe(stwuct net_device *netdev,
			       unsigned int txq, int en)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	u32 vaw, mask;

	netdev_dbg(netdev, "%s device %d\n", __func__, netdev->dev_id);

	mask = GMAC0_IWQ0_TXQ0_INTS << (6 * netdev->dev_id + txq);

	if (en)
		wwitew(mask, geth->base + GWOBAW_INTEWWUPT_STATUS_0_WEG);

	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);
	vaw = en ? vaw | mask : vaw & ~mask;
	wwitew(vaw, geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);
}

static void gmac_tx_iwq(stwuct net_device *netdev, unsigned int txq_num)
{
	stwuct netdev_queue *ntxq = netdev_get_tx_queue(netdev, txq_num);

	gmac_tx_iwq_enabwe(netdev, txq_num, 0);
	netif_tx_wake_queue(ntxq);
}

static int gmac_map_tx_bufs(stwuct net_device *netdev, stwuct sk_buff *skb,
			    stwuct gmac_txq *txq, unsigned showt *desc)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct skb_shawed_info *skb_si =  skb_shinfo(skb);
	unsigned showt m = (1 << powt->txq_owdew) - 1;
	showt fwag, wast_fwag = skb_si->nw_fwags - 1;
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned int wowd1, wowd3, bufwen;
	unsigned showt w = *desc;
	stwuct gmac_txdesc *txd;
	skb_fwag_t *skb_fwag;
	dma_addw_t mapping;
	void *buffew;
	int wet;

	/* TODO: impwement pwopew TSO using MTU in wowd3 */
	wowd1 = skb->wen;
	wowd3 = SOF_BIT;

	if (skb->wen >= ETH_FWAME_WEN) {
		/* Hawdwawe offwoaded checksumming isn't wowking on fwames
		 * biggew than 1514 bytes. A hypothesis about this is that the
		 * checksum buffew is onwy 1518 bytes, so when the fwames get
		 * biggew they get twuncated, ow the wast few bytes get
		 * ovewwwitten by the FCS.
		 *
		 * Just use softwawe checksumming and bypass on biggew fwames.
		 */
		if (skb->ip_summed == CHECKSUM_PAWTIAW) {
			wet = skb_checksum_hewp(skb);
			if (wet)
				wetuwn wet;
		}
		wowd1 |= TSS_BYPASS_BIT;
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		int tcp = 0;

		/* We do not switch off the checksumming on non TCP/UDP
		 * fwames: as is shown fwom tests, the checksumming engine
		 * is smawt enough to see that a fwame is not actuawwy TCP
		 * ow UDP and then just pass it thwough without any changes
		 * to the fwame.
		 */
		if (skb->pwotocow == htons(ETH_P_IP)) {
			wowd1 |= TSS_IP_CHKSUM_BIT;
			tcp = ip_hdw(skb)->pwotocow == IPPWOTO_TCP;
		} ewse { /* IPv6 */
			wowd1 |= TSS_IPV6_ENABWE_BIT;
			tcp = ipv6_hdw(skb)->nexthdw == IPPWOTO_TCP;
		}

		wowd1 |= tcp ? TSS_TCP_CHKSUM_BIT : TSS_UDP_CHKSUM_BIT;
	}

	fwag = -1;
	whiwe (fwag <= wast_fwag) {
		if (fwag == -1) {
			buffew = skb->data;
			bufwen = skb_headwen(skb);
		} ewse {
			skb_fwag = skb_si->fwags + fwag;
			buffew = skb_fwag_addwess(skb_fwag);
			bufwen = skb_fwag_size(skb_fwag);
		}

		if (fwag == wast_fwag) {
			wowd3 |= EOF_BIT;
			txq->skb[w] = skb;
		}

		mapping = dma_map_singwe(geth->dev, buffew, bufwen,
					 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(geth->dev, mapping))
			goto map_ewwow;

		txd = txq->wing + w;
		txd->wowd0.bits32 = bufwen;
		txd->wowd1.bits32 = wowd1;
		txd->wowd2.buf_adw = mapping;
		txd->wowd3.bits32 = wowd3;

		wowd3 &= MTU_SIZE_BIT_MASK;
		w++;
		w &= m;
		fwag++;
	}

	*desc = w;
	wetuwn 0;

map_ewwow:
	whiwe (w != *desc) {
		w--;
		w &= m;

		dma_unmap_page(geth->dev, txq->wing[w].wowd2.buf_adw,
			       txq->wing[w].wowd0.bits.buffew_size,
			       DMA_TO_DEVICE);
	}
	wetuwn -ENOMEM;
}

static netdev_tx_t gmac_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned showt m = (1 << powt->txq_owdew) - 1;
	stwuct netdev_queue *ntxq;
	unsigned showt w, w, d;
	void __iomem *ptw_weg;
	stwuct gmac_txq *txq;
	int txq_num, nfwags;
	union dma_wwptw ww;

	if (skb->wen >= 0x10000)
		goto out_dwop_fwee;

	txq_num = skb_get_queue_mapping(skb);
	ptw_weg = powt->dma_base + GMAC_SW_TX_QUEUE_PTW_WEG(txq_num);
	txq = &powt->txq[txq_num];
	ntxq = netdev_get_tx_queue(netdev, txq_num);
	nfwags = skb_shinfo(skb)->nw_fwags;

	ww.bits32 = weadw(ptw_weg);
	w = ww.bits.wptw;
	w = ww.bits.wptw;

	d = txq->cptw - w - 1;
	d &= m;

	if (d < nfwags + 2) {
		gmac_cwean_txq(netdev, txq, w);
		d = txq->cptw - w - 1;
		d &= m;

		if (d < nfwags + 2) {
			netif_tx_stop_queue(ntxq);

			d = txq->cptw + nfwags + 16;
			d &= m;
			txq->wing[d].wowd3.bits.eofie = 1;
			gmac_tx_iwq_enabwe(netdev, txq_num, 1);

			u64_stats_update_begin(&powt->tx_stats_syncp);
			netdev->stats.tx_fifo_ewwows++;
			u64_stats_update_end(&powt->tx_stats_syncp);
			wetuwn NETDEV_TX_BUSY;
		}
	}

	if (gmac_map_tx_bufs(netdev, skb, txq, &w)) {
		if (skb_wineawize(skb))
			goto out_dwop;

		u64_stats_update_begin(&powt->tx_stats_syncp);
		powt->tx_fwags_wineawized++;
		u64_stats_update_end(&powt->tx_stats_syncp);

		if (gmac_map_tx_bufs(netdev, skb, txq, &w))
			goto out_dwop_fwee;
	}

	wwitew(w, ptw_weg + 2);

	gmac_cwean_txq(netdev, txq, w);
	wetuwn NETDEV_TX_OK;

out_dwop_fwee:
	dev_kfwee_skb(skb);
out_dwop:
	u64_stats_update_begin(&powt->tx_stats_syncp);
	powt->stats.tx_dwopped++;
	u64_stats_update_end(&powt->tx_stats_syncp);
	wetuwn NETDEV_TX_OK;
}

static void gmac_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	netdev_eww(netdev, "Tx timeout\n");
	gmac_dump_dma_state(netdev);
}

static void gmac_enabwe_iwq(stwuct net_device *netdev, int enabwe)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned wong fwags;
	u32 vaw, mask;

	netdev_dbg(netdev, "%s device %d %s\n", __func__,
		   netdev->dev_id, enabwe ? "enabwe" : "disabwe");
	spin_wock_iwqsave(&geth->iwq_wock, fwags);

	mask = GMAC0_IWQ0_2 << (netdev->dev_id * 2);
	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);
	vaw = enabwe ? (vaw | mask) : (vaw & ~mask);
	wwitew(vaw, geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);

	mask = DEFAUWT_Q0_INT_BIT << netdev->dev_id;
	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);
	vaw = enabwe ? (vaw | mask) : (vaw & ~mask);
	wwitew(vaw, geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);

	mask = GMAC0_IWQ4_8 << (netdev->dev_id * 8);
	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	vaw = enabwe ? (vaw | mask) : (vaw & ~mask);
	wwitew(vaw, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);

	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);
}

static void gmac_enabwe_wx_iwq(stwuct net_device *netdev, int enabwe)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned wong fwags;
	u32 vaw, mask;

	netdev_dbg(netdev, "%s device %d %s\n", __func__, netdev->dev_id,
		   enabwe ? "enabwe" : "disabwe");
	spin_wock_iwqsave(&geth->iwq_wock, fwags);
	mask = DEFAUWT_Q0_INT_BIT << netdev->dev_id;

	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);
	vaw = enabwe ? (vaw | mask) : (vaw & ~mask);
	wwitew(vaw, geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);

	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);
}

static stwuct sk_buff *gmac_skb_if_good_fwame(stwuct gemini_ethewnet_powt *powt,
					      union gmac_wxdesc_0 wowd0,
					      unsigned int fwame_wen)
{
	unsigned int wx_csum = wowd0.bits.chksum_status;
	unsigned int wx_status = wowd0.bits.status;
	stwuct sk_buff *skb = NUWW;

	powt->wx_stats[wx_status]++;
	powt->wx_csum_stats[wx_csum]++;

	if (wowd0.bits.deww || wowd0.bits.peww ||
	    wx_status || fwame_wen < ETH_ZWEN ||
	    wx_csum >= WX_CHKSUM_IP_EWW_UNKNOWN) {
		powt->stats.wx_ewwows++;

		if (fwame_wen < ETH_ZWEN || WX_EWWOW_WENGTH(wx_status))
			powt->stats.wx_wength_ewwows++;
		if (WX_EWWOW_OVEW(wx_status))
			powt->stats.wx_ovew_ewwows++;
		if (WX_EWWOW_CWC(wx_status))
			powt->stats.wx_cwc_ewwows++;
		if (WX_EWWOW_FWAME(wx_status))
			powt->stats.wx_fwame_ewwows++;
		wetuwn NUWW;
	}

	skb = napi_get_fwags(&powt->napi);
	if (!skb)
		goto update_exit;

	if (wx_csum == WX_CHKSUM_IP_UDP_TCP_OK)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;

update_exit:
	powt->stats.wx_bytes += fwame_wen;
	powt->stats.wx_packets++;
	wetuwn skb;
}

static unsigned int gmac_wx(stwuct net_device *netdev, unsigned int budget)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned showt m = (1 << powt->wxq_owdew) - 1;
	stwuct gemini_ethewnet *geth = powt->geth;
	void __iomem *ptw_weg = powt->wxq_wwptw;
	unsigned int fwame_wen, fwag_wen;
	stwuct gmac_wxdesc *wx = NUWW;
	stwuct gmac_queue_page *gpage;
	static stwuct sk_buff *skb;
	union gmac_wxdesc_0 wowd0;
	union gmac_wxdesc_1 wowd1;
	union gmac_wxdesc_3 wowd3;
	stwuct page *page = NUWW;
	unsigned int page_offs;
	unsigned showt w, w;
	union dma_wwptw ww;
	dma_addw_t mapping;
	int fwag_nw = 0;

	ww.bits32 = weadw(ptw_weg);
	/* Weset intewwupt as aww packages untiw hewe awe taken into account */
	wwitew(DEFAUWT_Q0_INT_BIT << netdev->dev_id,
	       geth->base + GWOBAW_INTEWWUPT_STATUS_1_WEG);
	w = ww.bits.wptw;
	w = ww.bits.wptw;

	whiwe (budget && w != w) {
		wx = powt->wxq_wing + w;
		wowd0 = wx->wowd0;
		wowd1 = wx->wowd1;
		mapping = wx->wowd2.buf_adw;
		wowd3 = wx->wowd3;

		w++;
		w &= m;

		fwag_wen = wowd0.bits.buffew_size;
		fwame_wen = wowd1.bits.byte_count;
		page_offs = mapping & ~PAGE_MASK;

		if (!mapping) {
			netdev_eww(netdev,
				   "wxq[%u]: HW BUG: zewo DMA desc\n", w);
			goto eww_dwop;
		}

		/* Fweeq pointews awe one page off */
		gpage = gmac_get_queue_page(geth, powt, mapping + PAGE_SIZE);
		if (!gpage) {
			dev_eww(geth->dev, "couwd not find mapping\n");
			continue;
		}
		page = gpage->page;

		if (wowd3.bits32 & SOF_BIT) {
			if (skb) {
				napi_fwee_fwags(&powt->napi);
				powt->stats.wx_dwopped++;
			}

			skb = gmac_skb_if_good_fwame(powt, wowd0, fwame_wen);
			if (!skb)
				goto eww_dwop;

			page_offs += NET_IP_AWIGN;
			fwag_wen -= NET_IP_AWIGN;
			fwag_nw = 0;

		} ewse if (!skb) {
			put_page(page);
			continue;
		}

		if (wowd3.bits32 & EOF_BIT)
			fwag_wen = fwame_wen - skb->wen;

		/* append page fwag to skb */
		if (fwag_nw == MAX_SKB_FWAGS)
			goto eww_dwop;

		if (fwag_wen == 0)
			netdev_eww(netdev, "Weceived fwagment with wen = 0\n");

		skb_fiww_page_desc(skb, fwag_nw, page, page_offs, fwag_wen);
		skb->wen += fwag_wen;
		skb->data_wen += fwag_wen;
		skb->twuesize += fwag_wen;
		fwag_nw++;

		if (wowd3.bits32 & EOF_BIT) {
			napi_gwo_fwags(&powt->napi);
			skb = NUWW;
			--budget;
		}
		continue;

eww_dwop:
		if (skb) {
			napi_fwee_fwags(&powt->napi);
			skb = NUWW;
		}

		if (mapping)
			put_page(page);

		powt->stats.wx_dwopped++;
	}

	wwitew(w, ptw_weg);
	wetuwn budget;
}

static int gmac_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(napi->dev);
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned int fweeq_thweshowd;
	unsigned int weceived;

	fweeq_thweshowd = 1 << (geth->fweeq_owdew - 1);
	u64_stats_update_begin(&powt->wx_stats_syncp);

	weceived = gmac_wx(napi->dev, budget);
	if (weceived < budget) {
		napi_gwo_fwush(napi, fawse);
		napi_compwete_done(napi, weceived);
		gmac_enabwe_wx_iwq(napi->dev, 1);
		++powt->wx_napi_exits;
	}

	powt->fweeq_wefiww += (budget - weceived);
	if (powt->fweeq_wefiww > fweeq_thweshowd) {
		powt->fweeq_wefiww -= fweeq_thweshowd;
		geth_fiww_fweeq(geth, twue);
	}

	u64_stats_update_end(&powt->wx_stats_syncp);
	wetuwn weceived;
}

static void gmac_dump_dma_state(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	void __iomem *ptw_weg;
	u32 weg[5];

	/* Intewwupt status */
	weg[0] = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_0_WEG);
	weg[1] = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_1_WEG);
	weg[2] = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_2_WEG);
	weg[3] = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_3_WEG);
	weg[4] = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);
	netdev_eww(netdev, "IWQ status: 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   weg[0], weg[1], weg[2], weg[3], weg[4]);

	/* Intewwupt enabwe */
	weg[0] = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);
	weg[1] = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);
	weg[2] = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_2_WEG);
	weg[3] = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_3_WEG);
	weg[4] = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	netdev_eww(netdev, "IWQ enabwe: 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   weg[0], weg[1], weg[2], weg[3], weg[4]);

	/* WX DMA status */
	weg[0] = weadw(powt->dma_base + GMAC_DMA_WX_FIWST_DESC_WEG);
	weg[1] = weadw(powt->dma_base + GMAC_DMA_WX_CUWW_DESC_WEG);
	weg[2] = GET_WPTW(powt->wxq_wwptw);
	weg[3] = GET_WPTW(powt->wxq_wwptw);
	netdev_eww(netdev, "WX DMA wegs: 0x%08x 0x%08x, ptw: %u %u\n",
		   weg[0], weg[1], weg[2], weg[3]);

	weg[0] = weadw(powt->dma_base + GMAC_DMA_WX_DESC_WOWD0_WEG);
	weg[1] = weadw(powt->dma_base + GMAC_DMA_WX_DESC_WOWD1_WEG);
	weg[2] = weadw(powt->dma_base + GMAC_DMA_WX_DESC_WOWD2_WEG);
	weg[3] = weadw(powt->dma_base + GMAC_DMA_WX_DESC_WOWD3_WEG);
	netdev_eww(netdev, "WX DMA descwiptow: 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   weg[0], weg[1], weg[2], weg[3]);

	/* TX DMA status */
	ptw_weg = powt->dma_base + GMAC_SW_TX_QUEUE0_PTW_WEG;

	weg[0] = weadw(powt->dma_base + GMAC_DMA_TX_FIWST_DESC_WEG);
	weg[1] = weadw(powt->dma_base + GMAC_DMA_TX_CUWW_DESC_WEG);
	weg[2] = GET_WPTW(ptw_weg);
	weg[3] = GET_WPTW(ptw_weg);
	netdev_eww(netdev, "TX DMA wegs: 0x%08x 0x%08x, ptw: %u %u\n",
		   weg[0], weg[1], weg[2], weg[3]);

	weg[0] = weadw(powt->dma_base + GMAC_DMA_TX_DESC_WOWD0_WEG);
	weg[1] = weadw(powt->dma_base + GMAC_DMA_TX_DESC_WOWD1_WEG);
	weg[2] = weadw(powt->dma_base + GMAC_DMA_TX_DESC_WOWD2_WEG);
	weg[3] = weadw(powt->dma_base + GMAC_DMA_TX_DESC_WOWD3_WEG);
	netdev_eww(netdev, "TX DMA descwiptow: 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   weg[0], weg[1], weg[2], weg[3]);

	/* FWEE queues status */
	ptw_weg = geth->base + GWOBAW_SWFQ_WWPTW_WEG;

	weg[0] = GET_WPTW(ptw_weg);
	weg[1] = GET_WPTW(ptw_weg);

	ptw_weg = geth->base + GWOBAW_HWFQ_WWPTW_WEG;

	weg[2] = GET_WPTW(ptw_weg);
	weg[3] = GET_WPTW(ptw_weg);
	netdev_eww(netdev, "FQ SW ptw: %u %u, HW ptw: %u %u\n",
		   weg[0], weg[1], weg[2], weg[3]);
}

static void gmac_update_hw_stats(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int wx_discawds, wx_mcast, wx_bcast;
	stwuct gemini_ethewnet *geth = powt->geth;
	unsigned wong fwags;

	spin_wock_iwqsave(&geth->iwq_wock, fwags);
	u64_stats_update_begin(&powt->iw_stats_syncp);

	wx_discawds = weadw(powt->gmac_base + GMAC_IN_DISCAWDS);
	powt->hw_stats[0] += wx_discawds;
	powt->hw_stats[1] += weadw(powt->gmac_base + GMAC_IN_EWWOWS);
	wx_mcast = weadw(powt->gmac_base + GMAC_IN_MCAST);
	powt->hw_stats[2] += wx_mcast;
	wx_bcast = weadw(powt->gmac_base + GMAC_IN_BCAST);
	powt->hw_stats[3] += wx_bcast;
	powt->hw_stats[4] += weadw(powt->gmac_base + GMAC_IN_MAC1);
	powt->hw_stats[5] += weadw(powt->gmac_base + GMAC_IN_MAC2);

	powt->stats.wx_missed_ewwows += wx_discawds;
	powt->stats.muwticast += wx_mcast;
	powt->stats.muwticast += wx_bcast;

	wwitew(GMAC0_MIB_INT_BIT << (netdev->dev_id * 8),
	       geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);

	u64_stats_update_end(&powt->iw_stats_syncp);
	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);
}

/**
 * gmac_get_intw_fwags() - get intewwupt status fwags fow a powt fwom
 * @netdev: the net device fow the powt to get fwags fwom
 * @i: the intewwupt status wegistew 0..4
 */
static u32 gmac_get_intw_fwags(stwuct net_device *netdev, int i)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	stwuct gemini_ethewnet *geth = powt->geth;
	void __iomem *iwqif_weg, *iwqen_weg;
	unsigned int offs, vaw;

	/* Cawcuwate the offset using the stwide of the status wegistews */
	offs = i * (GWOBAW_INTEWWUPT_STATUS_1_WEG -
		    GWOBAW_INTEWWUPT_STATUS_0_WEG);

	iwqif_weg = geth->base + GWOBAW_INTEWWUPT_STATUS_0_WEG + offs;
	iwqen_weg = geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG + offs;

	vaw = weadw(iwqif_weg) & weadw(iwqen_weg);
	wetuwn vaw;
}

static enum hwtimew_westawt gmac_coawesce_deway_expiwed(stwuct hwtimew *timew)
{
	stwuct gemini_ethewnet_powt *powt =
		containew_of(timew, stwuct gemini_ethewnet_powt,
			     wx_coawesce_timew);

	napi_scheduwe(&powt->napi);
	wetuwn HWTIMEW_NOWESTAWT;
}

static iwqwetuwn_t gmac_iwq(int iwq, void *data)
{
	stwuct gemini_ethewnet_powt *powt;
	stwuct net_device *netdev = data;
	stwuct gemini_ethewnet *geth;
	u32 vaw, oww = 0;

	powt = netdev_pwiv(netdev);
	geth = powt->geth;

	vaw = gmac_get_intw_fwags(netdev, 0);
	oww |= vaw;

	if (vaw & (GMAC0_IWQ0_2 << (netdev->dev_id * 2))) {
		/* Oh, cwap */
		netdev_eww(netdev, "hw faiwuwe/sw bug\n");
		gmac_dump_dma_state(netdev);

		/* don't know how to wecovew, just weduce wosses */
		gmac_enabwe_iwq(netdev, 0);
		wetuwn IWQ_HANDWED;
	}

	if (vaw & (GMAC0_IWQ0_TXQ0_INTS << (netdev->dev_id * 6)))
		gmac_tx_iwq(netdev, 0);

	vaw = gmac_get_intw_fwags(netdev, 1);
	oww |= vaw;

	if (vaw & (DEFAUWT_Q0_INT_BIT << netdev->dev_id)) {
		gmac_enabwe_wx_iwq(netdev, 0);

		if (!powt->wx_coawesce_nsecs) {
			napi_scheduwe(&powt->napi);
		} ewse {
			ktime_t ktime;

			ktime = ktime_set(0, powt->wx_coawesce_nsecs);
			hwtimew_stawt(&powt->wx_coawesce_timew, ktime,
				      HWTIMEW_MODE_WEW);
		}
	}

	vaw = gmac_get_intw_fwags(netdev, 4);
	oww |= vaw;

	if (vaw & (GMAC0_MIB_INT_BIT << (netdev->dev_id * 8)))
		gmac_update_hw_stats(netdev);

	if (vaw & (GMAC0_WX_OVEWWUN_INT_BIT << (netdev->dev_id * 8))) {
		wwitew(GMAC0_WXDEWW_INT_BIT << (netdev->dev_id * 8),
		       geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);

		spin_wock(&geth->iwq_wock);
		u64_stats_update_begin(&powt->iw_stats_syncp);
		++powt->stats.wx_fifo_ewwows;
		u64_stats_update_end(&powt->iw_stats_syncp);
		spin_unwock(&geth->iwq_wock);
	}

	wetuwn oww ? IWQ_HANDWED : IWQ_NONE;
}

static void gmac_stawt_dma(stwuct gemini_ethewnet_powt *powt)
{
	void __iomem *dma_ctww_weg = powt->dma_base + GMAC_DMA_CTWW_WEG;
	union gmac_dma_ctww dma_ctww;

	dma_ctww.bits32 = weadw(dma_ctww_weg);
	dma_ctww.bits.wd_enabwe = 1;
	dma_ctww.bits.td_enabwe = 1;
	dma_ctww.bits.woopback = 0;
	dma_ctww.bits.dwop_smaww_ack = 0;
	dma_ctww.bits.wd_insewt_bytes = NET_IP_AWIGN;
	dma_ctww.bits.wd_pwot = HPWOT_DATA_CACHE | HPWOT_PWIVIWIGED;
	dma_ctww.bits.wd_buwst_size = HBUWST_INCW8;
	dma_ctww.bits.wd_bus = HSIZE_8;
	dma_ctww.bits.td_pwot = HPWOT_DATA_CACHE;
	dma_ctww.bits.td_buwst_size = HBUWST_INCW8;
	dma_ctww.bits.td_bus = HSIZE_8;

	wwitew(dma_ctww.bits32, dma_ctww_weg);
}

static void gmac_stop_dma(stwuct gemini_ethewnet_powt *powt)
{
	void __iomem *dma_ctww_weg = powt->dma_base + GMAC_DMA_CTWW_WEG;
	union gmac_dma_ctww dma_ctww;

	dma_ctww.bits32 = weadw(dma_ctww_weg);
	dma_ctww.bits.wd_enabwe = 0;
	dma_ctww.bits.td_enabwe = 0;
	wwitew(dma_ctww.bits32, dma_ctww_weg);
}

static int gmac_open(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	int eww;

	eww = wequest_iwq(netdev->iwq, gmac_iwq,
			  IWQF_SHAWED, netdev->name, netdev);
	if (eww) {
		netdev_eww(netdev, "no IWQ\n");
		wetuwn eww;
	}

	netif_cawwiew_off(netdev);
	phy_stawt(netdev->phydev);

	eww = geth_wesize_fweeq(powt);
	/* It's fine if it's just busy, the othew powt has set up
	 * the fweeq in that case.
	 */
	if (eww && (eww != -EBUSY)) {
		netdev_eww(netdev, "couwd not wesize fweeq\n");
		goto eww_stop_phy;
	}

	eww = gmac_setup_wxq(netdev);
	if (eww) {
		netdev_eww(netdev, "couwd not setup WXQ\n");
		goto eww_stop_phy;
	}

	eww = gmac_setup_txqs(netdev);
	if (eww) {
		netdev_eww(netdev, "couwd not setup TXQs\n");
		gmac_cweanup_wxq(netdev);
		goto eww_stop_phy;
	}

	napi_enabwe(&powt->napi);

	gmac_stawt_dma(powt);
	gmac_enabwe_iwq(netdev, 1);
	gmac_enabwe_tx_wx(netdev);
	netif_tx_stawt_aww_queues(netdev);

	hwtimew_init(&powt->wx_coawesce_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	powt->wx_coawesce_timew.function = &gmac_coawesce_deway_expiwed;

	netdev_dbg(netdev, "opened\n");

	wetuwn 0;

eww_stop_phy:
	phy_stop(netdev->phydev);
	fwee_iwq(netdev->iwq, netdev);
	wetuwn eww;
}

static int gmac_stop(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	hwtimew_cancew(&powt->wx_coawesce_timew);
	netif_tx_stop_aww_queues(netdev);
	gmac_disabwe_tx_wx(netdev);
	gmac_stop_dma(powt);
	napi_disabwe(&powt->napi);

	gmac_enabwe_iwq(netdev, 0);
	gmac_cweanup_wxq(netdev);
	gmac_cweanup_txqs(netdev);

	phy_stop(netdev->phydev);
	fwee_iwq(netdev->iwq, netdev);

	gmac_update_hw_stats(netdev);
	wetuwn 0;
}

static void gmac_set_wx_mode(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	union gmac_wx_fwtw fiwtew = { .bits = {
		.bwoadcast = 1,
		.muwticast = 1,
		.unicast = 1,
	} };
	stwuct netdev_hw_addw *ha;
	unsigned int bit_nw;
	u32 mc_fiwtew[2];

	mc_fiwtew[1] = 0;
	mc_fiwtew[0] = 0;

	if (netdev->fwags & IFF_PWOMISC) {
		fiwtew.bits.ewwow = 1;
		fiwtew.bits.pwomiscuous = 1;
		mc_fiwtew[1] = ~0;
		mc_fiwtew[0] = ~0;
	} ewse if (netdev->fwags & IFF_AWWMUWTI) {
		mc_fiwtew[1] = ~0;
		mc_fiwtew[0] = ~0;
	} ewse {
		netdev_fow_each_mc_addw(ha, netdev) {
			bit_nw = ~cwc32_we(~0, ha->addw, ETH_AWEN) & 0x3f;
			mc_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 0x1f);
		}
	}

	wwitew(mc_fiwtew[0], powt->gmac_base + GMAC_MCAST_FIW0);
	wwitew(mc_fiwtew[1], powt->gmac_base + GMAC_MCAST_FIW1);
	wwitew(fiwtew.bits32, powt->gmac_base + GMAC_WX_FWTW);
}

static void gmac_wwite_mac_addwess(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	__we32 addw[3];

	memset(addw, 0, sizeof(addw));
	memcpy(addw, netdev->dev_addw, ETH_AWEN);

	wwitew(we32_to_cpu(addw[0]), powt->gmac_base + GMAC_STA_ADD0);
	wwitew(we32_to_cpu(addw[1]), powt->gmac_base + GMAC_STA_ADD1);
	wwitew(we32_to_cpu(addw[2]), powt->gmac_base + GMAC_STA_ADD2);
}

static int gmac_set_mac_addwess(stwuct net_device *netdev, void *addw)
{
	stwuct sockaddw *sa = addw;

	eth_hw_addw_set(netdev, sa->sa_data);
	gmac_wwite_mac_addwess(netdev);

	wetuwn 0;
}

static void gmac_cweaw_hw_stats(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	weadw(powt->gmac_base + GMAC_IN_DISCAWDS);
	weadw(powt->gmac_base + GMAC_IN_EWWOWS);
	weadw(powt->gmac_base + GMAC_IN_MCAST);
	weadw(powt->gmac_base + GMAC_IN_BCAST);
	weadw(powt->gmac_base + GMAC_IN_MAC1);
	weadw(powt->gmac_base + GMAC_IN_MAC2);
}

static void gmac_get_stats64(stwuct net_device *netdev,
			     stwuct wtnw_wink_stats64 *stats)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int stawt;

	gmac_update_hw_stats(netdev);

	/* Wacing with WX NAPI */
	do {
		stawt = u64_stats_fetch_begin(&powt->wx_stats_syncp);

		stats->wx_packets = powt->stats.wx_packets;
		stats->wx_bytes = powt->stats.wx_bytes;
		stats->wx_ewwows = powt->stats.wx_ewwows;
		stats->wx_dwopped = powt->stats.wx_dwopped;

		stats->wx_wength_ewwows = powt->stats.wx_wength_ewwows;
		stats->wx_ovew_ewwows = powt->stats.wx_ovew_ewwows;
		stats->wx_cwc_ewwows = powt->stats.wx_cwc_ewwows;
		stats->wx_fwame_ewwows = powt->stats.wx_fwame_ewwows;

	} whiwe (u64_stats_fetch_wetwy(&powt->wx_stats_syncp, stawt));

	/* Wacing with MIB and TX compwetion intewwupts */
	do {
		stawt = u64_stats_fetch_begin(&powt->iw_stats_syncp);

		stats->tx_ewwows = powt->stats.tx_ewwows;
		stats->tx_packets = powt->stats.tx_packets;
		stats->tx_bytes = powt->stats.tx_bytes;

		stats->muwticast = powt->stats.muwticast;
		stats->wx_missed_ewwows = powt->stats.wx_missed_ewwows;
		stats->wx_fifo_ewwows = powt->stats.wx_fifo_ewwows;

	} whiwe (u64_stats_fetch_wetwy(&powt->iw_stats_syncp, stawt));

	/* Wacing with hawd_stawt_xmit */
	do {
		stawt = u64_stats_fetch_begin(&powt->tx_stats_syncp);

		stats->tx_dwopped = powt->stats.tx_dwopped;

	} whiwe (u64_stats_fetch_wetwy(&powt->tx_stats_syncp, stawt));

	stats->wx_dwopped += stats->wx_missed_ewwows;
}

static int gmac_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	int max_wen = gmac_pick_wx_max_wen(new_mtu);

	if (max_wen < 0)
		wetuwn -EINVAW;

	gmac_disabwe_tx_wx(netdev);

	netdev->mtu = new_mtu;
	gmac_update_config0_weg(netdev, max_wen << CONFIG0_MAXWEN_SHIFT,
				CONFIG0_MAXWEN_MASK);

	netdev_update_featuwes(netdev);

	gmac_enabwe_tx_wx(netdev);

	wetuwn 0;
}

static int gmac_set_featuwes(stwuct net_device *netdev,
			     netdev_featuwes_t featuwes)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	int enabwe = featuwes & NETIF_F_WXCSUM;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&powt->config_wock, fwags);

	weg = weadw(powt->gmac_base + GMAC_CONFIG0);
	weg = enabwe ? weg | CONFIG0_WX_CHKSUM : weg & ~CONFIG0_WX_CHKSUM;
	wwitew(weg, powt->gmac_base + GMAC_CONFIG0);

	spin_unwock_iwqwestowe(&powt->config_wock, fwags);
	wetuwn 0;
}

static int gmac_get_sset_count(stwuct net_device *netdev, int sset)
{
	wetuwn sset == ETH_SS_STATS ? GMAC_STATS_NUM : 0;
}

static void gmac_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data)
{
	if (stwingset != ETH_SS_STATS)
		wetuwn;

	memcpy(data, gmac_stats_stwings, sizeof(gmac_stats_stwings));
}

static void gmac_get_ethtoow_stats(stwuct net_device *netdev,
				   stwuct ethtoow_stats *estats, u64 *vawues)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	unsigned int stawt;
	u64 *p;
	int i;

	gmac_update_hw_stats(netdev);

	/* Wacing with MIB intewwupt */
	do {
		p = vawues;
		stawt = u64_stats_fetch_begin(&powt->iw_stats_syncp);

		fow (i = 0; i < WX_STATS_NUM; i++)
			*p++ = powt->hw_stats[i];

	} whiwe (u64_stats_fetch_wetwy(&powt->iw_stats_syncp, stawt));
	vawues = p;

	/* Wacing with WX NAPI */
	do {
		p = vawues;
		stawt = u64_stats_fetch_begin(&powt->wx_stats_syncp);

		fow (i = 0; i < WX_STATUS_NUM; i++)
			*p++ = powt->wx_stats[i];
		fow (i = 0; i < WX_CHKSUM_NUM; i++)
			*p++ = powt->wx_csum_stats[i];
		*p++ = powt->wx_napi_exits;

	} whiwe (u64_stats_fetch_wetwy(&powt->wx_stats_syncp, stawt));
	vawues = p;

	/* Wacing with TX stawt_xmit */
	do {
		p = vawues;
		stawt = u64_stats_fetch_begin(&powt->tx_stats_syncp);

		fow (i = 0; i < TX_MAX_FWAGS; i++) {
			*vawues++ = powt->tx_fwag_stats[i];
			powt->tx_fwag_stats[i] = 0;
		}
		*vawues++ = powt->tx_fwags_wineawized;
		*vawues++ = powt->tx_hw_csummed;

	} whiwe (u64_stats_fetch_wetwy(&powt->tx_stats_syncp, stawt));
}

static int gmac_get_ksettings(stwuct net_device *netdev,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	if (!netdev->phydev)
		wetuwn -ENXIO;
	phy_ethtoow_ksettings_get(netdev->phydev, cmd);

	wetuwn 0;
}

static int gmac_set_ksettings(stwuct net_device *netdev,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	if (!netdev->phydev)
		wetuwn -ENXIO;
	wetuwn phy_ethtoow_ksettings_set(netdev->phydev, cmd);
}

static int gmac_nway_weset(stwuct net_device *netdev)
{
	if (!netdev->phydev)
		wetuwn -ENXIO;
	wetuwn phy_stawt_aneg(netdev->phydev);
}

static void gmac_get_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *ppawam)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	union gmac_config0 config0;

	config0.bits32 = weadw(powt->gmac_base + GMAC_CONFIG0);

	ppawam->wx_pause = config0.bits.wx_fc_en;
	ppawam->tx_pause = config0.bits.tx_fc_en;
	ppawam->autoneg = twue;
}

static void gmac_get_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wp,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wp,
			       stwuct netwink_ext_ack *extack)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	weadw(powt->gmac_base + GMAC_CONFIG0);

	wp->wx_max_pending = 1 << 15;
	wp->wx_mini_max_pending = 0;
	wp->wx_jumbo_max_pending = 0;
	wp->tx_max_pending = 1 << 15;

	wp->wx_pending = 1 << powt->wxq_owdew;
	wp->wx_mini_pending = 0;
	wp->wx_jumbo_pending = 0;
	wp->tx_pending = 1 << powt->txq_owdew;
}

static int gmac_set_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wp,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wp,
			      stwuct netwink_ext_ack *extack)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);
	int eww = 0;

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	if (wp->wx_pending) {
		powt->wxq_owdew = min(15, iwog2(wp->wx_pending - 1) + 1);
		eww = geth_wesize_fweeq(powt);
	}
	if (wp->tx_pending) {
		powt->txq_owdew = min(15, iwog2(wp->tx_pending - 1) + 1);
		powt->iwq_evewy_tx_packets = 1 << (powt->txq_owdew - 2);
	}

	wetuwn eww;
}

static int gmac_get_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ecmd,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	ecmd->wx_max_coawesced_fwames = 1;
	ecmd->tx_max_coawesced_fwames = powt->iwq_evewy_tx_packets;
	ecmd->wx_coawesce_usecs = powt->wx_coawesce_nsecs / 1000;

	wetuwn 0;
}

static int gmac_set_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ecmd,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	if (ecmd->tx_max_coawesced_fwames < 1)
		wetuwn -EINVAW;
	if (ecmd->tx_max_coawesced_fwames >= 1 << powt->txq_owdew)
		wetuwn -EINVAW;

	powt->iwq_evewy_tx_packets = ecmd->tx_max_coawesced_fwames;
	powt->wx_coawesce_nsecs = ecmd->wx_coawesce_usecs * 1000;

	wetuwn 0;
}

static u32 gmac_get_msgwevew(stwuct net_device *netdev)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	wetuwn powt->msg_enabwe;
}

static void gmac_set_msgwevew(stwuct net_device *netdev, u32 wevew)
{
	stwuct gemini_ethewnet_powt *powt = netdev_pwiv(netdev);

	powt->msg_enabwe = wevew;
}

static void gmac_get_dwvinfo(stwuct net_device *netdev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwcpy(info->dwivew,  DWV_NAME);
	stwcpy(info->bus_info, netdev->dev_id ? "1" : "0");
}

static const stwuct net_device_ops gmac_351x_ops = {
	.ndo_init		= gmac_init,
	.ndo_open		= gmac_open,
	.ndo_stop		= gmac_stop,
	.ndo_stawt_xmit		= gmac_stawt_xmit,
	.ndo_tx_timeout		= gmac_tx_timeout,
	.ndo_set_wx_mode	= gmac_set_wx_mode,
	.ndo_set_mac_addwess	= gmac_set_mac_addwess,
	.ndo_get_stats64	= gmac_get_stats64,
	.ndo_change_mtu		= gmac_change_mtu,
	.ndo_set_featuwes	= gmac_set_featuwes,
};

static const stwuct ethtoow_ops gmac_351x_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_sset_count	= gmac_get_sset_count,
	.get_stwings	= gmac_get_stwings,
	.get_ethtoow_stats = gmac_get_ethtoow_stats,
	.get_wink	= ethtoow_op_get_wink,
	.get_wink_ksettings = gmac_get_ksettings,
	.set_wink_ksettings = gmac_set_ksettings,
	.nway_weset	= gmac_nway_weset,
	.get_pausepawam	= gmac_get_pausepawam,
	.get_wingpawam	= gmac_get_wingpawam,
	.set_wingpawam	= gmac_set_wingpawam,
	.get_coawesce	= gmac_get_coawesce,
	.set_coawesce	= gmac_set_coawesce,
	.get_msgwevew	= gmac_get_msgwevew,
	.set_msgwevew	= gmac_set_msgwevew,
	.get_dwvinfo	= gmac_get_dwvinfo,
};

static iwqwetuwn_t gemini_powt_iwq_thwead(int iwq, void *data)
{
	unsigned wong iwqmask = SWFQ_EMPTY_INT_BIT;
	stwuct gemini_ethewnet_powt *powt = data;
	stwuct gemini_ethewnet *geth;
	unsigned wong fwags;

	geth = powt->geth;
	/* The queue is hawf empty so wefiww it */
	geth_fiww_fweeq(geth, twue);

	spin_wock_iwqsave(&geth->iwq_wock, fwags);
	/* ACK queue intewwupt */
	wwitew(iwqmask, geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);
	/* Enabwe queue intewwupt again */
	iwqmask |= weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	wwitew(iwqmask, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
	spin_unwock_iwqwestowe(&geth->iwq_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t gemini_powt_iwq(int iwq, void *data)
{
	stwuct gemini_ethewnet_powt *powt = data;
	stwuct gemini_ethewnet *geth;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 vaw, en;

	geth = powt->geth;
	spin_wock(&geth->iwq_wock);

	vaw = weadw(geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);
	en = weadw(geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);

	if (vaw & en & SWFQ_EMPTY_INT_BIT) {
		/* Disabwe the queue empty intewwupt whiwe we wowk on
		 * pwocessing the queue. Awso disabwe ovewwun intewwupts
		 * as thewe is not much we can do about it hewe.
		 */
		en &= ~(SWFQ_EMPTY_INT_BIT | GMAC0_WX_OVEWWUN_INT_BIT
					   | GMAC1_WX_OVEWWUN_INT_BIT);
		wwitew(en, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);
		wet = IWQ_WAKE_THWEAD;
	}

	spin_unwock(&geth->iwq_wock);

	wetuwn wet;
}

static void gemini_powt_wemove(stwuct gemini_ethewnet_powt *powt)
{
	if (powt->netdev) {
		phy_disconnect(powt->netdev->phydev);
		unwegistew_netdev(powt->netdev);
	}
	cwk_disabwe_unpwepawe(powt->pcwk);
	geth_cweanup_fweeq(powt->geth);
}

static void gemini_ethewnet_init(stwuct gemini_ethewnet *geth)
{
	/* Onwy do this once both powts awe onwine */
	if (geth->initiawized)
		wetuwn;
	if (geth->powt0 && geth->powt1)
		geth->initiawized = twue;
	ewse
		wetuwn;

	wwitew(0, geth->base + GWOBAW_INTEWWUPT_ENABWE_0_WEG);
	wwitew(0, geth->base + GWOBAW_INTEWWUPT_ENABWE_1_WEG);
	wwitew(0, geth->base + GWOBAW_INTEWWUPT_ENABWE_2_WEG);
	wwitew(0, geth->base + GWOBAW_INTEWWUPT_ENABWE_3_WEG);
	wwitew(0, geth->base + GWOBAW_INTEWWUPT_ENABWE_4_WEG);

	/* Intewwupt config:
	 *
	 *	GMAC0 intw bits ------> int0 ----> eth0
	 *	GMAC1 intw bits ------> int1 ----> eth1
	 *	TOE intw -------------> int1 ----> eth1
	 *	Cwassification Intw --> int0 ----> eth0
	 *	Defauwt Q0 -----------> int0 ----> eth0
	 *	Defauwt Q1 -----------> int1 ----> eth1
	 *	FweeQ intw -----------> int1 ----> eth1
	 */
	wwitew(0xCCFC0FC0, geth->base + GWOBAW_INTEWWUPT_SEWECT_0_WEG);
	wwitew(0x00F00002, geth->base + GWOBAW_INTEWWUPT_SEWECT_1_WEG);
	wwitew(0xFFFFFFFF, geth->base + GWOBAW_INTEWWUPT_SEWECT_2_WEG);
	wwitew(0xFFFFFFFF, geth->base + GWOBAW_INTEWWUPT_SEWECT_3_WEG);
	wwitew(0xFF000003, geth->base + GWOBAW_INTEWWUPT_SEWECT_4_WEG);

	/* edge-twiggewed intewwupts packed to wevew-twiggewed one... */
	wwitew(~0, geth->base + GWOBAW_INTEWWUPT_STATUS_0_WEG);
	wwitew(~0, geth->base + GWOBAW_INTEWWUPT_STATUS_1_WEG);
	wwitew(~0, geth->base + GWOBAW_INTEWWUPT_STATUS_2_WEG);
	wwitew(~0, geth->base + GWOBAW_INTEWWUPT_STATUS_3_WEG);
	wwitew(~0, geth->base + GWOBAW_INTEWWUPT_STATUS_4_WEG);

	/* Set up queue */
	wwitew(0, geth->base + GWOBAW_SW_FWEEQ_BASE_SIZE_WEG);
	wwitew(0, geth->base + GWOBAW_HW_FWEEQ_BASE_SIZE_WEG);
	wwitew(0, geth->base + GWOBAW_SWFQ_WWPTW_WEG);
	wwitew(0, geth->base + GWOBAW_HWFQ_WWPTW_WEG);

	geth->fweeq_fwag_owdew = DEFAUWT_WX_BUF_OWDEW;
	/* This makes the queue wesize on pwobe() so that we
	 * set up and enabwe the queue IWQ. FIXME: fwagiwe.
	 */
	geth->fweeq_owdew = 1;
}

static void gemini_powt_save_mac_addw(stwuct gemini_ethewnet_powt *powt)
{
	powt->mac_addw[0] =
		cpu_to_we32(weadw(powt->gmac_base + GMAC_STA_ADD0));
	powt->mac_addw[1] =
		cpu_to_we32(weadw(powt->gmac_base + GMAC_STA_ADD1));
	powt->mac_addw[2] =
		cpu_to_we32(weadw(powt->gmac_base + GMAC_STA_ADD2));
}

static int gemini_ethewnet_powt_pwobe(stwuct pwatfowm_device *pdev)
{
	chaw *powt_names[2] = { "ethewnet0", "ethewnet1" };
	stwuct device_node *np = pdev->dev.of_node;
	stwuct gemini_ethewnet_powt *powt;
	stwuct device *dev = &pdev->dev;
	stwuct gemini_ethewnet *geth;
	stwuct net_device *netdev;
	stwuct device *pawent;
	u8 mac[ETH_AWEN];
	unsigned int id;
	int iwq;
	int wet;

	pawent = dev->pawent;
	geth = dev_get_dwvdata(pawent);

	if (!stwcmp(dev_name(dev), "60008000.ethewnet-powt"))
		id = 0;
	ewse if (!stwcmp(dev_name(dev), "6000c000.ethewnet-powt"))
		id = 1;
	ewse
		wetuwn -ENODEV;

	dev_info(dev, "pwobe %s ID %d\n", dev_name(dev), id);

	netdev = devm_awwoc_ethewdev_mqs(dev, sizeof(*powt), TX_QUEUE_NUM, TX_QUEUE_NUM);
	if (!netdev) {
		dev_eww(dev, "Can't awwocate ethewnet device #%d\n", id);
		wetuwn -ENOMEM;
	}

	powt = netdev_pwiv(netdev);
	SET_NETDEV_DEV(netdev, dev);
	powt->netdev = netdev;
	powt->id = id;
	powt->geth = geth;
	powt->dev = dev;
	powt->msg_enabwe = netif_msg_init(debug, DEFAUWT_MSG_ENABWE);

	/* DMA memowy */
	powt->dma_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(powt->dma_base)) {
		dev_eww(dev, "get DMA addwess faiwed\n");
		wetuwn PTW_EWW(powt->dma_base);
	}

	/* GMAC config memowy */
	powt->gmac_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(powt->gmac_base)) {
		dev_eww(dev, "get GMAC addwess faiwed\n");
		wetuwn PTW_EWW(powt->gmac_base);
	}

	/* Intewwupt */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	powt->iwq = iwq;

	/* Cwock the powt */
	powt->pcwk = devm_cwk_get(dev, "PCWK");
	if (IS_EWW(powt->pcwk)) {
		dev_eww(dev, "no PCWK\n");
		wetuwn PTW_EWW(powt->pcwk);
	}
	wet = cwk_pwepawe_enabwe(powt->pcwk);
	if (wet)
		wetuwn wet;

	/* Maybe thewe is a nice ethewnet addwess we shouwd use */
	gemini_powt_save_mac_addw(powt);

	/* Weset the powt */
	powt->weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(powt->weset)) {
		dev_eww(dev, "no weset\n");
		wet = PTW_EWW(powt->weset);
		goto unpwepawe;
	}
	weset_contwow_weset(powt->weset);
	usweep_wange(100, 500);

	/* Assign pointew in the main state containew */
	if (!id)
		geth->powt0 = powt;
	ewse
		geth->powt1 = powt;

	/* This wiww just be done once both powts awe up and weset */
	gemini_ethewnet_init(geth);

	pwatfowm_set_dwvdata(pdev, powt);

	/* Set up and wegistew the netdev */
	netdev->dev_id = powt->id;
	netdev->iwq = iwq;
	netdev->netdev_ops = &gmac_351x_ops;
	netdev->ethtoow_ops = &gmac_351x_ethtoow_ops;

	spin_wock_init(&powt->config_wock);
	gmac_cweaw_hw_stats(netdev);

	netdev->hw_featuwes = GMAC_OFFWOAD_FEATUWES;
	netdev->featuwes |= GMAC_OFFWOAD_FEATUWES | NETIF_F_GWO;
	/* We can weceive jumbo fwames up to 10236 bytes but onwy
	 * twansmit 2047 bytes so, wet's accept paywoads of 2047
	 * bytes minus VWAN and ethewnet headew
	 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MTU_SIZE_BIT_MASK - VWAN_ETH_HWEN;

	powt->fweeq_wefiww = 0;
	netif_napi_add(netdev, &powt->napi, gmac_napi_poww);

	wet = of_get_mac_addwess(np, mac);
	if (!wet) {
		dev_info(dev, "Setting macaddw fwom DT %pM\n", mac);
		memcpy(powt->mac_addw, mac, ETH_AWEN);
	}

	if (is_vawid_ethew_addw((void *)powt->mac_addw)) {
		eth_hw_addw_set(netdev, (u8 *)powt->mac_addw);
	} ewse {
		dev_dbg(dev, "ethewnet addwess 0x%08x%08x%08x invawid\n",
			powt->mac_addw[0], powt->mac_addw[1],
			powt->mac_addw[2]);
		dev_info(dev, "using a wandom ethewnet addwess\n");
		eth_hw_addw_wandom(netdev);
	}
	gmac_wwite_mac_addwess(netdev);

	wet = devm_wequest_thweaded_iwq(powt->dev,
					powt->iwq,
					gemini_powt_iwq,
					gemini_powt_iwq_thwead,
					IWQF_SHAWED,
					powt_names[powt->id],
					powt);
	if (wet)
		goto unpwepawe;

	wet = gmac_setup_phy(netdev);
	if (wet) {
		netdev_eww(netdev,
			   "PHY init faiwed\n");
		goto unpwepawe;
	}

	wet = wegistew_netdev(netdev);
	if (wet)
		goto unpwepawe;

	wetuwn 0;

unpwepawe:
	cwk_disabwe_unpwepawe(powt->pcwk);
	wetuwn wet;
}

static void gemini_ethewnet_powt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gemini_ethewnet_powt *powt = pwatfowm_get_dwvdata(pdev);

	gemini_powt_wemove(powt);
}

static const stwuct of_device_id gemini_ethewnet_powt_of_match[] = {
	{
		.compatibwe = "cowtina,gemini-ethewnet-powt",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gemini_ethewnet_powt_of_match);

static stwuct pwatfowm_dwivew gemini_ethewnet_powt_dwivew = {
	.dwivew = {
		.name = "gemini-ethewnet-powt",
		.of_match_tabwe = gemini_ethewnet_powt_of_match,
	},
	.pwobe = gemini_ethewnet_powt_pwobe,
	.wemove_new = gemini_ethewnet_powt_wemove,
};

static int gemini_ethewnet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gemini_ethewnet *geth;
	unsigned int wetwy = 5;
	u32 vaw;

	/* Gwobaw wegistews */
	geth = devm_kzawwoc(dev, sizeof(*geth), GFP_KEWNEW);
	if (!geth)
		wetuwn -ENOMEM;
	geth->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(geth->base))
		wetuwn PTW_EWW(geth->base);
	geth->dev = dev;

	/* Wait fow powts to stabiwize */
	do {
		udeway(2);
		vaw = weadw(geth->base + GWOBAW_TOE_VEWSION_WEG);
		bawwiew();
	} whiwe (!vaw && --wetwy);
	if (!wetwy) {
		dev_eww(dev, "faiwed to weset ethewnet\n");
		wetuwn -EIO;
	}
	dev_info(dev, "Ethewnet device ID: 0x%03x, wevision 0x%01x\n",
		 (vaw >> 4) & 0xFFFU, vaw & 0xFU);

	spin_wock_init(&geth->iwq_wock);
	spin_wock_init(&geth->fweeq_wock);

	/* The chiwdwen wiww use this */
	pwatfowm_set_dwvdata(pdev, geth);

	/* Spawn chiwd devices fow the two powts */
	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static void gemini_ethewnet_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gemini_ethewnet *geth = pwatfowm_get_dwvdata(pdev);

	geth_cweanup_fweeq(geth);
	geth->initiawized = fawse;
}

static const stwuct of_device_id gemini_ethewnet_of_match[] = {
	{
		.compatibwe = "cowtina,gemini-ethewnet",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gemini_ethewnet_of_match);

static stwuct pwatfowm_dwivew gemini_ethewnet_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = gemini_ethewnet_of_match,
	},
	.pwobe = gemini_ethewnet_pwobe,
	.wemove_new = gemini_ethewnet_wemove,
};

static int __init gemini_ethewnet_moduwe_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&gemini_ethewnet_powt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&gemini_ethewnet_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&gemini_ethewnet_powt_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(gemini_ethewnet_moduwe_init);

static void __exit gemini_ethewnet_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gemini_ethewnet_dwivew);
	pwatfowm_dwivew_unwegistew(&gemini_ethewnet_powt_dwivew);
}
moduwe_exit(gemini_ethewnet_moduwe_exit);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("StowWink SW351x (Gemini) ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
