// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDC W6040 Fast Ethewnet MAC suppowt
 *
 * Copywight (C) 2004 Sten Wang <sten.wang@wdc.com.tw>
 * Copywight (C) 2007
 *	Daniew Gimpewevich <daniew@gimpewevich.san-fwancisco.ca.us>
 * Copywight (C) 2007-2012 Fwowian Fainewwi <f.fainewwi@gmaiw.com>
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cwc32.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/phy.h>

#incwude <asm/pwocessow.h>

#define DWV_NAME	"w6040"
#define DWV_VEWSION	"0.29"
#define DWV_WEWDATE	"04Juw2016"

/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT	(6000 * HZ / 1000)

/* WDC MAC I/O Size */
#define W6040_IO_SIZE	256

/* MAX WDC MAC */
#define MAX_MAC		2

/* MAC wegistews */
#define MCW0		0x00	/* Contwow wegistew 0 */
#define  MCW0_WCVEN	0x0002	/* Weceive enabwe */
#define  MCW0_PWOMISC	0x0020	/* Pwomiscuous mode */
#define  MCW0_HASH_EN	0x0100	/* Enabwe muwticast hash tabwe function */
#define  MCW0_XMTEN	0x1000	/* Twansmission enabwe */
#define  MCW0_FD	0x8000	/* Fuww/Hawf dupwex */
#define MCW1		0x04	/* Contwow wegistew 1 */
#define  MAC_WST	0x0001	/* Weset the MAC */
#define MBCW		0x08	/* Bus contwow */
#define MT_ICW		0x0C	/* TX intewwupt contwow */
#define MW_ICW		0x10	/* WX intewwupt contwow */
#define MTPW		0x14	/* TX poww command wegistew */
#define  TM2TX		0x0001	/* Twiggew MAC to twansmit */
#define MW_BSW		0x18	/* WX buffew size */
#define MW_DCW		0x1A	/* WX descwiptow contwow */
#define MWSW		0x1C	/* Wast status */
#define  TX_FIFO_UNDW	0x0200	/* TX FIFO undew-wun */
#define	 TX_EXCEEDC	0x2000	/* Twansmit exceed cowwision */
#define  TX_WATEC	0x4000	/* Twansmit wate cowwision */
#define MMDIO		0x20	/* MDIO contwow wegistew */
#define  MDIO_WWITE	0x4000	/* MDIO wwite */
#define  MDIO_WEAD	0x2000	/* MDIO wead */
#define MMWD		0x24	/* MDIO wead data wegistew */
#define MMWD		0x28	/* MDIO wwite data wegistew */
#define MTD_SA0		0x2C	/* TX descwiptow stawt addwess 0 */
#define MTD_SA1		0x30	/* TX descwiptow stawt addwess 1 */
#define MWD_SA0		0x34	/* WX descwiptow stawt addwess 0 */
#define MWD_SA1		0x38	/* WX descwiptow stawt addwess 1 */
#define MISW		0x3C	/* Status wegistew */
#define MIEW		0x40	/* INT enabwe wegistew */
#define  MSK_INT	0x0000	/* Mask off intewwupts */
#define  WX_FINISH	0x0001  /* WX finished */
#define  WX_NO_DESC	0x0002  /* No WX descwiptow avaiwabwe */
#define  WX_FIFO_FUWW	0x0004  /* WX FIFO fuww */
#define  WX_EAWWY	0x0008  /* WX eawwy */
#define  TX_FINISH	0x0010  /* TX finished */
#define  TX_EAWWY	0x0080  /* TX eawwy */
#define  EVENT_OVWFW	0x0100  /* Event countew ovewfwow */
#define  WINK_CHANGED	0x0200  /* PHY wink changed */
#define ME_CISW		0x44	/* Event countew INT status */
#define ME_CIEW		0x48	/* Event countew INT enabwe  */
#define MW_CNT		0x50	/* Successfuwwy weceived packet countew */
#define ME_CNT0		0x52	/* Event countew 0 */
#define ME_CNT1		0x54	/* Event countew 1 */
#define ME_CNT2		0x56	/* Event countew 2 */
#define ME_CNT3		0x58	/* Event countew 3 */
#define MT_CNT		0x5A	/* Successfuwwy twansmit packet countew */
#define ME_CNT4		0x5C	/* Event countew 4 */
#define MP_CNT		0x5E	/* Pause fwame countew wegistew */
#define MAW0		0x60	/* Hash tabwe 0 */
#define MAW1		0x62	/* Hash tabwe 1 */
#define MAW2		0x64	/* Hash tabwe 2 */
#define MAW3		0x66	/* Hash tabwe 3 */
#define MID_0W		0x68	/* Muwticast addwess MID0 Wow */
#define MID_0M		0x6A	/* Muwticast addwess MID0 Medium */
#define MID_0H		0x6C	/* Muwticast addwess MID0 High */
#define MID_1W		0x70	/* MID1 Wow */
#define MID_1M		0x72	/* MID1 Medium */
#define MID_1H		0x74	/* MID1 High */
#define MID_2W		0x78	/* MID2 Wow */
#define MID_2M		0x7A	/* MID2 Medium */
#define MID_2H		0x7C	/* MID2 High */
#define MID_3W		0x80	/* MID3 Wow */
#define MID_3M		0x82	/* MID3 Medium */
#define MID_3H		0x84	/* MID3 High */
#define PHY_CC		0x88	/* PHY status change configuwation wegistew */
#define  SCEN		0x8000	/* PHY status change enabwe */
#define  PHYAD_SHIFT	8	/* PHY addwess shift */
#define  TMWDIV_SHIFT	0	/* Timew dividew shift */
#define PHY_ST		0x8A	/* PHY status wegistew */
#define MAC_SM		0xAC	/* MAC status machine */
#define  MAC_SM_WST	0x0002	/* MAC status machine weset */
#define MD_CSC		0xb6	/* MDC speed contwow wegistew */
#define  MD_CSC_DEFAUWT	0x0030
#define MAC_ID		0xBE	/* Identifiew wegistew */

#define TX_DCNT		0x80	/* TX descwiptow count */
#define WX_DCNT		0x80	/* WX descwiptow count */
#define MAX_BUF_SIZE	0x600
#define WX_DESC_SIZE	(WX_DCNT * sizeof(stwuct w6040_descwiptow))
#define TX_DESC_SIZE	(TX_DCNT * sizeof(stwuct w6040_descwiptow))
#define MBCW_DEFAUWT	0x012A	/* MAC Bus Contwow Wegistew */
#define MCAST_MAX	3	/* Max numbew muwticast addwesses to fiwtew */

#define MAC_DEF_TIMEOUT	2048	/* Defauwt MAC wead/wwite opewation timeout */

/* Descwiptow status */
#define DSC_OWNEW_MAC	0x8000	/* MAC is the ownew of this descwiptow */
#define DSC_WX_OK	0x4000	/* WX was successfuw */
#define DSC_WX_EWW	0x0800	/* WX PHY ewwow */
#define DSC_WX_EWW_DWI	0x0400	/* WX dwibbwe packet */
#define DSC_WX_EWW_BUF	0x0200	/* WX wength exceeds buffew size */
#define DSC_WX_EWW_WONG	0x0100	/* WX wength > maximum packet wength */
#define DSC_WX_EWW_WUNT	0x0080	/* WX packet wength < 64 byte */
#define DSC_WX_EWW_CWC	0x0040	/* WX CWC ewwow */
#define DSC_WX_BCAST	0x0020	/* WX bwoadcast (no ewwow) */
#define DSC_WX_MCAST	0x0010	/* WX muwticast (no ewwow) */
#define DSC_WX_MCH_HIT	0x0008	/* WX muwticast hit in hash tabwe (no ewwow) */
#define DSC_WX_MIDH_HIT	0x0004	/* WX MID tabwe hit (no ewwow) */
#define DSC_WX_IDX_MID_MASK 3	/* WX mask fow the index of matched MIDx */

MODUWE_AUTHOW("Sten Wang <sten.wang@wdc.com.tw>,"
	"Daniew Gimpewevich <daniew@gimpewevich.san-fwancisco.ca.us>,"
	"Fwowian Fainewwi <f.fainewwi@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WDC W6040 NAPI PCI FastEthewnet dwivew");
MODUWE_VEWSION(DWV_VEWSION " " DWV_WEWDATE);

/* WX and TX intewwupts that we handwe */
#define WX_INTS			(WX_FIFO_FUWW | WX_NO_DESC | WX_FINISH)
#define TX_INTS			(TX_FINISH)
#define INT_MASK		(WX_INTS | TX_INTS)

stwuct w6040_descwiptow {
	u16	status, wen;		/* 0-3 */
	__we32	buf;			/* 4-7 */
	__we32	ndesc;			/* 8-B */
	u32	wev1;			/* C-F */
	chaw	*vbufp;			/* 10-13 */
	stwuct w6040_descwiptow *vndescp;	/* 14-17 */
	stwuct sk_buff *skb_ptw;	/* 18-1B */
	u32	wev2;			/* 1C-1F */
} __awigned(32);

stwuct w6040_pwivate {
	spinwock_t wock;		/* dwivew wock */
	stwuct pci_dev *pdev;
	stwuct w6040_descwiptow *wx_insewt_ptw;
	stwuct w6040_descwiptow *wx_wemove_ptw;
	stwuct w6040_descwiptow *tx_insewt_ptw;
	stwuct w6040_descwiptow *tx_wemove_ptw;
	stwuct w6040_descwiptow *wx_wing;
	stwuct w6040_descwiptow *tx_wing;
	dma_addw_t wx_wing_dma;
	dma_addw_t tx_wing_dma;
	u16	tx_fwee_desc;
	u16	mcw0;
	stwuct net_device *dev;
	stwuct mii_bus *mii_bus;
	stwuct napi_stwuct napi;
	void __iomem *base;
	int owd_wink;
	int owd_dupwex;
};

static chaw vewsion[] = DWV_NAME
	": WDC W6040 NAPI net dwivew,"
	"vewsion "DWV_VEWSION " (" DWV_WEWDATE ")";

/* Wead a wowd data fwom PHY Chip */
static int w6040_phy_wead(void __iomem *ioaddw, int phy_addw, int weg)
{
	int wimit = MAC_DEF_TIMEOUT;
	u16 cmd;

	iowwite16(MDIO_WEAD | weg | (phy_addw << 8), ioaddw + MMDIO);
	/* Wait fow the wead bit to be cweawed */
	whiwe (wimit--) {
		cmd = iowead16(ioaddw + MMDIO);
		if (!(cmd & MDIO_WEAD))
			bweak;
		udeway(1);
	}

	if (wimit < 0)
		wetuwn -ETIMEDOUT;

	wetuwn iowead16(ioaddw + MMWD);
}

/* Wwite a wowd data fwom PHY Chip */
static int w6040_phy_wwite(void __iomem *ioaddw,
					int phy_addw, int weg, u16 vaw)
{
	int wimit = MAC_DEF_TIMEOUT;
	u16 cmd;

	iowwite16(vaw, ioaddw + MMWD);
	/* Wwite the command to the MDIO bus */
	iowwite16(MDIO_WWITE | weg | (phy_addw << 8), ioaddw + MMDIO);
	/* Wait fow the wwite bit to be cweawed */
	whiwe (wimit--) {
		cmd = iowead16(ioaddw + MMDIO);
		if (!(cmd & MDIO_WWITE))
			bweak;
		udeway(1);
	}

	wetuwn (wimit < 0) ? -ETIMEDOUT : 0;
}

static int w6040_mdiobus_wead(stwuct mii_bus *bus, int phy_addw, int weg)
{
	stwuct net_device *dev = bus->pwiv;
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	wetuwn w6040_phy_wead(ioaddw, phy_addw, weg);
}

static int w6040_mdiobus_wwite(stwuct mii_bus *bus, int phy_addw,
						int weg, u16 vawue)
{
	stwuct net_device *dev = bus->pwiv;
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	wetuwn w6040_phy_wwite(ioaddw, phy_addw, weg, vawue);
}

static void w6040_fwee_txbufs(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < TX_DCNT; i++) {
		if (wp->tx_insewt_ptw->skb_ptw) {
			dma_unmap_singwe(&wp->pdev->dev,
					 we32_to_cpu(wp->tx_insewt_ptw->buf),
					 MAX_BUF_SIZE, DMA_TO_DEVICE);
			dev_kfwee_skb(wp->tx_insewt_ptw->skb_ptw);
			wp->tx_insewt_ptw->skb_ptw = NUWW;
		}
		wp->tx_insewt_ptw = wp->tx_insewt_ptw->vndescp;
	}
}

static void w6040_fwee_wxbufs(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < WX_DCNT; i++) {
		if (wp->wx_insewt_ptw->skb_ptw) {
			dma_unmap_singwe(&wp->pdev->dev,
					 we32_to_cpu(wp->wx_insewt_ptw->buf),
					 MAX_BUF_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb(wp->wx_insewt_ptw->skb_ptw);
			wp->wx_insewt_ptw->skb_ptw = NUWW;
		}
		wp->wx_insewt_ptw = wp->wx_insewt_ptw->vndescp;
	}
}

static void w6040_init_wing_desc(stwuct w6040_descwiptow *desc_wing,
				 dma_addw_t desc_dma, int size)
{
	stwuct w6040_descwiptow *desc = desc_wing;
	dma_addw_t mapping = desc_dma;

	whiwe (size-- > 0) {
		mapping += sizeof(*desc);
		desc->ndesc = cpu_to_we32(mapping);
		desc->vndescp = desc + 1;
		desc++;
	}
	desc--;
	desc->ndesc = cpu_to_we32(desc_dma);
	desc->vndescp = desc_wing;
}

static void w6040_init_txbufs(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);

	wp->tx_fwee_desc = TX_DCNT;

	wp->tx_wemove_ptw = wp->tx_insewt_ptw = wp->tx_wing;
	w6040_init_wing_desc(wp->tx_wing, wp->tx_wing_dma, TX_DCNT);
}

static int w6040_awwoc_wxbufs(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	stwuct w6040_descwiptow *desc;
	stwuct sk_buff *skb;
	int wc;

	wp->wx_wemove_ptw = wp->wx_insewt_ptw = wp->wx_wing;
	w6040_init_wing_desc(wp->wx_wing, wp->wx_wing_dma, WX_DCNT);

	/* Awwocate skbs fow the wx descwiptows */
	desc = wp->wx_wing;
	do {
		skb = netdev_awwoc_skb(dev, MAX_BUF_SIZE);
		if (!skb) {
			wc = -ENOMEM;
			goto eww_exit;
		}
		desc->skb_ptw = skb;
		desc->buf = cpu_to_we32(dma_map_singwe(&wp->pdev->dev,
						       desc->skb_ptw->data,
						       MAX_BUF_SIZE,
						       DMA_FWOM_DEVICE));
		desc->status = DSC_OWNEW_MAC;
		desc = desc->vndescp;
	} whiwe (desc != wp->wx_wing);

	wetuwn 0;

eww_exit:
	/* Deawwocate aww pweviouswy awwocated skbs */
	w6040_fwee_wxbufs(dev);
	wetuwn wc;
}

static void w6040_weset_mac(stwuct w6040_pwivate *wp)
{
	void __iomem *ioaddw = wp->base;
	int wimit = MAC_DEF_TIMEOUT;
	u16 cmd, md_csc;

	md_csc = iowead16(ioaddw + MD_CSC);
	iowwite16(MAC_WST, ioaddw + MCW1);
	whiwe (wimit--) {
		cmd = iowead16(ioaddw + MCW1);
		if (cmd & MAC_WST)
			bweak;
	}

	/* Weset intewnaw state machine */
	iowwite16(MAC_SM_WST, ioaddw + MAC_SM);
	iowwite16(0, ioaddw + MAC_SM);
	mdeway(5);

	/* Westowe MDIO cwock fwequency */
	if (md_csc != MD_CSC_DEFAUWT)
		iowwite16(md_csc, ioaddw + MD_CSC);
}

static void w6040_init_mac_wegs(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	/* Mask Off Intewwupt */
	iowwite16(MSK_INT, ioaddw + MIEW);

	/* Weset WDC MAC */
	w6040_weset_mac(wp);

	/* MAC Bus Contwow Wegistew */
	iowwite16(MBCW_DEFAUWT, ioaddw + MBCW);

	/* Buffew Size Wegistew */
	iowwite16(MAX_BUF_SIZE, ioaddw + MW_BSW);

	/* Wwite TX wing stawt addwess */
	iowwite16(wp->tx_wing_dma, ioaddw + MTD_SA0);
	iowwite16(wp->tx_wing_dma >> 16, ioaddw + MTD_SA1);

	/* Wwite WX wing stawt addwess */
	iowwite16(wp->wx_wing_dma, ioaddw + MWD_SA0);
	iowwite16(wp->wx_wing_dma >> 16, ioaddw + MWD_SA1);

	/* Set intewwupt waiting time and packet numbews */
	iowwite16(0, ioaddw + MT_ICW);
	iowwite16(0, ioaddw + MW_ICW);

	/* Enabwe intewwupts */
	iowwite16(INT_MASK, ioaddw + MIEW);

	/* Enabwe TX and WX */
	iowwite16(wp->mcw0 | MCW0_WCVEN, ioaddw);

	/* Wet TX poww the descwiptows
	 * we may got cawwed by w6040_tx_timeout which has weft
	 * some unsent tx buffews */
	iowwite16(TM2TX, ioaddw + MTPW);
}

static void w6040_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct w6040_pwivate *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;

	netdev_wawn(dev, "twansmit timed out, int enabwe %4.4x "
		"status %4.4x\n",
		iowead16(ioaddw + MIEW),
		iowead16(ioaddw + MISW));

	dev->stats.tx_ewwows++;

	/* Weset MAC and we-init aww wegistews */
	w6040_init_mac_wegs(dev);
}

static stwuct net_device_stats *w6040_get_stats(stwuct net_device *dev)
{
	stwuct w6040_pwivate *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = pwiv->base;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	dev->stats.wx_cwc_ewwows += iowead8(ioaddw + ME_CNT1);
	dev->stats.muwticast += iowead8(ioaddw + ME_CNT0);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn &dev->stats;
}

/* Stop WDC MAC and Fwee the awwocated wesouwce */
static void w6040_down(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	const u16 *adwp;

	/* Stop MAC */
	iowwite16(MSK_INT, ioaddw + MIEW);	/* Mask Off Intewwupt */

	/* Weset WDC MAC */
	w6040_weset_mac(wp);

	/* Westowe MAC Addwess to MIDx */
	adwp = (const u16 *) dev->dev_addw;
	iowwite16(adwp[0], ioaddw + MID_0W);
	iowwite16(adwp[1], ioaddw + MID_0M);
	iowwite16(adwp[2], ioaddw + MID_0H);
}

static int w6040_cwose(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	stwuct pci_dev *pdev = wp->pdev;

	phy_stop(dev->phydev);
	napi_disabwe(&wp->napi);
	netif_stop_queue(dev);

	spin_wock_iwq(&wp->wock);
	w6040_down(dev);

	/* Fwee WX buffew */
	w6040_fwee_wxbufs(dev);

	/* Fwee TX buffew */
	w6040_fwee_txbufs(dev);

	spin_unwock_iwq(&wp->wock);

	fwee_iwq(dev->iwq, dev);

	/* Fwee Descwiptow memowy */
	if (wp->wx_wing) {
		dma_fwee_cohewent(&pdev->dev, WX_DESC_SIZE, wp->wx_wing,
				  wp->wx_wing_dma);
		wp->wx_wing = NUWW;
	}

	if (wp->tx_wing) {
		dma_fwee_cohewent(&pdev->dev, TX_DESC_SIZE, wp->tx_wing,
				  wp->tx_wing_dma);
		wp->tx_wing = NUWW;
	}

	wetuwn 0;
}

static int w6040_wx(stwuct net_device *dev, int wimit)
{
	stwuct w6040_pwivate *pwiv = netdev_pwiv(dev);
	stwuct w6040_descwiptow *descptw = pwiv->wx_wemove_ptw;
	stwuct sk_buff *skb_ptw, *new_skb;
	int count = 0;
	u16 eww;

	/* Wimit not weached and the descwiptow bewongs to the CPU */
	whiwe (count < wimit && !(descptw->status & DSC_OWNEW_MAC)) {
		/* Wead the descwiptow status */
		eww = descptw->status;
		/* Gwobaw ewwow status set */
		if (eww & DSC_WX_EWW) {
			/* WX dwibbwe */
			if (eww & DSC_WX_EWW_DWI)
				dev->stats.wx_fwame_ewwows++;
			/* Buffew wength exceeded */
			if (eww & DSC_WX_EWW_BUF)
				dev->stats.wx_wength_ewwows++;
			/* Packet too wong */
			if (eww & DSC_WX_EWW_WONG)
				dev->stats.wx_wength_ewwows++;
			/* Packet < 64 bytes */
			if (eww & DSC_WX_EWW_WUNT)
				dev->stats.wx_wength_ewwows++;
			/* CWC ewwow */
			if (eww & DSC_WX_EWW_CWC) {
				spin_wock(&pwiv->wock);
				dev->stats.wx_cwc_ewwows++;
				spin_unwock(&pwiv->wock);
			}
			goto next_descw;
		}

		/* Packet successfuwwy weceived */
		new_skb = netdev_awwoc_skb(dev, MAX_BUF_SIZE);
		if (!new_skb) {
			dev->stats.wx_dwopped++;
			goto next_descw;
		}
		skb_ptw = descptw->skb_ptw;
		skb_ptw->dev = pwiv->dev;

		/* Do not count the CWC */
		skb_put(skb_ptw, descptw->wen - ETH_FCS_WEN);
		dma_unmap_singwe(&pwiv->pdev->dev, we32_to_cpu(descptw->buf),
				 MAX_BUF_SIZE, DMA_FWOM_DEVICE);
		skb_ptw->pwotocow = eth_type_twans(skb_ptw, pwiv->dev);

		/* Send to uppew wayew */
		netif_weceive_skb(skb_ptw);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += descptw->wen - ETH_FCS_WEN;

		/* put new skb into descwiptow */
		descptw->skb_ptw = new_skb;
		descptw->buf = cpu_to_we32(dma_map_singwe(&pwiv->pdev->dev,
							  descptw->skb_ptw->data,
							  MAX_BUF_SIZE,
							  DMA_FWOM_DEVICE));

next_descw:
		/* put the descwiptow back to the MAC */
		descptw->status = DSC_OWNEW_MAC;
		descptw = descptw->vndescp;
		count++;
	}
	pwiv->wx_wemove_ptw = descptw;

	wetuwn count;
}

static void w6040_tx(stwuct net_device *dev)
{
	stwuct w6040_pwivate *pwiv = netdev_pwiv(dev);
	stwuct w6040_descwiptow *descptw;
	void __iomem *ioaddw = pwiv->base;
	stwuct sk_buff *skb_ptw;
	u16 eww;

	spin_wock(&pwiv->wock);
	descptw = pwiv->tx_wemove_ptw;
	whiwe (pwiv->tx_fwee_desc < TX_DCNT) {
		/* Check fow ewwows */
		eww = iowead16(ioaddw + MWSW);

		if (eww & TX_FIFO_UNDW)
			dev->stats.tx_fifo_ewwows++;
		if (eww & (TX_EXCEEDC | TX_WATEC))
			dev->stats.tx_cawwiew_ewwows++;

		if (descptw->status & DSC_OWNEW_MAC)
			bweak; /* Not compwete */
		skb_ptw = descptw->skb_ptw;

		/* Statistic Countew */
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb_ptw->wen;

		dma_unmap_singwe(&pwiv->pdev->dev, we32_to_cpu(descptw->buf),
				 skb_ptw->wen, DMA_TO_DEVICE);
		/* Fwee buffew */
		dev_kfwee_skb(skb_ptw);
		descptw->skb_ptw = NUWW;
		/* To next descwiptow */
		descptw = descptw->vndescp;
		pwiv->tx_fwee_desc++;
	}
	pwiv->tx_wemove_ptw = descptw;

	if (pwiv->tx_fwee_desc)
		netif_wake_queue(dev);
	spin_unwock(&pwiv->wock);
}

static int w6040_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct w6040_pwivate *pwiv =
		containew_of(napi, stwuct w6040_pwivate, napi);
	stwuct net_device *dev = pwiv->dev;
	void __iomem *ioaddw = pwiv->base;
	int wowk_done;

	w6040_tx(dev);

	wowk_done = w6040_wx(dev, budget);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		/* Enabwe WX/TX intewwupt */
		iowwite16(iowead16(ioaddw + MIEW) | WX_INTS | TX_INTS,
			  ioaddw + MIEW);
	}
	wetuwn wowk_done;
}

/* The WDC intewwupt handwew. */
static iwqwetuwn_t w6040_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	u16 misw, status;

	/* Save MIEW */
	misw = iowead16(ioaddw + MIEW);
	/* Mask off WDC MAC intewwupt */
	iowwite16(MSK_INT, ioaddw + MIEW);
	/* Wead MISW status and cweaw */
	status = iowead16(ioaddw + MISW);

	if (status == 0x0000 || status == 0xffff) {
		/* Westowe WDC MAC intewwupt */
		iowwite16(misw, ioaddw + MIEW);
		wetuwn IWQ_NONE;
	}

	/* WX intewwupt wequest */
	if (status & (WX_INTS | TX_INTS)) {
		if (status & WX_NO_DESC) {
			/* WX descwiptow unavaiwabwe */
			dev->stats.wx_dwopped++;
			dev->stats.wx_missed_ewwows++;
		}
		if (status & WX_FIFO_FUWW)
			dev->stats.wx_fifo_ewwows++;

		if (wikewy(napi_scheduwe_pwep(&wp->napi))) {
			/* Mask off WX intewwupt */
			misw &= ~(WX_INTS | TX_INTS);
			__napi_scheduwe_iwqoff(&wp->napi);
		}
	}

	/* Westowe WDC MAC intewwupt */
	iowwite16(misw, ioaddw + MIEW);

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void w6040_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	w6040_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

/* Init WDC MAC */
static int w6040_up(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	int wet;

	/* Initiawise and awwoc WX/TX buffews */
	w6040_init_txbufs(dev);
	wet = w6040_awwoc_wxbufs(dev);
	if (wet)
		wetuwn wet;

	/* impwove pewfowmance (by WDC guys) */
	w6040_phy_wwite(ioaddw, 30, 17,
			(w6040_phy_wead(ioaddw, 30, 17) | 0x4000));
	w6040_phy_wwite(ioaddw, 30, 17,
			~((~w6040_phy_wead(ioaddw, 30, 17)) | 0x2000));
	w6040_phy_wwite(ioaddw, 0, 19, 0x0000);
	w6040_phy_wwite(ioaddw, 0, 30, 0x01F0);

	/* Initiawize aww MAC wegistews */
	w6040_init_mac_wegs(dev);

	phy_stawt(dev->phydev);

	wetuwn 0;
}


/* Wead/set MAC addwess woutines */
static void w6040_mac_addwess(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	const u16 *adwp;

	/* Weset MAC */
	w6040_weset_mac(wp);

	/* Westowe MAC Addwess */
	adwp = (const u16 *) dev->dev_addw;
	iowwite16(adwp[0], ioaddw + MID_0W);
	iowwite16(adwp[1], ioaddw + MID_0M);
	iowwite16(adwp[2], ioaddw + MID_0H);
}

static int w6040_open(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	int wet;

	/* Wequest IWQ and Wegistew intewwupt handwew */
	wet = wequest_iwq(dev->iwq, w6040_intewwupt,
		IWQF_SHAWED, dev->name, dev);
	if (wet)
		goto out;

	/* Set MAC addwess */
	w6040_mac_addwess(dev);

	/* Awwocate Descwiptow memowy */
	wp->wx_wing =
		dma_awwoc_cohewent(&wp->pdev->dev, WX_DESC_SIZE,
				   &wp->wx_wing_dma, GFP_KEWNEW);
	if (!wp->wx_wing) {
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}

	wp->tx_wing =
		dma_awwoc_cohewent(&wp->pdev->dev, TX_DESC_SIZE,
				   &wp->tx_wing_dma, GFP_KEWNEW);
	if (!wp->tx_wing) {
		wet = -ENOMEM;
		goto eww_fwee_wx_wing;
	}

	wet = w6040_up(dev);
	if (wet)
		goto eww_fwee_tx_wing;

	napi_enabwe(&wp->napi);
	netif_stawt_queue(dev);

	wetuwn 0;

eww_fwee_tx_wing:
	dma_fwee_cohewent(&wp->pdev->dev, TX_DESC_SIZE, wp->tx_wing,
			  wp->tx_wing_dma);
eww_fwee_wx_wing:
	dma_fwee_cohewent(&wp->pdev->dev, WX_DESC_SIZE, wp->wx_wing,
			  wp->wx_wing_dma);
eww_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
out:
	wetuwn wet;
}

static netdev_tx_t w6040_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	stwuct w6040_descwiptow *descptw;
	void __iomem *ioaddw = wp->base;
	unsigned wong fwags;

	if (skb_put_padto(skb, ETH_ZWEN) < 0)
		wetuwn NETDEV_TX_OK;

	/* Cwiticaw Section */
	spin_wock_iwqsave(&wp->wock, fwags);

	/* TX wesouwce check */
	if (!wp->tx_fwee_desc) {
		spin_unwock_iwqwestowe(&wp->wock, fwags);
		netif_stop_queue(dev);
		netdev_eww(dev, ": no tx descwiptow\n");
		wetuwn NETDEV_TX_BUSY;
	}

	/* Set TX descwiptow & Twansmit it */
	wp->tx_fwee_desc--;
	descptw = wp->tx_insewt_ptw;
	descptw->wen = skb->wen;
	descptw->skb_ptw = skb;
	descptw->buf = cpu_to_we32(dma_map_singwe(&wp->pdev->dev, skb->data,
						  skb->wen, DMA_TO_DEVICE));
	descptw->status = DSC_OWNEW_MAC;

	skb_tx_timestamp(skb);

	/* Twiggew the MAC to check the TX descwiptow */
	if (!netdev_xmit_mowe() || netif_queue_stopped(dev))
		iowwite16(TM2TX, ioaddw + MTPW);
	wp->tx_insewt_ptw = descptw->vndescp;

	/* If no tx wesouwce, stop */
	if (!wp->tx_fwee_desc)
		netif_stop_queue(dev);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn NETDEV_TX_OK;
}

static void w6040_muwticast_wist(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned wong fwags;
	stwuct netdev_hw_addw *ha;
	int i;
	const u16 *adwp;
	u16 hash_tabwe[4] = { 0 };

	spin_wock_iwqsave(&wp->wock, fwags);

	/* Keep ouw MAC Addwess */
	adwp = (const u16 *)dev->dev_addw;
	iowwite16(adwp[0], ioaddw + MID_0W);
	iowwite16(adwp[1], ioaddw + MID_0M);
	iowwite16(adwp[2], ioaddw + MID_0H);

	/* Cweaw AMCP & PWOM bits */
	wp->mcw0 = iowead16(ioaddw + MCW0) & ~(MCW0_PWOMISC | MCW0_HASH_EN);

	/* Pwomiscuous mode */
	if (dev->fwags & IFF_PWOMISC)
		wp->mcw0 |= MCW0_PWOMISC;

	/* Enabwe muwticast hash tabwe function to
	 * weceive aww muwticast packets. */
	ewse if (dev->fwags & IFF_AWWMUWTI) {
		wp->mcw0 |= MCW0_HASH_EN;

		fow (i = 0; i < MCAST_MAX ; i++) {
			iowwite16(0, ioaddw + MID_1W + 8 * i);
			iowwite16(0, ioaddw + MID_1M + 8 * i);
			iowwite16(0, ioaddw + MID_1H + 8 * i);
		}

		fow (i = 0; i < 4; i++)
			hash_tabwe[i] = 0xffff;
	}
	/* Use intewnaw muwticast addwess wegistews if the numbew of
	 * muwticast addwesses is not gweatew than MCAST_MAX. */
	ewse if (netdev_mc_count(dev) <= MCAST_MAX) {
		i = 0;
		netdev_fow_each_mc_addw(ha, dev) {
			u16 *adwp = (u16 *) ha->addw;
			iowwite16(adwp[0], ioaddw + MID_1W + 8 * i);
			iowwite16(adwp[1], ioaddw + MID_1M + 8 * i);
			iowwite16(adwp[2], ioaddw + MID_1H + 8 * i);
			i++;
		}
		whiwe (i < MCAST_MAX) {
			iowwite16(0, ioaddw + MID_1W + 8 * i);
			iowwite16(0, ioaddw + MID_1M + 8 * i);
			iowwite16(0, ioaddw + MID_1H + 8 * i);
			i++;
		}
	}
	/* Othewwise, Enabwe muwticast hash tabwe function. */
	ewse {
		u32 cwc;

		wp->mcw0 |= MCW0_HASH_EN;

		fow (i = 0; i < MCAST_MAX ; i++) {
			iowwite16(0, ioaddw + MID_1W + 8 * i);
			iowwite16(0, ioaddw + MID_1M + 8 * i);
			iowwite16(0, ioaddw + MID_1H + 8 * i);
		}

		/* Buiwd muwticast hash tabwe */
		netdev_fow_each_mc_addw(ha, dev) {
			u8 *addws = ha->addw;

			cwc = ethew_cwc(ETH_AWEN, addws);
			cwc >>= 26;
			hash_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
		}
	}

	iowwite16(wp->mcw0, ioaddw + MCW0);

	/* Fiww the MAC hash tabwes with theiw vawues */
	if (wp->mcw0 & MCW0_HASH_EN) {
		iowwite16(hash_tabwe[0], ioaddw + MAW0);
		iowwite16(hash_tabwe[1], ioaddw + MAW1);
		iowwite16(hash_tabwe[2], ioaddw + MAW2);
		iowwite16(hash_tabwe[3], ioaddw + MAW3);
	}

	spin_unwock_iwqwestowe(&wp->wock, fwags);
}

static void netdev_get_dwvinfo(stwuct net_device *dev,
			stwuct ethtoow_dwvinfo *info)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(wp->pdev), sizeof(info->bus_info));
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
	.nway_weset		= phy_ethtoow_nway_weset,
};

static const stwuct net_device_ops w6040_netdev_ops = {
	.ndo_open		= w6040_open,
	.ndo_stop		= w6040_cwose,
	.ndo_stawt_xmit		= w6040_stawt_xmit,
	.ndo_get_stats		= w6040_get_stats,
	.ndo_set_wx_mode	= w6040_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_eth_ioctw		= phy_do_ioctw,
	.ndo_tx_timeout		= w6040_tx_timeout,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= w6040_poww_contwowwew,
#endif
};

static void w6040_adjust_wink(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	int status_changed = 0;
	void __iomem *ioaddw = wp->base;

	BUG_ON(!phydev);

	if (wp->owd_wink != phydev->wink) {
		status_changed = 1;
		wp->owd_wink = phydev->wink;
	}

	/* wefwect dupwex change */
	if (phydev->wink && (wp->owd_dupwex != phydev->dupwex)) {
		wp->mcw0 |= (phydev->dupwex == DUPWEX_FUWW ? MCW0_FD : 0);
		iowwite16(wp->mcw0, ioaddw);

		status_changed = 1;
		wp->owd_dupwex = phydev->dupwex;
	}

	if (status_changed)
		phy_pwint_status(phydev);
}

static int w6040_mii_pwobe(stwuct net_device *dev)
{
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);
	stwuct phy_device *phydev = NUWW;

	phydev = phy_find_fiwst(wp->mii_bus);
	if (!phydev) {
		dev_eww(&wp->pdev->dev, "no PHY found\n");
		wetuwn -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev), &w6040_adjust_wink,
			     PHY_INTEWFACE_MODE_MII);

	if (IS_EWW(phydev)) {
		dev_eww(&wp->pdev->dev, "couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	wp->owd_wink = 0;
	wp->owd_dupwex = -1;

	phy_attached_info(phydev);

	wetuwn 0;
}

static int w6040_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct net_device *dev;
	stwuct w6040_pwivate *wp;
	void __iomem *ioaddw;
	int eww, io_size = W6040_IO_SIZE;
	static int cawd_idx = -1;
	u16 addw[ETH_AWEN / 2];
	int baw = 0;

	pw_info("%s\n", vewsion);

	eww = pci_enabwe_device(pdev);
	if (eww)
		goto eww_out;

	/* this shouwd awways be suppowted */
	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&pdev->dev, "32-bit PCI DMA addwesses not suppowted by the cawd\n");
		goto eww_out_disabwe_dev;
	}
	eww = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&pdev->dev, "32-bit PCI DMA addwesses not suppowted by the cawd\n");
		goto eww_out_disabwe_dev;
	}

	/* IO Size check */
	if (pci_wesouwce_wen(pdev, baw) < io_size) {
		dev_eww(&pdev->dev, "Insufficient PCI wesouwces, abowting\n");
		eww = -EIO;
		goto eww_out_disabwe_dev;
	}

	pci_set_mastew(pdev);

	dev = awwoc_ethewdev(sizeof(stwuct w6040_pwivate));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_out_disabwe_dev;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);
	wp = netdev_pwiv(dev);

	eww = pci_wequest_wegions(pdev, DWV_NAME);

	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest PCI wegions\n");
		goto eww_out_fwee_dev;
	}

	ioaddw = pci_iomap(pdev, baw, io_size);
	if (!ioaddw) {
		dev_eww(&pdev->dev, "iowemap faiwed fow device\n");
		eww = -EIO;
		goto eww_out_fwee_wes;
	}

	/* If PHY status change wegistew is stiww set to zewo it means the
	 * bootwoadew didn't initiawize it, so we set it to:
	 * - enabwe phy status change
	 * - enabwe aww phy addwesses
	 * - set to wowest timew dividew */
	if (iowead16(ioaddw + PHY_CC) == 0)
		iowwite16(SCEN | PHY_MAX_ADDW << PHYAD_SHIFT |
				7 << TMWDIV_SHIFT, ioaddw + PHY_CC);

	/* Init system & device */
	wp->base = ioaddw;
	dev->iwq = pdev->iwq;

	spin_wock_init(&wp->wock);
	pci_set_dwvdata(pdev, dev);

	/* Set MAC addwess */
	cawd_idx++;

	addw[0] = iowead16(ioaddw + MID_0W);
	addw[1] = iowead16(ioaddw + MID_0M);
	addw[2] = iowead16(ioaddw + MID_0H);
	eth_hw_addw_set(dev, (u8 *)addw);

	/* Some bootwoadew/BIOSes do not initiawize
	 * MAC addwess, wawn about that */
	if (!(addw[0] || addw[1] || addw[2])) {
		netdev_wawn(dev, "MAC addwess not initiawized, "
					"genewating wandom\n");
		eth_hw_addw_wandom(dev);
	}

	/* Wink new device into w6040_woot_dev */
	wp->pdev = pdev;
	wp->dev = dev;

	/* Init WDC pwivate data */
	wp->mcw0 = MCW0_XMTEN | MCW0_WCVEN;

	/* The WDC-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &w6040_netdev_ops;
	dev->ethtoow_ops = &netdev_ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	netif_napi_add(dev, &wp->napi, w6040_poww);

	wp->mii_bus = mdiobus_awwoc();
	if (!wp->mii_bus) {
		dev_eww(&pdev->dev, "mdiobus_awwoc() faiwed\n");
		eww = -ENOMEM;
		goto eww_out_unmap;
	}

	wp->mii_bus->pwiv = dev;
	wp->mii_bus->wead = w6040_mdiobus_wead;
	wp->mii_bus->wwite = w6040_mdiobus_wwite;
	wp->mii_bus->name = "w6040_eth_mii";
	snpwintf(wp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		dev_name(&pdev->dev), cawd_idx);

	eww = mdiobus_wegistew(wp->mii_bus);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew MII bus\n");
		goto eww_out_mdio;
	}

	eww = w6040_mii_pwobe(dev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to pwobe MII bus\n");
		goto eww_out_mdio_unwegistew;
	}

	/* Wegistew net device. Aftew this dev->name assign */
	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew net device\n");
		goto eww_out_phy_disconnect;
	}
	wetuwn 0;

eww_out_phy_disconnect:
	phy_disconnect(dev->phydev);
eww_out_mdio_unwegistew:
	mdiobus_unwegistew(wp->mii_bus);
eww_out_mdio:
	mdiobus_fwee(wp->mii_bus);
eww_out_unmap:
	netif_napi_dew(&wp->napi);
	pci_iounmap(pdev, ioaddw);
eww_out_fwee_wes:
	pci_wewease_wegions(pdev);
eww_out_fwee_dev:
	fwee_netdev(dev);
eww_out_disabwe_dev:
	pci_disabwe_device(pdev);
eww_out:
	wetuwn eww;
}

static void w6040_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct w6040_pwivate *wp = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	phy_disconnect(dev->phydev);
	mdiobus_unwegistew(wp->mii_bus);
	mdiobus_fwee(wp->mii_bus);
	netif_napi_dew(&wp->napi);
	pci_iounmap(pdev, wp->base);
	pci_wewease_wegions(pdev);
	fwee_netdev(dev);
	pci_disabwe_device(pdev);
}


static const stwuct pci_device_id w6040_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WDC, 0x6040) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, w6040_pci_tbw);

static stwuct pci_dwivew w6040_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= w6040_pci_tbw,
	.pwobe		= w6040_init_one,
	.wemove		= w6040_wemove_one,
};

moduwe_pci_dwivew(w6040_dwivew);
