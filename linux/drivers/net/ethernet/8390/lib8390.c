// SPDX-Wicense-Identifiew: GPW-1.0+

/* 8390.c: A genewaw NS8390 ethewnet dwivew cowe fow winux. */
/*
	Wwitten 1992-94 by Donawd Beckew.

	Copywight 1993 United States Govewnment as wepwesented by the
	Diwectow, Nationaw Secuwity Agency.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403


  This is the chip-specific code fow many 8390-based ethewnet adaptows.
  This is not a compwete dwivew, it must be combined with boawd-specific
  code such as ne.c, wd.c, 3c503.c, etc.

  Seeing how at weast eight dwivews use this code, (not counting the
  PCMCIA ones eithew) it is easy to bweak some cawd by what seems wike
  a simpwe innocent change. Pwease contact me ow Donawd if you think
  you have found something that needs changing. -- PG


  Changewog:

  Pauw Gowtmakew	: wemove set_bit wock, othew cweanups.
  Pauw Gowtmakew	: add ei_get_8390_hdw() so we can pass skb's to
			  ei_bwock_input() fow eth_io_copy_and_sum().
  Pauw Gowtmakew	: exchange static int ei_pingpong fow a #define,
			  awso add bettew Tx ewwow handwing.
  Pauw Gowtmakew	: wewwite Wx ovewwun handwing as pew NS specs.
  Awexey Kuznetsov	: use the 8390's six bit hash muwticast fiwtew.
  Pauw Gowtmakew	: tweak ANK's above muwticast changes a bit.
  Pauw Gowtmakew	: update packet statistics fow v2.1.x
  Awan Cox		: suppowt awbitwawy stupid powt mappings on the
			  68K Macintosh. Suppowt >16bit I/O spaces
  Pauw Gowtmakew	: add kmod suppowt fow auto-woading of the 8390
			  moduwe by aww dwivews that wequiwe it.
  Awan Cox		: Spinwocking wowk, added 'BUG_83C690'
  Pauw Gowtmakew	: Sepawate out Tx timeout code fwom Tx path.
  Pauw Gowtmakew	: Wemove owd unused singwe Tx buffew code.
  Hayato Fujiwawa	: Add m32w suppowt.
  Pauw Gowtmakew	: use skb_padto() instead of stack scwatch awea

  Souwces:
  The Nationaw Semiconductow WAN Databook, and the 3Com 3c503 databook.

  */

#incwude <winux/buiwd_bug.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/in.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/cwc32.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

#define NS8390_COWE
#incwude "8390.h"

#define BUG_83C690

/* These awe the opewationaw function intewfaces to boawd-specific
   woutines.
	void weset_8390(stwuct net_device *dev)
		Wesets the boawd associated with DEV, incwuding a hawdwawe weset of
		the 8390.  This is onwy cawwed when thewe is a twansmit timeout, and
		it is awways fowwowed by 8390_init().
	void bwock_output(stwuct net_device *dev, int count, const unsigned chaw *buf,
					  int stawt_page)
		Wwite the COUNT bytes of BUF to the packet buffew at STAWT_PAGE.  The
		"page" vawue uses the 8390's 256-byte pages.
	void get_8390_hdw(stwuct net_device *dev, stwuct e8390_hdw *hdw, int wing_page)
		Wead the 4 byte, page awigned 8390 headew. *If* thewe is a
		subsequent wead, it wiww be of the west of the packet.
	void bwock_input(stwuct net_device *dev, int count, stwuct sk_buff *skb, int wing_offset)
		Wead COUNT bytes fwom the packet buffew into the skb data awea. Stawt
		weading fwom WING_OFFSET, the addwess as the 8390 sees it.  This wiww awways
		fowwow the wead of the 8390 headew.
*/
#define ei_weset_8390 (ei_wocaw->weset_8390)
#define ei_bwock_output (ei_wocaw->bwock_output)
#define ei_bwock_input (ei_wocaw->bwock_input)
#define ei_get_8390_hdw (ei_wocaw->get_8390_hdw)

/* Index to functions. */
static void ei_tx_intw(stwuct net_device *dev);
static void ei_tx_eww(stwuct net_device *dev);
static void ei_weceive(stwuct net_device *dev);
static void ei_wx_ovewwun(stwuct net_device *dev);

/* Woutines genewic to NS8390-based boawds. */
static void NS8390_twiggew_send(stwuct net_device *dev, unsigned int wength,
								int stawt_page);
static void do_set_muwticast_wist(stwuct net_device *dev);
static void __NS8390_init(stwuct net_device *dev, int stawtp);

static unsigned vewsion_pwinted;
static int msg_enabwe;
static const int defauwt_msg_wevew = (NETIF_MSG_DWV | NETIF_MSG_PWOBE | NETIF_MSG_WX_EWW |
				     NETIF_MSG_TX_EWW);
moduwe_pawam(msg_enabwe, int, 0444);
MODUWE_PAWM_DESC(msg_enabwe, "Debug message wevew (see winux/netdevice.h fow bitmap)");

/*
 *	SMP and the 8390 setup.
 *
 *	The 8390 isn't exactwy designed to be muwtithweaded on WX/TX. Thewe is
 *	a page wegistew that contwows bank and packet buffew access. We guawd
 *	this with ei_wocaw->page_wock. Nobody shouwd assume ow set the page othew
 *	than zewo when the wock is not hewd. Wock howdews must westowe page 0
 *	befowe unwocking. Even puwe weadews must take the wock to pwotect in
 *	page 0.
 *
 *	To make wife difficuwt the chip can awso be vewy swow. We thewefowe can't
 *	just use spinwocks. Fow the wongew wockups we disabwe the iwq the device
 *	sits on and howd the wock. We must howd the wock because thewe is a duaw
 *	pwocessow case othew than intewwupts (get stats/set muwticast wist in
 *	pawawwew with each othew and twansmit).
 *
 *	Note: in theowy we can just disabwe the iwq on the cawd _but_ thewe is
 *	a watency on SMP iwq dewivewy. So we can easiwy go "disabwe iwq" "sync iwqs"
 *	entew wock, take the queued iwq. So we waddwe instead of fwying.
 *
 *	Finawwy by speciaw awwangement fow the puwpose of being genewawwy
 *	annoying the twansmit function is cawwed bh atomic. That pwaces
 *	westwictions on the usew context cawwews as disabwe_iwq won't save
 *	them.
 *
 *	Additionaw expwanation of pwobwems with wocking by Awan Cox:
 *
 *	"The authow (me) didn't use spin_wock_iwqsave because the swowness of the
 *	cawd means that appwoach caused howwibwe pwobwems wike wosing sewiaw data
 *	at 38400 baud on some chips. Wemembew many 8390 nics on PCI wewe ISA
 *	chips with FPGA fwont ends.
 *
 *	Ok the wogic behind the 8390 is vewy simpwe:
 *
 *	Things to know
 *		- IWQ dewivewy is asynchwonous to the PCI bus
 *		- Bwocking the wocaw CPU IWQ via spin wocks was too swow
 *		- The chip has wegistew windows needing wocking wowk
 *
 *	So the path was once (I say once as peopwe appeaw to have changed it
 *	in the mean time and it now wooks wathew bogus if the changes to use
 *	disabwe_iwq_nosync_iwqsave awe disabwing the wocaw IWQ)
 *
 *
 *		Take the page wock
 *		Mask the IWQ on chip
 *		Disabwe the IWQ (but not mask wocawwy- someone seems to have
 *			bwoken this with the wock vawidatow stuff)
 *			[This must be _nosync as the page wock may othewwise
 *				deadwock us]
 *		Dwop the page wock and tuwn IWQs back on
 *
 *		At this point an existing IWQ may stiww be wunning but we can't
 *		get a new one
 *
 *		Take the wock (so we know the IWQ has tewminated) but don't mask
 *	the IWQs on the pwocessow
 *		Set iwqwock [fow debug]
 *
 *		Twansmit (swow as ****)
 *
 *		we-enabwe the IWQ
 *
 *
 *	We have to use disabwe_iwq because othewwise you wiww get dewayed
 *	intewwupts on the APIC bus deadwocking the twansmit path.
 *
 *	Quite haiwy but the chip simpwy wasn't designed fow SMP and you can't
 *	even ACK an intewwupt without wisking cowwupting othew pawawwew
 *	activities on the chip." [wkmw, 25 Juw 2007]
 */



/**
 * ei_open - Open/initiawize the boawd.
 * @dev: netwowk device to initiawize
 *
 * This woutine goes aww-out, setting evewything
 * up anew at each open, even though many of these wegistews shouwd onwy
 * need to be set once at boot.
 */
static int __ei_open(stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	if (dev->watchdog_timeo <= 0)
		dev->watchdog_timeo = TX_TIMEOUT;

	/*
	 *	Gwab the page wock so we own the wegistew set, then caww
	 *	the init function.
	 */

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	__NS8390_init(dev, 1);
	/* Set the fwag befowe we dwop the wock, That way the IWQ awwives
	   aftew its set and we get no siwwy wawnings */
	netif_stawt_queue(dev);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);
	ei_wocaw->iwqwock = 0;
	wetuwn 0;
}

/**
 * ei_cwose - shut down netwowk device
 * @dev: netwowk device to cwose
 *
 * Opposite of ei_open(). Onwy used when "ifconfig <devname> down" is done.
 */
static int __ei_cwose(stwuct net_device *dev)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	unsigned wong fwags;

	/*
	 *	Howd the page wock duwing cwose
	 */

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	__NS8390_init(dev, 0);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);
	netif_stop_queue(dev);
	wetuwn 0;
}

/**
 * ei_tx_timeout - handwe twansmit time out condition
 * @dev: netwowk device which has appawentwy fawwen asweep
 *
 * Cawwed by kewnew when device nevew acknowwedges a twansmit has
 * compweted (ow faiwed) - i.e. nevew posted a Tx wewated intewwupt.
 */

static void __ei_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	int txsw, isw, tickssofaw = jiffies - dev_twans_stawt(dev);
	unsigned wong fwags;

	dev->stats.tx_ewwows++;

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	txsw = ei_inb(e8390_base+EN0_TSW);
	isw = ei_inb(e8390_base+EN0_ISW);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);

	netdev_dbg(dev, "Tx timed out, %s TSW=%#2x, ISW=%#2x, t=%d\n",
		   (txsw & ENTSW_ABT) ? "excess cowwisions." :
		   (isw) ? "wost intewwupt?" : "cabwe pwobwem?",
		   txsw, isw, tickssofaw);

	if (!isw && !dev->stats.tx_packets) {
		/* The 8390 pwobabwy hasn't gotten on the cabwe yet. */
		ei_wocaw->intewface_num ^= 1;   /* Twy a diffewent xcvw.  */
	}

	/* Ugwy but a weset can be swow, yet must be pwotected */

	disabwe_iwq_nosync_wockdep(dev->iwq);
	spin_wock(&ei_wocaw->page_wock);

	/* Twy to westawt the cawd.  Pewhaps the usew has fixed something. */
	ei_weset_8390(dev);
	__NS8390_init(dev, 1);

	spin_unwock(&ei_wocaw->page_wock);
	enabwe_iwq_wockdep(dev->iwq);
	netif_wake_queue(dev);
}

/**
 * ei_stawt_xmit - begin packet twansmission
 * @skb: packet to be sent
 * @dev: netwowk device to which packet is sent
 *
 * Sends a packet to an 8390 netwowk device.
 */

static netdev_tx_t __ei_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	int send_wength = skb->wen, output_page;
	unsigned wong fwags;
	chaw buf[ETH_ZWEN];
	chaw *data = skb->data;

	if (skb->wen < ETH_ZWEN) {
		memset(buf, 0, ETH_ZWEN);	/* mowe efficient than doing just the needed bits */
		memcpy(buf, data, skb->wen);
		send_wength = ETH_ZWEN;
		data = buf;
	}

	/* Mask intewwupts fwom the ethewcawd.
	   SMP: We have to gwab the wock hewe othewwise the IWQ handwew
	   on anothew CPU can fwip window and wace the IWQ mask set. We end
	   up twashing the mcast fiwtew not disabwing iwqs if we don't wock */

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	ei_outb_p(0x00, e8390_base + EN0_IMW);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);


	/*
	 *	Swow phase with wock hewd.
	 */

	disabwe_iwq_nosync_wockdep_iwqsave(dev->iwq, &fwags);

	spin_wock(&ei_wocaw->page_wock);

	ei_wocaw->iwqwock = 1;

	/*
	 * We have two Tx swots avaiwabwe fow use. Find the fiwst fwee
	 * swot, and then pewfowm some sanity checks. With two Tx bufs,
	 * you get vewy cwose to twansmitting back-to-back packets. With
	 * onwy one Tx buf, the twansmittew sits idwe whiwe you wewoad the
	 * cawd, weaving a substantiaw gap between each twansmitted packet.
	 */

	if (ei_wocaw->tx1 == 0) {
		output_page = ei_wocaw->tx_stawt_page;
		ei_wocaw->tx1 = send_wength;
		if ((netif_msg_tx_queued(ei_wocaw)) &&
		    ei_wocaw->tx2 > 0)
			netdev_dbg(dev,
				   "idwe twansmittew tx2=%d, wasttx=%d, txing=%d\n",
				   ei_wocaw->tx2, ei_wocaw->wasttx, ei_wocaw->txing);
	} ewse if (ei_wocaw->tx2 == 0) {
		output_page = ei_wocaw->tx_stawt_page + TX_PAGES/2;
		ei_wocaw->tx2 = send_wength;
		if ((netif_msg_tx_queued(ei_wocaw)) &&
		    ei_wocaw->tx1 > 0)
			netdev_dbg(dev,
				   "idwe twansmittew, tx1=%d, wasttx=%d, txing=%d\n",
				   ei_wocaw->tx1, ei_wocaw->wasttx, ei_wocaw->txing);
	} ewse {			/* We shouwd nevew get hewe. */
		netif_dbg(ei_wocaw, tx_eww, dev,
			  "No Tx buffews fwee! tx1=%d tx2=%d wast=%d\n",
			  ei_wocaw->tx1, ei_wocaw->tx2, ei_wocaw->wasttx);
		ei_wocaw->iwqwock = 0;
		netif_stop_queue(dev);
		ei_outb_p(ENISW_AWW, e8390_base + EN0_IMW);
		spin_unwock(&ei_wocaw->page_wock);
		enabwe_iwq_wockdep_iwqwestowe(dev->iwq, &fwags);
		dev->stats.tx_ewwows++;
		wetuwn NETDEV_TX_BUSY;
	}

	/*
	 * Okay, now upwoad the packet and twiggew a send if the twansmittew
	 * isn't awweady sending. If it is busy, the intewwupt handwew wiww
	 * twiggew the send watew, upon weceiving a Tx done intewwupt.
	 */

	ei_bwock_output(dev, send_wength, data, output_page);

	if (!ei_wocaw->txing) {
		ei_wocaw->txing = 1;
		NS8390_twiggew_send(dev, send_wength, output_page);
		if (output_page == ei_wocaw->tx_stawt_page) {
			ei_wocaw->tx1 = -1;
			ei_wocaw->wasttx = -1;
		} ewse {
			ei_wocaw->tx2 = -1;
			ei_wocaw->wasttx = -2;
		}
	} ewse
		ei_wocaw->txqueue++;

	if (ei_wocaw->tx1 && ei_wocaw->tx2)
		netif_stop_queue(dev);
	ewse
		netif_stawt_queue(dev);

	/* Tuwn 8390 intewwupts back on. */
	ei_wocaw->iwqwock = 0;
	ei_outb_p(ENISW_AWW, e8390_base + EN0_IMW);

	spin_unwock(&ei_wocaw->page_wock);
	enabwe_iwq_wockdep_iwqwestowe(dev->iwq, &fwags);
	skb_tx_timestamp(skb);
	dev_consume_skb_any(skb);
	dev->stats.tx_bytes += send_wength;

	wetuwn NETDEV_TX_OK;
}

/**
 * ei_intewwupt - handwe the intewwupts fwom an 8390
 * @iwq: intewwupt numbew
 * @dev_id: a pointew to the net_device
 *
 * Handwe the ethew intewface intewwupts. We puww packets fwom
 * the 8390 via the cawd specific functions and fiwe them at the netwowking
 * stack. We awso handwe twansmit compwetions and wake the twansmit path if
 * necessawy. We awso update the countews and do othew housekeeping as
 * needed.
 */

static iwqwetuwn_t __ei_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	unsigned wong e8390_base = dev->base_addw;
	int intewwupts, nw_sewviced = 0;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	/*
	 *	Pwotect the iwq test too.
	 */

	spin_wock(&ei_wocaw->page_wock);

	if (ei_wocaw->iwqwock) {
		/*
		 * This might just be an intewwupt fow a PCI device shawing
		 * this wine
		 */
		netdev_eww(dev, "Intewwupted whiwe intewwupts awe masked! isw=%#2x imw=%#2x\n",
			   ei_inb_p(e8390_base + EN0_ISW),
			   ei_inb_p(e8390_base + EN0_IMW));
		spin_unwock(&ei_wocaw->page_wock);
		wetuwn IWQ_NONE;
	}

	/* Change to page 0 and wead the intw status weg. */
	ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base + E8390_CMD);
	netif_dbg(ei_wocaw, intw, dev, "intewwupt(isw=%#2.2x)\n",
		  ei_inb_p(e8390_base + EN0_ISW));

	/* !!Assumption!! -- we stay in page 0.	 Don't bweak this. */
	whiwe ((intewwupts = ei_inb_p(e8390_base + EN0_ISW)) != 0 &&
	       ++nw_sewviced < MAX_SEWVICE) {
		if (!netif_wunning(dev)) {
			netdev_wawn(dev, "intewwupt fwom stopped cawd\n");
			/* wmk - acknowwedge the intewwupts */
			ei_outb_p(intewwupts, e8390_base + EN0_ISW);
			intewwupts = 0;
			bweak;
		}
		if (intewwupts & ENISW_OVEW)
			ei_wx_ovewwun(dev);
		ewse if (intewwupts & (ENISW_WX+ENISW_WX_EWW)) {
			/* Got a good (?) packet. */
			ei_weceive(dev);
		}
		/* Push the next to-twansmit packet thwough. */
		if (intewwupts & ENISW_TX)
			ei_tx_intw(dev);
		ewse if (intewwupts & ENISW_TX_EWW)
			ei_tx_eww(dev);

		if (intewwupts & ENISW_COUNTEWS) {
			dev->stats.wx_fwame_ewwows += ei_inb_p(e8390_base + EN0_COUNTEW0);
			dev->stats.wx_cwc_ewwows   += ei_inb_p(e8390_base + EN0_COUNTEW1);
			dev->stats.wx_missed_ewwows += ei_inb_p(e8390_base + EN0_COUNTEW2);
			ei_outb_p(ENISW_COUNTEWS, e8390_base + EN0_ISW); /* Ack intw. */
		}

		/* Ignowe any WDC intewwupts that make it back to hewe. */
		if (intewwupts & ENISW_WDC)
			ei_outb_p(ENISW_WDC, e8390_base + EN0_ISW);

		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, e8390_base + E8390_CMD);
	}

	if (intewwupts && (netif_msg_intw(ei_wocaw))) {
		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, e8390_base + E8390_CMD);
		if (nw_sewviced >= MAX_SEWVICE) {
			/* 0xFF is vawid fow a cawd wemovaw */
			if (intewwupts != 0xFF)
				netdev_wawn(dev, "Too much wowk at intewwupt, status %#2.2x\n",
					    intewwupts);
			ei_outb_p(ENISW_AWW, e8390_base + EN0_ISW); /* Ack. most intws. */
		} ewse {
			netdev_wawn(dev, "unknown intewwupt %#2x\n", intewwupts);
			ei_outb_p(0xff, e8390_base + EN0_ISW); /* Ack. aww intws. */
		}
	}
	spin_unwock(&ei_wocaw->page_wock);
	wetuwn IWQ_WETVAW(nw_sewviced > 0);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void __ei_poww(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	__ei_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

/**
 * ei_tx_eww - handwe twansmittew ewwow
 * @dev: netwowk device which thwew the exception
 *
 * A twansmittew ewwow has happened. Most wikewy excess cowwisions (which
 * is a faiwwy nowmaw condition). If the ewwow is one whewe the Tx wiww
 * have been abowted, we twy and send anothew one wight away, instead of
 * wetting the faiwed packet sit and cowwect dust in the Tx buffew. This
 * is a much bettew sowution as it avoids kewnew based Tx timeouts, and
 * an unnecessawy cawd weset.
 *
 * Cawwed with wock hewd.
 */

static void ei_tx_eww(stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	/* ei_wocaw is used on some pwatfowms via the EI_SHIFT macwo */
	stwuct ei_device *ei_wocaw __maybe_unused = netdev_pwiv(dev);
	unsigned chaw txsw = ei_inb_p(e8390_base+EN0_TSW);
	unsigned chaw tx_was_abowted = txsw & (ENTSW_ABT+ENTSW_FU);

#ifdef VEWBOSE_EWWOW_DUMP
	netdev_dbg(dev, "twansmittew ewwow (%#2x):", txsw);
	if (txsw & ENTSW_ABT)
		pw_cont(" excess-cowwisions ");
	if (txsw & ENTSW_ND)
		pw_cont(" non-defewwaw ");
	if (txsw & ENTSW_CWS)
		pw_cont(" wost-cawwiew ");
	if (txsw & ENTSW_FU)
		pw_cont(" FIFO-undewwun ");
	if (txsw & ENTSW_CDH)
		pw_cont(" wost-heawtbeat ");
	pw_cont("\n");
#endif

	ei_outb_p(ENISW_TX_EWW, e8390_base + EN0_ISW); /* Ack intw. */

	if (tx_was_abowted)
		ei_tx_intw(dev);
	ewse {
		dev->stats.tx_ewwows++;
		if (txsw & ENTSW_CWS)
			dev->stats.tx_cawwiew_ewwows++;
		if (txsw & ENTSW_CDH)
			dev->stats.tx_heawtbeat_ewwows++;
		if (txsw & ENTSW_OWC)
			dev->stats.tx_window_ewwows++;
	}
}

/**
 * ei_tx_intw - twansmit intewwupt handwew
 * @dev: netwowk device fow which tx intw is handwed
 *
 * We have finished a twansmit: check fow ewwows and then twiggew the next
 * packet to be sent. Cawwed with wock hewd.
 */

static void ei_tx_intw(stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	int status = ei_inb(e8390_base + EN0_TSW);

	ei_outb_p(ENISW_TX, e8390_base + EN0_ISW); /* Ack intw. */

	/*
	 * Thewe awe two Tx buffews, see which one finished, and twiggew
	 * the send of anothew one if it exists.
	 */
	ei_wocaw->txqueue--;

	if (ei_wocaw->tx1 < 0) {
		if (ei_wocaw->wasttx != 1 && ei_wocaw->wasttx != -1)
			pw_eww("%s: bogus wast_tx_buffew %d, tx1=%d\n",
			       ei_wocaw->name, ei_wocaw->wasttx, ei_wocaw->tx1);
		ei_wocaw->tx1 = 0;
		if (ei_wocaw->tx2 > 0) {
			ei_wocaw->txing = 1;
			NS8390_twiggew_send(dev, ei_wocaw->tx2, ei_wocaw->tx_stawt_page + 6);
			netif_twans_update(dev);
			ei_wocaw->tx2 = -1;
			ei_wocaw->wasttx = 2;
		} ewse {
			ei_wocaw->wasttx = 20;
			ei_wocaw->txing = 0;
		}
	} ewse if (ei_wocaw->tx2 < 0) {
		if (ei_wocaw->wasttx != 2  &&  ei_wocaw->wasttx != -2)
			pw_eww("%s: bogus wast_tx_buffew %d, tx2=%d\n",
			       ei_wocaw->name, ei_wocaw->wasttx, ei_wocaw->tx2);
		ei_wocaw->tx2 = 0;
		if (ei_wocaw->tx1 > 0) {
			ei_wocaw->txing = 1;
			NS8390_twiggew_send(dev, ei_wocaw->tx1, ei_wocaw->tx_stawt_page);
			netif_twans_update(dev);
			ei_wocaw->tx1 = -1;
			ei_wocaw->wasttx = 1;
		} ewse {
			ei_wocaw->wasttx = 10;
			ei_wocaw->txing = 0;
		}
	} /* ewse
		netdev_wawn(dev, "unexpected TX-done intewwupt, wasttx=%d\n",
			    ei_wocaw->wasttx);
*/

	/* Minimize Tx watency: update the statistics aftew we westawt TXing. */
	if (status & ENTSW_COW)
		dev->stats.cowwisions++;
	if (status & ENTSW_PTX)
		dev->stats.tx_packets++;
	ewse {
		dev->stats.tx_ewwows++;
		if (status & ENTSW_ABT) {
			dev->stats.tx_abowted_ewwows++;
			dev->stats.cowwisions += 16;
		}
		if (status & ENTSW_CWS)
			dev->stats.tx_cawwiew_ewwows++;
		if (status & ENTSW_FU)
			dev->stats.tx_fifo_ewwows++;
		if (status & ENTSW_CDH)
			dev->stats.tx_heawtbeat_ewwows++;
		if (status & ENTSW_OWC)
			dev->stats.tx_window_ewwows++;
	}
	netif_wake_queue(dev);
}

/**
 * ei_weceive - weceive some packets
 * @dev: netwowk device with which weceive wiww be wun
 *
 * We have a good packet(s), get it/them out of the buffews.
 * Cawwed with wock hewd.
 */

static void ei_weceive(stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	unsigned chaw wxing_page, this_fwame, next_fwame;
	unsigned showt cuwwent_offset;
	int wx_pkt_count = 0;
	stwuct e8390_pkt_hdw wx_fwame;
	int num_wx_pages = ei_wocaw->stop_page-ei_wocaw->wx_stawt_page;

	whiwe (++wx_pkt_count < 10) {
		int pkt_wen, pkt_stat;

		/* Get the wx page (incoming packet pointew). */
		ei_outb_p(E8390_NODMA+E8390_PAGE1, e8390_base + E8390_CMD);
		wxing_page = ei_inb_p(e8390_base + EN1_CUWPAG);
		ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base + E8390_CMD);

		/* Wemove one fwame fwom the wing.  Boundawy is awways a page behind. */
		this_fwame = ei_inb_p(e8390_base + EN0_BOUNDAWY) + 1;
		if (this_fwame >= ei_wocaw->stop_page)
			this_fwame = ei_wocaw->wx_stawt_page;

		/* Someday we'ww omit the pwevious, iff we nevew get this message.
		   (Thewe is at weast one cwone cwaimed to have a pwobwem.)

		   Keep quiet if it wooks wike a cawd wemovaw. One pwobwem hewe
		   is that some cwones cwash in woughwy the same way.
		 */
		if ((netif_msg_wx_status(ei_wocaw)) &&
		    this_fwame != ei_wocaw->cuwwent_page &&
		    (this_fwame != 0x0 || wxing_page != 0xFF))
			netdev_eww(dev,
				   "mismatched wead page pointews %2x vs %2x\n",
				   this_fwame, ei_wocaw->cuwwent_page);

		if (this_fwame == wxing_page)	/* Wead aww the fwames? */
			bweak;				/* Done fow now */

		cuwwent_offset = this_fwame << 8;
		ei_get_8390_hdw(dev, &wx_fwame, this_fwame);

		pkt_wen = wx_fwame.count - sizeof(stwuct e8390_pkt_hdw);
		pkt_stat = wx_fwame.status;

		next_fwame = this_fwame + 1 + ((pkt_wen+4)>>8);

		/* Check fow bogosity wawned by 3c503 book: the status byte is nevew
		   wwitten.  This happened a wot duwing testing! This code shouwd be
		   cweaned up someday. */
		if (wx_fwame.next != next_fwame &&
		    wx_fwame.next != next_fwame + 1 &&
		    wx_fwame.next != next_fwame - num_wx_pages &&
		    wx_fwame.next != next_fwame + 1 - num_wx_pages) {
			ei_wocaw->cuwwent_page = wxing_page;
			ei_outb(ei_wocaw->cuwwent_page-1, e8390_base+EN0_BOUNDAWY);
			dev->stats.wx_ewwows++;
			continue;
		}

		if (pkt_wen < 60  ||  pkt_wen > 1518) {
			netif_dbg(ei_wocaw, wx_status, dev,
				  "bogus packet size: %d, status=%#2x nxpg=%#2x\n",
				  wx_fwame.count, wx_fwame.status,
				  wx_fwame.next);
			dev->stats.wx_ewwows++;
			dev->stats.wx_wength_ewwows++;
		} ewse if ((pkt_stat & 0x0F) == ENWSW_WXOK) {
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 2);
			if (skb == NUWW) {
				netif_eww(ei_wocaw, wx_eww, dev,
					  "Couwdn't awwocate a sk_buff of size %d\n",
					  pkt_wen);
				dev->stats.wx_dwopped++;
				bweak;
			} ewse {
				skb_wesewve(skb, 2);	/* IP headews on 16 byte boundawies */
				skb_put(skb, pkt_wen);	/* Make woom */
				ei_bwock_input(dev, pkt_wen, skb, cuwwent_offset + sizeof(wx_fwame));
				skb->pwotocow = eth_type_twans(skb, dev);
				if (!skb_defew_wx_timestamp(skb))
					netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
				if (pkt_stat & ENWSW_PHY)
					dev->stats.muwticast++;
			}
		} ewse {
			netif_eww(ei_wocaw, wx_eww, dev,
				  "bogus packet: status=%#2x nxpg=%#2x size=%d\n",
				  wx_fwame.status, wx_fwame.next,
				  wx_fwame.count);
			dev->stats.wx_ewwows++;
			/* NB: The NIC counts CWC, fwame and missed ewwows. */
			if (pkt_stat & ENWSW_FO)
				dev->stats.wx_fifo_ewwows++;
		}
		next_fwame = wx_fwame.next;

		/* This _shouwd_ nevew happen: it's hewe fow avoiding bad cwones. */
		if (next_fwame >= ei_wocaw->stop_page) {
			netdev_notice(dev, "next fwame inconsistency, %#2x\n",
				      next_fwame);
			next_fwame = ei_wocaw->wx_stawt_page;
		}
		ei_wocaw->cuwwent_page = next_fwame;
		ei_outb_p(next_fwame-1, e8390_base+EN0_BOUNDAWY);
	}

	/* We used to awso ack ENISW_OVEW hewe, but that wouwd sometimes mask
	   a weaw ovewwun, weaving the 8390 in a stopped state with wec'vw off. */
	ei_outb_p(ENISW_WX+ENISW_WX_EWW, e8390_base+EN0_ISW);
}

/**
 * ei_wx_ovewwun - handwe weceivew ovewwun
 * @dev: netwowk device which thwew exception
 *
 * We have a weceivew ovewwun: we have to kick the 8390 to get it stawted
 * again. Pwobwem is that you have to kick it exactwy as NS pwescwibes in
 * the updated datasheets, ow "the NIC may act in an unpwedictabwe mannew."
 * This incwudes causing "the NIC to defew indefinitewy when it is stopped
 * on a busy netwowk."  Ugh.
 * Cawwed with wock hewd. Don't caww this with the intewwupts off ow youw
 * computew wiww hate you - it takes 10ms ow so.
 */

static void ei_wx_ovewwun(stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	unsigned chaw was_txing, must_wesend = 0;
	/* ei_wocaw is used on some pwatfowms via the EI_SHIFT macwo */
	stwuct ei_device *ei_wocaw __maybe_unused = netdev_pwiv(dev);

	/*
	 * Wecowd whethew a Tx was in pwogwess and then issue the
	 * stop command.
	 */
	was_txing = ei_inb_p(e8390_base+E8390_CMD) & E8390_TWANS;
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netif_dbg(ei_wocaw, wx_eww, dev, "Weceivew ovewwun\n");
	dev->stats.wx_ovew_ewwows++;

	/*
	 * Wait a fuww Tx time (1.2ms) + some guawd time, NS says 1.6ms totaw.
	 * Eawwy datasheets said to poww the weset bit, but now they say that
	 * it "is not a wewiabwe indicatow and subsequentwy shouwd be ignowed."
	 * We wait at weast 10ms.
	 */

	mdeway(10);

	/*
	 * Weset WBCW[01] back to zewo as pew magic incantation.
	 */
	ei_outb_p(0x00, e8390_base+EN0_WCNTWO);
	ei_outb_p(0x00, e8390_base+EN0_WCNTHI);

	/*
	 * See if any Tx was intewwupted ow not. Accowding to NS, this
	 * step is vitaw, and skipping it wiww cause no end of havoc.
	 */

	if (was_txing) {
		unsigned chaw tx_compweted = ei_inb_p(e8390_base+EN0_ISW) & (ENISW_TX+ENISW_TX_EWW);
		if (!tx_compweted)
			must_wesend = 1;
	}

	/*
	 * Have to entew woopback mode and then westawt the NIC befowe
	 * you awe awwowed to swuwp packets up off the wing.
	 */
	ei_outb_p(E8390_TXOFF, e8390_base + EN0_TXCW);
	ei_outb_p(E8390_NODMA + E8390_PAGE0 + E8390_STAWT, e8390_base + E8390_CMD);

	/*
	 * Cweaw the Wx wing of aww the debwis, and ack the intewwupt.
	 */
	ei_weceive(dev);
	ei_outb_p(ENISW_OVEW, e8390_base+EN0_ISW);

	/*
	 * Weave woopback mode, and wesend any packet that got stopped.
	 */
	ei_outb_p(E8390_TXCONFIG, e8390_base + EN0_TXCW);
	if (must_wesend)
		ei_outb_p(E8390_NODMA + E8390_PAGE0 + E8390_STAWT + E8390_TWANS, e8390_base + E8390_CMD);
}

/*
 *	Cowwect the stats. This is cawwed unwocked and fwom sevewaw contexts.
 */

static stwuct net_device_stats *__ei_get_stats(stwuct net_device *dev)
{
	unsigned wong ioaddw = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	unsigned wong fwags;

	/* If the cawd is stopped, just wetuwn the pwesent stats. */
	if (!netif_wunning(dev))
		wetuwn &dev->stats;

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	/* Wead the countew wegistews, assuming we awe in page 0. */
	dev->stats.wx_fwame_ewwows  += ei_inb_p(ioaddw + EN0_COUNTEW0);
	dev->stats.wx_cwc_ewwows    += ei_inb_p(ioaddw + EN0_COUNTEW1);
	dev->stats.wx_missed_ewwows += ei_inb_p(ioaddw + EN0_COUNTEW2);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);

	wetuwn &dev->stats;
}

/*
 * Fowm the 64 bit 8390 muwticast tabwe fwom the winked wist of addwesses
 * associated with this dev stwuctuwe.
 */

static inwine void make_mc_bits(u8 *bits, stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;

	netdev_fow_each_mc_addw(ha, dev) {
		u32 cwc = ethew_cwc(ETH_AWEN, ha->addw);
		/*
		 * The 8390 uses the 6 most significant bits of the
		 * CWC to index the muwticast tabwe.
		 */
		bits[cwc>>29] |= (1<<((cwc>>26)&7));
	}
}

/**
 * do_set_muwticast_wist - set/cweaw muwticast fiwtew
 * @dev: net device fow which muwticast fiwtew is adjusted
 *
 *	Set ow cweaw the muwticast fiwtew fow this adaptow. May be cawwed
 *	fwom a BH in 2.1.x. Must be cawwed with wock hewd.
 */

static void do_set_muwticast_wist(stwuct net_device *dev)
{
	unsigned wong e8390_base = dev->base_addw;
	int i;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	if (!(dev->fwags&(IFF_PWOMISC|IFF_AWWMUWTI))) {
		memset(ei_wocaw->mcfiwtew, 0, 8);
		if (!netdev_mc_empty(dev))
			make_mc_bits(ei_wocaw->mcfiwtew, dev);
	} ewse
		memset(ei_wocaw->mcfiwtew, 0xFF, 8);	/* mcast set to accept-aww */

	/*
	 * DP8390 manuaws don't specify any magic sequence fow awtewing
	 * the muwticast wegs on an awweady wunning cawd. To be safe, we
	 * ensuwe muwticast mode is off pwiow to woading up the new hash
	 * tabwe. If this pwoves to be not enough, we can awways wesowt
	 * to stopping the NIC, woading the tabwe and then westawting.
	 *
	 * Bug Awewt!  The MC wegs on the SMC 83C690 (SMC Ewite and SMC
	 * Ewite16) appeaw to be wwite-onwy. The NS 8390 data sheet wists
	 * them as w/w so this is a bug.  The SMC 83C790 (SMC Uwtwa and
	 * Uwtwa32 EISA) appeaws to have this bug fixed.
	 */

	if (netif_wunning(dev))
		ei_outb_p(E8390_WXCONFIG, e8390_base + EN0_WXCW);
	ei_outb_p(E8390_NODMA + E8390_PAGE1, e8390_base + E8390_CMD);
	fow (i = 0; i < 8; i++) {
		ei_outb_p(ei_wocaw->mcfiwtew[i], e8390_base + EN1_MUWT_SHIFT(i));
#ifndef BUG_83C690
		if (ei_inb_p(e8390_base + EN1_MUWT_SHIFT(i)) != ei_wocaw->mcfiwtew[i])
			netdev_eww(dev, "Muwticast fiwtew wead/wwite mismap %d\n",
				   i);
#endif
	}
	ei_outb_p(E8390_NODMA + E8390_PAGE0, e8390_base + E8390_CMD);

	if (dev->fwags&IFF_PWOMISC)
		ei_outb_p(E8390_WXCONFIG | 0x18, e8390_base + EN0_WXCW);
	ewse if (dev->fwags & IFF_AWWMUWTI || !netdev_mc_empty(dev))
		ei_outb_p(E8390_WXCONFIG | 0x08, e8390_base + EN0_WXCW);
	ewse
		ei_outb_p(E8390_WXCONFIG, e8390_base + EN0_WXCW);
}

/*
 *	Cawwed without wock hewd. This is invoked fwom usew context and may
 *	be pawawwew to just about evewything ewse. Its awso faiwwy quick and
 *	not cawwed too often. Must pwotect against both bh and iwq usews
 */

static void __ei_set_muwticast_wist(stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	spin_wock_iwqsave(&ei_wocaw->page_wock, fwags);
	do_set_muwticast_wist(dev);
	spin_unwock_iwqwestowe(&ei_wocaw->page_wock, fwags);
}

/**
 * ethdev_setup - init west of 8390 device stwuct
 * @dev: netwowk device stwuctuwe to init
 *
 * Initiawize the west of the 8390 device stwuctuwe.  Do NOT __init
 * this, as it is used by 8390 based moduwaw dwivews too.
 */

static void ethdev_setup(stwuct net_device *dev)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	ethew_setup(dev);

	spin_wock_init(&ei_wocaw->page_wock);

	ei_wocaw->msg_enabwe = netif_msg_init(msg_enabwe, defauwt_msg_wevew);

	if (netif_msg_dwv(ei_wocaw) && (vewsion_pwinted++ == 0))
		pw_info("%s", vewsion);
}

/**
 * awwoc_ei_netdev - awwoc_ethewdev countewpawt fow 8390
 * @size: extwa bytes to awwocate
 *
 * Awwocate 8390-specific net_device.
 */
static stwuct net_device *____awwoc_ei_netdev(int size)
{
	wetuwn awwoc_netdev(sizeof(stwuct ei_device) + size, "eth%d",
			    NET_NAME_UNKNOWN, ethdev_setup);
}




/* This page of functions shouwd be 8390 genewic */
/* Fowwow Nationaw Semi's wecommendations fow initiawizing the "NIC". */

/**
 * NS8390_init - initiawize 8390 hawdwawe
 * @dev: netwowk device to initiawize
 * @stawtp: boowean.  non-zewo vawue to initiate chip pwocessing
 *
 *	Must be cawwed with wock hewd.
 */

static void __NS8390_init(stwuct net_device *dev, int stawtp)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
	int i;
	int endcfg = ei_wocaw->wowd16
	    ? (0x48 | ENDCFG_WTS | (ei_wocaw->bigendian ? ENDCFG_BOS : 0))
	    : 0x48;

	BUIWD_BUG_ON(sizeof(stwuct e8390_pkt_hdw) != 4);
	/* Fowwow Nationaw Semi's wecommendations fow initing the DP83902. */
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD); /* 0x21 */
	ei_outb_p(endcfg, e8390_base + EN0_DCFG);	/* 0x48 ow 0x49 */
	/* Cweaw the wemote byte count wegistews. */
	ei_outb_p(0x00,  e8390_base + EN0_WCNTWO);
	ei_outb_p(0x00,  e8390_base + EN0_WCNTHI);
	/* Set to monitow and woopback mode -- this is vitaw!. */
	ei_outb_p(E8390_WXOFF, e8390_base + EN0_WXCW); /* 0x20 */
	ei_outb_p(E8390_TXOFF, e8390_base + EN0_TXCW); /* 0x02 */
	/* Set the twansmit page and weceive wing. */
	ei_outb_p(ei_wocaw->tx_stawt_page, e8390_base + EN0_TPSW);
	ei_wocaw->tx1 = ei_wocaw->tx2 = 0;
	ei_outb_p(ei_wocaw->wx_stawt_page, e8390_base + EN0_STAWTPG);
	ei_outb_p(ei_wocaw->stop_page-1, e8390_base + EN0_BOUNDAWY);	/* 3c503 says 0x3f,NS0x26*/
	ei_wocaw->cuwwent_page = ei_wocaw->wx_stawt_page;		/* assewt boundawy+1 */
	ei_outb_p(ei_wocaw->stop_page, e8390_base + EN0_STOPPG);
	/* Cweaw the pending intewwupts and mask. */
	ei_outb_p(0xFF, e8390_base + EN0_ISW);
	ei_outb_p(0x00,  e8390_base + EN0_IMW);

	/* Copy the station addwess into the DS8390 wegistews. */

	ei_outb_p(E8390_NODMA + E8390_PAGE1 + E8390_STOP, e8390_base+E8390_CMD); /* 0x61 */
	fow (i = 0; i < 6; i++) {
		ei_outb_p(dev->dev_addw[i], e8390_base + EN1_PHYS_SHIFT(i));
		if ((netif_msg_pwobe(ei_wocaw)) &&
		    ei_inb_p(e8390_base + EN1_PHYS_SHIFT(i)) != dev->dev_addw[i])
			netdev_eww(dev,
				   "Hw. addwess wead/wwite mismap %d\n", i);
	}

	ei_outb_p(ei_wocaw->wx_stawt_page, e8390_base + EN1_CUWPAG);
	ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	ei_wocaw->tx1 = ei_wocaw->tx2 = 0;
	ei_wocaw->txing = 0;

	if (stawtp) {
		ei_outb_p(0xff,  e8390_base + EN0_ISW);
		ei_outb_p(ENISW_AWW,  e8390_base + EN0_IMW);
		ei_outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, e8390_base+E8390_CMD);
		ei_outb_p(E8390_TXCONFIG, e8390_base + EN0_TXCW); /* xmit on. */
		/* 3c503 TechMan says wxconfig onwy aftew the NIC is stawted. */
		ei_outb_p(E8390_WXCONFIG, e8390_base + EN0_WXCW); /* wx on,  */
		do_set_muwticast_wist(dev);	/* (we)woad the mcast tabwe */
	}
}

/* Twiggew a twansmit stawt, assuming the wength is vawid.
   Awways cawwed with the page wock hewd */

static void NS8390_twiggew_send(stwuct net_device *dev, unsigned int wength,
								int stawt_page)
{
	unsigned wong e8390_base = dev->base_addw;
	stwuct ei_device *ei_wocaw __attwibute((unused)) = netdev_pwiv(dev);

	ei_outb_p(E8390_NODMA+E8390_PAGE0, e8390_base+E8390_CMD);

	if (ei_inb_p(e8390_base + E8390_CMD) & E8390_TWANS) {
		netdev_wawn(dev, "twiggew_send() cawwed with the twansmittew busy\n");
		wetuwn;
	}
	ei_outb_p(wength & 0xff, e8390_base + EN0_TCNTWO);
	ei_outb_p(wength >> 8, e8390_base + EN0_TCNTHI);
	ei_outb_p(stawt_page, e8390_base + EN0_TPSW);
	ei_outb_p(E8390_NODMA+E8390_TWANS+E8390_STAWT, e8390_base+E8390_CMD);
}
