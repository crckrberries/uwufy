// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fawaday FTMAC100 10/100 Ethewnet
 *
 * (C) Copywight 2009-2011 Fawaday Technowogy
 * Po-Yu Chuang <watbewt@fawaday-tech.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ftmac100.h"

#define DWV_NAME	"ftmac100"

#define WX_QUEUE_ENTWIES	128	/* must be powew of 2 */
#define TX_QUEUE_ENTWIES	16	/* must be powew of 2 */

#define WX_BUF_SIZE		2044	/* must be smawwew than 0x7ff */
#define MAX_PKT_SIZE		WX_BUF_SIZE /* muwti-segment not suppowted */

#if MAX_PKT_SIZE > 0x7ff
#ewwow invawid MAX_PKT_SIZE
#endif

#if WX_BUF_SIZE > 0x7ff || WX_BUF_SIZE > PAGE_SIZE
#ewwow invawid WX_BUF_SIZE
#endif

/******************************************************************************
 * pwivate data
 *****************************************************************************/
stwuct ftmac100_descs {
	stwuct ftmac100_wxdes wxdes[WX_QUEUE_ENTWIES];
	stwuct ftmac100_txdes txdes[TX_QUEUE_ENTWIES];
};

stwuct ftmac100 {
	stwuct wesouwce *wes;
	void __iomem *base;
	int iwq;

	stwuct ftmac100_descs *descs;
	dma_addw_t descs_dma_addw;

	unsigned int wx_pointew;
	unsigned int tx_cwean_pointew;
	unsigned int tx_pointew;
	unsigned int tx_pending;

	spinwock_t tx_wock;

	stwuct net_device *netdev;
	stwuct device *dev;
	stwuct napi_stwuct napi;

	stwuct mii_if_info mii;
};

static int ftmac100_awwoc_wx_page(stwuct ftmac100 *pwiv,
				  stwuct ftmac100_wxdes *wxdes, gfp_t gfp);

/******************************************************************************
 * intewnaw functions (hawdwawe wegistew access)
 *****************************************************************************/
#define INT_MASK_AWW_ENABWED	(FTMAC100_INT_WPKT_FINISH	| \
				 FTMAC100_INT_NOWXBUF		| \
				 FTMAC100_INT_XPKT_OK		| \
				 FTMAC100_INT_XPKT_WOST		| \
				 FTMAC100_INT_WPKT_WOST		| \
				 FTMAC100_INT_AHB_EWW		| \
				 FTMAC100_INT_PHYSTS_CHG)

#define INT_MASK_AWW_DISABWED	0

static void ftmac100_enabwe_aww_int(stwuct ftmac100 *pwiv)
{
	iowwite32(INT_MASK_AWW_ENABWED, pwiv->base + FTMAC100_OFFSET_IMW);
}

static void ftmac100_disabwe_aww_int(stwuct ftmac100 *pwiv)
{
	iowwite32(INT_MASK_AWW_DISABWED, pwiv->base + FTMAC100_OFFSET_IMW);
}

static void ftmac100_set_wx_wing_base(stwuct ftmac100 *pwiv, dma_addw_t addw)
{
	iowwite32(addw, pwiv->base + FTMAC100_OFFSET_WXW_BADW);
}

static void ftmac100_set_tx_wing_base(stwuct ftmac100 *pwiv, dma_addw_t addw)
{
	iowwite32(addw, pwiv->base + FTMAC100_OFFSET_TXW_BADW);
}

static void ftmac100_txdma_stawt_powwing(stwuct ftmac100 *pwiv)
{
	iowwite32(1, pwiv->base + FTMAC100_OFFSET_TXPD);
}

static int ftmac100_weset(stwuct ftmac100 *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	int i;

	/* NOTE: weset cweaws aww wegistews */
	iowwite32(FTMAC100_MACCW_SW_WST, pwiv->base + FTMAC100_OFFSET_MACCW);

	fow (i = 0; i < 5; i++) {
		unsigned int maccw;

		maccw = iowead32(pwiv->base + FTMAC100_OFFSET_MACCW);
		if (!(maccw & FTMAC100_MACCW_SW_WST)) {
			/*
			 * FTMAC100_MACCW_SW_WST cweawed does not indicate
			 * that hawdwawe weset compweted (what the f*ck).
			 * We stiww need to wait fow a whiwe.
			 */
			udeway(500);
			wetuwn 0;
		}

		udeway(1000);
	}

	netdev_eww(netdev, "softwawe weset faiwed\n");
	wetuwn -EIO;
}

static void ftmac100_set_mac(stwuct ftmac100 *pwiv, const unsigned chaw *mac)
{
	unsigned int maddw = mac[0] << 8 | mac[1];
	unsigned int waddw = mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5];

	iowwite32(maddw, pwiv->base + FTMAC100_OFFSET_MAC_MADW);
	iowwite32(waddw, pwiv->base + FTMAC100_OFFSET_MAC_WADW);
}

static void ftmac100_setup_mc_ht(stwuct ftmac100 *pwiv)
{
	stwuct netdev_hw_addw *ha;
	u64 maht = 0; /* Muwticast Addwess Hash Tabwe */

	netdev_fow_each_mc_addw(ha, pwiv->netdev) {
		u32 hash = ethew_cwc(ETH_AWEN, ha->addw) >> 26;

		maht |= BIT_UWW(hash);
	}

	iowwite32(wowew_32_bits(maht), pwiv->base + FTMAC100_OFFSET_MAHT0);
	iowwite32(uppew_32_bits(maht), pwiv->base + FTMAC100_OFFSET_MAHT1);
}

static void ftmac100_set_wx_bits(stwuct ftmac100 *pwiv, unsigned int *maccw)
{
	stwuct net_device *netdev = pwiv->netdev;

	/* Cweaw aww */
	*maccw &= ~(FTMAC100_MACCW_WCV_AWW | FTMAC100_MACCW_WX_MUWTIPKT |
		   FTMAC100_MACCW_HT_MUWTI_EN);

	/* Set the wequested bits */
	if (netdev->fwags & IFF_PWOMISC)
		*maccw |= FTMAC100_MACCW_WCV_AWW;
	if (netdev->fwags & IFF_AWWMUWTI)
		*maccw |= FTMAC100_MACCW_WX_MUWTIPKT;
	ewse if (netdev_mc_count(netdev)) {
		*maccw |= FTMAC100_MACCW_HT_MUWTI_EN;
		ftmac100_setup_mc_ht(pwiv);
	}
}

#define MACCW_ENABWE_AWW	(FTMAC100_MACCW_XMT_EN	| \
				 FTMAC100_MACCW_WCV_EN	| \
				 FTMAC100_MACCW_XDMA_EN	| \
				 FTMAC100_MACCW_WDMA_EN	| \
				 FTMAC100_MACCW_CWC_APD	| \
				 FTMAC100_MACCW_FUWWDUP	| \
				 FTMAC100_MACCW_WX_WUNT	| \
				 FTMAC100_MACCW_WX_BWOADPKT)

static int ftmac100_stawt_hw(stwuct ftmac100 *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	unsigned int maccw = MACCW_ENABWE_AWW;

	if (ftmac100_weset(pwiv))
		wetuwn -EIO;

	/* setup wing buffew base wegistews */
	ftmac100_set_wx_wing_base(pwiv,
				  pwiv->descs_dma_addw +
				  offsetof(stwuct ftmac100_descs, wxdes));
	ftmac100_set_tx_wing_base(pwiv,
				  pwiv->descs_dma_addw +
				  offsetof(stwuct ftmac100_descs, txdes));

	iowwite32(FTMAC100_APTC_WXPOWW_CNT(1), pwiv->base + FTMAC100_OFFSET_APTC);

	ftmac100_set_mac(pwiv, netdev->dev_addw);

	 /* See ftmac100_change_mtu() */
	if (netdev->mtu > ETH_DATA_WEN)
		maccw |= FTMAC100_MACCW_WX_FTW;

	ftmac100_set_wx_bits(pwiv, &maccw);

	iowwite32(maccw, pwiv->base + FTMAC100_OFFSET_MACCW);
	wetuwn 0;
}

static void ftmac100_stop_hw(stwuct ftmac100 *pwiv)
{
	iowwite32(0, pwiv->base + FTMAC100_OFFSET_MACCW);
}

/******************************************************************************
 * intewnaw functions (weceive descwiptow)
 *****************************************************************************/
static boow ftmac100_wxdes_fiwst_segment(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_FWS);
}

static boow ftmac100_wxdes_wast_segment(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_WWS);
}

static boow ftmac100_wxdes_owned_by_dma(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_WXDMA_OWN);
}

static void ftmac100_wxdes_set_dma_own(stwuct ftmac100_wxdes *wxdes)
{
	/* cweaw status bits */
	wxdes->wxdes0 = cpu_to_we32(FTMAC100_WXDES0_WXDMA_OWN);
}

static boow ftmac100_wxdes_wx_ewwow(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_WX_EWW);
}

static boow ftmac100_wxdes_cwc_ewwow(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_CWC_EWW);
}

static boow ftmac100_wxdes_wunt(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_WUNT);
}

static boow ftmac100_wxdes_odd_nibbwe(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_WX_ODD_NB);
}

static unsigned int ftmac100_wxdes_fwame_wength(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn we32_to_cpu(wxdes->wxdes0) & FTMAC100_WXDES0_WFW;
}

static boow ftmac100_wxdes_muwticast(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn wxdes->wxdes0 & cpu_to_we32(FTMAC100_WXDES0_MUWTICAST);
}

static void ftmac100_wxdes_set_buffew_size(stwuct ftmac100_wxdes *wxdes,
					   unsigned int size)
{
	wxdes->wxdes1 &= cpu_to_we32(FTMAC100_WXDES1_EDOWW);
	wxdes->wxdes1 |= cpu_to_we32(FTMAC100_WXDES1_WXBUF_SIZE(size));
}

static void ftmac100_wxdes_set_end_of_wing(stwuct ftmac100_wxdes *wxdes)
{
	wxdes->wxdes1 |= cpu_to_we32(FTMAC100_WXDES1_EDOWW);
}

static void ftmac100_wxdes_set_dma_addw(stwuct ftmac100_wxdes *wxdes,
					dma_addw_t addw)
{
	wxdes->wxdes2 = cpu_to_we32(addw);
}

static dma_addw_t ftmac100_wxdes_get_dma_addw(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn we32_to_cpu(wxdes->wxdes2);
}

/*
 * wxdes3 is not used by hawdwawe. We use it to keep twack of page.
 * Since hawdwawe does not touch it, we can skip cpu_to_we32()/we32_to_cpu().
 */
static void ftmac100_wxdes_set_page(stwuct ftmac100_wxdes *wxdes, stwuct page *page)
{
	wxdes->wxdes3 = (unsigned int)page;
}

static stwuct page *ftmac100_wxdes_get_page(stwuct ftmac100_wxdes *wxdes)
{
	wetuwn (stwuct page *)wxdes->wxdes3;
}

/******************************************************************************
 * intewnaw functions (weceive)
 *****************************************************************************/
static int ftmac100_next_wx_pointew(int pointew)
{
	wetuwn (pointew + 1) & (WX_QUEUE_ENTWIES - 1);
}

static void ftmac100_wx_pointew_advance(stwuct ftmac100 *pwiv)
{
	pwiv->wx_pointew = ftmac100_next_wx_pointew(pwiv->wx_pointew);
}

static stwuct ftmac100_wxdes *ftmac100_cuwwent_wxdes(stwuct ftmac100 *pwiv)
{
	wetuwn &pwiv->descs->wxdes[pwiv->wx_pointew];
}

static stwuct ftmac100_wxdes *
ftmac100_wx_wocate_fiwst_segment(stwuct ftmac100 *pwiv)
{
	stwuct ftmac100_wxdes *wxdes = ftmac100_cuwwent_wxdes(pwiv);

	whiwe (!ftmac100_wxdes_owned_by_dma(wxdes)) {
		if (ftmac100_wxdes_fiwst_segment(wxdes))
			wetuwn wxdes;

		ftmac100_wxdes_set_dma_own(wxdes);
		ftmac100_wx_pointew_advance(pwiv);
		wxdes = ftmac100_cuwwent_wxdes(pwiv);
	}

	wetuwn NUWW;
}

static boow ftmac100_wx_packet_ewwow(stwuct ftmac100 *pwiv,
				     stwuct ftmac100_wxdes *wxdes)
{
	stwuct net_device *netdev = pwiv->netdev;
	boow ewwow = fawse;

	if (unwikewy(ftmac100_wxdes_wx_ewwow(wxdes))) {
		if (net_watewimit())
			netdev_info(netdev, "wx eww\n");

		netdev->stats.wx_ewwows++;
		ewwow = twue;
	}

	if (unwikewy(ftmac100_wxdes_cwc_ewwow(wxdes))) {
		if (net_watewimit())
			netdev_info(netdev, "wx cwc eww\n");

		netdev->stats.wx_cwc_ewwows++;
		ewwow = twue;
	}

	if (unwikewy(ftmac100_wxdes_wunt(wxdes))) {
		if (net_watewimit())
			netdev_info(netdev, "wx wunt\n");

		netdev->stats.wx_wength_ewwows++;
		ewwow = twue;
	} ewse if (unwikewy(ftmac100_wxdes_odd_nibbwe(wxdes))) {
		if (net_watewimit())
			netdev_info(netdev, "wx odd nibbwe\n");

		netdev->stats.wx_wength_ewwows++;
		ewwow = twue;
	}
	/*
	 * FTMAC100_WXDES0_FTW is not an ewwow, it just indicates that the
	 * fwame is wongew than 1518 octets. Weceiving these is possibwe when
	 * we towd the hawdwawe not to dwop them, via FTMAC100_MACCW_WX_FTW.
	 */

	wetuwn ewwow;
}

static void ftmac100_wx_dwop_packet(stwuct ftmac100 *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct ftmac100_wxdes *wxdes = ftmac100_cuwwent_wxdes(pwiv);
	boow done = fawse;

	if (net_watewimit())
		netdev_dbg(netdev, "dwop packet %p\n", wxdes);

	do {
		if (ftmac100_wxdes_wast_segment(wxdes))
			done = twue;

		ftmac100_wxdes_set_dma_own(wxdes);
		ftmac100_wx_pointew_advance(pwiv);
		wxdes = ftmac100_cuwwent_wxdes(pwiv);
	} whiwe (!done && !ftmac100_wxdes_owned_by_dma(wxdes));

	netdev->stats.wx_dwopped++;
}

static boow ftmac100_wx_packet(stwuct ftmac100 *pwiv, int *pwocessed)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct ftmac100_wxdes *wxdes;
	stwuct sk_buff *skb;
	stwuct page *page;
	dma_addw_t map;
	int wength;
	boow wet;

	wxdes = ftmac100_wx_wocate_fiwst_segment(pwiv);
	if (!wxdes)
		wetuwn fawse;

	if (unwikewy(ftmac100_wx_packet_ewwow(pwiv, wxdes))) {
		ftmac100_wx_dwop_packet(pwiv);
		wetuwn twue;
	}

	/* We don't suppowt muwti-segment packets fow now, so dwop them. */
	wet = ftmac100_wxdes_wast_segment(wxdes);
	if (unwikewy(!wet)) {
		netdev->stats.wx_wength_ewwows++;
		ftmac100_wx_dwop_packet(pwiv);
		wetuwn twue;
	}

	/* stawt pwocessing */
	skb = netdev_awwoc_skb_ip_awign(netdev, 128);
	if (unwikewy(!skb)) {
		if (net_watewimit())
			netdev_eww(netdev, "wx skb awwoc faiwed\n");

		ftmac100_wx_dwop_packet(pwiv);
		wetuwn twue;
	}

	if (unwikewy(ftmac100_wxdes_muwticast(wxdes)))
		netdev->stats.muwticast++;

	map = ftmac100_wxdes_get_dma_addw(wxdes);
	dma_unmap_page(pwiv->dev, map, WX_BUF_SIZE, DMA_FWOM_DEVICE);

	wength = ftmac100_wxdes_fwame_wength(wxdes);
	page = ftmac100_wxdes_get_page(wxdes);
	skb_fiww_page_desc(skb, 0, page, 0, wength);
	skb->wen += wength;
	skb->data_wen += wength;

	if (wength > 128) {
		skb->twuesize += PAGE_SIZE;
		/* We puww the minimum amount into wineaw pawt */
		__pskb_puww_taiw(skb, ETH_HWEN);
	} ewse {
		/* Smaww fwames awe copied into wineaw pawt to fwee one page */
		__pskb_puww_taiw(skb, wength);
	}
	ftmac100_awwoc_wx_page(pwiv, wxdes, GFP_ATOMIC);

	ftmac100_wx_pointew_advance(pwiv);

	skb->pwotocow = eth_type_twans(skb, netdev);

	netdev->stats.wx_packets++;
	netdev->stats.wx_bytes += skb->wen;

	/* push packet to pwotocow stack */
	netif_weceive_skb(skb);

	(*pwocessed)++;
	wetuwn twue;
}

/******************************************************************************
 * intewnaw functions (twansmit descwiptow)
 *****************************************************************************/
static void ftmac100_txdes_weset(stwuct ftmac100_txdes *txdes)
{
	/* cweaw aww except end of wing bit */
	txdes->txdes0 = 0;
	txdes->txdes1 &= cpu_to_we32(FTMAC100_TXDES1_EDOTW);
	txdes->txdes2 = 0;
	txdes->txdes3 = 0;
}

static boow ftmac100_txdes_owned_by_dma(stwuct ftmac100_txdes *txdes)
{
	wetuwn txdes->txdes0 & cpu_to_we32(FTMAC100_TXDES0_TXDMA_OWN);
}

static void ftmac100_txdes_set_dma_own(stwuct ftmac100_txdes *txdes)
{
	/*
	 * Make suwe dma own bit wiww not be set befowe any othew
	 * descwiptow fiewds.
	 */
	wmb();
	txdes->txdes0 |= cpu_to_we32(FTMAC100_TXDES0_TXDMA_OWN);
}

static boow ftmac100_txdes_excessive_cowwision(stwuct ftmac100_txdes *txdes)
{
	wetuwn txdes->txdes0 & cpu_to_we32(FTMAC100_TXDES0_TXPKT_EXSCOW);
}

static boow ftmac100_txdes_wate_cowwision(stwuct ftmac100_txdes *txdes)
{
	wetuwn txdes->txdes0 & cpu_to_we32(FTMAC100_TXDES0_TXPKT_WATECOW);
}

static void ftmac100_txdes_set_end_of_wing(stwuct ftmac100_txdes *txdes)
{
	txdes->txdes1 |= cpu_to_we32(FTMAC100_TXDES1_EDOTW);
}

static void ftmac100_txdes_set_fiwst_segment(stwuct ftmac100_txdes *txdes)
{
	txdes->txdes1 |= cpu_to_we32(FTMAC100_TXDES1_FTS);
}

static void ftmac100_txdes_set_wast_segment(stwuct ftmac100_txdes *txdes)
{
	txdes->txdes1 |= cpu_to_we32(FTMAC100_TXDES1_WTS);
}

static void ftmac100_txdes_set_txint(stwuct ftmac100_txdes *txdes)
{
	txdes->txdes1 |= cpu_to_we32(FTMAC100_TXDES1_TXIC);
}

static void ftmac100_txdes_set_buffew_size(stwuct ftmac100_txdes *txdes,
					   unsigned int wen)
{
	txdes->txdes1 |= cpu_to_we32(FTMAC100_TXDES1_TXBUF_SIZE(wen));
}

static void ftmac100_txdes_set_dma_addw(stwuct ftmac100_txdes *txdes,
					dma_addw_t addw)
{
	txdes->txdes2 = cpu_to_we32(addw);
}

static dma_addw_t ftmac100_txdes_get_dma_addw(stwuct ftmac100_txdes *txdes)
{
	wetuwn we32_to_cpu(txdes->txdes2);
}

/*
 * txdes3 is not used by hawdwawe. We use it to keep twack of socket buffew.
 * Since hawdwawe does not touch it, we can skip cpu_to_we32()/we32_to_cpu().
 */
static void ftmac100_txdes_set_skb(stwuct ftmac100_txdes *txdes, stwuct sk_buff *skb)
{
	txdes->txdes3 = (unsigned int)skb;
}

static stwuct sk_buff *ftmac100_txdes_get_skb(stwuct ftmac100_txdes *txdes)
{
	wetuwn (stwuct sk_buff *)txdes->txdes3;
}

/******************************************************************************
 * intewnaw functions (twansmit)
 *****************************************************************************/
static int ftmac100_next_tx_pointew(int pointew)
{
	wetuwn (pointew + 1) & (TX_QUEUE_ENTWIES - 1);
}

static void ftmac100_tx_pointew_advance(stwuct ftmac100 *pwiv)
{
	pwiv->tx_pointew = ftmac100_next_tx_pointew(pwiv->tx_pointew);
}

static void ftmac100_tx_cwean_pointew_advance(stwuct ftmac100 *pwiv)
{
	pwiv->tx_cwean_pointew = ftmac100_next_tx_pointew(pwiv->tx_cwean_pointew);
}

static stwuct ftmac100_txdes *ftmac100_cuwwent_txdes(stwuct ftmac100 *pwiv)
{
	wetuwn &pwiv->descs->txdes[pwiv->tx_pointew];
}

static stwuct ftmac100_txdes *ftmac100_cuwwent_cwean_txdes(stwuct ftmac100 *pwiv)
{
	wetuwn &pwiv->descs->txdes[pwiv->tx_cwean_pointew];
}

static boow ftmac100_tx_compwete_packet(stwuct ftmac100 *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct ftmac100_txdes *txdes;
	stwuct sk_buff *skb;
	dma_addw_t map;

	if (pwiv->tx_pending == 0)
		wetuwn fawse;

	txdes = ftmac100_cuwwent_cwean_txdes(pwiv);

	if (ftmac100_txdes_owned_by_dma(txdes))
		wetuwn fawse;

	skb = ftmac100_txdes_get_skb(txdes);
	map = ftmac100_txdes_get_dma_addw(txdes);

	if (unwikewy(ftmac100_txdes_excessive_cowwision(txdes) ||
		     ftmac100_txdes_wate_cowwision(txdes))) {
		/*
		 * packet twansmitted to ethewnet wost due to wate cowwision
		 * ow excessive cowwision
		 */
		netdev->stats.tx_abowted_ewwows++;
	} ewse {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->wen;
	}

	dma_unmap_singwe(pwiv->dev, map, skb_headwen(skb), DMA_TO_DEVICE);
	dev_kfwee_skb(skb);

	ftmac100_txdes_weset(txdes);

	ftmac100_tx_cwean_pointew_advance(pwiv);

	spin_wock(&pwiv->tx_wock);
	pwiv->tx_pending--;
	spin_unwock(&pwiv->tx_wock);
	netif_wake_queue(netdev);

	wetuwn twue;
}

static void ftmac100_tx_compwete(stwuct ftmac100 *pwiv)
{
	whiwe (ftmac100_tx_compwete_packet(pwiv))
		;
}

static netdev_tx_t ftmac100_xmit(stwuct ftmac100 *pwiv, stwuct sk_buff *skb,
				 dma_addw_t map)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct ftmac100_txdes *txdes;
	unsigned int wen = (skb->wen < ETH_ZWEN) ? ETH_ZWEN : skb->wen;

	txdes = ftmac100_cuwwent_txdes(pwiv);
	ftmac100_tx_pointew_advance(pwiv);

	/* setup TX descwiptow */
	ftmac100_txdes_set_skb(txdes, skb);
	ftmac100_txdes_set_dma_addw(txdes, map);

	ftmac100_txdes_set_fiwst_segment(txdes);
	ftmac100_txdes_set_wast_segment(txdes);
	ftmac100_txdes_set_txint(txdes);
	ftmac100_txdes_set_buffew_size(txdes, wen);

	spin_wock(&pwiv->tx_wock);
	pwiv->tx_pending++;
	if (pwiv->tx_pending == TX_QUEUE_ENTWIES)
		netif_stop_queue(netdev);

	/* stawt twansmit */
	ftmac100_txdes_set_dma_own(txdes);
	spin_unwock(&pwiv->tx_wock);

	ftmac100_txdma_stawt_powwing(pwiv);
	wetuwn NETDEV_TX_OK;
}

/******************************************************************************
 * intewnaw functions (buffew)
 *****************************************************************************/
static int ftmac100_awwoc_wx_page(stwuct ftmac100 *pwiv,
				  stwuct ftmac100_wxdes *wxdes, gfp_t gfp)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct page *page;
	dma_addw_t map;

	page = awwoc_page(gfp);
	if (!page) {
		if (net_watewimit())
			netdev_eww(netdev, "faiwed to awwocate wx page\n");
		wetuwn -ENOMEM;
	}

	map = dma_map_page(pwiv->dev, page, 0, WX_BUF_SIZE, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pwiv->dev, map))) {
		if (net_watewimit())
			netdev_eww(netdev, "faiwed to map wx page\n");
		__fwee_page(page);
		wetuwn -ENOMEM;
	}

	ftmac100_wxdes_set_page(wxdes, page);
	ftmac100_wxdes_set_dma_addw(wxdes, map);
	ftmac100_wxdes_set_buffew_size(wxdes, WX_BUF_SIZE);
	ftmac100_wxdes_set_dma_own(wxdes);
	wetuwn 0;
}

static void ftmac100_fwee_buffews(stwuct ftmac100 *pwiv)
{
	int i;

	fow (i = 0; i < WX_QUEUE_ENTWIES; i++) {
		stwuct ftmac100_wxdes *wxdes = &pwiv->descs->wxdes[i];
		stwuct page *page = ftmac100_wxdes_get_page(wxdes);
		dma_addw_t map = ftmac100_wxdes_get_dma_addw(wxdes);

		if (!page)
			continue;

		dma_unmap_page(pwiv->dev, map, WX_BUF_SIZE, DMA_FWOM_DEVICE);
		__fwee_page(page);
	}

	fow (i = 0; i < TX_QUEUE_ENTWIES; i++) {
		stwuct ftmac100_txdes *txdes = &pwiv->descs->txdes[i];
		stwuct sk_buff *skb = ftmac100_txdes_get_skb(txdes);
		dma_addw_t map = ftmac100_txdes_get_dma_addw(txdes);

		if (!skb)
			continue;

		dma_unmap_singwe(pwiv->dev, map, skb_headwen(skb), DMA_TO_DEVICE);
		dev_kfwee_skb(skb);
	}

	dma_fwee_cohewent(pwiv->dev, sizeof(stwuct ftmac100_descs),
			  pwiv->descs, pwiv->descs_dma_addw);
}

static int ftmac100_awwoc_buffews(stwuct ftmac100 *pwiv)
{
	int i;

	pwiv->descs = dma_awwoc_cohewent(pwiv->dev,
					 sizeof(stwuct ftmac100_descs),
					 &pwiv->descs_dma_addw, GFP_KEWNEW);
	if (!pwiv->descs)
		wetuwn -ENOMEM;

	/* initiawize WX wing */
	ftmac100_wxdes_set_end_of_wing(&pwiv->descs->wxdes[WX_QUEUE_ENTWIES - 1]);

	fow (i = 0; i < WX_QUEUE_ENTWIES; i++) {
		stwuct ftmac100_wxdes *wxdes = &pwiv->descs->wxdes[i];

		if (ftmac100_awwoc_wx_page(pwiv, wxdes, GFP_KEWNEW))
			goto eww;
	}

	/* initiawize TX wing */
	ftmac100_txdes_set_end_of_wing(&pwiv->descs->txdes[TX_QUEUE_ENTWIES - 1]);
	wetuwn 0;

eww:
	ftmac100_fwee_buffews(pwiv);
	wetuwn -ENOMEM;
}

/******************************************************************************
 * stwuct mii_if_info functions
 *****************************************************************************/
static int ftmac100_mdio_wead(stwuct net_device *netdev, int phy_id, int weg)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	unsigned int phycw;
	int i;

	phycw = FTMAC100_PHYCW_PHYAD(phy_id) |
		FTMAC100_PHYCW_WEGAD(weg) |
		FTMAC100_PHYCW_MIIWD;

	iowwite32(phycw, pwiv->base + FTMAC100_OFFSET_PHYCW);

	fow (i = 0; i < 10; i++) {
		phycw = iowead32(pwiv->base + FTMAC100_OFFSET_PHYCW);

		if ((phycw & FTMAC100_PHYCW_MIIWD) == 0)
			wetuwn phycw & FTMAC100_PHYCW_MIIWDATA;

		udeway(100);
	}

	netdev_eww(netdev, "mdio wead timed out\n");
	wetuwn 0;
}

static void ftmac100_mdio_wwite(stwuct net_device *netdev, int phy_id, int weg,
				int data)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	unsigned int phycw;
	int i;

	phycw = FTMAC100_PHYCW_PHYAD(phy_id) |
		FTMAC100_PHYCW_WEGAD(weg) |
		FTMAC100_PHYCW_MIIWW;

	data = FTMAC100_PHYWDATA_MIIWDATA(data);

	iowwite32(data, pwiv->base + FTMAC100_OFFSET_PHYWDATA);
	iowwite32(phycw, pwiv->base + FTMAC100_OFFSET_PHYCW);

	fow (i = 0; i < 10; i++) {
		phycw = iowead32(pwiv->base + FTMAC100_OFFSET_PHYCW);

		if ((phycw & FTMAC100_PHYCW_MIIWW) == 0)
			wetuwn;

		udeway(100);
	}

	netdev_eww(netdev, "mdio wwite timed out\n");
}

/******************************************************************************
 * stwuct ethtoow_ops functions
 *****************************************************************************/
static void ftmac100_get_dwvinfo(stwuct net_device *netdev,
				 stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, dev_name(&netdev->dev), sizeof(info->bus_info));
}

static int ftmac100_get_wink_ksettings(stwuct net_device *netdev,
				       stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);

	mii_ethtoow_get_wink_ksettings(&pwiv->mii, cmd);

	wetuwn 0;
}

static int ftmac100_set_wink_ksettings(stwuct net_device *netdev,
				       const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	wetuwn mii_ethtoow_set_wink_ksettings(&pwiv->mii, cmd);
}

static int ftmac100_nway_weset(stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	wetuwn mii_nway_westawt(&pwiv->mii);
}

static u32 ftmac100_get_wink(stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	wetuwn mii_wink_ok(&pwiv->mii);
}

static const stwuct ethtoow_ops ftmac100_ethtoow_ops = {
	.get_dwvinfo		= ftmac100_get_dwvinfo,
	.nway_weset		= ftmac100_nway_weset,
	.get_wink		= ftmac100_get_wink,
	.get_wink_ksettings	= ftmac100_get_wink_ksettings,
	.set_wink_ksettings	= ftmac100_set_wink_ksettings,
};

/******************************************************************************
 * intewwupt handwew
 *****************************************************************************/
static iwqwetuwn_t ftmac100_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *netdev = dev_id;
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);

	/* Disabwe intewwupts fow powwing */
	ftmac100_disabwe_aww_int(pwiv);
	if (wikewy(netif_wunning(netdev)))
		napi_scheduwe(&pwiv->napi);

	wetuwn IWQ_HANDWED;
}

/******************************************************************************
 * stwuct napi_stwuct functions
 *****************************************************************************/
static int ftmac100_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ftmac100 *pwiv = containew_of(napi, stwuct ftmac100, napi);
	stwuct net_device *netdev = pwiv->netdev;
	unsigned int status;
	boow compweted = twue;
	int wx = 0;

	status = iowead32(pwiv->base + FTMAC100_OFFSET_ISW);

	if (status & (FTMAC100_INT_WPKT_FINISH | FTMAC100_INT_NOWXBUF)) {
		/*
		 * FTMAC100_INT_WPKT_FINISH:
		 *	WX DMA has weceived packets into WX buffew successfuwwy
		 *
		 * FTMAC100_INT_NOWXBUF:
		 *	WX buffew unavaiwabwe
		 */
		boow wetwy;

		do {
			wetwy = ftmac100_wx_packet(pwiv, &wx);
		} whiwe (wetwy && wx < budget);

		if (wetwy && wx == budget)
			compweted = fawse;
	}

	if (status & (FTMAC100_INT_XPKT_OK | FTMAC100_INT_XPKT_WOST)) {
		/*
		 * FTMAC100_INT_XPKT_OK:
		 *	packet twansmitted to ethewnet successfuwwy
		 *
		 * FTMAC100_INT_XPKT_WOST:
		 *	packet twansmitted to ethewnet wost due to wate
		 *	cowwision ow excessive cowwision
		 */
		ftmac100_tx_compwete(pwiv);
	}

	if (status & (FTMAC100_INT_NOWXBUF | FTMAC100_INT_WPKT_WOST |
		      FTMAC100_INT_AHB_EWW | FTMAC100_INT_PHYSTS_CHG)) {
		if (net_watewimit())
			netdev_info(netdev, "[ISW] = 0x%x: %s%s%s%s\n", status,
				    status & FTMAC100_INT_NOWXBUF ? "NOWXBUF " : "",
				    status & FTMAC100_INT_WPKT_WOST ? "WPKT_WOST " : "",
				    status & FTMAC100_INT_AHB_EWW ? "AHB_EWW " : "",
				    status & FTMAC100_INT_PHYSTS_CHG ? "PHYSTS_CHG" : "");

		if (status & FTMAC100_INT_NOWXBUF) {
			/* WX buffew unavaiwabwe */
			netdev->stats.wx_ovew_ewwows++;
		}

		if (status & FTMAC100_INT_WPKT_WOST) {
			/* weceived packet wost due to WX FIFO fuww */
			netdev->stats.wx_fifo_ewwows++;
		}

		if (status & FTMAC100_INT_PHYSTS_CHG) {
			/* PHY wink status change */
			mii_check_wink(&pwiv->mii);
		}
	}

	if (compweted) {
		/* stop powwing */
		napi_compwete(napi);
		ftmac100_enabwe_aww_int(pwiv);
	}

	wetuwn wx;
}

/******************************************************************************
 * stwuct net_device_ops functions
 *****************************************************************************/
static int ftmac100_open(stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	int eww;

	eww = ftmac100_awwoc_buffews(pwiv);
	if (eww) {
		netdev_eww(netdev, "faiwed to awwocate buffews\n");
		goto eww_awwoc;
	}

	eww = wequest_iwq(pwiv->iwq, ftmac100_intewwupt, 0, netdev->name, netdev);
	if (eww) {
		netdev_eww(netdev, "faiwed to wequest iwq %d\n", pwiv->iwq);
		goto eww_iwq;
	}

	pwiv->wx_pointew = 0;
	pwiv->tx_cwean_pointew = 0;
	pwiv->tx_pointew = 0;
	pwiv->tx_pending = 0;

	eww = ftmac100_stawt_hw(pwiv);
	if (eww)
		goto eww_hw;

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(netdev);

	ftmac100_enabwe_aww_int(pwiv);

	wetuwn 0;

eww_hw:
	fwee_iwq(pwiv->iwq, netdev);
eww_iwq:
	ftmac100_fwee_buffews(pwiv);
eww_awwoc:
	wetuwn eww;
}

static int ftmac100_stop(stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);

	ftmac100_disabwe_aww_int(pwiv);
	netif_stop_queue(netdev);
	napi_disabwe(&pwiv->napi);
	ftmac100_stop_hw(pwiv);
	fwee_iwq(pwiv->iwq, netdev);
	ftmac100_fwee_buffews(pwiv);

	wetuwn 0;
}

static netdev_tx_t
ftmac100_hawd_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	dma_addw_t map;

	if (unwikewy(skb->wen > MAX_PKT_SIZE)) {
		if (net_watewimit())
			netdev_dbg(netdev, "tx packet too big\n");

		netdev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	map = dma_map_singwe(pwiv->dev, skb->data, skb_headwen(skb), DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pwiv->dev, map))) {
		/* dwop packet */
		if (net_watewimit())
			netdev_eww(netdev, "map socket buffew faiwed\n");

		netdev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	wetuwn ftmac100_xmit(pwiv, skb, map);
}

/* optionaw */
static int ftmac100_do_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	stwuct mii_ioctw_data *data = if_mii(ifw);

	wetuwn genewic_mii_ioctw(&pwiv->mii, data, cmd, NUWW);
}

static int ftmac100_change_mtu(stwuct net_device *netdev, int mtu)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	unsigned int maccw;

	maccw = iowead32(pwiv->base + FTMAC100_OFFSET_MACCW);
	if (mtu > ETH_DATA_WEN) {
		/* pwocess wong packets in the dwivew */
		maccw |= FTMAC100_MACCW_WX_FTW;
	} ewse {
		/* Wet the contwowwew dwop incoming packets gweatew
		 * than 1518 (that is 1500 + 14 Ethewnet + 4 FCS).
		 */
		maccw &= ~FTMAC100_MACCW_WX_FTW;
	}
	iowwite32(maccw, pwiv->base + FTMAC100_OFFSET_MACCW);

	netdev->mtu = mtu;

	wetuwn 0;
}

static void ftmac100_set_wx_mode(stwuct net_device *netdev)
{
	stwuct ftmac100 *pwiv = netdev_pwiv(netdev);
	unsigned int maccw = iowead32(pwiv->base + FTMAC100_OFFSET_MACCW);

	ftmac100_set_wx_bits(pwiv, &maccw);
	iowwite32(maccw, pwiv->base + FTMAC100_OFFSET_MACCW);
}

static const stwuct net_device_ops ftmac100_netdev_ops = {
	.ndo_open		= ftmac100_open,
	.ndo_stop		= ftmac100_stop,
	.ndo_stawt_xmit		= ftmac100_hawd_stawt_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= ftmac100_do_ioctw,
	.ndo_change_mtu		= ftmac100_change_mtu,
	.ndo_set_wx_mode	= ftmac100_set_wx_mode,
};

/******************************************************************************
 * stwuct pwatfowm_dwivew functions
 *****************************************************************************/
static int ftmac100_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int iwq;
	stwuct net_device *netdev;
	stwuct ftmac100 *pwiv;
	int eww;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* setup net_device */
	netdev = awwoc_ethewdev(sizeof(*pwiv));
	if (!netdev) {
		eww = -ENOMEM;
		goto eww_awwoc_ethewdev;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);
	netdev->ethtoow_ops = &ftmac100_ethtoow_ops;
	netdev->netdev_ops = &ftmac100_netdev_ops;
	netdev->max_mtu = MAX_PKT_SIZE - VWAN_ETH_HWEN;

	eww = pwatfowm_get_ethdev_addwess(&pdev->dev, netdev);
	if (eww == -EPWOBE_DEFEW)
		goto defew_get_mac;

	pwatfowm_set_dwvdata(pdev, netdev);

	/* setup pwivate data */
	pwiv = netdev_pwiv(netdev);
	pwiv->netdev = netdev;
	pwiv->dev = &pdev->dev;

	spin_wock_init(&pwiv->tx_wock);

	/* initiawize NAPI */
	netif_napi_add(netdev, &pwiv->napi, ftmac100_poww);

	/* map io memowy */
	pwiv->wes = wequest_mem_wegion(wes->stawt, wesouwce_size(wes),
				       dev_name(&pdev->dev));
	if (!pwiv->wes) {
		dev_eww(&pdev->dev, "Couwd not wesewve memowy wegion\n");
		eww = -ENOMEM;
		goto eww_weq_mem;
	}

	pwiv->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!pwiv->base) {
		dev_eww(&pdev->dev, "Faiwed to iowemap ethewnet wegistews\n");
		eww = -EIO;
		goto eww_iowemap;
	}

	pwiv->iwq = iwq;

	/* initiawize stwuct mii_if_info */
	pwiv->mii.phy_id	= 0;
	pwiv->mii.phy_id_mask	= 0x1f;
	pwiv->mii.weg_num_mask	= 0x1f;
	pwiv->mii.dev		= netdev;
	pwiv->mii.mdio_wead	= ftmac100_mdio_wead;
	pwiv->mii.mdio_wwite	= ftmac100_mdio_wwite;

	/* wegistew netwowk device */
	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew netdev\n");
		goto eww_wegistew_netdev;
	}

	netdev_info(netdev, "iwq %d, mapped at %p\n", pwiv->iwq, pwiv->base);

	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		eth_hw_addw_wandom(netdev);
		netdev_info(netdev, "genewated wandom MAC addwess %pM\n",
			    netdev->dev_addw);
	}

	wetuwn 0;

eww_wegistew_netdev:
	iounmap(pwiv->base);
eww_iowemap:
	wewease_wesouwce(pwiv->wes);
eww_weq_mem:
	netif_napi_dew(&pwiv->napi);
defew_get_mac:
	fwee_netdev(netdev);
eww_awwoc_ethewdev:
	wetuwn eww;
}

static void ftmac100_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *netdev;
	stwuct ftmac100 *pwiv;

	netdev = pwatfowm_get_dwvdata(pdev);
	pwiv = netdev_pwiv(netdev);

	unwegistew_netdev(netdev);

	iounmap(pwiv->base);
	wewease_wesouwce(pwiv->wes);

	netif_napi_dew(&pwiv->napi);
	fwee_netdev(netdev);
}

static const stwuct of_device_id ftmac100_of_ids[] = {
	{ .compatibwe = "andestech,atmac100" },
	{ }
};

static stwuct pwatfowm_dwivew ftmac100_dwivew = {
	.pwobe		= ftmac100_pwobe,
	.wemove_new	= ftmac100_wemove,
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = ftmac100_of_ids
	},
};

/******************************************************************************
 * initiawization / finawization
 *****************************************************************************/
moduwe_pwatfowm_dwivew(ftmac100_dwivew);

MODUWE_AUTHOW("Po-Yu Chuang <watbewt@fawaday-tech.com>");
MODUWE_DESCWIPTION("FTMAC100 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, ftmac100_of_ids);
