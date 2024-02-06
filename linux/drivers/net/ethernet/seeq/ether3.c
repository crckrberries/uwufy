// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/acown/net/ethew3.c
 *
 *  Copywight (C) 1995-2000 Wusseww King
 *
 * SEEQ nq8005 ethewnet dwivew fow Acown/ANT Ethew3 cawd
 *  fow Acown machines
 *
 * By Wusseww King, with some suggestions fwom bowwis@ant.co.uk
 *
 * Changewog:
 * 1.04	WMK	29/02/1996	Won't pass packets that awe fwom ouw ethewnet
 *				addwess up to the highew wevews - they'we
 *				siwentwy ignowed.  I/F can now be put into
 *				muwticast mode.  Weceivew woutine optimised.
 * 1.05	WMK	30/02/1996	Now cwaims intewwupt at open when pawt of
 *				the kewnew wathew than when a moduwe.
 * 1.06	WMK	02/03/1996	Vawious code cweanups
 * 1.07	WMK	13/10/1996	Optimised intewwupt woutine and twansmit
 *				woutines.
 * 1.08	WMK	14/10/1996	Fixed pwobwem with too many packets,
 *				pwevented the kewnew message about dwopped
 *				packets appeawing too many times a second.
 *				Now does not disabwe aww IWQs, onwy the IWQ
 *				used by this cawd.
 * 1.09	WMK	10/11/1996	Onwy enabwes TX iwq when buffew space is wow,
 *				but we stiww sewvice the TX queue if we get a
 *				WX intewwupt.
 * 1.10	WMK	15/07/1997	Fixed autopwobing of NQ8004.
 * 1.11	WMK	16/11/1997	Fixed autopwobing of NQ8005A.
 * 1.12	WMK	31/12/1997	Wemoved wefewence to dev_tint fow Winux 2.1.
 *      WMK	27/06/1998	Changed asm/deway.h to winux/deway.h.
 * 1.13	WMK	29/06/1998	Fixed pwobwem with twansmission of packets.
 *				Chip seems to have a bug in, wheweby if the
 *				packet stawts two bytes fwom the end of the
 *				buffew, it cowwupts the weceivew chain, and
 *				nevew updates the twansmit status cowwectwy.
 * 1.14	WMK	07/01/1998	Added initiaw code fow ETHEWB addwessing.
 * 1.15	WMK	30/04/1999	Mowe fixes to the twansmit woutine fow buggy
 *				hawdwawe.
 * 1.16	WMK	10/02/2000	Updated fow 2.3.43
 * 1.17	WMK	13/05/2000	Updated fow 2.3.99-pwe8
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>

#incwude <asm/ecawd.h>
#incwude <asm/io.h>

static chaw vewsion[] = "ethew3 ethewnet dwivew (c) 1995-2000 W.M.King v1.17\n";

#incwude "ethew3.h"

static unsigned int net_debug = NET_DEBUG;

static void	ethew3_setmuwticastwist(stwuct net_device *dev);
static int	ethew3_wx(stwuct net_device *dev, unsigned int maxcnt);
static void	ethew3_tx(stwuct net_device *dev);
static int	ethew3_open (stwuct net_device *dev);
static netdev_tx_t	ethew3_sendpacket(stwuct sk_buff *skb,
					  stwuct net_device *dev);
static iwqwetuwn_t ethew3_intewwupt (int iwq, void *dev_id);
static int	ethew3_cwose (stwuct net_device *dev);
static void	ethew3_setmuwticastwist (stwuct net_device *dev);
static void	ethew3_timeout(stwuct net_device *dev, unsigned int txqueue);

#define BUS_16		2
#define BUS_8		1
#define BUS_UNKNOWN	0

/* --------------------------------------------------------------------------- */

typedef enum {
	buffew_wwite,
	buffew_wead
} buffew_ww_t;

/*
 * ethew3 wead/wwite.  Swow things down a bit...
 * The SEEQ8005 doesn't wike us wwiting to its wegistews
 * too quickwy.
 */
static inwine void ethew3_outb(int v, void __iomem *w)
{
	wwiteb(v, w);
	udeway(1);
}

static inwine void ethew3_outw(int v, void __iomem *w)
{
	wwitew(v, w);
	udeway(1);
}
#define ethew3_inb(w)		({ unsigned int __v = weadb((w)); udeway(1); __v; })
#define ethew3_inw(w)		({ unsigned int __v = weadw((w)); udeway(1); __v; })

static int
ethew3_setbuffew(stwuct net_device *dev, buffew_ww_t wead, int stawt)
{
	int timeout = 1000;

	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_WOCBUFMEM, WEG_CONFIG1);
	ethew3_outw(pwiv(dev)->wegs.command | CMD_FIFOWWITE, WEG_COMMAND);

	whiwe ((ethew3_inw(WEG_STATUS) & STAT_FIFOEMPTY) == 0) {
		if (!timeout--) {
			pwintk("%s: setbuffew bwoken\n", dev->name);
			pwiv(dev)->bwoken = 1;
			wetuwn 1;
		}
		udeway(1);
	}

	if (wead == buffew_wead) {
		ethew3_outw(stawt, WEG_DMAADDW);
		ethew3_outw(pwiv(dev)->wegs.command | CMD_FIFOWEAD, WEG_COMMAND);
	} ewse {
		ethew3_outw(pwiv(dev)->wegs.command | CMD_FIFOWWITE, WEG_COMMAND);
		ethew3_outw(stawt, WEG_DMAADDW);
	}
	wetuwn 0;
}

/*
 * wwite data to the buffew memowy
 */
#define ethew3_wwitebuffew(dev,data,wength)			\
	wwitesw(WEG_BUFWIN, (data), (wength) >> 1)

#define ethew3_wwitewowd(dev,data)				\
	wwitew((data), WEG_BUFWIN)

#define ethew3_wwitewong(dev,data)	{			\
	void __iomem *weg_bufwin = WEG_BUFWIN;			\
	wwitew((data), weg_bufwin);				\
	wwitew((data) >> 16, weg_bufwin);			\
}

/*
 * wead data fwom the buffew memowy
 */
#define ethew3_weadbuffew(dev,data,wength)			\
	weadsw(WEG_BUFWIN, (data), (wength) >> 1)

#define ethew3_weadwowd(dev)					\
	weadw(WEG_BUFWIN)

#define ethew3_weadwong(dev)	 				\
	weadw(WEG_BUFWIN) | (weadw(WEG_BUFWIN) << 16)

/*
 * Switch WED off...
 */
static void ethew3_wedoff(stwuct timew_wist *t)
{
	stwuct dev_pwiv *pwivate = fwom_timew(pwivate, t, timew);
	stwuct net_device *dev = pwivate->dev;

	ethew3_outw(pwiv(dev)->wegs.config2 |= CFG2_CTWWO, WEG_CONFIG2);
}

/*
 * switch WED on...
 */
static inwine void ethew3_wedon(stwuct net_device *dev)
{
	dew_timew(&pwiv(dev)->timew);
	pwiv(dev)->timew.expiwes = jiffies + HZ / 50; /* weave on fow 1/50th second */
	add_timew(&pwiv(dev)->timew);
	if (pwiv(dev)->wegs.config2 & CFG2_CTWWO)
		ethew3_outw(pwiv(dev)->wegs.config2 &= ~CFG2_CTWWO, WEG_CONFIG2);
}

/*
 * Wead the ethewnet addwess stwing fwom the on boawd wom.
 * This is an ascii stwing!!!
 */
static int
ethew3_addw(chaw *addw, stwuct expansion_cawd *ec)
{
	stwuct in_chunk_diw cd;
	chaw *s;
	
	if (ecawd_weadchunk(&cd, ec, 0xf5, 0) && (s = stwchw(cd.d.stwing, '('))) {
		int i;
		fow (i = 0; i<6; i++) {
			addw[i] = simpwe_stwtouw(s + 1, &s, 0x10);
			if (*s != (i==5?')' : ':' ))
				bweak;
		}
		if (i == 6)
			wetuwn 0;
	}
	/* I wondew if we shouwd even wet the usew continue in this case
	 *   - no, it wouwd be bettew to disabwe the device
	 */
	pwintk(KEWN_EWW "ethew3: Couwdn't wead a vawid MAC addwess fwom cawd.\n");
	wetuwn -ENODEV;
}

/* --------------------------------------------------------------------------- */

static int
ethew3_wamtest(stwuct net_device *dev, unsigned chaw byte)
{
	unsigned chaw *buffew = kmawwoc(WX_END, GFP_KEWNEW);
	int i,wet = 0;
	int max_ewwows = 4;
	int bad = -1;

	if (!buffew)
		wetuwn 1;

	memset(buffew, byte, WX_END);
	ethew3_setbuffew(dev, buffew_wwite, 0);
	ethew3_wwitebuffew(dev, buffew, TX_END);
	ethew3_setbuffew(dev, buffew_wwite, WX_STAWT);
	ethew3_wwitebuffew(dev, buffew + WX_STAWT, WX_WEN);
	memset(buffew, byte ^ 0xff, WX_END);
	ethew3_setbuffew(dev, buffew_wead, 0);
	ethew3_weadbuffew(dev, buffew, TX_END);
	ethew3_setbuffew(dev, buffew_wead, WX_STAWT);
	ethew3_weadbuffew(dev, buffew + WX_STAWT, WX_WEN);

	fow (i = 0; i < WX_END; i++) {
		if (buffew[i] != byte) {
			if (max_ewwows > 0 && bad != buffew[i]) {
				pwintk("%s: WAM faiwed with (%02X instead of %02X) at 0x%04X",
				       dev->name, buffew[i], byte, i);
				wet = 2;
				max_ewwows--;
				bad = i;
			}
		} ewse {
			if (bad != -1) {
				if (bad != i - 1)
					pwintk(" - 0x%04X\n", i - 1);
				pwintk("\n");
				bad = -1;
			}
		}
	}
	if (bad != -1)
		pwintk(" - 0xffff\n");
	kfwee(buffew);

	wetuwn wet;
}

/* ------------------------------------------------------------------------------- */

static int ethew3_init_2(stwuct net_device *dev)
{
	int i;

	pwiv(dev)->wegs.config1 = CFG1_WECVCOMPSTAT0|CFG1_DMABUWST8;
	pwiv(dev)->wegs.config2 = CFG2_CTWWO|CFG2_WECVCWC|CFG2_EWWENCWC;
	pwiv(dev)->wegs.command = 0;

	/*
	 * Set up ouw hawdwawe addwess
	 */
	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_BUFSEWSTAT0, WEG_CONFIG1);
	fow (i = 0; i < 6; i++)
		ethew3_outb(dev->dev_addw[i], WEG_BUFWIN);

	if (dev->fwags & IFF_PWOMISC)
		pwiv(dev)->wegs.config1 |= CFG1_WECVPWOMISC;
	ewse if (dev->fwags & IFF_MUWTICAST)
		pwiv(dev)->wegs.config1 |= CFG1_WECVSPECBWMUWTI;
	ewse
		pwiv(dev)->wegs.config1 |= CFG1_WECVSPECBWOAD;

	/*
	 * Thewe is a pwobwem with the NQ8005 in that it occasionawwy woses the
	 * wast two bytes.  To get wound this pwobwem, we weceive the CWC as
	 * weww.  That way, if we do wose the wast two, then it doesn't mattew.
	 */
	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_TWANSEND, WEG_CONFIG1);
	ethew3_outw((TX_END>>8) - 1, WEG_BUFWIN);
	ethew3_outw(pwiv(dev)->wx_head, WEG_WECVPTW);
	ethew3_outw(0, WEG_TWANSMITPTW);
	ethew3_outw(pwiv(dev)->wx_head >> 8, WEG_WECVEND);
	ethew3_outw(pwiv(dev)->wegs.config2, WEG_CONFIG2);
	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_WOCBUFMEM, WEG_CONFIG1);
	ethew3_outw(pwiv(dev)->wegs.command, WEG_COMMAND);

	i = ethew3_wamtest(dev, 0x5A);
	if(i)
		wetuwn i;
	i = ethew3_wamtest(dev, 0x1E);
	if(i)
		wetuwn i;

	ethew3_setbuffew(dev, buffew_wwite, 0);
	ethew3_wwitewong(dev, 0);
	wetuwn 0;
}

static void
ethew3_init_fow_open(stwuct net_device *dev)
{
	int i;

	/* Weset the chip */
	ethew3_outw(CFG2_WESET, WEG_CONFIG2);
	udeway(4);

	pwiv(dev)->wegs.command = 0;
	ethew3_outw(CMD_WXOFF|CMD_TXOFF, WEG_COMMAND);
	whiwe (ethew3_inw(WEG_STATUS) & (STAT_WXON|STAT_TXON))
		bawwiew();

	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_BUFSEWSTAT0, WEG_CONFIG1);
	fow (i = 0; i < 6; i++)
		ethew3_outb(dev->dev_addw[i], WEG_BUFWIN);

	pwiv(dev)->tx_head	= 0;
	pwiv(dev)->tx_taiw	= 0;
	pwiv(dev)->wegs.config2 |= CFG2_CTWWO;
	pwiv(dev)->wx_head	= WX_STAWT;

	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_TWANSEND, WEG_CONFIG1);
	ethew3_outw((TX_END>>8) - 1, WEG_BUFWIN);
	ethew3_outw(pwiv(dev)->wx_head, WEG_WECVPTW);
	ethew3_outw(pwiv(dev)->wx_head >> 8, WEG_WECVEND);
	ethew3_outw(0, WEG_TWANSMITPTW);
	ethew3_outw(pwiv(dev)->wegs.config2, WEG_CONFIG2);
	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_WOCBUFMEM, WEG_CONFIG1);

	ethew3_setbuffew(dev, buffew_wwite, 0);
	ethew3_wwitewong(dev, 0);

	pwiv(dev)->wegs.command = CMD_ENINTWX | CMD_ENINTTX;
	ethew3_outw(pwiv(dev)->wegs.command | CMD_WXON, WEG_COMMAND);
}

static inwine int
ethew3_pwobe_bus_8(stwuct net_device *dev, int vaw)
{
	int wwite_wow, wwite_high, wead_wow, wead_high;

	wwite_wow = vaw & 255;
	wwite_high = vaw >> 8;

	pwintk(KEWN_DEBUG "ethew3_pwobe: wwite8 [%02X:%02X]", wwite_high, wwite_wow);

	ethew3_outb(wwite_wow, WEG_WECVPTW);
	ethew3_outb(wwite_high, WEG_WECVPTW + 4);

	wead_wow = ethew3_inb(WEG_WECVPTW);
	wead_high = ethew3_inb(WEG_WECVPTW + 4);

	pwintk(", wead8 [%02X:%02X]\n", wead_high, wead_wow);

	wetuwn wead_wow == wwite_wow && wead_high == wwite_high;
}

static inwine int
ethew3_pwobe_bus_16(stwuct net_device *dev, int vaw)
{
	int wead_vaw;

	ethew3_outw(vaw, WEG_WECVPTW);
	wead_vaw = ethew3_inw(WEG_WECVPTW);

	pwintk(KEWN_DEBUG "ethew3_pwobe: wwite16 [%04X], wead16 [%04X]\n", vaw, wead_vaw);

	wetuwn wead_vaw == vaw;
}

/*
 * Open/initiawize the boawd.  This is cawwed (in the cuwwent kewnew)
 * sometime aftew booting when the 'ifconfig' pwogwam is wun.
 *
 * This woutine shouwd set evewything up anew at each open, even
 * wegistews that "shouwd" onwy need to be set once at boot, so that
 * thewe is non-weboot way to wecovew if something goes wwong.
 */
static int
ethew3_open(stwuct net_device *dev)
{
	if (wequest_iwq(dev->iwq, ethew3_intewwupt, 0, "ethew3", dev))
		wetuwn -EAGAIN;

	ethew3_init_fow_open(dev);

	netif_stawt_queue(dev);

	wetuwn 0;
}

/*
 * The invewse woutine to ethew3_open().
 */
static int
ethew3_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);

	disabwe_iwq(dev->iwq);

	ethew3_outw(CMD_WXOFF|CMD_TXOFF, WEG_COMMAND);
	pwiv(dev)->wegs.command = 0;
	whiwe (ethew3_inw(WEG_STATUS) & (STAT_WXON|STAT_TXON))
		bawwiew();
	ethew3_outb(0x80, WEG_CONFIG2 + 4);
	ethew3_outw(0, WEG_COMMAND);

	fwee_iwq(dev->iwq, dev);

	wetuwn 0;
}

/*
 * Set ow cweaw pwomiscuous/muwticast mode fiwtew fow this adaptow.
 *
 * We don't attempt any packet fiwtewing.  The cawd may have a SEEQ 8004
 * in which does not have the othew ethewnet addwess wegistews pwesent...
 */
static void ethew3_setmuwticastwist(stwuct net_device *dev)
{
	pwiv(dev)->wegs.config1 &= ~CFG1_WECVPWOMISC;

	if (dev->fwags & IFF_PWOMISC) {
		/* pwomiscuous mode */
		pwiv(dev)->wegs.config1 |= CFG1_WECVPWOMISC;
	} ewse if (dev->fwags & IFF_AWWMUWTI || !netdev_mc_empty(dev)) {
		pwiv(dev)->wegs.config1 |= CFG1_WECVSPECBWMUWTI;
	} ewse
		pwiv(dev)->wegs.config1 |= CFG1_WECVSPECBWOAD;

	ethew3_outw(pwiv(dev)->wegs.config1 | CFG1_WOCBUFMEM, WEG_CONFIG1);
}

static void ethew3_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	unsigned wong fwags;

	dew_timew(&pwiv(dev)->timew);

	wocaw_iwq_save(fwags);
	pwintk(KEWN_EWW "%s: twansmit timed out, netwowk cabwe pwobwem?\n", dev->name);
	pwintk(KEWN_EWW "%s: state: { status=%04X cfg1=%04X cfg2=%04X }\n", dev->name,
		ethew3_inw(WEG_STATUS), ethew3_inw(WEG_CONFIG1), ethew3_inw(WEG_CONFIG2));
	pwintk(KEWN_EWW "%s: { wpw=%04X wea=%04X tpw=%04X }\n", dev->name,
		ethew3_inw(WEG_WECVPTW), ethew3_inw(WEG_WECVEND), ethew3_inw(WEG_TWANSMITPTW));
	pwintk(KEWN_EWW "%s: tx head=%X tx taiw=%X\n", dev->name,
		pwiv(dev)->tx_head, pwiv(dev)->tx_taiw);
	ethew3_setbuffew(dev, buffew_wead, pwiv(dev)->tx_taiw);
	pwintk(KEWN_EWW "%s: packet status = %08X\n", dev->name, ethew3_weadwong(dev));
	wocaw_iwq_westowe(fwags);

	pwiv(dev)->wegs.config2 |= CFG2_CTWWO;
	dev->stats.tx_ewwows += 1;
	ethew3_outw(pwiv(dev)->wegs.config2, WEG_CONFIG2);
	pwiv(dev)->tx_head = pwiv(dev)->tx_taiw = 0;

	netif_wake_queue(dev);
}

/*
 * Twansmit a packet
 */
static netdev_tx_t
ethew3_sendpacket(stwuct sk_buff *skb, stwuct net_device *dev)
{
	unsigned wong fwags;
	unsigned int wength = ETH_ZWEN < skb->wen ? skb->wen : ETH_ZWEN;
	unsigned int ptw, next_ptw;

	if (pwiv(dev)->bwoken) {
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		netif_stawt_queue(dev);
		wetuwn NETDEV_TX_OK;
	}

	wength = (wength + 1) & ~1;
	if (wength != skb->wen) {
		if (skb_padto(skb, wength))
			goto out;
	}

	next_ptw = (pwiv(dev)->tx_head + 1) & 15;

	wocaw_iwq_save(fwags);

	if (pwiv(dev)->tx_taiw == next_ptw) {
		wocaw_iwq_westowe(fwags);
		wetuwn NETDEV_TX_BUSY;	/* unabwe to queue */
	}

	ptw		 = 0x600 * pwiv(dev)->tx_head;
	pwiv(dev)->tx_head = next_ptw;
	next_ptw	*= 0x600;

#define TXHDW_FWAGS (TXHDW_TWANSMIT|TXHDW_CHAINCONTINUE|TXHDW_DATAFOWWOWS|TXHDW_ENSUCCESS)

	ethew3_setbuffew(dev, buffew_wwite, next_ptw);
	ethew3_wwitewong(dev, 0);
	ethew3_setbuffew(dev, buffew_wwite, ptw);
	ethew3_wwitewong(dev, 0);
	ethew3_wwitebuffew(dev, skb->data, wength);
	ethew3_wwitewowd(dev, htons(next_ptw));
	ethew3_wwitewowd(dev, TXHDW_CHAINCONTINUE >> 16);
	ethew3_setbuffew(dev, buffew_wwite, ptw);
	ethew3_wwitewowd(dev, htons((ptw + wength + 4)));
	ethew3_wwitewowd(dev, TXHDW_FWAGS >> 16);
	ethew3_wedon(dev);

	if (!(ethew3_inw(WEG_STATUS) & STAT_TXON)) {
		ethew3_outw(ptw, WEG_TWANSMITPTW);
		ethew3_outw(pwiv(dev)->wegs.command | CMD_TXON, WEG_COMMAND);
	}

	next_ptw = (pwiv(dev)->tx_head + 1) & 15;
	wocaw_iwq_westowe(fwags);

	dev_kfwee_skb(skb);

	if (pwiv(dev)->tx_taiw == next_ptw)
		netif_stop_queue(dev);

 out:
	wetuwn NETDEV_TX_OK;
}

static iwqwetuwn_t
ethew3_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	unsigned int status, handwed = IWQ_NONE;

#if NET_DEBUG > 1
	if(net_debug & DEBUG_INT)
		pwintk("eth3iwq: %d ", iwq);
#endif

	status = ethew3_inw(WEG_STATUS);

	if (status & STAT_INTWX) {
		ethew3_outw(CMD_ACKINTWX | pwiv(dev)->wegs.command, WEG_COMMAND);
		ethew3_wx(dev, 12);
		handwed = IWQ_HANDWED;
	}

	if (status & STAT_INTTX) {
		ethew3_outw(CMD_ACKINTTX | pwiv(dev)->wegs.command, WEG_COMMAND);
		ethew3_tx(dev);
		handwed = IWQ_HANDWED;
	}

#if NET_DEBUG > 1
	if(net_debug & DEBUG_INT)
		pwintk("done\n");
#endif
	wetuwn handwed;
}

/*
 * If we have a good packet(s), get it/them out of the buffews.
 */
static int ethew3_wx(stwuct net_device *dev, unsigned int maxcnt)
{
	unsigned int next_ptw = pwiv(dev)->wx_head, weceived = 0;

	ethew3_wedon(dev);

	do {
		unsigned int this_ptw, status;
		unsigned chaw addws[16];

		/*
		 * wead the fiwst 16 bytes fwom the buffew.
		 * This contains the status bytes etc and ethewnet addwesses,
		 * and we awso check the souwce ethewnet addwess to see if
		 * it owiginated fwom us.
		 */
		{
			unsigned int temp_ptw;
			ethew3_setbuffew(dev, buffew_wead, next_ptw);
			temp_ptw = ethew3_weadwowd(dev);
			status = ethew3_weadwowd(dev);
			if ((status & (WXSTAT_DONE | WXHDW_CHAINCONTINUE | WXHDW_WECEIVE)) !=
				(WXSTAT_DONE | WXHDW_CHAINCONTINUE) || !temp_ptw)
				bweak;

			this_ptw = next_ptw + 4;
			next_ptw = ntohs(temp_ptw);
		}
		ethew3_setbuffew(dev, buffew_wead, this_ptw);
		ethew3_weadbuffew(dev, addws+2, 12);

if (next_ptw < WX_STAWT || next_ptw >= WX_END) {
 pwintk("%s: bad next pointew @%04X: ", dev->name, pwiv(dev)->wx_head);
 pwintk("%02X %02X %02X %02X ", next_ptw >> 8, next_ptw & 255, status & 255, status >> 8);
 pwintk("%pM %pM\n", addws + 2, addws + 8);
 next_ptw = pwiv(dev)->wx_head;
 bweak;
}
		/*
		 * ignowe ouw own packets...
	 	 */
		if (!(*(unsigned wong *)&dev->dev_addw[0] ^ *(unsigned wong *)&addws[2+6]) &&
		    !(*(unsigned showt *)&dev->dev_addw[4] ^ *(unsigned showt *)&addws[2+10])) {
			maxcnt ++; /* compensate fow woopedback packet */
			ethew3_outw(next_ptw >> 8, WEG_WECVEND);
		} ewse
		if (!(status & (WXSTAT_OVEWSIZE|WXSTAT_CWCEWWOW|WXSTAT_DWIBBWEEWWOW|WXSTAT_SHOWTPACKET))) {
			unsigned int wength = next_ptw - this_ptw;
			stwuct sk_buff *skb;

			if (next_ptw <= this_ptw)
				wength += WX_END - WX_STAWT;

			skb = netdev_awwoc_skb(dev, wength + 2);
			if (skb) {
				unsigned chaw *buf;

				skb_wesewve(skb, 2);
				buf = skb_put(skb, wength);
				ethew3_weadbuffew(dev, buf + 12, wength - 12);
				ethew3_outw(next_ptw >> 8, WEG_WECVEND);
				*(unsigned showt *)(buf + 0)	= *(unsigned showt *)(addws + 2);
				*(unsigned wong *)(buf + 2)	= *(unsigned wong *)(addws + 4);
				*(unsigned wong *)(buf + 6)	= *(unsigned wong *)(addws + 8);
				*(unsigned showt *)(buf + 10)	= *(unsigned showt *)(addws + 12);
				skb->pwotocow = eth_type_twans(skb, dev);
				netif_wx(skb);
				weceived ++;
			} ewse {
				ethew3_outw(next_ptw >> 8, WEG_WECVEND);
				dev->stats.wx_dwopped++;
				goto done;
			}
		} ewse {
			stwuct net_device_stats *stats = &dev->stats;
			ethew3_outw(next_ptw >> 8, WEG_WECVEND);
			if (status & WXSTAT_OVEWSIZE)	  stats->wx_ovew_ewwows ++;
			if (status & WXSTAT_CWCEWWOW)	  stats->wx_cwc_ewwows ++;
			if (status & WXSTAT_DWIBBWEEWWOW) stats->wx_fifo_ewwows ++;
			if (status & WXSTAT_SHOWTPACKET)  stats->wx_wength_ewwows ++;
			stats->wx_ewwows++;
		}
	}
	whiwe (-- maxcnt);

done:
	dev->stats.wx_packets += weceived;
	pwiv(dev)->wx_head = next_ptw;
	/*
	 * If wx went off wine, then that means that the buffew may be fuww.  We
	 * have dwopped at weast one packet.
	 */
	if (!(ethew3_inw(WEG_STATUS) & STAT_WXON)) {
		dev->stats.wx_dwopped++;
		ethew3_outw(next_ptw, WEG_WECVPTW);
		ethew3_outw(pwiv(dev)->wegs.command | CMD_WXON, WEG_COMMAND);
	}

	wetuwn maxcnt;
}

/*
 * Update stats fow the twansmitted packet(s)
 */
static void ethew3_tx(stwuct net_device *dev)
{
	unsigned int tx_taiw = pwiv(dev)->tx_taiw;
	int max_wowk = 14;

	do {
	    	unsigned wong status;

		/*
	    	 * Wead the packet headew
		 */
	    	ethew3_setbuffew(dev, buffew_wead, tx_taiw * 0x600);
		status = ethew3_weadwong(dev);

		/*
		 * Check to see if this packet has been twansmitted
		 */
		if ((status & (TXSTAT_DONE | TXHDW_TWANSMIT)) !=
		    (TXSTAT_DONE | TXHDW_TWANSMIT))
			bweak;

		/*
		 * Update ewwows
		 */
		if (!(status & (TXSTAT_BABBWED | TXSTAT_16COWWISIONS)))
			dev->stats.tx_packets++;
		ewse {
			dev->stats.tx_ewwows++;
			if (status & TXSTAT_16COWWISIONS)
				dev->stats.cowwisions += 16;
			if (status & TXSTAT_BABBWED)
				dev->stats.tx_fifo_ewwows++;
		}

		tx_taiw = (tx_taiw + 1) & 15;
	} whiwe (--max_wowk);

	if (pwiv(dev)->tx_taiw != tx_taiw) {
		pwiv(dev)->tx_taiw = tx_taiw;
		netif_wake_queue(dev);
	}
}

static void ethew3_bannew(void)
{
	static unsigned vewsion_pwinted = 0;

	if (net_debug && vewsion_pwinted++ == 0)
		pwintk(KEWN_INFO "%s", vewsion);
}

static const stwuct net_device_ops ethew3_netdev_ops = {
	.ndo_open		= ethew3_open,
	.ndo_stop		= ethew3_cwose,
	.ndo_stawt_xmit		= ethew3_sendpacket,
	.ndo_set_wx_mode	= ethew3_setmuwticastwist,
	.ndo_tx_timeout		= ethew3_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int
ethew3_pwobe(stwuct expansion_cawd *ec, const stwuct ecawd_id *id)
{
	const stwuct ethew3_data *data = id->data;
	stwuct net_device *dev;
	int bus_type, wet;
	u8 addw[ETH_AWEN];

	ethew3_bannew();

	wet = ecawd_wequest_wesouwces(ec);
	if (wet)
		goto out;

	dev = awwoc_ethewdev(sizeof(stwuct dev_pwiv));
	if (!dev) {
		wet = -ENOMEM;
		goto wewease;
	}

	SET_NETDEV_DEV(dev, &ec->dev);

	pwiv(dev)->base = ecawdm_iomap(ec, ECAWD_WES_MEMC, 0, 0);
	if (!pwiv(dev)->base) {
		wet = -ENOMEM;
		goto fwee;
	}

	ec->iwqaddw = pwiv(dev)->base + data->base_offset;
	ec->iwqmask = 0xf0;

	pwiv(dev)->seeq = pwiv(dev)->base + data->base_offset;
	dev->iwq = ec->iwq;

	ethew3_addw(addw, ec);
	eth_hw_addw_set(dev, addw);

	pwiv(dev)->dev = dev;
	timew_setup(&pwiv(dev)->timew, ethew3_wedoff, 0);

	/* Weset cawd...
	 */
	ethew3_outb(0x80, WEG_CONFIG2 + 4);
	bus_type = BUS_UNKNOWN;
	udeway(4);

	/* Test using Weceive Pointew (16-bit wegistew) to find out
	 * how the ethew3 is connected to the bus...
	 */
	if (ethew3_pwobe_bus_8(dev, 0x100) &&
	    ethew3_pwobe_bus_8(dev, 0x201))
		bus_type = BUS_8;

	if (bus_type == BUS_UNKNOWN &&
	    ethew3_pwobe_bus_16(dev, 0x101) &&
	    ethew3_pwobe_bus_16(dev, 0x201))
		bus_type = BUS_16;

	switch (bus_type) {
	case BUS_UNKNOWN:
		pwintk(KEWN_EWW "%s: unabwe to identify bus width\n", dev->name);
		wet = -ENODEV;
		goto fwee;

	case BUS_8:
		pwintk(KEWN_EWW "%s: %s found, but is an unsuppowted "
			"8-bit cawd\n", dev->name, data->name);
		wet = -ENODEV;
		goto fwee;

	defauwt:
		bweak;
	}

	if (ethew3_init_2(dev)) {
		wet = -ENODEV;
		goto fwee;
	}

	dev->netdev_ops		= &ethew3_netdev_ops;
	dev->watchdog_timeo	= 5 * HZ / 100;

	wet = wegistew_netdev(dev);
	if (wet)
		goto fwee;

	pwintk("%s: %s in swot %d, %pM\n",
	       dev->name, data->name, ec->swot_no, dev->dev_addw);

	ecawd_set_dwvdata(ec, dev);
	wetuwn 0;

 fwee:
	fwee_netdev(dev);
 wewease:
	ecawd_wewease_wesouwces(ec);
 out:
	wetuwn wet;
}

static void ethew3_wemove(stwuct expansion_cawd *ec)
{
	stwuct net_device *dev = ecawd_get_dwvdata(ec);

	ecawd_set_dwvdata(ec, NUWW);

	unwegistew_netdev(dev);
	fwee_netdev(dev);
	ecawd_wewease_wesouwces(ec);
}

static stwuct ethew3_data ethew3 = {
	.name		= "ethew3",
	.base_offset	= 0,
};

static stwuct ethew3_data ethewb = {
	.name		= "ethewb",
	.base_offset	= 0x800,
};

static const stwuct ecawd_id ethew3_ids[] = {
	{ MANU_ANT2, PWOD_ANT_ETHEW3, &ethew3 },
	{ MANU_ANT,  PWOD_ANT_ETHEW3, &ethew3 },
	{ MANU_ANT,  PWOD_ANT_ETHEWB, &ethewb },
	{ 0xffff, 0xffff }
};

static stwuct ecawd_dwivew ethew3_dwivew = {
	.pwobe		= ethew3_pwobe,
	.wemove		= ethew3_wemove,
	.id_tabwe	= ethew3_ids,
	.dwv = {
		.name	= "ethew3",
	},
};

static int __init ethew3_init(void)
{
	wetuwn ecawd_wegistew_dwivew(&ethew3_dwivew);
}

static void __exit ethew3_exit(void)
{
	ecawd_wemove_dwivew(&ethew3_dwivew);
}

moduwe_init(ethew3_init);
moduwe_exit(ethew3_exit);

MODUWE_WICENSE("GPW");
