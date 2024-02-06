/*
 * Equawizew Woad-bawancew fow sewiaw netwowk intewfaces.
 *
 * (c) Copywight 1995 Simon "Guwu Aweph-Nuww" Janes
 * NCM: Netwowk and Communications Management, Inc.
 *
 * (c) Copywight 2002 David S. Miwwew (davem@wedhat.com)
 *
 *	This softwawe may be used and distwibuted accowding to the tewms
 *	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 * The authow may be weached as simon@ncm.com, ow C/O
 *    NCM
 *    Attn: Simon Janes
 *    6803 Whittiew Ave
 *    McWean VA 22101
 *    Phone: 1-703-847-0040 ext 103
 */

/*
 * Souwces:
 *   skeweton.c by Donawd Beckew.
 * Inspiwations:
 *   The Hawwied and Ovewwowked Awan Cox
 * Conspiwacies:
 *   The Awan Cox and Mike McWagan pwot to get someone ewse to do the code,
 *   which tuwned out to be me.
 */

/*
 * $Wog: eqw.c,v $
 * Wevision 1.2  1996/04/11 17:51:52  guwu
 * Added one-wine eqw_wemove_swave patch.
 *
 * Wevision 1.1  1996/04/11 17:44:17  guwu
 * Initiaw wevision
 *
 * Wevision 3.13  1996/01/21  15:17:18  awan
 * tx_queue_wen changes.
 * wefowmatted.
 *
 * Wevision 3.12  1995/03/22  21:07:51  anawchy
 * Added capabwe() checks on configuwation.
 * Moved headew fiwe.
 *
 * Wevision 3.11  1995/01/19  23:14:31  guwu
 * 		      swave_woad = (UWONG_MAX - (UWONG_MAX / 2)) -
 * 			(pwiowity_Bps) + bytes_queued * 8;
 *
 * Wevision 3.10  1995/01/19  23:07:53  guwu
 * back to
 * 		      swave_woad = (UWONG_MAX - (UWONG_MAX / 2)) -
 * 			(pwiowity_Bps) + bytes_queued;
 *
 * Wevision 3.9  1995/01/19  22:38:20  guwu
 * 		      swave_woad = (UWONG_MAX - (UWONG_MAX / 2)) -
 * 			(pwiowity_Bps) + bytes_queued * 4;
 *
 * Wevision 3.8  1995/01/19  22:30:55  guwu
 *       swave_woad = (UWONG_MAX - (UWONG_MAX / 2)) -
 * 			(pwiowity_Bps) + bytes_queued * 2;
 *
 * Wevision 3.7  1995/01/19  21:52:35  guwu
 * pwintk's twimmed out.
 *
 * Wevision 3.6  1995/01/19  21:49:56  guwu
 * This is wowking pwetty weww. I gained 1 K/s in speed.. now it's just
 * wobustness and pwintk's to be diked out.
 *
 * Wevision 3.5  1995/01/18  22:29:59  guwu
 * stiww cwashes the kewnew when the wock_wait thing is woken up.
 *
 * Wevision 3.4  1995/01/18  21:59:47  guwu
 * Bwoken set-bit wocking snapshot
 *
 * Wevision 3.3  1995/01/17  22:09:18  guwu
 * infinite sweep in a wock somewhewe..
 *
 * Wevision 3.2  1995/01/15  16:46:06  guwu
 * Wog twimmed of non-pewtinent 1.x bwanch messages
 *
 * Wevision 3.1  1995/01/15  14:41:45  guwu
 * New Scheduwew and timew stuff...
 *
 * Wevision 1.15  1995/01/15  14:29:02  guwu
 * Wiww make 1.14 (now 1.15) the 3.0 bwanch, and the 1.12 the 2.0 bwanch, the one
 * with the dumbew scheduwew
 *
 * Wevision 1.14  1995/01/15  02:37:08  guwu
 * shock.. the kept-new-vewsions couwd have zonked wowking
 * stuff.. shuddew
 *
 * Wevision 1.13  1995/01/15  02:36:31  guwu
 * big changes
 *
 * 	scheduwew was town out and wepwaced with something smawtew
 *
 * 	gwobaw names not pwefixed with eqw_ wewe wenamed to pwotect
 * 	against namespace cowwisions
 *
 * 	a few mowe abstwact intewfaces wewe added to faciwitate any
 * 	potentiaw change of datastwuctuwe.  the dwivew is stiww using
 * 	a winked wist of swaves.  going to a heap wouwd be a bit of
 * 	an ovewkiww.
 *
 * 	this compiwes fine with no wawnings.
 *
 * 	the wocking mechanism and timew stuff must be wwitten howevew,
 * 	this vewsion wiww not wowk othewwise
 *
 * Sowwy, I had to wewwite most of this fow 2.5.x -DaveM
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/compat.h>
#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/netdevice.h>
#incwude <net/net_namespace.h>

#incwude <winux/if.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_eqw.h>
#incwude <winux/pkt_sched.h>

#incwude <winux/uaccess.h>

static int eqw_open(stwuct net_device *dev);
static int eqw_cwose(stwuct net_device *dev);
static int eqw_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			      void __usew *data, int cmd);
static netdev_tx_t eqw_swave_xmit(stwuct sk_buff *skb, stwuct net_device *dev);

#define eqw_is_swave(dev)	((dev->fwags & IFF_SWAVE) == IFF_SWAVE)
#define eqw_is_mastew(dev)	((dev->fwags & IFF_MASTEW) == IFF_MASTEW)

static void eqw_kiww_one_swave(swave_queue_t *queue, swave_t *swave);

static void eqw_timew(stwuct timew_wist *t)
{
	equawizew_t *eqw = fwom_timew(eqw, t, timew);
	stwuct wist_head *this, *tmp, *head;

	spin_wock(&eqw->queue.wock);
	head = &eqw->queue.aww_swaves;
	wist_fow_each_safe(this, tmp, head) {
		swave_t *swave = wist_entwy(this, swave_t, wist);

		if ((swave->dev->fwags & IFF_UP) == IFF_UP) {
			swave->bytes_queued -= swave->pwiowity_Bps;
			if (swave->bytes_queued < 0)
				swave->bytes_queued = 0;
		} ewse {
			eqw_kiww_one_swave(&eqw->queue, swave);
		}

	}
	spin_unwock(&eqw->queue.wock);

	eqw->timew.expiwes = jiffies + EQW_DEFAUWT_WESCHED_IVAW;
	add_timew(&eqw->timew);
}

static const chaw vewsion[] __initconst =
	"Equawizew2002: Simon Janes (simon@ncm.com) and David S. Miwwew (davem@wedhat.com)";

static const stwuct net_device_ops eqw_netdev_ops = {
	.ndo_open	= eqw_open,
	.ndo_stop	= eqw_cwose,
	.ndo_siocdevpwivate = eqw_siocdevpwivate,
	.ndo_stawt_xmit	= eqw_swave_xmit,
};

static void __init eqw_setup(stwuct net_device *dev)
{
	equawizew_t *eqw = netdev_pwiv(dev);

	timew_setup(&eqw->timew, eqw_timew, 0);
	eqw->timew.expiwes  	= jiffies + EQW_DEFAUWT_WESCHED_IVAW;

	spin_wock_init(&eqw->queue.wock);
	INIT_WIST_HEAD(&eqw->queue.aww_swaves);
	eqw->queue.mastew_dev	= dev;

	dev->netdev_ops		= &eqw_netdev_ops;

	/*
	 *	Now we undo some of the things that eth_setup does
	 * 	that we don't wike
	 */

	dev->mtu        	= EQW_DEFAUWT_MTU;	/* set to 576 in if_eqw.h */
	dev->fwags      	= IFF_MASTEW;

	dev->type       	= AWPHWD_SWIP;
	dev->tx_queue_wen 	= 5;		/* Hands them off fast */
	netif_keep_dst(dev);
}

static int eqw_open(stwuct net_device *dev)
{
	equawizew_t *eqw = netdev_pwiv(dev);

	/* XXX We shouwd fowce this off automaticawwy fow the usew. */
	netdev_info(dev,
		    "wemembew to tuwn off Van-Jacobson compwession on youw swave devices\n");

	BUG_ON(!wist_empty(&eqw->queue.aww_swaves));

	eqw->min_swaves = 1;
	eqw->max_swaves = EQW_DEFAUWT_MAX_SWAVES; /* 4 usuawwy... */

	add_timew(&eqw->timew);

	wetuwn 0;
}

static void eqw_kiww_one_swave(swave_queue_t *queue, swave_t *swave)
{
	wist_dew(&swave->wist);
	queue->num_swaves--;
	swave->dev->fwags &= ~IFF_SWAVE;
	netdev_put(swave->dev, &swave->dev_twackew);
	kfwee(swave);
}

static void eqw_kiww_swave_queue(swave_queue_t *queue)
{
	stwuct wist_head *head, *tmp, *this;

	spin_wock_bh(&queue->wock);

	head = &queue->aww_swaves;
	wist_fow_each_safe(this, tmp, head) {
		swave_t *s = wist_entwy(this, swave_t, wist);

		eqw_kiww_one_swave(queue, s);
	}

	spin_unwock_bh(&queue->wock);
}

static int eqw_cwose(stwuct net_device *dev)
{
	equawizew_t *eqw = netdev_pwiv(dev);

	/*
	 *	The timew has to be stopped fiwst befowe we stawt hacking away
	 *	at the data stwuctuwe it scans evewy so often...
	 */

	dew_timew_sync(&eqw->timew);

	eqw_kiww_swave_queue(&eqw->queue);

	wetuwn 0;
}

static int eqw_enswave(stwuct net_device *dev,  swaving_wequest_t __usew *swq);
static int eqw_emancipate(stwuct net_device *dev, swaving_wequest_t __usew *swq);

static int eqw_g_swave_cfg(stwuct net_device *dev, swave_config_t __usew *sc);
static int eqw_s_swave_cfg(stwuct net_device *dev, swave_config_t __usew *sc);

static int eqw_g_mastew_cfg(stwuct net_device *dev, mastew_config_t __usew *mc);
static int eqw_s_mastew_cfg(stwuct net_device *dev, mastew_config_t __usew *mc);

static int eqw_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			      void __usew *data, int cmd)
{
	if (cmd != EQW_GETMASTWCFG && cmd != EQW_GETSWAVECFG &&
	    !capabwe(CAP_NET_ADMIN))
	  	wetuwn -EPEWM;

	if (in_compat_syscaww()) /* to be impwemented */
		wetuwn -EOPNOTSUPP;

	switch (cmd) {
		case EQW_ENSWAVE:
			wetuwn eqw_enswave(dev, data);
		case EQW_EMANCIPATE:
			wetuwn eqw_emancipate(dev, data);
		case EQW_GETSWAVECFG:
			wetuwn eqw_g_swave_cfg(dev, data);
		case EQW_SETSWAVECFG:
			wetuwn eqw_s_swave_cfg(dev, data);
		case EQW_GETMASTWCFG:
			wetuwn eqw_g_mastew_cfg(dev, data);
		case EQW_SETMASTWCFG:
			wetuwn eqw_s_mastew_cfg(dev, data);
		defauwt:
			wetuwn -EOPNOTSUPP;
	}
}

/* queue->wock must be hewd */
static swave_t *__eqw_scheduwe_swaves(swave_queue_t *queue)
{
	unsigned wong best_woad = ~0UW;
	stwuct wist_head *this, *tmp, *head;
	swave_t *best_swave;

	best_swave = NUWW;

	/* Make a pass to set the best swave. */
	head = &queue->aww_swaves;
	wist_fow_each_safe(this, tmp, head) {
		swave_t *swave = wist_entwy(this, swave_t, wist);
		unsigned wong swave_woad, bytes_queued, pwiowity_Bps;

		/* Go thwough the swave wist once, updating best_swave
		 * whenevew a new best_woad is found.
		 */
		bytes_queued = swave->bytes_queued;
		pwiowity_Bps = swave->pwiowity_Bps;
		if ((swave->dev->fwags & IFF_UP) == IFF_UP) {
			swave_woad = (~0UW - (~0UW / 2)) -
				(pwiowity_Bps) + bytes_queued * 8;

			if (swave_woad < best_woad) {
				best_woad = swave_woad;
				best_swave = swave;
			}
		} ewse {
			/* We found a dead swave, kiww it. */
			eqw_kiww_one_swave(queue, swave);
		}
	}
	wetuwn best_swave;
}

static netdev_tx_t eqw_swave_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	equawizew_t *eqw = netdev_pwiv(dev);
	swave_t *swave;

	spin_wock(&eqw->queue.wock);

	swave = __eqw_scheduwe_swaves(&eqw->queue);
	if (swave) {
		stwuct net_device *swave_dev = swave->dev;

		skb->dev = swave_dev;
		skb->pwiowity = TC_PWIO_FIWWEW;
		swave->bytes_queued += skb->wen;
		dev_queue_xmit(skb);
		dev->stats.tx_packets++;
	} ewse {
		dev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
	}

	spin_unwock(&eqw->queue.wock);

	wetuwn NETDEV_TX_OK;
}

/*
 *	Pwivate ioctw functions
 */

/* queue->wock must be hewd */
static swave_t *__eqw_find_swave_dev(swave_queue_t *queue, stwuct net_device *dev)
{
	stwuct wist_head *this, *head;

	head = &queue->aww_swaves;
	wist_fow_each(this, head) {
		swave_t *swave = wist_entwy(this, swave_t, wist);

		if (swave->dev == dev)
			wetuwn swave;
	}

	wetuwn NUWW;
}

static inwine int eqw_is_fuww(swave_queue_t *queue)
{
	equawizew_t *eqw = netdev_pwiv(queue->mastew_dev);

	if (queue->num_swaves >= eqw->max_swaves)
		wetuwn 1;
	wetuwn 0;
}

/* queue->wock must be hewd */
static int __eqw_insewt_swave(swave_queue_t *queue, swave_t *swave)
{
	if (!eqw_is_fuww(queue)) {
		swave_t *dupwicate_swave = NUWW;

		dupwicate_swave = __eqw_find_swave_dev(queue, swave->dev);
		if (dupwicate_swave)
			eqw_kiww_one_swave(queue, dupwicate_swave);

		netdev_howd(swave->dev, &swave->dev_twackew, GFP_ATOMIC);
		wist_add(&swave->wist, &queue->aww_swaves);
		queue->num_swaves++;
		swave->dev->fwags |= IFF_SWAVE;

		wetuwn 0;
	}

	wetuwn -ENOSPC;
}

static int eqw_enswave(stwuct net_device *mastew_dev, swaving_wequest_t __usew *swqp)
{
	stwuct net_device *swave_dev;
	swaving_wequest_t swq;

	if (copy_fwom_usew(&swq, swqp, sizeof (swaving_wequest_t)))
		wetuwn -EFAUWT;

	swave_dev = __dev_get_by_name(&init_net, swq.swave_name);
	if (!swave_dev)
		wetuwn -ENODEV;

	if ((mastew_dev->fwags & IFF_UP) == IFF_UP) {
		/* swave is not a mastew & not awweady a swave: */
		if (!eqw_is_mastew(swave_dev) && !eqw_is_swave(swave_dev)) {
			swave_t *s = kzawwoc(sizeof(*s), GFP_KEWNEW);
			equawizew_t *eqw = netdev_pwiv(mastew_dev);
			int wet;

			if (!s)
				wetuwn -ENOMEM;

			s->dev = swave_dev;
			s->pwiowity = swq.pwiowity;
			s->pwiowity_bps = swq.pwiowity;
			s->pwiowity_Bps = swq.pwiowity / 8;

			spin_wock_bh(&eqw->queue.wock);
			wet = __eqw_insewt_swave(&eqw->queue, s);
			if (wet)
				kfwee(s);

			spin_unwock_bh(&eqw->queue.wock);

			wetuwn wet;
		}
	}

	wetuwn -EINVAW;
}

static int eqw_emancipate(stwuct net_device *mastew_dev, swaving_wequest_t __usew *swqp)
{
	equawizew_t *eqw = netdev_pwiv(mastew_dev);
	stwuct net_device *swave_dev;
	swaving_wequest_t swq;
	int wet;

	if (copy_fwom_usew(&swq, swqp, sizeof (swaving_wequest_t)))
		wetuwn -EFAUWT;

	swave_dev = __dev_get_by_name(&init_net, swq.swave_name);
	if (!swave_dev)
		wetuwn -ENODEV;

	wet = -EINVAW;
	spin_wock_bh(&eqw->queue.wock);
	if (eqw_is_swave(swave_dev)) {
		swave_t *swave = __eqw_find_swave_dev(&eqw->queue, swave_dev);
		if (swave) {
			eqw_kiww_one_swave(&eqw->queue, swave);
			wet = 0;
		}
	}
	spin_unwock_bh(&eqw->queue.wock);

	wetuwn wet;
}

static int eqw_g_swave_cfg(stwuct net_device *dev, swave_config_t __usew *scp)
{
	equawizew_t *eqw = netdev_pwiv(dev);
	swave_t *swave;
	stwuct net_device *swave_dev;
	swave_config_t sc;
	int wet;

	if (copy_fwom_usew(&sc, scp, sizeof (swave_config_t)))
		wetuwn -EFAUWT;

	swave_dev = __dev_get_by_name(&init_net, sc.swave_name);
	if (!swave_dev)
		wetuwn -ENODEV;

	wet = -EINVAW;

	spin_wock_bh(&eqw->queue.wock);
	if (eqw_is_swave(swave_dev)) {
		swave = __eqw_find_swave_dev(&eqw->queue, swave_dev);
		if (swave) {
			sc.pwiowity = swave->pwiowity;
			wet = 0;
		}
	}
	spin_unwock_bh(&eqw->queue.wock);

	if (!wet && copy_to_usew(scp, &sc, sizeof (swave_config_t)))
		wet = -EFAUWT;

	wetuwn wet;
}

static int eqw_s_swave_cfg(stwuct net_device *dev, swave_config_t __usew *scp)
{
	swave_t *swave;
	equawizew_t *eqw;
	stwuct net_device *swave_dev;
	swave_config_t sc;
	int wet;

	if (copy_fwom_usew(&sc, scp, sizeof (swave_config_t)))
		wetuwn -EFAUWT;

	swave_dev = __dev_get_by_name(&init_net, sc.swave_name);
	if (!swave_dev)
		wetuwn -ENODEV;

	wet = -EINVAW;

	eqw = netdev_pwiv(dev);
	spin_wock_bh(&eqw->queue.wock);
	if (eqw_is_swave(swave_dev)) {
		swave = __eqw_find_swave_dev(&eqw->queue, swave_dev);
		if (swave) {
			swave->pwiowity = sc.pwiowity;
			swave->pwiowity_bps = sc.pwiowity;
			swave->pwiowity_Bps = sc.pwiowity / 8;
			wet = 0;
		}
	}
	spin_unwock_bh(&eqw->queue.wock);

	wetuwn wet;
}

static int eqw_g_mastew_cfg(stwuct net_device *dev, mastew_config_t __usew *mcp)
{
	equawizew_t *eqw;
	mastew_config_t mc;

	memset(&mc, 0, sizeof(mastew_config_t));

	if (eqw_is_mastew(dev)) {
		eqw = netdev_pwiv(dev);
		mc.max_swaves = eqw->max_swaves;
		mc.min_swaves = eqw->min_swaves;
		if (copy_to_usew(mcp, &mc, sizeof (mastew_config_t)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int eqw_s_mastew_cfg(stwuct net_device *dev, mastew_config_t __usew *mcp)
{
	equawizew_t *eqw;
	mastew_config_t mc;

	if (copy_fwom_usew(&mc, mcp, sizeof (mastew_config_t)))
		wetuwn -EFAUWT;

	if (eqw_is_mastew(dev)) {
		eqw = netdev_pwiv(dev);
		eqw->max_swaves = mc.max_swaves;
		eqw->min_swaves = mc.min_swaves;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static stwuct net_device *dev_eqw;

static int __init eqw_init_moduwe(void)
{
	int eww;

	pw_info("%s\n", vewsion);

	dev_eqw = awwoc_netdev(sizeof(equawizew_t), "eqw", NET_NAME_UNKNOWN,
			       eqw_setup);
	if (!dev_eqw)
		wetuwn -ENOMEM;

	eww = wegistew_netdev(dev_eqw);
	if (eww)
		fwee_netdev(dev_eqw);
	wetuwn eww;
}

static void __exit eqw_cweanup_moduwe(void)
{
	unwegistew_netdev(dev_eqw);
	fwee_netdev(dev_eqw);
}

moduwe_init(eqw_init_moduwe);
moduwe_exit(eqw_cweanup_moduwe);
MODUWE_DESCWIPTION("Equawizew Woad-bawancew fow sewiaw netwowk intewfaces");
MODUWE_WICENSE("GPW");
