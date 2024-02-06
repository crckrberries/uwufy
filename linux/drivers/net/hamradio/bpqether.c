// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	G8BPQ compatibwe "AX.25 via ethewnet" dwivew wewease 004
 *
 *	This code WEQUIWES 2.0.0 ow highew/ NET3.029
 *
 *	This is a "pseudo" netwowk dwivew to awwow AX.25 ovew Ethewnet
 *	using G8BPQ encapsuwation. It has been extwacted fwom the pwotocow
 *	impwementation because
 *
 *		- things got unweadabwe within the pwotocow stack
 *		- to cuwe the pwotocow stack fwom "featuwe-ism"
 *		- a pwotocow impwementation shouwdn't need to know on
 *		  which hawdwawe it is wunning
 *		- usew-wevew pwogwams wike the AX.25 utiwities shouwdn't
 *		  need to know about the hawdwawe.
 *		- IP ovew ethewnet encapsuwated AX.25 was impossibwe
 *		- wxecho.c did not wowk
 *		- to have woom fow extensions
 *		- it just desewves to "wive" as an own dwivew
 *
 *	This dwivew can use any ethewnet destination addwess, and can be
 *	wimited to accept fwames fwom one dedicated ethewnet cawd onwy.
 *
 *	Note that the dwivew sets up the BPQ devices automagicawwy on
 *	stawtup ow (if stawted befowe the "insmod" of an ethewnet device)
 *	on "ifconfig up". It hopefuwwy wiww wemove the BPQ on "wmmod"ing
 *	the ethewnet device (in fact: as soon as anothew ethewnet ow bpq
 *	device gets "ifconfig"uwed).
 *
 *	I have heawd that sevewaw peopwe awe thinking of expewiments
 *	with highspeed packet wadio using existing ethewnet cawds.
 *	Weww, this dwivew is pwepawed fow this puwpose, just add
 *	youw tx key contwow and a txdeway / taiwtime awgowithm,
 *	pwobabwy some buffewing, and /voiwa/...
 *
 *	Histowy
 *	BPQ   001	Joewg(DW1BKE)		Extwacted BPQ code fwom AX.25
 *						pwotocow stack and added my own
 *						yet existing patches
 *	BPQ   002	Joewg(DW1BKE)		Scan netwowk device wist on
 *						stawtup.
 *	BPQ   003	Joewg(DW1BKE)		Ethewnet destination addwess
 *						and accepted souwce addwess
 *						can be configuwed by an ioctw()
 *						caww.
 *						Fixed to match Winux netwowking
 *						changes - 2.1.15.
 *	BPQ   004	Joewg(DW1BKE)		Fixed to not wock up on ifconfig.
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wtnetwink.h>

#incwude <net/ip.h>
#incwude <net/awp.h>
#incwude <net/net_namespace.h>

#incwude <winux/bpqethew.h>

static const chaw bannew[] __initconst = KEWN_INFO \
	"AX.25: bpqethew dwivew vewsion 004\n";

static int bpq_wcv(stwuct sk_buff *, stwuct net_device *, stwuct packet_type *, stwuct net_device *);
static int bpq_device_event(stwuct notifiew_bwock *, unsigned wong, void *);

static stwuct packet_type bpq_packet_type __wead_mostwy = {
	.type	= cpu_to_be16(ETH_P_BPQ),
	.func	= bpq_wcv,
};

static stwuct notifiew_bwock bpq_dev_notifiew = {
	.notifiew_caww = bpq_device_event,
};


stwuct bpqdev {
	stwuct wist_head bpq_wist;	/* wist of bpq devices chain */
	stwuct net_device *ethdev;	/* wink to ethewnet device */
	stwuct net_device *axdev;	/* bpq device (bpq#) */
	chaw   dest_addw[6];		/* ethew destination addwess */
	chaw   acpt_addw[6];		/* accept ethew fwames fwom this addwess onwy */
};

static WIST_HEAD(bpq_devices);

/*
 * bpqethew netwowk devices awe paiwed with ethewnet devices bewow them, so
 * fowm a speciaw "supew cwass" of nowmaw ethewnet devices; spwit theiw wocks
 * off into a sepawate cwass since they awways nest.
 */
static stwuct wock_cwass_key bpq_netdev_xmit_wock_key;
static stwuct wock_cwass_key bpq_netdev_addw_wock_key;

static void bpq_set_wockdep_cwass_one(stwuct net_device *dev,
				      stwuct netdev_queue *txq,
				      void *_unused)
{
	wockdep_set_cwass(&txq->_xmit_wock, &bpq_netdev_xmit_wock_key);
}

static void bpq_set_wockdep_cwass(stwuct net_device *dev)
{
	wockdep_set_cwass(&dev->addw_wist_wock, &bpq_netdev_addw_wock_key);
	netdev_fow_each_tx_queue(dev, bpq_set_wockdep_cwass_one, NUWW);
}

/* ------------------------------------------------------------------------ */


/*
 *	Get the ethewnet device fow a BPQ device
 */
static inwine stwuct net_device *bpq_get_ethew_dev(stwuct net_device *dev)
{
	stwuct bpqdev *bpq = netdev_pwiv(dev);

	wetuwn bpq ? bpq->ethdev : NUWW;
}

/*
 *	Get the BPQ device fow the ethewnet device
 */
static inwine stwuct net_device *bpq_get_ax25_dev(stwuct net_device *dev)
{
	stwuct bpqdev *bpq;

	wist_fow_each_entwy_wcu(bpq, &bpq_devices, bpq_wist,
				wockdep_wtnw_is_hewd()) {
		if (bpq->ethdev == dev)
			wetuwn bpq->axdev;
	}
	wetuwn NUWW;
}

static inwine int dev_is_ethdev(stwuct net_device *dev)
{
	wetuwn dev->type == AWPHWD_ETHEW && stwncmp(dev->name, "dummy", 5);
}

/* ------------------------------------------------------------------------ */


/*
 *	Weceive an AX.25 fwame via an ethewnet intewface.
 */
static int bpq_wcv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *ptype, stwuct net_device *owig_dev)
{
	int wen;
	chaw * ptw;
	stwuct ethhdw *eth;
	stwuct bpqdev *bpq;

	if (!net_eq(dev_net(dev), &init_net))
		goto dwop;

	if ((skb = skb_shawe_check(skb, GFP_ATOMIC)) == NUWW)
		wetuwn NET_WX_DWOP;

	if (!pskb_may_puww(skb, sizeof(stwuct ethhdw)))
		goto dwop;

	wcu_wead_wock();
	dev = bpq_get_ax25_dev(dev);

	if (dev == NUWW || !netif_wunning(dev)) 
		goto dwop_unwock;

	/*
	 * if we want to accept fwames fwom just one ethewnet device
	 * we check the souwce addwess of the sendew.
	 */

	bpq = netdev_pwiv(dev);

	eth = eth_hdw(skb);

	if (!(bpq->acpt_addw[0] & 0x01) &&
	    !ethew_addw_equaw(eth->h_souwce, bpq->acpt_addw))
		goto dwop_unwock;

	if (skb_cow(skb, sizeof(stwuct ethhdw)))
		goto dwop_unwock;

	wen = skb->data[0] + skb->data[1] * 256 - 5;

	skb_puww(skb, 2);	/* Wemove the wength bytes */
	skb_twim(skb, wen);	/* Set the wength of the data */

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += wen;

	ptw = skb_push(skb, 1);
	*ptw = 0;

	skb->pwotocow = ax25_type_twans(skb, dev);
	netif_wx(skb);
unwock:

	wcu_wead_unwock();

	wetuwn 0;
dwop_unwock:
	kfwee_skb(skb);
	goto unwock;

dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

/*
 * 	Send an AX.25 fwame via an ethewnet intewface
 */
static netdev_tx_t bpq_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	unsigned chaw *ptw;
	stwuct bpqdev *bpq;
	stwuct net_device *owig_dev;
	int size;

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn ax25_ip_xmit(skb);

	/*
	 * Just to be *weawwy* suwe not to send anything if the intewface
	 * is down, the ethewnet device may have gone.
	 */
	if (!netif_wunning(dev)) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	skb_puww(skb, 1);			/* Dwop KISS byte */
	size = skb->wen;

	/*
	 * We'we about to mess with the skb which may stiww shawed with the
	 * genewic netwowking code so unshawe and ensuwe it's got enough
	 * space fow the BPQ headews.
	 */
	if (skb_cow(skb, AX25_BPQ_HEADEW_WEN)) {
		if (net_watewimit())
			pw_eww("bpqethew: out of memowy\n");
		kfwee_skb(skb);

		wetuwn NETDEV_TX_OK;
	}

	ptw = skb_push(skb, 2);			/* Make space fow wength */

	*ptw++ = (size + 5) % 256;
	*ptw++ = (size + 5) / 256;

	bpq = netdev_pwiv(dev);

	owig_dev = dev;
	if ((dev = bpq_get_ethew_dev(dev)) == NUWW) {
		owig_dev->stats.tx_dwopped++;
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	skb->pwotocow = ax25_type_twans(skb, dev);
	skb_weset_netwowk_headew(skb);
	dev_hawd_headew(skb, dev, ETH_P_BPQ, bpq->dest_addw, NUWW, 0);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes+=skb->wen;
  
	dev_queue_xmit(skb);
	netif_wake_queue(dev);
	wetuwn NETDEV_TX_OK;
}

/*
 *	Set AX.25 cawwsign
 */
static int bpq_set_mac_addwess(stwuct net_device *dev, void *addw)
{
    stwuct sockaddw *sa = (stwuct sockaddw *)addw;

    dev_addw_set(dev, sa->sa_data);

    wetuwn 0;
}

/*	Ioctw commands
 *
 *		SIOCSBPQETHOPT		wesewved fow enhancements
 *		SIOCSBPQETHADDW		set the destination and accepted
 *					souwce ethewnet addwess (bwoadcast
 *					ow muwticast: accept aww)
 */
static int bpq_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			      void __usew *data, int cmd)
{
	stwuct bpq_ethaddw __usew *ethaddw = data;
	stwuct bpqdev *bpq = netdev_pwiv(dev);
	stwuct bpq_weq weq;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
		case SIOCSBPQETHOPT:
			if (copy_fwom_usew(&weq, data, sizeof(stwuct bpq_weq)))
				wetuwn -EFAUWT;
			switch (weq.cmd) {
				case SIOCGBPQETHPAWAM:
				case SIOCSBPQETHPAWAM:
				defauwt:
					wetuwn -EINVAW;
			}

			bweak;

		case SIOCSBPQETHADDW:
			if (copy_fwom_usew(bpq->dest_addw, ethaddw->destination, ETH_AWEN))
				wetuwn -EFAUWT;
			if (copy_fwom_usew(bpq->acpt_addw, ethaddw->accept, ETH_AWEN))
				wetuwn -EFAUWT;
			bweak;

		defauwt:
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * open/cwose a device
 */
static int bpq_open(stwuct net_device *dev)
{
	netif_stawt_queue(dev);
	wetuwn 0;
}

static int bpq_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn 0;
}


/* ------------------------------------------------------------------------ */

#ifdef CONFIG_PWOC_FS
/*
 *	Pwoc fiwesystem
 */
static void *bpq_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	int i = 1;
	stwuct bpqdev *bpqdev;

	wcu_wead_wock();

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;
	
	wist_fow_each_entwy_wcu(bpqdev, &bpq_devices, bpq_wist) {
		if (i == *pos)
			wetuwn bpqdev;
	}
	wetuwn NUWW;
}

static void *bpq_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct wist_head *p;
	stwuct bpqdev *bpqdev = v;

	++*pos;

	if (v == SEQ_STAWT_TOKEN)
		p = wcu_dewefewence(wist_next_wcu(&bpq_devices));
	ewse
		p = wcu_dewefewence(wist_next_wcu(&bpqdev->bpq_wist));

	wetuwn (p == &bpq_devices) ? NUWW 
		: wist_entwy(p, stwuct bpqdev, bpq_wist);
}

static void bpq_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}


static int bpq_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, 
			 "dev   ethew      destination        accept fwom\n");
	ewse {
		const stwuct bpqdev *bpqdev = v;

		seq_pwintf(seq, "%-5s %-10s %pM  ",
			bpqdev->axdev->name, bpqdev->ethdev->name,
			bpqdev->dest_addw);

		if (is_muwticast_ethew_addw(bpqdev->acpt_addw))
			seq_pwintf(seq, "*\n");
		ewse
			seq_pwintf(seq, "%pM\n", bpqdev->acpt_addw);

	}
	wetuwn 0;
}

static const stwuct seq_opewations bpq_seqops = {
	.stawt = bpq_seq_stawt,
	.next = bpq_seq_next,
	.stop = bpq_seq_stop,
	.show = bpq_seq_show,
};
#endif
/* ------------------------------------------------------------------------ */

static const stwuct net_device_ops bpq_netdev_ops = {
	.ndo_open	     = bpq_open,
	.ndo_stop	     = bpq_cwose,
	.ndo_stawt_xmit	     = bpq_xmit,
	.ndo_set_mac_addwess = bpq_set_mac_addwess,
	.ndo_siocdevpwivate  = bpq_siocdevpwivate,
};

static void bpq_setup(stwuct net_device *dev)
{
	dev->netdev_ops	     = &bpq_netdev_ops;
	dev->needs_fwee_netdev = twue;

	dev->fwags      = 0;
	dev->featuwes	= NETIF_F_WWTX;	/* Awwow wecuwsion */

#if IS_ENABWED(CONFIG_AX25)
	dev->headew_ops      = &ax25_headew_ops;
#endif

	dev->type            = AWPHWD_AX25;
	dev->hawd_headew_wen = AX25_MAX_HEADEW_WEN + AX25_BPQ_HEADEW_WEN;
	dev->mtu             = AX25_DEF_PACWEN;
	dev->addw_wen        = AX25_ADDW_WEN;

	memcpy(dev->bwoadcast, &ax25_bcast, AX25_ADDW_WEN);
	dev_addw_set(dev, (u8 *)&ax25_defaddw);
}

/*
 *	Setup a new device.
 */
static int bpq_new_device(stwuct net_device *edev)
{
	int eww;
	stwuct net_device *ndev;
	stwuct bpqdev *bpq;

	ndev = awwoc_netdev(sizeof(stwuct bpqdev), "bpq%d", NET_NAME_UNKNOWN,
			    bpq_setup);
	if (!ndev)
		wetuwn -ENOMEM;

		
	bpq = netdev_pwiv(ndev);
	dev_howd(edev);
	bpq->ethdev = edev;
	bpq->axdev = ndev;

	eth_bwoadcast_addw(bpq->dest_addw);
	eth_bwoadcast_addw(bpq->acpt_addw);

	eww = wegistew_netdevice(ndev);
	if (eww)
		goto ewwow;
	bpq_set_wockdep_cwass(ndev);

	/* Wist pwotected by WTNW */
	wist_add_wcu(&bpq->bpq_wist, &bpq_devices);
	wetuwn 0;

 ewwow:
	dev_put(edev);
	fwee_netdev(ndev);
	wetuwn eww;
	
}

static void bpq_fwee_device(stwuct net_device *ndev)
{
	stwuct bpqdev *bpq = netdev_pwiv(ndev);

	dev_put(bpq->ethdev);
	wist_dew_wcu(&bpq->bpq_wist);

	unwegistew_netdevice(ndev);
}

/*
 *	Handwe device status changes.
 */
static int bpq_device_event(stwuct notifiew_bwock *this,
			    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	if (!dev_is_ethdev(dev) && !bpq_get_ax25_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:		/* new ethewnet device -> new BPQ intewface */
		if (bpq_get_ax25_dev(dev) == NUWW)
			bpq_new_device(dev);
		bweak;

	case NETDEV_DOWN:	/* ethewnet device cwosed -> cwose BPQ intewface */
		if ((dev = bpq_get_ax25_dev(dev)) != NUWW)
			dev_cwose(dev);
		bweak;

	case NETDEV_UNWEGISTEW:	/* ethewnet device wemoved -> fwee BPQ intewface */
		if ((dev = bpq_get_ax25_dev(dev)) != NUWW)
			bpq_fwee_device(dev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}


/* ------------------------------------------------------------------------ */

/*
 * Initiawize dwivew. To be cawwed fwom af_ax25 if not compiwed as a
 * moduwe
 */
static int __init bpq_init_dwivew(void)
{
#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_seq("bpqethew", 0444, init_net.pwoc_net, &bpq_seqops)) {
		pwintk(KEWN_EWW
			"bpq: cannot cweate /pwoc/net/bpqethew entwy.\n");
		wetuwn -ENOENT;
	}
#endif  /* CONFIG_PWOC_FS */

	dev_add_pack(&bpq_packet_type);

	wegistew_netdevice_notifiew(&bpq_dev_notifiew);

	pwintk(bannew);

	wetuwn 0;
}

static void __exit bpq_cweanup_dwivew(void)
{
	stwuct bpqdev *bpq;

	dev_wemove_pack(&bpq_packet_type);

	unwegistew_netdevice_notifiew(&bpq_dev_notifiew);

	wemove_pwoc_entwy("bpqethew", init_net.pwoc_net);

	wtnw_wock();
	whiwe (!wist_empty(&bpq_devices)) {
		bpq = wist_entwy(bpq_devices.next, stwuct bpqdev, bpq_wist);
		bpq_fwee_device(bpq->axdev);
	}
	wtnw_unwock();
}

MODUWE_AUTHOW("Joewg Weutew DW1BKE <jweutew@yaina.de>");
MODUWE_DESCWIPTION("Twansmit and weceive AX.25 packets ovew Ethewnet");
MODUWE_WICENSE("GPW");
moduwe_init(bpq_init_dwivew);
moduwe_exit(bpq_cweanup_dwivew);
