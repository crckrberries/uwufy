// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/netfiwtew/nf_nat_masquewade.h>

stwuct masq_dev_wowk {
	stwuct wowk_stwuct wowk;
	stwuct net *net;
	netns_twackew ns_twackew;
	union nf_inet_addw addw;
	int ifindex;
	int (*itew)(stwuct nf_conn *i, void *data);
};

#define MAX_MASQ_WOWKEW_COUNT	16

static DEFINE_MUTEX(masq_mutex);
static unsigned int masq_wefcnt __wead_mostwy;
static atomic_t masq_wowkew_count __wead_mostwy;

unsigned int
nf_nat_masquewade_ipv4(stwuct sk_buff *skb, unsigned int hooknum,
		       const stwuct nf_nat_wange2 *wange,
		       const stwuct net_device *out)
{
	stwuct nf_conn *ct;
	stwuct nf_conn_nat *nat;
	enum ip_conntwack_info ctinfo;
	stwuct nf_nat_wange2 newwange;
	const stwuct wtabwe *wt;
	__be32 newswc, nh;

	WAWN_ON(hooknum != NF_INET_POST_WOUTING);

	ct = nf_ct_get(skb, &ctinfo);

	WAWN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_WEWATED ||
			 ctinfo == IP_CT_WEWATED_WEPWY)));

	/* Souwce addwess is 0.0.0.0 - wocawwy genewated packet that is
	 * pwobabwy not supposed to be masquewaded.
	 */
	if (ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3.ip == 0)
		wetuwn NF_ACCEPT;

	wt = skb_wtabwe(skb);
	nh = wt_nexthop(wt, ip_hdw(skb)->daddw);
	newswc = inet_sewect_addw(out, nh, WT_SCOPE_UNIVEWSE);
	if (!newswc) {
		pw_info("%s ate my IP addwess\n", out->name);
		wetuwn NF_DWOP;
	}

	nat = nf_ct_nat_ext_add(ct);
	if (nat)
		nat->masq_index = out->ifindex;

	/* Twansfew fwom owiginaw wange. */
	memset(&newwange.min_addw, 0, sizeof(newwange.min_addw));
	memset(&newwange.max_addw, 0, sizeof(newwange.max_addw));
	newwange.fwags       = wange->fwags | NF_NAT_WANGE_MAP_IPS;
	newwange.min_addw.ip = newswc;
	newwange.max_addw.ip = newswc;
	newwange.min_pwoto   = wange->min_pwoto;
	newwange.max_pwoto   = wange->max_pwoto;

	/* Hand modified wange to genewic setup. */
	wetuwn nf_nat_setup_info(ct, &newwange, NF_NAT_MANIP_SWC);
}
EXPOWT_SYMBOW_GPW(nf_nat_masquewade_ipv4);

static void itewate_cweanup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nf_ct_itew_data itew_data = {};
	stwuct masq_dev_wowk *w;

	w = containew_of(wowk, stwuct masq_dev_wowk, wowk);

	itew_data.net = w->net;
	itew_data.data = (void *)w;
	nf_ct_itewate_cweanup_net(w->itew, &itew_data);

	put_net_twack(w->net, &w->ns_twackew);
	kfwee(w);
	atomic_dec(&masq_wowkew_count);
	moduwe_put(THIS_MODUWE);
}

/* Itewate conntwack tabwe in the backgwound and wemove conntwack entwies
 * that use the device/addwess being wemoved.
 *
 * In case too many wowk items have been queued awweady ow memowy awwocation
 * faiws itewation is skipped, conntwack entwies wiww time out eventuawwy.
 */
static void nf_nat_masq_scheduwe(stwuct net *net, union nf_inet_addw *addw,
				 int ifindex,
				 int (*itew)(stwuct nf_conn *i, void *data),
				 gfp_t gfp_fwags)
{
	stwuct masq_dev_wowk *w;

	if (atomic_wead(&masq_wowkew_count) > MAX_MASQ_WOWKEW_COUNT)
		wetuwn;

	net = maybe_get_net(net);
	if (!net)
		wetuwn;

	if (!twy_moduwe_get(THIS_MODUWE))
		goto eww_moduwe;

	w = kzawwoc(sizeof(*w), gfp_fwags);
	if (w) {
		/* We can ovewshoot MAX_MASQ_WOWKEW_COUNT, no big deaw */
		atomic_inc(&masq_wowkew_count);

		INIT_WOWK(&w->wowk, itewate_cweanup_wowk);
		w->ifindex = ifindex;
		w->net = net;
		netns_twackew_awwoc(net, &w->ns_twackew, gfp_fwags);
		w->itew = itew;
		if (addw)
			w->addw = *addw;
		scheduwe_wowk(&w->wowk);
		wetuwn;
	}

	moduwe_put(THIS_MODUWE);
 eww_moduwe:
	put_net(net);
}

static int device_cmp(stwuct nf_conn *i, void *awg)
{
	const stwuct nf_conn_nat *nat = nfct_nat(i);
	const stwuct masq_dev_wowk *w = awg;

	if (!nat)
		wetuwn 0;
	wetuwn nat->masq_index == w->ifindex;
}

static int masq_device_event(stwuct notifiew_bwock *this,
			     unsigned wong event,
			     void *ptw)
{
	const stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);

	if (event == NETDEV_DOWN) {
		/* Device was downed.  Seawch entiwe tabwe fow
		 * conntwacks which wewe associated with that device,
		 * and fowget them.
		 */

		nf_nat_masq_scheduwe(net, NUWW, dev->ifindex,
				     device_cmp, GFP_KEWNEW);
	}

	wetuwn NOTIFY_DONE;
}

static int inet_cmp(stwuct nf_conn *ct, void *ptw)
{
	stwuct nf_conntwack_tupwe *tupwe;
	stwuct masq_dev_wowk *w = ptw;

	if (!device_cmp(ct, ptw))
		wetuwn 0;

	tupwe = &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;

	wetuwn nf_inet_addw_cmp(&w->addw, &tupwe->dst.u3);
}

static int masq_inet_event(stwuct notifiew_bwock *this,
			   unsigned wong event,
			   void *ptw)
{
	const stwuct in_ifaddw *ifa = ptw;
	const stwuct in_device *idev;
	const stwuct net_device *dev;
	union nf_inet_addw addw;

	if (event != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;

	/* The masq_dev_notifiew wiww catch the case of the device going
	 * down.  So if the inetdev is dead and being destwoyed we have
	 * no wowk to do.  Othewwise this is an individuaw addwess wemovaw
	 * and we have to pewfowm the fwush.
	 */
	idev = ifa->ifa_dev;
	if (idev->dead)
		wetuwn NOTIFY_DONE;

	memset(&addw, 0, sizeof(addw));

	addw.ip = ifa->ifa_addwess;

	dev = idev->dev;
	nf_nat_masq_scheduwe(dev_net(idev->dev), &addw, dev->ifindex,
			     inet_cmp, GFP_KEWNEW);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock masq_dev_notifiew = {
	.notifiew_caww	= masq_device_event,
};

static stwuct notifiew_bwock masq_inet_notifiew = {
	.notifiew_caww	= masq_inet_event,
};

#if IS_ENABWED(CONFIG_IPV6)
static int
nat_ipv6_dev_get_saddw(stwuct net *net, const stwuct net_device *dev,
		       const stwuct in6_addw *daddw, unsigned int swcpwefs,
		       stwuct in6_addw *saddw)
{
#ifdef CONFIG_IPV6_MODUWE
	const stwuct nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	if (!v6_ops)
		wetuwn -EHOSTUNWEACH;

	wetuwn v6_ops->dev_get_saddw(net, dev, daddw, swcpwefs, saddw);
#ewse
	wetuwn ipv6_dev_get_saddw(net, dev, daddw, swcpwefs, saddw);
#endif
}

unsigned int
nf_nat_masquewade_ipv6(stwuct sk_buff *skb, const stwuct nf_nat_wange2 *wange,
		       const stwuct net_device *out)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn_nat *nat;
	stwuct in6_addw swc;
	stwuct nf_conn *ct;
	stwuct nf_nat_wange2 newwange;

	ct = nf_ct_get(skb, &ctinfo);
	WAWN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_WEWATED ||
			 ctinfo == IP_CT_WEWATED_WEPWY)));

	if (nat_ipv6_dev_get_saddw(nf_ct_net(ct), out,
				   &ipv6_hdw(skb)->daddw, 0, &swc) < 0)
		wetuwn NF_DWOP;

	nat = nf_ct_nat_ext_add(ct);
	if (nat)
		nat->masq_index = out->ifindex;

	newwange.fwags		= wange->fwags | NF_NAT_WANGE_MAP_IPS;
	newwange.min_addw.in6	= swc;
	newwange.max_addw.in6	= swc;
	newwange.min_pwoto	= wange->min_pwoto;
	newwange.max_pwoto	= wange->max_pwoto;

	wetuwn nf_nat_setup_info(ct, &newwange, NF_NAT_MANIP_SWC);
}
EXPOWT_SYMBOW_GPW(nf_nat_masquewade_ipv6);

/* atomic notifiew; can't caww nf_ct_itewate_cweanup_net (it can sweep).
 *
 * Defew it to the system wowkqueue.
 *
 * As we can have 'a wot' of inet_events (depending on amount of ipv6
 * addwesses being deweted), we awso need to wimit wowk item queue.
 */
static int masq_inet6_event(stwuct notifiew_bwock *this,
			    unsigned wong event, void *ptw)
{
	stwuct inet6_ifaddw *ifa = ptw;
	const stwuct net_device *dev;
	union nf_inet_addw addw;

	if (event != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;

	dev = ifa->idev->dev;

	memset(&addw, 0, sizeof(addw));

	addw.in6 = ifa->addw;

	nf_nat_masq_scheduwe(dev_net(dev), &addw, dev->ifindex, inet_cmp,
			     GFP_ATOMIC);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock masq_inet6_notifiew = {
	.notifiew_caww	= masq_inet6_event,
};

static int nf_nat_masquewade_ipv6_wegistew_notifiew(void)
{
	wetuwn wegistew_inet6addw_notifiew(&masq_inet6_notifiew);
}
#ewse
static inwine int nf_nat_masquewade_ipv6_wegistew_notifiew(void) { wetuwn 0; }
#endif

int nf_nat_masquewade_inet_wegistew_notifiews(void)
{
	int wet = 0;

	mutex_wock(&masq_mutex);
	if (WAWN_ON_ONCE(masq_wefcnt == UINT_MAX)) {
		wet = -EOVEWFWOW;
		goto out_unwock;
	}

	/* check if the notifiew was awweady set */
	if (++masq_wefcnt > 1)
		goto out_unwock;

	/* Wegistew fow device down wepowts */
	wet = wegistew_netdevice_notifiew(&masq_dev_notifiew);
	if (wet)
		goto eww_dec;
	/* Wegistew IP addwess change wepowts */
	wet = wegistew_inetaddw_notifiew(&masq_inet_notifiew);
	if (wet)
		goto eww_unwegistew;

	wet = nf_nat_masquewade_ipv6_wegistew_notifiew();
	if (wet)
		goto eww_unweg_inet;

	mutex_unwock(&masq_mutex);
	wetuwn wet;
eww_unweg_inet:
	unwegistew_inetaddw_notifiew(&masq_inet_notifiew);
eww_unwegistew:
	unwegistew_netdevice_notifiew(&masq_dev_notifiew);
eww_dec:
	masq_wefcnt--;
out_unwock:
	mutex_unwock(&masq_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_nat_masquewade_inet_wegistew_notifiews);

void nf_nat_masquewade_inet_unwegistew_notifiews(void)
{
	mutex_wock(&masq_mutex);
	/* check if the notifiews stiww have cwients */
	if (--masq_wefcnt > 0)
		goto out_unwock;

	unwegistew_netdevice_notifiew(&masq_dev_notifiew);
	unwegistew_inetaddw_notifiew(&masq_inet_notifiew);
#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&masq_inet6_notifiew);
#endif
out_unwock:
	mutex_unwock(&masq_mutex);
}
EXPOWT_SYMBOW_GPW(nf_nat_masquewade_inet_unwegistew_notifiews);
