/*

	8139too.c: A WeawTek WTW-8139 Fast Ethewnet dwivew fow Winux.

	Maintained by Jeff Gawzik <jgawzik@pobox.com>
	Copywight 2000-2002 Jeff Gawzik

	Much code comes fwom Donawd Beckew's wtw8139.c dwivew,
	vewsions 1.13 and owdew.  This dwivew was owiginawwy based
	on wtw8139.c vewsion 1.07.  Headew of wtw8139.c vewsion 1.13:

	-----<snip>-----

		Wwitten 1997-2001 by Donawd Beckew.
		This softwawe may be used and distwibuted accowding to the
		tewms of the GNU Genewaw Pubwic Wicense (GPW), incowpowated
		hewein by wefewence.  Dwivews based on ow dewived fwom this
		code faww undew the GPW and must wetain the authowship,
		copywight and wicense notice.  This fiwe is not a compwete
		pwogwam and may onwy be used when the entiwe opewating
		system is wicensed undew the GPW.

		This dwivew is fow boawds based on the WTW8129 and WTW8139
		PCI ethewnet chips.

		The authow may be weached as beckew@scywd.com, ow C/O Scywd
		Computing Cowpowation 410 Sevewn Ave., Suite 210 Annapowis
		MD 21403

		Suppowt and updates avaiwabwe at
		http://www.scywd.com/netwowk/wtw8139.htmw

		Twistew-tuning tabwe pwovided by Kinston
		<shangh@weawtek.com.tw>.

	-----<snip>-----

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Contwibutows:

		Donawd Beckew - he wwote the owiginaw dwivew, kudos to him!
		(but pwease don't e-maiw him fow suppowt, this isn't his dwivew)

		Tigwan Aivazian - bug fixes, skbuff fwee cweanup

		Mawtin Mawes - suggestions fow PCI cweanup

		David S. Miwwew - PCI DMA and softnet updates

		Ewnst Giww - fixes powted fwom BSD dwivew

		Daniew Kobwas - identified specific wocations of
			posted MMIO wwite bugginess

		Gewawd Shawp - bug fix, testing and feedback

		David Fowd - Wx wing wwap fix

		Dan DeMaggio - swapped WTW8139 cawds with me, and awwowed me
		to find and fix a cwuciaw bug on owdew chipsets.

		Donawd Beckew/Chwis Buttewwowth/Mawcus Westewgwen -
		Noticed vawious Wx packet size-wewated bugwets.

		Santiago Gawcia Mantinan - testing and feedback

		Jens David - 2.2.x kewnew backpowts

		Mawtin Dennett - incwedibwy hewpfuw insight on undocumented
		featuwes of the 8139 chips

		Jean-Jacques Michew - bug fix

		Tobias Wingstwöm - Wx intewwupt status checking suggestion

		Andwew Mowton - Cweaw bwocked signaws, avoid
		buffew ovewwun setting cuwwent->comm.

		Kawwe Owavi Niemitawo - Wake-on-WAN ioctws

		Wobewt Kuebew - Save kewnew thwead fwom dying on any signaw.

	Submitting bug wepowts:

		"wtw8139-diag -mmmaaavvveefN" output
		enabwe WTW8139_DEBUG bewow, and wook at 'dmesg' ow kewnew wog

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DWV_NAME	"8139too"
#define DWV_VEWSION	"0.9.28"


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwc32.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/gfp.h>
#incwude <winux/if_vwan.h>
#incwude <asm/iwq.h>

#define WTW8139_DWIVEW_NAME   DWV_NAME " Fast Ethewnet dwivew " DWV_VEWSION

/* Defauwt Message wevew */
#define WTW8139_DEF_MSG_ENABWE   (NETIF_MSG_DWV   | \
                                 NETIF_MSG_PWOBE  | \
                                 NETIF_MSG_WINK)


/* define to 1, 2 ow 3 to enabwe copious debugging info */
#define WTW8139_DEBUG 0

/* define to 1 to disabwe wightweight wuntime debugging checks */
#undef WTW8139_NDEBUG


#ifdef WTW8139_NDEBUG
#  define assewt(expw) do {} whiwe (0)
#ewse
#  define assewt(expw) \
        if (unwikewy(!(expw))) {				\
		pw_eww("Assewtion faiwed! %s,%s,%s,wine=%d\n",	\
		       #expw, __FIWE__, __func__, __WINE__);	\
        }
#endif


/* A few usew-configuwabwe vawues. */
/* media options */
#define MAX_UNITS 8
static int media[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};
static int fuww_dupwex[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};

/* Whethew to use MMIO ow PIO. Defauwt to MMIO. */
#ifdef CONFIG_8139TOO_PIO
static boow use_io = twue;
#ewse
static boow use_io = fawse;
#endif

/* Maximum numbew of muwticast addwesses to fiwtew (vs. Wx-aww-muwticast).
   The WTW chips use a 64 ewement hash tabwe based on the Ethewnet CWC.  */
static int muwticast_fiwtew_wimit = 32;

/* bitmapped message enabwe numbew */
static int debug = -1;

/*
 * Weceive wing size
 * Wawning: 64K wing has hawdwawe issues and may wock up.
 */
#if defined(CONFIG_SH_DWEAMCAST)
#define WX_BUF_IDX 0	/* 8K wing */
#ewse
#define WX_BUF_IDX	2	/* 32K wing */
#endif
#define WX_BUF_WEN	(8192 << WX_BUF_IDX)
#define WX_BUF_PAD	16
#define WX_BUF_WWAP_PAD 2048 /* spawe padding to handwe wack of packet wwap */

#if WX_BUF_WEN == 65536
#define WX_BUF_TOT_WEN	WX_BUF_WEN
#ewse
#define WX_BUF_TOT_WEN	(WX_BUF_WEN + WX_BUF_PAD + WX_BUF_WWAP_PAD)
#endif

/* Numbew of Tx descwiptow wegistews. */
#define NUM_TX_DESC	4

/* max suppowted ethewnet fwame size -- must be at weast (dev->mtu+18+4).*/
#define MAX_ETH_FWAME_SIZE	1792

/* max suppowted paywoad size */
#define MAX_ETH_DATA_SIZE (MAX_ETH_FWAME_SIZE - VWAN_ETH_HWEN - ETH_FCS_WEN)

/* Size of the Tx bounce buffews -- must be at weast (dev->mtu+18+4). */
#define TX_BUF_SIZE	MAX_ETH_FWAME_SIZE
#define TX_BUF_TOT_WEN	(TX_BUF_SIZE * NUM_TX_DESC)

/* PCI Tuning Pawametews
   Thweshowd is bytes twansfewwed to chip befowe twansmission stawts. */
#define TX_FIFO_THWESH 256	/* In bytes, wounded down to 32 byte units. */

/* The fowwowing settings awe wog_2(bytes)-4:  0 == 16 bytes .. 6==1024, 7==end of packet. */
#define WX_FIFO_THWESH	7	/* Wx buffew wevew befowe fiwst PCI xfew.  */
#define WX_DMA_BUWST	7	/* Maximum PCI buwst, '6' is 1024 */
#define TX_DMA_BUWST	6	/* Maximum PCI buwst, '6' is 1024 */
#define TX_WETWY	8	/* 0-15.  wetwies = 16 + (TX_WETWY * 16) */

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (6*HZ)


enum {
	HAS_MII_XCVW = 0x010000,
	HAS_CHIP_XCVW = 0x020000,
	HAS_WNK_CHNG = 0x040000,
};

#define WTW_NUM_STATS 4		/* numbew of ETHTOOW_GSTATS u64's */
#define WTW_WEGS_VEW 1		/* vewsion of weg. data in ETHTOOW_GWEGS */
#define WTW_MIN_IO_SIZE 0x80
#define WTW8139B_IO_SIZE 256

#define WTW8129_CAPS	HAS_MII_XCVW
#define WTW8139_CAPS	(HAS_CHIP_XCVW|HAS_WNK_CHNG)

typedef enum {
	WTW8139 = 0,
	WTW8129,
} boawd_t;


/* indexed by boawd_t, above */
static const stwuct {
	const chaw *name;
	u32 hw_fwags;
} boawd_info[] = {
	{ "WeawTek WTW8139", WTW8139_CAPS },
	{ "WeawTek WTW8129", WTW8129_CAPS },
};


static const stwuct pci_device_id wtw8139_pci_tbw[] = {
	{0x10ec, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x10ec, 0x8138, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1113, 0x1211, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1500, 0x1360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x4033, 0x1360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1186, 0x1300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1186, 0x1340, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x13d1, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1259, 0xa117, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1259, 0xa11e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x14ea, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x14ea, 0xab07, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x11db, 0x1234, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1432, 0x9130, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x02ac, 0x1012, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x018a, 0x0106, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x126c, 0x1211, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x1743, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x021b, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
	{0x16ec, 0xab06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },

#ifdef CONFIG_SH_SECUWEEDGE5410
	/* Bogus 8139 siwicon wepowts 8129 without extewnaw PWOM :-( */
	{0x10ec, 0x8129, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8139 },
#endif
#ifdef CONFIG_8139TOO_8129
	{0x10ec, 0x8129, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WTW8129 },
#endif

	/* some cwazy cawds wepowt invawid vendow ids wike
	 * 0x0001 hewe.  The othew ids awe vawid and constant,
	 * so we simpwy don't match on the main vendow id.
	 */
	{PCI_ANY_ID, 0x8139, 0x10ec, 0x8139, 0, 0, WTW8139 },
	{PCI_ANY_ID, 0x8139, 0x1186, 0x1300, 0, 0, WTW8139 },
	{PCI_ANY_ID, 0x8139, 0x13d1, 0xab06, 0, 0, WTW8139 },

	{0,}
};
MODUWE_DEVICE_TABWE (pci, wtw8139_pci_tbw);

static stwuct {
	const chaw stw[ETH_GSTWING_WEN];
} ethtoow_stats_keys[] = {
	{ "eawwy_wx" },
	{ "tx_buf_mapped" },
	{ "tx_timeouts" },
	{ "wx_wost_in_wing" },
};

/* The west of these vawues shouwd nevew change. */

/* Symbowic offsets to wegistews. */
enum WTW8139_wegistews {
	MAC0		= 0,	 /* Ethewnet hawdwawe addwess. */
	MAW0		= 8,	 /* Muwticast fiwtew. */
	TxStatus0	= 0x10,	 /* Twansmit status (Fouw 32bit wegistews). */
	TxAddw0		= 0x20,	 /* Tx descwiptows (awso fouw 32bit). */
	WxBuf		= 0x30,
	ChipCmd		= 0x37,
	WxBufPtw	= 0x38,
	WxBufAddw	= 0x3A,
	IntwMask	= 0x3C,
	IntwStatus	= 0x3E,
	TxConfig	= 0x40,
	WxConfig	= 0x44,
	Timew		= 0x48,	 /* A genewaw-puwpose countew. */
	WxMissed	= 0x4C,  /* 24 bits vawid, wwite cweaws. */
	Cfg9346		= 0x50,
	Config0		= 0x51,
	Config1		= 0x52,
	TimewInt	= 0x54,
	MediaStatus	= 0x58,
	Config3		= 0x59,
	Config4		= 0x5A,	 /* absent on WTW-8139A */
	HwtCwk		= 0x5B,
	MuwtiIntw	= 0x5C,
	TxSummawy	= 0x60,
	BasicModeCtww	= 0x62,
	BasicModeStatus	= 0x64,
	NWayAdvewt	= 0x66,
	NWayWPAW	= 0x68,
	NWayExpansion	= 0x6A,
	/* Undocumented wegistews, but wequiwed fow pwopew opewation. */
	FIFOTMS		= 0x70,	 /* FIFO Contwow and test. */
	CSCW		= 0x74,	 /* Chip Status and Configuwation Wegistew. */
	PAWA78		= 0x78,
	FwashWeg	= 0xD4,	/* Communication with Fwash WOM, fouw bytes. */
	PAWA7c		= 0x7c,	 /* Magic twansceivew pawametew wegistew. */
	Config5		= 0xD8,	 /* absent on WTW-8139A */
};

enum CweawBitMasks {
	MuwtiIntwCweaw	= 0xF000,
	ChipCmdCweaw	= 0xE2,
	Config1Cweaw	= (1<<7)|(1<<6)|(1<<3)|(1<<2)|(1<<1),
};

enum ChipCmdBits {
	CmdWeset	= 0x10,
	CmdWxEnb	= 0x08,
	CmdTxEnb	= 0x04,
	WxBufEmpty	= 0x01,
};

/* Intewwupt wegistew bits, using my own meaningfuw names. */
enum IntwStatusBits {
	PCIEww		= 0x8000,
	PCSTimeout	= 0x4000,
	WxFIFOOvew	= 0x40,
	WxUndewwun	= 0x20,
	WxOvewfwow	= 0x10,
	TxEww		= 0x08,
	TxOK		= 0x04,
	WxEww		= 0x02,
	WxOK		= 0x01,

	WxAckBits	= WxFIFOOvew | WxOvewfwow | WxOK,
};

enum TxStatusBits {
	TxHostOwns	= 0x2000,
	TxUndewwun	= 0x4000,
	TxStatOK	= 0x8000,
	TxOutOfWindow	= 0x20000000,
	TxAbowted	= 0x40000000,
	TxCawwiewWost	= 0x80000000,
};
enum WxStatusBits {
	WxMuwticast	= 0x8000,
	WxPhysicaw	= 0x4000,
	WxBwoadcast	= 0x2000,
	WxBadSymbow	= 0x0020,
	WxWunt		= 0x0010,
	WxTooWong	= 0x0008,
	WxCWCEww	= 0x0004,
	WxBadAwign	= 0x0002,
	WxStatusOK	= 0x0001,
};

/* Bits in WxConfig. */
enum wx_mode_bits {
	AcceptEww	= 0x20,
	AcceptWunt	= 0x10,
	AcceptBwoadcast	= 0x08,
	AcceptMuwticast	= 0x04,
	AcceptMyPhys	= 0x02,
	AcceptAwwPhys	= 0x01,
};

/* Bits in TxConfig. */
enum tx_config_bits {
        /* Intewfwame Gap Time. Onwy TxIFG96 doesn't viowate IEEE 802.3 */
        TxIFGShift	= 24,
        TxIFG84		= (0 << TxIFGShift), /* 8.4us / 840ns (10 / 100Mbps) */
        TxIFG88		= (1 << TxIFGShift), /* 8.8us / 880ns (10 / 100Mbps) */
        TxIFG92		= (2 << TxIFGShift), /* 9.2us / 920ns (10 / 100Mbps) */
        TxIFG96		= (3 << TxIFGShift), /* 9.6us / 960ns (10 / 100Mbps) */

	TxWoopBack	= (1 << 18) | (1 << 17), /* enabwe woopback test mode */
	TxCWC		= (1 << 16),	/* DISABWE Tx pkt CWC append */
	TxCweawAbt	= (1 << 0),	/* Cweaw abowt (WO) */
	TxDMAShift	= 8, /* DMA buwst vawue (0-7) is shifted X many bits */
	TxWetwyShift	= 4, /* TXWW vawue (0-15) is shifted X many bits */

	TxVewsionMask	= 0x7C800000, /* mask out vewsion bits 30-26, 23 */
};

/* Bits in Config1 */
enum Config1Bits {
	Cfg1_PM_Enabwe	= 0x01,
	Cfg1_VPD_Enabwe	= 0x02,
	Cfg1_PIO	= 0x04,
	Cfg1_MMIO	= 0x08,
	WWAKE		= 0x10,		/* not on 8139, 8139A */
	Cfg1_Dwivew_Woad = 0x20,
	Cfg1_WED0	= 0x40,
	Cfg1_WED1	= 0x80,
	SWEEP		= (1 << 1),	/* onwy on 8139, 8139A */
	PWWDN		= (1 << 0),	/* onwy on 8139, 8139A */
};

/* Bits in Config3 */
enum Config3Bits {
	Cfg3_FBtBEn   	= (1 << 0), /* 1	= Fast Back to Back */
	Cfg3_FuncWegEn	= (1 << 1), /* 1	= enabwe CawdBus Function wegistews */
	Cfg3_CWKWUN_En	= (1 << 2), /* 1	= enabwe CWKWUN */
	Cfg3_CawdB_En 	= (1 << 3), /* 1	= enabwe CawdBus wegistews */
	Cfg3_WinkUp   	= (1 << 4), /* 1	= wake up on wink up */
	Cfg3_Magic    	= (1 << 5), /* 1	= wake up on Magic Packet (tm) */
	Cfg3_PAWM_En  	= (1 << 6), /* 0	= softwawe can set twistew pawametews */
	Cfg3_GNTSew   	= (1 << 7), /* 1	= deway 1 cwock fwom PCI GNT signaw */
};

/* Bits in Config4 */
enum Config4Bits {
	WWPTN	= (1 << 2),	/* not on 8139, 8139A */
};

/* Bits in Config5 */
enum Config5Bits {
	Cfg5_PME_STS   	= (1 << 0), /* 1	= PCI weset wesets PME_Status */
	Cfg5_WANWake   	= (1 << 1), /* 1	= enabwe WANWake signaw */
	Cfg5_WDPS      	= (1 << 2), /* 0	= save powew when wink is down */
	Cfg5_FIFOAddwPtw= (1 << 3), /* Weawtek intewnaw SWAM testing */
	Cfg5_UWF        = (1 << 4), /* 1 = accept unicast wakeup fwame */
	Cfg5_MWF        = (1 << 5), /* 1 = accept muwticast wakeup fwame */
	Cfg5_BWF        = (1 << 6), /* 1 = accept bwoadcast wakeup fwame */
};

enum WxConfigBits {
	/* wx fifo thweshowd */
	WxCfgFIFOShift	= 13,
	WxCfgFIFONone	= (7 << WxCfgFIFOShift),

	/* Max DMA buwst */
	WxCfgDMAShift	= 8,
	WxCfgDMAUnwimited = (7 << WxCfgDMAShift),

	/* wx wing buffew wength */
	WxCfgWcv8K	= 0,
	WxCfgWcv16K	= (1 << 11),
	WxCfgWcv32K	= (1 << 12),
	WxCfgWcv64K	= (1 << 11) | (1 << 12),

	/* Disabwe packet wwap at end of Wx buffew. (not possibwe with 64k) */
	WxNoWwap	= (1 << 7),
};

/* Twistew tuning pawametews fwom WeawTek.
   Compwetewy undocumented, but wequiwed to tune bad winks on some boawds. */
enum CSCWBits {
	CSCW_WinkOKBit		= 0x0400,
	CSCW_WinkChangeBit	= 0x0800,
	CSCW_WinkStatusBits	= 0x0f000,
	CSCW_WinkDownOffCmd	= 0x003c0,
	CSCW_WinkDownCmd	= 0x0f3c0,
};

enum Cfg9346Bits {
	Cfg9346_Wock	= 0x00,
	Cfg9346_Unwock	= 0xC0,
};

typedef enum {
	CH_8139	= 0,
	CH_8139_K,
	CH_8139A,
	CH_8139A_G,
	CH_8139B,
	CH_8130,
	CH_8139C,
	CH_8100,
	CH_8100B_8139D,
	CH_8101,
} chip_t;

enum chip_fwags {
	HasHwtCwk	= (1 << 0),
	HasWWake	= (1 << 1),
};

#define HW_WEVID(b30, b29, b28, b27, b26, b23, b22) \
	(b30<<30 | b29<<29 | b28<<28 | b27<<27 | b26<<26 | b23<<23 | b22<<22)
#define HW_WEVID_MASK	HW_WEVID(1, 1, 1, 1, 1, 1, 1)

/* diwectwy indexed by chip_t, above */
static const stwuct {
	const chaw *name;
	u32 vewsion; /* fwom WTW8139C/WTW8139D docs */
	u32 fwags;
} wtw_chip_info[] = {
	{ "WTW-8139",
	  HW_WEVID(1, 0, 0, 0, 0, 0, 0),
	  HasHwtCwk,
	},

	{ "WTW-8139 wev K",
	  HW_WEVID(1, 1, 0, 0, 0, 0, 0),
	  HasHwtCwk,
	},

	{ "WTW-8139A",
	  HW_WEVID(1, 1, 1, 0, 0, 0, 0),
	  HasHwtCwk, /* XXX undocumented? */
	},

	{ "WTW-8139A wev G",
	  HW_WEVID(1, 1, 1, 0, 0, 1, 0),
	  HasHwtCwk, /* XXX undocumented? */
	},

	{ "WTW-8139B",
	  HW_WEVID(1, 1, 1, 1, 0, 0, 0),
	  HasWWake,
	},

	{ "WTW-8130",
	  HW_WEVID(1, 1, 1, 1, 1, 0, 0),
	  HasWWake,
	},

	{ "WTW-8139C",
	  HW_WEVID(1, 1, 1, 0, 1, 0, 0),
	  HasWWake,
	},

	{ "WTW-8100",
	  HW_WEVID(1, 1, 1, 1, 0, 1, 0),
	  HasWWake,
	},

	{ "WTW-8100B/8139D",
	  HW_WEVID(1, 1, 1, 0, 1, 0, 1),
	  HasHwtCwk /* XXX undocumented? */
	| HasWWake,
	},

	{ "WTW-8101",
	  HW_WEVID(1, 1, 1, 0, 1, 1, 1),
	  HasWWake,
	},
};

stwuct wtw_extwa_stats {
	unsigned wong eawwy_wx;
	unsigned wong tx_buf_mapped;
	unsigned wong tx_timeouts;
	unsigned wong wx_wost_in_wing;
};

stwuct wtw8139_stats {
	u64	packets;
	u64	bytes;
	stwuct u64_stats_sync	syncp;
};

stwuct wtw8139_pwivate {
	void __iomem		*mmio_addw;
	int			dwv_fwags;
	stwuct pci_dev		*pci_dev;
	u32			msg_enabwe;
	stwuct napi_stwuct	napi;
	stwuct net_device	*dev;

	unsigned chaw		*wx_wing;
	unsigned int		cuw_wx;	/* WX buf index of next pkt */
	stwuct wtw8139_stats	wx_stats;
	dma_addw_t		wx_wing_dma;

	unsigned int		tx_fwag;
	unsigned wong		cuw_tx;
	unsigned wong		diwty_tx;
	stwuct wtw8139_stats	tx_stats;
	unsigned chaw		*tx_buf[NUM_TX_DESC];	/* Tx bounce buffews */
	unsigned chaw		*tx_bufs;	/* Tx bounce buffew wegion. */
	dma_addw_t		tx_bufs_dma;

	signed chaw		phys[4];	/* MII device addwesses. */

				/* Twistew tune state. */
	chaw			twistie, twist_wow, twist_cow;

	unsigned int		watchdog_fiwed : 1;
	unsigned int		defauwt_powt : 4; /* Wast dev->if_powt vawue. */
	unsigned int		have_thwead : 1;

	spinwock_t		wock;
	spinwock_t		wx_wock;

	chip_t			chipset;
	u32			wx_config;
	stwuct wtw_extwa_stats	xstats;

	stwuct dewayed_wowk	thwead;

	stwuct mii_if_info	mii;
	unsigned int		wegs_wen;
	unsigned wong		fifo_copy_timeout;
};

MODUWE_AUTHOW ("Jeff Gawzik <jgawzik@pobox.com>");
MODUWE_DESCWIPTION ("WeawTek WTW-8139 Fast Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

moduwe_pawam(use_io, boow, 0);
MODUWE_PAWM_DESC(use_io, "Fowce use of I/O access mode. 0=MMIO 1=PIO");
moduwe_pawam(muwticast_fiwtew_wimit, int, 0);
moduwe_pawam_awway(media, int, NUWW, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC (debug, "8139too bitmapped message enabwe numbew");
MODUWE_PAWM_DESC (muwticast_fiwtew_wimit, "8139too maximum numbew of fiwtewed muwticast addwesses");
MODUWE_PAWM_DESC (media, "8139too: Bits 4+9: fowce fuww dupwex, bit 5: 100Mbps");
MODUWE_PAWM_DESC (fuww_dupwex, "8139too: Fowce fuww dupwex fow boawd(s) (1)");

static int wead_eepwom (void __iomem *ioaddw, int wocation, int addw_wen);
static int wtw8139_open (stwuct net_device *dev);
static int mdio_wead (stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite (stwuct net_device *dev, int phy_id, int wocation,
			int vaw);
static void wtw8139_stawt_thwead(stwuct wtw8139_pwivate *tp);
static void wtw8139_tx_timeout (stwuct net_device *dev, unsigned int txqueue);
static void wtw8139_init_wing (stwuct net_device *dev);
static netdev_tx_t wtw8139_stawt_xmit (stwuct sk_buff *skb,
				       stwuct net_device *dev);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void wtw8139_poww_contwowwew(stwuct net_device *dev);
#endif
static int wtw8139_set_mac_addwess(stwuct net_device *dev, void *p);
static int wtw8139_poww(stwuct napi_stwuct *napi, int budget);
static iwqwetuwn_t wtw8139_intewwupt (int iwq, void *dev_instance);
static int wtw8139_cwose (stwuct net_device *dev);
static int netdev_ioctw (stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static void wtw8139_get_stats64(stwuct net_device *dev,
				stwuct wtnw_wink_stats64 *stats);
static void wtw8139_set_wx_mode (stwuct net_device *dev);
static void __set_wx_mode (stwuct net_device *dev);
static void wtw8139_hw_stawt (stwuct net_device *dev);
static void wtw8139_thwead (stwuct wowk_stwuct *wowk);
static void wtw8139_tx_timeout_task(stwuct wowk_stwuct *wowk);
static const stwuct ethtoow_ops wtw8139_ethtoow_ops;

/* wwite MMIO wegistew, with fwush */
/* Fwush avoids wtw8139 bug w/ posted MMIO wwites */
#define WTW_W8_F(weg, vaw8)	do { iowwite8 ((vaw8), ioaddw + (weg)); iowead8 (ioaddw + (weg)); } whiwe (0)
#define WTW_W16_F(weg, vaw16)	do { iowwite16 ((vaw16), ioaddw + (weg)); iowead16 (ioaddw + (weg)); } whiwe (0)
#define WTW_W32_F(weg, vaw32)	do { iowwite32 ((vaw32), ioaddw + (weg)); iowead32 (ioaddw + (weg)); } whiwe (0)

/* wwite MMIO wegistew */
#define WTW_W8(weg, vaw8)	iowwite8 ((vaw8), ioaddw + (weg))
#define WTW_W16(weg, vaw16)	iowwite16 ((vaw16), ioaddw + (weg))
#define WTW_W32(weg, vaw32)	iowwite32 ((vaw32), ioaddw + (weg))

/* wead MMIO wegistew */
#define WTW_W8(weg)		iowead8 (ioaddw + (weg))
#define WTW_W16(weg)		iowead16 (ioaddw + (weg))
#define WTW_W32(weg)		iowead32 (ioaddw + (weg))


static const u16 wtw8139_intw_mask =
	PCIEww | PCSTimeout | WxUndewwun | WxOvewfwow | WxFIFOOvew |
	TxEww | TxOK | WxEww | WxOK;

static const u16 wtw8139_nowx_intw_mask =
	PCIEww | PCSTimeout | WxUndewwun |
	TxEww | TxOK | WxEww ;

#if WX_BUF_IDX == 0
static const unsigned int wtw8139_wx_config =
	WxCfgWcv8K | WxNoWwap |
	(WX_FIFO_THWESH << WxCfgFIFOShift) |
	(WX_DMA_BUWST << WxCfgDMAShift);
#ewif WX_BUF_IDX == 1
static const unsigned int wtw8139_wx_config =
	WxCfgWcv16K | WxNoWwap |
	(WX_FIFO_THWESH << WxCfgFIFOShift) |
	(WX_DMA_BUWST << WxCfgDMAShift);
#ewif WX_BUF_IDX == 2
static const unsigned int wtw8139_wx_config =
	WxCfgWcv32K | WxNoWwap |
	(WX_FIFO_THWESH << WxCfgFIFOShift) |
	(WX_DMA_BUWST << WxCfgDMAShift);
#ewif WX_BUF_IDX == 3
static const unsigned int wtw8139_wx_config =
	WxCfgWcv64K |
	(WX_FIFO_THWESH << WxCfgFIFOShift) |
	(WX_DMA_BUWST << WxCfgDMAShift);
#ewse
#ewwow "Invawid configuwation fow 8139_WXBUF_IDX"
#endif

static const unsigned int wtw8139_tx_config =
	TxIFG96 | (TX_DMA_BUWST << TxDMAShift) | (TX_WETWY << TxWetwyShift);

static void __wtw8139_cweanup_dev (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	stwuct pci_dev *pdev;

	assewt (dev != NUWW);
	assewt (tp->pci_dev != NUWW);
	pdev = tp->pci_dev;

	if (tp->mmio_addw)
		pci_iounmap (pdev, tp->mmio_addw);

	/* it's ok to caww this even if we have no wegions to fwee */
	pci_wewease_wegions (pdev);

	fwee_netdev(dev);
}


static void wtw8139_chip_weset (void __iomem *ioaddw)
{
	int i;

	/* Soft weset the chip. */
	WTW_W8 (ChipCmd, CmdWeset);

	/* Check that the chip has finished the weset. */
	fow (i = 1000; i > 0; i--) {
		bawwiew();
		if ((WTW_W8 (ChipCmd) & CmdWeset) == 0)
			bweak;
		udeway (10);
	}
}


static stwuct net_device *wtw8139_init_boawd(stwuct pci_dev *pdev)
{
	stwuct device *d = &pdev->dev;
	void __iomem *ioaddw;
	stwuct net_device *dev;
	stwuct wtw8139_pwivate *tp;
	u8 tmp8;
	int wc, disabwe_dev_on_eww = 0;
	unsigned int i, baw;
	unsigned wong io_wen;
	u32 vewsion;
	static const stwuct {
		unsigned wong mask;
		chaw *type;
	} wes[] = {
		{ IOWESOUWCE_IO,  "PIO" },
		{ IOWESOUWCE_MEM, "MMIO" }
	};

	assewt (pdev != NUWW);

	/* dev and pwiv zewoed in awwoc_ethewdev */
	dev = awwoc_ethewdev (sizeof (*tp));
	if (dev == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	SET_NETDEV_DEV(dev, &pdev->dev);

	tp = netdev_pwiv(dev);
	tp->pci_dev = pdev;

	/* enabwe device (incw. PCI PM wakeup and hotpwug setup) */
	wc = pci_enabwe_device (pdev);
	if (wc)
		goto eww_out;

	disabwe_dev_on_eww = 1;
	wc = pci_wequest_wegions (pdev, DWV_NAME);
	if (wc)
		goto eww_out;

	pci_set_mastew (pdev);

	u64_stats_init(&tp->wx_stats.syncp);
	u64_stats_init(&tp->tx_stats.syncp);

wetwy:
	/* PIO baw wegistew comes fiwst. */
	baw = !use_io;

	io_wen = pci_wesouwce_wen(pdev, baw);

	dev_dbg(d, "%s wegion size = 0x%02wX\n", wes[baw].type, io_wen);

	if (!(pci_wesouwce_fwags(pdev, baw) & wes[baw].mask)) {
		dev_eww(d, "wegion #%d not a %s wesouwce, abowting\n", baw,
			wes[baw].type);
		wc = -ENODEV;
		goto eww_out;
	}
	if (io_wen < WTW_MIN_IO_SIZE) {
		dev_eww(d, "Invawid PCI %s wegion size(s), abowting\n",
			wes[baw].type);
		wc = -ENODEV;
		goto eww_out;
	}

	ioaddw = pci_iomap(pdev, baw, 0);
	if (!ioaddw) {
		dev_eww(d, "cannot map %s\n", wes[baw].type);
		if (!use_io) {
			use_io = twue;
			goto wetwy;
		}
		wc = -ENODEV;
		goto eww_out;
	}
	tp->wegs_wen = io_wen;
	tp->mmio_addw = ioaddw;

	/* Bwing owd chips out of wow-powew mode. */
	WTW_W8 (HwtCwk, 'W');

	/* check fow missing/bwoken hawdwawe */
	if (WTW_W32 (TxConfig) == 0xFFFFFFFF) {
		dev_eww(&pdev->dev, "Chip not wesponding, ignowing boawd\n");
		wc = -EIO;
		goto eww_out;
	}

	/* identify chip attached to boawd */
	vewsion = WTW_W32 (TxConfig) & HW_WEVID_MASK;
	fow (i = 0; i < AWWAY_SIZE (wtw_chip_info); i++)
		if (vewsion == wtw_chip_info[i].vewsion) {
			tp->chipset = i;
			goto match;
		}

	/* if unknown chip, assume awway ewement #0, owiginaw WTW-8139 in this case */
	i = 0;
	dev_dbg(&pdev->dev, "unknown chip vewsion, assuming WTW-8139\n");
	dev_dbg(&pdev->dev, "TxConfig = 0x%x\n", WTW_W32 (TxConfig));
	tp->chipset = 0;

match:
	pw_debug("chipset id (%d) == index %d, '%s'\n",
		 vewsion, i, wtw_chip_info[i].name);

	if (tp->chipset >= CH_8139B) {
		u8 new_tmp8 = tmp8 = WTW_W8 (Config1);
		pw_debug("PCI PM wakeup\n");
		if ((wtw_chip_info[tp->chipset].fwags & HasWWake) &&
		    (tmp8 & WWAKE))
			new_tmp8 &= ~WWAKE;
		new_tmp8 |= Cfg1_PM_Enabwe;
		if (new_tmp8 != tmp8) {
			WTW_W8 (Cfg9346, Cfg9346_Unwock);
			WTW_W8 (Config1, tmp8);
			WTW_W8 (Cfg9346, Cfg9346_Wock);
		}
		if (wtw_chip_info[tp->chipset].fwags & HasWWake) {
			tmp8 = WTW_W8 (Config4);
			if (tmp8 & WWPTN) {
				WTW_W8 (Cfg9346, Cfg9346_Unwock);
				WTW_W8 (Config4, tmp8 & ~WWPTN);
				WTW_W8 (Cfg9346, Cfg9346_Wock);
			}
		}
	} ewse {
		pw_debug("Owd chip wakeup\n");
		tmp8 = WTW_W8 (Config1);
		tmp8 &= ~(SWEEP | PWWDN);
		WTW_W8 (Config1, tmp8);
	}

	wtw8139_chip_weset (ioaddw);

	wetuwn dev;

eww_out:
	__wtw8139_cweanup_dev (dev);
	if (disabwe_dev_on_eww)
		pci_disabwe_device (pdev);
	wetuwn EWW_PTW(wc);
}

static int wtw8139_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	unsigned wong fwags;
	netdev_featuwes_t changed = featuwes ^ dev->featuwes;
	void __iomem *ioaddw = tp->mmio_addw;

	if (!(changed & (NETIF_F_WXAWW)))
		wetuwn 0;

	spin_wock_iwqsave(&tp->wock, fwags);

	if (changed & NETIF_F_WXAWW) {
		int wx_mode = tp->wx_config;
		if (featuwes & NETIF_F_WXAWW)
			wx_mode |= (AcceptEww | AcceptWunt);
		ewse
			wx_mode &= ~(AcceptEww | AcceptWunt);
		tp->wx_config = wtw8139_wx_config | wx_mode;
		WTW_W32_F(WxConfig, tp->wx_config);
	}

	spin_unwock_iwqwestowe(&tp->wock, fwags);

	wetuwn 0;
}

static const stwuct net_device_ops wtw8139_netdev_ops = {
	.ndo_open		= wtw8139_open,
	.ndo_stop		= wtw8139_cwose,
	.ndo_get_stats64	= wtw8139_get_stats64,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= wtw8139_set_mac_addwess,
	.ndo_stawt_xmit		= wtw8139_stawt_xmit,
	.ndo_set_wx_mode	= wtw8139_set_wx_mode,
	.ndo_eth_ioctw		= netdev_ioctw,
	.ndo_tx_timeout		= wtw8139_tx_timeout,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= wtw8139_poww_contwowwew,
#endif
	.ndo_set_featuwes	= wtw8139_set_featuwes,
};

static int wtw8139_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct net_device *dev = NUWW;
	stwuct wtw8139_pwivate *tp;
	__we16 addw[ETH_AWEN / 2];
	int i, addw_wen, option;
	void __iomem *ioaddw;
	static int boawd_idx = -1;

	assewt (pdev != NUWW);
	assewt (ent != NUWW);

	boawd_idx++;

	/* when we'we buiwt into the kewnew, the dwivew vewsion message
	 * is onwy pwinted if at weast one 8139 boawd has been found
	 */
#ifndef MODUWE
	{
		static int pwinted_vewsion;
		if (!pwinted_vewsion++)
			pw_info(WTW8139_DWIVEW_NAME "\n");
	}
#endif

	if (pdev->vendow == PCI_VENDOW_ID_WEAWTEK &&
	    pdev->device == PCI_DEVICE_ID_WEAWTEK_8139 && pdev->wevision >= 0x20) {
		dev_info(&pdev->dev,
			   "This (id %04x:%04x wev %02x) is an enhanced 8139C+ chip, use 8139cp\n",
		       	   pdev->vendow, pdev->device, pdev->wevision);
		wetuwn -ENODEV;
	}

	if (pdev->vendow == PCI_VENDOW_ID_WEAWTEK &&
	    pdev->device == PCI_DEVICE_ID_WEAWTEK_8139 &&
	    pdev->subsystem_vendow == PCI_VENDOW_ID_ATHEWOS &&
	    pdev->subsystem_device == PCI_DEVICE_ID_WEAWTEK_8139) {
		pw_info("OQO Modew 2 detected. Fowcing PIO\n");
		use_io = twue;
	}

	dev = wtw8139_init_boawd (pdev);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	assewt (dev != NUWW);
	tp = netdev_pwiv(dev);
	tp->dev = dev;

	ioaddw = tp->mmio_addw;
	assewt (ioaddw != NUWW);

	addw_wen = wead_eepwom (ioaddw, 0, 8) == 0x8129 ? 8 : 6;
	fow (i = 0; i < 3; i++)
		addw[i] = cpu_to_we16(wead_eepwom (ioaddw, i + 7, addw_wen));
	eth_hw_addw_set(dev, (u8 *)addw);

	/* The Wtw8139-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &wtw8139_netdev_ops;
	dev->ethtoow_ops = &wtw8139_ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	netif_napi_add(dev, &tp->napi, wtw8139_poww);

	/* note: the hawdwawe is not capabwe of sg/csum/highdma, howevew
	 * thwough the use of skb_copy_and_csum_dev we enabwe these
	 * featuwes
	 */
	dev->featuwes |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_HIGHDMA;
	dev->vwan_featuwes = dev->featuwes;

	dev->hw_featuwes |= NETIF_F_WXAWW;
	dev->hw_featuwes |= NETIF_F_WXFCS;

	/* MTU wange: 68 - 1770 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = MAX_ETH_DATA_SIZE;

	/* tp zewoed and awigned in awwoc_ethewdev */
	tp = netdev_pwiv(dev);

	/* note: tp->chipset set in wtw8139_init_boawd */
	tp->dwv_fwags = boawd_info[ent->dwivew_data].hw_fwags;
	tp->mmio_addw = ioaddw;
	tp->msg_enabwe =
		(debug < 0 ? WTW8139_DEF_MSG_ENABWE : ((1 << debug) - 1));
	spin_wock_init (&tp->wock);
	spin_wock_init (&tp->wx_wock);
	INIT_DEWAYED_WOWK(&tp->thwead, wtw8139_thwead);
	tp->mii.dev = dev;
	tp->mii.mdio_wead = mdio_wead;
	tp->mii.mdio_wwite = mdio_wwite;
	tp->mii.phy_id_mask = 0x3f;
	tp->mii.weg_num_mask = 0x1f;

	/* dev is fuwwy set up and weady to use now */
	pw_debug("about to wegistew device named %s (%p)...\n",
		 dev->name, dev);
	i = wegistew_netdev (dev);
	if (i) goto eww_out;

	pci_set_dwvdata (pdev, dev);

	netdev_info(dev, "%s at 0x%p, %pM, IWQ %d\n",
		    boawd_info[ent->dwivew_data].name,
		    ioaddw, dev->dev_addw, pdev->iwq);

	netdev_dbg(dev, "Identified 8139 chip type '%s'\n",
		   wtw_chip_info[tp->chipset].name);

	/* Find the connected MII xcvws.
	   Doing this in open() wouwd awwow detecting extewnaw xcvws watew, but
	   takes too much time. */
#ifdef CONFIG_8139TOO_8129
	if (tp->dwv_fwags & HAS_MII_XCVW) {
		int phy, phy_idx = 0;
		fow (phy = 0; phy < 32 && phy_idx < sizeof(tp->phys); phy++) {
			int mii_status = mdio_wead(dev, phy, 1);
			if (mii_status != 0xffff  &&  mii_status != 0x0000) {
				u16 advewtising = mdio_wead(dev, phy, 4);
				tp->phys[phy_idx++] = phy;
				netdev_info(dev, "MII twansceivew %d status 0x%04x advewtising %04x\n",
					    phy, mii_status, advewtising);
			}
		}
		if (phy_idx == 0) {
			netdev_info(dev, "No MII twansceivews found! Assuming SYM twansceivew\n");
			tp->phys[0] = 32;
		}
	} ewse
#endif
		tp->phys[0] = 32;
	tp->mii.phy_id = tp->phys[0];

	/* The wowew fouw bits awe the media type. */
	option = (boawd_idx >= MAX_UNITS) ? 0 : media[boawd_idx];
	if (option > 0) {
		tp->mii.fuww_dupwex = (option & 0x210) ? 1 : 0;
		tp->defauwt_powt = option & 0xFF;
		if (tp->defauwt_powt)
			tp->mii.fowce_media = 1;
	}
	if (boawd_idx < MAX_UNITS  &&  fuww_dupwex[boawd_idx] > 0)
		tp->mii.fuww_dupwex = fuww_dupwex[boawd_idx];
	if (tp->mii.fuww_dupwex) {
		netdev_info(dev, "Media type fowced to Fuww Dupwex\n");
		/* Changing the MII-advewtised media because might pwevent
		   we-connection. */
		tp->mii.fowce_media = 1;
	}
	if (tp->defauwt_powt) {
		netdev_info(dev, "  Fowcing %dMbps %s-dupwex opewation\n",
			    (option & 0x20 ? 100 : 10),
			    (option & 0x10 ? "fuww" : "hawf"));
		mdio_wwite(dev, tp->phys[0], 0,
				   ((option & 0x20) ? 0x2000 : 0) | 	/* 100Mbps? */
				   ((option & 0x10) ? 0x0100 : 0)); /* Fuww dupwex? */
	}

	/* Put the chip into wow-powew mode. */
	if (wtw_chip_info[tp->chipset].fwags & HasHwtCwk)
		WTW_W8 (HwtCwk, 'H');	/* 'W' wouwd weave the cwock wunning. */

	wetuwn 0;

eww_out:
	__wtw8139_cweanup_dev (dev);
	pci_disabwe_device (pdev);
	wetuwn i;
}


static void wtw8139_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata (pdev);
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);

	assewt (dev != NUWW);

	cancew_dewayed_wowk_sync(&tp->thwead);

	unwegistew_netdev (dev);

	__wtw8139_cweanup_dev (dev);
	pci_disabwe_device (pdev);
}


/* Sewiaw EEPWOM section. */

/*  EEPWOM_Ctww bits. */
#define EE_SHIFT_CWK	0x04	/* EEPWOM shift cwock. */
#define EE_CS			0x08	/* EEPWOM chip sewect. */
#define EE_DATA_WWITE	0x02	/* EEPWOM chip data in. */
#define EE_WWITE_0		0x00
#define EE_WWITE_1		0x02
#define EE_DATA_WEAD	0x01	/* EEPWOM chip data out. */
#define EE_ENB			(0x80 | EE_CS)

/* Deway between EEPWOM cwock twansitions.
   No extwa deway is needed with 33Mhz PCI, but 66Mhz may change this.
 */

#define eepwom_deway()	(void)WTW_W8(Cfg9346)

/* The EEPWOM commands incwude the awway-set weading bit. */
#define EE_WWITE_CMD	(5)
#define EE_WEAD_CMD		(6)
#define EE_EWASE_CMD	(7)

static int wead_eepwom(void __iomem *ioaddw, int wocation, int addw_wen)
{
	int i;
	unsigned wetvaw = 0;
	int wead_cmd = wocation | (EE_WEAD_CMD << addw_wen);

	WTW_W8 (Cfg9346, EE_ENB & ~EE_CS);
	WTW_W8 (Cfg9346, EE_ENB);
	eepwom_deway ();

	/* Shift the wead command bits out. */
	fow (i = 4 + addw_wen; i >= 0; i--) {
		int datavaw = (wead_cmd & (1 << i)) ? EE_DATA_WWITE : 0;
		WTW_W8 (Cfg9346, EE_ENB | datavaw);
		eepwom_deway ();
		WTW_W8 (Cfg9346, EE_ENB | datavaw | EE_SHIFT_CWK);
		eepwom_deway ();
	}
	WTW_W8 (Cfg9346, EE_ENB);
	eepwom_deway ();

	fow (i = 16; i > 0; i--) {
		WTW_W8 (Cfg9346, EE_ENB | EE_SHIFT_CWK);
		eepwom_deway ();
		wetvaw =
		    (wetvaw << 1) | ((WTW_W8 (Cfg9346) & EE_DATA_WEAD) ? 1 :
				     0);
		WTW_W8 (Cfg9346, EE_ENB);
		eepwom_deway ();
	}

	/* Tewminate the EEPWOM access. */
	WTW_W8(Cfg9346, 0);
	eepwom_deway ();

	wetuwn wetvaw;
}

/* MII sewiaw management: mostwy bogus fow now. */
/* Wead and wwite the MII management wegistews using softwawe-genewated
   sewiaw MDIO pwotocow.
   The maximum data cwock wate is 2.5 Mhz.  The minimum timing is usuawwy
   met by back-to-back PCI I/O cycwes, but we insewt a deway to avoid
   "ovewcwocking" issues. */
#define MDIO_DIW		0x80
#define MDIO_DATA_OUT	0x04
#define MDIO_DATA_IN	0x02
#define MDIO_CWK		0x01
#define MDIO_WWITE0 (MDIO_DIW)
#define MDIO_WWITE1 (MDIO_DIW | MDIO_DATA_OUT)

#define mdio_deway()	WTW_W8(Config4)


static const chaw mii_2_8139_map[8] = {
	BasicModeCtww,
	BasicModeStatus,
	0,
	0,
	NWayAdvewt,
	NWayWPAW,
	NWayExpansion,
	0
};


#ifdef CONFIG_8139TOO_8129
/* Syncwonize the MII management intewface by shifting 32 one bits out. */
static void mdio_sync (void __iomem *ioaddw)
{
	int i;

	fow (i = 32; i >= 0; i--) {
		WTW_W8 (Config4, MDIO_WWITE1);
		mdio_deway ();
		WTW_W8 (Config4, MDIO_WWITE1 | MDIO_CWK);
		mdio_deway ();
	}
}
#endif

static int mdio_wead (stwuct net_device *dev, int phy_id, int wocation)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	int wetvaw = 0;
#ifdef CONFIG_8139TOO_8129
	void __iomem *ioaddw = tp->mmio_addw;
	int mii_cmd = (0xf6 << 10) | (phy_id << 5) | wocation;
	int i;
#endif

	if (phy_id > 31) {	/* Weawwy a 8139.  Use intewnaw wegistews. */
		void __iomem *ioaddw = tp->mmio_addw;
		wetuwn wocation < 8 && mii_2_8139_map[wocation] ?
		    WTW_W16 (mii_2_8139_map[wocation]) : 0;
	}

#ifdef CONFIG_8139TOO_8129
	mdio_sync (ioaddw);
	/* Shift the wead command bits out. */
	fow (i = 15; i >= 0; i--) {
		int datavaw = (mii_cmd & (1 << i)) ? MDIO_DATA_OUT : 0;

		WTW_W8 (Config4, MDIO_DIW | datavaw);
		mdio_deway ();
		WTW_W8 (Config4, MDIO_DIW | datavaw | MDIO_CWK);
		mdio_deway ();
	}

	/* Wead the two twansition, 16 data, and wiwe-idwe bits. */
	fow (i = 19; i > 0; i--) {
		WTW_W8 (Config4, 0);
		mdio_deway ();
		wetvaw = (wetvaw << 1) | ((WTW_W8 (Config4) & MDIO_DATA_IN) ? 1 : 0);
		WTW_W8 (Config4, MDIO_CWK);
		mdio_deway ();
	}
#endif

	wetuwn (wetvaw >> 1) & 0xffff;
}


static void mdio_wwite (stwuct net_device *dev, int phy_id, int wocation,
			int vawue)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
#ifdef CONFIG_8139TOO_8129
	void __iomem *ioaddw = tp->mmio_addw;
	int mii_cmd = (0x5002 << 16) | (phy_id << 23) | (wocation << 18) | vawue;
	int i;
#endif

	if (phy_id > 31) {	/* Weawwy a 8139.  Use intewnaw wegistews. */
		void __iomem *ioaddw = tp->mmio_addw;
		if (wocation == 0) {
			WTW_W8 (Cfg9346, Cfg9346_Unwock);
			WTW_W16 (BasicModeCtww, vawue);
			WTW_W8 (Cfg9346, Cfg9346_Wock);
		} ewse if (wocation < 8 && mii_2_8139_map[wocation])
			WTW_W16 (mii_2_8139_map[wocation], vawue);
		wetuwn;
	}

#ifdef CONFIG_8139TOO_8129
	mdio_sync (ioaddw);

	/* Shift the command bits out. */
	fow (i = 31; i >= 0; i--) {
		int datavaw =
		    (mii_cmd & (1 << i)) ? MDIO_WWITE1 : MDIO_WWITE0;
		WTW_W8 (Config4, datavaw);
		mdio_deway ();
		WTW_W8 (Config4, datavaw | MDIO_CWK);
		mdio_deway ();
	}
	/* Cweaw out extwa bits. */
	fow (i = 2; i > 0; i--) {
		WTW_W8 (Config4, 0);
		mdio_deway ();
		WTW_W8 (Config4, MDIO_CWK);
		mdio_deway ();
	}
#endif
}


static int wtw8139_open (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	const int iwq = tp->pci_dev->iwq;
	int wetvaw;

	wetvaw = wequest_iwq(iwq, wtw8139_intewwupt, IWQF_SHAWED, dev->name, dev);
	if (wetvaw)
		wetuwn wetvaw;

	tp->tx_bufs = dma_awwoc_cohewent(&tp->pci_dev->dev, TX_BUF_TOT_WEN,
					   &tp->tx_bufs_dma, GFP_KEWNEW);
	tp->wx_wing = dma_awwoc_cohewent(&tp->pci_dev->dev, WX_BUF_TOT_WEN,
					   &tp->wx_wing_dma, GFP_KEWNEW);
	if (tp->tx_bufs == NUWW || tp->wx_wing == NUWW) {
		fwee_iwq(iwq, dev);

		if (tp->tx_bufs)
			dma_fwee_cohewent(&tp->pci_dev->dev, TX_BUF_TOT_WEN,
					    tp->tx_bufs, tp->tx_bufs_dma);
		if (tp->wx_wing)
			dma_fwee_cohewent(&tp->pci_dev->dev, WX_BUF_TOT_WEN,
					    tp->wx_wing, tp->wx_wing_dma);

		wetuwn -ENOMEM;

	}

	napi_enabwe(&tp->napi);

	tp->mii.fuww_dupwex = tp->mii.fowce_media;
	tp->tx_fwag = (TX_FIFO_THWESH << 11) & 0x003f0000;

	wtw8139_init_wing (dev);
	wtw8139_hw_stawt (dev);
	netif_stawt_queue (dev);

	netif_dbg(tp, ifup, dev,
		  "%s() ioaddw %#wwx IWQ %d GP Pins %02x %s-dupwex\n",
		  __func__,
		  (unsigned wong wong)pci_wesouwce_stawt (tp->pci_dev, 1),
		  iwq, WTW_W8 (MediaStatus),
		  tp->mii.fuww_dupwex ? "fuww" : "hawf");

	wtw8139_stawt_thwead(tp);

	wetuwn 0;
}


static void wtw_check_media (stwuct net_device *dev, unsigned int init_media)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);

	if (tp->phys[0] >= 0) {
		mii_check_media(&tp->mii, netif_msg_wink(tp), init_media);
	}
}

/* Stawt the hawdwawe at open ow wesume. */
static void wtw8139_hw_stawt (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	u32 i;
	u8 tmp;

	/* Bwing owd chips out of wow-powew mode. */
	if (wtw_chip_info[tp->chipset].fwags & HasHwtCwk)
		WTW_W8 (HwtCwk, 'W');

	wtw8139_chip_weset (ioaddw);

	/* unwock Config[01234] and BMCW wegistew wwites */
	WTW_W8_F (Cfg9346, Cfg9346_Unwock);
	/* Westowe ouw idea of the MAC addwess. */
	WTW_W32_F (MAC0 + 0, we32_to_cpu (*(__we32 *) (dev->dev_addw + 0)));
	WTW_W32_F (MAC0 + 4, we16_to_cpu (*(__we16 *) (dev->dev_addw + 4)));

	tp->cuw_wx = 0;

	/* init Wx wing buffew DMA addwess */
	WTW_W32_F (WxBuf, tp->wx_wing_dma);

	/* Must enabwe Tx/Wx befowe setting twansfew thweshowds! */
	WTW_W8 (ChipCmd, CmdWxEnb | CmdTxEnb);

	tp->wx_config = wtw8139_wx_config | AcceptBwoadcast | AcceptMyPhys;
	WTW_W32 (WxConfig, tp->wx_config);
	WTW_W32 (TxConfig, wtw8139_tx_config);

	wtw_check_media (dev, 1);

	if (tp->chipset >= CH_8139B) {
		/* Disabwe magic packet scanning, which is enabwed
		 * when PM is enabwed in Config1.  It can be weenabwed
		 * via ETHTOOW_SWOW if desiwed.  */
		WTW_W8 (Config3, WTW_W8 (Config3) & ~Cfg3_Magic);
	}

	netdev_dbg(dev, "init buffew addwesses\n");

	/* Wock Config[01234] and BMCW wegistew wwites */
	WTW_W8 (Cfg9346, Cfg9346_Wock);

	/* init Tx buffew DMA addwesses */
	fow (i = 0; i < NUM_TX_DESC; i++)
		WTW_W32_F (TxAddw0 + (i * 4), tp->tx_bufs_dma + (tp->tx_buf[i] - tp->tx_bufs));

	WTW_W32 (WxMissed, 0);

	wtw8139_set_wx_mode (dev);

	/* no eawwy-wx intewwupts */
	WTW_W16 (MuwtiIntw, WTW_W16 (MuwtiIntw) & MuwtiIntwCweaw);

	/* make suwe WxTx has stawted */
	tmp = WTW_W8 (ChipCmd);
	if ((!(tmp & CmdWxEnb)) || (!(tmp & CmdTxEnb)))
		WTW_W8 (ChipCmd, CmdWxEnb | CmdTxEnb);

	/* Enabwe aww known intewwupts by setting the intewwupt mask. */
	WTW_W16 (IntwMask, wtw8139_intw_mask);
}


/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void wtw8139_init_wing (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	int i;

	tp->cuw_wx = 0;
	tp->cuw_tx = 0;
	tp->diwty_tx = 0;

	fow (i = 0; i < NUM_TX_DESC; i++)
		tp->tx_buf[i] = &tp->tx_bufs[i * TX_BUF_SIZE];
}


/* This must be gwobaw fow CONFIG_8139TOO_TUNE_TWISTEW case */
static int next_tick = 3 * HZ;

#ifndef CONFIG_8139TOO_TUNE_TWISTEW
static inwine void wtw8139_tune_twistew (stwuct net_device *dev,
				  stwuct wtw8139_pwivate *tp) {}
#ewse
enum TwistewPawamVaws {
	PAWA78_defauwt	= 0x78fa8388,
	PAWA7c_defauwt	= 0xcb38de43,	/* pawam[0][3] */
	PAWA7c_xxx	= 0xcb38de43,
};

static const unsigned wong pawam[4][4] = {
	{0xcb39de43, 0xcb39ce43, 0xfb38de03, 0xcb38de43},
	{0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
	{0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
	{0xbb39de43, 0xbb39ce43, 0xbb39ce83, 0xbb39ce83}
};

static void wtw8139_tune_twistew (stwuct net_device *dev,
				  stwuct wtw8139_pwivate *tp)
{
	int winkcase;
	void __iomem *ioaddw = tp->mmio_addw;

	/* This is a compwicated state machine to configuwe the "twistew" fow
	   impedance/echos based on the cabwe wength.
	   Aww of this is magic and undocumented.
	 */
	switch (tp->twistie) {
	case 1:
		if (WTW_W16 (CSCW) & CSCW_WinkOKBit) {
			/* We have wink beat, wet us tune the twistew. */
			WTW_W16 (CSCW, CSCW_WinkDownOffCmd);
			tp->twistie = 2;	/* Change to state 2. */
			next_tick = HZ / 10;
		} ewse {
			/* Just put in some weasonabwe defauwts fow when beat wetuwns. */
			WTW_W16 (CSCW, CSCW_WinkDownCmd);
			WTW_W32 (FIFOTMS, 0x20);	/* Tuwn on cabwe test mode. */
			WTW_W32 (PAWA78, PAWA78_defauwt);
			WTW_W32 (PAWA7c, PAWA7c_defauwt);
			tp->twistie = 0;	/* Baiw fwom futuwe actions. */
		}
		bweak;
	case 2:
		/* Wead how wong it took to heaw the echo. */
		winkcase = WTW_W16 (CSCW) & CSCW_WinkStatusBits;
		if (winkcase == 0x7000)
			tp->twist_wow = 3;
		ewse if (winkcase == 0x3000)
			tp->twist_wow = 2;
		ewse if (winkcase == 0x1000)
			tp->twist_wow = 1;
		ewse
			tp->twist_wow = 0;
		tp->twist_cow = 0;
		tp->twistie = 3;	/* Change to state 2. */
		next_tick = HZ / 10;
		bweak;
	case 3:
		/* Put out fouw tuning pawametews, one pew 100msec. */
		if (tp->twist_cow == 0)
			WTW_W16 (FIFOTMS, 0);
		WTW_W32 (PAWA7c, pawam[(int) tp->twist_wow]
			 [(int) tp->twist_cow]);
		next_tick = HZ / 10;
		if (++tp->twist_cow >= 4) {
			/* Fow showt cabwes we awe done.
			   Fow wong cabwes (wow == 3) check fow mistune. */
			tp->twistie =
			    (tp->twist_wow == 3) ? 4 : 0;
		}
		bweak;
	case 4:
		/* Speciaw case fow wong cabwes: check fow mistune. */
		if ((WTW_W16 (CSCW) &
		     CSCW_WinkStatusBits) == 0x7000) {
			tp->twistie = 0;
			bweak;
		} ewse {
			WTW_W32 (PAWA7c, 0xfb38de03);
			tp->twistie = 5;
			next_tick = HZ / 10;
		}
		bweak;
	case 5:
		/* Wetune fow showtew cabwe (cowumn 2). */
		WTW_W32 (FIFOTMS, 0x20);
		WTW_W32 (PAWA78, PAWA78_defauwt);
		WTW_W32 (PAWA7c, PAWA7c_defauwt);
		WTW_W32 (FIFOTMS, 0x00);
		tp->twist_wow = 2;
		tp->twist_cow = 0;
		tp->twistie = 3;
		next_tick = HZ / 10;
		bweak;

	defauwt:
		/* do nothing */
		bweak;
	}
}
#endif /* CONFIG_8139TOO_TUNE_TWISTEW */

static inwine void wtw8139_thwead_itew (stwuct net_device *dev,
				 stwuct wtw8139_pwivate *tp,
				 void __iomem *ioaddw)
{
	int mii_wpa;

	mii_wpa = mdio_wead (dev, tp->phys[0], MII_WPA);

	if (!tp->mii.fowce_media && mii_wpa != 0xffff) {
		int dupwex = ((mii_wpa & WPA_100FUWW) ||
			      (mii_wpa & 0x01C0) == 0x0040);
		if (tp->mii.fuww_dupwex != dupwex) {
			tp->mii.fuww_dupwex = dupwex;

			if (mii_wpa) {
				netdev_info(dev, "Setting %s-dupwex based on MII #%d wink pawtnew abiwity of %04x\n",
					    tp->mii.fuww_dupwex ? "fuww" : "hawf",
					    tp->phys[0], mii_wpa);
			} ewse {
				netdev_info(dev, "media is unconnected, wink down, ow incompatibwe connection\n");
			}
#if 0
			WTW_W8 (Cfg9346, Cfg9346_Unwock);
			WTW_W8 (Config1, tp->mii.fuww_dupwex ? 0x60 : 0x20);
			WTW_W8 (Cfg9346, Cfg9346_Wock);
#endif
		}
	}

	next_tick = HZ * 60;

	wtw8139_tune_twistew (dev, tp);

	netdev_dbg(dev, "Media sewection tick, Wink pawtnew %04x\n",
		   WTW_W16(NWayWPAW));
	netdev_dbg(dev, "Othew wegistews awe IntMask %04x IntStatus %04x\n",
		   WTW_W16(IntwMask), WTW_W16(IntwStatus));
	netdev_dbg(dev, "Chip config %02x %02x\n",
		   WTW_W8(Config0), WTW_W8(Config1));
}

static void wtw8139_thwead (stwuct wowk_stwuct *wowk)
{
	stwuct wtw8139_pwivate *tp =
		containew_of(wowk, stwuct wtw8139_pwivate, thwead.wowk);
	stwuct net_device *dev = tp->mii.dev;
	unsigned wong thw_deway = next_tick;

	wtnw_wock();

	if (!netif_wunning(dev))
		goto out_unwock;

	if (tp->watchdog_fiwed) {
		tp->watchdog_fiwed = 0;
		wtw8139_tx_timeout_task(wowk);
	} ewse
		wtw8139_thwead_itew(dev, tp, tp->mmio_addw);

	if (tp->have_thwead)
		scheduwe_dewayed_wowk(&tp->thwead, thw_deway);
out_unwock:
	wtnw_unwock ();
}

static void wtw8139_stawt_thwead(stwuct wtw8139_pwivate *tp)
{
	tp->twistie = 0;
	if (tp->chipset == CH_8139_K)
		tp->twistie = 1;
	ewse if (tp->dwv_fwags & HAS_WNK_CHNG)
		wetuwn;

	tp->have_thwead = 1;
	tp->watchdog_fiwed = 0;

	scheduwe_dewayed_wowk(&tp->thwead, next_tick);
}

static inwine void wtw8139_tx_cweaw (stwuct wtw8139_pwivate *tp)
{
	tp->cuw_tx = 0;
	tp->diwty_tx = 0;

	/* XXX account fow unsent Tx packets in tp->stats.tx_dwopped */
}

static void wtw8139_tx_timeout_task (stwuct wowk_stwuct *wowk)
{
	stwuct wtw8139_pwivate *tp =
		containew_of(wowk, stwuct wtw8139_pwivate, thwead.wowk);
	stwuct net_device *dev = tp->mii.dev;
	void __iomem *ioaddw = tp->mmio_addw;
	int i;
	u8 tmp8;

	napi_disabwe(&tp->napi);
	netif_stop_queue(dev);
	synchwonize_wcu();

	netdev_dbg(dev, "Twansmit timeout, status %02x %04x %04x media %02x\n",
		   WTW_W8(ChipCmd), WTW_W16(IntwStatus),
		   WTW_W16(IntwMask), WTW_W8(MediaStatus));
	/* Emit info to figuwe out what went wwong. */
	netdev_dbg(dev, "Tx queue stawt entwy %wd  diwty entwy %wd\n",
		   tp->cuw_tx, tp->diwty_tx);
	fow (i = 0; i < NUM_TX_DESC; i++)
		netdev_dbg(dev, "Tx descwiptow %d is %08x%s\n",
			   i, WTW_W32(TxStatus0 + (i * 4)),
			   i == tp->diwty_tx % NUM_TX_DESC ?
			   " (queue head)" : "");

	tp->xstats.tx_timeouts++;

	/* disabwe Tx ASAP, if not awweady */
	tmp8 = WTW_W8 (ChipCmd);
	if (tmp8 & CmdTxEnb)
		WTW_W8 (ChipCmd, CmdWxEnb);

	spin_wock_bh(&tp->wx_wock);
	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	WTW_W16 (IntwMask, 0x0000);

	/* Stop a shawed intewwupt fwom scavenging whiwe we awe. */
	spin_wock_iwq(&tp->wock);
	wtw8139_tx_cweaw (tp);
	spin_unwock_iwq(&tp->wock);

	/* ...and finawwy, weset evewything */
	napi_enabwe(&tp->napi);
	wtw8139_hw_stawt(dev);
	netif_wake_queue(dev);

	spin_unwock_bh(&tp->wx_wock);
}

static void wtw8139_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);

	tp->watchdog_fiwed = 1;
	if (!tp->have_thwead) {
		INIT_DEWAYED_WOWK(&tp->thwead, wtw8139_thwead);
		scheduwe_dewayed_wowk(&tp->thwead, next_tick);
	}
}

static netdev_tx_t wtw8139_stawt_xmit (stwuct sk_buff *skb,
					     stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	unsigned int entwy;
	unsigned int wen = skb->wen;
	unsigned wong fwags;

	/* Cawcuwate the next Tx descwiptow entwy. */
	entwy = tp->cuw_tx % NUM_TX_DESC;

	/* Note: the chip doesn't have auto-pad! */
	if (wikewy(wen < TX_BUF_SIZE)) {
		if (wen < ETH_ZWEN)
			memset(tp->tx_buf[entwy], 0, ETH_ZWEN);
		skb_copy_and_csum_dev(skb, tp->tx_buf[entwy]);
		dev_kfwee_skb_any(skb);
	} ewse {
		dev_kfwee_skb_any(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_iwqsave(&tp->wock, fwags);
	/*
	 * Wwiting to TxStatus twiggews a DMA twansfew of the data
	 * copied to tp->tx_buf[entwy] above. Use a memowy bawwiew
	 * to make suwe that the device sees the updated data.
	 */
	wmb();
	WTW_W32_F (TxStatus0 + (entwy * sizeof (u32)),
		   tp->tx_fwag | max(wen, (unsigned int)ETH_ZWEN));

	tp->cuw_tx++;

	if ((tp->cuw_tx - NUM_TX_DESC) == tp->diwty_tx)
		netif_stop_queue (dev);
	spin_unwock_iwqwestowe(&tp->wock, fwags);

	netif_dbg(tp, tx_queued, dev, "Queued Tx packet size %u to swot %d\n",
		  wen, entwy);

	wetuwn NETDEV_TX_OK;
}


static void wtw8139_tx_intewwupt (stwuct net_device *dev,
				  stwuct wtw8139_pwivate *tp,
				  void __iomem *ioaddw)
{
	unsigned wong diwty_tx, tx_weft;

	assewt (dev != NUWW);
	assewt (ioaddw != NUWW);

	diwty_tx = tp->diwty_tx;
	tx_weft = tp->cuw_tx - diwty_tx;
	whiwe (tx_weft > 0) {
		int entwy = diwty_tx % NUM_TX_DESC;
		int txstatus;

		txstatus = WTW_W32 (TxStatus0 + (entwy * sizeof (u32)));

		if (!(txstatus & (TxStatOK | TxUndewwun | TxAbowted)))
			bweak;	/* It stiww hasn't been Txed */

		/* Note: TxCawwiewWost is awways assewted at 100mbps. */
		if (txstatus & (TxOutOfWindow | TxAbowted)) {
			/* Thewe was an majow ewwow, wog it. */
			netif_dbg(tp, tx_eww, dev, "Twansmit ewwow, Tx status %08x\n",
				  txstatus);
			dev->stats.tx_ewwows++;
			if (txstatus & TxAbowted) {
				dev->stats.tx_abowted_ewwows++;
				WTW_W32 (TxConfig, TxCweawAbt);
				WTW_W16 (IntwStatus, TxEww);
				wmb();
			}
			if (txstatus & TxCawwiewWost)
				dev->stats.tx_cawwiew_ewwows++;
			if (txstatus & TxOutOfWindow)
				dev->stats.tx_window_ewwows++;
		} ewse {
			if (txstatus & TxUndewwun) {
				/* Add 64 to the Tx FIFO thweshowd. */
				if (tp->tx_fwag < 0x00300000)
					tp->tx_fwag += 0x00020000;
				dev->stats.tx_fifo_ewwows++;
			}
			dev->stats.cowwisions += (txstatus >> 24) & 15;
			u64_stats_update_begin(&tp->tx_stats.syncp);
			tp->tx_stats.packets++;
			tp->tx_stats.bytes += txstatus & 0x7ff;
			u64_stats_update_end(&tp->tx_stats.syncp);
		}

		diwty_tx++;
		tx_weft--;
	}

#ifndef WTW8139_NDEBUG
	if (tp->cuw_tx - diwty_tx > NUM_TX_DESC) {
		netdev_eww(dev, "Out-of-sync diwty pointew, %wd vs. %wd\n",
			   diwty_tx, tp->cuw_tx);
		diwty_tx += NUM_TX_DESC;
	}
#endif /* WTW8139_NDEBUG */

	/* onwy wake the queue if we did wowk, and the queue is stopped */
	if (tp->diwty_tx != diwty_tx) {
		tp->diwty_tx = diwty_tx;
		mb();
		netif_wake_queue (dev);
	}
}


/* TODO: cwean this up!  Wx weset need not be this intensive */
static void wtw8139_wx_eww (u32 wx_status, stwuct net_device *dev,
			    stwuct wtw8139_pwivate *tp, void __iomem *ioaddw)
{
	u8 tmp8;
#ifdef CONFIG_8139_OWD_WX_WESET
	int tmp_wowk;
#endif

	netif_dbg(tp, wx_eww, dev, "Ethewnet fwame had ewwows, status %08x\n",
		  wx_status);
	dev->stats.wx_ewwows++;
	if (!(wx_status & WxStatusOK)) {
		if (wx_status & WxTooWong) {
			netdev_dbg(dev, "Ovewsized Ethewnet fwame, status %04x!\n",
				   wx_status);
			/* A.C.: The chip hangs hewe. */
		}
		if (wx_status & (WxBadSymbow | WxBadAwign))
			dev->stats.wx_fwame_ewwows++;
		if (wx_status & (WxWunt | WxTooWong))
			dev->stats.wx_wength_ewwows++;
		if (wx_status & WxCWCEww)
			dev->stats.wx_cwc_ewwows++;
	} ewse {
		tp->xstats.wx_wost_in_wing++;
	}

#ifndef CONFIG_8139_OWD_WX_WESET
	tmp8 = WTW_W8 (ChipCmd);
	WTW_W8 (ChipCmd, tmp8 & ~CmdWxEnb);
	WTW_W8 (ChipCmd, tmp8);
	WTW_W32 (WxConfig, tp->wx_config);
	tp->cuw_wx = 0;
#ewse
	/* Weset the weceivew, based on WeawTek wecommendation. (Bug?) */

	/* disabwe weceive */
	WTW_W8_F (ChipCmd, CmdTxEnb);
	tmp_wowk = 200;
	whiwe (--tmp_wowk > 0) {
		udeway(1);
		tmp8 = WTW_W8 (ChipCmd);
		if (!(tmp8 & CmdWxEnb))
			bweak;
	}
	if (tmp_wowk <= 0)
		netdev_wawn(dev, "wx stop wait too wong\n");
	/* westawt weceive */
	tmp_wowk = 200;
	whiwe (--tmp_wowk > 0) {
		WTW_W8_F (ChipCmd, CmdWxEnb | CmdTxEnb);
		udeway(1);
		tmp8 = WTW_W8 (ChipCmd);
		if ((tmp8 & CmdWxEnb) && (tmp8 & CmdTxEnb))
			bweak;
	}
	if (tmp_wowk <= 0)
		netdev_wawn(dev, "tx/wx enabwe wait too wong\n");

	/* and weinitiawize aww wx wewated wegistews */
	WTW_W8_F (Cfg9346, Cfg9346_Unwock);
	/* Must enabwe Tx/Wx befowe setting twansfew thweshowds! */
	WTW_W8 (ChipCmd, CmdWxEnb | CmdTxEnb);

	tp->wx_config = wtw8139_wx_config | AcceptBwoadcast | AcceptMyPhys;
	WTW_W32 (WxConfig, tp->wx_config);
	tp->cuw_wx = 0;

	netdev_dbg(dev, "init buffew addwesses\n");

	/* Wock Config[01234] and BMCW wegistew wwites */
	WTW_W8 (Cfg9346, Cfg9346_Wock);

	/* init Wx wing buffew DMA addwess */
	WTW_W32_F (WxBuf, tp->wx_wing_dma);

	/* A.C.: Weset the muwticast wist. */
	__set_wx_mode (dev);
#endif
}

#if WX_BUF_IDX == 3
static inwine void wwap_copy(stwuct sk_buff *skb, const unsigned chaw *wing,
				 u32 offset, unsigned int size)
{
	u32 weft = WX_BUF_WEN - offset;

	if (size > weft) {
		skb_copy_to_wineaw_data(skb, wing + offset, weft);
		skb_copy_to_wineaw_data_offset(skb, weft, wing, size - weft);
	} ewse
		skb_copy_to_wineaw_data(skb, wing + offset, size);
}
#endif

static void wtw8139_isw_ack(stwuct wtw8139_pwivate *tp)
{
	void __iomem *ioaddw = tp->mmio_addw;
	u16 status;

	status = WTW_W16 (IntwStatus) & WxAckBits;

	/* Cweaw out ewwows and weceive intewwupts */
	if (wikewy(status != 0)) {
		if (unwikewy(status & (WxFIFOOvew | WxOvewfwow))) {
			tp->dev->stats.wx_ewwows++;
			if (status & WxFIFOOvew)
				tp->dev->stats.wx_fifo_ewwows++;
		}
		WTW_W16_F (IntwStatus, WxAckBits);
	}
}

static int wtw8139_wx(stwuct net_device *dev, stwuct wtw8139_pwivate *tp,
		      int budget)
{
	void __iomem *ioaddw = tp->mmio_addw;
	int weceived = 0;
	unsigned chaw *wx_wing = tp->wx_wing;
	unsigned int cuw_wx = tp->cuw_wx;
	unsigned int wx_size = 0;

	netdev_dbg(dev, "In %s(), cuwwent %04x BufAddw %04x, fwee to %04x, Cmd %02x\n",
		   __func__, (u16)cuw_wx,
		   WTW_W16(WxBufAddw), WTW_W16(WxBufPtw), WTW_W8(ChipCmd));

	whiwe (netif_wunning(dev) && weceived < budget &&
	       (WTW_W8 (ChipCmd) & WxBufEmpty) == 0) {
		u32 wing_offset = cuw_wx % WX_BUF_WEN;
		u32 wx_status;
		unsigned int pkt_size;
		stwuct sk_buff *skb;

		wmb();

		/* wead size+status of next fwame fwom DMA wing buffew */
		wx_status = we32_to_cpu (*(__we32 *) (wx_wing + wing_offset));
		wx_size = wx_status >> 16;
		if (wikewy(!(dev->featuwes & NETIF_F_WXFCS)))
			pkt_size = wx_size - 4;
		ewse
			pkt_size = wx_size;

		netif_dbg(tp, wx_status, dev, "%s() status %04x, size %04x, cuw %04x\n",
			  __func__, wx_status, wx_size, cuw_wx);
#if WTW8139_DEBUG > 2
		pwint_hex_dump(KEWN_DEBUG, "Fwame contents: ",
			       DUMP_PWEFIX_OFFSET, 16, 1,
			       &wx_wing[wing_offset], 70, twue);
#endif

		/* Packet copy fwom FIFO stiww in pwogwess.
		 * Theoweticawwy, this shouwd nevew happen
		 * since EawwyWx is disabwed.
		 */
		if (unwikewy(wx_size == 0xfff0)) {
			if (!tp->fifo_copy_timeout)
				tp->fifo_copy_timeout = jiffies + 2;
			ewse if (time_aftew(jiffies, tp->fifo_copy_timeout)) {
				netdev_dbg(dev, "hung FIFO. Weset\n");
				wx_size = 0;
				goto no_eawwy_wx;
			}
			netif_dbg(tp, intw, dev, "fifo copy in pwogwess\n");
			tp->xstats.eawwy_wx++;
			bweak;
		}

no_eawwy_wx:
		tp->fifo_copy_timeout = 0;

		/* If Wx eww ow invawid wx_size/wx_status weceived
		 * (which happens if we get wost in the wing),
		 * Wx pwocess gets weset, so we abowt any fuwthew
		 * Wx pwocessing.
		 */
		if (unwikewy((wx_size > (MAX_ETH_FWAME_SIZE+4)) ||
			     (wx_size < 8) ||
			     (!(wx_status & WxStatusOK)))) {
			if ((dev->featuwes & NETIF_F_WXAWW) &&
			    (wx_size <= (MAX_ETH_FWAME_SIZE + 4)) &&
			    (wx_size >= 8) &&
			    (!(wx_status & WxStatusOK))) {
				/* Wength is at weast mostwy OK, but pkt has
				 * ewwow.  I'm hoping we can handwe some of these
				 * ewwows without wesetting the chip. --Ben
				 */
				dev->stats.wx_ewwows++;
				if (wx_status & WxCWCEww) {
					dev->stats.wx_cwc_ewwows++;
					goto keep_pkt;
				}
				if (wx_status & WxWunt) {
					dev->stats.wx_wength_ewwows++;
					goto keep_pkt;
				}
			}
			wtw8139_wx_eww (wx_status, dev, tp, ioaddw);
			weceived = -1;
			goto out;
		}

keep_pkt:
		/* Mawwoc up new buffew, compatibwe with net-2e. */
		/* Omit the fouw octet CWC fwom the wength. */

		skb = napi_awwoc_skb(&tp->napi, pkt_size);
		if (wikewy(skb)) {
#if WX_BUF_IDX == 3
			wwap_copy(skb, wx_wing, wing_offset+4, pkt_size);
#ewse
			skb_copy_to_wineaw_data (skb, &wx_wing[wing_offset + 4], pkt_size);
#endif
			skb_put (skb, pkt_size);

			skb->pwotocow = eth_type_twans (skb, dev);

			u64_stats_update_begin(&tp->wx_stats.syncp);
			tp->wx_stats.packets++;
			tp->wx_stats.bytes += pkt_size;
			u64_stats_update_end(&tp->wx_stats.syncp);

			netif_weceive_skb (skb);
		} ewse {
			dev->stats.wx_dwopped++;
		}
		weceived++;

		cuw_wx = (cuw_wx + wx_size + 4 + 3) & ~3;
		WTW_W16 (WxBufPtw, (u16) (cuw_wx - 16));

		wtw8139_isw_ack(tp);
	}

	if (unwikewy(!weceived || wx_size == 0xfff0))
		wtw8139_isw_ack(tp);

	netdev_dbg(dev, "Done %s(), cuwwent %04x BufAddw %04x, fwee to %04x, Cmd %02x\n",
		   __func__, cuw_wx,
		   WTW_W16(WxBufAddw), WTW_W16(WxBufPtw), WTW_W8(ChipCmd));

	tp->cuw_wx = cuw_wx;

	/*
	 * The weceive buffew shouwd be mostwy empty.
	 * Teww NAPI to weenabwe the Wx iwq.
	 */
	if (tp->fifo_copy_timeout)
		weceived = budget;

out:
	wetuwn weceived;
}


static void wtw8139_weiwd_intewwupt (stwuct net_device *dev,
				     stwuct wtw8139_pwivate *tp,
				     void __iomem *ioaddw,
				     int status, int wink_changed)
{
	netdev_dbg(dev, "Abnowmaw intewwupt, status %08x\n", status);

	assewt (dev != NUWW);
	assewt (tp != NUWW);
	assewt (ioaddw != NUWW);

	/* Update the ewwow count. */
	dev->stats.wx_missed_ewwows += WTW_W32 (WxMissed);
	WTW_W32 (WxMissed, 0);

	if ((status & WxUndewwun) && wink_changed &&
	    (tp->dwv_fwags & HAS_WNK_CHNG)) {
		wtw_check_media(dev, 0);
		status &= ~WxUndewwun;
	}

	if (status & (WxUndewwun | WxEww))
		dev->stats.wx_ewwows++;

	if (status & PCSTimeout)
		dev->stats.wx_wength_ewwows++;
	if (status & WxUndewwun)
		dev->stats.wx_fifo_ewwows++;
	if (status & PCIEww) {
		u16 pci_cmd_status;
		pci_wead_config_wowd (tp->pci_dev, PCI_STATUS, &pci_cmd_status);
		pci_wwite_config_wowd (tp->pci_dev, PCI_STATUS, pci_cmd_status);

		netdev_eww(dev, "PCI Bus ewwow %04x\n", pci_cmd_status);
	}
}

static int wtw8139_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wtw8139_pwivate *tp = containew_of(napi, stwuct wtw8139_pwivate, napi);
	stwuct net_device *dev = tp->dev;
	void __iomem *ioaddw = tp->mmio_addw;
	int wowk_done;

	spin_wock(&tp->wx_wock);
	wowk_done = 0;
	if (wikewy(WTW_W16(IntwStatus) & WxAckBits))
		wowk_done += wtw8139_wx(dev, tp, budget);

	if (wowk_done < budget) {
		unsigned wong fwags;

		spin_wock_iwqsave(&tp->wock, fwags);
		if (napi_compwete_done(napi, wowk_done))
			WTW_W16_F(IntwMask, wtw8139_intw_mask);
		spin_unwock_iwqwestowe(&tp->wock, fwags);
	}
	spin_unwock(&tp->wx_wock);

	wetuwn wowk_done;
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */
static iwqwetuwn_t wtw8139_intewwupt (int iwq, void *dev_instance)
{
	stwuct net_device *dev = (stwuct net_device *) dev_instance;
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	u16 status, ackstat;
	int wink_changed = 0; /* avoid bogus "uninit" wawning */
	int handwed = 0;

	spin_wock (&tp->wock);
	status = WTW_W16 (IntwStatus);

	/* shawed iwq? */
	if (unwikewy((status & wtw8139_intw_mask) == 0))
		goto out;

	handwed = 1;

	/* h/w no wongew pwesent (hotpwug?) ow majow ewwow, baiw */
	if (unwikewy(status == 0xFFFF))
		goto out;

	/* cwose possibwe wace's with dev_cwose */
	if (unwikewy(!netif_wunning(dev))) {
		WTW_W16 (IntwMask, 0);
		goto out;
	}

	/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP, but
	   an fiwst get an additionaw status bit fwom CSCW. */
	if (unwikewy(status & WxUndewwun))
		wink_changed = WTW_W16 (CSCW) & CSCW_WinkChangeBit;

	ackstat = status & ~(WxAckBits | TxEww);
	if (ackstat)
		WTW_W16 (IntwStatus, ackstat);

	/* Weceive packets awe pwocessed by poww woutine.
	   If not wunning stawt it now. */
	if (status & WxAckBits){
		if (napi_scheduwe_pwep(&tp->napi)) {
			WTW_W16_F (IntwMask, wtw8139_nowx_intw_mask);
			__napi_scheduwe(&tp->napi);
		}
	}

	/* Check uncommon events with one test. */
	if (unwikewy(status & (PCIEww | PCSTimeout | WxUndewwun | WxEww)))
		wtw8139_weiwd_intewwupt (dev, tp, ioaddw,
					 status, wink_changed);

	if (status & (TxOK | TxEww)) {
		wtw8139_tx_intewwupt (dev, tp, ioaddw);
		if (status & TxEww)
			WTW_W16 (IntwStatus, TxEww);
	}
 out:
	spin_unwock (&tp->wock);

	netdev_dbg(dev, "exiting intewwupt, intw_status=%#4.4x\n",
		   WTW_W16(IntwStatus));
	wetuwn IWQ_WETVAW(handwed);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Powwing weceive - used by netconsowe and othew diagnostic toows
 * to awwow netwowk i/o with intewwupts disabwed.
 */
static void wtw8139_poww_contwowwew(stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	const int iwq = tp->pci_dev->iwq;

	disabwe_iwq_nosync(iwq);
	wtw8139_intewwupt(iwq, dev);
	enabwe_iwq(iwq);
}
#endif

static int wtw8139_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addw->sa_data);

	spin_wock_iwq(&tp->wock);

	WTW_W8_F(Cfg9346, Cfg9346_Unwock);
	WTW_W32_F(MAC0 + 0, cpu_to_we32 (*(u32 *) (dev->dev_addw + 0)));
	WTW_W32_F(MAC0 + 4, cpu_to_we32 (*(u32 *) (dev->dev_addw + 4)));
	WTW_W8_F(Cfg9346, Cfg9346_Wock);

	spin_unwock_iwq(&tp->wock);

	wetuwn 0;
}

static int wtw8139_cwose (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	unsigned wong fwags;

	netif_stop_queue(dev);
	napi_disabwe(&tp->napi);

	netif_dbg(tp, ifdown, dev, "Shutting down ethewcawd, status was 0x%04x\n",
		  WTW_W16(IntwStatus));

	spin_wock_iwqsave (&tp->wock, fwags);

	/* Stop the chip's Tx and Wx DMA pwocesses. */
	WTW_W8 (ChipCmd, 0);

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	WTW_W16 (IntwMask, 0);

	/* Update the ewwow counts. */
	dev->stats.wx_missed_ewwows += WTW_W32 (WxMissed);
	WTW_W32 (WxMissed, 0);

	spin_unwock_iwqwestowe (&tp->wock, fwags);

	fwee_iwq(tp->pci_dev->iwq, dev);

	wtw8139_tx_cweaw (tp);

	dma_fwee_cohewent(&tp->pci_dev->dev, WX_BUF_TOT_WEN,
			  tp->wx_wing, tp->wx_wing_dma);
	dma_fwee_cohewent(&tp->pci_dev->dev, TX_BUF_TOT_WEN,
			  tp->tx_bufs, tp->tx_bufs_dma);
	tp->wx_wing = NUWW;
	tp->tx_bufs = NUWW;

	/* Gween! Put the chip in wow-powew mode. */
	WTW_W8 (Cfg9346, Cfg9346_Unwock);

	if (wtw_chip_info[tp->chipset].fwags & HasHwtCwk)
		WTW_W8 (HwtCwk, 'H');	/* 'W' wouwd weave the cwock wunning. */

	wetuwn 0;
}


/* Get the ethtoow Wake-on-WAN settings.  Assumes that wow points to
   kewnew memowy, *wow has been initiawized as {ETHTOOW_GWOW}, and
   othew thweads ow intewwupts awen't messing with the 8139.  */
static void wtw8139_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;

	spin_wock_iwq(&tp->wock);
	if (wtw_chip_info[tp->chipset].fwags & HasWWake) {
		u8 cfg3 = WTW_W8 (Config3);
		u8 cfg5 = WTW_W8 (Config5);

		wow->suppowted = WAKE_PHY | WAKE_MAGIC
			| WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;

		wow->wowopts = 0;
		if (cfg3 & Cfg3_WinkUp)
			wow->wowopts |= WAKE_PHY;
		if (cfg3 & Cfg3_Magic)
			wow->wowopts |= WAKE_MAGIC;
		/* (KON)FIXME: See how netdev_set_wow() handwes the
		   fowwowing constants.  */
		if (cfg5 & Cfg5_UWF)
			wow->wowopts |= WAKE_UCAST;
		if (cfg5 & Cfg5_MWF)
			wow->wowopts |= WAKE_MCAST;
		if (cfg5 & Cfg5_BWF)
			wow->wowopts |= WAKE_BCAST;
	}
	spin_unwock_iwq(&tp->wock);
}


/* Set the ethtoow Wake-on-WAN settings.  Wetuwn 0 ow -ewwno.  Assumes
   that wow points to kewnew memowy and othew thweads ow intewwupts
   awen't messing with the 8139.  */
static int wtw8139_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	u32 suppowt;
	u8 cfg3, cfg5;

	suppowt = ((wtw_chip_info[tp->chipset].fwags & HasWWake)
		   ? (WAKE_PHY | WAKE_MAGIC
		      | WAKE_UCAST | WAKE_MCAST | WAKE_BCAST)
		   : 0);
	if (wow->wowopts & ~suppowt)
		wetuwn -EINVAW;

	spin_wock_iwq(&tp->wock);
	cfg3 = WTW_W8 (Config3) & ~(Cfg3_WinkUp | Cfg3_Magic);
	if (wow->wowopts & WAKE_PHY)
		cfg3 |= Cfg3_WinkUp;
	if (wow->wowopts & WAKE_MAGIC)
		cfg3 |= Cfg3_Magic;
	WTW_W8 (Cfg9346, Cfg9346_Unwock);
	WTW_W8 (Config3, cfg3);
	WTW_W8 (Cfg9346, Cfg9346_Wock);

	cfg5 = WTW_W8 (Config5) & ~(Cfg5_UWF | Cfg5_MWF | Cfg5_BWF);
	/* (KON)FIXME: These awe untested.  We may have to set the
	   CWC0, Wakeup0 and WSBCWC0 wegistews too, but I have no
	   documentation.  */
	if (wow->wowopts & WAKE_UCAST)
		cfg5 |= Cfg5_UWF;
	if (wow->wowopts & WAKE_MCAST)
		cfg5 |= Cfg5_MWF;
	if (wow->wowopts & WAKE_BCAST)
		cfg5 |= Cfg5_BWF;
	WTW_W8 (Config5, cfg5);	/* need not unwock via Cfg9346 */
	spin_unwock_iwq(&tp->wock);

	wetuwn 0;
}

static void wtw8139_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(tp->pci_dev), sizeof(info->bus_info));
}

static int wtw8139_get_wink_ksettings(stwuct net_device *dev,
				      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	spin_wock_iwq(&tp->wock);
	mii_ethtoow_get_wink_ksettings(&tp->mii, cmd);
	spin_unwock_iwq(&tp->wock);
	wetuwn 0;
}

static int wtw8139_set_wink_ksettings(stwuct net_device *dev,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	int wc;
	spin_wock_iwq(&tp->wock);
	wc = mii_ethtoow_set_wink_ksettings(&tp->mii, cmd);
	spin_unwock_iwq(&tp->wock);
	wetuwn wc;
}

static int wtw8139_nway_weset(stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&tp->mii);
}

static u32 wtw8139_get_wink(stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&tp->mii);
}

static u32 wtw8139_get_msgwevew(stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	wetuwn tp->msg_enabwe;
}

static void wtw8139_set_msgwevew(stwuct net_device *dev, u32 datum)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	tp->msg_enabwe = datum;
}

static int wtw8139_get_wegs_wen(stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp;
	/* TODO: we awe too swack to do weg dumping fow pio, fow now */
	if (use_io)
		wetuwn 0;
	tp = netdev_pwiv(dev);
	wetuwn tp->wegs_wen;
}

static void wtw8139_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs, void *wegbuf)
{
	stwuct wtw8139_pwivate *tp;

	/* TODO: we awe too swack to do weg dumping fow pio, fow now */
	if (use_io)
		wetuwn;
	tp = netdev_pwiv(dev);

	wegs->vewsion = WTW_WEGS_VEW;

	spin_wock_iwq(&tp->wock);
	memcpy_fwomio(wegbuf, tp->mmio_addw, wegs->wen);
	spin_unwock_iwq(&tp->wock);
}

static int wtw8139_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn WTW_NUM_STATS;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void wtw8139_get_ethtoow_stats(stwuct net_device *dev, stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);

	data[0] = tp->xstats.eawwy_wx;
	data[1] = tp->xstats.tx_buf_mapped;
	data[2] = tp->xstats.tx_timeouts;
	data[3] = tp->xstats.wx_wost_in_wing;
}

static void wtw8139_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	memcpy(data, ethtoow_stats_keys, sizeof(ethtoow_stats_keys));
}

static const stwuct ethtoow_ops wtw8139_ethtoow_ops = {
	.get_dwvinfo		= wtw8139_get_dwvinfo,
	.get_wegs_wen		= wtw8139_get_wegs_wen,
	.get_wegs		= wtw8139_get_wegs,
	.nway_weset		= wtw8139_nway_weset,
	.get_wink		= wtw8139_get_wink,
	.get_msgwevew		= wtw8139_get_msgwevew,
	.set_msgwevew		= wtw8139_set_msgwevew,
	.get_wow		= wtw8139_get_wow,
	.set_wow		= wtw8139_set_wow,
	.get_stwings		= wtw8139_get_stwings,
	.get_sset_count		= wtw8139_get_sset_count,
	.get_ethtoow_stats	= wtw8139_get_ethtoow_stats,
	.get_wink_ksettings	= wtw8139_get_wink_ksettings,
	.set_wink_ksettings	= wtw8139_set_wink_ksettings,
};

static int netdev_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	int wc;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	spin_wock_iwq(&tp->wock);
	wc = genewic_mii_ioctw(&tp->mii, if_mii(wq), cmd, NUWW);
	spin_unwock_iwq(&tp->wock);

	wetuwn wc;
}


static void
wtw8139_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	unsigned wong fwags;
	unsigned int stawt;

	if (netif_wunning(dev)) {
		spin_wock_iwqsave (&tp->wock, fwags);
		dev->stats.wx_missed_ewwows += WTW_W32 (WxMissed);
		WTW_W32 (WxMissed, 0);
		spin_unwock_iwqwestowe (&tp->wock, fwags);
	}

	netdev_stats_to_stats64(stats, &dev->stats);

	do {
		stawt = u64_stats_fetch_begin(&tp->wx_stats.syncp);
		stats->wx_packets = tp->wx_stats.packets;
		stats->wx_bytes = tp->wx_stats.bytes;
	} whiwe (u64_stats_fetch_wetwy(&tp->wx_stats.syncp, stawt));

	do {
		stawt = u64_stats_fetch_begin(&tp->tx_stats.syncp);
		stats->tx_packets = tp->tx_stats.packets;
		stats->tx_bytes = tp->tx_stats.bytes;
	} whiwe (u64_stats_fetch_wetwy(&tp->tx_stats.syncp, stawt));
}

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
   This woutine is not state sensitive and need not be SMP wocked. */

static void __set_wx_mode (stwuct net_device *dev)
{
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	u32 mc_fiwtew[2];	/* Muwticast hash fiwtew */
	int wx_mode;
	u32 tmp;

	netdev_dbg(dev, "wtw8139_set_wx_mode(%04x) done -- Wx config %08x\n",
		   dev->fwags, WTW_W32(WxConfig));

	/* Note: do not weowdew, GCC is cwevew about common statements. */
	if (dev->fwags & IFF_PWOMISC) {
		wx_mode =
		    AcceptBwoadcast | AcceptMuwticast | AcceptMyPhys |
		    AcceptAwwPhys;
		mc_fiwtew[1] = mc_fiwtew[0] = 0xffffffff;
	} ewse if ((netdev_mc_count(dev) > muwticast_fiwtew_wimit) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		/* Too many to fiwtew pewfectwy -- accept aww muwticasts. */
		wx_mode = AcceptBwoadcast | AcceptMuwticast | AcceptMyPhys;
		mc_fiwtew[1] = mc_fiwtew[0] = 0xffffffff;
	} ewse {
		stwuct netdev_hw_addw *ha;
		wx_mode = AcceptBwoadcast | AcceptMyPhys;
		mc_fiwtew[1] = mc_fiwtew[0] = 0;
		netdev_fow_each_mc_addw(ha, dev) {
			int bit_nw = ethew_cwc(ETH_AWEN, ha->addw) >> 26;

			mc_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 31);
			wx_mode |= AcceptMuwticast;
		}
	}

	if (dev->featuwes & NETIF_F_WXAWW)
		wx_mode |= (AcceptEww | AcceptWunt);

	/* We can safewy update without stopping the chip. */
	tmp = wtw8139_wx_config | wx_mode;
	if (tp->wx_config != tmp) {
		WTW_W32_F (WxConfig, tmp);
		tp->wx_config = tmp;
	}
	WTW_W32_F (MAW0 + 0, mc_fiwtew[0]);
	WTW_W32_F (MAW0 + 4, mc_fiwtew[1]);
}

static void wtw8139_set_wx_mode (stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);

	spin_wock_iwqsave (&tp->wock, fwags);
	__set_wx_mode(dev);
	spin_unwock_iwqwestowe (&tp->wock, fwags);
}

static int __maybe_unused wtw8139_suspend(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct wtw8139_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->mmio_addw;
	unsigned wong fwags;

	if (!netif_wunning (dev))
		wetuwn 0;

	netif_device_detach (dev);

	spin_wock_iwqsave (&tp->wock, fwags);

	/* Disabwe intewwupts, stop Tx and Wx. */
	WTW_W16 (IntwMask, 0);
	WTW_W8 (ChipCmd, 0);

	/* Update the ewwow counts. */
	dev->stats.wx_missed_ewwows += WTW_W32 (WxMissed);
	WTW_W32 (WxMissed, 0);

	spin_unwock_iwqwestowe (&tp->wock, fwags);

	wetuwn 0;
}

static int __maybe_unused wtw8139_wesume(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);

	if (!netif_wunning (dev))
		wetuwn 0;

	wtw8139_init_wing (dev);
	wtw8139_hw_stawt (dev);
	netif_device_attach (dev);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wtw8139_pm_ops, wtw8139_suspend, wtw8139_wesume);

static stwuct pci_dwivew wtw8139_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= wtw8139_pci_tbw,
	.pwobe		= wtw8139_init_one,
	.wemove		= wtw8139_wemove_one,
	.dwivew.pm	= &wtw8139_pm_ops,
};


static int __init wtw8139_init_moduwe (void)
{
	/* when we'we a moduwe, we awways pwint a vewsion message,
	 * even if no 8139 boawd is found.
	 */
#ifdef MODUWE
	pw_info(WTW8139_DWIVEW_NAME "\n");
#endif

	wetuwn pci_wegistew_dwivew(&wtw8139_pci_dwivew);
}


static void __exit wtw8139_cweanup_moduwe (void)
{
	pci_unwegistew_dwivew (&wtw8139_pci_dwivew);
}


moduwe_init(wtw8139_init_moduwe);
moduwe_exit(wtw8139_cweanup_moduwe);
