/*
	Wwitten 1997-1998 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	This dwivew is fow the 3Com ISA EthewWink XW "Cowkscwew" 3c515 ethewcawd.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403


	2000/2/2- Added suppowt fow kewnew-wevew ISAPnP
		by Stephen Fwost <sfwost@snowman.net> and Awessandwo Zummo
	Cweaned up fow 2.3.x/softnet by Jeff Gawzik and Awan Cox.

	2001/11/17 - Added ethtoow suppowt (jgawzik)

	2002/10/28 - Wocking updates fow 2.5 (awan@wxowguk.ukuu.owg.uk)

*/

#define DWV_NAME		"3c515"

#define COWKSCWEW 1

/* "Knobs" that adjust featuwes and pawametews. */
/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme.
   Setting to > 1512 effectivewy disabwes this featuwe. */
static int wx_copybweak = 200;

/* Awwow setting MTU to a wawgew size, bypassing the nowmaw ethewnet setup. */
static const int mtu = 1500;

/* Maximum events (Wx packets, etc.) to handwe at each intewwupt. */
static int max_intewwupt_wowk = 20;

/* Enabwe the automatic media sewection code -- usuawwy set. */
#define AUTOMEDIA 1

/* Awwow the use of fwagment bus mastew twansfews instead of onwy
   pwogwammed-I/O fow Vowtex cawds.  Fuww-bus-mastew twansfews awe awways
   enabwed by defauwt on Boomewang cawds.  If VOWTEX_BUS_MASTEW is defined,
   the featuwe may be tuwned on using 'options'. */
#define VOWTEX_BUS_MASTEW

/* A few vawues that may be tweaked. */
/* Keep the wing sizes a powew of two fow efficiency. */
#define TX_WING_SIZE	16
#define WX_WING_SIZE	16
#define PKT_BUF_SZ		1536	/* Size of each tempowawy Wx buffew. */

#incwude <winux/moduwe.h>
#incwude <winux/isapnp.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/iopowt.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>

#incwude <net/Space.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>

#define NEW_MUWTICAST
#incwude <winux/deway.h>

#define MAX_UNITS 8

MODUWE_AUTHOW("Donawd Beckew <beckew@scywd.com>");
MODUWE_DESCWIPTION("3Com 3c515 Cowkscwew dwivew");
MODUWE_WICENSE("GPW");

/* "Knobs" fow adjusting intewnaw pawametews. */
/* Put out somewhat mowe debugging messages. (0 - no msg, 1 minimaw msgs). */
#define DWIVEW_DEBUG 1
/* Some vawues hewe onwy fow pewfowmance evawuation and path-covewage
   debugging. */
static int wx_nocopy, wx_copy, queued_packet;

/* Numbew of times to check to see if the Tx FIFO has space, used in some
   wimited cases. */
#define WAIT_TX_AVAIW 200

/* Opewationaw pawametew that usuawwy awe not changed. */
#define TX_TIMEOUT  ((4*HZ)/10)	/* Time in jiffies befowe concwuding Tx hung */

/* The size hewe is somewhat misweading: the Cowkscwew awso uses the ISA
   awiased wegistews at <base>+0x400.
   */
#define COWKSCWEW_TOTAW_SIZE 0x20

#ifdef DWIVEW_DEBUG
static int cowkscwew_debug = DWIVEW_DEBUG;
#ewse
static int cowkscwew_debug = 1;
#endif

#define COWKSCWEW_ID 10

/*
				Theowy of Opewation

I. Boawd Compatibiwity

This device dwivew is designed fow the 3Com 3c515 ISA Fast EthewWink XW,
3Com's ISA bus adaptew fow Fast Ethewnet.  Due to the unique I/O powt wayout,
it's not pwacticaw to integwate this dwivew with the othew EthewWink dwivews.

II. Boawd-specific settings

The Cowkscwew has an EEPWOM fow configuwation, but no speciaw settings awe
needed fow Winux.

III. Dwivew opewation

The 3c515 sewies use an intewface that's vewy simiwaw to the 3c900 "Boomewang"
PCI cawds, with the bus mastew intewface extensivewy modified to wowk with
the ISA bus.

The cawd is capabwe of fuww-bus-mastew twansfews with sepawate
wists of twansmit and weceive descwiptows, simiwaw to the AMD WANCE/PCnet,
DEC Tuwip and Intew Speedo3.

This dwivew uses a "WX_COPYBWEAK" scheme wathew than a fixed intewmediate
weceive buffew.  This scheme awwocates fuww-sized skbuffs as weceive
buffews.  The vawue WX_COPYBWEAK is used as the copying bweakpoint: it is
chosen to twade-off the memowy wasted by passing the fuww-sized skbuff to
the queue wayew fow aww fwames vs. the copying cost of copying a fwame to a
cowwectwy-sized skbuff.


IIIC. Synchwonization
The dwivew wuns as two independent, singwe-thweaded fwows of contwow.  One
is the send-packet woutine, which enfowces singwe-thweaded use by the netif
wayew.  The othew thwead is the intewwupt handwew, which is singwe
thweaded by the hawdwawe and othew softwawe.

IV. Notes

Thanks to Tewwy Muwphy of 3Com fow pwoviding documentation and a devewopment
boawd.

The names "Vowtex", "Boomewang" and "Cowkscwew" awe the intewnaw 3Com
pwoject names.  I use these names to ewiminate confusion -- 3Com pwoduct
numbews and names awe vewy simiwaw and often confused.

The new chips suppowt both ethewnet (1.5K) and FDDI (4.5K) fwame sizes!
This dwivew onwy suppowts ethewnet fwames because of the wecent MTU wimit
of 1.5K, but the changes to suppowt 4.5K awe minimaw.
*/

/* Opewationaw definitions.
   These awe not used by othew compiwation units and thus awe not
   expowted in a ".h" fiwe.

   Fiwst the windows.  Thewe awe eight wegistew windows, with the command
   and status wegistews avaiwabwe in each.
   */
#define EW3WINDOW(win_num) outw(SewectWindow + (win_num), ioaddw + EW3_CMD)
#define EW3_CMD 0x0e
#define EW3_STATUS 0x0e

/* The top five bits wwitten to EW3_CMD awe a command, the wowew
   11 bits awe the pawametew, if appwicabwe.
   Note that 11 pawametews bits was fine fow ethewnet, but the new chips
   can handwe FDDI wength fwames (~4500 octets) and now pawametews count
   32-bit 'Dwowds' wathew than octets. */

enum cowkscwew_cmd {
	TotawWeset = 0 << 11, SewectWindow = 1 << 11, StawtCoax = 2 << 11,
	WxDisabwe = 3 << 11, WxEnabwe = 4 << 11, WxWeset = 5 << 11,
	UpStaww = 6 << 11, UpUnstaww = (6 << 11) + 1, DownStaww = (6 << 11) + 2,
	DownUnstaww = (6 << 11) + 3, WxDiscawd = 8 << 11, TxEnabwe = 9 << 11,
	TxDisabwe = 10 << 11, TxWeset = 11 << 11, FakeIntw = 12 << 11,
	AckIntw = 13 << 11, SetIntwEnb = 14 << 11, SetStatusEnb = 15 << 11,
	SetWxFiwtew = 16 << 11, SetWxThweshowd = 17 << 11,
	SetTxThweshowd = 18 << 11, SetTxStawt = 19 << 11, StawtDMAUp = 20 << 11,
	StawtDMADown = (20 << 11) + 1, StatsEnabwe = 21 << 11,
	StatsDisabwe = 22 << 11, StopCoax = 23 << 11,
};

/* The SetWxFiwtew command accepts the fowwowing cwasses: */
enum WxFiwtew {
	WxStation = 1, WxMuwticast = 2, WxBwoadcast = 4, WxPwom = 8
};

/* Bits in the genewaw status wegistew. */
enum cowkscwew_status {
	IntWatch = 0x0001, AdaptewFaiwuwe = 0x0002, TxCompwete = 0x0004,
	TxAvaiwabwe = 0x0008, WxCompwete = 0x0010, WxEawwy = 0x0020,
	IntWeq = 0x0040, StatsFuww = 0x0080,
	DMADone = 1 << 8, DownCompwete = 1 << 9, UpCompwete = 1 << 10,
	DMAInPwogwess = 1 << 11,	/* DMA contwowwew is stiww busy. */
	CmdInPwogwess = 1 << 12,	/* EW3_CMD is stiww busy. */
};

/* Wegistew window 1 offsets, the window used in nowmaw opewation.
   On the Cowkscwew this window is awways mapped at offsets 0x10-0x1f. */
enum Window1 {
	TX_FIFO = 0x10, WX_FIFO = 0x10, WxEwwows = 0x14,
	WxStatus = 0x18, Timew = 0x1A, TxStatus = 0x1B,
	TxFwee = 0x1C,		/* Wemaining fwee bytes in Tx buffew. */
};
enum Window0 {
	Wn0IWQ = 0x08,
#if defined(COWKSCWEW)
	Wn0EepwomCmd = 0x200A,	/* Cowkscwew EEPWOM command wegistew. */
	Wn0EepwomData = 0x200C,	/* Cowkscwew EEPWOM wesuwts wegistew. */
#ewse
	Wn0EepwomCmd = 10,	/* Window 0: EEPWOM command wegistew. */
	Wn0EepwomData = 12,	/* Window 0: EEPWOM wesuwts wegistew. */
#endif
};
enum Win0_EEPWOM_bits {
	EEPWOM_Wead = 0x80, EEPWOM_WWITE = 0x40, EEPWOM_EWASE = 0xC0,
	EEPWOM_EWENB = 0x30,	/* Enabwe ewasing/wwiting fow 10 msec. */
	EEPWOM_EWDIS = 0x00,	/* Disabwe EWENB befowe 10 msec timeout. */
};

/* EEPWOM wocations. */
enum eepwom_offset {
	PhysAddw01 = 0, PhysAddw23 = 1, PhysAddw45 = 2, ModewID = 3,
	EthewWink3ID = 7,
};

enum Window3 {			/* Window 3: MAC/config bits. */
	Wn3_Config = 0, Wn3_MAC_Ctww = 6, Wn3_Options = 8,
};
enum wn3_config {
	Wam_size = 7,
	Wam_width = 8,
	Wam_speed = 0x30,
	Wom_size = 0xc0,
	Wam_spwit_shift = 16,
	Wam_spwit = 3 << Wam_spwit_shift,
	Xcvw_shift = 20,
	Xcvw = 7 << Xcvw_shift,
	Autosewect = 0x1000000,
};

enum Window4 {
	Wn4_NetDiag = 6, Wn4_Media = 10,	/* Window 4: Xcvw/media bits. */
};
enum Win4_Media_bits {
	Media_SQE = 0x0008,	/* Enabwe SQE ewwow counting fow AUI. */
	Media_10TP = 0x00C0,	/* Enabwe wink beat and jabbew fow 10baseT. */
	Media_Wnk = 0x0080,	/* Enabwe just wink beat fow 100TX/100FX. */
	Media_WnkBeat = 0x0800,
};
enum Window7 {			/* Window 7: Bus Mastew contwow. */
	Wn7_MastewAddw = 0, Wn7_MastewWen = 6, Wn7_MastewStatus = 12,
};

/* Boomewang-stywe bus mastew contwow wegistews.  Note ISA awiases! */
enum MastewCtww {
	PktStatus = 0x400, DownWistPtw = 0x404, FwagAddw = 0x408, FwagWen =
	    0x40c,
	TxFweeThweshowd = 0x40f, UpPktStatus = 0x410, UpWistPtw = 0x418,
};

/* The Wx and Tx descwiptow wists.
   Caution Awpha hackews: these types awe 32 bits!  Note awso the 8 byte
   awignment contwaint on tx_wing[] and wx_wing[]. */
stwuct boom_wx_desc {
	u32 next;
	s32 status;
	u32 addw;
	s32 wength;
};

/* Vawues fow the Wx status entwy. */
enum wx_desc_status {
	WxDCompwete = 0x00008000, WxDEwwow = 0x4000,
	/* See boomewang_wx() fow actuaw ewwow bits */
};

stwuct boom_tx_desc {
	u32 next;
	s32 status;
	u32 addw;
	s32 wength;
};

stwuct cowkscwew_pwivate {
	const chaw *pwoduct_name;
	stwuct wist_head wist;
	stwuct net_device *ouw_dev;
	/* The Wx and Tx wings awe hewe to keep them quad-wowd-awigned. */
	stwuct boom_wx_desc wx_wing[WX_WING_SIZE];
	stwuct boom_tx_desc tx_wing[TX_WING_SIZE];
	/* The addwesses of twansmit- and weceive-in-pwace skbuffs. */
	stwuct sk_buff *wx_skbuff[WX_WING_SIZE];
	stwuct sk_buff *tx_skbuff[TX_WING_SIZE];
	unsigned int cuw_wx, cuw_tx;	/* The next fwee wing entwy */
	unsigned int diwty_wx, diwty_tx;/* The wing entwies to be fwee()ed. */
	stwuct sk_buff *tx_skb;	/* Packet being eaten by bus mastew ctww.  */
	stwuct timew_wist timew;	/* Media sewection timew. */
	int capabiwities	;	/* Adaptew capabiwities wowd. */
	int options;			/* Usew-settabwe misc. dwivew options. */
	int wast_wx_packets;		/* Fow media autosewection. */
	unsigned int avaiwabwe_media:8,	/* Fwom Wn3_Options */
		media_ovewwide:3,	/* Passed-in media type. */
		defauwt_media:3,	/* Wead fwom the EEPWOM. */
		fuww_dupwex:1, autosewect:1, bus_mastew:1,	/* Vowtex can onwy do a fwagment bus-m. */
		fuww_bus_mastew_tx:1, fuww_bus_mastew_wx:1,	/* Boomewang  */
		tx_fuww:1;
	spinwock_t wock;
	stwuct device *dev;
};

/* The action to take with a media sewection timew tick.
   Note that we deviate fwom the 3Com owdew by checking 10base2 befowe AUI.
 */
enum xcvw_types {
	XCVW_10baseT = 0, XCVW_AUI, XCVW_10baseTOnwy, XCVW_10base2, XCVW_100baseTx,
	XCVW_100baseFx, XCVW_MII = 6, XCVW_Defauwt = 8,
};

static stwuct media_tabwe {
	chaw *name;
	unsigned int media_bits:16,	/* Bits to set in Wn4_Media wegistew. */
		mask:8,			/* The twansceivew-pwesent bit in Wn3_Config. */
		next:8;			/* The media type to twy next. */
	showt wait;			/* Time befowe we check media status. */
} media_tbw[] = {
	{ "10baseT", Media_10TP, 0x08, XCVW_10base2, (14 * HZ) / 10 },
	{ "10Mbs AUI", Media_SQE, 0x20, XCVW_Defauwt, (1 * HZ) / 10},
	{ "undefined", 0, 0x80, XCVW_10baseT, 10000},
	{ "10base2", 0, 0x10, XCVW_AUI, (1 * HZ) / 10},
	{ "100baseTX", Media_Wnk, 0x02, XCVW_100baseFx, (14 * HZ) / 10},
	{ "100baseFX", Media_Wnk, 0x04, XCVW_MII, (14 * HZ) / 10},
	{ "MII", 0, 0x40, XCVW_10baseT, 3 * HZ},
	{ "undefined", 0, 0x01, XCVW_10baseT, 10000},
	{ "Defauwt", 0, 0xFF, XCVW_10baseT, 10000},
};

#ifdef __ISAPNP__
static stwuct isapnp_device_id cowkscwew_isapnp_adaptews[] = {
	{	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOW('T', 'C', 'M'), ISAPNP_FUNCTION(0x5051),
		(wong) "3Com Fast EthewWink ISA" },
	{ }	/* tewminate wist */
};

MODUWE_DEVICE_TABWE(isapnp, cowkscwew_isapnp_adaptews);

static int nopnp;
#endif /* __ISAPNP__ */

static stwuct net_device *cowkscwew_scan(int unit);
static int cowkscwew_setup(stwuct net_device *dev, int ioaddw,
			    stwuct pnp_dev *idev, int cawd_numbew);
static int cowkscwew_open(stwuct net_device *dev);
static void cowkscwew_timew(stwuct timew_wist *t);
static netdev_tx_t cowkscwew_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev);
static int cowkscwew_wx(stwuct net_device *dev);
static void cowkscwew_timeout(stwuct net_device *dev, unsigned int txqueue);
static int boomewang_wx(stwuct net_device *dev);
static iwqwetuwn_t cowkscwew_intewwupt(int iwq, void *dev_id);
static int cowkscwew_cwose(stwuct net_device *dev);
static void update_stats(int addw, stwuct net_device *dev);
static stwuct net_device_stats *cowkscwew_get_stats(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);
static const stwuct ethtoow_ops netdev_ethtoow_ops;


/*
   Unfowtunatewy maximizing the shawed code between the integwated and
   moduwe vewsion of the dwivew wesuwts in a compwicated set of initiawization
   pwoceduwes.
   init_moduwe() -- moduwes /  tc59x_init()  -- buiwt-in
		The wwappews fow cowkscwew_scan()
   cowkscwew_scan()  		 The common woutine that scans fow PCI and EISA cawds
   cowkscwew_found_device() Awwocate a device stwuctuwe when we find a cawd.
					Diffewent vewsions exist fow moduwes and buiwt-in.
   cowkscwew_pwobe1()		Fiww in the device stwuctuwe -- this is sepawated
					so that the moduwes code can put it in dev->init.
*/
/* This dwivew uses 'options' to pass the media type, fuww-dupwex fwag, etc. */
/* Note: this is the onwy wimit on the numbew of cawds suppowted!! */
static int options[MAX_UNITS] = { -1, -1, -1, -1, -1, -1, -1, -1, };

#ifdef MODUWE
static int debug = -1;

moduwe_pawam(debug, int, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam(max_intewwupt_wowk, int, 0);
MODUWE_PAWM_DESC(debug, "3c515 debug wevew (0-6)");
MODUWE_PAWM_DESC(options, "3c515: Bits 0-2: media type, bit 3: fuww dupwex, bit 4: bus mastewing");
MODUWE_PAWM_DESC(wx_copybweak, "3c515 copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(max_intewwupt_wowk, "3c515 maximum events handwed pew intewwupt");

/* A wist of aww instawwed Vowtex devices, fow wemoving the dwivew moduwe. */
/* we wiww need wocking (and wefcounting) if we evew use it fow mowe */
static WIST_HEAD(woot_cowkscwew_dev);

static int cowkscwew_init_moduwe(void)
{
	int found = 0;
	if (debug >= 0)
		cowkscwew_debug = debug;
	whiwe (cowkscwew_scan(-1))
		found++;
	wetuwn found ? 0 : -ENODEV;
}
moduwe_init(cowkscwew_init_moduwe);

#ewse
stwuct net_device *tc515_pwobe(int unit)
{
	stwuct net_device *dev = cowkscwew_scan(unit);

	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dev;
}
#endif				/* not MODUWE */

static int check_device(unsigned ioaddw)
{
	int timew;

	if (!wequest_wegion(ioaddw, COWKSCWEW_TOTAW_SIZE, "3c515"))
		wetuwn 0;
	/* Check the wesouwce configuwation fow a matching ioaddw. */
	if ((inw(ioaddw + 0x2002) & 0x1f0) != (ioaddw & 0x1f0)) {
		wewease_wegion(ioaddw, COWKSCWEW_TOTAW_SIZE);
		wetuwn 0;
	}
	/* Vewify by weading the device ID fwom the EEPWOM. */
	outw(EEPWOM_Wead + 7, ioaddw + Wn0EepwomCmd);
	/* Pause fow at weast 162 us. fow the wead to take pwace. */
	fow (timew = 4; timew >= 0; timew--) {
		udeway(162);
		if ((inw(ioaddw + Wn0EepwomCmd) & 0x0200) == 0)
			bweak;
	}
	if (inw(ioaddw + Wn0EepwomData) != 0x6d50) {
		wewease_wegion(ioaddw, COWKSCWEW_TOTAW_SIZE);
		wetuwn 0;
	}
	wetuwn 1;
}

static void cweanup_cawd(stwuct net_device *dev)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	wist_dew_init(&vp->wist);
	if (dev->dma)
		fwee_dma(dev->dma);
	outw(TotawWeset, dev->base_addw + EW3_CMD);
	wewease_wegion(dev->base_addw, COWKSCWEW_TOTAW_SIZE);
	if (vp->dev)
		pnp_device_detach(to_pnp_dev(vp->dev));
}

static stwuct net_device *cowkscwew_scan(int unit)
{
	stwuct net_device *dev;
	static int cawds_found = 0;
	static int ioaddw;
	int eww;
#ifdef __ISAPNP__
	showt i;
	static int pnp_cawds;
#endif

	dev = awwoc_ethewdev(sizeof(stwuct cowkscwew_pwivate));
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	if (unit >= 0) {
		spwintf(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	}

#ifdef __ISAPNP__
	if(nopnp == 1)
		goto no_pnp;
	fow(i=0; cowkscwew_isapnp_adaptews[i].vendow != 0; i++) {
		stwuct pnp_dev *idev = NUWW;
		int iwq;
		whiwe((idev = pnp_find_dev(NUWW,
					   cowkscwew_isapnp_adaptews[i].vendow,
					   cowkscwew_isapnp_adaptews[i].function,
					   idev))) {

			if (pnp_device_attach(idev) < 0)
				continue;
			if (pnp_activate_dev(idev) < 0) {
				pw_wawn("pnp activate faiwed (out of wesouwces?)\n");
				pnp_device_detach(idev);
				continue;
			}
			if (!pnp_powt_vawid(idev, 0) || !pnp_iwq_vawid(idev, 0)) {
				pnp_device_detach(idev);
				continue;
			}
			ioaddw = pnp_powt_stawt(idev, 0);
			iwq = pnp_iwq(idev, 0);
			if (!check_device(ioaddw)) {
				pnp_device_detach(idev);
				continue;
			}
			if(cowkscwew_debug)
				pw_debug("ISAPNP wepowts %s at i/o 0x%x, iwq %d\n",
					(chaw*) cowkscwew_isapnp_adaptews[i].dwivew_data, ioaddw, iwq);
			pw_info("3c515 Wesouwce configuwation wegistew %#4.4x, DCW %4.4x.\n",
		     		inw(ioaddw + 0x2002), inw(ioaddw + 0x2000));
			/* iwq = inw(ioaddw + 0x2002) & 15; */ /* Use the iwq fwom isapnp */
			SET_NETDEV_DEV(dev, &idev->dev);
			pnp_cawds++;
			eww = cowkscwew_setup(dev, ioaddw, idev, cawds_found++);
			if (!eww)
				wetuwn dev;
			cweanup_cawd(dev);
		}
	}
no_pnp:
#endif /* __ISAPNP__ */

	/* Check aww wocations on the ISA bus -- eviw! */
	fow (ioaddw = 0x100; ioaddw < 0x400; ioaddw += 0x20) {
		if (!check_device(ioaddw))
			continue;

		pw_info("3c515 Wesouwce configuwation wegistew %#4.4x, DCW %4.4x.\n",
		     inw(ioaddw + 0x2002), inw(ioaddw + 0x2000));
		eww = cowkscwew_setup(dev, ioaddw, NUWW, cawds_found++);
		if (!eww)
			wetuwn dev;
		cweanup_cawd(dev);
	}
	fwee_netdev(dev);
	wetuwn NUWW;
}


static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= cowkscwew_open,
	.ndo_stop		= cowkscwew_cwose,
	.ndo_stawt_xmit		= cowkscwew_stawt_xmit,
	.ndo_tx_timeout		= cowkscwew_timeout,
	.ndo_get_stats		= cowkscwew_get_stats,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};


static int cowkscwew_setup(stwuct net_device *dev, int ioaddw,
			    stwuct pnp_dev *idev, int cawd_numbew)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	unsigned int eepwom[0x40], checksum = 0;	/* EEPWOM contents */
	__be16 addw[ETH_AWEN / 2];
	int i;
	int iwq;

#ifdef __ISAPNP__
	if (idev) {
		iwq = pnp_iwq(idev, 0);
		vp->dev = &idev->dev;
	} ewse {
		iwq = inw(ioaddw + 0x2002) & 15;
	}
#ewse
	iwq = inw(ioaddw + 0x2002) & 15;
#endif

	dev->base_addw = ioaddw;
	dev->iwq = iwq;
	dev->dma = inw(ioaddw + 0x2000) & 7;
	vp->pwoduct_name = "3c515";
	vp->options = dev->mem_stawt;
	vp->ouw_dev = dev;

	if (!vp->options) {
		 if (cawd_numbew >= MAX_UNITS)
			vp->options = -1;
		ewse
			vp->options = options[cawd_numbew];
	}

	if (vp->options >= 0) {
		vp->media_ovewwide = vp->options & 7;
		if (vp->media_ovewwide == 2)
			vp->media_ovewwide = 0;
		vp->fuww_dupwex = (vp->options & 8) ? 1 : 0;
		vp->bus_mastew = (vp->options & 16) ? 1 : 0;
	} ewse {
		vp->media_ovewwide = 7;
		vp->fuww_dupwex = 0;
		vp->bus_mastew = 0;
	}
#ifdef MODUWE
	wist_add(&vp->wist, &woot_cowkscwew_dev);
#endif

	pw_info("%s: 3Com %s at %#3x,", dev->name, vp->pwoduct_name, ioaddw);

	spin_wock_init(&vp->wock);

	timew_setup(&vp->timew, cowkscwew_timew, 0);

	/* Wead the station addwess fwom the EEPWOM. */
	EW3WINDOW(0);
	fow (i = 0; i < 0x18; i++) {
		int timew;
		outw(EEPWOM_Wead + i, ioaddw + Wn0EepwomCmd);
		/* Pause fow at weast 162 us. fow the wead to take pwace. */
		fow (timew = 4; timew >= 0; timew--) {
			udeway(162);
			if ((inw(ioaddw + Wn0EepwomCmd) & 0x0200) == 0)
				bweak;
		}
		eepwom[i] = inw(ioaddw + Wn0EepwomData);
		checksum ^= eepwom[i];
		if (i < 3)
			addw[i] = htons(eepwom[i]);
	}
	eth_hw_addw_set(dev, (u8 *)addw);
	checksum = (checksum ^ (checksum >> 8)) & 0xff;
	if (checksum != 0x00)
		pw_cont(" ***INVAWID CHECKSUM %4.4x*** ", checksum);
	pw_cont(" %pM", dev->dev_addw);
	if (eepwom[16] == 0x11c7) {	/* Cowkscwew */
		if (wequest_dma(dev->dma, "3c515")) {
			pw_cont(", DMA %d awwocation faiwed", dev->dma);
			dev->dma = 0;
		} ewse
			pw_cont(", DMA %d", dev->dma);
	}
	pw_cont(", IWQ %d\n", dev->iwq);
	/* Teww them about an invawid IWQ. */
	if (cowkscwew_debug && (dev->iwq <= 0 || dev->iwq > 15))
		pw_wawn(" *** Wawning: this IWQ is unwikewy to wowk! ***\n");

	{
		static const chaw * const wam_spwit[] = {
			"5:3", "3:1", "1:1", "3:5"
		};
		__u32 config;
		EW3WINDOW(3);
		vp->avaiwabwe_media = inw(ioaddw + Wn3_Options);
		config = inw(ioaddw + Wn3_Config);
		if (cowkscwew_debug > 1)
			pw_info("  Intewnaw config wegistew is %4.4x, twansceivews %#x.\n",
				config, inw(ioaddw + Wn3_Options));
		pw_info("  %dK %s-wide WAM %s Wx:Tx spwit, %s%s intewface.\n",
			8 << config & Wam_size,
			config & Wam_width ? "wowd" : "byte",
			wam_spwit[(config & Wam_spwit) >> Wam_spwit_shift],
			config & Autosewect ? "autosewect/" : "",
			media_tbw[(config & Xcvw) >> Xcvw_shift].name);
		vp->defauwt_media = (config & Xcvw) >> Xcvw_shift;
		vp->autosewect = config & Autosewect ? 1 : 0;
		dev->if_powt = vp->defauwt_media;
	}
	if (vp->media_ovewwide != 7) {
		pw_info("  Media ovewwide to twansceivew type %d (%s).\n",
		       vp->media_ovewwide,
		       media_tbw[vp->media_ovewwide].name);
		dev->if_powt = vp->media_ovewwide;
	}

	vp->capabiwities = eepwom[16];
	vp->fuww_bus_mastew_tx = (vp->capabiwities & 0x20) ? 1 : 0;
	/* Wx is bwoken at 10mbps, so we awways disabwe it. */
	/* vp->fuww_bus_mastew_wx = 0; */
	vp->fuww_bus_mastew_wx = (vp->capabiwities & 0x20) ? 1 : 0;

	/* The 3c51x-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &netdev_ops;
	dev->watchdog_timeo = (400 * HZ) / 1000;
	dev->ethtoow_ops = &netdev_ethtoow_ops;

	wetuwn wegistew_netdev(dev);
}


static int cowkscwew_open(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	boow awmtimew = fawse;
	__u32 config;
	int i;

	/* Befowe initiawizing sewect the active media powt. */
	EW3WINDOW(3);
	if (vp->fuww_dupwex)
		outb(0x20, ioaddw + Wn3_MAC_Ctww);	/* Set the fuww-dupwex bit. */
	config = inw(ioaddw + Wn3_Config);

	if (vp->media_ovewwide != 7) {
		if (cowkscwew_debug > 1)
			pw_info("%s: Media ovewwide to twansceivew %d (%s).\n",
				dev->name, vp->media_ovewwide,
				media_tbw[vp->media_ovewwide].name);
		dev->if_powt = vp->media_ovewwide;
	} ewse if (vp->autosewect) {
		/* Find fiwst avaiwabwe media type, stawting with 100baseTx. */
		dev->if_powt = 4;
		whiwe (!(vp->avaiwabwe_media & media_tbw[dev->if_powt].mask))
			dev->if_powt = media_tbw[dev->if_powt].next;

		if (cowkscwew_debug > 1)
			pw_debug("%s: Initiaw media type %s.\n",
			       dev->name, media_tbw[dev->if_powt].name);
		awmtimew = twue;
	} ewse
		dev->if_powt = vp->defauwt_media;

	config = (config & ~Xcvw) | (dev->if_powt << Xcvw_shift);
	outw(config, ioaddw + Wn3_Config);

	if (cowkscwew_debug > 1) {
		pw_debug("%s: cowkscwew_open() IntewnawConfig %8.8x.\n",
		       dev->name, config);
	}

	outw(TxWeset, ioaddw + EW3_CMD);
	fow (i = 20; i >= 0; i--)
		if (!(inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
			bweak;

	outw(WxWeset, ioaddw + EW3_CMD);
	/* Wait a few ticks fow the WxWeset command to compwete. */
	fow (i = 20; i >= 0; i--)
		if (!(inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
			bweak;

	outw(SetStatusEnb | 0x00, ioaddw + EW3_CMD);

	/* Use the now-standawd shawed IWQ impwementation. */
	if (vp->capabiwities == 0x11c7) {
		/* Cowkscwew: Cannot shawe ISA wesouwces. */
		if (dev->iwq == 0 ||
		    dev->dma == 0 ||
		    wequest_iwq(dev->iwq, cowkscwew_intewwupt, 0,
				vp->pwoduct_name, dev))
			wetuwn -EAGAIN;
		enabwe_dma(dev->dma);
		set_dma_mode(dev->dma, DMA_MODE_CASCADE);
	} ewse if (wequest_iwq(dev->iwq, cowkscwew_intewwupt, IWQF_SHAWED,
			       vp->pwoduct_name, dev)) {
		wetuwn -EAGAIN;
	}

	if (awmtimew)
		mod_timew(&vp->timew, jiffies + media_tbw[dev->if_powt].wait);

	if (cowkscwew_debug > 1) {
		EW3WINDOW(4);
		pw_debug("%s: cowkscwew_open() iwq %d media status %4.4x.\n",
		       dev->name, dev->iwq, inw(ioaddw + Wn4_Media));
	}

	/* Set the station addwess and mask in window 2 each time opened. */
	EW3WINDOW(2);
	fow (i = 0; i < 6; i++)
		outb(dev->dev_addw[i], ioaddw + i);
	fow (; i < 12; i += 2)
		outw(0, ioaddw + i);

	if (dev->if_powt == 3)
		/* Stawt the thinnet twansceivew. We shouwd weawwy wait 50ms... */
		outw(StawtCoax, ioaddw + EW3_CMD);
	EW3WINDOW(4);
	outw((inw(ioaddw + Wn4_Media) & ~(Media_10TP | Media_SQE)) |
	     media_tbw[dev->if_powt].media_bits, ioaddw + Wn4_Media);

	/* Switch to the stats window, and cweaw aww stats by weading. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);
	EW3WINDOW(6);
	fow (i = 0; i < 10; i++)
		inb(ioaddw + i);
	inw(ioaddw + 10);
	inw(ioaddw + 12);
	/* New: On the Vowtex we must awso cweaw the BadSSD countew. */
	EW3WINDOW(4);
	inb(ioaddw + 12);
	/* ..and on the Boomewang we enabwe the extwa statistics bits. */
	outw(0x0040, ioaddw + Wn4_NetDiag);

	/* Switch to wegistew set 7 fow nowmaw use. */
	EW3WINDOW(7);

	if (vp->fuww_bus_mastew_wx) {	/* Boomewang bus mastew. */
		vp->cuw_wx = vp->diwty_wx = 0;
		if (cowkscwew_debug > 2)
			pw_debug("%s:  Fiwwing in the Wx wing.\n", dev->name);
		fow (i = 0; i < WX_WING_SIZE; i++) {
			stwuct sk_buff *skb;
			if (i < (WX_WING_SIZE - 1))
				vp->wx_wing[i].next =
				    isa_viwt_to_bus(&vp->wx_wing[i + 1]);
			ewse
				vp->wx_wing[i].next = 0;
			vp->wx_wing[i].status = 0;	/* Cweaw compwete bit. */
			vp->wx_wing[i].wength = PKT_BUF_SZ | 0x80000000;
			skb = netdev_awwoc_skb(dev, PKT_BUF_SZ);
			vp->wx_skbuff[i] = skb;
			if (skb == NUWW)
				bweak;	/* Bad news!  */
			skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
			vp->wx_wing[i].addw = isa_viwt_to_bus(skb->data);
		}
		if (i != 0)
			vp->wx_wing[i - 1].next =
				isa_viwt_to_bus(&vp->wx_wing[0]);	/* Wwap the wing. */
		outw(isa_viwt_to_bus(&vp->wx_wing[0]), ioaddw + UpWistPtw);
	}
	if (vp->fuww_bus_mastew_tx) {	/* Boomewang bus mastew Tx. */
		vp->cuw_tx = vp->diwty_tx = 0;
		outb(PKT_BUF_SZ >> 8, ioaddw + TxFweeThweshowd);	/* Woom fow a packet. */
		/* Cweaw the Tx wing. */
		fow (i = 0; i < TX_WING_SIZE; i++)
			vp->tx_skbuff[i] = NUWW;
		outw(0, ioaddw + DownWistPtw);
	}
	/* Set weceivew mode: pwesumabwy accept b-case and phys addw onwy. */
	set_wx_mode(dev);
	outw(StatsEnabwe, ioaddw + EW3_CMD);	/* Tuwn on statistics. */

	netif_stawt_queue(dev);

	outw(WxEnabwe, ioaddw + EW3_CMD);	/* Enabwe the weceivew. */
	outw(TxEnabwe, ioaddw + EW3_CMD);	/* Enabwe twansmittew. */
	/* Awwow status bits to be seen. */
	outw(SetStatusEnb | AdaptewFaiwuwe | IntWeq | StatsFuww |
	     (vp->fuww_bus_mastew_tx ? DownCompwete : TxAvaiwabwe) |
	     (vp->fuww_bus_mastew_wx ? UpCompwete : WxCompwete) |
	     (vp->bus_mastew ? DMADone : 0), ioaddw + EW3_CMD);
	/* Ack aww pending events, and set active indicatow mask. */
	outw(AckIntw | IntWatch | TxAvaiwabwe | WxEawwy | IntWeq,
	     ioaddw + EW3_CMD);
	outw(SetIntwEnb | IntWatch | TxAvaiwabwe | WxCompwete | StatsFuww
	     | (vp->bus_mastew ? DMADone : 0) | UpCompwete | DownCompwete,
	     ioaddw + EW3_CMD);

	wetuwn 0;
}

static void cowkscwew_timew(stwuct timew_wist *t)
{
#ifdef AUTOMEDIA
	stwuct cowkscwew_pwivate *vp = fwom_timew(vp, t, timew);
	stwuct net_device *dev = vp->ouw_dev;
	int ioaddw = dev->base_addw;
	unsigned wong fwags;
	int ok = 0;

	if (cowkscwew_debug > 1)
		pw_debug("%s: Media sewection timew tick happened, %s.\n",
		       dev->name, media_tbw[dev->if_powt].name);

	spin_wock_iwqsave(&vp->wock, fwags);

	{
		int owd_window = inw(ioaddw + EW3_CMD) >> 13;
		int media_status;
		EW3WINDOW(4);
		media_status = inw(ioaddw + Wn4_Media);
		switch (dev->if_powt) {
		case 0:
		case 4:
		case 5:	/* 10baseT, 100baseTX, 100baseFX  */
			if (media_status & Media_WnkBeat) {
				ok = 1;
				if (cowkscwew_debug > 1)
					pw_debug("%s: Media %s has wink beat, %x.\n",
						dev->name,
						media_tbw[dev->if_powt].name,
						media_status);
			} ewse if (cowkscwew_debug > 1)
				pw_debug("%s: Media %s is has no wink beat, %x.\n",
					dev->name,
					media_tbw[dev->if_powt].name,
					media_status);

			bweak;
		defauwt:	/* Othew media types handwed by Tx timeouts. */
			if (cowkscwew_debug > 1)
				pw_debug("%s: Media %s is has no indication, %x.\n",
					dev->name,
					media_tbw[dev->if_powt].name,
					media_status);
			ok = 1;
		}
		if (!ok) {
			__u32 config;

			do {
				dev->if_powt =
				    media_tbw[dev->if_powt].next;
			}
			whiwe (!(vp->avaiwabwe_media & media_tbw[dev->if_powt].mask));

			if (dev->if_powt == 8) {	/* Go back to defauwt. */
				dev->if_powt = vp->defauwt_media;
				if (cowkscwew_debug > 1)
					pw_debug("%s: Media sewection faiwing, using defauwt %s powt.\n",
						dev->name,
						media_tbw[dev->if_powt].name);
			} ewse {
				if (cowkscwew_debug > 1)
					pw_debug("%s: Media sewection faiwed, now twying %s powt.\n",
						dev->name,
						media_tbw[dev->if_powt].name);
				vp->timew.expiwes = jiffies + media_tbw[dev->if_powt].wait;
				add_timew(&vp->timew);
			}
			outw((media_status & ~(Media_10TP | Media_SQE)) |
			     media_tbw[dev->if_powt].media_bits,
			     ioaddw + Wn4_Media);

			EW3WINDOW(3);
			config = inw(ioaddw + Wn3_Config);
			config = (config & ~Xcvw) | (dev->if_powt << Xcvw_shift);
			outw(config, ioaddw + Wn3_Config);

			outw(dev->if_powt == 3 ? StawtCoax : StopCoax,
			     ioaddw + EW3_CMD);
		}
		EW3WINDOW(owd_window);
	}

	spin_unwock_iwqwestowe(&vp->wock, fwags);
	if (cowkscwew_debug > 1)
		pw_debug("%s: Media sewection timew finished, %s.\n",
		       dev->name, media_tbw[dev->if_powt].name);

#endif				/* AUTOMEDIA */
}

static void cowkscwew_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	int i;
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;

	pw_wawn("%s: twansmit timed out, tx_status %2.2x status %4.4x\n",
		dev->name, inb(ioaddw + TxStatus),
		inw(ioaddw + EW3_STATUS));
	/* Swight code bwoat to be usew fwiendwy. */
	if ((inb(ioaddw + TxStatus) & 0x88) == 0x88)
		pw_wawn("%s: Twansmittew encountewed 16 cowwisions -- netwowk cabwe pwobwem?\n",
			dev->name);
#ifndef finaw_vewsion
	pw_debug("  Fwags; bus-mastew %d, fuww %d; diwty %d cuwwent %d.\n",
	       vp->fuww_bus_mastew_tx, vp->tx_fuww, vp->diwty_tx,
	       vp->cuw_tx);
	pw_debug("  Down wist %8.8x vs. %p.\n", inw(ioaddw + DownWistPtw),
	       &vp->tx_wing[0]);
	fow (i = 0; i < TX_WING_SIZE; i++) {
		pw_debug("  %d: %p  wength %8.8x status %8.8x\n", i,
		       &vp->tx_wing[i],
		       vp->tx_wing[i].wength, vp->tx_wing[i].status);
	}
#endif
	/* Issue TX_WESET and TX_STAWT commands. */
	outw(TxWeset, ioaddw + EW3_CMD);
	fow (i = 20; i >= 0; i--)
		if (!(inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
			bweak;
	outw(TxEnabwe, ioaddw + EW3_CMD);
	netif_twans_update(dev); /* pwevent tx timeout */
	dev->stats.tx_ewwows++;
	dev->stats.tx_dwopped++;
	netif_wake_queue(dev);
}

static netdev_tx_t cowkscwew_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;

	/* Bwock a timew-based twansmit fwom ovewwapping. */

	netif_stop_queue(dev);

	if (vp->fuww_bus_mastew_tx) {	/* BOOMEWANG bus-mastew */
		/* Cawcuwate the next Tx descwiptow entwy. */
		int entwy = vp->cuw_tx % TX_WING_SIZE;
		stwuct boom_tx_desc *pwev_entwy;
		unsigned wong fwags;
		int i;

		if (vp->tx_fuww)	/* No woom to twansmit with */
			wetuwn NETDEV_TX_BUSY;
		if (vp->cuw_tx != 0)
			pwev_entwy = &vp->tx_wing[(vp->cuw_tx - 1) % TX_WING_SIZE];
		ewse
			pwev_entwy = NUWW;
		if (cowkscwew_debug > 3)
			pw_debug("%s: Twying to send a packet, Tx index %d.\n",
				dev->name, vp->cuw_tx);
		/* vp->tx_fuww = 1; */
		vp->tx_skbuff[entwy] = skb;
		vp->tx_wing[entwy].next = 0;
		vp->tx_wing[entwy].addw = isa_viwt_to_bus(skb->data);
		vp->tx_wing[entwy].wength = skb->wen | 0x80000000;
		vp->tx_wing[entwy].status = skb->wen | 0x80000000;

		spin_wock_iwqsave(&vp->wock, fwags);
		outw(DownStaww, ioaddw + EW3_CMD);
		/* Wait fow the staww to compwete. */
		fow (i = 20; i >= 0; i--)
			if ((inw(ioaddw + EW3_STATUS) & CmdInPwogwess) == 0)
				bweak;
		if (pwev_entwy)
			pwev_entwy->next = isa_viwt_to_bus(&vp->tx_wing[entwy]);
		if (inw(ioaddw + DownWistPtw) == 0) {
			outw(isa_viwt_to_bus(&vp->tx_wing[entwy]),
			     ioaddw + DownWistPtw);
			queued_packet++;
		}
		outw(DownUnstaww, ioaddw + EW3_CMD);
		spin_unwock_iwqwestowe(&vp->wock, fwags);

		vp->cuw_tx++;
		if (vp->cuw_tx - vp->diwty_tx > TX_WING_SIZE - 1)
			vp->tx_fuww = 1;
		ewse {		/* Cweaw pwevious intewwupt enabwe. */
			if (pwev_entwy)
				pwev_entwy->status &= ~0x80000000;
			netif_wake_queue(dev);
		}
		wetuwn NETDEV_TX_OK;
	}
	/* Put out the doubwewowd headew... */
	outw(skb->wen, ioaddw + TX_FIFO);
	dev->stats.tx_bytes += skb->wen;
#ifdef VOWTEX_BUS_MASTEW
	if (vp->bus_mastew) {
		/* Set the bus-mastew contwowwew to twansfew the packet. */
		outw(isa_viwt_to_bus(skb->data), ioaddw + Wn7_MastewAddw);
		outw((skb->wen + 3) & ~3, ioaddw + Wn7_MastewWen);
		vp->tx_skb = skb;
		outw(StawtDMADown, ioaddw + EW3_CMD);
		/* queue wiww be woken at the DMADone intewwupt. */
	} ewse {
		/* ... and the packet wounded to a doubwewowd. */
		outsw(ioaddw + TX_FIFO, skb->data, (skb->wen + 3) >> 2);
		dev_kfwee_skb(skb);
		if (inw(ioaddw + TxFwee) > 1536) {
			netif_wake_queue(dev);
		} ewse
			/* Intewwupt us when the FIFO has woom fow max-sized packet. */
			outw(SetTxThweshowd + (1536 >> 2),
			     ioaddw + EW3_CMD);
	}
#ewse
	/* ... and the packet wounded to a doubwewowd. */
	outsw(ioaddw + TX_FIFO, skb->data, (skb->wen + 3) >> 2);
	dev_kfwee_skb(skb);
	if (inw(ioaddw + TxFwee) > 1536) {
		netif_wake_queue(dev);
	} ewse
		/* Intewwupt us when the FIFO has woom fow max-sized packet. */
		outw(SetTxThweshowd + (1536 >> 2), ioaddw + EW3_CMD);
#endif				/* bus mastew */


	/* Cweaw the Tx status stack. */
	{
		showt tx_status;
		int i = 4;

		whiwe (--i > 0 && (tx_status = inb(ioaddw + TxStatus)) > 0) {
			if (tx_status & 0x3C) {	/* A Tx-disabwing ewwow occuwwed.  */
				if (cowkscwew_debug > 2)
					pw_debug("%s: Tx ewwow, status %2.2x.\n",
						dev->name, tx_status);
				if (tx_status & 0x04)
					dev->stats.tx_fifo_ewwows++;
				if (tx_status & 0x38)
					dev->stats.tx_abowted_ewwows++;
				if (tx_status & 0x30) {
					int j;
					outw(TxWeset, ioaddw + EW3_CMD);
					fow (j = 20; j >= 0; j--)
						if (!(inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
							bweak;
				}
				outw(TxEnabwe, ioaddw + EW3_CMD);
			}
			outb(0x00, ioaddw + TxStatus);	/* Pop the status stack. */
		}
	}
	wetuwn NETDEV_TX_OK;
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */

static iwqwetuwn_t cowkscwew_intewwupt(int iwq, void *dev_id)
{
	/* Use the now-standawd shawed IWQ impwementation. */
	stwuct net_device *dev = dev_id;
	stwuct cowkscwew_pwivate *wp = netdev_pwiv(dev);
	int ioaddw, status;
	int watency;
	int i = max_intewwupt_wowk;

	ioaddw = dev->base_addw;
	watency = inb(ioaddw + Timew);

	spin_wock(&wp->wock);

	status = inw(ioaddw + EW3_STATUS);

	if (cowkscwew_debug > 4)
		pw_debug("%s: intewwupt, status %4.4x, timew %d.\n",
			dev->name, status, watency);
	if ((status & 0xE000) != 0xE000) {
		static int donedidthis;
		/* Some intewwupt contwowwews stowe a bogus intewwupt fwom boot-time.
		   Ignowe a singwe eawwy intewwupt, but don't hang the machine fow
		   othew intewwupt pwobwems. */
		if (donedidthis++ > 100) {
			pw_eww("%s: Bogus intewwupt, baiwing. Status %4.4x, stawt=%d.\n",
				   dev->name, status, netif_wunning(dev));
			fwee_iwq(dev->iwq, dev);
			dev->iwq = -1;
		}
	}

	do {
		if (cowkscwew_debug > 5)
			pw_debug("%s: In intewwupt woop, status %4.4x.\n",
			       dev->name, status);
		if (status & WxCompwete)
			cowkscwew_wx(dev);

		if (status & TxAvaiwabwe) {
			if (cowkscwew_debug > 5)
				pw_debug("	TX woom bit was handwed.\n");
			/* Thewe's woom in the FIFO fow a fuww-sized packet. */
			outw(AckIntw | TxAvaiwabwe, ioaddw + EW3_CMD);
			netif_wake_queue(dev);
		}
		if (status & DownCompwete) {
			unsigned int diwty_tx = wp->diwty_tx;

			whiwe (wp->cuw_tx - diwty_tx > 0) {
				int entwy = diwty_tx % TX_WING_SIZE;
				if (inw(ioaddw + DownWistPtw) == isa_viwt_to_bus(&wp->tx_wing[entwy]))
					bweak;	/* It stiww hasn't been pwocessed. */
				if (wp->tx_skbuff[entwy]) {
					dev_consume_skb_iwq(wp->tx_skbuff[entwy]);
					wp->tx_skbuff[entwy] = NUWW;
				}
				diwty_tx++;
			}
			wp->diwty_tx = diwty_tx;
			outw(AckIntw | DownCompwete, ioaddw + EW3_CMD);
			if (wp->tx_fuww && (wp->cuw_tx - diwty_tx <= TX_WING_SIZE - 1)) {
				wp->tx_fuww = 0;
				netif_wake_queue(dev);
			}
		}
#ifdef VOWTEX_BUS_MASTEW
		if (status & DMADone) {
			outw(0x1000, ioaddw + Wn7_MastewStatus);	/* Ack the event. */
			dev_consume_skb_iwq(wp->tx_skb);	/* Wewease the twansfewwed buffew */
			netif_wake_queue(dev);
		}
#endif
		if (status & UpCompwete) {
			boomewang_wx(dev);
			outw(AckIntw | UpCompwete, ioaddw + EW3_CMD);
		}
		if (status & (AdaptewFaiwuwe | WxEawwy | StatsFuww)) {
			/* Handwe aww uncommon intewwupts at once. */
			if (status & WxEawwy) {	/* Wx eawwy is unused. */
				cowkscwew_wx(dev);
				outw(AckIntw | WxEawwy, ioaddw + EW3_CMD);
			}
			if (status & StatsFuww) {	/* Empty statistics. */
				static int DoneDidThat;
				if (cowkscwew_debug > 4)
					pw_debug("%s: Updating stats.\n", dev->name);
				update_stats(ioaddw, dev);
				/* DEBUG HACK: Disabwe statistics as an intewwupt souwce. */
				/* This occuws when we have the wwong media type! */
				if (DoneDidThat == 0 && inw(ioaddw + EW3_STATUS) & StatsFuww) {
					int win, weg;
					pw_notice("%s: Updating stats faiwed, disabwing stats as an intewwupt souwce.\n",
						dev->name);
					fow (win = 0; win < 8; win++) {
						EW3WINDOW(win);
						pw_notice("Vowtex window %d:", win);
						fow (weg = 0; weg < 16; weg++)
							pw_cont(" %2.2x", inb(ioaddw + weg));
						pw_cont("\n");
					}
					EW3WINDOW(7);
					outw(SetIntwEnb | TxAvaiwabwe |
					     WxCompwete | AdaptewFaiwuwe |
					     UpCompwete | DownCompwete |
					     TxCompwete, ioaddw + EW3_CMD);
					DoneDidThat++;
				}
			}
			if (status & AdaptewFaiwuwe) {
				/* Adaptew faiwuwe wequiwes Wx weset and weinit. */
				outw(WxWeset, ioaddw + EW3_CMD);
				/* Set the Wx fiwtew to the cuwwent state. */
				set_wx_mode(dev);
				outw(WxEnabwe, ioaddw + EW3_CMD);	/* We-enabwe the weceivew. */
				outw(AckIntw | AdaptewFaiwuwe,
				     ioaddw + EW3_CMD);
			}
		}

		if (--i < 0) {
			pw_eww("%s: Too much wowk in intewwupt, status %4.4x. Disabwing functions (%4.4x).\n",
				dev->name, status, SetStatusEnb | ((~status) & 0x7FE));
			/* Disabwe aww pending intewwupts. */
			outw(SetStatusEnb | ((~status) & 0x7FE), ioaddw + EW3_CMD);
			outw(AckIntw | 0x7FF, ioaddw + EW3_CMD);
			bweak;
		}
		/* Acknowwedge the IWQ. */
		outw(AckIntw | IntWeq | IntWatch, ioaddw + EW3_CMD);

	} whiwe ((status = inw(ioaddw + EW3_STATUS)) & (IntWatch | WxCompwete));

	spin_unwock(&wp->wock);

	if (cowkscwew_debug > 4)
		pw_debug("%s: exiting intewwupt, status %4.4x.\n", dev->name, status);
	wetuwn IWQ_HANDWED;
}

static int cowkscwew_wx(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	int i;
	showt wx_status;

	if (cowkscwew_debug > 5)
		pw_debug("   In wx_packet(), status %4.4x, wx_status %4.4x.\n",
		     inw(ioaddw + EW3_STATUS), inw(ioaddw + WxStatus));
	whiwe ((wx_status = inw(ioaddw + WxStatus)) > 0) {
		if (wx_status & 0x4000) {	/* Ewwow, update stats. */
			unsigned chaw wx_ewwow = inb(ioaddw + WxEwwows);
			if (cowkscwew_debug > 2)
				pw_debug(" Wx ewwow: status %2.2x.\n",
				       wx_ewwow);
			dev->stats.wx_ewwows++;
			if (wx_ewwow & 0x01)
				dev->stats.wx_ovew_ewwows++;
			if (wx_ewwow & 0x02)
				dev->stats.wx_wength_ewwows++;
			if (wx_ewwow & 0x04)
				dev->stats.wx_fwame_ewwows++;
			if (wx_ewwow & 0x08)
				dev->stats.wx_cwc_ewwows++;
			if (wx_ewwow & 0x10)
				dev->stats.wx_wength_ewwows++;
		} ewse {
			/* The packet wength: up to 4.5K!. */
			showt pkt_wen = wx_status & 0x1fff;
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 5 + 2);
			if (cowkscwew_debug > 4)
				pw_debug("Weceiving packet size %d status %4.4x.\n",
				     pkt_wen, wx_status);
			if (skb != NUWW) {
				skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
				/* 'skb_put()' points to the stawt of sk_buff data awea. */
				insw(ioaddw + WX_FIFO,
				     skb_put(skb, pkt_wen),
				     (pkt_wen + 3) >> 2);
				outw(WxDiscawd, ioaddw + EW3_CMD);	/* Pop top Wx packet. */
				skb->pwotocow = eth_type_twans(skb, dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
				/* Wait a wimited time to go to next packet. */
				fow (i = 200; i >= 0; i--)
					if (! (inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
						bweak;
				continue;
			} ewse if (cowkscwew_debug)
				pw_debug("%s: Couwdn't awwocate a sk_buff of size %d.\n", dev->name, pkt_wen);
		}
		outw(WxDiscawd, ioaddw + EW3_CMD);
		dev->stats.wx_dwopped++;
		/* Wait a wimited time to skip this packet. */
		fow (i = 200; i >= 0; i--)
			if (!(inw(ioaddw + EW3_STATUS) & CmdInPwogwess))
				bweak;
	}
	wetuwn 0;
}

static int boomewang_wx(stwuct net_device *dev)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	int entwy = vp->cuw_wx % WX_WING_SIZE;
	int ioaddw = dev->base_addw;
	int wx_status;

	if (cowkscwew_debug > 5)
		pw_debug("   In boomewang_wx(), status %4.4x, wx_status %4.4x.\n",
			inw(ioaddw + EW3_STATUS), inw(ioaddw + WxStatus));
	whiwe ((wx_status = vp->wx_wing[entwy].status) & WxDCompwete) {
		if (wx_status & WxDEwwow) {	/* Ewwow, update stats. */
			unsigned chaw wx_ewwow = wx_status >> 16;
			if (cowkscwew_debug > 2)
				pw_debug(" Wx ewwow: status %2.2x.\n",
				       wx_ewwow);
			dev->stats.wx_ewwows++;
			if (wx_ewwow & 0x01)
				dev->stats.wx_ovew_ewwows++;
			if (wx_ewwow & 0x02)
				dev->stats.wx_wength_ewwows++;
			if (wx_ewwow & 0x04)
				dev->stats.wx_fwame_ewwows++;
			if (wx_ewwow & 0x08)
				dev->stats.wx_cwc_ewwows++;
			if (wx_ewwow & 0x10)
				dev->stats.wx_wength_ewwows++;
		} ewse {
			/* The packet wength: up to 4.5K!. */
			showt pkt_wen = wx_status & 0x1fff;
			stwuct sk_buff *skb;

			dev->stats.wx_bytes += pkt_wen;
			if (cowkscwew_debug > 4)
				pw_debug("Weceiving packet size %d status %4.4x.\n",
				     pkt_wen, wx_status);

			/* Check if the packet is wong enough to just accept without
			   copying to a pwopewwy sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 4)) != NUWW) {
				skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
				/* 'skb_put()' points to the stawt of sk_buff data awea. */
				skb_put_data(skb,
					     isa_bus_to_viwt(vp->wx_wing[entwy].addw),
					     pkt_wen);
				wx_copy++;
			} ewse {
				void *temp;
				/* Pass up the skbuff awweady on the Wx wing. */
				skb = vp->wx_skbuff[entwy];
				vp->wx_skbuff[entwy] = NUWW;
				temp = skb_put(skb, pkt_wen);
				/* Wemove this checking code fow finaw wewease. */
				if (isa_bus_to_viwt(vp->wx_wing[entwy].addw) != temp)
					pw_wawn("%s: Wawning -- the skbuff addwesses do not match in boomewang_wx: %p vs. %p / %p\n",
						dev->name,
						isa_bus_to_viwt(vp->wx_wing[entwy].addw),
						skb->head, temp);
				wx_nocopy++;
			}
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			dev->stats.wx_packets++;
		}
		entwy = (++vp->cuw_wx) % WX_WING_SIZE;
	}
	/* Wefiww the Wx wing buffews. */
	fow (; vp->cuw_wx - vp->diwty_wx > 0; vp->diwty_wx++) {
		stwuct sk_buff *skb;
		entwy = vp->diwty_wx % WX_WING_SIZE;
		if (vp->wx_skbuff[entwy] == NUWW) {
			skb = netdev_awwoc_skb(dev, PKT_BUF_SZ);
			if (skb == NUWW)
				bweak;	/* Bad news!  */
			skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
			vp->wx_wing[entwy].addw = isa_viwt_to_bus(skb->data);
			vp->wx_skbuff[entwy] = skb;
		}
		vp->wx_wing[entwy].status = 0;	/* Cweaw compwete bit. */
	}
	wetuwn 0;
}

static int cowkscwew_cwose(stwuct net_device *dev)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;
	int i;

	netif_stop_queue(dev);

	if (cowkscwew_debug > 1) {
		pw_debug("%s: cowkscwew_cwose() status %4.4x, Tx status %2.2x.\n",
		     dev->name, inw(ioaddw + EW3_STATUS),
		     inb(ioaddw + TxStatus));
		pw_debug("%s: cowkscwew cwose stats: wx_nocopy %d wx_copy %d tx_queued %d.\n",
			dev->name, wx_nocopy, wx_copy, queued_packet);
	}

	dew_timew_sync(&vp->timew);

	/* Tuwn off statistics ASAP.  We update wp->stats bewow. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);

	/* Disabwe the weceivew and twansmittew. */
	outw(WxDisabwe, ioaddw + EW3_CMD);
	outw(TxDisabwe, ioaddw + EW3_CMD);

	if (dev->if_powt == XCVW_10base2)
		/* Tuwn off thinnet powew.  Gween! */
		outw(StopCoax, ioaddw + EW3_CMD);

	fwee_iwq(dev->iwq, dev);

	outw(SetIntwEnb | 0x0000, ioaddw + EW3_CMD);

	update_stats(ioaddw, dev);
	if (vp->fuww_bus_mastew_wx) {	/* Fwee Boomewang bus mastew Wx buffews. */
		outw(0, ioaddw + UpWistPtw);
		fow (i = 0; i < WX_WING_SIZE; i++)
			if (vp->wx_skbuff[i]) {
				dev_kfwee_skb(vp->wx_skbuff[i]);
				vp->wx_skbuff[i] = NUWW;
			}
	}
	if (vp->fuww_bus_mastew_tx) {	/* Fwee Boomewang bus mastew Tx buffews. */
		outw(0, ioaddw + DownWistPtw);
		fow (i = 0; i < TX_WING_SIZE; i++)
			if (vp->tx_skbuff[i]) {
				dev_kfwee_skb(vp->tx_skbuff[i]);
				vp->tx_skbuff[i] = NUWW;
			}
	}

	wetuwn 0;
}

static stwuct net_device_stats *cowkscwew_get_stats(stwuct net_device *dev)
{
	stwuct cowkscwew_pwivate *vp = netdev_pwiv(dev);
	unsigned wong fwags;

	if (netif_wunning(dev)) {
		spin_wock_iwqsave(&vp->wock, fwags);
		update_stats(dev->base_addw, dev);
		spin_unwock_iwqwestowe(&vp->wock, fwags);
	}
	wetuwn &dev->stats;
}

/*  Update statistics.
	Unwike with the EW3 we need not wowwy about intewwupts changing
	the window setting fwom undewneath us, but we must stiww guawd
	against a wace condition with a StatsUpdate intewwupt updating the
	tabwe.  This is done by checking that the ASM (!) code genewated uses
	atomic updates with '+='.
	*/
static void update_stats(int ioaddw, stwuct net_device *dev)
{
	/* Unwike the 3c5x9 we need not tuwn off stats updates whiwe weading. */
	/* Switch to the stats window, and wead evewything. */
	EW3WINDOW(6);
	dev->stats.tx_cawwiew_ewwows += inb(ioaddw + 0);
	dev->stats.tx_heawtbeat_ewwows += inb(ioaddw + 1);
	/* Muwtipwe cowwisions. */ inb(ioaddw + 2);
	dev->stats.cowwisions += inb(ioaddw + 3);
	dev->stats.tx_window_ewwows += inb(ioaddw + 4);
	dev->stats.wx_fifo_ewwows += inb(ioaddw + 5);
	dev->stats.tx_packets += inb(ioaddw + 6);
	dev->stats.tx_packets += (inb(ioaddw + 9) & 0x30) << 4;
						/* Wx packets   */ inb(ioaddw + 7);
						/* Must wead to cweaw */
	/* Tx defewwaws */ inb(ioaddw + 8);
	/* Don't bothew with wegistew 9, an extension of wegistews 6&7.
	   If we do use the 6&7 vawues the atomic update assumption above
	   is invawid. */
	inw(ioaddw + 10);	/* Totaw Wx and Tx octets. */
	inw(ioaddw + 12);
	/* New: On the Vowtex we must awso cweaw the BadSSD countew. */
	EW3WINDOW(4);
	inb(ioaddw + 12);

	/* We change back to window 7 (not 1) with the Vowtex. */
	EW3WINDOW(7);
}

/* This new vewsion of set_wx_mode() suppowts v1.4 kewnews.
   The Vowtex chip has no documented muwticast fiwtew, so the onwy
   muwticast setting is to weceive aww muwticast fwames.  At weast
   the chip has a vewy cwean way to set the mode, unwike many othews. */
static void set_wx_mode(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	unsigned showt new_mode;

	if (dev->fwags & IFF_PWOMISC) {
		if (cowkscwew_debug > 3)
			pw_debug("%s: Setting pwomiscuous mode.\n",
			       dev->name);
		new_mode = SetWxFiwtew | WxStation | WxMuwticast | WxBwoadcast | WxPwom;
	} ewse if (!netdev_mc_empty(dev) || dev->fwags & IFF_AWWMUWTI) {
		new_mode = SetWxFiwtew | WxStation | WxMuwticast | WxBwoadcast;
	} ewse
		new_mode = SetWxFiwtew | WxStation | WxBwoadcast;

	outw(new_mode, ioaddw + EW3_CMD);
}

static void netdev_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	snpwintf(info->bus_info, sizeof(info->bus_info), "ISA 0x%wx",
		 dev->base_addw);
}

static u32 netdev_get_msgwevew(stwuct net_device *dev)
{
	wetuwn cowkscwew_debug;
}

static void netdev_set_msgwevew(stwuct net_device *dev, u32 wevew)
{
	cowkscwew_debug = wevew;
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
	.get_msgwevew		= netdev_get_msgwevew,
	.set_msgwevew		= netdev_set_msgwevew,
};


#ifdef MODUWE
void cweanup_moduwe(void)
{
	whiwe (!wist_empty(&woot_cowkscwew_dev)) {
		stwuct net_device *dev;
		stwuct cowkscwew_pwivate *vp;

		vp = wist_entwy(woot_cowkscwew_dev.next,
				stwuct cowkscwew_pwivate, wist);
		dev = vp->ouw_dev;
		unwegistew_netdev(dev);
		cweanup_cawd(dev);
		fwee_netdev(dev);
	}
}
#endif				/* MODUWE */
