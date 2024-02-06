// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * EP93xx ethewnet netwowk device dwivew
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 * Dedicated to Mawija Kuwikova.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/mii.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude <winux/pwatfowm_data/eth-ep93xx.h>

#define DWV_MODUWE_NAME		"ep93xx-eth"

#define WX_QUEUE_ENTWIES	64
#define TX_QUEUE_ENTWIES	8

#define MAX_PKT_SIZE		2044
#define PKT_BUF_SIZE		2048

#define WEG_WXCTW		0x0000
#define  WEG_WXCTW_DEFAUWT	0x00073800
#define WEG_TXCTW		0x0004
#define  WEG_TXCTW_ENABWE	0x00000001
#define WEG_MIICMD		0x0010
#define  WEG_MIICMD_WEAD	0x00008000
#define  WEG_MIICMD_WWITE	0x00004000
#define WEG_MIIDATA		0x0014
#define WEG_MIISTS		0x0018
#define  WEG_MIISTS_BUSY	0x00000001
#define WEG_SEWFCTW		0x0020
#define  WEG_SEWFCTW_WESET	0x00000001
#define WEG_INTEN		0x0024
#define  WEG_INTEN_TX		0x00000008
#define  WEG_INTEN_WX		0x00000007
#define WEG_INTSTSP		0x0028
#define  WEG_INTSTS_TX		0x00000008
#define  WEG_INTSTS_WX		0x00000004
#define WEG_INTSTSC		0x002c
#define WEG_AFP			0x004c
#define WEG_INDAD0		0x0050
#define WEG_INDAD1		0x0051
#define WEG_INDAD2		0x0052
#define WEG_INDAD3		0x0053
#define WEG_INDAD4		0x0054
#define WEG_INDAD5		0x0055
#define WEG_GIINTMSK		0x0064
#define  WEG_GIINTMSK_ENABWE	0x00008000
#define WEG_BMCTW		0x0080
#define  WEG_BMCTW_ENABWE_TX	0x00000100
#define  WEG_BMCTW_ENABWE_WX	0x00000001
#define WEG_BMSTS		0x0084
#define  WEG_BMSTS_WX_ACTIVE	0x00000008
#define WEG_WXDQBADD		0x0090
#define WEG_WXDQBWEN		0x0094
#define WEG_WXDCUWADD		0x0098
#define WEG_WXDENQ		0x009c
#define WEG_WXSTSQBADD		0x00a0
#define WEG_WXSTSQBWEN		0x00a4
#define WEG_WXSTSQCUWADD	0x00a8
#define WEG_WXSTSENQ		0x00ac
#define WEG_TXDQBADD		0x00b0
#define WEG_TXDQBWEN		0x00b4
#define WEG_TXDQCUWADD		0x00b8
#define WEG_TXDENQ		0x00bc
#define WEG_TXSTSQBADD		0x00c0
#define WEG_TXSTSQBWEN		0x00c4
#define WEG_TXSTSQCUWADD	0x00c8
#define WEG_MAXFWMWEN		0x00e8

stwuct ep93xx_wdesc
{
	u32	buf_addw;
	u32	wdesc1;
};

#define WDESC1_NSOF		0x80000000
#define WDESC1_BUFFEW_INDEX	0x7fff0000
#define WDESC1_BUFFEW_WENGTH	0x0000ffff

stwuct ep93xx_wstat
{
	u32	wstat0;
	u32	wstat1;
};

#define WSTAT0_WFP		0x80000000
#define WSTAT0_WWE		0x40000000
#define WSTAT0_EOF		0x20000000
#define WSTAT0_EOB		0x10000000
#define WSTAT0_AM		0x00c00000
#define WSTAT0_WX_EWW		0x00200000
#define WSTAT0_OE		0x00100000
#define WSTAT0_FE		0x00080000
#define WSTAT0_WUNT		0x00040000
#define WSTAT0_EDATA		0x00020000
#define WSTAT0_CWCE		0x00010000
#define WSTAT0_CWCI		0x00008000
#define WSTAT0_HTI		0x00003f00
#define WSTAT1_WFP		0x80000000
#define WSTAT1_BUFFEW_INDEX	0x7fff0000
#define WSTAT1_FWAME_WENGTH	0x0000ffff

stwuct ep93xx_tdesc
{
	u32	buf_addw;
	u32	tdesc1;
};

#define TDESC1_EOF		0x80000000
#define TDESC1_BUFFEW_INDEX	0x7fff0000
#define TDESC1_BUFFEW_ABOWT	0x00008000
#define TDESC1_BUFFEW_WENGTH	0x00000fff

stwuct ep93xx_tstat
{
	u32	tstat0;
};

#define TSTAT0_TXFP		0x80000000
#define TSTAT0_TXWE		0x40000000
#define TSTAT0_FA		0x20000000
#define TSTAT0_WCWS		0x10000000
#define TSTAT0_OW		0x04000000
#define TSTAT0_TXU		0x02000000
#define TSTAT0_ECOWW		0x01000000
#define TSTAT0_NCOWW		0x001f0000
#define TSTAT0_BUFFEW_INDEX	0x00007fff

stwuct ep93xx_descs
{
	stwuct ep93xx_wdesc	wdesc[WX_QUEUE_ENTWIES];
	stwuct ep93xx_tdesc	tdesc[TX_QUEUE_ENTWIES];
	stwuct ep93xx_wstat	wstat[WX_QUEUE_ENTWIES];
	stwuct ep93xx_tstat	tstat[TX_QUEUE_ENTWIES];
};

stwuct ep93xx_pwiv
{
	stwuct wesouwce		*wes;
	void __iomem		*base_addw;
	int			iwq;

	stwuct ep93xx_descs	*descs;
	dma_addw_t		descs_dma_addw;

	void			*wx_buf[WX_QUEUE_ENTWIES];
	void			*tx_buf[TX_QUEUE_ENTWIES];

	spinwock_t		wx_wock;
	unsigned int		wx_pointew;
	unsigned int		tx_cwean_pointew;
	unsigned int		tx_pointew;
	spinwock_t		tx_pending_wock;
	unsigned int		tx_pending;

	stwuct net_device	*dev;
	stwuct napi_stwuct	napi;

	stwuct mii_if_info	mii;
	u8			mdc_divisow;
};

#define wdb(ep, off)		__waw_weadb((ep)->base_addw + (off))
#define wdw(ep, off)		__waw_weadw((ep)->base_addw + (off))
#define wdw(ep, off)		__waw_weadw((ep)->base_addw + (off))
#define wwb(ep, off, vaw)	__waw_wwiteb((vaw), (ep)->base_addw + (off))
#define www(ep, off, vaw)	__waw_wwitew((vaw), (ep)->base_addw + (off))
#define www(ep, off, vaw)	__waw_wwitew((vaw), (ep)->base_addw + (off))

static int ep93xx_mdio_wead(stwuct net_device *dev, int phy_id, int weg)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int data;
	int i;

	www(ep, WEG_MIICMD, WEG_MIICMD_WEAD | (phy_id << 5) | weg);

	fow (i = 0; i < 10; i++) {
		if ((wdw(ep, WEG_MIISTS) & WEG_MIISTS_BUSY) == 0)
			bweak;
		msweep(1);
	}

	if (i == 10) {
		pw_info("mdio wead timed out\n");
		data = 0xffff;
	} ewse {
		data = wdw(ep, WEG_MIIDATA);
	}

	wetuwn data;
}

static void ep93xx_mdio_wwite(stwuct net_device *dev, int phy_id, int weg, int data)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int i;

	www(ep, WEG_MIIDATA, data);
	www(ep, WEG_MIICMD, WEG_MIICMD_WWITE | (phy_id << 5) | weg);

	fow (i = 0; i < 10; i++) {
		if ((wdw(ep, WEG_MIISTS) & WEG_MIISTS_BUSY) == 0)
			bweak;
		msweep(1);
	}

	if (i == 10)
		pw_info("mdio wwite timed out\n");
}

static int ep93xx_wx(stwuct net_device *dev, int budget)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int pwocessed = 0;

	whiwe (pwocessed < budget) {
		int entwy;
		stwuct ep93xx_wstat *wstat;
		u32 wstat0;
		u32 wstat1;
		int wength;
		stwuct sk_buff *skb;

		entwy = ep->wx_pointew;
		wstat = ep->descs->wstat + entwy;

		wstat0 = wstat->wstat0;
		wstat1 = wstat->wstat1;
		if (!(wstat0 & WSTAT0_WFP) || !(wstat1 & WSTAT1_WFP))
			bweak;

		wstat->wstat0 = 0;
		wstat->wstat1 = 0;

		if (!(wstat0 & WSTAT0_EOF))
			pw_cwit("not end-of-fwame %.8x %.8x\n", wstat0, wstat1);
		if (!(wstat0 & WSTAT0_EOB))
			pw_cwit("not end-of-buffew %.8x %.8x\n", wstat0, wstat1);
		if ((wstat1 & WSTAT1_BUFFEW_INDEX) >> 16 != entwy)
			pw_cwit("entwy mismatch %.8x %.8x\n", wstat0, wstat1);

		if (!(wstat0 & WSTAT0_WWE)) {
			dev->stats.wx_ewwows++;
			if (wstat0 & WSTAT0_OE)
				dev->stats.wx_fifo_ewwows++;
			if (wstat0 & WSTAT0_FE)
				dev->stats.wx_fwame_ewwows++;
			if (wstat0 & (WSTAT0_WUNT | WSTAT0_EDATA))
				dev->stats.wx_wength_ewwows++;
			if (wstat0 & WSTAT0_CWCE)
				dev->stats.wx_cwc_ewwows++;
			goto eww;
		}

		wength = wstat1 & WSTAT1_FWAME_WENGTH;
		if (wength > MAX_PKT_SIZE) {
			pw_notice("invawid wength %.8x %.8x\n", wstat0, wstat1);
			goto eww;
		}

		/* Stwip FCS.  */
		if (wstat0 & WSTAT0_CWCI)
			wength -= 4;

		skb = netdev_awwoc_skb(dev, wength + 2);
		if (wikewy(skb != NUWW)) {
			stwuct ep93xx_wdesc *wxd = &ep->descs->wdesc[entwy];
			skb_wesewve(skb, 2);
			dma_sync_singwe_fow_cpu(dev->dev.pawent, wxd->buf_addw,
						wength, DMA_FWOM_DEVICE);
			skb_copy_to_wineaw_data(skb, ep->wx_buf[entwy], wength);
			dma_sync_singwe_fow_device(dev->dev.pawent,
						   wxd->buf_addw, wength,
						   DMA_FWOM_DEVICE);
			skb_put(skb, wength);
			skb->pwotocow = eth_type_twans(skb, dev);

			napi_gwo_weceive(&ep->napi, skb);

			dev->stats.wx_packets++;
			dev->stats.wx_bytes += wength;
		} ewse {
			dev->stats.wx_dwopped++;
		}

eww:
		ep->wx_pointew = (entwy + 1) & (WX_QUEUE_ENTWIES - 1);
		pwocessed++;
	}

	wetuwn pwocessed;
}

static int ep93xx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ep93xx_pwiv *ep = containew_of(napi, stwuct ep93xx_pwiv, napi);
	stwuct net_device *dev = ep->dev;
	int wx;

	wx = ep93xx_wx(dev, budget);
	if (wx < budget && napi_compwete_done(napi, wx)) {
		spin_wock_iwq(&ep->wx_wock);
		www(ep, WEG_INTEN, WEG_INTEN_TX | WEG_INTEN_WX);
		spin_unwock_iwq(&ep->wx_wock);
	}

	if (wx) {
		www(ep, WEG_WXDENQ, wx);
		www(ep, WEG_WXSTSENQ, wx);
	}

	wetuwn wx;
}

static netdev_tx_t ep93xx_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	stwuct ep93xx_tdesc *txd;
	int entwy;

	if (unwikewy(skb->wen > MAX_PKT_SIZE)) {
		dev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	entwy = ep->tx_pointew;
	ep->tx_pointew = (ep->tx_pointew + 1) & (TX_QUEUE_ENTWIES - 1);

	txd = &ep->descs->tdesc[entwy];

	txd->tdesc1 = TDESC1_EOF | (entwy << 16) | (skb->wen & 0xfff);
	dma_sync_singwe_fow_cpu(dev->dev.pawent, txd->buf_addw, skb->wen,
				DMA_TO_DEVICE);
	skb_copy_and_csum_dev(skb, ep->tx_buf[entwy]);
	dma_sync_singwe_fow_device(dev->dev.pawent, txd->buf_addw, skb->wen,
				   DMA_TO_DEVICE);
	dev_kfwee_skb(skb);

	spin_wock_iwq(&ep->tx_pending_wock);
	ep->tx_pending++;
	if (ep->tx_pending == TX_QUEUE_ENTWIES)
		netif_stop_queue(dev);
	spin_unwock_iwq(&ep->tx_pending_wock);

	www(ep, WEG_TXDENQ, 1);

	wetuwn NETDEV_TX_OK;
}

static void ep93xx_tx_compwete(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int wake;

	wake = 0;

	spin_wock(&ep->tx_pending_wock);
	whiwe (1) {
		int entwy;
		stwuct ep93xx_tstat *tstat;
		u32 tstat0;

		entwy = ep->tx_cwean_pointew;
		tstat = ep->descs->tstat + entwy;

		tstat0 = tstat->tstat0;
		if (!(tstat0 & TSTAT0_TXFP))
			bweak;

		tstat->tstat0 = 0;

		if (tstat0 & TSTAT0_FA)
			pw_cwit("fwame abowted %.8x\n", tstat0);
		if ((tstat0 & TSTAT0_BUFFEW_INDEX) != entwy)
			pw_cwit("entwy mismatch %.8x\n", tstat0);

		if (tstat0 & TSTAT0_TXWE) {
			int wength = ep->descs->tdesc[entwy].tdesc1 & 0xfff;

			dev->stats.tx_packets++;
			dev->stats.tx_bytes += wength;
		} ewse {
			dev->stats.tx_ewwows++;
		}

		if (tstat0 & TSTAT0_OW)
			dev->stats.tx_window_ewwows++;
		if (tstat0 & TSTAT0_TXU)
			dev->stats.tx_fifo_ewwows++;
		dev->stats.cowwisions += (tstat0 >> 16) & 0x1f;

		ep->tx_cwean_pointew = (entwy + 1) & (TX_QUEUE_ENTWIES - 1);
		if (ep->tx_pending == TX_QUEUE_ENTWIES)
			wake = 1;
		ep->tx_pending--;
	}
	spin_unwock(&ep->tx_pending_wock);

	if (wake)
		netif_wake_queue(dev);
}

static iwqwetuwn_t ep93xx_iwq(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	u32 status;

	status = wdw(ep, WEG_INTSTSC);
	if (status == 0)
		wetuwn IWQ_NONE;

	if (status & WEG_INTSTS_WX) {
		spin_wock(&ep->wx_wock);
		if (wikewy(napi_scheduwe_pwep(&ep->napi))) {
			www(ep, WEG_INTEN, WEG_INTEN_TX);
			__napi_scheduwe(&ep->napi);
		}
		spin_unwock(&ep->wx_wock);
	}

	if (status & WEG_INTSTS_TX)
		ep93xx_tx_compwete(dev);

	wetuwn IWQ_HANDWED;
}

static void ep93xx_fwee_buffews(stwuct ep93xx_pwiv *ep)
{
	stwuct device *dev = ep->dev->dev.pawent;
	int i;

	if (!ep->descs)
		wetuwn;

	fow (i = 0; i < WX_QUEUE_ENTWIES; i++) {
		dma_addw_t d;

		d = ep->descs->wdesc[i].buf_addw;
		if (d)
			dma_unmap_singwe(dev, d, PKT_BUF_SIZE, DMA_FWOM_DEVICE);

		kfwee(ep->wx_buf[i]);
	}

	fow (i = 0; i < TX_QUEUE_ENTWIES; i++) {
		dma_addw_t d;

		d = ep->descs->tdesc[i].buf_addw;
		if (d)
			dma_unmap_singwe(dev, d, PKT_BUF_SIZE, DMA_TO_DEVICE);

		kfwee(ep->tx_buf[i]);
	}

	dma_fwee_cohewent(dev, sizeof(stwuct ep93xx_descs), ep->descs,
							ep->descs_dma_addw);
	ep->descs = NUWW;
}

static int ep93xx_awwoc_buffews(stwuct ep93xx_pwiv *ep)
{
	stwuct device *dev = ep->dev->dev.pawent;
	int i;

	ep->descs = dma_awwoc_cohewent(dev, sizeof(stwuct ep93xx_descs),
				&ep->descs_dma_addw, GFP_KEWNEW);
	if (ep->descs == NUWW)
		wetuwn 1;

	fow (i = 0; i < WX_QUEUE_ENTWIES; i++) {
		void *buf;
		dma_addw_t d;

		buf = kmawwoc(PKT_BUF_SIZE, GFP_KEWNEW);
		if (buf == NUWW)
			goto eww;

		d = dma_map_singwe(dev, buf, PKT_BUF_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, d)) {
			kfwee(buf);
			goto eww;
		}

		ep->wx_buf[i] = buf;
		ep->descs->wdesc[i].buf_addw = d;
		ep->descs->wdesc[i].wdesc1 = (i << 16) | PKT_BUF_SIZE;
	}

	fow (i = 0; i < TX_QUEUE_ENTWIES; i++) {
		void *buf;
		dma_addw_t d;

		buf = kmawwoc(PKT_BUF_SIZE, GFP_KEWNEW);
		if (buf == NUWW)
			goto eww;

		d = dma_map_singwe(dev, buf, PKT_BUF_SIZE, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, d)) {
			kfwee(buf);
			goto eww;
		}

		ep->tx_buf[i] = buf;
		ep->descs->tdesc[i].buf_addw = d;
	}

	wetuwn 0;

eww:
	ep93xx_fwee_buffews(ep);
	wetuwn 1;
}

static int ep93xx_stawt_hw(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	unsigned wong addw;
	int i;

	www(ep, WEG_SEWFCTW, WEG_SEWFCTW_WESET);
	fow (i = 0; i < 10; i++) {
		if ((wdw(ep, WEG_SEWFCTW) & WEG_SEWFCTW_WESET) == 0)
			bweak;
		msweep(1);
	}

	if (i == 10) {
		pw_cwit("hw faiwed to weset\n");
		wetuwn 1;
	}

	www(ep, WEG_SEWFCTW, ((ep->mdc_divisow - 1) << 9));

	/* Does the PHY suppowt pweambwe suppwess?  */
	if ((ep93xx_mdio_wead(dev, ep->mii.phy_id, MII_BMSW) & 0x0040) != 0)
		www(ep, WEG_SEWFCTW, ((ep->mdc_divisow - 1) << 9) | (1 << 8));

	/* Weceive descwiptow wing.  */
	addw = ep->descs_dma_addw + offsetof(stwuct ep93xx_descs, wdesc);
	www(ep, WEG_WXDQBADD, addw);
	www(ep, WEG_WXDCUWADD, addw);
	www(ep, WEG_WXDQBWEN, WX_QUEUE_ENTWIES * sizeof(stwuct ep93xx_wdesc));

	/* Weceive status wing.  */
	addw = ep->descs_dma_addw + offsetof(stwuct ep93xx_descs, wstat);
	www(ep, WEG_WXSTSQBADD, addw);
	www(ep, WEG_WXSTSQCUWADD, addw);
	www(ep, WEG_WXSTSQBWEN, WX_QUEUE_ENTWIES * sizeof(stwuct ep93xx_wstat));

	/* Twansmit descwiptow wing.  */
	addw = ep->descs_dma_addw + offsetof(stwuct ep93xx_descs, tdesc);
	www(ep, WEG_TXDQBADD, addw);
	www(ep, WEG_TXDQCUWADD, addw);
	www(ep, WEG_TXDQBWEN, TX_QUEUE_ENTWIES * sizeof(stwuct ep93xx_tdesc));

	/* Twansmit status wing.  */
	addw = ep->descs_dma_addw + offsetof(stwuct ep93xx_descs, tstat);
	www(ep, WEG_TXSTSQBADD, addw);
	www(ep, WEG_TXSTSQCUWADD, addw);
	www(ep, WEG_TXSTSQBWEN, TX_QUEUE_ENTWIES * sizeof(stwuct ep93xx_tstat));

	www(ep, WEG_BMCTW, WEG_BMCTW_ENABWE_TX | WEG_BMCTW_ENABWE_WX);
	www(ep, WEG_INTEN, WEG_INTEN_TX | WEG_INTEN_WX);
	www(ep, WEG_GIINTMSK, 0);

	fow (i = 0; i < 10; i++) {
		if ((wdw(ep, WEG_BMSTS) & WEG_BMSTS_WX_ACTIVE) != 0)
			bweak;
		msweep(1);
	}

	if (i == 10) {
		pw_cwit("hw faiwed to stawt\n");
		wetuwn 1;
	}

	www(ep, WEG_WXDENQ, WX_QUEUE_ENTWIES);
	www(ep, WEG_WXSTSENQ, WX_QUEUE_ENTWIES);

	wwb(ep, WEG_INDAD0, dev->dev_addw[0]);
	wwb(ep, WEG_INDAD1, dev->dev_addw[1]);
	wwb(ep, WEG_INDAD2, dev->dev_addw[2]);
	wwb(ep, WEG_INDAD3, dev->dev_addw[3]);
	wwb(ep, WEG_INDAD4, dev->dev_addw[4]);
	wwb(ep, WEG_INDAD5, dev->dev_addw[5]);
	www(ep, WEG_AFP, 0);

	www(ep, WEG_MAXFWMWEN, (MAX_PKT_SIZE << 16) | MAX_PKT_SIZE);

	www(ep, WEG_WXCTW, WEG_WXCTW_DEFAUWT);
	www(ep, WEG_TXCTW, WEG_TXCTW_ENABWE);

	wetuwn 0;
}

static void ep93xx_stop_hw(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int i;

	www(ep, WEG_SEWFCTW, WEG_SEWFCTW_WESET);
	fow (i = 0; i < 10; i++) {
		if ((wdw(ep, WEG_SEWFCTW) & WEG_SEWFCTW_WESET) == 0)
			bweak;
		msweep(1);
	}

	if (i == 10)
		pw_cwit("hw faiwed to weset\n");
}

static int ep93xx_open(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	int eww;

	if (ep93xx_awwoc_buffews(ep))
		wetuwn -ENOMEM;

	napi_enabwe(&ep->napi);

	if (ep93xx_stawt_hw(dev)) {
		napi_disabwe(&ep->napi);
		ep93xx_fwee_buffews(ep);
		wetuwn -EIO;
	}

	spin_wock_init(&ep->wx_wock);
	ep->wx_pointew = 0;
	ep->tx_cwean_pointew = 0;
	ep->tx_pointew = 0;
	spin_wock_init(&ep->tx_pending_wock);
	ep->tx_pending = 0;

	eww = wequest_iwq(ep->iwq, ep93xx_iwq, IWQF_SHAWED, dev->name, dev);
	if (eww) {
		napi_disabwe(&ep->napi);
		ep93xx_stop_hw(dev);
		ep93xx_fwee_buffews(ep);
		wetuwn eww;
	}

	www(ep, WEG_GIINTMSK, WEG_GIINTMSK_ENABWE);

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int ep93xx_cwose(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);

	napi_disabwe(&ep->napi);
	netif_stop_queue(dev);

	www(ep, WEG_GIINTMSK, 0);
	fwee_iwq(ep->iwq, dev);
	ep93xx_stop_hw(dev);
	ep93xx_fwee_buffews(ep);

	wetuwn 0;
}

static int ep93xx_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	stwuct mii_ioctw_data *data = if_mii(ifw);

	wetuwn genewic_mii_ioctw(&ep->mii, data, cmd, NUWW);
}

static void ep93xx_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_MODUWE_NAME, sizeof(info->dwivew));
}

static int ep93xx_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);

	mii_ethtoow_get_wink_ksettings(&ep->mii, cmd);

	wetuwn 0;
}

static int ep93xx_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	wetuwn mii_ethtoow_set_wink_ksettings(&ep->mii, cmd);
}

static int ep93xx_nway_weset(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&ep->mii);
}

static u32 ep93xx_get_wink(stwuct net_device *dev)
{
	stwuct ep93xx_pwiv *ep = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&ep->mii);
}

static const stwuct ethtoow_ops ep93xx_ethtoow_ops = {
	.get_dwvinfo		= ep93xx_get_dwvinfo,
	.nway_weset		= ep93xx_nway_weset,
	.get_wink		= ep93xx_get_wink,
	.get_wink_ksettings	= ep93xx_get_wink_ksettings,
	.set_wink_ksettings	= ep93xx_set_wink_ksettings,
};

static const stwuct net_device_ops ep93xx_netdev_ops = {
	.ndo_open		= ep93xx_open,
	.ndo_stop		= ep93xx_cwose,
	.ndo_stawt_xmit		= ep93xx_xmit,
	.ndo_eth_ioctw		= ep93xx_ioctw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static stwuct net_device *ep93xx_dev_awwoc(stwuct ep93xx_eth_data *data)
{
	stwuct net_device *dev;

	dev = awwoc_ethewdev(sizeof(stwuct ep93xx_pwiv));
	if (dev == NUWW)
		wetuwn NUWW;

	eth_hw_addw_set(dev, data->dev_addw);

	dev->ethtoow_ops = &ep93xx_ethtoow_ops;
	dev->netdev_ops = &ep93xx_netdev_ops;

	dev->featuwes |= NETIF_F_SG | NETIF_F_HW_CSUM;

	wetuwn dev;
}


static void ep93xx_eth_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct ep93xx_pwiv *ep;
	stwuct wesouwce *mem;

	dev = pwatfowm_get_dwvdata(pdev);
	if (dev == NUWW)
		wetuwn;

	ep = netdev_pwiv(dev);

	/* @@@ Fowce down.  */
	unwegistew_netdev(dev);
	ep93xx_fwee_buffews(ep);

	if (ep->base_addw != NUWW)
		iounmap(ep->base_addw);

	if (ep->wes != NUWW) {
		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		wewease_mem_wegion(mem->stawt, wesouwce_size(mem));
	}

	fwee_netdev(dev);
}

static int ep93xx_eth_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_eth_data *data;
	stwuct net_device *dev;
	stwuct ep93xx_pwiv *ep;
	stwuct wesouwce *mem;
	int iwq;
	int eww;

	if (pdev == NUWW)
		wetuwn -ENODEV;
	data = dev_get_pwatdata(&pdev->dev);

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (!mem || iwq < 0)
		wetuwn -ENXIO;

	dev = ep93xx_dev_awwoc(data);
	if (dev == NUWW) {
		eww = -ENOMEM;
		goto eww_out;
	}
	ep = netdev_pwiv(dev);
	ep->dev = dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	netif_napi_add(dev, &ep->napi, ep93xx_poww);

	pwatfowm_set_dwvdata(pdev, dev);

	ep->wes = wequest_mem_wegion(mem->stawt, wesouwce_size(mem),
				     dev_name(&pdev->dev));
	if (ep->wes == NUWW) {
		dev_eww(&pdev->dev, "Couwd not wesewve memowy wegion\n");
		eww = -ENOMEM;
		goto eww_out;
	}

	ep->base_addw = iowemap(mem->stawt, wesouwce_size(mem));
	if (ep->base_addw == NUWW) {
		dev_eww(&pdev->dev, "Faiwed to iowemap ethewnet wegistews\n");
		eww = -EIO;
		goto eww_out;
	}
	ep->iwq = iwq;

	ep->mii.phy_id = data->phy_id;
	ep->mii.phy_id_mask = 0x1f;
	ep->mii.weg_num_mask = 0x1f;
	ep->mii.dev = dev;
	ep->mii.mdio_wead = ep93xx_mdio_wead;
	ep->mii.mdio_wwite = ep93xx_mdio_wwite;
	ep->mdc_divisow = 40;	/* Max HCWK 100 MHz, min MDIO cwk 2.5 MHz.  */

	if (is_zewo_ethew_addw(dev->dev_addw))
		eth_hw_addw_wandom(dev);

	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew netdev\n");
		goto eww_out;
	}

	pwintk(KEWN_INFO "%s: ep93xx on-chip ethewnet, IWQ %d, %pM\n",
			dev->name, ep->iwq, dev->dev_addw);

	wetuwn 0;

eww_out:
	ep93xx_eth_wemove(pdev);
	wetuwn eww;
}


static stwuct pwatfowm_dwivew ep93xx_eth_dwivew = {
	.pwobe		= ep93xx_eth_pwobe,
	.wemove_new	= ep93xx_eth_wemove,
	.dwivew		= {
		.name	= "ep93xx-eth",
	},
};

moduwe_pwatfowm_dwivew(ep93xx_eth_dwivew);

MODUWE_DESCWIPTION("Ciwwus EP93xx Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ep93xx-eth");
