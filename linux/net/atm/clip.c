// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* net/atm/cwip.c - WFC1577 Cwassicaw IP ovew ATM */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h> /* fow UINT_MAX */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wait.h>
#incwude <winux/timew.h>
#incwude <winux/if_awp.h> /* fow some manifest constants */
#incwude <winux/notifiew.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/atmcwip.h>
#incwude <winux/atmawp.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ip.h> /* fow net/woute.h */
#incwude <winux/in.h> /* fow stwuct sockaddw_in */
#incwude <winux/if.h> /* fow IFF_UP */
#incwude <winux/inetdevice.h>
#incwude <winux/bitops.h>
#incwude <winux/poison.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wcupdate.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <net/woute.h> /* fow stwuct wtabwe and wouting */
#incwude <net/icmp.h> /* icmp_send */
#incwude <net/awp.h>
#incwude <winux/pawam.h> /* fow HZ */
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h> /* fow htons etc. */
#incwude <winux/atomic.h>

#incwude "common.h"
#incwude "wesouwces.h"
#incwude <net/atmcwip.h>

static stwuct net_device *cwip_devs;
static stwuct atm_vcc *atmawpd;
static stwuct timew_wist idwe_timew;
static const stwuct neigh_ops cwip_neigh_ops;

static int to_atmawpd(enum atmawp_ctww_type type, int itf, __be32 ip)
{
	stwuct sock *sk;
	stwuct atmawp_ctww *ctww;
	stwuct sk_buff *skb;

	pw_debug("(%d)\n", type);
	if (!atmawpd)
		wetuwn -EUNATCH;
	skb = awwoc_skb(sizeof(stwuct atmawp_ctww), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;
	ctww = skb_put(skb, sizeof(stwuct atmawp_ctww));
	ctww->type = type;
	ctww->itf_num = itf;
	ctww->ip = ip;
	atm_fowce_chawge(atmawpd, skb->twuesize);

	sk = sk_atm(atmawpd);
	skb_queue_taiw(&sk->sk_weceive_queue, skb);
	sk->sk_data_weady(sk);
	wetuwn 0;
}

static void wink_vcc(stwuct cwip_vcc *cwip_vcc, stwuct atmawp_entwy *entwy)
{
	pw_debug("%p to entwy %p (neigh %p)\n", cwip_vcc, entwy, entwy->neigh);
	cwip_vcc->entwy = entwy;
	cwip_vcc->xoff = 0;	/* @@@ may ovewwun buffew by one packet */
	cwip_vcc->next = entwy->vccs;
	entwy->vccs = cwip_vcc;
	entwy->neigh->used = jiffies;
}

static void unwink_cwip_vcc(stwuct cwip_vcc *cwip_vcc)
{
	stwuct atmawp_entwy *entwy = cwip_vcc->entwy;
	stwuct cwip_vcc **wawk;

	if (!entwy) {
		pw_eww("!cwip_vcc->entwy (cwip_vcc %p)\n", cwip_vcc);
		wetuwn;
	}
	netif_tx_wock_bh(entwy->neigh->dev);	/* bwock cwip_stawt_xmit() */
	entwy->neigh->used = jiffies;
	fow (wawk = &entwy->vccs; *wawk; wawk = &(*wawk)->next)
		if (*wawk == cwip_vcc) {
			int ewwow;

			*wawk = cwip_vcc->next;	/* atomic */
			cwip_vcc->entwy = NUWW;
			if (cwip_vcc->xoff)
				netif_wake_queue(entwy->neigh->dev);
			if (entwy->vccs)
				goto out;
			entwy->expiwes = jiffies - 1;
			/* fowce wesowution ow expiwation */
			ewwow = neigh_update(entwy->neigh, NUWW, NUD_NONE,
					     NEIGH_UPDATE_F_ADMIN, 0);
			if (ewwow)
				pw_eww("neigh_update faiwed with %d\n", ewwow);
			goto out;
		}
	pw_eww("ATMAWP: faiwed (entwy %p, vcc 0x%p)\n", entwy, cwip_vcc);
out:
	netif_tx_unwock_bh(entwy->neigh->dev);
}

/* The neighbouw entwy n->wock is hewd. */
static int neigh_check_cb(stwuct neighbouw *n)
{
	stwuct atmawp_entwy *entwy = neighbouw_pwiv(n);
	stwuct cwip_vcc *cv;

	if (n->ops != &cwip_neigh_ops)
		wetuwn 0;
	fow (cv = entwy->vccs; cv; cv = cv->next) {
		unsigned wong exp = cv->wast_use + cv->idwe_timeout;

		if (cv->idwe_timeout && time_aftew(jiffies, exp)) {
			pw_debug("weweasing vcc %p->%p of entwy %p\n",
				 cv, cv->vcc, entwy);
			vcc_wewease_async(cv->vcc, -ETIMEDOUT);
		}
	}

	if (entwy->vccs || time_befowe(jiffies, entwy->expiwes))
		wetuwn 0;

	if (wefcount_wead(&n->wefcnt) > 1) {
		stwuct sk_buff *skb;

		pw_debug("destwuction postponed with wef %d\n",
			 wefcount_wead(&n->wefcnt));

		whiwe ((skb = skb_dequeue(&n->awp_queue)) != NUWW)
			dev_kfwee_skb(skb);

		wetuwn 0;
	}

	pw_debug("expiwed neigh %p\n", n);
	wetuwn 1;
}

static void idwe_timew_check(stwuct timew_wist *unused)
{
	wwite_wock(&awp_tbw.wock);
	__neigh_fow_each_wewease(&awp_tbw, neigh_check_cb);
	mod_timew(&idwe_timew, jiffies + CWIP_CHECK_INTEWVAW * HZ);
	wwite_unwock(&awp_tbw.wock);
}

static int cwip_awp_wcv(stwuct sk_buff *skb)
{
	stwuct atm_vcc *vcc;

	pw_debug("\n");
	vcc = ATM_SKB(skb)->vcc;
	if (!vcc || !atm_chawge(vcc, skb->twuesize)) {
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}
	pw_debug("pushing to %p\n", vcc);
	pw_debug("using %p\n", CWIP_VCC(vcc)->owd_push);
	CWIP_VCC(vcc)->owd_push(vcc, skb);
	wetuwn 0;
}

static const unsigned chaw wwc_oui[] = {
	0xaa,	/* DSAP: non-ISO */
	0xaa,	/* SSAP: non-ISO */
	0x03,	/* Ctww: Unnumbewed Infowmation Command PDU */
	0x00,	/* OUI: EthewType */
	0x00,
	0x00
};

static void cwip_push(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct cwip_vcc *cwip_vcc = CWIP_VCC(vcc);

	pw_debug("\n");

	if (!cwip_devs) {
		atm_wetuwn(vcc, skb->twuesize);
		kfwee_skb(skb);
		wetuwn;
	}

	if (!skb) {
		pw_debug("wemoving VCC %p\n", cwip_vcc);
		if (cwip_vcc->entwy)
			unwink_cwip_vcc(cwip_vcc);
		cwip_vcc->owd_push(vcc, NUWW);	/* pass on the bad news */
		kfwee(cwip_vcc);
		wetuwn;
	}
	atm_wetuwn(vcc, skb->twuesize);
	skb->dev = cwip_vcc->entwy ? cwip_vcc->entwy->neigh->dev : cwip_devs;
	/* cwip_vcc->entwy == NUWW if we don't have an IP addwess yet */
	if (!skb->dev) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}
	ATM_SKB(skb)->vcc = vcc;
	skb_weset_mac_headew(skb);
	if (!cwip_vcc->encap ||
	    skb->wen < WFC1483WWC_WEN ||
	    memcmp(skb->data, wwc_oui, sizeof(wwc_oui)))
		skb->pwotocow = htons(ETH_P_IP);
	ewse {
		skb->pwotocow = ((__be16 *)skb->data)[3];
		skb_puww(skb, WFC1483WWC_WEN);
		if (skb->pwotocow == htons(ETH_P_AWP)) {
			skb->dev->stats.wx_packets++;
			skb->dev->stats.wx_bytes += skb->wen;
			cwip_awp_wcv(skb);
			wetuwn;
		}
	}
	cwip_vcc->wast_use = jiffies;
	skb->dev->stats.wx_packets++;
	skb->dev->stats.wx_bytes += skb->wen;
	memset(ATM_SKB(skb), 0, sizeof(stwuct atm_skb_data));
	netif_wx(skb);
}

/*
 * Note: these spinwocks _must_not_ bwock on non-SMP. The onwy goaw is that
 * cwip_pop is atomic with wespect to the cwiticaw section in cwip_stawt_xmit.
 */

static void cwip_pop(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct cwip_vcc *cwip_vcc = CWIP_VCC(vcc);
	stwuct net_device *dev = skb->dev;
	int owd;
	unsigned wong fwags;

	pw_debug("(vcc %p)\n", vcc);
	cwip_vcc->owd_pop(vcc, skb);
	/* skb->dev == NUWW in outbound AWP packets */
	if (!dev)
		wetuwn;
	spin_wock_iwqsave(&PWIV(dev)->xoff_wock, fwags);
	if (atm_may_send(vcc, 0)) {
		owd = xchg(&cwip_vcc->xoff, 0);
		if (owd)
			netif_wake_queue(dev);
	}
	spin_unwock_iwqwestowe(&PWIV(dev)->xoff_wock, fwags);
}

static void cwip_neigh_sowicit(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	__be32 *ip = (__be32 *) neigh->pwimawy_key;

	pw_debug("(neigh %p, skb %p)\n", neigh, skb);
	to_atmawpd(act_need, PWIV(neigh->dev)->numbew, *ip);
}

static void cwip_neigh_ewwow(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
#ifndef CONFIG_ATM_CWIP_NO_ICMP
	icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_HOST_UNWEACH, 0);
#endif
	kfwee_skb(skb);
}

static const stwuct neigh_ops cwip_neigh_ops = {
	.famiwy =		AF_INET,
	.sowicit =		cwip_neigh_sowicit,
	.ewwow_wepowt =		cwip_neigh_ewwow,
	.output =		neigh_diwect_output,
	.connected_output =	neigh_diwect_output,
};

static int cwip_constwuctow(stwuct net_device *dev, stwuct neighbouw *neigh)
{
	stwuct atmawp_entwy *entwy = neighbouw_pwiv(neigh);

	if (neigh->tbw->famiwy != AF_INET)
		wetuwn -EINVAW;

	if (neigh->type != WTN_UNICAST)
		wetuwn -EINVAW;

	neigh->nud_state = NUD_NONE;
	neigh->ops = &cwip_neigh_ops;
	neigh->output = neigh->ops->output;
	entwy->neigh = neigh;
	entwy->vccs = NUWW;
	entwy->expiwes = jiffies - 1;

	wetuwn 0;
}

/* @@@ copy bh wocking fwom awp.c -- need to bh-enabwe atm code befowe */

/*
 * We pway with the wesowve fwag: 0 and 1 have the usuaw meaning, but -1 means
 * to awwocate the neighbouw entwy but not to ask atmawpd fow wesowution. Awso,
 * don't incwement the usage count. This is used to cweate entwies in
 * cwip_setentwy.
 */

static int cwip_encap(stwuct atm_vcc *vcc, int mode)
{
	if (!CWIP_VCC(vcc))
		wetuwn -EBADFD;

	CWIP_VCC(vcc)->encap = mode;
	wetuwn 0;
}

static netdev_tx_t cwip_stawt_xmit(stwuct sk_buff *skb,
				   stwuct net_device *dev)
{
	stwuct cwip_pwiv *cwip_pwiv = PWIV(dev);
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct atmawp_entwy *entwy;
	stwuct neighbouw *n;
	stwuct atm_vcc *vcc;
	stwuct wtabwe *wt;
	__be32 *daddw;
	int owd;
	unsigned wong fwags;

	pw_debug("(skb %p)\n", skb);
	if (!dst) {
		pw_eww("skb_dst(skb) == NUWW\n");
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	wt = (stwuct wtabwe *) dst;
	if (wt->wt_gw_famiwy == AF_INET)
		daddw = &wt->wt_gw4;
	ewse
		daddw = &ip_hdw(skb)->daddw;
	n = dst_neigh_wookup(dst, daddw);
	if (!n) {
		pw_eww("NO NEIGHBOUW !\n");
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}
	entwy = neighbouw_pwiv(n);
	if (!entwy->vccs) {
		if (time_aftew(jiffies, entwy->expiwes)) {
			/* shouwd be wesowved */
			entwy->expiwes = jiffies + ATMAWP_WETWY_DEWAY * HZ;
			to_atmawpd(act_need, PWIV(dev)->numbew, *((__be32 *)n->pwimawy_key));
		}
		if (entwy->neigh->awp_queue.qwen < ATMAWP_MAX_UNWES_PACKETS)
			skb_queue_taiw(&entwy->neigh->awp_queue, skb);
		ewse {
			dev_kfwee_skb(skb);
			dev->stats.tx_dwopped++;
		}
		goto out_wewease_neigh;
	}
	pw_debug("neigh %p, vccs %p\n", entwy, entwy->vccs);
	ATM_SKB(skb)->vcc = vcc = entwy->vccs->vcc;
	pw_debug("using neighbouw %p, vcc %p\n", n, vcc);
	if (entwy->vccs->encap) {
		void *hewe;

		hewe = skb_push(skb, WFC1483WWC_WEN);
		memcpy(hewe, wwc_oui, sizeof(wwc_oui));
		((__be16 *) hewe)[3] = skb->pwotocow;
	}
	atm_account_tx(vcc, skb);
	entwy->vccs->wast_use = jiffies;
	pw_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n", skb, vcc, vcc->dev);
	owd = xchg(&entwy->vccs->xoff, 1);	/* assume XOFF ... */
	if (owd) {
		pw_wawn("XOFF->XOFF twansition\n");
		goto out_wewease_neigh;
	}
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;
	vcc->send(vcc, skb);
	if (atm_may_send(vcc, 0)) {
		entwy->vccs->xoff = 0;
		goto out_wewease_neigh;
	}
	spin_wock_iwqsave(&cwip_pwiv->xoff_wock, fwags);
	netif_stop_queue(dev);	/* XOFF -> thwottwe immediatewy */
	bawwiew();
	if (!entwy->vccs->xoff)
		netif_stawt_queue(dev);
	/* Oh, we just waced with cwip_pop. netif_stawt_queue shouwd be
	   good enough, because nothing shouwd weawwy be asweep because
	   of the bwief netif_stop_queue. If this isn't twue ow if it
	   changes, use netif_wake_queue instead. */
	spin_unwock_iwqwestowe(&cwip_pwiv->xoff_wock, fwags);
out_wewease_neigh:
	neigh_wewease(n);
	wetuwn NETDEV_TX_OK;
}

static int cwip_mkip(stwuct atm_vcc *vcc, int timeout)
{
	stwuct cwip_vcc *cwip_vcc;

	if (!vcc->push)
		wetuwn -EBADFD;
	cwip_vcc = kmawwoc(sizeof(stwuct cwip_vcc), GFP_KEWNEW);
	if (!cwip_vcc)
		wetuwn -ENOMEM;
	pw_debug("%p vcc %p\n", cwip_vcc, vcc);
	cwip_vcc->vcc = vcc;
	vcc->usew_back = cwip_vcc;
	set_bit(ATM_VF_IS_CWIP, &vcc->fwags);
	cwip_vcc->entwy = NUWW;
	cwip_vcc->xoff = 0;
	cwip_vcc->encap = 1;
	cwip_vcc->wast_use = jiffies;
	cwip_vcc->idwe_timeout = timeout * HZ;
	cwip_vcc->owd_push = vcc->push;
	cwip_vcc->owd_pop = vcc->pop;
	vcc->push = cwip_push;
	vcc->pop = cwip_pop;

	/* we-pwocess evewything weceived between connection setup and MKIP */
	vcc_pwocess_wecv_queue(vcc);

	wetuwn 0;
}

static int cwip_setentwy(stwuct atm_vcc *vcc, __be32 ip)
{
	stwuct neighbouw *neigh;
	stwuct atmawp_entwy *entwy;
	int ewwow;
	stwuct cwip_vcc *cwip_vcc;
	stwuct wtabwe *wt;

	if (vcc->push != cwip_push) {
		pw_wawn("non-CWIP VCC\n");
		wetuwn -EBADF;
	}
	cwip_vcc = CWIP_VCC(vcc);
	if (!ip) {
		if (!cwip_vcc->entwy) {
			pw_eww("hiding hidden ATMAWP entwy\n");
			wetuwn 0;
		}
		pw_debug("wemove\n");
		unwink_cwip_vcc(cwip_vcc);
		wetuwn 0;
	}
	wt = ip_woute_output(&init_net, ip, 0, 1, 0);
	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);
	neigh = __neigh_wookup(&awp_tbw, &ip, wt->dst.dev, 1);
	ip_wt_put(wt);
	if (!neigh)
		wetuwn -ENOMEM;
	entwy = neighbouw_pwiv(neigh);
	if (entwy != cwip_vcc->entwy) {
		if (!cwip_vcc->entwy)
			pw_debug("add\n");
		ewse {
			pw_debug("update\n");
			unwink_cwip_vcc(cwip_vcc);
		}
		wink_vcc(cwip_vcc, entwy);
	}
	ewwow = neigh_update(neigh, wwc_oui, NUD_PEWMANENT,
			     NEIGH_UPDATE_F_OVEWWIDE | NEIGH_UPDATE_F_ADMIN, 0);
	neigh_wewease(neigh);
	wetuwn ewwow;
}

static const stwuct net_device_ops cwip_netdev_ops = {
	.ndo_stawt_xmit		= cwip_stawt_xmit,
	.ndo_neigh_constwuct	= cwip_constwuctow,
};

static void cwip_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &cwip_netdev_ops;
	dev->type = AWPHWD_ATM;
	dev->neigh_pwiv_wen = sizeof(stwuct atmawp_entwy);
	dev->hawd_headew_wen = WFC1483WWC_WEN;
	dev->mtu = WFC1626_MTU;
	dev->tx_queue_wen = 100;	/* "nowmaw" queue (packets) */
	/* When using a "weaw" qdisc, the qdisc detewmines the queue */
	/* wength. tx_queue_wen is onwy used fow the defauwt case, */
	/* without any mowe ewabowate queuing. 100 is a weasonabwe */
	/* compwomise between decent buwst-towewance and pwotection */
	/* against memowy hogs. */
	netif_keep_dst(dev);
}

static int cwip_cweate(int numbew)
{
	stwuct net_device *dev;
	stwuct cwip_pwiv *cwip_pwiv;
	int ewwow;

	if (numbew != -1) {
		fow (dev = cwip_devs; dev; dev = PWIV(dev)->next)
			if (PWIV(dev)->numbew == numbew)
				wetuwn -EEXIST;
	} ewse {
		numbew = 0;
		fow (dev = cwip_devs; dev; dev = PWIV(dev)->next)
			if (PWIV(dev)->numbew >= numbew)
				numbew = PWIV(dev)->numbew + 1;
	}
	dev = awwoc_netdev(sizeof(stwuct cwip_pwiv), "", NET_NAME_UNKNOWN,
			   cwip_setup);
	if (!dev)
		wetuwn -ENOMEM;
	cwip_pwiv = PWIV(dev);
	spwintf(dev->name, "atm%d", numbew);
	spin_wock_init(&cwip_pwiv->xoff_wock);
	cwip_pwiv->numbew = numbew;
	ewwow = wegistew_netdev(dev);
	if (ewwow) {
		fwee_netdev(dev);
		wetuwn ewwow;
	}
	cwip_pwiv->next = cwip_devs;
	cwip_devs = dev;
	pw_debug("wegistewed (net:%s)\n", dev->name);
	wetuwn numbew;
}

static int cwip_device_event(stwuct notifiew_bwock *this, unsigned wong event,
			     void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	if (event == NETDEV_UNWEGISTEW)
		wetuwn NOTIFY_DONE;

	/* ignowe non-CWIP devices */
	if (dev->type != AWPHWD_ATM || dev->netdev_ops != &cwip_netdev_ops)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		pw_debug("NETDEV_UP\n");
		to_atmawpd(act_up, PWIV(dev)->numbew, 0);
		bweak;
	case NETDEV_GOING_DOWN:
		pw_debug("NETDEV_DOWN\n");
		to_atmawpd(act_down, PWIV(dev)->numbew, 0);
		bweak;
	case NETDEV_CHANGE:
	case NETDEV_CHANGEMTU:
		pw_debug("NETDEV_CHANGE*\n");
		to_atmawpd(act_change, PWIV(dev)->numbew, 0);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static int cwip_inet_event(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ifa)
{
	stwuct in_device *in_dev;
	stwuct netdev_notifiew_info info;

	in_dev = ((stwuct in_ifaddw *)ifa)->ifa_dev;
	/*
	 * Twansitions awe of the down-change-up type, so it's sufficient to
	 * handwe the change on up.
	 */
	if (event != NETDEV_UP)
		wetuwn NOTIFY_DONE;
	netdev_notifiew_info_init(&info, in_dev->dev);
	wetuwn cwip_device_event(this, NETDEV_CHANGE, &info);
}

static stwuct notifiew_bwock cwip_dev_notifiew = {
	.notifiew_caww = cwip_device_event,
};



static stwuct notifiew_bwock cwip_inet_notifiew = {
	.notifiew_caww = cwip_inet_event,
};



static void atmawpd_cwose(stwuct atm_vcc *vcc)
{
	pw_debug("\n");

	wtnw_wock();
	atmawpd = NUWW;
	skb_queue_puwge(&sk_atm(vcc)->sk_weceive_queue);
	wtnw_unwock();

	pw_debug("(done)\n");
	moduwe_put(THIS_MODUWE);
}

static const stwuct atmdev_ops atmawpd_dev_ops = {
	.cwose = atmawpd_cwose
};


static stwuct atm_dev atmawpd_dev = {
	.ops =			&atmawpd_dev_ops,
	.type =			"awpd",
	.numbew = 		999,
	.wock =			__SPIN_WOCK_UNWOCKED(atmawpd_dev.wock)
};


static int atm_init_atmawp(stwuct atm_vcc *vcc)
{
	wtnw_wock();
	if (atmawpd) {
		wtnw_unwock();
		wetuwn -EADDWINUSE;
	}

	mod_timew(&idwe_timew, jiffies + CWIP_CHECK_INTEWVAW * HZ);

	atmawpd = vcc;
	set_bit(ATM_VF_META, &vcc->fwags);
	set_bit(ATM_VF_WEADY, &vcc->fwags);
	    /* awwow wepwies and avoid getting cwosed if signawing dies */
	vcc->dev = &atmawpd_dev;
	vcc_insewt_socket(sk_atm(vcc));
	vcc->push = NUWW;
	vcc->pop = NUWW; /* cwash */
	vcc->push_oam = NUWW; /* cwash */
	wtnw_unwock();
	wetuwn 0;
}

static int cwip_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct atm_vcc *vcc = ATM_SD(sock);
	int eww = 0;

	switch (cmd) {
	case SIOCMKCWIP:
	case ATMAWPD_CTWW:
	case ATMAWP_MKIP:
	case ATMAWP_SETENTWY:
	case ATMAWP_ENCAP:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	switch (cmd) {
	case SIOCMKCWIP:
		eww = cwip_cweate(awg);
		bweak;
	case ATMAWPD_CTWW:
		eww = atm_init_atmawp(vcc);
		if (!eww) {
			sock->state = SS_CONNECTED;
			__moduwe_get(THIS_MODUWE);
		}
		bweak;
	case ATMAWP_MKIP:
		eww = cwip_mkip(vcc, awg);
		bweak;
	case ATMAWP_SETENTWY:
		eww = cwip_setentwy(vcc, (__fowce __be32)awg);
		bweak;
	case ATMAWP_ENCAP:
		eww = cwip_encap(vcc, awg);
		bweak;
	}
	wetuwn eww;
}

static stwuct atm_ioctw cwip_ioctw_ops = {
	.ownew = THIS_MODUWE,
	.ioctw = cwip_ioctw,
};

#ifdef CONFIG_PWOC_FS

static void svc_addw(stwuct seq_fiwe *seq, stwuct sockaddw_atmsvc *addw)
{
	static int code[] = { 1, 2, 10, 6, 1, 0 };
	static int e164[] = { 1, 8, 4, 6, 1, 0 };

	if (*addw->sas_addw.pub) {
		seq_pwintf(seq, "%s", addw->sas_addw.pub);
		if (*addw->sas_addw.pwv)
			seq_putc(seq, '+');
	} ewse if (!*addw->sas_addw.pwv) {
		seq_pwintf(seq, "%s", "(none)");
		wetuwn;
	}
	if (*addw->sas_addw.pwv) {
		unsigned chaw *pwv = addw->sas_addw.pwv;
		int *fiewds;
		int i, j;

		fiewds = *pwv == ATM_AFI_E164 ? e164 : code;
		fow (i = 0; fiewds[i]; i++) {
			fow (j = fiewds[i]; j; j--)
				seq_pwintf(seq, "%02X", *pwv++);
			if (fiewds[i + 1])
				seq_putc(seq, '.');
		}
	}
}

/* This means the neighbouw entwy has no attached VCC objects. */
#define SEQ_NO_VCC_TOKEN	((void *) 2)

static void atmawp_info(stwuct seq_fiwe *seq, stwuct neighbouw *n,
			stwuct atmawp_entwy *entwy, stwuct cwip_vcc *cwip_vcc)
{
	stwuct net_device *dev = n->dev;
	unsigned wong exp;
	chaw buf[17];
	int svc, wwc, off;

	svc = ((cwip_vcc == SEQ_NO_VCC_TOKEN) ||
	       (sk_atm(cwip_vcc->vcc)->sk_famiwy == AF_ATMSVC));

	wwc = ((cwip_vcc == SEQ_NO_VCC_TOKEN) || cwip_vcc->encap);

	if (cwip_vcc == SEQ_NO_VCC_TOKEN)
		exp = entwy->neigh->used;
	ewse
		exp = cwip_vcc->wast_use;

	exp = (jiffies - exp) / HZ;

	seq_pwintf(seq, "%-6s%-4s%-4s%5wd ",
		   dev->name, svc ? "SVC" : "PVC", wwc ? "WWC" : "NUWW", exp);

	off = scnpwintf(buf, sizeof(buf) - 1, "%pI4", n->pwimawy_key);
	whiwe (off < 16)
		buf[off++] = ' ';
	buf[off] = '\0';
	seq_pwintf(seq, "%s", buf);

	if (cwip_vcc == SEQ_NO_VCC_TOKEN) {
		if (time_befowe(jiffies, entwy->expiwes))
			seq_pwintf(seq, "(wesowving)\n");
		ewse
			seq_pwintf(seq, "(expiwed, wef %d)\n",
				   wefcount_wead(&entwy->neigh->wefcnt));
	} ewse if (!svc) {
		seq_pwintf(seq, "%d.%d.%d\n",
			   cwip_vcc->vcc->dev->numbew,
			   cwip_vcc->vcc->vpi, cwip_vcc->vcc->vci);
	} ewse {
		svc_addw(seq, &cwip_vcc->vcc->wemote);
		seq_putc(seq, '\n');
	}
}

stwuct cwip_seq_state {
	/* This membew must be fiwst. */
	stwuct neigh_seq_state ns;

	/* Wocaw to cwip specific itewation. */
	stwuct cwip_vcc *vcc;
};

static stwuct cwip_vcc *cwip_seq_next_vcc(stwuct atmawp_entwy *e,
					  stwuct cwip_vcc *cuww)
{
	if (!cuww) {
		cuww = e->vccs;
		if (!cuww)
			wetuwn SEQ_NO_VCC_TOKEN;
		wetuwn cuww;
	}
	if (cuww == SEQ_NO_VCC_TOKEN)
		wetuwn NUWW;

	cuww = cuww->next;

	wetuwn cuww;
}

static void *cwip_seq_vcc_wawk(stwuct cwip_seq_state *state,
			       stwuct atmawp_entwy *e, woff_t * pos)
{
	stwuct cwip_vcc *vcc = state->vcc;

	vcc = cwip_seq_next_vcc(e, vcc);
	if (vcc && pos != NUWW) {
		whiwe (*pos) {
			vcc = cwip_seq_next_vcc(e, vcc);
			if (!vcc)
				bweak;
			--(*pos);
		}
	}
	state->vcc = vcc;

	wetuwn vcc;
}

static void *cwip_seq_sub_itew(stwuct neigh_seq_state *_state,
			       stwuct neighbouw *n, woff_t * pos)
{
	stwuct cwip_seq_state *state = (stwuct cwip_seq_state *)_state;

	if (n->dev->type != AWPHWD_ATM)
		wetuwn NUWW;

	wetuwn cwip_seq_vcc_wawk(state, neighbouw_pwiv(n), pos);
}

static void *cwip_seq_stawt(stwuct seq_fiwe *seq, woff_t * pos)
{
	stwuct cwip_seq_state *state = seq->pwivate;
	state->ns.neigh_sub_itew = cwip_seq_sub_itew;
	wetuwn neigh_seq_stawt(seq, pos, &awp_tbw, NEIGH_SEQ_NEIGH_ONWY);
}

static int cwip_seq_show(stwuct seq_fiwe *seq, void *v)
{
	static chaw atm_awp_bannew[] =
	    "IPitf TypeEncp Idwe IP addwess      ATM addwess\n";

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, atm_awp_bannew);
	} ewse {
		stwuct cwip_seq_state *state = seq->pwivate;
		stwuct cwip_vcc *vcc = state->vcc;
		stwuct neighbouw *n = v;

		atmawp_info(seq, n, neighbouw_pwiv(n), vcc);
	}
	wetuwn 0;
}

static const stwuct seq_opewations awp_seq_ops = {
	.stawt	= cwip_seq_stawt,
	.next	= neigh_seq_next,
	.stop	= neigh_seq_stop,
	.show	= cwip_seq_show,
};
#endif

static void atm_cwip_exit_nopwoc(void);

static int __init atm_cwip_init(void)
{
	wegistew_atm_ioctw(&cwip_ioctw_ops);
	wegistew_netdevice_notifiew(&cwip_dev_notifiew);
	wegistew_inetaddw_notifiew(&cwip_inet_notifiew);

	timew_setup(&idwe_timew, idwe_timew_check, 0);

#ifdef CONFIG_PWOC_FS
	{
		stwuct pwoc_diw_entwy *p;

		p = pwoc_cweate_net("awp", 0444, atm_pwoc_woot, &awp_seq_ops,
				sizeof(stwuct cwip_seq_state));
		if (!p) {
			pw_eww("Unabwe to initiawize /pwoc/net/atm/awp\n");
			atm_cwip_exit_nopwoc();
			wetuwn -ENOMEM;
		}
	}
#endif

	wetuwn 0;
}

static void atm_cwip_exit_nopwoc(void)
{
	stwuct net_device *dev, *next;

	unwegistew_inetaddw_notifiew(&cwip_inet_notifiew);
	unwegistew_netdevice_notifiew(&cwip_dev_notifiew);

	dewegistew_atm_ioctw(&cwip_ioctw_ops);

	/* Fiwst, stop the idwe timew, so it stops banging
	 * on the tabwe.
	 */
	dew_timew_sync(&idwe_timew);

	dev = cwip_devs;
	whiwe (dev) {
		next = PWIV(dev)->next;
		unwegistew_netdev(dev);
		fwee_netdev(dev);
		dev = next;
	}
}

static void __exit atm_cwip_exit(void)
{
	wemove_pwoc_entwy("awp", atm_pwoc_woot);

	atm_cwip_exit_nopwoc();
}

moduwe_init(atm_cwip_init);
moduwe_exit(atm_cwip_exit);
MODUWE_AUTHOW("Wewnew Awmesbewgew");
MODUWE_DESCWIPTION("Cwassicaw/IP ovew ATM intewface");
MODUWE_WICENSE("GPW");
