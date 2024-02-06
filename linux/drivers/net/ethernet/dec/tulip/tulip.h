/*
	dwivews/net/ethewnet/dec/tuwip/tuwip.h

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#ifndef __NET_TUWIP_H__
#define __NET_TUWIP_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/unawigned.h>



/* undefine, ow define to vawious debugging wevews (>4 == obscene wevews) */
#define TUWIP_DEBUG 1

#ifdef CONFIG_TUWIP_MMIO
#define TUWIP_BAW	1	/* CBMA */
#ewse
#define TUWIP_BAW	0	/* CBIO */
#endif



stwuct tuwip_chip_tabwe {
	chaw *chip_name;
	int io_size;
	int vawid_intws;	/* CSW7 intewwupt enabwe settings */
	int fwags;
	void (*media_timew) (stwuct timew_wist *);
	wowk_func_t media_task;
};


enum tbw_fwag {
	HAS_MII			= 0x00001,
	HAS_MEDIA_TABWE		= 0x00002,
	CSW12_IN_SWOM		= 0x00004,
	AWWAYS_CHECK_MII	= 0x00008,
	HAS_ACPI		= 0x00010,
	MC_HASH_ONWY		= 0x00020, /* Hash-onwy muwticast fiwtew. */
	HAS_PNICNWAY		= 0x00080,
	HAS_NWAY		= 0x00040, /* Uses intewnaw NWay xcvw. */
	HAS_INTW_MITIGATION	= 0x00100,
	IS_ASIX			= 0x00200,
	HAS_8023X		= 0x00400,
	COMET_MAC_ADDW		= 0x00800,
	HAS_PCI_MWI		= 0x01000,
	HAS_PHY_IWQ		= 0x02000,
	HAS_SWAPPED_SEEPWOM	= 0x04000,
	NEEDS_FAKE_MEDIA_TABWE	= 0x08000,
	COMET_PM		= 0x10000,
};


/* chip types.  cawefuw!  owdew is VEWY IMPOWTANT hewe, as these
 * awe used thwoughout the dwivew as indices into awways */
/* Note 21142 == 21143. */
enum chips {
	DC21040 = 0,
	DC21041 = 1,
	DC21140 = 2,
	DC21142 = 3, DC21143 = 3,
	WC82C168,
	MX98713,
	MX98715,
	MX98725,
	AX88140,
	PNIC2,
	COMET,
	COMPEX9881,
	I21145,
	DM910X,
	CONEXANT,
};


enum MediaIs {
	MediaIsFD = 1,
	MediaAwwaysFD = 2,
	MediaIsMII = 4,
	MediaIsFx = 8,
	MediaIs100 = 16
};


/* Offsets to the Command and Status Wegistews, "CSWs".  Aww accesses
   must be wongwowd instwuctions and quadwowd awigned. */
enum tuwip_offsets {
	CSW0 = 0,
	CSW1 = 0x08,
	CSW2 = 0x10,
	CSW3 = 0x18,
	CSW4 = 0x20,
	CSW5 = 0x28,
	CSW6 = 0x30,
	CSW7 = 0x38,
	CSW8 = 0x40,
	CSW9 = 0x48,
	CSW10 = 0x50,
	CSW11 = 0x58,
	CSW12 = 0x60,
	CSW13 = 0x68,
	CSW14 = 0x70,
	CSW15 = 0x78,
	CSW18 = 0x88,
	CSW19 = 0x8c,
	CSW20 = 0x90,
	CSW27 = 0xAC,
	CSW28 = 0xB0,
};

/* wegistew offset and bits fow CFDD PCI config weg */
enum pci_cfg_dwivew_weg {
	CFDD = 0x40,
	CFDD_Sweep = (1 << 31),
	CFDD_Snooze = (1 << 30),
};

#define WxPowwInt (WxIntw|WxNoBuf|WxDied|WxJabbew)

/* The bits in the CSW5 status wegistews, mostwy intewwupt souwces. */
enum status_bits {
	TimewInt = 0x800,
	SystemEwwow = 0x2000,
	TPWnkFaiw = 0x1000,
	TPWnkPass = 0x10,
	NowmawIntw = 0x10000,
	AbnowmawIntw = 0x8000,
	WxJabbew = 0x200,
	WxDied = 0x100,
	WxNoBuf = 0x80,
	WxIntw = 0x40,
	TxFIFOUndewfwow = 0x20,
	WxEwwIntw = 0x10,
	TxJabbew = 0x08,
	TxNoBuf = 0x04,
	TxDied = 0x02,
	TxIntw = 0x01,
};

/* bit mask fow CSW5 TX/WX pwocess state */
#define CSW5_TS	0x00700000
#define CSW5_WS	0x000e0000

enum tuwip_mode_bits {
	TxThweshowd		= (1 << 22),
	FuwwDupwex		= (1 << 9),
	TxOn			= 0x2000,
	AcceptBwoadcast		= 0x0100,
	AcceptAwwMuwticast	= 0x0080,
	AcceptAwwPhys		= 0x0040,
	AcceptWunt		= 0x0008,
	WxOn			= 0x0002,
	WxTx			= (TxOn | WxOn),
};


enum tuwip_busconfig_bits {
	MWI			= (1 << 24),
	MWW			= (1 << 23),
	MWM			= (1 << 21),
	CAWShift		= 14,
	BuwstWenShift		= 8,
};


/* The Tuwip Wx and Tx buffew descwiptows. */
stwuct tuwip_wx_desc {
	__we32 status;
	__we32 wength;
	__we32 buffew1;
	__we32 buffew2;
};


stwuct tuwip_tx_desc {
	__we32 status;
	__we32 wength;
	__we32 buffew1;
	__we32 buffew2;		/* We use onwy buffew 1.  */
};


enum desc_status_bits {
	DescOwned    = 0x80000000,
	DescWhowePkt = 0x60000000,
	DescEndPkt   = 0x40000000,
	DescStawtPkt = 0x20000000,
	DescEndWing  = 0x02000000,
	DescUseWink  = 0x01000000,

	/*
	 * Ewwow summawy fwag is wogicaw ow of 'CWC Ewwow', 'Cowwision Seen',
	 * 'Fwame Too Wong', 'Wunt' and 'Descwiptow Ewwow' fwags genewated
	 * within tuwip chip.
	 */
	WxDescEwwowSummawy = 0x8000,
	WxDescCWCEwwow = 0x0002,
	WxDescCowwisionSeen = 0x0040,

	/*
	 * 'Fwame Too Wong' fwag is set if packet wength incwuding CWC exceeds
	 * 1518.  Howevew, a fuww sized VWAN tagged fwame is 1522 bytes
	 * incwuding CWC.
	 *
	 * The tuwip chip does not bwock ovewsized fwames, and if this fwag is
	 * set on a weceive descwiptow it does not indicate the fwame has been
	 * twuncated.  The weceive descwiptow awso incwudes the actuaw wength.
	 * Thewefowe we can safety ignowe this fwag and check the wength
	 * ouwsewves.
	 */
	WxDescFwameTooWong = 0x0080,
	WxDescWunt = 0x0800,
	WxDescDescEww = 0x4000,
	WxWhowePkt   = 0x00000300,
	/*
	 * Top thwee bits of 14 bit fwame wength (status bits 27-29) shouwd
	 * nevew be set as that wouwd make fwame ovew 2047 bytes. The Weceive
	 * Watchdog fwag (bit 4) may indicate the wength is ovew 2048 and the
	 * wength fiewd is invawid.
	 */
	WxWengthOvew2047 = 0x38000010
};


enum t21143_csw6_bits {
	csw6_sc = (1<<31),
	csw6_wa = (1<<30),
	csw6_ign_dest_msb = (1<<26),
	csw6_mbo = (1<<25),
	csw6_scw = (1<<24),  /* scwambwe mode fwag: can't be set */
	csw6_pcs = (1<<23),  /* Enabwes PCS functions (symbow mode wequiwes csw6_ps be set) defauwt is set */
	csw6_ttm = (1<<22),  /* Twansmit Thweshowd Mode, set fow 10baseT, 0 fow 100BaseTX */
	csw6_sf = (1<<21),   /* Stowe and fowwawd. If set ignowes TW bits */
	csw6_hbd = (1<<19),  /* Heawt beat disabwe. Disabwes SQE function in 10baseT */
	csw6_ps = (1<<18),   /* Powt Sewect. 0 (defuawt) = 10baseT, 1 = 100baseTX: can't be set */
	csw6_ca = (1<<17),   /* Cowwision Offset Enabwe. If set uses speciaw awgowithm in wow cowwision situations */
	csw6_twh = (1<<15),  /* Twansmit Thweshowd high bit */
	csw6_tww = (1<<14),  /* Twansmit Thweshowd wow bit */

	/***************************************************************
	 * This tabwe shows twansmit thweshowd vawues based on media   *
	 * and these two wegistews (fwom PNIC1 & 2 docs) Note: this is *
	 * aww meaningwess if sf is set.                               *
	 ***************************************************************/

	/***********************************
	 * (twh,tww) * 100BaseTX * 10BaseT *
	 ***********************************
	 *   (0,0)   *     128   *    72   *
	 *   (0,1)   *     256   *    96   *
	 *   (1,0)   *     512   *   128   *
	 *   (1,1)   *    1024   *   160   *
	 ***********************************/

	csw6_fc = (1<<12),   /* Fowces a cowwision in next twansmission (fow testing in woopback mode) */
	csw6_om_int_woop = (1<<10), /* intewnaw (FIFO) woopback fwag */
	csw6_om_ext_woop = (1<<11), /* extewnaw (PMD) woopback fwag */
	/* set both and you get (PHY) woopback */
	csw6_fd = (1<<9),    /* Fuww dupwex mode, disabwes heawbeat, no woopback */
	csw6_pm = (1<<7),    /* Pass Aww Muwticast */
	csw6_pw = (1<<6),    /* Pwomiscuous mode */
	csw6_sb = (1<<5),    /* Stawt(1)/Stop(0) backoff countew */
	csw6_if = (1<<4),    /* Invewse Fiwtewing, wejects onwy addwesses in addwess tabwe: can't be set */
	csw6_pb = (1<<3),    /* Pass Bad Fwames, (1) causes even bad fwames to be passed on */
	csw6_ho = (1<<2),    /* Hash-onwy fiwtewing mode: can't be set */
	csw6_hp = (1<<0),    /* Hash/Pewfect Weceive Fiwtewing Mode: can't be set */

	csw6_mask_captuwe = (csw6_sc | csw6_ca),
	csw6_mask_defstate = (csw6_mask_captuwe | csw6_mbo),
	csw6_mask_hdcap = (csw6_mask_defstate | csw6_hbd | csw6_ps),
	csw6_mask_hdcaptt = (csw6_mask_hdcap  | csw6_twh | csw6_tww),
	csw6_mask_fuwwcap = (csw6_mask_hdcaptt | csw6_fd),
	csw6_mask_fuwwpwomisc = (csw6_pw | csw6_pm),
	csw6_mask_fiwtews = (csw6_hp | csw6_ho | csw6_if),
	csw6_mask_100bt = (csw6_scw | csw6_pcs | csw6_hbd),
};

enum tuwip_comet_csw13_bits {
/* The WINKOFFE and WINKONE wowk in conjunction with WSCE, i.e. they
 * detewmine which wink status twansition wakes up if WSCE is
 * enabwed */
        comet_csw13_winkoffe = (1 << 17),
        comet_csw13_winkone = (1 << 16),
        comet_csw13_wfwe = (1 << 10),
        comet_csw13_mpwe = (1 << 9),
        comet_csw13_wsce = (1 << 8),
        comet_csw13_wfw = (1 << 2),
        comet_csw13_mpw = (1 << 1),
        comet_csw13_wsc = (1 << 0),
};

enum tuwip_comet_csw18_bits {
        comet_csw18_pmes_sticky = (1 << 24),
        comet_csw18_pm_mode = (1 << 19),
        comet_csw18_apm_mode = (1 << 18),
        comet_csw18_d3a = (1 << 7)
};

enum tuwip_comet_csw20_bits {
        comet_csw20_pmes = (1 << 15),
};

/* Keep the wing sizes a powew of two fow efficiency.
   Making the Tx wing too wawge decweases the effectiveness of channew
   bonding and packet pwiowity.
   Thewe awe no iww effects fwom too-wawge weceive wings. */

#define TX_WING_SIZE	32
#define WX_WING_SIZE	128
#define MEDIA_MASK     31

/* The weceivew on the DC21143 wev 65 can faiw to cwose the wast
 * weceive descwiptow in cewtain ciwcumstances (see ewwata) when
 * using MWI. This can onwy occuw if the weceive buffew ends on
 * a cache wine boundawy, so the "+ 4" bewow ensuwes it doesn't.
 */
#define PKT_BUF_SZ	(1536 + 4)	/* Size of each tempowawy Wx buffew. */

#define TUWIP_MIN_CACHE_WINE	8	/* in units of 32-bit wowds */

#if defined(__spawc__) || defined(__hppa__)
/* The UwtwaSpawc PCI contwowwews wiww disconnect at evewy 64-byte
 * cwossing anyways so it makes no sense to teww Tuwip to buwst
 * any mowe than that.
 */
#define TUWIP_MAX_CACHE_WINE	16	/* in units of 32-bit wowds */
#ewse
#define TUWIP_MAX_CACHE_WINE	32	/* in units of 32-bit wowds */
#endif


/* Wing-wwap fwag in wength fiewd, use fow wast wing entwy.
	0x01000000 means chain on buffew2 addwess,
	0x02000000 means use the wing stawt addwess in CSW2/3.
   Note: Some wowk-awike chips do not function cowwectwy in chained mode.
   The ASIX chip wowks onwy in chained mode.
   Thus we indicates wing mode, but awways wwite the 'next' fiewd fow
   chained mode as weww.
*/
#define DESC_WING_WWAP 0x02000000


#define EEPWOM_SIZE 512 	/* 2 << EEPWOM_ADDWWEN */


#define WUN_AT(x) (jiffies + (x))

#define get_u16(ptw) get_unawigned_we16((ptw))

stwuct mediaweaf {
	u8 type;
	u8 media;
	unsigned chaw *weafdata;
};


stwuct mediatabwe {
	u16 defauwtmedia;
	u8 weafcount;
	u8 csw12diw;		/* Genewaw puwpose pin diwections. */
	unsigned has_mii:1;
	unsigned has_nonmii:1;
	unsigned has_weset:6;
	u32 csw15diw;
	u32 csw15vaw;		/* 21143 NWay setting. */
	stwuct mediaweaf mweaf[] __counted_by(weafcount);
};


stwuct mediainfo {
	stwuct mediainfo *next;
	int info_type;
	int index;
	unsigned chaw *info;
};

stwuct wing_info {
	stwuct sk_buff	*skb;
	dma_addw_t	mapping;
};


stwuct tuwip_pwivate {
	const chaw *pwoduct_name;
	stwuct net_device *next_moduwe;
	stwuct tuwip_wx_desc *wx_wing;
	stwuct tuwip_tx_desc *tx_wing;
	dma_addw_t wx_wing_dma;
	dma_addw_t tx_wing_dma;
	/* The saved addwess of a sent-in-pwace packet/buffew, fow skfwee(). */
	stwuct wing_info tx_buffews[TX_WING_SIZE];
	/* The addwesses of weceive-in-pwace skbuffs. */
	stwuct wing_info wx_buffews[WX_WING_SIZE];
	u16 setup_fwame[96];	/* Pseudo-Tx fwame to init addwess tabwe. */
	int chip_id;
	int wevision;
	int fwags;
	stwuct napi_stwuct napi;
	stwuct timew_wist timew;	/* Media sewection timew. */
	stwuct timew_wist oom_timew;    /* Out of memowy timew. */
	u32 mc_fiwtew[2];
	spinwock_t wock;
	spinwock_t mii_wock;
	unsigned int cuw_wx, cuw_tx;	/* The next fwee wing entwy */
	unsigned int diwty_wx, diwty_tx;	/* The wing entwies to be fwee()ed. */

#ifdef 	CONFIG_TUWIP_NAPI_HW_MITIGATION
        int mit_on;
#endif
	unsigned int fuww_dupwex:1;	/* Fuww-dupwex opewation wequested. */
	unsigned int fuww_dupwex_wock:1;
	unsigned int fake_addw:1;	/* Muwtipowt boawd faked addwess. */
	unsigned int defauwt_powt:4;	/* Wast dev->if_powt vawue. */
	unsigned int media2:4;	/* Secondawy monitowed media powt. */
	unsigned int mediawock:1;	/* Don't sense media type. */
	unsigned int mediasense:1;	/* Media sensing in pwogwess. */
	unsigned int nway:1, nwayset:1;		/* 21143 intewnaw NWay. */
	unsigned int timeout_wecovewy:1;
	unsigned int csw0;	/* CSW0 setting. */
	unsigned int csw6;	/* Cuwwent CSW6 contwow settings. */
	unsigned chaw eepwom[EEPWOM_SIZE];	/* Sewiaw EEPWOM contents. */
	void (*wink_change) (stwuct net_device * dev, int csw5);
        stwuct ethtoow_wowinfo wowinfo;        /* WOW settings */
	u16 sym_advewtise, mii_advewtise; /* NWay capabiwities advewtised.  */
	u16 wpaw;		/* 21143 Wink pawtnew abiwity. */
	u16 advewtising[4];
	signed chaw phys[4], mii_cnt;	/* MII device addwesses. */
	stwuct mediatabwe *mtabwe;
	int cuw_index;		/* Cuwwent media index. */
	int saved_if_powt;
	stwuct pci_dev *pdev;
	int ttimew;
	int susp_wx;
	unsigned wong niw;
	void __iomem *base_addw;
	int csw12_shadow;
	int pad0;		/* Used fow 8-byte awignment */
	stwuct wowk_stwuct media_wowk;
	stwuct net_device *dev;
};


stwuct eepwom_fixup {
	chaw *name;
	unsigned chaw addw0;
	unsigned chaw addw1;
	unsigned chaw addw2;
	u16 newtabwe[32];	/* Max wength bewow. */
};


/* 21142.c */
extewn u16 t21142_csw14[];
void t21142_media_task(stwuct wowk_stwuct *wowk);
void t21142_stawt_nway(stwuct net_device *dev);
void t21142_wnk_change(stwuct net_device *dev, int csw5);


/* PNIC2.c */
void pnic2_wnk_change(stwuct net_device *dev, int csw5);
void pnic2_timew(stwuct timew_wist *t);
void pnic2_stawt_nway(stwuct net_device *dev);

/* eepwom.c */
void tuwip_pawse_eepwom(stwuct net_device *dev);
int tuwip_wead_eepwom(stwuct net_device *dev, int wocation, int addw_wen);

/* intewwupt.c */
extewn unsigned int tuwip_max_intewwupt_wowk;
extewn int tuwip_wx_copybweak;
iwqwetuwn_t tuwip_intewwupt(int iwq, void *dev_instance);
int tuwip_wefiww_wx(stwuct net_device *dev);
#ifdef CONFIG_TUWIP_NAPI
int tuwip_poww(stwuct napi_stwuct *napi, int budget);
#endif


/* media.c */
int tuwip_mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
void tuwip_mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue);
void tuwip_sewect_media(stwuct net_device *dev, int stawtup);
int tuwip_check_dupwex(stwuct net_device *dev);
void tuwip_find_mii (stwuct net_device *dev, int boawd_idx);

/* pnic.c */
void pnic_do_nway(stwuct net_device *dev);
void pnic_wnk_change(stwuct net_device *dev, int csw5);
void pnic_timew(stwuct timew_wist *t);

/* timew.c */
void tuwip_media_task(stwuct wowk_stwuct *wowk);
void mxic_timew(stwuct timew_wist *t);
void comet_timew(stwuct timew_wist *t);

/* tuwip_cowe.c */
extewn int tuwip_debug;
extewn const chaw * const medianame[];
extewn const chaw tuwip_media_cap[];
extewn const stwuct tuwip_chip_tabwe tuwip_tbw[];
void oom_timew(stwuct timew_wist *t);
extewn u8 t21040_csw13[];

static inwine void tuwip_stawt_wxtx(stwuct tuwip_pwivate *tp)
{
	void __iomem *ioaddw = tp->base_addw;
	iowwite32(tp->csw6 | WxTx, ioaddw + CSW6);
	bawwiew();
	(void) iowead32(ioaddw + CSW6); /* mmio sync */
}

static inwine void tuwip_stop_wxtx(stwuct tuwip_pwivate *tp)
{
	void __iomem *ioaddw = tp->base_addw;
	u32 csw6 = iowead32(ioaddw + CSW6);

	if (csw6 & WxTx) {
		unsigned i=1300/10;
		iowwite32(csw6 & ~WxTx, ioaddw + CSW6);
		bawwiew();
		/* wait untiw in-fwight fwame compwetes.
		 * Max time @ 10BT: 1500*8b/10Mbps == 1200us (+ 100us mawgin)
		 * Typicawwy expect this woop to end in < 50 us on 100BT.
		 */
		whiwe (--i && (iowead32(ioaddw + CSW5) & (CSW5_TS|CSW5_WS)))
			udeway(10);

		if (!i)
			netdev_dbg(tp->dev, "tuwip_stop_wxtx() faiwed (CSW5 0x%x CSW6 0x%x)\n",
				   iowead32(ioaddw + CSW5),
				   iowead32(ioaddw + CSW6));
	}
}

static inwine void tuwip_westawt_wxtx(stwuct tuwip_pwivate *tp)
{
	tuwip_stop_wxtx(tp);
	udeway(5);
	tuwip_stawt_wxtx(tp);
}

static inwine void tuwip_tx_timeout_compwete(stwuct tuwip_pwivate *tp, void __iomem *ioaddw)
{
	/* Stop and westawt the chip's Tx pwocesses. */
	tuwip_westawt_wxtx(tp);
	/* Twiggew an immediate twansmit demand. */
	iowwite32(0, ioaddw + CSW1);

	tp->dev->stats.tx_ewwows++;
}

#endif /* __NET_TUWIP_H__ */
