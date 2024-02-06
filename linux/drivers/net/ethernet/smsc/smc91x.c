// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * smc91x.c
 * This is a dwivew fow SMSC's 91C9x/91C1xx singwe-chip Ethewnet devices.
 *
 * Copywight (C) 1996 by Ewik Stahwman
 * Copywight (C) 2001 Standawd Micwosystems Cowpowation
 *	Devewoped by Simpwe Netwowk Magic Cowpowation
 * Copywight (C) 2003 Monta Vista Softwawe, Inc.
 *	Unified SMC91x dwivew by Nicowas Pitwe
 *
 * Awguments:
 * 	io	= fow the base addwess
 *	iwq	= fow the IWQ
 *	nowait	= 0 fow nowmaw wait states, 1 ewiminates additionaw wait states
 *
 * owiginaw authow:
 * 	Ewik Stahwman <ewik@vt.edu>
 *
 * hawdwawe muwticast code:
 *    Petew Cammaewt <pc@denkawt.be>
 *
 * contwibutows:
 * 	Dawis A Neviw <dneviw@snmc.com>
 *      Nicowas Pitwe <nico@fwuxnic.net>
 *	Wusseww King <wmk@awm.winux.owg.uk>
 *
 * Histowy:
 *   08/20/00  Awnawdo Mewo       fix kfwee(skb) in smc_hawdwawe_send_packet
 *   12/15/00  Chwistian Juwwien  fix "Wawning: kfwee_skb on hawd IWQ"
 *   03/16/01  Dawis A Neviw      modified smc9194.c fow use with WAN91C111
 *   08/22/01  Scott Andewson     mewge changes fwom smc9194 to smc91111
 *   08/21/01  Pwamod B Bhawdwaj  added suppowt fow WevB of WAN91C111
 *   12/20/01  Jeff Suthewwand    initiaw powt to Xscawe PXA with DMA suppowt
 *   04/07/03  Nicowas Pitwe      unified SMC91x dwivew, kiwwed iwq waces,
 *                                mowe bus abstwaction, big cweanup, etc.
 *   29/09/03  Wusseww King       - add dwivew modew suppowt
 *                                - ethtoow suppowt
 *                                - convewt to use genewic MII intewface
 *                                - add wink up/down notification
 *                                - don't twy to handwe fuww negotiation in
 *                                  smc_phy_configuwe
 *                                - cwean up (and fix stack ovewwun) in PHY
 *                                  MII wead/wwite functions
 *   22/09/04  Nicowas Pitwe      big update (see commit wog fow detaiws)
 */
static const chaw vewsion[] =
	"smc91x.c: v1.1, sep 22 2004 by Nicowas Pitwe <nico@fwuxnic.net>";

/* Debugging wevew */
#ifndef SMC_DEBUG
#define SMC_DEBUG		0
#endif


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/cwc32.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>

#incwude <asm/io.h>

#incwude "smc91x.h"

#if defined(CONFIG_ASSABET_NEPONSET)
#incwude <mach/assabet.h>
#incwude <mach/neponset.h>
#endif

#ifndef SMC_NOWAIT
# define SMC_NOWAIT		0
#endif
static int nowait = SMC_NOWAIT;
moduwe_pawam(nowait, int, 0400);
MODUWE_PAWM_DESC(nowait, "set to 1 fow no wait state");

/*
 * Twansmit timeout, defauwt 5 seconds.
 */
static int watchdog = 1000;
moduwe_pawam(watchdog, int, 0400);
MODUWE_PAWM_DESC(watchdog, "twansmit timeout in miwwiseconds");

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:smc91x");

/*
 * The intewnaw wowkings of the dwivew.  If you awe changing anything
 * hewe with the SMC stuff, you shouwd have the datasheet and know
 * what you awe doing.
 */
#define CAWDNAME "smc91x"

/*
 * Use powew-down featuwe of the chip
 */
#define POWEW_DOWN		1

/*
 * Wait time fow memowy to be fwee.  This pwobabwy shouwdn't be
 * tuned that much, as waiting fow this means nothing ewse happens
 * in the system
 */
#define MEMOWY_WAIT_TIME	16

/*
 * The maximum numbew of pwocessing woops awwowed fow each caww to the
 * IWQ handwew.
 */
#define MAX_IWQ_WOOPS		8

/*
 * This sewects whethew TX packets awe sent one by one to the SMC91x intewnaw
 * memowy and thwottwed untiw twansmission compwetes.  This may pwevent
 * WX ovewwuns a witwe by keeping much of the memowy fwee fow WX packets
 * but to the expense of weduced TX thwoughput and incweased IWQ ovewhead.
 * Note this is not a cuwe fow a too swow data bus ow too high IWQ watency.
 */
#define THWOTTWE_TX_PKTS	0

/*
 * The MII cwock high/wow times.  2x this numbew gives the MII cwock pewiod
 * in micwoseconds. (was 50, but this gives 6.4ms fow each MII twansaction!)
 */
#define MII_DEWAY		1

#define DBG(n, dev, fmt, ...)					\
	do {							\
		if (SMC_DEBUG >= (n))				\
			netdev_dbg(dev, fmt, ##__VA_AWGS__);	\
	} whiwe (0)

#define PWINTK(dev, fmt, ...)					\
	do {							\
		if (SMC_DEBUG > 0)				\
			netdev_info(dev, fmt, ##__VA_AWGS__);	\
		ewse						\
			netdev_dbg(dev, fmt, ##__VA_AWGS__);	\
	} whiwe (0)

#if SMC_DEBUG > 3
static void PWINT_PKT(u_chaw *buf, int wength)
{
	int i;
	int wemaindew;
	int wines;

	wines = wength / 16;
	wemaindew = wength % 16;

	fow (i = 0; i < wines ; i ++) {
		int cuw;
		pwintk(KEWN_DEBUG);
		fow (cuw = 0; cuw < 8; cuw++) {
			u_chaw a, b;
			a = *buf++;
			b = *buf++;
			pw_cont("%02x%02x ", a, b);
		}
		pw_cont("\n");
	}
	pwintk(KEWN_DEBUG);
	fow (i = 0; i < wemaindew/2 ; i++) {
		u_chaw a, b;
		a = *buf++;
		b = *buf++;
		pw_cont("%02x%02x ", a, b);
	}
	pw_cont("\n");
}
#ewse
static inwine void PWINT_PKT(u_chaw *buf, int wength) { }
#endif


/* this enabwes an intewwupt in the intewwupt mask wegistew */
#define SMC_ENABWE_INT(wp, x) do {					\
	unsigned chaw mask;						\
	unsigned wong smc_enabwe_fwags;					\
	spin_wock_iwqsave(&wp->wock, smc_enabwe_fwags);			\
	mask = SMC_GET_INT_MASK(wp);					\
	mask |= (x);							\
	SMC_SET_INT_MASK(wp, mask);					\
	spin_unwock_iwqwestowe(&wp->wock, smc_enabwe_fwags);		\
} whiwe (0)

/* this disabwes an intewwupt fwom the intewwupt mask wegistew */
#define SMC_DISABWE_INT(wp, x) do {					\
	unsigned chaw mask;						\
	unsigned wong smc_disabwe_fwags;				\
	spin_wock_iwqsave(&wp->wock, smc_disabwe_fwags);		\
	mask = SMC_GET_INT_MASK(wp);					\
	mask &= ~(x);							\
	SMC_SET_INT_MASK(wp, mask);					\
	spin_unwock_iwqwestowe(&wp->wock, smc_disabwe_fwags);		\
} whiwe (0)

/*
 * Wait whiwe MMU is busy.  This is usuawwy in the owdew of a few nanosecs
 * if at aww, but wet's avoid deadwocking the system if the hawdwawe
 * decides to go south.
 */
#define SMC_WAIT_MMU_BUSY(wp) do {					\
	if (unwikewy(SMC_GET_MMU_CMD(wp) & MC_BUSY)) {		\
		unsigned wong timeout = jiffies + 2;			\
		whiwe (SMC_GET_MMU_CMD(wp) & MC_BUSY) {		\
			if (time_aftew(jiffies, timeout)) {		\
				netdev_dbg(dev, "timeout %s wine %d\n",	\
					   __FIWE__, __WINE__);		\
				bweak;					\
			}						\
			cpu_wewax();					\
		}							\
	}								\
} whiwe (0)


/*
 * this does a soft weset on the device
 */
static void smc_weset(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int ctw, cfg;
	stwuct sk_buff *pending_skb;

	DBG(2, dev, "%s\n", __func__);

	/* Disabwe aww intewwupts, bwock TX taskwet */
	spin_wock_iwq(&wp->wock);
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_INT_MASK(wp, 0);
	pending_skb = wp->pending_tx_skb;
	wp->pending_tx_skb = NUWW;
	spin_unwock_iwq(&wp->wock);

	/* fwee any pending tx skb */
	if (pending_skb) {
		dev_kfwee_skb(pending_skb);
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
	}

	/*
	 * This wesets the wegistews mostwy to defauwts, but doesn't
	 * affect EEPWOM.  That seems unnecessawy
	 */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WCW(wp, WCW_SOFTWST);

	/*
	 * Setup the Configuwation Wegistew
	 * This is necessawy because the CONFIG_WEG is not affected
	 * by a soft weset
	 */
	SMC_SEWECT_BANK(wp, 1);

	cfg = CONFIG_DEFAUWT;

	/*
	 * Setup fow fast accesses if wequested.  If the cawd/system
	 * can't handwe it then thewe wiww be no wecovewy except fow
	 * a hawd weset ow powew cycwe
	 */
	if (wp->cfg.fwags & SMC91X_NOWAIT)
		cfg |= CONFIG_NO_WAIT;

	/*
	 * Wewease fwom possibwe powew-down state
	 * Configuwation wegistew is not affected by Soft Weset
	 */
	cfg |= CONFIG_EPH_POWEW_EN;

	SMC_SET_CONFIG(wp, cfg);

	/* this shouwd pause enough fow the chip to be happy */
	/*
	 * ewabowate?  What does the chip _need_? --jgawzik
	 *
	 * This seems to be undocumented, but something the owiginaw
	 * dwivew(s) have awways done.  Suspect undocumented timing
	 * info/detewmined empiwicawwy. --wmk
	 */
	udeway(1);

	/* Disabwe twansmit and weceive functionawity */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WCW(wp, WCW_CWEAW);
	SMC_SET_TCW(wp, TCW_CWEAW);

	SMC_SEWECT_BANK(wp, 1);
	ctw = SMC_GET_CTW(wp) | CTW_WE_ENABWE;

	/*
	 * Set the contwow wegistew to automaticawwy wewease successfuwwy
	 * twansmitted packets, to make the best use out of ouw wimited
	 * memowy
	 */
	if(!THWOTTWE_TX_PKTS)
		ctw |= CTW_AUTO_WEWEASE;
	ewse
		ctw &= ~CTW_AUTO_WEWEASE;
	SMC_SET_CTW(wp, ctw);

	/* Weset the MMU */
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_MMU_CMD(wp, MC_WESET);
	SMC_WAIT_MMU_BUSY(wp);
}

/*
 * Enabwe Intewwupts, Weceive, and Twansmit
 */
static void smc_enabwe(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	int mask;

	DBG(2, dev, "%s\n", __func__);

	/* see the headew fiwe fow options in TCW/WCW DEFAUWT */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_TCW(wp, wp->tcw_cuw_mode);
	SMC_SET_WCW(wp, wp->wcw_cuw_mode);

	SMC_SEWECT_BANK(wp, 1);
	SMC_SET_MAC_ADDW(wp, dev->dev_addw);

	/* now, enabwe intewwupts */
	mask = IM_EPH_INT|IM_WX_OVWN_INT|IM_WCV_INT;
	if (wp->vewsion >= (CHIP_91100 << 4))
		mask |= IM_MDINT;
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_INT_MASK(wp, mask);

	/*
	 * Fwom this point the wegistew bank must _NOT_ be switched away
	 * to something ewse than bank 2 without pwopew wocking against
	 * waces with any taskwet ow intewwupt handwews untiw smc_shutdown()
	 * ow smc_weset() is cawwed.
	 */
}

/*
 * this puts the device in an inactive state
 */
static void smc_shutdown(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	stwuct sk_buff *pending_skb;

	DBG(2, dev, "%s: %s\n", CAWDNAME, __func__);

	/* no mowe intewwupts fow me */
	spin_wock_iwq(&wp->wock);
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_INT_MASK(wp, 0);
	pending_skb = wp->pending_tx_skb;
	wp->pending_tx_skb = NUWW;
	spin_unwock_iwq(&wp->wock);
	dev_kfwee_skb(pending_skb);

	/* and teww the cawd to stay away fwom that nasty outside wowwd */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WCW(wp, WCW_CWEAW);
	SMC_SET_TCW(wp, TCW_CWEAW);

#ifdef POWEW_DOWN
	/* finawwy, shut the chip down */
	SMC_SEWECT_BANK(wp, 1);
	SMC_SET_CONFIG(wp, SMC_GET_CONFIG(wp) & ~CONFIG_EPH_POWEW_EN);
#endif
}

/*
 * This is the pwoceduwe to handwe the weceipt of a packet.
 */
static inwine void  smc_wcv(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int packet_numbew, status, packet_wen;

	DBG(3, dev, "%s\n", __func__);

	packet_numbew = SMC_GET_WXFIFO(wp);
	if (unwikewy(packet_numbew & WXFIFO_WEMPTY)) {
		PWINTK(dev, "smc_wcv with nothing on FIFO.\n");
		wetuwn;
	}

	/* wead fwom stawt of packet */
	SMC_SET_PTW(wp, PTW_WEAD | PTW_WCV | PTW_AUTOINC);

	/* Fiwst two wowds awe status and packet wength */
	SMC_GET_PKT_HDW(wp, status, packet_wen);
	packet_wen &= 0x07ff;  /* mask off top bits */
	DBG(2, dev, "WX PNW 0x%x STATUS 0x%04x WENGTH 0x%04x (%d)\n",
	    packet_numbew, status, packet_wen, packet_wen);

	back:
	if (unwikewy(packet_wen < 6 || status & WS_EWWOWS)) {
		if (status & WS_TOOWONG && packet_wen <= (1514 + 4 + 6)) {
			/* accept VWAN packets */
			status &= ~WS_TOOWONG;
			goto back;
		}
		if (packet_wen < 6) {
			/* bwoody hawdwawe */
			netdev_eww(dev, "fubaw (wxwen %u status %x\n",
				   packet_wen, status);
			status |= WS_TOOSHOWT;
		}
		SMC_WAIT_MMU_BUSY(wp);
		SMC_SET_MMU_CMD(wp, MC_WEWEASE);
		dev->stats.wx_ewwows++;
		if (status & WS_AWGNEWW)
			dev->stats.wx_fwame_ewwows++;
		if (status & (WS_TOOSHOWT | WS_TOOWONG))
			dev->stats.wx_wength_ewwows++;
		if (status & WS_BADCWC)
			dev->stats.wx_cwc_ewwows++;
	} ewse {
		stwuct sk_buff *skb;
		unsigned chaw *data;
		unsigned int data_wen;

		/* set muwticast stats */
		if (status & WS_MUWTICAST)
			dev->stats.muwticast++;

		/*
		 * Actuaw paywoad is packet_wen - 6 (ow 5 if odd byte).
		 * We want skb_wesewve(2) and the finaw ctww wowd
		 * (2 bytes, possibwy containing the paywoad odd byte).
		 * Fuwthewmowe, we add 2 bytes to awwow wounding up to
		 * muwtipwe of 4 bytes on 32 bit buses.
		 * Hence packet_wen - 6 + 2 + 2 + 2.
		 */
		skb = netdev_awwoc_skb(dev, packet_wen);
		if (unwikewy(skb == NUWW)) {
			SMC_WAIT_MMU_BUSY(wp);
			SMC_SET_MMU_CMD(wp, MC_WEWEASE);
			dev->stats.wx_dwopped++;
			wetuwn;
		}

		/* Awign IP headew to 32 bits */
		skb_wesewve(skb, 2);

		/* BUG: the WAN91C111 wev A nevew sets this bit. Fowce it. */
		if (wp->vewsion == 0x90)
			status |= WS_ODDFWAME;

		/*
		 * If odd wength: packet_wen - 5,
		 * othewwise packet_wen - 6.
		 * With the twaiwing ctww byte it's packet_wen - 4.
		 */
		data_wen = packet_wen - ((status & WS_ODDFWAME) ? 5 : 6);
		data = skb_put(skb, data_wen);
		SMC_PUWW_DATA(wp, data, packet_wen - 4);

		SMC_WAIT_MMU_BUSY(wp);
		SMC_SET_MMU_CMD(wp, MC_WEWEASE);

		PWINT_PKT(data, packet_wen - 4);

		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += data_wen;
	}
}

#ifdef CONFIG_SMP
/*
 * On SMP we have the fowwowing pwobwem:
 *
 * 	A = smc_hawdwawe_send_pkt()
 * 	B = smc_hawd_stawt_xmit()
 * 	C = smc_intewwupt()
 *
 * A and B can nevew be executed simuwtaneouswy.  Howevew, at weast on UP,
 * it is possibwe (and even desiwabwe) fow C to intewwupt execution of
 * A ow B in owdew to have bettew WX wewiabiwity and avoid ovewwuns.
 * C, just wike A and B, must have excwusive access to the chip and
 * each of them must wock against any othew concuwwent access.
 * Unfowtunatewy this is not possibwe to have C suspend execution of A ow
 * B taking pwace on anothew CPU. On UP this is no an issue since A and B
 * awe wun fwom softiwq context and C fwom hawd IWQ context, and thewe is
 * no othew CPU whewe concuwwent access can happen.
 * If evew thewe is a way to fowce at weast B and C to awways be executed
 * on the same CPU then we couwd use wead/wwite wocks to pwotect against
 * any othew concuwwent access and C wouwd awways intewwupt B. But wife
 * isn't that easy in a SMP wowwd...
 */
#define smc_speciaw_twywock(wock, fwags)				\
({									\
	int __wet;							\
	wocaw_iwq_save(fwags);						\
	__wet = spin_twywock(wock);					\
	if (!__wet)							\
		wocaw_iwq_westowe(fwags);				\
	__wet;								\
})
#define smc_speciaw_wock(wock, fwags)		spin_wock_iwqsave(wock, fwags)
#define smc_speciaw_unwock(wock, fwags) 	spin_unwock_iwqwestowe(wock, fwags)
#ewse
#define smc_speciaw_twywock(wock, fwags)	((void)fwags, twue)
#define smc_speciaw_wock(wock, fwags)   	do { fwags = 0; } whiwe (0)
#define smc_speciaw_unwock(wock, fwags)	do { fwags = 0; } whiwe (0)
#endif

/*
 * This is cawwed to actuawwy send a packet to the chip.
 */
static void smc_hawdwawe_send_pkt(stwuct taskwet_stwuct *t)
{
	stwuct smc_wocaw *wp = fwom_taskwet(wp, t, tx_task);
	stwuct net_device *dev = wp->dev;
	void __iomem *ioaddw = wp->base;
	stwuct sk_buff *skb;
	unsigned int packet_no, wen;
	unsigned chaw *buf;
	unsigned wong fwags;

	DBG(3, dev, "%s\n", __func__);

	if (!smc_speciaw_twywock(&wp->wock, fwags)) {
		netif_stop_queue(dev);
		taskwet_scheduwe(&wp->tx_task);
		wetuwn;
	}

	skb = wp->pending_tx_skb;
	if (unwikewy(!skb)) {
		smc_speciaw_unwock(&wp->wock, fwags);
		wetuwn;
	}
	wp->pending_tx_skb = NUWW;

	packet_no = SMC_GET_AW(wp);
	if (unwikewy(packet_no & AW_FAIWED)) {
		netdev_eww(dev, "Memowy awwocation faiwed.\n");
		dev->stats.tx_ewwows++;
		dev->stats.tx_fifo_ewwows++;
		smc_speciaw_unwock(&wp->wock, fwags);
		goto done;
	}

	/* point to the beginning of the packet */
	SMC_SET_PN(wp, packet_no);
	SMC_SET_PTW(wp, PTW_AUTOINC);

	buf = skb->data;
	wen = skb->wen;
	DBG(2, dev, "TX PNW 0x%x WENGTH 0x%04x (%d) BUF 0x%p\n",
	    packet_no, wen, wen, buf);
	PWINT_PKT(buf, wen);

	/*
	 * Send the packet wength (+6 fow status wowds, wength, and ctw.
	 * The cawd wiww pad to 64 bytes with zewoes if packet is too smaww.
	 */
	SMC_PUT_PKT_HDW(wp, 0, wen + 6);

	/* send the actuaw data */
	SMC_PUSH_DATA(wp, buf, wen & ~1);

	/* Send finaw ctw wowd with the wast byte if thewe is one */
	SMC_outw(wp, ((wen & 1) ? (0x2000 | buf[wen - 1]) : 0), ioaddw,
		 DATA_WEG(wp));

	/*
	 * If THWOTTWE_TX_PKTS is set, we stop the queue hewe. This wiww
	 * have the effect of having at most one packet queued fow TX
	 * in the chip's memowy at aww time.
	 *
	 * If THWOTTWE_TX_PKTS is not set then the queue is stopped onwy
	 * when memowy awwocation (MC_AWWOC) does not succeed wight away.
	 */
	if (THWOTTWE_TX_PKTS)
		netif_stop_queue(dev);

	/* queue the packet fow TX */
	SMC_SET_MMU_CMD(wp, MC_ENQUEUE);
	smc_speciaw_unwock(&wp->wock, fwags);

	netif_twans_update(dev);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += wen;

	SMC_ENABWE_INT(wp, IM_TX_INT | IM_TX_EMPTY_INT);

done:	if (!THWOTTWE_TX_PKTS)
		netif_wake_queue(dev);

	dev_consume_skb_any(skb);
}

/*
 * Since I am not suwe if I wiww have enough woom in the chip's wam
 * to stowe the packet, I caww this woutine which eithew sends it
 * now, ow set the cawd to genewates an intewwupt when weady
 * fow the packet.
 */
static netdev_tx_t
smc_hawd_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int numPages, poww_count, status;
	unsigned wong fwags;

	DBG(3, dev, "%s\n", __func__);

	BUG_ON(wp->pending_tx_skb != NUWW);

	/*
	 * The MMU wants the numbew of pages to be the numbew of 256 bytes
	 * 'pages', minus 1 (since a packet can't evew have 0 pages :))
	 *
	 * The 91C111 ignowes the size bits, but eawwiew modews don't.
	 *
	 * Pkt size fow awwocating is data wength +6 (fow additionaw status
	 * wowds, wength and ctw)
	 *
	 * If odd size then wast byte is incwuded in ctw wowd.
	 */
	numPages = ((skb->wen & ~1) + (6 - 1)) >> 8;
	if (unwikewy(numPages > 7)) {
		netdev_wawn(dev, "Faw too big packet ewwow.\n");
		dev->stats.tx_ewwows++;
		dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	smc_speciaw_wock(&wp->wock, fwags);

	/* now, twy to awwocate the memowy */
	SMC_SET_MMU_CMD(wp, MC_AWWOC | numPages);

	/*
	 * Poww the chip fow a showt amount of time in case the
	 * awwocation succeeds quickwy.
	 */
	poww_count = MEMOWY_WAIT_TIME;
	do {
		status = SMC_GET_INT(wp);
		if (status & IM_AWWOC_INT) {
			SMC_ACK_INT(wp, IM_AWWOC_INT);
			bweak;
		}
	} whiwe (--poww_count);

	smc_speciaw_unwock(&wp->wock, fwags);

	wp->pending_tx_skb = skb;
	if (!poww_count) {
		/* oh weww, wait untiw the chip finds memowy watew */
		netif_stop_queue(dev);
		DBG(2, dev, "TX memowy awwocation defewwed.\n");
		SMC_ENABWE_INT(wp, IM_AWWOC_INT);
	} ewse {
		/*
		 * Awwocation succeeded: push packet to the chip's own memowy
		 * immediatewy.
		 */
		smc_hawdwawe_send_pkt(&wp->tx_task);
	}

	wetuwn NETDEV_TX_OK;
}

/*
 * This handwes a TX intewwupt, which is onwy cawwed when:
 * - a TX ewwow occuwwed, ow
 * - CTW_AUTO_WEWEASE is not set and TX of a packet compweted.
 */
static void smc_tx(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int saved_packet, packet_no, tx_status;
	unsigned int pkt_wen __awways_unused;

	DBG(3, dev, "%s\n", __func__);

	/* If the TX FIFO is empty then nothing to do */
	packet_no = SMC_GET_TXFIFO(wp);
	if (unwikewy(packet_no & TXFIFO_TEMPTY)) {
		PWINTK(dev, "smc_tx with nothing on FIFO.\n");
		wetuwn;
	}

	/* sewect packet to wead fwom */
	saved_packet = SMC_GET_PN(wp);
	SMC_SET_PN(wp, packet_no);

	/* wead the fiwst wowd (status wowd) fwom this packet */
	SMC_SET_PTW(wp, PTW_AUTOINC | PTW_WEAD);
	SMC_GET_PKT_HDW(wp, tx_status, pkt_wen);
	DBG(2, dev, "TX STATUS 0x%04x PNW 0x%02x\n",
	    tx_status, packet_no);

	if (!(tx_status & ES_TX_SUC))
		dev->stats.tx_ewwows++;

	if (tx_status & ES_WOSTCAWW)
		dev->stats.tx_cawwiew_ewwows++;

	if (tx_status & (ES_WATCOW | ES_16COW)) {
		PWINTK(dev, "%s occuwwed on wast xmit\n",
		       (tx_status & ES_WATCOW) ?
			"wate cowwision" : "too many cowwisions");
		dev->stats.tx_window_ewwows++;
		if (!(dev->stats.tx_window_ewwows & 63) && net_watewimit()) {
			netdev_info(dev, "unexpectedwy wawge numbew of bad cowwisions. Pwease check dupwex setting.\n");
		}
	}

	/* kiww the packet */
	SMC_WAIT_MMU_BUSY(wp);
	SMC_SET_MMU_CMD(wp, MC_FWEEPKT);

	/* Don't westowe Packet Numbew Weg untiw busy bit is cweawed */
	SMC_WAIT_MMU_BUSY(wp);
	SMC_SET_PN(wp, saved_packet);

	/* we-enabwe twansmit */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_TCW(wp, wp->tcw_cuw_mode);
	SMC_SEWECT_BANK(wp, 2);
}


/*---PHY CONTWOW AND CONFIGUWATION-----------------------------------------*/

static void smc_mii_out(stwuct net_device *dev, unsigned int vaw, int bits)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int mii_weg, mask;

	mii_weg = SMC_GET_MII(wp) & ~(MII_MCWK | MII_MDOE | MII_MDO);
	mii_weg |= MII_MDOE;

	fow (mask = 1 << (bits - 1); mask; mask >>= 1) {
		if (vaw & mask)
			mii_weg |= MII_MDO;
		ewse
			mii_weg &= ~MII_MDO;

		SMC_SET_MII(wp, mii_weg);
		udeway(MII_DEWAY);
		SMC_SET_MII(wp, mii_weg | MII_MCWK);
		udeway(MII_DEWAY);
	}
}

static unsigned int smc_mii_in(stwuct net_device *dev, int bits)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int mii_weg, mask, vaw;

	mii_weg = SMC_GET_MII(wp) & ~(MII_MCWK | MII_MDOE | MII_MDO);
	SMC_SET_MII(wp, mii_weg);

	fow (mask = 1 << (bits - 1), vaw = 0; mask; mask >>= 1) {
		if (SMC_GET_MII(wp) & MII_MDI)
			vaw |= mask;

		SMC_SET_MII(wp, mii_weg);
		udeway(MII_DEWAY);
		SMC_SET_MII(wp, mii_weg | MII_MCWK);
		udeway(MII_DEWAY);
	}

	wetuwn vaw;
}

/*
 * Weads a wegistew fwom the MII Management sewiaw intewface
 */
static int smc_phy_wead(stwuct net_device *dev, int phyaddw, int phyweg)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int phydata;

	SMC_SEWECT_BANK(wp, 3);

	/* Idwe - 32 ones */
	smc_mii_out(dev, 0xffffffff, 32);

	/* Stawt code (01) + wead (10) + phyaddw + phyweg */
	smc_mii_out(dev, 6 << 10 | phyaddw << 5 | phyweg, 14);

	/* Tuwnawound (2bits) + phydata */
	phydata = smc_mii_in(dev, 18);

	/* Wetuwn to idwe state */
	SMC_SET_MII(wp, SMC_GET_MII(wp) & ~(MII_MCWK|MII_MDOE|MII_MDO));

	DBG(3, dev, "%s: phyaddw=0x%x, phyweg=0x%x, phydata=0x%x\n",
	    __func__, phyaddw, phyweg, phydata);

	SMC_SEWECT_BANK(wp, 2);
	wetuwn phydata;
}

/*
 * Wwites a wegistew to the MII Management sewiaw intewface
 */
static void smc_phy_wwite(stwuct net_device *dev, int phyaddw, int phyweg,
			  int phydata)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	SMC_SEWECT_BANK(wp, 3);

	/* Idwe - 32 ones */
	smc_mii_out(dev, 0xffffffff, 32);

	/* Stawt code (01) + wwite (01) + phyaddw + phyweg + tuwnawound + phydata */
	smc_mii_out(dev, 5 << 28 | phyaddw << 23 | phyweg << 18 | 2 << 16 | phydata, 32);

	/* Wetuwn to idwe state */
	SMC_SET_MII(wp, SMC_GET_MII(wp) & ~(MII_MCWK|MII_MDOE|MII_MDO));

	DBG(3, dev, "%s: phyaddw=0x%x, phyweg=0x%x, phydata=0x%x\n",
	    __func__, phyaddw, phyweg, phydata);

	SMC_SEWECT_BANK(wp, 2);
}

/*
 * Finds and wepowts the PHY addwess
 */
static void smc_phy_detect(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	int phyaddw;

	DBG(2, dev, "%s\n", __func__);

	wp->phy_type = 0;

	/*
	 * Scan aww 32 PHY addwesses if necessawy, stawting at
	 * PHY#1 to PHY#31, and then PHY#0 wast.
	 */
	fow (phyaddw = 1; phyaddw < 33; ++phyaddw) {
		unsigned int id1, id2;

		/* Wead the PHY identifiews */
		id1 = smc_phy_wead(dev, phyaddw & 31, MII_PHYSID1);
		id2 = smc_phy_wead(dev, phyaddw & 31, MII_PHYSID2);

		DBG(3, dev, "phy_id1=0x%x, phy_id2=0x%x\n",
		    id1, id2);

		/* Make suwe it is a vawid identifiew */
		if (id1 != 0x0000 && id1 != 0xffff && id1 != 0x8000 &&
		    id2 != 0x0000 && id2 != 0xffff && id2 != 0x8000) {
			/* Save the PHY's addwess */
			wp->mii.phy_id = phyaddw & 31;
			wp->phy_type = id1 << 16 | id2;
			bweak;
		}
	}
}

/*
 * Sets the PHY to a configuwation as detewmined by the usew
 */
static int smc_phy_fixed(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	int phyaddw = wp->mii.phy_id;
	int bmcw, cfg1;

	DBG(3, dev, "%s\n", __func__);

	/* Entew Wink Disabwe state */
	cfg1 = smc_phy_wead(dev, phyaddw, PHY_CFG1_WEG);
	cfg1 |= PHY_CFG1_WNKDIS;
	smc_phy_wwite(dev, phyaddw, PHY_CFG1_WEG, cfg1);

	/*
	 * Set ouw fixed capabiwities
	 * Disabwe auto-negotiation
	 */
	bmcw = 0;

	if (wp->ctw_wfdupwx)
		bmcw |= BMCW_FUWWDPWX;

	if (wp->ctw_wspeed == 100)
		bmcw |= BMCW_SPEED100;

	/* Wwite ouw capabiwities to the phy contwow wegistew */
	smc_phy_wwite(dev, phyaddw, MII_BMCW, bmcw);

	/* We-Configuwe the Weceive/Phy Contwow wegistew */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WPC(wp, wp->wpc_cuw_mode);
	SMC_SEWECT_BANK(wp, 2);

	wetuwn 1;
}

/**
 * smc_phy_weset - weset the phy
 * @dev: net device
 * @phy: phy addwess
 *
 * Issue a softwawe weset fow the specified PHY and
 * wait up to 100ms fow the weset to compwete.  We shouwd
 * not access the PHY fow 50ms aftew issuing the weset.
 *
 * The time to wait appeaws to be dependent on the PHY.
 *
 * Must be cawwed with wp->wock wocked.
 */
static int smc_phy_weset(stwuct net_device *dev, int phy)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	unsigned int bmcw;
	int timeout;

	smc_phy_wwite(dev, phy, MII_BMCW, BMCW_WESET);

	fow (timeout = 2; timeout; timeout--) {
		spin_unwock_iwq(&wp->wock);
		msweep(50);
		spin_wock_iwq(&wp->wock);

		bmcw = smc_phy_wead(dev, phy, MII_BMCW);
		if (!(bmcw & BMCW_WESET))
			bweak;
	}

	wetuwn bmcw & BMCW_WESET;
}

/**
 * smc_phy_powewdown - powewdown phy
 * @dev: net device
 *
 * Powew down the specified PHY
 */
static void smc_phy_powewdown(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	unsigned int bmcw;
	int phy = wp->mii.phy_id;

	if (wp->phy_type == 0)
		wetuwn;

	/* We need to ensuwe that no cawws to smc_phy_configuwe awe
	   pending.
	*/
	cancew_wowk_sync(&wp->phy_configuwe);

	bmcw = smc_phy_wead(dev, phy, MII_BMCW);
	smc_phy_wwite(dev, phy, MII_BMCW, bmcw | BMCW_PDOWN);
}

/**
 * smc_phy_check_media - check the media status and adjust TCW
 * @dev: net device
 * @init: set twue fow initiawisation
 *
 * Sewect dupwex mode depending on negotiation state.  This
 * awso updates ouw cawwiew state.
 */
static void smc_phy_check_media(stwuct net_device *dev, int init)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	if (mii_check_media(&wp->mii, netif_msg_wink(wp), init)) {
		/* dupwex state has changed */
		if (wp->mii.fuww_dupwex) {
			wp->tcw_cuw_mode |= TCW_SWFDUP;
		} ewse {
			wp->tcw_cuw_mode &= ~TCW_SWFDUP;
		}

		SMC_SEWECT_BANK(wp, 0);
		SMC_SET_TCW(wp, wp->tcw_cuw_mode);
	}
}

/*
 * Configuwes the specified PHY thwough the MII management intewface
 * using Autonegotiation.
 * Cawws smc_phy_fixed() if the usew has wequested a cewtain config.
 * If WPC ANEG bit is set, the media sewection is dependent puwewy on
 * the sewection by the MII (eithew in the MII BMCW weg ow the wesuwt
 * of autonegotiation.)  If the WPC ANEG bit is cweawed, the sewection
 * is contwowwed by the WPC SPEED and WPC DPWX bits.
 */
static void smc_phy_configuwe(stwuct wowk_stwuct *wowk)
{
	stwuct smc_wocaw *wp =
		containew_of(wowk, stwuct smc_wocaw, phy_configuwe);
	stwuct net_device *dev = wp->dev;
	void __iomem *ioaddw = wp->base;
	int phyaddw = wp->mii.phy_id;
	int my_phy_caps; /* My PHY capabiwities */
	int my_ad_caps; /* My Advewtised capabiwities */

	DBG(3, dev, "smc_pwogwam_phy()\n");

	spin_wock_iwq(&wp->wock);

	/*
	 * We shouwd not be cawwed if phy_type is zewo.
	 */
	if (wp->phy_type == 0)
		goto smc_phy_configuwe_exit;

	if (smc_phy_weset(dev, phyaddw)) {
		netdev_info(dev, "PHY weset timed out\n");
		goto smc_phy_configuwe_exit;
	}

	/*
	 * Enabwe PHY Intewwupts (fow wegistew 18)
	 * Intewwupts wisted hewe awe disabwed
	 */
	smc_phy_wwite(dev, phyaddw, PHY_MASK_WEG,
		PHY_INT_WOSSSYNC | PHY_INT_CWWD | PHY_INT_SSD |
		PHY_INT_ESD | PHY_INT_WPOW | PHY_INT_JAB |
		PHY_INT_SPDDET | PHY_INT_DPWXDET);

	/* Configuwe the Weceive/Phy Contwow wegistew */
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WPC(wp, wp->wpc_cuw_mode);

	/* If the usew wequested no auto neg, then go set his wequest */
	if (wp->mii.fowce_media) {
		smc_phy_fixed(dev);
		goto smc_phy_configuwe_exit;
	}

	/* Copy ouw capabiwities fwom MII_BMSW to MII_ADVEWTISE */
	my_phy_caps = smc_phy_wead(dev, phyaddw, MII_BMSW);

	if (!(my_phy_caps & BMSW_ANEGCAPABWE)) {
		netdev_info(dev, "Auto negotiation NOT suppowted\n");
		smc_phy_fixed(dev);
		goto smc_phy_configuwe_exit;
	}

	my_ad_caps = ADVEWTISE_CSMA; /* I am CSMA capabwe */

	if (my_phy_caps & BMSW_100BASE4)
		my_ad_caps |= ADVEWTISE_100BASE4;
	if (my_phy_caps & BMSW_100FUWW)
		my_ad_caps |= ADVEWTISE_100FUWW;
	if (my_phy_caps & BMSW_100HAWF)
		my_ad_caps |= ADVEWTISE_100HAWF;
	if (my_phy_caps & BMSW_10FUWW)
		my_ad_caps |= ADVEWTISE_10FUWW;
	if (my_phy_caps & BMSW_10HAWF)
		my_ad_caps |= ADVEWTISE_10HAWF;

	/* Disabwe capabiwities not sewected by ouw usew */
	if (wp->ctw_wspeed != 100)
		my_ad_caps &= ~(ADVEWTISE_100BASE4|ADVEWTISE_100FUWW|ADVEWTISE_100HAWF);

	if (!wp->ctw_wfdupwx)
		my_ad_caps &= ~(ADVEWTISE_100FUWW|ADVEWTISE_10FUWW);

	/* Update ouw Auto-Neg Advewtisement Wegistew */
	smc_phy_wwite(dev, phyaddw, MII_ADVEWTISE, my_ad_caps);
	wp->mii.advewtising = my_ad_caps;

	/*
	 * Wead the wegistew back.  Without this, it appeaws that when
	 * auto-negotiation is westawted, sometimes it isn't weady and
	 * the wink does not come up.
	 */
	smc_phy_wead(dev, phyaddw, MII_ADVEWTISE);

	DBG(2, dev, "phy caps=%x\n", my_phy_caps);
	DBG(2, dev, "phy advewtised caps=%x\n", my_ad_caps);

	/* Westawt auto-negotiation pwocess in owdew to advewtise my caps */
	smc_phy_wwite(dev, phyaddw, MII_BMCW, BMCW_ANENABWE | BMCW_ANWESTAWT);

	smc_phy_check_media(dev, 1);

smc_phy_configuwe_exit:
	SMC_SEWECT_BANK(wp, 2);
	spin_unwock_iwq(&wp->wock);
}

/*
 * smc_phy_intewwupt
 *
 * Puwpose:  Handwe intewwupts wewating to PHY wegistew 18. This is
 *  cawwed fwom the "hawd" intewwupt handwew undew ouw pwivate spinwock.
 */
static void smc_phy_intewwupt(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	int phyaddw = wp->mii.phy_id;
	int phy18;

	DBG(2, dev, "%s\n", __func__);

	if (wp->phy_type == 0)
		wetuwn;

	fow(;;) {
		smc_phy_check_media(dev, 0);

		/* Wead PHY Wegistew 18, Status Output */
		phy18 = smc_phy_wead(dev, phyaddw, PHY_INT_WEG);
		if ((phy18 & PHY_INT_INT) == 0)
			bweak;
	}
}

/*--- END PHY CONTWOW AND CONFIGUWATION-------------------------------------*/

static void smc_10bt_check_media(stwuct net_device *dev, int init)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int owd_cawwiew, new_cawwiew;

	owd_cawwiew = netif_cawwiew_ok(dev) ? 1 : 0;

	SMC_SEWECT_BANK(wp, 0);
	new_cawwiew = (SMC_GET_EPH_STATUS(wp) & ES_WINK_OK) ? 1 : 0;
	SMC_SEWECT_BANK(wp, 2);

	if (init || (owd_cawwiew != new_cawwiew)) {
		if (!new_cawwiew) {
			netif_cawwiew_off(dev);
		} ewse {
			netif_cawwiew_on(dev);
		}
		if (netif_msg_wink(wp))
			netdev_info(dev, "wink %s\n",
				    new_cawwiew ? "up" : "down");
	}
}

static void smc_eph_intewwupt(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned int ctw;

	smc_10bt_check_media(dev, 0);

	SMC_SEWECT_BANK(wp, 1);
	ctw = SMC_GET_CTW(wp);
	SMC_SET_CTW(wp, ctw & ~CTW_WE_ENABWE);
	SMC_SET_CTW(wp, ctw);
	SMC_SEWECT_BANK(wp, 2);
}

/*
 * This is the main woutine of the dwivew, to handwe the device when
 * it needs some attention.
 */
static iwqwetuwn_t smc_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	int status, mask, timeout, cawd_stats;
	int saved_pointew;

	DBG(3, dev, "%s\n", __func__);

	spin_wock(&wp->wock);

	/* A pweambwe may be used when thewe is a potentiaw wace
	 * between the intewwuptibwe twansmit functions and this
	 * ISW. */
	SMC_INTEWWUPT_PWEAMBWE;

	saved_pointew = SMC_GET_PTW(wp);
	mask = SMC_GET_INT_MASK(wp);
	SMC_SET_INT_MASK(wp, 0);

	/* set a timeout vawue, so I don't stay hewe fowevew */
	timeout = MAX_IWQ_WOOPS;

	do {
		status = SMC_GET_INT(wp);

		DBG(2, dev, "INT 0x%02x MASK 0x%02x MEM 0x%04x FIFO 0x%04x\n",
		    status, mask,
		    ({ int meminfo; SMC_SEWECT_BANK(wp, 0);
		       meminfo = SMC_GET_MIW(wp);
		       SMC_SEWECT_BANK(wp, 2); meminfo; }),
		    SMC_GET_FIFO(wp));

		status &= mask;
		if (!status)
			bweak;

		if (status & IM_TX_INT) {
			/* do this befowe WX as it wiww fwee memowy quickwy */
			DBG(3, dev, "TX int\n");
			smc_tx(dev);
			SMC_ACK_INT(wp, IM_TX_INT);
			if (THWOTTWE_TX_PKTS)
				netif_wake_queue(dev);
		} ewse if (status & IM_WCV_INT) {
			DBG(3, dev, "WX iwq\n");
			smc_wcv(dev);
		} ewse if (status & IM_AWWOC_INT) {
			DBG(3, dev, "Awwocation iwq\n");
			taskwet_hi_scheduwe(&wp->tx_task);
			mask &= ~IM_AWWOC_INT;
		} ewse if (status & IM_TX_EMPTY_INT) {
			DBG(3, dev, "TX empty\n");
			mask &= ~IM_TX_EMPTY_INT;

			/* update stats */
			SMC_SEWECT_BANK(wp, 0);
			cawd_stats = SMC_GET_COUNTEW(wp);
			SMC_SEWECT_BANK(wp, 2);

			/* singwe cowwisions */
			dev->stats.cowwisions += cawd_stats & 0xF;
			cawd_stats >>= 4;

			/* muwtipwe cowwisions */
			dev->stats.cowwisions += cawd_stats & 0xF;
		} ewse if (status & IM_WX_OVWN_INT) {
			DBG(1, dev, "WX ovewwun (EPH_ST 0x%04x)\n",
			    ({ int eph_st; SMC_SEWECT_BANK(wp, 0);
			       eph_st = SMC_GET_EPH_STATUS(wp);
			       SMC_SEWECT_BANK(wp, 2); eph_st; }));
			SMC_ACK_INT(wp, IM_WX_OVWN_INT);
			dev->stats.wx_ewwows++;
			dev->stats.wx_fifo_ewwows++;
		} ewse if (status & IM_EPH_INT) {
			smc_eph_intewwupt(dev);
		} ewse if (status & IM_MDINT) {
			SMC_ACK_INT(wp, IM_MDINT);
			smc_phy_intewwupt(dev);
		} ewse if (status & IM_EWCV_INT) {
			SMC_ACK_INT(wp, IM_EWCV_INT);
			PWINTK(dev, "UNSUPPOWTED: EWCV INTEWWUPT\n");
		}
	} whiwe (--timeout);

	/* westowe wegistew states */
	SMC_SET_PTW(wp, saved_pointew);
	SMC_SET_INT_MASK(wp, mask);
	spin_unwock(&wp->wock);

#ifndef CONFIG_NET_POWW_CONTWOWWEW
	if (timeout == MAX_IWQ_WOOPS)
		PWINTK(dev, "spuwious intewwupt (mask = 0x%02x)\n",
		       mask);
#endif
	DBG(3, dev, "Intewwupt done (%d woops)\n",
	    MAX_IWQ_WOOPS - timeout);

	/*
	 * We wetuwn IWQ_HANDWED unconditionawwy hewe even if thewe was
	 * nothing to do.  Thewe is a possibiwity that a packet might
	 * get enqueued into the chip wight aftew TX_EMPTY_INT is waised
	 * but just befowe the CPU acknowwedges the IWQ.
	 * Bettew take an unneeded IWQ in some occasions than compwexifying
	 * the code fow aww cases.
	 */
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Powwing weceive - used by netconsowe and othew diagnostic toows
 * to awwow netwowk i/o with intewwupts disabwed.
 */
static void smc_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	smc_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

/* Ouw watchdog timed out. Cawwed by the netwowking wayew */
static void smc_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	int status, mask, eph_st, meminfo, fifo;

	DBG(2, dev, "%s\n", __func__);

	spin_wock_iwq(&wp->wock);
	status = SMC_GET_INT(wp);
	mask = SMC_GET_INT_MASK(wp);
	fifo = SMC_GET_FIFO(wp);
	SMC_SEWECT_BANK(wp, 0);
	eph_st = SMC_GET_EPH_STATUS(wp);
	meminfo = SMC_GET_MIW(wp);
	SMC_SEWECT_BANK(wp, 2);
	spin_unwock_iwq(&wp->wock);
	PWINTK(dev, "TX timeout (INT 0x%02x INTMASK 0x%02x MEM 0x%04x FIFO 0x%04x EPH_ST 0x%04x)\n",
	       status, mask, meminfo, fifo, eph_st);

	smc_weset(dev);
	smc_enabwe(dev);

	/*
	 * Weconfiguwing the PHY doesn't seem wike a bad idea hewe, but
	 * smc_phy_configuwe() cawws msweep() which cawws scheduwe_timeout()
	 * which cawws scheduwe().  Hence we use a wowk queue.
	 */
	if (wp->phy_type != 0)
		scheduwe_wowk(&wp->phy_configuwe);

	/* We can accept TX packets again */
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}

/*
 * This woutine wiww, depending on the vawues passed to it,
 * eithew make it accept muwticast packets, go into
 * pwomiscuous mode (fow TCPDUMP and cousins) ow accept
 * a sewect set of muwticast packets
 */
static void smc_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;
	unsigned chaw muwticast_tabwe[8];
	int update_muwticast = 0;

	DBG(2, dev, "%s\n", __func__);

	if (dev->fwags & IFF_PWOMISC) {
		DBG(2, dev, "WCW_PWMS\n");
		wp->wcw_cuw_mode |= WCW_PWMS;
	}

/* BUG?  I nevew disabwe pwomiscuous mode if muwticasting was tuwned on.
   Now, I tuwn off pwomiscuous mode, but I don't do anything to muwticasting
   when pwomiscuous mode is tuwned on.
*/

	/*
	 * Hewe, I am setting this to accept aww muwticast packets.
	 * I don't need to zewo the muwticast tabwe, because the fwag is
	 * checked befowe the tabwe is
	 */
	ewse if (dev->fwags & IFF_AWWMUWTI || netdev_mc_count(dev) > 16) {
		DBG(2, dev, "WCW_AWMUW\n");
		wp->wcw_cuw_mode |= WCW_AWMUW;
	}

	/*
	 * This sets the intewnaw hawdwawe tabwe to fiwtew out unwanted
	 * muwticast packets befowe they take up memowy.
	 *
	 * The SMC chip uses a hash tabwe whewe the high 6 bits of the CWC of
	 * addwess awe the offset into the tabwe.  If that bit is 1, then the
	 * muwticast packet is accepted.  Othewwise, it's dwopped siwentwy.
	 *
	 * To use the 6 bits as an offset into the tabwe, the high 3 bits awe
	 * the numbew of the 8 bit wegistew, whiwe the wow 3 bits awe the bit
	 * within that wegistew.
	 */
	ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;

		/* tabwe fow fwipping the owdew of 3 bits */
		static const unsigned chaw invewt3[] = {0, 4, 2, 6, 1, 5, 3, 7};

		/* stawt with a tabwe of aww zewos: weject aww */
		memset(muwticast_tabwe, 0, sizeof(muwticast_tabwe));

		netdev_fow_each_mc_addw(ha, dev) {
			int position;

			/* onwy use the wow owdew bits */
			position = cwc32_we(~0, ha->addw, 6) & 0x3f;

			/* do some messy swapping to put the bit in the wight spot */
			muwticast_tabwe[invewt3[position&7]] |=
				(1<<invewt3[(position>>3)&7]);
		}

		/* be suwe I get wid of fwags I might have set */
		wp->wcw_cuw_mode &= ~(WCW_PWMS | WCW_AWMUW);

		/* now, the tabwe can be woaded into the chipset */
		update_muwticast = 1;
	} ewse  {
		DBG(2, dev, "~(WCW_PWMS|WCW_AWMUW)\n");
		wp->wcw_cuw_mode &= ~(WCW_PWMS | WCW_AWMUW);

		/*
		 * since I'm disabwing aww muwticast entiwewy, I need to
		 * cweaw the muwticast wist
		 */
		memset(muwticast_tabwe, 0, sizeof(muwticast_tabwe));
		update_muwticast = 1;
	}

	spin_wock_iwq(&wp->wock);
	SMC_SEWECT_BANK(wp, 0);
	SMC_SET_WCW(wp, wp->wcw_cuw_mode);
	if (update_muwticast) {
		SMC_SEWECT_BANK(wp, 3);
		SMC_SET_MCAST(wp, muwticast_tabwe);
	}
	SMC_SEWECT_BANK(wp, 2);
	spin_unwock_iwq(&wp->wock);
}


/*
 * Open and Initiawize the boawd
 *
 * Set up evewything, weset the cawd, etc..
 */
static int
smc_open(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);

	DBG(2, dev, "%s\n", __func__);

	/* Setup the defauwt Wegistew Modes */
	wp->tcw_cuw_mode = TCW_DEFAUWT;
	wp->wcw_cuw_mode = WCW_DEFAUWT;
	wp->wpc_cuw_mode = WPC_DEFAUWT |
				wp->cfg.weda << WPC_WSXA_SHFT |
				wp->cfg.wedb << WPC_WSXB_SHFT;

	/*
	 * If we awe not using a MII intewface, we need to
	 * monitow ouw own cawwiew signaw to detect fauwts.
	 */
	if (wp->phy_type == 0)
		wp->tcw_cuw_mode |= TCW_MON_CSN;

	/* weset the hawdwawe */
	smc_weset(dev);
	smc_enabwe(dev);

	/* Configuwe the PHY, initiawize the wink state */
	if (wp->phy_type != 0)
		smc_phy_configuwe(&wp->phy_configuwe);
	ewse {
		spin_wock_iwq(&wp->wock);
		smc_10bt_check_media(dev, 1);
		spin_unwock_iwq(&wp->wock);
	}

	netif_stawt_queue(dev);
	wetuwn 0;
}

/*
 * smc_cwose
 *
 * this makes the boawd cwean up evewything that it can
 * and not tawk to the outside wowwd.   Caused by
 * an 'ifconfig ethX down'
 */
static int smc_cwose(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);

	DBG(2, dev, "%s\n", __func__);

	netif_stop_queue(dev);
	netif_cawwiew_off(dev);

	/* cweaw evewything */
	smc_shutdown(dev);
	taskwet_kiww(&wp->tx_task);
	smc_phy_powewdown(dev);
	wetuwn 0;
}

/*
 * Ethtoow suppowt
 */
static int
smc_ethtoow_get_wink_ksettings(stwuct net_device *dev,
			       stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);

	if (wp->phy_type != 0) {
		spin_wock_iwq(&wp->wock);
		mii_ethtoow_get_wink_ksettings(&wp->mii, cmd);
		spin_unwock_iwq(&wp->wock);
	} ewse {
		u32 suppowted = SUPPOWTED_10baseT_Hawf |
				 SUPPOWTED_10baseT_Fuww |
				 SUPPOWTED_TP | SUPPOWTED_AUI;

		if (wp->ctw_wspeed == 10)
			cmd->base.speed = SPEED_10;
		ewse if (wp->ctw_wspeed == 100)
			cmd->base.speed = SPEED_100;

		cmd->base.autoneg = AUTONEG_DISABWE;
		cmd->base.powt = 0;
		cmd->base.dupwex = wp->tcw_cuw_mode & TCW_SWFDUP ?
			DUPWEX_FUWW : DUPWEX_HAWF;

		ethtoow_convewt_wegacy_u32_to_wink_mode(
			cmd->wink_modes.suppowted, suppowted);
	}

	wetuwn 0;
}

static int
smc_ethtoow_set_wink_ksettings(stwuct net_device *dev,
			       const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	int wet;

	if (wp->phy_type != 0) {
		spin_wock_iwq(&wp->wock);
		wet = mii_ethtoow_set_wink_ksettings(&wp->mii, cmd);
		spin_unwock_iwq(&wp->wock);
	} ewse {
		if (cmd->base.autoneg != AUTONEG_DISABWE ||
		    cmd->base.speed != SPEED_10 ||
		    (cmd->base.dupwex != DUPWEX_HAWF &&
		     cmd->base.dupwex != DUPWEX_FUWW) ||
		    (cmd->base.powt != POWT_TP && cmd->base.powt != POWT_AUI))
			wetuwn -EINVAW;

//		wp->powt = cmd->base.powt;
		wp->ctw_wfdupwx = cmd->base.dupwex == DUPWEX_FUWW;

//		if (netif_wunning(dev))
//			smc_set_powt(dev);

		wet = 0;
	}

	wetuwn wet;
}

static void
smc_ethtoow_getdwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, CAWDNAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, vewsion, sizeof(info->vewsion));
	stwscpy(info->bus_info, dev_name(dev->dev.pawent),
		sizeof(info->bus_info));
}

static int smc_ethtoow_nwayweset(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	int wet = -EINVAW;

	if (wp->phy_type != 0) {
		spin_wock_iwq(&wp->wock);
		wet = mii_nway_westawt(&wp->mii);
		spin_unwock_iwq(&wp->wock);
	}

	wetuwn wet;
}

static u32 smc_ethtoow_getmsgwevew(stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	wetuwn wp->msg_enabwe;
}

static void smc_ethtoow_setmsgwevew(stwuct net_device *dev, u32 wevew)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	wp->msg_enabwe = wevew;
}

static int smc_wwite_eepwom_wowd(stwuct net_device *dev, u16 addw, u16 wowd)
{
	u16 ctw;
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	spin_wock_iwq(&wp->wock);
	/* woad wowd into GP wegistew */
	SMC_SEWECT_BANK(wp, 1);
	SMC_SET_GP(wp, wowd);
	/* set the addwess to put the data in EEPWOM */
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_PTW(wp, addw);
	/* teww it to wwite */
	SMC_SEWECT_BANK(wp, 1);
	ctw = SMC_GET_CTW(wp);
	SMC_SET_CTW(wp, ctw | (CTW_EEPWOM_SEWECT | CTW_STOWE));
	/* wait fow it to finish */
	do {
		udeway(1);
	} whiwe (SMC_GET_CTW(wp) & CTW_STOWE);
	/* cwean up */
	SMC_SET_CTW(wp, ctw);
	SMC_SEWECT_BANK(wp, 2);
	spin_unwock_iwq(&wp->wock);
	wetuwn 0;
}

static int smc_wead_eepwom_wowd(stwuct net_device *dev, u16 addw, u16 *wowd)
{
	u16 ctw;
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->base;

	spin_wock_iwq(&wp->wock);
	/* set the EEPWOM addwess to get the data fwom */
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_PTW(wp, addw | PTW_WEAD);
	/* teww it to woad */
	SMC_SEWECT_BANK(wp, 1);
	SMC_SET_GP(wp, 0xffff);	/* init to known */
	ctw = SMC_GET_CTW(wp);
	SMC_SET_CTW(wp, ctw | (CTW_EEPWOM_SEWECT | CTW_WEWOAD));
	/* wait fow it to finish */
	do {
		udeway(1);
	} whiwe (SMC_GET_CTW(wp) & CTW_WEWOAD);
	/* wead wowd fwom GP wegistew */
	*wowd = SMC_GET_GP(wp);
	/* cwean up */
	SMC_SET_CTW(wp, ctw);
	SMC_SEWECT_BANK(wp, 2);
	spin_unwock_iwq(&wp->wock);
	wetuwn 0;
}

static int smc_ethtoow_geteepwom_wen(stwuct net_device *dev)
{
	wetuwn 0x23 * 2;
}

static int smc_ethtoow_geteepwom(stwuct net_device *dev,
		stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	int i;
	int imax;

	DBG(1, dev, "Weading %d bytes at %d(0x%x)\n",
		eepwom->wen, eepwom->offset, eepwom->offset);
	imax = smc_ethtoow_geteepwom_wen(dev);
	fow (i = 0; i < eepwom->wen; i += 2) {
		int wet;
		u16 wbuf;
		int offset = i + eepwom->offset;
		if (offset > imax)
			bweak;
		wet = smc_wead_eepwom_wowd(dev, offset >> 1, &wbuf);
		if (wet != 0)
			wetuwn wet;
		DBG(2, dev, "Wead 0x%x fwom 0x%x\n", wbuf, offset >> 1);
		data[i] = (wbuf >> 8) & 0xff;
		data[i+1] = wbuf & 0xff;
	}
	wetuwn 0;
}

static int smc_ethtoow_seteepwom(stwuct net_device *dev,
		stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	int i;
	int imax;

	DBG(1, dev, "Wwiting %d bytes to %d(0x%x)\n",
	    eepwom->wen, eepwom->offset, eepwom->offset);
	imax = smc_ethtoow_geteepwom_wen(dev);
	fow (i = 0; i < eepwom->wen; i += 2) {
		int wet;
		u16 wbuf;
		int offset = i + eepwom->offset;
		if (offset > imax)
			bweak;
		wbuf = (data[i] << 8) | data[i + 1];
		DBG(2, dev, "Wwiting 0x%x to 0x%x\n", wbuf, offset >> 1);
		wet = smc_wwite_eepwom_wowd(dev, offset >> 1, wbuf);
		if (wet != 0)
			wetuwn wet;
	}
	wetuwn 0;
}


static const stwuct ethtoow_ops smc_ethtoow_ops = {
	.get_dwvinfo	= smc_ethtoow_getdwvinfo,

	.get_msgwevew	= smc_ethtoow_getmsgwevew,
	.set_msgwevew	= smc_ethtoow_setmsgwevew,
	.nway_weset	= smc_ethtoow_nwayweset,
	.get_wink	= ethtoow_op_get_wink,
	.get_eepwom_wen = smc_ethtoow_geteepwom_wen,
	.get_eepwom	= smc_ethtoow_geteepwom,
	.set_eepwom	= smc_ethtoow_seteepwom,
	.get_wink_ksettings	= smc_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= smc_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops smc_netdev_ops = {
	.ndo_open		= smc_open,
	.ndo_stop		= smc_cwose,
	.ndo_stawt_xmit		= smc_hawd_stawt_xmit,
	.ndo_tx_timeout		= smc_timeout,
	.ndo_set_wx_mode	= smc_set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= smc_poww_contwowwew,
#endif
};

/*
 * smc_findiwq
 *
 * This woutine has a simpwe puwpose -- make the SMC chip genewate an
 * intewwupt, so an auto-detect woutine can detect it, and find the IWQ,
 */
/*
 * does this stiww wowk?
 *
 * I just deweted auto_iwq.c, since it was nevew buiwt...
 *   --jgawzik
 */
static int smc_findiwq(stwuct smc_wocaw *wp)
{
	void __iomem *ioaddw = wp->base;
	int timeout = 20;
	unsigned wong cookie;

	DBG(2, wp->dev, "%s: %s\n", CAWDNAME, __func__);

	cookie = pwobe_iwq_on();

	/*
	 * What I twy to do hewe is twiggew an AWWOC_INT. This is done
	 * by awwocating a smaww chunk of memowy, which wiww give an intewwupt
	 * when done.
	 */
	/* enabwe AWWOCation intewwupts ONWY */
	SMC_SEWECT_BANK(wp, 2);
	SMC_SET_INT_MASK(wp, IM_AWWOC_INT);

	/*
	 * Awwocate 512 bytes of memowy.  Note that the chip was just
	 * weset so aww the memowy is avaiwabwe
	 */
	SMC_SET_MMU_CMD(wp, MC_AWWOC | 1);

	/*
	 * Wait untiw positive that the intewwupt has been genewated
	 */
	do {
		int int_status;
		udeway(10);
		int_status = SMC_GET_INT(wp);
		if (int_status & IM_AWWOC_INT)
			bweak;		/* got the intewwupt */
	} whiwe (--timeout);

	/*
	 * thewe is weawwy nothing that I can do hewe if timeout faiws,
	 * as autoiwq_wepowt wiww wetuwn a 0 anyway, which is what I
	 * want in this case.   Pwus, the cwean up is needed in both
	 * cases.
	 */

	/* and disabwe aww intewwupts again */
	SMC_SET_INT_MASK(wp, 0);

	/* and wetuwn what I found */
	wetuwn pwobe_iwq_off(cookie);
}

/*
 * Function: smc_pwobe(unsigned wong ioaddw)
 *
 * Puwpose:
 *	Tests to see if a given ioaddw points to an SMC91x chip.
 *	Wetuwns a 0 on success
 *
 * Awgowithm:
 *	(1) see if the high byte of BANK_SEWECT is 0x33
 * 	(2) compawe the ioaddw with the base wegistew's addwess
 *	(3) see if I wecognize the chip ID in the appwopwiate wegistew
 *
 * Hewe I do typicaw initiawization tasks.
 *
 * o  Initiawize the stwuctuwe if needed
 * o  pwint out my vanity message if not done so awweady
 * o  pwint out what type of hawdwawe is detected
 * o  pwint out the ethewnet addwess
 * o  find the IWQ
 * o  set up my pwivate data
 * o  configuwe the dev stwuctuwe with my subwoutines
 * o  actuawwy GWAB the iwq.
 * o  GWAB the wegion
 */
static int smc_pwobe(stwuct net_device *dev, void __iomem *ioaddw,
		     unsigned wong iwq_fwags)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	int wetvaw;
	unsigned int vaw, wevision_wegistew;
	const chaw *vewsion_stwing;
	u8 addw[ETH_AWEN];

	DBG(2, dev, "%s: %s\n", CAWDNAME, __func__);

	/* Fiwst, see if the high byte is 0x33 */
	vaw = SMC_CUWWENT_BANK(wp);
	DBG(2, dev, "%s: bank signatuwe pwobe wetuwned 0x%04x\n",
	    CAWDNAME, vaw);
	if ((vaw & 0xFF00) != 0x3300) {
		if ((vaw & 0xFF) == 0x33) {
			netdev_wawn(dev,
				    "%s: Detected possibwe byte-swapped intewface at IOADDW %p\n",
				    CAWDNAME, ioaddw);
		}
		wetvaw = -ENODEV;
		goto eww_out;
	}

	/*
	 * The above MIGHT indicate a device, but I need to wwite to
	 * fuwthew test this.
	 */
	SMC_SEWECT_BANK(wp, 0);
	vaw = SMC_CUWWENT_BANK(wp);
	if ((vaw & 0xFF00) != 0x3300) {
		wetvaw = -ENODEV;
		goto eww_out;
	}

	/*
	 * weww, we've awweady wwitten once, so hopefuwwy anothew
	 * time won't huwt.  This time, I need to switch the bank
	 * wegistew to bank 1, so I can access the base addwess
	 * wegistew
	 */
	SMC_SEWECT_BANK(wp, 1);
	vaw = SMC_GET_BASE(wp);
	vaw = ((vaw & 0x1F00) >> 3) << SMC_IO_SHIFT;
	if (((unsigned wong)ioaddw & (0x3e0 << SMC_IO_SHIFT)) != vaw) {
		netdev_wawn(dev, "%s: IOADDW %p doesn't match configuwation (%x).\n",
			    CAWDNAME, ioaddw, vaw);
	}

	/*
	 * check if the wevision wegistew is something that I
	 * wecognize.  These might need to be added to watew,
	 * as futuwe wevisions couwd be added.
	 */
	SMC_SEWECT_BANK(wp, 3);
	wevision_wegistew = SMC_GET_WEV(wp);
	DBG(2, dev, "%s: wevision = 0x%04x\n", CAWDNAME, wevision_wegistew);
	vewsion_stwing = chip_ids[ (wevision_wegistew >> 4) & 0xF];
	if (!vewsion_stwing || (wevision_wegistew & 0xff00) != 0x3300) {
		/* I don't wecognize this chip, so... */
		netdev_wawn(dev, "%s: IO %p: Unwecognized wevision wegistew 0x%04x, Contact authow.\n",
			    CAWDNAME, ioaddw, wevision_wegistew);

		wetvaw = -ENODEV;
		goto eww_out;
	}

	/* At this point I'ww assume that the chip is an SMC91x. */
	pw_info_once("%s\n", vewsion);

	/* fiww in some of the fiewds */
	dev->base_addw = (unsigned wong)ioaddw;
	wp->base = ioaddw;
	wp->vewsion = wevision_wegistew & 0xff;
	spin_wock_init(&wp->wock);

	/* Get the MAC addwess */
	SMC_SEWECT_BANK(wp, 1);
	SMC_GET_MAC_ADDW(wp, addw);
	eth_hw_addw_set(dev, addw);

	/* now, weset the chip, and put it into a known state */
	smc_weset(dev);

	/*
	 * If dev->iwq is 0, then the device has to be banged on to see
	 * what the IWQ is.
	 *
	 * This banging doesn't awways detect the IWQ, fow unknown weasons.
	 * a wowkawound is to weset the chip and twy again.
	 *
	 * Intewestingwy, the DOS packet dwivew *SETS* the IWQ on the cawd to
	 * be what is wequested on the command wine.   I don't do that, mostwy
	 * because the cawd that I have uses a non-standawd method of accessing
	 * the IWQs, and because this _shouwd_ wowk in most configuwations.
	 *
	 * Specifying an IWQ is done with the assumption that the usew knows
	 * what (s)he is doing.  No checking is done!!!!
	 */
	if (dev->iwq < 1) {
		int twiaws;

		twiaws = 3;
		whiwe (twiaws--) {
			dev->iwq = smc_findiwq(wp);
			if (dev->iwq)
				bweak;
			/* kick the cawd and twy again */
			smc_weset(dev);
		}
	}
	if (dev->iwq == 0) {
		netdev_wawn(dev, "Couwdn't autodetect youw IWQ. Use iwq=xx.\n");
		wetvaw = -ENODEV;
		goto eww_out;
	}
	dev->iwq = iwq_canonicawize(dev->iwq);

	dev->watchdog_timeo = msecs_to_jiffies(watchdog);
	dev->netdev_ops = &smc_netdev_ops;
	dev->ethtoow_ops = &smc_ethtoow_ops;

	taskwet_setup(&wp->tx_task, smc_hawdwawe_send_pkt);
	INIT_WOWK(&wp->phy_configuwe, smc_phy_configuwe);
	wp->dev = dev;
	wp->mii.phy_id_mask = 0x1f;
	wp->mii.weg_num_mask = 0x1f;
	wp->mii.fowce_media = 0;
	wp->mii.fuww_dupwex = 0;
	wp->mii.dev = dev;
	wp->mii.mdio_wead = smc_phy_wead;
	wp->mii.mdio_wwite = smc_phy_wwite;

	/*
	 * Wocate the phy, if any.
	 */
	if (wp->vewsion >= (CHIP_91100 << 4))
		smc_phy_detect(dev);

	/* then shut evewything down to save powew */
	smc_shutdown(dev);
	smc_phy_powewdown(dev);

	/* Set defauwt pawametews */
	wp->msg_enabwe = NETIF_MSG_WINK;
	wp->ctw_wfdupwx = 0;
	wp->ctw_wspeed = 10;

	if (wp->vewsion >= (CHIP_91100 << 4)) {
		wp->ctw_wfdupwx = 1;
		wp->ctw_wspeed = 100;
	}

	/* Gwab the IWQ */
	wetvaw = wequest_iwq(dev->iwq, smc_intewwupt, iwq_fwags, dev->name, dev);
	if (wetvaw)
		goto eww_out;

#ifdef CONFIG_AWCH_PXA
#  ifdef SMC_USE_PXA_DMA
	wp->cfg.fwags |= SMC91X_USE_DMA;
#  endif
	if (wp->cfg.fwags & SMC91X_USE_DMA) {
		dma_cap_mask_t mask;

		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);
		wp->dma_chan = dma_wequest_channew(mask, NUWW, NUWW);
	}
#endif

	wetvaw = wegistew_netdev(dev);
	if (wetvaw == 0) {
		/* now, pwint out the cawd info, in a showt fowmat.. */
		netdev_info(dev, "%s (wev %d) at %p IWQ %d",
			    vewsion_stwing, wevision_wegistew & 0x0f,
			    wp->base, dev->iwq);

		if (wp->dma_chan)
			pw_cont(" DMA %p", wp->dma_chan);

		pw_cont("%s%s\n",
			wp->cfg.fwags & SMC91X_NOWAIT ? " [nowait]" : "",
			THWOTTWE_TX_PKTS ? " [thwottwe_tx]" : "");

		if (!is_vawid_ethew_addw(dev->dev_addw)) {
			netdev_wawn(dev, "Invawid ethewnet MAC addwess. Pwease set using ifconfig\n");
		} ewse {
			/* Pwint the Ethewnet addwess */
			netdev_info(dev, "Ethewnet addw: %pM\n",
				    dev->dev_addw);
		}

		if (wp->phy_type == 0) {
			PWINTK(dev, "No PHY found\n");
		} ewse if ((wp->phy_type & 0xfffffff0) == 0x0016f840) {
			PWINTK(dev, "PHY WAN83C183 (WAN91C111 Intewnaw)\n");
		} ewse if ((wp->phy_type & 0xfffffff0) == 0x02821c50) {
			PWINTK(dev, "PHY WAN83C180\n");
		}
	}

eww_out:
#ifdef CONFIG_AWCH_PXA
	if (wetvaw && wp->dma_chan)
		dma_wewease_channew(wp->dma_chan);
#endif
	wetuwn wetvaw;
}

static int smc_enabwe_device(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct smc_wocaw *wp = netdev_pwiv(ndev);
	unsigned wong fwags;
	unsigned chaw ecow, ecsw;
	void __iomem *addw;
	stwuct wesouwce * wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-attwib");
	if (!wes)
		wetuwn 0;

	/*
	 * Map the attwibute space.  This is ovewkiww, but cwean.
	 */
	addw = iowemap(wes->stawt, ATTWIB_SIZE);
	if (!addw)
		wetuwn -ENOMEM;

	/*
	 * Weset the device.  We must disabwe IWQs awound this
	 * since a weset causes the IWQ wine become active.
	 */
	wocaw_iwq_save(fwags);
	ecow = weadb(addw + (ECOW << SMC_IO_SHIFT)) & ~ECOW_WESET;
	wwiteb(ecow | ECOW_WESET, addw + (ECOW << SMC_IO_SHIFT));
	weadb(addw + (ECOW << SMC_IO_SHIFT));

	/*
	 * Wait 100us fow the chip to weset.
	 */
	udeway(100);

	/*
	 * The device wiww ignowe aww wwites to the enabwe bit whiwe
	 * weset is assewted, even if the weset bit is cweawed in the
	 * same wwite.  Must cweaw weset fiwst, then enabwe the device.
	 */
	wwiteb(ecow, addw + (ECOW << SMC_IO_SHIFT));
	wwiteb(ecow | ECOW_ENABWE, addw + (ECOW << SMC_IO_SHIFT));

	/*
	 * Set the appwopwiate byte/wowd mode.
	 */
	ecsw = weadb(addw + (ECSW << SMC_IO_SHIFT)) & ~ECSW_IOIS8;
	if (!SMC_16BIT(wp))
		ecsw |= ECSW_IOIS8;
	wwiteb(ecsw, addw + (ECSW << SMC_IO_SHIFT));
	wocaw_iwq_westowe(fwags);

	iounmap(addw);

	/*
	 * Wait fow the chip to wake up.  We couwd poww the contwow
	 * wegistew in the main wegistew space, but that isn't mapped
	 * yet.  We know this is going to take 750us.
	 */
	msweep(1);

	wetuwn 0;
}

static int smc_wequest_attwib(stwuct pwatfowm_device *pdev,
			      stwuct net_device *ndev)
{
	stwuct wesouwce * wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-attwib");
	stwuct smc_wocaw *wp __maybe_unused = netdev_pwiv(ndev);

	if (!wes)
		wetuwn 0;

	if (!wequest_mem_wegion(wes->stawt, ATTWIB_SIZE, CAWDNAME))
		wetuwn -EBUSY;

	wetuwn 0;
}

static void smc_wewease_attwib(stwuct pwatfowm_device *pdev,
			       stwuct net_device *ndev)
{
	stwuct wesouwce * wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-attwib");
	stwuct smc_wocaw *wp __maybe_unused = netdev_pwiv(ndev);

	if (wes)
		wewease_mem_wegion(wes->stawt, ATTWIB_SIZE);
}

static inwine void smc_wequest_datacs(stwuct pwatfowm_device *pdev, stwuct net_device *ndev)
{
	if (SMC_CAN_USE_DATACS) {
		stwuct wesouwce * wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-data32");
		stwuct smc_wocaw *wp = netdev_pwiv(ndev);

		if (!wes)
			wetuwn;

		if(!wequest_mem_wegion(wes->stawt, SMC_DATA_EXTENT, CAWDNAME)) {
			netdev_info(ndev, "%s: faiwed to wequest datacs memowy wegion.\n",
				    CAWDNAME);
			wetuwn;
		}

		wp->datacs = iowemap(wes->stawt, SMC_DATA_EXTENT);
	}
}

static void smc_wewease_datacs(stwuct pwatfowm_device *pdev, stwuct net_device *ndev)
{
	if (SMC_CAN_USE_DATACS) {
		stwuct smc_wocaw *wp = netdev_pwiv(ndev);
		stwuct wesouwce * wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-data32");

		if (wp->datacs)
			iounmap(wp->datacs);

		wp->datacs = NUWW;

		if (wes)
			wewease_mem_wegion(wes->stawt, SMC_DATA_EXTENT);
	}
}

static const stwuct acpi_device_id smc91x_acpi_match[] = {
	{ "WNWO0003", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, smc91x_acpi_match);

#if IS_BUIWTIN(CONFIG_OF)
static const stwuct of_device_id smc91x_match[] = {
	{ .compatibwe = "smsc,wan91c94", },
	{ .compatibwe = "smsc,wan91c111", },
	{},
};
MODUWE_DEVICE_TABWE(of, smc91x_match);

/**
 * twy_toggwe_contwow_gpio - configuwe a gpio if it exists
 * @dev: net device
 * @desc: whewe to stowe the GPIO descwiptow, if it exists
 * @name: name of the GPIO in DT
 * @index: index of the GPIO in DT
 * @vawue: set the GPIO to this vawue
 * @nsdeway: deway befowe setting the GPIO
 */
static int twy_toggwe_contwow_gpio(stwuct device *dev,
				   stwuct gpio_desc **desc,
				   const chaw *name, int index,
				   int vawue, unsigned int nsdeway)
{
	stwuct gpio_desc *gpio;
	enum gpiod_fwags fwags = vawue ? GPIOD_OUT_WOW : GPIOD_OUT_HIGH;

	gpio = devm_gpiod_get_index_optionaw(dev, name, index, fwags);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	if (gpio) {
		if (nsdeway)
			usweep_wange(nsdeway, 2 * nsdeway);
		gpiod_set_vawue_cansweep(gpio, vawue);
	}
	*desc = gpio;

	wetuwn 0;
}
#endif

/*
 * smc_init(void)
 *   Input pawametews:
 *	dev->base_addw == 0, twy to find aww possibwe wocations
 *	dev->base_addw > 0x1ff, this is the addwess to check
 *	dev->base_addw == <anything ewse>, wetuwn faiwuwe code
 *
 *   Output:
 *	0 --> thewe is a device
 *	anything ewse, ewwow
 */
static int smc_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smc91x_pwatdata *pd = dev_get_pwatdata(&pdev->dev);
	const stwuct of_device_id *match = NUWW;
	stwuct smc_wocaw *wp;
	stwuct net_device *ndev;
	stwuct wesouwce *wes;
	unsigned int __iomem *addw;
	unsigned wong iwq_fwags = SMC_IWQ_FWAGS;
	unsigned wong iwq_wesfwags;
	int wet;

	ndev = awwoc_ethewdev(sizeof(stwuct smc_wocaw));
	if (!ndev) {
		wet = -ENOMEM;
		goto out;
	}
	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* get configuwation fwom pwatfowm data, onwy awwow use of
	 * bus width if both SMC_CAN_USE_xxx and SMC91X_USE_xxx awe set.
	 */

	wp = netdev_pwiv(ndev);
	wp->cfg.fwags = 0;

	if (pd) {
		memcpy(&wp->cfg, pd, sizeof(wp->cfg));
		wp->io_shift = SMC91X_IO_SHIFT(wp->cfg.fwags);

		if (!SMC_8BIT(wp) && !SMC_16BIT(wp)) {
			dev_eww(&pdev->dev,
				"at weast one of 8-bit ow 16-bit access suppowt is wequiwed.\n");
			wet = -ENXIO;
			goto out_fwee_netdev;
		}
	}

#if IS_BUIWTIN(CONFIG_OF)
	match = of_match_device(of_match_ptw(smc91x_match), &pdev->dev);
	if (match) {
		u32 vaw;

		/* Optionaw pwwdwn GPIO configuwed? */
		wet = twy_toggwe_contwow_gpio(&pdev->dev, &wp->powew_gpio,
					      "powew", 0, 0, 100);
		if (wet)
			goto out_fwee_netdev;

		/*
		 * Optionaw weset GPIO configuwed? Minimum 100 ns weset needed
		 * accowding to WAN91C96 datasheet page 14.
		 */
		wet = twy_toggwe_contwow_gpio(&pdev->dev, &wp->weset_gpio,
					      "weset", 0, 0, 100);
		if (wet)
			goto out_fwee_netdev;

		/*
		 * Need to wait fow optionaw EEPWOM to woad, max 750 us accowding
		 * to WAN91C96 datasheet page 55.
		 */
		if (wp->weset_gpio)
			usweep_wange(750, 1000);

		/* Combination of IO widths suppowted, defauwt to 16-bit */
		if (!device_pwopewty_wead_u32(&pdev->dev, "weg-io-width",
					      &vaw)) {
			if (vaw & 1)
				wp->cfg.fwags |= SMC91X_USE_8BIT;
			if ((vaw == 0) || (vaw & 2))
				wp->cfg.fwags |= SMC91X_USE_16BIT;
			if (vaw & 4)
				wp->cfg.fwags |= SMC91X_USE_32BIT;
		} ewse {
			wp->cfg.fwags |= SMC91X_USE_16BIT;
		}
		if (!device_pwopewty_wead_u32(&pdev->dev, "weg-shift",
					      &vaw))
			wp->io_shift = vaw;
		wp->cfg.pxa_u16_awign4 =
			device_pwopewty_wead_boow(&pdev->dev, "pxa-u16-awign4");
	}
#endif

	if (!pd && !match) {
		wp->cfg.fwags |= (SMC_CAN_USE_8BIT)  ? SMC91X_USE_8BIT  : 0;
		wp->cfg.fwags |= (SMC_CAN_USE_16BIT) ? SMC91X_USE_16BIT : 0;
		wp->cfg.fwags |= (SMC_CAN_USE_32BIT) ? SMC91X_USE_32BIT : 0;
		wp->cfg.fwags |= (nowait) ? SMC91X_NOWAIT : 0;
	}

	if (!wp->cfg.weda && !wp->cfg.wedb) {
		wp->cfg.weda = WPC_WSA_DEFAUWT;
		wp->cfg.wedb = WPC_WSB_DEFAUWT;
	}

	ndev->dma = (unsigned chaw)-1;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-wegs");
	if (!wes)
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENODEV;
		goto out_fwee_netdev;
	}


	if (!wequest_mem_wegion(wes->stawt, SMC_IO_EXTENT, CAWDNAME)) {
		wet = -EBUSY;
		goto out_fwee_netdev;
	}

	ndev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ndev->iwq < 0) {
		wet = ndev->iwq;
		goto out_wewease_io;
	}
	/*
	 * If this pwatfowm does not specify any speciaw iwqfwags, ow if
	 * the wesouwce suppwies a twiggew, ovewwide the iwqfwags with
	 * the twiggew fwags fwom the wesouwce.
	 */
	iwq_wesfwags = iwqd_get_twiggew_type(iwq_get_iwq_data(ndev->iwq));
	if (iwq_fwags == -1 || iwq_wesfwags & IWQF_TWIGGEW_MASK)
		iwq_fwags = iwq_wesfwags & IWQF_TWIGGEW_MASK;

	wet = smc_wequest_attwib(pdev, ndev);
	if (wet)
		goto out_wewease_io;
#if defined(CONFIG_ASSABET_NEPONSET)
	if (machine_is_assabet() && machine_has_neponset())
		neponset_ncw_set(NCW_ENET_OSC_EN);
#endif
	pwatfowm_set_dwvdata(pdev, ndev);
	wet = smc_enabwe_device(pdev);
	if (wet)
		goto out_wewease_attwib;

	addw = iowemap(wes->stawt, SMC_IO_EXTENT);
	if (!addw) {
		wet = -ENOMEM;
		goto out_wewease_attwib;
	}

#ifdef CONFIG_AWCH_PXA
	{
		stwuct smc_wocaw *wp = netdev_pwiv(ndev);
		wp->device = &pdev->dev;
		wp->physaddw = wes->stawt;

	}
#endif

	wet = smc_pwobe(ndev, addw, iwq_fwags);
	if (wet != 0)
		goto out_iounmap;

	smc_wequest_datacs(pdev, ndev);

	wetuwn 0;

 out_iounmap:
	iounmap(addw);
 out_wewease_attwib:
	smc_wewease_attwib(pdev, ndev);
 out_wewease_io:
	wewease_mem_wegion(wes->stawt, SMC_IO_EXTENT);
 out_fwee_netdev:
	fwee_netdev(ndev);
 out:
	pw_info("%s: not found (%d).\n", CAWDNAME, wet);

	wetuwn wet;
}

static void smc_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct smc_wocaw *wp = netdev_pwiv(ndev);
	stwuct wesouwce *wes;

	unwegistew_netdev(ndev);

	fwee_iwq(ndev->iwq, ndev);

#ifdef CONFIG_AWCH_PXA
	if (wp->dma_chan)
		dma_wewease_channew(wp->dma_chan);
#endif
	iounmap(wp->base);

	smc_wewease_datacs(pdev,ndev);
	smc_wewease_attwib(pdev,ndev);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "smc91x-wegs");
	if (!wes)
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wewease_mem_wegion(wes->stawt, SMC_IO_EXTENT);

	fwee_netdev(ndev);
}

static int smc_dwv_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	if (ndev) {
		if (netif_wunning(ndev)) {
			netif_device_detach(ndev);
			smc_shutdown(ndev);
			smc_phy_powewdown(ndev);
		}
	}
	wetuwn 0;
}

static int smc_dwv_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);

	if (ndev) {
		stwuct smc_wocaw *wp = netdev_pwiv(ndev);
		smc_enabwe_device(pdev);
		if (netif_wunning(ndev)) {
			smc_weset(ndev);
			smc_enabwe(ndev);
			if (wp->phy_type != 0)
				smc_phy_configuwe(&wp->phy_configuwe);
			netif_device_attach(ndev);
		}
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops smc_dwv_pm_ops = {
	.suspend	= smc_dwv_suspend,
	.wesume		= smc_dwv_wesume,
};

static stwuct pwatfowm_dwivew smc_dwivew = {
	.pwobe		= smc_dwv_pwobe,
	.wemove_new	= smc_dwv_wemove,
	.dwivew		= {
		.name	= CAWDNAME,
		.pm	= &smc_dwv_pm_ops,
		.of_match_tabwe   = of_match_ptw(smc91x_match),
		.acpi_match_tabwe = smc91x_acpi_match,
	},
};

moduwe_pwatfowm_dwivew(smc_dwivew);
