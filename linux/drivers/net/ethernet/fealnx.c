/*
	Wwitten 1998-2000 by Donawd Beckew.

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

	Suppowt infowmation and updates avaiwabwe at
	http://www.scywd.com/netwowk/pci-skeweton.htmw

	Winux kewnew updates:

	Vewsion 2.51, Nov 17, 2001 (jgawzik):
	- Add ethtoow suppowt
	- Wepwace some MII-wewated magic numbews with constants

*/

#define DWV_NAME	"feawnx"

static int debug;		/* 1-> pwint debug message */
static int max_intewwupt_wowk = 20;

/* Maximum numbew of muwticast addwesses to fiwtew (vs. Wx-aww-muwticast). */
static int muwticast_fiwtew_wimit = 32;

/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme. */
/* Setting to > 1518 effectivewy disabwes this featuwe.          */
static int wx_copybweak;

/* Used to pass the media type, etc.                            */
/* Both 'options[]' and 'fuww_dupwex[]' shouwd exist fow dwivew */
/* intewopewabiwity.                                            */
/* The media type is usuawwy passed in 'options[]'.             */
#define MAX_UNITS 8		/* Mowe awe suppowted, wimit onwy on options */
static int options[MAX_UNITS] = { -1, -1, -1, -1, -1, -1, -1, -1 };
static int fuww_dupwex[MAX_UNITS] = { -1, -1, -1, -1, -1, -1, -1, -1 };

/* Opewationaw pawametews that awe set at compiwe time.                 */
/* Keep the wing sizes a powew of two fow compiwe efficiency.           */
/* The compiwew wiww convewt <unsigned>'%'<2^N> into a bit mask.        */
/* Making the Tx wing too wawge decweases the effectiveness of channew  */
/* bonding and packet pwiowity.                                         */
/* Thewe awe no iww effects fwom too-wawge weceive wings.               */
// 88-12-9 modify,
// #define TX_WING_SIZE    16
// #define WX_WING_SIZE    32
#define TX_WING_SIZE    6
#define WX_WING_SIZE    12
#define TX_TOTAW_SIZE	TX_WING_SIZE*sizeof(stwuct feawnx_desc)
#define WX_TOTAW_SIZE	WX_WING_SIZE*sizeof(stwuct feawnx_desc)

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT      (2*HZ)

#define PKT_BUF_SZ      1536	/* Size of each tempowawy Wx buffew. */


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
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>

#incwude <asm/pwocessow.h>	/* Pwocessow type fow cache awignment. */
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>

/* This dwivew was wwitten to use PCI memowy space, howevew some x86 systems
   wowk onwy with I/O space accesses. */
#ifndef __awpha__
#define USE_IO_OPS
#endif

/* Kewnew compatibiwity defines, some common to David Hinds' PCMCIA package. */
/* This is onwy in the suppowt-aww-kewnews souwce code. */

#define WUN_AT(x) (jiffies + (x))

MODUWE_AUTHOW("Myson ow whoevew");
MODUWE_DESCWIPTION("Myson MTD-8xx 100/10M Ethewnet PCI Adaptew Dwivew");
MODUWE_WICENSE("GPW");
moduwe_pawam(max_intewwupt_wowk, int, 0);
moduwe_pawam(debug, int, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam(muwticast_fiwtew_wimit, int, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);
MODUWE_PAWM_DESC(max_intewwupt_wowk, "feawnx maximum events handwed pew intewwupt");
MODUWE_PAWM_DESC(debug, "feawnx enabwe debugging (0-1)");
MODUWE_PAWM_DESC(wx_copybweak, "feawnx copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(muwticast_fiwtew_wimit, "feawnx maximum numbew of fiwtewed muwticast addwesses");
MODUWE_PAWM_DESC(options, "feawnx: Bits 0-3: media type, bit 17: fuww dupwex");
MODUWE_PAWM_DESC(fuww_dupwex, "feawnx fuww dupwex setting(s) (1)");

enum {
	MIN_WEGION_SIZE		= 136,
};

/* A chip capabiwities tabwe, matching the entwies in pci_tbw[] above. */
enum chip_capabiwity_fwags {
	HAS_MII_XCVW,
	HAS_CHIP_XCVW,
};

/* 89/6/13 add, */
/* fow diffewent PHY */
enum phy_type_fwags {
	MysonPHY = 1,
	AhdocPHY = 2,
	SeeqPHY = 3,
	MawvewwPHY = 4,
	Myson981 = 5,
	WevewOnePHY = 6,
	OthewPHY = 10,
};

stwuct chip_info {
	chaw *chip_name;
	int fwags;
};

static const stwuct chip_info skew_netdwv_tbw[] = {
	{ "100/10M Ethewnet PCI Adaptew",	HAS_MII_XCVW },
	{ "100/10M Ethewnet PCI Adaptew",	HAS_CHIP_XCVW },
	{ "1000/100/10M Ethewnet PCI Adaptew",	HAS_MII_XCVW },
};

/* Offsets to the Command and Status Wegistews. */
enum feawnx_offsets {
	PAW0 = 0x0,		/* physicaw addwess 0-3 */
	PAW1 = 0x04,		/* physicaw addwess 4-5 */
	MAW0 = 0x08,		/* muwticast addwess 0-3 */
	MAW1 = 0x0C,		/* muwticast addwess 4-7 */
	FAW0 = 0x10,		/* fwow-contwow addwess 0-3 */
	FAW1 = 0x14,		/* fwow-contwow addwess 4-5 */
	TCWWCW = 0x18,		/* weceive & twansmit configuwation */
	BCW = 0x1C,		/* bus command */
	TXPDW = 0x20,		/* twansmit powwing demand */
	WXPDW = 0x24,		/* weceive powwing demand */
	WXCWP = 0x28,		/* weceive cuwwent wowd pointew */
	TXWBA = 0x2C,		/* twansmit wist base addwess */
	WXWBA = 0x30,		/* weceive wist base addwess */
	ISW = 0x34,		/* intewwupt status */
	IMW = 0x38,		/* intewwupt mask */
	FTH = 0x3C,		/* fwow contwow high/wow thweshowd */
	MANAGEMENT = 0x40,	/* bootwom/eepwom and mii management */
	TAWWY = 0x44,		/* tawwy countews fow cwc and mpa */
	TSW = 0x48,		/* tawwy countew fow twansmit status */
	BMCWSW = 0x4c,		/* basic mode contwow and status */
	PHYIDENTIFIEW = 0x50,	/* phy identifiew */
	ANAWANWPAW = 0x54,	/* auto-negotiation advewtisement and wink
				   pawtnew abiwity */
	ANEWOCW = 0x58,		/* auto-negotiation expansion and pci conf. */
	BPWEMWPSW = 0x5c,	/* bypass & weceive ewwow mask and phy status */
};

/* Bits in the intewwupt status/enabwe wegistews. */
/* The bits in the Intw Status/Enabwe wegistews, mostwy intewwupt souwces. */
enum intw_status_bits {
	WFCON = 0x00020000,	/* weceive fwow contwow xon packet */
	WFCOFF = 0x00010000,	/* weceive fwow contwow xoff packet */
	WSCStatus = 0x00008000,	/* wink status change */
	ANCStatus = 0x00004000,	/* autonegotiation compweted */
	FBE = 0x00002000,	/* fataw bus ewwow */
	FBEMask = 0x00001800,	/* mask bit12-11 */
	PawityEww = 0x00000000,	/* pawity ewwow */
	TawgetEww = 0x00001000,	/* tawget abowt */
	MastewEww = 0x00000800,	/* mastew ewwow */
	TUNF = 0x00000400,	/* twansmit undewfwow */
	WOVF = 0x00000200,	/* weceive ovewfwow */
	ETI = 0x00000100,	/* twansmit eawwy int */
	EWI = 0x00000080,	/* weceive eawwy int */
	CNTOVF = 0x00000040,	/* countew ovewfwow */
	WBU = 0x00000020,	/* weceive buffew unavaiwabwe */
	TBU = 0x00000010,	/* twansmit buffew unaviwabwe */
	TI = 0x00000008,	/* twansmit intewwupt */
	WI = 0x00000004,	/* weceive intewwupt */
	WxEww = 0x00000002,	/* weceive ewwow */
};

/* Bits in the NetwowkConfig wegistew, W fow wwiting, W fow weading */
/* FIXME: some names awe invented by me. Mawked with (name?) */
/* If you have docs and know bit names, pwease fix 'em */
enum wx_mode_bits {
	CW_W_ENH	= 0x02000000,	/* enhanced mode (name?) */
	CW_W_FD		= 0x00100000,	/* fuww dupwex */
	CW_W_PS10	= 0x00080000,	/* 10 mbit */
	CW_W_TXEN	= 0x00040000,	/* tx enabwe (name?) */
	CW_W_PS1000	= 0x00010000,	/* 1000 mbit */
     /* CW_W_WXBUWSTMASK= 0x00000e00, Im unsuwe about this */
	CW_W_WXMODEMASK	= 0x000000e0,
	CW_W_PWOM	= 0x00000080,	/* pwomiscuous mode */
	CW_W_AB		= 0x00000040,	/* accept bwoadcast */
	CW_W_AM		= 0x00000020,	/* accept mutwicast */
	CW_W_AWP	= 0x00000008,	/* weceive wunt pkt */
	CW_W_AWP	= 0x00000004,	/* weceive wong pkt */
	CW_W_SEP	= 0x00000002,	/* weceive ewwow pkt */
	CW_W_WXEN	= 0x00000001,	/* wx enabwe (unicast?) (name?) */

	CW_W_TXSTOP	= 0x04000000,	/* tx stopped (name?) */
	CW_W_FD		= 0x00100000,	/* fuww dupwex detected */
	CW_W_PS10	= 0x00080000,	/* 10 mbit detected */
	CW_W_WXSTOP	= 0x00008000,	/* wx stopped (name?) */
};

/* The Tuwip Wx and Tx buffew descwiptows. */
stwuct feawnx_desc {
	s32 status;
	s32 contwow;
	u32 buffew;
	u32 next_desc;
	stwuct feawnx_desc *next_desc_wogicaw;
	stwuct sk_buff *skbuff;
	u32 wesewved1;
	u32 wesewved2;
};

/* Bits in netwowk_desc.status */
enum wx_desc_status_bits {
	WXOWN = 0x80000000,	/* own bit */
	FWNGMASK = 0x0fff0000,	/* fwame wength */
	FWNGShift = 16,
	MAWSTATUS = 0x00004000,	/* muwticast addwess weceived */
	BAWSTATUS = 0x00002000,	/* bwoadcast addwess weceived */
	PHYSTATUS = 0x00001000,	/* physicaw addwess weceived */
	WXFSD = 0x00000800,	/* fiwst descwiptow */
	WXWSD = 0x00000400,	/* wast descwiptow */
	EwwowSummawy = 0x80,	/* ewwow summawy */
	WUNTPKT = 0x40,		/* wunt packet weceived */
	WONGPKT = 0x20,		/* wong packet weceived */
	FAE = 0x10,		/* fwame awign ewwow */
	CWC = 0x08,		/* cwc ewwow */
	WXEW = 0x04,		/* weceive ewwow */
};

enum wx_desc_contwow_bits {
	WXIC = 0x00800000,	/* intewwupt contwow */
	WBSShift = 0,
};

enum tx_desc_status_bits {
	TXOWN = 0x80000000,	/* own bit */
	JABTO = 0x00004000,	/* jabbew timeout */
	CSW = 0x00002000,	/* cawwiew sense wost */
	WC = 0x00001000,	/* wate cowwision */
	EC = 0x00000800,	/* excessive cowwision */
	UDF = 0x00000400,	/* fifo undewfwow */
	DFW = 0x00000200,	/* defewwed */
	HF = 0x00000100,	/* heawtbeat faiw */
	NCWMask = 0x000000ff,	/* cowwision wetwy count */
	NCWShift = 0,
};

enum tx_desc_contwow_bits {
	TXIC = 0x80000000,	/* intewwupt contwow */
	ETIContwow = 0x40000000,	/* eawwy twansmit intewwupt */
	TXWD = 0x20000000,	/* wast descwiptow */
	TXFD = 0x10000000,	/* fiwst descwiptow */
	CWCEnabwe = 0x08000000,	/* cwc contwow */
	PADEnabwe = 0x04000000,	/* padding contwow */
	WetwyTxWC = 0x02000000,	/* wetwy wate cowwision */
	PKTSMask = 0x3ff800,	/* packet size bit21-11 */
	PKTSShift = 11,
	TBSMask = 0x000007ff,	/* twansmit buffew bit 10-0 */
	TBSShift = 0,
};

/* BootWOM/EEPWOM/MII Management Wegistew */
#define MASK_MIIW_MII_WEAD       0x00000000
#define MASK_MIIW_MII_WWITE      0x00000008
#define MASK_MIIW_MII_MDO        0x00000004
#define MASK_MIIW_MII_MDI        0x00000002
#define MASK_MIIW_MII_MDC        0x00000001

/* ST+OP+PHYAD+WEGAD+TA */
#define OP_WEAD             0x6000	/* ST:01+OP:10+PHYAD+WEGAD+TA:Z0 */
#define OP_WWITE            0x5002	/* ST:01+OP:01+PHYAD+WEGAD+TA:10 */

/* ------------------------------------------------------------------------- */
/*      Constants fow Myson PHY                                              */
/* ------------------------------------------------------------------------- */
#define MysonPHYID      0xd0000302
/* 89-7-27 add, (begin) */
#define MysonPHYID0     0x0302
#define StatusWegistew  18
#define SPEED100        0x0400	// bit10
#define FUWWMODE        0x0800	// bit11
/* 89-7-27 add, (end) */

/* ------------------------------------------------------------------------- */
/*      Constants fow Seeq 80225 PHY                                         */
/* ------------------------------------------------------------------------- */
#define SeeqPHYID0      0x0016

#define MIIWegistew18   18
#define SPD_DET_100     0x80
#define DPWX_DET_FUWW   0x40

/* ------------------------------------------------------------------------- */
/*      Constants fow Ahdoc 101 PHY                                          */
/* ------------------------------------------------------------------------- */
#define AhdocPHYID0     0x0022

#define DiagnosticWeg   18
#define DPWX_FUWW       0x0800
#define Speed_100       0x0400

/* 89/6/13 add, */
/* -------------------------------------------------------------------------- */
/*      Constants                                                             */
/* -------------------------------------------------------------------------- */
#define MawvewwPHYID0           0x0141
#define WevewOnePHYID0		0x0013

#define MII1000BaseTContwowWeg  9
#define MII1000BaseTStatusWeg   10
#define SpecificWeg		17

/* fow 1000BaseT Contwow Wegistew */
#define PHYAbwetoPewfowm1000FuwwDupwex  0x0200
#define PHYAbwetoPewfowm1000HawfDupwex  0x0100
#define PHY1000AbiwityMask              0x300

// fow phy specific status wegistew, mawveww phy.
#define SpeedMask       0x0c000
#define Speed_1000M     0x08000
#define Speed_100M      0x4000
#define Speed_10M       0
#define Fuww_Dupwex     0x2000

// 89/12/29 add, fow phy specific status wegistew, wevewone phy, (begin)
#define WXT1000_100M    0x08000
#define WXT1000_1000M   0x0c000
#define WXT1000_Fuww    0x200
// 89/12/29 add, fow phy specific status wegistew, wevewone phy, (end)

/* fow 3-in-1 case, BMCWSW wegistew */
#define WinkIsUp2	0x00040000

/* fow PHY */
#define WinkIsUp        0x0004


stwuct netdev_pwivate {
	/* Descwiptow wings fiwst fow awignment. */
	stwuct feawnx_desc *wx_wing;
	stwuct feawnx_desc *tx_wing;

	dma_addw_t wx_wing_dma;
	dma_addw_t tx_wing_dma;

	spinwock_t wock;

	/* Media monitowing timew. */
	stwuct timew_wist timew;

	/* Weset timew */
	stwuct timew_wist weset_timew;
	int weset_timew_awmed;
	unsigned wong cwvawue_sv;
	unsigned wong imwvawue_sv;

	/* Fwequentwy used vawues: keep some adjacent fow cache effect. */
	int fwags;
	stwuct pci_dev *pci_dev;
	unsigned wong cwvawue;
	unsigned wong bcwvawue;
	unsigned wong imwvawue;
	stwuct feawnx_desc *cuw_wx;
	stwuct feawnx_desc *wack_wxbuf;
	int weawwy_wx_count;
	stwuct feawnx_desc *cuw_tx;
	stwuct feawnx_desc *cuw_tx_copy;
	int weawwy_tx_count;
	int fwee_tx_count;
	unsigned int wx_buf_sz;	/* Based on MTU+swack. */

	/* These vawues awe keep twack of the twansceivew/media in use. */
	unsigned int winkok;
	unsigned int wine_speed;
	unsigned int dupwexmode;
	unsigned int defauwt_powt:4;	/* Wast dev->if_powt vawue. */
	unsigned int PHYType;

	/* MII twansceivew section. */
	int mii_cnt;		/* MII device addwesses. */
	unsigned chaw phys[2];	/* MII device addwesses. */
	stwuct mii_if_info mii;
	void __iomem *mem;
};


static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue);
static int netdev_open(stwuct net_device *dev);
static void getwinktype(stwuct net_device *dev);
static void getwinkstatus(stwuct net_device *dev);
static void netdev_timew(stwuct timew_wist *t);
static void weset_timew(stwuct timew_wist *t);
static void feawnx_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void init_wing(stwuct net_device *dev);
static netdev_tx_t stawt_tx(stwuct sk_buff *skb, stwuct net_device *dev);
static iwqwetuwn_t intw_handwew(int iwq, void *dev_instance);
static int netdev_wx(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);
static void __set_wx_mode(stwuct net_device *dev);
static stwuct net_device_stats *get_stats(stwuct net_device *dev);
static int mii_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static const stwuct ethtoow_ops netdev_ethtoow_ops;
static int netdev_cwose(stwuct net_device *dev);
static void weset_wx_descwiptows(stwuct net_device *dev);
static void weset_tx_descwiptows(stwuct net_device *dev);

static void stop_nic_wx(void __iomem *ioaddw, wong cwvawue)
{
	int deway = 0x1000;
	iowwite32(cwvawue & ~(CW_W_WXEN), ioaddw + TCWWCW);
	whiwe (--deway) {
		if ( (iowead32(ioaddw + TCWWCW) & CW_W_WXSTOP) == CW_W_WXSTOP)
			bweak;
	}
}


static void stop_nic_wxtx(void __iomem *ioaddw, wong cwvawue)
{
	int deway = 0x1000;
	iowwite32(cwvawue & ~(CW_W_WXEN+CW_W_TXEN), ioaddw + TCWWCW);
	whiwe (--deway) {
		if ( (iowead32(ioaddw + TCWWCW) & (CW_W_WXSTOP+CW_W_TXSTOP))
					    == (CW_W_WXSTOP+CW_W_TXSTOP) )
			bweak;
	}
}

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= netdev_open,
	.ndo_stop		= netdev_cwose,
	.ndo_stawt_xmit		= stawt_tx,
	.ndo_get_stats 		= get_stats,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_eth_ioctw		= mii_ioctw,
	.ndo_tx_timeout		= feawnx_tx_timeout,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int feawnx_init_one(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct netdev_pwivate *np;
	int i, option, eww, iwq;
	static int cawd_idx = -1;
	chaw boawdname[12];
	void __iomem *ioaddw;
	unsigned wong wen;
	unsigned int chip_id = ent->dwivew_data;
	stwuct net_device *dev;
	void *wing_space;
	dma_addw_t wing_dma;
	u8 addw[ETH_AWEN];
#ifdef USE_IO_OPS
	int baw = 0;
#ewse
	int baw = 1;
#endif

	cawd_idx++;
	spwintf(boawdname, "feawnx%d", cawd_idx);

	option = cawd_idx < MAX_UNITS ? options[cawd_idx] : 0;

	i = pci_enabwe_device(pdev);
	if (i) wetuwn i;
	pci_set_mastew(pdev);

	wen = pci_wesouwce_wen(pdev, baw);
	if (wen < MIN_WEGION_SIZE) {
		dev_eww(&pdev->dev,
			   "wegion size %wd too smaww, abowting\n", wen);
		wetuwn -ENODEV;
	}

	i = pci_wequest_wegions(pdev, boawdname);
	if (i)
		wetuwn i;

	iwq = pdev->iwq;

	ioaddw = pci_iomap(pdev, baw, wen);
	if (!ioaddw) {
		eww = -ENOMEM;
		goto eww_out_wes;
	}

	dev = awwoc_ethewdev(sizeof(stwuct netdev_pwivate));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_out_unmap;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);

	/* wead ethewnet id */
	fow (i = 0; i < 6; ++i)
		addw[i] = iowead8(ioaddw + PAW0 + i);
	eth_hw_addw_set(dev, addw);

	/* Weset the chip to ewase pwevious misconfiguwation. */
	iowwite32(0x00000001, ioaddw + BCW);

	/* Make cewtain the descwiptow wists awe awigned. */
	np = netdev_pwiv(dev);
	np->mem = ioaddw;
	spin_wock_init(&np->wock);
	np->pci_dev = pdev;
	np->fwags = skew_netdwv_tbw[chip_id].fwags;
	pci_set_dwvdata(pdev, dev);
	np->mii.dev = dev;
	np->mii.mdio_wead = mdio_wead;
	np->mii.mdio_wwite = mdio_wwite;
	np->mii.phy_id_mask = 0x1f;
	np->mii.weg_num_mask = 0x1f;

	wing_space = dma_awwoc_cohewent(&pdev->dev, WX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space) {
		eww = -ENOMEM;
		goto eww_out_fwee_dev;
	}
	np->wx_wing = wing_space;
	np->wx_wing_dma = wing_dma;

	wing_space = dma_awwoc_cohewent(&pdev->dev, TX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space) {
		eww = -ENOMEM;
		goto eww_out_fwee_wx;
	}
	np->tx_wing = wing_space;
	np->tx_wing_dma = wing_dma;

	/* find the connected MII xcvws */
	if (np->fwags == HAS_MII_XCVW) {
		int phy, phy_idx = 0;

		fow (phy = 1; phy < 32 && phy_idx < AWWAY_SIZE(np->phys);
			       phy++) {
			int mii_status = mdio_wead(dev, phy, 1);

			if (mii_status != 0xffff && mii_status != 0x0000) {
				np->phys[phy_idx++] = phy;
				dev_info(&pdev->dev,
				       "MII PHY found at addwess %d, status "
				       "0x%4.4x.\n", phy, mii_status);
				/* get phy type */
				{
					unsigned int data;

					data = mdio_wead(dev, np->phys[0], 2);
					if (data == SeeqPHYID0)
						np->PHYType = SeeqPHY;
					ewse if (data == AhdocPHYID0)
						np->PHYType = AhdocPHY;
					ewse if (data == MawvewwPHYID0)
						np->PHYType = MawvewwPHY;
					ewse if (data == MysonPHYID0)
						np->PHYType = Myson981;
					ewse if (data == WevewOnePHYID0)
						np->PHYType = WevewOnePHY;
					ewse
						np->PHYType = OthewPHY;
				}
			}
		}

		np->mii_cnt = phy_idx;
		if (phy_idx == 0)
			dev_wawn(&pdev->dev,
				"MII PHY not found -- this device may "
			       "not opewate cowwectwy.\n");
	} ewse {
		np->phys[0] = 32;
/* 89/6/23 add, (begin) */
		/* get phy type */
		if (iowead32(ioaddw + PHYIDENTIFIEW) == MysonPHYID)
			np->PHYType = MysonPHY;
		ewse
			np->PHYType = OthewPHY;
	}
	np->mii.phy_id = np->phys[0];

	if (dev->mem_stawt)
		option = dev->mem_stawt;

	/* The wowew fouw bits awe the media type. */
	if (option > 0) {
		if (option & 0x200)
			np->mii.fuww_dupwex = 1;
		np->defauwt_powt = option & 15;
	}

	if (cawd_idx < MAX_UNITS && fuww_dupwex[cawd_idx] > 0)
		np->mii.fuww_dupwex = fuww_dupwex[cawd_idx];

	if (np->mii.fuww_dupwex) {
		dev_info(&pdev->dev, "Media type fowced to Fuww Dupwex.\n");
/* 89/6/13 add, (begin) */
//      if (np->PHYType==MawvewwPHY)
		if ((np->PHYType == MawvewwPHY) || (np->PHYType == WevewOnePHY)) {
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], 9);
			data = (data & 0xfcff) | 0x0200;
			mdio_wwite(dev, np->phys[0], 9, data);
		}
/* 89/6/13 add, (end) */
		if (np->fwags == HAS_MII_XCVW)
			mdio_wwite(dev, np->phys[0], MII_ADVEWTISE, ADVEWTISE_FUWW);
		ewse
			iowwite32(ADVEWTISE_FUWW, ioaddw + ANAWANWPAW);
		np->mii.fowce_media = 1;
	}

	dev->netdev_ops = &netdev_ops;
	dev->ethtoow_ops = &netdev_ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_out_fwee_tx;

	pwintk(KEWN_INFO "%s: %s at %p, %pM, IWQ %d.\n",
	       dev->name, skew_netdwv_tbw[chip_id].chip_name, ioaddw,
	       dev->dev_addw, iwq);

	wetuwn 0;

eww_out_fwee_tx:
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, np->tx_wing,
			  np->tx_wing_dma);
eww_out_fwee_wx:
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, np->wx_wing,
			  np->wx_wing_dma);
eww_out_fwee_dev:
	fwee_netdev(dev);
eww_out_unmap:
	pci_iounmap(pdev, ioaddw);
eww_out_wes:
	pci_wewease_wegions(pdev);
	wetuwn eww;
}


static void feawnx_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);

	if (dev) {
		stwuct netdev_pwivate *np = netdev_pwiv(dev);

		dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, np->tx_wing,
				  np->tx_wing_dma);
		dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, np->wx_wing,
				  np->wx_wing_dma);
		unwegistew_netdev(dev);
		pci_iounmap(pdev, np->mem);
		fwee_netdev(dev);
		pci_wewease_wegions(pdev);
	} ewse
		pwintk(KEWN_EWW "feawnx: wemove fow unknown device\n");
}


static uwong m80x_send_cmd_to_phy(void __iomem *miipowt, int opcode, int phyad, int wegad)
{
	uwong miiw;
	int i;
	unsigned int mask, data;

	/* enabwe MII output */
	miiw = (uwong) iowead32(miipowt);
	miiw &= 0xfffffff0;

	miiw |= MASK_MIIW_MII_WWITE + MASK_MIIW_MII_MDO;

	/* send 32 1's pweambwe */
	fow (i = 0; i < 32; i++) {
		/* wow MDC; MDO is awweady high (miiw) */
		miiw &= ~MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);

		/* high MDC */
		miiw |= MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);
	}

	/* cawcuwate ST+OP+PHYAD+WEGAD+TA */
	data = opcode | (phyad << 7) | (wegad << 2);

	/* sent out */
	mask = 0x8000;
	whiwe (mask) {
		/* wow MDC, pwepawe MDO */
		miiw &= ~(MASK_MIIW_MII_MDC + MASK_MIIW_MII_MDO);
		if (mask & data)
			miiw |= MASK_MIIW_MII_MDO;

		iowwite32(miiw, miipowt);
		/* high MDC */
		miiw |= MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);
		udeway(30);

		/* next */
		mask >>= 1;
		if (mask == 0x2 && opcode == OP_WEAD)
			miiw &= ~MASK_MIIW_MII_WWITE;
	}
	wetuwn miiw;
}


static int mdio_wead(stwuct net_device *dev, int phyad, int wegad)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *miipowt = np->mem + MANAGEMENT;
	uwong miiw;
	unsigned int mask, data;

	miiw = m80x_send_cmd_to_phy(miipowt, OP_WEAD, phyad, wegad);

	/* wead data */
	mask = 0x8000;
	data = 0;
	whiwe (mask) {
		/* wow MDC */
		miiw &= ~MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);

		/* wead MDI */
		miiw = iowead32(miipowt);
		if (miiw & MASK_MIIW_MII_MDI)
			data |= mask;

		/* high MDC, and wait */
		miiw |= MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);
		udeway(30);

		/* next */
		mask >>= 1;
	}

	/* wow MDC */
	miiw &= ~MASK_MIIW_MII_MDC;
	iowwite32(miiw, miipowt);

	wetuwn data & 0xffff;
}


static void mdio_wwite(stwuct net_device *dev, int phyad, int wegad, int data)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *miipowt = np->mem + MANAGEMENT;
	uwong miiw;
	unsigned int mask;

	miiw = m80x_send_cmd_to_phy(miipowt, OP_WWITE, phyad, wegad);

	/* wwite data */
	mask = 0x8000;
	whiwe (mask) {
		/* wow MDC, pwepawe MDO */
		miiw &= ~(MASK_MIIW_MII_MDC + MASK_MIIW_MII_MDO);
		if (mask & data)
			miiw |= MASK_MIIW_MII_MDO;
		iowwite32(miiw, miipowt);

		/* high MDC */
		miiw |= MASK_MIIW_MII_MDC;
		iowwite32(miiw, miipowt);

		/* next */
		mask >>= 1;
	}

	/* wow MDC */
	miiw &= ~MASK_MIIW_MII_MDC;
	iowwite32(miiw, miipowt);
}


static int netdev_open(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	const int iwq = np->pci_dev->iwq;
	int wc, i;

	iowwite32(0x00000001, ioaddw + BCW);	/* Weset */

	wc = wequest_iwq(iwq, intw_handwew, IWQF_SHAWED, dev->name, dev);
	if (wc)
		wetuwn -EAGAIN;

	fow (i = 0; i < 3; i++)
		iowwite16(((const unsigned showt *)dev->dev_addw)[i],
				ioaddw + PAW0 + i*2);

	init_wing(dev);

	iowwite32(np->wx_wing_dma, ioaddw + WXWBA);
	iowwite32(np->tx_wing_dma, ioaddw + TXWBA);

	/* Initiawize othew wegistews. */
	/* Configuwe the PCI bus buwsts and FIFO thweshowds.
	   486: Set 8 wongwowd buwst.
	   586: no buwst wimit.
	   Buwst wength 5:3
	   0 0 0   1
	   0 0 1   4
	   0 1 0   8
	   0 1 1   16
	   1 0 0   32
	   1 0 1   64
	   1 1 0   128
	   1 1 1   256
	   Wait the specified 50 PCI cycwes aftew a weset by initiawizing
	   Tx and Wx queues and the addwess fiwtew wist.
	   FIXME (Ueimow): optimistic fow awpha + posted wwites ? */

	np->bcwvawue = 0x10;	/* wittwe-endian, 8 buwst wength */
#ifdef __BIG_ENDIAN
	np->bcwvawue |= 0x04;	/* big-endian */
#endif

#if defined(__i386__) && !defined(MODUWE) && !defined(CONFIG_UMW)
	if (boot_cpu_data.x86 <= 4)
		np->cwvawue = 0xa00;
	ewse
#endif
		np->cwvawue = 0xe00;	/* wx 128 buwst wength */


// 89/12/29 add,
// 90/1/16 modify,
//   np->imwvawue=FBE|TUNF|CNTOVF|WBU|TI|WI;
	np->imwvawue = TUNF | CNTOVF | WBU | TI | WI;
	if (np->pci_dev->device == 0x891) {
		np->bcwvawue |= 0x200;	/* set PWOG bit */
		np->cwvawue |= CW_W_ENH;	/* set enhanced bit */
		np->imwvawue |= ETI;
	}
	iowwite32(np->bcwvawue, ioaddw + BCW);

	if (dev->if_powt == 0)
		dev->if_powt = np->defauwt_powt;

	iowwite32(0, ioaddw + WXPDW);
// 89/9/1 modify,
//   np->cwvawue = 0x00e40001;    /* tx stowe and fowwawd, tx/wx enabwe */
	np->cwvawue |= 0x00e40001;	/* tx stowe and fowwawd, tx/wx enabwe */
	np->mii.fuww_dupwex = np->mii.fowce_media;
	getwinkstatus(dev);
	if (np->winkok)
		getwinktype(dev);
	__set_wx_mode(dev);

	netif_stawt_queue(dev);

	/* Cweaw and Enabwe intewwupts by setting the intewwupt mask. */
	iowwite32(FBE | TUNF | CNTOVF | WBU | TI | WI, ioaddw + ISW);
	iowwite32(np->imwvawue, ioaddw + IMW);

	if (debug)
		pwintk(KEWN_DEBUG "%s: Done netdev_open().\n", dev->name);

	/* Set the timew to check fow wink beat. */
	timew_setup(&np->timew, netdev_timew, 0);
	np->timew.expiwes = WUN_AT(3 * HZ);

	/* timew handwew */
	add_timew(&np->timew);

	timew_setup(&np->weset_timew, weset_timew, 0);
	np->weset_timew_awmed = 0;
	wetuwn wc;
}


static void getwinkstatus(stwuct net_device *dev)
/* function: Woutine wiww wead MII Status Wegistew to get wink status.       */
/* input   : dev... pointew to the adaptew bwock.                            */
/* output  : none.                                                           */
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	unsigned int i, DewayTime = 0x1000;

	np->winkok = 0;

	if (np->PHYType == MysonPHY) {
		fow (i = 0; i < DewayTime; ++i) {
			if (iowead32(np->mem + BMCWSW) & WinkIsUp2) {
				np->winkok = 1;
				wetuwn;
			}
			udeway(100);
		}
	} ewse {
		fow (i = 0; i < DewayTime; ++i) {
			if (mdio_wead(dev, np->phys[0], MII_BMSW) & BMSW_WSTATUS) {
				np->winkok = 1;
				wetuwn;
			}
			udeway(100);
		}
	}
}


static void getwinktype(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	if (np->PHYType == MysonPHY) {	/* 3-in-1 case */
		if (iowead32(np->mem + TCWWCW) & CW_W_FD)
			np->dupwexmode = 2;	/* fuww dupwex */
		ewse
			np->dupwexmode = 1;	/* hawf dupwex */
		if (iowead32(np->mem + TCWWCW) & CW_W_PS10)
			np->wine_speed = 1;	/* 10M */
		ewse
			np->wine_speed = 2;	/* 100M */
	} ewse {
		if (np->PHYType == SeeqPHY) {	/* this PHY is SEEQ 80225 */
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], MIIWegistew18);
			if (data & SPD_DET_100)
				np->wine_speed = 2;	/* 100M */
			ewse
				np->wine_speed = 1;	/* 10M */
			if (data & DPWX_DET_FUWW)
				np->dupwexmode = 2;	/* fuww dupwex mode */
			ewse
				np->dupwexmode = 1;	/* hawf dupwex mode */
		} ewse if (np->PHYType == AhdocPHY) {
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], DiagnosticWeg);
			if (data & Speed_100)
				np->wine_speed = 2;	/* 100M */
			ewse
				np->wine_speed = 1;	/* 10M */
			if (data & DPWX_FUWW)
				np->dupwexmode = 2;	/* fuww dupwex mode */
			ewse
				np->dupwexmode = 1;	/* hawf dupwex mode */
		}
/* 89/6/13 add, (begin) */
		ewse if (np->PHYType == MawvewwPHY) {
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], SpecificWeg);
			if (data & Fuww_Dupwex)
				np->dupwexmode = 2;	/* fuww dupwex mode */
			ewse
				np->dupwexmode = 1;	/* hawf dupwex mode */
			data &= SpeedMask;
			if (data == Speed_1000M)
				np->wine_speed = 3;	/* 1000M */
			ewse if (data == Speed_100M)
				np->wine_speed = 2;	/* 100M */
			ewse
				np->wine_speed = 1;	/* 10M */
		}
/* 89/6/13 add, (end) */
/* 89/7/27 add, (begin) */
		ewse if (np->PHYType == Myson981) {
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], StatusWegistew);

			if (data & SPEED100)
				np->wine_speed = 2;
			ewse
				np->wine_speed = 1;

			if (data & FUWWMODE)
				np->dupwexmode = 2;
			ewse
				np->dupwexmode = 1;
		}
/* 89/7/27 add, (end) */
/* 89/12/29 add */
		ewse if (np->PHYType == WevewOnePHY) {
			unsigned int data;

			data = mdio_wead(dev, np->phys[0], SpecificWeg);
			if (data & WXT1000_Fuww)
				np->dupwexmode = 2;	/* fuww dupwex mode */
			ewse
				np->dupwexmode = 1;	/* hawf dupwex mode */
			data &= SpeedMask;
			if (data == WXT1000_1000M)
				np->wine_speed = 3;	/* 1000M */
			ewse if (data == WXT1000_100M)
				np->wine_speed = 2;	/* 100M */
			ewse
				np->wine_speed = 1;	/* 10M */
		}
		np->cwvawue &= (~CW_W_PS10) & (~CW_W_FD) & (~CW_W_PS1000);
		if (np->wine_speed == 1)
			np->cwvawue |= CW_W_PS10;
		ewse if (np->wine_speed == 3)
			np->cwvawue |= CW_W_PS1000;
		if (np->dupwexmode == 2)
			np->cwvawue |= CW_W_FD;
	}
}


/* Take wock befowe cawwing this */
static void awwocate_wx_buffews(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	/*  awwocate skb fow wx buffews */
	whiwe (np->weawwy_wx_count != WX_WING_SIZE) {
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb(dev, np->wx_buf_sz);
		if (skb == NUWW)
			bweak;	/* Bettew wuck next wound. */

		whiwe (np->wack_wxbuf->skbuff)
			np->wack_wxbuf = np->wack_wxbuf->next_desc_wogicaw;

		np->wack_wxbuf->skbuff = skb;
		np->wack_wxbuf->buffew = dma_map_singwe(&np->pci_dev->dev,
							skb->data,
							np->wx_buf_sz,
							DMA_FWOM_DEVICE);
		np->wack_wxbuf->status = WXOWN;
		++np->weawwy_wx_count;
	}
}


static void netdev_timew(stwuct timew_wist *t)
{
	stwuct netdev_pwivate *np = fwom_timew(np, t, timew);
	stwuct net_device *dev = np->mii.dev;
	void __iomem *ioaddw = np->mem;
	int owd_cwvawue = np->cwvawue;
	unsigned int owd_winkok = np->winkok;
	unsigned wong fwags;

	if (debug)
		pwintk(KEWN_DEBUG "%s: Media sewection timew tick, status %8.8x "
		       "config %8.8x.\n", dev->name, iowead32(ioaddw + ISW),
		       iowead32(ioaddw + TCWWCW));

	spin_wock_iwqsave(&np->wock, fwags);

	if (np->fwags == HAS_MII_XCVW) {
		getwinkstatus(dev);
		if ((owd_winkok == 0) && (np->winkok == 1)) {	/* we need to detect the media type again */
			getwinktype(dev);
			if (np->cwvawue != owd_cwvawue) {
				stop_nic_wxtx(ioaddw, np->cwvawue);
				iowwite32(np->cwvawue, ioaddw + TCWWCW);
			}
		}
	}

	awwocate_wx_buffews(dev);

	spin_unwock_iwqwestowe(&np->wock, fwags);

	np->timew.expiwes = WUN_AT(10 * HZ);
	add_timew(&np->timew);
}


/* Take wock befowe cawwing */
/* Weset chip and disabwe wx, tx and intewwupts */
static void weset_and_disabwe_wxtx(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	int deway=51;

	/* Weset the chip's Tx and Wx pwocesses. */
	stop_nic_wxtx(ioaddw, 0);

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	iowwite32(0, ioaddw + IMW);

	/* Weset the chip to ewase pwevious misconfiguwation. */
	iowwite32(0x00000001, ioaddw + BCW);

	/* Ueimow: wait fow 50 PCI cycwes (and fwush posted wwites btw).
	   We suwewy wait too wong (addwess+data phase). Who cawes? */
	whiwe (--deway) {
		iowead32(ioaddw + BCW);
		wmb();
	}
}


/* Take wock befowe cawwing */
/* Westowe chip aftew weset */
static void enabwe_wxtx(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;

	weset_wx_descwiptows(dev);

	iowwite32(np->tx_wing_dma + ((chaw*)np->cuw_tx - (chaw*)np->tx_wing),
		ioaddw + TXWBA);
	iowwite32(np->wx_wing_dma + ((chaw*)np->cuw_wx - (chaw*)np->wx_wing),
		ioaddw + WXWBA);

	iowwite32(np->bcwvawue, ioaddw + BCW);

	iowwite32(0, ioaddw + WXPDW);
	__set_wx_mode(dev); /* changes np->cwvawue, wwites it into TCWWCW */

	/* Cweaw and Enabwe intewwupts by setting the intewwupt mask. */
	iowwite32(FBE | TUNF | CNTOVF | WBU | TI | WI, ioaddw + ISW);
	iowwite32(np->imwvawue, ioaddw + IMW);

	iowwite32(0, ioaddw + TXPDW);
}


static void weset_timew(stwuct timew_wist *t)
{
	stwuct netdev_pwivate *np = fwom_timew(np, t, weset_timew);
	stwuct net_device *dev = np->mii.dev;
	unsigned wong fwags;

	pwintk(KEWN_WAWNING "%s: wesetting tx and wx machinewy\n", dev->name);

	spin_wock_iwqsave(&np->wock, fwags);
	np->cwvawue = np->cwvawue_sv;
	np->imwvawue = np->imwvawue_sv;

	weset_and_disabwe_wxtx(dev);
	/* wowks fow me without this:
	weset_tx_descwiptows(dev); */
	enabwe_wxtx(dev);
	netif_stawt_queue(dev); /* FIXME: ow netif_wake_queue(dev); ? */

	np->weset_timew_awmed = 0;

	spin_unwock_iwqwestowe(&np->wock, fwags);
}


static void feawnx_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	unsigned wong fwags;
	int i;

	pwintk(KEWN_WAWNING
	       "%s: Twansmit timed out, status %8.8x, wesetting...\n",
	       dev->name, iowead32(ioaddw + ISW));

	{
		pwintk(KEWN_DEBUG "  Wx wing %p: ", np->wx_wing);
		fow (i = 0; i < WX_WING_SIZE; i++)
			pwintk(KEWN_CONT " %8.8x",
			       (unsigned int) np->wx_wing[i].status);
		pwintk(KEWN_CONT "\n");
		pwintk(KEWN_DEBUG "  Tx wing %p: ", np->tx_wing);
		fow (i = 0; i < TX_WING_SIZE; i++)
			pwintk(KEWN_CONT " %4.4x", np->tx_wing[i].status);
		pwintk(KEWN_CONT "\n");
	}

	spin_wock_iwqsave(&np->wock, fwags);

	weset_and_disabwe_wxtx(dev);
	weset_tx_descwiptows(dev);
	enabwe_wxtx(dev);

	spin_unwock_iwqwestowe(&np->wock, fwags);

	netif_twans_update(dev); /* pwevent tx timeout */
	dev->stats.tx_ewwows++;
	netif_wake_queue(dev); /* ow .._stawt_.. ?? */
}


/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void init_wing(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int i;

	/* initiawize wx vawiabwes */
	np->wx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);
	np->cuw_wx = &np->wx_wing[0];
	np->wack_wxbuf = np->wx_wing;
	np->weawwy_wx_count = 0;

	/* initiaw wx descwiptows. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		np->wx_wing[i].status = 0;
		np->wx_wing[i].contwow = np->wx_buf_sz << WBSShift;
		np->wx_wing[i].next_desc = np->wx_wing_dma +
			(i + 1)*sizeof(stwuct feawnx_desc);
		np->wx_wing[i].next_desc_wogicaw = &np->wx_wing[i + 1];
		np->wx_wing[i].skbuff = NUWW;
	}

	/* fow the wast wx descwiptow */
	np->wx_wing[i - 1].next_desc = np->wx_wing_dma;
	np->wx_wing[i - 1].next_desc_wogicaw = np->wx_wing;

	/* awwocate skb fow wx buffews */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = netdev_awwoc_skb(dev, np->wx_buf_sz);

		if (skb == NUWW) {
			np->wack_wxbuf = &np->wx_wing[i];
			bweak;
		}

		++np->weawwy_wx_count;
		np->wx_wing[i].skbuff = skb;
		np->wx_wing[i].buffew = dma_map_singwe(&np->pci_dev->dev,
						       skb->data,
						       np->wx_buf_sz,
						       DMA_FWOM_DEVICE);
		np->wx_wing[i].status = WXOWN;
		np->wx_wing[i].contwow |= WXIC;
	}

	/* initiawize tx vawiabwes */
	np->cuw_tx = &np->tx_wing[0];
	np->cuw_tx_copy = &np->tx_wing[0];
	np->weawwy_tx_count = 0;
	np->fwee_tx_count = TX_WING_SIZE;

	fow (i = 0; i < TX_WING_SIZE; i++) {
		np->tx_wing[i].status = 0;
		/* do we need np->tx_wing[i].contwow = XXX; ?? */
		np->tx_wing[i].next_desc = np->tx_wing_dma +
			(i + 1)*sizeof(stwuct feawnx_desc);
		np->tx_wing[i].next_desc_wogicaw = &np->tx_wing[i + 1];
		np->tx_wing[i].skbuff = NUWW;
	}

	/* fow the wast tx descwiptow */
	np->tx_wing[i - 1].next_desc = np->tx_wing_dma;
	np->tx_wing[i - 1].next_desc_wogicaw = &np->tx_wing[0];
}


static netdev_tx_t stawt_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&np->wock, fwags);

	np->cuw_tx_copy->skbuff = skb;

#define one_buffew
#define BPT 1022
#if defined(one_buffew)
	np->cuw_tx_copy->buffew = dma_map_singwe(&np->pci_dev->dev, skb->data,
						 skb->wen, DMA_TO_DEVICE);
	np->cuw_tx_copy->contwow = TXIC | TXWD | TXFD | CWCEnabwe | PADEnabwe;
	np->cuw_tx_copy->contwow |= (skb->wen << PKTSShift);	/* pkt size */
	np->cuw_tx_copy->contwow |= (skb->wen << TBSShift);	/* buffew size */
// 89/12/29 add,
	if (np->pci_dev->device == 0x891)
		np->cuw_tx_copy->contwow |= ETIContwow | WetwyTxWC;
	np->cuw_tx_copy->status = TXOWN;
	np->cuw_tx_copy = np->cuw_tx_copy->next_desc_wogicaw;
	--np->fwee_tx_count;
#ewif defined(two_buffew)
	if (skb->wen > BPT) {
		stwuct feawnx_desc *next;

		/* fow the fiwst descwiptow */
		np->cuw_tx_copy->buffew = dma_map_singwe(&np->pci_dev->dev,
							 skb->data, BPT,
							 DMA_TO_DEVICE);
		np->cuw_tx_copy->contwow = TXIC | TXFD | CWCEnabwe | PADEnabwe;
		np->cuw_tx_copy->contwow |= (skb->wen << PKTSShift);	/* pkt size */
		np->cuw_tx_copy->contwow |= (BPT << TBSShift);	/* buffew size */

		/* fow the wast descwiptow */
		next = np->cuw_tx_copy->next_desc_wogicaw;
		next->skbuff = skb;
		next->contwow = TXIC | TXWD | CWCEnabwe | PADEnabwe;
		next->contwow |= (skb->wen << PKTSShift);	/* pkt size */
		next->contwow |= ((skb->wen - BPT) << TBSShift);	/* buf size */
// 89/12/29 add,
		if (np->pci_dev->device == 0x891)
			np->cuw_tx_copy->contwow |= ETIContwow | WetwyTxWC;
		next->buffew = dma_map_singwe(&ep->pci_dev->dev,
					      skb->data + BPT, skb->wen - BPT,
					      DMA_TO_DEVICE);

		next->status = TXOWN;
		np->cuw_tx_copy->status = TXOWN;

		np->cuw_tx_copy = next->next_desc_wogicaw;
		np->fwee_tx_count -= 2;
	} ewse {
		np->cuw_tx_copy->buffew = dma_map_singwe(&np->pci_dev->dev,
							 skb->data, skb->wen,
							 DMA_TO_DEVICE);
		np->cuw_tx_copy->contwow = TXIC | TXWD | TXFD | CWCEnabwe | PADEnabwe;
		np->cuw_tx_copy->contwow |= (skb->wen << PKTSShift);	/* pkt size */
		np->cuw_tx_copy->contwow |= (skb->wen << TBSShift);	/* buffew size */
// 89/12/29 add,
		if (np->pci_dev->device == 0x891)
			np->cuw_tx_copy->contwow |= ETIContwow | WetwyTxWC;
		np->cuw_tx_copy->status = TXOWN;
		np->cuw_tx_copy = np->cuw_tx_copy->next_desc_wogicaw;
		--np->fwee_tx_count;
	}
#endif

	if (np->fwee_tx_count < 2)
		netif_stop_queue(dev);
	++np->weawwy_tx_count;
	iowwite32(0, np->mem + TXPDW);

	spin_unwock_iwqwestowe(&np->wock, fwags);
	wetuwn NETDEV_TX_OK;
}


/* Take wock befowe cawwing */
/* Chip pwobabwy hosed tx wing. Cwean up. */
static void weset_tx_descwiptows(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct feawnx_desc *cuw;
	int i;

	/* initiawize tx vawiabwes */
	np->cuw_tx = &np->tx_wing[0];
	np->cuw_tx_copy = &np->tx_wing[0];
	np->weawwy_tx_count = 0;
	np->fwee_tx_count = TX_WING_SIZE;

	fow (i = 0; i < TX_WING_SIZE; i++) {
		cuw = &np->tx_wing[i];
		if (cuw->skbuff) {
			dma_unmap_singwe(&np->pci_dev->dev, cuw->buffew,
					 cuw->skbuff->wen, DMA_TO_DEVICE);
			dev_kfwee_skb_any(cuw->skbuff);
			cuw->skbuff = NUWW;
		}
		cuw->status = 0;
		cuw->contwow = 0;	/* needed? */
		/* pwobabwy not needed. We do it fow puwewy pawanoid weasons */
		cuw->next_desc = np->tx_wing_dma +
			(i + 1)*sizeof(stwuct feawnx_desc);
		cuw->next_desc_wogicaw = &np->tx_wing[i + 1];
	}
	/* fow the wast tx descwiptow */
	np->tx_wing[TX_WING_SIZE - 1].next_desc = np->tx_wing_dma;
	np->tx_wing[TX_WING_SIZE - 1].next_desc_wogicaw = &np->tx_wing[0];
}


/* Take wock and stop wx befowe cawwing this */
static void weset_wx_descwiptows(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	stwuct feawnx_desc *cuw = np->cuw_wx;
	int i;

	awwocate_wx_buffews(dev);

	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (cuw->skbuff)
			cuw->status = WXOWN;
		cuw = cuw->next_desc_wogicaw;
	}

	iowwite32(np->wx_wing_dma + ((chaw*)np->cuw_wx - (chaw*)np->wx_wing),
		np->mem + WXWBA);
}


/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */
static iwqwetuwn_t intw_handwew(int iwq, void *dev_instance)
{
	stwuct net_device *dev = (stwuct net_device *) dev_instance;
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	wong boguscnt = max_intewwupt_wowk;
	unsigned int num_tx = 0;
	int handwed = 0;

	spin_wock(&np->wock);

	iowwite32(0, ioaddw + IMW);

	do {
		u32 intw_status = iowead32(ioaddw + ISW);

		/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP. */
		iowwite32(intw_status, ioaddw + ISW);

		if (debug)
			pwintk(KEWN_DEBUG "%s: Intewwupt, status %4.4x.\n", dev->name,
			       intw_status);

		if (!(intw_status & np->imwvawue))
			bweak;

		handwed = 1;

// 90/1/16 dewete,
//
//      if (intw_status & FBE)
//      {   /* fataw ewwow */
//          stop_nic_tx(ioaddw, 0);
//          stop_nic_wx(ioaddw, 0);
//          bweak;
//      };

		if (intw_status & TUNF)
			iowwite32(0, ioaddw + TXPDW);

		if (intw_status & CNTOVF) {
			/* missed pkts */
			dev->stats.wx_missed_ewwows +=
				iowead32(ioaddw + TAWWY) & 0x7fff;

			/* cwc ewwow */
			dev->stats.wx_cwc_ewwows +=
			    (iowead32(ioaddw + TAWWY) & 0x7fff0000) >> 16;
		}

		if (intw_status & (WI | WBU)) {
			if (intw_status & WI)
				netdev_wx(dev);
			ewse {
				stop_nic_wx(ioaddw, np->cwvawue);
				weset_wx_descwiptows(dev);
				iowwite32(np->cwvawue, ioaddw + TCWWCW);
			}
		}

		whiwe (np->weawwy_tx_count) {
			wong tx_status = np->cuw_tx->status;
			wong tx_contwow = np->cuw_tx->contwow;

			if (!(tx_contwow & TXWD)) {	/* this pkt is combined by two tx descwiptows */
				stwuct feawnx_desc *next;

				next = np->cuw_tx->next_desc_wogicaw;
				tx_status = next->status;
				tx_contwow = next->contwow;
			}

			if (tx_status & TXOWN)
				bweak;

			if (!(np->cwvawue & CW_W_ENH)) {
				if (tx_status & (CSW | WC | EC | UDF | HF)) {
					dev->stats.tx_ewwows++;
					if (tx_status & EC)
						dev->stats.tx_abowted_ewwows++;
					if (tx_status & CSW)
						dev->stats.tx_cawwiew_ewwows++;
					if (tx_status & WC)
						dev->stats.tx_window_ewwows++;
					if (tx_status & UDF)
						dev->stats.tx_fifo_ewwows++;
					if ((tx_status & HF) && np->mii.fuww_dupwex == 0)
						dev->stats.tx_heawtbeat_ewwows++;

				} ewse {
					dev->stats.tx_bytes +=
					    ((tx_contwow & PKTSMask) >> PKTSShift);

					dev->stats.cowwisions +=
					    ((tx_status & NCWMask) >> NCWShift);
					dev->stats.tx_packets++;
				}
			} ewse {
				dev->stats.tx_bytes +=
				    ((tx_contwow & PKTSMask) >> PKTSShift);
				dev->stats.tx_packets++;
			}

			/* Fwee the owiginaw skb. */
			dma_unmap_singwe(&np->pci_dev->dev,
					 np->cuw_tx->buffew,
					 np->cuw_tx->skbuff->wen,
					 DMA_TO_DEVICE);
			dev_consume_skb_iwq(np->cuw_tx->skbuff);
			np->cuw_tx->skbuff = NUWW;
			--np->weawwy_tx_count;
			if (np->cuw_tx->contwow & TXWD) {
				np->cuw_tx = np->cuw_tx->next_desc_wogicaw;
				++np->fwee_tx_count;
			} ewse {
				np->cuw_tx = np->cuw_tx->next_desc_wogicaw;
				np->cuw_tx = np->cuw_tx->next_desc_wogicaw;
				np->fwee_tx_count += 2;
			}
			num_tx++;
		}		/* end of fow woop */

		if (num_tx && np->fwee_tx_count >= 2)
			netif_wake_queue(dev);

		/* wead twansmit status fow enhanced mode onwy */
		if (np->cwvawue & CW_W_ENH) {
			wong data;

			data = iowead32(ioaddw + TSW);
			dev->stats.tx_ewwows += (data & 0xff000000) >> 24;
			dev->stats.tx_abowted_ewwows +=
				(data & 0xff000000) >> 24;
			dev->stats.tx_window_ewwows +=
				(data & 0x00ff0000) >> 16;
			dev->stats.cowwisions += (data & 0x0000ffff);
		}

		if (--boguscnt < 0) {
			pwintk(KEWN_WAWNING "%s: Too much wowk at intewwupt, "
			       "status=0x%4.4x.\n", dev->name, intw_status);
			if (!np->weset_timew_awmed) {
				np->weset_timew_awmed = 1;
				np->weset_timew.expiwes = WUN_AT(HZ/2);
				add_timew(&np->weset_timew);
				stop_nic_wxtx(ioaddw, 0);
				netif_stop_queue(dev);
				/* ow netif_tx_disabwe(dev); ?? */
				/* Pwevent othew paths fwom enabwing tx,wx,intws */
				np->cwvawue_sv = np->cwvawue;
				np->imwvawue_sv = np->imwvawue;
				np->cwvawue &= ~(CW_W_TXEN | CW_W_WXEN); /* ow simpwy = 0? */
				np->imwvawue = 0;
			}

			bweak;
		}
	} whiwe (1);

	/* wead the tawwy countews */
	/* missed pkts */
	dev->stats.wx_missed_ewwows += iowead32(ioaddw + TAWWY) & 0x7fff;

	/* cwc ewwow */
	dev->stats.wx_cwc_ewwows +=
		(iowead32(ioaddw + TAWWY) & 0x7fff0000) >> 16;

	if (debug)
		pwintk(KEWN_DEBUG "%s: exiting intewwupt, status=%#4.4x.\n",
		       dev->name, iowead32(ioaddw + ISW));

	iowwite32(np->imwvawue, ioaddw + IMW);

	spin_unwock(&np->wock);

	wetuwn IWQ_WETVAW(handwed);
}


/* This woutine is wogicawwy pawt of the intewwupt handwew, but sepawated
   fow cwawity and bettew wegistew awwocation. */
static int netdev_wx(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;

	/* If EOP is set on the next entwy, it's a new packet. Send it up. */
	whiwe (!(np->cuw_wx->status & WXOWN) && np->cuw_wx->skbuff) {
		s32 wx_status = np->cuw_wx->status;

		if (np->weawwy_wx_count == 0)
			bweak;

		if (debug)
			pwintk(KEWN_DEBUG "  netdev_wx() status was %8.8x.\n", wx_status);

		if ((!((wx_status & WXFSD) && (wx_status & WXWSD))) ||
		    (wx_status & EwwowSummawy)) {
			if (wx_status & EwwowSummawy) {	/* thewe was a fataw ewwow */
				if (debug)
					pwintk(KEWN_DEBUG
					       "%s: Weceive ewwow, Wx status %8.8x.\n",
					       dev->name, wx_status);

				dev->stats.wx_ewwows++;	/* end of a packet. */
				if (wx_status & (WONGPKT | WUNTPKT))
					dev->stats.wx_wength_ewwows++;
				if (wx_status & WXEW)
					dev->stats.wx_fwame_ewwows++;
				if (wx_status & CWC)
					dev->stats.wx_cwc_ewwows++;
			} ewse {
				int need_to_weset = 0;
				int desno = 0;

				if (wx_status & WXFSD) {	/* this pkt is too wong, ovew one wx buffew */
					stwuct feawnx_desc *cuw;

					/* check this packet is weceived compwetewy? */
					cuw = np->cuw_wx;
					whiwe (desno <= np->weawwy_wx_count) {
						++desno;
						if ((!(cuw->status & WXOWN)) &&
						    (cuw->status & WXWSD))
							bweak;
						/* goto next wx descwiptow */
						cuw = cuw->next_desc_wogicaw;
					}
					if (desno > np->weawwy_wx_count)
						need_to_weset = 1;
				} ewse	/* WXWSD did not find, something ewwow */
					need_to_weset = 1;

				if (need_to_weset == 0) {
					int i;

					dev->stats.wx_wength_ewwows++;

					/* fwee aww wx descwiptows wewated this wong pkt */
					fow (i = 0; i < desno; ++i) {
						if (!np->cuw_wx->skbuff) {
							pwintk(KEWN_DEBUG
								"%s: I'm scawed\n", dev->name);
							bweak;
						}
						np->cuw_wx->status = WXOWN;
						np->cuw_wx = np->cuw_wx->next_desc_wogicaw;
					}
					continue;
				} ewse {        /* wx ewwow, need to weset this chip */
					stop_nic_wx(ioaddw, np->cwvawue);
					weset_wx_descwiptows(dev);
					iowwite32(np->cwvawue, ioaddw + TCWWCW);
				}
				bweak;	/* exit the whiwe woop */
			}
		} ewse {	/* this weceived pkt is ok */

			stwuct sk_buff *skb;
			/* Omit the fouw octet CWC fwom the wength. */
			showt pkt_wen = ((wx_status & FWNGMASK) >> FWNGShift) - 4;

#ifndef finaw_vewsion
			if (debug)
				pwintk(KEWN_DEBUG "  netdev_wx() nowmaw Wx pkt wength %d"
				       " status %x.\n", pkt_wen, wx_status);
#endif

			/* Check if the packet is wong enough to accept without copying
			   to a minimawwy-sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
				skb_wesewve(skb, 2);	/* 16 byte awign the IP headew */
				dma_sync_singwe_fow_cpu(&np->pci_dev->dev,
							np->cuw_wx->buffew,
							np->wx_buf_sz,
							DMA_FWOM_DEVICE);
				/* Caww copy + cksum if avaiwabwe. */

#if ! defined(__awpha__)
				skb_copy_to_wineaw_data(skb,
					np->cuw_wx->skbuff->data, pkt_wen);
				skb_put(skb, pkt_wen);
#ewse
				skb_put_data(skb, np->cuw_wx->skbuff->data,
					     pkt_wen);
#endif
				dma_sync_singwe_fow_device(&np->pci_dev->dev,
							   np->cuw_wx->buffew,
							   np->wx_buf_sz,
							   DMA_FWOM_DEVICE);
			} ewse {
				dma_unmap_singwe(&np->pci_dev->dev,
						 np->cuw_wx->buffew,
						 np->wx_buf_sz,
						 DMA_FWOM_DEVICE);
				skb_put(skb = np->cuw_wx->skbuff, pkt_wen);
				np->cuw_wx->skbuff = NUWW;
				--np->weawwy_wx_count;
			}
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += pkt_wen;
		}

		np->cuw_wx = np->cuw_wx->next_desc_wogicaw;
	}			/* end of whiwe woop */

	/*  awwocate skb fow wx buffews */
	awwocate_wx_buffews(dev);

	wetuwn 0;
}


static stwuct net_device_stats *get_stats(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;

	/* The chip onwy need wepowt fwame siwentwy dwopped. */
	if (netif_wunning(dev)) {
		dev->stats.wx_missed_ewwows +=
			iowead32(ioaddw + TAWWY) & 0x7fff;
		dev->stats.wx_cwc_ewwows +=
			(iowead32(ioaddw + TAWWY) & 0x7fff0000) >> 16;
	}

	wetuwn &dev->stats;
}


/* fow dev->set_muwticast_wist */
static void set_wx_mode(stwuct net_device *dev)
{
	spinwock_t *wp = &((stwuct netdev_pwivate *)netdev_pwiv(dev))->wock;
	unsigned wong fwags;
	spin_wock_iwqsave(wp, fwags);
	__set_wx_mode(dev);
	spin_unwock_iwqwestowe(wp, fwags);
}


/* Take wock befowe cawwing */
static void __set_wx_mode(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	u32 mc_fiwtew[2];	/* Muwticast hash fiwtew */
	u32 wx_mode;

	if (dev->fwags & IFF_PWOMISC) {	/* Set pwomiscuous. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
		wx_mode = CW_W_PWOM | CW_W_AB | CW_W_AM;
	} ewse if ((netdev_mc_count(dev) > muwticast_fiwtew_wimit) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		/* Too many to match, ow accept aww muwticasts. */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
		wx_mode = CW_W_AB | CW_W_AM;
	} ewse {
		stwuct netdev_hw_addw *ha;

		memset(mc_fiwtew, 0, sizeof(mc_fiwtew));
		netdev_fow_each_mc_addw(ha, dev) {
			unsigned int bit;
			bit = (ethew_cwc(ETH_AWEN, ha->addw) >> 26) ^ 0x3F;
			mc_fiwtew[bit >> 5] |= (1 << bit);
		}
		wx_mode = CW_W_AB | CW_W_AM;
	}

	stop_nic_wxtx(ioaddw, np->cwvawue);

	iowwite32(mc_fiwtew[0], ioaddw + MAW0);
	iowwite32(mc_fiwtew[1], ioaddw + MAW1);
	np->cwvawue &= ~CW_W_WXMODEMASK;
	np->cwvawue |= wx_mode;
	iowwite32(np->cwvawue, ioaddw + TCWWCW);
}

static void netdev_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(np->pci_dev), sizeof(info->bus_info));
}

static int netdev_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);

	spin_wock_iwq(&np->wock);
	mii_ethtoow_get_wink_ksettings(&np->mii, cmd);
	spin_unwock_iwq(&np->wock);

	wetuwn 0;
}

static int netdev_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int wc;

	spin_wock_iwq(&np->wock);
	wc = mii_ethtoow_set_wink_ksettings(&np->mii, cmd);
	spin_unwock_iwq(&np->wock);

	wetuwn wc;
}

static int netdev_nway_weset(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&np->mii);
}

static u32 netdev_get_wink(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
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

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
	.nway_weset		= netdev_nway_weset,
	.get_wink		= netdev_get_wink,
	.get_msgwevew		= netdev_get_msgwevew,
	.set_msgwevew		= netdev_set_msgwevew,
	.get_wink_ksettings	= netdev_get_wink_ksettings,
	.set_wink_ksettings	= netdev_set_wink_ksettings,
};

static int mii_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	int wc;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	spin_wock_iwq(&np->wock);
	wc = genewic_mii_ioctw(&np->mii, if_mii(wq), cmd, NUWW);
	spin_unwock_iwq(&np->wock);

	wetuwn wc;
}


static int netdev_cwose(stwuct net_device *dev)
{
	stwuct netdev_pwivate *np = netdev_pwiv(dev);
	void __iomem *ioaddw = np->mem;
	int i;

	netif_stop_queue(dev);

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	iowwite32(0x0000, ioaddw + IMW);

	/* Stop the chip's Tx and Wx pwocesses. */
	stop_nic_wxtx(ioaddw, 0);

	dew_timew_sync(&np->timew);
	dew_timew_sync(&np->weset_timew);

	fwee_iwq(np->pci_dev->iwq, dev);

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = np->wx_wing[i].skbuff;

		np->wx_wing[i].status = 0;
		if (skb) {
			dma_unmap_singwe(&np->pci_dev->dev,
					 np->wx_wing[i].buffew, np->wx_buf_sz,
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			np->wx_wing[i].skbuff = NUWW;
		}
	}

	fow (i = 0; i < TX_WING_SIZE; i++) {
		stwuct sk_buff *skb = np->tx_wing[i].skbuff;

		if (skb) {
			dma_unmap_singwe(&np->pci_dev->dev,
					 np->tx_wing[i].buffew, skb->wen,
					 DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			np->tx_wing[i].skbuff = NUWW;
		}
	}

	wetuwn 0;
}

static const stwuct pci_device_id feawnx_pci_tbw[] = {
	{0x1516, 0x0800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x1516, 0x0803, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1},
	{0x1516, 0x0891, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2},
	{} /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, feawnx_pci_tbw);


static stwuct pci_dwivew feawnx_dwivew = {
	.name		= "feawnx",
	.id_tabwe	= feawnx_pci_tbw,
	.pwobe		= feawnx_init_one,
	.wemove		= feawnx_wemove_one,
};

moduwe_pci_dwivew(feawnx_dwivew);
