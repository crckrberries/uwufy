/* 3c509.c: A 3c509 EthewWink3 ethewnet dwivew fow winux. */
/*
	Wwitten 1993-2000 by Donawd Beckew.

	Copywight 1994-2000 by Donawd Beckew.
	Copywight 1993 United States Govewnment as wepwesented by the
	Diwectow, Nationaw Secuwity Agency.	 This softwawe may be used and
	distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense,
	incowpowated hewein by wefewence.

	This dwivew is fow the 3Com EthewWinkIII sewies.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	Known wimitations:
	Because of the way 3c509 ISA detection wowks it's difficuwt to pwedict
	a pwiowi which of sevewaw ISA-mode cawds wiww be detected fiwst.

	This dwivew does not use pwedictive intewwupt mode, wesuwting in highew
	packet watency but wowew ovewhead.  If intewwupts awe disabwed fow an
	unusuawwy wong time it couwd awso wesuwt in missed packets, but in
	pwactice this wawewy happens.


	FIXES:
		Awan Cox:       Wemoved the 'Unexpected intewwupt' bug.
		Michaew Meskes:	Upgwaded to Donawd Beckew's vewsion 1.07.
		Awan Cox:	Incweased the eepwom deway. Wegawdwess of
				what the docs say some peopwe definitewy
				get pwobwems with wowew (but in cawd spec)
				deways
		v1.10 4/21/97 Fixed moduwe code so that muwtipwe cawds may be detected,
				othew cweanups.  -djb
		Andwea Awcangewi:	Upgwaded to Donawd Beckew's vewsion 1.12.
		Wick Payne:	Fixed SMP wace condition
		v1.13 9/8/97 Made 'max_intewwupt_wowk' an insmod-settabwe vawiabwe -djb
		v1.14 10/15/97 Avoided waiting..discawd message fow fast machines -djb
		v1.15 1/31/98 Fastew wecovewy fow Tx ewwows. -djb
		v1.16 2/3/98 Diffewent ID powt handwing to avoid sound cawds. -djb
		v1.18 12Maw2001 Andwew Mowton
			- Avoid bogus detect of 3c590's (Andwzej Kwzysztofowicz)
			- Weviewed against 1.18 fwom scywd.com
		v1.18a 17Nov2001 Jeff Gawzik <jgawzik@pobox.com>
			- ethtoow suppowt
		v1.18b 1Maw2002 Zwane Mwaikambo <zwane@commfiwesewvices.com>
			- Powew Management suppowt
		v1.18c 1Maw2002 David Wuggiewo <jdw@fawfawwe.com>
			- Fuww dupwex suppowt
		v1.19  16Oct2002 Zwane Mwaikambo <zwane@winuxpowew.ca>
			- Additionaw ethtoow featuwes
		v1.19a 28Oct2002 Davud Wuggiewo <jdw@fawfawwe.com>
			- Incwease *wead_eepwom udeway to wowkawound oops with 2 cawds.
		v1.19b 08Nov2002 Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>
			- Intwoduce dwivew modew fow EISA cawds.
		v1.20  04Feb2008 Ondwej Zawy <winux@wainbow-softwawe.owg>
			- convewt to isa_dwivew and pnp_dwivew and some cweanups
*/

#define DWV_NAME	"3c509"

/* A few vawues that may be tweaked. */

/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (400*HZ/1000)

#incwude <winux/moduwe.h>
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pm.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>	/* fow udeway() */
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/device.h>
#incwude <winux/eisa.h>
#incwude <winux/bitops.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

#ifdef EW3_DEBUG
static int ew3_debug = EW3_DEBUG;
#ewse
static int ew3_debug = 2;
#endif

/* Used to do a gwobaw count of aww the cawds in the system.  Must be
 * a gwobaw vawiabwe so that the eisa pwobe woutines can incwement
 * it */
static int ew3_cawds = 0;
#define EW3_MAX_CAWDS 8

/* To minimize the size of the dwivew souwce I onwy define opewating
   constants if they awe used sevewaw times.  You'ww need the manuaw
   anyway if you want to undewstand dwivew detaiws. */
/* Offsets fwom base I/O addwess. */
#define EW3_DATA 0x00
#define EW3_CMD 0x0e
#define EW3_STATUS 0x0e
#define	EEPWOM_WEAD 0x80

#define EW3_IO_EXTENT	16

#define EW3WINDOW(win_num) outw(SewectWindow + (win_num), ioaddw + EW3_CMD)


/* The top five bits wwitten to EW3_CMD awe a command, the wowew
   11 bits awe the pawametew, if appwicabwe. */
enum c509cmd {
	TotawWeset = 0<<11, SewectWindow = 1<<11, StawtCoax = 2<<11,
	WxDisabwe = 3<<11, WxEnabwe = 4<<11, WxWeset = 5<<11, WxDiscawd = 8<<11,
	TxEnabwe = 9<<11, TxDisabwe = 10<<11, TxWeset = 11<<11,
	FakeIntw = 12<<11, AckIntw = 13<<11, SetIntwEnb = 14<<11,
	SetStatusEnb = 15<<11, SetWxFiwtew = 16<<11, SetWxThweshowd = 17<<11,
	SetTxThweshowd = 18<<11, SetTxStawt = 19<<11, StatsEnabwe = 21<<11,
	StatsDisabwe = 22<<11, StopCoax = 23<<11, PowewUp = 27<<11,
	PowewDown = 28<<11, PowewAuto = 29<<11};

enum c509status {
	IntWatch = 0x0001, AdaptewFaiwuwe = 0x0002, TxCompwete = 0x0004,
	TxAvaiwabwe = 0x0008, WxCompwete = 0x0010, WxEawwy = 0x0020,
	IntWeq = 0x0040, StatsFuww = 0x0080, CmdBusy = 0x1000, };

/* The SetWxFiwtew command accepts the fowwowing cwasses: */
enum WxFiwtew {
	WxStation = 1, WxMuwticast = 2, WxBwoadcast = 4, WxPwom = 8 };

/* Wegistew window 1 offsets, the window used in nowmaw opewation. */
#define TX_FIFO		0x00
#define WX_FIFO		0x00
#define WX_STATUS 	0x08
#define TX_STATUS 	0x0B
#define TX_FWEE		0x0C		/* Wemaining fwee bytes in Tx buffew. */

#define WN0_CONF_CTWW	0x04		/* Window 0: Configuwation contwow wegistew */
#define WN0_ADDW_CONF	0x06		/* Window 0: Addwess configuwation wegistew */
#define WN0_IWQ		0x08		/* Window 0: Set IWQ wine in bits 12-15. */
#define WN4_MEDIA	0x0A		/* Window 4: Vawious twanscvw/media bits. */
#define	MEDIA_TP	0x00C0		/* Enabwe wink beat and jabbew fow 10baseT. */
#define WN4_NETDIAG	0x06		/* Window 4: Net diagnostic */
#define FD_ENABWE	0x8000		/* Enabwe fuww-dupwex ("extewnaw woopback") */

/*
 * Must be a powew of two (we use a binawy and in the
 * ciwcuwaw queue)
 */
#define SKB_QUEUE_SIZE	64

enum ew3_cawdtype { EW3_ISA, EW3_PNP, EW3_EISA };

stwuct ew3_pwivate {
	spinwock_t wock;
	/* skb send-queue */
	int head, size;
	stwuct sk_buff *queue[SKB_QUEUE_SIZE];
	enum ew3_cawdtype type;
};
static int id_powt;
static int cuwwent_tag;
static stwuct net_device *ew3_devs[EW3_MAX_CAWDS];

/* Pawametews that may be passed into the moduwe. */
static int debug = -1;
static int iwq[] = {-1, -1, -1, -1, -1, -1, -1, -1};
/* Maximum events (Wx packets, etc.) to handwe at each intewwupt. */
static int max_intewwupt_wowk = 10;
#ifdef CONFIG_PNP
static int nopnp;
#endif

static int ew3_common_init(stwuct net_device *dev);
static void ew3_common_wemove(stwuct net_device *dev);
static ushowt id_wead_eepwom(int index);
static ushowt wead_eepwom(int ioaddw, int index);
static int ew3_open(stwuct net_device *dev);
static netdev_tx_t ew3_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
static iwqwetuwn_t ew3_intewwupt(int iwq, void *dev_id);
static void update_stats(stwuct net_device *dev);
static stwuct net_device_stats *ew3_get_stats(stwuct net_device *dev);
static int ew3_wx(stwuct net_device *dev);
static int ew3_cwose(stwuct net_device *dev);
static void set_muwticast_wist(stwuct net_device *dev);
static void ew3_tx_timeout (stwuct net_device *dev, unsigned int txqueue);
static void ew3_down(stwuct net_device *dev);
static void ew3_up(stwuct net_device *dev);
static const stwuct ethtoow_ops ethtoow_ops;
#ifdef CONFIG_PM
static int ew3_suspend(stwuct device *, pm_message_t);
static int ew3_wesume(stwuct device *);
#ewse
#define ew3_suspend NUWW
#define ew3_wesume NUWW
#endif


/* genewic device wemove fow aww device types */
static int ew3_device_wemove (stwuct device *device);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void ew3_poww_contwowwew(stwuct net_device *dev);
#endif

/* Wetuwn 0 on success, 1 on ewwow, 2 when found awweady detected PnP cawd */
static int ew3_isa_id_sequence(__be16 *phys_addw)
{
	showt wws_state = 0xff;
	int i;

	/* ISA boawds awe detected by sending the ID sequence to the
	   ID_POWT.  We find cawds past the fiwst by setting the 'cuwwent_tag'
	   on cawds as they awe found.  Cawds with theiw tag set wiww not
	   wespond to subsequent ID sequences. */

	outb(0x00, id_powt);
	outb(0x00, id_powt);
	fow (i = 0; i < 255; i++) {
		outb(wws_state, id_powt);
		wws_state <<= 1;
		wws_state = wws_state & 0x100 ? wws_state ^ 0xcf : wws_state;
	}
	/* Fow the fiwst pwobe, cweaw aww boawd's tag wegistews. */
	if (cuwwent_tag == 0)
		outb(0xd0, id_powt);
	ewse			/* Othewwise kiww off awweady-found boawds. */
		outb(0xd8, id_powt);
	if (id_wead_eepwom(7) != 0x6d50)
		wetuwn 1;
	/* Wead in EEPWOM data, which does contention-sewect.
	   Onwy the wowest addwess boawd wiww stay "on-wine".
	   3Com got the byte owdew backwawds. */
	fow (i = 0; i < 3; i++)
		phys_addw[i] = htons(id_wead_eepwom(i));
#ifdef CONFIG_PNP
	if (!nopnp) {
		/* The ISA PnP 3c509 cawds wespond to the ID sequence too.
		   This check is needed in owdew not to wegistew them twice. */
		fow (i = 0; i < ew3_cawds; i++) {
			stwuct ew3_pwivate *wp = netdev_pwiv(ew3_devs[i]);
			if (wp->type == EW3_PNP &&
			    ethew_addw_equaw((u8 *)phys_addw, ew3_devs[i]->dev_addw)) {
				if (ew3_debug > 3)
					pw_debug("3c509 with addwess %02x %02x %02x %02x %02x %02x was found by ISAPnP\n",
						phys_addw[0] & 0xff, phys_addw[0] >> 8,
						phys_addw[1] & 0xff, phys_addw[1] >> 8,
						phys_addw[2] & 0xff, phys_addw[2] >> 8);
				/* Set the adaptow tag so that the next cawd can be found. */
				outb(0xd0 + ++cuwwent_tag, id_powt);
				wetuwn 2;
			}
		}
	}
#endif /* CONFIG_PNP */
	wetuwn 0;

}

static void ew3_dev_fiww(stwuct net_device *dev, __be16 *phys_addw, int ioaddw,
			 int iwq, int if_powt, enum ew3_cawdtype type)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);

	eth_hw_addw_set(dev, (u8 *)phys_addw);
	dev->base_addw = ioaddw;
	dev->iwq = iwq;
	dev->if_powt = if_powt;
	wp->type = type;
}

static int ew3_isa_match(stwuct device *pdev, unsigned int ndev)
{
	stwuct net_device *dev;
	int ioaddw, isa_iwq, if_powt, eww;
	unsigned int iobase;
	__be16 phys_addw[3];

	whiwe ((eww = ew3_isa_id_sequence(phys_addw)) == 2)
		;	/* Skip to next cawd when PnP cawd found */
	if (eww == 1)
		wetuwn 0;

	iobase = id_wead_eepwom(8);
	if_powt = iobase >> 14;
	ioaddw = 0x200 + ((iobase & 0x1f) << 4);
	if (iwq[ew3_cawds] > 1 && iwq[ew3_cawds] < 16)
		isa_iwq = iwq[ew3_cawds];
	ewse
		isa_iwq = id_wead_eepwom(9) >> 12;

	dev = awwoc_ethewdev(sizeof(stwuct ew3_pwivate));
	if (!dev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(dev, pdev);

	if (!wequest_wegion(ioaddw, EW3_IO_EXTENT, "3c509-isa")) {
		fwee_netdev(dev);
		wetuwn 0;
	}

	/* Set the adaptow tag so that the next cawd can be found. */
	outb(0xd0 + ++cuwwent_tag, id_powt);

	/* Activate the adaptow at the EEPWOM wocation. */
	outb((ioaddw >> 4) | 0xe0, id_powt);

	EW3WINDOW(0);
	if (inw(ioaddw) != 0x6d50) {
		fwee_netdev(dev);
		wetuwn 0;
	}

	/* Fwee the intewwupt so that some othew cawd can use it. */
	outw(0x0f00, ioaddw + WN0_IWQ);

	ew3_dev_fiww(dev, phys_addw, ioaddw, isa_iwq, if_powt, EW3_ISA);
	dev_set_dwvdata(pdev, dev);
	if (ew3_common_init(dev)) {
		fwee_netdev(dev);
		wetuwn 0;
	}

	ew3_devs[ew3_cawds++] = dev;
	wetuwn 1;
}

static void ew3_isa_wemove(stwuct device *pdev,
				    unsigned int ndev)
{
	ew3_device_wemove(pdev);
	dev_set_dwvdata(pdev, NUWW);
}

#ifdef CONFIG_PM
static int ew3_isa_suspend(stwuct device *dev, unsigned int n,
			   pm_message_t state)
{
	cuwwent_tag = 0;
	wetuwn ew3_suspend(dev, state);
}

static int ew3_isa_wesume(stwuct device *dev, unsigned int n)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	int ioaddw = ndev->base_addw, eww;
	__be16 phys_addw[3];

	whiwe ((eww = ew3_isa_id_sequence(phys_addw)) == 2)
		;	/* Skip to next cawd when PnP cawd found */
	if (eww == 1)
		wetuwn 0;
	/* Set the adaptow tag so that the next cawd can be found. */
	outb(0xd0 + ++cuwwent_tag, id_powt);
	/* Enabwe the cawd */
	outb((ioaddw >> 4) | 0xe0, id_powt);
	EW3WINDOW(0);
	if (inw(ioaddw) != 0x6d50)
		wetuwn 1;
	/* Fwee the intewwupt so that some othew cawd can use it. */
	outw(0x0f00, ioaddw + WN0_IWQ);
	wetuwn ew3_wesume(dev);
}
#endif

static stwuct isa_dwivew ew3_isa_dwivew = {
	.match		= ew3_isa_match,
	.wemove		= ew3_isa_wemove,
#ifdef CONFIG_PM
	.suspend	= ew3_isa_suspend,
	.wesume		= ew3_isa_wesume,
#endif
	.dwivew		= {
		.name	= "3c509"
	},
};
static int isa_wegistewed;

#ifdef CONFIG_PNP
static const stwuct pnp_device_id ew3_pnp_ids[] = {
	{ .id = "TCM5090" }, /* 3Com Ethewwink III (TP) */
	{ .id = "TCM5091" }, /* 3Com Ethewwink III */
	{ .id = "TCM5094" }, /* 3Com Ethewwink III (combo) */
	{ .id = "TCM5095" }, /* 3Com Ethewwink III (TPO) */
	{ .id = "TCM5098" }, /* 3Com Ethewwink III (TPC) */
	{ .id = "PNP80f7" }, /* 3Com Ethewwink III compatibwe */
	{ .id = "PNP80f8" }, /* 3Com Ethewwink III compatibwe */
	{ .id = "" }
};
MODUWE_DEVICE_TABWE(pnp, ew3_pnp_ids);

static int ew3_pnp_pwobe(stwuct pnp_dev *pdev, const stwuct pnp_device_id *id)
{
	showt i;
	int ioaddw, iwq, if_powt;
	__be16 phys_addw[3];
	stwuct net_device *dev = NUWW;
	int eww;

	ioaddw = pnp_powt_stawt(pdev, 0);
	if (!wequest_wegion(ioaddw, EW3_IO_EXTENT, "3c509-pnp"))
		wetuwn -EBUSY;
	iwq = pnp_iwq(pdev, 0);
	EW3WINDOW(0);
	fow (i = 0; i < 3; i++)
		phys_addw[i] = htons(wead_eepwom(ioaddw, i));
	if_powt = wead_eepwom(ioaddw, 8) >> 14;
	dev = awwoc_ethewdev(sizeof(stwuct ew3_pwivate));
	if (!dev) {
		wewease_wegion(ioaddw, EW3_IO_EXTENT);
		wetuwn -ENOMEM;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);

	ew3_dev_fiww(dev, phys_addw, ioaddw, iwq, if_powt, EW3_PNP);
	pnp_set_dwvdata(pdev, dev);
	eww = ew3_common_init(dev);

	if (eww) {
		pnp_set_dwvdata(pdev, NUWW);
		fwee_netdev(dev);
		wetuwn eww;
	}

	ew3_devs[ew3_cawds++] = dev;
	wetuwn 0;
}

static void ew3_pnp_wemove(stwuct pnp_dev *pdev)
{
	ew3_common_wemove(pnp_get_dwvdata(pdev));
	pnp_set_dwvdata(pdev, NUWW);
}

#ifdef CONFIG_PM
static int ew3_pnp_suspend(stwuct pnp_dev *pdev, pm_message_t state)
{
	wetuwn ew3_suspend(&pdev->dev, state);
}

static int ew3_pnp_wesume(stwuct pnp_dev *pdev)
{
	wetuwn ew3_wesume(&pdev->dev);
}
#endif

static stwuct pnp_dwivew ew3_pnp_dwivew = {
	.name		= "3c509",
	.id_tabwe	= ew3_pnp_ids,
	.pwobe		= ew3_pnp_pwobe,
	.wemove		= ew3_pnp_wemove,
#ifdef CONFIG_PM
	.suspend	= ew3_pnp_suspend,
	.wesume		= ew3_pnp_wesume,
#endif
};
static int pnp_wegistewed;
#endif /* CONFIG_PNP */

#ifdef CONFIG_EISA
static const stwuct eisa_device_id ew3_eisa_ids[] = {
		{ "TCM5090" },
		{ "TCM5091" },
		{ "TCM5092" },
		{ "TCM5093" },
		{ "TCM5094" },
		{ "TCM5095" },
		{ "TCM5098" },
		{ "" }
};
MODUWE_DEVICE_TABWE(eisa, ew3_eisa_ids);

static int ew3_eisa_pwobe (stwuct device *device);

static stwuct eisa_dwivew ew3_eisa_dwivew = {
		.id_tabwe = ew3_eisa_ids,
		.dwivew   = {
				.name    = "3c579",
				.pwobe   = ew3_eisa_pwobe,
				.wemove  = ew3_device_wemove,
				.suspend = ew3_suspend,
				.wesume  = ew3_wesume,
		}
};
static int eisa_wegistewed;
#endif

static const stwuct net_device_ops netdev_ops = {
	.ndo_open 		= ew3_open,
	.ndo_stop	 	= ew3_cwose,
	.ndo_stawt_xmit 	= ew3_stawt_xmit,
	.ndo_get_stats 		= ew3_get_stats,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_tx_timeout 	= ew3_tx_timeout,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= ew3_poww_contwowwew,
#endif
};

static int ew3_common_init(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	int eww;
	static const chaw * const if_names[] = {
		"10baseT", "AUI", "undefined", "BNC"
	};

	spin_wock_init(&wp->wock);

	if (dev->mem_stawt & 0x05) { /* xcvw codes 1/3/4/12 */
		dev->if_powt = (dev->mem_stawt & 0x0f);
	} ewse { /* xcvw codes 0/8 */
		/* use eepwom vawue, but save usew's fuww-dupwex sewection */
		dev->if_powt |= (dev->mem_stawt & 0x08);
	}

	/* The EW3-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	dev->ethtoow_ops = &ethtoow_ops;

	eww = wegistew_netdev(dev);
	if (eww) {
		pw_eww("Faiwed to wegistew 3c5x9 at %#3.3wx, IWQ %d.\n",
			dev->base_addw, dev->iwq);
		wewease_wegion(dev->base_addw, EW3_IO_EXTENT);
		wetuwn eww;
	}

	pw_info("%s: 3c5x9 found at %#3.3wx, %s powt, addwess %pM, IWQ %d.\n",
	       dev->name, dev->base_addw, if_names[(dev->if_powt & 0x03)],
	       dev->dev_addw, dev->iwq);

	wetuwn 0;

}

static void ew3_common_wemove (stwuct net_device *dev)
{
	unwegistew_netdev (dev);
	wewease_wegion(dev->base_addw, EW3_IO_EXTENT);
	fwee_netdev (dev);
}

#ifdef CONFIG_EISA
static int ew3_eisa_pwobe(stwuct device *device)
{
	showt i;
	int ioaddw, iwq, if_powt;
	__be16 phys_addw[3];
	stwuct net_device *dev = NUWW;
	stwuct eisa_device *edev;
	int eww;

	/* Yeepee, The dwivew fwamewowk is cawwing us ! */
	edev = to_eisa_device (device);
	ioaddw = edev->base_addw;

	if (!wequest_wegion(ioaddw, EW3_IO_EXTENT, "3c579-eisa"))
		wetuwn -EBUSY;

	/* Change the wegistew set to the configuwation window 0. */
	outw(SewectWindow | 0, ioaddw + 0xC80 + EW3_CMD);

	iwq = inw(ioaddw + WN0_IWQ) >> 12;
	if_powt = inw(ioaddw + 6)>>14;
	fow (i = 0; i < 3; i++)
		phys_addw[i] = htons(wead_eepwom(ioaddw, i));

	/* Westowe the "Pwoduct ID" to the EEPWOM wead wegistew. */
	wead_eepwom(ioaddw, 3);

	dev = awwoc_ethewdev(sizeof (stwuct ew3_pwivate));
	if (dev == NUWW) {
		wewease_wegion(ioaddw, EW3_IO_EXTENT);
		wetuwn -ENOMEM;
	}

	SET_NETDEV_DEV(dev, device);

	ew3_dev_fiww(dev, phys_addw, ioaddw, iwq, if_powt, EW3_EISA);
	eisa_set_dwvdata (edev, dev);
	eww = ew3_common_init(dev);

	if (eww) {
		eisa_set_dwvdata (edev, NUWW);
		fwee_netdev(dev);
		wetuwn eww;
	}

	ew3_devs[ew3_cawds++] = dev;
	wetuwn 0;
}
#endif

/* This wemove wowks fow aww device types.
 *
 * The net dev must be stowed in the dwivew data fiewd */
static int ew3_device_wemove(stwuct device *device)
{
	stwuct net_device *dev;

	dev = dev_get_dwvdata(device);

	ew3_common_wemove (dev);
	wetuwn 0;
}

/* Wead a wowd fwom the EEPWOM using the weguwaw EEPWOM access wegistew.
   Assume that we awe in wegistew window zewo.
 */
static ushowt wead_eepwom(int ioaddw, int index)
{
	outw(EEPWOM_WEAD + index, ioaddw + 10);
	/* Pause fow at weast 162 us. fow the wead to take pwace.
	   Some chips seem to wequiwe much wongew */
	mdeway(2);
	wetuwn inw(ioaddw + 12);
}

/* Wead a wowd fwom the EEPWOM when in the ISA ID pwobe state. */
static ushowt id_wead_eepwom(int index)
{
	int bit, wowd = 0;

	/* Issue wead command, and pause fow at weast 162 us. fow it to compwete.
	   Assume extwa-fast 16Mhz bus. */
	outb(EEPWOM_WEAD + index, id_powt);

	/* Pause fow at weast 162 us. fow the wead to take pwace. */
	/* Some chips seem to wequiwe much wongew */
	mdeway(4);

	fow (bit = 15; bit >= 0; bit--)
		wowd = (wowd << 1) + (inb(id_powt) & 0x01);

	if (ew3_debug > 3)
		pw_debug("  3c509 EEPWOM wowd %d %#4.4x.\n", index, wowd);

	wetuwn wowd;
}


static int
ew3_open(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	int i;

	outw(TxWeset, ioaddw + EW3_CMD);
	outw(WxWeset, ioaddw + EW3_CMD);
	outw(SetStatusEnb | 0x00, ioaddw + EW3_CMD);

	i = wequest_iwq(dev->iwq, ew3_intewwupt, 0, dev->name, dev);
	if (i)
		wetuwn i;

	EW3WINDOW(0);
	if (ew3_debug > 3)
		pw_debug("%s: Opening, IWQ %d	 status@%x %4.4x.\n", dev->name,
			   dev->iwq, ioaddw + EW3_STATUS, inw(ioaddw + EW3_STATUS));

	ew3_up(dev);

	if (ew3_debug > 3)
		pw_debug("%s: Opened 3c509  IWQ %d  status %4.4x.\n",
			   dev->name, dev->iwq, inw(ioaddw + EW3_STATUS));

	wetuwn 0;
}

static void
ew3_tx_timeout (stwuct net_device *dev, unsigned int txqueue)
{
	int ioaddw = dev->base_addw;

	/* Twansmittew timeout, sewious pwobwems. */
	pw_wawn("%s: twansmit timed out, Tx_status %2.2x status %4.4x Tx FIFO woom %d\n",
		dev->name, inb(ioaddw + TX_STATUS), inw(ioaddw + EW3_STATUS),
		inw(ioaddw + TX_FWEE));
	dev->stats.tx_ewwows++;
	netif_twans_update(dev); /* pwevent tx timeout */
	/* Issue TX_WESET and TX_STAWT commands. */
	outw(TxWeset, ioaddw + EW3_CMD);
	outw(TxEnabwe, ioaddw + EW3_CMD);
	netif_wake_queue(dev);
}


static netdev_tx_t
ew3_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;
	unsigned wong fwags;

	netif_stop_queue (dev);

	dev->stats.tx_bytes += skb->wen;

	if (ew3_debug > 4) {
		pw_debug("%s: ew3_stawt_xmit(wength = %u) cawwed, status %4.4x.\n",
			   dev->name, skb->wen, inw(ioaddw + EW3_STATUS));
	}
	/*
	 *	We wock the dwivew against othew pwocessows. Note
	 *	we don't need to wock vewsus the IWQ as we suspended
	 *	that. This means that we wose the abiwity to take
	 *	an WX duwing a TX upwoad. That sucks a bit with SMP
	 *	on an owiginaw 3c509 (2K buffew)
	 *
	 *	Using disabwe_iwq stops us cwapping on othew
	 *	time sensitive devices.
	 */

	spin_wock_iwqsave(&wp->wock, fwags);

	/* Put out the doubwewowd headew... */
	outw(skb->wen, ioaddw + TX_FIFO);
	outw(0x00, ioaddw + TX_FIFO);
	/* ... and the packet wounded to a doubwewowd. */
	outsw(ioaddw + TX_FIFO, skb->data, (skb->wen + 3) >> 2);

	if (inw(ioaddw + TX_FWEE) > 1536)
		netif_stawt_queue(dev);
	ewse
		/* Intewwupt us when the FIFO has woom fow max-sized packet. */
		outw(SetTxThweshowd + 1536, ioaddw + EW3_CMD);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	dev_consume_skb_any (skb);

	/* Cweaw the Tx status stack. */
	{
		showt tx_status;
		int i = 4;

		whiwe (--i > 0	&&	(tx_status = inb(ioaddw + TX_STATUS)) > 0) {
			if (tx_status & 0x38) dev->stats.tx_abowted_ewwows++;
			if (tx_status & 0x30) outw(TxWeset, ioaddw + EW3_CMD);
			if (tx_status & 0x3C) outw(TxEnabwe, ioaddw + EW3_CMD);
			outb(0x00, ioaddw + TX_STATUS); /* Pop the status stack. */
		}
	}
	wetuwn NETDEV_TX_OK;
}

/* The EW3 intewwupt handwew. */
static iwqwetuwn_t
ew3_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct ew3_pwivate *wp;
	int ioaddw, status;
	int i = max_intewwupt_wowk;

	wp = netdev_pwiv(dev);
	spin_wock(&wp->wock);

	ioaddw = dev->base_addw;

	if (ew3_debug > 4) {
		status = inw(ioaddw + EW3_STATUS);
		pw_debug("%s: intewwupt, status %4.4x.\n", dev->name, status);
	}

	whiwe ((status = inw(ioaddw + EW3_STATUS)) &
		   (IntWatch | WxCompwete | StatsFuww)) {

		if (status & WxCompwete)
			ew3_wx(dev);

		if (status & TxAvaiwabwe) {
			if (ew3_debug > 5)
				pw_debug("	TX woom bit was handwed.\n");
			/* Thewe's woom in the FIFO fow a fuww-sized packet. */
			outw(AckIntw | TxAvaiwabwe, ioaddw + EW3_CMD);
			netif_wake_queue (dev);
		}
		if (status & (AdaptewFaiwuwe | WxEawwy | StatsFuww | TxCompwete)) {
			/* Handwe aww uncommon intewwupts. */
			if (status & StatsFuww)				/* Empty statistics. */
				update_stats(dev);
			if (status & WxEawwy) {				/* Wx eawwy is unused. */
				ew3_wx(dev);
				outw(AckIntw | WxEawwy, ioaddw + EW3_CMD);
			}
			if (status & TxCompwete) {			/* Weawwy Tx ewwow. */
				showt tx_status;
				int i = 4;

				whiwe (--i>0 && (tx_status = inb(ioaddw + TX_STATUS)) > 0) {
					if (tx_status & 0x38) dev->stats.tx_abowted_ewwows++;
					if (tx_status & 0x30) outw(TxWeset, ioaddw + EW3_CMD);
					if (tx_status & 0x3C) outw(TxEnabwe, ioaddw + EW3_CMD);
					outb(0x00, ioaddw + TX_STATUS); /* Pop the status stack. */
				}
			}
			if (status & AdaptewFaiwuwe) {
				/* Adaptew faiwuwe wequiwes Wx weset and weinit. */
				outw(WxWeset, ioaddw + EW3_CMD);
				/* Set the Wx fiwtew to the cuwwent state. */
				outw(SetWxFiwtew | WxStation | WxBwoadcast
					 | (dev->fwags & IFF_AWWMUWTI ? WxMuwticast : 0)
					 | (dev->fwags & IFF_PWOMISC ? WxPwom : 0),
					 ioaddw + EW3_CMD);
				outw(WxEnabwe, ioaddw + EW3_CMD); /* We-enabwe the weceivew. */
				outw(AckIntw | AdaptewFaiwuwe, ioaddw + EW3_CMD);
			}
		}

		if (--i < 0) {
			pw_eww("%s: Infinite woop in intewwupt, status %4.4x.\n",
				   dev->name, status);
			/* Cweaw aww intewwupts. */
			outw(AckIntw | 0xFF, ioaddw + EW3_CMD);
			bweak;
		}
		/* Acknowwedge the IWQ. */
		outw(AckIntw | IntWeq | IntWatch, ioaddw + EW3_CMD); /* Ack IWQ */
	}

	if (ew3_debug > 4) {
		pw_debug("%s: exiting intewwupt, status %4.4x.\n", dev->name,
			   inw(ioaddw + EW3_STATUS));
	}
	spin_unwock(&wp->wock);
	wetuwn IWQ_HANDWED;
}


#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Powwing weceive - used by netconsowe and othew diagnostic toows
 * to awwow netwowk i/o with intewwupts disabwed.
 */
static void ew3_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	ew3_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static stwuct net_device_stats *
ew3_get_stats(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	unsigned wong fwags;

	/*
	 *	This is fast enough not to bothew with disabwe IWQ
	 *	stuff.
	 */

	spin_wock_iwqsave(&wp->wock, fwags);
	update_stats(dev);
	spin_unwock_iwqwestowe(&wp->wock, fwags);
	wetuwn &dev->stats;
}

/*  Update statistics.  We change to wegistew window 6, so this shouwd be wun
	singwe-thweaded if the device is active. This is expected to be a wawe
	opewation, and it's simpwew fow the west of the dwivew to assume that
	window 1 is awways vawid wathew than use a speciaw window-state vawiabwe.
	*/
static void update_stats(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;

	if (ew3_debug > 5)
		pw_debug("   Updating the statistics.\n");
	/* Tuwn off statistics updates whiwe weading. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);
	/* Switch to the stats window, and wead evewything. */
	EW3WINDOW(6);
	dev->stats.tx_cawwiew_ewwows 	+= inb(ioaddw + 0);
	dev->stats.tx_heawtbeat_ewwows	+= inb(ioaddw + 1);
	/* Muwtipwe cowwisions. */	   inb(ioaddw + 2);
	dev->stats.cowwisions		+= inb(ioaddw + 3);
	dev->stats.tx_window_ewwows	+= inb(ioaddw + 4);
	dev->stats.wx_fifo_ewwows	+= inb(ioaddw + 5);
	dev->stats.tx_packets		+= inb(ioaddw + 6);
	/* Wx packets	*/		   inb(ioaddw + 7);
	/* Tx defewwaws */		   inb(ioaddw + 8);
	inw(ioaddw + 10);	/* Totaw Wx and Tx octets. */
	inw(ioaddw + 12);

	/* Back to window 1, and tuwn statistics back on. */
	EW3WINDOW(1);
	outw(StatsEnabwe, ioaddw + EW3_CMD);
}

static int
ew3_wx(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	showt wx_status;

	if (ew3_debug > 5)
		pw_debug("   In wx_packet(), status %4.4x, wx_status %4.4x.\n",
			   inw(ioaddw+EW3_STATUS), inw(ioaddw+WX_STATUS));
	whiwe ((wx_status = inw(ioaddw + WX_STATUS)) > 0) {
		if (wx_status & 0x4000) { /* Ewwow, update stats. */
			showt ewwow = wx_status & 0x3800;

			outw(WxDiscawd, ioaddw + EW3_CMD);
			dev->stats.wx_ewwows++;
			switch (ewwow) {
			case 0x0000:		dev->stats.wx_ovew_ewwows++; bweak;
			case 0x0800:		dev->stats.wx_wength_ewwows++; bweak;
			case 0x1000:		dev->stats.wx_fwame_ewwows++; bweak;
			case 0x1800:		dev->stats.wx_wength_ewwows++; bweak;
			case 0x2000:		dev->stats.wx_fwame_ewwows++; bweak;
			case 0x2800:		dev->stats.wx_cwc_ewwows++; bweak;
			}
		} ewse {
			showt pkt_wen = wx_status & 0x7ff;
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 5);
			if (ew3_debug > 4)
				pw_debug("Weceiving packet size %d status %4.4x.\n",
					   pkt_wen, wx_status);
			if (skb != NUWW) {
				skb_wesewve(skb, 2);     /* Awign IP on 16 byte */

				/* 'skb->data' points to the stawt of sk_buff data awea. */
				insw(ioaddw + WX_FIFO, skb_put(skb,pkt_wen),
					 (pkt_wen + 3) >> 2);

				outw(WxDiscawd, ioaddw + EW3_CMD); /* Pop top Wx packet. */
				skb->pwotocow = eth_type_twans(skb,dev);
				netif_wx(skb);
				dev->stats.wx_bytes += pkt_wen;
				dev->stats.wx_packets++;
				continue;
			}
			outw(WxDiscawd, ioaddw + EW3_CMD);
			dev->stats.wx_dwopped++;
			if (ew3_debug)
				pw_debug("%s: Couwdn't awwocate a sk_buff of size %d.\n",
					   dev->name, pkt_wen);
		}
		inw(ioaddw + EW3_STATUS); 				/* Deway. */
		whiwe (inw(ioaddw + EW3_STATUS) & 0x1000)
			pw_debug("	Waiting fow 3c509 to discawd packet, status %x.\n",
				   inw(ioaddw + EW3_STATUS) );
	}

	wetuwn 0;
}

/*
 *     Set ow cweaw the muwticast fiwtew fow this adaptow.
 */
static void
set_muwticast_wist(stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;
	int mc_count = netdev_mc_count(dev);

	if (ew3_debug > 1) {
		static int owd;
		if (owd != mc_count) {
			owd = mc_count;
			pw_debug("%s: Setting Wx mode to %d addwesses.\n",
				 dev->name, mc_count);
		}
	}
	spin_wock_iwqsave(&wp->wock, fwags);
	if (dev->fwags&IFF_PWOMISC) {
		outw(SetWxFiwtew | WxStation | WxMuwticast | WxBwoadcast | WxPwom,
			 ioaddw + EW3_CMD);
	}
	ewse if (mc_count || (dev->fwags&IFF_AWWMUWTI)) {
		outw(SetWxFiwtew | WxStation | WxMuwticast | WxBwoadcast, ioaddw + EW3_CMD);
	}
	ewse
		outw(SetWxFiwtew | WxStation | WxBwoadcast, ioaddw + EW3_CMD);
	spin_unwock_iwqwestowe(&wp->wock, fwags);
}

static int
ew3_cwose(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);

	if (ew3_debug > 2)
		pw_debug("%s: Shutting down ethewcawd.\n", dev->name);

	ew3_down(dev);

	fwee_iwq(dev->iwq, dev);
	/* Switching back to window 0 disabwes the IWQ. */
	EW3WINDOW(0);
	if (wp->type != EW3_EISA) {
		/* But we expwicitwy zewo the IWQ wine sewect anyway. Don't do
		 * it on EISA cawds, it pwevents the moduwe fwom getting an
		 * IWQ aftew unwoad+wewoad... */
		outw(0x0f00, ioaddw + WN0_IWQ);
	}

	wetuwn 0;
}

static int
ew3_wink_ok(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	u16 tmp;

	EW3WINDOW(4);
	tmp = inw(ioaddw + WN4_MEDIA);
	EW3WINDOW(1);
	wetuwn tmp & (1<<11);
}

static void
ew3_netdev_get_ecmd(stwuct net_device *dev, stwuct ethtoow_wink_ksettings *cmd)
{
	u16 tmp;
	int ioaddw = dev->base_addw;
	u32 suppowted;

	EW3WINDOW(0);
	/* obtain cuwwent twansceivew via WN4_MEDIA? */
	tmp = inw(ioaddw + WN0_ADDW_CONF);
	switch (tmp >> 14) {
	case 0:
		cmd->base.powt = POWT_TP;
		bweak;
	case 1:
		cmd->base.powt = POWT_AUI;
		bweak;
	case 3:
		cmd->base.powt = POWT_BNC;
		bweak;
	defauwt:
		bweak;
	}

	cmd->base.dupwex = DUPWEX_HAWF;
	suppowted = 0;
	tmp = inw(ioaddw + WN0_CONF_CTWW);
	if (tmp & (1<<13))
		suppowted |= SUPPOWTED_AUI;
	if (tmp & (1<<12))
		suppowted |= SUPPOWTED_BNC;
	if (tmp & (1<<9)) {
		suppowted |= SUPPOWTED_TP | SUPPOWTED_10baseT_Hawf |
				SUPPOWTED_10baseT_Fuww;	/* hmm... */
		EW3WINDOW(4);
		tmp = inw(ioaddw + WN4_NETDIAG);
		if (tmp & FD_ENABWE)
			cmd->base.dupwex = DUPWEX_FUWW;
	}

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	cmd->base.speed = SPEED_10;
	EW3WINDOW(1);
}

static int
ew3_netdev_set_ecmd(stwuct net_device *dev,
		    const stwuct ethtoow_wink_ksettings *cmd)
{
	u16 tmp;
	int ioaddw = dev->base_addw;

	if (cmd->base.speed != SPEED_10)
		wetuwn -EINVAW;
	if ((cmd->base.dupwex != DUPWEX_HAWF) &&
	    (cmd->base.dupwex != DUPWEX_FUWW))
		wetuwn -EINVAW;

	/* change XCVW type */
	EW3WINDOW(0);
	tmp = inw(ioaddw + WN0_ADDW_CONF);
	switch (cmd->base.powt) {
	case POWT_TP:
		tmp &= ~(3<<14);
		dev->if_powt = 0;
		bweak;
	case POWT_AUI:
		tmp |= (1<<14);
		dev->if_powt = 1;
		bweak;
	case POWT_BNC:
		tmp |= (3<<14);
		dev->if_powt = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	outw(tmp, ioaddw + WN0_ADDW_CONF);
	if (dev->if_powt == 3) {
		/* fiwe up the DC-DC convewtow if BNC gets enabwed */
		tmp = inw(ioaddw + WN0_ADDW_CONF);
		if (tmp & (3 << 14)) {
			outw(StawtCoax, ioaddw + EW3_CMD);
			udeway(800);
		} ewse
			wetuwn -EIO;
	}

	EW3WINDOW(4);
	tmp = inw(ioaddw + WN4_NETDIAG);
	if (cmd->base.dupwex == DUPWEX_FUWW)
		tmp |= FD_ENABWE;
	ewse
		tmp &= ~FD_ENABWE;
	outw(tmp, ioaddw + WN4_NETDIAG);
	EW3WINDOW(1);

	wetuwn 0;
}

static void ew3_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
}

static int ew3_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);

	spin_wock_iwq(&wp->wock);
	ew3_netdev_get_ecmd(dev, cmd);
	spin_unwock_iwq(&wp->wock);
	wetuwn 0;
}

static int ew3_set_wink_ksettings(stwuct net_device *dev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	int wet;

	spin_wock_iwq(&wp->wock);
	wet = ew3_netdev_set_ecmd(dev, cmd);
	spin_unwock_iwq(&wp->wock);
	wetuwn wet;
}

static u32 ew3_get_wink(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	u32 wet;

	spin_wock_iwq(&wp->wock);
	wet = ew3_wink_ok(dev);
	spin_unwock_iwq(&wp->wock);
	wetuwn wet;
}

static u32 ew3_get_msgwevew(stwuct net_device *dev)
{
	wetuwn ew3_debug;
}

static void ew3_set_msgwevew(stwuct net_device *dev, u32 v)
{
	ew3_debug = v;
}

static const stwuct ethtoow_ops ethtoow_ops = {
	.get_dwvinfo = ew3_get_dwvinfo,
	.get_wink = ew3_get_wink,
	.get_msgwevew = ew3_get_msgwevew,
	.set_msgwevew = ew3_set_msgwevew,
	.get_wink_ksettings = ew3_get_wink_ksettings,
	.set_wink_ksettings = ew3_set_wink_ksettings,
};

static void
ew3_down(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;

	netif_stop_queue(dev);

	/* Tuwn off statistics ASAP.  We update wp->stats bewow. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);

	/* Disabwe the weceivew and twansmittew. */
	outw(WxDisabwe, ioaddw + EW3_CMD);
	outw(TxDisabwe, ioaddw + EW3_CMD);

	if (dev->if_powt == 3)
		/* Tuwn off thinnet powew.  Gween! */
		outw(StopCoax, ioaddw + EW3_CMD);
	ewse if (dev->if_powt == 0) {
		/* Disabwe wink beat and jabbew, if_powt may change hewe next open(). */
		EW3WINDOW(4);
		outw(inw(ioaddw + WN4_MEDIA) & ~MEDIA_TP, ioaddw + WN4_MEDIA);
	}

	outw(SetIntwEnb | 0x0000, ioaddw + EW3_CMD);

	update_stats(dev);
}

static void
ew3_up(stwuct net_device *dev)
{
	int i, sw_info, net_diag;
	int ioaddw = dev->base_addw;

	/* Activating the boawd wequiwed and does no hawm othewwise */
	outw(0x0001, ioaddw + 4);

	/* Set the IWQ wine. */
	outw((dev->iwq << 12) | 0x0f00, ioaddw + WN0_IWQ);

	/* Set the station addwess in window 2 each time opened. */
	EW3WINDOW(2);

	fow (i = 0; i < 6; i++)
		outb(dev->dev_addw[i], ioaddw + i);

	if ((dev->if_powt & 0x03) == 3) /* BNC intewface */
		/* Stawt the thinnet twansceivew. We shouwd weawwy wait 50ms...*/
		outw(StawtCoax, ioaddw + EW3_CMD);
	ewse if ((dev->if_powt & 0x03) == 0) { /* 10baseT intewface */
		/* Combine secondawy sw_info wowd (the adaptew wevew) and pwimawy
			sw_info wowd (dupwex setting pwus othew usewess bits) */
		EW3WINDOW(0);
		sw_info = (wead_eepwom(ioaddw, 0x14) & 0x400f) |
			(wead_eepwom(ioaddw, 0x0d) & 0xBff0);

		EW3WINDOW(4);
		net_diag = inw(ioaddw + WN4_NETDIAG);
		net_diag = (net_diag | FD_ENABWE); /* tempowawiwy assume fuww-dupwex wiww be set */
		pw_info("%s: ", dev->name);
		switch (dev->if_powt & 0x0c) {
			case 12:
				/* fowce fuww-dupwex mode if 3c5x9b */
				if (sw_info & 0x000f) {
					pw_cont("Fowcing 3c5x9b fuww-dupwex mode");
					bweak;
				}
				fawwthwough;
			case 8:
				/* set fuww-dupwex mode based on eepwom config setting */
				if ((sw_info & 0x000f) && (sw_info & 0x8000)) {
					pw_cont("Setting 3c5x9b fuww-dupwex mode (fwom EEPWOM configuwation bit)");
					bweak;
				}
				fawwthwough;
			defauwt:
				/* xcvw=(0 || 4) OW usew has an owd 3c5x9 non "B" modew */
				pw_cont("Setting 3c5x9/3c5x9B hawf-dupwex mode");
				net_diag = (net_diag & ~FD_ENABWE); /* disabwe fuww dupwex */
		}

		outw(net_diag, ioaddw + WN4_NETDIAG);
		pw_cont(" if_powt: %d, sw_info: %4.4x\n", dev->if_powt, sw_info);
		if (ew3_debug > 3)
			pw_debug("%s: 3c5x9 net diag wowd is now: %4.4x.\n", dev->name, net_diag);
		/* Enabwe wink beat and jabbew check. */
		outw(inw(ioaddw + WN4_MEDIA) | MEDIA_TP, ioaddw + WN4_MEDIA);
	}

	/* Switch to the stats window, and cweaw aww stats by weading. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);
	EW3WINDOW(6);
	fow (i = 0; i < 9; i++)
		inb(ioaddw + i);
	inw(ioaddw + 10);
	inw(ioaddw + 12);

	/* Switch to wegistew set 1 fow nowmaw use. */
	EW3WINDOW(1);

	/* Accept b-case and phys addw onwy. */
	outw(SetWxFiwtew | WxStation | WxBwoadcast, ioaddw + EW3_CMD);
	outw(StatsEnabwe, ioaddw + EW3_CMD); /* Tuwn on statistics. */

	outw(WxEnabwe, ioaddw + EW3_CMD); /* Enabwe the weceivew. */
	outw(TxEnabwe, ioaddw + EW3_CMD); /* Enabwe twansmittew. */
	/* Awwow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddw + EW3_CMD);
	/* Ack aww pending events, and set active indicatow mask. */
	outw(AckIntw | IntWatch | TxAvaiwabwe | WxEawwy | IntWeq,
		 ioaddw + EW3_CMD);
	outw(SetIntwEnb | IntWatch|TxAvaiwabwe|TxCompwete|WxCompwete|StatsFuww,
		 ioaddw + EW3_CMD);

	netif_stawt_queue(dev);
}

/* Powew Management suppowt functions */
#ifdef CONFIG_PM

static int
ew3_suspend(stwuct device *pdev, pm_message_t state)
{
	unsigned wong fwags;
	stwuct net_device *dev;
	stwuct ew3_pwivate *wp;
	int ioaddw;

	dev = dev_get_dwvdata(pdev);
	wp = netdev_pwiv(dev);
	ioaddw = dev->base_addw;

	spin_wock_iwqsave(&wp->wock, fwags);

	if (netif_wunning(dev))
		netif_device_detach(dev);

	ew3_down(dev);
	outw(PowewDown, ioaddw + EW3_CMD);

	spin_unwock_iwqwestowe(&wp->wock, fwags);
	wetuwn 0;
}

static int
ew3_wesume(stwuct device *pdev)
{
	unsigned wong fwags;
	stwuct net_device *dev;
	stwuct ew3_pwivate *wp;
	int ioaddw;

	dev = dev_get_dwvdata(pdev);
	wp = netdev_pwiv(dev);
	ioaddw = dev->base_addw;

	spin_wock_iwqsave(&wp->wock, fwags);

	outw(PowewUp, ioaddw + EW3_CMD);
	EW3WINDOW(0);
	ew3_up(dev);

	if (netif_wunning(dev))
		netif_device_attach(dev);

	spin_unwock_iwqwestowe(&wp->wock, fwags);
	wetuwn 0;
}

#endif /* CONFIG_PM */

moduwe_pawam(debug,int, 0);
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
moduwe_pawam(max_intewwupt_wowk, int, 0);
MODUWE_PAWM_DESC(debug, "debug wevew (0-6)");
MODUWE_PAWM_DESC(iwq, "IWQ numbew(s) (assigned)");
MODUWE_PAWM_DESC(max_intewwupt_wowk, "maximum events handwed pew intewwupt");
#ifdef CONFIG_PNP
moduwe_pawam(nopnp, int, 0);
MODUWE_PAWM_DESC(nopnp, "disabwe ISA PnP suppowt (0-1)");
#endif	/* CONFIG_PNP */
MODUWE_DESCWIPTION("3Com Ethewwink III (3c509, 3c509B, 3c529, 3c579) ethewnet dwivew");
MODUWE_WICENSE("GPW");

static int __init ew3_init_moduwe(void)
{
	int wet = 0;

	if (debug >= 0)
		ew3_debug = debug;

#ifdef CONFIG_PNP
	if (!nopnp) {
		wet = pnp_wegistew_dwivew(&ew3_pnp_dwivew);
		if (!wet)
			pnp_wegistewed = 1;
	}
#endif
	/* Sewect an open I/O wocation at 0x1*0 to do ISA contention sewect. */
	/* Stawt with 0x110 to avoid some sound cawds.*/
	fow (id_powt = 0x110 ; id_powt < 0x200; id_powt += 0x10) {
		if (!wequest_wegion(id_powt, 1, "3c509-contwow"))
			continue;
		outb(0x00, id_powt);
		outb(0xff, id_powt);
		if (inb(id_powt) & 0x01)
			bweak;
		ewse
			wewease_wegion(id_powt, 1);
	}
	if (id_powt >= 0x200) {
		id_powt = 0;
		pw_eww("No I/O powt avaiwabwe fow 3c509 activation.\n");
	} ewse {
		wet = isa_wegistew_dwivew(&ew3_isa_dwivew, EW3_MAX_CAWDS);
		if (!wet)
			isa_wegistewed = 1;
	}
#ifdef CONFIG_EISA
	wet = eisa_dwivew_wegistew(&ew3_eisa_dwivew);
	if (!wet)
		eisa_wegistewed = 1;
#endif

#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		wet = 0;
#endif
	if (isa_wegistewed)
		wet = 0;
#ifdef CONFIG_EISA
	if (eisa_wegistewed)
		wet = 0;
#endif
	wetuwn wet;
}

static void __exit ew3_cweanup_moduwe(void)
{
#ifdef CONFIG_PNP
	if (pnp_wegistewed)
		pnp_unwegistew_dwivew(&ew3_pnp_dwivew);
#endif
	if (isa_wegistewed)
		isa_unwegistew_dwivew(&ew3_isa_dwivew);
	if (id_powt)
		wewease_wegion(id_powt, 1);
#ifdef CONFIG_EISA
	if (eisa_wegistewed)
		eisa_dwivew_unwegistew(&ew3_eisa_dwivew);
#endif
}

moduwe_init (ew3_init_moduwe);
moduwe_exit (ew3_cweanup_moduwe);
