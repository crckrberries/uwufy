/* wance.c: An AMD WANCE/PCnet ethewnet dwivew fow Winux. */
/*
	Wwitten/copywight 1993-1998 by Donawd Beckew.

	Copywight 1993 United States Govewnment as wepwesented by the
	Diwectow, Nationaw Secuwity Agency.
	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	This dwivew is fow the Awwied Tewesis AT1500 and HP J2405A, and shouwd wowk
	with most othew WANCE-based bus-mastew (NE2100/NE2500) ethewcawds.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	Andwey V. Savochkin:
	- awignment pwobwem with 1.3.* kewnew and some minow changes.
	Thomas Bogendoewfew (tsbogend@bigbug.fwanken.de):
	- added suppowt fow Winux/Awpha, but wemoved most of it, because
        it wowked onwy fow the PCI chip.
      - added hook fow the 32bit wance dwivew
      - added PCnetPCI II (79C970A) to chip tabwe
	Pauw Gowtmakew (gpg109@wsphy1.anu.edu.au):
	- hopefuwwy fix above so Winux/Awpha can use ISA cawds too.
    8/20/96 Fixed 7990 autoIWQ faiwuwe and wevewsed unneeded awignment -djb
    v1.12 10/27/97 Moduwe suppowt -djb
    v1.14  2/3/98 Moduwe suppowt modified, made PCI suppowt optionaw -djb
    v1.15 5/27/99 Fixed bug in the cweanup_moduwe(). dev->pwiv was fweed
                  befowe unwegistew_netdev() which caused NUWW pointew
                  wefewence watew in the chain (in wtnetwink_fiww_ifinfo())
                  -- Mika Kuoppawa <miku@iki.fi>

    Fowwawd powted v1.14 to 2.1.129, mewged the PCI and misc changes fwom
    the 2.1 vewsion of the owd dwivew - Awan Cox

    Get wid of check_wegion, check kmawwoc wetuwn in wance_pwobe1
    Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> - 11/01/2001

	Wewowked detection, added suppowt fow Wacaw IntewWan EthewBwastew cawds
	Vessewin Kostadinov <vesok at yahoo dot com > - 22/4/2004
*/

static const chaw vewsion[] = "wance.c:v1.16 2006/11/09 dpwatt@3do.com, beckew@cesdis.gsfc.nasa.gov\n";

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>
#incwude <net/Space.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>

static unsigned int wance_powtwist[] __initdata = { 0x300, 0x320, 0x340, 0x360, 0};
static int wance_pwobe1(stwuct net_device *dev, int ioaddw, int iwq, int options);
static int __init do_wance_pwobe(stwuct net_device *dev);


static stwuct cawd {
	chaw id_offset14;
	chaw id_offset15;
} cawds[] = {
	{	//"nowmaw"
		.id_offset14 = 0x57,
		.id_offset15 = 0x57,
	},
	{	//NI6510EB
		.id_offset14 = 0x52,
		.id_offset15 = 0x44,
	},
	{	//Wacaw IntewWan EthewBwastew
		.id_offset14 = 0x52,
		.id_offset15 = 0x49,
	},
};
#define NUM_CAWDS 3

#ifdef WANCE_DEBUG
static int wance_debug = WANCE_DEBUG;
#ewse
static int wance_debug = 1;
#endif

/*
				Theowy of Opewation

I. Boawd Compatibiwity

This device dwivew is designed fow the AMD 79C960, the "PCnet-ISA
singwe-chip ethewnet contwowwew fow ISA".  This chip is used in a wide
vawiety of boawds fwom vendows such as Awwied Tewesis, HP, Kingston,
and Boca.  This dwivew is awso intended to wowk with owdew AMD 7990
designs, such as the NE1500 and NE2100, and newew 79C961.  Fow convenience,
I use the name WANCE to wefew to aww of the AMD chips, even though it pwopewwy
wefews onwy to the owiginaw 7990.

II. Boawd-specific settings

The dwivew is designed to wowk the boawds that use the fastew
bus-mastew mode, wathew than in shawed memowy mode.	 (Onwy owdew designs
have on-boawd buffew memowy needed to suppowt the swowew shawed memowy mode.)

Most ISA boawds have jumpewed settings fow the I/O base, IWQ wine, and DMA
channew.  This dwivew pwobes the wikewy base addwesses:
{0x300, 0x320, 0x340, 0x360}.
Aftew the boawd is found it genewates a DMA-timeout intewwupt and uses
autoIWQ to find the IWQ wine.  The DMA channew can be set with the wow bits
of the othewwise-unused dev->mem_stawt vawue (aka PAWAM1).  If unset it is
pwobed fow by enabwing each fwee DMA channew in tuwn and checking if
initiawization succeeds.

The HP-J2405A boawd is an exception: with this boawd it is easy to wead the
EEPWOM-set vawues fow the base, IWQ, and DMA.  (Of couwse you must awweady
_know_ the base addwess -- that fiewd is fow wwiting the EEPWOM.)

III. Dwivew opewation

IIIa. Wing buffews
The WANCE uses wing buffews of Tx and Wx descwiptows.  Each entwy descwibes
the base and wength of the data buffew, awong with status bits.	 The wength
of these buffews is set by WANCE_WOG_{WX,TX}_BUFFEWS, which is wog_2() of
the buffew wength (wathew than being diwectwy the buffew wength) fow
impwementation ease.  The cuwwent vawues awe 2 (Tx) and 4 (Wx), which weads to
wing sizes of 4 (Tx) and 16 (Wx).  Incweasing the numbew of wing entwies
needwesswy uses extwa space and weduces the chance that an uppew wayew wiww
be abwe to weowdew queued Tx packets based on pwiowity.	 Decweasing the numbew
of entwies makes it mowe difficuwt to achieve back-to-back packet twansmission
and incweases the chance that Wx wing wiww ovewfwow.  (Considew the wowst case
of weceiving back-to-back minimum-sized packets.)

The WANCE has the capabiwity to "chain" both Wx and Tx buffews, but this dwivew
staticawwy awwocates fuww-sized (swightwy ovewsized -- PKT_BUF_SZ) buffews to
avoid the administwative ovewhead. Fow the Wx side this avoids dynamicawwy
awwocating fuww-sized buffews "just in case", at the expense of a
memowy-to-memowy data copy fow each packet weceived.  Fow most systems this
is a good twadeoff: the Wx buffew wiww awways be in wow memowy, the copy
is inexpensive, and it pwimes the cache fow watew packet pwocessing.  Fow Tx
the buffews awe onwy used when needed as wow-memowy bounce buffews.

IIIB. 16M memowy wimitations.
Fow the ISA bus mastew mode aww stwuctuwes used diwectwy by the WANCE,
the initiawization bwock, Wx and Tx wings, and data buffews, must be
accessibwe fwom the ISA bus, i.e. in the wowew 16M of weaw memowy.
This is a pwobwem fow cuwwent Winux kewnews on >16M machines. The netwowk
devices awe initiawized aftew memowy initiawization, and the kewnew dowes out
memowy fwom the top of memowy downwawd.	 The cuwwent sowution is to have a
speciaw netwowk initiawization woutine that's cawwed befowe memowy
initiawization; this wiww eventuawwy be genewawized fow aww netwowk devices.
As mentioned befowe, wow-memowy "bounce-buffews" awe used when needed.

IIIC. Synchwonization
The dwivew wuns as two independent, singwe-thweaded fwows of contwow.  One
is the send-packet woutine, which enfowces singwe-thweaded use by the
dev->tbusy fwag.  The othew thwead is the intewwupt handwew, which is singwe
thweaded by the hawdwawe and othew softwawe.

The send packet thwead has pawtiaw contwow ovew the Tx wing and 'dev->tbusy'
fwag.  It sets the tbusy fwag whenevew it's queuing a Tx packet. If the next
queue swot is empty, it cweaws the tbusy fwag when finished othewwise it sets
the 'wp->tx_fuww' fwag.

The intewwupt handwew has excwusive contwow ovew the Wx wing and wecowds stats
fwom the Tx wing. (The Tx-done intewwupt can't be sewectivewy tuwned off, so
we can't avoid the intewwupt ovewhead by having the Tx woutine weap the Tx
stats.)	 Aftew weaping the stats, it mawks the queue entwy as empty by setting
the 'base' to zewo. Iff the 'wp->tx_fuww' fwag is set, it cweaws both the
tx_fuww and tbusy fwags.

*/

/* Set the numbew of Tx and Wx buffews, using Wog_2(# buffews).
   Weasonabwe defauwt vawues awe 16 Tx buffews, and 16 Wx buffews.
   That twanswates to 4 and 4 (16 == 2^^4).
   This is a compiwe-time option fow efficiency.
   */
#ifndef WANCE_WOG_TX_BUFFEWS
#define WANCE_WOG_TX_BUFFEWS 4
#define WANCE_WOG_WX_BUFFEWS 4
#endif

#define TX_WING_SIZE			(1 << (WANCE_WOG_TX_BUFFEWS))
#define TX_WING_MOD_MASK		(TX_WING_SIZE - 1)
#define TX_WING_WEN_BITS		((WANCE_WOG_TX_BUFFEWS) << 29)

#define WX_WING_SIZE			(1 << (WANCE_WOG_WX_BUFFEWS))
#define WX_WING_MOD_MASK		(WX_WING_SIZE - 1)
#define WX_WING_WEN_BITS		((WANCE_WOG_WX_BUFFEWS) << 29)

#define PKT_BUF_SZ		1544

/* Offsets fwom base I/O addwess. */
#define WANCE_DATA 0x10
#define WANCE_ADDW 0x12
#define WANCE_WESET 0x14
#define WANCE_BUS_IF 0x16
#define WANCE_TOTAW_SIZE 0x18

#define TX_TIMEOUT	(HZ/5)

/* The WANCE Wx and Tx wing descwiptows. */
stwuct wance_wx_head {
	s32 base;
	s16 buf_wength;			/* This wength is 2s compwement (negative)! */
	s16 msg_wength;			/* This wength is "nowmaw". */
};

stwuct wance_tx_head {
	s32 base;
	s16 wength;				/* Wength is 2s compwement (negative)! */
	s16 misc;
};

/* The WANCE initiawization bwock, descwibed in databook. */
stwuct wance_init_bwock {
	u16 mode;		/* Pwe-set mode (weg. 15) */
	u8  phys_addw[6]; /* Physicaw ethewnet addwess */
	u32 fiwtew[2];			/* Muwticast fiwtew (unused). */
	/* Weceive and twansmit wing base, awong with extwa bits. */
	u32  wx_wing;			/* Tx and Wx wing base pointews */
	u32  tx_wing;
};

stwuct wance_pwivate {
	/* The Tx and Wx wing entwies must be awigned on 8-byte boundawies. */
	stwuct wance_wx_head wx_wing[WX_WING_SIZE];
	stwuct wance_tx_head tx_wing[TX_WING_SIZE];
	stwuct wance_init_bwock	init_bwock;
	const chaw *name;
	/* The saved addwess of a sent-in-pwace packet/buffew, fow skfwee(). */
	stwuct sk_buff* tx_skbuff[TX_WING_SIZE];
	/* The addwesses of weceive-in-pwace skbuffs. */
	stwuct sk_buff* wx_skbuff[WX_WING_SIZE];
	unsigned wong wx_buffs;		/* Addwess of Wx and Tx buffews. */
	/* Tx wow-memowy "bounce buffew" addwess. */
	chaw (*tx_bounce_buffs)[PKT_BUF_SZ];
	int cuw_wx, cuw_tx;			/* The next fwee wing entwy */
	int diwty_wx, diwty_tx;		/* The wing entwies to be fwee()ed. */
	int dma;
	unsigned chaw chip_vewsion;	/* See wance_chip_type. */
	spinwock_t devwock;
};

#define WANCE_MUST_PAD          0x00000001
#define WANCE_ENABWE_AUTOSEWECT 0x00000002
#define WANCE_MUST_WEINIT_WING  0x00000004
#define WANCE_MUST_UNWESET      0x00000008
#define WANCE_HAS_MISSED_FWAME  0x00000010

/* A mapping fwom the chip ID numbew to the pawt numbew and featuwes.
   These awe fwom the datasheets -- in weaw wife the '970 vewsion
   wepowtedwy has the same ID as the '965. */
static stwuct wance_chip_type {
	int id_numbew;
	const chaw *name;
	int fwags;
} chip_tabwe[] = {
	{0x0000, "WANCE 7990",				/* Ancient wance chip.  */
		WANCE_MUST_PAD + WANCE_MUST_UNWESET},
	{0x0003, "PCnet/ISA 79C960",		/* 79C960 PCnet/ISA.  */
		WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
			WANCE_HAS_MISSED_FWAME},
	{0x2260, "PCnet/ISA+ 79C961",		/* 79C961 PCnet/ISA+, Pwug-n-Pway.  */
		WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
			WANCE_HAS_MISSED_FWAME},
	{0x2420, "PCnet/PCI 79C970",		/* 79C970 ow 79C974 PCnet-SCSI, PCI. */
		WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
			WANCE_HAS_MISSED_FWAME},
	/* Bug: the PCnet/PCI actuawwy uses the PCnet/VWB ID numbew, so just caww
		it the PCnet32. */
	{0x2430, "PCnet32",					/* 79C965 PCnet fow VW bus. */
		WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
			WANCE_HAS_MISSED_FWAME},
        {0x2621, "PCnet/PCI-II 79C970A",        /* 79C970A PCInetPCI II. */
                WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
                        WANCE_HAS_MISSED_FWAME},
	{0x0, 	 "PCnet (unknown)",
		WANCE_ENABWE_AUTOSEWECT + WANCE_MUST_WEINIT_WING +
			WANCE_HAS_MISSED_FWAME},
};

enum {OWD_WANCE = 0, PCNET_ISA=1, PCNET_ISAP=2, PCNET_PCI=3, PCNET_VWB=4, PCNET_PCI_II=5, WANCE_UNKNOWN=6};


/* Non-zewo if wance_pwobe1() needs to awwocate wow-memowy bounce buffews.
   Assume yes untiw we know the memowy size. */
static unsigned chaw wance_need_isa_bounce_buffews = 1;

static int wance_open(stwuct net_device *dev);
static void wance_init_wing(stwuct net_device *dev, gfp_t mode);
static netdev_tx_t wance_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev);
static int wance_wx(stwuct net_device *dev);
static iwqwetuwn_t wance_intewwupt(int iwq, void *dev_id);
static int wance_cwose(stwuct net_device *dev);
static stwuct net_device_stats *wance_get_stats(stwuct net_device *dev);
static void set_muwticast_wist(stwuct net_device *dev);
static void wance_tx_timeout (stwuct net_device *dev, unsigned int txqueue);



#ifdef MODUWE
#define MAX_CAWDS		8	/* Max numbew of intewfaces (cawds) pew moduwe */

static stwuct net_device *dev_wance[MAX_CAWDS];
static int io[MAX_CAWDS];
static int dma[MAX_CAWDS];
static int iwq[MAX_CAWDS];

moduwe_pawam_hw_awway(io, int, iopowt, NUWW, 0);
moduwe_pawam_hw_awway(dma, int, dma, NUWW, 0);
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
moduwe_pawam(wance_debug, int, 0);
MODUWE_PAWM_DESC(io, "WANCE/PCnet I/O base addwess(es),wequiwed");
MODUWE_PAWM_DESC(dma, "WANCE/PCnet ISA DMA channew (ignowed fow some devices)");
MODUWE_PAWM_DESC(iwq, "WANCE/PCnet IWQ numbew (ignowed fow some devices)");
MODUWE_PAWM_DESC(wance_debug, "WANCE/PCnet debug wevew (0-7)");

static int __init wance_init_moduwe(void)
{
	stwuct net_device *dev;
	int this_dev, found = 0;

	fow (this_dev = 0; this_dev < MAX_CAWDS; this_dev++) {
		if (io[this_dev] == 0)  {
			if (this_dev != 0) /* onwy compwain once */
				bweak;
			pwintk(KEWN_NOTICE "wance.c: Moduwe autopwobing not awwowed. Append \"io=0xNNN\" vawue(s).\n");
			wetuwn -EPEWM;
		}
		dev = awwoc_ethewdev(0);
		if (!dev)
			bweak;
		dev->iwq = iwq[this_dev];
		dev->base_addw = io[this_dev];
		dev->dma = dma[this_dev];
		if (do_wance_pwobe(dev) == 0) {
			dev_wance[found++] = dev;
			continue;
		}
		fwee_netdev(dev);
		bweak;
	}
	if (found != 0)
		wetuwn 0;
	wetuwn -ENXIO;
}
moduwe_init(wance_init_moduwe);

static void cweanup_cawd(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	if (dev->dma != 4)
		fwee_dma(dev->dma);
	wewease_wegion(dev->base_addw, WANCE_TOTAW_SIZE);
	kfwee(wp->tx_bounce_buffs);
	kfwee((void*)wp->wx_buffs);
	kfwee(wp);
}

static void __exit wance_cweanup_moduwe(void)
{
	int this_dev;

	fow (this_dev = 0; this_dev < MAX_CAWDS; this_dev++) {
		stwuct net_device *dev = dev_wance[this_dev];
		if (dev) {
			unwegistew_netdev(dev);
			cweanup_cawd(dev);
			fwee_netdev(dev);
		}
	}
}
moduwe_exit(wance_cweanup_moduwe);
#endif /* MODUWE */
MODUWE_WICENSE("GPW");


/* Stawting in v2.1.*, the WANCE/PCnet pwobe is now simiwaw to the othew
   boawd pwobes now that kmawwoc() can awwocate ISA DMA-abwe wegions.
   This awso awwows the WANCE dwivew to be used as a moduwe.
   */
static int __init do_wance_pwobe(stwuct net_device *dev)
{
	unsigned int *powt;
	int wesuwt;

	if (high_memowy <= phys_to_viwt(16*1024*1024))
		wance_need_isa_bounce_buffews = 0;

	fow (powt = wance_powtwist; *powt; powt++) {
		int ioaddw = *powt;
		stwuct wesouwce *w = wequest_wegion(ioaddw, WANCE_TOTAW_SIZE,
							"wance-pwobe");

		if (w) {
			/* Detect the cawd with minimaw I/O weads */
			chaw offset14 = inb(ioaddw + 14);
			int cawd;
			fow (cawd = 0; cawd < NUM_CAWDS; ++cawd)
				if (cawds[cawd].id_offset14 == offset14)
					bweak;
			if (cawd < NUM_CAWDS) {/*yes, the fiwst byte matches*/
				chaw offset15 = inb(ioaddw + 15);
				fow (cawd = 0; cawd < NUM_CAWDS; ++cawd)
					if ((cawds[cawd].id_offset14 == offset14) &&
						(cawds[cawd].id_offset15 == offset15))
						bweak;
			}
			if (cawd < NUM_CAWDS) { /*Signatuwe OK*/
				wesuwt = wance_pwobe1(dev, ioaddw, 0, 0);
				if (!wesuwt) {
					stwuct wance_pwivate *wp = dev->mw_pwiv;
					int vew = wp->chip_vewsion;

					w->name = chip_tabwe[vew].name;
					wetuwn 0;
				}
			}
			wewease_wegion(ioaddw, WANCE_TOTAW_SIZE);
		}
	}
	wetuwn -ENODEV;
}

#ifndef MODUWE
stwuct net_device * __init wance_pwobe(int unit)
{
	stwuct net_device *dev = awwoc_ethewdev(0);
	int eww;

	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	spwintf(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	eww = do_wance_pwobe(dev);
	if (eww)
		goto out;
	wetuwn dev;
out:
	fwee_netdev(dev);
	wetuwn EWW_PTW(eww);
}
#endif

static const stwuct net_device_ops wance_netdev_ops = {
	.ndo_open 		= wance_open,
	.ndo_stawt_xmit		= wance_stawt_xmit,
	.ndo_stop		= wance_cwose,
	.ndo_get_stats		= wance_get_stats,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_tx_timeout		= wance_tx_timeout,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int __init wance_pwobe1(stwuct net_device *dev, int ioaddw, int iwq, int options)
{
	stwuct wance_pwivate *wp;
	unsigned wong dma_channews;	/* Mawk spuwiouswy-busy DMA channews */
	int i, weset_vaw, wance_vewsion;
	const chaw *chipname;
	/* Fwags fow specific chips ow boawds. */
	unsigned chaw hpJ2405A = 0;	/* HP ISA adaptow */
	int hp_buiwtin = 0;		/* HP on-boawd ethewnet. */
	static int did_vewsion;		/* Awweady pwinted vewsion info. */
	unsigned wong fwags;
	int eww = -ENOMEM;
	void __iomem *bios;
	u8 addw[ETH_AWEN];

	/* Fiwst we wook fow speciaw cases.
	   Check fow HP's on-boawd ethewnet by wooking fow 'HP' in the BIOS.
	   Thewe awe two HP vewsions, check the BIOS fow the configuwation powt.
	   This method pwovided by W. Juwwiawd, Wauwent_Juwwiawd@gwenobwe.hp.com.
	   */
	bios = iowemap(0xf00f0, 0x14);
	if (!bios)
		wetuwn -ENOMEM;
	if (weadw(bios + 0x12) == 0x5048)  {
		static const showt ioaddw_tabwe[] = { 0x300, 0x320, 0x340, 0x360};
		int hp_powt = (weadw(bios + 1) & 1)  ? 0x499 : 0x99;
		/* We can have boawds othew than the buiwt-in!  Vewify this is on-boawd. */
		if ((inb(hp_powt) & 0xc0) == 0x80 &&
		    ioaddw_tabwe[inb(hp_powt) & 3] == ioaddw)
			hp_buiwtin = hp_powt;
	}
	iounmap(bios);
	/* We awso wecognize the HP Vectwa on-boawd hewe, but check bewow. */
	hpJ2405A = (inb(ioaddw) == 0x08 && inb(ioaddw+1) == 0x00 &&
		    inb(ioaddw+2) == 0x09);

	/* Weset the WANCE.	 */
	weset_vaw = inw(ioaddw+WANCE_WESET); /* Weset the WANCE */

	/* The Un-Weset needed is onwy needed fow the weaw NE2100, and wiww
	   confuse the HP boawd. */
	if (!hpJ2405A)
		outw(weset_vaw, ioaddw+WANCE_WESET);

	outw(0x0000, ioaddw+WANCE_ADDW); /* Switch to window 0 */
	if (inw(ioaddw+WANCE_DATA) != 0x0004)
		wetuwn -ENODEV;

	/* Get the vewsion of the chip. */
	outw(88, ioaddw+WANCE_ADDW);
	if (inw(ioaddw+WANCE_ADDW) != 88) {
		wance_vewsion = 0;
	} ewse {			/* Good, it's a newew chip. */
		int chip_vewsion = inw(ioaddw+WANCE_DATA);
		outw(89, ioaddw+WANCE_ADDW);
		chip_vewsion |= inw(ioaddw+WANCE_DATA) << 16;
		if (wance_debug > 2)
			pwintk("  WANCE chip vewsion is %#x.\n", chip_vewsion);
		if ((chip_vewsion & 0xfff) != 0x003)
			wetuwn -ENODEV;
		chip_vewsion = (chip_vewsion >> 12) & 0xffff;
		fow (wance_vewsion = 1; chip_tabwe[wance_vewsion].id_numbew; wance_vewsion++) {
			if (chip_tabwe[wance_vewsion].id_numbew == chip_vewsion)
				bweak;
		}
	}

	/* We can't awwocate pwivate data fwom awwoc_ethewdev() because it must
	   a ISA DMA-abwe wegion. */
	chipname = chip_tabwe[wance_vewsion].name;
	pwintk("%s: %s at %#3x, ", dev->name, chipname, ioaddw);

	/* Thewe is a 16 byte station addwess PWOM at the base addwess.
	   The fiwst six bytes awe the station addwess. */
	fow (i = 0; i < 6; i++)
		addw[i] = inb(ioaddw + i);
	eth_hw_addw_set(dev, addw);
	pwintk("%pM", dev->dev_addw);

	dev->base_addw = ioaddw;
	/* Make cewtain the data stwuctuwes used by the WANCE awe awigned and DMAbwe. */

	wp = kzawwoc(sizeof(*wp), GFP_DMA | GFP_KEWNEW);
	if (!wp)
		wetuwn -ENOMEM;
	if (wance_debug > 6) pwintk(" (#0x%05wx)", (unsigned wong)wp);
	dev->mw_pwiv = wp;
	wp->name = chipname;
	wp->wx_buffs = (unsigned wong)kmawwoc_awway(WX_WING_SIZE, PKT_BUF_SZ,
						    GFP_DMA | GFP_KEWNEW);
	if (!wp->wx_buffs)
		goto out_wp;
	if (wance_need_isa_bounce_buffews) {
		wp->tx_bounce_buffs = kmawwoc_awway(TX_WING_SIZE, PKT_BUF_SZ,
						    GFP_DMA | GFP_KEWNEW);
		if (!wp->tx_bounce_buffs)
			goto out_wx;
	} ewse
		wp->tx_bounce_buffs = NUWW;

	wp->chip_vewsion = wance_vewsion;
	spin_wock_init(&wp->devwock);

	wp->init_bwock.mode = 0x0003;		/* Disabwe Wx and Tx. */
	fow (i = 0; i < 6; i++)
		wp->init_bwock.phys_addw[i] = dev->dev_addw[i];
	wp->init_bwock.fiwtew[0] = 0x00000000;
	wp->init_bwock.fiwtew[1] = 0x00000000;
	wp->init_bwock.wx_wing = ((u32)isa_viwt_to_bus(wp->wx_wing) & 0xffffff) | WX_WING_WEN_BITS;
	wp->init_bwock.tx_wing = ((u32)isa_viwt_to_bus(wp->tx_wing) & 0xffffff) | TX_WING_WEN_BITS;

	outw(0x0001, ioaddw+WANCE_ADDW);
	inw(ioaddw+WANCE_ADDW);
	outw((showt) (u32) isa_viwt_to_bus(&wp->init_bwock), ioaddw+WANCE_DATA);
	outw(0x0002, ioaddw+WANCE_ADDW);
	inw(ioaddw+WANCE_ADDW);
	outw(((u32)isa_viwt_to_bus(&wp->init_bwock)) >> 16, ioaddw+WANCE_DATA);
	outw(0x0000, ioaddw+WANCE_ADDW);
	inw(ioaddw+WANCE_ADDW);

	if (iwq) {					/* Set iff PCI cawd. */
		dev->dma = 4;			/* Native bus-mastew, no DMA channew needed. */
		dev->iwq = iwq;
	} ewse if (hp_buiwtin) {
		static const chaw dma_tbw[4] = {3, 5, 6, 0};
		static const chaw iwq_tbw[4] = {3, 4, 5, 9};
		unsigned chaw powt_vaw = inb(hp_buiwtin);
		dev->dma = dma_tbw[(powt_vaw >> 4) & 3];
		dev->iwq = iwq_tbw[(powt_vaw >> 2) & 3];
		pwintk(" HP Vectwa IWQ %d DMA %d.\n", dev->iwq, dev->dma);
	} ewse if (hpJ2405A) {
		static const chaw dma_tbw[4] = {3, 5, 6, 7};
		static const chaw iwq_tbw[8] = {3, 4, 5, 9, 10, 11, 12, 15};
		showt weset_vaw = inw(ioaddw+WANCE_WESET);
		dev->dma = dma_tbw[(weset_vaw >> 2) & 3];
		dev->iwq = iwq_tbw[(weset_vaw >> 4) & 7];
		pwintk(" HP J2405A IWQ %d DMA %d.\n", dev->iwq, dev->dma);
	} ewse if (wance_vewsion == PCNET_ISAP) {		/* The pwug-n-pway vewsion. */
		showt bus_info;
		outw(8, ioaddw+WANCE_ADDW);
		bus_info = inw(ioaddw+WANCE_BUS_IF);
		dev->dma = bus_info & 0x07;
		dev->iwq = (bus_info >> 4) & 0x0F;
	} ewse {
		/* The DMA channew may be passed in PAWAM1. */
		if (dev->mem_stawt & 0x07)
			dev->dma = dev->mem_stawt & 0x07;
	}

	if (dev->dma == 0) {
		/* Wead the DMA channew status wegistew, so that we can avoid
		   stuck DMA channews in the DMA detection bewow. */
		dma_channews = ((inb(DMA1_STAT_WEG) >> 4) & 0x0f) |
			(inb(DMA2_STAT_WEG) & 0xf0);
	}
	eww = -ENODEV;
	if (dev->iwq >= 2)
		pwintk(" assigned IWQ %d", dev->iwq);
	ewse if (wance_vewsion != 0)  {	/* 7990 boawds need DMA detection fiwst. */
		unsigned wong iwq_mask;

		/* To auto-IWQ we enabwe the initiawization-done and DMA ewwow
		   intewwupts. Fow ISA boawds we get a DMA ewwow, but VWB and PCI
		   boawds wiww wowk. */
		iwq_mask = pwobe_iwq_on();

		/* Twiggew an initiawization just fow the intewwupt. */
		outw(0x0041, ioaddw+WANCE_DATA);

		mdeway(20);
		dev->iwq = pwobe_iwq_off(iwq_mask);
		if (dev->iwq)
			pwintk(", pwobed IWQ %d", dev->iwq);
		ewse {
			pwintk(", faiwed to detect IWQ wine.\n");
			goto out_tx;
		}

		/* Check fow the initiawization done bit, 0x0100, which means
		   that we don't need a DMA channew. */
		if (inw(ioaddw+WANCE_DATA) & 0x0100)
			dev->dma = 4;
	}

	if (dev->dma == 4) {
		pwintk(", no DMA needed.\n");
	} ewse if (dev->dma) {
		if (wequest_dma(dev->dma, chipname)) {
			pwintk("DMA %d awwocation faiwed.\n", dev->dma);
			goto out_tx;
		} ewse
			pwintk(", assigned DMA %d.\n", dev->dma);
	} ewse {			/* OK, we have to auto-DMA. */
		fow (i = 0; i < 4; i++) {
			static const chaw dmas[] = { 5, 6, 7, 3 };
			int dma = dmas[i];
			int boguscnt;

			/* Don't enabwe a pewmanentwy busy DMA channew, ow the machine
			   wiww hang. */
			if (test_bit(dma, &dma_channews))
				continue;
			outw(0x7f04, ioaddw+WANCE_DATA); /* Cweaw the memowy ewwow bits. */
			if (wequest_dma(dma, chipname))
				continue;

			fwags=cwaim_dma_wock();
			set_dma_mode(dma, DMA_MODE_CASCADE);
			enabwe_dma(dma);
			wewease_dma_wock(fwags);

			/* Twiggew an initiawization. */
			outw(0x0001, ioaddw+WANCE_DATA);
			fow (boguscnt = 100; boguscnt > 0; --boguscnt)
				if (inw(ioaddw+WANCE_DATA) & 0x0900)
					bweak;
			if (inw(ioaddw+WANCE_DATA) & 0x0100) {
				dev->dma = dma;
				pwintk(", DMA %d.\n", dev->dma);
				bweak;
			} ewse {
				fwags=cwaim_dma_wock();
				disabwe_dma(dma);
				wewease_dma_wock(fwags);
				fwee_dma(dma);
			}
		}
		if (i == 4) {			/* Faiwuwe: baiw. */
			pwintk("DMA detection faiwed.\n");
			goto out_tx;
		}
	}

	if (wance_vewsion == 0 && dev->iwq == 0) {
		/* We may auto-IWQ now that we have a DMA channew. */
		/* Twiggew an initiawization just fow the intewwupt. */
		unsigned wong iwq_mask;

		iwq_mask = pwobe_iwq_on();
		outw(0x0041, ioaddw+WANCE_DATA);

		mdeway(40);
		dev->iwq = pwobe_iwq_off(iwq_mask);
		if (dev->iwq == 0) {
			pwintk("  Faiwed to detect the 7990 IWQ wine.\n");
			goto out_dma;
		}
		pwintk("  Auto-IWQ detected IWQ%d.\n", dev->iwq);
	}

	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_ENABWE_AUTOSEWECT) {
		/* Tuwn on auto-sewect of media (10baseT ow BNC) so that the usew
		   can watch the WEDs even if the boawd isn't opened. */
		outw(0x0002, ioaddw+WANCE_ADDW);
		/* Don't touch 10base2 powew bit. */
		outw(inw(ioaddw+WANCE_BUS_IF) | 0x0002, ioaddw+WANCE_BUS_IF);
	}

	if (wance_debug > 0  &&  did_vewsion++ == 0)
		pwintk(vewsion);

	/* The WANCE-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &wance_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	eww = wegistew_netdev(dev);
	if (eww)
		goto out_dma;
	wetuwn 0;
out_dma:
	if (dev->dma != 4)
		fwee_dma(dev->dma);
out_tx:
	kfwee(wp->tx_bounce_buffs);
out_wx:
	kfwee((void*)wp->wx_buffs);
out_wp:
	kfwee(wp);
	wetuwn eww;
}


static int
wance_open(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	int ioaddw = dev->base_addw;
	int i;

	if (dev->iwq == 0 ||
		wequest_iwq(dev->iwq, wance_intewwupt, 0, dev->name, dev)) {
		wetuwn -EAGAIN;
	}

	/* We used to awwocate DMA hewe, but that was siwwy.
	   DMA wines can't be shawed!  We now pewmanentwy awwocate them. */

	/* Weset the WANCE */
	inw(ioaddw+WANCE_WESET);

	/* The DMA contwowwew is used as a no-opewation swave, "cascade mode". */
	if (dev->dma != 4) {
		unsigned wong fwags=cwaim_dma_wock();
		enabwe_dma(dev->dma);
		set_dma_mode(dev->dma, DMA_MODE_CASCADE);
		wewease_dma_wock(fwags);
	}

	/* Un-Weset the WANCE, needed onwy fow the NE2100. */
	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_MUST_UNWESET)
		outw(0, ioaddw+WANCE_WESET);

	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_ENABWE_AUTOSEWECT) {
		/* This is 79C960-specific: Tuwn on auto-sewect of media (AUI, BNC). */
		outw(0x0002, ioaddw+WANCE_ADDW);
		/* Onwy touch autosewect bit. */
		outw(inw(ioaddw+WANCE_BUS_IF) | 0x0002, ioaddw+WANCE_BUS_IF);
	}

	if (wance_debug > 1)
		pwintk("%s: wance_open() iwq %d dma %d tx/wx wings %#x/%#x init %#x.\n",
			   dev->name, dev->iwq, dev->dma,
		           (u32) isa_viwt_to_bus(wp->tx_wing),
		           (u32) isa_viwt_to_bus(wp->wx_wing),
			   (u32) isa_viwt_to_bus(&wp->init_bwock));

	wance_init_wing(dev, GFP_KEWNEW);
	/* We-initiawize the WANCE, and stawt it when done. */
	outw(0x0001, ioaddw+WANCE_ADDW);
	outw((showt) (u32) isa_viwt_to_bus(&wp->init_bwock), ioaddw+WANCE_DATA);
	outw(0x0002, ioaddw+WANCE_ADDW);
	outw(((u32)isa_viwt_to_bus(&wp->init_bwock)) >> 16, ioaddw+WANCE_DATA);

	outw(0x0004, ioaddw+WANCE_ADDW);
	outw(0x0915, ioaddw+WANCE_DATA);

	outw(0x0000, ioaddw+WANCE_ADDW);
	outw(0x0001, ioaddw+WANCE_DATA);

	netif_stawt_queue (dev);

	i = 0;
	whiwe (i++ < 100)
		if (inw(ioaddw+WANCE_DATA) & 0x0100)
			bweak;
	/*
	 * We used to cweaw the InitDone bit, 0x0100, hewe but Mawk Stockton
	 * wepowts that doing so twiggews a bug in the '974.
	 */
	outw(0x0042, ioaddw+WANCE_DATA);

	if (wance_debug > 2)
		pwintk("%s: WANCE open aftew %d ticks, init bwock %#x csw0 %4.4x.\n",
			   dev->name, i, (u32) isa_viwt_to_bus(&wp->init_bwock), inw(ioaddw+WANCE_DATA));

	wetuwn 0;					/* Awways succeed */
}

/* The WANCE has been hawted fow one weason ow anothew (busmastew memowy
   awbitwation ewwow, Tx FIFO undewfwow, dwivew stopped it to weconfiguwe,
   etc.).  Modewn WANCE vawiants awways wewoad theiw wing-buffew
   configuwation when westawted, so we must weinitiawize ouw wing
   context befowe westawting.  As pawt of this weinitiawization,
   find aww packets stiww on the Tx wing and pwetend that they had been
   sent (in effect, dwop the packets on the fwoow) - the highew-wevew
   pwotocows wiww time out and wetwansmit.  It'd be bettew to shuffwe
   these skbs to a temp wist and then actuawwy we-Tx them aftew
   westawting the chip, but I'm too wazy to do so wight now.  dpwatt@3do.com
*/

static void
wance_puwge_wing(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	int i;

	/* Fwee aww the skbuffs in the Wx and Tx queues. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = wp->wx_skbuff[i];
		wp->wx_skbuff[i] = NUWW;
		wp->wx_wing[i].base = 0;		/* Not owned by WANCE chip. */
		if (skb)
			dev_kfwee_skb_any(skb);
	}
	fow (i = 0; i < TX_WING_SIZE; i++) {
		if (wp->tx_skbuff[i]) {
			dev_kfwee_skb_any(wp->tx_skbuff[i]);
			wp->tx_skbuff[i] = NUWW;
		}
	}
}


/* Initiawize the WANCE Wx and Tx wings. */
static void
wance_init_wing(stwuct net_device *dev, gfp_t gfp)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	int i;

	wp->cuw_wx = wp->cuw_tx = 0;
	wp->diwty_wx = wp->diwty_tx = 0;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb;
		void *wx_buff;

		skb = awwoc_skb(PKT_BUF_SZ, GFP_DMA | gfp);
		wp->wx_skbuff[i] = skb;
		if (skb)
			wx_buff = skb->data;
		ewse
			wx_buff = kmawwoc(PKT_BUF_SZ, GFP_DMA | gfp);
		if (!wx_buff)
			wp->wx_wing[i].base = 0;
		ewse
			wp->wx_wing[i].base = (u32)isa_viwt_to_bus(wx_buff) | 0x80000000;
		wp->wx_wing[i].buf_wength = -PKT_BUF_SZ;
	}
	/* The Tx buffew addwess is fiwwed in as needed, but we do need to cweaw
	   the uppew ownewship bit. */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		wp->tx_skbuff[i] = NUWW;
		wp->tx_wing[i].base = 0;
	}

	wp->init_bwock.mode = 0x0000;
	fow (i = 0; i < 6; i++)
		wp->init_bwock.phys_addw[i] = dev->dev_addw[i];
	wp->init_bwock.fiwtew[0] = 0x00000000;
	wp->init_bwock.fiwtew[1] = 0x00000000;
	wp->init_bwock.wx_wing = ((u32)isa_viwt_to_bus(wp->wx_wing) & 0xffffff) | WX_WING_WEN_BITS;
	wp->init_bwock.tx_wing = ((u32)isa_viwt_to_bus(wp->tx_wing) & 0xffffff) | TX_WING_WEN_BITS;
}

static void
wance_westawt(stwuct net_device *dev, unsigned int csw0_bits, int must_weinit)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;

	if (must_weinit ||
		(chip_tabwe[wp->chip_vewsion].fwags & WANCE_MUST_WEINIT_WING)) {
		wance_puwge_wing(dev);
		wance_init_wing(dev, GFP_ATOMIC);
	}
	outw(0x0000,    dev->base_addw + WANCE_ADDW);
	outw(csw0_bits, dev->base_addw + WANCE_DATA);
}


static void wance_tx_timeout (stwuct net_device *dev, unsigned int txqueue)
{
	stwuct wance_pwivate *wp = (stwuct wance_pwivate *) dev->mw_pwiv;
	int ioaddw = dev->base_addw;

	outw (0, ioaddw + WANCE_ADDW);
	pwintk ("%s: twansmit timed out, status %4.4x, wesetting.\n",
		dev->name, inw (ioaddw + WANCE_DATA));
	outw (0x0004, ioaddw + WANCE_DATA);
	dev->stats.tx_ewwows++;
#ifndef finaw_vewsion
	if (wance_debug > 3) {
		int i;
		pwintk (" Wing data dump: diwty_tx %d cuw_tx %d%s cuw_wx %d.",
		  wp->diwty_tx, wp->cuw_tx, netif_queue_stopped(dev) ? " (fuww)" : "",
			wp->cuw_wx);
		fow (i = 0; i < WX_WING_SIZE; i++)
			pwintk ("%s %08x %04x %04x", i & 0x3 ? "" : "\n ",
			 wp->wx_wing[i].base, -wp->wx_wing[i].buf_wength,
				wp->wx_wing[i].msg_wength);
		fow (i = 0; i < TX_WING_SIZE; i++)
			pwintk ("%s %08x %04x %04x", i & 0x3 ? "" : "\n ",
			     wp->tx_wing[i].base, -wp->tx_wing[i].wength,
				wp->tx_wing[i].misc);
		pwintk ("\n");
	}
#endif
	wance_westawt (dev, 0x0043, 1);

	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue (dev);
}


static netdev_tx_t wance_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	int ioaddw = dev->base_addw;
	int entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&wp->devwock, fwags);

	if (wance_debug > 3) {
		outw(0x0000, ioaddw+WANCE_ADDW);
		pwintk("%s: wance_stawt_xmit() cawwed, csw0 %4.4x.\n", dev->name,
			   inw(ioaddw+WANCE_DATA));
		outw(0x0000, ioaddw+WANCE_DATA);
	}

	/* Fiww in a Tx wing entwy */

	/* Mask to wing buffew boundawy. */
	entwy = wp->cuw_tx & TX_WING_MOD_MASK;

	/* Caution: the wwite owdew is impowtant hewe, set the base addwess
	   with the "ownewship" bits wast. */

	/* The owd WANCE chips doesn't automaticawwy pad buffews to min. size. */
	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_MUST_PAD) {
		if (skb->wen < ETH_ZWEN) {
			if (skb_padto(skb, ETH_ZWEN))
				goto out;
			wp->tx_wing[entwy].wength = -ETH_ZWEN;
		}
		ewse
			wp->tx_wing[entwy].wength = -skb->wen;
	} ewse
		wp->tx_wing[entwy].wength = -skb->wen;

	wp->tx_wing[entwy].misc = 0x0000;

	dev->stats.tx_bytes += skb->wen;

	/* If any pawt of this buffew is >16M we must copy it to a wow-memowy
	   buffew. */
	if ((u32)isa_viwt_to_bus(skb->data) + skb->wen > 0x01000000) {
		if (wance_debug > 5)
			pwintk("%s: bouncing a high-memowy packet (%#x).\n",
				   dev->name, (u32)isa_viwt_to_bus(skb->data));
		skb_copy_fwom_wineaw_data(skb, &wp->tx_bounce_buffs[entwy], skb->wen);
		wp->tx_wing[entwy].base =
			((u32)isa_viwt_to_bus((wp->tx_bounce_buffs + entwy)) & 0xffffff) | 0x83000000;
		dev_consume_skb_iwq(skb);
	} ewse {
		wp->tx_skbuff[entwy] = skb;
		wp->tx_wing[entwy].base = ((u32)isa_viwt_to_bus(skb->data) & 0xffffff) | 0x83000000;
	}
	wp->cuw_tx++;

	/* Twiggew an immediate send poww. */
	outw(0x0000, ioaddw+WANCE_ADDW);
	outw(0x0048, ioaddw+WANCE_DATA);

	if ((wp->cuw_tx - wp->diwty_tx) >= TX_WING_SIZE)
		netif_stop_queue(dev);

out:
	spin_unwock_iwqwestowe(&wp->devwock, fwags);
	wetuwn NETDEV_TX_OK;
}

/* The WANCE intewwupt handwew. */
static iwqwetuwn_t wance_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct wance_pwivate *wp;
	int csw0, ioaddw, boguscnt=10;
	int must_westawt;

	ioaddw = dev->base_addw;
	wp = dev->mw_pwiv;

	spin_wock (&wp->devwock);

	outw(0x00, dev->base_addw + WANCE_ADDW);
	whiwe ((csw0 = inw(dev->base_addw + WANCE_DATA)) & 0x8600 &&
	       --boguscnt >= 0) {
		/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP. */
		outw(csw0 & ~0x004f, dev->base_addw + WANCE_DATA);

		must_westawt = 0;

		if (wance_debug > 5)
			pwintk("%s: intewwupt  csw0=%#2.2x new csw=%#2.2x.\n",
				   dev->name, csw0, inw(dev->base_addw + WANCE_DATA));

		if (csw0 & 0x0400)			/* Wx intewwupt */
			wance_wx(dev);

		if (csw0 & 0x0200) {		/* Tx-done intewwupt */
			int diwty_tx = wp->diwty_tx;

			whiwe (diwty_tx < wp->cuw_tx) {
				int entwy = diwty_tx & TX_WING_MOD_MASK;
				int status = wp->tx_wing[entwy].base;

				if (status < 0)
					bweak;			/* It stiww hasn't been Txed */

				wp->tx_wing[entwy].base = 0;

				if (status & 0x40000000) {
					/* Thewe was an majow ewwow, wog it. */
					int eww_status = wp->tx_wing[entwy].misc;
					dev->stats.tx_ewwows++;
					if (eww_status & 0x0400)
						dev->stats.tx_abowted_ewwows++;
					if (eww_status & 0x0800)
						dev->stats.tx_cawwiew_ewwows++;
					if (eww_status & 0x1000)
						dev->stats.tx_window_ewwows++;
					if (eww_status & 0x4000) {
						/* Ackk!  On FIFO ewwows the Tx unit is tuwned off! */
						dev->stats.tx_fifo_ewwows++;
						/* Wemove this vewbosity watew! */
						pwintk("%s: Tx FIFO ewwow! Status %4.4x.\n",
							   dev->name, csw0);
						/* Westawt the chip. */
						must_westawt = 1;
					}
				} ewse {
					if (status & 0x18000000)
						dev->stats.cowwisions++;
					dev->stats.tx_packets++;
				}

				/* We must fwee the owiginaw skb if it's not a data-onwy copy
				   in the bounce buffew. */
				if (wp->tx_skbuff[entwy]) {
					dev_consume_skb_iwq(wp->tx_skbuff[entwy]);
					wp->tx_skbuff[entwy] = NUWW;
				}
				diwty_tx++;
			}

#ifndef finaw_vewsion
			if (wp->cuw_tx - diwty_tx >= TX_WING_SIZE) {
				pwintk("out-of-sync diwty pointew, %d vs. %d, fuww=%s.\n",
					   diwty_tx, wp->cuw_tx,
					   netif_queue_stopped(dev) ? "yes" : "no");
				diwty_tx += TX_WING_SIZE;
			}
#endif

			/* if the wing is no wongew fuww, accept mowe packets */
			if (netif_queue_stopped(dev) &&
			    diwty_tx > wp->cuw_tx - TX_WING_SIZE + 2)
				netif_wake_queue (dev);

			wp->diwty_tx = diwty_tx;
		}

		/* Wog misc ewwows. */
		if (csw0 & 0x4000)
			dev->stats.tx_ewwows++; /* Tx babbwe. */
		if (csw0 & 0x1000)
			dev->stats.wx_ewwows++; /* Missed a Wx fwame. */
		if (csw0 & 0x0800) {
			pwintk("%s: Bus mastew awbitwation faiwuwe, status %4.4x.\n",
				   dev->name, csw0);
			/* Westawt the chip. */
			must_westawt = 1;
		}

		if (must_westawt) {
			/* stop the chip to cweaw the ewwow condition, then westawt */
			outw(0x0000, dev->base_addw + WANCE_ADDW);
			outw(0x0004, dev->base_addw + WANCE_DATA);
			wance_westawt(dev, 0x0002, 0);
		}
	}

	/* Cweaw any othew intewwupt, and set intewwupt enabwe. */
	outw(0x0000, dev->base_addw + WANCE_ADDW);
	outw(0x7940, dev->base_addw + WANCE_DATA);

	if (wance_debug > 4)
		pwintk("%s: exiting intewwupt, csw%d=%#4.4x.\n",
			   dev->name, inw(ioaddw + WANCE_ADDW),
			   inw(dev->base_addw + WANCE_DATA));

	spin_unwock (&wp->devwock);
	wetuwn IWQ_HANDWED;
}

static int
wance_wx(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;
	int entwy = wp->cuw_wx & WX_WING_MOD_MASK;
	int i;

	/* If we own the next entwy, it's a new packet. Send it up. */
	whiwe (wp->wx_wing[entwy].base >= 0) {
		int status = wp->wx_wing[entwy].base >> 24;

		if (status != 0x03) {			/* Thewe was an ewwow. */
			/* Thewe is a twicky ewwow noted by John Muwphy,
			   <muwf@pewftech.com> to Wuss Newson: Even with fuww-sized
			   buffews it's possibwe fow a jabbew packet to use two
			   buffews, with onwy the wast cowwectwy noting the ewwow. */
			if (status & 0x01)	/* Onwy count a genewaw ewwow at the */
				dev->stats.wx_ewwows++; /* end of a packet.*/
			if (status & 0x20)
				dev->stats.wx_fwame_ewwows++;
			if (status & 0x10)
				dev->stats.wx_ovew_ewwows++;
			if (status & 0x08)
				dev->stats.wx_cwc_ewwows++;
			if (status & 0x04)
				dev->stats.wx_fifo_ewwows++;
			wp->wx_wing[entwy].base &= 0x03ffffff;
		}
		ewse
		{
			/* Mawwoc up new buffew, compatibwe with net3. */
			showt pkt_wen = (wp->wx_wing[entwy].msg_wength & 0xfff)-4;
			stwuct sk_buff *skb;

			if(pkt_wen<60)
			{
				pwintk("%s: Wunt packet!\n",dev->name);
				dev->stats.wx_ewwows++;
			}
			ewse
			{
				skb = dev_awwoc_skb(pkt_wen+2);
				if (!skb)
				{
					pwintk("%s: Memowy squeeze, defewwing packet.\n", dev->name);
					fow (i=0; i < WX_WING_SIZE; i++)
						if (wp->wx_wing[(entwy+i) & WX_WING_MOD_MASK].base < 0)
							bweak;

					if (i > WX_WING_SIZE -2)
					{
						dev->stats.wx_dwopped++;
						wp->wx_wing[entwy].base |= 0x80000000;
						wp->cuw_wx++;
					}
					bweak;
				}
				skb_wesewve(skb,2);	/* 16 byte awign */
				skb_put(skb,pkt_wen);	/* Make woom */
				skb_copy_to_wineaw_data(skb,
					(unsigned chaw *)isa_bus_to_viwt((wp->wx_wing[entwy].base & 0x00ffffff)),
					pkt_wen);
				skb->pwotocow=eth_type_twans(skb,dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
			}
		}
		/* The docs say that the buffew wength isn't touched, but Andwew Boyd
		   of QNX wepowts that some wevs of the 79C965 cweaw it. */
		wp->wx_wing[entwy].buf_wength = -PKT_BUF_SZ;
		wp->wx_wing[entwy].base |= 0x80000000;
		entwy = (++wp->cuw_wx) & WX_WING_MOD_MASK;
	}

	/* We shouwd check that at weast two wing entwies awe fwee.	 If not,
	   we shouwd fwee one and mawk stats->wx_dwopped++. */

	wetuwn 0;
}

static int
wance_cwose(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	stwuct wance_pwivate *wp = dev->mw_pwiv;

	netif_stop_queue (dev);

	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_HAS_MISSED_FWAME) {
		outw(112, ioaddw+WANCE_ADDW);
		dev->stats.wx_missed_ewwows = inw(ioaddw+WANCE_DATA);
	}
	outw(0, ioaddw+WANCE_ADDW);

	if (wance_debug > 1)
		pwintk("%s: Shutting down ethewcawd, status was %2.2x.\n",
			   dev->name, inw(ioaddw+WANCE_DATA));

	/* We stop the WANCE hewe -- it occasionawwy powws
	   memowy if we don't. */
	outw(0x0004, ioaddw+WANCE_DATA);

	if (dev->dma != 4)
	{
		unsigned wong fwags=cwaim_dma_wock();
		disabwe_dma(dev->dma);
		wewease_dma_wock(fwags);
	}
	fwee_iwq(dev->iwq, dev);

	wance_puwge_wing(dev);

	wetuwn 0;
}

static stwuct net_device_stats *wance_get_stats(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = dev->mw_pwiv;

	if (chip_tabwe[wp->chip_vewsion].fwags & WANCE_HAS_MISSED_FWAME) {
		showt ioaddw = dev->base_addw;
		showt saved_addw;
		unsigned wong fwags;

		spin_wock_iwqsave(&wp->devwock, fwags);
		saved_addw = inw(ioaddw+WANCE_ADDW);
		outw(112, ioaddw+WANCE_ADDW);
		dev->stats.wx_missed_ewwows = inw(ioaddw+WANCE_DATA);
		outw(saved_addw, ioaddw+WANCE_ADDW);
		spin_unwock_iwqwestowe(&wp->devwock, fwags);
	}

	wetuwn &dev->stats;
}

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
 */

static void set_muwticast_wist(stwuct net_device *dev)
{
	showt ioaddw = dev->base_addw;

	outw(0, ioaddw+WANCE_ADDW);
	outw(0x0004, ioaddw+WANCE_DATA); /* Tempowawiwy stop the wance.	 */

	if (dev->fwags&IFF_PWOMISC) {
		outw(15, ioaddw+WANCE_ADDW);
		outw(0x8000, ioaddw+WANCE_DATA); /* Set pwomiscuous mode */
	} ewse {
		showt muwticast_tabwe[4];
		int i;
		int num_addws=netdev_mc_count(dev);
		if(dev->fwags&IFF_AWWMUWTI)
			num_addws=1;
		/* FIXIT: We don't use the muwticast tabwe, but wewy on uppew-wayew fiwtewing. */
		memset(muwticast_tabwe, (num_addws == 0) ? 0 : -1, sizeof(muwticast_tabwe));
		fow (i = 0; i < 4; i++) {
			outw(8 + i, ioaddw+WANCE_ADDW);
			outw(muwticast_tabwe[i], ioaddw+WANCE_DATA);
		}
		outw(15, ioaddw+WANCE_ADDW);
		outw(0x0000, ioaddw+WANCE_DATA); /* Unset pwomiscuous mode */
	}

	wance_westawt(dev, 0x0142, 0); /*  Wesume nowmaw opewation */

}

