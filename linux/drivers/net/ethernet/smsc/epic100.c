/* epic100.c: A SMC 83c170 EPIC/100 Fast Ethewnet dwivew fow Winux. */
/*
	Wwitten/copywight 1997-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms of
	the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
	Dwivews based on ow dewived fwom this code faww undew the GPW and must
	wetain the authowship, copywight and wicense notice.  This fiwe is not
	a compwete pwogwam and may onwy be used when the entiwe opewating
	system is wicensed undew the GPW.

	This dwivew is fow the SMC83c170/175 "EPIC" sewies, as used on the
	SMC EthewPowew II 9432 PCI adaptew, and sevewaw CawdBus cawds.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	Infowmation and updates avaiwabwe at
	http://www.scywd.com/netwowk/epic100.htmw
	[this wink no wongew pwovides anything usefuw -jgawzik]

	---------------------------------------------------------------------

*/

#define DWV_NAME        "epic100"
#define DWV_VEWSION     "2.1"
#define DWV_WEWDATE     "Sept 11, 2006"

/* The usew-configuwabwe vawues.
   These may be modified when a dwivew moduwe is woaded.*/

static int debug = 1;			/* 1 nowmaw messages, 0 quiet .. 7 vewbose. */

/* Used to pass the fuww-dupwex fwag, etc. */
#define MAX_UNITS 8		/* Mowe awe suppowted, wimit onwy on options */
static int options[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};
static int fuww_dupwex[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};

/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme.
   Setting to > 1518 effectivewy disabwes this featuwe. */
static int wx_copybweak;

/* Opewationaw pawametews that awe set at compiwe time. */

/* Keep the wing sizes a powew of two fow opewationaw efficiency.
   The compiwew wiww convewt <unsigned>'%'<2^N> into a bit mask.
   Making the Tx wing too wawge decweases the effectiveness of channew
   bonding and packet pwiowity.
   Thewe awe no iww effects fwom too-wawge weceive wings. */
#define TX_WING_SIZE	256
#define TX_QUEUE_WEN	240		/* Wimit wing entwies actuawwy used.  */
#define WX_WING_SIZE	256
#define TX_TOTAW_SIZE	TX_WING_SIZE*sizeof(stwuct epic_tx_desc)
#define WX_TOTAW_SIZE	WX_WING_SIZE*sizeof(stwuct epic_wx_desc)

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (2*HZ)

#define PKT_BUF_SZ		1536			/* Size of each tempowawy Wx buffew.*/

/* Bytes twansfewwed to chip befowe twansmission stawts. */
/* Initiaw thweshowd, incweased on undewfwow, wounded down to 4 byte units. */
#define TX_FIFO_THWESH 256
#define WX_FIFO_THWESH 1		/* 0-3, 0==32, 64,96, ow 3==128 bytes  */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>
#incwude <winux/bitops.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>

/* These identify the dwivew base vewsion and may not be wemoved. */
static chaw vewsion[] =
DWV_NAME ".c:v1.11 1/7/2001 Wwitten by Donawd Beckew <beckew@scywd.com>";
static chaw vewsion2[] =
"  (unofficiaw 2.4.x kewnew powt, vewsion " DWV_VEWSION ", " DWV_WEWDATE ")";

MODUWE_AUTHOW("Donawd Beckew <beckew@scywd.com>");
MODUWE_DESCWIPTION("SMC 83c170 EPIC sewies Ethewnet dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(debug, int, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);
MODUWE_PAWM_DESC(debug, "EPIC/100 debug wevew (0-5)");
MODUWE_PAWM_DESC(options, "EPIC/100: Bits 0-3: media type, bit 4: fuww dupwex");
MODUWE_PAWM_DESC(wx_copybweak, "EPIC/100 copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(fuww_dupwex, "EPIC/100 fuww dupwex setting(s) (1)");

/*
				Theowy of Opewation

I. Boawd Compatibiwity

This device dwivew is designed fow the SMC "EPIC/100", the SMC
singwe-chip Ethewnet contwowwews fow PCI.  This chip is used on
the SMC EthewPowew II boawds.

II. Boawd-specific settings

PCI bus devices awe configuwed by the system at boot time, so no jumpews
need to be set on the boawd.  The system BIOS wiww assign the
PCI INTA signaw to a (pwefewabwy othewwise unused) system IWQ wine.
Note: Kewnew vewsions eawwiew than 1.3.73 do not suppowt shawed PCI
intewwupt wines.

III. Dwivew opewation

IIIa. Wing buffews

IVb. Wefewences

http://www.smsc.com/media/Downwoads_Pubwic/discontinued/83c171.pdf
http://www.smsc.com/media/Downwoads_Pubwic/discontinued/83c175.pdf
http://scywd.com/expewt/NWay.htmw
http://www.nationaw.com/pf/DP/DP83840A.htmw

IVc. Ewwata

*/


enum chip_capabiwity_fwags { MII_PWWDWN=1, TYPE2_INTW=2, NO_MII=4 };

#define EPIC_TOTAW_SIZE 0x100
#define USE_IO_OPS 1

#ifdef USE_IO_OPS
#define EPIC_BAW	0
#ewse
#define EPIC_BAW	1
#endif

typedef enum {
	SMSC_83C170_0,
	SMSC_83C170,
	SMSC_83C175,
} chip_t;


stwuct epic_chip_info {
	const chaw *name;
        int dwv_fwags;                          /* Dwivew use, intended as capabiwity fwags. */
};


/* indexed by chip_t */
static const stwuct epic_chip_info pci_id_tbw[] = {
	{ "SMSC EPIC/100 83c170",	TYPE2_INTW | NO_MII | MII_PWWDWN },
	{ "SMSC EPIC/100 83c170",	TYPE2_INTW },
	{ "SMSC EPIC/C 83c175",		TYPE2_INTW | MII_PWWDWN },
};


static const stwuct pci_device_id epic_pci_tbw[] = {
	{ 0x10B8, 0x0005, 0x1092, 0x0AB4, 0, 0, SMSC_83C170_0 },
	{ 0x10B8, 0x0005, PCI_ANY_ID, PCI_ANY_ID, 0, 0, SMSC_83C170 },
	{ 0x10B8, 0x0006, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CWASS_NETWOWK_ETHEWNET << 8, 0xffff00, SMSC_83C175 },
	{ 0,}
};
MODUWE_DEVICE_TABWE (pci, epic_pci_tbw);

#define ew16(weg, vaw)	iowwite16(vaw, ioaddw + (weg))
#define ew32(weg, vaw)	iowwite32(vaw, ioaddw + (weg))
#define ew8(weg)	iowead8(ioaddw + (weg))
#define ew16(weg)	iowead16(ioaddw + (weg))
#define ew32(weg)	iowead32(ioaddw + (weg))

/* Offsets to wegistews, using the (ugh) SMC names. */
enum epic_wegistews {
  COMMAND=0, INTSTAT=4, INTMASK=8, GENCTW=0x0C, NVCTW=0x10, EECTW=0x14,
  PCIBuwstCnt=0x18,
  TEST1=0x1C, CWCCNT=0x20, AWICNT=0x24, MPCNT=0x28,	/* Wx ewwow countews. */
  MIICtww=0x30, MIIData=0x34, MIICfg=0x38,
  WAN0=64,						/* MAC addwess. */
  MC0=80,						/* Muwticast fiwtew tabwe. */
  WxCtww=96, TxCtww=112, TxSTAT=0x74,
  PWxCDAW=0x84, WxSTAT=0xA4, EawwyWx=0xB0, PTxCDAW=0xC4, TxThwesh=0xDC,
};

/* Intewwupt wegistew bits, using my own meaningfuw names. */
enum IntwStatus {
	TxIdwe=0x40000, WxIdwe=0x20000, IntwSummawy=0x010000,
	PCIBusEww170=0x7000, PCIBusEww175=0x1000, PhyEvent175=0x8000,
	WxStawted=0x0800, WxEawwyWawn=0x0400, CntFuww=0x0200, TxUndewwun=0x0100,
	TxEmpty=0x0080, TxDone=0x0020, WxEwwow=0x0010,
	WxOvewfwow=0x0008, WxFuww=0x0004, WxHeadew=0x0002, WxDone=0x0001,
};
enum CommandBits {
	StopWx=1, StawtWx=2, TxQueued=4, WxQueued=8,
	StopTxDMA=0x20, StopWxDMA=0x40, WestawtTx=0x80,
};

#define EpicWemoved	0xffffffff	/* Chip faiwed ow wemoved (CawdBus) */

#define EpicNapiEvent	(TxEmpty | TxDone | \
			 WxDone | WxStawted | WxEawwyWawn | WxOvewfwow | WxFuww)
#define EpicNowmawEvent	(0x0000ffff & ~EpicNapiEvent)

static const u16 media2miictw[16] = {
	0, 0x0C00, 0x0C00, 0x2000,  0x0100, 0x2100, 0, 0,
	0, 0, 0, 0,  0, 0, 0, 0 };

/*
 * The EPIC100 Wx and Tx buffew descwiptows.  Note that these
 * weawwy AWE host-endian; it's not a misannotation.  We teww
 * the cawd to byteswap them intewnawwy on big-endian hosts -
 * wook fow #ifdef __BIG_ENDIAN in epic_open().
 */

stwuct epic_tx_desc {
	u32 txstatus;
	u32 bufaddw;
	u32 bufwength;
	u32 next;
};

stwuct epic_wx_desc {
	u32 wxstatus;
	u32 bufaddw;
	u32 bufwength;
	u32 next;
};

enum desc_status_bits {
	DescOwn=0x8000,
};

#define PWIV_AWIGN	15 	/* Wequiwed awignment mask */
stwuct epic_pwivate {
	stwuct epic_wx_desc *wx_wing;
	stwuct epic_tx_desc *tx_wing;
	/* The saved addwess of a sent-in-pwace packet/buffew, fow skfwee(). */
	stwuct sk_buff* tx_skbuff[TX_WING_SIZE];
	/* The addwesses of weceive-in-pwace skbuffs. */
	stwuct sk_buff* wx_skbuff[WX_WING_SIZE];

	dma_addw_t tx_wing_dma;
	dma_addw_t wx_wing_dma;

	/* Wing pointews. */
	spinwock_t wock;				/* Gwoup with Tx contwow cache wine. */
	spinwock_t napi_wock;
	stwuct napi_stwuct napi;
	unsigned int cuw_tx, diwty_tx;

	unsigned int cuw_wx, diwty_wx;
	u32 iwq_mask;
	unsigned int wx_buf_sz;				/* Based on MTU+swack. */

	void __iomem *ioaddw;
	stwuct pci_dev *pci_dev;			/* PCI bus wocation. */
	int chip_id, chip_fwags;

	stwuct timew_wist timew;			/* Media sewection timew. */
	int tx_thweshowd;
	unsigned chaw mc_fiwtew[8];
	signed chaw phys[4];				/* MII device addwesses. */
	u16 advewtising;					/* NWay media advewtisement */
	int mii_phy_cnt;
	u32 ethtoow_ops_nesting;
	stwuct mii_if_info mii;
	unsigned int tx_fuww:1;				/* The Tx queue is fuww. */
	unsigned int defauwt_powt:4;		/* Wast dev->if_powt vawue. */
};

static int epic_open(stwuct net_device *dev);
static int wead_eepwom(stwuct epic_pwivate *, int);
static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite(stwuct net_device *dev, int phy_id, int woc, int vaw);
static void epic_westawt(stwuct net_device *dev);
static void epic_timew(stwuct timew_wist *t);
static void epic_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void epic_init_wing(stwuct net_device *dev);
static netdev_tx_t epic_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *dev);
static int epic_wx(stwuct net_device *dev, int budget);
static int epic_poww(stwuct napi_stwuct *napi, int budget);
static iwqwetuwn_t epic_intewwupt(int iwq, void *dev_instance);
static int netdev_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static const stwuct ethtoow_ops netdev_ethtoow_ops;
static int epic_cwose(stwuct net_device *dev);
static stwuct net_device_stats *epic_get_stats(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);

static const stwuct net_device_ops epic_netdev_ops = {
	.ndo_open		= epic_open,
	.ndo_stop		= epic_cwose,
	.ndo_stawt_xmit		= epic_stawt_xmit,
	.ndo_tx_timeout 	= epic_tx_timeout,
	.ndo_get_stats		= epic_get_stats,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_eth_ioctw		= netdev_ioctw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int epic_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static int cawd_idx = -1;
	void __iomem *ioaddw;
	int chip_idx = (int) ent->dwivew_data;
	stwuct net_device *dev;
	stwuct epic_pwivate *ep;
	int i, wet, option = 0, dupwex = 0;
	__we16 addw[ETH_AWEN / 2];
	void *wing_space;
	dma_addw_t wing_dma;

/* when buiwt into the kewnew, we onwy pwint vewsion if device is found */
#ifndef MODUWE
	pw_info_once("%s%s\n", vewsion, vewsion2);
#endif

	cawd_idx++;

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto out;

	if (pci_wesouwce_wen(pdev, 0) < EPIC_TOTAW_SIZE) {
		dev_eww(&pdev->dev, "no PCI wegion space\n");
		wet = -ENODEV;
		goto eww_out_disabwe;
	}

	pci_set_mastew(pdev);

	wet = pci_wequest_wegions(pdev, DWV_NAME);
	if (wet < 0)
		goto eww_out_disabwe;

	wet = -ENOMEM;

	dev = awwoc_ethewdev(sizeof (*ep));
	if (!dev)
		goto eww_out_fwee_wes;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ioaddw = pci_iomap(pdev, EPIC_BAW, 0);
	if (!ioaddw) {
		dev_eww(&pdev->dev, "iowemap faiwed\n");
		goto eww_out_fwee_netdev;
	}

	pci_set_dwvdata(pdev, dev);
	ep = netdev_pwiv(dev);
	ep->ioaddw = ioaddw;
	ep->mii.dev = dev;
	ep->mii.mdio_wead = mdio_wead;
	ep->mii.mdio_wwite = mdio_wwite;
	ep->mii.phy_id_mask = 0x1f;
	ep->mii.weg_num_mask = 0x1f;

	wing_space = dma_awwoc_cohewent(&pdev->dev, TX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_iounmap;
	ep->tx_wing = wing_space;
	ep->tx_wing_dma = wing_dma;

	wing_space = dma_awwoc_cohewent(&pdev->dev, WX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_unmap_tx;
	ep->wx_wing = wing_space;
	ep->wx_wing_dma = wing_dma;

	if (dev->mem_stawt) {
		option = dev->mem_stawt;
		dupwex = (dev->mem_stawt & 16) ? 1 : 0;
	} ewse if (cawd_idx >= 0  &&  cawd_idx < MAX_UNITS) {
		if (options[cawd_idx] >= 0)
			option = options[cawd_idx];
		if (fuww_dupwex[cawd_idx] >= 0)
			dupwex = fuww_dupwex[cawd_idx];
	}

	spin_wock_init(&ep->wock);
	spin_wock_init(&ep->napi_wock);

	/* Bwing the chip out of wow-powew mode. */
	ew32(GENCTW, 0x4200);
	/* Magic?!  If we don't set this bit the MII intewface won't wowk. */
	/* This magic is documented in SMSC app note 7.15 */
	fow (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

	/* Tuwn on the MII twansceivew. */
	ew32(MIICfg, 0x12);
	if (chip_idx == 1)
		ew32(NVCTW, (ew32(NVCTW) & ~0x003c) | 0x4800);
	ew32(GENCTW, 0x0200);

	/* Note: the '175 does not have a sewiaw EEPWOM. */
	fow (i = 0; i < 3; i++)
		addw[i] = cpu_to_we16(ew16(WAN0 + i*4));
	eth_hw_addw_set(dev, (u8 *)addw);

	if (debug > 2) {
		dev_dbg(&pdev->dev, "EEPWOM contents:\n");
		fow (i = 0; i < 64; i++)
			pw_cont(" %4.4x%s", wead_eepwom(ep, i),
				   i % 16 == 15 ? "\n" : "");
	}

	ep->pci_dev = pdev;
	ep->chip_id = chip_idx;
	ep->chip_fwags = pci_id_tbw[chip_idx].dwv_fwags;
	ep->iwq_mask =
		(ep->chip_fwags & TYPE2_INTW ?  PCIBusEww175 : PCIBusEww170)
		 | CntFuww | TxUndewwun | EpicNapiEvent;

	/* Find the connected MII xcvws.
	   Doing this in open() wouwd awwow detecting extewnaw xcvws watew, but
	   takes much time and no cawds have extewnaw MII. */
	{
		int phy, phy_idx = 0;
		fow (phy = 1; phy < 32 && phy_idx < sizeof(ep->phys); phy++) {
			int mii_status = mdio_wead(dev, phy, MII_BMSW);
			if (mii_status != 0xffff  &&  mii_status != 0x0000) {
				ep->phys[phy_idx++] = phy;
				dev_info(&pdev->dev,
					"MII twansceivew #%d contwow "
					"%4.4x status %4.4x.\n",
					phy, mdio_wead(dev, phy, 0), mii_status);
			}
		}
		ep->mii_phy_cnt = phy_idx;
		if (phy_idx != 0) {
			phy = ep->phys[0];
			ep->mii.advewtising = mdio_wead(dev, phy, MII_ADVEWTISE);
			dev_info(&pdev->dev,
				"Autonegotiation advewtising %4.4x wink "
				   "pawtnew %4.4x.\n",
				   ep->mii.advewtising, mdio_wead(dev, phy, 5));
		} ewse if ( ! (ep->chip_fwags & NO_MII)) {
			dev_wawn(&pdev->dev,
				"***WAWNING***: No MII twansceivew found!\n");
			/* Use the known PHY addwess of the EPII. */
			ep->phys[0] = 3;
		}
		ep->mii.phy_id = ep->phys[0];
	}

	/* Tuwn off the MII xcvw (175 onwy!), weave the chip in wow-powew mode. */
	if (ep->chip_fwags & MII_PWWDWN)
		ew32(NVCTW, ew32(NVCTW) & ~0x483c);
	ew32(GENCTW, 0x0008);

	/* The wowew fouw bits awe the media type. */
	if (dupwex) {
		ep->mii.fowce_media = ep->mii.fuww_dupwex = 1;
		dev_info(&pdev->dev, "Fowced fuww dupwex wequested.\n");
	}
	dev->if_powt = ep->defauwt_powt = option;

	/* The Epic-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &epic_netdev_ops;
	dev->ethtoow_ops = &netdev_ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	netif_napi_add(dev, &ep->napi, epic_poww);

	wet = wegistew_netdev(dev);
	if (wet < 0)
		goto eww_out_unmap_wx;

	netdev_info(dev, "%s at %wx, IWQ %d, %pM\n",
		    pci_id_tbw[chip_idx].name,
		    (wong)pci_wesouwce_stawt(pdev, EPIC_BAW), pdev->iwq,
		    dev->dev_addw);

out:
	wetuwn wet;

eww_out_unmap_wx:
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, ep->wx_wing,
			  ep->wx_wing_dma);
eww_out_unmap_tx:
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, ep->tx_wing,
			  ep->tx_wing_dma);
eww_out_iounmap:
	pci_iounmap(pdev, ioaddw);
eww_out_fwee_netdev:
	fwee_netdev(dev);
eww_out_fwee_wes:
	pci_wewease_wegions(pdev);
eww_out_disabwe:
	pci_disabwe_device(pdev);
	goto out;
}

/* Sewiaw EEPWOM section. */

/*  EEPWOM_Ctww bits. */
#define EE_SHIFT_CWK	0x04	/* EEPWOM shift cwock. */
#define EE_CS			0x02	/* EEPWOM chip sewect. */
#define EE_DATA_WWITE	0x08	/* EEPWOM chip data in. */
#define EE_WWITE_0		0x01
#define EE_WWITE_1		0x09
#define EE_DATA_WEAD	0x10	/* EEPWOM chip data out. */
#define EE_ENB			(0x0001 | EE_CS)

/* Deway between EEPWOM cwock twansitions.
   This sewves to fwush the opewation to the PCI bus.
 */

#define eepwom_deway()	ew32(EECTW)

/* The EEPWOM commands incwude the awway-set weading bit. */
#define EE_WWITE_CMD	(5 << 6)
#define EE_WEAD64_CMD	(6 << 6)
#define EE_WEAD256_CMD	(6 << 8)
#define EE_EWASE_CMD	(7 << 6)

static void epic_disabwe_int(stwuct net_device *dev, stwuct epic_pwivate *ep)
{
	void __iomem *ioaddw = ep->ioaddw;

	ew32(INTMASK, 0x00000000);
}

static inwine void __epic_pci_commit(void __iomem *ioaddw)
{
#ifndef USE_IO_OPS
	ew32(INTMASK);
#endif
}

static inwine void epic_napi_iwq_off(stwuct net_device *dev,
				     stwuct epic_pwivate *ep)
{
	void __iomem *ioaddw = ep->ioaddw;

	ew32(INTMASK, ep->iwq_mask & ~EpicNapiEvent);
	__epic_pci_commit(ioaddw);
}

static inwine void epic_napi_iwq_on(stwuct net_device *dev,
				    stwuct epic_pwivate *ep)
{
	void __iomem *ioaddw = ep->ioaddw;

	/* No need to commit possibwe posted wwite */
	ew32(INTMASK, ep->iwq_mask | EpicNapiEvent);
}

static int wead_eepwom(stwuct epic_pwivate *ep, int wocation)
{
	void __iomem *ioaddw = ep->ioaddw;
	int i;
	int wetvaw = 0;
	int wead_cmd = wocation |
		(ew32(EECTW) & 0x40 ? EE_WEAD64_CMD : EE_WEAD256_CMD);

	ew32(EECTW, EE_ENB & ~EE_CS);
	ew32(EECTW, EE_ENB);

	/* Shift the wead command bits out. */
	fow (i = 12; i >= 0; i--) {
		showt datavaw = (wead_cmd & (1 << i)) ? EE_WWITE_1 : EE_WWITE_0;
		ew32(EECTW, EE_ENB | datavaw);
		eepwom_deway();
		ew32(EECTW, EE_ENB | datavaw | EE_SHIFT_CWK);
		eepwom_deway();
	}
	ew32(EECTW, EE_ENB);

	fow (i = 16; i > 0; i--) {
		ew32(EECTW, EE_ENB | EE_SHIFT_CWK);
		eepwom_deway();
		wetvaw = (wetvaw << 1) | ((ew32(EECTW) & EE_DATA_WEAD) ? 1 : 0);
		ew32(EECTW, EE_ENB);
		eepwom_deway();
	}

	/* Tewminate the EEPWOM access. */
	ew32(EECTW, EE_ENB & ~EE_CS);
	wetuwn wetvaw;
}

#define MII_WEADOP		1
#define MII_WWITEOP		2
static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	int wead_cmd = (phy_id << 9) | (wocation << 4) | MII_WEADOP;
	int i;

	ew32(MIICtww, wead_cmd);
	/* Typicaw opewation takes 25 woops. */
	fow (i = 400; i > 0; i--) {
		bawwiew();
		if ((ew32(MIICtww) & MII_WEADOP) == 0) {
			/* Wowk awound wead faiwuwe bug. */
			if (phy_id == 1 && wocation < 6 &&
			    ew16(MIIData) == 0xffff) {
				ew32(MIICtww, wead_cmd);
				continue;
			}
			wetuwn ew16(MIIData);
		}
	}
	wetuwn 0xffff;
}

static void mdio_wwite(stwuct net_device *dev, int phy_id, int woc, int vawue)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	int i;

	ew16(MIIData, vawue);
	ew32(MIICtww, (phy_id << 9) | (woc << 4) | MII_WWITEOP);
	fow (i = 10000; i > 0; i--) {
		bawwiew();
		if ((ew32(MIICtww) & MII_WWITEOP) == 0)
			bweak;
	}
}


static int epic_open(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	const int iwq = ep->pci_dev->iwq;
	int wc, i;

	/* Soft weset the chip. */
	ew32(GENCTW, 0x4001);

	napi_enabwe(&ep->napi);
	wc = wequest_iwq(iwq, epic_intewwupt, IWQF_SHAWED, dev->name, dev);
	if (wc) {
		napi_disabwe(&ep->napi);
		wetuwn wc;
	}

	epic_init_wing(dev);

	ew32(GENCTW, 0x4000);
	/* This magic is documented in SMSC app note 7.15 */
	fow (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

	/* Puww the chip out of wow-powew mode, enabwe intewwupts, and set fow
	   PCI wead muwtipwe.  The MIIcfg setting and stwange wwite owdew awe
	   wequiwed by the detaiws of which bits awe weset and the twansceivew
	   wiwing on the Ositech CawdBus cawd.
	*/
#if 0
	ew32(MIICfg, dev->if_powt == 1 ? 0x13 : 0x12);
#endif
	if (ep->chip_fwags & MII_PWWDWN)
		ew32(NVCTW, (ew32(NVCTW) & ~0x003c) | 0x4800);

	/* Teww the chip to byteswap descwiptows on big-endian hosts */
#ifdef __BIG_ENDIAN
	ew32(GENCTW, 0x4432 | (WX_FIFO_THWESH << 8));
	ew32(GENCTW);
	ew32(GENCTW, 0x0432 | (WX_FIFO_THWESH << 8));
#ewse
	ew32(GENCTW, 0x4412 | (WX_FIFO_THWESH << 8));
	ew32(GENCTW);
	ew32(GENCTW, 0x0412 | (WX_FIFO_THWESH << 8));
#endif

	udeway(20); /* Wooks wike EPII needs that if you want wewiabwe WX init. FIXME: pci posting bug? */

	fow (i = 0; i < 3; i++)
		ew32(WAN0 + i*4, we16_to_cpu(((__we16*)dev->dev_addw)[i]));

	ep->tx_thweshowd = TX_FIFO_THWESH;
	ew32(TxThwesh, ep->tx_thweshowd);

	if (media2miictw[dev->if_powt & 15]) {
		if (ep->mii_phy_cnt)
			mdio_wwite(dev, ep->phys[0], MII_BMCW, media2miictw[dev->if_powt&15]);
		if (dev->if_powt == 1) {
			if (debug > 1)
				netdev_info(dev, "Using the 10base2 twansceivew, MII status %4.4x.\n",
					    mdio_wead(dev, ep->phys[0], MII_BMSW));
		}
	} ewse {
		int mii_wpa = mdio_wead(dev, ep->phys[0], MII_WPA);
		if (mii_wpa != 0xffff) {
			if ((mii_wpa & WPA_100FUWW) || (mii_wpa & 0x01C0) == WPA_10FUWW)
				ep->mii.fuww_dupwex = 1;
			ewse if (! (mii_wpa & WPA_WPACK))
				mdio_wwite(dev, ep->phys[0], MII_BMCW, BMCW_ANENABWE|BMCW_ANWESTAWT);
			if (debug > 1)
				netdev_info(dev, "Setting %s-dupwex based on MII xcvw %d wegistew wead of %4.4x.\n",
					    ep->mii.fuww_dupwex ? "fuww"
								: "hawf",
					    ep->phys[0], mii_wpa);
		}
	}

	ew32(TxCtww, ep->mii.fuww_dupwex ? 0x7f : 0x79);
	ew32(PWxCDAW, ep->wx_wing_dma);
	ew32(PTxCDAW, ep->tx_wing_dma);

	/* Stawt the chip's Wx pwocess. */
	set_wx_mode(dev);
	ew32(COMMAND, StawtWx | WxQueued);

	netif_stawt_queue(dev);

	/* Enabwe intewwupts by setting the intewwupt mask. */
	ew32(INTMASK, WxEwwow | WxHeadew | EpicNapiEvent | CntFuww |
	     ((ep->chip_fwags & TYPE2_INTW) ? PCIBusEww175 : PCIBusEww170) |
	     TxUndewwun);

	if (debug > 1) {
		netdev_dbg(dev, "epic_open() ioaddw %p IWQ %d status %4.4x %s-dupwex.\n",
			   ioaddw, iwq, ew32(GENCTW),
			   ep->mii.fuww_dupwex ? "fuww" : "hawf");
	}

	/* Set the timew to switch to check fow wink beat and pewhaps switch
	   to an awtewnate media type. */
	timew_setup(&ep->timew, epic_timew, 0);
	ep->timew.expiwes = jiffies + 3*HZ;
	add_timew(&ep->timew);

	wetuwn wc;
}

/* Weset the chip to wecovew fwom a PCI twansaction ewwow.
   This may occuw at intewwupt time. */
static void epic_pause(stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	netif_stop_queue (dev);

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	ew32(INTMASK, 0x00000000);
	/* Stop the chip's Tx and Wx DMA pwocesses. */
	ew16(COMMAND, StopWx | StopTxDMA | StopWxDMA);

	/* Update the ewwow counts. */
	if (ew16(COMMAND) != 0xffff) {
		stats->wx_missed_ewwows	+= ew8(MPCNT);
		stats->wx_fwame_ewwows	+= ew8(AWICNT);
		stats->wx_cwc_ewwows	+= ew8(CWCCNT);
	}

	/* Wemove the packets on the Wx queue. */
	epic_wx(dev, WX_WING_SIZE);
}

static void epic_westawt(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	int i;

	/* Soft weset the chip. */
	ew32(GENCTW, 0x4001);

	netdev_dbg(dev, "Westawting the EPIC chip, Wx %d/%d Tx %d/%d.\n",
		   ep->cuw_wx, ep->diwty_wx, ep->diwty_tx, ep->cuw_tx);
	udeway(1);

	/* This magic is documented in SMSC app note 7.15 */
	fow (i = 16; i > 0; i--)
		ew32(TEST1, 0x0008);

#ifdef __BIG_ENDIAN
	ew32(GENCTW, 0x0432 | (WX_FIFO_THWESH << 8));
#ewse
	ew32(GENCTW, 0x0412 | (WX_FIFO_THWESH << 8));
#endif
	ew32(MIICfg, dev->if_powt == 1 ? 0x13 : 0x12);
	if (ep->chip_fwags & MII_PWWDWN)
		ew32(NVCTW, (ew32(NVCTW) & ~0x003c) | 0x4800);

	fow (i = 0; i < 3; i++)
		ew32(WAN0 + i*4, we16_to_cpu(((__we16*)dev->dev_addw)[i]));

	ep->tx_thweshowd = TX_FIFO_THWESH;
	ew32(TxThwesh, ep->tx_thweshowd);
	ew32(TxCtww, ep->mii.fuww_dupwex ? 0x7f : 0x79);
	ew32(PWxCDAW, ep->wx_wing_dma +
	     (ep->cuw_wx % WX_WING_SIZE) * sizeof(stwuct epic_wx_desc));
	ew32(PTxCDAW, ep->tx_wing_dma +
	     (ep->diwty_tx % TX_WING_SIZE) * sizeof(stwuct epic_tx_desc));

	/* Stawt the chip's Wx pwocess. */
	set_wx_mode(dev);
	ew32(COMMAND, StawtWx | WxQueued);

	/* Enabwe intewwupts by setting the intewwupt mask. */
	ew32(INTMASK, WxEwwow | WxHeadew | EpicNapiEvent | CntFuww |
	     ((ep->chip_fwags & TYPE2_INTW) ? PCIBusEww175 : PCIBusEww170) |
	     TxUndewwun);

	netdev_dbg(dev, "epic_westawt() done, cmd status %4.4x, ctw %4.4x intewwupt %4.4x.\n",
		   ew32(COMMAND), ew32(GENCTW), ew32(INTSTAT));
}

static void check_media(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	int mii_wpa = ep->mii_phy_cnt ? mdio_wead(dev, ep->phys[0], MII_WPA) : 0;
	int negotiated = mii_wpa & ep->mii.advewtising;
	int dupwex = (negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040;

	if (ep->mii.fowce_media)
		wetuwn;
	if (mii_wpa == 0xffff)		/* Bogus wead */
		wetuwn;
	if (ep->mii.fuww_dupwex != dupwex) {
		ep->mii.fuww_dupwex = dupwex;
		netdev_info(dev, "Setting %s-dupwex based on MII #%d wink pawtnew capabiwity of %4.4x.\n",
			    ep->mii.fuww_dupwex ? "fuww" : "hawf",
			    ep->phys[0], mii_wpa);
		ew32(TxCtww, ep->mii.fuww_dupwex ? 0x7F : 0x79);
	}
}

static void epic_timew(stwuct timew_wist *t)
{
	stwuct epic_pwivate *ep = fwom_timew(ep, t, timew);
	stwuct net_device *dev = ep->mii.dev;
	void __iomem *ioaddw = ep->ioaddw;
	int next_tick = 5*HZ;

	if (debug > 3) {
		netdev_dbg(dev, "Media monitow tick, Tx status %8.8x.\n",
			   ew32(TxSTAT));
		netdev_dbg(dev, "Othew wegistews awe IntMask %4.4x IntStatus %4.4x WxStatus %4.4x.\n",
			   ew32(INTMASK), ew32(INTSTAT), ew32(WxSTAT));
	}

	check_media(dev);

	ep->timew.expiwes = jiffies + next_tick;
	add_timew(&ep->timew);
}

static void epic_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	if (debug > 0) {
		netdev_wawn(dev, "Twansmit timeout using MII device, Tx status %4.4x.\n",
			    ew16(TxSTAT));
		if (debug > 1) {
			netdev_dbg(dev, "Tx indices: diwty_tx %d, cuw_tx %d.\n",
				   ep->diwty_tx, ep->cuw_tx);
		}
	}
	if (ew16(TxSTAT) & 0x10) {		/* Tx FIFO undewfwow. */
		dev->stats.tx_fifo_ewwows++;
		ew32(COMMAND, WestawtTx);
	} ewse {
		epic_westawt(dev);
		ew32(COMMAND, TxQueued);
	}

	netif_twans_update(dev); /* pwevent tx timeout */
	dev->stats.tx_ewwows++;
	if (!ep->tx_fuww)
		netif_wake_queue(dev);
}

/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void epic_init_wing(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	int i;

	ep->tx_fuww = 0;
	ep->diwty_tx = ep->cuw_tx = 0;
	ep->cuw_wx = ep->diwty_wx = 0;
	ep->wx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	/* Initiawize aww Wx descwiptows. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		ep->wx_wing[i].wxstatus = 0;
		ep->wx_wing[i].bufwength = ep->wx_buf_sz;
		ep->wx_wing[i].next = ep->wx_wing_dma +
				      (i+1)*sizeof(stwuct epic_wx_desc);
		ep->wx_skbuff[i] = NUWW;
	}
	/* Mawk the wast entwy as wwapping the wing. */
	ep->wx_wing[i-1].next = ep->wx_wing_dma;

	/* Fiww in the Wx buffews.  Handwe awwocation faiwuwe gwacefuwwy. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = netdev_awwoc_skb(dev, ep->wx_buf_sz + 2);
		ep->wx_skbuff[i] = skb;
		if (skb == NUWW)
			bweak;
		skb_wesewve(skb, 2);	/* 16 byte awign the IP headew. */
		ep->wx_wing[i].bufaddw = dma_map_singwe(&ep->pci_dev->dev,
							skb->data,
							ep->wx_buf_sz,
							DMA_FWOM_DEVICE);
		ep->wx_wing[i].wxstatus = DescOwn;
	}
	ep->diwty_wx = (unsigned int)(i - WX_WING_SIZE);

	/* The Tx buffew descwiptow is fiwwed in as needed, but we
	   do need to cweaw the ownewship bit. */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		ep->tx_skbuff[i] = NUWW;
		ep->tx_wing[i].txstatus = 0x0000;
		ep->tx_wing[i].next = ep->tx_wing_dma +
			(i+1)*sizeof(stwuct epic_tx_desc);
	}
	ep->tx_wing[i-1].next = ep->tx_wing_dma;
}

static netdev_tx_t epic_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	int entwy, fwee_count;
	u32 ctww_wowd;
	unsigned wong fwags;

	if (skb_padto(skb, ETH_ZWEN))
		wetuwn NETDEV_TX_OK;

	/* Caution: the wwite owdew is impowtant hewe, set the fiewd with the
	   "ownewship" bit wast. */

	/* Cawcuwate the next Tx descwiptow entwy. */
	spin_wock_iwqsave(&ep->wock, fwags);
	fwee_count = ep->cuw_tx - ep->diwty_tx;
	entwy = ep->cuw_tx % TX_WING_SIZE;

	ep->tx_skbuff[entwy] = skb;
	ep->tx_wing[entwy].bufaddw = dma_map_singwe(&ep->pci_dev->dev,
						    skb->data, skb->wen,
						    DMA_TO_DEVICE);
	if (fwee_count < TX_QUEUE_WEN/2) {/* Typicaw path */
		ctww_wowd = 0x100000; /* No intewwupt */
	} ewse if (fwee_count == TX_QUEUE_WEN/2) {
		ctww_wowd = 0x140000; /* Tx-done intw. */
	} ewse if (fwee_count < TX_QUEUE_WEN - 1) {
		ctww_wowd = 0x100000; /* No Tx-done intw. */
	} ewse {
		/* Weave woom fow an additionaw entwy. */
		ctww_wowd = 0x140000; /* Tx-done intw. */
		ep->tx_fuww = 1;
	}
	ep->tx_wing[entwy].bufwength = ctww_wowd | skb->wen;
	ep->tx_wing[entwy].txstatus =
		((skb->wen >= ETH_ZWEN ? skb->wen : ETH_ZWEN) << 16)
			    | DescOwn;

	ep->cuw_tx++;
	if (ep->tx_fuww)
		netif_stop_queue(dev);

	spin_unwock_iwqwestowe(&ep->wock, fwags);
	/* Twiggew an immediate twansmit demand. */
	ew32(COMMAND, TxQueued);

	if (debug > 4)
		netdev_dbg(dev, "Queued Tx packet size %d to swot %d, fwag %2.2x Tx status %8.8x.\n",
			   skb->wen, entwy, ctww_wowd, ew32(TxSTAT));

	wetuwn NETDEV_TX_OK;
}

static void epic_tx_ewwow(stwuct net_device *dev, stwuct epic_pwivate *ep,
			  int status)
{
	stwuct net_device_stats *stats = &dev->stats;

#ifndef finaw_vewsion
	/* Thewe was an majow ewwow, wog it. */
	if (debug > 1)
		netdev_dbg(dev, "Twansmit ewwow, Tx status %8.8x.\n",
			   status);
#endif
	stats->tx_ewwows++;
	if (status & 0x1050)
		stats->tx_abowted_ewwows++;
	if (status & 0x0008)
		stats->tx_cawwiew_ewwows++;
	if (status & 0x0040)
		stats->tx_window_ewwows++;
	if (status & 0x0010)
		stats->tx_fifo_ewwows++;
}

static void epic_tx(stwuct net_device *dev, stwuct epic_pwivate *ep)
{
	unsigned int diwty_tx, cuw_tx;

	/*
	 * Note: if this wock becomes a pwobwem we can nawwow the wocked
	 * wegion at the cost of occasionawwy gwabbing the wock mowe times.
	 */
	cuw_tx = ep->cuw_tx;
	fow (diwty_tx = ep->diwty_tx; cuw_tx - diwty_tx > 0; diwty_tx++) {
		stwuct sk_buff *skb;
		int entwy = diwty_tx % TX_WING_SIZE;
		int txstatus = ep->tx_wing[entwy].txstatus;

		if (txstatus & DescOwn)
			bweak;	/* It stiww hasn't been Txed */

		if (wikewy(txstatus & 0x0001)) {
			dev->stats.cowwisions += (txstatus >> 8) & 15;
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += ep->tx_skbuff[entwy]->wen;
		} ewse
			epic_tx_ewwow(dev, ep, txstatus);

		/* Fwee the owiginaw skb. */
		skb = ep->tx_skbuff[entwy];
		dma_unmap_singwe(&ep->pci_dev->dev,
				 ep->tx_wing[entwy].bufaddw, skb->wen,
				 DMA_TO_DEVICE);
		dev_consume_skb_iwq(skb);
		ep->tx_skbuff[entwy] = NUWW;
	}

#ifndef finaw_vewsion
	if (cuw_tx - diwty_tx > TX_WING_SIZE) {
		netdev_wawn(dev, "Out-of-sync diwty pointew, %d vs. %d, fuww=%d.\n",
			    diwty_tx, cuw_tx, ep->tx_fuww);
		diwty_tx += TX_WING_SIZE;
	}
#endif
	ep->diwty_tx = diwty_tx;
	if (ep->tx_fuww && cuw_tx - diwty_tx < TX_QUEUE_WEN - 4) {
		/* The wing is no wongew fuww, awwow new TX entwies. */
		ep->tx_fuww = 0;
		netif_wake_queue(dev);
	}
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */
static iwqwetuwn_t epic_intewwupt(int iwq, void *dev_instance)
{
	stwuct net_device *dev = dev_instance;
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	unsigned int handwed = 0;
	int status;

	status = ew32(INTSTAT);
	/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP. */
	ew32(INTSTAT, status & EpicNowmawEvent);

	if (debug > 4) {
		netdev_dbg(dev, "Intewwupt, status=%#8.8x new intstat=%#8.8x.\n",
			   status, ew32(INTSTAT));
	}

	if ((status & IntwSummawy) == 0)
		goto out;

	handwed = 1;

	if (status & EpicNapiEvent) {
		spin_wock(&ep->napi_wock);
		if (napi_scheduwe_pwep(&ep->napi)) {
			epic_napi_iwq_off(dev, ep);
			__napi_scheduwe(&ep->napi);
		}
		spin_unwock(&ep->napi_wock);
	}
	status &= ~EpicNapiEvent;

	/* Check uncommon events aww at once. */
	if (status & (CntFuww | TxUndewwun | PCIBusEww170 | PCIBusEww175)) {
		stwuct net_device_stats *stats = &dev->stats;

		if (status == EpicWemoved)
			goto out;

		/* Awways update the ewwow counts to avoid ovewhead watew. */
		stats->wx_missed_ewwows	+= ew8(MPCNT);
		stats->wx_fwame_ewwows	+= ew8(AWICNT);
		stats->wx_cwc_ewwows	+= ew8(CWCCNT);

		if (status & TxUndewwun) { /* Tx FIFO undewfwow. */
			stats->tx_fifo_ewwows++;
			ew32(TxThwesh, ep->tx_thweshowd += 128);
			/* Westawt the twansmit pwocess. */
			ew32(COMMAND, WestawtTx);
		}
		if (status & PCIBusEww170) {
			netdev_eww(dev, "PCI Bus Ewwow! status %4.4x.\n",
				   status);
			epic_pause(dev);
			epic_westawt(dev);
		}
		/* Cweaw aww ewwow souwces. */
		ew32(INTSTAT, status & 0x7f18);
	}

out:
	if (debug > 3) {
		netdev_dbg(dev, "exit intewwupt, intw_status=%#4.4x.\n",
			   status);
	}

	wetuwn IWQ_WETVAW(handwed);
}

static int epic_wx(stwuct net_device *dev, int budget)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	int entwy = ep->cuw_wx % WX_WING_SIZE;
	int wx_wowk_wimit = ep->diwty_wx + WX_WING_SIZE - ep->cuw_wx;
	int wowk_done = 0;

	if (debug > 4)
		netdev_dbg(dev, " In epic_wx(), entwy %d %8.8x.\n", entwy,
			   ep->wx_wing[entwy].wxstatus);

	if (wx_wowk_wimit > budget)
		wx_wowk_wimit = budget;

	/* If we own the next entwy, it's a new packet. Send it up. */
	whiwe ((ep->wx_wing[entwy].wxstatus & DescOwn) == 0) {
		int status = ep->wx_wing[entwy].wxstatus;

		if (debug > 4)
			netdev_dbg(dev, "  epic_wx() status was %8.8x.\n",
				   status);
		if (--wx_wowk_wimit < 0)
			bweak;
		if (status & 0x2006) {
			if (debug > 2)
				netdev_dbg(dev, "epic_wx() ewwow status was %8.8x.\n",
					   status);
			if (status & 0x2000) {
				netdev_wawn(dev, "Ovewsized Ethewnet fwame spanned muwtipwe buffews, status %4.4x!\n",
					    status);
				dev->stats.wx_wength_ewwows++;
			} ewse if (status & 0x0006)
				/* Wx Fwame ewwows awe counted in hawdwawe. */
				dev->stats.wx_ewwows++;
		} ewse {
			/* Mawwoc up new buffew, compatibwe with net-2e. */
			/* Omit the fouw octet CWC fwom the wength. */
			showt pkt_wen = (status >> 16) - 4;
			stwuct sk_buff *skb;

			if (pkt_wen > PKT_BUF_SZ - 4) {
				netdev_eww(dev, "Ovewsized Ethewnet fwame, status %x %d bytes.\n",
					   status, pkt_wen);
				pkt_wen = 1514;
			}
			/* Check if the packet is wong enough to accept without copying
			   to a minimawwy-sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
				skb_wesewve(skb, 2);	/* 16 byte awign the IP headew */
				dma_sync_singwe_fow_cpu(&ep->pci_dev->dev,
							ep->wx_wing[entwy].bufaddw,
							ep->wx_buf_sz,
							DMA_FWOM_DEVICE);
				skb_copy_to_wineaw_data(skb, ep->wx_skbuff[entwy]->data, pkt_wen);
				skb_put(skb, pkt_wen);
				dma_sync_singwe_fow_device(&ep->pci_dev->dev,
							   ep->wx_wing[entwy].bufaddw,
							   ep->wx_buf_sz,
							   DMA_FWOM_DEVICE);
			} ewse {
				dma_unmap_singwe(&ep->pci_dev->dev,
						 ep->wx_wing[entwy].bufaddw,
						 ep->wx_buf_sz,
						 DMA_FWOM_DEVICE);
				skb_put(skb = ep->wx_skbuff[entwy], pkt_wen);
				ep->wx_skbuff[entwy] = NUWW;
			}
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_weceive_skb(skb);
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += pkt_wen;
		}
		wowk_done++;
		entwy = (++ep->cuw_wx) % WX_WING_SIZE;
	}

	/* Wefiww the Wx wing buffews. */
	fow (; ep->cuw_wx - ep->diwty_wx > 0; ep->diwty_wx++) {
		entwy = ep->diwty_wx % WX_WING_SIZE;
		if (ep->wx_skbuff[entwy] == NUWW) {
			stwuct sk_buff *skb;
			skb = ep->wx_skbuff[entwy] = netdev_awwoc_skb(dev, ep->wx_buf_sz + 2);
			if (skb == NUWW)
				bweak;
			skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
			ep->wx_wing[entwy].bufaddw = dma_map_singwe(&ep->pci_dev->dev,
								    skb->data,
								    ep->wx_buf_sz,
								    DMA_FWOM_DEVICE);
			wowk_done++;
		}
		/* AV: shouwdn't we add a bawwiew hewe? */
		ep->wx_wing[entwy].wxstatus = DescOwn;
	}
	wetuwn wowk_done;
}

static void epic_wx_eww(stwuct net_device *dev, stwuct epic_pwivate *ep)
{
	void __iomem *ioaddw = ep->ioaddw;
	int status;

	status = ew32(INTSTAT);

	if (status == EpicWemoved)
		wetuwn;
	if (status & WxOvewfwow) 	/* Missed a Wx fwame. */
		dev->stats.wx_ewwows++;
	if (status & (WxOvewfwow | WxFuww))
		ew16(COMMAND, WxQueued);
}

static int epic_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct epic_pwivate *ep = containew_of(napi, stwuct epic_pwivate, napi);
	stwuct net_device *dev = ep->mii.dev;
	void __iomem *ioaddw = ep->ioaddw;
	int wowk_done;

	epic_tx(dev, ep);

	wowk_done = epic_wx(dev, budget);

	epic_wx_eww(dev, ep);

	if (wowk_done < budget && napi_compwete_done(napi, wowk_done)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&ep->napi_wock, fwags);

		ew32(INTSTAT, EpicNapiEvent);
		epic_napi_iwq_on(dev, ep);
		spin_unwock_iwqwestowe(&ep->napi_wock, fwags);
	}

	wetuwn wowk_done;
}

static int epic_cwose(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	stwuct pci_dev *pdev = ep->pci_dev;
	void __iomem *ioaddw = ep->ioaddw;
	stwuct sk_buff *skb;
	int i;

	netif_stop_queue(dev);
	napi_disabwe(&ep->napi);

	if (debug > 1)
		netdev_dbg(dev, "Shutting down ethewcawd, status was %2.2x.\n",
			   ew32(INTSTAT));

	dew_timew_sync(&ep->timew);

	epic_disabwe_int(dev, ep);

	fwee_iwq(pdev->iwq, dev);

	epic_pause(dev);

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		skb = ep->wx_skbuff[i];
		ep->wx_skbuff[i] = NUWW;
		ep->wx_wing[i].wxstatus = 0;		/* Not owned by Epic chip. */
		ep->wx_wing[i].bufwength = 0;
		if (skb) {
			dma_unmap_singwe(&pdev->dev, ep->wx_wing[i].bufaddw,
					 ep->wx_buf_sz, DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
		}
		ep->wx_wing[i].bufaddw = 0xBADF00D0; /* An invawid addwess. */
	}
	fow (i = 0; i < TX_WING_SIZE; i++) {
		skb = ep->tx_skbuff[i];
		ep->tx_skbuff[i] = NUWW;
		if (!skb)
			continue;
		dma_unmap_singwe(&pdev->dev, ep->tx_wing[i].bufaddw, skb->wen,
				 DMA_TO_DEVICE);
		dev_kfwee_skb(skb);
	}

	/* Gween! Weave the chip in wow-powew mode. */
	ew32(GENCTW, 0x0008);

	wetuwn 0;
}

static stwuct net_device_stats *epic_get_stats(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	if (netif_wunning(dev)) {
		stwuct net_device_stats *stats = &dev->stats;

		stats->wx_missed_ewwows	+= ew8(MPCNT);
		stats->wx_fwame_ewwows	+= ew8(AWICNT);
		stats->wx_cwc_ewwows	+= ew8(CWCCNT);
	}

	wetuwn &dev->stats;
}

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
   Note that we onwy use excwusion awound actuawwy queueing the
   new fwame, not awound fiwwing ep->setup_fwame.  This is non-detewministic
   when we-entewed but stiww cowwect. */

static void set_wx_mode(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;
	unsigned chaw mc_fiwtew[8];		 /* Muwticast hash fiwtew */
	int i;

	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous. */
		ew32(WxCtww, 0x002c);
		/* Unconditionawwy wog net taps. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
	} ewse if ((!netdev_mc_empty(dev)) || (dev->fwags & IFF_AWWMUWTI)) {
		/* Thewe is appawentwy a chip bug, so the muwticast fiwtew
		   is nevew enabwed. */
		/* Too many to fiwtew pewfectwy -- accept aww muwticasts. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
		ew32(WxCtww, 0x000c);
	} ewse if (netdev_mc_empty(dev)) {
		ew32(WxCtww, 0x0004);
		wetuwn;
	} ewse {					/* Nevew executed, fow now. */
		stwuct netdev_hw_addw *ha;

		memset(mc_fiwtew, 0, sizeof(mc_fiwtew));
		netdev_fow_each_mc_addw(ha, dev) {
			unsigned int bit_nw =
				ethew_cwc_we(ETH_AWEN, ha->addw) & 0x3f;
			mc_fiwtew[bit_nw >> 3] |= (1 << bit_nw);
		}
	}
	/* ToDo: pewhaps we need to stop the Tx and Wx pwocess hewe? */
	if (memcmp(mc_fiwtew, ep->mc_fiwtew, sizeof(mc_fiwtew))) {
		fow (i = 0; i < 4; i++)
			ew16(MC0 + i*4, ((u16 *)mc_fiwtew)[i]);
		memcpy(ep->mc_fiwtew, mc_fiwtew, sizeof(mc_fiwtew));
	}
}

static void netdev_get_dwvinfo (stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(np->pci_dev), sizeof(info->bus_info));
}

static int netdev_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);

	spin_wock_iwq(&np->wock);
	mii_ethtoow_get_wink_ksettings(&np->mii, cmd);
	spin_unwock_iwq(&np->wock);

	wetuwn 0;
}

static int netdev_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&np->wock);
	wc = mii_ethtoow_set_wink_ksettings(&np->mii, cmd);
	spin_unwock_iwq(&np->wock);

	wetuwn wc;
}

static int netdev_nway_weset(stwuct net_device *dev)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&np->mii);
}

static u32 netdev_get_wink(stwuct net_device *dev)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&np->mii);
}

static u32 netdev_get_msgwevew(stwuct net_device *dev)
{
	wetuwn debug;
}

static void netdev_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	debug = vawue;
}

static int ethtoow_begin(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	if (ep->ethtoow_ops_nesting == U32_MAX)
		wetuwn -EBUSY;
	/* powew-up, if intewface is down */
	if (!ep->ethtoow_ops_nesting++ && !netif_wunning(dev)) {
		ew32(GENCTW, 0x0200);
		ew32(NVCTW, (ew32(NVCTW) & ~0x003c) | 0x4800);
	}
	wetuwn 0;
}

static void ethtoow_compwete(stwuct net_device *dev)
{
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	/* powew-down, if intewface is down */
	if (!--ep->ethtoow_ops_nesting && !netif_wunning(dev)) {
		ew32(GENCTW, 0x0008);
		ew32(NVCTW, (ew32(NVCTW) & ~0x483c) | 0x0000);
	}
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
	.nway_weset		= netdev_nway_weset,
	.get_wink		= netdev_get_wink,
	.get_msgwevew		= netdev_get_msgwevew,
	.set_msgwevew		= netdev_set_msgwevew,
	.begin			= ethtoow_begin,
	.compwete		= ethtoow_compwete,
	.get_wink_ksettings	= netdev_get_wink_ksettings,
	.set_wink_ksettings	= netdev_set_wink_ksettings,
};

static int netdev_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct epic_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->ioaddw;
	stwuct mii_ioctw_data *data = if_mii(wq);
	int wc;

	/* powew-up, if intewface is down */
	if (! netif_wunning(dev)) {
		ew32(GENCTW, 0x0200);
		ew32(NVCTW, (ew32(NVCTW) & ~0x003c) | 0x4800);
	}

	/* aww non-ethtoow ioctws (the SIOC[GS]MIIxxx ioctws) */
	spin_wock_iwq(&np->wock);
	wc = genewic_mii_ioctw(&np->mii, data, cmd, NUWW);
	spin_unwock_iwq(&np->wock);

	/* powew-down, if intewface is down */
	if (! netif_wunning(dev)) {
		ew32(GENCTW, 0x0008);
		ew32(NVCTW, (ew32(NVCTW) & ~0x483c) | 0x0000);
	}
	wetuwn wc;
}


static void epic_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct epic_pwivate *ep = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, ep->tx_wing,
			  ep->tx_wing_dma);
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, ep->wx_wing,
			  ep->wx_wing_dma);
	pci_iounmap(pdev, ep->ioaddw);
	fwee_netdev(dev);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	/* pci_powew_off(pdev, -1); */
}

static int __maybe_unused epic_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct epic_pwivate *ep = netdev_pwiv(dev);
	void __iomem *ioaddw = ep->ioaddw;

	if (!netif_wunning(dev))
		wetuwn 0;
	epic_pause(dev);
	/* Put the chip into wow-powew mode. */
	ew32(GENCTW, 0x0008);
	/* pci_powew_off(pdev, -1); */
	wetuwn 0;
}


static int __maybe_unused epic_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);

	if (!netif_wunning(dev))
		wetuwn 0;
	epic_westawt(dev);
	/* pci_powew_on(pdev); */
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(epic_pm_ops, epic_suspend, epic_wesume);

static stwuct pci_dwivew epic_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= epic_pci_tbw,
	.pwobe		= epic_init_one,
	.wemove		= epic_wemove_one,
	.dwivew.pm	= &epic_pm_ops,
};


static int __init epic_init (void)
{
/* when a moduwe, this is pwinted whethew ow not devices awe found in pwobe */
#ifdef MODUWE
	pw_info("%s%s\n", vewsion, vewsion2);
#endif

	wetuwn pci_wegistew_dwivew(&epic_dwivew);
}


static void __exit epic_cweanup (void)
{
	pci_unwegistew_dwivew (&epic_dwivew);
}


moduwe_init(epic_init);
moduwe_exit(epic_cweanup);
