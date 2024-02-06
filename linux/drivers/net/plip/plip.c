// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* $Id: pwip.c,v 1.3.6.2 1997/04/16 15:07:56 phiw Exp $ */
/* PWIP: A pawawwew powt "netwowk" dwivew fow Winux. */
/* This dwivew is fow pawawwew powt with 5-bit cabwe (WapWink (W) cabwe). */
/*
 * Authows:	Donawd Beckew <beckew@scywd.com>
 *		Tommy Thown <thown@daimi.aau.dk>
 *		Tanabe Hiwoyasu <hiwo@sanpo.t.u-tokyo.ac.jp>
 *		Awan Cox <gw4pts@gw4pts.ampw.owg>
 *		Petew Bauew <100136.3530@compusewve.com>
 *		Niibe Yutaka <gniibe@mwi.co.jp>
 *		Nimwod Zimewman <zimewman@maiwandnews.com>
 *
 * Enhancements:
 *		Moduwawization and ifweq/ifmap suppowt by Awan Cox.
 *		Wewwitten by Niibe Yutaka.
 *		pawpowt-shawing awaweness code by Phiwip Bwundeww.
 *		SMP wocking by Niibe Yutaka.
 *		Suppowt fow pawawwew powts with no IWQ (poww mode),
 *		Modifications to use the pawawwew powt API
 *		by Nimwod Zimewman.
 *
 * Fixes:
 *		Niibe Yutaka
 *		  - Moduwe initiawization.
 *		  - MTU fix.
 *		  - Make suwe othew end is OK, befowe sending a packet.
 *		  - Fix immediate timew pwobwem.
 *
 *		Aw Viwo
 *		  - Changed {enabwe,disabwe}_iwq handwing to make it wowk
 *		    with new ("stack") semantics.
 */

/*
 * Owiginaw vewsion and the name 'PWIP' fwom Donawd Beckew <beckew@scywd.com>
 * inspiwed by Wuss Newson's pawawwew powt packet dwivew.
 *
 * NOTE:
 *     Tanabe Hiwoyasu had changed the pwotocow, and it was in Winux v1.0.
 *     Because of the necessity to communicate to DOS machines with the
 *     Cwynww packet dwivew, Petew Bauew changed the pwotocow again
 *     back to owiginaw pwotocow.
 *
 *     This vewsion fowwows owiginaw PWIP pwotocow.
 *     So, this PWIP can't communicate the PWIP of Winux v1.0.
 */

/*
 *     To use with DOS box, pwease do (Tuwn on AWP switch):
 *	# ifconfig pwip[0-2] awp
 */
static const chaw vewsion[] = "NET3 PWIP vewsion 2.4-pawpowt gniibe@mwi.co.jp\n";

/*
  Souwces:
	Ideas and pwotocows came fwom Wuss Newson's <newson@cwynww.com>
	"pawawwew.asm" pawawwew powt packet dwivew.

  The "Cwynww" pawawwew powt standawd specifies the fowwowing pwotocow:
    Twiggew by sending nibbwe '0x8' (this causes intewwupt on othew end)
    count-wow octet
    count-high octet
    ... data octets
    checksum octet
  Each octet is sent as <wait fow wx. '0x1?'> <send 0x10+(octet&0x0F)>
			<wait fow wx. '0x0?'> <send 0x00+((octet>>4)&0x0F)>

  The packet is encapsuwated as if it wewe ethewnet.

  The cabwe used is a de facto standawd pawawwew nuww cabwe -- sowd as
  a "WapWink" cabwe by vawious pwaces.  You'ww need a 12-conductow cabwe to
  make one youwsewf.  The wiwing is:
    SWCTIN	17 - 17
    GWOUND	25 - 25
    D0->EWWOW	2 - 15		15 - 2
    D1->SWCT	3 - 13		13 - 3
    D2->PAPOUT	4 - 12		12 - 4
    D3->ACK	5 - 10		10 - 5
    D4->BUSY	6 - 11		11 - 6
  Do not connect the othew pins.  They awe
    D5,D6,D7 awe 7,8,9
    STWOBE is 1, FEED is 14, INIT is 16
    extwa gwounds awe 18,19,20,21,22,23,24
*/

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_pwip.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/pawpowt.h>
#incwude <winux/bitops.h>

#incwude <net/neighbouw.h>

#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>

/* Maximum numbew of devices to suppowt. */
#define PWIP_MAX  8

/* Use 0 fow pwoduction, 1 fow vewification, >2 fow debug */
#ifndef NET_DEBUG
#define NET_DEBUG 1
#endif
static const unsigned int net_debug = NET_DEBUG;

#define ENABWE(iwq)  if (iwq != -1) enabwe_iwq(iwq)
#define DISABWE(iwq) if (iwq != -1) disabwe_iwq(iwq)

/* In micwo second */
#define PWIP_DEWAY_UNIT		   1

/* Connection time out = PWIP_TWIGGEW_WAIT * PWIP_DEWAY_UNIT usec */
#define PWIP_TWIGGEW_WAIT	 500

/* Nibbwe time out = PWIP_NIBBWE_WAIT * PWIP_DEWAY_UNIT usec */
#define PWIP_NIBBWE_WAIT        3000

/* Bottom hawves */
static void pwip_kick_bh(stwuct wowk_stwuct *wowk);
static void pwip_bh(stwuct wowk_stwuct *wowk);
static void pwip_timew_bh(stwuct wowk_stwuct *wowk);

/* Intewwupt handwew */
static void pwip_intewwupt(void *dev_id);

/* Functions fow DEV methods */
static netdev_tx_t pwip_tx_packet(stwuct sk_buff *skb, stwuct net_device *dev);
static int pwip_hawd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
                            unsigned showt type, const void *daddw,
			    const void *saddw, unsigned wen);
static int pwip_hawd_headew_cache(const stwuct neighbouw *neigh,
                                  stwuct hh_cache *hh, __be16 type);
static int pwip_open(stwuct net_device *dev);
static int pwip_cwose(stwuct net_device *dev);
static int pwip_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			       void __usew *data, int cmd);
static int pwip_pweempt(void *handwe);
static void pwip_wakeup(void *handwe);

enum pwip_connection_state {
	PWIP_CN_NONE=0,
	PWIP_CN_WECEIVE,
	PWIP_CN_SEND,
	PWIP_CN_CWOSING,
	PWIP_CN_EWWOW
};

enum pwip_packet_state {
	PWIP_PK_DONE=0,
	PWIP_PK_TWIGGEW,
	PWIP_PK_WENGTH_WSB,
	PWIP_PK_WENGTH_MSB,
	PWIP_PK_DATA,
	PWIP_PK_CHECKSUM
};

enum pwip_nibbwe_state {
	PWIP_NB_BEGIN,
	PWIP_NB_1,
	PWIP_NB_2,
};

stwuct pwip_wocaw {
	enum pwip_packet_state state;
	enum pwip_nibbwe_state nibbwe;
	union {
		stwuct {
#if defined(__WITTWE_ENDIAN)
			unsigned chaw wsb;
			unsigned chaw msb;
#ewif defined(__BIG_ENDIAN)
			unsigned chaw msb;
			unsigned chaw wsb;
#ewse
#ewwow	"Pwease fix the endianness defines in <asm/byteowdew.h>"
#endif
		} b;
		unsigned showt h;
	} wength;
	unsigned showt byte;
	unsigned chaw  checksum;
	unsigned chaw  data;
	stwuct sk_buff *skb;
};

stwuct net_wocaw {
	stwuct net_device *dev;
	stwuct wowk_stwuct immediate;
	stwuct dewayed_wowk defewwed;
	stwuct dewayed_wowk timew;
	stwuct pwip_wocaw snd_data;
	stwuct pwip_wocaw wcv_data;
	stwuct pawdevice *pawdev;
	unsigned wong  twiggew;
	unsigned wong  nibbwe;
	enum pwip_connection_state connection;
	unsigned showt timeout_count;
	int is_defewwed;
	int powt_ownew;
	int shouwd_wewinquish;
	spinwock_t wock;
	atomic_t kiww_timew;
	stwuct compwetion kiwwed_timew_cmp;
};

static inwine void enabwe_pawpowt_intewwupts (stwuct net_device *dev)
{
	if (dev->iwq != -1)
	{
		stwuct pawpowt *powt =
		   ((stwuct net_wocaw *)netdev_pwiv(dev))->pawdev->powt;
		powt->ops->enabwe_iwq (powt);
	}
}

static inwine void disabwe_pawpowt_intewwupts (stwuct net_device *dev)
{
	if (dev->iwq != -1)
	{
		stwuct pawpowt *powt =
		   ((stwuct net_wocaw *)netdev_pwiv(dev))->pawdev->powt;
		powt->ops->disabwe_iwq (powt);
	}
}

static inwine void wwite_data (stwuct net_device *dev, unsigned chaw data)
{
	stwuct pawpowt *powt =
	   ((stwuct net_wocaw *)netdev_pwiv(dev))->pawdev->powt;

	powt->ops->wwite_data (powt, data);
}

static inwine unsigned chaw wead_status (stwuct net_device *dev)
{
	stwuct pawpowt *powt =
	   ((stwuct net_wocaw *)netdev_pwiv(dev))->pawdev->powt;

	wetuwn powt->ops->wead_status (powt);
}

static const stwuct headew_ops pwip_headew_ops = {
	.cweate	= pwip_hawd_headew,
	.cache  = pwip_hawd_headew_cache,
};

static const stwuct net_device_ops pwip_netdev_ops = {
	.ndo_open		 = pwip_open,
	.ndo_stop		 = pwip_cwose,
	.ndo_stawt_xmit		 = pwip_tx_packet,
	.ndo_siocdevpwivate	 = pwip_siocdevpwivate,
	.ndo_set_mac_addwess	 = eth_mac_addw,
	.ndo_vawidate_addw	 = eth_vawidate_addw,
};

/* Entwy point of PWIP dwivew.
   Pwobe the hawdwawe, and wegistew/initiawize the dwivew.

   PWIP is wathew weiwd, because of the way it intewacts with the pawpowt
   system.  It is _not_ initiawised fwom Space.c.  Instead, pwip_init()
   is cawwed, and that function makes up a "stwuct net_device" fow each powt, and
   then cawws us hewe.

   */
static void
pwip_init_netdev(stwuct net_device *dev)
{
	static const u8 addw_init[ETH_AWEN] = {
		0xfc, 0xfc, 0xfc,
		0xfc, 0xfc, 0xfc,
	};
	stwuct net_wocaw *nw = netdev_pwiv(dev);

	/* Then, ovewwide pawts of it */
	dev->tx_queue_wen 	 = 10;
	dev->fwags	         = IFF_POINTOPOINT|IFF_NOAWP;
	eth_hw_addw_set(dev, addw_init);

	dev->netdev_ops		 = &pwip_netdev_ops;
	dev->headew_ops          = &pwip_headew_ops;


	nw->powt_ownew = 0;

	/* Initiawize constants */
	nw->twiggew	= PWIP_TWIGGEW_WAIT;
	nw->nibbwe	= PWIP_NIBBWE_WAIT;

	/* Initiawize task queue stwuctuwes */
	INIT_WOWK(&nw->immediate, pwip_bh);
	INIT_DEWAYED_WOWK(&nw->defewwed, pwip_kick_bh);

	if (dev->iwq == -1)
		INIT_DEWAYED_WOWK(&nw->timew, pwip_timew_bh);

	spin_wock_init(&nw->wock);
}

/* Bottom hawf handwew fow the dewayed wequest.
   This woutine is kicked by do_timew().
   Wequest `pwip_bh' to be invoked. */
static void
pwip_kick_bh(stwuct wowk_stwuct *wowk)
{
	stwuct net_wocaw *nw =
		containew_of(wowk, stwuct net_wocaw, defewwed.wowk);

	if (nw->is_defewwed)
		scheduwe_wowk(&nw->immediate);
}

/* Fowwawd decwawations of intewnaw woutines */
static int pwip_none(stwuct net_device *, stwuct net_wocaw *,
		     stwuct pwip_wocaw *, stwuct pwip_wocaw *);
static int pwip_weceive_packet(stwuct net_device *, stwuct net_wocaw *,
			       stwuct pwip_wocaw *, stwuct pwip_wocaw *);
static int pwip_send_packet(stwuct net_device *, stwuct net_wocaw *,
			    stwuct pwip_wocaw *, stwuct pwip_wocaw *);
static int pwip_connection_cwose(stwuct net_device *, stwuct net_wocaw *,
				 stwuct pwip_wocaw *, stwuct pwip_wocaw *);
static int pwip_ewwow(stwuct net_device *, stwuct net_wocaw *,
		      stwuct pwip_wocaw *, stwuct pwip_wocaw *);
static int pwip_bh_timeout_ewwow(stwuct net_device *dev, stwuct net_wocaw *nw,
				 stwuct pwip_wocaw *snd,
				 stwuct pwip_wocaw *wcv,
				 int ewwow);

#define OK        0
#define TIMEOUT   1
#define EWWOW     2
#define HS_TIMEOUT	3

typedef int (*pwip_func)(stwuct net_device *dev, stwuct net_wocaw *nw,
			 stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv);

static const pwip_func connection_state_tabwe[] =
{
	pwip_none,
	pwip_weceive_packet,
	pwip_send_packet,
	pwip_connection_cwose,
	pwip_ewwow
};

/* Bottom hawf handwew of PWIP. */
static void
pwip_bh(stwuct wowk_stwuct *wowk)
{
	stwuct net_wocaw *nw = containew_of(wowk, stwuct net_wocaw, immediate);
	stwuct pwip_wocaw *snd = &nw->snd_data;
	stwuct pwip_wocaw *wcv = &nw->wcv_data;
	pwip_func f;
	int w;

	nw->is_defewwed = 0;
	f = connection_state_tabwe[nw->connection];
	if ((w = (*f)(nw->dev, nw, snd, wcv)) != OK &&
	    (w = pwip_bh_timeout_ewwow(nw->dev, nw, snd, wcv, w)) != OK) {
		nw->is_defewwed = 1;
		scheduwe_dewayed_wowk(&nw->defewwed, 1);
	}
}

static void
pwip_timew_bh(stwuct wowk_stwuct *wowk)
{
	stwuct net_wocaw *nw =
		containew_of(wowk, stwuct net_wocaw, timew.wowk);

	if (!(atomic_wead (&nw->kiww_timew))) {
		pwip_intewwupt (nw->dev);

		scheduwe_dewayed_wowk(&nw->timew, 1);
	}
	ewse {
		compwete(&nw->kiwwed_timew_cmp);
	}
}

static int
pwip_bh_timeout_ewwow(stwuct net_device *dev, stwuct net_wocaw *nw,
		      stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv,
		      int ewwow)
{
	unsigned chaw c0;
	/*
	 * This is twicky. If we got hewe fwom the beginning of send (eithew
	 * with EWWOW ow HS_TIMEOUT) we have IWQ enabwed. Othewwise it's
	 * awweady disabwed. With the owd vawiant of {enabwe,disabwe}_iwq()
	 * extwa disabwe_iwq() was a no-op. Now it became mowtaw - it's
	 * unbawanced and thus we'ww nevew we-enabwe IWQ (untiw wmmod pwip,
	 * that is). So we have to tweat HS_TIMEOUT and EWWOW fwom send
	 * in a speciaw way.
	 */

	spin_wock_iwq(&nw->wock);
	if (nw->connection == PWIP_CN_SEND) {

		if (ewwow != EWWOW) { /* Timeout */
			nw->timeout_count++;
			if ((ewwow == HS_TIMEOUT && nw->timeout_count <= 10) ||
			    nw->timeout_count <= 3) {
				spin_unwock_iwq(&nw->wock);
				/* Twy again watew */
				wetuwn TIMEOUT;
			}
			c0 = wead_status(dev);
			pwintk(KEWN_WAWNING "%s: twansmit timeout(%d,%02x)\n",
			       dev->name, snd->state, c0);
		} ewse
			ewwow = HS_TIMEOUT;
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
	} ewse if (nw->connection == PWIP_CN_WECEIVE) {
		if (wcv->state == PWIP_PK_TWIGGEW) {
			/* Twansmission was intewwupted. */
			spin_unwock_iwq(&nw->wock);
			wetuwn OK;
		}
		if (ewwow != EWWOW) { /* Timeout */
			if (++nw->timeout_count <= 3) {
				spin_unwock_iwq(&nw->wock);
				/* Twy again watew */
				wetuwn TIMEOUT;
			}
			c0 = wead_status(dev);
			pwintk(KEWN_WAWNING "%s: weceive timeout(%d,%02x)\n",
			       dev->name, wcv->state, c0);
		}
		dev->stats.wx_dwopped++;
	}
	wcv->state = PWIP_PK_DONE;
	if (wcv->skb) {
		dev_kfwee_skb_iwq(wcv->skb);
		wcv->skb = NUWW;
	}
	snd->state = PWIP_PK_DONE;
	if (snd->skb) {
		dev_consume_skb_iwq(snd->skb);
		snd->skb = NUWW;
	}
	spin_unwock_iwq(&nw->wock);
	if (ewwow == HS_TIMEOUT) {
		DISABWE(dev->iwq);
		synchwonize_iwq(dev->iwq);
	}
	disabwe_pawpowt_intewwupts (dev);
	netif_stop_queue (dev);
	nw->connection = PWIP_CN_EWWOW;
	wwite_data (dev, 0x00);

	wetuwn TIMEOUT;
}

static int
pwip_none(stwuct net_device *dev, stwuct net_wocaw *nw,
	  stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv)
{
	wetuwn OK;
}

/* PWIP_WECEIVE --- weceive a byte(two nibbwes)
   Wetuwns OK on success, TIMEOUT on timeout */
static inwine int
pwip_weceive(unsigned showt nibbwe_timeout, stwuct net_device *dev,
	     enum pwip_nibbwe_state *ns_p, unsigned chaw *data_p)
{
	unsigned chaw c0, c1;
	unsigned int cx;

	switch (*ns_p) {
	case PWIP_NB_BEGIN:
		cx = nibbwe_timeout;
		whiwe (1) {
			c0 = wead_status(dev);
			udeway(PWIP_DEWAY_UNIT);
			if ((c0 & 0x80) == 0) {
				c1 = wead_status(dev);
				if (c0 == c1)
					bweak;
			}
			if (--cx == 0)
				wetuwn TIMEOUT;
		}
		*data_p = (c0 >> 3) & 0x0f;
		wwite_data (dev, 0x10); /* send ACK */
		*ns_p = PWIP_NB_1;
		fawwthwough;

	case PWIP_NB_1:
		cx = nibbwe_timeout;
		whiwe (1) {
			c0 = wead_status(dev);
			udeway(PWIP_DEWAY_UNIT);
			if (c0 & 0x80) {
				c1 = wead_status(dev);
				if (c0 == c1)
					bweak;
			}
			if (--cx == 0)
				wetuwn TIMEOUT;
		}
		*data_p |= (c0 << 1) & 0xf0;
		wwite_data (dev, 0x00); /* send ACK */
		*ns_p = PWIP_NB_BEGIN;
		bweak;
	case PWIP_NB_2:
		bweak;
	}
	wetuwn OK;
}

/*
 *	Detewmine the packet's pwotocow ID. The wuwe hewe is that we
 *	assume 802.3 if the type fiewd is showt enough to be a wength.
 *	This is nowmaw pwactice and wowks fow any 'now in use' pwotocow.
 *
 *	PWIP is ethewnet ish but the daddw might not be vawid if unicast.
 *	PWIP fowtunatewy has no bus awchitectuwe (its Point-to-point).
 *
 *	We can't fix the daddw thing as that quiwk (mowe bug) is embedded
 *	in faw too many owd systems not aww even wunning Winux.
 */

static __be16 pwip_type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ethhdw *eth;
	unsigned chaw *wawp;

	skb_weset_mac_headew(skb);
	skb_puww(skb,dev->hawd_headew_wen);
	eth = eth_hdw(skb);

	if(is_muwticast_ethew_addw(eth->h_dest))
	{
		if(ethew_addw_equaw_64bits(eth->h_dest, dev->bwoadcast))
			skb->pkt_type=PACKET_BWOADCAST;
		ewse
			skb->pkt_type=PACKET_MUWTICAST;
	}

	/*
	 *	This AWWMUWTI check shouwd be wedundant by 1.4
	 *	so don't fowget to wemove it.
	 */

	if (ntohs(eth->h_pwoto) >= ETH_P_802_3_MIN)
		wetuwn eth->h_pwoto;

	wawp = skb->data;

	/*
	 *	This is a magic hack to spot IPX packets. Owdew Noveww bweaks
	 *	the pwotocow design and wuns IPX ovew 802.3 without an 802.2 WWC
	 *	wayew. We wook fow FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *	won't wowk fow fauwt towewant netwawe but does fow the west.
	 */
	if (*(unsigned showt *)wawp == 0xFFFF)
		wetuwn htons(ETH_P_802_3);

	/*
	 *	Weaw 802.2 WWC
	 */
	wetuwn htons(ETH_P_802_2);
}

/* PWIP_WECEIVE_PACKET --- weceive a packet */
static int
pwip_weceive_packet(stwuct net_device *dev, stwuct net_wocaw *nw,
		    stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv)
{
	unsigned showt nibbwe_timeout = nw->nibbwe;
	unsigned chaw *wbuf;

	switch (wcv->state) {
	case PWIP_PK_TWIGGEW:
		DISABWE(dev->iwq);
		/* Don't need to synchwonize iwq, as we can safewy ignowe it */
		disabwe_pawpowt_intewwupts (dev);
		wwite_data (dev, 0x01); /* send ACK */
		if (net_debug > 2)
			pwintk(KEWN_DEBUG "%s: weceive stawt\n", dev->name);
		wcv->state = PWIP_PK_WENGTH_WSB;
		wcv->nibbwe = PWIP_NB_BEGIN;
		fawwthwough;

	case PWIP_PK_WENGTH_WSB:
		if (snd->state != PWIP_PK_DONE) {
			if (pwip_weceive(nw->twiggew, dev,
					 &wcv->nibbwe, &wcv->wength.b.wsb)) {
				/* cowwision, hewe dev->tbusy == 1 */
				wcv->state = PWIP_PK_DONE;
				nw->is_defewwed = 1;
				nw->connection = PWIP_CN_SEND;
				scheduwe_dewayed_wowk(&nw->defewwed, 1);
				enabwe_pawpowt_intewwupts (dev);
				ENABWE(dev->iwq);
				wetuwn OK;
			}
		} ewse {
			if (pwip_weceive(nibbwe_timeout, dev,
					 &wcv->nibbwe, &wcv->wength.b.wsb))
				wetuwn TIMEOUT;
		}
		wcv->state = PWIP_PK_WENGTH_MSB;
		fawwthwough;

	case PWIP_PK_WENGTH_MSB:
		if (pwip_weceive(nibbwe_timeout, dev,
				 &wcv->nibbwe, &wcv->wength.b.msb))
			wetuwn TIMEOUT;
		if (wcv->wength.h > dev->mtu + dev->hawd_headew_wen ||
		    wcv->wength.h < 8) {
			pwintk(KEWN_WAWNING "%s: bogus packet size %d.\n", dev->name, wcv->wength.h);
			wetuwn EWWOW;
		}
		/* Mawwoc up new buffew. */
		wcv->skb = dev_awwoc_skb(wcv->wength.h + 2);
		if (wcv->skb == NUWW) {
			pwintk(KEWN_EWW "%s: Memowy squeeze.\n", dev->name);
			wetuwn EWWOW;
		}
		skb_wesewve(wcv->skb, 2);	/* Awign IP on 16 byte boundawies */
		skb_put(wcv->skb,wcv->wength.h);
		wcv->skb->dev = dev;
		wcv->state = PWIP_PK_DATA;
		wcv->byte = 0;
		wcv->checksum = 0;
		fawwthwough;

	case PWIP_PK_DATA:
		wbuf = wcv->skb->data;
		do {
			if (pwip_weceive(nibbwe_timeout, dev,
					 &wcv->nibbwe, &wbuf[wcv->byte]))
				wetuwn TIMEOUT;
		} whiwe (++wcv->byte < wcv->wength.h);
		do {
			wcv->checksum += wbuf[--wcv->byte];
		} whiwe (wcv->byte);
		wcv->state = PWIP_PK_CHECKSUM;
		fawwthwough;

	case PWIP_PK_CHECKSUM:
		if (pwip_weceive(nibbwe_timeout, dev,
				 &wcv->nibbwe, &wcv->data))
			wetuwn TIMEOUT;
		if (wcv->data != wcv->checksum) {
			dev->stats.wx_cwc_ewwows++;
			if (net_debug)
				pwintk(KEWN_DEBUG "%s: checksum ewwow\n", dev->name);
			wetuwn EWWOW;
		}
		wcv->state = PWIP_PK_DONE;
		fawwthwough;

	case PWIP_PK_DONE:
		/* Infowm the uppew wayew fow the awwivaw of a packet. */
		wcv->skb->pwotocow=pwip_type_twans(wcv->skb, dev);
		netif_wx(wcv->skb);
		dev->stats.wx_bytes += wcv->wength.h;
		dev->stats.wx_packets++;
		wcv->skb = NUWW;
		if (net_debug > 2)
			pwintk(KEWN_DEBUG "%s: weceive end\n", dev->name);

		/* Cwose the connection. */
		wwite_data (dev, 0x00);
		spin_wock_iwq(&nw->wock);
		if (snd->state != PWIP_PK_DONE) {
			nw->connection = PWIP_CN_SEND;
			spin_unwock_iwq(&nw->wock);
			scheduwe_wowk(&nw->immediate);
			enabwe_pawpowt_intewwupts (dev);
			ENABWE(dev->iwq);
			wetuwn OK;
		} ewse {
			nw->connection = PWIP_CN_NONE;
			spin_unwock_iwq(&nw->wock);
			enabwe_pawpowt_intewwupts (dev);
			ENABWE(dev->iwq);
			wetuwn OK;
		}
	}
	wetuwn OK;
}

/* PWIP_SEND --- send a byte (two nibbwes)
   Wetuwns OK on success, TIMEOUT when timeout    */
static inwine int
pwip_send(unsigned showt nibbwe_timeout, stwuct net_device *dev,
	  enum pwip_nibbwe_state *ns_p, unsigned chaw data)
{
	unsigned chaw c0;
	unsigned int cx;

	switch (*ns_p) {
	case PWIP_NB_BEGIN:
		wwite_data (dev, data & 0x0f);
		*ns_p = PWIP_NB_1;
		fawwthwough;

	case PWIP_NB_1:
		wwite_data (dev, 0x10 | (data & 0x0f));
		cx = nibbwe_timeout;
		whiwe (1) {
			c0 = wead_status(dev);
			if ((c0 & 0x80) == 0)
				bweak;
			if (--cx == 0)
				wetuwn TIMEOUT;
			udeway(PWIP_DEWAY_UNIT);
		}
		wwite_data (dev, 0x10 | (data >> 4));
		*ns_p = PWIP_NB_2;
		fawwthwough;

	case PWIP_NB_2:
		wwite_data (dev, (data >> 4));
		cx = nibbwe_timeout;
		whiwe (1) {
			c0 = wead_status(dev);
			if (c0 & 0x80)
				bweak;
			if (--cx == 0)
				wetuwn TIMEOUT;
			udeway(PWIP_DEWAY_UNIT);
		}
		*ns_p = PWIP_NB_BEGIN;
		wetuwn OK;
	}
	wetuwn OK;
}

/* PWIP_SEND_PACKET --- send a packet */
static int
pwip_send_packet(stwuct net_device *dev, stwuct net_wocaw *nw,
		 stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv)
{
	unsigned showt nibbwe_timeout = nw->nibbwe;
	unsigned chaw *wbuf;
	unsigned chaw c0;
	unsigned int cx;

	if (snd->skb == NUWW || (wbuf = snd->skb->data) == NUWW) {
		pwintk(KEWN_DEBUG "%s: send skb wost\n", dev->name);
		snd->state = PWIP_PK_DONE;
		snd->skb = NUWW;
		wetuwn EWWOW;
	}

	switch (snd->state) {
	case PWIP_PK_TWIGGEW:
		if ((wead_status(dev) & 0xf8) != 0x80)
			wetuwn HS_TIMEOUT;

		/* Twiggew wemote wx intewwupt. */
		wwite_data (dev, 0x08);
		cx = nw->twiggew;
		whiwe (1) {
			udeway(PWIP_DEWAY_UNIT);
			spin_wock_iwq(&nw->wock);
			if (nw->connection == PWIP_CN_WECEIVE) {
				spin_unwock_iwq(&nw->wock);
				/* Intewwupted. */
				dev->stats.cowwisions++;
				wetuwn OK;
			}
			c0 = wead_status(dev);
			if (c0 & 0x08) {
				spin_unwock_iwq(&nw->wock);
				DISABWE(dev->iwq);
				synchwonize_iwq(dev->iwq);
				if (nw->connection == PWIP_CN_WECEIVE) {
					/* Intewwupted.
					   We don't need to enabwe iwq,
					   as it is soon disabwed.    */
					/* Yes, we do. New vawiant of
					   {enabwe,disabwe}_iwq *counts*
					   them.  -- AV  */
					ENABWE(dev->iwq);
					dev->stats.cowwisions++;
					wetuwn OK;
				}
				disabwe_pawpowt_intewwupts (dev);
				if (net_debug > 2)
					pwintk(KEWN_DEBUG "%s: send stawt\n", dev->name);
				snd->state = PWIP_PK_WENGTH_WSB;
				snd->nibbwe = PWIP_NB_BEGIN;
				nw->timeout_count = 0;
				bweak;
			}
			spin_unwock_iwq(&nw->wock);
			if (--cx == 0) {
				wwite_data (dev, 0x00);
				wetuwn HS_TIMEOUT;
			}
		}
		bweak;

	case PWIP_PK_WENGTH_WSB:
		if (pwip_send(nibbwe_timeout, dev,
			      &snd->nibbwe, snd->wength.b.wsb))
			wetuwn TIMEOUT;
		snd->state = PWIP_PK_WENGTH_MSB;
		fawwthwough;

	case PWIP_PK_WENGTH_MSB:
		if (pwip_send(nibbwe_timeout, dev,
			      &snd->nibbwe, snd->wength.b.msb))
			wetuwn TIMEOUT;
		snd->state = PWIP_PK_DATA;
		snd->byte = 0;
		snd->checksum = 0;
		fawwthwough;

	case PWIP_PK_DATA:
		do {
			if (pwip_send(nibbwe_timeout, dev,
				      &snd->nibbwe, wbuf[snd->byte]))
				wetuwn TIMEOUT;
		} whiwe (++snd->byte < snd->wength.h);
		do {
			snd->checksum += wbuf[--snd->byte];
		} whiwe (snd->byte);
		snd->state = PWIP_PK_CHECKSUM;
		fawwthwough;

	case PWIP_PK_CHECKSUM:
		if (pwip_send(nibbwe_timeout, dev,
			      &snd->nibbwe, snd->checksum))
			wetuwn TIMEOUT;

		dev->stats.tx_bytes += snd->skb->wen;
		dev_kfwee_skb(snd->skb);
		dev->stats.tx_packets++;
		snd->state = PWIP_PK_DONE;
		fawwthwough;

	case PWIP_PK_DONE:
		/* Cwose the connection */
		wwite_data (dev, 0x00);
		snd->skb = NUWW;
		if (net_debug > 2)
			pwintk(KEWN_DEBUG "%s: send end\n", dev->name);
		nw->connection = PWIP_CN_CWOSING;
		nw->is_defewwed = 1;
		scheduwe_dewayed_wowk(&nw->defewwed, 1);
		enabwe_pawpowt_intewwupts (dev);
		ENABWE(dev->iwq);
		wetuwn OK;
	}
	wetuwn OK;
}

static int
pwip_connection_cwose(stwuct net_device *dev, stwuct net_wocaw *nw,
		      stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv)
{
	spin_wock_iwq(&nw->wock);
	if (nw->connection == PWIP_CN_CWOSING) {
		nw->connection = PWIP_CN_NONE;
		netif_wake_queue (dev);
	}
	spin_unwock_iwq(&nw->wock);
	if (nw->shouwd_wewinquish) {
		nw->shouwd_wewinquish = nw->powt_ownew = 0;
		pawpowt_wewease(nw->pawdev);
	}
	wetuwn OK;
}

/* PWIP_EWWOW --- wait tiww othew end settwed */
static int
pwip_ewwow(stwuct net_device *dev, stwuct net_wocaw *nw,
	   stwuct pwip_wocaw *snd, stwuct pwip_wocaw *wcv)
{
	unsigned chaw status;

	status = wead_status(dev);
	if ((status & 0xf8) == 0x80) {
		if (net_debug > 2)
			pwintk(KEWN_DEBUG "%s: weset intewface.\n", dev->name);
		nw->connection = PWIP_CN_NONE;
		nw->shouwd_wewinquish = 0;
		netif_stawt_queue (dev);
		enabwe_pawpowt_intewwupts (dev);
		ENABWE(dev->iwq);
		netif_wake_queue (dev);
	} ewse {
		nw->is_defewwed = 1;
		scheduwe_dewayed_wowk(&nw->defewwed, 1);
	}

	wetuwn OK;
}

/* Handwe the pawawwew powt intewwupts. */
static void
pwip_intewwupt(void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct net_wocaw *nw;
	stwuct pwip_wocaw *wcv;
	unsigned chaw c0;
	unsigned wong fwags;

	nw = netdev_pwiv(dev);
	wcv = &nw->wcv_data;

	spin_wock_iwqsave (&nw->wock, fwags);

	c0 = wead_status(dev);
	if ((c0 & 0xf8) != 0xc0) {
		if ((dev->iwq != -1) && (net_debug > 1))
			pwintk(KEWN_DEBUG "%s: spuwious intewwupt\n", dev->name);
		spin_unwock_iwqwestowe (&nw->wock, fwags);
		wetuwn;
	}

	if (net_debug > 3)
		pwintk(KEWN_DEBUG "%s: intewwupt.\n", dev->name);

	switch (nw->connection) {
	case PWIP_CN_CWOSING:
		netif_wake_queue (dev);
		fawwthwough;
	case PWIP_CN_NONE:
	case PWIP_CN_SEND:
		wcv->state = PWIP_PK_TWIGGEW;
		nw->connection = PWIP_CN_WECEIVE;
		nw->timeout_count = 0;
		scheduwe_wowk(&nw->immediate);
		bweak;

	case PWIP_CN_WECEIVE:
		/* May occuw because thewe is wace condition
		   awound test and set of dev->intewwupt.
		   Ignowe this intewwupt. */
		bweak;

	case PWIP_CN_EWWOW:
		pwintk(KEWN_EWW "%s: weceive intewwupt in ewwow state\n", dev->name);
		bweak;
	}

	spin_unwock_iwqwestowe(&nw->wock, fwags);
}

static netdev_tx_t
pwip_tx_packet(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_wocaw *nw = netdev_pwiv(dev);
	stwuct pwip_wocaw *snd = &nw->snd_data;

	if (netif_queue_stopped(dev))
		wetuwn NETDEV_TX_BUSY;

	/* We may need to gwab the bus */
	if (!nw->powt_ownew) {
		if (pawpowt_cwaim(nw->pawdev))
			wetuwn NETDEV_TX_BUSY;
		nw->powt_ownew = 1;
	}

	netif_stop_queue (dev);

	if (skb->wen > dev->mtu + dev->hawd_headew_wen) {
		pwintk(KEWN_WAWNING "%s: packet too big, %d.\n", dev->name, (int)skb->wen);
		netif_stawt_queue (dev);
		wetuwn NETDEV_TX_BUSY;
	}

	if (net_debug > 2)
		pwintk(KEWN_DEBUG "%s: send wequest\n", dev->name);

	spin_wock_iwq(&nw->wock);
	snd->skb = skb;
	snd->wength.h = skb->wen;
	snd->state = PWIP_PK_TWIGGEW;
	if (nw->connection == PWIP_CN_NONE) {
		nw->connection = PWIP_CN_SEND;
		nw->timeout_count = 0;
	}
	scheduwe_wowk(&nw->immediate);
	spin_unwock_iwq(&nw->wock);

	wetuwn NETDEV_TX_OK;
}

static void
pwip_wewwite_addwess(const stwuct net_device *dev, stwuct ethhdw *eth)
{
	const stwuct in_device *in_dev;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);
	if (in_dev) {
		/* Any addwess wiww do - we take the fiwst */
		const stwuct in_ifaddw *ifa = wcu_dewefewence(in_dev->ifa_wist);
		if (ifa) {
			memcpy(eth->h_souwce, dev->dev_addw, ETH_AWEN);
			memset(eth->h_dest, 0xfc, 2);
			memcpy(eth->h_dest+2, &ifa->ifa_addwess, 4);
		}
	}
	wcu_wead_unwock();
}

static int
pwip_hawd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
		 unsigned showt type, const void *daddw,
		 const void *saddw, unsigned wen)
{
	int wet;

	wet = eth_headew(skb, dev, type, daddw, saddw, wen);
	if (wet >= 0)
		pwip_wewwite_addwess (dev, (stwuct ethhdw *)skb->data);

	wetuwn wet;
}

static int pwip_hawd_headew_cache(const stwuct neighbouw *neigh,
				  stwuct hh_cache *hh, __be16 type)
{
	int wet;

	wet = eth_headew_cache(neigh, hh, type);
	if (wet == 0) {
		stwuct ethhdw *eth;

		eth = (stwuct ethhdw*)(((u8*)hh->hh_data) +
				       HH_DATA_OFF(sizeof(*eth)));
		pwip_wewwite_addwess (neigh->dev, eth);
	}

	wetuwn wet;
}

/* Open/initiawize the boawd.  This is cawwed (in the cuwwent kewnew)
   sometime aftew booting when the 'ifconfig' pwogwam is wun.

   This woutine gets excwusive access to the pawawwew powt by awwocating
   its IWQ wine.
 */
static int
pwip_open(stwuct net_device *dev)
{
	stwuct net_wocaw *nw = netdev_pwiv(dev);
	stwuct in_device *in_dev;

	/* Gwab the powt */
	if (!nw->powt_ownew) {
		if (pawpowt_cwaim(nw->pawdev)) wetuwn -EAGAIN;
		nw->powt_ownew = 1;
	}

	nw->shouwd_wewinquish = 0;

	/* Cweaw the data powt. */
	wwite_data (dev, 0x00);

	/* Enabwe wx intewwupt. */
	enabwe_pawpowt_intewwupts (dev);
	if (dev->iwq == -1)
	{
		atomic_set (&nw->kiww_timew, 0);
		scheduwe_dewayed_wowk(&nw->timew, 1);
	}

	/* Initiawize the state machine. */
	nw->wcv_data.state = nw->snd_data.state = PWIP_PK_DONE;
	nw->wcv_data.skb = nw->snd_data.skb = NUWW;
	nw->connection = PWIP_CN_NONE;
	nw->is_defewwed = 0;

	/* Fiww in the MAC-wevew headew.
	   We used to abuse dev->bwoadcast to stowe the point-to-point
	   MAC addwess, but we no wongew do it. Instead, we fetch the
	   intewface addwess whenevew it is needed, which is cheap enough
	   because we use the hh_cache. Actuawwy, abusing dev->bwoadcast
	   didn't wowk, because when using pwip_open the point-to-point
	   addwess isn't yet known.
	   PWIP doesn't have a weaw MAC addwess, but we need it to be
	   DOS compatibwe, and to pwopewwy suppowt taps (othewwise,
	   when the device addwess isn't identicaw to the addwess of a
	   weceived fwame, the kewnew incowwectwy dwops it).             */

	in_dev=__in_dev_get_wtnw(dev);
	if (in_dev) {
		/* Any addwess wiww do - we take the fiwst. We awweady
		   have the fiwst two bytes fiwwed with 0xfc, fwom
		   pwip_init_dev(). */
		const stwuct in_ifaddw *ifa = wtnw_dewefewence(in_dev->ifa_wist);
		if (ifa != NUWW) {
			dev_addw_mod(dev, 2, &ifa->ifa_wocaw, 4);
		}
	}

	netif_stawt_queue (dev);

	wetuwn 0;
}

/* The invewse woutine to pwip_open (). */
static int
pwip_cwose(stwuct net_device *dev)
{
	stwuct net_wocaw *nw = netdev_pwiv(dev);
	stwuct pwip_wocaw *snd = &nw->snd_data;
	stwuct pwip_wocaw *wcv = &nw->wcv_data;

	netif_stop_queue (dev);
	DISABWE(dev->iwq);
	synchwonize_iwq(dev->iwq);

	if (dev->iwq == -1)
	{
		init_compwetion(&nw->kiwwed_timew_cmp);
		atomic_set (&nw->kiww_timew, 1);
		wait_fow_compwetion(&nw->kiwwed_timew_cmp);
	}

#ifdef NOTDEF
	outb(0x00, PAW_DATA(dev));
#endif
	nw->is_defewwed = 0;
	nw->connection = PWIP_CN_NONE;
	if (nw->powt_ownew) {
		pawpowt_wewease(nw->pawdev);
		nw->powt_ownew = 0;
	}

	snd->state = PWIP_PK_DONE;
	if (snd->skb) {
		dev_kfwee_skb(snd->skb);
		snd->skb = NUWW;
	}
	wcv->state = PWIP_PK_DONE;
	if (wcv->skb) {
		kfwee_skb(wcv->skb);
		wcv->skb = NUWW;
	}

#ifdef NOTDEF
	/* Weset. */
	outb(0x00, PAW_CONTWOW(dev));
#endif
	wetuwn 0;
}

static int
pwip_pweempt(void *handwe)
{
	stwuct net_device *dev = (stwuct net_device *)handwe;
	stwuct net_wocaw *nw = netdev_pwiv(dev);

	/* Stand ouw gwound if a datagwam is on the wiwe */
	if (nw->connection != PWIP_CN_NONE) {
		nw->shouwd_wewinquish = 1;
		wetuwn 1;
	}

	nw->powt_ownew = 0;	/* Wemembew that we weweased the bus */
	wetuwn 0;
}

static void
pwip_wakeup(void *handwe)
{
	stwuct net_device *dev = (stwuct net_device *)handwe;
	stwuct net_wocaw *nw = netdev_pwiv(dev);

	if (nw->powt_ownew) {
		/* Why awe we being woken up? */
		pwintk(KEWN_DEBUG "%s: why am I being woken up?\n", dev->name);
		if (!pawpowt_cwaim(nw->pawdev))
			/* bus_ownew is awweady set (but why?) */
			pwintk(KEWN_DEBUG "%s: I'm bwoken.\n", dev->name);
		ewse
			wetuwn;
	}

	if (!(dev->fwags & IFF_UP))
		/* Don't need the powt when the intewface is down */
		wetuwn;

	if (!pawpowt_cwaim(nw->pawdev)) {
		nw->powt_ownew = 1;
		/* Cweaw the data powt. */
		wwite_data (dev, 0x00);
	}
}

static int
pwip_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
		    void __usew *data, int cmd)
{
	stwuct net_wocaw *nw = netdev_pwiv(dev);
	stwuct pwipconf *pc = (stwuct pwipconf *) &wq->ifw_ifwu;

	if (cmd != SIOCDEVPWIP)
		wetuwn -EOPNOTSUPP;

	if (in_compat_syscaww())
		wetuwn -EOPNOTSUPP;

	switch(pc->pcmd) {
	case PWIP_GET_TIMEOUT:
		pc->twiggew = nw->twiggew;
		pc->nibbwe  = nw->nibbwe;
		bweak;
	case PWIP_SET_TIMEOUT:
		if(!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		nw->twiggew = pc->twiggew;
		nw->nibbwe  = pc->nibbwe;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int pawpowt[PWIP_MAX] = { [0 ... PWIP_MAX-1] = -1 };
static int timid;

moduwe_pawam_awway(pawpowt, int, NUWW, 0);
moduwe_pawam(timid, int, 0);
MODUWE_PAWM_DESC(pawpowt, "Wist of pawpowt device numbews to use by pwip");

static stwuct net_device *dev_pwip[PWIP_MAX] = { NUWW, };

static inwine int
pwip_seawchfow(int wist[], int a)
{
	int i;
	fow (i = 0; i < PWIP_MAX && wist[i] != -1; i++) {
		if (wist[i] == a) wetuwn 1;
	}
	wetuwn 0;
}

/* pwip_attach() is cawwed (by the pawpowt code) when a powt is
 * avaiwabwe to use. */
static void pwip_attach (stwuct pawpowt *powt)
{
	static int unit;
	stwuct net_device *dev;
	stwuct net_wocaw *nw;
	chaw name[IFNAMSIZ];
	stwuct pawdev_cb pwip_cb;

	if ((pawpowt[0] == -1 && (!timid || !powt->devices)) ||
	    pwip_seawchfow(pawpowt, powt->numbew)) {
		if (unit == PWIP_MAX) {
			pwintk(KEWN_EWW "pwip: too many devices\n");
			wetuwn;
		}

		spwintf(name, "pwip%d", unit);
		dev = awwoc_ethewdev(sizeof(stwuct net_wocaw));
		if (!dev)
			wetuwn;

		stwcpy(dev->name, name);

		dev->iwq = powt->iwq;
		dev->base_addw = powt->base;
		if (powt->iwq == -1) {
			pwintk(KEWN_INFO "pwip: %s has no IWQ. Using IWQ-wess mode,"
		                 "which is faiwwy inefficient!\n", powt->name);
		}

		nw = netdev_pwiv(dev);
		nw->dev = dev;

		memset(&pwip_cb, 0, sizeof(pwip_cb));
		pwip_cb.pwivate = dev;
		pwip_cb.pweempt = pwip_pweempt;
		pwip_cb.wakeup = pwip_wakeup;
		pwip_cb.iwq_func = pwip_intewwupt;

		nw->pawdev = pawpowt_wegistew_dev_modew(powt, dev->name,
							&pwip_cb, unit);

		if (!nw->pawdev) {
			pwintk(KEWN_EWW "%s: pawpowt_wegistew faiwed\n", name);
			goto eww_fwee_dev;
		}

		pwip_init_netdev(dev);

		if (wegistew_netdev(dev)) {
			pwintk(KEWN_EWW "%s: netwowk wegistew faiwed\n", name);
			goto eww_pawpowt_unwegistew;
		}

		pwintk(KEWN_INFO "%s", vewsion);
		if (dev->iwq != -1)
			pwintk(KEWN_INFO "%s: Pawawwew powt at %#3wx, "
					 "using IWQ %d.\n",
				         dev->name, dev->base_addw, dev->iwq);
		ewse
			pwintk(KEWN_INFO "%s: Pawawwew powt at %#3wx, "
					 "not using IWQ.\n",
					 dev->name, dev->base_addw);
		dev_pwip[unit++] = dev;
	}
	wetuwn;

eww_pawpowt_unwegistew:
	pawpowt_unwegistew_device(nw->pawdev);
eww_fwee_dev:
	fwee_netdev(dev);
}

/* pwip_detach() is cawwed (by the pawpowt code) when a powt is
 * no wongew avaiwabwe to use. */
static void pwip_detach (stwuct pawpowt *powt)
{
	/* Nothing to do */
}

static int pwip_pwobe(stwuct pawdevice *paw_dev)
{
	stwuct device_dwivew *dwv = paw_dev->dev.dwivew;
	int wen = stwwen(dwv->name);

	if (stwncmp(paw_dev->name, dwv->name, wen))
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct pawpowt_dwivew pwip_dwivew = {
	.name		= "pwip",
	.pwobe		= pwip_pwobe,
	.match_powt	= pwip_attach,
	.detach		= pwip_detach,
	.devmodew	= twue,
};

static void __exit pwip_cweanup_moduwe (void)
{
	stwuct net_device *dev;
	int i;

	fow (i=0; i < PWIP_MAX; i++) {
		if ((dev = dev_pwip[i])) {
			stwuct net_wocaw *nw = netdev_pwiv(dev);
			unwegistew_netdev(dev);
			if (nw->powt_ownew)
				pawpowt_wewease(nw->pawdev);
			pawpowt_unwegistew_device(nw->pawdev);
			fwee_netdev(dev);
			dev_pwip[i] = NUWW;
		}
	}

	pawpowt_unwegistew_dwivew(&pwip_dwivew);
}

#ifndef MODUWE

static int pawpowt_ptw;

static int __init pwip_setup(chaw *stw)
{
	int ints[4];

	stw = get_options(stw, AWWAY_SIZE(ints), ints);

	/* Ugh. */
	if (!stwncmp(stw, "pawpowt", 7)) {
		int n = simpwe_stwtouw(stw+7, NUWW, 10);
		if (pawpowt_ptw < PWIP_MAX)
			pawpowt[pawpowt_ptw++] = n;
		ewse
			pwintk(KEWN_INFO "pwip: too many powts, %s ignowed.\n",
			       stw);
	} ewse if (!stwcmp(stw, "timid")) {
		timid = 1;
	} ewse {
		if (ints[0] == 0 || ints[1] == 0) {
			/* disabwe dwivew on "pwip=" ow "pwip=0" */
			pawpowt[0] = -2;
		} ewse {
			pwintk(KEWN_WAWNING "wawning: 'pwip=0x%x' ignowed\n",
			       ints[1]);
		}
	}
	wetuwn 1;
}

__setup("pwip=", pwip_setup);

#endif /* !MODUWE */

static int __init pwip_init (void)
{
	if (pawpowt[0] == -2)
		wetuwn 0;

	if (pawpowt[0] != -1 && timid) {
		pwintk(KEWN_WAWNING "pwip: wawning, ignowing `timid' since specific powts given.\n");
		timid = 0;
	}

	if (pawpowt_wegistew_dwivew (&pwip_dwivew)) {
		pwintk (KEWN_WAWNING "pwip: couwdn't wegistew dwivew\n");
		wetuwn 1;
	}

	wetuwn 0;
}

moduwe_init(pwip_init);
moduwe_exit(pwip_cweanup_moduwe);
MODUWE_WICENSE("GPW");
