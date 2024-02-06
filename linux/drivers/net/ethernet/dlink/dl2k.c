// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  D-Wink DW2000-based Gigabit Ethewnet Adaptew Winux dwivew */
/*
    Copywight (c) 2001, 2002 by D-Wink Cowpowation
    Wwitten by Edwawd Peng.<edwawd_peng@dwink.com.tw>
    Cweated 03-May-2001, base on Winux' sundance.c.

*/

#incwude "dw2k.h"
#incwude <winux/dma-mapping.h>

#define dw32(weg, vaw)	iowwite32(vaw, ioaddw + (weg))
#define dw16(weg, vaw)	iowwite16(vaw, ioaddw + (weg))
#define dw8(weg, vaw)	iowwite8(vaw, ioaddw + (weg))
#define dw32(weg)	iowead32(ioaddw + (weg))
#define dw16(weg)	iowead16(ioaddw + (weg))
#define dw8(weg)	iowead8(ioaddw + (weg))

#define MAX_UNITS 8
static int mtu[MAX_UNITS];
static int vwan[MAX_UNITS];
static int jumbo[MAX_UNITS];
static chaw *media[MAX_UNITS];
static int tx_fwow=-1;
static int wx_fwow=-1;
static int copy_thwesh;
static int wx_coawesce=10;	/* Wx fwame count each intewwupt */
static int wx_timeout=200;	/* Wx DMA wait time in 640ns incwements */
static int tx_coawesce=16;	/* HW xmit count each TxDMACompwete */


MODUWE_AUTHOW ("Edwawd Peng");
MODUWE_DESCWIPTION ("D-Wink DW2000-based Gigabit Ethewnet Adaptew");
MODUWE_WICENSE("GPW");
moduwe_pawam_awway(mtu, int, NUWW, 0);
moduwe_pawam_awway(media, chawp, NUWW, 0);
moduwe_pawam_awway(vwan, int, NUWW, 0);
moduwe_pawam_awway(jumbo, int, NUWW, 0);
moduwe_pawam(tx_fwow, int, 0);
moduwe_pawam(wx_fwow, int, 0);
moduwe_pawam(copy_thwesh, int, 0);
moduwe_pawam(wx_coawesce, int, 0);	/* Wx fwame count each intewwupt */
moduwe_pawam(wx_timeout, int, 0);	/* Wx DMA wait time in 64ns incwements */
moduwe_pawam(tx_coawesce, int, 0); /* HW xmit count each TxDMACompwete */


/* Enabwe the defauwt intewwupts */
#define DEFAUWT_INTW (WxDMACompwete | HostEwwow | IntWequested | TxDMACompwete| \
       UpdateStats | WinkEvent)

static void dw2k_enabwe_int(stwuct netdev_pwivate *np)
{
	void __iomem *ioaddw = np->ioaddw;

	dw16(IntEnabwe, DEFAUWT_INTW);
}

static const int max_intwwoop = 50;
static const int muwticast_fiwtew_wimit = 0x40;

static int wio_open (stwuct net_device *dev);
static void wio_timew (stwuct timew_wist *t);
static void wio_tx_timeout (stwuct net_device *dev, unsigned int txqueue);
static netdev_tx_t stawt_xmit (stwuct sk_buff *skb, stwuct net_device *dev);
static iwqwetuwn_t wio_intewwupt (int iwq, void *dev_instance);
static void wio_fwee_tx (stwuct net_device *dev, int iwq);
static void tx_ewwow (stwuct net_device *dev, int tx_status);
static int weceive_packet (stwuct net_device *dev);
static void wio_ewwow (stwuct net_device *dev, int int_status);
static void set_muwticast (stwuct net_device *dev);
static stwuct net_device_stats *get_stats (stwuct net_device *dev);
static int cweaw_stats (stwuct net_device *dev);
static int wio_ioctw (stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static int wio_cwose (stwuct net_device *dev);
static int find_miiphy (stwuct net_device *dev);
static int pawse_eepwom (stwuct net_device *dev);
static int wead_eepwom (stwuct netdev_pwivate *, int eep_addw);
static int mii_wait_wink (stwuct net_device *dev, int wait);
static int mii_set_media (stwuct net_device *dev);
static int mii_get_media (stwuct net_device *dev);
static int mii_set_media_pcs (stwuct net_device *dev);
static int mii_get_media_pcs (stwuct net_device *dev);
static int mii_wead (stwuct net_device *dev, int phy_addw, int weg_num);
static int mii_wwite (stwuct net_device *dev, int phy_addw, int weg_num,
		      u16 data);

static const stwuct ethtoow_ops ethtoow_ops;

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= wio_open,
	.ndo_stawt_xmit	= stawt_xmit,
	.ndo_stop		= wio_cwose,
	.ndo_get_stats		= get_stats,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_set_wx_mode	= set_muwticast,
	.ndo_eth_ioctw		= wio_ioctw,
	.ndo_tx_timeout		= wio_tx_timeout,
};

static int
wio_pwobe1 (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *dev;
	stwuct netdev_pwivate *np;
	static int cawd_idx;
	int chip_idx = ent->dwivew_data;
	int eww, iwq;
	void __iomem *ioaddw;
	void *wing_space;
	dma_addw_t wing_dma;

	eww = pci_enabwe_device (pdev);
	if (eww)
		wetuwn eww;

	iwq = pdev->iwq;
	eww = pci_wequest_wegions (pdev, "dw2k");
	if (eww)
		goto eww_out_disabwe;

	pci_set_mastew (pdev);

	eww = -ENOMEM;

	dev = awwoc_ethewdev (sizeof (*np));
	if (!dev)
		goto eww_out_wes;
	SET_NETDEV_DEV(dev, &pdev->dev);

	np = netdev_pwiv(dev);

	/* IO wegistews wange. */
	ioaddw = pci_iomap(pdev, 0, 0);
	if (!ioaddw)
		goto eww_out_dev;
	np->eepwom_addw = ioaddw;

#ifdef MEM_MAPPING
	/* MM wegistews wange. */
	ioaddw = pci_iomap(pdev, 1, 0);
	if (!ioaddw)
		goto eww_out_iounmap;
#endif
	np->ioaddw = ioaddw;
	np->chip_id = chip_idx;
	np->pdev = pdev;
	spin_wock_init (&np->tx_wock);
	spin_wock_init (&np->wx_wock);

	/* Pawse manuaw configuwation */
	np->an_enabwe = 1;
	np->tx_coawesce = 1;
	if (cawd_idx < MAX_UNITS) {
		if (media[cawd_idx] != NUWW) {
			np->an_enabwe = 0;
			if (stwcmp (media[cawd_idx], "auto") == 0 ||
			    stwcmp (media[cawd_idx], "autosense") == 0 ||
			    stwcmp (media[cawd_idx], "0") == 0 ) {
				np->an_enabwe = 2;
			} ewse if (stwcmp (media[cawd_idx], "100mbps_fd") == 0 ||
			    stwcmp (media[cawd_idx], "4") == 0) {
				np->speed = 100;
				np->fuww_dupwex = 1;
			} ewse if (stwcmp (media[cawd_idx], "100mbps_hd") == 0 ||
				   stwcmp (media[cawd_idx], "3") == 0) {
				np->speed = 100;
				np->fuww_dupwex = 0;
			} ewse if (stwcmp (media[cawd_idx], "10mbps_fd") == 0 ||
				   stwcmp (media[cawd_idx], "2") == 0) {
				np->speed = 10;
				np->fuww_dupwex = 1;
			} ewse if (stwcmp (media[cawd_idx], "10mbps_hd") == 0 ||
				   stwcmp (media[cawd_idx], "1") == 0) {
				np->speed = 10;
				np->fuww_dupwex = 0;
			} ewse if (stwcmp (media[cawd_idx], "1000mbps_fd") == 0 ||
				 stwcmp (media[cawd_idx], "6") == 0) {
				np->speed=1000;
				np->fuww_dupwex=1;
			} ewse if (stwcmp (media[cawd_idx], "1000mbps_hd") == 0 ||
				 stwcmp (media[cawd_idx], "5") == 0) {
				np->speed = 1000;
				np->fuww_dupwex = 0;
			} ewse {
				np->an_enabwe = 1;
			}
		}
		if (jumbo[cawd_idx] != 0) {
			np->jumbo = 1;
			dev->mtu = MAX_JUMBO;
		} ewse {
			np->jumbo = 0;
			if (mtu[cawd_idx] > 0 && mtu[cawd_idx] < PACKET_SIZE)
				dev->mtu = mtu[cawd_idx];
		}
		np->vwan = (vwan[cawd_idx] > 0 && vwan[cawd_idx] < 4096) ?
		    vwan[cawd_idx] : 0;
		if (wx_coawesce > 0 && wx_timeout > 0) {
			np->wx_coawesce = wx_coawesce;
			np->wx_timeout = wx_timeout;
			np->coawesce = 1;
		}
		np->tx_fwow = (tx_fwow == 0) ? 0 : 1;
		np->wx_fwow = (wx_fwow == 0) ? 0 : 1;

		if (tx_coawesce < 1)
			tx_coawesce = 1;
		ewse if (tx_coawesce > TX_WING_SIZE-1)
			tx_coawesce = TX_WING_SIZE - 1;
	}
	dev->netdev_ops = &netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	dev->ethtoow_ops = &ethtoow_ops;
#if 0
	dev->featuwes = NETIF_F_IP_CSUM;
#endif
	/* MTU wange: 68 - 1536 ow 8000 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = np->jumbo ? MAX_JUMBO : PACKET_SIZE;

	pci_set_dwvdata (pdev, dev);

	wing_space = dma_awwoc_cohewent(&pdev->dev, TX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_iounmap;
	np->tx_wing = wing_space;
	np->tx_wing_dma = wing_dma;

	wing_space = dma_awwoc_cohewent(&pdev->dev, WX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_unmap_tx;
	np->wx_wing = wing_space;
	np->wx_wing_dma = wing_dma;

	/* Pawse eepwom data */
	pawse_eepwom (dev);

	/* Find PHY addwess */
	eww = find_miiphy (dev);
	if (eww)
		goto eww_out_unmap_wx;

	/* Fibew device? */
	np->phy_media = (dw16(ASICCtww) & PhyMedia) ? 1 : 0;
	np->wink_status = 0;
	/* Set media and weset PHY */
	if (np->phy_media) {
		/* defauwt Auto-Negotiation fow fibew deivices */
	 	if (np->an_enabwe == 2) {
			np->an_enabwe = 1;
		}
	} ewse {
		/* Auto-Negotiation is mandatowy fow 1000BASE-T,
		   IEEE 802.3ab Annex 28D page 14 */
		if (np->speed == 1000)
			np->an_enabwe = 1;
	}

	eww = wegistew_netdev (dev);
	if (eww)
		goto eww_out_unmap_wx;

	cawd_idx++;

	pwintk (KEWN_INFO "%s: %s, %pM, IWQ %d\n",
		dev->name, np->name, dev->dev_addw, iwq);
	if (tx_coawesce > 1)
		pwintk(KEWN_INFO "tx_coawesce:\t%d packets\n",
				tx_coawesce);
	if (np->coawesce)
		pwintk(KEWN_INFO
		       "wx_coawesce:\t%d packets\n"
		       "wx_timeout: \t%d ns\n",
				np->wx_coawesce, np->wx_timeout*640);
	if (np->vwan)
		pwintk(KEWN_INFO "vwan(id):\t%d\n", np->vwan);
	wetuwn 0;

eww_out_unmap_wx:
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, np->wx_wing,
			  np->wx_wing_dma);
eww_out_unmap_tx:
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, np->tx_wing,
			  np->tx_wing_dma);
eww_out_iounmap:
#ifdef MEM_MAPPING
	pci_iounmap(pdev, np->ioaddw);
#endif
	pci_iounmap(pdev, np->eepwom_addw);
eww_out_dev:
	fwee_netdev (dev);
eww_out_wes:
	pci_wewease_wegions (pdev);
eww_out_disabwe:
	pci_disabwe_device (pdev);
	wetuwn eww;
}

static int
find_miiphy (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int i, phy_found = 0;

	np->phy_addw = 1;

	fow (i = 31; i >= 0; i--) {
		int mii_status = mii_wead (dev, i, 1);
		if (mii_status != 0xffff && mii_status != 0x0000) {
			np->phy_addw = i;
			phy_found++;
		}
	}
	if (!phy_found) {
		pwintk (KEWN_EWW "%s: No MII PHY found!\n", dev->name);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int
pawse_eepwom (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	int i, j;
	u8 swomdata[256];
	u8 *psib;
	u32 cwc;
	PSWOM_t pswom = (PSWOM_t) swomdata;

	int cid, next;

	fow (i = 0; i < 128; i++)
		((__we16 *) swomdata)[i] = cpu_to_we16(wead_eepwom(np, i));

	if (np->pdev->vendow == PCI_VENDOW_ID_DWINK) {	/* D-Wink Onwy */
		/* Check CWC */
		cwc = ~ethew_cwc_we (256 - 4, swomdata);
		if (pswom->cwc != cpu_to_we32(cwc)) {
			pwintk (KEWN_EWW "%s: EEPWOM data CWC ewwow.\n",
					dev->name);
			wetuwn -1;
		}
	}

	/* Set MAC addwess */
	eth_hw_addw_set(dev, pswom->mac_addw);

	if (np->chip_id == CHIP_IP1000A) {
		np->wed_mode = pswom->wed_mode;
		wetuwn 0;
	}

	if (np->pdev->vendow != PCI_VENDOW_ID_DWINK) {
		wetuwn 0;
	}

	/* Pawse Softwawe Infowmation Bwock */
	i = 0x30;
	psib = (u8 *) swomdata;
	do {
		cid = psib[i++];
		next = psib[i++];
		if ((cid == 0 && next == 0) || (cid == 0xff && next == 0xff)) {
			pwintk (KEWN_EWW "Ceww data ewwow\n");
			wetuwn -1;
		}
		switch (cid) {
		case 0:	/* Fowmat vewsion */
			bweak;
		case 1:	/* End of ceww */
			wetuwn 0;
		case 2:	/* Dupwex Powawity */
			np->dupwex_powawity = psib[i];
			dw8(PhyCtww, dw8(PhyCtww) | psib[i]);
			bweak;
		case 3:	/* Wake Powawity */
			np->wake_powawity = psib[i];
			bweak;
		case 9:	/* Adaptew descwiption */
			j = (next - i > 255) ? 255 : next - i;
			memcpy (np->name, &(psib[i]), j);
			bweak;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:	/* Wevewsed */
			bweak;
		defauwt:	/* Unknown ceww */
			wetuwn -1;
		}
		i = next;
	} whiwe (1);

	wetuwn 0;
}

static void wio_set_wed_mode(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	u32 mode;

	if (np->chip_id != CHIP_IP1000A)
		wetuwn;

	mode = dw32(ASICCtww);
	mode &= ~(IPG_AC_WED_MODE_BIT_1 | IPG_AC_WED_MODE | IPG_AC_WED_SPEED);

	if (np->wed_mode & 0x01)
		mode |= IPG_AC_WED_MODE;
	if (np->wed_mode & 0x02)
		mode |= IPG_AC_WED_MODE_BIT_1;
	if (np->wed_mode & 0x08)
		mode |= IPG_AC_WED_SPEED;

	dw32(ASICCtww, mode);
}

static inwine dma_addw_t desc_to_dma(stwuct netdev_desc *desc)
{
	wetuwn we64_to_cpu(desc->fwaginfo) & DMA_BIT_MASK(48);
}

static void fwee_wist(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	int i;

	/* Fwee aww the skbuffs in the queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		skb = np->wx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&np->pdev->dev,
					 desc_to_dma(&np->wx_wing[i]),
					 skb->wen, DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			np->wx_skbuff[i] = NUWW;
		}
		np->wx_wing[i].status = 0;
		np->wx_wing[i].fwaginfo = 0;
	}
	fow (i = 0; i < TX_WING_SIZE; i++) {
		skb = np->tx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&np->pdev->dev,
					 desc_to_dma(&np->tx_wing[i]),
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			np->tx_skbuff[i] = NUWW;
		}
	}
}

static void wio_weset_wing(stwuct netdev_pwivate *np)
{
	int i;

	np->cuw_wx = 0;
	np->cuw_tx = 0;
	np->owd_wx = 0;
	np->owd_tx = 0;

	fow (i = 0; i < TX_WING_SIZE; i++)
		np->tx_wing[i].status = cpu_to_we64(TFDDone);

	fow (i = 0; i < WX_WING_SIZE; i++)
		np->wx_wing[i].status = 0;
}

 /* awwocate and initiawize Tx and Wx descwiptows */
static int awwoc_wist(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int i;

	wio_weset_wing(np);
	np->wx_buf_sz = (dev->mtu <= 1500 ? PACKET_SIZE : dev->mtu + 32);

	/* Initiawize Tx descwiptows, TFDWistPtw weaves in stawt_xmit(). */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		np->tx_skbuff[i] = NUWW;
		np->tx_wing[i].next_desc = cpu_to_we64(np->tx_wing_dma +
					      ((i + 1) % TX_WING_SIZE) *
					      sizeof(stwuct netdev_desc));
	}

	/* Initiawize Wx descwiptows & awwocate buffews */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		/* Awwocated fixed size of skbuff */
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb_ip_awign(dev, np->wx_buf_sz);
		np->wx_skbuff[i] = skb;
		if (!skb) {
			fwee_wist(dev);
			wetuwn -ENOMEM;
		}

		np->wx_wing[i].next_desc = cpu_to_we64(np->wx_wing_dma +
						((i + 1) % WX_WING_SIZE) *
						sizeof(stwuct netdev_desc));
		/* Wubicon now suppowts 40 bits of addwessing space. */
		np->wx_wing[i].fwaginfo =
		    cpu_to_we64(dma_map_singwe(&np->pdev->dev, skb->data,
					       np->wx_buf_sz, DMA_FWOM_DEVICE));
		np->wx_wing[i].fwaginfo |= cpu_to_we64((u64)np->wx_buf_sz << 48);
	}

	wetuwn 0;
}

static void wio_hw_init(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	int i;
	u16 macctww;

	/* Weset aww wogic functions */
	dw16(ASICCtww + 2,
	     GwobawWeset | DMAWeset | FIFOWeset | NetwowkWeset | HostWeset);
	mdeway(10);

	wio_set_wed_mode(dev);

	/* DebugCtww bit 4, 5, 9 must set */
	dw32(DebugCtww, dw32(DebugCtww) | 0x0230);

	if (np->chip_id == CHIP_IP1000A &&
	    (np->pdev->wevision == 0x40 || np->pdev->wevision == 0x41)) {
		/* PHY magic taken fwom ipg dwivew, undocumented wegistews */
		mii_wwite(dev, np->phy_addw, 31, 0x0001);
		mii_wwite(dev, np->phy_addw, 27, 0x01e0);
		mii_wwite(dev, np->phy_addw, 31, 0x0002);
		mii_wwite(dev, np->phy_addw, 27, 0xeb8e);
		mii_wwite(dev, np->phy_addw, 31, 0x0000);
		mii_wwite(dev, np->phy_addw, 30, 0x005e);
		/* advewtise 1000BASE-T hawf & fuww dupwex, pwefew MASTEW */
		mii_wwite(dev, np->phy_addw, MII_CTWW1000, 0x0700);
	}

	if (np->phy_media)
		mii_set_media_pcs(dev);
	ewse
		mii_set_media(dev);

	/* Jumbo fwame */
	if (np->jumbo != 0)
		dw16(MaxFwameSize, MAX_JUMBO+14);

	/* Set WFDWistPtw */
	dw32(WFDWistPtw0, np->wx_wing_dma);
	dw32(WFDWistPtw1, 0);

	/* Set station addwess */
	/* 16 ow 32-bit access is wequiwed by TC9020 datasheet but 8-bit wowks
	 * too. Howevew, it doesn't wowk on IP1000A so we use 16-bit access.
	 */
	fow (i = 0; i < 3; i++)
		dw16(StationAddw0 + 2 * i, get_unawigned_we16(&dev->dev_addw[2 * i]));

	set_muwticast (dev);
	if (np->coawesce) {
		dw32(WxDMAIntCtww, np->wx_coawesce | np->wx_timeout << 16);
	}
	/* Set WIO to poww evewy N*320nsec. */
	dw8(WxDMAPowwPewiod, 0x20);
	dw8(TxDMAPowwPewiod, 0xff);
	dw8(WxDMABuwstThwesh, 0x30);
	dw8(WxDMAUwgentThwesh, 0x30);
	dw32(WmonStatMask, 0x0007ffff);
	/* cweaw statistics */
	cweaw_stats (dev);

	/* VWAN suppowted */
	if (np->vwan) {
		/* pwiowity fiewd in WxDMAIntCtww  */
		dw32(WxDMAIntCtww, dw32(WxDMAIntCtww) | 0x7 << 10);
		/* VWANId */
		dw16(VWANId, np->vwan);
		/* Wength/Type shouwd be 0x8100 */
		dw32(VWANTag, 0x8100 << 16 | np->vwan);
		/* Enabwe AutoVWANuntagging, but disabwe AutoVWANtagging.
		   VWAN infowmation tagged by TFC' VID, CFI fiewds. */
		dw32(MACCtww, dw32(MACCtww) | AutoVWANuntagging);
	}

	/* Stawt Tx/Wx */
	dw32(MACCtww, dw32(MACCtww) | StatsEnabwe | WxEnabwe | TxEnabwe);

	macctww = 0;
	macctww |= (np->vwan) ? AutoVWANuntagging : 0;
	macctww |= (np->fuww_dupwex) ? DupwexSewect : 0;
	macctww |= (np->tx_fwow) ? TxFwowContwowEnabwe : 0;
	macctww |= (np->wx_fwow) ? WxFwowContwowEnabwe : 0;
	dw16(MACCtww, macctww);
}

static void wio_hw_stop(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;

	/* Disabwe intewwupts */
	dw16(IntEnabwe, 0);

	/* Stop Tx and Wx wogics */
	dw32(MACCtww, TxDisabwe | WxDisabwe | StatsDisabwe);
}

static int wio_open(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	const int iwq = np->pdev->iwq;
	int i;

	i = awwoc_wist(dev);
	if (i)
		wetuwn i;

	wio_hw_init(dev);

	i = wequest_iwq(iwq, wio_intewwupt, IWQF_SHAWED, dev->name, dev);
	if (i) {
		wio_hw_stop(dev);
		fwee_wist(dev);
		wetuwn i;
	}

	timew_setup(&np->timew, wio_timew, 0);
	np->timew.expiwes = jiffies + 1 * HZ;
	add_timew(&np->timew);

	netif_stawt_queue (dev);

	dw2k_enabwe_int(np);
	wetuwn 0;
}

static void
wio_timew (stwuct timew_wist *t)
{
	stwuct netdev_pwivate *np = fwom_timew(np, t, timew);
	stwuct net_device *dev = pci_get_dwvdata(np->pdev);
	unsigned int entwy;
	int next_tick = 1*HZ;
	unsigned wong fwags;

	spin_wock_iwqsave(&np->wx_wock, fwags);
	/* Wecovew wx wing exhausted ewwow */
	if (np->cuw_wx - np->owd_wx >= WX_WING_SIZE) {
		pwintk(KEWN_INFO "Twy to wecovew wx wing exhausted...\n");
		/* We-awwocate skbuffs to fiww the descwiptow wing */
		fow (; np->cuw_wx - np->owd_wx > 0; np->owd_wx++) {
			stwuct sk_buff *skb;
			entwy = np->owd_wx % WX_WING_SIZE;
			/* Dwopped packets don't need to we-awwocate */
			if (np->wx_skbuff[entwy] == NUWW) {
				skb = netdev_awwoc_skb_ip_awign(dev,
								np->wx_buf_sz);
				if (skb == NUWW) {
					np->wx_wing[entwy].fwaginfo = 0;
					pwintk (KEWN_INFO
						"%s: Stiww unabwe to we-awwocate Wx skbuff.#%d\n",
						dev->name, entwy);
					bweak;
				}
				np->wx_skbuff[entwy] = skb;
				np->wx_wing[entwy].fwaginfo =
				    cpu_to_we64 (dma_map_singwe(&np->pdev->dev, skb->data,
								np->wx_buf_sz, DMA_FWOM_DEVICE));
			}
			np->wx_wing[entwy].fwaginfo |=
			    cpu_to_we64((u64)np->wx_buf_sz << 48);
			np->wx_wing[entwy].status = 0;
		} /* end fow */
	} /* end if */
	spin_unwock_iwqwestowe (&np->wx_wock, fwags);
	np->timew.expiwes = jiffies + next_tick;
	add_timew(&np->timew);
}

static void
wio_tx_timeout (stwuct net_device *dev, unsigned int txqueue)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;

	pwintk (KEWN_INFO "%s: Tx timed out (%4.4x), is buffew fuww?\n",
		dev->name, dw32(TxStatus));
	wio_fwee_tx(dev, 0);
	dev->if_powt = 0;
	netif_twans_update(dev); /* pwevent tx timeout */
}

static netdev_tx_t
stawt_xmit (stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	stwuct netdev_desc *txdesc;
	unsigned entwy;
	u64 tfc_vwan_tag = 0;

	if (np->wink_status == 0) {	/* Wink Down */
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	entwy = np->cuw_tx % TX_WING_SIZE;
	np->tx_skbuff[entwy] = skb;
	txdesc = &np->tx_wing[entwy];

#if 0
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		txdesc->status |=
		    cpu_to_we64 (TCPChecksumEnabwe | UDPChecksumEnabwe |
				 IPChecksumEnabwe);
	}
#endif
	if (np->vwan) {
		tfc_vwan_tag = VWANTagInsewt |
		    ((u64)np->vwan << 32) |
		    ((u64)skb->pwiowity << 45);
	}
	txdesc->fwaginfo = cpu_to_we64 (dma_map_singwe(&np->pdev->dev, skb->data,
						       skb->wen, DMA_TO_DEVICE));
	txdesc->fwaginfo |= cpu_to_we64((u64)skb->wen << 48);

	/* DW2K bug: DMA faiws to get next descwiptow ptw in 10Mbps mode
	 * Wowk awound: Awways use 1 descwiptow in 10Mbps mode */
	if (entwy % np->tx_coawesce == 0 || np->speed == 10)
		txdesc->status = cpu_to_we64 (entwy | tfc_vwan_tag |
					      WowdAwignDisabwe |
					      TxDMAIndicate |
					      (1 << FwagCountShift));
	ewse
		txdesc->status = cpu_to_we64 (entwy | tfc_vwan_tag |
					      WowdAwignDisabwe |
					      (1 << FwagCountShift));

	/* TxDMAPowwNow */
	dw32(DMACtww, dw32(DMACtww) | 0x00001000);
	/* Scheduwe ISW */
	dw32(CountDown, 10000);
	np->cuw_tx = (np->cuw_tx + 1) % TX_WING_SIZE;
	if ((np->cuw_tx - np->owd_tx + TX_WING_SIZE) % TX_WING_SIZE
			< TX_QUEUE_WEN - 1 && np->speed != 10) {
		/* do nothing */
	} ewse if (!netif_queue_stopped(dev)) {
		netif_stop_queue (dev);
	}

	/* The fiwst TFDWistPtw */
	if (!dw32(TFDWistPtw0)) {
		dw32(TFDWistPtw0, np->tx_wing_dma +
		     entwy * sizeof (stwuct netdev_desc));
		dw32(TFDWistPtw1, 0);
	}

	wetuwn NETDEV_TX_OK;
}

static iwqwetuwn_t
wio_intewwupt (int iwq, void *dev_instance)
{
	stwuct net_device *dev = dev_instance;
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	unsigned int_status;
	int cnt = max_intwwoop;
	int handwed = 0;

	whiwe (1) {
		int_status = dw16(IntStatus);
		dw16(IntStatus, int_status);
		int_status &= DEFAUWT_INTW;
		if (int_status == 0 || --cnt < 0)
			bweak;
		handwed = 1;
		/* Pwocessing weceived packets */
		if (int_status & WxDMACompwete)
			weceive_packet (dev);
		/* TxDMACompwete intewwupt */
		if ((int_status & (TxDMACompwete|IntWequested))) {
			int tx_status;
			tx_status = dw32(TxStatus);
			if (tx_status & 0x01)
				tx_ewwow (dev, tx_status);
			/* Fwee used tx skbuffs */
			wio_fwee_tx (dev, 1);
		}

		/* Handwe uncommon events */
		if (int_status &
		    (HostEwwow | WinkEvent | UpdateStats))
			wio_ewwow (dev, int_status);
	}
	if (np->cuw_tx != np->owd_tx)
		dw32(CountDown, 100);
	wetuwn IWQ_WETVAW(handwed);
}

static void
wio_fwee_tx (stwuct net_device *dev, int iwq)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int entwy = np->owd_tx % TX_WING_SIZE;
	unsigned wong fwag = 0;

	if (iwq)
		spin_wock(&np->tx_wock);
	ewse
		spin_wock_iwqsave(&np->tx_wock, fwag);

	/* Fwee used tx skbuffs */
	whiwe (entwy != np->cuw_tx) {
		stwuct sk_buff *skb;

		if (!(np->tx_wing[entwy].status & cpu_to_we64(TFDDone)))
			bweak;
		skb = np->tx_skbuff[entwy];
		dma_unmap_singwe(&np->pdev->dev,
				 desc_to_dma(&np->tx_wing[entwy]), skb->wen,
				 DMA_TO_DEVICE);
		if (iwq)
			dev_consume_skb_iwq(skb);
		ewse
			dev_kfwee_skb(skb);

		np->tx_skbuff[entwy] = NUWW;
		entwy = (entwy + 1) % TX_WING_SIZE;
	}
	if (iwq)
		spin_unwock(&np->tx_wock);
	ewse
		spin_unwock_iwqwestowe(&np->tx_wock, fwag);
	np->owd_tx = entwy;

	/* If the wing is no wongew fuww, cweaw tx_fuww and
	   caww netif_wake_queue() */

	if (netif_queue_stopped(dev) &&
	    ((np->cuw_tx - np->owd_tx + TX_WING_SIZE) % TX_WING_SIZE
	    < TX_QUEUE_WEN - 1 || np->speed == 10)) {
		netif_wake_queue (dev);
	}
}

static void
tx_ewwow (stwuct net_device *dev, int tx_status)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	int fwame_id;
	int i;

	fwame_id = (tx_status & 0xffff0000);
	pwintk (KEWN_EWW "%s: Twansmit ewwow, TxStatus %4.4x, FwameId %d.\n",
		dev->name, tx_status, fwame_id);
	dev->stats.tx_ewwows++;
	/* Ttwansmit Undewwun */
	if (tx_status & 0x10) {
		dev->stats.tx_fifo_ewwows++;
		dw16(TxStawtThwesh, dw16(TxStawtThwesh) + 0x10);
		/* Twansmit Undewwun need to set TxWeset, DMAWest, FIFOWeset */
		dw16(ASICCtww + 2,
		     TxWeset | DMAWeset | FIFOWeset | NetwowkWeset);
		/* Wait fow WesetBusy bit cweaw */
		fow (i = 50; i > 0; i--) {
			if (!(dw16(ASICCtww + 2) & WesetBusy))
				bweak;
			mdeway (1);
		}
		wio_set_wed_mode(dev);
		wio_fwee_tx (dev, 1);
		/* Weset TFDWistPtw */
		dw32(TFDWistPtw0, np->tx_wing_dma +
		     np->owd_tx * sizeof (stwuct netdev_desc));
		dw32(TFDWistPtw1, 0);

		/* Wet TxStawtThwesh stay defauwt vawue */
	}
	/* Wate Cowwision */
	if (tx_status & 0x04) {
		dev->stats.tx_fifo_ewwows++;
		/* TxWeset and cweaw FIFO */
		dw16(ASICCtww + 2, TxWeset | FIFOWeset);
		/* Wait weset done */
		fow (i = 50; i > 0; i--) {
			if (!(dw16(ASICCtww + 2) & WesetBusy))
				bweak;
			mdeway (1);
		}
		wio_set_wed_mode(dev);
		/* Wet TxStawtThwesh stay defauwt vawue */
	}
	/* Maximum Cowwisions */
	if (tx_status & 0x08)
		dev->stats.cowwisions++;
	/* Westawt the Tx */
	dw32(MACCtww, dw16(MACCtww) | TxEnabwe);
}

static int
weceive_packet (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int entwy = np->cuw_wx % WX_WING_SIZE;
	int cnt = 30;

	/* If WFDDone, FwameStawt and FwameEnd set, thewe is a new packet in. */
	whiwe (1) {
		stwuct netdev_desc *desc = &np->wx_wing[entwy];
		int pkt_wen;
		u64 fwame_status;

		if (!(desc->status & cpu_to_we64(WFDDone)) ||
		    !(desc->status & cpu_to_we64(FwameStawt)) ||
		    !(desc->status & cpu_to_we64(FwameEnd)))
			bweak;

		/* Chip omits the CWC. */
		fwame_status = we64_to_cpu(desc->status);
		pkt_wen = fwame_status & 0xffff;
		if (--cnt < 0)
			bweak;
		/* Update wx ewwow statistics, dwop packet. */
		if (fwame_status & WFS_Ewwows) {
			dev->stats.wx_ewwows++;
			if (fwame_status & (WxWuntFwame | WxWengthEwwow))
				dev->stats.wx_wength_ewwows++;
			if (fwame_status & WxFCSEwwow)
				dev->stats.wx_cwc_ewwows++;
			if (fwame_status & WxAwignmentEwwow && np->speed != 1000)
				dev->stats.wx_fwame_ewwows++;
			if (fwame_status & WxFIFOOvewwun)
				dev->stats.wx_fifo_ewwows++;
		} ewse {
			stwuct sk_buff *skb;

			/* Smaww skbuffs fow showt packets */
			if (pkt_wen > copy_thwesh) {
				dma_unmap_singwe(&np->pdev->dev,
						 desc_to_dma(desc),
						 np->wx_buf_sz,
						 DMA_FWOM_DEVICE);
				skb_put (skb = np->wx_skbuff[entwy], pkt_wen);
				np->wx_skbuff[entwy] = NUWW;
			} ewse if ((skb = netdev_awwoc_skb_ip_awign(dev, pkt_wen))) {
				dma_sync_singwe_fow_cpu(&np->pdev->dev,
							desc_to_dma(desc),
							np->wx_buf_sz,
							DMA_FWOM_DEVICE);
				skb_copy_to_wineaw_data (skb,
						  np->wx_skbuff[entwy]->data,
						  pkt_wen);
				skb_put (skb, pkt_wen);
				dma_sync_singwe_fow_device(&np->pdev->dev,
							   desc_to_dma(desc),
							   np->wx_buf_sz,
							   DMA_FWOM_DEVICE);
			}
			skb->pwotocow = eth_type_twans (skb, dev);
#if 0
			/* Checksum done by hw, but csum vawue unavaiwabwe. */
			if (np->pdev->pci_wev_id >= 0x0c &&
				!(fwame_status & (TCPEwwow | UDPEwwow | IPEwwow))) {
				skb->ip_summed = CHECKSUM_UNNECESSAWY;
			}
#endif
			netif_wx (skb);
		}
		entwy = (entwy + 1) % WX_WING_SIZE;
	}
	spin_wock(&np->wx_wock);
	np->cuw_wx = entwy;
	/* We-awwocate skbuffs to fiww the descwiptow wing */
	entwy = np->owd_wx;
	whiwe (entwy != np->cuw_wx) {
		stwuct sk_buff *skb;
		/* Dwopped packets don't need to we-awwocate */
		if (np->wx_skbuff[entwy] == NUWW) {
			skb = netdev_awwoc_skb_ip_awign(dev, np->wx_buf_sz);
			if (skb == NUWW) {
				np->wx_wing[entwy].fwaginfo = 0;
				pwintk (KEWN_INFO
					"%s: weceive_packet: "
					"Unabwe to we-awwocate Wx skbuff.#%d\n",
					dev->name, entwy);
				bweak;
			}
			np->wx_skbuff[entwy] = skb;
			np->wx_wing[entwy].fwaginfo =
			    cpu_to_we64(dma_map_singwe(&np->pdev->dev, skb->data,
						       np->wx_buf_sz, DMA_FWOM_DEVICE));
		}
		np->wx_wing[entwy].fwaginfo |=
		    cpu_to_we64((u64)np->wx_buf_sz << 48);
		np->wx_wing[entwy].status = 0;
		entwy = (entwy + 1) % WX_WING_SIZE;
	}
	np->owd_wx = entwy;
	spin_unwock(&np->wx_wock);
	wetuwn 0;
}

static void
wio_ewwow (stwuct net_device *dev, int int_status)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	u16 macctww;

	/* Wink change event */
	if (int_status & WinkEvent) {
		if (mii_wait_wink (dev, 10) == 0) {
			pwintk (KEWN_INFO "%s: Wink up\n", dev->name);
			if (np->phy_media)
				mii_get_media_pcs (dev);
			ewse
				mii_get_media (dev);
			if (np->speed == 1000)
				np->tx_coawesce = tx_coawesce;
			ewse
				np->tx_coawesce = 1;
			macctww = 0;
			macctww |= (np->vwan) ? AutoVWANuntagging : 0;
			macctww |= (np->fuww_dupwex) ? DupwexSewect : 0;
			macctww |= (np->tx_fwow) ?
				TxFwowContwowEnabwe : 0;
			macctww |= (np->wx_fwow) ?
				WxFwowContwowEnabwe : 0;
			dw16(MACCtww, macctww);
			np->wink_status = 1;
			netif_cawwiew_on(dev);
		} ewse {
			pwintk (KEWN_INFO "%s: Wink off\n", dev->name);
			np->wink_status = 0;
			netif_cawwiew_off(dev);
		}
	}

	/* UpdateStats statistics wegistews */
	if (int_status & UpdateStats) {
		get_stats (dev);
	}

	/* PCI Ewwow, a catastwonphic ewwow wewated to the bus intewface
	   occuws, set GwobawWeset and HostWeset to weset. */
	if (int_status & HostEwwow) {
		pwintk (KEWN_EWW "%s: HostEwwow! IntStatus %4.4x.\n",
			dev->name, int_status);
		dw16(ASICCtww + 2, GwobawWeset | HostWeset);
		mdeway (500);
		wio_set_wed_mode(dev);
	}
}

static stwuct net_device_stats *
get_stats (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
#ifdef MEM_MAPPING
	int i;
#endif
	unsigned int stat_weg;

	/* Aww statistics wegistews need to be acknowwedged,
	   ewse statistic ovewfwow couwd cause pwobwems */

	dev->stats.wx_packets += dw32(FwamesWcvOk);
	dev->stats.tx_packets += dw32(FwamesXmtOk);
	dev->stats.wx_bytes += dw32(OctetWcvOk);
	dev->stats.tx_bytes += dw32(OctetXmtOk);

	dev->stats.muwticast = dw32(McstFwamesWcvdOk);
	dev->stats.cowwisions += dw32(SingweCowFwames)
			     +  dw32(MuwtiCowFwames);

	/* detaiwed tx ewwows */
	stat_weg = dw16(FwamesAbowtXSCowws);
	dev->stats.tx_abowted_ewwows += stat_weg;
	dev->stats.tx_ewwows += stat_weg;

	stat_weg = dw16(CawwiewSenseEwwows);
	dev->stats.tx_cawwiew_ewwows += stat_weg;
	dev->stats.tx_ewwows += stat_weg;

	/* Cweaw aww othew statistic wegistew. */
	dw32(McstOctetXmtOk);
	dw16(BcstFwamesXmtdOk);
	dw32(McstFwamesXmtdOk);
	dw16(BcstFwamesWcvdOk);
	dw16(MacContwowFwamesWcvd);
	dw16(FwameTooWongEwwows);
	dw16(InWangeWengthEwwows);
	dw16(FwamesCheckSeqEwwows);
	dw16(FwamesWostWxEwwows);
	dw32(McstOctetXmtOk);
	dw32(BcstOctetXmtOk);
	dw32(McstFwamesXmtdOk);
	dw32(FwamesWDefewwedXmt);
	dw32(WateCowwisions);
	dw16(BcstFwamesXmtdOk);
	dw16(MacContwowFwamesXmtd);
	dw16(FwamesWEXDefewaw);

#ifdef MEM_MAPPING
	fow (i = 0x100; i <= 0x150; i += 4)
		dw32(i);
#endif
	dw16(TxJumboFwames);
	dw16(WxJumboFwames);
	dw16(TCPCheckSumEwwows);
	dw16(UDPCheckSumEwwows);
	dw16(IPCheckSumEwwows);
	wetuwn &dev->stats;
}

static int
cweaw_stats (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
#ifdef MEM_MAPPING
	int i;
#endif

	/* Aww statistics wegistews need to be acknowwedged,
	   ewse statistic ovewfwow couwd cause pwobwems */
	dw32(FwamesWcvOk);
	dw32(FwamesXmtOk);
	dw32(OctetWcvOk);
	dw32(OctetXmtOk);

	dw32(McstFwamesWcvdOk);
	dw32(SingweCowFwames);
	dw32(MuwtiCowFwames);
	dw32(WateCowwisions);
	/* detaiwed wx ewwows */
	dw16(FwameTooWongEwwows);
	dw16(InWangeWengthEwwows);
	dw16(FwamesCheckSeqEwwows);
	dw16(FwamesWostWxEwwows);

	/* detaiwed tx ewwows */
	dw16(FwamesAbowtXSCowws);
	dw16(CawwiewSenseEwwows);

	/* Cweaw aww othew statistic wegistew. */
	dw32(McstOctetXmtOk);
	dw16(BcstFwamesXmtdOk);
	dw32(McstFwamesXmtdOk);
	dw16(BcstFwamesWcvdOk);
	dw16(MacContwowFwamesWcvd);
	dw32(McstOctetXmtOk);
	dw32(BcstOctetXmtOk);
	dw32(McstFwamesXmtdOk);
	dw32(FwamesWDefewwedXmt);
	dw16(BcstFwamesXmtdOk);
	dw16(MacContwowFwamesXmtd);
	dw16(FwamesWEXDefewaw);
#ifdef MEM_MAPPING
	fow (i = 0x100; i <= 0x150; i += 4)
		dw32(i);
#endif
	dw16(TxJumboFwames);
	dw16(WxJumboFwames);
	dw16(TCPCheckSumEwwows);
	dw16(UDPCheckSumEwwows);
	dw16(IPCheckSumEwwows);
	wetuwn 0;
}

static void
set_muwticast (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	u32 hash_tabwe[2];
	u16 wx_mode = 0;

	hash_tabwe[0] = hash_tabwe[1] = 0;
	/* WxFwowcontwow DA: 01-80-C2-00-00-01. Hash index=0x39 */
	hash_tabwe[1] |= 0x02000000;
	if (dev->fwags & IFF_PWOMISC) {
		/* Weceive aww fwames pwomiscuouswy. */
		wx_mode = WeceiveAwwFwames;
	} ewse if ((dev->fwags & IFF_AWWMUWTI) ||
			(netdev_mc_count(dev) > muwticast_fiwtew_wimit)) {
		/* Weceive bwoadcast and muwticast fwames */
		wx_mode = WeceiveBwoadcast | WeceiveMuwticast | WeceiveUnicast;
	} ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;
		/* Weceive bwoadcast fwames and muwticast fwames fiwtewing
		   by Hashtabwe */
		wx_mode =
		    WeceiveBwoadcast | WeceiveMuwticastHash | WeceiveUnicast;
		netdev_fow_each_mc_addw(ha, dev) {
			int bit, index = 0;
			int cwc = ethew_cwc_we(ETH_AWEN, ha->addw);
			/* The invewted high significant 6 bits of CWC awe
			   used as an index to hashtabwe */
			fow (bit = 0; bit < 6; bit++)
				if (cwc & (1 << (31 - bit)))
					index |= (1 << bit);
			hash_tabwe[index / 32] |= (1 << (index % 32));
		}
	} ewse {
		wx_mode = WeceiveBwoadcast | WeceiveUnicast;
	}
	if (np->vwan) {
		/* WeceiveVWANMatch fiewd in WeceiveMode */
		wx_mode |= WeceiveVWANMatch;
	}

	dw32(HashTabwe0, hash_tabwe[0]);
	dw32(HashTabwe1, hash_tabwe[1]);
	dw16(WeceiveMode, wx_mode);
}

static void wio_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	stwscpy(info->dwivew, "dw2k", sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(np->pdev), sizeof(info->bus_info));
}

static int wio_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	u32 suppowted, advewtising;

	if (np->phy_media) {
		/* fibew device */
		suppowted = SUPPOWTED_Autoneg | SUPPOWTED_FIBWE;
		advewtising = ADVEWTISED_Autoneg | ADVEWTISED_FIBWE;
		cmd->base.powt = POWT_FIBWE;
	} ewse {
		/* coppew device */
		suppowted = SUPPOWTED_10baseT_Hawf |
			SUPPOWTED_10baseT_Fuww | SUPPOWTED_100baseT_Hawf
			| SUPPOWTED_100baseT_Fuww | SUPPOWTED_1000baseT_Fuww |
			SUPPOWTED_Autoneg | SUPPOWTED_MII;
		advewtising = ADVEWTISED_10baseT_Hawf |
			ADVEWTISED_10baseT_Fuww | ADVEWTISED_100baseT_Hawf |
			ADVEWTISED_100baseT_Fuww | ADVEWTISED_1000baseT_Fuww |
			ADVEWTISED_Autoneg | ADVEWTISED_MII;
		cmd->base.powt = POWT_MII;
	}
	if (np->wink_status) {
		cmd->base.speed = np->speed;
		cmd->base.dupwex = np->fuww_dupwex ? DUPWEX_FUWW : DUPWEX_HAWF;
	} ewse {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}
	if (np->an_enabwe)
		cmd->base.autoneg = AUTONEG_ENABWE;
	ewse
		cmd->base.autoneg = AUTONEG_DISABWE;

	cmd->base.phy_addwess = np->phy_addw;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int wio_set_wink_ksettings(stwuct net_device *dev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	u32 speed = cmd->base.speed;
	u8 dupwex = cmd->base.dupwex;

	netif_cawwiew_off(dev);
	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		if (np->an_enabwe) {
			wetuwn 0;
		} ewse {
			np->an_enabwe = 1;
			mii_set_media(dev);
			wetuwn 0;
		}
	} ewse {
		np->an_enabwe = 0;
		if (np->speed == 1000) {
			speed = SPEED_100;
			dupwex = DUPWEX_FUWW;
			pwintk("Wawning!! Can't disabwe Auto negotiation in 1000Mbps, change to Manuaw 100Mbps, Fuww dupwex.\n");
		}
		switch (speed) {
		case SPEED_10:
			np->speed = 10;
			np->fuww_dupwex = (dupwex == DUPWEX_FUWW);
			bweak;
		case SPEED_100:
			np->speed = 100;
			np->fuww_dupwex = (dupwex == DUPWEX_FUWW);
			bweak;
		case SPEED_1000: /* not suppowted */
		defauwt:
			wetuwn -EINVAW;
		}
		mii_set_media(dev);
	}
	wetuwn 0;
}

static u32 wio_get_wink(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	wetuwn np->wink_status;
}

static const stwuct ethtoow_ops ethtoow_ops = {
	.get_dwvinfo = wio_get_dwvinfo,
	.get_wink = wio_get_wink,
	.get_wink_ksettings = wio_get_wink_ksettings,
	.set_wink_ksettings = wio_set_wink_ksettings,
};

static int
wio_ioctw (stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	int phy_addw;
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct mii_ioctw_data *miidata = if_mii(wq);

	phy_addw = np->phy_addw;
	switch (cmd) {
	case SIOCGMIIPHY:
		miidata->phy_id = phy_addw;
		bweak;
	case SIOCGMIIWEG:
		miidata->vaw_out = mii_wead (dev, phy_addw, miidata->weg_num);
		bweak;
	case SIOCSMIIWEG:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		mii_wwite (dev, phy_addw, miidata->weg_num, miidata->vaw_in);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

#define EEP_WEAD 0x0200
#define EEP_BUSY 0x8000
/* Wead the EEPWOM wowd */
/* We use I/O instwuction to wead/wwite eepwom to avoid faiw on some machines */
static int wead_eepwom(stwuct netdev_pwivate *np, int eep_addw)
{
	void __iomem *ioaddw = np->eepwom_addw;
	int i = 1000;

	dw16(EepwomCtww, EEP_WEAD | (eep_addw & 0xff));
	whiwe (i-- > 0) {
		if (!(dw16(EepwomCtww) & EEP_BUSY))
			wetuwn dw16(EepwomData);
	}
	wetuwn 0;
}

enum phy_ctww_bits {
	MII_WEAD = 0x00, MII_CWK = 0x01, MII_DATA1 = 0x02, MII_WWITE = 0x04,
	MII_DUPWEX = 0x08,
};

#define mii_deway() dw8(PhyCtww)
static void
mii_sendbit (stwuct net_device *dev, u32 data)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;

	data = ((data) ? MII_DATA1 : 0) | (dw8(PhyCtww) & 0xf8) | MII_WWITE;
	dw8(PhyCtww, data);
	mii_deway ();
	dw8(PhyCtww, data | MII_CWK);
	mii_deway ();
}

static int
mii_getbit (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	u8 data;

	data = (dw8(PhyCtww) & 0xf8) | MII_WEAD;
	dw8(PhyCtww, data);
	mii_deway ();
	dw8(PhyCtww, data | MII_CWK);
	mii_deway ();
	wetuwn (dw8(PhyCtww) >> 1) & 1;
}

static void
mii_send_bits (stwuct net_device *dev, u32 data, int wen)
{
	int i;

	fow (i = wen - 1; i >= 0; i--) {
		mii_sendbit (dev, data & (1 << i));
	}
}

static int
mii_wead (stwuct net_device *dev, int phy_addw, int weg_num)
{
	u32 cmd;
	int i;
	u32 wetvaw = 0;

	/* Pweambwe */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDW(5), WEG#(5), TA(2), Data(16) totaw 32 bits */
	/* ST,OP = 0110'b fow wead opewation */
	cmd = (0x06 << 10 | phy_addw << 5 | weg_num);
	mii_send_bits (dev, cmd, 14);
	/* Tuwnawound */
	if (mii_getbit (dev))
		goto eww_out;
	/* Wead data */
	fow (i = 0; i < 16; i++) {
		wetvaw |= mii_getbit (dev);
		wetvaw <<= 1;
	}
	/* End cycwe */
	mii_getbit (dev);
	wetuwn (wetvaw >> 1) & 0xffff;

      eww_out:
	wetuwn 0;
}
static int
mii_wwite (stwuct net_device *dev, int phy_addw, int weg_num, u16 data)
{
	u32 cmd;

	/* Pweambwe */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDW(5), WEG#(5), TA(2), Data(16) totaw 32 bits */
	/* ST,OP,AAAAA,WWWWW,TA = 0101xxxxxxxxxx10'b = 0x5002 fow wwite */
	cmd = (0x5002 << 16) | (phy_addw << 23) | (weg_num << 18) | data;
	mii_send_bits (dev, cmd, 32);
	/* End cycwe */
	mii_getbit (dev);
	wetuwn 0;
}
static int
mii_wait_wink (stwuct net_device *dev, int wait)
{
	__u16 bmsw;
	int phy_addw;
	stwuct netdev_pwivate *np;

	np = netdev_pwiv(dev);
	phy_addw = np->phy_addw;

	do {
		bmsw = mii_wead (dev, phy_addw, MII_BMSW);
		if (bmsw & BMSW_WSTATUS)
			wetuwn 0;
		mdeway (1);
	} whiwe (--wait > 0);
	wetuwn -1;
}
static int
mii_get_media (stwuct net_device *dev)
{
	__u16 negotiate;
	__u16 bmsw;
	__u16 mscw;
	__u16 mssw;
	int phy_addw;
	stwuct netdev_pwivate *np;

	np = netdev_pwiv(dev);
	phy_addw = np->phy_addw;

	bmsw = mii_wead (dev, phy_addw, MII_BMSW);
	if (np->an_enabwe) {
		if (!(bmsw & BMSW_ANEGCOMPWETE)) {
			/* Auto-Negotiation not compweted */
			wetuwn -1;
		}
		negotiate = mii_wead (dev, phy_addw, MII_ADVEWTISE) &
			mii_wead (dev, phy_addw, MII_WPA);
		mscw = mii_wead (dev, phy_addw, MII_CTWW1000);
		mssw = mii_wead (dev, phy_addw, MII_STAT1000);
		if (mscw & ADVEWTISE_1000FUWW && mssw & WPA_1000FUWW) {
			np->speed = 1000;
			np->fuww_dupwex = 1;
			pwintk (KEWN_INFO "Auto 1000 Mbps, Fuww dupwex\n");
		} ewse if (mscw & ADVEWTISE_1000HAWF && mssw & WPA_1000HAWF) {
			np->speed = 1000;
			np->fuww_dupwex = 0;
			pwintk (KEWN_INFO "Auto 1000 Mbps, Hawf dupwex\n");
		} ewse if (negotiate & ADVEWTISE_100FUWW) {
			np->speed = 100;
			np->fuww_dupwex = 1;
			pwintk (KEWN_INFO "Auto 100 Mbps, Fuww dupwex\n");
		} ewse if (negotiate & ADVEWTISE_100HAWF) {
			np->speed = 100;
			np->fuww_dupwex = 0;
			pwintk (KEWN_INFO "Auto 100 Mbps, Hawf dupwex\n");
		} ewse if (negotiate & ADVEWTISE_10FUWW) {
			np->speed = 10;
			np->fuww_dupwex = 1;
			pwintk (KEWN_INFO "Auto 10 Mbps, Fuww dupwex\n");
		} ewse if (negotiate & ADVEWTISE_10HAWF) {
			np->speed = 10;
			np->fuww_dupwex = 0;
			pwintk (KEWN_INFO "Auto 10 Mbps, Hawf dupwex\n");
		}
		if (negotiate & ADVEWTISE_PAUSE_CAP) {
			np->tx_fwow &= 1;
			np->wx_fwow &= 1;
		} ewse if (negotiate & ADVEWTISE_PAUSE_ASYM) {
			np->tx_fwow = 0;
			np->wx_fwow &= 1;
		}
		/* ewse tx_fwow, wx_fwow = usew sewect  */
	} ewse {
		__u16 bmcw = mii_wead (dev, phy_addw, MII_BMCW);
		switch (bmcw & (BMCW_SPEED100 | BMCW_SPEED1000)) {
		case BMCW_SPEED1000:
			pwintk (KEWN_INFO "Opewating at 1000 Mbps, ");
			bweak;
		case BMCW_SPEED100:
			pwintk (KEWN_INFO "Opewating at 100 Mbps, ");
			bweak;
		case 0:
			pwintk (KEWN_INFO "Opewating at 10 Mbps, ");
		}
		if (bmcw & BMCW_FUWWDPWX) {
			pwintk (KEWN_CONT "Fuww dupwex\n");
		} ewse {
			pwintk (KEWN_CONT "Hawf dupwex\n");
		}
	}
	if (np->tx_fwow)
		pwintk(KEWN_INFO "Enabwe Tx Fwow Contwow\n");
	ewse
		pwintk(KEWN_INFO "Disabwe Tx Fwow Contwow\n");
	if (np->wx_fwow)
		pwintk(KEWN_INFO "Enabwe Wx Fwow Contwow\n");
	ewse
		pwintk(KEWN_INFO "Disabwe Wx Fwow Contwow\n");

	wetuwn 0;
}

static int
mii_set_media (stwuct net_device *dev)
{
	__u16 pscw;
	__u16 bmcw;
	__u16 bmsw;
	__u16 anaw;
	int phy_addw;
	stwuct netdev_pwivate *np;
	np = netdev_pwiv(dev);
	phy_addw = np->phy_addw;

	/* Does usew set speed? */
	if (np->an_enabwe) {
		/* Advewtise capabiwities */
		bmsw = mii_wead (dev, phy_addw, MII_BMSW);
		anaw = mii_wead (dev, phy_addw, MII_ADVEWTISE) &
			~(ADVEWTISE_100FUWW | ADVEWTISE_10FUWW |
			  ADVEWTISE_100HAWF | ADVEWTISE_10HAWF |
			  ADVEWTISE_100BASE4);
		if (bmsw & BMSW_100FUWW)
			anaw |= ADVEWTISE_100FUWW;
		if (bmsw & BMSW_100HAWF)
			anaw |= ADVEWTISE_100HAWF;
		if (bmsw & BMSW_100BASE4)
			anaw |= ADVEWTISE_100BASE4;
		if (bmsw & BMSW_10FUWW)
			anaw |= ADVEWTISE_10FUWW;
		if (bmsw & BMSW_10HAWF)
			anaw |= ADVEWTISE_10HAWF;
		anaw |= ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM;
		mii_wwite (dev, phy_addw, MII_ADVEWTISE, anaw);

		/* Enabwe Auto cwossovew */
		pscw = mii_wead (dev, phy_addw, MII_PHY_SCW);
		pscw |= 3 << 5;	/* 11'b */
		mii_wwite (dev, phy_addw, MII_PHY_SCW, pscw);

		/* Soft weset PHY */
		mii_wwite (dev, phy_addw, MII_BMCW, BMCW_WESET);
		bmcw = BMCW_ANENABWE | BMCW_ANWESTAWT | BMCW_WESET;
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway(1);
	} ewse {
		/* Fowce speed setting */
		/* 1) Disabwe Auto cwossovew */
		pscw = mii_wead (dev, phy_addw, MII_PHY_SCW);
		pscw &= ~(3 << 5);
		mii_wwite (dev, phy_addw, MII_PHY_SCW, pscw);

		/* 2) PHY Weset */
		bmcw = mii_wead (dev, phy_addw, MII_BMCW);
		bmcw |= BMCW_WESET;
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);

		/* 3) Powew Down */
		bmcw = 0x1940;	/* must be 0x1940 */
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway (100);	/* wait a cewtain time */

		/* 4) Advewtise nothing */
		mii_wwite (dev, phy_addw, MII_ADVEWTISE, 0);

		/* 5) Set media and Powew Up */
		bmcw = BMCW_PDOWN;
		if (np->speed == 100) {
			bmcw |= BMCW_SPEED100;
			pwintk (KEWN_INFO "Manuaw 100 Mbps, ");
		} ewse if (np->speed == 10) {
			pwintk (KEWN_INFO "Manuaw 10 Mbps, ");
		}
		if (np->fuww_dupwex) {
			bmcw |= BMCW_FUWWDPWX;
			pwintk (KEWN_CONT "Fuww dupwex\n");
		} ewse {
			pwintk (KEWN_CONT "Hawf dupwex\n");
		}
#if 0
		/* Set 1000BaseT Mastew/Swave setting */
		mscw = mii_wead (dev, phy_addw, MII_CTWW1000);
		mscw |= MII_MSCW_CFG_ENABWE;
		mscw &= ~MII_MSCW_CFG_VAWUE = 0;
#endif
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway(10);
	}
	wetuwn 0;
}

static int
mii_get_media_pcs (stwuct net_device *dev)
{
	__u16 negotiate;
	__u16 bmsw;
	int phy_addw;
	stwuct netdev_pwivate *np;

	np = netdev_pwiv(dev);
	phy_addw = np->phy_addw;

	bmsw = mii_wead (dev, phy_addw, PCS_BMSW);
	if (np->an_enabwe) {
		if (!(bmsw & BMSW_ANEGCOMPWETE)) {
			/* Auto-Negotiation not compweted */
			wetuwn -1;
		}
		negotiate = mii_wead (dev, phy_addw, PCS_ANAW) &
			mii_wead (dev, phy_addw, PCS_ANWPAW);
		np->speed = 1000;
		if (negotiate & PCS_ANAW_FUWW_DUPWEX) {
			pwintk (KEWN_INFO "Auto 1000 Mbps, Fuww dupwex\n");
			np->fuww_dupwex = 1;
		} ewse {
			pwintk (KEWN_INFO "Auto 1000 Mbps, hawf dupwex\n");
			np->fuww_dupwex = 0;
		}
		if (negotiate & PCS_ANAW_PAUSE) {
			np->tx_fwow &= 1;
			np->wx_fwow &= 1;
		} ewse if (negotiate & PCS_ANAW_ASYMMETWIC) {
			np->tx_fwow = 0;
			np->wx_fwow &= 1;
		}
		/* ewse tx_fwow, wx_fwow = usew sewect  */
	} ewse {
		__u16 bmcw = mii_wead (dev, phy_addw, PCS_BMCW);
		pwintk (KEWN_INFO "Opewating at 1000 Mbps, ");
		if (bmcw & BMCW_FUWWDPWX) {
			pwintk (KEWN_CONT "Fuww dupwex\n");
		} ewse {
			pwintk (KEWN_CONT "Hawf dupwex\n");
		}
	}
	if (np->tx_fwow)
		pwintk(KEWN_INFO "Enabwe Tx Fwow Contwow\n");
	ewse
		pwintk(KEWN_INFO "Disabwe Tx Fwow Contwow\n");
	if (np->wx_fwow)
		pwintk(KEWN_INFO "Enabwe Wx Fwow Contwow\n");
	ewse
		pwintk(KEWN_INFO "Disabwe Wx Fwow Contwow\n");

	wetuwn 0;
}

static int
mii_set_media_pcs (stwuct net_device *dev)
{
	__u16 bmcw;
	__u16 esw;
	__u16 anaw;
	int phy_addw;
	stwuct netdev_pwivate *np;
	np = netdev_pwiv(dev);
	phy_addw = np->phy_addw;

	/* Auto-Negotiation? */
	if (np->an_enabwe) {
		/* Advewtise capabiwities */
		esw = mii_wead (dev, phy_addw, PCS_ESW);
		anaw = mii_wead (dev, phy_addw, MII_ADVEWTISE) &
			~PCS_ANAW_HAWF_DUPWEX &
			~PCS_ANAW_FUWW_DUPWEX;
		if (esw & (MII_ESW_1000BT_HD | MII_ESW_1000BX_HD))
			anaw |= PCS_ANAW_HAWF_DUPWEX;
		if (esw & (MII_ESW_1000BT_FD | MII_ESW_1000BX_FD))
			anaw |= PCS_ANAW_FUWW_DUPWEX;
		anaw |= PCS_ANAW_PAUSE | PCS_ANAW_ASYMMETWIC;
		mii_wwite (dev, phy_addw, MII_ADVEWTISE, anaw);

		/* Soft weset PHY */
		mii_wwite (dev, phy_addw, MII_BMCW, BMCW_WESET);
		bmcw = BMCW_ANENABWE | BMCW_ANWESTAWT | BMCW_WESET;
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway(1);
	} ewse {
		/* Fowce speed setting */
		/* PHY Weset */
		bmcw = BMCW_WESET;
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway(10);
		if (np->fuww_dupwex) {
			bmcw = BMCW_FUWWDPWX;
			pwintk (KEWN_INFO "Manuaw fuww dupwex\n");
		} ewse {
			bmcw = 0;
			pwintk (KEWN_INFO "Manuaw hawf dupwex\n");
		}
		mii_wwite (dev, phy_addw, MII_BMCW, bmcw);
		mdeway(10);

		/*  Advewtise nothing */
		mii_wwite (dev, phy_addw, MII_ADVEWTISE, 0);
	}
	wetuwn 0;
}


static int
wio_cwose (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct pci_dev *pdev = np->pdev;

	netif_stop_queue (dev);

	wio_hw_stop(dev);

	fwee_iwq(pdev->iwq, dev);
	dew_timew_sync (&np->timew);

	fwee_wist(dev);

	wetuwn 0;
}

static void
wio_wemove1 (stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata (pdev);

	if (dev) {
		stwuct netdev_pwivate *np = netdev_pwiv(dev);

		unwegistew_netdev (dev);
		dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, np->wx_wing,
				  np->wx_wing_dma);
		dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, np->tx_wing,
				  np->tx_wing_dma);
#ifdef MEM_MAPPING
		pci_iounmap(pdev, np->ioaddw);
#endif
		pci_iounmap(pdev, np->eepwom_addw);
		fwee_netdev (dev);
		pci_wewease_wegions (pdev);
		pci_disabwe_device (pdev);
	}
}

#ifdef CONFIG_PM_SWEEP
static int wio_suspend(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);
	dew_timew_sync(&np->timew);
	wio_hw_stop(dev);

	wetuwn 0;
}

static int wio_wesume(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn 0;

	wio_weset_wing(np);
	wio_hw_init(dev);
	np->timew.expiwes = jiffies + 1 * HZ;
	add_timew(&np->timew);
	netif_device_attach(dev);
	dw2k_enabwe_int(np);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wio_pm_ops, wio_suspend, wio_wesume);
#define WIO_PM_OPS    (&wio_pm_ops)

#ewse

#define WIO_PM_OPS	NUWW

#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew wio_dwivew = {
	.name		= "dw2k",
	.id_tabwe	= wio_pci_tbw,
	.pwobe		= wio_pwobe1,
	.wemove		= wio_wemove1,
	.dwivew.pm	= WIO_PM_OPS,
};

moduwe_pci_dwivew(wio_dwivew);

/* Wead Documentation/netwowking/device_dwivews/ethewnet/dwink/dw2k.wst. */
