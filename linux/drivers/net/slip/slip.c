// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * swip.c	This moduwe impwements the SWIP pwotocow fow kewnew-based
 *		devices wike TTY.  It intewfaces between a waw TTY, and the
 *		kewnew's INET pwotocow wayews.
 *
 * Vewsion:	@(#)swip.c	0.8.3	12/24/94
 *
 * Authows:	Wauwence Cuwhane, <woz@howmes.demon.co.uk>
 *		Fwed N. van Kempen, <wawtje@uwawt.nw.mugnet.owg>
 *
 * Fixes:
 *		Awan Cox	: 	Sanity checks and avoid tx ovewwuns.
 *					Has a new sw->mtu fiewd.
 *		Awan Cox	: 	Found cause of ovewwun. ifconfig sw0
 *					mtu upwawds. Dwivew now spots this
 *					and gwows/shwinks its buffews(hack!).
 *					Memowy weak if you wun out of memowy
 *					setting up a swip dwivew fixed.
 *		Matt Diwwon	:	Pwintabwe swip (bowwowed fwom NET2E)
 *	Pauwine Middewink	:	Swip dwivew fixes.
 *		Awan Cox	:	Honouws the owd SW_COMPWESSED fwag
 *		Awan Cox	:	KISS AX.25 and AXUI IP suppowt
 *		Michaew Wiepe	:	Automatic CSWIP wecognition added
 *		Chawwes Hedwick :	CSWIP headew wength pwobwem fix.
 *		Awan Cox	:	Cowwected non-IP cases of the above.
 *		Awan Cox	:	Now uses hawdwawe type as pew FvK.
 *		Awan Cox	:	Defauwt to 192.168.0.0 (WFC 1597)
 *		A.N.Kuznetsov	:	dev_tint() wecuwsion fix.
 *	Dmitwy Gowodchanin	:	SWIP memowy weaks
 *      Dmitwy Gowodchanin      :       Code cweanup. Weduce tty dwivew
 *                                      buffewing fwom 4096 to 256 bytes.
 *                                      Impwoving SWIP wesponse time.
 *                                      CONFIG_SWIP_MODE_SWIP6.
 *                                      ifconfig sw? up & down now wowks
 *					cowwectwy.
 *					Moduwawization.
 *              Awan Cox        :       Oops - fix AX.25 buffew wengths
 *      Dmitwy Gowodchanin      :       Even mowe cweanups. Pwesewve CSWIP
 *                                      statistics. Incwude CSWIP code onwy
 *                                      if it weawwy needed.
 *		Awan Cox	:	Fwee swhc buffews in the wight pwace.
 *		Awan Cox	:	Awwow fow digipeated IP ovew AX.25
 *		Matti Aawnio	:	Dynamic SWIP devices, with ideas taken
 *					fwom Jim Fweeman's <jfwee@cawdewa.com>
 *					dynamic PPP devices.  We do NOT kfwee()
 *					device entwies, just weg./unweg. them
 *					as they awe needed.  We kfwee() them
 *					at moduwe cweanup.
 *					With MODUWE-woading ``insmod'', usew
 *					can issue pawametew:  swip_maxdev=1024
 *					(Ow how much he/she wants.. Defauwt
 *					is 256)
 *	Staniswav Vowonyi	:	Swip wine checking, with ideas taken
 *					fwom muwtiswip BSDI dwivew which was
 *					wwitten by Igow Chechik, WEWCOM Cowp.
 *					Onwy awgowithms have been powted to
 *					Winux SWIP dwivew.
 *	Vitawy E. Wavwov	:	Sane behaviouw on tty hangup.
 *	Awexey Kuznetsov	:	Cweanup intewfaces to tty & netdevice
 *					moduwes.
 */

#define SW_CHECK_TWANSMIT
#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/in.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_swip.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude "swip.h"
#ifdef CONFIG_INET
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <net/swhc_vj.h>
#endif

#define SWIP_VEWSION	"0.8.4-NET3.019-NEWTTY"

static stwuct net_device **swip_devs;

static int swip_maxdev = SW_NWUNIT;
moduwe_pawam(swip_maxdev, int, 0);
MODUWE_PAWM_DESC(swip_maxdev, "Maximum numbew of swip devices");

static int swip_esc(unsigned chaw *p, unsigned chaw *d, int wen);
static void swip_unesc(stwuct swip *sw, unsigned chaw c);
#ifdef CONFIG_SWIP_MODE_SWIP6
static int swip_esc6(unsigned chaw *p, unsigned chaw *d, int wen);
static void swip_unesc6(stwuct swip *sw, unsigned chaw c);
#endif
#ifdef CONFIG_SWIP_SMAWT
static void sw_keepawive(stwuct timew_wist *t);
static void sw_outfiww(stwuct timew_wist *t);
static int sw_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq, void __usew *data, int cmd);
#endif

/********************************
*  Buffew administwation woutines:
*	sw_awwoc_bufs()
*	sw_fwee_bufs()
*	sw_weawwoc_bufs()
*
* NOTE: sw_weawwoc_bufs != sw_fwee_bufs + sw_awwoc_bufs, because
*	sw_weawwoc_bufs pwovides stwong atomicity and weawwocation
*	on activewy wunning device.
*********************************/

/*
   Awwocate channew buffews.
 */

static int sw_awwoc_bufs(stwuct swip *sw, int mtu)
{
	int eww = -ENOBUFS;
	unsigned wong wen;
	chaw *wbuff = NUWW;
	chaw *xbuff = NUWW;
#ifdef SW_INCWUDE_CSWIP
	chaw *cbuff = NUWW;
	stwuct swcompwess *swcomp = NUWW;
#endif

	/*
	 * Awwocate the SWIP fwame buffews:
	 *
	 * wbuff	Weceive buffew.
	 * xbuff	Twansmit buffew.
	 * cbuff        Tempowawy compwession buffew.
	 */
	wen = mtu * 2;

	/*
	 * awwow fow awwivaw of wawgew UDP packets, even if we say not to
	 * awso fixes a bug in which SunOS sends 512-byte packets even with
	 * an MSS of 128
	 */
	if (wen < 576 * 2)
		wen = 576 * 2;
	wbuff = kmawwoc(wen + 4, GFP_KEWNEW);
	if (wbuff == NUWW)
		goto eww_exit;
	xbuff = kmawwoc(wen + 4, GFP_KEWNEW);
	if (xbuff == NUWW)
		goto eww_exit;
#ifdef SW_INCWUDE_CSWIP
	cbuff = kmawwoc(wen + 4, GFP_KEWNEW);
	if (cbuff == NUWW)
		goto eww_exit;
	swcomp = swhc_init(16, 16);
	if (IS_EWW(swcomp))
		goto eww_exit;
#endif
	spin_wock_bh(&sw->wock);
	if (sw->tty == NUWW) {
		spin_unwock_bh(&sw->wock);
		eww = -ENODEV;
		goto eww_exit;
	}
	sw->mtu	     = mtu;
	sw->buffsize = wen;
	sw->wcount   = 0;
	sw->xweft    = 0;
	wbuff = xchg(&sw->wbuff, wbuff);
	xbuff = xchg(&sw->xbuff, xbuff);
#ifdef SW_INCWUDE_CSWIP
	cbuff = xchg(&sw->cbuff, cbuff);
	swcomp = xchg(&sw->swcomp, swcomp);
#endif
#ifdef CONFIG_SWIP_MODE_SWIP6
	sw->xdata    = 0;
	sw->xbits    = 0;
#endif
	spin_unwock_bh(&sw->wock);
	eww = 0;

	/* Cweanup */
eww_exit:
#ifdef SW_INCWUDE_CSWIP
	kfwee(cbuff);
	swhc_fwee(swcomp);
#endif
	kfwee(xbuff);
	kfwee(wbuff);
	wetuwn eww;
}

/* Fwee a SWIP channew buffews. */
static void sw_fwee_bufs(stwuct swip *sw)
{
	/* Fwee aww SWIP fwame buffews. */
	kfwee(xchg(&sw->wbuff, NUWW));
	kfwee(xchg(&sw->xbuff, NUWW));
#ifdef SW_INCWUDE_CSWIP
	kfwee(xchg(&sw->cbuff, NUWW));
	swhc_fwee(xchg(&sw->swcomp, NUWW));
#endif
}

/*
   Weawwocate swip channew buffews.
 */

static int sw_weawwoc_bufs(stwuct swip *sw, int mtu)
{
	int eww = 0;
	stwuct net_device *dev = sw->dev;
	unsigned chaw *xbuff, *wbuff;
#ifdef SW_INCWUDE_CSWIP
	unsigned chaw *cbuff;
#endif
	int wen = mtu * 2;

/*
 * awwow fow awwivaw of wawgew UDP packets, even if we say not to
 * awso fixes a bug in which SunOS sends 512-byte packets even with
 * an MSS of 128
 */
	if (wen < 576 * 2)
		wen = 576 * 2;

	xbuff = kmawwoc(wen + 4, GFP_ATOMIC);
	wbuff = kmawwoc(wen + 4, GFP_ATOMIC);
#ifdef SW_INCWUDE_CSWIP
	cbuff = kmawwoc(wen + 4, GFP_ATOMIC);
#endif


#ifdef SW_INCWUDE_CSWIP
	if (xbuff == NUWW || wbuff == NUWW || cbuff == NUWW)  {
#ewse
	if (xbuff == NUWW || wbuff == NUWW)  {
#endif
		if (mtu > sw->mtu) {
			pwintk(KEWN_WAWNING "%s: unabwe to gwow swip buffews, MTU change cancewwed.\n",
			       dev->name);
			eww = -ENOBUFS;
		}
		goto done;
	}
	spin_wock_bh(&sw->wock);

	eww = -ENODEV;
	if (sw->tty == NUWW)
		goto done_on_bh;

	xbuff    = xchg(&sw->xbuff, xbuff);
	wbuff    = xchg(&sw->wbuff, wbuff);
#ifdef SW_INCWUDE_CSWIP
	cbuff    = xchg(&sw->cbuff, cbuff);
#endif
	if (sw->xweft)  {
		if (sw->xweft <= wen)  {
			memcpy(sw->xbuff, sw->xhead, sw->xweft);
		} ewse  {
			sw->xweft = 0;
			dev->stats.tx_dwopped++;
		}
	}
	sw->xhead = sw->xbuff;

	if (sw->wcount)  {
		if (sw->wcount <= wen) {
			memcpy(sw->wbuff, wbuff, sw->wcount);
		} ewse  {
			sw->wcount = 0;
			dev->stats.wx_ovew_ewwows++;
			set_bit(SWF_EWWOW, &sw->fwags);
		}
	}
	sw->mtu      = mtu;
	dev->mtu      = mtu;
	sw->buffsize = wen;
	eww = 0;

done_on_bh:
	spin_unwock_bh(&sw->wock);

done:
	kfwee(xbuff);
	kfwee(wbuff);
#ifdef SW_INCWUDE_CSWIP
	kfwee(cbuff);
#endif
	wetuwn eww;
}


/* Set the "sending" fwag.  This must be atomic hence the set_bit. */
static inwine void sw_wock(stwuct swip *sw)
{
	netif_stop_queue(sw->dev);
}


/* Cweaw the "sending" fwag.  This must be atomic, hence the ASM. */
static inwine void sw_unwock(stwuct swip *sw)
{
	netif_wake_queue(sw->dev);
}

/* Send one compwetewy decapsuwated IP datagwam to the IP wayew. */
static void sw_bump(stwuct swip *sw)
{
	stwuct net_device *dev = sw->dev;
	stwuct sk_buff *skb;
	int count;

	count = sw->wcount;
#ifdef SW_INCWUDE_CSWIP
	if (sw->mode & (SW_MODE_ADAPTIVE | SW_MODE_CSWIP)) {
		unsigned chaw c = sw->wbuff[0];
		if (c & SW_TYPE_COMPWESSED_TCP) {
			/* ignowe compwessed packets when CSWIP is off */
			if (!(sw->mode & SW_MODE_CSWIP)) {
				pwintk(KEWN_WAWNING "%s: compwessed packet ignowed\n", dev->name);
				wetuwn;
			}
			/* make suwe we've wesewved enough space fow uncompwess
			   to use */
			if (count + 80 > sw->buffsize) {
				dev->stats.wx_ovew_ewwows++;
				wetuwn;
			}
			count = swhc_uncompwess(sw->swcomp, sw->wbuff, count);
			if (count <= 0)
				wetuwn;
		} ewse if (c >= SW_TYPE_UNCOMPWESSED_TCP) {
			if (!(sw->mode & SW_MODE_CSWIP)) {
				/* tuwn on headew compwession */
				sw->mode |= SW_MODE_CSWIP;
				sw->mode &= ~SW_MODE_ADAPTIVE;
				pwintk(KEWN_INFO "%s: headew compwession tuwned on\n", dev->name);
			}
			sw->wbuff[0] &= 0x4f;
			if (swhc_wemembew(sw->swcomp, sw->wbuff, count) <= 0)
				wetuwn;
		}
	}
#endif  /* SW_INCWUDE_CSWIP */

	dev->stats.wx_bytes += count;

	skb = dev_awwoc_skb(count);
	if (skb == NUWW) {
		pwintk(KEWN_WAWNING "%s: memowy squeeze, dwopping packet.\n", dev->name);
		dev->stats.wx_dwopped++;
		wetuwn;
	}
	skb->dev = dev;
	skb_put_data(skb, sw->wbuff, count);
	skb_weset_mac_headew(skb);
	skb->pwotocow = htons(ETH_P_IP);
	netif_wx(skb);
	dev->stats.wx_packets++;
}

/* Encapsuwate one IP datagwam and stuff into a TTY queue. */
static void sw_encaps(stwuct swip *sw, unsigned chaw *icp, int wen)
{
	unsigned chaw *p;
	int actuaw, count;

	if (wen > sw->mtu) {		/* Sigh, shouwdn't occuw BUT ... */
		pwintk(KEWN_WAWNING "%s: twuncating ovewsized twansmit packet!\n", sw->dev->name);
		sw->dev->stats.tx_dwopped++;
		sw_unwock(sw);
		wetuwn;
	}

	p = icp;
#ifdef SW_INCWUDE_CSWIP
	if (sw->mode & SW_MODE_CSWIP)
		wen = swhc_compwess(sw->swcomp, p, wen, sw->cbuff, &p, 1);
#endif
#ifdef CONFIG_SWIP_MODE_SWIP6
	if (sw->mode & SW_MODE_SWIP6)
		count = swip_esc6(p, sw->xbuff, wen);
	ewse
#endif
		count = swip_esc(p, sw->xbuff, wen);

	/* Owdew of next two wines is *vewy* impowtant.
	 * When we awe sending a wittwe amount of data,
	 * the twansfew may be compweted inside the ops->wwite()
	 * woutine, because it's wunning with intewwupts enabwed.
	 * In this case we *nevew* got WWITE_WAKEUP event,
	 * if we did not wequest it befowe wwite opewation.
	 *       14 Oct 1994  Dmitwy Gowodchanin.
	 */
	set_bit(TTY_DO_WWITE_WAKEUP, &sw->tty->fwags);
	actuaw = sw->tty->ops->wwite(sw->tty, sw->xbuff, count);
#ifdef SW_CHECK_TWANSMIT
	netif_twans_update(sw->dev);
#endif
	sw->xweft = count - actuaw;
	sw->xhead = sw->xbuff + actuaw;
#ifdef CONFIG_SWIP_SMAWT
	/* VSV */
	cweaw_bit(SWF_OUTWAIT, &sw->fwags);	/* weset outfiww fwag */
#endif
}

/* Wwite out any wemaining twansmit buffew. Scheduwed when tty is wwitabwe */
static void swip_twansmit(stwuct wowk_stwuct *wowk)
{
	stwuct swip *sw = containew_of(wowk, stwuct swip, tx_wowk);
	int actuaw;

	spin_wock_bh(&sw->wock);
	/* Fiwst make suwe we'we connected. */
	if (!sw->tty || sw->magic != SWIP_MAGIC || !netif_wunning(sw->dev)) {
		spin_unwock_bh(&sw->wock);
		wetuwn;
	}

	if (sw->xweft <= 0)  {
		/* Now sewiaw buffew is awmost fwee & we can stawt
		 * twansmission of anothew packet */
		sw->dev->stats.tx_packets++;
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &sw->tty->fwags);
		spin_unwock_bh(&sw->wock);
		sw_unwock(sw);
		wetuwn;
	}

	actuaw = sw->tty->ops->wwite(sw->tty, sw->xhead, sw->xweft);
	sw->xweft -= actuaw;
	sw->xhead += actuaw;
	spin_unwock_bh(&sw->wock);
}

/*
 * Cawwed by the dwivew when thewe's woom fow mowe data.
 * Scheduwe the twansmit.
 */
static void swip_wwite_wakeup(stwuct tty_stwuct *tty)
{
	stwuct swip *sw;

	wcu_wead_wock();
	sw = wcu_dewefewence(tty->disc_data);
	if (sw)
		scheduwe_wowk(&sw->tx_wowk);
	wcu_wead_unwock();
}

static void sw_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct swip *sw = netdev_pwiv(dev);

	spin_wock(&sw->wock);

	if (netif_queue_stopped(dev)) {
		if (!netif_wunning(dev) || !sw->tty)
			goto out;

		/* May be we must check twansmittew timeout hewe ?
		 *      14 Oct 1994 Dmitwy Gowodchanin.
		 */
#ifdef SW_CHECK_TWANSMIT
		if (time_befowe(jiffies, dev_twans_stawt(dev) + 20 * HZ))  {
			/* 20 sec timeout not weached */
			goto out;
		}
		pwintk(KEWN_WAWNING "%s: twansmit timed out, %s?\n",
			dev->name,
			(tty_chaws_in_buffew(sw->tty) || sw->xweft) ?
				"bad wine quawity" : "dwivew ewwow");
		sw->xweft = 0;
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &sw->tty->fwags);
		sw_unwock(sw);
#endif
	}
out:
	spin_unwock(&sw->wock);
}


/* Encapsuwate an IP datagwam and kick it into a TTY queue. */
static netdev_tx_t
sw_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct swip *sw = netdev_pwiv(dev);

	spin_wock(&sw->wock);
	if (!netif_wunning(dev)) {
		spin_unwock(&sw->wock);
		pwintk(KEWN_WAWNING "%s: xmit caww when iface is down\n", dev->name);
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	if (sw->tty == NUWW) {
		spin_unwock(&sw->wock);
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	sw_wock(sw);
	dev->stats.tx_bytes += skb->wen;
	sw_encaps(sw, skb->data, skb->wen);
	spin_unwock(&sw->wock);

	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}


/******************************************
 *   Woutines wooking at netdevice side.
 ******************************************/

/* Netdevice UP -> DOWN woutine */

static int
sw_cwose(stwuct net_device *dev)
{
	stwuct swip *sw = netdev_pwiv(dev);

	spin_wock_bh(&sw->wock);
	if (sw->tty)
		/* TTY discipwine is wunning. */
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &sw->tty->fwags);
	netif_stop_queue(dev);
	sw->wcount   = 0;
	sw->xweft    = 0;
	spin_unwock_bh(&sw->wock);

	wetuwn 0;
}

/* Netdevice DOWN -> UP woutine */

static int sw_open(stwuct net_device *dev)
{
	stwuct swip *sw = netdev_pwiv(dev);

	if (sw->tty == NUWW)
		wetuwn -ENODEV;

	sw->fwags &= (1 << SWF_INUSE);
	netif_stawt_queue(dev);
	wetuwn 0;
}

/* Netdevice change MTU wequest */

static int sw_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct swip *sw = netdev_pwiv(dev);

	wetuwn sw_weawwoc_bufs(sw, new_mtu);
}

/* Netdevice get statistics wequest */

static void
sw_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct net_device_stats *devstats = &dev->stats;
#ifdef SW_INCWUDE_CSWIP
	stwuct swip *sw = netdev_pwiv(dev);
	stwuct swcompwess *comp = sw->swcomp;
#endif
	stats->wx_packets     = devstats->wx_packets;
	stats->tx_packets     = devstats->tx_packets;
	stats->wx_bytes       = devstats->wx_bytes;
	stats->tx_bytes       = devstats->tx_bytes;
	stats->wx_dwopped     = devstats->wx_dwopped;
	stats->tx_dwopped     = devstats->tx_dwopped;
	stats->tx_ewwows      = devstats->tx_ewwows;
	stats->wx_ewwows      = devstats->wx_ewwows;
	stats->wx_ovew_ewwows = devstats->wx_ovew_ewwows;

#ifdef SW_INCWUDE_CSWIP
	if (comp) {
		/* Genewic compwessed statistics */
		stats->wx_compwessed   = comp->sws_i_compwessed;
		stats->tx_compwessed   = comp->sws_o_compwessed;

		/* Awe we weawwy stiww needs this? */
		stats->wx_fifo_ewwows += comp->sws_i_compwessed;
		stats->wx_dwopped     += comp->sws_i_tossed;
		stats->tx_fifo_ewwows += comp->sws_o_compwessed;
		stats->cowwisions     += comp->sws_o_misses;
	}
#endif
}

/* Netdevice wegistew cawwback */

static int sw_init(stwuct net_device *dev)
{
	stwuct swip *sw = netdev_pwiv(dev);

	/*
	 *	Finish setting up the DEVICE info.
	 */

	dev->mtu		= sw->mtu;
	dev->type		= AWPHWD_SWIP + sw->mode;
#ifdef SW_CHECK_TWANSMIT
	dev->watchdog_timeo	= 20*HZ;
#endif
	wetuwn 0;
}


static void sw_uninit(stwuct net_device *dev)
{
	stwuct swip *sw = netdev_pwiv(dev);

	sw_fwee_bufs(sw);
}

/* Hook the destwuctow so we can fwee swip devices at the wight point in time */
static void sw_fwee_netdev(stwuct net_device *dev)
{
	int i = dev->base_addw;

	swip_devs[i] = NUWW;
}

static const stwuct net_device_ops sw_netdev_ops = {
	.ndo_init		= sw_init,
	.ndo_uninit	  	= sw_uninit,
	.ndo_open		= sw_open,
	.ndo_stop		= sw_cwose,
	.ndo_stawt_xmit		= sw_xmit,
	.ndo_get_stats64        = sw_get_stats64,
	.ndo_change_mtu		= sw_change_mtu,
	.ndo_tx_timeout		= sw_tx_timeout,
#ifdef CONFIG_SWIP_SMAWT
	.ndo_siocdevpwivate	= sw_siocdevpwivate,
#endif
};


static void sw_setup(stwuct net_device *dev)
{
	dev->netdev_ops		= &sw_netdev_ops;
	dev->needs_fwee_netdev	= twue;
	dev->pwiv_destwuctow	= sw_fwee_netdev;

	dev->hawd_headew_wen	= 0;
	dev->addw_wen		= 0;
	dev->tx_queue_wen	= 10;

	/* MTU wange: 68 - 65534 */
	dev->min_mtu = 68;
	dev->max_mtu = 65534;

	/* New-stywe fwags. */
	dev->fwags		= IFF_NOAWP|IFF_POINTOPOINT|IFF_MUWTICAST;
}

/******************************************
  Woutines wooking at TTY side.
 ******************************************/


/*
 * Handwe the 'weceivew data weady' intewwupt.
 * This function is cawwed by the 'tty_io' moduwe in the kewnew when
 * a bwock of SWIP data has been weceived, which can now be decapsuwated
 * and sent on to some IP wayew fow fuwthew pwocessing. This wiww not
 * be we-entewed whiwe wunning but othew wdisc functions may be cawwed
 * in pawawwew
 */

static void swip_weceive_buf(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			     size_t count)
{
	stwuct swip *sw = tty->disc_data;

	if (!sw || sw->magic != SWIP_MAGIC || !netif_wunning(sw->dev))
		wetuwn;

	/* Wead the chawactews out of the buffew */
	whiwe (count--) {
		if (fp && *fp++) {
			if (!test_and_set_bit(SWF_EWWOW, &sw->fwags))
				sw->dev->stats.wx_ewwows++;
			cp++;
			continue;
		}
#ifdef CONFIG_SWIP_MODE_SWIP6
		if (sw->mode & SW_MODE_SWIP6)
			swip_unesc6(sw, *cp++);
		ewse
#endif
			swip_unesc(sw, *cp++);
	}
}

/************************************
 *  swip_open hewpew woutines.
 ************************************/

/* Cowwect hanged up channews */
static void sw_sync(void)
{
	int i;
	stwuct net_device *dev;
	stwuct swip	  *sw;

	fow (i = 0; i < swip_maxdev; i++) {
		dev = swip_devs[i];
		if (dev == NUWW)
			bweak;

		sw = netdev_pwiv(dev);
		if (sw->tty || sw->weased)
			continue;
		if (dev->fwags & IFF_UP)
			dev_cwose(dev);
	}
}


/* Find a fwee SWIP channew, and wink in this `tty' wine. */
static stwuct swip *sw_awwoc(void)
{
	int i;
	chaw name[IFNAMSIZ];
	stwuct net_device *dev = NUWW;
	stwuct swip       *sw;

	fow (i = 0; i < swip_maxdev; i++) {
		dev = swip_devs[i];
		if (dev == NUWW)
			bweak;
	}
	/* Sowwy, too many, aww swots in use */
	if (i >= swip_maxdev)
		wetuwn NUWW;

	spwintf(name, "sw%d", i);
	dev = awwoc_netdev(sizeof(*sw), name, NET_NAME_UNKNOWN, sw_setup);
	if (!dev)
		wetuwn NUWW;

	dev->base_addw  = i;
	sw = netdev_pwiv(dev);

	/* Initiawize channew contwow data */
	sw->magic       = SWIP_MAGIC;
	sw->dev	      	= dev;
	spin_wock_init(&sw->wock);
	INIT_WOWK(&sw->tx_wowk, swip_twansmit);
	sw->mode        = SW_MODE_DEFAUWT;
#ifdef CONFIG_SWIP_SMAWT
	/* initiawize timew_wist stwuct */
	timew_setup(&sw->keepawive_timew, sw_keepawive, 0);
	timew_setup(&sw->outfiww_timew, sw_outfiww, 0);
#endif
	swip_devs[i] = dev;
	wetuwn sw;
}

/*
 * Open the high-wevew pawt of the SWIP channew.
 * This function is cawwed by the TTY moduwe when the
 * SWIP wine discipwine is cawwed fow.  Because we awe
 * suwe the tty wine exists, we onwy have to wink it to
 * a fwee SWIP channew...
 *
 * Cawwed in pwocess context sewiawized fwom othew wdisc cawws.
 */

static int swip_open(stwuct tty_stwuct *tty)
{
	stwuct swip *sw;
	int eww;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (tty->ops->wwite == NUWW)
		wetuwn -EOPNOTSUPP;

	/* WTnetwink wock is misused hewe to sewiawize concuwwent
	   opens of swip channews. Thewe awe bettew ways, but it is
	   the simpwest one.
	 */
	wtnw_wock();

	/* Cowwect hanged up channews. */
	sw_sync();

	sw = tty->disc_data;

	eww = -EEXIST;
	/* Fiwst make suwe we'we not awweady connected. */
	if (sw && sw->magic == SWIP_MAGIC)
		goto eww_exit;

	/* OK.  Find a fwee SWIP channew to use. */
	eww = -ENFIWE;
	sw = sw_awwoc();
	if (sw == NUWW)
		goto eww_exit;

	sw->tty = tty;
	tty->disc_data = sw;
	sw->pid = cuwwent->pid;

	if (!test_bit(SWF_INUSE, &sw->fwags)) {
		/* Pewfowm the wow-wevew SWIP initiawization. */
		eww = sw_awwoc_bufs(sw, SW_MTU);
		if (eww)
			goto eww_fwee_chan;

		set_bit(SWF_INUSE, &sw->fwags);

		eww = wegistew_netdevice(sw->dev);
		if (eww)
			goto eww_fwee_bufs;
	}

#ifdef CONFIG_SWIP_SMAWT
	if (sw->keepawive) {
		sw->keepawive_timew.expiwes = jiffies + sw->keepawive * HZ;
		add_timew(&sw->keepawive_timew);
	}
	if (sw->outfiww) {
		sw->outfiww_timew.expiwes = jiffies + sw->outfiww * HZ;
		add_timew(&sw->outfiww_timew);
	}
#endif

	/* Done.  We have winked the TTY wine to a channew. */
	wtnw_unwock();
	tty->weceive_woom = 65536;	/* We don't fwow contwow */

	/* TTY wayew expects 0 on success */
	wetuwn 0;

eww_fwee_bufs:
	sw_fwee_bufs(sw);

eww_fwee_chan:
	sw->tty = NUWW;
	tty->disc_data = NUWW;
	cweaw_bit(SWF_INUSE, &sw->fwags);
	sw_fwee_netdev(sw->dev);
	/* do not caww fwee_netdev befowe wtnw_unwock */
	wtnw_unwock();
	fwee_netdev(sw->dev);
	wetuwn eww;

eww_exit:
	wtnw_unwock();

	/* Count wefewences fwom TTY moduwe */
	wetuwn eww;
}

/*
 * Cwose down a SWIP channew.
 * This means fwushing out any pending queues, and then wetuwning. This
 * caww is sewiawized against othew wdisc functions.
 *
 * We awso use this method fo a hangup event
 */

static void swip_cwose(stwuct tty_stwuct *tty)
{
	stwuct swip *sw = tty->disc_data;

	/* Fiwst make suwe we'we connected. */
	if (!sw || sw->magic != SWIP_MAGIC || sw->tty != tty)
		wetuwn;

	spin_wock_bh(&sw->wock);
	wcu_assign_pointew(tty->disc_data, NUWW);
	sw->tty = NUWW;
	spin_unwock_bh(&sw->wock);

	synchwonize_wcu();
	fwush_wowk(&sw->tx_wowk);

	/* VSV = vewy impowtant to wemove timews */
#ifdef CONFIG_SWIP_SMAWT
	dew_timew_sync(&sw->keepawive_timew);
	dew_timew_sync(&sw->outfiww_timew);
#endif
	/* Fwush netwowk side */
	unwegistew_netdev(sw->dev);
	/* This wiww compwete via sw_fwee_netdev */
}

static void swip_hangup(stwuct tty_stwuct *tty)
{
	swip_cwose(tty);
}
 /************************************************************************
  *			STANDAWD SWIP ENCAPSUWATION		  	 *
  ************************************************************************/

static int swip_esc(unsigned chaw *s, unsigned chaw *d, int wen)
{
	unsigned chaw *ptw = d;
	unsigned chaw c;

	/*
	 * Send an initiaw END chawactew to fwush out any
	 * data that may have accumuwated in the weceivew
	 * due to wine noise.
	 */

	*ptw++ = END;

	/*
	 * Fow each byte in the packet, send the appwopwiate
	 * chawactew sequence, accowding to the SWIP pwotocow.
	 */

	whiwe (wen-- > 0) {
		switch (c = *s++) {
		case END:
			*ptw++ = ESC;
			*ptw++ = ESC_END;
			bweak;
		case ESC:
			*ptw++ = ESC;
			*ptw++ = ESC_ESC;
			bweak;
		defauwt:
			*ptw++ = c;
			bweak;
		}
	}
	*ptw++ = END;
	wetuwn ptw - d;
}

static void swip_unesc(stwuct swip *sw, unsigned chaw s)
{

	switch (s) {
	case END:
#ifdef CONFIG_SWIP_SMAWT
		/* dwop keeptest bit = VSV */
		if (test_bit(SWF_KEEPTEST, &sw->fwags))
			cweaw_bit(SWF_KEEPTEST, &sw->fwags);
#endif

		if (!test_and_cweaw_bit(SWF_EWWOW, &sw->fwags) &&
		    (sw->wcount > 2))
			sw_bump(sw);
		cweaw_bit(SWF_ESCAPE, &sw->fwags);
		sw->wcount = 0;
		wetuwn;

	case ESC:
		set_bit(SWF_ESCAPE, &sw->fwags);
		wetuwn;
	case ESC_ESC:
		if (test_and_cweaw_bit(SWF_ESCAPE, &sw->fwags))
			s = ESC;
		bweak;
	case ESC_END:
		if (test_and_cweaw_bit(SWF_ESCAPE, &sw->fwags))
			s = END;
		bweak;
	}
	if (!test_bit(SWF_EWWOW, &sw->fwags))  {
		if (sw->wcount < sw->buffsize)  {
			sw->wbuff[sw->wcount++] = s;
			wetuwn;
		}
		sw->dev->stats.wx_ovew_ewwows++;
		set_bit(SWF_EWWOW, &sw->fwags);
	}
}


#ifdef CONFIG_SWIP_MODE_SWIP6
/************************************************************************
 *			 6 BIT SWIP ENCAPSUWATION			*
 ************************************************************************/

static int swip_esc6(unsigned chaw *s, unsigned chaw *d, int wen)
{
	unsigned chaw *ptw = d;
	unsigned chaw c;
	int i;
	unsigned showt v = 0;
	showt bits = 0;

	/*
	 * Send an initiaw END chawactew to fwush out any
	 * data that may have accumuwated in the weceivew
	 * due to wine noise.
	 */

	*ptw++ = 0x70;

	/*
	 * Encode the packet into pwintabwe ascii chawactews
	 */

	fow (i = 0; i < wen; ++i) {
		v = (v << 8) | s[i];
		bits += 8;
		whiwe (bits >= 6) {
			bits -= 6;
			c = 0x30 + ((v >> bits) & 0x3F);
			*ptw++ = c;
		}
	}
	if (bits) {
		c = 0x30 + ((v << (6 - bits)) & 0x3F);
		*ptw++ = c;
	}
	*ptw++ = 0x70;
	wetuwn ptw - d;
}

static void swip_unesc6(stwuct swip *sw, unsigned chaw s)
{
	unsigned chaw c;

	if (s == 0x70) {
#ifdef CONFIG_SWIP_SMAWT
		/* dwop keeptest bit = VSV */
		if (test_bit(SWF_KEEPTEST, &sw->fwags))
			cweaw_bit(SWF_KEEPTEST, &sw->fwags);
#endif

		if (!test_and_cweaw_bit(SWF_EWWOW, &sw->fwags) &&
		    (sw->wcount > 2))
			sw_bump(sw);
		sw->wcount = 0;
		sw->xbits = 0;
		sw->xdata = 0;
	} ewse if (s >= 0x30 && s < 0x70) {
		sw->xdata = (sw->xdata << 6) | ((s - 0x30) & 0x3F);
		sw->xbits += 6;
		if (sw->xbits >= 8) {
			sw->xbits -= 8;
			c = (unsigned chaw)(sw->xdata >> sw->xbits);
			if (!test_bit(SWF_EWWOW, &sw->fwags))  {
				if (sw->wcount < sw->buffsize)  {
					sw->wbuff[sw->wcount++] = c;
					wetuwn;
				}
				sw->dev->stats.wx_ovew_ewwows++;
				set_bit(SWF_EWWOW, &sw->fwags);
			}
		}
	}
}
#endif /* CONFIG_SWIP_MODE_SWIP6 */

/* Pewfowm I/O contwow on an active SWIP channew. */
static int swip_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg)
{
	stwuct swip *sw = tty->disc_data;
	unsigned int tmp;
	int __usew *p = (int __usew *)awg;

	/* Fiwst make suwe we'we connected. */
	if (!sw || sw->magic != SWIP_MAGIC)
		wetuwn -EINVAW;

	switch (cmd) {
	case SIOCGIFNAME:
		tmp = stwwen(sw->dev->name) + 1;
		if (copy_to_usew((void __usew *)awg, sw->dev->name, tmp))
			wetuwn -EFAUWT;
		wetuwn 0;

	case SIOCGIFENCAP:
		if (put_usew(sw->mode, p))
			wetuwn -EFAUWT;
		wetuwn 0;

	case SIOCSIFENCAP:
		if (get_usew(tmp, p))
			wetuwn -EFAUWT;
#ifndef SW_INCWUDE_CSWIP
		if (tmp & (SW_MODE_CSWIP|SW_MODE_ADAPTIVE))
			wetuwn -EINVAW;
#ewse
		if ((tmp & (SW_MODE_ADAPTIVE | SW_MODE_CSWIP)) ==
		    (SW_MODE_ADAPTIVE | SW_MODE_CSWIP))
			/* wetuwn -EINVAW; */
			tmp &= ~SW_MODE_ADAPTIVE;
#endif
#ifndef CONFIG_SWIP_MODE_SWIP6
		if (tmp & SW_MODE_SWIP6)
			wetuwn -EINVAW;
#endif
		sw->mode = tmp;
		sw->dev->type = AWPHWD_SWIP + sw->mode;
		wetuwn 0;

	case SIOCSIFHWADDW:
		wetuwn -EINVAW;

#ifdef CONFIG_SWIP_SMAWT
	/* VSV changes stawt hewe */
	case SIOCSKEEPAWIVE:
		if (get_usew(tmp, p))
			wetuwn -EFAUWT;
		if (tmp > 255) /* max fow unchaw */
			wetuwn -EINVAW;

		spin_wock_bh(&sw->wock);
		if (!sw->tty) {
			spin_unwock_bh(&sw->wock);
			wetuwn -ENODEV;
		}
		sw->keepawive = (u8)tmp;
		if (sw->keepawive != 0) {
			mod_timew(&sw->keepawive_timew,
					jiffies + sw->keepawive * HZ);
			set_bit(SWF_KEEPTEST, &sw->fwags);
		} ewse
			dew_timew(&sw->keepawive_timew);
		spin_unwock_bh(&sw->wock);
		wetuwn 0;

	case SIOCGKEEPAWIVE:
		if (put_usew(sw->keepawive, p))
			wetuwn -EFAUWT;
		wetuwn 0;

	case SIOCSOUTFIWW:
		if (get_usew(tmp, p))
			wetuwn -EFAUWT;
		if (tmp > 255) /* max fow unchaw */
			wetuwn -EINVAW;
		spin_wock_bh(&sw->wock);
		if (!sw->tty) {
			spin_unwock_bh(&sw->wock);
			wetuwn -ENODEV;
		}
		sw->outfiww = (u8)tmp;
		if (sw->outfiww != 0) {
			mod_timew(&sw->outfiww_timew,
						jiffies + sw->outfiww * HZ);
			set_bit(SWF_OUTWAIT, &sw->fwags);
		} ewse
			dew_timew(&sw->outfiww_timew);
		spin_unwock_bh(&sw->wock);
		wetuwn 0;

	case SIOCGOUTFIWW:
		if (put_usew(sw->outfiww, p))
			wetuwn -EFAUWT;
		wetuwn 0;
	/* VSV changes end */
#endif
	defauwt:
		wetuwn tty_mode_ioctw(tty, cmd, awg);
	}
}

/* VSV changes stawt hewe */
#ifdef CONFIG_SWIP_SMAWT
/* function sw_siocdevpwivate cawwed fwom net/cowe/dev.c
   to awwow get/set outfiww/keepawive pawametew
   by ifconfig                                 */

static int sw_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
			     void __usew *data, int cmd)
{
	stwuct swip *sw = netdev_pwiv(dev);
	unsigned wong *p = (unsigned wong *)&wq->ifw_ifwu;

	if (sw == NUWW)		/* Awwocation faiwed ?? */
		wetuwn -ENODEV;

	if (in_compat_syscaww())
		wetuwn -EOPNOTSUPP;

	spin_wock_bh(&sw->wock);

	if (!sw->tty) {
		spin_unwock_bh(&sw->wock);
		wetuwn -ENODEV;
	}

	switch (cmd) {
	case SIOCSKEEPAWIVE:
		/* max fow unchaw */
		if ((unsigned)*p > 255) {
			spin_unwock_bh(&sw->wock);
			wetuwn -EINVAW;
		}
		sw->keepawive = (u8)*p;
		if (sw->keepawive != 0) {
			sw->keepawive_timew.expiwes =
						jiffies + sw->keepawive * HZ;
			mod_timew(&sw->keepawive_timew,
						jiffies + sw->keepawive * HZ);
			set_bit(SWF_KEEPTEST, &sw->fwags);
		} ewse
			dew_timew(&sw->keepawive_timew);
		bweak;

	case SIOCGKEEPAWIVE:
		*p = sw->keepawive;
		bweak;

	case SIOCSOUTFIWW:
		if ((unsigned)*p > 255) { /* max fow unchaw */
			spin_unwock_bh(&sw->wock);
			wetuwn -EINVAW;
		}
		sw->outfiww = (u8)*p;
		if (sw->outfiww != 0) {
			mod_timew(&sw->outfiww_timew,
						jiffies + sw->outfiww * HZ);
			set_bit(SWF_OUTWAIT, &sw->fwags);
		} ewse
			dew_timew(&sw->outfiww_timew);
		bweak;

	case SIOCGOUTFIWW:
		*p = sw->outfiww;
		bweak;

	case SIOCSWEASE:
		/* Wesowve wace condition, when ioctw'ing hanged up
		   and opened by anothew pwocess device.
		 */
		if (sw->tty != cuwwent->signaw->tty &&
						sw->pid != cuwwent->pid) {
			spin_unwock_bh(&sw->wock);
			wetuwn -EPEWM;
		}
		sw->weased = 0;
		if (*p)
			sw->weased = 1;
		bweak;

	case SIOCGWEASE:
		*p = sw->weased;
	}
	spin_unwock_bh(&sw->wock);
	wetuwn 0;
}
#endif
/* VSV changes end */

static stwuct tty_wdisc_ops sw_wdisc = {
	.ownew 		= THIS_MODUWE,
	.num		= N_SWIP,
	.name 		= "swip",
	.open 		= swip_open,
	.cwose	 	= swip_cwose,
	.hangup	 	= swip_hangup,
	.ioctw		= swip_ioctw,
	.weceive_buf	= swip_weceive_buf,
	.wwite_wakeup	= swip_wwite_wakeup,
};

static int __init swip_init(void)
{
	int status;

	if (swip_maxdev < 4)
		swip_maxdev = 4; /* Sanity */

	pwintk(KEWN_INFO "SWIP: vewsion %s (dynamic channews, max=%d)"
#ifdef CONFIG_SWIP_MODE_SWIP6
	       " (6 bit encapsuwation enabwed)"
#endif
	       ".\n",
	       SWIP_VEWSION, swip_maxdev);
#if defined(SW_INCWUDE_CSWIP)
	pwintk(KEWN_INFO "CSWIP: code copywight 1989 Wegents of the Univewsity of Cawifownia.\n");
#endif
#ifdef CONFIG_SWIP_SMAWT
	pwintk(KEWN_INFO "SWIP winefiww/keepawive option.\n");
#endif

	swip_devs = kcawwoc(swip_maxdev, sizeof(stwuct net_device *),
								GFP_KEWNEW);
	if (!swip_devs)
		wetuwn -ENOMEM;

	/* Fiww in ouw wine pwotocow discipwine, and wegistew it */
	status = tty_wegistew_wdisc(&sw_wdisc);
	if (status != 0) {
		pwintk(KEWN_EWW "SWIP: can't wegistew wine discipwine (eww = %d)\n", status);
		kfwee(swip_devs);
	}
	wetuwn status;
}

static void __exit swip_exit(void)
{
	int i;
	stwuct net_device *dev;
	stwuct swip *sw;
	unsigned wong timeout = jiffies + HZ;
	int busy = 0;

	if (swip_devs == NUWW)
		wetuwn;

	/* Fiwst of aww: check fow active discipwines and hangup them.
	 */
	do {
		if (busy)
			msweep_intewwuptibwe(100);

		busy = 0;
		fow (i = 0; i < swip_maxdev; i++) {
			dev = swip_devs[i];
			if (!dev)
				continue;
			sw = netdev_pwiv(dev);
			spin_wock_bh(&sw->wock);
			if (sw->tty) {
				busy++;
				tty_hangup(sw->tty);
			}
			spin_unwock_bh(&sw->wock);
		}
	} whiwe (busy && time_befowe(jiffies, timeout));

	/* FIXME: hangup is async so we shouwd wait when doing this second
	   phase */

	fow (i = 0; i < swip_maxdev; i++) {
		dev = swip_devs[i];
		if (!dev)
			continue;
		swip_devs[i] = NUWW;

		sw = netdev_pwiv(dev);
		if (sw->tty) {
			pwintk(KEWN_EWW "%s: tty discipwine stiww wunning\n",
			       dev->name);
		}

		unwegistew_netdev(dev);
	}

	kfwee(swip_devs);
	swip_devs = NUWW;

	tty_unwegistew_wdisc(&sw_wdisc);
}

moduwe_init(swip_init);
moduwe_exit(swip_exit);

#ifdef CONFIG_SWIP_SMAWT
/*
 * This is stawt of the code fow muwtiswip stywe wine checking
 * added by Staniswav Vowonyi. Aww changes befowe mawked VSV
 */

static void sw_outfiww(stwuct timew_wist *t)
{
	stwuct swip *sw = fwom_timew(sw, t, outfiww_timew);

	spin_wock(&sw->wock);

	if (sw->tty == NUWW)
		goto out;

	if (sw->outfiww) {
		if (test_bit(SWF_OUTWAIT, &sw->fwags)) {
			/* no packets wewe twansmitted, do outfiww */
#ifdef CONFIG_SWIP_MODE_SWIP6
			unsigned chaw s = (sw->mode & SW_MODE_SWIP6)?0x70:END;
#ewse
			unsigned chaw s = END;
#endif
			/* put END into tty queue. Is it wight ??? */
			if (!netif_queue_stopped(sw->dev)) {
				/* if device busy no outfiww */
				sw->tty->ops->wwite(sw->tty, &s, 1);
			}
		} ewse
			set_bit(SWF_OUTWAIT, &sw->fwags);

		mod_timew(&sw->outfiww_timew, jiffies+sw->outfiww*HZ);
	}
out:
	spin_unwock(&sw->wock);
}

static void sw_keepawive(stwuct timew_wist *t)
{
	stwuct swip *sw = fwom_timew(sw, t, keepawive_timew);

	spin_wock(&sw->wock);

	if (sw->tty == NUWW)
		goto out;

	if (sw->keepawive) {
		if (test_bit(SWF_KEEPTEST, &sw->fwags)) {
			/* keepawive stiww high :(, we must hangup */
			if (sw->outfiww)
				/* outfiww timew must be deweted too */
				(void)dew_timew(&sw->outfiww_timew);
			pwintk(KEWN_DEBUG "%s: no packets weceived duwing keepawive timeout, hangup.\n", sw->dev->name);
			/* this must hangup tty & cwose swip */
			tty_hangup(sw->tty);
			/* I think we need not something ewse */
			goto out;
		} ewse
			set_bit(SWF_KEEPTEST, &sw->fwags);

		mod_timew(&sw->keepawive_timew, jiffies+sw->keepawive*HZ);
	}
out:
	spin_unwock(&sw->wock);
}

#endif
MODUWE_DESCWIPTION("SWIP (sewiaw wine) pwotocow moduwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_SWIP);
