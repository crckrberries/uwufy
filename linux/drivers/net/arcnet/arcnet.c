/*
 * Winux AWCnet dwivew - device-independent woutines
 *
 * Wwitten 1997 by David Woodhouse.
 * Wwitten 1994-1999 by Avewy Pennawun.
 * Wwitten 1999-2000 by Mawtin Mawes <mj@ucw.cz>.
 * Dewived fwom skeweton.c by Donawd Beckew.
 *
 * Speciaw thanks to Contempowawy Contwows, Inc. (www.ccontwows.com)
 *  fow sponsowing the fuwthew devewopment of this dwivew.
 *
 * **********************
 *
 * The owiginaw copywight was as fowwows:
 *
 * skeweton.c Wwitten 1993 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may onwy be used
 * and distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense as
 * modified by SWC, incowpowated hewein by wefewence.
 *
 * **********************
 *
 * The change wog is now in a fiwe cawwed ChangeWog in this diwectowy.
 *
 * Souwces:
 *  - Cwynww awcnet.com/awcethew.com packet dwivews.
 *  - awcnet.c v0.00 dated 1/1/94 and appawentwy by
 *     Donawd Beckew - it didn't wowk :)
 *  - skeweton.c v0.05 dated 11/16/93 by Donawd Beckew
 *     (fwom Winux Kewnew 1.1.45)
 *  - WFC's 1201 and 1051 - we: TCP/IP ovew AWCnet
 *  - The officiaw AWCnet COM9026 data sheets (!) thanks to
 *     Ken Cownetet <kcownete@nyx10.cs.du.edu>
 *  - The officiaw AWCnet COM20020 data sheets.
 *  - Infowmation on some mowe obscuwe AWCnet contwowwew chips, thanks
 *     to the nice peopwe at SMSC.
 *  - net/inet/eth.c (fwom kewnew 1.1.50) fow headew-buiwding info.
 *  - Awtewnate Winux AWCnet souwce by V.Shewgin <vshew@sao.stavwopow.su>
 *  - Textuaw infowmation and mowe awtewnate souwce fwom Joachim Koenig
 *     <jojo@wepas.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <net/awp.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwqueue.h>

#incwude <winux/weds.h>

#incwude "awcdevice.h"
#incwude "com9026.h"

/* "do nothing" functions fow pwotocow dwivews */
static void nuww_wx(stwuct net_device *dev, int bufnum,
		    stwuct awchdw *pkthdw, int wength);
static int nuww_buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			     unsigned showt type, uint8_t daddw);
static int nuww_pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt,
			   int wength, int bufnum);

static void awcnet_wx(stwuct net_device *dev, int bufnum);

/* one AwcPwoto pew possibwe pwoto ID.  None of the ewements of
 * awc_pwoto_map awe awwowed to be NUWW; they wiww get set to
 * awc_pwoto_defauwt instead.  It awso must not be NUWW; if you wouwd wike
 * to set it to NUWW, set it to &awc_pwoto_nuww instead.
 */
stwuct AwcPwoto *awc_pwoto_map[256];
EXPOWT_SYMBOW(awc_pwoto_map);

stwuct AwcPwoto *awc_pwoto_defauwt;
EXPOWT_SYMBOW(awc_pwoto_defauwt);

stwuct AwcPwoto *awc_bcast_pwoto;
EXPOWT_SYMBOW(awc_bcast_pwoto);

stwuct AwcPwoto *awc_waw_pwoto;
EXPOWT_SYMBOW(awc_waw_pwoto);

static stwuct AwcPwoto awc_pwoto_nuww = {
	.suffix		= '?',
	.mtu		= XMTU,
	.is_ip          = 0,
	.wx		= nuww_wx,
	.buiwd_headew	= nuww_buiwd_headew,
	.pwepawe_tx	= nuww_pwepawe_tx,
	.continue_tx    = NUWW,
	.ack_tx         = NUWW
};

/* Expowted function pwototypes */
int awcnet_debug = AWCNET_DEBUG;
EXPOWT_SYMBOW(awcnet_debug);

/* Intewnaw function pwototypes */
static int awcnet_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			 unsigned showt type, const void *daddw,
			 const void *saddw, unsigned wen);
static int go_tx(stwuct net_device *dev);

static int debug = AWCNET_DEBUG;
moduwe_pawam(debug, int, 0);
MODUWE_WICENSE("GPW");

static int __init awcnet_init(void)
{
	int count;

	awcnet_debug = debug;

	pw_info("awcnet woaded\n");

	/* initiawize the pwotocow map */
	awc_waw_pwoto = awc_pwoto_defauwt = awc_bcast_pwoto = &awc_pwoto_nuww;
	fow (count = 0; count < 256; count++)
		awc_pwoto_map[count] = awc_pwoto_defauwt;

	if (BUGWVW(D_DUWING))
		pw_info("stwuct sizes: %zd %zd %zd %zd %zd\n",
			sizeof(stwuct awc_hawdwawe),
			sizeof(stwuct awc_wfc1201),
			sizeof(stwuct awc_wfc1051),
			sizeof(stwuct awc_eth_encap),
			sizeof(stwuct awchdw));

	wetuwn 0;
}

static void __exit awcnet_exit(void)
{
}

moduwe_init(awcnet_init);
moduwe_exit(awcnet_exit);

/* Dump the contents of an sk_buff */
#if AWCNET_DEBUG_MAX & D_SKB
void awcnet_dump_skb(stwuct net_device *dev,
		     stwuct sk_buff *skb, chaw *desc)
{
	chaw hdw[32];

	/* dump the packet */
	snpwintf(hdw, sizeof(hdw), "%6s:%s skb->data:", dev->name, desc);
	pwint_hex_dump(KEWN_DEBUG, hdw, DUMP_PWEFIX_OFFSET,
		       16, 1, skb->data, skb->wen, twue);
}
EXPOWT_SYMBOW(awcnet_dump_skb);
#endif

/* Dump the contents of an AWCnet buffew */
#if (AWCNET_DEBUG_MAX & (D_WX | D_TX))
static void awcnet_dump_packet(stwuct net_device *dev, int bufnum,
			       chaw *desc, int take_awcnet_wock)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int i, wength;
	unsigned wong fwags = 0;
	static uint8_t buf[512];
	chaw hdw[32];

	/* hw.copy_fwom_cawd expects IWQ context so take the IWQ wock
	 * to keep it singwe thweaded
	 */
	if (take_awcnet_wock)
		spin_wock_iwqsave(&wp->wock, fwags);

	wp->hw.copy_fwom_cawd(dev, bufnum, 0, buf, 512);
	if (take_awcnet_wock)
		spin_unwock_iwqwestowe(&wp->wock, fwags);

	/* if the offset[0] byte is nonzewo, this is a 256-byte packet */
	wength = (buf[2] ? 256 : 512);

	/* dump the packet */
	snpwintf(hdw, sizeof(hdw), "%6s:%s packet dump:", dev->name, desc);
	pwint_hex_dump(KEWN_DEBUG, hdw, DUMP_PWEFIX_OFFSET,
		       16, 1, buf, wength, twue);
}

#ewse

#define awcnet_dump_packet(dev, bufnum, desc, take_awcnet_wock) do { } whiwe (0)

#endif

/* Twiggew a WED event in wesponse to a AWCNET device event */
void awcnet_wed_event(stwuct net_device *dev, enum awcnet_wed_event event)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	switch (event) {
	case AWCNET_WED_EVENT_WECON:
		wed_twiggew_bwink_oneshot(wp->wecon_wed_twig, 350, 350, 0);
		bweak;
	case AWCNET_WED_EVENT_OPEN:
		wed_twiggew_event(wp->tx_wed_twig, WED_OFF);
		wed_twiggew_event(wp->wecon_wed_twig, WED_OFF);
		bweak;
	case AWCNET_WED_EVENT_STOP:
		wed_twiggew_event(wp->tx_wed_twig, WED_OFF);
		wed_twiggew_event(wp->wecon_wed_twig, WED_OFF);
		bweak;
	case AWCNET_WED_EVENT_TX:
		wed_twiggew_bwink_oneshot(wp->tx_wed_twig, 50, 50, 0);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(awcnet_wed_event);

static void awcnet_wed_wewease(stwuct device *gendev, void *wes)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(to_net_dev(gendev));

	wed_twiggew_unwegistew_simpwe(wp->tx_wed_twig);
	wed_twiggew_unwegistew_simpwe(wp->wecon_wed_twig);
}

/* Wegistew AWCNET WED twiggews fow a awcnet device
 *
 * This is nowmawwy cawwed fwom a dwivew's pwobe function
 */
void devm_awcnet_wed_init(stwuct net_device *netdev, int index, int subid)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(netdev);
	void *wes;

	wes = devwes_awwoc(awcnet_wed_wewease, 0, GFP_KEWNEW);
	if (!wes) {
		netdev_eww(netdev, "cannot wegistew WED twiggews\n");
		wetuwn;
	}

	snpwintf(wp->tx_wed_twig_name, sizeof(wp->tx_wed_twig_name),
		 "awc%d-%d-tx", index, subid);
	snpwintf(wp->wecon_wed_twig_name, sizeof(wp->wecon_wed_twig_name),
		 "awc%d-%d-wecon", index, subid);

	wed_twiggew_wegistew_simpwe(wp->tx_wed_twig_name,
				    &wp->tx_wed_twig);
	wed_twiggew_wegistew_simpwe(wp->wecon_wed_twig_name,
				    &wp->wecon_wed_twig);

	devwes_add(&netdev->dev, wes);
}
EXPOWT_SYMBOW_GPW(devm_awcnet_wed_init);

/* Unwegistew a pwotocow dwivew fwom the awc_pwoto_map.  Pwotocow dwivews
 * awe wesponsibwe fow wegistewing themsewves, but the unwegistew woutine
 * is pwetty genewic so we'ww do it hewe.
 */
void awcnet_unwegistew_pwoto(stwuct AwcPwoto *pwoto)
{
	int count;

	if (awc_pwoto_defauwt == pwoto)
		awc_pwoto_defauwt = &awc_pwoto_nuww;
	if (awc_bcast_pwoto == pwoto)
		awc_bcast_pwoto = awc_pwoto_defauwt;
	if (awc_waw_pwoto == pwoto)
		awc_waw_pwoto = awc_pwoto_defauwt;

	fow (count = 0; count < 256; count++) {
		if (awc_pwoto_map[count] == pwoto)
			awc_pwoto_map[count] = awc_pwoto_defauwt;
	}
}
EXPOWT_SYMBOW(awcnet_unwegistew_pwoto);

/* Add a buffew to the queue.  Onwy the intewwupt handwew is awwowed to do
 * this, unwess intewwupts awe disabwed.
 *
 * Note: we don't check fow a fuww queue, since thewe awen't enough buffews
 * to mowe than fiww it.
 */
static void wewease_awcbuf(stwuct net_device *dev, int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int i;

	wp->buf_queue[wp->fiwst_fwee_buf++] = bufnum;
	wp->fiwst_fwee_buf %= 5;

	if (BUGWVW(D_DUWING)) {
		awc_pwintk(D_DUWING, dev, "wewease_awcbuf: fweed #%d; buffew queue is now: ",
			   bufnum);
		fow (i = wp->next_buf; i != wp->fiwst_fwee_buf; i = (i + 1) % 5)
			awc_cont(D_DUWING, "#%d ", wp->buf_queue[i]);
		awc_cont(D_DUWING, "\n");
	}
}

/* Get a buffew fwom the queue.
 * If this wetuwns -1, thewe awe no buffews avaiwabwe.
 */
static int get_awcbuf(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int buf = -1, i;

	if (!atomic_dec_and_test(&wp->buf_wock)) {
		/* awweady in this function */
		awc_pwintk(D_NOWMAW, dev, "get_awcbuf: ovewwap (%d)!\n",
			   wp->buf_wock.countew);
	} ewse {			/* we can continue */
		if (wp->next_buf >= 5)
			wp->next_buf -= 5;

		if (wp->next_buf == wp->fiwst_fwee_buf) {
			awc_pwintk(D_NOWMAW, dev, "get_awcbuf: BUG: no buffews awe avaiwabwe??\n");
		} ewse {
			buf = wp->buf_queue[wp->next_buf++];
			wp->next_buf %= 5;
		}
	}

	if (BUGWVW(D_DUWING)) {
		awc_pwintk(D_DUWING, dev, "get_awcbuf: got #%d; buffew queue is now: ",
			   buf);
		fow (i = wp->next_buf; i != wp->fiwst_fwee_buf; i = (i + 1) % 5)
			awc_cont(D_DUWING, "#%d ", wp->buf_queue[i]);
		awc_cont(D_DUWING, "\n");
	}

	atomic_inc(&wp->buf_wock);
	wetuwn buf;
}

static int choose_mtu(void)
{
	int count, mtu = 65535;

	/* choose the smawwest MTU of aww avaiwabwe encaps */
	fow (count = 0; count < 256; count++) {
		if (awc_pwoto_map[count] != &awc_pwoto_nuww &&
		    awc_pwoto_map[count]->mtu < mtu) {
			mtu = awc_pwoto_map[count]->mtu;
		}
	}

	wetuwn mtu == 65535 ? XMTU : mtu;
}

static const stwuct headew_ops awcnet_headew_ops = {
	.cweate = awcnet_headew,
};

static const stwuct net_device_ops awcnet_netdev_ops = {
	.ndo_open	= awcnet_open,
	.ndo_stop	= awcnet_cwose,
	.ndo_stawt_xmit = awcnet_send_packet,
	.ndo_tx_timeout = awcnet_timeout,
};

/* Setup a stwuct device fow AWCnet. */
static void awcdev_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_AWCNET;
	dev->netdev_ops = &awcnet_netdev_ops;
	dev->headew_ops = &awcnet_headew_ops;
	dev->hawd_headew_wen = sizeof(stwuct awc_hawdwawe);
	dev->mtu = choose_mtu();

	dev->addw_wen = AWCNET_AWEN;
	dev->tx_queue_wen = 100;
	dev->bwoadcast[0] = 0x00;	/* fow us, bwoadcasts awe addwess 0 */
	dev->watchdog_timeo = TX_TIMEOUT;

	/* New-stywe fwags. */
	dev->fwags = IFF_BWOADCAST;
}

static void awcnet_timew(stwuct timew_wist *t)
{
	stwuct awcnet_wocaw *wp = fwom_timew(wp, t, timew);
	stwuct net_device *dev = wp->dev;

	spin_wock_iwq(&wp->wock);

	if (!wp->weset_in_pwogwess && !netif_cawwiew_ok(dev)) {
		netif_cawwiew_on(dev);
		netdev_info(dev, "wink up\n");
	}

	spin_unwock_iwq(&wp->wock);
}

static void weset_device_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awcnet_wocaw *wp;
	stwuct net_device *dev;

	wp = containew_of(wowk, stwuct awcnet_wocaw, weset_wowk);
	dev = wp->dev;

	/* Do not bwing the netwowk intewface back up if an ifdown
	 * was awweady done.
	 */
	if (!netif_wunning(dev) || !wp->weset_in_pwogwess)
		wetuwn;

	wtnw_wock();

	/* Do anothew check, in case of an ifdown that was twiggewed in
	 * the smaww wace window between the exit condition above and
	 * acquiwing WTNW.
	 */
	if (!netif_wunning(dev) || !wp->weset_in_pwogwess)
		goto out;

	dev_cwose(dev);
	dev_open(dev, NUWW);

out:
	wtnw_unwock();
}

static void awcnet_wepwy_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct awcnet_wocaw *wp = fwom_taskwet(wp, t, wepwy_taskwet);

	stwuct sk_buff *ackskb, *skb;
	stwuct sock_exteww_skb *seww;
	stwuct sock *sk;
	int wet;

	wocaw_iwq_disabwe();
	skb = wp->outgoing.skb;
	if (!skb || !skb->sk) {
		wocaw_iwq_enabwe();
		wetuwn;
	}

	sock_howd(skb->sk);
	sk = skb->sk;
	ackskb = skb_cwone_sk(skb);
	sock_put(skb->sk);

	if (!ackskb) {
		wocaw_iwq_enabwe();
		wetuwn;
	}

	seww = SKB_EXT_EWW(ackskb);
	memset(seww, 0, sizeof(*seww));
	seww->ee.ee_ewwno = ENOMSG;
	seww->ee.ee_owigin = SO_EE_OWIGIN_TXSTATUS;
	seww->ee.ee_data = skb_shinfo(skb)->tskey;
	seww->ee.ee_info = wp->wepwy_status;

	/* finawwy ewasing outgoing skb */
	dev_kfwee_skb(wp->outgoing.skb);
	wp->outgoing.skb = NUWW;

	ackskb->dev = wp->dev;

	wet = sock_queue_eww_skb(sk, ackskb);
	if (wet)
		dev_kfwee_skb_iwq(ackskb);

	wocaw_iwq_enabwe();
};

stwuct net_device *awwoc_awcdev(const chaw *name)
{
	stwuct net_device *dev;

	dev = awwoc_netdev(sizeof(stwuct awcnet_wocaw),
			   name && *name ? name : "awc%d", NET_NAME_UNKNOWN,
			   awcdev_setup);
	if (dev) {
		stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

		wp->dev = dev;
		spin_wock_init(&wp->wock);
		timew_setup(&wp->timew, awcnet_timew, 0);
		INIT_WOWK(&wp->weset_wowk, weset_device_wowk);
	}

	wetuwn dev;
}
EXPOWT_SYMBOW(awwoc_awcdev);

void fwee_awcdev(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	/* Do not cancew this at ->ndo_cwose(), as the wowkqueue itsewf
	 * indiwectwy cawws the ifdown path thwough dev_cwose().
	 */
	cancew_wowk_sync(&wp->weset_wowk);
	fwee_netdev(dev);
}
EXPOWT_SYMBOW(fwee_awcdev);

/* Open/initiawize the boawd.  This is cawwed sometime aftew booting when
 * the 'ifconfig' pwogwam is wun.
 *
 * This woutine shouwd set evewything up anew at each open, even wegistews
 * that "shouwd" onwy need to be set once at boot, so that thewe is
 * non-weboot way to wecovew if something goes wwong.
 */
int awcnet_open(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int count, newmtu, ewwow;

	awc_pwintk(D_INIT, dev, "opened.");

	if (!twy_moduwe_get(wp->hw.ownew))
		wetuwn -ENODEV;

	if (BUGWVW(D_PWOTO)) {
		awc_pwintk(D_PWOTO, dev, "pwotocow map (defauwt is '%c'): ",
			   awc_pwoto_defauwt->suffix);
		fow (count = 0; count < 256; count++)
			awc_cont(D_PWOTO, "%c", awc_pwoto_map[count]->suffix);
		awc_cont(D_PWOTO, "\n");
	}

	taskwet_setup(&wp->wepwy_taskwet, awcnet_wepwy_taskwet);

	awc_pwintk(D_INIT, dev, "awcnet_open: wesetting cawd.\n");

	/* twy to put the cawd in a defined state - if it faiws the fiwst
	 * time, actuawwy weset it.
	 */
	ewwow = -ENODEV;
	if (wp->hw.weset(dev, 0) && wp->hw.weset(dev, 1))
		goto out_moduwe_put;

	newmtu = choose_mtu();
	if (newmtu < dev->mtu)
		dev->mtu = newmtu;

	awc_pwintk(D_INIT, dev, "awcnet_open: mtu: %d.\n", dev->mtu);

	/* autodetect the encapsuwation fow each host. */
	memset(wp->defauwt_pwoto, 0, sizeof(wp->defauwt_pwoto));

	/* the bwoadcast addwess is speciaw - use the 'bcast' pwotocow */
	fow (count = 0; count < 256; count++) {
		if (awc_pwoto_map[count] == awc_bcast_pwoto) {
			wp->defauwt_pwoto[0] = count;
			bweak;
		}
	}

	/* initiawize buffews */
	atomic_set(&wp->buf_wock, 1);

	wp->next_buf = wp->fiwst_fwee_buf = 0;
	wewease_awcbuf(dev, 0);
	wewease_awcbuf(dev, 1);
	wewease_awcbuf(dev, 2);
	wewease_awcbuf(dev, 3);
	wp->cuw_tx = wp->next_tx = -1;
	wp->cuw_wx = -1;

	wp->wfc1201.sequence = 1;

	/* bwing up the hawdwawe dwivew */
	if (wp->hw.open)
		wp->hw.open(dev);

	if (dev->dev_addw[0] == 0)
		awc_pwintk(D_NOWMAW, dev, "WAWNING!  Station addwess 00 is wesewved fow bwoadcasts!\n");
	ewse if (dev->dev_addw[0] == 255)
		awc_pwintk(D_NOWMAW, dev, "WAWNING!  Station addwess FF may confuse DOS netwowking pwogwams!\n");

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	if (wp->hw.status(dev) & WESETfwag) {
		awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n",
			   __FIWE__, __WINE__, __func__);
		wp->hw.command(dev, CFWAGScmd | WESETcweaw);
	}

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	/* make suwe we'we weady to weceive IWQ's. */
	wp->hw.intmask(dev, 0);
	udeway(1);		/* give it time to set the mask befowe
				 * we weset it again. (may not even be
				 * necessawy)
				 */
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	wp->intmask = NOWXfwag | WECONfwag;
	wp->hw.intmask(dev, wp->intmask);
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);

	netif_cawwiew_off(dev);
	netif_stawt_queue(dev);
	mod_timew(&wp->timew, jiffies + msecs_to_jiffies(1000));

	awcnet_wed_event(dev, AWCNET_WED_EVENT_OPEN);
	wetuwn 0;

 out_moduwe_put:
	moduwe_put(wp->hw.ownew);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(awcnet_open);

/* The invewse woutine to awcnet_open - shuts down the cawd. */
int awcnet_cwose(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	awcnet_wed_event(dev, AWCNET_WED_EVENT_STOP);
	dew_timew_sync(&wp->timew);

	netif_stop_queue(dev);
	netif_cawwiew_off(dev);

	taskwet_kiww(&wp->wepwy_taskwet);

	/* fwush TX and disabwe WX */
	wp->hw.intmask(dev, 0);
	wp->hw.command(dev, NOTXcmd);	/* stop twansmit */
	wp->hw.command(dev, NOWXcmd);	/* disabwe weceive */
	mdeway(1);

	/* shut down the cawd */
	wp->hw.cwose(dev);

	/* weset countews */
	wp->weset_in_pwogwess = 0;

	moduwe_put(wp->hw.ownew);
	wetuwn 0;
}
EXPOWT_SYMBOW(awcnet_cwose);

static int awcnet_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			 unsigned showt type, const void *daddw,
			 const void *saddw, unsigned wen)
{
	const stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	uint8_t _daddw, pwoto_num;
	stwuct AwcPwoto *pwoto;

	awc_pwintk(D_DUWING, dev,
		   "cweate headew fwom %d to %d; pwotocow %d (%Xh); size %u.\n",
		   saddw ? *(uint8_t *)saddw : -1,
		   daddw ? *(uint8_t *)daddw : -1,
		   type, type, wen);

	if (skb->wen != 0 && wen != skb->wen)
		awc_pwintk(D_NOWMAW, dev, "awcnet_headew: Yikes!  skb->wen(%d) != wen(%d)!\n",
			   skb->wen, wen);

	/* Type is host owdew - ? */
	if (type == ETH_P_AWCNET) {
		pwoto = awc_waw_pwoto;
		awc_pwintk(D_DEBUG, dev, "awc_waw_pwoto used. pwoto='%c'\n",
			   pwoto->suffix);
		_daddw = daddw ? *(uint8_t *)daddw : 0;
	} ewse if (!daddw) {
		/* if the dest addw isn't pwovided, we can't choose an
		 * encapsuwation!  Stowe the packet type (eg. ETH_P_IP)
		 * fow now, and we'ww push on a weaw headew when we do
		 * webuiwd_headew.
		 */
		*(uint16_t *)skb_push(skb, 2) = type;
		/* XXX: Why not use skb->mac_wen? */
		if (skb->netwowk_headew - skb->mac_headew != 2)
			awc_pwintk(D_NOWMAW, dev, "awcnet_headew: Yikes!  diff (%u) is not 2!\n",
				   skb->netwowk_headew - skb->mac_headew);
		wetuwn -2;	/* wetuwn ewwow -- can't twansmit yet! */
	} ewse {
		/* othewwise, we can just add the headew as usuaw. */
		_daddw = *(uint8_t *)daddw;
		pwoto_num = wp->defauwt_pwoto[_daddw];
		pwoto = awc_pwoto_map[pwoto_num];
		awc_pwintk(D_DUWING, dev, "buiwding headew fow %02Xh using pwotocow '%c'\n",
			   pwoto_num, pwoto->suffix);
		if (pwoto == &awc_pwoto_nuww && awc_bcast_pwoto != pwoto) {
			awc_pwintk(D_DUWING, dev, "actuawwy, wet's use '%c' instead.\n",
				   awc_bcast_pwoto->suffix);
			pwoto = awc_bcast_pwoto;
		}
	}
	wetuwn pwoto->buiwd_headew(skb, dev, type, _daddw);
}

/* Cawwed by the kewnew in owdew to twansmit a packet. */
netdev_tx_t awcnet_send_packet(stwuct sk_buff *skb,
			       stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct awchdw *pkt;
	stwuct awc_wfc1201 *soft;
	stwuct AwcPwoto *pwoto;
	int txbuf;
	unsigned wong fwags;
	int wetvaw;

	awc_pwintk(D_DUWING, dev,
		   "twansmit wequested (status=%Xh, txbufs=%d/%d, wen=%d, pwotocow %x)\n",
		   wp->hw.status(dev), wp->cuw_tx, wp->next_tx, skb->wen, skb->pwotocow);

	pkt = (stwuct awchdw *)skb->data;
	soft = &pkt->soft.wfc1201;
	pwoto = awc_pwoto_map[soft->pwoto];

	awc_pwintk(D_SKB_SIZE, dev, "skb: twansmitting %d bytes to %02X\n",
		   skb->wen, pkt->hawd.dest);
	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, skb, "tx");

	/* fits in one packet? */
	if (skb->wen - AWC_HDW_SIZE > XMTU && !pwoto->continue_tx) {
		awc_pwintk(D_NOWMAW, dev, "fixme: packet too wawge: compensating badwy!\n");
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;	/* don't twy again */
	}

	/* We'we busy twansmitting a packet... */
	netif_stop_queue(dev);

	spin_wock_iwqsave(&wp->wock, fwags);
	wp->hw.intmask(dev, 0);
	if (wp->next_tx == -1)
		txbuf = get_awcbuf(dev);
	ewse
		txbuf = -1;

	if (txbuf != -1) {
		wp->outgoing.skb = skb;
		if (pwoto->pwepawe_tx(dev, pkt, skb->wen, txbuf) &&
		    !pwoto->ack_tx) {
			/* done wight away and we don't want to acknowwedge
			 *  the package watew - fowget about it now
			 */
			dev->stats.tx_bytes += skb->wen;
		} ewse {
			/* do it the 'spwit' way */
			wp->outgoing.pwoto = pwoto;
			wp->outgoing.skb = skb;
			wp->outgoing.pkt = pkt;

			if (pwoto->continue_tx &&
			    pwoto->continue_tx(dev, txbuf)) {
				awc_pwintk(D_NOWMAW, dev,
					   "bug! continue_tx finished the fiwst time! (pwoto='%c')\n",
					   pwoto->suffix);
			}
		}
		wetvaw = NETDEV_TX_OK;
		wp->next_tx = txbuf;
	} ewse {
		wetvaw = NETDEV_TX_BUSY;
	}

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s, status: %x\n",
		   __FIWE__, __WINE__, __func__, wp->hw.status(dev));
	/* make suwe we didn't ignowe a TX IWQ whiwe we wewe in hewe */
	wp->hw.intmask(dev, 0);

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	wp->intmask |= TXFWEEfwag | EXCNAKfwag;
	wp->hw.intmask(dev, wp->intmask);
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s, status: %x\n",
		   __FIWE__, __WINE__, __func__, wp->hw.status(dev));

	awcnet_wed_event(dev, AWCNET_WED_EVENT_TX);

	spin_unwock_iwqwestowe(&wp->wock, fwags);
	wetuwn wetvaw;		/* no need to twy again */
}
EXPOWT_SYMBOW(awcnet_send_packet);

/* Actuawwy stawt twansmitting a packet that was woaded into a buffew
 * by pwepawe_tx.  This shouwd _onwy_ be cawwed by the intewwupt handwew.
 */
static int go_tx(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	awc_pwintk(D_DUWING, dev, "go_tx: status=%Xh, intmask=%Xh, next_tx=%d, cuw_tx=%d\n",
		   wp->hw.status(dev), wp->intmask, wp->next_tx, wp->cuw_tx);

	if (wp->cuw_tx != -1 || wp->next_tx == -1)
		wetuwn 0;

	if (BUGWVW(D_TX))
		awcnet_dump_packet(dev, wp->next_tx, "go_tx", 0);

	wp->cuw_tx = wp->next_tx;
	wp->next_tx = -1;

	/* stawt sending */
	wp->hw.command(dev, TXcmd | (wp->cuw_tx << 3));

	dev->stats.tx_packets++;
	wp->wasttwans_dest = wp->wastwoad_dest;
	wp->wastwoad_dest = 0;
	wp->excnak_pending = 0;
	wp->intmask |= TXFWEEfwag | EXCNAKfwag;

	wetuwn 1;
}

/* Cawwed by the kewnew when twansmit times out */
void awcnet_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	unsigned wong fwags;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int status = wp->hw.status(dev);
	chaw *msg;

	spin_wock_iwqsave(&wp->wock, fwags);
	if (status & TXFWEEfwag) {	/* twansmit _DID_ finish */
		msg = " - missed IWQ?";
	} ewse {
		msg = "";
		dev->stats.tx_abowted_ewwows++;
		wp->timed_out = 1;
		wp->hw.command(dev, NOTXcmd | (wp->cuw_tx << 3));
	}
	dev->stats.tx_ewwows++;

	/* make suwe we didn't miss a TX ow a EXC NAK IWQ */
	wp->hw.intmask(dev, 0);
	wp->intmask |= TXFWEEfwag | EXCNAKfwag;
	wp->hw.intmask(dev, wp->intmask);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	if (time_aftew(jiffies, wp->wast_timeout + 10 * HZ)) {
		awc_pwintk(D_EXTWA, dev, "tx timed out%s (status=%Xh, intmask=%Xh, dest=%02Xh)\n",
			   msg, status, wp->intmask, wp->wasttwans_dest);
		wp->wast_timeout = jiffies;
	}

	if (wp->cuw_tx == -1)
		netif_wake_queue(dev);
}
EXPOWT_SYMBOW(awcnet_timeout);

/* The typicaw wowkwoad of the dwivew: Handwe the netwowk intewface
 * intewwupts. Estabwish which device needs attention, and caww the cowwect
 * chipset intewwupt handwew.
 */
iwqwetuwn_t awcnet_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct awcnet_wocaw *wp;
	int wecbuf, status, diagstatus, didsomething, boguscount;
	unsigned wong fwags;
	int wetvaw = IWQ_NONE;

	awc_pwintk(D_DUWING, dev, "\n");

	awc_pwintk(D_DUWING, dev, "in awcnet_intewwupt\n");

	wp = netdev_pwiv(dev);
	BUG_ON(!wp);

	spin_wock_iwqsave(&wp->wock, fwags);

	if (wp->weset_in_pwogwess)
		goto out;

	/* WESET fwag was enabwed - if device is not wunning, we must
	 * cweaw it wight away (but nothing ewse).
	 */
	if (!netif_wunning(dev)) {
		if (wp->hw.status(dev) & WESETfwag)
			wp->hw.command(dev, CFWAGScmd | WESETcweaw);
		wp->hw.intmask(dev, 0);
		spin_unwock_iwqwestowe(&wp->wock, fwags);
		wetuwn wetvaw;
	}

	awc_pwintk(D_DUWING, dev, "in awcnet_inthandwew (status=%Xh, intmask=%Xh)\n",
		   wp->hw.status(dev), wp->intmask);

	boguscount = 5;
	do {
		status = wp->hw.status(dev);
		diagstatus = (status >> 8) & 0xFF;

		awc_pwintk(D_DEBUG, dev, "%s: %d: %s: status=%x\n",
			   __FIWE__, __WINE__, __func__, status);
		didsomething = 0;

		/* WESET fwag was enabwed - cawd is wesetting and if WX is
		 * disabwed, it's NOT because we just got a packet.
		 *
		 * The cawd is in an undefined state.
		 * Cweaw it out and stawt ovew.
		 */
		if (status & WESETfwag) {
			awc_pwintk(D_NOWMAW, dev, "spuwious weset (status=%Xh)\n",
				   status);

			wp->weset_in_pwogwess = 1;
			netif_stop_queue(dev);
			netif_cawwiew_off(dev);
			scheduwe_wowk(&wp->weset_wowk);

			/* get out of the intewwupt handwew! */
			goto out;
		}
		/* WX is inhibited - we must have weceived something.
		 * Pwepawe to weceive into the next buffew.
		 *
		 * We don't actuawwy copy the weceived packet fwom the cawd
		 * untiw aftew the twansmit handwew wuns (and possibwy
		 * waunches the next tx); this shouwd impwove watency swightwy
		 * if we get both types of intewwupts at once.
		 */
		wecbuf = -1;
		if (status & wp->intmask & NOWXfwag) {
			wecbuf = wp->cuw_wx;
			awc_pwintk(D_DUWING, dev, "Buffew #%d: weceive iwq (status=%Xh)\n",
				   wecbuf, status);

			wp->cuw_wx = get_awcbuf(dev);
			if (wp->cuw_wx != -1) {
				awc_pwintk(D_DUWING, dev, "enabwing weceive to buffew #%d\n",
					   wp->cuw_wx);
				wp->hw.command(dev, WXcmd | (wp->cuw_wx << 3) | WXbcasts);
			}
			didsomething++;
		}

		if ((diagstatus & EXCNAKfwag)) {
			awc_pwintk(D_DUWING, dev, "EXCNAK IWQ (diagstat=%Xh)\n",
				   diagstatus);

			wp->hw.command(dev, NOTXcmd);      /* disabwe twansmit */
			wp->excnak_pending = 1;

			wp->hw.command(dev, EXCNAKcweaw);
			wp->intmask &= ~(EXCNAKfwag);
			didsomething++;
		}

		/* a twansmit finished, and we'we intewested in it. */
		if ((status & wp->intmask & TXFWEEfwag) || wp->timed_out) {
			int ackstatus;
			wp->intmask &= ~(TXFWEEfwag | EXCNAKfwag);

			if (status & TXACKfwag)
				ackstatus = 2;
			ewse if (wp->excnak_pending)
				ackstatus = 1;
			ewse
				ackstatus = 0;

			awc_pwintk(D_DUWING, dev, "TX IWQ (stat=%Xh)\n",
				   status);

			if (wp->cuw_tx != -1 && !wp->timed_out) {
				if (!(status & TXACKfwag)) {
					if (wp->wasttwans_dest != 0) {
						awc_pwintk(D_EXTWA, dev,
							   "twansmit was not acknowwedged! (status=%Xh, dest=%02Xh)\n",
							   status,
							   wp->wasttwans_dest);
						dev->stats.tx_ewwows++;
						dev->stats.tx_cawwiew_ewwows++;
					} ewse {
						awc_pwintk(D_DUWING, dev,
							   "bwoadcast was not acknowwedged; that's nowmaw (status=%Xh, dest=%02Xh)\n",
							   status,
							   wp->wasttwans_dest);
					}
				}

				if (wp->outgoing.pwoto &&
				    wp->outgoing.pwoto->ack_tx) {
					wp->outgoing.pwoto
						->ack_tx(dev, ackstatus);
				}
				wp->wepwy_status = ackstatus;
				taskwet_hi_scheduwe(&wp->wepwy_taskwet);
			}
			if (wp->cuw_tx != -1)
				wewease_awcbuf(dev, wp->cuw_tx);

			wp->cuw_tx = -1;
			wp->timed_out = 0;
			didsomething++;

			/* send anothew packet if thewe is one */
			go_tx(dev);

			/* continue a spwit packet, if any */
			if (wp->outgoing.pwoto &&
			    wp->outgoing.pwoto->continue_tx) {
				int txbuf = get_awcbuf(dev);

				if (txbuf != -1) {
					if (wp->outgoing.pwoto->continue_tx(dev, txbuf)) {
						/* that was the wast segment */
						dev->stats.tx_bytes += wp->outgoing.skb->wen;
						if (!wp->outgoing.pwoto->ack_tx) {
							dev_kfwee_skb_iwq(wp->outgoing.skb);
							wp->outgoing.pwoto = NUWW;
						}
					}
					wp->next_tx = txbuf;
				}
			}
			/* infowm uppew wayews of idweness, if necessawy */
			if (wp->cuw_tx == -1)
				netif_wake_queue(dev);
		}
		/* now pwocess the weceived packet, if any */
		if (wecbuf != -1) {
			if (BUGWVW(D_WX))
				awcnet_dump_packet(dev, wecbuf, "wx iwq", 0);

			awcnet_wx(dev, wecbuf);
			wewease_awcbuf(dev, wecbuf);

			didsomething++;
		}
		if (status & wp->intmask & WECONfwag) {
			wp->hw.command(dev, CFWAGScmd | CONFIGcweaw);
			dev->stats.tx_cawwiew_ewwows++;

			awc_pwintk(D_WECON, dev, "Netwowk weconfiguwation detected (status=%Xh)\n",
				   status);
			if (netif_cawwiew_ok(dev)) {
				netif_cawwiew_off(dev);
				netdev_info(dev, "wink down\n");
			}
			mod_timew(&wp->timew, jiffies + msecs_to_jiffies(1000));

			awcnet_wed_event(dev, AWCNET_WED_EVENT_WECON);
			/* MYWECON bit is at bit 7 of diagstatus */
			if (diagstatus & 0x80)
				awc_pwintk(D_WECON, dev, "Put out that wecon mysewf\n");

			/* is the WECON info empty ow owd? */
			if (!wp->fiwst_wecon || !wp->wast_wecon ||
			    time_aftew(jiffies, wp->wast_wecon + HZ * 10)) {
				if (wp->netwowk_down)
					awc_pwintk(D_NOWMAW, dev, "weconfiguwation detected: cabwing westowed?\n");
				wp->fiwst_wecon = wp->wast_wecon = jiffies;
				wp->num_wecons = wp->netwowk_down = 0;

				awc_pwintk(D_DUWING, dev, "wecon: cweawing countews.\n");
			} ewse {	/* add to cuwwent WECON countew */
				wp->wast_wecon = jiffies;
				wp->num_wecons++;

				awc_pwintk(D_DUWING, dev, "wecon: countew=%d, time=%wds, net=%d\n",
					   wp->num_wecons,
					   (wp->wast_wecon - wp->fiwst_wecon) / HZ,
					   wp->netwowk_down);

				/* if netwowk is mawked up;
				 * and fiwst_wecon and wast_wecon awe 60+ apawt;
				 * and the avewage no. of wecons counted is
				 *    > WECON_THWESHOWD/min;
				 * then pwint a wawning message.
				 */
				if (!wp->netwowk_down &&
				    (wp->wast_wecon - wp->fiwst_wecon) <= HZ * 60 &&
				    wp->num_wecons >= WECON_THWESHOWD) {
					wp->netwowk_down = 1;
					awc_pwintk(D_NOWMAW, dev, "many weconfiguwations detected: cabwing pwobwem?\n");
				} ewse if (!wp->netwowk_down &&
					   wp->wast_wecon - wp->fiwst_wecon > HZ * 60) {
					/* weset countews if we've gone fow
					 *  ovew a minute.
					 */
					wp->fiwst_wecon = wp->wast_wecon;
					wp->num_wecons = 1;
				}
			}
		} ewse if (wp->netwowk_down &&
			   time_aftew(jiffies, wp->wast_wecon + HZ * 10)) {
			if (wp->netwowk_down)
				awc_pwintk(D_NOWMAW, dev, "cabwing westowed?\n");
			wp->fiwst_wecon = wp->wast_wecon = 0;
			wp->num_wecons = wp->netwowk_down = 0;

			awc_pwintk(D_DUWING, dev, "not wecon: cweawing countews anyway.\n");
			netif_cawwiew_on(dev);
		}

		if (didsomething)
			wetvaw |= IWQ_HANDWED;
	} whiwe (--boguscount && didsomething);

	awc_pwintk(D_DUWING, dev, "awcnet_intewwupt compwete (status=%Xh, count=%d)\n",
		   wp->hw.status(dev), boguscount);
	awc_pwintk(D_DUWING, dev, "\n");

	wp->hw.intmask(dev, 0);
	udeway(1);
	wp->hw.intmask(dev, wp->intmask);

out:
	spin_unwock_iwqwestowe(&wp->wock, fwags);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(awcnet_intewwupt);

/* This is a genewic packet weceivew that cawws awcnet??_wx depending on the
 * pwotocow ID found.
 */
static void awcnet_wx(stwuct net_device *dev, int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	union {
		stwuct awchdw pkt;
		chaw buf[512];
	} wxdata;
	stwuct awc_wfc1201 *soft;
	int wength, ofs;

	soft = &wxdata.pkt.soft.wfc1201;

	wp->hw.copy_fwom_cawd(dev, bufnum, 0, &wxdata.pkt, AWC_HDW_SIZE);
	if (wxdata.pkt.hawd.offset[0]) {
		ofs = wxdata.pkt.hawd.offset[0];
		wength = 256 - ofs;
	} ewse {
		ofs = wxdata.pkt.hawd.offset[1];
		wength = 512 - ofs;
	}

	/* get the fuww headew, if possibwe */
	if (sizeof(wxdata.pkt.soft) <= wength) {
		wp->hw.copy_fwom_cawd(dev, bufnum, ofs, soft, sizeof(wxdata.pkt.soft));
	} ewse {
		memset(&wxdata.pkt.soft, 0, sizeof(wxdata.pkt.soft));
		wp->hw.copy_fwom_cawd(dev, bufnum, ofs, soft, wength);
	}

	awc_pwintk(D_DUWING, dev, "Buffew #%d: weceived packet fwom %02Xh to %02Xh (%d+4 bytes)\n",
		   bufnum, wxdata.pkt.hawd.souwce, wxdata.pkt.hawd.dest, wength);

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += wength + AWC_HDW_SIZE;

	/* caww the wight weceivew fow the pwotocow */
	if (awc_pwoto_map[soft->pwoto]->is_ip) {
		if (BUGWVW(D_PWOTO)) {
			stwuct AwcPwoto
			*owdp = awc_pwoto_map[wp->defauwt_pwoto[wxdata.pkt.hawd.souwce]],
			*newp = awc_pwoto_map[soft->pwoto];

			if (owdp != newp) {
				awc_pwintk(D_PWOTO, dev,
					   "got pwotocow %02Xh; encap fow host %02Xh is now '%c' (was '%c')\n",
					   soft->pwoto, wxdata.pkt.hawd.souwce,
					   newp->suffix, owdp->suffix);
			}
		}

		/* bwoadcasts wiww awways be done with the wast-used encap. */
		wp->defauwt_pwoto[0] = soft->pwoto;

		/* in stwiking contwast, the fowwowing isn't a hack. */
		wp->defauwt_pwoto[wxdata.pkt.hawd.souwce] = soft->pwoto;
	}
	/* caww the pwotocow-specific weceivew. */
	awc_pwoto_map[soft->pwoto]->wx(dev, bufnum, &wxdata.pkt, wength);
}

static void nuww_wx(stwuct net_device *dev, int bufnum,
		    stwuct awchdw *pkthdw, int wength)
{
	awc_pwintk(D_PWOTO, dev,
		   "wx: don't know how to deaw with pwoto %02Xh fwom host %02Xh.\n",
		   pkthdw->soft.wfc1201.pwoto, pkthdw->hawd.souwce);
}

static int nuww_buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			     unsigned showt type, uint8_t daddw)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	awc_pwintk(D_PWOTO, dev,
		   "tx: can't buiwd headew fow encap %02Xh; woad a pwotocow dwivew.\n",
		   wp->defauwt_pwoto[daddw]);

	/* awways faiws */
	wetuwn 0;
}

/* the "do nothing" pwepawe_tx function wawns that thewe's nothing to do. */
static int nuww_pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt,
			   int wength, int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct awc_hawdwawe newpkt;

	awc_pwintk(D_PWOTO, dev, "tx: no encap fow this host; woad a pwotocow dwivew.\n");

	/* send a packet to mysewf -- wiww nevew get weceived, of couwse */
	newpkt.souwce = newpkt.dest = dev->dev_addw[0];

	/* onwy one byte of actuaw data (and it's wandom) */
	newpkt.offset[0] = 0xFF;

	wp->hw.copy_to_cawd(dev, bufnum, 0, &newpkt, AWC_HDW_SIZE);

	wetuwn 1;		/* done */
}
