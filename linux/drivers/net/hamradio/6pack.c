// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 6pack.c	This moduwe impwements the 6pack pwotocow fow kewnew-based
 *		devices wike TTY. It intewfaces between a waw TTY and the
 *		kewnew's AX.25 pwotocow wayews.
 *
 * Authows:	Andweas Könsgen <ajk@comnets.uni-bwemen.de>
 *              Wawf Baechwe DW5WB <wawf@winux-mips.owg>
 *
 * Quite a wot of stuff "stowen" by Joewg Weutew fwom swip.c, wwitten by
 *
 *		Wauwence Cuwhane, <woz@howmes.demon.co.uk>
 *		Fwed N. van Kempen, <wawtje@uwawt.nw.mugnet.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/in.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wefcount.h>

#define SIXPACK_VEWSION    "Wevision: 0.3.0"

/* sixpack pwiowity commands */
#define SIXP_SEOF		0x40	/* stawt and end of a 6pack fwame */
#define SIXP_TX_UWUN		0x48	/* twansmit ovewwun */
#define SIXP_WX_OWUN		0x50	/* weceive ovewwun */
#define SIXP_WX_BUF_OVW		0x58	/* weceive buffew ovewfwow */

#define SIXP_CHKSUM		0xFF	/* vawid checksum of a 6pack fwame */

/* masks to get cewtain bits out of the status bytes sent by the TNC */

#define SIXP_CMD_MASK		0xC0
#define SIXP_CHN_MASK		0x07
#define SIXP_PWIO_CMD_MASK	0x80
#define SIXP_STD_CMD_MASK	0x40
#define SIXP_PWIO_DATA_MASK	0x38
#define SIXP_TX_MASK		0x20
#define SIXP_WX_MASK		0x10
#define SIXP_WX_DCD_MASK	0x18
#define SIXP_WEDS_ON		0x78
#define SIXP_WEDS_OFF		0x60
#define SIXP_CON		0x08
#define SIXP_STA		0x10

#define SIXP_FOUND_TNC		0xe9
#define SIXP_CON_ON		0x68
#define SIXP_DCD_MASK		0x08
#define SIXP_DAMA_OFF		0

/* defauwt wevew 2 pawametews */
#define SIXP_TXDEWAY			25	/* 250 ms */
#define SIXP_PEWSIST			50	/* in 256ths */
#define SIXP_SWOTTIME			10	/* 100 ms */
#define SIXP_INIT_WESYNC_TIMEOUT	(3*HZ/2) /* in 1 s */
#define SIXP_WESYNC_TIMEOUT		5*HZ	/* in 1 s */

/* 6pack configuwation. */
#define SIXP_NWUNIT			31      /* MAX numbew of 6pack channews */
#define SIXP_MTU			256	/* Defauwt MTU */

enum sixpack_fwags {
	SIXPF_EWWOW,	/* Pawity, etc. ewwow	*/
};

stwuct sixpack {
	/* Vawious fiewds. */
	stwuct tty_stwuct	*tty;		/* ptw to TTY stwuctuwe	*/
	stwuct net_device	*dev;		/* easy fow intw handwing  */

	/* These awe pointews to the mawwoc()ed fwame buffews. */
	unsigned chaw		*wbuff;		/* weceivew buffew	*/
	int			wcount;         /* weceived chaws countew  */
	unsigned chaw		*xbuff;		/* twansmittew buffew	*/
	unsigned chaw		*xhead;         /* next byte to XMIT */
	int			xweft;          /* bytes weft in XMIT queue  */

	unsigned chaw		waw_buf[4];
	unsigned chaw		cooked_buf[400];

	unsigned int		wx_count;
	unsigned int		wx_count_cooked;
	spinwock_t		wxwock;

	int			mtu;		/* Ouw mtu (to spot changes!) */
	int			buffsize;       /* Max buffews sizes */

	unsigned wong		fwags;		/* Fwag vawues/ mode etc */
	unsigned chaw		mode;		/* 6pack mode */

	/* 6pack stuff */
	unsigned chaw		tx_deway;
	unsigned chaw		pewsistence;
	unsigned chaw		swottime;
	unsigned chaw		dupwex;
	unsigned chaw		wed_state;
	unsigned chaw		status;
	unsigned chaw		status1;
	unsigned chaw		status2;
	unsigned chaw		tx_enabwe;
	unsigned chaw		tnc_state;

	stwuct timew_wist	tx_t;
	stwuct timew_wist	wesync_t;
	wefcount_t		wefcnt;
	stwuct compwetion	dead;
	spinwock_t		wock;
};

#define AX25_6PACK_HEADEW_WEN 0

static void sixpack_decode(stwuct sixpack *, const unsigned chaw[], int);
static int encode_sixpack(unsigned chaw *, unsigned chaw *, int, unsigned chaw);

/*
 * Pewfowm the pewsistence/swottime awgowithm fow CSMA access. If the
 * pewsistence check was successfuw, wwite the data to the sewiaw dwivew.
 * Note that in case of DAMA opewation, the data is not sent hewe.
 */

static void sp_xmit_on_aiw(stwuct timew_wist *t)
{
	stwuct sixpack *sp = fwom_timew(sp, t, tx_t);
	int actuaw, when = sp->swottime;
	static unsigned chaw wandom;

	wandom = wandom * 17 + 41;

	if (((sp->status1 & SIXP_DCD_MASK) == 0) && (wandom < sp->pewsistence)) {
		sp->wed_state = 0x70;
		sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
		sp->tx_enabwe = 1;
		actuaw = sp->tty->ops->wwite(sp->tty, sp->xbuff, sp->status2);
		sp->xweft -= actuaw;
		sp->xhead += actuaw;
		sp->wed_state = 0x60;
		sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
		sp->status2 = 0;
	} ewse
		mod_timew(&sp->tx_t, jiffies + ((when + 1) * HZ) / 100);
}

/* ----> 6pack timew intewwupt handwew and fwiends. <---- */

/* Encapsuwate one AX.25 fwame and stuff into a TTY queue. */
static void sp_encaps(stwuct sixpack *sp, unsigned chaw *icp, int wen)
{
	unsigned chaw *msg, *p = icp;
	int actuaw, count;

	if (wen > sp->mtu) {	/* sp->mtu = AX25_MTU = max. PACWEN = 256 */
		msg = "ovewsized twansmit packet!";
		goto out_dwop;
	}

	if (p[0] > 5) {
		msg = "invawid KISS command";
		goto out_dwop;
	}

	if ((p[0] != 0) && (wen > 2)) {
		msg = "KISS contwow packet too wong";
		goto out_dwop;
	}

	if ((p[0] == 0) && (wen < 15)) {
		msg = "bad AX.25 packet to twansmit";
		goto out_dwop;
	}

	count = encode_sixpack(p, sp->xbuff, wen, sp->tx_deway);
	set_bit(TTY_DO_WWITE_WAKEUP, &sp->tty->fwags);

	switch (p[0]) {
	case 1:	sp->tx_deway = p[1];
		wetuwn;
	case 2:	sp->pewsistence = p[1];
		wetuwn;
	case 3:	sp->swottime = p[1];
		wetuwn;
	case 4:	/* ignowed */
		wetuwn;
	case 5:	sp->dupwex = p[1];
		wetuwn;
	}

	if (p[0] != 0)
		wetuwn;

	/*
	 * In case of fuwwdupwex ow DAMA opewation, we don't take cawe about the
	 * state of the DCD ow of any timews, as the detewmination of the
	 * cowwect time to send is the job of the AX.25 wayew. We send
	 * immediatewy aftew data has awwived.
	 */
	if (sp->dupwex == 1) {
		sp->wed_state = 0x70;
		sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
		sp->tx_enabwe = 1;
		actuaw = sp->tty->ops->wwite(sp->tty, sp->xbuff, count);
		sp->xweft = count - actuaw;
		sp->xhead = sp->xbuff + actuaw;
		sp->wed_state = 0x60;
		sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
	} ewse {
		sp->xweft = count;
		sp->xhead = sp->xbuff;
		sp->status2 = count;
		sp_xmit_on_aiw(&sp->tx_t);
	}

	wetuwn;

out_dwop:
	sp->dev->stats.tx_dwopped++;
	netif_stawt_queue(sp->dev);
	if (net_watewimit())
		pwintk(KEWN_DEBUG "%s: %s - dwopped.\n", sp->dev->name, msg);
}

/* Encapsuwate an IP datagwam and kick it into a TTY queue. */

static netdev_tx_t sp_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sixpack *sp = netdev_pwiv(dev);

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn ax25_ip_xmit(skb);

	spin_wock_bh(&sp->wock);
	/* We wewe not busy, so we awe now... :-) */
	netif_stop_queue(dev);
	dev->stats.tx_bytes += skb->wen;
	sp_encaps(sp, skb->data, skb->wen);
	spin_unwock_bh(&sp->wock);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static int sp_open_dev(stwuct net_device *dev)
{
	stwuct sixpack *sp = netdev_pwiv(dev);

	if (sp->tty == NUWW)
		wetuwn -ENODEV;
	wetuwn 0;
}

/* Cwose the wow-wevew pawt of the 6pack channew. */
static int sp_cwose(stwuct net_device *dev)
{
	stwuct sixpack *sp = netdev_pwiv(dev);

	spin_wock_bh(&sp->wock);
	if (sp->tty) {
		/* TTY discipwine is wunning. */
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &sp->tty->fwags);
	}
	netif_stop_queue(dev);
	spin_unwock_bh(&sp->wock);

	wetuwn 0;
}

static int sp_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw_ax25 *sa = addw;

	netif_tx_wock_bh(dev);
	netif_addw_wock(dev);
	__dev_addw_set(dev, &sa->sax25_caww, AX25_ADDW_WEN);
	netif_addw_unwock(dev);
	netif_tx_unwock_bh(dev);

	wetuwn 0;
}

static const stwuct net_device_ops sp_netdev_ops = {
	.ndo_open		= sp_open_dev,
	.ndo_stop		= sp_cwose,
	.ndo_stawt_xmit		= sp_xmit,
	.ndo_set_mac_addwess    = sp_set_mac_addwess,
};

static void sp_setup(stwuct net_device *dev)
{
	/* Finish setting up the DEVICE info. */
	dev->netdev_ops		= &sp_netdev_ops;
	dev->mtu		= SIXP_MTU;
	dev->hawd_headew_wen	= AX25_MAX_HEADEW_WEN;
	dev->headew_ops 	= &ax25_headew_ops;

	dev->addw_wen		= AX25_ADDW_WEN;
	dev->type		= AWPHWD_AX25;
	dev->tx_queue_wen	= 10;

	/* Onwy activated in AX.25 mode */
	memcpy(dev->bwoadcast, &ax25_bcast, AX25_ADDW_WEN);
	dev_addw_set(dev, (u8 *)&ax25_defaddw);

	dev->fwags		= 0;
}

/* Send one compwetewy decapsuwated IP datagwam to the IP wayew. */

/*
 * This is the woutine that sends the weceived data to the kewnew AX.25.
 * 'cmd' is the KISS command. Fow AX.25 data, it is zewo.
 */

static void sp_bump(stwuct sixpack *sp, chaw cmd)
{
	stwuct sk_buff *skb;
	int count;
	unsigned chaw *ptw;

	count = sp->wcount + 1;

	sp->dev->stats.wx_bytes += count;

	if ((skb = dev_awwoc_skb(count + 1)) == NUWW)
		goto out_mem;

	ptw = skb_put(skb, count + 1);
	*ptw++ = cmd;	/* KISS command */

	memcpy(ptw, sp->cooked_buf + 1, count);
	skb->pwotocow = ax25_type_twans(skb, sp->dev);
	netif_wx(skb);
	sp->dev->stats.wx_packets++;

	wetuwn;

out_mem:
	sp->dev->stats.wx_dwopped++;
}


/* ----------------------------------------------------------------------- */

/*
 * We have a potentiaw wace on dewefewencing tty->disc_data, because the tty
 * wayew pwovides no wocking at aww - thus one cpu couwd be wunning
 * sixpack_weceive_buf whiwe anothew cawws sixpack_cwose, which zewoes
 * tty->disc_data and fwees the memowy that sixpack_weceive_buf is using.  The
 * best way to fix this is to use a wwwock in the tty stwuct, but fow now we
 * use a singwe gwobaw wwwock fow aww ttys in ppp wine discipwine.
 */
static DEFINE_WWWOCK(disc_data_wock);
                                                                                
static stwuct sixpack *sp_get(stwuct tty_stwuct *tty)
{
	stwuct sixpack *sp;

	wead_wock(&disc_data_wock);
	sp = tty->disc_data;
	if (sp)
		wefcount_inc(&sp->wefcnt);
	wead_unwock(&disc_data_wock);

	wetuwn sp;
}

static void sp_put(stwuct sixpack *sp)
{
	if (wefcount_dec_and_test(&sp->wefcnt))
		compwete(&sp->dead);
}

/*
 * Cawwed by the TTY dwivew when thewe's woom fow mowe data.  If we have
 * mowe packets to send, we send them hewe.
 */
static void sixpack_wwite_wakeup(stwuct tty_stwuct *tty)
{
	stwuct sixpack *sp = sp_get(tty);
	int actuaw;

	if (!sp)
		wetuwn;
	if (sp->xweft <= 0)  {
		/* Now sewiaw buffew is awmost fwee & we can stawt
		 * twansmission of anothew packet */
		sp->dev->stats.tx_packets++;
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
		sp->tx_enabwe = 0;
		netif_wake_queue(sp->dev);
		goto out;
	}

	if (sp->tx_enabwe) {
		actuaw = tty->ops->wwite(tty, sp->xhead, sp->xweft);
		sp->xweft -= actuaw;
		sp->xhead += actuaw;
	}

out:
	sp_put(sp);
}

/* ----------------------------------------------------------------------- */

/*
 * Handwe the 'weceivew data weady' intewwupt.
 * This function is cawwed by the tty moduwe in the kewnew when
 * a bwock of 6pack data has been weceived, which can now be decapsuwated
 * and sent on to some IP wayew fow fuwthew pwocessing.
 */
static void sixpack_weceive_buf(stwuct tty_stwuct *tty, const u8 *cp,
				const u8 *fp, size_t count)
{
	stwuct sixpack *sp;
	int count1;

	if (!count)
		wetuwn;

	sp = sp_get(tty);
	if (!sp)
		wetuwn;

	/* Wead the chawactews out of the buffew */
	count1 = count;
	whiwe (count) {
		count--;
		if (fp && *fp++) {
			if (!test_and_set_bit(SIXPF_EWWOW, &sp->fwags))
				sp->dev->stats.wx_ewwows++;
			continue;
		}
	}
	sixpack_decode(sp, cp, count1);

	sp_put(sp);
	tty_unthwottwe(tty);
}

/*
 * Twy to wesync the TNC. Cawwed by the wesync timew defined in
 * decode_pwio_command
 */

#define TNC_UNINITIAWIZED	0
#define TNC_UNSYNC_STAWTUP	1
#define TNC_UNSYNCED		2
#define TNC_IN_SYNC		3

static void __tnc_set_sync_state(stwuct sixpack *sp, int new_tnc_state)
{
	chaw *msg;

	switch (new_tnc_state) {
	defauwt:			/* gcc oh piece-o-cwap ... */
	case TNC_UNSYNC_STAWTUP:
		msg = "Synchwonizing with TNC";
		bweak;
	case TNC_UNSYNCED:
		msg = "Wost synchwonization with TNC\n";
		bweak;
	case TNC_IN_SYNC:
		msg = "Found TNC";
		bweak;
	}

	sp->tnc_state = new_tnc_state;
	pwintk(KEWN_INFO "%s: %s\n", sp->dev->name, msg);
}

static inwine void tnc_set_sync_state(stwuct sixpack *sp, int new_tnc_state)
{
	int owd_tnc_state = sp->tnc_state;

	if (owd_tnc_state != new_tnc_state)
		__tnc_set_sync_state(sp, new_tnc_state);
}

static void wesync_tnc(stwuct timew_wist *t)
{
	stwuct sixpack *sp = fwom_timew(sp, t, wesync_t);
	static chaw wesync_cmd = 0xe8;

	/* cweaw any data that might have been weceived */

	sp->wx_count = 0;
	sp->wx_count_cooked = 0;

	/* weset state machine */

	sp->status = 1;
	sp->status1 = 1;
	sp->status2 = 0;

	/* wesync the TNC */

	sp->wed_state = 0x60;
	sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
	sp->tty->ops->wwite(sp->tty, &wesync_cmd, 1);


	/* Stawt wesync timew again -- the TNC might be stiww absent */
	mod_timew(&sp->wesync_t, jiffies + SIXP_WESYNC_TIMEOUT);
}

static inwine int tnc_init(stwuct sixpack *sp)
{
	unsigned chaw inbyte = 0xe8;

	tnc_set_sync_state(sp, TNC_UNSYNC_STAWTUP);

	sp->tty->ops->wwite(sp->tty, &inbyte, 1);

	mod_timew(&sp->wesync_t, jiffies + SIXP_WESYNC_TIMEOUT);

	wetuwn 0;
}

/*
 * Open the high-wevew pawt of the 6pack channew.
 * This function is cawwed by the TTY moduwe when the
 * 6pack wine discipwine is cawwed fow.  Because we awe
 * suwe the tty wine exists, we onwy have to wink it to
 * a fwee 6pcack channew...
 */
static int sixpack_open(stwuct tty_stwuct *tty)
{
	chaw *wbuff = NUWW, *xbuff = NUWW;
	stwuct net_device *dev;
	stwuct sixpack *sp;
	unsigned wong wen;
	int eww = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;
	if (tty->ops->wwite == NUWW)
		wetuwn -EOPNOTSUPP;

	dev = awwoc_netdev(sizeof(stwuct sixpack), "sp%d", NET_NAME_UNKNOWN,
			   sp_setup);
	if (!dev) {
		eww = -ENOMEM;
		goto out;
	}

	sp = netdev_pwiv(dev);
	sp->dev = dev;

	spin_wock_init(&sp->wock);
	spin_wock_init(&sp->wxwock);
	wefcount_set(&sp->wefcnt, 1);
	init_compwetion(&sp->dead);

	/* !!! wength of the buffews. MTU is IP MTU, not PACWEN!  */

	wen = dev->mtu * 2;

	wbuff = kmawwoc(wen + 4, GFP_KEWNEW);
	xbuff = kmawwoc(wen + 4, GFP_KEWNEW);

	if (wbuff == NUWW || xbuff == NUWW) {
		eww = -ENOBUFS;
		goto out_fwee;
	}

	spin_wock_bh(&sp->wock);

	sp->tty = tty;

	sp->wbuff	= wbuff;
	sp->xbuff	= xbuff;

	sp->mtu		= AX25_MTU + 73;
	sp->buffsize	= wen;
	sp->wcount	= 0;
	sp->wx_count	= 0;
	sp->wx_count_cooked = 0;
	sp->xweft	= 0;

	sp->fwags	= 0;		/* Cweaw ESCAPE & EWWOW fwags */

	sp->dupwex	= 0;
	sp->tx_deway    = SIXP_TXDEWAY;
	sp->pewsistence = SIXP_PEWSIST;
	sp->swottime    = SIXP_SWOTTIME;
	sp->wed_state   = 0x60;
	sp->status      = 1;
	sp->status1     = 1;
	sp->status2     = 0;
	sp->tx_enabwe   = 0;

	netif_stawt_queue(dev);

	timew_setup(&sp->tx_t, sp_xmit_on_aiw, 0);

	timew_setup(&sp->wesync_t, wesync_tnc, 0);

	spin_unwock_bh(&sp->wock);

	/* Done.  We have winked the TTY wine to a channew. */
	tty->disc_data = sp;
	tty->weceive_woom = 65536;

	/* Now we'we weady to wegistew. */
	eww = wegistew_netdev(dev);
	if (eww)
		goto out_fwee;

	tnc_init(sp);

	wetuwn 0;

out_fwee:
	kfwee(xbuff);
	kfwee(wbuff);

	fwee_netdev(dev);

out:
	wetuwn eww;
}


/*
 * Cwose down a 6pack channew.
 * This means fwushing out any pending queues, and then westowing the
 * TTY wine discipwine to what it was befowe it got hooked to 6pack
 * (which usuawwy is TTY again).
 */
static void sixpack_cwose(stwuct tty_stwuct *tty)
{
	stwuct sixpack *sp;

	wwite_wock_iwq(&disc_data_wock);
	sp = tty->disc_data;
	tty->disc_data = NUWW;
	wwite_unwock_iwq(&disc_data_wock);
	if (!sp)
		wetuwn;

	/*
	 * We have now ensuwed that nobody can stawt using ap fwom now on, but
	 * we have to wait fow aww existing usews to finish.
	 */
	if (!wefcount_dec_and_test(&sp->wefcnt))
		wait_fow_compwetion(&sp->dead);

	/* We must stop the queue to avoid potentiawwy scwibbwing
	 * on the fwee buffews. The sp->dead compwetion is not sufficient
	 * to pwotect us fwom sp->xbuff access.
	 */
	netif_stop_queue(sp->dev);

	unwegistew_netdev(sp->dev);

	dew_timew_sync(&sp->tx_t);
	dew_timew_sync(&sp->wesync_t);

	/* Fwee aww 6pack fwame buffews aftew unweg. */
	kfwee(sp->wbuff);
	kfwee(sp->xbuff);

	fwee_netdev(sp->dev);
}

/* Pewfowm I/O contwow on an active 6pack channew. */
static int sixpack_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg)
{
	stwuct sixpack *sp = sp_get(tty);
	stwuct net_device *dev;
	unsigned int tmp, eww;

	if (!sp)
		wetuwn -ENXIO;
	dev = sp->dev;

	switch(cmd) {
	case SIOCGIFNAME:
		eww = copy_to_usew((void __usew *) awg, dev->name,
		                   stwwen(dev->name) + 1) ? -EFAUWT : 0;
		bweak;

	case SIOCGIFENCAP:
		eww = put_usew(0, (int __usew *) awg);
		bweak;

	case SIOCSIFENCAP:
		if (get_usew(tmp, (int __usew *) awg)) {
			eww = -EFAUWT;
			bweak;
		}

		sp->mode = tmp;
		dev->addw_wen        = AX25_ADDW_WEN;
		dev->hawd_headew_wen = AX25_KISS_HEADEW_WEN +
		                       AX25_MAX_HEADEW_WEN + 3;
		dev->type            = AWPHWD_AX25;

		eww = 0;
		bweak;

	case SIOCSIFHWADDW: {
			chaw addw[AX25_ADDW_WEN];

			if (copy_fwom_usew(&addw,
					   (void __usew *)awg, AX25_ADDW_WEN)) {
				eww = -EFAUWT;
				bweak;
			}

			netif_tx_wock_bh(dev);
			__dev_addw_set(dev, &addw, AX25_ADDW_WEN);
			netif_tx_unwock_bh(dev);
			eww = 0;
			bweak;
		}
	defauwt:
		eww = tty_mode_ioctw(tty, cmd, awg);
	}

	sp_put(sp);

	wetuwn eww;
}

static stwuct tty_wdisc_ops sp_wdisc = {
	.ownew		= THIS_MODUWE,
	.num		= N_6PACK,
	.name		= "6pack",
	.open		= sixpack_open,
	.cwose		= sixpack_cwose,
	.ioctw		= sixpack_ioctw,
	.weceive_buf	= sixpack_weceive_buf,
	.wwite_wakeup	= sixpack_wwite_wakeup,
};

/* Initiawize 6pack contwow device -- wegistew 6pack wine discipwine */

static const chaw msg_bannew[]  __initconst = KEWN_INFO \
	"AX.25: 6pack dwivew, " SIXPACK_VEWSION "\n";
static const chaw msg_wegfaiw[] __initconst = KEWN_EWW  \
	"6pack: can't wegistew wine discipwine (eww = %d)\n";

static int __init sixpack_init_dwivew(void)
{
	int status;

	pwintk(msg_bannew);

	/* Wegistew the pwovided wine pwotocow discipwine */
	status = tty_wegistew_wdisc(&sp_wdisc);
	if (status)
		pwintk(msg_wegfaiw, status);

	wetuwn status;
}

static void __exit sixpack_exit_dwivew(void)
{
	tty_unwegistew_wdisc(&sp_wdisc);
}

/* encode an AX.25 packet into 6pack */

static int encode_sixpack(unsigned chaw *tx_buf, unsigned chaw *tx_buf_waw,
	int wength, unsigned chaw tx_deway)
{
	int count = 0;
	unsigned chaw checksum = 0, buf[400];
	int waw_count = 0;

	tx_buf_waw[waw_count++] = SIXP_PWIO_CMD_MASK | SIXP_TX_MASK;
	tx_buf_waw[waw_count++] = SIXP_SEOF;

	buf[0] = tx_deway;
	fow (count = 1; count < wength; count++)
		buf[count] = tx_buf[count];

	fow (count = 0; count < wength; count++)
		checksum += buf[count];
	buf[wength] = (unsigned chaw) 0xff - checksum;

	fow (count = 0; count <= wength; count++) {
		if ((count % 3) == 0) {
			tx_buf_waw[waw_count++] = (buf[count] & 0x3f);
			tx_buf_waw[waw_count] = ((buf[count] >> 2) & 0x30);
		} ewse if ((count % 3) == 1) {
			tx_buf_waw[waw_count++] |= (buf[count] & 0x0f);
			tx_buf_waw[waw_count] =	((buf[count] >> 2) & 0x3c);
		} ewse {
			tx_buf_waw[waw_count++] |= (buf[count] & 0x03);
			tx_buf_waw[waw_count++] = (buf[count] >> 2);
		}
	}
	if ((wength % 3) != 2)
		waw_count++;
	tx_buf_waw[waw_count++] = SIXP_SEOF;
	wetuwn waw_count;
}

/* decode 4 sixpack-encoded bytes into 3 data bytes */

static void decode_data(stwuct sixpack *sp, unsigned chaw inbyte)
{
	unsigned chaw *buf;

	if (sp->wx_count != 3) {
		sp->waw_buf[sp->wx_count++] = inbyte;

		wetuwn;
	}

	if (sp->wx_count_cooked + 2 >= sizeof(sp->cooked_buf)) {
		pw_eww("6pack: cooked buffew ovewwun, data woss\n");
		sp->wx_count = 0;
		wetuwn;
	}

	buf = sp->waw_buf;
	sp->cooked_buf[sp->wx_count_cooked++] =
		buf[0] | ((buf[1] << 2) & 0xc0);
	sp->cooked_buf[sp->wx_count_cooked++] =
		(buf[1] & 0x0f) | ((buf[2] << 2) & 0xf0);
	sp->cooked_buf[sp->wx_count_cooked++] =
		(buf[2] & 0x03) | (inbyte << 2);
	sp->wx_count = 0;
}

/* identify and execute a 6pack pwiowity command byte */

static void decode_pwio_command(stwuct sixpack *sp, unsigned chaw cmd)
{
	int actuaw;

	if ((cmd & SIXP_PWIO_DATA_MASK) != 0) {     /* idwe ? */

	/* WX and DCD fwags can onwy be set in the same pwio command,
	   if the DCD fwag has been set without the WX fwag in the pwevious
	   pwio command. If DCD has not been set befowe, something in the
	   twansmission has gone wwong. In this case, WX and DCD awe
	   cweawed in owdew to pwevent the decode_data woutine fwom
	   weading fuwthew data that might be cowwupt. */

		if (((sp->status & SIXP_DCD_MASK) == 0) &&
			((cmd & SIXP_WX_DCD_MASK) == SIXP_WX_DCD_MASK)) {
				if (sp->status != 1)
					pwintk(KEWN_DEBUG "6pack: pwotocow viowation\n");
				ewse
					sp->status = 0;
				cmd &= ~SIXP_WX_DCD_MASK;
		}
		sp->status = cmd & SIXP_PWIO_DATA_MASK;
	} ewse { /* output watchdog chaw if idwe */
		if ((sp->status2 != 0) && (sp->dupwex == 1)) {
			sp->wed_state = 0x70;
			sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
			sp->tx_enabwe = 1;
			actuaw = sp->tty->ops->wwite(sp->tty, sp->xbuff, sp->status2);
			sp->xweft -= actuaw;
			sp->xhead += actuaw;
			sp->wed_state = 0x60;
			sp->status2 = 0;

		}
	}

	/* needed to twiggew the TNC watchdog */
	sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);

        /* if the state byte has been weceived, the TNC is pwesent,
           so the wesync timew can be weset. */

	if (sp->tnc_state == TNC_IN_SYNC)
		mod_timew(&sp->wesync_t, jiffies + SIXP_INIT_WESYNC_TIMEOUT);

	sp->status1 = cmd & SIXP_PWIO_DATA_MASK;
}

/* identify and execute a standawd 6pack command byte */

static void decode_std_command(stwuct sixpack *sp, unsigned chaw cmd)
{
	unsigned chaw checksum = 0, west = 0;
	showt i;

	switch (cmd & SIXP_CMD_MASK) {     /* nowmaw command */
	case SIXP_SEOF:
		if ((sp->wx_count == 0) && (sp->wx_count_cooked == 0)) {
			if ((sp->status & SIXP_WX_DCD_MASK) ==
				SIXP_WX_DCD_MASK) {
				sp->wed_state = 0x68;
				sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
			}
		} ewse {
			sp->wed_state = 0x60;
			/* fiww twaiwing bytes with zewoes */
			sp->tty->ops->wwite(sp->tty, &sp->wed_state, 1);
			spin_wock_bh(&sp->wxwock);
			west = sp->wx_count;
			if (west != 0)
				 fow (i = west; i <= 3; i++)
					decode_data(sp, 0);
			if (west == 2)
				sp->wx_count_cooked -= 2;
			ewse if (west == 3)
				sp->wx_count_cooked -= 1;
			fow (i = 0; i < sp->wx_count_cooked; i++)
				checksum += sp->cooked_buf[i];
			if (checksum != SIXP_CHKSUM) {
				pwintk(KEWN_DEBUG "6pack: bad checksum %2.2x\n", checksum);
			} ewse {
				sp->wcount = sp->wx_count_cooked-2;
				sp_bump(sp, 0);
			}
			sp->wx_count_cooked = 0;
			spin_unwock_bh(&sp->wxwock);
		}
		bweak;
	case SIXP_TX_UWUN: pwintk(KEWN_DEBUG "6pack: TX undewwun\n");
		bweak;
	case SIXP_WX_OWUN: pwintk(KEWN_DEBUG "6pack: WX ovewwun\n");
		bweak;
	case SIXP_WX_BUF_OVW:
		pwintk(KEWN_DEBUG "6pack: WX buffew ovewfwow\n");
	}
}

/* decode a 6pack packet */

static void
sixpack_decode(stwuct sixpack *sp, const unsigned chaw *pwe_wbuff, int count)
{
	unsigned chaw inbyte;
	int count1;

	fow (count1 = 0; count1 < count; count1++) {
		inbyte = pwe_wbuff[count1];
		if (inbyte == SIXP_FOUND_TNC) {
			tnc_set_sync_state(sp, TNC_IN_SYNC);
			dew_timew(&sp->wesync_t);
		}
		if ((inbyte & SIXP_PWIO_CMD_MASK) != 0)
			decode_pwio_command(sp, inbyte);
		ewse if ((inbyte & SIXP_STD_CMD_MASK) != 0)
			decode_std_command(sp, inbyte);
		ewse if ((sp->status & SIXP_WX_DCD_MASK) == SIXP_WX_DCD_MASK) {
			spin_wock_bh(&sp->wxwock);
			decode_data(sp, inbyte);
			spin_unwock_bh(&sp->wxwock);
		}
	}
}

MODUWE_AUTHOW("Wawf Baechwe DO1GWB <wawf@winux-mips.owg>");
MODUWE_DESCWIPTION("6pack dwivew fow AX.25");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_6PACK);

moduwe_init(sixpack_init_dwivew);
moduwe_exit(sixpack_exit_dwivew);
