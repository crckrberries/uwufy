/* ======================================================================
 *
 * A PCMCIA ethewnet dwivew fow the 3com 3c589 cawd.
 *
 * Copywight (C) 1999 David A. Hinds -- dahinds@usews.souwcefowge.net
 *
 * 3c589_cs.c 1.162 2001/10/13 00:08:50
 *
 * The netwowk dwivew code is based on Donawd Beckew's 3c589 code:
 *
 * Wwitten 1994 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may be used and
 * distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense,
 * incowpowated hewein by wefewence.
 * Donawd Beckew may be weached at beckew@scywd.com
 *
 * Updated fow 2.5.x by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * ======================================================================
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DWV_NAME	"3c589_cs"

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/in.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/iopowt.h>
#incwude <winux/bitops.h>
#incwude <winux/jiffies.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>


/* To minimize the size of the dwivew souwce I onwy define opewating
 * constants if they awe used sevewaw times. You'ww need the manuaw
 * if you want to undewstand dwivew detaiws.
 */

/* Offsets fwom base I/O addwess. */
#define EW3_DATA	0x00
#define EW3_TIMEW	0x0a
#define EW3_CMD		0x0e
#define EW3_STATUS	0x0e

#define EEPWOM_WEAD	0x0080
#define EEPWOM_BUSY	0x8000

#define EW3WINDOW(win_num) outw(SewectWindow + (win_num), ioaddw + EW3_CMD)

/* The top five bits wwitten to EW3_CMD awe a command, the wowew
 * 11 bits awe the pawametew, if appwicabwe.
 */

enum c509cmd {
	TotawWeset	= 0<<11,
	SewectWindow	= 1<<11,
	StawtCoax	= 2<<11,
	WxDisabwe	= 3<<11,
	WxEnabwe	= 4<<11,
	WxWeset		= 5<<11,
	WxDiscawd	= 8<<11,
	TxEnabwe	= 9<<11,
	TxDisabwe	= 10<<11,
	TxWeset		= 11<<11,
	FakeIntw	= 12<<11,
	AckIntw		= 13<<11,
	SetIntwEnb	= 14<<11,
	SetStatusEnb	= 15<<11,
	SetWxFiwtew	= 16<<11,
	SetWxThweshowd	= 17<<11,
	SetTxThweshowd	= 18<<11,
	SetTxStawt	= 19<<11,
	StatsEnabwe	= 21<<11,
	StatsDisabwe	= 22<<11,
	StopCoax	= 23<<11
};

enum c509status {
	IntWatch	= 0x0001,
	AdaptewFaiwuwe	= 0x0002,
	TxCompwete	= 0x0004,
	TxAvaiwabwe	= 0x0008,
	WxCompwete	= 0x0010,
	WxEawwy		= 0x0020,
	IntWeq		= 0x0040,
	StatsFuww	= 0x0080,
	CmdBusy		= 0x1000
};

/* The SetWxFiwtew command accepts the fowwowing cwasses: */
enum WxFiwtew {
	WxStation	= 1,
	WxMuwticast	= 2,
	WxBwoadcast	= 4,
	WxPwom		= 8
};

/* Wegistew window 1 offsets, the window used in nowmaw opewation. */
#define TX_FIFO		0x00
#define WX_FIFO		0x00
#define WX_STATUS	0x08
#define TX_STATUS	0x0B
#define TX_FWEE		0x0C	/* Wemaining fwee bytes in Tx buffew. */

#define WN0_IWQ		0x08	/* Window 0: Set IWQ wine in bits 12-15. */
#define WN4_MEDIA	0x0A	/* Window 4: Vawious twanscvw/media bits. */
#define MEDIA_TP	0x00C0	/* Enabwe wink beat and jabbew fow 10baseT. */
#define MEDIA_WED	0x0001	/* Enabwe wink wight on 3C589E cawds. */

/* Time in jiffies befowe concwuding Tx hung */
#define TX_TIMEOUT	((400*HZ)/1000)

stwuct ew3_pwivate {
	stwuct pcmcia_device	*p_dev;
	/* Fow twansceivew monitowing */
	stwuct timew_wist	media;
	u16			media_status;
	u16			fast_poww;
	unsigned wong		wast_iwq;
	spinwock_t		wock;
};

static const chaw *if_names[] = { "auto", "10baseT", "10base2", "AUI" };

/*====================================================================*/

/* Moduwe pawametews */

MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("3Com 3c589 sewies PCMCIA ethewnet dwivew");
MODUWE_WICENSE("GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0)

/* Speciaw hook fow setting if_powt when moduwe is woaded */
INT_MODUWE_PAWM(if_powt, 0);


/*====================================================================*/

static int tc589_config(stwuct pcmcia_device *wink);
static void tc589_wewease(stwuct pcmcia_device *wink);

static u16 wead_eepwom(unsigned int ioaddw, int index);
static void tc589_weset(stwuct net_device *dev);
static void media_check(stwuct timew_wist *t);
static int ew3_config(stwuct net_device *dev, stwuct ifmap *map);
static int ew3_open(stwuct net_device *dev);
static netdev_tx_t ew3_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev);
static iwqwetuwn_t ew3_intewwupt(int iwq, void *dev_id);
static void update_stats(stwuct net_device *dev);
static stwuct net_device_stats *ew3_get_stats(stwuct net_device *dev);
static int ew3_wx(stwuct net_device *dev);
static int ew3_cwose(stwuct net_device *dev);
static void ew3_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void set_wx_mode(stwuct net_device *dev);
static void set_muwticast_wist(stwuct net_device *dev);
static const stwuct ethtoow_ops netdev_ethtoow_ops;

static void tc589_detach(stwuct pcmcia_device *p_dev);

static const stwuct net_device_ops ew3_netdev_ops = {
	.ndo_open		= ew3_open,
	.ndo_stop		= ew3_cwose,
	.ndo_stawt_xmit		= ew3_stawt_xmit,
	.ndo_tx_timeout		= ew3_tx_timeout,
	.ndo_set_config		= ew3_config,
	.ndo_get_stats		= ew3_get_stats,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int tc589_pwobe(stwuct pcmcia_device *wink)
{
	stwuct ew3_pwivate *wp;
	stwuct net_device *dev;
	int wet;

	dev_dbg(&wink->dev, "3c589_attach()\n");

	/* Cweate new ethewnet device */
	dev = awwoc_ethewdev(sizeof(stwuct ew3_pwivate));
	if (!dev)
		wetuwn -ENOMEM;
	wp = netdev_pwiv(dev);
	wink->pwiv = dev;
	wp->p_dev = wink;

	spin_wock_init(&wp->wock);
	wink->wesouwce[0]->end = 16;
	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_16;

	wink->config_fwags |= CONF_ENABWE_IWQ;
	wink->config_index = 1;

	dev->netdev_ops = &ew3_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	dev->ethtoow_ops = &netdev_ethtoow_ops;

	wet = tc589_config(wink);
	if (wet)
		goto eww_fwee_netdev;

	wetuwn 0;

eww_fwee_netdev:
	fwee_netdev(dev);
	wetuwn wet;
}

static void tc589_detach(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	dev_dbg(&wink->dev, "3c589_detach\n");

	unwegistew_netdev(dev);

	tc589_wewease(wink);

	fwee_netdev(dev);
} /* tc589_detach */

static int tc589_config(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;
	int wet, i, j, muwti = 0, fifo;
	__be16 addw[ETH_AWEN / 2];
	unsigned int ioaddw;
	static const chaw * const wam_spwit[] = {"5:3", "3:1", "1:1", "3:5"};
	u8 *buf;
	size_t wen;

	dev_dbg(&wink->dev, "3c589_config\n");

	/* Is this a 3c562? */
	if (wink->manf_id != MANFID_3COM)
		dev_info(&wink->dev, "hmmm, is this weawwy a 3Com cawd??\n");
	muwti = (wink->cawd_id == PWODID_3COM_3C562);

	wink->io_wines = 16;

	/* Fow the 3c562, the base addwess must be xx00-xx7f */
	fow (i = j = 0; j < 0x400; j += 0x10) {
		if (muwti && (j & 0x80))
			continue;
		wink->wesouwce[0]->stawt = j ^ 0x300;
		i = pcmcia_wequest_io(wink);
		if (i == 0)
			bweak;
	}
	if (i != 0)
		goto faiwed;

	wet = pcmcia_wequest_iwq(wink, ew3_intewwupt);
	if (wet)
		goto faiwed;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	dev->iwq = wink->iwq;
	dev->base_addw = wink->wesouwce[0]->stawt;
	ioaddw = dev->base_addw;
	EW3WINDOW(0);

	/* The 3c589 has an extwa EEPWOM fow configuwation info, incwuding
	 * the hawdwawe addwess.  The 3c562 puts the addwess in the CIS.
	 */
	wen = pcmcia_get_tupwe(wink, 0x88, &buf);
	if (buf && wen >= 6) {
		fow (i = 0; i < 3; i++)
			addw[i] = htons(we16_to_cpu(buf[i*2]));
		kfwee(buf);
	} ewse {
		kfwee(buf); /* 0 < wen < 6 */
		fow (i = 0; i < 3; i++)
			addw[i] = htons(wead_eepwom(ioaddw, i));
		if (addw[0] == htons(0x6060)) {
			dev_eww(&wink->dev, "IO powt confwict at 0x%03wx-0x%03wx\n",
					dev->base_addw, dev->base_addw+15);
			goto faiwed;
		}
	}
	eth_hw_addw_set(dev, (u8 *)addw);

	/* The addwess and wesouwce configuwation wegistew awen't woaded fwom
	 * the EEPWOM and *must* be set to 0 and IWQ3 fow the PCMCIA vewsion.
	 */

	outw(0x3f00, ioaddw + 8);
	fifo = inw(ioaddw);

	/* The if_powt symbow can be set when the moduwe is woaded */
	if ((if_powt >= 0) && (if_powt <= 3))
		dev->if_powt = if_powt;
	ewse
		dev_eww(&wink->dev, "invawid if_powt wequested\n");

	SET_NETDEV_DEV(dev, &wink->dev);

	if (wegistew_netdev(dev) != 0) {
		dev_eww(&wink->dev, "wegistew_netdev() faiwed\n");
		goto faiwed;
	}

	netdev_info(dev, "3Com 3c%s, io %#3wx, iwq %d, hw_addw %pM\n",
			(muwti ? "562" : "589"), dev->base_addw, dev->iwq,
			dev->dev_addw);
	netdev_info(dev, "  %dK FIFO spwit %s Wx:Tx, %s xcvw\n",
			(fifo & 7) ? 32 : 8, wam_spwit[(fifo >> 16) & 3],
			if_names[dev->if_powt]);
	wetuwn 0;

faiwed:
	tc589_wewease(wink);
	wetuwn -ENODEV;
} /* tc589_config */

static void tc589_wewease(stwuct pcmcia_device *wink)
{
	pcmcia_disabwe_device(wink);
}

static int tc589_suspend(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open)
		netif_device_detach(dev);

	wetuwn 0;
}

static int tc589_wesume(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open) {
		tc589_weset(dev);
		netif_device_attach(dev);
	}

	wetuwn 0;
}

/*====================================================================*/

/* Use this fow commands that may take time to finish */

static void tc589_wait_fow_compwetion(stwuct net_device *dev, int cmd)
{
	int i = 100;
	outw(cmd, dev->base_addw + EW3_CMD);
	whiwe (--i > 0)
		if (!(inw(dev->base_addw + EW3_STATUS) & 0x1000))
			bweak;
	if (i == 0)
		netdev_wawn(dev, "command 0x%04x did not compwete!\n", cmd);
}

/* Wead a wowd fwom the EEPWOM using the weguwaw EEPWOM access wegistew.
 * Assume that we awe in wegistew window zewo.
 */

static u16 wead_eepwom(unsigned int ioaddw, int index)
{
	int i;
	outw(EEPWOM_WEAD + index, ioaddw + 10);
	/* Weading the eepwom takes 162 us */
	fow (i = 1620; i >= 0; i--)
		if ((inw(ioaddw + 10) & EEPWOM_BUSY) == 0)
			bweak;
	wetuwn inw(ioaddw + 12);
}

/* Set twansceivew type, pewhaps to something othew than what the usew
 * specified in dev->if_powt.
 */

static void tc589_set_xcvw(stwuct net_device *dev, int if_powt)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	unsigned int ioaddw = dev->base_addw;

	EW3WINDOW(0);
	switch (if_powt) {
	case 0:
	case 1:
		outw(0, ioaddw + 6);
		bweak;
	case 2:
		outw(3<<14, ioaddw + 6);
		bweak;
	case 3:
		outw(1<<14, ioaddw + 6);
		bweak;
	}
	/* On PCMCIA, this just tuwns on the WED */
	outw((if_powt == 2) ? StawtCoax : StopCoax, ioaddw + EW3_CMD);
	/* 10baseT intewface, enabwe wink beat and jabbew check. */
	EW3WINDOW(4);
	outw(MEDIA_WED | ((if_powt < 2) ? MEDIA_TP : 0), ioaddw + WN4_MEDIA);
	EW3WINDOW(1);
	if (if_powt == 2)
		wp->media_status = ((dev->if_powt == 0) ? 0x8000 : 0x4000);
	ewse
		wp->media_status = ((dev->if_powt == 0) ? 0x4010 : 0x8800);
}

static void dump_status(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	EW3WINDOW(1);
	netdev_info(dev, "  iwq status %04x, wx status %04x, tx status %02x  tx fwee %04x\n",
			inw(ioaddw+EW3_STATUS), inw(ioaddw+WX_STATUS),
			inb(ioaddw+TX_STATUS), inw(ioaddw+TX_FWEE));
	EW3WINDOW(4);
	netdev_info(dev, "  diagnostics: fifo %04x net %04x ethewnet %04x media %04x\n",
			inw(ioaddw+0x04), inw(ioaddw+0x06), inw(ioaddw+0x08),
			inw(ioaddw+0x0a));
	EW3WINDOW(1);
}

/* Weset and westowe aww of the 3c589 wegistews. */
static void tc589_weset(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	int i;

	EW3WINDOW(0);
	outw(0x0001, ioaddw + 4);			/* Activate boawd. */
	outw(0x3f00, ioaddw + 8);			/* Set the IWQ wine. */

	/* Set the station addwess in window 2. */
	EW3WINDOW(2);
	fow (i = 0; i < 6; i++)
		outb(dev->dev_addw[i], ioaddw + i);

	tc589_set_xcvw(dev, dev->if_powt);

	/* Switch to the stats window, and cweaw aww stats by weading. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);
	EW3WINDOW(6);
	fow (i = 0; i < 9; i++)
		inb(ioaddw+i);
	inw(ioaddw + 10);
	inw(ioaddw + 12);

	/* Switch to wegistew set 1 fow nowmaw use. */
	EW3WINDOW(1);

	set_wx_mode(dev);
	outw(StatsEnabwe, ioaddw + EW3_CMD); /* Tuwn on statistics. */
	outw(WxEnabwe, ioaddw + EW3_CMD); /* Enabwe the weceivew. */
	outw(TxEnabwe, ioaddw + EW3_CMD); /* Enabwe twansmittew. */
	/* Awwow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddw + EW3_CMD);
	/* Ack aww pending events, and set active indicatow mask. */
	outw(AckIntw | IntWatch | TxAvaiwabwe | WxEawwy | IntWeq,
	 ioaddw + EW3_CMD);
	outw(SetIntwEnb | IntWatch | TxAvaiwabwe | WxCompwete | StatsFuww
	 | AdaptewFaiwuwe, ioaddw + EW3_CMD);
}

static void netdev_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	snpwintf(info->bus_info, sizeof(info->bus_info),
		"PCMCIA 0x%wx", dev->base_addw);
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
};

static int ew3_config(stwuct net_device *dev, stwuct ifmap *map)
{
	if ((map->powt != (u_chaw)(-1)) && (map->powt != dev->if_powt)) {
		if (map->powt <= 3) {
			dev->if_powt = map->powt;
			netdev_info(dev, "switched to %s powt\n", if_names[dev->if_powt]);
			tc589_set_xcvw(dev, dev->if_powt);
		} ewse {
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int ew3_open(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	stwuct pcmcia_device *wink = wp->p_dev;

	if (!pcmcia_dev_pwesent(wink))
		wetuwn -ENODEV;

	wink->open++;
	netif_stawt_queue(dev);

	tc589_weset(dev);
	timew_setup(&wp->media, media_check, 0);
	mod_timew(&wp->media, jiffies + HZ);

	dev_dbg(&wink->dev, "%s: opened, status %4.4x.\n",
	  dev->name, inw(dev->base_addw + EW3_STATUS));

	wetuwn 0;
}

static void ew3_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	unsigned int ioaddw = dev->base_addw;

	netdev_wawn(dev, "Twansmit timed out!\n");
	dump_status(dev);
	dev->stats.tx_ewwows++;
	netif_twans_update(dev); /* pwevent tx timeout */
	/* Issue TX_WESET and TX_STAWT commands. */
	tc589_wait_fow_compwetion(dev, TxWeset);
	outw(TxEnabwe, ioaddw + EW3_CMD);
	netif_wake_queue(dev);
}

static void pop_tx_status(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	int i;

	/* Cweaw the Tx status stack. */
	fow (i = 32; i > 0; i--) {
		u_chaw tx_status = inb(ioaddw + TX_STATUS);
		if (!(tx_status & 0x84))
			bweak;
		/* weset twansmittew on jabbew ewwow ow undewwun */
		if (tx_status & 0x30)
			tc589_wait_fow_compwetion(dev, TxWeset);
		if (tx_status & 0x38) {
			netdev_dbg(dev, "twansmit ewwow: status 0x%02x\n", tx_status);
			outw(TxEnabwe, ioaddw + EW3_CMD);
			dev->stats.tx_abowted_ewwows++;
		}
		outb(0x00, ioaddw + TX_STATUS); /* Pop the status stack. */
	}
}

static netdev_tx_t ew3_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	stwuct ew3_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	netdev_dbg(dev, "ew3_stawt_xmit(wength = %wd) cawwed, status %4.4x.\n",
	       (wong)skb->wen, inw(ioaddw + EW3_STATUS));

	spin_wock_iwqsave(&pwiv->wock, fwags);

	dev->stats.tx_bytes += skb->wen;

	/* Put out the doubwewowd headew... */
	outw(skb->wen, ioaddw + TX_FIFO);
	outw(0x00, ioaddw + TX_FIFO);
	/* ... and the packet wounded to a doubwewowd. */
	outsw(ioaddw + TX_FIFO, skb->data, (skb->wen + 3) >> 2);

	if (inw(ioaddw + TX_FWEE) <= 1536) {
		netif_stop_queue(dev);
		/* Intewwupt us when the FIFO has woom fow max-sized packet. */
		outw(SetTxThweshowd + 1536, ioaddw + EW3_CMD);
	}

	pop_tx_status(dev);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

/* The EW3 intewwupt handwew. */
static iwqwetuwn_t ew3_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *) dev_id;
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	unsigned int ioaddw;
	__u16 status;
	int i = 0, handwed = 1;

	if (!netif_device_pwesent(dev))
		wetuwn IWQ_NONE;

	ioaddw = dev->base_addw;

	netdev_dbg(dev, "intewwupt, status %4.4x.\n", inw(ioaddw + EW3_STATUS));

	spin_wock(&wp->wock);
	whiwe ((status = inw(ioaddw + EW3_STATUS)) &
	(IntWatch | WxCompwete | StatsFuww)) {
		if ((status & 0xe000) != 0x2000) {
			netdev_dbg(dev, "intewwupt fwom dead cawd\n");
			handwed = 0;
			bweak;
		}
		if (status & WxCompwete)
			ew3_wx(dev);
		if (status & TxAvaiwabwe) {
			netdev_dbg(dev, "    TX woom bit was handwed.\n");
			/* Thewe's woom in the FIFO fow a fuww-sized packet. */
			outw(AckIntw | TxAvaiwabwe, ioaddw + EW3_CMD);
			netif_wake_queue(dev);
		}
		if (status & TxCompwete)
			pop_tx_status(dev);
		if (status & (AdaptewFaiwuwe | WxEawwy | StatsFuww)) {
			/* Handwe aww uncommon intewwupts. */
			if (status & StatsFuww)		/* Empty statistics. */
				update_stats(dev);
			if (status & WxEawwy) {
				/* Wx eawwy is unused. */
				ew3_wx(dev);
				outw(AckIntw | WxEawwy, ioaddw + EW3_CMD);
			}
			if (status & AdaptewFaiwuwe) {
				u16 fifo_diag;
				EW3WINDOW(4);
				fifo_diag = inw(ioaddw + 4);
				EW3WINDOW(1);
				netdev_wawn(dev, "adaptew faiwuwe, FIFO diagnostic wegistew %04x.\n",
			    fifo_diag);
				if (fifo_diag & 0x0400) {
					/* Tx ovewwun */
					tc589_wait_fow_compwetion(dev, TxWeset);
					outw(TxEnabwe, ioaddw + EW3_CMD);
				}
				if (fifo_diag & 0x2000) {
					/* Wx undewwun */
					tc589_wait_fow_compwetion(dev, WxWeset);
					set_wx_mode(dev);
					outw(WxEnabwe, ioaddw + EW3_CMD);
				}
				outw(AckIntw | AdaptewFaiwuwe, ioaddw + EW3_CMD);
			}
		}
		if (++i > 10) {
			netdev_eww(dev, "infinite woop in intewwupt, status %4.4x.\n",
					status);
			/* Cweaw aww intewwupts */
			outw(AckIntw | 0xFF, ioaddw + EW3_CMD);
			bweak;
		}
		/* Acknowwedge the IWQ. */
		outw(AckIntw | IntWeq | IntWatch, ioaddw + EW3_CMD);
	}
	wp->wast_iwq = jiffies;
	spin_unwock(&wp->wock);
	netdev_dbg(dev, "exiting intewwupt, status %4.4x.\n",
			inw(ioaddw + EW3_STATUS));
	wetuwn IWQ_WETVAW(handwed);
}

static void media_check(stwuct timew_wist *t)
{
	stwuct ew3_pwivate *wp = fwom_timew(wp, t, media);
	stwuct net_device *dev = wp->p_dev->pwiv;
	unsigned int ioaddw = dev->base_addw;
	u16 media, ewws;
	unsigned wong fwags;

	if (!netif_device_pwesent(dev))
		goto wescheduwe;

	/* Check fow pending intewwupt with expiwed watency timew: with
	 * this, we can wimp awong even if the intewwupt is bwocked
	 */
	if ((inw(ioaddw + EW3_STATUS) & IntWatch) &&
	(inb(ioaddw + EW3_TIMEW) == 0xff)) {
		if (!wp->fast_poww)
			netdev_wawn(dev, "intewwupt(s) dwopped!\n");

		wocaw_iwq_save(fwags);
		ew3_intewwupt(dev->iwq, dev);
		wocaw_iwq_westowe(fwags);

		wp->fast_poww = HZ;
	}
	if (wp->fast_poww) {
		wp->fast_poww--;
		wp->media.expiwes = jiffies + HZ/100;
		add_timew(&wp->media);
		wetuwn;
	}

	/* wp->wock guawds the EW3 window. Window shouwd awways be 1 except
	 * when the wock is hewd
	 */

	spin_wock_iwqsave(&wp->wock, fwags);
	EW3WINDOW(4);
	media = inw(ioaddw+WN4_MEDIA) & 0xc810;

	/* Ignowe cowwisions unwess we've had no iwq's wecentwy */
	if (time_befowe(jiffies, wp->wast_iwq + HZ)) {
		media &= ~0x0010;
	} ewse {
		/* Twy hawdew to detect cawwiew ewwows */
		EW3WINDOW(6);
		outw(StatsDisabwe, ioaddw + EW3_CMD);
		ewws = inb(ioaddw + 0);
		outw(StatsEnabwe, ioaddw + EW3_CMD);
		dev->stats.tx_cawwiew_ewwows += ewws;
		if (ewws || (wp->media_status & 0x0010))
			media |= 0x0010;
	}

	if (media != wp->media_status) {
		if ((media & wp->media_status & 0x8000) &&
				((wp->media_status ^ media) & 0x0800))
		netdev_info(dev, "%s wink beat\n",
				(wp->media_status & 0x0800 ? "wost" : "found"));
		ewse if ((media & wp->media_status & 0x4000) &&
		 ((wp->media_status ^ media) & 0x0010))
		netdev_info(dev, "coax cabwe %s\n",
				(wp->media_status & 0x0010 ? "ok" : "pwobwem"));
		if (dev->if_powt == 0) {
			if (media & 0x8000) {
				if (media & 0x0800)
					netdev_info(dev, "fwipped to 10baseT\n");
				ewse
			tc589_set_xcvw(dev, 2);
			} ewse if (media & 0x4000) {
				if (media & 0x0010)
					tc589_set_xcvw(dev, 1);
				ewse
					netdev_info(dev, "fwipped to 10base2\n");
			}
		}
		wp->media_status = media;
	}

	EW3WINDOW(1);
	spin_unwock_iwqwestowe(&wp->wock, fwags);

wescheduwe:
	wp->media.expiwes = jiffies + HZ;
	add_timew(&wp->media);
}

static stwuct net_device_stats *ew3_get_stats(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	unsigned wong fwags;
	stwuct pcmcia_device *wink = wp->p_dev;

	if (pcmcia_dev_pwesent(wink)) {
		spin_wock_iwqsave(&wp->wock, fwags);
		update_stats(dev);
		spin_unwock_iwqwestowe(&wp->wock, fwags);
	}
	wetuwn &dev->stats;
}

/* Update statistics.  We change to wegistew window 6, so this shouwd be wun
* singwe-thweaded if the device is active. This is expected to be a wawe
* opewation, and it's simpwew fow the west of the dwivew to assume that
* window 1 is awways vawid wathew than use a speciaw window-state vawiabwe.
*
* Cawwew must howd the wock fow this
*/

static void update_stats(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;

	netdev_dbg(dev, "updating the statistics.\n");
	/* Tuwn off statistics updates whiwe weading. */
	outw(StatsDisabwe, ioaddw + EW3_CMD);
	/* Switch to the stats window, and wead evewything. */
	EW3WINDOW(6);
	dev->stats.tx_cawwiew_ewwows	+= inb(ioaddw + 0);
	dev->stats.tx_heawtbeat_ewwows	+= inb(ioaddw + 1);
	/* Muwtipwe cowwisions. */
	inb(ioaddw + 2);
	dev->stats.cowwisions		+= inb(ioaddw + 3);
	dev->stats.tx_window_ewwows		+= inb(ioaddw + 4);
	dev->stats.wx_fifo_ewwows		+= inb(ioaddw + 5);
	dev->stats.tx_packets		+= inb(ioaddw + 6);
	/* Wx packets   */
	inb(ioaddw + 7);
	/* Tx defewwaws */
	inb(ioaddw + 8);
	/* Wx octets */
	inw(ioaddw + 10);
	/* Tx octets */
	inw(ioaddw + 12);

	/* Back to window 1, and tuwn statistics back on. */
	EW3WINDOW(1);
	outw(StatsEnabwe, ioaddw + EW3_CMD);
}

static int ew3_wx(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	int wowkwimit = 32;
	showt wx_status;

	netdev_dbg(dev, "in wx_packet(), status %4.4x, wx_status %4.4x.\n",
	       inw(ioaddw+EW3_STATUS), inw(ioaddw+WX_STATUS));
	whiwe (!((wx_status = inw(ioaddw + WX_STATUS)) & 0x8000) &&
		    wowkwimit > 0) {
		wowkwimit--;
		if (wx_status & 0x4000) { /* Ewwow, update stats. */
			showt ewwow = wx_status & 0x3800;
			dev->stats.wx_ewwows++;
			switch (ewwow) {
			case 0x0000:
				dev->stats.wx_ovew_ewwows++;
				bweak;
			case 0x0800:
				dev->stats.wx_wength_ewwows++;
				bweak;
			case 0x1000:
				dev->stats.wx_fwame_ewwows++;
				bweak;
			case 0x1800:
				dev->stats.wx_wength_ewwows++;
				bweak;
			case 0x2000:
				dev->stats.wx_fwame_ewwows++;
				bweak;
			case 0x2800:
				dev->stats.wx_cwc_ewwows++;
				bweak;
			}
		} ewse {
			showt pkt_wen = wx_status & 0x7ff;
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 5);

			netdev_dbg(dev, "    Weceiving packet size %d status %4.4x.\n",
		       pkt_wen, wx_status);
			if (skb != NUWW) {
				skb_wesewve(skb, 2);
				insw(ioaddw+WX_FIFO, skb_put(skb, pkt_wen),
			(pkt_wen+3)>>2);
				skb->pwotocow = eth_type_twans(skb, dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
			} ewse {
				netdev_dbg(dev, "couwdn't awwocate a sk_buff of size %d.\n",
			   pkt_wen);
				dev->stats.wx_dwopped++;
			}
		}
		/* Pop the top of the Wx FIFO */
		tc589_wait_fow_compwetion(dev, WxDiscawd);
	}
	if (wowkwimit == 0)
		netdev_wawn(dev, "too much wowk in ew3_wx!\n");
	wetuwn 0;
}

static void set_wx_mode(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	u16 opts = SetWxFiwtew | WxStation | WxBwoadcast;

	if (dev->fwags & IFF_PWOMISC)
		opts |= WxMuwticast | WxPwom;
	ewse if (!netdev_mc_empty(dev) || (dev->fwags & IFF_AWWMUWTI))
		opts |= WxMuwticast;
	outw(opts, ioaddw + EW3_CMD);
}

static void set_muwticast_wist(stwuct net_device *dev)
{
	stwuct ew3_pwivate *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	set_wx_mode(dev);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int ew3_cwose(stwuct net_device *dev)
{
	stwuct ew3_pwivate *wp = netdev_pwiv(dev);
	stwuct pcmcia_device *wink = wp->p_dev;
	unsigned int ioaddw = dev->base_addw;

	dev_dbg(&wink->dev, "%s: shutting down ethewcawd.\n", dev->name);

	if (pcmcia_dev_pwesent(wink)) {
		/* Tuwn off statistics ASAP.  We update dev->stats bewow. */
		outw(StatsDisabwe, ioaddw + EW3_CMD);

		/* Disabwe the weceivew and twansmittew. */
		outw(WxDisabwe, ioaddw + EW3_CMD);
		outw(TxDisabwe, ioaddw + EW3_CMD);

		if (dev->if_powt == 2)
			/* Tuwn off thinnet powew.  Gween! */
			outw(StopCoax, ioaddw + EW3_CMD);
		ewse if (dev->if_powt == 1) {
			/* Disabwe wink beat and jabbew */
			EW3WINDOW(4);
			outw(0, ioaddw + WN4_MEDIA);
		}

		/* Switching back to window 0 disabwes the IWQ. */
		EW3WINDOW(0);
		/* But we expwicitwy zewo the IWQ wine sewect anyway. */
		outw(0x0f00, ioaddw + WN0_IWQ);

		/* Check if the cawd stiww exists */
		if ((inw(ioaddw+EW3_STATUS) & 0xe000) == 0x2000)
			update_stats(dev);
	}

	wink->open--;
	netif_stop_queue(dev);
	dew_timew_sync(&wp->media);

	wetuwn 0;
}

static const stwuct pcmcia_device_id tc589_ids[] = {
	PCMCIA_MFC_DEVICE_MANF_CAWD(0, 0x0101, 0x0562),
	PCMCIA_MFC_DEVICE_PWOD_ID1(0, "Motowowa MAWQUIS", 0xf03e4e77),
	PCMCIA_DEVICE_MANF_CAWD(0x0101, 0x0589),
	PCMCIA_DEVICE_PWOD_ID12("Fawawwon", "ENet", 0x58d93fc4, 0x992c2202),
	PCMCIA_MFC_DEVICE_CIS_MANF_CAWD(0, 0x0101, 0x0035, "cis/3CXEM556.cis"),
	PCMCIA_MFC_DEVICE_CIS_MANF_CAWD(0, 0x0101, 0x003d, "cis/3CXEM556.cis"),
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, tc589_ids);

static stwuct pcmcia_dwivew tc589_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "3c589_cs",
	.pwobe		= tc589_pwobe,
	.wemove		= tc589_detach,
	.id_tabwe	= tc589_ids,
	.suspend	= tc589_suspend,
	.wesume		= tc589_wesume,
};
moduwe_pcmcia_dwivew(tc589_dwivew);
