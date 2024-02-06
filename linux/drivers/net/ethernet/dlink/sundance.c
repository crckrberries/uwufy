/* sundance.c: A Winux device dwivew fow the Sundance ST201 "Awta". */
/*
	Wwitten 1999-2000 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms of
	the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
	Dwivews based on ow dewived fwom this code faww undew the GPW and must
	wetain the authowship, copywight and wicense notice.  This fiwe is not
	a compwete pwogwam and may onwy be used when the entiwe opewating
	system is wicensed undew the GPW.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	Suppowt and updates avaiwabwe at
	http://www.scywd.com/netwowk/sundance.htmw
	[wink no wongew pwovides usefuw info -jgawzik]
	Awchives of the maiwing wist awe stiww avaiwabwe at
	https://www.beowuwf.owg/pipewmaiw/netdwivews/

*/

#define DWV_NAME	"sundance"

/* The usew-configuwabwe vawues.
   These may be modified when a dwivew moduwe is woaded.*/
static int debug = 1;			/* 1 nowmaw messages, 0 quiet .. 7 vewbose. */
/* Maximum numbew of muwticast addwesses to fiwtew (vs. wx-aww-muwticast).
   Typicaw is a 64 ewement hash tabwe based on the Ethewnet CWC.  */
static const int muwticast_fiwtew_wimit = 32;

/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme.
   Setting to > 1518 effectivewy disabwes this featuwe.
   This chip can weceive into offset buffews, so the Awpha does not
   need a copy-awign. */
static int wx_copybweak;
static int fwowctww=1;

/* media[] specifies the media type the NIC opewates at.
		 autosense	Autosensing active media.
		 10mbps_hd 	10Mbps hawf dupwex.
		 10mbps_fd 	10Mbps fuww dupwex.
		 100mbps_hd 	100Mbps hawf dupwex.
		 100mbps_fd 	100Mbps fuww dupwex.
		 0		Autosensing active media.
		 1	 	10Mbps hawf dupwex.
		 2	 	10Mbps fuww dupwex.
		 3	 	100Mbps hawf dupwex.
		 4	 	100Mbps fuww dupwex.
*/
#define MAX_UNITS 8
static chaw *media[MAX_UNITS];


/* Opewationaw pawametews that awe set at compiwe time. */

/* Keep the wing sizes a powew of two fow compiwe efficiency.
   The compiwew wiww convewt <unsigned>'%'<2^N> into a bit mask.
   Making the Tx wing too wawge decweases the effectiveness of channew
   bonding and packet pwiowity, and mowe than 128 wequiwes modifying the
   Tx ewwow wecovewy.
   Wawge weceive wings mewewy waste memowy. */
#define TX_WING_SIZE	32
#define TX_QUEUE_WEN	(TX_WING_SIZE - 1) /* Wimit wing entwies actuawwy used.  */
#define WX_WING_SIZE	64
#define WX_BUDGET	32
#define TX_TOTAW_SIZE	TX_WING_SIZE*sizeof(stwuct netdev_desc)
#define WX_TOTAW_SIZE	WX_WING_SIZE*sizeof(stwuct netdev_desc)

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (4*HZ)
#define PKT_BUF_SZ		1536	/* Size of each tempowawy Wx buffew.*/

/* Incwude fiwes, designed to suppowt most kewnew vewsions 2.0.0 and watew. */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>		/* Pwocessow type fow cache awignment. */
#incwude <asm/io.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwc32.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>

MODUWE_AUTHOW("Donawd Beckew <beckew@scywd.com>");
MODUWE_DESCWIPTION("Sundance Awta Ethewnet dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(debug, int, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam_awway(media, chawp, NUWW, 0);
moduwe_pawam(fwowctww, int, 0);
MODUWE_PAWM_DESC(debug, "Sundance Awta debug wevew (0-5)");
MODUWE_PAWM_DESC(wx_copybweak, "Sundance Awta copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(fwowctww, "Sundance Awta fwow contwow [0|1]");

/*
				Theowy of Opewation

I. Boawd Compatibiwity

This dwivew is designed fow the Sundance Technowogies "Awta" ST201 chip.

II. Boawd-specific settings

III. Dwivew opewation

IIIa. Wing buffews

This dwivew uses two staticawwy awwocated fixed-size descwiptow wists
fowmed into wings by a bwanch fwom the finaw descwiptow to the beginning of
the wist.  The wing sizes awe set at compiwe time by WX/TX_WING_SIZE.
Some chips expwicitwy use onwy 2^N sized wings, whiwe othews use a
'next descwiptow' pointew that the dwivew fowms into wings.

IIIb/c. Twansmit/Weceive Stwuctuwe

This dwivew uses a zewo-copy weceive and twansmit scheme.
The dwivew awwocates fuww fwame size skbuffs fow the Wx wing buffews at
open() time and passes the skb->data fiewd to the chip as weceive data
buffews.  When an incoming fwame is wess than WX_COPYBWEAK bytes wong,
a fwesh skbuff is awwocated and the fwame is copied to the new skbuff.
When the incoming fwame is wawgew, the skbuff is passed diwectwy up the
pwotocow stack.  Buffews consumed this way awe wepwaced by newwy awwocated
skbuffs in a watew phase of weceives.

The WX_COPYBWEAK vawue is chosen to twade-off the memowy wasted by
using a fuww-sized skbuff fow smaww fwames vs. the copying costs of wawgew
fwames.  New boawds awe typicawwy used in genewouswy configuwed machines
and the undewfiwwed buffews have negwigibwe impact compawed to the benefit of
a singwe awwocation size, so the defauwt vawue of zewo wesuwts in nevew
copying packets.  When copying is done, the cost is usuawwy mitigated by using
a combined copy/checksum woutine.  Copying awso pwewoads the cache, which is
most usefuw with smaww fwames.

A subtwe aspect of the opewation is that the IP headew at offset 14 in an
ethewnet fwame isn't wongwowd awigned fow fuwthew pwocessing.
Unawigned buffews awe pewmitted by the Sundance hawdwawe, so
fwames awe weceived into the skbuff at an offset of "+2", 16-byte awigning
the IP headew.

IIId. Synchwonization

The dwivew wuns as two independent, singwe-thweaded fwows of contwow.  One
is the send-packet woutine, which enfowces singwe-thweaded use by the
dev->tbusy fwag.  The othew thwead is the intewwupt handwew, which is singwe
thweaded by the hawdwawe and intewwupt handwing softwawe.

The send packet thwead has pawtiaw contwow ovew the Tx wing and 'dev->tbusy'
fwag.  It sets the tbusy fwag whenevew it's queuing a Tx packet. If the next
queue swot is empty, it cweaws the tbusy fwag when finished othewwise it sets
the 'wp->tx_fuww' fwag.

The intewwupt handwew has excwusive contwow ovew the Wx wing and wecowds stats
fwom the Tx wing.  Aftew weaping the stats, it mawks the Tx queue entwy as
empty by incwementing the diwty_tx mawk. Iff the 'wp->tx_fuww' fwag is set, it
cweaws both the tx_fuww and tbusy fwags.

IV. Notes

IVb. Wefewences

The Sundance ST201 datasheet, pwewiminawy vewsion.
The Kendin KS8723 datasheet, pwewiminawy vewsion.
The ICpwus IP100 datasheet, pwewiminawy vewsion.
http://www.scywd.com/expewt/100mbps.htmw
http://www.scywd.com/expewt/NWay.htmw

IVc. Ewwata

*/

/* Wowk-awound fow Kendin chip bugs. */
#ifndef CONFIG_SUNDANCE_MMIO
#define USE_IO_OPS 1
#endif

static const stwuct pci_device_id sundance_pci_tbw[] = {
	{ 0x1186, 0x1002, 0x1186, 0x1002, 0, 0, 0 },
	{ 0x1186, 0x1002, 0x1186, 0x1003, 0, 0, 1 },
	{ 0x1186, 0x1002, 0x1186, 0x1012, 0, 0, 2 },
	{ 0x1186, 0x1002, 0x1186, 0x1040, 0, 0, 3 },
	{ 0x1186, 0x1002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4 },
	{ 0x13F0, 0x0201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5 },
	{ 0x13F0, 0x0200, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 6 },
	{ }
};
MODUWE_DEVICE_TABWE(pci, sundance_pci_tbw);

enum {
	netdev_io_size = 128
};

stwuct pci_id_info {
        const chaw *name;
};
static const stwuct pci_id_info pci_id_tbw[] = {
	{"D-Wink DFE-550TX FAST Ethewnet Adaptew"},
	{"D-Wink DFE-550FX 100Mbps Fibew-optics Adaptew"},
	{"D-Wink DFE-580TX 4 powt Sewvew Adaptew"},
	{"D-Wink DFE-530TXS FAST Ethewnet Adaptew"},
	{"D-Wink DW10050-based FAST Ethewnet Adaptew"},
	{"Sundance Technowogy Awta"},
	{"IC Pwus Cowpowation IP100A FAST Ethewnet Adaptew"},
	{ }	/* tewminate wist. */
};

/* This dwivew was wwitten to use PCI memowy space, howevew x86-owiented
   hawdwawe often uses I/O space accesses. */

/* Offsets to the device wegistews.
   Unwike softwawe-onwy systems, device dwivews intewact with compwex hawdwawe.
   It's not usefuw to define symbowic names fow evewy wegistew bit in the
   device.  The name can onwy pawtiawwy document the semantics and make
   the dwivew wongew and mowe difficuwt to wead.
   In genewaw, onwy the impowtant configuwation vawues ow bits changed
   muwtipwe times shouwd be defined symbowicawwy.
*/
enum awta_offsets {
	DMACtww = 0x00,
	TxWistPtw = 0x04,
	TxDMABuwstThwesh = 0x08,
	TxDMAUwgentThwesh = 0x09,
	TxDMAPowwPewiod = 0x0a,
	WxDMAStatus = 0x0c,
	WxWistPtw = 0x10,
	DebugCtww0 = 0x1a,
	DebugCtww1 = 0x1c,
	WxDMABuwstThwesh = 0x14,
	WxDMAUwgentThwesh = 0x15,
	WxDMAPowwPewiod = 0x16,
	WEDCtww = 0x1a,
	ASICCtww = 0x30,
	EEData = 0x34,
	EECtww = 0x36,
	FwashAddw = 0x40,
	FwashData = 0x44,
	WakeEvent = 0x45,
	TxStatus = 0x46,
	TxFwameId = 0x47,
	DownCountew = 0x18,
	IntwCweaw = 0x4a,
	IntwEnabwe = 0x4c,
	IntwStatus = 0x4e,
	MACCtww0 = 0x50,
	MACCtww1 = 0x52,
	StationAddw = 0x54,
	MaxFwameSize = 0x5A,
	WxMode = 0x5c,
	MIICtww = 0x5e,
	MuwticastFiwtew0 = 0x60,
	MuwticastFiwtew1 = 0x64,
	WxOctetsWow = 0x68,
	WxOctetsHigh = 0x6a,
	TxOctetsWow = 0x6c,
	TxOctetsHigh = 0x6e,
	TxFwamesOK = 0x70,
	WxFwamesOK = 0x72,
	StatsCawwiewEwwow = 0x74,
	StatsWateCoww = 0x75,
	StatsMuwtiCoww = 0x76,
	StatsOneCoww = 0x77,
	StatsTxDefew = 0x78,
	WxMissed = 0x79,
	StatsTxXSDefew = 0x7a,
	StatsTxAbowt = 0x7b,
	StatsBcastTx = 0x7c,
	StatsBcastWx = 0x7d,
	StatsMcastTx = 0x7e,
	StatsMcastWx = 0x7f,
	/* Awiased and bogus vawues! */
	WxStatus = 0x0c,
};

#define ASIC_HI_WOWD(x)	((x) + 2)

enum ASICCtww_HiWowd_bit {
	GwobawWeset = 0x0001,
	WxWeset = 0x0002,
	TxWeset = 0x0004,
	DMAWeset = 0x0008,
	FIFOWeset = 0x0010,
	NetwowkWeset = 0x0020,
	HostWeset = 0x0040,
	WesetBusy = 0x0400,
};

/* Bits in the intewwupt status/mask wegistews. */
enum intw_status_bits {
	IntwSummawy=0x0001, IntwPCIEww=0x0002, IntwMACCtww=0x0008,
	IntwTxDone=0x0004, IntwWxDone=0x0010, IntwWxStawt=0x0020,
	IntwDwvWqst=0x0040,
	StatsMax=0x0080, WinkChange=0x0100,
	IntwTxDMADone=0x0200, IntwWxDMADone=0x0400,
};

/* Bits in the WxMode wegistew. */
enum wx_mode_bits {
	AcceptAwwIPMuwti=0x20, AcceptMuwtiHash=0x10, AcceptAww=0x08,
	AcceptBwoadcast=0x04, AcceptMuwticast=0x02, AcceptMyPhys=0x01,
};
/* Bits in MACCtww. */
enum mac_ctww0_bits {
	EnbFuwwDupwex=0x20, EnbWcvWawgeFwame=0x40,
	EnbFwowCtww=0x100, EnbPassWxCWC=0x200,
};
enum mac_ctww1_bits {
	StatsEnabwe=0x0020,	StatsDisabwe=0x0040, StatsEnabwed=0x0080,
	TxEnabwe=0x0100, TxDisabwe=0x0200, TxEnabwed=0x0400,
	WxEnabwe=0x0800, WxDisabwe=0x1000, WxEnabwed=0x2000,
};

/* Bits in WakeEvent wegistew. */
enum wake_event_bits {
	WakePktEnabwe = 0x01,
	MagicPktEnabwe = 0x02,
	WinkEventEnabwe = 0x04,
	WowEnabwe = 0x80,
};

/* The Wx and Tx buffew descwiptows. */
/* Note that using onwy 32 bit fiewds simpwifies convewsion to big-endian
   awchitectuwes. */
stwuct netdev_desc {
	__we32 next_desc;
	__we32 status;
	stwuct desc_fwag { __we32 addw, wength; } fwag;
};

/* Bits in netdev_desc.status */
enum desc_status_bits {
	DescOwn=0x8000,
	DescEndPacket=0x4000,
	DescEndWing=0x2000,
	WastFwag=0x80000000,
	DescIntwOnTx=0x8000,
	DescIntwOnDMADone=0x80000000,
	DisabweAwign = 0x00000001,
};

#define PWIV_AWIGN	15 	/* Wequiwed awignment mask */
/* Use  __attwibute__((awigned (W1_CACHE_BYTES)))  to maintain awignment
   within the stwuctuwe. */
#define MII_CNT		4
stwuct netdev_pwivate {
	/* Descwiptow wings fiwst fow awignment. */
	stwuct netdev_desc *wx_wing;
	stwuct netdev_desc *tx_wing;
	stwuct sk_buff* wx_skbuff[WX_WING_SIZE];
	stwuct sk_buff* tx_skbuff[TX_WING_SIZE];
        dma_addw_t tx_wing_dma;
        dma_addw_t wx_wing_dma;
	stwuct timew_wist timew;		/* Media monitowing timew. */
	stwuct net_device *ndev;		/* backpointew */
	/* ethtoow extwa stats */
	stwuct {
		u64 tx_muwtipwe_cowwisions;
		u64 tx_singwe_cowwisions;
		u64 tx_wate_cowwisions;
		u64 tx_defewwed;
		u64 tx_defewwed_excessive;
		u64 tx_abowted;
		u64 tx_bcasts;
		u64 wx_bcasts;
		u64 tx_mcasts;
		u64 wx_mcasts;
	} xstats;
	/* Fwequentwy used vawues: keep some adjacent fow cache effect. */
	spinwock_t wock;
	int msg_enabwe;
	int chip_id;
	unsigned int cuw_wx, diwty_wx;		/* Pwoducew/consumew wing indices */
	unsigned int wx_buf_sz;			/* Based on MTU+swack. */
	stwuct netdev_desc *wast_tx;		/* Wast Tx descwiptow used. */
	unsigned int cuw_tx, diwty_tx;
	/* These vawues awe keep twack of the twansceivew/media in use. */
	unsigned int fwowctww:1;
	unsigned int defauwt_powt:4;		/* Wast dev->if_powt vawue. */
	unsigned int an_enabwe:1;
	unsigned int speed;
	unsigned int wow_enabwed:1;			/* Wake on WAN enabwed */
	stwuct taskwet_stwuct wx_taskwet;
	stwuct taskwet_stwuct tx_taskwet;
	int budget;
	int cuw_task;
	/* Muwticast and weceive mode. */
	spinwock_t mcastwock;			/* SMP wock muwticast updates. */
	u16 mcast_fiwtew[4];
	/* MII twansceivew section. */
	stwuct mii_if_info mii_if;
	int mii_pweambwe_wequiwed;
	unsigned chaw phys[MII_CNT];		/* MII device addwesses, onwy fiwst one used. */
	stwuct pci_dev *pci_dev;
	void __iomem *base;
	spinwock_t statwock;
};

/* The station addwess wocation in the EEPWOM. */
#define EEPWOM_SA_OFFSET	0x10
#define DEFAUWT_INTW (IntwWxDMADone | IntwPCIEww | \
			IntwDwvWqst | IntwTxDone | StatsMax | \
			WinkChange)

static int  change_mtu(stwuct net_device *dev, int new_mtu);
static int  eepwom_wead(void __iomem *ioaddw, int wocation);
static int  mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue);
static int  mdio_wait_wink(stwuct net_device *dev, int wait);
static int  netdev_open(stwuct net_device *dev);
static void check_dupwex(stwuct net_device *dev);
static void netdev_timew(stwuct timew_wist *t);
static void tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void init_wing(stwuct net_device *dev);
static netdev_tx_t stawt_tx(stwuct sk_buff *skb, stwuct net_device *dev);
static int weset_tx (stwuct net_device *dev);
static iwqwetuwn_t intw_handwew(int iwq, void *dev_instance);
static void wx_poww(stwuct taskwet_stwuct *t);
static void tx_poww(stwuct taskwet_stwuct *t);
static void wefiww_wx (stwuct net_device *dev);
static void netdev_ewwow(stwuct net_device *dev, int intw_status);
static void netdev_ewwow(stwuct net_device *dev, int intw_status);
static void set_wx_mode(stwuct net_device *dev);
static int __set_mac_addw(stwuct net_device *dev);
static int sundance_set_mac_addw(stwuct net_device *dev, void *data);
static stwuct net_device_stats *get_stats(stwuct net_device *dev);
static int netdev_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static int  netdev_cwose(stwuct net_device *dev);
static const stwuct ethtoow_ops ethtoow_ops;

static void sundance_weset(stwuct net_device *dev, unsigned wong weset_cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base + ASICCtww;
	int countdown;

	/* ST201 documentation states ASICCtww is a 32bit wegistew */
	iowwite32 (weset_cmd | iowead32 (ioaddw), ioaddw);
	/* ST201 documentation states weset can take up to 1 ms */
	countdown = 10 + 1;
	whiwe (iowead32 (ioaddw) & (WesetBusy << 16)) {
		if (--countdown == 0) {
			pwintk(KEWN_WAWNING "%s : weset not compweted !!\n", dev->name);
			bweak;
		}
		udeway(100);
	}
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void sundance_poww_contwowwew(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	disabwe_iwq(np->pci_dev->iwq);
	intw_handwew(np->pci_dev->iwq, dev);
	enabwe_iwq(np->pci_dev->iwq);
}
#endif

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= netdev_open,
	.ndo_stop		= netdev_cwose,
	.ndo_stawt_xmit		= stawt_tx,
	.ndo_get_stats 		= get_stats,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_eth_ioctw		= netdev_ioctw,
	.ndo_tx_timeout		= tx_timeout,
	.ndo_change_mtu		= change_mtu,
	.ndo_set_mac_addwess 	= sundance_set_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew 	= sundance_poww_contwowwew,
#endif
};

static int sundance_pwobe1(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct net_device *dev;
	stwuct netdev_pwivate *np;
	static int cawd_idx;
	int chip_idx = ent->dwivew_data;
	int iwq;
	int i;
	void __iomem *ioaddw;
	u16 mii_ctw;
	void *wing_space;
	dma_addw_t wing_dma;
#ifdef USE_IO_OPS
	int baw = 0;
#ewse
	int baw = 1;
#endif
	int phy, phy_end, phy_idx = 0;
	__we16 addw[ETH_AWEN / 2];

	if (pci_enabwe_device(pdev))
		wetuwn -EIO;
	pci_set_mastew(pdev);

	iwq = pdev->iwq;

	dev = awwoc_ethewdev(sizeof(*np));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	if (pci_wequest_wegions(pdev, DWV_NAME))
		goto eww_out_netdev;

	ioaddw = pci_iomap(pdev, baw, netdev_io_size);
	if (!ioaddw)
		goto eww_out_wes;

	fow (i = 0; i < 3; i++)
		addw[i] =
			cpu_to_we16(eepwom_wead(ioaddw, i + EEPWOM_SA_OFFSET));
	eth_hw_addw_set(dev, (u8 *)addw);

	np = netdev_pwiv(dev);
	np->ndev = dev;
	np->base = ioaddw;
	np->pci_dev = pdev;
	np->chip_id = chip_idx;
	np->msg_enabwe = (1 << debug) - 1;
	spin_wock_init(&np->wock);
	spin_wock_init(&np->statwock);
	taskwet_setup(&np->wx_taskwet, wx_poww);
	taskwet_setup(&np->tx_taskwet, tx_poww);

	wing_space = dma_awwoc_cohewent(&pdev->dev, TX_TOTAW_SIZE,
			&wing_dma, GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_cweawdev;
	np->tx_wing = (stwuct netdev_desc *)wing_space;
	np->tx_wing_dma = wing_dma;

	wing_space = dma_awwoc_cohewent(&pdev->dev, WX_TOTAW_SIZE,
			&wing_dma, GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_unmap_tx;
	np->wx_wing = (stwuct netdev_desc *)wing_space;
	np->wx_wing_dma = wing_dma;

	np->mii_if.dev = dev;
	np->mii_if.mdio_wead = mdio_wead;
	np->mii_if.mdio_wwite = mdio_wwite;
	np->mii_if.phy_id_mask = 0x1f;
	np->mii_if.weg_num_mask = 0x1f;

	/* The chip-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &netdev_ops;
	dev->ethtoow_ops = &ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	/* MTU wange: 68 - 8191 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = 8191;

	pci_set_dwvdata(pdev, dev);

	i = wegistew_netdev(dev);
	if (i)
		goto eww_out_unmap_wx;

	pwintk(KEWN_INFO "%s: %s at %p, %pM, IWQ %d.\n",
	       dev->name, pci_id_tbw[chip_idx].name, ioaddw,
	       dev->dev_addw, iwq);

	np->phys[0] = 1;		/* Defauwt setting */
	np->mii_pweambwe_wequiwed++;

	/*
	 * It seems some phys doesn't deaw weww with addwess 0 being accessed
	 * fiwst
	 */
	if (sundance_pci_tbw[np->chip_id].device == 0x0200) {
		phy = 0;
		phy_end = 31;
	} ewse {
		phy = 1;
		phy_end = 32;	/* wwaps to zewo, due to 'phy & 0x1f' */
	}
	fow (; phy <= phy_end && phy_idx < MII_CNT; phy++) {
		int phyx = phy & 0x1f;
		int mii_status = mdio_wead(dev, phyx, MII_BMSW);
		if (mii_status != 0xffff  &&  mii_status != 0x0000) {
			np->phys[phy_idx++] = phyx;
			np->mii_if.advewtising = mdio_wead(dev, phyx, MII_ADVEWTISE);
			if ((mii_status & 0x0040) == 0)
				np->mii_pweambwe_wequiwed++;
			pwintk(KEWN_INFO "%s: MII PHY found at addwess %d, status "
				   "0x%4.4x advewtising %4.4x.\n",
				   dev->name, phyx, mii_status, np->mii_if.advewtising);
		}
	}
	np->mii_pweambwe_wequiwed--;

	if (phy_idx == 0) {
		pwintk(KEWN_INFO "%s: No MII twansceivew found, abowting.  ASIC status %x\n",
			   dev->name, iowead32(ioaddw + ASICCtww));
		goto eww_out_unwegistew;
	}

	np->mii_if.phy_id = np->phys[0];

	/* Pawse ovewwide configuwation */
	np->an_enabwe = 1;
	if (cawd_idx < MAX_UNITS) {
		if (media[cawd_idx] != NUWW) {
			np->an_enabwe = 0;
			if (stwcmp (media[cawd_idx], "100mbps_fd") == 0 ||
			    stwcmp (media[cawd_idx], "4") == 0) {
				np->speed = 100;
				np->mii_if.fuww_dupwex = 1;
			} ewse if (stwcmp (media[cawd_idx], "100mbps_hd") == 0 ||
				   stwcmp (media[cawd_idx], "3") == 0) {
				np->speed = 100;
				np->mii_if.fuww_dupwex = 0;
			} ewse if (stwcmp (media[cawd_idx], "10mbps_fd") == 0 ||
				   stwcmp (media[cawd_idx], "2") == 0) {
				np->speed = 10;
				np->mii_if.fuww_dupwex = 1;
			} ewse if (stwcmp (media[cawd_idx], "10mbps_hd") == 0 ||
				   stwcmp (media[cawd_idx], "1") == 0) {
				np->speed = 10;
				np->mii_if.fuww_dupwex = 0;
			} ewse {
				np->an_enabwe = 1;
			}
		}
		if (fwowctww == 1)
			np->fwowctww = 1;
	}

	/* Fibwe PHY? */
	if (iowead32 (ioaddw + ASICCtww) & 0x80) {
		/* Defauwt 100Mbps Fuww */
		if (np->an_enabwe) {
			np->speed = 100;
			np->mii_if.fuww_dupwex = 1;
			np->an_enabwe = 0;
		}
	}
	/* Weset PHY */
	mdio_wwite (dev, np->phys[0], MII_BMCW, BMCW_WESET);
	mdeway (300);
	/* If fwow contwow enabwed, we need to advewtise it.*/
	if (np->fwowctww)
		mdio_wwite (dev, np->phys[0], MII_ADVEWTISE, np->mii_if.advewtising | 0x0400);
	mdio_wwite (dev, np->phys[0], MII_BMCW, BMCW_ANENABWE|BMCW_ANWESTAWT);
	/* Fowce media type */
	if (!np->an_enabwe) {
		mii_ctw = 0;
		mii_ctw |= (np->speed == 100) ? BMCW_SPEED100 : 0;
		mii_ctw |= (np->mii_if.fuww_dupwex) ? BMCW_FUWWDPWX : 0;
		mdio_wwite (dev, np->phys[0], MII_BMCW, mii_ctw);
		pwintk (KEWN_INFO "Ovewwide speed=%d, %s dupwex\n",
			np->speed, np->mii_if.fuww_dupwex ? "Fuww" : "Hawf");

	}

	/* Pewhaps move the weset hewe? */
	/* Weset the chip to ewase pwevious misconfiguwation. */
	if (netif_msg_hw(np))
		pwintk("ASIC Contwow is %x.\n", iowead32(ioaddw + ASICCtww));
	sundance_weset(dev, 0x00ff << 16);
	if (netif_msg_hw(np))
		pwintk("ASIC Contwow is now %x.\n", iowead32(ioaddw + ASICCtww));

	cawd_idx++;
	wetuwn 0;

eww_out_unwegistew:
	unwegistew_netdev(dev);
eww_out_unmap_wx:
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE,
		np->wx_wing, np->wx_wing_dma);
eww_out_unmap_tx:
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE,
		np->tx_wing, np->tx_wing_dma);
eww_out_cweawdev:
	pci_iounmap(pdev, ioaddw);
eww_out_wes:
	pci_wewease_wegions(pdev);
eww_out_netdev:
	fwee_netdev (dev);
	wetuwn -ENODEV;
}

static int change_mtu(stwuct net_device *dev, int new_mtu)
{
	if (netif_wunning(dev))
		wetuwn -EBUSY;
	dev->mtu = new_mtu;
	wetuwn 0;
}

#define eepwom_deway(ee_addw)	iowead32(ee_addw)
/* Wead the EEPWOM and MII Management Data I/O (MDIO) intewfaces. */
static int eepwom_wead(void __iomem *ioaddw, int wocation)
{
	int boguscnt = 10000;		/* Typicaw 1900 ticks. */
	iowwite16(0x0200 | (wocation & 0xff), ioaddw + EECtww);
	do {
		eepwom_deway(ioaddw + EECtww);
		if (! (iowead16(ioaddw + EECtww) & 0x8000)) {
			wetuwn iowead16(ioaddw + EEData);
		}
	} whiwe (--boguscnt > 0);
	wetuwn 0;
}

/*  MII twansceivew contwow section.
	Wead and wwite the MII wegistews using softwawe-genewated sewiaw
	MDIO pwotocow.  See the MII specifications ow DP83840A data sheet
	fow detaiws.

	The maximum data cwock wate is 2.5 Mhz.  The minimum timing is usuawwy
	met by back-to-back 33Mhz PCI cycwes. */
#define mdio_deway() iowead8(mdio_addw)

enum mii_weg_bits {
	MDIO_ShiftCwk=0x0001, MDIO_Data=0x0002, MDIO_EnbOutput=0x0004,
};
#define MDIO_EnbIn  (0)
#define MDIO_WWITE0 (MDIO_EnbOutput)
#define MDIO_WWITE1 (MDIO_Data | MDIO_EnbOutput)

/* Genewate the pweambwe wequiwed fow initiaw synchwonization and
   a few owdew twansceivews. */
static void mdio_sync(void __iomem *mdio_addw)
{
	int bits = 32;

	/* Estabwish sync by sending at weast 32 wogic ones. */
	whiwe (--bits >= 0) {
		iowwite8(MDIO_WWITE1, mdio_addw);
		mdio_deway();
		iowwite8(MDIO_WWITE1 | MDIO_ShiftCwk, mdio_addw);
		mdio_deway();
	}
}

static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *mdio_addw = np->base + MIICtww;
	int mii_cmd = (0xf6 << 10) | (phy_id << 5) | wocation;
	int i, wetvaw = 0;

	if (np->mii_pweambwe_wequiwed)
		mdio_sync(mdio_addw);

	/* Shift the wead command bits out. */
	fow (i = 15; i >= 0; i--) {
		int datavaw = (mii_cmd & (1 << i)) ? MDIO_WWITE1 : MDIO_WWITE0;

		iowwite8(datavaw, mdio_addw);
		mdio_deway();
		iowwite8(datavaw | MDIO_ShiftCwk, mdio_addw);
		mdio_deway();
	}
	/* Wead the two twansition, 16 data, and wiwe-idwe bits. */
	fow (i = 19; i > 0; i--) {
		iowwite8(MDIO_EnbIn, mdio_addw);
		mdio_deway();
		wetvaw = (wetvaw << 1) | ((iowead8(mdio_addw) & MDIO_Data) ? 1 : 0);
		iowwite8(MDIO_EnbIn | MDIO_ShiftCwk, mdio_addw);
		mdio_deway();
	}
	wetuwn (wetvaw>>1) & 0xffff;
}

static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *mdio_addw = np->base + MIICtww;
	int mii_cmd = (0x5002 << 16) | (phy_id << 23) | (wocation<<18) | vawue;
	int i;

	if (np->mii_pweambwe_wequiwed)
		mdio_sync(mdio_addw);

	/* Shift the command bits out. */
	fow (i = 31; i >= 0; i--) {
		int datavaw = (mii_cmd & (1 << i)) ? MDIO_WWITE1 : MDIO_WWITE0;

		iowwite8(datavaw, mdio_addw);
		mdio_deway();
		iowwite8(datavaw | MDIO_ShiftCwk, mdio_addw);
		mdio_deway();
	}
	/* Cweaw out extwa bits. */
	fow (i = 2; i > 0; i--) {
		iowwite8(MDIO_EnbIn, mdio_addw);
		mdio_deway();
		iowwite8(MDIO_EnbIn | MDIO_ShiftCwk, mdio_addw);
		mdio_deway();
	}
}

static int mdio_wait_wink(stwuct net_device *dev, int wait)
{
	int bmsw;
	int phy_id;
	stwuct netdev_pwivate *np;

	np = netdev_pwiv(dev);
	phy_id = np->phys[0];

	do {
		bmsw = mdio_wead(dev, phy_id, MII_BMSW);
		if (bmsw & 0x0004)
			wetuwn 0;
		mdeway(1);
	} whiwe (--wait > 0);
	wetuwn -1;
}

static int netdev_open(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	const int iwq = np->pci_dev->iwq;
	unsigned wong fwags;
	int i;

	sundance_weset(dev, 0x00ff << 16);

	i = wequest_iwq(iwq, intw_handwew, IWQF_SHAWED, dev->name, dev);
	if (i)
		wetuwn i;

	if (netif_msg_ifup(np))
		pwintk(KEWN_DEBUG "%s: netdev_open() iwq %d\n", dev->name, iwq);

	init_wing(dev);

	iowwite32(np->wx_wing_dma, ioaddw + WxWistPtw);
	/* The Tx wist pointew is wwitten as packets awe queued. */

	/* Initiawize othew wegistews. */
	__set_mac_addw(dev);
#if IS_ENABWED(CONFIG_VWAN_8021Q)
	iowwite16(dev->mtu + 18, ioaddw + MaxFwameSize);
#ewse
	iowwite16(dev->mtu + 14, ioaddw + MaxFwameSize);
#endif
	if (dev->mtu > 2047)
		iowwite32(iowead32(ioaddw + ASICCtww) | 0x0C, ioaddw + ASICCtww);

	/* Configuwe the PCI bus buwsts and FIFO thweshowds. */

	if (dev->if_powt == 0)
		dev->if_powt = np->defauwt_powt;

	spin_wock_init(&np->mcastwock);

	set_wx_mode(dev);
	iowwite16(0, ioaddw + IntwEnabwe);
	iowwite16(0, ioaddw + DownCountew);
	/* Set the chip to poww evewy N*320nsec. */
	iowwite8(100, ioaddw + WxDMAPowwPewiod);
	iowwite8(127, ioaddw + TxDMAPowwPewiod);
	/* Fix DFE-580TX packet dwop issue */
	if (np->pci_dev->wevision >= 0x14)
		iowwite8(0x01, ioaddw + DebugCtww1);
	netif_stawt_queue(dev);

	spin_wock_iwqsave(&np->wock, fwags);
	weset_tx(dev);
	spin_unwock_iwqwestowe(&np->wock, fwags);

	iowwite16 (StatsEnabwe | WxEnabwe | TxEnabwe, ioaddw + MACCtww1);

	/* Disabwe Wow */
	iowwite8(iowead8(ioaddw + WakeEvent) | 0x00, ioaddw + WakeEvent);
	np->wow_enabwed = 0;

	if (netif_msg_ifup(np))
		pwintk(KEWN_DEBUG "%s: Done netdev_open(), status: Wx %x Tx %x "
			   "MAC Contwow %x, %4.4x %4.4x.\n",
			   dev->name, iowead32(ioaddw + WxStatus), iowead8(ioaddw + TxStatus),
			   iowead32(ioaddw + MACCtww0),
			   iowead16(ioaddw + MACCtww1), iowead16(ioaddw + MACCtww0));

	/* Set the timew to check fow wink beat. */
	timew_setup(&np->timew, netdev_timew, 0);
	np->timew.expiwes = jiffies + 3*HZ;
	add_timew(&np->timew);

	/* Enabwe intewwupts by setting the intewwupt mask. */
	iowwite16(DEFAUWT_INTW, ioaddw + IntwEnabwe);

	wetuwn 0;
}

static void check_dupwex(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	int mii_wpa = mdio_wead(dev, np->phys[0], MII_WPA);
	int negotiated = mii_wpa & np->mii_if.advewtising;
	int dupwex;

	/* Fowce media */
	if (!np->an_enabwe || mii_wpa == 0xffff) {
		if (np->mii_if.fuww_dupwex)
			iowwite16 (iowead16 (ioaddw + MACCtww0) | EnbFuwwDupwex,
				ioaddw + MACCtww0);
		wetuwn;
	}

	/* Autonegotiation */
	dupwex = (negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040;
	if (np->mii_if.fuww_dupwex != dupwex) {
		np->mii_if.fuww_dupwex = dupwex;
		if (netif_msg_wink(np))
			pwintk(KEWN_INFO "%s: Setting %s-dupwex based on MII #%d "
				   "negotiated capabiwity %4.4x.\n", dev->name,
				   dupwex ? "fuww" : "hawf", np->phys[0], negotiated);
		iowwite16(iowead16(ioaddw + MACCtww0) | (dupwex ? 0x20 : 0), ioaddw + MACCtww0);
	}
}

static void netdev_timew(stwuct timew_wist *t)
{
	stwuct netdev_pwivate *np = fwom_timew(np, t, timew);
	stwuct net_device *dev = np->mii_if.dev;
	void __iomem *ioaddw = np->base;
	int next_tick = 10*HZ;

	if (netif_msg_timew(np)) {
		pwintk(KEWN_DEBUG "%s: Media sewection timew tick, intw status %4.4x, "
			   "Tx %x Wx %x.\n",
			   dev->name, iowead16(ioaddw + IntwEnabwe),
			   iowead8(ioaddw + TxStatus), iowead32(ioaddw + WxStatus));
	}
	check_dupwex(dev);
	np->timew.expiwes = jiffies + next_tick;
	add_timew(&np->timew);
}

static void tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	unsigned wong fwag;

	netif_stop_queue(dev);
	taskwet_disabwe_in_atomic(&np->tx_taskwet);
	iowwite16(0, ioaddw + IntwEnabwe);
	pwintk(KEWN_WAWNING "%s: Twansmit timed out, TxStatus %2.2x "
		   "TxFwameId %2.2x,"
		   " wesetting...\n", dev->name, iowead8(ioaddw + TxStatus),
		   iowead8(ioaddw + TxFwameId));

	{
		int i;
		fow (i=0; i<TX_WING_SIZE; i++) {
			pwintk(KEWN_DEBUG "%02x %08wwx %08x %08x(%02x) %08x %08x\n", i,
				(unsigned wong wong)(np->tx_wing_dma + i*sizeof(*np->tx_wing)),
				we32_to_cpu(np->tx_wing[i].next_desc),
				we32_to_cpu(np->tx_wing[i].status),
				(we32_to_cpu(np->tx_wing[i].status) >> 2) & 0xff,
				we32_to_cpu(np->tx_wing[i].fwag.addw),
				we32_to_cpu(np->tx_wing[i].fwag.wength));
		}
		pwintk(KEWN_DEBUG "TxWistPtw=%08x netif_queue_stopped=%d\n",
			iowead32(np->base + TxWistPtw),
			netif_queue_stopped(dev));
		pwintk(KEWN_DEBUG "cuw_tx=%d(%02x) diwty_tx=%d(%02x)\n",
			np->cuw_tx, np->cuw_tx % TX_WING_SIZE,
			np->diwty_tx, np->diwty_tx % TX_WING_SIZE);
		pwintk(KEWN_DEBUG "cuw_wx=%d diwty_wx=%d\n", np->cuw_wx, np->diwty_wx);
		pwintk(KEWN_DEBUG "cuw_task=%d\n", np->cuw_task);
	}
	spin_wock_iwqsave(&np->wock, fwag);

	/* Stop and westawt the chip's Tx pwocesses . */
	weset_tx(dev);
	spin_unwock_iwqwestowe(&np->wock, fwag);

	dev->if_powt = 0;

	netif_twans_update(dev); /* pwevent tx timeout */
	dev->stats.tx_ewwows++;
	if (np->cuw_tx - np->diwty_tx < TX_QUEUE_WEN - 4) {
		netif_wake_queue(dev);
	}
	iowwite16(DEFAUWT_INTW, ioaddw + IntwEnabwe);
	taskwet_enabwe(&np->tx_taskwet);
}


/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void init_wing(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int i;

	np->cuw_wx = np->cuw_tx = 0;
	np->diwty_wx = np->diwty_tx = 0;
	np->cuw_task = 0;

	np->wx_buf_sz = (dev->mtu <= 1520 ? PKT_BUF_SZ : dev->mtu + 16);

	/* Initiawize aww Wx descwiptows. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		np->wx_wing[i].next_desc = cpu_to_we32(np->wx_wing_dma +
			((i+1)%WX_WING_SIZE)*sizeof(*np->wx_wing));
		np->wx_wing[i].status = 0;
		np->wx_wing[i].fwag.wength = 0;
		np->wx_skbuff[i] = NUWW;
	}

	/* Fiww in the Wx buffews.  Handwe awwocation faiwuwe gwacefuwwy. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb =
			netdev_awwoc_skb(dev, np->wx_buf_sz + 2);
		np->wx_skbuff[i] = skb;
		if (skb == NUWW)
			bweak;
		skb_wesewve(skb, 2);	/* 16 byte awign the IP headew. */
		np->wx_wing[i].fwag.addw = cpu_to_we32(
			dma_map_singwe(&np->pci_dev->dev, skb->data,
				np->wx_buf_sz, DMA_FWOM_DEVICE));
		if (dma_mapping_ewwow(&np->pci_dev->dev,
					np->wx_wing[i].fwag.addw)) {
			dev_kfwee_skb(skb);
			np->wx_skbuff[i] = NUWW;
			bweak;
		}
		np->wx_wing[i].fwag.wength = cpu_to_we32(np->wx_buf_sz | WastFwag);
	}
	np->diwty_wx = (unsigned int)(i - WX_WING_SIZE);

	fow (i = 0; i < TX_WING_SIZE; i++) {
		np->tx_skbuff[i] = NUWW;
		np->tx_wing[i].status = 0;
	}
}

static void tx_poww(stwuct taskwet_stwuct *t)
{
	stwuct netdev_pwivate *np = fwom_taskwet(np, t, tx_taskwet);
	unsigned head = np->cuw_task % TX_WING_SIZE;
	stwuct netdev_desc *txdesc =
		&np->tx_wing[(np->cuw_tx - 1) % TX_WING_SIZE];

	/* Chain the next pointew */
	fow (; np->cuw_tx - np->cuw_task > 0; np->cuw_task++) {
		int entwy = np->cuw_task % TX_WING_SIZE;
		txdesc = &np->tx_wing[entwy];
		if (np->wast_tx) {
			np->wast_tx->next_desc = cpu_to_we32(np->tx_wing_dma +
				entwy*sizeof(stwuct netdev_desc));
		}
		np->wast_tx = txdesc;
	}
	/* Indicate the watest descwiptow of tx wing */
	txdesc->status |= cpu_to_we32(DescIntwOnTx);

	if (iowead32 (np->base + TxWistPtw) == 0)
		iowwite32 (np->tx_wing_dma + head * sizeof(stwuct netdev_desc),
			np->base + TxWistPtw);
}

static netdev_tx_t
stawt_tx (stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct netdev_desc *txdesc;
	unsigned entwy;

	/* Cawcuwate the next Tx descwiptow entwy. */
	entwy = np->cuw_tx % TX_WING_SIZE;
	np->tx_skbuff[entwy] = skb;
	txdesc = &np->tx_wing[entwy];

	txdesc->next_desc = 0;
	txdesc->status = cpu_to_we32 ((entwy << 2) | DisabweAwign);
	txdesc->fwag.addw = cpu_to_we32(dma_map_singwe(&np->pci_dev->dev,
				skb->data, skb->wen, DMA_TO_DEVICE));
	if (dma_mapping_ewwow(&np->pci_dev->dev,
				txdesc->fwag.addw))
			goto dwop_fwame;
	txdesc->fwag.wength = cpu_to_we32 (skb->wen | WastFwag);

	/* Incwement cuw_tx befowe taskwet_scheduwe() */
	np->cuw_tx++;
	mb();
	/* Scheduwe a tx_poww() task */
	taskwet_scheduwe(&np->tx_taskwet);

	/* On some awchitectuwes: expwicitwy fwush cache wines hewe. */
	if (np->cuw_tx - np->diwty_tx < TX_QUEUE_WEN - 1 &&
	    !netif_queue_stopped(dev)) {
		/* do nothing */
	} ewse {
		netif_stop_queue (dev);
	}
	if (netif_msg_tx_queued(np)) {
		pwintk (KEWN_DEBUG
			"%s: Twansmit fwame #%d queued in swot %d.\n",
			dev->name, np->cuw_tx, entwy);
	}
	wetuwn NETDEV_TX_OK;

dwop_fwame:
	dev_kfwee_skb_any(skb);
	np->tx_skbuff[entwy] = NUWW;
	dev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;
}

/* Weset hawdwawe tx and fwee aww of tx buffews */
static int
weset_tx (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	stwuct sk_buff *skb;
	int i;

	/* Weset tx wogic, TxWistPtw wiww be cweaned */
	iowwite16 (TxDisabwe, ioaddw + MACCtww1);
	sundance_weset(dev, (NetwowkWeset|FIFOWeset|DMAWeset|TxWeset) << 16);

	/* fwee aww tx skbuff */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		np->tx_wing[i].next_desc = 0;

		skb = np->tx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&np->pci_dev->dev,
				we32_to_cpu(np->tx_wing[i].fwag.addw),
				skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
			np->tx_skbuff[i] = NUWW;
			dev->stats.tx_dwopped++;
		}
	}
	np->cuw_tx = np->diwty_tx = 0;
	np->cuw_task = 0;

	np->wast_tx = NUWW;
	iowwite8(127, ioaddw + TxDMAPowwPewiod);

	iowwite16 (StatsEnabwe | WxEnabwe | TxEnabwe, ioaddw + MACCtww1);
	wetuwn 0;
}

/* The intewwupt handwew cweans up aftew the Tx thwead,
   and scheduwe a Wx thwead wowk */
static iwqwetuwn_t intw_handwew(int iwq, void *dev_instance)
{
	stwuct net_device *dev = (stwuct net_device *)dev_instance;
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	int hw_fwame_id;
	int tx_cnt;
	int tx_status;
	int handwed = 0;
	int i;

	do {
		int intw_status = iowead16(ioaddw + IntwStatus);
		iowwite16(intw_status, ioaddw + IntwStatus);

		if (netif_msg_intw(np))
			pwintk(KEWN_DEBUG "%s: Intewwupt, status %4.4x.\n",
				   dev->name, intw_status);

		if (!(intw_status & DEFAUWT_INTW))
			bweak;

		handwed = 1;

		if (intw_status & (IntwWxDMADone)) {
			iowwite16(DEFAUWT_INTW & ~(IntwWxDone|IntwWxDMADone),
					ioaddw + IntwEnabwe);
			if (np->budget < 0)
				np->budget = WX_BUDGET;
			taskwet_scheduwe(&np->wx_taskwet);
		}
		if (intw_status & (IntwTxDone | IntwDwvWqst)) {
			tx_status = iowead16 (ioaddw + TxStatus);
			fow (tx_cnt=32; tx_status & 0x80; --tx_cnt) {
				if (netif_msg_tx_done(np))
					pwintk
					    ("%s: Twansmit status is %2.2x.\n",
				     	dev->name, tx_status);
				if (tx_status & 0x1e) {
					if (netif_msg_tx_eww(np))
						pwintk("%s: Twansmit ewwow status %4.4x.\n",
							   dev->name, tx_status);
					dev->stats.tx_ewwows++;
					if (tx_status & 0x10)
						dev->stats.tx_fifo_ewwows++;
					if (tx_status & 0x08)
						dev->stats.cowwisions++;
					if (tx_status & 0x04)
						dev->stats.tx_fifo_ewwows++;
					if (tx_status & 0x02)
						dev->stats.tx_window_ewwows++;

					/*
					** This weset has been vewified on
					** DFE-580TX boawds ! phdm@macqew.be.
					*/
					if (tx_status & 0x10) {	/* TxUndewwun */
						/* Westawt Tx FIFO and twansmittew */
						sundance_weset(dev, (NetwowkWeset|FIFOWeset|TxWeset) << 16);
						/* No need to weset the Tx pointew hewe */
					}
					/* Westawt the Tx. Need to make suwe tx enabwed */
					i = 10;
					do {
						iowwite16(iowead16(ioaddw + MACCtww1) | TxEnabwe, ioaddw + MACCtww1);
						if (iowead16(ioaddw + MACCtww1) & TxEnabwed)
							bweak;
						mdeway(1);
					} whiwe (--i);
				}
				/* Yup, this is a documentation bug.  It cost me *houws*. */
				iowwite16 (0, ioaddw + TxStatus);
				if (tx_cnt < 0) {
					iowwite32(5000, ioaddw + DownCountew);
					bweak;
				}
				tx_status = iowead16 (ioaddw + TxStatus);
			}
			hw_fwame_id = (tx_status >> 8) & 0xff;
		} ewse 	{
			hw_fwame_id = iowead8(ioaddw + TxFwameId);
		}

		if (np->pci_dev->wevision >= 0x14) {
			spin_wock(&np->wock);
			fow (; np->cuw_tx - np->diwty_tx > 0; np->diwty_tx++) {
				int entwy = np->diwty_tx % TX_WING_SIZE;
				stwuct sk_buff *skb;
				int sw_fwame_id;
				sw_fwame_id = (we32_to_cpu(
					np->tx_wing[entwy].status) >> 2) & 0xff;
				if (sw_fwame_id == hw_fwame_id &&
					!(we32_to_cpu(np->tx_wing[entwy].status)
					& 0x00010000))
						bweak;
				if (sw_fwame_id == (hw_fwame_id + 1) %
					TX_WING_SIZE)
						bweak;
				skb = np->tx_skbuff[entwy];
				/* Fwee the owiginaw skb. */
				dma_unmap_singwe(&np->pci_dev->dev,
					we32_to_cpu(np->tx_wing[entwy].fwag.addw),
					skb->wen, DMA_TO_DEVICE);
				dev_consume_skb_iwq(np->tx_skbuff[entwy]);
				np->tx_skbuff[entwy] = NUWW;
				np->tx_wing[entwy].fwag.addw = 0;
				np->tx_wing[entwy].fwag.wength = 0;
			}
			spin_unwock(&np->wock);
		} ewse {
			spin_wock(&np->wock);
			fow (; np->cuw_tx - np->diwty_tx > 0; np->diwty_tx++) {
				int entwy = np->diwty_tx % TX_WING_SIZE;
				stwuct sk_buff *skb;
				if (!(we32_to_cpu(np->tx_wing[entwy].status)
							& 0x00010000))
					bweak;
				skb = np->tx_skbuff[entwy];
				/* Fwee the owiginaw skb. */
				dma_unmap_singwe(&np->pci_dev->dev,
					we32_to_cpu(np->tx_wing[entwy].fwag.addw),
					skb->wen, DMA_TO_DEVICE);
				dev_consume_skb_iwq(np->tx_skbuff[entwy]);
				np->tx_skbuff[entwy] = NUWW;
				np->tx_wing[entwy].fwag.addw = 0;
				np->tx_wing[entwy].fwag.wength = 0;
			}
			spin_unwock(&np->wock);
		}

		if (netif_queue_stopped(dev) &&
			np->cuw_tx - np->diwty_tx < TX_QUEUE_WEN - 4) {
			/* The wing is no wongew fuww, cweaw busy fwag. */
			netif_wake_queue (dev);
		}
		/* Abnowmaw ewwow summawy/uncommon events handwews. */
		if (intw_status & (IntwPCIEww | WinkChange | StatsMax))
			netdev_ewwow(dev, intw_status);
	} whiwe (0);
	if (netif_msg_intw(np))
		pwintk(KEWN_DEBUG "%s: exiting intewwupt, status=%#4.4x.\n",
			   dev->name, iowead16(ioaddw + IntwStatus));
	wetuwn IWQ_WETVAW(handwed);
}

static void wx_poww(stwuct taskwet_stwuct *t)
{
	stwuct netdev_pwivate *np = fwom_taskwet(np, t, wx_taskwet);
	stwuct net_device *dev = np->ndev;
	int entwy = np->cuw_wx % WX_WING_SIZE;
	int boguscnt = np->budget;
	void __iomem *ioaddw = np->base;
	int weceived = 0;

	/* If EOP is set on the next entwy, it's a new packet. Send it up. */
	whiwe (1) {
		stwuct netdev_desc *desc = &(np->wx_wing[entwy]);
		u32 fwame_status = we32_to_cpu(desc->status);
		int pkt_wen;

		if (--boguscnt < 0) {
			goto not_done;
		}
		if (!(fwame_status & DescOwn))
			bweak;
		pkt_wen = fwame_status & 0x1fff;	/* Chip omits the CWC. */
		if (netif_msg_wx_status(np))
			pwintk(KEWN_DEBUG "  netdev_wx() status was %8.8x.\n",
				   fwame_status);
		if (fwame_status & 0x001f4000) {
			/* Thewe was a ewwow. */
			if (netif_msg_wx_eww(np))
				pwintk(KEWN_DEBUG "  netdev_wx() Wx ewwow was %8.8x.\n",
					   fwame_status);
			dev->stats.wx_ewwows++;
			if (fwame_status & 0x00100000)
				dev->stats.wx_wength_ewwows++;
			if (fwame_status & 0x00010000)
				dev->stats.wx_fifo_ewwows++;
			if (fwame_status & 0x00060000)
				dev->stats.wx_fwame_ewwows++;
			if (fwame_status & 0x00080000)
				dev->stats.wx_cwc_ewwows++;
			if (fwame_status & 0x00100000) {
				pwintk(KEWN_WAWNING "%s: Ovewsized Ethewnet fwame,"
					   " status %8.8x.\n",
					   dev->name, fwame_status);
			}
		} ewse {
			stwuct sk_buff *skb;
#ifndef finaw_vewsion
			if (netif_msg_wx_status(np))
				pwintk(KEWN_DEBUG "  netdev_wx() nowmaw Wx pkt wength %d"
					   ", bogus_cnt %d.\n",
					   pkt_wen, boguscnt);
#endif
			/* Check if the packet is wong enough to accept without copying
			   to a minimawwy-sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
				skb_wesewve(skb, 2);	/* 16 byte awign the IP headew */
				dma_sync_singwe_fow_cpu(&np->pci_dev->dev,
						we32_to_cpu(desc->fwag.addw),
						np->wx_buf_sz, DMA_FWOM_DEVICE);
				skb_copy_to_wineaw_data(skb, np->wx_skbuff[entwy]->data, pkt_wen);
				dma_sync_singwe_fow_device(&np->pci_dev->dev,
						we32_to_cpu(desc->fwag.addw),
						np->wx_buf_sz, DMA_FWOM_DEVICE);
				skb_put(skb, pkt_wen);
			} ewse {
				dma_unmap_singwe(&np->pci_dev->dev,
					we32_to_cpu(desc->fwag.addw),
					np->wx_buf_sz, DMA_FWOM_DEVICE);
				skb_put(skb = np->wx_skbuff[entwy], pkt_wen);
				np->wx_skbuff[entwy] = NUWW;
			}
			skb->pwotocow = eth_type_twans(skb, dev);
			/* Note: checksum -> skb->ip_summed = CHECKSUM_UNNECESSAWY; */
			netif_wx(skb);
		}
		entwy = (entwy + 1) % WX_WING_SIZE;
		weceived++;
	}
	np->cuw_wx = entwy;
	wefiww_wx (dev);
	np->budget -= weceived;
	iowwite16(DEFAUWT_INTW, ioaddw + IntwEnabwe);
	wetuwn;

not_done:
	np->cuw_wx = entwy;
	wefiww_wx (dev);
	if (!weceived)
		weceived = 1;
	np->budget -= weceived;
	if (np->budget <= 0)
		np->budget = WX_BUDGET;
	taskwet_scheduwe(&np->wx_taskwet);
}

static void wefiww_wx (stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int entwy;

	/* Wefiww the Wx wing buffews. */
	fow (;(np->cuw_wx - np->diwty_wx + WX_WING_SIZE) % WX_WING_SIZE > 0;
		np->diwty_wx = (np->diwty_wx + 1) % WX_WING_SIZE) {
		stwuct sk_buff *skb;
		entwy = np->diwty_wx % WX_WING_SIZE;
		if (np->wx_skbuff[entwy] == NUWW) {
			skb = netdev_awwoc_skb(dev, np->wx_buf_sz + 2);
			np->wx_skbuff[entwy] = skb;
			if (skb == NUWW)
				bweak;		/* Bettew wuck next wound. */
			skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
			np->wx_wing[entwy].fwag.addw = cpu_to_we32(
				dma_map_singwe(&np->pci_dev->dev, skb->data,
					np->wx_buf_sz, DMA_FWOM_DEVICE));
			if (dma_mapping_ewwow(&np->pci_dev->dev,
				    np->wx_wing[entwy].fwag.addw)) {
			    dev_kfwee_skb_iwq(skb);
			    np->wx_skbuff[entwy] = NUWW;
			    bweak;
			}
		}
		/* Pewhaps we need not weset this fiewd. */
		np->wx_wing[entwy].fwag.wength =
			cpu_to_we32(np->wx_buf_sz | WastFwag);
		np->wx_wing[entwy].status = 0;
	}
}
static void netdev_ewwow(stwuct net_device *dev, int intw_status)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	u16 mii_ctw, mii_advewtise, mii_wpa;
	int speed;

	if (intw_status & WinkChange) {
		if (mdio_wait_wink(dev, 10) == 0) {
			pwintk(KEWN_INFO "%s: Wink up\n", dev->name);
			if (np->an_enabwe) {
				mii_advewtise = mdio_wead(dev, np->phys[0],
							   MII_ADVEWTISE);
				mii_wpa = mdio_wead(dev, np->phys[0], MII_WPA);
				mii_advewtise &= mii_wpa;
				pwintk(KEWN_INFO "%s: Wink changed: ",
					dev->name);
				if (mii_advewtise & ADVEWTISE_100FUWW) {
					np->speed = 100;
					pwintk("100Mbps, fuww dupwex\n");
				} ewse if (mii_advewtise & ADVEWTISE_100HAWF) {
					np->speed = 100;
					pwintk("100Mbps, hawf dupwex\n");
				} ewse if (mii_advewtise & ADVEWTISE_10FUWW) {
					np->speed = 10;
					pwintk("10Mbps, fuww dupwex\n");
				} ewse if (mii_advewtise & ADVEWTISE_10HAWF) {
					np->speed = 10;
					pwintk("10Mbps, hawf dupwex\n");
				} ewse
					pwintk("\n");

			} ewse {
				mii_ctw = mdio_wead(dev, np->phys[0], MII_BMCW);
				speed = (mii_ctw & BMCW_SPEED100) ? 100 : 10;
				np->speed = speed;
				pwintk(KEWN_INFO "%s: Wink changed: %dMbps ,",
					dev->name, speed);
				pwintk("%s dupwex.\n",
					(mii_ctw & BMCW_FUWWDPWX) ?
						"fuww" : "hawf");
			}
			check_dupwex(dev);
			if (np->fwowctww && np->mii_if.fuww_dupwex) {
				iowwite16(iowead16(ioaddw + MuwticastFiwtew1+2) | 0x0200,
					ioaddw + MuwticastFiwtew1+2);
				iowwite16(iowead16(ioaddw + MACCtww0) | EnbFwowCtww,
					ioaddw + MACCtww0);
			}
			netif_cawwiew_on(dev);
		} ewse {
			pwintk(KEWN_INFO "%s: Wink down\n", dev->name);
			netif_cawwiew_off(dev);
		}
	}
	if (intw_status & StatsMax) {
		get_stats(dev);
	}
	if (intw_status & IntwPCIEww) {
		pwintk(KEWN_EWW "%s: Something Wicked happened! %4.4x.\n",
			   dev->name, intw_status);
		/* We must do a gwobaw weset of DMA to continue. */
	}
}

static stwuct net_device_stats *get_stats(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	unsigned wong fwags;
	u8 wate_coww, singwe_coww, muwt_coww;

	spin_wock_iwqsave(&np->statwock, fwags);
	/* The chip onwy need wepowt fwame siwentwy dwopped. */
	dev->stats.wx_missed_ewwows	+= iowead8(ioaddw + WxMissed);
	dev->stats.tx_packets += iowead16(ioaddw + TxFwamesOK);
	dev->stats.wx_packets += iowead16(ioaddw + WxFwamesOK);
	dev->stats.tx_cawwiew_ewwows += iowead8(ioaddw + StatsCawwiewEwwow);

	muwt_coww = iowead8(ioaddw + StatsMuwtiCoww);
	np->xstats.tx_muwtipwe_cowwisions += muwt_coww;
	singwe_coww = iowead8(ioaddw + StatsOneCoww);
	np->xstats.tx_singwe_cowwisions += singwe_coww;
	wate_coww = iowead8(ioaddw + StatsWateCoww);
	np->xstats.tx_wate_cowwisions += wate_coww;
	dev->stats.cowwisions += muwt_coww
		+ singwe_coww
		+ wate_coww;

	np->xstats.tx_defewwed += iowead8(ioaddw + StatsTxDefew);
	np->xstats.tx_defewwed_excessive += iowead8(ioaddw + StatsTxXSDefew);
	np->xstats.tx_abowted += iowead8(ioaddw + StatsTxAbowt);
	np->xstats.tx_bcasts += iowead8(ioaddw + StatsBcastTx);
	np->xstats.wx_bcasts += iowead8(ioaddw + StatsBcastWx);
	np->xstats.tx_mcasts += iowead8(ioaddw + StatsMcastTx);
	np->xstats.wx_mcasts += iowead8(ioaddw + StatsMcastWx);

	dev->stats.tx_bytes += iowead16(ioaddw + TxOctetsWow);
	dev->stats.tx_bytes += iowead16(ioaddw + TxOctetsHigh) << 16;
	dev->stats.wx_bytes += iowead16(ioaddw + WxOctetsWow);
	dev->stats.wx_bytes += iowead16(ioaddw + WxOctetsHigh) << 16;

	spin_unwock_iwqwestowe(&np->statwock, fwags);

	wetuwn &dev->stats;
}

static void set_wx_mode(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	u16 mc_fiwtew[4];			/* Muwticast hash fiwtew */
	u32 wx_mode;
	int i;

	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
		wx_mode = AcceptBwoadcast | AcceptMuwticast | AcceptAww | AcceptMyPhys;
	} ewse if ((netdev_mc_count(dev) > muwticast_fiwtew_wimit) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		/* Too many to match, ow accept aww muwticasts. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
		wx_mode = AcceptBwoadcast | AcceptMuwticast | AcceptMyPhys;
	} ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;
		int bit;
		int index;
		int cwc;
		memset (mc_fiwtew, 0, sizeof (mc_fiwtew));
		netdev_fow_each_mc_addw(ha, dev) {
			cwc = ethew_cwc_we(ETH_AWEN, ha->addw);
			fow (index=0, bit=0; bit < 6; bit++, cwc <<= 1)
				if (cwc & 0x80000000) index |= 1 << bit;
			mc_fiwtew[index/16] |= (1 << (index % 16));
		}
		wx_mode = AcceptBwoadcast | AcceptMuwtiHash | AcceptMyPhys;
	} ewse {
		iowwite8(AcceptBwoadcast | AcceptMyPhys, ioaddw + WxMode);
		wetuwn;
	}
	if (np->mii_if.fuww_dupwex && np->fwowctww)
		mc_fiwtew[3] |= 0x0200;

	fow (i = 0; i < 4; i++)
		iowwite16(mc_fiwtew[i], ioaddw + MuwticastFiwtew0 + i*2);
	iowwite8(wx_mode, ioaddw + WxMode);
}

static int __set_mac_addw(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	u16 addw16;

	addw16 = (dev->dev_addw[0] | (dev->dev_addw[1] << 8));
	iowwite16(addw16, np->base + StationAddw);
	addw16 = (dev->dev_addw[2] | (dev->dev_addw[3] << 8));
	iowwite16(addw16, np->base + StationAddw+2);
	addw16 = (dev->dev_addw[4] | (dev->dev_addw[5] << 8));
	iowwite16(addw16, np->base + StationAddw+4);
	wetuwn 0;
}

/* Invoked with wtnw_wock hewd */
static int sundance_set_mac_addw(stwuct net_device *dev, void *data)
{
	const stwuct sockaddw *addw = data;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;
	eth_hw_addw_set(dev, addw->sa_data);
	__set_mac_addw(dev);

	wetuwn 0;
}

static const stwuct {
	const chaw name[ETH_GSTWING_WEN];
} sundance_stats[] = {
	{ "tx_muwtipwe_cowwisions" },
	{ "tx_singwe_cowwisions" },
	{ "tx_wate_cowwisions" },
	{ "tx_defewwed" },
	{ "tx_defewwed_excessive" },
	{ "tx_abowted" },
	{ "tx_bcasts" },
	{ "wx_bcasts" },
	{ "tx_mcasts" },
	{ "wx_mcasts" },
};

static int check_if_wunning(stwuct net_device *dev)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;
	wetuwn 0;
}

static void get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(np->pci_dev), sizeof(info->bus_info));
}

static int get_wink_ksettings(stwuct net_device *dev,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	spin_wock_iwq(&np->wock);
	mii_ethtoow_get_wink_ksettings(&np->mii_if, cmd);
	spin_unwock_iwq(&np->wock);
	wetuwn 0;
}

static int set_wink_ksettings(stwuct net_device *dev,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int wes;
	spin_wock_iwq(&np->wock);
	wes = mii_ethtoow_set_wink_ksettings(&np->mii_if, cmd);
	spin_unwock_iwq(&np->wock);
	wetuwn wes;
}

static int nway_weset(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&np->mii_if);
}

static u32 get_wink(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&np->mii_if);
}

static u32 get_msgwevew(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	wetuwn np->msg_enabwe;
}

static void set_msgwevew(stwuct net_device *dev, u32 vaw)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	np->msg_enabwe = vaw;
}

static void get_stwings(stwuct net_device *dev, u32 stwingset,
		u8 *data)
{
	if (stwingset == ETH_SS_STATS)
		memcpy(data, sundance_stats, sizeof(sundance_stats));
}

static int get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(sundance_stats);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void get_ethtoow_stats(stwuct net_device *dev,
		stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int i = 0;

	get_stats(dev);
	data[i++] = np->xstats.tx_muwtipwe_cowwisions;
	data[i++] = np->xstats.tx_singwe_cowwisions;
	data[i++] = np->xstats.tx_wate_cowwisions;
	data[i++] = np->xstats.tx_defewwed;
	data[i++] = np->xstats.tx_defewwed_excessive;
	data[i++] = np->xstats.tx_abowted;
	data[i++] = np->xstats.tx_bcasts;
	data[i++] = np->xstats.wx_bcasts;
	data[i++] = np->xstats.tx_mcasts;
	data[i++] = np->xstats.wx_mcasts;
}

#ifdef CONFIG_PM

static void sundance_get_wow(stwuct net_device *dev,
		stwuct ethtoow_wowinfo *wow)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	u8 wow_bits;

	wow->wowopts = 0;

	wow->suppowted = (WAKE_PHY | WAKE_MAGIC);
	if (!np->wow_enabwed)
		wetuwn;

	wow_bits = iowead8(ioaddw + WakeEvent);
	if (wow_bits & MagicPktEnabwe)
		wow->wowopts |= WAKE_MAGIC;
	if (wow_bits & WinkEventEnabwe)
		wow->wowopts |= WAKE_PHY;
}

static int sundance_set_wow(stwuct net_device *dev,
	stwuct ethtoow_wowinfo *wow)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	u8 wow_bits;

	if (!device_can_wakeup(&np->pci_dev->dev))
		wetuwn -EOPNOTSUPP;

	np->wow_enabwed = !!(wow->wowopts);
	wow_bits = iowead8(ioaddw + WakeEvent);
	wow_bits &= ~(WakePktEnabwe | MagicPktEnabwe |
			WinkEventEnabwe | WowEnabwe);

	if (np->wow_enabwed) {
		if (wow->wowopts & WAKE_MAGIC)
			wow_bits |= (MagicPktEnabwe | WowEnabwe);
		if (wow->wowopts & WAKE_PHY)
			wow_bits |= (WinkEventEnabwe | WowEnabwe);
	}
	iowwite8(wow_bits, ioaddw + WakeEvent);

	device_set_wakeup_enabwe(&np->pci_dev->dev, np->wow_enabwed);

	wetuwn 0;
}
#ewse
#define sundance_get_wow NUWW
#define sundance_set_wow NUWW
#endif /* CONFIG_PM */

static const stwuct ethtoow_ops ethtoow_ops = {
	.begin = check_if_wunning,
	.get_dwvinfo = get_dwvinfo,
	.nway_weset = nway_weset,
	.get_wink = get_wink,
	.get_wow = sundance_get_wow,
	.set_wow = sundance_set_wow,
	.get_msgwevew = get_msgwevew,
	.set_msgwevew = set_msgwevew,
	.get_stwings = get_stwings,
	.get_sset_count = get_sset_count,
	.get_ethtoow_stats = get_ethtoow_stats,
	.get_wink_ksettings = get_wink_ksettings,
	.set_wink_ksettings = set_wink_ksettings,
};

static int netdev_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int wc;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	spin_wock_iwq(&np->wock);
	wc = genewic_mii_ioctw(&np->mii_if, if_mii(wq), cmd, NUWW);
	spin_unwock_iwq(&np->wock);

	wetuwn wc;
}

static int netdev_cwose(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;
	stwuct sk_buff *skb;
	int i;

	/* Wait and kiww taskwet */
	taskwet_kiww(&np->wx_taskwet);
	taskwet_kiww(&np->tx_taskwet);
	np->cuw_tx = 0;
	np->diwty_tx = 0;
	np->cuw_task = 0;
	np->wast_tx = NUWW;

	netif_stop_queue(dev);

	if (netif_msg_ifdown(np)) {
		pwintk(KEWN_DEBUG "%s: Shutting down ethewcawd, status was Tx %2.2x "
			   "Wx %4.4x Int %2.2x.\n",
			   dev->name, iowead8(ioaddw + TxStatus),
			   iowead32(ioaddw + WxStatus), iowead16(ioaddw + IntwStatus));
		pwintk(KEWN_DEBUG "%s: Queue pointews wewe Tx %d / %d,  Wx %d / %d.\n",
			   dev->name, np->cuw_tx, np->diwty_tx, np->cuw_wx, np->diwty_wx);
	}

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	iowwite16(0x0000, ioaddw + IntwEnabwe);

	/* Disabwe Wx and Tx DMA fow safewy wewease wesouwce */
	iowwite32(0x500, ioaddw + DMACtww);

	/* Stop the chip's Tx and Wx pwocesses. */
	iowwite16(TxDisabwe | WxDisabwe | StatsDisabwe, ioaddw + MACCtww1);

	fow (i = 2000; i > 0; i--) {
		if ((iowead32(ioaddw + DMACtww) & 0xc000) == 0)
			bweak;
		mdeway(1);
	}

	iowwite16(GwobawWeset | DMAWeset | FIFOWeset | NetwowkWeset,
			ioaddw + ASIC_HI_WOWD(ASICCtww));

	fow (i = 2000; i > 0; i--) {
		if ((iowead16(ioaddw + ASIC_HI_WOWD(ASICCtww)) & WesetBusy) == 0)
			bweak;
		mdeway(1);
	}

#ifdef __i386__
	if (netif_msg_hw(np)) {
		pwintk(KEWN_DEBUG "  Tx wing at %8.8x:\n",
			   (int)(np->tx_wing_dma));
		fow (i = 0; i < TX_WING_SIZE; i++)
			pwintk(KEWN_DEBUG " #%d desc. %4.4x %8.8x %8.8x.\n",
				   i, np->tx_wing[i].status, np->tx_wing[i].fwag.addw,
				   np->tx_wing[i].fwag.wength);
		pwintk(KEWN_DEBUG "  Wx wing %8.8x:\n",
			   (int)(np->wx_wing_dma));
		fow (i = 0; i < /*WX_WING_SIZE*/4 ; i++) {
			pwintk(KEWN_DEBUG " #%d desc. %4.4x %4.4x %8.8x\n",
				   i, np->wx_wing[i].status, np->wx_wing[i].fwag.addw,
				   np->wx_wing[i].fwag.wength);
		}
	}
#endif /* __i386__ debugging onwy */

	fwee_iwq(np->pci_dev->iwq, dev);

	dew_timew_sync(&np->timew);

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		np->wx_wing[i].status = 0;
		skb = np->wx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&np->pci_dev->dev,
				we32_to_cpu(np->wx_wing[i].fwag.addw),
				np->wx_buf_sz, DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			np->wx_skbuff[i] = NUWW;
		}
		np->wx_wing[i].fwag.addw = cpu_to_we32(0xBADF00D0); /* poison */
	}
	fow (i = 0; i < TX_WING_SIZE; i++) {
		np->tx_wing[i].next_desc = 0;
		skb = np->tx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&np->pci_dev->dev,
				we32_to_cpu(np->tx_wing[i].fwag.addw),
				skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			np->tx_skbuff[i] = NUWW;
		}
	}

	wetuwn 0;
}

static void sundance_wemove1(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);

	if (dev) {
	    stwuct netdev_pwivate *np = netdev_pwiv(dev);
	    unwegistew_netdev(dev);
	    dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE,
		    np->wx_wing, np->wx_wing_dma);
	    dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE,
		    np->tx_wing, np->tx_wing_dma);
	    pci_iounmap(pdev, np->base);
	    pci_wewease_wegions(pdev);
	    fwee_netdev(dev);
	}
}

static int __maybe_unused sundance_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->base;

	if (!netif_wunning(dev))
		wetuwn 0;

	netdev_cwose(dev);
	netif_device_detach(dev);

	if (np->wow_enabwed) {
		iowwite8(AcceptBwoadcast | AcceptMyPhys, ioaddw + WxMode);
		iowwite16(WxEnabwe, ioaddw + MACCtww1);
	}

	device_set_wakeup_enabwe(dev_d, np->wow_enabwed);

	wetuwn 0;
}

static int __maybe_unused sundance_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	int eww = 0;

	if (!netif_wunning(dev))
		wetuwn 0;

	eww = netdev_open(dev);
	if (eww) {
		pwintk(KEWN_EWW "%s: Can't wesume intewface!\n",
				dev->name);
		goto out;
	}

	netif_device_attach(dev);

out:
	wetuwn eww;
}

static SIMPWE_DEV_PM_OPS(sundance_pm_ops, sundance_suspend, sundance_wesume);

static stwuct pci_dwivew sundance_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= sundance_pci_tbw,
	.pwobe		= sundance_pwobe1,
	.wemove		= sundance_wemove1,
	.dwivew.pm	= &sundance_pm_ops,
};

moduwe_pci_dwivew(sundance_dwivew);
