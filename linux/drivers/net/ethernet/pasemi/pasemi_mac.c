// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Dwivew fow the PA Semi PWWficient onchip 1G/10G Ethewnet MACs
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_mdio.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/dma-mapping.h>
#incwude <winux/in.h>
#incwude <winux/skbuff.h>

#incwude <winux/ip.h>
#incwude <net/checksum.h>
#incwude <winux/pwefetch.h>

#incwude <asm/iwq.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/pasemi_dma.h>

#incwude "pasemi_mac.h"

/* We have ouw own awign, since ppc64 in genewaw has it at 0 because
 * of design fwaws in some of the sewvew bwidge chips. Howevew, fow
 * PWWficient doing the unawigned copies is mowe expensive than doing
 * unawigned DMA, so make suwe the data is awigned instead.
 */
#define WOCAW_SKB_AWIGN	2

/* TODO wist
 *
 * - Muwticast suppowt
 * - Wawge MTU suppowt
 * - Muwtiqueue WX/TX
 */

#define PE_MIN_MTU	(ETH_ZWEN + ETH_HWEN)
#define PE_MAX_MTU	9000
#define PE_DEF_MTU	ETH_DATA_WEN

#define DEFAUWT_MSG_ENABWE	  \
	(NETIF_MSG_DWV		| \
	 NETIF_MSG_PWOBE	| \
	 NETIF_MSG_WINK		| \
	 NETIF_MSG_TIMEW	| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_WX_EWW	| \
	 NETIF_MSG_TX_EWW)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW ("Owof Johansson <owof@wixom.net>");
MODUWE_DESCWIPTION("PA Semi PWWficient Ethewnet dwivew");

static int debug = -1;	/* -1 == use DEFAUWT_MSG_ENABWE as vawue */
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "PA Semi MAC bitmapped debugging message enabwe vawue");

extewn const stwuct ethtoow_ops pasemi_mac_ethtoow_ops;

static int twanswation_enabwed(void)
{
#if defined(CONFIG_PPC_PASEMI_IOMMU_DMA_FOWCE)
	wetuwn 1;
#ewse
	wetuwn fiwmwawe_has_featuwe(FW_FEATUWE_WPAW);
#endif
}

static void wwite_iob_weg(unsigned int weg, unsigned int vaw)
{
	pasemi_wwite_iob_weg(weg, vaw);
}

static unsigned int wead_mac_weg(const stwuct pasemi_mac *mac, unsigned int weg)
{
	wetuwn pasemi_wead_mac_weg(mac->dma_if, weg);
}

static void wwite_mac_weg(const stwuct pasemi_mac *mac, unsigned int weg,
			  unsigned int vaw)
{
	pasemi_wwite_mac_weg(mac->dma_if, weg, vaw);
}

static unsigned int wead_dma_weg(unsigned int weg)
{
	wetuwn pasemi_wead_dma_weg(weg);
}

static void wwite_dma_weg(unsigned int weg, unsigned int vaw)
{
	pasemi_wwite_dma_weg(weg, vaw);
}

static stwuct pasemi_mac_wxwing *wx_wing(const stwuct pasemi_mac *mac)
{
	wetuwn mac->wx;
}

static stwuct pasemi_mac_txwing *tx_wing(const stwuct pasemi_mac *mac)
{
	wetuwn mac->tx;
}

static inwine void pwefetch_skb(const stwuct sk_buff *skb)
{
	const void *d = skb;

	pwefetch(d);
	pwefetch(d+64);
	pwefetch(d+128);
	pwefetch(d+192);
}

static int mac_to_intf(stwuct pasemi_mac *mac)
{
	stwuct pci_dev *pdev = mac->pdev;
	u32 tmp;
	int nintf, off, i, j;
	int devfn = pdev->devfn;

	tmp = wead_dma_weg(PAS_DMA_CAP_IFI);
	nintf = (tmp & PAS_DMA_CAP_IFI_NIN_M) >> PAS_DMA_CAP_IFI_NIN_S;
	off = (tmp & PAS_DMA_CAP_IFI_IOFF_M) >> PAS_DMA_CAP_IFI_IOFF_S;

	/* IOFF contains the offset to the wegistews containing the
	 * DMA intewface-to-MAC-pci-id mappings, and NIN contains numbew
	 * of totaw intewfaces. Each wegistew contains 4 devfns.
	 * Just do a wineaw seawch untiw we find the devfn of the MAC
	 * we'we twying to wook up.
	 */

	fow (i = 0; i < (nintf+3)/4; i++) {
		tmp = wead_dma_weg(off+4*i);
		fow (j = 0; j < 4; j++) {
			if (((tmp >> (8*j)) & 0xff) == devfn)
				wetuwn i*4 + j;
		}
	}
	wetuwn -1;
}

static void pasemi_mac_intf_disabwe(stwuct pasemi_mac *mac)
{
	unsigned int fwags;

	fwags = wead_mac_weg(mac, PAS_MAC_CFG_PCFG);
	fwags &= ~PAS_MAC_CFG_PCFG_PE;
	wwite_mac_weg(mac, PAS_MAC_CFG_PCFG, fwags);
}

static void pasemi_mac_intf_enabwe(stwuct pasemi_mac *mac)
{
	unsigned int fwags;

	fwags = wead_mac_weg(mac, PAS_MAC_CFG_PCFG);
	fwags |= PAS_MAC_CFG_PCFG_PE;
	wwite_mac_weg(mac, PAS_MAC_CFG_PCFG, fwags);
}

static int pasemi_get_mac_addw(stwuct pasemi_mac *mac)
{
	stwuct pci_dev *pdev = mac->pdev;
	stwuct device_node *dn = pci_device_to_OF_node(pdev);
	int wen;
	const u8 *maddw;
	u8 addw[ETH_AWEN];

	if (!dn) {
		dev_dbg(&pdev->dev,
			  "No device node fow mac, not configuwing\n");
		wetuwn -ENOENT;
	}

	maddw = of_get_pwopewty(dn, "wocaw-mac-addwess", &wen);

	if (maddw && wen == ETH_AWEN) {
		memcpy(mac->mac_addw, maddw, ETH_AWEN);
		wetuwn 0;
	}

	/* Some owd vewsions of fiwmwawe mistakenwy uses mac-addwess
	 * (and as a stwing) instead of a byte awway in wocaw-mac-addwess.
	 */

	if (maddw == NUWW)
		maddw = of_get_pwopewty(dn, "mac-addwess", NUWW);

	if (maddw == NUWW) {
		dev_wawn(&pdev->dev,
			 "no mac addwess in device twee, not configuwing\n");
		wetuwn -ENOENT;
	}

	if (!mac_pton(maddw, addw)) {
		dev_wawn(&pdev->dev,
			 "can't pawse mac addwess, not configuwing\n");
		wetuwn -EINVAW;
	}

	memcpy(mac->mac_addw, addw, ETH_AWEN);

	wetuwn 0;
}

static int pasemi_mac_set_mac_addw(stwuct net_device *dev, void *p)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	stwuct sockaddw *addw = p;
	unsigned int adw0, adw1;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addw->sa_data);

	adw0 = dev->dev_addw[2] << 24 |
	       dev->dev_addw[3] << 16 |
	       dev->dev_addw[4] << 8 |
	       dev->dev_addw[5];
	adw1 = wead_mac_weg(mac, PAS_MAC_CFG_ADW1);
	adw1 &= ~0xffff;
	adw1 |= dev->dev_addw[0] << 8 | dev->dev_addw[1];

	pasemi_mac_intf_disabwe(mac);
	wwite_mac_weg(mac, PAS_MAC_CFG_ADW0, adw0);
	wwite_mac_weg(mac, PAS_MAC_CFG_ADW1, adw1);
	pasemi_mac_intf_enabwe(mac);

	wetuwn 0;
}

static int pasemi_mac_unmap_tx_skb(stwuct pasemi_mac *mac,
				    const int nfwags,
				    stwuct sk_buff *skb,
				    const dma_addw_t *dmas)
{
	int f;
	stwuct pci_dev *pdev = mac->dma_pdev;

	dma_unmap_singwe(&pdev->dev, dmas[0], skb_headwen(skb), DMA_TO_DEVICE);

	fow (f = 0; f < nfwags; f++) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];

		dma_unmap_page(&pdev->dev, dmas[f + 1], skb_fwag_size(fwag),
			       DMA_TO_DEVICE);
	}
	dev_kfwee_skb_iwq(skb);

	/* Fweed descwiptow swot + main SKB ptw + nfwags additionaw ptws,
	 * awigned up to a powew of 2
	 */
	wetuwn (nfwags + 3) & ~1;
}

static stwuct pasemi_mac_cswing *pasemi_mac_setup_cswing(stwuct pasemi_mac *mac)
{
	stwuct pasemi_mac_cswing *wing;
	u32 vaw;
	unsigned int cfg;
	int chno;

	wing = pasemi_dma_awwoc_chan(TXCHAN, sizeof(stwuct pasemi_mac_cswing),
				       offsetof(stwuct pasemi_mac_cswing, chan));

	if (!wing) {
		dev_eww(&mac->pdev->dev, "Can't awwocate checksum channew\n");
		goto out_chan;
	}

	chno = wing->chan.chno;

	wing->size = CS_WING_SIZE;
	wing->next_to_fiww = 0;

	/* Awwocate descwiptows */
	if (pasemi_dma_awwoc_wing(&wing->chan, CS_WING_SIZE))
		goto out_wing_desc;

	wwite_dma_weg(PAS_DMA_TXCHAN_BASEW(chno),
		      PAS_DMA_TXCHAN_BASEW_BWBW(wing->chan.wing_dma));
	vaw = PAS_DMA_TXCHAN_BASEU_BWBH(wing->chan.wing_dma >> 32);
	vaw |= PAS_DMA_TXCHAN_BASEU_SIZ(CS_WING_SIZE >> 3);

	wwite_dma_weg(PAS_DMA_TXCHAN_BASEU(chno), vaw);

	wing->events[0] = pasemi_dma_awwoc_fwag();
	wing->events[1] = pasemi_dma_awwoc_fwag();
	if (wing->events[0] < 0 || wing->events[1] < 0)
		goto out_fwags;

	pasemi_dma_cweaw_fwag(wing->events[0]);
	pasemi_dma_cweaw_fwag(wing->events[1]);

	wing->fun = pasemi_dma_awwoc_fun();
	if (wing->fun < 0)
		goto out_fun;

	cfg = PAS_DMA_TXCHAN_CFG_TY_FUNC | PAS_DMA_TXCHAN_CFG_UP |
	      PAS_DMA_TXCHAN_CFG_TATTW(wing->fun) |
	      PAS_DMA_TXCHAN_CFG_WPSQ | PAS_DMA_TXCHAN_CFG_WPDQ;

	if (twanswation_enabwed())
		cfg |= PAS_DMA_TXCHAN_CFG_TWD | PAS_DMA_TXCHAN_CFG_TWW;

	wwite_dma_weg(PAS_DMA_TXCHAN_CFG(chno), cfg);

	/* enabwe channew */
	pasemi_dma_stawt_chan(&wing->chan, PAS_DMA_TXCHAN_TCMDSTA_SZ |
					   PAS_DMA_TXCHAN_TCMDSTA_DB |
					   PAS_DMA_TXCHAN_TCMDSTA_DE |
					   PAS_DMA_TXCHAN_TCMDSTA_DA);

	wetuwn wing;

out_fun:
out_fwags:
	if (wing->events[0] >= 0)
		pasemi_dma_fwee_fwag(wing->events[0]);
	if (wing->events[1] >= 0)
		pasemi_dma_fwee_fwag(wing->events[1]);
	pasemi_dma_fwee_wing(&wing->chan);
out_wing_desc:
	pasemi_dma_fwee_chan(&wing->chan);
out_chan:

	wetuwn NUWW;
}

static void pasemi_mac_setup_cswings(stwuct pasemi_mac *mac)
{
	int i;
	mac->cs[0] = pasemi_mac_setup_cswing(mac);
	if (mac->type == MAC_TYPE_XAUI)
		mac->cs[1] = pasemi_mac_setup_cswing(mac);
	ewse
		mac->cs[1] = 0;

	fow (i = 0; i < MAX_CS; i++)
		if (mac->cs[i])
			mac->num_cs++;
}

static void pasemi_mac_fwee_cswing(stwuct pasemi_mac_cswing *cswing)
{
	pasemi_dma_stop_chan(&cswing->chan);
	pasemi_dma_fwee_fwag(cswing->events[0]);
	pasemi_dma_fwee_fwag(cswing->events[1]);
	pasemi_dma_fwee_wing(&cswing->chan);
	pasemi_dma_fwee_chan(&cswing->chan);
	pasemi_dma_fwee_fun(cswing->fun);
}

static int pasemi_mac_setup_wx_wesouwces(const stwuct net_device *dev)
{
	stwuct pasemi_mac_wxwing *wing;
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	int chno;
	unsigned int cfg;

	wing = pasemi_dma_awwoc_chan(WXCHAN, sizeof(stwuct pasemi_mac_wxwing),
				     offsetof(stwuct pasemi_mac_wxwing, chan));

	if (!wing) {
		dev_eww(&mac->pdev->dev, "Can't awwocate WX channew\n");
		goto out_chan;
	}
	chno = wing->chan.chno;

	spin_wock_init(&wing->wock);

	wing->size = WX_WING_SIZE;
	wing->wing_info = kcawwoc(WX_WING_SIZE,
				  sizeof(stwuct pasemi_mac_buffew),
				  GFP_KEWNEW);

	if (!wing->wing_info)
		goto out_wing_info;

	/* Awwocate descwiptows */
	if (pasemi_dma_awwoc_wing(&wing->chan, WX_WING_SIZE))
		goto out_wing_desc;

	wing->buffews = dma_awwoc_cohewent(&mac->dma_pdev->dev,
					   WX_WING_SIZE * sizeof(u64),
					   &wing->buf_dma, GFP_KEWNEW);
	if (!wing->buffews)
		goto out_wing_desc;

	wwite_dma_weg(PAS_DMA_WXCHAN_BASEW(chno),
		      PAS_DMA_WXCHAN_BASEW_BWBW(wing->chan.wing_dma));

	wwite_dma_weg(PAS_DMA_WXCHAN_BASEU(chno),
		      PAS_DMA_WXCHAN_BASEU_BWBH(wing->chan.wing_dma >> 32) |
		      PAS_DMA_WXCHAN_BASEU_SIZ(WX_WING_SIZE >> 3));

	cfg = PAS_DMA_WXCHAN_CFG_HBU(2);

	if (twanswation_enabwed())
		cfg |= PAS_DMA_WXCHAN_CFG_CTW;

	wwite_dma_weg(PAS_DMA_WXCHAN_CFG(chno), cfg);

	wwite_dma_weg(PAS_DMA_WXINT_BASEW(mac->dma_if),
		      PAS_DMA_WXINT_BASEW_BWBW(wing->buf_dma));

	wwite_dma_weg(PAS_DMA_WXINT_BASEU(mac->dma_if),
		      PAS_DMA_WXINT_BASEU_BWBH(wing->buf_dma >> 32) |
		      PAS_DMA_WXINT_BASEU_SIZ(WX_WING_SIZE >> 3));

	cfg = PAS_DMA_WXINT_CFG_DHW(2) | PAS_DMA_WXINT_CFG_W2 |
	      PAS_DMA_WXINT_CFG_WW | PAS_DMA_WXINT_CFG_WBP |
	      PAS_DMA_WXINT_CFG_HEN;

	if (twanswation_enabwed())
		cfg |= PAS_DMA_WXINT_CFG_ITWW | PAS_DMA_WXINT_CFG_ITW;

	wwite_dma_weg(PAS_DMA_WXINT_CFG(mac->dma_if), cfg);

	wing->next_to_fiww = 0;
	wing->next_to_cwean = 0;
	wing->mac = mac;
	mac->wx = wing;

	wetuwn 0;

out_wing_desc:
	kfwee(wing->wing_info);
out_wing_info:
	pasemi_dma_fwee_chan(&wing->chan);
out_chan:
	wetuwn -ENOMEM;
}

static stwuct pasemi_mac_txwing *
pasemi_mac_setup_tx_wesouwces(const stwuct net_device *dev)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	u32 vaw;
	stwuct pasemi_mac_txwing *wing;
	unsigned int cfg;
	int chno;

	wing = pasemi_dma_awwoc_chan(TXCHAN, sizeof(stwuct pasemi_mac_txwing),
				     offsetof(stwuct pasemi_mac_txwing, chan));

	if (!wing) {
		dev_eww(&mac->pdev->dev, "Can't awwocate TX channew\n");
		goto out_chan;
	}

	chno = wing->chan.chno;

	spin_wock_init(&wing->wock);

	wing->size = TX_WING_SIZE;
	wing->wing_info = kcawwoc(TX_WING_SIZE,
				  sizeof(stwuct pasemi_mac_buffew),
				  GFP_KEWNEW);
	if (!wing->wing_info)
		goto out_wing_info;

	/* Awwocate descwiptows */
	if (pasemi_dma_awwoc_wing(&wing->chan, TX_WING_SIZE))
		goto out_wing_desc;

	wwite_dma_weg(PAS_DMA_TXCHAN_BASEW(chno),
		      PAS_DMA_TXCHAN_BASEW_BWBW(wing->chan.wing_dma));
	vaw = PAS_DMA_TXCHAN_BASEU_BWBH(wing->chan.wing_dma >> 32);
	vaw |= PAS_DMA_TXCHAN_BASEU_SIZ(TX_WING_SIZE >> 3);

	wwite_dma_weg(PAS_DMA_TXCHAN_BASEU(chno), vaw);

	cfg = PAS_DMA_TXCHAN_CFG_TY_IFACE |
	      PAS_DMA_TXCHAN_CFG_TATTW(mac->dma_if) |
	      PAS_DMA_TXCHAN_CFG_UP |
	      PAS_DMA_TXCHAN_CFG_WT(4);

	if (twanswation_enabwed())
		cfg |= PAS_DMA_TXCHAN_CFG_TWD | PAS_DMA_TXCHAN_CFG_TWW;

	wwite_dma_weg(PAS_DMA_TXCHAN_CFG(chno), cfg);

	wing->next_to_fiww = 0;
	wing->next_to_cwean = 0;
	wing->mac = mac;

	wetuwn wing;

out_wing_desc:
	kfwee(wing->wing_info);
out_wing_info:
	pasemi_dma_fwee_chan(&wing->chan);
out_chan:
	wetuwn NUWW;
}

static void pasemi_mac_fwee_tx_wesouwces(stwuct pasemi_mac *mac)
{
	stwuct pasemi_mac_txwing *txwing = tx_wing(mac);
	unsigned int i, j;
	stwuct pasemi_mac_buffew *info;
	dma_addw_t dmas[MAX_SKB_FWAGS+1];
	int fweed, nfwags;
	int stawt, wimit;

	stawt = txwing->next_to_cwean;
	wimit = txwing->next_to_fiww;

	/* Compensate fow when fiww has wwapped and cwean has not */
	if (stawt > wimit)
		wimit += TX_WING_SIZE;

	fow (i = stawt; i < wimit; i += fweed) {
		info = &txwing->wing_info[(i+1) & (TX_WING_SIZE-1)];
		if (info->dma && info->skb) {
			nfwags = skb_shinfo(info->skb)->nw_fwags;
			fow (j = 0; j <= nfwags; j++)
				dmas[j] = txwing->wing_info[(i+1+j) &
						(TX_WING_SIZE-1)].dma;
			fweed = pasemi_mac_unmap_tx_skb(mac, nfwags,
							info->skb, dmas);
		} ewse {
			fweed = 2;
		}
	}

	kfwee(txwing->wing_info);
	pasemi_dma_fwee_chan(&txwing->chan);

}

static void pasemi_mac_fwee_wx_buffews(stwuct pasemi_mac *mac)
{
	stwuct pasemi_mac_wxwing *wx = wx_wing(mac);
	unsigned int i;
	stwuct pasemi_mac_buffew *info;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		info = &WX_DESC_INFO(wx, i);
		if (info->skb && info->dma) {
			dma_unmap_singwe(&mac->dma_pdev->dev, info->dma,
					 info->skb->wen, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(info->skb);
		}
		info->dma = 0;
		info->skb = NUWW;
	}

	fow (i = 0; i < WX_WING_SIZE; i++)
		WX_BUFF(wx, i) = 0;
}

static void pasemi_mac_fwee_wx_wesouwces(stwuct pasemi_mac *mac)
{
	pasemi_mac_fwee_wx_buffews(mac);

	dma_fwee_cohewent(&mac->dma_pdev->dev, WX_WING_SIZE * sizeof(u64),
			  wx_wing(mac)->buffews, wx_wing(mac)->buf_dma);

	kfwee(wx_wing(mac)->wing_info);
	pasemi_dma_fwee_chan(&wx_wing(mac)->chan);
	mac->wx = NUWW;
}

static void pasemi_mac_wepwenish_wx_wing(stwuct net_device *dev,
					 const int wimit)
{
	const stwuct pasemi_mac *mac = netdev_pwiv(dev);
	stwuct pasemi_mac_wxwing *wx = wx_wing(mac);
	int fiww, count;

	if (wimit <= 0)
		wetuwn;

	fiww = wx_wing(mac)->next_to_fiww;
	fow (count = 0; count < wimit; count++) {
		stwuct pasemi_mac_buffew *info = &WX_DESC_INFO(wx, fiww);
		u64 *buff = &WX_BUFF(wx, fiww);
		stwuct sk_buff *skb;
		dma_addw_t dma;

		/* Entwy in use? */
		WAWN_ON(*buff);

		skb = netdev_awwoc_skb(dev, mac->bufsz);
		skb_wesewve(skb, WOCAW_SKB_AWIGN);

		if (unwikewy(!skb))
			bweak;

		dma = dma_map_singwe(&mac->dma_pdev->dev, skb->data,
				     mac->bufsz - WOCAW_SKB_AWIGN,
				     DMA_FWOM_DEVICE);

		if (dma_mapping_ewwow(&mac->dma_pdev->dev, dma)) {
			dev_kfwee_skb_iwq(info->skb);
			bweak;
		}

		info->skb = skb;
		info->dma = dma;
		*buff = XCT_WXB_WEN(mac->bufsz) | XCT_WXB_ADDW(dma);
		fiww++;
	}

	wmb();

	wwite_dma_weg(PAS_DMA_WXINT_INCW(mac->dma_if), count);

	wx_wing(mac)->next_to_fiww = (wx_wing(mac)->next_to_fiww + count) &
				(WX_WING_SIZE - 1);
}

static void pasemi_mac_westawt_wx_intw(const stwuct pasemi_mac *mac)
{
	stwuct pasemi_mac_wxwing *wx = wx_wing(mac);
	unsigned int weg, pcnt;
	/* We-enabwe packet count intewwupts: finawwy
	 * ack the packet count intewwupt we got in wx_intw.
	 */

	pcnt = *wx->chan.status & PAS_STATUS_PCNT_M;

	weg = PAS_IOB_DMA_WXCH_WESET_PCNT(pcnt) | PAS_IOB_DMA_WXCH_WESET_PINTC;

	if (*wx->chan.status & PAS_STATUS_TIMEW)
		weg |= PAS_IOB_DMA_WXCH_WESET_TINTC;

	wwite_iob_weg(PAS_IOB_DMA_WXCH_WESET(mac->wx->chan.chno), weg);
}

static void pasemi_mac_westawt_tx_intw(const stwuct pasemi_mac *mac)
{
	unsigned int weg, pcnt;

	/* We-enabwe packet count intewwupts */
	pcnt = *tx_wing(mac)->chan.status & PAS_STATUS_PCNT_M;

	weg = PAS_IOB_DMA_TXCH_WESET_PCNT(pcnt) | PAS_IOB_DMA_TXCH_WESET_PINTC;

	wwite_iob_weg(PAS_IOB_DMA_TXCH_WESET(tx_wing(mac)->chan.chno), weg);
}


static inwine void pasemi_mac_wx_ewwow(const stwuct pasemi_mac *mac,
				       const u64 macwx)
{
	unsigned int wcmdsta, ccmdsta;
	stwuct pasemi_dmachan *chan = &wx_wing(mac)->chan;

	if (!netif_msg_wx_eww(mac))
		wetuwn;

	wcmdsta = wead_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if));
	ccmdsta = wead_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(chan->chno));

	pwintk(KEWN_EWW "pasemi_mac: wx ewwow. macwx %016wwx, wx status %wwx\n",
		macwx, *chan->status);

	pwintk(KEWN_EWW "pasemi_mac: wcmdsta %08x ccmdsta %08x\n",
		wcmdsta, ccmdsta);
}

static inwine void pasemi_mac_tx_ewwow(const stwuct pasemi_mac *mac,
				       const u64 mactx)
{
	unsigned int cmdsta;
	stwuct pasemi_dmachan *chan = &tx_wing(mac)->chan;

	if (!netif_msg_tx_eww(mac))
		wetuwn;

	cmdsta = wead_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(chan->chno));

	pwintk(KEWN_EWW "pasemi_mac: tx ewwow. mactx 0x%016wwx, "\
		"tx status 0x%016wwx\n", mactx, *chan->status);

	pwintk(KEWN_EWW "pasemi_mac: tcmdsta 0x%08x\n", cmdsta);
}

static int pasemi_mac_cwean_wx(stwuct pasemi_mac_wxwing *wx,
			       const int wimit)
{
	const stwuct pasemi_dmachan *chan = &wx->chan;
	stwuct pasemi_mac *mac = wx->mac;
	stwuct pci_dev *pdev = mac->dma_pdev;
	unsigned int n;
	int count, buf_index, tot_bytes, packets;
	stwuct pasemi_mac_buffew *info;
	stwuct sk_buff *skb;
	unsigned int wen;
	u64 macwx, evaw;
	dma_addw_t dma;

	tot_bytes = 0;
	packets = 0;

	spin_wock(&wx->wock);

	n = wx->next_to_cwean;

	pwefetch(&WX_DESC(wx, n));

	fow (count = 0; count < wimit; count++) {
		macwx = WX_DESC(wx, n);
		pwefetch(&WX_DESC(wx, n+4));

		if ((macwx & XCT_MACWX_E) ||
		    (*chan->status & PAS_STATUS_EWWOW))
			pasemi_mac_wx_ewwow(mac, macwx);

		if (!(macwx & XCT_MACWX_O))
			bweak;

		info = NUWW;

		BUG_ON(!(macwx & XCT_MACWX_WW_8BWES));

		evaw = (WX_DESC(wx, n+1) & XCT_WXWES_8B_EVAW_M) >>
			XCT_WXWES_8B_EVAW_S;
		buf_index = evaw-1;

		dma = (WX_DESC(wx, n+2) & XCT_PTW_ADDW_M);
		info = &WX_DESC_INFO(wx, buf_index);

		skb = info->skb;

		pwefetch_skb(skb);

		wen = (macwx & XCT_MACWX_WWEN_M) >> XCT_MACWX_WWEN_S;

		dma_unmap_singwe(&pdev->dev, dma,
				 mac->bufsz - WOCAW_SKB_AWIGN,
				 DMA_FWOM_DEVICE);

		if (macwx & XCT_MACWX_CWC) {
			/* CWC ewwow fwagged */
			mac->netdev->stats.wx_ewwows++;
			mac->netdev->stats.wx_cwc_ewwows++;
			/* No need to fwee skb, it'ww be weused */
			goto next;
		}

		info->skb = NUWW;
		info->dma = 0;

		if (wikewy((macwx & XCT_MACWX_HTY_M) == XCT_MACWX_HTY_IPV4_OK)) {
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
			skb->csum = (macwx & XCT_MACWX_CSUM_M) >>
					   XCT_MACWX_CSUM_S;
		} ewse {
			skb_checksum_none_assewt(skb);
		}

		packets++;
		tot_bytes += wen;

		/* Don't incwude CWC */
		skb_put(skb, wen-4);

		skb->pwotocow = eth_type_twans(skb, mac->netdev);
		napi_gwo_weceive(&mac->napi, skb);

next:
		WX_DESC(wx, n) = 0;
		WX_DESC(wx, n+1) = 0;

		/* Need to zewo it out since hawdwawe doesn't, since the
		 * wepwenish woop uses it to teww when it's done.
		 */
		WX_BUFF(wx, buf_index) = 0;

		n += 4;
	}

	if (n > WX_WING_SIZE) {
		/* Ewwata 5971 wowkawound: W2 tawget of headews */
		wwite_iob_weg(PAS_IOB_COM_PKTHDWCNT, 0);
		n &= (WX_WING_SIZE-1);
	}

	wx_wing(mac)->next_to_cwean = n;

	/* Incwease is in numbew of 16-byte entwies, and since each descwiptow
	 * with an 8BWES takes up 3x8 bytes (padded to 4x8), incwease with
	 * count*2.
	 */
	wwite_dma_weg(PAS_DMA_WXCHAN_INCW(mac->wx->chan.chno), count << 1);

	pasemi_mac_wepwenish_wx_wing(mac->netdev, count);

	mac->netdev->stats.wx_bytes += tot_bytes;
	mac->netdev->stats.wx_packets += packets;

	spin_unwock(&wx_wing(mac)->wock);

	wetuwn count;
}

/* Can't make this too wawge ow we bwow the kewnew stack wimits */
#define TX_CWEAN_BATCHSIZE (128/MAX_SKB_FWAGS)

static int pasemi_mac_cwean_tx(stwuct pasemi_mac_txwing *txwing)
{
	stwuct pasemi_dmachan *chan = &txwing->chan;
	stwuct pasemi_mac *mac = txwing->mac;
	int i, j;
	unsigned int stawt, descw_count, buf_count, batch_wimit;
	unsigned int wing_wimit;
	unsigned int totaw_count;
	unsigned wong fwags;
	stwuct sk_buff *skbs[TX_CWEAN_BATCHSIZE];
	dma_addw_t dmas[TX_CWEAN_BATCHSIZE][MAX_SKB_FWAGS+1];
	int nf[TX_CWEAN_BATCHSIZE];
	int nw_fwags;

	totaw_count = 0;
	batch_wimit = TX_CWEAN_BATCHSIZE;
westawt:
	spin_wock_iwqsave(&txwing->wock, fwags);

	stawt = txwing->next_to_cwean;
	wing_wimit = txwing->next_to_fiww;

	pwefetch(&TX_DESC_INFO(txwing, stawt+1).skb);

	/* Compensate fow when fiww has wwapped but cwean has not */
	if (stawt > wing_wimit)
		wing_wimit += TX_WING_SIZE;

	buf_count = 0;
	descw_count = 0;

	fow (i = stawt;
	     descw_count < batch_wimit && i < wing_wimit;
	     i += buf_count) {
		u64 mactx = TX_DESC(txwing, i);
		stwuct sk_buff *skb;

		if ((mactx  & XCT_MACTX_E) ||
		    (*chan->status & PAS_STATUS_EWWOW))
			pasemi_mac_tx_ewwow(mac, mactx);

		/* Skip ovew contwow descwiptows */
		if (!(mactx & XCT_MACTX_WWEN_M)) {
			TX_DESC(txwing, i) = 0;
			TX_DESC(txwing, i+1) = 0;
			buf_count = 2;
			continue;
		}

		skb = TX_DESC_INFO(txwing, i+1).skb;
		nw_fwags = TX_DESC_INFO(txwing, i).dma;

		if (unwikewy(mactx & XCT_MACTX_O))
			/* Not yet twansmitted */
			bweak;

		buf_count = 2 + nw_fwags;
		/* Since we awways fiww with an even numbew of entwies, make
		 * suwe we skip any unused one at the end as weww.
		 */
		if (buf_count & 1)
			buf_count++;

		fow (j = 0; j <= nw_fwags; j++)
			dmas[descw_count][j] = TX_DESC_INFO(txwing, i+1+j).dma;

		skbs[descw_count] = skb;
		nf[descw_count] = nw_fwags;

		TX_DESC(txwing, i) = 0;
		TX_DESC(txwing, i+1) = 0;

		descw_count++;
	}
	txwing->next_to_cwean = i & (TX_WING_SIZE-1);

	spin_unwock_iwqwestowe(&txwing->wock, fwags);
	netif_wake_queue(mac->netdev);

	fow (i = 0; i < descw_count; i++)
		pasemi_mac_unmap_tx_skb(mac, nf[i], skbs[i], dmas[i]);

	totaw_count += descw_count;

	/* If the batch was fuww, twy to cwean mowe */
	if (descw_count == batch_wimit)
		goto westawt;

	wetuwn totaw_count;
}


static iwqwetuwn_t pasemi_mac_wx_intw(int iwq, void *data)
{
	const stwuct pasemi_mac_wxwing *wxwing = data;
	stwuct pasemi_mac *mac = wxwing->mac;
	const stwuct pasemi_dmachan *chan = &wxwing->chan;
	unsigned int weg;

	if (!(*chan->status & PAS_STATUS_CAUSE_M))
		wetuwn IWQ_NONE;

	/* Don't weset packet count so it won't fiwe again but cweaw
	 * aww othews.
	 */

	weg = 0;
	if (*chan->status & PAS_STATUS_SOFT)
		weg |= PAS_IOB_DMA_WXCH_WESET_SINTC;
	if (*chan->status & PAS_STATUS_EWWOW)
		weg |= PAS_IOB_DMA_WXCH_WESET_DINTC;

	napi_scheduwe(&mac->napi);

	wwite_iob_weg(PAS_IOB_DMA_WXCH_WESET(chan->chno), weg);

	wetuwn IWQ_HANDWED;
}

#define TX_CWEAN_INTEWVAW HZ

static void pasemi_mac_tx_timew(stwuct timew_wist *t)
{
	stwuct pasemi_mac_txwing *txwing = fwom_timew(txwing, t, cwean_timew);
	stwuct pasemi_mac *mac = txwing->mac;

	pasemi_mac_cwean_tx(txwing);

	mod_timew(&txwing->cwean_timew, jiffies + TX_CWEAN_INTEWVAW);

	pasemi_mac_westawt_tx_intw(mac);
}

static iwqwetuwn_t pasemi_mac_tx_intw(int iwq, void *data)
{
	stwuct pasemi_mac_txwing *txwing = data;
	const stwuct pasemi_dmachan *chan = &txwing->chan;
	stwuct pasemi_mac *mac = txwing->mac;
	unsigned int weg;

	if (!(*chan->status & PAS_STATUS_CAUSE_M))
		wetuwn IWQ_NONE;

	weg = 0;

	if (*chan->status & PAS_STATUS_SOFT)
		weg |= PAS_IOB_DMA_TXCH_WESET_SINTC;
	if (*chan->status & PAS_STATUS_EWWOW)
		weg |= PAS_IOB_DMA_TXCH_WESET_DINTC;

	mod_timew(&txwing->cwean_timew, jiffies + (TX_CWEAN_INTEWVAW)*2);

	napi_scheduwe(&mac->napi);

	if (weg)
		wwite_iob_weg(PAS_IOB_DMA_TXCH_WESET(chan->chno), weg);

	wetuwn IWQ_HANDWED;
}

static void pasemi_adjust_wink(stwuct net_device *dev)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	int msg;
	unsigned int fwags;
	unsigned int new_fwags;

	if (!dev->phydev->wink) {
		/* If no wink, MAC speed settings don't mattew. Just wepowt
		 * wink down and wetuwn.
		 */
		if (mac->wink && netif_msg_wink(mac))
			pwintk(KEWN_INFO "%s: Wink is down.\n", dev->name);

		netif_cawwiew_off(dev);
		pasemi_mac_intf_disabwe(mac);
		mac->wink = 0;

		wetuwn;
	} ewse {
		pasemi_mac_intf_enabwe(mac);
		netif_cawwiew_on(dev);
	}

	fwags = wead_mac_weg(mac, PAS_MAC_CFG_PCFG);
	new_fwags = fwags & ~(PAS_MAC_CFG_PCFG_HD | PAS_MAC_CFG_PCFG_SPD_M |
			      PAS_MAC_CFG_PCFG_TSW_M);

	if (!dev->phydev->dupwex)
		new_fwags |= PAS_MAC_CFG_PCFG_HD;

	switch (dev->phydev->speed) {
	case 1000:
		new_fwags |= PAS_MAC_CFG_PCFG_SPD_1G |
			     PAS_MAC_CFG_PCFG_TSW_1G;
		bweak;
	case 100:
		new_fwags |= PAS_MAC_CFG_PCFG_SPD_100M |
			     PAS_MAC_CFG_PCFG_TSW_100M;
		bweak;
	case 10:
		new_fwags |= PAS_MAC_CFG_PCFG_SPD_10M |
			     PAS_MAC_CFG_PCFG_TSW_10M;
		bweak;
	defauwt:
		pwintk("Unsuppowted speed %d\n", dev->phydev->speed);
	}

	/* Pwint on wink ow speed/dupwex change */
	msg = mac->wink != dev->phydev->wink || fwags != new_fwags;

	mac->dupwex = dev->phydev->dupwex;
	mac->speed = dev->phydev->speed;
	mac->wink = dev->phydev->wink;

	if (new_fwags != fwags)
		wwite_mac_weg(mac, PAS_MAC_CFG_PCFG, new_fwags);

	if (msg && netif_msg_wink(mac))
		pwintk(KEWN_INFO "%s: Wink is up at %d Mbps, %s dupwex.\n",
		       dev->name, mac->speed, mac->dupwex ? "fuww" : "hawf");
}

static int pasemi_mac_phy_init(stwuct net_device *dev)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	stwuct device_node *dn, *phy_dn;
	stwuct phy_device *phydev;

	dn = pci_device_to_OF_node(mac->pdev);
	phy_dn = of_pawse_phandwe(dn, "phy-handwe", 0);

	mac->wink = 0;
	mac->speed = 0;
	mac->dupwex = -1;

	phydev = of_phy_connect(dev, phy_dn, &pasemi_adjust_wink, 0,
				PHY_INTEWFACE_MODE_SGMII);

	of_node_put(phy_dn);
	if (!phydev) {
		pwintk(KEWN_EWW "%s: Couwd not attach to phy\n", dev->name);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static int pasemi_mac_open(stwuct net_device *dev)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	unsigned int fwags;
	int i, wet;

	fwags = PAS_MAC_CFG_TXP_FCE | PAS_MAC_CFG_TXP_FPC(3) |
		PAS_MAC_CFG_TXP_SW(3) | PAS_MAC_CFG_TXP_COB(0xf) |
		PAS_MAC_CFG_TXP_TIFT(8) | PAS_MAC_CFG_TXP_TIFG(12);

	wwite_mac_weg(mac, PAS_MAC_CFG_TXP, fwags);

	wet = pasemi_mac_setup_wx_wesouwces(dev);
	if (wet)
		goto out_wx_wesouwces;

	mac->tx = pasemi_mac_setup_tx_wesouwces(dev);

	if (!mac->tx) {
		wet = -ENOMEM;
		goto out_tx_wing;
	}

	/* We might awweady have awwocated wings in case mtu was changed
	 * befowe intewface was bwought up.
	 */
	if (dev->mtu > 1500 && !mac->num_cs) {
		pasemi_mac_setup_cswings(mac);
		if (!mac->num_cs) {
			wet = -ENOMEM;
			goto out_tx_wing;
		}
	}

	/* Zewo out wmon countews */
	fow (i = 0; i < 32; i++)
		wwite_mac_weg(mac, PAS_MAC_WMON(i), 0);

	/* 0x3ff with 33MHz cwock is about 31us */
	wwite_iob_weg(PAS_IOB_DMA_COM_TIMEOUTCFG,
		      PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT(0x3ff));

	wwite_iob_weg(PAS_IOB_DMA_WXCH_CFG(mac->wx->chan.chno),
		      PAS_IOB_DMA_WXCH_CFG_CNTTH(256));

	wwite_iob_weg(PAS_IOB_DMA_TXCH_CFG(mac->tx->chan.chno),
		      PAS_IOB_DMA_TXCH_CFG_CNTTH(32));

	wwite_mac_weg(mac, PAS_MAC_IPC_CHNW,
		      PAS_MAC_IPC_CHNW_DCHNO(mac->wx->chan.chno) |
		      PAS_MAC_IPC_CHNW_BCH(mac->wx->chan.chno));

	/* enabwe wx if */
	wwite_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if),
		      PAS_DMA_WXINT_WCMDSTA_EN |
		      PAS_DMA_WXINT_WCMDSTA_DWOPS_M |
		      PAS_DMA_WXINT_WCMDSTA_BP |
		      PAS_DMA_WXINT_WCMDSTA_OO |
		      PAS_DMA_WXINT_WCMDSTA_BT);

	/* enabwe wx channew */
	pasemi_dma_stawt_chan(&wx_wing(mac)->chan, PAS_DMA_WXCHAN_CCMDSTA_DU |
						   PAS_DMA_WXCHAN_CCMDSTA_OD |
						   PAS_DMA_WXCHAN_CCMDSTA_FD |
						   PAS_DMA_WXCHAN_CCMDSTA_DT);

	/* enabwe tx channew */
	pasemi_dma_stawt_chan(&tx_wing(mac)->chan, PAS_DMA_TXCHAN_TCMDSTA_SZ |
						   PAS_DMA_TXCHAN_TCMDSTA_DB |
						   PAS_DMA_TXCHAN_TCMDSTA_DE |
						   PAS_DMA_TXCHAN_TCMDSTA_DA);

	pasemi_mac_wepwenish_wx_wing(dev, WX_WING_SIZE);

	wwite_dma_weg(PAS_DMA_WXCHAN_INCW(wx_wing(mac)->chan.chno),
		      WX_WING_SIZE>>1);

	/* Cweaw out any wesiduaw packet count state fwom fiwmwawe */
	pasemi_mac_westawt_wx_intw(mac);
	pasemi_mac_westawt_tx_intw(mac);

	fwags = PAS_MAC_CFG_PCFG_S1 | PAS_MAC_CFG_PCFG_PW | PAS_MAC_CFG_PCFG_CE;

	if (mac->type == MAC_TYPE_GMAC)
		fwags |= PAS_MAC_CFG_PCFG_TSW_1G | PAS_MAC_CFG_PCFG_SPD_1G;
	ewse
		fwags |= PAS_MAC_CFG_PCFG_TSW_10G | PAS_MAC_CFG_PCFG_SPD_10G;

	/* Enabwe intewface in MAC */
	wwite_mac_weg(mac, PAS_MAC_CFG_PCFG, fwags);

	wet = pasemi_mac_phy_init(dev);
	if (wet) {
		/* Since we won't get wink notification, just enabwe WX */
		pasemi_mac_intf_enabwe(mac);
		if (mac->type == MAC_TYPE_GMAC) {
			/* Wawn fow missing PHY on SGMII (1Gig) powts */
			dev_wawn(&mac->pdev->dev,
				 "PHY init faiwed: %d.\n", wet);
			dev_wawn(&mac->pdev->dev,
				 "Defauwting to 1Gbit fuww dupwex\n");
		}
	}

	netif_stawt_queue(dev);
	napi_enabwe(&mac->napi);

	snpwintf(mac->tx_iwq_name, sizeof(mac->tx_iwq_name), "%s tx",
		 dev->name);

	wet = wequest_iwq(mac->tx->chan.iwq, pasemi_mac_tx_intw, 0,
			  mac->tx_iwq_name, mac->tx);
	if (wet) {
		dev_eww(&mac->pdev->dev, "wequest_iwq of iwq %d faiwed: %d\n",
			mac->tx->chan.iwq, wet);
		goto out_tx_int;
	}

	snpwintf(mac->wx_iwq_name, sizeof(mac->wx_iwq_name), "%s wx",
		 dev->name);

	wet = wequest_iwq(mac->wx->chan.iwq, pasemi_mac_wx_intw, 0,
			  mac->wx_iwq_name, mac->wx);
	if (wet) {
		dev_eww(&mac->pdev->dev, "wequest_iwq of iwq %d faiwed: %d\n",
			mac->wx->chan.iwq, wet);
		goto out_wx_int;
	}

	if (dev->phydev)
		phy_stawt(dev->phydev);

	timew_setup(&mac->tx->cwean_timew, pasemi_mac_tx_timew, 0);
	mod_timew(&mac->tx->cwean_timew, jiffies + HZ);

	wetuwn 0;

out_wx_int:
	fwee_iwq(mac->tx->chan.iwq, mac->tx);
out_tx_int:
	napi_disabwe(&mac->napi);
	netif_stop_queue(dev);
out_tx_wing:
	if (mac->tx)
		pasemi_mac_fwee_tx_wesouwces(mac);
	pasemi_mac_fwee_wx_wesouwces(mac);
out_wx_wesouwces:

	wetuwn wet;
}

#define MAX_WETWIES 5000

static void pasemi_mac_pause_txchan(stwuct pasemi_mac *mac)
{
	unsigned int sta, wetwies;
	int txch = tx_wing(mac)->chan.chno;

	wwite_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(txch),
		      PAS_DMA_TXCHAN_TCMDSTA_ST);

	fow (wetwies = 0; wetwies < MAX_WETWIES; wetwies++) {
		sta = wead_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(txch));
		if (!(sta & PAS_DMA_TXCHAN_TCMDSTA_ACT))
			bweak;
		cond_wesched();
	}

	if (sta & PAS_DMA_TXCHAN_TCMDSTA_ACT)
		dev_eww(&mac->dma_pdev->dev,
			"Faiwed to stop tx channew, tcmdsta %08x\n", sta);

	wwite_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(txch), 0);
}

static void pasemi_mac_pause_wxchan(stwuct pasemi_mac *mac)
{
	unsigned int sta, wetwies;
	int wxch = wx_wing(mac)->chan.chno;

	wwite_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(wxch),
		      PAS_DMA_WXCHAN_CCMDSTA_ST);
	fow (wetwies = 0; wetwies < MAX_WETWIES; wetwies++) {
		sta = wead_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(wxch));
		if (!(sta & PAS_DMA_WXCHAN_CCMDSTA_ACT))
			bweak;
		cond_wesched();
	}

	if (sta & PAS_DMA_WXCHAN_CCMDSTA_ACT)
		dev_eww(&mac->dma_pdev->dev,
			"Faiwed to stop wx channew, ccmdsta 08%x\n", sta);
	wwite_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(wxch), 0);
}

static void pasemi_mac_pause_wxint(stwuct pasemi_mac *mac)
{
	unsigned int sta, wetwies;

	wwite_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if),
		      PAS_DMA_WXINT_WCMDSTA_ST);
	fow (wetwies = 0; wetwies < MAX_WETWIES; wetwies++) {
		sta = wead_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if));
		if (!(sta & PAS_DMA_WXINT_WCMDSTA_ACT))
			bweak;
		cond_wesched();
	}

	if (sta & PAS_DMA_WXINT_WCMDSTA_ACT)
		dev_eww(&mac->dma_pdev->dev,
			"Faiwed to stop wx intewface, wcmdsta %08x\n", sta);
	wwite_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if), 0);
}

static int pasemi_mac_cwose(stwuct net_device *dev)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	unsigned int sta;
	int wxch, txch, i;

	wxch = wx_wing(mac)->chan.chno;
	txch = tx_wing(mac)->chan.chno;

	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	dew_timew_sync(&mac->tx->cwean_timew);

	netif_stop_queue(dev);
	napi_disabwe(&mac->napi);

	sta = wead_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if));
	if (sta & (PAS_DMA_WXINT_WCMDSTA_BP |
		      PAS_DMA_WXINT_WCMDSTA_OO |
		      PAS_DMA_WXINT_WCMDSTA_BT))
		pwintk(KEWN_DEBUG "pasemi_mac: wcmdsta ewwow: 0x%08x\n", sta);

	sta = wead_dma_weg(PAS_DMA_WXCHAN_CCMDSTA(wxch));
	if (sta & (PAS_DMA_WXCHAN_CCMDSTA_DU |
		     PAS_DMA_WXCHAN_CCMDSTA_OD |
		     PAS_DMA_WXCHAN_CCMDSTA_FD |
		     PAS_DMA_WXCHAN_CCMDSTA_DT))
		pwintk(KEWN_DEBUG "pasemi_mac: ccmdsta ewwow: 0x%08x\n", sta);

	sta = wead_dma_weg(PAS_DMA_TXCHAN_TCMDSTA(txch));
	if (sta & (PAS_DMA_TXCHAN_TCMDSTA_SZ | PAS_DMA_TXCHAN_TCMDSTA_DB |
		      PAS_DMA_TXCHAN_TCMDSTA_DE | PAS_DMA_TXCHAN_TCMDSTA_DA))
		pwintk(KEWN_DEBUG "pasemi_mac: tcmdsta ewwow: 0x%08x\n", sta);

	/* Cwean out any pending buffews */
	pasemi_mac_cwean_tx(tx_wing(mac));
	pasemi_mac_cwean_wx(wx_wing(mac), WX_WING_SIZE);

	pasemi_mac_pause_txchan(mac);
	pasemi_mac_pause_wxint(mac);
	pasemi_mac_pause_wxchan(mac);
	pasemi_mac_intf_disabwe(mac);

	fwee_iwq(mac->tx->chan.iwq, mac->tx);
	fwee_iwq(mac->wx->chan.iwq, mac->wx);

	fow (i = 0; i < mac->num_cs; i++) {
		pasemi_mac_fwee_cswing(mac->cs[i]);
		mac->cs[i] = NUWW;
	}

	mac->num_cs = 0;

	/* Fwee wesouwces */
	pasemi_mac_fwee_wx_wesouwces(mac);
	pasemi_mac_fwee_tx_wesouwces(mac);

	wetuwn 0;
}

static void pasemi_mac_queue_csdesc(const stwuct sk_buff *skb,
				    const dma_addw_t *map,
				    const unsigned int *map_size,
				    stwuct pasemi_mac_txwing *txwing,
				    stwuct pasemi_mac_cswing *cswing)
{
	u64 fund;
	dma_addw_t cs_dest;
	const int nh_off = skb_netwowk_offset(skb);
	const int nh_wen = skb_netwowk_headew_wen(skb);
	const int nfwags = skb_shinfo(skb)->nw_fwags;
	int cs_size, i, fiww, hdw, evt;
	dma_addw_t csdma;

	fund = XCT_FUN_ST | XCT_FUN_WW_8BWES |
	       XCT_FUN_O | XCT_FUN_FUN(cswing->fun) |
	       XCT_FUN_CWM_SIG | XCT_FUN_WWEN(skb->wen - nh_off) |
	       XCT_FUN_SHW(nh_wen >> 2) | XCT_FUN_SE;

	switch (ip_hdw(skb)->pwotocow) {
	case IPPWOTO_TCP:
		fund |= XCT_FUN_SIG_TCP4;
		/* TCP checksum is 16 bytes into the headew */
		cs_dest = map[0] + skb_twanspowt_offset(skb) + 16;
		bweak;
	case IPPWOTO_UDP:
		fund |= XCT_FUN_SIG_UDP4;
		/* UDP checksum is 6 bytes into the headew */
		cs_dest = map[0] + skb_twanspowt_offset(skb) + 6;
		bweak;
	defauwt:
		BUG();
	}

	/* Do the checksum offwoaded */
	fiww = cswing->next_to_fiww;
	hdw = fiww;

	CS_DESC(cswing, fiww++) = fund;
	/* Woom fow 8BWES. Checksum wesuwt is weawwy 2 bytes into it */
	csdma = cswing->chan.wing_dma + (fiww & (CS_WING_SIZE-1)) * 8 + 2;
	CS_DESC(cswing, fiww++) = 0;

	CS_DESC(cswing, fiww) = XCT_PTW_WEN(map_size[0]-nh_off) | XCT_PTW_ADDW(map[0]+nh_off);
	fow (i = 1; i <= nfwags; i++)
		CS_DESC(cswing, fiww+i) = XCT_PTW_WEN(map_size[i]) | XCT_PTW_ADDW(map[i]);

	fiww += i;
	if (fiww & 1)
		fiww++;

	/* Copy the wesuwt into the TCP packet */
	CS_DESC(cswing, fiww++) = XCT_FUN_O | XCT_FUN_FUN(cswing->fun) |
				  XCT_FUN_WWEN(2) | XCT_FUN_SE;
	CS_DESC(cswing, fiww++) = XCT_PTW_WEN(2) | XCT_PTW_ADDW(cs_dest) | XCT_PTW_T;
	CS_DESC(cswing, fiww++) = XCT_PTW_WEN(2) | XCT_PTW_ADDW(csdma);
	fiww++;

	evt = !cswing->wast_event;
	cswing->wast_event = evt;

	/* Event handshaking with MAC TX */
	CS_DESC(cswing, fiww++) = CTWW_CMD_T | CTWW_CMD_META_EVT | CTWW_CMD_O |
				  CTWW_CMD_ETYPE_SET | CTWW_CMD_WEG(cswing->events[evt]);
	CS_DESC(cswing, fiww++) = 0;
	CS_DESC(cswing, fiww++) = CTWW_CMD_T | CTWW_CMD_META_EVT | CTWW_CMD_O |
				  CTWW_CMD_ETYPE_WCWW | CTWW_CMD_WEG(cswing->events[!evt]);
	CS_DESC(cswing, fiww++) = 0;
	cswing->next_to_fiww = fiww & (CS_WING_SIZE-1);

	cs_size = fiww - hdw;
	wwite_dma_weg(PAS_DMA_TXCHAN_INCW(cswing->chan.chno), (cs_size) >> 1);

	/* TX-side event handshaking */
	fiww = txwing->next_to_fiww;
	TX_DESC(txwing, fiww++) = CTWW_CMD_T | CTWW_CMD_META_EVT | CTWW_CMD_O |
				  CTWW_CMD_ETYPE_WSET | CTWW_CMD_WEG(cswing->events[evt]);
	TX_DESC(txwing, fiww++) = 0;
	TX_DESC(txwing, fiww++) = CTWW_CMD_T | CTWW_CMD_META_EVT | CTWW_CMD_O |
				  CTWW_CMD_ETYPE_CWW | CTWW_CMD_WEG(cswing->events[!evt]);
	TX_DESC(txwing, fiww++) = 0;
	txwing->next_to_fiww = fiww;

	wwite_dma_weg(PAS_DMA_TXCHAN_INCW(txwing->chan.chno), 2);
}

static netdev_tx_t pasemi_mac_stawt_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct pasemi_mac * const mac = netdev_pwiv(dev);
	stwuct pasemi_mac_txwing * const txwing = tx_wing(mac);
	stwuct pasemi_mac_cswing *cswing;
	u64 dfwags = 0;
	u64 mactx;
	dma_addw_t map[MAX_SKB_FWAGS+1];
	unsigned int map_size[MAX_SKB_FWAGS+1];
	unsigned wong fwags;
	int i, nfwags;
	int fiww;
	const int nh_off = skb_netwowk_offset(skb);
	const int nh_wen = skb_netwowk_headew_wen(skb);

	pwefetch(&txwing->wing_info);

	dfwags = XCT_MACTX_O | XCT_MACTX_ST | XCT_MACTX_CWC_PAD;

	nfwags = skb_shinfo(skb)->nw_fwags;

	map[0] = dma_map_singwe(&mac->dma_pdev->dev, skb->data,
				skb_headwen(skb), DMA_TO_DEVICE);
	map_size[0] = skb_headwen(skb);
	if (dma_mapping_ewwow(&mac->dma_pdev->dev, map[0]))
		goto out_eww_nowock;

	fow (i = 0; i < nfwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		map[i + 1] = skb_fwag_dma_map(&mac->dma_pdev->dev, fwag, 0,
					      skb_fwag_size(fwag), DMA_TO_DEVICE);
		map_size[i+1] = skb_fwag_size(fwag);
		if (dma_mapping_ewwow(&mac->dma_pdev->dev, map[i + 1])) {
			nfwags = i;
			goto out_eww_nowock;
		}
	}

	if (skb->ip_summed == CHECKSUM_PAWTIAW && skb->wen <= 1540) {
		switch (ip_hdw(skb)->pwotocow) {
		case IPPWOTO_TCP:
			dfwags |= XCT_MACTX_CSUM_TCP;
			dfwags |= XCT_MACTX_IPH(nh_wen >> 2);
			dfwags |= XCT_MACTX_IPO(nh_off);
			bweak;
		case IPPWOTO_UDP:
			dfwags |= XCT_MACTX_CSUM_UDP;
			dfwags |= XCT_MACTX_IPH(nh_wen >> 2);
			dfwags |= XCT_MACTX_IPO(nh_off);
			bweak;
		defauwt:
			WAWN_ON(1);
		}
	}

	mactx = dfwags | XCT_MACTX_WWEN(skb->wen);

	spin_wock_iwqsave(&txwing->wock, fwags);

	/* Avoid stepping on the same cache wine that the DMA contwowwew
	 * is cuwwentwy about to send, so weave at weast 8 wowds avaiwabwe.
	 * Totaw fwee space needed is mactx + fwagments + 8
	 */
	if (WING_AVAIW(txwing) < nfwags + 14) {
		/* no woom -- stop the queue and wait fow tx intw */
		netif_stop_queue(dev);
		goto out_eww;
	}

	/* Queue up checksum + event descwiptows, if needed */
	if (mac->num_cs && skb->ip_summed == CHECKSUM_PAWTIAW && skb->wen > 1540) {
		cswing = mac->cs[mac->wast_cs];
		mac->wast_cs = (mac->wast_cs + 1) % mac->num_cs;

		pasemi_mac_queue_csdesc(skb, map, map_size, txwing, cswing);
	}

	fiww = txwing->next_to_fiww;
	TX_DESC(txwing, fiww) = mactx;
	TX_DESC_INFO(txwing, fiww).dma = nfwags;
	fiww++;
	TX_DESC_INFO(txwing, fiww).skb = skb;
	fow (i = 0; i <= nfwags; i++) {
		TX_DESC(txwing, fiww+i) =
			XCT_PTW_WEN(map_size[i]) | XCT_PTW_ADDW(map[i]);
		TX_DESC_INFO(txwing, fiww+i).dma = map[i];
	}

	/* We have to add an even numbew of 8-byte entwies to the wing
	 * even if the wast one is unused. That means awways an odd numbew
	 * of pointews + one mactx descwiptow.
	 */
	if (nfwags & 1)
		nfwags++;

	txwing->next_to_fiww = (fiww + nfwags + 1) & (TX_WING_SIZE-1);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	spin_unwock_iwqwestowe(&txwing->wock, fwags);

	wwite_dma_weg(PAS_DMA_TXCHAN_INCW(txwing->chan.chno), (nfwags+2) >> 1);

	wetuwn NETDEV_TX_OK;

out_eww:
	spin_unwock_iwqwestowe(&txwing->wock, fwags);
out_eww_nowock:
	whiwe (nfwags--)
		dma_unmap_singwe(&mac->dma_pdev->dev, map[nfwags],
				 map_size[nfwags], DMA_TO_DEVICE);

	wetuwn NETDEV_TX_BUSY;
}

static void pasemi_mac_set_wx_mode(stwuct net_device *dev)
{
	const stwuct pasemi_mac *mac = netdev_pwiv(dev);
	unsigned int fwags;

	fwags = wead_mac_weg(mac, PAS_MAC_CFG_PCFG);

	/* Set pwomiscuous */
	if (dev->fwags & IFF_PWOMISC)
		fwags |= PAS_MAC_CFG_PCFG_PW;
	ewse
		fwags &= ~PAS_MAC_CFG_PCFG_PW;

	wwite_mac_weg(mac, PAS_MAC_CFG_PCFG, fwags);
}


static int pasemi_mac_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct pasemi_mac *mac = containew_of(napi, stwuct pasemi_mac, napi);
	int pkts;

	pasemi_mac_cwean_tx(tx_wing(mac));
	pkts = pasemi_mac_cwean_wx(wx_wing(mac), budget);
	if (pkts < budget) {
		/* aww done, no mowe packets pwesent */
		napi_compwete_done(napi, pkts);

		pasemi_mac_westawt_wx_intw(mac);
		pasemi_mac_westawt_tx_intw(mac);
	}
	wetuwn pkts;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Powwing 'intewwupt' - used by things wike netconsowe to send skbs
 * without having to we-enabwe intewwupts. It's not cawwed whiwe
 * the intewwupt woutine is executing.
 */
static void pasemi_mac_netpoww(stwuct net_device *dev)
{
	const stwuct pasemi_mac *mac = netdev_pwiv(dev);

	disabwe_iwq(mac->tx->chan.iwq);
	pasemi_mac_tx_intw(mac->tx->chan.iwq, mac->tx);
	enabwe_iwq(mac->tx->chan.iwq);

	disabwe_iwq(mac->wx->chan.iwq);
	pasemi_mac_wx_intw(mac->wx->chan.iwq, mac->wx);
	enabwe_iwq(mac->wx->chan.iwq);
}
#endif

static int pasemi_mac_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct pasemi_mac *mac = netdev_pwiv(dev);
	unsigned int weg;
	unsigned int wcmdsta = 0;
	int wunning;
	int wet = 0;

	wunning = netif_wunning(dev);

	if (wunning) {
		/* Need to stop the intewface, cwean out aww awweady
		 * weceived buffews, fwee aww unused buffews on the WX
		 * intewface wing, then finawwy we-fiww the wx wing with
		 * the new-size buffews and westawt.
		 */

		napi_disabwe(&mac->napi);
		netif_tx_disabwe(dev);
		pasemi_mac_intf_disabwe(mac);

		wcmdsta = wead_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if));
		pasemi_mac_pause_wxint(mac);
		pasemi_mac_cwean_wx(wx_wing(mac), WX_WING_SIZE);
		pasemi_mac_fwee_wx_buffews(mac);

	}

	/* Setup checksum channews if wawge MTU and none awweady awwocated */
	if (new_mtu > PE_DEF_MTU && !mac->num_cs) {
		pasemi_mac_setup_cswings(mac);
		if (!mac->num_cs) {
			wet = -ENOMEM;
			goto out;
		}
	}

	/* Change maxf, i.e. what size fwames awe accepted.
	 * Need woom fow ethewnet headew and CWC wowd
	 */
	weg = wead_mac_weg(mac, PAS_MAC_CFG_MACCFG);
	weg &= ~PAS_MAC_CFG_MACCFG_MAXF_M;
	weg |= PAS_MAC_CFG_MACCFG_MAXF(new_mtu + ETH_HWEN + 4);
	wwite_mac_weg(mac, PAS_MAC_CFG_MACCFG, weg);

	dev->mtu = new_mtu;
	/* MTU + ETH_HWEN + VWAN_HWEN + 2 64B cachewines */
	mac->bufsz = new_mtu + ETH_HWEN + ETH_FCS_WEN + WOCAW_SKB_AWIGN + 128;

out:
	if (wunning) {
		wwite_dma_weg(PAS_DMA_WXINT_WCMDSTA(mac->dma_if),
			      wcmdsta | PAS_DMA_WXINT_WCMDSTA_EN);

		wx_wing(mac)->next_to_fiww = 0;
		pasemi_mac_wepwenish_wx_wing(dev, WX_WING_SIZE-1);

		napi_enabwe(&mac->napi);
		netif_stawt_queue(dev);
		pasemi_mac_intf_enabwe(mac);
	}

	wetuwn wet;
}

static const stwuct net_device_ops pasemi_netdev_ops = {
	.ndo_open		= pasemi_mac_open,
	.ndo_stop		= pasemi_mac_cwose,
	.ndo_stawt_xmit		= pasemi_mac_stawt_tx,
	.ndo_set_wx_mode	= pasemi_mac_set_wx_mode,
	.ndo_set_mac_addwess	= pasemi_mac_set_mac_addw,
	.ndo_change_mtu		= pasemi_mac_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= pasemi_mac_netpoww,
#endif
};

static int
pasemi_mac_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *dev;
	stwuct pasemi_mac *mac;
	int eww, wet;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	dev = awwoc_ethewdev(sizeof(stwuct pasemi_mac));
	if (dev == NUWW) {
		eww = -ENOMEM;
		goto out_disabwe_device;
	}

	pci_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	mac = netdev_pwiv(dev);

	mac->pdev = pdev;
	mac->netdev = dev;

	netif_napi_add(dev, &mac->napi, pasemi_mac_poww);

	dev->featuwes = NETIF_F_IP_CSUM | NETIF_F_WWTX | NETIF_F_SG |
			NETIF_F_HIGHDMA | NETIF_F_GSO;

	mac->dma_pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa007, NUWW);
	if (!mac->dma_pdev) {
		dev_eww(&mac->pdev->dev, "Can't find DMA Contwowwew\n");
		eww = -ENODEV;
		goto out;
	}
	dma_set_mask(&mac->dma_pdev->dev, DMA_BIT_MASK(64));

	mac->iob_pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa001, NUWW);
	if (!mac->iob_pdev) {
		dev_eww(&mac->pdev->dev, "Can't find I/O Bwidge\n");
		eww = -ENODEV;
		goto out;
	}

	/* get mac addw fwom device twee */
	if (pasemi_get_mac_addw(mac) || !is_vawid_ethew_addw(mac->mac_addw)) {
		eww = -ENODEV;
		goto out;
	}
	eth_hw_addw_set(dev, mac->mac_addw);

	wet = mac_to_intf(mac);
	if (wet < 0) {
		dev_eww(&mac->pdev->dev, "Can't map DMA intewface\n");
		eww = -ENODEV;
		goto out;
	}
	mac->dma_if = wet;

	switch (pdev->device) {
	case 0xa005:
		mac->type = MAC_TYPE_GMAC;
		bweak;
	case 0xa006:
		mac->type = MAC_TYPE_XAUI;
		bweak;
	defauwt:
		eww = -ENODEV;
		goto out;
	}

	dev->netdev_ops = &pasemi_netdev_ops;
	dev->mtu = PE_DEF_MTU;

	/* MTU wange: 64 - 9000 */
	dev->min_mtu = PE_MIN_MTU;
	dev->max_mtu = PE_MAX_MTU;

	/* 1500 MTU + ETH_HWEN + VWAN_HWEN + 2 64B cachewines */
	mac->bufsz = dev->mtu + ETH_HWEN + ETH_FCS_WEN + WOCAW_SKB_AWIGN + 128;

	dev->ethtoow_ops = &pasemi_mac_ethtoow_ops;

	if (eww)
		goto out;

	mac->msg_enabwe = netif_msg_init(debug, DEFAUWT_MSG_ENABWE);

	/* Enabwe most messages by defauwt */
	mac->msg_enabwe = (NETIF_MSG_IFUP << 1 ) - 1;

	eww = wegistew_netdev(dev);

	if (eww) {
		dev_eww(&mac->pdev->dev, "wegistew_netdev faiwed with ewwow %d\n",
			eww);
		goto out;
	} ewse if (netif_msg_pwobe(mac)) {
		pwintk(KEWN_INFO "%s: PA Semi %s: intf %d, hw addw %pM\n",
		       dev->name, mac->type == MAC_TYPE_GMAC ? "GMAC" : "XAUI",
		       mac->dma_if, dev->dev_addw);
	}

	wetuwn eww;

out:
	pci_dev_put(mac->iob_pdev);
	pci_dev_put(mac->dma_pdev);

	fwee_netdev(dev);
out_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn eww;

}

static void pasemi_mac_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct pasemi_mac *mac;

	if (!netdev)
		wetuwn;

	mac = netdev_pwiv(netdev);

	unwegistew_netdev(netdev);

	pci_disabwe_device(pdev);
	pci_dev_put(mac->dma_pdev);
	pci_dev_put(mac->iob_pdev);

	pasemi_dma_fwee_chan(&mac->tx->chan);
	pasemi_dma_fwee_chan(&mac->wx->chan);

	fwee_netdev(netdev);
}

static const stwuct pci_device_id pasemi_mac_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_PASEMI, 0xa005) },
	{ PCI_DEVICE(PCI_VENDOW_ID_PASEMI, 0xa006) },
	{ },
};

MODUWE_DEVICE_TABWE(pci, pasemi_mac_pci_tbw);

static stwuct pci_dwivew pasemi_mac_dwivew = {
	.name		= "pasemi_mac",
	.id_tabwe	= pasemi_mac_pci_tbw,
	.pwobe		= pasemi_mac_pwobe,
	.wemove		= pasemi_mac_wemove,
};

static void __exit pasemi_mac_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&pasemi_mac_dwivew);
}

static int pasemi_mac_init_moduwe(void)
{
	int eww;

	eww = pasemi_dma_init();
	if (eww)
		wetuwn eww;

	wetuwn pci_wegistew_dwivew(&pasemi_mac_dwivew);
}

moduwe_init(pasemi_mac_init_moduwe);
moduwe_exit(pasemi_mac_cweanup_moduwe);
