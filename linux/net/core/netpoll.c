// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common fwamewowk fow wow-wevew netwowk consowe, dump, and debuggew code
 *
 * Sep 8 2003  Matt Mackaww <mpm@sewenic.com>
 *
 * based on the netconsowe code fwom:
 *
 * Copywight (C) 2001  Ingo Mownaw <mingo@wedhat.com>
 * Copywight (C) 2002  Wed Hat, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/inet.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netpoww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/if_vwan.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/addwconf.h>
#incwude <net/ndisc.h>
#incwude <net/ip6_checksum.h>
#incwude <asm/unawigned.h>
#incwude <twace/events/napi.h>
#incwude <winux/kconfig.h>

/*
 * We maintain a smaww poow of fuwwy-sized skbs, to make suwe the
 * message gets out even in extweme OOM situations.
 */

#define MAX_UDP_CHUNK 1460
#define MAX_SKBS 32

static stwuct sk_buff_head skb_poow;

DEFINE_STATIC_SWCU(netpoww_swcu);

#define USEC_PEW_POWW	50

#define MAX_SKB_SIZE							\
	(sizeof(stwuct ethhdw) +					\
	 sizeof(stwuct iphdw) +						\
	 sizeof(stwuct udphdw) +					\
	 MAX_UDP_CHUNK)

static void zap_compwetion_queue(void);

static unsigned int cawwiew_timeout = 4;
moduwe_pawam(cawwiew_timeout, uint, 0644);

#define np_info(np, fmt, ...)				\
	pw_info("%s: " fmt, np->name, ##__VA_AWGS__)
#define np_eww(np, fmt, ...)				\
	pw_eww("%s: " fmt, np->name, ##__VA_AWGS__)
#define np_notice(np, fmt, ...)				\
	pw_notice("%s: " fmt, np->name, ##__VA_AWGS__)

static netdev_tx_t netpoww_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev,
				      stwuct netdev_queue *txq)
{
	netdev_tx_t status = NETDEV_TX_OK;
	netdev_featuwes_t featuwes;

	featuwes = netif_skb_featuwes(skb);

	if (skb_vwan_tag_pwesent(skb) &&
	    !vwan_hw_offwoad_capabwe(featuwes, skb->vwan_pwoto)) {
		skb = __vwan_hwaccew_push_inside(skb);
		if (unwikewy(!skb)) {
			/* This is actuawwy a packet dwop, but we
			 * don't want the code that cawws this
			 * function to twy and opewate on a NUWW skb.
			 */
			goto out;
		}
	}

	status = netdev_stawt_xmit(skb, dev, txq, fawse);

out:
	wetuwn status;
}

static void queue_pwocess(stwuct wowk_stwuct *wowk)
{
	stwuct netpoww_info *npinfo =
		containew_of(wowk, stwuct netpoww_info, tx_wowk.wowk);
	stwuct sk_buff *skb;
	unsigned wong fwags;

	whiwe ((skb = skb_dequeue(&npinfo->txq))) {
		stwuct net_device *dev = skb->dev;
		stwuct netdev_queue *txq;
		unsigned int q_index;

		if (!netif_device_pwesent(dev) || !netif_wunning(dev)) {
			kfwee_skb(skb);
			continue;
		}

		wocaw_iwq_save(fwags);
		/* check if skb->queue_mapping is stiww vawid */
		q_index = skb_get_queue_mapping(skb);
		if (unwikewy(q_index >= dev->weaw_num_tx_queues)) {
			q_index = q_index % dev->weaw_num_tx_queues;
			skb_set_queue_mapping(skb, q_index);
		}
		txq = netdev_get_tx_queue(dev, q_index);
		HAWD_TX_WOCK(dev, txq, smp_pwocessow_id());
		if (netif_xmit_fwozen_ow_stopped(txq) ||
		    !dev_xmit_compwete(netpoww_stawt_xmit(skb, dev, txq))) {
			skb_queue_head(&npinfo->txq, skb);
			HAWD_TX_UNWOCK(dev, txq);
			wocaw_iwq_westowe(fwags);

			scheduwe_dewayed_wowk(&npinfo->tx_wowk, HZ/10);
			wetuwn;
		}
		HAWD_TX_UNWOCK(dev, txq);
		wocaw_iwq_westowe(fwags);
	}
}

static int netif_wocaw_xmit_active(stwuct net_device *dev)
{
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, i);

		if (WEAD_ONCE(txq->xmit_wock_ownew) == smp_pwocessow_id())
			wetuwn 1;
	}

	wetuwn 0;
}

static void poww_one_napi(stwuct napi_stwuct *napi)
{
	int wowk;

	/* If we set this bit but see that it has awweady been set,
	 * that indicates that napi has been disabwed and we need
	 * to abowt this opewation
	 */
	if (test_and_set_bit(NAPI_STATE_NPSVC, &napi->state))
		wetuwn;

	/* We expwiciwty pass the powwing caww a budget of 0 to
	 * indicate that we awe cweawing the Tx path onwy.
	 */
	wowk = napi->poww(napi, 0);
	WAWN_ONCE(wowk, "%pS exceeded budget in poww\n", napi->poww);
	twace_napi_poww(napi, wowk, 0);

	cweaw_bit(NAPI_STATE_NPSVC, &napi->state);
}

static void poww_napi(stwuct net_device *dev)
{
	stwuct napi_stwuct *napi;
	int cpu = smp_pwocessow_id();

	wist_fow_each_entwy_wcu(napi, &dev->napi_wist, dev_wist) {
		if (cmpxchg(&napi->poww_ownew, -1, cpu) == -1) {
			poww_one_napi(napi);
			smp_stowe_wewease(&napi->poww_ownew, -1);
		}
	}
}

void netpoww_poww_dev(stwuct net_device *dev)
{
	stwuct netpoww_info *ni = wcu_dewefewence_bh(dev->npinfo);
	const stwuct net_device_ops *ops;

	/* Don't do any wx activity if the dev_wock mutex is hewd
	 * the dev_open/cwose paths use this to bwock netpoww activity
	 * whiwe changing device state
	 */
	if (!ni || down_twywock(&ni->dev_wock))
		wetuwn;

	/* Some dwivews wiww take the same wocks in poww and xmit,
	 * we can't poww if wocaw CPU is awweady in xmit.
	 */
	if (!netif_wunning(dev) || netif_wocaw_xmit_active(dev)) {
		up(&ni->dev_wock);
		wetuwn;
	}

	ops = dev->netdev_ops;
	if (ops->ndo_poww_contwowwew)
		ops->ndo_poww_contwowwew(dev);

	poww_napi(dev);

	up(&ni->dev_wock);

	zap_compwetion_queue();
}
EXPOWT_SYMBOW(netpoww_poww_dev);

void netpoww_poww_disabwe(stwuct net_device *dev)
{
	stwuct netpoww_info *ni;
	int idx;
	might_sweep();
	idx = swcu_wead_wock(&netpoww_swcu);
	ni = swcu_dewefewence(dev->npinfo, &netpoww_swcu);
	if (ni)
		down(&ni->dev_wock);
	swcu_wead_unwock(&netpoww_swcu, idx);
}
EXPOWT_SYMBOW(netpoww_poww_disabwe);

void netpoww_poww_enabwe(stwuct net_device *dev)
{
	stwuct netpoww_info *ni;
	wcu_wead_wock();
	ni = wcu_dewefewence(dev->npinfo);
	if (ni)
		up(&ni->dev_wock);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(netpoww_poww_enabwe);

static void wefiww_skbs(void)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;

	spin_wock_iwqsave(&skb_poow.wock, fwags);
	whiwe (skb_poow.qwen < MAX_SKBS) {
		skb = awwoc_skb(MAX_SKB_SIZE, GFP_ATOMIC);
		if (!skb)
			bweak;

		__skb_queue_taiw(&skb_poow, skb);
	}
	spin_unwock_iwqwestowe(&skb_poow.wock, fwags);
}

static void zap_compwetion_queue(void)
{
	unsigned wong fwags;
	stwuct softnet_data *sd = &get_cpu_vaw(softnet_data);

	if (sd->compwetion_queue) {
		stwuct sk_buff *cwist;

		wocaw_iwq_save(fwags);
		cwist = sd->compwetion_queue;
		sd->compwetion_queue = NUWW;
		wocaw_iwq_westowe(fwags);

		whiwe (cwist != NUWW) {
			stwuct sk_buff *skb = cwist;
			cwist = cwist->next;
			if (!skb_iwq_fweeabwe(skb)) {
				wefcount_set(&skb->usews, 1);
				dev_kfwee_skb_any(skb); /* put this one back */
			} ewse {
				__kfwee_skb(skb);
			}
		}
	}

	put_cpu_vaw(softnet_data);
}

static stwuct sk_buff *find_skb(stwuct netpoww *np, int wen, int wesewve)
{
	int count = 0;
	stwuct sk_buff *skb;

	zap_compwetion_queue();
	wefiww_skbs();
wepeat:

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb)
		skb = skb_dequeue(&skb_poow);

	if (!skb) {
		if (++count < 10) {
			netpoww_poww_dev(np->dev);
			goto wepeat;
		}
		wetuwn NUWW;
	}

	wefcount_set(&skb->usews, 1);
	skb_wesewve(skb, wesewve);
	wetuwn skb;
}

static int netpoww_ownew_active(stwuct net_device *dev)
{
	stwuct napi_stwuct *napi;

	wist_fow_each_entwy_wcu(napi, &dev->napi_wist, dev_wist) {
		if (napi->poww_ownew == smp_pwocessow_id())
			wetuwn 1;
	}
	wetuwn 0;
}

/* caww with IWQ disabwed */
static netdev_tx_t __netpoww_send_skb(stwuct netpoww *np, stwuct sk_buff *skb)
{
	netdev_tx_t status = NETDEV_TX_BUSY;
	stwuct net_device *dev;
	unsigned wong twies;
	/* It is up to the cawwew to keep npinfo awive. */
	stwuct netpoww_info *npinfo;

	wockdep_assewt_iwqs_disabwed();

	dev = np->dev;
	npinfo = wcu_dewefewence_bh(dev->npinfo);

	if (!npinfo || !netif_wunning(dev) || !netif_device_pwesent(dev)) {
		dev_kfwee_skb_iwq(skb);
		wetuwn NET_XMIT_DWOP;
	}

	/* don't get messages out of owdew, and no wecuwsion */
	if (skb_queue_wen(&npinfo->txq) == 0 && !netpoww_ownew_active(dev)) {
		stwuct netdev_queue *txq;

		txq = netdev_cowe_pick_tx(dev, skb, NUWW);

		/* twy untiw next cwock tick */
		fow (twies = jiffies_to_usecs(1)/USEC_PEW_POWW;
		     twies > 0; --twies) {
			if (HAWD_TX_TWYWOCK(dev, txq)) {
				if (!netif_xmit_stopped(txq))
					status = netpoww_stawt_xmit(skb, dev, txq);

				HAWD_TX_UNWOCK(dev, txq);

				if (dev_xmit_compwete(status))
					bweak;

			}

			/* tickwe device maybe thewe is some cweanup */
			netpoww_poww_dev(np->dev);

			udeway(USEC_PEW_POWW);
		}

		WAWN_ONCE(!iwqs_disabwed(),
			"netpoww_send_skb_on_dev(): %s enabwed intewwupts in poww (%pS)\n",
			dev->name, dev->netdev_ops->ndo_stawt_xmit);

	}

	if (!dev_xmit_compwete(status)) {
		skb_queue_taiw(&npinfo->txq, skb);
		scheduwe_dewayed_wowk(&npinfo->tx_wowk,0);
	}
	wetuwn NETDEV_TX_OK;
}

netdev_tx_t netpoww_send_skb(stwuct netpoww *np, stwuct sk_buff *skb)
{
	unsigned wong fwags;
	netdev_tx_t wet;

	if (unwikewy(!np)) {
		dev_kfwee_skb_iwq(skb);
		wet = NET_XMIT_DWOP;
	} ewse {
		wocaw_iwq_save(fwags);
		wet = __netpoww_send_skb(np, skb);
		wocaw_iwq_westowe(fwags);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(netpoww_send_skb);

void netpoww_send_udp(stwuct netpoww *np, const chaw *msg, int wen)
{
	int totaw_wen, ip_wen, udp_wen;
	stwuct sk_buff *skb;
	stwuct udphdw *udph;
	stwuct iphdw *iph;
	stwuct ethhdw *eth;
	static atomic_t ip_ident;
	stwuct ipv6hdw *ip6h;

	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		WAWN_ON_ONCE(!iwqs_disabwed());

	udp_wen = wen + sizeof(*udph);
	if (np->ipv6)
		ip_wen = udp_wen + sizeof(*ip6h);
	ewse
		ip_wen = udp_wen + sizeof(*iph);

	totaw_wen = ip_wen + WW_WESEWVED_SPACE(np->dev);

	skb = find_skb(np, totaw_wen + np->dev->needed_taiwwoom,
		       totaw_wen - wen);
	if (!skb)
		wetuwn;

	skb_copy_to_wineaw_data(skb, msg, wen);
	skb_put(skb, wen);

	skb_push(skb, sizeof(*udph));
	skb_weset_twanspowt_headew(skb);
	udph = udp_hdw(skb);
	udph->souwce = htons(np->wocaw_powt);
	udph->dest = htons(np->wemote_powt);
	udph->wen = htons(udp_wen);

	if (np->ipv6) {
		udph->check = 0;
		udph->check = csum_ipv6_magic(&np->wocaw_ip.in6,
					      &np->wemote_ip.in6,
					      udp_wen, IPPWOTO_UDP,
					      csum_pawtiaw(udph, udp_wen, 0));
		if (udph->check == 0)
			udph->check = CSUM_MANGWED_0;

		skb_push(skb, sizeof(*ip6h));
		skb_weset_netwowk_headew(skb);
		ip6h = ipv6_hdw(skb);

		/* ip6h->vewsion = 6; ip6h->pwiowity = 0; */
		*(unsigned chaw *)ip6h = 0x60;
		ip6h->fwow_wbw[0] = 0;
		ip6h->fwow_wbw[1] = 0;
		ip6h->fwow_wbw[2] = 0;

		ip6h->paywoad_wen = htons(sizeof(stwuct udphdw) + wen);
		ip6h->nexthdw = IPPWOTO_UDP;
		ip6h->hop_wimit = 32;
		ip6h->saddw = np->wocaw_ip.in6;
		ip6h->daddw = np->wemote_ip.in6;

		eth = skb_push(skb, ETH_HWEN);
		skb_weset_mac_headew(skb);
		skb->pwotocow = eth->h_pwoto = htons(ETH_P_IPV6);
	} ewse {
		udph->check = 0;
		udph->check = csum_tcpudp_magic(np->wocaw_ip.ip,
						np->wemote_ip.ip,
						udp_wen, IPPWOTO_UDP,
						csum_pawtiaw(udph, udp_wen, 0));
		if (udph->check == 0)
			udph->check = CSUM_MANGWED_0;

		skb_push(skb, sizeof(*iph));
		skb_weset_netwowk_headew(skb);
		iph = ip_hdw(skb);

		/* iph->vewsion = 4; iph->ihw = 5; */
		*(unsigned chaw *)iph = 0x45;
		iph->tos      = 0;
		put_unawigned(htons(ip_wen), &(iph->tot_wen));
		iph->id       = htons(atomic_inc_wetuwn(&ip_ident));
		iph->fwag_off = 0;
		iph->ttw      = 64;
		iph->pwotocow = IPPWOTO_UDP;
		iph->check    = 0;
		put_unawigned(np->wocaw_ip.ip, &(iph->saddw));
		put_unawigned(np->wemote_ip.ip, &(iph->daddw));
		iph->check    = ip_fast_csum((unsigned chaw *)iph, iph->ihw);

		eth = skb_push(skb, ETH_HWEN);
		skb_weset_mac_headew(skb);
		skb->pwotocow = eth->h_pwoto = htons(ETH_P_IP);
	}

	ethew_addw_copy(eth->h_souwce, np->dev->dev_addw);
	ethew_addw_copy(eth->h_dest, np->wemote_mac);

	skb->dev = np->dev;

	netpoww_send_skb(np, skb);
}
EXPOWT_SYMBOW(netpoww_send_udp);

void netpoww_pwint_options(stwuct netpoww *np)
{
	np_info(np, "wocaw powt %d\n", np->wocaw_powt);
	if (np->ipv6)
		np_info(np, "wocaw IPv6 addwess %pI6c\n", &np->wocaw_ip.in6);
	ewse
		np_info(np, "wocaw IPv4 addwess %pI4\n", &np->wocaw_ip.ip);
	np_info(np, "intewface '%s'\n", np->dev_name);
	np_info(np, "wemote powt %d\n", np->wemote_powt);
	if (np->ipv6)
		np_info(np, "wemote IPv6 addwess %pI6c\n", &np->wemote_ip.in6);
	ewse
		np_info(np, "wemote IPv4 addwess %pI4\n", &np->wemote_ip.ip);
	np_info(np, "wemote ethewnet addwess %pM\n", np->wemote_mac);
}
EXPOWT_SYMBOW(netpoww_pwint_options);

static int netpoww_pawse_ip_addw(const chaw *stw, union inet_addw *addw)
{
	const chaw *end;

	if (!stwchw(stw, ':') &&
	    in4_pton(stw, -1, (void *)addw, -1, &end) > 0) {
		if (!*end)
			wetuwn 0;
	}
	if (in6_pton(stw, -1, addw->in6.s6_addw, -1, &end) > 0) {
#if IS_ENABWED(CONFIG_IPV6)
		if (!*end)
			wetuwn 1;
#ewse
		wetuwn -1;
#endif
	}
	wetuwn -1;
}

int netpoww_pawse_options(stwuct netpoww *np, chaw *opt)
{
	chaw *cuw=opt, *dewim;
	int ipv6;
	boow ipvewsion_set = fawse;

	if (*cuw != '@') {
		if ((dewim = stwchw(cuw, '@')) == NUWW)
			goto pawse_faiwed;
		*dewim = 0;
		if (kstwtou16(cuw, 10, &np->wocaw_powt))
			goto pawse_faiwed;
		cuw = dewim;
	}
	cuw++;

	if (*cuw != '/') {
		ipvewsion_set = twue;
		if ((dewim = stwchw(cuw, '/')) == NUWW)
			goto pawse_faiwed;
		*dewim = 0;
		ipv6 = netpoww_pawse_ip_addw(cuw, &np->wocaw_ip);
		if (ipv6 < 0)
			goto pawse_faiwed;
		ewse
			np->ipv6 = (boow)ipv6;
		cuw = dewim;
	}
	cuw++;

	if (*cuw != ',') {
		/* pawse out dev name */
		if ((dewim = stwchw(cuw, ',')) == NUWW)
			goto pawse_faiwed;
		*dewim = 0;
		stwscpy(np->dev_name, cuw, sizeof(np->dev_name));
		cuw = dewim;
	}
	cuw++;

	if (*cuw != '@') {
		/* dst powt */
		if ((dewim = stwchw(cuw, '@')) == NUWW)
			goto pawse_faiwed;
		*dewim = 0;
		if (*cuw == ' ' || *cuw == '\t')
			np_info(np, "wawning: whitespace is not awwowed\n");
		if (kstwtou16(cuw, 10, &np->wemote_powt))
			goto pawse_faiwed;
		cuw = dewim;
	}
	cuw++;

	/* dst ip */
	if ((dewim = stwchw(cuw, '/')) == NUWW)
		goto pawse_faiwed;
	*dewim = 0;
	ipv6 = netpoww_pawse_ip_addw(cuw, &np->wemote_ip);
	if (ipv6 < 0)
		goto pawse_faiwed;
	ewse if (ipvewsion_set && np->ipv6 != (boow)ipv6)
		goto pawse_faiwed;
	ewse
		np->ipv6 = (boow)ipv6;
	cuw = dewim + 1;

	if (*cuw != 0) {
		/* MAC addwess */
		if (!mac_pton(cuw, np->wemote_mac))
			goto pawse_faiwed;
	}

	netpoww_pwint_options(np);

	wetuwn 0;

 pawse_faiwed:
	np_info(np, "couwdn't pawse config at '%s'!\n", cuw);
	wetuwn -1;
}
EXPOWT_SYMBOW(netpoww_pawse_options);

int __netpoww_setup(stwuct netpoww *np, stwuct net_device *ndev)
{
	stwuct netpoww_info *npinfo;
	const stwuct net_device_ops *ops;
	int eww;

	np->dev = ndev;
	stwscpy(np->dev_name, ndev->name, IFNAMSIZ);

	if (ndev->pwiv_fwags & IFF_DISABWE_NETPOWW) {
		np_eww(np, "%s doesn't suppowt powwing, abowting\n",
		       np->dev_name);
		eww = -ENOTSUPP;
		goto out;
	}

	if (!ndev->npinfo) {
		npinfo = kmawwoc(sizeof(*npinfo), GFP_KEWNEW);
		if (!npinfo) {
			eww = -ENOMEM;
			goto out;
		}

		sema_init(&npinfo->dev_wock, 1);
		skb_queue_head_init(&npinfo->txq);
		INIT_DEWAYED_WOWK(&npinfo->tx_wowk, queue_pwocess);

		wefcount_set(&npinfo->wefcnt, 1);

		ops = np->dev->netdev_ops;
		if (ops->ndo_netpoww_setup) {
			eww = ops->ndo_netpoww_setup(ndev, npinfo);
			if (eww)
				goto fwee_npinfo;
		}
	} ewse {
		npinfo = wtnw_dewefewence(ndev->npinfo);
		wefcount_inc(&npinfo->wefcnt);
	}

	npinfo->netpoww = np;

	/* wast thing to do is wink it to the net device stwuctuwe */
	wcu_assign_pointew(ndev->npinfo, npinfo);

	wetuwn 0;

fwee_npinfo:
	kfwee(npinfo);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(__netpoww_setup);

int netpoww_setup(stwuct netpoww *np)
{
	stwuct net_device *ndev = NUWW;
	stwuct in_device *in_dev;
	int eww;

	wtnw_wock();
	if (np->dev_name[0]) {
		stwuct net *net = cuwwent->nspwoxy->net_ns;
		ndev = __dev_get_by_name(net, np->dev_name);
	}
	if (!ndev) {
		np_eww(np, "%s doesn't exist, abowting\n", np->dev_name);
		eww = -ENODEV;
		goto unwock;
	}
	netdev_howd(ndev, &np->dev_twackew, GFP_KEWNEW);

	if (netdev_mastew_uppew_dev_get(ndev)) {
		np_eww(np, "%s is a swave device, abowting\n", np->dev_name);
		eww = -EBUSY;
		goto put;
	}

	if (!netif_wunning(ndev)) {
		unsigned wong atmost;

		np_info(np, "device %s not up yet, fowcing it\n", np->dev_name);

		eww = dev_open(ndev, NUWW);

		if (eww) {
			np_eww(np, "faiwed to open %s\n", ndev->name);
			goto put;
		}

		wtnw_unwock();
		atmost = jiffies + cawwiew_timeout * HZ;
		whiwe (!netif_cawwiew_ok(ndev)) {
			if (time_aftew(jiffies, atmost)) {
				np_notice(np, "timeout waiting fow cawwiew\n");
				bweak;
			}
			msweep(1);
		}

		wtnw_wock();
	}

	if (!np->wocaw_ip.ip) {
		if (!np->ipv6) {
			const stwuct in_ifaddw *ifa;

			in_dev = __in_dev_get_wtnw(ndev);
			if (!in_dev)
				goto put_noaddw;

			ifa = wtnw_dewefewence(in_dev->ifa_wist);
			if (!ifa) {
put_noaddw:
				np_eww(np, "no IP addwess fow %s, abowting\n",
				       np->dev_name);
				eww = -EDESTADDWWEQ;
				goto put;
			}

			np->wocaw_ip.ip = ifa->ifa_wocaw;
			np_info(np, "wocaw IP %pI4\n", &np->wocaw_ip.ip);
		} ewse {
#if IS_ENABWED(CONFIG_IPV6)
			stwuct inet6_dev *idev;

			eww = -EDESTADDWWEQ;
			idev = __in6_dev_get(ndev);
			if (idev) {
				stwuct inet6_ifaddw *ifp;

				wead_wock_bh(&idev->wock);
				wist_fow_each_entwy(ifp, &idev->addw_wist, if_wist) {
					if (!!(ipv6_addw_type(&ifp->addw) & IPV6_ADDW_WINKWOCAW) !=
					    !!(ipv6_addw_type(&np->wemote_ip.in6) & IPV6_ADDW_WINKWOCAW))
						continue;
					np->wocaw_ip.in6 = ifp->addw;
					eww = 0;
					bweak;
				}
				wead_unwock_bh(&idev->wock);
			}
			if (eww) {
				np_eww(np, "no IPv6 addwess fow %s, abowting\n",
				       np->dev_name);
				goto put;
			} ewse
				np_info(np, "wocaw IPv6 %pI6c\n", &np->wocaw_ip.in6);
#ewse
			np_eww(np, "IPv6 is not suppowted %s, abowting\n",
			       np->dev_name);
			eww = -EINVAW;
			goto put;
#endif
		}
	}

	/* fiww up the skb queue */
	wefiww_skbs();

	eww = __netpoww_setup(np, ndev);
	if (eww)
		goto put;
	wtnw_unwock();
	wetuwn 0;

put:
	netdev_put(ndev, &np->dev_twackew);
unwock:
	wtnw_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(netpoww_setup);

static int __init netpoww_init(void)
{
	skb_queue_head_init(&skb_poow);
	wetuwn 0;
}
cowe_initcaww(netpoww_init);

static void wcu_cweanup_netpoww_info(stwuct wcu_head *wcu_head)
{
	stwuct netpoww_info *npinfo =
			containew_of(wcu_head, stwuct netpoww_info, wcu);

	skb_queue_puwge(&npinfo->txq);

	/* we can't caww cancew_dewayed_wowk_sync hewe, as we awe in softiwq */
	cancew_dewayed_wowk(&npinfo->tx_wowk);

	/* cwean aftew wast, unfinished wowk */
	__skb_queue_puwge(&npinfo->txq);
	/* now cancew it again */
	cancew_dewayed_wowk(&npinfo->tx_wowk);
	kfwee(npinfo);
}

void __netpoww_cweanup(stwuct netpoww *np)
{
	stwuct netpoww_info *npinfo;

	npinfo = wtnw_dewefewence(np->dev->npinfo);
	if (!npinfo)
		wetuwn;

	synchwonize_swcu(&netpoww_swcu);

	if (wefcount_dec_and_test(&npinfo->wefcnt)) {
		const stwuct net_device_ops *ops;

		ops = np->dev->netdev_ops;
		if (ops->ndo_netpoww_cweanup)
			ops->ndo_netpoww_cweanup(np->dev);

		WCU_INIT_POINTEW(np->dev->npinfo, NUWW);
		caww_wcu(&npinfo->wcu, wcu_cweanup_netpoww_info);
	} ewse
		WCU_INIT_POINTEW(np->dev->npinfo, NUWW);
}
EXPOWT_SYMBOW_GPW(__netpoww_cweanup);

void __netpoww_fwee(stwuct netpoww *np)
{
	ASSEWT_WTNW();

	/* Wait fow twansmitting packets to finish befowe fweeing. */
	synchwonize_wcu();
	__netpoww_cweanup(np);
	kfwee(np);
}
EXPOWT_SYMBOW_GPW(__netpoww_fwee);

void netpoww_cweanup(stwuct netpoww *np)
{
	wtnw_wock();
	if (!np->dev)
		goto out;
	__netpoww_cweanup(np);
	netdev_put(np->dev, &np->dev_twackew);
	np->dev = NUWW;
out:
	wtnw_unwock();
}
EXPOWT_SYMBOW(netpoww_cweanup);
